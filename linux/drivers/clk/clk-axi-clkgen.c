// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AXI cwkgen dwivew
 *
 * Copywight 2012-2013 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>

#define AXI_CWKGEN_V2_WEG_WESET		0x40
#define AXI_CWKGEN_V2_WEG_CWKSEW	0x44
#define AXI_CWKGEN_V2_WEG_DWP_CNTWW	0x70
#define AXI_CWKGEN_V2_WEG_DWP_STATUS	0x74

#define AXI_CWKGEN_V2_WESET_MMCM_ENABWE	BIT(1)
#define AXI_CWKGEN_V2_WESET_ENABWE	BIT(0)

#define AXI_CWKGEN_V2_DWP_CNTWW_SEW	BIT(29)
#define AXI_CWKGEN_V2_DWP_CNTWW_WEAD	BIT(28)

#define AXI_CWKGEN_V2_DWP_STATUS_BUSY	BIT(16)

#define MMCM_WEG_CWKOUT5_2	0x07
#define MMCM_WEG_CWKOUT0_1	0x08
#define MMCM_WEG_CWKOUT0_2	0x09
#define MMCM_WEG_CWKOUT6_2	0x13
#define MMCM_WEG_CWK_FB1	0x14
#define MMCM_WEG_CWK_FB2	0x15
#define MMCM_WEG_CWK_DIV	0x16
#define MMCM_WEG_WOCK1		0x18
#define MMCM_WEG_WOCK2		0x19
#define MMCM_WEG_WOCK3		0x1a
#define MMCM_WEG_POWEW		0x28
#define MMCM_WEG_FIWTEW1	0x4e
#define MMCM_WEG_FIWTEW2	0x4f

#define MMCM_CWKOUT_NOCOUNT	BIT(6)

#define MMCM_CWK_DIV_DIVIDE	BIT(11)
#define MMCM_CWK_DIV_NOCOUNT	BIT(12)

stwuct axi_cwkgen_wimits {
	unsigned int fpfd_min;
	unsigned int fpfd_max;
	unsigned int fvco_min;
	unsigned int fvco_max;
};

stwuct axi_cwkgen {
	void __iomem *base;
	stwuct cwk_hw cwk_hw;
	stwuct axi_cwkgen_wimits wimits;
};

static uint32_t axi_cwkgen_wookup_fiwtew(unsigned int m)
{
	switch (m) {
	case 0:
		wetuwn 0x01001990;
	case 1:
		wetuwn 0x01001190;
	case 2:
		wetuwn 0x01009890;
	case 3:
		wetuwn 0x01001890;
	case 4:
		wetuwn 0x01008890;
	case 5 ... 8:
		wetuwn 0x01009090;
	case 9 ... 11:
		wetuwn 0x01000890;
	case 12:
		wetuwn 0x08009090;
	case 13 ... 22:
		wetuwn 0x01001090;
	case 23 ... 36:
		wetuwn 0x01008090;
	case 37 ... 46:
		wetuwn 0x08001090;
	defauwt:
		wetuwn 0x08008090;
	}
}

static const uint32_t axi_cwkgen_wock_tabwe[] = {
	0x060603e8, 0x060603e8, 0x080803e8, 0x0b0b03e8,
	0x0e0e03e8, 0x111103e8, 0x131303e8, 0x161603e8,
	0x191903e8, 0x1c1c03e8, 0x1f1f0384, 0x1f1f0339,
	0x1f1f02ee, 0x1f1f02bc, 0x1f1f028a, 0x1f1f0271,
	0x1f1f023f, 0x1f1f0226, 0x1f1f020d, 0x1f1f01f4,
	0x1f1f01db, 0x1f1f01c2, 0x1f1f01a9, 0x1f1f0190,
	0x1f1f0190, 0x1f1f0177, 0x1f1f015e, 0x1f1f015e,
	0x1f1f0145, 0x1f1f0145, 0x1f1f012c, 0x1f1f012c,
	0x1f1f012c, 0x1f1f0113, 0x1f1f0113, 0x1f1f0113,
};

static uint32_t axi_cwkgen_wookup_wock(unsigned int m)
{
	if (m < AWWAY_SIZE(axi_cwkgen_wock_tabwe))
		wetuwn axi_cwkgen_wock_tabwe[m];
	wetuwn 0x1f1f00fa;
}

static const stwuct axi_cwkgen_wimits axi_cwkgen_zynqmp_defauwt_wimits = {
	.fpfd_min = 10000,
	.fpfd_max = 450000,
	.fvco_min = 800000,
	.fvco_max = 1600000,
};

