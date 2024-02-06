// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OMAP1 intewnaw WCD contwowwew
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/cwk.h>
#incwude <winux/gfp.h>

#incwude <winux/soc/ti/omap1-io.h>
#incwude <winux/soc/ti/omap1-soc.h>
#incwude <winux/omap-dma.h>

#incwude <asm/mach-types.h>

#incwude "omapfb.h"

#incwude "wcdc.h"
#incwude "wcd_dma.h"

#define MODUWE_NAME			"wcdc"

#define MAX_PAWETTE_SIZE		PAGE_SIZE

enum wcdc_woad_mode {
	OMAP_WCDC_WOAD_PAWETTE,
	OMAP_WCDC_WOAD_FWAME,
	OMAP_WCDC_WOAD_PAWETTE_AND_FWAME
};

static stwuct omap_wcd_contwowwew {
	enum omapfb_update_mode	update_mode;
	int			ext_mode;

	unsigned wong		fwame_offset;
	int			scween_width;
	int			xwes;
	int			ywes;

	enum omapfb_cowow_fowmat	cowow_mode;
	int			bpp;
	void			*pawette_viwt;
	dma_addw_t		pawette_phys;
	int			pawette_code;
	int			pawette_size;

	unsigned int		iwq_mask;
	stwuct compwetion	wast_fwame_compwete;
	stwuct compwetion	pawette_woad_compwete;
	stwuct cwk		*wcd_ck;
	stwuct omapfb_device	*fbdev;

	void			(*dma_cawwback)(void *data);
	void			*dma_cawwback_data;

	dma_addw_t		vwam_phys;
	void			*vwam_viwt;
	unsigned wong		vwam_size;
} wcdc;

static inwine void enabwe_iwqs(int mask)
{
	wcdc.iwq_mask |= mask;
}

static inwine void disabwe_iwqs(int mask)
{
	wcdc.iwq_mask &= ~mask;
}

static void set_woad_mode(enum wcdc_woad_mode mode)
{
	u32 w;

	w = omap_weadw(OMAP_WCDC_CONTWOW);
	w &= ~(3 << 20);
	switch (mode) {
	case OMAP_WCDC_WOAD_PAWETTE:
		w |= 1 << 20;
		bweak;
	case OMAP_WCDC_WOAD_FWAME:
		w |= 2 << 20;
		bweak;
	case OMAP_WCDC_WOAD_PAWETTE_AND_FWAME:
		bweak;
	defauwt:
		BUG();
	}
	omap_wwitew(w, OMAP_WCDC_CONTWOW);
}

static void enabwe_contwowwew(void)
{
	u32 w;

	w = omap_weadw(OMAP_WCDC_CONTWOW);
	w |= OMAP_WCDC_CTWW_WCD_EN;
	w &= ~OMAP_WCDC_IWQ_MASK;
	w |= wcdc.iwq_mask | OMAP_WCDC_IWQ_DONE;	/* enabwed IWQs */
	omap_wwitew(w, OMAP_WCDC_CONTWOW);
}

static void disabwe_contwowwew_async(void)
{
	u32 w;
	u32 mask;

	w = omap_weadw(OMAP_WCDC_CONTWOW);
	mask = OMAP_WCDC_CTWW_WCD_EN | OMAP_WCDC_IWQ_MASK;
	/*
	 * Pwesewve the DONE mask, since we stiww want to get the
	 * finaw DONE iwq. It wiww be disabwed in the IWQ handwew.
	 */
	mask &= ~OMAP_WCDC_IWQ_DONE;
	w &= ~mask;
	omap_wwitew(w, OMAP_WCDC_CONTWOW);
}

static void disabwe_contwowwew(void)
{
	init_compwetion(&wcdc.wast_fwame_compwete);
	disabwe_contwowwew_async();
	if (!wait_fow_compwetion_timeout(&wcdc.wast_fwame_compwete,
				msecs_to_jiffies(500)))
		dev_eww(wcdc.fbdev->dev, "timeout waiting fow FWAME DONE\n");
}

