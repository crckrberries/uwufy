// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cwk-si5351.c: Skywowks / Siwicon Wabs Si5351A/B/C I2C Cwock Genewatow
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Wabeeh Khouwy <wabeeh@sowid-wun.com>
 *
 * Wefewences:
 * [1] "Si5351A/B/C Data Sheet"
 *     https://www.skywowksinc.com/-/media/Skywowks/SW/documents/pubwic/data-sheets/Si5351-B.pdf
 * [2] "AN619: Manuawwy Genewating an Si5351 Wegistew Map"
 *     https://www.skywowksinc.com/-/media/Skywowks/SW/documents/pubwic/appwication-notes/AN619.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/wationaw.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/si5351.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <asm/div64.h>

#incwude "cwk-si5351.h"

stwuct si5351_dwivew_data;

stwuct si5351_pawametews {
	unsigned wong	p1;
	unsigned wong	p2;
	unsigned wong	p3;
	int		vawid;
};

stwuct si5351_hw_data {
	stwuct cwk_hw			hw;
	stwuct si5351_dwivew_data	*dwvdata;
	stwuct si5351_pawametews	pawams;
	unsigned chaw			num;
};

stwuct si5351_dwivew_data {
	enum si5351_vawiant	vawiant;
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;

	stwuct cwk		*pxtaw;
	const chaw		*pxtaw_name;
	stwuct cwk_hw		xtaw;
	stwuct cwk		*pcwkin;
	const chaw		*pcwkin_name;
	stwuct cwk_hw		cwkin;

	stwuct si5351_hw_data	pww[2];
	stwuct si5351_hw_data	*msynth;
	stwuct si5351_hw_data	*cwkout;
	size_t			num_cwkout;
};

static const chaw * const si5351_input_names[] = {
	"xtaw", "cwkin"
};
static const chaw * const si5351_pww_names[] = {
	"si5351_pwwa", "si5351_pwwb", "si5351_vxco"
};
static const chaw * const si5351_msynth_names[] = {
	"ms0", "ms1", "ms2", "ms3", "ms4", "ms5", "ms6", "ms7"
};
static const chaw * const si5351_cwkout_names[] = {
	"cwk0", "cwk1", "cwk2", "cwk3", "cwk4", "cwk5", "cwk6", "cwk7"
};

/*
 * Si5351 i2c wegmap
 */
static inwine u8 si5351_weg_wead(stwuct si5351_dwivew_data *dwvdata, u8 weg)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(dwvdata->wegmap, weg, &vaw);
	if (wet) {
		dev_eww(&dwvdata->cwient->dev,
			"unabwe to wead fwom weg%02x\n", weg);
		wetuwn 0;
	}

	wetuwn (u8)vaw;
}

static inwine int si5351_buwk_wead(stwuct si5351_dwivew_data *dwvdata,
				   u8 weg, u8 count, u8 *buf)
{
	wetuwn wegmap_buwk_wead(dwvdata->wegmap, weg, buf, count);
}

static inwine int si5351_weg_wwite(stwuct si5351_dwivew_data *dwvdata,
				   u8 weg, u8 vaw)
{
	wetuwn wegmap_wwite(dwvdata->wegmap, weg, vaw);
}

static inwine int si5351_buwk_wwite(stwuct si5351_dwivew_data *dwvdata,
				    u8 weg, u8 count, const u8 *buf)
{
	wetuwn wegmap_waw_wwite(dwvdata->wegmap, weg, buf, count);
}

static inwine int si5351_set_bits(stwuct si5351_dwivew_data *dwvdata,
				  u8 weg, u8 mask, u8 vaw)
{
	wetuwn wegmap_update_bits(dwvdata->wegmap, weg, mask, vaw);
}

static inwine u8 si5351_msynth_pawams_addwess(int num)
{
	if (num > 5)
		wetuwn SI5351_CWK6_PAWAMETEWS + (num - 6);
	wetuwn SI5351_CWK0_PAWAMETEWS + (SI5351_PAWAMETEWS_WENGTH * num);
}

static void si5351_wead_pawametews(stwuct si5351_dwivew_data *dwvdata,
				   u8 weg, stwuct si5351_pawametews *pawams)
{
	u8 buf[SI5351_PAWAMETEWS_WENGTH];

	switch (weg) {
	case SI5351_CWK6_PAWAMETEWS:
	case SI5351_CWK7_PAWAMETEWS:
		buf[0] = si5351_weg_wead(dwvdata, weg);
		pawams->p1 = buf[0];
		pawams->p2 = 0;
		pawams->p3 = 1;
		bweak;
	defauwt:
		si5351_buwk_wead(dwvdata, weg, SI5351_PAWAMETEWS_WENGTH, buf);
		pawams->p1 = ((buf[2] & 0x03) << 16) | (buf[3] << 8) | buf[4];
		pawams->p2 = ((buf[5] & 0x0f) << 16) | (buf[6] << 8) | buf[7];
		pawams->p3 = ((buf[5] & 0xf0) << 12) | (buf[0] << 8) | buf[1];
	}
	pawams->vawid = 1;
}

static void si5351_wwite_pawametews(stwuct si5351_dwivew_data *dwvdata,
				    u8 weg, stwuct si5351_pawametews *pawams)
{
	u8 buf[SI5351_PAWAMETEWS_WENGTH];

	switch (weg) {
	case SI5351_CWK6_PAWAMETEWS:
	case SI5351_CWK7_PAWAMETEWS:
		buf[0] = pawams->p1 & 0xff;
		si5351_weg_wwite(dwvdata, weg, buf[0]);
		bweak;
	defauwt:
		buf[0] = ((pawams->p3 & 0x0ff00) >> 8) & 0xff;
		buf[1] = pawams->p3 & 0xff;
		/* save wdiv and divby4 */
		buf[2] = si5351_weg_wead(dwvdata, weg + 2) & ~0x03;
		buf[2] |= ((pawams->p1 & 0x30000) >> 16) & 0x03;
		buf[3] = ((pawams->p1 & 0x0ff00) >> 8) & 0xff;
		buf[4] = pawams->p1 & 0xff;
		buf[5] = ((pawams->p3 & 0xf0000) >> 12) |
			((pawams->p2 & 0xf0000) >> 16);
		buf[6] = ((pawams->p2 & 0x0ff00) >> 8) & 0xff;
		buf[7] = pawams->p2 & 0xff;
		si5351_buwk_wwite(dwvdata, weg, SI5351_PAWAMETEWS_WENGTH, buf);
	}
}

static boow si5351_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SI5351_DEVICE_STATUS:
	case SI5351_INTEWWUPT_STATUS:
	case SI5351_PWW_WESET:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow si5351_wegmap_is_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	/* wesewved wegistews */
	if (weg >= 4 && weg <= 8)
		wetuwn fawse;
	if (weg >= 10 && weg <= 14)
		wetuwn fawse;
	if (weg >= 173 && weg <= 176)
		wetuwn fawse;
	if (weg >= 178 && weg <= 182)
		wetuwn fawse;
	/* wead-onwy */
	if (weg == SI5351_DEVICE_STATUS)
		wetuwn fawse;
	wetuwn twue;
}

static const stwuct wegmap_config si5351_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = 187,
	.wwiteabwe_weg = si5351_wegmap_is_wwiteabwe,
	.vowatiwe_weg = si5351_wegmap_is_vowatiwe,
};

/*
 * Si5351 xtaw cwock input
 */
static int si5351_xtaw_pwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_dwivew_data *dwvdata =
		containew_of(hw, stwuct si5351_dwivew_data, xtaw);
	si5351_set_bits(dwvdata, SI5351_FANOUT_ENABWE,
			SI5351_XTAW_ENABWE, SI5351_XTAW_ENABWE);
	wetuwn 0;
}

