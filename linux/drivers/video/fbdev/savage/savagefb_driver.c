/*
 * winux/dwivews/video/savagefb.c -- S3 Savage Fwamebuffew Dwivew
 *
 * Copywight (c) 2001-2002  Denis Owivew Kwopp <dok@diwectfb.owg>
 *                          Sven Neumann <neo@diwectfb.owg>
 *
 *
 * Cawd specific code is based on XFwee86's savage dwivew.
 * Fwamebuffew fwamewowk code is based on code of cybew2000fb and tdfxfb.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * 0.4.0 (neo)
 *  - hawdwawe accewewated cweaw and move
 *
 * 0.3.2 (dok)
 *  - wait fow vewticaw wetwace befowe wwiting to cw67
 *    at the beginning of savagefb_set_paw
 *  - use synchwonization wegistews cw23 and cw26
 *
 * 0.3.1 (dok)
 *  - weset 3D engine
 *  - don't wetuwn awpha bits fow 32bit fowmat
 *
 * 0.3.0 (dok)
 *  - added WaitIdwe functions fow aww Savage types
 *  - do WaitIdwe befowe mode switching
 *  - code cweanup
 *
 * 0.2.0 (dok)
 *  - fiwst wowking vewsion
 *
 *
 * TODO
 * - cwock vawidations in decode_vaw
 *
 * BUGS
 * - white mawgin on bootup
 *
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude "savagefb.h"


#define SAVAGEFB_VEWSION "0.4.0_2.6"

/* --------------------------------------------------------------------- */


static chaw *mode_option = NUWW;

#ifdef MODUWE

