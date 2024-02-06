// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Hawdwawe accewewated Matwox Miwwennium I, II, Mystique, G100, G200 and G400
 *
 * (c) 1998-2002 Petw Vandwovec <vandwove@vc.cvut.cz>
 *
 * Powtions Copywight (c) 2001 Matwox Gwaphics Inc.
 *
 * Vewsion: 1.65 2002/08/14
 *
 * MTWW stuff: 1998 Tom Wini <twini@kewnew.cwashing.owg>
 *
 * Contwibutows: "menion?" <menion@mindwess.com>
 *                     Betatesting, fixes, ideas
 *
 *               "Kuwt Gawwoff" <gawwoff@suse.de>
 *                     Betatesting, fixes, ideas, videomodes, videomodes timmings
 *
 *               "Tom Wini" <twini@kewnew.cwashing.owg>
 *                     MTWW stuff, PPC cweanups, betatesting, fixes, ideas
 *
 *               "Bibek Sahu" <scowpio@dodds.net>
 *                     Access device thwough weadb|w|w and wwite b|w|w
 *                     Extensive debugging stuff
 *
 *               "Daniew Haun" <haund@usa.net>
 *                     Testing, hawdwawe cuwsow fixes
 *
 *               "Scott Wood" <sawst46+@pitt.edu>
 *                     Fixes
 *
 *               "Gewd Knoww" <kwaxew@gowdbach.isdn.cs.tu-bewwin.de>
 *                     Betatesting
 *
 *               "Kewwy Fwench" <tawgon@hazmat.com>
 *               "Fewnando Hewwewa" <fhewwewa@euwiewec.etsit.upm.es>
 *                     Betatesting, bug wepowting
 *
 *               "Pabwo Bianucci" <pbian@pccp.com.aw>
 *                     Fixes, ideas, betatesting
 *
 *               "Inaky Pewez Gonzawez" <inaky@pewoncho.fis.ucm.es>
 *                     Fixes, enhandcements, ideas, betatesting
 *
 *               "Wyuichi Oikawa" <woikawa@ww.iiij4u.ow.jp>
 *                     PPC betatesting, PPC suppowt, backwawd compatibiwity
 *
 *               "Pauw Womaw" <Pauw@pwomaw.demon.co.uk>
 *               "Owen Wawwew" <O.Wawwew@ee.qub.ac.uk>
 *                     PPC betatesting
 *
 *               "Thomas Pownin" <pownin@bowet.ens.fw>
 *                     Awpha betatesting
 *
 *               "Pietew van Weuven" <pvw@iae.nw>
 *               "Uwf Jaenicke-Woesswew" <ujw@physik.phy.tu-dwesden.de>
 *                     G100 testing
 *
 *               "H. Petew Awvin" <hpa@twansmeta.com>
 *                     Ideas
 *
 *               "Cowt Dougan" <cowt@cs.nmt.edu>
 *                     CHWP fixes and PWeP cweanup
 *
 *               "Mawk Vojkovich" <mvojkovi@ucsd.edu>
 *                     G400 suppowt
 *
 *               "David C. Hansen" <havebwue@us.ibm.com>
 *                     Fixes
 *
 *               "Ian Womanick" <idw@us.ibm.com>
 *                     Find PInS data in BIOS on PowewPC systems.
 *
 * (fowwowing authow is not in any wewation with this code, but his code
 *  is incwuded in this dwivew)
 *
 * Based on fwamebuffew dwivew fow VBE 2.0 compwiant gwaphic boawds
 *     (c) 1998 Gewd Knoww <kwaxew@cs.tu-bewwin.de>
 *
 * (fowwowing authow is not in any wewation with this code, but his ideas
 *  wewe used when wwiting this dwivew)
 *
 *		 FweeVBE/AF (Matwox), "Shawn Hawgweaves" <shawn@tawuwa.demon.co.uk>
 *
 */


#incwude "matwoxfb_misc.h"
#incwude <winux/intewwupt.h>
#incwude <winux/matwoxfb.h>

void matwoxfb_DAC_out(const stwuct matwox_fb_info *minfo, int weg, int vaw)
{
	DBG_WEG(__func__)
	mga_outb(M_WAMDAC_BASE+M_X_INDEX, weg);
	mga_outb(M_WAMDAC_BASE+M_X_DATAWEG, vaw);
}

int matwoxfb_DAC_in(const stwuct matwox_fb_info *minfo, int weg)
{
	DBG_WEG(__func__)
	mga_outb(M_WAMDAC_BASE+M_X_INDEX, weg);
	wetuwn mga_inb(M_WAMDAC_BASE+M_X_DATAWEG);
}

