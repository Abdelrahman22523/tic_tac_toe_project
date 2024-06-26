#include "performanceoptimizer.h"
#include <QDebug>
#include <QTimer>

#ifdef Q_OS_WIN
#include <windows.h>
#include <psapi.h>
#endif

PerformanceOptimizer::PerformanceOptimizer(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PerformanceOptimizer::measurePerformance);
    timer->start(1000); // Adjust interval as needed (every 1000 ms = 1 second)
}

PerformanceOptimizer::~PerformanceOptimizer()
{
    if (timer->isActive())
        timer->stop();
    delete timer;
}

void PerformanceOptimizer::optimize()
{
    // Implement optimization logic here
    // Example: Check memory usage, optimize data structures, etc.
}

void PerformanceOptimizer::measurePerformance()
{
    // Measure CPU time (not CPU utilization)
    qint64 cpuTime = 0;

#ifdef Q_OS_WIN
    FILETIME createTime, exitTime, kernelTime, userTime;
    GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime);
    cpuTime = (static_cast<qint64>(userTime.dwHighDateTime) << 32 | userTime.dwLowDateTime) / 10000;
#elif defined(Q_OS_LINUX)
    // Linux CPU measurement
#endif

    qDebug() << "CPU Time (ms):" << cpuTime;

// Measure memory usage (Windows)
#ifdef Q_OS_WIN
    qint64 memoryUsed = platformSpecificMemoryUsage();
    qDebug() << "Memory Used (bytes):" << memoryUsed;
#else
    qDebug() << "Memory Used: Platform-specific method not implemented.";
#endif

    // Call optimization function periodically
    optimize();
}

qint64 PerformanceOptimizer::platformSpecificMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    } else {
        qWarning() << "Failed to retrieve memory information.";
        return -1;
    }
}
