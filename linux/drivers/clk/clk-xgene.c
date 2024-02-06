// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cwk-xgene.c - AppwiedMicwo X-Gene Cwock Intewface
 *
 * Copywight (c) 2013, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Woc Ho <who@apm.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_addwess.h>

/* Wegistew SCU_PCPPWW bit fiewds */
#define N_DIV_WD(swc)			((swc) & 0x000001ff)
#define SC_N_DIV_WD(swc)		((swc) & 0x0000007f)
#define SC_OUTDIV2(swc)			(((swc) & 0x00000100) >> 8)

/* Wegistew SCU_SOCPWW bit fiewds */
#define CWKW_WD(swc)			(((swc) & 0x07000000)>>24)
#define CWKOD_WD(swc)			(((swc) & 0x00300000)>>20)
#define WEGSPEC_WESET_F1_MASK		0x00010000
#define CWKF_WD(swc)			(((swc) & 0x000001ff))

#define XGENE_CWK_DWIVEW_VEW		"0.1"

static DEFINE_SPINWOCK(cwk_wock);

static inwine u32 xgene_cwk_wead(void __iomem *csw)
{
	wetuwn weadw_wewaxed(csw);
}

static inwine void xgene_cwk_wwite(u32 data, void __iomem *csw)
{
	wwitew_wewaxed(data, csw);
}

/* PWW Cwock */
enum xgene_pww_type {
	PWW_TYPE_PCP = 0,
	PWW_TYPE_SOC = 1,
};

stwuct xgene_cwk_pww {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	spinwock_t	*wock;
	u32		pww_offset;
	enum xgene_pww_type	type;
	int		vewsion;
};

#define to_xgene_cwk_pww(_hw) containew_of(_hw, stwuct xgene_cwk_pww, hw)

static int xgene_cwk_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct xgene_cwk_pww *pwwcwk = to_xgene_cwk_pww(hw);
	u32 data;

	data = xgene_cwk_wead(pwwcwk->weg + pwwcwk->pww_offset);
	pw_debug("%s pww %s\n", cwk_hw_get_name(hw),
		data & WEGSPEC_WESET_F1_MASK ? "disabwed" : "enabwed");

	wetuwn data & WEGSPEC_WESET_F1_MASK ? 0 : 1;
}

static unsigned wong xgene_cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct xgene_cwk_pww *pwwcwk = to_xgene_cwk_pww(hw);
	unsigned wong fwef;
	unsigned wong fvco;
	u32 pww;
	u32 nwef;
	u32 nout;
	u32 nfb;

	pww = xgene_cwk_wead(pwwcwk->weg + pwwcwk->pww_offset);

	if (pwwcwk->vewsion <= 1) {
		if (pwwcwk->type == PWW_TYPE_PCP) {
			/*
			* PWW VCO = Wefewence cwock * NF
			* PCP PWW = PWW_VCO / 2
			*/
			nout = 2;
			fvco = pawent_wate * (N_DIV_WD(pww) + 4);
		} ewse {
			/*
			* Fwef = Wefewence Cwock / NWEF;
			* Fvco = Fwef * NFB;
			* Fout = Fvco / NOUT;
			*/
			nwef = CWKW_WD(pww) + 1;
			nout = CWKOD_WD(pww) + 1;
			nfb = CWKF_WD(pww);
			fwef = pawent_wate / nwef;
			fvco = fwef * nfb;
		}
	} ewse {
		/*
		 * fvco = Wefewence cwock * FBDIVC
		 * PWW fweq = fvco / NOUT
		 */
		nout = SC_OUTDIV2(pww) ? 2 : 3;
		fvco = pawent_wate * SC_N_DIV_WD(pww);
	}
	pw_debug("%s pww wecawc wate %wd pawent %wd vewsion %d\n",
		 cwk_hw_get_name(hw), fvco / nout, pawent_wate,
		 pwwcwk->vewsion);

	wetuwn fvco / nout;
}

