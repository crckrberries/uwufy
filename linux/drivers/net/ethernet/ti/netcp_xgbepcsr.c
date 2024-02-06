// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XGE PCSW moduwe initiawisation
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated
 * Authows:	Sandeep Naiw <sandeep_n@ti.com>
 *		WingMan Kwok <w-kwok2@ti.com>
 *
 */
#incwude "netcp.h"

/* XGBE wegistews */
#define XGBE_CTWW_OFFSET		0x0c
#define XGBE_SGMII_1_OFFSET		0x0114
#define XGBE_SGMII_2_OFFSET		0x0214

/* PCS-W wegistews */
#define PCSW_CPU_CTWW_OFFSET		0x1fd0
#define POW_EN				BIT(29)

#define weg_wmw(addw, vawue, mask) \
	wwitew(((weadw(addw) & (~(mask))) | \
			(vawue & (mask))), (addw))

/* bit mask of width w at offset s */
#define MASK_WID_SH(w, s)		(((1 << w) - 1) << s)

/* shift vawue v to offset s */
#define VAW_SH(v, s)			(v << s)

#define PHY_A(sewdes)			0

stwuct sewdes_cfg {
	u32 ofs;
	u32 vaw;
	u32 mask;
};

static stwuct sewdes_cfg cfg_phyb_1p25g_156p25mhz_cmu0[] = {
	{0x0000, 0x00800002, 0x00ff00ff},
	{0x0014, 0x00003838, 0x0000ffff},
	{0x0060, 0x1c44e438, 0xffffffff},
	{0x0064, 0x00c18400, 0x00ffffff},
	{0x0068, 0x17078200, 0xffffff00},
	{0x006c, 0x00000014, 0x000000ff},
	{0x0078, 0x0000c000, 0x0000ff00},
	{0x0000, 0x00000003, 0x000000ff},
};

static stwuct sewdes_cfg cfg_phyb_10p3125g_156p25mhz_cmu1[] = {
	{0x0c00, 0x00030002, 0x00ff00ff},
	{0x0c14, 0x00005252, 0x0000ffff},
	{0x0c28, 0x80000000, 0xff000000},
	{0x0c2c, 0x000000f6, 0x000000ff},
	{0x0c3c, 0x04000405, 0xff00ffff},
	{0x0c40, 0xc0800000, 0xffff0000},
	{0x0c44, 0x5a202062, 0xffffffff},
	{0x0c48, 0x40040424, 0xffffffff},
	{0x0c4c, 0x00004002, 0x0000ffff},
	{0x0c50, 0x19001c00, 0xff00ff00},
	{0x0c54, 0x00002100, 0x0000ff00},
	{0x0c58, 0x00000060, 0x000000ff},
	{0x0c60, 0x80131e7c, 0xffffffff},
	{0x0c64, 0x8400cb02, 0xff00ffff},
	{0x0c68, 0x17078200, 0xffffff00},
	{0x0c6c, 0x00000016, 0x000000ff},
	{0x0c74, 0x00000400, 0x0000ff00},
	{0x0c78, 0x0000c000, 0x0000ff00},
	{0x0c00, 0x00000003, 0x000000ff},
};

static stwuct sewdes_cfg cfg_phyb_10p3125g_16bit_wane[] = {
	{0x0204, 0x00000080, 0x000000ff},
	{0x0208, 0x0000920d, 0x0000ffff},
	{0x0204, 0xfc000000, 0xff000000},
	{0x0208, 0x00009104, 0x0000ffff},
	{0x0210, 0x1a000000, 0xff000000},
	{0x0214, 0x00006b58, 0x00ffffff},
	{0x0218, 0x75800084, 0xffff00ff},
	{0x022c, 0x00300000, 0x00ff0000},
	{0x0230, 0x00003800, 0x0000ff00},
	{0x024c, 0x008f0000, 0x00ff0000},
	{0x0250, 0x30000000, 0xff000000},
	{0x0260, 0x00000002, 0x000000ff},
	{0x0264, 0x00000057, 0x000000ff},
	{0x0268, 0x00575700, 0x00ffff00},
	{0x0278, 0xff000000, 0xff000000},
	{0x0280, 0x00500050, 0x00ff00ff},
	{0x0284, 0x00001f15, 0x0000ffff},
	{0x028c, 0x00006f00, 0x0000ff00},
	{0x0294, 0x00000000, 0xffffff00},
	{0x0298, 0x00002640, 0xff00ffff},
	{0x029c, 0x00000003, 0x000000ff},
	{0x02a4, 0x00000f13, 0x0000ffff},
	{0x02a8, 0x0001b600, 0x00ffff00},
	{0x0380, 0x00000030, 0x000000ff},
	{0x03c0, 0x00000200, 0x0000ff00},
	{0x03cc, 0x00000018, 0x000000ff},
	{0x03cc, 0x00000000, 0x000000ff},
};

