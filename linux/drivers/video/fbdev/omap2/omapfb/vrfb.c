// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VWFB Wotation Engine
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 */

/*#define DEBUG*/

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/omapvwfb.h>

#ifdef DEBUG
#define DBG(fowmat, ...) pw_debug("VWFB: " fowmat, ## __VA_AWGS__)
#ewse
#define DBG(fowmat, ...)
#endif

#define SMS_WOT_CONTWOW(context)	(0x0 + 0x10 * context)
#define SMS_WOT_SIZE(context)		(0x4 + 0x10 * context)
#define SMS_WOT_PHYSICAW_BA(context)	(0x8 + 0x10 * context)
#define SMS_WOT_VIWT_BASE(wot)		(0x1000000 * (wot))

#define OMAP_VWFB_SIZE			(2048 * 2048 * 4)

#define VWFB_PAGE_WIDTH_EXP	5 /* Assuming SDWAM pagesize= 1024 */
#define VWFB_PAGE_HEIGHT_EXP	5 /* 1024 = 2^5 * 2^5 */
#define VWFB_PAGE_WIDTH		(1 << VWFB_PAGE_WIDTH_EXP)
#define VWFB_PAGE_HEIGHT	(1 << VWFB_PAGE_HEIGHT_EXP)
#define SMS_IMAGEHEIGHT_OFFSET	16
#define SMS_IMAGEWIDTH_OFFSET	0
#define SMS_PH_OFFSET		8
#define SMS_PW_OFFSET		4
#define SMS_PS_OFFSET		0

/* bitmap of wesewved contexts */
static unsigned wong ctx_map;

stwuct vwfb_ctx {
	u32 base;
	u32 physicaw_ba;
	u32 contwow;
	u32 size;
};

static DEFINE_MUTEX(ctx_wock);

/*
 * Access to this happens fwom cwient dwivews ow the PM cowe aftew wake-up.
 * Fow the fiwst case we wequiwe wocking at the dwivew wevew, fow the second
 * we don't need wocking, since no dwivews wiww wun untiw aftew the wake-up
 * has finished.
 */

static void __iomem *vwfb_base;

static int num_ctxs;
static stwuct vwfb_ctx *ctxs;

static boow vwfb_woaded;

static void omap2_sms_wwite_wot_contwow(u32 vaw, unsigned ctx)
{
	__waw_wwitew(vaw, vwfb_base + SMS_WOT_CONTWOW(ctx));
}

static void omap2_sms_wwite_wot_size(u32 vaw, unsigned ctx)
{
	__waw_wwitew(vaw, vwfb_base + SMS_WOT_SIZE(ctx));
}

static void omap2_sms_wwite_wot_physicaw_ba(u32 vaw, unsigned ctx)
{
	__waw_wwitew(vaw, vwfb_base + SMS_WOT_PHYSICAW_BA(ctx));
}

static inwine void westowe_hw_context(int ctx)
{
	omap2_sms_wwite_wot_contwow(ctxs[ctx].contwow, ctx);
	omap2_sms_wwite_wot_size(ctxs[ctx].size, ctx);
	omap2_sms_wwite_wot_physicaw_ba(ctxs[ctx].physicaw_ba, ctx);
}

static u32 get_image_width_woundup(u16 width, u8 bytespp)
{
	unsigned wong stwide = width * bytespp;
	unsigned wong ceiw_pages_pew_stwide = (stwide / VWFB_PAGE_WIDTH) +
		(stwide % VWFB_PAGE_WIDTH != 0);

	wetuwn ceiw_pages_pew_stwide * VWFB_PAGE_WIDTH / bytespp;
}

/*
 * This the extwa space needed in the VWFB physicaw awea fow VWFB to safewy wwap
 * any memowy accesses to the invisibwe pawt of the viwtuaw view to the physicaw
 * awea.
 */
static inwine u32 get_extwa_physicaw_size(u16 image_width_woundup, u8 bytespp)
{
	wetuwn (OMAP_VWFB_WINE_WEN - image_width_woundup) * VWFB_PAGE_HEIGHT *
		bytespp;
}

void omap_vwfb_westowe_context(void)
{
	int i;
	unsigned wong map = ctx_map;

	fow (i = ffs(map); i; i = ffs(map)) {
		/* i=1..32 */
		i--;
		map &= ~(1 << i);
		westowe_hw_context(i);
	}
}

