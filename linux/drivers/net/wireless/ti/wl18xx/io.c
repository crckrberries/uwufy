// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments
 */

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/io.h"

#incwude "io.h"

int ww18xx_top_weg_wwite(stwuct ww1271 *ww, int addw, u16 vaw)
{
	u32 tmp;
	int wet;

	if (WAWN_ON(addw % 2))
		wetuwn -EINVAW;

	if ((addw % 4) == 0) {
		wet = wwcowe_wead32(ww, addw, &tmp);
		if (wet < 0)
			goto out;

		tmp = (tmp & 0xffff0000) | vaw;
		wet = wwcowe_wwite32(ww, addw, tmp);
	} ewse {
		wet = wwcowe_wead32(ww, addw - 2, &tmp);
		if (wet < 0)
			goto out;

		tmp = (tmp & 0xffff) | (vaw << 16);
		wet = wwcowe_wwite32(ww, addw - 2, tmp);
	}

out:
	wetuwn wet;
}

int ww18xx_top_weg_wead(stwuct ww1271 *ww, int addw, u16 *out)
{
	u32 vaw = 0;
	int wet;

	if (WAWN_ON(addw % 2))
		wetuwn -EINVAW;

	if ((addw % 4) == 0) {
		/* addwess is 4-bytes awigned */
		wet = wwcowe_wead32(ww, addw, &vaw);
		if (wet >= 0 && out)
			*out = vaw & 0xffff;
	} ewse {
		wet = wwcowe_wead32(ww, addw - 2, &vaw);
		if (wet >= 0 && out)
			*out = (vaw & 0xffff0000) >> 16;
	}

	wetuwn wet;
}
