#include <iostream>
#include <fstream>
#include <string> 
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
	    cout<< "Please provide the flux file\n" ;
	    return 1 ;
    }
    char *datafile=argv[1];
    cout << "reading the data..\n";
    vector< double> J_x;  
    vector< double> J_y;  
    vector< double> J_z;  
    vector< double> autocorr_x;  
    vector< double> autocorr_y;  
    vector< double> autocorr_z;  
    double buff;
    ifstream f_data;
    f_data.open(datafile);
    double jx,jy,jz;
    while (!f_data.eof())
    {
	f_data >> buff >> buff >> jx >> jy >> jz ;
	J_x.push_back(jx);
	J_y.push_back(jy);
	J_z.push_back(jz);
    }
    cout << "Length of trajectory is -> " << J_x.size()<< endl;
    int size_data=J_x.size();
    int size_autocrr=0.01*size_data;

    for (int ct=0; ct < size_autocrr; ct++)
    {
        double total_x=0.0;
        double total_y=0.0;
        double total_z=0.0;
        for (int j=0; j< size_data-ct; j++)
        {
            total_x =total_x + J_x[j]*J_x[j+ct];
            total_y =total_y + J_y[j]*J_y[j+ct];
            total_z =total_z + J_z[j]*J_z[j+ct];
        }
        autocorr_x.push_back(total_x/(double)(size_data-ct));
        autocorr_y.push_back(total_y/(double)(size_data-ct));
        autocorr_z.push_back(total_z/(double)(size_data-ct));
    }
    ofstream f_out("autocorrelation.dat");
    f_out << "# time autocorr   "  <<endl;
    for (int ct=0; ct < size_autocrr; ct++)
    {
        double sum;
        sum = autocorr_x[ct] + autocorr_y[ct] + autocorr_z[ct];    
        f_out << ct << "   " << sum << "  " <<autocorr_x[ct] <<  "  " <<autocorr_y[ct] <<  "  " <<autocorr_z[ct] <<endl;
    }
    return 0;
}
