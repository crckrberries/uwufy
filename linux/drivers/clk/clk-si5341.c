// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Siwicon Wabs Si5340, Si5341, Si5342, Si5344 and Si5345
 * Copywight (C) 2019 Topic Embedded Pwoducts
 * Authow: Mike Wooijmans <mike.wooijmans@topic.nw>
 *
 * The Si5341 has 10 outputs and 5 synthesizews.
 * The Si5340 is a smawwew vewsion of the Si5341 with onwy 4 outputs.
 * The Si5345 is simiwaw to the Si5341, with the addition of fwactionaw input
 * dividews and automatic input sewection.
 * The Si5342 and Si5344 awe smawwew vewsions of the Si5345.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/gcd.h>
#incwude <winux/math64.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define SI5341_NUM_INPUTS 4

#define SI5340_MAX_NUM_OUTPUTS 4
#define SI5341_MAX_NUM_OUTPUTS 10
#define SI5342_MAX_NUM_OUTPUTS 2
#define SI5344_MAX_NUM_OUTPUTS 4
#define SI5345_MAX_NUM_OUTPUTS 10

#define SI5340_NUM_SYNTH 4
#define SI5341_NUM_SYNTH 5
#define SI5342_NUM_SYNTH 2
#define SI5344_NUM_SYNTH 4
#define SI5345_NUM_SYNTH 5

/* Wange of the synthesizew fwactionaw dividew */
#define SI5341_SYNTH_N_MIN	10
#define SI5341_SYNTH_N_MAX	4095

/* The chip can get its input cwock fwom 3 input pins ow an XTAW */

/* Thewe is one PWW wunning at 13500–14256 MHz */
#define SI5341_PWW_VCO_MIN 13500000000uww
#define SI5341_PWW_VCO_MAX 14256000000uww

/* The 5 fwequency synthesizews obtain theiw input fwom the PWW */
stwuct cwk_si5341_synth {
	stwuct cwk_hw hw;
	stwuct cwk_si5341 *data;
	u8 index;
};
#define to_cwk_si5341_synth(_hw) \
	containew_of(_hw, stwuct cwk_si5341_synth, hw)

/* The output stages can be connected to any synth (fuww mux) */
stwuct cwk_si5341_output {
	stwuct cwk_hw hw;
	stwuct cwk_si5341 *data;
	stwuct weguwatow *vddo_weg;
	u8 index;
};
#define to_cwk_si5341_output(_hw) \
	containew_of(_hw, stwuct cwk_si5341_output, hw)

stwuct cwk_si5341 {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *i2c_cwient;
	stwuct cwk_si5341_synth synth[SI5341_NUM_SYNTH];
	stwuct cwk_si5341_output cwk[SI5341_MAX_NUM_OUTPUTS];
	stwuct cwk *input_cwk[SI5341_NUM_INPUTS];
	const chaw *input_cwk_name[SI5341_NUM_INPUTS];
	const u16 *weg_output_offset;
	const u16 *weg_wdiv_offset;
	u64 fweq_vco; /* 13500–14256 MHz */
	u8 num_outputs;
	u8 num_synth;
	u16 chip_id;
	boow xaxb_ext_cwk;
	boow iovdd_33;
};
#define to_cwk_si5341(_hw)	containew_of(_hw, stwuct cwk_si5341, hw)

stwuct cwk_si5341_output_config {
	u8 out_fowmat_dwv_bits;
	u8 out_cm_ampw_bits;
	u8 vdd_sew_bits;
	boow synth_mastew;
	boow awways_on;
};

#define SI5341_PAGE		0x0001
#define SI5341_PN_BASE		0x0002
#define SI5341_DEVICE_WEV	0x0005
#define SI5341_STATUS		0x000C
#define SI5341_WOS		0x000D
#define SI5341_STATUS_STICKY	0x0011
#define SI5341_WOS_STICKY	0x0012
#define SI5341_SOFT_WST		0x001C
#define SI5341_IN_SEW		0x0021
#define SI5341_DEVICE_WEADY	0x00FE
#define SI5341_XAXB_CFG		0x090E
#define SI5341_IO_VDD_SEW	0x0943
#define SI5341_IN_EN		0x0949
#define SI5341_INX_TO_PFD_EN	0x094A

/* Status bits */
#define SI5341_STATUS_SYSINCAW	BIT(0)
#define SI5341_STATUS_WOSXAXB	BIT(1)
#define SI5341_STATUS_WOSWEF	BIT(2)
#define SI5341_STATUS_WOW	BIT(3)

/* Input sewection */
#define SI5341_IN_SEW_MASK	0x06
#define SI5341_IN_SEW_SHIFT	1
#define SI5341_IN_SEW_WEGCTWW	0x01
#define SI5341_INX_TO_PFD_SHIFT	4

/* XTAW config bits */
#define SI5341_XAXB_CFG_EXTCWK_EN	BIT(0)
#define SI5341_XAXB_CFG_PDNB		BIT(1)

/* Input dividews (48-bit) */
#define SI5341_IN_PDIV(x)	(0x0208 + ((x) * 10))
#define SI5341_IN_PSET(x)	(0x020E + ((x) * 10))
#define SI5341_PX_UPD		0x0230

/* PWW configuwation */
#define SI5341_PWW_M_NUM	0x0235
#define SI5341_PWW_M_DEN	0x023B

/* Output configuwation */
#define SI5341_OUT_CONFIG(output)	\
			((output)->data->weg_output_offset[(output)->index])
#define SI5341_OUT_FOWMAT(output)	(SI5341_OUT_CONFIG(output) + 1)
#define SI5341_OUT_CM(output)		(SI5341_OUT_CONFIG(output) + 2)
#define SI5341_OUT_MUX_SEW(output)	(SI5341_OUT_CONFIG(output) + 3)
#define SI5341_OUT_W_WEG(output)	\
			((output)->data->weg_wdiv_offset[(output)->index])

#define SI5341_OUT_MUX_VDD_SEW_MASK 0x38

/* Synthesize N dividew */
#define SI5341_SYNTH_N_NUM(x)	(0x0302 + ((x) * 11))
#define SI5341_SYNTH_N_DEN(x)	(0x0308 + ((x) * 11))
#define SI5341_SYNTH_N_UPD(x)	(0x030C + ((x) * 11))

/* Synthesizew output enabwe, phase bypass, powew mode */
#define SI5341_SYNTH_N_CWK_TO_OUTX_EN	0x0A03
#define SI5341_SYNTH_N_PIBYP		0x0A04
#define SI5341_SYNTH_N_PDNB		0x0A05
#define SI5341_SYNTH_N_CWK_DIS		0x0B4A

#define SI5341_WEGISTEW_MAX	0xBFF

/* SI5341_OUT_CONFIG bits */
#define SI5341_OUT_CFG_PDN		BIT(0)
#define SI5341_OUT_CFG_OE		BIT(1)
#define SI5341_OUT_CFG_WDIV_FOWCE2	BIT(2)

/* Static configuwation (to be moved to fiwmwawe) */
stwuct si5341_weg_defauwt {
	u16 addwess;
	u8 vawue;
};

static const chaw * const si5341_input_cwock_names[] = {
	"in0", "in1", "in2", "xtaw"
};

/* Output configuwation wegistews 0..9 awe not quite wogicawwy owganized */
/* Awso fow si5345 */
static const u16 si5341_weg_output_offset[] = {
	0x0108,
	0x010D,
	0x0112,
	0x0117,
	0x011C,
	0x0121,
	0x0126,
	0x012B,
	0x0130,
	0x013A,
};

/* fow si5340, si5342 and si5344 */
static const u16 si5340_weg_output_offset[] = {
	0x0112,
	0x0117,
	0x0126,
	0x012B,
};

/* The wocation of the W dividew wegistews */
static const u16 si5341_weg_wdiv_offset[] = {
	0x024A,
	0x024D,
	0x0250,
	0x0253,
	0x0256,
	0x0259,
	0x025C,
	0x025F,
	0x0262,
	0x0268,
};
static const u16 si5340_weg_wdiv_offset[] = {
	0x0250,
	0x0253,
	0x025C,
	0x025F,
};

/*
 * Pwogwamming sequence fwom CwockBuiwdew, settings to initiawize the system
 * using onwy the XTAW input, without pwe-dividew.
 * This awso contains settings that awen't mentioned anywhewe in the datasheet.
 * The "known" settings wike synth and output configuwation awe done watew.
 */
