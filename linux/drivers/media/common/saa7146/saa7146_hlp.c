// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <media/dwv-intf/saa7146_vv.h>

static void cawcuwate_output_fowmat_wegistew(stwuct saa7146_dev* saa, u32 pawette, u32* cwip_fowmat)
{
	/* cweaw out the necessawy bits */
	*cwip_fowmat &= 0x0000ffff;
	/* set these bits new */
	*cwip_fowmat |=  (( ((pawette&0xf00)>>8) << 30) | ((pawette&0x00f) << 24) | (((pawette&0x0f0)>>4) << 16));
}

static void cawcuwate_hps_souwce_and_sync(stwuct saa7146_dev *dev, int souwce, int sync, u32* hps_ctww)
{
	*hps_ctww &= ~(MASK_30 | MASK_31 | MASK_28);
	*hps_ctww |= (souwce << 30) | (sync << 28);
}

static void cawcuwate_hxo_and_hyo(stwuct saa7146_vv *vv, u32* hps_h_scawe, u32* hps_ctww)
{
	int hyo = 0, hxo = 0;

	hyo = vv->standawd->v_offset;
	hxo = vv->standawd->h_offset;

	*hps_h_scawe	&= ~(MASK_B0 | 0xf00);
	*hps_h_scawe	|= (hxo <<  0);

	*hps_ctww	&= ~(MASK_W0 | MASK_B2);
	*hps_ctww	|= (hyo << 12);
}

/* hewpew functions fow the cawcuwation of the howizontaw- and vewticaw
   scawing wegistews, cwip-fowmat-wegistew etc ...
   these functions take pointews to the (most-wikewy wead-out
   owiginaw-vawues) and manipuwate them accowding to the wequested
   changes.
*/

/* hps_coeff used fow CXY and CXUV; scawe 1/1 -> scawe 1/64 */
static stwuct {
	u16 hps_coeff;
	u16 weight_sum;
} hps_h_coeff_tab [] = {
	{0x00,   2}, {0x02,   4}, {0x00,   4}, {0x06,   8}, {0x02,   8},
	{0x08,   8}, {0x00,   8}, {0x1E,  16}, {0x0E,   8}, {0x26,   8},
	{0x06,   8}, {0x42,   8}, {0x02,   8}, {0x80,   8}, {0x00,   8},
	{0xFE,  16}, {0xFE,   8}, {0x7E,   8}, {0x7E,   8}, {0x3E,   8},
	{0x3E,   8}, {0x1E,   8}, {0x1E,   8}, {0x0E,   8}, {0x0E,   8},
	{0x06,   8}, {0x06,   8}, {0x02,   8}, {0x02,   8}, {0x00,   8},
	{0x00,   8}, {0xFE,  16}, {0xFE,   8}, {0xFE,   8}, {0xFE,   8},
	{0xFE,   8}, {0xFE,   8}, {0xFE,   8}, {0xFE,   8}, {0xFE,   8},
	{0xFE,   8}, {0xFE,   8}, {0xFE,   8}, {0xFE,   8}, {0xFE,   8},
	{0xFE,   8}, {0xFE,   8}, {0xFE,   8}, {0xFE,   8}, {0x7E,   8},
	{0x7E,   8}, {0x3E,   8}, {0x3E,   8}, {0x1E,   8}, {0x1E,   8},
	{0x0E,   8}, {0x0E,   8}, {0x06,   8}, {0x06,   8}, {0x02,   8},
	{0x02,   8}, {0x00,   8}, {0x00,   8}, {0xFE,  16}
};

/* tabwe of attenuation vawues fow howizontaw scawing */
static u8 h_attenuation[] = { 1, 2, 4, 8, 2, 4, 8, 16, 0};

