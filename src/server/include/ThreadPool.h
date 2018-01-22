#include <queue>
#include <pthread.h>
#include "Task.h"

using namespace std;

class ThreadPool {
public:
    /**
     * The c'tor of the class.
     * @param threadsNum
     */
    ThreadPool(int threadsNum);

    /**
     * Adds the input task to the pool.
     * @param task
     */
    void addTask(Task *task);

    /**
     * Ends all the tasks in the pool.
     */
    void terminate();

    /**
     * The d'tor of the class.
     */
    virtual ~ThreadPool();

private:
    queue<Task *> tasksQueue;
    pthread_t *threads;

    void executeTasks();

    bool stopped;
    pthread_mutex_t lock;

    static void *execute(void *arg);
};