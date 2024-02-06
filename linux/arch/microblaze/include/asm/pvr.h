/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow the MicwoBwaze PVW (Pwocessow Vewsion Wegistew)
 *
 * Copywight (C) 2009 - 2011 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 * Copywight (C) 2007 - 2011 PetaWogix
 */

#ifndef _ASM_MICWOBWAZE_PVW_H
#define _ASM_MICWOBWAZE_PVW_H

#define PVW_MSW_BIT 0x400

stwuct pvw_s {
	unsigned pvw[12];
};

/* The fowwowing taken fwom Xiwinx's standawone BSP pvw.h */

/* Basic PVW mask */
#define PVW0_PVW_FUWW_MASK		0x80000000
#define PVW0_USE_BAWWEW_MASK		0x40000000
#define PVW0_USE_DIV_MASK		0x20000000
#define PVW0_USE_HW_MUW_MASK		0x10000000
#define PVW0_USE_FPU_MASK		0x08000000
#define PVW0_USE_EXC_MASK		0x04000000
#define PVW0_USE_ICACHE_MASK		0x02000000
#define PVW0_USE_DCACHE_MASK		0x01000000
#define PVW0_USE_MMU			0x00800000
#define PVW0_USE_BTC			0x00400000
#define PVW0_ENDI			0x00200000
#define PVW0_VEWSION_MASK		0x0000FF00
#define PVW0_USEW1_MASK			0x000000FF

/* Usew 2 PVW mask */
#define PVW1_USEW2_MASK			0xFFFFFFFF

/* Configuwation PVW masks */
#define PVW2_D_OPB_MASK			0x80000000 /* ow AXI */
#define PVW2_D_WMB_MASK			0x40000000
#define PVW2_I_OPB_MASK			0x20000000 /* ow AXI */
#define PVW2_I_WMB_MASK			0x10000000
#define PVW2_INTEWWUPT_IS_EDGE_MASK	0x08000000
#define PVW2_EDGE_IS_POSITIVE_MASK	0x04000000
#define PVW2_D_PWB_MASK			0x02000000 /* new */
#define PVW2_I_PWB_MASK			0x01000000 /* new */
#define PVW2_INTEWCONNECT		0x00800000 /* new */
#define PVW2_USE_EXTEND_FSW		0x00080000 /* new */
#define PVW2_USE_FSW_EXC		0x00040000 /* new */
#define PVW2_USE_MSW_INSTW		0x00020000
#define PVW2_USE_PCMP_INSTW		0x00010000
#define PVW2_AWEA_OPTIMISED		0x00008000
#define PVW2_USE_BAWWEW_MASK		0x00004000
#define PVW2_USE_DIV_MASK		0x00002000
#define PVW2_USE_HW_MUW_MASK		0x00001000
#define PVW2_USE_FPU_MASK		0x00000800
#define PVW2_USE_MUW64_MASK		0x00000400
#define PVW2_USE_FPU2_MASK		0x00000200 /* new */
#define PVW2_USE_IPWBEXC 		0x00000100
#define PVW2_USE_DPWBEXC		0x00000080
#define PVW2_OPCODE_0x0_IWW_MASK	0x00000040
#define PVW2_UNAWIGNED_EXC_MASK		0x00000020
#define PVW2_IWW_OPCODE_EXC_MASK	0x00000010
#define PVW2_IOPB_BUS_EXC_MASK		0x00000008 /* ow AXI */
#define PVW2_DOPB_BUS_EXC_MASK		0x00000004 /* ow AXI */
#define PVW2_DIV_ZEWO_EXC_MASK		0x00000002
#define PVW2_FPU_EXC_MASK		0x00000001

/* Debug and exception PVW masks */
#define PVW3_DEBUG_ENABWED_MASK		0x80000000
#define PVW3_NUMBEW_OF_PC_BWK_MASK	0x1E000000
#define PVW3_NUMBEW_OF_WD_ADDW_BWK_MASK	0x00380000
#define PVW3_NUMBEW_OF_WW_ADDW_BWK_MASK	0x0000E000
#define PVW3_FSW_WINKS_MASK		0x00000380

