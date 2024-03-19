#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<chrono>
#include<bits/stdc++.h>

using namespace std;

#define NIL 0
#define INF INT_MAX

#define SIZE_OF_ARRAY(Usage) (sizeof(Usage)/sizeof(Usage[0]))

struct Server{

   int index;
   int M_i;

};

struct Edge{

    int index;
    int origin_index;
    int s_index;
    int delay;

};

bool cmp_edge( const struct Edge& left, const struct Edge& right){

    return left.delay < right.delay;

}

bool cmp_index( const struct Server& left, const struct Server& right){

    return left.index < right.index;

}

// select set of candidate usage servers {Usage}

void select_usage(vector<int>& Usage, vector<Edge> const& edge, int num_SV, int j, int i){

    int n;

    int Usage_Serv;

    for(n=0;n<=i;n++){

        Usage_Serv = edge[n].index - (j*num_SV);

        Usage[n] = Usage_Serv;

    }

}

/*
void ToE2index(int *i_2_k, int *i_2_l, int i, int sum_M, Edge e, Server *usage_list_server){

    int before_sum = 0;
     
     (*i_2_k) = e.index / sum_M;

    for(int k=0;k<=i;k++){

        if(e.s_index == usage_list_server[k].index){

            for(int l=0;l<k;l++){
               before_sum += usage_list_server[l].M_i;
            }

            k = i+1;

        }

    }

    (*i_2_l) = before_sum;

}
*/

class BipGraph
{

    int m, n;

    list<int> *adj;

    int *pairU, *pairV, *dist;

public:
    BipGraph(int m, int n, int *pairU, int *pairV);
    void addEdge(int u, int v);

    bool bfs(int m, int n, int *pairU, int *pairV);

    bool dfs(int u, int *pairU, int *pairV);

    int hopcroftKarp(int m, int n, int *pairU, int *pairV);

};

int BipGraph::hopcroftKarp(int m, int n, int *pairU, int *pairV)
{

    this->m = m;

    this->n = n;

    this->pairU = pairU;

    this->pairV = pairV;

    dist = new int[m+1];

    int result = 0;

    while(bfs(m, n, this->pairU, this->pairV))
    {

        for(int u=1; u<=this->m; u++){

            if(this->pairU[u]==NIL && dfs(u, this->pairU, this->pairV)){

                result++;

            }

        }

    }
    
    return result;

}

bool BipGraph::bfs(int m, int n, int *pairU, int *pairV)
{

    queue<int> Q;

    for(int u=1; u<=m; u++)
    {
        if(pairU[u]==NIL)
        {
            dist[u] = 0;
            Q.push(u);
        }else{
            dist[u] = INF;
        }

    }

    dist[NIL] = INF;

    while(!Q.empty())
    {

        int u = Q.front();
        
        Q.pop();

        /*
        std::cout << "this->m : " << m;

        std::cout << "this->n : " << n;  

        std::cout << endl;
        */

        if(dist[u] < dist[NIL])
        {

            list<int>::iterator i;

            for(i=adj[u].begin(); i!=adj[u].end(); ++i)
            {


                int v = *i;

                if(dist[pairV[v]]==INF)
                {

                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);

                }

            }

        }
    }

    return (dist[NIL] != INF);

}

