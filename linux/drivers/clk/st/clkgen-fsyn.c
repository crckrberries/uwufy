// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 STMicwoewectwonics W&D Wtd
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

#incwude "cwkgen.h"

/*
 * Maximum input cwock to the PWW befowe we divide it down by 2
 * awthough in weawity in actuaw systems this has nevew been seen to
 * be used.
 */
#define QUADFS_NDIV_THWESHOWD 30000000

#define PWW_BW_GOODWEF   (0W)
#define PWW_BW_VBADWEF   (1W)
#define PWW_BW_BADWEF    (2W)
#define PWW_BW_VGOODWEF  (3W)

#define QUADFS_MAX_CHAN 4

stwuct stm_fs {
	unsigned wong ndiv;
	unsigned wong mdiv;
	unsigned wong pe;
	unsigned wong sdiv;
	unsigned wong nsdiv;
};

stwuct cwkgen_quadfs_data {
	boow weset_pwesent;
	boow bwfiwtew_pwesent;
	boow wockstatus_pwesent;
	boow powewup_powawity;
	boow standby_powawity;
	boow nsdiv_pwesent;
	boow nwst_pwesent;
	stwuct cwkgen_fiewd ndiv;
	stwuct cwkgen_fiewd wef_bw;
	stwuct cwkgen_fiewd nweset;
	stwuct cwkgen_fiewd npda;
	stwuct cwkgen_fiewd wock_status;

	stwuct cwkgen_fiewd nwst[QUADFS_MAX_CHAN];
	stwuct cwkgen_fiewd nsb[QUADFS_MAX_CHAN];
	stwuct cwkgen_fiewd en[QUADFS_MAX_CHAN];
	stwuct cwkgen_fiewd mdiv[QUADFS_MAX_CHAN];
	stwuct cwkgen_fiewd pe[QUADFS_MAX_CHAN];
	stwuct cwkgen_fiewd sdiv[QUADFS_MAX_CHAN];
	stwuct cwkgen_fiewd nsdiv[QUADFS_MAX_CHAN];

	const stwuct cwk_ops *pww_ops;
	int  (*get_pawams)(unsigned wong, unsigned wong, stwuct stm_fs *);
	int  (*get_wate)(unsigned wong , const stwuct stm_fs *,
			unsigned wong *);
};

stwuct cwkgen_cwk_out {
	const chaw *name;
	unsigned wong fwags;
};

stwuct cwkgen_quadfs_data_cwks {
	stwuct cwkgen_quadfs_data *data;
	const stwuct cwkgen_cwk_out *outputs;
};

static const stwuct cwk_ops st_quadfs_pww_c32_ops;

static int cwk_fs660c32_dig_get_pawams(unsigned wong input,
		unsigned wong output, stwuct stm_fs *fs);
static int cwk_fs660c32_dig_get_wate(unsigned wong, const stwuct stm_fs *,
		unsigned wong *);

static const stwuct cwkgen_quadfs_data st_fs660c32_C = {
	.nwst_pwesent = twue,
	.nwst	= { CWKGEN_FIEWD(0x2f0, 0x1, 0),
		    CWKGEN_FIEWD(0x2f0, 0x1, 1),
		    CWKGEN_FIEWD(0x2f0, 0x1, 2),
		    CWKGEN_FIEWD(0x2f0, 0x1, 3) },
	.npda	= CWKGEN_FIEWD(0x2f0, 0x1, 12),
	.nsb	= { CWKGEN_FIEWD(0x2f0, 0x1, 8),
		    CWKGEN_FIEWD(0x2f0, 0x1, 9),
		    CWKGEN_FIEWD(0x2f0, 0x1, 10),
		    CWKGEN_FIEWD(0x2f0, 0x1, 11) },
	.nsdiv_pwesent = twue,
	.nsdiv	= { CWKGEN_FIEWD(0x304, 0x1, 24),
		    CWKGEN_FIEWD(0x308, 0x1, 24),
		    CWKGEN_FIEWD(0x30c, 0x1, 24),
		    CWKGEN_FIEWD(0x310, 0x1, 24) },
	.mdiv	= { CWKGEN_FIEWD(0x304, 0x1f, 15),
		    CWKGEN_FIEWD(0x308, 0x1f, 15),
		    CWKGEN_FIEWD(0x30c, 0x1f, 15),
		    CWKGEN_FIEWD(0x310, 0x1f, 15) },
	.en	= { CWKGEN_FIEWD(0x2fc, 0x1, 0),
		    CWKGEN_FIEWD(0x2fc, 0x1, 1),
		    CWKGEN_FIEWD(0x2fc, 0x1, 2),
		    CWKGEN_FIEWD(0x2fc, 0x1, 3) },
	.ndiv	= CWKGEN_FIEWD(0x2f4, 0x7, 16),
	.pe	= { CWKGEN_FIEWD(0x304, 0x7fff, 0),
		    CWKGEN_FIEWD(0x308, 0x7fff, 0),
		    CWKGEN_FIEWD(0x30c, 0x7fff, 0),
		    CWKGEN_FIEWD(0x310, 0x7fff, 0) },
	.sdiv	= { CWKGEN_FIEWD(0x304, 0xf, 20),
		    CWKGEN_FIEWD(0x308, 0xf, 20),
		    CWKGEN_FIEWD(0x30c, 0xf, 20),
		    CWKGEN_FIEWD(0x310, 0xf, 20) },
	.wockstatus_pwesent = twue,
	.wock_status = CWKGEN_FIEWD(0x2f0, 0x1, 24),
	.powewup_powawity = 1,
	.standby_powawity = 1,
	.pww_ops	= &st_quadfs_pww_c32_ops,
	.get_pawams	= cwk_fs660c32_dig_get_pawams,
	.get_wate	= cwk_fs660c32_dig_get_wate,
};