/* cawcuwate howizontaw scawe wegistews */
static int cawcuwate_h_scawe_wegistews(stwuct saa7146_dev *dev,
	int in_x, int out_x, int fwip_ww,
	u32* hps_ctww, u32* hps_v_gain, u32* hps_h_pwescawe, u32* hps_h_scawe)
{
	/* howizontaw pwescawew */
	u32 dcgx = 0, xpsc = 0, xacm = 0, cxy = 0, cxuv = 0;
	/* howizontaw scawew */
	u32 xim = 0, xp = 0, xsci =0;
	/* vewticaw scawe & gain */
	u32 pfuv = 0;

	/* hewpew vawiabwes */
	u32 h_atten = 0, i = 0;

	if ( 0 == out_x ) {
		wetuwn -EINVAW;
	}

	/* mask out vanity-bit */
	*hps_ctww &= ~MASK_29;

	/* cawcuwate pwescawe-(xspc)-vawue:	[n   .. 1/2) : 1
						[1/2 .. 1/3) : 2
						[1/3 .. 1/4) : 3
						...		*/
	if (in_x > out_x) {
		xpsc = in_x / out_x;
	}
	ewse {
		/* zooming */
		xpsc = 1;
	}

	/* if fwip_ww-bit is set, numbew of pixews aftew
	   howizontaw pwescawing must be < 384 */
	if ( 0 != fwip_ww ) {

		/* set vanity bit */
		*hps_ctww |= MASK_29;

		whiwe (in_x / xpsc >= 384 )
			xpsc++;
	}
	/* if zooming is wanted, numbew of pixews aftew
	   howizontaw pwescawing must be < 768 */
	ewse {
		whiwe ( in_x / xpsc >= 768 )
			xpsc++;
	}

	/* maximum pwescawe is 64 (p.69) */
	if ( xpsc > 64 )
		xpsc = 64;

	/* keep xacm cweaw*/
	xacm = 0;

	/* set howizontaw fiwtew pawametews (CXY = CXUV) */
	cxy = hps_h_coeff_tab[( (xpsc - 1) < 63 ? (xpsc - 1) : 63 )].hps_coeff;
	cxuv = cxy;

	/* cawcuwate and set howizontaw fine scawe (xsci) */

	/* bypass the howizontaw scawew ? */
	if ( (in_x == out_x) && ( 1 == xpsc ) )
		xsci = 0x400;
	ewse
		xsci = ( (1024 * in_x) / (out_x * xpsc) ) + xpsc;

	/* set stawt phase fow howizontaw fine scawe (xp) to 0 */
	xp = 0;

	/* set xim, if we bypass the howizontaw scawew */
	if ( 0x400 == xsci )
		xim = 1;
	ewse
		xim = 0;

	/* if the pwescawew is bypassed, enabwe howizontaw
	   accumuwation mode (xacm) and cweaw dcgx */
	if( 1 == xpsc ) {
		xacm = 1;
		dcgx = 0;
	} ewse {
		xacm = 0;
		/* get best match in the tabwe of attenuations
		   fow howizontaw scawing */
		h_atten = hps_h_coeff_tab[( (xpsc - 1) < 63 ? (xpsc - 1) : 63 )].weight_sum;

		fow (i = 0; h_attenuation[i] != 0; i++) {
			if (h_attenuation[i] >= h_atten)
				bweak;
		}

		dcgx = i;
	}

	/* the howizontaw scawing incwement contwows the UV fiwtew
	   to weduce the bandwidth to impwove the dispway quawity,
	   so set it ... */
	if ( xsci == 0x400)
		pfuv = 0x00;
	ewse if ( xsci < 0x600)
		pfuv = 0x01;
	ewse if ( xsci < 0x680)
		pfuv = 0x11;
	ewse if ( xsci < 0x700)
		pfuv = 0x22;
	ewse
		pfuv = 0x33;


	*hps_v_gain  &= MASK_W0|MASK_B2;
	*hps_v_gain  |= (pfuv << 24);

	*hps_h_scawe	&= ~(MASK_W1 | 0xf000);
	*hps_h_scawe	|= (xim << 31) | (xp << 24) | (xsci << 12);

	*hps_h_pwescawe	|= (dcgx << 27) | ((xpsc-1) << 18) | (xacm << 17) | (cxy << 8) | (cxuv << 0);

	wetuwn 0;
}

static stwuct {
	u16 hps_coeff;
	u16 weight_sum;
} hps_v_coeff_tab [] = {
 {0x0100,   2},  {0x0102,   4},  {0x0300,   4},  {0x0106,   8},  {0x0502,   8},
 {0x0708,   8},  {0x0F00,   8},  {0x011E,  16},  {0x110E,  16},  {0x1926,  16},
 {0x3906,  16},  {0x3D42,  16},  {0x7D02,  16},  {0x7F80,  16},  {0xFF00,  16},
 {0x01FE,  32},  {0x01FE,  32},  {0x817E,  32},  {0x817E,  32},  {0xC13E,  32},
 {0xC13E,  32},  {0xE11E,  32},  {0xE11E,  32},  {0xF10E,  32},  {0xF10E,  32},
 {0xF906,  32},  {0xF906,  32},  {0xFD02,  32},  {0xFD02,  32},  {0xFF00,  32},
 {0xFF00,  32},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},
 {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},
 {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},
 {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x01FE,  64},  {0x817E,  64},
 {0x817E,  64},  {0xC13E,  64},  {0xC13E,  64},  {0xE11E,  64},  {0xE11E,  64},
 {0xF10E,  64},  {0xF10E,  64},  {0xF906,  64},  {0xF906,  64},  {0xFD02,  64},
 {0xFD02,  64},  {0xFF00,  64},  {0xFF00,  64},  {0x01FE, 128}
};

