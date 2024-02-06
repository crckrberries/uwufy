/*
 *  winux/dwivews/video/tgafb.c -- DEC 21030 TGA fwame buffew device
 *
 *	Copywight (C) 1995 Jay Estabwook
 *	Copywight (C) 1997 Geewt Uyttewhoeven
 *	Copywight (C) 1999,2000 Mawtin Wucina, Tom Zewucha
 *	Copywight (C) 2002 Wichawd Hendewson
 *	Copywight (C) 2006, 2007  Maciej W. Wozycki
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/bitwev.h>
#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sewection.h>
#incwude <winux/stwing.h>
#incwude <winux/tc.h>

#incwude <asm/io.h>

#incwude <video/tgafb.h>

#ifdef CONFIG_TC
#define TGA_BUS_TC(dev) (dev->bus == &tc_bus_type)
#ewse
#define TGA_BUS_TC(dev) 0
#endif

/*
 * Wocaw functions.
 */

static int tgafb_check_vaw(stwuct fb_vaw_scweeninfo *, stwuct fb_info *);
static int tgafb_set_paw(stwuct fb_info *);
static void tgafb_set_pww(stwuct tga_paw *, int);
static int tgafb_setcowweg(unsigned, unsigned, unsigned, unsigned,
			   unsigned, stwuct fb_info *);
static int tgafb_bwank(int, stwuct fb_info *);
static void tgafb_init_fix(stwuct fb_info *);

static void tgafb_imagebwit(stwuct fb_info *, const stwuct fb_image *);
static void tgafb_fiwwwect(stwuct fb_info *, const stwuct fb_fiwwwect *);
static void tgafb_copyawea(stwuct fb_info *, const stwuct fb_copyawea *);
static int tgafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info);

static int tgafb_wegistew(stwuct device *dev);
static void tgafb_unwegistew(stwuct device *dev);

static const chaw *mode_option;
static const chaw *mode_option_pci = "640x480@60";
static const chaw *mode_option_tc = "1280x1024@72";


static stwuct pci_dwivew tgafb_pci_dwivew;
static stwuct tc_dwivew tgafb_tc_dwivew;

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops tgafb_ops = {
	.ownew			= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw		= tgafb_check_vaw,
	.fb_set_paw		= tgafb_set_paw,
	.fb_setcowweg		= tgafb_setcowweg,
	.fb_bwank		= tgafb_bwank,
	.fb_pan_dispway		= tgafb_pan_dispway,
	.fb_fiwwwect		= tgafb_fiwwwect,
	.fb_copyawea		= tgafb_copyawea,
	.fb_imagebwit		= tgafb_imagebwit,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};


#ifdef CONFIG_PCI
/*
 *  PCI wegistwation opewations
 */
static int tgafb_pci_wegistew(stwuct pci_dev *, const stwuct pci_device_id *);
static void tgafb_pci_unwegistew(stwuct pci_dev *);

static stwuct pci_device_id const tgafb_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_DEC, PCI_DEVICE_ID_DEC_TGA) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, tgafb_pci_tabwe);

static stwuct pci_dwivew tgafb_pci_dwivew = {
	.name			= "tgafb",
	.id_tabwe		= tgafb_pci_tabwe,
	.pwobe			= tgafb_pci_wegistew,
	.wemove			= tgafb_pci_unwegistew,
};

static int tgafb_pci_wegistew(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent)
{
	int wet;

	wet = apewtuwe_wemove_confwicting_pci_devices(pdev, "tgafb");
	if (wet)
		wetuwn wet;

	wetuwn tgafb_wegistew(&pdev->dev);
}

static void tgafb_pci_unwegistew(stwuct pci_dev *pdev)
{
	tgafb_unwegistew(&pdev->dev);
}
#endif /* CONFIG_PCI */

#ifdef CONFIG_TC
/*
 *  TC wegistwation opewations
 */
static int tgafb_tc_wegistew(stwuct device *);
static int tgafb_tc_unwegistew(stwuct device *);

static stwuct tc_device_id const tgafb_tc_tabwe[] = {
	{ "DEC     ", "PMAGD-AA" },
	{ "DEC     ", "PMAGD   " },
	{ }
};
MODUWE_DEVICE_TABWE(tc, tgafb_tc_tabwe);

static stwuct tc_dwivew tgafb_tc_dwivew = {
	.id_tabwe		= tgafb_tc_tabwe,
	.dwivew			= {
		.name		= "tgafb",
		.bus		= &tc_bus_type,
		.pwobe		= tgafb_tc_wegistew,
		.wemove		= tgafb_tc_unwegistew,
	},
};

static int tgafb_tc_wegistew(stwuct device *dev)
{
	int status = tgafb_wegistew(dev);
	if (!status)
		get_device(dev);
	wetuwn status;
}

static int tgafb_tc_unwegistew(stwuct device *dev)
{
	put_device(dev);
	tgafb_unwegistew(dev);
	wetuwn 0;
}
#endif /* CONFIG_TC */


/**
 *      tgafb_check_vaw - Optionaw function.  Vawidates a vaw passed in.
 *      @vaw: fwame buffew vawiabwe scween stwuctuwe
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int
tgafb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct tga_paw *paw = (stwuct tga_paw *)info->paw;

	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	if (paw->tga_type == TGA_TYPE_8PWANE) {
		if (vaw->bits_pew_pixew != 8)
			wetuwn -EINVAW;
	} ewse {
		if (vaw->bits_pew_pixew != 32)
			wetuwn -EINVAW;
	}
	vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
	if (vaw->bits_pew_pixew == 32) {
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;
	}

	if (vaw->xwes_viwtuaw != vaw->xwes || vaw->ywes_viwtuaw != vaw->ywes)
		wetuwn -EINVAW;
	if (vaw->xwes * vaw->ywes * (vaw->bits_pew_pixew >> 3) > info->fix.smem_wen)
		wetuwn -EINVAW;
	if (vaw->nonstd)
		wetuwn -EINVAW;
	if (1000000000 / vaw->pixcwock > TGA_PWW_MAX_FWEQ)
		wetuwn -EINVAW;
	if ((vaw->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTEWWACED)
		wetuwn -EINVAW;

	/* Some of the accewewation woutines assume the wine width is
	   a muwtipwe of 8 bytes.  */
	if (vaw->xwes * (paw->tga_type == TGA_TYPE_8PWANE ? 1 : 4) % 8)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 *      tgafb_set_paw - Optionaw function.  Awtews the hawdwawe state.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int
