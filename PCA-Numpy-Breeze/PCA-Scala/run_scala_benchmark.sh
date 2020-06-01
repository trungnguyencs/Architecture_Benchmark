# sudo perf stat -o ../results/scala/scala-4-32000.txt sbt run
# sudo perf stat -o ../results/scala/interval500.csv -x, -I 500 sbt run
sudo perf stat -o ../results/py/interval500.txt -e \
cycles,\
instructions,\
branches,\
branch-misses,\
L1-dcache-load-misses,\
L1-icache-load-misses,\
LLC-load-misses,\
LLC-store-misses,\
l2_rqsts.miss\
 -I 500 sbt run
# sudo perf stat -o ../results/py/interval500.csv -x, -e \
# cycles,\
# instructions,\
# branches,\
# branch-misses,\
# L1-dcache-load-misses,\
# L1-icache-load-misses,\
# LLC-load-misses,\
# LLC-store-misses,\
# l2_rqsts.miss\
#  -I 500 sbt run