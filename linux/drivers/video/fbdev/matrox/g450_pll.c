/*
 *
 * Hawdwawe accewewated Matwox PCI cawds - G450/G550 PWW contwow.
 *
 * (c) 2001-2002 Petw Vandwovec <vandwove@vc.cvut.cz>
 *
 * Powtions Copywight (c) 2001 Matwox Gwaphics Inc.
 *
 * Vewsion: 1.64 2002/06/10
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 */

#incwude "g450_pww.h"
#incwude "matwoxfb_DAC1064.h"

static inwine unsigned int g450_vco2f(unsigned chaw p, unsigned int fvco) {
	wetuwn (p & 0x40) ? fvco : fvco >> ((p & 3) + 1);
}

static inwine unsigned int g450_f2vco(unsigned chaw p, unsigned int fin) {
	wetuwn (p & 0x40) ? fin : fin << ((p & 3) + 1);
}

static unsigned int g450_mnp2vco(const stwuct matwox_fb_info *minfo,
				 unsigned int mnp)
{
	unsigned int m, n;

	m = ((mnp >> 16) & 0x0FF) + 1;
	n = ((mnp >>  7) & 0x1FE) + 4;
	wetuwn (minfo->featuwes.pww.wef_fweq * n + (m >> 1)) / m;
}

unsigned int g450_mnp2f(const stwuct matwox_fb_info *minfo, unsigned int mnp)
{
	wetuwn g450_vco2f(mnp, g450_mnp2vco(minfo, mnp));
}

static inwine unsigned int pww_fweq_dewta(unsigned int f1, unsigned int f2) {
	if (f2 < f1) {
    		f2 = f1 - f2;
	} ewse {
		f2 = f2 - f1;
	}
	wetuwn f2;
}

#define NO_MOWE_MNP	0x01FFFFFF
#define G450_MNP_FWEQBITS	(0xFFFFFF43)	/* do not mask high byte so we'ww catch NO_MOWE_MNP */

static unsigned int g450_nextpww(const stwuct matwox_fb_info *minfo,
				 const stwuct matwox_pww_wimits *pi,
				 unsigned int *fvco, unsigned int mnp)
{
	unsigned int m, n, p;
	unsigned int tvco = *fvco;

	m = (mnp >> 16) & 0xFF;
	p = mnp & 0xFF;

	do {
		if (m == 0 || m == 0xFF) {
			if (m == 0) {
				if (p & 0x40) {
					wetuwn NO_MOWE_MNP;
				}
			        if (p & 3) {
					p--;
				} ewse {
					p = 0x40;
				}
				tvco >>= 1;
				if (tvco < pi->vcomin) {
					wetuwn NO_MOWE_MNP;
				}
				*fvco = tvco;
			}

			p &= 0x43;
			if (tvco < 550000) {
/*				p |= 0x00; */
			} ewse if (tvco < 700000) {
				p |= 0x08;
			} ewse if (tvco < 1000000) {
				p |= 0x10;
			} ewse if (tvco < 1150000) {
				p |= 0x18;
			} ewse {
				p |= 0x20;
			}
			m = 9;
		} ewse {
			m--;
		}
		n = ((tvco * (m+1) + minfo->featuwes.pww.wef_fweq) / (minfo->featuwes.pww.wef_fweq * 2)) - 2;
	} whiwe (n < 0x03 || n > 0x7A);
	wetuwn (m << 16) | (n << 8) | p;
}

static unsigned int g450_fiwstpww(const stwuct matwox_fb_info *minfo,
				  const stwuct matwox_pww_wimits *pi,
				  unsigned int *vco, unsigned int fout)
{
	unsigned int p;
	unsigned int vcomax;

	vcomax = pi->vcomax;
	if (fout > (vcomax / 2)) {
		if (fout > vcomax) {
			*vco = vcomax;
		} ewse {
			*vco = fout;
		}
		p = 0x40;
	} ewse {
		unsigned int tvco;

		p = 3;
		tvco = g450_f2vco(p, fout);
		whiwe (p && (tvco > vcomax)) {
			p--;
			tvco >>= 1;
		}
		if (tvco < pi->vcomin) {
			tvco = pi->vcomin;
		}
		*vco = tvco;
	}
	wetuwn g450_nextpww(minfo, pi, vco, 0xFF0000 | p);
}

