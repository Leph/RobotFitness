#ifndef PLOT_HPP
#define PLOT_HPP

#include <iostream>
#include <vector>

class Plot
{
    public:

        /**
         * Add a data set and its title to the ploting
         */
        static void add
            (const std::string& title, const std::vector<double>& data);

        /**
         * Plot dataset
         */
        static void plot();

    private:

        /**
         * dataset and titles container
         */
        static std::vector< std::vector<double> > _dataset;
        static std::vector<std::string> _titles;
};

#endif

