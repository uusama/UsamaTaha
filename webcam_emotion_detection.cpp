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

using namespace dlib;
using namespace std;

typedef matrix<double,98,1> sample_type;



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
        //  positions of widgets . 
		imgv.set_pos(20,70);
		imgv.set_size(658,484);
		b.set_pos(imgv.left(),imgv.bottom()+5);
        b.set_name("Detect");
		b.set_size(80,50);
		c.set_pos(b.left()+10,b.bottom());
		
        // let's put the label 5 pixels below the button
        c.set_pos(b.left(),b.bottom()+5);

        set_size(730,660);

        counter = 0;

        set_title("Emotion Detection Example");
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

  
	void on_button_clicke(string counf)
	{
		ostringstream sout;
        sout << "Emotion: " << counf;
        c.set_text(sout.str());
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
		
		string emotion[8] = {"neutral","anger", "contempt", "disgust", "fear", "happy", "sadness", "surprise"};
		matrix<double,98,1> m;
		typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
        ovo_trainer trainer;
		typedef polynomial_kernel<sample_type> poly_kernel;
		svm_nu_trainer<poly_kernel> poly_trainer;
        poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));
		trainer.set_trainer(poly_trainer);
		 one_vs_one_decision_function<ovo_trainer, 
        decision_function<poly_kernel>    // This is the output of the rbf_trainer
        > df2;

        // load the function back in from disk and store it in df3.  
        deserialize("df2.dat") >> df2;
        cv::VideoCapture cap(0);
        

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
        // Grab and process frames until the main window is closed by the user.
		int starter = 0;
		string emot;

		my_window.b.set_click_handler([&](){
             
			if (starter==0)
			{
				starter=1;
				my_window.imgv.show();
				my_window.b.set_name("Close");
				my_window.b.set_size(80,50);
			}
			else
			{
				starter=0;
				my_window.b.set_name("Detect");
				my_window.b.set_size(80,50);
				my_window.imgv.clear_overlay();
				my_window.imgv.hide();
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

            // Time 
           //TIME_THIS( std::vector<rectangle> faces = detector(cimg);) 
			
			   std::vector<rectangle> faces = detector(cimg);
            // Find the pose of each face.
            std::vector<full_object_detection> shapes;
			
            for (unsigned long i = 0; i < faces.size(); ++i)
                shapes.push_back(pose_model(cimg, faces[i]));
				dlib::point fg;
			
				for (unsigned long i = 0; i < shapes.size(); ++i)
				{
				full_object_detection& d = shapes[i];

				 int count = 0;int coun = 0;;int counter = 0;
				 for (unsigned long i = 0; i < d.num_parts(); ++i)
					 {
						 if(i<=16 && i!=8)
						 {
							 continue;
						 }
						  if(i>=27 && i<=29)
						 {
							 continue;
						 }
						 
						  coun++;
						 fg = d.part(i);
						 double fj = fg.x();
						 m(counter+1*count)=fg.x();
						 m(counter+1*count+1)=fg.y();
						 count++;counter++;
						 
					 }
					
					
				int emo =	df2(m);
				emot = emotion[emo];
					
				}		
           
			my_window.imgv.clear_overlay();
			if(starter)
			{

				my_window.on_button_clicke(emot);
				my_window.imgv.set_image(cimg);
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
    }
}

#ifdef _MSC_VER
#   pragma comment( linker, "/entry:mainCRTStartup" )
#   pragma comment( linker, "/SUBSYSTEM:WINDOWS" )
#endif