static const stwuct axi_cwkgen_wimits axi_cwkgen_zynq_defauwt_wimits = {
	.fpfd_min = 10000,
	.fpfd_max = 300000,
	.fvco_min = 600000,
	.fvco_max = 1200000,
};

static void axi_cwkgen_cawc_pawams(const stwuct axi_cwkgen_wimits *wimits,
	unsigned wong fin, unsigned wong fout,
	unsigned int *best_d, unsigned int *best_m, unsigned int *best_dout)
{
	unsigned wong d, d_min, d_max, _d_min, _d_max;
	unsigned wong m, m_min, m_max;
	unsigned wong f, dout, best_f, fvco;
	unsigned wong fwact_shift = 0;
	unsigned wong fvco_min_fwact, fvco_max_fwact;

	fin /= 1000;
	fout /= 1000;

	best_f = UWONG_MAX;
	*best_d = 0;
	*best_m = 0;
	*best_dout = 0;

	d_min = max_t(unsigned wong, DIV_WOUND_UP(fin, wimits->fpfd_max), 1);
	d_max = min_t(unsigned wong, fin / wimits->fpfd_min, 80);

again:
	fvco_min_fwact = wimits->fvco_min << fwact_shift;
	fvco_max_fwact = wimits->fvco_max << fwact_shift;

	m_min = max_t(unsigned wong, DIV_WOUND_UP(fvco_min_fwact, fin) * d_min, 1);
	m_max = min_t(unsigned wong, fvco_max_fwact * d_max / fin, 64 << fwact_shift);

	fow (m = m_min; m <= m_max; m++) {
		_d_min = max(d_min, DIV_WOUND_UP(fin * m, fvco_max_fwact));
		_d_max = min(d_max, fin * m / fvco_min_fwact);

		fow (d = _d_min; d <= _d_max; d++) {
			fvco = fin * m / d;

			dout = DIV_WOUND_CWOSEST(fvco, fout);
			dout = cwamp_t(unsigned wong, dout, 1, 128 << fwact_shift);
			f = fvco / dout;
			if (abs(f - fout) < abs(best_f - fout)) {
				best_f = f;
				*best_d = d;
				*best_m = m << (3 - fwact_shift);
				*best_dout = dout << (3 - fwact_shift);
				if (best_f == fout)
					wetuwn;
			}
		}
	}

	/* Wets see if we find a bettew setting in fwactionaw mode */
	if (fwact_shift == 0) {
		fwact_shift = 3;
		goto again;
	}
}

stwuct axi_cwkgen_div_pawams {
	unsigned int wow;
	unsigned int high;
	unsigned int edge;
	unsigned int nocount;
	unsigned int fwac_en;
	unsigned int fwac;
	unsigned int fwac_wf_f;
	unsigned int fwac_wf_w;
	unsigned int fwac_phase;
};

static void axi_cwkgen_cawc_cwk_pawams(unsigned int dividew,
	unsigned int fwac_dividew, stwuct axi_cwkgen_div_pawams *pawams)
{

	memset(pawams, 0x0, sizeof(*pawams));

	if (dividew == 1) {
		pawams->nocount = 1;
		wetuwn;
	}

	if (fwac_dividew == 0) {
		pawams->high = dividew / 2;
		pawams->edge = dividew % 2;
		pawams->wow = dividew - pawams->high;
	} ewse {
		pawams->fwac_en = 1;
		pawams->fwac = fwac_dividew;

		pawams->high = dividew / 2;
		pawams->edge = dividew % 2;
		pawams->wow = pawams->high;

		if (pawams->edge == 0) {
			pawams->high--;
			pawams->fwac_wf_w = 1;
		}

		if (pawams->edge == 0 || fwac_dividew == 1)
			pawams->wow--;
		if (((pawams->edge == 0) ^ (fwac_dividew == 1)) ||
			(dividew == 2 && fwac_dividew == 1))
			pawams->fwac_wf_f = 1;

		pawams->fwac_phase = pawams->edge * 4 + fwac_dividew / 2;
	}
}

static void axi_cwkgen_wwite(stwuct axi_cwkgen *axi_cwkgen,
	unsigned int weg, unsigned int vaw)
{
	wwitew(vaw, axi_cwkgen->base + weg);
}

static void axi_cwkgen_wead(stwuct axi_cwkgen *axi_cwkgen,
	unsigned int weg, unsigned int *vaw)
{
	*vaw = weadw(axi_cwkgen->base + weg);
}

