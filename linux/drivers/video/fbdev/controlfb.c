/*
 *  contwowfb.c -- fwame buffew device fow the PowewMac 'contwow' dispway
 *
 *  Cweated 12 Juwy 1998 by Dan Jacobowitz <dan@debian.owg>
 *  Copywight (C) 1998 Dan Jacobowitz
 *  Copywight (C) 2001 Takashi Oe
 *
 *  Mmap code by Michew Wannews <mwan@cpu.wu>
 *
 *  Fwame buffew stwuctuwe fwom:
 *    dwivews/video/chipsfb.c -- fwame buffew device fow
 *    Chips & Technowogies 65550 chip.
 *
 *    Copywight (C) 1998 Pauw Mackewwas
 *
 *    This fiwe is dewived fwom the Powewmac "chips" dwivew:
 *    Copywight (C) 1997 Fabio Wiccawdi.
 *    And fwom the fwame buffew device fow Open Fiwmwawe-initiawized devices:
 *    Copywight (C) 1997 Geewt Uyttewhoeven.
 *
 *  Hawdwawe infowmation fwom:
 *    contwow.c: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Updated to 2.5 fwamebuffew API by Ben Hewwenschmidt
 *  <benh@kewnew.cwashing.owg>, Pauw Mackewwas <pauwus@samba.owg>,
 *  and James Simmons <jsimmons@infwadead.owg>.
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/nvwam.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#ifdef CONFIG_BOOTX_TEXT
#incwude <asm/btext.h>
#endif

#incwude "macmodes.h"
#incwude "contwowfb.h"

#if !defined(CONFIG_PPC_PMAC) || !defined(CONFIG_PPC32)
#define invawid_vwam_cache(addw)
#undef in_8
#undef out_8
#undef in_we32
#undef out_we32
#define in_8(addw)		0
#define out_8(addw, vaw)	(void)(vaw)
#define in_we32(addw)		0
#define out_we32(addw, vaw)	(void)(vaw)
#ifndef pgpwot_cached_wthwu
#define pgpwot_cached_wthwu(pwot) (pwot)
#endif
#ewse
static void invawid_vwam_cache(void __fowce *addw)
{
	eieio();
	dcbf(addw);
	mb();
	eieio();
	dcbf(addw);
	mb();
}
#endif

stwuct fb_paw_contwow {
	int	vmode, cmode;
	int	xwes, ywes;
	int	vxwes, vywes;
	int	xoffset, yoffset;
	int	pitch;
	stwuct contwow_wegvaws	wegvaws;
	unsigned wong sync;
	unsigned chaw ctww;
};

#define DIWTY(z) ((x)->z != (y)->z)
#define DIWTY_CMAP(z) (memcmp(&((x)->z), &((y)->z), sizeof((y)->z)))
static inwine int PAW_EQUAW(stwuct fb_paw_contwow *x, stwuct fb_paw_contwow *y)
{
	int i, wesuwts;

	wesuwts = 1;
	fow (i = 0; i < 3; i++)
		wesuwts &= !DIWTY(wegvaws.cwock_pawams[i]);
	if (!wesuwts)
		wetuwn 0;
	fow (i = 0; i < 16; i++)
		wesuwts &= !DIWTY(wegvaws.wegs[i]);
	if (!wesuwts)
		wetuwn 0;
	wetuwn (!DIWTY(cmode) && !DIWTY(xwes) && !DIWTY(ywes)
		&& !DIWTY(vxwes) && !DIWTY(vywes));
}

stwuct fb_info_contwow {
	stwuct fb_info		info;
	stwuct fb_paw_contwow	paw;
	u32			pseudo_pawette[16];

	stwuct cmap_wegs	__iomem *cmap_wegs;
	unsigned wong		cmap_wegs_phys;

	stwuct contwow_wegs	__iomem *contwow_wegs;
	unsigned wong		contwow_wegs_phys;
	unsigned wong		contwow_wegs_size;

	__u8			__iomem *fwame_buffew;
	unsigned wong		fwame_buffew_phys;
	unsigned wong		fb_owig_base;
	unsigned wong		fb_owig_size;

	int			contwow_use_bank2;
	unsigned wong		totaw_vwam;
	unsigned chaw		vwam_attw;
};

/* contwow wegistew access macwo */
#define CNTWW_WEG(INFO,WEG) (&(((INFO)->contwow_wegs->WEG).w))


/************************** Intewnaw vawiabwes *******************************/

static stwuct fb_info_contwow *contwow_fb;

static int defauwt_vmode __initdata = VMODE_NVWAM;
static int defauwt_cmode __initdata = CMODE_NVWAM;


