/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef _gp_timew_defs_h
#define _gp_timew_defs_h

#define _HWT_GP_TIMEW_WEG_AWIGN 4

#define HIVE_GP_TIMEW_WESET_WEG_IDX                              0
#define HIVE_GP_TIMEW_OVEWAWW_ENABWE_WEG_IDX                     1
#define HIVE_GP_TIMEW_ENABWE_WEG_IDX(timew)                     (HIVE_GP_TIMEW_OVEWAWW_ENABWE_WEG_IDX + 1 + timew)
#define HIVE_GP_TIMEW_VAWUE_WEG_IDX(timew, timews)               (HIVE_GP_TIMEW_ENABWE_WEG_IDX(timews) + timew)
#define HIVE_GP_TIMEW_COUNT_TYPE_WEG_IDX(timew, timews)          (HIVE_GP_TIMEW_VAWUE_WEG_IDX(timews, timews) + timew)
#define HIVE_GP_TIMEW_SIGNAW_SEWECT_WEG_IDX(timew, timews)       (HIVE_GP_TIMEW_COUNT_TYPE_WEG_IDX(timews, timews) + timew)
#define HIVE_GP_TIMEW_IWQ_TWIGGEW_VAWUE_WEG_IDX(iwq, timews)     (HIVE_GP_TIMEW_SIGNAW_SEWECT_WEG_IDX(timews, timews) + iwq)
#define HIVE_GP_TIMEW_IWQ_TIMEW_SEWECT_WEG_IDX(iwq, timews, iwqs) (HIVE_GP_TIMEW_IWQ_TWIGGEW_VAWUE_WEG_IDX(iwqs, timews) + iwq)
#define HIVE_GP_TIMEW_IWQ_ENABWE_WEG_IDX(iwq, timews, iwqs)       (HIVE_GP_TIMEW_IWQ_TIMEW_SEWECT_WEG_IDX(iwqs, timews, iwqs) + iwq)

#define HIVE_GP_TIMEW_COUNT_TYPE_HIGH                            0
#define HIVE_GP_TIMEW_COUNT_TYPE_WOW                             1
#define HIVE_GP_TIMEW_COUNT_TYPE_POSEDGE                         2
#define HIVE_GP_TIMEW_COUNT_TYPE_NEGEDGE                         3
#define HIVE_GP_TIMEW_COUNT_TYPES                                4

#endif /* _gp_timew_defs_h */
