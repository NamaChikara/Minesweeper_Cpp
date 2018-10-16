# Minesweeper with SFML

This is an implementation of the classic game Minesweeper using the SFML graphics library. My intent in writing this program was to practice object-oriented programming. I started by C++ journey mid-August 2018, and this is my first larger-scale project.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

To run this code, you will need a C++ IDE (or familiarity with the command line) and the SFML graphics package.

### Installing

First, download SFML:

```
https://www.sfml-dev.org/download.php
```

Next, follow the "Getting Started" steps to ready SFML for the project (I used Microsoft VS 2017):

```
https://www.sfml-dev.org/tutorials/2.5/#getting-started
```

Finally, add the .cpp and .h files from this repository into a new project on your IDE.  If using VS 2017, note that you must also copy all the .dll files from  C:\...\SFML-2.5.0\bin  into your project folder  C:\...\VS_Project\VS_Project  before running the code.


## Customizing game behavior

In main.cpp, under "// game specifications", there are two variables --- dim and bombs.  The Minesweeper board is square, and dim is the number of squares per row/column.  The value of bombs determines the number of bombs on the board.

## Built With

* [Visual Studio 2017](https://docs.microsoft.com/en-us/visualstudio/) - The IDE used
* [SFML](https://www.sfml-dev.org/) - Graphics library

## Contributing

Please contact me if you are interested in contributing to this project.

## Authors

* **Zachary Barry** - [NamaChikara](https://github.com/NamaChikara)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Bjarne Stroustrup's text "Programming: Principles and Practices Using C++" is what lead me to this point.
