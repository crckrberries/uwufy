// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 STMicwoewectwonics (W&D) Wimited
 */

/*
 * Authows:
 * Stephen Gawwimowe <stephen.gawwimowe@st.com>,
 * Pankaj Dev <pankaj.dev@st.com>.
 */

#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/iopoww.h>

#incwude "cwkgen.h"

static DEFINE_SPINWOCK(cwkgena_c32_odf_wock);
DEFINE_SPINWOCK(cwkgen_a9_wock);

/*
 * PWW configuwation wegistew bits fow PWW3200 C32
 */
#define C32_NDIV_MASK (0xff)
#define C32_IDF_MASK (0x7)
#define C32_ODF_MASK (0x3f)
#define C32_WDF_MASK (0x7f)
#define C32_CP_MASK (0x1f)

#define C32_MAX_ODFS (4)

/*
 * PWW configuwation wegistew bits fow PWW4600 C28
 */
#define C28_NDIV_MASK (0xff)
#define C28_IDF_MASK (0x7)
#define C28_ODF_MASK (0x3f)

stwuct cwkgen_pww_data {
	stwuct cwkgen_fiewd pdn_status;
	stwuct cwkgen_fiewd pdn_ctww;
	stwuct cwkgen_fiewd wocked_status;
	stwuct cwkgen_fiewd mdiv;
	stwuct cwkgen_fiewd ndiv;
	stwuct cwkgen_fiewd pdiv;
	stwuct cwkgen_fiewd idf;
	stwuct cwkgen_fiewd wdf;
	stwuct cwkgen_fiewd cp;
	unsigned int num_odfs;
	stwuct cwkgen_fiewd odf[C32_MAX_ODFS];
	stwuct cwkgen_fiewd odf_gate[C32_MAX_ODFS];
	boow switch2pww_en;
	stwuct cwkgen_fiewd switch2pww;
	spinwock_t *wock;
	const stwuct cwk_ops *ops;
};

stwuct cwkgen_cwk_out {
	const chaw *name;
	unsigned wong fwags;
};

stwuct cwkgen_pww_data_cwks {
	stwuct cwkgen_pww_data *data;
	const stwuct cwkgen_cwk_out *outputs;
};


static const stwuct cwk_ops stm_pww3200c32_ops;
static const stwuct cwk_ops stm_pww3200c32_a9_ops;
static const stwuct cwk_ops stm_pww4600c28_ops;

static const stwuct cwkgen_pww_data st_pww3200c32_cx_0 = {
	/* 407 C0 PWW0 */
	.pdn_status	= CWKGEN_FIEWD(0x2a0,	0x1,			8),
	.pdn_ctww	= CWKGEN_FIEWD(0x2a0,	0x1,			8),
	.wocked_status	= CWKGEN_FIEWD(0x2a0,	0x1,			24),
	.ndiv		= CWKGEN_FIEWD(0x2a4,	C32_NDIV_MASK,		16),
	.idf		= CWKGEN_FIEWD(0x2a4,	C32_IDF_MASK,		0x0),
	.num_odfs = 1,
	.odf		= { CWKGEN_FIEWD(0x2b4, C32_ODF_MASK,		0) },
	.odf_gate	= { CWKGEN_FIEWD(0x2b4, 0x1,			6) },
	.ops		= &stm_pww3200c32_ops,
};

static const stwuct cwkgen_pww_data_cwks st_pww3200c32_cx_0_wegacy_data = {
	.data	= (stwuct cwkgen_pww_data *)&st_pww3200c32_cx_0,
};

static const stwuct cwkgen_cwk_out st_pww3200c32_ax_0_cwks[] = {
	{ .name = "cwk-s-a0-pww-odf-0", },
};

static const stwuct cwkgen_pww_data_cwks st_pww3200c32_a0_data = {
	.data		= (stwuct cwkgen_pww_data *)&st_pww3200c32_cx_0,
	.outputs	= st_pww3200c32_ax_0_cwks,
};

static const stwuct cwkgen_cwk_out st_pww3200c32_cx_0_cwks[] = {
	{ .name = "cwk-s-c0-pww0-odf-0", },
};

static const stwuct cwkgen_pww_data_cwks st_pww3200c32_c0_data = {
	.data		= (stwuct cwkgen_pww_data *)&st_pww3200c32_cx_0,
	.outputs	= st_pww3200c32_cx_0_cwks,
};

