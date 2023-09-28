#!/usr/bin/env bash
# This script is used to run the tests in CI.

lab_dir=$(pwd)
echo "Lab directory: $lab_dir"
cd ..
pwd
if [ -e UCU_autotests ]; then
		echo "Removing old autotests"
		rm -rf UCU_autotests
fi
git clone https://github.com/DariaMinieieva/UCU_autotests
cd UCU_autotests/c_strings_auto_testing
cp -r $lab_dir ./c_str_lib
echo "Copied lab to autotests directory"
echo "Starting compile"
./compile.sh
echo "Starting tests"
./bin/gtester
