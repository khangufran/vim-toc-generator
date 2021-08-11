#include<iostream>
#include<map>
#include<cstring>
#include<string>
#include<algorithm>
#include<fstream>

std::string heading_identifier = "==[";

void usage(const char* s) {
    std::cout << "Usage: " << s << " <filename>" << std::endl;
    exit(1);
}

std::string toc_filename(const char* in_file) {
    int file_base_index = std::string(in_file).find("."); // index for . before extension
    std::string toc_filename = "toc_"+std::string(in_file,in_file+file_base_index)+".txt"; // toc file will be named toc<input_filename>.txt
    return toc_filename;
}

bool toc_exists(const char* in_file) {
    std::ifstream in(toc_filename(in_file));
    return in.good();
}

std::string generate_tag_name(std::string heading) {
    std::replace(heading.begin(),heading.end(),' ','_');
    return heading;
}

int generate_toc(const char* in_file) {
    std::ofstream toc(toc_filename(in_file),std::ios_base::out);

    std::string first_line = "|=" + std::string(86,'-') + "=|"+'\n';
    std::string second_line_text = std::string("Table of contents for ") + in_file;
    int padding = 80-second_line_text.size(); // 90 (total) - 4 (boundary) - 6 (text wrap) - file_name_size
    std::string second_line = "|=" + std::string(padding-padding/2,'-') + "=[ "
	+ second_line_text + " ]=" + std::string(padding/2,'-') + "=|" + '\n';

    toc << first_line << second_line << first_line << "\n\n";
    toc << "Table of Contents for " << in_file << "\n\n";

    std::ifstream in(in_file,std::ios_base::in);
    std::ofstream tags("tags",std::ios_base::out);
    std::map<std::string,std::string> tag_map;
    std::string line;
    int toc_heading_number = 1;
    while(getline(in,line)) {
	if(line.find(heading_identifier + " ") == 0) {
	    std::string heading(line.begin()+heading_identifier.size()+1,line.end());
	    std::string tag_name = generate_tag_name(heading);
	    toc << toc_heading_number++ <<". "<< tag_name << '\n';
	    tag_map[tag_name] = heading;
	}
    }
    std::map<std::string,std::string>::const_iterator iter = tag_map.begin();
    while(iter != tag_map.end()) {
	tags << iter->first << '\t' << "./" << in_file << '\t' << "/" << iter->second << '\n';
	iter++;
    }

    toc.close();
    in.close();
    tags.close();
    return 0;
}

int update_toc(const char* in_file) {
    return 0;
}

int main(int argc, char** argv) {
    if(argc != 2)
	usage(argv[0]);

    if(toc_exists(argv[1])) {
	//update_toc(argv[1]);
warning:
	std::cout << "toc file already exists!\nIf you want to regenerate toc, type y or n: ";
	char c;
	std::cin >> c;
	if(c=='y') {
	    generate_toc(argv[1]);
	} else if(c=='n')
	    ;
	else goto warning;
    }
    else {
	generate_toc(argv[1]);
    }

    return 0;
}
