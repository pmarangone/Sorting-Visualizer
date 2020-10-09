# Sorting Visualizer in C++ 

This is my Capstone Project for the Udacity C++ Nanodegree. After launching the program you can choose (with your mouse) between [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort), [QuickSort](https://en.wikipedia.org/wiki/Quicksort), and [Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort). When the sorting is done, you can generate a new array and pick another algorithm. To exit, press ESC.
<br>

![alt text](https://github.com/mestto/Sorting-Visualizer/blob/master/images/visu.png "Logo Title Text 1")


## Project Structure

`button.h/button.cpp`: Contains a class _Button_ that is responsible for creating places in the screen where it is responsive to clicks.

`layout.h/layout.cpp`: Contains a class _Layout_ that was written with the goal of easy portability. You can place it in a SDL application and add text to it with ease. Here, it display the sorting algorithm names and the project name. 

`quickSort.h/mergeSort.h`: Contains both the functions that operate in the array and the functions that are responsible for the update of the screen and display of the sorting algorithm. 

`main.h/main.cpp`: Contains the initialization of SDL and SDL_TFF. The text and buttons are inicialized afterwards. The first loop keeps checking for input of the user (through the buttons in the screen and keys) and a second loop is started only if the user choose a sorting algorithm and inicialize it. A condition variable is then used with a mutex to restrict changes in the array until the end of the sorting.

## Dependencies for Running Locally [(extended from here)](https://github.com/udacity/CppND-Capstone-Hello-World)
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_ttf >= 2.0
  * All installation instructions can be found [here (ubuntu)](https://www.howtoinstall.me/ubuntu/18-04/libsdl2-ttf-dev/) or [here (from source)](https://www.libsdl.org/projects/SDL_ttf/release-1.2.html)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Visualizer`.

## Basic Instructions
- Rightwards arrow ( → ) increments array size
- Leftwards arrow ( ← ) decrements array size

## References for SDL:
  - https://lazyfoo.net/tutorials/SDL/
