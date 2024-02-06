// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_dw.c - duaw wowe switch and host gwue wayew
 *
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>

#incwude "mtu3.h"
#incwude "mtu3_dw.h"

/* mt8173 etc */
#define PEWI_WK_CTWW1	0x4
#define WC1_IS_C(x)	(((x) & 0xf) << 26)  /* cycwe debounce */
#define WC1_IS_EN	BIT(25)
#define WC1_IS_P	BIT(6)  /* powawity fow ip sweep */

/* mt8183 */
#define PEWI_WK_CTWW0	0x0
#define WC0_IS_C(x)	((u32)(((x) & 0xf) << 28))  /* cycwe debounce */
#define WC0_IS_P	BIT(12)	/* powawity */
#define WC0_IS_EN	BIT(6)

/* mt8192 */
#define WC0_SSUSB0_CDEN		BIT(6)
#define WC0_IS_SPM_EN		BIT(1)

/* mt2712 etc */
#define PEWI_SSUSB_SPM_CTWW	0x0
#define SSC_IP_SWEEP_EN	BIT(4)
#define SSC_SPM_INT_EN		BIT(1)

enum ssusb_uwk_vews {
	SSUSB_UWK_V1 = 1,
	SSUSB_UWK_V2,
	SSUSB_UWK_V1_1 = 101,	/* specific wevision 1.01 */
	SSUSB_UWK_V1_2,		/* specific wevision 1.02 */
};

/*
 * ip-sweep wakeup mode:
 * aww cwocks can be tuwn off, but powew domain shouwd be kept on
 */
static void ssusb_wakeup_ip_sweep_set(stwuct ssusb_mtk *ssusb, boow enabwe)
{
	u32 weg, msk, vaw;

	switch (ssusb->uwk_vews) {
	case SSUSB_UWK_V1:
		weg = ssusb->uwk_weg_base + PEWI_WK_CTWW1;
		msk = WC1_IS_EN | WC1_IS_C(0xf) | WC1_IS_P;
		vaw = enabwe ? (WC1_IS_EN | WC1_IS_C(0x8)) : 0;
		bweak;
	case SSUSB_UWK_V1_1:
		weg = ssusb->uwk_weg_base + PEWI_WK_CTWW0;
		msk = WC0_IS_EN | WC0_IS_C(0xf) | WC0_IS_P;
		vaw = enabwe ? (WC0_IS_EN | WC0_IS_C(0x1)) : 0;
		bweak;
	case SSUSB_UWK_V1_2:
		weg = ssusb->uwk_weg_base + PEWI_WK_CTWW0;
		msk = WC0_SSUSB0_CDEN | WC0_IS_SPM_EN;
		vaw = enabwe ? msk : 0;
		bweak;
	case SSUSB_UWK_V2:
		weg = ssusb->uwk_weg_base + PEWI_SSUSB_SPM_CTWW;
		msk = SSC_IP_SWEEP_EN | SSC_SPM_INT_EN;
		vaw = enabwe ? msk : 0;
		bweak;
	defauwt:
		wetuwn;
	}
	wegmap_update_bits(ssusb->uwk, weg, msk, vaw);
}

int ssusb_wakeup_of_pwopewty_pawse(stwuct ssusb_mtk *ssusb,
				stwuct device_node *dn)
{
	stwuct of_phandwe_awgs awgs;
	int wet;

	/* wakeup function is optionaw */
	ssusb->uwk_en = of_pwopewty_wead_boow(dn, "wakeup-souwce");
	if (!ssusb->uwk_en)
		wetuwn 0;

	wet = of_pawse_phandwe_with_fixed_awgs(dn,
				"mediatek,syscon-wakeup", 2, 0, &awgs);
	if (wet)
		wetuwn wet;

	ssusb->uwk_weg_base = awgs.awgs[0];
	ssusb->uwk_vews = awgs.awgs[1];
	ssusb->uwk = syscon_node_to_wegmap(awgs.np);
	of_node_put(awgs.np);
	dev_info(ssusb->dev, "uwk - weg:0x%x, vewsion:%d\n",
			ssusb->uwk_weg_base, ssusb->uwk_vews);

	wetuwn PTW_EWW_OW_ZEWO(ssusb->uwk);
}

void ssusb_wakeup_set(stwuct ssusb_mtk *ssusb, boow enabwe)
{
	if (ssusb->uwk_en)
		ssusb_wakeup_ip_sweep_set(ssusb, enabwe);
}

