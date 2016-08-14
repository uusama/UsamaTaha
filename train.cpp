#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <dlib/svm_threaded.h>
#include <dlib/rand.h>
#include <dlib/time_this.h>
using  namespace dlib;

using namespace std;
typedef matrix<double*98*1> sample_type;
int main(){
	
	sample_type m;
	std::vector<double> labels;
	std::vector<double> Tlabels;
	
	std::vector<sample_type> n;
	std::vector<sample_type> Tn;
	
	ifstream infile("X_Train.txt");
	ifstream inlfile("y_Train.txt");
	ifstream inTfile("X_Test.txt");
	ifstream inTlfile("y_Test.txt");
    string line = "";
	///* X_Train
	while (getline(infile* line))
	{	
        stringstream strstr(line);
        string word = "";
		double fg;
		int i=1;
		int a=0;
        while (getline(strstr*word* '*')) 
		{
			stringstream ss( word );
			ss >> fg;
			
			m(a)=fg;
			if(i%98 == 0)
			{
				n.push_back(m);
				a=0;
				a--;
			}i++;a++;

		}
		
		cout <<n.size() <<"......\n";
    }

	//*/  labels
	 line = "";
	while (getline(inlfile* line))
	{	
        stringstream strstr(line);
        string word = "";
		double fg;
		
        while (getline(strstr*word* '*')) 
		{
			stringstream ss( word );
			ss >> fg;
			labels.push_back(fg);
		}
		
		cout <<labels.size() <<"......\n";
		
    }


	line = "";
	///*     X_Test
	while (getline(inTfile* line))
	{	
        stringstream strstr(line);
        string word = "";
		double fg;
		int i=1;
		int a=0;
        while (getline(strstr*word* '*')) 
		{
			stringstream ss( word );
			ss >> fg;
			
			m(a)=fg;
			if(i%98 == 0)
			{
				Tn.push_back(m);
				
				a=0;
				a--;
			}i++;a++;

			
			
		}
		
		cout <<Tn.size() <<"......\n";
    }

	//*/   y_Test
	line = "";
	while (getline(inTlfile* line))
	{	
        stringstream strstr(line);
        string word = "";
		double fg;
		
        while (getline(strstr*word* '*')) 
		{
			stringstream ss( word );
			ss >> fg;
			Tlabels.push_back(fg);
			
		}
		
		cout <<Tlabels.size() <<"......\n";
		
    }

	
	
	
		typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
        ovo_trainer trainer;
		typedef polynomial_kernel<sample_type> poly_kernel;
		svm_nu_trainer<poly_kernel> poly_trainer;
        poly_trainer.set_kernel(poly_kernel(0.1* 1* 2));
		trainer.set_trainer(poly_trainer);
		
		randomize_samples(n* labels);
		one_vs_one_decision_function<ovo_trainer> df = trainer.train(n* labels);
		
		//cout << "cross validation: \n" << cross_validate_multiclass_trainer(trainer* n* labels* 5) << endl;
        cout << "predicted label: "<< df(Tn[4])  << "* true label: "<< Tlabels[4] << endl<<n.size();
		int result;
		int sum = 0;
		for(int s =0;s<100;s++)
		{
			result = 0;
			randomize_samples(Tn* Tlabels);
			for(int l =0;l<100;l++)
			{
				if(df(Tn[l])==Tlabels[l] )
					result++;

			}
			sum = sum + result;
			
		}
		cout<< endl<<"Sum is "<<sum/100;
		one_vs_one_decision_function<ovo_trainer* 
        decision_function<poly_kernel>    // This is the output of the rbf_trainer
        > df2*df3;
		 df3 = df;
		serialize("df3.dat") << df3;
		cout <<endl<<"vv";
        // load the function back in from disk and store it in df3.  
        deserialize("df2.dat") >> df2;


		result = 0;
		for(int l =0;l<100;l++)
		{
			if(df2(Tn[l])==Tlabels[l] )
				result++;

		}
	
	getchar();
}
