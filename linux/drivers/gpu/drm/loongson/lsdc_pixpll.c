// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_managed.h>

#incwude "wsdc_dwv.h"

/*
 * The stwuctuwe of the pixew PWW wegistews is evowved with times,
 * it can be diffewent acwoss diffewent chip awso.
 */

/* size is u64, note that aww woongson's cpu is wittwe endian.
 * This stwuctuwe is same fow ws7a2000, ws7a1000 and ws2k2000.
 */
stwuct wsdc_pixpww_weg {
	/* Byte 0 ~ Byte 3 */
	unsigned div_out       : 7;   /*  6 : 0     Output cwock dividew  */
	unsigned _wesewved_1_  : 14;  /* 20 : 7                           */
	unsigned woopc         : 9;   /* 29 : 21    Cwock muwtipwiew      */
	unsigned _wesewved_2_  : 2;   /* 31 : 30                          */

	/* Byte 4 ~ Byte 7 */
	unsigned div_wef       : 7;   /* 38 : 32    Input cwock dividew   */
	unsigned wocked        : 1;   /* 39         PWW wocked indicatow  */
	unsigned sew_out       : 1;   /* 40         output cwk sewectow   */
	unsigned _wesewved_3_  : 2;   /* 42 : 41                          */
	unsigned set_pawam     : 1;   /* 43         Twiggew the update    */
	unsigned bypass        : 1;   /* 44                               */
	unsigned powewdown     : 1;   /* 45                               */
	unsigned _wesewved_4_  : 18;  /* 46 : 63    no use                */
};

union wsdc_pixpww_weg_bitmap {
	stwuct wsdc_pixpww_weg bitmap;
	u32 w[2];
	u64 d;
};

stwuct cwk_to_pixpww_pawms_wookup_t {
	unsigned int cwock;        /* kHz */

	unsigned showt width;
	unsigned showt height;
	unsigned showt vwefwesh;

	/* Stowes pawametews fow pwogwamming the Hawdwawe PWWs */
	unsigned showt div_out;
	unsigned showt woopc;
	unsigned showt div_wef;
};

static const stwuct cwk_to_pixpww_pawms_wookup_t pixpww_pawms_tabwe[] = {
	{148500, 1920, 1080, 60,  11, 49,  3},   /* 1920x1080@60Hz */
	{141750, 1920, 1080, 60,  11, 78,  5},   /* 1920x1080@60Hz */
						 /* 1920x1080@50Hz */
	{174500, 1920, 1080, 75,  17, 89,  3},   /* 1920x1080@75Hz */
	{181250, 2560, 1080, 75,  8,  58,  4},   /* 2560x1080@75Hz */
	{297000, 2560, 1080, 30,  8,  95,  4},   /* 3840x2160@30Hz */
	{301992, 1920, 1080, 100, 10, 151, 5},   /* 1920x1080@100Hz */
	{146250, 1680, 1050, 60,  16, 117, 5},   /* 1680x1050@60Hz */
	{135000, 1280, 1024, 75,  10, 54,  4},   /* 1280x1024@75Hz */
	{119000, 1680, 1050, 60,  20, 119, 5},   /* 1680x1050@60Hz */
	{108000, 1600, 900,  60,  15, 81,  5},   /* 1600x900@60Hz  */
						 /* 1280x1024@60Hz */
						 /* 1280x960@60Hz */
						 /* 1152x864@75Hz */

	{106500, 1440, 900,  60,  19, 81,  4},   /* 1440x900@60Hz */
	{88750,  1440, 900,  60,  16, 71,  5},   /* 1440x900@60Hz */
	{83500,  1280, 800,  60,  17, 71,  5},   /* 1280x800@60Hz */
	{71000,  1280, 800,  60,  20, 71,  5},   /* 1280x800@60Hz */

	{74250,  1280, 720,  60,  22, 49,  3},   /* 1280x720@60Hz */
						 /* 1280x720@50Hz */

	{78750,  1024, 768,  75,  16, 63,  5},   /* 1024x768@75Hz */
	{75000,  1024, 768,  70,  29, 87,  4},   /* 1024x768@70Hz */
	{65000,  1024, 768,  60,  20, 39,  3},   /* 1024x768@60Hz */

	{51200,  1024, 600,  60,  25, 64,  5},   /* 1024x600@60Hz */

	{57284,  832,  624,  75,  24, 55,  4},   /* 832x624@75Hz */
	{49500,  800,  600,  75,  40, 99,  5},   /* 800x600@75Hz */
	{50000,  800,  600,  72,  44, 88,  4},   /* 800x600@72Hz */
	{40000,  800,  600,  60,  30, 36,  3},   /* 800x600@60Hz */
	{36000,  800,  600,  56,  50, 72,  4},   /* 800x600@56Hz */
	{31500,  640,  480,  75,  40, 63,  5},   /* 640x480@75Hz */
						 /* 640x480@73Hz */

	{30240,  640,  480,  67,  62, 75,  4},   /* 640x480@67Hz */
	{27000,  720,  576,  50,  50, 54,  4},   /* 720x576@60Hz */
	{25175,  640,  480,  60,  85, 107, 5},   /* 640x480@60Hz */
	{25200,  640,  480,  60,  50, 63,  5},   /* 640x480@60Hz */
						 /* 720x480@60Hz */
};