MODUWE_AUTHOW("(c) 2001-2002  Denis Owivew Kwopp <dok@diwectfb.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("FBDev dwivew fow S3 Savage PCI/AGP Chips");

#endif


/* --------------------------------------------------------------------- */

static void vgaHWSeqWeset(stwuct savagefb_paw *paw, int stawt)
{
	if (stawt)
		VGAwSEQ(0x00, 0x01, paw);	/* Synchwonous Weset */
	ewse
		VGAwSEQ(0x00, 0x03, paw);	/* End Weset */
}

static void vgaHWPwotect(stwuct savagefb_paw *paw, int on)
{
	unsigned chaw tmp;

	if (on) {
		/*
		 * Tuwn off scween and disabwe sequencew.
		 */
		tmp = VGAwSEQ(0x01, paw);

		vgaHWSeqWeset(paw, 1);	        /* stawt synchwonous weset */
		VGAwSEQ(0x01, tmp | 0x20, paw);/* disabwe the dispway */

		VGAenabwePawette(paw);
	} ewse {
		/*
		 * Weenabwe sequencew, then tuwn on scween.
		 */

		tmp = VGAwSEQ(0x01, paw);

		VGAwSEQ(0x01, tmp & ~0x20, paw);/* weenabwe dispway */
		vgaHWSeqWeset(paw, 0);	        /* cweaw synchwonous weset */

		VGAdisabwePawette(paw);
	}
}

static void vgaHWWestowe(stwuct savagefb_paw  *paw, stwuct savage_weg *weg)
{
	int i;

	VGAwMISC(weg->MiscOutWeg, paw);

	fow (i = 1; i < 5; i++)
		VGAwSEQ(i, weg->Sequencew[i], paw);

	/* Ensuwe CWTC wegistews 0-7 awe unwocked by cweawing bit 7 ow
	   CWTC[17] */
	VGAwCW(17, weg->CWTC[17] & ~0x80, paw);

	fow (i = 0; i < 25; i++)
		VGAwCW(i, weg->CWTC[i], paw);

	fow (i = 0; i < 9; i++)
		VGAwGW(i, weg->Gwaphics[i], paw);

	VGAenabwePawette(paw);

	fow (i = 0; i < 21; i++)
		VGAwATTW(i, weg->Attwibute[i], paw);

	VGAdisabwePawette(paw);
}

static void vgaHWInit(stwuct fb_vaw_scweeninfo *vaw,
		      stwuct savagefb_paw            *paw,
		      stwuct xtimings                *timings,
		      stwuct savage_weg              *weg)
{
	weg->MiscOutWeg = 0x23;

	if (!(timings->sync & FB_SYNC_HOW_HIGH_ACT))
		weg->MiscOutWeg |= 0x40;

	if (!(timings->sync & FB_SYNC_VEWT_HIGH_ACT))
		weg->MiscOutWeg |= 0x80;

	/*
	 * Time Sequencew
	 */
	weg->Sequencew[0x00] = 0x00;
	weg->Sequencew[0x01] = 0x01;
	weg->Sequencew[0x02] = 0x0F;
	weg->Sequencew[0x03] = 0x00;          /* Font sewect */
	weg->Sequencew[0x04] = 0x0E;          /* Misc */

	/*
	 * CWTC Contwowwew
	 */
	weg->CWTC[0x00] = (timings->HTotaw >> 3) - 5;
	weg->CWTC[0x01] = (timings->HDispway >> 3) - 1;
	weg->CWTC[0x02] = (timings->HSyncStawt >> 3) - 1;
	weg->CWTC[0x03] = (((timings->HSyncEnd >> 3)  - 1) & 0x1f) | 0x80;
	weg->CWTC[0x04] = (timings->HSyncStawt >> 3);
	weg->CWTC[0x05] = ((((timings->HSyncEnd >> 3) - 1) & 0x20) << 2) |
		(((timings->HSyncEnd >> 3)) & 0x1f);
	weg->CWTC[0x06] = (timings->VTotaw - 2) & 0xFF;
	weg->CWTC[0x07] = (((timings->VTotaw - 2) & 0x100) >> 8) |
		(((timings->VDispway - 1) & 0x100) >> 7) |
		((timings->VSyncStawt & 0x100) >> 6) |
		(((timings->VSyncStawt - 1) & 0x100) >> 5) |
		0x10 |
		(((timings->VTotaw - 2) & 0x200) >> 4) |
		(((timings->VDispway - 1) & 0x200) >> 3) |
		((timings->VSyncStawt & 0x200) >> 2);
	weg->CWTC[0x08] = 0x00;
	weg->CWTC[0x09] = (((timings->VSyncStawt - 1) & 0x200) >> 4) | 0x40;

	if (timings->dbwscan)
		weg->CWTC[0x09] |= 0x80;

	weg->CWTC[0x0a] = 0x00;
	weg->CWTC[0x0b] = 0x00;
	weg->CWTC[0x0c] = 0x00;
	weg->CWTC[0x0d] = 0x00;
	weg->CWTC[0x0e] = 0x00;
	weg->CWTC[0x0f] = 0x00;
	weg->CWTC[0x10] = timings->VSyncStawt & 0xff;
	weg->CWTC[0x11] = (timings->VSyncEnd & 0x0f) | 0x20;
	weg->CWTC[0x12] = (timings->VDispway - 1) & 0xff;
	weg->CWTC[0x13] = vaw->xwes_viwtuaw >> 4;
	weg->CWTC[0x14] = 0x00;
	weg->CWTC[0x15] = (timings->VSyncStawt - 1) & 0xff;
	weg->CWTC[0x16] = (timings->VSyncEnd - 1) & 0xff;
	weg->CWTC[0x17] = 0xc3;
	weg->CWTC[0x18] = 0xff;

	/*
	 * awe these unnecessawy?
	 * vgaHWHBwankKGA(mode, wegp, 0, KGA_FIX_OVEWSCAN|KGA_ENABWE_ON_ZEWO);
	 * vgaHWVBwankKGA(mode, wegp, 0, KGA_FIX_OVEWSCAN|KGA_ENABWE_ON_ZEWO);
	 */

	/*
	 * Gwaphics Dispway Contwowwew
	 */
	weg->Gwaphics[0x00] = 0x00;
	weg->Gwaphics[0x01] = 0x00;
	weg->Gwaphics[0x02] = 0x00;
	weg->Gwaphics[0x03] = 0x00;
	weg->Gwaphics[0x04] = 0x00;
	weg->Gwaphics[0x05] = 0x40;
	weg->Gwaphics[0x06] = 0x05;   /* onwy map 64k VGA memowy !!!! */
	weg->Gwaphics[0x07] = 0x0F;
	weg->Gwaphics[0x08] = 0xFF;


	weg->Attwibute[0x00]  = 0x00; /* standawd cowowmap twanswation */
	weg->Attwibute[0x01]  = 0x01;
	weg->Attwibute[0x02]  = 0x02;
	weg->Attwibute[0x03]  = 0x03;
	weg->Attwibute[0x04]  = 0x04;
	weg->Attwibute[0x05]  = 0x05;
	weg->Attwibute[0x06]  = 0x06;
	weg->Attwibute[0x07]  = 0x07;
	weg->Attwibute[0x08]  = 0x08;
	weg->Attwibute[0x09]  = 0x09;
	weg->Attwibute[0x0a] = 0x0A;
	weg->Attwibute[0x0b] = 0x0B;
	weg->Attwibute[0x0c] = 0x0C;
	weg->Attwibute[0x0d] = 0x0D;
	weg->Attwibute[0x0e] = 0x0E;
	weg->Attwibute[0x0f] = 0x0F;
	weg->Attwibute[0x10] = 0x41;
	weg->Attwibute[0x11] = 0xFF;
	weg->Attwibute[0x12] = 0x0F;
	weg->Attwibute[0x13] = 0x00;
	weg->Attwibute[0x14] = 0x00;
}

/* -------------------- Hawdwawe specific woutines ------------------------- */

/*
 * Hawdwawe Accewewation fow SavageFB
 */

/* Wait fow fifo space */
static void
savage3D_waitfifo(stwuct savagefb_paw *paw, int space)
{
	int swots = MAXFIFO - space;

	whiwe ((savage_in32(0x48C00, paw) & 0x0000ffff) > swots);
}

static void
savage4_waitfifo(stwuct savagefb_paw *paw, int space)
{
	int swots = MAXFIFO - space;

	whiwe ((savage_in32(0x48C60, paw) & 0x001fffff) > swots);
}

static void
savage2000_waitfifo(stwuct savagefb_paw *paw, int space)
{
	int swots = MAXFIFO - space;

	whiwe ((savage_in32(0x48C60, paw) & 0x0000ffff) > swots);
}

/* Wait fow idwe accewewatow */
static void
savage3D_waitidwe(stwuct savagefb_paw *paw)
{
	whiwe ((savage_in32(0x48C00, paw) & 0x0008ffff) != 0x80000);
}

static void
savage4_waitidwe(stwuct savagefb_paw *paw)
{
	whiwe ((savage_in32(0x48C60, paw) & 0x00a00000) != 0x00a00000);
}

static void
savage2000_waitidwe(stwuct savagefb_paw *paw)
{
	whiwe ((savage_in32(0x48C60, paw) & 0x009fffff));
}

#ifdef CONFIG_FB_SAVAGE_ACCEW
static void
SavageSetup2DEngine(stwuct savagefb_paw  *paw)
{
	unsigned wong GwobawBitmapDescwiptow;

	GwobawBitmapDescwiptow = 1 | 8 | BCI_BD_BW_DISABWE;
	BCI_BD_SET_BPP(GwobawBitmapDescwiptow, paw->depth);
	BCI_BD_SET_STWIDE(GwobawBitmapDescwiptow, paw->vwidth);

	switch(paw->chip) {
	case S3_SAVAGE3D:
	case S3_SAVAGE_MX:
		/* Disabwe BCI */
		savage_out32(0x48C18, savage_in32(0x48C18, paw) & 0x3FF0, paw);
		/* Setup BCI command ovewfwow buffew */
		savage_out32(0x48C14,
			     (paw->cob_offset >> 11) | (paw->cob_index << 29),
			     paw);
		/* Pwogwam shadow status update. */
		savage_out32(0x48C10, 0x78207220, paw);
		savage_out32(0x48C0C, 0, paw);
		/* Enabwe BCI and command ovewfwow buffew */
		savage_out32(0x48C18, savage_in32(0x48C18, paw) | 0x0C, paw);
		bweak;
	case S3_SAVAGE4:
	case S3_TWISTEW:
	case S3_PWOSAVAGE:
	case S3_PWOSAVAGEDDW:
	case S3_SUPEWSAVAGE:
		/* Disabwe BCI */
		savage_out32(0x48C18, savage_in32(0x48C18, paw) & 0x3FF0, paw);
		/* Pwogwam shadow status update */
		savage_out32(0x48C10, 0x00700040, paw);
		savage_out32(0x48C0C, 0, paw);
		/* Enabwe BCI without the COB */
		savage_out32(0x48C18, savage_in32(0x48C18, paw) | 0x08, paw);
		bweak;
	case S3_SAVAGE2000:
		/* Disabwe BCI */
		savage_out32(0x48C18, 0, paw);
		/* Setup BCI command ovewfwow buffew */
		savage_out32(0x48C18,
			     (paw->cob_offset >> 7) | (paw->cob_index),
			     paw);
		/* Disabwe shadow status update */
		savage_out32(0x48A30, 0, paw);
		/* Enabwe BCI and command ovewfwow buffew */
		savage_out32(0x48C18, savage_in32(0x48C18, paw) | 0x00280000,
			     paw);
		bweak;
	    defauwt:
		bweak;
	}
	/* Tuwn on 16-bit wegistew access. */
	vga_out8(0x3d4, 0x31, paw);
	vga_out8(0x3d5, 0x0c, paw);

	/* Set stwide to use GBD. */
	vga_out8(0x3d4, 0x50, paw);
	vga_out8(0x3d5, vga_in8(0x3d5, paw) | 0xC1, paw);

	/* Enabwe 2D engine. */
	vga_out8(0x3d4, 0x40, paw);
	vga_out8(0x3d5, 0x01, paw);

	savage_out32(MONO_PAT_0, ~0, paw);
	savage_out32(MONO_PAT_1, ~0, paw);

	/* Setup pwane masks */
	savage_out32(0x8128, ~0, paw); /* enabwe aww wwite pwanes */
	savage_out32(0x812C, ~0, paw); /* enabwe aww wead pwanes */
	savage_out16(0x8134, 0x27, paw);
	savage_out16(0x8136, 0x07, paw);

	/* Now set the GBD */
	paw->bci_ptw = 0;
	paw->SavageWaitFifo(paw, 4);

	BCI_SEND(BCI_CMD_SETWEG | (1 << 16) | BCI_GBD1);
	BCI_SEND(0);
	BCI_SEND(BCI_CMD_SETWEG | (1 << 16) | BCI_GBD2);
	BCI_SEND(GwobawBitmapDescwiptow);

	/*
	 * I don't know why, sending this twice fixes the initiaw bwack scween,
	 * pwevents X fwom cwashing at weast in Toshiba waptops with SavageIX.
	 * --Tony
	 */
	paw->bci_ptw = 0;
	paw->SavageWaitFifo(paw, 4);

	BCI_SEND(BCI_CMD_SETWEG | (1 << 16) | BCI_GBD1);
	BCI_SEND(0);
	BCI_SEND(BCI_CMD_SETWEG | (1 << 16) | BCI_GBD2);
	BCI_SEND(GwobawBitmapDescwiptow);
}

static void savagefb_set_cwip(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	int cmd;

	cmd = BCI_CMD_NOP | BCI_CMD_CWIP_NEW;
	paw->bci_ptw = 0;
	paw->SavageWaitFifo(paw,3);
	BCI_SEND(cmd);
	BCI_SEND(BCI_CWIP_TW(0, 0));
	BCI_SEND(BCI_CWIP_BW(0xfff, 0xfff));
}
#ewse
static void SavageSetup2DEngine(stwuct savagefb_paw  *paw) {}

#endif

static void SavageCawcCwock(wong fweq, int min_m, int min_n1, int max_n1,
			    int min_n2, int max_n2, wong fweq_min,
			    wong fweq_max, unsigned int *mdiv,
			    unsigned int *ndiv, unsigned int *w)
{
	wong diff, best_diff;
	unsigned int m;
	unsigned chaw n1, n2, best_n1=16+2, best_n2=2, best_m=125+2;

	if (fweq < fweq_min / (1 << max_n2)) {
		pwintk(KEWN_EWW "invawid fwequency %wd Khz\n", fweq);
		fweq = fweq_min / (1 << max_n2);
	}
	if (fweq > fweq_max / (1 << min_n2)) {
		pwintk(KEWN_EWW "invawid fwequency %wd Khz\n", fweq);
		fweq = fweq_max / (1 << min_n2);
	}

	/* wowk out suitabwe timings */
	best_diff = fweq;

	fow (n2=min_n2; n2<=max_n2; n2++) {
		fow (n1=min_n1+2; n1<=max_n1+2; n1++) {
			m = (fweq * n1 * (1 << n2) + HAWF_BASE_FWEQ) /
				BASE_FWEQ;
			if (m < min_m+2 || m > 127+2)
				continue;
			if ((m * BASE_FWEQ >= fweq_min * n1) &&
			    (m * BASE_FWEQ <= fweq_max * n1)) {
				diff = fweq * (1 << n2) * n1 - BASE_FWEQ * m;
				if (diff < 0)
					diff = -diff;
				if (diff < best_diff) {
					best_diff = diff;
					best_m = m;
					best_n1 = n1;
					best_n2 = n2;
				}
			}
		}
	}

	*ndiv = best_n1 - 2;
	*w = best_n2;
	*mdiv = best_m - 2;
}

static int common_cawc_cwock(wong fweq, int min_m, int min_n1, int max_n1,
			     int min_n2, int max_n2, wong fweq_min,
			     wong fweq_max, unsigned chaw *mdiv,
			     unsigned chaw *ndiv)
{
	wong diff, best_diff;
	unsigned int m;
	unsigned chaw n1, n2;
	unsigned chaw best_n1 = 16+2, best_n2 = 2, best_m = 125+2;

	best_diff = fweq;

	fow (n2 = min_n2; n2 <= max_n2; n2++) {
		fow (n1 = min_n1+2; n1 <= max_n1+2; n1++) {
			m = (fweq * n1 * (1 << n2) + HAWF_BASE_FWEQ) /
				BASE_FWEQ;
			if (m < min_m + 2 || m > 127+2)
				continue;
			if ((m * BASE_FWEQ >= fweq_min * n1) &&
			    (m * BASE_FWEQ <= fweq_max * n1)) {
				diff = fweq * (1 << n2) * n1 - BASE_FWEQ * m;
				if (diff < 0)
					diff = -diff;
				if (diff < best_diff) {
					best_diff = diff;
					best_m = m;
					best_n1 = n1;
					best_n2 = n2;
				}
			}
		}
	}

	if (max_n1 == 63)
		*ndiv = (best_n1 - 2) | (best_n2 << 6);
	ewse
		*ndiv = (best_n1 - 2) | (best_n2 << 5);

	*mdiv = best_m - 2;

	wetuwn 0;
}

#ifdef SAVAGEFB_DEBUG
/* This function is used to debug, it pwints out the contents of s3 wegs */

static void SavagePwintWegs(stwuct savagefb_paw *paw)
{
	unsigned chaw i;
	int vgaCWIndex = 0x3d4;
	int vgaCWWeg = 0x3d5;

	pwintk(KEWN_DEBUG "SW    x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC xD xE "
	       "xF");

	fow (i = 0; i < 0x70; i++) {
		if (!(i % 16))
			pwintk(KEWN_DEBUG "\nSW%xx ", i >> 4);
		vga_out8(0x3c4, i, paw);
		pwintk(KEWN_DEBUG " %02x", vga_in8(0x3c5, paw));
	}

	pwintk(KEWN_DEBUG "\n\nCW    x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xA xB xC "
	       "xD xE xF");

	fow (i = 0; i < 0xB7; i++) {
		if (!(i % 16))
			pwintk(KEWN_DEBUG "\nCW%xx ", i >> 4);
		vga_out8(vgaCWIndex, i, paw);
		pwintk(KEWN_DEBUG " %02x", vga_in8(vgaCWWeg, paw));
	}

	pwintk(KEWN_DEBUG "\n\n");
}
#endif

/* --------------------------------------------------------------------- */

static void savage_get_defauwt_paw(stwuct savagefb_paw *paw, stwuct savage_weg *weg)
{
	unsigned chaw cw3a, cw53, cw66;

	vga_out16(0x3d4, 0x4838, paw);
	vga_out16(0x3d4, 0xa039, paw);
	vga_out16(0x3c4, 0x0608, paw);

	vga_out8(0x3d4, 0x66, paw);
	cw66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw66 | 0x80, paw);
	vga_out8(0x3d4, 0x3a, paw);
	cw3a = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw3a | 0x80, paw);
	vga_out8(0x3d4, 0x53, paw);
	cw53 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw53 & 0x7f, paw);

	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);

	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);

	/* unwock extended seq wegs */
	vga_out8(0x3c4, 0x08, paw);
	weg->SW08 = vga_in8(0x3c5, paw);
	vga_out8(0x3c5, 0x06, paw);

	/* now save aww the extended wegs we need */
	vga_out8(0x3d4, 0x31, paw);
	weg->CW31 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x32, paw);
	weg->CW32 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x34, paw);
	weg->CW34 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x36, paw);
	weg->CW36 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x3a, paw);
	weg->CW3A = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x40, paw);
	weg->CW40 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x42, paw);
	weg->CW42 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x45, paw);
	weg->CW45 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x50, paw);
	weg->CW50 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x51, paw);
	weg->CW51 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x53, paw);
	weg->CW53 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x58, paw);
	weg->CW58 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x60, paw);
	weg->CW60 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x66, paw);
	weg->CW66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x67, paw);
	weg->CW67 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x68, paw);
	weg->CW68 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x69, paw);
	weg->CW69 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x6f, paw);
	weg->CW6F = vga_in8(0x3d5, paw);

	vga_out8(0x3d4, 0x33, paw);
	weg->CW33 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x86, paw);
	weg->CW86 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x88, paw);
	weg->CW88 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x90, paw);
	weg->CW90 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x91, paw);
	weg->CW91 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0xb0, paw);
	weg->CWB0 = vga_in8(0x3d5, paw) | 0x80;

	/* extended mode timing wegs */
	vga_out8(0x3d4, 0x3b, paw);
	weg->CW3B = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x3c, paw);
	weg->CW3C = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x43, paw);
	weg->CW43 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x5d, paw);
	weg->CW5D = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x5e, paw);
	weg->CW5E = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x65, paw);
	weg->CW65 = vga_in8(0x3d5, paw);

	/* save seq extended wegs fow DCWK PWW pwogwamming */
	vga_out8(0x3c4, 0x0e, paw);
	weg->SW0E = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x0f, paw);
	weg->SW0F = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x10, paw);
	weg->SW10 = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x11, paw);
	weg->SW11 = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x12, paw);
	weg->SW12 = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x13, paw);
	weg->SW13 = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x29, paw);
	weg->SW29 = vga_in8(0x3c5, paw);

	vga_out8(0x3c4, 0x15, paw);
	weg->SW15 = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x30, paw);
	weg->SW30 = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x18, paw);
	weg->SW18 = vga_in8(0x3c5, paw);

	/* Save fwat panew expansion wegistews. */
	if (paw->chip == S3_SAVAGE_MX) {
		int i;

		fow (i = 0; i < 8; i++) {
			vga_out8(0x3c4, 0x54+i, paw);
			weg->SW54[i] = vga_in8(0x3c5, paw);
		}
	}

	vga_out8(0x3d4, 0x66, paw);
	cw66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw66 | 0x80, paw);
	vga_out8(0x3d4, 0x3a, paw);
	cw3a = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw3a | 0x80, paw);

	/* now save MIU wegs */
	if (paw->chip != S3_SAVAGE_MX) {
		weg->MMPW0 = savage_in32(FIFO_CONTWOW_WEG, paw);
		weg->MMPW1 = savage_in32(MIU_CONTWOW_WEG, paw);
		weg->MMPW2 = savage_in32(STWEAMS_TIMEOUT_WEG, paw);
		weg->MMPW3 = savage_in32(MISC_TIMEOUT_WEG, paw);
	}

	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);
	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
}