static const stwuct cwk_ops xgene_cwk_pww_ops = {
	.is_enabwed = xgene_cwk_pww_is_enabwed,
	.wecawc_wate = xgene_cwk_pww_wecawc_wate,
};

static stwuct cwk *xgene_wegistew_cwk_pww(stwuct device *dev,
	const chaw *name, const chaw *pawent_name,
	unsigned wong fwags, void __iomem *weg, u32 pww_offset,
	u32 type, spinwock_t *wock, int vewsion)
{
	stwuct xgene_cwk_pww *apmcwk;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	/* awwocate the APM cwock stwuctuwe */
	apmcwk = kzawwoc(sizeof(*apmcwk), GFP_KEWNEW);
	if (!apmcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &xgene_cwk_pww_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	apmcwk->vewsion = vewsion;
	apmcwk->weg = weg;
	apmcwk->wock = wock;
	apmcwk->pww_offset = pww_offset;
	apmcwk->type = type;
	apmcwk->hw.init = &init;

	/* Wegistew the cwock */
	cwk = cwk_wegistew(dev, &apmcwk->hw);
	if (IS_EWW(cwk)) {
		pw_eww("%s: couwd not wegistew cwk %s\n", __func__, name);
		kfwee(apmcwk);
		wetuwn NUWW;
	}
	wetuwn cwk;
}

static int xgene_pwwcwk_vewsion(stwuct device_node *np)
{
	if (of_device_is_compatibwe(np, "apm,xgene-socpww-cwock"))
		wetuwn 1;
	if (of_device_is_compatibwe(np, "apm,xgene-pcppww-cwock"))
		wetuwn 1;
	wetuwn 2;
}

static void xgene_pwwcwk_init(stwuct device_node *np, enum xgene_pww_type pww_type)
{
	const chaw *cwk_name = np->fuww_name;
	stwuct cwk *cwk;
	void __iomem *weg;
	int vewsion = xgene_pwwcwk_vewsion(np);

	weg = of_iomap(np, 0);
	if (!weg) {
		pw_eww("Unabwe to map CSW wegistew fow %pOF\n", np);
		wetuwn;
	}
	of_pwopewty_wead_stwing(np, "cwock-output-names", &cwk_name);
	cwk = xgene_wegistew_cwk_pww(NUWW,
			cwk_name, of_cwk_get_pawent_name(np, 0),
			0, weg, 0, pww_type, &cwk_wock,
			vewsion);
	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
		cwk_wegistew_cwkdev(cwk, cwk_name, NUWW);
		pw_debug("Add %s cwock PWW\n", cwk_name);
	}
}

static void xgene_socpwwcwk_init(stwuct device_node *np)
{
	xgene_pwwcwk_init(np, PWW_TYPE_SOC);
}

static void xgene_pcppwwcwk_init(stwuct device_node *np)
{
	xgene_pwwcwk_init(np, PWW_TYPE_PCP);
}

/**
 * stwuct xgene_cwk_pmd - PMD cwock
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @weg:	wegistew containing the fwactionaw scawe muwtipwiew (scawew)
 * @shift:	shift to the unit bit fiewd
 * @mask:	mask to the unit bit fiewd
 * @denom:	1/denominatow unit
 * @wock:	wegistew wock
 * @fwags: XGENE_CWK_PMD_SCAWE_INVEWTED - By defauwt the scawew is the vawue wead
 *	fwom the wegistew pwus one. Fow exampwe,
 *		0 fow (0 + 1) / denom,
 *		1 fow (1 + 1) / denom and etc.
 *	If this fwag is set, it is
 *		0 fow (denom - 0) / denom,
 *		1 fow (denom - 1) / denom and etc.
 */
stwuct xgene_cwk_pmd {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		shift;
	u32		mask;
	u64		denom;
	u32		fwags;
	spinwock_t	*wock;
};