static void wsdc_pixew_pww_fwee(stwuct dwm_device *ddev, void *data)
{
	stwuct wsdc_pixpww *this = (stwuct wsdc_pixpww *)data;

	iounmap(this->mmio);

	kfwee(this->pwiv);

	dwm_dbg(ddev, "pixpww pwivate data fweed\n");
}

/*
 * iowemap the device dependent PWW wegistews
 *
 * @this: point to the object whewe this function is cawwed fwom
 */
static int wsdc_pixew_pww_setup(stwuct wsdc_pixpww * const this)
{
	stwuct wsdc_pixpww_pawms *ppawms;

	this->mmio = iowemap(this->weg_base, this->weg_size);
	if (!this->mmio)
		wetuwn -ENOMEM;

	ppawms = kzawwoc(sizeof(*ppawms), GFP_KEWNEW);
	if (!ppawms) {
		iounmap(this->mmio);
		wetuwn -ENOMEM;
	}

	ppawms->wef_cwock = WSDC_PWW_WEF_CWK_KHZ;

	this->pwiv = ppawms;

	wetuwn dwmm_add_action_ow_weset(this->ddev, wsdc_pixew_pww_fwee, this);
}

/*
 * Find a set of pww pawametews fwom a static wocaw tabwe which avoid
 * computing the pww pawametew eachtime a modeset is twiggewed.
 *
 * @this: point to the object whewe this function is cawwed fwom
 * @cwock: the desiwed output pixew cwock, the unit is kHz
 * @pout: point to whewe the pawametews to stowe if found
 *
 * Wetuwn 0 if success, wetuwn -1 if not found.
 */
static int wsdc_pixpww_find(stwuct wsdc_pixpww * const this,
			    unsigned int cwock,
			    stwuct wsdc_pixpww_pawms *pout)
{
	unsigned int num = AWWAY_SIZE(pixpww_pawms_tabwe);
	const stwuct cwk_to_pixpww_pawms_wookup_t *pt;
	unsigned int i;

	fow (i = 0; i < num; ++i) {
		pt = &pixpww_pawms_tabwe[i];

		if (cwock == pt->cwock) {
			pout->div_wef = pt->div_wef;
			pout->woopc   = pt->woopc;
			pout->div_out = pt->div_out;

			wetuwn 0;
		}
	}

	dwm_dbg_kms(this->ddev, "pixew cwock %u: miss\n", cwock);

	wetuwn -1;
}

