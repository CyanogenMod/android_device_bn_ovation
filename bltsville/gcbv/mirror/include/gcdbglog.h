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

#ifndef GCDBGLOG_H
#define GCDBGLOG_H

#include "gclist.h"
#include <bltsville.h>
struct gcmmucontext;


/*******************************************************************************
 * Debug logging switches.
 */

/* Enables internal gccore logging backend. */
#if !defined(GCDEBUG_ENABLE)
#define GCDEBUG_ENABLE 0	/* Enabled for development branch only. */
#endif

/* Enables linux builtin logging backend. */
#if !defined(GCDEBUG_LINUXLOGS)
#define GCDEBUG_LINUXLOGS 0
#endif

#if GCDEBUG_ENABLE && GCDEBUG_LINUXLOGS
#error GCDEBUG_ENABLE and GCDEBUG_LINUXLOGS cannot be enabled simultaneously.
#endif


/*******************************************************************************
 * Dumping interface macro for release mode.
 */

#if !GCDEBUG_ENABLE && !GCDEBUG_LINUXLOGS
#define GCDBG_INIT(...)
#define GCDBG_EXIT(...)
#define GCDBG_FILTERDEF(...)
#define GCDBG_REGISTER(...)
#define GCENTER(...)
#define GCEXIT(...)
#define GCENTERARG(...)
#define GCEXITARG(...)
#define GCDBG(...) {}
#define GCERR(...) {}
#define GCDUMPSTRING(...) {}
#define GCDUMPBUFFER(...) {}
#define GCDUMPARENA(...) {}
#define GCDUMPARENAS(...) {}
#define GCGPUSTATUS(...) {}
#endif

#if !GCDEBUG_ENABLE
#define GCDBG_REPORT_MISSING() \
	printf("gcx logging is not integrated.\n")

#define GCDBG_SHOWENABLED(s) \
	GCDBG_REPORT_MISSING()

#define GCDBG_ENABLEDUMP() \
	GCDBG_REPORT_MISSING()

#define GCDBG_DISABLEDUMP() \
	GCDBG_REPORT_MISSING()

#define GCDBG_SETFILTER(filtername, zone) \
	GCDBG_REPORT_MISSING()

#define GCDBG_FLUSHDUMP(s) \
	GCDBG_REPORT_MISSING()

#define GCDBG_RESETDUMP() \
	GCDBG_REPORT_MISSING()

#endif


/*******************************************************************************
 * Dumping macros not specific to a particular logging backend.
 */

#if GCDEBUG_ENABLE || GCDEBUG_LINUXLOGS

#define GC_MOD_PREFIX \
	GC_DEV_NAME ": %s(%d) "

#define GCDUMPARENA(zone, text, arena) \
do { \
	GCDBG(zone, text " @ 0x%08X:\n", (unsigned int) arena); \
	GCDBG(zone, "  number of pages = %u\n", \
		(arena)->count); \
	GCDBG(zone, "  from (absolute/mtlb/stlb) = 0x%08X / %u / %u\n", \
		(arena)->start.absolute, \
		(arena)->start.loc.mtlb, \
		(arena)->start.loc.stlb); \
	GCDBG(zone, "  to   (absolute/mtlb/stlb) = 0x%08X / %u / %u\n", \
		(arena)->end.absolute, \
		(arena)->end.loc.mtlb, \
		(arena)->end.loc.stlb); \
} while (false)

#define GCDUMPARENAS(zone, text, arenahead) \
do { \
	GCDBG(zone, "%s:\n", text); \
	\
	if (list_empty(arenahead)) { \
		GCDBG(zone, "  no arenas defined in the list.\n"); \
	} else { \
		struct list_head *entry; \
		struct gcmmuarena *arena; \
		\
		list_for_each(entry, arenahead) { \
			arena = list_entry(entry, struct gcmmuarena, link); \
			GCDUMPARENA(zone, "arena", arena); \
		} \
	} \
} while (false)

#endif

#define GC_FUNC_ENTER "++"
#define GC_FUNC_EXIT "--"


/*******************************************************************************
 * Dumping macros for internal gccore logging backend.
 */

#if GCDEBUG_ENABLE

#define GCDBGFILTER \
	g_gcdbgfilter

#define GCDBG_INIT() \
	gcdbg_init()

#define GCDBG_EXIT() \
	gcdbg_exit()

#define GCDBG_FILTERDEF(name, initzone, ...) \
	static struct gcdbgfilter GCDBGFILTER = { \
		.link = LIST_HEAD_INIT(GCDBGFILTER.link), \
		.filtername = #name, \
		.zone = initzone, \
		.zonename = { __VA_ARGS__, NULL } \
	}; \
	\
	struct gcdbgfilter *name ## _dbgfilter(void) \
	{ \
		return &GCDBGFILTER; \
	}

