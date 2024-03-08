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

    vector<vector<double>> serv_location(11,vector<double>(2));

    ofstream ofs("COST239_test_data5.txt");

    ofstream ofs1("COST239_test_location.txt");

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

    serv_location[0] = {55.676,	12.5683};
    serv_location[1] = {51.5073, -0.1277};
    serv_location[2] = {52.3702, 4.8951};
    serv_location[3] = {50.0755, 14.4378};
    serv_location[4] = {48.8566, 2.3522};
    serv_location[5] = {49.8152, 6.1295};
    serv_location[6] = {52.52, 13.4049};
    serv_location[7] = {50.8503, 4.3517};
    serv_location[8] = {47.3768, 8.5416};
    serv_location[9] = {48.2081, 16.3738};
    serv_location[10] = {45.4654, 9.1859};

    vector<vector<int>> serv_distance(11,vector<int>(11));

    serv_distance[0] = {0, 957,	622, 636, 1061, 920, 356, 796, 1163, 881, 1382};
    serv_distance[1] = {957, 0, 358, 1088, 344, 492, 1223, 321, 817, 1340, 984};
    serv_distance[2] = {622, 358, 0, 894, 439, 298, 978, 174, 623, 1146, 842};
    serv_distance[3] = {636, 1088, 894, 0, 891, 596, 282, 767, 527, 252, 746};
    serv_distance[4] = {1061, 344, 439, 891, 0, 295, 879, 265, 489, 1082, 640};
    serv_distance[5] = {920, 492, 298, 596, 295, 0, 878, 171, 325, 848, 544};
    serv_distance[6] = {356, 1223, 978, 282, 879, 878, 0, 1049, 809, 525, 1028};
    serv_distance[7] = {796, 321, 174, 767, 265, 171, 1049, 0, 496, 1019, 699};
    serv_distance[8] = {1163, 817, 623, 527, 489, 325, 809, 496, 0, 593, 219};
    serv_distance[9] = {881, 1340, 1146, 252, 1082, 848, 525, 1019, 593, 0, 627};
    serv_distance[10] = {1382, 984, 842, 746, 640, 544, 1028, 715, 219, 627, 0};

    double equator = 6378.137;

    int num_SV = 11;

    int num_TE = 1000;
    
    ofs << "V_T" << endl;

    ofs << num_TE << endl;

    ofs << "V_S" << endl;

    ofs << num_SV << endl;

    vector<int> serv_capacity(11);

    double ratio = 0.91;

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

    vector<vector<int>> te_distance(num_TE, vector<int>(11));

    srand(time(NULL));

    ofs << "E_T" << endl;

    rand() / (1.0 + RAND_MAX);

    for(t = 0; t < num_TE; t++){

        te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(57-44) + 44;
        te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(19+2) - 2;

        ofs1 << t << " " << te_location[t][0] << " " << te_location[t][1] << endl;

        for(i = 0; i < num_SV; i++){

            te_distance[t][i] = ceil(equator*acos(sin((te_location[t][0]/180)*PI)*sin((serv_location[i][0]/180)*PI)+cos((te_location[t][0]/180)*PI)*cos((serv_location[i][0]/180)*PI)*cos(((serv_location[i][1]-te_location[t][1])/180)*PI)));

            ofs << t+1 << " " << i+1 << " " << te_distance[t][i] << endl;

        }

    }

    std::cout << "Calculation complete" << std::endl;

    return 0;

}

