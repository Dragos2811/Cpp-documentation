#pragma once

#include <map>
#include <memory>
#include <iostream>
#include <mutex>

#include "ring.h"


template<typename T>
class cache
{
public:
    cache(ring<std::shared_ptr<T>> ring) : m_ring{ring} {}
    
    std::shared_ptr<T> get(int key) throw(std::string)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        auto shared_p{m_cache[key].lock()};
        if (!shared_p) {
            auto value {m_ring.get(key)};  // value is shared_ptr
            m_cache[key] = value;  // as weak_ptr!! (weak = shared)
            shared_p = value;
        }
        return shared_p;
        // at this point, use_count >= 2, and client uses a shared_ptr =>
        // impossible for the area to be deleted!
        // because in the client use_count >= 1 (always!!)
    }

    T* bad_get(int key) throw(std::string)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        auto shared_p{m_cache[key].lock()};
        if (!shared_p) {
            auto value {m_ring.get(key)};  // value is shared_ptr
            m_cache[key] = value;  // as weak_ptr!!
            shared_p = value;
        }
        return shared_p.get();
        // at this point, use_count = 1 => you may use a pointer to a deleted area
        // in the client
    }
    
private:
    ring<std::shared_ptr<T>> m_ring;
    std::map<int, std::weak_ptr<T>> m_cache{};
    std::mutex m_mutex{};
};
