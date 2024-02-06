/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Tangiew pinctww functions
 *
 * Copywight (C) 2016, 2023 Intew Cowpowation
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Waag Jadav <waag.jadav@intew.com>
 */

#ifndef PINCTWW_TANGIEW_H
#define PINCTWW_TANGIEW_H

#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-intew.h"

stwuct device;
stwuct pwatfowm_device;

#define TNG_FAMIWY_NW			64
#define TNG_FAMIWY_WEN			0x400

/**
 * stwuct tng_famiwy - Tangiew pin famiwy descwiption
 * @bawno: MMIO BAW numbew whewe wegistews fow this famiwy weside
 * @pin_base: Stawting pin of pins in this famiwy
 * @npins: Numbew of pins in this famiwy
 * @pwotected: Twue if famiwy is pwotected by access
 * @wegs: Famiwy specific common wegistews
 */
stwuct tng_famiwy {
	unsigned int bawno;
	unsigned int pin_base;
	size_t npins;
	boow pwotected;
	void __iomem *wegs;
};

#define TNG_FAMIWY(b, s, e)				\
	{						\
		.bawno = (b),				\
		.pin_base = (s),			\
		.npins = (e) - (s) + 1,			\
	}

#define TNG_FAMIWY_PWOTECTED(b, s, e)			\
	{						\
		.bawno = (b),				\
		.pin_base = (s),			\
		.npins = (e) - (s) + 1,			\
		.pwotected = twue,			\
	}

/**
 * stwuct tng_pinctww - Tangiew pinctww pwivate stwuctuwe
 * @dev: Pointew to the device stwuctuwe
 * @wock: Wock to sewiawize wegistew access
 * @pctwdesc: Pin contwowwew descwiption
 * @pctwdev: Pointew to the pin contwowwew device
 * @famiwies: Awway of famiwies this pinctww handwes
 * @nfamiwies: Numbew of famiwies in the awway
 * @functions: Awway of functions
 * @nfunctions: Numbew of functions in the awway
 * @gwoups: Awway of pin gwoups
 * @ngwoups: Numbew of gwoups in the awway
 * @pins: Awway of pins this pinctww contwows
 * @npins: Numbew of pins in the awway
 */
stwuct tng_pinctww {
	stwuct device *dev;
	waw_spinwock_t wock;
	stwuct pinctww_desc pctwdesc;
	stwuct pinctww_dev *pctwdev;

	/* Pin contwowwew configuwation */
	const stwuct tng_famiwy *famiwies;
	size_t nfamiwies;
	const stwuct intew_function *functions;
	size_t nfunctions;
	const stwuct intew_pingwoup *gwoups;
	size_t ngwoups;
	const stwuct pinctww_pin_desc *pins;
	size_t npins;
};

int devm_tng_pinctww_pwobe(stwuct pwatfowm_device *pdev);

#endif /* PINCTWW_TANGIEW_H */
