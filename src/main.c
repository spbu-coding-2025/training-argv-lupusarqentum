#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <getopt.h>

int lower_bound_value;
int upper_bound_value;

int parse(int argc, char** argv) {
    bool detected_lower_bound = false;
    bool detected_upper_bound = false;

    struct option long_options[3] = {
        {
            .name = "lower_bound",
            .has_arg = required_argument,
            .flag = NULL,
            .val = 'L'
        },
        {
            .name = "upper_bound",
            .has_arg = required_argument,
            .flag = NULL,
            .val = 'U'
        },
        {
            .name = NULL,
            .has_arg = 0,
            .flag = NULL,
            .val = 0
        }
    };
    int option;
    while ((option = getopt_long(argc, argv, "", long_options, NULL)) != -1) {
        switch (option) {
            case 'U':
                upper_bound_value = atoi(optarg);
                detected_upper_bound = true;
                break;
            case 'L':
                lower_bound_value = atoi(optarg);
                detected_lower_bound = true;
                break;
            case '?':
            default:
                break;
        }
    }
    if (detected_upper_bound == false) {
        if (detected_lower_bound == false) {
            fprintf(stderr, "No flags found.\n");
            return 1;
        } else {
            fprintf(stderr, "Flag --upper_bound is missing.\n");
            return 1;
        }
    } else if (detected_lower_bound == false) {
        fprintf(stderr, "Flag --lower_bound is missing.\n");
        return 1;
    }
    if (lower_bound_value > upper_bound_value) {
        fprintf(stderr, "The lower bound is greater than the upper bound.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    int parser_return_value = parse(argc, argv);
    if (parser_return_value != 0) {
        return parser_return_value;
    }
    for (int i = lower_bound_value; i <= upper_bound_value; i++) {
        printf("%s%d", (i != lower_bound_value ? " " : ""), i);
    }
    printf("\n");
    return 0;
}