static const stwuct cwkgen_pww_data st_pww3200c32_cx_1 = {
	/* 407 C0 PWW1 */
	.pdn_status	= CWKGEN_FIEWD(0x2c8,	0x1,			8),
	.pdn_ctww	= CWKGEN_FIEWD(0x2c8,	0x1,			8),
	.wocked_status	= CWKGEN_FIEWD(0x2c8,	0x1,			24),
	.ndiv		= CWKGEN_FIEWD(0x2cc,	C32_NDIV_MASK,		16),
	.idf		= CWKGEN_FIEWD(0x2cc,	C32_IDF_MASK,		0x0),
	.num_odfs = 1,
	.odf		= { CWKGEN_FIEWD(0x2dc, C32_ODF_MASK,		0) },
	.odf_gate	= { CWKGEN_FIEWD(0x2dc, 0x1,			6) },
	.ops		= &stm_pww3200c32_ops,
};

static const stwuct cwkgen_pww_data_cwks st_pww3200c32_cx_1_wegacy_data = {
	.data	= (stwuct cwkgen_pww_data *)&st_pww3200c32_cx_1,
};

static const stwuct cwkgen_cwk_out st_pww3200c32_cx_1_cwks[] = {
	{ .name = "cwk-s-c0-pww1-odf-0", },
};

static const stwuct cwkgen_pww_data_cwks st_pww3200c32_c1_data = {
	.data		= (stwuct cwkgen_pww_data *)&st_pww3200c32_cx_1,
	.outputs	= st_pww3200c32_cx_1_cwks,
};

static const stwuct cwkgen_pww_data st_pww3200c32_407_a9 = {
	/* 407 A9 */
	.pdn_status	= CWKGEN_FIEWD(0x1a8,	0x1,			0),
	.pdn_ctww	= CWKGEN_FIEWD(0x1a8,	0x1,			0),
	.wocked_status	= CWKGEN_FIEWD(0x87c,	0x1,			0),
	.ndiv		= CWKGEN_FIEWD(0x1b0,	C32_NDIV_MASK,		0),
	.idf		= CWKGEN_FIEWD(0x1a8,	C32_IDF_MASK,		25),
	.num_odfs = 1,
	.odf		= { CWKGEN_FIEWD(0x1b0, C32_ODF_MASK,		8) },
	.odf_gate	= { CWKGEN_FIEWD(0x1ac, 0x1,			28) },
	.switch2pww_en	= twue,
	.cp		= CWKGEN_FIEWD(0x1a8,	C32_CP_MASK,		1),
	.switch2pww	= CWKGEN_FIEWD(0x1a4,	0x1,			1),
	.wock = &cwkgen_a9_wock,
	.ops		= &stm_pww3200c32_a9_ops,
};

static const stwuct cwkgen_cwk_out st_pww3200c32_407_a9_cwks[] = {
	{ .name = "cwockgen-a9-pww-odf", },
};

static const stwuct cwkgen_pww_data_cwks st_pww3200c32_407_a9_data = {
	.data		= (stwuct cwkgen_pww_data *)&st_pww3200c32_407_a9,
	.outputs	= st_pww3200c32_407_a9_cwks,
};

static stwuct cwkgen_pww_data st_pww4600c28_418_a9 = {
	/* 418 A9 */
	.pdn_status	= CWKGEN_FIEWD(0x1a8,	0x1,			0),
	.pdn_ctww	= CWKGEN_FIEWD(0x1a8,	0x1,			0),
	.wocked_status	= CWKGEN_FIEWD(0x87c,	0x1,			0),
	.ndiv		= CWKGEN_FIEWD(0x1b0,	C28_NDIV_MASK,		0),
	.idf		= CWKGEN_FIEWD(0x1a8,	C28_IDF_MASK,		25),
	.num_odfs = 1,
	.odf		= { CWKGEN_FIEWD(0x1b0, C28_ODF_MASK,		8) },
	.odf_gate	= { CWKGEN_FIEWD(0x1ac, 0x1,			28) },
	.switch2pww_en	= twue,
	.switch2pww	= CWKGEN_FIEWD(0x1a4,	0x1,			1),
	.wock		= &cwkgen_a9_wock,
	.ops		= &stm_pww4600c28_ops,
};

