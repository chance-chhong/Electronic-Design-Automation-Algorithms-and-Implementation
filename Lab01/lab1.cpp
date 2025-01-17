#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <math.h>   //calculate the abs of double
#include <unordered_map>

using namespace std;

class Bipartition{
    public:
        Bipartition(){bucket_list.resize(2);}
        void readInputFile(const string& filename);
    private:
        void gain_initialize();
        void FMalgorithm();
        struct net{
            int num_in_block[2] = {0};
            bool block_is_locked[2] = {false};
            vector<unordered_map<int, int>> set_cell;
            net(){set_cell.resize(2);}
        };
        struct cell{
            bool check = false;
            bool is_locked = false;
            int id;
            int block = 0;
            int cell_gain = 0;
            double distance_balance = 0;
            vector<int> set_net;
        };
        double calculate_balance(int block);
        void bucket_maintain(cell& free_cell, int in_or_de);
        void gain_maintain(int block);
        vector<net> net_list;
        vector<cell> cell_list;
        vector<vector<unordered_map<int, cell>>> bucket_list;
        vector<cell> free_cell_list;
        vector<int> list_maximum;
        enum cal{
            increment,
            decrement
        };
        enum Block{
            block0,
            block1
        };
        int index_max_gain[2] = {0};
        int Pmax = 0;
        int num_in_block[2] = {0};
        int largest_partial_sum = 0;
};




int main(int argc, char* argv[]) {
    Bipartition Bi;
    Bi.readInputFile(argv[1]);
	return 0;
}

void Bipartition::readInputFile(const string& filename){
    ifstream input_file(filename);
    string input_string;
    stringstream sstream;
    srand(10);
    int num_net, num_cell;
    if (input_file.is_open()) {
        // Read the number of nets and cells
        input_file >> num_net >> num_cell;
        cell_list.resize(num_cell + 1);
        net_list.resize(num_net + 1);
        // Read the nets
        getline(input_file,input_string);
        for (int i = 1; i < num_net + 1; i++) {
            getline(input_file,input_string);
            int temp;
            sstream.str("");
            sstream.clear();
            sstream << input_string;
            //place all the cells in the block0
            while(sstream>>temp){
                if(!cell_list.at(temp).check){
                    cell_list.at(temp).check = true;
                    cell_list.at(temp).block = 0;
                    cell_list.at(temp).id = temp;
                    num_in_block[0]++;
                }
                cell_list.at(temp).set_net.push_back(i);    // add the net to the cell's list of connected nets
                net_list.at(i).set_cell.at(cell_list.at(temp).block).emplace(temp, temp);
                net_list.at(i).num_in_block[cell_list.at(temp).block]++;
            }

        }
        input_file.close();
        //record the max pins
        for(int i = 1; i < (int)cell_list.size(); i++)
            if((int)cell_list.at(i).set_net.size() > Pmax)
                Pmax = (int)cell_list.at(i).set_net.size();
    }
    else {
        cout << "Error: cannot open input file \"" << filename << "\"" << endl;
        exit(1);
    }
    ofstream output_file("output.txt");
    //transfer the some cells from block0 to block1
    gain_initialize();
    for(int j = 0; j < 2; j++) {
        bucket_list.at(j).clear();
        bucket_list.at(j).resize(2 * Pmax + 1);
        index_max_gain[j] = 0;
    }
    for(unsigned int i = 1; i < cell_list.size(); i++) {
        bucket_list.at(cell_list.at(i).block).at(cell_list.at(i).cell_gain + Pmax).emplace(cell_list.at(i).id, cell_list.at(i));
            if(cell_list.at(i).cell_gain + Pmax > index_max_gain[cell_list.at(i).block])
                index_max_gain[cell_list.at(i).block] = cell_list.at(i).cell_gain + Pmax;
        }
    unsigned int n = cell_list.size() - 1;
    while(n>(cell_list.size()-1)/2){
        gain_maintain(block0);
        n--;
    }
    //repeat the whole process
    for(int i = 0; i < 5; i++){
        gain_initialize();
        FMalgorithm();
    }
    for(unsigned int i = 1; i < cell_list.size(); i++)
        output_file<<cell_list.at(i).block<<endl;
    output_file.close();
}

void Bipartition::gain_initialize(){
    //initialize the cell_gain of all the cells according to the block which they are from
    for(unsigned int i = 1; i < cell_list.size(); i++)
         cell_list.at(i).cell_gain = 0;
    for(unsigned int i = 1; i < cell_list.size(); i++)
        for(unsigned int j = 0; j < cell_list.at(i).set_net.size(); j++)
            if(net_list.at(cell_list.at(i).set_net.at(j)).num_in_block[cell_list.at(i).block] == 1)    //F(n) == 1, gain++
                cell_list.at(i).cell_gain += 1;
            else if(net_list.at(cell_list.at(i).set_net.at(j)).num_in_block[!cell_list.at(i).block] == 0)   //T(n) == 0, gain--
                cell_list.at(i).cell_gain -= 1;
}

