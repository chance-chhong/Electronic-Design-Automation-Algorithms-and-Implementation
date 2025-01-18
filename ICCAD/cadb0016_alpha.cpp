#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <math.h>   //calculate the abs of double
#include <unordered_map>
#include <set>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

/*NumTechnologies   //�X��Tech�AŪ�Ҧ�Tech�����쪺cell��T  NumTechnologies 2
                                                            Tech TA 2
                                                            LibCell N MC1 5 10 1
                                                            Pin P1 2 7
                                                            LibCell Y MC2 7 10 2
                                                            Pin P1 5 3
                                                            Pin P2 3 6
                                                            Tech TB 2
                                                            LibCell N MC1 5 15 1
                                                            Pin P1 2 11
                                                            LibCell Y MC2 7 15 2
                                                            Pin P1 2 12
                                                            Pin P2 3 3

* DieSize   //��������j�p DieSize 0 0 500 450

* TopDieMaxUtil     //�Ҧ�cell�����n�`�M�W��(Top)  TopDieMaxUtil 75
  BottomDieMaxUtil  //�Ҧ�cell�����n�`�M�W��(Bottom)  BottomDieMaxUtil 80

* TopDieRows    //�H�C����Die�A���w���Ϊ���  TopDieRows 0 0 500 10 45
* BottomDieRows //�H�C����Die�A���w���Ϊ���  BottomDieRows 0 0 500 15 30
    
* TopDieTech    //�Ҧ�cell�Τ@�άƻ�Tech(Top) TopDieTech TA
* BottomDieTech //�Ҧ�cell�Τ@�άƻ�Tech(Bottom) BottomDieTech TB
    
* TerminalSize      //Terminal�j�p TerminalSize 20 20
* TerminalSpacing   //Terminal�������άO�P��ɶ����̤p�Z�� TerminalSpacing 15
* TerminalCost      //�@��Terminal���O�� TerminalCost 40
    
* NumInstances  //input���h��cell NumInstances 2
                                  Inst C1 MC1
                                  Inst C2 MC3
* NumNets   //input���h��net NumNets 1
                             Net N1 2
                             Pin C1/P2
                             Pin C2/P1
*/

using namespace std;

struct terminal{
        int ter_id, score;
};

bool compare(terminal a, terminal b){
    return a.score < b.score;
}
enum technology{
    TA,
    TB
};
enum Die{
            top_die,
            bot_die
    };
struct Pin {
    string pinName;
    double pinLocationX;
    double pinLocationY;
};

class Tech {
    public:
        bool isMacro;
        int libCellSizeX;
        int libCellSizeY;
        int libCellArea;
        int pinCount;
        vector<Pin> pin_vec;
    private:
};
vector<unordered_map<string, Tech>> tech;

class Bipartition{
    public:
        Bipartition(){bucket_list.resize(2);}
        void readInputFile(const string& filename, const string& filename2);
    private:
        void gain_initialize();
        void FMalgorithm();
        struct net{
            int num_in_block[2] = {0};  //two block's cell num, used for F(n) and T(n)
            bool block_is_locked[2] = {false};  //once block has locked cell, the part of the net in the block do not update
            unordered_map<int, int> cell_pin;
            vector<unordered_map<int, int>> set_cell;   //two block's cell
            net(){set_cell.resize(2);}
        };
        struct cell{
            int id;
            string name;
            string libCellname;
            Tech tech;
            bool is_locked = false; //once extracted from bucket list, it is locked
            int block;  //two block:one is top, another is bot
            int cell_gain = 0;  //bucket list index
            double distance_balance = 0;    //util distance to ratio
            vector<int> set_net;    //the net connected
            bool is_checked = false;
            double locationX;
            double locationY;
        };
        double calculate_balance(int block);
        void rand_part(int net_id, int cellNum, int pinNum);
        void bucket_maintain(cell& free_cell, int in_or_de);
        void gain_maintain(int block);
        pair<int, int> gain_closet_factor(int n);
        string dir_trans(string);
        vector<net> net_list;
        vector<cell> cell_list;
        vector<vector<unordered_map<int, cell>>> bucket_list;
        vector<cell> free_cell_list;
        vector<int> list_maximum;
        enum cal{
            increment,
            decrement
        };
        