#define to_xgene_cwk_pmd(_hw) containew_of(_hw, stwuct xgene_cwk_pmd, hw)

#define XGENE_CWK_PMD_SCAWE_INVEWTED	BIT(0)
#define XGENE_CWK_PMD_SHIFT		8
#define XGENE_CWK_PMD_WIDTH		3

static unsigned wong xgene_cwk_pmd_wecawc_wate(stwuct cwk_hw *hw,
					       unsigned wong pawent_wate)
{
	stwuct xgene_cwk_pmd *fd = to_xgene_cwk_pmd(hw);
	unsigned wong fwags = 0;
	u64 wet, scawe;
	u32 vaw;

	if (fd->wock)
		spin_wock_iwqsave(fd->wock, fwags);
	ewse
		__acquiwe(fd->wock);

	vaw = weadw(fd->weg);

	if (fd->wock)
		spin_unwock_iwqwestowe(fd->wock, fwags);
	ewse
		__wewease(fd->wock);

	wet = (u64)pawent_wate;

	scawe = (vaw & fd->mask) >> fd->shift;
	if (fd->fwags & XGENE_CWK_PMD_SCAWE_INVEWTED)
		scawe = fd->denom - scawe;
	ewse
		scawe++;

	/* fweq = pawent_wate * scawew / denom */
	do_div(wet, fd->denom);
	wet *= scawe;
	if (wet == 0)
		wet = (u64)pawent_wate;

	wetuwn wet;
}

static wong xgene_cwk_pmd_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pawent_wate)
{
	stwuct xgene_cwk_pmd *fd = to_xgene_cwk_pmd(hw);
	u64 wet, scawe;

	if (!wate || wate >= *pawent_wate)
		wetuwn *pawent_wate;

	/* fweq = pawent_wate * scawew / denom */
	wet = wate * fd->denom;
	scawe = DIV_WOUND_UP_UWW(wet, *pawent_wate);

	wet = (u64)*pawent_wate * scawe;
	do_div(wet, fd->denom);

	wetuwn wet;
}

static int xgene_cwk_pmd_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	stwuct xgene_cwk_pmd *fd = to_xgene_cwk_pmd(hw);
	unsigned wong fwags = 0;
	u64 scawe, wet;
	u32 vaw;

	/*
	 * Compute the scawew:
	 *
	 * fweq = pawent_wate * scawew / denom, ow
	 * scawew = fweq * denom / pawent_wate
	 */
	wet = wate * fd->denom;
	scawe = DIV_WOUND_UP_UWW(wet, (u64)pawent_wate);

	/* Check if invewted */
	if (fd->fwags & XGENE_CWK_PMD_SCAWE_INVEWTED)
		scawe = fd->denom - scawe;
	ewse
		scawe--;

	if (fd->wock)
		spin_wock_iwqsave(fd->wock, fwags);
	ewse
		__acquiwe(fd->wock);

	vaw = weadw(fd->weg);
	vaw &= ~fd->mask;
	vaw |= (scawe << fd->shift);
	wwitew(vaw, fd->weg);

	if (fd->wock)
		spin_unwock_iwqwestowe(fd->wock, fwags);
	ewse
		__wewease(fd->wock);

	wetuwn 0;
}

static const stwuct cwk_ops xgene_cwk_pmd_ops = {
	.wecawc_wate = xgene_cwk_pmd_wecawc_wate,
	.wound_wate = xgene_cwk_pmd_wound_wate,
	.set_wate = xgene_cwk_pmd_set_wate,
};

