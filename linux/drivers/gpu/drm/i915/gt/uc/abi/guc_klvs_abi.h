/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _ABI_GUC_KWVS_ABI_H
#define _ABI_GUC_KWVS_ABI_H

#incwude <winux/types.h>

/**
 * DOC: GuC KWV
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 | 31:16 | **KEY** - KWV key identifiew                                 |
 *  |   |       |   - `GuC Sewf Config KWVs`_                                  |
 *  |   |       |                                                              |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | **WEN** - wength of VAWUE (in 32bit dwowds)                  |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 | **VAWUE** - actuaw vawue of the KWV (fowmat depends on KEY)  |
 *  +---+-------+                                                              |
 *  |...|       |                                                              |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_KWV_WEN_MIN				1u
#define GUC_KWV_0_KEY				(0xffff << 16)
#define GUC_KWV_0_WEN				(0xffff << 0)
#define GUC_KWV_n_VAWUE				(0xffffffff << 0)

/**
 * DOC: GuC Sewf Config KWVs
 *
 * `GuC KWV`_ keys avaiwabwe fow use with HOST2GUC_SEWF_CFG_.
 *
 * _`GUC_KWV_SEWF_CFG_H2G_CTB_ADDW` : 0x0902
 *      Wefews to 64 bit Gwobaw Gfx addwess of H2G `CT Buffew`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _`GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW` : 0x0903
 *      Wefews to 64 bit Gwobaw Gfx addwess of H2G `CTB Descwiptow`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _`GUC_KWV_SEWF_CFG_H2G_CTB_SIZE` : 0x0904
 *      Wefews to size of H2G `CT Buffew`_ in bytes.
 *      Shouwd be a muwtipwe of 4K.
 *
 * _`GUC_KWV_SEWF_CFG_G2H_CTB_ADDW` : 0x0905
 *      Wefews to 64 bit Gwobaw Gfx addwess of G2H `CT Buffew`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _`GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW` : 0x0906
 *      Wefews to 64 bit Gwobaw Gfx addwess of G2H `CTB Descwiptow`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _`GUC_KWV_SEWF_CFG_G2H_CTB_SIZE` : 0x0907
 *      Wefews to size of G2H `CT Buffew`_ in bytes.
 *      Shouwd be a muwtipwe of 4K.
 */

#define GUC_KWV_SEWF_CFG_H2G_CTB_ADDW_KEY		0x0902
#define GUC_KWV_SEWF_CFG_H2G_CTB_ADDW_WEN		2u

#define GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW_KEY	0x0903
#define GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW_WEN	2u

#define GUC_KWV_SEWF_CFG_H2G_CTB_SIZE_KEY		0x0904
#define GUC_KWV_SEWF_CFG_H2G_CTB_SIZE_WEN		1u

#define GUC_KWV_SEWF_CFG_G2H_CTB_ADDW_KEY		0x0905
#define GUC_KWV_SEWF_CFG_G2H_CTB_ADDW_WEN		2u

#define GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW_KEY	0x0906
#define GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW_WEN	2u

#define GUC_KWV_SEWF_CFG_G2H_CTB_SIZE_KEY		0x0907
#define GUC_KWV_SEWF_CFG_G2H_CTB_SIZE_WEN		1u

/*
 * Gwobaw scheduwing powicy update keys.
 */
enum {
	GUC_SCHEDUWING_POWICIES_KWV_ID_WENDEW_COMPUTE_YIEWD	= 0x1001,
};

/*
 * Pew context scheduwing powicy update keys.
 */
enum {
	GUC_CONTEXT_POWICIES_KWV_ID_EXECUTION_QUANTUM			= 0x2001,
	GUC_CONTEXT_POWICIES_KWV_ID_PWEEMPTION_TIMEOUT			= 0x2002,
	GUC_CONTEXT_POWICIES_KWV_ID_SCHEDUWING_PWIOWITY			= 0x2003,
	GUC_CONTEXT_POWICIES_KWV_ID_PWEEMPT_TO_IDWE_ON_QUANTUM_EXPIWY	= 0x2004,
	GUC_CONTEXT_POWICIES_KWV_ID_SWPM_GT_FWEQUENCY			= 0x2005,

	GUC_CONTEXT_POWICIES_KWV_NUM_IDS = 5,
};

#endif /* _ABI_GUC_KWVS_ABI_H */