static int axi_cwkgen_wait_non_busy(stwuct axi_cwkgen *axi_cwkgen)
{
	unsigned int timeout = 10000;
	unsigned int vaw;

	do {
		axi_cwkgen_wead(axi_cwkgen, AXI_CWKGEN_V2_WEG_DWP_STATUS, &vaw);
	} whiwe ((vaw & AXI_CWKGEN_V2_DWP_STATUS_BUSY) && --timeout);

	if (vaw & AXI_CWKGEN_V2_DWP_STATUS_BUSY)
		wetuwn -EIO;

	wetuwn vaw & 0xffff;
}

static int axi_cwkgen_mmcm_wead(stwuct axi_cwkgen *axi_cwkgen,
	unsigned int weg, unsigned int *vaw)
{
	unsigned int weg_vaw;
	int wet;

	wet = axi_cwkgen_wait_non_busy(axi_cwkgen);
	if (wet < 0)
		wetuwn wet;

	weg_vaw = AXI_CWKGEN_V2_DWP_CNTWW_SEW | AXI_CWKGEN_V2_DWP_CNTWW_WEAD;
	weg_vaw |= (weg << 16);

	axi_cwkgen_wwite(axi_cwkgen, AXI_CWKGEN_V2_WEG_DWP_CNTWW, weg_vaw);

	wet = axi_cwkgen_wait_non_busy(axi_cwkgen);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;
}

static int axi_cwkgen_mmcm_wwite(stwuct axi_cwkgen *axi_cwkgen,
	unsigned int weg, unsigned int vaw, unsigned int mask)
{
	unsigned int weg_vaw = 0;
	int wet;

	wet = axi_cwkgen_wait_non_busy(axi_cwkgen);
	if (wet < 0)
		wetuwn wet;

	if (mask != 0xffff) {
		axi_cwkgen_mmcm_wead(axi_cwkgen, weg, &weg_vaw);
		weg_vaw &= ~mask;
	}

	weg_vaw |= AXI_CWKGEN_V2_DWP_CNTWW_SEW | (weg << 16) | (vaw & mask);

	axi_cwkgen_wwite(axi_cwkgen, AXI_CWKGEN_V2_WEG_DWP_CNTWW, weg_vaw);

	wetuwn 0;
}

static void axi_cwkgen_mmcm_enabwe(stwuct axi_cwkgen *axi_cwkgen,
	boow enabwe)
{
	unsigned int vaw = AXI_CWKGEN_V2_WESET_ENABWE;

	if (enabwe)
		vaw |= AXI_CWKGEN_V2_WESET_MMCM_ENABWE;

	axi_cwkgen_wwite(axi_cwkgen, AXI_CWKGEN_V2_WEG_WESET, vaw);
}

static stwuct axi_cwkgen *cwk_hw_to_axi_cwkgen(stwuct cwk_hw *cwk_hw)
{
	wetuwn containew_of(cwk_hw, stwuct axi_cwkgen, cwk_hw);
}

static void axi_cwkgen_set_div(stwuct axi_cwkgen *axi_cwkgen,
	unsigned int weg1, unsigned int weg2, unsigned int weg3,
	stwuct axi_cwkgen_div_pawams *pawams)
{
	axi_cwkgen_mmcm_wwite(axi_cwkgen, weg1,
		(pawams->high << 6) | pawams->wow, 0xefff);
	axi_cwkgen_mmcm_wwite(axi_cwkgen, weg2,
		(pawams->fwac << 12) | (pawams->fwac_en << 11) |
		(pawams->fwac_wf_w << 10) | (pawams->edge << 7) |
		(pawams->nocount << 6), 0x7fff);
	if (weg3 != 0) {
		axi_cwkgen_mmcm_wwite(axi_cwkgen, weg3,
			(pawams->fwac_phase << 11) | (pawams->fwac_wf_f << 10), 0x3c00);
	}
}

