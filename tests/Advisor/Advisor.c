int printk(int ptr, ...);
int scank(char ptr, ...);

static char strend = 0; 
static char strnewline = 10; 
static char strseq = 124; 
static char strspace = 32; 
static char str0 = 48; 
static char str1 = 49; 
static char str2 = 50; 
static char str3 = 51; 
static char str4 = 52; 
static char str5 = 53; 
static char gradeA = 65;
static char gradeB = 66;
static char gradeC = 67;
static char gradeD = 68;
static char gradeF = 70;

int myStrlen(char ptr s) {
    int i; 
    for (i = 0; s[i] != strend; i=i+1){}
    return i; 
}

int charAddStr(char chr, char ptr s) {
    int i; 
    i = myStrlen(s) + 1;
    for (; i>0; i=i-1) {
        s[i] = s[i-1];
    }
    s[0] = chr;

    return 0;
}

int eqStr(char ptr s1, char ptr s2) {
    int i; 
    for (i = 0; s1[i] != strend || s2[i] != strend; i=i+1){
        if (s1[i] != s2[i]) {
            return 0;
        }
    }
    return 1; 
}

int copyStr(char ptr s1, char ptr s2, int begin, char seq) {
    int i = 0; 
    for (i = 0; s2[begin] != seq; i=i+1) {
        s1[i] = s2[begin];
        begin = begin+1;
    }
    s1[i] = strend; 
    return 0; 
}

int appendStr(char ptr s1, char ptr s2, char seq) {
    int i; 
    int len = myStrlen(s1); 
    s1[len] = seq; 
    len = len + 1; 
    for(i = 0; s2[i] != strend; i=i+1) {
        s1[len] = s2[i];
        len = len+1; 
    }
    s1[len] = strend; 
    return 0;
}

int getSubStr(char ptr substr, char ptr str, int index, char seq) {
    int begin = 0; 
    for (;index != 0; index = index-1){
        while(str[begin] != seq) {
            begin = begin+1;
        }
        begin = begin+1;
    }
    int i = 0;
    while(str[begin] != seq && str[begin] != strend) {
        substr[i] = str[begin];
        i = i+1;
        begin = begin+1;
    }
    substr[i] = strend; 
    return 0;
}

int getStrIndex(char ptr substr, char ptr str, char seq) {
    int i = 0; 
    int i2 = 0;
    int index = 0; 
    int temp = 0;
    while(str[temp] != strend) {
        i = 0; 
        while(substr[i] != strend && str[i2] != strend && str[i2] != seq && (str[i2] == substr[i])) {
            i2 = i2+1;
            i = i+1; 
        }
        // printk("%d %d %d\n", index, i2, i);
        index = index + 1; 
        if (substr[i] == strend && (str[i2] == strend || str[i2] == seq)){
            return index;
        }
        // remember to go to strend or seq
        while(str[i2] != strend && str[i2] != seq) {
            i2 = i2+1;
        }

        temp = i2; 
        i2 = i2 + 1; 
    } 
    return 0;
}

int charToInt(char chr) {
    if (chr == str0) {
        return 0; 
    }
    if (chr == str1) {
        return 1; 
    }
    if (chr == str2) {
        return 2; 
    }
    if (chr == str3) {
        return 3; 
    }
    if (chr == str4) {
        return 4; 
    }
    if (chr == str5) {
        return 5; 
    }
    return 0;
}

int gradeToInt(char chr) {
    if (chr == gradeA) {
        return 4; 
    }
    if (chr == gradeB) {
        return 3; 
    }
    if (chr == gradeC) {
        return 2; 
    }
    if (chr == gradeD) {
        return 1; 
    }
    if (chr == gradeF) {
        return 0; 
    }
    return 0; 
}

int main(){
    char coursename[6]; 
    char coursescore; 
    char coursepre[1000]; 
    char coursegrade; 

    char oneline[1000];
    char firstchar; 
    char tempchar; 

    int score;
    int grade; 

    int score_learn = 0;
    int score_get = 0;
    int score_remain = 0; 
    int gpa = 0; 
    int cnt = 0;

    int cursor; 

    char names[1000];
    char pres[1000000];
    int learned[100];
    int learnable[100];

    // get read
    while(1) {
        // read the line
        scank("%c", &firstchar); 
        if (firstchar == strnewline) {
            // read over 

            // print the result
            printk("GPA: %d\n", gpa);
            printk("Hours Attempted: %d\n", score_learn); 
            printk("Hours Completed: %d\n", score_get);
            printk("Credits Remaining: %d\n\n", score_remain); 

            // print recommended course
            printk("Possible Courses to Take Next\n");
            if (score_remain) {

            }
            else {
                printk("\tNone - Congratulations!\n"); 
            }

            return 0;
        }
        scank("%s", oneline); 
        scank("%c", &tempchar); // remove the newline \n
        charAddStr(firstchar, oneline); 
        
        // decode the line
        cursor = 0;
        copyStr(coursename, oneline, cursor, strseq);
        cursor = myStrlen(coursename)+1; 
        coursescore = oneline[cursor];
        cursor = cursor + 2;
        copyStr(coursepre, oneline, cursor, strseq);
        cursor = cursor + myStrlen(coursepre) + 1; 
        coursegrade = oneline[cursor];

        score = charToInt(coursescore);
        grade = gradeToInt(coursegrade);

        // printk("%d %d %s %s\n", score, grade, coursename, coursepre);

        // renew the statistical information
        if (coursegrade == gradeF) {
            score_learn = score_learn + score;
            score_remain = score_remain + score;
            learned[cnt] = 0; 
        }
        else {
            if (coursegrade == strend) {
                score_remain = score_remain + score; 
                learned[cnt] = 0; 
            }
            else {
                score_learn = score_learn + score;
                score_get = score_get + score;
                gpa = gpa + grade*score; 
                learned[cnt] = 1; 
            }
        }
        cnt = cnt + 1; 

        // record the course

    }
    
	return 0;
}