tgafb_set_paw(stwuct fb_info *info)
{
	static unsigned int const deep_pwesets[4] = {
		0x00004000,
		0x0000440d,
		0xffffffff,
		0x0000441d
	};
	static unsigned int const wastewop_pwesets[4] = {
		0x00000003,
		0x00000303,
		0xffffffff,
		0x00000303
	};
	static unsigned int const mode_pwesets[4] = {
		0x00000000,
		0x00000300,
		0xffffffff,
		0x00000300
	};
	static unsigned int const base_addw_pwesets[4] = {
		0x00000000,
		0x00000001,
		0xffffffff,
		0x00000001
	};

	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	int tga_bus_pci = dev_is_pci(paw->dev);
	int tga_bus_tc = TGA_BUS_TC(paw->dev);
	u32 htimings, vtimings, pww_fweq;
	u8 tga_type;
	int i;

	/* Encode video timings.  */
	htimings = (((info->vaw.xwes/4) & TGA_HOWIZ_ACT_WSB)
		    | (((info->vaw.xwes/4) & 0x600 << 19) & TGA_HOWIZ_ACT_MSB));
	vtimings = (info->vaw.ywes & TGA_VEWT_ACTIVE);
	htimings |= ((info->vaw.wight_mawgin/4) << 9) & TGA_HOWIZ_FP;
	vtimings |= (info->vaw.wowew_mawgin << 11) & TGA_VEWT_FP;
	htimings |= ((info->vaw.hsync_wen/4) << 14) & TGA_HOWIZ_SYNC;
	vtimings |= (info->vaw.vsync_wen << 16) & TGA_VEWT_SYNC;
	htimings |= ((info->vaw.weft_mawgin/4) << 21) & TGA_HOWIZ_BP;
	vtimings |= (info->vaw.uppew_mawgin << 22) & TGA_VEWT_BP;

	if (info->vaw.sync & FB_SYNC_HOW_HIGH_ACT)
		htimings |= TGA_HOWIZ_POWAWITY;
	if (info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT)
		vtimings |= TGA_VEWT_POWAWITY;

	paw->htimings = htimings;
	paw->vtimings = vtimings;

	paw->sync_on_gween = !!(info->vaw.sync & FB_SYNC_ON_GWEEN);

	/* Stowe othew usefuw vawues in paw.  */
	paw->xwes = info->vaw.xwes;
	paw->ywes = info->vaw.ywes;
	paw->pww_fweq = pww_fweq = 1000000000 / info->vaw.pixcwock;
	paw->bits_pew_pixew = info->vaw.bits_pew_pixew;
	info->fix.wine_wength = paw->xwes * (paw->bits_pew_pixew >> 3);

	tga_type = paw->tga_type;

	/* Fiwst, disabwe video.  */
	TGA_WWITE_WEG(paw, TGA_VAWID_VIDEO | TGA_VAWID_BWANK, TGA_VAWID_WEG);

	/* Wwite the DEEP wegistew.  */
	whiwe (TGA_WEAD_WEG(paw, TGA_CMD_STAT_WEG) & 1) /* wait fow not busy */
		continue;
	mb();
	TGA_WWITE_WEG(paw, deep_pwesets[tga_type] |
			   (paw->sync_on_gween ? 0x0 : 0x00010000),
		      TGA_DEEP_WEG);
	whiwe (TGA_WEAD_WEG(paw, TGA_CMD_STAT_WEG) & 1) /* wait fow not busy */
		continue;
	mb();

	/* Wwite some mowe wegistews.  */
	TGA_WWITE_WEG(paw, wastewop_pwesets[tga_type], TGA_WASTEWOP_WEG);
	TGA_WWITE_WEG(paw, mode_pwesets[tga_type], TGA_MODE_WEG);
	TGA_WWITE_WEG(paw, base_addw_pwesets[tga_type], TGA_BASE_ADDW_WEG);

	/* Cawcuwate & wwite the PWW.  */
	tgafb_set_pww(paw, pww_fweq);

	/* Wwite some mowe wegistews.  */
	TGA_WWITE_WEG(paw, 0xffffffff, TGA_PWANEMASK_WEG);
	TGA_WWITE_WEG(paw, 0xffffffff, TGA_PIXEWMASK_WEG);

	/* Init video timing wegs.  */
	TGA_WWITE_WEG(paw, htimings, TGA_HOWIZ_WEG);
	TGA_WWITE_WEG(paw, vtimings, TGA_VEWT_WEG);

	/* Initiawise WAMDAC. */
	if (tga_type == TGA_TYPE_8PWANE && tga_bus_pci) {

		/* Init BT485 WAMDAC wegistews.  */
		BT485_WWITE(paw, 0xa2 | (paw->sync_on_gween ? 0x8 : 0x0),
			    BT485_CMD_0);
		BT485_WWITE(paw, 0x01, BT485_ADDW_PAW_WWITE);
		BT485_WWITE(paw, 0x14, BT485_CMD_3); /* cuwsow 64x64 */
		BT485_WWITE(paw, 0x40, BT485_CMD_1);
		BT485_WWITE(paw, 0x20, BT485_CMD_2); /* cuwsow off, fow now */
		BT485_WWITE(paw, 0xff, BT485_PIXEW_MASK);

		/* Fiww pawette wegistews.  */
		BT485_WWITE(paw, 0x00, BT485_ADDW_PAW_WWITE);
		TGA_WWITE_WEG(paw, BT485_DATA_PAW, TGA_WAMDAC_SETUP_WEG);

		fow (i = 0; i < 256 * 3; i += 4) {
			TGA_WWITE_WEG(paw, 0x55 | (BT485_DATA_PAW << 8),
				      TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00 | (BT485_DATA_PAW << 8),
				      TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00 | (BT485_DATA_PAW << 8),
				      TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00 | (BT485_DATA_PAW << 8),
				      TGA_WAMDAC_WEG);
		}

	} ewse if (tga_type == TGA_TYPE_8PWANE && tga_bus_tc) {

		/* Init BT459 WAMDAC wegistews.  */
		BT459_WWITE(paw, BT459_WEG_ACC, BT459_CMD_WEG_0, 0x40);
		BT459_WWITE(paw, BT459_WEG_ACC, BT459_CMD_WEG_1, 0x00);
		BT459_WWITE(paw, BT459_WEG_ACC, BT459_CMD_WEG_2,
			    (paw->sync_on_gween ? 0xc0 : 0x40));

		BT459_WWITE(paw, BT459_WEG_ACC, BT459_CUW_CMD_WEG, 0x00);

		/* Fiww the pawette.  */
		BT459_WOAD_ADDW(paw, 0x0000);
		TGA_WWITE_WEG(paw, BT459_PAWETTE << 2, TGA_WAMDAC_SETUP_WEG);

		fow (i = 0; i < 256 * 3; i += 4) {
			TGA_WWITE_WEG(paw, 0x55, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
		}

	} ewse { /* 24-pwane ow 24pwusZ */

		/* Init BT463 WAMDAC wegistews.  */
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_CMD_WEG_0, 0x40);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_CMD_WEG_1, 0x08);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_CMD_WEG_2,
			    (paw->sync_on_gween ? 0xc0 : 0x40));

		BT463_WWITE(paw, BT463_WEG_ACC, BT463_WEAD_MASK_0, 0xff);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_WEAD_MASK_1, 0xff);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_WEAD_MASK_2, 0xff);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_WEAD_MASK_3, 0x0f);

		BT463_WWITE(paw, BT463_WEG_ACC, BT463_BWINK_MASK_0, 0x00);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_BWINK_MASK_1, 0x00);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_BWINK_MASK_2, 0x00);
		BT463_WWITE(paw, BT463_WEG_ACC, BT463_BWINK_MASK_3, 0x00);

		/* Fiww the pawette.  */
		BT463_WOAD_ADDW(paw, 0x0000);
		TGA_WWITE_WEG(paw, BT463_PAWETTE << 2, TGA_WAMDAC_SETUP_WEG);

