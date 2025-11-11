# WSL
```powershell
wsl --install Ubuntu
```

.wslconfig
```ini
[wsl2]
processors=5      # 2x2 for MicroVMs, 1 for system
```

```powershell
wsl -d Ubuntu
```
```bash
$ lscpu
Architecture:             x86_64
  CPU op-mode(s):         32-bit, 64-bit
  Address sizes:          46 bits physical, 48 bits virtual
  Byte Order:             Little Endian
CPU(s):                   5
  On-line CPU(s) list:    0-4
```

# Firecracker

## Setup
```bash
curl -LOJ https://github.com/firecracker-microvm/firecracker/releases/download/v1.13.1/firecracker-v1.13.1-x86_64.tgz
tar -xvzf firecracker-v1.13.1-x86_64.tgz
chmod +x release-v1.13.1-x86_64/firecracker-v1.13.1-x86_64
sudo mv release-v1.13.1-x86_64/firecracker-v1.13.1-x86_64 /usr/local/bin/firecracker

wget https://s3.amazonaws.com/spec.ccfc.min/img/hello/kernel/hello-vmlinux.bin
wget https://s3.amazonaws.com/spec.ccfc.min/img/hello/fsfiles/hello-rootfs.ext4 
```
TODO: Firecracker setup

## Start Firecracker
```bash
sudo firecracker --no-api --config-file vmconfig.json
```

# Initial Test
## Isolated
```bash
$ ./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.082 s
Thread 1 reached 1000000000 iterations, elapsed: 1.102 s
Thread 0 reached 2000000000 iterations, elapsed: 2.056 s
Thread 1 reached 2000000000 iterations, elapsed: 2.078 s
Thread 0 reached 3000000000 iterations, elapsed: 3.043 s
Thread 1 reached 3000000000 iterations, elapsed: 3.073 s
Thread 0 reached 4000000000 iterations, elapsed: 4.031 s
Thread 1 reached 4000000000 iterations, elapsed: 4.052 s
Thread 0 reached 5000000000 iterations, elapsed: 5.017 s
Thread 1 reached 5000000000 iterations, elapsed: 5.028 s
Thread 0 reached 6000000000 iterations, elapsed: 5.996 s
Thread 1 reached 6000000000 iterations, elapsed: 6.012 s
Thread 0 reached 7000000000 iterations, elapsed: 6.966 s
Thread 1 reached 7000000000 iterations, elapsed: 6.977 s
Thread 0 reached 8000000000 iterations, elapsed: 7.932 s
Thread 1 reached 8000000000 iterations, elapsed: 7.950 s
Thread 0 reached 9000000000 iterations, elapsed: 8.911 s
Thread 1 reached 9000000000 iterations, elapsed: 8.936 s
Thread 0 reached 10000000000 iterations, elapsed: 9.880 s
Thread 0 finished 10000000000 iterations in 9.881 s
Thread 1 reached 10000000000 iterations, elapsed: 9.899 s
Thread 1 finished 10000000000 iterations in 9.900 s
All threads finished.
```

## Multi-Tenent

### Tenent 1
```bash
$ ./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.270 s
Thread 1 reached 1000000000 iterations, elapsed: 1.381 s
Thread 0 reached 2000000000 iterations, elapsed: 2.413 s
Thread 1 reached 2000000000 iterations, elapsed: 2.734 s
Thread 0 reached 3000000000 iterations, elapsed: 3.746 s
Thread 1 reached 3000000000 iterations, elapsed: 3.879 s
Thread 0 reached 4000000000 iterations, elapsed: 4.952 s
Thread 1 reached 4000000000 iterations, elapsed: 5.066 s
Thread 0 reached 5000000000 iterations, elapsed: 6.201 s
Thread 1 reached 5000000000 iterations, elapsed: 6.351 s
Thread 0 reached 6000000000 iterations, elapsed: 7.437 s
Thread 1 reached 6000000000 iterations, elapsed: 7.684 s
Thread 0 reached 7000000000 iterations, elapsed: 8.633 s
Thread 1 reached 7000000000 iterations, elapsed: 8.860 s
Thread 0 reached 8000000000 iterations, elapsed: 9.983 s
Thread 1 reached 8000000000 iterations, elapsed: 10.202 s
Thread 1 reached 9000000000 iterations, elapsed: 11.316 s
Thread 0 reached 9000000000 iterations, elapsed: 11.364 s
Thread 0 reached 10000000000 iterations, elapsed: 12.560 s
Thread 0 finished 10000000000 iterations in 12.561 s
Thread 1 reached 10000000000 iterations, elapsed: 12.689 s
Thread 1 finished 10000000000 iterations in 12.690 s
All threads finished.
```

