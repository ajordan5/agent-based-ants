# agent-based-ants

![](https://github.com/ajordan5/agent-based-ants/blob/master/doc/ant.gif)

Agent based modeling of an ant colony. To start, all ants begin at the colony and wander with a random heading rate until they find either pheromones or food. Once food is found the ants again search for pheromones or the home colony. If the colony is reached, the food is dropped off and the ant again searches for food.

Two types of pheromones are placed:
* Food pheromones by ants holding food (red)
* Home pheromones by ants without food (green)

## Dependencies
* Qt6 (building with Qt Creator is recommended)
* GTest
