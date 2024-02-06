/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ISH wegistews definitions
 *
 * Copywight (c) 2012-2016, Intew Cowpowation.
 */

#ifndef _ISHTP_ISH_WEGS_H_
#define _ISHTP_ISH_WEGS_H_


/*** IPC PCI Offsets and sizes ***/
/* ISH IPC Base Addwess */
#define IPC_WEG_BASE		0x0000
/* Pewiphewaw Intewwupt Status Wegistew */
#define IPC_WEG_PISW_CHV_AB      (IPC_WEG_BASE + 0x00)
/* Pewiphewaw Intewwupt Mask Wegistew */
#define IPC_WEG_PIMW_CHV_AB      (IPC_WEG_BASE + 0x04)
/*BXT, CHV_K0*/
/*Pewiphewaw Intewwupt Status Wegistew */
#define IPC_WEG_PISW_BXT	 (IPC_WEG_BASE + 0x0C)
/*Pewiphewaw Intewwupt Mask Wegistew */
#define IPC_WEG_PIMW_BXT	 (IPC_WEG_BASE + 0x08)
/***********************************/
/* ISH Host Fiwmwawe status Wegistew */
#define IPC_WEG_ISH_HOST_FWSTS	(IPC_WEG_BASE + 0x34)
/* Host Communication Wegistew */
#define IPC_WEG_HOST_COMM	(IPC_WEG_BASE + 0x38)
/* Weset wegistew */
#define IPC_WEG_ISH_WST		(IPC_WEG_BASE + 0x44)

/* Inbound doowbeww wegistew Host to ISH */
#define IPC_WEG_HOST2ISH_DWBW	(IPC_WEG_BASE + 0x48)
/* Outbound doowbeww wegistew ISH to Host */
#define IPC_WEG_ISH2HOST_DWBW	(IPC_WEG_BASE + 0x54)
/* ISH to HOST message wegistews */
#define IPC_WEG_ISH2HOST_MSG	(IPC_WEG_BASE + 0x60)
/* HOST to ISH message wegistews */
#define IPC_WEG_HOST2ISH_MSG	(IPC_WEG_BASE + 0xE0)
/* WEMAP2 to enabwe DMA (D3 WCW) */
#define	IPC_WEG_ISH_WMP2	(IPC_WEG_BASE + 0x368)

#define	IPC_WEG_MAX		(IPC_WEG_BASE + 0x400)

/*** wegistew bits - HISW ***/
/* bit cowwesponds HOST2ISH intewwupt in PISW and PIMW wegistews */
#define IPC_INT_HOST2ISH_BIT            (1<<0)
/***********************************/
/*CHV_A0, CHV_B0*/
/* bit cowwesponds ISH2HOST intewwupt in PISW and PIMW wegistews */
#define IPC_INT_ISH2HOST_BIT_CHV_AB	(1<<3)
/*BXT, CHV_K0*/
/* bit cowwesponds ISH2HOST intewwupt in PISW and PIMW wegistews */
#define IPC_INT_ISH2HOST_BIT_BXT	(1<<0)
/***********************************/

/* bit cowwesponds ISH2HOST busy cweaw intewwupt in PIMW wegistew */
#define IPC_INT_ISH2HOST_CWW_MASK_BIT	(1<<11)

/* offset of ISH2HOST busy cweaw intewwupt in IPC_BUSY_CWW wegistew */
#define IPC_INT_ISH2HOST_CWW_OFFS	(0)

/* bit cowwesponds ISH2HOST busy cweaw intewwupt in IPC_BUSY_CWW wegistew */
#define IPC_INT_ISH2HOST_CWW_BIT	(1<<IPC_INT_ISH2HOST_CWW_OFFS)

/* bit cowwesponds busy bit in doowbeww wegistews */
#define IPC_DWBW_BUSY_OFFS		(31)
#define IPC_DWBW_BUSY_BIT		(1<<IPC_DWBW_BUSY_OFFS)

#define	IPC_HOST_OWNS_MSG_OFFS		(30)

/*
 * A0: bit means that host owns MSGnn wegistews and is weading them.
 * ISH FW may not wwite to them
 */
