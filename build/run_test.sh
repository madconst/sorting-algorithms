#!/bin/bash

# Timeout in seconds after which the sorting process will be killed if still running:
TIMEOUT=60 # 1800
LOGFILE="/dev/stdout"
CSVFILE="results.tsv"

declare -A RESULTS

ALGORITHMS=(
    std_sort
    qsort
    quick_sort
    quick_sort+insertion_sort
    quick_sort+selection_sort
    merge_sort
    merge_sort_recursive_top_down
    heap_sort
    selection_sort
    insertion_sort
    radix_sort
    bucket_sort
)

N_ELEMENTS=(
    1E2 2E2 3E2 4E2 5E2 6E2 7E2 8E2 9E2
    1E3 2E3 3E3 4E3 5E3 6E3 7E3 8E3 9E3
    1E4 2E4 3E4 4E4 5E4 6E4 7E4 8E4 9E4
    1E5 2E5 3E5 4E5 5E5 6E5 7E5 8E5 9E5
    1E6 2E6 3E6 4E6 5E6 6E6 7E6 8E6 9E6
    1E7 2E7 3E7 4E7 5E7 6E7 7E7 8E7 9E7
    1E8 2E8 3E8 4E8 5E8 6E8 7E8 8E8 9E8
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
        elif [ $? -eq 124 ]; then
            echo "$s timed out" >> $LOGFILE
        fi
        diff_result=$(diff -q $s.sorted std_sort.sorted)
        if [ $? -eq 0 ]; then
            time_spent=$(echo "$result" | grep 'Time spent' | cut -d" " -f3)
            RESULTS[$s,$n]=$(echo "$result" | grep 'Time spent' | cut -d" " -f3)
        else
            RESULTS[$s,$n]=NaN
        fi

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