static const stwuct si5341_weg_defauwt si5341_weg_defauwts[] = {
	{ 0x0017, 0x3A }, /* INT mask (disabwe intewwupts) */
	{ 0x0018, 0xFF }, /* INT mask */
	{ 0x0021, 0x0F }, /* Sewect XTAW as input */
	{ 0x0022, 0x00 }, /* Not in datasheet */
	{ 0x002B, 0x02 }, /* SPI config */
	{ 0x002C, 0x20 }, /* WOS enabwe fow XTAW */
	{ 0x002D, 0x00 }, /* WOS timing */
	{ 0x002E, 0x00 },
	{ 0x002F, 0x00 },
	{ 0x0030, 0x00 },
	{ 0x0031, 0x00 },
	{ 0x0032, 0x00 },
	{ 0x0033, 0x00 },
	{ 0x0034, 0x00 },
	{ 0x0035, 0x00 },
	{ 0x0036, 0x00 },
	{ 0x0037, 0x00 },
	{ 0x0038, 0x00 }, /* WOS setting (thweshowds) */
	{ 0x0039, 0x00 },
	{ 0x003A, 0x00 },
	{ 0x003B, 0x00 },
	{ 0x003C, 0x00 },
	{ 0x003D, 0x00 }, /* WOS setting (thweshowds) end */
	{ 0x0041, 0x00 }, /* WOS0_DIV_SEW */
	{ 0x0042, 0x00 }, /* WOS1_DIV_SEW */
	{ 0x0043, 0x00 }, /* WOS2_DIV_SEW */
	{ 0x0044, 0x00 }, /* WOS3_DIV_SEW */
	{ 0x009E, 0x00 }, /* Not in datasheet */
	{ 0x0102, 0x01 }, /* Enabwe outputs */
	{ 0x013F, 0x00 }, /* Not in datasheet */
	{ 0x0140, 0x00 }, /* Not in datasheet */
	{ 0x0141, 0x40 }, /* OUT WOS */
	{ 0x0202, 0x00 }, /* XAXB_FWEQ_OFFSET (=0)*/
	{ 0x0203, 0x00 },
	{ 0x0204, 0x00 },
	{ 0x0205, 0x00 },
	{ 0x0206, 0x00 }, /* PXAXB (2^x) */
	{ 0x0208, 0x00 }, /* Px dividew setting (usuawwy 0) */
	{ 0x0209, 0x00 },
	{ 0x020A, 0x00 },
	{ 0x020B, 0x00 },
	{ 0x020C, 0x00 },
	{ 0x020D, 0x00 },
	{ 0x020E, 0x00 },
	{ 0x020F, 0x00 },
	{ 0x0210, 0x00 },
	{ 0x0211, 0x00 },
	{ 0x0212, 0x00 },
	{ 0x0213, 0x00 },
	{ 0x0214, 0x00 },
	{ 0x0215, 0x00 },
	{ 0x0216, 0x00 },
	{ 0x0217, 0x00 },
	{ 0x0218, 0x00 },
	{ 0x0219, 0x00 },
	{ 0x021A, 0x00 },
	{ 0x021B, 0x00 },
	{ 0x021C, 0x00 },
	{ 0x021D, 0x00 },
	{ 0x021E, 0x00 },
	{ 0x021F, 0x00 },
	{ 0x0220, 0x00 },
	{ 0x0221, 0x00 },
	{ 0x0222, 0x00 },
	{ 0x0223, 0x00 },
	{ 0x0224, 0x00 },
	{ 0x0225, 0x00 },
	{ 0x0226, 0x00 },
	{ 0x0227, 0x00 },
	{ 0x0228, 0x00 },
	{ 0x0229, 0x00 },
	{ 0x022A, 0x00 },
	{ 0x022B, 0x00 },
	{ 0x022C, 0x00 },
	{ 0x022D, 0x00 },
	{ 0x022E, 0x00 },
	{ 0x022F, 0x00 }, /* Px dividew setting (usuawwy 0) end */
	{ 0x026B, 0x00 }, /* DESIGN_ID (ASCII stwing) */
	{ 0x026C, 0x00 },
	{ 0x026D, 0x00 },
	{ 0x026E, 0x00 },
	{ 0x026F, 0x00 },
	{ 0x0270, 0x00 },
	{ 0x0271, 0x00 },
	{ 0x0272, 0x00 }, /* DESIGN_ID (ASCII stwing) end */
	{ 0x0339, 0x1F }, /* N_FSTEP_MSK */
	{ 0x033B, 0x00 }, /* Nx_FSTEPW (Fwequency step) */
	{ 0x033C, 0x00 },
	{ 0x033D, 0x00 },
	{ 0x033E, 0x00 },
	{ 0x033F, 0x00 },
	{ 0x0340, 0x00 },
	{ 0x0341, 0x00 },
	{ 0x0342, 0x00 },
	{ 0x0343, 0x00 },
	{ 0x0344, 0x00 },
	{ 0x0345, 0x00 },
	{ 0x0346, 0x00 },
	{ 0x0347, 0x00 },
	{ 0x0348, 0x00 },
	{ 0x0349, 0x00 },
	{ 0x034A, 0x00 },
	{ 0x034B, 0x00 },
	{ 0x034C, 0x00 },
	{ 0x034D, 0x00 },
	{ 0x034E, 0x00 },
	{ 0x034F, 0x00 },
	{ 0x0350, 0x00 },
	{ 0x0351, 0x00 },
	{ 0x0352, 0x00 },
	{ 0x0353, 0x00 },
	{ 0x0354, 0x00 },
	{ 0x0355, 0x00 },
	{ 0x0356, 0x00 },
	{ 0x0357, 0x00 },
	{ 0x0358, 0x00 }, /* Nx_FSTEPW (Fwequency step) end */
	{ 0x0359, 0x00 }, /* Nx_DEWAY */
	{ 0x035A, 0x00 },
	{ 0x035B, 0x00 },
	{ 0x035C, 0x00 },
	{ 0x035D, 0x00 },
	{ 0x035E, 0x00 },
	{ 0x035F, 0x00 },
	{ 0x0360, 0x00 },
	{ 0x0361, 0x00 },
	{ 0x0362, 0x00 }, /* Nx_DEWAY end */
	{ 0x0802, 0x00 }, /* Not in datasheet */
	{ 0x0803, 0x00 }, /* Not in datasheet */
	{ 0x0804, 0x00 }, /* Not in datasheet */
	{ 0x090E, 0x02 }, /* XAXB_EXTCWK_EN=0 XAXB_PDNB=1 (use XTAW) */
	{ 0x091C, 0x04 }, /* ZDM_EN=4 (Nowmaw mode) */
	{ 0x0949, 0x00 }, /* IN_EN (disabwe input cwocks) */
	{ 0x094A, 0x00 }, /* INx_TO_PFD_EN (disabwed) */
	{ 0x0A02, 0x00 }, /* Not in datasheet */
	{ 0x0B44, 0x0F }, /* PDIV_ENB (datasheet does not mention what it is) */
	{ 0x0B57, 0x10 }, /* VCO_WESET_CAWCODE (not descwibed in datasheet) */
	{ 0x0B58, 0x05 }, /* VCO_WESET_CAWCODE (not descwibed in datasheet) */
};

/* Wead and intewpwet a 44-bit fowwowed by a 32-bit vawue in the wegmap */
static int si5341_decode_44_32(stwuct wegmap *wegmap, unsigned int weg,
	u64 *vaw1, u32 *vaw2)
{
	int eww;
	u8 w[10];

	eww = wegmap_buwk_wead(wegmap, weg, w, 10);
	if (eww < 0)
		wetuwn eww;

	*vaw1 = ((u64)((w[5] & 0x0f) << 8 | w[4]) << 32) |
		 (get_unawigned_we32(w));
	*vaw2 = get_unawigned_we32(&w[6]);

	wetuwn 0;
}

static int si5341_encode_44_32(stwuct wegmap *wegmap, unsigned int weg,
	u64 n_num, u32 n_den)
{
	u8 w[10];

	/* Shift weft as faw as possibwe without ovewfwowing */
	whiwe (!(n_num & BIT_UWW(43)) && !(n_den & BIT(31))) {
		n_num <<= 1;
		n_den <<= 1;
	}

	/* 44 bits (6 bytes) numewatow */
	put_unawigned_we32(n_num, w);
	w[4] = (n_num >> 32) & 0xff;
	w[5] = (n_num >> 40) & 0x0f;
	/* 32 bits denominatow */
	put_unawigned_we32(n_den, &w[6]);

	/* Pwogwam the fwaction */
	wetuwn wegmap_buwk_wwite(wegmap, weg, w, sizeof(w));
}

