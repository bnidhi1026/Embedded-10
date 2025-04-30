/*
 * hello-sysfs.c sysfs example
 */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/delay.h>


static struct task_struct *etx_thread;


static struct kobject *mymodule;

/* the variable you want to be able to change */
static int myvariable = 0;

static ssize_t myvariable_show(struct kobject *kobj,
                               struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", myvariable);
}

static ssize_t myvariable_store(struct kobject *kobj,
                                struct kobj_attribute *attr, char *buf,
                                size_t count)
{
    sscanf(buf, "%du", &myvariable);
    return count;
}


static struct kobj_attribute myvariable_attribute =
        __ATTR(myvariable, 0660, myvariable_show, (void *)myvariable_store);


int thread_function(void *pv)
{
    int i=0;
    while(!kthread_should_stop()) {
        char buf[100];
        myvariable_show(mymodule, &myvariable_attribute, buf);
        pr_info("%s\n", buf);
        msleep(1000);
    }
    return 0;
}



static int __init mymodule_init(void)
{
    int error = 0;

    pr_info("mymodule: initialised\n");

    mymodule = kobject_create_and_add("mymodule", kernel_kobj);
    if (!mymodule)
        return -ENOMEM;

    error = sysfs_create_file(mymodule, &myvariable_attribute.attr);
    if (error) {
        pr_info("failed to create the myvariable file "
                "in /sys/kernel/mymodule\n");
    }

    etx_thread = kthread_create(thread_function, NULL, "eTx Thread");
    if (etx_thread) {
        wake_up_process(etx_thread);
    } else {
        pr_err("Cannot create kthread\n");
    }

    return error;
}

static void __exit mymodule_exit(void)
{
    kthread_stop(etx_thread);
    pr_info("mymodule: Exit success\n");
    kobject_put(mymodule);
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");