# Winding Number Homework Problem

## Overview

We feel a short homework assignment in C++ will give us a sense of your coding abilities and will give you an example of the kind of work we do at Dyndrite. To be clear, this assignment has already been implemented several times in our own code base by many members of the team. We hope that this assignment only takes an hour or two of your time. We do not expect it to exceed 5 hours. However, feel free to devote as much or as little time as you see fit.

A winding number counts the number of times the polygon winds around a test point and is used to determine if a point is inside or outside of the given polygon. The point is outside only when the winding number equals zero; otherwise, the point is inside. Please see https://en.wikipedia.org/wiki/Winding_number for more details or ask us in an email.

We have provided [a bitbucket repository](https://bitbucket.org/dynall/winding_number_homework/src/master/) with all files needed to complete this assignment. This includes an interface for the winding number algorithm (in `winding.hpp` and `winding.cpp`), as well as some basic code to read points and polygons from an input text file (in `poly_io.hpp` and `poly_io.cpp`). It also includes a test framework with both some tests and some example input files to get you started.

The repository is located here:
https://bitbucket.org/dynall/winding_number_homework/src/master/

## What We Want

We would like you to do the following:
- Implement the winding number algorithm by subclassing the `IWindingNumberAlgorithm` interface class.
- Make the code that reads in the input text file a bit more resilient to bad input.

There are "TODO" comments with more detail scattered throughout the code.

During the interview process we will go through a code review with you to discuss any issues around readability, efficiency, and robustness. You will want to indicate any assumptions or algorithmic decisions you have made by commenting the code appropriately.

We will test your implementation with our own full set of tests that may contain errors and interesting edge cases.

Please email us your solution as a zip file and/or provide a link to download the code. You can email us at eng.careers@dyndrite.com. If we have any issues compiling/running your code, we will try to reach out to you to ensure we are able to resolve those issues.

## Getting Started

Requirements:

- Git
- CMake
- A C++17 capable compiler: Visual Studio 2019 or 2022 (when on Windows), g++ or clang

The development environment makes use of the standard [CMake](https://cmake.org/) configuration process.

- Install the above requirements
- Clone the repository for the homework problem by running `git clone git@bitbucket.org:dynall/winding_number_homework.git`
- Create a `build` directory in the `winding_number_homework` folder at the root level
- From the `build` directory, run `cmake ..` on the command-line, which will create either a Visual Studio solution or a set of Makefiles
- Either open the solution and build, or run `make` from the `build` directory