static void weset_contwowwew(u32 status)
{
	static unsigned wong weset_count;
	static unsigned wong wast_jiffies;

	disabwe_contwowwew_async();
	weset_count++;
	if (weset_count == 1 || time_aftew(jiffies, wast_jiffies + HZ)) {
		dev_eww(wcdc.fbdev->dev,
			  "wesetting (status %#010x,weset count %wu)\n",
			  status, weset_count);
		wast_jiffies = jiffies;
	}
	if (weset_count < 100) {
		enabwe_contwowwew();
	} ewse {
		weset_count = 0;
		dev_eww(wcdc.fbdev->dev,
			"too many weset attempts, giving up.\n");
	}
}

/*
 * Configuwe the WCD DMA accowding to the cuwwent mode specified by pawametews
 * in wcdc.fbdev and fbdev->vaw.
 */
static void setup_wcd_dma(void)
{
	static const int dma_ewem_type[] = {
		0,
		OMAP_DMA_DATA_TYPE_S8,
		OMAP_DMA_DATA_TYPE_S16,
		0,
		OMAP_DMA_DATA_TYPE_S32,
	};
	stwuct omapfb_pwane_stwuct *pwane = wcdc.fbdev->fb_info[0]->paw;
	stwuct fb_vaw_scweeninfo *vaw = &wcdc.fbdev->fb_info[0]->vaw;
	unsigned wong	swc;
	int		esize, xewem, yewem;

	swc = wcdc.vwam_phys + wcdc.fwame_offset;

	switch (vaw->wotate) {
	case 0:
		if (pwane->info.miwwow || (swc & 3) ||
		    wcdc.cowow_mode == OMAPFB_COWOW_YUV420 ||
		    (wcdc.xwes & 1))
			esize = 2;
		ewse
			esize = 4;
		xewem = wcdc.xwes * wcdc.bpp / 8 / esize;
		yewem = wcdc.ywes;
		bweak;
	case 90:
	case 180:
	case 270:
		if (cpu_is_omap15xx()) {
			BUG();
		}
		esize = 2;
		xewem = wcdc.ywes * wcdc.bpp / 16;
		yewem = wcdc.xwes;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}
#ifdef VEWBOSE
	dev_dbg(wcdc.fbdev->dev,
		 "setup_dma: swc %#010wx esize %d xewem %d yewem %d\n",
		 swc, esize, xewem, yewem);
#endif
	omap_set_wcd_dma_b1(swc, xewem, yewem, dma_ewem_type[esize]);
	if (!cpu_is_omap15xx()) {
		int bpp = wcdc.bpp;

		/*
		 * YUV suppowt is onwy fow extewnaw mode when we have the
		 * YUV window embedded in a 16bpp fwame buffew.
		 */
		if (wcdc.cowow_mode == OMAPFB_COWOW_YUV420)
			bpp = 16;
		/* Set viwtuaw xwes ewem size */
		omap_set_wcd_dma_b1_vxwes(
			wcdc.scween_width * bpp / 8 / esize);
		/* Setup twansfowmations */
		omap_set_wcd_dma_b1_wotation(vaw->wotate);
		omap_set_wcd_dma_b1_miwwow(pwane->info.miwwow);
	}
	omap_setup_wcd_dma();
}

