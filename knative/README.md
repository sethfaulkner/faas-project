# Knative

## Install [Docker](https://docs.docker.com/engine/install/ubuntu/)

## Install [Minikube](https://minikube.sigs.k8s.io/docs/start/?arch=%2Flinux%2Fx86-64%2Fstable%2Fbinary+download)
```bash
minikube start --driver=docker --cpus=5 --memory=4096
```

## Setup [Knative](https://knative.dev/docs/install/yaml-install/serving/install-serving-with-yaml/)
```bash
minikube kubectl -- apply -f https://github.com/knative/serving/releases/download/knative-v1.20.0/serving-crds.yaml
minikube kubectl -- apply -f https://github.com/knative/serving/releases/download/knative-v1.20.0/serving-core.yaml
```

# Initial Test
## Isolated
```yaml
# Ensure a single replica
autoscaling.knative.dev/minScale: "1"
autoscaling.knative.dev/maxScale: "1"

# Ensure CPU requests are in place
resources:
requests:
    cpu: "2"
    memory: "512Mi"
limits:
    cpu: "2"
    memory: "512Mi"
```
```bash
minikube kubectl -- apply -f hello.yaml
minikube kubectl -- get pods

NAME          READY   STATUS    RESTARTS   AGE
hello-00001   2/2     Running   0          18s

# Copy payload into pod
minikube kubectl -- cp ../cpu_stress hello-00001:/

# Exec into pod
minikube kubectl -- exec -it hello-00001 -- sh

# Execute payload
./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.053 s
Thread 0 reached 1000000000 iterations, elapsed: 1.054 s
Thread 1 reached 2000000000 iterations, elapsed: 2.105 s
Thread 0 reached 2000000000 iterations, elapsed: 2.108 s
Thread 1 reached 3000000000 iterations, elapsed: 3.138 s
Thread 0 reached 3000000000 iterations, elapsed: 3.141 s
Thread 0 reached 4000000000 iterations, elapsed: 4.174 s
Thread 1 reached 4000000000 iterations, elapsed: 4.174 s
Thread 1 reached 5000000000 iterations, elapsed: 5.206 s
Thread 0 reached 5000000000 iterations, elapsed: 5.213 s
Thread 1 reached 6000000000 iterations, elapsed: 6.258 s
Thread 0 reached 6000000000 iterations, elapsed: 6.265 s
Thread 1 reached 7000000000 iterations, elapsed: 7.324 s
Thread 0 reached 7000000000 iterations, elapsed: 7.341 s
Thread 1 reached 8000000000 iterations, elapsed: 8.351 s
Thread 0 reached 8000000000 iterations, elapsed: 8.388 s
Thread 1 reached 9000000000 iterations, elapsed: 9.394 s
Thread 0 reached 9000000000 iterations, elapsed: 9.422 s
Thread 0 reached 10000000000 iterations, elapsed: 10.448 s
Thread 0 finished 10000000000 iterations in 10.448 s
Thread 1 reached 10000000000 iterations, elapsed: 10.457 s
Thread 1 finished 10000000000 iterations in 10.457 s
All threads finished.
```

## Multi-Tenent
```yaml
# Ensure a two replicas
autoscaling.knative.dev/minScale: "2"
autoscaling.knative.dev/maxScale: "2"
```

### Tenent 1
```bash
./cpu_stress
Thread 1 reached 1000000000 iterations, elapsed: 1.135 s
Thread 0 reached 1000000000 iterations, elapsed: 1.172 s
Thread 0 reached 2000000000 iterations, elapsed: 2.447 s
Thread 1 reached 2000000000 iterations, elapsed: 2.538 s
Thread 0 reached 3000000000 iterations, elapsed: 3.810 s
Thread 1 reached 3000000000 iterations, elapsed: 3.847 s
Thread 1 reached 4000000000 iterations, elapsed: 5.088 s
Thread 0 reached 4000000000 iterations, elapsed: 5.241 s
Thread 1 reached 5000000000 iterations, elapsed: 6.392 s
Thread 0 reached 5000000000 iterations, elapsed: 6.569 s
Thread 1 reached 6000000000 iterations, elapsed: 7.627 s
Thread 0 reached 6000000000 iterations, elapsed: 7.934 s
Thread 1 reached 7000000000 iterations, elapsed: 8.915 s
Thread 0 reached 7000000000 iterations, elapsed: 9.171 s
Thread 1 reached 8000000000 iterations, elapsed: 10.152 s
Thread 0 reached 8000000000 iterations, elapsed: 10.496 s
Thread 1 reached 9000000000 iterations, elapsed: 11.432 s
Thread 0 reached 9000000000 iterations, elapsed: 11.823 s
Thread 1 reached 10000000000 iterations, elapsed: 12.779 s
Thread 1 finished 10000000000 iterations in 12.779 s
Thread 0 reached 10000000000 iterations, elapsed: 13.136 s
Thread 0 finished 10000000000 iterations in 13.136 s
All threads finished.
```

### Tenant 2
```bash
./cpu_stress
Thread 0 reached 1000000000 iterations, elapsed: 1.290 s
Thread 1 reached 1000000000 iterations, elapsed: 1.355 s
Thread 0 reached 2000000000 iterations, elapsed: 2.576 s
Thread 1 reached 2000000000 iterations, elapsed: 2.713 s
Thread 0 reached 3000000000 iterations, elapsed: 3.849 s
Thread 1 reached 3000000000 iterations, elapsed: 3.888 s
Thread 0 reached 4000000000 iterations, elapsed: 5.088 s
Thread 1 reached 4000000000 iterations, elapsed: 5.213 s
Thread 1 reached 5000000000 iterations, elapsed: 6.462 s
Thread 0 reached 5000000000 iterations, elapsed: 6.473 s
Thread 1 reached 6000000000 iterations, elapsed: 7.812 s
Thread 0 reached 6000000000 iterations, elapsed: 7.851 s
Thread 0 reached 7000000000 iterations, elapsed: 9.159 s
Thread 1 reached 7000000000 iterations, elapsed: 9.185 s
Thread 0 reached 8000000000 iterations, elapsed: 10.429 s
Thread 1 reached 8000000000 iterations, elapsed: 10.573 s
Thread 0 reached 9000000000 iterations, elapsed: 11.688 s
Thread 1 reached 9000000000 iterations, elapsed: 11.906 s
Thread 0 reached 10000000000 iterations, elapsed: 12.895 s
Thread 0 finished 10000000000 iterations in 12.895 s
Thread 1 reached 10000000000 iterations, elapsed: 13.036 s
Thread 1 finished 10000000000 iterations in 13.036 s
All threads finished.
```