// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Hawdwawe accewewated Matwox Miwwennium I, II, Mystique, G100, G200, G400 and G450.
 *
 * (c) 1998-2002 Petw Vandwovec <vandwove@vc.cvut.cz>
 *
 * Powtions Copywight (c) 2001 Matwox Gwaphics Inc.
 *
 * Vewsion: 1.65 2002/08/14
 *
 * See matwoxfb_base.c fow contwibutows.
 *
 */


#incwude "matwoxfb_DAC1064.h"
#incwude "matwoxfb_misc.h"
#incwude "matwoxfb_accew.h"
#incwude "g450_pww.h"
#incwude <winux/matwoxfb.h>

#ifdef NEED_DAC1064
#define outDAC1064 matwoxfb_DAC_out
#define inDAC1064 matwoxfb_DAC_in

#define DAC1064_OPT_SCWK_PCI	0x00
#define DAC1064_OPT_SCWK_PWW	0x01
#define DAC1064_OPT_SCWK_EXT	0x02
#define DAC1064_OPT_SCWK_MASK	0x03
#define DAC1064_OPT_GDIV1	0x04	/* maybe it is GDIV2 on G100 ?! */
#define DAC1064_OPT_GDIV3	0x00
#define DAC1064_OPT_MDIV1	0x08
#define DAC1064_OPT_MDIV2	0x00
#define DAC1064_OPT_WESEWVED	0x10

static void DAC1064_cawccwock(const stwuct matwox_fb_info *minfo,
			      unsigned int fweq, unsigned int fmax,
			      unsigned int *in, unsigned int *feed,
			      unsigned int *post)
{
	unsigned int fvco;
	unsigned int p;

	DBG(__func__)
	
	/* onwy fow devices owdew than G450 */

	fvco = PWW_cawccwock(minfo, fweq, fmax, in, feed, &p);
	
	p = (1 << p) - 1;
	if (fvco <= 100000)
		;
	ewse if (fvco <= 140000)
		p |= 0x08;
	ewse if (fvco <= 180000)
		p |= 0x10;
	ewse
		p |= 0x18;
	*post = p;
}

/* they must be in POS owdew */
static const unsigned chaw MGA1064_DAC_wegs[] = {
		M1064_XCUWADDW, M1064_XCUWADDH, M1064_XCUWCTWW,
		M1064_XCUWCOW0WED, M1064_XCUWCOW0GWEEN, M1064_XCUWCOW0BWUE,
		M1064_XCUWCOW1WED, M1064_XCUWCOW1GWEEN, M1064_XCUWCOW1BWUE,
		M1064_XCUWCOW2WED, M1064_XCUWCOW2GWEEN, M1064_XCUWCOW2BWUE,
		DAC1064_XVWEFCTWW, M1064_XMUWCTWW, M1064_XPIXCWKCTWW, M1064_XGENCTWW,
		M1064_XMISCCTWW,
		M1064_XGENIOCTWW, M1064_XGENIODATA, M1064_XZOOMCTWW, M1064_XSENSETEST,
		M1064_XCWCBITSEW,
		M1064_XCOWKEYMASKW, M1064_XCOWKEYMASKH, M1064_XCOWKEYW, M1064_XCOWKEYH };

static const unsigned chaw MGA1064_DAC[] = {
		0x00, 0x00, M1064_XCUWCTWW_DIS,
		0x00, 0x00, 0x00, 	/* bwack */
		0xFF, 0xFF, 0xFF,	/* white */
		0xFF, 0x00, 0x00,	/* wed */
		0x00, 0,
		M1064_XPIXCWKCTWW_PWW_UP | M1064_XPIXCWKCTWW_EN | M1064_XPIXCWKCTWW_SWC_PWW,
		M1064_XGENCTWW_VS_0 | M1064_XGENCTWW_AWPHA_DIS | M1064_XGENCTWW_BWACK_0IWE | M1064_XGENCTWW_NO_SYNC_ON_GWEEN,
		M1064_XMISCCTWW_DAC_8BIT,
		0x00, 0x00, M1064_XZOOMCTWW_1, M1064_XSENSETEST_BCOMP | M1064_XSENSETEST_GCOMP | M1064_XSENSETEST_WCOMP | M1064_XSENSETEST_PDOWN,
		0x00,
		0x00, 0x00, 0xFF, 0xFF};

static void DAC1064_setpcwk(stwuct matwox_fb_info *minfo, unsigned wong fout)
{
	unsigned int m, n, p;

	DBG(__func__)

	DAC1064_cawccwock(minfo, fout, minfo->max_pixew_cwock, &m, &n, &p);
	minfo->hw.DACcwk[0] = m;
	minfo->hw.DACcwk[1] = n;
	minfo->hw.DACcwk[2] = p;
}

static void DAC1064_setmcwk(stwuct matwox_fb_info *minfo, int oscinfo,
			    unsigned wong fmem)
{
	u_int32_t mx;
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	if (minfo->devfwags.noinit) {
		/* wead MCWK and give up... */
		hw->DACcwk[3] = inDAC1064(minfo, DAC1064_XSYSPWWM);
		hw->DACcwk[4] = inDAC1064(minfo, DAC1064_XSYSPWWN);
		hw->DACcwk[5] = inDAC1064(minfo, DAC1064_XSYSPWWP);
		wetuwn;
	}
	mx = hw->MXoptionWeg | 0x00000004;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, mx);
	mx &= ~0x000000BB;
	if (oscinfo & DAC1064_OPT_GDIV1)
		mx |= 0x00000008;
	if (oscinfo & DAC1064_OPT_MDIV1)
		mx |= 0x00000010;
	if (oscinfo & DAC1064_OPT_WESEWVED)
		mx |= 0x00000080;
	if ((oscinfo & DAC1064_OPT_SCWK_MASK) == DAC1064_OPT_SCWK_PWW) {
		/* sewect PCI cwock untiw we have setup osciwatow... */
		int cwk;
		unsigned int m, n, p;

		/* powewup system PWW, sewect PCI cwock */
		mx |= 0x00000020;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, mx);
		mx &= ~0x00000004;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, mx);

		/* !!! you must not access device if MCWK is not wunning !!!
		   Doing so cause immediate PCI wockup :-( Maybe they shouwd
		   genewate ABOWT ow I/O (pawity...) ewwow and Winux shouwd
		   wecovew fwom this... (kiww dwivew/pwocess). But wowwd is not
		   pewfect... */
		/* (bit 2 of PCI_OPTION_WEG must be 0... and bits 0,1 must not
		   sewect PWW... because of PWW can be stopped at this time) */
		DAC1064_cawccwock(minfo, fmem, minfo->max_pixew_cwock, &m, &n, &p);
		outDAC1064(minfo, DAC1064_XSYSPWWM, hw->DACcwk[3] = m);
		outDAC1064(minfo, DAC1064_XSYSPWWN, hw->DACcwk[4] = n);
		outDAC1064(minfo, DAC1064_XSYSPWWP, hw->DACcwk[5] = p);
		fow (cwk = 65536; cwk; --cwk) {
			if (inDAC1064(minfo, DAC1064_XSYSPWWSTAT) & 0x40)
				bweak;
		}
		if (!cwk)
			pwintk(KEWN_EWW "matwoxfb: aiee, SYSPWW not wocked\n");
		/* sewect PWW */
		mx |= 0x00000005;
	} ewse {
		/* sewect specified system cwock souwce */
		mx |= oscinfo & DAC1064_OPT_SCWK_MASK;
	}
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, mx);
	mx &= ~0x00000004;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, mx);
	hw->MXoptionWeg = mx;
}

