#include "process_ancestors.h"
#include <linux/sched.h>

asmlinkage long sys_process_ancestors(
                struct process_info info_array[],
                long size,
                long *num_filled);


asmlinkage long sys_process_ancestors(struct process_info info_array[], long size, long *num_filled){
	
	struct process_info info;
	int i;
	int j;
	struct list_head *list_head_child;
	int num_child = 0;
	struct list_head *list_head_sib;
	int num_sib = 0;
	struct task_struct cur_task = current;

	if (size <= 0){
	    printk("size <= 0\n");
	    return -EINVAL;
	}

	if (info_array == NULL || num_filled == NULL){
		printk("info_array or num_filled is NULL \n");
		return -EFAULT;
	}

	for (i; i < size; i++){
    //validating pointer passed by user
	    if (copy_from_user(&info, info_array[i], sizeof(long))){
			return -EFAULT;
	    }
	    else{
	    	info.pid = cur_task->pid;
			
			for(j = 0; j < ANCESTOR_NAME_LEN; j++){
				info.name[j] = cur_task->comm[j];
			}
			printk(info.name);
			info.state = cur_task->state;
			info.uid =  cur_task->cred->uid.val;


			//number of children
			list_for_each(list_head_child, &(cur_task->children)){
				num_child ++;
			}
			info.num_children = num_child;

			//number of sibling
			list_for_each(list_head_sib, &(cur_task->sibling)){
				num_sib ++;
			}
			info.num_siblings = num_sib - 1;


			info.nvcsw = cur_task->nvcsw;
			info.nivcsw = cur_task->nivcsw;

			if(cur_task->parent->pid == cur_task->pid){
				break;
			}
			cur_task = cur_task->parent;
			num_sib = 0;
			num_child = 0;
		}
	}
	return 0;
}
