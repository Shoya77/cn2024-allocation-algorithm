#include<iostream>
#include<stdio.h>
#include<vector>
#include<random>
#include <iomanip>
#include<math.h>
#include<fstream>

# define PI 3.14159265359

using namespace std;

int main(){

    int t, i, j;

    vector<vector<double>> serv_location(8,vector<double>(2));

    ofstream ofs("Kanto_test_data5.txt");

    ofstream ofs1("Kanto_test_location.txt");

    if(!ofs){

        cout << "Can't open output file!" << endl;

        return -1;

    }

    if(!ofs1){

        cout << "Can't open output file1!" << endl;

        return -1;

    }

    // serv_location[0][0] = 55.676;
    // serv_location[0][1] = 12.5683;
    // serv_location[1][0] = 51.5073;
    // serv_location[1][1] = -0.1277;
    // serv_location[2][0] = 52.3702;
    // serv_location[2][1] = 4.8951;
    // serv_location[3][0] = 50.0755;
    // serv_location[3][1] = 14.4378;
    // serv_location[4][0] = 48.8566;
    // serv_location[4][1] = 2.3522;
    // serv_location[5][0] = 49.8152;
    // serv_location[5][1] = 6.1295;
    // serv_location[6][0] = 52.52;
    // serv_location[6][1] = 13.4049;
    // serv_location[7][0] = 50.8503;
    // serv_location[7][1] = 4.3517;
    // serv_location[8][0] = 47.3768;
    // serv_location[8][1] = 8.5416;
    // serv_location[9][0] = 48.2081;
    // serv_location[9][1] = 16.3738;
    // serv_location[10][0] = 45.4654;
    // serv_location[10][1] = 9.1859;

    serv_location[0] = {36.3659, 140.4714};
    serv_location[1] = {36.5551, 139.8826};
    serv_location[2] = {36.3895, 139.0634};
    serv_location[3] = {35.9086, 139.6248};
    serv_location[4] = {35.6074, 140.1065};
    serv_location[5] = {35.6762, 139.6503};
    serv_location[6] = {35.6664, 139.316};
    serv_location[7] = {35.4437, 139.638};
    

    vector<vector<int>> serv_distance(8,vector<int>(8));

    serv_distance[0] = {0, 57, 133, 92, 91, 118, 149, 144};
    serv_distance[1] = {57, 0, 76, 76, 131, 102, 133, 128};
    serv_distance[2] = {133, 76, 0, 74, 129, 100, 84, 123};
    serv_distance[3] = {92, 76, 74, 0, 55, 26, 57, 52};
    serv_distance[4] = {91, 131, 129, 55, 0, 42, 73, 68};
    serv_distance[5] = {118, 102, 100, 26, 42, 0, 31, 26};
    serv_distance[6] = {149, 133, 84, 57, 73, 31, 0, 39};
    serv_distance[7] = {144, 128, 123, 52, 68, 26, 39, 0};
    
    double equator = 6378.137;

    int num_SV = 8;

    int num_TE = 1000;
    
    ofs << "V_T" << endl;

    ofs << num_TE << endl;

    ofs << "V_S" << endl;

    ofs << num_SV << endl;

    vector<int> serv_capacity(8);

    double ratio = 0.70;

    int each_capacity = (num_TE / ratio) / num_SV;

    ofs << "M_i" << endl;

    for(i = 0; i < num_SV; i++){

        ofs << i+1 << " " << each_capacity << endl;

    }

    ofs << "E_S" << endl;

    for(i = 0; i < num_SV; i++){
        for(j = 0; j < num_SV; j++){

            ofs << i+1 << " " << j+1 << " " << serv_distance[i][j] << endl;

        }
    }

    // std::random_device rd;
    // std::default_random_engine eng(rd());
    // std::uniform_real_distribution<double> distr(0, 1);

    vector<vector<double>> te_location(num_TE,vector<double>(2));

    vector<vector<int>> te_distance(num_TE, vector<int>(8));

    srand(time(NULL));

    ofs << "E_T" << endl;

    rand() / (1.0 + RAND_MAX);

    for(t = 0; t < num_TE; t++){

        te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(36.8-35.2) + 35.2;
        te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(140.8-138.8) + 138.8;

        ofs1 << t << " " << te_location[t][0] << " " << te_location[t][1] << endl;

        for(i = 0; i < num_SV; i++){

            te_distance[t][i] = ceil(equator*acos(sin((te_location[t][0]/180)*PI)*sin((serv_location[i][0]/180)*PI)+cos((te_location[t][0]/180)*PI)*cos((serv_location[i][0]/180)*PI)*cos(((serv_location[i][1]-te_location[t][1])/180)*PI)));

            ofs << t+1 << " " << i+1 << " " << te_distance[t][i] << endl;

        }

    }

    std::cout << "Calculation complete" << std::endl;

    return 0;

}

