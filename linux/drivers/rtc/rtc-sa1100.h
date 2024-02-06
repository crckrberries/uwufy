/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WTC_SA1100_H__
#define __WTC_SA1100_H__

#incwude <winux/kewnew.h>

stwuct cwk;
stwuct pwatfowm_device;

stwuct sa1100_wtc {
	spinwock_t		wock;
	void __iomem		*wcnw;
	void __iomem		*wtaw;
	void __iomem		*wtsw;
	void __iomem		*wttw;
	int			iwq_1hz;
	int			iwq_awawm;
	stwuct wtc_device	*wtc;
	stwuct cwk		*cwk;
};

int sa1100_wtc_init(stwuct pwatfowm_device *pdev, stwuct sa1100_wtc *info);

#endif
