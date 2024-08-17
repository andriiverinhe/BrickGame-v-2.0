# |======================================================================| #
# |============================== Compiler ==============================| #
# |======================================================================| #

CC := gcc
CXX := g++


# |======================================================================| #
# |============================== Flags =================================| #
# |======================================================================| #

CFLAGS := -Wall -Wextra -Werror -g --std=gnu11  

# -Wall: Enables most compiler warnings.
# -Wextra: Enables additional warnings not covered by -Wall.
# -Werror: Treats all warnings as errors, preventing compilation if there are any warnings.
# -g: Includes debugging information in the compiled code.
# --std=gnu11: Specifies the C standard to be used (GNU dialect of C11).

# |======================================================================| #

CXXFLAGS := -Wall -Wextra -g -std=c++17

# -Wall: Enables most compiler warnings for C++.
# -Wextra: Enables additional warnings for C++.
# -g: Includes debugging information in the compiled C++ code.
# -std=c++17: Specifies the C++ standard to be used (C++17).
# |======================================================================| #

GTESTFLAG := -lgtest -lgtest_main -pthread
# -lgtest: Links the Google Test library, used for unit testing in C++.
# -lgtest_main: Links the Google Test main library, providing a default main function for tests.
# -pthread: Links the pthread library for threading support, required by Google Test.
# |======================================================================| #

LDFLAGS := -lncurses -lrt -lstdc++
# -lncurses: Links the ncurses library for handling terminal display.
# -lrt: Links the real-time library for additional functionalities like clock_gettime.
# -lstdc++: Links the standard C++ library.
# |======================================================================| #

LIBS := -lcheck -lsubunit -lgcov -lm
# -lcheck: Links the Check library for C unit testing.
# -lsubunit: Links the Subunit library, used with Check for test reporting.
# -lgcov: Links the gcov library for code coverage analysis.
# -lm: Links the math library for mathematical functions.
# |======================================================================| #

CFLAGS_COVERAGE := -fprofile-arcs -ftest-coverage --coverage 
# -fprofile-arcs: Generates profiling information used for coverage analysis.
# -ftest-coverage: Generates additional information needed for coverage analysis.
# --coverage: Activates coverage analysis instrumentation.
# |======================================================================| #

FLAGC_REPORT := --html --html-details
# --html: Specifies that the coverage report should be generated in HTML format. 
# 	This makes the report viewable in a web browser, which is useful for visualizing coverage metrics.
# --html-details: Provides detailed HTML output for the coverage report. 
# 	This typically includes more granular information about code coverage, 
# 	such as which lines or branches were covered or missed.
# |======================================================================| #

EXCLUDE_COVEREGE := --exclude src/tests/CheckTest --exclude src/tests/GTest



# |======================================================================| #
# |============================== Directories ===========================| #
# |======================================================================| #

DIR_ROOT := src

DIR_BRICK_GAME := $(DIR_ROOT)/brick_game
DIR_BACKEND_TETRIS := $(DIR_BRICK_GAME)/tetris
DIR_BACKEND_SNAKE := $(DIR_BRICK_GAME)/snake
DIR_BACKEND_COMMON := $(DIR_BRICK_GAME)/common

DIR_GUI := $(DIR_ROOT)/gui
DIR_GUI_CLI := $(DIR_GUI)/cli
DIR_GUI_DESKTOP := $(DIR_GUI)/desktop

DIR_TESTS := $(DIR_ROOT)/tests
DIR_CHECK_TEST := $(DIR_TESTS)/CheckTest
DIR_GTEST := $(DIR_TESTS)/GTest

DIR_DIST := BrickGame
DIR_ALL_OBJ := obj
DIR_CT_OBJ := obj_ctest
DIR_GT_OBJ := obj_gtest
DIR_BUILD_CLI := build_cli
DIR_BUILD_DESKTOP := build_desktop


INSTALL_DIR_CLI := $(DIR_BUILD_CLI)/$(DIR_ALL_OBJ)

DIR_GCOV := Coverage
DIR_DOCUMANTATION := Docs
DIR_LATEX := latex

SRC_DIRS_CLI := $(DIR_GUI_CLI) $(DIR_BRICK_GAME)
SRC_DIRS_QT := $(DIR_GUI_DESKTOP) $(DIR_BRICK_GAME)
SRC_TEST_DIRS := $(DIR_CHECK_TEST) $(DIR_BACKEND_TETRIS) $(DIR_BACKEND_COMMON)
SRC_GTEST_DIRS := $(DIR_GTEST) $(DIR_BACKEND_SNAKE) $(DIR_BACKEND_COMMON)



# |======================================================================| #
# |============================== Source Files ==========================| #
# |======================================================================| #

SRC_INSTALL_C_CLI := $(shell find $(SRC_DIRS_CLI) -name '*.c')
SRC_INSTALL_CXX_CLI := $(shell find $(SRC_DIRS_CLI) -name '*.cpp')