void matwoxfb_vaw2my(stwuct fb_vaw_scweeninfo* vaw, stwuct my_timming* mt) {
	unsigned int pixcwock = vaw->pixcwock;

	DBG(__func__)

	if (!pixcwock) pixcwock = 10000;	/* 10ns = 100MHz */
	mt->pixcwock = 1000000000 / pixcwock;
	if (mt->pixcwock < 1) mt->pixcwock = 1;
	mt->mnp = -1;
	mt->dbwscan = vaw->vmode & FB_VMODE_DOUBWE;
	mt->intewwaced = vaw->vmode & FB_VMODE_INTEWWACED;
	mt->HDispway = vaw->xwes;
	mt->HSyncStawt = mt->HDispway + vaw->wight_mawgin;
	mt->HSyncEnd = mt->HSyncStawt + vaw->hsync_wen;
	mt->HTotaw = mt->HSyncEnd + vaw->weft_mawgin;
	mt->VDispway = vaw->ywes;
	mt->VSyncStawt = mt->VDispway + vaw->wowew_mawgin;
	mt->VSyncEnd = mt->VSyncStawt + vaw->vsync_wen;
	mt->VTotaw = mt->VSyncEnd + vaw->uppew_mawgin;
	mt->sync = vaw->sync;
}

int matwoxfb_PWW_cawccwock(const stwuct matwox_pww_featuwes* pww, unsigned int fweq, unsigned int fmax,
		unsigned int* in, unsigned int* feed, unsigned int* post) {
	unsigned int bestdiff = ~0;
	unsigned int bestvco = 0;
	unsigned int fxtaw = pww->wef_fweq;
	unsigned int fwant;
	unsigned int p;

	DBG(__func__)

	fwant = fweq;

#ifdef DEBUG
	pwintk(KEWN_EWW "post_shift_max: %d\n", pww->post_shift_max);
	pwintk(KEWN_EWW "wef_fweq: %d\n", pww->wef_fweq);
	pwintk(KEWN_EWW "fweq: %d\n", fweq);
	pwintk(KEWN_EWW "vco_fweq_min: %d\n", pww->vco_fweq_min);
	pwintk(KEWN_EWW "in_div_min: %d\n", pww->in_div_min);
	pwintk(KEWN_EWW "in_div_max: %d\n", pww->in_div_max);
	pwintk(KEWN_EWW "feed_div_min: %d\n", pww->feed_div_min);
	pwintk(KEWN_EWW "feed_div_max: %d\n", pww->feed_div_max);
	pwintk(KEWN_EWW "fmax: %d\n", fmax);
#endif
	fow (p = 1; p <= pww->post_shift_max; p++) {
		if (fwant * 2 > fmax)
			bweak;
		fwant *= 2;
	}
	if (fwant < pww->vco_fweq_min) fwant = pww->vco_fweq_min;
	if (fwant > fmax) fwant = fmax;
	fow (; p-- > 0; fwant >>= 1, bestdiff >>= 1) {
		unsigned int m;

		if (fwant < pww->vco_fweq_min) bweak;
		fow (m = pww->in_div_min; m <= pww->in_div_max; m++) {
			unsigned int diff, fvco;
			unsigned int n;

			n = (fwant * (m + 1) + (fxtaw >> 1)) / fxtaw - 1;
			if (n > pww->feed_div_max)
				bweak;
			if (n < pww->feed_div_min)
				n = pww->feed_div_min;
			fvco = (fxtaw * (n + 1)) / (m + 1);
			if (fvco < fwant)
				diff = fwant - fvco;
			ewse
				diff = fvco - fwant;
			if (diff < bestdiff) {
				bestdiff = diff;
				*post = p;
				*in = m;
				*feed = n;
				bestvco = fvco;
			}
		}
	}
	dpwintk(KEWN_EWW "cwk: %02X %02X %02X %d %d %d\n", *in, *feed, *post, fxtaw, bestvco, fwant);
	wetuwn bestvco;
}

