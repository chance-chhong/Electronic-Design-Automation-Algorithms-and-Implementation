#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <set>
using namespace std;

class Grid {
public:
    friend class Router;
    Grid() : x(0), y(0), m(0), g(0), h(0), f(0), is_open(false), is_closed(false), is_block(false), parent(nullptr) {}
    void clear() {
        g = h = f = 0;
        is_open = is_closed = false;
        parent = NULL;
    }
private:
    int x;
    int y;
    int m;
    int g;  // cost of start grid to the grid
    int h;  // cost of the grid to end grid, many implemetations
    int f;  // cost of total = g+h
    bool is_open;   //is the grid in openList
    bool is_closed;   //is the grid in closeList
    bool is_block;  //is the grid block
    int id_occupying = -1;   //the current grid is occupied by net id, 0 represent no net occupying
    Grid* parent;
};

class Net {
public:
    friend class Router;
    int id = 0;
    int len = 0;
    int congestion = 0;
private:
    string name;
    pair<int, int> start;
    pair<int, int> end;
    vector<pair<int, int>> path;    //path except start grid and end grid
    vector<pair<int, int>> corner;  //start grid, turing grid, and end grid
};

//the net sort priority is according to its congestion
bool cmp_cong(const Net& a, const Net& b) { return a.congestion < b.congestion; }
//the net sort priority is according to its id
bool cmp_id(const Net& a, const Net& b) { return a.id < b.id; }
//the net sort priority is according to its overflow
bool cmp_length(const Net& a, const Net& b) { return a.len < b.len; }

class Router {
public:
    Router() : row(0), col(0), grid(), net() {}
    void read_file(const char*);
    void write_file(const char*);
    void set_grid();
    void AStar(Net&, vector<Net>&);
    //bool over(const Net&);
    void route();
private:
    int row;
    int col;
    vector<vector<Grid>> grid;
    vector<Net> net;
    bool between(int a, int b, int c) { return ((a <= b) && (b <= c)) || ((c <= b) && (b <= a)); }

    struct CompareNodes {
        bool operator()(const Grid* n1, const Grid* n2) const {
            return n1->f > n2->f; // f is used to sort the grid, smaller is better
        }
    };
    void clear_grid();
    void clear_path(Net&);
};

int main(int argc, char** argv) {
    Router router;
    router.read_file(argv[1]);
    router.write_file(argv[2]);
    return 0;
}

void Router::read_file(const char* input) {
    ifstream input_file(input);
    string temp_string;
    int temp_num;
    input_file >> temp_string >> row;
    input_file >> temp_string >> col;
    grid.resize(row, vector<Grid>(col));
    input_file >> temp_string >> temp_num;
    for (int i = 0; i < temp_num; i++) {
        int leftX, rightX, leftY, rightY;
        input_file >> leftX >> rightX >> leftY >> rightY;
        for (int y = leftY; y <= rightY; y++)
            for (int x = leftX; x <= rightX; x++)
                grid[y][x].is_block = true; // the grid is the block
    }
    set_grid();
    input_file >> temp_string >> temp_num;
    for (int i = 0; i < temp_num; i++) {
        int sourceX, sourceY, targetX, targetY;
        string name;
        input_file >> name >> sourceX >> sourceY >> targetX >> targetY;
        Net _net;
        _net.name = name;
        _net.id = i;
        _net.start = make_pair(sourceX, sourceY);
        _net.end = make_pair(targetX, targetY);
        net.push_back(_net);
        grid[sourceY][sourceX].is_block = true;
        grid[targetY][targetX].is_block = true;
    }
    input_file.close();
}