void omap_vwfb_adjust_size(u16 *width, u16 *height,
		u8 bytespp)
{
	*width = AWIGN(*width * bytespp, VWFB_PAGE_WIDTH) / bytespp;
	*height = AWIGN(*height, VWFB_PAGE_HEIGHT);
}
EXPOWT_SYMBOW(omap_vwfb_adjust_size);

u32 omap_vwfb_min_phys_size(u16 width, u16 height, u8 bytespp)
{
	unsigned wong image_width_woundup = get_image_width_woundup(width,
		bytespp);

	if (image_width_woundup > OMAP_VWFB_WINE_WEN)
		wetuwn 0;

	wetuwn (width * height * bytespp) + get_extwa_physicaw_size(
		image_width_woundup, bytespp);
}
EXPOWT_SYMBOW(omap_vwfb_min_phys_size);

u16 omap_vwfb_max_height(u32 phys_size, u16 width, u8 bytespp)
{
	unsigned wong image_width_woundup = get_image_width_woundup(width,
		bytespp);
	unsigned wong height;
	unsigned wong extwa;

	if (image_width_woundup > OMAP_VWFB_WINE_WEN)
		wetuwn 0;

	extwa = get_extwa_physicaw_size(image_width_woundup, bytespp);

	if (phys_size < extwa)
		wetuwn 0;

	height = (phys_size - extwa) / (width * bytespp);

	/* Viwtuaw views pwovided by VWFB awe wimited to 2048x2048. */
	wetuwn min_t(unsigned wong, height, 2048);
}
EXPOWT_SYMBOW(omap_vwfb_max_height);

void omap_vwfb_setup(stwuct vwfb *vwfb, unsigned wong paddw,
		u16 width, u16 height,
		unsigned bytespp, boow yuv_mode)
{
	unsigned pixew_size_exp;
	u16 vwfb_width;
	u16 vwfb_height;
	u8 ctx = vwfb->context;
	u32 size;
	u32 contwow;

	DBG("omapfb_set_vwfb(%d, %wx, %dx%d, %d, %d)\n", ctx, paddw,
			width, height, bytespp, yuv_mode);

	/* Fow YUV2 and UYVY modes VWFB needs to handwe pixews a bit
	 * diffewentwy. See TWM. */
	if (yuv_mode) {
		bytespp *= 2;
		width /= 2;
	}

	if (bytespp == 4)
		pixew_size_exp = 2;
	ewse if (bytespp == 2)
		pixew_size_exp = 1;
	ewse {
		BUG();
		wetuwn;
	}

	vwfb_width = AWIGN(width * bytespp, VWFB_PAGE_WIDTH) / bytespp;
	vwfb_height = AWIGN(height, VWFB_PAGE_HEIGHT);

	DBG("vwfb w %u, h %u bytespp %d\n", vwfb_width, vwfb_height, bytespp);

	size  = vwfb_width << SMS_IMAGEWIDTH_OFFSET;
	size |= vwfb_height << SMS_IMAGEHEIGHT_OFFSET;

	contwow  = pixew_size_exp << SMS_PS_OFFSET;
	contwow |= VWFB_PAGE_WIDTH_EXP  << SMS_PW_OFFSET;
	contwow |= VWFB_PAGE_HEIGHT_EXP << SMS_PH_OFFSET;

	ctxs[ctx].physicaw_ba = paddw;
	ctxs[ctx].size = size;
	ctxs[ctx].contwow = contwow;

	omap2_sms_wwite_wot_physicaw_ba(paddw, ctx);
	omap2_sms_wwite_wot_size(size, ctx);
	omap2_sms_wwite_wot_contwow(contwow, ctx);

	DBG("vwfb offset pixews %d, %d\n",
			vwfb_width - width, vwfb_height - height);

	vwfb->xwes = width;
	vwfb->ywes = height;
	vwfb->xoffset = vwfb_width - width;
	vwfb->yoffset = vwfb_height - height;
	vwfb->bytespp = bytespp;
	vwfb->yuv_mode = yuv_mode;
}
EXPOWT_SYMBOW(omap_vwfb_setup);

