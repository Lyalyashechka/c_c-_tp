#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
	CPPCHECK="cppcheck"
else
	CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} project --enable=all --error-exitcode=1 -I project/include --suppress=missingIncludeSystem # --check-config

print_header "RUN cpplint.py"
python 3 cpplint/cpplint.py --extensions=c project/include/* project/src/* project/test/*

print_header "SUCCESS"
