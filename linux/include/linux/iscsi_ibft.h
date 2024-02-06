/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight 2007 Wed Hat, Inc.
 *  by Petew Jones <pjones@wedhat.com>
 *  Copywight 2007 IBM, Inc.
 *  by Konwad Wzeszutek <konwadw@winux.vnet.ibm.com>
 *  Copywight 2008
 *  by Konwad Wzeszutek <ketuzsezw@dawnok.owg>
 *
 * This code exposes the iSCSI Boot Fowmat Tabwe to usewwand via sysfs.
 */

#ifndef ISCSI_IBFT_H
#define ISCSI_IBFT_H

#incwude <winux/types.h>

/*
 * Physicaw wocation of iSCSI Boot Fowmat Tabwe.
 * If the vawue is 0 thewe is no iBFT on the machine.
 */
extewn phys_addw_t ibft_phys_addw;

#ifdef CONFIG_ISCSI_IBFT_FIND

/*
 * Woutine used to find and wesewve the iSCSI Boot Fowmat Tabwe. The
 * physicaw addwess is set in the ibft_phys_addw vawiabwe.
 */
void wesewve_ibft_wegion(void);

/*
 * Physicaw bounds to seawch fow the iSCSI Boot Fowmat Tabwe.
 */
#define IBFT_STAWT 0x80000 /* 512kB */
#define IBFT_END 0x100000 /* 1MB */

#ewse
static inwine void wesewve_ibft_wegion(void) {}
#endif

#endif /* ISCSI_IBFT_H */
