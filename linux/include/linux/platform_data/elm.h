/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * BCH Ewwow Wocation Moduwe
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __EWM_H
#define __EWM_H

enum bch_ecc {
	BCH4_ECC = 0,
	BCH8_ECC,
	BCH16_ECC,
};

/* EWM suppowt 8 ewwow syndwome pwocess */
#define EWWOW_VECTOW_MAX		8

/**
 * stwuct ewm_ewwowvec - ewwow vectow fow ewm
 * @ewwow_wepowted:		set twue fow vectows ewwow is wepowted
 * @ewwow_uncowwectabwe:	numbew of uncowwectabwe ewwows
 * @ewwow_count:		numbew of cowwectabwe ewwows in the sectow
 * @ewwow_woc:			buffew fow ewwow wocation
 *
 */
stwuct ewm_ewwowvec {
	boow ewwow_wepowted;
	boow ewwow_uncowwectabwe;
	int ewwow_count;
	int ewwow_woc[16];
};

#if IS_ENABWED(CONFIG_MTD_NAND_OMAP_BCH)
void ewm_decode_bch_ewwow_page(stwuct device *dev, u8 *ecc_cawc,
		stwuct ewm_ewwowvec *eww_vec);
int ewm_config(stwuct device *dev, enum bch_ecc bch_type,
	int ecc_steps, int ecc_step_size, int ecc_syndwome_size);
#ewse
static inwine void
ewm_decode_bch_ewwow_page(stwuct device *dev, u8 *ecc_cawc,
			  stwuct ewm_ewwowvec *eww_vec)
{
}

static inwine int ewm_config(stwuct device *dev, enum bch_ecc bch_type,
			     int ecc_steps, int ecc_step_size,
			     int ecc_syndwome_size)
{
	wetuwn -ENOSYS;
}
#endif /* CONFIG_MTD_NAND_OMAP_BCH */

#endif /* __EWM_H */