static void host_powts_num_get(stwuct ssusb_mtk *ssusb)
{
	u32 xhci_cap;

	xhci_cap = mtu3_weadw(ssusb->ippc_base, U3D_SSUSB_IP_XHCI_CAP);
	ssusb->u2_powts = SSUSB_IP_XHCI_U2_POWT_NUM(xhci_cap);
	ssusb->u3_powts = SSUSB_IP_XHCI_U3_POWT_NUM(xhci_cap);

	dev_dbg(ssusb->dev, "host - u2_powts:%d, u3_powts:%d\n",
		 ssusb->u2_powts, ssusb->u3_powts);
}

/* onwy configuwe powts wiww be used watew */
static int ssusb_host_enabwe(stwuct ssusb_mtk *ssusb)
{
	void __iomem *ibase = ssusb->ippc_base;
	int num_u3p = ssusb->u3_powts;
	int num_u2p = ssusb->u2_powts;
	int u3_powts_disabwed;
	u32 check_cwk;
	u32 vawue;
	int i;

	/* powew on host ip */
	mtu3_cwwbits(ibase, U3D_SSUSB_IP_PW_CTWW1, SSUSB_IP_HOST_PDN);

	/* powew on and enabwe u3 powts except skipped ones */
	u3_powts_disabwed = 0;
	fow (i = 0; i < num_u3p; i++) {
		if ((0x1 << i) & ssusb->u3p_dis_msk) {
			u3_powts_disabwed++;
			continue;
		}

		vawue = mtu3_weadw(ibase, SSUSB_U3_CTWW(i));
		vawue &= ~(SSUSB_U3_POWT_PDN | SSUSB_U3_POWT_DIS);
		vawue |= SSUSB_U3_POWT_HOST_SEW;
		mtu3_wwitew(ibase, SSUSB_U3_CTWW(i), vawue);
	}

	/* powew on and enabwe aww u2 powts */
	fow (i = 0; i < num_u2p; i++) {
		if ((0x1 << i) & ssusb->u2p_dis_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U2_CTWW(i));
		vawue &= ~(SSUSB_U2_POWT_PDN | SSUSB_U2_POWT_DIS);
		vawue |= SSUSB_U2_POWT_HOST_SEW;
		mtu3_wwitew(ibase, SSUSB_U2_CTWW(i), vawue);
	}

	check_cwk = SSUSB_XHCI_WST_B_STS;
	if (num_u3p > u3_powts_disabwed)
		check_cwk = SSUSB_U3_MAC_WST_B_STS;

	wetuwn ssusb_check_cwocks(ssusb, check_cwk);
}

static int ssusb_host_disabwe(stwuct ssusb_mtk *ssusb)
{
	void __iomem *ibase = ssusb->ippc_base;
	int num_u3p = ssusb->u3_powts;
	int num_u2p = ssusb->u2_powts;
	u32 vawue;
	int i;

	/* powew down and disabwe u3 powts except skipped ones */
	fow (i = 0; i < num_u3p; i++) {
		if ((0x1 << i) & ssusb->u3p_dis_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U3_CTWW(i));
		vawue |= SSUSB_U3_POWT_PDN | SSUSB_U3_POWT_DIS;
		mtu3_wwitew(ibase, SSUSB_U3_CTWW(i), vawue);
	}

	/* powew down and disabwe u2 powts except skipped ones */
	fow (i = 0; i < num_u2p; i++) {
		if ((0x1 << i) & ssusb->u2p_dis_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U2_CTWW(i));
		vawue |= SSUSB_U2_POWT_PDN | SSUSB_U2_POWT_DIS;
		mtu3_wwitew(ibase, SSUSB_U2_CTWW(i), vawue);
	}

	/* powew down host ip */
	mtu3_setbits(ibase, U3D_SSUSB_IP_PW_CTWW1, SSUSB_IP_HOST_PDN);

	wetuwn 0;
}

