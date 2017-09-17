Quickstart
----------

- Build this, you will need hiredis `sudo apt-get install libhiredis-dev`.
- Use my new fangled mock driver to get a trace `./ycsbc -db mock -threads 1 -P workloads/workloadb.spec > wrkloadb.out`. 
  This will be a set of gets and puts.
- Pass trace through augment.py `/augment.py wrkloada.out wrkloada-2 2` (first argument is trace, second argument is a
  file prefix, third argument is number of servers) to get an access log (wrkloada-2.access) and a loading log
  (wrkloada-2.load). Both are  in the form:
  `<server-id> <command> <key> <value>`
- Prosper.