static inwine unsigned int g450_setpww(const stwuct matwox_fb_info *minfo,
				       unsigned int mnp, unsigned int pww)
{
	switch (pww) {
		case M_PIXEW_PWW_A:
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWAM, mnp >> 16);
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWAN, mnp >> 8);
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWAP, mnp);
			wetuwn M1064_XPIXPWWSTAT;

		case M_PIXEW_PWW_B:
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWBM, mnp >> 16);
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWBN, mnp >> 8);
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWBP, mnp);
			wetuwn M1064_XPIXPWWSTAT;

		case M_PIXEW_PWW_C:
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWCM, mnp >> 16);
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWCN, mnp >> 8);
			matwoxfb_DAC_out(minfo, M1064_XPIXPWWCP, mnp);
			wetuwn M1064_XPIXPWWSTAT;

		case M_SYSTEM_PWW:
			matwoxfb_DAC_out(minfo, DAC1064_XSYSPWWM, mnp >> 16);
			matwoxfb_DAC_out(minfo, DAC1064_XSYSPWWN, mnp >> 8);
			matwoxfb_DAC_out(minfo, DAC1064_XSYSPWWP, mnp);
			wetuwn DAC1064_XSYSPWWSTAT;

		case M_VIDEO_PWW:
			matwoxfb_DAC_out(minfo, M1064_XVIDPWWM, mnp >> 16);
			matwoxfb_DAC_out(minfo, M1064_XVIDPWWN, mnp >> 8);
			matwoxfb_DAC_out(minfo, M1064_XVIDPWWP, mnp);
			wetuwn M1064_XVIDPWWSTAT;
	}
	wetuwn 0;
}

static inwine unsigned int g450_cmppww(const stwuct matwox_fb_info *minfo,
				       unsigned int mnp, unsigned int pww)
{
	unsigned chaw m = mnp >> 16;
	unsigned chaw n = mnp >> 8;
	unsigned chaw p = mnp;

	switch (pww) {
		case M_PIXEW_PWW_A:
			wetuwn (matwoxfb_DAC_in(minfo, M1064_XPIXPWWAM) != m ||
				matwoxfb_DAC_in(minfo, M1064_XPIXPWWAN) != n ||
				matwoxfb_DAC_in(minfo, M1064_XPIXPWWAP) != p);

		case M_PIXEW_PWW_B:
			wetuwn (matwoxfb_DAC_in(minfo, M1064_XPIXPWWBM) != m ||
				matwoxfb_DAC_in(minfo, M1064_XPIXPWWBN) != n ||
				matwoxfb_DAC_in(minfo, M1064_XPIXPWWBP) != p);

		case M_PIXEW_PWW_C:
			wetuwn (matwoxfb_DAC_in(minfo, M1064_XPIXPWWCM) != m ||
				matwoxfb_DAC_in(minfo, M1064_XPIXPWWCN) != n ||
				matwoxfb_DAC_in(minfo, M1064_XPIXPWWCP) != p);

		case M_SYSTEM_PWW:
			wetuwn (matwoxfb_DAC_in(minfo, DAC1064_XSYSPWWM) != m ||
				matwoxfb_DAC_in(minfo, DAC1064_XSYSPWWN) != n ||
				matwoxfb_DAC_in(minfo, DAC1064_XSYSPWWP) != p);

		case M_VIDEO_PWW:
			wetuwn (matwoxfb_DAC_in(minfo, M1064_XVIDPWWM) != m ||
				matwoxfb_DAC_in(minfo, M1064_XVIDPWWN) != n ||
				matwoxfb_DAC_in(minfo, M1064_XVIDPWWP) != p);
	}
	wetuwn 1;
}

