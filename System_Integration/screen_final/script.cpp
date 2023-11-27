#include <iostream>
#include <string>
using namespace std;

// const int CHAR_MAPS_SIZE = 127;
// const int CHAR_MAPS_ROW_SIZE = 11;
// const int SCREEN_SIZE = 32 * 960;

int charMaps[127 * 11];
int cursor_x = 0, cursor_y = 0;
int screen[32 * 23];
int backupScreen[32 * 23];
int charMasks[4];

void backupOriginalScreen()
{
    for (int i = 0; i < 32 * 23; ++i)
    {
        backupScreen[i] = screen[i];
    }
}

void revertToOriginalScreen()
{
    for (int i = 0; i < 32 * 23; ++i)
    {
        screen[i] = backupScreen[i];
    }
}

void create(int index, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
    int map[11] = {a, b, c, d, e, f, g, h, i, j, k};
    for (int i1 = 0; i1 < 11; i1=i1+1)
    {
        charMaps[index * 11 + i1] = map[i1];
    }
}

void initMap()
{
    // Initialize charMaps here
    create(32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);          //
    create(33, 12, 30, 30, 30, 12, 12, 0, 12, 12, 0, 0);  // !
    create(34, 54, 54, 20, 0, 0, 0, 0, 0, 0, 0, 0);       // "
    create(35, 0, 18, 18, 63, 18, 18, 63, 18, 18, 0, 0);  // #
    create(36, 12, 30, 51, 3, 30, 48, 51, 30, 12, 12, 0); // $
    create(37, 0, 0, 35, 51, 24, 12, 6, 51, 49, 0, 0);    // %
    create(38, 12, 30, 30, 12, 54, 27, 27, 27, 54, 0, 0); // &
    create(39, 12, 12, 6, 0, 0, 0, 0, 0, 0, 0, 0);        // '
    create(40, 24, 12, 6, 6, 6, 6, 6, 12, 24, 0, 0);      // (
    create(41, 6, 12, 24, 24, 24, 24, 24, 12, 6, 0, 0);   // )
    create(42, 0, 0, 0, 51, 30, 63, 30, 51, 0, 0, 0);     // *
    create(43, 0, 0, 0, 12, 12, 63, 12, 12, 0, 0, 0);     // +
    create(44, 0, 0, 0, 0, 0, 0, 0, 12, 12, 6, 0);        // ,
    create(45, 0, 0, 0, 0, 0, 63, 0, 0, 0, 0, 0);         // -
    create(46, 0, 0, 0, 0, 0, 0, 0, 12, 12, 0, 0);        // .
    create(47, 0, 0, 32, 48, 24, 12, 6, 3, 1, 0, 0);      // /

    create(48, 12, 30, 51, 51, 51, 51, 51, 30, 12, 0, 0); // 0
    create(49, 12, 14, 15, 12, 12, 12, 12, 12, 63, 0, 0); // 1
    create(50, 30, 51, 48, 24, 12, 6, 3, 51, 63, 0, 0);   // 2
    create(51, 30, 51, 48, 48, 28, 48, 48, 51, 30, 0, 0); // 3
    create(52, 16, 24, 28, 26, 25, 63, 24, 24, 60, 0, 0); // 4
    create(53, 63, 3, 3, 31, 48, 48, 48, 51, 30, 0, 0);   // 5
    create(54, 28, 6, 3, 3, 31, 51, 51, 51, 30, 0, 0);    // 6
    create(55, 63, 49, 48, 48, 24, 12, 12, 12, 12, 0, 0); // 7
    create(56, 30, 51, 51, 51, 30, 51, 51, 51, 30, 0, 0); // 8
    create(57, 30, 51, 51, 51, 62, 48, 48, 24, 14, 0, 0); // 9

    create(58, 0, 0, 12, 12, 0, 0, 12, 12, 0, 0, 0);     // :
    create(59, 0, 0, 12, 12, 0, 0, 12, 12, 6, 0, 0);     // ;
    create(60, 0, 0, 24, 12, 6, 3, 6, 12, 24, 0, 0);     // <
    create(61, 0, 0, 0, 63, 0, 0, 63, 0, 0, 0, 0);       // =
    create(62, 0, 0, 3, 6, 12, 24, 12, 6, 3, 0, 0);      // >
    create(63, 30, 51, 51, 24, 12, 12, 0, 12, 12, 0, 0); // ?
    create(64, 30, 51, 51, 59, 59, 59, 27, 3, 30, 0, 0); // @

    create(65, 12, 30, 51, 51, 63, 51, 51, 51, 51, 0, 0);  // A
    create(66, 31, 51, 51, 51, 31, 51, 51, 51, 31, 0, 0);  // B
    create(67, 28, 54, 35, 3, 3, 3, 35, 54, 28, 0, 0);     // C
    create(68, 15, 27, 51, 51, 51, 51, 51, 27, 15, 0, 0);  // D
    create(69, 63, 51, 35, 11, 15, 11, 35, 51, 63, 0, 0);  // E
    create(70, 63, 51, 35, 11, 15, 11, 3, 3, 3, 0, 0);     // F
    create(71, 28, 54, 35, 3, 59, 51, 51, 54, 44, 0, 0);   // G
    create(72, 51, 51, 51, 51, 63, 51, 51, 51, 51, 0, 0);  // H
    create(73, 30, 12, 12, 12, 12, 12, 12, 12, 30, 0, 0);  // I
    create(74, 60, 24, 24, 24, 24, 24, 27, 27, 14, 0, 0);  // J
    create(75, 51, 51, 51, 27, 15, 27, 51, 51, 51, 0, 0);  // K
    create(76, 3, 3, 3, 3, 3, 3, 35, 51, 63, 0, 0);        // L
    create(77, 33, 51, 63, 63, 51, 51, 51, 51, 51, 0, 0);  // M
    create(78, 51, 51, 55, 55, 63, 59, 59, 51, 51, 0, 0);  // N
    create(79, 30, 51, 51, 51, 51, 51, 51, 51, 30, 0, 0);  // O
    create(80, 31, 51, 51, 51, 31, 3, 3, 3, 3, 0, 0);      // P
    create(81, 30, 51, 51, 51, 51, 51, 63, 59, 30, 48, 0); // Q
    create(82, 31, 51, 51, 51, 31, 27, 51, 51, 51, 0, 0);  // R
    create(83, 30, 51, 51, 6, 28, 48, 51, 51, 30, 0, 0);   // S
    create(84, 63, 63, 45, 12, 12, 12, 12, 12, 30, 0, 0);  // T
    create(85, 51, 51, 51, 51, 51, 51, 51, 51, 30, 0, 0);  // U
    create(86, 51, 51, 51, 51, 51, 30, 30, 12, 12, 0, 0);  // V
    create(87, 51, 51, 51, 51, 51, 63, 63, 63, 18, 0, 0);  // W
    create(88, 51, 51, 30, 30, 12, 30, 30, 51, 51, 0, 0);  // X
    create(89, 51, 51, 51, 51, 30, 12, 12, 12, 30, 0, 0);  // Y
    create(90, 63, 51, 49, 24, 12, 6, 35, 51, 63, 0, 0);   // Z

    create(91, 30, 6, 6, 6, 6, 6, 6, 6, 30, 0, 0);        // [
    create(92, 0, 0, 1, 3, 6, 12, 24, 48, 32, 0, 0);      //
    create(93, 30, 24, 24, 24, 24, 24, 24, 24, 30, 0, 0); // ]
    create(94, 8, 28, 54, 0, 0, 0, 0, 0, 0, 0, 0);        // ^
    create(95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 0);         // _
    create(96, 6, 12, 24, 0, 0, 0, 0, 0, 0, 0, 0);        // `

    create(97, 0, 0, 0, 14, 24, 30, 27, 27, 54, 0, 0);     // a
    create(98, 3, 3, 3, 15, 27, 51, 51, 51, 30, 0, 0);     // b
    create(99, 0, 0, 0, 30, 51, 3, 3, 51, 30, 0, 0);       // c
    create(100, 48, 48, 48, 60, 54, 51, 51, 51, 30, 0, 0); // d
    create(101, 0, 0, 0, 30, 51, 63, 3, 51, 30, 0, 0);     // e
    create(102, 28, 54, 38, 6, 15, 6, 6, 6, 15, 0, 0);     // f
    create(103, 0, 0, 30, 51, 51, 51, 62, 48, 51, 30, 0);  // g
    create(104, 3, 3, 3, 27, 55, 51, 51, 51, 51, 0, 0);    // h
    create(105, 12, 12, 0, 14, 12, 12, 12, 12, 30, 0, 0);  // i
    create(106, 48, 48, 0, 56, 48, 48, 48, 48, 51, 30, 0); // j
    create(107, 3, 3, 3, 51, 27, 15, 15, 27, 51, 0, 0);    // k
    create(108, 14, 12, 12, 12, 12, 12, 12, 12, 30, 0, 0); // l
    create(109, 0, 0, 0, 29, 63, 43, 43, 43, 43, 0, 0);    // m
    create(110, 0, 0, 0, 29, 51, 51, 51, 51, 51, 0, 0);    // n
    create(111, 0, 0, 0, 30, 51, 51, 51, 51, 30, 0, 0);    // o
    create(112, 0, 0, 0, 30, 51, 51, 51, 31, 3, 3, 0);     // p
    create(113, 0, 0, 0, 30, 51, 51, 51, 62, 48, 48, 0);   // q
    create(114, 0, 0, 0, 29, 55, 51, 3, 3, 7, 0, 0);       // r
    create(115, 0, 0, 0, 30, 51, 6, 24, 51, 30, 0, 0);     // s
    create(116, 4, 6, 6, 15, 6, 6, 6, 54, 28, 0, 0);       // t
    create(117, 0, 0, 0, 27, 27, 27, 27, 27, 54, 0, 0);    // u
    create(118, 0, 0, 0, 51, 51, 51, 51, 30, 12, 0, 0);    // v
    create(119, 0, 0, 0, 51, 51, 51, 63, 63, 18, 0, 0);    // w
    create(120, 0, 0, 0, 51, 30, 12, 12, 30, 51, 0, 0);    // x
    create(121, 0, 0, 0, 51, 51, 51, 62, 48, 24, 15, 0);   // y
    create(122, 0, 0, 0, 63, 27, 12, 6, 51, 63, 0, 0);     // z

    create(123, 56, 12, 12, 12, 7, 12, 12, 12, 56, 0, 0);  // {
    create(124, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0); // |
    create(125, 7, 12, 12, 12, 56, 12, 12, 12, 7, 0, 0);   // }
    create(126, 38, 45, 25, 0, 0, 0, 0, 0, 0, 0, 0);       // ~
}