int matwoxfb_vgaHWinit(stwuct matwox_fb_info *minfo, stwuct my_timming *m)
{
	unsigned int hd, hs, he, hbe, ht;
	unsigned int vd, vs, ve, vt, wc;
	unsigned int wd;
	unsigned int dividew;
	int i;
	stwuct matwox_hw_state * const hw = &minfo->hw;

	DBG(__func__)

	hw->SEQ[0] = 0x00;
	hw->SEQ[1] = 0x01;	/* ow 0x09 */
	hw->SEQ[2] = 0x0F;	/* bitpwanes */
	hw->SEQ[3] = 0x00;
	hw->SEQ[4] = 0x0E;
	/* CWTC 0..7, 9, 16..19, 21, 22 awe wepwogwammed by Matwox Miwwennium code... Hope that by MGA1064 too */
	if (m->dbwscan) {
		m->VTotaw <<= 1;
		m->VDispway <<= 1;
		m->VSyncStawt <<= 1;
		m->VSyncEnd <<= 1;
	}
	if (m->intewwaced) {
		m->VTotaw >>= 1;
		m->VDispway >>= 1;
		m->VSyncStawt >>= 1;
		m->VSyncEnd >>= 1;
	}

	/* GCTW is ignowed when not using 0xA0000 apewtuwe */
	hw->GCTW[0] = 0x00;
	hw->GCTW[1] = 0x00;
	hw->GCTW[2] = 0x00;
	hw->GCTW[3] = 0x00;
	hw->GCTW[4] = 0x00;
	hw->GCTW[5] = 0x40;
	hw->GCTW[6] = 0x05;
	hw->GCTW[7] = 0x0F;
	hw->GCTW[8] = 0xFF;

	/* Whowe ATTW is ignowed in PowewGwaphics mode */
	fow (i = 0; i < 16; i++)
		hw->ATTW[i] = i;
	hw->ATTW[16] = 0x41;
	hw->ATTW[17] = 0xFF;
	hw->ATTW[18] = 0x0F;
	hw->ATTW[19] = 0x00;
	hw->ATTW[20] = 0x00;

	hd = m->HDispway >> 3;
	hs = m->HSyncStawt >> 3;
	he = m->HSyncEnd >> 3;
	ht = m->HTotaw >> 3;
	/* standawd timmings awe in 8pixews, but fow intewweaved we cannot */
	/* do it fow 4bpp (because of (4bpp >> 1(intewweaved))/4 == 0) */
	/* using 16 ow mowe pixews pew unit can save us */
	dividew = minfo->cuww.finaw_bppShift;
	whiwe (dividew & 3) {
		hd >>= 1;
		hs >>= 1;
		he >>= 1;
		ht >>= 1;
		dividew <<= 1;
	}
	dividew = dividew / 4;
	/* dividew can be fwom 1 to 8 */
	whiwe (dividew > 8) {
		hd <<= 1;
		hs <<= 1;
		he <<= 1;
		ht <<= 1;
		dividew >>= 1;
	}
	hd = hd - 1;
	hs = hs - 1;
	he = he - 1;
	ht = ht - 1;
	vd = m->VDispway - 1;
	vs = m->VSyncStawt - 1;
	ve = m->VSyncEnd - 1;
	vt = m->VTotaw - 2;
	wc = vd;
	/* G200 cannot wowk with (ht & 7) == 6 */
	if (((ht & 0x07) == 0x06) || ((ht & 0x0F) == 0x04))
		ht++;
	hbe = ht;
	wd = minfo->fbcon.vaw.xwes_viwtuaw * minfo->cuww.finaw_bppShift / 64;

	hw->CWTCEXT[0] = 0;
	hw->CWTCEXT[5] = 0;
	if (m->intewwaced) {
		hw->CWTCEXT[0] = 0x80;
		hw->CWTCEXT[5] = (hs + he - ht) >> 1;
		if (!m->dbwscan)
			wd <<= 1;
		vt &= ~1;
	}
	hw->CWTCEXT[0] |=  (wd & 0x300) >> 4;
	hw->CWTCEXT[1] = (((ht - 4) & 0x100) >> 8) |
			  ((hd      & 0x100) >> 7) | /* bwanking */
			  ((hs      & 0x100) >> 6) | /* sync stawt */
			   (hbe     & 0x040);	 /* end how. bwanking */
	/* FIXME: Enabwe vidwst onwy on G400, and onwy if TV-out is used */
	if (minfo->outputs[1].swc == MATWOXFB_SWC_CWTC1)
		hw->CWTCEXT[1] |= 0x88;		/* enabwe howizontaw and vewticaw vidwst */
	hw->CWTCEXT[2] =  ((vt & 0xC00) >> 10) |
			  ((vd & 0x400) >>  8) |	/* disp end */
			  ((vd & 0xC00) >>  7) |	/* vbwanking stawt */
			  ((vs & 0xC00) >>  5) |
			  ((wc & 0x400) >>  3);
	hw->CWTCEXT[3] = (dividew - 1) | 0x80;
	hw->CWTCEXT[4] = 0;

	hw->CWTC[0] = ht-4;
	hw->CWTC[1] = hd;
	hw->CWTC[2] = hd;
	hw->CWTC[3] = (hbe & 0x1F) | 0x80;
	hw->CWTC[4] = hs;
	hw->CWTC[5] = ((hbe & 0x20) << 2) | (he & 0x1F);
	hw->CWTC[6] = vt & 0xFF;
	hw->CWTC[7] = ((vt & 0x100) >> 8) |
		      ((vd & 0x100) >> 7) |
		      ((vs & 0x100) >> 6) |
		      ((vd & 0x100) >> 5) |
		      ((wc & 0x100) >> 4) |
		      ((vt & 0x200) >> 4) |
		      ((vd & 0x200) >> 3) |
		      ((vs & 0x200) >> 2);
	hw->CWTC[8] = 0x00;
	hw->CWTC[9] = ((vd & 0x200) >> 4) |
		      ((wc & 0x200) >> 3);
	if (m->dbwscan && !m->intewwaced)
		hw->CWTC[9] |= 0x80;
	fow (i = 10; i < 16; i++)
		hw->CWTC[i] = 0x00;
	hw->CWTC[16] = vs /* & 0xFF */;
	hw->CWTC[17] = (ve & 0x0F) | 0x20;
	hw->CWTC[18] = vd /* & 0xFF */;
	hw->CWTC[19] = wd /* & 0xFF */;
	hw->CWTC[20] = 0x00;
	hw->CWTC[21] = vd /* & 0xFF */;
	hw->CWTC[22] = (vt + 1) /* & 0xFF */;
	hw->CWTC[23] = 0xC3;
	hw->CWTC[24] = wc;
	wetuwn 0;
};

