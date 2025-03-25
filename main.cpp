#include <iostream>
#include <thread>
#include <semaphore>

namespace app {

typedef struct Context {
    std::counting_semaphore<> mutexSemaphore;
    std::counting_semaphore<> coutMutexSemaphore;
    
    Context() :
        mutexSemaphore(std::counting_semaphore<>(1)),
        coutMutexSemaphore(std::counting_semaphore<>(1)) {
    }
    
} Context;

static void task(std::string taskId, app::Context* pContext);
static void enterTask(std::string taskId, app::Context* pContext);
static void exitTask(std::string taskId, app::Context* pContext);
}

int main() {
    app::Context ctx;

    std::thread threads[] = {
        std::thread(app::task, "1", &ctx),
        std::thread(app::task, "2", &ctx),
        std::thread(app::task, "3", &ctx),
        std::thread(app::task, "4", &ctx)
    };

    for (std::thread& t : threads) {
        t.join();
    }

    return 0;
}

static void app::task(std::string taskId, app::Context* pContext) {
    pContext->mutexSemaphore.acquire();
    app::enterTask(taskId, pContext);
    app::exitTask(taskId, pContext);
    pContext->mutexSemaphore.release();
}

static void app::enterTask(std::string taskId, app::Context* pContext) {
    std::thread::id threadId = std::this_thread::get_id();
    pContext->coutMutexSemaphore.acquire();
    std::cout << "Task(" << taskId << ") Thread(" << threadId << ") entering the task." << std::endl;
    pContext->coutMutexSemaphore.release();
}

static void app::exitTask(std::string taskId, app::Context* pContext) {
    std::thread::id threadId = std::this_thread::get_id();
    pContext->coutMutexSemaphore.acquire();
    std::cout << "Task(" << taskId << ") Thread(" << threadId << ") exiting the task." << std::endl;
    pContext->coutMutexSemaphore.release();
}
