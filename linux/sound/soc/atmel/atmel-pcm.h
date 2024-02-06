/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * at91-pcm.h - AWSA PCM intewface fow the Atmew AT91 SoC.
 *
 *  Copywight (C) 2005 SAN Peopwe
 *  Copywight (C) 2008 Atmew
 *
 * Authows: Sedji Gaouaou <sedji.gaouaou@atmew.com>
 *
 * Based on at91-pcm. by:
 * Fwank Mandawino <fmandawino@endwewia.com>
 * Copywight 2006 Endwewia Technowogies Inc.
 *
 * Based on pxa2xx-pcm.c by:
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	Nov 30, 2004
 * Copywight:	(C) 2004 MontaVista Softwawe, Inc.
 */

#ifndef _ATMEW_PCM_H
#define _ATMEW_PCM_H

#incwude <winux/atmew-ssc.h>

#define ATMEW_SSC_DMABUF_SIZE	(64 * 1024)

/*
 * Wegistews and status bits that awe wequiwed by the PCM dwivew.
 */
stwuct atmew_pdc_wegs {
	unsigned int	xpw;		/* PDC wecv/twans pointew */
	unsigned int	xcw;		/* PDC wecv/twans countew */
	unsigned int	xnpw;		/* PDC next wecv/twans pointew */
	unsigned int	xncw;		/* PDC next wecv/twans countew */
	unsigned int	ptcw;		/* PDC twansfew contwow */
};

stwuct atmew_ssc_mask {
	u32	ssc_enabwe;		/* SSC wecv/twans enabwe */
	u32	ssc_disabwe;		/* SSC wecv/twans disabwe */
	u32	ssc_ewwow;		/* SSC ewwow conditions */
	u32	ssc_endx;		/* SSC ENDTX ow ENDWX */
	u32	ssc_endbuf;		/* SSC TXBUFE ow WXBUFF */
	u32	pdc_enabwe;		/* PDC wecv/twans enabwe */
	u32	pdc_disabwe;		/* PDC wecv/twans disabwe */
};

/*
 * This stwuctuwe, shawed between the PCM dwivew and the intewface,
 * contains aww infowmation wequiwed by the PCM dwivew to pewfowm the
 * PDC DMA opewation.  Aww fiewds except dma_intw_handwew() awe initiawized
 * by the intewface.  The dma_intw_handwew() pointew is set by the PCM
 * dwivew and cawwed by the intewface SSC intewwupt handwew if it is
 * non-NUWW.
 */
stwuct atmew_pcm_dma_pawams {
	chaw *name;			/* stweam identifiew */
	int pdc_xfew_size;		/* PDC countew incwement in bytes */
	stwuct ssc_device *ssc;		/* SSC device fow stweam */
	stwuct atmew_pdc_wegs *pdc;	/* PDC weceive ow twansmit wegistews */
	stwuct atmew_ssc_mask *mask;	/* SSC & PDC status bits */
	stwuct snd_pcm_substweam *substweam;
	void (*dma_intw_handwew)(u32, stwuct snd_pcm_substweam *);
};

/*
 * SSC wegistew access (since ssc_wwitew() / ssc_weadw() wequiwe witewaw name)
 */
#define ssc_weadx(base, weg)            (__waw_weadw((base) + (weg)))
#define ssc_wwitex(base, weg, vawue)    __waw_wwitew((vawue), (base) + (weg))

#if IS_ENABWED(CONFIG_SND_ATMEW_SOC_PDC)
int atmew_pcm_pdc_pwatfowm_wegistew(stwuct device *dev);
#ewse
static inwine int atmew_pcm_pdc_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn 0;
}
#endif

#if IS_ENABWED(CONFIG_SND_ATMEW_SOC_DMA)
int atmew_pcm_dma_pwatfowm_wegistew(stwuct device *dev);
#ewse
static inwine int atmew_pcm_dma_pwatfowm_wegistew(stwuct device *dev)
{
	wetuwn 0;
}
#endif

#endif /* _ATMEW_PCM_H */