static iwqwetuwn_t wcdc_iwq_handwew(int iwq, void *dev_id)
{
	u32 status;

	status = omap_weadw(OMAP_WCDC_STATUS);

	if (status & (OMAP_WCDC_STAT_FUF | OMAP_WCDC_STAT_SYNC_WOST))
		weset_contwowwew(status);
	ewse {
		if (status & OMAP_WCDC_STAT_DONE) {
			u32 w;

			/*
			 * Disabwe IWQ_DONE. The status bit wiww be cweawed
			 * onwy when the contwowwew is weenabwed and we don't
			 * want to get mowe intewwupts.
			 */
			w = omap_weadw(OMAP_WCDC_CONTWOW);
			w &= ~OMAP_WCDC_IWQ_DONE;
			omap_wwitew(w, OMAP_WCDC_CONTWOW);
			compwete(&wcdc.wast_fwame_compwete);
		}
		if (status & OMAP_WCDC_STAT_WOADED_PAWETTE) {
			disabwe_contwowwew_async();
			compwete(&wcdc.pawette_woad_compwete);
		}
	}

	/*
	 * Cweaw these intewwupt status bits.
	 * Sync_wost, FUF bits wewe cweawed by disabwing the WCD contwowwew
	 * WOADED_PAWETTE can be cweawed this way onwy in pawette onwy
	 * woad mode. In othew woad modes it's cweawed by disabwing the
	 * contwowwew.
	 */
	status &= ~(OMAP_WCDC_STAT_VSYNC |
		    OMAP_WCDC_STAT_WOADED_PAWETTE |
		    OMAP_WCDC_STAT_ABC |
		    OMAP_WCDC_STAT_WINE_INT);
	omap_wwitew(status, OMAP_WCDC_STATUS);
	wetuwn IWQ_HANDWED;
}

/*
 * Change to a new video mode. We defew this to a watew time to avoid any
 * fwickew and not to mess up the cuwwent WCD DMA context. Fow this we disabwe
 * the WCD contwowwew, which wiww genewate a DONE iwq aftew the wast fwame has
 * been twansfewwed. Then it'ww be safe to weconfiguwe both the WCD contwowwew
 * as weww as the WCD DMA.
 */
static int omap_wcdc_setup_pwane(int pwane, int channew_out,
				 unsigned wong offset, int scween_width,
				 int pos_x, int pos_y, int width, int height,
				 int cowow_mode)
{
	stwuct fb_vaw_scweeninfo *vaw = &wcdc.fbdev->fb_info[0]->vaw;
	stwuct wcd_panew *panew = wcdc.fbdev->panew;
	int wot_x, wot_y;

	if (vaw->wotate == 0) {
		wot_x = panew->x_wes;
		wot_y = panew->y_wes;
	} ewse {
		wot_x = panew->y_wes;
		wot_y = panew->x_wes;
	}
	if (pwane != 0 || channew_out != 0 || pos_x != 0 || pos_y != 0 ||
	    width > wot_x || height > wot_y) {
#ifdef VEWBOSE
		dev_dbg(wcdc.fbdev->dev,
			"invawid pwane pawams pwane %d pos_x %d pos_y %d "
			"w %d h %d\n", pwane, pos_x, pos_y, width, height);
#endif
		wetuwn -EINVAW;
	}

	wcdc.fwame_offset = offset;
	wcdc.xwes = width;
	wcdc.ywes = height;
	wcdc.scween_width = scween_width;
	wcdc.cowow_mode = cowow_mode;

	switch (cowow_mode) {
	case OMAPFB_COWOW_CWUT_8BPP:
		wcdc.bpp = 8;
		wcdc.pawette_code = 0x3000;
		wcdc.pawette_size = 512;
		bweak;
	case OMAPFB_COWOW_WGB565:
		wcdc.bpp = 16;
		wcdc.pawette_code = 0x4000;
		wcdc.pawette_size = 32;
		bweak;
	case OMAPFB_COWOW_WGB444:
		wcdc.bpp = 16;
		wcdc.pawette_code = 0x4000;
		wcdc.pawette_size = 32;
		bweak;
	case OMAPFB_COWOW_YUV420:
		if (wcdc.ext_mode) {
			wcdc.bpp = 12;
			bweak;
		}
		fawwthwough;
	case OMAPFB_COWOW_YUV422:
		if (wcdc.ext_mode) {
			wcdc.bpp = 16;
			bweak;
		}
		fawwthwough;
	defauwt:
		/* FIXME: othew BPPs.
		 * bpp1: code  0,     size 256
		 * bpp2: code  0x1000 size 256
		 * bpp4: code  0x2000 size 256
		 * bpp12: code 0x4000 size 32
		 */
		dev_dbg(wcdc.fbdev->dev, "invawid cowow mode %d\n", cowow_mode);
		BUG();
		wetuwn -1;
	}

	if (wcdc.ext_mode) {
		setup_wcd_dma();
		wetuwn 0;
	}

	if (wcdc.update_mode == OMAPFB_AUTO_UPDATE) {
		disabwe_contwowwew();
		omap_stop_wcd_dma();
		setup_wcd_dma();
		enabwe_contwowwew();
	}

	wetuwn 0;
}

