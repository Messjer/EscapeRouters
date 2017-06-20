# Source files in C++ and Java (only in Visualizer)
## Common Module
Basic board representation and Base router class are declared here.
## Network Flow
Network Flow solver is stored here.
## DC
A network flow router which implements divide-conquer by splitting the board into quarters. About 20x faster than NetworkFlow router. Note that this router may produce slightly longer paths for odd-sized boards.
## Rule
A high performance, suboptimal rule-based router.

PS. DC and Rule only work for square boards.
