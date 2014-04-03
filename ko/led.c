
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/highmem.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("bzli");

unsigned long gpio_virt, gpmcon, gpmdat;

int led_ioctl(struct inode *no, struct file *fp, 
			unsigned long cmd, 
			unsigned long args)
{
#define LED_ON	555
#define LED_OFF  666

	int ret = 0;
	switch (cmd) {
		case LED_ON:
		iowrite32( ioread32(gpmcon) & ~0xffff, gpmcon);	
		iowrite32( ioread32(gpmcon) | 0x1111, gpmcon);
		iowrite32( ioread32(gpmdat) & ~0xf, gpmdat);
		break;

		case LED_OFF:
		iowrite32( ioread32(gpmcon) & ~0xffff, gpmcon);	
		iowrite32( ioread32(gpmcon) | 0x1111, gpmcon);
		iowrite32( ioread32(gpmdat) | 0xf, gpmdat);
		break;
	}

	return ret;
}	

int led_open(struct inode *no, struct file *fp)
{
	int ret = 0;
	return ret;
}

int led_release(struct inode *no, struct file *fp)
{
	int ret = 0;
	return ret;
}

struct file_operations ledops = {
	.open = led_open,
	.ioctl = led_ioctl,
	.release = led_release,
};

struct miscdevice led_misc = {
	.name = "led_misc",	
	.minor = 99,
	.fops = &ledops,	
};


int led_probe(struct platform_device *dev)
{
	int ret = 0;
		
	gpio_virt = ioremap(0x7f008000, SZ_4K);
	gpmcon = gpio_virt + 0x820;
	gpmdat = gpio_virt + 0x824;

	misc_register(&led_misc);
	return ret;
}

int led_remove(struct platform_device *dev)
{
	int ret = 0;
	misc_deregister(&led_misc);
	iounmap(gpio_virt);
	return ret;
}


void led_pdev_release(struct device *dev)
{
}

struct platform_device  led_pdev = {
	.name = "s3c6410_led",	
	.dev = {
		.release = led_pdev_release,
	},	
};

struct platform_driver  led_pdrv = {
	.probe = led_probe, 
	.remove = led_remove,
	.driver = {
		.name = "s3c6410_led",
	},
};

int led_init(void)
{
	int ret = 0;
	
	platform_device_register(&led_pdev);
	platform_driver_register(&led_pdrv);
	return ret;
}

void led_exit(void)
{
	platform_device_unregister(&led_pdev);
	platform_driver_unregister(&led_pdrv);
}

module_init(led_init);
module_exit(led_exit);


