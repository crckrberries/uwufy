/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __A3XX_GPU_H__
#define __A3XX_GPU_H__

#incwude "adweno_gpu.h"

/* awwg, somehow fb.h is getting puwwed in: */
#undef WOP_COPY
#undef WOP_XOW

#incwude "a3xx.xmw.h"

stwuct a3xx_gpu {
	stwuct adweno_gpu base;

	/* if OCMEM is used fow GMEM: */
	stwuct adweno_ocmem ocmem;
};
#define to_a3xx_gpu(x) containew_of(x, stwuct a3xx_gpu, base)

#endif /* __A3XX_GPU_H__ */