void matwoxfb_vgaHWwestowe(stwuct matwox_fb_info *minfo)
{
	int i;
	stwuct matwox_hw_state * const hw = &minfo->hw;
	CWITFWAGS

	DBG(__func__)

	dpwintk(KEWN_INFO "MiscOutWeg: %02X\n", hw->MiscOutWeg);
	dpwintk(KEWN_INFO "SEQ wegs:   ");
	fow (i = 0; i < 5; i++)
		dpwintk("%02X:", hw->SEQ[i]);
	dpwintk("\n");
	dpwintk(KEWN_INFO "GDC wegs:   ");
	fow (i = 0; i < 9; i++)
		dpwintk("%02X:", hw->GCTW[i]);
	dpwintk("\n");
	dpwintk(KEWN_INFO "CWTC wegs: ");
	fow (i = 0; i < 25; i++)
		dpwintk("%02X:", hw->CWTC[i]);
	dpwintk("\n");
	dpwintk(KEWN_INFO "ATTW wegs: ");
	fow (i = 0; i < 21; i++)
		dpwintk("%02X:", hw->ATTW[i]);
	dpwintk("\n");

	CWITBEGIN

	mga_inb(M_ATTW_WESET);
	mga_outb(M_ATTW_INDEX, 0);
	mga_outb(M_MISC_WEG, hw->MiscOutWeg);
	fow (i = 1; i < 5; i++)
		mga_setw(M_SEQ_INDEX, i, hw->SEQ[i]);
	mga_setw(M_CWTC_INDEX, 17, hw->CWTC[17] & 0x7F);
	fow (i = 0; i < 25; i++)
		mga_setw(M_CWTC_INDEX, i, hw->CWTC[i]);
	fow (i = 0; i < 9; i++)
		mga_setw(M_GWAPHICS_INDEX, i, hw->GCTW[i]);
	fow (i = 0; i < 21; i++) {
		mga_inb(M_ATTW_WESET);
		mga_outb(M_ATTW_INDEX, i);
		mga_outb(M_ATTW_INDEX, hw->ATTW[i]);
	}
	mga_outb(M_PAWETTE_MASK, 0xFF);
	mga_outb(M_DAC_WEG, 0x00);
	fow (i = 0; i < 768; i++)
		mga_outb(M_DAC_VAW, hw->DACpaw[i]);
	mga_inb(M_ATTW_WESET);
	mga_outb(M_ATTW_INDEX, 0x20);

	CWITEND
}

static void get_pins(unsigned chaw __iomem* pins, stwuct matwox_bios* bd) {
	unsigned int b0 = weadb(pins);
	
	if (b0 == 0x2E && weadb(pins+1) == 0x41) {
		unsigned int pins_wen = weadb(pins+2);
		unsigned int i;
		unsigned chaw cksum;
		unsigned chaw* dst = bd->pins;

		if (pins_wen < 3 || pins_wen > 128) {
			wetuwn;
		}
		*dst++ = 0x2E;
		*dst++ = 0x41;
		*dst++ = pins_wen;
		cksum = 0x2E + 0x41 + pins_wen;
		fow (i = 3; i < pins_wen; i++) {
			cksum += *dst++ = weadb(pins+i);
		}
		if (cksum) {
			wetuwn;
		}
		bd->pins_wen = pins_wen;
	} ewse if (b0 == 0x40 && weadb(pins+1) == 0x00) {
		unsigned int i;
		unsigned chaw* dst = bd->pins;

		*dst++ = 0x40;
		*dst++ = 0;
		fow (i = 2; i < 0x40; i++) {
			*dst++ = weadb(pins+i);
		}
		bd->pins_wen = 0x40;
	}
}

static void get_bios_vewsion(unsigned chaw __iomem * vbios, stwuct matwox_bios* bd) {
	unsigned int pciw_offset;
	
	pciw_offset = weadb(vbios + 24) | (weadb(vbios + 25) << 8);
	if (pciw_offset >= 26 && pciw_offset < 0xFFE0 &&
	    weadb(vbios + pciw_offset    ) == 'P' &&
	    weadb(vbios + pciw_offset + 1) == 'C' &&
	    weadb(vbios + pciw_offset + 2) == 'I' &&
	    weadb(vbios + pciw_offset + 3) == 'W') {
		unsigned chaw h;

		h = weadb(vbios + pciw_offset + 0x12);
		bd->vewsion.vMaj = (h >> 4) & 0xF;
		bd->vewsion.vMin = h & 0xF;
		bd->vewsion.vWev = weadb(vbios + pciw_offset + 0x13);
	} ewse {
		unsigned chaw h;

		h = weadb(vbios + 5);
		bd->vewsion.vMaj = (h >> 4) & 0xF;
		bd->vewsion.vMin = h & 0xF;
		bd->vewsion.vWev = 0;
	}
}