        int dieTech[2];
        int index_max_gain[2] = {0};
        int Pmax = 0;
        int area_in_block[2] = {0};
        int largest_partial_sum = 0;
        int Numsites, Height, dieArea;
        double Top_Util, Bot_Util;
        int Top_Height, Top_Numrows, Bot_Height, Bot_Numrows;
        int terminalSizeX, terminalSizeY, terminalCost, terminalSpacing;
};

int main(int argc, char** argv) {
    Bipartition bi;
    bi.readInputFile(argv[1], argv[2]);
    
    
    return 0;
}

void Bipartition::readInputFile(const string& filename, const string& filename2){
    ifstream input_file(filename);
    string input_string;    //redundant
    stringstream sstream;
    int input_num;  //redundant
    tech.resize(2);

    //kind of tech
    input_file >> input_string >> input_num;
    for(int i = 0; i < input_num; i++){
        int count;
        input_file >> input_string >> input_string >> count;
        for(int j = 0; j < count; j++){
            Tech tech;
            string isMacro, libCellName;
            input_file >> input_string >> isMacro >> libCellName >> tech.libCellSizeX >> tech.libCellSizeY >> tech.pinCount;
            tech.isMacro = isMacro == "Y" ? true : false;
            tech.libCellArea = tech.libCellSizeX * tech.libCellSizeY;
            ::tech[i][libCellName] = tech;
            ::tech[i][libCellName].pin_vec.resize(tech.pinCount + 1);
            for(int k = 1; k <= tech.pinCount; k++){
                Pin pin;
                double pinLocationX, pinLocationY;
                input_file >> input_string >> pin.pinName >> pinLocationX >> pinLocationY;
                pinLocationX -= ::tech[i][libCellName].libCellSizeX / 2.0;
                pinLocationY -= ::tech[i][libCellName].libCellSizeY / 2.0;
                pin.pinLocationX = pinLocationX;
                pin.pinLocationY = pinLocationY;
                ::tech[i][libCellName].pin_vec[k] = pin;
            }
        }
    }
    if(input_num == 1)
        tech[1] = tech[0];
    // Die size
    input_file >> input_string >> input_num >> input_num >> Numsites >> Height;
    dieArea = Numsites * Height;

    //Top util & bottom util
    input_file >> input_string >> Top_Util >> input_string >> Bot_Util;
    Top_Util /= 100;
    Bot_Util /= 100;

    //Top height and rows & bottom height and rows
    input_file >> input_string >> input_num >> input_num >> input_num >> Top_Height >>Top_Numrows;
    input_file >> input_string >> input_num >> input_num >> input_num >> Bot_Height >>Bot_Numrows;
    
    //top & bottom tech
    input_file >> input_string >> input_string;
    if(input_string == "TA")
        dieTech[top_die] = TA;
    else
        dieTech[top_die] = TB;
    input_file >> input_string >> input_string;
    if(input_string == "TA")
        dieTech[bot_die] = TA;
    else
        dieTech[bot_die] = TB; 

    //terminal size & spacing & cost
    input_file >> input_string >> terminalSizeX >> terminalSizeY;
    input_file >> input_string >> terminalSpacing;
    input_file >> input_string >> terminalCost;

    

    //instance cell
    input_file >> input_string >> input_num;
    cell_list.resize(input_num + 1);
    for(int i = 0; i < input_num; i++){
        string temp_string;
        input_file >> input_string >> input_string >> temp_string;
        cell_list[stoi(input_string.substr(1))].name = input_string;
        cell_list[stoi(input_string.substr(1))].libCellname = temp_string;
        cell_list[stoi(input_string.substr(1))].id = stoi(input_string.substr(1));
        //cout<<stoi(input_string.substr(1))<<" "<<temp_string<<endl;
    }

    srand(time(NULL));
    //net
    input_file >> input_string >> input_num;
    net_list.resize(input_num + 1);
    for(int i = 1; i <= input_num; i++){
        int temp_num;
        input_file >> input_string >> input_string >> temp_num;
        for(int j = 0; j < temp_num; j++){
            input_file >> input_string >> input_string;
            unsigned int k = 0;
            int cellNum = 0, pinNum = 0;
            while(k < input_string.size() && !isdigit(input_string[k]))
                k++;
            while(k < input_string.size() && isdigit(input_string[k]))
                cellNum = cellNum * 10 + input_string[k++] - '0';
            while(k < input_string.size() && !isdigit(input_string[k]))
                k++;
            pinNum = stoi(input_string.substr(k));
            rand_part(i, cellNum, pinNum);
            //cout<<cellNum<<" "<<pinNum<<endl;
        }
    }
    input_file.close();

    //record the max pins
    for(int i = 1; i < (int)cell_list.size(); i++)
        if((int)cell_list[i].set_net.size() > Pmax)
            Pmax = (int)cell_list[i].set_net.size();

    

    //repeat the whole process
    for(int i = 0; i < 10; i++){
        gain_initialize();
        //cout<<endl;
        FMalgorithm();
        //cout<<"top "<<(double)area_in_block[top_die]/dieArea<<endl<<"bot "<<(double)area_in_block[bot_die]/dieArea<<endl;
    }
    //for(int i = 1; i < 9;i++)
        //cout<<cell_list[i].block<<endl;
    

    //-----output-----
    ofstream output_aux_Top("netlistTop.aux");
    ofstream output_nodes_Top("netlistTop.nodes");
    ofstream output_nets_Top("netlistTop.nets");
    ofstream output_pl_Top("netlistTop.pl");
    ofstream output_scl_Top("netlistTop.scl");
    ofstream output_wts_Top("netlistTop.wts");
    ofstream output_aux_Bot("netlistBot.aux");
    ofstream output_nodes_Bot("netlistBot.nodes");
    ofstream output_nets_Bot("netlistBot.nets");
    ofstream output_pl_Bot("netlistBot.pl");
    ofstream output_scl_Bot("netlistBot.scl");
    ofstream output_wts_Bot("netlistBot.wts");
    ofstream output_final(filename2);

    //aux
    output_aux_Top << "RowBasedPlacement : netlistTop.nodes netlistTop.nets netlistTop.wts netlistTop.pl netlistTop.scl" << endl;
    output_aux_Bot << "RowBasedPlacement : netlistBot.nodes netlistBot.nets netlistBot.wts netlistBot.pl netlistBot.scl" << endl;

    //nodes
    for(unsigned int i = 0; i < 5; i++){
        output_nodes_Top << endl;
        output_nodes_Bot << endl;
    }
    vector<cell> top_nodes, bot_nodes;
    for(unsigned int i = 1; i < cell_list.size(); i++)
        if(cell_list[i].block == top_die)
            top_nodes.emplace_back(cell_list[i]);
        else
            bot_nodes.emplace_back(cell_list[i]);
    output_nodes_Top << "NumNodes : " << top_nodes.size() << endl << "NumTerminals : " << 0 << endl;
    output_nodes_Bot << "NumNodes : " << bot_nodes.size() << endl << "NumTerminals : " << 0 << endl;
    for(unsigned int i = 0; i < top_nodes.size(); i++)
        output_nodes_Top << top_nodes[i].name << " " << top_nodes[i].tech.libCellSizeX << " " << top_nodes[i].tech.libCellSizeY << endl;
    for(unsigned int i = 0; i < bot_nodes.size(); i++)
        output_nodes_Bot << bot_nodes[i].name << " " << bot_nodes[i].tech.libCellSizeX << " " << bot_nodes[i].tech.libCellSizeY << endl;
    
    //nets
    for(unsigned int i = 0; i < 5; i++){
        output_nets_Top << endl;
        output_nets_Bot << endl;
    }
    vector<pair<int, vector<int>>> top_nets, bot_nets;
    set<int> term;
    int top_pins = 0, bot_pins = 0;
    for(unsigned int i = 1; i < net_list.size(); i++){
        vector<int> temp;
        int temp_pins = 0;
        bool top = false, bot = false;
        for(const auto& n : net_list[i].set_cell[top_die]){
            temp.emplace_back(n.first);
            temp_pins++;
        }
        if(!temp.empty()){
            top_nets.emplace_back(make_pair(i, temp));
            top_pins += temp_pins;
            top = true;
        }     
        temp.clear();
        temp_pins = 0;
        for(const auto& n : net_list[i].set_cell[bot_die]){
            temp.emplace_back(n.first);
            temp_pins++;
        }
        if(!temp.empty()){
            bot_nets.emplace_back(make_pair(i, temp));
            bot_pins += temp_pins;
            bot = true;
        }
        if(top && bot)
            term.insert(i);
    }
    output_nets_Top << "NumNets : " << top_nets.size() << endl;
    output_nets_Top << "NumPins : " << top_pins << endl;
    output_nets_Bot << "NumNets : " << bot_nets.size() << endl;
    output_nets_Bot << "NumPins : " << bot_pins << endl;
    
    for(unsigned int i = 0; i < top_nets.size(); i++){
        output_nets_Top << "NetDegree : " << top_nets[i].second.size() << " net" << endl;
        for(unsigned int j = 0; j < top_nets[i].second.size(); j++) {
            Pin pin = cell_list[top_nets[i].second[j]].tech.pin_vec[net_list[top_nets[i].first].cell_pin[top_nets[i].second[j]]];
            output_nets_Top << cell_list[top_nets[i].second[j]].name << " B : " <<  pin.pinLocationX << " " << pin.pinLocationY << endl;
        }  
    }
    for(unsigned int i = 0; i < bot_nets.size(); i++){
        output_nets_Bot << "NetDegree : " << bot_nets[i].second.size() << " net" << endl;
        for(unsigned int j = 0; j < bot_nets[i].second.size(); j++) {
            Pin pin = cell_list[bot_nets[i].second[j]].tech.pin_vec[net_list[bot_nets[i].first].cell_pin[bot_nets[i].second[j]]];
            output_nets_Bot << cell_list[bot_nets[i].second[j]].name << " B : " <<  pin.pinLocationX << " " << pin.pinLocationY << endl;
        }  
    }
    
    //pl
    for(int i = 0; i < 6; i++){
        output_pl_Top << endl;
        output_pl_Bot << endl;
    }
    int side_top = sqrt(top_nodes.size());
    int start_x = Numsites / 2 - side_top, start_y = Top_Height * Top_Numrows / 2 - side_top;
    int temp_x = start_x, temp_y = start_y;
    for(unsigned int i = 0; i < top_nodes.size(); i++){
        output_pl_Top << top_nodes[i].name << " " << temp_x << " " << temp_y << " : N" << endl;
        temp_x++;
        if(i != 0 && i % side_top == 0){
            temp_x = start_x;
            temp_y++;
        }
    }
    int side_bot = sqrt(bot_nodes.size());
    start_x = Numsites / 2 - side_bot;
    start_y = Top_Height * Top_Numrows / 2 - side_top;
    temp_x = start_x;
    temp_y = start_y;
    for(unsigned int i = 0; i < bot_nodes.size(); i++){
        output_pl_Bot << bot_nodes[i].name << " " << temp_x << " " << temp_y << " : N" << endl;
        temp_x++;
        if(i != 0 && i % side_bot == 0){
            temp_x = start_x;
            temp_y++;
        }
    }

    //scl
    for(int i = 0; i < 6; i++){
        output_scl_Top << endl;
        output_scl_Bot << endl;
    }
    output_scl_Top << "Numrows : " << Top_Numrows << endl << endl;
    output_scl_Bot << "Numrows : " << Bot_Numrows << endl << endl;
    
    for(int i = 0; i < Top_Numrows; i++){
        output_scl_Top << "CoreRow Horizontal" << endl
        << "Coordinate : " << i * Top_Height << endl
        << "Height : " << Top_Height << endl
        << "Sitewidth : " << 1 << endl
        << "Sitespacing : " << 1 << endl
        << "Siteorient : N" << endl
        << "Sitesymmetry : N" << endl
        << "SubrowOrigin : 0 Numsites : " << Numsites << endl
        << "End" << endl;
    }
    for(int i = 0; i < Bot_Numrows; i++){
        output_scl_Bot << "CoreRow Horizontal" << endl
        << "Coordinate : " << i * Bot_Height << endl
        << "Height : " << Bot_Height << endl
        << "Sitewidth : " << 1 << endl
        << "Sitespacing : " << 1 << endl
        << "Siteorient : N" << endl
        << "Sitesymmetry : N" << endl
        << "SubrowOrigin : 0 Numsites : " << Numsites << endl
        << "End" << endl;
    }

    //wts
    for(int i = 0; i < 5; i++){
        output_wts_Top << endl;
        output_wts_Bot << endl;
    }
    for(unsigned int i = 0; i < top_nodes.size(); i++)
        output_wts_Top << top_nodes[i].name << " " << top_nodes[i].tech.libCellArea << endl;
    for(unsigned int i = 0; i < bot_nodes.size(); i++)
        output_wts_Bot << bot_nodes[i].name << " " << bot_nodes[i].tech.libCellArea << endl;
    
    string cmd1 = "chmod 755 ntuplace3";
    system(cmd1.c_str());
    string cmd2 = "./ntuplace3 -aux netlistTop.aux -MRT";
    system(cmd2.c_str());
    string cmd3 = "./ntuplace3 -aux netlistBot.aux -MRT";
    system(cmd3.c_str());
    ifstream input_top_pl("netlistTop.ntup.pl");
    ifstream input_bot_pl("netlistBot.ntup.pl");
            
    //top placement
    output_final << "TopDiePlacement " << top_nodes.size() << endl;
    getline(input_top_pl, input_string);
    getline(input_top_pl, input_string);
    for(unsigned int i = 0; i < top_nodes.size(); i++){
        int x, y;
        string direction;
        input_top_pl >> input_string >> x >> y >> direction >> direction;
        output_final << "Inst" << " " << input_string << " " << x << " " << y << " " << dir_trans(direction) << endl;
        cell_list[stoi(input_string.substr(1))].locationX = x + cell_list[stoi(input_string.substr(1))].tech.libCellSizeX / 2;
        cell_list[stoi(input_string.substr(1))].locationY = y + cell_list[stoi(input_string.substr(1))].tech.libCellSizeY / 2;
    }

    output_final << endl;

    //bot placement
    output_final << "BottomDiePlacement " << bot_nodes.size() << endl;
    getline(input_bot_pl, input_string);
    getline(input_bot_pl, input_string);
    for(unsigned int i = 0; i < bot_nodes.size(); i++){
        int x, y;
        string direction;
        input_bot_pl >> input_string >> x >> y >> direction >> direction;
        output_final << "Inst" << " " << input_string << " " << x << " " << y << " " << dir_trans(direction) << endl;
        cell_list[stoi(input_string.substr(1))].locationX = x + cell_list[stoi(input_string.substr(1))].tech.libCellSizeX / 2;
        cell_list[stoi(input_string.substr(1))].locationY = y + cell_list[stoi(input_string.substr(1))].tech.libCellSizeY / 2;
    }

    //terminal placement
    
    vector<terminal> term_vec;
    int core_x = 0, core_y = 0;
    for(const auto& i : term){
        double aver_x = 0, aver_y = 0;
        for(const auto& j : net_list[i].cell_pin){
            aver_x += cell_list[j.first].locationX + cell_list[j.first].tech.pin_vec[j.second].pinLocationX;
            aver_y += cell_list[j.first].locationY + cell_list[j.first].tech.pin_vec[j.second].pinLocationY;
        }
        aver_x /= net_list[i].cell_pin.size();
        aver_y /= net_list[i].cell_pin.size();
        terminal t;
        t.score = aver_x + aver_y * 10;
        t.ter_id = i;
        term_vec.emplace_back(t);
        core_x += aver_x;
        core_y += aver_y;
    }
    sort(term_vec.begin(), term_vec.end(), compare);
    core_x /= term.size();
    core_y /= term.size();
    /*
    int row, column;
    row = gain_closet_factor(term.size()).first;
    column = gain_closet_factor(term.size()).second;
    cout<<row<<" "<<column<<" "<<term.size()<<endl;*/
    output_final << endl;
    output_final << "NumTerminals " << term.size() << endl;

    //terminal placement initial position
    int side_length = sqrt(term.size());
    int side_height = term.size() / side_length + 1;
    if(side_length % 2 == 0){
        if(core_x - (side_length / 2 * (terminalSpacing + terminalSizeX) + terminalSpacing / 2 + 1) <= 0)
            start_x = terminalSpacing + terminalSizeX / 2 + 1;
        else if(core_x + (side_length / 2 * (terminalSpacing + terminalSizeX) + terminalSpacing / 2 + 1) >= Numsites)
            start_x = Numsites - side_length * (terminalSizeX + terminalSpacing);
        else
            start_x = core_x - (side_length / 2 * (terminalSpacing + terminalSizeX) + terminalSpacing / 2 + 1) + terminalSizeX / 2;
    }
    else{
        if(core_x - (side_length / 2 * (terminalSpacing + terminalSizeX) + terminalSizeX / 2 + 1) <= 0)
            start_x = terminalSpacing + terminalSizeX / 2 + 1;
        else if(core_x + (side_length / 2 * (terminalSpacing + terminalSizeX) + terminalSizeX / 2 + 1) >= Numsites)
            start_x = Numsites - side_length * (terminalSizeX + terminalSpacing);
        else
            start_x = core_x - (side_length / 2 * (terminalSpacing + terminalSizeX) - terminalSpacing);
    }
    if(side_height % 2 == 0){
        if(core_y - (side_height / 2 * (terminalSpacing + terminalSizeY) + terminalSpacing / 2) <= 0)
            start_y = terminalSpacing + terminalSizeY / 2 + 1;
        else if(core_y + (side_height / 2 * (terminalSpacing + terminalSizeY) + terminalSpacing / 2) >= Height){
            start_y = Height - side_height * (terminalSizeY + terminalSpacing);
            if(start_y <= terminalSizeY / 2 + terminalSpacing + 1)
                start_y = terminalSizeY / 2 + terminalSpacing + 1;
        }
        else
            start_y = core_y - (side_height / 2 * (terminalSpacing + terminalSizeY) + terminalSpacing / 2 + 1) + terminalSizeY / 2;
    }
    else{
        if(core_y - (side_height / 2 * (terminalSpacing + terminalSizeY) + terminalSizeY / 2 + 1) <= 0)
            start_y = terminalSpacing + terminalSizeY / 2 + 1;
        else if(core_y + (side_height / 2 * (terminalSpacing + terminalSizeY) + terminalSizeY / 2 + 1) >= Height){
            start_y = Height - side_height * (terminalSizeY + terminalSpacing);
            if(start_y <= terminalSizeY / 2 + terminalSpacing + 1)
                start_y = terminalSizeY / 2 + terminalSpacing + 1;
        }
        else
            start_y = core_y - (side_height / 2 * (terminalSpacing + terminalSizeY) - terminalSpacing) ;
    }
    temp_x = start_x;
    temp_y = start_y;
    for(unsigned int i = 0; i < term.size(); i++){
        output_final << "Terminal N" << term_vec[i].ter_id << " " << temp_x << " " << temp_y << endl;
        temp_x += terminalSizeX + terminalSpacing;
        if(i != 0 && i % side_length == 0){
            temp_x = start_x;
            temp_y += terminalSizeY + terminalSpacing;
        }
    }

    output_aux_Top.close();
    output_nodes_Top.close();
    output_nets_Top.close();
    output_pl_Top.close();
    output_scl_Top.close();
    output_wts_Top.close();
    output_aux_Bot.close();
    output_nodes_Bot.close();
    output_nets_Bot.close();
    output_pl_Bot.close();
    output_scl_Bot.close();
    output_wts_Bot.close();
    output_final.close();
 

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
    /*for(unsigned int i = 1; i < cell_list.size(); i++)
        cout<<cell_list[i].cell_gain<<endl;*/
}