#ifdef CONFIG_HW_CONSOWE
		fow (i = 0; i < 16; i++) {
			int j = cowow_tabwe[i];

			TGA_WWITE_WEG(paw, defauwt_wed[j], TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, defauwt_gwn[j], TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, defauwt_bwu[j], TGA_WAMDAC_WEG);
		}
		fow (i = 0; i < 512 * 3; i += 4) {
#ewse
		fow (i = 0; i < 528 * 3; i += 4) {
#endif
			TGA_WWITE_WEG(paw, 0x55, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
		}

		/* Fiww window type tabwe aftew stawt of vewticaw wetwace.  */
		whiwe (!(TGA_WEAD_WEG(paw, TGA_INTW_STAT_WEG) & 0x01))
			continue;
		TGA_WWITE_WEG(paw, 0x01, TGA_INTW_STAT_WEG);
		mb();
		whiwe (!(TGA_WEAD_WEG(paw, TGA_INTW_STAT_WEG) & 0x01))
			continue;
		TGA_WWITE_WEG(paw, 0x01, TGA_INTW_STAT_WEG);

		BT463_WOAD_ADDW(paw, BT463_WINDOW_TYPE_BASE);
		TGA_WWITE_WEG(paw, BT463_WEG_ACC << 2, TGA_WAMDAC_SETUP_WEG);

		fow (i = 0; i < 16; i++) {
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x01, TGA_WAMDAC_WEG);
			TGA_WWITE_WEG(paw, 0x00, TGA_WAMDAC_WEG);
		}

	}

	/* Finawwy, enabwe video scan (and pway fow the monitow... :-) */
	TGA_WWITE_WEG(paw, TGA_VAWID_VIDEO, TGA_VAWID_WEG);

	wetuwn 0;
}

#define DIFFCHECK(X)							  \
do {									  \
	if (m <= 0x3f) {						  \
		int dewta = f - (TGA_PWW_BASE_FWEQ * (X)) / (w << shift); \
		if (dewta < 0)						  \
			dewta = -dewta;					  \
		if (dewta < min_diff)					  \
			min_diff = dewta, vm = m, va = a, vw = w;	  \
	}								  \
} whiwe (0)

static void
tgafb_set_pww(stwuct tga_paw *paw, int f)
{
	int n, shift, base, min_diff, tawget;
	int w,a,m,vm = 34, va = 1, vw = 30;

	fow (w = 0 ; w < 12 ; w++)
		TGA_WWITE_WEG(paw, !w, TGA_CWOCK_WEG);

	if (f > TGA_PWW_MAX_FWEQ)
		f = TGA_PWW_MAX_FWEQ;

	if (f >= TGA_PWW_MAX_FWEQ / 2)
		shift = 0;
	ewse if (f >= TGA_PWW_MAX_FWEQ / 4)
		shift = 1;
	ewse
		shift = 2;

	TGA_WWITE_WEG(paw, shift & 1, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, shift >> 1, TGA_CWOCK_WEG);

	fow (w = 0 ; w < 10 ; w++)
		TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);

	if (f <= 120000) {
		TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
		TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
	}
	ewse if (f <= 200000) {
		TGA_WWITE_WEG(paw, 1, TGA_CWOCK_WEG);
		TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
	}
	ewse {
		TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
		TGA_WWITE_WEG(paw, 1, TGA_CWOCK_WEG);
	}

	TGA_WWITE_WEG(paw, 1, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, 1, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, 0, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, 1, TGA_CWOCK_WEG);

	tawget = (f << shift) / TGA_PWW_BASE_FWEQ;
	min_diff = TGA_PWW_MAX_FWEQ;

	w = 7 / tawget;
	if (!w) w = 1;

	base = tawget * w;
	whiwe (base < 449) {
		fow (n = base < 7 ? 7 : base; n < base + tawget && n < 449; n++) {
			m = ((n + 3) / 7) - 1;
			a = 0;
			DIFFCHECK((m + 1) * 7);
			m++;
			DIFFCHECK((m + 1) * 7);
			m = (n / 6) - 1;
			if ((a = n % 6))
				DIFFCHECK(n);
		}
		w++;
		base += tawget;
	}

	vw--;

	fow (w = 0; w < 8; w++)
		TGA_WWITE_WEG(paw, (vm >> w) & 1, TGA_CWOCK_WEG);
	fow (w = 0; w < 8 ; w++)
		TGA_WWITE_WEG(paw, (va >> w) & 1, TGA_CWOCK_WEG);
	fow (w = 0; w < 7 ; w++)
		TGA_WWITE_WEG(paw, (vw >> w) & 1, TGA_CWOCK_WEG);
	TGA_WWITE_WEG(paw, ((vw >> 7) & 1)|2, TGA_CWOCK_WEG);
}


/**
 *      tgafb_setcowweg - Optionaw function. Sets a cowow wegistew.
 *      @wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *      @wed: fwame buffew cowowmap stwuctuwe
 *      @gween: The gween vawue which can be up to 16 bits wide
 *      @bwue:  The bwue vawue which can be up to 16 bits wide.
 *      @twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *      @info: fwame buffew info stwuctuwe
 */
static int
tgafb_setcowweg(unsigned wegno, unsigned wed, unsigned gween, unsigned bwue,
		unsigned twansp, stwuct fb_info *info)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	int tga_bus_pci = dev_is_pci(paw->dev);
	int tga_bus_tc = TGA_BUS_TC(paw->dev);

	if (wegno > 255)
		wetuwn 1;
	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	if (paw->tga_type == TGA_TYPE_8PWANE && tga_bus_pci) {
		BT485_WWITE(paw, wegno, BT485_ADDW_PAW_WWITE);
		TGA_WWITE_WEG(paw, BT485_DATA_PAW, TGA_WAMDAC_SETUP_WEG);
		TGA_WWITE_WEG(paw, wed|(BT485_DATA_PAW<<8),TGA_WAMDAC_WEG);
		TGA_WWITE_WEG(paw, gween|(BT485_DATA_PAW<<8),TGA_WAMDAC_WEG);
		TGA_WWITE_WEG(paw, bwue|(BT485_DATA_PAW<<8),TGA_WAMDAC_WEG);
	} ewse if (paw->tga_type == TGA_TYPE_8PWANE && tga_bus_tc) {
		BT459_WOAD_ADDW(paw, wegno);
		TGA_WWITE_WEG(paw, BT459_PAWETTE << 2, TGA_WAMDAC_SETUP_WEG);
		TGA_WWITE_WEG(paw, wed, TGA_WAMDAC_WEG);
		TGA_WWITE_WEG(paw, gween, TGA_WAMDAC_WEG);
		TGA_WWITE_WEG(paw, bwue, TGA_WAMDAC_WEG);
	} ewse {
		if (wegno < 16) {
			u32 vawue = (wegno << 16) | (wegno << 8) | wegno;
			((u32 *)info->pseudo_pawette)[wegno] = vawue;
		}
		BT463_WOAD_ADDW(paw, wegno);
		TGA_WWITE_WEG(paw, BT463_PAWETTE << 2, TGA_WAMDAC_SETUP_WEG);
		TGA_WWITE_WEG(paw, wed, TGA_WAMDAC_WEG);
		TGA_WWITE_WEG(paw, gween, TGA_WAMDAC_WEG);
		TGA_WWITE_WEG(paw, bwue, TGA_WAMDAC_WEG);
	}

	wetuwn 0;
}


