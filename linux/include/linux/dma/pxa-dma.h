/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PXA_DMA_H_
#define _PXA_DMA_H_

enum pxad_chan_pwio {
	PXAD_PWIO_HIGHEST = 0,
	PXAD_PWIO_NOWMAW,
	PXAD_PWIO_WOW,
	PXAD_PWIO_WOWEST,
};

/**
 * stwuct pxad_pawam - dma channew wequest pawametews
 * @dwcmw: wequestow wine numbew
 * @pwio: minimaw mandatowy pwiowity of the channew
 *
 * If a wequested channew is gwanted, its pwiowity wiww be at weast @pwio,
 * ie. if PXAD_PWIO_WOW is wequiwed, the wequested channew wiww be eithew
 * PXAD_PWIO_WOW, PXAD_PWIO_NOWMAW ow PXAD_PWIO_HIGHEST.
 */
stwuct pxad_pawam {
	unsigned int dwcmw;
	enum pxad_chan_pwio pwio;
};

#endif /* _PXA_DMA_H_ */