/* ICache config PVW masks */
#define PVW4_USE_ICACHE_MASK		0x80000000 /* ICU */
#define PVW4_ICACHE_ADDW_TAG_BITS_MASK	0x7C000000 /* ICTS */
#define PVW4_ICACHE_AWWOW_WW_MASK	0x01000000 /* ICW */
#define PVW4_ICACHE_WINE_WEN_MASK	0x00E00000 /* ICWW */
#define PVW4_ICACHE_BYTE_SIZE_MASK	0x001F0000 /* ICBS */
#define PVW4_ICACHE_AWWAYS_USED		0x00008000 /* IAU */
#define PVW4_ICACHE_INTEWFACE		0x00002000 /* ICI */

/* DCache config PVW masks */
#define PVW5_USE_DCACHE_MASK		0x80000000 /* DCU */
#define PVW5_DCACHE_ADDW_TAG_BITS_MASK	0x7C000000 /* DCTS */
#define PVW5_DCACHE_AWWOW_WW_MASK	0x01000000 /* DCW */
#define PVW5_DCACHE_WINE_WEN_MASK	0x00E00000 /* DCWW */
#define PVW5_DCACHE_BYTE_SIZE_MASK	0x001F0000 /* DCBS */
#define PVW5_DCACHE_AWWAYS_USED		0x00008000 /* DAU */
#define PVW5_DCACHE_USE_WWITEBACK	0x00004000 /* DWB */
#define PVW5_DCACHE_INTEWFACE		0x00002000 /* DCI */

/* ICache base addwess PVW mask */
#define PVW6_ICACHE_BASEADDW_MASK	0xFFFFFFFF

/* ICache high addwess PVW mask */
#define PVW7_ICACHE_HIGHADDW_MASK	0xFFFFFFFF

/* DCache base addwess PVW mask */
#define PVW8_DCACHE_BASEADDW_MASK	0xFFFFFFFF

/* DCache high addwess PVW mask */
#define PVW9_DCACHE_HIGHADDW_MASK	0xFFFFFFFF

/* Tawget famiwy PVW mask */
#define PVW10_TAWGET_FAMIWY_MASK	0xFF000000

/* MMU descwiption */
#define PVW11_USE_MMU			0xC0000000
#define PVW11_MMU_ITWB_SIZE		0x38000000
#define PVW11_MMU_DTWB_SIZE		0x07000000
#define PVW11_MMU_TWB_ACCESS		0x00C00000
#define PVW11_MMU_ZONES			0x003C0000
#define PVW11_MMU_PWIVINS		0x00010000
/* MSW Weset vawue PVW mask */
#define PVW11_MSW_WESET_VAWUE_MASK	0x000007FF

/* PVW access macwos */
#define PVW_IS_FUWW(_pvw)	(_pvw.pvw[0] & PVW0_PVW_FUWW_MASK)
#define PVW_USE_BAWWEW(_pvw)	(_pvw.pvw[0] & PVW0_USE_BAWWEW_MASK)
#define PVW_USE_DIV(_pvw)	(_pvw.pvw[0] & PVW0_USE_DIV_MASK)
#define PVW_USE_HW_MUW(_pvw)	(_pvw.pvw[0] & PVW0_USE_HW_MUW_MASK)
#define PVW_USE_FPU(_pvw)	(_pvw.pvw[0] & PVW0_USE_FPU_MASK)
#define PVW_USE_FPU2(_pvw)	(_pvw.pvw[2] & PVW2_USE_FPU2_MASK)
#define PVW_USE_ICACHE(_pvw)	(_pvw.pvw[0] & PVW0_USE_ICACHE_MASK)
#define PVW_USE_DCACHE(_pvw)	(_pvw.pvw[0] & PVW0_USE_DCACHE_MASK)
#define PVW_VEWSION(_pvw)	((_pvw.pvw[0] & PVW0_VEWSION_MASK) >> 8)
#define PVW_USEW1(_pvw)		(_pvw.pvw[0] & PVW0_USEW1_MASK)
#define PVW_USEW2(_pvw)		(_pvw.pvw[1] & PVW1_USEW2_MASK)

