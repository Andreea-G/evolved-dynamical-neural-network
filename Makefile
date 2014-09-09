
CXX := g++
CXXFLAGS := -pthread -std=c++11 -O2 -pedantic -Wall -Wextra
INCPATH := -I.
# the "-Wl,--no-as-needed" is a workaround for a current bug in g++
# (see: http://stackoverflow.com/questions/19463602/compiling-multithread-code-with-g)
LFLAGS := -pthread -Wl,--no-as-needed
CXX_EXT := cpp

SOURCE_DIR := src
BUILD_DIR := .build
EXECUTABLE := ednn

##############################################################

SOURCES := $(shell find $(SOURCE_DIR) -name "*.$(CXX_EXT)")
OBJECTS := $(SOURCES:%.$(CXX_EXT)=$(BUILD_DIR)/%.o)


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)


$(BUILD_DIR)/%.o: %.$(CXX_EXT)
	@mkdir -p $(dir $@); fi	
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $^ -o $@


clean:
	@rm -rf $(BUILD_DIR) $(EXECUTABLE)
	@echo "Finished cleaning"

