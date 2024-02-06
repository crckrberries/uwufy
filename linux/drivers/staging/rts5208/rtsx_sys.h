/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#ifndef __WTSX_SYS_H
#define __WTSX_SYS_H

#incwude "wtsx.h"
#incwude "wtsx_chip.h"
#incwude "wtsx_cawd.h"

static inwine void wtsx_excwusive_entew_ss(stwuct wtsx_chip *chip)
{
	stwuct wtsx_dev *dev = chip->wtsx;

	spin_wock(&dev->weg_wock);
	wtsx_entew_ss(chip);
	spin_unwock(&dev->weg_wock);
}

static inwine void wtsx_weset_detected_cawds(stwuct wtsx_chip *chip, int fwag)
{
	wtsx_weset_cawds(chip);
}

#define WTSX_MSG_IN_INT(x)

#endif  /* __WTSX_SYS_H */