double Bipartition::calculate_balance(int block){
    return block ? ((double)(num_in_block[1] - 1)/(cell_list.size() - 1)) : ((double)(num_in_block[0] - 1)/(cell_list.size() - 1));
}

void Bipartition::FMalgorithm(){
    //initialize the bucket and index of max gain
    for(int j = 0; j < 2; j++) {
        bucket_list.at(j).clear();
        bucket_list.at(j).resize(2 * Pmax + 1);
        index_max_gain[j] = 0;
    }
    list_maximum.clear();
    //unlock all the cells
    for(unsigned int i = 0; i < free_cell_list.size(); i++)
        cell_list.at(free_cell_list.at(i).id).is_locked = false;
    free_cell_list.clear();
    //unlock the two blocks of all the nets
    for(unsigned int i = 1; i < net_list.size(); i++){
        net_list.at(i).block_is_locked[0] = false;
        net_list.at(i).block_is_locked[1] = false;
    }
    //place all the cells in bucket0 or bucket1 and set the index of max_gain
    for(unsigned int i = 1; i < cell_list.size(); i++) {
        bucket_list.at(cell_list.at(i).block).at(cell_list.at(i).cell_gain + Pmax).emplace(cell_list.at(i).id, cell_list.at(i));
            if(cell_list.at(i).cell_gain + Pmax > index_max_gain[cell_list.at(i).block])
                index_max_gain[cell_list.at(i).block] = cell_list.at(i).cell_gain + Pmax;
    }
    //repeat the whole process until largest partial sum <= 0 or two buckets are empty
    int maximum = 0;
    largest_partial_sum = 0;
    while(true){
        if(index_max_gain[0] > index_max_gain[1]) {
            if(calculate_balance(block0) > 0.45 && calculate_balance(block0) < 0.55)
                gain_maintain(block0);
            else
                gain_maintain(block1);
        }else if(index_max_gain[0] < index_max_gain[1]) {
            if(calculate_balance(block1) > 0.45 && calculate_balance(block1) < 0.55)
                gain_maintain(block1);
            else
                gain_maintain(block0);
        }else {
            if(fabs(calculate_balance(block0) - 0.5) > fabs(calculate_balance(block1) - 0.5))
                gain_maintain(block1);
            else
                gain_maintain(block0);
        }
        largest_partial_sum += free_cell_list.back().cell_gain;
        if(largest_partial_sum > maximum) {
            maximum = largest_partial_sum;
            list_maximum.clear();
            list_maximum.push_back(free_cell_list.size() - 1);
        }else if(largest_partial_sum == maximum)
            list_maximum.push_back(free_cell_list.size() - 1);
        else if((bucket_list.at(0).at(0).empty() && bucket_list.at(1).at(0).empty()) || largest_partial_sum <= 0){
            break;
        }
    }
    int minimum = 1;
    int index_minimum = 0;
    //record transfer the cell until the largest partial sum and the best balance
    for(unsigned int i = 0; i < list_maximum.size(); i++)
        if(minimum < free_cell_list.at(list_maximum.at(i)).distance_balance){
            minimum = free_cell_list.at(list_maximum.at(i)).distance_balance;
            index_minimum = list_maximum.at(i);
        }
    //retransfer the remaining cells
    for(unsigned int i = index_minimum + 1; i < free_cell_list.size(); i++){
        cell_list.at(free_cell_list.at(i).id).block = !cell_list.at(free_cell_list.at(i).id).block;
        num_in_block[cell_list.at(free_cell_list.at(i).id).block]++;
        num_in_block[!cell_list.at(free_cell_list.at(i).id).block]--;
        for(unsigned int j = 0; j < cell_list.at(free_cell_list.at(i).id).set_net.size(); j++) {
            net& net_n = net_list.at(cell_list.at(free_cell_list.at(i).id).set_net.at(j));
            net_n.num_in_block[cell_list.at(free_cell_list.at(i).id).block]++;
            net_n.num_in_block[!cell_list.at(free_cell_list.at(i).id).block]--;
            net_n.set_cell.at(cell_list.at(free_cell_list.at(i).id).block).emplace(free_cell_list.at(i).id, free_cell_list.at(i).id);
            net_n.set_cell.at(!cell_list.at(free_cell_list.at(i).id).block).erase(net_n.set_cell.at(!cell_list.at(free_cell_list.at(i).id).block).find(free_cell_list.at(i).id));
        }
    }
}