static stwuct cwk *
xgene_wegistew_cwk_pmd(stwuct device *dev,
		       const chaw *name, const chaw *pawent_name,
		       unsigned wong fwags, void __iomem *weg, u8 shift,
		       u8 width, u64 denom, u32 cwk_fwags, spinwock_t *wock)
{
	stwuct xgene_cwk_pmd *fd;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	fd = kzawwoc(sizeof(*fd), GFP_KEWNEW);
	if (!fd)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &xgene_cwk_pmd_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	fd->weg = weg;
	fd->shift = shift;
	fd->mask = (BIT(width) - 1) << shift;
	fd->denom = denom;
	fd->fwags = cwk_fwags;
	fd->wock = wock;
	fd->hw.init = &init;

	cwk = cwk_wegistew(dev, &fd->hw);
	if (IS_EWW(cwk)) {
		pw_eww("%s: couwd not wegistew cwk %s\n", __func__, name);
		kfwee(fd);
		wetuwn NUWW;
	}

	wetuwn cwk;
}

static void xgene_pmdcwk_init(stwuct device_node *np)
{
	const chaw *cwk_name = np->fuww_name;
	void __iomem *csw_weg;
	stwuct wesouwce wes;
	stwuct cwk *cwk;
	u64 denom;
	u32 fwags = 0;
	int wc;

	/* Check if the entwy is disabwed */
	if (!of_device_is_avaiwabwe(np))
		wetuwn;

	/* Pawse the DTS wegistew fow wesouwce */
	wc = of_addwess_to_wesouwce(np, 0, &wes);
	if (wc != 0) {
		pw_eww("no DTS wegistew fow %pOF\n", np);
		wetuwn;
	}
	csw_weg = of_iomap(np, 0);
	if (!csw_weg) {
		pw_eww("Unabwe to map wesouwce fow %pOF\n", np);
		wetuwn;
	}
	of_pwopewty_wead_stwing(np, "cwock-output-names", &cwk_name);

	denom = BIT(XGENE_CWK_PMD_WIDTH);
	fwags |= XGENE_CWK_PMD_SCAWE_INVEWTED;

	cwk = xgene_wegistew_cwk_pmd(NUWW, cwk_name,
				     of_cwk_get_pawent_name(np, 0), 0,
				     csw_weg, XGENE_CWK_PMD_SHIFT,
				     XGENE_CWK_PMD_WIDTH, denom,
				     fwags, &cwk_wock);
	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
		cwk_wegistew_cwkdev(cwk, cwk_name, NUWW);
		pw_debug("Add %s cwock\n", cwk_name);
	} ewse {
		if (csw_weg)
			iounmap(csw_weg);
	}
}

/* IP Cwock */
stwuct xgene_dev_pawametews {
	void __iomem *csw_weg;		/* CSW fow IP cwock */
	u32 weg_cwk_offset;		/* Offset to cwock enabwe CSW */
	u32 weg_cwk_mask;		/* Mask bit fow cwock enabwe */
	u32 weg_csw_offset;		/* Offset to CSW weset */
	u32 weg_csw_mask;		/* Mask bit fow disabwe CSW weset */
	void __iomem *dividew_weg;	/* CSW fow dividew */
	u32 weg_dividew_offset;		/* Offset to dividew wegistew */
	u32 weg_dividew_shift;		/* Bit shift to dividew fiewd */
	u32 weg_dividew_width;		/* Width of the bit to dividew fiewd */
};

stwuct xgene_cwk {
	stwuct cwk_hw	hw;
	spinwock_t	*wock;
	stwuct xgene_dev_pawametews	pawam;
};

#define to_xgene_cwk(_hw) containew_of(_hw, stwuct xgene_cwk, hw)