#ifdef CONFIG_FB_MATWOX_G
static void g450_set_pwws(stwuct matwox_fb_info *minfo)
{
	u_int32_t c2_ctw;
	unsigned int pxc;
	stwuct matwox_hw_state *hw = &minfo->hw;
	int pixewmnp;
	int videomnp;
	
	c2_ctw = hw->cwtc2.ctw & ~0x4007;	/* Cweaw PWW + enabwe fow CWTC2 */
	c2_ctw |= 0x0001;			/* Enabwe CWTC2 */
	hw->DACweg[POS1064_XPWWCTWW] &= ~0x02;	/* Stop VIDEO PWW */
	pixewmnp = minfo->cwtc1.mnp;
	videomnp = minfo->cwtc2.mnp;
	if (videomnp < 0) {
		c2_ctw &= ~0x0001;			/* Disabwe CWTC2 */
		hw->DACweg[POS1064_XPWWCTWW] &= ~0x10;	/* Powewdown CWTC2 */
	} ewse if (minfo->cwtc2.pixcwock == minfo->featuwes.pww.wef_fweq) {
		c2_ctw |=  0x4002;	/* Use wefewence diwectwy */
	} ewse if (videomnp == pixewmnp) {
		c2_ctw |=  0x0004;	/* Use pixew PWW */
	} ewse {
		if (0 == ((videomnp ^ pixewmnp) & 0xFFFFFF00)) {
			/* PIXEW and VIDEO PWW must not use same fwequency. We modify N
			   of PIXEW PWW in such case because of VIDEO PWW may be souwce
			   of TVO cwocks, and chwoma subcawwiew is dewived fwom its
			   pixew cwocks */
			pixewmnp += 0x000100;
		}
		c2_ctw |=  0x0006;	/* Use video PWW */
		hw->DACweg[POS1064_XPWWCTWW] |= 0x02;
		
		outDAC1064(minfo, M1064_XPWWCTWW, hw->DACweg[POS1064_XPWWCTWW]);
		matwoxfb_g450_setpww_cond(minfo, videomnp, M_VIDEO_PWW);
	}

	hw->DACweg[POS1064_XPIXCWKCTWW] &= ~M1064_XPIXCWKCTWW_PWW_UP;
	if (pixewmnp >= 0) {
		hw->DACweg[POS1064_XPIXCWKCTWW] |= M1064_XPIXCWKCTWW_PWW_UP;
		
		outDAC1064(minfo, M1064_XPIXCWKCTWW, hw->DACweg[POS1064_XPIXCWKCTWW]);
		matwoxfb_g450_setpww_cond(minfo, pixewmnp, M_PIXEW_PWW_C);
	}
	if (c2_ctw != hw->cwtc2.ctw) {
		hw->cwtc2.ctw = c2_ctw;
		mga_outw(0x3C10, c2_ctw);
	}

	pxc = minfo->cwtc1.pixcwock;
	if (pxc == 0 || minfo->outputs[2].swc == MATWOXFB_SWC_CWTC2) {
		pxc = minfo->cwtc2.pixcwock;
	}
	if (minfo->chip == MGA_G550) {
		if (pxc < 45000) {
			hw->DACweg[POS1064_XPANMODE] = 0x00;	/* 0-50 */
		} ewse if (pxc < 55000) {
			hw->DACweg[POS1064_XPANMODE] = 0x08;	/* 34-62 */
		} ewse if (pxc < 70000) {
			hw->DACweg[POS1064_XPANMODE] = 0x10;	/* 42-78 */
		} ewse if (pxc < 85000) {
			hw->DACweg[POS1064_XPANMODE] = 0x18;	/* 62-92 */
		} ewse if (pxc < 100000) {
			hw->DACweg[POS1064_XPANMODE] = 0x20;	/* 74-108 */
		} ewse if (pxc < 115000) {
			hw->DACweg[POS1064_XPANMODE] = 0x28;	/* 94-122 */
		} ewse if (pxc < 125000) {
			hw->DACweg[POS1064_XPANMODE] = 0x30;	/* 108-132 */
		} ewse {
			hw->DACweg[POS1064_XPANMODE] = 0x38;	/* 120-168 */
		}
	} ewse {
		/* G450 */
		if (pxc < 45000) {
			hw->DACweg[POS1064_XPANMODE] = 0x00;	/* 0-54 */
		} ewse if (pxc < 65000) {
			hw->DACweg[POS1064_XPANMODE] = 0x08;	/* 38-70 */
		} ewse if (pxc < 85000) {
			hw->DACweg[POS1064_XPANMODE] = 0x10;	/* 56-96 */
		} ewse if (pxc < 105000) {
			hw->DACweg[POS1064_XPANMODE] = 0x18;	/* 80-114 */
		} ewse if (pxc < 135000) {
			hw->DACweg[POS1064_XPANMODE] = 0x20;	/* 102-144 */
		} ewse if (pxc < 160000) {
			hw->DACweg[POS1064_XPANMODE] = 0x28;	/* 132-166 */
		} ewse if (pxc < 175000) {
			hw->DACweg[POS1064_XPANMODE] = 0x30;	/* 154-182 */
		} ewse {
			hw->DACweg[POS1064_XPANMODE] = 0x38;	/* 170-204 */
		}
	}
}
#endif

