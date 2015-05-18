# —————————————————————————————————————————————————————————
# Make file for C++ building
# —————————————————————————————————————————————————————————

# —————————————————————————————————————————————————————————
# Compilers
# —————————————————————————————————————————————————————————

#CC = gcc-4.9
CC  = mpic++   # Message passing interface compiler

# —————————————————————————————————————————————————————————
# Library paths
# —————————————————————————————————————————————————————————

# Boost

IBOOST_PATH = -I/usr/local/bin/boost_1_57_0
LBOOST_PATH = -L/usr/local/bin/boost_1_57_0/stage/lib

# Scythestat

ISCYTHE_PATH = -I/usr/local/include/

# —————————————————————————————————————————————————————————
# Compiling and linking flags
# —————————————————————————————————————————————————————————

CFLAGS  = -c -Wall -std=c++11 ${IBOOST_PATH} ${ISCYTHE_PATH} -DSCYTHE_DEBUG=1 
LDFLAGS = ${LBOOST_PATH}

# —————————————————————————————————————————————————————————
# Sources and executables
# —————————————————————————————————————————————————————————

SOURCES    = MpiHelloWorld.cpp  
OBJECTS    = $(SOURCES:.cpp=.o)
EXECUTABLE = MpiHelloWorld

# —————————————————————————————————————————————————————————
# All
# —————————————————————————————————————————————————————————

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# —————————————————————————————————————————————————————————
# Clean
# —————————————————————————————————————————————————————————

clean:
	rm -f *.o