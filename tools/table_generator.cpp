#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

char et[64] = {
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0x0, 0x0
};

uint32_t dt[1024];

void generate_and_print(string preset_name, char _62, char _63)
{
    et[62] = _62;
    et[63] = _63;

    fill_n(dt, 1024, 0b1111'1100u);

    uint32_t i = 0;
    for (char c : et)
    {
        dt[  0 + c] = i << 26;
        dt[256 + c] = i << 20;
        dt[512 + c] = i << 14;
        dt[768 + c] = i <<  8;
        i++;
    }
    dt[  0 + '='] = 0b1111'1100u;
    dt[256 + '='] = 0b1111'1100u;
    dt[512 + '='] = 0b0000'0010u;
    dt[768 + '='] = 0b0000'0001u;

    cout << "/* " << preset_name << " */" << endl;
    cout << "#define MTRP_B64_DT_" << uppercase << hex << (int)_62 << (int)_63 << " \\" << endl;
    cout << "uint32_t const dt[1024] = {\\" << endl;
    int num = 0;
    for (uint32_t dword : dt)
    {
        cout << "0x" << setfill('0') << setw(8) << right << hex << dword << ", ";
        num++;

        if (num >= 16  && (num %  16) == 0) cout << "\\" << endl;
        if (num >= 256 && (num % 256) == 0) cout << "\\" << endl;
    }
    cout << "};" << endl;
}

int main()
{
    generate_and_print("base64 (standard)", '+', '/');
    generate_and_print("base64 (url)", '-', '_');
}
