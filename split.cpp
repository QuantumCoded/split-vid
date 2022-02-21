#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("usage: split-vid <video> <times>\n");
        return 1;
    }

    int clip = 1;
    char* curr;
    char* prev = (char*)"0";
    char* video = argv[1];
    char* ext = video + strlen(video) - 3;

    argv = argv + 2; // start parsing times at 2nd index

    string command = "mkdir ";
    command += video;
    command += "_clips";

    system(command.c_str());

    while (*argv) {
        curr = *argv;

        float curr_f, prev_f;

        stringstream curr_s{string(curr)};
        stringstream prev_s{string(prev)};
        stringstream len;

        if (!(curr_s >> curr_f)) {
            printf("parsing error\n");
            return 1;
        }

        if (!(prev_s >> prev_f)) {
            printf("parsing error\n");
            return 1;
        }

        len << (curr_f - prev_f);

        command = "ffmpeg -y -loglevel error -i ";
        command += video;
        command += " -ss ";
        command += prev;
        command += " -t ";
        command += len.str();
        command += " ";
        command += video;
        command += "_clips/";
        command += prev;
        command += "-";
        command += curr;
        command += ".";
        command += ext;

        printf("splitting video %s clip: %d start: %f end: %f\n", video, clip++, prev_f, curr_f);

        system(command.c_str());

        prev = curr;

        argv += 1;
    }
}