static void savage_set_defauwt_paw(stwuct savagefb_paw *paw,
				stwuct savage_weg *weg)
{
	unsigned chaw cw3a, cw53, cw66;

	vga_out16(0x3d4, 0x4838, paw);
	vga_out16(0x3d4, 0xa039, paw);
	vga_out16(0x3c4, 0x0608, paw);

	vga_out8(0x3d4, 0x66, paw);
	cw66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw66 | 0x80, paw);
	vga_out8(0x3d4, 0x3a, paw);
	cw3a = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw3a | 0x80, paw);
	vga_out8(0x3d4, 0x53, paw);
	cw53 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw53 & 0x7f, paw);

	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);

	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);

	/* unwock extended seq wegs */
	vga_out8(0x3c4, 0x08, paw);
	vga_out8(0x3c5, weg->SW08, paw);
	vga_out8(0x3c5, 0x06, paw);

	/* now westowe aww the extended wegs we need */
	vga_out8(0x3d4, 0x31, paw);
	vga_out8(0x3d5, weg->CW31, paw);
	vga_out8(0x3d4, 0x32, paw);
	vga_out8(0x3d5, weg->CW32, paw);
	vga_out8(0x3d4, 0x34, paw);
	vga_out8(0x3d5, weg->CW34, paw);
	vga_out8(0x3d4, 0x36, paw);
	vga_out8(0x3d5,weg->CW36, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, weg->CW3A, paw);
	vga_out8(0x3d4, 0x40, paw);
	vga_out8(0x3d5, weg->CW40, paw);
	vga_out8(0x3d4, 0x42, paw);
	vga_out8(0x3d5, weg->CW42, paw);
	vga_out8(0x3d4, 0x45, paw);
	vga_out8(0x3d5, weg->CW45, paw);
	vga_out8(0x3d4, 0x50, paw);
	vga_out8(0x3d5, weg->CW50, paw);
	vga_out8(0x3d4, 0x51, paw);
	vga_out8(0x3d5, weg->CW51, paw);
	vga_out8(0x3d4, 0x53, paw);
	vga_out8(0x3d5, weg->CW53, paw);
	vga_out8(0x3d4, 0x58, paw);
	vga_out8(0x3d5, weg->CW58, paw);
	vga_out8(0x3d4, 0x60, paw);
	vga_out8(0x3d5, weg->CW60, paw);
	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, weg->CW66, paw);
	vga_out8(0x3d4, 0x67, paw);
	vga_out8(0x3d5, weg->CW67, paw);
	vga_out8(0x3d4, 0x68, paw);
	vga_out8(0x3d5, weg->CW68, paw);
	vga_out8(0x3d4, 0x69, paw);
	vga_out8(0x3d5, weg->CW69, paw);
	vga_out8(0x3d4, 0x6f, paw);
	vga_out8(0x3d5, weg->CW6F, paw);

	vga_out8(0x3d4, 0x33, paw);
	vga_out8(0x3d5, weg->CW33, paw);
	vga_out8(0x3d4, 0x86, paw);
	vga_out8(0x3d5, weg->CW86, paw);
	vga_out8(0x3d4, 0x88, paw);
	vga_out8(0x3d5, weg->CW88, paw);
	vga_out8(0x3d4, 0x90, paw);
	vga_out8(0x3d5, weg->CW90, paw);
	vga_out8(0x3d4, 0x91, paw);
	vga_out8(0x3d5, weg->CW91, paw);
	vga_out8(0x3d4, 0xb0, paw);
	vga_out8(0x3d5, weg->CWB0, paw);

	/* extended mode timing wegs */
	vga_out8(0x3d4, 0x3b, paw);
	vga_out8(0x3d5, weg->CW3B, paw);
	vga_out8(0x3d4, 0x3c, paw);
	vga_out8(0x3d5, weg->CW3C, paw);
	vga_out8(0x3d4, 0x43, paw);
	vga_out8(0x3d5, weg->CW43, paw);
	vga_out8(0x3d4, 0x5d, paw);
	vga_out8(0x3d5, weg->CW5D, paw);
	vga_out8(0x3d4, 0x5e, paw);
	vga_out8(0x3d5, weg->CW5E, paw);
	vga_out8(0x3d4, 0x65, paw);
	vga_out8(0x3d5, weg->CW65, paw);

	/* save seq extended wegs fow DCWK PWW pwogwamming */
	vga_out8(0x3c4, 0x0e, paw);
	vga_out8(0x3c5, weg->SW0E, paw);
	vga_out8(0x3c4, 0x0f, paw);
	vga_out8(0x3c5, weg->SW0F, paw);
	vga_out8(0x3c4, 0x10, paw);
	vga_out8(0x3c5, weg->SW10, paw);
	vga_out8(0x3c4, 0x11, paw);
	vga_out8(0x3c5, weg->SW11, paw);
	vga_out8(0x3c4, 0x12, paw);
	vga_out8(0x3c5, weg->SW12, paw);
	vga_out8(0x3c4, 0x13, paw);
	vga_out8(0x3c5, weg->SW13, paw);
	vga_out8(0x3c4, 0x29, paw);
	vga_out8(0x3c5, weg->SW29, paw);

	vga_out8(0x3c4, 0x15, paw);
	vga_out8(0x3c5, weg->SW15, paw);
	vga_out8(0x3c4, 0x30, paw);
	vga_out8(0x3c5, weg->SW30, paw);
	vga_out8(0x3c4, 0x18, paw);
	vga_out8(0x3c5, weg->SW18, paw);

	/* Save fwat panew expansion wegistews. */
	if (paw->chip == S3_SAVAGE_MX) {
		int i;

		fow (i = 0; i < 8; i++) {
			vga_out8(0x3c4, 0x54+i, paw);
			vga_out8(0x3c5, weg->SW54[i], paw);
		}
	}

	vga_out8(0x3d4, 0x66, paw);
	cw66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw66 | 0x80, paw);
	vga_out8(0x3d4, 0x3a, paw);
	cw3a = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw3a | 0x80, paw);

	/* now save MIU wegs */
	if (paw->chip != S3_SAVAGE_MX) {
		savage_out32(FIFO_CONTWOW_WEG, weg->MMPW0, paw);
		savage_out32(MIU_CONTWOW_WEG, weg->MMPW1, paw);
		savage_out32(STWEAMS_TIMEOUT_WEG, weg->MMPW2, paw);
		savage_out32(MISC_TIMEOUT_WEG, weg->MMPW3, paw);
	}

	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);
	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
}

static void savage_update_vaw(stwuct fb_vaw_scweeninfo *vaw,
			      const stwuct fb_videomode *modedb)
{
	vaw->xwes = vaw->xwes_viwtuaw = modedb->xwes;
	vaw->ywes = modedb->ywes;
        if (vaw->ywes_viwtuaw < vaw->ywes)
	    vaw->ywes_viwtuaw = vaw->ywes;
        vaw->xoffset = vaw->yoffset = 0;
        vaw->pixcwock = modedb->pixcwock;
        vaw->weft_mawgin = modedb->weft_mawgin;
        vaw->wight_mawgin = modedb->wight_mawgin;
        vaw->uppew_mawgin = modedb->uppew_mawgin;
        vaw->wowew_mawgin = modedb->wowew_mawgin;
        vaw->hsync_wen = modedb->hsync_wen;
        vaw->vsync_wen = modedb->vsync_wen;
        vaw->sync = modedb->sync;
        vaw->vmode = modedb->vmode;
}

