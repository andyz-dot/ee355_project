
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}


// Phase 2 Part 3
// codeName("Enania", "Mordak Young") should return "enaniamordakyoung"
string codeName(string str1, string str2){
    string combined = str1 + str2;
    string result = "";
    for (int i = 0; i < (int)combined.length(); i++){
        char c = combined[i];
        // skip spaces so "Mordak Young" becomes "mordakyoung"
        if (c == ' ') continue;
        // 'A' is 65 and 'a' is 97, so we add 32 to any capital letter
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        result += c;
    }
    return result;
}