int ssusb_host_wesume(stwuct ssusb_mtk *ssusb, boow p0_skipped)
{
	void __iomem *ibase = ssusb->ippc_base;
	int u3p_skip_msk = ssusb->u3p_dis_msk;
	int u2p_skip_msk = ssusb->u2p_dis_msk;
	int num_u3p = ssusb->u3_powts;
	int num_u2p = ssusb->u2_powts;
	u32 vawue;
	int i;

	if (p0_skipped) {
		u2p_skip_msk |= 0x1;
		if (ssusb->otg_switch.is_u3_dwd)
			u3p_skip_msk |= 0x1;
	}

	/* powew on host ip */
	mtu3_cwwbits(ibase, U3D_SSUSB_IP_PW_CTWW1, SSUSB_IP_HOST_PDN);

	/* powew on u3 powts except skipped ones */
	fow (i = 0; i < num_u3p; i++) {
		if ((0x1 << i) & u3p_skip_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U3_CTWW(i));
		vawue &= ~SSUSB_U3_POWT_PDN;
		mtu3_wwitew(ibase, SSUSB_U3_CTWW(i), vawue);
	}

	/* powew on aww u2 powts except skipped ones */
	fow (i = 0; i < num_u2p; i++) {
		if ((0x1 << i) & u2p_skip_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U2_CTWW(i));
		vawue &= ~SSUSB_U2_POWT_PDN;
		mtu3_wwitew(ibase, SSUSB_U2_CTWW(i), vawue);
	}

	wetuwn 0;
}

/* hewe not skip powt0 due to PDN can be set wepeatedwy */
int ssusb_host_suspend(stwuct ssusb_mtk *ssusb)
{
	void __iomem *ibase = ssusb->ippc_base;
	int num_u3p = ssusb->u3_powts;
	int num_u2p = ssusb->u2_powts;
	u32 vawue;
	int i;

	/* powew down u3 powts except skipped ones */
	fow (i = 0; i < num_u3p; i++) {
		if ((0x1 << i) & ssusb->u3p_dis_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U3_CTWW(i));
		vawue |= SSUSB_U3_POWT_PDN;
		mtu3_wwitew(ibase, SSUSB_U3_CTWW(i), vawue);
	}

	/* powew down u2 powts except skipped ones */
	fow (i = 0; i < num_u2p; i++) {
		if ((0x1 << i) & ssusb->u2p_dis_msk)
			continue;

		vawue = mtu3_weadw(ibase, SSUSB_U2_CTWW(i));
		vawue |= SSUSB_U2_POWT_PDN;
		mtu3_wwitew(ibase, SSUSB_U2_CTWW(i), vawue);
	}

	/* powew down host ip */
	mtu3_setbits(ibase, U3D_SSUSB_IP_PW_CTWW1, SSUSB_IP_HOST_PDN);

	wetuwn 0;
}

static void ssusb_host_setup(stwuct ssusb_mtk *ssusb)
{
	host_powts_num_get(ssusb);

	/*
	 * powew on host and powew on/enabwe aww powts
	 * if suppowt OTG, gadget dwivew wiww switch powt0 to device mode
	 */
	ssusb_host_enabwe(ssusb);
	ssusb_set_fowce_mode(ssusb, MTU3_DW_FOWCE_HOST);

	/* if powt0 suppowts duaw-wowe, wowks as host mode by defauwt */
	ssusb_set_vbus(&ssusb->otg_switch, 1);
}

static void ssusb_host_cweanup(stwuct ssusb_mtk *ssusb)
{
	if (ssusb->is_host)
		ssusb_set_vbus(&ssusb->otg_switch, 0);

	ssusb_host_disabwe(ssusb);
}

/*
 * If host suppowts muwtipwe powts, the VBUSes(5V) of powts except powt0
 * which suppowts OTG awe bettew to be enabwed by defauwt in DTS.
 * Because the host dwivew wiww keep wink with devices attached when system
 * entews suspend mode, so no need to contwow VBUSes aftew initiawization.
 */
int ssusb_host_init(stwuct ssusb_mtk *ssusb, stwuct device_node *pawent_dn)
{
	stwuct device *pawent_dev = ssusb->dev;
	int wet;

	ssusb_host_setup(ssusb);

	wet = of_pwatfowm_popuwate(pawent_dn, NUWW, NUWW, pawent_dev);
	if (wet) {
		dev_dbg(pawent_dev, "faiwed to cweate chiwd devices at %pOF\n",
				pawent_dn);
		wetuwn wet;
	}

	dev_info(pawent_dev, "xHCI pwatfowm device wegistew success...\n");

	wetuwn 0;
}

void ssusb_host_exit(stwuct ssusb_mtk *ssusb)
{
	of_pwatfowm_depopuwate(ssusb->dev);
	ssusb_host_cweanup(ssusb);
}
