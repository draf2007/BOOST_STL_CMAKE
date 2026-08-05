#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

//#define DEBUG_SECTION(x) x;
#define DEBUG_SECTION(x);

namespace my
{
    template<typename T>
    class Alloc
    {
        template <typename U> friend class Alloc;
       
    public:
        using Byte = uint8_t;
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using void_pointer = void*;
        using const_void_pointer = const void*;
        using size_type = size_t;

        Alloc() = delete;
        Alloc(void_pointer mem, size_t size) : 
              m_mem((Byte*)mem)
            , m_size(size)
            , m_cursor((Byte*)mem)
            , m_max_el_count(size/sizeof(T))
            , m_el_size(sizeof(T))
        {
            DEBUG_SECTION(std::cout << "Alloc\n");
        }

        template<typename U>
        Alloc(const Alloc<U>& other)
        {
            DEBUG_SECTION(std::cout << "Alloc rebind\n");
            m_mem = other.m_mem;
            m_size = other.m_size;
            m_cursor = other.m_cursor;
            m_max_el_count = m_size / sizeof(Alloc<T>::value_type);
            m_el_size = sizeof(Alloc<T>::value_type);
        }

        pointer allocate(size_type n, const_void_pointer* hint = nullptr) 
        {
            DEBUG_SECTION(std::cout << "allocate n = " << n << "\n");
            if (!m_mem)
                throw std::bad_alloc();

            if (n > m_max_el_count)
                throw std::bad_alloc();

            auto ptr = (pointer)m_cursor;
            m_cursor += n * m_el_size;

            return ptr;
        }

        void deallocate(T* p, size_type n) {
            //NOTHING TO DO
            DEBUG_SECTION(std::cout << "deallocate\n");
        }

        template<typename U, typename... Args>
        void construct(U* p, Args&&... args) {
            DEBUG_SECTION(std::cout << "construct\n");
            ::new((void*)p) U(std::forward<Args>(args)...);
        }

        template<typename U>
        void destroy(U* p)
        {
            DEBUG_SECTION(std::cout << "destroy\n");
            p->~T();
        }

    private:
        Byte* m_mem = nullptr;
        size_type m_size = 0;

        Byte* m_cursor = nullptr;
        size_type m_max_el_count = 0;
        size_type m_el_size = 0;
    };

    class Time
    {
    public:
        Time() {
            start();
        }

        void start() {
            m_tp = std::chrono::steady_clock::now();
        }

        auto elapsed() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - m_tp).count();
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> m_tp;
    };
}

void test_alloc_1()
{
    std::cout << "------ALLOC MAIN MEM----\n";
    constexpr size_t mem_size = 256;
    uint8_t mem[mem_size];
    memset(mem, 0, mem_size);

    std::cout << "---------ADD ELEMENTS---------\n";
    my::Alloc<int> alloc(mem, mem_size);
    std::vector<decltype(alloc)::value_type, decltype(alloc)> mv(alloc);
    //mv.reserve(10);
    for (size_t i = 0; i < 10; i++) {
        mv.push_back(i);
    }

    std::cout << "--------PRINT MEMORY----------\n";
    std::for_each(mem, mem + mem_size, [](int v) {std::cout << v << " ";});
    std::cout << std::endl;
}

int main()
{
    std::cout << "------ALLOC MAIN MEM----\n";
    constexpr size_t mem_size = 1024 * 1024 * 8;
    std::unique_ptr<uint8_t> pmem(new uint8_t[mem_size]);
    auto mem = pmem.get();
    memset(mem, 0, mem_size);

    std::cout << "------ALLOC AND CONTAINER PREPARATION----\n";
    my::Alloc<int> alloc(mem, mem_size);
    std::vector<decltype(alloc)::value_type, decltype(alloc)> mv(alloc);
    std::vector<int> v;

    constexpr size_t elements_count = 10000;
    
    {
        std::cout << "------MY ALLOC TEST----\n";
        my::Time t;
        mv.reserve(elements_count);
        for (size_t i = 0; i < elements_count; i++) {
            mv.push_back(i);
        }
        std::cout << "my alloc: " << t.elapsed() << std::endl;
    }

    {
        std::cout << "------STD ALLOC TEST----\n";
        my::Time t;
        v.reserve(elements_count);
        for (size_t i = 0; i < elements_count;i++) {
            v.push_back(i);
        }
        std::cout << "std alloc: " << t.elapsed() << std::endl;
    }
}