#define GCDBG_REGISTER(name) \
do { \
	struct gcdbgfilter *name ## _dbgfilter(void); \
	gc_dbg_add_client(name ## _dbgfilter()); \
} while (0)

#define GCDBG_SHOWENABLED(s) \
	gc_dump_show_enabled(s)

#define GCDBG_ENABLEDUMP() \
	gc_dump_enable()

#define GCDBG_DISABLEDUMP() \
	gc_dump_disable()

#define GCDBG_SETFILTER(filtername, zone) \
	gc_dump_filter_enable(filtername, zone)

#define GCDBG_FLUSHDUMP(s) \
	gc_dump_flush(s)

#define GCDBG_RESETDUMP() \
	gc_dump_reset()

#define GCENTER(zone) \
	gc_dump_string(&GCDBGFILTER, zone, GC_FUNC_ENTER GC_MOD_PREFIX "\n", \
			__func__, __LINE__)

#define GCEXIT(zone) \
	gc_dump_string(&GCDBGFILTER, zone, GC_FUNC_EXIT GC_MOD_PREFIX "\n", \
			__func__, __LINE__)

#define GCENTERARG(zone, msg, ...) \
	gc_dump_string(&GCDBGFILTER, zone, GC_FUNC_ENTER GC_MOD_PREFIX msg, \
			__func__, __LINE__, ##__VA_ARGS__)

#define GCEXITARG(zone, msg, ...) \
	gc_dump_string(&GCDBGFILTER, zone, GC_FUNC_EXIT GC_MOD_PREFIX msg, \
			__func__, __LINE__, ##__VA_ARGS__)

#define GCDBG(zone, msg, ...) \
	gc_dump_string(&GCDBGFILTER, zone, GC_MOD_PREFIX msg,	\
			__func__, __LINE__, ##__VA_ARGS__)

#define GCERR(msg, ...) \
	gc_dump_string(NULL, 0, GC_MOD_PREFIX "[ERROR] " msg,	\
			__func__, __LINE__, ##__VA_ARGS__)

#define GCDUMPSTRING(msg, ...) \
	gc_dump_string(NULL, 0, msg, ##__VA_ARGS__)

#define GCDUMPBUFFER(zone, ptr, gpuaddr, datasize) \
	gc_dump_cmd_buffer(&GCDBGFILTER, zone, ptr, gpuaddr, datasize)

#endif


/*******************************************************************************
 * Dumping macros for linux builtin logging backend.
 */

#if GCDEBUG_LINUXLOGS

#define GCDBG_INIT()
#define GCDBG_EXIT()
#define GCDBG_FILTERDEF(...)
#define GCDBG_REGISTER(...)

#define GCENTER(zone) \
	GCDBG(zone, GC_FUNC_ENTER " %s(%d)\n", __func__, __LINE__)

#define GCEXIT(zone) \
	GCDBG(zone, GC_FUNC_EXIT " %s(%d)\n", __func__, __LINE__)

#define GCENTERARG(zone, msg, ...) \
	GCDBG(zone, GC_FUNC_ENTER " %s(%d) " msg "\n", \
	      __func__, __LINE__, ##__VA_ARGS__)

#define GCEXITARG(zone, msg, ...) \
	GCDBG(zone, GC_FUNC_EXIT " %s(%d) " msg "\n", \
	      __func__, __LINE__, ##__VA_ARGS__)

#define GCDBG(zone, msg, ...) \
	dev_dbg(gc_get_dev(), msg, ##__VA_ARGS__)

#define GCERR(msg, ...) \
	GCDBG(0, msg, ##__VA_ARGS__)

#define GCDUMPSTRING(msg, ...) \
	GCDBG(0, msg, ##__VA_ARGS__)

#define GCDUMPBUFFER(...) {}
#define GCGPUSTATUS(...) {}

#endif


/*******************************************************************************
 * Command buffer parser.
 */

struct gcsurfaceinfo {
	unsigned int width;
	unsigned int height;
	unsigned int address;
	unsigned int stride;
	unsigned int swizzle;
	unsigned int format;
	unsigned int bpp;
};

struct gcrect {
	int left;
	int top;
	int right;
	int bottom;
};

struct gcsourceinfo {
	struct gcsurfaceinfo surf;
	struct gcrect rect;
};

struct gcdestinfo {
	struct gcsurfaceinfo surf;
	unsigned int rectcount;
	struct gcrect rect[256];
};

struct gccommandinfo {
	unsigned int command;
	unsigned int srccount;
	struct gcsourceinfo src[4];
	struct gcdestinfo dst;
};

/* Parse the specified command buffer and fill in the structure. */
int gc_parse_command_buffer(unsigned int *buffer, unsigned int size,
			    struct gccommandinfo *info);


/*******************************************************************************
 * Filter structure.
 */

struct gcdbgfilter {
	struct list_head link;
	char *filtername;
	unsigned int zone;
	const char *zonename[];
};


/*******************************************************************************
 * Debug init/exit functions.
 */

void gcdbg_init(void);
void gcdbg_exit(void);


/*******************************************************************************
 * Dumping functions.
 */

/* String dumping. */
void gc_dump_string(struct gcdbgfilter *filter, unsigned int zone,
		    const char *message, ...);
void gc_dump_string_sized(struct gcdbgfilter *filter, unsigned int zone,
			  unsigned int argsize, const char *message, ...);

/* Dump command buffer. */
void gc_dump_cmd_buffer(struct gcdbgfilter *filter, unsigned int zone,
			void *ptr, unsigned int gpuaddr, unsigned int datasize);

/* Dump generic buffer. */
void gc_dump_buffer(struct gcdbgfilter *filter, unsigned int zone,
		    void *ptr, unsigned int gpuaddr, unsigned int datasize);


/*******************************************************************************
 * Bltsville debugging.
 */

char *gc_bvblend_name(enum bvblend blend);


/*******************************************************************************
 * Dumping control.
 */

struct seq_file;

struct device *gc_get_dev(void);
void gc_dump_show_enabled(struct seq_file *s);
void gc_dump_enable(void);
void gc_dump_disable(void);
void gc_dump_filter_enable(const char *filtername, int zone);
void gc_dump_flush(struct seq_file *s);
void gc_dump_reset(void);
void gc_dbg_add_client(struct gcdbgfilter *filter);

#endif
