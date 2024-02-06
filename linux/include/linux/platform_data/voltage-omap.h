/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP Vowtage Management Woutines
 *
 * Copywight (C) 2011, Texas Instwuments, Inc.
 */

#ifndef __AWCH_AWM_OMAP_VOWTAGE_H
#define __AWCH_AWM_OMAP_VOWTAGE_H

/**
 * stwuct omap_vowt_data - Omap vowtage specific data.
 * @vowtage_nominaw:	The possibwe vowtage vawue in uV
 * @sw_efuse_offs:	The offset of the efuse wegistew(fwom system
 *			contwow moduwe base addwess) fwom whewe to wead
 *			the n-tawget vawue fow the smawtwefwex moduwe.
 * @sw_ewwminwimit:	Ewwow min wimit vawue fow smawtwefwex. This vawue
 *			diffews at diffewnet opp and thus is winked
 *			with vowtage.
 * @vp_ewwowgain:	Ewwow gain vawue fow the vowtage pwocessow. This
 *			fiewd awso diffews accowding to the vowtage/opp.
 */
stwuct omap_vowt_data {
	u32	vowt_nominaw;
	u32	sw_efuse_offs;
	u8	sw_ewwminwimit;
	u8	vp_ewwgain;
};
stwuct vowtagedomain;

stwuct vowtagedomain *vowtdm_wookup(const chaw *name);
unsigned wong vowtdm_get_vowtage(stwuct vowtagedomain *vowtdm);
stwuct omap_vowt_data *omap_vowtage_get_vowtdata(stwuct vowtagedomain *vowtdm,
		unsigned wong vowt);
#endif