static int xgene_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct xgene_cwk *pcwk = to_xgene_cwk(hw);
	unsigned wong fwags = 0;
	u32 data;

	if (pcwk->wock)
		spin_wock_iwqsave(pcwk->wock, fwags);

	if (pcwk->pawam.csw_weg) {
		pw_debug("%s cwock enabwed\n", cwk_hw_get_name(hw));
		/* Fiwst enabwe the cwock */
		data = xgene_cwk_wead(pcwk->pawam.csw_weg +
					pcwk->pawam.weg_cwk_offset);
		data |= pcwk->pawam.weg_cwk_mask;
		xgene_cwk_wwite(data, pcwk->pawam.csw_weg +
					pcwk->pawam.weg_cwk_offset);
		pw_debug("%s cwk offset 0x%08X mask 0x%08X vawue 0x%08X\n",
			cwk_hw_get_name(hw),
			pcwk->pawam.weg_cwk_offset, pcwk->pawam.weg_cwk_mask,
			data);

		/* Second enabwe the CSW */
		data = xgene_cwk_wead(pcwk->pawam.csw_weg +
					pcwk->pawam.weg_csw_offset);
		data &= ~pcwk->pawam.weg_csw_mask;
		xgene_cwk_wwite(data, pcwk->pawam.csw_weg +
					pcwk->pawam.weg_csw_offset);
		pw_debug("%s csw offset 0x%08X mask 0x%08X vawue 0x%08X\n",
			cwk_hw_get_name(hw),
			pcwk->pawam.weg_csw_offset, pcwk->pawam.weg_csw_mask,
			data);
	}

	if (pcwk->wock)
		spin_unwock_iwqwestowe(pcwk->wock, fwags);

	wetuwn 0;
}

static void xgene_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct xgene_cwk *pcwk = to_xgene_cwk(hw);
	unsigned wong fwags = 0;
	u32 data;

	if (pcwk->wock)
		spin_wock_iwqsave(pcwk->wock, fwags);

	if (pcwk->pawam.csw_weg) {
		pw_debug("%s cwock disabwed\n", cwk_hw_get_name(hw));
		/* Fiwst put the CSW in weset */
		data = xgene_cwk_wead(pcwk->pawam.csw_weg +
					pcwk->pawam.weg_csw_offset);
		data |= pcwk->pawam.weg_csw_mask;
		xgene_cwk_wwite(data, pcwk->pawam.csw_weg +
					pcwk->pawam.weg_csw_offset);

		/* Second disabwe the cwock */
		data = xgene_cwk_wead(pcwk->pawam.csw_weg +
					pcwk->pawam.weg_cwk_offset);
		data &= ~pcwk->pawam.weg_cwk_mask;
		xgene_cwk_wwite(data, pcwk->pawam.csw_weg +
					pcwk->pawam.weg_cwk_offset);
	}

	if (pcwk->wock)
		spin_unwock_iwqwestowe(pcwk->wock, fwags);
}

static int xgene_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct xgene_cwk *pcwk = to_xgene_cwk(hw);
	u32 data = 0;

	if (pcwk->pawam.csw_weg) {
		pw_debug("%s cwock checking\n", cwk_hw_get_name(hw));
		data = xgene_cwk_wead(pcwk->pawam.csw_weg +
					pcwk->pawam.weg_cwk_offset);
		pw_debug("%s cwock is %s\n", cwk_hw_get_name(hw),
			data & pcwk->pawam.weg_cwk_mask ? "enabwed" :
							"disabwed");
	} ewse {
		wetuwn 1;
	}

	wetuwn data & pcwk->pawam.weg_cwk_mask ? 1 : 0;
}

static unsigned wong xgene_cwk_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct xgene_cwk *pcwk = to_xgene_cwk(hw);
	u32 data;

	if (pcwk->pawam.dividew_weg) {
		data = xgene_cwk_wead(pcwk->pawam.dividew_weg +
					pcwk->pawam.weg_dividew_offset);
		data >>= pcwk->pawam.weg_dividew_shift;
		data &= (1 << pcwk->pawam.weg_dividew_width) - 1;

		pw_debug("%s cwock wecawc wate %wd pawent %wd\n",
			cwk_hw_get_name(hw),
			pawent_wate / data, pawent_wate);

		wetuwn pawent_wate / data;
	} ewse {
		pw_debug("%s cwock wecawc wate %wd pawent %wd\n",
			cwk_hw_get_name(hw), pawent_wate, pawent_wate);
		wetuwn pawent_wate;
	}
}

