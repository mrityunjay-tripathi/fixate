# Include the configuration file
include config.mk

TEST_SRC_DIR=test
TEST_BUILD_DIR=build/test
TEST_BINARY=bin/fixtest
BENCHMARK_SRC_DIR=benchmark
BENCHMARK_BUILD_DIR=build/benchmark
BENCHMARK_BINARY=bin/fixbenchmark
EXAMPLE_SRC_DIR=examples
EXAMPLE_BUILD_DIR=build/examples
EXAMPLE_BINARY=bin/fixexamples

all: test benchmark docs example

TEST_MAIN_SRC := ${TEST_SRC_DIR}/main.cpp
TEST_MAIN_OBJ := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_BUILD_DIR)/%.o,$(TEST_MAIN_SRC))
TEST_SRCS :=
TEST_OBJS := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_BUILD_DIR)/%.o,$(TEST_SRCS))

test: ${TEST_BINARY}
${TEST_BINARY}: ${TEST_OBJS} ${TEST_MAIN_OBJ}
	@mkdir -p $(shell dirname ${TEST_BINARY})
	@(echo "Building Tests $(TEST_BINARY)")
	@${CXX} -o ${TEST_BINARY} ${TEST_OBJS} ${TEST_MAIN_OBJ} ${LDFLAGS} ${LIBS}
${TEST_BUILD_DIR}/%.o : ${TEST_SRC_DIR}/%.cpp
	@mkdir -p ${TEST_BUILD_DIR}
	@(echo "Compiling $<")
	@${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

BENCHMARK_MAIN_SRC := ${BENCHMARK_SRC_DIR}/main.cpp
BENCHMARK_MAIN_OBJ := $(patsubst $(BENCHMARK_SRC_DIR)/%.cpp,$(BENCHMARK_BUILD_DIR)/%.o,$(BENCHMARK_MAIN_SRC))
BENCHMARK_SRCS :=
BENCHMARK_OBJS := $(patsubst $(BENCHMARK_SRC_DIR)/%.cpp,$(BENCHMARK_BUILD_DIR)/%.o,$(BENCHMARK_SRCS))

benchmark: ${BENCHMARK_BINARY}
${BENCHMARK_BINARY}: ${BENCHMARK_OBJS} ${BENCHMARK_MAIN_OBJ}
	@mkdir -p $(shell dirname ${BENCHMARK_BINARY})
	@(echo "Building Benchmarks $(BENCHMARK_BINARY)")
	@${CXX} -o ${BENCHMARK_BINARY} ${BENCHMARK_OBJS} ${BENCHMARK_MAIN_OBJ} ${LDFLAGS} -lbenchmark ${LIBS}
${BENCHMARK_BUILD_DIR}/%.o : ${BENCHMARK_SRC_DIR}/%.cpp
	@mkdir -p ${BENCHMARK_BUILD_DIR}
	@(echo "Compiling $<")
	@${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

EXAMPLE_MAIN_SRC := ${EXAMPLE_SRC_DIR}/main.cpp
EXAMPLE_MAIN_OBJ := $(patsubst $(EXAMPLE_SRC_DIR)/%.cpp,$(EXAMPLE_BUILD_DIR)/%.o,$(EXAMPLE_MAIN_SRC))
EXAMPLE_SRCS :=
EXAMPLE_OBJS := $(patsubst $(EXAMPLE_SRC_DIR)/%.cpp,$(EXAMPLE_BUILD_DIR)/%.o,$(EXAMPLE_SRCS))

example: ${EXAMPLE_BINARY}
${EXAMPLE_BINARY}: ${EXAMPLE_OBJS} ${EXAMPLE_MAIN_OBJ}
	@mkdir -p $(shell dirname ${EXAMPLE_BINARY})
	@(echo "Building Examples $(EXAMPLE_BINARY)")
	@${CXX} -o ${EXAMPLE_BINARY} ${EXAMPLE_OBJS} ${EXAMPLE_MAIN_OBJ} ${LDFLAGS} ${LIBS}
${EXAMPLE_BUILD_DIR}/%.o : ${EXAMPLE_SRC_DIR}/%.cpp
	@mkdir -p ${EXAMPLE_BUILD_DIR}
	@(echo "Compiling $<")
	@${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

docs:
	@if [ -e ${PROJECT_BASE_DIR}/Doxyfile ] && [ ${BUILD_DOCS} -eq 1 ]; then \
		echo "Building Doxygen docs"; \
		doxygen Doxyfile > /dev/null 2>&1; \
	fi

clean:
	@rm -rf ${TEST_BINARY} ${TEST_OBJS} ${TEST_MAIN_OBJ} \
		${BENCHMARK_BINARY} ${BENCHMARK_OBJS} ${BENCHMARK_MAIN_OBJ} \
		${EXAMPLE_BINARY} ${EXAMPLE_OBJS} ${EXAMPLE_MAIN_OBJ} \
		${PROJECT_BASE_DIR}/docs

install:
	@rm -rf ${INSTALL_DIR}/include/fixate
	@mkdir -p ${INSTALL_DIR}/include/fixate
	cp -rf ${PROJECT_BASE_DIR}/include/fixate ${INSTALL_DIR}/include/;
	cp -rf ${PROJECT_BASE_DIR}/include/ringbuffer ${INSTALL_DIR}/include/;
	cp -rf ${PROJECT_BASE_DIR}/lib/* ${INSTALL_DIR}/lib/;