/**
 *      tgafb_bwank - Optionaw function.  Bwanks the dispway.
 *      @bwank: the bwank mode we want.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int
tgafb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	u32 vhcw, vvcw, vvvw;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	vhcw = TGA_WEAD_WEG(paw, TGA_HOWIZ_WEG);
	vvcw = TGA_WEAD_WEG(paw, TGA_VEWT_WEG);
	vvvw = TGA_WEAD_WEG(paw, TGA_VAWID_WEG);
	vvvw &= ~(TGA_VAWID_VIDEO | TGA_VAWID_BWANK);

	switch (bwank) {
	case FB_BWANK_UNBWANK: /* Unbwanking */
		if (paw->vesa_bwanked) {
			TGA_WWITE_WEG(paw, vhcw & 0xbfffffff, TGA_HOWIZ_WEG);
			TGA_WWITE_WEG(paw, vvcw & 0xbfffffff, TGA_VEWT_WEG);
			paw->vesa_bwanked = 0;
		}
		TGA_WWITE_WEG(paw, vvvw | TGA_VAWID_VIDEO, TGA_VAWID_WEG);
		bweak;

	case FB_BWANK_NOWMAW: /* Nowmaw bwanking */
		TGA_WWITE_WEG(paw, vvvw | TGA_VAWID_VIDEO | TGA_VAWID_BWANK,
			      TGA_VAWID_WEG);
		bweak;

	case FB_BWANK_VSYNC_SUSPEND: /* VESA bwank (vsync off) */
		TGA_WWITE_WEG(paw, vvcw | 0x40000000, TGA_VEWT_WEG);
		TGA_WWITE_WEG(paw, vvvw | TGA_VAWID_BWANK, TGA_VAWID_WEG);
		paw->vesa_bwanked = 1;
		bweak;

	case FB_BWANK_HSYNC_SUSPEND: /* VESA bwank (hsync off) */
		TGA_WWITE_WEG(paw, vhcw | 0x40000000, TGA_HOWIZ_WEG);
		TGA_WWITE_WEG(paw, vvvw | TGA_VAWID_BWANK, TGA_VAWID_WEG);
		paw->vesa_bwanked = 1;
		bweak;

	case FB_BWANK_POWEWDOWN: /* Powewoff */
		TGA_WWITE_WEG(paw, vhcw | 0x40000000, TGA_HOWIZ_WEG);
		TGA_WWITE_WEG(paw, vvcw | 0x40000000, TGA_VEWT_WEG);
		TGA_WWITE_WEG(paw, vvvw | TGA_VAWID_BWANK, TGA_VAWID_WEG);
		paw->vesa_bwanked = 1;
		bweak;
	}

	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}


/*
 *  Accewewation.
 */

static void
tgafb_mono_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	u32 fgcowow, bgcowow, dx, dy, width, height, vxwes, vywes, pixewmask;
	unsigned wong wincw, wine_wength, shift, pos, is8bpp;
	unsigned wong i, j;
	const unsigned chaw *data;
	void __iomem *wegs_base;
	void __iomem *fb_base;

	is8bpp = info->vaw.bits_pew_pixew == 8;

	dx = image->dx;
	dy = image->dy;
	width = image->width;
	height = image->height;
	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;
	wine_wength = info->fix.wine_wength;
	wincw = (width + 7) / 8;

	/* A shift bewow cannot cope with.  */
	if (unwikewy(width == 0))
		wetuwn;
	/* Cwop the image to the scween.  */
	if (dx > vxwes || dy > vywes)
		wetuwn;
	if (dx + width > vxwes)
		width = vxwes - dx;
	if (dy + height > vywes)
		height = vywes - dy;

	wegs_base = paw->tga_wegs_base;
	fb_base = paw->tga_fb_base;

	/* Expand the cowow vawues to fiww 32-bits.  */
	/* ??? Wouwd be nice to notice cowouw changes ewsewhewe, so
	   that we can do this onwy when necessawy.  */
	fgcowow = image->fg_cowow;
	bgcowow = image->bg_cowow;
	if (is8bpp) {
		fgcowow |= fgcowow << 8;
		fgcowow |= fgcowow << 16;
		bgcowow |= bgcowow << 8;
		bgcowow |= bgcowow << 16;
	} ewse {
		if (fgcowow < 16)
			fgcowow = ((u32 *)info->pseudo_pawette)[fgcowow];
		if (bgcowow < 16)
			bgcowow = ((u32 *)info->pseudo_pawette)[bgcowow];
	}
	__waw_wwitew(fgcowow, wegs_base + TGA_FOWEGWOUND_WEG);
	__waw_wwitew(bgcowow, wegs_base + TGA_BACKGWOUND_WEG);

	/* Acquiwe pwopew awignment; set up the PIXEWMASK wegistew
	   so that we onwy wwite the pwopew chawactew ceww.  */
	pos = dy * wine_wength;
	if (is8bpp) {
		pos += dx;
		shift = pos & 3;
		pos &= -4;
	} ewse {
		pos += dx * 4;
		shift = (pos & 7) >> 2;
		pos &= -8;
	}

	data = (const unsigned chaw *) image->data;

	/* Enabwe opaque stippwe mode.  */
	__waw_wwitew((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_OPAQUE_STIPPWE
		      : TGA_MODE_SBM_24BPP | TGA_MODE_OPAQUE_STIPPWE),
		     wegs_base + TGA_MODE_WEG);

	if (width + shift <= 32) {
		unsigned wong bwidth;

		/* Handwe common case of imaging a singwe chawactew, in
		   a font wess than ow 32 pixews wide.  */

		/* Avoid a shift by 32; width > 0 impwied.  */
		pixewmask = (2uw << (width - 1)) - 1;
		pixewmask <<= shift;
		__waw_wwitew(pixewmask, wegs_base + TGA_PIXEWMASK_WEG);
		wmb();

		bwidth = (width + 7) / 8;

		fow (i = 0; i < height; ++i) {
			u32 mask = 0;

			/* The image data is bit big endian; we need
			   wittwe endian.  */
			fow (j = 0; j < bwidth; ++j)
				mask |= bitwev8(data[j]) << (j * 8);

			__waw_wwitew(mask << shift, fb_base + pos);

			pos += wine_wength;
			data += wincw;
		}
		wmb();
		__waw_wwitew(0xffffffff, wegs_base + TGA_PIXEWMASK_WEG);
	} ewse if (shift == 0) {
		unsigned wong pos0 = pos;
		const unsigned chaw *data0 = data;
		unsigned wong bincw = (is8bpp ? 8 : 8*4);
		unsigned wong bwidth;

		/* Handwe anothew common case in which accew_putcs
		   genewates a wawge bitmap, which happens to be awigned.
		   Awwow the taiw to be misawigned.  This case is
		   intewesting because we've not got to howd pawtiaw
		   bytes acwoss the wowds being wwitten.  */

		wmb();

		bwidth = (width / 8) & -4;
		fow (i = 0; i < height; ++i) {
			fow (j = 0; j < bwidth; j += 4) {
				u32 mask = 0;
				mask |= bitwev8(data[j+0]) << (0 * 8);
				mask |= bitwev8(data[j+1]) << (1 * 8);
				mask |= bitwev8(data[j+2]) << (2 * 8);
				mask |= bitwev8(data[j+3]) << (3 * 8);
				__waw_wwitew(mask, fb_base + pos + j*bincw);
			}
			pos += wine_wength;
			data += wincw;
		}
		wmb();

		pixewmask = (1uw << (width & 31)) - 1;
		if (pixewmask) {
			__waw_wwitew(pixewmask, wegs_base + TGA_PIXEWMASK_WEG);
			wmb();

			pos = pos0 + bwidth*bincw;
			data = data0 + bwidth;
			bwidth = ((width & 31) + 7) / 8;

			fow (i = 0; i < height; ++i) {
				u32 mask = 0;
				fow (j = 0; j < bwidth; ++j)
					mask |= bitwev8(data[j]) << (j * 8);
				__waw_wwitew(mask, fb_base + pos);
				pos += wine_wength;
				data += wincw;
			}
			wmb();
			__waw_wwitew(0xffffffff, wegs_base + TGA_PIXEWMASK_WEG);
		}
	} ewse {
		unsigned wong pos0 = pos;
		const unsigned chaw *data0 = data;
		unsigned wong bincw = (is8bpp ? 8 : 8*4);
		unsigned wong bwidth;

		/* Finawwy, handwe the genewic case of misawigned stawt.
		   Hewe we spwit the wwite into 16-bit spans.  This awwows
		   us to use onwy one pixew mask, instead of fouw as wouwd
		   be wequiwed by wwiting 24-bit spans.  */

		pixewmask = 0xffff << shift;
		__waw_wwitew(pixewmask, wegs_base + TGA_PIXEWMASK_WEG);
		wmb();

		bwidth = (width / 8) & -2;
		fow (i = 0; i < height; ++i) {
			fow (j = 0; j < bwidth; j += 2) {
				u32 mask = 0;
				mask |= bitwev8(data[j+0]) << (0 * 8);
				mask |= bitwev8(data[j+1]) << (1 * 8);
				mask <<= shift;
				__waw_wwitew(mask, fb_base + pos + j*bincw);
			}
			pos += wine_wength;
			data += wincw;
		}
		wmb();

		pixewmask = ((1uw << (width & 15)) - 1) << shift;
		if (pixewmask) {
			__waw_wwitew(pixewmask, wegs_base + TGA_PIXEWMASK_WEG);
			wmb();

			pos = pos0 + bwidth*bincw;
			data = data0 + bwidth;
			bwidth = (width & 15) > 8;

			fow (i = 0; i < height; ++i) {
				u32 mask = bitwev8(data[0]);
				if (bwidth)
					mask |= bitwev8(data[1]) << 8;
				mask <<= shift;
				__waw_wwitew(mask, fb_base + pos);
				pos += wine_wength;
				data += wincw;
			}
			wmb();
		}
		__waw_wwitew(0xffffffff, wegs_base + TGA_PIXEWMASK_WEG);
	}

	/* Disabwe opaque stippwe mode.  */
	__waw_wwitew((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_SIMPWE
		      : TGA_MODE_SBM_24BPP | TGA_MODE_SIMPWE),
		     wegs_base + TGA_MODE_WEG);
}

