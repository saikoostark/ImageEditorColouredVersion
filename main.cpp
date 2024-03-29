// FCI � Programming 1 � 2022 - Assignment 3
// Program Name:    main.cpp
// Last Modification Date: 20/04/2022
// Author 1 and ID and Group: Eslam Amin Mostafa 20210064 S15
// Author 2 and ID and Group: Saead Mohamed Mohamed 20210159 S15
// Author 3 and ID and Group: Karim Mohamed Shebl 20210300 S15
// Teaching Assistant:  Nesma Mohamed & Yousra Ayman
// Purpose: 12 filters to make edits on colored bmp images


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image2 [SIZE][SIZE][RGB];
unsigned char image3 [SIZE][SIZE][RGB];

void loadRGBImage (){

char imageFileName[100];
// Get coloured image file name
cout << "Enter Image Name to Process: ";
cin >> imageFileName;
// Add to it .bmp extension and load image
strcat (imageFileName, ".bmp");

// check if file exist or not
ifstream image_exist;
image_exist.open(imageFileName);

if (image_exist)
{
   readRGBBMP(imageFileName, image2);
}
else
{
	cout << "\n invalid name \n";
	cout << " try again: \n ";
	loadRGBImage();
}
}

void loadRGBImage2 (){

    char imageFileName[100];
    // Get coloured image file name
    cout << "Enter Image Name to Process: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    // check if file exist or not
    ifstream image_exist;
    image_exist.open(imageFileName);

    if (image_exist)
    {
       readRGBBMP(imageFileName, image3);
    }
    else
    {
        cout << "\n invalid name \n";
        cout << " try again: \n ";
        loadRGBImage();
    }
}

void saveRGBImage (){

char imageFileName[100];
cout << "Enter New Image Name: ";
cin >> imageFileName;
strcat (imageFileName, ".bmp");
writeRGBBMP(imageFileName, image2);
}

void ConvertBlackAndWhiteRGB(){

for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
            //check if the sum of colors is greater than average or not ....
            //if sum is greater convert it to white
            if (image2[i][j][0] + image2[i][j][1] + image2[i][j][2] > 384){
                image2[i][j][0] = 255;
                image2[i][j][1] = 255;
                image2[i][j][2] = 255;
            }
            //else convert it to black
            else{
                image2[i][j][0] = 0;
                image2[i][j][1] = 0;
                image2[i][j][2] = 0;
            }
        }
    }
}

void flipImageHorizontally(){

    // flip horizontally
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
        swap(image2[i][j],image2[i][SIZE-1-j]);
        }
    }
}

void flipImageVertically(){

    // flip vertically
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j < SIZE; j++) {
            swap(image2[i][j],image2[SIZE-1-i][j]);
        }
    }
}

void mirrorDown(){
    //mirror the down side
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int l = 0 ; l < RGB ; ++l){
                image2[i][j][l]=image2[255-i][j][l];
            }
        }
    }
}

void mirrorUp(){
     //mirror the upper side
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int l = 0 ; l < RGB ; ++l){
                image2[255-i][j][l]=image2[i][j][l];
            }
        }
    }
}

void mirrorLeft(){
    // mirror the left side
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE/2; j++) {
            for (int l = 0 ; l < RGB ; ++l){
                image2[i][255-j][l]=image2[i][j][l];
            }
        }
    }
}

void mirrorRight(){
    //mirror the right side
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE/2; j++) {
            for (int l = 0 ; l < RGB ; ++l){
                image2[i][j][l]=image2[i][255-j][l];
            }
        }
    }
}

void detectImageEdges(){
    //convert black and white
    ConvertBlackAndWhiteRGB();

    // detect the edges
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int l = 0 ; l < RGB ; ++l){
                if(image2[i][j][l] == image2[i][j+1][l]){
                    image2[i][j][l]=255;
                }
                else{
                    image2[i][j][l]=0;
                }
            }
        }
    }
}

void mergeImages()
{
    loadRGBImage2 ();
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                image2[i][j][k] = (image2[i][j][k] + image3[i][j][k])/2;
            }
        }
    }
}


void darken_Lighten()
{
    string s;
    cout << "To darken an image press d\nTo lighten an image press l\n";
    cin >> s;
    if (s == "d")
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    image2[i][j][k] *= 0.5;
                }
            }
        }
    }
    else if (s == "l")
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                 for(int k = 0; k < 3; k++)
                {
                    if (image2[i][j][k] < 170)
                    {
                        image2[i][j][k] *= 1.5;
                    }
                    else
                    {
                        image2[i][j][k] = 255;
                    }
                }
            }
        }
    }
}

void shrink()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                image3[i][j][k] = image2[i][j][k];
            }
        }
    }
    int index_i, index_j, value, new_size;
    cout << "enter a shrink value : ";
    cin >> value;
    new_size = SIZE / value;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                if (i < new_size && j < new_size)
                {
                    image2[i][j][k] = image3[index_i][index_j][k];
                }
                else
                {
                    image2[i][j][k] = 255;
                }

            }
            index_j += value;
        }
        index_j = 0;
        index_i += value;
    }
}

void blurImage()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                image3[i + 1][j + 1][k] = image2[i][j][k];
            }
        }
    }

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
           for (int k = 0; k < 3; k++)
           {
                 image2[i][j][k] = (image3[i][j][k]+image3[i][j+1][k]+image3[i][j+2][k]+image3[i+1][j][k]+image3[i+1][j+2][k]+image3[i+2][j][k]+image3[i+2][j+1][k]+image3[i+2][j+2][k])/9;
           }
        }
    }
}

int main()
{

string choice , flipDetect , mirordetect;
bool isVAlid =true , contin = true;

loadRGBImage ();

while (contin){
    cout<<"\n\n";
    cout<<"Enter The Number of the operation \n";
    cout<<"1- Black & White Filter \n";
    cout<<"3- Merge Images \n";
    cout<<"4- Flip Image \n";
    cout<<"6- Darken or Lighten Image \n";
    cout<<"7- Detect Image Edges \n";
    cout<<"9- Shrink Image \n";
    cout<<"a- Mirror 1/2 Image \n";
    cout<<"c- Blur Image \n";
    cout<<"s- Save the image to a file \n";
    cout<<"0- Exit \n\n";
    cout<<">>>> ";
    cin>>choice;

if (choice == "1"){
   ConvertBlackAndWhiteRGB();
}
else if (choice == "3"){
   mergeImages();
}
else if(choice =="4"){
    cout<<"Flip (h)orizontally or (v)ertically ? \n";
    cin>>flipDetect;

    if(flipDetect == "h"){
        flipImageHorizontally();
    }

    else if(flipDetect == "v"){
        flipImageVertically();
    }
}
else if (choice == "6"){
   darken_Lighten();
}
else if(choice =="7"){
    detectImageEdges();
}
else if(choice =="9"){
    shrink();
}
else if (choice == "a"){
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
    cin>>mirordetect;

    if(mirordetect=="d"){
        mirrorDown();
    }

    else if(mirordetect == "u"){
        mirrorUp();
    }

    else if(mirordetect == "l"){
        mirrorLeft();
    }

    else if(mirordetect == "r"){
        mirrorRight();
    }
}
else if(choice =="c"){
    blurImage();
}

else if (choice == "s"){
    saveRGBImage ();
}

else if (choice == "0") {
    cout<<"HAVE A NICE DAY !! \n";
    contin = false;
}

else {
    cout<<"Please enter a VALID number ";
}
}
    return 0;
}