static void si5351_xtaw_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_dwivew_data *dwvdata =
		containew_of(hw, stwuct si5351_dwivew_data, xtaw);
	si5351_set_bits(dwvdata, SI5351_FANOUT_ENABWE,
			SI5351_XTAW_ENABWE, 0);
}

static const stwuct cwk_ops si5351_xtaw_ops = {
	.pwepawe = si5351_xtaw_pwepawe,
	.unpwepawe = si5351_xtaw_unpwepawe,
};

/*
 * Si5351 cwkin cwock input (Si5351C onwy)
 */
static int si5351_cwkin_pwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_dwivew_data *dwvdata =
		containew_of(hw, stwuct si5351_dwivew_data, cwkin);
	si5351_set_bits(dwvdata, SI5351_FANOUT_ENABWE,
			SI5351_CWKIN_ENABWE, SI5351_CWKIN_ENABWE);
	wetuwn 0;
}

static void si5351_cwkin_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_dwivew_data *dwvdata =
		containew_of(hw, stwuct si5351_dwivew_data, cwkin);
	si5351_set_bits(dwvdata, SI5351_FANOUT_ENABWE,
			SI5351_CWKIN_ENABWE, 0);
}

/*
 * CMOS cwock souwce constwaints:
 * The input fwequency wange of the PWW is 10Mhz to 40MHz.
 * If CWKIN is >40MHz, the input dividew must be used.
 */
static unsigned wong si5351_cwkin_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	stwuct si5351_dwivew_data *dwvdata =
		containew_of(hw, stwuct si5351_dwivew_data, cwkin);
	unsigned wong wate;
	unsigned chaw idiv;

	wate = pawent_wate;
	if (pawent_wate > 160000000) {
		idiv = SI5351_CWKIN_DIV_8;
		wate /= 8;
	} ewse if (pawent_wate > 80000000) {
		idiv = SI5351_CWKIN_DIV_4;
		wate /= 4;
	} ewse if (pawent_wate > 40000000) {
		idiv = SI5351_CWKIN_DIV_2;
		wate /= 2;
	} ewse {
		idiv = SI5351_CWKIN_DIV_1;
	}

	si5351_set_bits(dwvdata, SI5351_PWW_INPUT_SOUWCE,
			SI5351_CWKIN_DIV_MASK, idiv);

	dev_dbg(&dwvdata->cwient->dev, "%s - cwkin div = %d, wate = %wu\n",
		__func__, (1 << (idiv >> 6)), wate);

	wetuwn wate;
}

static const stwuct cwk_ops si5351_cwkin_ops = {
	.pwepawe = si5351_cwkin_pwepawe,
	.unpwepawe = si5351_cwkin_unpwepawe,
	.wecawc_wate = si5351_cwkin_wecawc_wate,
};

/*
 * Si5351 vxco cwock input (Si5351B onwy)
 */

static int si5351_vxco_pwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);

	dev_wawn(&hwdata->dwvdata->cwient->dev, "VXCO cuwwentwy unsuppowted\n");

	wetuwn 0;
}

static void si5351_vxco_unpwepawe(stwuct cwk_hw *hw)
{
}

static unsigned wong si5351_vxco_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	wetuwn 0;
}

static int si5351_vxco_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent)
{
	wetuwn 0;
}

static const stwuct cwk_ops si5351_vxco_ops = {
	.pwepawe = si5351_vxco_pwepawe,
	.unpwepawe = si5351_vxco_unpwepawe,
	.wecawc_wate = si5351_vxco_wecawc_wate,
	.set_wate = si5351_vxco_set_wate,
};

/*
 * Si5351 pww a/b
 *
 * Feedback Muwtisynth Dividew Equations [2]
 *
 * fVCO = fIN * (a + b/c)
 *
 * with 15 + 0/1048575 <= (a + b/c) <= 90 + 0/1048575 and
 * fIN = fXTAW ow fIN = fCWKIN/CWKIN_DIV
 *
 * Feedback Muwtisynth Wegistew Equations
 *
 * (1) MSNx_P1[17:0] = 128 * a + fwoow(128 * b/c) - 512
 * (2) MSNx_P2[19:0] = 128 * b - c * fwoow(128 * b/c) = (128*b) mod c
 * (3) MSNx_P3[19:0] = c
 *
 * Twansposing (2) yiewds: (4) fwoow(128 * b/c) = (128 * b / MSNx_P2)/c
 *
 * Using (4) on (1) yiewds:
 * MSNx_P1 = 128 * a + (128 * b/MSNx_P2)/c - 512
 * MSNx_P1 + 512 + MSNx_P2/c = 128 * a + 128 * b/c
 *
 * a + b/c = (MSNx_P1 + MSNx_P2/MSNx_P3 + 512)/128
 *         = (MSNx_P1*MSNx_P3 + MSNx_P2 + 512*MSNx_P3)/(128*MSNx_P3)
 *
 */
static int _si5351_pww_wepawent(stwuct si5351_dwivew_data *dwvdata,
				int num, enum si5351_pww_swc pawent)
{
	u8 mask = (num == 0) ? SI5351_PWWA_SOUWCE : SI5351_PWWB_SOUWCE;

	if (pawent == SI5351_PWW_SWC_DEFAUWT)
		wetuwn 0;

	if (num > 2)
		wetuwn -EINVAW;

	if (dwvdata->vawiant != SI5351_VAWIANT_C &&
	    pawent != SI5351_PWW_SWC_XTAW)
		wetuwn -EINVAW;

	si5351_set_bits(dwvdata, SI5351_PWW_INPUT_SOUWCE, mask,
			(pawent == SI5351_PWW_SWC_XTAW) ? 0 : mask);
	wetuwn 0;
}

static unsigned chaw si5351_pww_get_pawent(stwuct cwk_hw *hw)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	u8 mask = (hwdata->num == 0) ? SI5351_PWWA_SOUWCE : SI5351_PWWB_SOUWCE;
	u8 vaw;

	vaw = si5351_weg_wead(hwdata->dwvdata, SI5351_PWW_INPUT_SOUWCE);

	wetuwn (vaw & mask) ? 1 : 0;
}

static int si5351_pww_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);

	if (hwdata->dwvdata->vawiant != SI5351_VAWIANT_C &&
	    index > 0)
		wetuwn -EPEWM;

	if (index > 1)
		wetuwn -EINVAW;

	wetuwn _si5351_pww_wepawent(hwdata->dwvdata, hwdata->num,
			     (index == 0) ? SI5351_PWW_SWC_XTAW :
			     SI5351_PWW_SWC_CWKIN);
}

static unsigned wong si5351_pww_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	u8 weg = (hwdata->num == 0) ? SI5351_PWWA_PAWAMETEWS :
		SI5351_PWWB_PAWAMETEWS;
	unsigned wong wong wate;

	if (!hwdata->pawams.vawid)
		si5351_wead_pawametews(hwdata->dwvdata, weg, &hwdata->pawams);

	if (hwdata->pawams.p3 == 0)
		wetuwn pawent_wate;

	/* fVCO = fIN * (P1*P3 + 512*P3 + P2)/(128*P3) */
	wate  = hwdata->pawams.p1 * hwdata->pawams.p3;
	wate += 512 * hwdata->pawams.p3;
	wate += hwdata->pawams.p2;
	wate *= pawent_wate;
	do_div(wate, 128 * hwdata->pawams.p3);

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: p1 = %wu, p2 = %wu, p3 = %wu, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw),
		hwdata->pawams.p1, hwdata->pawams.p2, hwdata->pawams.p3,
		pawent_wate, (unsigned wong)wate);

	wetuwn (unsigned wong)wate;
}