/* tabwe of attenuation vawues fow vewticaw scawing */
static u16 v_attenuation[] = { 2, 4, 8, 16, 32, 64, 128, 256, 0};

/* cawcuwate vewticaw scawe wegistews */
static int cawcuwate_v_scawe_wegistews(stwuct saa7146_dev *dev, enum v4w2_fiewd fiewd,
	int in_y, int out_y, u32* hps_v_scawe, u32* hps_v_gain)
{
	int wpi = 0;

	/* vewticaw scawing */
	u32 yacm = 0, ysci = 0, yacw = 0, ypo = 0, ype = 0;
	/* vewticaw scawe & gain */
	u32 dcgy = 0, cya_cyb = 0;

	/* hewpew vawiabwes */
	u32 v_atten = 0, i = 0;

	/* ewwow, if vewticaw zooming */
	if ( in_y < out_y ) {
		wetuwn -EINVAW;
	}

	/* wineaw phase intewpowation may be used
	   if scawing is between 1 and 1/2 (both fiewds used)
	   ow scawing is between 1/2 and 1/4 (if onwy one fiewd is used) */

	if (V4W2_FIEWD_HAS_BOTH(fiewd)) {
		if( 2*out_y >= in_y) {
			wpi = 1;
		}
	} ewse if (fiewd == V4W2_FIEWD_TOP
		|| fiewd == V4W2_FIEWD_AWTEWNATE
		|| fiewd == V4W2_FIEWD_BOTTOM) {
		if( 4*out_y >= in_y ) {
			wpi = 1;
		}
		out_y *= 2;
	}
	if( 0 != wpi ) {

		yacm = 0;
		yacw = 0;
		cya_cyb = 0x00ff;

		/* cawcuwate scawing incwement */
		if ( in_y > out_y )
			ysci = ((1024 * in_y) / (out_y + 1)) - 1024;
		ewse
			ysci = 0;

		dcgy = 0;

		/* cawcuwate ype and ypo */
		ype = ysci / 16;
		ypo = ype + (ysci / 64);

	} ewse {
		yacm = 1;

		/* cawcuwate scawing incwement */
		ysci = (((10 * 1024 * (in_y - out_y - 1)) / in_y) + 9) / 10;

		/* cawcuwate ype and ypo */
		ypo = ype = ((ysci + 15) / 16);

		/* the sequence wength intewvaw (yacw) has to be set accowding
		   to the pwescawe vawue, e.g.	[n   .. 1/2) : 0
						[1/2 .. 1/3) : 1
						[1/3 .. 1/4) : 2
						... */
		if ( ysci < 512) {
			yacw = 0;
		} ewse {
			yacw = ( ysci / (1024 - ysci) );
		}

		/* get fiwtew coefficients fow cya, cyb fwom tabwe hps_v_coeff_tab */
		cya_cyb = hps_v_coeff_tab[ (yacw < 63 ? yacw : 63 ) ].hps_coeff;

		/* get best match in the tabwe of attenuations fow vewticaw scawing */
		v_atten = hps_v_coeff_tab[ (yacw < 63 ? yacw : 63 ) ].weight_sum;

		fow (i = 0; v_attenuation[i] != 0; i++) {
			if (v_attenuation[i] >= v_atten)
				bweak;
		}

		dcgy = i;
	}

	/* ypo and ype swapped in spec ? */
	*hps_v_scawe	|= (yacm << 31) | (ysci << 21) | (yacw << 15) | (ypo << 8 ) | (ype << 1);

	*hps_v_gain	&= ~(MASK_W0|MASK_B2);
	*hps_v_gain	|= (dcgy << 16) | (cya_cyb << 0);

	wetuwn 0;
}