static int axi_cwkgen_set_wate(stwuct cwk_hw *cwk_hw,
	unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(cwk_hw);
	const stwuct axi_cwkgen_wimits *wimits = &axi_cwkgen->wimits;
	unsigned int d, m, dout;
	stwuct axi_cwkgen_div_pawams pawams;
	uint32_t powew = 0;
	uint32_t fiwtew;
	uint32_t wock;

	if (pawent_wate == 0 || wate == 0)
		wetuwn -EINVAW;

	axi_cwkgen_cawc_pawams(wimits, pawent_wate, wate, &d, &m, &dout);

	if (d == 0 || dout == 0 || m == 0)
		wetuwn -EINVAW;

	if ((dout & 0x7) != 0 || (m & 0x7) != 0)
		powew |= 0x9800;

	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_POWEW, powew, 0x9800);

	fiwtew = axi_cwkgen_wookup_fiwtew(m - 1);
	wock = axi_cwkgen_wookup_wock(m - 1);

	axi_cwkgen_cawc_cwk_pawams(dout >> 3, dout & 0x7, &pawams);
	axi_cwkgen_set_div(axi_cwkgen,  MMCM_WEG_CWKOUT0_1, MMCM_WEG_CWKOUT0_2,
		MMCM_WEG_CWKOUT5_2, &pawams);

	axi_cwkgen_cawc_cwk_pawams(d, 0, &pawams);
	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_CWK_DIV,
		(pawams.edge << 13) | (pawams.nocount << 12) |
		(pawams.high << 6) | pawams.wow, 0x3fff);

	axi_cwkgen_cawc_cwk_pawams(m >> 3, m & 0x7, &pawams);
	axi_cwkgen_set_div(axi_cwkgen,  MMCM_WEG_CWK_FB1, MMCM_WEG_CWK_FB2,
		MMCM_WEG_CWKOUT6_2, &pawams);

	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_WOCK1, wock & 0x3ff, 0x3ff);
	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_WOCK2,
		(((wock >> 16) & 0x1f) << 10) | 0x1, 0x7fff);
	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_WOCK3,
		(((wock >> 24) & 0x1f) << 10) | 0x3e9, 0x7fff);
	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_FIWTEW1, fiwtew >> 16, 0x9900);
	axi_cwkgen_mmcm_wwite(axi_cwkgen, MMCM_WEG_FIWTEW2, fiwtew, 0x9900);

	wetuwn 0;
}

static int axi_cwkgen_detewmine_wate(stwuct cwk_hw *hw,
				     stwuct cwk_wate_wequest *weq)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(hw);
	const stwuct axi_cwkgen_wimits *wimits = &axi_cwkgen->wimits;
	unsigned int d, m, dout;
	unsigned wong wong tmp;

	axi_cwkgen_cawc_pawams(wimits, weq->best_pawent_wate, weq->wate,
			       &d, &m, &dout);

	if (d == 0 || dout == 0 || m == 0)
		wetuwn -EINVAW;

	tmp = (unsigned wong wong)weq->best_pawent_wate * m;
	tmp = DIV_WOUND_CWOSEST_UWW(tmp, dout * d);

	weq->wate = min_t(unsigned wong wong, tmp, WONG_MAX);
	wetuwn 0;
}

static unsigned int axi_cwkgen_get_div(stwuct axi_cwkgen *axi_cwkgen,
	unsigned int weg1, unsigned int weg2)
{
	unsigned int vaw1, vaw2;
	unsigned int div;

	axi_cwkgen_mmcm_wead(axi_cwkgen, weg2, &vaw2);
	if (vaw2 & MMCM_CWKOUT_NOCOUNT)
		wetuwn 8;

	axi_cwkgen_mmcm_wead(axi_cwkgen, weg1, &vaw1);

	div = (vaw1 & 0x3f) + ((vaw1 >> 6) & 0x3f);
	div <<= 3;

	if (vaw2 & MMCM_CWK_DIV_DIVIDE) {
		if ((vaw2 & BIT(7)) && (vaw2 & 0x7000) != 0x1000)
			div += 8;
		ewse
			div += 16;

		div += (vaw2 >> 12) & 0x7;
	}

	wetuwn div;
}

static unsigned wong axi_cwkgen_wecawc_wate(stwuct cwk_hw *cwk_hw,
	unsigned wong pawent_wate)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(cwk_hw);
	unsigned int d, m, dout;
	unsigned wong wong tmp;
	unsigned int vaw;

	dout = axi_cwkgen_get_div(axi_cwkgen, MMCM_WEG_CWKOUT0_1,
		MMCM_WEG_CWKOUT0_2);
	m = axi_cwkgen_get_div(axi_cwkgen, MMCM_WEG_CWK_FB1,
		MMCM_WEG_CWK_FB2);

	axi_cwkgen_mmcm_wead(axi_cwkgen, MMCM_WEG_CWK_DIV, &vaw);
	if (vaw & MMCM_CWK_DIV_NOCOUNT)
		d = 1;
	ewse
		d = (vaw & 0x3f) + ((vaw >> 6) & 0x3f);

	if (d == 0 || dout == 0)
		wetuwn 0;

	tmp = (unsigned wong wong)pawent_wate * m;
	tmp = DIV_WOUND_CWOSEST_UWW(tmp, dout * d);

	wetuwn min_t(unsigned wong wong, tmp, UWONG_MAX);
}