SRC_TEST_C := $(shell find $(SRC_TEST_DIRS) -name '*.c')
SRC_TEST_CXX := $(shell find $(SRC_TEST_DIRS) -name '*.cpp')

SRC_GTEST_C := $(shell find $(SRC_GTEST_DIRS) -name '*.c')
SRC_GTEST_CXX := $(shell find $(SRC_GTEST_DIRS) -name '*.cpp')




# |======================================================================| #
# |============================== OBJECT Files ==========================| #
# |======================================================================| #

OBJ_INSTALL_C_CLI := $(patsubst %.c,$(INSTALL_DIR_CLI)/%.o,$(SRC_INSTALL_C_CLI))
OBJ_INSTALL_CXX_CLI := $(patsubst %.cpp,$(INSTALL_DIR_CLI)/%.o,$(SRC_INSTALL_CXX_CLI))

OBJ_CHECKTEST_C := $(patsubst %.c,$(DIR_CT_OBJ)/%.o,$(SRC_TEST_C))
OBJ_CHECKTEST_CXX := $(patsubst %.cpp,$(DIR_CT_OBJ)/%.o,$(SRC_TEST_CXX))

OBJ_GTEST_C := $(patsubst %.c,$(DIR_GT_OBJ)/%.o,$(SRC_GTEST_C))
OBJ_GTEST_CXX := $(patsubst %.cpp,$(DIR_GT_OBJ)/%.o,$(SRC_GTEST_CXX))




# |======================================================================| #
# |============================== Executable Files ======================| #
# |======================================================================| #

EXECUTABLE_FILE_GAME_UI_CLI := BrickGame_cli
EXECUTABLE_FILE_GAME_UI_DESKTOT := BrickGame_desktop

EXECUTABLE_FILE_CHECKTEST := debug_ct
EXECUTABLE_FILE_GTEST := debug_gt

FILE_COVEREGE := coverage_report.html
FILE_DOCUMENTATION := DocumentationDVI.pdf




# |======================================================================| #
# |============================== Utilities =============================| #
# |======================================================================| #

GCOVBIN := gcovr
OPEN_COMMAND := xdg-open




# |======================================================================| #
# |============================== Targets ===============================| #
# |======================================================================| #

.PHONY: all install uninstall dvi dist tests gcov_report 

# Default target
all: gcov_report install

install: install_ui_cli install_ui_qt

# Build the main game
install_ui_cli: $(INSTALL_DIR_CLI) $(OBJ_INSTALL_C_CLI) $(OBJ_INSTALL_CXX_CLI)
	cp $(DIR_BACKEND_TETRIS)/Model/Helpers/Model_templates.txt $(DIR_BUILD_CLI)/Model_templates.txt
	$(CXX) $(OBJ_INSTALL_C_CLI) $(OBJ_INSTALL_CXX_CLI) -o $(DIR_BUILD_CLI)/$(EXECUTABLE_FILE_GAME_UI_CLI) $(LDFLAGS)

# Run the game
run_cli: 
	@cd $(DIR_BUILD_CLI) && ./$(EXECUTABLE_FILE_GAME_UI_CLI)

# Build UI with Qt
install_ui_qt:
	@cd $(DIR_ROOT) && cmake -B ../$(DIR_BUILD_DESKTOP)
	@cd $(DIR_BUILD_DESKTOP) && make

# Run the game
run_desktop: 
	@cd $(DIR_BUILD_DESKTOP) && ./$(EXECUTABLE_FILE_GAME_UI_DESKTOT)

# Uninstall the build artifacts
uninstall:
	rm -rf $(DIR_BUILD_CLI)
	rm -rf $(DIR_BUILD_DESKTOP)

# Rebuild the project
rebuild: uninstall install

tests: ctest gtest

# Compile and run tests
ctest: $(DIR_CT_OBJ) $(OBJ_CHECKTEST_C) 
	cp $(DIR_BACKEND_TETRIS)/Model/Helpers/Model_templates.txt $(DIR_CT_OBJ)/Model_templates.txt
	$(CC) $(OBJ_CHECKTEST_C) -o $(DIR_CT_OBJ)/$(EXECUTABLE_FILE_CHECKTEST) $(LIBS)
	@make run_ctest

# Run the compiled tests
run_ctest: 
	@cd $(DIR_CT_OBJ) && ./$(EXECUTABLE_FILE_CHECKTEST)

# Compile and run Google Test
gtest: $(DIR_GT_OBJ) $(OBJ_GTEST_C) $(OBJ_GTEST_CXX)
	cp $(DIR_BACKEND_TETRIS)/Model/Helpers/Model_templates.txt $(DIR_GT_OBJ)/Model_templates.txt
	$(CXX) $(OBJ_GTEST_C) $(OBJ_GTEST_CXX) -o $(DIR_GT_OBJ)/$(EXECUTABLE_FILE_GTEST) $(GTESTFLAG) $(LIBS)
	@make run_gtest

