#include "Comm.hpp"

int main()
{
    int wfd = open(PATH, O_WRONLY);
    if (wfd < 0)
    {
        cerr << "open error,  "
             << "errorno:" << errno << " error info:" << strerror(errno) << endl;
        return 1;
    }
    string str;
    while (true)
    {
        cout << "please start write: ";
        getline(cin, str);
        if(str == "quit") break;
        ssize_t n = write(wfd, str.c_str(), str.size());
        if (n < 0)
        {
            cerr << "write error,  "
                 << "errorno:" << errno << " error info:" << strerror(errno) << endl;
            break;
        }
    }
    close(wfd);
    return 0;
}