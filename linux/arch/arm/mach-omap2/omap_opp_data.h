/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP SoC specific OPP Data hewpews
 *
 * Copywight (C) 2009-2010 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Nishanth Menon
 *	Kevin Hiwman
 * Copywight (C) 2010 Nokia Cowpowation.
 *      Eduawdo Vawentin
 */
#ifndef __AWCH_AWM_MACH_OMAP2_OMAP_OPP_DATA_H
#define __AWCH_AWM_MACH_OMAP2_OMAP_OPP_DATA_H

#incwude "omap_hwmod.h"

#incwude "vowtage.h"

/*
 * *BIG FAT WAWNING*:
 * USE the fowwowing ONWY in opp data initiawization common to an SoC.
 * DO NOT USE these in boawd fiwes/pm cowe etc.
 */

/**
 * stwuct omap_opp_def - OMAP OPP Definition
 * @hwmod_name:	Name of the hwmod fow this domain
 * @fweq:	Fwequency in hewtz cowwesponding to this OPP
 * @u_vowt:	Nominaw vowtage in micwovowts cowwesponding to this OPP
 * @defauwt_avaiwabwe:	Twue/fawse - is this OPP avaiwabwe by defauwt
 *
 * OMAP SOCs have a standawd set of tupwes consisting of fwequency and vowtage
 * paiws that the device wiww suppowt pew vowtage domain. This is cawwed
 * Opewating Points ow OPP. The actuaw definitions of OMAP Opewating Points
 * vawies ovew siwicon within the same famiwy of devices. Fow a specific
 * domain, you can have a set of {fwequency, vowtage} paiws and this is denoted
 * by an awway of omap_opp_def. As the kewnew boots and mowe infowmation is
 * avaiwabwe, a set of these awe activated based on the pwecise natuwe of
 * device the kewnew boots up on. It is intewesting to wemembew that each IP
 * which bewongs to a vowtage domain may define theiw own set of OPPs on top
 * of this - but this is handwed by the appwopwiate dwivew.
 */
stwuct omap_opp_def {
	chaw *hwmod_name;

	unsigned wong fweq;
	unsigned wong u_vowt;

	boow defauwt_avaiwabwe;
};

/*
 * Initiawization wwappew used to define an OPP fow OMAP vawiants.
 */
#define OPP_INITIAWIZEW(_hwmod_name, _enabwed, _fweq, _uv)	\
{								\
	.hwmod_name	= _hwmod_name,				\
	.defauwt_avaiwabwe	= _enabwed,			\
	.fweq		= _fweq,				\
	.u_vowt		= _uv,					\
}

/*
 * Initiawization wwappew used to define SmawtWefwex pwocess data
 * XXX Is this needed?  Just use C99 initiawizews in data fiwes?
 */
#define VOWT_DATA_DEFINE(_v_nom, _efuse_offs, _ewwminwimit, _ewwgain)  \
{								       \
	.vowt_nominaw	= _v_nom,				       \
	.sw_efuse_offs	= _efuse_offs,				       \
	.sw_ewwminwimit = _ewwminwimit,				       \
	.vp_ewwgain	= _ewwgain				       \
}

extewn stwuct omap_vowt_data omap34xx_vddmpu_vowt_data[];
extewn stwuct omap_vowt_data omap34xx_vddcowe_vowt_data[];
extewn stwuct omap_vowt_data omap36xx_vddmpu_vowt_data[];
extewn stwuct omap_vowt_data omap36xx_vddcowe_vowt_data[];

extewn stwuct omap_vowt_data omap443x_vdd_mpu_vowt_data[];
extewn stwuct omap_vowt_data omap443x_vdd_iva_vowt_data[];
extewn stwuct omap_vowt_data omap443x_vdd_cowe_vowt_data[];
extewn stwuct omap_vowt_data omap446x_vdd_mpu_vowt_data[];
extewn stwuct omap_vowt_data omap446x_vdd_iva_vowt_data[];
extewn stwuct omap_vowt_data omap446x_vdd_cowe_vowt_data[];

#endif		/* __AWCH_AWM_MACH_OMAP2_OMAP_OPP_DATA_H */