bool BipGraph::dfs(int u, int *pairU, int *pairV)
{
    if(u != NIL)
    {

        list<int>::iterator i;

        for(i=adj[u].begin(); i!=adj[u].end(); ++i)
        {

            int v = *i;

            if(dist[pairV[v]] == dist[u]+1)
            {

                if(dfs(pairV[v], pairU, pairV) == true)
                {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }

        dist[u] = INF;
        return false;

    }

    return true;

}

BipGraph::BipGraph(int m, int n, int *pairU, int *pairV)
{
    this->m = m;
    this->m = n;
    this->pairU = pairU;
    this->pairV = pairV;
    adj = new list<int>[m+1];
}

void BipGraph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}


int main(int argc, char* argv[]){
   
   int i, j, k, l;
   int i_1, i_2;
   int b;
   int i_2_k, i_2_l;
   int gadd;
   int num_TE;
   int num_SV;
   int origin_index;
   int s_index;
   int SUM_M = 0;
   int sum_M = 0;
   int match = 0;
   int real_match_sindex;

   int first_find_flag = 0;

   int do_try = 0;

   int delay_max_db;
   int delay_max_te;
   int T_delay = INF;      

   int prev_T_delay;
   int T_delay_pre;

   int *pairU;

   string input_data_file;


    if(argc == 2){
        input_data_file = argv[1];
    } else {
        input_data_file = "data/nsfnet.txt";
    }

   std::ifstream ifs(input_data_file);

   if(!ifs){

     std::cout << "Can't open data input file: " << input_data_file << std::endl;
     return -1;

   }

   std::string str;

   ifs >> str;

   ifs >> num_TE;

   ifs >> str;

   ifs >> num_SV;

   std::cout << "num_TE " << num_TE << "num_SV " << num_SV << endl;
   
   ifs >> str;
   
   vector<Server> list_server(num_SV);

   vector<Server> list_server_copy(num_SV);

   for(i=0;i<num_SV;i++){
     
      ifs >> k >> list_server[i].M_i;
      list_server[i].index = i;
      SUM_M += list_server[i].M_i;

   }
   
   std::cout << "Server Info : " << endl;

   for(i=0;i<num_SV;i++){

      std::cout << list_server[i].index << ", " << list_server[i].M_i << endl;

   }
   

   vector<vector<Edge>> list_edge_s(num_SV, vector<Edge>(num_SV));   // list_edge_s 2D

   vector<Edge> list_edge_t(num_TE*num_SV);   // list_edge_t 1D
 
   
   ifs >> str;
   
   std::cout << "Server-Server links" << endl;

   for(i=0;i<num_SV;i++){
     for(j=0;j<num_SV;j++){

        ifs >> k >> l >> list_edge_s[i][j].delay;
        list_edge_s[i][j].index = (k-1)*num_SV + (l-1);
     
     }
   }
   
   /*
   for(i=0;i<num_SV;i++){
     for(j=0;j<num_SV;j++){

        std::cout << list_edge_s[i][j].index << ", " << list_edge_s[i][j].delay << endl;
     
     }
   }
   */

   ifs >> str;

   std::cout << "TE-Server links" << endl;

   
   for(i=0;i<num_TE*num_SV;i++){
      
      ifs >> k >> l >> list_edge_t[i].delay;
      list_edge_t[i].index = i;

   }
   
   /*
   for(i=0;i<num_TE*num_SV;i++){

      std::cout << list_edge_t[i].index << " " << list_edge_t[i].delay << endl;

   }
   */
   
   
   vector<int> x1(num_TE);

   vector<int> x1_0(num_TE);
   

   vector<int> y(num_SV);

   vector<int> y_0(num_SV);

   //vector<int> find_num(num_TE, -1);
   
   //std::cout << y_0[0] << ", " << y_0[1] << ", " << y_0[2] << endl;

   int z = 0;

   list_server_copy = list_server;


   vector<Edge> match_edge(num_TE);

   vector<int> match_edge_delay(num_TE);

   auto start = chrono::high_resolution_clock::now();

   for(j=0;j<num_SV;j++){    // Main loop start   DB allocation server : j 

      //std::cout << " j : " << j << endl;

      std::sort(list_edge_s[j].begin(), list_edge_s[j].end(), cmp_edge);  // sorting d_ji from j

      //std::cout << endl;

      for(i=0;i<num_SV;i++){     // Usage Servers case  {Usage} number = i + 1
        
        //std::cout << " i : " << i << endl;

        sum_M = 0;

        delay_max_db = list_edge_s[j][i].delay;

        //std::cout << "delay_max_db : " << delay_max_db << endl; 
        
        if(delay_max_db >= T_delay){     // Go check another j : DB allocation other
            
            //std::cout << "DB_delay_OVER!!. Go Next." << std::endl;

            //std::cout << "j : " << j << ", i : " << i << endl;

            //std::cout << endl;

            break;

        }
        
        vector<int> Usage(i+1);

        select_usage(Usage, list_edge_s[j], num_SV, j, i);   // select {Usage} servers
        
        //std::cout << "Check Usage : ";
        
        /*
        for(i_1=0;i_1<=i;i_1++){

            std::cout << Usage[i_1] << ", ";
            
        }
        */

        std::sort(Usage.begin(), Usage.end());   // sort {Usage} index in ascending 

        //std::cout << endl;

        Server usage_list_server[i+1];

        //std::cout << endl;

        for(b=0;b<=i;b++){

          usage_list_server[b].index = Usage[b]; 

          usage_list_server[b].M_i = list_server_copy[Usage[b]].M_i;

          //std::cout << b << ", " << usage_list_server[b].index << endl;

          sum_M += usage_list_server[b].M_i;

        }

        //std::cout << "sum_M : " << sum_M << endl;

        if(sum_M < num_TE){
        
          //std::cout << "sum_M LOW IMPOSSIBLE!!" << endl;

          continue;

        }

        int V_sprime[sum_M];

        vector<Edge> E_t;

        //vector<Edge> E_tprime(num_TE*sum_M);   // E' set of copy edges

        vector<vector<Edge>> E_t2prime(num_TE, vector<Edge>(sum_M));   // E'' set of G(V, E'') add
        
        int usage_server;
        
        /*
        std::cout << "list_edge_t" << std::endl;
        
        for(int t=0;t<num_TE*num_SV;t++){

            std::cout << list_edge_t[t].delay << ", ";

        }

        std::cout << std::endl;
        */
        
        for(k=0;k<num_TE;k++){
            for(int s_i = 0; s_i <= i; s_i++){

                usage_server = usage_list_server[s_i].index;

                E_t.push_back(list_edge_t[k*num_SV+usage_server]);

            }
        }
        
        //std::cout << "This 2" << std::endl;

        std::sort(E_t.begin(), E_t.end(), cmp_edge);   // only real edges sorting
        
        /*
        for(int t=0;t<num_TE*(i+1);t++){

            std::cout << E_t[t].delay << ", ";

        }

           std::cout << std::endl;
        */
        
        i_1 = 0;

        int D_T;

        vector<int> hop_real_sindex(sum_M);

        int *pairU;

        pairU = new int[num_TE+1]; 

        int *pairV;

        pairV = new int[sum_M+1];

        BipGraph g(num_TE, sum_M, pairU, pairV);

        std::vector<int> nodes;

        //std::cout << "Start Hopcroft-Karp" << std::endl;

        int first_find_flag = 0;

        do_try = 0;

        gadd = 0;

        //std::cout << " i : " << i << " j : " << j << std::endl;

        while(i_1 < num_TE*(i+1)){

           D_T = E_t[i_1].delay;
            
            /*
            if(first_find_flag == 1){

                std::cout << "FIRST_MATCHING_FOUND!!" << endl;

                break;
            }
            */
            
            if(E_t[i_1].delay >= T_delay){   // Check if Shining will {Usage}
                
                //std::cout << "THIS E_tprime.delay" << E_t[i_1].delay <<  "MORE than" << T_delay << endl;
                
                //std::cout << " j : " << j << ", i : " << i << endl;

                //std::cout << "gadd : " << gadd << endl;

                break;
            }

           i_2_k = E_t[i_1].index / num_SV;

           if(std::find(nodes.begin(), nodes.end(), i_2_k) == nodes.end()){

                nodes.push_back(i_2_k);

                do_try = do_try + 1;

            }

           E_t[i_1].s_index = E_t[i_1].index % num_SV;

           auto it = std::find(Usage.begin(), Usage.end(), E_t[i_1].s_index);
           
           int wanted_index = std::distance(Usage.begin(), it);

           //std::cout << "wanted_index : " << wanted_index << std::endl;
           
           int start_point = list_server[E_t[i_1].s_index].M_i * wanted_index;

           //std::cout << "This 4" << std::endl;

           i_2_l = start_point;
           
           E_t2prime[i_2_k][i_2_l] = E_t[i_1];  // This line causes problem.  // E_t[i_1].delay is negative.

           hop_real_sindex[i_2_l] = E_t[i_1].s_index;

           g.addEdge(i_2_k+1, i_2_l+1);

           gadd = gadd + 1;

           i_2 = 1;

           while(i_2 < list_server[E_t[i_1].s_index].M_i){
              
              i_2_l = start_point + i_2;
          
              E_t2prime[i_2_k][i_2_l] = E_t[i_1];

              hop_real_sindex[i_2_l] = E_t[i_1].s_index;

              g.addEdge(i_2_k+1, i_2_l+1);

              i_2 = i_2 + 1;

           }

           i_1 = i_1 + 1;
        

            for(int u=0; u<=num_TE; u++){    // initialization pairU[u] 
                pairU[u] = NIL;
            }
            for(int v=0; v<=sum_M; v++){     // initialization pairV[v]
                pairV[v] = NIL;
            }

            //std::cout << "This 5" << std::endl;

            //std::cout << "num_TE : " << num_TE << ", sum_M : " << sum_M << endl;
            
            match = 0;

            int left_find_num = 0;

            if(do_try == num_TE){

                match = g.hopcroftKarp(num_TE, sum_M, pairU, pairV);    // return size of maximum matching

                //std::cout << "Possible Hopcroft-Karp " << endl;
                
            } 

            int max_num = 0;

            //std::cout << "match " << match << endl;

            if(match == num_TE){
               
               first_find_flag = 1;

               std::cout << "match = " << match << " !! " << endl; 

               std::cout << "do_try : " << do_try << endl;

               std::cout << "j : " << j << ", i : " << i << endl;
               
               //max_num = *max_element(find_num.begin(), find_num.end());

               //std::cout << max_num << endl;

               for(int u=0;u<num_TE;u++){

                 match_edge_delay[u] = E_t2prime[u][pairU[u+1]-1].delay; 
                 
               }

               std::cout << "gadd : " << gadd << endl;

               std::cout << "delay_max_db : " << delay_max_db << endl;

               delay_max_te = *max_element(match_edge_delay.begin(), match_edge_delay.end());
               
               std::cout << "delay_max_te : " << delay_max_te << endl;

               prev_T_delay = T_delay;

               T_delay_pre = std::max(delay_max_db, delay_max_te);

               std::cout << "T_delay " << T_delay_pre << endl;

               std::cout << std::endl;

               if(T_delay_pre < prev_T_delay){
                  
                  T_delay = T_delay_pre;

                  x1 = x1_0;

                  y = y_0;
                  
                  for(int u=0;u<num_TE;u++){

                    x1[u] = hop_real_sindex[pairU[u+1]-1];
                    
                    /*
                    if((pairU[u+1]) == NIL){

                      std::cout << "u = " << u << " This is suspecious!!" << endl;

                    }
                    */

                    /*
                    if(T_delay_pre == 817)
                      std::cout << "x1[ " << u << " ] = " << pairU[u+1]-1 << ", " << x1[u] << endl;  
                    */


                    y[hop_real_sindex[pairU[u+1]-1]] = 1;

                  }
                  
                  /*
                  for(int i1=0; i1<num_SV; i1++){

                     //std::cout << "y[ " << i1 << " ] = " << y[i1] << endl;

                  }
                  */

                  z = j;

               }

            }

            if(first_find_flag == 1){

                //std::cout << "FIRST_MATCHING_FOUND!!" << endl;

                //delete pairU;

                //delete pairV;

                break;
            }

        }

        delete [] pairU;

        delete [] pairV;

      }

   }

   auto end = chrono::high_resolution_clock::now();

   auto Elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

   std::cout << "Elapsed Time: (ms)" << Elapsed.count() << endl;   // Important
   
   std::cout << "Allocation Algorithm Finished " << endl;

   std::cout << "T_delay = " << T_delay << endl;     //  Most Important 

   /*
   for(int u=0;u<num_TE;u++){

     std::cout << "x [" << u << "]=" << x1[u] << endl;    // TE allocation server

   }
   */



   for(int i=0;i<num_SV;i++){

     std::cout << "y[ " << i << " ] = " << y[i] << endl;    // APL Usage servers

   }
     
     std::cout << "z = " << z << endl;    // DB allocation server
   

   ifs.close();

   return 0;

}

