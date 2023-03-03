#include "hello.h"

MODULE_LICENSE("IDK");
MODULE_DESCRIPTION("My firt kernel module");
MODULE_AUTHOR("You");

module_init(my_init);
module_exit(my_exit);

static int n = 0;
static int _isopen = 0;
//static charp *str = NULL;                                                                                                                                
module_param(n, int , S_IRUSR | S_IWUSR);
//module_param(str, charp, IS_IRUSR | S_IWUSR);                                                                                                            

static int my_dev_open(struct inode *inode, struct file *file);
static int my_dev_close(struct inode *inode, struct file *file);
static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off);
static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off);

static struct file_operations fops = {
  .read = my_dev_read,
  .write = my_dev_write,
  .open = my_dev_open,
  .release = my_dev_close
};

static int my_dev_open(struct inode *inode, struct file *file)
{
  if (_isopen == 0) {
    printk("Device is open\n");
    _isopen = 1;
  }
  if (_isopen != 0)
    printk("Device already open\n");
  return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
  if (_isopen == 1) {
    printk("Device is not close\n");
    _isopen = 0;
  }
  if (_isopen != 1)
    printk("Device is close\n");
  return 0;
}

static ssize_t my_dev_read(struct file *file, char *buf, size_t len, loff_t *off)
{

  return 0;
}

static ssize_t my_dev_write(struct file *file, const char *buf, size_t len, loff_t *off)
{

  return 0;
}

static int __init my_init()
{
  int i = 0;
  int value = register_chrdev(0, "hugo", &fops);
  printk("%d\n", value);
  for (i = 0; i < n; i++)
    printk("Hello kernel!\n");

  return 0;
}

static void __exit my_exit(void)
{
  int i = 0;

  for (i = 0; i < n; i++)
    printk("Goobye kernel!\n");
  return;
}
