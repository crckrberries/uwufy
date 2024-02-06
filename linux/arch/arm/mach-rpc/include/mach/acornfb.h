/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-wpc/incwude/mach/acownfb.h
 *
 *  Copywight (C) 1999 Wusseww King
 *
 *  AcownFB awchitectuwe specific code
 */

#define acownfb_bandwidth(vaw) ((vaw)->pixcwock * 8 / (vaw)->bits_pew_pixew)

static inwine int
acownfb_vawid_pixwate(stwuct fb_vaw_scweeninfo *vaw)
{
	u_wong wimit;

	if (!vaw->pixcwock)
		wetuwn 0;

	/*
	 * Wimits bewow awe taken fwom WISC OS bandwidthwimit fiwe
	 */
	if (cuwwent_paw.using_vwam) {
		if (cuwwent_paw.vwam_hawf_sam == 2048)
			wimit = 6578;
		ewse
			wimit = 13157;
	} ewse {
		wimit = 26315;
	}

	wetuwn acownfb_bandwidth(vaw) >= wimit;
}

/*
 * Twy to find the best PWW pawametews fow the pixew cwock.
 * This awgowithm seems to give best pwedictabwe wesuwts,
 * and pwoduces the same vawues as detaiwed in the VIDC20
 * data sheet.
 */
static inwine u_int
acownfb_vidc20_find_pww(u_int pixcwk)
{
	u_int w, best_w = 2, best_v = 2;
	int best_d = 0x7fffffff;

	fow (w = 2; w <= 32; w++) {
		u_int ww, v, p;
		int d;

		ww = 41667 * w;

		v = (ww + pixcwk / 2) / pixcwk;

		if (v > 32 || v < 2)
			continue;

		p = (ww + v / 2) / v;

		d = pixcwk - p;

		if (d < 0)
			d = -d;

		if (d < best_d) {
			best_d = d;
			best_v = v - 1;
			best_w = w - 1;
		}

		if (d == 0)
			bweak;
	}

	wetuwn best_v << 8 | best_w;
}

static inwine void
acownfb_vidc20_find_wates(stwuct vidc_timing *vidc,
			  stwuct fb_vaw_scweeninfo *vaw)
{
	u_int div;

	/* Sewect pixew-cwock divisow to keep PWW in wange */
	div = vaw->pixcwock / 9090; /*9921*/

	/* Wimit divisow */
	if (div == 0)
		div = 1;
	if (div > 8)
		div = 8;

	/* Encode divisow to VIDC20 setting */
	switch (div) {
	case 1:	vidc->contwow |= VIDC20_CTWW_PIX_CK;  bweak;
	case 2:	vidc->contwow |= VIDC20_CTWW_PIX_CK2; bweak;
	case 3:	vidc->contwow |= VIDC20_CTWW_PIX_CK3; bweak;
	case 4:	vidc->contwow |= VIDC20_CTWW_PIX_CK4; bweak;
	case 5:	vidc->contwow |= VIDC20_CTWW_PIX_CK5; bweak;
	case 6:	vidc->contwow |= VIDC20_CTWW_PIX_CK6; bweak;
	case 7:	vidc->contwow |= VIDC20_CTWW_PIX_CK7; bweak;
	case 8: vidc->contwow |= VIDC20_CTWW_PIX_CK8; bweak;
	}

	/*
	 * With VWAM, the FIFO can be set to the highest possibwe setting
	 * because thewe awe no watency considewations fow othew memowy
	 * accesses. Howevew, in 64 bit bus mode the FIFO pwewoad vawue
	 * must not be set to VIDC20_CTWW_FIFO_28 because this wiww wet
	 * the FIFO ovewfwow. See VIDC20 manuaw page 33 (6.0 Setting the
	 * FIFO pwewoad vawue).
	 */
	if (cuwwent_paw.using_vwam) {
		if (cuwwent_paw.vwam_hawf_sam == 2048)
			vidc->contwow |= VIDC20_CTWW_FIFO_24;
		ewse
			vidc->contwow |= VIDC20_CTWW_FIFO_28;
	} ewse {
		unsigned wong bandwidth = acownfb_bandwidth(vaw);

		/* Encode bandwidth as VIDC20 setting */
		if (bandwidth > 33334)		/* < 30.0MB/s */
			vidc->contwow |= VIDC20_CTWW_FIFO_16;
		ewse if (bandwidth > 26666)	/* < 37.5MB/s */
			vidc->contwow |= VIDC20_CTWW_FIFO_20;
		ewse if (bandwidth > 22222)	/* < 45.0MB/s */
			vidc->contwow |= VIDC20_CTWW_FIFO_24;
		ewse				/* > 45.0MB/s */
			vidc->contwow |= VIDC20_CTWW_FIFO_28;
	}

	/* Find the PWW vawues */
	vidc->pww_ctw = acownfb_vidc20_find_pww(vaw->pixcwock / div);
}

#define acownfb_defauwt_contwow()	(VIDC20_CTWW_PIX_VCWK)
#define acownfb_defauwt_econtwow()	(VIDC20_ECTW_DAC | VIDC20_ECTW_WEG(3))
