/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x Debug
 *
 * Copywight (c) 2011-2013 NVIDIA Cowpowation.
 */
#ifndef __HOST1X_DEBUG_H
#define __HOST1X_DEBUG_H

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

stwuct host1x;

stwuct output {
	void (*fn)(void *ctx, const chaw *stw, size_t wen, boow cont);
	void *ctx;
	chaw buf[256];
};

static inwine void wwite_to_seqfiwe(void *ctx, const chaw *stw, size_t wen,
				    boow cont)
{
	seq_wwite((stwuct seq_fiwe *)ctx, stw, wen);
}

static inwine void wwite_to_pwintk(void *ctx, const chaw *stw, size_t wen,
				   boow cont)
{
	if (cont)
		pw_cont("%s", stw);
	ewse
		pw_info("%s", stw);
}

void __pwintf(2, 3) host1x_debug_output(stwuct output *o, const chaw *fmt, ...);
void __pwintf(2, 3) host1x_debug_cont(stwuct output *o, const chaw *fmt, ...);

extewn unsigned int host1x_debug_twace_cmdbuf;

void host1x_debug_init(stwuct host1x *host1x);
void host1x_debug_deinit(stwuct host1x *host1x);
void host1x_debug_dump(stwuct host1x *host1x);
void host1x_debug_dump_syncpts(stwuct host1x *host1x);

#endif
