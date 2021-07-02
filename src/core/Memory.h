// Core Library - Copyright (c) 2008-2015, Glenn Fiedler

#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H

#include "core/Core.h"
#include "core/Allocator.h"
#include <new>

namespace core
{
	// memory interface

	class Allocator;

	namespace memory
	{
		void initialize( uint32_t scratch_buffer_size = 8 * 1024 * 1024 );

		Allocator & default_allocator();
		
		Allocator & scratch_allocator();
		
		void shutdown();
	}

	// helper functions used by allocator

    inline void * align_forward( void * p, uint32_t align )
    {
        uintptr_t pi = uintptr_t( p );
        const uint32_t mod = pi % align;
        if ( mod )
            pi += align - mod;
        return (void*) pi;
    }

    inline void * pointer_add( void * p, uint32_t bytes )
    {
        return (void*) ( (uint8_t*)p + bytes );
    }

    inline const void * pointer_add( const void * p, uint32_t bytes )
    {
        return (const void*) ( (const uint8_t*)p + bytes );
    }

    inline void * pointer_sub( void * p, uint32_t bytes )
    {
        return (void*)( (char*)p - bytes );
    }

    inline const void * pointer_sub( const void * p, uint32_t bytes )
    {
        return (const void*) ( (const char*)p - bytes );
    }

	// temporary allocator

	template <int BUFFER_SIZE> class TempAllocator : public Allocator
	{
	public:
		
		TempAllocator( Allocator & backing = memory::scratch_allocator() )
			: m_backing( backing ), m_chunk_size( 4*1024 )
		{
			m_p = m_start = m_buffer;
			m_end = m_start + BUFFER_SIZE;
			*(void**) m_start = 0;
			m_p += sizeof(void*);
		}

		~TempAllocator()
		{
			void * p = *(void**) m_buffer;
			while ( p ) 
			{
				void * next = *(void**) p;
				m_backing.Free( p );
				p = next;
			}
		}

		void * Allocate( uint32_t size, uint32_t align = DEFAULT_ALIGN )
		{
			m_p = (uint8_t*) align_forward( m_p, align );
			if ( (int)size > m_end - m_p )
			{
				uint32_t to_allocate = sizeof(void*) + size + align;
				if ( to_allocate < m_chunk_size)
					to_allocate = m_chunk_size;
				m_chunk_size *= 2;
				void * p = m_backing.Allocate( to_allocate );
				*(void**) m_start = p;
				m_p = m_start = (uint8_t*)p;
				m_end = m_start + to_allocate;
				*(void**) m_start = nullptr;
				m_p += sizeof(void*);
				m_p = (uint8_t*) align_forward( m_p, align );
			}
			void * result = m_p;
			m_p += size;
			return result;
		}		

		virtual void Free( void * ) {}

		virtual uint32_t GetAllocatedSize( void * ) { return SIZE_NOT_TRACKED; }

		virtual uint32_t GetTotalAllocated() { return SIZE_NOT_TRACKED; }

	private:

		uint8_t m_buffer[BUFFER_SIZE];		// local stack buffer for allocations.
		Allocator & m_backing;				// backing allocator if local memory is exhausted.
		uint8_t * m_start;					// start of current allocation region.
		uint8_t * m_p;						// current allocation pointer.
		uint8_t * m_end;					// end of current allocation region.
		unsigned m_chunk_size;				// chunks to allocate from backing allocator.
	};

	typedef TempAllocator<64> TempAllocator64;
	typedef TempAllocator<128> TempAllocator128;
	typedef TempAllocator<256> TempAllocator256;
	typedef TempAllocator<512> TempAllocator512;
	typedef TempAllocator<1024> TempAllocator1024;
	typedef TempAllocator<2048> TempAllocator2048;
	typedef TempAllocator<4096> TempAllocator4096;

	struct Header 
	{
		uint32_t size;
	};

	const uint32_t HEADER_PAD_VALUE = 0xffffffff;

	inline void * data_pointer( Header * header, uint32_t align )
	{
		void * p = header + 1;
		return align_forward( p, align );
	}

	inline Header * header( void * data )
	{
		uint32_t * p = (uint32_t*) data;
		while ( p[-1] == HEADER_PAD_VALUE )
			--p;
		return (Header*)p - 1;
	}

	inline void fill( Header * header, void * data, uint32_t size )
	{
		header->size = size;
		uint32_t * p = (uint32_t*) ( header + 1 );
		while ( p < data )
			*p++ = HEADER_PAD_VALUE;
	}

	class MallocAllocator : public Allocator
	{
		uint32_t m_total_allocated;

#if CORE_DEBUG_MEMORY_LEAKS
		std::map<void*,int> m_alloc_map;
#endif

		static inline uint32_t size_with_padding( uint32_t size, uint32_t align ) 
		{
			return size + align + sizeof( Header );
		}

	public:

		MallocAllocator() : m_total_allocated(0) {}

		~MallocAllocator()
		{
#if CORE_DEBUG_MEMORY_LEAKS
			if ( m_alloc_map.size() )
			{
				printf( "you leaked memory!\n" );
				printf( "%d blocks still allocated\n", (int) m_alloc_map.size() );
				printf( "%d bytes still allocated\n", m_total_allocated );
				for ( auto itor : m_alloc_map )
				{
					auto p = itor.first;
					printf( "leaked block %p\n", p );
				}
				exit(1);
			}
#endif
			if ( m_total_allocated != 0 )
			{
				printf( "you leaked memory! %d bytes still allocated\n", m_total_allocated );
				CORE_ASSERT( !"leaked memory" );
			}
			CORE_ASSERT( m_total_allocated == 0 );
		}

