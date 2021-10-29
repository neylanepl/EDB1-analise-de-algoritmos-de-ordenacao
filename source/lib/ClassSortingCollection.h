#ifndef SORTING_COLLECTION_H
#define SORTING_COLLECTION_H

#include <vector>
using std::vector;
#include <iterator>
using std::advance;
#include <utility>
using std::pair;

#include "sorting.h"

template <typename DataType, typename RandomIt, typename Compare>
class SortingCollection {
    private:
        using value_t = DataType;
        using SortFuncType = void (*)(RandomIt, RandomIt, Compare);
        using MapItem = std::pair<std::string, SortFuncType>;

        vector<MapItem> m_sorting_algs;
        typename vector<MapItem>::iterator m_curr_algo;

    public:
        enum algorithm_t {
            INSERTION = 1,
            SELECTION = 2,
            BUBBLE = 4,
            SHELL = 8,
            QUICK = 16,
            MERGE = 32,
            RADIX = 64,
            ALL_ALGORITHMS = 127,
        };

        SortingCollection(short selected_algs = 1){

            if ( selected_algs & INSERTION)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("insertion", sa::insertion));
                
            if ( selected_algs & SELECTION)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("selection", sa::selection));

            if ( selected_algs & BUBBLE)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("bubble", sa::bubble));

            if ( selected_algs & SHELL)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("shell", sa::shell));

            if ( selected_algs & QUICK)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("quick", sa::quick));

            if ( selected_algs & MERGE)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("merge", sa::merge));

            if ( selected_algs & RADIX)
                m_sorting_algs.push_back(std::make_pair<std::string, SortFuncType>("radix", sa::radix));

            m_curr_algo = m_sorting_algs.begin();
        }
        
        void start(void) {
            m_curr_algo = m_sorting_algs.begin();
        }

        void next(void) {
            m_curr_algo++;
        }

        bool has_ended(void) const {
            if ( m_curr_algo != m_sorting_algs.end() )
                return false;
            return true;
        }
        
        SortFuncType algorithm(void) const {
            return (*m_curr_algo).second;
        }

        std::string name(void) const {
            return (*m_curr_algo).first;
        }
};


#endif // SORTING_COLLECTION_H
