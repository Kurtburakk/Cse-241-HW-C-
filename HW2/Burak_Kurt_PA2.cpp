#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using std::cout;   using std::cin;    using std::endl;
using std::string; using std::vector; using std::ifstream; using std::ofstream;

class Image_Editor
{
private:
    int input,input1,input2,input3,input4;
    int columns,rows;
    int  maximum_color_value;
    string image_format;                    // hold to ppm format
    string filename;                        // open file name
    vector<vector<int>> image_value;        // this 2-D vector hold to pixel value
public:
    void startProgram();     // start menu
    void openImage();        // open menu
    void saveImage();        // save menu
    void convertGrayscale(); // scripts menu
};
void Image_Editor::startProgram()
{
    int input;
    do
    {
        cout <<"MAIN MENU"<<endl;
        cout <<"0 - Exit"<<endl;
        cout <<"1 - Open An Image(D)"<<endl;
        cout <<"2 - Save Image Data(D)"<<endl;
        cout <<"3 - Scripts(D)"<<endl;
        do
        {
        cin >> input;
        }while((input<0)||(input>4));  // check input
        
        if(input==0)
        {
        exit(0);
        }
        else if(input==1)
        {
            int input1;
            do
            {
                cout <<"OPEN AN IMAGE MENU"<<endl;
                cout <<"0 - Up"<<endl;
                cout <<"1 - Enter The Name Of The Image File"<<endl;
                cin >> input1;
                if(input1==1)
                {
                    openImage(); // open image function
                }
            }while(input1!=0);
        }
        else if(input==2)
        {
            int input2;
            do
            {
                cout <<"SAVE IMAGE DATA IMAGE MENU"<<endl;
                cout <<"0 - Up"<<endl;
                cout <<"1 - Enter A File Name"<<endl;
                cin >> input2;
                if(input2==1)
                {
                    saveImage(); // save image function
                }
            }while(input2!=0);
        }
        else if(input==3)
        {
            int input3;
            do
            {
                cout <<"SCRIPTS MENU"<<endl;
                cout <<"0 - Up"<<endl;
                cout <<"1 - Convert To Grayscale(D)"<<endl;
                cin >> input3;
                if(input3==1)
                {              
                    do
                    {
                        cout <<"CONVERT TO GRAYSCALE MENU"<<endl;
                        cout <<"0 - Up"<<endl;
                        cout <<"1 - Enter Coefficients For RED GREEN And BLUE Channels."<<endl;
                        cin >> input4;
                        if(input4==1)
                        {
                            convertGrayscale(); // convertGrayscale function
                        }
                    }while(input4!=0);
                }
            }while(input3!=0);
        }
        
    }while(input!=0);
}
void Image_Editor::openImage()
{
    int temp=0,counter=0,i=0,j=0;
    cin >> filename; // get file name
    string image_size;  // hold to rows and columns value

    ifstream myfile;
    myfile.open(filename); // open file
    if (!myfile)
    {
    cout<<"File does not exist."<<endl;
    }
    else
    {
        getline (myfile, image_format); // get ppm format
        getline (myfile, image_size);   // get pixel size
        rows=image_size[0]-48;          // convert rows value char to int
        columns=image_size[2]-48;       // convert rows value char to int
        myfile >> maximum_color_value;  // get maximum size
        image_value.resize(rows, vector<int>(columns*3));  // resize vector according to pixels size (rows,columns)

        while (myfile >> temp)   //take the numbers in order
        {
            image_value[i][j]=temp; // put value in vector
            if(j==columns*3)        // pass other rows
            {
            j=0;
            ++i; // rows value
            }
            ++j;    // slide columns 
        }
        myfile.close();   
    }
}
void Image_Editor::saveImage()
{
    string save_filename;       
    cin >> save_filename;       // take new file name
    int counter=0;
    if(!image_value.empty())    // if we open file and get number, this part active
    {
        ofstream myfile;
        myfile.open (save_filename);
        myfile << image_format<<endl;           // puts ppm format
        myfile << rows <<" "<<columns<<endl;    // puts pixels size
        myfile << maximum_color_value<<endl;    // puts maximum value

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns*3;j++)
            {
                myfile << image_value[i][j]<<" ";   // puts vector value in file 
                ++counter;
                if(counter==3)
                {
                    myfile<<"\t";                   // put tab space each pixels
                    counter=0;
                }
                cout<<counter;
            }
            myfile<<endl;
        }
        myfile.close();
    }
    else
    cout << "You not open any file , it has not any value."<<endl; // if not open before file 
}
void Image_Editor::convertGrayscale()
{
    float c_r, c_g, c_b;
    int RED=0, GREEN=0, BLUE=0,n_RED=0,n_GREEN=0,n_BLUE=0;
    int check_number=0,count = 0;

    if(!image_value.empty())        // if we already opened a file
    {
    cin >> c_r >> c_g >> c_b;

    if (std::cin.fail() || c_r < 0 || c_r >= 1 || c_g < 0 || c_g >= 1 || c_b < 0 || c_b >= 1) // check input valid and int the range[0,1)
    cout << "Invalid input."<<endl;
    else
    check_number=1;         // if input valid

    if(check_number==1)     
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns*3;j++)
            {

                if(j%3==0)
                n_RED=image_value[i][j];      // firs pixel red
                else if(j%3==1)
                n_GREEN=image_value[i][j];    //second pixel green
                else
                {
                n_BLUE=image_value[i][j];     // third pixel blue
                RED=(c_r*n_RED)+(c_g*n_GREEN)+(c_b*n_BLUE); // calculate new value
                GREEN=(c_r*n_RED)+(c_g*n_GREEN)+(c_b*n_BLUE);
                BLUE=(c_r*n_RED)+(c_g*n_GREEN)+(c_b*n_BLUE);

                if(RED>255)   // check is it value bigger than max value
                RED=255;
                if(GREEN>255)
                GREEN=255;
                if(BLUE>255)
                BLUE=255;
                image_value[i][j-2]=RED;    // new calculated value swap old value
                image_value[i][j-1]=GREEN;
                image_value[i][j]=BLUE;
                }
            }
        }
    }
    }
    else
    cout << "You not open any file "<<endl;
}
int main()
{
    Image_Editor first_image;
    first_image.startProgram();
    return 0;
}