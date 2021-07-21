#include <sys/utsname.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include <sys/resource.h>
#include <string.h>
#include <cmath>
using namespace std;

int Date(){

char command[50];
strcpy( command, "date +'Date = %A %d %B'");
system(command);

}

void Memory(){

system("awk -F ':|kB' '/MemTotal:/ {printf $2}' /proc/meminfo > memtotal.txt");
system("awk -F ':|kB' '/MemAvailable:/ {printf $2}' /proc/meminfo > memavailable.txt");
ifstream file1("memtotal.txt");
ifstream file2("memavailable.txt");
string temp1;
string temp2;
double memTotal;
double memAvailable;
getline(file1, temp1);
getline(file2, temp2);
memTotal = stod(temp1);
memAvailable = stod(temp2);
double memFree = memTotal - memAvailable;

memTotal = memTotal / 1024 / 1024;
memAvailable = memAvailable / 1024 / 1024;
memFree = memFree / 1024 / 1024;

memTotal = std::ceil(memTotal * 100.0) / 100.0;
memAvailable = std::ceil(memAvailable * 100.0) / 100.0;
memFree = std::ceil(memFree * 100.0) / 100.0;


cout << "Memory = " << memFree << "G / " << memTotal << "G " << endl;

system("rm memtotal.txt memavailable.txt");

}
int System()
{

  struct utsname uts;

  if (uname(&uts) < 0)
    perror("uname() error");
  else {
    printf("Operating System = %s\n", uts.sysname);
    printf("Kernel = %s\n", uts.release);
    printf("Host = %s\n", uts.machine);
	}
}
int Details()
{
  char hostname[HOST_NAME_MAX];
  char username[LOGIN_NAME_MAX];
  int result;
  result = gethostname(hostname, HOST_NAME_MAX);
  if (result)
    {
      perror("gethostname");
      return EXIT_FAILURE;
    }
  result = getlogin_r(username, LOGIN_NAME_MAX);
  if (result)
    {
      perror("getlogin_r");
      return EXIT_FAILURE;
    }
  result = printf("%s@%s\n",
                  username, hostname);

  if (result < 0)
    {
      perror("printf");
      return EXIT_FAILURE;
    }
}


int main(){


Details();
System();
Date();
Memory();

return (0);

}
