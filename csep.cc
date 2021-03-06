/******************************************
 * CSEP utility tool                      *
 *                                        *
 * Author: Felix Glas                     *
 * License: CC0 1.0 Universal             *
 ******************************************/

#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const std::string VERSION = "1.2.1";

int main(int argc, char* argv[]) {
    // 浜様様様様様様様様様様様様様様様融
    // � Check program input arguments. �
    // 藩様様様様様様様様様様様様様様様夕
    if (argc <= 2 || argc >= 5) {
        std::cout << "CSep column separate utility. Version " << VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Usage: CSEP <source> [target] <delimit>" << std::endl;
        return EXIT_FAILURE;
    }

    // 浜様様様様様様様様様様様様融
    // � Check output parameters. �
    // 藩様様様様様様様様様様様様夕
    if (argc == 4) {
        // Check that output file is not the same as input file.
        if (argv[1] == argv[2]) {
            std::cerr << "Output file can not be same as input file" << std::endl;
            return EXIT_FAILURE;
        }

        // Check if output file already exists.
        std::ifstream outputTest{argv[2]};
        if (outputTest) {
            std::string line;
            do {
                std::cout << "File \"" << argv[2] << "\" already exists. Replace? (y/n): ";
                std::getline(std::cin, line);
                std::transform(std::begin(line), std::end(line), std::begin(line), [] (auto c) { return std::tolower(c); });
            } while (line != "y" && line != "n");
            if (line == "n") {
                return EXIT_FAILURE;
            }
        }
    } else {
        // Check that file contents should be replaced.
        {
            std::string line;
            do {
                std::cout << "Are your sure you want to replace file contents? (y/n): ";
                std::getline(std::cin, line);
                std::transform(std::begin(line), std::end(line), std::begin(line), [] (auto c) { return std::tolower(c); });
            } while (line != "y" && line != "n");
            if (line == "n") {
                return EXIT_FAILURE;
            }
        }
    }

    // 浜様様様様様様様様様様様様様様融
    // � Open input file for reading. �
    // 藩様様様様様様様様様様様様様様夕
    std::ifstream input{argv[1]};

    // 浜様様様様様様様様様様様様様様�
    // � Check if input file exists. �
    // 藩様様様様様様様様様様様様様様�
    if (!input) {
        std::cerr << "Input file could not be found" << std::endl;
        return EXIT_FAILURE;
    }

    // 浜様様様様様様様様様様様様様様様様様様様様融
    // � Read delimiter string from command line. �
    // 藩様様様様様様様様様様様様様様様様様様様様夕
    std::string delimit = argc == 4 ? argv[3] : argv[2];

    // 浜様様様様様様様様様様様様様様様�
    // � Read column widths from data. �
    // 藩様様様様様様様様様様様様様様様�
    std::cout << "Reading column widths..." << std::endl;
    std::vector<std::string::size_type> columnWidths;
    for (std::string line; std::getline(input, line);) {
        std::size_t count = 0;
        std::string::size_type startPos = 0, pos = 0;
        do {
            pos = line.find(delimit, startPos);
            auto endPos = (pos == std::string::npos) ? line.size() : pos;
            auto width = endPos - startPos;
            auto charPos = endPos - 1;
            if (charPos < line.size() && (line.at(charPos) == ' ' || line.at(charPos) == '\t')) {
                --width;
            }
            if (++count > columnWidths.size()) {
                columnWidths.push_back(width);
            } else {
                if (width > columnWidths[count - 1]) {
                    columnWidths[count - 1] = width;
                }
            }
            startPos = endPos + 1;
        } while (pos != std::string::npos);
    }

    // Reset input file to beginning.
    input.clear();
    input.seekg(0, std::ios::beg);

    // 浜様様様様様様様様様様様様様様様様様様様様様�
    // � Adjust column widths and store in vector. �
    // 藩様様様様様様様様様様様様様様様様様様様様様�
    std::cout << "Processing file..." << std::endl;
    std::vector<std::string> rows;
    {
        // Output directly to file if using separate output file.
        std::ofstream output;
        if (argc == 4) {
            output.open(argv[2]);
        }

        // Identify and indent columns according to maximum column widths.
        for (std::string line; std::getline(input, line);) {
            decltype(columnWidths)::size_type index = 0;
            std::string::size_type startPos = 0, pos = 0;
            std::ostringstream row;
            do {
                pos = line.find(delimit, startPos);
                auto endPos = (pos == std::string::npos) ? line.size() : pos;
                auto charCount = endPos - startPos;
                auto charPos = endPos - 1;
                if (charPos < line.size() && (line.at(charPos) == ' ' || line.at(charPos) == '\t')) {
                    --charCount;
                }
                auto column = line.substr(startPos, charCount);

                auto nbr_of_spaces = columnWidths[index++] - column.size() + 1;
                row << column;

                if (index < columnWidths.size()) {
                    row << std::string(nbr_of_spaces, ' ') << delimit;
                }

                startPos = endPos + 1;
            } while (pos != std::string::npos);

            // Output to file if output is open (separate file), else store in vector.
            if (output.is_open()) {
                output << std::move(row.str()) << std::endl;
            } else {
                rows.push_back(std::move(row.str()));
            }
        }

    }

    // 浜様様様様様様様様様様様様様様様様様様�
    // � Exit if using separate output file. �
    // 藩様様様様様様様様様様様様様様様様様様�
    if (argc == 4) {
        return EXIT_SUCCESS;
    }

    // 浜様様様様様様様様様�
    // � Close input file. �
    // 藩様様様様様様様様様�
    input.close();

    // 浜様様様様様様様様様様様様様様様様�
    // � Write adjusted columns to file. �
    // 藩様様様様様様様様様様様様様様様様�
    {
        std::string outputFileName = argc == 4 ? argv[2] : argv[1];
        std::ofstream output{outputFileName};

        for (auto&& r : rows) {
            output << r << std::endl;
        }

        std::cout << "Done! Result written to file \"" << outputFileName << "\"" << std::endl;
    }
}
