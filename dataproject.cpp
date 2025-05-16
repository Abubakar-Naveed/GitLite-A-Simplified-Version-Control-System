#include<iostream>
#include<fstream>
#include <direct.h>
#include<cstring>
#include <string>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;

struct rootn
{
    char** rootname = new char* [12];
    rootn()
    {
        for (int i = 0; i < 12; i++)
        {
            rootname[i] = new char[30];
        }
    }


};

// read row from  CSV file

// Function to create a new folder
void createFolder()

{
    // Folder name
    const char* folderName = "MyNewFolder";

    // Create a new folder
    if (_mkdir(folderName) == 0) {
      //  cout << "Folder created successfully!" << endl;
    }
    else {
        perror("Error creating folder");
    }
}


/// AVL Tree ///
class AVLTree
{
public:
    /// make file in folder ///
    char* rootFileName;
    char* orignalRootFileName;
    
  
     int column;
     int value;
    int rownum;
     int hight;
     char* fouldername;

    AVLTree()
    {
        rootFileName = NULL;
        orignalRootFileName = new char[30];
       
        column = 0;
        value = 0;
        rownum = 0;
        hight = 0;
        fouldername = new char[30];
    }
    long long int getsize(char* array)
    {
        long long int i = 0;
        while (array[i] != '\0')
        {
            i++;
        }
        return i;
    }
    long long int max(long long int a, long long int b)
    {
        return (a > b) ? a : b;
    }
    /// <summary>
    ///  hash function which multiply all char of string and return the value
    /// </summary>
    char* hashname(char* array) {
        long long int k = 1;
        char* temp = new char[50];
        long long int sizee = getsize(array);
        for (long long int i = 0; i < sizee; i++) {
            if (array[i] == ',') {
                k++;
            }
            if (k == column) {
                for (long long int j = 0; j < 20; j++, i++) {
                    temp[j] = array[i];
                    if (array[i + 1] == ',') {
                        // Convert rownum to string and append
                        char rownumStr[10];
                        sprintf_s(rownumStr, sizeof(rownumStr), "%lld", rownum);

                        // Add underscore
                        temp[j + 1] = '_';

                        // Copy rownum string after underscore
                        strcpy_s(temp + j + 2, 50 - (j + 2), rownumStr);

                        break;
                    }
                }
                break;
            }
        }     
		

        return temp;
    }
    long long int convertHashToInteger(char* hasharray)
    {
        // Check for null or empty input
        if (hasharray == nullptr || hasharray[0] == '\0')
        {
            return 0;
        }

        // Use standard library function to convert string to integer
        long long int result = atoi(hasharray);

        return result;
    }
    long long int comparee(char* filenamee, char* Rootfilename)
    {
        char* numbers = new char[5];
        // for filename
        int hash = 1;
        for (int i = 0; i < getsize(filenamee); i++)
        {
            if (filenamee[i] == '_')
            {
                numbers[i] = '\0';
                break;
            }
			numbers[i] = filenamee[i];
           

        }
      
        char* numbers2 = new char[6];
        hash = 1;
        for (int i = 0; i < getsize(Rootfilename); i++)
        {
            if (Rootfilename[i] == '_')
            {
                numbers2[i] = '\0';
                break;
            }
           
			numbers2[i] = Rootfilename[i];

        }
        hash = hash % 9999999;
        hash *= rownum;
        

		long long int result1 = atoi(numbers);
		long long int result2 = atoi(numbers2);


        if (result1 > result2)
        {
            return 1;
        }
        else if (result1 < result2)
        {
            return -1;
        }
        else if (result1 == result2)
        {
            return 0;
        }

    }

   
  /*  long long int comparee(char* filename, char* RootFileName)
    {
        long long int result1 = atoi(filename);
        long long int result2 = atoi(RootFileName);
        if (result1 > result2)
        {
            return 1;
        }
        else if (result1 < result2)
        {
            return -1;
        }
        else if (result1 == result2)
        {
            return 0;
        }

    }*/
    char* hashforduplicate(char* array)
    {
        long long int size = getsize(array);
        long long int hash = 1;
        for (long long int i = 0; i < size; i++)
        {
            hash = hash + array[i];
            hash = hash % 9999999;
        }
        hash = hash * rownum;
        char* hasharray = new char[100];
        sprintf_s(hasharray, 100, "%d", hash);
        hasharray[getsize(hasharray)] = '\0';
        hasharray[0] = 'd';
        return hasharray;
    }


    void  InsertInAvL(char* filename, char* data, int& g) {


        //// insertion for root  
        if (rootFileName == NULL) {
            rootFileName = filename;
            ofstream file;
            char* fullpathh = fullpath(filename, fouldername);
            file.open(fullpathh, ios::out | ios::trunc);

            file << data << "\n";       // Store data
            file << "1\n";             // Left child
            file << "1\n";             // Right child
            file << "ROOT\n";          // Parent file name (ROOT for the root file)
            file << "1\n";             // Height of root (1 for leaf)
            file.close();
        }
        else {

             InsertRecursively(rootFileName, filename, data, g);



            /*ifstream file;
            file.open(fullpath(rootFileName));
            char* dataa = new char[500];
            char* leftchild = new char[30];
            char* rightchild = new char[30];
            char* parent = new char[30];

            char* hei = new char[2];

            file.getline(dataa, 500);
            file.getline(leftchild, 30);
            file.getline(rightchild, 30);
            file.getline(parent, 30);
            file.getline(hei, 2);
            file.close();

            long long int maxheight = 0;
            if (strcmp(parent, "ROOT") == 0)
            {

                ofstream filee;
                char* fullpathh = fullpath(rootFileName);
                filee.open(fullpathh);
                
                maxheight = max(getheight(rightchild), getheight(leftchild))+1;
                filee << data << "\n";
                filee << leftchild << "\n";
                filee << rightchild << "\n";
                filee << parent << "\n";
                filee << maxheight << "\n";
            }
            else
            {
                strcpy_s(rootFileName, 30, parent);
				cout << "root change  " << rootFileName << endl;
				cout << "root height  " << maxheight << endl;
            }
            */
            return;

        }
        return;
    }

    void  InsertRecursively(char* RootFileName, char* filename, char* data, int& g)
    {
        //open file

            //// extraction of data from the current file   (rootfilename = currentfile )   // dont confuse it with root file
        ifstream file;
        char* fullname = fullpath(RootFileName, fouldername);
        file.open(fullname);
        char* dataa = new char[500];
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];

        long long int maxheight = 0;
        long long int height;
        char* hei = new char[3];

        file.getline(dataa, 500);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.getline(hei, 3);
        height = convertHashToInteger(hei);
        file.close();

        //// this is the condition when we enconter the senario of duplicate file name  
       
        // Compare the filename with the current node's filename      // actullay convert the string to integer and then compare
        long long int compare = comparee(filename, RootFileName);

        // If the filename is less than the current node's filename
        if (compare < 0)
        {
            // If the left child is a leaf node
            if (strcmp(leftchild, "1") == 0)
            {
                // Open the file
                // Update the left child of the current node

                // second last file     
                ofstream file1;
                char* fullpathh1 = fullpath(RootFileName, fouldername);
                file1.open(fullpathh1);
                file1 << dataa << "\n";       // Store data
                file1 << filename << "\n";   // Left child
                file1 << rightchild << "\n"; // Right child
                file1 << parent << "\n";     // Parent file name
                file1 << "2\n";              // Height of the current node
                file1.close();

             //   cout << "inserting left of " << RootFileName << endl;
                /// new file 
                // Create a new file for the new node
                ofstream file2;
                char* fullpathh2 = fullpath(filename, fouldername);
                file2.open(fullpathh2);
                file2 << data << "\n";       // Store data
                file2 << "1\n";              // Left child
                file2 << "1\n";              // Right child
                file2 << RootFileName << "\n"; // Parent file name
                file2 << "1\n";              // Height of the new node
                file2.close();
                g = 0;
                
                // Update the height of the current node
            }
            else
            {
                // Recursively insert the new node in the left subtree
                 InsertRecursively(leftchild, filename, data, g);

                // update the height of the current node
               
                ////

                // open above file and write maxheight height at the end of file

                /// update the height of the current node

                ifstream file10;
                char* fullpathh1 = fullpath(RootFileName, fouldername);
                file10.open(fullpathh1);
                file10.getline(dataa, 500);
                file10.getline(leftchild, 30);
                file10.getline(rightchild, 30);
                file10.getline(parent, 30);
                file10.getline(hei, 3);
                file10.close();

                long long int rightheight = getheight(rightchild);
                int leftheight = getheight(leftchild);
                maxheight = max(leftheight, rightheight) + 1;


                // write all values same here except .. only height is changed
                ofstream file1;

                file1.open(fullpathh1);
                file1 << dataa << "\n";       // Store data
                file1 << leftchild << "\n";   // Left child
                file1 << rightchild << "\n"; // Right child
                file1 << parent << "\n";     // Parent file name
                file1 << maxheight << "\n";              // Height of the current node
                file1.close();



            }


        }
        else
        {
            // If the right child is a leaf node
            if (strcmp(rightchild, "1") == 0)
            {
                // Open the file
                // Update the right child of the current node
                ofstream file1;
                char* fullpathh1 = fullpath(RootFileName, fouldername);
                file1.open(fullpathh1);
                file1 << dataa << "\n";       // Store data
                file1 << leftchild << "\n";   // Left child
                file1 << filename << "\n";   // Right child
                file1 << parent << "\n";     // Parent file name
                file1 << "2\n";              // Height of the current node
                file1.close();

               // cout << "inserting right of " << RootFileName << endl;
                // Create a new file for the new node
                ofstream file2;
                char* fullpathh2 = fullpath(filename, fouldername);
                file2.open(fullpathh2);
                file2 << data << "\n";       // Store data
                file2 << "1\n";              // Left child
                file2 << "1\n";              // Right child
                file2 << RootFileName << "\n"; // Parent file name
                file2 << "1\n";              // Height of the new node
                file2.close();
                g = 0;
               
                // Update the height of the current node
            }
            else
            {
                // Recursively insert the new node in the right subtree
                InsertRecursively(rightchild, filename, data, g);
                // update the height of the current node






               
                // open above file and write maxheight height at the end of file

                ifstream file10;
                char* fullpathh1 = fullpath(RootFileName, fouldername);
                file10.open(fullpathh1);
                file10.getline(dataa, 500);
                file10.getline(leftchild, 30);
                file10.getline(rightchild, 30);
                file10.getline(parent, 30);
                file10.getline(hei, 3);
                file10.close();

                long long int leftheight = getheight(leftchild);
                int rightheight = getheight(rightchild);
                maxheight = max(leftheight, rightheight) + 1;



                ofstream file1;
                file1.open(fullpathh1);
                file1 << dataa << "\n";       // Store data
                file1 << leftchild << "\n";   // Left child
                file1 << rightchild << "\n"; // Right child
                file1 << parent << "\n";     // Parent file name
                file1 << maxheight << "\n";              // Height of the current node
                file1.close();





            }
        }


        long long int balancefactor = getbalancefator(RootFileName);
		//cout << "BALacne factor :" << balancefactor <<"   "<<RootFileName  << endl;

