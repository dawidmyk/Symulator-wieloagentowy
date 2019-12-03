CPPFLAGS=-std=c++17 -Iheaders -pthread
OBJ=builds/simulation.o builds/graph.o builds/elements.o builds/console.o builds/agent.o builds/main.o

builds/app: $(OBJ)
	g++ $(CPPFLAGS) $(OBJ) -o $@
	
builds/%.o: sources/%.cpp headers/*.hpp
	g++ $(CPPFLAGS) -c $< -o $@

clean_obj:
	rm builds/*.o
	
clean_app:
	rm builds/app