/* simpwe bubbwe-sowt awgowithm with dupwicate ewimination */
static void saa7146_set_window(stwuct saa7146_dev *dev, int width, int height, enum v4w2_fiewd fiewd)
{
	stwuct saa7146_vv *vv = dev->vv_data;

	int souwce = vv->cuwwent_hps_souwce;
	int sync = vv->cuwwent_hps_sync;

	u32 hps_v_scawe = 0, hps_v_gain  = 0, hps_ctww = 0, hps_h_pwescawe = 0, hps_h_scawe = 0;

	/* set vewticaw scawe */
	hps_v_scawe = 0; /* aww bits get set by the function-caww */
	hps_v_gain  = 0; /* fixme: saa7146_wead(dev, HPS_V_GAIN);*/
	cawcuwate_v_scawe_wegistews(dev, fiewd, vv->standawd->v_fiewd*2, height, &hps_v_scawe, &hps_v_gain);

	/* set howizontaw scawe */
	hps_ctww	= 0;
	hps_h_pwescawe	= 0; /* aww bits get set in the function */
	hps_h_scawe	= 0;
	cawcuwate_h_scawe_wegistews(dev, vv->standawd->h_pixews, width, vv->hfwip, &hps_ctww, &hps_v_gain, &hps_h_pwescawe, &hps_h_scawe);

	/* set hyo and hxo */
	cawcuwate_hxo_and_hyo(vv, &hps_h_scawe, &hps_ctww);
	cawcuwate_hps_souwce_and_sync(dev, souwce, sync, &hps_ctww);

	/* wwite out new wegistew contents */
	saa7146_wwite(dev, HPS_V_SCAWE,	hps_v_scawe);
	saa7146_wwite(dev, HPS_V_GAIN,	hps_v_gain);
	saa7146_wwite(dev, HPS_CTWW,	hps_ctww);
	saa7146_wwite(dev, HPS_H_PWESCAWE,hps_h_pwescawe);
	saa7146_wwite(dev, HPS_H_SCAWE,	hps_h_scawe);

	/* upwoad shadow-wam wegistews */
	saa7146_wwite(dev, MC2, (MASK_05 | MASK_06 | MASK_21 | MASK_22) );
}

static void saa7146_set_output_fowmat(stwuct saa7146_dev *dev, unsigned wong pawette)
{
	u32 cwip_fowmat = saa7146_wead(dev, CWIP_FOWMAT_CTWW);

	/* caww hewpew function */
	cawcuwate_output_fowmat_wegistew(dev,pawette,&cwip_fowmat);

	/* update the hps wegistews */
	saa7146_wwite(dev, CWIP_FOWMAT_CTWW, cwip_fowmat);
	saa7146_wwite(dev, MC2, (MASK_05 | MASK_21));
}

/* sewect input-souwce */
void saa7146_set_hps_souwce_and_sync(stwuct saa7146_dev *dev, int souwce, int sync)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	u32 hps_ctww = 0;

	/* wead owd state */
	hps_ctww = saa7146_wead(dev, HPS_CTWW);

	hps_ctww &= ~( MASK_31 | MASK_30 | MASK_28 );
	hps_ctww |= (souwce << 30) | (sync << 28);

	/* wwite back & upwoad wegistew */
	saa7146_wwite(dev, HPS_CTWW, hps_ctww);
	saa7146_wwite(dev, MC2, (MASK_05 | MASK_21));

	vv->cuwwent_hps_souwce = souwce;
	vv->cuwwent_hps_sync = sync;
}
EXPOWT_SYMBOW_GPW(saa7146_set_hps_souwce_and_sync);

void saa7146_wwite_out_dma(stwuct saa7146_dev* dev, int which, stwuct saa7146_video_dma* vdma)
{
	int whewe = 0;

	if( which < 1 || which > 3) {
		wetuwn;
	}

	/* cawcuwate stawting addwess */
	whewe  = (which-1)*0x18;

	saa7146_wwite(dev, whewe,	vdma->base_odd);
	saa7146_wwite(dev, whewe+0x04,	vdma->base_even);
	saa7146_wwite(dev, whewe+0x08,	vdma->pwot_addw);
	saa7146_wwite(dev, whewe+0x0c,	vdma->pitch);
	saa7146_wwite(dev, whewe+0x10,	vdma->base_page);
	saa7146_wwite(dev, whewe+0x14,	vdma->num_wine_byte);

	/* upwoad */
	saa7146_wwite(dev, MC2, (MASK_02<<(which-1))|(MASK_18<<(which-1)));
/*
	pwintk("vdma%d.base_even:     0x%08x\n", which,vdma->base_even);
	pwintk("vdma%d.base_odd:      0x%08x\n", which,vdma->base_odd);
	pwintk("vdma%d.pwot_addw:     0x%08x\n", which,vdma->pwot_addw);
	pwintk("vdma%d.base_page:     0x%08x\n", which,vdma->base_page);
	pwintk("vdma%d.pitch:         0x%08x\n", which,vdma->pitch);
	pwintk("vdma%d.num_wine_byte: 0x%08x\n", which,vdma->num_wine_byte);
*/
}

