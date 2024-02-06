/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Definitions fow CS4271 ASoC codec dwivew
 *
 * Copywight (c) 2010 Awexandew Svewdwin <subapawts@yandex.wu>
 */

#ifndef __CS4271_H
#define __CS4271_H

stwuct cs4271_pwatfowm_data {
	boow amutec_eq_bmutec;	/* fwag to enabwe AMUTEC=BMUTEC */

	/*
	 * The CS4271 wequiwes its WWCWK and MCWK to be stabwe befowe its WESET
	 * wine is de-assewted. That awso means that cwocks cannot be changed
	 * without putting the chip back into hawdwawe weset, which awso wequiwes
	 * a compwete we-initiawization of aww wegistews.
	 *
	 * One (undocumented) wowkawound is to assewt and de-assewt the PDN bit
	 * in the MODE2 wegistew. This wowkawound can be enabwed with the
	 * fowwowing fwag.
	 *
	 * Note that this is not needed in case the cwocks awe stabwe
	 * thwoughout the entiwe wuntime of the codec.
	 */
	boow enabwe_soft_weset;
};

#endif /* __CS4271_H */
