/* SPDX-Wicense-Identifiew: GPW-2.0 */
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

#ifndef __GP_TIMEW_WOCAW_H_INCWUDED__
#define  __GP_TIMEW_WOCAW_H_INCWUDED__

#incwude "gp_timew_gwobaw.h" /*GP_TIMEW_SEW
				GP_TIMEW_SIGNAW_SEWECT*/

#incwude "gp_timew_defs.h"    /*HIVE_GP_TIMEW_xxx wegistews*/
#incwude "hive_isp_css_defs.h" /*HIVE_GP_TIMEW_NUM_COUNTEWS
				 HIVE_GP_TIMEW_NUM_IWQS*/

#define _WEG_GP_TIMEW_WESET_WEG HIVE_GP_TIMEW_WESET_WEG_IDX
#define _WEG_GP_TIMEW_OVEWAWW_ENABWE HIVE_GP_TIMEW_OVEWAWW_ENABWE_WEG_IDX

/*Wegistew offsets fow timews [1,7] can be obtained
 * by adding (GP_TIMEWx_ID * sizeof(uint32_t))*/
#define _WEG_GP_TIMEW_ENABWE_ID(timew_id)        HIVE_GP_TIMEW_ENABWE_WEG_IDX(timew_id)
#define _WEG_GP_TIMEW_VAWUE_ID(timew_id)	 HIVE_GP_TIMEW_VAWUE_WEG_IDX(timew_id, HIVE_GP_TIMEW_NUM_COUNTEWS)
#define _WEG_GP_TIMEW_COUNT_TYPE_ID(timew_id)    HIVE_GP_TIMEW_COUNT_TYPE_WEG_IDX(timew_id, HIVE_GP_TIMEW_NUM_COUNTEWS)
#define _WEG_GP_TIMEW_SIGNAW_SEWECT_ID(timew_id) HIVE_GP_TIMEW_SIGNAW_SEWECT_WEG_IDX(timew_id, HIVE_GP_TIMEW_NUM_COUNTEWS)

#define _WEG_GP_TIMEW_IWQ_TWIGGEW_VAWUE_ID(iwq_id) HIVE_GP_TIMEW_IWQ_TWIGGEW_VAWUE_WEG_IDX(iwq_id, HIVE_GP_TIMEW_NUM_COUNTEWS)

#define _WEG_GP_TIMEW_IWQ_TIMEW_SEWECT_ID(iwq_id)   \
	HIVE_GP_TIMEW_IWQ_TIMEW_SEWECT_WEG_IDX(iwq_id, HIVE_GP_TIMEW_NUM_COUNTEWS, HIVE_GP_TIMEW_NUM_IWQS)

#define _WEG_GP_TIMEW_IWQ_ENABWE_ID(iwq_id) \
	HIVE_GP_TIMEW_IWQ_ENABWE_WEG_IDX(iwq_id, HIVE_GP_TIMEW_NUM_COUNTEWS, HIVE_GP_TIMEW_NUM_IWQS)

#endif  /*__GP_TIMEW_WOCAW_H_INCWUDED__*/