int getIndex(char c)
{
    if ((c < 32) || (c > 126))
    {
        c = 0;
    }

    return c;
}

void getMap(int index, int map[])
{
    for (int i = 0; i < 11; ++i)
    {
        map[i] = charMaps[index * 11 + i];
    }
}

void init()
{
    cursor_x = 0;
    cursor_y = 0;
    charMasks[0] = 255;
    charMasks[1] = -1;
    initMap();
}

void moveCursor(int i, int j)
{
    cursor_x = j;
    cursor_y = i;
}

void scroll()
{
    cursor_x = 0;
    cursor_y = 0;
}

void println()
{
    cursor_x = 0;
    if (cursor_y < 959)
    {
        cursor_y = cursor_y + 1;
    }
    else
    {
        scroll();
    }
}

void printChar(char c)
{
    int map[11];
    int index = getIndex(c);
    getMap(index, map);

    int address = (cursor_y * 32 * 11) + (cursor_x / 11);
    int mask = cursor_x % 11;

    for (int i = 0; i < 11; i=i+1)
    {
        int bitmap = map[i];
        if (mask != 0)
        {
            int shift = mask;
            int multiplier = 1;
            while (shift > 0)
            {
                multiplier = multiplier * 2;
                shift = shift - 1;
            }
            bitmap = bitmap * multiplier;
        }
        screen[address] = screen[address] + bitmap; // Use addition to combine the existing data with the new bitmap
        address = address + 32;
    }

    if (cursor_x == 1279)
    {
        println();
    }
    else
    {
        cursor_x = cursor_x + 8;
    }
}