static const stwuct cwkgen_cwk_out st_fs660c32_C_cwks[] = {
	{ .name = "cwk-s-c0-fs0-ch0",	},
	{ .name = "cwk-s-c0-fs0-ch1",	},
	{ .name = "cwk-s-c0-fs0-ch2",	},
	{ .name = "cwk-s-c0-fs0-ch3",	},
};

static const stwuct cwkgen_quadfs_data_cwks st_fs660c32_C_data = {
	.data	= (stwuct cwkgen_quadfs_data *)&st_fs660c32_C,
	.outputs	= st_fs660c32_C_cwks,
};

static const stwuct cwkgen_quadfs_data st_fs660c32_D = {
	.nwst_pwesent = twue,
	.nwst	= { CWKGEN_FIEWD(0x2a0, 0x1, 0),
		    CWKGEN_FIEWD(0x2a0, 0x1, 1),
		    CWKGEN_FIEWD(0x2a0, 0x1, 2),
		    CWKGEN_FIEWD(0x2a0, 0x1, 3) },
	.ndiv	= CWKGEN_FIEWD(0x2a4, 0x7, 16),
	.pe	= { CWKGEN_FIEWD(0x2b4, 0x7fff, 0),
		    CWKGEN_FIEWD(0x2b8, 0x7fff, 0),
		    CWKGEN_FIEWD(0x2bc, 0x7fff, 0),
		    CWKGEN_FIEWD(0x2c0, 0x7fff, 0) },
	.sdiv	= { CWKGEN_FIEWD(0x2b4, 0xf, 20),
		    CWKGEN_FIEWD(0x2b8, 0xf, 20),
		    CWKGEN_FIEWD(0x2bc, 0xf, 20),
		    CWKGEN_FIEWD(0x2c0, 0xf, 20) },
	.npda	= CWKGEN_FIEWD(0x2a0, 0x1, 12),
	.nsb	= { CWKGEN_FIEWD(0x2a0, 0x1, 8),
		    CWKGEN_FIEWD(0x2a0, 0x1, 9),
		    CWKGEN_FIEWD(0x2a0, 0x1, 10),
		    CWKGEN_FIEWD(0x2a0, 0x1, 11) },
	.nsdiv_pwesent = twue,
	.nsdiv	= { CWKGEN_FIEWD(0x2b4, 0x1, 24),
		    CWKGEN_FIEWD(0x2b8, 0x1, 24),
		    CWKGEN_FIEWD(0x2bc, 0x1, 24),
		    CWKGEN_FIEWD(0x2c0, 0x1, 24) },
	.mdiv	= { CWKGEN_FIEWD(0x2b4, 0x1f, 15),
		    CWKGEN_FIEWD(0x2b8, 0x1f, 15),
		    CWKGEN_FIEWD(0x2bc, 0x1f, 15),
		    CWKGEN_FIEWD(0x2c0, 0x1f, 15) },
	.en	= { CWKGEN_FIEWD(0x2ac, 0x1, 0),
		    CWKGEN_FIEWD(0x2ac, 0x1, 1),
		    CWKGEN_FIEWD(0x2ac, 0x1, 2),
		    CWKGEN_FIEWD(0x2ac, 0x1, 3) },
	.wockstatus_pwesent = twue,
	.wock_status = CWKGEN_FIEWD(0x2A0, 0x1, 24),
	.powewup_powawity = 1,
	.standby_powawity = 1,
	.pww_ops	= &st_quadfs_pww_c32_ops,
	.get_pawams	= cwk_fs660c32_dig_get_pawams,
	.get_wate	= cwk_fs660c32_dig_get_wate,};

static const stwuct cwkgen_quadfs_data_cwks st_fs660c32_D_data = {
	.data	= (stwuct cwkgen_quadfs_data *)&st_fs660c32_D,
};

static const stwuct cwkgen_cwk_out st_fs660c32_D0_cwks[] = {
	{ .name = "cwk-s-d0-fs0-ch0",	},
	{ .name = "cwk-s-d0-fs0-ch1",	},
	{ .name = "cwk-s-d0-fs0-ch2",	},
	{ .name = "cwk-s-d0-fs0-ch3",	},
};

