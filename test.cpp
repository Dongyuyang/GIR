#include "gir.hpp"
#include "../commonTool/common_tool.hpp"
#include "../commonTool/catch.h"
#include "bitio.hpp"

int main()
{
  int number = 50000;
  int d = 10;
  
  std::vector<std::vector<double> > aa(number);
  std::vector<std::vector<double> > ww(number);

  randinit(aa,d,0,1);
  randinit_w(ww,d,0,1);

  write_vec("./data/products.dat",aa);
  write_vec("./data/weights.dat",ww);

  /*gir g;
  g.initGrid(128,128,1,1);

  for(int i = 0; i < aa.size();i++){
    g.addIndexP(aa[i]);
    g.addIndexW(ww[i]);
    }*/

  /*for(int i = 0; i < aa.size();i++){
    put_vector(g.m_index_a[i]);
    }*/

  /*bitChar bc;
  std::ofstream outf("Sample.dat");
  bc.setBITS(bc.covert_vec(g.m_index_a,8));
  bc.insertBits(outf);*/

  /*std::vector<std::vector<int> > index(number);
  
  CATCH bcost;
  bcost.catch_time();
  auto byte_vec = read_by_BYTE("sample.dat");
  int st = 0;
  for(int j = 0; j < index.size(); j++){
    std::vector<int> temp(d);
    for(int i = 0; i < temp.size();i++){
      temp[i] = (int)byte_vec[st++];
    }
    index[j] = temp;
  }
  bcost.catch_time();*/
  
  /*std::cout << "bcost: " << bcost.get_cost(2) << " millisecond(s)" << std::endl;
  
  for(auto &dfg : index){
    put_vector(dfg);
  }

  std::cout << std::endl;*/
  
  //std::cout << bc.covert_vec(g.m_index_a,5)  << std::endl;

  CATCH pcost;
  std::vector<std::vector<double> > p(number);
  pcost.catch_time();
  read_file(p,d,"./data/products.dat");
  pcost.catch_time();
  std::cout << "pcost: " << pcost.get_cost(2) << " millisecond(s)" << std::endl;

  std::vector<std::vector<double> > w(number);
  read_file(w,d,"./data/weights.dat");

  

  

  
  
  /*g.addIndexP(p);
  g.addIndexW(w);

  put_vector(g.m_index_a[0]);*/


  CATCH simcost;
  simcost.catch_time();
  for(auto &wei : w){
    for(auto &pro : p){
      auto aaa = inner_product(wei,pro);
    }
  }
  simcost.catch_time();

    
  /* CATCH gircost;
  gircost.catch_time();
  double lower = 0;
  double upper = 0;
  for(int i = 0; i < number*number; i++){
    //double a = g.check_score_index(g.m_index_a[0],g.m_index_b[0],10000);
    for(int j = 0; j < d; j++){
      //lower += g.m_grid[ g.m_index_a[6][5] ][ g.m_index_b[3][4] ];
      lower += index[6][7] + index[100][7];
      upper += index[7][8] + index[101][8];
    }
    lower = 0;
    upper = 0;
    }*/
  /*for(int i = 0; i < 1000000; i++){
    int a = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10;
    }
  
  
    gircost.catch_time();*/


  //std::cout << "gir: cpu cost is " << gircost.get_cost(2) << " millisecond(s)" << std::endl;

  std::cout << "sim: cpu cost is " << simcost.get_cost(2) << " millisecond(s)" << std::endl;
  

  

}