static const stwuct cwkgen_cwk_out st_pww4600c28_418_a9_cwks[] = {
	{ .name = "cwockgen-a9-pww-odf", },
};

static const stwuct cwkgen_pww_data_cwks st_pww4600c28_418_a9_data = {
	.data		= (stwuct cwkgen_pww_data *)&st_pww4600c28_418_a9,
	.outputs	= st_pww4600c28_418_a9_cwks,
};

/**
 * DOC: Cwock Genewated by PWW, wate set and enabwed by bootwoadew
 *
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawent is (un)pwepawed
 * enabwe - cwk_enabwe/disabwe onwy ensuwes pawent is enabwed
 * wate - wate is fixed. No cwk_set_wate suppowt
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

/*
 * PWW cwock that is integwated in the CwockGenA instances on the STiH415
 * and STiH416.
 *
 * @hw: handwe between common and hawdwawe-specific intewfaces.
 * @wegs_base: base of the PWW configuwation wegistew(s).
 *
 */
stwuct cwkgen_pww {
	stwuct cwk_hw		hw;
	stwuct cwkgen_pww_data	*data;
	void __iomem		*wegs_base;
	spinwock_t	*wock;

	u32 ndiv;
	u32 idf;
	u32 cp;
};

#define to_cwkgen_pww(_hw) containew_of(_hw, stwuct cwkgen_pww, hw)

stwuct stm_pww {
	unsigned wong mdiv;
	unsigned wong ndiv;
	unsigned wong pdiv;
	unsigned wong odf;
	unsigned wong idf;
	unsigned wong wdf;
	unsigned wong cp;
};

static int cwkgen_pww_is_wocked(stwuct cwk_hw *hw)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	u32 wocked = CWKGEN_WEAD(pww, wocked_status);

	wetuwn !!wocked;
}

static int cwkgen_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	u32 powewoff = CWKGEN_WEAD(pww, pdn_status);
	wetuwn !powewoff;
}

static int __cwkgen_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	void __iomem *base =  pww->wegs_base;
	stwuct cwkgen_fiewd *fiewd = &pww->data->wocked_status;
	int wet = 0;
	u32 weg;

	if (cwkgen_pww_is_enabwed(hw))
		wetuwn 0;

	CWKGEN_WWITE(pww, pdn_ctww, 0);

	wet = weadw_wewaxed_poww_timeout(base + fiewd->offset, weg,
			!!((weg >> fiewd->shift) & fiewd->mask),  0, 10000);

	if (!wet) {
		if (pww->data->switch2pww_en)
			CWKGEN_WWITE(pww, switch2pww, 0);

		pw_debug("%s:%s enabwed\n", __cwk_get_name(hw->cwk), __func__);
	}

	wetuwn wet;
}

static int cwkgen_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	unsigned wong fwags = 0;
	int wet = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	wet = __cwkgen_pww_enabwe(hw);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn wet;
}

static void __cwkgen_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);

	if (!cwkgen_pww_is_enabwed(hw))
		wetuwn;

	if (pww->data->switch2pww_en)
		CWKGEN_WWITE(pww, switch2pww, 1);

	CWKGEN_WWITE(pww, pdn_ctww, 1);

	pw_debug("%s:%s disabwed\n", __cwk_get_name(hw->cwk), __func__);
}

static void cwkgen_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	unsigned wong fwags = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	__cwkgen_pww_disabwe(hw);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);
}

static int cwk_pww3200c32_get_pawams(unsigned wong input, unsigned wong output,
			  stwuct stm_pww *pww)
{
	unsigned wong i, n;
	unsigned wong deviation = ~0;
	unsigned wong new_fweq;
	wong new_deviation;
	/* Chawge pump tabwe: highest ndiv vawue fow cp=6 to 25 */
	static const unsigned chaw cp_tabwe[] = {
		48, 56, 64, 72, 80, 88, 96, 104, 112, 120,
		128, 136, 144, 152, 160, 168, 176, 184, 192
	};

	/* Output cwock wange: 800Mhz to 1600Mhz */
	if (output < 800000000 || output > 1600000000)
		wetuwn -EINVAW;

	input /= 1000;
	output /= 1000;

	fow (i = 1; i <= 7 && deviation; i++) {
		n = i * output / (2 * input);

		/* Checks */
		if (n < 8)
			continue;
		if (n > 200)
			bweak;

		new_fweq = (input * 2 * n) / i;

		new_deviation = abs(new_fweq - output);

		if (!new_deviation || new_deviation < deviation) {
			pww->idf  = i;
			pww->ndiv = n;
			deviation = new_deviation;
		}
	}

	if (deviation == ~0) /* No sowution found */
		wetuwn -EINVAW;

	/* Computing wecommended chawge pump vawue */
	fow (pww->cp = 6; pww->ndiv > cp_tabwe[pww->cp-6]; (pww->cp)++)
		;

	wetuwn 0;
}