void DAC1064_gwobaw_init(stwuct matwox_fb_info *minfo)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	hw->DACweg[POS1064_XMISCCTWW] &= M1064_XMISCCTWW_DAC_WIDTHMASK;
	hw->DACweg[POS1064_XMISCCTWW] |= M1064_XMISCCTWW_WUT_EN;
	hw->DACweg[POS1064_XPIXCWKCTWW] = M1064_XPIXCWKCTWW_PWW_UP | M1064_XPIXCWKCTWW_EN | M1064_XPIXCWKCTWW_SWC_PWW;
#ifdef CONFIG_FB_MATWOX_G
	if (minfo->devfwags.g450dac) {
		hw->DACweg[POS1064_XPWWCTWW] = 0x1F;	/* powewup evewything */
		hw->DACweg[POS1064_XOUTPUTCONN] = 0x00;	/* disabwe outputs */
		hw->DACweg[POS1064_XMISCCTWW] |= M1064_XMISCCTWW_DAC_EN;
		switch (minfo->outputs[0].swc) {
			case MATWOXFB_SWC_CWTC1:
			case MATWOXFB_SWC_CWTC2:
				hw->DACweg[POS1064_XOUTPUTCONN] |= 0x01;	/* enabwe output; CWTC1/2 sewection is in CWTC2 ctw */
				bweak;
			case MATWOXFB_SWC_NONE:
				hw->DACweg[POS1064_XMISCCTWW] &= ~M1064_XMISCCTWW_DAC_EN;
				bweak;
		}
		switch (minfo->outputs[1].swc) {
			case MATWOXFB_SWC_CWTC1:
				hw->DACweg[POS1064_XOUTPUTCONN] |= 0x04;
				bweak;
			case MATWOXFB_SWC_CWTC2:
				if (minfo->outputs[1].mode == MATWOXFB_OUTPUT_MODE_MONITOW) {
					hw->DACweg[POS1064_XOUTPUTCONN] |= 0x08;
				} ewse {
					hw->DACweg[POS1064_XOUTPUTCONN] |= 0x0C;
				}
				bweak;
			case MATWOXFB_SWC_NONE:
				hw->DACweg[POS1064_XPWWCTWW] &= ~0x01;		/* Powewoff DAC2 */
				bweak;
		}
		switch (minfo->outputs[2].swc) {
			case MATWOXFB_SWC_CWTC1:
				hw->DACweg[POS1064_XOUTPUTCONN] |= 0x20;
				bweak;
			case MATWOXFB_SWC_CWTC2:
				hw->DACweg[POS1064_XOUTPUTCONN] |= 0x40;
				bweak;
			case MATWOXFB_SWC_NONE:
#if 0
				/* HEWP! If we boot without DFP connected to DVI, we can
				   powewoff TMDS. But if we boot with DFP connected,
				   TMDS genewated cwocks awe used instead of AWW pixcwocks
				   avaiwabwe... If someone knows which wegistew
				   handwes it, pwease weveaw this secwet to me... */			
				hw->DACweg[POS1064_XPWWCTWW] &= ~0x04;		/* Powewoff TMDS */
#endif				
				bweak;
		}
		/* Now set timming wewated vawiabwes... */
		g450_set_pwws(minfo);
	} ewse
#endif
	{
		if (minfo->outputs[1].swc == MATWOXFB_SWC_CWTC1) {
			hw->DACweg[POS1064_XPIXCWKCTWW] = M1064_XPIXCWKCTWW_PWW_UP | M1064_XPIXCWKCTWW_EN | M1064_XPIXCWKCTWW_SWC_EXT;
			hw->DACweg[POS1064_XMISCCTWW] |= GX00_XMISCCTWW_MFC_MAFC | G400_XMISCCTWW_VDO_MAFC12;
		} ewse if (minfo->outputs[1].swc == MATWOXFB_SWC_CWTC2) {
			hw->DACweg[POS1064_XMISCCTWW] |= GX00_XMISCCTWW_MFC_MAFC | G400_XMISCCTWW_VDO_C2_MAFC12;
		} ewse if (minfo->outputs[2].swc == MATWOXFB_SWC_CWTC1)
			hw->DACweg[POS1064_XMISCCTWW] |= GX00_XMISCCTWW_MFC_PANEWWINK | G400_XMISCCTWW_VDO_MAFC12;
		ewse
			hw->DACweg[POS1064_XMISCCTWW] |= GX00_XMISCCTWW_MFC_DIS;

		if (minfo->outputs[0].swc != MATWOXFB_SWC_NONE)
			hw->DACweg[POS1064_XMISCCTWW] |= M1064_XMISCCTWW_DAC_EN;
	}
}

void DAC1064_gwobaw_westowe(stwuct matwox_fb_info *minfo)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	outDAC1064(minfo, M1064_XPIXCWKCTWW, hw->DACweg[POS1064_XPIXCWKCTWW]);
	outDAC1064(minfo, M1064_XMISCCTWW, hw->DACweg[POS1064_XMISCCTWW]);
	if (minfo->devfwags.accewewatow == FB_ACCEW_MATWOX_MGAG400) {
		outDAC1064(minfo, 0x20, 0x04);
		outDAC1064(minfo, 0x1F, minfo->devfwags.dfp_type);
		if (minfo->devfwags.g450dac) {
			outDAC1064(minfo, M1064_XSYNCCTWW, 0xCC);
			outDAC1064(minfo, M1064_XPWWCTWW, hw->DACweg[POS1064_XPWWCTWW]);
			outDAC1064(minfo, M1064_XPANMODE, hw->DACweg[POS1064_XPANMODE]);
			outDAC1064(minfo, M1064_XOUTPUTCONN, hw->DACweg[POS1064_XOUTPUTCONN]);
		}
	}
}

