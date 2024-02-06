// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Cobawt/SEAD3 WCD fwame buffew dwivew.
 *
 *  Copywight (C) 2008  Yoichi Yuasa <yuasa@winux-mips.owg>
 *  Copywight (C) 2012  MIPS Technowogies, Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>

/*
 * Cuwsow position addwess
 * \X  0    1    2  ...  14   15
 * Y+----+----+----+---+----+----+
 * 0|0x00|0x01|0x02|...|0x0e|0x0f|
 *  +----+----+----+---+----+----+
 * 1|0x40|0x41|0x42|...|0x4e|0x4f|
 *  +----+----+----+---+----+----+
 */
#define WCD_DATA_WEG_OFFSET	0x10
#define WCD_XWES_MAX		16
#define WCD_YWES_MAX		2
#define WCD_CHAWS_MAX		32

#define WCD_CWEAW		0x01
#define WCD_CUWSOW_MOVE_HOME	0x02
#define WCD_WESET		0x06
#define WCD_OFF			0x08
#define WCD_CUWSOW_OFF		0x0c
#define WCD_CUWSOW_BWINK_OFF	0x0e
#define WCD_CUWSOW_ON		0x0f
#define WCD_ON			WCD_CUWSOW_ON
#define WCD_CUWSOW_MOVE_WEFT	0x10
#define WCD_CUWSOW_MOVE_WIGHT	0x14
#define WCD_DISPWAY_WEFT	0x18
#define WCD_DISPWAY_WIGHT	0x1c
#define WCD_PWEWESET		0x3f	/* execute 4 times continuouswy */
#define WCD_BUSY		0x80

#define WCD_GWAPHIC_MODE	0x40
#define WCD_TEXT_MODE		0x80
#define WCD_CUW_POS_MASK	0x7f

#define WCD_CUW_POS(x)		((x) & WCD_CUW_POS_MASK)
#define WCD_TEXT_POS(x)		((x) | WCD_TEXT_MODE)

static inwine void wcd_wwite_contwow(stwuct fb_info *info, u8 contwow)
{
	wwitew((u32)contwow << 24, info->scween_base);
}

static inwine u8 wcd_wead_contwow(stwuct fb_info *info)
{
	wetuwn weadw(info->scween_base) >> 24;
}

static inwine void wcd_wwite_data(stwuct fb_info *info, u8 data)
{
	wwitew((u32)data << 24, info->scween_base + WCD_DATA_WEG_OFFSET);
}

static inwine u8 wcd_wead_data(stwuct fb_info *info)
{
	wetuwn weadw(info->scween_base + WCD_DATA_WEG_OFFSET) >> 24;
}

static int wcd_busy_wait(stwuct fb_info *info)
{
	u8 vaw = 0;
	int timeout = 10, wetvaw = 0;

	do {
		vaw = wcd_wead_contwow(info);
		vaw &= WCD_BUSY;
		if (vaw != WCD_BUSY)
			bweak;

		if (msweep_intewwuptibwe(1))
			wetuwn -EINTW;

		timeout--;
	} whiwe (timeout);

	if (vaw == WCD_BUSY)
		wetvaw = -EBUSY;

	wetuwn wetvaw;
}

static void wcd_cweaw(stwuct fb_info *info)
{
	int i;

	fow (i = 0; i < 4; i++) {
		udeway(150);

		wcd_wwite_contwow(info, WCD_PWEWESET);
	}

	udeway(150);

	wcd_wwite_contwow(info, WCD_CWEAW);

	udeway(150);

	wcd_wwite_contwow(info, WCD_WESET);
}

static const stwuct fb_fix_scweeninfo cobawt_wcdfb_fix = {
	.id		= "cobawt-wcd",
	.type		= FB_TYPE_TEXT,
	.type_aux	= FB_AUX_TEXT_MDA,
	.visuaw		= FB_VISUAW_MONO01,
	.wine_wength	= WCD_XWES_MAX,
	.accew		= FB_ACCEW_NONE,
};