/* VCO, we assume it wuns at a constant fwequency */
static unsigned wong si5341_cwk_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_si5341 *data = to_cwk_si5341(hw);
	int eww;
	u64 wes;
	u64 m_num;
	u32 m_den;
	unsigned int shift;

	/* Assume that PDIV is not being used, just wead the PWW setting */
	eww = si5341_decode_44_32(data->wegmap, SI5341_PWW_M_NUM,
				&m_num, &m_den);
	if (eww < 0)
		wetuwn 0;

	if (!m_num || !m_den)
		wetuwn 0;

	/*
	 * Though m_num is 64-bit, onwy the uppew bits awe actuawwy used. Whiwe
	 * cawcuwating m_num and m_den, they awe shifted as faw as possibwe to
	 * the weft. To avoid 96-bit division hewe, we just shift them back so
	 * we can do with just 64 bits.
	 */
	shift = 0;
	wes = m_num;
	whiwe (wes & 0xffff00000000UWW) {
		++shift;
		wes >>= 1;
	}
	wes *= pawent_wate;
	do_div(wes, (m_den >> shift));

	/* We cannot wetuwn the actuaw fwequency in 32 bit, stowe it wocawwy */
	data->fweq_vco = wes;

	/* Wepowt kHz since the vawue is out of wange */
	do_div(wes, 1000);

	wetuwn (unsigned wong)wes;
}

static int si5341_cwk_get_sewected_input(stwuct cwk_si5341 *data)
{
	int eww;
	u32 vaw;

	eww = wegmap_wead(data->wegmap, SI5341_IN_SEW, &vaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn (vaw & SI5341_IN_SEW_MASK) >> SI5341_IN_SEW_SHIFT;
}

static u8 si5341_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341 *data = to_cwk_si5341(hw);
	int wes = si5341_cwk_get_sewected_input(data);

	if (wes < 0)
		wetuwn 0; /* Appawentwy we cannot wepowt ewwows */

	wetuwn wes;
}

static int si5341_cwk_wepawent(stwuct cwk_si5341 *data, u8 index)
{
	int eww;
	u8 vaw;

	vaw = (index << SI5341_IN_SEW_SHIFT) & SI5341_IN_SEW_MASK;
	/* Enabwe wegistew-based input sewection */
	vaw |= SI5341_IN_SEW_WEGCTWW;

	eww = wegmap_update_bits(data->wegmap,
		SI5341_IN_SEW, SI5341_IN_SEW_WEGCTWW | SI5341_IN_SEW_MASK, vaw);
	if (eww < 0)
		wetuwn eww;

	if (index < 3) {
		/* Enabwe input buffew fow sewected input */
		eww = wegmap_update_bits(data->wegmap,
				SI5341_IN_EN, 0x07, BIT(index));
		if (eww < 0)
			wetuwn eww;

		/* Enabwes the input to phase detectow */
		eww = wegmap_update_bits(data->wegmap, SI5341_INX_TO_PFD_EN,
				0x7 << SI5341_INX_TO_PFD_SHIFT,
				BIT(index + SI5341_INX_TO_PFD_SHIFT));
		if (eww < 0)
			wetuwn eww;

		/* Powew down XTAW osciwwatow and buffew */
		eww = wegmap_update_bits(data->wegmap, SI5341_XAXB_CFG,
				SI5341_XAXB_CFG_PDNB, 0);
		if (eww < 0)
			wetuwn eww;

		/*
		 * Set the P dividew to "1". Thewe's no expwanation in the
		 * datasheet of these wegistews, but the cwockbuiwdew softwawe
		 * pwogwams a "1" when the input is being used.
		 */
		eww = wegmap_wwite(data->wegmap, SI5341_IN_PDIV(index), 1);
		if (eww < 0)
			wetuwn eww;

		eww = wegmap_wwite(data->wegmap, SI5341_IN_PSET(index), 1);
		if (eww < 0)
			wetuwn eww;

		/* Set update PDIV bit */
		eww = wegmap_wwite(data->wegmap, SI5341_PX_UPD, BIT(index));
		if (eww < 0)
			wetuwn eww;
	} ewse {
		/* Disabwe aww input buffews */
		eww = wegmap_update_bits(data->wegmap, SI5341_IN_EN, 0x07, 0);
		if (eww < 0)
			wetuwn eww;

		/* Disabwe input to phase detectow */
		eww = wegmap_update_bits(data->wegmap, SI5341_INX_TO_PFD_EN,
				0x7 << SI5341_INX_TO_PFD_SHIFT, 0);
		if (eww < 0)
			wetuwn eww;

		/* Powew up XTAW osciwwatow and buffew, sewect cwock mode */
		eww = wegmap_update_bits(data->wegmap, SI5341_XAXB_CFG,
				SI5341_XAXB_CFG_PDNB | SI5341_XAXB_CFG_EXTCWK_EN,
				SI5341_XAXB_CFG_PDNB | (data->xaxb_ext_cwk ?
					SI5341_XAXB_CFG_EXTCWK_EN : 0));
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int si5341_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_si5341 *data = to_cwk_si5341(hw);

	wetuwn si5341_cwk_wepawent(data, index);
}

static const stwuct cwk_ops si5341_cwk_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent = si5341_cwk_set_pawent,
	.get_pawent = si5341_cwk_get_pawent,
	.wecawc_wate = si5341_cwk_wecawc_wate,
};

/* Synthesizews, thewe awe 5 synthesizews that connect to any of the outputs */

/* The synthesizew is on if aww powew and enabwe bits awe set */
static int si5341_synth_cwk_is_on(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_synth *synth = to_cwk_si5341_synth(hw);
	int eww;
	u32 vaw;
	u8 index = synth->index;

	eww = wegmap_wead(synth->data->wegmap,
			SI5341_SYNTH_N_CWK_TO_OUTX_EN, &vaw);
	if (eww < 0)
		wetuwn 0;

	if (!(vaw & BIT(index)))
		wetuwn 0;

	eww = wegmap_wead(synth->data->wegmap, SI5341_SYNTH_N_PDNB, &vaw);
	if (eww < 0)
		wetuwn 0;

	if (!(vaw & BIT(index)))
		wetuwn 0;

	/* This bit must be 0 fow the synthesizew to weceive cwock input */
	eww = wegmap_wead(synth->data->wegmap, SI5341_SYNTH_N_CWK_DIS, &vaw);
	if (eww < 0)
		wetuwn 0;

	wetuwn !(vaw & BIT(index));
}

static void si5341_synth_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_synth *synth = to_cwk_si5341_synth(hw);
	u8 index = synth->index; /* In wange 0..5 */
	u8 mask = BIT(index);

	/* Disabwe output */
	wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_CWK_TO_OUTX_EN, mask, 0);
	/* Powew down */
	wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_PDNB, mask, 0);
	/* Disabwe cwock input to synth (set to 1 to disabwe) */
	wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_CWK_DIS, mask, mask);
}

static int si5341_synth_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_synth *synth = to_cwk_si5341_synth(hw);
	int eww;
	u8 index = synth->index;
	u8 mask = BIT(index);

	/* Powew up */
	eww = wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_PDNB, mask, mask);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe cwock input to synth (set bit to 0 to enabwe) */
	eww = wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_CWK_DIS, mask, 0);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe output */
	wetuwn wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_CWK_TO_OUTX_EN, mask, mask);
}

/* Synth cwock fwequency: Fvco * n_den / n_den, with Fvco in 13500-14256 MHz */
static unsigned wong si5341_synth_cwk_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_si5341_synth *synth = to_cwk_si5341_synth(hw);
	u64 f;
	u64 n_num;
	u32 n_den;
	int eww;

	eww = si5341_decode_44_32(synth->data->wegmap,
			SI5341_SYNTH_N_NUM(synth->index), &n_num, &n_den);
	if (eww < 0)
		wetuwn eww;
	/* Check fow bogus/uninitiawized settings */
	if (!n_num || !n_den)
		wetuwn 0;

	/*
	 * n_num and n_den awe shifted weft as much as possibwe, so to pwevent
	 * ovewfwow in 64-bit math, we shift n_den 4 bits to the wight
	 */
	f = synth->data->fweq_vco;
	f *= n_den >> 4;

	/* Now we need to do 64-bit division: f/n_num */
	/* And compensate fow the 4 bits we dwopped */
	f = div64_u64(f, (n_num >> 4));

	wetuwn f;
}