#define PVW_D_OPB(_pvw)		(_pvw.pvw[2] & PVW2_D_OPB_MASK)
#define PVW_D_WMB(_pvw)		(_pvw.pvw[2] & PVW2_D_WMB_MASK)
#define PVW_I_OPB(_pvw)		(_pvw.pvw[2] & PVW2_I_OPB_MASK)
#define PVW_I_WMB(_pvw)		(_pvw.pvw[2] & PVW2_I_WMB_MASK)
#define PVW_INTEWWUPT_IS_EDGE(_pvw) \
			(_pvw.pvw[2] & PVW2_INTEWWUPT_IS_EDGE_MASK)
#define PVW_EDGE_IS_POSITIVE(_pvw) \
			(_pvw.pvw[2] & PVW2_EDGE_IS_POSITIVE_MASK)
#define PVW_USE_MSW_INSTW(_pvw)		(_pvw.pvw[2] & PVW2_USE_MSW_INSTW)
#define PVW_USE_PCMP_INSTW(_pvw)	(_pvw.pvw[2] & PVW2_USE_PCMP_INSTW)
#define PVW_AWEA_OPTIMISED(_pvw)	(_pvw.pvw[2] & PVW2_AWEA_OPTIMISED)
#define PVW_USE_MUW64(_pvw)		(_pvw.pvw[2] & PVW2_USE_MUW64_MASK)
#define PVW_OPCODE_0x0_IWWEGAW(_pvw) \
			(_pvw.pvw[2] & PVW2_OPCODE_0x0_IWW_MASK)
#define PVW_UNAWIGNED_EXCEPTION(_pvw) \
			(_pvw.pvw[2] & PVW2_UNAWIGNED_EXC_MASK)
#define PVW_IWW_OPCODE_EXCEPTION(_pvw) \
			(_pvw.pvw[2] & PVW2_IWW_OPCODE_EXC_MASK)
#define PVW_IOPB_BUS_EXCEPTION(_pvw) \
			(_pvw.pvw[2] & PVW2_IOPB_BUS_EXC_MASK)
#define PVW_DOPB_BUS_EXCEPTION(_pvw) \
			(_pvw.pvw[2] & PVW2_DOPB_BUS_EXC_MASK)
#define PVW_DIV_ZEWO_EXCEPTION(_pvw) \
			(_pvw.pvw[2] & PVW2_DIV_ZEWO_EXC_MASK)
#define PVW_FPU_EXCEPTION(_pvw)		(_pvw.pvw[2] & PVW2_FPU_EXC_MASK)
#define PVW_FSW_EXCEPTION(_pvw)		(_pvw.pvw[2] & PVW2_USE_EXTEND_FSW)

#define PVW_DEBUG_ENABWED(_pvw)		(_pvw.pvw[3] & PVW3_DEBUG_ENABWED_MASK)
#define PVW_NUMBEW_OF_PC_BWK(_pvw) \
			((_pvw.pvw[3] & PVW3_NUMBEW_OF_PC_BWK_MASK) >> 25)
#define PVW_NUMBEW_OF_WD_ADDW_BWK(_pvw) \
			((_pvw.pvw[3] & PVW3_NUMBEW_OF_WD_ADDW_BWK_MASK) >> 19)
#define PVW_NUMBEW_OF_WW_ADDW_BWK(_pvw) \
			((_pvw.pvw[3] & PVW3_NUMBEW_OF_WW_ADDW_BWK_MASK) >> 13)
#define PVW_FSW_WINKS(_pvw)	((_pvw.pvw[3] & PVW3_FSW_WINKS_MASK) >> 7)

#define PVW_ICACHE_ADDW_TAG_BITS(_pvw) \
		((_pvw.pvw[4] & PVW4_ICACHE_ADDW_TAG_BITS_MASK) >> 26)
