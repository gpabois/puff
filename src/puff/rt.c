#include <puff/rt.h>

#include <puff/exception/sys.h>
#include <puff/yarn/sys.h>

void __init_puff_rt() {
    // Initialise exception system
    __init_exception_sys();

    // Initialise yarn system
    __init_yarn_sys();

    // Initialise generator system
}