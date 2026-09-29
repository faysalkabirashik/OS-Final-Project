#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gcd.h>

// These are good practice 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Md Foysal Kabir Ashik");
MODULE_DESCRIPTION("A simple kernel module for OS project that prints values.");
MODULE_VERSION("0.1");



int simple_init(void) {
    printk(KERN_INFO "Loading Kernel Module\n");
    printk(KERN_INFO "Golden Ratio Prime: %lu\n", GOLDEN_RATIO_PRIME);
    return 0;
}

void simple_exit(void) {
    unsigned long result = gcd(3700, 24);
    printk(KERN_INFO "Removing Kernel Module\n");
    printk(KERN_INFO "GCD of 3700 and 24: %lu\n", result);
}

module_init(simple_init);
module_exit(simple_exit);