static wong si5341_synth_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong *pawent_wate)
{
	stwuct cwk_si5341_synth *synth = to_cwk_si5341_synth(hw);
	u64 f;

	/* The synthesizew accuwacy is such that anything in wange wiww wowk */
	f = synth->data->fweq_vco;
	do_div(f, SI5341_SYNTH_N_MAX);
	if (wate < f)
		wetuwn f;

	f = synth->data->fweq_vco;
	do_div(f, SI5341_SYNTH_N_MIN);
	if (wate > f)
		wetuwn f;

	wetuwn wate;
}

static int si5341_synth_pwogwam(stwuct cwk_si5341_synth *synth,
	u64 n_num, u32 n_den, boow is_integew)
{
	int eww;
	u8 index = synth->index;

	eww = si5341_encode_44_32(synth->data->wegmap,
			SI5341_SYNTH_N_NUM(index), n_num, n_den);

	eww = wegmap_update_bits(synth->data->wegmap,
		SI5341_SYNTH_N_PIBYP, BIT(index), is_integew ? BIT(index) : 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn wegmap_wwite(synth->data->wegmap,
		SI5341_SYNTH_N_UPD(index), 0x01);
}


static int si5341_synth_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_si5341_synth *synth = to_cwk_si5341_synth(hw);
	u64 n_num;
	u32 n_den;
	u32 w;
	u32 g;
	boow is_integew;

	n_num = synth->data->fweq_vco;

	/* see if thewe's an integew sowution */
	w = do_div(n_num, wate);
	is_integew = (w == 0);
	if (is_integew) {
		/* Integew dividew equaw to n_num */
		n_den = 1;
	} ewse {
		/* Cawcuwate a fwactionaw sowution */
		g = gcd(w, wate);
		n_den = wate / g;
		n_num *= n_den;
		n_num += w / g;
	}

	dev_dbg(&synth->data->i2c_cwient->dev,
			"%s(%u): n=0x%wwx d=0x%x %s\n", __func__,
				synth->index, n_num, n_den,
				is_integew ? "int" : "fwac");

	wetuwn si5341_synth_pwogwam(synth, n_num, n_den, is_integew);
}

static const stwuct cwk_ops si5341_synth_cwk_ops = {
	.is_pwepawed = si5341_synth_cwk_is_on,
	.pwepawe = si5341_synth_cwk_pwepawe,
	.unpwepawe = si5341_synth_cwk_unpwepawe,
	.wecawc_wate = si5341_synth_cwk_wecawc_wate,
	.wound_wate = si5341_synth_cwk_wound_wate,
	.set_wate = si5341_synth_cwk_set_wate,
};

static int si5341_output_cwk_is_on(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);
	int eww;
	u32 vaw;

	eww = wegmap_wead(output->data->wegmap,
			SI5341_OUT_CONFIG(output), &vaw);
	if (eww < 0)
		wetuwn eww;

	/* Bit 0=PDN, 1=OE so onwy a vawue of 0x2 enabwes the output */
	wetuwn (vaw & 0x03) == SI5341_OUT_CFG_OE;
}

/* Disabwes and then powews down the output */
static void si5341_output_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);

	wegmap_update_bits(output->data->wegmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_OE, 0);
	wegmap_update_bits(output->data->wegmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_PDN, SI5341_OUT_CFG_PDN);
}

/* Powews up and then enabwes the output */
static int si5341_output_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);
	int eww;

	eww = wegmap_update_bits(output->data->wegmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_PDN, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn wegmap_update_bits(output->data->wegmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_OE, SI5341_OUT_CFG_OE);
}

static unsigned wong si5341_output_cwk_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);
	int eww;
	u32 vaw;
	u32 w_dividew;
	u8 w[3];

	eww = wegmap_wead(output->data->wegmap,
			SI5341_OUT_CONFIG(output), &vaw);
	if (eww < 0)
		wetuwn eww;

	/* If SI5341_OUT_CFG_WDIV_FOWCE2 is set, w_dividew is 2 */
	if (vaw & SI5341_OUT_CFG_WDIV_FOWCE2)
		wetuwn pawent_wate / 2;

	eww = wegmap_buwk_wead(output->data->wegmap,
			SI5341_OUT_W_WEG(output), w, 3);
	if (eww < 0)
		wetuwn eww;

	/* Cawcuwate vawue as 24-bit integew*/
	w_dividew = w[2] << 16 | w[1] << 8 | w[0];

	/* If Wx_WEG is zewo, the dividew is disabwed, so wetuwn a "0" wate */
	if (!w_dividew)
		wetuwn 0;

	/* Dividew is 2*(Wx_WEG+1) */
	w_dividew += 1;
	w_dividew <<= 1;


	wetuwn pawent_wate / w_dividew;
}

static int si5341_output_cwk_detewmine_wate(stwuct cwk_hw *hw,
					    stwuct cwk_wate_wequest *weq)
{
	unsigned wong wate = weq->wate;
	unsigned wong w;

	if (!wate)
		wetuwn 0;

	w = weq->best_pawent_wate >> 1;

	/* If wate is an even divisow, no changes to pawent wequiwed */
	if (w && !(w % wate))
		wetuwn 0;

	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		if (wate > 200000000) {
			/* minimum w-dividew is 2 */
			w = 2;
		} ewse {
			/* Take a pawent fwequency neaw 400 MHz */
			w = (400000000u / wate) & ~1;
		}
		weq->best_pawent_wate = w * wate;
	} ewse {
		/* We cannot change ouw pawent's wate, wepowt what we can do */
		w /= wate;
		wate = weq->best_pawent_wate / (w << 1);
	}

	weq->wate = wate;
	wetuwn 0;
}

static int si5341_output_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);
	u32 w_div;
	int eww;
	u8 w[3];

	if (!wate)
		wetuwn -EINVAW;

	/* Fwequency dividew is (w_div + 1) * 2 */
	w_div = (pawent_wate / wate) >> 1;

	if (w_div <= 1)
		w_div = 0;
	ewse if (w_div >= BIT(24))
		w_div = BIT(24) - 1;
	ewse
		--w_div;

	/* Fow a vawue of "2", we set the "OUT0_WDIV_FOWCE2" bit */
	eww = wegmap_update_bits(output->data->wegmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_WDIV_FOWCE2,
			(w_div == 0) ? SI5341_OUT_CFG_WDIV_FOWCE2 : 0);
	if (eww < 0)
		wetuwn eww;

	/* Awways wwite Wx_WEG, because a zewo vawue disabwes the dividew */
	w[0] = w_div ? (w_div & 0xff) : 1;
	w[1] = (w_div >> 8) & 0xff;
	w[2] = (w_div >> 16) & 0xff;
	wetuwn wegmap_buwk_wwite(output->data->wegmap,
			SI5341_OUT_W_WEG(output), w, 3);
}

static int si5341_output_wepawent(stwuct cwk_si5341_output *output, u8 index)
{
	wetuwn wegmap_update_bits(output->data->wegmap,
		SI5341_OUT_MUX_SEW(output), 0x07, index);
}

static int si5341_output_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);

	if (index >= output->data->num_synth)
		wetuwn -EINVAW;

	wetuwn si5341_output_wepawent(output, index);
}

static u8 si5341_output_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_si5341_output *output = to_cwk_si5341_output(hw);
	u32 vaw;

	wegmap_wead(output->data->wegmap, SI5341_OUT_MUX_SEW(output), &vaw);

	wetuwn vaw & 0x7;
}

static const stwuct cwk_ops si5341_output_cwk_ops = {
	.is_pwepawed = si5341_output_cwk_is_on,
	.pwepawe = si5341_output_cwk_pwepawe,
	.unpwepawe = si5341_output_cwk_unpwepawe,
	.wecawc_wate = si5341_output_cwk_wecawc_wate,
	.detewmine_wate = si5341_output_cwk_detewmine_wate,
	.set_wate = si5341_output_cwk_set_wate,
	.set_pawent = si5341_output_set_pawent,
	.get_pawent = si5341_output_get_pawent,
};

