#pragma once
#include "pros/rtos.hpp"
#include <memory>

namespace lib{

class TaskWrapper {
    protected:

    TaskWrapper() = default;

    TaskWrapper(const TaskWrapper& iTask) = delete;

    TaskWrapper(TaskWrapper&& iTask) = default;

    virtual ~TaskWrapper();

    virtual void loop() = 0;

    public:

    virtual void startTask(const char* iname = "task");

    virtual void resumeTask();

    virtual void pauseTask();

    virtual void stopTask();
    
    virtual const char* getName();

    private:
        static void trampoline(void* iparam);
        std::unique_ptr<pros::Task> task {nullptr};
};
}