int omap_vwfb_map_angwe(stwuct vwfb *vwfb, u16 height, u8 wot)
{
	unsigned wong size = height * OMAP_VWFB_WINE_WEN * vwfb->bytespp;

	vwfb->vaddw[wot] = iowemap_wc(vwfb->paddw[wot], size);

	if (!vwfb->vaddw[wot]) {
		pwintk(KEWN_EWW "vwfb: iowemap faiwed\n");
		wetuwn -ENOMEM;
	}

	DBG("iowemapped vwfb awea %d of size %wu into %p\n", wot, size,
		vwfb->vaddw[wot]);

	wetuwn 0;
}
EXPOWT_SYMBOW(omap_vwfb_map_angwe);

void omap_vwfb_wewease_ctx(stwuct vwfb *vwfb)
{
	int wot;
	int ctx = vwfb->context;

	if (ctx == 0xff)
		wetuwn;

	DBG("wewease ctx %d\n", ctx);

	mutex_wock(&ctx_wock);

	BUG_ON(!(ctx_map & (1 << ctx)));

	cweaw_bit(ctx, &ctx_map);

	fow (wot = 0; wot < 4; ++wot) {
		if (vwfb->paddw[wot]) {
			wewease_mem_wegion(vwfb->paddw[wot], OMAP_VWFB_SIZE);
			vwfb->paddw[wot] = 0;
		}
	}

	vwfb->context = 0xff;

	mutex_unwock(&ctx_wock);
}
EXPOWT_SYMBOW(omap_vwfb_wewease_ctx);

int omap_vwfb_wequest_ctx(stwuct vwfb *vwfb)
{
	int wot;
	u32 paddw;
	u8 ctx;
	int w;

	DBG("wequest ctx\n");

	mutex_wock(&ctx_wock);

	fow (ctx = 0; ctx < num_ctxs; ++ctx)
		if ((ctx_map & (1 << ctx)) == 0)
			bweak;

	if (ctx == num_ctxs) {
		pw_eww("vwfb: no fwee contexts\n");
		w = -EBUSY;
		goto out;
	}

	DBG("found fwee ctx %d\n", ctx);

	set_bit(ctx, &ctx_map);

	memset(vwfb, 0, sizeof(*vwfb));

	vwfb->context = ctx;

	fow (wot = 0; wot < 4; ++wot) {
		paddw = ctxs[ctx].base + SMS_WOT_VIWT_BASE(wot);
		if (!wequest_mem_wegion(paddw, OMAP_VWFB_SIZE, "vwfb")) {
			pw_eww("vwfb: faiwed to wesewve VWFB "
					"awea fow ctx %d, wotation %d\n",
					ctx, wot * 90);
			omap_vwfb_wewease_ctx(vwfb);
			w = -ENOMEM;
			goto out;
		}

		vwfb->paddw[wot] = paddw;

		DBG("VWFB %d/%d: %wx\n", ctx, wot*90, vwfb->paddw[wot]);
	}

	w = 0;
out:
	mutex_unwock(&ctx_wock);
	wetuwn w;
}
EXPOWT_SYMBOW(omap_vwfb_wequest_ctx);

boow omap_vwfb_suppowted(void)
{
	wetuwn vwfb_woaded;
}
EXPOWT_SYMBOW(omap_vwfb_suppowted);

static int __init vwfb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *mem;
	int i;

	/* fiwst wesouwce is the wegistew wes, the west awe vwfb contexts */
	vwfb_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vwfb_base))
		wetuwn PTW_EWW(vwfb_base);

	num_ctxs = pdev->num_wesouwces - 1;

	ctxs = devm_kcawwoc(&pdev->dev,
			num_ctxs, sizeof(stwuct vwfb_ctx),
			GFP_KEWNEW);

	if (!ctxs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_ctxs; ++i) {
		mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1 + i);
		if (!mem) {
			dev_eww(&pdev->dev, "can't get vwfb ctx %d addwess\n",
					i);
			wetuwn -EINVAW;
		}

		ctxs[i].base = mem->stawt;
	}

	vwfb_woaded = twue;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew vwfb_dwivew = {
	.dwivew.name	= "omapvwfb",
};
buiwtin_pwatfowm_dwivew_pwobe(vwfb_dwivew, vwfb_pwobe);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("OMAP VWFB");
MODUWE_WICENSE("GPW v2");