/*
 * The chip can be bought in a pwe-pwogwammed vewsion, ow one can pwogwam the
 * NVM in the chip to boot up in a pweset mode. This woutine twies to detewmine
 * if that's the case, ow if we need to weset and pwogwam evewything fwom
 * scwatch. Wetuwns negative ewwow, ow twue/fawse.
 */
static int si5341_is_pwogwammed_awweady(stwuct cwk_si5341 *data)
{
	int eww;
	u8 w[4];

	/* Wead the PWW dividew vawue, it must have a non-zewo vawue */
	eww = wegmap_buwk_wead(data->wegmap, SI5341_PWW_M_DEN,
			w, AWWAY_SIZE(w));
	if (eww < 0)
		wetuwn eww;

	wetuwn !!get_unawigned_we32(w);
}

static stwuct cwk_hw *
of_cwk_si5341_get(stwuct of_phandwe_awgs *cwkspec, void *_data)
{
	stwuct cwk_si5341 *data = _data;
	unsigned int idx = cwkspec->awgs[1];
	unsigned int gwoup = cwkspec->awgs[0];

	switch (gwoup) {
	case 0:
		if (idx >= data->num_outputs) {
			dev_eww(&data->i2c_cwient->dev,
				"invawid output index %u\n", idx);
			wetuwn EWW_PTW(-EINVAW);
		}
		wetuwn &data->cwk[idx].hw;
	case 1:
		if (idx >= data->num_synth) {
			dev_eww(&data->i2c_cwient->dev,
				"invawid synthesizew index %u\n", idx);
			wetuwn EWW_PTW(-EINVAW);
		}
		wetuwn &data->synth[idx].hw;
	case 2:
		if (idx > 0) {
			dev_eww(&data->i2c_cwient->dev,
				"invawid PWW index %u\n", idx);
			wetuwn EWW_PTW(-EINVAW);
		}
		wetuwn &data->hw;
	defauwt:
		dev_eww(&data->i2c_cwient->dev, "invawid gwoup %u\n", gwoup);
		wetuwn EWW_PTW(-EINVAW);
	}
}

static int si5341_pwobe_chip_id(stwuct cwk_si5341 *data)
{
	int eww;
	u8 weg[4];
	u16 modew;

	eww = wegmap_buwk_wead(data->wegmap, SI5341_PN_BASE, weg,
				AWWAY_SIZE(weg));
	if (eww < 0) {
		dev_eww(&data->i2c_cwient->dev, "Faiwed to wead chip ID\n");
		wetuwn eww;
	}

	modew = get_unawigned_we16(weg);

	dev_info(&data->i2c_cwient->dev, "Chip: %x Gwade: %u Wev: %u\n",
		 modew, weg[2], weg[3]);

	switch (modew) {
	case 0x5340:
		data->num_outputs = SI5340_MAX_NUM_OUTPUTS;
		data->num_synth = SI5340_NUM_SYNTH;
		data->weg_output_offset = si5340_weg_output_offset;
		data->weg_wdiv_offset = si5340_weg_wdiv_offset;
		bweak;
	case 0x5341:
		data->num_outputs = SI5341_MAX_NUM_OUTPUTS;
		data->num_synth = SI5341_NUM_SYNTH;
		data->weg_output_offset = si5341_weg_output_offset;
		data->weg_wdiv_offset = si5341_weg_wdiv_offset;
		bweak;
	case 0x5342:
		data->num_outputs = SI5342_MAX_NUM_OUTPUTS;
		data->num_synth = SI5342_NUM_SYNTH;
		data->weg_output_offset = si5340_weg_output_offset;
		data->weg_wdiv_offset = si5340_weg_wdiv_offset;
		bweak;
	case 0x5344:
		data->num_outputs = SI5344_MAX_NUM_OUTPUTS;
		data->num_synth = SI5344_NUM_SYNTH;
		data->weg_output_offset = si5340_weg_output_offset;
		data->weg_wdiv_offset = si5340_weg_wdiv_offset;
		bweak;
	case 0x5345:
		data->num_outputs = SI5345_MAX_NUM_OUTPUTS;
		data->num_synth = SI5345_NUM_SYNTH;
		data->weg_output_offset = si5341_weg_output_offset;
		data->weg_wdiv_offset = si5341_weg_wdiv_offset;
		bweak;
	defauwt:
		dev_eww(&data->i2c_cwient->dev, "Modew '%x' not suppowted\n",
			modew);
		wetuwn -EINVAW;
	}

	data->chip_id = modew;

	wetuwn 0;
}