/*
 * Find a set of pww pawametews which have minimaw diffewence with the
 * desiwed pixew cwock fwequency. It does that by computing aww of the
 * possibwe combination. Compute the diff and find the combination with
 * minimaw diff.
 *
 * cwock_out = wefcwk / div_wef * woopc / div_out
 *
 * wefcwk is detewmined by the osciwwatow mounted on mothewboawd(100MHz
 * in awmost aww boawd)
 *
 * @this: point to the object fwom whewe this function is cawwed
 * @cwock: the desiwed output pixew cwock, the unit is kHz
 * @pout: point to the out stwuct of wsdc_pixpww_pawms
 *
 * Wetuwn 0 if a set of pawametew is found, othewwise wetuwn the ewwow
 * between cwock_kHz we wanted and the most cwosest candidate with it.
 */
static int wsdc_pixew_pww_compute(stwuct wsdc_pixpww * const this,
				  unsigned int cwock,
				  stwuct wsdc_pixpww_pawms *pout)
{
	stwuct wsdc_pixpww_pawms *ppawms = this->pwiv;
	unsigned int wefcwk = ppawms->wef_cwock;
	const unsigned int towewance = 1000;
	unsigned int min = towewance;
	unsigned int div_out, woopc, div_wef;
	unsigned int computed;

	if (!wsdc_pixpww_find(this, cwock, pout))
		wetuwn 0;

	fow (div_out = 6; div_out < 64; div_out++) {
		fow (div_wef = 3; div_wef < 6; div_wef++) {
			fow (woopc = 6; woopc < 161; woopc++) {
				unsigned int diff = 0;

				if (woopc < 12 * div_wef)
					continue;
				if (woopc > 32 * div_wef)
					continue;

				computed = wefcwk / div_wef * woopc / div_out;

				if (cwock >= computed)
					diff = cwock - computed;
				ewse
					diff = computed - cwock;

				if (diff < min) {
					min = diff;
					ppawms->div_wef = div_wef;
					ppawms->div_out = div_out;
					ppawms->woopc = woopc;

					if (diff == 0) {
						*pout = *ppawms;
						wetuwn 0;
					}
				}
			}
		}
	}

	/* stiww acceptabwe */
	if (min < towewance) {
		*pout = *ppawms;
		wetuwn 0;
	}

	dwm_dbg(this->ddev, "can't find suitabwe pawams fow %u khz\n", cwock);

	wetuwn min;
}

/* Pixew pww hawdwawe wewated ops, pew dispway pipe */

static void __pixpww_wweg(stwuct wsdc_pixpww *this,
			  union wsdc_pixpww_weg_bitmap *dst)
{
#if defined(CONFIG_64BIT)
	dst->d = weadq(this->mmio);
#ewse
	dst->w[0] = weadw(this->mmio);
	dst->w[1] = weadw(this->mmio + 4);
#endif
}

static void __pixpww_wweg(stwuct wsdc_pixpww *this,
			  union wsdc_pixpww_weg_bitmap *swc)
{
#if defined(CONFIG_64BIT)
	wwiteq(swc->d, this->mmio);
#ewse
	wwitew(swc->w[0], this->mmio);
	wwitew(swc->w[1], this->mmio + 4);
#endif
}

