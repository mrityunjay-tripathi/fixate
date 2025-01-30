#!/bin/bash
set -e

PROJECT_VERSION=1.0.0
PROJECT_BASE_DIR=${PWD}
PROJECT_BUILD_DIR=${PROJECT_BASE_DIR}/build
PROJECT_INCLUDE_DIR=${PROJECT_BASE_DIR}/include
PROJECT_SRC_DIR=${PROJECT_BASE_DIR}/src

INSTALL_DIR=/usr/local
CXX=/usr/bin/g++
VERBOSE=0
DEBUG=0
BUILD_DOCS=0

HELP_MESSAGE="Configuration Paramters:
--cxx: Provide C++ compiler binary path.
--debug: Build test and benchmark suite in debug mode. [0/1]
--verbose: Enable compiler verbose mode. [0/1]
--install_dir: Provide installation directory, default is '/usr/local'
--build_docs: Build Doxygen documentation
--help: Print this help message."

for arg in "$@"; do
    case $arg in
        --help*) echo "${HELP_MESSAGE}"; exit 0 ;;
        --cxx=*) CXX="${arg#*=}" ;;
        --debug=*) DEBUG="${arg#*=}"; ;;
        --verbose=*) VERBOSE="${arg#*=}"; ;;
        --install_dir=*) INSTALL_DIR="${arg#*=}"; ;;
        --build_docs=*) BUILD_DOCS="${arg#*=}"; ;;
        *) echo "Unknown option: $arg"; exit 1 ;;
    esac
done

CXXFLAGS="-std=c++2a"
if [[ "${VERBOSE}" == "1" ]]; then
    CXXFLAGS="${CXXFLAGS} -v"
fi
if [[ "${DEBUG}" == "1" ]]; then
    CXXFLAGS="${CXXFLAGS} -g -O0"
else
    CXXFLAGS="${CXXFLAGS} -O3"
fi
CXXFLAGS="${CXXFLAGS} -Wall -Werror=format -Wpedantic -Wno-switch -Wno-unused-function -Wno-deprecated-declarations"

check_directories() {
    local dirs="$1"
    local all_found=true
    for dir in $dirs; do
        if [ ! -d "${dir:2}" ]; then
            echo "'$dir' not found."
            all_found=false
        fi
    done
    if ! $all_found; then
        return 1
    else
        return 0
    fi
}

check_libraries_exist() {
    local library_path="$1"
    local libraries="$2"

    local all_paths=()
    for libpaths in $library_path; do
        all_paths+=("${libpaths:2}")
    done

    IFS=':' read -r -a ld_paths <<< "$LD_LIBRARY_PATH"
    all_paths+=("${ld_paths[@]}")

    local all_found=true
    for lib in $libraries; do
        local lib_name="${lib:2}"
        local found=false

        # Check user-defined and standard paths first
        for dir in "${all_paths[@]}"; do
            if [[ -f "$dir/lib${lib_name}.so" || -f "$dir/lib${lib_name}.a" ]]; then
                echo "'$lib_name' found in $dir."
                found=true
                break
            fi
        done

        # If not found, check using ldconfig for system-installed libraries
        if ! $found; then
            if ldconfig -p | grep -q "lib${lib_name}"; then
                echo "'$lib_name' found via 'ldconfig'."
                found=true
            fi
        fi

        if ! $found; then
            echo "'$lib_name' not found."
        fi
        all_found=$all_found && $found
    done

    if ! $all_found; then
        return 1
    else
        return 0
    fi
}

INCLUDE_PATH="-I${PROJECT_BASE_DIR}/include -I/usr/local/include"
LIBRARY_PATH="-L/usr/local/lib -L./lib"
LIBRARIES="-lvrb -lssl -lcrypto"

echo "Checking Includes and Libraries:"
check_directories "$INCLUDE_PATH"
check_directories "$LIBRARY_PATH"
check_libraries_exist "$LIBRARY_PATH" "$LIBRARIES"
echo

cat > config.mk <<EOL
# Generated configuration file

PROJECT_VERSION := ${PROJECT_VERSION}
PROJECT_BASE_DIR := ${PROJECT_BASE_DIR}
PROJECT_BUILD_DIR := ${PROJECT_BUILD_DIR}
PROJECT_INCLUDE_DIR := ${PROJECT_INCLUDE_DIR}
PROJECT_SRC_DIR := ${PROJECT_SRC_DIR}
INSTALL_DIR := ${INSTALL_DIR}
CXX := ${CXX}
VERBOSE := ${VERBOSE}
DEBUG := ${DEBUG}
BUILD_DOCS := ${BUILD_DOCS}
CXXFLAGS := ${CXXFLAGS}
INCS := ${INCLUDE_PATH}
LDFLAGS := ${LIBRARY_PATH}
LIBS := ${LIBRARIES}
EOL

echo "Configuration Parameters:"
echo "cxx=${CXX}"
echo "debug=${DEBUG}"
echo "verbose=${VERBOSE}"
echo "install_dir=${INSTALL_DIR}"
echo "build_docs=${BUILD_DOCS}"
echo
echo "Build Parameters:"
echo "CXXFLAGS=${CXXFLAGS}"
echo "INCS=${INCLUDE_PATH}"
echo "LDFLAGS=${LIBRARY_PATH}"
echo "LIBS=${LIBRARIES}"
echo
echo "Build configuration written to 'config.mk'"