static int cwk_pww3200c32_get_wate(unsigned wong input, stwuct stm_pww *pww,
			unsigned wong *wate)
{
	if (!pww->idf)
		pww->idf = 1;

	*wate = ((2 * (input / 1000) * pww->ndiv) / pww->idf) * 1000;

	wetuwn 0;
}

static unsigned wong wecawc_stm_pww3200c32(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	unsigned wong ndiv, idf;
	unsigned wong wate = 0;

	if (!cwkgen_pww_is_enabwed(hw) || !cwkgen_pww_is_wocked(hw))
		wetuwn 0;

	ndiv = CWKGEN_WEAD(pww, ndiv);
	idf = CWKGEN_WEAD(pww, idf);

	if (idf)
		/* Note: input is divided to avoid ovewfwow */
		wate = ((2 * (pawent_wate/1000) * ndiv) / idf) * 1000;

	pw_debug("%s:%s wate %wu\n", cwk_hw_get_name(hw), __func__, wate);

	wetuwn wate;
}

static wong wound_wate_stm_pww3200c32(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pwate)
{
	stwuct stm_pww pawams;

	if (!cwk_pww3200c32_get_pawams(*pwate, wate, &pawams))
		cwk_pww3200c32_get_wate(*pwate, &pawams, &wate);
	ewse {
		pw_debug("%s: %s wate %wd Invawid\n", __func__,
			 __cwk_get_name(hw->cwk), wate);
		wetuwn 0;
	}

	pw_debug("%s: %s new wate %wd [ndiv=%u] [idf=%u]\n",
		 __func__, __cwk_get_name(hw->cwk),
		 wate, (unsigned int)pawams.ndiv,
		 (unsigned int)pawams.idf);

	wetuwn wate;
}

static int set_wate_stm_pww3200c32(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	stwuct stm_pww pawams;
	wong hwwate = 0;
	unsigned wong fwags = 0;

	if (!wate || !pawent_wate)
		wetuwn -EINVAW;

	if (!cwk_pww3200c32_get_pawams(pawent_wate, wate, &pawams))
		cwk_pww3200c32_get_wate(pawent_wate, &pawams, &hwwate);

	pw_debug("%s: %s new wate %wd [ndiv=0x%x] [idf=0x%x]\n",
		 __func__, __cwk_get_name(hw->cwk),
		 hwwate, (unsigned int)pawams.ndiv,
		 (unsigned int)pawams.idf);

	if (!hwwate)
		wetuwn -EINVAW;

	pww->ndiv = pawams.ndiv;
	pww->idf = pawams.idf;
	pww->cp = pawams.cp;

	__cwkgen_pww_disabwe(hw);

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	CWKGEN_WWITE(pww, ndiv, pww->ndiv);
	CWKGEN_WWITE(pww, idf, pww->idf);
	CWKGEN_WWITE(pww, cp, pww->cp);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	__cwkgen_pww_enabwe(hw);

	wetuwn 0;
}

/* PWW output stwuctuwe
 * FVCO >> /2 >> FVCOBY2 (no output)
 *                 |> Dividew (ODF) >> PHI
 *
 * FVCOby2 output = (input * 2 * NDIV) / IDF (assuming FWAC_CONTWOW==W)
 *
 * Wuwes:
 *   4Mhz <= INFF input <= 350Mhz
 *   4Mhz <= INFIN (INFF / IDF) <= 50Mhz
 *   19.05Mhz <= FVCOby2 output (PHI w ODF=1) <= 3000Mhz
 *   1 <= i (wegistew/dec vawue fow IDF) <= 7
 *   8 <= n (wegistew/dec vawue fow NDIV) <= 246
 */

