# Emotion Detection
======
the code detect emotion using a webcam through cLassifing 49 keypoints optained using [dlib library](http://dlib.net/)

the program can classify 6 emotions 
* anger
* disgust
* fear
* happy
* sadness
* surprise

the classifer used is an SVm classifer with an accurcay of 99% 
obtained from 100 test ssample.
# Dataset
======
Extended Cohn-Kanade Dataset (CK+)

# Usage 
======
you can install the program using the provided Cmake file
you will need to download [Dlib model](http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2)
to be able to run the program . 
if you need to try collecting the data yourself 
there's a matlab code to collect the data from the datasets

notice this need you to have openCv installed in order to run it.
# P.S
=====
the code is a little rugh but i couldn't find the time to clean it  

### License ###

this code  is distributed under the [MIT License](http://www.opensource.org/licenses/MIT)
