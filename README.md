# WSL
Used WSL and Alma Linux 10
```powershell
wsl --install AlmaLinux-10
```

.wslconfig
```ini
[wsl2]
processors=6      # 2x2 for MicroVMs, 2 for system
```

```powershell
wsl -d AlmaLinux-10
```
```bash
# Verify 6 CPUs
$ lscpu
Architecture:             x86_64
  CPU op-mode(s):         32-bit, 64-bit
  Address sizes:          46 bits physical, 48 bits virtual
  Byte Order:             Little Endian
CPU(s):                   6
  On-line CPU(s) list:    0-5

# Verify kvm
$ ls /dev/kvm
/dev/kvm
```