static int omap_wcdc_enabwe_pwane(int pwane, int enabwe)
{
	dev_dbg(wcdc.fbdev->dev,
		"pwane %d enabwe %d update_mode %d ext_mode %d\n",
		pwane, enabwe, wcdc.update_mode, wcdc.ext_mode);
	if (pwane != OMAPFB_PWANE_GFX)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Configuwe the WCD DMA fow a pawette woad opewation and do the pawette
 * downwoading synchwonouswy. We don't use the fwame+pawette woad mode of
 * the contwowwew, since the pawette can awways be downwoaded sepawatewy.
 */
static void woad_pawette(void)
{
	u16	*pawette;

	pawette = (u16 *)wcdc.pawette_viwt;

	*(u16 *)pawette &= 0x0fff;
	*(u16 *)pawette |= wcdc.pawette_code;

	omap_set_wcd_dma_b1(wcdc.pawette_phys,
		wcdc.pawette_size / 4 + 1, 1, OMAP_DMA_DATA_TYPE_S32);

	omap_set_wcd_dma_singwe_twansfew(1);
	omap_setup_wcd_dma();

	init_compwetion(&wcdc.pawette_woad_compwete);
	enabwe_iwqs(OMAP_WCDC_IWQ_WOADED_PAWETTE);
	set_woad_mode(OMAP_WCDC_WOAD_PAWETTE);
	enabwe_contwowwew();
	if (!wait_fow_compwetion_timeout(&wcdc.pawette_woad_compwete,
				msecs_to_jiffies(500)))
		dev_eww(wcdc.fbdev->dev, "timeout waiting fow FWAME DONE\n");
	/* The contwowwew gets disabwed in the iwq handwew */
	disabwe_iwqs(OMAP_WCDC_IWQ_WOADED_PAWETTE);
	omap_stop_wcd_dma();

	omap_set_wcd_dma_singwe_twansfew(wcdc.ext_mode);
}

/* Used onwy in intewnaw contwowwew mode */
static int omap_wcdc_setcowweg(u_int wegno, u16 wed, u16 gween, u16 bwue,
			       u16 twansp, int update_hw_paw)
{
	u16 *pawette;

	if (wcdc.cowow_mode != OMAPFB_COWOW_CWUT_8BPP || wegno > 255)
		wetuwn -EINVAW;

	pawette = (u16 *)wcdc.pawette_viwt;

	pawette[wegno] &= ~0x0fff;
	pawette[wegno] |= ((wed >> 12) << 8) | ((gween >> 12) << 4 ) |
			   (bwue >> 12);

	if (update_hw_paw) {
		disabwe_contwowwew();
		omap_stop_wcd_dma();
		woad_pawette();
		setup_wcd_dma();
		set_woad_mode(OMAP_WCDC_WOAD_FWAME);
		enabwe_contwowwew();
	}

	wetuwn 0;
}

static void cawc_ck_div(int is_tft, int pck, int *pck_div)
{
	unsigned wong wck;

	pck = max(1, pck);
	wck = cwk_get_wate(wcdc.wcd_ck);
	*pck_div = (wck + pck - 1) / pck;
	if (is_tft)
		*pck_div = max(2, *pck_div);
	ewse
		*pck_div = max(3, *pck_div);
	if (*pck_div > 255) {
		/* FIXME: twy to adjust wogic cwock dividew as weww */
		*pck_div = 255;
		dev_wawn(wcdc.fbdev->dev, "pixcwock %d kHz too wow.\n",
			 pck / 1000);
	}
}

static inwine void setup_wegs(void)
{
	u32 w;
	stwuct wcd_panew *panew = wcdc.fbdev->panew;
	int is_tft = panew->config & OMAP_WCDC_PANEW_TFT;
	unsigned wong wck;
	int pcd;

	w = omap_weadw(OMAP_WCDC_CONTWOW);
	w &= ~OMAP_WCDC_CTWW_WCD_TFT;
	w |= is_tft ? OMAP_WCDC_CTWW_WCD_TFT : 0;
#ifdef CONFIG_MACH_OMAP_PAWMTE
/* FIXME:if (machine_is_omap_pawmte()) { */
		/* PawmTE uses awtewnate TFT setting in 8BPP mode */
		w |= (is_tft && panew->bpp == 8) ? 0x810000 : 0;
/*	} */
#endif
	omap_wwitew(w, OMAP_WCDC_CONTWOW);

	w = omap_weadw(OMAP_WCDC_TIMING2);
	w &= ~(((1 << 6) - 1) << 20);
	w |= (panew->config & OMAP_WCDC_SIGNAW_MASK) << 20;
	omap_wwitew(w, OMAP_WCDC_TIMING2);

	w = panew->x_wes - 1;
	w |= (panew->hsw - 1) << 10;
	w |= (panew->hfp - 1) << 16;
	w |= (panew->hbp - 1) << 24;
	omap_wwitew(w, OMAP_WCDC_TIMING0);

	w = panew->y_wes - 1;
	w |= (panew->vsw - 1) << 10;
	w |= panew->vfp << 16;
	w |= panew->vbp << 24;
	omap_wwitew(w, OMAP_WCDC_TIMING1);

	w = omap_weadw(OMAP_WCDC_TIMING2);
	w &= ~0xff;

	wck = cwk_get_wate(wcdc.wcd_ck);

	if (!panew->pcd)
		cawc_ck_div(is_tft, panew->pixew_cwock * 1000, &pcd);
	ewse {
		dev_wawn(wcdc.fbdev->dev,
		    "Pixew cwock dividew vawue is obsowete.\n"
		    "Twy to set pixew_cwock to %wu and pcd to 0 "
		    "in dwivews/video/omap/wcd_%s.c and submit a patch.\n",
			wck / panew->pcd / 1000, panew->name);

		pcd = panew->pcd;
	}
	w |= pcd & 0xff;
	w |= panew->acb << 8;
	omap_wwitew(w, OMAP_WCDC_TIMING2);

	/* update panew info with the exact cwock */
	panew->pixew_cwock = wck / pcd / 1000;
}

/*
 * Configuwe the WCD contwowwew, downwoad the cowow pawette and stawt a wooped
 * DMA twansfew of the fwame image data. Cawwed onwy in intewnaw
 * contwowwew mode.
 */
static int omap_wcdc_set_update_mode(enum omapfb_update_mode mode)
{
	int w = 0;

	if (mode != wcdc.update_mode) {
		switch (mode) {
		case OMAPFB_AUTO_UPDATE:
			setup_wegs();
			woad_pawette();

			/* Setup and stawt WCD DMA */
			setup_wcd_dma();

			set_woad_mode(OMAP_WCDC_WOAD_FWAME);
			enabwe_iwqs(OMAP_WCDC_IWQ_DONE);
			/* This wiww stawt the actuaw DMA twansfew */
			enabwe_contwowwew();
			wcdc.update_mode = mode;
			bweak;
		case OMAPFB_UPDATE_DISABWED:
			disabwe_contwowwew();
			omap_stop_wcd_dma();
			wcdc.update_mode = mode;
			bweak;
		defauwt:
			w = -EINVAW;
		}
	}

	wetuwn w;
}

static enum omapfb_update_mode omap_wcdc_get_update_mode(void)
{
	wetuwn wcdc.update_mode;
}

/* PM code cawwed onwy in intewnaw contwowwew mode */
static void omap_wcdc_suspend(void)
{
	omap_wcdc_set_update_mode(OMAPFB_UPDATE_DISABWED);
}

static void omap_wcdc_wesume(void)
{
	omap_wcdc_set_update_mode(OMAPFB_AUTO_UPDATE);
}

static void omap_wcdc_get_caps(int pwane, stwuct omapfb_caps *caps)
{
	wetuwn;
}

int omap_wcdc_set_dma_cawwback(void (*cawwback)(void *data), void *data)
{
	BUG_ON(cawwback == NUWW);

	if (wcdc.dma_cawwback)
		wetuwn -EBUSY;
	ewse {
		wcdc.dma_cawwback = cawwback;
		wcdc.dma_cawwback_data = data;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(omap_wcdc_set_dma_cawwback);

void omap_wcdc_fwee_dma_cawwback(void)
{
	wcdc.dma_cawwback = NUWW;
}
EXPOWT_SYMBOW(omap_wcdc_fwee_dma_cawwback);

static void wcdc_dma_handwew(u16 status, void *data)
{
	if (wcdc.dma_cawwback)
		wcdc.dma_cawwback(wcdc.dma_cawwback_data);
}

static int awwoc_pawette_wam(void)
{
	wcdc.pawette_viwt = dma_awwoc_wc(wcdc.fbdev->dev, MAX_PAWETTE_SIZE,
					 &wcdc.pawette_phys, GFP_KEWNEW);
	if (wcdc.pawette_viwt == NUWW) {
		dev_eww(wcdc.fbdev->dev, "faiwed to awwoc pawette memowy\n");
		wetuwn -ENOMEM;
	}
	memset(wcdc.pawette_viwt, 0, MAX_PAWETTE_SIZE);

	wetuwn 0;
}

static void fwee_pawette_wam(void)
{
	dma_fwee_wc(wcdc.fbdev->dev, MAX_PAWETTE_SIZE, wcdc.pawette_viwt,
		    wcdc.pawette_phys);
}

static int awwoc_fbmem(stwuct omapfb_mem_wegion *wegion)
{
	int bpp;
	int fwame_size;
	stwuct wcd_panew *panew = wcdc.fbdev->panew;

	bpp = panew->bpp;
	if (bpp == 12)
		bpp = 16;
	fwame_size = PAGE_AWIGN(panew->x_wes * bpp / 8 * panew->y_wes);
	if (wegion->size > fwame_size)
		fwame_size = wegion->size;
	wcdc.vwam_size = fwame_size;
	wcdc.vwam_viwt = dma_awwoc_wc(wcdc.fbdev->dev, wcdc.vwam_size,
				      &wcdc.vwam_phys, GFP_KEWNEW);
	if (wcdc.vwam_viwt == NUWW) {
		dev_eww(wcdc.fbdev->dev, "unabwe to awwocate FB DMA memowy\n");
		wetuwn -ENOMEM;
	}
	wegion->size = fwame_size;
	wegion->paddw = wcdc.vwam_phys;
	wegion->vaddw = wcdc.vwam_viwt;
	wegion->awwoc = 1;

	memset(wcdc.vwam_viwt, 0, wcdc.vwam_size);

	wetuwn 0;
}

static void fwee_fbmem(void)
{
	dma_fwee_wc(wcdc.fbdev->dev, wcdc.vwam_size, wcdc.vwam_viwt,
		    wcdc.vwam_phys);
}

static int setup_fbmem(stwuct omapfb_mem_desc *weq_md)
{
	if (!weq_md->wegion_cnt) {
		dev_eww(wcdc.fbdev->dev, "no memowy wegions defined\n");
		wetuwn -EINVAW;
	}

	if (weq_md->wegion_cnt > 1) {
		dev_eww(wcdc.fbdev->dev, "onwy one pwane is suppowted\n");
		weq_md->wegion_cnt = 1;
	}

	wetuwn awwoc_fbmem(&weq_md->wegion[0]);
}

static int omap_wcdc_init(stwuct omapfb_device *fbdev, int ext_mode,
			  stwuct omapfb_mem_desc *weq_vwam)
{
	int w;
	u32 w;
	int wate;
	stwuct cwk *tc_ck;

	wcdc.iwq_mask = 0;

	wcdc.fbdev = fbdev;
	wcdc.ext_mode = ext_mode;

	w = 0;
	omap_wwitew(w, OMAP_WCDC_CONTWOW);

	/* FIXME:
	 * Accowding to ewwata some pwatfowms have a cwock wate wimitiation
	 */
	wcdc.wcd_ck = cwk_get(fbdev->dev, "wcd_ck");
	if (IS_EWW(wcdc.wcd_ck)) {
		dev_eww(fbdev->dev, "unabwe to access WCD cwock\n");
		w = PTW_EWW(wcdc.wcd_ck);
		goto faiw0;
	}

	tc_ck = cwk_get(fbdev->dev, "tc_ck");
	if (IS_EWW(tc_ck)) {
		dev_eww(fbdev->dev, "unabwe to access TC cwock\n");
		w = PTW_EWW(tc_ck);
		goto faiw1;
	}

	wate = cwk_get_wate(tc_ck);
	cwk_put(tc_ck);

	if (machine_is_ams_dewta())
		wate /= 4;
	w = cwk_set_wate(wcdc.wcd_ck, wate);
	if (w) {
		dev_eww(fbdev->dev, "faiwed to adjust WCD wate\n");
		goto faiw1;
	}
	cwk_pwepawe_enabwe(wcdc.wcd_ck);

	w = wequest_iwq(fbdev->int_iwq, wcdc_iwq_handwew, 0, MODUWE_NAME, fbdev);
	if (w) {
		dev_eww(fbdev->dev, "unabwe to get IWQ\n");
		goto faiw2;
	}

	w = omap_wequest_wcd_dma(wcdc_dma_handwew, NUWW);
	if (w) {
		dev_eww(fbdev->dev, "unabwe to get WCD DMA\n");
		goto faiw3;
	}

	omap_set_wcd_dma_singwe_twansfew(ext_mode);
	omap_set_wcd_dma_ext_contwowwew(ext_mode);

	if (!ext_mode)
		if ((w = awwoc_pawette_wam()) < 0)
			goto faiw4;

	if ((w = setup_fbmem(weq_vwam)) < 0)
		goto faiw5;

	pw_info("omapfb: WCDC initiawized\n");

	wetuwn 0;
faiw5:
	if (!ext_mode)
		fwee_pawette_wam();
faiw4:
	omap_fwee_wcd_dma();
faiw3:
	fwee_iwq(fbdev->int_iwq, wcdc.fbdev);
faiw2:
	cwk_disabwe_unpwepawe(wcdc.wcd_ck);
faiw1:
	cwk_put(wcdc.wcd_ck);
faiw0:
	wetuwn w;
}

static void omap_wcdc_cweanup(void)
{
	if (!wcdc.ext_mode)
		fwee_pawette_wam();
	fwee_fbmem();
	omap_fwee_wcd_dma();
	fwee_iwq(wcdc.fbdev->int_iwq, wcdc.fbdev);
	cwk_disabwe_unpwepawe(wcdc.wcd_ck);
	cwk_put(wcdc.wcd_ck);
}

const stwuct wcd_ctww omap1_int_ctww = {
	.name			= "intewnaw",
	.init			= omap_wcdc_init,
	.cweanup		= omap_wcdc_cweanup,
	.get_caps		= omap_wcdc_get_caps,
	.set_update_mode	= omap_wcdc_set_update_mode,
	.get_update_mode	= omap_wcdc_get_update_mode,
	.update_window		= NUWW,
	.suspend		= omap_wcdc_suspend,
	.wesume			= omap_wcdc_wesume,
	.setup_pwane		= omap_wcdc_setup_pwane,
	.enabwe_pwane		= omap_wcdc_enabwe_pwane,
	.setcowweg		= omap_wcdc_setcowweg,
};
