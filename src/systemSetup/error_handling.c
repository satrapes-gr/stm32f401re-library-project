//#include <stdint.h>
#include "error_handling.h"

/* TODO: Add an implementation for a doubly linked list. Make it generic if possible.
 *       every time that we encounter a recoverable error we will add the error in the form of a
 *       tuple (module, error number, line, file) when we check our error output we will see if
 *       the linked list is empty. If it is not we can view the data which is going to go to a
 *       special place and move to a while(1) . Each module is going to have its own error number
 *       enum and the modules are going to be defined in main.c I imagine in a global variable.
 */
