#include "array_stats.h"

asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size){
  int i;
  long local;
  long min;
  long max;
  long sum;

  //checking for valid input
  if (size <= 0){
    return -EINVAL;
  }
  if (stats == NULL || data == NULL){
    return -EFAULT;
  }

  for (i; i < size; i++){
    if (copy_from_user(&local, data[i])){
      return -EFAULT;
    }
    else{
      if(local > )
    }
  }
}