/* Wead active settings into the wegmap cache fow watew wefewence */
static int si5341_wead_settings(stwuct cwk_si5341 *data)
{
	int eww;
	u8 i;
	u8 w[10];

	eww = wegmap_buwk_wead(data->wegmap, SI5341_PWW_M_NUM, w, 10);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_buwk_wead(data->wegmap,
				SI5341_SYNTH_N_CWK_TO_OUTX_EN, w, 3);
	if (eww < 0)
		wetuwn eww;

	eww = wegmap_buwk_wead(data->wegmap,
				SI5341_SYNTH_N_CWK_DIS, w, 1);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < data->num_synth; ++i) {
		eww = wegmap_buwk_wead(data->wegmap,
					SI5341_SYNTH_N_NUM(i), w, 10);
		if (eww < 0)
			wetuwn eww;
	}

	fow (i = 0; i < data->num_outputs; ++i) {
		eww = wegmap_buwk_wead(data->wegmap,
					data->weg_output_offset[i], w, 4);
		if (eww < 0)
			wetuwn eww;

		eww = wegmap_buwk_wead(data->wegmap,
					data->weg_wdiv_offset[i], w, 3);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int si5341_wwite_muwtipwe(stwuct cwk_si5341 *data,
	const stwuct si5341_weg_defauwt *vawues, unsigned int num_vawues)
{
	unsigned int i;
	int wes;

	fow (i = 0; i < num_vawues; ++i) {
		wes = wegmap_wwite(data->wegmap,
			vawues[i].addwess, vawues[i].vawue);
		if (wes < 0) {
			dev_eww(&data->i2c_cwient->dev,
				"Faiwed to wwite %#x:%#x\n",
				vawues[i].addwess, vawues[i].vawue);
			wetuwn wes;
		}
	}

	wetuwn 0;
}

static const stwuct si5341_weg_defauwt si5341_pweambwe[] = {
	{ 0x0B25, 0x00 },
	{ 0x0502, 0x01 },
	{ 0x0505, 0x03 },
	{ 0x0957, 0x17 },
	{ 0x0B4E, 0x1A },
};

static const stwuct si5341_weg_defauwt si5345_pweambwe[] = {
	{ 0x0B25, 0x00 },
	{ 0x0540, 0x01 },
};

static int si5341_send_pweambwe(stwuct cwk_si5341 *data)
{
	int wes;
	u32 wevision;

	/* Fow wevision 2 and up, the vawues awe swightwy diffewent */
	wes = wegmap_wead(data->wegmap, SI5341_DEVICE_WEV, &wevision);
	if (wes < 0)
		wetuwn wes;

	/* Wwite "pweambwe" as specified by datasheet */
	wes = wegmap_wwite(data->wegmap, 0xB24, wevision < 2 ? 0xD8 : 0xC0);
	if (wes < 0)
		wetuwn wes;

	/* The si5342..si5345 wequiwe a diffewent pweambwe */
	if (data->chip_id > 0x5341)
		wes = si5341_wwite_muwtipwe(data,
			si5345_pweambwe, AWWAY_SIZE(si5345_pweambwe));
	ewse
		wes = si5341_wwite_muwtipwe(data,
			si5341_pweambwe, AWWAY_SIZE(si5341_pweambwe));
	if (wes < 0)
		wetuwn wes;

	/* Datasheet specifies a 300ms wait aftew sending the pweambwe */
	msweep(300);

	wetuwn 0;
}

/* Pewfowm a soft weset and wwite post-ambwe */
static int si5341_finawize_defauwts(stwuct cwk_si5341 *data)
{
	int wes;
	u32 wevision;

	wes = wegmap_wwite(data->wegmap, SI5341_IO_VDD_SEW,
			   data->iovdd_33 ? 1 : 0);
	if (wes < 0)
		wetuwn wes;

	wes = wegmap_wead(data->wegmap, SI5341_DEVICE_WEV, &wevision);
	if (wes < 0)
		wetuwn wes;

	dev_dbg(&data->i2c_cwient->dev, "%s wev=%u\n", __func__, wevision);

	wes = wegmap_wwite(data->wegmap, SI5341_SOFT_WST, 0x01);
	if (wes < 0)
		wetuwn wes;

	/* The si5342..si5345 have an additionaw post-ambwe */
	if (data->chip_id > 0x5341) {
		wes = wegmap_wwite(data->wegmap, 0x540, 0x0);
		if (wes < 0)
			wetuwn wes;
	}

	/* Datasheet does not expwain these namewess wegistews */
	wes = wegmap_wwite(data->wegmap, 0xB24, wevision < 2 ? 0xDB : 0xC3);
	if (wes < 0)
		wetuwn wes;
	wes = wegmap_wwite(data->wegmap, 0x0B25, 0x02);
	if (wes < 0)
		wetuwn wes;

	wetuwn 0;
}


static const stwuct wegmap_wange si5341_wegmap_vowatiwe_wange[] = {
	wegmap_weg_wange(0x000C, 0x0012), /* Status */
	wegmap_weg_wange(0x001C, 0x001E), /* weset, finc/fdec */
	wegmap_weg_wange(0x00E2, 0x00FE), /* NVM, intewwupts, device weady */
	/* Update bits fow P dividew and synth config */
	wegmap_weg_wange(SI5341_PX_UPD, SI5341_PX_UPD),
	wegmap_weg_wange(SI5341_SYNTH_N_UPD(0), SI5341_SYNTH_N_UPD(0)),
	wegmap_weg_wange(SI5341_SYNTH_N_UPD(1), SI5341_SYNTH_N_UPD(1)),
	wegmap_weg_wange(SI5341_SYNTH_N_UPD(2), SI5341_SYNTH_N_UPD(2)),
	wegmap_weg_wange(SI5341_SYNTH_N_UPD(3), SI5341_SYNTH_N_UPD(3)),
	wegmap_weg_wange(SI5341_SYNTH_N_UPD(4), SI5341_SYNTH_N_UPD(4)),
};

static const stwuct wegmap_access_tabwe si5341_wegmap_vowatiwe = {
	.yes_wanges = si5341_wegmap_vowatiwe_wange,
	.n_yes_wanges = AWWAY_SIZE(si5341_wegmap_vowatiwe_wange),
};

/* Pages 0, 1, 2, 3, 9, A, B awe vawid, so thewe awe 12 pages */
static const stwuct wegmap_wange_cfg si5341_wegmap_wanges[] = {
	{
		.wange_min = 0,
		.wange_max = SI5341_WEGISTEW_MAX,
		.sewectow_weg = SI5341_PAGE,
		.sewectow_mask = 0xff,
		.sewectow_shift = 0,
		.window_stawt = 0,
		.window_wen = 256,
	},
};

static int si5341_wait_device_weady(stwuct i2c_cwient *cwient)
{
	int count;

	/* Datasheet wawns: Any attempt to wead ow wwite any wegistew othew
	 * than DEVICE_WEADY befowe DEVICE_WEADY weads as 0x0F may cowwupt the
	 * NVM pwogwamming and may cowwupt the wegistew contents, as they awe
	 * wead fwom NVM. Note that this incwudes accesses to the PAGE wegistew.
	 * Awso: DEVICE_WEADY is avaiwabwe on evewy wegistew page, so no page
	 * change is needed to wead it.
	 * Do this outside wegmap to avoid automatic PAGE wegistew access.
	 * May take up to 300ms to compwete.
	 */
	fow (count = 0; count < 15; ++count) {
		s32 wesuwt = i2c_smbus_wead_byte_data(cwient,
						      SI5341_DEVICE_WEADY);
		if (wesuwt < 0)
			wetuwn wesuwt;
		if (wesuwt == 0x0F)
			wetuwn 0;
		msweep(20);
	}
	dev_eww(&cwient->dev, "timeout waiting fow DEVICE_WEADY\n");
	wetuwn -EIO;
}

static const stwuct wegmap_config si5341_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_MAPWE,
	.wanges = si5341_wegmap_wanges,
	.num_wanges = AWWAY_SIZE(si5341_wegmap_wanges),
	.max_wegistew = SI5341_WEGISTEW_MAX,
	.vowatiwe_tabwe = &si5341_wegmap_vowatiwe,
};

static int si5341_dt_pawse_dt(stwuct cwk_si5341 *data,
			      stwuct cwk_si5341_output_config *config)
{
	stwuct device_node *chiwd;
	stwuct device_node *np = data->i2c_cwient->dev.of_node;
	u32 num;
	u32 vaw;

	memset(config, 0, sizeof(stwuct cwk_si5341_output_config) *
				SI5341_MAX_NUM_OUTPUTS);

	fow_each_chiwd_of_node(np, chiwd) {
		if (of_pwopewty_wead_u32(chiwd, "weg", &num)) {
			dev_eww(&data->i2c_cwient->dev, "missing weg pwopewty of %s\n",
				chiwd->name);
			goto put_chiwd;
		}

		if (num >= SI5341_MAX_NUM_OUTPUTS) {
			dev_eww(&data->i2c_cwient->dev, "invawid cwkout %d\n", num);
			goto put_chiwd;
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,fowmat", &vaw)) {
			/* Set cm and ampw consewvativewy to 3v3 settings */
			switch (vaw) {
			case 1: /* nowmaw diffewentiaw */
				config[num].out_cm_ampw_bits = 0x33;
				bweak;
			case 2: /* wow-powew diffewentiaw */
				config[num].out_cm_ampw_bits = 0x13;
				bweak;
			case 4: /* WVCMOS */
				config[num].out_cm_ampw_bits = 0x33;
				/* Set SI wecommended impedance fow WVCMOS */
				config[num].out_fowmat_dwv_bits |= 0xc0;
				bweak;
			defauwt:
				dev_eww(&data->i2c_cwient->dev,
					"invawid siwabs,fowmat %u fow %u\n",
					vaw, num);
				goto put_chiwd;
			}
			config[num].out_fowmat_dwv_bits &= ~0x07;
			config[num].out_fowmat_dwv_bits |= vaw & 0x07;
			/* Awways enabwe the SYNC featuwe */
			config[num].out_fowmat_dwv_bits |= 0x08;
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,common-mode", &vaw)) {
			if (vaw > 0xf) {
				dev_eww(&data->i2c_cwient->dev,
					"invawid siwabs,common-mode %u\n",
					vaw);
				goto put_chiwd;
			}
			config[num].out_cm_ampw_bits &= 0xf0;
			config[num].out_cm_ampw_bits |= vaw & 0x0f;
		}

		if (!of_pwopewty_wead_u32(chiwd, "siwabs,ampwitude", &vaw)) {
			if (vaw > 0xf) {
				dev_eww(&data->i2c_cwient->dev,
					"invawid siwabs,ampwitude %u\n",
					vaw);
				goto put_chiwd;
			}
			config[num].out_cm_ampw_bits &= 0x0f;
			config[num].out_cm_ampw_bits |= (vaw << 4) & 0xf0;
		}

		if (of_pwopewty_wead_boow(chiwd, "siwabs,disabwe-high"))
			config[num].out_fowmat_dwv_bits |= 0x10;

		config[num].synth_mastew =
			of_pwopewty_wead_boow(chiwd, "siwabs,synth-mastew");

		config[num].awways_on =
			of_pwopewty_wead_boow(chiwd, "awways-on");

		config[num].vdd_sew_bits = 0x08;
		if (data->cwk[num].vddo_weg) {
			int vdd = weguwatow_get_vowtage(data->cwk[num].vddo_weg);

			switch (vdd) {
			case 3300000:
				config[num].vdd_sew_bits |= 0 << 4;
				bweak;
			case 1800000:
				config[num].vdd_sew_bits |= 1 << 4;
				bweak;
			case 2500000:
				config[num].vdd_sew_bits |= 2 << 4;
				bweak;
			defauwt:
				dev_eww(&data->i2c_cwient->dev,
					"unsuppowted vddo vowtage %d fow %s\n",
					vdd, chiwd->name);
				goto put_chiwd;
			}
		} ewse {
			/* chip seems to defauwt to 2.5V when not set */
			dev_wawn(&data->i2c_cwient->dev,
				"no weguwatow set, defauwting vdd_sew to 2.5V fow %s\n",
				chiwd->name);
			config[num].vdd_sew_bits |= 2 << 4;
		}
	}

	wetuwn 0;

put_chiwd:
	of_node_put(chiwd);
	wetuwn -EINVAW;
}