### Tenent 2
```bash
./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.253 s
Thread 1 reached 1000000000 iterations, elapsed: 1.288 s
Thread 0 reached 2000000000 iterations, elapsed: 2.496 s
Thread 1 reached 2000000000 iterations, elapsed: 2.562 s
Thread 1 reached 3000000000 iterations, elapsed: 3.967 s
Thread 0 reached 3000000000 iterations, elapsed: 3.996 s
Thread 1 reached 4000000000 iterations, elapsed: 5.165 s
Thread 0 reached 4000000000 iterations, elapsed: 5.282 s
Thread 1 reached 5000000000 iterations, elapsed: 6.362 s
Thread 0 reached 5000000000 iterations, elapsed: 6.572 s
Thread 1 reached 6000000000 iterations, elapsed: 7.489 s
Thread 0 reached 6000000000 iterations, elapsed: 7.890 s
Thread 1 reached 7000000000 iterations, elapsed: 8.755 s
Thread 0 reached 7000000000 iterations, elapsed: 9.125 s
Thread 1 reached 8000000000 iterations, elapsed: 9.977 s
Thread 0 reached 8000000000 iterations, elapsed: 10.329 s
Thread 1 reached 9000000000 iterations, elapsed: 11.467 s
Thread 0 reached 9000000000 iterations, elapsed: 11.526 s
Thread 1 reached 10000000000 iterations, elapsed: 12.551 s
Thread 1 finished 10000000000 iterations in 12.552 s
Thread 0 reached 10000000000 iterations, elapsed: 12.650 s
Thread 0 finished 10000000000 iterations in 12.652 s
All threads finished.
```

# Numactl

## Isloated
```bash
sudo numactl --physcpubind=0-1 --membind=0 firecracker --no-api --config-file vmconfig.json
```

```bash
$ ./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.008 s
Thread 0 reached 1000000000 iterations, elapsed: 1.017 s
Thread 1 reached 2000000000 iterations, elapsed: 2.022 s
Thread 0 reached 2000000000 iterations, elapsed: 2.022 s
Thread 1 reached 3000000000 iterations, elapsed: 3.000 s
Thread 0 reached 3000000000 iterations, elapsed: 3.010 s
Thread 1 reached 4000000000 iterations, elapsed: 3.989 s
Thread 0 reached 4000000000 iterations, elapsed: 3.998 s
Thread 1 reached 5000000000 iterations, elapsed: 4.963 s
Thread 0 reached 5000000000 iterations, elapsed: 4.970 s
Thread 1 reached 6000000000 iterations, elapsed: 5.969 s
Thread 0 reached 6000000000 iterations, elapsed: 5.982 s
Thread 1 reached 7000000000 iterations, elapsed: 6.965 s
Thread 0 reached 7000000000 iterations, elapsed: 6.975 s
Thread 0 reached 8000000000 iterations, elapsed: 7.939 s
Thread 1 reached 8000000000 iterations, elapsed: 7.951 s
Thread 0 reached 9000000000 iterations, elapsed: 8.916 s
Thread 1 reached 9000000000 iterations, elapsed: 8.939 s
Thread 0 reached 10000000000 iterations, elapsed: 9.920 s
Thread 0 finished 10000000000 iterations in 9.922 s
Thread 1 reached 10000000000 iterations, elapsed: 9.952 s
Thread 1 finished 10000000000 iterations in 9.953 s
All threads finished.
```

