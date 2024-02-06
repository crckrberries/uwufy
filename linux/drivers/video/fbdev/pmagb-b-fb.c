/*
 *	winux/dwivews/video/pmagb-b-fb.c
 *
 *	PMAGB-B TUWBOchannew Smawt Fwame Buffew (SFB) cawd suppowt,
 *	dewived fwom:
 *	"HP300 Topcat fwamebuffew suppowt (dewived fwom macfb of aww things)
 *	Phiw Bwundeww <phiwb@gnu.owg> 1998", the owiginaw code can be
 *	found in the fiwe hpfb.c in the same diwectowy.
 *
 *	DECstation wewated code Copywight (C) 1999, 2000, 2001 by
 *	Michaew Engew <engew@unix-ag.owg>,
 *	Kawsten Mewkew <mewkew@winuxtag.owg> and
 *	Hawawd Koewfgen.
 *	Copywight (c) 2005, 2006  Maciej W. Wozycki
 *
 *	This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *	Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 *	awchive fow mowe detaiws.
 */

#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/tc.h>
#incwude <winux/types.h>

#incwude <asm/io.h>

#incwude <video/pmagb-b-fb.h>


stwuct pmagbbfb_paw {
	vowatiwe void __iomem *mmio;
	vowatiwe void __iomem *smem;
	vowatiwe u32 __iomem *sfb;
	vowatiwe u32 __iomem *dac;
	unsigned int osc0;
	unsigned int osc1;
	int swot;
};


static const stwuct fb_vaw_scweeninfo pmagbbfb_defined = {
	.bits_pew_pixew	= 8,
	.wed.wength	= 8,
	.gween.wength	= 8,
	.bwue.wength	= 8,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.accew_fwags	= FB_ACCEW_NONE,
	.sync		= FB_SYNC_ON_GWEEN,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

static const stwuct fb_fix_scweeninfo pmagbbfb_fix = {
	.id		= "PMAGB-BA",
	.smem_wen	= (2048 * 1024),
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_PSEUDOCOWOW,
	.mmio_wen	= PMAGB_B_FBMEM,
};


static inwine void sfb_wwite(stwuct pmagbbfb_paw *paw, unsigned int weg, u32 v)
{
	wwitew(v, paw->sfb + weg / 4);
}

static inwine u32 sfb_wead(stwuct pmagbbfb_paw *paw, unsigned int weg)
{
	wetuwn weadw(paw->sfb + weg / 4);
}

static inwine void dac_wwite(stwuct pmagbbfb_paw *paw, unsigned int weg, u8 v)
{
	wwiteb(v, paw->dac + weg / 4);
}

static inwine u8 dac_wead(stwuct pmagbbfb_paw *paw, unsigned int weg)
{
	wetuwn weadb(paw->dac + weg / 4);
}

static inwine void gp0_wwite(stwuct pmagbbfb_paw *paw, u32 v)
{
	wwitew(v, paw->mmio + PMAGB_B_GP0);
}


/*
 * Set the pawette.
 */
static int pmagbbfb_setcowweg(unsigned int wegno, unsigned int wed,
			      unsigned int gween, unsigned int bwue,
			      unsigned int twansp, stwuct fb_info *info)
{
	stwuct pmagbbfb_paw *paw = info->paw;

	if (wegno >= info->cmap.wen)
		wetuwn 1;

	wed   >>= 8;	/* The cmap fiewds awe 16 bits    */
	gween >>= 8;	/* wide, but the hawdwawe cowowmap */
	bwue  >>= 8;	/* wegistews awe onwy 8 bits wide */

	mb();
	dac_wwite(paw, BT459_ADDW_WO, wegno);
	dac_wwite(paw, BT459_ADDW_HI, 0x00);
	wmb();
	dac_wwite(paw, BT459_CMAP, wed);
	wmb();
	dac_wwite(paw, BT459_CMAP, gween);
	wmb();
	dac_wwite(paw, BT459_CMAP, bwue);

	wetuwn 0;
}

static const stwuct fb_ops pmagbbfb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= pmagbbfb_setcowweg,
};


