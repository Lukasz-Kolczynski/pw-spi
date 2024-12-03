#!/bin/bash

compression_time() {
    local command="$1"
    local result=()
    for i in $(seq 1 5); do
        start=$(date +%s.%N)
        eval "$command" > /dev/null 2>&1
        end=$(date +%s.%N)
        result+=($(echo "$end - $start" | bc -l))
    done
    echo "${result[@]}" | awk '{sum=0; for (i=1; i<=NF; i++) sum+=$i; print sum/NF}'}

ghost_temp=$(mktemp -d) #tworzy tymczasowy
trap "rm -rf $ghost_temp" EXIT #usuwa


for dir in "$@"; do
    echo"$dir"
    echo -e "name/tcompress/tdecompress/tratio"

    archive="$ghost_temp/$(basename "$dir").tar"

    tar cvf "$archive" "$dir"
done