```bash
$ mpstat -P ALL 1
Linux 6.6.87.2-microsoft-standard-WSL2 (GUARD-LAPTOP)   11/08/25        _x86_64_        (5 CPU)

14:36:45     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:54     all    0.20    0.00    0.20    0.20    0.00    0.00    0.00    0.00    0.00   99.40
14:36:54       0    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
14:36:54       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:54       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:54       3    1.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
14:36:54       4    0.00    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00   99.00

14:36:54     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:47     all    0.20    0.00    1.40    0.80    0.00    0.40    0.00    5.60    0.00   91.60
14:36:47       0    0.00    0.00    0.99    1.98    0.00    0.99    0.00   13.86    0.00   82.18
14:36:47       1    0.00    0.00    0.00    1.01    0.00    0.00    0.00   14.14    0.00   84.85
14:36:47       2    0.99    0.00    3.96    0.00    0.00    0.99    0.00    0.00    0.00   94.06
14:36:47       3    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
14:36:47       4    0.00    0.00    1.01    1.01    0.00    0.00    0.00    0.00    0.00   97.98

14:36:47     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:48     all    0.20    0.00    0.20    0.00    0.00    0.20    0.00   39.64    0.00   59.76
14:36:48       0    0.99    0.00    0.99    0.00    0.00    0.00    0.00   98.02    0.00    0.00
14:36:48       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:36:48       2    0.00    0.00    0.00    0.00    0.00    0.99    0.00    0.00    0.00   99.01
14:36:48       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:48       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:48     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:49     all    0.00    0.00    0.20    0.00    0.00    0.40    0.00   39.88    0.00   59.52
14:36:49       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:36:49       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:36:49       2    0.00    0.00    0.00    0.00    0.00    1.98    0.00    0.00    0.00   98.02
14:36:49       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:49       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:49     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:50     all    0.39    0.00    0.59    0.00    0.00    0.39    0.00   39.76    0.00   58.66
14:36:50       0    0.00    0.00    0.98    0.00    0.00    0.00    0.00   99.02    0.00    0.00
14:36:50       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:36:50       2    0.97    0.00    0.00    0.00    0.00    1.94    0.00    0.00    0.00   97.09
14:36:50       3    0.99    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   98.02
14:36:50       4    0.99    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   98.02

14:36:50     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:51     all    0.00    0.00    0.59    0.00    0.00    0.59    0.00   39.37    0.00   59.45
14:36:51       0    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:36:51       1    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
14:36:51       2    0.00    0.00    0.95    0.00    0.00    2.86    0.00    0.95    0.00   95.24
14:36:51       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:51       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:51     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:51     all    0.40    0.00    2.38    1.19    0.00    0.20    0.00   39.41    0.00   56.44
14:36:51       0    0.99    0.00    1.98    0.00    0.00    0.00    0.00   97.03    0.00    0.00
14:36:51       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:36:51       2    0.00    0.00    2.00    2.00    0.00    1.00    0.00    0.00    0.00   95.00
14:36:51       3    0.00    0.00    3.92    2.94    0.00    0.00    0.00    0.98    0.00   92.16
14:36:51       4    0.99    0.00    2.97    0.99    0.00    0.00    0.00    0.00    0.00   95.05

14:36:51     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:52     all    0.00    0.00    0.20    0.00    0.00    0.20    0.00   39.84    0.00   59.76
14:36:52       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:36:52       1    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
14:36:52       2    0.00    0.00    0.00    0.00    0.00    0.99    0.00    0.00    0.00   99.01
14:36:52       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:52       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:52     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:53     all    0.79    0.00    1.58    0.00    0.00    0.39    0.00   39.05    0.00   58.19
14:36:53       0    0.99    0.00    1.98    0.00    0.00    0.00    0.00   97.03    0.00    0.00
14:36:53       1    0.00    0.00    1.96    0.00    0.00    0.00    0.00   98.04    0.00    0.00
14:36:53       2    0.98    0.00    1.96    0.00    0.00    0.98    0.00    0.00    0.00   96.08
14:36:53       3    1.94    0.00    1.94    0.00    0.00    0.97    0.00    0.00    0.00   95.15
14:36:53       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:53     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:54     all    0.00    0.00    0.20    0.00    0.00    0.00    0.00   39.84    0.00   59.76
14:36:54       0    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:36:54       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:36:54       2    0.99    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.01
14:36:54       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:54       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:54     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:55     all    0.40    0.00    0.80    0.00    0.00    0.00    0.00   39.88    0.00   58.92
14:36:55       0    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:36:55       1    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
14:36:55       2    0.00    0.00    1.01    0.00    0.00    0.00    0.00    0.00    0.00   98.99
14:36:55       3    2.02    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   97.98
14:36:55       4    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00

14:36:55     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:56     all    0.20    0.00    0.40    0.00    0.00    0.20    0.00   39.76    0.00   59.44
14:36:56       0    1.00    0.00    1.00    0.00    0.00    0.00    0.00   98.00    0.00    0.00
14:36:56       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:36:56       2    0.00    0.00    1.00    0.00    0.00    1.00    0.00    0.00    0.00   98.00
14:36:56       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:36:56       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:36:56     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:36:57     all    0.59    0.00    1.77    0.59    0.00    0.39    0.00   28.94    0.00   67.72
14:36:57       0    0.00    0.00    1.00    0.00    0.00    0.00    0.00   75.00    0.00   24.00
14:36:57       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00   71.29    0.00   27.72
14:36:57       2    0.96    0.00    2.88    1.92    0.00    1.92    0.00    0.00    0.00   92.31
14:36:57       3    1.94    0.00    1.94    0.97    0.00    0.00    0.00    0.00    0.00   95.15
14:36:57       4    0.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   98.00
```

## Multi-Tenent
### Tenant 1
```bash
sudo numactl --physcpubind=0-1 --membind=0 firecracker --no-api --config-file vmconfig.json
```

### Tenant 2
```bash
sudo numactl --physcpubind=2-3 --membind=0 firecracker --no-api --config-file vmconfig.json
```

Verify
```bash
$ ps -eLo pid,tid,psr,comm | grep firecracker
  36788   36788   0 firecracker
  37233   37233   3 firecracker
```

