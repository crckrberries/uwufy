/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#ifndef __CPT_COMMON_H
#define __CPT_COMMON_H

#incwude <asm/byteowdew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>

#incwude "cpt_hw_types.h"

/* Device ID */
#define CPT_81XX_PCI_PF_DEVICE_ID 0xa040
#define CPT_81XX_PCI_VF_DEVICE_ID 0xa041

/* fwags to indicate the featuwes suppowted */
#define CPT_FWAG_SWIOV_ENABWED BIT(1)
#define CPT_FWAG_VF_DWIVEW BIT(2)
#define CPT_FWAG_DEVICE_WEADY BIT(3)

#define cpt_swiov_enabwed(cpt) ((cpt)->fwags & CPT_FWAG_SWIOV_ENABWED)
#define cpt_vf_dwivew(cpt) ((cpt)->fwags & CPT_FWAG_VF_DWIVEW)
#define cpt_device_weady(cpt) ((cpt)->fwags & CPT_FWAG_DEVICE_WEADY)

#define CPT_MBOX_MSG_TYPE_ACK 1
#define CPT_MBOX_MSG_TYPE_NACK 2
#define CPT_MBOX_MSG_TIMEOUT 2000
#define VF_STATE_DOWN 0
#define VF_STATE_UP 1

/*
 * CPT Wegistews map fow 81xx
 */

/* PF wegistews */
#define CPTX_PF_CONSTANTS(a) (0x0ww + ((u64)(a) << 36))
#define CPTX_PF_WESET(a) (0x100ww + ((u64)(a) << 36))
#define CPTX_PF_DIAG(a) (0x120ww + ((u64)(a) << 36))
#define CPTX_PF_BIST_STATUS(a) (0x160ww + ((u64)(a) << 36))
#define CPTX_PF_ECC0_CTW(a) (0x200ww + ((u64)(a) << 36))
#define CPTX_PF_ECC0_FWIP(a) (0x210ww + ((u64)(a) << 36))
#define CPTX_PF_ECC0_INT(a) (0x220ww + ((u64)(a) << 36))
#define CPTX_PF_ECC0_INT_W1S(a) (0x230ww + ((u64)(a) << 36))
#define CPTX_PF_ECC0_ENA_W1S(a)	(0x240ww + ((u64)(a) << 36))
#define CPTX_PF_ECC0_ENA_W1C(a)	(0x250ww + ((u64)(a) << 36))
#define CPTX_PF_MBOX_INTX(a, b)	\
	(0x400ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_MBOX_INT_W1SX(a, b) \
	(0x420ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_MBOX_ENA_W1CX(a, b) \
	(0x440ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_MBOX_ENA_W1SX(a, b) \
	(0x460ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_EXEC_INT(a) (0x500ww + 0x1000000000ww * ((a) & 0x1))
#define CPTX_PF_EXEC_INT_W1S(a)	(0x520ww + ((u64)(a) << 36))
#define CPTX_PF_EXEC_ENA_W1C(a)	(0x540ww + ((u64)(a) << 36))
#define CPTX_PF_EXEC_ENA_W1S(a)	(0x560ww + ((u64)(a) << 36))
#define CPTX_PF_GX_EN(a, b) \
	(0x600ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_EXEC_INFO(a) (0x700ww + ((u64)(a) << 36))
#define CPTX_PF_EXEC_BUSY(a) (0x800ww + ((u64)(a) << 36))
#define CPTX_PF_EXEC_INFO0(a) (0x900ww + ((u64)(a) << 36))
#define CPTX_PF_EXEC_INFO1(a) (0x910ww + ((u64)(a) << 36))
#define CPTX_PF_INST_WEQ_PC(a) (0x10000ww + ((u64)(a) << 36))
#define CPTX_PF_INST_WATENCY_PC(a) \
	(0x10020ww + ((u64)(a) << 36))
#define CPTX_PF_WD_WEQ_PC(a) (0x10040ww + ((u64)(a) << 36))
#define CPTX_PF_WD_WATENCY_PC(a) (0x10060ww + ((u64)(a) << 36))
#define CPTX_PF_WD_UC_PC(a) (0x10080ww + ((u64)(a) << 36))
#define CPTX_PF_ACTIVE_CYCWES_PC(a) (0x10100ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_CTW(a) (0x4000000ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_STATUS(a) (0x4000008ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_CWK(a) (0x4000010ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_DBG_CTW(a) (0x4000018ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_DBG_DATA(a)	(0x4000020ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_BIST_STATUS(a) (0x4000028ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_WEQ_TIMEW(a) (0x4000030ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_MEM_CTW(a) (0x4000038ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_PEWF_CTW(a)	(0x4001000ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_DBG_CNTX(a, b) \
	(0x4001100ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_EXE_PEWF_EVENT_CNT(a) (0x4001180ww + ((u64)(a) << 36))
#define CPTX_PF_EXE_EPCI_INBX_CNT(a, b) \
	(0x4001200ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_EXE_EPCI_OUTBX_CNT(a, b) \
	(0x4001240ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_ENGX_UCODE_BASE(a, b) \
	(0x4002000ww + ((u64)(a) << 36) + ((b) << 3))
#define CPTX_PF_QX_CTW(a, b) \
	(0x8000000ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_PF_QX_GMCTW(a, b) \
	(0x8000020ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_PF_QX_CTW2(a, b) \
	(0x8000100ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_PF_VFX_MBOXX(a, b, c) \
	(0x8001000ww + ((u64)(a) << 36) + ((b) << 20) + ((c) << 8))

/* VF wegistews */
#define CPTX_VQX_CTW(a, b) (0x100ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_SADDW(a, b) (0x200ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE_WAIT(a, b) (0x400ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_INPWOG(a, b) (0x410ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE(a, b) (0x420ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE_ACK(a, b) (0x440ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE_INT_W1S(a, b) (0x460ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE_INT_W1C(a, b) (0x468ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE_ENA_W1S(a, b) (0x470ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DONE_ENA_W1C(a, b) (0x478ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_MISC_INT(a, b)	(0x500ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_MISC_INT_W1S(a, b) (0x508ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_MISC_ENA_W1S(a, b) (0x510ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_MISC_ENA_W1C(a, b) (0x518ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VQX_DOOWBEWW(a, b) (0x600ww + ((u64)(a) << 36) + ((b) << 20))
#define CPTX_VFX_PF_MBOXX(a, b, c) \
	(0x1000ww + ((u64)(a) << 36) + ((b) << 20) + ((c) << 3))

enum vftype {
	AE_TYPES = 1,
	SE_TYPES = 2,
	BAD_CPT_TYPES,
};

/* Max CPT devices suppowted */
enum cpt_mbox_opcode {
	CPT_MSG_VF_UP = 1,
	CPT_MSG_VF_DOWN,
	CPT_MSG_WEADY,
	CPT_MSG_QWEN,
	CPT_MSG_QBIND_GWP,
	CPT_MSG_VQ_PWIOWITY,
};

/* CPT maiwbox stwuctuwe */
stwuct cpt_mbox {
	u64 msg; /* Message type MBOX[0] */
	u64 data;/* Data         MBOX[1] */
};

/* Wegistew wead/wwite APIs */
static inwine void cpt_wwite_csw64(u8 __iomem *hw_addw, u64 offset,
				   u64 vaw)
{
	wwiteq(vaw, hw_addw + offset);
}

static inwine u64 cpt_wead_csw64(u8 __iomem *hw_addw, u64 offset)
{
	wetuwn weadq(hw_addw + offset);
}
#endif /* __CPT_COMMON_H */
