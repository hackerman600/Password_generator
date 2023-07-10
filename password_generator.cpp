#include <string>
#include <iostream>
#include <sstream>
#include <random>
#include <any>
#include <tuple>
#include <algorithm> 
#include <cstdlib>

//compromised password list.

void presentation_screen(){
    std::string intro = R"(
                            /$$$$$$$                                                            /$$        /$$$$$$                     
                            | $$__  $$                                                          | $$       /$$__  $$                    
                            | $$  \ $$ /$$$$$$   /$$$$$$$ /$$$$$$$ /$$  /$$  /$$  /$$$$$$   /$$$$$$$      | $$  \__/  /$$$$$$  /$$$$$$$ 
                            | $$$$$$$/|____  $$ /$$_____//$$_____/| $$ | $$ | $$ /$$__  $$ /$$__  $$      | $$ /$$$$ /$$__  $$| $$__  $$
                            | $$____/  /$$$$$$$|  $$$$$$|  $$$$$$ | $$ | $$ | $$| $$  \__/| $$  | $$      | $$|_  $$| $$$$$$$$| $$  \ $$
                            | $$      /$$__  $$ \____  $$\____  $$| $$ | $$ | $$| $$      | $$  | $$      | $$  \ $$| $$_____/| $$  | $$
                            | $$     |  $$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$/$$$$/| $$      |  $$$$$$$      |  $$$$$$/|  $$$$$$$| $$  | $$
                            |__/      \_______/|_______/|_______/  \_____/\___/ |__/       \_______/       \______/  \_______/|__/  |__/)";

    std::cout << intro << "\n\n\n" << std::endl;                                                                                                                                                                                                                                                                  
}; 


std::string clean_up_the_input(std::string nouns){

    if (nouns.find(" ") == 0 || nouns.find(".") == 0){
        nouns = nouns.substr(1,nouns.length());
    }

    if (nouns.find(" ") == nouns.length() || nouns.find(".") == nouns.length()){
        nouns = nouns.substr(0,nouns.length()-1);
    }

    if (nouns.find(" ") != std::string::npos){
        std::replace(nouns.begin(), nouns.end(), ' ','.');
    } 

    if (nouns.find("..") != std::string::npos){
        
        std::string pattern = "..";
        std::string replacement = ".";
        std::size_t pos = nouns.find(pattern);
        while (pos != std::string::npos){
            nouns.replace(pos, pattern.length(), replacement);
            pos = nouns.find(pattern);
        }

    } 
    return nouns;   

} 

