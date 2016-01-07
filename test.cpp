#include "gir.hpp"
#include "../commonTool/common_tool.hpp"
#include "../commonTool/catch.h"
#include "../commonTool/init_data.hpp"
#include "bitio.hpp"

int main()
{
  int number = 10000;
  int d = 10;
  int k = 10000;
  std::string product_data = "./data/P_";
  product_data.append(std::to_string(number));
  product_data.append("_");
  product_data.append(std::to_string(d));
  product_data.append(".dat");

  std::string weight_data = "./data/W_";
  weight_data.append(std::to_string(number));
  weight_data.append("_");
  weight_data.append(std::to_string(d));
  weight_data.append(".dat");

  std::string indexp = "./data/index_P";
  indexp.append(std::to_string(number));
  indexp.append("_");
  indexp.append(std::to_string(d));
  indexp.append(".dat");

  std::string indexw = "./data/index_W";
  indexw.append(std::to_string(number));
  indexw.append("_");
  indexw.append(std::to_string(d));
  indexw.append(".dat");

  
  gir g;
  g.initGrid(128,128,1,1);
  
  std::vector<std::vector<int> > index_p(number);
  std::vector<std::vector<int> > index_w(number);
  
  CATCH bcost;
  bcost.catch_time();
  auto byte_vec_p = read_by_BYTE(indexp);
  auto byte_vec_w = read_by_BYTE(indexw);
  int st = 0;
  for(int j = 0; j < number; j++){
    std::vector<int> t_p(d);
    std::vector<int> t_w(d);
    for(int i = 0; i < d;i++){
      t_p[i] = (int)byte_vec_p[st];
      t_w[i] = (int)byte_vec_w[st];
      st++;
    }
    index_p[j] = t_p;
    index_w[j] = t_w;
  }
 
  bcost.catch_time();
  std::cout << "bcost: " << bcost.get_cost(2) << " millisecond(s)" << std::endl;


  std::vector<std::vector<double> > p(number);
  std::vector<std::vector<double> > w(number);
  CATCH pcost;
  pcost.catch_time();
  read_file(p,d,product_data);
  read_file(w,d,weight_data);
  pcost.catch_time();
  std::cout << "pcost: " << pcost.get_cost(2) << " millisecond(s)" << std::endl;

  int rand_number = get_rand(1,number);
  std::vector<double> q = p[rand_number];
  //std::vector<double> q(6,0);
  //q[rand_number] = 0.1;
  put_vector(q);
  
  CATCH simcost;
  simcost.catch_time();
  std::vector<int> sim_result;
  for(int i = 0; i < number; i++){
    int sim_count = 0;
    double q_score = inner_product(q,w[i]);
    for(int j = 0; j < number; j++){
      //double q_score = inner_product(q,w[i]);
      double p_score = inner_product(p[j],w[i]);
      if(p_score < q_score){
	sim_count++;
	if(sim_count > k){
	  break;
	}
      }
    }
    if(sim_count <= k)
      sim_result.push_back(i);
  }
  simcost.catch_time();

  auto grid = g.m_grid;
  
    
  CATCH gircost;
  std::vector<int> girresult;
  double q_score,p_score;
  int flag;
  int gir_count = 0;
  double lower = 0;
  int index_pp, index_ww;
  gircost.catch_time();
  for(int i = 0; i < number;i++){
    q_score = inner_product(q,w[i]);
    for(int j = 0; j < number;j++){
      //flag = g.check_score_index(index_p[j],index_w[i],q_score);

      for(int k = 0; k < d; k++){
	lower += g.m_grid[3][4];
	//lower += g.m_grid[index_ww][index_pp];
      }
      
      /*if(flag == 1){
	gir_count++;
	if(gir_count > k){
	  break;
	}
      }
      if(flag == 0){
	p_score = inner_product(p[j],w[i]);
	if(p_score < q_score){
	  gir_count++;
	  if(gir_count > k)
	    break;
	}
	}*/


    }
    if(gir_count <= k)
      girresult.push_back(i);
    gir_count = 0;
  }
  
  gircost.catch_time();


  std::cout << "s result size: " << sim_result.size() << std::endl;
  std::cout << "g result size: " << girresult.size() << std::endl;
  if(sim_result.size() != girresult.size()){
    std::cout << "error!"<< std::endl;
  }
  else{
    for(int i = 0; i < sim_result.size();i++){
      if(sim_result[i] != girresult[i]){
	std::cout << "error!"<< std::endl;
	break;
      }
    }
  }
  

  std::cout << "sim: cpu cost is " << simcost.get_cost(2) << " millisecond(s)" << std::endl;
  std::cout << "gir: cpu cost is " << gircost.get_cost(2) << " millisecond(s)" << std::endl;

  

}
