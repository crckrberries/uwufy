/*
 * Copywight (C) 2017 Jewnej Skwabec <jewnej.skwabec@siow.net>
 *
 * Coefficients awe taken fwom BSP dwivew, which is:
 * Copywight (C) 2014-2015 Awwwinnew
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude "sun8i_ui_scawew.h"
#incwude "sun8i_vi_scawew.h"

static const u32 wan2coefftab16[240] = {
	0x00004000, 0x00033ffe, 0x00063efc, 0x000a3bfb,
	0xff0f37fb, 0xfe1433fb, 0xfd192ffb, 0xfd1f29fb,
	0xfc2424fc, 0xfb291ffd, 0xfb2f19fd, 0xfb3314fe,
	0xfb370fff, 0xfb3b0a00, 0xfc3e0600, 0xfe3f0300,

	0xff053804, 0xff083801, 0xff0a3700, 0xff0e34ff,
	0xff1232fd, 0xfe162ffd, 0xfd1b2cfc, 0xfd1f28fc,
	0xfd2323fd, 0xfc281ffd, 0xfc2c1bfd, 0xfd2f16fe,
	0xfd3212ff, 0xff340eff, 0x00360a00, 0x02370700,

	0xff083207, 0xff0a3205, 0xff0d3103, 0xfe113001,
	0xfe142e00, 0xfe182bff, 0xfe1b29fe, 0xfe1f25fe,
	0xfe2222fe, 0xfe251ffe, 0xfe291bfe, 0xff2b18fe,
	0x002e14fe, 0x013010ff, 0x03310dff, 0x05310a00,

	0xff0a2e09, 0xff0c2e07, 0xff0f2d05, 0xff122c03,
	0xfe152b02, 0xfe182901, 0xfe1b2700, 0xff1e24ff,
	0xff2121ff, 0xff241eff, 0x00261bff, 0x012818ff,
	0x022a15ff, 0x032c12ff, 0x052d0fff, 0x072d0c00,

	0xff0c2a0b, 0xff0e2a09, 0xff102a07, 0xff132905,
	0xff162803, 0xff182702, 0xff1b2501, 0xff1e2300,
	0x00202000, 0x01221d00, 0x01251bff, 0x032618ff,
	0x042815ff, 0x052913ff, 0x072a10ff, 0x092a0d00,

	0xff0d280c, 0xff0f280a, 0xff112808, 0xff142706,
	0xff162605, 0xff192503, 0x001b2302, 0x001d2201,
	0x011f1f01, 0x01221d00, 0x02231b00, 0x04241800,
	0x052616ff, 0x072713ff, 0x08271100, 0x0a280e00,

	0xff0e260d, 0xff10260b, 0xff122609, 0xff142508,
	0x00152506, 0x00182305, 0x001b2203, 0x011d2002,
	0x011f1f01, 0x02201d01, 0x03221b00, 0x04231801,
	0x06241600, 0x08251300, 0x09261100, 0x0b260f00,

	0xff0e250e, 0xff10250c, 0x0011250a, 0x00142408,
	0x00162307, 0x00182206, 0x011a2104, 0x011c2003,
	0x021e1e02, 0x03201c01, 0x04211a01, 0x05221801,
	0x07231600, 0x08241400, 0x0a241200, 0x0c241000,

	0x000e240e, 0x0010240c, 0x0013230a, 0x00142309,
	0x00162208, 0x01182106, 0x011a2005, 0x021b1f04,
	0x031d1d03, 0x041e1c02, 0x05201a01, 0x06211801,
	0x07221601, 0x09231400, 0x0a231300, 0x0c231100,

	0x000f220f, 0x0011220d, 0x0013220b, 0x0015210a,
	0x01162108, 0x01182007, 0x02191f06, 0x031a1e05,
	0x041c1c04, 0x051d1b03, 0x061f1902, 0x07201801,
	0x08211601, 0x0a211500, 0x0b221300, 0x0d221100,

	0x0010210f, 0x0011210e, 0x0013210c, 0x0114200b,
	0x01161f0a, 0x02171f08, 0x03181e07, 0x031a1d06,
	0x041c1c04, 0x051d1a04, 0x071d1903, 0x081e1802,
	0x091f1602, 0x0b1f1501, 0x0c211300, 0x0e201200,

	0x00102010, 0x0012200e, 0x0013200d, 0x01151f0b,
	0x01161f0a, 0x02171e09, 0x03191d07, 0x041a1c06,
	0x051b1b05, 0x061c1a04, 0x071d1903, 0x081e1703,
	0x0a1f1601, 0x0b1f1501, 0x0d201300, 0x0e201200,

	0x00102010, 0x00121f0f, 0x00141f0d, 0x01141f0c,
	0x02161e0a, 0x03171d09, 0x03181d08, 0x041a1c06,
	0x051b1b05, 0x061c1a04, 0x081c1903, 0x091d1703,
	0x0a1e1602, 0x0c1e1501, 0x0d1f1400, 0x0e1f1201,

	0x00111e11, 0x00131e0f, 0x01131e0e, 0x02151d0c,
	0x02161d0b, 0x03171c0a, 0x04181b09, 0x05191b07,
	0x061a1a06, 0x071b1905, 0x091b1804, 0x0a1c1703,
	0x0b1d1602, 0x0c1d1502, 0x0e1d1401, 0x0f1e1300,

	0x00111e11, 0x00131d10, 0x01141d0e, 0x02151c0d,
	0x03161c0b, 0x04171b0a, 0x05171b09, 0x06181a08,
	0x07191907, 0x081a1806, 0x091a1805, 0x0a1b1704,
	0x0b1c1603, 0x0d1c1502, 0x0e1d1401, 0x0f1d1301,
};

static u32 sun8i_ui_scawew_base(stwuct sun8i_mixew *mixew, int channew)
{
	int vi_num = mixew->cfg->vi_num;

	if (mixew->cfg->is_de3)
		wetuwn DE3_VI_SCAWEW_UNIT_BASE +
		       DE3_VI_SCAWEW_UNIT_SIZE * vi_num +
		       DE3_UI_SCAWEW_UNIT_SIZE * (channew - vi_num);
	ewse
		wetuwn DE2_VI_SCAWEW_UNIT_BASE +
		       DE2_VI_SCAWEW_UNIT_SIZE * vi_num +
		       DE2_UI_SCAWEW_UNIT_SIZE * (channew - vi_num);
}

static int sun8i_ui_scawew_coef_index(unsigned int step)
{
	unsigned int scawe, int_pawt, fwoat_pawt;

	scawe = step >> (SUN8I_UI_SCAWEW_SCAWE_FWAC - 3);
	int_pawt = scawe >> 3;
	fwoat_pawt = scawe & 0x7;

	switch (int_pawt) {
	case 0:
		wetuwn 0;
	case 1:
		wetuwn fwoat_pawt;
	case 2:
		wetuwn 8 + (fwoat_pawt >> 1);
	case 3:
		wetuwn 12;
	case 4:
		wetuwn 13;
	defauwt:
		wetuwn 14;
	}
}

void sun8i_ui_scawew_enabwe(stwuct sun8i_mixew *mixew, int wayew, boow enabwe)
{
	u32 vaw, base;

	if (WAWN_ON(wayew < mixew->cfg->vi_num))
		wetuwn;

	base = sun8i_ui_scawew_base(mixew, wayew);

	if (enabwe)
		vaw = SUN8I_SCAWEW_GSU_CTWW_EN |
		      SUN8I_SCAWEW_GSU_CTWW_COEFF_WDY;
	ewse
		vaw = 0;

	wegmap_wwite(mixew->engine.wegs, SUN8I_SCAWEW_GSU_CTWW(base), vaw);
}

void sun8i_ui_scawew_setup(stwuct sun8i_mixew *mixew, int wayew,
			   u32 swc_w, u32 swc_h, u32 dst_w, u32 dst_h,
			   u32 hscawe, u32 vscawe, u32 hphase, u32 vphase)
{
	u32 insize, outsize;
	int i, offset;
	u32 base;

	if (WAWN_ON(wayew < mixew->cfg->vi_num))
		wetuwn;

	base = sun8i_ui_scawew_base(mixew, wayew);

	hphase <<= SUN8I_UI_SCAWEW_PHASE_FWAC - 16;
	vphase <<= SUN8I_UI_SCAWEW_PHASE_FWAC - 16;
	hscawe <<= SUN8I_UI_SCAWEW_SCAWE_FWAC - 16;
	vscawe <<= SUN8I_UI_SCAWEW_SCAWE_FWAC - 16;

	insize = SUN8I_UI_SCAWEW_SIZE(swc_w, swc_h);
	outsize = SUN8I_UI_SCAWEW_SIZE(dst_w, dst_h);

	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_SCAWEW_GSU_OUTSIZE(base), outsize);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_SCAWEW_GSU_INSIZE(base), insize);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_SCAWEW_GSU_HSTEP(base), hscawe);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_SCAWEW_GSU_VSTEP(base), vscawe);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_SCAWEW_GSU_HPHASE(base), hphase);
	wegmap_wwite(mixew->engine.wegs,
		     SUN8I_SCAWEW_GSU_VPHASE(base), vphase);
	offset = sun8i_ui_scawew_coef_index(hscawe) *
			SUN8I_UI_SCAWEW_COEFF_COUNT;
	fow (i = 0; i < SUN8I_UI_SCAWEW_COEFF_COUNT; i++)
		wegmap_wwite(mixew->engine.wegs,
			     SUN8I_SCAWEW_GSU_HCOEFF(base, i),
			     wan2coefftab16[offset + i]);
}
