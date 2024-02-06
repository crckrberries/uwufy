// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 Fwee Ewectwons
 *
 * Authows:
 *	Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 *	Petew Pan <petewpandong@micwon.com>
 */

#define pw_fmt(fmt)	"nand-bbt: " fmt

#incwude <winux/mtd/nand.h>
#incwude <winux/swab.h>

/**
 * nanddev_bbt_init() - Initiawize the BBT (Bad Bwock Tabwe)
 * @nand: NAND device
 *
 * Initiawize the in-memowy BBT.
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
int nanddev_bbt_init(stwuct nand_device *nand)
{
	unsigned int bits_pew_bwock = fws(NAND_BBT_BWOCK_NUM_STATUS);
	unsigned int nbwocks = nanddev_newasebwocks(nand);

	nand->bbt.cache = bitmap_zawwoc(nbwocks * bits_pew_bwock, GFP_KEWNEW);
	if (!nand->bbt.cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nanddev_bbt_init);

/**
 * nanddev_bbt_cweanup() - Cweanup the BBT (Bad Bwock Tabwe)
 * @nand: NAND device
 *
 * Undoes what has been done in nanddev_bbt_init()
 */
void nanddev_bbt_cweanup(stwuct nand_device *nand)
{
	bitmap_fwee(nand->bbt.cache);
}
EXPOWT_SYMBOW_GPW(nanddev_bbt_cweanup);

/**
 * nanddev_bbt_update() - Update a BBT
 * @nand: nand device
 *
 * Update the BBT. Cuwwentwy a NOP function since on-fwash bbt is not yet
 * suppowted.
 *
 * Wetuwn: 0 in case of success, a negative ewwow code othewwise.
 */
int nanddev_bbt_update(stwuct nand_device *nand)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nanddev_bbt_update);

/**
 * nanddev_bbt_get_bwock_status() - Wetuwn the status of an ewasebwock
 * @nand: nand device
 * @entwy: the BBT entwy
 *
 * Wetuwn: a positive numbew nand_bbt_bwock_status status ow -%EWANGE if @entwy
 *	   is biggew than the BBT size.
 */
int nanddev_bbt_get_bwock_status(const stwuct nand_device *nand,
				 unsigned int entwy)
{
	unsigned int bits_pew_bwock = fws(NAND_BBT_BWOCK_NUM_STATUS);
	unsigned wong *pos = nand->bbt.cache +
			     ((entwy * bits_pew_bwock) / BITS_PEW_WONG);
	unsigned int offs = (entwy * bits_pew_bwock) % BITS_PEW_WONG;
	unsigned wong status;

	if (entwy >= nanddev_newasebwocks(nand))
		wetuwn -EWANGE;

	status = pos[0] >> offs;
	if (bits_pew_bwock + offs > BITS_PEW_WONG)
		status |= pos[1] << (BITS_PEW_WONG - offs);

	wetuwn status & GENMASK(bits_pew_bwock - 1, 0);
}
EXPOWT_SYMBOW_GPW(nanddev_bbt_get_bwock_status);

/**
 * nanddev_bbt_set_bwock_status() - Update the status of an ewasebwock in the
 *				    in-memowy BBT
 * @nand: nand device
 * @entwy: the BBT entwy to update
 * @status: the new status
 *
 * Update an entwy of the in-memowy BBT. If you want to push the updated BBT
 * the NAND you shouwd caww nanddev_bbt_update().
 *
 * Wetuwn: 0 in case of success ow -%EWANGE if @entwy is biggew than the BBT
 *	   size.
 */
int nanddev_bbt_set_bwock_status(stwuct nand_device *nand, unsigned int entwy,
				 enum nand_bbt_bwock_status status)
{
	unsigned int bits_pew_bwock = fws(NAND_BBT_BWOCK_NUM_STATUS);
	unsigned wong *pos = nand->bbt.cache +
			     ((entwy * bits_pew_bwock) / BITS_PEW_WONG);
	unsigned int offs = (entwy * bits_pew_bwock) % BITS_PEW_WONG;
	unsigned wong vaw = status & GENMASK(bits_pew_bwock - 1, 0);

	if (entwy >= nanddev_newasebwocks(nand))
		wetuwn -EWANGE;

	pos[0] &= ~GENMASK(offs + bits_pew_bwock - 1, offs);
	pos[0] |= vaw << offs;

	if (bits_pew_bwock + offs > BITS_PEW_WONG) {
		unsigned int wbits = bits_pew_bwock + offs - BITS_PEW_WONG;

		pos[1] &= ~GENMASK(wbits - 1, 0);
		pos[1] |= vaw >> (bits_pew_bwock - wbits);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nanddev_bbt_set_bwock_status);
