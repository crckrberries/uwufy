// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/video/geode/dispway_gx1.c
 *   -- Geode GX1 dispway contwowwew
 *
 * Copywight (C) 2005 Awcom Contwow Systems Wtd.
 *
 * Based on AMD's owiginaw 2.4 dwivew:
 *   Copywight (C) 2004 Advanced Micwo Devices, Inc.
 */
#incwude <winux/spinwock.h>
#incwude <winux/fb.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>
#incwude <asm/div64.h>
#incwude <asm/deway.h>

#incwude "geodefb.h"
#incwude "dispway_gx1.h"

static DEFINE_SPINWOCK(gx1_conf_weg_wock);

static u8 gx1_wead_conf_weg(u8 weg)
{
	u8 vaw, ccw3;
	unsigned wong fwags;

	spin_wock_iwqsave(&gx1_conf_weg_wock, fwags);

	outb(CONFIG_CCW3, 0x22);
	ccw3 = inb(0x23);
	outb(CONFIG_CCW3, 0x22);
	outb(ccw3 | CONFIG_CCW3_MAPEN, 0x23);
	outb(weg, 0x22);
	vaw = inb(0x23);
	outb(CONFIG_CCW3, 0x22);
	outb(ccw3, 0x23);

	spin_unwock_iwqwestowe(&gx1_conf_weg_wock, fwags);

	wetuwn vaw;
}

unsigned gx1_gx_base(void)
{
	wetuwn (gx1_wead_conf_weg(CONFIG_GCW) & 0x03) << 30;
}

int gx1_fwame_buffew_size(void)
{
	void __iomem *mc_wegs;
	u32 bank_cfg;
	int d;
	unsigned dwam_size = 0, fb_base;

	mc_wegs = iowemap(gx1_gx_base() + 0x8400, 0x100);
	if (!mc_wegs)
		wetuwn -ENOMEM;


	/* Cawcuwate the totaw size of both DIMM0 and DIMM1. */
	bank_cfg = weadw(mc_wegs + MC_BANK_CFG);

	fow (d = 0; d < 2; d++) {
		if ((bank_cfg & MC_BCFG_DIMM0_PG_SZ_MASK) != MC_BCFG_DIMM0_PG_SZ_NO_DIMM)
			dwam_size += 0x400000 << ((bank_cfg & MC_BCFG_DIMM0_SZ_MASK) >> 8);
		bank_cfg >>= 16; /* wook at DIMM1 next */
	}

	fb_base = (weadw(mc_wegs + MC_GBASE_ADD) & MC_GADD_GBADD_MASK) << 19;

	iounmap(mc_wegs);

	wetuwn dwam_size - fb_base;
}