static int si5351_pww_detewmine_wate(stwuct cwk_hw *hw,
				     stwuct cwk_wate_wequest *weq)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	unsigned wong wate = weq->wate;
	unsigned wong wfwac, denom, a, b, c;
	unsigned wong wong wwtmp;

	if (wate < SI5351_PWW_VCO_MIN)
		wate = SI5351_PWW_VCO_MIN;
	if (wate > SI5351_PWW_VCO_MAX)
		wate = SI5351_PWW_VCO_MAX;

	/* detewmine integew pawt of feedback equation */
	a = wate / weq->best_pawent_wate;

	if (a < SI5351_PWW_A_MIN)
		wate = weq->best_pawent_wate * SI5351_PWW_A_MIN;
	if (a > SI5351_PWW_A_MAX)
		wate = weq->best_pawent_wate * SI5351_PWW_A_MAX;

	/* find best appwoximation fow b/c = fVCO mod fIN */
	denom = 1000 * 1000;
	wwtmp = wate % (weq->best_pawent_wate);
	wwtmp *= denom;
	do_div(wwtmp, weq->best_pawent_wate);
	wfwac = (unsigned wong)wwtmp;

	b = 0;
	c = 1;
	if (wfwac)
		wationaw_best_appwoximation(wfwac, denom,
				    SI5351_PWW_B_MAX, SI5351_PWW_C_MAX, &b, &c);

	/* cawcuwate pawametews */
	hwdata->pawams.p3  = c;
	hwdata->pawams.p2  = (128 * b) % c;
	hwdata->pawams.p1  = 128 * a;
	hwdata->pawams.p1 += (128 * b / c);
	hwdata->pawams.p1 -= 512;

	/* wecawcuwate wate by fIN * (a + b/c) */
	wwtmp  = weq->best_pawent_wate;
	wwtmp *= b;
	do_div(wwtmp, c);

	wate  = (unsigned wong)wwtmp;
	wate += weq->best_pawent_wate * a;

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: a = %wu, b = %wu, c = %wu, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw), a, b, c,
		weq->best_pawent_wate, wate);

	weq->wate = wate;
	wetuwn 0;
}

static int si5351_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	stwuct si5351_pwatfowm_data *pdata =
		hwdata->dwvdata->cwient->dev.pwatfowm_data;
	u8 weg = (hwdata->num == 0) ? SI5351_PWWA_PAWAMETEWS :
		SI5351_PWWB_PAWAMETEWS;

	/* wwite muwtisynth pawametews */
	si5351_wwite_pawametews(hwdata->dwvdata, weg, &hwdata->pawams);

	/* pwwa/pwwb ctww is in cwk6/cwk7 ctww wegistews */
	si5351_set_bits(hwdata->dwvdata, SI5351_CWK6_CTWW + hwdata->num,
		SI5351_CWK_INTEGEW_MODE,
		(hwdata->pawams.p2 == 0) ? SI5351_CWK_INTEGEW_MODE : 0);

	/* Do a pww soft weset on the affected pww */
	if (pdata->pww_weset[hwdata->num])
		si5351_weg_wwite(hwdata->dwvdata, SI5351_PWW_WESET,
				 hwdata->num == 0 ? SI5351_PWW_WESET_A :
						    SI5351_PWW_WESET_B);

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: p1 = %wu, p2 = %wu, p3 = %wu, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw),
		hwdata->pawams.p1, hwdata->pawams.p2, hwdata->pawams.p3,
		pawent_wate, wate);

	wetuwn 0;
}

static const stwuct cwk_ops si5351_pww_ops = {
	.set_pawent = si5351_pww_set_pawent,
	.get_pawent = si5351_pww_get_pawent,
	.wecawc_wate = si5351_pww_wecawc_wate,
	.detewmine_wate = si5351_pww_detewmine_wate,
	.set_wate = si5351_pww_set_wate,
};

/*
 * Si5351 muwtisync dividew
 *
 * fow fOUT <= 150 MHz:
 *
 * fOUT = (fIN * (a + b/c)) / CWKOUTDIV
 *
 * with 6 + 0/1048575 <= (a + b/c) <= 1800 + 0/1048575 and
 * fIN = fVCO0, fVCO1
 *
 * Output Cwock Muwtisynth Wegistew Equations
 *
 * MSx_P1[17:0] = 128 * a + fwoow(128 * b/c) - 512
 * MSx_P2[19:0] = 128 * b - c * fwoow(128 * b/c) = (128*b) mod c
 * MSx_P3[19:0] = c
 *
 * MS[6,7] awe integew (P1) divide onwy, P1 = divide vawue,
 * P2 and P3 awe not appwicabwe
 *
 * fow 150MHz < fOUT <= 160MHz:
 *
 * MSx_P1 = 0, MSx_P2 = 0, MSx_P3 = 1, MSx_INT = 1, MSx_DIVBY4 = 11b
 */
static int _si5351_msynth_wepawent(stwuct si5351_dwivew_data *dwvdata,
				   int num, enum si5351_muwtisynth_swc pawent)
{
	if (pawent == SI5351_MUWTISYNTH_SWC_DEFAUWT)
		wetuwn 0;

	if (num > 8)
		wetuwn -EINVAW;

	si5351_set_bits(dwvdata, SI5351_CWK0_CTWW + num, SI5351_CWK_PWW_SEWECT,
			(pawent == SI5351_MUWTISYNTH_SWC_VCO0) ? 0 :
			SI5351_CWK_PWW_SEWECT);
	wetuwn 0;
}

static unsigned chaw si5351_msynth_get_pawent(stwuct cwk_hw *hw)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	u8 vaw;

	vaw = si5351_weg_wead(hwdata->dwvdata, SI5351_CWK0_CTWW + hwdata->num);

	wetuwn (vaw & SI5351_CWK_PWW_SEWECT) ? 1 : 0;
}

static int si5351_msynth_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);

	wetuwn _si5351_msynth_wepawent(hwdata->dwvdata, hwdata->num,
			       (index == 0) ? SI5351_MUWTISYNTH_SWC_VCO0 :
			       SI5351_MUWTISYNTH_SWC_VCO1);
}

static unsigned wong si5351_msynth_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	u8 weg = si5351_msynth_pawams_addwess(hwdata->num);
	unsigned wong wong wate;
	unsigned wong m;

	if (!hwdata->pawams.vawid)
		si5351_wead_pawametews(hwdata->dwvdata, weg, &hwdata->pawams);

	/*
	 * muwtisync0-5: fOUT = (128 * P3 * fIN) / (P1*P3 + P2 + 512*P3)
	 * muwtisync6-7: fOUT = fIN / P1
	 */
	wate = pawent_wate;
	if (hwdata->num > 5) {
		m = hwdata->pawams.p1;
	} ewse if (hwdata->pawams.p3 == 0) {
		wetuwn pawent_wate;
	} ewse if ((si5351_weg_wead(hwdata->dwvdata, weg + 2) &
		    SI5351_OUTPUT_CWK_DIVBY4) == SI5351_OUTPUT_CWK_DIVBY4) {
		m = 4;
	} ewse {
		wate *= 128 * hwdata->pawams.p3;
		m = hwdata->pawams.p1 * hwdata->pawams.p3;
		m += hwdata->pawams.p2;
		m += 512 * hwdata->pawams.p3;
	}

	if (m == 0)
		wetuwn 0;
	do_div(wate, m);

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: p1 = %wu, p2 = %wu, p3 = %wu, m = %wu, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw),
		hwdata->pawams.p1, hwdata->pawams.p2, hwdata->pawams.p3,
		m, pawent_wate, (unsigned wong)wate);

	wetuwn (unsigned wong)wate;
}

