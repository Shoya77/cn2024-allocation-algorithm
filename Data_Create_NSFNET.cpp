#include<iostream>
#include<stdio.h>
#include<vector>
#include<random>
#include <iomanip>
#include<math.h>
#include<fstream>
#include<sstream>
#include<string>

# define PI 3.14159265359

using namespace std;

vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int main(){

    int t, i, j;

    vector<vector<double>> serv_location(14,vector<double>(2));

    ofstream ofs("NSFNET_test_data5.txt");

    ofstream ofs1("NSFNET_test_location.txt");

    if(!ofs){

        cout << "Can't open output file!" << endl;

        return -1;

    }

    if(!ofs1){

        cout << "Can't open output file1!" << endl;

        return -1;

    }

    ifstream ifs("data_NSFNET/NSFNET_Serv_distance.csv");

    vector<vector<int>> serv_distance(24,vector<int>(24));

    string line;

    int s = 0;

    while (getline(ifs, line)) {

        vector<string> strvec = split(line, ',');

        for (int i=0; i<strvec.size();i++){

            serv_distance[s][i] = stoi(strvec.at(i));

        }

        s = s + 1;

    }

    for(int i = 0; i < 14; i++){

        std::cout << "serv_distance_from0" << serv_distance[0][i] << ", ";

    }

    std::cout << std::endl;

    for(int i = 0; i < 14; i++){

        std::cout << "serv_distance_from10" << serv_distance[0][i] << ", ";

    }

    std::cout << std::endl;

    serv_location[0] = {47.6062, -122.3321};
    serv_location[1] = {37.4419, -122.143};
    serv_location[2] = {32.7153, -117.1573};
    serv_location[3] = {40.7608, -111.8911};
    serv_location[4] = {40.015, -105.2706};
    serv_location[5] = {40.8, -96.667};
    serv_location[6] = {29.7633, -95.3633};
    serv_location[7] = {40.1164, -88.2434};
    serv_location[8] = {42.2776, -83.7409};
    serv_location[9] = {33.749, -84.388};
    serv_location[10] = {40.4406, -79.9959};
    serv_location[11] = {42.444, -76.5019};
    serv_location[12] = {38.9897, -76.9369};
    serv_location[13] = {40.3487, -74.6591};
    

    //vector<vector<int>> serv_distance(24,vector<int>(24));

    // serv_distance[0] = {0, 593, 672, 838, 835, 942, 914, 966, 944, 991, 973, 931, 1311, 1059, 1340, 1124, 1310, 1457, 1496, 1533, 1838, 1904, 2119, 2219};
    // serv_distance[1] = {593, 0, 79, 245, 242, 349, 321, 373, 351, 398, 380, 259, 718, 466, 747, 531, 717, 864, 903, 940, 1245, 1311, 1526, 1626};
    // serv_distance[2] = {672, 79, 0, 259, 163, 270, 242, 308, 272, 319, 301, 180, 639, 387, 668, 452, 638, 785, 824, 861, 1166, 1232, 1447, 1547};
    // serv_distance[3] = {838,245,259,0,96,192,117,128,147,194,176,421,561,309,543,327,513,660,699,736,1041,1107,1322,1422};
    // serv_distance[4] = {835,242,163,96,0,107,79,145,109,156,138,336,476,224,505,289,475,622,661,698,1003,1069,1284,1384};
    // serv_distance[5] = {942,349,270,192,107,0,75,141,105,96,133,229,369,117,398,284,368,515,554,591,896,962,1177,1277};
    // serv_distance[6] = {914,321,242,117,79,75,0,66,30,77,59,304,444,192,426,210,396,543,582,619,924,990,1205,1305};
    // serv_distance[7] = {966,373,308,128,145,141,66,0,39,86,68,370,510,258,435,219,405,552,591,628,933,999,1214,1314};
    // serv_distance[8] = {944,351,272,147,109,105,30,39,0,47,29,334,474,222,396,180,366,513,552,589,894,960,1175,1275};
    // serv_distance[9] = {991,398,319,194,156,96,77,86,47,0,37,325,465,251,404,188,374,521,560,597,902,968,1183,1283};
    // serv_distance[10] = {973,380,301,176,138,133,59,68,29,37,0,362,502,250,367,151,337,484,523,560,865,931,1146,1246};
    // serv_distance[11] = {931,259,180,421,336,229,304,370,334,325,362,0,463,211,492,513,462,609,648,685,990,1056,1271,1371};
    // serv_distance[12] = {1311,718,639,561,476,369,444,510,474,465,502,463,0,252,342,558,372,225,264,301,606,672,887,987};
    // serv_distance[13] = {1059,466,387,309,224,117,192,258,222,251,250,211,252,0,281,401,251,398,437,474,779,845,1060,1160};
    // serv_distance[14] = {1340,747,668,543,505,398,426,435,396,404,367,492,342,281,0,216,30,117,156,193,498,564,779,879};
    // serv_distance[15] = {1124,531,452,327,289,284,210,219,180,188,151,513,558,401,216,0,186,333,372,409,714,780,995,1095};
    // serv_distance[16] = {1310,717,638,513,475,368,396,405,366,374,337,462,372,251,30,186,0,147,208,223,528,594,809,909};
    // serv_distance[17] = {1457,864,785,660,622,515,543,552,513,521,484,609,225,398,117,333,147,0,39,77,381,447,662,762};
    // serv_distance[18] = {1496,903,824,699,661,554,582,591,552,560,523,648,264,437,156,372,208,39,0,37,342,411,623,723};
    // serv_distance[19] = {1533,940,861,736,698,591,619,628,589,597,560,685,301,474,193,409,223,77,37,0,305,371,586,686};
    // serv_distance[20] = {1838,1245,1166,1041,1003,896,924,933,894,902,865,990,606,779,498,714,528,381,342,305,0,66,281,381};
    // serv_distance[21] = {1904,1311,1232,1107,1069,962,990,999,960,968,931,1056,672,845,564,780,594,447,411,371,66,0,365,315};
    // serv_distance[22] = {2119,1526,1447,1322,1284,1177,1205,1214,1175,1183,1146,1271,887,1060,779,995,809,662,623,586,281,365,0,118};
    // serv_distance[23] = {2219,1626,1547,1422,1384,1277,1305,1314,1275,1283,1246,1371,987,1160,879,1095,909,762,723,686,381,315,118,0};
    

    double equator = 6378.137;

    int num_SV = 14;

    int num_TE = 2000;
    
    ofs << "V_T" << endl;

    ofs << num_TE << endl;

    ofs << "V_S" << endl;

    ofs << num_SV << endl;

    vector<int> serv_capacity(14);

    double ratio = 0.30;

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

    vector<vector<int>> te_distance(num_TE, vector<int>(14));

    srand(time(NULL));

    ofs << "E_T" << endl;

    rand() / (1.0 + RAND_MAX);

    for(t = 0; t < num_TE; t++){

        if(t < 0.20 * num_TE){

            te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(48.201821-36.524937) + 36.524937;
            te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(-87.626+124.014012) - 124.014012;

        }

        else if(0.20 * num_TE <= t && t < 0.50 * num_TE){

            te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(36.197415-29.671358) + 29.671358;
            te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(-81.590802+118.463413) - 118.463413;

        }

        else if(0.50 * num_TE <= t && t < 0.70 * num_TE){

            te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(40.429377-36.499834) + 36.499834;
            te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(-75.942348+87.396156) - 87.396156;

        }

        else{

            te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(44.64657-40.608289) + 40.608289;
            te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(-70.84305+86.297846) - 86.297846;

        }


        ofs1 << t << " " << te_location[t][0] << " " << te_location[t][1] << endl;

        for(i = 0; i < num_SV; i++){

            te_distance[t][i] = ceil(equator*acos(sin((te_location[t][0]/180)*PI)*sin((serv_location[i][0]/180)*PI)+cos((te_location[t][0]/180)*PI)*cos((serv_location[i][0]/180)*PI)*cos(((serv_location[i][1]-te_location[t][1])/180)*PI)));

            ofs << t+1 << " " << i+1 << " " << te_distance[t][i] << endl;

        }

    }

    std::cout << "Calculation complete" << std::endl;

    return 0;

}