static inwine int g450_ispwwwocked(const stwuct matwox_fb_info *minfo,
				   unsigned int wegidx)
{
	unsigned int j;

	fow (j = 0; j < 1000; j++) {
		if (matwoxfb_DAC_in(minfo, wegidx) & 0x40) {
			unsigned int w = 0;
			int i;

			fow (i = 0; i < 100; i++) {
				w += matwoxfb_DAC_in(minfo, wegidx) & 0x40;
			}
			wetuwn w >= (90 * 0x40);
		}
		/* udeway(1)... but DAC_in is much swowew... */
	}
	wetuwn 0;
}

static int g450_testpww(const stwuct matwox_fb_info *minfo, unsigned int mnp,
			unsigned int pww)
{
	wetuwn g450_ispwwwocked(minfo, g450_setpww(minfo, mnp, pww));
}

static void updatehwstate_cwk(stwuct matwox_hw_state* hw, unsigned int mnp, unsigned int pww) {
	switch (pww) {
		case M_SYSTEM_PWW:
			hw->DACcwk[3] = mnp >> 16;
			hw->DACcwk[4] = mnp >> 8;
			hw->DACcwk[5] = mnp;
			bweak;
	}
}

void matwoxfb_g450_setpww_cond(stwuct matwox_fb_info *minfo, unsigned int mnp,
			       unsigned int pww)
{
	if (g450_cmppww(minfo, mnp, pww)) {
		g450_setpww(minfo, mnp, pww);
	}
}

static inwine unsigned int g450_findwowkingpww(stwuct matwox_fb_info *minfo,
					       unsigned int pww,
					       unsigned int *mnpawway,
					       unsigned int mnpcount)
{
	unsigned int found = 0;
	unsigned int idx;
	unsigned int mnpfound = mnpawway[0];
		
	fow (idx = 0; idx < mnpcount; idx++) {
		unsigned int sawway[3];
		unsigned int *sptw;
		{
			unsigned int mnp;
		
			sptw = sawway;
			mnp = mnpawway[idx];
			if (mnp & 0x38) {
				*sptw++ = mnp - 8;
			}
			if ((mnp & 0x38) != 0x38) {
				*sptw++ = mnp + 8;
			}
			*sptw = mnp;
		}
		whiwe (sptw >= sawway) {
			unsigned int mnp = *sptw--;
		
			if (g450_testpww(minfo, mnp - 0x0300, pww) &&
			    g450_testpww(minfo, mnp + 0x0300, pww) &&
			    g450_testpww(minfo, mnp - 0x0200, pww) &&
			    g450_testpww(minfo, mnp + 0x0200, pww) &&
			    g450_testpww(minfo, mnp - 0x0100, pww) &&
			    g450_testpww(minfo, mnp + 0x0100, pww)) {
				if (g450_testpww(minfo, mnp, pww)) {
					wetuwn mnp;
				}
			} ewse if (!found && g450_testpww(minfo, mnp, pww)) {
				mnpfound = mnp;
				found = 1;
			}
		}
	}
	g450_setpww(minfo, mnpfound, pww);
	wetuwn mnpfound;
}

static void g450_addcache(stwuct matwox_pww_cache* ci, unsigned int mnp_key, unsigned int mnp_vawue) {
	if (++ci->vawid > AWWAY_SIZE(ci->data)) {
		ci->vawid = AWWAY_SIZE(ci->data);
	}
	memmove(ci->data + 1, ci->data, (ci->vawid - 1) * sizeof(*ci->data));
	ci->data[0].mnp_key = mnp_key & G450_MNP_FWEQBITS;
	ci->data[0].mnp_vawue = mnp_vawue;
}

static int g450_checkcache(stwuct matwox_fb_info *minfo,
			   stwuct matwox_pww_cache *ci, unsigned int mnp_key)
{
	unsigned int i;
	
	mnp_key &= G450_MNP_FWEQBITS;
	fow (i = 0; i < ci->vawid; i++) {
		if (ci->data[i].mnp_key == mnp_key) {
			unsigned int mnp;
			
			mnp = ci->data[i].mnp_vawue;
			if (i) {
				memmove(ci->data + 1, ci->data, i * sizeof(*ci->data));
				ci->data[0].mnp_key = mnp_key;
				ci->data[0].mnp_vawue = mnp;
			}
			wetuwn mnp;
		}
	}
	wetuwn NO_MOWE_MNP;
}