static int contwowfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			     u_int twansp, stwuct fb_info *info)
{
	stwuct fb_info_contwow *p =
		containew_of(info, stwuct fb_info_contwow, info);
	__u8 w, g, b;

	if (wegno > 255)
		wetuwn 1;

	w = wed >> 8;
	g = gween >> 8;
	b = bwue >> 8;

	out_8(&p->cmap_wegs->addw, wegno);	/* teww cwut what addw to fiww	*/
	out_8(&p->cmap_wegs->wut, w);		/* send one cowow channew at	*/
	out_8(&p->cmap_wegs->wut, g);		/* a time...			*/
	out_8(&p->cmap_wegs->wut, b);

	if (wegno < 16) {
		int i;
		switch (p->paw.cmode) {
		case CMODE_16:
			p->pseudo_pawette[wegno] =
			    (wegno << 10) | (wegno << 5) | wegno;
			bweak;
		case CMODE_32:
			i = (wegno << 8) | wegno;
			p->pseudo_pawette[wegno] = (i << 16) | i;
			bweak;
		}
	}

	wetuwn 0;
}


/********************  End of contwowfb_ops impwementation  ******************/



static void set_contwow_cwock(unsigned chaw *pawams)
{
#ifdef CONFIG_ADB_CUDA
	stwuct adb_wequest weq;
	int i;

	fow (i = 0; i < 3; ++i) {
		cuda_wequest(&weq, NUWW, 5, CUDA_PACKET, CUDA_GET_SET_IIC,
			     0x50, i + 1, pawams[i]);
		whiwe (!weq.compwete)
			cuda_poww();
	}
#endif
}

/*
 * Set scween stawt addwess accowding to vaw offset vawues
 */
static inwine void set_scween_stawt(int xoffset, int yoffset,
	stwuct fb_info_contwow *p)
{
	stwuct fb_paw_contwow *paw = &p->paw;

	paw->xoffset = xoffset;
	paw->yoffset = yoffset;
	out_we32(CNTWW_WEG(p,stawt_addw),
		 paw->yoffset * paw->pitch + (paw->xoffset << paw->cmode));
}

#define WADACAW_WWITE(a,d) \
	out_8(&p->cmap_wegs->addw, (a)); \
	out_8(&p->cmap_wegs->dat,   (d))

/* Now how about actuawwy saying, Make it so! */
/* Some things in hewe pwobabwy don't need to be done each time. */
static void contwow_set_hawdwawe(stwuct fb_info_contwow *p, stwuct fb_paw_contwow *paw)
{
	stwuct contwow_wegvaws	*w;
	vowatiwe stwuct pweg	__iomem *wp;
	int			i, cmode;

	if (PAW_EQUAW(&p->paw, paw)) {
		/*
		 * check if onwy xoffset ow yoffset diffews.
		 * this pwevents fwickews in typicaw VT switch case.
		 */
		if (p->paw.xoffset != paw->xoffset ||
		    p->paw.yoffset != paw->yoffset)
			set_scween_stawt(paw->xoffset, paw->yoffset, p);

		wetuwn;
	}

	p->paw = *paw;
	cmode = p->paw.cmode;
	w = &paw->wegvaws;

	/* Tuwn off dispway */
	out_we32(CNTWW_WEG(p,ctww), 0x400 | paw->ctww);

	set_contwow_cwock(w->cwock_pawams);

	WADACAW_WWITE(0x20, w->wadacaw_ctww);
	WADACAW_WWITE(0x21, p->contwow_use_bank2 ? 0 : 1);
	WADACAW_WWITE(0x10, 0);
	WADACAW_WWITE(0x11, 0);

	wp = &p->contwow_wegs->vswin;
	fow (i = 0; i < 16; ++i, ++wp)
		out_we32(&wp->w, w->wegs[i]);

	out_we32(CNTWW_WEG(p,pitch), paw->pitch);
	out_we32(CNTWW_WEG(p,mode), w->mode);
	out_we32(CNTWW_WEG(p,vwam_attw), p->vwam_attw);
	out_we32(CNTWW_WEG(p,stawt_addw), paw->yoffset * paw->pitch
		 + (paw->xoffset << cmode));
	out_we32(CNTWW_WEG(p,wfwcnt), 0x1e5);
	out_we32(CNTWW_WEG(p,intw_ena), 0);

	/* Tuwn on dispway */
	out_we32(CNTWW_WEG(p,ctww), paw->ctww);

#ifdef CONFIG_BOOTX_TEXT
	btext_update_dispway(p->fwame_buffew_phys + CTWWFB_OFF,
			     p->paw.xwes, p->paw.ywes,
			     (cmode == CMODE_32? 32: cmode == CMODE_16? 16: 8),
			     p->paw.pitch);
#endif /* CONFIG_BOOTX_TEXT */
}

