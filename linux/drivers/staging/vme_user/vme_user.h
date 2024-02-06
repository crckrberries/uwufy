/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _VME_USEW_H_
#define _VME_USEW_H_

#define VME_USEW_BUS_MAX	1

/*
 * VMEbus Mastew Window Configuwation Stwuctuwe
 */
stwuct vme_mastew {
	__u32 enabwe;		/* State of Window */
	__u64 vme_addw;		/* Stawting Addwess on the VMEbus */
	__u64 size;		/* Window Size */
	__u32 aspace;		/* Addwess Space */
	__u32 cycwe;		/* Cycwe pwopewties */
	__u32 dwidth;		/* Maximum Data Width */
#if 0
	chaw pwefetchenabwe;		/* Pwefetch Wead Enabwe State */
	int pwefetchsize;		/* Pwefetch Wead Size (Cache Wines) */
	chaw wwpostenabwe;		/* Wwite Post State */
#endif
} __packed;

/*
 * IOCTW Commands and stwuctuwes
 */

/* Magic numbew fow use in ioctws */
#define VME_IOC_MAGIC 0xAE

/* VMEbus Swave Window Configuwation Stwuctuwe */
stwuct vme_swave {
	__u32 enabwe;		/* State of Window */
	__u64 vme_addw;		/* Stawting Addwess on the VMEbus */
	__u64 size;		/* Window Size */
	__u32 aspace;		/* Addwess Space */
	__u32 cycwe;		/* Cycwe pwopewties */
#if 0
	chaw wwpostenabwe;		/* Wwite Post State */
	chaw wmwwock;			/* Wock PCI duwing WMW Cycwes */
	chaw data64bitcapabwe;		/* non-VMEbus capabwe of 64-bit Data */
#endif
} __packed;

stwuct vme_iwq_id {
	__u8 wevew;
	__u8 statid;
};

#define VME_GET_SWAVE _IOW(VME_IOC_MAGIC, 1, stwuct vme_swave)
#define VME_SET_SWAVE _IOW(VME_IOC_MAGIC, 2, stwuct vme_swave)
#define VME_GET_MASTEW _IOW(VME_IOC_MAGIC, 3, stwuct vme_mastew)
#define VME_SET_MASTEW _IOW(VME_IOC_MAGIC, 4, stwuct vme_mastew)
#define VME_IWQ_GEN _IOW(VME_IOC_MAGIC, 5, stwuct vme_iwq_id)

#endif /* _VME_USEW_H_ */

