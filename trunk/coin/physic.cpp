/*******************************************************
 *** Здесь реализуются функции, описанные в physic.h ***
 *******************************************************/

// Time-stamp: <physic.cpp - 01:22:19 08.11.2005>

#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

float WCOEF = 2.0;
float NOISEPOWER = 5.0;
float SLOMO = 20.0;
float STARTACCEL = 1.5;
int MAXVEL = 100;
int SEED = 0;

double myrand(int min, int max)
{
#if defined(Q_OS_WIN)

#else
  static int dev_random_fd = -1;
  char * next_random_byte;
  int bytes_to_read;
  unsigned random_value;

  assert(max > min);

  if (dev_random_fd == -1) {
    dev_random_fd = open("/dev/urandom", O_RDONLY);
    assert(dev_random_fd != -1);
  }
  next_random_byte = (char *)&random_value;
  bytes_to_read = sizeof(random_value);
  do {
    int bytes_read;
    bytes_read = read(dev_random_fd, next_random_byte, bytes_to_read);
    bytes_to_read -= bytes_read;
    next_random_byte += bytes_read;
  } while (bytes_to_read > 0);

  return min+(random_value%(max-min+1));
#endif
}