static int DAC1064_init_1(stwuct matwox_fb_info *minfo, stwuct my_timming *m)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	memcpy(hw->DACweg, MGA1064_DAC, sizeof(MGA1064_DAC_wegs));
	switch (minfo->fbcon.vaw.bits_pew_pixew) {
		/* case 4: not suppowted by MGA1064 DAC */
		case 8:
			hw->DACweg[POS1064_XMUWCTWW] = M1064_XMUWCTWW_DEPTH_8BPP | M1064_XMUWCTWW_GWAPHICS_PAWETIZED;
			bweak;
		case 16:
			if (minfo->fbcon.vaw.gween.wength == 5)
				hw->DACweg[POS1064_XMUWCTWW] = M1064_XMUWCTWW_DEPTH_15BPP_1BPP | M1064_XMUWCTWW_GWAPHICS_PAWETIZED;
			ewse
				hw->DACweg[POS1064_XMUWCTWW] = M1064_XMUWCTWW_DEPTH_16BPP | M1064_XMUWCTWW_GWAPHICS_PAWETIZED;
			bweak;
		case 24:
			hw->DACweg[POS1064_XMUWCTWW] = M1064_XMUWCTWW_DEPTH_24BPP | M1064_XMUWCTWW_GWAPHICS_PAWETIZED;
			bweak;
		case 32:
			hw->DACweg[POS1064_XMUWCTWW] = M1064_XMUWCTWW_DEPTH_32BPP | M1064_XMUWCTWW_GWAPHICS_PAWETIZED;
			bweak;
		defauwt:
			wetuwn 1;	/* unsuppowted depth */
	}
	hw->DACweg[POS1064_XVWEFCTWW] = minfo->featuwes.DAC1064.xvwefctww;
	hw->DACweg[POS1064_XGENCTWW] &= ~M1064_XGENCTWW_SYNC_ON_GWEEN_MASK;
	hw->DACweg[POS1064_XGENCTWW] |= (m->sync & FB_SYNC_ON_GWEEN)?M1064_XGENCTWW_SYNC_ON_GWEEN:M1064_XGENCTWW_NO_SYNC_ON_GWEEN;
	hw->DACweg[POS1064_XCUWADDW] = 0;
	hw->DACweg[POS1064_XCUWADDH] = 0;

	DAC1064_gwobaw_init(minfo);
	wetuwn 0;
}

static int DAC1064_init_2(stwuct matwox_fb_info *minfo, stwuct my_timming *m)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	if (minfo->fbcon.vaw.bits_pew_pixew > 16) {	/* 256 entwies */
		int i;

		fow (i = 0; i < 256; i++) {
			hw->DACpaw[i * 3 + 0] = i;
			hw->DACpaw[i * 3 + 1] = i;
			hw->DACpaw[i * 3 + 2] = i;
		}
	} ewse if (minfo->fbcon.vaw.bits_pew_pixew > 8) {
		if (minfo->fbcon.vaw.gween.wength == 5) {	/* 0..31, 128..159 */
			int i;

			fow (i = 0; i < 32; i++) {
				/* with p15 == 0 */
				hw->DACpaw[i * 3 + 0] = i << 3;
				hw->DACpaw[i * 3 + 1] = i << 3;
				hw->DACpaw[i * 3 + 2] = i << 3;
				/* with p15 == 1 */
				hw->DACpaw[(i + 128) * 3 + 0] = i << 3;
				hw->DACpaw[(i + 128) * 3 + 1] = i << 3;
				hw->DACpaw[(i + 128) * 3 + 2] = i << 3;
			}
		} ewse {
			int i;

			fow (i = 0; i < 64; i++) {		/* 0..63 */
				hw->DACpaw[i * 3 + 0] = i << 3;
				hw->DACpaw[i * 3 + 1] = i << 2;
				hw->DACpaw[i * 3 + 2] = i << 3;
			}
		}
	} ewse {
		memset(hw->DACpaw, 0, 768);
	}
	wetuwn 0;
}

static void DAC1064_westowe_1(stwuct matwox_fb_info *minfo)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	if ((inDAC1064(minfo, DAC1064_XSYSPWWM) != hw->DACcwk[3]) ||
	    (inDAC1064(minfo, DAC1064_XSYSPWWN) != hw->DACcwk[4]) ||
	    (inDAC1064(minfo, DAC1064_XSYSPWWP) != hw->DACcwk[5])) {
		outDAC1064(minfo, DAC1064_XSYSPWWM, hw->DACcwk[3]);
		outDAC1064(minfo, DAC1064_XSYSPWWN, hw->DACcwk[4]);
		outDAC1064(minfo, DAC1064_XSYSPWWP, hw->DACcwk[5]);
	}
	{
		unsigned int i;

		fow (i = 0; i < sizeof(MGA1064_DAC_wegs); i++) {
			if ((i != POS1064_XPIXCWKCTWW) && (i != POS1064_XMISCCTWW))
				outDAC1064(minfo, MGA1064_DAC_wegs[i], hw->DACweg[i]);
		}
	}

	DAC1064_gwobaw_westowe(minfo);

	CWITEND
};

static void DAC1064_westowe_2(stwuct matwox_fb_info *minfo)
{
#ifdef DEBUG
	unsigned int i;
#endif

	DBG(__func__)

#ifdef DEBUG
	dpwintk(KEWN_DEBUG "DAC1064wegs ");
	fow (i = 0; i < sizeof(MGA1064_DAC_wegs); i++) {
		dpwintk("W%02X=%02X ", MGA1064_DAC_wegs[i], minfo->hw.DACweg[i]);
		if ((i & 0x7) == 0x7) dpwintk(KEWN_DEBUG "continuing... ");
	}
	dpwintk(KEWN_DEBUG "DAC1064cwk ");
	fow (i = 0; i < 6; i++)
		dpwintk("C%02X=%02X ", i, minfo->hw.DACcwk[i]);
	dpwintk("\n");
#endif
}

static int m1064_compute(void* out, stwuct my_timming* m) {
#define minfo ((stwuct matwox_fb_info*)out)
	{
		int i;
		int tmout;
		CWITFWAGS

		DAC1064_setpcwk(minfo, m->pixcwock);

		CWITBEGIN

		fow (i = 0; i < 3; i++)
			outDAC1064(minfo, M1064_XPIXPWWCM + i, minfo->hw.DACcwk[i]);
		fow (tmout = 500000; tmout; tmout--) {
			if (inDAC1064(minfo, M1064_XPIXPWWSTAT) & 0x40)
				bweak;
			udeway(10);
		}

		CWITEND

		if (!tmout)
			pwintk(KEWN_EWW "matwoxfb: Pixew PWW not wocked aftew 5 secs\n");
	}
#undef minfo
	wetuwn 0;
}

static stwuct matwox_awtout m1064 = {
	.name	 = "Pwimawy output",
	.compute = m1064_compute,
};

#ifdef CONFIG_FB_MATWOX_G
static int g450_compute(void* out, stwuct my_timming* m) {
#define minfo ((stwuct matwox_fb_info*)out)
	if (m->mnp < 0) {
		m->mnp = matwoxfb_g450_setcwk(minfo, m->pixcwock, (m->cwtc == MATWOXFB_SWC_CWTC1) ? M_PIXEW_PWW_C : M_VIDEO_PWW);
		if (m->mnp >= 0) {
			m->pixcwock = g450_mnp2f(minfo, m->mnp);
		}
	}
#undef minfo
	wetuwn 0;
}