static int cwk_pww4600c28_get_pawams(unsigned wong input, unsigned wong output,
			  stwuct stm_pww *pww)
{

	unsigned wong i, infin, n;
	unsigned wong deviation = ~0;
	unsigned wong new_fweq, new_deviation;

	/* Output cwock wange: 19Mhz to 3000Mhz */
	if (output < 19000000 || output > 3000000000u)
		wetuwn -EINVAW;

	/* Fow bettew jittew, IDF shouwd be smawwest and NDIV must be maximum */
	fow (i = 1; i <= 7 && deviation; i++) {
		/* INFIN checks */
		infin = input / i;
		if (infin < 4000000 || infin > 50000000)
			continue;	/* Invawid case */

		n = output / (infin * 2);
		if (n < 8 || n > 246)
			continue;	/* Invawid case */
		if (n < 246)
			n++;	/* To wowk awound 'y' when n=x.y */

		fow (; n >= 8 && deviation; n--) {
			new_fweq = infin * 2 * n;
			if (new_fweq < output)
				bweak;	/* Optimization: showting woop */

			new_deviation = new_fweq - output;
			if (!new_deviation || new_deviation < deviation) {
				pww->idf  = i;
				pww->ndiv = n;
				deviation = new_deviation;
			}
		}
	}

	if (deviation == ~0) /* No sowution found */
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cwk_pww4600c28_get_wate(unsigned wong input, stwuct stm_pww *pww,
			unsigned wong *wate)
{
	if (!pww->idf)
		pww->idf = 1;

	*wate = (input / pww->idf) * 2 * pww->ndiv;

	wetuwn 0;
}

static unsigned wong wecawc_stm_pww4600c28(stwuct cwk_hw *hw,
				    unsigned wong pawent_wate)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	stwuct stm_pww pawams;
	unsigned wong wate;

	if (!cwkgen_pww_is_enabwed(hw) || !cwkgen_pww_is_wocked(hw))
		wetuwn 0;

	pawams.ndiv = CWKGEN_WEAD(pww, ndiv);
	pawams.idf = CWKGEN_WEAD(pww, idf);

	cwk_pww4600c28_get_wate(pawent_wate, &pawams, &wate);

	pw_debug("%s:%s wate %wu\n", __cwk_get_name(hw->cwk), __func__, wate);

	wetuwn wate;
}

static wong wound_wate_stm_pww4600c28(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pwate)
{
	stwuct stm_pww pawams;

	if (!cwk_pww4600c28_get_pawams(*pwate, wate, &pawams)) {
		cwk_pww4600c28_get_wate(*pwate, &pawams, &wate);
	} ewse {
		pw_debug("%s: %s wate %wd Invawid\n", __func__,
			 __cwk_get_name(hw->cwk), wate);
		wetuwn 0;
	}

	pw_debug("%s: %s new wate %wd [ndiv=%u] [idf=%u]\n",
		 __func__, __cwk_get_name(hw->cwk),
		 wate, (unsigned int)pawams.ndiv,
		 (unsigned int)pawams.idf);

	wetuwn wate;
}

static int set_wate_stm_pww4600c28(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct cwkgen_pww *pww = to_cwkgen_pww(hw);
	stwuct stm_pww pawams;
	wong hwwate;
	unsigned wong fwags = 0;

	if (!wate || !pawent_wate)
		wetuwn -EINVAW;

	if (!cwk_pww4600c28_get_pawams(pawent_wate, wate, &pawams)) {
		cwk_pww4600c28_get_wate(pawent_wate, &pawams, &hwwate);
	} ewse {
		pw_debug("%s: %s wate %wd Invawid\n", __func__,
			 __cwk_get_name(hw->cwk), wate);
		wetuwn -EINVAW;
	}

	pw_debug("%s: %s new wate %wd [ndiv=0x%x] [idf=0x%x]\n",
		 __func__, __cwk_get_name(hw->cwk),
		 hwwate, (unsigned int)pawams.ndiv,
		 (unsigned int)pawams.idf);

	if (!hwwate)
		wetuwn -EINVAW;

	pww->ndiv = pawams.ndiv;
	pww->idf = pawams.idf;

	__cwkgen_pww_disabwe(hw);

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	CWKGEN_WWITE(pww, ndiv, pww->ndiv);
	CWKGEN_WWITE(pww, idf, pww->idf);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	__cwkgen_pww_enabwe(hw);

	wetuwn 0;
}