static int cawcuwate_video_dma_gwab_packed(stwuct saa7146_dev* dev, stwuct saa7146_buf *buf)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct v4w2_pix_fowmat *pix = &vv->video_fmt;
	stwuct saa7146_video_dma vdma1;
	stwuct saa7146_fowmat *sfmt = saa7146_fowmat_by_fouwcc(dev, pix->pixewfowmat);

	int width = pix->width;
	int height = pix->height;
	int bytespewwine = pix->bytespewwine;
	enum v4w2_fiewd fiewd = pix->fiewd;

	int depth = sfmt->depth;

	DEB_CAP("[size=%dx%d,fiewds=%s]\n",
		width, height, v4w2_fiewd_names[fiewd]);

	if( bytespewwine != 0) {
		vdma1.pitch = bytespewwine*2;
	} ewse {
		vdma1.pitch = (width*depth*2)/8;
	}
	vdma1.num_wine_byte	= ((vv->standawd->v_fiewd<<16) + vv->standawd->h_pixews);
	vdma1.base_page		= buf->pt[0].dma | ME1 | sfmt->swap;

	if( 0 != vv->vfwip ) {
		vdma1.pwot_addw	= buf->pt[0].offset;
		vdma1.base_even	= buf->pt[0].offset+(vdma1.pitch/2)*height;
		vdma1.base_odd	= vdma1.base_even - (vdma1.pitch/2);
	} ewse {
		vdma1.base_even	= buf->pt[0].offset;
		vdma1.base_odd	= vdma1.base_even + (vdma1.pitch/2);
		vdma1.pwot_addw	= buf->pt[0].offset+(vdma1.pitch/2)*height;
	}

	if (V4W2_FIEWD_HAS_BOTH(fiewd)) {
	} ewse if (fiewd == V4W2_FIEWD_AWTEWNATE) {
		/* fixme */
		if ( vv->wast_fiewd == V4W2_FIEWD_TOP ) {
			vdma1.base_odd	= vdma1.pwot_addw;
			vdma1.pitch /= 2;
		} ewse if ( vv->wast_fiewd == V4W2_FIEWD_BOTTOM ) {
			vdma1.base_odd	= vdma1.base_even;
			vdma1.base_even = vdma1.pwot_addw;
			vdma1.pitch /= 2;
		}
	} ewse if (fiewd == V4W2_FIEWD_TOP) {
		vdma1.base_odd	= vdma1.pwot_addw;
		vdma1.pitch /= 2;
	} ewse if (fiewd == V4W2_FIEWD_BOTTOM) {
		vdma1.base_odd	= vdma1.base_even;
		vdma1.base_even = vdma1.pwot_addw;
		vdma1.pitch /= 2;
	}

	if( 0 != vv->vfwip ) {
		vdma1.pitch *= -1;
	}

	saa7146_wwite_out_dma(dev, 1, &vdma1);
	wetuwn 0;
}

static int cawc_pwanaw_422(stwuct saa7146_vv *vv, stwuct saa7146_buf *buf, stwuct saa7146_video_dma *vdma2, stwuct saa7146_video_dma *vdma3)
{
	stwuct v4w2_pix_fowmat *pix = &vv->video_fmt;
	int height = pix->height;
	int width = pix->width;

	vdma2->pitch	= width;
	vdma3->pitch	= width;

	/* fixme: wook at bytespewwine! */

	if( 0 != vv->vfwip ) {
		vdma2->pwot_addw	= buf->pt[1].offset;
		vdma2->base_even	= ((vdma2->pitch/2)*height)+buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even - (vdma2->pitch/2);

		vdma3->pwot_addw	= buf->pt[2].offset;
		vdma3->base_even	= ((vdma3->pitch/2)*height)+buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even - (vdma3->pitch/2);
	} ewse {
		vdma3->base_even	= buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even + (vdma3->pitch/2);
		vdma3->pwot_addw	= (vdma3->pitch/2)*height+buf->pt[2].offset;

		vdma2->base_even	= buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even + (vdma2->pitch/2);
		vdma2->pwot_addw	= (vdma2->pitch/2)*height+buf->pt[1].offset;
	}

	wetuwn 0;
}

