# sudo perf stat -o ./results/py/py-64-32000.txt python PCA-Python.py
# sudo perf stat -o ./results/py/interval500.csv -x, -I 500 python PCA-Python.py
# sudo perf stat -o ./results/py/interval500.txt -e \
# cycles,\
# instructions,\
# branches,\
# branch-misses,\
# L1-dcache-load-misses,\
# L1-icache-load-misses,\
# LLC-load-misses,\
# LLC-store-misses,\
# l2_rqsts.miss\
#  -I 500 python PCA-Python.py
sudo perf stat -o ./results/py/interval500.csv -x, -e \
cycles,\
instructions,\
branches,\
branch-misses,\
L1-dcache-load-misses,\
L1-icache-load-misses,\
LLC-load-misses,\
LLC-store-misses,\
l2_rqsts.miss\
 -I 500 python PCA-Python.py