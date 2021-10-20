/*
ID: th3c0r11
TASK: castle
LANG: C++14
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>

using namespace std;

#define WEST 1
#define NORTH 2
#define EAST 4
#define SOUTH 8
#define FOUND 16

// floorplan: M x N

vector<unsigned int> modules;

// maps module indices to room sizes
map<int, int> roomSizes;

// stores adjacent module indices per room & room size
vector<pair<set<pair<int, int>>, int>> allAdjacentModules;

int main()
{
	ifstream in{"castle.in"};
	ofstream out{"castle.out"};

	int X, Y;

	in >> X >> Y;

	for (int y = 0; y < Y; ++y) {
		for (int x = 0; x < X; ++x) {
			unsigned int module;
			in >> module;
			modules.push_back(module);
		}
	}

	int noRooms = 0;
	int largestRoom = 0;
	int largestPotRoom = 0;

	for (int i = 0; i < modules.size(); ++i) {
		while (modules[i] & FOUND)
			++i;
		if (i >= modules.size())
			break;
		++noRooms;

		int roomSize = 0;
		queue<int> nextIndices;
		set<pair<int, int>> adjacentModules;
		vector<int> roomModules;
		nextIndices.push(i);
		modules[i] |= FOUND;
		while (!nextIndices.empty()) {
			auto nextModule = nextIndices.front();
			++roomSize;
			nextIndices.pop();
			roomModules.push_back(nextModule);

			auto erroneousAdjacent = adjacentModules.find({nextModule, WEST});
			if (erroneousAdjacent != adjacentModules.end())
				adjacentModules.erase(erroneousAdjacent);
			if ((erroneousAdjacent = adjacentModules.find({nextModule, EAST})) != adjacentModules.end())
				adjacentModules.erase(erroneousAdjacent);
			if ((erroneousAdjacent = adjacentModules.find({nextModule, NORTH})) != adjacentModules.end())
				adjacentModules.erase(erroneousAdjacent);
			if ((erroneousAdjacent = adjacentModules.find({nextModule, SOUTH})) != adjacentModules.end())
				adjacentModules.erase(erroneousAdjacent);

			if ((modules[nextModule] & NORTH) == 0) {
				if ((modules[nextModule - X] & FOUND) == 0) {
					nextIndices.push(nextModule - X);
					modules[nextModule - X] |= FOUND;
				}
			} else if (nextModule - X >= 0 && !(modules[nextModule - X] & FOUND))  {
				adjacentModules.insert({nextModule - X, NORTH});
			}
			if ((modules[nextModule] & WEST) == 0) {
				if ((modules[nextModule - 1] & FOUND) == 0) {
					nextIndices.push(nextModule - 1);
					modules[nextModule - 1] |= FOUND;
				}
			} else if (nextModule - 1 >= 0 && (nextModule % X != 0) && !(modules[nextModule - 1] & FOUND)) {
				adjacentModules.insert({nextModule - 1, WEST});
			}
			if ((modules[nextModule] & EAST) == 0) {
				if ((modules[nextModule + 1] & FOUND) == 0) {
					nextIndices.push(nextModule + 1);
					modules[nextModule + 1] |= FOUND;
				}
			} else if (nextModule + 1 < modules.size() && ((nextModule + 1) % X != 0) && !(modules[nextModule + 1] & FOUND)) {
				adjacentModules.insert({nextModule + 1, EAST});
			}
			if ((modules[nextModule] & SOUTH) == 0) {
				if ((modules[nextModule + X] & FOUND) == 0) {
					nextIndices.push(nextModule + X);
					modules[nextModule + X] |= FOUND;
				}
			} else if (nextModule + X < modules.size() && !(modules[nextModule + X] & FOUND)) {
				adjacentModules.insert({nextModule + X, SOUTH});
			}
		}

		for (auto i : roomModules)
			roomSizes[i] = roomSize;
		
		allAdjacentModules.push_back({move(adjacentModules), roomSize});

		if (roomSize > largestRoom) {
			largestRoom = roomSize;
			roomSize = 0;
		}
	}

	int largestCreatable = 0;
	int wallX = 0, wallY = 0;
	char direction;

	for (auto &room : allAdjacentModules) {
		auto roomSize = room.second;
		for (auto module : room.first) {
			auto moduleIndex = module.first;
			auto moduleAdjWall = module.second; // from other room's perspective
			auto newSize = roomSize + roomSizes[moduleIndex];

			int newWallX = moduleIndex % X + 1;
			int newWallY = moduleIndex / X + 1;
			char newDirection;

			switch (moduleAdjWall) {
			case NORTH:
				++newWallY;
				newDirection = 'N';
				break;
			case SOUTH:
				newDirection = 'N';
				break;
			case EAST:
				--newWallX;
				newDirection = 'E';
				break;
			case WEST:
				newDirection = 'E';
			}

			if (newSize > largestCreatable) {
				largestCreatable = newSize;
				wallX = newWallX;
				wallY = newWallY;
				direction = newDirection;
			} else if (newSize == largestCreatable) {
				if (newWallX < wallX) {
					wallX = newWallX;
					wallY = newWallY;
					direction = newDirection;
				} else if (newWallX == wallX) {
					if (newWallY > wallY) {
						wallX = newWallX;
						wallY = newWallY;
						direction = newDirection;
					} else if (newWallY == wallY) {
						if (newDirection == 'N') {
							wallX = newWallX;
							wallY = newWallY;
							direction = newDirection;
						}
					}
				}
			}
		}
	}

	out << noRooms << '\n' << largestRoom << '\n' << largestCreatable <<
		'\n' << wallY << ' ' << wallX << ' ' << direction << '\n';
}