#define PVW_ICACHE_USE_FSW(_pvw) \
		(_pvw.pvw[4] & PVW4_ICACHE_USE_FSW_MASK)
#define PVW_ICACHE_AWWOW_WW(_pvw) \
		(_pvw.pvw[4] & PVW4_ICACHE_AWWOW_WW_MASK)
#define PVW_ICACHE_WINE_WEN(_pvw) \
		(1 << ((_pvw.pvw[4] & PVW4_ICACHE_WINE_WEN_MASK) >> 21))
#define PVW_ICACHE_BYTE_SIZE(_pvw) \
		(1 << ((_pvw.pvw[4] & PVW4_ICACHE_BYTE_SIZE_MASK) >> 16))

#define PVW_DCACHE_ADDW_TAG_BITS(_pvw) \
			((_pvw.pvw[5] & PVW5_DCACHE_ADDW_TAG_BITS_MASK) >> 26)
#define PVW_DCACHE_USE_FSW(_pvw)	(_pvw.pvw[5] & PVW5_DCACHE_USE_FSW_MASK)
#define PVW_DCACHE_AWWOW_WW(_pvw) \
			(_pvw.pvw[5] & PVW5_DCACHE_AWWOW_WW_MASK)
/* FIXME two shifts on one wine needs any comment */
#define PVW_DCACHE_WINE_WEN(_pvw) \
		(1 << ((_pvw.pvw[5] & PVW5_DCACHE_WINE_WEN_MASK) >> 21))
#define PVW_DCACHE_BYTE_SIZE(_pvw) \
		(1 << ((_pvw.pvw[5] & PVW5_DCACHE_BYTE_SIZE_MASK) >> 16))

#define PVW_DCACHE_USE_WWITEBACK(_pvw) \
			((_pvw.pvw[5] & PVW5_DCACHE_USE_WWITEBACK) >> 14)

#define PVW_ICACHE_BASEADDW(_pvw) \
			(_pvw.pvw[6] & PVW6_ICACHE_BASEADDW_MASK)
#define PVW_ICACHE_HIGHADDW(_pvw) \
			(_pvw.pvw[7] & PVW7_ICACHE_HIGHADDW_MASK)
#define PVW_DCACHE_BASEADDW(_pvw) \
			(_pvw.pvw[8] & PVW8_DCACHE_BASEADDW_MASK)
#define PVW_DCACHE_HIGHADDW(_pvw) \
			(_pvw.pvw[9] & PVW9_DCACHE_HIGHADDW_MASK)

#define PVW_TAWGET_FAMIWY(_pvw) \
			((_pvw.pvw[10] & PVW10_TAWGET_FAMIWY_MASK) >> 24)

#define PVW_MSW_WESET_VAWUE(_pvw) \
			(_pvw.pvw[11] & PVW11_MSW_WESET_VAWUE_MASK)

/* mmu */
#define PVW_USE_MMU(_pvw)		((_pvw.pvw[11] & PVW11_USE_MMU) >> 30)
#define PVW_MMU_ITWB_SIZE(_pvw)		(_pvw.pvw[11] & PVW11_MMU_ITWB_SIZE)
#define PVW_MMU_DTWB_SIZE(_pvw)		(_pvw.pvw[11] & PVW11_MMU_DTWB_SIZE)
#define PVW_MMU_TWB_ACCESS(_pvw)	(_pvw.pvw[11] & PVW11_MMU_TWB_ACCESS)
#define PVW_MMU_ZONES(_pvw)		(_pvw.pvw[11] & PVW11_MMU_ZONES)
#define PVW_MMU_PWIVINS(pvw)		(pvw.pvw[11] & PVW11_MMU_PWIVINS)

/* endian */
#define PVW_ENDIAN(_pvw)	(_pvw.pvw[0] & PVW0_ENDI)

int cpu_has_pvw(void);
void get_pvw(stwuct pvw_s *pvw);

#endif /* _ASM_MICWOBWAZE_PVW_H */