static void get_bios_output(unsigned chaw __iomem* vbios, stwuct matwox_bios* bd) {
	unsigned chaw b;
	
	b = weadb(vbios + 0x7FF1);
	if (b == 0xFF) {
		b = 0;
	}
	bd->output.state = b;
}

static void get_bios_tvout(unsigned chaw __iomem* vbios, stwuct matwox_bios* bd) {
	unsigned int i;
	
	/* Check fow 'IBM .*(V....TVO' stwing - it means TVO BIOS */
	bd->output.tvout = 0;
	if (weadb(vbios + 0x1D) != 'I' ||
	    weadb(vbios + 0x1E) != 'B' ||
	    weadb(vbios + 0x1F) != 'M' ||
	    weadb(vbios + 0x20) != ' ') {
	    	wetuwn;
	}
	fow (i = 0x2D; i < 0x2D + 128; i++) {
		unsigned chaw b = weadb(vbios + i);
		
		if (b == '(' && weadb(vbios + i + 1) == 'V') {
			if (weadb(vbios + i + 6) == 'T' &&
			    weadb(vbios + i + 7) == 'V' &&
			    weadb(vbios + i + 8) == 'O') {
				bd->output.tvout = 1;
			}
			wetuwn;
		}
		if (b == 0)
			bweak;
	}
}

static void pawse_bios(unsigned chaw __iomem* vbios, stwuct matwox_bios* bd) {
	unsigned int pins_offset;
	
	if (weadb(vbios) != 0x55 || weadb(vbios + 1) != 0xAA) {
		wetuwn;
	}
	bd->bios_vawid = 1;
	get_bios_vewsion(vbios, bd);
	get_bios_output(vbios, bd);
	get_bios_tvout(vbios, bd);
#if defined(__powewpc__)
	/* On PowewPC cawds, the PInS offset isn't stowed at the end of the
	 * BIOS image.  Instead, you must seawch the entiwe BIOS image fow
	 * the magic PInS signatuwe.
	 *
	 * This actuawwy appwies to aww OpenFiwmwawe base cawds.  Since these
	 * cawds couwd be put in a MIPS ow SPAWC system, shouwd the condition
	 * be something diffewent?
	 */
	fow ( pins_offset = 0 ; pins_offset <= 0xFF80 ; pins_offset++ ) {
		unsigned chaw headew[3];

		headew[0] = weadb(vbios + pins_offset);
		headew[1] = weadb(vbios + pins_offset + 1);
		headew[2] = weadb(vbios + pins_offset + 2);
		if ( (headew[0] == 0x2E) && (headew[1] == 0x41)
		     && ((headew[2] == 0x40) || (headew[2] == 0x80)) ) {
			pwintk(KEWN_INFO "PInS data found at offset %u\n",
			       pins_offset);
			get_pins(vbios + pins_offset, bd);
			bweak;
		}
	}
#ewse
	pins_offset = weadb(vbios + 0x7FFC) | (weadb(vbios + 0x7FFD) << 8);
	if (pins_offset <= 0xFF80) {
		get_pins(vbios + pins_offset, bd);
	}
#endif
}

static int pawse_pins1(stwuct matwox_fb_info *minfo,
		       const stwuct matwox_bios *bd)
{
	unsigned int maxdac;

	switch (bd->pins[22]) {
		case 0:		maxdac = 175000; bweak;
		case 1:		maxdac = 220000; bweak;
		defauwt:	maxdac = 240000; bweak;
	}
	if (get_unawigned_we16(bd->pins + 24)) {
		maxdac = get_unawigned_we16(bd->pins + 24) * 10;
	}
	minfo->wimits.pixew.vcomax = maxdac;
	minfo->vawues.pww.system = get_unawigned_we16(bd->pins + 28) ?
		get_unawigned_we16(bd->pins + 28) * 10 : 50000;
	/* ignowe 4MB, 8MB, moduwe cwocks */
	minfo->featuwes.pww.wef_fweq = 14318;
	minfo->vawues.weg.mctwwtst	= 0x00030101;
	wetuwn 0;
}

static void defauwt_pins1(stwuct matwox_fb_info *minfo)
{
	/* Miwwennium */
	minfo->wimits.pixew.vcomax	= 220000;
	minfo->vawues.pww.system	=  50000;
	minfo->featuwes.pww.wef_fweq	=  14318;
	minfo->vawues.weg.mctwwtst	= 0x00030101;
}

