#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using std::cout;   using std::cin;    using std::endl;
using std::string; using std::vector; using std::ifstream; using std::ofstream;

class ppmImage
{
private:
    vector<vector<int>> Image_data;                                                                   // this 2-D vector hold to pixel value
    int rows;                                                                                         // row value                
    int columns;                                                                                      // columns value                
    int maximum_color_value=255;                                                                      // maximum value
    string image_format="P3";                                                                         // hold to ppm format
    string image_size;                                                                                // row and columns value hold stirng   
public:                                                                  
    ppmImage();                                                                                       // default constructor
    ~ppmImage();                                                                                      // destructor
    ppmImage(const ppmImage& other);                                                                  // copy constructor
    ppmImage(const string filename_image);                                                            // constructor take parameter file name    
    ppmImage(const int rows, const int columns);                                                      // constructor take parameter size
    int getRows()const {return rows;}                                                                 // return row value
    int getColums()const {return columns;}                                                            // return columns value
    vector<vector<int>> getImage_data()const {return Image_data;}                                     // return Image data  
    bool setSize(const int rows, const int columns);                                                  // setting row,columns and vector size
    int readImage(const string filename_image);                                                       // read file and store object
    int saveImage(const string filename_image)const;                                                  // saves the values in the object to the file
    void print_dimensions();                                                                          // print row and columns number
    int infoIndividualPixels(const int rows, const int columns, const int color);                     // return individual pixels  
    void changePixels(const int color_1, const int color2);                                           // swap two colors  
    void changeIndividualPixels(const ppmImage& source,const int color_choice);                       // take only one color  
    const int& operator () (const int rows, const int columns, const int color)const;                 // operator ()  
    friend const ppmImage operator +(const ppmImage &first_ppmImage,const ppmImage &second_ppmImage); // operator +
    friend const ppmImage operator -(const ppmImage &first_ppmImage,const ppmImage &second_ppmImage); // operator -
    friend std::ostream& operator << (std::ostream& out, const ppmImage& obj);                        // operator <<  
};
ppmImage::ppmImage()
{
    this->columns=0;
    this->rows=0;
}
ppmImage::~ppmImage()
{
    // destructor
}
ppmImage::ppmImage(const ppmImage &other)
{
    this->rows=other.rows;
    this->columns=other.columns;
    (*this).setSize(rows,columns);             // set size vector
    for(int i=0;i<rows;i++)                    // copy Image_data vector
        for(int j=0;j<columns*3;j++)
        this->Image_data[i][j]=other.Image_data[i][j];
}
ppmImage::ppmImage(const string filename_image)
{
    int valid=0;
    if(readImage(filename_image)) //read file and store values int the object
        ++valid;
}
ppmImage::ppmImage(const int rows, const int columns)
{
    if(setSize(rows,columns)) // set size vector
    {
        for(int i=0;i<rows;i++)
            for(int j=0;j<columns*3;j++)
            Image_data[i][j]=255;       // white image
    }
    else
        cout << "Invalid input."<<endl;
}
bool ppmImage::setSize(const int rows, const int columns)
{
    if((rows>0)&&(columns>0))
    {
        this->rows=rows;
        this->columns=columns;
        for (int i = 0; i < rows; i++) 
        {
            vector<int> temp_row;               
            for (int j = 0; j < columns*3; j++) 
            temp_row.push_back(0);              // create vector columns
            Image_data.push_back(temp_row);     // puts vector rows
        }
        return true;
    }
    else
    {
        cout << "Invalid input."<<endl;
        return false;
    }
}
int ppmImage::readImage(const string filename_image)
{
    int temp=0,i=0,j=0;
    ifstream myfile;
    myfile.open(filename_image); // open file
    if (!myfile)
    {
        cout<<"File does not exist."<<endl;
        return 0;
    }
    else
    {
        getline (myfile, image_format); // get ppm format
        getline (myfile, image_size);   // get pixel size
        rows=image_size[0]-48;          // convert rows value char to int
        columns=image_size[2]-48;       // convert rows value char to int
        myfile >> maximum_color_value;  // get maximum size
        (*this).setSize(rows,columns);  //
        while (myfile >> temp)          //take the numbers in order
        {
            Image_data[i][j]=temp;      // put value in vector
            ++j;                        // slide columns
            if(j==columns*3)            // pass other rows
            {
            j=0;++i;                    // rows value
            }
        }
        myfile.close();
        return 1; 
    }
}
int ppmImage::saveImage(const string filename_image) const
{
    if(!Image_data.empty())                     // if we open file and get number, this part active
    {
        int counter=0;
        ofstream myfile;
        myfile.open (filename_image);
        myfile << image_format<<endl;           // puts ppm format
        myfile << rows <<" "<<columns<<endl;    // puts pixels size
        myfile << maximum_color_value<<endl;    // puts maximum value

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<columns*3;j++)
            {
                myfile << Image_data[i][j]<<" ";   // puts vector value in file 
                ++counter;
                if(counter==3)
                {
                    myfile<<"\t";                   // put tab space each pixels
                    counter=0;
                }
            }
            myfile<<endl;
        }
        myfile.close();
        return 1;
    }
    else
    {
    cout << "You not open any file , it has not any value."<<endl; // if not open before file 
    return 0;
    }
}

