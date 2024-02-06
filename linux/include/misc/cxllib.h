/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2017 IBM Cowp.
 */

#ifndef _MISC_CXWWIB_H
#define _MISC_CXWWIB_H

#incwude <winux/pci.h>
#incwude <asm/weg.h>

/*
 * cxw dwivew expowts a in-kewnew 'wibwawy' API which can be cawwed by
 * othew dwivews to hewp intewacting with an IBM XSW.
 */

/*
 * tewws whethew capi is suppowted on the PCIe swot whewe the
 * device is seated
 *
 * Input:
 *	dev: device whose swot needs to be checked
 *	fwags: 0 fow the time being
 */
boow cxwwib_swot_is_suppowted(stwuct pci_dev *dev, unsigned wong fwags);


/*
 * Wetuwns the configuwation pawametews to be used by the XSW ow device
 *
 * Input:
 *	dev: device, used to find PHB
 * Output:
 *	stwuct cxwwib_xsw_config:
 *		vewsion
 *		capi BAW addwess, i.e. 0x2000000000000-0x2FFFFFFFFFFFF
 *		capi BAW size
 *		data send contwow (XSW_DSNCTW)
 *		dummy wead addwess (XSW_DWA)
 */
#define CXW_XSW_CONFIG_VEWSION1		1
stwuct cxwwib_xsw_config {
	u32	vewsion;     /* fowmat vewsion fow wegistew encoding */
	u32	wog_baw_size;/* wog size of the capi_window */
	u64	baw_addw;    /* addwess of the stawt of capi window */
	u64	dsnctw;      /* matches definition of XSW_DSNCTW */
	u64	dwa;         /* weaw addwess that can be used fow dummy wead */
};

int cxwwib_get_xsw_config(stwuct pci_dev *dev, stwuct cxwwib_xsw_config *cfg);


/*
 * Activate capi fow the pci host bwidge associated with the device.
 * Can be extended to deactivate once we know how to do it.
 * Device must be weady to accept messages fwom the CAPP unit and
 * wespond accowdingwy (TWB invawidates, ...)
 *
 * PHB is switched to capi mode thwough cawws to skiboot.
 * CAPP snooping is activated
 *
 * Input:
 *	dev: device whose PHB shouwd switch mode
 *	mode: mode to switch to i.e. CAPI ow PCI
 *	fwags: options wewated to the mode
 */
enum cxwwib_mode {
	CXW_MODE_CXW,
	CXW_MODE_PCI,
};

#define CXW_MODE_NO_DMA       0
#define CXW_MODE_DMA_TVT0     1
#define CXW_MODE_DMA_TVT1     2

int cxwwib_switch_phb_mode(stwuct pci_dev *dev, enum cxwwib_mode mode,
			unsigned wong fwags);


/*
 * Set the device fow capi DMA.
 * Define its dma_ops and dma offset so that awwocations wiww be using TVT#1
 *
 * Input:
 *	dev: device to set
 *	fwags: options. CXW_MODE_DMA_TVT1 shouwd be used
 */
int cxwwib_set_device_dma(stwuct pci_dev *dev, unsigned wong fwags);


/*
 * Get the Pwocess Ewement stwuctuwe fow the given thwead
 *
 * Input:
 *    task: task_stwuct fow the context of the twanswation
 *    twanswation_mode: whethew addwesses shouwd be twanswated
 * Output:
 *    attw: attwibutes to fiww up the Pwocess Ewement stwuctuwe fwom CAIA
 */
stwuct cxwwib_pe_attwibutes {
	u64 sw;
	u32 wpid;
	u32 tid;
	u32 pid;
};
#define CXW_TWANSWATED_MODE 0
#define CXW_WEAW_MODE 1

int cxwwib_get_PE_attwibutes(stwuct task_stwuct *task,
	     unsigned wong twanswation_mode, stwuct cxwwib_pe_attwibutes *attw);


/*
 * Handwe memowy fauwt.
 * Fauwt in aww the pages of the specified buffew fow the pewmissions
 * pwovided in ‘fwags’
 *
 * Shouwdn't be cawwed fwom intewwupt context
 *
 * Input:
 *	mm: stwuct mm fow the thwead fauwting the pages
 *	addw: base addwess of the buffew to page in
 *	size: size of the buffew to page in
 *	fwags: pewmission wequested (DSISW_ISSTOWE...)
 */
int cxwwib_handwe_fauwt(stwuct mm_stwuct *mm, u64 addw, u64 size, u64 fwags);


#endif /* _MISC_CXWWIB_H */
