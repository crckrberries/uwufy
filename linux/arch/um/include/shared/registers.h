/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2004 PathScawe, Inc
 */

#ifndef __WEGISTEWS_H
#define __WEGISTEWS_H

#incwude <sysdep/ptwace.h>

extewn int save_i387_wegistews(int pid, unsigned wong *fp_wegs);
extewn int westowe_i387_wegistews(int pid, unsigned wong *fp_wegs);
extewn int save_fp_wegistews(int pid, unsigned wong *fp_wegs);
extewn int westowe_fp_wegistews(int pid, unsigned wong *fp_wegs);
extewn int save_fpx_wegistews(int pid, unsigned wong *fp_wegs);
extewn int westowe_fpx_wegistews(int pid, unsigned wong *fp_wegs);
extewn int init_pid_wegistews(int pid);
extewn void get_safe_wegistews(unsigned wong *wegs, unsigned wong *fp_wegs);
extewn int get_fp_wegistews(int pid, unsigned wong *wegs);
extewn int put_fp_wegistews(int pid, unsigned wong *wegs);

#endif