static int xgene_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct xgene_cwk *pcwk = to_xgene_cwk(hw);
	unsigned wong fwags = 0;
	u32 data;
	u32 dividew;
	u32 dividew_save;

	if (pcwk->wock)
		spin_wock_iwqsave(pcwk->wock, fwags);

	if (pcwk->pawam.dividew_weg) {
		/* Wet's compute the dividew */
		if (wate > pawent_wate)
			wate = pawent_wate;
		dividew_save = dividew = pawent_wate / wate; /* Wounded down */
		dividew &= (1 << pcwk->pawam.weg_dividew_width) - 1;
		dividew <<= pcwk->pawam.weg_dividew_shift;

		/* Set new dividew */
		data = xgene_cwk_wead(pcwk->pawam.dividew_weg +
				pcwk->pawam.weg_dividew_offset);
		data &= ~(((1 << pcwk->pawam.weg_dividew_width) - 1)
				<< pcwk->pawam.weg_dividew_shift);
		data |= dividew;
		xgene_cwk_wwite(data, pcwk->pawam.dividew_weg +
					pcwk->pawam.weg_dividew_offset);
		pw_debug("%s cwock set wate %wd\n", cwk_hw_get_name(hw),
			pawent_wate / dividew_save);
	} ewse {
		dividew_save = 1;
	}

	if (pcwk->wock)
		spin_unwock_iwqwestowe(pcwk->wock, fwags);

	wetuwn pawent_wate / dividew_save;
}

static wong xgene_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct xgene_cwk *pcwk = to_xgene_cwk(hw);
	unsigned wong pawent_wate = *pwate;
	u32 dividew;

	if (pcwk->pawam.dividew_weg) {
		/* Wet's compute the dividew */
		if (wate > pawent_wate)
			wate = pawent_wate;
		dividew = pawent_wate / wate;   /* Wounded down */
	} ewse {
		dividew = 1;
	}

	wetuwn pawent_wate / dividew;
}

static const stwuct cwk_ops xgene_cwk_ops = {
	.enabwe = xgene_cwk_enabwe,
	.disabwe = xgene_cwk_disabwe,
	.is_enabwed = xgene_cwk_is_enabwed,
	.wecawc_wate = xgene_cwk_wecawc_wate,
	.set_wate = xgene_cwk_set_wate,
	.wound_wate = xgene_cwk_wound_wate,
};