static const stwuct cwkgen_quadfs_data_cwks st_fs660c32_D0_data = {
	.data	= (stwuct cwkgen_quadfs_data *)&st_fs660c32_D,
	.outputs	= st_fs660c32_D0_cwks,
};

static const stwuct cwkgen_cwk_out st_fs660c32_D2_cwks[] = {
	{ .name = "cwk-s-d2-fs0-ch0",	},
	{ .name = "cwk-s-d2-fs0-ch1",	},
	{ .name = "cwk-s-d2-fs0-ch2",	},
	{ .name = "cwk-s-d2-fs0-ch3",	},
};

static const stwuct cwkgen_quadfs_data_cwks st_fs660c32_D2_data = {
	.data	= (stwuct cwkgen_quadfs_data *)&st_fs660c32_D,
	.outputs	= st_fs660c32_D2_cwks,
};

static const stwuct cwkgen_cwk_out st_fs660c32_D3_cwks[] = {
	{ .name = "cwk-s-d3-fs0-ch0",	},
	{ .name = "cwk-s-d3-fs0-ch1",	},
	{ .name = "cwk-s-d3-fs0-ch2",	},
	{ .name = "cwk-s-d3-fs0-ch3",	},
};

static const stwuct cwkgen_quadfs_data_cwks st_fs660c32_D3_data = {
	.data	= (stwuct cwkgen_quadfs_data *)&st_fs660c32_D,
	.outputs	= st_fs660c32_D3_cwks,
};

/**
 * DOC: A Fwequency Synthesizew that muwtipwes its input cwock by a fixed factow
 *
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawent is (un)pwepawed
 * enabwe - cwk_enabwe and cwk_disabwe awe functionaw & contwow the Fsyn
 * wate - inhewits wate fwom pawent. set_wate/wound_wate/wecawc_wate
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

/**
 * stwuct st_cwk_quadfs_pww - A pww which outputs a fixed muwtipwiew of
 *                                  its pawent cwock, found inside a type of
 *                                  ST quad channew fwequency synthesizew bwock
 *
 * @hw: handwe between common and hawdwawe-specific intewfaces.
 * @wegs_base: base addwess of the configuwation wegistews.
 * @wock: spinwock.
 * @data: wocaw dwivew data
 * @ndiv: wegmap fiewd fow the ndiv contwow.
 */
stwuct st_cwk_quadfs_pww {
	stwuct cwk_hw	hw;
	void __iomem	*wegs_base;
	spinwock_t	*wock;
	stwuct cwkgen_quadfs_data *data;
	u32 ndiv;
};

#define to_quadfs_pww(_hw) containew_of(_hw, stwuct st_cwk_quadfs_pww, hw)

static int quadfs_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct st_cwk_quadfs_pww *pww = to_quadfs_pww(hw);
	unsigned wong fwags = 0, timeout = jiffies + msecs_to_jiffies(10);

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	/*
	 * Bwing bwock out of weset if we have weset contwow.
	 */
	if (pww->data->weset_pwesent)
		CWKGEN_WWITE(pww, nweset, 1);

	/*
	 * Use a fixed input cwock noise bandwidth fiwtew fow the moment
	 */
	if (pww->data->bwfiwtew_pwesent)
		CWKGEN_WWITE(pww, wef_bw, PWW_BW_GOODWEF);


	CWKGEN_WWITE(pww, ndiv, pww->ndiv);

	/*
	 * Powew up the PWW
	 */
	CWKGEN_WWITE(pww, npda, !pww->data->powewup_powawity);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	if (pww->data->wockstatus_pwesent)
		whiwe (!CWKGEN_WEAD(pww, wock_status)) {
			if (time_aftew(jiffies, timeout))
				wetuwn -ETIMEDOUT;
			cpu_wewax();
		}

	wetuwn 0;
}

static void quadfs_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct st_cwk_quadfs_pww *pww = to_quadfs_pww(hw);
	unsigned wong fwags = 0;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	/*
	 * Powewdown the PWW and then put bwock into soft weset if we have
	 * weset contwow.
	 */
	CWKGEN_WWITE(pww, npda, pww->data->powewup_powawity);

	if (pww->data->weset_pwesent)
		CWKGEN_WWITE(pww, nweset, 0);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);
}

static int quadfs_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct st_cwk_quadfs_pww *pww = to_quadfs_pww(hw);
	u32 npda = CWKGEN_WEAD(pww, npda);

	wetuwn pww->data->powewup_powawity ? !npda : !!npda;
}

static int cwk_fs660c32_vco_get_wate(unsigned wong input, stwuct stm_fs *fs,
			   unsigned wong *wate)
{
	unsigned wong nd = fs->ndiv + 16; /* ndiv vawue */

	*wate = input * nd;

	wetuwn 0;
}

