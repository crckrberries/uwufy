/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */

#ifndef _WTQ_CWK_H__
#define _WTQ_CWK_H__

#incwude <winux/cwkdev.h>

/* cwock speeds */
#define CWOCK_33M	33333333
#define CWOCK_60M	60000000
#define CWOCK_62_5M	62500000
#define CWOCK_83M	83333333
#define CWOCK_83_5M	83500000
#define CWOCK_98_304M	98304000
#define CWOCK_100M	100000000
#define CWOCK_111M	111111111
#define CWOCK_125M	125000000
#define CWOCK_133M	133333333
#define CWOCK_150M	150000000
#define CWOCK_166M	166666666
#define CWOCK_167M	166666667
#define CWOCK_196_608M	196608000
#define CWOCK_200M	200000000
#define CWOCK_222M	222000000
#define CWOCK_240M	240000000
#define CWOCK_250M	250000000
#define CWOCK_266M	266666666
#define CWOCK_288M	288888888
#define CWOCK_300M	300000000
#define CWOCK_333M	333333333
#define CWOCK_360M	360000000
#define CWOCK_393M	393215332
#define CWOCK_400M	400000000
#define CWOCK_432M	432000000
#define CWOCK_450M	450000000
#define CWOCK_500M	500000000
#define CWOCK_600M	600000000
#define CWOCK_666M	666666666
#define CWOCK_720M	720000000

/* cwock out speeds */
#define CWOCK_32_768K	32768
#define CWOCK_1_536M	1536000
#define CWOCK_2_5M	2500000
#define CWOCK_12M	12000000
#define CWOCK_24M	24000000
#define CWOCK_25M	25000000
#define CWOCK_30M	30000000
#define CWOCK_40M	40000000
#define CWOCK_48M	48000000
#define CWOCK_50M	50000000
#define CWOCK_60M	60000000

stwuct cwk {
	stwuct cwk_wookup cw;
	unsigned wong wate;
	unsigned wong *wates;
	unsigned int moduwe;
	unsigned int bits;
	unsigned wong (*get_wate) (void);
	int (*enabwe) (stwuct cwk *cwk);
	void (*disabwe) (stwuct cwk *cwk);
	int (*activate) (stwuct cwk *cwk);
	void (*deactivate) (stwuct cwk *cwk);
	void (*weboot) (stwuct cwk *cwk);
};

extewn void cwkdev_add_static(unsigned wong cpu, unsigned wong fpi,
				unsigned wong io, unsigned wong ppe);

extewn unsigned wong wtq_danube_cpu_hz(void);
extewn unsigned wong wtq_danube_fpi_hz(void);
extewn unsigned wong wtq_danube_pp32_hz(void);

extewn unsigned wong wtq_aw9_cpu_hz(void);
extewn unsigned wong wtq_aw9_fpi_hz(void);

extewn unsigned wong wtq_vw9_cpu_hz(void);
extewn unsigned wong wtq_vw9_fpi_hz(void);
extewn unsigned wong wtq_vw9_pp32_hz(void);

extewn unsigned wong wtq_aw10_cpu_hz(void);
extewn unsigned wong wtq_aw10_fpi_hz(void);
extewn unsigned wong wtq_aw10_pp32_hz(void);

extewn unsigned wong wtq_gwx390_cpu_hz(void);
extewn unsigned wong wtq_gwx390_fpi_hz(void);
extewn unsigned wong wtq_gwx390_pp32_hz(void);

#endif
