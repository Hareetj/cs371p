// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <new>       // bad_alloc, new
#include <stdexcept> // invalid_argument
#include <iostream>

using namespace std;
// ---------
// Allocator
// ---------

template <typename T, std::size_t N>
class Allocator {
    public:
        // --------
        // typedefs
        // --------

        typedef T                 value_type;

        typedef std::size_t       size_type;
        typedef std::ptrdiff_t    difference_type;

        typedef       value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef       value_type&       reference;
        typedef const value_type& const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        friend bool operator == (const Allocator&, const Allocator&) {
            return true;}                                              // this is correct

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
            return !(lhs == rhs);}

    private:
        // ----
        // data
        // ----

        char a[N];

        // -----
        // valid
        // -----

        /**
         * O(1) in space
         * O(n) in time
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

        /**
         * O(1) in space
         * O(1) in time
         * https://code.google.com/p/googletest/wiki/AdvancedGuide#Private_Class_Members
         */
        FRIEND_TEST(TestAllocator2, index);
        int& operator [] (int i) {
            return *reinterpret_cast<int*>(&a[i]);}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time
         * throw a bad_alloc exception, if N is less than sizeof(T) + (2 * sizeof(int))
         */
        Allocator () {
            if (N < (sizeof(T) + (2 * sizeof(int)))){
                std::bad_alloc exception;
                throw exception;
            }

            else{
                a[0] =  static_cast<char>((N - (2 * sizeof(int))));
                a[N-sizeof(int)] = static_cast<char>((N - (2 * sizeof(int))));
            }
            // <your code>
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Allocator  (const Allocator&);
        // ~Allocator ();
        // Allocator& operator = (const Allocator&);

        // --------
        // allocate
        // --------

        /**
         * O(1) in space
         * O(n) in time
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
         * throw a bad_alloc exception, if n is invalid
         */
        pointer allocate (size_type n) {
            int sentinel = static_cast<int>(a[0]);
            int pos1 = 0;
            int pos2;
            //cout << sentinel;
            while (pos1 < N){
                while (sentinel < 0 || (sentinel > 0 && sentinel < sizeof(T) + (2 * sizeof(int)))){
                    pos1 = sentinel * -1 + 2*sizeof(int);
                    sentintel = static_cast<int>(a[pos1]);
                }
                if (sentinel >= sizeof(T) + (2 * sizeof(int))){
                    break;
                }
            }

            if (pos1 > N){
                std::bad_alloc exception;
                throw exception;
            }

            pos2 = pos1 + sizeof(int) + n * sizeof(T);
            int nextSentinel = sentinel - sizeof(T) * n + 2 * sizeof(n);
            sentinel -= sizeof(T) * n;
            if (nextSentinel < sizeof(T) + (2 * sizeof(int))){
                std::bad_alloc exception;
                throw exception;
            }

            a[pos1] = static_cast<char>(-sentinel);
            a[pos2] = static_cast<char>(-sentinel);
            a[pos2 + sizeof(int)] = nextSentinel;
            a[pos2 + sizeof(int) + nextSentinel] = nextSentinel;

            assert(valid());
            return a[pos1+sizeof(int)];}             // replace!

        // ---------
        // construct
        // ---------

        /**
         * O(1) in space
         * O(1) in time
         */
        void construct (pointer p, const_reference v) {
            new (p) T(v);                               // this is correct and exempt
            assert(valid());}                           // from the prohibition of new

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * after deallocation adjacent free blocks must be coalesced
         * throw an invalid_argument exception, if p is invalid
         * <your documentation>
         */
        void deallocate (pointer p, size_type) {
            // <your code>
            assert(valid());}

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
         */
        void destroy (pointer p) {
            p->~T();               // this is correct
            assert(valid());}

        /**
         * O(1) in space
         * O(1) in time
         */
        const int& operator [] (int i) const {
            return *reinterpret_cast<const int*>(&a[i]);}};

#endif // Allocator_h
