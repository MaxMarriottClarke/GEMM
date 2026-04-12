CXX ?= g++
CXXFLAGS ?= -O2 -std=c++17 -Wall -Wextra -Iinclude
AVXFLAGS := -mavx2 -mfma
BIN_DIR := bin

all: naive naive_avx

naive: $(BIN_DIR)/naive

naive_avx: $(BIN_DIR)/naive_avx

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/naive: src/Naive.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/naive_avx: src/Naive_avx.cpp include/Naive_avx.h | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(AVXFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean naive naive_avx