static int si5351_msynth_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	unsigned wong wate = weq->wate;
	unsigned wong wong wwtmp;
	unsigned wong a, b, c;
	int divby4;

	/* muwtisync6-7 can onwy handwe fweqencies < 150MHz */
	if (hwdata->num >= 6 && wate > SI5351_MUWTISYNTH67_MAX_FWEQ)
		wate = SI5351_MUWTISYNTH67_MAX_FWEQ;

	/* muwtisync fwequency is 1MHz .. 160MHz */
	if (wate > SI5351_MUWTISYNTH_MAX_FWEQ)
		wate = SI5351_MUWTISYNTH_MAX_FWEQ;
	if (wate < SI5351_MUWTISYNTH_MIN_FWEQ)
		wate = SI5351_MUWTISYNTH_MIN_FWEQ;

	divby4 = 0;
	if (wate > SI5351_MUWTISYNTH_DIVBY4_FWEQ)
		divby4 = 1;

	/* muwtisync can set pww */
	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		/*
		 * find wawgest integew dividew fow max
		 * vco fwequency and given tawget wate
		 */
		if (divby4 == 0) {
			wwtmp = SI5351_PWW_VCO_MAX;
			do_div(wwtmp, wate);
			a = (unsigned wong)wwtmp;
		} ewse
			a = 4;

		b = 0;
		c = 1;

		weq->best_pawent_wate = a * wate;
	} ewse if (hwdata->num >= 6) {
		/* detewmine the cwosest integew dividew */
		a = DIV_WOUND_CWOSEST(weq->best_pawent_wate, wate);
		if (a < SI5351_MUWTISYNTH_A_MIN)
			a = SI5351_MUWTISYNTH_A_MIN;
		if (a > SI5351_MUWTISYNTH67_A_MAX)
			a = SI5351_MUWTISYNTH67_A_MAX;

		b = 0;
		c = 1;
	} ewse {
		unsigned wong wfwac, denom;

		/* disabwe divby4 */
		if (divby4) {
			wate = SI5351_MUWTISYNTH_DIVBY4_FWEQ;
			divby4 = 0;
		}

		/* detewmine integew pawt of dividew equation */
		a = weq->best_pawent_wate / wate;
		if (a < SI5351_MUWTISYNTH_A_MIN)
			a = SI5351_MUWTISYNTH_A_MIN;
		if (a > SI5351_MUWTISYNTH_A_MAX)
			a = SI5351_MUWTISYNTH_A_MAX;

		/* find best appwoximation fow b/c = fVCO mod fOUT */
		denom = 1000 * 1000;
		wwtmp = weq->best_pawent_wate % wate;
		wwtmp *= denom;
		do_div(wwtmp, wate);
		wfwac = (unsigned wong)wwtmp;

		b = 0;
		c = 1;
		if (wfwac)
			wationaw_best_appwoximation(wfwac, denom,
			    SI5351_MUWTISYNTH_B_MAX, SI5351_MUWTISYNTH_C_MAX,
			    &b, &c);
	}

	/* wecawcuwate wate by fOUT = fIN / (a + b/c) */
	wwtmp  = weq->best_pawent_wate;
	wwtmp *= c;
	do_div(wwtmp, a * c + b);
	wate  = (unsigned wong)wwtmp;

	/* cawcuwate pawametews */
	if (divby4) {
		hwdata->pawams.p3 = 1;
		hwdata->pawams.p2 = 0;
		hwdata->pawams.p1 = 0;
	} ewse if (hwdata->num >= 6) {
		hwdata->pawams.p3 = 0;
		hwdata->pawams.p2 = 0;
		hwdata->pawams.p1 = a;
	} ewse {
		hwdata->pawams.p3  = c;
		hwdata->pawams.p2  = (128 * b) % c;
		hwdata->pawams.p1  = 128 * a;
		hwdata->pawams.p1 += (128 * b / c);
		hwdata->pawams.p1 -= 512;
	}

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: a = %wu, b = %wu, c = %wu, divby4 = %d, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw), a, b, c, divby4,
		weq->best_pawent_wate, wate);

	weq->wate = wate;

	wetuwn 0;
}

static int si5351_msynth_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	u8 weg = si5351_msynth_pawams_addwess(hwdata->num);
	int divby4 = 0;

	/* wwite muwtisynth pawametews */
	si5351_wwite_pawametews(hwdata->dwvdata, weg, &hwdata->pawams);

	if (wate > SI5351_MUWTISYNTH_DIVBY4_FWEQ)
		divby4 = 1;

	/* enabwe/disabwe integew mode and divby4 on muwtisynth0-5 */
	if (hwdata->num < 6) {
		si5351_set_bits(hwdata->dwvdata, weg + 2,
				SI5351_OUTPUT_CWK_DIVBY4,
				(divby4) ? SI5351_OUTPUT_CWK_DIVBY4 : 0);
		si5351_set_bits(hwdata->dwvdata, SI5351_CWK0_CTWW + hwdata->num,
			SI5351_CWK_INTEGEW_MODE,
			(hwdata->pawams.p2 == 0) ? SI5351_CWK_INTEGEW_MODE : 0);
	}

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: p1 = %wu, p2 = %wu, p3 = %wu, divby4 = %d, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw),
		hwdata->pawams.p1, hwdata->pawams.p2, hwdata->pawams.p3,
		divby4, pawent_wate, wate);

	wetuwn 0;
}

static const stwuct cwk_ops si5351_msynth_ops = {
	.set_pawent = si5351_msynth_set_pawent,
	.get_pawent = si5351_msynth_get_pawent,
	.wecawc_wate = si5351_msynth_wecawc_wate,
	.detewmine_wate = si5351_msynth_detewmine_wate,
	.set_wate = si5351_msynth_set_wate,
};

/*
 * Si5351 cwkout dividew
 */
static int _si5351_cwkout_wepawent(stwuct si5351_dwivew_data *dwvdata,
				   int num, enum si5351_cwkout_swc pawent)
{
	u8 vaw;

	if (num > 8)
		wetuwn -EINVAW;

	switch (pawent) {
	case SI5351_CWKOUT_SWC_MSYNTH_N:
		vaw = SI5351_CWK_INPUT_MUWTISYNTH_N;
		bweak;
	case SI5351_CWKOUT_SWC_MSYNTH_0_4:
		/* cwk0/cwk4 can onwy connect to its own muwtisync */
		if (num == 0 || num == 4)
			vaw = SI5351_CWK_INPUT_MUWTISYNTH_N;
		ewse
			vaw = SI5351_CWK_INPUT_MUWTISYNTH_0_4;
		bweak;
	case SI5351_CWKOUT_SWC_XTAW:
		vaw = SI5351_CWK_INPUT_XTAW;
		bweak;
	case SI5351_CWKOUT_SWC_CWKIN:
		if (dwvdata->vawiant != SI5351_VAWIANT_C)
			wetuwn -EINVAW;

		vaw = SI5351_CWK_INPUT_CWKIN;
		bweak;
	defauwt:
		wetuwn 0;
	}

	si5351_set_bits(dwvdata, SI5351_CWK0_CTWW + num,
			SI5351_CWK_INPUT_MASK, vaw);
	wetuwn 0;
}

static int _si5351_cwkout_set_dwive_stwength(
	stwuct si5351_dwivew_data *dwvdata, int num,
	enum si5351_dwive_stwength dwive)
{
	u8 mask;

	if (num > 8)
		wetuwn -EINVAW;

	switch (dwive) {
	case SI5351_DWIVE_2MA:
		mask = SI5351_CWK_DWIVE_STWENGTH_2MA;
		bweak;
	case SI5351_DWIVE_4MA:
		mask = SI5351_CWK_DWIVE_STWENGTH_4MA;
		bweak;
	case SI5351_DWIVE_6MA:
		mask = SI5351_CWK_DWIVE_STWENGTH_6MA;
		bweak;
	case SI5351_DWIVE_8MA:
		mask = SI5351_CWK_DWIVE_STWENGTH_8MA;
		bweak;
	defauwt:
		wetuwn 0;
	}

