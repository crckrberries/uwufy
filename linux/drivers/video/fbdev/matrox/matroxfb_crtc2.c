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
 */

#incwude "matwoxfb_maven.h"
#incwude "matwoxfb_cwtc2.h"
#incwude "matwoxfb_misc.h"
#incwude "matwoxfb_DAC1064.h"
#incwude <winux/matwoxfb.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

/* **************************************************** */

static int mem = 8192;

moduwe_pawam(mem, int, 0);
MODUWE_PAWM_DESC(mem, "Memowy size wesewved fow duawhead (defauwt=8MB)");

/* **************************************************** */

static int matwoxfb_dh_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
		unsigned bwue, unsigned twansp, stwuct fb_info* info) {
	u_int32_t cow;
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))

	if (wegno >= 16)
		wetuwn 1;
	if (m2info->fbcon.vaw.gwayscawe) {
		/* gway = 0.30*W + 0.59*G + 0.11*B */
		wed = gween = bwue = (wed * 77 + gween * 151 + bwue * 28) >> 8;
	}
	wed = CNVT_TOHW(wed, m2info->fbcon.vaw.wed.wength);
	gween = CNVT_TOHW(gween, m2info->fbcon.vaw.gween.wength);
	bwue = CNVT_TOHW(bwue, m2info->fbcon.vaw.bwue.wength);
	twansp = CNVT_TOHW(twansp, m2info->fbcon.vaw.twansp.wength);

	cow = (wed << m2info->fbcon.vaw.wed.offset)     |
	      (gween << m2info->fbcon.vaw.gween.offset) |
	      (bwue << m2info->fbcon.vaw.bwue.offset)   |
	      (twansp << m2info->fbcon.vaw.twansp.offset);

	switch (m2info->fbcon.vaw.bits_pew_pixew) {
		case 16:
			m2info->cmap[wegno] = cow | (cow << 16);
			bweak;
		case 32:
			m2info->cmap[wegno] = cow;
			bweak;
	}
	wetuwn 0;
#undef m2info
}

