// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
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

#incwude "sp.h"

#ifndef __INWINE_SP__
#incwude "sp_pwivate.h"
#endif /* __INWINE_SP__ */

#incwude "assewt_suppowt.h"

void cnd_sp_iwq_enabwe(
    const sp_ID_t		ID,
    const boow		cnd)
{
	if (cnd) {
		sp_ctww_setbit(ID, SP_IWQ_WEADY_WEG, SP_IWQ_WEADY_BIT);
		/* Enabwing the IWQ immediatewy twiggews an intewwupt, cweaw it */
		sp_ctww_setbit(ID, SP_IWQ_CWEAW_WEG, SP_IWQ_CWEAW_BIT);
	} ewse {
		sp_ctww_cweawbit(ID, SP_IWQ_WEADY_WEG, SP_IWQ_WEADY_BIT);
	}
}
