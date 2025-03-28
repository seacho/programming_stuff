#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/kext/OSKextLib.h>

void printKexts(CFDictionaryRef dict) {

    CFDataRef xml = CFPropertyListCreateXMLData(kCFAllocatorDefault, (CFPropertyListRef)dict);

    printf("%s", CFDataGetBytePtr(xml));

    CFRelease(xml);
}

int main() {
    CFDictionaryRef kextDict = OSKextCopyLoadedKextInfo(NULL, NULL);

    printKexts(kextDict);

}


