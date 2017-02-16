#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
//#include <linux/io.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_AUTHOR("Akira Tanabe");
MODULE_DESCRIPTION("driver for Blink LED");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

#define LED1 26

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
//static volatile u32 *gpio_base = NULL;



static struct timer_list blink_timer;

static void blink_timer_func(unsigned long data)
{
//printk(KERN_INFO "%s\n", __func__);

	gpio_set_value(LED1, data);
	blink_timer.data = !data;
	blink_timer.expires = jiffies + (HZ/4);
	add_timer(&blink_timer);
}

//static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
//{
//	char c;
//	if(copy_from_user(&c,buf,sizeof(char)))
//	return -EFAULT;	
	
//	if(c == '0'){
//		gpio_base[10] = 1 << 4;
//	}

//	else if(c == '1'){
//		gpio_base[7] = 1 << 4;
//	}
//
//
//	//printk(KERN_INFO "receive %c\n",c);
//       return 1;
//}


//-------------------------------------------------------

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
	int size = 0;
	char sushi[] = {0xF0,0x9F,0x8D,0xA3,0x0A};
	if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
		printk( KERN_INFO "sushi : copy_to_user failed\n" );
		return -EFAULT;
	}
	size += sizeof(sushi);

	return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
//	.write = led_write,
	.read = sushi_read
};

//-------------------------------------------------------


static int __init init_mod(void)
{
	int retval;
	int ret = 0;
//	gpio_base = ioremap_nocache(0x3F200000,0xA0);
	
//	const u32 led = 4;
//	const u32 index = led/10;//GPFSEL2
//	const u32 shift = (led%10)*3;//15bit
//	const u32 mask = ~(0x7 << shift);
//	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);

        printk(KERN_INFO "%s\n", __func__);
        ret = gpio_request_one(LED1, GPIOF_OUT_INIT_LOW, "led1");

        if (ret) {
                printk(KERN_ERR "Unable to request GPIOs: %d\n", ret);
                return ret;
        }

        blink_timer.function = blink_timer_func;
        blink_timer.data = 1L;
        blink_timer.expires = jiffies + (HZ/4);
        add_timer(&blink_timer);



	retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}		
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));	
	return 0;

}

static void __exit cleanup_mod(void)
{

	del_timer_sync(&blink_timer);
	gpio_set_value(LED1, 0);
	gpio_free(LED1);

	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);

	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));

}

module_init(init_mod);
module_exit(cleanup_mod);

