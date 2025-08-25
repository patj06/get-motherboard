#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    char     Signature[4];  
    uint32_t Length;
    uint8_t  Revision;
    uint8_t  Checksum;
    char     OEMID[6];       
    char     OEMTableID[8];  
    uint32_t OEMRevision;
    char     ASLCompilerID[4];
    uint32_t ASLCompilerRevision;
} ACPI_HEADER;
#pragma pack(pop)

static void print_oem_from_acpi(const char sig[4]) {
    DWORD id = *(const DWORD*)sig; // little-endian
    DWORD needed = GetSystemFirmwareTable('ACPI', id, NULL, 0);
    if (!needed) return;
    BYTE* buf = (BYTE*)malloc(needed);
    if (!buf) return;
    if (GetSystemFirmwareTable('ACPI', id, buf, needed) == needed) {
        ACPI_HEADER* hdr = (ACPI_HEADER*)buf;
        char oemid[7] = { 0 }, oemtab[9] = { 0 };
        memcpy(oemid, hdr->OEMID, 6);
        memcpy(oemtab, hdr->OEMTableID, 8);
        printf("%4.4s OEMID='%s' OEMTableID='%s'\n", sig, oemid, oemtab);
    }
    free(buf);
}

int main(void) {
    print_oem_from_acpi("XSDT");
    print_oem_from_acpi("RSDT");
    print_oem_from_acpi("FACP"); 
    print_oem_from_acpi("APIC");
    print_oem_from_acpi("SSDT");
    print_oem_from_acpi("MSDM"); 
    return 0;
}