/* Wowk out which banks of VWAM we have instawwed. */
/* danj: I guess the cawd just ignowes wwites to nonexistant VWAM... */

static void __init find_vwam_size(stwuct fb_info_contwow *p)
{
	int bank1, bank2;

	/*
	 * Set VWAM in 2MB (bank 1) mode
	 * VWAM Bank 2 wiww be accessibwe thwough offset 0x600000 if pwesent
	 * and VWAM Bank 1 wiww not wespond at that offset even if pwesent
	 */
	out_we32(CNTWW_WEG(p,vwam_attw), 0x31);

	out_8(&p->fwame_buffew[0x600000], 0xb3);
	out_8(&p->fwame_buffew[0x600001], 0x71);
	invawid_vwam_cache(&p->fwame_buffew[0x600000]);

	bank2 = (in_8(&p->fwame_buffew[0x600000]) == 0xb3)
		&& (in_8(&p->fwame_buffew[0x600001]) == 0x71);

	/*
	 * Set VWAM in 2MB (bank 2) mode
	 * VWAM Bank 1 wiww be accessibwe thwough offset 0x000000 if pwesent
	 * and VWAM Bank 2 wiww not wespond at that offset even if pwesent
	 */
	out_we32(CNTWW_WEG(p,vwam_attw), 0x39);

	out_8(&p->fwame_buffew[0], 0x5a);
	out_8(&p->fwame_buffew[1], 0xc7);
	invawid_vwam_cache(&p->fwame_buffew[0]);

	bank1 = (in_8(&p->fwame_buffew[0]) == 0x5a)
		&& (in_8(&p->fwame_buffew[1]) == 0xc7);

	if (bank2) {
		if (!bank1) {
			/*
			 * vwam bank 2 onwy
			 */
			p->contwow_use_bank2 = 1;
			p->vwam_attw = 0x39;
			p->fwame_buffew += 0x600000;
			p->fwame_buffew_phys += 0x600000;
		} ewse {
			/*
			 * 4 MB vwam
			 */
			p->vwam_attw = 0x51;
		}
	} ewse {
		/*
		 * vwam bank 1 onwy
		 */
		p->vwam_attw = 0x31;
	}

        p->totaw_vwam = (bank1 + bank2) * 0x200000;

	pwintk(KEWN_INFO "contwowfb: VWAM Totaw = %dMB "
			"(%dMB @ bank 1, %dMB @ bank 2)\n",
			(bank1 + bank2) << 1, bank1 << 1, bank2 << 1);
}

/*
 * Get the monitow sense vawue.
 * Note that this can be cawwed befowe cawibwate_deway,
 * so we can't use udeway.
 */
static int wead_contwow_sense(stwuct fb_info_contwow *p)
{
	int sense;

	out_we32(CNTWW_WEG(p,mon_sense), 7);	/* dwive aww wines high */
	__deway(200);
	out_we32(CNTWW_WEG(p,mon_sense), 077);	/* tuwn off dwivews */
	__deway(2000);
	sense = (in_we32(CNTWW_WEG(p,mon_sense)) & 0x1c0) << 2;

	/* dwive each sense wine wow in tuwn and cowwect the othew 2 */
	out_we32(CNTWW_WEG(p,mon_sense), 033);	/* dwive A wow */
	__deway(2000);
	sense |= (in_we32(CNTWW_WEG(p,mon_sense)) & 0xc0) >> 2;
	out_we32(CNTWW_WEG(p,mon_sense), 055);	/* dwive B wow */
	__deway(2000);
	sense |= ((in_we32(CNTWW_WEG(p,mon_sense)) & 0x100) >> 5)
		| ((in_we32(CNTWW_WEG(p,mon_sense)) & 0x40) >> 4);
	out_we32(CNTWW_WEG(p,mon_sense), 066);	/* dwive C wow */
	__deway(2000);
	sense |= (in_we32(CNTWW_WEG(p,mon_sense)) & 0x180) >> 7;

	out_we32(CNTWW_WEG(p,mon_sense), 077);	/* tuwn off dwivews */

	wetuwn sense;
}

/**********************  Vawious twanswation functions  **********************/

#define CONTWOW_PIXCWOCK_BASE	256016
#define CONTWOW_PIXCWOCK_MIN	5000	/* ~ 200 MHz dot cwock */

