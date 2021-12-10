#include <iostream>
#include <vector>

struct position {
    int x;
    int y;

    position (int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Grid {
    int* _grid;

public:
    Grid() {
        _grid = new int[16]{};
    }

    Grid(int start_figures[4]) {
        _grid = new int[16]{};
        for (int i = 0; i < 4; i++) {
            _grid[i] = start_figures[i];
        }
    }

    Grid (int start_figures[4], std::vector<position> figure_positions) {
        _grid = new int[16]{};
        for (int i = 0; i < 4; i++) {
            _grid[i] = start_figures[i];
            int index = figure_positions[i].y * 4 + figure_positions[i].x;
            if(_grid[index] == 0) _grid[index] = start_figures[i];
        }
    }

    int& get(int y, int x) {
        int index = y * 4 + x;
        return _grid[index];
    }

    int score() {
        int result = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result += (_grid[i*4+j] * i);
            }
        }
        return result;
    }

    void print() {
        for (int i = 0; i < 16; i++){
            std::cout << _grid[i] << " ";
            if ((i+1) % 4 == 0) std::cout << std::endl;
        }
    }
};

std::vector<position> calculate_knight_positions(int start) {
    std::vector<position> results;

    results.push_back(position(start, 0));

    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            if (i+abs(j - start) == 3) {
                position p (j, i);
                results.push_back(p);
            }
        }
    }
    return results;
}

std::vector<position> calculate_rook_positions(int start) {
    std::vector<position> results;

    for (int i = 0; i < 4; i++) {
        position p(start, i);
        results.push_back(p);
    }
    return results;
}

std::vector<position> calculate_bishop_positions(int start) {
    std::vector<position> results;

    for (int i = 0; i+start < 4; i++) {
        position p (i+start, i);
        results.push_back(p);
    }
    for (int i = 0; i < start+1; i++) {
        position p (start-i, i);
        results.push_back(p);
    }
    return results;
}

std::vector<position> calculate_queen_positions(int start) {
    std::vector<position> results;
    std::vector<position> first = calculate_rook_positions(start);
    std::vector<position> second = calculate_bishop_positions(start);

    for (int i = 0; i < first.size(); i++) results.push_back(first[i]);
    for (int i = 0; i < second.size(); i++) results.push_back(second[i]);

    return results;
}

std::vector<Grid> calculate_grids(int start_figures[4]) {
    // Конь = 1
    // Ладья = 2
    // Слон = 3
    // Ферзь = 4

    std::vector<Grid> grids;
    std::vector<position> knight_positions;
    std::vector<position> rook_positions;
    std::vector<position> bishop_positions;
    std::vector<position> queen_positions;

    for (int i = 0; i < 4; i++) {
        switch (start_figures[i]) {
            case 1:
                knight_positions = calculate_knight_positions(i);
                break;
            case 2:
                rook_positions = calculate_rook_positions(i);
                break;
            case 3:
                bishop_positions = calculate_bishop_positions(i);
                break;
            case 4:
                queen_positions = calculate_queen_positions(i);
                break;
            default:
                break;
        }
    }

    for (position knight : knight_positions) {
        for (position rook : rook_positions) {
            for (position bishop : bishop_positions) {
                for (position queen : queen_positions) {
                    std::vector<position> current_case_positions = {knight, rook, bishop, queen};
                    grids.push_back(Grid(start_figures, current_case_positions));
                }
            }
        }
    }
    return grids;
}

int main() {
    int start_figures[4] = {1,2,3,4};
    std::vector<Grid> grids = calculate_grids(start_figures);
    Grid max_score_grid = Grid();
    int max_score = 0;

    for (Grid grid : grids) {
        if (max_score < grid.score()){
            max_score = grid.score();
            max_score_grid = grid;
        }
    }

    max_score_grid.print();
    std::cout << max_score << std::endl;

    return 0;
}
