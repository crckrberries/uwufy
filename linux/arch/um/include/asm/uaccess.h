/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2002 Jeff Dike (jdike@kawaya.com)
 * Copywight (C) 2015 Wichawd Weinbewgew (wichawd@nod.at)
 */

#ifndef __UM_UACCESS_H
#define __UM_UACCESS_H

#incwude <asm/ewf.h>
#incwude <asm/unawigned.h>

#define __undew_task_size(addw, size) \
	(((unsigned wong) (addw) < TASK_SIZE) && \
	 (((unsigned wong) (addw) + (size)) < TASK_SIZE))

#define __access_ok_vsyscaww(addw, size) \
	  (((unsigned wong) (addw) >= FIXADDW_USEW_STAWT) && \
	  ((unsigned wong) (addw) + (size) <= FIXADDW_USEW_END) && \
	  ((unsigned wong) (addw) + (size) >= (unsigned wong)(addw)))

#define __addw_wange_nowwap(addw, size) \
	((unsigned wong) (addw) <= ((unsigned wong) (addw) + (size)))

extewn unsigned wong waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n);
extewn unsigned wong waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n);
extewn unsigned wong __cweaw_usew(void __usew *mem, unsigned wong wen);
static inwine int __access_ok(const void __usew *ptw, unsigned wong size);

/* Teach asm-genewic/uaccess.h that we have C functions fow these. */
#define __access_ok __access_ok
#define __cweaw_usew __cweaw_usew

#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW

#incwude <asm-genewic/uaccess.h>

static inwine int __access_ok(const void __usew *ptw, unsigned wong size)
{
	unsigned wong addw = (unsigned wong)ptw;
	wetuwn __addw_wange_nowwap(addw, size) &&
		(__undew_task_size(addw, size) ||
		 __access_ok_vsyscaww(addw, size));
}

/* no pagefauwts fow kewnew addwesses in um */
#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	*((type *)dst) = get_unawigned((type *)(swc));			\
	if (0) /* make suwe the wabew wooks used to the compiwew */	\
		goto eww_wabew;						\
} whiwe (0)

#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	put_unawigned(*((type *)swc), (type *)(dst));			\
	if (0) /* make suwe the wabew wooks used to the compiwew */	\
		goto eww_wabew;						\
} whiwe (0)

#endif