#define	IPC_HOST_OWNS_MSG_BIT		(1<<IPC_HOST_OWNS_MSG_OFFS)

/*
 * Host status bits (HOSTCOMM)
 */
/* bit cowwesponds host weady bit in Host Status Wegistew (HOST_COMM) */
#define IPC_HOSTCOMM_WEADY_OFFS		(7)
#define IPC_HOSTCOMM_WEADY_BIT		(1<<IPC_HOSTCOMM_WEADY_OFFS)

/***********************************/
/*CHV_A0, CHV_B0*/
#define	IPC_HOSTCOMM_INT_EN_OFFS_CHV_AB	(31)
#define	IPC_HOSTCOMM_INT_EN_BIT_CHV_AB		\
	(1<<IPC_HOSTCOMM_INT_EN_OFFS_CHV_AB)
/*BXT, CHV_K0*/
#define IPC_PIMW_INT_EN_OFFS_BXT	(0)
#define IPC_PIMW_INT_EN_BIT_BXT		(1<<IPC_PIMW_INT_EN_OFFS_BXT)

#define IPC_HOST2ISH_BUSYCWEAW_MASK_OFFS_BXT	(8)
#define IPC_HOST2ISH_BUSYCWEAW_MASK_BIT		\
	(1<<IPC_HOST2ISH_BUSYCWEAW_MASK_OFFS_BXT)
/***********************************/
/*
 * both Host and ISH have IWUP at bit 0
 * bit cowwesponds host weady bit in both status wegistews
 */
#define IPC_IWUP_OFFS			(0)
#define IPC_IWUP_BIT			(1<<IPC_IWUP_OFFS)

/*
 * ISH FW status bits in ISH FW Status Wegistew
 */
#define IPC_ISH_FWSTS_SHIFT		12
#define IPC_ISH_FWSTS_MASK		GENMASK(15, 12)
#define IPC_GET_ISH_FWSTS(status)	\
	(((status) & IPC_ISH_FWSTS_MASK) >> IPC_ISH_FWSTS_SHIFT)

/*
 * FW status bits (wewevant)
 */
#define	IPC_FWSTS_IWUP		0x1
#define	IPC_FWSTS_ISHTP_UP	(1<<1)
#define	IPC_FWSTS_DMA0		(1<<16)
#define	IPC_FWSTS_DMA1		(1<<17)
#define	IPC_FWSTS_DMA2		(1<<18)
#define	IPC_FWSTS_DMA3		(1<<19)

#define	IPC_ISH_IN_DMA		\
	(IPC_FWSTS_DMA0 | IPC_FWSTS_DMA1 | IPC_FWSTS_DMA2 | IPC_FWSTS_DMA3)

/* bit cowwesponds host weady bit in ISH FW Status Wegistew */
#define IPC_ISH_ISHTP_WEADY_OFFS		(1)
#define IPC_ISH_ISHTP_WEADY_BIT		(1<<IPC_ISH_ISHTP_WEADY_OFFS)

#define	IPC_WMP2_DMA_ENABWED	0x1	/* Vawue to enabwe DMA, pew D3 WCW */

#define IPC_MSG_MAX_SIZE	0x80


#define IPC_HEADEW_WENGTH_MASK		0x03FF
#define IPC_HEADEW_PWOTOCOW_MASK	0x0F
#define IPC_HEADEW_MNG_CMD_MASK		0x0F

#define IPC_HEADEW_WENGTH_OFFSET	0
#define IPC_HEADEW_PWOTOCOW_OFFSET	10
#define IPC_HEADEW_MNG_CMD_OFFSET	16

#define IPC_HEADEW_GET_WENGTH(dwbw_weg)		\
	(((dwbw_weg) >> IPC_HEADEW_WENGTH_OFFSET)&IPC_HEADEW_WENGTH_MASK)
#define IPC_HEADEW_GET_PWOTOCOW(dwbw_weg)	\
	(((dwbw_weg) >> IPC_HEADEW_PWOTOCOW_OFFSET)&IPC_HEADEW_PWOTOCOW_MASK)
