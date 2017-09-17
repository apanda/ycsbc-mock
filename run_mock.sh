#/bin/bash

trap 'kill $(jobs -p)' SIGINT

workloads="./workloads/workloada.spec ./workloads/workloadb.spec ./workloads/workloadd.spec ./workloads/workloadf.spec"

for file_name in $workloads; do
  echo "Running Redis with for $file_name"
  ./ycsbc -db mock -threads 1 -P $file_name > $file_name.output
  wait
done

