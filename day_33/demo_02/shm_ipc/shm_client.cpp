#include "Comm.hpp"

int main()
{
    cout << ToHex(GetshmKeyOrDie()) << endl;

    key_t key = GetshmKeyOrDie();
    int shmid = GetShm(key, defaultSize);

    if (shmid < 0)
    {
        cerr << "GetShm error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
        return 1;
    }
    else
    {
        cout << "shmid :" << shmid << endl;
    }

    char *addr = (char *)ShmAttach(shmid); // 页表映射的逻辑地址罢了
    cout << "ShmAttach Address:" << ToHex((uint64_t)addr) << endl;

    cout << "client挂接后：" << endl;
    DebugShm(shmid);
    sleep(5);

    // 通信
    memset(addr, 0, defaultSize); // 根据逻辑地址找到物理地址并初始化

    Sync sync;
    sync.OpenWriteOrDie();

    for (char c = 'A'; c <= 'Z'; ++c)
    {
        addr[c - 'A'] = c;
        sleep(1);
        sync.WakeUp();
    }

    sleep(10);
    ShmDetach(addr);
    sleep(10);
    return 0;
}