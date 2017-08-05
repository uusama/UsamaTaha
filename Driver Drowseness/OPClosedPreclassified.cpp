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

#include<dlib/time_this.h>



#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>
#include <dlib/matrix.h>
#include<dlib/time_this.h>





using namespace dlib;
using namespace std;

typedef matrix<double,576,1> sample_type;




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





int main()
{
    try
    {

		win my_window;
		
	
		//my_window.wait_until_closed();

		//my_window.wait_until_closed();
		string emotion[2] = {"Closed","Open"};
		sample_type m;
		typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
        ovo_trainer trainer;
		typedef polynomial_kernel<sample_type> poly_kernel;
		svm_nu_trainer<poly_kernel> poly_trainer;
        poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));
		trainer.set_trainer(poly_trainer);
		 one_vs_one_decision_function<ovo_trainer, 
        decision_function<poly_kernel>    // This is the output of the rbf_trainer
        > df2;
		 
		
		//cout <<endl<<"vv";
        // load the function back in from disk and store it in df3.  
        deserialize("CloseOpen.dat") >> df2;
        cv::VideoCapture cap(0);
        

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
        // Grab and process frames until the main window is closed by the user.
		int starter = 0;
		string emot;

		my_window.b.set_click_handler([&](){
                //on_button_clicked (int& start);
			 if (starter==0)
		{
			starter=1;
			
			 my_window.b.set_name("Close");
		}
		else
		{
			starter=0;
			my_window.b.set_name("Detect");
			my_window.imgv.clear_overlay();
		}
                });



        while(!my_window.is_closed())
        {
            // Grab a frame
            cv::Mat temp;
            cap >> temp;
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
            cv_image<bgr_pixel> cimg(temp);

            // Detect faces 
           //TIME_THIS( std::vector<rectangle> faces = detector(cimg);) 
			
			   std::vector<rectangle> faces = detector(cimg);
			   // std::vector<rectangle> faces = detector(cimg);
            // Find the pose of each face.
            std::vector<full_object_detection> shapes;
			// unsigned long sha= shapes[1].num_parts();
			//full_object_detection sha=shapes[0];
			
            for (unsigned long i = 0; i < faces.size(); ++i)
                shapes.push_back(pose_model(cimg, faces[i]));
			//full_object_detection shp = pose_model(cimg, faces[0]);
			
			dlib::point fg;
			
				for (unsigned long i = 0; i < shapes.size(); ++i)
				 {
					 full_object_detection& d = shapes[i];
					 

					 cout <<"........"<<d.part(29).y()-d.part(27).y()<<"    ";
					cv::Rect myROI(d.part(22).x(), d.part(22).y(), d.part(26).x()-d.part(22).x(), d.part(28).y()-d.part(24).y());
					cout <<d.part(45).x()<<"  "<<d.part(42).x(); 
					// Crop the full image to that image contained by the rectangle myROI
					// Note that this doesn't copy the data
					cv::Mat croppedImage = temp(myROI);
					
					cv::cvtColor(croppedImage,croppedImage,CV_RGB2GRAY);
					
					cv::Size siz(24,24);//the dst image size,e.g.100x100
					//Mat dst;//dst image
					//Mat src;//src image
					resize(croppedImage,croppedImage,siz);//resize image
					//cout <<endl <<"........"<<croppedImage.size();
					cv_image<unsigned char> cimg1(croppedImage); 
					my_window.imgv.set_image(cimg1);
					sample_type im;
					std::vector<uchar> arra;
					if (croppedImage.isContinuous()) {
					  arra.assign(croppedImage.datastart, croppedImage.dataend);
					} else {
					  for (int i = 0; i < croppedImage.rows; ++i) {
						arra.insert(arra.end(), croppedImage.ptr<uchar>(i), croppedImage.ptr<uchar>(i)+croppedImage.cols);
					  }
					}
					//*/
					//cout <<endl <<"........"<<arra.size()<<"  "<<im.size();;
			
					//im(0) =1;
					for(std::vector<int>::size_type i = 0; i != arra.size(); i++) 
								im(i) = arra[i];
					
					
					
							
					int emo =	df2(im);
					cout << "predicted label: "<<emotion[emo];
					if (emo)
						cout<<"........"<<endl<< endl;
					else
						cout<<endl<< endl;
					emot = emotion[emo];
					cout <<endl  <<"  "<<emo;
					//getchar();
					
					//getchar();
				//cout <<	d.num_parts()<<endl;
		// }
				}		
            // Display it all on the screen
            //win1.clear_overlay();
            //win1.set_image(cimg);
            //win1.add_overlay(render_face_detections(shapes));
			my_window.imgv.clear_overlay();
			if(starter)
			{

			
				my_window.on_button_clicke(emot);
				//my_window.imgv.set_image(cimg);
				my_window.imgv.add_overlay(render_face_detections(shapes));
			}
			
        }
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
		
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
		getchar();
    }
}

