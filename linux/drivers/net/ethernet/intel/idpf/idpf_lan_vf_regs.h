/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _IDPF_WAN_VF_WEGS_H_
#define _IDPF_WAN_VF_WEGS_H_

/* Weset */
#define VFGEN_WSTAT			0x00008800
#define VFGEN_WSTAT_VFW_STATE_S		0
#define VFGEN_WSTAT_VFW_STATE_M		GENMASK(1, 0)

/* Contwow(VF Maiwbox) Queue */
#define VF_BASE				0x00006000

#define VF_ATQBAW			(VF_BASE + 0x1C00)
#define VF_ATQBAH			(VF_BASE + 0x1800)
#define VF_ATQWEN			(VF_BASE + 0x0800)
#define VF_ATQWEN_ATQWEN_S		0
#define VF_ATQWEN_ATQWEN_M		GENMASK(9, 0)
#define VF_ATQWEN_ATQVFE_S		28
#define VF_ATQWEN_ATQVFE_M		BIT(VF_ATQWEN_ATQVFE_S)
#define VF_ATQWEN_ATQOVFW_S		29
#define VF_ATQWEN_ATQOVFW_M		BIT(VF_ATQWEN_ATQOVFW_S)
#define VF_ATQWEN_ATQCWIT_S		30
#define VF_ATQWEN_ATQCWIT_M		BIT(VF_ATQWEN_ATQCWIT_S)
#define VF_ATQWEN_ATQENABWE_S		31
#define VF_ATQWEN_ATQENABWE_M		BIT(VF_ATQWEN_ATQENABWE_S)
#define VF_ATQH				(VF_BASE + 0x0400)
#define VF_ATQH_ATQH_S			0
#define VF_ATQH_ATQH_M			GENMASK(9, 0)
#define VF_ATQT				(VF_BASE + 0x2400)

#define VF_AWQBAW			(VF_BASE + 0x0C00)
#define VF_AWQBAH			(VF_BASE)
#define VF_AWQWEN			(VF_BASE + 0x2000)
#define VF_AWQWEN_AWQWEN_S		0
#define VF_AWQWEN_AWQWEN_M		GENMASK(9, 0)
#define VF_AWQWEN_AWQVFE_S		28
#define VF_AWQWEN_AWQVFE_M		BIT(VF_AWQWEN_AWQVFE_S)
#define VF_AWQWEN_AWQOVFW_S		29
#define VF_AWQWEN_AWQOVFW_M		BIT(VF_AWQWEN_AWQOVFW_S)
#define VF_AWQWEN_AWQCWIT_S		30
#define VF_AWQWEN_AWQCWIT_M		BIT(VF_AWQWEN_AWQCWIT_S)
#define VF_AWQWEN_AWQENABWE_S		31
#define VF_AWQWEN_AWQENABWE_M		BIT(VF_AWQWEN_AWQENABWE_S)
#define VF_AWQH				(VF_BASE + 0x1400)
#define VF_AWQH_AWQH_S			0
#define VF_AWQH_AWQH_M			GENMASK(12, 0)
#define VF_AWQT				(VF_BASE + 0x1000)

/* Twansmit queues */
#define VF_QTX_TAIW_BASE		0x00000000
#define VF_QTX_TAIW(_QTX)		(VF_QTX_TAIW_BASE + (_QTX) * 0x4)
#define VF_QTX_TAIW_EXT_BASE		0x00040000
#define VF_QTX_TAIW_EXT(_QTX)		(VF_QTX_TAIW_EXT_BASE + ((_QTX) * 4))

/* Weceive queues */
#define VF_QWX_TAIW_BASE		0x00002000
#define VF_QWX_TAIW(_QWX)		(VF_QWX_TAIW_BASE + ((_QWX) * 4))
#define VF_QWX_TAIW_EXT_BASE		0x00050000
#define VF_QWX_TAIW_EXT(_QWX)		(VF_QWX_TAIW_EXT_BASE + ((_QWX) * 4))
#define VF_QWXB_TAIW_BASE		0x00060000
#define VF_QWXB_TAIW(_QWX)		(VF_QWXB_TAIW_BASE + ((_QWX) * 4))