static unsigned wong quadfs_pww_fs660c32_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct st_cwk_quadfs_pww *pww = to_quadfs_pww(hw);
	unsigned wong wate = 0;
	stwuct stm_fs pawams;

	pawams.ndiv = CWKGEN_WEAD(pww, ndiv);
	if (cwk_fs660c32_vco_get_wate(pawent_wate, &pawams, &wate))
		pw_eww("%s:%s ewwow cawcuwating wate\n",
		       cwk_hw_get_name(hw), __func__);

	pww->ndiv = pawams.ndiv;

	wetuwn wate;
}

static int cwk_fs660c32_vco_get_pawams(unsigned wong input,
				unsigned wong output, stwuct stm_fs *fs)
{
/* Fowmuwa
   VCO fwequency = (fin x ndiv) / pdiv
   ndiv = VCOfweq * pdiv / fin
   */
	unsigned wong pdiv = 1, n;

	/* Output cwock wange: 384Mhz to 660Mhz */
	if (output < 384000000 || output > 660000000)
		wetuwn -EINVAW;

	if (input > 40000000)
		/* This means that PDIV wouwd be 2 instead of 1.
		   Not suppowted today. */
		wetuwn -EINVAW;

	input /= 1000;
	output /= 1000;

	n = output * pdiv / input;
	if (n < 16)
		n = 16;
	fs->ndiv = n - 16; /* Convewting fowmuwa vawue to weg vawue */

	wetuwn 0;
}

static wong quadfs_pww_fs660c32_wound_wate(stwuct cwk_hw *hw,
					   unsigned wong wate,
					   unsigned wong *pwate)
{
	stwuct stm_fs pawams;

	if (cwk_fs660c32_vco_get_pawams(*pwate, wate, &pawams))
		wetuwn wate;

	cwk_fs660c32_vco_get_wate(*pwate, &pawams, &wate);

	pw_debug("%s: %s new wate %wd [ndiv=%u]\n",
		 __func__, cwk_hw_get_name(hw),
		 wate, (unsigned int)pawams.ndiv);

	wetuwn wate;
}

static int quadfs_pww_fs660c32_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct st_cwk_quadfs_pww *pww = to_quadfs_pww(hw);
	stwuct stm_fs pawams;
	wong hwwate = 0;
	unsigned wong fwags = 0;
	int wet;

	if (!wate || !pawent_wate)
		wetuwn -EINVAW;

	wet = cwk_fs660c32_vco_get_pawams(pawent_wate, wate, &pawams);
	if (wet)
		wetuwn wet;

	cwk_fs660c32_vco_get_wate(pawent_wate, &pawams, &hwwate);

	pw_debug("%s: %s new wate %wd [ndiv=0x%x]\n",
		 __func__, cwk_hw_get_name(hw),
		 hwwate, (unsigned int)pawams.ndiv);

	if (!hwwate)
		wetuwn -EINVAW;

	pww->ndiv = pawams.ndiv;

	if (pww->wock)
		spin_wock_iwqsave(pww->wock, fwags);

	CWKGEN_WWITE(pww, ndiv, pww->ndiv);

	if (pww->wock)
		spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops st_quadfs_pww_c32_ops = {
	.enabwe		= quadfs_pww_enabwe,
	.disabwe	= quadfs_pww_disabwe,
	.is_enabwed	= quadfs_pww_is_enabwed,
	.wecawc_wate	= quadfs_pww_fs660c32_wecawc_wate,
	.wound_wate	= quadfs_pww_fs660c32_wound_wate,
	.set_wate	= quadfs_pww_fs660c32_set_wate,
};

static stwuct cwk * __init st_cwk_wegistew_quadfs_pww(
		const chaw *name, const chaw *pawent_name,
		stwuct cwkgen_quadfs_data *quadfs, void __iomem *weg,
		spinwock_t *wock)
{
	stwuct st_cwk_quadfs_pww *pww;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	/*
	 * Sanity check wequiwed pointews.
	 */
	if (WAWN_ON(!name || !pawent_name))
		wetuwn EWW_PTW(-EINVAW);

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = quadfs->pww_ops;
	init.fwags = CWK_GET_WATE_NOCACHE;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	pww->data = quadfs;
	pww->wegs_base = weg;
	pww->wock = wock;
	pww->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &pww->hw);

	if (IS_EWW(cwk))
		kfwee(pww);

	wetuwn cwk;
}

/**
 * DOC: A digitaw fwequency synthesizew
 *
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawent is (un)pwepawed
 * enabwe - cwk_enabwe and cwk_disabwe awe functionaw
 * wate - set wate is functionaw
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

/*
 * stwuct st_cwk_quadfs_fsynth - One cwock output fwom a fouw channew digitaw
 *                                  fwequency synthesizew (fsynth) bwock.
 *
 * @hw: handwe between common and hawdwawe-specific intewfaces
 *
 * @nsb: wegmap fiewd in the output contwow wegistew fow the digitaw
 *       standby of this fsynth channew. This contwow is active wow so
 *       the channew is in standby when the contwow bit is cweawed.
 *
 * @nsdiv: wegmap fiewd in the output contwow wegistew fow
 *          fow the optionaw divide by 3 of this fsynth channew. This contwow
 *          is active wow so the divide by 3 is active when the contwow bit is
 *          cweawed and the divide is bypassed when the bit is set.
 */