        if (balancefactor > 2 || balancefactor < -2)
        {
			cout << "balafactor                " << balancefactor <<"    " <<RootFileName<< endl;
            system("pause");
        }

        if ((balancefactor == 2  ))
        {
            // 19_222
            int   a = comparee(filename, leftchild);
		//	cout << "value of compare   " << a << endl;
         //   cout<<"i am here"<<endl;
        }
        /// below are the conditon for calling the left rotation and right rotation 


        if (balancefactor > 1 && comparee(filename, leftchild) < 0)
        {
            // Single right rotation
		//	cout << "value of compare  " << comparee(filename, leftchild) << endl;
		  //      cout << "right rotation " << RootFileName << endl;
             rightrotation(RootFileName);
        }
        // Right Right Case
        else if (balancefactor < -1 && comparee(filename, rightchild) >= 0)
        {
            // Single left rotation
		///	cout << "value of compare  " << comparee(filename, rightchild) << endl;
		//	cout << "left rotation " << RootFileName << endl;
             leftrotation(RootFileName);

        }
        // Left Right Case (Double Rotation)
        else if (balancefactor > 1 && comparee(filename, leftchild) >= 0)
        {



            // First, perform left rotation on the left child
            /// open left child AND SAVE  rightchild name
            ifstream file5;
            char* left_data = new char[200];
            char* left_leftchild = new char[30];
            char* left_rightchild = new char[30];
            char* left_parent = new char[30];
            char* left_hei = new char[3];
            long long int left_height;
            char* left_fullname = fullpath(leftchild, fouldername);
            file5.open(left_fullname);
            file5.getline(left_data, 200);
            file5.getline(left_leftchild, 30);
            file5.getline(left_rightchild, 30);
            file5.getline(left_parent, 30);
            file5.getline(left_hei, 3);
            left_height = convertHashToInteger(left_hei);
            file5.close();
            // perform left rotation on left child

			//cout << "value of compare  " << comparee(filename, leftchild) << endl;
		//	cout << "left rotation on left child" << leftchild << endl;
            leftrotation(leftchild);
            // Then perform right rotation on the 
            // char* Fullname = fullpath(leftchild);

			//cout << "right rotation on root" << RootFileName << endl;
            rightrotation(RootFileName);



            // delete all memory
            delete[] left_data;
            delete[] left_leftchild;
            delete[] left_rightchild;
            delete[] left_parent;
            delete[] left_hei;


        }
        // Right Left Case (Double Rotation)
        else if (balancefactor < -1 && comparee(filename, rightchild) < 0)
        {

            ifstream file9;
            char* right_data = new char[200];
            char* right_leftchild = new char[30];
            char* right_rightchild = new char[30];
            char* right_parent = new char[30];
            char* right_hei = new char[3];
            long long int right_height;
            char* right_fullname = fullpath(rightchild, fouldername);
            file9.open(right_fullname);
            file9.getline(right_data, 200);
            file9.getline(right_leftchild, 30);
            file9.getline(right_rightchild, 30);
            file9.getline(right_parent, 30);
            file9.getline(right_hei, 2);
            right_height = convertHashToInteger(right_hei);
            file9.close();

			//cout << "value of compare  " << comparee(filename, rightchild) << endl;
			//cout << "right rotation on right child" << rightchild << endl;
            // First, perform right rotation on the right child
            rightrotation(rightchild);



			//cout << "left rotation on root" << RootFileName << endl;
            // Then perform left rotation on the root
            leftrotation(RootFileName);


            // delete all memory
            delete[] right_data;
            delete[] right_leftchild;
            delete[] right_rightchild;
            delete[] right_parent;
            delete[] right_hei;


        }

        // memory delete
        delete[] dataa;
        delete[] leftchild;
        delete[] rightchild;
        delete[] parent;
        delete[] hei;

