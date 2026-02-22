#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


int main()
{
   std::ifstream infile("input.txt");
   std::ofstream outfile("output.txt");

   if(!infile.is_open() || !outfile.is_open())
   {
        std::cerr<<"Error Opening File!"<< std::endl;
        return 1;
   }
   std::vector<int> data;
   std::string line;

   while(getline(infile, line))
    {
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if(command == "create") {
            int val;
            while(ss >> val) {
                data.push_back(val);
            }
            outfile << "Vector created" << data.size() << std::endl;
        }
        else if(command == "insert") {
            int val, idx;
            char at;
            if(ss >> val >> at >> idx) {
                if(idx <= data.size()) { 
                    data.insert(data.begin() + idx, val);
                    outfile << "Value :" << val << "inserted at:" << data.at(idx) << std::endl; 
                    
                }else{
                    outfile << "Idx: " << idx << "Is out of bound" << std::endl; 
                }

            }
        }
        else if(command == "erase") {
            int idx;
            if(ss >> idx) {
                if(idx < data.size()) { 
                    data.erase(data.begin() + idx);  
                    outfile<< "value" << data.at(idx) << "Is erased" << std::endl;
                }else{
                    outfile << "idx: " << idx << " Is out of bound" << std::endl;
                }
            }
        }
        else if(command == "append") {
            int val;
            if(ss >> val) {
                data.push_back(val);
                outfile << "data: " << val << " Appended" << std::endl;
            }else
            {
                outfile << "Failed to read the value for" <<std::endl;
            }
        }
        else if(command == "read") {
            int idx;
            if(ss >> idx) {
                if(idx < data.size()) {
                    std::cout << "Value at " << idx << ": " << data.at(idx) << std::endl;
                    outfile << "Value at index: " << idx  << ":" << data.at(idx) << std::endl;
                }else{
                    outfile << "Error :" << idx << " Is out of bound" << std::endl; 
                }
            }
        }
        else if(command == "write") {
            int val, idx;
            char at;
           
            if(ss >> val >> at >> idx) {
                if(idx < data.size()) {
                    data.at(idx) = val;
                    outfile << "data overrided" << std::endl;
                }
            }
        }
    }


   infile.close();

    
    return 0;



    
}