#include "../headers/console.hpp"
#include "../headers/graph.hpp"
#include <iostream>
#include <string>

void Console::runConsole(Graph graph) {
	while (1) {
		graph.actualize();
	}
}