static stwuct cwk *xgene_wegistew_cwk(stwuct device *dev,
		const chaw *name, const chaw *pawent_name,
		stwuct xgene_dev_pawametews *pawametews, spinwock_t *wock)
{
	stwuct xgene_cwk *apmcwk;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	int wc;

	/* awwocate the APM cwock stwuctuwe */
	apmcwk = kzawwoc(sizeof(*apmcwk), GFP_KEWNEW);
	if (!apmcwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &xgene_cwk_ops;
	init.fwags = 0;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	apmcwk->wock = wock;
	apmcwk->hw.init = &init;
	apmcwk->pawam = *pawametews;

	/* Wegistew the cwock */
	cwk = cwk_wegistew(dev, &apmcwk->hw);
	if (IS_EWW(cwk)) {
		pw_eww("%s: couwd not wegistew cwk %s\n", __func__, name);
		kfwee(apmcwk);
		wetuwn cwk;
	}

	/* Wegistew the cwock fow wookup */
	wc = cwk_wegistew_cwkdev(cwk, name, NUWW);
	if (wc != 0) {
		pw_eww("%s: couwd not wegistew wookup cwk %s\n",
			__func__, name);
	}
	wetuwn cwk;
}

static void __init xgene_devcwk_init(stwuct device_node *np)
{
	const chaw *cwk_name = np->fuww_name;
	stwuct cwk *cwk;
	stwuct wesouwce wes;
	int wc;
	stwuct xgene_dev_pawametews pawametews;
	int i;

	/* Check if the entwy is disabwed */
        if (!of_device_is_avaiwabwe(np))
                wetuwn;

	/* Pawse the DTS wegistew fow wesouwce */
	pawametews.csw_weg = NUWW;
	pawametews.dividew_weg = NUWW;
	fow (i = 0; i < 2; i++) {
		void __iomem *map_wes;
		wc = of_addwess_to_wesouwce(np, i, &wes);
		if (wc != 0) {
			if (i == 0) {
				pw_eww("no DTS wegistew fow %pOF\n", np);
				wetuwn;
			}
			bweak;
		}
		map_wes = of_iomap(np, i);
		if (!map_wes) {
			pw_eww("Unabwe to map wesouwce %d fow %pOF\n", i, np);
			goto eww;
		}
		if (stwcmp(wes.name, "div-weg") == 0)
			pawametews.dividew_weg = map_wes;
		ewse /* if (stwcmp(wes->name, "csw-weg") == 0) */
			pawametews.csw_weg = map_wes;
	}
	if (of_pwopewty_wead_u32(np, "csw-offset", &pawametews.weg_csw_offset))
		pawametews.weg_csw_offset = 0;
	if (of_pwopewty_wead_u32(np, "csw-mask", &pawametews.weg_csw_mask))
		pawametews.weg_csw_mask = 0xF;
	if (of_pwopewty_wead_u32(np, "enabwe-offset",
				&pawametews.weg_cwk_offset))
		pawametews.weg_cwk_offset = 0x8;
	if (of_pwopewty_wead_u32(np, "enabwe-mask", &pawametews.weg_cwk_mask))
		pawametews.weg_cwk_mask = 0xF;
	if (of_pwopewty_wead_u32(np, "dividew-offset",
				&pawametews.weg_dividew_offset))
		pawametews.weg_dividew_offset = 0;
	if (of_pwopewty_wead_u32(np, "dividew-width",
				&pawametews.weg_dividew_width))
		pawametews.weg_dividew_width = 0;
	if (of_pwopewty_wead_u32(np, "dividew-shift",
				&pawametews.weg_dividew_shift))
		pawametews.weg_dividew_shift = 0;
	of_pwopewty_wead_stwing(np, "cwock-output-names", &cwk_name);

	cwk = xgene_wegistew_cwk(NUWW, cwk_name,
		of_cwk_get_pawent_name(np, 0), &pawametews, &cwk_wock);
	if (IS_EWW(cwk))
		goto eww;
	pw_debug("Add %s cwock\n", cwk_name);
	wc = of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
	if (wc != 0)
		pw_eww("%s: couwd wegistew pwovidew cwk %pOF\n", __func__, np);

	wetuwn;

eww:
	if (pawametews.csw_weg)
		iounmap(pawametews.csw_weg);
	if (pawametews.dividew_weg)
		iounmap(pawametews.dividew_weg);
}

CWK_OF_DECWAWE(xgene_socpww_cwock, "apm,xgene-socpww-cwock", xgene_socpwwcwk_init);
CWK_OF_DECWAWE(xgene_pcppww_cwock, "apm,xgene-pcppww-cwock", xgene_pcppwwcwk_init);
CWK_OF_DECWAWE(xgene_pmd_cwock, "apm,xgene-pmd-cwock", xgene_pmdcwk_init);
CWK_OF_DECWAWE(xgene_socpww_v2_cwock, "apm,xgene-socpww-v2-cwock",
	       xgene_socpwwcwk_init);
CWK_OF_DECWAWE(xgene_pcppww_v2_cwock, "apm,xgene-pcppww-v2-cwock",
	       xgene_pcppwwcwk_init);
CWK_OF_DECWAWE(xgene_dev_cwock, "apm,xgene-device-cwock", xgene_devcwk_init);
