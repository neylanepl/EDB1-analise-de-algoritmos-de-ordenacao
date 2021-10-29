/**
 * Several types of sorting algorithms that work on a data range.
 * @author 
 * @date July 5th, 2021
 * @file sorting.h
 */

#ifndef SORTING_H
#define SORTING_H

#include <sstream>
using std::ostringstream;
#include <iterator>
using std::next;
using std::ostream_iterator;
#include <functional>
using std::less;
using std::function;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <algorithm>
using std::max_element;
using std::for_each;
using std::copy;
#include <cmath>
using std::pow;
#include <string>
using std::string;
using std::to_string;

namespace sa { // sa = sorting algorithms
    /// Prints out the range to a string and returns it to the client.
    template <typename FwrdIt>
    std::string to_string(FwrdIt first, FwrdIt last){
        std::ostringstream oss;
        oss << "[ ";
        while (first!=last)
            oss << *first++ << " ";
        oss << "]";
        return oss.str();
    }

    //{{{ RADIX SORT
    /*!
     * This function implements the Radix Sorting Algorithm based on the **less significant digit** (LSD).
     * 
     * @note There is no need for a comparison function to be passed as argument.
     *
     * @param first Pointer/iterator to the beginning of the range we wish to sort.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to sort.
     * @tparam FwrdIt A forward iterator to the range we need to sort.
     * @tparam Comparator A Comparator type function tha returns true if first argument is less than the second argument.
     */
    template < typename FwrdIt, typename Comparator >
    void radix( FwrdIt first, FwrdIt last, Comparator cmp )
    {   
        using myType = typename std::remove_reference<decltype(*std::declval<FwrdIt>())>::type;
        
        int index, exp=1;
        size_t arraySize = std::distance( first, last );
        std::vector <myType> auxiliary(arraySize);

        // Make a copy of elements in [first, last) range to vector auxiliary.
        std::copy( first, last, auxiliary.begin() );

        // Found the largest number.
        myType largest = *first;
        for (FwrdIt iterator=first+1; iterator<last; iterator++)
        {
            if ( cmp (largest, *iterator) )
                largest = *iterator;
        }

        while ( largest/exp > 0 )
        {
            int count[10]={0};

            for ( index=0; index< (static_cast<int> (arraySize)); index++ )
                count[( *(first+index) / exp ) % 10]++;
        
            for ( index=1; index<10; index++ )
                count[index] += count[index - 1];
        
            for ( index=arraySize-1; index>=0; index-- )
                auxiliary[--count[( *(first+index) / exp) % 10]] = *(first+index);
        
            for (index=0; index<(static_cast<int> (arraySize)); index++)
                *(first+index) = auxiliary[index];

            exp *= 10;
        }
    }
    //}}} RADIX SORT