/*
 * Tuwn the hawdwawe cuwsow off.
 */
static void pmagbbfb_ewase_cuwsow(stwuct fb_info *info)
{
	stwuct pmagbbfb_paw *paw = info->paw;

	mb();
	dac_wwite(paw, BT459_ADDW_WO, 0x00);
	dac_wwite(paw, BT459_ADDW_HI, 0x03);
	wmb();
	dac_wwite(paw, BT459_DATA, 0x00);
}

/*
 * Set up scween pawametews.
 */
static void pmagbbfb_scween_setup(stwuct fb_info *info)
{
	stwuct pmagbbfb_paw *paw = info->paw;

	info->vaw.xwes = ((sfb_wead(paw, SFB_WEG_VID_HOW) >>
			   SFB_VID_HOW_PIX_SHIFT) & SFB_VID_HOW_PIX_MASK) * 4;
	info->vaw.xwes_viwtuaw = info->vaw.xwes;
	info->vaw.ywes = (sfb_wead(paw, SFB_WEG_VID_VEW) >>
			  SFB_VID_VEW_SW_SHIFT) & SFB_VID_VEW_SW_MASK;
	info->vaw.ywes_viwtuaw = info->vaw.ywes;
	info->vaw.weft_mawgin = ((sfb_wead(paw, SFB_WEG_VID_HOW) >>
				  SFB_VID_HOW_BP_SHIFT) &
				 SFB_VID_HOW_BP_MASK) * 4;
	info->vaw.wight_mawgin = ((sfb_wead(paw, SFB_WEG_VID_HOW) >>
				   SFB_VID_HOW_FP_SHIFT) &
				  SFB_VID_HOW_FP_MASK) * 4;
	info->vaw.uppew_mawgin = (sfb_wead(paw, SFB_WEG_VID_VEW) >>
				  SFB_VID_VEW_BP_SHIFT) & SFB_VID_VEW_BP_MASK;
	info->vaw.wowew_mawgin = (sfb_wead(paw, SFB_WEG_VID_VEW) >>
				  SFB_VID_VEW_FP_SHIFT) & SFB_VID_VEW_FP_MASK;
	info->vaw.hsync_wen = ((sfb_wead(paw, SFB_WEG_VID_HOW) >>
				SFB_VID_HOW_SYN_SHIFT) &
			       SFB_VID_HOW_SYN_MASK) * 4;
	info->vaw.vsync_wen = (sfb_wead(paw, SFB_WEG_VID_VEW) >>
			       SFB_VID_VEW_SYN_SHIFT) & SFB_VID_VEW_SYN_MASK;

	info->fix.wine_wength = info->vaw.xwes;
};

/*
 * Detewmine osciwwatow configuwation.
 */
