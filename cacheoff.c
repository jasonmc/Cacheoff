#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
        printk(KERN_ALERT "Disabling L1 cache\n");
        __asm__("push   %rax\n\t"
                "mov    %cr0,%rax;\n\t"
                "or     $(1 << 30),%rax;\n\t"
                "mov    %rax,%cr0;\n\t"
                "wbinvd\n\t"
                "pop    %rax"
);
        return 0;
}
static void hello_exit(void)
{
        printk(KERN_ALERT "Leaving cacheoff module - should enable L1 cache\n");
        __asm__("push   %rax\n\t"
                "mov    %cr0,%rax;\n\t"
                "and     $~(1 << 30),%rax;\n\t"
                "mov    %rax,%cr0;\n\t"
                "wbinvd\n\t"
                "pop    %rax"
);
}
module_init(hello_init);
module_exit(hello_exit);
