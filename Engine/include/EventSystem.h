#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>

class EventSystem
{
public:
	template<typename EventType>
	using Handler = std::function<void( const EventType& )>;

	template<typename EventType>
	void subscribe( Handler<EventType> handler )
	{
		auto& handlers = m_handlers[typeid( EventType )];
		handlers.push_back( [h = std::move( handler )] ( const void* event )
			{
				h( *static_cast<const EventType*>( event ) );
			} );
	}

	template<typename EventType>
	void publish( const EventType& event )
	{
		auto it = m_handlers.find( typeid( EventType ) );
		if ( it != m_handlers.end() )
		{
			for ( auto& handler : it->second )
			{
				handler( &event );
			}
		}
	}

private:
	std::unordered_map<std::type_index, std::vector<std::function<void( const void* )>>> m_handlers;
};