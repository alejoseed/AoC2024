#include <iostream>
#include <random>
void createGrids(int maxHashes, int length);

std::random_device rd;
std::mt19937 gen(rd()); 

int main() {
    freopen("output.txt", "w", stdout);

    // length 10 string
    createGrids(2, 10);
    std::cout << '\n';

    // length 11 string
    createGrids(2, 11);
    std::cout << '\n';
    
    // length 12 string
    createGrids(3, 12);
    std::cout << '\n';
    
    // length 15 string
    createGrids(4, 15);
    std::cout << '\n';

    return 0;
}

/**
 * @brief Create a Grids object based off a input string. The grid would be 
 * symmetrical meaning a length of 10 would be a grid of length 10x10
 */
void createGrids(int maxHashes, int length) {
    std::uniform_int_distribution<int> dist(0, maxHashes);
    std::uniform_int_distribution<int> lineLength(0, length);

    for (int i = 0; i < length; i++) {
        std::string line(length, '.');

        // Up to a max of 2 times it should show # on random indeces.
        int random_number = dist(gen);
        for (int x = 0; x < random_number; x++) {
            // Seed the random number to see where to place the #
            int second_random_number_for_index = lineLength(gen);
            line[second_random_number_for_index] = '#';
        }

        std::cout << line << "\n";
    };
}