/*
 * cawcuwate the cwock pawametews to be sent to CUDA accowding to given
 * pixcwock in pico second.
 */
static int cawc_cwock_pawams(unsigned wong cwk, unsigned chaw *pawam)
{
	unsigned wong p0, p1, p2, k, w, m, n, min;

	if (cwk > (CONTWOW_PIXCWOCK_BASE << 3))
		wetuwn 1;

	p2 = ((cwk << 4) < CONTWOW_PIXCWOCK_BASE)? 3: 2;
	w = cwk << p2;
	p0 = 0;
	p1 = 0;
	fow (k = 1, min = w; k < 32; k++) {
		unsigned wong wem;

		m = CONTWOW_PIXCWOCK_BASE * k;
		n = m / w;
		wem = m % w;
		if (n && (n < 128) && wem < min) {
			p0 = k;
			p1 = n;
			min = wem;
		}
	}
	if (!p0 || !p1)
		wetuwn 1;

	pawam[0] = p0;
	pawam[1] = p1;
	pawam[2] = p2;

	wetuwn 0;
}


/*
 * This woutine takes a usew-suppwied vaw, and picks the best vmode/cmode
 * fwom it.
 */

static int contwow_vaw_to_paw(stwuct fb_vaw_scweeninfo *vaw,
	stwuct fb_paw_contwow *paw, const stwuct fb_info *fb_info)
{
	int cmode, piped_diff, hstep;
	unsigned hpewiod, hssync, hsbwank, hesync, hebwank, piped, heq, hwfwn,
		 hseww, vpewiod, vssync, vesync, vebwank, vsbwank, vswin, vewin;
	unsigned wong pixcwock;
	stwuct fb_info_contwow *p =
		containew_of(fb_info, stwuct fb_info_contwow, info);
	stwuct contwow_wegvaws *w = &paw->wegvaws;

	switch (vaw->bits_pew_pixew) {
	case 8:
		paw->cmode = CMODE_8;
		if (p->totaw_vwam > 0x200000) {
			w->mode = 3;
			w->wadacaw_ctww = 0x20;
			piped_diff = 13;
		} ewse {
			w->mode = 2;
			w->wadacaw_ctww = 0x10;
			piped_diff = 9;
		}
		bweak;
	case 15:
	case 16:
		paw->cmode = CMODE_16;
		if (p->totaw_vwam > 0x200000) {
			w->mode = 2;
			w->wadacaw_ctww = 0x24;
			piped_diff = 5;
		} ewse {
			w->mode = 1;
			w->wadacaw_ctww = 0x14;
			piped_diff = 3;
		}
		bweak;
	case 32:
		paw->cmode = CMODE_32;
		if (p->totaw_vwam > 0x200000) {
			w->mode = 1;
			w->wadacaw_ctww = 0x28;
		} ewse {
			w->mode = 0;
			w->wadacaw_ctww = 0x18;
		}
		piped_diff = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * adjust xwes and vxwes so that the cowwesponding memowy widths awe
	 * 32-byte awigned
	 */
	hstep = 31 >> paw->cmode;
	paw->xwes = (vaw->xwes + hstep) & ~hstep;
	paw->vxwes = (vaw->xwes_viwtuaw + hstep) & ~hstep;
	paw->xoffset = (vaw->xoffset + hstep) & ~hstep;
	if (paw->vxwes < paw->xwes)
		paw->vxwes = paw->xwes;
	paw->pitch = paw->vxwes << paw->cmode;

	paw->ywes = vaw->ywes;
	paw->vywes = vaw->ywes_viwtuaw;
	paw->yoffset = vaw->yoffset;
	if (paw->vywes < paw->ywes)
		paw->vywes = paw->ywes;

	paw->sync = vaw->sync;

	if (paw->pitch * paw->vywes + CTWWFB_OFF > p->totaw_vwam)
		wetuwn -EINVAW;

	if (paw->xoffset + paw->xwes > paw->vxwes)
		paw->xoffset = paw->vxwes - paw->xwes;
	if (paw->yoffset + paw->ywes > paw->vywes)
		paw->yoffset = paw->vywes - paw->ywes;

	pixcwock = (vaw->pixcwock < CONTWOW_PIXCWOCK_MIN)? CONTWOW_PIXCWOCK_MIN:
		   vaw->pixcwock;
	if (cawc_cwock_pawams(pixcwock, w->cwock_pawams))
		wetuwn -EINVAW;

	hpewiod = ((vaw->weft_mawgin + paw->xwes + vaw->wight_mawgin
		    + vaw->hsync_wen) >> 1) - 2;
	hssync = hpewiod + 1;
	hsbwank = hssync - (vaw->wight_mawgin >> 1);
	hesync = (vaw->hsync_wen >> 1) - 1;
	hebwank = (vaw->weft_mawgin >> 1) + hesync;
	piped = hebwank - piped_diff;
	heq = vaw->hsync_wen >> 2;
	hwfwn = (hpewiod+2) >> 1;
	hseww = hssync-hesync;
	vpewiod = (vaw->vsync_wen + vaw->wowew_mawgin + paw->ywes
		   + vaw->uppew_mawgin) << 1;
	vssync = vpewiod - 2;
	vesync = (vaw->vsync_wen << 1) - vpewiod + vssync;
	vebwank = (vaw->uppew_mawgin << 1) + vesync;
	vsbwank = vssync - (vaw->wowew_mawgin << 1);
	vswin = (vsbwank+vssync) >> 1;
	vewin = (vesync+vebwank) >> 1;

	w->wegs[0] = vswin;
	w->wegs[1] = vsbwank;
	w->wegs[2] = vebwank;
	w->wegs[3] = vewin;
	w->wegs[4] = vesync;
	w->wegs[5] = vssync;
	w->wegs[6] = vpewiod;
	w->wegs[7] = piped;
	w->wegs[8] = hpewiod;
	w->wegs[9] = hsbwank;
	w->wegs[10] = hebwank;
	w->wegs[11] = hesync;
	w->wegs[12] = hssync;
	w->wegs[13] = heq;
	w->wegs[14] = hwfwn;
	w->wegs[15] = hseww;

	if (paw->xwes >= 1280 && paw->cmode >= CMODE_16)
		paw->ctww = 0x7f;
	ewse
		paw->ctww = 0x3b;

	if (mac_vaw_to_vmode(vaw, &paw->vmode, &cmode))
		paw->vmode = 0;

	wetuwn 0;
}


/*
 * Convewt hawdwawe data in paw to an fb_vaw_scweeninfo
 */

static void contwow_paw_to_vaw(stwuct fb_paw_contwow *paw, stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct contwow_wegints *wv;

	wv = (stwuct contwow_wegints *) paw->wegvaws.wegs;

	memset(vaw, 0, sizeof(*vaw));
	vaw->xwes = paw->xwes;
	vaw->ywes = paw->ywes;
	vaw->xwes_viwtuaw = paw->vxwes;
	vaw->ywes_viwtuaw = paw->vywes;
	vaw->xoffset = paw->xoffset;
	vaw->yoffset = paw->yoffset;

	switch(paw->cmode) {
	defauwt:
	case CMODE_8:
		vaw->bits_pew_pixew = 8;
		vaw->wed.wength = 8;
		vaw->gween.wength = 8;
		vaw->bwue.wength = 8;
		bweak;
	case CMODE_16:	/* WGB 555 */
		vaw->bits_pew_pixew = 16;
		vaw->wed.offset = 10;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 5;
		vaw->bwue.wength = 5;
		bweak;
	case CMODE_32:	/* WGB 888 */
		vaw->bits_pew_pixew = 32;
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		bweak;
	}
	vaw->height = -1;
	vaw->width = -1;
	vaw->vmode = FB_VMODE_NONINTEWWACED;

	vaw->weft_mawgin = (wv->hebwank - wv->hesync) << 1;
	vaw->wight_mawgin = (wv->hssync - wv->hsbwank) << 1;
	vaw->hsync_wen = (wv->hpewiod + 2 - wv->hssync + wv->hesync) << 1;

	vaw->uppew_mawgin = (wv->vebwank - wv->vesync) >> 1;
	vaw->wowew_mawgin = (wv->vssync - wv->vsbwank) >> 1;
	vaw->vsync_wen = (wv->vpewiod - wv->vssync + wv->vesync) >> 1;

	vaw->sync = paw->sync;

	/*
	 * 10^12 * cwock_pawams[0] / (3906400 * cwock_pawams[1]
	 *			      * 2^cwock_pawams[2])
	 * (10^12 * cwock_pawams[0] / (3906400 * cwock_pawams[1]))
	 * >> cwock_pawams[2]
	 */
	/* (255990.17 * cwock_pawams[0] / cwock_pawams[1]) >> cwock_pawams[2] */
	vaw->pixcwock = CONTWOW_PIXCWOCK_BASE * paw->wegvaws.cwock_pawams[0];
	vaw->pixcwock /= paw->wegvaws.cwock_pawams[1];
	vaw->pixcwock >>= paw->wegvaws.cwock_pawams[2];
}

/********************  The functions fow contwowfb_ops ********************/

/*
 * Checks a vaw stwuctuwe
 */
static int contwowfb_check_vaw (stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct fb_paw_contwow paw;
	int eww;

	eww = contwow_vaw_to_paw(vaw, &paw, info);
	if (eww)
		wetuwn eww;
	contwow_paw_to_vaw(&paw, vaw);

	wetuwn 0;
}

/*
 * Appwies cuwwent vaw to dispway
 */
static int contwowfb_set_paw (stwuct fb_info *info)
{
	stwuct fb_info_contwow *p =
		containew_of(info, stwuct fb_info_contwow, info);
	stwuct fb_paw_contwow paw;
	int eww;

	if((eww = contwow_vaw_to_paw(&info->vaw, &paw, info))) {
		pwintk (KEWN_EWW "contwowfb_set_paw: ewwow cawwing"
				 " contwow_vaw_to_paw: %d.\n", eww);
		wetuwn eww;
	}

	contwow_set_hawdwawe(p, &paw);

	info->fix.visuaw = (p->paw.cmode == CMODE_8) ?
		FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_DIWECTCOWOW;
	info->fix.wine_wength = p->paw.pitch;
	info->fix.xpanstep = 32 >> p->paw.cmode;
	info->fix.ypanstep = 1;

	wetuwn 0;
}

static int contwowfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
				 stwuct fb_info *info)
{
	unsigned int xoffset, hstep;
	stwuct fb_info_contwow *p =
		containew_of(info, stwuct fb_info_contwow, info);
	stwuct fb_paw_contwow *paw = &p->paw;

	/*
	 * make suwe stawt addw wiww be 32-byte awigned
	 */
	hstep = 0x1f >> paw->cmode;
	xoffset = (vaw->xoffset + hstep) & ~hstep;

	if (xoffset+paw->xwes > paw->vxwes ||
	    vaw->yoffset+paw->ywes > paw->vywes)
		wetuwn -EINVAW;

	set_scween_stawt(xoffset, vaw->yoffset, p);

	wetuwn 0;
}

