#!/bin/bash

mkdir -p /tmp/data/random /tmp/data/empty /tmp/data/various

for i in $(seq 1 5); do

    dd if=/dev/urandom of=/tmp/data/random/file$i bs=10M count=1 status=none

done

for i in $(seq 1 5); do

    dd if=/dev/zero of=/tmp/data/empty/file$i bs=10M count=1 status=none

done

cp /home/u335775/Pobrane/SilesiaCorpus-master/* /tmp/data/various