void Router::write_file(const char* output) {
    ofstream output_file(output);
    /*vector<Net> temp;
    for (const auto& i : net)
        temp.push_back(i.second);
    for (unsigned int i = 0; i < temp.size(); i++)
        for (unsigned int j = 0; j < temp.size(); j++)
            if (j != i) {
                //start point
                if (between(temp[i].start.first, temp[j].start.first, temp[i].end.first) && between(temp[i].start.second, temp[j].start.second, temp[i].end.second))
                    net[temp[i].id].congestion++;
                //end point
                else if (between(temp[i].start.first, temp[j].end.first, temp[i].end.first) && between(temp[i].start.second, temp[j].end.second, temp[i].end.second))
                    net[temp[i].id].congestion++;
            }
    for(const auto& i : net)
        cout<<i.second.start.first<<" "<<i.second.start.second<<"   "<<i.second.congestion<<endl;
    exit(0)
    temp.clear();
    for (const auto& i : net)
        temp.push_back(i.second);
    sort(temp.begin(), temp.end(), cmp_cong);

    //route
    unordered_map<int, int> t;
    for (unsigned int i = 0; i < temp.size(); i++) {
        clear_grid();
        AStar(temp[i].id, net);
        if (over(net[temp[i].id])) {
                for(unsigned int j = 0; j < net[temp[i].id].path.size(); j++){
                    if(grid[net[temp[i].id].path[j].second][net[temp[i].id].path[j].first].num_net != 1)
                        for(const auto& k : grid[net[temp[i].id].path[j].second][net[temp[i].id].path[j].first].overlap)
                            t[k.second] = k.second;
                }
                clear_path(net[temp[i].id]);
                for(const auto& itr : t)
                    clear_path(net[itr.second]);
                clear_grid();
                AStar(temp[i].id, net);
                for(const auto& itr : t){
                    clear_grid();
                    AStar(itr.second, net);
                }
            }
    }*/

    vector<Net> temp = net;
    sort(temp.begin(), temp.end(), cmp_cong);
    /*clock_t start = clock();
    int timeLimit = 110000; // execution time is at most 110s
    */
    //((clock() - start) * 1000 / CLOCKS_PER_SEC < timeLimit)
    for (unsigned int i = 0; i < net.size(); i++) {
        clear_grid();
        AStar(net[i], net);
    }
    /*
    bool flag = false;
    clock_t start = clock();
    int timeLimit = 110000; // execution time is at most 110s
    while ((clock() - start) * 1000 / CLOCKS_PER_SEC < timeLimit) {
        flag = true;
        temp.clear();
        for (const auto& i : net)
            temp.push_back(i.second);
        sort(temp.begin(), temp.end(), cmp_length);
        for (unsigned int i = 0; i < temp.size(); i++) {
            if (net[temp[i].id].overflow) {
                flag = false;
                clear_grid();
                clear_path(net[temp[i].id]);
                AStar(temp[i].id, net);
            }
        }
        if (flag)
            break;
    }
    temp.clear();
    for (const auto& i : net)
        temp.push_back(i.second);
    sort(temp.begin(), temp.end(), cmp_id);*/

    for (unsigned int i = 0; i < net.size(); i++) {
        output_file << net[i].name << " " << net[i].len << endl;
        output_file << "begin" << endl;
        for (unsigned int j = 0; j < net[i].corner.size() - 1; j++)
            output_file << net[i].corner[j].first << " " << net[i].corner[j].second << " " << net[i].corner[j + 1].first << " " << net[i].corner[j + 1].second << endl;
        output_file << "end" << endl;
    }
    /*for(int i = 0; i< 50; i++)
    cout<<net[i].corner.size();*/
    output_file.close();
}

