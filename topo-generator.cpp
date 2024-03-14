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

int main(int argc, char* argv[]){

    int t, i, j, num_SV, num_TE, size_geo_SV, size_net_SV;
    double ratio;
    string input_geo_file, input_net_file, input_area_file, output_file_prefix;
    unsigned seed;

    if(argc == 9){
        input_geo_file = argv[1];
        input_net_file = argv[2];
        input_area_file = argv[3];
        output_file_prefix = argv[4];
        num_SV = stoi(argv[5]);
        num_TE = stoi(argv[6]);
        ratio = stod(argv[7]);
        seed = stoi(argv[8]);
    } else {
        input_geo_file = "models/NSFNET_geo.csv";
        input_net_file = "models/NSFNET_net.csv";
        input_area_file = "models/NSFNET_area.csv";
        output_file_prefix = "data/nsfnet";
        num_SV = 1;
        num_TE = 10;
        ratio = 0.3;
        seed = 20240308;
    }
      

    string output_file = output_file_prefix + to_string(num_SV) + "-" + to_string(num_TE) + "-" + to_string(ratio) + "-" + to_string(seed) + ".txt";
       
    ifstream ifs_geo(input_geo_file);
    ifstream ifs_net(input_net_file);
    ifstream ifs_area(input_area_file);
    ofstream ofs(output_file);

    if(!ifs_geo or !ifs_net or !ifs_area or !ofs){

        cout << "Can't open argument files!" << endl;
        cout << "Please, check README to know how to execute it." << endl;

        return -1;

    }

    string line;

    int s = 0;

    std::string str_sv;
    ifs_geo >> str_sv;
    size_geo_SV = stoi(str_sv);
    size_net_SV = size_geo_SV * size_geo_SV;

    vector<vector<double>> serv_location(size_geo_SV,vector<double>(2));
    vector<vector<int>> serv_distance(size_net_SV,vector<int>(size_net_SV));

    while (getline(ifs_net, line)) {

        vector<string> strvec = split(line, ',');

        for (int i=0; i<strvec.size();i++){

            serv_distance[s][i] = stoi(strvec.at(i));

        }

        s = s + 1;

    }

    std::string str_geo;

    for(int i = 0; i < size_geo_SV; i++){
        ifs_geo >> str_geo;
        vector<string> str_geo_vec = split(str_geo, ',');
        string str_geo_lat = str_geo_vec.at(0);
        string str_geo_lon = str_geo_vec.at(1);
        serv_location[i] = {stod(str_geo_lat), stod(str_geo_lon)};
    }


    double equator = 6378.137;

    ofs << "V_T" << endl;

    ofs << num_TE << endl;

    ofs << "V_S" << endl;

    ofs << num_SV << endl;

    vector<int> serv_capacity(size_geo_SV);

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

    vector<vector<double>> te_location(num_TE,vector<double>(2));

    vector<vector<int>> te_distance(num_TE, vector<int>(size_geo_SV));

    srand(seed);

    ofs << "E_T" << endl;

    rand() / (1.0 + RAND_MAX);

    std::string str_area;
    double area_density = 0.0;
    double area_lat;
    double area_lat_tra;
    double area_lon;
    double area_lon_tra;

    for(t = 0; t < num_TE; t++){

        if(t > area_density * num_TE){
            ifs_area >> str_area;
            vector<string> str_area_vec = split(str_area, ',');
            area_density += stod(str_area_vec.at(0));
            area_lat = stod(str_area_vec.at(1));
            area_lat_tra = stod(str_area_vec.at(2));
            area_lon = stod(str_area_vec.at(3));
            area_lon_tra = stod(str_area_vec.at(4));
        }

        te_location[t][0] = (rand() / (1.0 + RAND_MAX))*(area_lat - area_lat_tra) + area_lat_tra;
        te_location[t][1] = (rand() / (1.0 + RAND_MAX))*(area_lon + area_lon_tra) - area_lon_tra;

        for(i = 0; i < num_SV; i++){

            te_distance[t][i] = ceil(equator*acos(sin((te_location[t][0]/180)*PI)*sin((serv_location[i][0]/180)*PI)+cos((te_location[t][0]/180)*PI)*cos((serv_location[i][0]/180)*PI)*cos(((serv_location[i][1]-te_location[t][1])/180)*PI)));

            ofs << t+1 << " " << i+1 << " " << te_distance[t][i] << endl;

        }

    }

    std::cout << "data file create at " << '"' << output_file << '"' << std::endl;

    return 0;

}

