#include "gui.h"

// Global data structures
CriminalList criminals;
CaseQueue cases;
Graph criminal_network;

int main(int argc, char *argv[]) {
    start_gui(argc, argv);
    return 0;
}