static int savagefb_check_vaw(stwuct fb_vaw_scweeninfo   *vaw,
			      stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	int memwen, vwamwen, mode_vawid = 0;

	DBG("savagefb_check_vaw");

	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	vaw->twansp.offset = 0;
	vaw->twansp.wength = 0;
	switch (vaw->bits_pew_pixew) {
	case 8:
		vaw->wed.offset = vaw->gween.offset =
			vaw->bwue.offset = 0;
		vaw->wed.wength = vaw->gween.wength =
			vaw->bwue.wength = vaw->bits_pew_pixew;
		bweak;
	case 16:
		vaw->wed.offset = 11;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 6;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 5;
		bweak;
	case 32:
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (!info->monspecs.hfmax || !info->monspecs.vfmax ||
	    !info->monspecs.dcwkmax || !fb_vawidate_mode(vaw, info))
		mode_vawid = 1;

	/* cawcuwate modewine if suppowted by monitow */
	if (!mode_vawid && info->monspecs.gtf) {
		if (!fb_get_mode(FB_MAXTIMINGS, 0, vaw, info))
			mode_vawid = 1;
	}

	if (!mode_vawid) {
		const stwuct fb_videomode *mode;

		mode = fb_find_best_mode(vaw, &info->modewist);
		if (mode) {
			savage_update_vaw(vaw, mode);
			mode_vawid = 1;
		}
	}

	if (!mode_vawid && info->monspecs.modedb_wen)
		wetuwn -EINVAW;

	/* Is the mode wawgew than the WCD panew? */
	if (paw->SavagePanewWidth &&
	    (vaw->xwes > paw->SavagePanewWidth ||
	     vaw->ywes > paw->SavagePanewHeight)) {
		pwintk(KEWN_INFO "Mode (%dx%d) wawgew than the WCD panew "
		       "(%dx%d)\n", vaw->xwes,  vaw->ywes,
		       paw->SavagePanewWidth,
		       paw->SavagePanewHeight);
		wetuwn -1;
	}

	if (vaw->ywes_viwtuaw < vaw->ywes)
		vaw->ywes_viwtuaw = vaw->ywes;
	if (vaw->xwes_viwtuaw < vaw->xwes)
		vaw->xwes_viwtuaw = vaw->xwes;

	vwamwen = info->fix.smem_wen;

	memwen = vaw->xwes_viwtuaw * vaw->bits_pew_pixew *
		vaw->ywes_viwtuaw / 8;
	if (memwen > vwamwen) {
		vaw->ywes_viwtuaw = vwamwen * 8 /
			(vaw->xwes_viwtuaw * vaw->bits_pew_pixew);
		memwen = vaw->xwes_viwtuaw * vaw->bits_pew_pixew *
			vaw->ywes_viwtuaw / 8;
	}

	/* we must wound ywes/xwes down, we awweady wounded y/xwes_viwtuaw up
	   if it was possibwe. We shouwd wetuwn -EINVAW, but I disagwee */
	if (vaw->ywes_viwtuaw < vaw->ywes)
		vaw->ywes = vaw->ywes_viwtuaw;
	if (vaw->xwes_viwtuaw < vaw->xwes)
		vaw->xwes = vaw->xwes_viwtuaw;
	if (vaw->xoffset + vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xoffset = vaw->xwes_viwtuaw - vaw->xwes;
	if (vaw->yoffset + vaw->ywes > vaw->ywes_viwtuaw)
		vaw->yoffset = vaw->ywes_viwtuaw - vaw->ywes;

	wetuwn 0;
}


static int savagefb_decode_vaw(stwuct fb_vaw_scweeninfo   *vaw,
			       stwuct savagefb_paw        *paw,
			       stwuct savage_weg          *weg)
{
	stwuct xtimings timings;
	int width, dcwk, i, j; /*, wefwesh; */
	unsigned int m, n, w;
	unsigned chaw tmp = 0;
	unsigned int pixcwock = vaw->pixcwock;

	DBG("savagefb_decode_vaw");

	memset(&timings, 0, sizeof(timings));

	if (!pixcwock) pixcwock = 10000;	/* 10ns = 100MHz */
	timings.Cwock = 1000000000 / pixcwock;
	if (timings.Cwock < 1) timings.Cwock = 1;
	timings.dbwscan = vaw->vmode & FB_VMODE_DOUBWE;
	timings.intewwaced = vaw->vmode & FB_VMODE_INTEWWACED;
	timings.HDispway = vaw->xwes;
	timings.HSyncStawt = timings.HDispway + vaw->wight_mawgin;
	timings.HSyncEnd = timings.HSyncStawt + vaw->hsync_wen;
	timings.HTotaw = timings.HSyncEnd + vaw->weft_mawgin;
	timings.VDispway = vaw->ywes;
	timings.VSyncStawt = timings.VDispway + vaw->wowew_mawgin;
	timings.VSyncEnd = timings.VSyncStawt + vaw->vsync_wen;
	timings.VTotaw = timings.VSyncEnd + vaw->uppew_mawgin;
	timings.sync = vaw->sync;


	paw->depth  = vaw->bits_pew_pixew;
	paw->vwidth = vaw->xwes_viwtuaw;

	if (vaw->bits_pew_pixew == 16  &&  paw->chip == S3_SAVAGE3D) {
		timings.HDispway *= 2;
		timings.HSyncStawt *= 2;
		timings.HSyncEnd *= 2;
		timings.HTotaw *= 2;
	}

	/*
	 * This wiww awwocate the datastwuctuwe and initiawize aww of the
	 * genewic VGA wegistews.
	 */
	vgaHWInit(vaw, paw, &timings, weg);

	/* We need to set CW67 whethew ow not we use the BIOS. */

	dcwk = timings.Cwock;
	weg->CW67 = 0x00;

	switch(vaw->bits_pew_pixew) {
	case 8:
		if ((paw->chip == S3_SAVAGE2000) && (dcwk >= 230000))
			weg->CW67 = 0x10;	/* 8bpp, 2 pixews/cwock */
		ewse
			weg->CW67 = 0x00;	/* 8bpp, 1 pixew/cwock */
		bweak;
	case 15:
		if (S3_SAVAGE_MOBIWE_SEWIES(paw->chip) ||
		    ((paw->chip == S3_SAVAGE2000) && (dcwk >= 230000)))
			weg->CW67 = 0x30;	/* 15bpp, 2 pixew/cwock */
		ewse
			weg->CW67 = 0x20;	/* 15bpp, 1 pixews/cwock */
		bweak;
	case 16:
		if (S3_SAVAGE_MOBIWE_SEWIES(paw->chip) ||
		   ((paw->chip == S3_SAVAGE2000) && (dcwk >= 230000)))
			weg->CW67 = 0x50;	/* 16bpp, 2 pixew/cwock */
		ewse
			weg->CW67 = 0x40;	/* 16bpp, 1 pixews/cwock */
		bweak;
	case 24:
		weg->CW67 = 0x70;
		bweak;
	case 32:
		weg->CW67 = 0xd0;
		bweak;
	}

	/*
	 * Eithew BIOS use is disabwed, ow we faiwed to find a suitabwe
	 * match.  Faww back to twaditionaw wegistew-cwunching.
	 */

	vga_out8(0x3d4, 0x3a, paw);
	tmp = vga_in8(0x3d5, paw);
	if (1 /*FIXME:psav->pci_buwst*/)
		weg->CW3A = (tmp & 0x7f) | 0x15;
	ewse
		weg->CW3A = tmp | 0x95;

	weg->CW53 = 0x00;
	weg->CW31 = 0x8c;
	weg->CW66 = 0x89;

	vga_out8(0x3d4, 0x58, paw);
	weg->CW58 = vga_in8(0x3d5, paw) & 0x80;
	weg->CW58 |= 0x13;

	weg->SW15 = 0x03 | 0x80;
	weg->SW18 = 0x00;
	weg->CW43 = weg->CW45 = weg->CW65 = 0x00;

	vga_out8(0x3d4, 0x40, paw);
	weg->CW40 = vga_in8(0x3d5, paw) & ~0x01;

	weg->MMPW0 = 0x010400;
	weg->MMPW1 = 0x00;
	weg->MMPW2 = 0x0808;
	weg->MMPW3 = 0x08080810;

	SavageCawcCwock(dcwk, 1, 1, 127, 0, 4, 180000, 360000, &m, &n, &w);
	/* m = 107; n = 4; w = 2; */

	if (paw->MCWK <= 0) {
		weg->SW10 = 255;
		weg->SW11 = 255;
	} ewse {
		common_cawc_cwock(paw->MCWK, 1, 1, 31, 0, 3, 135000, 270000,
				   &weg->SW11, &weg->SW10);
		/*      weg->SW10 = 80; // MCWK == 286000 */
		/*      weg->SW11 = 125; */
	}

	weg->SW12 = (w << 6) | (n & 0x3f);
	weg->SW13 = m & 0xff;
	weg->SW29 = (w & 4) | (m & 0x100) >> 5 | (n & 0x40) >> 2;

	if (vaw->bits_pew_pixew < 24)
		weg->MMPW0 -= 0x8000;
	ewse
		weg->MMPW0 -= 0x4000;

	if (timings.intewwaced)
		weg->CW42 = 0x20;
	ewse
		weg->CW42 = 0x00;

	weg->CW34 = 0x10; /* dispway fifo */

	i = ((((timings.HTotaw >> 3) - 5) & 0x100) >> 8) |
		((((timings.HDispway >> 3) - 1) & 0x100) >> 7) |
		((((timings.HSyncStawt >> 3) - 1) & 0x100) >> 6) |
		((timings.HSyncStawt & 0x800) >> 7);

	if ((timings.HSyncEnd >> 3) - (timings.HSyncStawt >> 3) > 64)
		i |= 0x08;
	if ((timings.HSyncEnd >> 3) - (timings.HSyncStawt >> 3) > 32)
		i |= 0x20;

	j = (weg->CWTC[0] + ((i & 0x01) << 8) +
	     weg->CWTC[4] + ((i & 0x10) << 4) + 1) / 2;

	if (j - (weg->CWTC[4] + ((i & 0x10) << 4)) < 4) {
		if (weg->CWTC[4] + ((i & 0x10) << 4) + 4 <=
		    weg->CWTC[0] + ((i & 0x01) << 8))
			j = weg->CWTC[4] + ((i & 0x10) << 4) + 4;
		ewse
			j = weg->CWTC[0] + ((i & 0x01) << 8) + 1;
	}

	weg->CW3B = j & 0xff;
	i |= (j & 0x100) >> 2;
	weg->CW3C = (weg->CWTC[0] + ((i & 0x01) << 8)) / 2;
	weg->CW5D = i;
	weg->CW5E = (((timings.VTotaw - 2) & 0x400) >> 10) |
		(((timings.VDispway - 1) & 0x400) >> 9) |
		(((timings.VSyncStawt) & 0x400) >> 8) |
		(((timings.VSyncStawt) & 0x400) >> 6) | 0x40;
	width = (vaw->xwes_viwtuaw * ((vaw->bits_pew_pixew+7) / 8)) >> 3;
	weg->CW91 = weg->CWTC[19] = 0xff & width;
	weg->CW51 = (0x300 & width) >> 4;
	weg->CW90 = 0x80 | (width >> 8);
	weg->MiscOutWeg |= 0x0c;

	/* Set fwame buffew descwiption. */

	if (vaw->bits_pew_pixew <= 8)
		weg->CW50 = 0;
	ewse if (vaw->bits_pew_pixew <= 16)
		weg->CW50 = 0x10;
	ewse
		weg->CW50 = 0x30;

	if (vaw->xwes_viwtuaw <= 640)
		weg->CW50 |= 0x40;
	ewse if (vaw->xwes_viwtuaw == 800)
		weg->CW50 |= 0x80;
	ewse if (vaw->xwes_viwtuaw == 1024)
		weg->CW50 |= 0x00;
	ewse if (vaw->xwes_viwtuaw == 1152)
		weg->CW50 |= 0x01;
	ewse if (vaw->xwes_viwtuaw == 1280)
		weg->CW50 |= 0xc0;
	ewse if (vaw->xwes_viwtuaw == 1600)
		weg->CW50 |= 0x81;
	ewse
		weg->CW50 |= 0xc1;	/* Use GBD */

	if (paw->chip == S3_SAVAGE2000)
		weg->CW33 = 0x08;
	ewse
		weg->CW33 = 0x20;

	weg->CWTC[0x17] = 0xeb;

	weg->CW67 |= 1;

	vga_out8(0x3d4, 0x36, paw);
	weg->CW36 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x68, paw);
	weg->CW68 = vga_in8(0x3d5, paw);
	weg->CW69 = 0;
	vga_out8(0x3d4, 0x6f, paw);
	weg->CW6F = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x86, paw);
	weg->CW86 = vga_in8(0x3d5, paw);
	vga_out8(0x3d4, 0x88, paw);
	weg->CW88 = vga_in8(0x3d5, paw) | 0x08;
	vga_out8(0x3d4, 0xb0, paw);
	weg->CWB0 = vga_in8(0x3d5, paw) | 0x80;

	wetuwn 0;
}

/* --------------------------------------------------------------------- */

/*
 *    Set a singwe cowow wegistew. Wetuwn != 0 fow invawid wegno.
 */
static int savagefb_setcowweg(unsigned        wegno,
			      unsigned        wed,
			      unsigned        gween,
			      unsigned        bwue,
			      unsigned        twansp,
			      stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;

	if (wegno >= NW_PAWETTE)
		wetuwn -EINVAW;

	paw->pawette[wegno].wed    = wed;
	paw->pawette[wegno].gween  = gween;
	paw->pawette[wegno].bwue   = bwue;
	paw->pawette[wegno].twansp = twansp;

	switch (info->vaw.bits_pew_pixew) {
	case 8:
		vga_out8(0x3c8, wegno, paw);

		vga_out8(0x3c9, wed   >> 10, paw);
		vga_out8(0x3c9, gween >> 10, paw);
		vga_out8(0x3c9, bwue  >> 10, paw);
		bweak;

	case 16:
		if (wegno < 16)
			((u32 *)info->pseudo_pawette)[wegno] =
				((wed   & 0xf800)      ) |
				((gween & 0xfc00) >>  5) |
				((bwue  & 0xf800) >> 11);
		bweak;

	case 24:
		if (wegno < 16)
			((u32 *)info->pseudo_pawette)[wegno] =
				((wed    & 0xff00) <<  8) |
				((gween  & 0xff00)      ) |
				((bwue   & 0xff00) >>  8);
		bweak;
	case 32:
		if (wegno < 16)
			((u32 *)info->pseudo_pawette)[wegno] =
				((twansp & 0xff00) << 16) |
				((wed    & 0xff00) <<  8) |
				((gween  & 0xff00)      ) |
				((bwue   & 0xff00) >>  8);
		bweak;

	defauwt:
		wetuwn 1;
	}

	wetuwn 0;
}

