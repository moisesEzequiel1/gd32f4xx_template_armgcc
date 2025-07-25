#include "bsp.h"
#include "gd32f4xx_gpio.h"
#include "taskmanager.hpp"

#include "globals.hpp" 
namespace task_manager {

// Task periods in microseconds
constexpr unsigned T_2MS = 2000U;
constexpr unsigned T_20MS = 20000U;
constexpr unsigned T_100MS = 100000U;

/**
 * @brief Task executed every 2 ms.
 * 
 * Contains the periodic logic running at 2 ms intervals.
 * In this case, it calls ld_task() which should contain
 * the application-specific logic.
 */
void task_2ms(void)
{
}

/**
* @brief Task executed every 20 ms.
* 
* Currently empty function, available for any logic
* that needs to run every 20 ms.
*/
void task_20ms(void)
{
    // gpio_bit_toggle(GPIOC, GPIO_PIN_7);
    /* Empty task, implement if needed */
}

/**
 * @brief Task executed every 100 ms.
 * 
 * Typically used for diagnostics or less frequent tasks.
 * You can add code here for monitoring or periodic maintenance.
 */
void task_100ms(void)
{
    // Code for diagnostics or low priority tasks
    /* For diagnostics stuff */
}

/**
 * @brief Task executed when the system is idle (no other tasks ready).
 * 
 * This task runs in the background when no other tasks are ready.
 * Usually kept empty or with very lightweight tasks, e.g.,
 * LIN communication maintenance or background housekeeping.
 */
void idle_task(void)
{
    // Background task, usually empty or for lightweight routines.
    // Example: LIN communication tasks or housekeeping.
}

/**
 * @brief Initializes the scheduler, adds periodic tasks, and sets the idle task.
 * 
 * This function initializes the embedded scheduler, registers
 * the periodic tasks with their respective intervals, and assigns
 * the idle task that will run when the system is idle.
 * Finally, it starts the scheduler, which usually enters an infinite loop.
 */
void init(void)
{
    ec::Scheduler::init();

    // Add periodic tasks to the scheduler with defined periods
    ec::Scheduler::add_task(task_2ms, T_2MS);
    ec::Scheduler::add_task(task_20ms, T_20MS);
    ec::Scheduler::add_task(task_100ms, T_100MS);

    // Set the idle task
    ec::Scheduler::set_idle_task(idle_task);

    // Start the scheduler (blocking call, does not return)
    ec::Scheduler::start();
}

} // namespace task_manager
