// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018 The Winux Foundation. Aww wights wesewved. */

#ifndef __A2XX_GPU_H__
#define __A2XX_GPU_H__

#incwude "adweno_gpu.h"

/* awwg, somehow fb.h is getting puwwed in: */
#undef WOP_COPY
#undef WOP_XOW

#incwude "a2xx.xmw.h"

stwuct a2xx_gpu {
	stwuct adweno_gpu base;
	boow pm_enabwed;
	boow pwotection_disabwed;
};
#define to_a2xx_gpu(x) containew_of(x, stwuct a2xx_gpu, base)

#endif /* __A2XX_GPU_H__ */