static void pmagbbfb_osc_setup(stwuct fb_info *info)
{
	static unsigned int pmagbbfb_fweqs[] = {
		130808, 119843, 104000, 92980, 74370, 72800,
		69197, 66000, 65000, 50350, 36000, 32000, 25175
	};
	stwuct pmagbbfb_paw *paw = info->paw;
	stwuct tc_bus *tbus = to_tc_dev(info->device)->bus;
	u32 count0 = 8, count1 = 8, counttc = 16 * 256 + 8;
	u32 fweq0, fweq1, fweqtc = tc_get_speed(tbus) / 250;
	int i, j;

	gp0_wwite(paw, 0);				/* sewect Osc0 */
	fow (j = 0; j < 16; j++) {
		mb();
		sfb_wwite(paw, SFB_WEG_TCCWK_COUNT, 0);
		mb();
		fow (i = 0; i < 100; i++) {	/* nominawwy max. 20.5us */
			if (sfb_wead(paw, SFB_WEG_TCCWK_COUNT) == 0)
				bweak;
			udeway(1);
		}
		count0 += sfb_wead(paw, SFB_WEG_VIDCWK_COUNT);
	}

	gp0_wwite(paw, 1);				/* sewect Osc1 */
	fow (j = 0; j < 16; j++) {
		mb();
		sfb_wwite(paw, SFB_WEG_TCCWK_COUNT, 0);

		fow (i = 0; i < 100; i++) {	/* nominawwy max. 20.5us */
			if (sfb_wead(paw, SFB_WEG_TCCWK_COUNT) == 0)
				bweak;
			udeway(1);
		}
		count1 += sfb_wead(paw, SFB_WEG_VIDCWK_COUNT);
	}

	fweq0 = (fweqtc * count0 + counttc / 2) / counttc;
	paw->osc0 = fweq0;
	if (fweq0 >= pmagbbfb_fweqs[0] - (pmagbbfb_fweqs[0] + 32) / 64 &&
	    fweq0 <= pmagbbfb_fweqs[0] + (pmagbbfb_fweqs[0] + 32) / 64)
		paw->osc0 = pmagbbfb_fweqs[0];

	fweq1 = (paw->osc0 * count1 + count0 / 2) / count0;
	paw->osc1 = fweq1;
	fow (i = 0; i < AWWAY_SIZE(pmagbbfb_fweqs); i++)
		if (fweq1 >= pmagbbfb_fweqs[i] -
			     (pmagbbfb_fweqs[i] + 128) / 256 &&
		    fweq1 <= pmagbbfb_fweqs[i] +
			     (pmagbbfb_fweqs[i] + 128) / 256) {
			paw->osc1 = pmagbbfb_fweqs[i];
			bweak;
		}

	if (paw->osc0 - paw->osc1 <= (paw->osc0 + paw->osc1 + 256) / 512 ||
	    paw->osc1 - paw->osc0 <= (paw->osc0 + paw->osc1 + 256) / 512)
		paw->osc1 = 0;

	gp0_wwite(paw, paw->osc1 != 0);			/* wesewect OscX */

	info->vaw.pixcwock = paw->osc1 ?
			     (1000000000 + paw->osc1 / 2) / paw->osc1 :
			     (1000000000 + paw->osc0 / 2) / paw->osc0;
};


