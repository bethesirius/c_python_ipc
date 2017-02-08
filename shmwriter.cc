#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>

using namespace cv;

int main(int argc, const char **argv)
{
   int shmid;
   key_t key = 123456;
   char *shared_memory;

   // Setup shared memory 
   if ((shmid = shmget(key, 921600, IPC_CREAT | 0666)) < 0)
   {
      printf("Error getting shared memory id");
      exit(1);
   }
   // Attached shared memory
   if ((shared_memory = static_cast<char*>(shmat(shmid, NULL, 0))) == (char *) -1) 
   {
      printf("Error attaching shared memory id");
      exit(1);
   }

   Mat image;
   //image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
   image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

   //char a[1000];
   //gets(&a);
   printf("%d ", image.at<unsigned char>(0,0));
   printf("%d ", image.at<unsigned char>(0,1));
   printf("%d ", image.at<unsigned char>(0,2));
   memcpy(shared_memory, image.datastart, image.dataend - image.datastart);

   usleep(5000000);
   // Detach and remove shared memory
   shmdt(shared_memory);
   shmctl(shmid, IPC_RMID, NULL);
}