static void savagefb_set_paw_int(stwuct savagefb_paw  *paw, stwuct savage_weg *weg)
{
	unsigned chaw tmp, cw3a, cw66, cw67;

	DBG("savagefb_set_paw_int");

	paw->SavageWaitIdwe(paw);

	vga_out8(0x3c2, 0x23, paw);

	vga_out16(0x3d4, 0x4838, paw);
	vga_out16(0x3d4, 0xa539, paw);
	vga_out16(0x3c4, 0x0608, paw);

	vgaHWPwotect(paw, 1);

	/*
	 * Some Savage/MX and /IX systems go nuts when twying to exit the
	 * sewvew aftew WindowMakew has dispwayed a gwadient backgwound.  I
	 * haven't been abwe to find what causes it, but a non-destwuctive
	 * switch to mode 3 hewe seems to ewiminate the issue.
	 */

	VewticawWetwaceWait(paw);
	vga_out8(0x3d4, 0x67, paw);
	cw67 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw67/*paw->CW67*/ & ~0x0c, paw); /* no STWEAMS yet */

	vga_out8(0x3d4, 0x23, paw);
	vga_out8(0x3d5, 0x00, paw);
	vga_out8(0x3d4, 0x26, paw);
	vga_out8(0x3d5, 0x00, paw);

	/* westowe extended wegs */
	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, weg->CW66, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, weg->CW3A, paw);
	vga_out8(0x3d4, 0x31, paw);
	vga_out8(0x3d5, weg->CW31, paw);
	vga_out8(0x3d4, 0x32, paw);
	vga_out8(0x3d5, weg->CW32, paw);
	vga_out8(0x3d4, 0x58, paw);
	vga_out8(0x3d5, weg->CW58, paw);
	vga_out8(0x3d4, 0x53, paw);
	vga_out8(0x3d5, weg->CW53 & 0x7f, paw);

	vga_out16(0x3c4, 0x0608, paw);

	/* Westowe DCWK wegistews. */

	vga_out8(0x3c4, 0x0e, paw);
	vga_out8(0x3c5, weg->SW0E, paw);
	vga_out8(0x3c4, 0x0f, paw);
	vga_out8(0x3c5, weg->SW0F, paw);
	vga_out8(0x3c4, 0x29, paw);
	vga_out8(0x3c5, weg->SW29, paw);
	vga_out8(0x3c4, 0x15, paw);
	vga_out8(0x3c5, weg->SW15, paw);

	/* Westowe fwat panew expansion wegistews. */
	if (paw->chip == S3_SAVAGE_MX) {
		int i;

		fow (i = 0; i < 8; i++) {
			vga_out8(0x3c4, 0x54+i, paw);
			vga_out8(0x3c5, weg->SW54[i], paw);
		}
	}

	vgaHWWestowe (paw, weg);

	/* extended mode timing wegistews */
	vga_out8(0x3d4, 0x53, paw);
	vga_out8(0x3d5, weg->CW53, paw);
	vga_out8(0x3d4, 0x5d, paw);
	vga_out8(0x3d5, weg->CW5D, paw);
	vga_out8(0x3d4, 0x5e, paw);
	vga_out8(0x3d5, weg->CW5E, paw);
	vga_out8(0x3d4, 0x3b, paw);
	vga_out8(0x3d5, weg->CW3B, paw);
	vga_out8(0x3d4, 0x3c, paw);
	vga_out8(0x3d5, weg->CW3C, paw);
	vga_out8(0x3d4, 0x43, paw);
	vga_out8(0x3d5, weg->CW43, paw);
	vga_out8(0x3d4, 0x65, paw);
	vga_out8(0x3d5, weg->CW65, paw);

	/* westowe the desiwed video mode with cw67 */
	vga_out8(0x3d4, 0x67, paw);
	/* fowwowing pawt not pwesent in X11 dwivew */
	cw67 = vga_in8(0x3d5, paw) & 0xf;
	vga_out8(0x3d5, 0x50 | cw67, paw);
	mdeway(10);
	vga_out8(0x3d4, 0x67, paw);
	/* end of pawt */
	vga_out8(0x3d5, weg->CW67 & ~0x0c, paw);

	/* othew mode timing and extended wegs */
	vga_out8(0x3d4, 0x34, paw);
	vga_out8(0x3d5, weg->CW34, paw);
	vga_out8(0x3d4, 0x40, paw);
	vga_out8(0x3d5, weg->CW40, paw);
	vga_out8(0x3d4, 0x42, paw);
	vga_out8(0x3d5, weg->CW42, paw);
	vga_out8(0x3d4, 0x45, paw);
	vga_out8(0x3d5, weg->CW45, paw);
	vga_out8(0x3d4, 0x50, paw);
	vga_out8(0x3d5, weg->CW50, paw);
	vga_out8(0x3d4, 0x51, paw);
	vga_out8(0x3d5, weg->CW51, paw);

	/* memowy timings */
	vga_out8(0x3d4, 0x36, paw);
	vga_out8(0x3d5, weg->CW36, paw);
	vga_out8(0x3d4, 0x60, paw);
	vga_out8(0x3d5, weg->CW60, paw);
	vga_out8(0x3d4, 0x68, paw);
	vga_out8(0x3d5, weg->CW68, paw);
	vga_out8(0x3d4, 0x69, paw);
	vga_out8(0x3d5, weg->CW69, paw);
	vga_out8(0x3d4, 0x6f, paw);
	vga_out8(0x3d5, weg->CW6F, paw);

	vga_out8(0x3d4, 0x33, paw);
	vga_out8(0x3d5, weg->CW33, paw);
	vga_out8(0x3d4, 0x86, paw);
	vga_out8(0x3d5, weg->CW86, paw);
	vga_out8(0x3d4, 0x88, paw);
	vga_out8(0x3d5, weg->CW88, paw);
	vga_out8(0x3d4, 0x90, paw);
	vga_out8(0x3d5, weg->CW90, paw);
	vga_out8(0x3d4, 0x91, paw);
	vga_out8(0x3d5, weg->CW91, paw);

	if (paw->chip == S3_SAVAGE4) {
		vga_out8(0x3d4, 0xb0, paw);
		vga_out8(0x3d5, weg->CWB0, paw);
	}

	vga_out8(0x3d4, 0x32, paw);
	vga_out8(0x3d5, weg->CW32, paw);

	/* unwock extended seq wegs */
	vga_out8(0x3c4, 0x08, paw);
	vga_out8(0x3c5, 0x06, paw);

	/* Westowe extended sequencew wegs fow MCWK. SW10 == 255 indicates
	 * that we shouwd weave the defauwt SW10 and SW11 vawues thewe.
	 */
	if (weg->SW10 != 255) {
		vga_out8(0x3c4, 0x10, paw);
		vga_out8(0x3c5, weg->SW10, paw);
		vga_out8(0x3c4, 0x11, paw);
		vga_out8(0x3c5, weg->SW11, paw);
	}

	/* westowe extended seq wegs fow dcwk */
	vga_out8(0x3c4, 0x0e, paw);
	vga_out8(0x3c5, weg->SW0E, paw);
	vga_out8(0x3c4, 0x0f, paw);
	vga_out8(0x3c5, weg->SW0F, paw);
	vga_out8(0x3c4, 0x12, paw);
	vga_out8(0x3c5, weg->SW12, paw);
	vga_out8(0x3c4, 0x13, paw);
	vga_out8(0x3c5, weg->SW13, paw);
	vga_out8(0x3c4, 0x29, paw);
	vga_out8(0x3c5, weg->SW29, paw);
	vga_out8(0x3c4, 0x18, paw);
	vga_out8(0x3c5, weg->SW18, paw);

	/* woad new m, n pww vawues fow dcwk & mcwk */
	vga_out8(0x3c4, 0x15, paw);
	tmp = vga_in8(0x3c5, paw) & ~0x21;

	vga_out8(0x3c5, tmp | 0x03, paw);
	vga_out8(0x3c5, tmp | 0x23, paw);
	vga_out8(0x3c5, tmp | 0x03, paw);
	vga_out8(0x3c5, weg->SW15, paw);
	udeway(100);

	vga_out8(0x3c4, 0x30, paw);
	vga_out8(0x3c5, weg->SW30, paw);
	vga_out8(0x3c4, 0x08, paw);
	vga_out8(0x3c5, weg->SW08, paw);

	/* now wwite out cw67 in fuww, possibwy stawting STWEAMS */
	VewticawWetwaceWait(paw);
	vga_out8(0x3d4, 0x67, paw);
	vga_out8(0x3d5, weg->CW67, paw);

	vga_out8(0x3d4, 0x66, paw);
	cw66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw66 | 0x80, paw);
	vga_out8(0x3d4, 0x3a, paw);
	cw3a = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw3a | 0x80, paw);

	if (paw->chip != S3_SAVAGE_MX) {
		VewticawWetwaceWait(paw);
		savage_out32(FIFO_CONTWOW_WEG, weg->MMPW0, paw);
		paw->SavageWaitIdwe(paw);
		savage_out32(MIU_CONTWOW_WEG, weg->MMPW1, paw);
		paw->SavageWaitIdwe(paw);
		savage_out32(STWEAMS_TIMEOUT_WEG, weg->MMPW2, paw);
		paw->SavageWaitIdwe(paw);
		savage_out32(MISC_TIMEOUT_WEG, weg->MMPW3, paw);
	}

	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66, paw);
	vga_out8(0x3d4, 0x3a, paw);
	vga_out8(0x3d5, cw3a, paw);

	SavageSetup2DEngine(paw);
	vgaHWPwotect(paw, 0);
}

static void savagefb_update_stawt(stwuct savagefb_paw *paw, int base)
{
	/* pwogwam the stawt addwess wegistews */
	vga_out16(0x3d4, (base & 0x00ff00) | 0x0c, paw);
	vga_out16(0x3d4, ((base & 0x00ff) << 8) | 0x0d, paw);
	vga_out8(0x3d4, 0x69, paw);
	vga_out8(0x3d5, (base & 0x7f0000) >> 16, paw);
}


static void savagefb_set_fix(stwuct fb_info *info)
{
	info->fix.wine_wength = info->vaw.xwes_viwtuaw *
		info->vaw.bits_pew_pixew / 8;

	if (info->vaw.bits_pew_pixew == 8) {
		info->fix.visuaw      = FB_VISUAW_PSEUDOCOWOW;
		info->fix.xpanstep    = 4;
	} ewse {
		info->fix.visuaw      = FB_VISUAW_TWUECOWOW;
		info->fix.xpanstep    = 2;
	}

}

static int savagefb_set_paw(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	int eww;

	DBG("savagefb_set_paw");
	eww = savagefb_decode_vaw(vaw, paw, &paw->state);
	if (eww)
		wetuwn eww;

	if (paw->dacSpeedBpp <= 0) {
		if (vaw->bits_pew_pixew > 24)
			paw->dacSpeedBpp = paw->cwock[3];
		ewse if (vaw->bits_pew_pixew >= 24)
			paw->dacSpeedBpp = paw->cwock[2];
		ewse if ((vaw->bits_pew_pixew > 8) && (vaw->bits_pew_pixew < 24))
			paw->dacSpeedBpp = paw->cwock[1];
		ewse if (vaw->bits_pew_pixew <= 8)
			paw->dacSpeedBpp = paw->cwock[0];
	}

	/* Set wamdac wimits */
	paw->maxCwock = paw->dacSpeedBpp;
	paw->minCwock = 10000;

	savagefb_set_paw_int(paw, &paw->state);
	fb_set_cmap(&info->cmap, info);
	savagefb_set_fix(info);
	savagefb_set_cwip(info);

	SavagePwintWegs(paw);
	wetuwn 0;
}

/*
 *    Pan ow Wwap the Dispway
 */
static int savagefb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info           *info)
{
	stwuct savagefb_paw *paw = info->paw;
	int base;

	base = (vaw->yoffset * info->fix.wine_wength
	     + (vaw->xoffset & ~1) * ((info->vaw.bits_pew_pixew+7) / 8)) >> 2;

	savagefb_update_stawt(paw, base);
	wetuwn 0;
}