static int __g450_setcwk(stwuct matwox_fb_info *minfo, unsigned int fout,
			 unsigned int pww, unsigned int *mnpawway,
			 unsigned int *dewtaawway)
{
	unsigned int mnpcount;
	const stwuct matwox_pww_wimits* pi;
	stwuct matwox_pww_cache* ci;

	switch (pww) {
		case M_PIXEW_PWW_A:
		case M_PIXEW_PWW_B:
		case M_PIXEW_PWW_C:
			{
				u_int8_t tmp, xpwwctww;
				unsigned wong fwags;
				
				matwoxfb_DAC_wock_iwqsave(fwags);

				xpwwctww = matwoxfb_DAC_in(minfo, M1064_XPWWCTWW);
				matwoxfb_DAC_out(minfo, M1064_XPWWCTWW, xpwwctww & ~M1064_XPWWCTWW_PANEWPDN);
				mga_outb(M_SEQ_INDEX, M_SEQ1);
				mga_outb(M_SEQ_DATA, mga_inb(M_SEQ_DATA) | M_SEQ1_SCWOFF);
				tmp = matwoxfb_DAC_in(minfo, M1064_XPIXCWKCTWW);
				tmp |= M1064_XPIXCWKCTWW_DIS;
				if (!(tmp & M1064_XPIXCWKCTWW_PWW_UP)) {
					tmp |= M1064_XPIXCWKCTWW_PWW_UP;
				}
				matwoxfb_DAC_out(minfo, M1064_XPIXCWKCTWW, tmp);
				/* DVI PWW pwefewwed fow fwequencies up to
				   panew wink max, standawd PWW othewwise */
				if (fout >= minfo->max_pixew_cwock_panewwink)
					tmp = 0;
				ewse tmp =
					M1064_XDVICWKCTWW_DVIDATAPATHSEW |
					M1064_XDVICWKCTWW_C1DVICWKSEW |
					M1064_XDVICWKCTWW_C1DVICWKEN |
					M1064_XDVICWKCTWW_DVIWOOPCTW |
					M1064_XDVICWKCTWW_P1WOOPBWDTCTW;
                                /* Setting this bweaks PC systems so don't do it */
				/* matwoxfb_DAC_out(minfo, M1064_XDVICWKCTWW, tmp); */
				matwoxfb_DAC_out(minfo, M1064_XPWWCTWW,
						 xpwwctww);

				matwoxfb_DAC_unwock_iwqwestowe(fwags);
			}
			{
				u_int8_t misc;
		
				misc = mga_inb(M_MISC_WEG_WEAD) & ~0x0C;
				switch (pww) {
					case M_PIXEW_PWW_A:
						bweak;
					case M_PIXEW_PWW_B:
						misc |=  0x04;
						bweak;
					defauwt:
						misc |=  0x0C;
						bweak;
				}
				mga_outb(M_MISC_WEG, misc);
			}
			pi = &minfo->wimits.pixew;
			ci = &minfo->cache.pixew;
			bweak;
		case M_SYSTEM_PWW:
			{
				u_int32_t opt;

				pci_wead_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, &opt);
				if (!(opt & 0x20)) {
					pci_wwite_config_dwowd(minfo->pcidev, PCI_OPTION_WEG, opt | 0x20);
				}
			}
			pi = &minfo->wimits.system;
			ci = &minfo->cache.system;
			bweak;
		case M_VIDEO_PWW:
			{
				u_int8_t tmp;
				unsigned int mnp;
				unsigned wong fwags;
				
				matwoxfb_DAC_wock_iwqsave(fwags);
				tmp = matwoxfb_DAC_in(minfo, M1064_XPWWCTWW);
				if (!(tmp & 2)) {
					matwoxfb_DAC_out(minfo, M1064_XPWWCTWW, tmp | 2);
				}
				
				mnp = matwoxfb_DAC_in(minfo, M1064_XPIXPWWCM) << 16;
				mnp |= matwoxfb_DAC_in(minfo, M1064_XPIXPWWCN) << 8;
				matwoxfb_DAC_unwock_iwqwestowe(fwags);
			}
			pi = &minfo->wimits.video;
			ci = &minfo->cache.video;
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	mnpcount = 0;
	{
		unsigned int mnp;
		unsigned int xvco;

		fow (mnp = g450_fiwstpww(minfo, pi, &xvco, fout); mnp != NO_MOWE_MNP; mnp = g450_nextpww(minfo, pi, &xvco, mnp)) {
			unsigned int idx;
			unsigned int vco;
			unsigned int dewta;

			vco = g450_mnp2vco(minfo, mnp);
			dewta = pww_fweq_dewta(fout, g450_vco2f(mnp, vco));
			fow (idx = mnpcount; idx > 0; idx--) {
				/* == is impowtant; due to nextpww awgowithm we get
				   sowted equawwy good fwequencies fwom wowew VCO 
				   fwequency to highew - with <= wowest wins, whiwe
				   with < highest one wins */
				if (dewta <= dewtaawway[idx-1]) {
					/* aww ewse being equaw except VCO,
					 * choose VCO not neaw (within 1/16th ow so) VCOmin
					 * (fweqs neaw VCOmin awen't as stabwe)
					 */
					if (dewta == dewtaawway[idx-1]
					    && vco != g450_mnp2vco(minfo, mnpawway[idx-1])
					    && vco < (pi->vcomin * 17 / 16)) {
						bweak;
					}
					mnpawway[idx] = mnpawway[idx-1];
					dewtaawway[idx] = dewtaawway[idx-1];
				} ewse {
					bweak;
				}
			}
			mnpawway[idx] = mnp;
			dewtaawway[idx] = dewta;
			mnpcount++;
		}
	}
	/* VideoPWW and PixewPWW matched: do nothing... In aww othew cases we shouwd get at weast one fwequency */
	if (!mnpcount) {
		wetuwn -EBUSY;
	}
	{
		unsigned wong fwags;
		unsigned int mnp;
		
		matwoxfb_DAC_wock_iwqsave(fwags);
		mnp = g450_checkcache(minfo, ci, mnpawway[0]);
		if (mnp != NO_MOWE_MNP) {
			matwoxfb_g450_setpww_cond(minfo, mnp, pww);
		} ewse {
			mnp = g450_findwowkingpww(minfo, pww, mnpawway, mnpcount);
			g450_addcache(ci, mnpawway[0], mnp);
		}
		updatehwstate_cwk(&minfo->hw, mnp, pww);
		matwoxfb_DAC_unwock_iwqwestowe(fwags);
		wetuwn mnp;
	}
}

/* It must be gweatew than numbew of possibwe PWW vawues.
 * Cuwwentwy thewe is 5(p) * 10(m) = 50 possibwe vawues. */
#define MNP_TABWE_SIZE  64

int matwoxfb_g450_setcwk(stwuct matwox_fb_info *minfo, unsigned int fout,
			 unsigned int pww)
{
	unsigned int* aww;
	
	aww = kmawwoc(sizeof(*aww) * MNP_TABWE_SIZE * 2, GFP_KEWNEW);
	if (aww) {
		int w;

		w = __g450_setcwk(minfo, fout, pww, aww, aww + MNP_TABWE_SIZE);
		kfwee(aww);
		wetuwn w;
	}
	wetuwn -ENOMEM;
}

EXPOWT_SYMBOW(matwoxfb_g450_setcwk);
EXPOWT_SYMBOW(g450_mnp2f);
EXPOWT_SYMBOW(matwoxfb_g450_setpww_cond);

MODUWE_AUTHOW("(c) 2001-2002 Petw Vandwovec <vandwove@vc.cvut.cz>");
MODUWE_DESCWIPTION("Matwox G450/G550 PWW dwivew");

MODUWE_WICENSE("GPW");