void ppmImage::print_dimensions()
{
    if(!Image_data.empty())    // if we open file and get number, this part active
        cout << "Rows: " << rows << " Columns: " << columns << endl;
    else
        cout << "You not open any file , it has not any value."<<endl; // if not open before file
}

int ppmImage::infoIndividualPixels(const int rows, const int columns, const int color)
{
    return this->Image_data[rows][(columns*3)+color-1]; // return individual pixels value
}

void ppmImage::changePixels(const int first_color, const int second_color)
{
    int temp=0,j=0;
    for (int i = 0; i < rows; i++)
        {
            while(j < columns)  // this part swap colors
            {
                temp = (*this)(i,j,first_color);
                this->Image_data[i][(j*3)+first_color-1] = (*this)(i,j,second_color);
                this->Image_data[i][(j*3)+second_color-1] =temp;
                j++;
            }
            j=0;
        }
}
void ppmImage::changeIndividualPixels(const ppmImage& source,const int color_choice)
{       
    for(int i=0;i<this->getRows();i++)
    {
        for(int j=0;j<this->getColums()*3;j++) 
        {
            if(j % 3 == color_choice-1)                                 
                this->Image_data[i][j] = source(i,(j/3),color_choice);  // this part store only one color value
            else
                this->Image_data[i][j]=0;                               // other value equal to zero        
        }
    }
}
const int& ppmImage::operator()(const int rows, const int columns, const int color) const 
{
    return this->Image_data[rows][(columns*3)+color-1];                 // operator () overload return individual pixels
}

std::ostream& operator <<(std::ostream& out, const ppmImage& obj)
{
    out << obj.image_format<<'\n';               // prints ppm format
    out << obj.rows <<" "<<obj.columns<<'\n';    // prints pixels size
    out << obj.maximum_color_value<<'\n';        // prints maximum value
    for(int i=0;i<obj.rows;i++)
    {
        for(int j=0;j<obj.columns*3;j++)
        {
            out<<obj.Image_data[i][j]<<" ";      // print pixels value
        }
        out<<'\n';
    }
    return out;
}

