#include <cstdio>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include "Plot.hpp"

std::vector< std::vector<double> > Plot::_dataset;
std::vector<std::string> Plot::_titles;

void Plot::add
    (const std::string& title, const std::vector<double>& data)
{
    _titles.push_back(title);
    _dataset.push_back(data);
}

void Plot::plot()
{
    if (_dataset.size() == 0) {
        return;
    }

    //Creating pipe
    int fd[2];
    if (pipe(fd) == -1) {
        throw std::string("Unable to pipe");
    }

    //Fork
    pid_t pid = fork();
    //Parent
    if (pid > 0) {
        close(fd[0]);
        //Dataset length check
        for (size_t i=1;i<_dataset.size();i++) {
            if (_dataset[i].size() != _dataset[0].size()) {
                throw std::string("Dataset have different length");
            }
        }
        size_t length = _dataset[0].size();
        //Output data lines
        for (size_t j=0;j<_dataset.size();j++) {
            for (size_t i=0;i<length;i++) {
                std::ostringstream oss;
                oss << _dataset[j][i];
                std::string line;
                line += oss.str();
                line += "\n";
                if (
                    write(fd[1], line.c_str(), line.size()) != 
                    (ssize_t)line.size()
                ) {
                    throw std::string("Fail to write");
                }
            }
            char eof[] = "e\n";
            if (write(fd[1], &eof, 2) != 2) {
                throw std::string("Fail to write");
            }
        }
        close(fd[1]);
        //Clear saved dataset
        _titles.clear();
        _dataset.clear();
        return;
    //Child
    } else if (pid == 0) {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            throw std::string("Unable to dup2");
        }
        std::string command;
        command += "plot ";
        for (size_t i=0;i<_dataset.size();i++) {
            if (i > 0) {
                command += " ,";
            } 
            command += "'-' with lines title '";
            command += _titles[i];
            command += "'";
        }
        execlp("gnuplot", "gnuplot", "-p", "-e", 
            command.c_str(), NULL);
    //Error
    } else {
        throw std::string("Unable to fork");
    }
}

