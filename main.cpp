#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Journal{
private:
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

        SStudData(std::string s_name, const int& n, std::string str){
            name = std::move(s_name);
            Number = n;
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
            sum += temp.Mark;
            Marks.push_back(temp);
            avg_mark = sum / double(Marks.size());
        }

        SStudData(){
            name = "";
            Number = 0;
            avg_mark = 0;
        }
    };

    std::map<int, SStudData> students;

public:
    Journal()= default;
    void read_file(const std::string& file_name = "input.txt");
    void print_journal();
    void print_by_name();
    void print_by_avg_mark(const int& a, const int& b);
    void print_by_subject(const std::string& str);
    void number_of_students_by_subject();
    void avg_mark_by_subject();
    void print_max_sum_marks();
    void print_dissuasive_marks();
};

void Journal::read_file(const std::string& file_name){
    std::ifstream in(file_name);
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

void Journal::print_journal(){
    std::cout << "Journal:" << std::endl;
    for(auto& i : students){
        std::cout << i.second.Number << " | " << i.second.name << " | ";
        for(auto& j : i.second.Marks){
            std::cout << j.subject << " " << j.Mark << " ";
        }
        std::cout << "| " << i.second.avg_mark << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

bool compare_vector_by_name(std::vector<std::string> a, std::vector<std::string> b){
    if(a[0] != b[0]){
        return a[0] < b[0];
    }
    else {
        return a[2] > b[2];
    }
}

void Journal::print_by_name(){
    std::cout << "Students sorted by name:" << std::endl;
    std::vector <std::string> info;
    std::vector <std::vector<std::string> > vec;
    for(auto& i : students){
        info.push_back(i.second.name.substr(0, i.second.name.find(' ')));
        info.push_back(std::to_string(i.second.Number));
        info.push_back(std::to_string(i.second.avg_mark).substr(0, 4));
        vec.push_back(info);
        info.clear();
    }
    std::sort(vec.begin(), vec.end(), compare_vector_by_name);
    int count = 1;
    for(auto& i : vec){
        std::cout << count << ") " << i[0] << " | " << i[1] << " | " << i[2] << std::endl;
        count++;
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

bool compare_vec_by_avg_mark(std::vector<std::string> a, std::vector<std::string> b){
    return a[2] > b[2];
}

void Journal::print_by_avg_mark(const int& a, const int& b){
    std::cout << "Students sorted by avg mark:" << std::endl;
    std::vector <std::string> info;
    std::vector <std::vector<std::string> > vec;
    for(auto& i : students){
        if(i.second.avg_mark >= a && i.second.avg_mark <= b){
            info.push_back(i.second.name);
            info.push_back(std::to_string(i.second.Number));
            info.push_back(std::to_string(i.second.avg_mark).substr(0, 4));
            vec.push_back(info);
            info.clear();
        }
    }
    std::sort(vec.begin(), vec.end(), compare_vec_by_avg_mark);
    int count = 1;
    for(auto& i : vec){
        std::cout << count << ") " << i[0] << " | " << i[1] << " | " << i[2] << std::endl;
        count++;
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

void Journal::print_by_subject(const std::string& str){
    std::cout << "Students who took the subject " << str << " and their mark:" << std::endl;
    for(auto& i : students){
        for(auto& j : i.second.Marks){
            if(j.subject == str){
                std::cout << i.second.Number << " | " << i.second.name << " | " << j.Mark << std::endl;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

void Journal::number_of_students_by_subject(){
    std::cout << "Number of students by subject:" << std::endl;
    std::map<std::string, int> subjects;
    for(auto& i : students){
        for(auto& j : i.second.Marks){
            subjects[j.subject]++;
        }
    }
    for(auto& i : subjects){
        std::cout << i.first << ": " << i.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

bool compare_vec_pair_by_avg_mark(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b){
    return a.second > b.second;
}

void Journal::avg_mark_by_subject(){
    std::cout << "Avg mark by subject:" << std::endl;
    std::map<std::string, double> subjects;
    std::map<std::string, int> num;
    for(auto& i : students){
        for(auto& j : i.second.Marks){
            num[j.subject]++;
        }
    }
    for(auto& i : students){
        for(auto& j : i.second.Marks){
            subjects[j.subject] += j.Mark / double(num[j.subject]);
        }
    }
    std::vector <std::pair<std::string, double> > vec;
    for(auto& i : subjects){
        vec.emplace_back(i.first, i.second);
    }
    std::sort(vec.begin(), vec.end(), compare_vec_pair_by_avg_mark);
    for(auto& i : vec){
        std::cout << i.first << " - " << i.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

void Journal::print_max_sum_marks(){
    std::map<int, int> students_marks; // number, sum
    int max = 0;
    for(auto& i : students){
        int sum = 0;
        for(auto& j : i.second.Marks){
            students_marks[i.second.Number] += j.Mark;
            sum += j.Mark;
        }
        if(sum > max){
            max = sum;
        }
    }
    std::cout << "Students with max sum (" << max << ") of marks:" << std::endl;
    for (auto& i : students_marks){
        if(i.second == max){
            auto it = students.find(i.first);
            std::cout << it->second.Number << " | " << it->second.name << " | ";
            for(auto& j : it->second.Marks){
                std::cout << j.subject << " " << j.Mark << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

void Journal::print_dissuasive_marks(){
    std::cout << "Students with dissuasive marks:" << std::endl;
    for (auto& i : students){
        for(auto& j : i.second.Marks){
            if(j.Mark <= 3){
                std::cout << i.second.Number << " | " << i.second.name << " | " << j.subject
                << " " << j.Mark << std::endl;
                break;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------------\n";
    std::cout << std::endl;
}

int main() {
    Journal group11;
    group11.read_file();
    group11.print_journal();
    group11.print_by_name();
    group11.print_by_avg_mark(4, 10);
    group11.print_by_subject("Math");
    group11.number_of_students_by_subject();
    group11.avg_mark_by_subject();
    group11.print_max_sum_marks();
    group11.print_dissuasive_marks();
    return 0;
}