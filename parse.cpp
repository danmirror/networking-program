#include <iostream>
#include <string.h>
#include <stdio.h>

void parse(std::string str){
    int len = str.length();
    std::cout<<len<<std::endl;

    std::string array[10];

    int count=0;
    for(int i =0; i<=len; i++){
       if(str[i]== ',')
            continue;
        else{
            array[count]=str[i];
            count++;
        }
    }
    std::cout<<array[2]<<std::endl;
}

int main(){
    char *variabel = "2,3,4,4";
    std::string data ;

    data = variabel;
    std::cout<<data;
    parse(data);
}