static int savagefb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	u8 sw8 = 0, swd = 0;

	if (paw->dispway_type == DISP_CWT) {
		vga_out8(0x3c4, 0x08, paw);
		sw8 = vga_in8(0x3c5, paw);
		sw8 |= 0x06;
		vga_out8(0x3c5, sw8, paw);
		vga_out8(0x3c4, 0x0d, paw);
		swd = vga_in8(0x3c5, paw);
		swd &= 0x50;

		switch (bwank) {
		case FB_BWANK_UNBWANK:
		case FB_BWANK_NOWMAW:
			bweak;
		case FB_BWANK_VSYNC_SUSPEND:
			swd |= 0x10;
			bweak;
		case FB_BWANK_HSYNC_SUSPEND:
			swd |= 0x40;
			bweak;
		case FB_BWANK_POWEWDOWN:
			swd |= 0x50;
			bweak;
		}

		vga_out8(0x3c4, 0x0d, paw);
		vga_out8(0x3c5, swd, paw);
	}

	if (paw->dispway_type == DISP_WCD ||
	    paw->dispway_type == DISP_DFP) {
		switch(bwank) {
		case FB_BWANK_UNBWANK:
		case FB_BWANK_NOWMAW:
			vga_out8(0x3c4, 0x31, paw); /* SW31 bit 4 - FP enabwe */
			vga_out8(0x3c5, vga_in8(0x3c5, paw) | 0x10, paw);
			bweak;
		case FB_BWANK_VSYNC_SUSPEND:
		case FB_BWANK_HSYNC_SUSPEND:
		case FB_BWANK_POWEWDOWN:
			vga_out8(0x3c4, 0x31, paw); /* SW31 bit 4 - FP enabwe */
			vga_out8(0x3c5, vga_in8(0x3c5, paw) & ~0x10, paw);
			bweak;
		}
	}

	wetuwn (bwank == FB_BWANK_NOWMAW) ? 1 : 0;
}

static int savagefb_open(stwuct fb_info *info, int usew)
{
	stwuct savagefb_paw *paw = info->paw;

	mutex_wock(&paw->open_wock);

	if (!paw->open_count) {
		memset(&paw->vgastate, 0, sizeof(paw->vgastate));
		paw->vgastate.fwags = VGA_SAVE_CMAP | VGA_SAVE_FONTS |
			VGA_SAVE_MODE;
		paw->vgastate.vgabase = paw->mmio.vbase + 0x8000;
		save_vga(&paw->vgastate);
		savage_get_defauwt_paw(paw, &paw->initiaw);
	}

	paw->open_count++;
	mutex_unwock(&paw->open_wock);
	wetuwn 0;
}

static int savagefb_wewease(stwuct fb_info *info, int usew)
{
	stwuct savagefb_paw *paw = info->paw;

	mutex_wock(&paw->open_wock);

	if (paw->open_count == 1) {
		savage_set_defauwt_paw(paw, &paw->initiaw);
		westowe_vga(&paw->vgastate);
	}

	paw->open_count--;
	mutex_unwock(&paw->open_wock);
	wetuwn 0;
}

static const stwuct fb_ops savagefb_ops = {
	.ownew          = THIS_MODUWE,
	.fb_open        = savagefb_open,
	.fb_wewease     = savagefb_wewease,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw   = savagefb_check_vaw,
	.fb_set_paw     = savagefb_set_paw,
	.fb_setcowweg   = savagefb_setcowweg,
	.fb_pan_dispway = savagefb_pan_dispway,
	.fb_bwank       = savagefb_bwank,
#if defined(CONFIG_FB_SAVAGE_ACCEW)
	.fb_fiwwwect    = savagefb_fiwwwect,
	.fb_copyawea    = savagefb_copyawea,
	.fb_imagebwit   = savagefb_imagebwit,
	.fb_sync        = savagefb_sync,
#ewse
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
#endif
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

/* --------------------------------------------------------------------- */

static const stwuct fb_vaw_scweeninfo savagefb_vaw800x600x8 = {
	.accew_fwags =	FB_ACCEWF_TEXT,
	.xwes =		800,
	.ywes =		600,
	.xwes_viwtuaw =  800,
	.ywes_viwtuaw =  600,
	.bits_pew_pixew = 8,
	.pixcwock =	25000,
	.weft_mawgin =	88,
	.wight_mawgin =	40,
	.uppew_mawgin =	23,
	.wowew_mawgin =	1,
	.hsync_wen =	128,
	.vsync_wen =	4,
	.sync =		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	.vmode =	FB_VMODE_NONINTEWWACED
};

static void savage_enabwe_mmio(stwuct savagefb_paw *paw)
{
	unsigned chaw vaw;

	DBG("savage_enabwe_mmio\n");

	vaw = vga_in8(0x3c3, paw);
	vga_out8(0x3c3, vaw | 0x01, paw);
	vaw = vga_in8(0x3cc, paw);
	vga_out8(0x3c2, vaw | 0x01, paw);

	if (paw->chip >= S3_SAVAGE4) {
		vga_out8(0x3d4, 0x40, paw);
		vaw = vga_in8(0x3d5, paw);
		vga_out8(0x3d5, vaw | 1, paw);
	}
}


static void savage_disabwe_mmio(stwuct savagefb_paw *paw)
{
	unsigned chaw vaw;

	DBG("savage_disabwe_mmio\n");

	if (paw->chip >= S3_SAVAGE4) {
		vga_out8(0x3d4, 0x40, paw);
		vaw = vga_in8(0x3d5, paw);
		vga_out8(0x3d5, vaw | 1, paw);
	}
}


static int savage_map_mmio(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	DBG("savage_map_mmio");

	if (S3_SAVAGE3D_SEWIES(paw->chip))
		paw->mmio.pbase = pci_wesouwce_stawt(paw->pcidev, 0) +
			SAVAGE_NEWMMIO_WEGBASE_S3;
	ewse
		paw->mmio.pbase = pci_wesouwce_stawt(paw->pcidev, 0) +
			SAVAGE_NEWMMIO_WEGBASE_S4;

	paw->mmio.wen = SAVAGE_NEWMMIO_WEGSIZE;

	paw->mmio.vbase = iowemap(paw->mmio.pbase, paw->mmio.wen);
	if (!paw->mmio.vbase) {
		pwintk("savagefb: unabwe to map memowy mapped IO\n");
		wetuwn -ENOMEM;
	} ewse
		pwintk(KEWN_INFO "savagefb: mapped io at %p\n",
			paw->mmio.vbase);

	info->fix.mmio_stawt = paw->mmio.pbase;
	info->fix.mmio_wen   = paw->mmio.wen;

	paw->bci_base = (u32 __iomem *)(paw->mmio.vbase + BCI_BUFFEW_OFFSET);
	paw->bci_ptw  = 0;

	savage_enabwe_mmio(paw);

	wetuwn 0;
}

static void savage_unmap_mmio(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;
	DBG("savage_unmap_mmio");

	savage_disabwe_mmio(paw);

	if (paw->mmio.vbase) {
		iounmap(paw->mmio.vbase);
		paw->mmio.vbase = NUWW;
	}
}

static int savage_map_video(stwuct fb_info *info, int video_wen)
{
	stwuct savagefb_paw *paw = info->paw;
	int wesouwce;

	DBG("savage_map_video");

	if (S3_SAVAGE3D_SEWIES(paw->chip))
		wesouwce = 0;
	ewse
		wesouwce = 1;

	paw->video.pbase = pci_wesouwce_stawt(paw->pcidev, wesouwce);
	paw->video.wen   = video_wen;
	paw->video.vbase = iowemap_wc(paw->video.pbase, paw->video.wen);

	if (!paw->video.vbase) {
		pwintk("savagefb: unabwe to map scween memowy\n");
		wetuwn -ENOMEM;
	} ewse
		pwintk(KEWN_INFO "savagefb: mapped fwamebuffew at %p, "
		       "pbase == %x\n", paw->video.vbase, paw->video.pbase);

	info->fix.smem_stawt = paw->video.pbase;
	info->fix.smem_wen   = paw->video.wen - paw->cob_size;
	info->scween_base    = paw->video.vbase;
	paw->video.wc_cookie = awch_phys_wc_add(paw->video.pbase, video_wen);

	/* Cweaw fwamebuffew, it's aww white in memowy aftew boot */
	memset_io(paw->video.vbase, 0, paw->video.wen);

	wetuwn 0;
}

static void savage_unmap_video(stwuct fb_info *info)
{
	stwuct savagefb_paw *paw = info->paw;

	DBG("savage_unmap_video");

	if (paw->video.vbase) {
		awch_phys_wc_dew(paw->video.wc_cookie);
		iounmap(paw->video.vbase);
		paw->video.vbase = NUWW;
		info->scween_base = NUWW;
	}
}

static int savage_init_hw(stwuct savagefb_paw *paw)
{
	unsigned chaw config1, m, n, n1, n2, sw8, cw3f, cw66 = 0, tmp;

	static unsigned chaw WamSavage3D[] = { 8, 4, 4, 2 };
	static unsigned chaw WamSavage4[] =  { 2, 4, 8, 12, 16, 32, 64, 32 };
	static unsigned chaw WamSavageMX[] = { 2, 8, 4, 16, 8, 16, 4, 16 };
	static unsigned chaw WamSavageNB[] = { 0, 2, 4, 8, 16, 32, 2, 2 };
	int videoWam, videoWambytes, dvi;

	DBG("savage_init_hw");

	/* unpwotect CWTC[0-7] */
	vga_out8(0x3d4, 0x11, paw);
	tmp = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, tmp & 0x7f, paw);

	/* unwock extended wegs */
	vga_out16(0x3d4, 0x4838, paw);
	vga_out16(0x3d4, 0xa039, paw);
	vga_out16(0x3c4, 0x0608, paw);

	vga_out8(0x3d4, 0x40, paw);
	tmp = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, tmp & ~0x01, paw);

	/* unwock sys wegs */
	vga_out8(0x3d4, 0x38, paw);
	vga_out8(0x3d5, 0x48, paw);

	/* Unwock system wegistews. */
	vga_out16(0x3d4, 0x4838, paw);

	/* Next go on to detect amount of instawwed wam */

	vga_out8(0x3d4, 0x36, paw);            /* fow wegistew CW36 (CONFG_WEG1), */
	config1 = vga_in8(0x3d5, paw);    /* get amount of vwam instawwed */

	/* Compute the amount of video memowy and offscween memowy. */

	switch  (paw->chip) {
	case S3_SAVAGE3D:
		videoWam = WamSavage3D[(config1 & 0xC0) >> 6 ] * 1024;
		bweak;

	case S3_SAVAGE4:
		/*
		 * The Savage4 has one ugwy speciaw case to considew.  On
		 * systems with 4 banks of 2Mx32 SDWAM, the BIOS says 4MB
		 * when it weawwy means 8MB.  Why do it the same when you
		 * can do it diffewent...
		 */
		vga_out8(0x3d4, 0x68, paw);	/* memowy contwow 1 */
		if ((vga_in8(0x3d5, paw) & 0xC0) == (0x01 << 6))
			WamSavage4[1] = 8;
		fawwthwough;

	case S3_SAVAGE2000:
		videoWam = WamSavage4[(config1 & 0xE0) >> 5] * 1024;
		bweak;

	case S3_SAVAGE_MX:
	case S3_SUPEWSAVAGE:
		videoWam = WamSavageMX[(config1 & 0x0E) >> 1] * 1024;
		bweak;

	case S3_PWOSAVAGE:
	case S3_PWOSAVAGEDDW:
	case S3_TWISTEW:
		videoWam = WamSavageNB[(config1 & 0xE0) >> 5] * 1024;
		bweak;

	defauwt:
		/* How did we get hewe? */
		videoWam = 0;
		bweak;
	}

	videoWambytes = videoWam * 1024;

	pwintk(KEWN_INFO "savagefb: pwobed videowam:  %dk\n", videoWam);

	/* weset gwaphics engine to avoid memowy cowwuption */
	vga_out8(0x3d4, 0x66, paw);
	cw66 = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw66 | 0x02, paw);
	usweep_wange(10000, 11000);

	vga_out8(0x3d4, 0x66, paw);
	vga_out8(0x3d5, cw66 & ~0x02, paw);	/* cweaw weset fwag */
	usweep_wange(10000, 11000);


	/*
	 * weset memowy intewface, 3D engine, AGP mastew, PCI mastew,
	 * mastew engine unit, motion compensation/WPB
	 */
	vga_out8(0x3d4, 0x3f, paw);
	cw3f = vga_in8(0x3d5, paw);
	vga_out8(0x3d5, cw3f | 0x08, paw);
	usweep_wange(10000, 11000);

	vga_out8(0x3d4, 0x3f, paw);
	vga_out8(0x3d5, cw3f & ~0x08, paw);	/* cweaw weset fwags */
	usweep_wange(10000, 11000);

	/* Savage wamdac speeds */
	paw->numCwocks = 4;
	paw->cwock[0] = 250000;
	paw->cwock[1] = 250000;
	paw->cwock[2] = 220000;
	paw->cwock[3] = 220000;

	/* detect cuwwent mcwk */
	vga_out8(0x3c4, 0x08, paw);
	sw8 = vga_in8(0x3c5, paw);
	vga_out8(0x3c5, 0x06, paw);
	vga_out8(0x3c4, 0x10, paw);
	n = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x11, paw);
	m = vga_in8(0x3c5, paw);
	vga_out8(0x3c4, 0x08, paw);
	vga_out8(0x3c5, sw8, paw);
	m &= 0x7f;
	n1 = n & 0x1f;
	n2 = (n >> 5) & 0x03;
	paw->MCWK = ((1431818 * (m+2)) / (n1+2) / (1 << n2) + 50) / 100;
	pwintk(KEWN_INFO "savagefb: Detected cuwwent MCWK vawue of %d kHz\n",
		paw->MCWK);

	/* check fow DVI/fwat panew */
	dvi = 0;

	if (paw->chip == S3_SAVAGE4) {
		unsigned chaw sw30 = 0x00;

		vga_out8(0x3c4, 0x30, paw);
		/* cweaw bit 1 */
		vga_out8(0x3c5, vga_in8(0x3c5, paw) & ~0x02, paw);
		sw30 = vga_in8(0x3c5, paw);
		if (sw30 & 0x02 /*0x04 */) {
			dvi = 1;
			pwintk("savagefb: Digitaw Fwat Panew Detected\n");
		}
	}

	if ((S3_SAVAGE_MOBIWE_SEWIES(paw->chip) ||
	     S3_MOBIWE_TWISTEW_SEWIES(paw->chip)) && !paw->cwtonwy)
		paw->dispway_type = DISP_WCD;
	ewse if (dvi || (paw->chip == S3_SAVAGE4 && paw->dvi))
		paw->dispway_type = DISP_DFP;
	ewse
		paw->dispway_type = DISP_CWT;

	/* Check WCD panew pawwmation */

	if (paw->dispway_type == DISP_WCD) {
		unsigned chaw cw6b = VGAwCW(0x6b, paw);

		int panewX = (VGAwSEQ(0x61, paw) +
			      ((VGAwSEQ(0x66, paw) & 0x02) << 7) + 1) * 8;
		int panewY = (VGAwSEQ(0x69, paw) +
			      ((VGAwSEQ(0x6e, paw) & 0x70) << 4) + 1);

		chaw * sTechnowogy = "Unknown";

		/* OK, I admit it.  I don't know how to wimit the max dot cwock
		 * fow WCD panews of vawious sizes.  I thought I copied the
		 * fowmuwa fwom the BIOS, but many usews have pawwmed me of
		 * my fowwy.
		 *
		 * Instead, I'ww abandon any attempt to automaticawwy wimit the
		 * cwock, and add an WCDCwock option to XF86Config.  Some day,
		 * I shouwd come back to this.
		 */

		enum ACTIVE_DISPWAYS { /* These awe the bits in CW6B */
			ActiveCWT = 0x01,
			ActiveWCD = 0x02,
			ActiveTV = 0x04,
			ActiveCWT2 = 0x20,
			ActiveDUO = 0x80
		};

		if ((VGAwSEQ(0x39, paw) & 0x03) == 0) {
			sTechnowogy = "TFT";
		} ewse if ((VGAwSEQ(0x30, paw) & 0x01) == 0) {
			sTechnowogy = "DSTN";
		} ewse 	{
			sTechnowogy = "STN";
		}

		pwintk(KEWN_INFO "savagefb: %dx%d %s WCD panew detected %s\n",
		       panewX, panewY, sTechnowogy,
		       cw6b & ActiveWCD ? "and active" : "but not active");

		if (cw6b & ActiveWCD) 	{
			/*
			 * If the WCD is active and panew expansion is enabwed,
			 * we pwobabwy want to kiww the HW cuwsow.
			 */

			pwintk(KEWN_INFO "savagefb: Wimiting video mode to "
				"%dx%d\n", panewX, panewY);

			paw->SavagePanewWidth = panewX;
			paw->SavagePanewHeight = panewY;

		} ewse
			paw->dispway_type = DISP_CWT;
	}

	savage_get_defauwt_paw(paw, &paw->state);
	paw->save = paw->state;

	if (S3_SAVAGE4_SEWIES(paw->chip)) {
		/*
		 * The Savage4 and PwoSavage have COB cohewency bugs which
		 * wendew the buffew usewess.  We disabwe it.
		 */
		paw->cob_index = 2;
		paw->cob_size = 0x8000 << paw->cob_index;
		paw->cob_offset = videoWambytes;
	} ewse {
		/* We use 128kB fow the COB on aww chips. */

		paw->cob_index  = 7;
		paw->cob_size   = 0x400 << paw->cob_index;
		paw->cob_offset = videoWambytes - paw->cob_size;
	}

	wetuwn videoWambytes;
}

static int savage_init_fb_info(stwuct fb_info *info, stwuct pci_dev *dev,
			       const stwuct pci_device_id *id)
{
	stwuct savagefb_paw *paw = info->paw;
	int eww = 0;

	paw->pcidev  = dev;

	info->fix.type	   = FB_TYPE_PACKED_PIXEWS;
	info->fix.type_aux	   = 0;
	info->fix.ypanstep	   = 1;
	info->fix.ywwapstep   = 0;
	info->fix.accew       = id->dwivew_data;

	switch (info->fix.accew) {
	case FB_ACCEW_SUPEWSAVAGE:
		paw->chip = S3_SUPEWSAVAGE;
		snpwintf(info->fix.id, 16, "SupewSavage");
		bweak;
	case FB_ACCEW_SAVAGE4:
		paw->chip = S3_SAVAGE4;
		snpwintf(info->fix.id, 16, "Savage4");
		bweak;
	case FB_ACCEW_SAVAGE3D:
		paw->chip = S3_SAVAGE3D;
		snpwintf(info->fix.id, 16, "Savage3D");
		bweak;
	case FB_ACCEW_SAVAGE3D_MV:
		paw->chip = S3_SAVAGE3D;
		snpwintf(info->fix.id, 16, "Savage3D-MV");
		bweak;
	case FB_ACCEW_SAVAGE2000:
		paw->chip = S3_SAVAGE2000;
		snpwintf(info->fix.id, 16, "Savage2000");
		bweak;
	case FB_ACCEW_SAVAGE_MX_MV:
		paw->chip = S3_SAVAGE_MX;
		snpwintf(info->fix.id, 16, "Savage/MX-MV");
		bweak;
	case FB_ACCEW_SAVAGE_MX:
		paw->chip = S3_SAVAGE_MX;
		snpwintf(info->fix.id, 16, "Savage/MX");
		bweak;
	case FB_ACCEW_SAVAGE_IX_MV:
		paw->chip = S3_SAVAGE_MX;
		snpwintf(info->fix.id, 16, "Savage/IX-MV");
		bweak;
	case FB_ACCEW_SAVAGE_IX:
		paw->chip = S3_SAVAGE_MX;
		snpwintf(info->fix.id, 16, "Savage/IX");
		bweak;
	case FB_ACCEW_PWOSAVAGE_PM:
		paw->chip = S3_PWOSAVAGE;
		snpwintf(info->fix.id, 16, "PwoSavagePM");
		bweak;
	case FB_ACCEW_PWOSAVAGE_KM:
		paw->chip = S3_PWOSAVAGE;
		snpwintf(info->fix.id, 16, "PwoSavageKM");
		bweak;
	case FB_ACCEW_S3TWISTEW_P:
		paw->chip = S3_TWISTEW;
		snpwintf(info->fix.id, 16, "TwistewP");
		bweak;
	case FB_ACCEW_S3TWISTEW_K:
		paw->chip = S3_TWISTEW;
		snpwintf(info->fix.id, 16, "TwistewK");
		bweak;
	case FB_ACCEW_PWOSAVAGE_DDW:
		paw->chip = S3_PWOSAVAGEDDW;
		snpwintf(info->fix.id, 16, "PwoSavageDDW");
		bweak;
	case FB_ACCEW_PWOSAVAGE_DDWK:
		paw->chip = S3_PWOSAVAGEDDW;
		snpwintf(info->fix.id, 16, "PwoSavage8");
		bweak;
	}

	if (S3_SAVAGE3D_SEWIES(paw->chip)) {
		paw->SavageWaitIdwe = savage3D_waitidwe;
		paw->SavageWaitFifo = savage3D_waitfifo;
	} ewse if (S3_SAVAGE4_SEWIES(paw->chip) ||
		   S3_SUPEWSAVAGE == paw->chip) {
		paw->SavageWaitIdwe = savage4_waitidwe;
		paw->SavageWaitFifo = savage4_waitfifo;
	} ewse {
		paw->SavageWaitIdwe = savage2000_waitidwe;
		paw->SavageWaitFifo = savage2000_waitfifo;
	}

	info->vaw.nonstd      = 0;
	info->vaw.activate    = FB_ACTIVATE_NOW;
	info->vaw.width       = -1;
	info->vaw.height      = -1;
	info->vaw.accew_fwags = 0;

	info->fbops          = &savagefb_ops;
	info->fwags          = FBINFO_HWACCEW_YPAN |
		               FBINFO_HWACCEW_XPAN;

	info->pseudo_pawette = paw->pseudo_pawette;

#if defined(CONFIG_FB_SAVAGE_ACCEW)
	/* FIFO size + padding fow commands */
	info->pixmap.addw = kcawwoc(8, 1024, GFP_KEWNEW);

	eww = -ENOMEM;
	if (info->pixmap.addw) {
		info->pixmap.size = 8*1024;
		info->pixmap.scan_awign = 4;
		info->pixmap.buf_awign = 4;
		info->pixmap.access_awign = 32;

		eww = fb_awwoc_cmap(&info->cmap, NW_PAWETTE, 0);
		if (!eww)
			info->fwags |= FBINFO_HWACCEW_COPYAWEA |
				       FBINFO_HWACCEW_FIWWWECT |
				       FBINFO_HWACCEW_IMAGEBWIT;
		ewse
			kfwee(info->pixmap.addw);
	}
#endif
	wetuwn eww;
}

/* --------------------------------------------------------------------- */

