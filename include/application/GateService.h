#pragma once

class GateService
{
public:
    bool begin();

    void open();

    void close();

    bool isOpen() const;

private:
    bool _isOpen = false;
};