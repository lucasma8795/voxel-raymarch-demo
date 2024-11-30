.PHONY: build

# name of output executable
EXEC_FILE = voxel-raymarch-demo

# compiler to use
CXX = /opt/homebrew/bin/g++-14

# compiler flags
CXXFLAGS = -O3 -Wall -Wextra -Wpedantic # -Wfatal-errors
CXXFLAGS += -march=native -std=c++23 # -fsanitize=undefined
CXXFLAGS += -flto=auto # -pthread -fopenmp
CXXFLAGS += -fno-exceptions # -DNDEBUG
# CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter

CXXFLAGS += -DGL_SILENCE_DEPRECATION

# linker flags
LDFLAGS = -flto=auto # -pthread

# precompiled headers
PCH_SRC = src/stdafx.h
PCH_OUT = src/stdafx.h.gch

# list of cpp files
CPPFILES = $(shell find ./src -name "*.cpp")

# list of object files
OBJECTS = $(CPPFILES:.cpp=.o)

# libraries
LIBS = -L/opt/homebrew/lib/ -lGLEW -lglfw -framework OpenGL

# include path
INCLUDE = -I$(CURDIR)/src -isystem /opt/homebrew/include/

# rebuild objects which have their dependencies changed
-include $(OBJECTS:.o=.d)
-include $(PCH_SRC:.h=.h.d)

# compile PCH
$(PCH_OUT): $(PCH_SRC) Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDE) -MMD -MP -o $@ -c $<

# compile .cpp
%.o: %.cpp Makefile $(PCH_OUT)
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $(INCLUDE) -MMD -MP -o $@ -c $<

# invoke linker to build final executable
$(EXEC_FILE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBS) $(LDFLAGS) $^ -o $@

# define 'build' target
build: $(EXEC_FILE)

clean:
	rm -rf $(shell find ./src ./vendor -name "*.d")
	rm -rf $(shell find ./src ./vendor -name "*.o")
	rm -rf $(shell find ./src ./vendor -name "*.gch")
	rm -f $(EXEC_FILE)