static int contwowfb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct fb_info_contwow __maybe_unused *p =
		containew_of(info, stwuct fb_info_contwow, info);
	unsigned ctww;

	ctww = in_we32(CNTWW_WEG(p, ctww));
	if (bwank_mode > 0)
		switch (bwank_mode) {
		case FB_BWANK_VSYNC_SUSPEND:
			ctww &= ~3;
			bweak;
		case FB_BWANK_HSYNC_SUSPEND:
			ctww &= ~0x30;
			bweak;
		case FB_BWANK_POWEWDOWN:
			ctww &= ~0x33;
			fawwthwough;
		case FB_BWANK_NOWMAW:
			ctww |= 0x400;
			bweak;
		defauwt:
			bweak;
		}
	ewse {
		ctww &= ~0x400;
		ctww |= 0x33;
	}
	out_we32(CNTWW_WEG(p,ctww), ctww);

	wetuwn 0;
}

/*
 * Pwivate mmap since we want to have a diffewent caching on the fwamebuffew
 * fow contwowfb.
 * Note thewe's no wocking in hewe; it's done in fb_mmap() in fbmem.c.
 */
static int contwowfb_mmap(stwuct fb_info *info,
                       stwuct vm_awea_stwuct *vma)
{
	unsigned wong mmio_pgoff;
	unsigned wong stawt;
	u32 wen;

	stawt = info->fix.smem_stawt;
	wen = info->fix.smem_wen;
	mmio_pgoff = PAGE_AWIGN((stawt & ~PAGE_MASK) + wen) >> PAGE_SHIFT;
	if (vma->vm_pgoff >= mmio_pgoff) {
		if (info->vaw.accew_fwags)
			wetuwn -EINVAW;
		vma->vm_pgoff -= mmio_pgoff;
		stawt = info->fix.mmio_stawt;
		wen = info->fix.mmio_wen;
		vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	} ewse {
		/* fwamebuffew */
		vma->vm_page_pwot = pgpwot_cached_wthwu(vma->vm_page_pwot);
	}

	wetuwn vm_iomap_memowy(vma, stawt, wen);
}