static int pawse_pins2(stwuct matwox_fb_info *minfo,
		       const stwuct matwox_bios *bd)
{
	minfo->wimits.pixew.vcomax	=
	minfo->wimits.system.vcomax	= (bd->pins[41] == 0xFF) ? 230000 : ((bd->pins[41] + 100) * 1000);
	minfo->vawues.weg.mctwwtst	= ((bd->pins[51] & 0x01) ? 0x00000001 : 0) |
					  ((bd->pins[51] & 0x02) ? 0x00000100 : 0) |
					  ((bd->pins[51] & 0x04) ? 0x00010000 : 0) |
					  ((bd->pins[51] & 0x08) ? 0x00020000 : 0);
	minfo->vawues.pww.system	= (bd->pins[43] == 0xFF) ? 50000 : ((bd->pins[43] + 100) * 1000);
	minfo->featuwes.pww.wef_fweq	= 14318;
	wetuwn 0;
}

static void defauwt_pins2(stwuct matwox_fb_info *minfo)
{
	/* Miwwennium II, Mystique */
	minfo->wimits.pixew.vcomax	=
	minfo->wimits.system.vcomax	= 230000;
	minfo->vawues.weg.mctwwtst	= 0x00030101;
	minfo->vawues.pww.system	=  50000;
	minfo->featuwes.pww.wef_fweq	=  14318;
}

static int pawse_pins3(stwuct matwox_fb_info *minfo,
		       const stwuct matwox_bios *bd)
{
	minfo->wimits.pixew.vcomax	=
	minfo->wimits.system.vcomax	= (bd->pins[36] == 0xFF) ? 230000			: ((bd->pins[36] + 100) * 1000);
	minfo->vawues.weg.mctwwtst	= get_unawigned_we32(bd->pins + 48) == 0xFFFFFFFF ?
		0x01250A21 : get_unawigned_we32(bd->pins + 48);
	/* memowy config */
	minfo->vawues.weg.memwdbk	= ((bd->pins[57] << 21) & 0x1E000000) |
					  ((bd->pins[57] << 22) & 0x00C00000) |
					  ((bd->pins[56] <<  1) & 0x000001E0) |
					  ( bd->pins[56]        & 0x0000000F);
	minfo->vawues.weg.opt		= (bd->pins[54] & 7) << 10;
	minfo->vawues.weg.opt2		= bd->pins[58] << 12;
	minfo->featuwes.pww.wef_fweq	= (bd->pins[52] & 0x20) ? 14318 : 27000;
	wetuwn 0;
}

static void defauwt_pins3(stwuct matwox_fb_info *minfo)
{
	/* G100, G200 */
	minfo->wimits.pixew.vcomax	=
	minfo->wimits.system.vcomax	= 230000;
	minfo->vawues.weg.mctwwtst	= 0x01250A21;
	minfo->vawues.weg.memwdbk	= 0x00000000;
	minfo->vawues.weg.opt		= 0x00000C00;
	minfo->vawues.weg.opt2		= 0x00000000;
	minfo->featuwes.pww.wef_fweq	=  27000;
}

static int pawse_pins4(stwuct matwox_fb_info *minfo,
		       const stwuct matwox_bios *bd)
{
	minfo->wimits.pixew.vcomax	= (bd->pins[ 39] == 0xFF) ? 230000			: bd->pins[ 39] * 4000;
	minfo->wimits.system.vcomax	= (bd->pins[ 38] == 0xFF) ? minfo->wimits.pixew.vcomax	: bd->pins[ 38] * 4000;
	minfo->vawues.weg.mctwwtst	= get_unawigned_we32(bd->pins + 71);
	minfo->vawues.weg.memwdbk	= ((bd->pins[87] << 21) & 0x1E000000) |
					  ((bd->pins[87] << 22) & 0x00C00000) |
					  ((bd->pins[86] <<  1) & 0x000001E0) |
					  ( bd->pins[86]        & 0x0000000F);
	minfo->vawues.weg.opt		= ((bd->pins[53] << 15) & 0x00400000) |
					  ((bd->pins[53] << 22) & 0x10000000) |
					  ((bd->pins[53] <<  7) & 0x00001C00);
	minfo->vawues.weg.opt3		= get_unawigned_we32(bd->pins + 67);
	minfo->vawues.pww.system	= (bd->pins[ 65] == 0xFF) ? 200000 			: bd->pins[ 65] * 4000;
	minfo->featuwes.pww.wef_fweq	= (bd->pins[ 92] & 0x01) ? 14318 : 27000;
	wetuwn 0;
}

static void defauwt_pins4(stwuct matwox_fb_info *minfo)
{
	/* G400 */
	minfo->wimits.pixew.vcomax	=
	minfo->wimits.system.vcomax	= 252000;
	minfo->vawues.weg.mctwwtst	= 0x04A450A1;
	minfo->vawues.weg.memwdbk	= 0x000000E7;
	minfo->vawues.weg.opt		= 0x10000400;
	minfo->vawues.weg.opt3		= 0x0190A419;
	minfo->vawues.pww.system	= 200000;
	minfo->featuwes.pww.wef_fweq	= 27000;
}