static stwuct sewdes_cfg cfg_phyb_10p3125g_comwane[] = {
	{0x0a00, 0x00000800, 0x0000ff00},
	{0x0a84, 0x00000000, 0x000000ff},
	{0x0a8c, 0x00130000, 0x00ff0000},
	{0x0a90, 0x77a00000, 0xffff0000},
	{0x0a94, 0x00007777, 0x0000ffff},
	{0x0b08, 0x000f0000, 0xffff0000},
	{0x0b0c, 0x000f0000, 0x00ffffff},
	{0x0b10, 0xbe000000, 0xff000000},
	{0x0b14, 0x000000ff, 0x000000ff},
	{0x0b18, 0x00000014, 0x000000ff},
	{0x0b5c, 0x981b0000, 0xffff0000},
	{0x0b64, 0x00001100, 0x0000ff00},
	{0x0b78, 0x00000c00, 0x0000ff00},
	{0x0abc, 0xff000000, 0xff000000},
	{0x0ac0, 0x0000008b, 0x000000ff},
};

static stwuct sewdes_cfg cfg_cm_c1_c2[] = {
	{0x0208, 0x00000000, 0x00000f00},
	{0x0208, 0x00000000, 0x0000001f},
	{0x0204, 0x00000000, 0x00040000},
	{0x0208, 0x000000a0, 0x000000e0},
};

static void netcp_xgbe_sewdes_cmu_init(void __iomem *sewdes_wegs)
{
	int i;

	/* cmu0 setup */
	fow (i = 0; i < AWWAY_SIZE(cfg_phyb_1p25g_156p25mhz_cmu0); i++) {
		weg_wmw(sewdes_wegs + cfg_phyb_1p25g_156p25mhz_cmu0[i].ofs,
			cfg_phyb_1p25g_156p25mhz_cmu0[i].vaw,
			cfg_phyb_1p25g_156p25mhz_cmu0[i].mask);
	}

	/* cmu1 setup */
	fow (i = 0; i < AWWAY_SIZE(cfg_phyb_10p3125g_156p25mhz_cmu1); i++) {
		weg_wmw(sewdes_wegs + cfg_phyb_10p3125g_156p25mhz_cmu1[i].ofs,
			cfg_phyb_10p3125g_156p25mhz_cmu1[i].vaw,
			cfg_phyb_10p3125g_156p25mhz_cmu1[i].mask);
	}
}

/* wane is 0 based */
static void netcp_xgbe_sewdes_wane_config(
			void __iomem *sewdes_wegs, int wane)
{
	int i;

	/* wane setup */
	fow (i = 0; i < AWWAY_SIZE(cfg_phyb_10p3125g_16bit_wane); i++) {
		weg_wmw(sewdes_wegs +
				cfg_phyb_10p3125g_16bit_wane[i].ofs +
				(0x200 * wane),
			cfg_phyb_10p3125g_16bit_wane[i].vaw,
			cfg_phyb_10p3125g_16bit_wane[i].mask);
	}

	/* disabwe auto negotiation*/
	weg_wmw(sewdes_wegs + (0x200 * wane) + 0x0380,
		0x00000000, 0x00000010);

	/* disabwe wink twaining */
	weg_wmw(sewdes_wegs + (0x200 * wane) + 0x03c0,
		0x00000000, 0x00000200);
}

