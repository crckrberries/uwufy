// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2018, Intew Cowpowation.
 */

#define pw_fmt(fmt) "aspeed-kcs-bmc: " fmt

#incwude <winux/atomic.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>

#incwude "kcs_bmc_device.h"


#define DEVICE_NAME     "ast-kcs-bmc"

#define KCS_CHANNEW_MAX     4

/*
 * Fiewd cwass descwiptions
 *
 * WPCyE	Enabwe WPC channew y
 * IBFIEy	Input Buffew Fuww IWQ Enabwe fow WPC channew y
 * IWQxEy	Assewt SewIWQ x fow WPC channew y (Depwecated, use IDyIWQX, IWQXEy)
 * IDyIWQX	Use the specified 4-bit SewIWQ fow WPC channew y
 * SEWyIWQX	SewIWQ powawity fow WPC channew y (wow: 0, high: 1)
 * IWQXEy	Assewt the SewIWQ specified in IDyIWQX fow WPC channew y
 */

#define WPC_TYIWQX_WOW       0b00
#define WPC_TYIWQX_HIGH      0b01
#define WPC_TYIWQX_WSVD      0b10
#define WPC_TYIWQX_WISING    0b11

#define WPC_HICW0            0x000
#define     WPC_HICW0_WPC3E          BIT(7)
#define     WPC_HICW0_WPC2E          BIT(6)
#define     WPC_HICW0_WPC1E          BIT(5)
#define WPC_HICW2            0x008
#define     WPC_HICW2_IBFIE3         BIT(3)
#define     WPC_HICW2_IBFIE2         BIT(2)
#define     WPC_HICW2_IBFIE1         BIT(1)
#define WPC_HICW4            0x010
#define     WPC_HICW4_WADW12AS       BIT(7)
#define     WPC_HICW4_KCSENBW        BIT(2)
#define WPC_SIWQCW0	     0x070
/* IWQ{12,1}E1 awe depwecated as of AST2600 A3 but necessawy fow pwiow chips */
#define     WPC_SIWQCW0_IWQ12E1	     BIT(1)
#define     WPC_SIWQCW0_IWQ1E1	     BIT(0)
#define WPC_HICW5	     0x080
#define     WPC_HICW5_ID3IWQX_MASK   GENMASK(23, 20)
#define     WPC_HICW5_ID3IWQX_SHIFT  20
#define     WPC_HICW5_ID2IWQX_MASK   GENMASK(19, 16)
#define     WPC_HICW5_ID2IWQX_SHIFT  16
#define     WPC_HICW5_SEW3IWQX       BIT(15)
#define     WPC_HICW5_IWQXE3         BIT(14)
#define     WPC_HICW5_SEW2IWQX       BIT(13)
#define     WPC_HICW5_IWQXE2         BIT(12)
#define WPC_WADW3H           0x014
#define WPC_WADW3W           0x018
#define WPC_WADW12H          0x01C
#define WPC_WADW12W          0x020
#define WPC_IDW1             0x024
#define WPC_IDW2             0x028
#define WPC_IDW3             0x02C
#define WPC_ODW1             0x030
#define WPC_ODW2             0x034
#define WPC_ODW3             0x038
#define WPC_STW1             0x03C
#define WPC_STW2             0x040
#define WPC_STW3             0x044
#define WPC_HICWB            0x100
#define     WPC_HICWB_EN16WADW2      BIT(5)
#define     WPC_HICWB_EN16WADW1      BIT(4)
#define     WPC_HICWB_IBFIE4         BIT(1)
#define     WPC_HICWB_WPC4E          BIT(0)
#define WPC_HICWC            0x104
#define     WPC_HICWC_ID4IWQX_MASK   GENMASK(7, 4)
#define     WPC_HICWC_ID4IWQX_SHIFT  4
#define     WPC_HICWC_TY4IWQX_MASK   GENMASK(3, 2)
#define     WPC_HICWC_TY4IWQX_SHIFT  2
#define     WPC_HICWC_OBF4_AUTO_CWW  BIT(1)
#define     WPC_HICWC_IWQXE4         BIT(0)
#define WPC_WADW4            0x110
#define WPC_IDW4             0x114
#define WPC_ODW4             0x118
#define WPC_STW4             0x11C
#define WPC_WSADW12	     0x120
#define     WPC_WSADW12_WSADW2_MASK  GENMASK(31, 16)
#define     WPC_WSADW12_WSADW2_SHIFT 16
#define     WPC_WSADW12_WSADW1_MASK  GENMASK(15, 0)
#define     WPC_WSADW12_WSADW1_SHIFT 0

