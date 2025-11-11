# gVisor (runsc)

# Install [runsc](https://gvisor.dev/docs/user_guide/install/)

Add runtime to docker
```json
{
  "runtimes": {
    "runsc": {
      "path": "/usr/bin/runsc"
    }
  }
}
```

# Isolated
```bash
docker run -it --runtime=runsc --cpus=2 --cpuset-cpus="0,1" --memory=512m --rm ubuntu:24.04 bash
./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.099 s
Thread 1 reached 1000000000 iterations, elapsed: 1.108 s
Thread 0 reached 2000000000 iterations, elapsed: 2.172 s
Thread 1 reached 2000000000 iterations, elapsed: 2.184 s
Thread 1 reached 3000000000 iterations, elapsed: 3.259 s
Thread 0 reached 3000000000 iterations, elapsed: 3.275 s
Thread 0 reached 4000000000 iterations, elapsed: 4.347 s
Thread 1 reached 4000000000 iterations, elapsed: 4.363 s
Thread 0 reached 5000000000 iterations, elapsed: 5.361 s
Thread 1 reached 5000000000 iterations, elapsed: 5.406 s
Thread 0 reached 6000000000 iterations, elapsed: 6.428 s
Thread 1 reached 6000000000 iterations, elapsed: 6.505 s
Thread 0 reached 7000000000 iterations, elapsed: 7.460 s
Thread 1 reached 7000000000 iterations, elapsed: 7.550 s
Thread 0 reached 8000000000 iterations, elapsed: 8.484 s
Thread 1 reached 8000000000 iterations, elapsed: 8.587 s
Thread 0 reached 9000000000 iterations, elapsed: 9.505 s
Thread 1 reached 9000000000 iterations, elapsed: 9.614 s
Thread 0 reached 10000000000 iterations, elapsed: 10.516 s
Thread 0 finished 10000000000 iterations in 10.516 s
Thread 1 reached 10000000000 iterations, elapsed: 10.639 s
Thread 1 finished 10000000000 iterations in 10.639 s
```

# Multi Tenant

## Tenant 1
```bash
./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.172 s
Thread 1 reached 1000000000 iterations, elapsed: 1.259 s
Thread 1 reached 2000000000 iterations, elapsed: 2.533 s
Thread 0 reached 2000000000 iterations, elapsed: 2.663 s
Thread 1 reached 3000000000 iterations, elapsed: 3.839 s
Thread 0 reached 3000000000 iterations, elapsed: 3.874 s
Thread 1 reached 4000000000 iterations, elapsed: 5.154 s
Thread 0 reached 4000000000 iterations, elapsed: 5.231 s
Thread 0 reached 5000000000 iterations, elapsed: 6.512 s
Thread 1 reached 5000000000 iterations, elapsed: 6.524 s
Thread 0 reached 6000000000 iterations, elapsed: 7.672 s
Thread 1 reached 6000000000 iterations, elapsed: 7.964 s
Thread 0 reached 7000000000 iterations, elapsed: 9.156 s
Thread 1 reached 7000000000 iterations, elapsed: 9.290 s
Thread 0 reached 8000000000 iterations, elapsed: 10.523 s
Thread 1 reached 8000000000 iterations, elapsed: 10.684 s
Thread 0 reached 9000000000 iterations, elapsed: 11.870 s
Thread 1 reached 9000000000 iterations, elapsed: 12.036 s
Thread 0 reached 10000000000 iterations, elapsed: 13.225 s
Thread 0 finished 10000000000 iterations in 13.225 s
Thread 1 reached 10000000000 iterations, elapsed: 13.297 s
Thread 1 finished 10000000000 iterations in 13.297 s
```

## Tenant 2
```bash
./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.238 s
Thread 0 reached 1000000000 iterations, elapsed: 1.361 s
Thread 1 reached 2000000000 iterations, elapsed: 2.638 s
Thread 0 reached 2000000000 iterations, elapsed: 2.776 s
Thread 1 reached 3000000000 iterations, elapsed: 3.953 s
Thread 0 reached 3000000000 iterations, elapsed: 4.208 s
Thread 1 reached 4000000000 iterations, elapsed: 5.258 s
Thread 0 reached 4000000000 iterations, elapsed: 5.488 s
Thread 1 reached 5000000000 iterations, elapsed: 6.698 s
Thread 0 reached 5000000000 iterations, elapsed: 6.804 s
Thread 1 reached 6000000000 iterations, elapsed: 8.071 s
Thread 0 reached 6000000000 iterations, elapsed: 8.326 s
Thread 1 reached 7000000000 iterations, elapsed: 9.440 s
Thread 0 reached 7000000000 iterations, elapsed: 9.804 s
Thread 1 reached 8000000000 iterations, elapsed: 10.874 s
Thread 0 reached 8000000000 iterations, elapsed: 11.127 s
Thread 1 reached 9000000000 iterations, elapsed: 12.214 s
Thread 0 reached 9000000000 iterations, elapsed: 12.502 s
Thread 1 reached 10000000000 iterations, elapsed: 13.416 s
Thread 1 finished 10000000000 iterations in 13.416 s
Thread 0 reached 10000000000 iterations, elapsed: 13.591 s
Thread 0 finished 10000000000 iterations in 13.591 s
```