#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("ANY LICENCE HERE");
MODULE_AUTHOR("Davydov Alexey");
MODULE_DESCRIPTION("Random text for test there");

static int __init hello_init(void)
{
    printk(KERN_INFO "It is my first task in module 5!\n");
    return 0;
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "See you in the next task.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
