#include <iostream>
#include <vector>
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/svm_threaded.h>
#include<string>
#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <dlib/matrix.h>
#include<dlib/time_this.h>

using namespace dlib;
using namespace std;
using namespace cv;




class win : public drawable_window 
{
    
   
public:
    win(
    ) : // All widgets take their parent window as an argument to their constructor.
        c(*this),
        b(*this),
        mbar(*this),
		imgv(*this)
    {
        // tell our button to put itself at the position (10,60). 
		imgv.set_pos(20,70);
		imgv.set_size(658,484);
		b.set_pos(imgv.left(),imgv.bottom()+5);
        b.set_name("Detect");
		b.set_size(40,40);
		c.set_pos(b.left()+10,b.bottom());
		
        // let's put the label 5 pixels below the button
        c.set_pos(b.left(),b.bottom()+5);

		
       
        set_size(730,660);

        counter = 0;

        set_title("dlib gui example");
        show();
    } 

    ~win(
    )
    {
        // You should always call close_window() in the destructor of window
        // objects to ensure that no events will be sent to this window while 
        // it is being destructed.  
        close_window();
    }

public:

    void on_button_clicked (int& start)
    {cout<<"ffffffffffffffffffff";
        if (start==0)
		{
			start=1;
			
			 b.set_name("closed");
		}
		else
		{
			start=0;
			b.set_name("Detect");
		}
    }
	void on_button_clicke(string counf)
	{
		ostringstream sout;
        sout << "counter: " << counf;
        c.set_text(sout.str());
	}

    void show_about(
    )
    {
        message_box("About","This is a dlib gui example program");
    }

    unsigned long counter;
	
    label c;
    button b;

    menu_bar mbar;
	image_display imgv; 

};

typedef matrix<double,576,1> sample_type;



int main()
{
    try
    {
		
		int i = 1;
		std::vector<sample_type>  ln;
		std::vector<double> emo;
		std::vector<sample_type> lnT;
		std::vector<double> emoT;
		win my_window;
		sample_type im;
		std::vector<uchar> arra;
		Mat im_gray;
		Mat temp; 
		i = 1;
		VideoCapture cap("Dataset_A_Eye_Images/Ctrain/%03d.jpg");
        while(!my_window.is_closed())
        {
           
			if(i==120)
			{
				//cout << "Size = "<<ln.size();
				break;
			}
                    
			cap.read(temp);
			
			cvtColor(temp,im_gray,CV_RGB2GRAY);	
			//cv_image<bgr_pixel> cimg(im_gray);
			//cout << "Width : " << im_gray.size() << endl;
			///*
			
			
			if (im_gray.isContinuous()) {
			  arra.assign(im_gray.datastart, im_gray.dataend);
			} else {
			  for (int i = 0; i < im_gray.rows; ++i) {
				arra.insert(arra.end(), im_gray.ptr<uchar>(i), im_gray.ptr<uchar>(i)+im_gray.cols);
			  }
			}
			//*/
			//cout <<endl <<"........"<<arra.size()<<im.size();;
			
			//im(0) =1;
			for(std::vector<int>::size_type i = 0; i != arra.size(); i++) 
						im(i) = arra[i];
			//getchar();
			ln.push_back(im);
			emo.push_back(0);
			i++;		
		}

		i = 1;
		VideoCapture cap1("Dataset_A_Eye_Images/Otrain/%03d.jpg");
        while(!my_window.is_closed())
        {
           
			if(i==120)
			{
				//cout << "Size = "<<ln.size();
				break;
			}
                    
			cap.read(temp);
			
			cvtColor(temp,im_gray,CV_RGB2GRAY);	
			//cv_image<bgr_pixel> cimg(im_gray);
			//cout << "Width : " << im_gray.size() << endl;
			///*
			
			
			if (im_gray.isContinuous()) {
			  arra.assign(im_gray.datastart, im_gray.dataend);
			} else {
			  for (int i = 0; i < im_gray.rows; ++i) {
				arra.insert(arra.end(), im_gray.ptr<uchar>(i), im_gray.ptr<uchar>(i)+im_gray.cols);
			  }
			}
			//*/
			//cout <<endl <<"........"<<arra.size()<<im.size();;
			
			//im(0) =1;
			for(std::vector<int>::size_type i = 0; i != arra.size(); i++) 
						im(i) = arra[i];
			//getchar();
			ln.push_back(im);
			emo.push_back(1);
			i++;		
		}


		cout<<endl <<"sizzzze  ==== "<<ln.size()<<"  " <<emo.size()<<endl ;

// ...
		randomize_samples(ln, emo);
		for(i = 0;i<100;i++)
		{
			emoT.push_back(emo[i]);
			lnT.push_back(ln[i]) ;
			
			emo.erase(emo.begin() + i);
			ln.erase(ln.begin() + i);
		}
		randomize_samples(lnT, emoT);
		cout<<endl <<"sizzzze  ==== "<<lnT.size()<<"  " <<emoT.size()<<endl ;
		cout<<endl <<"sizzzze  ==== "<<ln.size()<<"  " <<emo.size()<<endl ;


		///*
		typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
        ovo_trainer trainer;
		typedef polynomial_kernel<sample_type> poly_kernel;
		svm_nu_trainer<poly_kernel> poly_trainer;
        poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));
		trainer.set_trainer(poly_trainer);
		///*
		one_vs_one_decision_function<ovo_trainer> df = trainer.train(ln, emo);
		
		cout << "cross validation: \n" << cross_validate_multiclass_trainer(trainer, ln, emo, 5) << endl;
        cout << "predicted label: "<< df(lnT[4])  << ", true label: "<< emoT[4] << endl;
		
		int result = 0;
		for(int l =0;l<100;l++)
		{
			if(df(lnT[l])==emoT[l] )
				result++;

		}
		cout <<"Result is "<<result;
		//*/
		cout<<endl <<lnT.size()<<"  " <<emoT.size() ;


		 one_vs_one_decision_function<ovo_trainer, 
        decision_function<poly_kernel>    // This is the output of the rbf_trainer
        > df3;
		 df3 = df;
		serialize("CloseOpen.dat") << df3;



		//cout<<endl <<lnT.size()<<"  " <<emoT.size() ;
		getchar();
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
		getchar();
    }
    catch(exception& e)
    {
        cout << e.what() << endl;getchar();
    }
}

