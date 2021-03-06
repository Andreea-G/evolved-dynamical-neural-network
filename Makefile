
CXX := g++
CXXFLAGS := -pthread -std=c++0x -O2 -pedantic -Wall -Wextra
INCPATH := -I.
LFLAGS := -pthread
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
	@mkdir -p $(dir $@);
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $^ -o $@


clean:
	@rm -rf $(BUILD_DIR) $(EXECUTABLE)
	@echo "Finished cleaning"

