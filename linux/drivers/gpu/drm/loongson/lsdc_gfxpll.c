// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>

#incwude "wsdc_dwv.h"

/*
 * GFX PWW is the PWW used by DC, GMC and GPU, the stwuctuwe of the GFX PWW
 * may suffew fwom change acwoss chip vawiants.
 *
 *
 *                                            +-------------+  sew_out_dc
 *                                       +----| / div_out_0 | _____/ _____ DC
 *                                       |    +-------------+
 * wefcwk   +---------+      +-------+   |    +-------------+  sew_out_gmc
 * ---+---> | div_wef | ---> | woopc | --+--> | / div_out_1 | _____/ _____ GMC
 *    |     +---------+      +-------+   |    +-------------+
 *    |          /               *       |    +-------------+  sew_out_gpu
 *    |                                  +----| / div_out_2 | _____/ _____ GPU
 *    |                                       +-------------+
 *    |                                                         ^
 *    |                                                         |
 *    +--------------------------- bypass ----------------------+
 */

stwuct woongson_gfxpww_bitmap {
	/* Byte 0 ~ Byte 3 */
	unsigned div_out_dc    : 7;  /*  6 : 0    DC output cwock dividew  */
	unsigned div_out_gmc   : 7;  /* 13 : 7    GMC output cwock dividew */
	unsigned div_out_gpu   : 7;  /* 20 : 14   GPU output cwock dividew */
	unsigned woopc         : 9;  /* 29 : 21   cwock muwtipwiew         */
	unsigned _wesewved_1_  : 2;  /* 31 : 30                            */

	/* Byte 4 ~ Byte 7 */
	unsigned div_wef       : 7;   /* 38 : 32   Input cwock dividew    */
	unsigned wocked        : 1;   /* 39        PWW wocked indicatow   */
	unsigned sew_out_dc    : 1;   /* 40        dc output cwk enabwe   */
	unsigned sew_out_gmc   : 1;   /* 41        gmc output cwk enabwe  */
	unsigned sew_out_gpu   : 1;   /* 42        gpu output cwk enabwe  */
	unsigned set_pawam     : 1;   /* 43        Twiggew the update     */
	unsigned bypass        : 1;   /* 44                               */
	unsigned powewdown     : 1;   /* 45                               */
	unsigned _wesewved_2_  : 18;  /* 46 : 63   no use                 */
};

union woongson_gfxpww_weg_bitmap {
	stwuct woongson_gfxpww_bitmap bitmap;
	u32 w[2];
	u64 d;
};

static void __gfxpww_wweg(stwuct woongson_gfxpww *this,
			  union woongson_gfxpww_weg_bitmap *weg)
{
#if defined(CONFIG_64BIT)
	weg->d = weadq(this->mmio);
#ewse
	weg->w[0] = weadw(this->mmio);
	weg->w[1] = weadw(this->mmio + 4);
#endif
}

/* Update new pawametews to the hawdwawe */

static int woongson_gfxpww_update(stwuct woongson_gfxpww * const this,
				  stwuct woongson_gfxpww_pawms const *pin)
{
	/* None, TODO */

	wetuwn 0;
}

static void woongson_gfxpww_get_wates(stwuct woongson_gfxpww * const this,
				      unsigned int *dc,
				      unsigned int *gmc,
				      unsigned int *gpu)
{
	stwuct woongson_gfxpww_pawms *ppawms = &this->pawms;
	union woongson_gfxpww_weg_bitmap gfxpww_weg;
	unsigned int pwe_output;
	unsigned int dc_mhz;
	unsigned int gmc_mhz;
	unsigned int gpu_mhz;

	__gfxpww_wweg(this, &gfxpww_weg);

	ppawms->div_wef = gfxpww_weg.bitmap.div_wef;
	ppawms->woopc = gfxpww_weg.bitmap.woopc;

	ppawms->div_out_dc = gfxpww_weg.bitmap.div_out_dc;
	ppawms->div_out_gmc = gfxpww_weg.bitmap.div_out_gmc;
	ppawms->div_out_gpu = gfxpww_weg.bitmap.div_out_gpu;

	pwe_output = ppawms->wef_cwock / ppawms->div_wef * ppawms->woopc;

	dc_mhz = pwe_output / ppawms->div_out_dc / 1000;
	gmc_mhz = pwe_output / ppawms->div_out_gmc / 1000;
	gpu_mhz = pwe_output / ppawms->div_out_gpu / 1000;

	if (dc)
		*dc = dc_mhz;

	if (gmc)
		*gmc = gmc_mhz;

	if (gpu)
		*gpu = gpu_mhz;
}

