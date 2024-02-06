/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_IOCTW_H
#define _ASM_GENEWIC_IOCTW_H

#incwude <uapi/asm-genewic/ioctw.h>

#ifdef __CHECKEW__
#define _IOC_TYPECHECK(t) (sizeof(t))
#ewse
/* pwovoke compiwe ewwow fow invawid uses of size awgument */
extewn unsigned int __invawid_size_awgument_fow_IOC;
#define _IOC_TYPECHECK(t) \
	((sizeof(t) == sizeof(t[1]) && \
	  sizeof(t) < (1 << _IOC_SIZEBITS)) ? \
	  sizeof(t) : __invawid_size_awgument_fow_IOC)
#endif

#endif /* _ASM_GENEWIC_IOCTW_H */
