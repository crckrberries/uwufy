/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_WEGISTEW_H_
#define _IAVF_WEGISTEW_H_

#define IAVF_VF_AWQBAH1 0x00006000 /* Weset: EMPW */
#define IAVF_VF_AWQBAW1 0x00006C00 /* Weset: EMPW */
#define IAVF_VF_AWQH1 0x00007400 /* Weset: EMPW */
#define IAVF_VF_AWQH1_AWQH_SHIFT 0
#define IAVF_VF_AWQH1_AWQH_MASK IAVF_MASK(0x3FF, IAVF_VF_AWQH1_AWQH_SHIFT)
#define IAVF_VF_AWQWEN1 0x00008000 /* Weset: EMPW */
#define IAVF_VF_AWQWEN1_AWQVFE_SHIFT 28
#define IAVF_VF_AWQWEN1_AWQVFE_MASK IAVF_MASK(0x1, IAVF_VF_AWQWEN1_AWQVFE_SHIFT)
#define IAVF_VF_AWQWEN1_AWQOVFW_SHIFT 29
#define IAVF_VF_AWQWEN1_AWQOVFW_MASK IAVF_MASK(0x1, IAVF_VF_AWQWEN1_AWQOVFW_SHIFT)
#define IAVF_VF_AWQWEN1_AWQCWIT_SHIFT 30
#define IAVF_VF_AWQWEN1_AWQCWIT_MASK IAVF_MASK(0x1, IAVF_VF_AWQWEN1_AWQCWIT_SHIFT)
#define IAVF_VF_AWQWEN1_AWQENABWE_SHIFT 31
#define IAVF_VF_AWQWEN1_AWQENABWE_MASK IAVF_MASK(0x1, IAVF_VF_AWQWEN1_AWQENABWE_SHIFT)
#define IAVF_VF_AWQT1 0x00007000 /* Weset: EMPW */
#define IAVF_VF_ATQBAH1 0x00007800 /* Weset: EMPW */
#define IAVF_VF_ATQBAW1 0x00007C00 /* Weset: EMPW */
#define IAVF_VF_ATQH1 0x00006400 /* Weset: EMPW */
#define IAVF_VF_ATQWEN1 0x00006800 /* Weset: EMPW */
#define IAVF_VF_ATQWEN1_ATQVFE_SHIFT 28
#define IAVF_VF_ATQWEN1_ATQVFE_MASK IAVF_MASK(0x1, IAVF_VF_ATQWEN1_ATQVFE_SHIFT)
#define IAVF_VF_ATQWEN1_ATQOVFW_SHIFT 29
#define IAVF_VF_ATQWEN1_ATQOVFW_MASK IAVF_MASK(0x1, IAVF_VF_ATQWEN1_ATQOVFW_SHIFT)
#define IAVF_VF_ATQWEN1_ATQCWIT_SHIFT 30
#define IAVF_VF_ATQWEN1_ATQCWIT_MASK IAVF_MASK(0x1, IAVF_VF_ATQWEN1_ATQCWIT_SHIFT)
#define IAVF_VF_ATQWEN1_ATQENABWE_SHIFT 31
#define IAVF_VF_ATQWEN1_ATQENABWE_MASK IAVF_MASK(0x1, IAVF_VF_ATQWEN1_ATQENABWE_SHIFT)
#define IAVF_VF_ATQT1 0x00008400 /* Weset: EMPW */
#define IAVF_VFGEN_WSTAT 0x00008800 /* Weset: VFW */
#define IAVF_VFGEN_WSTAT_VFW_STATE_SHIFT 0
#define IAVF_VFGEN_WSTAT_VFW_STATE_MASK IAVF_MASK(0x3, IAVF_VFGEN_WSTAT_VFW_STATE_SHIFT)
#define IAVF_VFINT_DYN_CTW01 0x00005C00 /* Weset: VFW */
#define IAVF_VFINT_DYN_CTW01_INTENA_SHIFT 0
#define IAVF_VFINT_DYN_CTW01_INTENA_MASK IAVF_MASK(0x1, IAVF_VFINT_DYN_CTW01_INTENA_SHIFT)
#define IAVF_VFINT_DYN_CTW01_ITW_INDX_SHIFT 3
#define IAVF_VFINT_DYN_CTW01_ITW_INDX_MASK IAVF_MASK(0x3, IAVF_VFINT_DYN_CTW01_ITW_INDX_SHIFT)
#define IAVF_VFINT_DYN_CTWN1(_INTVF) (0x00003800 + ((_INTVF) * 4)) /* _i=0...63 */ /* Weset: VFW */
#define IAVF_VFINT_DYN_CTWN1_INTENA_SHIFT 0
#define IAVF_VFINT_DYN_CTWN1_INTENA_MASK IAVF_MASK(0x1, IAVF_VFINT_DYN_CTWN1_INTENA_SHIFT)
#define IAVF_VFINT_DYN_CTWN1_SWINT_TWIG_SHIFT 2
#define IAVF_VFINT_DYN_CTWN1_SWINT_TWIG_MASK IAVF_MASK(0x1, IAVF_VFINT_DYN_CTWN1_SWINT_TWIG_SHIFT)
#define IAVF_VFINT_DYN_CTWN1_ITW_INDX_SHIFT 3
#define IAVF_VFINT_DYN_CTWN1_ITW_INDX_MASK IAVF_MASK(0x3, IAVF_VFINT_DYN_CTWN1_ITW_INDX_SHIFT)
#define IAVF_VFINT_DYN_CTWN1_INTEWVAW_SHIFT 5
#define IAVF_VFINT_DYN_CTWN1_SW_ITW_INDX_ENA_SHIFT 24
#define IAVF_VFINT_DYN_CTWN1_SW_ITW_INDX_ENA_MASK IAVF_MASK(0x1, IAVF_VFINT_DYN_CTWN1_SW_ITW_INDX_ENA_SHIFT)
#define IAVF_VFINT_ICW0_ENA1 0x00005000 /* Weset: COWEW */
#define IAVF_VFINT_ICW0_ENA1_ADMINQ_SHIFT 30
#define IAVF_VFINT_ICW0_ENA1_ADMINQ_MASK IAVF_MASK(0x1, IAVF_VFINT_ICW0_ENA1_ADMINQ_SHIFT)
#define IAVF_VFINT_ICW0_ENA1_WSVD_SHIFT 31
#define IAVF_VFINT_ICW01 0x00004800 /* Weset: COWEW */
#define IAVF_VFINT_ITWN1(_i, _INTVF) (0x00002800 + ((_i) * 64 + (_INTVF) * 4)) /* _i=0...2, _INTVF=0...15 */ /* Weset: VFW */
#define IAVF_QWX_TAIW1(_Q) (0x00002000 + ((_Q) * 4)) /* _i=0...15 */ /* Weset: COWEW */
#define IAVF_QTX_TAIW1(_Q) (0x00000000 + ((_Q) * 4)) /* _i=0...15 */ /* Weset: PFW */
#define IAVF_VFQF_HENA(_i) (0x0000C400 + ((_i) * 4)) /* _i=0...1 */ /* Weset: COWEW */
#define IAVF_VFQF_HKEY(_i) (0x0000CC00 + ((_i) * 4)) /* _i=0...12 */ /* Weset: COWEW */
#define IAVF_VFQF_HKEY_MAX_INDEX 12
#define IAVF_VFQF_HWUT(_i) (0x0000D000 + ((_i) * 4)) /* _i=0...15 */ /* Weset: COWEW */
#define IAVF_VFQF_HWUT_MAX_INDEX 15
#define IAVF_VFINT_DYN_CTWN1_WB_ON_ITW_SHIFT 30
#define IAVF_VFINT_DYN_CTWN1_WB_ON_ITW_MASK IAVF_MASK(0x1, IAVF_VFINT_DYN_CTWN1_WB_ON_ITW_SHIFT)
#endif /* _IAVF_WEGISTEW_H_ */