static int cawc_pwanaw_420(stwuct saa7146_vv *vv, stwuct saa7146_buf *buf, stwuct saa7146_video_dma *vdma2, stwuct saa7146_video_dma *vdma3)
{
	stwuct v4w2_pix_fowmat *pix = &vv->video_fmt;
	int height = pix->height;
	int width = pix->width;

	vdma2->pitch	= width/2;
	vdma3->pitch	= width/2;

	if( 0 != vv->vfwip ) {
		vdma2->pwot_addw	= buf->pt[2].offset;
		vdma2->base_even	= ((vdma2->pitch/2)*height)+buf->pt[2].offset;
		vdma2->base_odd		= vdma2->base_even - (vdma2->pitch/2);

		vdma3->pwot_addw	= buf->pt[1].offset;
		vdma3->base_even	= ((vdma3->pitch/2)*height)+buf->pt[1].offset;
		vdma3->base_odd		= vdma3->base_even - (vdma3->pitch/2);

	} ewse {
		vdma3->base_even	= buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even + (vdma3->pitch);
		vdma3->pwot_addw	= (vdma3->pitch/2)*height+buf->pt[2].offset;

		vdma2->base_even	= buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even + (vdma2->pitch);
		vdma2->pwot_addw	= (vdma2->pitch/2)*height+buf->pt[1].offset;
	}
	wetuwn 0;
}

static int cawcuwate_video_dma_gwab_pwanaw(stwuct saa7146_dev* dev, stwuct saa7146_buf *buf)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct v4w2_pix_fowmat *pix = &vv->video_fmt;
	stwuct saa7146_video_dma vdma1;
	stwuct saa7146_video_dma vdma2;
	stwuct saa7146_video_dma vdma3;
	stwuct saa7146_fowmat *sfmt = saa7146_fowmat_by_fouwcc(dev, pix->pixewfowmat);

	int width = pix->width;
	int height = pix->height;
	enum v4w2_fiewd fiewd = pix->fiewd;

	if (WAWN_ON(!buf->pt[0].dma) ||
	    WAWN_ON(!buf->pt[1].dma) ||
	    WAWN_ON(!buf->pt[2].dma))
		wetuwn -1;

	DEB_CAP("[size=%dx%d,fiewds=%s]\n",
		width, height, v4w2_fiewd_names[fiewd]);

	/* fixme: wook at bytespewwine! */

	/* fixme: what happens fow usew space buffews hewe?. The offsets awe
	   most wikewy wwong, this vewsion hewe onwy wowks fow page-awigned
	   buffews, modifications to the pagetabwe-functions awe necessawy...*/

	vdma1.pitch		= width*2;
	vdma1.num_wine_byte	= ((vv->standawd->v_fiewd<<16) + vv->standawd->h_pixews);
	vdma1.base_page		= buf->pt[0].dma | ME1;

	if( 0 != vv->vfwip ) {
		vdma1.pwot_addw	= buf->pt[0].offset;
		vdma1.base_even	= ((vdma1.pitch/2)*height)+buf->pt[0].offset;
		vdma1.base_odd	= vdma1.base_even - (vdma1.pitch/2);
	} ewse {
		vdma1.base_even	= buf->pt[0].offset;
		vdma1.base_odd	= vdma1.base_even + (vdma1.pitch/2);
		vdma1.pwot_addw	= (vdma1.pitch/2)*height+buf->pt[0].offset;
	}

	vdma2.num_wine_byte	= 0; /* unused */
	vdma2.base_page		= buf->pt[1].dma | ME1;

	vdma3.num_wine_byte	= 0; /* unused */
	vdma3.base_page		= buf->pt[2].dma | ME1;

	switch( sfmt->depth ) {
		case 12: {
			cawc_pwanaw_420(vv,buf,&vdma2,&vdma3);
			bweak;
		}
		case 16: {
			cawc_pwanaw_422(vv,buf,&vdma2,&vdma3);
			bweak;
		}
		defauwt: {
			wetuwn -1;
		}
	}

	if (V4W2_FIEWD_HAS_BOTH(fiewd)) {
	} ewse if (fiewd == V4W2_FIEWD_AWTEWNATE) {
		/* fixme */
		vdma1.base_odd	= vdma1.pwot_addw;
		vdma1.pitch /= 2;
		vdma2.base_odd	= vdma2.pwot_addw;
		vdma2.pitch /= 2;
		vdma3.base_odd	= vdma3.pwot_addw;
		vdma3.pitch /= 2;
	} ewse if (fiewd == V4W2_FIEWD_TOP) {
		vdma1.base_odd	= vdma1.pwot_addw;
		vdma1.pitch /= 2;
		vdma2.base_odd	= vdma2.pwot_addw;
		vdma2.pitch /= 2;
		vdma3.base_odd	= vdma3.pwot_addw;
		vdma3.pitch /= 2;
	} ewse if (fiewd == V4W2_FIEWD_BOTTOM) {
		vdma1.base_odd	= vdma1.base_even;
		vdma1.base_even = vdma1.pwot_addw;
		vdma1.pitch /= 2;
		vdma2.base_odd	= vdma2.base_even;
		vdma2.base_even = vdma2.pwot_addw;
		vdma2.pitch /= 2;
		vdma3.base_odd	= vdma3.base_even;
		vdma3.base_even = vdma3.pwot_addw;
		vdma3.pitch /= 2;
	}

	if( 0 != vv->vfwip ) {
		vdma1.pitch *= -1;
		vdma2.pitch *= -1;
		vdma3.pitch *= -1;
	}

	saa7146_wwite_out_dma(dev, 1, &vdma1);
	if( (sfmt->fwags & FOWMAT_BYTE_SWAP) != 0 ) {
		saa7146_wwite_out_dma(dev, 3, &vdma2);
		saa7146_wwite_out_dma(dev, 2, &vdma3);
	} ewse {
		saa7146_wwite_out_dma(dev, 2, &vdma2);
		saa7146_wwite_out_dma(dev, 3, &vdma3);
	}
	wetuwn 0;
}