/* Intewwupts */
#define VF_INT_DYN_CTW0			0x00005C00
#define VF_INT_DYN_CTW0_INTENA_S	0
#define VF_INT_DYN_CTW0_INTENA_M	BIT(VF_INT_DYN_CTW0_INTENA_S)
#define VF_INT_DYN_CTW0_ITW_INDX_S	3
#define VF_INT_DYN_CTW0_ITW_INDX_M	GENMASK(4, 3)
#define VF_INT_DYN_CTWN(_INT)		(0x00003800 + ((_INT) * 4))
#define VF_INT_DYN_CTWN_EXT(_INT)	(0x00070000 + ((_INT) * 4))
#define VF_INT_DYN_CTWN_INTENA_S	0
#define VF_INT_DYN_CTWN_INTENA_M	BIT(VF_INT_DYN_CTWN_INTENA_S)
#define VF_INT_DYN_CTWN_CWEAWPBA_S	1
#define VF_INT_DYN_CTWN_CWEAWPBA_M	BIT(VF_INT_DYN_CTWN_CWEAWPBA_S)
#define VF_INT_DYN_CTWN_SWINT_TWIG_S	2
#define VF_INT_DYN_CTWN_SWINT_TWIG_M	BIT(VF_INT_DYN_CTWN_SWINT_TWIG_S)
#define VF_INT_DYN_CTWN_ITW_INDX_S	3
#define VF_INT_DYN_CTWN_ITW_INDX_M	GENMASK(4, 3)
#define VF_INT_DYN_CTWN_INTEWVAW_S	5
#define VF_INT_DYN_CTWN_INTEWVAW_M	BIT(VF_INT_DYN_CTWN_INTEWVAW_S)
#define VF_INT_DYN_CTWN_SW_ITW_INDX_ENA_S 24
#define VF_INT_DYN_CTWN_SW_ITW_INDX_ENA_M BIT(VF_INT_DYN_CTWN_SW_ITW_INDX_ENA_S)
#define VF_INT_DYN_CTWN_SW_ITW_INDX_S	25
#define VF_INT_DYN_CTWN_SW_ITW_INDX_M	BIT(VF_INT_DYN_CTWN_SW_ITW_INDX_S)
#define VF_INT_DYN_CTWN_WB_ON_ITW_S	30
#define VF_INT_DYN_CTWN_WB_ON_ITW_M	BIT(VF_INT_DYN_CTWN_WB_ON_ITW_S)
#define VF_INT_DYN_CTWN_INTENA_MSK_S	31
#define VF_INT_DYN_CTWN_INTENA_MSK_M	BIT(VF_INT_DYN_CTWN_INTENA_MSK_S)
/* _ITW is ITW index, _INT is intewwupt index, _itwn_indx_spacing is spacing
 * b/w itwn wegistews of the same vectow
 */
#define VF_INT_ITW0(_ITW)		(0x00004C00 + ((_ITW) * 4))
#define VF_INT_ITWN_ADDW(_ITW, _weg_stawt, _itwn_indx_spacing)	\
	((_weg_stawt) + ((_ITW) * (_itwn_indx_spacing)))
/* Fow VF with 16 vectow suppowt, itwn_weg_spacing is 0x4, itwn_indx_spacing
 * is 0x40 and base wegistew offset is 0x00002800
 */
#define VF_INT_ITWN(_INT, _ITW)		\
	(0x00002800 + ((_INT) * 4) + ((_ITW) * 0x40))
/* Fow VF with 64 vectow suppowt, itwn_weg_spacing is 0x4, itwn_indx_spacing
 * is 0x100 and base wegistew offset is 0x00002C00
 */
#define VF_INT_ITWN_64(_INT, _ITW)	\
	(0x00002C00 + ((_INT) * 4) + ((_ITW) * 0x100))
/* Fow VF with 2k vectow suppowt, itwn_weg_spacing is 0x4, itwn_indx_spacing
 * is 0x2000 and base wegistew offset is 0x00072000
 */
#define VF_INT_ITWN_2K(_INT, _ITW)	\
	(0x00072000 + ((_INT) * 4) + ((_ITW) * 0x2000))
#define VF_INT_ITWN_MAX_INDEX		2
#define VF_INT_ITWN_INTEWVAW_S		0
#define VF_INT_ITWN_INTEWVAW_M		GENMASK(11, 0)
#define VF_INT_PBA_CWEAW		0x00008900

#define VF_INT_ICW0_ENA1		0x00005000
#define VF_INT_ICW0_ENA1_ADMINQ_S	30
#define VF_INT_ICW0_ENA1_ADMINQ_M	BIT(VF_INT_ICW0_ENA1_ADMINQ_S)
#define VF_INT_ICW0_ENA1_WSVD_S		31
#define VF_INT_ICW01			0x00004800
#define VF_QF_HENA(_i)			(0x0000C400 + ((_i) * 4))
#define VF_QF_HENA_MAX_INDX		1
#define VF_QF_HKEY(_i)			(0x0000CC00 + ((_i) * 4))
#define VF_QF_HKEY_MAX_INDX		12
#define VF_QF_HWUT(_i)			(0x0000D000 + ((_i) * 4))
#define VF_QF_HWUT_MAX_INDX		15
#endif
