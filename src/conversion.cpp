/*
    kajiya2D is an editor for leveldata for heikiko2D/nodachi2D.
    Copyright (C) 2010-2011  Paul Predkiewicz

    kajiya2D is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <conversion.hpp>

namespace conversion
{
    std::string itoa (int n) {
        char * s = new char[17];
        std::string u;

        if (n < 0) { //turns n positive
            n = (-1 * n);
            u = "-"; //adds '-' on result string
        }

        int i=0; //s counter

        do {
            s[i++]= n%10 + '0'; //conversion of each digit of n to char
            n -= n%10; //update n value
        }
        while ((n /= 10) > 0);

        for (int j = i-1; j >= 0; j--) {
            u += s[j]; //building our string number
        }

        delete[] s; //free-up the memory!
        return u;
    }
}