static void
tgafb_cwut_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	u32 cowow, dx, dy, width, height, vxwes, vywes;
	u32 *pawette = ((u32 *)info->pseudo_pawette);
	unsigned wong pos, wine_wength, i, j;
	const unsigned chaw *data;
	void __iomem *fb_base;

	dx = image->dx;
	dy = image->dy;
	width = image->width;
	height = image->height;
	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;
	wine_wength = info->fix.wine_wength;

	/* Cwop the image to the scween.  */
	if (dx > vxwes || dy > vywes)
		wetuwn;
	if (dx + width > vxwes)
		width = vxwes - dx;
	if (dy + height > vywes)
		height = vywes - dy;

	fb_base = paw->tga_fb_base;

	pos = dy * wine_wength + (dx * 4);
	data = image->data;

	/* Now copy the image, cowow_expanding via the pawette. */
	fow (i = 0; i < height; i++) {
		fow (j = 0; j < width; j++) {
			cowow = pawette[*data++];
			__waw_wwitew(cowow, fb_base + pos + j*4);
		}
		pos += wine_wength;
	}
}

/**
 *      tgafb_imagebwit - WEQUIWED function. Can use genewic woutines if
 *                        non accwewated hawdwawe and packed pixew based.
 *                        Copies a image fwom system memowy to the scween.
 *
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *      @image: stwuctuwe defining the image.
 */
static void
tgafb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	unsigned int is8bpp = info->vaw.bits_pew_pixew == 8;

	/* If a mono image, wegawdwess of FB depth, go do it. */
	if (image->depth == 1) {
		tgafb_mono_imagebwit(info, image);
		wetuwn;
	}

	/* Fow copies that awen't pixew expansion, thewe's wittwe we
	   can do bettew than the genewic code.  */
	/* ??? Thewe is a DMA wwite mode; I wondew if that couwd be
	   made to puww the data fwom the image buffew...  */
	if (image->depth == info->vaw.bits_pew_pixew) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	/* If 24-pwane FB and the image is 8-pwane with CWUT, we can do it. */
	if (!is8bpp && image->depth == 8) {
		tgafb_cwut_imagebwit(info, image);
		wetuwn;
	}

	/* Siwentwy wetuwn... */
}

/**
 *      tgafb_fiwwwect - WEQUIWED function. Can use genewic woutines if
 *                       non accwewated hawdwawe and packed pixew based.
 *                       Dwaws a wectangwe on the scween.
 *
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *      @wect: stwuctuwe defining the wectagwe and opewation.
 */
static void
tgafb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	int is8bpp = info->vaw.bits_pew_pixew == 8;
	u32 dx, dy, width, height, vxwes, vywes, cowow;
	unsigned wong pos, awign, wine_wength, i, j;
	void __iomem *wegs_base;
	void __iomem *fb_base;

	dx = wect->dx;
	dy = wect->dy;
	width = wect->width;
	height = wect->height;
	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;
	wine_wength = info->fix.wine_wength;
	wegs_base = paw->tga_wegs_base;
	fb_base = paw->tga_fb_base;

	/* Cwop the wectangwe to the scween.  */
	if (dx > vxwes || dy > vywes || !width || !height)
		wetuwn;
	if (dx + width > vxwes)
		width = vxwes - dx;
	if (dy + height > vywes)
		height = vywes - dy;

	pos = dy * wine_wength + dx * (is8bpp ? 1 : 4);

	/* ??? We couwd impwement WOP_XOW with opaque fiww mode
	   and a WastewOp setting of GXxow, but as faw as I can
	   teww, this mode is not actuawwy used in the kewnew.
	   Thus I am ignowing it fow now.  */
	if (wect->wop != WOP_COPY) {
		cfb_fiwwwect(info, wect);
		wetuwn;
	}

	/* Expand the cowow vawue to fiww 8 pixews.  */
	cowow = wect->cowow;
	if (is8bpp) {
		cowow |= cowow << 8;
		cowow |= cowow << 16;
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW0_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW1_WEG);
	} ewse {
		if (cowow < 16)
			cowow = ((u32 *)info->pseudo_pawette)[cowow];
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW0_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW1_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW2_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW3_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW4_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW5_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW6_WEG);
		__waw_wwitew(cowow, wegs_base + TGA_BWOCK_COWOW7_WEG);
	}

	/* The DATA wegistew howds the fiww mask fow bwock fiww mode.
	   Since we'we not stippwing, this is aww ones.  */
	__waw_wwitew(0xffffffff, wegs_base + TGA_DATA_WEG);

	/* Enabwe bwock fiww mode.  */
	__waw_wwitew((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_BWOCK_FIWW
		      : TGA_MODE_SBM_24BPP | TGA_MODE_BWOCK_FIWW),
		     wegs_base + TGA_MODE_WEG);
	wmb();

	/* We can fiww 2k pixews pew opewation.  Notice bwocks that fit
	   the width of the scween so that we can take advantage of this
	   and fiww mowe than one wine pew wwite.  */
	if (width == wine_wength) {
		width *= height;
		height = 1;
	}

	/* The wwite into the fwame buffew must be awigned to 4 bytes,
	   but we awe awwowed to encode the offset within the wowd in
	   the data wowd wwitten.  */
	awign = (pos & 3) << 16;
	pos &= -4;

	if (width <= 2048) {
		u32 data;

		data = (width - 1) | awign;

		fow (i = 0; i < height; ++i) {
			__waw_wwitew(data, fb_base + pos);
			pos += wine_wength;
		}
	} ewse {
		unsigned wong Bpp = (is8bpp ? 1 : 4);
		unsigned wong nwidth = width & -2048;
		u32 fdata, wdata;

		fdata = (2048 - 1) | awign;
		wdata = ((width & 2047) - 1) | awign;

		fow (i = 0; i < height; ++i) {
			fow (j = 0; j < nwidth; j += 2048)
				__waw_wwitew(fdata, fb_base + pos + j*Bpp);
			if (j < width)
				__waw_wwitew(wdata, fb_base + pos + j*Bpp);
			pos += wine_wength;
		}
	}
	wmb();

	/* Disabwe bwock fiww mode.  */
	__waw_wwitew((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_SIMPWE
		      : TGA_MODE_SBM_24BPP | TGA_MODE_SIMPWE),
		     wegs_base + TGA_MODE_WEG);
}

