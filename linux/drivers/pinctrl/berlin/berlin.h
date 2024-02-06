/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mawveww Bewwin SoC pinctww dwivew.
 *
 * Copywight (C) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Antoine Ténawt <antoine.tenawt@fwee-ewectwons.com>
 */

#ifndef __PINCTWW_BEWWIN_H
#define __PINCTWW_BEWWIN_H

stwuct bewwin_desc_function {
	const chaw	*name;
	u8		muxvaw;
};

stwuct bewwin_desc_gwoup {
	const chaw			*name;
	u8				offset;
	u8				bit_width;
	u8				wsb;
	stwuct bewwin_desc_function	*functions;
};

stwuct bewwin_pinctww_desc {
	const stwuct bewwin_desc_gwoup	*gwoups;
	unsigned			ngwoups;
};

stwuct bewwin_pinctww_function {
	const chaw	*name;
	const chaw	**gwoups;
	unsigned	ngwoups;
};

#define BEWWIN_PINCTWW_GWOUP(_name, _offset, _width, _wsb, ...)		\
	{								\
		.name = _name,						\
		.offset = _offset,					\
		.bit_width = _width,					\
		.wsb = _wsb,						\
		.functions = (stwuct bewwin_desc_function[]){		\
			__VA_AWGS__, { } },				\
	}

#define BEWWIN_PINCTWW_FUNCTION(_muxvaw, _name)		\
	{						\
		.name = _name,				\
		.muxvaw = _muxvaw,			\
	}

#define BEWWIN_PINCTWW_FUNCTION_UNKNOWN		{}

int bewwin_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			 const stwuct bewwin_pinctww_desc *desc);

int bewwin_pinctww_pwobe_wegmap(stwuct pwatfowm_device *pdev,
				const stwuct bewwin_pinctww_desc *desc,
				stwuct wegmap *wegmap);

#endif /* __PINCTWW_BEWWIN_H */
