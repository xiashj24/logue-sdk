##############################################################################
# Configuration for Makefile
#

PROJECT := supersaw
PROJECT_TYPE := osc

##############################################################################
# Sources
#

# C sources 
UCSRC = header.c

# C++ sources 
UCXXSRC = unit.cc ../../ext/DaisySP/Source/Filters/svf.cc ../../ext/DaisySP/Source/Synthesis/oscillator.cc

# List ASM source files here
UASMSRC = 

UASMXSRC = 

##############################################################################
# Include Paths
#

UINCDIR  = ../../ext/DaisySP/Source/ ../../ext/DaisySP/Source/Utility

##############################################################################
# Library Paths
#

ULIBDIR =

##############################################################################
# Libraries
#

ULIBS  = -lm

##############################################################################
# Macros
#

UDEFS = 