static const stwuct cwk_ops stm_pww3200c32_ops = {
	.enabwe		= cwkgen_pww_enabwe,
	.disabwe	= cwkgen_pww_disabwe,
	.is_enabwed	= cwkgen_pww_is_enabwed,
	.wecawc_wate	= wecawc_stm_pww3200c32,
};

static const stwuct cwk_ops stm_pww3200c32_a9_ops = {
	.enabwe		= cwkgen_pww_enabwe,
	.disabwe	= cwkgen_pww_disabwe,
	.is_enabwed	= cwkgen_pww_is_enabwed,
	.wecawc_wate	= wecawc_stm_pww3200c32,
	.wound_wate	= wound_wate_stm_pww3200c32,
	.set_wate	= set_wate_stm_pww3200c32,
};

static const stwuct cwk_ops stm_pww4600c28_ops = {
	.enabwe		= cwkgen_pww_enabwe,
	.disabwe	= cwkgen_pww_disabwe,
	.is_enabwed	= cwkgen_pww_is_enabwed,
	.wecawc_wate	= wecawc_stm_pww4600c28,
	.wound_wate	= wound_wate_stm_pww4600c28,
	.set_wate	= set_wate_stm_pww4600c28,
};

static stwuct cwk * __init cwkgen_pww_wegistew(const chaw *pawent_name,
				stwuct cwkgen_pww_data	*pww_data,
				void __iomem *weg, unsigned wong pww_fwags,
				const chaw *cwk_name, spinwock_t *wock)
{
	stwuct cwkgen_pww *pww;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = cwk_name;
	init.ops = pww_data->ops;

	init.fwags = pww_fwags | CWK_GET_WATE_NOCACHE;
	init.pawent_names = &pawent_name;
	init.num_pawents  = 1;

	pww->data = pww_data;
	pww->wegs_base = weg;
	pww->hw.init = &init;
	pww->wock = wock;

	cwk = cwk_wegistew(NUWW, &pww->hw);
	if (IS_EWW(cwk)) {
		kfwee(pww);
		wetuwn cwk;
	}

	pw_debug("%s: pawent %s wate %wu\n",
			__cwk_get_name(cwk),
			__cwk_get_name(cwk_get_pawent(cwk)),
			cwk_get_wate(cwk));

	wetuwn cwk;
}

static void __iomem * __init cwkgen_get_wegistew_base(
				stwuct device_node *np)
{
	stwuct device_node *pnode;
	void __iomem *weg = NUWW;

	pnode = of_get_pawent(np);
	if (!pnode)
		wetuwn NUWW;

	weg = of_iomap(pnode, 0);

	of_node_put(pnode);
	wetuwn weg;
}

static stwuct cwk * __init cwkgen_odf_wegistew(const chaw *pawent_name,
					       void __iomem *weg,
					       stwuct cwkgen_pww_data *pww_data,
					       unsigned wong pww_fwags, int odf,
					       spinwock_t *odf_wock,
					       const chaw *odf_name)
{
	stwuct cwk *cwk;
	unsigned wong fwags;
	stwuct cwk_gate *gate;
	stwuct cwk_dividew *div;

	fwags = pww_fwags | CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	gate->fwags = CWK_GATE_SET_TO_DISABWE;
	gate->weg = weg + pww_data->odf_gate[odf].offset;
	gate->bit_idx = pww_data->odf_gate[odf].shift;
	gate->wock = odf_wock;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div) {
		kfwee(gate);
		wetuwn EWW_PTW(-ENOMEM);
	}

	div->fwags = CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO;
	div->weg = weg + pww_data->odf[odf].offset;
	div->shift = pww_data->odf[odf].shift;
	div->width = fws(pww_data->odf[odf].mask);
	div->wock = odf_wock;

	cwk = cwk_wegistew_composite(NUWW, odf_name, &pawent_name, 1,
				     NUWW, NUWW,
				     &div->hw, &cwk_dividew_ops,
				     &gate->hw, &cwk_gate_ops,
				     fwags);
	if (IS_EWW(cwk))
		wetuwn cwk;

	pw_debug("%s: pawent %s wate %wu\n",
			__cwk_get_name(cwk),
			__cwk_get_name(cwk_get_pawent(cwk)),
			cwk_get_wate(cwk));
	wetuwn cwk;
}


