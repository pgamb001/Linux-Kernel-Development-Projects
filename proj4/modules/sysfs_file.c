#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h> 

static struct kobject *ee255_obj;

char *partition_policy[2];
static ssize_t part_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{        

return sprintf(buf,"%c\n", partition_policy);
}

static ssize_t part_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

sscanf(buf, "%c", partition_policy);
//sscanf(buf[1], "%c", partition_policy[1]);
if(buf == "WF")
{
partition_policy[0] = "W";
partition_policy[1] = "F";
}
if(buf[0] == "F" && buf[1] == "F")
{
partition_policy[0] = "F";
partition_policy[1] = "F";
}
if(buf[0] == "B" && buf[1] =="F")
{
partition_policy[0] = "B";
partition_policy[1] = "F";
}
return count;
}


static struct kobj_attribute part_attribute =__ATTR(partition_policy, 0660,part_show, part_store);

static int __init mymodule_init (void)
{

        pr_debug("Module initialized successfully \n");

        kobject_init(ee255_obj, NULL);
	kobject_add(ee255_obj, NULL, "ee255");
	//kobject_init(part_policy, kernel_obj);
	//kobject_add(part_policy, ee255, "partition_policy");
        
 sysfs_create_file(ee255_obj, &part_attribute.attr);
return 0;
}

static void __exit mymodule_exit (void)
{
        pr_debug ("Module un initialized successfully \n");
        kobject_put(ee255_obj);
}

module_init(mymodule_init);
module_exit(mymodule_exit);
