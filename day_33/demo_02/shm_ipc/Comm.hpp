#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "Fifo.hpp"

using namespace std;

const char *Path = "/home/xp2";
int proj_id = 0x168;
const int defaultSize = 4096;

string ToHex(key_t key)
{
    char buff[1024];
    snprintf(buff, sizeof(buff), "0x%x", key);
    return buff;
}

key_t GetshmKeyOrDie()
{
    key_t k = ftok(Path, proj_id);
    if (k < 0)
    {
        cerr << "ftok error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
        exit(1);
    }
    return k;
}

int CreatShmOrDie(key_t key, int size, int flag)
{
    int shmid = shmget(key, size, flag);
    if (shmid < 0)
    {
        cerr << "shmget error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
        exit(1);
    }
    return shmid;
}

int CreatShm(key_t key, int size)
{
    return CreatShmOrDie(key, size, IPC_CREAT | IPC_EXCL | 0666);
}

int GetShm(key_t key, int size)
{
    return CreatShmOrDie(key, size, IPC_CREAT);
}

// void *shmat(int shmid, const void *shmaddr, int shmflg);

//    int shmdt(const void *shmaddr);

void DeleteShm(int shmid)
{
    int n = shmctl(shmid, IPC_RMID, nullptr);
    if (n < 0)
    {
        cerr << "shmctl error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
    }
    else
    {
        cout << "shmctl delete shm sucess,"
             << "shmid :" << shmid << endl;
    }
}

void *ShmAttach(int shmid)
{
    void *addr = shmat(shmid, nullptr, 0);
    if ((long long int)addr == -1)
    {
        cerr << "shmat error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
        return nullptr;
    }
    return addr;
}

void ShmDetach(void *addr)
{
    int n = shmdt(addr);
    if (n < 0)
    {
        cerr << "shmdt error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
    }
}

void DebugShm(int shmid)
{
    struct shmid_ds shmds;
    int n = shmctl(shmid, IPC_STAT, &shmds);
    if (n < 0)
    {
        cerr << "Debug error, "
             << "error code: " << errno << ", error string :" << strerror(errno) << endl;
        return;
    }
    else
    {
        cout << "shmds.shm_segsz: " << shmds.shm_segsz << endl;
        cout << "shmds.shm_nattch: " << shmds.shm_nattch << endl;
        cout << "shmds.shm_ctime: " << shmds.shm_ctime << endl;
        cout << "shmds.shm_perm.__key: " << ToHex(shmds.shm_perm.__key) << endl;
    }
}
