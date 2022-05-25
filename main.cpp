/*
#  File        : main.cpp
#  Description : Main procedure of A4 Paper Sheet Detection
#                and Cropping with Hough Transform and Warping
#  Copyright   : HYPJUDY 2017/4/6, Raphaël Droz 2022
#  Details     : https://hypjudy.github.io/2017/03/28/cvpr-A4-paper-sheet-detection-and-cropping/
#  Code        : https://github.com/HYPJUDY/A4-paper-sheet-detection-and-cropping
*/

#include <iostream>
#include <getopt.h>
#include <limits.h>
#include "Warping.h"

void help(char *prog) {
    std::cout << prog << " [--output <filename>] [--marked-output <filename>] [--preview] <file>" << std::endl;
    std::cout << prog << " --help" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "--marked-output Output file of the image whose identified corners are marked" << std::endl;
    std::cout << "--preview       Display intermediary files as they are generated" << std::endl;
}

int main(int argc, char **argv) {
    int c, option_index, preview_flag = 0, help_flag = 0;
    char *arg_long = nullptr, *marked_output = nullptr, *output = nullptr;

    static struct option long_options[] =
	{
	 {"preview",       no_argument,       &preview_flag, 1},
	 {"help",          no_argument,       &help_flag, 1},
	 {"marked-output", required_argument, 0, 'm'},
	 {"output",        required_argument, 0, 'o'},
	 {0, 0, 0, 0}
	};

    while ((c = getopt_long(argc, argv, "phm:o:", long_options, &option_index)) != -1) {
	switch (c) {
	case 'h':
	    help_flag = 1;
	    break;
	case 'p':
	    preview_flag = 1;
	    break;
	case 'm':
	    marked_output = optarg;
	    break;
	case 'o':
	    output = optarg;
	    break;
	default:
	    std::cerr << "Unknown parse returns: " << c << std::endl;
	    return 1;
	}
    }

    if (help_flag) {
	help(argv[0]);
	return 0;
    }

    if (optind >= argc) {
	std::cerr << "No input file specified: " << c << std::endl;
	return 1;
    }

    Hough hough(argv[optind], preview_flag);
    Warping Warping(hough);

    if (marked_output) {
	hough.getMarkedImg().save(marked_output);
    }
    if (output) {
	Warping.getCroppedImg().save(output);
    } else {
	std::cerr << "No output file specified: " << std::endl;
    }
}

/* Exceptions
 * ERROR: Please set parameter Q larger in file \
 *        'hough_transform.h' to filter out four edges!
 * ERROR: Bug in function void Hough::getHoughEdges()!\
 *        Please check the ifelse statement to filter out four hough_edges.
 * ERROR: Can not detect four ordered_corners in function \
 *        void Hough::orderCorners(). Please try to adjust parameters.
 */
