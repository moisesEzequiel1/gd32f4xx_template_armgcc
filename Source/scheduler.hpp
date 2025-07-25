#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <stdint.h>

namespace ec {

// Function pointer type for periodic tasks
using TaskFunc = void (*)();

// Configuration constants
constexpr int MAX_TASKS = 10;
constexpr uint32_t TICK_US = 100U;  // Tick duration in microseconds

class Scheduler {
public:
    // Initialize the scheduler and configure SysTick
    static void init();

    /**
     * Add a periodic task.
     * @param task Function to execute periodically.
     * @param period_us Period in microseconds.
     * @return true if added successfully.
     */
    static bool add_task(TaskFunc task, uint32_t period_us);

    // Start the scheduler (infinite loop)
    static void start();

    // Tick handler to be called periodically (e.g., from SysTick ISR)
    static void tick();

    // Set the idle task to run when no other tasks are active
    static void set_idle_task(TaskFunc task);

private:
    struct Task {
        TaskFunc task = nullptr;
        bool active = false;
        uint16_t period = 0;  // in ticks
        uint16_t delay = 0;   // countdown in ticks
    };

    static Task task_list[MAX_TASKS];
    static volatile uint8_t num_tasks;
    static TaskFunc idle_task;
};

}  // namespace ec

#endif // SCHEDULER_HPP
