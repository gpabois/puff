#include <puff/entry.h>
#include <puff/printk.h>
#include <puff/exception/sys.h>
#include <puff/yarn/sys.h>

void __init_kernel() {
    printk("Initialise PUFF systems");
    
    // Initialise exception system
    __init_exception_sys();

    // Initialise yarn system
    __init_yarn_sys();

    // Initialise generator system
}

void __step_kernel() {
    
}