### Tenent 1
```bash
$ ./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.160 s
Thread 0 reached 1000000000 iterations, elapsed: 1.178 s
Thread 0 reached 2000000000 iterations, elapsed: 2.428 s
Thread 1 reached 2000000000 iterations, elapsed: 2.502 s
Thread 0 reached 3000000000 iterations, elapsed: 3.754 s
Thread 1 reached 3000000000 iterations, elapsed: 3.765 s
Thread 0 reached 4000000000 iterations, elapsed: 5.038 s
Thread 1 reached 4000000000 iterations, elapsed: 5.074 s
Thread 0 reached 5000000000 iterations, elapsed: 6.259 s
Thread 1 reached 5000000000 iterations, elapsed: 6.339 s
Thread 0 reached 6000000000 iterations, elapsed: 7.487 s
Thread 1 reached 6000000000 iterations, elapsed: 7.740 s
Thread 0 reached 7000000000 iterations, elapsed: 8.793 s
Thread 1 reached 7000000000 iterations, elapsed: 9.010 s
Thread 0 reached 8000000000 iterations, elapsed: 10.145 s
Thread 1 reached 8000000000 iterations, elapsed: 10.242 s
Thread 0 reached 9000000000 iterations, elapsed: 11.396 s
Thread 1 reached 9000000000 iterations, elapsed: 11.591 s
Thread 0 reached 10000000000 iterations, elapsed: 12.678 s
Thread 0 finished 10000000000 iterations in 12.679 s
Thread 1 reached 10000000000 iterations, elapsed: 12.865 s
Thread 1 finished 10000000000 iterations in 12.866 s
All threads finished.
```

### Tenent 2
```bash
./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.337 s
Thread 0 reached 1000000000 iterations, elapsed: 1.450 s
Thread 1 reached 2000000000 iterations, elapsed: 2.621 s
Thread 0 reached 2000000000 iterations, elapsed: 2.659 s
Thread 1 reached 3000000000 iterations, elapsed: 3.743 s
Thread 0 reached 3000000000 iterations, elapsed: 3.950 s
Thread 1 reached 4000000000 iterations, elapsed: 5.069 s
Thread 0 reached 4000000000 iterations, elapsed: 5.228 s
Thread 1 reached 5000000000 iterations, elapsed: 6.326 s
Thread 0 reached 5000000000 iterations, elapsed: 6.582 s
Thread 1 reached 6000000000 iterations, elapsed: 7.529 s
Thread 0 reached 6000000000 iterations, elapsed: 7.826 s
Thread 1 reached 7000000000 iterations, elapsed: 8.742 s
Thread 0 reached 7000000000 iterations, elapsed: 9.130 s
Thread 1 reached 8000000000 iterations, elapsed: 9.929 s
Thread 0 reached 8000000000 iterations, elapsed: 10.385 s
Thread 1 reached 9000000000 iterations, elapsed: 11.174 s
Thread 0 reached 9000000000 iterations, elapsed: 11.632 s
Thread 1 reached 10000000000 iterations, elapsed: 12.404 s
Thread 1 finished 10000000000 iterations in 12.405 s
Thread 0 reached 10000000000 iterations, elapsed: 12.788 s
Thread 0 finished 10000000000 iterations in 12.789 s
All threads finished.
```

