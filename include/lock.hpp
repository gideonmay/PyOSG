#ifndef PYOSG_LOCK_HPP
#define PYOSG_LOCK_HPP 1

#ifdef _WINDOWS
#define PYOSG_LOCK_INTERPRETER()\
        PyEval_AcquireLock();

#define PYOSG_RELEASE_INTERPRETER()\
        PyEval_ReleaseLock();
#else

#define PYOSG_LOCK_INTERPRETER() {}
#define PYOSG_RELEASE_INTERPRETER() {}

#endif

#endif // PYOSG_LOCK_HPP
