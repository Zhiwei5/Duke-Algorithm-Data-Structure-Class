#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

void access_setup(
    char ** access_ptr,
    long unsigned int read,
    long unsigned int write,
    long unsigned int executable);  // a helper function to set up the Access string in step2

void filetype_setup(
    const char ** filetype_ptr,
    char * access0,
    long unsigned int mode);  // a helper function to determine the file type in step 1

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "the input number is not right");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; ++i) {
    struct stat sb;

    if (lstat(argv[i], &sb) == -1) {
      perror("stat");
      exit(EXIT_FAILURE);
    }

    if (S_ISLNK(
            sb.st_mode)) {  // if the file is a symbolic link then need to print out the target of the link
      char linktarget[256];
      ssize_t len = readlink(argv[i], linktarget, 256);
      if (len < 0) {
        perror("lstat");
        exit(EXIT_FAILURE);
      }

      if (len > 256) {
        fprintf(stderr, "symlink write in size is over 256\n");
        exit(EXIT_FAILURE);
      }
      linktarget[len] = '\0';
      printf("  File: %s -> %s\n", argv[i], linktarget);
    }
    else {
      printf("  File: %s\n", argv[i]);
    }

    char access[11] = {'\0'};
    const char * file_type = NULL;
    int device_type = 0;
    if (S_ISCHR(sb.st_mode) ||
        S_ISBLK(
            sb.st_mode)) {  // if the device type is charachter or block device then need to print the device number later
      device_type = 1;
    }

    char * access0 = &access[0];
    filetype_setup(&file_type, access0, sb.st_mode & S_IFMT);

    printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",  //print sratement for step 1
           sb.st_size,
           sb.st_blocks,
           sb.st_blksize,
           file_type);

    if (device_type == 0) {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",  //print statement for step2
             sb.st_dev,
             sb.st_dev,
             sb.st_ino,
             sb.st_nlink);
    }
    if (device_type == 1) {
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
             sb.st_dev,
             sb.st_dev,
             sb.st_ino,
             sb.st_nlink,
             major(sb.st_rdev),
             minor(sb.st_rdev));
    }

    char * user_ptr = access + 1;
    access_setup(&user_ptr, sb.st_mode & S_IRUSR, sb.st_mode & S_IWUSR, sb.st_mode & S_IXUSR);
    char * group_ptr = access + 4;
    access_setup(&group_ptr, sb.st_mode & S_IRGRP, sb.st_mode & S_IWGRP, sb.st_mode & S_IXGRP);
    char * other_ptr = access + 7;
    access_setup(&other_ptr, sb.st_mode & S_IROTH, sb.st_mode & S_IWOTH, sb.st_mode & S_IXOTH);
    printf("Access: (%04o/%s)", sb.st_mode & ~S_IFMT, access);

    struct passwd * owner_struct_ptr = NULL;
    owner_struct_ptr = getpwuid(sb.st_uid);
    struct group * group_struct_ptr = NULL;
    group_struct_ptr = getgrgid(sb.st_gid);
    printf("  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
           sb.st_uid,
           owner_struct_ptr->pw_name,
           sb.st_gid,
           group_struct_ptr->gr_name);

    char * atime_str = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
    char * mtime_str = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
    char * ctime_str = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);

    printf("Access: %s\nModify: %s\nChange: %s\n Birth: -\n", atime_str, mtime_str, ctime_str);
    free(atime_str);
    free(mtime_str);
    free(ctime_str);
  }
  return EXIT_SUCCESS;
}

void access_setup(char ** access_ptr,
                  long unsigned int read,
                  long unsigned int write,
                  long unsigned int executable) {
  if (read)
    (*access_ptr)[0] = 'r';
  else {
    (*access_ptr)[0] = '-';
  }
  if (write)
    (*access_ptr)[1] = 'w';
  else {
    (*access_ptr)[1] = '-';
  }
  if (executable)
    (*access_ptr)[2] = 'x';
  else {
    (*access_ptr)[2] = '-';
  }
}

void filetype_setup(const char ** filetype_ptr, char * access0, long unsigned int mode) {
  switch (mode) {
    case S_IFBLK:
      (*filetype_ptr) = "block special file\n";
      (*access0) = 'b';

      break;
    case S_IFCHR:
      (*filetype_ptr) = "character special file\n";
      (*access0) = 'c';

      break;
    case S_IFDIR:
      (*filetype_ptr) = "directory\n";
      (*access0) = 'd';
      break;
    case S_IFIFO:
      (*filetype_ptr) = "fifo\n";
      (*access0) = 'p';
      break;
    case S_IFLNK:
      (*filetype_ptr) = "symbolic link\n";
      (*access0) = 'l';
      break;
    case S_IFREG:
      (*filetype_ptr) = "regular file\n";
      (*access0) = '-';
      break;
    case S_IFSOCK:
      (*filetype_ptr) = "socket\n";
      (*access0) = 's';
      break;
    default:
      (*filetype_ptr) = "unknown\n";
      break;
  }
}