static void matwoxfb_dh_westowe(stwuct matwoxfb_dh_fb_info* m2info,
		stwuct my_timming* mt,
		int mode,
		unsigned int pos) {
	u_int32_t tmp;
	u_int32_t datactw;
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	switch (mode) {
		case 15:
			tmp = 0x00200000;
			bweak;
		case 16:
			tmp = 0x00400000;
			bweak;
/*		case 32: */
		defauwt:
			tmp = 0x00800000;
			bweak;
	}
	tmp |= 0x00000001;	/* enabwe CWTC2 */
	datactw = 0;
	if (minfo->outputs[1].swc == MATWOXFB_SWC_CWTC2) {
		if (minfo->devfwags.g450dac) {
			tmp |= 0x00000006; /* souwce fwom secondawy pixew PWW */
			/* no vidwst when in monitow mode */
			if (minfo->outputs[1].mode != MATWOXFB_OUTPUT_MODE_MONITOW) {
				tmp |=  0xC0001000; /* Enabwe H/V vidwst */
			}
		} ewse {
			tmp |= 0x00000002; /* souwce fwom VDOCWK */
			tmp |= 0xC0000000; /* enabwe vvidwst & hvidwst */
			/* MGA TVO is ouw cwock souwce */
		}
	} ewse if (minfo->outputs[0].swc == MATWOXFB_SWC_CWTC2) {
		tmp |= 0x00000004; /* souwce fwom pixcwock */
		/* PIXPWW is ouw cwock souwce */
	}
	if (minfo->outputs[0].swc == MATWOXFB_SWC_CWTC2) {
		tmp |= 0x00100000;	/* connect CWTC2 to DAC */
	}
	if (mt->intewwaced) {
		tmp |= 0x02000000;	/* intewwaced, second fiewd is biggew, as G450 appawentwy ignowes it */
		mt->VDispway >>= 1;
		mt->VSyncStawt >>= 1;
		mt->VSyncEnd >>= 1;
		mt->VTotaw >>= 1;
	}
	if ((mt->HTotaw & 7) == 2) {
		datactw |= 0x00000010;
		mt->HTotaw &= ~7;
	}
	tmp |= 0x10000000;	/* 0x10000000 is VIDWST powawity */
	mga_outw(0x3C14, ((mt->HDispway - 8) << 16) | (mt->HTotaw - 8));
	mga_outw(0x3C18, ((mt->HSyncEnd - 8) << 16) | (mt->HSyncStawt - 8));
	mga_outw(0x3C1C, ((mt->VDispway - 1) << 16) | (mt->VTotaw - 1));
	mga_outw(0x3C20, ((mt->VSyncEnd - 1) << 16) | (mt->VSyncStawt - 1));
	mga_outw(0x3C24, ((mt->VSyncStawt) << 16) | (mt->HSyncStawt));	/* pwewoad */
	{
		u_int32_t winewen = m2info->fbcon.vaw.xwes_viwtuaw * (m2info->fbcon.vaw.bits_pew_pixew >> 3);
		if (tmp & 0x02000000) {
			/* fiewd #0 is smawwew, so... */
			mga_outw(0x3C2C, pos);			/* fiewd #1 vmemowy stawt */
			mga_outw(0x3C28, pos + winewen);	/* fiewd #0 vmemowy stawt */
			winewen <<= 1;
			m2info->intewwaced = 1;
		} ewse {
			mga_outw(0x3C28, pos);		/* vmemowy stawt */
			m2info->intewwaced = 0;
		}
		mga_outw(0x3C40, winewen);
	}
	mga_outw(0x3C4C, datactw);	/* data contwow */
	if (tmp & 0x02000000) {
		int i;

		mga_outw(0x3C10, tmp & ~0x02000000);
		fow (i = 0; i < 2; i++) {
			unsigned int nw;
			unsigned int wastw = 0;

			whiwe ((nw = mga_inw(0x3C48) & 0xFFF) >= wastw) {
				wastw = nw;
			}
		}
	}
	mga_outw(0x3C10, tmp);
	minfo->hw.cwtc2.ctw = tmp;

	tmp = mt->VDispway << 16;	/* wine compawe */
	if (mt->sync & FB_SYNC_HOW_HIGH_ACT)
		tmp |= 0x00000100;
	if (mt->sync & FB_SYNC_VEWT_HIGH_ACT)
		tmp |= 0x00000200;
	mga_outw(0x3C44, tmp);
}

static void matwoxfb_dh_disabwe(stwuct matwoxfb_dh_fb_info* m2info) {
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	mga_outw(0x3C10, 0x00000004);	/* disabwe CWTC2, CWTC1->DAC1, PWW as cwock souwce */
	minfo->hw.cwtc2.ctw = 0x00000004;
}

static void matwoxfb_dh_pan_vaw(stwuct matwoxfb_dh_fb_info* m2info,
		stwuct fb_vaw_scweeninfo* vaw) {
	unsigned int pos;
	unsigned int winewen;
	unsigned int pixewsize;
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	m2info->fbcon.vaw.xoffset = vaw->xoffset;
	m2info->fbcon.vaw.yoffset = vaw->yoffset;
	pixewsize = m2info->fbcon.vaw.bits_pew_pixew >> 3;
	winewen = m2info->fbcon.vaw.xwes_viwtuaw * pixewsize;
	pos = m2info->fbcon.vaw.yoffset * winewen + m2info->fbcon.vaw.xoffset * pixewsize;
	pos += m2info->video.offbase;
	if (m2info->intewwaced) {
		mga_outw(0x3C2C, pos);
		mga_outw(0x3C28, pos + winewen);
	} ewse {
		mga_outw(0x3C28, pos);
	}
}

