#include "KnownOperators.h"

std::string minus(std::string a, std::string b)
{
    size_t start = a.find(b);

    if(start != std::string::npos)
        a.erase(start, b.size());
    return a;
}

std::string multiplies2(std::string a, std::string b)
{
    int i = 0;
    int j = 0;
    std::string result("");
    std::string temp("");
    for(i = 0; i < a.size(); ++i)
    {
        for(j = 0; j < b.size() && i+j < a.size(); ++j)
        {
            if(a[i+j] == b[j])
                temp += a;
            else
            {
                if(result.size()<temp.size())
                    result = temp;
                temp = "";
                break;
            }
            if(result.size()<temp.size())
                result = temp;
            temp = "";
        }
    }
    return result;
}

std::string multiplies(std::string a, std::string b)
{
    const char* X = a.c_str();
    const char* Y = b.c_str();
    int m = a.size();
    int n = b.size();

        // Create a table to store lengths of longest common
        // suffixes of substrings.   Note that LCSuff[i][j]
        // contains length of longest common suffix of X[0..i-1]
        // and Y[0..j-1]. The first row and first column entries
        // have no logical meaning, they are used only for
        // simplicity of program
        int LCSuff[m + 1][n + 1];

        // To store length of the longest common substring
        int len = 0;

        // To store the index of the cell which contains the
        // maximum value. This cell's index helps in building
        // up the longest common substring from right to left.
        int row, col;

        /* Following steps build LCSuff[m+1][n+1] in bottom
           up fashion. */
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    LCSuff[i][j] = 0;

                else if (X[i - 1] == Y[j - 1]) {
                    LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                    if (len < LCSuff[i][j]) {
                        len = LCSuff[i][j];
                        row = i;
                        col = j;
                    }
                } else
                    LCSuff[i][j] = 0;
            }
        }

        // if true, then no common substring exists
        if (len == 0) {
            return "";
        }

        // allocate space for the longest common substring
        char* resultStr = (char*)malloc((len + 1) * sizeof(char));
        resultStr[len] = '&#092;&#048;';

        // traverse up diagonally form the (row, col) cell
        // until LCSuff[row][col] != 0
        while (LCSuff[row][col] != 0) {
            resultStr[--len] = X[row - 1]; // or Y[col-1]

            // move diagonally up to previous cell
            row--;
            col--;
        }

        // required longest common substring
        return std::string(resultStr);
}

std::string divides(std::string a, std::string b)
{
    size_t start = a.find(b);
    int result = 0;

    while(start != std::string::npos)
    {
        a.erase(start, b.size());
        start = a.find(b);
        ++result;
    }

    return std::to_string(result);
}