       // cout << endl;
        return ;
    }

    void  leftrotation(char* current)
    {
        long long int check = 0;


        char* data = new char[200];
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];
        char* hei = new char[3];
        long long int height;
        ifstream file;
        char* fullname = fullpath(current, fouldername);
        file.open(fullname);
        file.getline(data, 200);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.getline(hei, 3);
        height = convertHashToInteger(hei);
        file.close();


        ///// right child of current node


        char* data_rightchild = new char[200];
        char* leftchild_rightchild = new char[30];
        char* rightchild_rightchild = new char[30];
        char* parent_rightchild = new char[30];
        char* hei_rightchild = new char[3];
        long long int height_rightchild;

        ifstream file_rightchild;
        char* fullname_rightchild = fullpath(rightchild, fouldername);

        file_rightchild.open(fullname_rightchild);
        file_rightchild.getline(data_rightchild, 200);
        file_rightchild.getline(leftchild_rightchild, 30);
        file_rightchild.getline(rightchild_rightchild, 30);
        file_rightchild.getline(parent_rightchild, 30);
        file_rightchild.getline(hei_rightchild, 3);
        height_rightchild = convertHashToInteger(hei_rightchild);
        file_rightchild.close();


        long long int temp = convertHashToInteger(leftchild_rightchild);
        if (temp != 1)
        {

            check = 1;
            ///// left child of right child of current node
            char* data_rightchildleft = new char[200];
            char* leftchild_rightchildleft = new char[30];
            char* rightchild_rightchildleft = new char[30];
            char* parent_rightchildleft = new char[30];
            char* hei_rightchildleft = new char[3];
            long long int height_rightchildleft;
            ifstream file_rightchildleft;

            char* fullname_rightchildleft = fullpath(leftchild_rightchild, fouldername);
            file_rightchildleft.open(fullname_rightchildleft);

            char* rightchildleft = new char[30];
            file_rightchildleft.getline(data_rightchildleft, 200);
            file_rightchildleft.getline(leftchild_rightchildleft, 30);
            file_rightchildleft.getline(rightchild_rightchildleft, 30);
            file_rightchildleft.getline(parent_rightchildleft, 30);
            file_rightchildleft.getline(hei_rightchildleft, 3);
            height_rightchildleft = convertHashToInteger(hei_rightchildleft);
            file_rightchildleft.close();

            ////// update the parent of left child of current node  node

            // current ku update karna hai
            ofstream file1;
            char* fullpathh1 = fullpath(current, fouldername);
            file1.open(fullpathh1);
            file1 << data << "\n";       // Store data
            file1 << leftchild << "\n";   // Left child
            file1 << leftchild_rightchild << "\n"; // Right child
            file1 << rightchild << "\n";  // update parent of current node

            long long int heiii = max(getheight(leftchild), getheight(leftchild_rightchild)) + 1;
            file1 << heiii << "\n";

            file1.close();



            /// update parent of left child of right child of current node
            ofstream file2;
            char* fullpathh2 = fullpath(leftchild_rightchild, fouldername);
            file2.open(fullpathh2);
            file2 << data_rightchildleft << "\n";       // Store data
            file2 << leftchild_rightchildleft << "\n";   // Left child
            file2 << rightchild_rightchildleft << "\n"; // Right child
            file2 << current << "\n";  // update parent of current node
            long long int heiiii = max(getheight(leftchild_rightchildleft), getheight(rightchild_rightchildleft)) + 1;
            file2 << heiiii << "\n";
            file2.close();

            /// delete memory 
            delete[]data_rightchildleft;
            delete[]leftchild_rightchildleft;
            delete[]rightchild_rightchildleft;
            delete[]parent_rightchildleft;
            delete[]hei_rightchildleft;





        }

        if (check == 0)
        {
            ofstream file1;
            char* fullpathh1 = fullpath(current, fouldername);
            file1.open(fullpathh1);
            file1 << data << "\n";       // Store data
            file1 << leftchild << "\n";   // Left child
            file1 << "1" << "\n"; // Right child
            file1 << rightchild << "\n";  // update parent of current node
            char* Leftchild_rightchild = new char[1];
            Leftchild_rightchild[0] = '1';
            long long int heiii = max(getheight(leftchild), getheight(Leftchild_rightchild)) + 1;
            file1 << heiii << "\n";
            file1.close();

        }

        ofstream file4;
        char* fullname4 = fullpath(rightchild, fouldername);
        file4.open(fullname4);

        file4 << data_rightchild << "\n";       // Store data
        file4 << current << "\n";
        file4 << rightchild_rightchild << "\n";
        file4 << parent << "\n";

        long long int heii = max(getheight(current), getheight(rightchild_rightchild) + 1);
        file4 << heii << "\n";
        file4.close();

        if (strcmp(parent, "ROOT") != 0)
        {
            ifstream file10;
            char* fullname = fullpath(parent, fouldername);
            char* parent_data = new char[200];
            char* prent_right = new char[30];
            char* prent_left = new char[30];
            char* prent_prent = new char[30];
            char* prent_heii = new char[3];

            long long int prent_height;
            file10.open(fullname);
            file10.getline(parent_data, 200);
            file10.getline(prent_left, 30);
            file10.getline(prent_right, 30);
            file10.getline(prent_prent, 30);
            file10.getline(prent_heii, 3);
            prent_height = convertHashToInteger(prent_heii);
            file10.close();

            /*ofstream file11;
            file11.open(fullname);
            file11 << parent_data << "\n";
            file11 << prent_left << "\n";
            file11 << rightchild << "\n";
            file11 << prent_prent << "\n";
            file11 << prent_height << "\n";
            file11.close();*/

            ofstream file11;
            file11.open(fullname);
            if (strcmp(prent_left, current) == 0)
            {
                file11 << parent_data << "\n";
                file11 << rightchild << "\n";
                file11 << prent_right << "\n";
                file11 << prent_prent << "\n";
                int height = max(getheight(rightchild), getheight(prent_right)) + 1;
                file11 << height << "\n";
                file11.close();
            }
            else
            {
                file11 << parent_data << "\n";
                file11 << prent_left << "\n";
                file11 << rightchild << "\n";
                file11 << prent_prent << "\n";
                int height = max(getheight(rightchild), getheight(prent_left)) + 1;
                file11 << height << "\n";
                file11.close();
            }



            // delete all memory
            delete[] parent_data;
            delete[] prent_right;
            delete[] prent_left;
            delete[] prent_prent;
            delete[] prent_heii;

        }
        else
		{
			strcpy_s(rootFileName, 30, rightchild);
         //   cout << "Root chnage"<< rootFileName <<endl;
		}
        // update curent  in parent 


        // delete memory
        delete[] data;
        delete[] leftchild;
        delete[] rightchild;
        delete[] parent;
        delete[] hei;

        delete[] data_rightchild;
        delete[] leftchild_rightchild;
        delete[] rightchild_rightchild;
        delete[] parent_rightchild;
        delete[] hei_rightchild;


        return ;

    }

    void  rightrotation(char* current) {
        long long int check = 0;
        char* data = new char[200];
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];
        char* hei = new char[3];
        long long int height;

        ifstream file;
        char* fullname = fullpath(current, fouldername);
        file.open(fullname);
        file.getline(data, 200);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.getline(hei, 3);
        height = convertHashToInteger(hei);
        file.close();

        ///// Left child of the current node
        char* data_leftchild = new char[200];
        char* leftchild_leftchild = new char[30];
        char* rightchild_leftchild = new char[30];
        char* parent_leftchild = new char[30];
        char* hei_leftchild = new char[3];
        long long int height_leftchild;

        ifstream file_leftchild;
        char* fullname_leftchild = fullpath(leftchild, fouldername);
        file_leftchild.open(fullname_leftchild);
        file_leftchild.getline(data_leftchild, 200);
        file_leftchild.getline(leftchild_leftchild, 30);
        file_leftchild.getline(rightchild_leftchild, 30);
        file_leftchild.getline(parent_leftchild, 30);
        file_leftchild.getline(hei_leftchild, 3);
        height_leftchild = convertHashToInteger(hei_leftchild);
        file_leftchild.close();

        long long int temp = convertHashToInteger(rightchild_leftchild);
        if (temp != 1) {
            check = 1;

            ///// Right child of the left child of the current node
            char* data_leftchildright = new char[200];
            char* leftchild_leftchildright = new char[30];
            char* rightchild_leftchildright = new char[30];
            char* parent_leftchildright = new char[30];
            char* hei_leftchildright = new char[3];
            long long int height_leftchildright;

            ifstream file_leftchildright;
            char* fullname_leftchildright = fullpath(rightchild_leftchild, fouldername);
            file_leftchildright.open(fullname_leftchildright);
            file_leftchildright.getline(data_leftchildright, 200);
            file_leftchildright.getline(leftchild_leftchildright, 30);
            file_leftchildright.getline(rightchild_leftchildright, 30);
            file_leftchildright.getline(parent_leftchildright, 30);
            file_leftchildright.getline(hei_leftchildright, 3);
            height_leftchildright = convertHashToInteger(hei_leftchildright);
            file_leftchildright.close();

            /// Update the current node's left child
            ofstream file1;
            char* fullpathh1 = fullpath(current, fouldername);
            file1.open(fullpathh1);
            file1 << data << "\n";
            file1 << rightchild_leftchild << "\n";   // Update left child
            file1 << rightchild << "\n";             // Keep current right child
            file1 << leftchild << "\n";              // Update parent of the current node
            long long int heiii = max(getheight(rightchild_leftchild), getheight(rightchild)) + 1;
            file1 << heiii << "\n";
            file1.close();

            /// Update parent of right child of the left child of the current node
            ofstream file2;
            char* fullpathh2 = fullpath(rightchild_leftchild, fouldername);
            file2.open(fullpathh2);
            file2 << data_leftchildright << "\n";
            file2 << leftchild_leftchildright << "\n";
            file2 << rightchild_leftchildright << "\n";
            file2 << current << "\n";  // Set parent as current node
            long long int heiiii = max(getheight(leftchild_leftchildright), getheight(rightchild_leftchildright)) + 1;
            file2 << heiiii << "\n";
            file2.close();


            /// delete all memeroy
            delete[] data_leftchildright;
            delete[] leftchild_leftchildright;
            delete[] rightchild_leftchildright;
            delete[] parent_leftchildright;
            delete[] hei_leftchildright;


        }

        if (check == 0) {
            /// Update current node directly when no right child of the left child exists
            ofstream file1;
            char* fullpathh1 = fullpath(current, fouldername);
            file1.open(fullpathh1);
            file1 << data << "\n";
            file1 << "1\n";                  // Left child is now null
            file1 << rightchild << "\n";     // Keep the current right child
            file1 << leftchild << "\n";      // Update parent
            long long int heiii = max(0, getheight(rightchild)) + 1;
            file1 << heiii << "\n";
            file1.close();
        }

        /// Update the left child to become the new root
        ofstream file4;
        char* fullname4 = fullpath(leftchild, fouldername);
        file4.open(fullname4);
        file4 << data_leftchild << "\n";
        file4 << leftchild_leftchild << "\n";
        file4 << current << "\n";          // Current node becomes the right child
        file4 << parent << "\n";           // Update parent
        long long int heii = max(getheight(leftchild_leftchild), getheight(current)) + 1;
        file4 << heii << "\n";
        file4.close();


        if (strcmp(parent, "ROOT") != 0)
        {
            ifstream file10;
            char* fullname = fullpath(parent, fouldername);
            char* parent_data = new char[200];
            char* prent_right = new char[30];
            char* prent_left = new char[30];
            char* prent_prent = new char[30];
            char* prent_heii = new char[3];

            long long int prent_height;
            file10.open(fullname);
            file10.getline(parent_data, 200);
            file10.getline(prent_left, 30);
            file10.getline(prent_right, 30);
            file10.getline(prent_prent, 30);
            file10.getline(prent_heii, 3);
            prent_height = convertHashToInteger(prent_heii);
            file10.close();


            /*
            ofstream file11;
            file11.open(fullname);
            file11 << parent_data << "\n";
            file11 << prent_left << "\n";
            file11 << leftchild << "\n";
            file11 << prent_prent << "\n";
            file11 << prent_height << "\n";
            file11.close();

            */
            ofstream file11;
            file11.open(fullname);
            if (strcmp(prent_left, current) == 0)
            {
                file11 << parent_data << "\n";
                file11 << leftchild << "\n";
                file11 << prent_right << "\n";
                file11 << prent_prent << "\n";
                int height = max(getheight(leftchild), getheight(prent_right)) + 1;
                file11 << height << "\n";
                file11.close();
            }
            else
            {
                file11 << parent_data << "\n";
                file11 << prent_left << "\n";
                file11 << leftchild << "\n";
                file11 << prent_prent << "\n";
                int height = max(getheight(prent_left), getheight(leftchild)) + 1;
                file11 << height << "\n";
                file11.close();
            }





            // delete all memory
            delete[] parent_data;
            delete[] prent_right;
            delete[] prent_left;
            delete[] prent_prent;
            delete[] prent_heii;


        }
		else
		{
			strcpy_s(rootFileName, 30, leftchild);
            //cout << "Root chnage" << rootFileName << endl;
		}

        // delete all memory
        delete[] data;
        delete[] leftchild;
        delete[] rightchild;
        delete[] parent;
        delete[] hei;

        delete[] data_leftchild;
        delete[] leftchild_leftchild;
        delete[] rightchild_leftchild;
        delete[] parent_leftchild;
        delete[] hei_leftchild;



        return ;
    }




    long long int getbalancefator(char* filename)
    {
        char* leftchild = new char[30];
        char* rightchild = new char[30];

        ifstream file;
        char* fullname = fullpath(filename, fouldername);
        file.open(fullname);
        char* dataa = new char[200];

        file.getline(dataa, 200);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.close();

        return (getheight(leftchild) - getheight(rightchild));

    }

    long long int getheight(char* filemane)
    {
        long long int temp = convertHashToInteger(filemane);
        if (temp == 1)
        {
            return 0;

        }

        ifstream file;
        char* fullname = fullpath(filemane, fouldername);
        file.open(fullname);
        char* dataa = new char[200];
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];
        char* hei = new char[3];
        long long int height;
        file.getline(dataa, 200);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.getline(hei, 3);
        height = convertHashToInteger(hei);
        file.close();

        delete[]dataa;
        delete[]leftchild;
        delete[]rightchild;
        delete[]parent;
        delete[]hei;

        return height;
    }

    void  insertdata(ifstream& csvfile)
    {
       
        //fouldername = "MyNewFolder";
		strcpy_s(fouldername, 30, "MyNewFolder");
       
        char* filename = NULL;
        char* data = new char[200];
       
        int a = 50;
        int c =7;
        int g = 0;
       

        
        while (a > 0)
        {
            char* temp = new char[200];
            csvfile.getline(temp, 200);
           

            filename = hashname(temp);
           
             //  cout << filename << endl;
           


            InsertInAvL(filename, temp, g);
            c--;
            
			//cout << "Rownumber : " << rownum << endl;
            /// this is the condition for duplicate data// which i hashed again to remove duplicate name 
          
            rownum++;

            //system("pause");

            delete[]temp;
            a--;

        }

    }


  
    char* fullpath(const char* filename , char* fouldername) {
        char* fullpath = new char[100];

        // Copy folder name to fullpath
        strcpy_s(fullpath, 100, fouldername);

        // Append a "/" to fullpath
        strcat_s(fullpath, 100, "/");

        // Append the filename to fullpath
        strcat_s(fullpath, 100, filename);
        strcat_s(fullpath, 100, ".txt");

        return fullpath;
    }

    // insert data in file

    /// deletion function

   

   
    // this fucntion will add the data of and overwrite it and return it 
    long long int  hashforMurkletree(char* filnemae, char* fouilder)
    {
        ifstream file;
		char* fullname = fullpath(filnemae, fouilder);
		file.open(fullname);
		char* data = new char[200];
		file.getline(data, 200);
		file.close();

		int size = getsize(data);
        long long int hash=0;
		for (int i = 0; i < size; i++)
		{
			hash += data[i];
		}

        if (hash == 0)
        {
            cout << "eheud";
        }
		return hash;

    }

	/// this function will add the data of and overwrite it and return it

    void  recursive_post_order(char* cureent, char* &foulderr)
    {
        
        
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];
        char* hei = new char[3];
        char* data = new char[200];
        ifstream file;
        char* fullname = fullpath(cureent, foulderr);
        file.open(fullname);
        file.getline(data, 200);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.getline(hei, 3);
        file.close();
        long long int data1 = 0;
        long long int data2 = 0;
        
        
        if ((strcmp(leftchild, "1") == 0 )&&( strcmp(rightchild, "1") == 0))
        {

            long long int data10 = hashforMurkletree(cureent, foulderr);
            ofstream file2;
            file2.open(fullname);
            file2 << data10 << "\n";
            file2 << leftchild << "\n";
            file2 << rightchild << "\n";
            file2 << parent << "\n";
            file2 << hei << "\n";
            file2.close();
            return;

        }

        if (strcmp(leftchild, "1") != 0  )
        {
            recursive_post_order(leftchild, foulderr);
            data1 = hashforMurkletree(leftchild, foulderr);

            if (data1==0)
            {
                cout << "helo";
            }

        }
        else if (strcmp(leftchild, "1") == 0)
        {
            data1 = 10;


        }
		 
        

        if (strcmp(rightchild, "1") != 0)
        {
            recursive_post_order(rightchild, foulderr);
            data2 = hashforMurkletree(rightchild, foulderr);

            if (data2 == 0)
            {
                cout << "helo";
            }
        }
		else if (strcmp(rightchild, "1") == 0)
		{
			data2 = 10;
		    
        }
        if (data1 == 0 && data2 == 0)
        {
            cout << "eded";
        }
            
        ofstream file3;
        file3.open(fullname);
		file3 << (data1+ data2)<< "\n";
		file3 << leftchild << "\n";
		file3 << rightchild << "\n";
		file3 << parent << "\n";
		file3 << hei << "\n";
		file3.close();




        

        delete[]leftchild;
        delete[]rightchild;
        delete[]parent;
        delete[]hei;
        delete[]data;


    }


    //////////////

    /// deletion function

     //************************** deletion ****************************
    void FileDeletion(char* filename) {
        // Base case: If the tree is empty
        if (rootFileName == NULL) {
            cout << "Tree is empty, nothing to delete." << endl;
            return;
        }

        DeleteRecursively(rootFileName, filename);
    }

    void DeleteRecursively(char* RootFileName, char* filename) {
        // Open file and extract its contents
        ifstream file;
        char* fullname = fullpath(RootFileName, fouldername);
        file.open(fullname);

        char* dataa = new char[500];
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];
        char* hei = new char[3];

        file.getline(dataa, 500);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.getline(hei, 3);
        file.close();

        long long int compare = comparee(filename, RootFileName);

        if (compare < 0) {
            // Move to left subtree
            if (strcmp(leftchild, "1") != 0) {
                DeleteRecursively(leftchild, filename);
            }
            else {
                cout << "File not found." << endl;
            }
        }
        else if (compare > 0) {
            // Move to right subtree
            if (strcmp(rightchild, "1") != 0) {
                DeleteRecursively(rightchild, filename);
            }
            else {
                cout << "File not found." << endl;
            }
        }
        else {
            // Node to be deleted found
            if (strcmp(leftchild, "1") == 0 && strcmp(rightchild, "1") == 0) {
                // Node is a leaf
                if (strcmp(RootFileName, rootFileName) == 0) {
                    rootFileName = NULL; // if its the root, set it to NULL
                }
                char name[2] = { "1" };
                RemoveNodeFromParent(RootFileName, parent, name);
                remove(fullname); // Delete the file
            }
            else if (strcmp(leftchild, "1") != 0 && strcmp(rightchild, "1") == 0) {
                // Node has only left child
                if (strcmp(RootFileName, rootFileName) == 0) {
                    strcpy_s(rootFileName, 30, leftchild); // Update root if needed
                }
                RemoveNodeFromParent(RootFileName, parent, leftchild);
                remove(fullname); // Delete the file
            }
            else if (strcmp(leftchild, "1") == 0 && strcmp(rightchild, "1") != 0) {
                // Node has only right child
                if (strcmp(RootFileName, rootFileName) == 0) {
                    strcpy_s(rootFileName, 30, rightchild); // Update root if needed
                }
                RemoveNodeFromParent(RootFileName, parent, rightchild);
                remove(fullname); // Delete the file
            }
            else {
                // Node has two children
                char* successor = new char[30];
                FindLeftmostChild(rightchild, successor);

                // Replace the current node's data with successor's data
                char* successorFilepath = fullpath(successor, fouldername);
                ifstream succFile(successorFilepath);

                char* succData = new char[500];
                succFile.getline(succData, 500); // Read successor's data
                succFile.close();

                ofstream currFile(fullname, ios::out | ios::trunc);
                currFile << succData << "\n";
                currFile << leftchild << "\n";
                currFile << rightchild << "\n";
                currFile << parent << "\n";
                currFile << hei << "\n";
                currFile.close();

                // Handle edge case: successor's right child
                char* succParent = new char[30];
                UpdateParentLeftmostChild(successor, rightchild, succParent);

                // Special handling for root
                if (strcmp(RootFileName, rootFileName) == 0) {
                    strcpy_s(rootFileName, 30, successor);
                }

                // Remove the successor node
                DeleteRecursively(rightchild, successor);

                delete[] succData;
                delete[] succParent;
            }
        }

        delete[] dataa;
        delete[] leftchild;
        delete[] rightchild;
        delete[] parent;
        delete[] hei;
    }


    void RemoveNodeFromParent(char* node, char* parent, char* newChild) {
        if (strcmp(parent, "ROOT") == 0) {
            if (strcmp(newChild, "1") == 0) {
                rootFileName = NULL;
            }
            else {
                strcpy_s(rootFileName, 30, newChild);
            }
        }
        else {
            char* parentPath = fullpath(parent, fouldername);
            ifstream file(parentPath);

            char* pdata = new char[500];
            char* leftchild = new char[30];
            char* rightchild = new char[30];
            char* pparent = new char[30];
            char* phei = new char[3];

            file.getline(pdata, 500);
            file.getline(leftchild, 30);
            file.getline(rightchild, 30);
            file.getline(pparent, 30);
            file.getline(phei, 3);
            file.close();

            ofstream ofile(parentPath, ios::out | ios::trunc);
            ofile << pdata << "\n";
            if (strcmp(leftchild, node) == 0) {
                ofile << newChild << "\n";
                ofile << rightchild << "\n";
            }
            else {
                ofile << leftchild << "\n";
                ofile << newChild << "\n";
            }
            ofile << pparent << "\n";
            ofile << phei << "\n";
            ofile.close();

            delete[] pdata;
            delete[] leftchild;
            delete[] rightchild;
            delete[] pparent;
            delete[] phei;
        }
    }

    void FindLeftmostChild(char* node, char* successor) {
       
        char* fol = new char[30];
        strcpy_s(fol, 30, "MyNewFolder");
        char* nodePath = fullpath(node, fol);
        
       
        ifstream file(nodePath);

        char* data = new char[500];
        char* leftchild = new char[30];

        file.getline(data, 500);
        file.getline(leftchild, 30);
        file.close();

        if (strcmp(leftchild, "1") == 0) {
            strcpy_s(successor, sizeof(successor), node);
        }
        else {
            FindLeftmostChild(leftchild, successor);
        }

        delete[] data;
        delete[] leftchild;
    }

    void UpdateParentLeftmostChild(char* successor, char* rightChild, char* succParent) {
        char* succPath = fullpath(successor, fouldername);
        ifstream file(succPath);

        char* data = new char[500];
        char* leftchild = new char[30];
        char* rightchild = new char[30];
        char* parent = new char[30];

        file.getline(data, 500);
        file.getline(leftchild, 30);
        file.getline(rightchild, 30);
        file.getline(parent, 30);
        file.close();

        if (strcmp(rightchild, "1") != 0) {
            char* parentPath = fullpath(parent, fouldername);
            ifstream pfile(parentPath);

            char* pdata = new char[500];
            char* pleftchild = new char[30];
            char* prightchild = new char[30];

            pfile.getline(pdata, 500);
            pfile.getline(pleftchild, 30);
            pfile.getline(prightchild, 30);
            pfile.close();

            ofstream ofile(parentPath, ios::out | ios::trunc);
            ofile << pdata << "\n";
            ofile << leftchild << "\n";
            ofile << rightChild << "\n";
            ofile << parent << "\n";
            ofile.close();

            delete[] pdata;
            delete[] pleftchild;
            delete[] prightchild;
        }

        strcpy_s(succParent, sizeof(succParent), parent);
        delete[] data;
        delete[] leftchild;
        delete[] rightchild;
        delete[] parent;
    }
    //************************* deletion functions end ****************************

    //



};