```bash
$ mpstat -P ALL 1
Linux 6.6.87.2-microsoft-standard-WSL2 (GUARD-LAPTOP)   11/08/25        _x86_64_        (5 CPU)

14:48:14     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:15     all    0.20    0.00    0.00    0.00    0.00    0.00    0.00    5.02    0.00   94.78
14:48:15       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00   13.00    0.00   87.00
14:48:15       1    1.01    0.00    0.00    0.00    0.00    0.00    0.00   12.12    0.00   86.87
14:48:15       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:48:15       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:48:15       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:48:15     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:16     all    0.00    0.00    0.60    0.00    0.00    0.00    0.00   65.80    0.00   33.40
14:48:16       0    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
14:48:16       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:16       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00   65.00    0.00   35.00
14:48:16       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00   65.00    0.00   35.00
14:48:16       4    1.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00

14:48:16     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:17     all    0.00    0.00    0.20    0.00    0.00    0.00    0.00   79.92    0.00   19.68
14:48:17       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:17       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:17       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:17       3    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:17       4    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00

14:48:17     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:18     all    0.40    0.00    0.60    0.40    0.00    0.00    0.00   79.80    0.00   18.80
14:48:18       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:18       1    0.99    0.00    0.99    0.00    0.00    0.00    0.00   98.02    0.00    0.00
14:48:18       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:18       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:18       4    1.01    0.00    2.02    2.02    0.00    0.00    0.00    0.00    0.00   94.95

14:48:18     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:19     all    0.00    0.00    0.20    0.00    0.00    0.00    0.00   80.16    0.00   19.64
14:48:19       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:19       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:19       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:19       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:19       4    0.00    0.00    1.01    0.00    0.00    0.00    0.00    0.00    0.00   98.99

14:48:19     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:20     all    0.00    0.00    0.00    0.00    0.00    0.00    0.00   80.20    0.00   19.80
14:48:20       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:20       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:20       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:20       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:20       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

14:48:20     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:21     all    0.20    0.00    0.80    0.00    0.00    0.00    0.00   79.64    0.00   19.36
14:48:21       0    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
14:48:21       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:21       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:21       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:21       4    0.99    0.00    2.97    0.00    0.00    0.00    0.00    0.00    0.00   96.04

14:48:21     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:22     all    0.20    0.00    0.00    0.00    0.00    0.20    0.00   79.84    0.00   19.76
14:48:22       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:22       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:22       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:22       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:22       4    0.99    0.00    0.00    0.00    0.00    0.99    0.00    0.00    0.00   98.02

14:48:22     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:23     all    0.00    0.00    0.79    0.00    0.00    0.00    0.00   79.96    0.00   19.25
14:48:23       0    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:23       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:23       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:23       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:23       4    0.00    0.00    3.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00

14:48:23     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:23     all    0.40    0.00    0.80    0.40    0.00    0.20    0.00   79.44    0.00   18.76
14:48:23       0    0.99    0.00    0.99    0.00    0.00    0.99    0.00   97.03    0.00    0.00
14:48:23       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:23       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:23       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:23       4    1.00    0.00    3.00    2.00    0.00    0.00    0.00    0.00    0.00   94.00

14:48:23     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:24     all    0.20    0.00    0.79    0.00    0.00    0.00    0.00   79.56    0.00   19.25
14:48:24       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:24       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:24       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:24       3    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:24       4    0.99    0.00    2.97    0.00    0.00    0.00    0.00    0.00    0.00   96.04

14:48:24     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:25     all    0.20    0.00    0.00    0.00    0.00    0.00    0.00   80.00    0.00   19.80
14:48:25       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:25       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:25       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:25       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:25       4    1.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00

14:48:25     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:26     all    0.20    0.00    0.60    0.00    0.00    0.00    0.00   79.84    0.00   19.16
14:48:26       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:26       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:26       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:26       3    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:26       4    2.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   96.00

14:48:26     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:27     all    0.59    0.00    0.40    0.00    0.00    0.00    0.00   79.05    0.00   19.96
14:48:27       0    0.00    0.00    0.98    0.00    0.00    0.00    0.00   98.04    0.00    0.98
14:48:27       1    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:27       2    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:27       3    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
14:48:27       4    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01

14:48:27     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:28     all    0.20    0.00    1.20    0.40    0.00    0.20    0.00   74.80    0.00   23.20
14:48:28       0    0.00    0.00    1.01    0.00    0.00    0.00    0.00   98.99    0.00    0.00
14:48:28       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00   78.22    0.00   20.79
14:48:28       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
14:48:28       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00    0.00    3.00
14:48:28       4    1.00    0.00    4.00    2.00    0.00    1.00    0.00    0.00    0.00   92.00

14:48:28     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
14:48:29     all    0.00    0.00    0.20    0.00    0.00    0.00    0.00    8.15    0.00   91.65
14:48:29       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:48:29       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
14:48:29       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00   39.60    0.00   60.40
14:48:29       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.99    0.00   99.01
14:48:29       4    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01
```

# Taskset

## Isloated
```bash
$ sudo taskset -c 0,1 firecracker --no-api --config-file vmconfig.json
```

```bash
$ ./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.017 s
Thread 1 reached 1000000000 iterations, elapsed: 1.039 s
Thread 0 reached 2000000000 iterations, elapsed: 2.023 s
Thread 1 reached 2000000000 iterations, elapsed: 2.052 s
Thread 0 reached 3000000000 iterations, elapsed: 2.990 s
Thread 1 reached 3000000000 iterations, elapsed: 3.026 s
Thread 0 reached 4000000000 iterations, elapsed: 3.980 s
Thread 1 reached 4000000000 iterations, elapsed: 4.020 s
Thread 0 reached 5000000000 iterations, elapsed: 4.985 s
Thread 1 reached 5000000000 iterations, elapsed: 5.036 s
Thread 0 reached 6000000000 iterations, elapsed: 5.974 s
Thread 1 reached 6000000000 iterations, elapsed: 6.021 s
Thread 0 reached 7000000000 iterations, elapsed: 6.996 s
Thread 1 reached 7000000000 iterations, elapsed: 7.049 s
Thread 0 reached 8000000000 iterations, elapsed: 7.985 s
Thread 1 reached 8000000000 iterations, elapsed: 8.043 s
Thread 0 reached 9000000000 iterations, elapsed: 8.985 s
Thread 1 reached 9000000000 iterations, elapsed: 9.041 s
Thread 0 reached 10000000000 iterations, elapsed: 9.984 s
Thread 0 finished 10000000000 iterations in 9.985 s
Thread 1 reached 10000000000 iterations, elapsed: 10.041 s
Thread 1 finished 10000000000 iterations in 10.042 s
All threads finished.
```

