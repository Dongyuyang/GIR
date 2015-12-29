#include <cmath>

using namespace std;


class bitChar{
public:
  unsigned char* c;
  int shift_count;
  string BITS;

  bitChar()
  {
    shift_count = 0;
    c = (unsigned char*)calloc(1, sizeof(char));
  }

  string covert(int a, int bit_number){
    string code = "";
    int remain = a;
    for(int i = bit_number - 1; i >= 0; i--){
      int v = pow(2,i);
      if(remain - v >= 0){
	code.append("1");
	remain = remain - v;
      }else{
        code.append("0");
      }      	
    }
    return code;
  }

  string covert_vec(const vector<vector<int> > &vector, int code_number)
  {
    std::string encode = "";
    for(auto &vec : vector){
      for(auto value : vec){
	encode.append(covert(value,code_number));
      }
    }
    return encode;
  }

  string readByBits(ifstream& inf)
  {
    string s ="";
    char buffer[1];
    while (inf.read (buffer, 1))
      {
	s += getBits(*buffer);
      }
    return s;
  }

  void setBITS(string X)
  {
    BITS = X;
  }

  int insertBits(ofstream& outf)
  {
    int total = 0;

    while(BITS.length())
      {
	if(BITS[0] == '1')
	  *c |= 1;
	*c <<= 1;
	++shift_count;
	++total;
	BITS.erase(0, 1);

	if(shift_count == 7 )
	  {
	    if(BITS.size()>0)
	      {
		if(BITS[0] == '1')
		  *c |= 1;
		++total;
		BITS.erase(0, 1);
	      }

	    writeBits(outf);
	    shift_count = 0;
	    free(c);
	    c = (unsigned char*)calloc(1, sizeof(char));
	  }
      }

    if(shift_count > 0)
      {
	*c <<= (7 - shift_count);
	writeBits(outf);
	free(c);
	c = (unsigned char*)calloc(1, sizeof(char));
      }
    outf.close();
    return total;
  }

  string getBits(unsigned char X)
  {
    stringstream itoa;
    for(unsigned s = 7; s > 0 ; s--)
      {
	itoa << ((X >> s) & 1);
      }

    itoa << (X&1) ;
    return itoa.str();
  }

  void writeBits(ofstream& outf)
  {
    outf << *c;
  }

  ~bitChar()
  {
    if(c)
      free(c);
  }
};