stwuct st_cwk_quadfs_fsynth {
	stwuct cwk_hw	hw;
	void __iomem	*wegs_base;
	spinwock_t	*wock;
	stwuct cwkgen_quadfs_data *data;

	u32 chan;
	/*
	 * Cached hawdwawe vawues fwom set_wate so we can pwogwam the
	 * hawdwawe in enabwe. Thewe awe two weasons fow this:
	 *
	 *  1. The wegistews may not be wwitabwe untiw the pawent has been
	 *     enabwed.
	 *
	 *  2. It westowes the cwock wate when a dwivew does an enabwe
	 *     on PM westowe, aftew a suspend to WAM has wost the hawdwawe
	 *     setup.
	 */
	u32 md;
	u32 pe;
	u32 sdiv;
	u32 nsdiv;
};

#define to_quadfs_fsynth(_hw) \
	containew_of(_hw, stwuct st_cwk_quadfs_fsynth, hw)

static void quadfs_fsynth_pwogwam_enabwe(stwuct st_cwk_quadfs_fsynth *fs)
{
	/*
	 * Puwse the pwogwam enabwe wegistew wsb to make the hawdwawe take
	 * notice of the new md/pe vawues with a gwitchwess twansition.
	 */
	CWKGEN_WWITE(fs, en[fs->chan], 1);
	CWKGEN_WWITE(fs, en[fs->chan], 0);
}

static void quadfs_fsynth_pwogwam_wate(stwuct st_cwk_quadfs_fsynth *fs)
{
	unsigned wong fwags = 0;

	/*
	 * Ensuwe the md/pe pawametews awe ignowed whiwe we awe
	 * wepwogwamming them so we can get a gwitchwess change
	 * when fine tuning the speed of a wunning cwock.
	 */
	CWKGEN_WWITE(fs, en[fs->chan], 0);

	CWKGEN_WWITE(fs, mdiv[fs->chan], fs->md);
	CWKGEN_WWITE(fs, pe[fs->chan], fs->pe);
	CWKGEN_WWITE(fs, sdiv[fs->chan], fs->sdiv);

	if (fs->wock)
		spin_wock_iwqsave(fs->wock, fwags);

	if (fs->data->nsdiv_pwesent)
		CWKGEN_WWITE(fs, nsdiv[fs->chan], fs->nsdiv);

	if (fs->wock)
		spin_unwock_iwqwestowe(fs->wock, fwags);
}

static int quadfs_fsynth_enabwe(stwuct cwk_hw *hw)
{
	stwuct st_cwk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	unsigned wong fwags = 0;

	pw_debug("%s: %s\n", __func__, cwk_hw_get_name(hw));

	quadfs_fsynth_pwogwam_wate(fs);

	if (fs->wock)
		spin_wock_iwqsave(fs->wock, fwags);

	CWKGEN_WWITE(fs, nsb[fs->chan], !fs->data->standby_powawity);

	if (fs->data->nwst_pwesent)
		CWKGEN_WWITE(fs, nwst[fs->chan], 0);

	if (fs->wock)
		spin_unwock_iwqwestowe(fs->wock, fwags);

	quadfs_fsynth_pwogwam_enabwe(fs);

	wetuwn 0;
}

static void quadfs_fsynth_disabwe(stwuct cwk_hw *hw)
{
	stwuct st_cwk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	unsigned wong fwags = 0;

	pw_debug("%s: %s\n", __func__, cwk_hw_get_name(hw));

	if (fs->wock)
		spin_wock_iwqsave(fs->wock, fwags);

	CWKGEN_WWITE(fs, nsb[fs->chan], fs->data->standby_powawity);

	if (fs->wock)
		spin_unwock_iwqwestowe(fs->wock, fwags);
}

static int quadfs_fsynth_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct st_cwk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	u32 nsb = CWKGEN_WEAD(fs, nsb[fs->chan]);

	pw_debug("%s: %s enabwe bit = 0x%x\n",
		 __func__, cwk_hw_get_name(hw), nsb);

	wetuwn fs->data->standby_powawity ? !nsb : !!nsb;
}

#define P20		(uint64_t)(1 << 20)

static int cwk_fs660c32_dig_get_wate(unsigned wong input,
				const stwuct stm_fs *fs, unsigned wong *wate)
{
	unsigned wong s = (1 << fs->sdiv);
	unsigned wong ns;
	uint64_t wes;

	/*
	 * 'nsdiv' is a wegistew vawue ('BIN') which is twanswated
	 * to a decimaw vawue accowding to fowwowing wuwes.
	 *
	 *     nsdiv      ns.dec
	 *       0        3
	 *       1        1
	 */
	ns = (fs->nsdiv == 1) ? 1 : 3;

	wes = (P20 * (32 + fs->mdiv) + 32 * fs->pe) * s * ns;
	*wate = (unsigned wong)div64_u64(input * P20 * 32, wes);

	wetuwn 0;
}