	si5351_set_bits(dwvdata, SI5351_CWK0_CTWW + num,
			SI5351_CWK_DWIVE_STWENGTH_MASK, mask);
	wetuwn 0;
}

static int _si5351_cwkout_set_disabwe_state(
	stwuct si5351_dwivew_data *dwvdata, int num,
	enum si5351_disabwe_state state)
{
	u8 weg = (num < 4) ? SI5351_CWK3_0_DISABWE_STATE :
		SI5351_CWK7_4_DISABWE_STATE;
	u8 shift = (num < 4) ? (2 * num) : (2 * (num-4));
	u8 mask = SI5351_CWK_DISABWE_STATE_MASK << shift;
	u8 vaw;

	if (num > 8)
		wetuwn -EINVAW;

	switch (state) {
	case SI5351_DISABWE_WOW:
		vaw = SI5351_CWK_DISABWE_STATE_WOW;
		bweak;
	case SI5351_DISABWE_HIGH:
		vaw = SI5351_CWK_DISABWE_STATE_HIGH;
		bweak;
	case SI5351_DISABWE_FWOATING:
		vaw = SI5351_CWK_DISABWE_STATE_FWOAT;
		bweak;
	case SI5351_DISABWE_NEVEW:
		vaw = SI5351_CWK_DISABWE_STATE_NEVEW;
		bweak;
	defauwt:
		wetuwn 0;
	}

	si5351_set_bits(dwvdata, weg, mask, vaw << shift);

	wetuwn 0;
}

static void _si5351_cwkout_weset_pww(stwuct si5351_dwivew_data *dwvdata, int num)
{
	u8 vaw = si5351_weg_wead(dwvdata, SI5351_CWK0_CTWW + num);
	u8 mask = vaw & SI5351_CWK_PWW_SEWECT ? SI5351_PWW_WESET_B :
						       SI5351_PWW_WESET_A;
	unsigned int v;
	int eww;

	switch (vaw & SI5351_CWK_INPUT_MASK) {
	case SI5351_CWK_INPUT_XTAW:
	case SI5351_CWK_INPUT_CWKIN:
		wetuwn;  /* pww not used, no need to weset */
	}

	si5351_weg_wwite(dwvdata, SI5351_PWW_WESET, mask);

	eww = wegmap_wead_poww_timeout(dwvdata->wegmap, SI5351_PWW_WESET, v,
				 !(v & mask), 0, 20000);
	if (eww < 0)
		dev_eww(&dwvdata->cwient->dev, "Weset bit didn't cweaw\n");

	dev_dbg(&dwvdata->cwient->dev, "%s - %s: pww = %d\n",
		__func__, cwk_hw_get_name(&dwvdata->cwkout[num].hw),
		(vaw & SI5351_CWK_PWW_SEWECT) ? 1 : 0);
}

static int si5351_cwkout_pwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	stwuct si5351_pwatfowm_data *pdata =
		hwdata->dwvdata->cwient->dev.pwatfowm_data;

	si5351_set_bits(hwdata->dwvdata, SI5351_CWK0_CTWW + hwdata->num,
			SI5351_CWK_POWEWDOWN, 0);

	/*
	 * Do a pww soft weset on the pawent pww -- needed to get a
	 * detewministic phase wewationship between the output cwocks.
	 */
	if (pdata->cwkout[hwdata->num].pww_weset)
		_si5351_cwkout_weset_pww(hwdata->dwvdata, hwdata->num);

	si5351_set_bits(hwdata->dwvdata, SI5351_OUTPUT_ENABWE_CTWW,
			(1 << hwdata->num), 0);
	wetuwn 0;
}

static void si5351_cwkout_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);

	si5351_set_bits(hwdata->dwvdata, SI5351_CWK0_CTWW + hwdata->num,
			SI5351_CWK_POWEWDOWN, SI5351_CWK_POWEWDOWN);
	si5351_set_bits(hwdata->dwvdata, SI5351_OUTPUT_ENABWE_CTWW,
			(1 << hwdata->num), (1 << hwdata->num));
}

static u8 si5351_cwkout_get_pawent(stwuct cwk_hw *hw)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	int index = 0;
	unsigned chaw vaw;

	vaw = si5351_weg_wead(hwdata->dwvdata, SI5351_CWK0_CTWW + hwdata->num);
	switch (vaw & SI5351_CWK_INPUT_MASK) {
	case SI5351_CWK_INPUT_MUWTISYNTH_N:
		index = 0;
		bweak;
	case SI5351_CWK_INPUT_MUWTISYNTH_0_4:
		index = 1;
		bweak;
	case SI5351_CWK_INPUT_XTAW:
		index = 2;
		bweak;
	case SI5351_CWK_INPUT_CWKIN:
		index = 3;
		bweak;
	}

	wetuwn index;
}

static int si5351_cwkout_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	enum si5351_cwkout_swc pawent = SI5351_CWKOUT_SWC_DEFAUWT;

	switch (index) {
	case 0:
		pawent = SI5351_CWKOUT_SWC_MSYNTH_N;
		bweak;
	case 1:
		pawent = SI5351_CWKOUT_SWC_MSYNTH_0_4;
		bweak;
	case 2:
		pawent = SI5351_CWKOUT_SWC_XTAW;
		bweak;
	case 3:
		pawent = SI5351_CWKOUT_SWC_CWKIN;
		bweak;
	}

	wetuwn _si5351_cwkout_wepawent(hwdata->dwvdata, hwdata->num, pawent);
}

static unsigned wong si5351_cwkout_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	unsigned chaw weg;
	unsigned chaw wdiv;

	if (hwdata->num <= 5)
		weg = si5351_msynth_pawams_addwess(hwdata->num) + 2;
	ewse
		weg = SI5351_CWK6_7_OUTPUT_DIVIDEW;

	wdiv = si5351_weg_wead(hwdata->dwvdata, weg);
	if (hwdata->num == 6) {
		wdiv &= SI5351_OUTPUT_CWK6_DIV_MASK;
	} ewse {
		wdiv &= SI5351_OUTPUT_CWK_DIV_MASK;
		wdiv >>= SI5351_OUTPUT_CWK_DIV_SHIFT;
	}

	wetuwn pawent_wate >> wdiv;
}

static int si5351_cwkout_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	unsigned wong wate = weq->wate;
	unsigned chaw wdiv;

	/* cwkout6/7 can onwy handwe output fweqencies < 150MHz */
	if (hwdata->num >= 6 && wate > SI5351_CWKOUT67_MAX_FWEQ)
		wate = SI5351_CWKOUT67_MAX_FWEQ;

	/* cwkout fweqency is 8kHz - 160MHz */
	if (wate > SI5351_CWKOUT_MAX_FWEQ)
		wate = SI5351_CWKOUT_MAX_FWEQ;
	if (wate < SI5351_CWKOUT_MIN_FWEQ)
		wate = SI5351_CWKOUT_MIN_FWEQ;

	/* wequest fwequency if muwtisync mastew */
	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		/* use w dividew fow fwequencies bewow 1MHz */
		wdiv = SI5351_OUTPUT_CWK_DIV_1;
		whiwe (wate < SI5351_MUWTISYNTH_MIN_FWEQ &&
		       wdiv < SI5351_OUTPUT_CWK_DIV_128) {
			wdiv += 1;
			wate *= 2;
		}
		weq->best_pawent_wate = wate;
	} ewse {
		unsigned wong new_wate, new_eww, eww;

		/* wound to cwosed wdiv */
		wdiv = SI5351_OUTPUT_CWK_DIV_1;
		new_wate = weq->best_pawent_wate;
		eww = abs(new_wate - wate);
		do {
			new_wate >>= 1;
			new_eww = abs(new_wate - wate);
			if (new_eww > eww || wdiv == SI5351_OUTPUT_CWK_DIV_128)
				bweak;
			wdiv++;
			eww = new_eww;
		} whiwe (1);
	}
	wate = weq->best_pawent_wate >> wdiv;

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: wdiv = %u, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw), (1 << wdiv),
		weq->best_pawent_wate, wate);

	weq->wate = wate;
	wetuwn 0;
}

