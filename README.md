# CSep

Command-line tool for breaking CSV file data into white-space separated columns.

_E.g._ transform the following:

    name,age,occupation
    anna svensson,31,programmer
    bertil nilsson,52,cook
    ceasar lind,26,nurse

into:

    name           ,age ,occupation
    anna svensson  ,31  ,programmer
    bertil nilsson ,52  ,cook
    ceasar lind    ,26  ,nurse

### Installation

Go to the **csep** source-file directory and run **make**. Copy **csep.exe** to desired directory.

### Usage

    CSORT <source> [target] <delimit>

* **source** - Source file
* **target** (optional) - Output file
* **delimit** - Sequence of delimiter characters used to separated values in the source file, _e.g._, `,` (comma) in CSV files.

When no target is specified, output is written to source file.