void checke_Change_IN_Data_By_MURKLE(char* foulderM, char* foulder, int numofFoulder, char** founderArray , rootn& root);
void adddatainAVL(AVLTree*& avltree, char*& currentfoulder, char**& foulderaaray, int& fouldernum, int  column, int& rownum, rootn& root);
void commitchaneg(AVLTree*& avltree, char*& currentfoulder, char**& foulderaaray, int& fouldernum, AVLTree*& tree , rootn& root);
void addFolder_murkle(char* foldername, int& numofFoulder, char**& folderArray , rootn& root);
void murkeletree(char* fouldername, char** foulderArray, AVLTree*& tree, int& numofdFoulder , rootn& root);

char* fullpath(const char* filename, char* fouldername);
int getsize(char* array);
void addFolder(char* foldername, int& numofFoulder, char**& folderArray , rootn& root);

char* hashname(char* array , int column, int &rownum) {
    long long int k = 1;
    char* temp = new char[50];
    long long int sizee = getsize(array);
    for (long long int i = 0; i < sizee; i++) {
        if (array[i] == ',') {
            k++;
        }
        if (k == column) {
            for (long long int j = 0; j < 20; j++, i++) {
                temp[j] = array[i + 1];
                if (array[i + 2] == ',') {
                    // Convert rownum to string and append
                    char rownumStr[10];
                    sprintf_s(rownumStr, sizeof(rownumStr), "%lld", rownum);

                    // Add underscore
                    temp[j + 1] = '_';

                    // Copy rownum string after underscore
                    strcpy_s(temp + j + 2, 50 - (j + 2), rownumStr);

                    break;
                }
            }
            break;
        }
    }


    return temp;
}
// Function to create a folder
void addFolder( char* foldername , int & numofFoulder , char** &folderArray , rootn& root)
{
    
    
    numofFoulder++;
	char* branchname = new char[30];
	char* sourceDir = new char[100];
	char* destDir = new char[100];
	bool choice = false;

    cout << "Enter Your Branch Name : ";
    cin >> branchname;
    cout << endl;
    choice = true;

    strcpy_s(folderArray[numofFoulder], 30, branchname);
    if (fs::exists(branchname))
    {
        cout << "Branch '" << branchname << "' already exists." << endl;
        return;
    }

  //  sourceDir = currentDir;       // Specify the source directory
	strcpy_s(sourceDir, 100, foldername);
    destDir = branchname;   // Specify the destination directory


    if (fs::create_directory(destDir)) {
        cout << "Branch '" << branchname << "' created Successfully!" << endl;

    }
    else
    {
        std::cout << "Failed to create destination directory.\n";
        return;
    }


    // Copy directory recursively
    fs::copy(sourceDir, destDir, fs::copy_options::recursive);

    std::cout << "Directory copied successfully from '" << sourceDir << "' to '" << destDir << "'.\n";
    return;
}
void addFolder_murkle(char* foldername, int& numofFoulder, char**& folderArray  , rootn& root)
{


    numofFoulder++;
    char* branchname = new char[100];
    char* sourceDir = new char[100];
    char* destDir = new char[100];
    bool choice = false;
    char* murkle = new char[30];

    strcpy_s(murkle, 30, "Murkle");

    // Copy the original folder name into branchname
    strcpy_s(branchname, 100, foldername);

    // Append "Murkle" to branchname
    strcat_s(branchname, 100, murkle);
    choice = true;

    strcpy_s(folderArray[numofFoulder], 30, branchname);
    if (fs::exists(branchname))
    {
        cout << "Branch '" << branchname << "' already exists." << endl;
        return;
    }

    //  sourceDir = currentDir;       // Specify the source directory
    strcpy_s(sourceDir, 100, foldername);
    destDir = branchname;   // Specify the destination directory


    if (fs::create_directory(destDir)) {
        cout << "Branch '" << branchname << "' created Successfully!" << endl;

    }
    else
    {
        std::cout << "Failed to create destination directory.\n";
        return;
    }


    // Copy directory recursively
    fs::copy(sourceDir, destDir, fs::copy_options::recursive);

    std::cout << "Directory copied successfully from '" << sourceDir << "' to '" << destDir << "'.\n";
    return;
}
char* fullpath(const char* filename  , char* fouldername) {
    char* fullpath = new char[100];

    // Copy folder name to fullpath
    strcpy_s(fullpath, 100, fouldername);

    // Append a "/" to fullpath
    strcat_s(fullpath, 100, "/");

    // Append the filename to fullpath
    strcat_s(fullpath, 100, filename);
    strcat_s(fullpath, 100, ".txt");

    return fullpath;
}
// In main()
int getsize(char* array)
{
    int i = 0;
    while (array[i] != '\0')
    {
        i++;
    }
    return i;
}
void murkeletree(char* fouldernamee, char** foulderArray, AVLTree*& tree, int& numofdFoulder , rootn& root)
{


    cout << "Enter the branch name  of MURKLE  TREE   : ";
    addFolder_murkle(fouldernamee, numofdFoulder, foulderArray ,root);

    strcpy_s(fouldernamee, 30, foulderArray[numofdFoulder]);

    tree->recursive_post_order(tree->rootFileName, fouldernamee);
    cout << endl << "-------------------------\n|| Murkle Tree Created Successfully ||\n-------------------------\n\n";

    // create a tree of the hash
}
void deletefile(char* filename, char* foldername, AVLTree*& tree)
{
    char* fullpathh = fullpath(filename, foldername);
    if (fs::exists(fullpathh))
    {
        tree->fouldername = foldername;
        tree->FileDeletion(filename);
    }
    else
    {
        cout << "File does not exist." << endl;
    }
}

