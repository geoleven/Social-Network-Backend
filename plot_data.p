set term png size 1920,1080
set output "degreedistribution.png"
set title "Graph Degree Distribution"
set xtics 0.02
set ytics 2
set xlabel "Distribution"
set ylabel "Degree"
plot "graph_data.txt" with lines