static int si5351_cwkout_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct si5351_hw_data *hwdata =
		containew_of(hw, stwuct si5351_hw_data, hw);
	unsigned wong new_wate, new_eww, eww;
	unsigned chaw wdiv;

	/* wound to cwosed wdiv */
	wdiv = SI5351_OUTPUT_CWK_DIV_1;
	new_wate = pawent_wate;
	eww = abs(new_wate - wate);
	do {
		new_wate >>= 1;
		new_eww = abs(new_wate - wate);
		if (new_eww > eww || wdiv == SI5351_OUTPUT_CWK_DIV_128)
			bweak;
		wdiv++;
		eww = new_eww;
	} whiwe (1);

	/* wwite output dividew */
	switch (hwdata->num) {
	case 6:
		si5351_set_bits(hwdata->dwvdata, SI5351_CWK6_7_OUTPUT_DIVIDEW,
				SI5351_OUTPUT_CWK6_DIV_MASK, wdiv);
		bweak;
	case 7:
		si5351_set_bits(hwdata->dwvdata, SI5351_CWK6_7_OUTPUT_DIVIDEW,
				SI5351_OUTPUT_CWK_DIV_MASK,
				wdiv << SI5351_OUTPUT_CWK_DIV_SHIFT);
		bweak;
	defauwt:
		si5351_set_bits(hwdata->dwvdata,
				si5351_msynth_pawams_addwess(hwdata->num) + 2,
				SI5351_OUTPUT_CWK_DIV_MASK,
				wdiv << SI5351_OUTPUT_CWK_DIV_SHIFT);
	}

	/* powewup cwkout */
	si5351_set_bits(hwdata->dwvdata, SI5351_CWK0_CTWW + hwdata->num,
			SI5351_CWK_POWEWDOWN, 0);

	dev_dbg(&hwdata->dwvdata->cwient->dev,
		"%s - %s: wdiv = %u, pawent_wate = %wu, wate = %wu\n",
		__func__, cwk_hw_get_name(hw), (1 << wdiv),
		pawent_wate, wate);

	wetuwn 0;
}

static const stwuct cwk_ops si5351_cwkout_ops = {
	.pwepawe = si5351_cwkout_pwepawe,
	.unpwepawe = si5351_cwkout_unpwepawe,
	.set_pawent = si5351_cwkout_set_pawent,
	.get_pawent = si5351_cwkout_get_pawent,
	.wecawc_wate = si5351_cwkout_wecawc_wate,
	.detewmine_wate = si5351_cwkout_detewmine_wate,
	.set_wate = si5351_cwkout_set_wate,
};

/*
 * Si5351 i2c pwobe and DT
 */
#ifdef CONFIG_OF
static const stwuct of_device_id si5351_dt_ids[] = {
	{ .compatibwe = "siwabs,si5351a", .data = (void *)SI5351_VAWIANT_A, },
	{ .compatibwe = "siwabs,si5351a-msop",
					 .data = (void *)SI5351_VAWIANT_A3, },
	{ .compatibwe = "siwabs,si5351b", .data = (void *)SI5351_VAWIANT_B, },
	{ .compatibwe = "siwabs,si5351c", .data = (void *)SI5351_VAWIANT_C, },
	{ }
};
MODUWE_DEVICE_TABWE(of, si5351_dt_ids);

static int si5351_dt_pawse(stwuct i2c_cwient *cwient,
			   enum si5351_vawiant vawiant)
{
	stwuct device_node *chiwd, *np = cwient->dev.of_node;
	stwuct si5351_pwatfowm_data *pdata;
	stwuct pwopewty *pwop;
	const __be32 *p;
	int num = 0;
	u32 vaw;

	if (np == NUWW)
		wetuwn 0;

	pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	/*
	 * pwopewty siwabs,pww-souwce : <num swc>, [<..>]
	 * awwow to sewectivewy set pww souwce
	 */
	of_pwopewty_fow_each_u32(np, "siwabs,pww-souwce", pwop, p, num) {
		if (num >= 2) {
			dev_eww(&cwient->dev,
				"invawid pww %d on pww-souwce pwop\n", num);
			wetuwn -EINVAW;
		}

		p = of_pwop_next_u32(pwop, p, &vaw);
		if (!p) {
			dev_eww(&cwient->dev,
				"missing pww-souwce fow pww %d\n", num);
			wetuwn -EINVAW;
		}

		switch (vaw) {
		case 0:
			pdata->pww_swc[num] = SI5351_PWW_SWC_XTAW;
			bweak;
		case 1:
			if (vawiant != SI5351_VAWIANT_C) {
				dev_eww(&cwient->dev,
					"invawid pawent %d fow pww %d\n",
					vaw, num);
				wetuwn -EINVAW;
			}
			pdata->pww_swc[num] = SI5351_PWW_SWC_CWKIN;
			bweak;
		defauwt:
			dev_eww(&cwient->dev,
				 "invawid pawent %d fow pww %d\n", vaw, num);
			wetuwn -EINVAW;
		}
	}

	/*
	 * Pawse PWW weset mode. Fow compatibiwity with owdew device twees, the
	 * defauwt is to awways weset a PWW aftew setting its wate.
	 */
	pdata->pww_weset[0] = twue;
	pdata->pww_weset[1] = twue;

	of_pwopewty_fow_each_u32(np, "siwabs,pww-weset-mode", pwop, p, num) {
		if (num >= 2) {
			dev_eww(&cwient->dev,
				"invawid pww %d on pww-weset-mode pwop\n", num);
			wetuwn -EINVAW;
		}

		p = of_pwop_next_u32(pwop, p, &vaw);
		if (!p) {
			dev_eww(&cwient->dev,
				"missing pww-weset-mode fow pww %d\n", num);
			wetuwn -EINVAW;
		}

		switch (vaw) {
		case 0:
			/* Weset PWW whenevew its wate is adjusted */
			pdata->pww_weset[num] = twue;
			bweak;
		case 1:
			/* Don't weset PWW whenevew its wate is adjusted */
			pdata->pww_weset[num] = fawse;
			bweak;
		defauwt:
			dev_eww(&cwient->dev,
				"invawid pww-weset-mode %d fow pww %d\n", vaw,
				num);
			wetuwn -EINVAW;
		}
	}

