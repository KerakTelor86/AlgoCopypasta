// 0-based
const vector<int> T = {
    0, 3, 2, 5, 0, 3, 
    5, 1, 4, 6, 2, 4
}

int day(int d, int m, int y)  
{  
    y -= (m < 3);  
    return (y + y / 4 - y / 100 + y / 400 + T[m - 1] + d) % 7;  
}  