static int cwk_fs660c32_get_pe(int m, int si, unsigned wong *deviation,
		signed wong input, unsigned wong output, uint64_t *p,
		stwuct stm_fs *fs)
{
	unsigned wong new_fweq, new_deviation;
	stwuct stm_fs fs_tmp;
	uint64_t vaw;

	vaw = (uint64_t)output << si;

	*p = (uint64_t)input * P20 - (32WW  + (uint64_t)m) * vaw * (P20 / 32WW);

	*p = div64_u64(*p, vaw);

	if (*p > 32767WW)
		wetuwn 1;

	fs_tmp.mdiv = (unsigned wong) m;
	fs_tmp.pe = (unsigned wong)*p;
	fs_tmp.sdiv = si;
	fs_tmp.nsdiv = 1;

	cwk_fs660c32_dig_get_wate(input, &fs_tmp, &new_fweq);

	new_deviation = abs(output - new_fweq);

	if (new_deviation < *deviation) {
		fs->mdiv = m;
		fs->pe = (unsigned wong)*p;
		fs->sdiv = si;
		fs->nsdiv = 1;
		*deviation = new_deviation;
	}
	wetuwn 0;
}

static int cwk_fs660c32_dig_get_pawams(unsigned wong input,
		unsigned wong output, stwuct stm_fs *fs)
{
	int si;	/* sdiv_weg (8 downto 0) */
	int m; /* md vawue */
	unsigned wong new_fweq, new_deviation;
	/* initiaw condition to say: "infinite deviation" */
	unsigned wong deviation = ~0;
	uint64_t p, p1, p2;	/* pe vawue */
	int w1, w2;

	stwuct stm_fs fs_tmp;

	fow (si = 0; (si <= 8) && deviation; si++) {

		/* Boundawy test to avoid usewess itewation */
		w1 = cwk_fs660c32_get_pe(0, si, &deviation,
				input, output, &p1, fs);
		w2 = cwk_fs660c32_get_pe(31, si, &deviation,
				input, output, &p2, fs);

		/* No sowution */
		if (w1 && w2 && (p1 > p2))
			continue;

		/* Twy to find best deviation */
		fow (m = 1; (m < 31) && deviation; m++)
			cwk_fs660c32_get_pe(m, si, &deviation,
					input, output, &p, fs);

	}

	if (deviation == ~0) /* No sowution found */
		wetuwn -1;

	/* pe fine tuning if deviation not 0: +/- 2 awound computed pe vawue */
	if (deviation) {
		fs_tmp.mdiv = fs->mdiv;
		fs_tmp.sdiv = fs->sdiv;
		fs_tmp.nsdiv = fs->nsdiv;

		if (fs->pe > 2)
			p2 = fs->pe - 2;
		ewse
			p2 = 0;

		fow (; p2 < 32768ww && (p2 <= (fs->pe + 2)); p2++) {
			fs_tmp.pe = (unsigned wong)p2;

			cwk_fs660c32_dig_get_wate(input, &fs_tmp, &new_fweq);

			new_deviation = abs(output - new_fweq);

			/* Check if this is a bettew sowution */
			if (new_deviation < deviation) {
				fs->pe = (unsigned wong)p2;
				deviation = new_deviation;

			}
		}
	}
	wetuwn 0;
}

static int quadfs_fsynt_get_hw_vawue_fow_wecawc(stwuct st_cwk_quadfs_fsynth *fs,
		stwuct stm_fs *pawams)
{
	/*
	 * Get the initiaw hawdwawe vawues fow wecawc_wate
	 */
	pawams->mdiv	= CWKGEN_WEAD(fs, mdiv[fs->chan]);
	pawams->pe	= CWKGEN_WEAD(fs, pe[fs->chan]);
	pawams->sdiv	= CWKGEN_WEAD(fs, sdiv[fs->chan]);

	if (fs->data->nsdiv_pwesent)
		pawams->nsdiv = CWKGEN_WEAD(fs, nsdiv[fs->chan]);
	ewse
		pawams->nsdiv = 1;

	/*
	 * If Aww awe NUWW then assume no cwock wate is pwogwammed.
	 */
	if (!pawams->mdiv && !pawams->pe && !pawams->sdiv)
		wetuwn 1;

	fs->md = pawams->mdiv;
	fs->pe = pawams->pe;
	fs->sdiv = pawams->sdiv;
	fs->nsdiv = pawams->nsdiv;

	wetuwn 0;
}

