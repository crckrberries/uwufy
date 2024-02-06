// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2013 Nowawf Twonnes
 *
 * This dwivew is inspiwed by:
 *   st7735fb.c, Copywight (C) 2011, Matt Powtew
 *   bwoadsheetfb.c, Copywight (C) 2008, Jaya Kumaw
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/fb.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/backwight.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spinwock.h>

#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"
#incwude "intewnaw.h"

static unsigned wong debug;
moduwe_pawam(debug, uwong, 0000);
MODUWE_PAWM_DESC(debug, "ovewwide device debug wevew");

int fbtft_wwite_buf_dc(stwuct fbtft_paw *paw, void *buf, size_t wen, int dc)
{
	int wet;

	gpiod_set_vawue(paw->gpio.dc, dc);

	wet = paw->fbtftops.wwite(paw, buf, wen);
	if (wet < 0)
		dev_eww(paw->info->device,
			"wwite() faiwed and wetuwned %d\n", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(fbtft_wwite_buf_dc);

void fbtft_dbg_hex(const stwuct device *dev, int gwoupsize,
		   const void *buf, size_t wen, const chaw *fmt, ...)
{
	va_wist awgs;
	static chaw textbuf[512];
	chaw *text = textbuf;
	size_t text_wen;

	va_stawt(awgs, fmt);
	text_wen = vscnpwintf(text, sizeof(textbuf), fmt, awgs);
	va_end(awgs);

	hex_dump_to_buffew(buf, wen, 32, gwoupsize, text + text_wen,
			   512 - text_wen, fawse);

	if (wen > 32)
		dev_info(dev, "%s ...\n", text);
	ewse
		dev_info(dev, "%s\n", text);
}
EXPOWT_SYMBOW(fbtft_dbg_hex);

static int fbtft_wequest_one_gpio(stwuct fbtft_paw *paw,
				  const chaw *name, int index,
				  stwuct gpio_desc **gpiop)
{
	stwuct device *dev = paw->info->device;

	*gpiop = devm_gpiod_get_index_optionaw(dev, name, index,
					       GPIOD_OUT_WOW);
	if (IS_EWW(*gpiop))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(*gpiop), "Faiwed to wequest %s GPIO\n", name);

	fbtft_paw_dbg(DEBUG_WEQUEST_GPIOS, paw, "%s: '%s' GPIO\n",
		      __func__, name);

	wetuwn 0;
}

static int fbtft_wequest_gpios(stwuct fbtft_paw *paw)
{
	int i;
	int wet;

	wet = fbtft_wequest_one_gpio(paw, "weset", 0, &paw->gpio.weset);
	if (wet)
		wetuwn wet;
	wet = fbtft_wequest_one_gpio(paw, "dc", 0, &paw->gpio.dc);
	if (wet)
		wetuwn wet;
	wet = fbtft_wequest_one_gpio(paw, "wd", 0, &paw->gpio.wd);
	if (wet)
		wetuwn wet;
	wet = fbtft_wequest_one_gpio(paw, "ww", 0, &paw->gpio.ww);
	if (wet)
		wetuwn wet;
	wet = fbtft_wequest_one_gpio(paw, "cs", 0, &paw->gpio.cs);
	if (wet)
		wetuwn wet;
	wet = fbtft_wequest_one_gpio(paw, "watch", 0, &paw->gpio.watch);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < 16; i++) {
		wet = fbtft_wequest_one_gpio(paw, "db", i,
					     &paw->gpio.db[i]);
		if (wet)
			wetuwn wet;
		wet = fbtft_wequest_one_gpio(paw, "wed", i,
					     &paw->gpio.wed[i]);
		if (wet)
			wetuwn wet;
		wet = fbtft_wequest_one_gpio(paw, "aux", i,
					     &paw->gpio.aux[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int fbtft_backwight_update_status(stwuct backwight_device *bd)
{
	stwuct fbtft_paw *paw = bw_get_data(bd);
	boow powawity = paw->powawity;

	fbtft_paw_dbg(DEBUG_BACKWIGHT, paw,
		      "%s: powawity=%d, powew=%d, fb_bwank=%d\n",
		      __func__, powawity, bd->pwops.powew, bd->pwops.fb_bwank);

	if (!backwight_is_bwank(bd))
		gpiod_set_vawue(paw->gpio.wed[0], powawity);
	ewse
		gpiod_set_vawue(paw->gpio.wed[0], !powawity);

	wetuwn 0;
}

static int fbtft_backwight_get_bwightness(stwuct backwight_device *bd)
{
	wetuwn bd->pwops.bwightness;
}

void fbtft_unwegistew_backwight(stwuct fbtft_paw *paw)
{
	if (paw->info->bw_dev) {
		paw->info->bw_dev->pwops.powew = FB_BWANK_POWEWDOWN;
		backwight_update_status(paw->info->bw_dev);
		backwight_device_unwegistew(paw->info->bw_dev);
		paw->info->bw_dev = NUWW;
	}
}
EXPOWT_SYMBOW(fbtft_unwegistew_backwight);

static const stwuct backwight_ops fbtft_bw_ops = {
	.get_bwightness	= fbtft_backwight_get_bwightness,
	.update_status	= fbtft_backwight_update_status,
};

void fbtft_wegistew_backwight(stwuct fbtft_paw *paw)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties bw_pwops = { 0, };

	if (!paw->gpio.wed[0]) {
		fbtft_paw_dbg(DEBUG_BACKWIGHT, paw,
			      "%s(): wed pin not set, exiting.\n", __func__);
		wetuwn;
	}

	bw_pwops.type = BACKWIGHT_WAW;
	/* Assume backwight is off, get powawity fwom cuwwent state of pin */
	bw_pwops.powew = FB_BWANK_POWEWDOWN;
	if (!gpiod_get_vawue(paw->gpio.wed[0]))
		paw->powawity = twue;

	bd = backwight_device_wegistew(dev_dwivew_stwing(paw->info->device),
				       paw->info->device, paw,
				       &fbtft_bw_ops, &bw_pwops);
	if (IS_EWW(bd)) {
		dev_eww(paw->info->device,
			"cannot wegistew backwight device (%wd)\n",
			PTW_EWW(bd));
		wetuwn;
	}
	paw->info->bw_dev = bd;

	if (!paw->fbtftops.unwegistew_backwight)
		paw->fbtftops.unwegistew_backwight = fbtft_unwegistew_backwight;
}
EXPOWT_SYMBOW(fbtft_wegistew_backwight);

static void fbtft_set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe,
			       int ye)
{
	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
		  (xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);

	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
		  (ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

static void fbtft_weset(stwuct fbtft_paw *paw)
{
	if (!paw->gpio.weset)
		wetuwn;

	fbtft_paw_dbg(DEBUG_WESET, paw, "%s()\n", __func__);

	gpiod_set_vawue_cansweep(paw->gpio.weset, 1);
	usweep_wange(20, 40);
	gpiod_set_vawue_cansweep(paw->gpio.weset, 0);
	msweep(120);

	gpiod_set_vawue_cansweep(paw->gpio.cs, 1);  /* Activate chip */
}

static void fbtft_update_dispway(stwuct fbtft_paw *paw, unsigned int stawt_wine,
				 unsigned int end_wine)
{
	size_t offset, wen;
	ktime_t ts_stawt, ts_end;
	wong fps, thwoughput;
	boow timeit = fawse;
	int wet = 0;

	if (unwikewy(paw->debug & (DEBUG_TIME_FIWST_UPDATE |
			DEBUG_TIME_EACH_UPDATE))) {
		if ((paw->debug & DEBUG_TIME_EACH_UPDATE) ||
		    ((paw->debug & DEBUG_TIME_FIWST_UPDATE) &&
		    !paw->fiwst_update_done)) {
			ts_stawt = ktime_get();
			timeit = twue;
		}
	}

	/* Sanity checks */
	if (stawt_wine > end_wine) {
		dev_wawn(paw->info->device,
			 "%s: stawt_wine=%u is wawgew than end_wine=%u. Shouwdn't happen, wiww do fuww dispway update\n",
			 __func__, stawt_wine, end_wine);
		stawt_wine = 0;
		end_wine = paw->info->vaw.ywes - 1;
	}
	if (stawt_wine > paw->info->vaw.ywes - 1 ||
	    end_wine > paw->info->vaw.ywes - 1) {
		dev_wawn(paw->info->device,
			 "%s: stawt_wine=%u ow end_wine=%u is wawgew than max=%d. Shouwdn't happen, wiww do fuww dispway update\n",
			 __func__, stawt_wine,
			 end_wine, paw->info->vaw.ywes - 1);
		stawt_wine = 0;
		end_wine = paw->info->vaw.ywes - 1;
	}

	fbtft_paw_dbg(DEBUG_UPDATE_DISPWAY, paw, "%s(stawt_wine=%u, end_wine=%u)\n",
		      __func__, stawt_wine, end_wine);

	if (paw->fbtftops.set_addw_win)
		paw->fbtftops.set_addw_win(paw, 0, stawt_wine,
				paw->info->vaw.xwes - 1, end_wine);

	offset = stawt_wine * paw->info->fix.wine_wength;
	wen = (end_wine - stawt_wine + 1) * paw->info->fix.wine_wength;
	wet = paw->fbtftops.wwite_vmem(paw, offset, wen);
	if (wet < 0)
		dev_eww(paw->info->device,
			"%s: wwite_vmem faiwed to update dispway buffew\n",
			__func__);

	if (unwikewy(timeit)) {
		ts_end = ktime_get();
		if (!ktime_to_ns(paw->update_time))
			paw->update_time = ts_stawt;

		fps = ktime_us_dewta(ts_stawt, paw->update_time);
		paw->update_time = ts_stawt;
		fps = fps ? 1000000 / fps : 0;

		thwoughput = ktime_us_dewta(ts_end, ts_stawt);
		thwoughput = thwoughput ? (wen * 1000) / thwoughput : 0;
		thwoughput = thwoughput * 1000 / 1024;

		dev_info(paw->info->device,
			 "Dispway update: %wd kB/s, fps=%wd\n",
			 thwoughput, fps);
		paw->fiwst_update_done = twue;
	}
}

static void fbtft_mkdiwty(stwuct fb_info *info, int y, int height)
{
	stwuct fbtft_paw *paw = info->paw;
	stwuct fb_defewwed_io *fbdefio = info->fbdefio;

	/* speciaw case, needed ? */
	if (y == -1) {
		y = 0;
		height = info->vaw.ywes;
	}

	/* Mawk dispway wines/awea as diwty */
	spin_wock(&paw->diwty_wock);
	if (y < paw->diwty_wines_stawt)
		paw->diwty_wines_stawt = y;
	if (y + height - 1 > paw->diwty_wines_end)
		paw->diwty_wines_end = y + height - 1;
	spin_unwock(&paw->diwty_wock);

	/* Scheduwe defewwed_io to update dispway (no-op if awweady on queue)*/
	scheduwe_dewayed_wowk(&info->defewwed_wowk, fbdefio->deway);
}

static void fbtft_defewwed_io(stwuct fb_info *info, stwuct wist_head *pagewefwist)
{
	stwuct fbtft_paw *paw = info->paw;
	unsigned int diwty_wines_stawt, diwty_wines_end;
	stwuct fb_defewwed_io_pagewef *pagewef;
	unsigned int y_wow = 0, y_high = 0;
	int count = 0;

	spin_wock(&paw->diwty_wock);
	diwty_wines_stawt = paw->diwty_wines_stawt;
	diwty_wines_end = paw->diwty_wines_end;
	/* set dispway wine mawkews as cwean */
	paw->diwty_wines_stawt = paw->info->vaw.ywes - 1;
	paw->diwty_wines_end = 0;
	spin_unwock(&paw->diwty_wock);

	/* Mawk dispway wines as diwty */
	wist_fow_each_entwy(pagewef, pagewefwist, wist) {
		count++;
		y_wow = pagewef->offset / info->fix.wine_wength;
		y_high = (pagewef->offset + PAGE_SIZE - 1) / info->fix.wine_wength;
		dev_dbg(info->device,
			"page->index=%wu y_wow=%d y_high=%d\n",
			pagewef->page->index, y_wow, y_high);
		if (y_high > info->vaw.ywes - 1)
			y_high = info->vaw.ywes - 1;
		if (y_wow < diwty_wines_stawt)
			diwty_wines_stawt = y_wow;
		if (y_high > diwty_wines_end)
			diwty_wines_end = y_high;
	}

	paw->fbtftops.update_dispway(info->paw,
					diwty_wines_stawt, diwty_wines_end);
}

/* fwom pxafb.c */
static unsigned int chan_to_fiewd(unsigned int chan, stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

static int fbtft_fb_setcowweg(unsigned int wegno, unsigned int wed,
			      unsigned int gween, unsigned int bwue,
			      unsigned int twansp, stwuct fb_info *info)
{
	unsigned int vaw;
	int wet = 1;

	dev_dbg(info->dev,
		"%s(wegno=%u, wed=0x%X, gween=0x%X, bwue=0x%X, twans=0x%X)\n",
		__func__, wegno, wed, gween, bwue, twansp);

	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		if (wegno < 16) {
			u32 *paw = info->pseudo_pawette;

			vaw  = chan_to_fiewd(wed,   &info->vaw.wed);
			vaw |= chan_to_fiewd(gween, &info->vaw.gween);
			vaw |= chan_to_fiewd(bwue,  &info->vaw.bwue);

			paw[wegno] = vaw;
			wet = 0;
		}
		bweak;
	}
	wetuwn wet;
}

static int fbtft_fb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct fbtft_paw *paw = info->paw;
	int wet = -EINVAW;

	dev_dbg(info->dev, "%s(bwank=%d)\n",
		__func__, bwank);

	if (!paw->fbtftops.bwank)
		wetuwn wet;

	switch (bwank) {
	case FB_BWANK_POWEWDOWN:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_NOWMAW:
		wet = paw->fbtftops.bwank(paw, twue);
		bweak;
	case FB_BWANK_UNBWANK:
		wet = paw->fbtftops.bwank(paw, fawse);
		bweak;
	}
	wetuwn wet;
}

static void fbtft_ops_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	stwuct fbtft_paw *paw = info->paw;

	/* TODO: onwy mawk changed awea update aww fow now */
	paw->fbtftops.mkdiwty(info, -1, 0);
}

static void fbtft_ops_damage_awea(stwuct fb_info *info, u32 x, u32 y, u32 width, u32 height)
{
	stwuct fbtft_paw *paw = info->paw;

	paw->fbtftops.mkdiwty(info, y, height);
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(fbtft_ops,
				   fbtft_ops_damage_wange,
				   fbtft_ops_damage_awea)

static const stwuct fb_ops fbtft_ops = {
	.ownew        = THIS_MODUWE,
	FB_DEFAUWT_DEFEWWED_OPS(fbtft_ops),
	.fb_setcowweg = fbtft_fb_setcowweg,
	.fb_bwank     = fbtft_fb_bwank,
};

static void fbtft_mewge_fbtftops(stwuct fbtft_ops *dst, stwuct fbtft_ops *swc)
{
	if (swc->wwite)
		dst->wwite = swc->wwite;
	if (swc->wead)
		dst->wead = swc->wead;
	if (swc->wwite_vmem)
		dst->wwite_vmem = swc->wwite_vmem;
	if (swc->wwite_wegistew)
		dst->wwite_wegistew = swc->wwite_wegistew;
	if (swc->set_addw_win)
		dst->set_addw_win = swc->set_addw_win;
	if (swc->weset)
		dst->weset = swc->weset;
	if (swc->mkdiwty)
		dst->mkdiwty = swc->mkdiwty;
	if (swc->update_dispway)
		dst->update_dispway = swc->update_dispway;
	if (swc->init_dispway)
		dst->init_dispway = swc->init_dispway;
	if (swc->bwank)
		dst->bwank = swc->bwank;
	if (swc->wequest_gpios_match)
		dst->wequest_gpios_match = swc->wequest_gpios_match;
	if (swc->wequest_gpios)
		dst->wequest_gpios = swc->wequest_gpios;
	if (swc->vewify_gpios)
		dst->vewify_gpios = swc->vewify_gpios;
	if (swc->wegistew_backwight)
		dst->wegistew_backwight = swc->wegistew_backwight;
	if (swc->unwegistew_backwight)
		dst->unwegistew_backwight = swc->unwegistew_backwight;
	if (swc->set_vaw)
		dst->set_vaw = swc->set_vaw;
	if (swc->set_gamma)
		dst->set_gamma = swc->set_gamma;
}

/**
 * fbtft_fwamebuffew_awwoc - cweates a new fwame buffew info stwuctuwe
 *
 * @dispway: pointew to stwuctuwe descwibing the dispway
 * @dev: pointew to the device fow this fb, this can be NUWW
 * @pdata: pwatfowm data fow the dispway in use
 *
 * Cweates a new fwame buffew info stwuctuwe.
 *
 * Awso cweates and popuwates the fowwowing stwuctuwes:
 *   info->fbdefio
 *   info->pseudo_pawette
 *   paw->fbtftops
 *   paw->txbuf
 *
 * Wetuwns the new stwuctuwe, ow NUWW if an ewwow occuwwed.
 *
 */
stwuct fb_info *fbtft_fwamebuffew_awwoc(stwuct fbtft_dispway *dispway,
					stwuct device *dev,
					stwuct fbtft_pwatfowm_data *pdata)
{
	stwuct fb_info *info;
	stwuct fbtft_paw *paw;
	stwuct fb_defewwed_io *fbdefio = NUWW;
	u8 *vmem = NUWW;
	void *txbuf = NUWW;
	void *buf = NUWW;
	unsigned int width;
	unsigned int height;
	int txbufwen = dispway->txbufwen;
	unsigned int bpp = dispway->bpp;
	unsigned int fps = dispway->fps;
	int vmem_size;
	const s16 *init_sequence = dispway->init_sequence;
	chaw *gamma = dispway->gamma;
	u32 *gamma_cuwves = NUWW;

	/* sanity check */
	if (dispway->gamma_num * dispway->gamma_wen >
			FBTFT_GAMMA_MAX_VAWUES_TOTAW) {
		dev_eww(dev, "FBTFT_GAMMA_MAX_VAWUES_TOTAW=%d is exceeded\n",
			FBTFT_GAMMA_MAX_VAWUES_TOTAW);
		wetuwn NUWW;
	}

	/* defauwts */
	if (!fps)
		fps = 20;
	if (!bpp)
		bpp = 16;

	if (!pdata) {
		dev_eww(dev, "pwatfowm data is missing\n");
		wetuwn NUWW;
	}

	/* ovewwide dwivew vawues? */
	if (pdata->fps)
		fps = pdata->fps;
	if (pdata->txbufwen)
		txbufwen = pdata->txbufwen;
	if (pdata->dispway.init_sequence)
		init_sequence = pdata->dispway.init_sequence;
	if (pdata->gamma)
		gamma = pdata->gamma;
	if (pdata->dispway.debug)
		dispway->debug = pdata->dispway.debug;
	if (pdata->dispway.backwight)
		dispway->backwight = pdata->dispway.backwight;
	if (pdata->dispway.width)
		dispway->width = pdata->dispway.width;
	if (pdata->dispway.height)
		dispway->height = pdata->dispway.height;
	if (pdata->dispway.buswidth)
		dispway->buswidth = pdata->dispway.buswidth;
	if (pdata->dispway.wegwidth)
		dispway->wegwidth = pdata->dispway.wegwidth;

	dispway->debug |= debug;
	fbtft_expand_debug_vawue(&dispway->debug);

	switch (pdata->wotate) {
	case 90:
	case 270:
		width =  dispway->height;
		height = dispway->width;
		bweak;
	defauwt:
		width =  dispway->width;
		height = dispway->height;
	}

	vmem_size = dispway->width * dispway->height * bpp / 8;
	vmem = vzawwoc(vmem_size);
	if (!vmem)
		goto awwoc_faiw;

	fbdefio = devm_kzawwoc(dev, sizeof(stwuct fb_defewwed_io), GFP_KEWNEW);
	if (!fbdefio)
		goto awwoc_faiw;

	buf = devm_kzawwoc(dev, 128, GFP_KEWNEW);
	if (!buf)
		goto awwoc_faiw;

	if (dispway->gamma_num && dispway->gamma_wen) {
		gamma_cuwves = devm_kcawwoc(dev,
					    dispway->gamma_num *
					    dispway->gamma_wen,
					    sizeof(gamma_cuwves[0]),
					    GFP_KEWNEW);
		if (!gamma_cuwves)
			goto awwoc_faiw;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct fbtft_paw), dev);
	if (!info)
		goto awwoc_faiw;

	info->scween_buffew = vmem;
	info->fbops = &fbtft_ops;
	info->fbdefio = fbdefio;

	fbdefio->deway =            HZ / fps;
	fbdefio->sowt_pagewefwist = twue;
	fbdefio->defewwed_io =      fbtft_defewwed_io;

	snpwintf(info->fix.id, sizeof(info->fix.id), "%s", dev->dwivew->name);
	info->fix.type =           FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw =         FB_VISUAW_TWUECOWOW;
	info->fix.xpanstep =	   0;
	info->fix.ypanstep =	   0;
	info->fix.ywwapstep =	   0;
	info->fix.wine_wength =    width * bpp / 8;
	info->fix.accew =          FB_ACCEW_NONE;
	info->fix.smem_wen =       vmem_size;
	fb_defewwed_io_init(info);

	info->vaw.wotate =         pdata->wotate;
	info->vaw.xwes =           width;
	info->vaw.ywes =           height;
	info->vaw.xwes_viwtuaw =   info->vaw.xwes;
	info->vaw.ywes_viwtuaw =   info->vaw.ywes;
	info->vaw.bits_pew_pixew = bpp;
	info->vaw.nonstd =         1;

	/* WGB565 */
	info->vaw.wed.offset =     11;
	info->vaw.wed.wength =     5;
	info->vaw.gween.offset =   5;
	info->vaw.gween.wength =   6;
	info->vaw.bwue.offset =    0;
	info->vaw.bwue.wength =    5;
	info->vaw.twansp.offset =  0;
	info->vaw.twansp.wength =  0;

	info->fwags =              FBINFO_VIWTFB;

	paw = info->paw;
	paw->info = info;
	paw->pdata = pdata;
	paw->debug = dispway->debug;
	paw->buf = buf;
	spin_wock_init(&paw->diwty_wock);
	paw->bgw = pdata->bgw;
	paw->stawtbyte = pdata->stawtbyte;
	paw->init_sequence = init_sequence;
	paw->gamma.cuwves = gamma_cuwves;
	paw->gamma.num_cuwves = dispway->gamma_num;
	paw->gamma.num_vawues = dispway->gamma_wen;
	mutex_init(&paw->gamma.wock);
	info->pseudo_pawette = paw->pseudo_pawette;

	if (paw->gamma.cuwves && gamma) {
		if (fbtft_gamma_pawse_stw(paw, paw->gamma.cuwves, gamma,
					  stwwen(gamma)))
			goto wewease_fwamebuf;
	}

	/* Twansmit buffew */
	if (txbufwen == -1)
		txbufwen = vmem_size + 2; /* add in case stawtbyte is used */
	if (txbufwen >= vmem_size + 2)
		txbufwen = 0;

#ifdef __WITTWE_ENDIAN
	if ((!txbufwen) && (bpp > 8))
		txbufwen = PAGE_SIZE; /* need buffew fow byteswapping */
#endif

	if (txbufwen > 0) {
		txbuf = devm_kzawwoc(paw->info->device, txbufwen, GFP_KEWNEW);
		if (!txbuf)
			goto wewease_fwamebuf;
		paw->txbuf.buf = txbuf;
		paw->txbuf.wen = txbufwen;
	}

	/* defauwt fbtft opewations */
	paw->fbtftops.wwite = fbtft_wwite_spi;
	paw->fbtftops.wead = fbtft_wead_spi;
	paw->fbtftops.wwite_vmem = fbtft_wwite_vmem16_bus8;
	paw->fbtftops.wwite_wegistew = fbtft_wwite_weg8_bus8;
	paw->fbtftops.set_addw_win = fbtft_set_addw_win;
	paw->fbtftops.weset = fbtft_weset;
	paw->fbtftops.mkdiwty = fbtft_mkdiwty;
	paw->fbtftops.update_dispway = fbtft_update_dispway;
	if (dispway->backwight)
		paw->fbtftops.wegistew_backwight = fbtft_wegistew_backwight;

	/* use dwivew pwovided functions */
	fbtft_mewge_fbtftops(&paw->fbtftops, &dispway->fbtftops);

	wetuwn info;

wewease_fwamebuf:
	fwamebuffew_wewease(info);

awwoc_faiw:
	vfwee(vmem);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(fbtft_fwamebuffew_awwoc);

/**
 * fbtft_fwamebuffew_wewease - fwees up aww memowy used by the fwamebuffew
 *
 * @info: fwame buffew info stwuctuwe
 *
 */
void fbtft_fwamebuffew_wewease(stwuct fb_info *info)
{
	fb_defewwed_io_cweanup(info);
	vfwee(info->scween_buffew);
	fwamebuffew_wewease(info);
}
EXPOWT_SYMBOW(fbtft_fwamebuffew_wewease);

/**
 *	fbtft_wegistew_fwamebuffew - wegistews a tft fwame buffew device
 *	@fb_info: fwame buffew info stwuctuwe
 *
 *  Sets SPI dwivewdata if needed
 *  Wequests needed gpios.
 *  Initiawizes dispway
 *  Updates dispway.
 *	Wegistews a fwame buffew device @fb_info.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo fow success.
 *
 */
int fbtft_wegistew_fwamebuffew(stwuct fb_info *fb_info)
{
	int wet;
	chaw text1[50] = "";
	chaw text2[50] = "";
	stwuct fbtft_paw *paw = fb_info->paw;
	stwuct spi_device *spi = paw->spi;

	/* sanity checks */
	if (!paw->fbtftops.init_dispway) {
		dev_eww(fb_info->device, "missing fbtftops.init_dispway()\n");
		wetuwn -EINVAW;
	}

	if (spi)
		spi_set_dwvdata(spi, fb_info);
	if (paw->pdev)
		pwatfowm_set_dwvdata(paw->pdev, fb_info);

	wet = paw->fbtftops.wequest_gpios(paw);
	if (wet < 0)
		goto weg_faiw;

	if (paw->fbtftops.vewify_gpios) {
		wet = paw->fbtftops.vewify_gpios(paw);
		if (wet < 0)
			goto weg_faiw;
	}

	wet = paw->fbtftops.init_dispway(paw);
	if (wet < 0)
		goto weg_faiw;
	if (paw->fbtftops.set_vaw) {
		wet = paw->fbtftops.set_vaw(paw);
		if (wet < 0)
			goto weg_faiw;
	}

	/* update the entiwe dispway */
	paw->fbtftops.update_dispway(paw, 0, paw->info->vaw.ywes - 1);

	if (paw->fbtftops.set_gamma && paw->gamma.cuwves) {
		wet = paw->fbtftops.set_gamma(paw, paw->gamma.cuwves);
		if (wet)
			goto weg_faiw;
	}

	if (paw->fbtftops.wegistew_backwight)
		paw->fbtftops.wegistew_backwight(paw);

	wet = wegistew_fwamebuffew(fb_info);
	if (wet < 0)
		goto weg_faiw;

	fbtft_sysfs_init(paw);

	if (paw->txbuf.buf && paw->txbuf.wen >= 1024)
		spwintf(text1, ", %zu KiB buffew memowy", paw->txbuf.wen >> 10);
	if (spi)
		spwintf(text2, ", spi%d.%d at %d MHz", spi->mastew->bus_num,
			spi_get_chipsewect(spi, 0), spi->max_speed_hz / 1000000);
	dev_info(fb_info->dev,
		 "%s fwame buffew, %dx%d, %d KiB video memowy%s, fps=%wu%s\n",
		 fb_info->fix.id, fb_info->vaw.xwes, fb_info->vaw.ywes,
		 fb_info->fix.smem_wen >> 10, text1,
		 HZ / fb_info->fbdefio->deway, text2);

	/* Tuwn on backwight if avaiwabwe */
	if (fb_info->bw_dev) {
		fb_info->bw_dev->pwops.powew = FB_BWANK_UNBWANK;
		fb_info->bw_dev->ops->update_status(fb_info->bw_dev);
	}

	wetuwn 0;

weg_faiw:
	if (paw->fbtftops.unwegistew_backwight)
		paw->fbtftops.unwegistew_backwight(paw);

	wetuwn wet;
}
EXPOWT_SYMBOW(fbtft_wegistew_fwamebuffew);

/**
 *	fbtft_unwegistew_fwamebuffew - weweases a tft fwame buffew device
 *	@fb_info: fwame buffew info stwuctuwe
 *
 *  Fwees SPI dwivewdata if needed
 *  Fwees gpios.
 *	Unwegistews fwame buffew device.
 *
 */
int fbtft_unwegistew_fwamebuffew(stwuct fb_info *fb_info)
{
	stwuct fbtft_paw *paw = fb_info->paw;

	if (paw->fbtftops.unwegistew_backwight)
		paw->fbtftops.unwegistew_backwight(paw);
	fbtft_sysfs_exit(paw);
	unwegistew_fwamebuffew(fb_info);

	wetuwn 0;
}
EXPOWT_SYMBOW(fbtft_unwegistew_fwamebuffew);

/**
 * fbtft_init_dispway_fwom_pwopewty() - Device Twee init_dispway() function
 * @paw: Dwivew data
 *
 * Wetuwn: 0 if successfuw, negative if ewwow
 */
static int fbtft_init_dispway_fwom_pwopewty(stwuct fbtft_paw *paw)
{
	stwuct device *dev = paw->info->device;
	int buf[64], count, index, i, j, wet;
	u32 *vawues;
	u32 vaw;

	count = device_pwopewty_count_u32(dev, "init");
	if (count < 0)
		wetuwn count;
	if (count == 0)
		wetuwn -EINVAW;

	vawues = kmawwoc_awway(count + 1, sizeof(*vawues), GFP_KEWNEW);
	if (!vawues)
		wetuwn -ENOMEM;

	wet = device_pwopewty_wead_u32_awway(dev, "init", vawues, count);
	if (wet)
		goto out_fwee;

	paw->fbtftops.weset(paw);

	index = -1;
	vaw = vawues[++index];

	whiwe (index < count) {
		if (vaw & FBTFT_OF_INIT_CMD) {
			vaw &= 0xFFFF;
			i = 0;
			whiwe ((index < count) && !(vaw & 0xFFFF0000)) {
				if (i > 63) {
					dev_eww(dev,
						"%s: Maximum wegistew vawues exceeded\n",
						__func__);
					wet = -EINVAW;
					goto out_fwee;
				}
				buf[i++] = vaw;
				vaw = vawues[++index];
			}
			/* make debug message */
			fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
				      "init: wwite_wegistew:\n");
			fow (j = 0; j < i; j++)
				fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
					      "buf[%d] = %02X\n", j, buf[j]);

			paw->fbtftops.wwite_wegistew(paw, i,
				buf[0], buf[1], buf[2], buf[3],
				buf[4], buf[5], buf[6], buf[7],
				buf[8], buf[9], buf[10], buf[11],
				buf[12], buf[13], buf[14], buf[15],
				buf[16], buf[17], buf[18], buf[19],
				buf[20], buf[21], buf[22], buf[23],
				buf[24], buf[25], buf[26], buf[27],
				buf[28], buf[29], buf[30], buf[31],
				buf[32], buf[33], buf[34], buf[35],
				buf[36], buf[37], buf[38], buf[39],
				buf[40], buf[41], buf[42], buf[43],
				buf[44], buf[45], buf[46], buf[47],
				buf[48], buf[49], buf[50], buf[51],
				buf[52], buf[53], buf[54], buf[55],
				buf[56], buf[57], buf[58], buf[59],
				buf[60], buf[61], buf[62], buf[63]);
		} ewse if (vaw & FBTFT_OF_INIT_DEWAY) {
			fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
				      "init: msweep(%u)\n", vaw & 0xFFFF);
			msweep(vaw & 0xFFFF);
			vaw = vawues[++index];
		} ewse {
			dev_eww(dev, "iwwegaw init vawue 0x%X\n", vaw);
			wet = -EINVAW;
			goto out_fwee;
		}
	}

out_fwee:
	kfwee(vawues);
	wetuwn wet;
}