void printString(string s)
{
    for (int i = 0; i < s.length(); ++i)
    {
        printChar(s[i]);
    }
}

void printInt(int i)
{
    string s = to_string(i);
    printString(s);
}

void backSpace()
{
    if (cursor_x == 0)
    {
        if (cursor_y != 0)
        {
            cursor_x = 1279;
            cursor_y = cursor_y - 1;
        }
    }
    else
    {
        cursor_x = cursor_x - 11;
    }
}

int *getScreen()
{
    return screen;
}

int main()
{
    init();
    string a,b;
    cin >> a;
    printString(a);
    int k=0;

   
    backupOriginalScreen();

    // Print the modified string
    printString(a);

    // Retrieve the modified screen
    int *modifiedScreen = getScreen();

    // Revert to the original screen
    revertToOriginalScreen();
   
    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            cout << ((modifiedScreen[i * 32 + j / 11] & (1 << (j % 11))) ? '1' : '0');
        }
        cout<<endl;
        moveCursor(cursor_y + 1, 0);
        // for(int l=0;l<19;l++)
        // {
        //     for(int u=0;u<32;u++)
        //     {
        //         cout<<'0';
        //     }
        //     cout<<endl;
        // }
       
    }
    
   
   cin>>b;
   
    backupOriginalScreen();

    // Print the modified string
    printString(b);

    // Retrieve the modified screen
    int *modifiedScreen1 = getScreen();

    // Revert to the original screen
    revertToOriginalScreen();
   
    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            cout << ((modifiedScreen1[i * 32 + j / 11] & (1 << (j % 11))) ? '1' : '0');
        }
        cout<<endl;
        moveCursor(cursor_y + 1, 0);
        // for(int l=0;l<19;l++)
        // {
        //     for(int u=0;u<32;u++)
        //     {
        //         cout<<'0';
        //     }
        //     cout<<endl;
        // }
       
    }
   
    return 0;
}