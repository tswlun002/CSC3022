# Building a ‘video’ from a large image
 
Provided with a very large input image (for example, 16K x 16K “image moscaic” from
an astronomy sky survey) we want to produce a video that captures the movement of a
much smaller window across this large image. You can think of this as lens that allows us
to focus on a trajectory of interest

# RECOMMENDED USE MAKEFILE TO TEST THIS CODE AS FOLLOW:
- compile using : 
 ```bash
 make
 ```
- run using 
```bash
make run
```

Explaining run command , note everything below is already written on `frametester.sh`
`frametester.sh` make video also and save them to their folder.

### Option 1 - Test core work:
- for E.G process can be none or reverse or invert or revinvert :
```bash
 ./extractor larger_image.pgm -t 0 0 800 800 -s 600 600 -w none SIMPLE 
```
- Outputfilename will be concatenated with image number like `filename-NNNN.pgm`, where `NNNN` is the number
./extractor image_name -t x1 y1 x2 y2 -s width height -w process outputfilename  
                                                                                                                                                            
 ### Option 2 - Test core work:
./extractor image_name -t x1 y1 x2 y2 -s width height -w process outputfilename process outputfilename 
- for E.G :
```bash
- ./extractor larger_image.pgm -t 0 0 800 800 -s 600 600 -w none simple1  invert  simple2
```
### Option 3 - Test mastery , Path:
- here we tell video which path to use instead of start -End
- -t is replaced by -p 
- n is the number of path to take, in our example above n=3
- Other part of command is the same as above

#### For E.G ./extractor image_name -p 3 0 0 800 800 0 0 -s 100 100 -w none 3POINT                                                                           
```bash
./extractor image_name -p n x1 y1 x2 y2 x3 y3 -s width height -w process outputfi 
```
### Option 4 - Test mastery, Acceleration of video
- so maxmum acceleration = 100
- all other part of the command are same as above
- just added to command to allow user to enter acceleration it wants
- Added -a which indicate user has given maximum acceleration
- maximumAcceleration- is the maximum acceleration use wants vidoe to accelerate upto the de-accelerate
- If user does not give acceleration, then its defaulted to zero on the code the application
- So acceleration can be included at options or others by just adding -a maxAcceleration after outputfilename
- /extractor image_name -t x1 y1 x2 y2 -s width height -w process outputfilename -a maximumAcceleration :
```bash
./extractor image_name -t 0 0 100 100 -s 100 100 -w none ACCELERATE_SIMPLE -a 100
```                                                                                              
                                                                                                                                                                                      
### CLEANING use command: 
-  all *.pgm, *.png, *.mp4, *.o ,extractor will be removed   
```sh
make clean     
```
                                                                                                                                                                           