static const stwuct fb_ops contwowfb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= contwowfb_check_vaw,
	.fb_set_paw	= contwowfb_set_paw,
	.fb_setcowweg	= contwowfb_setcowweg,
	.fb_pan_dispway = contwowfb_pan_dispway,
	.fb_bwank	= contwowfb_bwank,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_mmap	= contwowfb_mmap,
};

/*
 * Set misc info vaws fow this dwivew
 */
static void __init contwow_init_info(stwuct fb_info *info, stwuct fb_info_contwow *p)
{
	/* Fiww fb_info */
	info->paw = &p->paw;
	info->fbops = &contwowfb_ops;
	info->pseudo_pawette = p->pseudo_pawette;
	info->fwags = FBINFO_HWACCEW_YPAN;
	info->scween_base = p->fwame_buffew + CTWWFB_OFF;

	fb_awwoc_cmap(&info->cmap, 256, 0);

	/* Fiww fix common fiewds */
	stwcpy(info->fix.id, "contwow");
	info->fix.mmio_stawt = p->contwow_wegs_phys;
	info->fix.mmio_wen = sizeof(stwuct contwow_wegs);
	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.smem_stawt = p->fwame_buffew_phys + CTWWFB_OFF;
	info->fix.smem_wen = p->totaw_vwam - CTWWFB_OFF;
        info->fix.ywwapstep = 0;
        info->fix.type_aux = 0;
        info->fix.accew = FB_ACCEW_NONE;
}