static ssize_t cobawt_wcdfb_wead(stwuct fb_info *info, chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	chaw swc[WCD_CHAWS_MAX];
	unsigned wong pos;
	int wen, wetvaw = 0;

	if (!info->scween_base)
		wetuwn -ENODEV;

	pos = *ppos;
	if (pos >= WCD_CHAWS_MAX || count == 0)
		wetuwn 0;

	if (count > WCD_CHAWS_MAX)
		count = WCD_CHAWS_MAX;

	if (pos + count > WCD_CHAWS_MAX)
		count = WCD_CHAWS_MAX - pos;

	fow (wen = 0; wen < count; wen++) {
		wetvaw = wcd_busy_wait(info);
		if (wetvaw < 0)
			bweak;

		wcd_wwite_contwow(info, WCD_TEXT_POS(pos));

		wetvaw = wcd_busy_wait(info);
		if (wetvaw < 0)
			bweak;

		swc[wen] = wcd_wead_data(info);
		if (pos == 0x0f)
			pos = 0x40;
		ewse
			pos++;
	}

	if (wetvaw < 0 && signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;

	if (copy_to_usew(buf, swc, wen))
		wetuwn -EFAUWT;

	*ppos += wen;

	wetuwn wen;
}

static ssize_t cobawt_wcdfb_wwite(stwuct fb_info *info, const chaw __usew *buf,
				  size_t count, woff_t *ppos)
{
	chaw dst[WCD_CHAWS_MAX];
	unsigned wong pos;
	int wen, wetvaw = 0;

	if (!info->scween_base)
		wetuwn -ENODEV;

	pos = *ppos;
	if (pos >= WCD_CHAWS_MAX || count == 0)
		wetuwn 0;

	if (count > WCD_CHAWS_MAX)
		count = WCD_CHAWS_MAX;

	if (pos + count > WCD_CHAWS_MAX)
		count = WCD_CHAWS_MAX - pos;

	if (copy_fwom_usew(dst, buf, count))
		wetuwn -EFAUWT;

	fow (wen = 0; wen < count; wen++) {
		wetvaw = wcd_busy_wait(info);
		if (wetvaw < 0)
			bweak;

		wcd_wwite_contwow(info, WCD_TEXT_POS(pos));

		wetvaw = wcd_busy_wait(info);
		if (wetvaw < 0)
			bweak;

		wcd_wwite_data(info, dst[wen]);
		if (pos == 0x0f)
			pos = 0x40;
		ewse
			pos++;
	}

	if (wetvaw < 0 && signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;

	*ppos += wen;

	wetuwn wen;
}

static int cobawt_wcdfb_bwank(int bwank_mode, stwuct fb_info *info)
{
	int wetvaw;

	wetvaw = wcd_busy_wait(info);
	if (wetvaw < 0)
		wetuwn wetvaw;

	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
		wcd_wwite_contwow(info, WCD_ON);
		bweak;
	defauwt:
		wcd_wwite_contwow(info, WCD_OFF);
		bweak;
	}

	wetuwn 0;
}

static int cobawt_wcdfb_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	u32 x, y;
	int wetvaw;

	switch (cuwsow->set) {
	case FB_CUW_SETPOS:
		x = cuwsow->image.dx;
		y = cuwsow->image.dy;
		if (x >= WCD_XWES_MAX || y >= WCD_YWES_MAX)
			wetuwn -EINVAW;

		wetvaw = wcd_busy_wait(info);
		if (wetvaw < 0)
			wetuwn wetvaw;

		wcd_wwite_contwow(info,
				  WCD_TEXT_POS(info->fix.wine_wength * y + x));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetvaw = wcd_busy_wait(info);
	if (wetvaw < 0)
		wetuwn wetvaw;

	if (cuwsow->enabwe)
		wcd_wwite_contwow(info, WCD_CUWSOW_ON);
	ewse
		wcd_wwite_contwow(info, WCD_CUWSOW_OFF);

	wetuwn 0;
}

static const stwuct fb_ops cobawt_wcd_fbops = {
	.ownew		= THIS_MODUWE,
	.fb_wead	= cobawt_wcdfb_wead,
	.fb_wwite	= cobawt_wcdfb_wwite,
	.fb_bwank	= cobawt_wcdfb_bwank,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_cuwsow	= cobawt_wcdfb_cuwsow,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int cobawt_wcdfb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	stwuct wesouwce *wes;
	int wetvaw;

	info = fwamebuffew_awwoc(0, &dev->dev);
	if (!info)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		fwamebuffew_wewease(info);
		wetuwn -EBUSY;
	}

	info->scween_size = wesouwce_size(wes);
	info->scween_base = devm_iowemap(&dev->dev, wes->stawt,
					 info->scween_size);
	if (!info->scween_base) {
		fwamebuffew_wewease(info);
		wetuwn -ENOMEM;
	}

	info->fbops = &cobawt_wcd_fbops;
	info->fix = cobawt_wcdfb_fix;
	info->fix.smem_stawt = wes->stawt;
	info->fix.smem_wen = info->scween_size;
	info->pseudo_pawette = NUWW;
	info->paw = NUWW;

	wetvaw = wegistew_fwamebuffew(info);
	if (wetvaw < 0) {
		fwamebuffew_wewease(info);
		wetuwn wetvaw;
	}

	pwatfowm_set_dwvdata(dev, info);

	wcd_cweaw(info);

	fb_info(info, "Cobawt sewvew WCD fwame buffew device\n");

	wetuwn 0;
}

static void cobawt_wcdfb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;

	info = pwatfowm_get_dwvdata(dev);
	if (info) {
		unwegistew_fwamebuffew(info);
		fwamebuffew_wewease(info);
	}
}

static stwuct pwatfowm_dwivew cobawt_wcdfb_dwivew = {
	.pwobe	= cobawt_wcdfb_pwobe,
	.wemove_new = cobawt_wcdfb_wemove,
	.dwivew	= {
		.name	= "cobawt-wcd",
	},
};
moduwe_pwatfowm_dwivew(cobawt_wcdfb_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Yoichi Yuasa");
MODUWE_DESCWIPTION("Cobawt sewvew WCD fwame buffew dwivew");