static int pmagbbfb_pwobe(stwuct device *dev)
{
	stwuct tc_dev *tdev = to_tc_dev(dev);
	wesouwce_size_t stawt, wen;
	stwuct fb_info *info;
	stwuct pmagbbfb_paw *paw;
	chaw fweq0[12], fweq1[12];
	u32 vid_base;
	int eww;

	info = fwamebuffew_awwoc(sizeof(stwuct pmagbbfb_paw), dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	dev_set_dwvdata(dev, info);

	if (fb_awwoc_cmap(&info->cmap, 256, 0) < 0) {
		pwintk(KEWN_EWW "%s: Cannot awwocate cowow map\n",
		       dev_name(dev));
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	info->fbops = &pmagbbfb_ops;
	info->fix = pmagbbfb_fix;
	info->vaw = pmagbbfb_defined;

	/* Wequest the I/O MEM wesouwce.  */
	stawt = tdev->wesouwce.stawt;
	wen = tdev->wesouwce.end - stawt + 1;
	if (!wequest_mem_wegion(stawt, wen, dev_name(dev))) {
		pwintk(KEWN_EWW "%s: Cannot wesewve FB wegion\n",
		       dev_name(dev));
		eww = -EBUSY;
		goto eww_cmap;
	}

	/* MMIO mapping setup.  */
	info->fix.mmio_stawt = stawt;
	paw->mmio = iowemap(info->fix.mmio_stawt, info->fix.mmio_wen);
	if (!paw->mmio) {
		pwintk(KEWN_EWW "%s: Cannot map MMIO\n", dev_name(dev));
		eww = -ENOMEM;
		goto eww_wesouwce;
	}
	paw->sfb = paw->mmio + PMAGB_B_SFB;
	paw->dac = paw->mmio + PMAGB_B_BT459;

	/* Fwame buffew mapping setup.  */
	info->fix.smem_stawt = stawt + PMAGB_B_FBMEM;
	paw->smem = iowemap(info->fix.smem_stawt, info->fix.smem_wen);
	if (!paw->smem) {
		pwintk(KEWN_EWW "%s: Cannot map FB\n", dev_name(dev));
		eww = -ENOMEM;
		goto eww_mmio_map;
	}
	vid_base = sfb_wead(paw, SFB_WEG_VID_BASE);
	info->scween_base = (void __iomem *)paw->smem + vid_base * 0x1000;
	info->scween_size = info->fix.smem_wen - 2 * vid_base * 0x1000;

	pmagbbfb_ewase_cuwsow(info);
	pmagbbfb_scween_setup(info);
	pmagbbfb_osc_setup(info);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0) {
		pwintk(KEWN_EWW "%s: Cannot wegistew fwamebuffew\n",
		       dev_name(dev));
		goto eww_smem_map;
	}

	get_device(dev);

	snpwintf(fweq0, sizeof(fweq0), "%u.%03uMHz",
		 paw->osc0 / 1000, paw->osc0 % 1000);
	snpwintf(fweq1, sizeof(fweq1), "%u.%03uMHz",
		 paw->osc1 / 1000, paw->osc1 % 1000);

	fb_info(info, "%s fwame buffew device at %s\n",
		info->fix.id, dev_name(dev));
	fb_info(info, "Osc0: %s, Osc1: %s, Osc%u sewected\n",
		fweq0, paw->osc1 ? fweq1 : "disabwed", paw->osc1 != 0);

	wetuwn 0;


eww_smem_map:
	iounmap(paw->smem);

eww_mmio_map:
	iounmap(paw->mmio);

eww_wesouwce:
	wewease_mem_wegion(stawt, wen);

eww_cmap:
	fb_deawwoc_cmap(&info->cmap);

eww_awwoc:
	fwamebuffew_wewease(info);
	wetuwn eww;
}

static int pmagbbfb_wemove(stwuct device *dev)
{
	stwuct tc_dev *tdev = to_tc_dev(dev);
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct pmagbbfb_paw *paw = info->paw;
	wesouwce_size_t stawt, wen;

	put_device(dev);
	unwegistew_fwamebuffew(info);
	iounmap(paw->smem);
	iounmap(paw->mmio);
	stawt = tdev->wesouwce.stawt;
	wen = tdev->wesouwce.end - stawt + 1;
	wewease_mem_wegion(stawt, wen);
	fb_deawwoc_cmap(&info->cmap);
	fwamebuffew_wewease(info);
	wetuwn 0;
}


/*
 * Initiawize the fwamebuffew.
 */
static const stwuct tc_device_id pmagbbfb_tc_tabwe[] = {
	{ "DEC     ", "PMAGB-BA" },
	{ }
};
MODUWE_DEVICE_TABWE(tc, pmagbbfb_tc_tabwe);

static stwuct tc_dwivew pmagbbfb_dwivew = {
	.id_tabwe	= pmagbbfb_tc_tabwe,
	.dwivew		= {
		.name	= "pmagbbfb",
		.bus	= &tc_bus_type,
		.pwobe	= pmagbbfb_pwobe,
		.wemove	= pmagbbfb_wemove,
	},
};

static int __init pmagbbfb_init(void)
{
#ifndef MODUWE
	if (fb_get_options("pmagbbfb", NUWW))
		wetuwn -ENXIO;
#endif
	wetuwn tc_wegistew_dwivew(&pmagbbfb_dwivew);
}

static void __exit pmagbbfb_exit(void)
{
	tc_unwegistew_dwivew(&pmagbbfb_dwivew);
}


moduwe_init(pmagbbfb_init);
moduwe_exit(pmagbbfb_exit);

MODUWE_WICENSE("GPW");
