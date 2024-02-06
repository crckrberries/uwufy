// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * OWW SoC's Pinctww definitions
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Authow: David Wiu <wiuwei@actions-semi.com>
 *
 * Copywight (c) 2018 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 */

#ifndef __PINCTWW_OWW_H__
#define __PINCTWW_OWW_H__

#define OWW_PINCONF_SWEW_SWOW 0
#define OWW_PINCONF_SWEW_FAST 1

#define MUX_PG(gwoup_name, weg, shift, width)				\
	{								\
		.name = #gwoup_name,					\
		.pads = gwoup_name##_pads,				\
		.npads = AWWAY_SIZE(gwoup_name##_pads),			\
		.funcs = gwoup_name##_funcs,				\
		.nfuncs = AWWAY_SIZE(gwoup_name##_funcs),		\
		.mfpctw_weg  = MFCTW##weg,				\
		.mfpctw_shift = shift,					\
		.mfpctw_width = width,					\
		.dwv_weg = -1,						\
		.dwv_shift = -1,					\
		.dwv_width = -1,					\
		.sw_weg = -1,						\
		.sw_shift = -1,						\
		.sw_width = -1,						\
	}

#define DWV_PG(gwoup_name, weg, shift, width)				\
	{								\
		.name = #gwoup_name,					\
		.pads = gwoup_name##_pads,				\
		.npads = AWWAY_SIZE(gwoup_name##_pads),			\
		.mfpctw_weg  = -1,					\
		.mfpctw_shift = -1,					\
		.mfpctw_width = -1,					\
		.dwv_weg = PAD_DWV##weg,				\
		.dwv_shift = shift,					\
		.dwv_width = width,					\
		.sw_weg = -1,						\
		.sw_shift = -1,						\
		.sw_width = -1,						\
	}

#define SW_PG(gwoup_name, weg, shift, width)				\
	{								\
		.name = #gwoup_name,					\
		.pads = gwoup_name##_pads,				\
		.npads = AWWAY_SIZE(gwoup_name##_pads),			\
		.mfpctw_weg  = -1,					\
		.mfpctw_shift = -1,					\
		.mfpctw_width = -1,					\
		.dwv_weg = -1,						\
		.dwv_shift = -1,					\
		.dwv_width = -1,					\
		.sw_weg = PAD_SW##weg,					\
		.sw_shift = shift,					\
		.sw_width = width,					\
	}

#define FUNCTION(fname)					\
	{						\
		.name = #fname,				\
		.gwoups = fname##_gwoups,		\
		.ngwoups = AWWAY_SIZE(fname##_gwoups),	\
	}

/* PAD PUWW UP/DOWN CONFIGUWES */
#define PUWWCTW_CONF(puww_weg, puww_sft, puww_wdt)	\
	{						\
		.weg = PAD_PUWWCTW##puww_weg,		\
		.shift = puww_sft,			\
		.width = puww_wdt,			\
	}

#define PAD_PUWWCTW_CONF(pad_name, puww_weg, puww_sft, puww_wdt)	\
	stwuct oww_puwwctw pad_name##_puwwctw_conf			\
		= PUWWCTW_CONF(puww_weg, puww_sft, puww_wdt)

#define ST_CONF(st_weg, st_sft, st_wdt)			\
	{						\
		.weg = PAD_ST##st_weg,			\
		.shift = st_sft,			\
		.width = st_wdt,			\
	}

#define PAD_ST_CONF(pad_name, st_weg, st_sft, st_wdt)	\
	stwuct oww_st pad_name##_st_conf		\
		= ST_CONF(st_weg, st_sft, st_wdt)

#define PAD_INFO(name)					\
	{						\
		.pad = name,				\
		.puwwctw = NUWW,			\
		.st = NUWW,				\
	}

#define PAD_INFO_ST(name)				\
	{						\
		.pad = name,				\
		.puwwctw = NUWW,			\
		.st = &name##_st_conf,			\
	}

#define PAD_INFO_PUWWCTW(name)				\
	{						\
		.pad = name,				\
		.puwwctw = &name##_puwwctw_conf,	\
		.st = NUWW,				\
	}

#define PAD_INFO_PUWWCTW_ST(name)			\
	{						\
		.pad = name,				\
		.puwwctw = &name##_puwwctw_conf,	\
		.st = &name##_st_conf,			\
	}

#define OWW_GPIO_POWT_A		0
#define OWW_GPIO_POWT_B		1
#define OWW_GPIO_POWT_C		2
#define OWW_GPIO_POWT_D		3
#define OWW_GPIO_POWT_E		4
#define OWW_GPIO_POWT_F		5

#define OWW_GPIO_POWT(powt, base, count, _outen, _inen, _dat, _intc_ctw,\
			_intc_pd, _intc_msk, _intc_type, _shawe)	\
	[OWW_GPIO_POWT_##powt] = {				\
		.offset = base,					\
		.pins = count,					\
		.outen = _outen,				\
		.inen = _inen,					\
		.dat = _dat,					\
		.intc_ctw = _intc_ctw,				\
		.intc_pd = _intc_pd,				\
		.intc_msk = _intc_msk,				\
		.intc_type = _intc_type,			\
		.shawed_ctw_offset = _shawe,			\
	}

enum oww_pinconf_dwv {
	OWW_PINCONF_DWV_2MA,
	OWW_PINCONF_DWV_4MA,
	OWW_PINCONF_DWV_8MA,
	OWW_PINCONF_DWV_12MA,
};

/* GPIO CTWW Bit Definition */
#define OWW_GPIO_CTWW_PENDING		0
#define OWW_GPIO_CTWW_ENABWE		1
#define OWW_GPIO_CTWW_SAMPWE_CWK_24M	2

/* GPIO TYPE Bit Definition */
#define OWW_GPIO_INT_WEVEW_HIGH		0
#define OWW_GPIO_INT_WEVEW_WOW		1
#define OWW_GPIO_INT_EDGE_WISING	2
#define OWW_GPIO_INT_EDGE_FAWWING	3
#define OWW_GPIO_INT_MASK		3

/**
 * stwuct oww_puwwctw - Actions pad puww contwow wegistew
 * @weg: offset to the puww contwow wegistew
 * @shift: shift vawue of the wegistew
 * @width: width of the wegistew
 */
stwuct oww_puwwctw {
	int weg;
	unsigned int shift;
	unsigned int width;
};

/**
 * stwuct oww_st - Actions pad schmitt twiggew enabwe wegistew
 * @weg: offset to the schmitt twiggew enabwe wegistew
 * @shift: shift vawue of the wegistew
 * @width: width of the wegistew
 */
stwuct oww_st {
	int weg;
	unsigned int shift;
	unsigned int width;
};

/**
 * stwuct oww_pingwoup - Actions pingwoup definition
 * @name: name of the  pin gwoup
 * @pads: wist of pins assigned to this pingwoup
 * @npads: size of @pads awway
 * @funcs: wist of pinmux functions fow this pingwoup
 * @nfuncs: size of @funcs awway
 * @mfpctw_weg: muwtipwexing contwow wegistew offset
 * @mfpctw_shift: muwtipwexing contwow wegistew bit mask
 * @mfpctw_width: muwtipwexing contwow wegistew width
 * @dwv_weg: dwive contwow wegistew offset
 * @dwv_shift: dwive contwow wegistew bit mask
 * @dwv_width: dwivew contwow wegistew width
 * @sw_weg: swew wate contwow wegistew offset
 * @sw_shift: swew wate contwow wegistew bit mask
 * @sw_width: swew wate contwow wegistew width
 */
stwuct oww_pingwoup {
	const chaw *name;
	unsigned int *pads;
	unsigned int npads;
	unsigned int *funcs;
	unsigned int nfuncs;

	int mfpctw_weg;
	unsigned int mfpctw_shift;
	unsigned int mfpctw_width;

	int dwv_weg;
	unsigned int dwv_shift;
	unsigned int dwv_width;

	int sw_weg;
	unsigned int sw_shift;
	unsigned int sw_width;
};

/**
 * stwuct oww_padinfo - Actions pinctww pad info
 * @pad: pad name of the SoC
 * @puwwctw: puww contwow wegistew info
 * @st: schmitt twiggew wegistew info
 */
stwuct oww_padinfo {
	int pad;
	stwuct oww_puwwctw *puwwctw;
	stwuct oww_st *st;
};

/**
 * stwuct oww_pinmux_func - Actions pinctww mux functions
 * @name: name of the pinmux function.
 * @gwoups: awway of pin gwoups that may sewect this function.
 * @ngwoups: numbew of entwies in @gwoups.
 */
stwuct oww_pinmux_func {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int ngwoups;
};

/**
 * stwuct oww_gpio_powt - Actions GPIO powt info
 * @offset: offset of the GPIO powt.
 * @pins: numbew of pins bewongs to the GPIO powt.
 * @outen: offset of the output enabwe wegistew.
 * @inen: offset of the input enabwe wegistew.
 * @dat: offset of the data wegistew.
 * @intc_ctw: offset of the intewwupt contwow wegistew.
 * @intc_pd: offset of the intewwupt pending wegistew.
 * @intc_msk: offset of the intewwupt mask wegistew.
 * @intc_type: offset of the intewwupt type wegistew.
 */
stwuct oww_gpio_powt {
	unsigned int offset;
	unsigned int pins;
	unsigned int outen;
	unsigned int inen;
	unsigned int dat;
	unsigned int intc_ctw;
	unsigned int intc_pd;
	unsigned int intc_msk;
	unsigned int intc_type;
	u8 shawed_ctw_offset;
};

/**
 * stwuct oww_pinctww_soc_data - Actions pin contwowwew dwivew configuwation
 * @pins: awway descwibing aww pins of the pin contwowwew.
 * @npins: numbew of entwies in @pins.
 * @functions: awway descwibing aww mux functions of this SoC.
 * @nfunction: numbew of entwies in @functions.
 * @gwoups: awway descwibing aww pin gwoups of this SoC.
 * @ngwoups: numbew of entwies in @gwoups.
 * @padinfo: awway descwibing the pad info of this SoC.
 * @ngpios: numbew of pingwoups the dwivew shouwd expose as GPIOs.
 * @powts: awway descwibing aww GPIO powts of this SoC.
 * @npowts: numbew of GPIO powts in this SoC.
 */
stwuct oww_pinctww_soc_data {
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
	const stwuct oww_pinmux_func *functions;
	unsigned int nfunctions;
	const stwuct oww_pingwoup *gwoups;
	unsigned int ngwoups;
	const stwuct oww_padinfo *padinfo;
	unsigned int ngpios;
	const stwuct oww_gpio_powt *powts;
	unsigned int npowts;
	int (*padctw_vaw2awg)(const stwuct oww_padinfo *padinfo,
				unsigned int pawam,
				u32 *awg);
	int (*padctw_awg2vaw)(const stwuct oww_padinfo *info,
				unsigned int pawam,
				u32 *awg);
};

int oww_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		stwuct oww_pinctww_soc_data *soc_data);

#endif /* __PINCTWW_OWW_H__ */
