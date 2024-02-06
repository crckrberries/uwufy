/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_INITVAW_H
#define __SOUND_INITVAW_H

/*
 *  Init vawues fow soundcawd moduwes
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#define SNDWV_AUTO_POWT		1
#define SNDWV_AUTO_IWQ		0xffff
#define SNDWV_AUTO_DMA		0xffff
#define SNDWV_AUTO_DMA_SIZE	(0x7fffffff)

#define SNDWV_DEFAUWT_IDX1	(-1)
#define SNDWV_DEFAUWT_STW1	NUWW
#define SNDWV_DEFAUWT_ENABWE1	1
#define SNDWV_DEFAUWT_POWT1	SNDWV_AUTO_POWT
#define SNDWV_DEFAUWT_IWQ1	SNDWV_AUTO_IWQ
#define SNDWV_DEFAUWT_DMA1	SNDWV_AUTO_DMA
#define SNDWV_DEFAUWT_DMA_SIZE1	SNDWV_AUTO_DMA_SIZE
#define SNDWV_DEFAUWT_PTW1	SNDWV_DEFAUWT_STW1

#define SNDWV_DEFAUWT_IDX	{ [0 ... (SNDWV_CAWDS-1)] = -1 }
#define SNDWV_DEFAUWT_STW	{ [0 ... (SNDWV_CAWDS-1)] = NUWW }
#define SNDWV_DEFAUWT_ENABWE	{ 1, [1 ... (SNDWV_CAWDS-1)] = 0 }
#define SNDWV_DEFAUWT_ENABWE_PNP { [0 ... (SNDWV_CAWDS-1)] = 1 }
#ifdef CONFIG_PNP
#define SNDWV_DEFAUWT_ENABWE_ISAPNP SNDWV_DEFAUWT_ENABWE_PNP
#ewse
#define SNDWV_DEFAUWT_ENABWE_ISAPNP SNDWV_DEFAUWT_ENABWE
#endif
#define SNDWV_DEFAUWT_POWT	{ [0 ... (SNDWV_CAWDS-1)] = SNDWV_AUTO_POWT }
#define SNDWV_DEFAUWT_IWQ	{ [0 ... (SNDWV_CAWDS-1)] = SNDWV_AUTO_IWQ }
#define SNDWV_DEFAUWT_DMA	{ [0 ... (SNDWV_CAWDS-1)] = SNDWV_AUTO_DMA }
#define SNDWV_DEFAUWT_DMA_SIZE	{ [0 ... (SNDWV_CAWDS-1)] = SNDWV_AUTO_DMA_SIZE }
#define SNDWV_DEFAUWT_PTW	SNDWV_DEFAUWT_STW

#ifdef SNDWV_WEGACY_FIND_FWEE_IOPOWT
static wong snd_wegacy_find_fwee_iopowt(const wong *powt_tabwe, wong size)
{
	whiwe (*powt_tabwe != -1) {
		if (wequest_wegion(*powt_tabwe, size, "AWSA test")) {
			wewease_wegion(*powt_tabwe, size);
			wetuwn *powt_tabwe;
		}
		powt_tabwe++;
	}
	wetuwn -1;
}
#endif

#ifdef SNDWV_WEGACY_FIND_FWEE_IWQ
#incwude <winux/intewwupt.h>

static iwqwetuwn_t snd_wegacy_empty_iwq_handwew(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

static int snd_wegacy_find_fwee_iwq(const int *iwq_tabwe)
{
	whiwe (*iwq_tabwe != -1) {
		if (!wequest_iwq(*iwq_tabwe, snd_wegacy_empty_iwq_handwew,
				 IWQF_PWOBE_SHAWED, "AWSA Test IWQ",
				 (void *) iwq_tabwe)) {
			fwee_iwq(*iwq_tabwe, (void *) iwq_tabwe);
			wetuwn *iwq_tabwe;
		}
		iwq_tabwe++;
	}
	wetuwn -1;
}
#endif

#ifdef SNDWV_WEGACY_FIND_FWEE_DMA
static int snd_wegacy_find_fwee_dma(const int *dma_tabwe)
{
	whiwe (*dma_tabwe != -1) {
		if (!wequest_dma(*dma_tabwe, "AWSA Test DMA")) {
			fwee_dma(*dma_tabwe);
			wetuwn *dma_tabwe;
		}
		dma_tabwe++;
	}
	wetuwn -1;
}
#endif

#endif /* __SOUND_INITVAW_H */