std::vector<std::string> pre_gen_password(){
    std::cout << "\nstrong passwords have a minimum of 8 characters, uppercase, lowercase, numbers and special characters. Let us make a strong password for you and store it safetly on your device.\n";
    std::string nounz; 
    std::string numbers;
    std::string full; 
    std::string catchr = "";
    std::string password = ""; 
    std::vector<std::string> numbz; 
    std::vector<std::string> nz;
    std::vector<std::string> passwords;
    std::vector<std::string> special = {"%","$","!","*"};
    std::vector<char> numbrz = {'0','1','2','3','4','5','6','7','8','9'};
    std::vector<char> alphabet = {'%','$','!','*'};      
    int itter = 0; 

    //add to alphabet;
    for (char letter = 'A'; letter <= 'Z'; ++letter){
        alphabet.push_back(letter);
    } for (char letter = 'a'; letter <= 'z'; ++letter){
        alphabet.push_back(letter);
    } for (int x = 0; x <= 9; x++){
        alphabet.push_back(x);
    }
   
    while(nounz.length() <= 0) {
        std::cout << "\ngive me the name of 1-3 people or locations that you cherish, follow each entry with a fullstop or a space: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, nounz);
        nounz = nounz;
    }

    nounz = clean_up_the_input(nounz);

    while(numbers.length() <= 0){
        std::cout << "\ngive me your fav 1-3 number(s), follow each entry with a space or fullstop: ";
        std::getline(std::cin, numbers);
        numbers = numbers;
    }

    numbers = clean_up_the_input(numbers);
 
    //std::cout << "\nfull is: " + numbers + "." + nounz << std::endl;
    std::cout << "\ngenerating your passwords now...\n\n";
    full = numbers + "." + nounz;

    for (char n : numbers){
        if (n == '.'){
            numbz.push_back(catchr);
            catchr = "";
        }

        else if (itter == numbers.length() - 1){
            catchr += n;
            numbz.push_back(catchr);
        }

        else{
            catchr += n;
        }     
        itter += 1;

    } catchr = ""; itter = 0;

    for (char n : nounz){
        if (n == '.'){
            nz.push_back(catchr);
            catchr = "";
        }

        else if (itter == nounz.length() - 1){
            catchr += n;
            nz.push_back(catchr);
        }

        else{
            catchr += n;
        }     
        itter += 1;
    }

    //std::cout << nz.size() << " " << numbz.size() << " " << special.size(); 
    
    //std::cout << "here <<<>>>";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::vector<std::vector<std::string>> options = {nz, numbz};

    //std::shuffle(alphabet.begin(), alphabet.end(),generator); 
    
    
    while (passwords.size() < 3){
        password = "";
        for (int i = 0; i <= 1; i++){
            std::vector<std::string> vector_corpus = options[i];
            std::uniform_int_distribution<int>corp_dist(0,vector_corpus.size()-1);
            
            password += vector_corpus[corp_dist(generator)];

            //std::cout << " password is: " << password << " i is: " << i << std::endl;

            
            if (password.length() >= 6){
                
                std::uniform_int_distribution<int>spec_dist(0,special.size()-1);
                std::string spesh = special[spec_dist(generator)];               
                //std::cout << "chosen special was: " <<  spesh << std::endl;
                //std::cout << "password was: " <<  password << std::endl;
                password += spesh;
                //std::cout << "password is: " <<  password << std::endl;


                if (i == 1){
                //check if number exists
                    int found = 0;
                    for (char no : numbrz){
                        if (password.find(no) != std::string::npos){
                            found = 1;
                            //std::cout << "number found was is: " <<  no << std::endl;
                            break;
          
                        }                       
                    }
                    if (found == 0){
                        //std::cout << "didn't find a number in: " <<  password << std::endl;
                        std::uniform_int_distribution<int>spec_dist(0,numbrz.size()-1);
                        char num = numbrz[spec_dist(generator)];  
                        std::string str(num,1);
                        //std::cout << "password was: " <<  password << std::endl;
                        password += str;
                        //std::cout << "password is: " <<  password << std::endl;
                        found = 1;

                    }
                    if (found == 1){
                        passwords.push_back(password);
                        found = 0;
                        break;
                    }
                }
                
         
            }

            //else if()
    }
    }

    
    //std::cout << passwords.size() << std::endl; 
    //std::cout << passwords[0];
    return passwords;
    

}

std::string print_passwords(std::vector<std::string> pwz){
    
    int itter = 0;
    std::string choice;

    for (auto p : pwz){
        std::cout << "pwz" << itter << ": " << p << std::endl;
        itter += 1;
    }

    bool con = true;

    while (con == true){

        std::cout << "\n\nchoose your favourite password, 0, 1 or 2: " << std::endl;
        std::cin >> choice;

        //std::cout << "\nur choice was: " << choice << std::endl;

        if (choice.find(".") != std::string::npos){
            std::cout << "\nplease do not use a decimal value" << std::endl;
        }

        else {
            int choice_i = std::stoi(choice);
            if (choice_i > 2){
                std::cout << "choose a value less than 2" << std::endl;
            } 
            else{
                choice = pwz[choice_i];
                break;
            }
        }   

    }    

    return choice;
    

}

void user_information(){

    std::string name;  

    std::cout << "1. Password generation:" << std::endl;
    std::cout << "2. File overwrite: " << std::endl;
    
    std::cout << "\nChoose 1 or 2: " << std::endl;
    std::cin >> name;

    if (name == "1"){
        std::vector<std::string> pwz = pre_gen_password();
        std::string password = print_passwords(pwz);
        password[0] = std::toupper(password[0]);
        std::cout << "chosen password is: " << password << std::endl; 
        std::cout << "saving password to localhost ...." << std::endl;

        int exitcode = std::system("ls -l");

        if (exitcode == 0){
            std::string action = "echo " + password + " > " + "Saved_password.txt";
            std::system(action.c_str());  
        }

        
    }
    else {
        std::string action = "echo Passwordwasoverwritten > Saved_password.txt";
        std::system(action.c_str());
    }

}

int main() { 

    
    presentation_screen();
    user_information();

    //std::cout << pw;
    return 0;
    
}

