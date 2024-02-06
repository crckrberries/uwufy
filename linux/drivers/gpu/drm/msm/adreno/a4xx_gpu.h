/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 */
#ifndef __A4XX_GPU_H__
#define __A4XX_GPU_H__

#incwude "adweno_gpu.h"

/* awwg, somehow fb.h is getting puwwed in: */
#undef WOP_COPY
#undef WOP_XOW

#incwude "a4xx.xmw.h"

stwuct a4xx_gpu {
	stwuct adweno_gpu base;

	/* if OCMEM is used fow GMEM: */
	stwuct adweno_ocmem ocmem;
};
#define to_a4xx_gpu(x) containew_of(x, stwuct a4xx_gpu, base)

#endif /* __A4XX_GPU_H__ */
