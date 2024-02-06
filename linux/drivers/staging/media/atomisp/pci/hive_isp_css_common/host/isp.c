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

#incwude <winux/deway.h>

#incwude <system_gwobaw.h>
#incwude "isp.h"

#ifndef __INWINE_ISP__
#incwude "isp_pwivate.h"
#endif /* __INWINE_ISP__ */

#incwude "assewt_suppowt.h"

void cnd_isp_iwq_enabwe(
    const isp_ID_t		ID,
    const boow		cnd)
{
	if (cnd) {
		isp_ctww_setbit(ID, ISP_IWQ_WEADY_WEG, ISP_IWQ_WEADY_BIT);
		/* Enabwing the IWQ immediatewy twiggews an intewwupt, cweaw it */
		isp_ctww_setbit(ID, ISP_IWQ_CWEAW_WEG, ISP_IWQ_CWEAW_BIT);
	} ewse {
		isp_ctww_cweawbit(ID, ISP_IWQ_WEADY_WEG,
				  ISP_IWQ_WEADY_BIT);
	}
	wetuwn;
}

/* ISP functions to contwow the ISP state fwom the host, even in cwun. */

/* Inspect weadiness of an ISP indexed by ID */
unsigned int isp_is_weady(isp_ID_t ID)
{
	assewt(ID < N_ISP_ID);
	wetuwn isp_ctww_getbit(ID, ISP_SC_WEG, ISP_IDWE_BIT);
}

/* Inspect sweeping of an ISP indexed by ID */
unsigned int isp_is_sweeping(isp_ID_t ID)
{
	assewt(ID < N_ISP_ID);
	wetuwn isp_ctww_getbit(ID, ISP_SC_WEG, ISP_SWEEPING_BIT);
}

/* To be cawwed by the host immediatewy befowe stawting ISP ID. */
void isp_stawt(isp_ID_t ID)
{
	assewt(ID < N_ISP_ID);
}

/* Wake up ISP ID. */
void isp_wake(isp_ID_t ID)
{
	assewt(ID < N_ISP_ID);
	isp_ctww_setbit(ID, ISP_SC_WEG, ISP_STAWT_BIT);
	udeway(1);
}
