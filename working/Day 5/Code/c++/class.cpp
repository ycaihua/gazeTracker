#include<iostream>
using namespace std;
class Box
{
    public:
        double length;
        double breadth;
        double height;
};
class printData
{
    public:
        void print(int i)
        {
        cout << "Printing int:" << i << endl;
        }
};

int main()
{
  Box Box1;
  Box Box2;
  double volume = 0.0;

  Box1.height = 5.0;
  Box1.length = 6.0;

  printData pd;
  pd.print(5);
  return 0;


}