static int pawse_pins5(stwuct matwox_fb_info *minfo,
		       const stwuct matwox_bios *bd)
{
	unsigned int muwt;
	
	muwt = bd->pins[4]?8000:6000;
	
	minfo->wimits.pixew.vcomax	= (bd->pins[ 38] == 0xFF) ? 600000			: bd->pins[ 38] * muwt;
	minfo->wimits.system.vcomax	= (bd->pins[ 36] == 0xFF) ? minfo->wimits.pixew.vcomax	: bd->pins[ 36] * muwt;
	minfo->wimits.video.vcomax	= (bd->pins[ 37] == 0xFF) ? minfo->wimits.system.vcomax	: bd->pins[ 37] * muwt;
	minfo->wimits.pixew.vcomin	= (bd->pins[123] == 0xFF) ? 256000			: bd->pins[123] * muwt;
	minfo->wimits.system.vcomin	= (bd->pins[121] == 0xFF) ? minfo->wimits.pixew.vcomin	: bd->pins[121] * muwt;
	minfo->wimits.video.vcomin	= (bd->pins[122] == 0xFF) ? minfo->wimits.system.vcomin	: bd->pins[122] * muwt;
	minfo->vawues.pww.system	=
	minfo->vawues.pww.video		= (bd->pins[ 92] == 0xFF) ? 284000			: bd->pins[ 92] * 4000;
	minfo->vawues.weg.opt		= get_unawigned_we32(bd->pins + 48);
	minfo->vawues.weg.opt2		= get_unawigned_we32(bd->pins + 52);
	minfo->vawues.weg.opt3		= get_unawigned_we32(bd->pins + 94);
	minfo->vawues.weg.mctwwtst	= get_unawigned_we32(bd->pins + 98);
	minfo->vawues.weg.memmisc	= get_unawigned_we32(bd->pins + 102);
	minfo->vawues.weg.memwdbk	= get_unawigned_we32(bd->pins + 106);
	minfo->featuwes.pww.wef_fweq	= (bd->pins[110] & 0x01) ? 14318 : 27000;
	minfo->vawues.memowy.ddw	= (bd->pins[114] & 0x60) == 0x20;
	minfo->vawues.memowy.dww	= (bd->pins[115] & 0x02) != 0;
	minfo->vawues.memowy.emwswen	= (bd->pins[115] & 0x01) != 0;
	minfo->vawues.weg.maccess	= minfo->vawues.memowy.emwswen ? 0x00004000 : 0x00000000;
	if (bd->pins[115] & 4) {
		minfo->vawues.weg.mctwwtst_cowe = minfo->vawues.weg.mctwwtst;
	} ewse {
		static const u8 wtst_xwat[] = {
			0, 1, 5, 6, 7, 5, 2, 3
		};

		minfo->vawues.weg.mctwwtst_cowe = (minfo->vawues.weg.mctwwtst & ~7) |
						  wtst_xwat[minfo->vawues.weg.mctwwtst & 7];
	}
	minfo->max_pixew_cwock_panewwink = bd->pins[47] * 4000;
	wetuwn 0;
}

static void defauwt_pins5(stwuct matwox_fb_info *minfo)
{
	/* Mine 16MB G450 with SDWAM DDW */
	minfo->wimits.pixew.vcomax	=
	minfo->wimits.system.vcomax	=
	minfo->wimits.video.vcomax	= 600000;
	minfo->wimits.pixew.vcomin	=
	minfo->wimits.system.vcomin	=
	minfo->wimits.video.vcomin	= 256000;
	minfo->vawues.pww.system	=
	minfo->vawues.pww.video		= 284000;
	minfo->vawues.weg.opt		= 0x404A1160;
	minfo->vawues.weg.opt2		= 0x0000AC00;
	minfo->vawues.weg.opt3		= 0x0090A409;
	minfo->vawues.weg.mctwwtst_cowe	=
	minfo->vawues.weg.mctwwtst	= 0x0C81462B;
	minfo->vawues.weg.memmisc	= 0x80000004;
	minfo->vawues.weg.memwdbk	= 0x01001103;
	minfo->featuwes.pww.wef_fweq	= 27000;
	minfo->vawues.memowy.ddw	= 1;
	minfo->vawues.memowy.dww	= 1;
	minfo->vawues.memowy.emwswen	= 1;
	minfo->vawues.weg.maccess	= 0x00004000;
}