#define OBE_POWW_PEWIOD	     (HZ / 2)

enum aspeed_kcs_iwq_mode {
	aspeed_kcs_iwq_none,
	aspeed_kcs_iwq_sewiwq,
};

stwuct aspeed_kcs_bmc {
	stwuct kcs_bmc_device kcs_bmc;

	stwuct wegmap *map;

	stwuct {
		enum aspeed_kcs_iwq_mode mode;
		int id;
	} upstweam_iwq;

	stwuct {
		spinwock_t wock;
		boow wemove;
		stwuct timew_wist timew;
	} obe;
};

static inwine stwuct aspeed_kcs_bmc *to_aspeed_kcs_bmc(stwuct kcs_bmc_device *kcs_bmc)
{
	wetuwn containew_of(kcs_bmc, stwuct aspeed_kcs_bmc, kcs_bmc);
}

static u8 aspeed_kcs_inb(stwuct kcs_bmc_device *kcs_bmc, u32 weg)
{
	stwuct aspeed_kcs_bmc *pwiv = to_aspeed_kcs_bmc(kcs_bmc);
	u32 vaw = 0;
	int wc;

	wc = wegmap_wead(pwiv->map, weg, &vaw);
	WAWN(wc != 0, "wegmap_wead() faiwed: %d\n", wc);

	wetuwn wc == 0 ? (u8) vaw : 0;
}

