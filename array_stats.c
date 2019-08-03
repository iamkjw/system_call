#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include "array_stats.h"

asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size){
  int i;
  long local = 0;
  long min = LONG_MAX;
  long max = LONG_MIN;
  long sum = 0;

  //checking for valid input
  if (size <= 0){
    return -EINVAL;
  }
  if (stats == NULL || data == NULL){
    return -EFAULT;
  }

  for (i; i < size; i++){
    //validating pointer passed by user
    if (copy_from_user(&local, data[i], sizeof(long))){
      return -EFAULT;
    }
    else{
      if (local > max){
        max = local;
      }
      if (local < min){
        min = local;
      }
      sum += local;
    }
  }
  struct array_stats results = {min, max, sum};

  //inserting local results into user pointer
  if (copy_to_user(stats, &results, sizeof(struct array_stats){
    return -EFAULT;
  }
  return 0;
}
