#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
void ics53_hw3(char*);
char* get_perms(mode_t);
void ics53_hw3(char* name)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    struct passwd  *pwd;
    struct group   *grp;
    struct tm      *tm;
    char datestring[256];

    time_t t = mystat.st_mtime;
    struct tm lt;
    localtime_r(&t, &lt);

    mydir = opendir(name); 
    if (mydir == NULL)
    {
        stat(name, &mystat);
        printf("%10.10s", get_perms(mystat.st_mode));
        printf("%4d", mystat.st_nlink);
        if ((pwd = getpwuid(mystat.st_uid)) != NULL)
                printf(" %-8.8s", pwd->pw_name);
        else
                printf(" %-8d", mystat.st_uid);
        if ((grp = getgrgid(mystat.st_gid)) != NULL)
                printf(" %-8.8s", grp->gr_name);
        else
                printf(" %-8d", mystat.st_gid);

        printf(" %9jd", (intmax_t)mystat.st_size);

        t = mystat.st_mtime;
        localtime_r(&t, &lt);


        strftime(datestring, sizeof(datestring), "%B %e %R", &lt);

        printf(" %s %s\n", datestring, myfile->d_name);
        return;
    }
    while ((myfile = readdir(mydir)) != NULL)
    {
        char path[1024];
        strcpy(path, name);
        strcat(path, myfile->d_name);

        stat(path, &mystat);
        if (strcmp(".",myfile->d_name) != 0 && strcmp("..",myfile->d_name) != 0)
        {

                printf("%10.10s", get_perms(mystat.st_mode));
                printf("%4d", mystat.st_nlink);
                if ((pwd = getpwuid(mystat.st_uid)) != NULL)
                        printf(" %-8.8s", pwd->pw_name);
                else
                        printf(" %-8d", mystat.st_uid);
                if ((grp = getgrgid(mystat.st_gid)) != NULL)
                        printf(" %-8.8s", grp->gr_name);
                else
                        printf(" %-8d", mystat.st_gid);

                printf(" %9jd", (intmax_t)mystat.st_size);
                t = mystat.st_mtime;

                localtime_r(&t, &lt);

 
                strftime(datestring, sizeof(datestring),  "%B %e %R", &lt);


                printf(" %s %s\n", datestring, myfile->d_name);
        }

        if( stat(path ,&mystat) == 0 )
        {
                if( mystat.st_mode & S_IFDIR )
                {
                        if (strcmp(".",myfile->d_name) != 0 && strcmp("..",myfile->d_name) != 0)
                        {
                                ics53_hw3(strcat(path, "/"));
                        }
                }
        }
    }
        closedir(mydir);
}

char* get_perms(mode_t mode)
{
        char perms_buff[256] = "";
        char* str;
        str = perms_buff;
        char ftype = '?';
        if (S_ISREG(mode)) ftype = '-';
        if (S_ISLNK(mode)) ftype = 'l';
        if (S_ISDIR(mode)) ftype = 'd';
        if (S_ISBLK(mode)) ftype = 'b';
        if (S_ISCHR(mode)) ftype = 'c';
        if (S_ISFIFO(mode)) ftype = '|';
        sprintf(str, "%c%c%c%c%c%c%c%c%c%c %c%c%c",
                ftype,
                mode & S_IRUSR ? 'r' : '-',
                mode & S_IWUSR ? 'w' : '-',
                mode & S_IXUSR ? 'x' : '-',
                mode & S_IRGRP ? 'r' : '-',
                mode & S_IWGRP ? 'w' : '-',
                mode & S_IXGRP ? 'x' : '-',
                mode & S_IROTH ? 'r' : '-',
                mode & S_IWOTH ? 'w' : '-',
                mode & S_IXOTH ? 'x' : '-',
                mode & S_ISUID ? 'U' : '-',
                mode & S_ISGID ? 'G' : '-',
                mode & S_ISVTX ? 'S' : '-');
        return str;
}

int main(int argc, char* argv[])
{
        ics53_hw3(argv[1]);
        return 0;
}
                                