void Bipartition::gain_maintain(int num_block){
    num_in_block[num_block]--;  num_in_block[!num_block]++;     //number of cells in block changes because of cell transfer
    //handle the base cell in bucket according to block
    int id_base;
    id_base = bucket_list.at(num_block).at(index_max_gain[num_block]).begin()->first;    //set the max_gain cell as the base cell
    cell_list.at(id_base).is_locked = true;     //lock the base cell, so its cell_gain would never change
    bucket_list.at(num_block).at(index_max_gain[num_block]).erase(bucket_list.at(num_block).at(index_max_gain[num_block]).begin());     //delete the base cell from bucket list
    cell_list.at(id_base).block = !cell_list.at(id_base).block;     //transfer the cell to the other block
    cell_list.at(id_base).distance_balance = fabs((double)num_in_block[num_block] / (cell_list.size() - 1) - 0.5);  //store the balance distance
    free_cell_list.push_back(cell_list.at(id_base));   //place the base cell in free cell list
    //for each net n on the base cell
    for(unsigned int i = 0; i < cell_list.at(id_base).set_net.size(); i++) {
        net& net_n = net_list.at(cell_list.at(id_base).set_net.at(i));
        for(unordered_map<int, int>::iterator itr = net_n.set_cell.at(num_block).begin(); itr != net_n.set_cell.at(num_block).end(); itr++)
            if(itr->first == id_base){
                net_n.set_cell.at(!num_block).emplace(itr->first, itr->second);
                net_n.set_cell.at(num_block).erase(itr);
                break;
            }
        //there exists a critical net before move
        if(!net_n.block_is_locked[!num_block]){
            //if T(n) == 0 before move
            if(net_n.num_in_block[!num_block] == 0) {
                for(unordered_map<int, int>::iterator itr = net_n.set_cell.at(num_block).begin(); itr != net_n.set_cell.at(num_block).end(); itr++)
                    //the neighbor cell in from_block is free?
                    if(cell_list.at(itr->first).is_locked == false){
                        bucket_maintain(cell_list.at(itr->first), increment);}
            //if T(n) == 1 before move
            }else if(net_n.num_in_block[!num_block] == 1)
                for(unordered_map<int, int>::iterator itr = net_n.set_cell.at(!num_block).begin(); itr != net_n.set_cell.at(!num_block).end(); itr++)
                    //the neighbor cell in to_block is free?
                    if(cell_list.at(itr->first).is_locked == false){
                        bucket_maintain(cell_list.at(itr->first), decrement);}
        }
        net_n.block_is_locked[!num_block] = true;   //lock the T(n)
        net_n.num_in_block[!num_block]++;  //after the move, T(n)++;
        net_n.num_in_block[num_block]--;   //after the move, F(n)--;
        //there exists a critical net after move
        if(!net_n.block_is_locked[num_block]){
            //if F(n) == 0 after move
            if(net_n.num_in_block[num_block] == 0) {
                for(unordered_map<int, int>::iterator itr = net_n.set_cell.at(!num_block).begin(); itr != net_n.set_cell.at(!num_block).end(); itr++)
                    //the neighbor cell in to_block is free?
                    if(cell_list.at(itr->first).is_locked == false){
                        bucket_maintain(cell_list.at(itr->first), decrement);}
            //if F(n) == 1 after move
            }else if(net_n.num_in_block[num_block] == 1)
                for(unordered_map<int, int>::iterator itr = net_n.set_cell.at(num_block).begin(); itr != net_n.set_cell.at(num_block).end(); itr++)
                    //the neighbor cell in from_block is free?
                    if(cell_list.at(itr->first).is_locked == false){
                        bucket_maintain(cell_list.at(itr->first), increment);}
        }
    }
    //update index_max_gain_0 and index_max_gain_1 after deleting the base cell
    for(int i = 0; i < 2; i++)
        while(true)
            if(bucket_list.at(i).at(index_max_gain[i]).empty()) {
                if(index_max_gain[i] == 0)
                    break;
                index_max_gain[i]--;
            }
            else
                break;

}

void Bipartition::bucket_maintain(cell& free_cell, int in_or_de){
    int cellgain = free_cell.cell_gain;
    free_cell.cell_gain += in_or_de ? -1: 1;     //increment or decrement the gain of the free neighbor cell
     //transfer the position of the free neighbor cell
    bucket_list.at(free_cell.block).at(free_cell.cell_gain + Pmax).emplace(free_cell.id, free_cell);
    bucket_list.at(free_cell.block).at(cellgain + Pmax).erase(free_cell.id);
    if(free_cell.cell_gain + Pmax > index_max_gain[free_cell.block])
        index_max_gain[free_cell.block] = free_cell.cell_gain + Pmax;
}
