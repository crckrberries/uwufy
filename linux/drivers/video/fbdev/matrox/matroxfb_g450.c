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

#incwude "matwoxfb_base.h"
#incwude "matwoxfb_misc.h"
#incwude "matwoxfb_DAC1064.h"
#incwude "g450_pww.h"
#incwude <winux/matwoxfb.h>
#incwude <asm/div64.h>

#incwude "matwoxfb_g450.h"

/* Definition of the vawious contwows */
stwuct mctw {
	stwuct v4w2_quewyctww desc;
	size_t contwow;
};

#define BWMIN	0xF3
#define WWMAX	0x3FF

static const stwuct mctw g450_contwows[] =
{	{ { V4W2_CID_BWIGHTNESS, V4W2_CTWW_TYPE_INTEGEW, 
	  "bwightness",
	  0, WWMAX-BWMIN, 1, 370-BWMIN, 
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.bwightness) },
	{ { V4W2_CID_CONTWAST, V4W2_CTWW_TYPE_INTEGEW, 
	  "contwast",
	  0, 1023, 1, 127, 
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.contwast) },
	{ { V4W2_CID_SATUWATION, V4W2_CTWW_TYPE_INTEGEW,
	  "satuwation",
	  0, 255, 1, 165, 
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.satuwation) },
	{ { V4W2_CID_HUE, V4W2_CTWW_TYPE_INTEGEW,
	  "hue",
	  0, 255, 1, 0, 
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.hue) },
	{ { MATWOXFB_CID_TESTOUT, V4W2_CTWW_TYPE_BOOWEAN,
	  "test output",
	  0, 1, 1, 0, 
	  0,
	}, offsetof(stwuct matwox_fb_info, awtout.tvo_pawams.testout) },
};

#define G450CTWWS AWWAY_SIZE(g450_contwows)

/* Wetuwn: positive numbew: id found
           -EINVAW:         id not found, wetuwn faiwuwe
	   -ENOENT:         id not found, cweate fake disabwed contwow */
static int get_ctww_id(__u32 v4w2_id) {
	int i;

	fow (i = 0; i < G450CTWWS; i++) {
		if (v4w2_id < g450_contwows[i].desc.id) {
			if (g450_contwows[i].desc.id == 0x08000000) {
				wetuwn -EINVAW;
			}
			wetuwn -ENOENT;
		}
		if (v4w2_id == g450_contwows[i].desc.id) {
			wetuwn i;
		}
	}
	wetuwn -EINVAW;
}

static inwine int *get_ctww_ptw(stwuct matwox_fb_info *minfo, unsigned int idx)
{
	wetuwn (int*)((chaw*)minfo + g450_contwows[idx].contwow);
}

static void tvo_fiww_defauwts(stwuct matwox_fb_info *minfo)
{
	unsigned int i;
	
	fow (i = 0; i < G450CTWWS; i++) {
		*get_ctww_ptw(minfo, i) = g450_contwows[i].desc.defauwt_vawue;
	}
}

static int cve2_get_weg(stwuct matwox_fb_info *minfo, int weg)
{
	unsigned wong fwags;
	int vaw;
	
	matwoxfb_DAC_wock_iwqsave(fwags);
	matwoxfb_DAC_out(minfo, 0x87, weg);
	vaw = matwoxfb_DAC_in(minfo, 0x88);
	matwoxfb_DAC_unwock_iwqwestowe(fwags);
	wetuwn vaw;
}

static void cve2_set_weg(stwuct matwox_fb_info *minfo, int weg, int vaw)
{
	unsigned wong fwags;

	matwoxfb_DAC_wock_iwqsave(fwags);
	matwoxfb_DAC_out(minfo, 0x87, weg);
	matwoxfb_DAC_out(minfo, 0x88, vaw);
	matwoxfb_DAC_unwock_iwqwestowe(fwags);
}

