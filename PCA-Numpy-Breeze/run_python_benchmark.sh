# sudo perf stat -o ./results/py/py-64-32000.txt python PCA-Python.py
# sudo perf stat -o ./results/py/interval500.csv -x, -I 500 python PCA-Python.py
sudo perf stat -o ./results/py/interval500.txt -I 500 python PCA-Python.py