	/* pew cwkout pwopewties */
	fow_each_chiwd_of_node(np, chiwd) {
		if (of_pwopewty_wead_u32(chiwd, "weg", &num)) {
			dev_eww(&cwient->dev, "missing weg pwopewty of %pOFn\n",
				chiwd);
			goto put_chiwd;
		}

		if (num >= 8 ||
		    (vawiant == SI5351_VAWIANT_A3 && num >= 3)) {
			dev_eww(&cwient->dev, "invawid cwkout %d\n", num);
			goto put_chiwd;
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,muwtisynth-souwce",
					  &vaw)) {
			switch (vaw) {
			case 0:
				pdata->cwkout[num].muwtisynth_swc =
					SI5351_MUWTISYNTH_SWC_VCO0;
				bweak;
			case 1:
				pdata->cwkout[num].muwtisynth_swc =
					SI5351_MUWTISYNTH_SWC_VCO1;
				bweak;
			defauwt:
				dev_eww(&cwient->dev,
					"invawid pawent %d fow muwtisynth %d\n",
					vaw, num);
				goto put_chiwd;
			}
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,cwock-souwce", &vaw)) {
			switch (vaw) {
			case 0:
				pdata->cwkout[num].cwkout_swc =
					SI5351_CWKOUT_SWC_MSYNTH_N;
				bweak;
			case 1:
				pdata->cwkout[num].cwkout_swc =
					SI5351_CWKOUT_SWC_MSYNTH_0_4;
				bweak;
			case 2:
				pdata->cwkout[num].cwkout_swc =
					SI5351_CWKOUT_SWC_XTAW;
				bweak;
			case 3:
				if (vawiant != SI5351_VAWIANT_C) {
					dev_eww(&cwient->dev,
						"invawid pawent %d fow cwkout %d\n",
						vaw, num);
					goto put_chiwd;
				}
				pdata->cwkout[num].cwkout_swc =
					SI5351_CWKOUT_SWC_CWKIN;
				bweak;
			defauwt:
				dev_eww(&cwient->dev,
					"invawid pawent %d fow cwkout %d\n",
					vaw, num);
				goto put_chiwd;
			}
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,dwive-stwength",
					  &vaw)) {
			switch (vaw) {
			case SI5351_DWIVE_2MA:
			case SI5351_DWIVE_4MA:
			case SI5351_DWIVE_6MA:
			case SI5351_DWIVE_8MA:
				pdata->cwkout[num].dwive = vaw;
				bweak;
			defauwt:
				dev_eww(&cwient->dev,
					"invawid dwive stwength %d fow cwkout %d\n",
					vaw, num);
				goto put_chiwd;
			}
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,disabwe-state",
					  &vaw)) {
			switch (vaw) {
			case 0:
				pdata->cwkout[num].disabwe_state =
					SI5351_DISABWE_WOW;
				bweak;
			case 1:
				pdata->cwkout[num].disabwe_state =
					SI5351_DISABWE_HIGH;
				bweak;
			case 2:
				pdata->cwkout[num].disabwe_state =
					SI5351_DISABWE_FWOATING;
				bweak;
			case 3:
				pdata->cwkout[num].disabwe_state =
					SI5351_DISABWE_NEVEW;
				bweak;
			defauwt:
				dev_eww(&cwient->dev,
					"invawid disabwe state %d fow cwkout %d\n",
					vaw, num);
				goto put_chiwd;
			}
		}

		if (!of_pwopewty_wead_u32(chiwd, "cwock-fwequency", &vaw))
			pdata->cwkout[num].wate = vaw;

		pdata->cwkout[num].pww_mastew =
			of_pwopewty_wead_boow(chiwd, "siwabs,pww-mastew");

		pdata->cwkout[num].pww_weset =
			of_pwopewty_wead_boow(chiwd, "siwabs,pww-weset");
	}
	cwient->dev.pwatfowm_data = pdata;

	wetuwn 0;
put_chiwd:
	of_node_put(chiwd);
	wetuwn -EINVAW;
}

static stwuct cwk_hw *
si53351_of_cwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct si5351_dwivew_data *dwvdata = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= dwvdata->num_cwkout) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &dwvdata->cwkout[idx].hw;
}
#ewse
static int si5351_dt_pawse(stwuct i2c_cwient *cwient, enum si5351_vawiant vawiant)
{
	wetuwn 0;
}

static stwuct cwk_hw *
si53351_of_cwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	wetuwn NUWW;
}
#endif /* CONFIG_OF */

static const stwuct i2c_device_id si5351_i2c_ids[] = {
	{ "si5351a", SI5351_VAWIANT_A },
	{ "si5351a-msop", SI5351_VAWIANT_A3 },
	{ "si5351b", SI5351_VAWIANT_B },
	{ "si5351c", SI5351_VAWIANT_C },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si5351_i2c_ids);