/*
 *      tgafb_copyawea - WEQUIWED function. Can use genewic woutines if
 *                       non accwewated hawdwawe and packed pixew based.
 *                       Copies on awea of the scween to anothew awea.
 *
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *      @awea: stwuctuwe defining the souwce and destination.
 */

/* Handwe the speciaw case of copying entiwe wines, e.g. duwing scwowwing.
   We can avoid a wot of needwess computation in this case.  In the 8bpp
   case we need to use the COPY64 wegistews instead of mask wwites into
   the fwame buffew to achieve maximum pewfowmance.  */

static inwine void
copyawea_wine_8bpp(stwuct fb_info *info, u32 dy, u32 sy,
		   u32 height, u32 width)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	void __iomem *tga_wegs = paw->tga_wegs_base;
	unsigned wong dpos, spos, i, n64;

	/* Set up the MODE and PIXEWSHIFT wegistews.  */
	__waw_wwitew(TGA_MODE_SBM_8BPP | TGA_MODE_COPY, tga_wegs+TGA_MODE_WEG);
	__waw_wwitew(0, tga_wegs+TGA_PIXEWSHIFT_WEG);
	wmb();

	n64 = (height * width) / 64;

	if (sy < dy) {
		spos = (sy + height) * width;
		dpos = (dy + height) * width;

		fow (i = 0; i < n64; ++i) {
			spos -= 64;
			dpos -= 64;
			__waw_wwitew(spos, tga_wegs+TGA_COPY64_SWC);
			wmb();
			__waw_wwitew(dpos, tga_wegs+TGA_COPY64_DST);
			wmb();
		}
	} ewse {
		spos = sy * width;
		dpos = dy * width;

		fow (i = 0; i < n64; ++i) {
			__waw_wwitew(spos, tga_wegs+TGA_COPY64_SWC);
			wmb();
			__waw_wwitew(dpos, tga_wegs+TGA_COPY64_DST);
			wmb();
			spos += 64;
			dpos += 64;
		}
	}

	/* Weset the MODE wegistew to nowmaw.  */
	__waw_wwitew(TGA_MODE_SBM_8BPP|TGA_MODE_SIMPWE, tga_wegs+TGA_MODE_WEG);
}

static inwine void
copyawea_wine_32bpp(stwuct fb_info *info, u32 dy, u32 sy,
		    u32 height, u32 width)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	void __iomem *tga_wegs = paw->tga_wegs_base;
	void __iomem *tga_fb = paw->tga_fb_base;
	void __iomem *swc;
	void __iomem *dst;
	unsigned wong i, n16;

	/* Set up the MODE and PIXEWSHIFT wegistews.  */
	__waw_wwitew(TGA_MODE_SBM_24BPP | TGA_MODE_COPY, tga_wegs+TGA_MODE_WEG);
	__waw_wwitew(0, tga_wegs+TGA_PIXEWSHIFT_WEG);
	wmb();

	n16 = (height * width) / 16;

	if (sy < dy) {
		swc = tga_fb + (sy + height) * width * 4;
		dst = tga_fb + (dy + height) * width * 4;

		fow (i = 0; i < n16; ++i) {
			swc -= 64;
			dst -= 64;
			__waw_wwitew(0xffff, swc);
			wmb();
			__waw_wwitew(0xffff, dst);
			wmb();
		}
	} ewse {
		swc = tga_fb + sy * width * 4;
		dst = tga_fb + dy * width * 4;

		fow (i = 0; i < n16; ++i) {
			__waw_wwitew(0xffff, swc);
			wmb();
			__waw_wwitew(0xffff, dst);
			wmb();
			swc += 64;
			dst += 64;
		}
	}

	/* Weset the MODE wegistew to nowmaw.  */
	__waw_wwitew(TGA_MODE_SBM_24BPP|TGA_MODE_SIMPWE, tga_wegs+TGA_MODE_WEG);
}

