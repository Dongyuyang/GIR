#include <math.h>
#include <vector>
#include <iostream>

class gir
{
public:

  gir(){}

  void initGrid(int a_split_num, int b_split_num, double a_up, double b_up){
    m_grid.resize(b_split_num + 1);
    m_step_a = a_up / (double)a_split_num;
    m_step_b = b_up / (double)b_split_num;
    for(int i = 0; i < m_grid.size(); i++){
      std::vector<double> b_vec(a_split_num + 1);
      for(int j = 0; j < b_vec.size();j++)
	b_vec[j] = m_step_a * m_step_b * i * j;
      m_grid[i] = b_vec;
    }
  }

  void addIndexP(const std::vector<double> &p){
    std::vector<int> index_p(p.size());
    for(int i = 0; i < index_p.size();i++)
      index_p[i] = p[i] / m_step_a;
    m_index_a.push_back(index_p);
  }

  void addIndexW(const std::vector<double> &w){
    std::vector<int> index_w(w.size());
    for(int i = 0; i < index_w.size();i++)
      index_w[i] = w[i] / m_step_b;
    m_index_b.push_back(index_w);
  }

  /*1 : < value; -1: > value; 0: not sure*/
  int check_score(const std::vector<double> &p, const std::vector<double> &w, double value){
    double lower = 0, upper = 0;
    for(int i = 0; i < p.size();i++){
      lower += m_grid[ floor( w[i] / m_step_b ) ][ floor( p[i] / m_step_a) ];
      upper += m_grid[ ceil(w[i] / m_step_b ) ][ ceil( p[i] / m_step_a ) ];
      if(lower > value)
	return -1;
    }
    if(upper < value)
      return 1;
    else
      return 0;
    
  }

  /*1 : < value; -1: > value; 0: not sure*/
  int check_score_index(const std::vector<int> &p, const std::vector<int> &w, double value){
    double lower = 0.0;
    //double upper = 0.0;
    for(int i = 0; i < p.size();i++){
      lower += m_grid[ w[i] ][ p[i] ];
      //upper += m_grid[ w[i] + 1][ p[i] + 1 ];
      if(lower > value)
	return -1;
    }
    //upper = lower + m_step_a*m_step_b*p.size();
    //if(upper < value)
    if(lower + 0.06 < value)
      return 1;
    else
      return 0;
  }

  


  std::vector<std::vector<double> > m_grid;
  std::vector<std::vector<int> > m_index_a;
  std::vector<std::vector<int> > m_index_b;
  
  double m_step_a = 0;
  double m_step_b = 0;

  
};
