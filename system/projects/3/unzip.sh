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
            ./"${currentStudent}"/cipher 1 3 ../data.txt ../encrypt.txt
            ./"${currentStudent}"/cipher 2 3 ../encrypt.txt ../decrypt.txt
            isCorrect=true
            cmp --silent ../data.txt ../decrypt.txt || isCorrect=false
            if [ $isCorrect == true ]; then
              echo "${currentStudent}: files match"
            else
              echo "${currentStudent}: files do not match"
            fi
        fi

        currentStudent="${_Separated[1]}"
        mkdir "${currentStudent}"
    fi;
    if [ "${_Separated[4]}" != "" ]
    then
        cp "${spaceSeparated[0]}"\ "${spaceSeparated[1]}" "${currentStudent}/${_Separated[4]}"
    fi;

done

make -C "${currentStudent}"
./"${currentStudent}"/cipher 1 3 ../data.txt ../encrypt.txt
./"${currentStudent}"/cipher 2 3 ../encrypt.txt ../decrypt.txt
isCorrect=true
cmp --silent ../data.txt ../decrypt.txt || isCorrect=false
if [ $isCorrect == true ]; then
  echo "${currentStudent}: files match"
else
  echo "${currentStudent}: files do not match"
fi
