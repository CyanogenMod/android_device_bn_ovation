/*
 * Copyright(c) 2012,
 * Texas Instruments, Inc. and Vivante Corporation.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Vivante Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GCX_H
#define GCX_H

#include <pthread.h>
#include "gcerror.h"
#include "gcreg.h"
#include "gcdbglog.h"

#ifndef countof
#define countof(a) \
( \
	sizeof(a) / sizeof(a[0]) \
)
#endif

#define GC_PTR2INT(p) \
( \
	(unsigned int) (p) \
)

#define GC_ALIGN(n, align) \
( \
	((n) + ((align) - 1)) & ~((align) - 1) \
)

#define GCLOCK_TIMEOUT_SEC 10
#define GCLOCK_TIMEOUT_JIF (msecs_to_jiffies(GCLOCK_TIMEOUT_SEC * 1000))

#define GCLOCK_TYPE \
	pthread_mutex_t

#define GCDEFINE_LOCK(name) \
	pthread_mutex_t name = PTHREAD_MUTEX_INITIALIZER

#define GCLOCK_INIT(lock) \
	if (pthread_mutex_init(lock, NULL)) { \
		GCERR("failed to init mutex.\n"); \
	}

#define GCLOCK_DESTROY(lock) \
	if (pthread_mutex_destroy(lock)) { \
		GCERR("failed to destroy mutex.\n"); \
	}

#define GCLOCK(lock) \
	if (pthread_mutex_lock(lock)) { \
		GCERR("failed to lock mutex.\n"); \
	}

#define GCUNLOCK(lock) \
	if (pthread_mutex_unlock(lock)) { \
		GCERR("failed to unlock mutex.\n"); \
	}

#endif
