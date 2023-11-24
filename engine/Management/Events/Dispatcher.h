#pragma once
#include <functional>
#include <unordered_map>
#include <concepts>
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>

#include "Events.h"

#define GET_ID_IMPL(type) FunctionDummy_Impl::getID<type>()

namespace engine
{
	template<typename T>
	concept EventType = std::derived_from<T, Event>;

	template<EventType type>
	using EventFn_Impl = std::function<void(const type&)>;

	class FunctionDummy_Impl
	{
	public:
		template<EventType type>
		static uint8_t getID()
		{
			static uint8_t id = idCount++;
			return id;
		}

	private:
		inline static uint8_t idCount = 0;
	};

	template<EventType type>
	struct FunctionWrapper_Impl : public FunctionDummy_Impl
	{
		FunctionWrapper_Impl(const EventFn_Impl<type>& callback) : callback(callback) {}
		EventFn_Impl<type> callback;
	};


	class Dispatcher
	{
	public:
		Dispatcher() = default;

		template<EventType type, typename F>
		[[nodiscard]] void* addListener(F&& callback)
		{
			m_callbackMap[GET_ID_IMPL(type)].emplace_back(std::make_unique<FunctionWrapper_Impl<type>>(std::forward<F>(callback)));
			
			return m_callbackMap.at(GET_ID_IMPL(type)).back().get();
		}

		template<EventType type, typename T, typename F>
		[[nodiscard]] void* addListener(T* obj, F&& callback)
		{
			return addListener<type>(std::bind_front(std::forward<F>(callback), obj));
		}

		template<EventType type>
		void removeListener(void* id)
		{
			auto& vector = m_callbackMap.at(GET_ID_IMPL(type));

			auto it = std::find_if(vector.begin(), vector.end(), [&](const auto& l) { return l.get() == id; });

			if (it != vector.end())
				vector.erase(it);
		}

	private:
		Dispatcher(const Dispatcher&) = delete;
		Dispatcher(Dispatcher&&) = delete;
		Dispatcher& operator=(const Dispatcher&) = delete;
		Dispatcher& operator=(Dispatcher&&) = delete;

	private:
		template<EventType type>
		void onNotify(const type& e)
		{
			if (m_callbackMap.find(GET_ID_IMPL(type)) == m_callbackMap.end())
				return;

			for (const auto& cb : m_callbackMap.at(GET_ID_IMPL(type)))
				static_cast<FunctionWrapper_Impl<type>*>(cb.get())->callback(e);
		}

	private:
		//TODO: CHANGE VECTOR TO UNORDERED_SET AND CHANGE REMOVE FOR CONSTANT TIME LOOK UP
		std::unordered_map<uint8_t, std::vector<std::unique_ptr<FunctionDummy_Impl>>> m_callbackMap;

		friend class EventManager;
	};
}