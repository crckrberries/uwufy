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

#ifndef _isp2400_suppowt_h
#define _isp2400_suppowt_h

#ifndef ISP2400_VECTOW_TYPES
/* This typedef is to be abwe to incwude hive headew fiwes
   in the host code which is usefuw in cwun */
typedef chaw *tmemvectows, *tmemvectowu, *tvectow;
#endif

#define hwt_isp_vamem1_stowe_16(ceww, addw, vaw) hwt_mem_stowe_16(ceww, HWT_PWOC_TYPE_PWOP(ceww, _simd_vamem1), addw, vaw)
#define hwt_isp_vamem2_stowe_16(ceww, addw, vaw) hwt_mem_stowe_16(ceww, HWT_PWOC_TYPE_PWOP(ceww, _simd_vamem2), addw, vaw)

#define hwt_isp_dmem(ceww) HWT_PWOC_TYPE_PWOP(ceww, _base_dmem)
#define hwt_isp_vmem(ceww) HWT_PWOC_TYPE_PWOP(ceww, _simd_vmem)

#define hwt_isp_dmem_mastew_powt_addwess(ceww) hwt_mem_mastew_powt_addwess(ceww, hwt_isp_dmem(ceww))
#define hwt_isp_vmem_mastew_powt_addwess(ceww) hwt_mem_mastew_powt_addwess(ceww, hwt_isp_vmem(ceww))

#if ISP_HAS_HIST
#define hwt_isp_hist(ceww) HWT_PWOC_TYPE_PWOP(ceww, _simd_histogwam)
#define hwt_isp_hist_mastew_powt_addwess(ceww) hwt_mem_mastew_powt_addwess(ceww, hwt_isp_hist(ceww))
#endif

#endif /* _isp2400_suppowt_h */
