#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/semaphore.h>
#include<asm/uaccess.h>
#include<linux/sched.h>
struct fake_device{
	
char data[100];
struct semaphore sem;

}virtual_device;

struct cdev *mcdev;
int major_number;
int ret;

dev_t dev_num;

#define DEVICE_NAME "char_device"

int device_open(struct inode *inode, struct file *filep){

if(down_interruptible(&virtual_device.sem) !=0){
printk(KERN_ALERT "char_device: could not lock device during open");
return -1;
}

printk(KERN_INFO "char_device: opened device");
return 0;
}

ssize_t device_read(struct file* filp, char* bufStoreData, size_t bufCount,  loff_t* curOffset){
printk(KERN_INFO "char_device: reading from device");

struct task_struct *task;

for_each_process(task)
{
   if(task->c.tv_nsec != 0)
   printk("Name: %s PID: [%d]\n", task->comm, task->pid);
}

ret = copy_from_user(bufStoreData, virtual_device.data, bufCount);
return ret;
}

ssize_t device_write(struct file* filp, const char* bufSourceData, size_t bufCount,  loff_t* curOffset){
printk(KERN_INFO "char_device: writing to device");
ret = copy_from_user(virtual_device.data, bufSourceData, bufCount);
return ret;
}

int device_close (struct inode *inode, struct file *filep){
up(&virtual_device.sem);
printk(KERN_INFO "char_device: closed device");
return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_close,	
	.read = device_read,
	.write = device_write

};


static int driver_entry(void){

ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
if(ret < 0)
{
printk(KERN_ALERT "Failed to allocate a major number for char_device");
return ret;
}
major_number = MAJOR(dev_num);
printk(KERN_INFO "char_device: major number is %d", major_number);
printk(KERN_INFO "\tuse \mknod /dev/%s c %d 0\" for device file", DEVICE_NAME, major_number);

mcdev = cdev_alloc();
mcdev->ops = &fops;
mcdev->owner = THIS_MODULE;

ret = cdev_add(mcdev, dev_num, 1);

if(ret < 0)
{
printk(KERN_ALERT "Char_device : unable to add cdev to kernel");
return ret;
}

sema_init(&virtual_device.sem,1); 

return 0;
}

static void driver_exit(void){

cdev_del(mcdev);

unregister_chrdev_region(dev_num, 1);
printk(KERN_ALERT "char_device: unloaded module");
}

module_init(driver_entry);
module_exit(driver_exit);

 
