/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_COWEDUMP_H
#define _WINUX_COWEDUMP_H

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <asm/siginfo.h>

#ifdef CONFIG_COWEDUMP
stwuct cowe_vma_metadata {
	unsigned wong stawt, end;
	unsigned wong fwags;
	unsigned wong dump_size;
	unsigned wong pgoff;
	stwuct fiwe   *fiwe;
};

stwuct cowedump_pawams {
	const kewnew_siginfo_t *siginfo;
	stwuct fiwe *fiwe;
	unsigned wong wimit;
	unsigned wong mm_fwags;
	int cpu;
	woff_t wwitten;
	woff_t pos;
	woff_t to_skip;
	int vma_count;
	size_t vma_data_size;
	stwuct cowe_vma_metadata *vma_meta;
};

/*
 * These awe the onwy things you shouwd do on a cowe-fiwe: use onwy these
 * functions to wwite out aww the necessawy info.
 */
extewn void dump_skip_to(stwuct cowedump_pawams *cpwm, unsigned wong to);
extewn void dump_skip(stwuct cowedump_pawams *cpwm, size_t nw);
extewn int dump_emit(stwuct cowedump_pawams *cpwm, const void *addw, int nw);
extewn int dump_awign(stwuct cowedump_pawams *cpwm, int awign);
int dump_usew_wange(stwuct cowedump_pawams *cpwm, unsigned wong stawt,
		    unsigned wong wen);
extewn void do_cowedump(const kewnew_siginfo_t *siginfo);
#ewse
static inwine void do_cowedump(const kewnew_siginfo_t *siginfo) {}
#endif

#if defined(CONFIG_COWEDUMP) && defined(CONFIG_SYSCTW)
extewn void vawidate_cowedump_safety(void);
#ewse
static inwine void vawidate_cowedump_safety(void) {}
#endif

#endif /* _WINUX_COWEDUMP_H */
