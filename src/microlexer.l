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

%}


/* 空白符和注释 */
WHTIESPACE              [ \t\n\r]*
LINECOMMET              "//".*
BLOCKCOMMET             "/*"[^*]*[*]+([^*/][^*]*[*]+)*"/"

/* 标识符 */
IDENTIFIER              [a-zA-Z_][a-zA-Z0-9_]*

/* 字符串 */
STRING                  [^\s\t\n\r]*

/* Define */
MICRODEFINE             #define{WHTIESPACE}{IDENTIFIER}{WHTIESPACE}{STRING}

%%

{WHTIESPACE}            { cout << yytext;}
{LINECOMMET}            { cout << yytext;}
{BLOCKCOMMET}           { cout << yytext;}

{MICRODEFINE}           { 
                            microdef temp; 
                            int i;
                            char tstr[256]; 
                            for(i = 0; i < yyleng; i++) {
                                tstr[i] = yytext[i];
                            }
                            tstr[i] = '\0'; 
                            sscanf(tstr, "#define%s%s", temp.origin, temp.transform);
                            // cout << "A new micro " << yytext << "###" << endl;
                            // cout << "[A new micro " << temp.origin << "$" << temp.transform << "###" << strlen(yytext) << " " << yyleng << "]" << endl;
                            microList.push_back(temp); 
                        }

{IDENTIFIER}            {   
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

.                       { cout << yytext;}

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