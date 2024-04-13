# global variables
.DEFAULT_GOAL := all_codexpander_release
SHELL = /bin/bash
CC = g++ -std=c++20


# global targets
debug_build:
	$(eval CC=g++ -std=c++20 -g)

all: all_core_release all_codexpander_release


# codexpander core properties
core_project = codexpander_core
core_source_dir = $(core_project)/src
core_include_dir = $(core_project)/include
core_object_dir = $(core_project)/objects
core_bin_dir = $(core_project)/bin
core_sources_files = $(wildcard $(core_source_dir)/*.cpp)
core_object_files = $(patsubst $(core_source_dir)/%.cpp, $(core_object_dir)/%.o, $(core_sources_files))
core_library_files = codepander_core


# codexpander core targets
all_core: clean_core debug_build build_core

all_core_release: clean_core build_core

clean_core:
	rm -rf $(core_object_dir)
	rm -rf $(core_bin_dir)
	mkdir -p $(core_object_dir)
	mkdir -p $(core_bin_dir)

build_core: $(core_object_files)
	ar rcs $(core_bin_dir)/libcodepander_core.a $(core_object_files)

$(core_object_files): $(core_object_dir)/%.o: $(core_source_dir)/%.cpp
	$(CC) -I$(core_include_dir) -c $< -o $@


# codexpander test properties
test_project = codexpander_tests
test_source_dir = $(test_project)/src
test_include_dir = $(test_project)/include
test_object_dir = $(test_project)/objects
test_bin_dir = $(test_project)/bin
test_res_dir = $(test_project)/res
test_bin_res_dir = $(test_bin_dir)/res
test_sources_files = $(wildcard $(test_source_dir)/*.cpp)
test_object_files = $(patsubst $(test_source_dir)/%.cpp, $(test_object_dir)/%.o, $(test_sources_files))


# codexpander test targets
run_tests: all_tests
	$(test_bin_dir)/codexpander_tests

all_tests: all_core clean_tests debug_build build_tests copy_resources_tests

run_tests_release: all_tests_release
	$(test_bin_dir)/codexpander_tests

all_tests_release: all_core_release clean_tests build_tests copy_resources_tests

clean_tests:
	rm -rf $(test_object_dir)
	rm -rf $(test_bin_dir)
	mkdir -p $(test_object_dir)
	mkdir -p $(test_bin_dir)

build_tests: $(test_object_files)
	$(CC) $(test_object_files) -I$(test_include_dir) -I$(core_include_dir) -L$(core_bin_dir) -l$(core_library_files) -o $(test_bin_dir)/codexpander_tests

$(test_object_files): $(test_object_dir)/%.o: $(test_source_dir)/%.cpp
	$(CC) -I$(test_include_dir) -I$(core_include_dir) -c $< -o $@

copy_resources_tests:
	mkdir -p $(test_bin_res_dir)
	cp -r $(test_res_dir) $(test_bin_dir)


# codexpander properties
codexpander_project = codexpander
codexpander_source_dir = $(codexpander_project)/src
codexpander_object_dir = $(codexpander_project)/objects
codexpander_bin_dir = $(codexpander_project)/bin
codexpander_sources_files = $(wildcard $(codexpander_source_dir)/*.cpp)
codexpander_object_files = $(patsubst $(codexpander_source_dir)/%.cpp, $(codexpander_object_dir)/%.o, $(codexpander_sources_files))


# codexpander targets
run_codexpander: all_codexpander
	$(codexpander_bin_dir)/codexpander

all_codexpander: all_core clean_codexpander debug_build build_codexpander

run_codexpander_release: all_codexpander_release
	$(codexpander_bin_dir)/codexpander

all_codexpander_release: all_core_release clean_codexpander build_codexpander

clean_codexpander:
	rm -rf $(codexpander_object_dir)
	rm -rf $(codexpander_bin_dir)
	mkdir -p $(codexpander_object_dir)
	mkdir -p $(codexpander_bin_dir)

build_codexpander: $(codexpander_object_files)
	$(CC) $(codexpander_object_files) -I$(core_include_dir) -L$(core_bin_dir) -l$(core_library_files) -o $(codexpander_bin_dir)/codexpander

$(codexpander_object_files): $(codexpander_object_dir)/%.o: $(codexpander_source_dir)/%.cpp
	$(CC) -I$(core_include_dir) -c $< -o $@