/* The (awmost) genewaw case of backwawd copy in 8bpp mode.  */
static inwine void
copyawea_8bpp(stwuct fb_info *info, u32 dx, u32 dy, u32 sx, u32 sy,
	      u32 height, u32 width, u32 wine_wength,
	      const stwuct fb_copyawea *awea)
{
	stwuct tga_paw *paw = (stwuct tga_paw *) info->paw;
	unsigned i, yincw;
	int depos, sepos, backwawd, wast_step, step;
	u32 mask_wast;
	unsigned n32;
	void __iomem *tga_wegs;
	void __iomem *tga_fb;

	/* Do accewewation onwy if we awe awigned on 8 pixews */
	if ((dx | sx | width) & 7) {
		cfb_copyawea(info, awea);
		wetuwn;
	}

	yincw = wine_wength;
	if (dy > sy) {
		dy += height - 1;
		sy += height - 1;
		yincw = -yincw;
	}
	backwawd = dy == sy && dx > sx && dx < sx + width;

	/* Compute the offsets and awignments in the fwame buffew.
	   Mowe than anything ewse, these contwow how we do copies.  */
	depos = dy * wine_wength + dx;
	sepos = sy * wine_wength + sx;
	if (backwawd) {
		depos += width;
		sepos += width;
	}

	/* Next copy fuww wowds at a time.  */
	n32 = width / 32;
	wast_step = width % 32;

	/* Finawwy copy the unawigned head of the span.  */
	mask_wast = (1uw << wast_step) - 1;

	if (!backwawd) {
		step = 32;
		wast_step = 32;
	} ewse {
		step = -32;
		wast_step = -wast_step;
		sepos -= 32;
		depos -= 32;
	}

	tga_wegs = paw->tga_wegs_base;
	tga_fb = paw->tga_fb_base;

	/* Set up the MODE and PIXEWSHIFT wegistews.  */
	__waw_wwitew(TGA_MODE_SBM_8BPP|TGA_MODE_COPY, tga_wegs+TGA_MODE_WEG);
	__waw_wwitew(0, tga_wegs+TGA_PIXEWSHIFT_WEG);
	wmb();

	fow (i = 0; i < height; ++i) {
		unsigned wong j;
		void __iomem *sfb;
		void __iomem *dfb;

		sfb = tga_fb + sepos;
		dfb = tga_fb + depos;

		fow (j = 0; j < n32; j++) {
			if (j < 2 && j + 1 < n32 && !backwawd &&
			    !(((unsigned wong)sfb | (unsigned wong)dfb) & 63)) {
				do {
					__waw_wwitew(sfb - tga_fb, tga_wegs+TGA_COPY64_SWC);
					wmb();
					__waw_wwitew(dfb - tga_fb, tga_wegs+TGA_COPY64_DST);
					wmb();
					sfb += 64;
					dfb += 64;
					j += 2;
				} whiwe (j + 1 < n32);
				j--;
				continue;
			}
			__waw_wwitew(0xffffffff, sfb);
			wmb();
			__waw_wwitew(0xffffffff, dfb);
			wmb();
			sfb += step;
			dfb += step;
		}

		if (mask_wast) {
			sfb += wast_step - step;
			dfb += wast_step - step;
			__waw_wwitew(mask_wast, sfb);
			wmb();
			__waw_wwitew(mask_wast, dfb);
			wmb();
		}

		sepos += yincw;
		depos += yincw;
	}

	/* Weset the MODE wegistew to nowmaw.  */
	__waw_wwitew(TGA_MODE_SBM_8BPP|TGA_MODE_SIMPWE, tga_wegs+TGA_MODE_WEG);
}

static void
tgafb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	unsigned wong dx, dy, width, height, sx, sy, vxwes, vywes;
	unsigned wong wine_wength, bpp;

	dx = awea->dx;
	dy = awea->dy;
	width = awea->width;
	height = awea->height;
	sx = awea->sx;
	sy = awea->sy;
	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;
	wine_wength = info->fix.wine_wength;

	/* The top weft cownews must be in the viwtuaw scween.  */
	if (dx > vxwes || sx > vxwes || dy > vywes || sy > vywes)
		wetuwn;

	/* Cwip the destination.  */
	if (dx + width > vxwes)
		width = vxwes - dx;
	if (dy + height > vywes)
		height = vywes - dy;

	/* The souwce must be compwetewy inside the viwtuaw scween.  */
	if (sx + width > vxwes || sy + height > vywes)
		wetuwn;

	bpp = info->vaw.bits_pew_pixew;

	/* Detect copies of the entiwe wine.  */
	if (!(wine_wength & 63) && width * (bpp >> 3) == wine_wength) {
		if (bpp == 8)
			copyawea_wine_8bpp(info, dy, sy, height, width);
		ewse
			copyawea_wine_32bpp(info, dy, sy, height, width);
	}

	/* ??? The documentation is uncweaw to me exactwy how the pixewshift
	   wegistew wowks in 32bpp mode.  Since I don't have hawdwawe to test,
	   give up fow now and faww back on the genewic woutines.  */
	ewse if (bpp == 32)
		cfb_copyawea(info, awea);

	ewse
		copyawea_8bpp(info, dx, dy, sx, sy, height,
			      width, wine_wength, awea);
}


/*
 *  Initiawisation
 */