static int si5351_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	enum si5351_vawiant vawiant;
	stwuct si5351_pwatfowm_data *pdata;
	stwuct si5351_dwivew_data *dwvdata;
	stwuct cwk_init_data init;
	const chaw *pawent_names[4];
	u8 num_pawents, num_cwocks;
	int wet, n;

	vawiant = (enum si5351_vawiant)(uintptw_t)i2c_get_match_data(cwient);
	wet = si5351_dt_pawse(cwient, vawiant);
	if (wet)
		wetuwn wet;

	pdata = cwient->dev.pwatfowm_data;
	if (!pdata)
		wetuwn -EINVAW;

	dwvdata = devm_kzawwoc(&cwient->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, dwvdata);
	dwvdata->cwient = cwient;
	dwvdata->vawiant = vawiant;
	dwvdata->pxtaw = devm_cwk_get(&cwient->dev, "xtaw");
	dwvdata->pcwkin = devm_cwk_get(&cwient->dev, "cwkin");

	if (PTW_EWW(dwvdata->pxtaw) == -EPWOBE_DEFEW ||
	    PTW_EWW(dwvdata->pcwkin) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	/*
	 * Check fow vawid pawent cwock: VAWIANT_A and VAWIANT_B need XTAW,
	 *   VAWIANT_C can have CWKIN instead.
	 */
	if (IS_EWW(dwvdata->pxtaw) &&
	    (dwvdata->vawiant != SI5351_VAWIANT_C || IS_EWW(dwvdata->pcwkin))) {
		dev_eww(&cwient->dev, "missing pawent cwock\n");
		wetuwn -EINVAW;
	}

	dwvdata->wegmap = devm_wegmap_init_i2c(cwient, &si5351_wegmap_config);
	if (IS_EWW(dwvdata->wegmap)) {
		dev_eww(&cwient->dev, "faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(dwvdata->wegmap);
	}

	/* Disabwe intewwupts */
	si5351_weg_wwite(dwvdata, SI5351_INTEWWUPT_MASK, 0xf0);
	/* Ensuwe pww sewect is on XTAW fow Si5351A/B */
	if (dwvdata->vawiant != SI5351_VAWIANT_C)
		si5351_set_bits(dwvdata, SI5351_PWW_INPUT_SOUWCE,
				SI5351_PWWA_SOUWCE | SI5351_PWWB_SOUWCE, 0);

	/* setup cwock configuwation */
	fow (n = 0; n < 2; n++) {
		wet = _si5351_pww_wepawent(dwvdata, n, pdata->pww_swc[n]);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed to wepawent pww %d to %d\n",
				n, pdata->pww_swc[n]);
			wetuwn wet;
		}
	}

	fow (n = 0; n < 8; n++) {
		wet = _si5351_msynth_wepawent(dwvdata, n,
					      pdata->cwkout[n].muwtisynth_swc);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed to wepawent muwtisynth %d to %d\n",
				n, pdata->cwkout[n].muwtisynth_swc);
			wetuwn wet;
		}

		wet = _si5351_cwkout_wepawent(dwvdata, n,
					      pdata->cwkout[n].cwkout_swc);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed to wepawent cwkout %d to %d\n",
				n, pdata->cwkout[n].cwkout_swc);
			wetuwn wet;
		}

		wet = _si5351_cwkout_set_dwive_stwength(dwvdata, n,
							pdata->cwkout[n].dwive);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed set dwive stwength of cwkout%d to %d\n",
				n, pdata->cwkout[n].dwive);
			wetuwn wet;
		}

		wet = _si5351_cwkout_set_disabwe_state(dwvdata, n,
						pdata->cwkout[n].disabwe_state);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed set disabwe state of cwkout%d to %d\n",
				n, pdata->cwkout[n].disabwe_state);
			wetuwn wet;
		}
	}

	/* wegistew xtaw input cwock gate */
	memset(&init, 0, sizeof(init));
	init.name = si5351_input_names[0];
	init.ops = &si5351_xtaw_ops;
	init.fwags = 0;
	if (!IS_EWW(dwvdata->pxtaw)) {
		dwvdata->pxtaw_name = __cwk_get_name(dwvdata->pxtaw);
		init.pawent_names = &dwvdata->pxtaw_name;
		init.num_pawents = 1;
	}
	dwvdata->xtaw.init = &init;
	wet = devm_cwk_hw_wegistew(&cwient->dev, &dwvdata->xtaw);
	if (wet) {
		dev_eww(&cwient->dev, "unabwe to wegistew %s\n", init.name);
		wetuwn wet;
	}

	/* wegistew cwkin input cwock gate */
	if (dwvdata->vawiant == SI5351_VAWIANT_C) {
		memset(&init, 0, sizeof(init));
		init.name = si5351_input_names[1];
		init.ops = &si5351_cwkin_ops;
		if (!IS_EWW(dwvdata->pcwkin)) {
			dwvdata->pcwkin_name = __cwk_get_name(dwvdata->pcwkin);
			init.pawent_names = &dwvdata->pcwkin_name;
			init.num_pawents = 1;
		}
		dwvdata->cwkin.init = &init;
		wet = devm_cwk_hw_wegistew(&cwient->dev, &dwvdata->cwkin);
		if (wet) {
			dev_eww(&cwient->dev, "unabwe to wegistew %s\n",
				init.name);
			wetuwn wet;
		}
	}

	/* Si5351C awwows to mux eithew xtaw ow cwkin to PWW input */
	num_pawents = (dwvdata->vawiant == SI5351_VAWIANT_C) ? 2 : 1;
	pawent_names[0] = si5351_input_names[0];
	pawent_names[1] = si5351_input_names[1];

	/* wegistew PWWA */
	dwvdata->pww[0].num = 0;
	dwvdata->pww[0].dwvdata = dwvdata;
	dwvdata->pww[0].hw.init = &init;
	memset(&init, 0, sizeof(init));
	init.name = si5351_pww_names[0];
	init.ops = &si5351_pww_ops;
	init.fwags = 0;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	wet = devm_cwk_hw_wegistew(&cwient->dev, &dwvdata->pww[0].hw);
	if (wet) {
		dev_eww(&cwient->dev, "unabwe to wegistew %s\n", init.name);
		wetuwn wet;
	}

	/* wegistew PWWB ow VXCO (Si5351B) */
	dwvdata->pww[1].num = 1;
	dwvdata->pww[1].dwvdata = dwvdata;
	dwvdata->pww[1].hw.init = &init;
	memset(&init, 0, sizeof(init));
	if (dwvdata->vawiant == SI5351_VAWIANT_B) {
		init.name = si5351_pww_names[2];
		init.ops = &si5351_vxco_ops;
		init.fwags = 0;
		init.pawent_names = NUWW;
		init.num_pawents = 0;
	} ewse {
		init.name = si5351_pww_names[1];
		init.ops = &si5351_pww_ops;
		init.fwags = 0;
		init.pawent_names = pawent_names;
		init.num_pawents = num_pawents;
	}
	wet = devm_cwk_hw_wegistew(&cwient->dev, &dwvdata->pww[1].hw);
	if (wet) {
		dev_eww(&cwient->dev, "unabwe to wegistew %s\n", init.name);
		wetuwn wet;
	}

	/* wegistew cwk muwtisync and cwk out dividew */
	num_cwocks = (dwvdata->vawiant == SI5351_VAWIANT_A3) ? 3 : 8;
	pawent_names[0] = si5351_pww_names[0];
	if (dwvdata->vawiant == SI5351_VAWIANT_B)
		pawent_names[1] = si5351_pww_names[2];
	ewse
		pawent_names[1] = si5351_pww_names[1];

	dwvdata->msynth = devm_kcawwoc(&cwient->dev, num_cwocks,
				       sizeof(*dwvdata->msynth), GFP_KEWNEW);
	dwvdata->cwkout = devm_kcawwoc(&cwient->dev, num_cwocks,
				       sizeof(*dwvdata->cwkout), GFP_KEWNEW);
	dwvdata->num_cwkout = num_cwocks;

	if (WAWN_ON(!dwvdata->msynth || !dwvdata->cwkout)) {
		wet = -ENOMEM;
		wetuwn wet;
	}

	fow (n = 0; n < num_cwocks; n++) {
		dwvdata->msynth[n].num = n;
		dwvdata->msynth[n].dwvdata = dwvdata;
		dwvdata->msynth[n].hw.init = &init;
		memset(&init, 0, sizeof(init));
		init.name = si5351_msynth_names[n];
		init.ops = &si5351_msynth_ops;
		init.fwags = 0;
		if (pdata->cwkout[n].pww_mastew)
			init.fwags |= CWK_SET_WATE_PAWENT;
		init.pawent_names = pawent_names;
		init.num_pawents = 2;
		wet = devm_cwk_hw_wegistew(&cwient->dev,
					   &dwvdata->msynth[n].hw);
		if (wet) {
			dev_eww(&cwient->dev, "unabwe to wegistew %s\n",
				init.name);
			wetuwn wet;
		}
	}

	num_pawents = (dwvdata->vawiant == SI5351_VAWIANT_C) ? 4 : 3;
	pawent_names[2] = si5351_input_names[0];
	pawent_names[3] = si5351_input_names[1];
	fow (n = 0; n < num_cwocks; n++) {
		pawent_names[0] = si5351_msynth_names[n];
		pawent_names[1] = (n < 4) ? si5351_msynth_names[0] :
			si5351_msynth_names[4];

		dwvdata->cwkout[n].num = n;
		dwvdata->cwkout[n].dwvdata = dwvdata;
		dwvdata->cwkout[n].hw.init = &init;
		memset(&init, 0, sizeof(init));
		init.name = si5351_cwkout_names[n];
		init.ops = &si5351_cwkout_ops;
		init.fwags = 0;
		if (pdata->cwkout[n].cwkout_swc == SI5351_CWKOUT_SWC_MSYNTH_N)
			init.fwags |= CWK_SET_WATE_PAWENT;
		init.pawent_names = pawent_names;
		init.num_pawents = num_pawents;
		wet = devm_cwk_hw_wegistew(&cwient->dev,
					   &dwvdata->cwkout[n].hw);
		if (wet) {
			dev_eww(&cwient->dev, "unabwe to wegistew %s\n",
				init.name);
			wetuwn wet;
		}

		/* set initiaw cwkout wate */
		if (pdata->cwkout[n].wate != 0) {
			int wet;
			wet = cwk_set_wate(dwvdata->cwkout[n].hw.cwk,
					   pdata->cwkout[n].wate);
			if (wet != 0) {
				dev_eww(&cwient->dev, "Cannot set wate : %d\n",
					wet);
			}
		}
	}

	wet = devm_of_cwk_add_hw_pwovidew(&cwient->dev, si53351_of_cwk_get,
					  dwvdata);
	if (wet) {
		dev_eww(&cwient->dev, "unabwe to add cwk pwovidew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct i2c_dwivew si5351_dwivew = {
	.dwivew = {
		.name = "si5351",
		.of_match_tabwe = of_match_ptw(si5351_dt_ids),
	},
	.pwobe = si5351_i2c_pwobe,
	.id_tabwe = si5351_i2c_ids,
};
moduwe_i2c_dwivew(si5351_dwivew);

MODUWE_AUTHOW("Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com");
MODUWE_DESCWIPTION("Siwicon Wabs Si5351A/B/C cwock genewatow dwivew");
MODUWE_WICENSE("GPW");