```bash
mpstat -P ALL 1
Linux 6.6.87.2-microsoft-standard-WSL2 (GUARD-LAPTOP)   11/08/25        _x86_64_        (5 CPU)

13:53:05     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:06     all    0.40    0.00    0.60    0.00    0.00    0.00    0.00    5.98    0.00   93.03
13:53:06       0    0.00    0.00    1.00    0.00    0.00    0.00    0.00   15.00    0.00   84.00
13:53:06       1    1.00    0.00    0.00    0.00    0.00    0.00    0.00   15.00    0.00   84.00
13:53:06       2    0.98    0.00    0.98    0.00    0.00    0.00    0.00    0.00    0.00   98.04
13:53:06       3    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
13:53:06       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:53:06     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:07     all    0.20    0.00    0.40    0.00    0.00    0.40    0.00   39.76    0.00   59.24
13:53:07       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:07       1    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:53:07       2    0.98    0.00    0.00    0.00    0.00    1.96    0.00    0.00    0.00   97.06
13:53:07       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:53:07       4    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00

13:53:07     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:08     all    0.19    0.00    0.78    0.00    0.00    0.00    0.00   40.08    0.00   58.95
13:53:08       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:08       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:08       2    0.00    0.00    0.98    0.00    0.00    0.00    0.00    0.00    0.00   99.02
13:53:08       3    0.00    0.00    0.97    0.00    0.00    0.00    0.00    0.00    0.00   99.03
13:53:08       4    0.97    0.00    1.94    0.00    0.00    0.00    0.00    0.00    0.00   97.09

13:53:08     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:09     all    0.00    0.00    0.00    0.00    0.00    0.60    0.00   39.76    0.00   59.64
13:53:09       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:09       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:09       2    0.00    0.00    0.00    0.00    0.00    2.91    0.00    0.00    0.00   97.09
13:53:09       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:53:09       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:53:09     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:10     all    0.78    0.00    0.59    0.00    0.00    0.20    0.00   40.00    0.00   58.43
13:53:10       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:10       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:10       2    1.96    0.00    0.98    0.00    0.00    0.98    0.00    0.00    0.00   96.08
13:53:10       3    0.97    0.00    1.94    0.00    0.00    0.00    0.00    0.00    0.00   97.09
13:53:10       4    0.99    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.01

13:53:10     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:11     all    0.00    0.00    1.39    0.60    0.00    0.00    0.00   39.84    0.00   58.17
13:53:11       0    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:53:11       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:11       2    0.00    0.00    1.98    1.98    0.00    0.00    0.00    0.00    0.00   96.04
13:53:11       3    0.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   98.00
13:53:11       4    0.00    0.00    2.00    1.00    0.00    0.00    0.00    0.00    0.00   97.00

13:53:11     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:12     all    0.20    0.00    0.60    0.00    0.00    0.20    0.00   40.08    0.00   58.93
13:53:12       0    0.98    0.00    0.00    0.00    0.00    0.00    0.00   99.02    0.00    0.00
13:53:12       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:12       2    0.00    0.00    0.98    0.00    0.00    0.98    0.00    0.00    0.00   98.04
13:53:12       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:53:12       4    0.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   98.00

13:53:12     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:13     all    0.20    0.00    0.20    0.00    0.00    0.20    0.00   39.84    0.00   59.56
13:53:13       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:13       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:13       2    0.00    0.00    0.99    0.00    0.00    0.99    0.00    0.00    0.00   98.02
13:53:13       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:53:13       4    0.99    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.01

13:53:13     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:14     all    0.00    0.00    0.98    0.00    0.00    0.39    0.00   40.08    0.00   58.55
13:53:14       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:14       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:14       2    0.00    0.00    1.94    0.00    0.00    1.94    0.00    0.00    0.00   96.12
13:53:14       3    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01
13:53:14       4    0.00    0.00    1.98    0.00    0.00    0.00    0.00    0.00    0.00   98.02

13:53:14     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:15     all    0.00    0.00    0.00    0.00    0.00    0.20    0.00   39.92    0.00   59.88
13:53:15       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:15       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:15       2    0.00    0.00    0.00    0.00    0.00    0.99    0.00    0.00    0.00   99.01
13:53:15       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:53:15       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:53:15     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:15     all    0.98    0.00    1.37    0.78    0.00    0.20    0.00   39.65    0.00   57.03
13:53:15       0    0.98    0.00    0.00    0.00    0.00    0.00    0.00   99.02    0.00    0.00
13:53:15       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:53:15       2    1.92    0.00    1.92    0.96    0.00    0.96    0.00    0.00    0.00   94.23
13:53:15       3    0.97    0.00    2.91    0.00    0.00    0.00    0.00    0.00    0.00   96.12
13:53:15       4    0.99    0.00    1.98    2.97    0.00    0.00    0.00    0.00    0.00   94.06

13:53:15     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:53:16     all    0.00    0.00    0.40    0.00    0.00    0.20    0.00   30.54    0.00   68.86
13:53:16       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00   80.00    0.00   20.00
13:53:16       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00   73.74    0.00   26.26
13:53:16       2    0.00    0.00    0.00    0.00    0.00    1.00    0.00    0.00    0.00   99.00
13:53:16       3    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01
13:53:16       4    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01
```

## Multi-Tenent

### Tenant 1
```bash
sudo taskset -c 0,1 firecracker --no-api --config-file vmconfig.json
```

### Tenant 2
```bash
sudo taskset -c 2,3 firecracker --no-api --config-file vmconfig.json
```

Verify cores set successfully
```bash
$ ps -eLo pid,tid,psr,comm | grep firecracker
  26990   26990   0 firecracker
  27809   27809   2 firecracker
```

