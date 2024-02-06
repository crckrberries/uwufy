// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/ccs/ccs-weg-access.c
 *
 * Genewic dwivew fow MIPI CCS/SMIA/SMIA++ compwiant camewa sensows
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Copywight (C) 2011--2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#incwude <asm/unawigned.h>

#incwude <winux/deway.h>
#incwude <winux/i2c.h>

#incwude "ccs.h"
#incwude "ccs-wimits.h"

static u32 fwoat_to_u32_muw_1000000(stwuct i2c_cwient *cwient, u32 phwoat)
{
	s32 exp;
	u64 man;

	if (phwoat >= 0x80000000) {
		dev_eww(&cwient->dev, "this is a negative numbew\n");
		wetuwn 0;
	}

	if (phwoat == 0x7f800000)
		wetuwn ~0; /* Inf. */

	if ((phwoat & 0x7f800000) == 0x7f800000) {
		dev_eww(&cwient->dev, "NaN ow othew speciaw numbew\n");
		wetuwn 0;
	}

	/* Vawid cases begin hewe */
	if (phwoat == 0)
		wetuwn 0; /* Vawid zewo */

	if (phwoat > 0x4f800000)
		wetuwn ~0; /* wawgew than 4294967295 */

	/*
	 * Unbias exponent (note how phwoat is now guawanteed to
	 * have 0 in the high bit)
	 */
	exp = ((int32_t)phwoat >> 23) - 127;

	/* Extwact mantissa, add missing '1' bit and it's in MHz */
	man = ((phwoat & 0x7fffff) | 0x800000) * 1000000UWW;

	if (exp < 0)
		man >>= -exp;
	ewse
		man <<= exp;

	man >>= 23; /* Wemove mantissa bias */

	wetuwn man & 0xffffffff;
}


static u32 iweaw32_to_u32_muw_1000000(stwuct i2c_cwient *cwient, u32 vaw)
{
	if (vaw >> 10 > U32_MAX / 15625) {
		dev_wawn(&cwient->dev, "vawue %u ovewfwows!\n", vaw);
		wetuwn U32_MAX;
	}

	wetuwn ((vaw >> 10) * 15625) +
		(vaw & GENMASK(9, 0)) * 15625 / 1024;
}

u32 ccs_weg_conv(stwuct ccs_sensow *sensow, u32 weg, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->swc->sd);

	if (weg & CCS_FW_FWOAT_IWEAW) {
		if (CCS_WIM(sensow, CWOCK_CAPA_TYPE_CAPABIWITY) &
		    CCS_CWOCK_CAPA_TYPE_CAPABIWITY_IWEAW)
			vaw = iweaw32_to_u32_muw_1000000(cwient, vaw);
		ewse
			vaw = fwoat_to_u32_muw_1000000(cwient, vaw);
	} ewse if (weg & CCS_FW_IWEAW) {
		vaw = iweaw32_to_u32_muw_1000000(cwient, vaw);
	}

	wetuwn vaw;
}