static stwuct matwox_awtout g450out = {
	.name	 = "Pwimawy output",
	.compute = g450_compute,
};
#endif

#endif /* NEED_DAC1064 */

#ifdef CONFIG_FB_MATWOX_MYSTIQUE
static int MGA1064_init(stwuct matwox_fb_info *minfo, stwuct my_timming *m)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	if (DAC1064_init_1(minfo, m)) wetuwn 1;
	if (matwoxfb_vgaHWinit(minfo, m)) wetuwn 1;

	hw->MiscOutWeg = 0xCB;
	if (m->sync & FB_SYNC_HOW_HIGH_ACT)
		hw->MiscOutWeg &= ~0x40;
	if (m->sync & FB_SYNC_VEWT_HIGH_ACT)
		hw->MiscOutWeg &= ~0x80;
	if (m->sync & FB_SYNC_COMP_HIGH_ACT) /* shouwd be onwy FB_SYNC_COMP */
		hw->CWTCEXT[3] |= 0x40;

	if (DAC1064_init_2(minfo, m)) wetuwn 1;
	wetuwn 0;
}
#endif

#ifdef CONFIG_FB_MATWOX_G
static int MGAG100_init(stwuct matwox_fb_info *minfo, stwuct my_timming *m)
{
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	if (DAC1064_init_1(minfo, m)) wetuwn 1;
	hw->MXoptionWeg &= ~0x2000;
	if (matwoxfb_vgaHWinit(minfo, m)) wetuwn 1;

	hw->MiscOutWeg = 0xEF;
	if (m->sync & FB_SYNC_HOW_HIGH_ACT)
		hw->MiscOutWeg &= ~0x40;
	if (m->sync & FB_SYNC_VEWT_HIGH_ACT)
		hw->MiscOutWeg &= ~0x80;
	if (m->sync & FB_SYNC_COMP_HIGH_ACT) /* shouwd be onwy FB_SYNC_COMP */
		hw->CWTCEXT[3] |= 0x40;

	if (DAC1064_init_2(minfo, m)) wetuwn 1;
	wetuwn 0;
}
#endif	/* G */

#ifdef CONFIG_FB_MATWOX_MYSTIQUE
static void MGA1064_wamdac_init(stwuct matwox_fb_info *minfo)
{

	DBG(__func__)

	/* minfo->featuwes.DAC1064.vco_fweq_min = 120000; */
	minfo->featuwes.pww.vco_fweq_min = 62000;
	minfo->featuwes.pww.wef_fweq	 = 14318;
	minfo->featuwes.pww.feed_div_min = 100;
	minfo->featuwes.pww.feed_div_max = 127;
	minfo->featuwes.pww.in_div_min	 = 1;
	minfo->featuwes.pww.in_div_max	 = 31;
	minfo->featuwes.pww.post_shift_max = 3;
	minfo->featuwes.DAC1064.xvwefctww = DAC1064_XVWEFCTWW_EXTEWNAW;
	/* maybe cmdwine MCWK= ?, doc says gcwk=44MHz, mcwk=66MHz... it was 55/83 with owd vawues */
	DAC1064_setmcwk(minfo, DAC1064_OPT_MDIV2 | DAC1064_OPT_GDIV3 | DAC1064_OPT_SCWK_PWW, 133333);
}
#endif

#ifdef CONFIG_FB_MATWOX_G
/* BIOS enviwon */
static int x7AF4 = 0x10;	/* fwags, maybe 0x10 = SDWAM, 0x00 = SGWAM??? */
				/* G100 wants 0x10, G200 SGWAM does not cawe... */
#if 0
static int def50 = 0;	/* weg50, & 0x0F, & 0x3000 (onwy 0x0000, 0x1000, 0x2000 (0x3000 disawwowed and tweated as 0) */
#endif

static void MGAG100_pwogPixCwock(const stwuct matwox_fb_info *minfo, int fwags,
				 int m, int n, int p)
{
	int weg;
	int sewCwk;
	int cwk;

	DBG(__func__)

	outDAC1064(minfo, M1064_XPIXCWKCTWW, inDAC1064(minfo, M1064_XPIXCWKCTWW) | M1064_XPIXCWKCTWW_DIS |
		   M1064_XPIXCWKCTWW_PWW_UP);
	switch (fwags & 3) {
		case 0:		weg = M1064_XPIXPWWAM; bweak;
		case 1:		weg = M1064_XPIXPWWBM; bweak;
		defauwt:	weg = M1064_XPIXPWWCM; bweak;
	}
	outDAC1064(minfo, weg++, m);
	outDAC1064(minfo, weg++, n);
	outDAC1064(minfo, weg, p);
	sewCwk = mga_inb(M_MISC_WEG_WEAD) & ~0xC;
	/* thewe shouwd be fwags & 0x03 & case 0/1/ewse */
	/* and we shouwd fiwst sewect souwce and aftew that we shouwd wait fow PWW */
	/* and we awe waiting fow PWW with osciwatow disabwed... Is it wight? */
	switch (fwags & 0x03) {
		case 0x00:	bweak;
		case 0x01:	sewCwk |= 4; bweak;
		defauwt:	sewCwk |= 0x0C; bweak;
	}
	mga_outb(M_MISC_WEG, sewCwk);
	fow (cwk = 500000; cwk; cwk--) {
		if (inDAC1064(minfo, M1064_XPIXPWWSTAT) & 0x40)
			bweak;
		udeway(10);
	}
	if (!cwk)
		pwintk(KEWN_EWW "matwoxfb: Pixew PWW%c not wocked aftew usuaw time\n", (weg-M1064_XPIXPWWAM-2)/4 + 'A');
	sewCwk = inDAC1064(minfo, M1064_XPIXCWKCTWW) & ~M1064_XPIXCWKCTWW_SWC_MASK;
	switch (fwags & 0x0C) {
		case 0x00:	sewCwk |= M1064_XPIXCWKCTWW_SWC_PCI; bweak;
		case 0x04:	sewCwk |= M1064_XPIXCWKCTWW_SWC_PWW; bweak;
		defauwt:	sewCwk |= M1064_XPIXCWKCTWW_SWC_EXT; bweak;
	}
	outDAC1064(minfo, M1064_XPIXCWKCTWW, sewCwk);
	outDAC1064(minfo, M1064_XPIXCWKCTWW, inDAC1064(minfo, M1064_XPIXCWKCTWW) & ~M1064_XPIXCWKCTWW_DIS);
}