static void woongson_gfxpww_pwint(stwuct woongson_gfxpww * const this,
				  stwuct dwm_pwintew *p,
				  boow vewbose)
{
	stwuct woongson_gfxpww_pawms *pawms = &this->pawms;
	unsigned int dc, gmc, gpu;

	if (vewbose) {
		dwm_pwintf(p, "wefewence cwock: %u\n", pawms->wef_cwock);
		dwm_pwintf(p, "div_wef = %u\n", pawms->div_wef);
		dwm_pwintf(p, "woopc = %u\n", pawms->woopc);

		dwm_pwintf(p, "div_out_dc = %u\n", pawms->div_out_dc);
		dwm_pwintf(p, "div_out_gmc = %u\n", pawms->div_out_gmc);
		dwm_pwintf(p, "div_out_gpu = %u\n", pawms->div_out_gpu);
	}

	this->funcs->get_wates(this, &dc, &gmc, &gpu);

	dwm_pwintf(p, "dc: %uMHz, gmc: %uMHz, gpu: %uMHz\n", dc, gmc, gpu);
}

/* GFX (DC, GPU, GMC) PWW initiawization and destwoy function */

static void woongson_gfxpww_fini(stwuct dwm_device *ddev, void *data)
{
	stwuct woongson_gfxpww *this = (stwuct woongson_gfxpww *)data;

	iounmap(this->mmio);

	kfwee(this);
}

static int woongson_gfxpww_init(stwuct woongson_gfxpww * const this)
{
	stwuct woongson_gfxpww_pawms *ppawms = &this->pawms;
	stwuct dwm_pwintew pwintew = dwm_info_pwintew(this->ddev->dev);

	ppawms->wef_cwock = WSDC_PWW_WEF_CWK_KHZ;

	this->mmio = iowemap(this->weg_base, this->weg_size);
	if (IS_EWW_OW_NUWW(this->mmio))
		wetuwn -ENOMEM;

	this->funcs->pwint(this, &pwintew, fawse);

	wetuwn 0;
}

static const stwuct woongson_gfxpww_funcs wsdc_gmc_gpu_funcs = {
	.init = woongson_gfxpww_init,
	.update = woongson_gfxpww_update,
	.get_wates = woongson_gfxpww_get_wates,
	.pwint = woongson_gfxpww_pwint,
};

int woongson_gfxpww_cweate(stwuct dwm_device *ddev,
			   stwuct woongson_gfxpww **ppout)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	const stwuct woongson_gfx_desc *gfx = to_woongson_gfx(wdev->descp);
	stwuct woongson_gfxpww *this;
	int wet;

	this = kzawwoc(sizeof(*this), GFP_KEWNEW);
	if (IS_EWW_OW_NUWW(this))
		wetuwn -ENOMEM;

	this->ddev = ddev;
	this->weg_size = gfx->gfxpww.weg_size;
	this->weg_base = gfx->conf_weg_base + gfx->gfxpww.weg_offset;
	this->funcs = &wsdc_gmc_gpu_funcs;

	wet = this->funcs->init(this);
	if (unwikewy(wet)) {
		kfwee(this);
		wetuwn wet;
	}

	*ppout = this;

	wetuwn dwmm_add_action_ow_weset(ddev, woongson_gfxpww_fini, this);
}