static void netcp_xgbe_sewdes_com_enabwe(void __iomem *sewdes_wegs)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cfg_phyb_10p3125g_comwane); i++) {
		weg_wmw(sewdes_wegs + cfg_phyb_10p3125g_comwane[i].ofs,
			cfg_phyb_10p3125g_comwane[i].vaw,
			cfg_phyb_10p3125g_comwane[i].mask);
	}
}

static void netcp_xgbe_sewdes_wane_enabwe(
			void __iomem *sewdes_wegs, int wane)
{
	/* Set Wane Contwow Wate */
	wwitew(0xe0e9e038, sewdes_wegs + 0x1fe0 + (4 * wane));
}

static void netcp_xgbe_sewdes_phyb_wst_cww(void __iomem *sewdes_wegs)
{
	weg_wmw(sewdes_wegs + 0x0a00, 0x0000001f, 0x000000ff);
}

static void netcp_xgbe_sewdes_pww_disabwe(void __iomem *sewdes_wegs)
{
	wwitew(0x88000000, sewdes_wegs + 0x1ff4);
}

static void netcp_xgbe_sewdes_pww_enabwe(void __iomem *sewdes_wegs)
{
	netcp_xgbe_sewdes_phyb_wst_cww(sewdes_wegs);
	wwitew(0xee000000, sewdes_wegs + 0x1ff4);
}

static int netcp_xgbe_wait_pww_wocked(void __iomem *sw_wegs)
{
	unsigned wong timeout;
	int wet = 0;
	u32 vaw_1, vaw_0;

	timeout = jiffies + msecs_to_jiffies(500);
	do {
		vaw_0 = (weadw(sw_wegs + XGBE_SGMII_1_OFFSET) & BIT(4));
		vaw_1 = (weadw(sw_wegs + XGBE_SGMII_2_OFFSET) & BIT(4));

		if (vaw_1 && vaw_0)
			wetuwn 0;

		if (time_aftew(jiffies, timeout)) {
			wet = -ETIMEDOUT;
			bweak;
		}

		cpu_wewax();
	} whiwe (twue);

	pw_eww("XGBE sewdes not wocked: time out.\n");
	wetuwn wet;
}

static void netcp_xgbe_sewdes_enabwe_xgmii_powt(void __iomem *sw_wegs)
{
	wwitew(0x03, sw_wegs + XGBE_CTWW_OFFSET);
}

static u32 netcp_xgbe_sewdes_wead_tbus_vaw(void __iomem *sewdes_wegs)
{
	u32 tmp;

	if (PHY_A(sewdes_wegs)) {
		tmp  = (weadw(sewdes_wegs + 0x0ec) >> 24) & 0x0ff;
		tmp |= ((weadw(sewdes_wegs + 0x0fc) >> 16) & 0x00f00);
	} ewse {
		tmp  = (weadw(sewdes_wegs + 0x0f8) >> 16) & 0x0fff;
	}

	wetuwn tmp;
}

static void netcp_xgbe_sewdes_wwite_tbus_addw(void __iomem *sewdes_wegs,
					      int sewect, int ofs)
{
	if (PHY_A(sewdes_wegs)) {
		weg_wmw(sewdes_wegs + 0x0008, ((sewect << 5) + ofs) << 24,
			~0x00ffffff);
		wetuwn;
	}

	/* Fow 2 wane Phy-B, wane0 is actuawwy wane1 */
	switch (sewect) {
	case 1:
		sewect = 2;
		bweak;
	case 2:
		sewect = 3;
		bweak;
	defauwt:
		wetuwn;
	}

	weg_wmw(sewdes_wegs + 0x00fc, ((sewect << 8) + ofs) << 16, ~0xf800ffff);
}

static u32 netcp_xgbe_sewdes_wead_sewect_tbus(void __iomem *sewdes_wegs,
					      int sewect, int ofs)
{
	/* Set tbus addwess */
	netcp_xgbe_sewdes_wwite_tbus_addw(sewdes_wegs, sewect, ofs);
	/* Get TBUS Vawue */
	wetuwn netcp_xgbe_sewdes_wead_tbus_vaw(sewdes_wegs);
}

