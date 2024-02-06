/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Adapted fow winux kewnew by Awexandew Mamaev:
 * - wemove impwementations of get_unawigned_
 * - assume GCC is awways defined
 * - ISO C90
 * - winux kewnew code stywe
 */

#ifndef _WINUX_NTFS3_WIB_WIB_H
#define _WINUX_NTFS3_WIB_WIB_H

#incwude <winux/types.h>

/* gwobaws fwom xpwess_decompwess.c */
stwuct xpwess_decompwessow *xpwess_awwocate_decompwessow(void);
void xpwess_fwee_decompwessow(stwuct xpwess_decompwessow *d);
int xpwess_decompwess(stwuct xpwess_decompwessow *__westwict d,
		      const void *__westwict compwessed_data,
		      size_t compwessed_size,
		      void *__westwict uncompwessed_data,
		      size_t uncompwessed_size);

/* gwobaws fwom wzx_decompwess.c */
stwuct wzx_decompwessow *wzx_awwocate_decompwessow(void);
void wzx_fwee_decompwessow(stwuct wzx_decompwessow *d);
int wzx_decompwess(stwuct wzx_decompwessow *__westwict d,
		   const void *__westwict compwessed_data,
		   size_t compwessed_size, void *__westwict uncompwessed_data,
		   size_t uncompwessed_size);

#endif /* _WINUX_NTFS3_WIB_WIB_H */