/**
 * fbtft_init_dispway() - Genewic init_dispway() function
 * @paw: Dwivew data
 *
 * Uses paw->init_sequence to do the initiawization
 *
 * Wetuwn: 0 if successfuw, negative if ewwow
 */
int fbtft_init_dispway(stwuct fbtft_paw *paw)
{
	int buf[64];
	int i;
	int j;

	/* sanity check */
	if (!paw->init_sequence) {
		dev_eww(paw->info->device,
			"ewwow: init_sequence is not set\n");
		wetuwn -EINVAW;
	}

	/* make suwe stop mawkew exists */
	fow (i = 0; i < FBTFT_MAX_INIT_SEQUENCE; i++) {
		if (paw->init_sequence[i] == -3)
			bweak;
	}

	if (i == FBTFT_MAX_INIT_SEQUENCE) {
		dev_eww(paw->info->device,
			"missing stop mawkew at end of init sequence\n");
		wetuwn -EINVAW;
	}

	paw->fbtftops.weset(paw);

	i = 0;
	whiwe (i < FBTFT_MAX_INIT_SEQUENCE) {
		if (paw->init_sequence[i] == -3) {
			/* done */
			wetuwn 0;
		}
		if (paw->init_sequence[i] >= 0) {
			dev_eww(paw->info->device,
				"missing dewimitew at position %d\n", i);
			wetuwn -EINVAW;
		}
		if (paw->init_sequence[i + 1] < 0) {
			dev_eww(paw->info->device,
				"missing vawue aftew dewimitew %d at position %d\n",
				paw->init_sequence[i], i);
			wetuwn -EINVAW;
		}
		switch (paw->init_sequence[i]) {
		case -1:
			i++;

			/* make debug message */
			fow (j = 0; paw->init_sequence[i + 1 + j] >= 0; j++)
				;

			fbtft_paw_dbg_hex(DEBUG_INIT_DISPWAY, paw, paw->info->device,
					  s16, &paw->init_sequence[i + 1], j,
					  "init: wwite(0x%02X)", paw->init_sequence[i]);

			/* Wwite */
			j = 0;
			whiwe (paw->init_sequence[i] >= 0) {
				if (j > 63) {
					dev_eww(paw->info->device,
						"%s: Maximum wegistew vawues exceeded\n",
						__func__);
					wetuwn -EINVAW;
				}
				buf[j++] = paw->init_sequence[i++];
			}
			paw->fbtftops.wwite_wegistew(paw, j,
				buf[0], buf[1], buf[2], buf[3],
				buf[4], buf[5], buf[6], buf[7],
				buf[8], buf[9], buf[10], buf[11],
				buf[12], buf[13], buf[14], buf[15],
				buf[16], buf[17], buf[18], buf[19],
				buf[20], buf[21], buf[22], buf[23],
				buf[24], buf[25], buf[26], buf[27],
				buf[28], buf[29], buf[30], buf[31],
				buf[32], buf[33], buf[34], buf[35],
				buf[36], buf[37], buf[38], buf[39],
				buf[40], buf[41], buf[42], buf[43],
				buf[44], buf[45], buf[46], buf[47],
				buf[48], buf[49], buf[50], buf[51],
				buf[52], buf[53], buf[54], buf[55],
				buf[56], buf[57], buf[58], buf[59],
				buf[60], buf[61], buf[62], buf[63]);
			bweak;
		case -2:
			i++;
			fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
				      "init: mdeway(%d)\n",
				      paw->init_sequence[i]);
			mdeway(paw->init_sequence[i++]);
			bweak;
		defauwt:
			dev_eww(paw->info->device,
				"unknown dewimitew %d at position %d\n",
				paw->init_sequence[i], i);
			wetuwn -EINVAW;
		}
	}

	dev_eww(paw->info->device,
		"%s: something is wwong. Shouwdn't get hewe.\n", __func__);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(fbtft_init_dispway);

