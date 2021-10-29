
#ifndef _SCENARIOS_
#define _SCENARIOS_

#include <iostream>     // lib padrão
#include <vector>       // std::vector 
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


namespace sc { // sc = sorting algorithms
    /*!
     * This function arranges the sample (array) for non-descending elements.
     * 
     * @param first Pointer/iterator to the beginning of the range we wish to arrange.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to arrange.
     * @tparam FwrdIt A forward iterator to the range we need to arrange.
     */
    template< typename FwrdIt >
    void notDecreasing( FwrdIt first, FwrdIt last )
    {
        size_t length = std::distance( first, last );

        for (size_t i = 0; i < length; i++)
        {   
            for (size_t j = 0; j < length-i-1; j++)
            {
                if (*(first+j) > *(first+j+1))
                {
                    std::swap(*(first+j), *(first+j+1));
                }
            }
        }
    }

    /*!
     * This function arranges the sample (array) for non-growing elements.
     * 
     * @param first Pointer/iterator to the beginning of the range we wish to arrange.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to arrange.
     * @tparam FwrdIt A forward iterator to the range we need to arrange.
     */
    template< typename FwrdIt >
    void notGrowing( FwrdIt first, FwrdIt last )
    {
        size_t length = std::distance( first, last );

        for (size_t i = 0; i < length; i++)
        {   
            for (size_t j = 0; j < length-i-1; j++)
            {
                if (*(first+j) < *(first+j+1))
                {
                    std::swap(*(first+j), *(first+j+1));
                }
            }
        }
    }

    /*!
     * This function arranges the sample (array) for random elements.
     * 
     * @param first Pointer/iterator to the beginning of the range we wish to arrange.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to arrange.
     * @tparam FwrdIt A forward iterator to the range we need to arrange.
     */
    template< typename FwrdIt >
    void random( FwrdIt first, FwrdIt last )
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        
        std::shuffle(first, last, std::default_random_engine(seed));
    }

    /*!
     * This function arranges the sample (array) for 75 percent of elements in definite position.
     * 
     * @param first Pointer/iterator to the beginning of the range we wish to arrange.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to arrange.
     * @tparam FwrdIt A forward iterator to the range we need to arrange.
     */
    template< typename FwrdIt >
    void _75perInDefinitivePosition( FwrdIt first, FwrdIt last )
    {   
        size_t length = std::distance( first, last );

        for (size_t i = 0; i <= (0.25*length); i+=2)
        {
            std::swap(*(first+i), *(first+i+1));
        }
    }

    /*!
     * This function arranges the sample (array) for 50 percent of elements in definite position.
     * 
     * @param first Pointer/iterator to the beginning of the range we wish to arrange.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to arrange.
     * @tparam FwrdIt A forward iterator to the range we need to arrange.
     */
    template< typename FwrdIt >
    void _50perInDefinitivePosition( FwrdIt first, FwrdIt last )
    {
        size_t length = std::distance( first, last );

        for (size_t i = 0; i <= (0.50*length); i+=2)
        {
            std::swap(*(first+i), *(first+i+1));
        }
    }

    /*!
     * This function arranges the sample (array) for 25 percent of elements in definite position.
     * 
     * @param first Pointer/iterator to the beginning of the range we wish to arrange.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to arrange.
     * @tparam FwrdIt A forward iterator to the range we need to arrange.
     */
    template< typename FwrdIt >
    void _25perInDefinitivePosition( FwrdIt first, FwrdIt last )
    {
        size_t length = std::distance( first, last );

        for (size_t i = 0; i <= (0.75*length); i+=2)
        {
            std::swap(*(first+i), *(first+i+1));
        }
    }
}

#endif //_SCENARIOS_