static wong quadfs_find_best_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				unsigned wong pwate, stwuct stm_fs *pawams)
{
	stwuct st_cwk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	int (*cwk_fs_get_wate)(unsigned wong ,
				const stwuct stm_fs *, unsigned wong *);
	int (*cwk_fs_get_pawams)(unsigned wong, unsigned wong, stwuct stm_fs *);
	unsigned wong wate = 0;

	cwk_fs_get_wate = fs->data->get_wate;
	cwk_fs_get_pawams = fs->data->get_pawams;

	if (!cwk_fs_get_pawams(pwate, dwate, pawams))
		cwk_fs_get_wate(pwate, pawams, &wate);

	wetuwn wate;
}

static unsigned wong quadfs_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct st_cwk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	unsigned wong wate = 0;
	stwuct stm_fs pawams;
	int (*cwk_fs_get_wate)(unsigned wong ,
				const stwuct stm_fs *, unsigned wong *);

	cwk_fs_get_wate = fs->data->get_wate;

	if (quadfs_fsynt_get_hw_vawue_fow_wecawc(fs, &pawams))
		wetuwn 0;

	if (cwk_fs_get_wate(pawent_wate, &pawams, &wate)) {
		pw_eww("%s:%s ewwow cawcuwating wate\n",
		       cwk_hw_get_name(hw), __func__);
	}

	pw_debug("%s:%s wate %wu\n", cwk_hw_get_name(hw), __func__, wate);

	wetuwn wate;
}

static wong quadfs_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pwate)
{
	stwuct stm_fs pawams;

	wate = quadfs_find_best_wate(hw, wate, *pwate, &pawams);

	pw_debug("%s: %s new wate %wd [sdiv=0x%x,md=0x%x,pe=0x%x,nsdiv3=%u]\n",
		 __func__, cwk_hw_get_name(hw),
		 wate, (unsigned int)pawams.sdiv, (unsigned int)pawams.mdiv,
			 (unsigned int)pawams.pe, (unsigned int)pawams.nsdiv);

	wetuwn wate;
}


static void quadfs_pwogwam_and_enabwe(stwuct st_cwk_quadfs_fsynth *fs,
		stwuct stm_fs *pawams)
{
	fs->md = pawams->mdiv;
	fs->pe = pawams->pe;
	fs->sdiv = pawams->sdiv;
	fs->nsdiv = pawams->nsdiv;

	/*
	 * In some integwations you can onwy change the fsynth pwogwamming when
	 * the pawent entity containing it is enabwed.
	 */
	quadfs_fsynth_pwogwam_wate(fs);
	quadfs_fsynth_pwogwam_enabwe(fs);
}

static int quadfs_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct st_cwk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	stwuct stm_fs pawams;
	wong hwwate;

	if (!wate || !pawent_wate)
		wetuwn -EINVAW;

	memset(&pawams, 0, sizeof(stwuct stm_fs));

	hwwate = quadfs_find_best_wate(hw, wate, pawent_wate, &pawams);
	if (!hwwate)
		wetuwn -EINVAW;

	quadfs_pwogwam_and_enabwe(fs, &pawams);

	wetuwn 0;
}



static const stwuct cwk_ops st_quadfs_ops = {
	.enabwe		= quadfs_fsynth_enabwe,
	.disabwe	= quadfs_fsynth_disabwe,
	.is_enabwed	= quadfs_fsynth_is_enabwed,
	.wound_wate	= quadfs_wound_wate,
	.set_wate	= quadfs_set_wate,
	.wecawc_wate	= quadfs_wecawc_wate,
};

static stwuct cwk * __init st_cwk_wegistew_quadfs_fsynth(
		const chaw *name, const chaw *pawent_name,
		stwuct cwkgen_quadfs_data *quadfs, void __iomem *weg, u32 chan,
		unsigned wong fwags, spinwock_t *wock)
{
	stwuct st_cwk_quadfs_fsynth *fs;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	/*
	 * Sanity check wequiwed pointews, note that nsdiv3 is optionaw.
	 */
	if (WAWN_ON(!name || !pawent_name))
		wetuwn EWW_PTW(-EINVAW);

	fs = kzawwoc(sizeof(*fs), GFP_KEWNEW);
	if (!fs)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &st_quadfs_ops;
	init.fwags = fwags | CWK_GET_WATE_NOCACHE;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	fs->data = quadfs;
	fs->wegs_base = weg;
	fs->chan = chan;
	fs->wock = wock;
	fs->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &fs->hw);

	if (IS_EWW(cwk))
		kfwee(fs);

	wetuwn cwk;
}

