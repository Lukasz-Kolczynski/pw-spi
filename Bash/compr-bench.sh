#!/bin/bash

measure_time() {
    local command="$1"
    start=$(date +%s.%N)
    eval "$command" > /dev/null 2>&1
    end=$(date +%s.%N)
    echo "$(echo "$end - $start" | bc -l)"
}

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <directories>"
    exit 1
fi

compressors=("gzip -k" "bzip2 -k" "xz -k" "zstd -k" "lz4 -k" "7z a -y")
decompressors=("gzip -d -k" "bzip2 -d -k" "xz -d -k" "zstd -d -k" "lz4 -d -k" "7z x -y")

tmp_dir=$(mktemp -d)
trap "rm -rf $tmp_dir" EXIT

for dir in "$@"; do
    if [ ! -d "$dir" ]; then
        echo "Directory $dir does not exist. Skipping."
        continue
    fi

    echo "$dir"
    echo -e "name\tcompress\tdecompress\tratio"

    archive="$tmp_dir/$(basename "$dir").tar"
    tar cf "$archive" -C "$(dirname "$dir")" "$(basename "$dir")"
    original_size=$(stat -c%s "$archive")

    for i in "${!compressors[@]}"; do
        compressor="${compressors[$i]}"
        decompressor="${decompressors[$i]}"
        compressed_file="$archive.compressed"

        compress_time=$(measure_time "$compressor $archive -o $compressed_file")
        compressed_size=$(stat -c%s "$compressed_file" 2>/dev/null || echo 0)

        decompress_time=$(measure_time "$decompressor $compressed_file")
        ratio=$(echo "scale=2; $compressed_size / $original_size * 100" | bc -l 2>/dev/null || echo 0)

        echo -e "$(echo "$compressor" | awk '{print $1}')\t$compress_time\t$decompress_time\t${ratio}%"

        rm -f "$compressed_file"
    done

    rm -f "$archive"
done
