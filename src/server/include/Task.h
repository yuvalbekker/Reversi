class Task {
public:
    /**
     * The c'tor of the class.
     * @param func
     * @param arg
     */
    Task(void *(*func)(void *arg), void *arg) :
            func(func), arg(arg) {}

    /**
     * Executes the generic funtion of the task.
     */
    void execute() {
        func(arg);
    }

    /**
     * The d'tor of the class.
     */
    virtual ~Task() {}

private:
    void *(*func)(void *arg);

    void *arg;
};
