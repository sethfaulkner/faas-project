# No Pinning

## Isolated
```bash
Thread 0 finished 10000000000 iterations in 9.563 s
Thread 1 finished 10000000000 iterations in 9.619 s
```

Load is shared between CPU's 0,1,2,3

## Multi-tenant

### Tenant 1
```bash
Thread 1 finished 10000000000 iterations in 10.252 s
Thread 0 finished 10000000000 iterations in 14.096 s
```

### Tenant 2
```bash
Thread 0 finished 10000000000 iterations in 10.318 s
Thread 1 finished 10000000000 iterations in 13.028 s
```

One of the threads finishes much before the other, probably due to sharing the performace cores (0-3). The firecracker config did not have an effect as running two tenants is clearly having an effect on both tenants.

# CPU Pinning with `cgroups` 

## Isolated

Firecracker was pinned to cores 0 and 1

```bash
sudo systemd-run --scope -p AllowedCPUs=0,1 ./firecracker --no-api --config-file vmconfig.json

Thread 1 finished 10000000000 iterations in 20.357 s
Thread 0 finished 10000000000 iterations in 20.392 s
```

Threads were forced to run only on cores 0 and 1, slowing down performance.

## Mult-tenant

### Tenant 1
Firecracker was pinned to cores 0 and 1
```bash
sudo systemd-run --scope -p AllowedCPUs=0,1 ./firecracker --no-api --config-file vmconfig.json

Thread 0 finished 10000000000 iterations in 20.806 s
Thread 1 finished 10000000000 iterations in 20.862 s
```

### Tenant 2
Firecracker was pinned to cores 2 and 3
```bash
sudo systemd-run --scope -p AllowedCPUs=2,3 ./firecracker --no-api --config-file vmconfig.json

Thread 0 finished 10000000000 iterations in 20.386 s
Thread 1 finished 10000000000 iterations in 20.402 s
```

This privided consistent results for both processes.

# CPU Pinning - Skewed Allowed CPUs

## Isolated
One process is given a single core and allowed to use 100% of it.
```bash
sudo systemd-run --scope -p AllowedCPUs=0 ./firecracker --no-api --config-file vmconfig.json

Thread 1 finished 10000000000 iterations in 19.356 s
Thread 0 finished 10000000000 iterations in 19.373 s
```

Odly, slightly faster than 2 cores.

## Mult-tenant

### Tenant 1
```bash
sudo systemd-run --scope -p AllowedCPUs=0 ./firecracker --no-api --config-file vmconfig.json

Thread 1 finished 10000000000 iterations in 33.076 s
Thread 0 finished 10000000000 iterations in 33.091 s
```

### Tenant 2
```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 ./firecracker --no-api --config-file vmconfig.json
```
Finished 2 cycles in close to the same time. When run by itself, tenant 2 shows activity only on cores 1 and 2, but is clearly slowing down the progress of tenant 1. Ran the same scenario with `numactl` with nearly identical results.


# CPU Pinning - Skewed Allowed Quota

## Isolated
```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 -p CPUQuota=60% ./firecracker --no-api --config-file vmconfig.json

Thread 0 finished 10000000000 iterations in 103.253 s
Thread 1 finished 10000000000 iterations in 104.771 s
```
Very very slow execution.

## Multi-Tenant 

### Tenant 1
```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 -p CPUQuota=60% ./firecracker --no-api --config-file vmconfig.json

Thread 1 finished 10000000000 iterations in 73.860 s
Thread 0 finished 10000000000 iterations in 74.100 s
```

### Tenant 2
```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 -p CPUQuota=140% ./firecracker --no-api --config-file vmconfig.json

Thread 1 finished 10000000000 iterations in 15.092 s
Thread 0 finished 10000000000 iterations in 15.222 s
```

The first tenant was actually faster. This is due to the CPU being fully allocated, which reduces throttling.

# CPU Pinning - Skewed Weight

## Isolated

```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 -p CPUWeight=300 ./firecracker --no-api --config-file vmconfig.json

Thread 0 finished 10000000000 iterations in 10.609 s
Thread 1 finished 10000000000 iterations in 10.620 s
```

## Multi-Tenant

### Tenant 1
```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 -p CPUWeight=300 ./firecracker --no-api --config-file vmconfig.json

Thread 0 finished 10000000000 iterations in 20.827 s
Thread 1 finished 10000000000 iterations in 21.175 s
```

### Tenant 2
```bash
sudo systemd-run --scope -p AllowedCPUs=1,2 -p CPUWeight=700 ./firecracker --no-api --config-file vmconfig.json

Thread 0 finished 10000000000 iterations in 15.484 s
Thread 1 finished 10000000000 iterations in 15.897 s
```
