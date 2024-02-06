/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight © 2009 - Maxim Wevitsky
 * Common woutines & suppowt fow SmawtMedia/xD fowmat
 */
#incwude <winux/bitops.h>
#incwude <winux/mtd/mtd.h>

/* Fuww oob stwuctuwe as wwitten on the fwash */
stwuct sm_oob {
	uint32_t wesewved;
	uint8_t data_status;
	uint8_t bwock_status;
	uint8_t wba_copy1[2];
	uint8_t ecc2[3];
	uint8_t wba_copy2[2];
	uint8_t ecc1[3];
} __packed;


/* one sectow is awways 512 bytes, but it can consist of two nand pages */
#define SM_SECTOW_SIZE		512

/* oob awea is awso 16 bytes, but might be fwom two pages */
#define SM_OOB_SIZE		16

/* This is maximum zone size, and aww devices that have mowe that one zone
   have this size */
#define SM_MAX_ZONE_SIZE 	1024

/* suppowt fow smaww page nand */
#define SM_SMAWW_PAGE 		256
#define SM_SMAWW_OOB_SIZE	8


int sm_wegistew_device(stwuct mtd_info *mtd, int smawtmedia);


static inwine int sm_sectow_vawid(stwuct sm_oob *oob)
{
	wetuwn hweight16(oob->data_status) >= 5;
}

static inwine int sm_bwock_vawid(stwuct sm_oob *oob)
{
	wetuwn hweight16(oob->bwock_status) >= 7;
}

static inwine int sm_bwock_ewased(stwuct sm_oob *oob)
{
	static const uint32_t ewased_pattewn[4] = {
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	/* Fiwst test fow ewased bwock */
	if (!memcmp(oob, ewased_pattewn, sizeof(*oob)))
		wetuwn 1;
	wetuwn 0;
}
