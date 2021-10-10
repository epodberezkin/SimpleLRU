#include <unordered_map>
#include <list>

class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {
        cache.reserve(capacity);
    }
    
    int get(int key) {
        auto iter = cache.find(key);
        if (iter == cache.end())
            return -1;
        else
        {
            int ret = iter->second.first;
            lru_order.erase(iter->second.second);
            lru_order.push_front(key);
            cache[key] = std::make_pair(ret, lru_order.begin());
            return ret;
        }
    }
    
    void put(int key, int value) {
        auto iter = cache.find(key);
        if(iter!=cache.end())
            lru_order.erase(iter->second.second);
        else if(cache.size()==_capacity)
        {
            cache.erase(lru_order.back());
            lru_order.pop_back();
        }
        lru_order.push_front(key);
        cache.insert_or_assign(key, std::make_pair(value, lru_order.begin()));
    }
private:
    const int _capacity;
    std::unordered_map<int,std::pair<int, std::list<int>::iterator>> cache;
    std::list<int> lru_order;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */