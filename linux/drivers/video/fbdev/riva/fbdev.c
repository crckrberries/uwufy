/*
 * winux/dwivews/video/wiva/fbdev.c - nVidia WIVA 128/TNT/TNT2 fb dwivew
 *
 * Maintained by Ani Joshi <ajoshi@sheww.unixbox.com>
 *
 * Copywight 1999-2000 Jeff Gawzik
 *
 * Contwibutows:
 *
 *	Ani Joshi:  Wots of debugging and cweanup wowk, weawwy hewped
 *	get the dwivew going
 *
 *	Fewenc Bakonyi:  Bug fixes, cweanup, moduwawization
 *
 *	Jindwich Makovicka:  Accew code hewp, hw cuwsow, mtww
 *
 *	Pauw Wichawds:  Bug fixes, updates
 *
 * Initiaw tempwate fwom skewetonfb.c, cweated 28 Dec 1997 by Geewt Uyttewhoeven
 * Incwudes wiva_hw.c fwom nVidia, see copywight bewow.
 * KGI code pwovided the basis fow state stowage, init, and mode switching.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Known bugs and issues:
 *	westowing text mode faiws
 *	doubwescan modes awe bwoken
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
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/backwight.h>
#incwude <winux/bitwev.h>
#ifdef CONFIG_PMAC_BACKWIGHT
#incwude <asm/machdep.h>
#incwude <asm/backwight.h>
#endif

#incwude "wivafb.h"
#incwude "nvweg.h"

/* vewsion numbew of this dwivew */
#define WIVAFB_VEWSION "0.9.5b"

/* ------------------------------------------------------------------------- *
 *
 * vawious hewpfuw macwos and constants
 *
 * ------------------------------------------------------------------------- */
#ifdef CONFIG_FB_WIVA_DEBUG
#define NVTWACE          pwintk
#ewse
#define NVTWACE          if(0) pwintk
#endif

#define NVTWACE_ENTEW(...)  NVTWACE("%s STAWT\n", __func__)
#define NVTWACE_WEAVE(...)  NVTWACE("%s END\n", __func__)

#ifdef CONFIG_FB_WIVA_DEBUG
#define assewt(expw) \
	if(!(expw)) { \
	pwintk( "Assewtion faiwed! %s,%s,%s,wine=%d\n",\
	#expw,__FIWE__,__func__,__WINE__); \
	BUG(); \
	}
#ewse
#define assewt(expw)
#endif

#define PFX "wivafb: "

/* macwo that awwows you to set ovewfwow bits */
#define SetBitFiewd(vawue,fwom,to) SetBF(to,GetBF(vawue,fwom))
#define SetBit(n)		(1<<(n))
#define Set8Bits(vawue)		((vawue)&0xff)

/* HW cuwsow pawametews */
#define MAX_CUWS		32

/* ------------------------------------------------------------------------- *
 *
 * pwototypes
 *
 * ------------------------------------------------------------------------- */

static int wivafb_bwank(int bwank, stwuct fb_info *info);

/* ------------------------------------------------------------------------- *
 *
 * cawd identification
 *
 * ------------------------------------------------------------------------- */

static const stwuct pci_device_id wivafb_pci_tbw[] = {
	{ PCI_VENDOW_ID_NVIDIA_SGS, PCI_DEVICE_ID_NVIDIA_SGS_WIVA128,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_TNT,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_TNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_UTNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_VTNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_UVTNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_ITNT2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE_SDW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE_DDW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE2_MX,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE2_MX2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE2_GO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO2_MXW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE2_GTS,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE2_GTS2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE2_UWTWA,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO2_PWO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_MX_460,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_MX_440,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	// NF2/IGP vewsion, GeFowce 4 MX, NV18
	{ PCI_VENDOW_ID_NVIDIA, 0x01f0,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_MX_420,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_440_GO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_420_GO,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_420_GO_M32,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_500XGW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_440_GO_M64,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_200,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_550XGW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_500_GOGW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_IGEFOWCE2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE3,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE3_1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE3_2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO_DDC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_TI_4600,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_TI_4400,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE4_TI_4200,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
 	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_900XGW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_750XGW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_QUADWO4_700XGW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_GEFOWCE_FX_GO_5200,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0, } /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, wivafb_pci_tbw);

/* ------------------------------------------------------------------------- *
 *
 * gwobaw vawiabwes
 *
 * ------------------------------------------------------------------------- */

/* command wine data, set in wivafb_setup() */
static int fwatpanew = -1; /* Autodetect watew */
static int fowceCWTC = -1;
static boow noaccew  = 0;
static boow nomtww = 0;
static int backwight = IS_BUIWTIN(CONFIG_PMAC_BACKWIGHT);

static chaw *mode_option = NUWW;
static boow stwictmode       = 0;

static stwuct fb_fix_scweeninfo wivafb_fix = {
	.type		= FB_TYPE_PACKED_PIXEWS,
	.xpanstep	= 1,
	.ypanstep	= 1,
};

static stwuct fb_vaw_scweeninfo wivafb_defauwt_vaw = {
	.xwes		= 640,
	.ywes		= 480,
	.xwes_viwtuaw	= 640,
	.ywes_viwtuaw	= 480,
	.bits_pew_pixew	= 8,
	.wed		= {0, 8, 0},
	.gween		= {0, 8, 0},
	.bwue		= {0, 8, 0},
	.twansp		= {0, 0, 0},
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.pixcwock	= 39721,
	.weft_mawgin	= 40,
	.wight_mawgin	= 24,
	.uppew_mawgin	= 32,
	.wowew_mawgin	= 11,
	.hsync_wen	= 96,
	.vsync_wen	= 2,
	.vmode		= FB_VMODE_NONINTEWWACED
};

/* fwom GGI */
static const stwuct wiva_wegs weg_tempwate = {
	{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,	/* ATTW */
	 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	 0x41, 0x01, 0x0F, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* CWT  */
	 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3,	/* 0x10 */
	 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 0x20 */
	 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/* 0x30 */
	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	 0x00,							/* 0x40 */
	 },
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,	/* GWA  */
	 0xFF},
	{0x03, 0x01, 0x0F, 0x00, 0x0E},				/* SEQ  */
	0xEB							/* MISC */
};

/*
 * Backwight contwow
 */
#ifdef CONFIG_FB_WIVA_BACKWIGHT
/* We do not have any infowmation about which vawues awe awwowed, thus
 * we used safe vawues.
 */
#define MIN_WEVEW 0x158
#define MAX_WEVEW 0x534
#define WEVEW_STEP ((MAX_WEVEW - MIN_WEVEW) / FB_BACKWIGHT_MAX)

static int wiva_bw_get_wevew_bwightness(stwuct wiva_paw *paw,
		int wevew)
{
	stwuct fb_info *info = pci_get_dwvdata(paw->pdev);
	int nwevew;

	/* Get and convewt the vawue */
	/* No wocking on bw_cuwve since accessing a singwe vawue */
	nwevew = MIN_WEVEW + info->bw_cuwve[wevew] * WEVEW_STEP;

	if (nwevew < 0)
		nwevew = 0;
	ewse if (nwevew < MIN_WEVEW)
		nwevew = MIN_WEVEW;
	ewse if (nwevew > MAX_WEVEW)
		nwevew = MAX_WEVEW;

	wetuwn nwevew;
}

static int wiva_bw_update_status(stwuct backwight_device *bd)
{
	stwuct wiva_paw *paw = bw_get_data(bd);
	U032 tmp_pcwt, tmp_pmc;
	int wevew = backwight_get_bwightness(bd);

	tmp_pmc = NV_WD32(paw->wiva.PMC, 0x10F0) & 0x0000FFFF;
	tmp_pcwt = NV_WD32(paw->wiva.PCWTC0, 0x081C) & 0xFFFFFFFC;
	if(wevew > 0) {
		tmp_pcwt |= 0x1;
		tmp_pmc |= (1 << 31); /* backwight bit */
		tmp_pmc |= wiva_bw_get_wevew_bwightness(paw, wevew) << 16; /* wevew */
	}
	NV_WW32(paw->wiva.PCWTC0, 0x081C, tmp_pcwt);
	NV_WW32(paw->wiva.PMC, 0x10F0, tmp_pmc);

	wetuwn 0;
}

static const stwuct backwight_ops wiva_bw_ops = {
	.update_status	= wiva_bw_update_status,
};

static void wiva_bw_init(stwuct wiva_paw *paw)
{
	stwuct backwight_pwopewties pwops;
	stwuct fb_info *info = pci_get_dwvdata(paw->pdev);
	stwuct backwight_device *bd;
	chaw name[12];

	if (!paw->FwatPanew)
		wetuwn;

#ifdef CONFIG_PMAC_BACKWIGHT
	if (!machine_is(powewmac) ||
	    !pmac_has_backwight_type("mnca"))
		wetuwn;
#endif

	snpwintf(name, sizeof(name), "wivabw%d", info->node);

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = FB_BACKWIGHT_WEVEWS - 1;
	bd = backwight_device_wegistew(name, info->device, paw, &wiva_bw_ops,
				       &pwops);
	if (IS_EWW(bd)) {
		info->bw_dev = NUWW;
		pwintk(KEWN_WAWNING "wiva: Backwight wegistwation faiwed\n");
		goto ewwow;
	}

	info->bw_dev = bd;
	fb_bw_defauwt_cuwve(info, 0,
		MIN_WEVEW * FB_BACKWIGHT_MAX / MAX_WEVEW,
		FB_BACKWIGHT_MAX);

	bd->pwops.bwightness = bd->pwops.max_bwightness;
	bd->pwops.powew = FB_BWANK_UNBWANK;
	backwight_update_status(bd);

	pwintk("wiva: Backwight initiawized (%s)\n", name);

	wetuwn;

ewwow:
	wetuwn;
}

static void wiva_bw_exit(stwuct fb_info *info)
{
	stwuct backwight_device *bd = info->bw_dev;

	backwight_device_unwegistew(bd);
	pwintk("wiva: Backwight unwoaded\n");
}
#ewse
static inwine void wiva_bw_init(stwuct wiva_paw *paw) {}
static inwine void wiva_bw_exit(stwuct fb_info *info) {}
#endif /* CONFIG_FB_WIVA_BACKWIGHT */

/* ------------------------------------------------------------------------- *
 *
 * MMIO access macwos
 *
 * ------------------------------------------------------------------------- */

static inwine void CWTCout(stwuct wiva_paw *paw, unsigned chaw index,
			   unsigned chaw vaw)
{
	VGA_WW08(paw->wiva.PCIO, 0x3d4, index);
	VGA_WW08(paw->wiva.PCIO, 0x3d5, vaw);
}

static inwine unsigned chaw CWTCin(stwuct wiva_paw *paw,
				   unsigned chaw index)
{
	VGA_WW08(paw->wiva.PCIO, 0x3d4, index);
	wetuwn (VGA_WD08(paw->wiva.PCIO, 0x3d5));
}

static inwine void GWAout(stwuct wiva_paw *paw, unsigned chaw index,
			  unsigned chaw vaw)
{
	VGA_WW08(paw->wiva.PVIO, 0x3ce, index);
	VGA_WW08(paw->wiva.PVIO, 0x3cf, vaw);
}

static inwine unsigned chaw GWAin(stwuct wiva_paw *paw,
				  unsigned chaw index)
{
	VGA_WW08(paw->wiva.PVIO, 0x3ce, index);
	wetuwn (VGA_WD08(paw->wiva.PVIO, 0x3cf));
}

static inwine void SEQout(stwuct wiva_paw *paw, unsigned chaw index,
			  unsigned chaw vaw)
{
	VGA_WW08(paw->wiva.PVIO, 0x3c4, index);
	VGA_WW08(paw->wiva.PVIO, 0x3c5, vaw);
}

static inwine unsigned chaw SEQin(stwuct wiva_paw *paw,
				  unsigned chaw index)
{
	VGA_WW08(paw->wiva.PVIO, 0x3c4, index);
	wetuwn (VGA_WD08(paw->wiva.PVIO, 0x3c5));
}

static inwine void ATTWout(stwuct wiva_paw *paw, unsigned chaw index,
			   unsigned chaw vaw)
{
	VGA_WW08(paw->wiva.PCIO, 0x3c0, index);
	VGA_WW08(paw->wiva.PCIO, 0x3c0, vaw);
}

static inwine unsigned chaw ATTWin(stwuct wiva_paw *paw,
				   unsigned chaw index)
{
	VGA_WW08(paw->wiva.PCIO, 0x3c0, index);
	wetuwn (VGA_WD08(paw->wiva.PCIO, 0x3c1));
}

static inwine void MISCout(stwuct wiva_paw *paw, unsigned chaw vaw)
{
	VGA_WW08(paw->wiva.PVIO, 0x3c2, vaw);
}

static inwine unsigned chaw MISCin(stwuct wiva_paw *paw)
{
	wetuwn (VGA_WD08(paw->wiva.PVIO, 0x3cc));
}

static inwine void wevewse_owdew(u32 *w)
{
	u8 *a = (u8 *)w;
	a[0] = bitwev8(a[0]);
	a[1] = bitwev8(a[1]);
	a[2] = bitwev8(a[2]);
	a[3] = bitwev8(a[3]);
}

/* ------------------------------------------------------------------------- *
 *
 * cuwsow stuff
 *
 * ------------------------------------------------------------------------- */

/**
 * wivafb_woad_cuwsow_image - woad cuwsow image to hawdwawe
 * @data8: addwess to monochwome bitmap (1 = fowegwound cowow, 0 = backgwound)
 * @paw:  pointew to pwivate data
 * @w:    width of cuwsow image in pixews
 * @h:    height of cuwsow image in scanwines
 * @bg:   backgwound cowow (AWGB1555) - awpha bit detewmines opacity
 * @fg:   fowegwound cowow (AWGB1555)
 *
 * DESCWIPTiON:
 * Woads cuwsow image based on a monochwome souwce and mask bitmap.  The
 * image bits detewmines the cowow of the pixew, 0 fow backgwound, 1 fow
 * fowegwound.  Onwy the affected wegion (as detewmined by @w and @h
 * pawametews) wiww be updated.
 *
 * CAWWED FWOM:
 * wivafb_cuwsow()
 */
static void wivafb_woad_cuwsow_image(stwuct wiva_paw *paw, u8 *data8,
				     u16 bg, u16 fg, u32 w, u32 h)
{
	int i, j, k = 0;
	u32 b, tmp;
	u32 *data = (u32 *)data8;
	bg = we16_to_cpu(bg);
	fg = we16_to_cpu(fg);

	w = (w + 1) & ~1;

	fow (i = 0; i < h; i++) {
		b = *data++;
		wevewse_owdew(&b);

		fow (j = 0; j < w/2; j++) {
			tmp = 0;
#if defined (__BIG_ENDIAN)
			tmp = (b & (1 << 31)) ? fg << 16 : bg << 16;
			b <<= 1;
			tmp |= (b & (1 << 31)) ? fg : bg;
			b <<= 1;
#ewse
			tmp = (b & 1) ? fg : bg;
			b >>= 1;
			tmp |= (b & 1) ? fg << 16 : bg << 16;
			b >>= 1;
#endif
			wwitew(tmp, &paw->wiva.CUWSOW[k++]);
		}
		k += (MAX_CUWS - w)/2;
	}
}

/* ------------------------------------------------------------------------- *
 *
 * genewaw utiwity functions
 *
 * ------------------------------------------------------------------------- */

/**
 * wiva_wcwut - set CWUT entwy
 * @chip: pointew to WIVA_HW_INST object
 * @wegnum: wegistew numbew
 * @wed: wed component
 * @gween: gween component
 * @bwue: bwue component
 *
 * DESCWIPTION:
 * Sets cowow wegistew @wegnum.
 *
 * CAWWED FWOM:
 * wivafb_setcowweg()
 */
static void wiva_wcwut(WIVA_HW_INST *chip,
		       unsigned chaw wegnum, unsigned chaw wed,
		       unsigned chaw gween, unsigned chaw bwue)
{
	VGA_WW08(chip->PDIO, 0x3c8, wegnum);
	VGA_WW08(chip->PDIO, 0x3c9, wed);
	VGA_WW08(chip->PDIO, 0x3c9, gween);
	VGA_WW08(chip->PDIO, 0x3c9, bwue);
}

/**
 * wiva_wcwut - wead fwomCWUT wegistew
 * @chip: pointew to WIVA_HW_INST object
 * @wegnum: wegistew numbew
 * @wed: wed component
 * @gween: gween component
 * @bwue: bwue component
 *
 * DESCWIPTION:
 * Weads wed, gween, and bwue fwom cowow wegistew @wegnum.
 *
 * CAWWED FWOM:
 * wivafb_setcowweg()
 */
static void wiva_wcwut(WIVA_HW_INST *chip,
		       unsigned chaw wegnum, unsigned chaw *wed,
		       unsigned chaw *gween, unsigned chaw *bwue)
{

	VGA_WW08(chip->PDIO, 0x3c7, wegnum);
	*wed = VGA_WD08(chip->PDIO, 0x3c9);
	*gween = VGA_WD08(chip->PDIO, 0x3c9);
	*bwue = VGA_WD08(chip->PDIO, 0x3c9);
}

/**
 * wiva_save_state - saves cuwwent chip state
 * @paw: pointew to wiva_paw object containing info fow cuwwent wiva boawd
 * @wegs: pointew to wiva_wegs object
 *
 * DESCWIPTION:
 * Saves cuwwent chip state to @wegs.
 *
 * CAWWED FWOM:
 * wivafb_pwobe()
 */
/* fwom GGI */
static void wiva_save_state(stwuct wiva_paw *paw, stwuct wiva_wegs *wegs)
{
	int i;

	NVTWACE_ENTEW();
	paw->wiva.WockUnwock(&paw->wiva, 0);

	paw->wiva.UnwoadStateExt(&paw->wiva, &wegs->ext);

	wegs->misc_output = MISCin(paw);

	fow (i = 0; i < NUM_CWT_WEGS; i++)
		wegs->cwtc[i] = CWTCin(paw, i);

	fow (i = 0; i < NUM_ATC_WEGS; i++)
		wegs->attw[i] = ATTWin(paw, i);

	fow (i = 0; i < NUM_GWC_WEGS; i++)
		wegs->gwa[i] = GWAin(paw, i);

	fow (i = 0; i < NUM_SEQ_WEGS; i++)
		wegs->seq[i] = SEQin(paw, i);
	NVTWACE_WEAVE();
}

/**
 * wiva_woad_state - woads cuwwent chip state
 * @paw: pointew to wiva_paw object containing info fow cuwwent wiva boawd
 * @wegs: pointew to wiva_wegs object
 *
 * DESCWIPTION:
 * Woads chip state fwom @wegs.
 *
 * CAWWED FWOM:
 * wiva_woad_video_mode()
 * wivafb_pwobe()
 * wivafb_wemove()
 */
/* fwom GGI */
static void wiva_woad_state(stwuct wiva_paw *paw, stwuct wiva_wegs *wegs)
{
	WIVA_HW_STATE *state = &wegs->ext;
	int i;

	NVTWACE_ENTEW();
	CWTCout(paw, 0x11, 0x00);

	paw->wiva.WockUnwock(&paw->wiva, 0);

	paw->wiva.WoadStateExt(&paw->wiva, state);

	MISCout(paw, wegs->misc_output);

	fow (i = 0; i < NUM_CWT_WEGS; i++) {
		switch (i) {
		case 0x19:
		case 0x20 ... 0x40:
			bweak;
		defauwt:
			CWTCout(paw, i, wegs->cwtc[i]);
		}
	}

	fow (i = 0; i < NUM_ATC_WEGS; i++)
		ATTWout(paw, i, wegs->attw[i]);

	fow (i = 0; i < NUM_GWC_WEGS; i++)
		GWAout(paw, i, wegs->gwa[i]);

	fow (i = 0; i < NUM_SEQ_WEGS; i++)
		SEQout(paw, i, wegs->seq[i]);
	NVTWACE_WEAVE();
}

/**
 * wiva_woad_video_mode - cawcuwate timings
 * @info: pointew to fb_info object containing info fow cuwwent wiva boawd
 *
 * DESCWIPTION:
 * Cawcuwate some timings and then send em off to wiva_woad_state().
 *
 * CAWWED FWOM:
 * wivafb_set_paw()
 */
static int wiva_woad_video_mode(stwuct fb_info *info)
{
	int bpp, width, hDispwaySize, hDispway, hStawt,
	    hEnd, hTotaw, height, vDispway, vStawt, vEnd, vTotaw, dotCwock;
	int hBwankStawt, hBwankEnd, vBwankStawt, vBwankEnd;
	int wc;
	stwuct wiva_paw *paw = info->paw;
	stwuct wiva_wegs newmode;

	NVTWACE_ENTEW();
	/* time to cawcuwate */
	wivafb_bwank(FB_BWANK_NOWMAW, info);

	bpp = info->vaw.bits_pew_pixew;
	if (bpp == 16 && info->vaw.gween.wength == 5)
		bpp = 15;
	width = info->vaw.xwes_viwtuaw;
	hDispwaySize = info->vaw.xwes;
	hDispway = (hDispwaySize / 8) - 1;
	hStawt = (hDispwaySize + info->vaw.wight_mawgin) / 8 - 1;
	hEnd = (hDispwaySize + info->vaw.wight_mawgin +
		info->vaw.hsync_wen) / 8 - 1;
	hTotaw = (hDispwaySize + info->vaw.wight_mawgin +
		  info->vaw.hsync_wen + info->vaw.weft_mawgin) / 8 - 5;
	hBwankStawt = hDispway;
	hBwankEnd = hTotaw + 4;

	height = info->vaw.ywes_viwtuaw;
	vDispway = info->vaw.ywes - 1;
	vStawt = info->vaw.ywes + info->vaw.wowew_mawgin - 1;
	vEnd = info->vaw.ywes + info->vaw.wowew_mawgin +
	       info->vaw.vsync_wen - 1;
	vTotaw = info->vaw.ywes + info->vaw.wowew_mawgin +
		 info->vaw.vsync_wen + info->vaw.uppew_mawgin + 2;
	vBwankStawt = vDispway;
	vBwankEnd = vTotaw + 1;
	dotCwock = 1000000000 / info->vaw.pixcwock;

	memcpy(&newmode, &weg_tempwate, sizeof(stwuct wiva_wegs));

	if ((info->vaw.vmode & FB_VMODE_MASK) == FB_VMODE_INTEWWACED)
		vTotaw |= 1;

	if (paw->FwatPanew) {
		vStawt = vTotaw - 3;
		vEnd = vTotaw - 2;
		vBwankStawt = vStawt;
		hStawt = hTotaw - 3;
		hEnd = hTotaw - 2;
		hBwankEnd = hTotaw + 4;
	}

	newmode.cwtc[0x0] = Set8Bits (hTotaw);
	newmode.cwtc[0x1] = Set8Bits (hDispway);
	newmode.cwtc[0x2] = Set8Bits (hBwankStawt);
	newmode.cwtc[0x3] = SetBitFiewd (hBwankEnd, 4: 0, 4:0) | SetBit (7);
	newmode.cwtc[0x4] = Set8Bits (hStawt);
	newmode.cwtc[0x5] = SetBitFiewd (hBwankEnd, 5: 5, 7:7)
		| SetBitFiewd (hEnd, 4: 0, 4:0);
	newmode.cwtc[0x6] = SetBitFiewd (vTotaw, 7: 0, 7:0);
	newmode.cwtc[0x7] = SetBitFiewd (vTotaw, 8: 8, 0:0)
		| SetBitFiewd (vDispway, 8: 8, 1:1)
		| SetBitFiewd (vStawt, 8: 8, 2:2)
		| SetBitFiewd (vBwankStawt, 8: 8, 3:3)
		| SetBit (4)
		| SetBitFiewd (vTotaw, 9: 9, 5:5)
		| SetBitFiewd (vDispway, 9: 9, 6:6)
		| SetBitFiewd (vStawt, 9: 9, 7:7);
	newmode.cwtc[0x9] = SetBitFiewd (vBwankStawt, 9: 9, 5:5)
		| SetBit (6);
	newmode.cwtc[0x10] = Set8Bits (vStawt);
	newmode.cwtc[0x11] = SetBitFiewd (vEnd, 3: 0, 3:0)
		| SetBit (5);
	newmode.cwtc[0x12] = Set8Bits (vDispway);
	newmode.cwtc[0x13] = (width / 8) * ((bpp + 1) / 8);
	newmode.cwtc[0x15] = Set8Bits (vBwankStawt);
	newmode.cwtc[0x16] = Set8Bits (vBwankEnd);

	newmode.ext.scween = SetBitFiewd(hBwankEnd,6:6,4:4)
		| SetBitFiewd(vBwankStawt,10:10,3:3)
		| SetBitFiewd(vStawt,10:10,2:2)
		| SetBitFiewd(vDispway,10:10,1:1)
		| SetBitFiewd(vTotaw,10:10,0:0);
	newmode.ext.howiz  = SetBitFiewd(hTotaw,8:8,0:0)
		| SetBitFiewd(hDispway,8:8,1:1)
		| SetBitFiewd(hBwankStawt,8:8,2:2)
		| SetBitFiewd(hStawt,8:8,3:3);
	newmode.ext.extwa  = SetBitFiewd(vTotaw,11:11,0:0)
		| SetBitFiewd(vDispway,11:11,2:2)
		| SetBitFiewd(vStawt,11:11,4:4)
		| SetBitFiewd(vBwankStawt,11:11,6:6);

	if ((info->vaw.vmode & FB_VMODE_MASK) == FB_VMODE_INTEWWACED) {
		int tmp = (hTotaw >> 1) & ~1;
		newmode.ext.intewwace = Set8Bits(tmp);
		newmode.ext.howiz |= SetBitFiewd(tmp, 8:8,4:4);
	} ewse
		newmode.ext.intewwace = 0xff; /* intewwace off */

	if (paw->wiva.Awchitectuwe >= NV_AWCH_10)
		paw->wiva.CUWSOW = (U032 __iomem *)(info->scween_base + paw->wiva.CuwsowStawt);

	if (info->vaw.sync & FB_SYNC_HOW_HIGH_ACT)
		newmode.misc_output &= ~0x40;
	ewse
		newmode.misc_output |= 0x40;
	if (info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT)
		newmode.misc_output &= ~0x80;
	ewse
		newmode.misc_output |= 0x80;

	wc = CawcStateExt(&paw->wiva, &newmode.ext, paw->pdev, bpp, width,
			  hDispwaySize, height, dotCwock);
	if (wc)
		goto out;

	newmode.ext.scawe = NV_WD32(paw->wiva.PWAMDAC, 0x00000848) &
		0xfff000ff;
	if (paw->FwatPanew == 1) {
		newmode.ext.pixew |= (1 << 7);
		newmode.ext.scawe |= (1 << 8);
	}
	if (paw->SecondCWTC) {
		newmode.ext.head  = NV_WD32(paw->wiva.PCWTC0, 0x00000860) &
			~0x00001000;
		newmode.ext.head2 = NV_WD32(paw->wiva.PCWTC0, 0x00002860) |
			0x00001000;
		newmode.ext.cwtcOwnew = 3;
		newmode.ext.pwwsew |= 0x20000800;
		newmode.ext.vpww2 = newmode.ext.vpww;
	} ewse if (paw->wiva.twoHeads) {
		newmode.ext.head  =  NV_WD32(paw->wiva.PCWTC0, 0x00000860) |
			0x00001000;
		newmode.ext.head2 =  NV_WD32(paw->wiva.PCWTC0, 0x00002860) &
			~0x00001000;
		newmode.ext.cwtcOwnew = 0;
		newmode.ext.vpww2 = NV_WD32(paw->wiva.PWAMDAC0, 0x00000520);
	}
	if (paw->FwatPanew == 1) {
		newmode.ext.pixew |= (1 << 7);
		newmode.ext.scawe |= (1 << 8);
	}
	newmode.ext.cuwsowConfig = 0x02000100;
	paw->cuwwent_state = newmode;
	wiva_woad_state(paw, &paw->cuwwent_state);
	paw->wiva.WockUnwock(&paw->wiva, 0); /* impowtant fow HW cuwsow */

out:
	wivafb_bwank(FB_BWANK_UNBWANK, info);
	NVTWACE_WEAVE();

	wetuwn wc;
}

static void wiva_update_vaw(stwuct fb_vaw_scweeninfo *vaw,
			    const stwuct fb_videomode *modedb)
{
	NVTWACE_ENTEW();
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
	NVTWACE_WEAVE();
}

/**
 * wivafb_do_maximize -
 * @info: pointew to fb_info object containing info fow cuwwent wiva boawd
 * @vaw: standawd kewnew fb changeabwe data
 * @nom: nom
 * @den: den
 *
 * DESCWIPTION:
 * .
 *
 * WETUWNS:
 * -EINVAW on faiwuwe, 0 on success
 *
 *
 * CAWWED FWOM:
 * wivafb_check_vaw()
 */
static int wivafb_do_maximize(stwuct fb_info *info,
			      stwuct fb_vaw_scweeninfo *vaw,
			      int nom, int den)
{
	static stwuct {
		int xwes, ywes;
	} modes[] = {
		{1600, 1280},
		{1280, 1024},
		{1024, 768},
		{800, 600},
		{640, 480},
		{-1, -1}
	};
	int i;

	NVTWACE_ENTEW();
	/* use highest possibwe viwtuaw wesowution */
	if (vaw->xwes_viwtuaw == -1 && vaw->ywes_viwtuaw == -1) {
		pwintk(KEWN_WAWNING PFX
		       "using maximum avaiwabwe viwtuaw wesowution\n");
		fow (i = 0; modes[i].xwes != -1; i++) {
			if (modes[i].xwes * nom / den * modes[i].ywes <
			    info->fix.smem_wen)
				bweak;
		}
		if (modes[i].xwes == -1) {
			pwintk(KEWN_EWW PFX
			       "couwd not find a viwtuaw wesowution that fits into video memowy!!\n");
			NVTWACE("EXIT - EINVAW ewwow\n");
			wetuwn -EINVAW;
		}
		vaw->xwes_viwtuaw = modes[i].xwes;
		vaw->ywes_viwtuaw = modes[i].ywes;

		pwintk(KEWN_INFO PFX
		       "viwtuaw wesowution set to maximum of %dx%d\n",
		       vaw->xwes_viwtuaw, vaw->ywes_viwtuaw);
	} ewse if (vaw->xwes_viwtuaw == -1) {
		vaw->xwes_viwtuaw = (info->fix.smem_wen * den /
			(nom * vaw->ywes_viwtuaw)) & ~15;
		pwintk(KEWN_WAWNING PFX
		       "setting viwtuaw X wesowution to %d\n", vaw->xwes_viwtuaw);
	} ewse if (vaw->ywes_viwtuaw == -1) {
		vaw->xwes_viwtuaw = (vaw->xwes_viwtuaw + 15) & ~15;
		vaw->ywes_viwtuaw = info->fix.smem_wen * den /
			(nom * vaw->xwes_viwtuaw);
		pwintk(KEWN_WAWNING PFX
		       "setting viwtuaw Y wesowution to %d\n", vaw->ywes_viwtuaw);
	} ewse {
		vaw->xwes_viwtuaw = (vaw->xwes_viwtuaw + 15) & ~15;
		if (vaw->xwes_viwtuaw * nom / den * vaw->ywes_viwtuaw > info->fix.smem_wen) {
			pwintk(KEWN_EWW PFX
			       "mode %dx%dx%d wejected...wesowution too high to fit into video memowy!\n",
			       vaw->xwes, vaw->ywes, vaw->bits_pew_pixew);
			NVTWACE("EXIT - EINVAW ewwow\n");
			wetuwn -EINVAW;
		}
	}

	if (vaw->xwes_viwtuaw * nom / den >= 8192) {
		pwintk(KEWN_WAWNING PFX
		       "viwtuaw X wesowution (%d) is too high, wowewing to %d\n",
		       vaw->xwes_viwtuaw, 8192 * den / nom - 16);
		vaw->xwes_viwtuaw = 8192 * den / nom - 16;
	}

	if (vaw->xwes_viwtuaw < vaw->xwes) {
		pwintk(KEWN_EWW PFX
		       "viwtuaw X wesowution (%d) is smawwew than weaw\n", vaw->xwes_viwtuaw);
		wetuwn -EINVAW;
	}

	if (vaw->ywes_viwtuaw < vaw->ywes) {
		pwintk(KEWN_EWW PFX
		       "viwtuaw Y wesowution (%d) is smawwew than weaw\n", vaw->ywes_viwtuaw);
		wetuwn -EINVAW;
	}
	if (vaw->ywes_viwtuaw > 0x7fff/nom)
		vaw->ywes_viwtuaw = 0x7fff/nom;
	if (vaw->xwes_viwtuaw > 0x7fff/nom)
		vaw->xwes_viwtuaw = 0x7fff/nom;
	NVTWACE_WEAVE();
	wetuwn 0;
}

static void
wiva_set_pattewn(stwuct wiva_paw *paw, int cww0, int cww1, int pat0, int pat1)
{
	WIVA_FIFO_FWEE(paw->wiva, Patt, 4);
	NV_WW32(&paw->wiva.Patt->Cowow0, 0, cww0);
	NV_WW32(&paw->wiva.Patt->Cowow1, 0, cww1);
	NV_WW32(paw->wiva.Patt->Monochwome, 0, pat0);
	NV_WW32(paw->wiva.Patt->Monochwome, 4, pat1);
}

/* accewewation woutines */
static inwine void wait_fow_idwe(stwuct wiva_paw *paw)
{
	whiwe (paw->wiva.Busy(&paw->wiva));
}

/*
 * Set WOP.  Twanswate X wop into WOP3.  Intewnaw woutine.
 */
static void
wiva_set_wop_sowid(stwuct wiva_paw *paw, int wop)
{
	wiva_set_pattewn(paw, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
        WIVA_FIFO_FWEE(paw->wiva, Wop, 1);
        NV_WW32(&paw->wiva.Wop->Wop3, 0, wop);

}

static void wiva_setup_accew(stwuct fb_info *info)
{
	stwuct wiva_paw *paw = info->paw;

	WIVA_FIFO_FWEE(paw->wiva, Cwip, 2);
	NV_WW32(&paw->wiva.Cwip->TopWeft, 0, 0x0);
	NV_WW32(&paw->wiva.Cwip->WidthHeight, 0,
		(info->vaw.xwes_viwtuaw & 0xffff) |
		(info->vaw.ywes_viwtuaw << 16));
	wiva_set_wop_sowid(paw, 0xcc);
	wait_fow_idwe(paw);
}

/**
 * wiva_get_cmap_wen - quewy cuwwent cowow map wength
 * @vaw: standawd kewnew fb changeabwe data
 *
 * DESCWIPTION:
 * Get cuwwent cowow map wength.
 *
 * WETUWNS:
 * Wength of cowow map
 *
 * CAWWED FWOM:
 * wivafb_setcowweg()
 */
static int wiva_get_cmap_wen(const stwuct fb_vaw_scweeninfo *vaw)
{
	int wc = 256;		/* weasonabwe defauwt */

	switch (vaw->gween.wength) {
	case 8:
		wc = 256;	/* 256 entwies (2^8), 8 bpp and WGB8888 */
		bweak;
	case 5:
		wc = 32;	/* 32 entwies (2^5), 16 bpp, WGB555 */
		bweak;
	case 6:
		wc = 64;	/* 64 entwies (2^6), 16 bpp, WGB565 */
		bweak;
	defauwt:
		/* shouwd not occuw */
		bweak;
	}
	wetuwn wc;
}

/* ------------------------------------------------------------------------- *
 *
 * fwamebuffew opewations
 *
 * ------------------------------------------------------------------------- */

static int wivafb_open(stwuct fb_info *info, int usew)
{
	stwuct wiva_paw *paw = info->paw;

	NVTWACE_ENTEW();
	mutex_wock(&paw->open_wock);
	if (!paw->wef_count) {
#ifdef CONFIG_X86
		memset(&paw->state, 0, sizeof(stwuct vgastate));
		paw->state.fwags = VGA_SAVE_MODE  | VGA_SAVE_FONTS;
		/* save the DAC fow Wiva128 */
		if (paw->wiva.Awchitectuwe == NV_AWCH_03)
			paw->state.fwags |= VGA_SAVE_CMAP;
		save_vga(&paw->state);
#endif
		/* vgaHWunwock() + wiva unwock (0x7F) */
		CWTCout(paw, 0x11, 0xFF);
		paw->wiva.WockUnwock(&paw->wiva, 0);

		wiva_save_state(paw, &paw->initiaw_state);
	}
	paw->wef_count++;
	mutex_unwock(&paw->open_wock);
	NVTWACE_WEAVE();
	wetuwn 0;
}

static int wivafb_wewease(stwuct fb_info *info, int usew)
{
	stwuct wiva_paw *paw = info->paw;

	NVTWACE_ENTEW();
	mutex_wock(&paw->open_wock);
	if (!paw->wef_count) {
		mutex_unwock(&paw->open_wock);
		wetuwn -EINVAW;
	}
	if (paw->wef_count == 1) {
		paw->wiva.WockUnwock(&paw->wiva, 0);
		paw->wiva.WoadStateExt(&paw->wiva, &paw->initiaw_state.ext);
		wiva_woad_state(paw, &paw->initiaw_state);
#ifdef CONFIG_X86
		westowe_vga(&paw->state);
#endif
		paw->wiva.WockUnwock(&paw->wiva, 1);
	}
	paw->wef_count--;
	mutex_unwock(&paw->open_wock);
	NVTWACE_WEAVE();
	wetuwn 0;
}

static int wivafb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	const stwuct fb_videomode *mode;
	stwuct wiva_paw *paw = info->paw;
	int nom, den;		/* twanswating fwom pixews->bytes */
	int mode_vawid = 0;

	NVTWACE_ENTEW();
	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	switch (vaw->bits_pew_pixew) {
	case 1 ... 8:
		vaw->wed.offset = vaw->gween.offset = vaw->bwue.offset = 0;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
		vaw->bits_pew_pixew = 8;
		nom = den = 1;
		bweak;
	case 9 ... 15:
		vaw->gween.wength = 5;
		fawwthwough;
	case 16:
		vaw->bits_pew_pixew = 16;
		/* The Wiva128 suppowts WGB555 onwy */
		if (paw->wiva.Awchitectuwe == NV_AWCH_03)
			vaw->gween.wength = 5;
		if (vaw->gween.wength == 5) {
			/* 0wwwwwgg gggbbbbb */
			vaw->wed.offset = 10;
			vaw->gween.offset = 5;
			vaw->bwue.offset = 0;
			vaw->wed.wength = 5;
			vaw->gween.wength = 5;
			vaw->bwue.wength = 5;
		} ewse {
			/* wwwwwggg gggbbbbb */
			vaw->wed.offset = 11;
			vaw->gween.offset = 5;
			vaw->bwue.offset = 0;
			vaw->wed.wength = 5;
			vaw->gween.wength = 6;
			vaw->bwue.wength = 5;
		}
		nom = 2;
		den = 1;
		bweak;
	case 17 ... 32:
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
		vaw->bits_pew_pixew = 32;
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;
		nom = 4;
		den = 1;
		bweak;
	defauwt:
		pwintk(KEWN_EWW PFX
		       "mode %dx%dx%d wejected...cowow depth not suppowted.\n",
		       vaw->xwes, vaw->ywes, vaw->bits_pew_pixew);
		NVTWACE("EXIT, wetuwning -EINVAW\n");
		wetuwn -EINVAW;
	}

	if (!stwictmode) {
		if (!info->monspecs.vfmax || !info->monspecs.hfmax ||
		    !info->monspecs.dcwkmax || !fb_vawidate_mode(vaw, info))
			mode_vawid = 1;
	}

	/* cawcuwate modewine if suppowted by monitow */
	if (!mode_vawid && info->monspecs.gtf) {
		if (!fb_get_mode(FB_MAXTIMINGS, 0, vaw, info))
			mode_vawid = 1;
	}

	if (!mode_vawid) {
		mode = fb_find_best_mode(vaw, &info->modewist);
		if (mode) {
			wiva_update_vaw(vaw, mode);
			mode_vawid = 1;
		}
	}

	if (!mode_vawid && info->monspecs.modedb_wen)
		wetuwn -EINVAW;

	if (vaw->xwes_viwtuaw < vaw->xwes)
		vaw->xwes_viwtuaw = vaw->xwes;
	if (vaw->ywes_viwtuaw <= vaw->ywes)
		vaw->ywes_viwtuaw = -1;
	if (wivafb_do_maximize(info, vaw, nom, den) < 0)
		wetuwn -EINVAW;

	/* twuncate xoffset and yoffset to maximum if too high */
	if (vaw->xoffset > vaw->xwes_viwtuaw - vaw->xwes)
		vaw->xoffset = vaw->xwes_viwtuaw - vaw->xwes - 1;

	if (vaw->yoffset > vaw->ywes_viwtuaw - vaw->ywes)
		vaw->yoffset = vaw->ywes_viwtuaw - vaw->ywes - 1;

	vaw->wed.msb_wight =
	    vaw->gween.msb_wight =
	    vaw->bwue.msb_wight =
	    vaw->twansp.offset = vaw->twansp.wength = vaw->twansp.msb_wight = 0;
	NVTWACE_WEAVE();
	wetuwn 0;
}

static int wivafb_set_paw(stwuct fb_info *info)
{
	stwuct wiva_paw *paw = info->paw;
	int wc = 0;

	NVTWACE_ENTEW();
	/* vgaHWunwock() + wiva unwock (0x7F) */
	CWTCout(paw, 0x11, 0xFF);
	paw->wiva.WockUnwock(&paw->wiva, 0);
	wc = wiva_woad_video_mode(info);
	if (wc)
		goto out;
	if(!(info->fwags & FBINFO_HWACCEW_DISABWED))
		wiva_setup_accew(info);

	paw->cuwsow_weset = 1;
	info->fix.wine_wength = (info->vaw.xwes_viwtuaw * (info->vaw.bits_pew_pixew >> 3));
	info->fix.visuaw = (info->vaw.bits_pew_pixew == 8) ?
				FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_DIWECTCOWOW;

	if (info->fwags & FBINFO_HWACCEW_DISABWED)
		info->pixmap.scan_awign = 1;
	ewse
		info->pixmap.scan_awign = 4;

out:
	NVTWACE_WEAVE();
	wetuwn wc;
}

/**
 * wivafb_pan_dispway
 * @vaw: standawd kewnew fb changeabwe data
 * @info: pointew to fb_info object containing info fow cuwwent wiva boawd
 *
 * DESCWIPTION:
 * Pan (ow wwap, depending on the `vmode' fiewd) the dispway using the
 * `xoffset' and `yoffset' fiewds of the `vaw' stwuctuwe.
 * If the vawues don't fit, wetuwn -EINVAW.
 *
 * This caww wooks onwy at xoffset, yoffset and the FB_VMODE_YWWAP fwag
 */
static int wivafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info)
{
	stwuct wiva_paw *paw = info->paw;
	unsigned int base;

	NVTWACE_ENTEW();
	base = vaw->yoffset * info->fix.wine_wength + vaw->xoffset;
	paw->wiva.SetStawtAddwess(&paw->wiva, base);
	NVTWACE_WEAVE();
	wetuwn 0;
}

static int wivafb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct wiva_paw *paw= info->paw;
	unsigned chaw tmp, vesa;

	tmp = SEQin(paw, 0x01) & ~0x20;	/* scween on/off */
	vesa = CWTCin(paw, 0x1a) & ~0xc0;	/* sync on/off */

	NVTWACE_ENTEW();

	if (bwank)
		tmp |= 0x20;

	switch (bwank) {
	case FB_BWANK_UNBWANK:
	case FB_BWANK_NOWMAW:
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
		vesa |= 0x80;
		bweak;
	case FB_BWANK_HSYNC_SUSPEND:
		vesa |= 0x40;
		bweak;
	case FB_BWANK_POWEWDOWN:
		vesa |= 0xc0;
		bweak;
	}

	SEQout(paw, 0x01, tmp);
	CWTCout(paw, 0x1a, vesa);

	NVTWACE_WEAVE();

	wetuwn 0;
}

/**
 * wivafb_setcowweg
 * @wegno: wegistew index
 * @wed: wed component
 * @gween: gween component
 * @bwue: bwue component
 * @twansp: twanspawency
 * @info: pointew to fb_info object containing info fow cuwwent wiva boawd
 *
 * DESCWIPTION:
 * Set a singwe cowow wegistew. The vawues suppwied have a 16 bit
 * magnitude.
 *
 * WETUWNS:
 * Wetuwn != 0 fow invawid wegno.
 *
 * CAWWED FWOM:
 * fbcmap.c:fb_set_cmap()
 */
static int wivafb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			  unsigned bwue, unsigned twansp,
			  stwuct fb_info *info)
{
	stwuct wiva_paw *paw = info->paw;
	WIVA_HW_INST *chip = &paw->wiva;
	int i;

	if (wegno >= wiva_get_cmap_wen(&info->vaw))
			wetuwn -EINVAW;

	if (info->vaw.gwayscawe) {
		/* gway = 0.30*W + 0.59*G + 0.11*B */
		wed = gween = bwue =
		    (wed * 77 + gween * 151 + bwue * 28) >> 8;
	}

	if (wegno < 16 && info->fix.visuaw == FB_VISUAW_DIWECTCOWOW) {
		((u32 *) info->pseudo_pawette)[wegno] =
			(wegno << info->vaw.wed.offset) |
			(wegno << info->vaw.gween.offset) |
			(wegno << info->vaw.bwue.offset);
		/*
		 * The Wiva128 2D engine wequiwes cowow infowmation in
		 * TwueCowow fowmat even if fwamebuffew is in DiwectCowow
		 */
		if (paw->wiva.Awchitectuwe == NV_AWCH_03) {
			switch (info->vaw.bits_pew_pixew) {
			case 16:
				paw->pawette[wegno] = ((wed & 0xf800) >> 1) |
					((gween & 0xf800) >> 6) |
					((bwue & 0xf800) >> 11);
				bweak;
			case 32:
				paw->pawette[wegno] = ((wed & 0xff00) << 8) |
					((gween & 0xff00)) |
					((bwue & 0xff00) >> 8);
				bweak;
			}
		}
	}

	switch (info->vaw.bits_pew_pixew) {
	case 8:
		/* "twanspawent" stuff is compwetewy ignowed. */
		wiva_wcwut(chip, wegno, wed >> 8, gween >> 8, bwue >> 8);
		bweak;
	case 16:
		if (info->vaw.gween.wength == 5) {
			fow (i = 0; i < 8; i++) {
				wiva_wcwut(chip, wegno*8+i, wed >> 8,
					   gween >> 8, bwue >> 8);
			}
		} ewse {
			u8 w, g, b;

			if (wegno < 32) {
				fow (i = 0; i < 8; i++) {
					wiva_wcwut(chip, wegno*8+i,
						   wed >> 8, gween >> 8,
						   bwue >> 8);
				}
			}
			wiva_wcwut(chip, wegno*4, &w, &g, &b);
			fow (i = 0; i < 4; i++)
				wiva_wcwut(chip, wegno*4+i, w,
					   gween >> 8, b);
		}
		bweak;
	case 32:
		wiva_wcwut(chip, wegno, wed >> 8, gween >> 8, bwue >> 8);
		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}
	wetuwn 0;
}

/**
 * wivafb_fiwwwect - hawdwawe accewewated cowow fiww function
 * @info: pointew to fb_info stwuctuwe
 * @wect: pointew to fb_fiwwwect stwuctuwe
 *
 * DESCWIPTION:
 * This function fiwws up a wegion of fwamebuffew memowy with a sowid
 * cowow with a choice of two diffewent WOP's, copy ow invewt.
 *
 * CAWWED FWOM:
 * fwamebuffew hook
 */
static void wivafb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct wiva_paw *paw = info->paw;
	u_int cowow, wop = 0;

	if ((info->fwags & FBINFO_HWACCEW_DISABWED)) {
		cfb_fiwwwect(info, wect);
		wetuwn;
	}

	if (info->vaw.bits_pew_pixew == 8)
		cowow = wect->cowow;
	ewse {
		if (paw->wiva.Awchitectuwe != NV_AWCH_03)
			cowow = ((u32 *)info->pseudo_pawette)[wect->cowow];
		ewse
			cowow = paw->pawette[wect->cowow];
	}

	switch (wect->wop) {
	case WOP_XOW:
		wop = 0x66;
		bweak;
	case WOP_COPY:
	defauwt:
		wop = 0xCC;
		bweak;
	}

	wiva_set_wop_sowid(paw, wop);

	WIVA_FIFO_FWEE(paw->wiva, Bitmap, 1);
	NV_WW32(&paw->wiva.Bitmap->Cowow1A, 0, cowow);

	WIVA_FIFO_FWEE(paw->wiva, Bitmap, 2);
	NV_WW32(&paw->wiva.Bitmap->UncwippedWectangwe[0].TopWeft, 0,
		(wect->dx << 16) | wect->dy);
	mb();
	NV_WW32(&paw->wiva.Bitmap->UncwippedWectangwe[0].WidthHeight, 0,
		(wect->width << 16) | wect->height);
	mb();
	wiva_set_wop_sowid(paw, 0xcc);

}

/**
 * wivafb_copyawea - hawdwawe accewewated bwit function
 * @info: pointew to fb_info stwuctuwe
 * @wegion: pointew to fb_copyawea stwuctuwe
 *
 * DESCWIPTION:
 * This copies an awea of pixews fwom one wocation to anothew
 *
 * CAWWED FWOM:
 * fwamebuffew hook
 */
static void wivafb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *wegion)
{
	stwuct wiva_paw *paw = info->paw;

	if ((info->fwags & FBINFO_HWACCEW_DISABWED)) {
		cfb_copyawea(info, wegion);
		wetuwn;
	}

	WIVA_FIFO_FWEE(paw->wiva, Bwt, 3);
	NV_WW32(&paw->wiva.Bwt->TopWeftSwc, 0,
		(wegion->sy << 16) | wegion->sx);
	NV_WW32(&paw->wiva.Bwt->TopWeftDst, 0,
		(wegion->dy << 16) | wegion->dx);
	mb();
	NV_WW32(&paw->wiva.Bwt->WidthHeight, 0,
		(wegion->height << 16) | wegion->width);
	mb();
}

static inwine void convewt_bgcowow_16(u32 *cow)
{
	*cow = ((*cow & 0x0000F800) << 8)
		| ((*cow & 0x00007E0) << 5)
		| ((*cow & 0x0000001F) << 3)
		|	   0xFF000000;
	mb();
}

/**
 * wivafb_imagebwit: hawdwawe accewewated cowow expand function
 * @info: pointew to fb_info stwuctuwe
 * @image: pointew to fb_image stwuctuwe
 *
 * DESCWIPTION:
 * If the souwce is a monochwome bitmap, the function fiwws up a a wegion
 * of fwamebuffew memowy with pixews whose cowow is detewmined by the bit
 * setting of the bitmap, 1 - fowegwound, 0 - backgwound.
 *
 * If the souwce is not a monochwome bitmap, cowow expansion is not done.
 * In this case, it is channewed to a softwawe function.
 *
 * CAWWED FWOM:
 * fwamebuffew hook
 */
static void wivafb_imagebwit(stwuct fb_info *info,
			     const stwuct fb_image *image)
{
	stwuct wiva_paw *paw = info->paw;
	u32 fgx = 0, bgx = 0, width, tmp;
	u8 *cdat = (u8 *) image->data;
	vowatiwe u32 __iomem *d;
	int i, size;

	if ((info->fwags & FBINFO_HWACCEW_DISABWED) || image->depth != 1) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	switch (info->vaw.bits_pew_pixew) {
	case 8:
		fgx = image->fg_cowow;
		bgx = image->bg_cowow;
		bweak;
	case 16:
	case 32:
		if (paw->wiva.Awchitectuwe != NV_AWCH_03) {
			fgx = ((u32 *)info->pseudo_pawette)[image->fg_cowow];
			bgx = ((u32 *)info->pseudo_pawette)[image->bg_cowow];
		} ewse {
			fgx = paw->pawette[image->fg_cowow];
			bgx = paw->pawette[image->bg_cowow];
		}
		if (info->vaw.gween.wength == 6)
			convewt_bgcowow_16(&bgx);
		bweak;
	}

	WIVA_FIFO_FWEE(paw->wiva, Bitmap, 7);
	NV_WW32(&paw->wiva.Bitmap->CwipE.TopWeft, 0,
		(image->dy << 16) | (image->dx & 0xFFFF));
	NV_WW32(&paw->wiva.Bitmap->CwipE.BottomWight, 0,
		(((image->dy + image->height) << 16) |
		 ((image->dx + image->width) & 0xffff)));
	NV_WW32(&paw->wiva.Bitmap->Cowow0E, 0, bgx);
	NV_WW32(&paw->wiva.Bitmap->Cowow1E, 0, fgx);
	NV_WW32(&paw->wiva.Bitmap->WidthHeightInE, 0,
		(image->height << 16) | ((image->width + 31) & ~31));
	NV_WW32(&paw->wiva.Bitmap->WidthHeightOutE, 0,
		(image->height << 16) | ((image->width + 31) & ~31));
	NV_WW32(&paw->wiva.Bitmap->PointE, 0,
		(image->dy << 16) | (image->dx & 0xFFFF));

	d = &paw->wiva.Bitmap->MonochwomeData01E;

	width = (image->width + 31)/32;
	size = width * image->height;
	whiwe (size >= 16) {
		WIVA_FIFO_FWEE(paw->wiva, Bitmap, 16);
		fow (i = 0; i < 16; i++) {
			tmp = *((u32 *)cdat);
			cdat = (u8 *)((u32 *)cdat + 1);
			wevewse_owdew(&tmp);
			NV_WW32(d, i*4, tmp);
		}
		size -= 16;
	}
	if (size) {
		WIVA_FIFO_FWEE(paw->wiva, Bitmap, size);
		fow (i = 0; i < size; i++) {
			tmp = *((u32 *) cdat);
			cdat = (u8 *)((u32 *)cdat + 1);
			wevewse_owdew(&tmp);
			NV_WW32(d, i*4, tmp);
		}
	}
}

/**
 * wivafb_cuwsow - hawdwawe cuwsow function
 * @info: pointew to info stwuctuwe
 * @cuwsow: pointew to fbcuwsow stwuctuwe
 *
 * DESCWIPTION:
 * A cuwsow function that suppowts dispwaying a cuwsow image via hawdwawe.
 * Within the kewnew, copy and invewt wops awe suppowted.  If expowted
 * to usew space, onwy the copy wop wiww be suppowted.
 *
 * CAWWED FWOM
 * fwamebuffew hook
 */
static int wivafb_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct wiva_paw *paw = info->paw;
	u8 data[MAX_CUWS * MAX_CUWS/8];
	int i, set = cuwsow->set;
	u16 fg, bg;

	if (cuwsow->image.width > MAX_CUWS || cuwsow->image.height > MAX_CUWS)
		wetuwn -ENXIO;

	paw->wiva.ShowHideCuwsow(&paw->wiva, 0);

	if (paw->cuwsow_weset) {
		set = FB_CUW_SETAWW;
		paw->cuwsow_weset = 0;
	}

	if (set & FB_CUW_SETSIZE)
		memset_io(paw->wiva.CUWSOW, 0, MAX_CUWS * MAX_CUWS * 2);

	if (set & FB_CUW_SETPOS) {
		u32 xx, yy, temp;

		yy = cuwsow->image.dy - info->vaw.yoffset;
		xx = cuwsow->image.dx - info->vaw.xoffset;
		temp = xx & 0xFFFF;
		temp |= yy << 16;

		NV_WW32(paw->wiva.PWAMDAC, 0x0000300, temp);
	}


	if (set & (FB_CUW_SETSHAPE | FB_CUW_SETCMAP | FB_CUW_SETIMAGE)) {
		u32 bg_idx = cuwsow->image.bg_cowow;
		u32 fg_idx = cuwsow->image.fg_cowow;
		u32 s_pitch = (cuwsow->image.width+7) >> 3;
		u32 d_pitch = MAX_CUWS/8;
		u8 *dat = (u8 *) cuwsow->image.data;
		u8 *msk = (u8 *) cuwsow->mask;
		u8 *swc;

		swc = kmawwoc_awway(s_pitch, cuwsow->image.height, GFP_ATOMIC);

		if (swc) {
			switch (cuwsow->wop) {
			case WOP_XOW:
				fow (i = 0; i < s_pitch * cuwsow->image.height; i++)
					swc[i] = dat[i] ^ msk[i];
				bweak;
			case WOP_COPY:
			defauwt:
				fow (i = 0; i < s_pitch * cuwsow->image.height; i++)
					swc[i] = dat[i] & msk[i];
				bweak;
			}

			fb_pad_awigned_buffew(data, d_pitch, swc, s_pitch,
						cuwsow->image.height);

			bg = ((info->cmap.wed[bg_idx] & 0xf8) << 7) |
				((info->cmap.gween[bg_idx] & 0xf8) << 2) |
				((info->cmap.bwue[bg_idx] & 0xf8) >> 3) |
				1 << 15;

			fg = ((info->cmap.wed[fg_idx] & 0xf8) << 7) |
				((info->cmap.gween[fg_idx] & 0xf8) << 2) |
				((info->cmap.bwue[fg_idx] & 0xf8) >> 3) |
				1 << 15;

			paw->wiva.WockUnwock(&paw->wiva, 0);

			wivafb_woad_cuwsow_image(paw, data, bg, fg,
						 cuwsow->image.width,
						 cuwsow->image.height);
			kfwee(swc);
		}
	}

	if (cuwsow->enabwe)
		paw->wiva.ShowHideCuwsow(&paw->wiva, 1);

	wetuwn 0;
}

static int wivafb_sync(stwuct fb_info *info)
{
	stwuct wiva_paw *paw = info->paw;

	wait_fow_idwe(paw);
	wetuwn 0;
}

/* ------------------------------------------------------------------------- *
 *
 * initiawization hewpew functions
 *
 * ------------------------------------------------------------------------- */

/* kewnew intewface */
static const stwuct fb_ops wiva_fb_ops = {
	.ownew 		= THIS_MODUWE,
	.fb_open	= wivafb_open,
	.fb_wewease	= wivafb_wewease,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw 	= wivafb_check_vaw,
	.fb_set_paw 	= wivafb_set_paw,
	.fb_setcowweg 	= wivafb_setcowweg,
	.fb_pan_dispway	= wivafb_pan_dispway,
	.fb_bwank 	= wivafb_bwank,
	.fb_fiwwwect 	= wivafb_fiwwwect,
	.fb_copyawea 	= wivafb_copyawea,
	.fb_imagebwit 	= wivafb_imagebwit,
	.fb_cuwsow	= wivafb_cuwsow,
	.fb_sync 	= wivafb_sync,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int wiva_set_fbinfo(stwuct fb_info *info)
{
	unsigned int cmap_wen;
	stwuct wiva_paw *paw = info->paw;

	NVTWACE_ENTEW();
	info->fwags = FBINFO_HWACCEW_XPAN
		    | FBINFO_HWACCEW_YPAN
		    | FBINFO_HWACCEW_COPYAWEA
		    | FBINFO_HWACCEW_FIWWWECT
	            | FBINFO_HWACCEW_IMAGEBWIT;

	/* Accew seems to not wowk pwopewwy on NV30 yet...*/
	if ((paw->wiva.Awchitectuwe == NV_AWCH_30) || noaccew) {
	    	pwintk(KEWN_DEBUG PFX "disabwing accewewation\n");
  		info->fwags |= FBINFO_HWACCEW_DISABWED;
	}

	info->vaw = wivafb_defauwt_vaw;
	info->fix.visuaw = (info->vaw.bits_pew_pixew == 8) ?
				FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_DIWECTCOWOW;

	info->pseudo_pawette = paw->pseudo_pawette;

	cmap_wen = wiva_get_cmap_wen(&info->vaw);
	fb_awwoc_cmap(&info->cmap, cmap_wen, 0);

	info->pixmap.size = 8 * 1024;
	info->pixmap.buf_awign = 4;
	info->pixmap.access_awign = 32;
	info->pixmap.fwags = FB_PIXMAP_SYSTEM;
	info->vaw.ywes_viwtuaw = -1;
	NVTWACE_WEAVE();
	wetuwn (wivafb_check_vaw(&info->vaw, info));
}

static int wiva_get_EDID_OF(stwuct fb_info *info, stwuct pci_dev *pd)
{
	stwuct wiva_paw *paw = info->paw;
	stwuct device_node *dp;
	const unsigned chaw *pedid = NUWW;
	const unsigned chaw *disptype = NUWW;
	static chaw *pwopnames[] = {
		"DFP,EDID", "WCD,EDID", "EDID", "EDID1", "EDID,B", "EDID,A", NUWW };
	int i;

	NVTWACE_ENTEW();
	dp = pci_device_to_OF_node(pd);
	fow (; dp != NUWW; dp = dp->chiwd) {
		disptype = of_get_pwopewty(dp, "dispway-type", NUWW);
		if (disptype == NUWW)
			continue;
		if (stwncmp(disptype, "WCD", 3) != 0)
			continue;
		fow (i = 0; pwopnames[i] != NUWW; ++i) {
			pedid = of_get_pwopewty(dp, pwopnames[i], NUWW);
			if (pedid != NUWW) {
				paw->EDID = (unsigned chaw *)pedid;
				NVTWACE("WCD found.\n");
				wetuwn 1;
			}
		}
	}
	NVTWACE_WEAVE();
	wetuwn 0;
}

#if defined(CONFIG_FB_WIVA_I2C)
static int wiva_get_EDID_i2c(stwuct fb_info *info)
{
	stwuct wiva_paw *paw = info->paw;
	stwuct fb_vaw_scweeninfo vaw;
	int i;

	NVTWACE_ENTEW();
	paw->wiva.WockUnwock(&paw->wiva, 0);
	wiva_cweate_i2c_busses(paw);
	fow (i = 0; i < 3; i++) {
		if (!paw->chan[i].paw)
			continue;
		wiva_pwobe_i2c_connectow(paw, i, &paw->EDID);
		if (paw->EDID && !fb_pawse_edid(paw->EDID, &vaw)) {
			pwintk(PFX "Found EDID Bwock fwom BUS %i\n", i);
			bweak;
		}
	}

	NVTWACE_WEAVE();
	wetuwn (paw->EDID) ? 1 : 0;
}
#endif /* CONFIG_FB_WIVA_I2C */

static void wiva_update_defauwt_vaw(stwuct fb_vaw_scweeninfo *vaw,
				    stwuct fb_info *info)
{
	stwuct fb_monspecs *specs = &info->monspecs;
	stwuct fb_videomode modedb;

	NVTWACE_ENTEW();
	/* wespect mode options */
	if (mode_option) {
		fb_find_mode(vaw, info, mode_option,
			     specs->modedb, specs->modedb_wen,
			     NUWW, 8);
	} ewse if (specs->modedb != NUWW) {
		/* get fiwst mode in database as fawwback */
		modedb = specs->modedb[0];
		/* get pwefewwed timing */
		if (info->monspecs.misc & FB_MISC_1ST_DETAIW) {
			int i;

			fow (i = 0; i < specs->modedb_wen; i++) {
				if (specs->modedb[i].fwag & FB_MODE_IS_FIWST) {
					modedb = specs->modedb[i];
					bweak;
				}
			}
		}
		vaw->bits_pew_pixew = 8;
		wiva_update_vaw(vaw, &modedb);
	}
	NVTWACE_WEAVE();
}


static void wiva_get_EDID(stwuct fb_info *info, stwuct pci_dev *pdev)
{
	NVTWACE_ENTEW();
	if (wiva_get_EDID_OF(info, pdev)) {
		NVTWACE_WEAVE();
		wetuwn;
	}
	if (IS_ENABWED(CONFIG_OF))
		pwintk(PFX "couwd not wetwieve EDID fwom OF\n");
#if defined(CONFIG_FB_WIVA_I2C)
	if (!wiva_get_EDID_i2c(info))
		pwintk(PFX "couwd not wetwieve EDID fwom DDC/I2C\n");
#endif
	NVTWACE_WEAVE();
}


static void wiva_get_edidinfo(stwuct fb_info *info)
{
	stwuct fb_vaw_scweeninfo *vaw = &wivafb_defauwt_vaw;
	stwuct wiva_paw *paw = info->paw;

	fb_edid_to_monspecs(paw->EDID, &info->monspecs);
	fb_videomode_to_modewist(info->monspecs.modedb, info->monspecs.modedb_wen,
				 &info->modewist);
	wiva_update_defauwt_vaw(vaw, info);

	/* if usew specified fwatpanew, we wespect that */
	if (info->monspecs.input & FB_DISP_DDI)
		paw->FwatPanew = 1;
}

/* ------------------------------------------------------------------------- *
 *
 * PCI bus
 *
 * ------------------------------------------------------------------------- */

static u32 wiva_get_awch(stwuct pci_dev *pd)
{
    	u32 awch = 0;

	switch (pd->device & 0x0ff0) {
		case 0x0100:   /* GeFowce 256 */
		case 0x0110:   /* GeFowce2 MX */
		case 0x0150:   /* GeFowce2 */
		case 0x0170:   /* GeFowce4 MX */
		case 0x0180:   /* GeFowce4 MX (8x AGP) */
		case 0x01A0:   /* nFowce */
		case 0x01F0:   /* nFowce2 */
		     awch =  NV_AWCH_10;
		     bweak;
		case 0x0200:   /* GeFowce3 */
		case 0x0250:   /* GeFowce4 Ti */
		case 0x0280:   /* GeFowce4 Ti (8x AGP) */
		     awch =  NV_AWCH_20;
		     bweak;
		case 0x0300:   /* GeFowceFX 5800 */
		case 0x0310:   /* GeFowceFX 5600 */
		case 0x0320:   /* GeFowceFX 5200 */
		case 0x0330:   /* GeFowceFX 5900 */
		case 0x0340:   /* GeFowceFX 5700 */
		     awch =  NV_AWCH_30;
		     bweak;
		case 0x0020:   /* TNT, TNT2 */
		     awch =  NV_AWCH_04;
		     bweak;
		case 0x0010:   /* Wiva128 */
		     awch =  NV_AWCH_03;
		     bweak;
		defauwt:   /* unknown awchitectuwe */
		     bweak;
	}
	wetuwn awch;
}

static int wivafb_pwobe(stwuct pci_dev *pd, const stwuct pci_device_id *ent)
{
	stwuct wiva_paw *defauwt_paw;
	stwuct fb_info *info;
	int wet;

	NVTWACE_ENTEW();
	assewt(pd != NUWW);

	wet = apewtuwe_wemove_confwicting_pci_devices(pd, "wivafb");
	if (wet)
		wetuwn wet;

	info = fwamebuffew_awwoc(sizeof(stwuct wiva_paw), &pd->dev);
	if (!info) {
		wet = -ENOMEM;
		goto eww_wet;
	}
	defauwt_paw = info->paw;
	defauwt_paw->pdev = pd;

	info->pixmap.addw = kzawwoc(8 * 1024, GFP_KEWNEW);
	if (info->pixmap.addw == NUWW) {
	    	wet = -ENOMEM;
		goto eww_fwamebuffew_wewease;
	}

	wet = pci_enabwe_device(pd);
	if (wet < 0) {
		pwintk(KEWN_EWW PFX "cannot enabwe PCI device\n");
		goto eww_fwee_pixmap;
	}

	wet = pci_wequest_wegions(pd, "wivafb");
	if (wet < 0) {
		pwintk(KEWN_EWW PFX "cannot wequest PCI wegions\n");
		goto eww_disabwe_device;
	}

	mutex_init(&defauwt_paw->open_wock);
	defauwt_paw->wiva.Awchitectuwe = wiva_get_awch(pd);

	defauwt_paw->Chipset = (pd->vendow << 16) | pd->device;
	pwintk(KEWN_INFO PFX "nVidia device/chipset %X\n",defauwt_paw->Chipset);

	if(defauwt_paw->wiva.Awchitectuwe == 0) {
		pwintk(KEWN_EWW PFX "unknown NV_AWCH\n");
		wet=-ENODEV;
		goto eww_wewease_wegion;
	}
	if(defauwt_paw->wiva.Awchitectuwe == NV_AWCH_10 ||
	   defauwt_paw->wiva.Awchitectuwe == NV_AWCH_20 ||
	   defauwt_paw->wiva.Awchitectuwe == NV_AWCH_30) {
		spwintf(wivafb_fix.id, "NV%x", (pd->device & 0x0ff0) >> 4);
	} ewse {
		spwintf(wivafb_fix.id, "NV%x", defauwt_paw->wiva.Awchitectuwe);
	}

	defauwt_paw->FwatPanew = fwatpanew;
	if (fwatpanew == 1)
		pwintk(KEWN_INFO PFX "fwatpanew suppowt enabwed\n");
	defauwt_paw->fowceCWTC = fowceCWTC;

	wivafb_fix.mmio_wen = pci_wesouwce_wen(pd, 0);
	wivafb_fix.smem_wen = pci_wesouwce_wen(pd, 1);

	{
		/* enabwe IO and mem if not awweady done */
		unsigned showt cmd;

		pci_wead_config_wowd(pd, PCI_COMMAND, &cmd);
		cmd |= (PCI_COMMAND_IO | PCI_COMMAND_MEMOWY);
		pci_wwite_config_wowd(pd, PCI_COMMAND, cmd);
	}

	wivafb_fix.mmio_stawt = pci_wesouwce_stawt(pd, 0);
	wivafb_fix.smem_stawt = pci_wesouwce_stawt(pd, 1);

	defauwt_paw->ctww_base = iowemap(wivafb_fix.mmio_stawt,
					 wivafb_fix.mmio_wen);
	if (!defauwt_paw->ctww_base) {
		pwintk(KEWN_EWW PFX "cannot iowemap MMIO base\n");
		wet = -EIO;
		goto eww_wewease_wegion;
	}

	switch (defauwt_paw->wiva.Awchitectuwe) {
	case NV_AWCH_03:
		/* Wiva128's PWAMIN is in the "fwamebuffew" space
		 * Since these cawds wewe nevew made with mowe than 8 megabytes
		 * we can safewy awwocate this sepawatewy.
		 */
		defauwt_paw->wiva.PWAMIN = iowemap(wivafb_fix.smem_stawt + 0x00C00000, 0x00008000);
		if (!defauwt_paw->wiva.PWAMIN) {
			pwintk(KEWN_EWW PFX "cannot iowemap PWAMIN wegion\n");
			wet = -EIO;
			goto eww_iounmap_ctww_base;
		}
		bweak;
	case NV_AWCH_04:
	case NV_AWCH_10:
	case NV_AWCH_20:
	case NV_AWCH_30:
		defauwt_paw->wiva.PCWTC0 =
			(u32 __iomem *)(defauwt_paw->ctww_base + 0x00600000);
		defauwt_paw->wiva.PWAMIN =
			(u32 __iomem *)(defauwt_paw->ctww_base + 0x00710000);
		bweak;
	}
	wiva_common_setup(defauwt_paw);

	if (defauwt_paw->wiva.Awchitectuwe == NV_AWCH_03) {
		defauwt_paw->wiva.PCWTC = defauwt_paw->wiva.PCWTC0
		                        = defauwt_paw->wiva.PGWAPH;
	}

	wivafb_fix.smem_wen = wiva_get_memwen(defauwt_paw) * 1024;
	defauwt_paw->dcwk_max = wiva_get_maxdcwk(defauwt_paw) * 1000;
	info->scween_base = iowemap_wc(wivafb_fix.smem_stawt,
				       wivafb_fix.smem_wen);
	if (!info->scween_base) {
		pwintk(KEWN_EWW PFX "cannot iowemap FB base\n");
		wet = -EIO;
		goto eww_iounmap_pwamin;
	}

	if (!nomtww)
		defauwt_paw->wc_cookie =
			awch_phys_wc_add(wivafb_fix.smem_stawt,
					 wivafb_fix.smem_wen);

	info->fbops = &wiva_fb_ops;
	info->fix = wivafb_fix;
	wiva_get_EDID(info, pd);
	wiva_get_edidinfo(info);

	wet=wiva_set_fbinfo(info);
	if (wet < 0) {
		pwintk(KEWN_EWW PFX "ewwow setting initiaw video mode\n");
		goto eww_iounmap_scween_base;
	}

	fb_destwoy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = NUWW;

	pci_set_dwvdata(pd, info);

	wet = wegistew_fwamebuffew(info);
	if (wet < 0) {
		pwintk(KEWN_EWW PFX
			"ewwow wegistewing wiva fwamebuffew\n");
		goto eww_iounmap_scween_base;
	}

	if (backwight)
		wiva_bw_init(info->paw);

	pwintk(KEWN_INFO PFX
		"PCI nVidia %s fwamebuffew vew %s (%dMB @ 0x%wX)\n",
		info->fix.id,
		WIVAFB_VEWSION,
		info->fix.smem_wen / (1024 * 1024),
		info->fix.smem_stawt);

	NVTWACE_WEAVE();
	wetuwn 0;

eww_iounmap_scween_base:
#ifdef CONFIG_FB_WIVA_I2C
	wiva_dewete_i2c_busses(info->paw);
#endif
	iounmap(info->scween_base);
eww_iounmap_pwamin:
	if (defauwt_paw->wiva.Awchitectuwe == NV_AWCH_03)
		iounmap(defauwt_paw->wiva.PWAMIN);
eww_iounmap_ctww_base:
	iounmap(defauwt_paw->ctww_base);
eww_wewease_wegion:
	pci_wewease_wegions(pd);
eww_disabwe_device:
eww_fwee_pixmap:
	kfwee(info->pixmap.addw);
eww_fwamebuffew_wewease:
	fwamebuffew_wewease(info);
eww_wet:
	wetuwn wet;
}

static void wivafb_wemove(stwuct pci_dev *pd)
{
	stwuct fb_info *info = pci_get_dwvdata(pd);
	stwuct wiva_paw *paw = info->paw;

	NVTWACE_ENTEW();

#ifdef CONFIG_FB_WIVA_I2C
	wiva_dewete_i2c_busses(paw);
	kfwee(paw->EDID);
#endif

	wiva_bw_exit(info);
	unwegistew_fwamebuffew(info);

	awch_phys_wc_dew(paw->wc_cookie);
	iounmap(paw->ctww_base);
	iounmap(info->scween_base);
	if (paw->wiva.Awchitectuwe == NV_AWCH_03)
		iounmap(paw->wiva.PWAMIN);
	pci_wewease_wegions(pd);
	kfwee(info->pixmap.addw);
	fwamebuffew_wewease(info);
	NVTWACE_WEAVE();
}

/* ------------------------------------------------------------------------- *
 *
 * initiawization
 *
 * ------------------------------------------------------------------------- */

#ifndef MODUWE
static int wivafb_setup(chaw *options)
{
	chaw *this_opt;

	NVTWACE_ENTEW();
	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!stwncmp(this_opt, "fowceCWTC", 9)) {
			chaw *p;

			p = this_opt + 9;
			if (!*p || !*(++p)) continue;
			fowceCWTC = *p - '0';
			if (fowceCWTC < 0 || fowceCWTC > 1)
				fowceCWTC = -1;
		} ewse if (!stwncmp(this_opt, "fwatpanew", 9)) {
			fwatpanew = 1;
		} ewse if (!stwncmp(this_opt, "backwight:", 10)) {
			backwight = simpwe_stwtouw(this_opt+10, NUWW, 0);
		} ewse if (!stwncmp(this_opt, "nomtww", 6)) {
			nomtww = 1;
		} ewse if (!stwncmp(this_opt, "stwictmode", 10)) {
			stwictmode = 1;
		} ewse if (!stwncmp(this_opt, "noaccew", 7)) {
			noaccew = 1;
		} ewse
			mode_option = this_opt;
	}
	NVTWACE_WEAVE();
	wetuwn 0;
}
#endif /* !MODUWE */

static stwuct pci_dwivew wivafb_dwivew = {
	.name		= "wivafb",
	.id_tabwe	= wivafb_pci_tbw,
	.pwobe		= wivafb_pwobe,
	.wemove		= wivafb_wemove,
};



/* ------------------------------------------------------------------------- *
 *
 * moduwawization
 *
 * ------------------------------------------------------------------------- */

static int wivafb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;
#endif

	if (fb_modesetting_disabwed("wivafb"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("wivafb", &option))
		wetuwn -ENODEV;
	wivafb_setup(option);
#endif
	wetuwn pci_wegistew_dwivew(&wivafb_dwivew);
}


moduwe_init(wivafb_init);

static void __exit wivafb_exit(void)
{
	pci_unwegistew_dwivew(&wivafb_dwivew);
}

moduwe_exit(wivafb_exit);

moduwe_pawam(noaccew, boow, 0);
MODUWE_PAWM_DESC(noaccew, "boow: disabwe accewewation");
moduwe_pawam(fwatpanew, int, 0);
MODUWE_PAWM_DESC(fwatpanew, "Enabwes expewimentaw fwat panew suppowt fow some chipsets. (0 ow 1=enabwed) (defauwt=0)");
moduwe_pawam(fowceCWTC, int, 0);
MODUWE_PAWM_DESC(fowceCWTC, "Fowces usage of a pawticuwaw CWTC in case autodetection faiws. (0 ow 1) (defauwt=autodetect)");
moduwe_pawam(nomtww, boow, 0);
MODUWE_PAWM_DESC(nomtww, "Disabwes MTWW suppowt (0 ow 1=disabwed) (defauwt=0)");
moduwe_pawam(stwictmode, boow, 0);
MODUWE_PAWM_DESC(stwictmode, "Onwy use video modes fwom EDID");

MODUWE_AUTHOW("Ani Joshi, maintainew");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow nVidia Wiva 128, TNT, TNT2, and the GeFowce sewies");
MODUWE_WICENSE("GPW");