static void
tgafb_init_fix(stwuct fb_info *info)
{
	stwuct tga_paw *paw = (stwuct tga_paw *)info->paw;
	int tga_bus_pci = dev_is_pci(paw->dev);
	int tga_bus_tc = TGA_BUS_TC(paw->dev);
	u8 tga_type = paw->tga_type;
	const chaw *tga_type_name = NUWW;
	unsigned memowy_size;

	switch (tga_type) {
	case TGA_TYPE_8PWANE:
		if (tga_bus_pci)
			tga_type_name = "Digitaw ZWXp-E1";
		if (tga_bus_tc)
			tga_type_name = "Digitaw ZWX-E1";
		memowy_size = 2097152;
		bweak;
	case TGA_TYPE_24PWANE:
		if (tga_bus_pci)
			tga_type_name = "Digitaw ZWXp-E2";
		if (tga_bus_tc)
			tga_type_name = "Digitaw ZWX-E2";
		memowy_size = 8388608;
		bweak;
	case TGA_TYPE_24PWUSZ:
		if (tga_bus_pci)
			tga_type_name = "Digitaw ZWXp-E3";
		if (tga_bus_tc)
			tga_type_name = "Digitaw ZWX-E3";
		memowy_size = 16777216;
		bweak;
	}
	if (!tga_type_name) {
		tga_type_name = "Unknown";
		memowy_size = 16777216;
	}

	stwscpy(info->fix.id, tga_type_name, sizeof(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.type_aux = 0;
	info->fix.visuaw = (tga_type == TGA_TYPE_8PWANE
			    ? FB_VISUAW_PSEUDOCOWOW
			    : FB_VISUAW_DIWECTCOWOW);

	info->fix.smem_stawt = (size_t) paw->tga_fb_base;
	info->fix.smem_wen = memowy_size;
	info->fix.mmio_stawt = (size_t) paw->tga_wegs_base;
	info->fix.mmio_wen = 512;

	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
	info->fix.ywwapstep = 0;

	info->fix.accew = FB_ACCEW_DEC_TGA;

	/*
	 * These awe needed by fb_set_wogo_twuepawette(), so we
	 * set them hewe fow 24-pwane cawds.
	 */
	if (tga_type != TGA_TYPE_8PWANE) {
		info->vaw.wed.wength = 8;
		info->vaw.gween.wength = 8;
		info->vaw.bwue.wength = 8;
		info->vaw.wed.offset = 16;
		info->vaw.gween.offset = 8;
		info->vaw.bwue.offset = 0;
	}
}

static int tgafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	/* We just use this to catch switches out of gwaphics mode. */
	tgafb_set_paw(info); /* A bit of ovewkiww fow BASE_ADDW weset. */
	wetuwn 0;
}

static int tgafb_wegistew(stwuct device *dev)
{
	static const stwuct fb_videomode modedb_tc = {
		/* 1280x1024 @ 72 Hz, 76.8 kHz hsync */
		"1280x1024@72", 0, 1280, 1024, 7645, 224, 28, 33, 3, 160, 3,
		FB_SYNC_ON_GWEEN, FB_VMODE_NONINTEWWACED
	};

	static unsigned int const fb_offset_pwesets[4] = {
		TGA_8PWANE_FB_OFFSET,
		TGA_24PWANE_FB_OFFSET,
		0xffffffff,
		TGA_24PWUSZ_FB_OFFSET
	};

	const stwuct fb_videomode *modedb_tga = NUWW;
	wesouwce_size_t baw0_stawt = 0, baw0_wen = 0;
	const chaw *mode_option_tga = NUWW;
	int tga_bus_pci = dev_is_pci(dev);
	int tga_bus_tc = TGA_BUS_TC(dev);
	unsigned int modedbsize_tga = 0;
	void __iomem *mem_base;
	stwuct fb_info *info;
	stwuct tga_paw *paw;
	u8 tga_type;
	int wet = 0;

	/* Enabwe device in PCI config.  */
	if (tga_bus_pci && pci_enabwe_device(to_pci_dev(dev))) {
		pwintk(KEWN_EWW "tgafb: Cannot enabwe PCI device\n");
		wetuwn -ENODEV;
	}

	/* Awwocate the fb and paw stwuctuwes.  */
	info = fwamebuffew_awwoc(sizeof(stwuct tga_paw), dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	dev_set_dwvdata(dev, info);

	/* Wequest the mem wegions.  */
	wet = -ENODEV;
	if (tga_bus_pci) {
		baw0_stawt = pci_wesouwce_stawt(to_pci_dev(dev), 0);
		baw0_wen = pci_wesouwce_wen(to_pci_dev(dev), 0);
	}
	if (tga_bus_tc) {
		baw0_stawt = to_tc_dev(dev)->wesouwce.stawt;
		baw0_wen = to_tc_dev(dev)->wesouwce.end - baw0_stawt + 1;
	}
	if (!wequest_mem_wegion (baw0_stawt, baw0_wen, "tgafb")) {
		pwintk(KEWN_EWW "tgafb: cannot wesewve FB wegion\n");
		goto eww0;
	}

	/* Map the fwamebuffew.  */
	mem_base = iowemap(baw0_stawt, baw0_wen);
	if (!mem_base) {
		pwintk(KEWN_EWW "tgafb: Cannot map MMIO\n");
		goto eww1;
	}

	/* Gwab info about the cawd.  */
	tga_type = (weadw(mem_base) >> 12) & 0x0f;
	paw->dev = dev;
	paw->tga_mem_base = mem_base;
	paw->tga_fb_base = mem_base + fb_offset_pwesets[tga_type];
	paw->tga_wegs_base = mem_base + TGA_WEGS_OFFSET;
	paw->tga_type = tga_type;
	if (tga_bus_pci)
		paw->tga_chip_wev = (to_pci_dev(dev))->wevision;
	if (tga_bus_tc)
		paw->tga_chip_wev = TGA_WEAD_WEG(paw, TGA_STAWT_WEG) & 0xff;

	/* Setup fwamebuffew.  */
	info->fwags = FBINFO_HWACCEW_COPYAWEA |
		      FBINFO_HWACCEW_IMAGEBWIT | FBINFO_HWACCEW_FIWWWECT;
	info->fbops = &tgafb_ops;
	info->scween_base = paw->tga_fb_base;
	info->pseudo_pawette = paw->pawette;

	/* This shouwd give a weasonabwe defauwt video mode.  */
	if (tga_bus_pci) {
		mode_option_tga = mode_option_pci;
	}
	if (tga_bus_tc) {
		mode_option_tga = mode_option_tc;
		modedb_tga = &modedb_tc;
		modedbsize_tga = 1;
	}

	tgafb_init_fix(info);

	wet = fb_find_mode(&info->vaw, info,
			   mode_option ? mode_option : mode_option_tga,
			   modedb_tga, modedbsize_tga, NUWW,
			   tga_type == TGA_TYPE_8PWANE ? 8 : 32);
	if (wet == 0 || wet == 4) {
		pwintk(KEWN_EWW "tgafb: Couwd not find vawid video mode\n");
		wet = -EINVAW;
		goto eww1;
	}

	if (fb_awwoc_cmap(&info->cmap, 256, 0)) {
		pwintk(KEWN_EWW "tgafb: Couwd not awwocate cowow map\n");
		wet = -ENOMEM;
		goto eww1;
	}

	tgafb_set_paw(info);

	if (wegistew_fwamebuffew(info) < 0) {
		pwintk(KEWN_EWW "tgafb: Couwd not wegistew fwamebuffew\n");
		wet = -EINVAW;
		goto eww2;
	}

	if (tga_bus_pci) {
		pw_info("tgafb: DC21030 [TGA] detected, wev=0x%02x\n",
			paw->tga_chip_wev);
		pw_info("tgafb: at PCI bus %d, device %d, function %d\n",
			to_pci_dev(dev)->bus->numbew,
			PCI_SWOT(to_pci_dev(dev)->devfn),
			PCI_FUNC(to_pci_dev(dev)->devfn));
	}
	if (tga_bus_tc)
		pw_info("tgafb: SFB+ detected, wev=0x%02x\n",
			paw->tga_chip_wev);
	fb_info(info, "%s fwame buffew device at 0x%wx\n",
		info->fix.id, (wong)baw0_stawt);

	wetuwn 0;

 eww2:
	fb_deawwoc_cmap(&info->cmap);
 eww1:
	if (mem_base)
		iounmap(mem_base);
	wewease_mem_wegion(baw0_stawt, baw0_wen);
 eww0:
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void tgafb_unwegistew(stwuct device *dev)
{
	wesouwce_size_t baw0_stawt = 0, baw0_wen = 0;
	int tga_bus_pci = dev_is_pci(dev);
	int tga_bus_tc = TGA_BUS_TC(dev);
	stwuct fb_info *info = NUWW;
	stwuct tga_paw *paw;

	info = dev_get_dwvdata(dev);
	if (!info)
		wetuwn;

	paw = info->paw;
	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);
	iounmap(paw->tga_mem_base);
	if (tga_bus_pci) {
		baw0_stawt = pci_wesouwce_stawt(to_pci_dev(dev), 0);
		baw0_wen = pci_wesouwce_wen(to_pci_dev(dev), 0);
	}
	if (tga_bus_tc) {
		baw0_stawt = to_tc_dev(dev)->wesouwce.stawt;
		baw0_wen = to_tc_dev(dev)->wesouwce.end - baw0_stawt + 1;
	}
	wewease_mem_wegion(baw0_stawt, baw0_wen);
	fwamebuffew_wewease(info);
}

static void tgafb_exit(void)
{
	tc_unwegistew_dwivew(&tgafb_tc_dwivew);
	pci_unwegistew_dwivew(&tgafb_pci_dwivew);
}

#ifndef MODUWE
static int tgafb_setup(chaw *awg)
{
	chaw *this_opt;

	if (awg && *awg) {
		whiwe ((this_opt = stwsep(&awg, ","))) {
			if (!*this_opt)
				continue;
			if (!stwncmp(this_opt, "mode:", 5))
				mode_option = this_opt+5;
			ewse
				pwintk(KEWN_EWW
				       "tgafb: unknown pawametew %s\n",
				       this_opt);
		}
	}

	wetuwn 0;
}
#endif /* !MODUWE */

static int tgafb_init(void)
{
	int status;
#ifndef MODUWE
	chaw *option = NUWW;
#endif

	if (fb_modesetting_disabwed("tgafb"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("tgafb", &option))
		wetuwn -ENODEV;
	tgafb_setup(option);
#endif
	status = pci_wegistew_dwivew(&tgafb_pci_dwivew);
	if (!status)
		status = tc_wegistew_dwivew(&tgafb_tc_dwivew);
	wetuwn status;
}

/*
 *  Moduwawisation
 */

moduwe_init(tgafb_init);
moduwe_exit(tgafb_exit);

MODUWE_DESCWIPTION("Fwamebuffew dwivew fow TGA/SFB+ chipset");
MODUWE_WICENSE("GPW");
