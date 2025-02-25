#include <map>
#include <limits>
#include <iostream>
#include <vector>
#include <type_traits>
template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
    interval_map(V const& val) : m_valBegin(val) {
        m_map[std::numeric_limits<K>::min()]=val;
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        //the following 2 if's didn't work, just left them here
        if(     !std::is_arithmetic<K>::value &&
                std::is_copy_assignable<K>::value &&
                std::is_copy_constructible<K>::value &&
                std::is_same<decltype(std::declval<K>() < std::declval<K>()), bool>::value)
        {
            return;
        }

        if(     !std::is_arithmetic<V>::value &&
                 std::is_copy_assignable<V>::value &&
                 std::is_copy_constructible<K>::value &&
                 std::is_same<decltype(std::declval<V>() == std::declval<V>()), bool>::value)
        {
            return;
        }

        if( !(keyBegin < keyEnd) )
            return;

        //everything bigger than keyEnd is whatever was there before
        //get that value
        V valEnd = (*this)[keyEnd];

        //delete everything in between
        auto it=m_map.upper_bound(keyBegin);
        while(it!=m_map.upper_bound(keyEnd)){
            auto it_next = it;
            it_next++;
            m_map.erase(it);
            it = it_next;
        }

        //assign that value to keyEnd
        m_map[keyEnd]=valEnd;

        //everything bigger than keyBegin is val
        if(val != m_valBegin) m_map[keyBegin]=val;

    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it=m_map.upper_bound(key);
        if(it==m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
};

template<typename K, typename V>
void InnerIntervalMapTest(interval_map<K, V> imap, K key, V val, int test_nr){
    V res_val = imap[key];
    if(res_val != val){
        std::cout << "Test " << test_nr << " failed" << "Error: " << key <<
                        " should be " << val << " but is " << res_val << std::endl;
    }else{
        std::cout << "Test " << test_nr << " passed" << std::endl;
    }
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.
void IntervalMapTest(){
    interval_map<int,char> imap('A');

    struct Data{
        int key;
        char value;
    };

    std::vector<Data> test_map;

    imap.assign(60, 70, 'B');
    imap.assign(60, 61, 'C');
    imap.assign(-1000, -100, 'K');
    imap.assign(-1, 0, 'K');
    imap.assign(10, 20, 'X');
    imap.assign(22, 23, 'Y');
    imap.assign(24, 30, 'Z');
    imap.assign(15, 25, 'W');
    imap.assign(15, 25, 'M');
    imap.assign(15, 32, 'M');

    imap.assign(10000, 10100, 'M');
    imap.assign(10050, 10150, 'N');

    test_map.push_back({ 10040, 'M'});
    test_map.push_back({ 10060, 'N'});

    test_map.push_back({ 10, 'X'});
    test_map.push_back({ 14, 'X'});
    test_map.push_back({ 15, 'M'});
    test_map.push_back({ 17, 'M'});
    test_map.push_back({ 20, 'M'});
    test_map.push_back({ 22, 'M'});
    test_map.push_back({ 24, 'M'});
    test_map.push_back({ 31, 'M'});
    test_map.push_back({ 35, 'A'});
    test_map.push_back({70, 'A'});
    test_map.push_back({100, 'A'});
    test_map.push_back({1000, 'A'});
    test_map.push_back({59, 'A'});
    test_map.push_back({60, 'C'});
    test_map.push_back({61, 'B'});
    test_map.push_back({69, 'B'});
    test_map.push_back({70, 'A'});
    test_map.push_back({71, 'A'});
    test_map.push_back({-1, 'K'});
    test_map.push_back({0, 'A'});
    test_map.push_back({-100, 'A'});
    test_map.push_back({-1000, 'K'});
    test_map.push_back({-1001, 'A'});
    test_map.push_back({-2, 'A'});

    int test_cnt = 1;
    for(auto i: test_map)
        InnerIntervalMapTest(imap, i.key, i.value, test_cnt++);

}

int main(){
    IntervalMapTest();
    return 0;
}