%option never-interactive
%option outfile="microlexer.cpp"

%{
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SAVE_TOKEN yylval.strVal = new std::string(yytext, yyleng)

using namespace std;

class microdef{
public:
    char origin[256];
    char transform[256];
};

vector<microdef> microList; 
microdef temp; 

%}


/* 空白符和注释 */
WHTIESPACE              [ \t\n\r]*
LINECOMMET              "//".*
BLOCKCOMMET             "/*"[^*]*[*]+([^*/][^*]*[*]+)*"/"

/* 标识符 */
IDENTIFIER              [a-zA-Z_][a-zA-Z0-9_]*

/* 字符串 */
STRING                  [a-zA-Z0-9_]*

/* Define */
DEFINE                  #define

%s MICRODEFINE MICRODEFINE2

%%

<INITIAL>{WHTIESPACE}               { cout << yytext;}
<INITIAL>{LINECOMMET}               { cout << yytext;}
<INITIAL>{BLOCKCOMMET}              { cout << yytext;}
<MICRODEFINE>{WHTIESPACE}           { }
<MICRODEFINE2>{WHTIESPACE}          { }

<INITIAL>{DEFINE}                   { BEGIN MICRODEFINE; }

<MICRODEFINE>{IDENTIFIER}           {
                                        strcpy(temp.origin, yytext);
                                        BEGIN MICRODEFINE2; 
                                    }

<MICRODEFINE2>{STRING}              {
                                        strcpy(temp.transform, yytext);
                                        microList.push_back(temp); 
                                        BEGIN 0; 
                                    }

<INITIAL>{IDENTIFIER}               {   
                                        int i; 
                                        for(i = 0; i < microList.size(); i++) {
                                            if (!strcmp(yytext, microList[i].origin)) 
                                                break;
                                        }
                                        if (i == microList.size()) {
                                            cout << yytext; 
                                        }
                                        else {
                                            cout << microList[i].transform;
                                        }
                                    }

<INITIAL>.                          { cout << yytext; }

%%

int yywrap() {
    return 1;
}

int main(int argc, const char* argv[]) {
    string inputfile = argv[1], outputfile = argv[2]; 

    cout << "######## Micro Replace ########" << endl;
    cout << "inputfile: " << inputfile << endl; 
    cout << "outputfile: " << outputfile << endl;
    cout << "###############################" << endl;

    freopen(inputfile.c_str(), "r", stdin);
    freopen(outputfile.c_str(), "w", stdout);

    yylex();

    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);

    return 0;
}