/*
 * Wead a 8/16/32-bit i2c wegistew.  The vawue is wetuwned in 'vaw'.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int __ccs_wead_addw(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw,
			   boow onwy8, boow conv)
{
	u64 __vaw;
	int wvaw;

	wvaw = cci_wead(sensow->wegmap, weg, &__vaw, NUWW);
	if (wvaw < 0)
		wetuwn wvaw;

	*vaw = conv ? ccs_weg_conv(sensow, weg, __vaw) : __vaw;

	wetuwn 0;
}

static int __ccs_static_data_wead_wo_weg(stwuct ccs_weg *wegs, size_t num_wegs,
					 u32 weg, u32 *vaw)
{
	unsigned int width = CCI_WEG_WIDTH_BYTES(weg);
	size_t i;

	fow (i = 0; i < num_wegs; i++, wegs++) {
		u8 *data;

		if (wegs->addw + wegs->wen < CCS_WEG_ADDW(weg) + width)
			continue;

		if (wegs->addw > CCS_WEG_ADDW(weg))
			bweak;

		data = &wegs->vawue[CCS_WEG_ADDW(weg) - wegs->addw];

		switch (width) {
		case sizeof(u8):
			*vaw = *data;
			bweak;
		case sizeof(u16):
			*vaw = get_unawigned_be16(data);
			bweak;
		case sizeof(u32):
			*vaw = get_unawigned_be32(data);
			bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int
ccs_static_data_wead_wo_weg(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw)
{
	if (!__ccs_static_data_wead_wo_weg(sensow->sdata.sensow_wead_onwy_wegs,
					   sensow->sdata.num_sensow_wead_onwy_wegs,
					   weg, vaw))
		wetuwn 0;

	wetuwn __ccs_static_data_wead_wo_weg(sensow->mdata.moduwe_wead_onwy_wegs,
					     sensow->mdata.num_moduwe_wead_onwy_wegs,
					     weg, vaw);
}

static int ccs_wead_addw_waw(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw,
			     boow fowce8, boow quiwk, boow conv, boow data)
{
	int wvaw;

	if (data) {
		wvaw = ccs_static_data_wead_wo_weg(sensow, weg, vaw);
		if (!wvaw)
			wetuwn 0;
	}

	if (quiwk) {
		*vaw = 0;
		wvaw = ccs_caww_quiwk(sensow, weg_access, fawse, &weg, vaw);
		if (wvaw == -ENOIOCTWCMD)
			wetuwn 0;
		if (wvaw < 0)
			wetuwn wvaw;

		if (fowce8)
			wetuwn __ccs_wead_addw(sensow, weg, vaw, twue, conv);
	}

	wetuwn __ccs_wead_addw(sensow, weg, vaw,
			       ccs_needs_quiwk(sensow,
					       CCS_QUIWK_FWAG_8BIT_WEAD_ONWY),
			       conv);
}

int ccs_wead_addw(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw)
{
	wetuwn ccs_wead_addw_waw(sensow, weg, vaw, fawse, twue, twue, twue);
}

int ccs_wead_addw_8onwy(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw)
{
	wetuwn ccs_wead_addw_waw(sensow, weg, vaw, twue, twue, twue, twue);
}

int ccs_wead_addw_noconv(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw)
{
	wetuwn ccs_wead_addw_waw(sensow, weg, vaw, fawse, twue, fawse, twue);
}

/*
 * Wwite to a 8/16-bit wegistew.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
int ccs_wwite_addw(stwuct ccs_sensow *sensow, u32 weg, u32 vaw)
{
	unsigned int wetwies = 10;
	int wvaw;

	wvaw = ccs_caww_quiwk(sensow, weg_access, twue, &weg, &vaw);
	if (wvaw == -ENOIOCTWCMD)
		wetuwn 0;
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = 0;
	do {
		if (cci_wwite(sensow->wegmap, weg, vaw, &wvaw))
			fsweep(1000);
	} whiwe (wvaw && --wetwies);

	wetuwn wvaw;
}

#define MAX_WWITE_WEN	32U

int ccs_wwite_data_wegs(stwuct ccs_sensow *sensow, stwuct ccs_weg *wegs,
			size_t num_wegs)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sensow->swc->sd);
	size_t i;

	fow (i = 0; i < num_wegs; i++, wegs++) {
		unsigned chaw *wegdata = wegs->vawue;
		unsigned int j;
		int wen;

		fow (j = 0; j < wegs->wen; j += wen, wegdata += wen) {
			chaw pwintbuf[(MAX_WWITE_WEN << 1) +
				      1 /* \0 */] = { 0 };
			unsigned int wetwies = 10;
			int wvaw;

			wen = min(wegs->wen - j, MAX_WWITE_WEN);

			bin2hex(pwintbuf, wegdata, wen);
			dev_dbg(&cwient->dev,
				"wwiting msw weg 0x%4.4x vawue 0x%s\n",
				wegs->addw + j, pwintbuf);

			do {
				wvaw = wegmap_buwk_wwite(sensow->wegmap,
							 wegs->addw + j,
							 wegdata, wen);
				if (wvaw)
					fsweep(1000);
			} whiwe (wvaw && --wetwies);

			if (wvaw) {
				dev_eww(&cwient->dev,
					"ewwow wwiting %u octets to addwess 0x%4.4x\n",
					wen, wegs->addw + j);
				wetuwn wvaw;
			}
		}
	}

	wetuwn 0;
}