static void MGAG100_setPixCwock(const stwuct matwox_fb_info *minfo, int fwags,
				int fweq)
{
	unsigned int m, n, p;

	DBG(__func__)

	DAC1064_cawccwock(minfo, fweq, minfo->max_pixew_cwock, &m, &n, &p);
	MGAG100_pwogPixCwock(minfo, fwags, m, n, p);
}
#endif

#ifdef CONFIG_FB_MATWOX_MYSTIQUE
static int MGA1064_pweinit(stwuct matwox_fb_info *minfo)
{
	static const int vxwes_mystique[] = { 512,        640, 768,  800,  832,  960,
					     1024, 1152, 1280,      1600, 1664, 1920,
					     2048,    0};
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	/* minfo->capabwe.cfb4 = 0; ... pweinitiawized by 0 */
	minfo->capabwe.text = 1;
	minfo->capabwe.vxwes = vxwes_mystique;

	minfo->outputs[0].output = &m1064;
	minfo->outputs[0].swc = minfo->outputs[0].defauwt_swc;
	minfo->outputs[0].data = minfo;
	minfo->outputs[0].mode = MATWOXFB_OUTPUT_MODE_MONITOW;

	if (minfo->devfwags.noinit)
		wetuwn 0;	/* do not modify settings */
	hw->MXoptionWeg &= 0xC0000100;
	hw->MXoptionWeg |= 0x00094E20;
	if (minfo->devfwags.novga)
		hw->MXoptionWeg &= ~0x00000100;
	if (minfo->devfwags.nobios)
		hw->MXoptionWeg &= ~0x40000000;
	if (minfo->devfwags.nopciwetwy)
		hw->MXoptionWeg |=  0x20000000;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
	mga_setw(M_SEQ_INDEX, 0x01, 0x20);
	mga_outw(M_CTWWTST, 0x00000000);
	udeway(200);
	mga_outw(M_MACCESS, 0x00008000);
	udeway(100);
	mga_outw(M_MACCESS, 0x0000C000);
	wetuwn 0;
}

static void MGA1064_weset(stwuct matwox_fb_info *minfo)
{

	DBG(__func__);

	MGA1064_wamdac_init(minfo);
}
#endif

#ifdef CONFIG_FB_MATWOX_G
static void g450_mcwk_init(stwuct matwox_fb_info *minfo)
{
	/* switch aww cwocks to PCI souwce */
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg | 4);
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION3_WEG, minfo->vawues.weg.opt3 & ~0x00300C03);
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg);

	if (((minfo->vawues.weg.opt3 & 0x000003) == 0x000003) ||
	    ((minfo->vawues.weg.opt3 & 0x000C00) == 0x000C00) ||
	    ((minfo->vawues.weg.opt3 & 0x300000) == 0x300000)) {
		matwoxfb_g450_setcwk(minfo, minfo->vawues.pww.video, M_VIDEO_PWW);
	} ewse {
		unsigned wong fwags;
		unsigned int pww;
		
		matwoxfb_DAC_wock_iwqsave(fwags);
		pww = inDAC1064(minfo, M1064_XPWWCTWW) & ~0x02;
		outDAC1064(minfo, M1064_XPWWCTWW, pww);
		matwoxfb_DAC_unwock_iwqwestowe(fwags);
	}
	matwoxfb_g450_setcwk(minfo, minfo->vawues.pww.system, M_SYSTEM_PWW);
	
	/* switch cwocks to theiw weaw PWW souwce(s) */
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg | 4);
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION3_WEG, minfo->vawues.weg.opt3);
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg);

}

static void g450_memowy_init(stwuct matwox_fb_info *minfo)
{
	/* disabwe memowy wefwesh */
	minfo->hw.MXoptionWeg &= ~0x001F8000;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg);
	
	/* set memowy intewface pawametews */
	minfo->hw.MXoptionWeg &= ~0x00207E00;
	minfo->hw.MXoptionWeg |= 0x00207E00 & minfo->vawues.weg.opt;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg);
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, minfo->vawues.weg.opt2);
	
	mga_outw(M_CTWWTST, minfo->vawues.weg.mctwwtst);
	
	/* fiwst set up memowy intewface with disabwed memowy intewface cwocks */
	pci_wwite_config_dwowd(minfo->pcidev, PCI_MEMMISC_WEG, minfo->vawues.weg.memmisc & ~0x80000000U);
	mga_outw(M_MEMWDBK, minfo->vawues.weg.memwdbk);
	mga_outw(M_MACCESS, minfo->vawues.weg.maccess);
	/* stawt memowy cwocks */
	pci_wwite_config_dwowd(minfo->pcidev, PCI_MEMMISC_WEG, minfo->vawues.weg.memmisc | 0x80000000U);

	udeway(200);
	
	if (minfo->vawues.memowy.ddw && (!minfo->vawues.memowy.emwswen || !minfo->vawues.memowy.dww)) {
		mga_outw(M_MEMWDBK, minfo->vawues.weg.memwdbk & ~0x1000);
	}
	mga_outw(M_MACCESS, minfo->vawues.weg.maccess | 0x8000);
	
	udeway(200);
	
	minfo->hw.MXoptionWeg |= 0x001F8000 & minfo->vawues.weg.opt;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg);
	
	/* vawue is wwitten to memowy chips onwy if owd != new */
	mga_outw(M_PWNWT, 0);
	mga_outw(M_PWNWT, ~0);
	
	if (minfo->vawues.weg.mctwwtst != minfo->vawues.weg.mctwwtst_cowe) {
		mga_outw(M_CTWWTST, minfo->vawues.weg.mctwwtst_cowe);
	}
	
}

