# Computer-vision-OpenCV-Hough-lines-detection

In the code, we first read the frame from the webcam and then applied Canny edge 
detection on it. The frame after applying canny edge was given to the cvtColor to 
convert it from gray to BGR. Then we created a vector to store the frame in BGR format 
and then applied the Hough lines technique and got the lines in the image by iterating 
through the for loop in the vector of frames. By using these methods one after the other, 
we got the desired output by ‘imshow’ method.
