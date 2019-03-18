#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <fibersapi.h>
#include <libloaderapi.h>
#include <direct.h>

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

int main(int argc, char *argv[]) {
    //TYPE=VECTOR COLOR=12 WIDTH=2 END_CAP=ARROW_ANCHOR  GEO=(151.5830, 46.9804 151.5610, 46.9854)
    //TYPE = POINT	COLOR = 10	GEO = (151.5830, 46.9804)	WIDTH = 10
    //TYPE = POINT	COLOR = 14	GEO = (151.5904, 46.9729)	WIDTH = 10
    std::string input_file_path = argv[1];
    replaceAll(input_file_path, "\\", "/");
    std::string line;
    std::ifstream file(input_file_path);
    std::string a, output_type;
    getline(file, output_type);
    std::vector<std::string> res;
    while(getline(file, line)){
        replaceAll(line, "\t", " ");
        replaceAll(line, ",", ".");
        for (char i : line)
            if (i != ' ')
                a += i;
            else{
                res.push_back(a);
                a = "";
            }
        res.push_back(a);
        a = "";
        if (output_type == "VECTOR"){
            std::cout << "TYPE=VECTOR COLOR=12 WIDTH=2 END_CAP=ARROW_ANCHOR GEO=(" << res[0] << ", "
                                                                                   << res[1] << " "
                                                                                   << res[2] <<", "
                                                                                   << res[3] << ")\n";
        }
        if (output_type == "VECTOR_POINTS"){
            std::cout << "TYPE=VECTOR COLOR=12 WIDTH=2 END_CAP=NO_ANCHOR GEO=(" << res[0] << ", "
                                                                                << res[1] << " "
                                                                                << res[2] <<", "
                                                                                << res[3] << ")\n";
            std::cout << "TYPE=POINT COLOR=10 GEO=(" << res[0] << ", " << res[1] <<") WIDTH=10\n";
            std::cout << "TYPE=POINT COLOR=14 GEO=(" << res[2] << ", " << res[3] <<") WIDTH=10\n\n";
        }
        res.clear();
    }
    return 0;
}