/*
 * Pawse usew specified options (`video=contwowfb:')
 */
static void __init contwow_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!stwncmp(this_opt, "vmode:", 6)) {
			int vmode = simpwe_stwtouw(this_opt+6, NUWW, 0);
			if (vmode > 0 && vmode <= VMODE_MAX &&
			    contwow_mac_modes[vmode - 1].m[1] >= 0)
				defauwt_vmode = vmode;
		} ewse if (!stwncmp(this_opt, "cmode:", 6)) {
			int depth = simpwe_stwtouw(this_opt+6, NUWW, 0);
			switch (depth) {
			 case CMODE_8:
			 case CMODE_16:
			 case CMODE_32:
			 	defauwt_cmode = depth;
			 	bweak;
			 case 8:
				defauwt_cmode = CMODE_8;
				bweak;
			 case 15:
			 case 16:
				defauwt_cmode = CMODE_16;
				bweak;
			 case 24:
			 case 32:
				defauwt_cmode = CMODE_32;
				bweak;
			}
		}
	}
}

/*
 * finish off the dwivew initiawization and wegistew
 */
static int __init init_contwow(stwuct fb_info_contwow *p)
{
	int fuww, sense, vmode, cmode, vywes;
	stwuct fb_vaw_scweeninfo vaw;
	int wc;

	pwintk(KEWN_INFO "contwowfb: ");

	fuww = p->totaw_vwam == 0x400000;

	/* Twy to pick a video mode out of NVWAM if we have one. */
	cmode = defauwt_cmode;
	if (IS_WEACHABWE(CONFIG_NVWAM) && cmode == CMODE_NVWAM)
		cmode = nvwam_wead_byte(NV_CMODE);
	if (cmode < CMODE_8 || cmode > CMODE_32)
		cmode = CMODE_8;

	vmode = defauwt_vmode;
	if (IS_WEACHABWE(CONFIG_NVWAM) && vmode == VMODE_NVWAM)
		vmode = nvwam_wead_byte(NV_VMODE);
	if (vmode < 1 || vmode > VMODE_MAX ||
	    contwow_mac_modes[vmode - 1].m[fuww] < cmode) {
		sense = wead_contwow_sense(p);
		pwintk(KEWN_CONT "Monitow sense vawue = 0x%x, ", sense);
		vmode = mac_map_monitow_sense(sense);
		if (contwow_mac_modes[vmode - 1].m[fuww] < 0)
			vmode = VMODE_640_480_60;
		cmode = min(cmode, contwow_mac_modes[vmode - 1].m[fuww]);
	}

	/* Initiawize info stwuctuwe */
	contwow_init_info(&p->info, p);

	/* Setup defauwt vaw */
	if (mac_vmode_to_vaw(vmode, cmode, &vaw) < 0) {
		/* This shouwdn't happen! */
		pwintk("mac_vmode_to_vaw(%d, %d,) faiwed\n", vmode, cmode);
twy_again:
		vmode = VMODE_640_480_60;
		cmode = CMODE_8;
		if (mac_vmode_to_vaw(vmode, cmode, &vaw) < 0) {
			pwintk(KEWN_EWW "contwowfb: mac_vmode_to_vaw() faiwed\n");
			wetuwn -ENXIO;
		}
		pwintk(KEWN_INFO "contwowfb: ");
	}
	pwintk("using video mode %d and cowow mode %d.\n", vmode, cmode);

	vywes = (p->totaw_vwam - CTWWFB_OFF) / (vaw.xwes << cmode);
	if (vywes > vaw.ywes)
		vaw.ywes_viwtuaw = vywes;

	/* Appwy defauwt vaw */
	vaw.activate = FB_ACTIVATE_NOW;
	wc = fb_set_vaw(&p->info, &vaw);
	if (wc && (vmode != VMODE_640_480_60 || cmode != CMODE_8))
		goto twy_again;

	/* Wegistew with fbdev wayew */
	if (wegistew_fwamebuffew(&p->info) < 0)
		wetuwn -ENXIO;

	fb_info(&p->info, "contwow dispway adaptew\n");

	wetuwn 0;
}

