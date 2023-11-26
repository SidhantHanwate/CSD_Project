
// const int CHAR_MAPS_SIZE = 127;
// const int CHAR_MAPS_ROW_SIZE = 11;
// const int SCREEN_SIZE = 1280 * 960;

void global()
{
    int charMaps[1397];
    int cursor_x = 0;
	int cursor_y = 0;
    int map[15];
    int screen[1228800];
    int charMasks[2];
}


void create(int index, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
    map[0] = a;
    map[1] = b;
    map[2] = c;
    map[3] = d;
    map[4] = e;
    map[5] = f;
    map[6] = g;
    map[7] = h;
    map[8] = i;
    map[9] = j;
    map[10] = k;
    int i1;
    for (i1 = 0; i1 < 11; i1=i1+1)
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

    create(58, 0, 0, 12, 12, 0, 0, 12, 12, 0, 0, 0);              // :
    create(59, 0, 0, 12, 12, 0, 0, 12, 12, 6, 0, 0);              // ;
    create(60, 0, 0, 24, 12, 6, 3, 6, 12, 24, 0, 0);              // <
    create(61, 0, 0, 0, 63, 0, 0, 63, 0, 0, 0, 0);                // =
    create(62, 0, 0, 3, 6, 12, 24, 12, 6, 3, 0, 0);               // >
    create(63, 30, 51, 51, 24, 12, 12, 0, 12, 12, 0, 0);          // ?
    create(64, 30, 51, 51, 59, 59, 59, 27, 3, 30, 0, 0);          // @
    create(65, 24, 36, 66, 129, 255, 129, 129, 129, 129, 129, 0); // A
    create(66, 254, 129, 129, 254, 129, 129, 129, 254, 0, 0, 0);  // B
    create(67, 126, 129, 128, 128, 128, 128, 129, 126, 0, 0, 0);  // C
    create(68, 254, 129, 129, 129, 129, 129, 129, 254, 0, 0, 0);  // D
    create(69, 255, 128, 128, 255, 128, 128, 128, 255, 0, 0, 0);  // E
    create(70, 255, 128, 128, 255, 128, 128, 128, 128, 0, 0, 0);  // F
    create(71, 255, 128, 128, 143, 129, 129, 129, 255, 0, 0, 0);  // G
    create(72, 129, 129, 129, 255, 129, 129, 129, 129, 0, 0, 0);  // H
    create(73, 255, 24, 24, 24, 24, 24, 24, 255, 0, 0, 0);        // I
    create(74, 255, 24, 24, 24, 24, 24, 129, 126, 0, 0, 0);       // J
    create(75, 129, 130, 132, 144, 128, 144, 132, 129, 0, 0, 0);  // K
    create(76, 128, 128, 128, 128, 128, 128, 128, 255, 0, 0, 0);  // L
    create(77, 129, 195, 165, 153, 129, 129, 129, 129, 0, 0, 0);  // M
    create(78, 129, 193, 161, 145, 137, 133, 131, 129, 0, 0, 0);  // N
    create(79, 126, 129, 129, 129, 129, 129, 129, 126, 0, 0, 0);  // O
    create(80, 255, 129, 129, 255, 128, 128, 128, 128, 0, 0, 0);  // P
    create(81, 126, 129, 129, 129, 145, 133, 121, 126, 0, 0, 0);  // Q
    create(82, 255, 129, 129, 255, 144, 132, 132, 129, 0, 0, 0);  // R
    create(83, 126, 129, 128, 126, 1, 1, 129, 126, 0, 0, 0);      // S
    create(84, 255, 24, 24, 24, 24, 24, 24, 24, 0, 0, 0);         // T
    create(85, 129, 129, 129, 129, 129, 129, 129, 126, 0, 0, 0);  // U
    create(86, 129, 66, 66, 36, 36, 24, 24, 24, 0, 0, 0);         // V
    create(87, 129, 129, 129, 129, 129, 165, 165, 153, 0, 0, 0);  // W
    create(88, 129, 66, 36, 24, 24, 36, 66, 129, 0, 0, 0);        // X
    create(89, 129, 66, 36, 24, 24, 24, 24, 24, 0, 0, 0);         // Y
    create(90, 255, 2, 4, 8, 16, 32, 64, 255, 0, 0, 0);           // Z

    create(91, 60, 48, 48, 48, 48, 48, 48, 60, 0, 0, 0); // [
    create(92, 128, 64, 32, 16, 8, 4, 2, 1, 0, 0, 0);    //
    create(93, 63, 3, 3, 3, 3, 3, 3, 63, 0, 0, 0);       // ]
    create(94, 0, 0, 24, 36, 66, 0, 0, 0, 0, 0, 0);      // ^
    create(95, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0);       // _
    create(96, 0, 128, 64, 0, 0, 0, 0, 0, 0, 0, 0);      // `

    create(97, 0, 28, 34, 2, 30, 34, 34, 34, 26, 0, 0);          // a
    create(98, 0, 128, 128, 128, 255, 129, 129, 129, 255, 0, 0); // b
    create(99, 0, 0, 0, 255, 128, 128, 128, 255, 0, 0, 0);       // c
    create(100, 0, 0, 128, 128, 128, 255, 129, 129, 255, 0, 0);  // d
    create(101, 0, 0, 255, 129, 129, 255, 128, 128, 255, 0, 0);  // e
    create(102, 0, 28, 54, 38, 6, 15, 6, 6, 6, 15, 0);           // f
    create(103, 0, 30, 51, 51, 51, 62, 48, 51, 30, 0, 0);        // g
    create(104, 3, 3, 3, 27, 55, 51, 51, 51, 51, 0, 0);          // h
    create(105, 12, 12, 0, 14, 12, 12, 12, 12, 30, 0, 0);        // i
    create(106, 48, 48, 0, 56, 48, 48, 48, 48, 51, 30, 0);       // j
    create(107, 3, 3, 3, 51, 27, 15, 15, 27, 51, 0, 0);          // k
    create(108, 14, 12, 12, 12, 12, 12, 12, 12, 30, 0, 0);       // l
    create(109, 0, 0, 0, 29, 63, 43, 43, 43, 43, 0, 0);          // m
    create(110, 0, 0, 0, 29, 51, 51, 51, 51, 51, 0, 0);          // n
    create(111, 0, 0, 0, 30, 51, 51, 51, 51, 30, 0, 0);          // o
    create(112, 0, 0, 0, 30, 51, 51, 51, 31, 3, 3, 0);           // p
    create(113, 0, 0, 0, 30, 51, 51, 51, 62, 48, 48, 0);         // q
    create(114, 0, 0, 0, 29, 55, 51, 3, 3, 7, 0, 0);             // r
    create(115, 0, 0, 0, 30, 51, 6, 24, 51, 30, 0, 0);           // s
    create(116, 4, 6, 6, 15, 6, 6, 6, 54, 28, 0, 0);             // t
    create(117, 0, 0, 0, 27, 27, 27, 27, 27, 54, 0, 0);          // u
    create(118, 0, 0, 0, 51, 51, 51, 51, 30, 12, 0, 0);          // v
    create(119, 0, 0, 0, 51, 51, 51, 63, 63, 18, 0, 0);          // w
    create(120, 0, 0, 0, 51, 30, 12, 12, 30, 51, 0, 0);          // x
    create(121, 0, 0, 0, 51, 51, 51, 62, 48, 24, 15, 0);         // y
    create(122, 0, 0, 0, 63, 27, 12, 6, 51, 63, 0, 0);           // z

    create(123, 56, 12, 12, 12, 7, 12, 12, 12, 56, 0, 0);  // {
    create(124, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0); // |
    create(125, 7, 12, 12, 12, 56, 12, 12, 12, 7, 0, 0);   // }
    create(126, 38, 45, 25, 0, 0, 0, 0, 0, 0, 0, 0);       // ~
}

int getIndex(char c)
{
    if (c < 32)
    {
        c = 0;
    }
    if(c > 126){
        c=0;
    }

    return 0;
}

void getMap(int index )
{
    int i;
    for (i = 0; i < 11;i=i+1)
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
    // int map[11];
    int index = getIndex(c);
    getMap(index);

    int address = (cursor_y * 1280 * 11) + (cursor_x / 11);
    int mask = cursor_x % 11;
	int i;
    for (i = 0; i < 11; i=i+1)
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
        address = address + 1280;
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


void printString(string s,int length)
{
	int i;
    for ( i = 0; i < length; i=i+1)
    {
        printChar(s[i]);
    }
}

void printInt(int num)
{
    int length = 0;
    if (num == 0) {
        return 1;
    }
    // Count the number of digits
    while (num != 0) {
        num = num/10;
        length = length+1;
    }
    string s = num;
    printString(s,length);
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

int main()
{
    global();
    init();
    return 0;
}