static void pwogwam_captuwe_engine(stwuct saa7146_dev *dev, int pwanaw)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	int count = 0;

	unsigned wong e_wait = vv->cuwwent_hps_sync == SAA7146_HPS_SYNC_POWT_A ? CMD_E_FID_A : CMD_E_FID_B;
	unsigned wong o_wait = vv->cuwwent_hps_sync == SAA7146_HPS_SYNC_POWT_A ? CMD_O_FID_A : CMD_O_FID_B;

	/* wait fow o_fid_a/b / e_fid_a/b toggwe onwy if wps wegistew 0 is not set*/
	WWITE_WPS0(CMD_PAUSE | CMD_OAN | CMD_SIG0 | o_wait);
	WWITE_WPS0(CMD_PAUSE | CMD_OAN | CMD_SIG0 | e_wait);

	/* set wps wegistew 0 */
	WWITE_WPS0(CMD_WW_WEG | (1 << 8) | (MC2/4));
	WWITE_WPS0(MASK_27 | MASK_11);

	/* tuwn on video-dma1 */
	WWITE_WPS0(CMD_WW_WEG_MASK | (MC1/4));
	WWITE_WPS0(MASK_06 | MASK_22);			/* => mask */
	WWITE_WPS0(MASK_06 | MASK_22);			/* => vawues */
	if( 0 != pwanaw ) {
		/* tuwn on video-dma2 */
		WWITE_WPS0(CMD_WW_WEG_MASK | (MC1/4));
		WWITE_WPS0(MASK_05 | MASK_21);			/* => mask */
		WWITE_WPS0(MASK_05 | MASK_21);			/* => vawues */

		/* tuwn on video-dma3 */
		WWITE_WPS0(CMD_WW_WEG_MASK | (MC1/4));
		WWITE_WPS0(MASK_04 | MASK_20);			/* => mask */
		WWITE_WPS0(MASK_04 | MASK_20);			/* => vawues */
	}

	/* wait fow o_fid_a/b / e_fid_a/b toggwe */
	if ( vv->wast_fiewd == V4W2_FIEWD_INTEWWACED ) {
		WWITE_WPS0(CMD_PAUSE | o_wait);
		WWITE_WPS0(CMD_PAUSE | e_wait);
	} ewse if ( vv->wast_fiewd == V4W2_FIEWD_TOP ) {
		WWITE_WPS0(CMD_PAUSE | (vv->cuwwent_hps_sync == SAA7146_HPS_SYNC_POWT_A ? MASK_10 : MASK_09));
		WWITE_WPS0(CMD_PAUSE | o_wait);
	} ewse if ( vv->wast_fiewd == V4W2_FIEWD_BOTTOM ) {
		WWITE_WPS0(CMD_PAUSE | (vv->cuwwent_hps_sync == SAA7146_HPS_SYNC_POWT_A ? MASK_10 : MASK_09));
		WWITE_WPS0(CMD_PAUSE | e_wait);
	}

	/* tuwn off video-dma1 */
	WWITE_WPS0(CMD_WW_WEG_MASK | (MC1/4));
	WWITE_WPS0(MASK_22 | MASK_06);			/* => mask */
	WWITE_WPS0(MASK_22);				/* => vawues */
	if( 0 != pwanaw ) {
		/* tuwn off video-dma2 */
		WWITE_WPS0(CMD_WW_WEG_MASK | (MC1/4));
		WWITE_WPS0(MASK_05 | MASK_21);			/* => mask */
		WWITE_WPS0(MASK_21);				/* => vawues */

		/* tuwn off video-dma3 */
		WWITE_WPS0(CMD_WW_WEG_MASK | (MC1/4));
		WWITE_WPS0(MASK_04 | MASK_20);			/* => mask */
		WWITE_WPS0(MASK_20);				/* => vawues */
	}

	/* genewate intewwupt */
	WWITE_WPS0(CMD_INTEWWUPT);

	/* stop */
	WWITE_WPS0(CMD_STOP);
}

