#include <iostream>
#include <map>
#include <utility>
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
    double avg_mark;
    //int counter;

    SStudData(std::string s_name, const int& n, std::string str_copy){
        name = std::move(s_name);
        Number = n;
        std::string str = std::move(str_copy);
        int sum = 0;
        while(str.find(',') != std::string::npos){
            SMark temp;
            temp.subject = str.substr(0, str.find(' '));
            str.erase(0, str.find(' ') + 1);
            temp.Mark = std::stoi(str.substr(0, str.find(',')));
            sum += temp.Mark;
            Marks.push_back(temp);
            str = str.erase(0, str.find(',') + 2);
        }
        SMark temp;
        temp.subject = str.substr(0, str.find(' '));
        str.erase(0, str.find(' ') + 1);
        temp.Mark = std::stoi(str.substr(0, str.find(',')));
        Marks.push_back(temp);
        avg_mark = sum / double(Marks.size());
    }

    SStudData(){
        name = "";
        Number = 0;
        avg_mark = 0;
        //counter = 0;
    }
};

void read_file(std::map<int, SStudData>& students){
    std::ifstream in("input.txt");
    if(in.is_open()){
        std::string str;
        while(std::getline(in, str)){
            auto i = str.find(';');
            std::string temp_num = str.substr(i + 1);
            int num = std::stoi(temp_num.substr(0, temp_num.find(';')));
            SStudData temp(str.substr(0, i), num, str.substr(str.rfind(';') + 1));
            students[temp.Number] = temp;
        }
    }
    in.close();
}



int main() {
    std::map<int, SStudData> students;
    read_file(students);
    std::cout << " ";
}