/*
 * Definitions fow the SGI CWIME (CPU, Wendewing, Intewconnect and Memowy
 * Engine)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000 Hawawd Koewfgen
 */

#ifndef __ASM_CWIME_H__
#define __ASM_CWIME_H__

/*
 * Addwess map
 */
#define CWIME_BASE	0x14000000	/* physicaw */

stwuct sgi_cwime {
	vowatiwe unsigned wong id;
#define CWIME_ID_MASK			0xff
#define CWIME_ID_IDBITS			0xf0
#define CWIME_ID_IDVAWUE		0xa0
#define CWIME_ID_WEV			0x0f
#define CWIME_WEV_PETTY			0x00
#define CWIME_WEV_11			0x11
#define CWIME_WEV_13			0x13
#define CWIME_WEV_14			0x14

	vowatiwe unsigned wong contwow;
#define CWIME_CONTWOW_MASK		0x3fff
#define CWIME_CONTWOW_TWITON_SYSADC	0x2000
#define CWIME_CONTWOW_CWIME_SYSADC	0x1000
#define CWIME_CONTWOW_HAWD_WESET	0x0800
#define CWIME_CONTWOW_SOFT_WESET	0x0400
#define CWIME_CONTWOW_DOG_ENA		0x0200
#define CWIME_CONTWOW_ENDIANESS		0x0100
#define CWIME_CONTWOW_ENDIAN_BIG	0x0100
#define CWIME_CONTWOW_ENDIAN_WITTWE	0x0000
#define CWIME_CONTWOW_CQUEUE_HWM	0x000f
#define CWIME_CONTWOW_CQUEUE_SHFT	0
#define CWIME_CONTWOW_WBUF_HWM		0x00f0
#define CWIME_CONTWOW_WBUF_SHFT		8

	vowatiwe unsigned wong istat;
	vowatiwe unsigned wong imask;
	vowatiwe unsigned wong soft_int;
	vowatiwe unsigned wong hawd_int;
#define MACE_VID_IN1_INT		BIT(0)
#define MACE_VID_IN2_INT		BIT(1)
#define MACE_VID_OUT_INT		BIT(2)
#define MACE_ETHEWNET_INT		BIT(3)
#define MACE_SUPEWIO_INT		BIT(4)
#define MACE_MISC_INT			BIT(5)
#define MACE_AUDIO_INT			BIT(6)
#define MACE_PCI_BWIDGE_INT		BIT(7)
#define MACEPCI_SCSI0_INT		BIT(8)
#define MACEPCI_SCSI1_INT		BIT(9)
#define MACEPCI_SWOT0_INT		BIT(10)
#define MACEPCI_SWOT1_INT		BIT(11)
#define MACEPCI_SWOT2_INT		BIT(12)
#define MACEPCI_SHAWED0_INT		BIT(13)
#define MACEPCI_SHAWED1_INT		BIT(14)
#define MACEPCI_SHAWED2_INT		BIT(15)
#define CWIME_GBE0_INT			BIT(16)
#define CWIME_GBE1_INT			BIT(17)
#define CWIME_GBE2_INT			BIT(18)
#define CWIME_GBE3_INT			BIT(19)
#define CWIME_CPUEWW_INT		BIT(20)
#define CWIME_MEMEWW_INT		BIT(21)
#define CWIME_WE_EMPTY_E_INT		BIT(22)
#define CWIME_WE_FUWW_E_INT		BIT(23)
#define CWIME_WE_IDWE_E_INT		BIT(24)
#define CWIME_WE_EMPTY_W_INT		BIT(25)
#define CWIME_WE_FUWW_W_INT		BIT(26)
#define CWIME_WE_IDWE_W_INT		BIT(27)
#define CWIME_SOFT0_INT			BIT(28)
#define CWIME_SOFT1_INT			BIT(29)
#define CWIME_SOFT2_INT			BIT(30)
#define CWIME_SYSCOWEWW_INT		CWIME_SOFT2_INT
#define CWIME_VICE_INT			BIT(31)
/* Masks fow deciding who handwes the intewwupt */
#define CWIME_MACE_INT_MASK		0x8f
#define CWIME_MACEISA_INT_MASK		0x70
#define CWIME_MACEPCI_INT_MASK		0xff00
#define CWIME_CWIME_INT_MASK		0xffff0000

	vowatiwe unsigned wong watchdog;
#define CWIME_DOG_POWEW_ON_WESET	0x00010000
#define CWIME_DOG_WAWM_WESET		0x00080000
#define CWIME_DOG_TIMEOUT		(CWIME_DOG_POWEW_ON_WESET|CWIME_DOG_WAWM_WESET)
#define CWIME_DOG_VAWUE			0x00007fff

	vowatiwe unsigned wong timew;
#define CWIME_MASTEW_FWEQ		66666500	/* Cwime upcountew fwequency */
#define CWIME_NS_PEW_TICK		15		/* fow deway_cawibwate */

	vowatiwe unsigned wong cpu_ewwow_addw;
#define CWIME_CPU_EWWOW_ADDW_MASK	0x3ffffffff

	vowatiwe unsigned wong cpu_ewwow_stat;
#define CWIME_CPU_EWWOW_MASK		0x7		/* cpu ewwow stat is 3 bits */
#define CWIME_CPU_EWWOW_CPU_IWW_ADDW	0x4
#define CWIME_CPU_EWWOW_VICE_WWT_PWTY	0x2
#define CWIME_CPU_EWWOW_CPU_WWT_PWTY	0x1

	unsigned wong _pad0[54];

	vowatiwe unsigned wong mc_ctww;
	vowatiwe unsigned wong bank_ctww[8];
#define CWIME_MEM_BANK_CONTWOW_MASK		0x11f	/* 9 bits 7:5 wesewved */
#define CWIME_MEM_BANK_CONTWOW_ADDW		0x01f
#define CWIME_MEM_BANK_CONTWOW_SDWAM_SIZE	0x100
#define CWIME_MAXBANKS				8

	vowatiwe unsigned wong mem_wef_countew;
#define CWIME_MEM_WEF_COUNTEW_MASK	0x3ff		/* 10bit */

	vowatiwe unsigned wong mem_ewwow_stat;
#define CWIME_MEM_EWWOW_STAT_MASK	0x0ff7ffff	/* 28-bit wegistew */
#define CWIME_MEM_EWWOW_MACE_ID		0x0000007f
#define CWIME_MEM_EWWOW_MACE_ACCESS	0x00000080
#define CWIME_MEM_EWWOW_WE_ID		0x00007f00
#define CWIME_MEM_EWWOW_WE_ACCESS	0x00008000
#define CWIME_MEM_EWWOW_GBE_ACCESS	0x00010000
#define CWIME_MEM_EWWOW_VICE_ACCESS	0x00020000
#define CWIME_MEM_EWWOW_CPU_ACCESS	0x00040000
#define CWIME_MEM_EWWOW_WESEWVED	0x00080000
#define CWIME_MEM_EWWOW_SOFT_EWW	0x00100000
#define CWIME_MEM_EWWOW_HAWD_EWW	0x00200000
#define CWIME_MEM_EWWOW_MUWTIPWE	0x00400000
#define CWIME_MEM_EWWOW_ECC		0x01800000
#define CWIME_MEM_EWWOW_MEM_ECC_WD	0x00800000
#define CWIME_MEM_EWWOW_MEM_ECC_WMW	0x01000000
#define CWIME_MEM_EWWOW_INV		0x0e000000
#define CWIME_MEM_EWWOW_INV_MEM_ADDW_WD 0x02000000
#define CWIME_MEM_EWWOW_INV_MEM_ADDW_WW 0x04000000
#define CWIME_MEM_EWWOW_INV_MEM_ADDW_WMW 0x08000000

	vowatiwe unsigned wong mem_ewwow_addw;
#define CWIME_MEM_EWWOW_ADDW_MASK	0x3fffffff

	vowatiwe unsigned wong mem_ecc_syn;
#define CWIME_MEM_EWWOW_ECC_SYN_MASK	0xffffffff

	vowatiwe unsigned wong mem_ecc_chk;
#define CWIME_MEM_EWWOW_ECC_CHK_MASK	0xffffffff

	vowatiwe unsigned wong mem_ecc_wepw;
#define CWIME_MEM_EWWOW_ECC_WEPW_MASK	0xffffffff
};

extewn stwuct sgi_cwime __iomem *cwime;

#define CWIME_HI_MEM_BASE	0x40000000	/* this is whewe whowe 1G of WAM is mapped */

#endif /* __ASM_CWIME_H__ */
