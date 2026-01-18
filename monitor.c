
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read CPU usage from /proc/stat
void getCPUUsage() {
    FILE *fp;
    char buffer[1024];
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Error opening /proc/stat");
        return;
    }

    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    char cpu[5];
    long user, nice, system, idle;
    sscanf(buffer, "%s %ld %ld %ld %ld", cpu, &user, &nice, &system, &idle);

    long total = user + nice + system + idle;
    double usage = (double)(user + nice + system) / total * 100.0;

    printf("CPU Usage: %.2f%%\n", usage);
}

// Function to read memory usage from /proc/meminfo
void getMemoryUsage() {
    FILE *fp;
    char label[256];
    long totalMem, freeMem;

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Error opening /proc/meminfo");
        return;
    }

    fscanf(fp, "%s %ld", label, &totalMem);
    fscanf(fp, "%s %ld", label, &freeMem);
    fclose(fp);

    double used = (double)(totalMem - freeMem) / totalMem * 100.0;
    printf("Memory Usage: %.2f%%\n", used);
}

int main() {
    printf("=== System Resource Monitor ===\n");
    getCPUUsage();
    getMemoryUsage();
    return 0;
}

