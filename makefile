GC = gcc
MAIN = main.o
GRAPH = graph.o
WARN= -Wall -g

all: graph 
graph: $(MAIN) $(GRAPH) 
	$(GC) $(WARN) $(MAIN) $(GRAPH)  -o graph -lm
main.o:  main.c  graph.h
	$(GC) $(WARN) -c main.c
graph.o: graph.c  graph.h
		$(GC) $(WARN) -c graph.c 

clean: 
	rm -f *.o *.a *.so graph
.PHONY: clean all