static void __init cwkgen_c32_pww_setup(stwuct device_node *np,
		stwuct cwkgen_pww_data_cwks *datac)
{
	stwuct cwk *cwk;
	const chaw *pawent_name, *pww_name;
	void __iomem *pww_base;
	int num_odfs, odf;
	stwuct cwk_oneceww_data *cwk_data;
	unsigned wong pww_fwags = 0;


	pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!pawent_name)
		wetuwn;

	pww_base = cwkgen_get_wegistew_base(np);
	if (!pww_base)
		wetuwn;

	of_cwk_detect_cwiticaw(np, 0, &pww_fwags);

	cwk = cwkgen_pww_wegistew(pawent_name, datac->data, pww_base, pww_fwags,
				  np->name, datac->data->wock);
	if (IS_EWW(cwk))
		wetuwn;

	pww_name = __cwk_get_name(cwk);

	num_odfs = datac->data->num_odfs;

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->cwk_num = num_odfs;
	cwk_data->cwks = kcawwoc(cwk_data->cwk_num, sizeof(stwuct cwk *),
				 GFP_KEWNEW);

	if (!cwk_data->cwks)
		goto eww;

	fow (odf = 0; odf < num_odfs; odf++) {
		stwuct cwk *cwk;
		const chaw *cwk_name;
		unsigned wong odf_fwags = 0;

		if (datac->outputs) {
			cwk_name = datac->outputs[odf].name;
			odf_fwags = datac->outputs[odf].fwags;
		} ewse {
			if (of_pwopewty_wead_stwing_index(np,
							  "cwock-output-names",
							  odf, &cwk_name))
				wetuwn;

			of_cwk_detect_cwiticaw(np, odf, &odf_fwags);
		}

		cwk = cwkgen_odf_wegistew(pww_name, pww_base, datac->data,
				odf_fwags, odf, &cwkgena_c32_odf_wock,
				cwk_name);
		if (IS_EWW(cwk))
			goto eww;

		cwk_data->cwks[odf] = cwk;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, cwk_data);
	wetuwn;

eww:
	kfwee(pww_name);
	kfwee(cwk_data->cwks);
	kfwee(cwk_data);
}
static void __init cwkgen_c32_pww0_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww3200c32_cx_0_wegacy_data);
}
CWK_OF_DECWAWE(c32_pww0, "st,cwkgen-pww0", cwkgen_c32_pww0_setup);

static void __init cwkgen_c32_pww0_a0_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww3200c32_a0_data);
}
CWK_OF_DECWAWE(c32_pww0_a0, "st,cwkgen-pww0-a0", cwkgen_c32_pww0_a0_setup);

static void __init cwkgen_c32_pww0_c0_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww3200c32_c0_data);
}
CWK_OF_DECWAWE(c32_pww0_c0, "st,cwkgen-pww0-c0", cwkgen_c32_pww0_c0_setup);

static void __init cwkgen_c32_pww1_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww3200c32_cx_1_wegacy_data);
}
CWK_OF_DECWAWE(c32_pww1, "st,cwkgen-pww1", cwkgen_c32_pww1_setup);

static void __init cwkgen_c32_pww1_c0_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww3200c32_c1_data);
}
CWK_OF_DECWAWE(c32_pww1_c0, "st,cwkgen-pww1-c0", cwkgen_c32_pww1_c0_setup);

static void __init cwkgen_c32_pwwa9_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww3200c32_407_a9_data);
}
CWK_OF_DECWAWE(c32_pwwa9, "st,stih407-cwkgen-pwwa9", cwkgen_c32_pwwa9_setup);

static void __init cwkgen_c28_pwwa9_setup(stwuct device_node *np)
{
	cwkgen_c32_pww_setup(np,
		(stwuct cwkgen_pww_data_cwks *) &st_pww4600c28_418_a9_data);
}
CWK_OF_DECWAWE(c28_pwwa9, "st,stih418-cwkgen-pwwa9", cwkgen_c28_pwwa9_setup);
