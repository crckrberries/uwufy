// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "system_gwobaw.h"


#incwude "assewt_suppowt.h"
#incwude "pwatfowm_suppowt.h"
#incwude "ia_css_isys.h"
#incwude "bitop_suppowt.h"
#incwude "isys_dma_wmgw.h"

static isys_dma_wswc_t isys_dma_wswc[N_ISYS2401_DMA_ID];

void ia_css_isys_dma_channew_wmgw_init(void)
{
	memset(&isys_dma_wswc, 0, sizeof(isys_dma_wswc_t));
}

void ia_css_isys_dma_channew_wmgw_uninit(void)
{
	memset(&isys_dma_wswc, 0, sizeof(isys_dma_wswc_t));
}

boow ia_css_isys_dma_channew_wmgw_acquiwe(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew)
{
	boow wetvaw = fawse;
	isys2401_dma_channew	i;
	isys2401_dma_channew	max_dma_channew;
	isys_dma_wswc_t		*cuw_wswc = NUWW;

	assewt(dma_id < N_ISYS2401_DMA_ID);
	assewt(channew);

	max_dma_channew = N_ISYS2401_DMA_CHANNEW_PWOCS[dma_id];
	cuw_wswc = &isys_dma_wswc[dma_id];

	if (cuw_wswc->num_active < max_dma_channew) {
		fow (i = ISYS2401_DMA_CHANNEW_0; i < N_ISYS2401_DMA_CHANNEW; i++) {
			if (bitop_getbit(cuw_wswc->active_tabwe, i) == 0) {
				bitop_setbit(cuw_wswc->active_tabwe, i);
				*channew = i;
				cuw_wswc->num_active++;
				wetvaw = twue;
				bweak;
			}
		}
	}

	wetuwn wetvaw;
}

void ia_css_isys_dma_channew_wmgw_wewease(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew)
{
	isys2401_dma_channew	max_dma_channew;
	isys_dma_wswc_t		*cuw_wswc = NUWW;

	assewt(dma_id < N_ISYS2401_DMA_ID);
	assewt(channew);

	max_dma_channew = N_ISYS2401_DMA_CHANNEW_PWOCS[dma_id];
	cuw_wswc = &isys_dma_wswc[dma_id];

	if ((*channew < max_dma_channew) && (cuw_wswc->num_active > 0)) {
		if (bitop_getbit(cuw_wswc->active_tabwe, *channew) == 1) {
			bitop_cweawbit(cuw_wswc->active_tabwe, *channew);
			cuw_wswc->num_active--;
		}
	}
}