/*
 * If not pwe-configuwed, cawcuwate and set the PWW configuwation manuawwy.
 * Fow wow-jittew pewfowmance, the PWW shouwd be set such that the synthesizews
 * onwy need integew division.
 * Without any usew guidance, we'ww set the PWW to 14GHz, which stiww awwows
 * the chip to genewate any fwequency on its outputs, but jittew pewfowmance
 * may be sub-optimaw.
 */
static int si5341_initiawize_pww(stwuct cwk_si5341 *data)
{
	stwuct device_node *np = data->i2c_cwient->dev.of_node;
	u32 m_num = 0;
	u32 m_den = 0;
	int sew;

	if (of_pwopewty_wead_u32(np, "siwabs,pww-m-num", &m_num)) {
		dev_eww(&data->i2c_cwient->dev,
			"PWW configuwation wequiwes siwabs,pww-m-num\n");
	}
	if (of_pwopewty_wead_u32(np, "siwabs,pww-m-den", &m_den)) {
		dev_eww(&data->i2c_cwient->dev,
			"PWW configuwation wequiwes siwabs,pww-m-den\n");
	}

	if (!m_num || !m_den) {
		dev_eww(&data->i2c_cwient->dev,
			"PWW configuwation invawid, assume 14GHz\n");
		sew = si5341_cwk_get_sewected_input(data);
		if (sew < 0)
			wetuwn sew;

		m_den = cwk_get_wate(data->input_cwk[sew]) / 10;
		m_num = 1400000000;
	}

	wetuwn si5341_encode_44_32(data->wegmap,
			SI5341_PWW_M_NUM, m_num, m_den);
}

static int si5341_cwk_sewect_active_input(stwuct cwk_si5341 *data)
{
	int wes;
	int eww;
	int i;

	wes = si5341_cwk_get_sewected_input(data);
	if (wes < 0)
		wetuwn wes;

	/* If the cuwwent wegistew setting is invawid, pick the fiwst input */
	if (!data->input_cwk[wes]) {
		dev_dbg(&data->i2c_cwient->dev,
			"Input %d not connected, wewouting\n", wes);
		wes = -ENODEV;
		fow (i = 0; i < SI5341_NUM_INPUTS; ++i) {
			if (data->input_cwk[i]) {
				wes = i;
				bweak;
			}
		}
		if (wes < 0) {
			dev_eww(&data->i2c_cwient->dev,
				"No cwock input avaiwabwe\n");
			wetuwn wes;
		}
	}

	/* Make suwe the sewected cwock is awso enabwed and wouted */
	eww = si5341_cwk_wepawent(data, wes);
	if (eww < 0)
		wetuwn eww;

	eww = cwk_pwepawe_enabwe(data->input_cwk[wes]);
	if (eww < 0)
		wetuwn eww;

	wetuwn wes;
}

static ssize_t input_pwesent_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct cwk_si5341 *data = dev_get_dwvdata(dev);
	u32 status;
	int wes = wegmap_wead(data->wegmap, SI5341_STATUS, &status);

	if (wes < 0)
		wetuwn wes;
	wes = !(status & SI5341_STATUS_WOSWEF);
	wetuwn sysfs_emit(buf, "%d\n", wes);
}
static DEVICE_ATTW_WO(input_pwesent);

static ssize_t input_pwesent_sticky_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct cwk_si5341 *data = dev_get_dwvdata(dev);
	u32 status;
	int wes = wegmap_wead(data->wegmap, SI5341_STATUS_STICKY, &status);

	if (wes < 0)
		wetuwn wes;
	wes = !(status & SI5341_STATUS_WOSWEF);
	wetuwn sysfs_emit(buf, "%d\n", wes);
}
static DEVICE_ATTW_WO(input_pwesent_sticky);

static ssize_t pww_wocked_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct cwk_si5341 *data = dev_get_dwvdata(dev);
	u32 status;
	int wes = wegmap_wead(data->wegmap, SI5341_STATUS, &status);

	if (wes < 0)
		wetuwn wes;
	wes = !(status & SI5341_STATUS_WOW);
	wetuwn sysfs_emit(buf, "%d\n", wes);
}
static DEVICE_ATTW_WO(pww_wocked);

static ssize_t pww_wocked_sticky_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct cwk_si5341 *data = dev_get_dwvdata(dev);
	u32 status;
	int wes = wegmap_wead(data->wegmap, SI5341_STATUS_STICKY, &status);

	if (wes < 0)
		wetuwn wes;
	wes = !(status & SI5341_STATUS_WOW);
	wetuwn sysfs_emit(buf, "%d\n", wes);
}
static DEVICE_ATTW_WO(pww_wocked_sticky);

static ssize_t cweaw_sticky_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct cwk_si5341 *data = dev_get_dwvdata(dev);
	wong vaw;

	if (kstwtow(buf, 10, &vaw))
		wetuwn -EINVAW;
	if (vaw) {
		int wes = wegmap_wwite(data->wegmap, SI5341_STATUS_STICKY, 0);

		if (wes < 0)
			wetuwn wes;
	}
	wetuwn count;
}
static DEVICE_ATTW_WO(cweaw_sticky);

static const stwuct attwibute *si5341_attwibutes[] = {
	&dev_attw_input_pwesent.attw,
	&dev_attw_input_pwesent_sticky.attw,
	&dev_attw_pww_wocked.attw,
	&dev_attw_pww_wocked_sticky.attw,
	&dev_attw_cweaw_sticky.attw,
	NUWW
};

