/**
 * @file TaskManager.h
 * @brief FreeRTOS task initialization and lifecycle manager.
 */

#pragma once

/**
 * @brief Manager responsible for spawning all application FreeRTOS tasks pinned to CPU cores.
 */
class TaskManager
{
public:
    /**
     * @brief Create and pin all FreeRTOS tasks to their designated CPU cores.
     *
     * @return true All tasks were created successfully.
     * @return false Task creation failed.
     */
    static bool createTasks();
};