const ppmImage operator +(const ppmImage &first_ppmImage,const ppmImage &second_ppmImage)
{
    ppmImage temp;
    if(((first_ppmImage.rows==second_ppmImage.rows)&&(first_ppmImage.columns==second_ppmImage.columns))&&(first_ppmImage.rows!=0))
    {   // it check size equal and it check object empty
        temp.setSize(first_ppmImage.rows,first_ppmImage.columns);   // this function set vector size
        for (int i = 0; i < temp.rows; i++)
        {
            for (int j = 0; j < temp.columns*3; j++)
            {
                temp.Image_data[i][j] = first_ppmImage.Image_data[i][j] + second_ppmImage.Image_data[i][j]; // this part add each pixel value
                if(temp.Image_data[i][j]>temp.maximum_color_value)      // this part check max value
                temp.Image_data[i][j]=temp.maximum_color_value;
            }
        }
        return temp;
    }
    else
        return temp; // if it size not equal, return empty object
}
const ppmImage operator -(const ppmImage &first_ppmImage,const ppmImage &second_ppmImage)
{
    ppmImage temp;
    if(((first_ppmImage.rows==second_ppmImage.rows)&&(first_ppmImage.columns==second_ppmImage.columns))&&(first_ppmImage.rows!=0))
    {   // it check size equal and it check object empty
        temp.setSize(first_ppmImage.rows,first_ppmImage.columns); // this function set vector size
        for (int i = 0; i < temp.rows; i++)
        {
            for (int j = 0; j < temp.columns*3; j++)
            {
                temp.Image_data[i][j] = first_ppmImage.Image_data[i][j] - second_ppmImage.Image_data[i][j]; // this part add each pixel value
                if(temp.Image_data[i][j]<0) // this part check min value
                temp.Image_data[i][j]=0;
            }
        }
        return temp;
    }
    else
        return temp; // if it size not equal, return empty object
}
int read_ppm(const string source_ppm_file_name,ppmImage& destination_object);                                   // reads file
int write_ppm(const string destination_ppm_file_name,const ppmImage& source_object);                            // write file
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);    // add two object
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3); // subtrat two object
int test_print(const string filename_image1);                                                                   // print object << operator overload
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);                                      // swap colors
ppmImage single_color(const ppmImage& source, int color_choice);                                                // read only one color    

int main(int argc, char** argv)
{
    int choice=argv[1][0]-48;   // choice number
    ppmImage image;             // default object
    if(choice==1)
    {
        if(argc==5)             // check file numbers
        test_addition(argv[2],argv[3],argv[4]);
        else
        exit(0);
    }
    else if(choice==2)
    {
        if(argc==5)             // check file numbers
        test_subtraction(argv[2],argv[3],argv[4]);
        else
        exit(0);
    }
    else if(choice==3)
    {
        image.readImage(argv[2]);
        if(swap_channels(image,2))
            write_ppm(argv[3],image);
    }
    else if(choice==4)
    {
        image.readImage(argv[2]);
        if(swap_channels(image,3))
            write_ppm(argv[3],image);
    }
    else if(choice==5)
    {
        image.readImage(argv[2]);
        write_ppm(argv[3],single_color(image,1));
    }
    else if(choice==6)
    {
        image.readImage(argv[2]);
        write_ppm(argv[3],single_color(image,2));
    }
    else if(choice==7)
    {
        image.readImage(argv[2]);
        write_ppm(argv[3],single_color(image,3));
    }
    return 0;
}
int read_ppm(const string source_ppm_file_name, ppmImage& destination_object)
{
    if(destination_object.readImage(source_ppm_file_name)) // read file and store value in the destination_object
    return 1;
    else 
    return 0;
}
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object)
{
    if(source_object.saveImage(destination_ppm_file_name))  // save file on to objects in the source objects value
    return 1;
    else 
    return 0;
}
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage image1(filename_image1),image2(filename_image2),image3(filename_image3);   // constructor take parameter file name
    image3 = image1 + image2; // add operator overload
    if(write_ppm(filename_image3,image3)) // write result on the file name3
    return 1;
    else
    return 0;
}
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage image1(filename_image1),image2(filename_image2),image3(filename_image3);   // constructor take parameter file name
    image3 = image1 - image2; // subtract operator oveload
    if(write_ppm(filename_image3,image3)) // write result on the file name3
    return 1;
    else
    return 0;
}
int test_print(const string filename_image1)
{
    ppmImage image1;
    if(read_ppm(filename_image1,image1)) // read file
    {
    cout << image1;        // << operator overload <<
    return 1;
    }
    else
    return 0; 
}
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice)
{
    int con=0; // check operation successful
    if(swap_choice==1)
    {image_object_to_be_modified.changePixels(1,2);++con;}  // swaps red and green
    if (swap_choice==2)
    {image_object_to_be_modified.changePixels(1,3);++con;}  // swaps red and blue
    if (swap_choice==3)
    {image_object_to_be_modified.changePixels(2,3);++con;}  // swaps green and blue
    if(con==1)
    return 1;
    else 
    return 0; 
}
ppmImage single_color(const ppmImage& source, int color_choice)
{
    ppmImage new_image(source.getRows(),source.getColums());    // create empty object with takes parameters size 
    new_image.changeIndividualPixels(source,color_choice);      // stores only one color
    return new_image;                                           // return one color object            
}