// Copyright (C) 2016 Gideon May (gideon@borges.xyz)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.

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