    //{{{ INSERTION SORT
    /**
     * This function implements the Insertion Sort algorithm.
     * 
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename RandomIt, typename Compare >
    void insertion(RandomIt first, RandomIt last, Compare cmp)
    {
        for (RandomIt i = first+1; i < last; i++) 
        { 
            RandomIt j = i;
        
            while (j > first && cmp(*j, *(j-1)))
            {
                std::swap(*j, *(j-1));
                j--;
            }
	
	    }	
    }
    //}}} INSERTION SORT

    //{{{ SELECTION SORT
     /**
     * This function implements the Selection Sort algorithm.
     * 
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename RandomIt, typename Compare >
    void selection(RandomIt first, RandomIt last, Compare cmp)
    {
        for (RandomIt i = first; i < last-1; i++) 
        {
            RandomIt smaller = i;
            for (RandomIt j = i + 1; j < last; j++)
            {
                if (cmp(*j, *smaller))
                {
                   smaller = j;
                }
            }
            std::swap(*i, *smaller);
	    }
    }
    //}}} SELECTION SORT

    //{{{ BUBBLE SORT
     /**
     * This function implements the Bubble Sort algorithm.
     * 
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename RandomIt, typename Compare >
    void bubble(RandomIt first, RandomIt last, Compare cmp)
    {
        for(RandomIt i=first; i<last; i++)
        {
            for(RandomIt j=first; j<last-1; j++)
            {
                if(cmp( *(j+1), *j ))
                {
                    std::swap(*j, *(j+1));
                }
            }
        }
    }
    //}}} BUBBLE SORT

    //{{{ SHELL SORT
    /**
     * This function implements the Shell Sort algorithm.
     * 
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename RandomIt, typename Compare >
    void shell(RandomIt first, RandomIt last, Compare cmp)
    {
        int length = std::distance( first, last ), interval, i, auxiliary, j;

        while ( interval < length ) 
        {
            interval = interval*3+1;
        }

        while ( interval > 1 ) 
        {
            interval /= 3;
            for ( i = interval; i < length; i++ ) 
            {
                auxiliary = *(first + i);
                for ( j = i; j >= interval && cmp(auxiliary, *(first+(j-interval))); j-=interval ) 
                {   
                    *(first + j) = *(first + (j-interval));
                }
                *(first + j) = auxiliary;
            }
        }
    }
    //}}} SHELL SORT

    //{{{ MERGE SORT
    /**
     * Merges two subarrays of array[first..last).
     * 
     * @param L The first element in the subarray L[begin..middle).
     * @param l_last Past the last element in the subarray L[begin..middle).
     * @param R The first element in the subarray L[middle..end).
     * @param r_last Past the last element in the subarray R[middle..end).
     * @param A The first element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename FwrdIt, typename Compare >
    void mergeSort( FwrdIt L, FwrdIt l_last, // [L; l_last)
         FwrdIt R, FwrdIt r_last, // [R; r_last)
         FwrdIt A, Compare cmp)
    {
        size_t sizeArrayLeft = std::distance( L, l_last ), 
                sizeArrayRight = std::distance( R, r_last ), 
                indexArrayLeft = 0, indexArrayRight = 0, indexMergedArray = 0; 

        while (indexArrayLeft < sizeArrayLeft && indexArrayRight < sizeArrayRight) 
        {
            if ( cmp( L[indexArrayLeft], R[indexArrayRight] ) ) 
            {
                A[indexMergedArray] = L[indexArrayLeft++];
            }
            else
            {
                A[indexMergedArray] = R[indexArrayRight++];
            }
            indexMergedArray++;
        }
        
        while ( indexArrayLeft < sizeArrayLeft ) 
        {
            A[indexMergedArray++] = L[indexArrayLeft++];
        }
        
        while ( indexArrayRight < sizeArrayRight ) 
        {
            A[indexMergedArray++] = R[indexArrayRight++];
        }

    }

    /**
     * This function implements the Merge Sort algorithm.
     * 
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template< typename RandomIt, typename Compare >
    void merge(RandomIt first, RandomIt last, Compare cmp)
    {   
        using myType = typename std::remove_reference<decltype(*std::declval<RandomIt>())>::type;

        size_t length = std::distance( first, last );

        if (length > 1) 
        {
            size_t L_sz = length/2;
            size_t R_sz = length - L_sz;

            std::vector<myType> L( L_sz );
            std::vector<myType> R( R_sz );
 
            std::copy( first, first+L_sz, L.begin() );
            std::copy( first+L_sz, last, R.begin() );
            
            merge(L.begin(), L.end(), cmp);
            merge(R.begin(), R.end(), cmp);

            mergeSort( L.begin(), L.end(), R.begin(), R.end(), first, cmp );

        }
    }
    //}}} MERGE SORT

    //{{{ QUICK SORT
    /*!
     * Partition reorders the elements in the range [first;last) in such a way that
     * all elements **less** than the pivot appear before the pivot, and all elements
     * equal or greater than the pivot appear after the pivot.
     *
     * Any relative order among elements of the array might not be preserved.
     *
     * By **less** we mean a _strict order_ binary relation among the elements we
     * wantt to partition.
     *
     * \note We assume the pivot is a valid iterator in [first; last).
     *
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param pivot Location of the pivot element we need to partition the array.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     * @return An iterator to the new pivot location within the range.
     */
    template<class FwrdIt, class Compare>
    FwrdIt partition(FwrdIt first, FwrdIt last, FwrdIt pivot, Compare cmp)
    {
        FwrdIt middle = first + (last-first)/2, fast = first;

        if ( *first < *middle )
        {
            if( *middle < *(last-1) )
            {
                pivot = middle;
            }
            else if ( *first < *(last-1) )
            {
                pivot = last-1;
            }
            else
            {
                pivot = first;
            }
        }
        else
        {
            if( *(last-1) < *middle )
            {
                pivot = middle;
            }
            else if ( *(last-1) < *first )
            {
                pivot = last-1;
            }
            else
            {
                pivot = first;
            }
        }

        if ( pivot != last-1 )
        {
            std::swap( *pivot, *(last-1) );
            pivot = last-1;
        }

        for (FwrdIt j = first; j < last; j++)
        {
            if (cmp(*j, *pivot))
            {
                std::swap(*fast, *j);
                fast++;
            }
        }
        
        std::swap(*fast, *pivot);
        pivot = fast;
        
        return pivot;
    }

    /**
     * This function implements the Quick Sort algorithm.
     * 
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     */
    template<typename RandomIt, typename Compare>
    void quick(RandomIt first,RandomIt last,Compare comp){
        int length = std::distance( first, last );
        if (length <= 1)
        {
            return;
        }

        RandomIt pivot = partition( first, last, last-1, comp );
        quick( first, pivot, comp );
        quick( pivot+1, last, comp );
    }
    //}}} QUICK SORT
}
#endif // SORTING_H