### Tenent 1
```bash
$ ./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.236 s
Thread 0 reached 1000000000 iterations, elapsed: 1.238 s
Thread 0 reached 2000000000 iterations, elapsed: 2.394 s
Thread 1 reached 2000000000 iterations, elapsed: 2.446 s
Thread 0 reached 3000000000 iterations, elapsed: 3.510 s
Thread 1 reached 3000000000 iterations, elapsed: 3.795 s
Thread 0 reached 4000000000 iterations, elapsed: 4.741 s
Thread 1 reached 4000000000 iterations, elapsed: 5.015 s
Thread 0 reached 5000000000 iterations, elapsed: 6.052 s
Thread 1 reached 5000000000 iterations, elapsed: 6.379 s
Thread 0 reached 6000000000 iterations, elapsed: 7.367 s
Thread 1 reached 6000000000 iterations, elapsed: 7.656 s
Thread 0 reached 7000000000 iterations, elapsed: 8.459 s
Thread 1 reached 7000000000 iterations, elapsed: 8.860 s
Thread 0 reached 8000000000 iterations, elapsed: 9.711 s
Thread 1 reached 8000000000 iterations, elapsed: 10.175 s
Thread 0 reached 9000000000 iterations, elapsed: 10.921 s
Thread 1 reached 9000000000 iterations, elapsed: 11.490 s
Thread 0 reached 10000000000 iterations, elapsed: 12.161 s
Thread 0 finished 10000000000 iterations in 12.162 s
Thread 1 reached 10000000000 iterations, elapsed: 12.740 s
Thread 1 finished 10000000000 iterations in 12.741 s
All threads finished.
```

### Tenent 2
```bash
$ ./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.209 s
Thread 1 reached 1000000000 iterations, elapsed: 1.352 s
Thread 0 reached 2000000000 iterations, elapsed: 2.501 s
Thread 1 reached 2000000000 iterations, elapsed: 2.660 s
Thread 0 reached 3000000000 iterations, elapsed: 3.853 s
Thread 1 reached 3000000000 iterations, elapsed: 3.955 s
Thread 0 reached 4000000000 iterations, elapsed: 5.106 s
Thread 1 reached 4000000000 iterations, elapsed: 5.195 s
Thread 0 reached 5000000000 iterations, elapsed: 6.351 s
Thread 1 reached 5000000000 iterations, elapsed: 6.370 s
Thread 1 reached 6000000000 iterations, elapsed: 7.620 s
Thread 0 reached 6000000000 iterations, elapsed: 7.739 s
Thread 1 reached 7000000000 iterations, elapsed: 8.946 s
Thread 0 reached 7000000000 iterations, elapsed: 9.110 s
Thread 1 reached 8000000000 iterations, elapsed: 10.233 s
Thread 0 reached 8000000000 iterations, elapsed: 10.467 s
Thread 1 reached 9000000000 iterations, elapsed: 11.470 s
Thread 0 reached 9000000000 iterations, elapsed: 11.677 s
Thread 1 reached 10000000000 iterations, elapsed: 12.658 s
Thread 1 finished 10000000000 iterations in 12.659 s
Thread 0 reached 10000000000 iterations, elapsed: 12.745 s
Thread 0 finished 10000000000 iterations in 12.746 s
All threads finished.
```

