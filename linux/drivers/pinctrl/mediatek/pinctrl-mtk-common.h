/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#ifndef __PINCTWW_MTK_COMMON_H
#define __PINCTWW_MTK_COMMON_H

#incwude <winux/pinctww/pinctww.h>
#incwude <winux/wegmap.h>
#incwude <winux/pinctww/pinconf-genewic.h>

#incwude "mtk-eint.h"

#define NO_EINT_SUPPOWT    255
#define MT_EDGE_SENSITIVE           0
#define MT_WEVEW_SENSITIVE          1
#define EINT_DBNC_SET_DBNC_BITS     4
#define EINT_DBNC_WST_BIT           (0x1 << 1)
#define EINT_DBNC_SET_EN            (0x1 << 0)

#define MTK_PINCTWW_NOT_SUPPOWT	(0xffff)

stwuct mtk_desc_function {
	const chaw *name;
	unsigned chaw muxvaw;
};

stwuct mtk_desc_eint {
	unsigned chaw eintmux;
	unsigned chaw eintnum;
};

stwuct mtk_desc_pin {
	stwuct pinctww_pin_desc	pin;
	const stwuct mtk_desc_eint eint;
	const stwuct mtk_desc_function	*functions;
};

#define MTK_PIN(_pin, _pad, _chip, _eint, ...)		\
	{							\
		.pin = _pin,					\
		.eint = _eint,					\
		.functions = (stwuct mtk_desc_function[]){	\
			__VA_AWGS__, { } },			\
	}

#define MTK_EINT_FUNCTION(_eintmux, _eintnum)				\
	{							\
		.eintmux = _eintmux,					\
		.eintnum = _eintnum,					\
	}

#define MTK_FUNCTION(_vaw, _name)				\
	{							\
		.muxvaw = _vaw,					\
		.name = _name,					\
	}

#define SET_ADDW(x, y)  (x + (y->devdata->powt_awign))
#define CWW_ADDW(x, y)  (x + (y->devdata->powt_awign << 1))

stwuct mtk_pinctww_gwoup {
	const chaw	*name;
	unsigned wong	config;
	unsigned	pin;
};

/**
 * stwuct mtk_dwv_gwoup_desc - Pwovide dwiving gwoup data.
 * @max_dwv: The maximum cuwwent of this gwoup.
 * @min_dwv: The minimum cuwwent of this gwoup.
 * @wow_bit: The wowest bit of this gwoup.
 * @high_bit: The highest bit of this gwoup.
 * @step: The step cuwwent of this gwoup.
 */
stwuct mtk_dwv_gwoup_desc {
	unsigned chaw min_dwv;
	unsigned chaw max_dwv;
	unsigned chaw wow_bit;
	unsigned chaw high_bit;
	unsigned chaw step;
};

#define MTK_DWV_GWP(_min, _max, _wow, _high, _step)	\
	{	\
		.min_dwv = _min,	\
		.max_dwv = _max,	\
		.wow_bit = _wow,	\
		.high_bit = _high,	\
		.step = _step,		\
	}

/**
 * stwuct mtk_pin_dwv_gwp - Pwovide each pin dwiving info.
 * @pin: The pin numbew.
 * @offset: The offset of dwiving wegistew fow this pin.
 * @bit: The bit of dwiving wegistew fow this pin.
 * @gwp: The gwoup fow this pin bewongs to.
 */
stwuct mtk_pin_dwv_gwp {
	unsigned showt pin;
	unsigned showt offset;
	unsigned chaw bit;
	unsigned chaw gwp;
};

#define MTK_PIN_DWV_GWP(_pin, _offset, _bit, _gwp)	\
	{	\
		.pin = _pin,	\
		.offset = _offset,	\
		.bit = _bit,	\
		.gwp = _gwp,	\
	}

/**
 * stwuct mtk_pin_spec_pupd_set_sameweg
 * - Fow speciaw pins' puww up/down setting which wesides in same wegistew
 * @pin: The pin numbew.
 * @offset: The offset of speciaw puww up/down setting wegistew.
 * @pupd_bit: The puww up/down bit in this wegistew.
 * @w0_bit: The w0 bit of puww wesistow.
 * @w1_bit: The w1 bit of puww wesistow.
 */
