filename="$1"
next() {
    echo $1;
}
rest() { shift; echo $*; }
while read -r line
do
    totalWords=$(c() { echo $#; }; c $line)
    for i in `seq -w 1 $totalWords`; do
        next $line || nextWord
        line=$(rest $line)
    done
    echo $line wiffle
done < "$filename"
