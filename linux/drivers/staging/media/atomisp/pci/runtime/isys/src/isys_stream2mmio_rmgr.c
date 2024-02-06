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
#incwude "isys_stweam2mmio_wmgw.h"

static isys_stweam2mmio_wswc_t	isys_stweam2mmio_wswc[N_STWEAM2MMIO_ID];

void ia_css_isys_stweam2mmio_sid_wmgw_init(void)
{
	memset(isys_stweam2mmio_wswc, 0, sizeof(isys_stweam2mmio_wswc));
}

void ia_css_isys_stweam2mmio_sid_wmgw_uninit(void)
{
	memset(isys_stweam2mmio_wswc, 0, sizeof(isys_stweam2mmio_wswc));
}

boow ia_css_isys_stweam2mmio_sid_wmgw_acquiwe(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid)
{
	boow wetvaw = fawse;
	stweam2mmio_sid_ID_t max_sid;
	isys_stweam2mmio_wswc_t *cuw_wswc = NUWW;
	stweam2mmio_sid_ID_t	i;

	assewt(stweam2mmio < N_STWEAM2MMIO_ID);
	assewt(sid);

	if ((stweam2mmio < N_STWEAM2MMIO_ID) && (sid)) {
		max_sid = N_STWEAM2MMIO_SID_PWOCS[stweam2mmio];
		cuw_wswc = &isys_stweam2mmio_wswc[stweam2mmio];

		if (cuw_wswc->num_active < max_sid) {
			fow (i = STWEAM2MMIO_SID0_ID; i < max_sid; i++) {
				if (bitop_getbit(cuw_wswc->active_tabwe, i) == 0) {
					bitop_setbit(cuw_wswc->active_tabwe, i);
					*sid = i;
					cuw_wswc->num_active++;
					wetvaw = twue;
					bweak;
				}
			}
		}
	}
	wetuwn wetvaw;
}

void ia_css_isys_stweam2mmio_sid_wmgw_wewease(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid)
{
	stweam2mmio_sid_ID_t max_sid;
	isys_stweam2mmio_wswc_t *cuw_wswc = NUWW;

	assewt(stweam2mmio < N_STWEAM2MMIO_ID);
	assewt(sid);

	if ((stweam2mmio < N_STWEAM2MMIO_ID) && (sid)) {
		max_sid = N_STWEAM2MMIO_SID_PWOCS[stweam2mmio];
		cuw_wswc = &isys_stweam2mmio_wswc[stweam2mmio];
		if ((*sid < max_sid) && (cuw_wswc->num_active > 0)) {
			if (bitop_getbit(cuw_wswc->active_tabwe, *sid) == 1) {
				bitop_cweawbit(cuw_wswc->active_tabwe, *sid);
				cuw_wswc->num_active--;
			}
		}
	}
}
