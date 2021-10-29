/**
 * g++ -Wall -pedantic -std=c++17 -fsanitize=address -o bin/analisysEmpirical
 * source/main.cpp source/lib/sorting.h source/lib/scenarios.h
 * source/lib/ClassDataScenarios.h source/lib/ClassSortingCollection.h
 * 
 * ./bin/analisysEmpirical 10 50 5 1 1 2
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <string>
#include <cassert>
#include <algorithm>
#include <functional>
using std::function;

#include "lib/sorting.h"
#include "lib/ClassDataScenarios.h"
#include "lib/ClassSortingCollection.h"


using value_type = long int;
using size_type = long int;
using duration_t = std::chrono::duration<double>;


constexpr short FIELD_WIDTH = 20;
constexpr short PRECISION = 2;


struct RunningOpt{
    size_t min_sample_sz{100};    //!< Default 10^5.
    size_t max_sample_sz{100000}; //!< The max sample size.
    int n_samples{25};            //!< The number of samples to collect.
    short which_algs{1};          //!< Bit code for the chosen algorithms to run.
    short which_scenarios{1};     //!< Bit code for the chosen scenarios to run.
    short n_runs{5};              //!< Number of rounds for each size.

    size_type sample_step(void){
        return static_cast<float>(max_sample_sz-min_sample_sz)/(n_samples-1);
    }
};


constexpr bool compare( const int&a, const int &b ){
    return ( a < b );
}


int main( int argc, char * argv[] ){
    RunningOpt run_opt;
 
    if ( argv[1] )
        run_opt.min_sample_sz = std::stoi(argv[1]);
    if ( argv[2] )
        run_opt.max_sample_sz = std::stoi(argv[2]);
    if ( argv[3] )
        run_opt.n_samples = std::stoi(argv[3]);
    if ( argv[4] )
        run_opt.which_algs = std::stoi(argv[4]);
    if ( argv[5] )
        run_opt.which_scenarios = std::stoi(argv[5]);
    if ( argv[6] )
        run_opt.n_runs = std::stoi(argv[6]);

    bool printed_header;
    size_type sample_step(run_opt.sample_step());

    DataScenarios<long int> scenariosSet{run_opt.min_sample_sz, run_opt.max_sample_sz, run_opt.which_scenarios};
    scenariosSet.start();

    using MyIt = std::vector<value_type>::iterator;
    SortingCollection<value_type, MyIt, bool (*)(const int&, const int&)> sort_algs{ run_opt.which_algs };


    // FOR EACH DATA SCENARIO DO...
    while(not scenariosSet.has_ended())
    {
        scenariosSet.reset();
        printed_header = false;

        std::stringstream headerFile, bodyFile, bodyLine;
        headerFile << "size" << ",";
                               
        std::ofstream file;
        std::string fileName = "data/" + scenariosSet.name() + ".csv";
        file.open( fileName.c_str() );

        // FOR EACH SAMPLE SIZE DO...
        for ( auto ns{1} ; ns < run_opt.n_samples ; ++ns )
        {
            scenariosSet.runScenery();
            bodyLine.str("");
            bodyLine << run_opt.max_sample_sz - ((ns-1)*sample_step) << ",";

            sort_algs.start();

            // FOR EACH SORTING ALGORITHM DO...
            while ( not sort_algs.has_ended() )
            {
                if ( not printed_header ){
                    headerFile << sort_algs.name() << ",";
                }

                duration_t elapsed_time_mean{0.0};
                auto sorting = sort_algs.algorithm();
                
                // FOR EACH RUN DO...This is necessary to reduce any measurement noise.
                for( auto ct_run(0) ; ct_run < run_opt.n_runs ; ++ct_run )
                {
                    scenariosSet.reset();

                    auto start = std::chrono::steady_clock::now();
                    sorting(scenariosSet.begin_data(), scenariosSet.end_data(), compare);
                    auto end = std::chrono::steady_clock::now();

                    auto diff( end - start );

                    elapsed_time_mean = elapsed_time_mean + (  diff - elapsed_time_mean ) 
                                        / static_cast<double>(ct_run+1);
                }
                
                bodyLine << std::fixed << std::setprecision(PRECISION)
                         << std::chrono::duration <double, std::nano> (elapsed_time_mean).count() << ",";

                sort_algs.next();
            }

            bodyFile << "\n" << bodyLine.str();
            printed_header = true;

            scenariosSet.decrease(sample_step);
        }

        file << headerFile.str();
        file << bodyFile.str();
        file.close();
        
        scenariosSet.next();
    }

    return 0;
}