# Run the compiled tests
run_gtest: 
	@cd $(DIR_GT_OBJ) && ./$(EXECUTABLE_FILE_GTEST)

# Generate coverage report
gcov_report: CFLAGS += $(CFLAGS_COVERAGE)
gcov_report: CXXFLAGS += $(CFLAGS_COVERAGE)
gcov_report: clean $(DIR_GCOV) tests
	$(GCOVBIN) -r . $(FLAGC_REPORT) $(EXCLUDE_COVEREGE) -o $(DIR_GCOV)/$(FILE_COVEREGE)

# Show coverage report
gcov_show:
	$(OPEN_COMMAND) $(DIR_GCOV)/$(FILE_COVEREGE)

# Clean build artifacts and generate coverage report
peer: clean gcov_report gcov_show

# Generate documentation with Doxygen
doxygen: 
	doxygen Doxyfile

# Generate DVI documentation
dvigen: doxygen
	@cd ./$(DIR_DOCUMANTATION)/$(DIR_LATEX)/ && make pdf > /dev/null 2>&1
	@mv ./$(DIR_DOCUMANTATION)/$(DIR_LATEX)/refman.pdf $(FILE_DOCUMENTATION)

# Open the documentation
dvi: 
	$(OPEN_COMMAND) $(FILE_DOCUMENTATION)

# Create a distribution tarball
dist:
	mkdir -p $(DIR_DIST)
	cp -r $(DIR_ROOT) misc Makefile Doxyfile README.md $(FILE_DOCUMENTATION) $(DIR_DIST)
	tar -czvf $(DIR_DIST).tar.gz $(DIR_DIST)/
	rm -rf $(DIR_DIST)

clean:
	rm -rf $(DIR_BUILD_CLI)
	rm -rf $(DIR_BUILD_DESKTOP)
	rm -rf $(DIR_CT_OBJ)
	rm -rf $(DIR_GT_OBJ)
	rm -rf $(DIR_ALL_OBJ)
	rm -rf $(DIR_GCOV)
	rm -rf $(DIR_DIST)
	rm -rf $(DIR_DOCUMANTATION)
	rm -rf *tar.gz



# |======================================================================| #
# |============================== Check Targets =========================| #
# |======================================================================| #

# Check coding style
check-style:
	@clang-format -style=Google -n $$(find . -name '*.c' -o -name '*.h')
	@clang-format -style=Google -n $$(find . -name '*.cpp' -o -name '*.hpp')

# Fix coding style
fix-style:
	@clang-format -style=Google -i $$(find . -name '*.c' -o -name '*.h')
	@clang-format -style=Google -i $$(find . -name '*.cpp' -o -name '*.hpp')

# Check memory leaks with Valgrind (tests)
val_ct: ctest
	@cd $(DIR_CT_OBJ) && valgrind --tool=memcheck --leak-check=full --log-file=mylogfile.txt ./$(EXECUTABLE_FILE_CHECKTEST)

# Check memory leaks with Valgrind (tests)
val_gt: gtest
	@cd $(DIR_GT_OBJ) && valgrind --tool=memcheck --leak-check=full --log-file=mylogfile.txt ./$(EXECUTABLE_FILE_GTEST)



# |======================================================================| #
# |============================== Build Rules ===========================| #
# |======================================================================| #

$(DIR_GCOV):
	mkdir -p $(DIR_GCOV)

$(INSTALL_DIR_CLI):
	mkdir -p $(INSTALL_DIR_CLI)

$(INSTALL_DIR_CLI)/%.o: %.c | $(INSTALL_DIR_CLI)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(INSTALL_DIR_CLI)/%.o: %.cpp | $(INSTALL_DIR_CLI)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

$(DIR_ALL_OBJ):
	cp $(DIR_BACKEND_TETRIS)/Model/Helpers/Model_templates.txt $(DIR_ALL_OBJ)/Model_templates.txt
	mkdir -p $(DIR_ALL_OBJ)

$(DIR_ALL_OBJ)/%.o: %.c | $(DIR_ALL_OBJ)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(DIR_ALL_OBJ)/%.o: %.cpp | $(DIR_ALL_OBJ)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(GTESTFLAG) $(LIBS)

$(DIR_CT_OBJ):
	mkdir -p $(DIR_CT_OBJ)

$(DIR_CT_OBJ)/%.o: %.c | $(DIR_CT_OBJ)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(DIR_CT_OBJ)/%.o: %.cpp | $(DIR_CT_OBJ)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(GTESTFLAG) $(LIBS)

$(DIR_GT_OBJ):
	mkdir -p $(DIR_GT_OBJ)

$(DIR_GT_OBJ)/%.o: %.c | $(DIR_GT_OBJ)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(DIR_GT_OBJ)/%.o: %.cpp | $(DIR_GT_OBJ)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(GTESTFLAG) $(LIBS)