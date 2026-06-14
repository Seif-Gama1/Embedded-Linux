#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/mutex.h>
#include <linux/io.h>

#include "inc/BCM2837_GPIO.h"

#define MY_PROC_NAME "rpi_gpio"

static char gpio_current_char = '0';

static struct proc_dir_entry *proc_entry;

DEFINE_MUTEX(my_mutex);

// ioremapping
static void __iomem *gpio_base;

#define GPFSEL2 (gpio_base + 0x08)
#define GPSET0 (gpio_base + 0x1C)
#define GPCLR0 (gpio_base + 0x28)

static ssize_t gpio_read(struct file *file, char __user *buf, size_t len, loff_t *ppos){
    if (*ppos != 0){
        return 0;
    }

    mutex_lock(&my_mutex);
    if (copy_to_user(buf, &gpio_current_char, 1)){
        mutex_unlock(&my_mutex);
        return -EFAULT;
    }

    *ppos += 1; // protect against infinite loop by 'cat'

    printk(KERN_INFO "Someone read: %c from gpio pin\n", gpio_current_char);
    mutex_unlock(&my_mutex);
    return 1; // we return only 1 byte
}

static ssize_t gpio_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos){
    mutex_lock(&my_mutex);
    // we only take first character and ignore the rest
    if (copy_from_user(&gpio_current_char, buf, 1)){
        mutex_unlock(&my_mutex);
        return -EFAULT;
    }
    // check that it is  0 or 1
    if (gpio_current_char != '0' && gpio_current_char != '1'){
        mutex_unlock(&my_mutex);
        return -EINVAL;
    }

    if (gpio_current_char == '0'){
        iowrite32(1 << 26, GPCLR0); // clear bit
    }else{
        iowrite32(1 << 26, GPSET0); // set bit
    }

    printk(KERN_INFO "wrote: %c\n", gpio_current_char);
    mutex_unlock(&my_mutex);
    return len; // return number of bytes taken by kernel (even if we only cared about first byte)
}

struct proc_ops rpi_gpio_proc_ops = {
    .proc_read = gpio_read,
    .proc_write = gpio_write
};

__init static int rpi_gpio_init(void){
    proc_entry = proc_create(MY_PROC_NAME, 0666, NULL, &rpi_gpio_proc_ops);

    // remapping
    gpio_base = ioremap(BCM2837_GPIO_BASE, BCM2837_GPIO_SIZE);
    if (!gpio_base){
        return -ENOMEM;
    }
    
    // setup the gpio pin to output
    uint32_t reg;
    reg = ioread32(GPFSEL2);
    reg &= ~(7 << 18); // clear bits
    reg |= (1 << 18);  // set GPIO 26 to output
    iowrite32(reg, GPFSEL2);

    printk(KERN_INFO "Hello from rpi_gpio_module\n");
    return 0;
}

__exit static void rpi_gpio_deinit(void){
    proc_remove(proc_entry);
    if (gpio_base){
        iounmap(gpio_base);
    }
    
    printk(KERN_INFO "Goodbye from rpi_gpio_module\n");
}

module_init(rpi_gpio_init);
module_exit(rpi_gpio_deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Seif Gamal");
MODULE_DESCRIPTION("Kernel module that allows you to read and write from /proc/rpi_gpio");