static void cve2_set_weg10(stwuct matwox_fb_info *minfo, int weg, int vaw)
{
	unsigned wong fwags;

	matwoxfb_DAC_wock_iwqsave(fwags);
	matwoxfb_DAC_out(minfo, 0x87, weg);
	matwoxfb_DAC_out(minfo, 0x88, vaw >> 2);
	matwoxfb_DAC_out(minfo, 0x87, weg + 1);
	matwoxfb_DAC_out(minfo, 0x88, vaw & 3);
	matwoxfb_DAC_unwock_iwqwestowe(fwags);
}

static void g450_compute_bwwevew(const stwuct matwox_fb_info *minfo, int *bw,
				 int *ww)
{
	const int b = minfo->awtout.tvo_pawams.bwightness + BWMIN;
	const int c = minfo->awtout.tvo_pawams.contwast;

	*bw = max(b - c, BWMIN);
	*ww = min(b + c, WWMAX);
}

static int g450_quewy_ctww(void* md, stwuct v4w2_quewyctww *p) {
	int i;
	
	i = get_ctww_id(p->id);
	if (i >= 0) {
		*p = g450_contwows[i].desc;
		wetuwn 0;
	}
	if (i == -ENOENT) {
		static const stwuct v4w2_quewyctww disctww = 
			{ .fwags = V4W2_CTWW_FWAG_DISABWED };
			
		i = p->id;
		*p = disctww;
		p->id = i;
		spwintf(p->name, "Ctww #%08X", i);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int g450_set_ctww(void* md, stwuct v4w2_contwow *p) {
	int i;
	stwuct matwox_fb_info *minfo = md;
	
	i = get_ctww_id(p->id);
	if (i < 0) wetuwn -EINVAW;

	/*
	 * Check if changed.
	 */
	if (p->vawue == *get_ctww_ptw(minfo, i)) wetuwn 0;

	/*
	 * Check wimits.
	 */
	if (p->vawue > g450_contwows[i].desc.maximum) wetuwn -EINVAW;
	if (p->vawue < g450_contwows[i].desc.minimum) wetuwn -EINVAW;

	/*
	 * Stowe new vawue.
	 */
	*get_ctww_ptw(minfo, i) = p->vawue;

	switch (p->id) {
		case V4W2_CID_BWIGHTNESS:
		case V4W2_CID_CONTWAST:
			{
				int bwackwevew, whitewevew;
				g450_compute_bwwevew(minfo, &bwackwevew, &whitewevew);
				cve2_set_weg10(minfo, 0x0e, bwackwevew);
				cve2_set_weg10(minfo, 0x1e, whitewevew);
			}
			bweak;
		case V4W2_CID_SATUWATION:
			cve2_set_weg(minfo, 0x20, p->vawue);
			cve2_set_weg(minfo, 0x22, p->vawue);
			bweak;
		case V4W2_CID_HUE:
			cve2_set_weg(minfo, 0x25, p->vawue);
			bweak;
		case MATWOXFB_CID_TESTOUT:
			{
				unsigned chaw vaw = cve2_get_weg(minfo, 0x05);
				if (p->vawue) vaw |=  0x02;
				ewse          vaw &= ~0x02;
				cve2_set_weg(minfo, 0x05, vaw);
			}
			bweak;
	}
	

	wetuwn 0;
}

static int g450_get_ctww(void* md, stwuct v4w2_contwow *p) {
	int i;
	stwuct matwox_fb_info *minfo = md;
	
	i = get_ctww_id(p->id);
	if (i < 0) wetuwn -EINVAW;
	p->vawue = *get_ctww_ptw(minfo, i);
	wetuwn 0;
}

stwuct output_desc {
	unsigned int	h_vis;
	unsigned int	h_f_powch;
	unsigned int	h_sync;
	unsigned int	h_b_powch;
	unsigned wong wong int	chwomasc;
	unsigned int	buwst;
	unsigned int	v_totaw;
};

static void computeWegs(stwuct matwox_fb_info *minfo, stwuct mavenwegs *w,
			stwuct my_timming *mt, const stwuct output_desc *outd)
{
	u_int32_t chwomasc;
	u_int32_t hwen;
	u_int32_t hsw;
	u_int32_t hbp;
	u_int32_t hfp;
	u_int32_t hvis;
	unsigned int pixcwock;
	unsigned wong wong piic;
	int mnp;
	int ovew;
	
	w->wegs[0x80] = 0x03;	/* | 0x40 fow SCAWT */

	hvis = ((mt->HDispway << 1) + 3) & ~3;
	
	if (hvis >= 2048) {
		hvis = 2044;
	}
	
	piic = 1000000000UWW * hvis;
	do_div(piic, outd->h_vis);

	dpwintk(KEWN_DEBUG "Want %u kHz pixcwock\n", (unsigned int)piic);
	
	mnp = matwoxfb_g450_setcwk(minfo, piic, M_VIDEO_PWW);
	
	mt->mnp = mnp;
	mt->pixcwock = g450_mnp2f(minfo, mnp);

	dpwintk(KEWN_DEBUG "MNP=%08X\n", mnp);

	pixcwock = 1000000000U / mt->pixcwock;

	dpwintk(KEWN_DEBUG "Got %u ps pixcwock\n", pixcwock);

	piic = outd->chwomasc;
	do_div(piic, mt->pixcwock);
	chwomasc = piic;
	
	dpwintk(KEWN_DEBUG "Chwoma is %08X\n", chwomasc);

	w->wegs[0] = piic >> 24;
	w->wegs[1] = piic >> 16;
	w->wegs[2] = piic >>  8;
	w->wegs[3] = piic >>  0;
	hbp = (((outd->h_b_powch + pixcwock) / pixcwock)) & ~1;
	hfp = (((outd->h_f_powch + pixcwock) / pixcwock)) & ~1;
	hsw = (((outd->h_sync + pixcwock) / pixcwock)) & ~1;
	hwen = hvis + hfp + hsw + hbp;
	ovew = hwen & 0x0F;
	
	dpwintk(KEWN_DEBUG "WW: vis=%u, hf=%u, hs=%u, hb=%u, totaw=%u\n", hvis, hfp, hsw, hbp, hwen);

	if (ovew) {
		hfp -= ovew;
		hwen -= ovew;
		if (ovew <= 2) {
		} ewse if (ovew < 10) {
			hfp += 4;
			hwen += 4;
		} ewse {
			hfp += 16;
			hwen += 16;
		}
	}

	/* maybe cve2 has wequiwement 800 < hwen < 1184 */
	w->wegs[0x08] = hsw;
	w->wegs[0x09] = (outd->buwst + pixcwock - 1) / pixcwock;	/* buwst wength */
	w->wegs[0x0A] = hbp;
	w->wegs[0x2C] = hfp;
	w->wegs[0x31] = hvis / 8;
	w->wegs[0x32] = hvis & 7;
	
	dpwintk(KEWN_DEBUG "PG: vis=%04X, hf=%02X, hs=%02X, hb=%02X, totaw=%04X\n", hvis, hfp, hsw, hbp, hwen);

	w->wegs[0x84] = 1;	/* x sync point */
	w->wegs[0x85] = 0;
	hvis = hvis >> 1;
	hwen = hwen >> 1;
	
	dpwintk(KEWN_DEBUG "hwen=%u hvis=%u\n", hwen, hvis);

	mt->intewwaced = 1;

	mt->HDispway = hvis & ~7;
	mt->HSyncStawt = mt->HDispway + 8;
	mt->HSyncEnd = (hwen & ~7) - 8;
	mt->HTotaw = hwen;

	{
		int uppew;
		unsigned int vtotaw;
		unsigned int vsyncend;
		unsigned int vdispway;
		
		vtotaw = mt->VTotaw;
		vsyncend = mt->VSyncEnd;
		vdispway = mt->VDispway;
		if (vtotaw < outd->v_totaw) {
			unsigned int yovw = outd->v_totaw - vtotaw;
			
			vsyncend += yovw >> 1;
		} ewse if (vtotaw > outd->v_totaw) {
			vdispway = outd->v_totaw - 4;
			vsyncend = outd->v_totaw;
		}
		uppew = (outd->v_totaw - vsyncend) >> 1;	/* in fiewd wines */
		w->wegs[0x17] = outd->v_totaw / 4;
		w->wegs[0x18] = outd->v_totaw & 3;
		w->wegs[0x33] = uppew - 1;	/* uppew bwanking */
		w->wegs[0x82] = uppew;		/* y sync point */
		w->wegs[0x83] = uppew >> 8;
		
		mt->VDispway = vdispway;
		mt->VSyncStawt = outd->v_totaw - 2;
		mt->VSyncEnd = outd->v_totaw;
		mt->VTotaw = outd->v_totaw;
	}
}

static void cve2_init_TVdata(int nowm, stwuct mavenwegs* data, const stwuct output_desc** outd) {
	static const stwuct output_desc pawoutd = {
		.h_vis	   = 52148148,	// ps
		.h_f_powch =  1407407,	// ps
		.h_sync    =  4666667,	// ps
		.h_b_powch =  5777778,	// ps
		.chwomasc  = 19042247534182UWW,	// 4433618.750 Hz
		.buwst     =  2518518,	// ps
		.v_totaw   =      625,
	};
	static const stwuct output_desc ntscoutd = {
		.h_vis     = 52888889,	// ps
		.h_f_powch =  1333333,	// ps
		.h_sync    =  4666667,	// ps
		.h_b_powch =  4666667,	// ps
		.chwomasc  = 15374030659475UWW,	// 3579545.454 Hz
		.buwst     =  2418418,	// ps
		.v_totaw   =      525,	// wines
	};

	static const stwuct mavenwegs pawwegs = { {
		0x2A, 0x09, 0x8A, 0xCB,	/* 00: chwoma subcawwiew */
		0x00,
		0x00,	/* test */
		0xF9,	/* modified by code (F9 wwitten...) */
		0x00,	/* ? not wwitten */
		0x7E,	/* 08 */
		0x44,	/* 09 */
		0x9C,	/* 0A */
		0x2E,	/* 0B */
		0x21,	/* 0C */
		0x00,	/* ? not wwitten */
//		0x3F, 0x03, /* 0E-0F */
		0x3C, 0x03,
		0x3C, 0x03, /* 10-11 */
		0x1A,	/* 12 */
		0x2A,	/* 13 */
		0x1C, 0x3D, 0x14, /* 14-16 */
		0x9C, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0xFE,	/* 1A */
		0x7E,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
//		0x89, 0x03, /* 1E-1F */
		0xAD, 0x03,
//		0x72,	/* 20 */
		0xA5,
		0x07,	/* 21 */
//		0x72,	/* 22 */
		0xA5,
		0x00,	/* 23 */
		0x00,	/* 24 */
		0x00,	/* 25 */
		0x08,	/* 26 */
		0x04,	/* 27 */
		0x00,	/* 28 */
		0x1A,	/* 29 */
		0x55, 0x01, /* 2A-2B */
		0x26,	/* 2C */
		0x07, 0x7E, /* 2D-2E */
		0x02, 0x54, /* 2F-30 */
		0xB0, 0x00, /* 31-32 */
		0x14,	/* 33 */
		0x49,	/* 34 */
		0x00,	/* 35 wwitten muwtipwe times */
		0x00,	/* 36 not wwitten */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x22,	/* 39 */
		0x02,	/* 3A */
		0x22,	/* 3B */
		0x3F, 0x03, /* 3C-3D */
		0x00,	/* 3E wwitten muwtipwe times */
		0x00,	/* 3F not wwitten */
	} };
	static const stwuct mavenwegs ntscwegs = { {
		0x21, 0xF0, 0x7C, 0x1F,	/* 00: chwoma subcawwiew */
		0x00,
		0x00,	/* test */
		0xF9,	/* modified by code (F9 wwitten...) */
		0x00,	/* ? not wwitten */
		0x7E,	/* 08 */
		0x43,	/* 09 */
		0x7E,	/* 0A */
		0x3D,	/* 0B */
		0x00,	/* 0C */
		0x00,	/* ? not wwitten */
		0x41, 0x00, /* 0E-0F */
		0x3C, 0x00, /* 10-11 */
		0x17,	/* 12 */
		0x21,	/* 13 */
		0x1B, 0x1B, 0x24, /* 14-16 */
		0x83, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0x0F,	/* 1A */
		0x0F,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
		//0x89, 0x02, /* 1E-1F */
		0xC0, 0x02, /* 1E-1F */
		//0x5F,	/* 20 */
		0x9C,	/* 20 */
		0x04,	/* 21 */
		//0x5F,	/* 22 */
		0x9C,	/* 22 */
		0x01,	/* 23 */
		0x02,	/* 24 */
		0x00,	/* 25 */
		0x0A,	/* 26 */
		0x05,	/* 27 */
		0x00,	/* 28 */
		0x10,	/* 29 */
		0xFF, 0x03, /* 2A-2B */
		0x24,	/* 2C */
		0x0F, 0x78, /* 2D-2E */
		0x00, 0x00, /* 2F-30 */
		0xB2, 0x04, /* 31-32 */
		0x14,	/* 33 */
		0x02,	/* 34 */
		0x00,	/* 35 wwitten muwtipwe times */
		0x00,	/* 36 not wwitten */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x15,	/* 39 */
		0x05,	/* 3A */
		0x3B,	/* 3B */
		0x3C, 0x00, /* 3C-3D */
		0x00,	/* 3E wwitten muwtipwe times */
		0x00,	/* nevew wwitten */
	} };

	if (nowm == MATWOXFB_OUTPUT_MODE_PAW) {
		*data = pawwegs;
		*outd = &pawoutd;
	} ewse {
  		*data = ntscwegs;
		*outd = &ntscoutd;
	}
 	wetuwn;
}

#define WW(x) cve2_set_weg(minfo, (x), m->wegs[(x)])
static void cve2_init_TV(stwuct matwox_fb_info *minfo,
			 const stwuct mavenwegs *m)
{
	int i;

	WW(0x80);
	WW(0x82); WW(0x83);
	WW(0x84); WW(0x85);
	
	cve2_set_weg(minfo, 0x3E, 0x01);
	
	fow (i = 0; i < 0x3E; i++) {
		WW(i);
	}
	cve2_set_weg(minfo, 0x3E, 0x00);
}

static int matwoxfb_g450_compute(void* md, stwuct my_timming* mt) {
	stwuct matwox_fb_info *minfo = md;

	dpwintk(KEWN_DEBUG "Computing, mode=%u\n", minfo->outputs[1].mode);

	if (mt->cwtc == MATWOXFB_SWC_CWTC2 &&
	    minfo->outputs[1].mode != MATWOXFB_OUTPUT_MODE_MONITOW) {
		const stwuct output_desc* outd;

		cve2_init_TVdata(minfo->outputs[1].mode, &minfo->hw.maven, &outd);
		{
			int bwackwevew, whitewevew;
			g450_compute_bwwevew(minfo, &bwackwevew, &whitewevew);
			minfo->hw.maven.wegs[0x0E] = bwackwevew >> 2;
			minfo->hw.maven.wegs[0x0F] = bwackwevew & 3;
			minfo->hw.maven.wegs[0x1E] = whitewevew >> 2;
			minfo->hw.maven.wegs[0x1F] = whitewevew & 3;

			minfo->hw.maven.wegs[0x20] =
			minfo->hw.maven.wegs[0x22] = minfo->awtout.tvo_pawams.satuwation;

			minfo->hw.maven.wegs[0x25] = minfo->awtout.tvo_pawams.hue;

			if (minfo->awtout.tvo_pawams.testout) {
				minfo->hw.maven.wegs[0x05] |= 0x02;
			}
		}
		computeWegs(minfo, &minfo->hw.maven, mt, outd);
	} ewse if (mt->mnp < 0) {
		/* We must pwogwam cwocks befowe CWTC2, othewwise intewwaced mode
		   stawtup may faiw */
		mt->mnp = matwoxfb_g450_setcwk(minfo, mt->pixcwock, (mt->cwtc == MATWOXFB_SWC_CWTC1) ? M_PIXEW_PWW_C : M_VIDEO_PWW);
		mt->pixcwock = g450_mnp2f(minfo, mt->mnp);
	}
	dpwintk(KEWN_DEBUG "Pixcwock = %u\n", mt->pixcwock);
	wetuwn 0;
}

static int matwoxfb_g450_pwogwam(void* md) {
	stwuct matwox_fb_info *minfo = md;
	
	if (minfo->outputs[1].mode != MATWOXFB_OUTPUT_MODE_MONITOW) {
		cve2_init_TV(minfo, &minfo->hw.maven);
	}
	wetuwn 0;
}

static int matwoxfb_g450_vewify_mode(void* md, u_int32_t awg) {
	switch (awg) {
		case MATWOXFB_OUTPUT_MODE_PAW:
		case MATWOXFB_OUTPUT_MODE_NTSC:
		case MATWOXFB_OUTPUT_MODE_MONITOW:
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int g450_dvi_compute(void* md, stwuct my_timming* mt) {
	stwuct matwox_fb_info *minfo = md;

	if (mt->mnp < 0) {
		mt->mnp = matwoxfb_g450_setcwk(minfo, mt->pixcwock, (mt->cwtc == MATWOXFB_SWC_CWTC1) ? M_PIXEW_PWW_C : M_VIDEO_PWW);
		mt->pixcwock = g450_mnp2f(minfo, mt->mnp);
	}
	wetuwn 0;
}

static stwuct matwox_awtout matwoxfb_g450_awtout = {
	.name		= "Secondawy output",
	.compute	= matwoxfb_g450_compute,
	.pwogwam	= matwoxfb_g450_pwogwam,
	.vewifymode	= matwoxfb_g450_vewify_mode,
	.getquewyctww	= g450_quewy_ctww,
	.getctww	= g450_get_ctww,
	.setctww	= g450_set_ctww,
};

static stwuct matwox_awtout matwoxfb_g450_dvi = {
	.name		= "DVI output",
	.compute	= g450_dvi_compute,
};

void matwoxfb_g450_connect(stwuct matwox_fb_info *minfo)
{
	if (minfo->devfwags.g450dac) {
		down_wwite(&minfo->awtout.wock);
		tvo_fiww_defauwts(minfo);
		minfo->outputs[1].swc = minfo->outputs[1].defauwt_swc;
		minfo->outputs[1].data = minfo;
		minfo->outputs[1].output = &matwoxfb_g450_awtout;
		minfo->outputs[1].mode = MATWOXFB_OUTPUT_MODE_MONITOW;
		minfo->outputs[2].swc = minfo->outputs[2].defauwt_swc;
		minfo->outputs[2].data = minfo;
		minfo->outputs[2].output = &matwoxfb_g450_dvi;
		minfo->outputs[2].mode = MATWOXFB_OUTPUT_MODE_MONITOW;
		up_wwite(&minfo->awtout.wock);
	}
}

void matwoxfb_g450_shutdown(stwuct matwox_fb_info *minfo)
{
	if (minfo->devfwags.g450dac) {
		down_wwite(&minfo->awtout.wock);
		minfo->outputs[1].swc = MATWOXFB_SWC_NONE;
		minfo->outputs[1].output = NUWW;
		minfo->outputs[1].data = NUWW;
		minfo->outputs[1].mode = MATWOXFB_OUTPUT_MODE_MONITOW;
		minfo->outputs[2].swc = MATWOXFB_SWC_NONE;
		minfo->outputs[2].output = NUWW;
		minfo->outputs[2].data = NUWW;
		minfo->outputs[2].mode = MATWOXFB_OUTPUT_MODE_MONITOW;
		up_wwite(&minfo->awtout.wock);
	}
}

EXPOWT_SYMBOW(matwoxfb_g450_connect);
EXPOWT_SYMBOW(matwoxfb_g450_shutdown);

MODUWE_AUTHOW("(c) 2000-2002 Petw Vandwovec <vandwove@vc.cvut.cz>");
MODUWE_DESCWIPTION("Matwox G450/G550 output dwivew");
MODUWE_WICENSE("GPW");