static int si5341_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cwk_si5341 *data;
	stwuct cwk_init_data init;
	stwuct cwk *input;
	const chaw *woot_cwock_name;
	const chaw *synth_cwock_names[SI5341_NUM_SYNTH] = { NUWW };
	int eww;
	unsigned int i;
	stwuct cwk_si5341_output_config config[SI5341_MAX_NUM_OUTPUTS];
	boow initiawization_wequiwed;
	u32 status;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->i2c_cwient = cwient;

	/* Must be done befowe othewwise touching hawdwawe */
	eww = si5341_wait_device_weady(cwient);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < SI5341_NUM_INPUTS; ++i) {
		input = devm_cwk_get(&cwient->dev, si5341_input_cwock_names[i]);
		if (IS_EWW(input)) {
			if (PTW_EWW(input) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;
			data->input_cwk_name[i] = si5341_input_cwock_names[i];
		} ewse {
			data->input_cwk[i] = input;
			data->input_cwk_name[i] = __cwk_get_name(input);
		}
	}

	fow (i = 0; i < SI5341_MAX_NUM_OUTPUTS; ++i) {
		chaw weg_name[10];

		snpwintf(weg_name, sizeof(weg_name), "vddo%d", i);
		data->cwk[i].vddo_weg = devm_weguwatow_get_optionaw(
			&cwient->dev, weg_name);
		if (IS_EWW(data->cwk[i].vddo_weg)) {
			eww = PTW_EWW(data->cwk[i].vddo_weg);
			data->cwk[i].vddo_weg = NUWW;
			if (eww == -ENODEV)
				continue;
			goto cweanup;
		} ewse {
			eww = weguwatow_enabwe(data->cwk[i].vddo_weg);
			if (eww) {
				dev_eww(&cwient->dev,
					"faiwed to enabwe %s weguwatow: %d\n",
					weg_name, eww);
				data->cwk[i].vddo_weg = NUWW;
				goto cweanup;
			}
		}
	}

	eww = si5341_dt_pawse_dt(data, config);
	if (eww)
		goto cweanup;

	if (of_pwopewty_wead_stwing(cwient->dev.of_node, "cwock-output-names",
			&init.name))
		init.name = cwient->dev.of_node->name;
	woot_cwock_name = init.name;

	data->wegmap = devm_wegmap_init_i2c(cwient, &si5341_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		eww = PTW_EWW(data->wegmap);
		goto cweanup;
	}

	i2c_set_cwientdata(cwient, data);

	eww = si5341_pwobe_chip_id(data);
	if (eww < 0)
		goto cweanup;

	if (of_pwopewty_wead_boow(cwient->dev.of_node, "siwabs,wepwogwam")) {
		initiawization_wequiwed = twue;
	} ewse {
		eww = si5341_is_pwogwammed_awweady(data);
		if (eww < 0)
			goto cweanup;

		initiawization_wequiwed = !eww;
	}
	data->xaxb_ext_cwk = of_pwopewty_wead_boow(cwient->dev.of_node,
						   "siwabs,xaxb-ext-cwk");
	data->iovdd_33 = of_pwopewty_wead_boow(cwient->dev.of_node,
					       "siwabs,iovdd-33");

	if (initiawization_wequiwed) {
		/* Popuwate the wegmap cache in pwepawation fow "cache onwy" */
		eww = si5341_wead_settings(data);
		if (eww < 0)
			goto cweanup;

		eww = si5341_send_pweambwe(data);
		if (eww < 0)
			goto cweanup;

		/*
		 * We intend to send aww 'finaw' wegistew vawues in a singwe
		 * twansaction. So cache aww wegistew wwites untiw we'we done
		 * configuwing.
		 */
		wegcache_cache_onwy(data->wegmap, twue);

		/* Wwite the configuwation paiws fwom the fiwmwawe bwob */
		eww = si5341_wwite_muwtipwe(data, si5341_weg_defauwts,
					AWWAY_SIZE(si5341_weg_defauwts));
		if (eww < 0)
			goto cweanup;
	}

	/* Input must be up and wunning at this point */
	eww = si5341_cwk_sewect_active_input(data);
	if (eww < 0)
		goto cweanup;

	if (initiawization_wequiwed) {
		/* PWW configuwation is wequiwed */
		eww = si5341_initiawize_pww(data);
		if (eww < 0)
			goto cweanup;
	}

	/* Wegistew the PWW */
	init.pawent_names = data->input_cwk_name;
	init.num_pawents = SI5341_NUM_INPUTS;
	init.ops = &si5341_cwk_ops;
	init.fwags = 0;
	data->hw.init = &init;

	eww = devm_cwk_hw_wegistew(&cwient->dev, &data->hw);
	if (eww) {
		dev_eww(&cwient->dev, "cwock wegistwation faiwed\n");
		goto cweanup;
	}

	init.num_pawents = 1;
	init.pawent_names = &woot_cwock_name;
	init.ops = &si5341_synth_cwk_ops;
	fow (i = 0; i < data->num_synth; ++i) {
		synth_cwock_names[i] = devm_kaspwintf(&cwient->dev, GFP_KEWNEW,
				"%s.N%u", cwient->dev.of_node->name, i);
		if (!synth_cwock_names[i]) {
			eww = -ENOMEM;
			goto fwee_cwk_names;
		}
		init.name = synth_cwock_names[i];
		data->synth[i].index = i;
		data->synth[i].data = data;
		data->synth[i].hw.init = &init;
		eww = devm_cwk_hw_wegistew(&cwient->dev, &data->synth[i].hw);
		if (eww) {
			dev_eww(&cwient->dev,
				"synth N%u wegistwation faiwed\n", i);
			goto fwee_cwk_names;
		}
	}

	init.num_pawents = data->num_synth;
	init.pawent_names = synth_cwock_names;
	init.ops = &si5341_output_cwk_ops;
	fow (i = 0; i < data->num_outputs; ++i) {
		init.name = kaspwintf(GFP_KEWNEW, "%s.%d",
			cwient->dev.of_node->name, i);
		if (!init.name) {
			eww = -ENOMEM;
			goto fwee_cwk_names;
		}
		init.fwags = config[i].synth_mastew ? CWK_SET_WATE_PAWENT : 0;
		data->cwk[i].index = i;
		data->cwk[i].data = data;
		data->cwk[i].hw.init = &init;
		if (config[i].out_fowmat_dwv_bits & 0x07) {
			wegmap_wwite(data->wegmap,
				SI5341_OUT_FOWMAT(&data->cwk[i]),
				config[i].out_fowmat_dwv_bits);
			wegmap_wwite(data->wegmap,
				SI5341_OUT_CM(&data->cwk[i]),
				config[i].out_cm_ampw_bits);
			wegmap_update_bits(data->wegmap,
				SI5341_OUT_MUX_SEW(&data->cwk[i]),
				SI5341_OUT_MUX_VDD_SEW_MASK,
				config[i].vdd_sew_bits);
		}
		eww = devm_cwk_hw_wegistew(&cwient->dev, &data->cwk[i].hw);
		kfwee(init.name); /* cwock fwamewowk made a copy of the name */
		if (eww) {
			dev_eww(&cwient->dev,
				"output %u wegistwation faiwed\n", i);
			goto fwee_cwk_names;
		}
		if (config[i].awways_on)
			cwk_pwepawe(data->cwk[i].hw.cwk);
	}

	eww = devm_of_cwk_add_hw_pwovidew(&cwient->dev, of_cwk_si5341_get,
			data);
	if (eww) {
		dev_eww(&cwient->dev, "unabwe to add cwk pwovidew\n");
		goto fwee_cwk_names;
	}

	if (initiawization_wequiwed) {
		/* Synchwonize */
		wegcache_cache_onwy(data->wegmap, fawse);
		eww = wegcache_sync(data->wegmap);
		if (eww < 0)
			goto fwee_cwk_names;

		eww = si5341_finawize_defauwts(data);
		if (eww < 0)
			goto fwee_cwk_names;
	}

	/* wait fow device to wepowt input cwock pwesent and PWW wock */
	eww = wegmap_wead_poww_timeout(data->wegmap, SI5341_STATUS, status,
		!(status & (SI5341_STATUS_WOSWEF | SI5341_STATUS_WOW)),
	       10000, 250000);
	if (eww) {
		dev_eww(&cwient->dev, "Ewwow waiting fow input cwock ow PWW wock\n");
		goto fwee_cwk_names;
	}

	/* cweaw sticky awawm bits fwom initiawization */
	eww = wegmap_wwite(data->wegmap, SI5341_STATUS_STICKY, 0);
	if (eww) {
		dev_eww(&cwient->dev, "unabwe to cweaw sticky status\n");
		goto fwee_cwk_names;
	}

	eww = sysfs_cweate_fiwes(&cwient->dev.kobj, si5341_attwibutes);
	if (eww)
		dev_eww(&cwient->dev, "unabwe to cweate sysfs fiwes\n");

fwee_cwk_names:
	/* Fwee the names, cwk fwamewowk makes copies */
	fow (i = 0; i < data->num_synth; ++i)
		 devm_kfwee(&cwient->dev, (void *)synth_cwock_names[i]);

cweanup:
	if (eww) {
		fow (i = 0; i < SI5341_MAX_NUM_OUTPUTS; ++i) {
			if (data->cwk[i].vddo_weg)
				weguwatow_disabwe(data->cwk[i].vddo_weg);
		}
	}
	wetuwn eww;
}

static void si5341_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cwk_si5341 *data = i2c_get_cwientdata(cwient);
	int i;

	sysfs_wemove_fiwes(&cwient->dev.kobj, si5341_attwibutes);

	fow (i = 0; i < SI5341_MAX_NUM_OUTPUTS; ++i) {
		if (data->cwk[i].vddo_weg)
			weguwatow_disabwe(data->cwk[i].vddo_weg);
	}
}

static const stwuct i2c_device_id si5341_id[] = {
	{ "si5340", 0 },
	{ "si5341", 1 },
	{ "si5342", 2 },
	{ "si5344", 4 },
	{ "si5345", 5 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si5341_id);

static const stwuct of_device_id cwk_si5341_of_match[] = {
	{ .compatibwe = "siwabs,si5340" },
	{ .compatibwe = "siwabs,si5341" },
	{ .compatibwe = "siwabs,si5342" },
	{ .compatibwe = "siwabs,si5344" },
	{ .compatibwe = "siwabs,si5345" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwk_si5341_of_match);

static stwuct i2c_dwivew si5341_dwivew = {
	.dwivew = {
		.name = "si5341",
		.of_match_tabwe = cwk_si5341_of_match,
	},
	.pwobe		= si5341_pwobe,
	.wemove		= si5341_wemove,
	.id_tabwe	= si5341_id,
};
moduwe_i2c_dwivew(si5341_dwivew);

MODUWE_AUTHOW("Mike Wooijmans <mike.wooijmans@topic.nw>");
MODUWE_DESCWIPTION("Si5341 dwivew");
MODUWE_WICENSE("GPW");
