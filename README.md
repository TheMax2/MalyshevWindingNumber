# winding_number_homework

Basic 2D Geometry Coding

We feel a short homework assignment will allow us to get a feel for your coding abilities and gives you an example of what kind of work we do at Dyndrite. To be clear, this assignment has already been implemented several times in our own code base by many members of the team. We expect it to take no more than 5 hours to complete.

You will implement a winding number class and improve a polygon reader class in C++. The winding number class computes the winding number of each polygon. The polygon reader class reads in the points and polygons from a simple text format that is described below.

A winding number counts the number of times the polygon winds around a test point and is used to determine if a point is inside or outside of the given polygon. The point is outside only when the winding number equals zero; otherwise, the point is inside. Please see https://en.wikipedia.org/wiki/Winding_number for more details or ask us in an email.

We have provided a bitbucket repository with all files needed to complete this assignment. This includes an interface for the winding number algorithm (in winding.hpp and winding.cpp), as well as some basic code to read points and polygons from an input text file (in poly_io.hpp and poly_io.cpp). It also includes a test framework with some tests and example input files to get you started.

We would like you to implement the winding number algorithm by subclassing the interface class, and we would like you to make the file reading code a bit more resilient to bad inputs. There are TODO comments with details throughout the code.

The repository is located here:
https://bitbucket.org/dynall/winding_number_homework/src/master/

We will test your implementation locally with a different set of test files that may contain errors and interesting edge cases. You will want to indicate any algorithmic decisions you've made via comments in the code. During the in-person interview, we will also do a code review with you to check out readability, efficiency, and robustness. If we have any issues compiling/running your code, we will reach out to you to ensure we resolve those issues.

Please email us your solution as a zip file and/or provide a link to download it. You can email us at eng.careers@dyndrite.com.