#!/bin/bash

# Timeout in seconds after which the sorting process will be killed if still running:
TIMEOUT=60 # 1800
LOGFILE="results.log"
CSVFILE="results.csv"

declare -A RESULTS

ALGORITHMS=(
    std_sort
    qsort
    quick_sort
    quick_sort+insertion_sort
    merge_sort
    heap_sort
    selection_sort \
    insertion_sort \
)

N_ELEMENTS=(
    10
    100
    500
    1000
    5000
    1E4
    5E4
    1E5
    5E5
    1E6
    5E6
    1E7
    5E7
    1E8
)


date '+%F %T' > $LOGFILE
echo >> $LOGFILE

# Print table header
printf "\t" > $CSVFILE
for s in "${ALGORITHMS[@]}"
do
    printf "$s\t" >> $CSVFILE
done
printf "\n" >> $CSVFILE

# Run tests for every number of elements:
for n in "${N_ELEMENTS[@]}"
do
    echo "=== testing $n elements ===" >> $LOGFILE
    ./generate $n
    for s in "${ALGORITHMS[@]}"
    do
        echo "$s:" >> $LOGFILE
        result=$(timeout $TIMEOUT ./$s 2>&1 || exit 1)
        echo "$result" >> $LOGFILE
        if [ $? -eq 139 ]; then
            echo "Fatal error" >> $LOGFILE
            exit 1
        fi
        diff -q $s.sorted std_sort.sorted
        time_spent=$(echo "$result" | grep 'Time spent' | cut -d" " -f3)
        RESULTS[$s,$n]=$(echo "$result" | grep 'Time spent' | cut -d" " -f3)

        echo >> $LOGFILE
    done

    # Print table row:
    printf "$n\t" >> $CSVFILE
    for s in "${ALGORITHMS[@]}"
    do
        printf "${RESULTS[$s,$n]}\t" >> $CSVFILE
    done
    printf "\n" >> $CSVFILE

done