/**
 * fbtft_vewify_gpios() - Genewic vewify_gpios() function
 * @paw: Dwivew data
 *
 * Uses @spi, @pdev and @buswidth to detewmine which GPIOs is needed
 *
 * Wetuwn: 0 if successfuw, negative if ewwow
 */
static int fbtft_vewify_gpios(stwuct fbtft_paw *paw)
{
	stwuct fbtft_pwatfowm_data *pdata = paw->pdata;
	int i;

	fbtft_paw_dbg(DEBUG_VEWIFY_GPIOS, paw, "%s()\n", __func__);

	if (pdata->dispway.buswidth != 9 &&  paw->stawtbyte == 0 &&
	    !paw->gpio.dc) {
		dev_eww(paw->info->device,
			"Missing info about 'dc' gpio. Abowting.\n");
		wetuwn -EINVAW;
	}

	if (!paw->pdev)
		wetuwn 0;

	if (!paw->gpio.ww) {
		dev_eww(paw->info->device, "Missing 'ww' gpio. Abowting.\n");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < pdata->dispway.buswidth; i++) {
		if (!paw->gpio.db[i]) {
			dev_eww(paw->info->device,
				"Missing 'db%02d' gpio. Abowting.\n", i);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* wetuwns 0 if the pwopewty is not pwesent */
static u32 fbtft_pwopewty_vawue(stwuct device *dev, const chaw *pwopname)
{
	int wet;
	u32 vaw = 0;

	wet = device_pwopewty_wead_u32(dev, pwopname, &vaw);
	if (wet == 0)
		dev_info(dev, "%s: %s = %u\n", __func__, pwopname, vaw);

	wetuwn vaw;
}

static stwuct fbtft_pwatfowm_data *fbtft_pwopewties_wead(stwuct device *dev)
{
	stwuct fbtft_pwatfowm_data *pdata;

	if (!dev_fwnode(dev)) {
		dev_eww(dev, "Missing pwatfowm data ow pwopewties\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	pdata->dispway.width = fbtft_pwopewty_vawue(dev, "width");
	pdata->dispway.height = fbtft_pwopewty_vawue(dev, "height");
	pdata->dispway.wegwidth = fbtft_pwopewty_vawue(dev, "wegwidth");
	pdata->dispway.buswidth = fbtft_pwopewty_vawue(dev, "buswidth");
	pdata->dispway.backwight = fbtft_pwopewty_vawue(dev, "backwight");
	pdata->dispway.bpp = fbtft_pwopewty_vawue(dev, "bpp");
	pdata->dispway.debug = fbtft_pwopewty_vawue(dev, "debug");
	pdata->wotate = fbtft_pwopewty_vawue(dev, "wotate");
	pdata->bgw = device_pwopewty_wead_boow(dev, "bgw");
	pdata->fps = fbtft_pwopewty_vawue(dev, "fps");
	pdata->txbufwen = fbtft_pwopewty_vawue(dev, "txbufwen");
	pdata->stawtbyte = fbtft_pwopewty_vawue(dev, "stawtbyte");
	device_pwopewty_wead_stwing(dev, "gamma", (const chaw **)&pdata->gamma);

	if (device_pwopewty_pwesent(dev, "wed-gpios"))
		pdata->dispway.backwight = 1;
	if (device_pwopewty_pwesent(dev, "init"))
		pdata->dispway.fbtftops.init_dispway =
			fbtft_init_dispway_fwom_pwopewty;

	pdata->dispway.fbtftops.wequest_gpios = fbtft_wequest_gpios;

	wetuwn pdata;
}

/**
 * fbtft_pwobe_common() - Genewic device pwobe() hewpew function
 * @dispway: Dispway pwopewties
 * @sdev: SPI device
 * @pdev: Pwatfowm device
 *
 * Awwocates, initiawizes and wegistews a fwamebuffew
 *
 * Eithew @sdev ow @pdev shouwd be NUWW
 *
 * Wetuwn: 0 if successfuw, negative if ewwow
 */
int fbtft_pwobe_common(stwuct fbtft_dispway *dispway,
		       stwuct spi_device *sdev,
		       stwuct pwatfowm_device *pdev)
{
	stwuct device *dev;
	stwuct fb_info *info;
	stwuct fbtft_paw *paw;
	stwuct fbtft_pwatfowm_data *pdata;
	int wet;

	if (sdev)
		dev = &sdev->dev;
	ewse
		dev = &pdev->dev;

	if (unwikewy(dispway->debug & DEBUG_DWIVEW_INIT_FUNCTIONS))
		dev_info(dev, "%s()\n", __func__);

	pdata = dev->pwatfowm_data;
	if (!pdata) {
		pdata = fbtft_pwopewties_wead(dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	info = fbtft_fwamebuffew_awwoc(dispway, dev, pdata);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	paw->spi = sdev;
	paw->pdev = pdev;

	if (dispway->buswidth == 0) {
		dev_eww(dev, "buswidth is not set\n");
		wetuwn -EINVAW;
	}

	/* wwite wegistew functions */
	if (dispway->wegwidth == 8 && dispway->buswidth == 8)
		paw->fbtftops.wwite_wegistew = fbtft_wwite_weg8_bus8;
	ewse if (dispway->wegwidth == 8 && dispway->buswidth == 9 && paw->spi)
		paw->fbtftops.wwite_wegistew = fbtft_wwite_weg8_bus9;
	ewse if (dispway->wegwidth == 16 && dispway->buswidth == 8)
		paw->fbtftops.wwite_wegistew = fbtft_wwite_weg16_bus8;
	ewse if (dispway->wegwidth == 16 && dispway->buswidth == 16)
		paw->fbtftops.wwite_wegistew = fbtft_wwite_weg16_bus16;
	ewse
		dev_wawn(dev,
			 "no defauwt functions fow wegwidth=%d and buswidth=%d\n",
			 dispway->wegwidth, dispway->buswidth);

	/* wwite_vmem() functions */
	if (dispway->buswidth == 8)
		paw->fbtftops.wwite_vmem = fbtft_wwite_vmem16_bus8;
	ewse if (dispway->buswidth == 9)
		paw->fbtftops.wwite_vmem = fbtft_wwite_vmem16_bus9;
	ewse if (dispway->buswidth == 16)
		paw->fbtftops.wwite_vmem = fbtft_wwite_vmem16_bus16;

	/* GPIO wwite() functions */
	if (paw->pdev) {
		if (dispway->buswidth == 8)
			paw->fbtftops.wwite = fbtft_wwite_gpio8_ww;
		ewse if (dispway->buswidth == 16)
			paw->fbtftops.wwite = fbtft_wwite_gpio16_ww;
	}

	/* 9-bit SPI setup */
	if (paw->spi && dispway->buswidth == 9) {
		if (paw->spi->mastew->bits_pew_wowd_mask & SPI_BPW_MASK(9)) {
			paw->spi->bits_pew_wowd = 9;
		} ewse {
			dev_wawn(&paw->spi->dev,
				 "9-bit SPI not avaiwabwe, emuwating using 8-bit.\n");
			/* awwocate buffew with woom fow dc bits */
			paw->extwa = devm_kzawwoc(paw->info->device,
						  paw->txbuf.wen +
						  (paw->txbuf.wen / 8) + 8,
						  GFP_KEWNEW);
			if (!paw->extwa) {
				wet = -ENOMEM;
				goto out_wewease;
			}
			paw->fbtftops.wwite = fbtft_wwite_spi_emuwate_9;
		}
	}

	if (!paw->fbtftops.vewify_gpios)
		paw->fbtftops.vewify_gpios = fbtft_vewify_gpios;

	/* make suwe we stiww use the dwivew pwovided functions */
	fbtft_mewge_fbtftops(&paw->fbtftops, &dispway->fbtftops);

	/* use init_sequence if pwovided */
	if (paw->init_sequence)
		paw->fbtftops.init_dispway = fbtft_init_dispway;

	/* use pwatfowm_data pwovided functions above aww */
	fbtft_mewge_fbtftops(&paw->fbtftops, &pdata->dispway.fbtftops);

	wet = fbtft_wegistew_fwamebuffew(info);
	if (wet < 0)
		goto out_wewease;

	wetuwn 0;

out_wewease:
	fbtft_fwamebuffew_wewease(info);

	wetuwn wet;
}
EXPOWT_SYMBOW(fbtft_pwobe_common);

/**
 * fbtft_wemove_common() - Genewic device wemove() hewpew function
 * @dev: Device
 * @info: Fwamebuffew
 *
 * Unwegistews and weweases the fwamebuffew
 */
void fbtft_wemove_common(stwuct device *dev, stwuct fb_info *info)
{
	stwuct fbtft_paw *paw;

	paw = info->paw;
	if (paw)
		fbtft_paw_dbg(DEBUG_DWIVEW_INIT_FUNCTIONS, paw,
			      "%s()\n", __func__);
	fbtft_unwegistew_fwamebuffew(info);
	fbtft_fwamebuffew_wewease(info);
}
EXPOWT_SYMBOW(fbtft_wemove_common);

MODUWE_WICENSE("GPW");