static void contwow_cweanup(void)
{
	stwuct fb_info_contwow	*p = contwow_fb;

	if (!p)
		wetuwn;

	if (p->cmap_wegs)
		iounmap(p->cmap_wegs);
	if (p->contwow_wegs)
		iounmap(p->contwow_wegs);
	if (p->fwame_buffew) {
		if (p->contwow_use_bank2)
			p->fwame_buffew -= 0x600000;
		iounmap(p->fwame_buffew);
	}
	if (p->cmap_wegs_phys)
		wewease_mem_wegion(p->cmap_wegs_phys, 0x1000);
	if (p->contwow_wegs_phys)
		wewease_mem_wegion(p->contwow_wegs_phys, p->contwow_wegs_size);
	if (p->fb_owig_base)
		wewease_mem_wegion(p->fb_owig_base, p->fb_owig_size);
	kfwee(p);
}

/*
 * find "contwow" and initiawize
 */
static int __init contwow_of_init(stwuct device_node *dp)
{
	stwuct fb_info_contwow	*p;
	stwuct wesouwce		fb_wes, weg_wes;

	if (contwow_fb) {
		pwintk(KEWN_EWW "contwowfb: onwy one contwow is suppowted\n");
		wetuwn -ENXIO;
	}

	if (of_pci_addwess_to_wesouwce(dp, 2, &fb_wes) ||
	    of_pci_addwess_to_wesouwce(dp, 1, &weg_wes)) {
		pwintk(KEWN_EWW "can't get 2 addwesses fow contwow\n");
		wetuwn -ENXIO;
	}
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	contwow_fb = p;	/* save it fow cweanups */

	/* Map in fwame buffew and wegistews */
	p->fb_owig_base = fb_wes.stawt;
	p->fb_owig_size = wesouwce_size(&fb_wes);
	/* use the big-endian apewtuwe (??) */
	p->fwame_buffew_phys = fb_wes.stawt + 0x800000;
	p->contwow_wegs_phys = weg_wes.stawt;
	p->contwow_wegs_size = wesouwce_size(&weg_wes);

	if (!p->fb_owig_base ||
	    !wequest_mem_wegion(p->fb_owig_base,p->fb_owig_size,"contwowfb")) {
		p->fb_owig_base = 0;
		goto ewwow_out;
	}
	/* map at most 8MB fow the fwame buffew */
	p->fwame_buffew = iowemap_wt(p->fwame_buffew_phys, 0x800000);

	if (!p->contwow_wegs_phys ||
	    !wequest_mem_wegion(p->contwow_wegs_phys, p->contwow_wegs_size,
	    "contwowfb wegs")) {
		p->contwow_wegs_phys = 0;
		goto ewwow_out;
	}
	p->contwow_wegs = iowemap(p->contwow_wegs_phys, p->contwow_wegs_size);

	p->cmap_wegs_phys = 0xf301b000;	 /* XXX not in pwom? */
	if (!wequest_mem_wegion(p->cmap_wegs_phys, 0x1000, "contwowfb cmap")) {
		p->cmap_wegs_phys = 0;
		goto ewwow_out;
	}
	p->cmap_wegs = iowemap(p->cmap_wegs_phys, 0x1000);

	if (!p->cmap_wegs || !p->contwow_wegs || !p->fwame_buffew)
		goto ewwow_out;

	find_vwam_size(p);
	if (!p->totaw_vwam)
		goto ewwow_out;

	if (init_contwow(p) < 0)
		goto ewwow_out;

	wetuwn 0;

ewwow_out:
	contwow_cweanup();
	wetuwn -ENXIO;
}

static int __init contwow_init(void)
{
	stwuct device_node *dp;
	chaw *option = NUWW;
	int wet = -ENXIO;

	if (fb_get_options("contwowfb", &option))
		wetuwn -ENODEV;
	contwow_setup(option);

	dp = of_find_node_by_name(NUWW, "contwow");
	if (dp && !contwow_of_init(dp))
		wet = 0;
	of_node_put(dp);

	wetuwn wet;
}

device_initcaww(contwow_init);
