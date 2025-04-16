#include <linux/module.h>
#include <linux/kallsyms.h>

static unsigned long *sys_call_table;
typedef long (*gettimeofday_type)(struct timeval *, struct timezone *);
gettimeofday_type orig_gettimeofday;

// 加速因子（2倍）
static int speed_factor = 2;

asmlinkage long hook_gettimeofday(struct timeval *tv, struct timezone *tz) {
    long ret = orig_gettimeofday(tv, tz);
    if (tv) {
        tv->tv_sec *= speed_factor;
        tv->tv_usec *= speed_factor;
        // 处理溢出
        if (tv->tv_usec >= 1000000) {
            tv->tv_sec += tv->tv_usec / 1000000;
            tv->tv_usec %= 1000000;
        }
    }
    return ret;
}

static int __init speed_init(void) {
    sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
    orig_gettimeofday = (gettimeofday_type)sys_call_table[__NR_gettimeofday];
    // 关闭写保护
    write_cr0(read_cr0() & (~0x10000));
    sys_call_table[__NR_gettimeofday] = (unsigned long)hook_gettimeofday;
    // 恢复写保护
    write_cr0(read_cr0() | 0x10000);
    printk("Speed hack module loaded\n");
    return 0;
}

static void __exit speed_exit(void) {
    write_cr0(read_cr0() & (~0x10000));
    sys_call_table[__NR_gettimeofday] = (unsigned long)orig_gettimeofday;
    write_cr0(read_cr0() | 0x10000);
    printk("Speed hack module unloaded\n");
}

module_init(speed_init);
module_exit(speed_exit);
MODULE_LICENSE("GPL");
