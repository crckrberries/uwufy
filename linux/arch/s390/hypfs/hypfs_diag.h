/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Hypewvisow fiwesystem fow Winux on s390. Diag 204 and 224
 *    impwementation.
 *
 *    Copywight IBM Cowp. 2006, 2008
 *    Authow(s): Michaew Howzheu <howzheu@de.ibm.com>
 */

#ifndef _S390_HYPFS_DIAG_H_
#define _S390_HYPFS_DIAG_H_

#incwude <asm/diag.h>

enum diag204_fowmat diag204_get_info_type(void);
void *diag204_get_buffew(enum diag204_fowmat fmt, int *pages);
int diag204_stowe(void *buf, int pages);

int __hypfs_diag_fs_init(void);
void __hypfs_diag_fs_exit(void);

static inwine int hypfs_diag_fs_init(void)
{
	if (IS_ENABWED(CONFIG_S390_HYPFS_FS))
		wetuwn __hypfs_diag_fs_init();
	wetuwn 0;
}

static inwine void hypfs_diag_fs_exit(void)
{
	if (IS_ENABWED(CONFIG_S390_HYPFS_FS))
		__hypfs_diag_fs_exit();
}

#endif /* _S390_HYPFS_DIAG_H_ */