```bash
mpstat -P ALL 1
Linux 6.6.87.2-microsoft-standard-WSL2 (GUARD-LAPTOP)   11/08/25        _x86_64_        (5 CPU)

13:56:41     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:41     all    0.00    0.00    0.98    0.59    0.00    0.00    0.00    7.86    0.00   90.57
13:56:41       0    0.00    0.00    0.98    0.00    0.00    0.00    0.00   19.61    0.00   79.41
13:56:41       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00   19.80    0.00   80.20
13:56:41       2    0.00    0.00    1.96    0.98    0.00    0.00    0.00    0.00    0.00   97.06
13:56:41       3    0.00    0.00    0.98    0.98    0.00    0.00    0.00    0.00    0.00   98.04
13:56:41       4    0.00    0.00    0.98    0.98    0.00    0.00    0.00    0.00    0.00   98.04

13:56:41     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:42     all    0.20    0.00    0.40    0.00    0.00    0.20    0.00   67.13    0.00   31.87
13:56:42       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:42       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:42       2    0.00    0.00    0.00    0.00    0.00    0.99    0.00   68.32    0.00   30.69
13:56:42       3    0.99    0.00    0.00    0.00    0.00    0.00    0.00   67.33    0.00   31.68
13:56:42       4    1.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00

13:56:42     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:43     all    0.00    0.00    0.00    0.00    0.00    0.20    0.00   79.80    0.00   19.80
13:56:43       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:43       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:43       2    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
13:56:43       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:43       4    0.00    0.00    0.00    0.00    0.00    1.00    0.00    0.00    0.00   99.00

13:56:43     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:44     all    0.60    0.00    0.40    0.00    0.00    0.00    0.00   79.68    0.00   19.32
13:56:44       0    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:56:44       1    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:56:44       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:44       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:44       4    1.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00

13:56:44     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:45     all    0.00    0.00    0.00    0.00    0.00    0.00    0.00   80.16    0.00   19.84
13:56:45       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:45       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:45       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:45       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:45       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:56:45     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:46     all    0.20    0.00    0.60    0.40    0.00    0.00    0.00   79.64    0.00   18.96
13:56:46       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:46       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:46       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:46       3    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
13:56:46       4    0.99    0.00    2.97    1.98    0.00    0.00    0.00    0.00    0.00   94.06

13:56:46     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:47     all    0.40    0.00    0.40    0.00    0.00    0.00    0.00   79.80    0.00   19.20
13:56:47       0    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
13:56:47       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:47       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:47       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:47       4    2.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   96.00

13:56:47     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:48     all    0.00    0.00    0.00    0.00    0.00    0.00    0.00   80.16    0.00   19.84
13:56:48       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:48       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:48       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:48       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:48       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:56:48     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:49     all    0.00    0.00    0.40    0.00    0.00    0.00    0.00   80.16    0.00   19.44
13:56:49       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:49       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:49       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:49       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:49       4    0.00    0.00    2.02    0.00    0.00    0.00    0.00    0.00    0.00   97.98

13:56:49     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:50     all    0.00    0.00    0.40    0.00    0.00    0.00    0.00   79.76    0.00   19.84
13:56:50       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:50       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:50       2    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
13:56:50       3    0.00    0.00    1.00    0.00    0.00    0.00    0.00   99.00    0.00    0.00
13:56:50       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:56:50     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:51     all    0.20    0.00    0.60    0.00    0.00    0.00    0.00   79.64    0.00   19.36
13:56:51       0    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:56:51       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:51       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:51       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:51       4    1.98    0.00    1.98    0.00    0.00    0.00    0.00    0.00    0.00   96.04

13:56:51     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:51     all    0.00    0.00    0.80    0.60    0.00    0.00    0.00   79.84    0.00   18.76
13:56:51       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:51       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:51       2    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:56:51       3    0.00    0.00    0.99    0.00    0.00    0.00    0.00   99.01    0.00    0.00
13:56:51       4    0.00    0.00    2.02    3.03    0.00    0.00    0.00    0.00    0.00   94.95

13:56:51     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:52     all    0.78    0.00    0.39    0.00    0.00    0.20    0.00   79.22    0.00   19.41
13:56:52       0    0.98    0.00    0.00    0.00    0.00    0.00    0.00   99.02    0.00    0.00
13:56:52       1    0.98    0.00    0.00    0.00    0.00    0.00    0.00   99.02    0.00    0.00
13:56:52       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:52       3    0.98    0.00    0.00    0.00    0.00    0.00    0.00   99.02    0.00    0.00
13:56:52       4    0.97    0.00    1.94    0.00    0.00    0.97    0.00    0.00    0.00   96.12

13:56:52     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:53     all    0.00    0.00    0.20    0.00    0.00    0.00    0.00   80.00    0.00   19.80
13:56:53       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:53       1    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:53       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:53       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:53       4    0.00    0.00    0.99    0.00    0.00    0.00    0.00    0.00    0.00   99.01

13:56:53     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:54     all    0.00    0.00    0.59    0.00    0.00    0.79    0.00   58.50    0.00   39.92
13:56:54       0    0.00    0.00    0.00    0.00    0.00    0.00    0.00   79.00    0.00   21.00
13:56:54       1    0.00    0.00    0.95    0.00    0.00    3.81    0.00   15.24    0.00   80.00
13:56:54       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:54       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00    0.00    0.00
13:56:54       4    1.00    0.00    2.00    0.00    0.00    0.00    0.00    0.00    0.00   97.00

13:56:54     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:55     all    0.20    0.00    0.00    0.00    0.00    0.20    0.00   10.34    0.00   89.26
13:56:55       0    0.00    0.00    0.00    0.00    0.00    0.99    0.00    0.00    0.00   99.01
13:56:55       1    0.99    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00   99.01
13:56:55       2    0.00    0.00    0.00    0.00    0.00    0.00    0.00   30.69    0.00   69.31
13:56:55       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00   21.00    0.00   79.00
13:56:55       4    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00

13:56:55     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:56:56     all    0.40    0.00    1.20    0.60    0.00    0.00    0.00    0.00    0.00   97.80
13:56:56       0    0.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   99.00
13:56:56       1    0.00    0.00    1.00    1.00    0.00    0.00    0.00    0.00    0.00   98.00
13:56:56       2    0.98    0.00    1.96    0.98    0.00    0.00    0.00    0.00    0.00   96.08
13:56:56       3    0.00    0.00    1.01    1.01    0.00    0.00    0.00    0.00    0.00   97.98
13:56:56       4    1.00    0.00    1.00    0.00    0.00    0.00    0.00    0.00    0.00   98.00
```
