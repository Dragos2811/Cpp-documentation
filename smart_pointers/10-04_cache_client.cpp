#include <iostream>
#include <memory>
#include <string>

#include "cache.h"
#include "ring.h"

using namespace std;


int main()
{
    ring<shared_ptr<string>> names{3, {
        make_shared<string>("Ana"),
        make_shared<string>("Maria"),
        make_shared<string>("Ioana")
    }};
    cache<string> my_cache{names};
    
    cout << *my_cache.get(1) << endl;  // from cache, but first it's fetched from ring
    cout << *my_cache.get(1) << endl;  // from cache

    return 0;
}
