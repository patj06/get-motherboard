# Get Motherboard Info

A lightweight C++ utility for retrieving motherboard vendor information without relying on SMBIOS. This tool uses the Windows ACPI (Advanced Configuration and Power Interface) firmware tables to extract OEM manufacturer details.

## Overview

Traditional motherboard identification tools often rely on SMBIOS (System Management BIOS) data, which can sometimes be unreliable or unavailable. This utility takes an alternative approach by directly querying ACPI firmware tables to obtain motherboard vendor information.

## How It Works

The program uses the Windows API function `GetSystemFirmwareTable()` to retrieve ACPI tables including:

- **XSDT** (Extended System Description Table) - Main ACPI table in 64-bit systems
- **RSDT** (Root System Description Table) - Main ACPI table in 32-bit systems  
- **FACP** (Fixed ACPI Description Table) - Core ACPI configuration
- **APIC** (Advanced Programmable Interrupt Controller) - Interrupt controller info
- **SSDT** (Secondary System Description Table) - Additional system info
- **MSDM** (Microsoft Data Management) - Windows licensing info

Each ACPI table contains OEM identification fields that reveal the motherboard manufacturer and model information.

## Features

- **SMBIOS-independent** - Works even when SMBIOS is unavailable
- **Lightweight** - Minimal dependencies, just Windows API
- **Multiple sources** - Queries several ACPI tables for comprehensive info
- **Fast execution** - Direct firmware table access
- **C++14 compatible** - Modern C++ standards

## Building

### Requirements
- Windows SDK
- C++14 compatible compiler (Visual Studio 2015 or later)

### Compilation
```bash
# Using Visual Studio Developer Command Prompt
cl get-motherboard.cpp

# Or open the .vcxproj file in Visual Studio and build
```

## Usage

Simply run the executable:

```bash
get-motherboard.exe
```

### Sample Output
```
XSDT OEMID='ALASKA' OEMTableID='A M I '
FACP OEMID='ALASKA' OEMTableID='A M I '
APIC OEMID='ALASKA' OEMTableID='A M I '
SSDT OEMID='PmaxDv' OEMTableID='Pmax_Dev'
```

## Understanding the Output

- **OEMID**: Manufacturer identifier (usually 6 characters)
- **OEMTableID**: Specific table/board identifier (usually 8 characters)

Common OEMIDs include:
- `MSFT` - Microsoft (Surface devices, VMs)
- `ASUS` - ASUS motherboards
- `DELL` - Dell systems
- `HP` - HP/Compaq systems
- `LENOVO` - Lenovo systems

## Why Not SMBIOS?

While SMBIOS is the standard method for hardware identification, it has limitations:
- May not be available in virtual machines
- Can be modified or spoofed
- Sometimes returns generic/incomplete information
- Requires special permissions in some environments

ACPI tables provide an alternative data source that's:
- Always present in modern systems
- Harder to modify
- Contains authentic OEM information
- Accessible through standard Windows API

## Technical Details

The program defines the standard ACPI table header structure and uses little-endian signature matching to identify specific tables. It safely allocates memory for each table and extracts the OEM fields using proper bounds checking.

## License

This project is provided as-is for educational and utility purposes.

## Contributing

Feel free to submit issues or pull requests to improve the utility or add support for additional ACPI tables