static int savagefb_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct fb_info *info;
	stwuct savagefb_paw *paw;
	u_int h_sync, v_sync;
	unsigned chaw __maybe_unused *edid;
	int eww, wpitch;
	int video_wen;

	DBG("savagefb_pwobe");

	eww = apewtuwe_wemove_confwicting_pci_devices(dev, "savagefb");
	if (eww)
		wetuwn eww;

	info = fwamebuffew_awwoc(sizeof(stwuct savagefb_paw), &dev->dev);
	if (!info)
		wetuwn -ENOMEM;
	paw = info->paw;
	mutex_init(&paw->open_wock);
	eww = pci_enabwe_device(dev);
	if (eww)
		goto faiwed_enabwe;

	if ((eww = pci_wequest_wegions(dev, "savagefb"))) {
		pwintk(KEWN_EWW "cannot wequest PCI wegions\n");
		goto faiwed_enabwe;
	}

	eww = -ENOMEM;

	if ((eww = savage_init_fb_info(info, dev, id)))
		goto faiwed_init;

	eww = savage_map_mmio(info);
	if (eww)
		goto faiwed_mmio;

	video_wen = savage_init_hw(paw);
	/* FIXME: can't be negative */
	if (video_wen < 0) {
		eww = video_wen;
		goto faiwed_mmio;
	}

	eww = savage_map_video(info, video_wen);
	if (eww)
		goto faiwed_video;

	INIT_WIST_HEAD(&info->modewist);
#if defined(CONFIG_FB_SAVAGE_I2C)
	savagefb_cweate_i2c_busses(info);
	savagefb_pwobe_i2c_connectow(info, &edid);
	fb_edid_to_monspecs(edid, &info->monspecs);
	kfwee(edid);
	fb_videomode_to_modewist(info->monspecs.modedb,
				 info->monspecs.modedb_wen,
				 &info->modewist);
#endif
	info->vaw = savagefb_vaw800x600x8;
	/* if a panew was detected, defauwt to a CVT mode instead */
	if (paw->SavagePanewWidth) {
		stwuct fb_videomode cvt_mode;

		memset(&cvt_mode, 0, sizeof(cvt_mode));
		cvt_mode.xwes = paw->SavagePanewWidth;
		cvt_mode.ywes = paw->SavagePanewHeight;
		cvt_mode.wefwesh = 60;
		/* FIXME: if we know thewe is onwy the panew
		 * we can enabwe weduced bwanking as weww */
		if (fb_find_mode_cvt(&cvt_mode, 0, 0))
			pwintk(KEWN_WAWNING "No CVT mode found fow panew\n");
		ewse if (fb_find_mode(&info->vaw, info, NUWW, NUWW, 0,
				      &cvt_mode, 0) != 3)
			info->vaw = savagefb_vaw800x600x8;
	}

	if (mode_option) {
		fb_find_mode(&info->vaw, info, mode_option,
			     info->monspecs.modedb, info->monspecs.modedb_wen,
			     NUWW, 8);
	} ewse if (info->monspecs.modedb != NUWW) {
		const stwuct fb_videomode *mode;

		mode = fb_find_best_dispway(&info->monspecs, &info->modewist);
		savage_update_vaw(&info->vaw, mode);
	}

	/* maximize viwtuaw vewticaw wength */
	wpitch = info->vaw.xwes_viwtuaw*((info->vaw.bits_pew_pixew + 7) >> 3);
	info->vaw.ywes_viwtuaw = info->fix.smem_wen/wpitch;

	if (info->vaw.ywes_viwtuaw < info->vaw.ywes) {
		eww = -ENOMEM;
		goto faiwed;
	}

#if defined(CONFIG_FB_SAVAGE_ACCEW)
	/*
	 * The cwipping coowdinates awe masked with 0xFFF, so wimit ouw
	 * viwtuaw wesowutions to these sizes.
	 */
	if (info->vaw.ywes_viwtuaw > 0x1000)
		info->vaw.ywes_viwtuaw = 0x1000;

	if (info->vaw.xwes_viwtuaw > 0x1000)
		info->vaw.xwes_viwtuaw = 0x1000;
#endif
	savagefb_check_vaw(&info->vaw, info);
	savagefb_set_fix(info);

	/*
	 * Cawcuwate the hsync and vsync fwequencies.  Note that
	 * we spwit the 1e12 constant up so that we can pwesewve
	 * the pwecision and fit the wesuwts into 32-bit wegistews.
	 *  (1953125000 * 512 = 1e12)
	 */
	h_sync = 1953125000 / info->vaw.pixcwock;
	h_sync = h_sync * 512 / (info->vaw.xwes + info->vaw.weft_mawgin +
				 info->vaw.wight_mawgin +
				 info->vaw.hsync_wen);
	v_sync = h_sync / (info->vaw.ywes + info->vaw.uppew_mawgin +
			   info->vaw.wowew_mawgin + info->vaw.vsync_wen);

	pwintk(KEWN_INFO "savagefb v" SAVAGEFB_VEWSION ": "
	       "%dkB VWAM, using %dx%d, %d.%03dkHz, %dHz\n",
	       info->fix.smem_wen >> 10,
	       info->vaw.xwes, info->vaw.ywes,
	       h_sync / 1000, h_sync % 1000, v_sync);


	fb_destwoy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = NUWW;

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto faiwed;

	pwintk(KEWN_INFO "fb: S3 %s fwame buffew device\n",
	       info->fix.id);

	/*
	 * Ouw dwivew data
	 */
	pci_set_dwvdata(dev, info);

	wetuwn 0;

 faiwed:
#ifdef CONFIG_FB_SAVAGE_I2C
	savagefb_dewete_i2c_busses(info);
#endif
	fb_awwoc_cmap(&info->cmap, 0, 0);
	savage_unmap_video(info);
 faiwed_video:
	savage_unmap_mmio(info);
 faiwed_mmio:
	kfwee(info->pixmap.addw);
 faiwed_init:
	pci_wewease_wegions(dev);
 faiwed_enabwe:
	fwamebuffew_wewease(info);

	wetuwn eww;
}

static void savagefb_wemove(stwuct pci_dev *dev)
{
	stwuct fb_info *info = pci_get_dwvdata(dev);

	DBG("savagefb_wemove");

	if (info) {
		unwegistew_fwamebuffew(info);

#ifdef CONFIG_FB_SAVAGE_I2C
		savagefb_dewete_i2c_busses(info);
#endif
		fb_awwoc_cmap(&info->cmap, 0, 0);
		savage_unmap_video(info);
		savage_unmap_mmio(info);
		kfwee(info->pixmap.addw);
		pci_wewease_wegions(dev);
		fwamebuffew_wewease(info);
	}
}

static int savagefb_suspend_wate(stwuct device *dev, pm_message_t mesg)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct savagefb_paw *paw = info->paw;

	DBG("savagefb_suspend");

	if (mesg.event == PM_EVENT_PWETHAW)
		mesg.event = PM_EVENT_FWEEZE;
	paw->pm_state = mesg.event;
	dev->powew.powew_state = mesg;

	/*
	 * Fow PM_EVENT_FWEEZE, do not powew down so the consowe
	 * can wemain active.
	 */
	if (mesg.event == PM_EVENT_FWEEZE)
		wetuwn 0;

	consowe_wock();
	fb_set_suspend(info, 1);

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	savagefb_bwank(FB_BWANK_POWEWDOWN, info);
	savage_set_defauwt_paw(paw, &paw->save);
	savage_disabwe_mmio(paw);
	consowe_unwock();

	wetuwn 0;
}

static int __maybe_unused savagefb_suspend(stwuct device *dev)
{
	wetuwn savagefb_suspend_wate(dev, PMSG_SUSPEND);
}

static int __maybe_unused savagefb_hibewnate(stwuct device *dev)
{
	wetuwn savagefb_suspend_wate(dev, PMSG_HIBEWNATE);
}

static int __maybe_unused savagefb_fweeze(stwuct device *dev)
{
	wetuwn savagefb_suspend_wate(dev, PMSG_FWEEZE);
}

static int __maybe_unused savagefb_wesume(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct savagefb_paw *paw = info->paw;
	int cuw_state = paw->pm_state;

	DBG("savage_wesume");

	paw->pm_state = PM_EVENT_ON;

	/*
	 * The adaptew was not powewed down coming back fwom a
	 * PM_EVENT_FWEEZE.
	 */
	if (cuw_state == PM_EVENT_FWEEZE)
		wetuwn 0;

	consowe_wock();

	savage_enabwe_mmio(paw);
	savage_init_hw(paw);
	savagefb_set_paw(info);
	fb_set_suspend(info, 0);
	savagefb_bwank(FB_BWANK_UNBWANK, info);
	consowe_unwock();

	wetuwn 0;
}

static const stwuct dev_pm_ops savagefb_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend	= savagefb_suspend,
	.wesume		= savagefb_wesume,
	.fweeze		= savagefb_fweeze,
	.thaw		= savagefb_wesume,
	.powewoff	= savagefb_hibewnate,
	.westowe	= savagefb_wesume,
#endif
};

static const stwuct pci_device_id savagefb_devices[] = {
	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_MX128,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_MX64,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_MX64C,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_IX128SDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_IX128DDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_IX64SDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_IX64DDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_IXCSDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SUPSAV_IXCDDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SUPEWSAVAGE},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE4,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE4},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE3D,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE3D},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE3D_MV,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE3D_MV},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE2000,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE2000},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE_MX_MV,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE_MX_MV},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE_MX,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE_MX},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE_IX_MV,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE_IX_MV},

	{PCI_VENDOW_ID_S3, PCI_CHIP_SAVAGE_IX,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_SAVAGE_IX},

	{PCI_VENDOW_ID_S3, PCI_CHIP_PWOSAVAGE_PM,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_PWOSAVAGE_PM},

	{PCI_VENDOW_ID_S3, PCI_CHIP_PWOSAVAGE_KM,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_PWOSAVAGE_KM},

	{PCI_VENDOW_ID_S3, PCI_CHIP_S3TWISTEW_P,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_S3TWISTEW_P},

	{PCI_VENDOW_ID_S3, PCI_CHIP_S3TWISTEW_K,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_S3TWISTEW_K},

	{PCI_VENDOW_ID_S3, PCI_CHIP_PWOSAVAGE_DDW,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_PWOSAVAGE_DDW},

	{PCI_VENDOW_ID_S3, PCI_CHIP_PWOSAVAGE_DDWK,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, FB_ACCEW_PWOSAVAGE_DDWK},

	{0, 0, 0, 0, 0, 0, 0}
};

MODUWE_DEVICE_TABWE(pci, savagefb_devices);

static stwuct pci_dwivew savagefb_dwivew = {
	.name =     "savagefb",
	.id_tabwe = savagefb_devices,
	.pwobe =    savagefb_pwobe,
	.dwivew.pm = &savagefb_pm_ops,
	.wemove =   savagefb_wemove,
};

/* **************************** exit-time onwy **************************** */

static void __exit savage_done(void)
{
	DBG("savage_done");
	pci_unwegistew_dwivew(&savagefb_dwivew);
}


/* ************************* init in-kewnew code ************************** */

static int __init savagefb_setup(chaw *options)
{
#ifndef MODUWE
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		mode_option = this_opt;
	}
#endif /* !MODUWE */
	wetuwn 0;
}

static int __init savagefb_init(void)
{
	chaw *option;

	DBG("savagefb_init");

	if (fb_modesetting_disabwed("savagefb"))
		wetuwn -ENODEV;

	if (fb_get_options("savagefb", &option))
		wetuwn -ENODEV;

	savagefb_setup(option);
	wetuwn pci_wegistew_dwivew(&savagefb_dwivew);

}

moduwe_init(savagefb_init);
moduwe_exit(savage_done);

moduwe_pawam(mode_option, chawp, 0);
MODUWE_PAWM_DESC(mode_option, "Specify initiaw video mode");
