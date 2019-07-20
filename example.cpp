#include "hlapi/hlapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

FILE *dfile;

<<<<<<< HEAD
__attribute__((constructor)) void init() {
  FILE *out = stdout;
  pid_t pid;
=======
__attribute__((constructor))
static void init()
{
	FILE* out = stdout;
	pid_t pid;
>>>>>>> upstream/master
#if (LMODE() == MODE_EXTERNAL())
  FILE *pipe = popen("pidof qemu-system-x86_64", "r");
  fscanf(pipe, "%d", &pid);
  pclose(pipe);
#else
  out = fopen("/tmp/testr.txt", "w");
  pid = getpid();
#endif
  fprintf(out, "Using Mode: %s\n", TOSTRING(LMODE));

  dfile = out;

  try {
    WinContext ctx(pid);
    ctx.processList.Refresh();

    fprintf(out, "Process List:\n");
    for (auto &i : ctx.processList)
      fprintf(out, "%.4lx\t%s\n", i.proc.pid, i.proc.name);

    for (auto &i : ctx.processList) {
      if (!strcasecmp("r5apex.exe", i.proc.name)) {
        int health = i.Read<int>(0x01935F38);
        fprintf(out, "\nHealth: %d", health);
        fprintf(out, "\nLooping process %lx:\t%s\n", i.proc.pid, i.proc.name);

        PEB peb = i.GetPeb();
        short magic = i.Read<short>(peb.ImageBaseAddress);
        fprintf(out, "\tBase:\t%lx\tMagic:\t%hx (valid: %hhx)\n",
                peb.ImageBaseAddress, magic,
                (char)(magic == IMAGE_DOS_SIGNATURE));
      }
    }

  } catch (VMException &e) {
    fprintf(out, "Initialization error: %d\n", e.value);
  }
  fclose(out);
}

int main() { return 0; }