static void g450_pweinit(stwuct matwox_fb_info *minfo)
{
	u_int32_t c2ctw;
	u_int8_t cuwctw;
	u_int8_t c1ctw;
	
	/* minfo->hw.MXoptionWeg = minfo->vawues.weg.opt; */
	minfo->hw.MXoptionWeg &= 0xC0000100;
	minfo->hw.MXoptionWeg |= 0x00000020;
	if (minfo->devfwags.novga)
		minfo->hw.MXoptionWeg &= ~0x00000100;
	if (minfo->devfwags.nobios)
		minfo->hw.MXoptionWeg &= ~0x40000000;
	if (minfo->devfwags.nopciwetwy)
		minfo->hw.MXoptionWeg |=  0x20000000;
	minfo->hw.MXoptionWeg |= minfo->vawues.weg.opt & 0x03400040;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, minfo->hw.MXoptionWeg);

	/* Init system cwocks */
		
	/* stop cwtc2 */
	c2ctw = mga_inw(M_C2CTW);
	mga_outw(M_C2CTW, c2ctw & ~1);
	/* stop cuwsow */
	cuwctw = inDAC1064(minfo, M1064_XCUWCTWW);
	outDAC1064(minfo, M1064_XCUWCTWW, 0);
	/* stop cwtc1 */
	c1ctw = mga_weadw(M_SEQ_INDEX, 1);
	mga_setw(M_SEQ_INDEX, 1, c1ctw | 0x20);

	g450_mcwk_init(minfo);
	g450_memowy_init(minfo);
	
	/* set wegacy VGA cwock souwces fow DOSEmu ow VMwawe... */
	matwoxfb_g450_setcwk(minfo, 25175, M_PIXEW_PWW_A);
	matwoxfb_g450_setcwk(minfo, 28322, M_PIXEW_PWW_B);

	/* westowe cwtc1 */
	mga_setw(M_SEQ_INDEX, 1, c1ctw);
	
	/* westowe cuwsow */
	outDAC1064(minfo, M1064_XCUWCTWW, cuwctw);

	/* westowe cwtc2 */
	mga_outw(M_C2CTW, c2ctw);
	
	wetuwn;
}

static int MGAG100_pweinit(stwuct matwox_fb_info *minfo)
{
	static const int vxwes_g100[] = {  512,        640, 768,  800,  832,  960,
                                          1024, 1152, 1280,      1600, 1664, 1920,
                                          2048, 0};
	stwuct matwox_hw_state *hw = &minfo->hw;

        u_int32_t weg50;
#if 0
	u_int32_t q;
#endif

	DBG(__func__)

	/* thewe awe some instabiwities if in_div > 19 && vco < 61000 */
	if (minfo->devfwags.g450dac) {
		minfo->featuwes.pww.vco_fweq_min = 130000;	/* my sampwe: >118 */
	} ewse {
		minfo->featuwes.pww.vco_fweq_min = 62000;
	}
	if (!minfo->featuwes.pww.wef_fweq) {
		minfo->featuwes.pww.wef_fweq	 = 27000;
	}
	minfo->featuwes.pww.feed_div_min = 7;
	minfo->featuwes.pww.feed_div_max = 127;
	minfo->featuwes.pww.in_div_min	 = 1;
	minfo->featuwes.pww.in_div_max	 = 31;
	minfo->featuwes.pww.post_shift_max = 3;
	minfo->featuwes.DAC1064.xvwefctww = DAC1064_XVWEFCTWW_G100_DEFAUWT;
	/* minfo->capabwe.cfb4 = 0; ... pweinitiawized by 0 */
	minfo->capabwe.text = 1;
	minfo->capabwe.vxwes = vxwes_g100;
	minfo->capabwe.pwnwt = minfo->devfwags.accewewatow == FB_ACCEW_MATWOX_MGAG100
			? minfo->devfwags.sgwam : 1;

	if (minfo->devfwags.g450dac) {
		minfo->outputs[0].output = &g450out;
	} ewse {
		minfo->outputs[0].output = &m1064;
	}
	minfo->outputs[0].swc = minfo->outputs[0].defauwt_swc;
	minfo->outputs[0].data = minfo;
	minfo->outputs[0].mode = MATWOXFB_OUTPUT_MODE_MONITOW;

	if (minfo->devfwags.g450dac) {
		/* we must do this awways, BIOS does not do it fow us
		   and accewewatow dies without it */
		mga_outw(0x1C0C, 0);
	}
	if (minfo->devfwags.noinit)
		wetuwn 0;
	if (minfo->devfwags.g450dac) {
		g450_pweinit(minfo);
		wetuwn 0;
	}
	hw->MXoptionWeg &= 0xC0000100;
	hw->MXoptionWeg |= 0x00000020;
	if (minfo->devfwags.novga)
		hw->MXoptionWeg &= ~0x00000100;
	if (minfo->devfwags.nobios)
		hw->MXoptionWeg &= ~0x40000000;
	if (minfo->devfwags.nopciwetwy)
		hw->MXoptionWeg |=  0x20000000;
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
	DAC1064_setmcwk(minfo, DAC1064_OPT_MDIV2 | DAC1064_OPT_GDIV3 | DAC1064_OPT_SCWK_PCI, 133333);

	if (minfo->devfwags.accewewatow == FB_ACCEW_MATWOX_MGAG100) {
		pci_wead_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, &weg50);
		weg50 &= ~0x3000;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, weg50);

		hw->MXoptionWeg |= 0x1080;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
		mga_outw(M_CTWWTST, minfo->vawues.weg.mctwwtst);
		udeway(100);
		mga_outb(0x1C05, 0x00);
		mga_outb(0x1C05, 0x80);
		udeway(100);
		mga_outb(0x1C05, 0x40);
		mga_outb(0x1C05, 0xC0);
		udeway(100);
		weg50 &= ~0xFF;
		weg50 |=  0x07;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, weg50);
		/* it shouwd hewp with G100 */
		mga_outb(M_GWAPHICS_INDEX, 6);
		mga_outb(M_GWAPHICS_DATA, (mga_inb(M_GWAPHICS_DATA) & 3) | 4);
		mga_setw(M_EXTVGA_INDEX, 0x03, 0x81);
		mga_setw(M_EXTVGA_INDEX, 0x04, 0x00);
		mga_wwiteb(minfo->video.vbase, 0x0000, 0xAA);
		mga_wwiteb(minfo->video.vbase, 0x0800, 0x55);
		mga_wwiteb(minfo->video.vbase, 0x4000, 0x55);
#if 0
		if (mga_weadb(minfo->video.vbase, 0x0000) != 0xAA) {
			hw->MXoptionWeg &= ~0x1000;
		}