void Router::AStar(Net& _net, vector<Net>& net) {

    priority_queue<Grid*, vector<Grid*>, CompareNodes> openList; // store the grid would expand
    pair<int, int>start = _net.start;
    pair<int, int>end = _net.end;
    grid[start.second][start.first].g = 0;
    grid[start.second][start.first].h = abs(start.first - end.first) + abs(start.second - end.second);     //Manhattan distance
    grid[start.second][start.first].f = grid[start.second][start.first].g + grid[start.second][start.first].h;
    grid[start.second][start.first].is_open = true; // store the start grid in openList
    openList.push(&grid[start.second][start.first]);

    grid[end.second][end.first].is_block = false;

    set<int> unique_overlap_num;
    vector<Net> overlap;

    while (!openList.empty()) {
        Grid* current = openList.top(); // pop out the grid with the smallest cost
        openList.pop();

        current->is_closed = true; // store the grid in closeList

        // arrive the end grid, output the shortest path
        if (current->x == end.first && current->y == end.second) {
            //cout << end.first << " " << end.second << endl;
            grid[end.second][end.first].is_block = true;
            Grid* prev = current->parent;
            bool is_horizon = (prev->x != current->x) ? 1 : 0;
            //corner has start and end, path otherwise
            vector<pair<int, int>>& corner = _net.corner;
            vector<pair<int, int>>& path = _net.path;

            corner.push_back(make_pair(current->x, current->y));
            while (prev != nullptr) {
                if (is_horizon != (prev->x != current->x)) {
                    corner.push_back(make_pair(current->x, current->y));
                    is_horizon = !is_horizon;
                }
                path.push_back(make_pair(prev->x, prev->y));
                if (prev->id_occupying != -1 && !prev->is_block) {
                    unique_overlap_num.insert(prev->id_occupying);
                }
                grid[prev->y][prev->x].id_occupying = _net.id;
                current = current->parent;
                prev = prev->parent;
            }
            path.pop_back();
            _net.len = path.size();
            corner.push_back(make_pair(current->x, current->y));
            reverse(corner.begin(), corner.end());
        }

        // expand the neighbor
        vector<pair<int, int>> neighbors = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} }; // up, down, left, right

        for (auto& neighbor : neighbors) {
            int nextX = current->x + neighbor.second;
            int nextY = current->y + neighbor.first;

            // check the gird in map
            if (nextX >= 0 && nextX < col && nextY >= 0 && nextY < row) {
                // check the grid is block or in closeList
                if (grid[nextY][nextX].is_block == true || grid[nextY][nextX].is_closed == true)
                    continue; // if the grid in the closeList, one more time
                else {
                    int tentativeGScore = current->g + 1; // tentative g = current g + 1
                    int tentativeHScore = abs(end.first - nextX) + abs(end.second - nextY);; // tentative h
                    int tentativeFScore = tentativeGScore + tentativeHScore; // tentative f = tentative g + tentative h
                    if (grid[nextY][nextX].id_occupying != -1)
                        tentativeFScore += 10000;

                    // if the grid is not in openList or g is smaller, update
                    if (!grid[nextY][nextX].is_open || tentativeFScore < grid[nextY][nextX].f) {

                        if (!grid[nextY][nextX].is_open) {
                            grid[nextY][nextX].is_open = true;
                        }
                        else {
                            Grid* target = &grid[nextY][nextX];
                            vector<Grid*> temp;
                            while (!openList.empty()) {
                                Grid* cur = openList.top();
                                openList.pop();
                                if (cur == target)
                                    break;
                                temp.push_back(cur);
                            }
                            for (unsigned int i = 0; i < temp.size(); i++)
                                openList.push(temp[i]);
                        }
                        grid[nextY][nextX].parent = current;
                        grid[nextY][nextX].g = tentativeGScore;
                        grid[nextY][nextX].h = tentativeHScore;
                        grid[nextY][nextX].f = tentativeFScore;
                        openList.push(&grid[nextY][nextX]);
                    }
                }
            }
        }
    }
    //rip off some routed nets, route blocked net again, and reroute the ripped-up net
    if (!unique_overlap_num.empty()) {
        for (const auto& i : unique_overlap_num)
            overlap.push_back(net[i]);
        sort(overlap.begin(), overlap.end(), cmp_length);
        for (unsigned int i = 0; i < overlap.size(); i++)
            clear_path(net[overlap[i].id]);
        clear_grid();
        clear_path(_net);
        AStar(_net, net);
        for (unsigned int i = 0; i < overlap.size(); i++) {
            clear_grid();
            AStar(net[overlap[i].id], net);
        }
    }

}

void Router::set_grid() {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {
            grid[i][j].x = j;
            grid[i][j].y = i;
            grid[i][j].m = 100 * min(min(row - i, i), min(col - j, j));
        }
}

void Router::clear_grid() {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            grid[i][j].clear();
}

void Router::clear_path(Net& _net) {
    for (unsigned int i = 0; i < _net.path.size(); i++) {
        grid[_net.path[i].second][_net.path[i].first].id_occupying = -1;
    }

    _net.path.clear();
    _net.corner.clear();
}

/*bool Router::over(const Net& n){
    for(unsigned int i = 0; i < n.path.size(); i++)
        if(grid[n.path[i].second][n.path[i].first].num_net != 1)
            return true;
    return false;
}*/

void Router::route() {
    //sort(net.begin(), net.end(), cmp_cong);
    //for(auto& i : net)
}
