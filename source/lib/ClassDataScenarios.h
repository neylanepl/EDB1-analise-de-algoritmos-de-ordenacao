#ifndef DATA_SCENARIOS_H
#define DATA_SCENARIOS_H

#include <utility>
#include <vector>

#include "ClassSortingCollection.h"
#include "scenarios.h"


template <typename DataType>
class DataScenarios {
    private:
        size_t max_sample_sz;
        size_t min_sample_sz;

        std::vector<DataType> data;
        std::vector<DataType> data_copy;
        typename std::vector<DataType>::iterator first_copy, last_copy;
        DataType *first, *last;

        using DataIt = typename std::vector<DataType>::iterator;
        using value_t = DataType;
        using ScenariosFuncType = void (*)(value_t *, value_t *);
        using MapItem = std::pair<std::string, ScenariosFuncType>;

        std::vector<MapItem> m_scenarios;
        typename std::vector<MapItem>::iterator m_curr_scenery;

    public:
        enum scenarios_t {
            NOTDECREASING = 1,
            NOTGROWING = 2,
            RANDOM = 4,
            _75PERINDEFINITIVEPOSITION = 8,
            _50PERINDEFINITIVEPOSITION = 16,
            _25PERINDEFINITIVEPOSITION = 32,
            ALL_SCENARIOS = 63,
        };

    public:
        DataScenarios( size_t m_min_sample_sz, size_t m_max_sample_sz, short selected_scenarios = 1 ) {

            if ( selected_scenarios & NOTDECREASING)
                m_scenarios.push_back(std::make_pair<std::string, ScenariosFuncType>("notDecreasing", sc::notDecreasing));

            if ( selected_scenarios & NOTGROWING)
                m_scenarios.push_back(std::make_pair<std::string, ScenariosFuncType>("notGrowing", sc::notGrowing));

            if ( selected_scenarios & RANDOM)
                m_scenarios.push_back(std::make_pair<std::string, ScenariosFuncType>("random", sc::random));

            if ( selected_scenarios & _75PERINDEFINITIVEPOSITION)
                m_scenarios.push_back(std::make_pair<std::string, ScenariosFuncType>("_75perInDefinitivePosition", sc::_75perInDefinitivePosition));

            if ( selected_scenarios & _50PERINDEFINITIVEPOSITION)
                m_scenarios.push_back(std::make_pair<std::string, ScenariosFuncType>("_50perInDefinitivePosition", sc::_50perInDefinitivePosition));

            if ( selected_scenarios & _25PERINDEFINITIVEPOSITION)
                m_scenarios.push_back(std::make_pair<std::string, ScenariosFuncType>("_25perInDefinitivePosition", sc::_25perInDefinitivePosition));

            m_curr_scenery = m_scenarios.begin();

            size_t data_size = m_max_sample_sz - m_min_sample_sz;
            data.resize(data_size);
            data_copy.resize(data_size);

            for ( size_t i=0; i<data_size; i++ )
                data.at(i) = i+1;
            
            first = &*data.begin();
            last = &*data.end();
            first_copy = data_copy.begin();
            last_copy = data_copy.end();

            reset();
        }
        
        void start( void ) {
            m_curr_scenery = m_scenarios.begin();
            runScenery();
            reset();
        }

        void next( void ) {
            m_curr_scenery++;
            resetPointers();
        }

        void reset( void ) {
            std::copy(data.begin(), data.end(), data_copy.begin());
        }

        void resetPointers(){
            first_copy = data_copy.begin();
            first = &*data_copy.begin();
        }

        DataIt begin_data( void ) {
            return first_copy;
        }

        DataIt end_data( void ) {
            return last_copy;
        }

        void decrease( DataType decrement ) {
            first_copy += decrement;
            first += decrement;
        }

        bool has_ended( void ) const {
            if ( m_curr_scenery != m_scenarios.end() )
                return false;
            return true;
        }

        std::string name( void ) {
            return (*m_curr_scenery).first;
        }

        void runScenery ( void ) {
            reset();
            auto scenery = (*m_curr_scenery).second;
            sc::notDecreasing(first, last);

            scenery(first, last);
        }
        
};


#endif // DATA_SCENARIOS_H