double Bipartition::calculate_balance(int block){
    int id_base, area;
    id_base = bucket_list.at(block).at(index_max_gain[block]).begin()->first;    //set the max_gain cell as the base cell
    area = tech[!block][cell_list[id_base].libCellname].libCellArea;    //area of cells in block changes because of cell transfer
    //cout<<block<<" "<<(double)(area_in_block[block])/dieArea<<endl;
    return (double)(area_in_block[!block] + area)/dieArea;
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
        net_list.at(i).block_is_locked[top_die] = false;
        net_list.at(i).block_is_locked[bot_die] = false;
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
        if(index_max_gain[top_die] > index_max_gain[bot_die]) {
            if(calculate_balance(top_die) > Bot_Util)
                gain_maintain(bot_die);
            else
                gain_maintain(top_die);
        }else if(index_max_gain[top_die] < index_max_gain[bot_die]) {
            if(calculate_balance(bot_die) > Top_Util)
                gain_maintain(top_die);
            else
                gain_maintain(bot_die);
        }else {
            if(calculate_balance(top_die) > calculate_balance(bot_die))
                gain_maintain(bot_die);
            else
                gain_maintain(top_die);
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
        if(minimum > free_cell_list.at(list_maximum.at(i)).distance_balance){
            minimum = free_cell_list.at(list_maximum.at(i)).distance_balance;
            index_minimum = list_maximum.at(i);
        }
    //retransfer the remaining cells
    for(unsigned int i = index_minimum + 1; i < free_cell_list.size(); i++){
        cell_list.at(free_cell_list.at(i).id).block = !cell_list.at(free_cell_list.at(i).id).block;
        area_in_block[!cell_list.at(free_cell_list.at(i).id).block] -= cell_list.at(free_cell_list.at(i).id).tech.libCellArea;
        cell_list.at(free_cell_list.at(i).id).tech = tech[dieTech[cell_list.at(free_cell_list.at(i).id).block]][cell_list.at(free_cell_list.at(i).id).libCellname]; //tech retransfer
        area_in_block[cell_list.at(free_cell_list.at(i).id).block] += cell_list.at(free_cell_list.at(i).id).tech.libCellArea;
        
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
    //handle the base cell in bucket according to block
    int id_base;
    id_base = bucket_list.at(num_block).at(index_max_gain[num_block]).begin()->first;    //set the max_gain cell as the base cell
    area_in_block[num_block] -= cell_list[id_base].tech.libCellArea;    //area of cells in block changes because of cell transfer
    cell_list[id_base].tech = tech[dieTech[!num_block]][cell_list[id_base].libCellname];     //tech transfer
    area_in_block[!num_block] += cell_list[id_base].tech.libCellArea;    //area of cells in block changes because of cell transfer
    cell_list.at(id_base).is_locked = true;     //lock the base cell, so its cell_gain would never change
    bucket_list.at(num_block).at(index_max_gain[num_block]).erase(bucket_list.at(num_block).at(index_max_gain[num_block]).begin());     //delete the base cell from bucket list
    cell_list.at(id_base).block = !cell_list.at(id_base).block;     //transfer the cell to the other block
    cell_list.at(id_base).distance_balance = fabs((double)(area_in_block[num_block] + cell_list[id_base].tech.libCellArea)/dieArea - 0.5);  //store the balance distance
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
    index_max_gain[top_die] = 2 * Pmax;
    index_max_gain[bot_die] = 2 * Pmax;
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
    /*if(free_cell.cell_gain + Pmax > index_max_gain[free_cell.block])
        index_max_gain[free_cell.block] = free_cell.cell_gain + Pmax;*/
}

string Bipartition::dir_trans(string dir){
    if(dir == "N" || dir == "FN")
        return "R0";
    else if(dir == "W" || dir == "FW")
        return "R90";
    else if(dir == "S" || dir == "FS")
        return "R180";
    else if(dir == "E" || dir == "FE")
        return "R270";
    return "";
}

void Bipartition::rand_part(int net_id, int cellNum, int pinNum){
    
    if(!cell_list[cellNum].is_checked){
        int rand_num = rand() % 2;
        int block;
        if(area_in_block[top_die] == area_in_block[bot_die])
            block = rand_num;
        else if(area_in_block[top_die] > area_in_block[bot_die])
            block = bot_die;
        else
            block = top_die;

        cell_list[cellNum].tech = tech[dieTech[block]][cell_list[cellNum].libCellname];
        cell_list[cellNum].block = block;
        //cout<<cellNum <<" "<<cell_list[cellNum].block<<endl;
        area_in_block[block] += cell_list[cellNum].tech.libCellArea;
        cell_list[cellNum].is_checked = true;
    }
    cell_list[cellNum].set_net.emplace_back(net_id);
    net_list[net_id].set_cell[cell_list[cellNum].block].emplace(cellNum, cellNum);
    net_list[net_id].num_in_block[cell_list[cellNum].block]++;
    net_list[net_id].cell_pin[cellNum] = pinNum;
}

pair<int, int> Bipartition::gain_closet_factor(int n){
    int integral = sqrt(n);
    if(n % integral == 0)
        return make_pair(integral, n/integral);
    else{
        int flag;
        int low = pow(integral, 2);
        int high = pow(integral + 1, 2);
        if((n - low) >= (high - n))
            flag = integral;
        else
            flag = integral - 1;
        int i;
        for(i = flag; i > 0; i--)
            if(n % i == 0)
                break;
        return make_pair(i, n/i);
    }
}