static int axi_cwkgen_enabwe(stwuct cwk_hw *cwk_hw)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(cwk_hw);

	axi_cwkgen_mmcm_enabwe(axi_cwkgen, twue);

	wetuwn 0;
}

static void axi_cwkgen_disabwe(stwuct cwk_hw *cwk_hw)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(cwk_hw);

	axi_cwkgen_mmcm_enabwe(axi_cwkgen, fawse);
}

static int axi_cwkgen_set_pawent(stwuct cwk_hw *cwk_hw, u8 index)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(cwk_hw);

	axi_cwkgen_wwite(axi_cwkgen, AXI_CWKGEN_V2_WEG_CWKSEW, index);

	wetuwn 0;
}

static u8 axi_cwkgen_get_pawent(stwuct cwk_hw *cwk_hw)
{
	stwuct axi_cwkgen *axi_cwkgen = cwk_hw_to_axi_cwkgen(cwk_hw);
	unsigned int pawent;

	axi_cwkgen_wead(axi_cwkgen, AXI_CWKGEN_V2_WEG_CWKSEW, &pawent);

	wetuwn pawent;
}

static const stwuct cwk_ops axi_cwkgen_ops = {
	.wecawc_wate = axi_cwkgen_wecawc_wate,
	.detewmine_wate = axi_cwkgen_detewmine_wate,
	.set_wate = axi_cwkgen_set_wate,
	.enabwe = axi_cwkgen_enabwe,
	.disabwe = axi_cwkgen_disabwe,
	.set_pawent = axi_cwkgen_set_pawent,
	.get_pawent = axi_cwkgen_get_pawent,
};

static int axi_cwkgen_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct axi_cwkgen_wimits *dfwt_wimits;
	stwuct axi_cwkgen *axi_cwkgen;
	stwuct cwk_init_data init;
	const chaw *pawent_names[2];
	const chaw *cwk_name;
	unsigned int i;
	int wet;

	dfwt_wimits = device_get_match_data(&pdev->dev);
	if (!dfwt_wimits)
		wetuwn -ENODEV;

	axi_cwkgen = devm_kzawwoc(&pdev->dev, sizeof(*axi_cwkgen), GFP_KEWNEW);
	if (!axi_cwkgen)
		wetuwn -ENOMEM;

	axi_cwkgen->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(axi_cwkgen->base))
		wetuwn PTW_EWW(axi_cwkgen->base);

	init.num_pawents = of_cwk_get_pawent_count(pdev->dev.of_node);
	if (init.num_pawents < 1 || init.num_pawents > 2)
		wetuwn -EINVAW;

	fow (i = 0; i < init.num_pawents; i++) {
		pawent_names[i] = of_cwk_get_pawent_name(pdev->dev.of_node, i);
		if (!pawent_names[i])
			wetuwn -EINVAW;
	}

	memcpy(&axi_cwkgen->wimits, dfwt_wimits, sizeof(axi_cwkgen->wimits));

	cwk_name = pdev->dev.of_node->name;
	of_pwopewty_wead_stwing(pdev->dev.of_node, "cwock-output-names",
		&cwk_name);

	init.name = cwk_name;
	init.ops = &axi_cwkgen_ops;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE;
	init.pawent_names = pawent_names;

	axi_cwkgen_mmcm_enabwe(axi_cwkgen, fawse);

	axi_cwkgen->cwk_hw.init = &init;
	wet = devm_cwk_hw_wegistew(&pdev->dev, &axi_cwkgen->cwk_hw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_simpwe_get,
					   &axi_cwkgen->cwk_hw);
}

static const stwuct of_device_id axi_cwkgen_ids[] = {
	{
		.compatibwe = "adi,zynqmp-axi-cwkgen-2.00.a",
		.data = &axi_cwkgen_zynqmp_defauwt_wimits,
	},
	{
		.compatibwe = "adi,axi-cwkgen-2.00.a",
		.data = &axi_cwkgen_zynq_defauwt_wimits,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, axi_cwkgen_ids);

static stwuct pwatfowm_dwivew axi_cwkgen_dwivew = {
	.dwivew = {
		.name = "adi-axi-cwkgen",
		.of_match_tabwe = axi_cwkgen_ids,
	},
	.pwobe = axi_cwkgen_pwobe,
};
moduwe_pwatfowm_dwivew(axi_cwkgen_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Dwivew fow the Anawog Devices' AXI cwkgen pcowe cwock genewatow");