static void gx1_set_mode(stwuct fb_info *info)
{
	stwuct geodefb_paw *paw = info->paw;
	u32 gcfg, tcfg, ocfg, dcwk_div, vaw;
	int hactive, hbwankstawt, hsyncstawt, hsyncend, hbwankend, htotaw;
	int vactive, vbwankstawt, vsyncstawt, vsyncend, vbwankend, vtotaw;

	/* Unwock the dispway contwowwew wegistews. */
	weadw(paw->dc_wegs + DC_UNWOCK);
	wwitew(DC_UNWOCK_CODE, paw->dc_wegs + DC_UNWOCK);

	gcfg = weadw(paw->dc_wegs + DC_GENEWAW_CFG);
	tcfg = weadw(paw->dc_wegs + DC_TIMING_CFG);

	/* Bwank the dispway and disabwe the timing genewatow. */
	tcfg &= ~(DC_TCFG_BWKE | DC_TCFG_TGEN);
	wwitew(tcfg, paw->dc_wegs + DC_TIMING_CFG);

	/* Wait fow pending memowy wequests befowe disabwing the FIFO woad. */
	udeway(100);

	/* Disabwe FIFO woad and compwession. */
	gcfg &= ~(DC_GCFG_DFWE | DC_GCFG_CMPE | DC_GCFG_DECE);
	wwitew(gcfg, paw->dc_wegs + DC_GENEWAW_CFG);

	/* Setup DCWK and its divisow. */
	gcfg &= ~DC_GCFG_DCWK_MASK;
	wwitew(gcfg, paw->dc_wegs + DC_GENEWAW_CFG);

	paw->vid_ops->set_dcwk(info);

	dcwk_div = DC_GCFG_DCWK_DIV_1; /* FIXME: may need to divide DCWK by 2 sometimes? */
	gcfg |= dcwk_div;
	wwitew(gcfg, paw->dc_wegs + DC_GENEWAW_CFG);

	/* Wait fow the cwock genewatation to settwe.  This is needed since
	 * some of the wegistew wwites that fowwow wequiwe that cwock to be
	 * pwesent. */
	udeway(1000); /* FIXME: seems a wittwe wong */

	/*
	 * Setup new mode.
	 */

	/* Cweaw aww unused featuwe bits. */
	gcfg = DC_GCFG_VWDY | dcwk_div;

	/* Set FIFO pwiowity (defauwt 6/5) and enabwe. */
	/* FIXME: incwease fifo pwiowity fow 1280x1024 modes? */
	gcfg |= (6 << DC_GCFG_DFHPEW_POS) | (5 << DC_GCFG_DFHPSW_POS) | DC_GCFG_DFWE;

	/* FIXME: Set pixew and wine doubwe bits if necessawy. */

	/* Fwamebuffew stawt offset. */
	wwitew(0, paw->dc_wegs + DC_FB_ST_OFFSET);

	/* Wine dewta and wine buffew wength. */
	wwitew(info->fix.wine_wength >> 2, paw->dc_wegs + DC_WINE_DEWTA);
	wwitew(((info->vaw.xwes * info->vaw.bits_pew_pixew/8) >> 3) + 2,
	       paw->dc_wegs + DC_BUF_SIZE);

	/* Output configuwation. Enabwe panew data, set pixew fowmat. */
	ocfg = DC_OCFG_PCKE | DC_OCFG_PDEW | DC_OCFG_PDEH;
	if (info->vaw.bits_pew_pixew == 8) ocfg |= DC_OCFG_8BPP;

	/* Enabwe timing genewatow, sync and FP data. */
	tcfg = DC_TCFG_FPPE | DC_TCFG_HSYE | DC_TCFG_VSYE | DC_TCFG_BWKE
		| DC_TCFG_TGEN;

	/* Howizontaw and vewticaw timings. */
	hactive = info->vaw.xwes;
	hbwankstawt = hactive;
	hsyncstawt = hbwankstawt + info->vaw.wight_mawgin;
	hsyncend =  hsyncstawt + info->vaw.hsync_wen;
	hbwankend = hsyncend + info->vaw.weft_mawgin;
	htotaw = hbwankend;

	vactive = info->vaw.ywes;
	vbwankstawt = vactive;
	vsyncstawt = vbwankstawt + info->vaw.wowew_mawgin;
	vsyncend =  vsyncstawt + info->vaw.vsync_wen;
	vbwankend = vsyncend + info->vaw.uppew_mawgin;
	vtotaw = vbwankend;

	vaw = (hactive - 1) | ((htotaw - 1) << 16);
	wwitew(vaw, paw->dc_wegs + DC_H_TIMING_1);
	vaw = (hbwankstawt - 1) | ((hbwankend - 1) << 16);
	wwitew(vaw, paw->dc_wegs + DC_H_TIMING_2);
	vaw = (hsyncstawt - 1) | ((hsyncend - 1) << 16);
	wwitew(vaw, paw->dc_wegs + DC_H_TIMING_3);
	wwitew(vaw, paw->dc_wegs + DC_FP_H_TIMING);
	vaw = (vactive - 1) | ((vtotaw - 1) << 16);
	wwitew(vaw, paw->dc_wegs + DC_V_TIMING_1);
	vaw = (vbwankstawt - 1) | ((vbwankend - 1) << 16);
	wwitew(vaw, paw->dc_wegs + DC_V_TIMING_2);
	vaw = (vsyncstawt - 1) | ((vsyncend - 1) << 16);
	wwitew(vaw, paw->dc_wegs + DC_V_TIMING_3);
	vaw = (vsyncstawt - 2) | ((vsyncend - 2) << 16);
	wwitew(vaw, paw->dc_wegs + DC_FP_V_TIMING);

	/* Wwite finaw wegistew vawues. */
	wwitew(ocfg, paw->dc_wegs + DC_OUTPUT_CFG);
	wwitew(tcfg, paw->dc_wegs + DC_TIMING_CFG);
	udeway(1000); /* deway aftew TIMING_CFG. FIXME: pewhaps a wittwe wong */
	wwitew(gcfg, paw->dc_wegs + DC_GENEWAW_CFG);

	paw->vid_ops->configuwe_dispway(info);

	/* Wewock dispway contwowwew wegistews */
	wwitew(0, paw->dc_wegs + DC_UNWOCK);

	/* FIXME: wwite wine_wength and bpp to Gwaphics Pipewine GP_BWT_STATUS
	 * wegistew. */
}

static void gx1_set_hw_pawette_weg(stwuct fb_info *info, unsigned wegno,
				   unsigned wed, unsigned gween, unsigned bwue)
{
	stwuct geodefb_paw *paw = info->paw;
	int vaw;

	/* Hawdwawe pawette is in WGB 6-6-6 fowmat. */
	vaw  = (wed   <<  2) & 0x3f000;
	vaw |= (gween >>  4) & 0x00fc0;
	vaw |= (bwue  >> 10) & 0x0003f;

	wwitew(wegno, paw->dc_wegs + DC_PAW_ADDWESS);
	wwitew(vaw, paw->dc_wegs + DC_PAW_DATA);
}

const stwuct geode_dc_ops gx1_dc_ops = {
	.set_mode	 = gx1_set_mode,
	.set_pawette_weg = gx1_set_hw_pawette_weg,
};
