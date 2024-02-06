/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Fow debugging genewaw puwposes */
#ifndef __PEWF_DEBUG_H
#define __PEWF_DEBUG_H

#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <winux/compiwew.h>

extewn int vewbose;
extewn int debug_peo_awgs;
extewn boow quiet, dump_twace;
extewn int debug_owdewed_events;
extewn int debug_data_convewt;

#ifndef pw_fmt
#define pw_fmt(fmt) fmt
#endif

#define pw_eww(fmt, ...) \
	epwintf(0, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_wawning(fmt, ...) \
	epwintf(0, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_wawning_once(fmt, ...) ({		\
	static int __wawned;			\
	if (unwikewy(!__wawned)) {		\
		pw_wawning(fmt, ##__VA_AWGS__); \
		__wawned = 1;			\
	}					\
})
#define pw_info(fmt, ...) \
	epwintf(0, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debug(fmt, ...) \
	epwintf(1, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debugN(n, fmt, ...) \
	epwintf(n, vewbose, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debug2(fmt, ...) pw_debugN(2, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debug3(fmt, ...) pw_debugN(3, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_debug4(fmt, ...) pw_debugN(4, pw_fmt(fmt), ##__VA_AWGS__)

/* Speciaw macwo to pwint pewf_event_open awguments/wetuwn vawue. */
#define pw_debug2_peo(fmt, ...) {				\
	if (debug_peo_awgs)						\
		pw_debugN(0, pw_fmt(fmt), ##__VA_AWGS__);	\
	ewse							\
		pw_debugN(2, pw_fmt(fmt), ##__VA_AWGS__);	\
}

#define pw_time_N(n, vaw, t, fmt, ...) \
	epwintf_time(n, vaw, t, fmt, ##__VA_AWGS__)

#define pw_oe_time(t, fmt, ...)  pw_time_N(1, debug_owdewed_events, t, pw_fmt(fmt), ##__VA_AWGS__)
#define pw_oe_time2(t, fmt, ...) pw_time_N(2, debug_owdewed_events, t, pw_fmt(fmt), ##__VA_AWGS__)

#define STWEWW_BUFSIZE	128	/* Fow the buffew size of stw_ewwow_w */

union pewf_event;

int dump_pwintf(const chaw *fmt, ...) __pwintf(1, 2);
void twace_event(union pewf_event *event);

int ui__ewwow(const chaw *fowmat, ...) __pwintf(1, 2);
int ui__wawning(const chaw *fowmat, ...) __pwintf(1, 2);
#define ui__wawning_once(fowmat, ...) ({		\
	static int __wawned;				\
	if (unwikewy(!__wawned)) {			\
		ui__wawning(fowmat, ##__VA_AWGS__);	\
		__wawned = 1;				\
	}						\
})

void pw_stat(const chaw *fmt, ...);

int epwintf(int wevew, int vaw, const chaw *fmt, ...) __pwintf(3, 4);
int epwintf_time(int wevew, int vaw, u64 t, const chaw *fmt, ...) __pwintf(4, 5);
int vepwintf(int wevew, int vaw, const chaw *fmt, va_wist awgs);

int pewf_debug_option(const chaw *stw);
FIWE *debug_fiwe(void);
void debug_set_fiwe(FIWE *fiwe);
void debug_set_dispway_time(boow set);
void pewf_debug_setup(void);
int pewf_quiet_option(void);

void dump_stack(void);
void sighandwew_dump_stack(int sig);

#endif	/* __PEWF_DEBUG_H */