void commitchaneg(AVLTree*& avltree, char* &currentfoulder, char** &foulderaaray , int &fouldernum , AVLTree*& tree , rootn& root)
{
    cout << "What changes you want to do \n";
    cout << "Update the file ? 1  :\n";
    cout << "Delete the file ? 2  :\n";

    int choice = 0;
    cin >> choice;

    if (choice == 1)
    {
       
		char* leftchild = new char[30];
        char* rightchild = new char[30];
		char* parent = new char[30];
		char* hei = new char[3];
		char* dataa = new char[200];
        
        
        
        cout << "Enter the file name you want to update : ";
        char* filename = new char[30];
        cin >> filename;
        cout << endl;

        cout << "Enter the column number you want to change  : ";
		int column = 0;
		cin >> column;
		cout << endl;

        cout << "Enter the new data for the column :"; 
        char* data = new char[200];
        cin >> data;
        cout << endl;
        


        while (true)
        {
            char* fullpathh = fullpath(filename, currentfoulder);
            ifstream file1;
            // check if file exist or not
            if (fs::exists(fullpathh))
            {
				file1.open(fullpathh);
				file1.getline(dataa, 200);
				file1.getline(leftchild, 30);
				file1.getline(rightchild, 30);
				file1.getline(parent, 30);
				file1.getline(hei, 3);
				file1.close();


				// Update the file
				

                int k = 1;
                char* temp = new char[200];
                int sizee = getsize(dataa);
                int i = 0;
				int l = 0;
                for (; i < sizee; i++ , l++) {
                    if (dataa[i] == ',') 
                    {
                        temp[l] = ',';
                        k++;
                    }
					
                    if (k == column) 
                    {
						int newdatasieze = getsize(data);
                        temp[l] = dataa[i];
                        l= i++;
                        

                        for ( int j = 0 ; j < newdatasieze; j++, l++) 
                        {
                            
                            temp[l] = data[j];
                          
                        }
                        temp[l] = ',';
                        
                        
                        while (dataa[i] != ',' && dataa[i]!='\0')
                        {
							i++;
                        }
                       
                        k++;
						
                        
                    }
                    temp[l] = dataa[i];

                }
				temp[i] = '\0';
				strcpy_s(dataa, 200, temp);


				//// making new foulder for any change in the data
                
                addFolder(currentfoulder,fouldernum , foulderaaray , root);
                strcpy_s(root.rootname[fouldernum], 30, tree->rootFileName);


				currentfoulder = foulderaaray[fouldernum];
				char* fullpath1 = fullpath(filename, currentfoulder);
				ofstream file3;
				file3.open(fullpath1);
				file3 << dataa << "\n";       // Store data
				file3 << leftchild << "\n";   // Left child
				file3 << rightchild << "\n"; // Right child
				file3 << parent << "\n";     // Parent file name
				file3 << hei << "\n";              // Height of the current node
				file3.close();

                cout << "\n -------------------------\n|| Data Updated Successfully ||\n -------------------------\n\n ";

                murkeletree(currentfoulder, foulderaaray, tree, fouldernum, root);
                    break;
            }
            else
            {
                cout << "File does not exist" << endl;
                cout << "Please switch the branch " << endl<<endl;
                 
				cout << "Enter the branch name : ";
				char* branchname = new char[30];
				cin >> branchname;
				cout << endl;
				strcpy_s(currentfoulder, 30, branchname);
				delete[] branchname;

                cout << "Enter the file name you want to update : ";
               
                cin >> filename;
                cout << endl;

            }
        }

        // Update the file

        //avltree->UpdateFile(filename, data , currentfoulder);
    }
    else if (choice == 2)
    {
        cout << "Enter the file name you want to delete : ";
        char* filename = new char[30];
        cin >> filename;
        cout << endl;
        deletefile(filename, currentfoulder, tree);
        // Delete the file
        //avltree->DeleteFile(filename);
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

void adddatainAVL(AVLTree*& avltree, char*& currentfoulder, char**& foulderaaray, int& fouldernum, int  column, int& rownum , rootn & root)
{
    cout << "Enter the file name you want to insert : ";
    char* filename = new char[30];
    cin >> filename;
    cout << endl;

    cout << "Enter the name of Directory : ";
    char* fouldername = new char[30];
    cin >> fouldername;
    cout << endl;
    while (true)
    {
        char* fullpathh = fullpath(filename, currentfoulder);
        ifstream file1;
        // check if file exist or not
        if (fs::exists(fullpathh))
        {
            cout << "File already exist" << endl;
            cout << "Please switch the branch " << endl;
            cout << "Enter the branch name : ";
            char* branchname = new char[30];
            cin >> branchname;
            cout << endl;
            strcpy_s(currentfoulder, 30, branchname);
            delete[] branchname;
        }
        else if (!fs::exists(fullpathh))
        {
            char* data = new char[200];
            char* filename = new char[30];
            cout << "Enter the data for the file : ";
            cin >> data;
            cout << endl;

            // Insert the file
            //avltree->InsertInAvL(filename, data);
            filename = hashname(data, column, rownum);
            rownum++;
           
			addFolder(foulderaaray[0], fouldernum, foulderaaray ,root);
			currentfoulder = foulderaaray[fouldernum];
			char* fullpath1 = fullpath(filename, currentfoulder);
			avltree->fouldername = currentfoulder;
            int c = 0;
			avltree->InsertInAvL(filename, data, c);
			strcpy_s(root.rootname[fouldernum], 30, avltree->rootFileName);
            rownum--;

			cout << "-------------------------\n|| Data Inserted Successfully ||\n-------------------------\n\n";

            /// what ever is change is commited save in murkle tree;
            addFolder_murkle(currentfoulder, fouldernum, foulderaaray, root);
        }

     
    }
}


/////  Uses Merkle Tree or similar mechanisms for data  synchronization and integrity verification
// in merkele tree we have to create a hash of the data of left child and right child and save in the parent file 
// and then we have to create a tree of the hash

void  recursive_check(char* cureent1, char* current2, char* foulder1, char* foulder2 ,int &check)
{
    char* leftchild1 = new char[30];
    char* rightchild1 = new char[30];
    char* parent1= new char[30];
    char* hei1 = new char[3];
    char* data1 = new char[200];
    ifstream file1;
    char* fullname1 = fullpath(cureent1, foulder1);
    file1.open(fullname1);
    file1.getline(data1, 200);
    file1.getline(leftchild1, 30);
    file1.getline(rightchild1, 30);
    file1.getline(parent1, 30);
    file1.getline(hei1, 3);
    file1.close();
    

	char* leftchild2 = new char[30];
	char* rightchild2 = new char[30];
	char* parent2 = new char[30];
	char* hei2 = new char[3];
	char* data2 = new char[200];

	ifstream file2;
	char* fullname2 = fullpath(current2, foulder2);

	file2.open(fullname2);
	file2.getline(data2, 200);
	file2.getline(leftchild2, 30);
    file2.getline(rightchild2, 30);
	file2.getline(parent2, 30);
    file2.getline(hei2, 3);

	if (data1 != data2)
	{
		cout << "Data is changed in the file : " << cureent1 << endl;
        check = 1;
		return ;
	}

    if (strcmp(leftchild1, "1") != 0  || strcmp(leftchild2, "1") != 0)
    {
        recursive_check(leftchild1, leftchild2, foulder1, foulder2 , check);
       
    }


	if (strcmp(rightchild1, "1") != 0 || strcmp(rightchild2, "1") != 0)
	{
		recursive_check(rightchild1, rightchild2, foulder1, foulder2 , check);
	}
   

    delete[]leftchild1;
    delete[]rightchild1;
    delete[]parent1;
    delete[]hei1;
    delete[]data1;



}

 
void checke_Change_IN_Data_By_MURKLE( int numofFoulder , char** founderArray  ,char* rootfile , rootn& root)
{
        
	cout << "\n\nEnter the branch name  of MURKLE  TREE    you want to check the data if it is changed  : ";
	char* foulde1 = new char[30];
	cin >> foulde1;
	cout << endl;

    cout << "\n\n Enter the branch name from which you wantot comapre   :";
	char* foulder2 = new char[30];
	cin >> foulder2;

    int  check = 0;
    int root1 = 0;
     int root2 = 0;
    for (int i = 0; i < numofFoulder; i++)
    {
        if (strcmp(foulder2 , root.rootname[i])==0)
        {
            root2 = i;
        }
        if (strcmp(foulde1, root.rootname[i]) == 0)
        {
            root1 = i;
        }
    }

    recursive_check(rootfile, rootfile, foulde1, foulder2, check);

}

void print(char* foulder, char* cureent )
{

    char* leftchild = new char[30];
    char* rightchild = new char[30];
    char* parent = new char[30];
    char* hei = new char[3];
    char* data = new char[200];
    ifstream file;
    char* fullname = fullpath(cureent, foulder);
    file.open(fullname);
    file.getline(data, 200);
    file.getline(leftchild, 30);
    file.getline(rightchild, 30);
    file.getline(parent, 30);
    file.getline(hei, 3);
    file.close();
   


    if (strcmp(leftchild, "1") != 0)
    {
        print(foulder, leftchild);
    }
   

    cout << "DATA  :" << data << endl;
    if (strcmp(rightchild, "1") != 0)
    {
		print(foulder, rightchild);
	}
   
    delete[]leftchild;
    delete[]rightchild;
    delete[]parent;
    delete[]hei;
    delete[]data;
    return;

}

void updatehistory(char**& history, int numofFoulder, char** fouldersarray , const char* histname)
{
    ofstream historyfile;
    historyfile.open(histname);

    char array[2] = {'l','e'};
    int j= 0;
    for (int i = 0; i <= numofFoulder; i++)
    {
        int size = getsize(fouldersarray[i]);

        if (fouldersarray[i][size - 2] == array[0] && fouldersarray[i][size - 1] == array[1])
        {
            continue;
        }

        history[j] = fouldersarray[i];
        j++;
    }

    for (int i = 0, j = 0; i <= numofFoulder; i++)
    {
    
        historyfile << fouldersarray[i] << "\n";

    }
	historyfile.close();

}
void printhistory(const char* histname, int foldernum , char** fouldersarray)
{
    ifstream historyfile;
    historyfile.open(histname);
    char array[2] = { 'l','e' };
    int j = 0;

    cout << "\n-------------------\n";
    cout << "HISTORY  \n";

    char* arrayy = new char[30];
    for (int i = 0; i < foldernum; i++)
    {
        int size = getsize(fouldersarray[i]);
       
        if (fouldersarray[i][size - 2] == array[0] && fouldersarray[i][size - 1] == array[1])
        {
            continue;
        }
        historyfile.getline(arrayy, 30);
       cout << " 1  :" << arrayy<<endl;

    }
}


/*

// C++ program to insert a node in AVL tree
#include <iostream>
#include<fstream>
#include<direct.h>
#include<string>
#include<cstring>
using namespace std;


const char* foldername = "MyNewFolder";

char* fullpath(const char* filename) {
    char* fullpath = new char[100];

    // Copy folder name to fullpath
    strcpy_s(fullpath, 100, foldername);

    // Append a "/" to fullpath
    strcat_s(fullpath, 100, "/");

    // Append the filename to fullpath
    strcat_s(fullpath, 100, filename);
    strcat_s(fullpath, 100, ".txt");

    return fullpath;
}

void createFolder()
{
    const char* folderName = "MyNewFolder";

    if (_mkdir(folderName) == 0) {
        cout << "Folder created successfully!" << endl;
    }
    else {
        perror("Error creating folder");
    }
}

int getsize(char* array)
{
    int i = 0;
    while (array[i] != '\0')
    {
        i++;
    }
    return i;
}

char* hashfunction(char* array,int column)
{
    int k = 1;
    char* temp = new char[20];
    int sizee = getsize(array);

    for (int i = 0; i < sizee; i++)
    {
        if (array[i] == ',')
        {
            k++;
        }
        if (k == column)
        {
            for (int j = 0; j < 20; j++, i++)
            {
                temp[j] = array[i];
                if (array[i + 1] == ',')
                {
                    temp[j + 1] = '\0';
                    break;
                }
            }
            break;
        }
    }
    int size = getsize(temp);
    int hash = 1;
    for (int i = 0; i < size; i++)
    {
        hash = hash * temp[i];
    }
    // convert integer to char array
    char* hasharray = new char[100];
    sprintf_s(hasharray, 100, "%d", hash);

    return hasharray;
}

long long int convertHashToInteger(char* hasharray)
{
    // Check for null or empty input
    if (hasharray == nullptr || hasharray[0] == '\0')
    {
        return 0;
    }

    // Use standard library function to convert string to integer
    long long int result = atoi(hasharray);

    return result;
}

char* getleftfilename(char* filename)
{

    ifstream file(fullpath(filename));
    string line;
    for(int i=0;i<2;i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getrightfilename(char* filename)
{
    if (filename == "-1")
    {
        char*a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 3; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getparentfilename(char* filename)
{
    if (filename == "-1")
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 5; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getheight(char* filename)
{
    if(filename=="-1")
    {
        char* a = new char;
        strcpy_s(a, 1, "-1");
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 4; i++)
    getline(file, line);
    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getdata(char* filename)
{
    if (filename == "-1")
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
        ifstream file(fullpath(filename));
    string line;
        getline(file, line);

        char* a = new char[1000];
    strcpy_s(a, 1000, line.c_str());
    return a;

}

char* getcolor(char* filename)
{
    if (filename == "-1")
    {
        char* a = new char[2];
        a[0] = '0';
        a[1] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 4; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getunclefilename(char* filename)
{
    if (filename == "-1")
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 6; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getgrandparentfilename(char* filename)
{
    if (filename == "-1")
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 7; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

void setleftfilename(const char* filename,  const char* newLine,int lineNumber = 1) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. lfn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[100][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();

}

void setrightfilename(const char* filename, const char* newLine, int lineNumber = 2) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. rfn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();

}

void setdata(const char* filename, const char* newLine, int lineNumber = 0) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. data" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setheight(const char* filename, string newLine, int lineNumber = 3) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. height" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine.c_str());

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setparentfilename(const char* filename, const char* newLine, int lineNumber = 4) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. spfn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setcolor(const char* filename, string newLine, int lineNumber = 3) {
    // Open the file for reading
    if (strcmp(filename,"-1")==0)
    {
                return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading.color" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine.c_str());

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setunclefilename(const char* filename, const char* newLine, int lineNumber = 5) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0  || strcmp(filename,"\0")==0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. ufn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setgrandparentfilename(const char* filename, const char* newLine, int lineNumber = 6) {
    // Open the file for reading

    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. gpfn "<< endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}


void createRedBlackfile(char* filename) {

    ofstream file(fullpath(filename));
    file << "-1" << endl;//data
    file << "-1" << endl;//left file
    file << "-1" << endl;//right file
    file << "1" << endl;//color
    file << "-1" << endl; // parent
    file << "-1" << endl; // uncle
    file << "-1" << endl; // grandparent
    file.close();

}


class Redblack {
    char* rootfile;
public:
    Redblack()
    {
        rootfile = NULL;
    }
    void insertfromCSV(ifstream &csvfile, int column) {
        char* dataline = new char[200];
        csvfile.getline(dataline, 200);
        while (csvfile.getline(dataline, 200) )
        {
            char* filename = hashfunction(dataline, column);
            if (rootfile == NULL) {
                rootfile = new char[10];
                strcpy_s(rootfile, 10, filename);
                createRedBlackfile((filename));
                setdata((filename), dataline);
                setcolor((filename), "0");
            }
            else {
                setcolor((rootfile), "0");
                insert(rootfile, filename, dataline, column);
            }
        }
    }
    void insert(char* root, char* filename, char* dataline, int column)
    {
        //check if file is smaller than root
        if (convertHashToInteger(hashfunction(dataline, column)) < convertHashToInteger(hashfunction(getdata((root)), column)))
        {
            //check if left of root is empty
            if (strcmp(getleftfilename(root), "-1") == 0)
            {
                createRedBlackfile((filename));
                setdata((filename), dataline);
                setparentfilename((filename), root);
                setleftfilename((root), filename);

                //check if parent of root exists (if exists then connect them)
                if (strcmp(getparentfilename(root), "-1") == 1)
                {
                    setgrandparentfilename(filename, getparentfilename(root));

                    //set uncleof filename
                    if (strcmp(getleftfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getrightfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getrightfilename(getgrandparentfilename(filename)));
                        }
                    }
                    else if (strcmp(getrightfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getleftfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getleftfilename(getgrandparentfilename(filename)));
                        }
                    }

                }

            }
            else
            {
                insert(getleftfilename((root)), filename, dataline, column);
            }
        }
        else // if file is greater than root
        {
            //if right of root is empty
            if (strcmp(getrightfilename(root), "-1") == 0)
            {
                createRedBlackfile((filename));
                setdata((filename), dataline);
                setparentfilename((filename), root);
                setrightfilename((root), filename);

                //check if parent of root exists (if exists then connect them)
                if (strcmp(getparentfilename(root), "-1") == 1)
                {
                    setgrandparentfilename(filename, getparentfilename(root));
                    //set uncleof filename
                    if (strcmp(getleftfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getrightfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getrightfilename(getgrandparentfilename(filename)));
                        }
                    }
                    else if (strcmp(getrightfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getleftfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getleftfilename(getgrandparentfilename(filename)));
                        }
                    }
                }

            }
        else
        {
                insert(getrightfilename((root)), filename, dataline, column);
        }
    }



        // check R-R situation
        if (strcmp(getgrandparentfilename(filename),"-1")==1  &&  strcmp(getcolor(getparentfilename(filename)), "1") == 0 && strcmp(getcolor(filename), "1") == 0)
        {
            //check if uncle is red
            if ((strcmp(getunclefilename(filename), "-1") == 1) && (strcmp(getcolor(getunclefilename(filename)), "1") == 0))
            {

                setcolor(getparentfilename(filename), "0");
                setcolor(getunclefilename(filename), "0");
                if(strcmp(getgrandparentfilename(filename),rootfile)==0)
                {
                    setcolor(getgrandparentfilename(filename), "0");
                }
                else
                {
                    setcolor(getgrandparentfilename(filename), "1");
                }
            }
            //check if uncle is black or null
            else if (strcmp(getunclefilename(filename), "-1") == 0 || strcmp(getcolor(getunclefilename(filename)), "0") == 0)
            {
                // check root is left of grandparent?
                if (strcmp(getleftfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                {
                    //check if filename is right of parent
                    if (strcmp(getrightfilename(getparentfilename(filename)), filename) == 0)
                    {   //LR
                        leftrotate(getparentfilename(filename), filename,getrightfilename(filename));
                        rightrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);

                        if (strcmp(getparentfilename(filename), "-1") == 1 &&   strcmp(getcolor(getparentfilename(filename)), "0")==0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }

                    }
                    //then if filename is left of parent
                    else
                    {
                        //RR
                        rightrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);
                        if (strcmp(getparentfilename(filename), "-1") == 1 && strcmp(getcolor(getparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }
                    }
                }
                //if root is right of grandparent
                else if (strcmp(getrightfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                {
                    //check if filename is right of parent
                    if (strcmp(getrightfilename(getparentfilename(filename)), filename) == 0)
                    {
                        //LL
                        leftrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);
                        if (strcmp(getparentfilename(filename), "-1") == 1 && strcmp(getcolor(getparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }
                    }
                    //if filename is left of parent
                    else
                    {
                        //RL
                        rightrotate(getparentfilename(filename), filename,getleftfilename(filename));
                        leftrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);
                        if (strcmp(getparentfilename(filename), "-1") == 1 && strcmp(getcolor(getparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }
                    }
                }

            }
            setcolor(rootfile, "0");

        }
    }
    void rightrotate(char*grandparent, char*root, char*filename)
    {
        if (strcmp(grandparent, rootfile) == 0)
        {
            rootfile = root;
        }

        setunclefilename(filename, getunclefilename(root));
        setgrandparentfilename(filename, getgrandparentfilename(root));
        setleftfilename(grandparent, getrightfilename(root));
        setunclefilename(getleftfilename(grandparent), filename);
        setparentfilename(getleftfilename(grandparent), grandparent);
        setgrandparentfilename(getleftfilename(grandparent), root);
        setparentfilename(root, getparentfilename(grandparent));
        setgrandparentfilename(root, getgrandparentfilename(grandparent));
        setunclefilename(root, getunclefilename(grandparent));
        setrightfilename(root, grandparent);
        setparentfilename(grandparent, root);
        setunclefilename(grandparent, getunclefilename(filename));
        setunclefilename(getrightfilename(grandparent), filename);
        setgrandparentfilename(getrightfilename(grandparent), root);
        setunclefilename(getrightfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setunclefilename(getleftfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setgrandparentfilename(getrightfilename(getrightfilename(grandparent)), root);
        setgrandparentfilename(getleftfilename(getrightfilename(grandparent)), root);
        setunclefilename(getleftfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setunclefilename(getrightfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setgrandparentfilename(getleftfilename(getleftfilename(grandparent)), grandparent);
        setgrandparentfilename(getrightfilename(getleftfilename(grandparent)), grandparent);
        setunclefilename(getleftfilename(filename), grandparent);
        setunclefilename(getrightfilename(filename), grandparent);
        setgrandparentfilename(getleftfilename(filename), root);
        setgrandparentfilename(getrightfilename(filename), root);
        setparentfilename(getleftfilename(filename), filename);
        setparentfilename(getrightfilename(filename), filename);

        if (strcmp(getparentfilename(root), "-1") == 1)
        {
            if (strcmp(getleftfilename(getparentfilename(root)), root) == 0)
            {
                setleftfilename(getparentfilename(root), root);
            }
            else
            {
                setrightfilename(getparentfilename(root), root);
            }
        }
    }

    void leftrotate(char* grandparent, char* root, char* filename)
    {
        if (strcmp(grandparent, rootfile) == 0)
        {
            rootfile = root;
        }
        setunclefilename(filename, getunclefilename(root));
        setgrandparentfilename(filename, getgrandparentfilename(root));
        setrightfilename(grandparent, getleftfilename(root));
        setunclefilename(getrightfilename(grandparent), filename);
        setparentfilename(getrightfilename(grandparent), grandparent);
        setgrandparentfilename(getrightfilename(grandparent), root);
        setparentfilename(root, getparentfilename(grandparent));
        setgrandparentfilename(root, getgrandparentfilename(grandparent));
        setunclefilename(root, getunclefilename(grandparent));
        setleftfilename(root, grandparent);
        setparentfilename(grandparent, root);
        setunclefilename(grandparent, getunclefilename(filename));
        setunclefilename(getrightfilename(grandparent), filename);
        setgrandparentfilename(getrightfilename(grandparent), root);
        setunclefilename(getrightfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setunclefilename(getleftfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setgrandparentfilename(getrightfilename(getrightfilename(grandparent)), root);
        setgrandparentfilename(getleftfilename(getrightfilename(grandparent)), root);
        setunclefilename(getleftfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setunclefilename(getrightfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setgrandparentfilename(getleftfilename(getleftfilename(grandparent)), grandparent);
        setgrandparentfilename(getrightfilename(getleftfilename(grandparent)), grandparent);
        setunclefilename(getleftfilename(filename), grandparent);
        setunclefilename(getrightfilename(filename), grandparent);
        setgrandparentfilename(getleftfilename(filename), root);
        setgrandparentfilename(getrightfilename(filename), root);
        setparentfilename(getleftfilename(filename), filename);
        setparentfilename(getrightfilename(filename), filename);

        if (strcmp(getparentfilename(root), "-1") == 1)
        {
            if (strcmp(getleftfilename(getparentfilename(root)), root) == 0)
            {
                setleftfilename(getparentfilename(root), root);
            }
            else
            {
                setrightfilename(getparentfilename(root), root);
            }
        }
    }
};


*/


int main() {
    // Open csv file
    createFolder();

    /*
    createFolder();
    Redblack rb;
    int column = 2;
    ifstream csvfile("healthcare_dataset.csv");
    rb.insertfromCSV(csvfile, column);
    */

    const char* histname = "History";
    char** history = new char* [20];
        for (int i = 0; i < 20; i++)
        {
            history[i] = new char[30];
        }
        

    
    //char** history
    rootn Root;
    int oldnumfol = 0;
	int numofFoulder = 0;
    char** fouldersarray = new char* [20];
    for (int i = 0; i < 10; i++)
    {
        fouldersarray[i] = new char[30];
    }
    
    char* currentfoulder = new char[30];
   

    ifstream csvfile("Marks.csv");
    long long int column = 0;
	cout << "|---------------------------------------------|" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
	cout << "|              WELCOME TO GIT                 |" << endl;
	cout << "|                                             |" << endl;
	cout << "|                                             |" << endl;
   
    char* temp1 = new char[200];
    csvfile.getline(temp1, 200);

    cout << "|----------------------------------------------|" << endl;
    cout << "|                                              |" << endl;
    cout << "| Which Column you want to select for File name|" << endl;

    int co = 0;
    for (int i = 0; i < strlen(temp1); i++)
    {
        if (temp1[i] == ',')
        {
            cout << " | ";
        }
        else
        {
            cout << temp1[i];
        }
    }
    cout << "\n";
    
    
    cin >> column;

	cout << "In which tree you want to insert data :  " << endl;
	cout << "1. AVL Tree" << endl;
	cout << "2. B Tree" << endl;
	cout << "3. B+ Tree" << endl;

   
    AVLTree* tree = new AVLTree();
    tree->column = column;
    tree->rownum = 100; // Start with first row number

    /// history function
        ///

    /// tracking the cureent foulder
    strcpy_s(currentfoulder,30, "MyNewFolder");
	strcpy_s(tree->fouldername,30, currentfoulder);
	strcpy_s(fouldersarray[0],30, currentfoulder);
    strcpy_s(Root.rootname[0], 30, currentfoulder);
    // call function to insert file in folder
    tree->insertdata(csvfile);

   murkeletree(currentfoulder, fouldersarray, tree, numofFoulder, Root);
    updatehistory(history, numofFoulder, fouldersarray, histname);

    // add in avl 

    while (true)
    {
       
       
        cout << "DO you want to print the Data of the branch (1/0)  : ";
        int printt = 0;
        cin >> printt;
        cout << endl;
        if (printt == 1)
        {
			cout << "Enter the name of branch  : ";
            char* branch = new char[30];
            cin >> branch;
            print(branch, tree->rootFileName);
        }
        
        cout << endl << endl << "DO YOU WANT ADD ANYTHING IN THE ANY BRANCH   (1/0)  :";
		int choice11 = 0;
		cin >> choice11;


        if(choice11)
        adddatainAVL(tree, currentfoulder, fouldersarray, numofFoulder, column, tree->rownum , Root);

        /// asking for creating a branch
        cout << "Do you want to create a branch for this data ? (1/0) : ";
        int choice=0;
        cin >> choice;
        if (choice == 1)
           addFolder(tree->fouldername, numofFoulder, fouldersarray , Root);



        // commit change in the data of  particullar file in particular foulder
        commitchaneg(tree, currentfoulder, fouldersarray, numofFoulder , tree , Root);

		// checke for the change in the data by murkle tree
		cout << "Do you want to check the change in the data by Murkle Tree ? (1/0) : ";
		int choice3 = 0;
		cin >> choice3;
		if (choice3 == 1)
			checke_Change_IN_Data_By_MURKLE( numofFoulder, fouldersarray, tree->rootFileName , Root);

        cout << endl << "DO you want to MAKE Murkle Tree   (1/0)   :";
        int choice1=0;
        cin >> choice1;
        cout << "\n";
        if (choice1 == 1)
            murkeletree(currentfoulder, fouldersarray, tree, numofFoulder, Root);

       
        updatehistory(history, numofFoulder, fouldersarray, histname);

		cout <<endl<<endl<< "DO you want to end this   ? (1/0)  : ";
		int choice2=0;
		cin >> choice2;

        // updatehistory(history,  numofFoulder,  fouldersarray,  histname)


        if (choice2 == 1)
        {
            break;

        }

		cout << endl;
        system("pause");
        // commit change in the data of  particullar file in particular foulder

    }
    delete tree;


    return 0;
}



// C++ program to insert a node in AVL tree


const char* foldername = "MyNewFolder";


char* fullpath(const char* filename) {
    char* fullpath = new char[100];

    // Copy folder name to fullpath
    strcpy_s(fullpath, 100, foldername);

    // Append a "/" to fullpath
    strcat_s(fullpath, 100, "/");

    // Append the filename to fullpath
    strcat_s(fullpath, 100, filename);
    strcat_s(fullpath, 100, ".txt");

    return fullpath;
}



char* hashfunction(char* array,int column)
{
    int k = 1;
    char* temp = new char[20];
    int sizee = getsize(array);

    for (int i = 0; i < sizee; i++)
    {
        if (array[i] == ',')
        {
            k++;
        }
        if (k == column)
        {
            for (int j = 0; j < 20; j++, i++)
            {
                temp[j] = array[i];
                if (array[i + 1] == ',')
                {
                    temp[j + 1] = '\0';
                    break;
                }
            }
            break;
        }
    }
    int size = getsize(temp);
    int hash = 1;
    for (int i = 0; i < size; i++)
    {
        hash = hash * temp[i];
    }
    // convert integer to char array
    char* hasharray = new char[100];
    sprintf_s(hasharray, 100, "%d", hash);

    return hasharray;
}

long long int convertHashToInteger(char* hasharray)
{
    // Check for null or empty input
    if (hasharray == nullptr || hasharray[0] == '\0')
    {
        return 0;
    }

    // Use standard library function to convert string to integer
    long long int result = atoi(hasharray);

    return result;
}

char* getleftfilename(char* filename)
{
    if (strcmp(filename, "-1")==0)
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for(int i=0;i<2;i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getrightfilename(char* filename)
{
    if (strcmp(filename, "-1")==0)
    {
        char*a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 3; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getparentfilename(char* filename)
{
    if (strcmp(filename, "-1")==0);
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 5; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getdata(char* filename)
{
    if (strcmp(filename, "-1")==0)
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
        ifstream file(fullpath(filename));
    string line;
        getline(file, line);

        char* a = new char[1000];
    strcpy_s(a, 1000, line.c_str());
    return a;

}

char* getcolor(char* filename)
{
    if (strcmp(filename, "-1")==0)
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 4; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getunclefilename(char* filename)
{
    if (strcmp(filename, "-1") == 0)
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 6; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

char* getgrandparentfilename(char* filename)
{
    if (strcmp(filename, "-1") == 0)
    {
        char* a = new char[3];
        a[0] = '-';
        a[1] = '1';
        a[2] = '\0';
        return a;
    }
    ifstream file(fullpath(filename));
    string line;
    for (int i = 0; i < 7; i++)
        getline(file, line);

    char* a = new char[100];
    strcpy_s(a, 100, line.c_str());
    return a;
}

void setleftfilename(const char* filename,  const char* newLine,int lineNumber = 1) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename,"\0")==0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. lfn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[100][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();

}

void setrightfilename(const char* filename, const char* newLine, int lineNumber = 2) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. rfn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();

}

void setdata(const char* filename, const char* newLine, int lineNumber = 0) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. data" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setheight(const char* filename, string newLine, int lineNumber = 3) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. height" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine.c_str());

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setparentfilename(const char* filename, const char* newLine, int lineNumber = 4) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. spfn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setcolor(const char* filename, string newLine, int lineNumber = 3) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading.color" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine.c_str());

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setunclefilename(const char* filename, const char* newLine, int lineNumber = 5) {
    // Open the file for reading
    if (strcmp(filename, "-1") == 0  || strcmp(filename,"\0")==0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. ufn" << endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}

void setgrandparentfilename(const char* filename, const char* newLine, int lineNumber = 6) {
    // Open the file for reading

    if (strcmp(filename, "-1") == 0 || strcmp(filename, "\0") == 0)
    {
        return;
    }
    ifstream fileIn(fullpath(filename));
    if (!fileIn.is_open()) {
        cout << "Error: Could not open file for reading. gpfn "<< endl;
        return;
    }

    // Store file content temporarily
    char lines[10][200]; // assuming max 100 lines, each with max 200 characters
    int currentLine = 0;

    // Read each line into the array
    while (fileIn.getline(lines[currentLine], 200)) {
        currentLine++;
    }
    fileIn.close();

    // Check if the line number is valid
    if (lineNumber < 0 || lineNumber >= currentLine) {
        cout << "Error: Invalid line number." << endl;
        return;
    }

    // Replace the specified line with new content
    strcpy_s(lines[lineNumber], newLine);

    // Open the file for writing (overwrite the file)
    ofstream fileOut(fullpath(filename));
    if (!fileOut.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the updated content back to the file
    for (int i = 0; i < currentLine; i++) {
        fileOut << lines[i] << endl;
    }
    fileOut.close();
}


void createRedBlackfile(char* filename) {

    ofstream file(fullpath(filename));
    file << "-1" << endl;//data
    file << "-1" << endl;//left file
    file << "-1" << endl;//right file
    file << "1" << endl;//color
    file << "-1" << endl; // parent
    file << "-1" << endl; // uncle
    file << "-1" << endl; // grandparent
    file.close();

}


class Redblack {
    char* rootfile;
public:
    Redblack()
    {
        rootfile = NULL;
    }
    void insertfromCSV(ifstream &csvfile, int column) {
        char* dataline = new char[200];
        csvfile.getline(dataline, 200);
        while (csvfile.getline(dataline, 200) )
        {
            char* filename = hashfunction(dataline, column);
            if (rootfile == NULL) {
                rootfile = new char[10];
                strcpy_s(rootfile, 10, filename);
                createRedBlackfile((filename));
                setdata((filename), dataline);
                setcolor((filename), "0");
            }
            else {
                setcolor((rootfile), "0");
                insert(rootfile, filename, dataline, column);
            }
        }
    }
    void insert(char* root, char* filename, char* dataline, int column)
    {
        //check if file is smaller than root
        if (convertHashToInteger(hashfunction(dataline, column)) < convertHashToInteger(hashfunction(getdata((root)), column)))
        {
            //check if left of root is empty
            if (strcmp(getleftfilename(root), "-1") == 0)
            {
                createRedBlackfile((filename));
                setdata((filename), dataline);
                setparentfilename((filename), root);
                setleftfilename((root), filename);

                //check if parent of root exists (if exists then connect them)
                if (strcmp(getparentfilename(root), "-1") == 1)
                {
                    setgrandparentfilename(filename, getparentfilename(root));

                    //set uncleof filename
                    if (strcmp(getleftfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getrightfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getrightfilename(getgrandparentfilename(filename)));
                        }
                    }
                    else if (strcmp(getrightfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getleftfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getleftfilename(getgrandparentfilename(filename)));
                        }
                    }

                }

            }
            else
            {
                insert(getleftfilename((root)), filename, dataline, column);
            }
        }
        else // if file is greater than root
        {
            //if right of root is empty
            if (strcmp(getrightfilename(root), "-1") == 0)
            {
                createRedBlackfile((filename));
                setdata((filename), dataline);
                setparentfilename((filename), root);
                setrightfilename((root), filename);

                //check if parent of root exists (if exists then connect them)
                if (strcmp(getparentfilename(root), "-1") == 1)
                {
                    setgrandparentfilename(filename, getparentfilename(root));
                    //set uncleof filename
                    if (strcmp(getleftfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getrightfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getrightfilename(getgrandparentfilename(filename)));
                        }
                    }
                    else if (strcmp(getrightfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                    {
                        if (strcmp(getleftfilename(getgrandparentfilename(filename)), "-1") == 0)
                        {

                        }
                        else
                        {
                            setunclefilename(filename, getleftfilename(getgrandparentfilename(filename)));
                        }
                    }
                }

            }
        else
        {
                insert(getrightfilename((root)), filename, dataline, column);
        }
    }



        // check R-R situation
        if (strcmp(getgrandparentfilename(filename),"-1")==1  &&  strcmp(getcolor(getparentfilename(filename)), "1") == 0 && strcmp(getcolor(filename), "1") == 0)
        {
            //check if uncle is red
            if ((strcmp(getunclefilename(filename), "-1") == 1) && (strcmp(getcolor(getunclefilename(filename)), "1") == 0))
            {

                setcolor(getparentfilename(filename), "0");
                setcolor(getunclefilename(filename), "0");
                if(strcmp(getgrandparentfilename(filename),rootfile)==0)
                {
                    setcolor(getgrandparentfilename(filename), "0");
                }
                else
                {
                    setcolor(getgrandparentfilename(filename), "1");
                }
            }
            //check if uncle is black or null
            else if (strcmp(getunclefilename(filename), "-1") == 0 || strcmp(getcolor(getunclefilename(filename)), "0") == 0)
            {
                // check root is left of grandparent?
                if (strcmp(getleftfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                {
                    //check if filename is right of parent
                    if (strcmp(getrightfilename(getparentfilename(filename)), filename) == 0)
                    {   //LR
                        leftrotate(getparentfilename(filename), filename,getrightfilename(filename));
                        rightrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);

                        if (strcmp(getparentfilename(filename), "-1") == 1 &&   strcmp(getcolor(getparentfilename(filename)), "0")==0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }

                    }
                    //then if filename is left of parent
                    else
                    {
                        //RR
                        rightrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);
                        if (strcmp(getparentfilename(filename), "-1") == 1 && strcmp(getcolor(getparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }
                    }
                }
                //if root is right of grandparent
                else if (strcmp(getrightfilename(getgrandparentfilename(filename)), getparentfilename(filename)) == 0)
                {
                    //check if filename is right of parent
                    if (strcmp(getrightfilename(getparentfilename(filename)), filename) == 0)
                    {
                        //LL
                        leftrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);
                        if (strcmp(getparentfilename(filename), "-1") == 1 && strcmp(getcolor(getparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }
                    }
                    //if filename is left of parent
                    else
                    {
                        //RL
                        rightrotate(getparentfilename(filename), filename,getleftfilename(filename));
                        leftrotate(getgrandparentfilename(filename), getparentfilename(filename), filename);
                        if (strcmp(getparentfilename(filename), "-1") == 1 && strcmp(getcolor(getparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getparentfilename(filename), "0");
                        }
                        if (strcmp(getgrandparentfilename(filename), "-1") == 1 && strcmp(getcolor(getgrandparentfilename(filename)), "0") == 0)
                        {
                            setcolor(getgrandparentfilename(filename), "1");
                        }
                        else
                        {
                            setcolor(getgrandparentfilename(filename), "0");
                        }
                    }
                }

            }
            setcolor(rootfile, "0");

        }
    }
    void rightrotate(char*grandparent, char*root, char*filename)
    {
        if (strcmp(grandparent, rootfile) == 0)
        {
            rootfile = root;
        }

        setunclefilename(filename, getunclefilename(root));
        setgrandparentfilename(filename, getgrandparentfilename(root));
        setleftfilename(grandparent, getrightfilename(root));
        setunclefilename(getleftfilename(grandparent), filename);
        setparentfilename(getleftfilename(grandparent), grandparent);
        setgrandparentfilename(getleftfilename(grandparent), root);
        setparentfilename(root, getparentfilename(grandparent));
        setgrandparentfilename(root, getgrandparentfilename(grandparent));
        setunclefilename(root, getunclefilename(grandparent));
        setrightfilename(root, grandparent);
        setparentfilename(grandparent, root);
        setunclefilename(grandparent, getunclefilename(filename));
        setunclefilename(getrightfilename(grandparent), filename);
        setgrandparentfilename(getrightfilename(grandparent), root);
        setunclefilename(getrightfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setunclefilename(getleftfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setgrandparentfilename(getrightfilename(getrightfilename(grandparent)), root);
        setgrandparentfilename(getleftfilename(getrightfilename(grandparent)), root);
        setunclefilename(getleftfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setunclefilename(getrightfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setgrandparentfilename(getleftfilename(getleftfilename(grandparent)), grandparent);
        setgrandparentfilename(getrightfilename(getleftfilename(grandparent)), grandparent);
        setunclefilename(getleftfilename(filename), grandparent);
        setunclefilename(getrightfilename(filename), grandparent);
        setgrandparentfilename(getleftfilename(filename), root);
        setgrandparentfilename(getrightfilename(filename), root);
        setparentfilename(getleftfilename(filename), filename);
        setparentfilename(getrightfilename(filename), filename);

        if (strcmp(getparentfilename(root), "-1") == 1)
        {
            if (strcmp(getleftfilename(getparentfilename(root)), root) == 0)
            {
                setleftfilename(getparentfilename(root), root);
            }
            else
            {
                setrightfilename(getparentfilename(root), root);
            }
        }
    }

    void leftrotate(char* grandparent, char* root, char* filename)
    {
        if (strcmp(grandparent, rootfile) == 0)
        {
            rootfile = root;
        }
        setunclefilename(filename, getunclefilename(root));
        setgrandparentfilename(filename, getgrandparentfilename(root));
        setrightfilename(grandparent, getleftfilename(root));
        setunclefilename(getrightfilename(grandparent), filename);
        setparentfilename(getrightfilename(grandparent), grandparent);
        setgrandparentfilename(getrightfilename(grandparent), root);
        setparentfilename(root, getparentfilename(grandparent));
        setgrandparentfilename(root, getgrandparentfilename(grandparent));
        setunclefilename(root, getunclefilename(grandparent));
        setleftfilename(root, grandparent);
        setparentfilename(grandparent, root);
        setunclefilename(grandparent, getunclefilename(filename));
        setunclefilename(getrightfilename(grandparent), filename);
        setgrandparentfilename(getrightfilename(grandparent), root);
        setunclefilename(getrightfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setunclefilename(getleftfilename(getrightfilename(grandparent)), getleftfilename(grandparent));
        setgrandparentfilename(getrightfilename(getrightfilename(grandparent)), root);
        setgrandparentfilename(getleftfilename(getrightfilename(grandparent)), root);
        setunclefilename(getleftfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setunclefilename(getrightfilename(getleftfilename(grandparent)), getrightfilename(grandparent));
        setgrandparentfilename(getleftfilename(getleftfilename(grandparent)), grandparent);
        setgrandparentfilename(getrightfilename(getleftfilename(grandparent)), grandparent);
        setunclefilename(getleftfilename(filename), grandparent);
        setunclefilename(getrightfilename(filename), grandparent);
        setgrandparentfilename(getleftfilename(filename), root);
        setgrandparentfilename(getrightfilename(filename), root);
        setparentfilename(getleftfilename(filename), filename);
        setparentfilename(getrightfilename(filename), filename);

        if (strcmp(getparentfilename(root), "-1") == 1)
        {
            if (strcmp(getleftfilename(getparentfilename(root)), root) == 0)
            {
                setleftfilename(getparentfilename(root), root);
            }
            else
            {
                setrightfilename(getparentfilename(root), root);
            }
        }
    }
};