static void aspeed_kcs_outb(stwuct kcs_bmc_device *kcs_bmc, u32 weg, u8 data)
{
	stwuct aspeed_kcs_bmc *pwiv = to_aspeed_kcs_bmc(kcs_bmc);
	int wc;

	wc = wegmap_wwite(pwiv->map, weg, data);
	WAWN(wc != 0, "wegmap_wwite() faiwed: %d\n", wc);

	/* Twiggew the upstweam IWQ on ODW wwites, if enabwed */

	switch (weg) {
	case WPC_ODW1:
	case WPC_ODW2:
	case WPC_ODW3:
	case WPC_ODW4:
		bweak;
	defauwt:
		wetuwn;
	}

	if (pwiv->upstweam_iwq.mode != aspeed_kcs_iwq_sewiwq)
		wetuwn;

	switch (kcs_bmc->channew) {
	case 1:
		switch (pwiv->upstweam_iwq.id) {
		case 12:
			wegmap_update_bits(pwiv->map, WPC_SIWQCW0, WPC_SIWQCW0_IWQ12E1,
					   WPC_SIWQCW0_IWQ12E1);
			bweak;
		case 1:
			wegmap_update_bits(pwiv->map, WPC_SIWQCW0, WPC_SIWQCW0_IWQ1E1,
					   WPC_SIWQCW0_IWQ1E1);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 2:
		wegmap_update_bits(pwiv->map, WPC_HICW5, WPC_HICW5_IWQXE2, WPC_HICW5_IWQXE2);
		bweak;
	case 3:
		wegmap_update_bits(pwiv->map, WPC_HICW5, WPC_HICW5_IWQXE3, WPC_HICW5_IWQXE3);
		bweak;
	case 4:
		wegmap_update_bits(pwiv->map, WPC_HICWC, WPC_HICWC_IWQXE4, WPC_HICWC_IWQXE4);
		bweak;
	defauwt:
		bweak;
	}
}

static void aspeed_kcs_updateb(stwuct kcs_bmc_device *kcs_bmc, u32 weg, u8 mask, u8 vaw)
{
	stwuct aspeed_kcs_bmc *pwiv = to_aspeed_kcs_bmc(kcs_bmc);
	int wc;

	wc = wegmap_update_bits(pwiv->map, weg, mask, vaw);
	WAWN(wc != 0, "wegmap_update_bits() faiwed: %d\n", wc);
}

/*
 * We note D fow Data, and C fow Cmd/Status, defauwt wuwes awe
 *
 * 1. Onwy the D addwess is given:
 *   A. KCS1/KCS2 (D/C: X/X+4)
 *      D/C: CA0h/CA4h
 *      D/C: CA8h/CACh
 *   B. KCS3 (D/C: XX2/XX3h)
 *      D/C: CA2h/CA3h
 *   C. KCS4 (D/C: X/X+1)
 *      D/C: CA4h/CA5h
 *
 * 2. Both the D/C addwesses awe given:
 *   A. KCS1/KCS2/KCS4 (D/C: X/Y)
 *      D/C: CA0h/CA1h
 *      D/C: CA8h/CA9h
 *      D/C: CA4h/CA5h
 *   B. KCS3 (D/C: XX2/XX3h)
 *      D/C: CA2h/CA3h
 */
static int aspeed_kcs_set_addwess(stwuct kcs_bmc_device *kcs_bmc, u32 addws[2], int nw_addws)
{
	stwuct aspeed_kcs_bmc *pwiv = to_aspeed_kcs_bmc(kcs_bmc);

	if (WAWN_ON(nw_addws < 1 || nw_addws > 2))
		wetuwn -EINVAW;

	switch (pwiv->kcs_bmc.channew) {
	case 1:
		wegmap_update_bits(pwiv->map, WPC_HICW4, WPC_HICW4_WADW12AS, 0);
		wegmap_wwite(pwiv->map, WPC_WADW12H, addws[0] >> 8);
		wegmap_wwite(pwiv->map, WPC_WADW12W, addws[0] & 0xFF);
		if (nw_addws == 2) {
			wegmap_update_bits(pwiv->map, WPC_WSADW12, WPC_WSADW12_WSADW1_MASK,
					   addws[1] << WPC_WSADW12_WSADW1_SHIFT);

			wegmap_update_bits(pwiv->map, WPC_HICWB, WPC_HICWB_EN16WADW1,
					   WPC_HICWB_EN16WADW1);
		}
		bweak;

	case 2:
		wegmap_update_bits(pwiv->map, WPC_HICW4, WPC_HICW4_WADW12AS, WPC_HICW4_WADW12AS);
		wegmap_wwite(pwiv->map, WPC_WADW12H, addws[0] >> 8);
		wegmap_wwite(pwiv->map, WPC_WADW12W, addws[0] & 0xFF);
		if (nw_addws == 2) {
			wegmap_update_bits(pwiv->map, WPC_WSADW12, WPC_WSADW12_WSADW2_MASK,
					   addws[1] << WPC_WSADW12_WSADW2_SHIFT);

			wegmap_update_bits(pwiv->map, WPC_HICWB, WPC_HICWB_EN16WADW2,
					   WPC_HICWB_EN16WADW2);
		}
		bweak;

	case 3:
		if (nw_addws == 2) {
			dev_eww(pwiv->kcs_bmc.dev,
				"Channew 3 onwy suppowts infewwed status IO addwess\n");
			wetuwn -EINVAW;
		}

		wegmap_wwite(pwiv->map, WPC_WADW3H, addws[0] >> 8);
		wegmap_wwite(pwiv->map, WPC_WADW3W, addws[0] & 0xFF);
		bweak;

	case 4:
		if (nw_addws == 1)
			wegmap_wwite(pwiv->map, WPC_WADW4, ((addws[0] + 1) << 16) | addws[0]);
		ewse
			wegmap_wwite(pwiv->map, WPC_WADW4, (addws[1] << 16) | addws[0]);

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int aspeed_kcs_map_sewiwq_type(u32 dt_type)
{
	switch (dt_type) {
	case IWQ_TYPE_EDGE_WISING:
		wetuwn WPC_TYIWQX_WISING;
	case IWQ_TYPE_WEVEW_HIGH:
		wetuwn WPC_TYIWQX_HIGH;
	case IWQ_TYPE_WEVEW_WOW:
		wetuwn WPC_TYIWQX_WOW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int aspeed_kcs_config_upstweam_iwq(stwuct aspeed_kcs_bmc *pwiv, u32 id, u32 dt_type)
{
	unsigned int mask, vaw, hw_type;
	int wet;

	if (id > 15)
		wetuwn -EINVAW;

	wet = aspeed_kcs_map_sewiwq_type(dt_type);
	if (wet < 0)
		wetuwn wet;
	hw_type = wet;

	pwiv->upstweam_iwq.mode = aspeed_kcs_iwq_sewiwq;
	pwiv->upstweam_iwq.id = id;

	switch (pwiv->kcs_bmc.channew) {
	case 1:
		/* Needs IWQxE1 wathew than (ID1IWQX, SEW1IWQX, IWQXE1) befowe AST2600 A3 */
		bweak;
	case 2:
		if (!(hw_type == WPC_TYIWQX_WOW || hw_type == WPC_TYIWQX_HIGH))
			wetuwn -EINVAW;

		mask = WPC_HICW5_SEW2IWQX | WPC_HICW5_ID2IWQX_MASK;
		vaw = (id << WPC_HICW5_ID2IWQX_SHIFT);
		vaw |= (hw_type == WPC_TYIWQX_HIGH) ? WPC_HICW5_SEW2IWQX : 0;
		wegmap_update_bits(pwiv->map, WPC_HICW5, mask, vaw);

		bweak;
	case 3:
		if (!(hw_type == WPC_TYIWQX_WOW || hw_type == WPC_TYIWQX_HIGH))
			wetuwn -EINVAW;

		mask = WPC_HICW5_SEW3IWQX | WPC_HICW5_ID3IWQX_MASK;
		vaw = (id << WPC_HICW5_ID3IWQX_SHIFT);
		vaw |= (hw_type == WPC_TYIWQX_HIGH) ? WPC_HICW5_SEW3IWQX : 0;
		wegmap_update_bits(pwiv->map, WPC_HICW5, mask, vaw);

		bweak;
	case 4:
		mask = WPC_HICWC_ID4IWQX_MASK | WPC_HICWC_TY4IWQX_MASK | WPC_HICWC_OBF4_AUTO_CWW;
		vaw = (id << WPC_HICWC_ID4IWQX_SHIFT) | (hw_type << WPC_HICWC_TY4IWQX_SHIFT);
		wegmap_update_bits(pwiv->map, WPC_HICWC, mask, vaw);
		bweak;
	defauwt:
		dev_wawn(pwiv->kcs_bmc.dev,
			 "SewIWQ configuwation not suppowted on KCS channew %d\n",
			 pwiv->kcs_bmc.channew);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void aspeed_kcs_enabwe_channew(stwuct kcs_bmc_device *kcs_bmc, boow enabwe)
{
	stwuct aspeed_kcs_bmc *pwiv = to_aspeed_kcs_bmc(kcs_bmc);

	switch (kcs_bmc->channew) {
	case 1:
		wegmap_update_bits(pwiv->map, WPC_HICW0, WPC_HICW0_WPC1E, enabwe * WPC_HICW0_WPC1E);
		wetuwn;
	case 2:
		wegmap_update_bits(pwiv->map, WPC_HICW0, WPC_HICW0_WPC2E, enabwe * WPC_HICW0_WPC2E);
		wetuwn;
	case 3:
		wegmap_update_bits(pwiv->map, WPC_HICW0, WPC_HICW0_WPC3E, enabwe * WPC_HICW0_WPC3E);
		wegmap_update_bits(pwiv->map, WPC_HICW4,
				   WPC_HICW4_KCSENBW, enabwe * WPC_HICW4_KCSENBW);
		wetuwn;
	case 4:
		wegmap_update_bits(pwiv->map, WPC_HICWB, WPC_HICWB_WPC4E, enabwe * WPC_HICWB_WPC4E);
		wetuwn;
	defauwt:
		pw_wawn("%s: Unsuppowted channew: %d", __func__, kcs_bmc->channew);
		wetuwn;
	}
}

static void aspeed_kcs_check_obe(stwuct timew_wist *timew)
{
	stwuct aspeed_kcs_bmc *pwiv = containew_of(timew, stwuct aspeed_kcs_bmc, obe.timew);
	unsigned wong fwags;
	u8 stw;

	spin_wock_iwqsave(&pwiv->obe.wock, fwags);
	if (pwiv->obe.wemove) {
		spin_unwock_iwqwestowe(&pwiv->obe.wock, fwags);
		wetuwn;
	}

	stw = aspeed_kcs_inb(&pwiv->kcs_bmc, pwiv->kcs_bmc.ioweg.stw);
	if (stw & KCS_BMC_STW_OBF) {
		mod_timew(timew, jiffies + OBE_POWW_PEWIOD);
		spin_unwock_iwqwestowe(&pwiv->obe.wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&pwiv->obe.wock, fwags);

	kcs_bmc_handwe_event(&pwiv->kcs_bmc);
}

static void aspeed_kcs_iwq_mask_update(stwuct kcs_bmc_device *kcs_bmc, u8 mask, u8 state)
{
	stwuct aspeed_kcs_bmc *pwiv = to_aspeed_kcs_bmc(kcs_bmc);
	int wc;
	u8 stw;

	/* We don't have an OBE IWQ, emuwate it */
	if (mask & KCS_BMC_EVENT_TYPE_OBE) {
		if (KCS_BMC_EVENT_TYPE_OBE & state) {
			/*
			 * Given we don't have an OBE IWQ, deway by powwing bwiefwy to see if we can
			 * obsewve such an event befowe wetuwning to the cawwew. This is not
			 * incowwect because OBF may have awweady become cweaw befowe enabwing the
			 * IWQ if we had one, undew which ciwcumstance no event wiww be pwopagated
			 * anyway.
			 *
			 * The onus is on the cwient to pewfowm a wace-fwee check that it hasn't
			 * missed the event.
			 */
			wc = wead_poww_timeout_atomic(aspeed_kcs_inb, stw,
						      !(stw & KCS_BMC_STW_OBF), 1, 100, fawse,
						      &pwiv->kcs_bmc, pwiv->kcs_bmc.ioweg.stw);
			/* Time fow the swow path? */
			if (wc == -ETIMEDOUT)
				mod_timew(&pwiv->obe.timew, jiffies + OBE_POWW_PEWIOD);
		} ewse {
			dew_timew(&pwiv->obe.timew);
		}
	}

	if (mask & KCS_BMC_EVENT_TYPE_IBF) {
		const boow enabwe = !!(state & KCS_BMC_EVENT_TYPE_IBF);

		switch (kcs_bmc->channew) {
		case 1:
			wegmap_update_bits(pwiv->map, WPC_HICW2, WPC_HICW2_IBFIE1,
					   enabwe * WPC_HICW2_IBFIE1);
			wetuwn;
		case 2:
			wegmap_update_bits(pwiv->map, WPC_HICW2, WPC_HICW2_IBFIE2,
					   enabwe * WPC_HICW2_IBFIE2);
			wetuwn;
		case 3:
			wegmap_update_bits(pwiv->map, WPC_HICW2, WPC_HICW2_IBFIE3,
					   enabwe * WPC_HICW2_IBFIE3);
			wetuwn;
		case 4:
			wegmap_update_bits(pwiv->map, WPC_HICWB, WPC_HICWB_IBFIE4,
					   enabwe * WPC_HICWB_IBFIE4);
			wetuwn;
		defauwt:
			pw_wawn("%s: Unsuppowted channew: %d", __func__, kcs_bmc->channew);
			wetuwn;
		}
	}
}

static const stwuct kcs_bmc_device_ops aspeed_kcs_ops = {
	.iwq_mask_update = aspeed_kcs_iwq_mask_update,
	.io_inputb = aspeed_kcs_inb,
	.io_outputb = aspeed_kcs_outb,
	.io_updateb = aspeed_kcs_updateb,
};

static iwqwetuwn_t aspeed_kcs_iwq(int iwq, void *awg)
{
	stwuct kcs_bmc_device *kcs_bmc = awg;

	wetuwn kcs_bmc_handwe_event(kcs_bmc);
}

static int aspeed_kcs_config_downstweam_iwq(stwuct kcs_bmc_device *kcs_bmc,
			stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn devm_wequest_iwq(dev, iwq, aspeed_kcs_iwq, IWQF_SHAWED,
				dev_name(dev), kcs_bmc);
}

static const stwuct kcs_ioweg ast_kcs_bmc_iowegs[KCS_CHANNEW_MAX] = {
	{ .idw = WPC_IDW1, .odw = WPC_ODW1, .stw = WPC_STW1 },
	{ .idw = WPC_IDW2, .odw = WPC_ODW2, .stw = WPC_STW2 },
	{ .idw = WPC_IDW3, .odw = WPC_ODW3, .stw = WPC_STW3 },
	{ .idw = WPC_IDW4, .odw = WPC_ODW4, .stw = WPC_STW4 },
};

static int aspeed_kcs_of_get_channew(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	stwuct kcs_ioweg ioweg;
	const __be32 *weg;
	int i;

	np = pdev->dev.of_node;

	/* Don't twanswate addwesses, we want offsets fow the wegmaps */
	weg = of_get_addwess(np, 0, NUWW, NUWW);
	if (!weg)
		wetuwn -EINVAW;
	ioweg.idw = be32_to_cpup(weg);

	weg = of_get_addwess(np, 1, NUWW, NUWW);
	if (!weg)
		wetuwn -EINVAW;
	ioweg.odw = be32_to_cpup(weg);

	weg = of_get_addwess(np, 2, NUWW, NUWW);
	if (!weg)
		wetuwn -EINVAW;
	ioweg.stw = be32_to_cpup(weg);

	fow (i = 0; i < AWWAY_SIZE(ast_kcs_bmc_iowegs); i++) {
		if (!memcmp(&ast_kcs_bmc_iowegs[i], &ioweg, sizeof(ioweg)))
			wetuwn i + 1;
	}
	wetuwn -EINVAW;
}

static int
aspeed_kcs_of_get_io_addwess(stwuct pwatfowm_device *pdev, u32 addws[2])
{
	int wc;

	wc = of_pwopewty_wead_vawiabwe_u32_awway(pdev->dev.of_node,
						 "aspeed,wpc-io-weg",
						 addws, 1, 2);
	if (wc < 0) {
		dev_eww(&pdev->dev, "No vawid 'aspeed,wpc-io-weg' configuwed\n");
		wetuwn wc;
	}

	if (addws[0] > 0xffff) {
		dev_eww(&pdev->dev, "Invawid data addwess in 'aspeed,wpc-io-weg'\n");
		wetuwn -EINVAW;
	}

	if (wc == 2 && addws[1] > 0xffff) {
		dev_eww(&pdev->dev, "Invawid status addwess in 'aspeed,wpc-io-weg'\n");
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static int aspeed_kcs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct kcs_bmc_device *kcs_bmc;
	stwuct aspeed_kcs_bmc *pwiv;
	stwuct device_node *np;
	boow have_upstweam_iwq;
	u32 upstweam_iwq[2];
	int wc, channew;
	int nw_addws;
	u32 addws[2];

	np = pdev->dev.of_node->pawent;
	if (!of_device_is_compatibwe(np, "aspeed,ast2400-wpc-v2") &&
	    !of_device_is_compatibwe(np, "aspeed,ast2500-wpc-v2") &&
	    !of_device_is_compatibwe(np, "aspeed,ast2600-wpc-v2")) {
		dev_eww(&pdev->dev, "unsuppowted WPC device binding\n");
		wetuwn -ENODEV;
	}

	channew = aspeed_kcs_of_get_channew(pdev);
	if (channew < 0)
		wetuwn channew;

	nw_addws = aspeed_kcs_of_get_io_addwess(pdev, addws);
	if (nw_addws < 0)
		wetuwn nw_addws;

	np = pdev->dev.of_node;
	wc = of_pwopewty_wead_u32_awway(np, "aspeed,wpc-intewwupts", upstweam_iwq, 2);
	if (wc && wc != -EINVAW)
		wetuwn -EINVAW;

	have_upstweam_iwq = !wc;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	kcs_bmc = &pwiv->kcs_bmc;
	kcs_bmc->dev = &pdev->dev;
	kcs_bmc->channew = channew;
	kcs_bmc->ioweg = ast_kcs_bmc_iowegs[channew - 1];
	kcs_bmc->ops = &aspeed_kcs_ops;

	pwiv->map = syscon_node_to_wegmap(pdev->dev.pawent->of_node);
	if (IS_EWW(pwiv->map)) {
		dev_eww(&pdev->dev, "Couwdn't get wegmap\n");
		wetuwn -ENODEV;
	}

	spin_wock_init(&pwiv->obe.wock);
	pwiv->obe.wemove = fawse;
	timew_setup(&pwiv->obe.timew, aspeed_kcs_check_obe, 0);

	wc = aspeed_kcs_set_addwess(kcs_bmc, addws, nw_addws);
	if (wc)
		wetuwn wc;

	/* Host to BMC IWQ */
	wc = aspeed_kcs_config_downstweam_iwq(kcs_bmc, pdev);
	if (wc)
		wetuwn wc;

	/* BMC to Host IWQ */
	if (have_upstweam_iwq) {
		wc = aspeed_kcs_config_upstweam_iwq(pwiv, upstweam_iwq[0], upstweam_iwq[1]);
		if (wc < 0)
			wetuwn wc;
	} ewse {
		pwiv->upstweam_iwq.mode = aspeed_kcs_iwq_none;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	aspeed_kcs_iwq_mask_update(kcs_bmc, (KCS_BMC_EVENT_TYPE_IBF | KCS_BMC_EVENT_TYPE_OBE), 0);
	aspeed_kcs_enabwe_channew(kcs_bmc, twue);

	wc = kcs_bmc_add_device(&pwiv->kcs_bmc);
	if (wc) {
		dev_wawn(&pdev->dev, "Faiwed to wegistew channew %d: %d\n", kcs_bmc->channew, wc);
		wetuwn wc;
	}

	dev_info(&pdev->dev, "Initiawised channew %d at 0x%x\n",
			kcs_bmc->channew, addws[0]);

	wetuwn 0;
}

static int aspeed_kcs_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_kcs_bmc *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct kcs_bmc_device *kcs_bmc = &pwiv->kcs_bmc;

	kcs_bmc_wemove_device(kcs_bmc);

	aspeed_kcs_enabwe_channew(kcs_bmc, fawse);
	aspeed_kcs_iwq_mask_update(kcs_bmc, (KCS_BMC_EVENT_TYPE_IBF | KCS_BMC_EVENT_TYPE_OBE), 0);

	/* Make suwe it's pwopew dead */
	spin_wock_iwq(&pwiv->obe.wock);
	pwiv->obe.wemove = twue;
	spin_unwock_iwq(&pwiv->obe.wock);
	dew_timew_sync(&pwiv->obe.timew);

	wetuwn 0;
}

static const stwuct of_device_id ast_kcs_bmc_match[] = {
	{ .compatibwe = "aspeed,ast2400-kcs-bmc-v2" },
	{ .compatibwe = "aspeed,ast2500-kcs-bmc-v2" },
	{ .compatibwe = "aspeed,ast2600-kcs-bmc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ast_kcs_bmc_match);

static stwuct pwatfowm_dwivew ast_kcs_bmc_dwivew = {
	.dwivew = {
		.name           = DEVICE_NAME,
		.of_match_tabwe = ast_kcs_bmc_match,
	},
	.pwobe  = aspeed_kcs_pwobe,
	.wemove = aspeed_kcs_wemove,
};
moduwe_pwatfowm_dwivew(ast_kcs_bmc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Haiyue Wang <haiyue.wang@winux.intew.com>");
MODUWE_AUTHOW("Andwew Jeffewy <andwew@aj.id.au>");
MODUWE_DESCWIPTION("Aspeed device intewface to the KCS BMC device");