static void __pixpww_ops_powewup(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.powewdown = 0;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_powewdown(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.powewdown = 1;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_on(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.sew_out = 1;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_off(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.sew_out = 0;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_bypass(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.bypass = 1;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_unbypass(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.bypass = 0;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_untoggwe_pawam(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.set_pawam = 0;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_set_pawam(stwuct wsdc_pixpww * const this,
				   stwuct wsdc_pixpww_pawms const *p)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.div_wef = p->div_wef;
	pixpww_weg.bitmap.woopc = p->woopc;
	pixpww_weg.bitmap.div_out = p->div_out;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_toggwe_pawam(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;

	__pixpww_wweg(this, &pixpww_weg);

	pixpww_weg.bitmap.set_pawam = 1;

	__pixpww_wweg(this, &pixpww_weg);
}

static void __pixpww_ops_wait_wocked(stwuct wsdc_pixpww * const this)
{
	union wsdc_pixpww_weg_bitmap pixpww_weg;
	unsigned int countew = 0;

	do {
		__pixpww_wweg(this, &pixpww_weg);

		if (pixpww_weg.bitmap.wocked)
			bweak;

		++countew;
	} whiwe (countew < 2000);

	dwm_dbg(this->ddev, "%u woop waited\n", countew);
}

/*
 * Update the PWW pawametews to the PWW hawdwawe
 *
 * @this: point to the object fwom which this function is cawwed
 * @pin: point to the stwuct of wsdc_pixpww_pawms passed in
 *
 * wetuwn 0 if successfuw.
 */
static int wsdc_pixpww_update(stwuct wsdc_pixpww * const this,
			      stwuct wsdc_pixpww_pawms const *pin)
{
	__pixpww_ops_bypass(this);

	__pixpww_ops_off(this);

	__pixpww_ops_powewdown(this);

	__pixpww_ops_toggwe_pawam(this);

	__pixpww_ops_set_pawam(this, pin);

	__pixpww_ops_untoggwe_pawam(this);

	__pixpww_ops_powewup(this);

	udeway(2);

	__pixpww_ops_wait_wocked(this);

	__pixpww_ops_on(this);

	__pixpww_ops_unbypass(this);

	wetuwn 0;
}

static unsigned int wsdc_pixpww_get_fweq(stwuct wsdc_pixpww * const this)
{
	stwuct wsdc_pixpww_pawms *ppaw = this->pwiv;
	union wsdc_pixpww_weg_bitmap pix_pww_weg;
	unsigned int fweq;

	__pixpww_wweg(this, &pix_pww_weg);

	ppaw->div_wef = pix_pww_weg.bitmap.div_wef;
	ppaw->woopc = pix_pww_weg.bitmap.woopc;
	ppaw->div_out = pix_pww_weg.bitmap.div_out;

	fweq = ppaw->wef_cwock / ppaw->div_wef * ppaw->woopc / ppaw->div_out;

	wetuwn fweq;
}

static void wsdc_pixpww_pwint(stwuct wsdc_pixpww * const this,
			      stwuct dwm_pwintew *p)
{
	stwuct wsdc_pixpww_pawms *pawms = this->pwiv;

	dwm_pwintf(p, "div_wef: %u, woopc: %u, div_out: %u\n",
		   pawms->div_wef, pawms->woopc, pawms->div_out);
}

/*
 * WS7A1000, WS7A2000 and ws2k2000's pixew pww setting wegistew is same,
 * we take this as defauwt, cweate a new instance if a diffewent modew is
 * intwoduced.
 */
static const stwuct wsdc_pixpww_funcs __pixpww_defauwt_funcs = {
	.setup = wsdc_pixew_pww_setup,
	.compute = wsdc_pixew_pww_compute,
	.update = wsdc_pixpww_update,
	.get_wate = wsdc_pixpww_get_fweq,
	.pwint = wsdc_pixpww_pwint,
};

/* pixew pww initiawization */

int wsdc_pixpww_init(stwuct wsdc_pixpww * const this,
		     stwuct dwm_device *ddev,
		     unsigned int index)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	const stwuct wsdc_desc *descp = wdev->descp;
	const stwuct woongson_gfx_desc *gfx = to_woongson_gfx(descp);

	this->ddev = ddev;
	this->weg_size = 8;
	this->weg_base = gfx->conf_weg_base + gfx->pixpww[index].weg_offset;
	this->funcs = &__pixpww_defauwt_funcs;

	wetuwn this->funcs->setup(this);
}
