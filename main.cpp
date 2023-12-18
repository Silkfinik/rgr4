#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>


struct SMark{
    std::string subject;
    int Mark;

    SMark(const std::string& str, const int& n){
        subject = str;
        Mark = n;
    }

    SMark(){
        subject = "";
        Mark = 0;
    }
};

struct SStudData{
    std::string name;
    int Number;
    std::vector <SMark> Marks;

    SStudData(std::string s_name, const int& n, std::string str_copy){
        name = s_name;
        Number = n;
        std::string str = str_copy;
        while(str.find(',') != std::string::npos){
            SMark temp;
            temp.subject = str.substr(0, str.find(' '));
            str.erase(0, str.find(' ') + 1);
            temp.Mark = std::stoi(str.substr(0, str.find(',')));
            Marks.push_back(temp);
            str = str.erase(0, str.find(',') + 1);
        }
        //Marks.push_back(temp);
    }

    SStudData(){
        name = "";
        Number = 0;
    }
};

struct comp_by_number {
    bool operator()(const SStudData& a, const SStudData& b) const {
        return a.Number < b.Number;
    }
};

void read_file(std::map<int, SStudData>& students){
    std::ifstream in("input.txt");
    if(in.is_open()){
        std::string str;
        int counter = 0;
        while(std::getline(in, str)){
            auto i = str.find(';');
            auto ri = str.rfind(';');
            std::string temp_num = str.substr(i + 1);
            int num = std::stoi(temp_num.substr(0, temp_num.find(';')));
            SStudData temp(str.substr(0, i), num, str.substr(str.rfind(';') + 1));
            students[++counter] = temp;
        }
    }
    in.close();
}

int main(){
    std::map<int, SStudData> students;
    read_file(students);
    std::cout << " ";
}