		void * Allocate( uint32_t size, uint32_t align )
		{
			const uint32_t ts = size_with_padding( size, align );
			Header * h = (Header*) malloc( ts );
			void * p = data_pointer( h, align );
			fill( h, p, ts );
			m_total_allocated += ts;
#if CORE_DEBUG_MEMORY_LEAKS
			m_alloc_map[p] = 1;
#endif
			return p;
		}

		virtual void Free( void * p ) 
		{
			if ( !p )
				return;
#if CORE_DEBUG_MEMORY_LEAKS
			auto itor = m_alloc_map.find( p );
			CORE_ASSERT( itor != m_alloc_map.end() );
			m_alloc_map.erase( p );
#endif
			Header * h = header( p );
			m_total_allocated -= h->size;
			CORE_ASSERT( m_total_allocated >= 0 );
			free( h );
		}

		virtual uint32_t GetAllocatedSize( void * p )
		{
			return header(p)->size;
		}

		virtual uint32_t GetTotalAllocated() 
		{
			return m_total_allocated;
		}
	};

	class ScratchAllocator : public Allocator
	{
		Allocator & m_backing;
		
		uint8_t * m_begin;
		uint8_t * m_end;

		uint8_t * m_allocate;
		uint8_t * m_free;
		
	public:

		ScratchAllocator( Allocator & backing, uint32_t size ) : m_backing( backing )
		{
			m_begin = (uint8_t*) m_backing.Allocate( size );
			m_end = m_begin + size;
			m_allocate = m_begin;
			m_free = m_begin;
		}

		~ScratchAllocator() 
		{
			CORE_ASSERT( m_free == m_allocate );			// You leaked memory!

			m_backing.Free( m_begin );
		}

		bool IsAllocated( void * p )
		{
			if ( m_free == m_allocate )
				return false;
			if ( m_allocate > m_free )
				return p >= m_free && p < m_allocate;
			else
				return p >= m_free || p < m_allocate;
		}

		void * Allocate( uint32_t size, uint32_t align ) 
		{
			CORE_ASSERT( align % 4 == 0 );

			size = ( ( size + 3 ) / 4 ) * 4;

			uint8_t * p = m_allocate;
			Header * h = (Header*) p;
			uint8_t * data = (uint8_t*) data_pointer( h, align );
			p = data + size;

			// Reached the end of the buffer, wrap around to the beginning.
			if ( p > m_end )
			{
				h->size = ( m_end - (uint8_t*)h ) | 0x80000000u;
				
				p = m_begin;
				h = (Header*) p;
				data = (uint8_t*) data_pointer( h, align );
				p = data + size;
			}
			
			// If the buffer is exhausted use the backing allocator instead.
			if ( IsAllocated( p ) )
				return m_backing.Allocate( size, align );

			fill( h, data, p - (uint8_t*) h );
			m_allocate = p;
			return data;
		}

		void Free( void * p ) 
		{
			if ( !p )
				return;

			if ( p < m_begin || p >= m_end )
			{
				m_backing.Free( p );
				return;
			}

			// Mark this slot as free
			Header * h = header( p );
			CORE_ASSERT( (h->size & 0x80000000u ) == 0 );
			h->size = h->size | 0x80000000u;

			// Advance the free pointer past all free slots.
			int iterations = 0;
			while ( m_free != m_allocate )
			{
				Header * h = (Header*) m_free;
				if ( ( h->size & 0x80000000u ) == 0 )
					break;

				m_free += h->size & 0x7fffffffu;
				if ( m_free == m_end )
					 m_free = m_begin ;

				iterations++;
			}
		}

		uint32_t GetAllocatedSize( void * p )
		{
			Header * h = header( p );
			return h->size - ( (uint8_t*)p - (uint8_t*) h );
		}

		uint32_t GetTotalAllocated() 
		{
			return m_end - m_begin;
		}
	};

	// macros

#if defined( _MSC_VER )
	#define _ALLOW_KEYWORD_MACROS
#endif
	
#if !defined( alignof )
	#define alignof(x) __alignof(x)
#endif

	#define CORE_NEW( a, T, ... ) ( new ((a).Allocate(sizeof(T), alignof(T))) T(__VA_ARGS__) )
	#define CORE_DELETE( a, T, p ) do { if (p) { (p)->~T(); (a).Free(p); } } while (0)	

	template <typename T> T * AllocateArray( Allocator & allocator, int arraySize, T * dummy )
	{
		T * array = (T*) allocator.Allocate( sizeof(T) * arraySize, alignof(T) );
		for ( int i = 0; i < arraySize; ++i )
			new( &array[i] ) T();
		return array;
	}

	template <typename T> void DeleteArray( Allocator & allocator, T * array, int arraySize )
	{
		for ( int i = 0; i < arraySize; ++i )
			(&array[i])->~T();
		allocator.Free( array );
	}

	#define CORE_NEW_ARRAY( a, T, count ) AllocateArray( a, count, (T*)nullptr )
	#define CORE_DELETE_ARRAY( a, array, count ) DeleteArray( a, array, count )

}

#endif