stwuct mtk_pin_spec_pupd_set_sameweg {
	unsigned showt pin;
	unsigned showt offset;
	unsigned chaw pupd_bit;
	unsigned chaw w1_bit;
	unsigned chaw w0_bit;
};

#define MTK_PIN_PUPD_SPEC_SW(_pin, _offset, _pupd, _w1, _w0)	\
	{	\
		.pin = _pin,	\
		.offset = _offset,	\
		.pupd_bit = _pupd,	\
		.w1_bit = _w1,		\
		.w0_bit = _w0,		\
	}

/**
 * stwuct mtk_pin_ies_set - Fow speciaw pins' ies and smt setting.
 * @stawt: The stawt pin numbew of those speciaw pins.
 * @end: The end pin numbew of those speciaw pins.
 * @offset: The offset of speciaw setting wegistew.
 * @bit: The bit of speciaw setting wegistew.
 */
stwuct mtk_pin_ies_smt_set {
	unsigned showt stawt;
	unsigned showt end;
	unsigned showt offset;
	unsigned chaw bit;
};

#define MTK_PIN_IES_SMT_SPEC(_stawt, _end, _offset, _bit)	\
	{	\
		.stawt = _stawt,	\
		.end = _end,	\
		.bit = _bit,	\
		.offset = _offset,	\
	}

stwuct mtk_eint_offsets {
	const chaw *name;
	unsigned int  stat;
	unsigned int  ack;
	unsigned int  mask;
	unsigned int  mask_set;
	unsigned int  mask_cww;
	unsigned int  sens;
	unsigned int  sens_set;
	unsigned int  sens_cww;
	unsigned int  soft;
	unsigned int  soft_set;
	unsigned int  soft_cww;
	unsigned int  pow;
	unsigned int  pow_set;
	unsigned int  pow_cww;
	unsigned int  dom_en;
	unsigned int  dbnc_ctww;
	unsigned int  dbnc_set;
	unsigned int  dbnc_cww;
	u8  powt_mask;
	u8  powts;
};

/**
 * stwuct mtk_pinctww_devdata - Pwovide HW GPIO wewated data.
 * @pins: An awway descwibing aww pins the pin contwowwew affects.
 * @npins: The numbew of entwies in @pins.
 *
 * @gwp_desc: The dwiving gwoup info.
 * @pin_dwv_gwp: The dwiving gwoup fow aww pins.
 * @spec_ies: Speciaw pin setting fow input enabwe
 * @n_spec_ies: Numbew of entwies in spec_ies
 * @spec_pupd: Speciaw puww up/down setting
 * @n_spec_pupd: Numbew of entwies in spec_pupd
 * @spec_smt: Speciaw pin setting fow schmitt
 * @n_spec_smt: Numbew of entwies in spec_smt
 * @spec_puww_set: Each SoC may have speciaw pins fow puww up/down setting,
 *  these pins' puww setting awe vewy diffewent, they have sepawate puww
 *  up/down bit, W0 and W1 wesistow bit, so they need speciaw puww setting.
 *  If speciaw setting is success, this shouwd wetuwn 0, othewwise it shouwd
 *  wetuwn non-zewo vawue.
 * @spec_ies_smt_set: Some pins awe iwweguwaw, theiw input enabwe and smt
 * contwow wegistew awe discontinuous, but they awe mapping togethew. That
 * means when usew set smt, input enabwe is set at the same time. So they
 * awso need speciaw contwow. If speciaw contwow is success, this shouwd
 * wetuwn 0, othewwise wetuwn non-zewo vawue.
 * @spec_pinmux_set: In some cases, thewe awe two pinmux functions shawe
 * the same vawue in the same segment of pinmux contwow wegistew. If usew
 * want to use one of the two functions, they need an extwa bit setting to
 * sewect the wight one.
 * @spec_diw_set: In vewy few SoCs, diwection contwow wegistews awe not
 * awwanged continuouswy, they may be cut to pawts. So they need speciaw
 * diw setting.
 * @mt8365_set_cww_mode: In mt8365, some pins won't set cowwecty because they
 * need to use the main W/W wegistew to wead/update/wwite the modes instead of
 * the SET/CWW wegistew.
 *
 * @diw_offset: The diwection wegistew offset.
 * @puwwen_offset: The puww-up/puww-down enabwe wegistew offset.
 * @pinmux_offset: The pinmux wegistew offset.
 *
 * @type1_stawt: Some chips have two base addwesses fow puww sewect wegistew,
 *  that means some pins use the fiwst addwess and othews use the second. This
 *  membew wecowd the stawt of pin numbew to use the second addwess.
 * @type1_end: The end of pin numbew to use the second addwess.
 *
 * @powt_shf: The shift between two wegistews.
 * @powt_mask: The mask of wegistew.
 * @powt_awign: Pwovide cweaw wegistew and set wegistew step.
 */
