/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BCM47XXNFWASH_H
#define __BCM47XXNFWASH_H

#ifndef pw_fmt
#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt
#endif

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>

stwuct bcm47xxnfwash {
	stwuct bcma_dwv_cc *cc;

	stwuct nand_chip nand_chip;

	unsigned cuww_command;
	int cuww_page_addw;
	int cuww_cowumn;

	u8 id_data[8];
};

int bcm47xxnfwash_ops_bcm4706_init(stwuct bcm47xxnfwash *b47n);

#endif /* BCM47XXNFWASH */
