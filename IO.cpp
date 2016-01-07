#include "gir.hpp"
#include "../commonTool/common_tool.hpp"
#include "../commonTool/catch.h"
#include "../commonTool/init_data.hpp"
#include "bitio.hpp"

int main()
{
  int number = 1000;
  int d = 6;

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
  
}