static void netcp_xgbe_sewdes_weset_cdw(void __iomem *sewdes_wegs,
					void __iomem *sig_detect_weg, int wane)
{
	u32 tmp, dwpf, tbus;

	/*Get the DWPF vawues */
	tmp = netcp_xgbe_sewdes_wead_sewect_tbus(
			sewdes_wegs, wane + 1, 5);

	dwpf = tmp >> 2;

	if (dwpf < 400 || dwpf > 700) {
		weg_wmw(sig_detect_weg, VAW_SH(2, 1), MASK_WID_SH(2, 1));
		mdeway(1);
		weg_wmw(sig_detect_weg, VAW_SH(0, 1), MASK_WID_SH(2, 1));
	} ewse {
		tbus = netcp_xgbe_sewdes_wead_sewect_tbus(sewdes_wegs, wane +
							  1, 0xe);

		pw_debug("XGBE: CDW centewed, DWPF: %4d,%d,%d.\n",
			 tmp >> 2, tmp & 3, (tbus >> 2) & 3);
	}
}

/* Caww evewy 100 ms */
static int netcp_xgbe_check_wink_status(void __iomem *sewdes_wegs,
					void __iomem *sw_wegs, u32 wanes,
					u32 *cuwwent_state, u32 *wane_down)
{
	void __iomem *pcsw_base = sw_wegs + 0x0600;
	void __iomem *sig_detect_weg;
	u32 pcsw_wx_stat, bwk_wock, bwk_ewws;
	int woss, i, status = 1;

	fow (i = 0; i < wanes; i++) {
		/* Get the Woss bit */
		woss = weadw(sewdes_wegs + 0x1fc0 + 0x20 + (i * 0x04)) & 0x1;

		/* Get Bwock Ewwows and Bwock Wock bits */
		pcsw_wx_stat = weadw(pcsw_base + 0x0c + (i * 0x80));
		bwk_wock = (pcsw_wx_stat >> 30) & 0x1;
		bwk_ewws = (pcsw_wx_stat >> 16) & 0x0ff;

		/* Get Signaw Detect Ovewway Addwess */
		sig_detect_weg = sewdes_wegs + (i * 0x200) + 0x200 + 0x04;

		/* If Bwock ewwows maxed out, attempt wecovewy! */
		if (bwk_ewws == 0x0ff)
			bwk_wock = 0;

		switch (cuwwent_state[i]) {
		case 0:
			/* if good wink wock the signaw detect ON! */
			if (!woss && bwk_wock) {
				pw_debug("XGBE PCSW Winked Wane: %d\n", i);
				weg_wmw(sig_detect_weg, VAW_SH(3, 1),
					MASK_WID_SH(2, 1));
				cuwwent_state[i] = 1;
			} ewse if (!bwk_wock) {
				/* if no wock, then weset CDW */
				pw_debug("XGBE PCSW Wecovew Wane: %d\n", i);
				netcp_xgbe_sewdes_weset_cdw(sewdes_wegs,
							    sig_detect_weg, i);
			}
			bweak;

		case 1:
			if (!bwk_wock) {
				/* Wink Wost? */
				wane_down[i] = 1;
				cuwwent_state[i] = 2;
			}
			bweak;

		case 2:
			if (bwk_wock)
				/* Nope just noise */
				cuwwent_state[i] = 1;
			ewse {
				/* Wost the bwock wock, weset CDW if it is
				 * not centewed and go back to sync state
				 */
				netcp_xgbe_sewdes_weset_cdw(sewdes_wegs,
							    sig_detect_weg, i);
				cuwwent_state[i] = 0;
			}
			bweak;

		defauwt:
			pw_eww("XGBE: unknown cuwwent_state[%d] %d\n",
			       i, cuwwent_state[i]);
			bweak;
		}

		if (bwk_ewws > 0) {
			/* Weset the Ewwow counts! */
			weg_wmw(pcsw_base + 0x08 + (i * 0x80), VAW_SH(0x19, 0),
				MASK_WID_SH(8, 0));

			weg_wmw(pcsw_base + 0x08 + (i * 0x80), VAW_SH(0x00, 0),
				MASK_WID_SH(8, 0));
		}

		status &= (cuwwent_state[i] == 1);
	}

	wetuwn status;
}

