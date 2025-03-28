//gcc 1.c -framework IOKit -framework CoreFoundation
#include <stdio.h>
#include <stdlib.h>
#include <IOKit/IOKitLib.h>
#include <mach/mach.h>

int main(int argc, const char *argv[]) {
    kern_return_t kr;
    io_service_t service;
    io_connect_t connect = IO_OBJECT_NULL;
    
    // 1. 创建匹配字典（这里的字符串需要与 kext 中注册的名字一致）
    CFMutableDictionaryRef matchingDict = IOServiceMatching("io_oooverflow_IPwnKit");
    if (!matchingDict) {
        fprintf(stderr, "无法创建匹配字典\n");
        return -1;
    }
    
    // 2. 查找服务
    service = IOServiceGetMatchingService(kIOMasterPortDefault, matchingDict);
    if (service == IO_OBJECT_NULL) {
        fprintf(stderr, "未找到目标服务\n");
        return -1;
    }
    
    // 3. 打开服务连接
    kr = IOServiceOpen(service, mach_task_self(), 0, &connect);
    if (kr != KERN_SUCCESS) {
        fprintf(stderr, "IOServiceOpen 失败: 0x%x: %s\n", kr, mach_error_string(kr));
        IOObjectRelease(service);
        return -1;
    }
    
    // 4. 调用外部方法
    //    此处假设驱动在外部方法数组中注册了方法索引 0，
    //    用户程序向该方法传递一个 scalar 参数，并期望返回一个 scalar 值。
    uint64_t inputScalar[1024] = { 0 }; // 示例输入参数
    uint32_t inputCount = 1;
    uint64_t outputScalar[1024] = { 0 };
    uint32_t outputCount = 1024*8;
    kr = IOConnectCallScalarMethod(connect, 0,      // 方法索引（需与驱动端约定）
                                   inputScalar, &inputCount,       // 输入参数及数量
                                   outputScalar, &outputCount); // 输出参数及数量
    if (kr != KERN_SUCCESS) {
        fprintf(stderr, "调用外部方法失败: 0x%x: %s\n", kr, mach_error_string(kr));
    } else {
        printf("接收到的返回值: %llu\n", outputScalar[0]);
    }
    
    // 5. 清理资源
    IOServiceClose(connect);
    IOObjectRelease(service);
    
    return 0;
}