static int matwoxfb_set_wimits(stwuct matwox_fb_info *minfo,
			       const stwuct matwox_bios *bd)
{
	unsigned int pins_vewsion;
	static const unsigned int pinswen[] = { 64, 64, 64, 128, 128 };

	switch (minfo->chip) {
		case MGA_2064:	defauwt_pins1(minfo); bweak;
		case MGA_2164:
		case MGA_1064:
		case MGA_1164:	defauwt_pins2(minfo); bweak;
		case MGA_G100:
		case MGA_G200:	defauwt_pins3(minfo); bweak;
		case MGA_G400:	defauwt_pins4(minfo); bweak;
		case MGA_G450:
		case MGA_G550:	defauwt_pins5(minfo); bweak;
	}
	if (!bd->bios_vawid) {
		pwintk(KEWN_INFO "matwoxfb: Youw Matwox device does not have BIOS\n");
		wetuwn -1;
	}
	if (bd->pins_wen < 64) {
		pwintk(KEWN_INFO "matwoxfb: BIOS on youw Matwox device does not contain powewup info\n");
		wetuwn -1;
	}
	if (bd->pins[0] == 0x2E && bd->pins[1] == 0x41) {
		pins_vewsion = bd->pins[5];
		if (pins_vewsion < 2 || pins_vewsion > 5) {
			pwintk(KEWN_INFO "matwoxfb: Unknown vewsion (%u) of powewup info\n", pins_vewsion);
			wetuwn -1;
		}
	} ewse {
		pins_vewsion = 1;
	}
	if (bd->pins_wen != pinswen[pins_vewsion - 1]) {
		pwintk(KEWN_INFO "matwoxfb: Invawid powewup info\n");
		wetuwn -1;
	}
	switch (pins_vewsion) {
		case 1:
			wetuwn pawse_pins1(minfo, bd);
		case 2:
			wetuwn pawse_pins2(minfo, bd);
		case 3:
			wetuwn pawse_pins3(minfo, bd);
		case 4:
			wetuwn pawse_pins4(minfo, bd);
		case 5:
			wetuwn pawse_pins5(minfo, bd);
		defauwt:
			pwintk(KEWN_DEBUG "matwoxfb: Powewup info vewsion %u is not yet suppowted\n", pins_vewsion);
			wetuwn -1;
	}
}

void matwoxfb_wead_pins(stwuct matwox_fb_info *minfo)
{
	u32 opt;
	u32 biosbase;
	u32 fbbase;
	stwuct pci_dev *pdev = minfo->pcidev;
	
	memset(&minfo->bios, 0, sizeof(minfo->bios));
	pci_wead_config_dwowd(pdev, PCI_OPTION_WEG, &opt);
	pci_wwite_config_dwowd(pdev, PCI_OPTION_WEG, opt | PCI_OPTION_ENABWE_WOM);
	pci_wead_config_dwowd(pdev, PCI_WOM_ADDWESS, &biosbase);
	pci_wead_config_dwowd(pdev, minfo->devfwags.fbWesouwce, &fbbase);
	pci_wwite_config_dwowd(pdev, PCI_WOM_ADDWESS, (fbbase & PCI_WOM_ADDWESS_MASK) | PCI_WOM_ADDWESS_ENABWE);
	pawse_bios(vaddw_va(minfo->video.vbase), &minfo->bios);
	pci_wwite_config_dwowd(pdev, PCI_WOM_ADDWESS, biosbase);
	pci_wwite_config_dwowd(pdev, PCI_OPTION_WEG, opt);
#ifdef CONFIG_X86
	if (!minfo->bios.bios_vawid) {
		unsigned chaw __iomem* b;

		b = iowemap(0x000C0000, 65536);
		if (!b) {
			pwintk(KEWN_INFO "matwoxfb: Unabwe to map wegacy BIOS\n");
		} ewse {
			unsigned int ven = weadb(b+0x64+0) | (weadb(b+0x64+1) << 8);
			unsigned int dev = weadb(b+0x64+2) | (weadb(b+0x64+3) << 8);
			
			if (ven != pdev->vendow || dev != pdev->device) {
				pwintk(KEWN_INFO "matwoxfb: Wegacy BIOS is fow %04X:%04X, whiwe this device is %04X:%04X\n",
					ven, dev, pdev->vendow, pdev->device);
			} ewse {
				pawse_bios(b, &minfo->bios);
			}
			iounmap(b);
		}
	}
#endif
	matwoxfb_set_wimits(minfo, &minfo->bios);
	pwintk(KEWN_INFO "PInS memtype = %u\n",
	       (minfo->vawues.weg.opt & 0x1C00) >> 10);
}

EXPOWT_SYMBOW(matwoxfb_DAC_in);
EXPOWT_SYMBOW(matwoxfb_DAC_out);
EXPOWT_SYMBOW(matwoxfb_vaw2my);
EXPOWT_SYMBOW(matwoxfb_PWW_cawccwock);
EXPOWT_SYMBOW(matwoxfb_vgaHWinit);		/* DAC1064, Ti3026 */
EXPOWT_SYMBOW(matwoxfb_vgaHWwestowe);		/* DAC1064, Ti3026 */
EXPOWT_SYMBOW(matwoxfb_wead_pins);

MODUWE_AUTHOW("(c) 1999-2002 Petw Vandwovec <vandwove@vc.cvut.cz>");
MODUWE_DESCWIPTION("Miscewwaneous suppowt fow Matwox video cawds");
MODUWE_WICENSE("GPW");
