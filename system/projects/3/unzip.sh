#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Error: missing command line argument"
    exit 1
fi

unzip cis361p4.zip -d $1
cd $1;
currentStudent=""
for file in *; do
    IFS=' ' read -r -a spaceSeparated <<< "$file"
    IFS='_' read -r -a _Separated <<< "${spaceSeparated[1]}"
    if [ "${_Separated[1]}" != "${currentStudent}" ]
    then
        if [ "${currentStudent}" != "" ]
        then
            make -C "${currentStudent}"
        fi

        currentStudent="${_Separated[1]}"
        mkdir "${currentStudent}"
    fi;
    if [ "${_Separated[4]}" != "" ]
    then
        cp "${spaceSeparated[0]}"\ "${spaceSeparated[1]}" "${currentStudent}/${_Separated[4]}"
    fi;

done