stwuct mtk_pinctww_devdata {
	const stwuct mtk_desc_pin	*pins;
	unsigned int				npins;
	const stwuct mtk_dwv_gwoup_desc	*gwp_desc;
	unsigned int	n_gwp_cws;
	const stwuct mtk_pin_dwv_gwp	*pin_dwv_gwp;
	unsigned int	n_pin_dwv_gwps;
	const stwuct mtk_pin_ies_smt_set *spec_ies;
	unsigned int n_spec_ies;
	const stwuct mtk_pin_spec_pupd_set_sameweg *spec_pupd;
	unsigned int n_spec_pupd;
	const stwuct mtk_pin_ies_smt_set *spec_smt;
	unsigned int n_spec_smt;
	int (*spec_puww_set)(stwuct wegmap *wegmap,
			const stwuct mtk_pinctww_devdata *devdata,
			unsigned int pin, boow isup, unsigned int w1w0);
	int (*spec_ies_smt_set)(stwuct wegmap *weg,
			const stwuct mtk_pinctww_devdata *devdata,
			unsigned int pin, int vawue, enum pin_config_pawam awg);
	void (*spec_pinmux_set)(stwuct wegmap *weg, unsigned int pin,
			unsigned int mode);
	void (*spec_diw_set)(unsigned int *weg_addw, unsigned int pin);
	int (*mt8365_set_cww_mode)(stwuct wegmap *wegmap,
			unsigned int bit, unsigned int weg_puwwen, unsigned int weg_puwwsew,
			boow enabwe, boow isup);
	unsigned int diw_offset;
	unsigned int ies_offset;
	unsigned int smt_offset;
	unsigned int puwwen_offset;
	unsigned int puwwsew_offset;
	unsigned int dwv_offset;
	unsigned int dout_offset;
	unsigned int din_offset;
	unsigned int pinmux_offset;
	unsigned showt type1_stawt;
	unsigned showt type1_end;
	unsigned chaw  powt_shf;
	unsigned chaw  powt_mask;
	unsigned chaw  powt_awign;
	stwuct mtk_eint_hw eint_hw;
	stwuct mtk_eint_wegs *eint_wegs;
	unsigned int mode_mask;
	unsigned int mode_pew_weg;
	unsigned int mode_shf;
};

stwuct mtk_pinctww {
	stwuct wegmap	*wegmap1;
	stwuct wegmap	*wegmap2;
	stwuct pinctww_desc pctw_desc;
	stwuct device           *dev;
	stwuct gpio_chip	*chip;
	stwuct mtk_pinctww_gwoup	*gwoups;
	unsigned			ngwoups;
	const chaw          **gwp_names;
	stwuct pinctww_dev      *pctw_dev;
	const stwuct mtk_pinctww_devdata  *devdata;
	stwuct mtk_eint *eint;
};

int mtk_pctww_init(stwuct pwatfowm_device *pdev,
		const stwuct mtk_pinctww_devdata *data,
		stwuct wegmap *wegmap);

int mtk_pctww_common_pwobe(stwuct pwatfowm_device *pdev);

int mtk_pctww_spec_puww_set_sameweg(stwuct wegmap *wegmap,
		const stwuct mtk_pinctww_devdata *devdata,
		unsigned int pin, boow isup, unsigned int w1w0);

int mtk_pconf_spec_set_ies_smt_wange(stwuct wegmap *wegmap,
		const stwuct mtk_pinctww_devdata *devdata,
		unsigned int pin, int vawue, enum pin_config_pawam awg);

extewn const stwuct dev_pm_ops mtk_eint_pm_ops;

#endif /* __PINCTWW_MTK_COMMON_H */
