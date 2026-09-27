# Day-to-day front-end for the CMake build.
#
#   make
#   make test
#   make test FILTER=Dijkstra
#   make app
#   make dev
#   make scaffold NAME=linked_list
#   make scaffold FOLDER=shortest_path NAME=bellman_ford

BUILD_DIR ?= cmake-build-debug
BUILD_TYPE ?= Debug
GENERATOR ?= Ninja
JOBS ?=

CMAKE ?= cmake
SHELL := /bin/bash

.DEFAULT_GOAL := build

.PHONY: help build configure test tests app dev release clean scaffold

help:
	@printf '%s\n' \
		'Targets:' \
		'  make                              build the Debug tree (default)' \
		'  make test                         build and run every unit test' \
		'  make test FILTER=Dijkstra         tests whose names start with Dijkstra' \
		'  make test FILTER=Dijkstra.SimpleGraph' \
		'                                    one test; a dot or * is passed through' \
		'  make app                          build and run the production CLI' \
		'  make dev                          build and run the scratch binary' \
		'  make release                      Release build in cmake-build-release' \
		'  make clean                        delete the Debug and Release trees' \
		'  make scaffold NAME=foo' \
		'                                    header/foo.hpp, src/foo.cpp, unit_tests/test_foo.cpp' \
		'  make scaffold FOLDER=shortest_path NAME=bellman_ford' \
		'                                    the same trio inside an existing category' \
		'' \
		'After scaffold, add the new .cpp to add_library() in CMakeLists.txt.' \
		'New tests are picked up on the next build. Category folders must already exist.' \
		'' \
		'Variables:' \
		'  BUILD_DIR    $(BUILD_DIR)' \
		'  BUILD_TYPE   $(BUILD_TYPE)' \
		'  GENERATOR    $(GENERATOR)' \
		'  JOBS         parallel jobs (default: the native tool decides)' \
		'  FILTER       gtest name or prefix' \
		'  NAME         scaffold file stem' \
		'  FOLDER       existing category (shortest_path, traversal, ...)'

configure:
	$(CMAKE) -S . -B "$(BUILD_DIR)" -G "$(GENERATOR)" -DCMAKE_BUILD_TYPE="$(BUILD_TYPE)"

build: configure
	$(CMAKE) --build "$(BUILD_DIR)" --parallel$(if $(JOBS), $(JOBS),)

test: build
	@filter='$(FILTER)'; \
	args=(); \
	if [[ -n "$$filter" ]]; then \
		if [[ "$$filter" == *.* || "$$filter" == *'*'* ]]; then \
			args=(--gtest_filter="$$filter"); \
		else \
			args=(--gtest_filter="$$filter.*"); \
		fi; \
	fi; \
	"$(BUILD_DIR)/test_environment" "$${args[@]}"

tests: test

app: build
	"$(BUILD_DIR)/app"

dev: build
	"$(BUILD_DIR)/dev_main"

release:
	$(MAKE) build BUILD_DIR=cmake-build-release BUILD_TYPE=Release

clean:
	rm -rf "$(BUILD_DIR)" cmake-build-debug cmake-build-release

scaffold:
	@if [[ -z "$(NAME)" ]]; then \
		echo "Usage: make scaffold NAME=<name> [FOLDER=<category>]"; \
		echo "       make scaffold NAME=linked_list"; \
		echo "       make scaffold FOLDER=shortest_path NAME=bellman_ford"; \
		exit 1; \
	fi
	@bash generate_scaffold.sh $(if $(FOLDER),"$(FOLDER)") "$(NAME)"
