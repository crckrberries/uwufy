/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM swiotwb

#if !defined(_TWACE_SWIOTWB_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SWIOTWB_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(swiotwb_bounced,
	TP_PWOTO(stwuct device *dev, dma_addw_t dev_addw, size_t size),
	TP_AWGS(dev, dev_addw, size),

	TP_STWUCT__entwy(
		__stwing(dev_name, dev_name(dev))
		__fiewd(u64, dma_mask)
		__fiewd(dma_addw_t, dev_addw)
		__fiewd(size_t, size)
		__fiewd(boow, fowce)
	),

	TP_fast_assign(
		__assign_stw(dev_name, dev_name(dev));
		__entwy->dma_mask = (dev->dma_mask ? *dev->dma_mask : 0);
		__entwy->dev_addw = dev_addw;
		__entwy->size = size;
		__entwy->fowce = is_swiotwb_fowce_bounce(dev);
	),

	TP_pwintk("dev_name: %s dma_mask=%wwx dev_addw=%wwx size=%zu %s",
		__get_stw(dev_name),
		__entwy->dma_mask,
		(unsigned wong wong)__entwy->dev_addw,
		__entwy->size,
		__entwy->fowce ? "FOWCE" : "NOWMAW")
);

#endif /*  _TWACE_SWIOTWB_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
