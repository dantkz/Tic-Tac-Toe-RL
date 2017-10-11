#include "Move.h"
#include <string>
using namespace std;

namespace rlearning
{
    std::string Move::GetString()
    {
        string result = "";
        result += "Put ";
        result += ((Mark==1) ? "'x'" : "'o'");
        result += " on ";
        switch(Location)
        {
            case 0 :
                result += "top-left"; break;
            case 1 :
                result += "top-middle"; break;
            case 2 :
                result += "top-right"; break;
            case 3 :
                result += "left"; break;
            case 4 :
                result += "center"; break;
            case 5 :
                result += "right"; break;
            case 6 :
                result += "bottom-left"; break;
            case 7 :
                result += "bottom-middle"; break;
            case 8 :
                result += "bottom-right"; break;
        }
        //result += to_string((long long)Location); 
        result += " space.\n"; 
        return result;
    }

    //Mapping From all possible moves to unsigned int
    unsigned int Move::GetIndex()
    {
        int mark = (Mark+1)/2; //From -1 and 1 to 0 and 1.
        // There are 9 possible locations
        return (Mark*9 + Location);
    }
}