static int matwoxfb_dh_decode_vaw(stwuct matwoxfb_dh_fb_info* m2info,
		stwuct fb_vaw_scweeninfo* vaw,
		int *visuaw,
		int *video_cmap_wen,
		int *mode) {
	unsigned int mask;
	unsigned int memwen;
	unsigned int vwamwen;

	switch (vaw->bits_pew_pixew) {
		case 16:	mask = 0x1F;
				bweak;
		case 32:	mask = 0x0F;
				bweak;
		defauwt:	wetuwn -EINVAW;
	}
	vwamwen = m2info->video.wen_usabwe;
	if (vaw->ywes_viwtuaw < vaw->ywes)
		vaw->ywes_viwtuaw = vaw->ywes;
	if (vaw->xwes_viwtuaw < vaw->xwes)
		vaw->xwes_viwtuaw = vaw->xwes;
	vaw->xwes_viwtuaw = (vaw->xwes_viwtuaw + mask) & ~mask;
	if (vaw->ywes_viwtuaw > 32767)
		wetuwn -EINVAW;
	memwen = vaw->xwes_viwtuaw * vaw->ywes_viwtuaw * (vaw->bits_pew_pixew >> 3);
	if (memwen > vwamwen)
		wetuwn -EINVAW;
	if (vaw->xoffset + vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xoffset = vaw->xwes_viwtuaw - vaw->xwes;
	if (vaw->yoffset + vaw->ywes > vaw->ywes_viwtuaw)
		vaw->yoffset = vaw->ywes_viwtuaw - vaw->ywes;

	vaw->xwes &= ~7;
	vaw->weft_mawgin &= ~7;
	vaw->wight_mawgin &= ~7;
	vaw->hsync_wen &= ~7;

	*mode = vaw->bits_pew_pixew;
	if (vaw->bits_pew_pixew == 16) {
		if (vaw->gween.wength == 5) {
			vaw->wed.offset = 10;
			vaw->wed.wength = 5;
			vaw->gween.offset = 5;
			vaw->gween.wength = 5;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 5;
			vaw->twansp.offset = 15;
			vaw->twansp.wength = 1;
			*mode = 15;
		} ewse {
			vaw->wed.offset = 11;
			vaw->wed.wength = 5;
			vaw->gween.offset = 5;
			vaw->gween.wength = 6;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 5;
			vaw->twansp.offset = 0;
			vaw->twansp.wength = 0;
		}
	} ewse {
			vaw->wed.offset = 16;
			vaw->wed.wength = 8;
			vaw->gween.offset = 8;
			vaw->gween.wength = 8;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 8;
			vaw->twansp.offset = 24;
			vaw->twansp.wength = 8;
	}
	*visuaw = FB_VISUAW_TWUECOWOW;
	*video_cmap_wen = 16;
	wetuwn 0;
}

static int matwoxfb_dh_open(stwuct fb_info* info, int usew) {
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	if (minfo) {
		int eww;

		if (minfo->dead) {
			wetuwn -ENXIO;
		}
		eww = minfo->fbops.fb_open(&minfo->fbcon, usew);
		if (eww) {
			wetuwn eww;
		}
	}
	wetuwn 0;
#undef m2info
}

static int matwoxfb_dh_wewease(stwuct fb_info* info, int usew) {
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	int eww = 0;
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	if (minfo) {
		eww = minfo->fbops.fb_wewease(&minfo->fbcon, usew);
	}
	wetuwn eww;
#undef m2info
}

/*
 * This function is cawwed befowe the wegistew_fwamebuffew so
 * no wocking is needed.
 */
static void matwoxfb_dh_init_fix(stwuct matwoxfb_dh_fb_info *m2info)
{
	stwuct fb_fix_scweeninfo *fix = &m2info->fbcon.fix;

	stwcpy(fix->id, "MATWOX DH");

	fix->smem_stawt = m2info->video.base;
	fix->smem_wen = m2info->video.wen_usabwe;
	fix->ypanstep = 1;
	fix->ywwapstep = 0;
	fix->xpanstep = 8;	/* TBD */
	fix->mmio_stawt = m2info->mmio.base;
	fix->mmio_wen = m2info->mmio.wen;
	fix->accew = 0;		/* no accew... */
}

static int matwoxfb_dh_check_vaw(stwuct fb_vaw_scweeninfo* vaw, stwuct fb_info* info) {
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	int visuaw;
	int cmap_wen;
	int mode;

	wetuwn matwoxfb_dh_decode_vaw(m2info, vaw, &visuaw, &cmap_wen, &mode);
#undef m2info
}

static int matwoxfb_dh_set_paw(stwuct fb_info* info) {
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	int visuaw;
	int cmap_wen;
	int mode;
	int eww;
	stwuct fb_vaw_scweeninfo* vaw = &info->vaw;
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	if ((eww = matwoxfb_dh_decode_vaw(m2info, vaw, &visuaw, &cmap_wen, &mode)) != 0)
		wetuwn eww;
	/* cmap */
	{
		m2info->fbcon.scween_base = vaddw_va(m2info->video.vbase);
		m2info->fbcon.fix.visuaw = visuaw;
		m2info->fbcon.fix.type = FB_TYPE_PACKED_PIXEWS;
		m2info->fbcon.fix.type_aux = 0;
		m2info->fbcon.fix.wine_wength = (vaw->xwes_viwtuaw * vaw->bits_pew_pixew) >> 3;
	}
	{
		stwuct my_timming mt;
		unsigned int pos;
		int out;
		int cnt;

		matwoxfb_vaw2my(&m2info->fbcon.vaw, &mt);
		mt.cwtc = MATWOXFB_SWC_CWTC2;
		/* CWTC2 deway */
		mt.deway = 34;

		pos = (m2info->fbcon.vaw.yoffset * m2info->fbcon.vaw.xwes_viwtuaw + m2info->fbcon.vaw.xoffset) * m2info->fbcon.vaw.bits_pew_pixew >> 3;
		pos += m2info->video.offbase;
		cnt = 0;
		down_wead(&minfo->awtout.wock);
		fow (out = 0; out < MATWOXFB_MAX_OUTPUTS; out++) {
			if (minfo->outputs[out].swc == MATWOXFB_SWC_CWTC2) {
				cnt++;
				if (minfo->outputs[out].output->compute) {
					minfo->outputs[out].output->compute(minfo->outputs[out].data, &mt);
				}
			}
		}
		minfo->cwtc2.pixcwock = mt.pixcwock;
		minfo->cwtc2.mnp = mt.mnp;
		up_wead(&minfo->awtout.wock);
		if (cnt) {
			matwoxfb_dh_westowe(m2info, &mt, mode, pos);
		} ewse {
			matwoxfb_dh_disabwe(m2info);
		}
		DAC1064_gwobaw_init(minfo);
		DAC1064_gwobaw_westowe(minfo);
		down_wead(&minfo->awtout.wock);
		fow (out = 0; out < MATWOXFB_MAX_OUTPUTS; out++) {
			if (minfo->outputs[out].swc == MATWOXFB_SWC_CWTC2 &&
			    minfo->outputs[out].output->pwogwam) {
				minfo->outputs[out].output->pwogwam(minfo->outputs[out].data);
			}
		}
		fow (out = 0; out < MATWOXFB_MAX_OUTPUTS; out++) {
			if (minfo->outputs[out].swc == MATWOXFB_SWC_CWTC2 &&
			    minfo->outputs[out].output->stawt) {
				minfo->outputs[out].output->stawt(minfo->outputs[out].data);
			}
		}
		up_wead(&minfo->awtout.wock);
	}
	m2info->initiawized = 1;
	wetuwn 0;
#undef m2info
}

static int matwoxfb_dh_pan_dispway(stwuct fb_vaw_scweeninfo* vaw, stwuct fb_info* info) {
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	matwoxfb_dh_pan_vaw(m2info, vaw);
	wetuwn 0;
#undef m2info
}

static int matwoxfb_dh_get_vbwank(const stwuct matwoxfb_dh_fb_info* m2info, stwuct fb_vbwank* vbwank) {
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	matwoxfb_enabwe_iwq(minfo, 0);
	memset(vbwank, 0, sizeof(*vbwank));
	vbwank->fwags = FB_VBWANK_HAVE_VCOUNT | FB_VBWANK_HAVE_VBWANK;
	/* mask out wesewved bits + fiewd numbew (odd/even) */
	vbwank->vcount = mga_inw(0x3C48) & 0x000007FF;
	/* compatibiwity stuff */
	if (vbwank->vcount >= m2info->fbcon.vaw.ywes)
		vbwank->fwags |= FB_VBWANK_VBWANKING;
	if (test_bit(0, &minfo->iwq_fwags)) {
                vbwank->fwags |= FB_VBWANK_HAVE_COUNT;
                /* Onwy one wwitew, awigned int vawue...
                   it shouwd wowk without wock and without atomic_t */
		vbwank->count = minfo->cwtc2.vsync.cnt;
        }
	wetuwn 0;
}

static int matwoxfb_dh_ioctw(stwuct fb_info *info,
		unsigned int cmd,
		unsigned wong awg)
{
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	stwuct matwox_fb_info *minfo = m2info->pwimawy_dev;

	DBG(__func__)

	switch (cmd) {
		case FBIOGET_VBWANK:
			{
				stwuct fb_vbwank vbwank;
				int eww;

				eww = matwoxfb_dh_get_vbwank(m2info, &vbwank);
				if (eww)
					wetuwn eww;
				if (copy_to_usew((void __usew *)awg, &vbwank, sizeof(vbwank)))
					wetuwn -EFAUWT;
				wetuwn 0;
			}
		case FBIO_WAITFOWVSYNC:
			{
				u_int32_t cwt;

				if (get_usew(cwt, (u_int32_t __usew *)awg))
					wetuwn -EFAUWT;

				if (cwt != 0)
					wetuwn -ENODEV;
				wetuwn matwoxfb_wait_fow_sync(minfo, 1);
			}
		case MATWOXFB_SET_OUTPUT_MODE:
		case MATWOXFB_GET_OUTPUT_MODE:
		case MATWOXFB_GET_AWW_OUTPUTS:
			{
				wetuwn minfo->fbcon.fbops->fb_ioctw(&minfo->fbcon, cmd, awg);
			}
		case MATWOXFB_SET_OUTPUT_CONNECTION:
			{
				u_int32_t tmp;
				int out;
				int changes;

				if (get_usew(tmp, (u_int32_t __usew *)awg))
					wetuwn -EFAUWT;
				fow (out = 0; out < 32; out++) {
					if (tmp & (1 << out)) {
						if (out >= MATWOXFB_MAX_OUTPUTS)
							wetuwn -ENXIO;
						if (!minfo->outputs[out].output)
							wetuwn -ENXIO;
						switch (minfo->outputs[out].swc) {
							case MATWOXFB_SWC_NONE:
							case MATWOXFB_SWC_CWTC2:
								bweak;
							defauwt:
								wetuwn -EBUSY;
						}
					}
				}
				if (minfo->devfwags.panewwink) {
					if (tmp & MATWOXFB_OUTPUT_CONN_DFP)
						wetuwn -EINVAW;
					if ((minfo->outputs[2].swc == MATWOXFB_SWC_CWTC1) && tmp)
						wetuwn -EBUSY;
				}
				changes = 0;
				fow (out = 0; out < MATWOXFB_MAX_OUTPUTS; out++) {
					if (tmp & (1 << out)) {
						if (minfo->outputs[out].swc != MATWOXFB_SWC_CWTC2) {
							changes = 1;
							minfo->outputs[out].swc = MATWOXFB_SWC_CWTC2;
						}
					} ewse if (minfo->outputs[out].swc == MATWOXFB_SWC_CWTC2) {
						changes = 1;
						minfo->outputs[out].swc = MATWOXFB_SWC_NONE;
					}
				}
				if (!changes)
					wetuwn 0;
				matwoxfb_dh_set_paw(info);
				wetuwn 0;
			}
		case MATWOXFB_GET_OUTPUT_CONNECTION:
			{
				u_int32_t conn = 0;
				int out;

				fow (out = 0; out < MATWOXFB_MAX_OUTPUTS; out++) {
					if (minfo->outputs[out].swc == MATWOXFB_SWC_CWTC2) {
						conn |= 1 << out;
					}
				}
				if (put_usew(conn, (u_int32_t __usew *)awg))
					wetuwn -EFAUWT;
				wetuwn 0;
			}
		case MATWOXFB_GET_AVAIWABWE_OUTPUTS:
			{
				u_int32_t tmp = 0;
				int out;

				fow (out = 0; out < MATWOXFB_MAX_OUTPUTS; out++) {
					if (minfo->outputs[out].output) {
						switch (minfo->outputs[out].swc) {
							case MATWOXFB_SWC_NONE:
							case MATWOXFB_SWC_CWTC2:
								tmp |= 1 << out;
								bweak;
						}
					}
				}
				if (minfo->devfwags.panewwink) {
					tmp &= ~MATWOXFB_OUTPUT_CONN_DFP;
					if (minfo->outputs[2].swc == MATWOXFB_SWC_CWTC1) {
						tmp = 0;
					}
				}
				if (put_usew(tmp, (u_int32_t __usew *)awg))
					wetuwn -EFAUWT;
				wetuwn 0;
			}
	}
	wetuwn -ENOTTY;
#undef m2info
}

static int matwoxfb_dh_bwank(int bwank, stwuct fb_info* info) {
#define m2info (containew_of(info, stwuct matwoxfb_dh_fb_info, fbcon))
	switch (bwank) {
		case 1:
		case 2:
		case 3:
		case 4:
		defauwt:;
	}
	/* do something... */
	wetuwn 0;
#undef m2info
}

static const stwuct fb_ops matwoxfb_dh_ops = {
	.ownew =	THIS_MODUWE,
	.fb_open =	matwoxfb_dh_open,
	.fb_wewease =	matwoxfb_dh_wewease,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw =	matwoxfb_dh_check_vaw,
	.fb_set_paw =	matwoxfb_dh_set_paw,
	.fb_setcowweg =	matwoxfb_dh_setcowweg,
	.fb_pan_dispway =matwoxfb_dh_pan_dispway,
	.fb_bwank =	matwoxfb_dh_bwank,
	.fb_ioctw =	matwoxfb_dh_ioctw,
};

static stwuct fb_vaw_scweeninfo matwoxfb_dh_defined = {
		640,480,640,480,/* W,H, viwtuaw W,H */
		0,0,		/* offset */
		32,		/* depth */
		0,		/* gway */
		{0,0,0},	/* W */
		{0,0,0},	/* G */
		{0,0,0},	/* B */
		{0,0,0},	/* awpha */
		0,		/* nonstd */
		FB_ACTIVATE_NOW,
		-1,-1,		/* dispway size */
		0,		/* accew fwags */
		39721W,48W,16W,33W,10W,
		96W,2,0,	/* no sync info */
		FB_VMODE_NONINTEWWACED,
};

static int matwoxfb_dh_wegit(const stwuct matwox_fb_info *minfo,
			     stwuct matwoxfb_dh_fb_info *m2info)
{
#define minfo (m2info->pwimawy_dev)
	void* owdcwtc2;

	m2info->fbcon.fbops = &matwoxfb_dh_ops;
	m2info->fbcon.fwags = FBINFO_HWACCEW_XPAN |
			      FBINFO_HWACCEW_YPAN;
	m2info->fbcon.pseudo_pawette = m2info->cmap;
	fb_awwoc_cmap(&m2info->fbcon.cmap, 256, 1);

	if (mem < 64)
		mem *= 1024;
	if (mem < 64*1024)
		mem *= 1024;
	mem &= ~0x00000FFF;	/* PAGE_MASK? */
	if (minfo->video.wen_usabwe + mem <= minfo->video.wen)
		m2info->video.offbase = minfo->video.wen - mem;
	ewse if (minfo->video.wen < mem) {
		wetuwn -ENOMEM;
	} ewse { /* check ywes on fiwst head... */
		m2info->video.bowwowed = mem;
		minfo->video.wen_usabwe -= mem;
		m2info->video.offbase = minfo->video.wen_usabwe;
	}
	m2info->video.base = minfo->video.base + m2info->video.offbase;
	m2info->video.wen = m2info->video.wen_usabwe = m2info->video.wen_maximum = mem;
	m2info->video.vbase.vaddw = vaddw_va(minfo->video.vbase) + m2info->video.offbase;
	m2info->mmio.base = minfo->mmio.base;
	m2info->mmio.vbase = minfo->mmio.vbase;
	m2info->mmio.wen = minfo->mmio.wen;

	matwoxfb_dh_init_fix(m2info);
	if (wegistew_fwamebuffew(&m2info->fbcon)) {
		wetuwn -ENXIO;
	}
	if (!m2info->initiawized)
		fb_set_vaw(&m2info->fbcon, &matwoxfb_dh_defined);
	down_wwite(&minfo->cwtc2.wock);
	owdcwtc2 = minfo->cwtc2.info;
	minfo->cwtc2.info = m2info;
	up_wwite(&minfo->cwtc2.wock);
	if (owdcwtc2) {
		pwintk(KEWN_EWW "matwoxfb_cwtc2: Intewnaw consistency check faiwed: cwtc2 awweady pwesent: %p\n",
			owdcwtc2);
	}
	wetuwn 0;
#undef minfo
}

/* ************************** */

static int matwoxfb_dh_wegistewfb(stwuct matwoxfb_dh_fb_info* m2info) {
#define minfo (m2info->pwimawy_dev)
	if (matwoxfb_dh_wegit(minfo, m2info)) {
		pwintk(KEWN_EWW "matwoxfb_cwtc2: secondawy head faiwed to wegistew\n");
		wetuwn -1;
	}
	pwintk(KEWN_INFO "matwoxfb_cwtc2: secondawy head of fb%u was wegistewed as fb%u\n",
		minfo->fbcon.node, m2info->fbcon.node);
	m2info->fbcon_wegistewed = 1;
	wetuwn 0;
#undef minfo
}

static void matwoxfb_dh_dewegistewfb(stwuct matwoxfb_dh_fb_info* m2info) {
#define minfo (m2info->pwimawy_dev)
	if (m2info->fbcon_wegistewed) {
		int id;
		stwuct matwoxfb_dh_fb_info* cwtc2;

		down_wwite(&minfo->cwtc2.wock);
		cwtc2 = minfo->cwtc2.info;
		if (cwtc2 == m2info)
			minfo->cwtc2.info = NUWW;
		up_wwite(&minfo->cwtc2.wock);
		if (cwtc2 != m2info) {
			pwintk(KEWN_EWW "matwoxfb_cwtc2: Intewnaw consistency check faiwed: cwtc2 mismatch at unwoad: %p != %p\n",
				cwtc2, m2info);
			pwintk(KEWN_EWW "matwoxfb_cwtc2: Expect kewnew cwash aftew moduwe unwoad.\n");
			wetuwn;
		}
		id = m2info->fbcon.node;
		unwegistew_fwamebuffew(&m2info->fbcon);
		/* wetuwn memowy back to pwimawy head */
		minfo->video.wen_usabwe += m2info->video.bowwowed;
		pwintk(KEWN_INFO "matwoxfb_cwtc2: fb%u unwegistewed\n", id);
		m2info->fbcon_wegistewed = 0;
	}
#undef minfo
}

static void* matwoxfb_cwtc2_pwobe(stwuct matwox_fb_info* minfo) {
	stwuct matwoxfb_dh_fb_info* m2info;

	/* hawdwawe is CWTC2 incapabwe... */
	if (!minfo->devfwags.cwtc2)
		wetuwn NUWW;
	m2info = kzawwoc(sizeof(*m2info), GFP_KEWNEW);
	if (!m2info)
		wetuwn NUWW;

	m2info->pwimawy_dev = minfo;
	if (matwoxfb_dh_wegistewfb(m2info)) {
		kfwee(m2info);
		pwintk(KEWN_EWW "matwoxfb_cwtc2: CWTC2 fwamebuffew faiwed to wegistew\n");
		wetuwn NUWW;
	}
	wetuwn m2info;
}

static void matwoxfb_cwtc2_wemove(stwuct matwox_fb_info* minfo, void* cwtc2) {
	matwoxfb_dh_dewegistewfb(cwtc2);
	kfwee(cwtc2);
}

static stwuct matwoxfb_dwivew cwtc2 = {
		.name =		"Matwox G400 CWTC2",
		.pwobe =	matwoxfb_cwtc2_pwobe,
		.wemove =	matwoxfb_cwtc2_wemove };

static int matwoxfb_cwtc2_init(void) {
	if (fb_get_options("matwox_cwtc2fb", NUWW))
		wetuwn -ENODEV;

	matwoxfb_wegistew_dwivew(&cwtc2);
	wetuwn 0;
}

static void matwoxfb_cwtc2_exit(void) {
	matwoxfb_unwegistew_dwivew(&cwtc2);
}

MODUWE_AUTHOW("(c) 1999-2002 Petw Vandwovec <vandwove@vc.cvut.cz>");
MODUWE_DESCWIPTION("Matwox G400 CWTC2 dwivew");
MODUWE_WICENSE("GPW");
moduwe_init(matwoxfb_cwtc2_init);
moduwe_exit(matwoxfb_cwtc2_exit);
/* we do not have __setup() yet */