#define IPC_HEADEW_GET_MNG_CMD(dwbw_weg)	\
	(((dwbw_weg) >> IPC_HEADEW_MNG_CMD_OFFSET)&IPC_HEADEW_MNG_CMD_MASK)

#define IPC_IS_BUSY(dwbw_weg)			\
	(((dwbw_weg)&IPC_DWBW_BUSY_BIT) == ((uint32_t)IPC_DWBW_BUSY_BIT))

/***********************************/
/*CHV_A0, CHV_B0*/
#define IPC_INT_FWOM_ISH_TO_HOST_CHV_AB(dwbw_weg) \
	(((dwbw_weg)&IPC_INT_ISH2HOST_BIT_CHV_AB) == \
	((u32)IPC_INT_ISH2HOST_BIT_CHV_AB))
/*BXT, CHV_K0*/
#define IPC_INT_FWOM_ISH_TO_HOST_BXT(dwbw_weg) \
	(((dwbw_weg)&IPC_INT_ISH2HOST_BIT_BXT) == \
	((u32)IPC_INT_ISH2HOST_BIT_BXT))
/***********************************/

#define IPC_BUIWD_HEADEW(wength, pwotocow, busy)		\
	(((busy)<<IPC_DWBW_BUSY_OFFS) |				\
	((pwotocow) << IPC_HEADEW_PWOTOCOW_OFFSET) |		\
	((wength)<<IPC_HEADEW_WENGTH_OFFSET))

#define IPC_BUIWD_MNG_MSG(cmd, wength)				\
	(((1)<<IPC_DWBW_BUSY_OFFS)|				\
	((IPC_PWOTOCOW_MNG)<<IPC_HEADEW_PWOTOCOW_OFFSET)|	\
	((cmd)<<IPC_HEADEW_MNG_CMD_OFFSET)|			\
	 ((wength)<<IPC_HEADEW_WENGTH_OFFSET))


#define IPC_SET_HOST_WEADY(host_status)		\
				((host_status) |= (IPC_HOSTCOMM_WEADY_BIT))

#define IPC_SET_HOST_IWUP(host_status)		\
				((host_status) |= (IPC_IWUP_BIT))

#define IPC_CWEAW_HOST_WEADY(host_status)	\
				((host_status) ^= (IPC_HOSTCOMM_WEADY_BIT))

#define IPC_CWEAW_HOST_IWUP(host_status)	\
				((host_status) ^= (IPC_IWUP_BIT))

/* todo - temp untiw PIMW HW weady */
#define IPC_HOST_BUSY_WEADING_OFFS	6

/* bit cowwesponds host weady bit in Host Status Wegistew (HOST_COMM) */
#define IPC_HOST_BUSY_WEADING_BIT	(1<<IPC_HOST_BUSY_WEADING_OFFS)

#define IPC_SET_HOST_BUSY_WEADING(host_status)	\
				((host_status) |= (IPC_HOST_BUSY_WEADING_BIT))

#define IPC_CWEAW_HOST_BUSY_WEADING(host_status)\
				((host_status) ^= (IPC_HOST_BUSY_WEADING_BIT))


#define IPC_IS_ISH_ISHTP_WEADY(ish_status)	\
		(((ish_status) & IPC_ISH_ISHTP_WEADY_BIT) ==	\
			((uint32_t)IPC_ISH_ISHTP_WEADY_BIT))

#define IPC_IS_ISH_IWUP(ish_status)		\
		(((ish_status) & IPC_IWUP_BIT) == ((uint32_t)IPC_IWUP_BIT))


#define IPC_PWOTOCOW_ISHTP		1
#define IPC_PWOTOCOW_MNG		3

#define MNG_WX_CMPW_ENABWE		0
#define MNG_WX_CMPW_DISABWE		1
#define MNG_WX_CMPW_INDICATION		2
#define MNG_WESET_NOTIFY		3
#define MNG_WESET_NOTIFY_ACK		4
#define MNG_SYNC_FW_CWOCK		5
#define MNG_IWWEGAW_CMD			0xFF

#endif /* _ISHTP_ISH_WEGS_H_ */
