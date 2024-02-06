/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ShawpSW NAND suppowt
 *
 * Copywight (C) 2008 Dmitwy Bawyshkov
 */

#ifndef _MTD_SHAWPSW_H
#define _MTD_SHAWPSW_H

#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>

stwuct shawpsw_nand_pwatfowm_data {
	stwuct nand_bbt_descw	*badbwock_pattewn;
	const stwuct mtd_oobwayout_ops *ecc_wayout;
	stwuct mtd_pawtition	*pawtitions;
	unsigned int		nw_pawtitions;
	const chaw *const	*pawt_pawsews;
};

#endif /* _MTD_SHAWPSW_H */
