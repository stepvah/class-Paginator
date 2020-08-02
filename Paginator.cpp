// Here is function main starts
#include "profile.h"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <numeric>
#include <vector>


using namespace std;



template<typename Iterator>
struct IteratorRange {
    Iterator first, last;
    size_t size_;

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return size_;
    }

};

template<typename iterator>
bool operator==(const IteratorRange<iterator>& lhs, const IteratorRange<iterator>& rhs) {
    return lhs.first == rhs.first && lhs.last == rhs.last;
}

template<typename iterator>
bool operator!=(const IteratorRange<iterator>& lhs, const IteratorRange<iterator>& rhs) {
    return !(lhs == rhs);
}


template<typename Iterator>
IteratorRange<Iterator> Head(const Iterator& begin,
    const Iterator& last, size_t top) {
    Iterator cur = begin;
    size_t size = 0;
    for (; size < top && cur != last; ++size, ++cur) {}

    return IteratorRange<Iterator>{ begin, cur, size };
}


template<typename Iterator>
class Paginator {
private:
    vector<IteratorRange<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end,
        size_t page_size) : pages({}) {
        Iterator cur = begin;
        while (cur != end) {
            pages.push_back(Head(cur, end, page_size));
            cur = pages.back().last;
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }

};


template<typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

#include "tests.h"


int main()
{
    std::cout << "Hello World!\n";
    TestAll();
}
