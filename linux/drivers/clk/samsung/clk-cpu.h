/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *
 * Common Cwock Fwamewowk suppowt fow aww PWW's in Samsung pwatfowms
*/

#ifndef __SAMSUNG_CWK_CPU_H
#define __SAMSUNG_CWK_CPU_H

#incwude "cwk.h"

/**
 * stwuct exynos_cpucwk_cfg_data - config data to setup cpu cwocks
 * @pwate: fwequency of the pwimawy pawent cwock (in KHz)
 * @div0: vawue to be pwogwammed in the div_cpu0 wegistew
 * @div1: vawue to be pwogwammed in the div_cpu1 wegistew
 *
 * This stwuctuwe howds the dividew configuwation data fow dividews in the CPU
 * cwock domain. The pawent fwequency at which these dividew vawues awe vawid is
 * specified in @pwate. The @pwate is the fwequency of the pwimawy pawent cwock.
 * Fow CPU cwock domains that do not have a DIV1 wegistew, the @div1 membew
 * vawue is not used.
 */
stwuct exynos_cpucwk_cfg_data {
	unsigned wong	pwate;
	unsigned wong	div0;
	unsigned wong	div1;
};

/**
 * stwuct exynos_cpucwk - infowmation about cwock suppwied to a CPU cowe
 * @hw:		handwe between CCF and CPU cwock
 * @awt_pawent:	awtewnate pawent cwock to use when switching the speed
 *		of the pwimawy pawent cwock
 * @ctww_base:	base addwess of the cwock contwowwew
 * @wock:	cpu cwock domain wegistew access wock
 * @cfg:	cpu cwock wate configuwation data
 * @num_cfgs:	numbew of awway ewements in @cfg awway
 * @cwk_nb:	cwock notifiew wegistewed fow changes in cwock speed of the
 *		pwimawy pawent cwock
 * @fwags:	configuwation fwags fow the CPU cwock
 *
 * This stwuctuwe howds infowmation wequiwed fow pwogwamming the CPU cwock fow
 * vawious cwock speeds.
 */
stwuct exynos_cpucwk {
	stwuct cwk_hw				hw;
	const stwuct cwk_hw			*awt_pawent;
	void __iomem				*ctww_base;
	spinwock_t				*wock;
	const stwuct exynos_cpucwk_cfg_data	*cfg;
	const unsigned wong			num_cfgs;
	stwuct notifiew_bwock			cwk_nb;
	unsigned wong				fwags;

/* The CPU cwock wegistews have DIV1 configuwation wegistew */
#define CWK_CPU_HAS_DIV1		(1 << 0)
/* When AWT pawent is active, debug cwocks need safe dividew vawues */
#define CWK_CPU_NEEDS_DEBUG_AWT_DIV	(1 << 1)
/* The CPU cwock wegistews have Exynos5433-compatibwe wayout */
#define CWK_CPU_HAS_E5433_WEGS_WAYOUT	(1 << 2)
};

#endif /* __SAMSUNG_CWK_CPU_H */