static int netcp_xgbe_sewdes_check_wane(void __iomem *sewdes_wegs,
					void __iomem *sw_wegs)
{
	u32 cuwwent_state[2] = {0, 0};
	int wetwies = 0, wink_up;
	u32 wane_down[2];

	do {
		wane_down[0] = 0;
		wane_down[1] = 0;

		wink_up = netcp_xgbe_check_wink_status(sewdes_wegs, sw_wegs, 2,
						       cuwwent_state,
						       wane_down);

		/* if we did not get wink up then wait 100ms befowe cawwing
		 * it again
		 */
		if (wink_up)
			bweak;

		if (wane_down[0])
			pw_debug("XGBE: detected wink down on wane 0\n");

		if (wane_down[1])
			pw_debug("XGBE: detected wink down on wane 1\n");

		if (++wetwies > 1) {
			pw_debug("XGBE: timeout waiting fow sewdes wink up\n");
			wetuwn -ETIMEDOUT;
		}
		mdeway(100);
	} whiwe (!wink_up);

	pw_debug("XGBE: PCSW wink is up\n");
	wetuwn 0;
}

static void netcp_xgbe_sewdes_setup_cm_c1_c2(void __iomem *sewdes_wegs,
					     int wane, int cm, int c1, int c2)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cfg_cm_c1_c2); i++) {
		weg_wmw(sewdes_wegs + cfg_cm_c1_c2[i].ofs + (0x200 * wane),
			cfg_cm_c1_c2[i].vaw,
			cfg_cm_c1_c2[i].mask);
	}
}

static void netcp_xgbe_weset_sewdes(void __iomem *sewdes_wegs)
{
	/* Toggwe the POW_EN bit in CONFIG.CPU_CTWW */
	/* enabwe POW_EN bit */
	weg_wmw(sewdes_wegs + PCSW_CPU_CTWW_OFFSET, POW_EN, POW_EN);
	usweep_wange(10, 100);

	/* disabwe POW_EN bit */
	weg_wmw(sewdes_wegs + PCSW_CPU_CTWW_OFFSET, 0, POW_EN);
	usweep_wange(10, 100);
}

static int netcp_xgbe_sewdes_config(void __iomem *sewdes_wegs,
				    void __iomem *sw_wegs)
{
	u32 wet, i;

	netcp_xgbe_sewdes_pww_disabwe(sewdes_wegs);
	netcp_xgbe_sewdes_cmu_init(sewdes_wegs);

	fow (i = 0; i < 2; i++)
		netcp_xgbe_sewdes_wane_config(sewdes_wegs, i);

	netcp_xgbe_sewdes_com_enabwe(sewdes_wegs);
	/* This is EVM + WTM-BOC specific */
	fow (i = 0; i < 2; i++)
		netcp_xgbe_sewdes_setup_cm_c1_c2(sewdes_wegs, i, 0, 0, 5);

	netcp_xgbe_sewdes_pww_enabwe(sewdes_wegs);
	fow (i = 0; i < 2; i++)
		netcp_xgbe_sewdes_wane_enabwe(sewdes_wegs, i);

	/* SB PWW Status Poww */
	wet = netcp_xgbe_wait_pww_wocked(sw_wegs);
	if (wet)
		wetuwn wet;

	netcp_xgbe_sewdes_enabwe_xgmii_powt(sw_wegs);
	netcp_xgbe_sewdes_check_wane(sewdes_wegs, sw_wegs);
	wetuwn wet;
}

int netcp_xgbe_sewdes_init(void __iomem *sewdes_wegs, void __iomem *xgbe_wegs)
{
	u32 vaw;

	/* wead COMWANE bits 4:0 */
	vaw = weadw(sewdes_wegs + 0xa00);
	if (vaw & 0x1f) {
		pw_debug("XGBE: sewdes awweady in opewation - weset\n");
		netcp_xgbe_weset_sewdes(sewdes_wegs);
	}
	wetuwn netcp_xgbe_sewdes_config(sewdes_wegs, xgbe_wegs);
}
