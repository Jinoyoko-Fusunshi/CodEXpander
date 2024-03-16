# MakeFiles variables
SHELL = /bin/bash
CC = g++


# core project properties
core_project = codeexpander_core
core_source_dir = $(core_project)/src
core_include_dir = $(core_project)/include
core_object_dir = $(core_project)/objects
core_bin_dir = $(core_project)/bin
core_sources_files = $(wildcard $(core_source_dir)/*.cpp)
core_object_files = $(patsubst $(core_source_dir)/%.cpp, $(core_object_dir)/%.o, $(core_sources_files))
core_library_files = test


# core targets
all_core: clean_core build_core

all_core_release: clean_core build_core_release

clean_core:
	rm -rf $(core_object_dir)
	rm -rf $(core_bin_dir)
	mkdir -p $(core_object_dir)
	mkdir -p $(core_bin_dir)

build_core: debug_build $(core_object_files)
	ar rcs $(core_bin_dir)/libtest.a $(core_object_files)

build_core_release: $(core_object_files)
	ar rcs $(core_bin_dir)/libtest.a $(core_object_files)

$(core_object_files): $(core_object_dir)/%.o: $(core_source_dir)/%.cpp
	$(CC) -I$(core_include_dir) -c $< -o $@


# test project properties
test_project = codeexpander_tests
test_source_dir = $(test_project)/src
test_include_dir = $(test_project)/include
test_object_dir = $(test_project)/objects
test_bin_dir = $(test_project)/bin
test_res_dir = $(test_project)/res
test_bin_res_dir = $(test_bin_dir)/res
test_sources_files = $(wildcard $(test_source_dir)/*.cpp)
test_object_files = $(patsubst $(test_source_dir)/%.cpp, $(test_object_dir)/%.o, $(test_sources_files))
test_object_files_release = $(patsubst $(test_source_dir)/%.cpp, $(test_object_dir)/%.o, $(test_sources_files))


# test targets
run_tests: all_tests
	$(test_bin_dir)/codeexpander_tests

all_tests: all_core clean_tests build_tests copy_resources_tests

run_tests_release: all_tests_release
	$(test_bin_dir)/codeexpander_tests

all_tests_release: all_core_release clean_tests build_tests_release copy_resources_tests

clean_tests:
	rm -rf $(test_object_dir)
	rm -rf $(test_bin_dir)
	rm -rf $(test_bin_res_dir)
	mkdir -p $(test_object_dir)
	mkdir -p $(test_bin_dir)

build_tests: debug_build $(test_object_files)
	$(CC) $(test_object_files) -I$(test_include_dir) -I$(core_include_dir) -L$(core_bin_dir) -l$(core_library_files) -o $(test_bin_dir)/codeexpander_tests

build_tests_release: $(test_object_files)
	$(CC) $(test_object_files) -I$(test_include_dir) -I$(core_include_dir) -L$(core_bin_dir) -l$(core_library_files) -o $(test_bin_dir)/codeexpander_tests

$(test_object_files): $(test_object_dir)/%.o: $(test_source_dir)/%.cpp
	$(CC) -I$(test_include_dir) -I$(core_include_dir) -L$(core_bin_dir) -l$(core_library_files) -c $< -o $@

copy_resources_tests:
	mkdir -p $(test_bin_res_dir)
	cp -r $(test_res_dir) $(test_bin_res_dir)

debug_build:
	$(eval CC=g++ -g)

all: all_core_release all_tests_release