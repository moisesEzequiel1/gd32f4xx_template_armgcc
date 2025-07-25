#include "bsp.h"
#include "system_gd32f4xx.h"
#include "scheduler.hpp"

namespace ec {

Scheduler::Task Scheduler::task_list[MAX_TASKS] = {};
volatile uint8_t Scheduler::num_tasks = 0U;
TaskFunc Scheduler::idle_task = nullptr;

void Scheduler::init() {
    for (uint8_t i = 0; i < MAX_TASKS; ++i) {
        task_list[i] = {};
    }
    SystemCoreClockUpdate();
    uint32_t tick_reload = SystemCoreClock / (1000000U / TICK_US);

    // Asegurar que no se exceda el límite de 24 bits del SysTick
    if (tick_reload > SysTick_LOAD_RELOAD_Msk) {
        while (1); // Error: valor demasiado grande
    }

    if (SysTick_Config(tick_reload) != 0) {
        while (1); // Error al configurar SysTick
    }
}

bool Scheduler::add_task(TaskFunc task, uint32_t period_us) {
    if (num_tasks >= MAX_TASKS || task == nullptr)
        return false;

    uint32_t ticks = period_us / TICK_US;
    if (ticks == 0) ticks = 1;

    task_list[num_tasks].task = task;
    task_list[num_tasks].active = true;
    task_list[num_tasks].period = static_cast<uint16_t>(ticks);
    task_list[num_tasks].delay = static_cast<uint16_t>(ticks);

    ++num_tasks;
    return true;
}

void Scheduler::start() {
    while (true) {
        bool did_run_task = false;

        for (uint8_t i = 0; i < num_tasks; ++i) {
            Task &t = task_list[i];
            if (t.active && t.task && (t.delay == 0)) {
                t.task();
                t.delay = t.period;
                did_run_task = true;
            }
        }

        if (!did_run_task && idle_task) {
            idle_task();
        }
    }
}

void Scheduler::tick() {
    for (uint8_t i = 0; i < num_tasks; ++i) {
        if (task_list[i].delay > 0) {
            --task_list[i].delay;
        }
    }
}

void Scheduler::set_idle_task(TaskFunc task) {
    idle_task = task;
}

}  // namespace ec

extern "C" void SysTick_Handler(void) {
    ec::Scheduler::tick();
}
