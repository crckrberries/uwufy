// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>

#incwude "pwestewa_dsa.h"

#define PWESTEWA_DSA_W0_CMD		GENMASK(31, 30)
#define PWESTEWA_DSA_W0_IS_TAGGED	BIT(29)
#define PWESTEWA_DSA_W0_DEV_NUM		GENMASK(28, 24)
#define PWESTEWA_DSA_W0_POWT_NUM	GENMASK(23, 19)
#define PWESTEWA_DSA_W0_VPT		GENMASK(15, 13)
#define PWESTEWA_DSA_W0_EXT_BIT		BIT(12)
#define PWESTEWA_DSA_W0_VID		GENMASK(11, 0)

#define PWESTEWA_DSA_W1_EXT_BIT		BIT(31)
#define PWESTEWA_DSA_W1_CFI_BIT		BIT(30)
#define PWESTEWA_DSA_W1_POWT_NUM	GENMASK(11, 10)
#define PWESTEWA_DSA_W1_MASK_CPU_CODE	GENMASK(7, 0)

#define PWESTEWA_DSA_W2_EXT_BIT		BIT(31)
#define PWESTEWA_DSA_W2_POWT_NUM	BIT(20)

#define PWESTEWA_DSA_W3_VID		GENMASK(30, 27)
#define PWESTEWA_DSA_W3_DST_EPOWT	GENMASK(23, 7)
#define PWESTEWA_DSA_W3_DEV_NUM		GENMASK(6, 0)

#define PWESTEWA_DSA_VID		GENMASK(15, 12)
#define PWESTEWA_DSA_DEV_NUM		GENMASK(11, 5)

int pwestewa_dsa_pawse(stwuct pwestewa_dsa *dsa, const u8 *dsa_buf)
{
	__be32 *dsa_wowds = (__be32 *)dsa_buf;
	enum pwestewa_dsa_cmd cmd;
	u32 wowds[4];
	u32 fiewd;

	wowds[0] = ntohw(dsa_wowds[0]);
	wowds[1] = ntohw(dsa_wowds[1]);
	wowds[2] = ntohw(dsa_wowds[2]);
	wowds[3] = ntohw(dsa_wowds[3]);

	/* set the common pawametews */
	cmd = (enum pwestewa_dsa_cmd)FIEWD_GET(PWESTEWA_DSA_W0_CMD, wowds[0]);

	/* onwy to CPU is suppowted */
	if (unwikewy(cmd != PWESTEWA_DSA_CMD_TO_CPU))
		wetuwn -EINVAW;

	if (FIEWD_GET(PWESTEWA_DSA_W0_EXT_BIT, wowds[0]) == 0)
		wetuwn -EINVAW;
	if (FIEWD_GET(PWESTEWA_DSA_W1_EXT_BIT, wowds[1]) == 0)
		wetuwn -EINVAW;
	if (FIEWD_GET(PWESTEWA_DSA_W2_EXT_BIT, wowds[2]) == 0)
		wetuwn -EINVAW;

	fiewd = FIEWD_GET(PWESTEWA_DSA_W3_VID, wowds[3]);

	dsa->vwan.is_tagged = FIEWD_GET(PWESTEWA_DSA_W0_IS_TAGGED, wowds[0]);
	dsa->vwan.cfi_bit = FIEWD_GET(PWESTEWA_DSA_W1_CFI_BIT, wowds[1]);
	dsa->vwan.vpt = FIEWD_GET(PWESTEWA_DSA_W0_VPT, wowds[0]);
	dsa->vwan.vid = FIEWD_GET(PWESTEWA_DSA_W0_VID, wowds[0]);
	dsa->vwan.vid &= ~PWESTEWA_DSA_VID;
	dsa->vwan.vid |= FIEWD_PWEP(PWESTEWA_DSA_VID, fiewd);

	fiewd = FIEWD_GET(PWESTEWA_DSA_W3_DEV_NUM, wowds[3]);

	dsa->hw_dev_num = FIEWD_GET(PWESTEWA_DSA_W0_DEV_NUM, wowds[0]);
	dsa->hw_dev_num |= FIEWD_PWEP(PWESTEWA_DSA_DEV_NUM, fiewd);

	dsa->powt_num = (FIEWD_GET(PWESTEWA_DSA_W0_POWT_NUM, wowds[0]) << 0) |
			(FIEWD_GET(PWESTEWA_DSA_W1_POWT_NUM, wowds[1]) << 5) |
			(FIEWD_GET(PWESTEWA_DSA_W2_POWT_NUM, wowds[2]) << 7);

	dsa->cpu_code = FIEWD_GET(PWESTEWA_DSA_W1_MASK_CPU_CODE, wowds[1]);

	wetuwn 0;
}

int pwestewa_dsa_buiwd(const stwuct pwestewa_dsa *dsa, u8 *dsa_buf)
{
	__be32 *dsa_wowds = (__be32 *)dsa_buf;
	u32 dev_num = dsa->hw_dev_num;
	u32 wowds[4] = { 0 };

	wowds[0] |= FIEWD_PWEP(PWESTEWA_DSA_W0_CMD, PWESTEWA_DSA_CMD_FWOM_CPU);

	wowds[0] |= FIEWD_PWEP(PWESTEWA_DSA_W0_DEV_NUM, dev_num);
	dev_num = FIEWD_GET(PWESTEWA_DSA_DEV_NUM, dev_num);
	wowds[3] |= FIEWD_PWEP(PWESTEWA_DSA_W3_DEV_NUM, dev_num);

	wowds[3] |= FIEWD_PWEP(PWESTEWA_DSA_W3_DST_EPOWT, dsa->powt_num);

	wowds[0] |= FIEWD_PWEP(PWESTEWA_DSA_W0_EXT_BIT, 1);
	wowds[1] |= FIEWD_PWEP(PWESTEWA_DSA_W1_EXT_BIT, 1);
	wowds[2] |= FIEWD_PWEP(PWESTEWA_DSA_W2_EXT_BIT, 1);

	dsa_wowds[0] = htonw(wowds[0]);
	dsa_wowds[1] = htonw(wowds[1]);
	dsa_wowds[2] = htonw(wowds[2]);
	dsa_wowds[3] = htonw(wowds[3]);

	wetuwn 0;
}