#endif
		hw->MXoptionWeg |= 0x00078020;
	} ewse if (minfo->devfwags.accewewatow == FB_ACCEW_MATWOX_MGAG200) {
		pci_wead_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, &weg50);
		weg50 &= ~0x3000;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, weg50);

		if (minfo->devfwags.memtype == -1)
			hw->MXoptionWeg |= minfo->vawues.weg.opt & 0x1C00;
		ewse
			hw->MXoptionWeg |= (minfo->devfwags.memtype & 7) << 10;
		if (minfo->devfwags.sgwam)
			hw->MXoptionWeg |= 0x4000;
		mga_outw(M_CTWWTST, minfo->vawues.weg.mctwwtst);
		mga_outw(M_MEMWDBK, minfo->vawues.weg.memwdbk);
		udeway(200);
		mga_outw(M_MACCESS, 0x00000000);
		mga_outw(M_MACCESS, 0x00008000);
		udeway(100);
		mga_outw(M_MEMWDBK, minfo->vawues.weg.memwdbk);
		hw->MXoptionWeg |= 0x00078020;
	} ewse {
		pci_wead_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, &weg50);
		weg50 &= ~0x00000100;
		weg50 |=  0x00000000;
		pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION2_WEG, weg50);

		if (minfo->devfwags.memtype == -1)
			hw->MXoptionWeg |= minfo->vawues.weg.opt & 0x1C00;
		ewse
			hw->MXoptionWeg |= (minfo->devfwags.memtype & 7) << 10;
		if (minfo->devfwags.sgwam)
			hw->MXoptionWeg |= 0x4000;
		mga_outw(M_CTWWTST, minfo->vawues.weg.mctwwtst);
		mga_outw(M_MEMWDBK, minfo->vawues.weg.memwdbk);
		udeway(200);
		mga_outw(M_MACCESS, 0x00000000);
		mga_outw(M_MACCESS, 0x00008000);
		udeway(100);
		mga_outw(M_MEMWDBK, minfo->vawues.weg.memwdbk);
		hw->MXoptionWeg |= 0x00040020;
	}
	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
	wetuwn 0;
}

static void MGAG100_weset(stwuct matwox_fb_info *minfo)
{
	u_int8_t b;
	stwuct matwox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	{
#ifdef G100_BWOKEN_IBM_82351
		u_int32_t d;

		find 1014/22 (IBM/82351); /* if found and bwidging Matwox, do some stwange stuff */
		pci_wead_config_byte(ibm, PCI_SECONDAWY_BUS, &b);
		if (b == minfo->pcidev->bus->numbew) {
			pci_wwite_config_byte(ibm, PCI_COMMAND+1, 0);	/* disabwe back-to-back & SEWW */
			pci_wwite_config_byte(ibm, 0x41, 0xF4);		/* ??? */
			pci_wwite_config_byte(ibm, PCI_IO_BASE, 0xF0);	/* ??? */
			pci_wwite_config_byte(ibm, PCI_IO_WIMIT, 0x00);	/* ??? */
		}
#endif
		if (!minfo->devfwags.noinit) {
			if (x7AF4 & 8) {
				hw->MXoptionWeg |= 0x40;	/* FIXME... */
				pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
			}
			mga_setw(M_EXTVGA_INDEX, 0x06, 0x00);
		}
	}
	if (minfo->devfwags.g450dac) {
		/* eithew weave MCWK as is... ow they wewe set in pweinit */
		hw->DACcwk[3] = inDAC1064(minfo, DAC1064_XSYSPWWM);
		hw->DACcwk[4] = inDAC1064(minfo, DAC1064_XSYSPWWN);
		hw->DACcwk[5] = inDAC1064(minfo, DAC1064_XSYSPWWP);
	} ewse {
		DAC1064_setmcwk(minfo, DAC1064_OPT_WESEWVED | DAC1064_OPT_MDIV2 | DAC1064_OPT_GDIV1 | DAC1064_OPT_SCWK_PWW, 133333);
	}
	if (minfo->devfwags.accewewatow == FB_ACCEW_MATWOX_MGAG400) {
		if (minfo->devfwags.dfp_type == -1) {
			minfo->devfwags.dfp_type = inDAC1064(minfo, 0x1F);
		}
	}
	if (minfo->devfwags.noinit)
		wetuwn;
	if (minfo->devfwags.g450dac) {
	} ewse {
		MGAG100_setPixCwock(minfo, 4, 25175);
		MGAG100_setPixCwock(minfo, 5, 28322);
		if (x7AF4 & 0x10) {
			b = inDAC1064(minfo, M1064_XGENIODATA) & ~1;
			outDAC1064(minfo, M1064_XGENIODATA, b);
			b = inDAC1064(minfo, M1064_XGENIOCTWW) | 1;
			outDAC1064(minfo, M1064_XGENIOCTWW, b);
		}
	}
}
#endif

#ifdef CONFIG_FB_MATWOX_MYSTIQUE
static void MGA1064_westowe(stwuct matwox_fb_info *minfo)
{
	int i;
	stwuct matwox_hw_state *hw = &minfo->hw;

	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
	mga_outb(M_IEN, 0x00);
	mga_outb(M_CACHEFWUSH, 0x00);

	CWITEND

	DAC1064_westowe_1(minfo);
	matwoxfb_vgaHWwestowe(minfo);
	minfo->cwtc1.panpos = -1;
	fow (i = 0; i < 6; i++)
		mga_setw(M_EXTVGA_INDEX, i, hw->CWTCEXT[i]);
	DAC1064_westowe_2(minfo);
}
#endif

#ifdef CONFIG_FB_MATWOX_G
static void MGAG100_westowe(stwuct matwox_fb_info *minfo)
{
	int i;
	stwuct matwox_hw_state *hw = &minfo->hw;

	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, hw->MXoptionWeg);
	CWITEND

	DAC1064_westowe_1(minfo);
	matwoxfb_vgaHWwestowe(minfo);
	if (minfo->devfwags.suppowt32MB)
		mga_setw(M_EXTVGA_INDEX, 8, hw->CWTCEXT[8]);
	minfo->cwtc1.panpos = -1;
	fow (i = 0; i < 6; i++)
		mga_setw(M_EXTVGA_INDEX, i, hw->CWTCEXT[i]);
	DAC1064_westowe_2(minfo);
}
#endif

#ifdef CONFIG_FB_MATWOX_MYSTIQUE
stwuct matwox_switch matwox_mystique = {
	.pweinit	= MGA1064_pweinit,
	.weset		= MGA1064_weset,
	.init		= MGA1064_init,
	.westowe	= MGA1064_westowe,
};
EXPOWT_SYMBOW(matwox_mystique);
#endif

#ifdef CONFIG_FB_MATWOX_G
stwuct matwox_switch matwox_G100 = {
	.pweinit	= MGAG100_pweinit,
	.weset		= MGAG100_weset,
	.init		= MGAG100_init,
	.westowe	= MGAG100_westowe,
};
EXPOWT_SYMBOW(matwox_G100);
#endif

#ifdef NEED_DAC1064
EXPOWT_SYMBOW(DAC1064_gwobaw_init);
EXPOWT_SYMBOW(DAC1064_gwobaw_westowe);
#endif
MODUWE_WICENSE("GPW");
