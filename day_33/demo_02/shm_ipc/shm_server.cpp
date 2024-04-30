#include "Comm.hpp"

int main()
{
    cout << ToHex(GetshmKeyOrDie()) << endl;

    key_t key = GetshmKeyOrDie();
    int shmid = CreatShm(key, defaultSize);

    if (shmid < 0)
    {
        cerr << "CreatShm error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
        return 1;
    }
    else
    {
        cout << "shmid :" << shmid << endl;
    }

    cout << "server挂接前：" << endl;
    DebugShm(shmid);
    sleep(5);

    char *addr = (char *)ShmAttach(shmid);
    cout << "ShmAttach Address:" << ToHex((uint64_t)addr) << endl;

    cout << "server挂接后：" << endl;
    DebugShm(shmid);
    sleep(5);

    // 先创建管道
    Fifo fifo(PATH);
    Sync sync;
    sync.OpenReadOrDie();

    //  通信
    while (true)
    {
        bool ret = sync.Wait();
        if (ret == true)
        {
            cout << "shm content:" << addr << endl;
            sleep(1);
        }
        else
            break;
    }

    sleep(10);
    ShmDetach(addr);
    sleep(10);
    DeleteShm(shmid);
    sleep(5);
    return 0;
}