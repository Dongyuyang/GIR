#include "gir.hpp"
#include "../commonTool/common_tool.hpp"
#include "../commonTool/init_data.hpp"
#include "bitio.hpp"

int main()
{
  int number = 1000;
  int d = 10;
  
  std::vector<std::vector<double> > aa(number);
  std::vector<std::vector<double> > ww(number);

  randinit(aa,d,0,1);
  randinit_w(ww,d,0,1);

  std::string product = "./data/P_";
  product.append(std::to_string(number));
  product.append("_");
  product.append(std::to_string(d));
  product.append(".dat");

  std::string weight = "./data/W_";
  weight.append(std::to_string(number));
  weight.append("_");
  weight.append(std::to_string(d));
  weight.append(".dat");
  
  std::string index = "./data/index_";
  index.append(std::to_string(number));
  index.append("_");
  index.append(std::to_string(d));
  index.append(".dat");
  

  write_vec(product,aa);
  write_vec(weight,ww);

  gir g;
  g.initGrid(128,128,1,1);

  for(int i = 0; i < aa.size();i++){
    g.addIndexP(aa[i]);
    g.addIndexW(ww[i]);
  }

  bitChar bc;
  std::ofstream outf(index);
  bc.setBITS(bc.covert_vec(g.m_index_a,8));
  bc.insertBits(outf);

  

}