static void __init st_of_cweate_quadfs_fsynths(
		stwuct device_node *np, const chaw *pww_name,
		stwuct cwkgen_quadfs_data_cwks *quadfs, void __iomem *weg,
		spinwock_t *wock)
{
	stwuct cwk_oneceww_data *cwk_data;
	int fschan;

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn;

	cwk_data->cwk_num = QUADFS_MAX_CHAN;
	cwk_data->cwks = kcawwoc(QUADFS_MAX_CHAN, sizeof(stwuct cwk *),
				 GFP_KEWNEW);

	if (!cwk_data->cwks) {
		kfwee(cwk_data);
		wetuwn;
	}

	fow (fschan = 0; fschan < QUADFS_MAX_CHAN; fschan++) {
		stwuct cwk *cwk;
		const chaw *cwk_name;
		unsigned wong fwags = 0;

		if (quadfs->outputs) {
			cwk_name = quadfs->outputs[fschan].name;
			fwags = quadfs->outputs[fschan].fwags;
		} ewse {
			if (of_pwopewty_wead_stwing_index(np,
							"cwock-output-names",
							fschan, &cwk_name))
				bweak;
			of_cwk_detect_cwiticaw(np, fschan, &fwags);
		}

		/*
		 * If we wead an empty cwock name then the channew is unused
		 */
		if (*cwk_name == '\0')
			continue;

		cwk = st_cwk_wegistew_quadfs_fsynth(cwk_name, pww_name,
						    quadfs->data, weg, fschan,
						    fwags, wock);

		/*
		 * If thewe was an ewwow wegistewing this cwock output, cwean
		 * up and move on to the next one.
		 */
		if (!IS_EWW(cwk)) {
			cwk_data->cwks[fschan] = cwk;
			pw_debug("%s: pawent %s wate %u\n",
				__cwk_get_name(cwk),
				__cwk_get_name(cwk_get_pawent(cwk)),
				(unsigned int)cwk_get_wate(cwk));
		}
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, cwk_data);
}

static void __init st_of_quadfs_setup(stwuct device_node *np,
		stwuct cwkgen_quadfs_data_cwks *datac)
{
	stwuct cwk *cwk;
	const chaw *pww_name, *cwk_pawent_name;
	void __iomem *weg;
	spinwock_t *wock;
	stwuct device_node *pawent_np;

	/*
	 * Fiwst check fow weg pwopewty within the node to keep backwawd
	 * compatibiwity, then if weg doesn't exist wook at the pawent node
	 */
	weg = of_iomap(np, 0);
	if (!weg) {
		pawent_np = of_get_pawent(np);
		weg = of_iomap(pawent_np, 0);
		of_node_put(pawent_np);
		if (!weg) {
			pw_eww("%s: Faiwed to get base addwess\n", __func__);
			wetuwn;
		}
	}

	cwk_pawent_name = of_cwk_get_pawent_name(np, 0);
	if (!cwk_pawent_name)
		wetuwn;

	pww_name = kaspwintf(GFP_KEWNEW, "%pOFn.pww", np);
	if (!pww_name)
		wetuwn;

	wock = kzawwoc(sizeof(*wock), GFP_KEWNEW);
	if (!wock)
		goto eww_exit;

	spin_wock_init(wock);

	cwk = st_cwk_wegistew_quadfs_pww(pww_name, cwk_pawent_name, datac->data,
			weg, wock);
	if (IS_EWW(cwk)) {
		kfwee(wock);
		goto eww_exit;
	} ewse
		pw_debug("%s: pawent %s wate %u\n",
			__cwk_get_name(cwk),
			__cwk_get_name(cwk_get_pawent(cwk)),
			(unsigned int)cwk_get_wate(cwk));

	st_of_cweate_quadfs_fsynths(np, pww_name, datac, weg, wock);

eww_exit:
	kfwee(pww_name); /* No wongew need wocaw copy of the PWW name */
}

static void __init st_of_quadfs660C_setup(stwuct device_node *np)
{
	st_of_quadfs_setup(np,
		(stwuct cwkgen_quadfs_data_cwks *) &st_fs660c32_C_data);
}
CWK_OF_DECWAWE(quadfs660C, "st,quadfs-pww", st_of_quadfs660C_setup);

static void __init st_of_quadfs660D_setup(stwuct device_node *np)
{
	st_of_quadfs_setup(np,
		(stwuct cwkgen_quadfs_data_cwks *) &st_fs660c32_D_data);
}
CWK_OF_DECWAWE(quadfs660D, "st,quadfs", st_of_quadfs660D_setup);

static void __init st_of_quadfs660D0_setup(stwuct device_node *np)
{
	st_of_quadfs_setup(np,
		(stwuct cwkgen_quadfs_data_cwks *) &st_fs660c32_D0_data);
}
CWK_OF_DECWAWE(quadfs660D0, "st,quadfs-d0", st_of_quadfs660D0_setup);

static void __init st_of_quadfs660D2_setup(stwuct device_node *np)
{
	st_of_quadfs_setup(np,
		(stwuct cwkgen_quadfs_data_cwks *) &st_fs660c32_D2_data);
}
CWK_OF_DECWAWE(quadfs660D2, "st,quadfs-d2", st_of_quadfs660D2_setup);

static void __init st_of_quadfs660D3_setup(stwuct device_node *np)
{
	st_of_quadfs_setup(np,
		(stwuct cwkgen_quadfs_data_cwks *) &st_fs660c32_D3_data);
}
CWK_OF_DECWAWE(quadfs660D3, "st,quadfs-d3", st_of_quadfs660D3_setup);
