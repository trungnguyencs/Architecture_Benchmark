# sudo perf stat -o ../results/scala/scala-4-32000.txt sbt run
# sudo perf stat -o ../results/scala/interval500.csv -x, -I 500 sbt run
sudo perf stat -o ../results/scala/interval500.txt -I 500 sbt run