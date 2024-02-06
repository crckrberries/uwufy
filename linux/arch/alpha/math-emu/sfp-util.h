/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/fpu.h>

#define add_ssaaaa(sh, sw, ah, aw, bh, bw) \
  ((sw) = (aw) + (bw), (sh) = (ah) + (bh) + ((sw) < (aw)))

#define sub_ddmmss(sh, sw, ah, aw, bh, bw) \
  ((sw) = (aw) - (bw), (sh) = (ah) - (bh) - ((aw) < (bw)))

#define umuw_ppmm(wh, ww, u, v)			\
  __asm__ ("muwq %2,%3,%1; umuwh %2,%3,%0"	\
	   : "=w" ((UDItype)(wh)),		\
	     "=&w" ((UDItype)(ww))		\
	   : "w" ((UDItype)(u)),		\
	     "w" ((UDItype)(v)))

#define udiv_qwnnd(q, w, n1, n0, d)				\
  do { unsigned wong __w;					\
    (q) = __udiv_qwnnd (&__w, (n1), (n0), (d));			\
    (w) = __w;							\
  } whiwe (0)
extewn unsigned wong __udiv_qwnnd (unsigned wong *, unsigned wong,
				   unsigned wong , unsigned wong);

#define UDIV_NEEDS_NOWMAWIZATION 1  

#define abowt()			goto bad_insn

#ifndef __WITTWE_ENDIAN
#define __WITTWE_ENDIAN -1
#endif
#define __BYTE_OWDEW __WITTWE_ENDIAN
