# clmtrackr
======
this code detect emotion using a webcam through cLassifing 49 keypoints optained using [dlib library](http://dlib.net/)
It can classify 6 emotions 
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
you can install the program through Cmake using the provided file
you will need to download [Dlib model](http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2)
to be able to run the program . 
notice this need you to have openCv installed in order to run it.
# P.S
=====
the code is alittle rugh but i couldn't find the time to optmize it  

### License ###

this code  is distributed under the [MIT License](http://www.opensource.org/licenses/MIT)