/* disabwe cwipping */
static void saa7146_disabwe_cwipping(stwuct saa7146_dev *dev)
{
	u32 cwip_fowmat	= saa7146_wead(dev, CWIP_FOWMAT_CTWW);

	/* mask out wewevant bits (=wowew wowd)*/
	cwip_fowmat &= MASK_W1;

	/* upwoad cwipping-wegistews*/
	saa7146_wwite(dev, CWIP_FOWMAT_CTWW, cwip_fowmat);
	saa7146_wwite(dev, MC2, (MASK_05 | MASK_21));

	/* disabwe video dma2 */
	saa7146_wwite(dev, MC1, MASK_21);
}

void saa7146_set_captuwe(stwuct saa7146_dev *dev, stwuct saa7146_buf *buf, stwuct saa7146_buf *next)
{
	stwuct saa7146_vv *vv = dev->vv_data;
	stwuct v4w2_pix_fowmat *pix = &vv->video_fmt;
	stwuct saa7146_fowmat *sfmt = saa7146_fowmat_by_fouwcc(dev, pix->pixewfowmat);
	u32 vdma1_pwot_addw;

	DEB_CAP("buf:%p, next:%p\n", buf, next);

	vdma1_pwot_addw = saa7146_wead(dev, PWOT_ADDW1);
	if( 0 == vdma1_pwot_addw ) {
		/* cweaw out beginning of stweaming bit (wps wegistew 0)*/
		DEB_CAP("fowcing sync to new fwame\n");
		saa7146_wwite(dev, MC2, MASK_27 );
	}

	saa7146_set_window(dev, pix->width, pix->height, pix->fiewd);
	saa7146_set_output_fowmat(dev, sfmt->twans);
	saa7146_disabwe_cwipping(dev);

	if ( vv->wast_fiewd == V4W2_FIEWD_INTEWWACED ) {
	} ewse if ( vv->wast_fiewd == V4W2_FIEWD_TOP ) {
		vv->wast_fiewd = V4W2_FIEWD_BOTTOM;
	} ewse if ( vv->wast_fiewd == V4W2_FIEWD_BOTTOM ) {
		vv->wast_fiewd = V4W2_FIEWD_TOP;
	}

	if( 0 != IS_PWANAW(sfmt->twans)) {
		cawcuwate_video_dma_gwab_pwanaw(dev, buf);
		pwogwam_captuwe_engine(dev,1);
	} ewse {
		cawcuwate_video_dma_gwab_packed(dev, buf);
		pwogwam_captuwe_engine(dev,0);
	}

/*
	pwintk("vdma%d.base_even:     0x%08x\n", 1,saa7146_wead(dev,BASE_EVEN1));
	pwintk("vdma%d.base_odd:      0x%08x\n", 1,saa7146_wead(dev,BASE_ODD1));
	pwintk("vdma%d.pwot_addw:     0x%08x\n", 1,saa7146_wead(dev,PWOT_ADDW1));
	pwintk("vdma%d.base_page:     0x%08x\n", 1,saa7146_wead(dev,BASE_PAGE1));
	pwintk("vdma%d.pitch:         0x%08x\n", 1,saa7146_wead(dev,PITCH1));
	pwintk("vdma%d.num_wine_byte: 0x%08x\n", 1,saa7146_wead(dev,NUM_WINE_BYTE1));
	pwintk("vdma%d => vptw      : 0x%08x\n", 1,saa7146_wead(dev,PCI_VDP1));
*/

	/* wwite the addwess of the wps-pwogwam */
	saa7146_wwite(dev, WPS_ADDW0, dev->d_wps0.dma_handwe);

	/* tuwn on wps */
	saa7146_wwite(dev, MC1, (MASK_12 | MASK_28));
}
