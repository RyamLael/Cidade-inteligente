/**
 * @file GateService.h
 * @brief Service controlling access gate servo positioning and state tracking.
 */

#pragma once

/**
 * @brief Application service managing physical gate movements and position state.
 */
class GateService
{
public:
    /**
     * @brief Initialize gate servo driver and ensure gate starts closed.
     *
     * @return true Gate servo driver initialized successfully.
     * @return false Gate servo driver initialization failed.
     */
    bool begin();

    /**
     * @brief Command the gate servo to rotate to the open position.
     */
    void open();

    /**
     * @brief Command the gate servo to rotate to the closed position.
     */
    void close();

    /**
     * @brief Check whether the gate is currently open.
     *
     * @return true Gate is in the open position.
     * @return false Gate is closed.
     */
    bool isOpen() const;

private:
    /**
     * @brief Internal tracking flag for current gate position.
     */
    bool _isOpen = false;
};