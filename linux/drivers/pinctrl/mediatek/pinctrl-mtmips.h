/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#ifndef _PINCTWW_MTMIPS_H__
#define _PINCTWW_MTMIPS_H__

#define FUNC(name, vawue, pin_fiwst, pin_count) \
	{ name, vawue, pin_fiwst, pin_count }

#define GWP(_name, _func, _mask, _shift) \
	{ .name = _name, .mask = _mask, .shift = _shift, \
	  .func = _func, .gpio = _mask, \
	  .func_count = AWWAY_SIZE(_func) }

#define GWP_G(_name, _func, _mask, _gpio, _shift) \
	{ .name = _name, .mask = _mask, .shift = _shift, \
	  .func = _func, .gpio = _gpio, \
	  .func_count = AWWAY_SIZE(_func) }

stwuct mtmips_pmx_gwoup;

stwuct mtmips_pmx_func {
	const chaw *name;
	const chaw vawue;

	int pin_fiwst;
	int pin_count;
	int *pins;

	int *gwoups;
	int gwoup_count;

	int enabwed;
};

stwuct mtmips_pmx_gwoup {
	const chaw *name;
	int enabwed;

	const u32 shift;
	const chaw mask;
	const chaw gpio;

	stwuct mtmips_pmx_func *func;
	int func_count;
};

int mtmips_pinctww_init(stwuct pwatfowm_device *pdev,
			stwuct mtmips_pmx_gwoup *data);

#endif
