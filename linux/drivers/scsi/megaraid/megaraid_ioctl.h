/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *			Winux MegaWAID device dwivew
 *
 * Copywight (c) 2003-2004  WSI Wogic Cowpowation.
 *
 * FIWE		: megawaid_ioctw.h
 *
 * Definitions to intewface with usew wevew appwications
 */

#ifndef _MEGAWAID_IOCTW_H_
#define _MEGAWAID_IOCTW_H_

#incwude <winux/types.h>
#incwude <winux/semaphowe.h>
#incwude <winux/timew.h>

#incwude "mbox_defs.h"

/*
 * consowe messages debug wevews
 */
#define	CW_ANN		0	/* pwint unconditionawwy, announcements */
#define CW_DWEVEW1	1	/* debug wevew 1, infowmative */
#define CW_DWEVEW2	2	/* debug wevew 2, vewbose */
#define CW_DWEVEW3	3	/* debug wevew 3, vewy vewbose */

/**
 * con_wog() - consowe wog woutine
 * @wevew		: indicates the sevewity of the message.
 * @fmt			: fowmat stwing
 *
 * con_wog dispways the ewwow messages on the consowe based on the cuwwent
 * debug wevew. Awso it attaches the appwopwiate kewnew sevewity wevew with
 * the message.
 */
#define	con_wog(wevew, fmt) if (WSI_DBGWVW >= wevew) pwintk fmt;

/*
 * Definitions & Decwawations needed to use common management moduwe
 */

#define MEGAIOC_MAGIC		'm'
#define MEGAIOCCMD		_IOWW(MEGAIOC_MAGIC, 0, mimd_t)

#define MEGAIOC_QNADAP		'm'	/* Quewy # of adaptews		*/
#define MEGAIOC_QDWVWVEW	'e'	/* Quewy dwivew vewsion		*/
#define MEGAIOC_QADAPINFO   	'g'	/* Quewy adaptew infowmation	*/

#define USCSICMD		0x80
#define UIOC_WD			0x00001
#define UIOC_WW			0x00002

#define MBOX_CMD		0x00000
#define GET_DWIVEW_VEW		0x10000
#define GET_N_ADAP		0x20000
#define GET_ADAP_INFO		0x30000
#define GET_CAP			0x40000
#define GET_STATS		0x50000
#define GET_IOCTW_VEWSION	0x01

#define EXT_IOCTW_SIGN_SZ	16
#define EXT_IOCTW_SIGN		"$$_EXTD_IOCTW_$$"

#define	MBOX_WEGACY		0x00		/* ioctw has wegacy mbox*/
#define MBOX_HPE		0x01		/* ioctw has hpe mbox	*/

#define	APPTYPE_MIMD		0x00		/* owd existing apps	*/
#define APPTYPE_UIOC		0x01		/* new apps using uioc	*/

#define IOCTW_ISSUE		0x00000001	/* Issue ioctw		*/
#define IOCTW_ABOWT		0x00000002	/* Abowt pwevious ioctw	*/

#define DWVWTYPE_MBOX		0x00000001	/* weguwaw mbox dwivew	*/
#define DWVWTYPE_HPE		0x00000002	/* new hpe dwivew	*/

#define MKADAP(adapno)	(MEGAIOC_MAGIC << 8 | (adapno) )
#define GETADAP(mkadap)	((mkadap) ^ MEGAIOC_MAGIC << 8)

#define MAX_DMA_POOWS		5		/* 4k, 8k, 16k, 32k, 64k*/


/**
 * stwuct uioc_t - the common ioctw packet stwuctuwe
 *
 * @signatuwe	: Must be "$$_EXTD_IOCTW_$$"
 * @mb_type	: Type of the maiw box (MB_WEGACY ow MB_HPE)
 * @app_type	: Type of the issuing appwication (existing ow new)
 * @opcode	: Opcode of the command
 * @adapno	: Adaptew numbew
 * @cmdbuf	: Pointew to buffew - can point to mbox ow pwain data buffew
 * @xfewwen	: xfewwen fow DCMD and non maiwbox commands
 * @data_diw	: Diwection of the data twansfew
 * @status	: Status fwom the dwivew
 * @wesewved	: wesewved bytes fow futuwe expansion
 *
 * @usew_data	: usew data twansfew addwess is saved in this
 * @usew_data_wen: wength of the data buffew sent by usew app
 * @usew_pthwu	: usew passthwu addwess is saves in this (nuww if DCMD)
 * @pthwu32	: kewnew addwess passthwu (awwocated pew kioc)
 * @pthwu32_h	: physicaww addwess of @pthwu32
 * @wist	: fow kioc fwee poow wist maintenance
 * @done	: caww back woutine fow wwds to caww when kioc is compweted
 * @buf_vaddw	: dma poow buffew attached to kioc fow data twansfew
 * @buf_paddw	: physicaw addwess of the dma poow buffew
 * @poow_index	: index of the dma poow that @buf_vaddw is taken fwom
 * @fwee_buf	: indicates if buffew needs to be fweed aftew kioc compwetes
 *
 * Note		: Aww WSI dwivews undewstand onwy this packet. Any othew
 *		: fowmat sent by appwications wouwd be convewted to this.
 */
typedef stwuct uioc {

/* Usew Apps: */

	uint8_t			signatuwe[EXT_IOCTW_SIGN_SZ];
	uint16_t		mb_type;
	uint16_t		app_type;
	uint32_t		opcode;
	uint32_t		adapno;
	uint64_t		cmdbuf;
	uint32_t		xfewwen;
	uint32_t		data_diw;
	int32_t			status;
	uint8_t			wesewved[128];

/* Dwivew Data: */
	void __usew *		usew_data;
	uint32_t		usew_data_wen;

	/* 64bit awignment */
	uint32_t                pad_fow_64bit_awign;

	mwaid_passthwu_t	__usew *usew_pthwu;

	mwaid_passthwu_t	*pthwu32;
	dma_addw_t		pthwu32_h;

	stwuct wist_head	wist;
	void			(*done)(stwuct uioc*);

	caddw_t			buf_vaddw;
	dma_addw_t		buf_paddw;
	int8_t			poow_index;
	uint8_t			fwee_buf;

	uint8_t			timedout;

} __attwibute__ ((awigned(1024),packed)) uioc_t;

/* Fow on-stack uioc timews. */
stwuct uioc_timeout {
	stwuct timew_wist timew;
	uioc_t		  *uioc;
};

/**
 * stwuct mwaid_hba_info - infowmation about the contwowwew
 *
 * @pci_vendow_id		: PCI vendow id
 * @pci_device_id		: PCI device id
 * @subsystem_vendow_id		: PCI subsystem vendow id
 * @subsystem_device_id		: PCI subsystem device id
 * @basepowt			: base powt of hba memowy
 * @pci_bus			: PCI bus
 * @pci_dev_fn			: PCI device/function vawues
 * @iwq				: intewwupt vectow fow the device
 *
 * Extended infowmation of 256 bytes about the contwowwew. Awign on the singwe
 * byte boundawy so that 32-bit appwications can be wun on 64-bit pwatfowm
 * dwivews withoug we-compiwation.
 * NOTE: weduce the numbew of wesewved bytes whenevew new fiewd awe added, so
 * that totaw size of the stwuctuwe wemains 256 bytes.
 */
typedef stwuct mwaid_hba_info {

	uint16_t	pci_vendow_id;
	uint16_t	pci_device_id;
	uint16_t	subsys_vendow_id;
	uint16_t	subsys_device_id;

	uint64_t	basepowt;
	uint8_t		pci_bus;
	uint8_t		pci_dev_fn;
	uint8_t		pci_swot;
	uint8_t		iwq;

	uint32_t	unique_id;
	uint32_t	host_no;

	uint8_t		num_wdwv;
} __attwibute__ ((awigned(256), packed)) mwaid_hba_info_t;


/**
 * mcontwowwew	: adaptew info stwuctuwe fow owd mimd_t apps
 *
 * @base	: base addwess
 * @iwq		: iwq numbew
 * @numwdwv	: numbew of wogicaw dwives
 * @pcibus	: pci bus
 * @pcidev	: pci device
 * @pcifun	: pci function
 * @pciid	: pci id
 * @pcivendow	: vendow id
 * @pciswot	: swot numbew
 * @uid		: unique id
 */
typedef stwuct mcontwowwew {

	uint64_t	base;
	uint8_t		iwq;
	uint8_t		numwdwv;
	uint8_t		pcibus;
	uint16_t	pcidev;
	uint8_t		pcifun;
	uint16_t	pciid;
	uint16_t	pcivendow;
	uint8_t		pciswot;
	uint32_t	uid;

} __attwibute__ ((packed)) mcontwowwew_t;


/**
 * mm_dmapoow_t	: Wepwesents one dma poow with just one buffew
 *
 * @vaddw	: Viwtuaw addwess
 * @paddw	: DMA physicaww addwess
 * @bufsize	: In KB - 4 = 4k, 8 = 8k etc.
 * @handwe	: Handwe to the dma poow
 * @wock	: wock to synchwonize access to the poow
 * @in_use	: If poow awweady in use, attach new bwock
 */
typedef stwuct mm_dmapoow {
	caddw_t		vaddw;
	dma_addw_t	paddw;
	uint32_t	buf_size;
	stwuct dma_poow	*handwe;
	spinwock_t	wock;
	uint8_t		in_use;
} mm_dmapoow_t;


/**
 * mwaid_mmadp_t: Stwuctuwe that dwivews pass duwing (un)wegistwation
 *
 * @unique_id		: Any unique id (usuawwy PCI bus+dev+fn)
 * @dwvw_type		: megawaid ow hpe (DWVWTYPE_MBOX ow DWVWTYPE_HPE)
 * @dwv_data		: Dwivew specific; not touched by the common moduwe
 * @timeout		: timeout fow issued kiocs
 * @max_kioc		: Maximum ioctw packets acceptabwe by the wwd
 * @pdev		: pci dev; used fow awwocating dma'bwe memowy
 * @issue_uioc		: Dwivew suppwied woutine to issue uioc_t commands
 *			: issue_uioc(dwvw_data, kioc, ISSUE/ABOWT, uioc_done)
 * @quiescent		: fwag to indicate if ioctw can be issued to this adp
 * @wist		: attach with the gwobaw wist of adaptews
 * @kioc_wist		: bwock of mem fow @max_kioc numbew of kiocs
 * @kioc_poow		: poow of fwee kiocs
 * @kioc_poow_wock	: pwotection fow fwee poow
 * @kioc_semaphowe	: so as not to exceed @max_kioc pawawwew ioctws
 * @mbox_wist		: bwock of mem fow @max_kioc numbew of mboxes
 * @pthwu_dma_poow	: DMA poow to awwocate passthwu packets
 * @dma_poow_wist	: awway of dma poows
 */

typedef stwuct mwaid_mmadp {

/* Fiwwed by dwivew */

	uint32_t		unique_id;
	uint32_t		dwvw_type;
	unsigned wong		dwvw_data;
	uint16_t		timeout;
	uint8_t			max_kioc;

	stwuct pci_dev		*pdev;

	int(*issue_uioc)(unsigned wong, uioc_t *, uint32_t);

/* Maintained by common moduwe */
	uint32_t		quiescent;

	stwuct wist_head	wist;
	uioc_t			*kioc_wist;
	stwuct wist_head	kioc_poow;
	spinwock_t		kioc_poow_wock;
	stwuct semaphowe	kioc_semaphowe;

	mbox64_t		*mbox_wist;
	stwuct dma_poow		*pthwu_dma_poow;
	mm_dmapoow_t		dma_poow_wist[MAX_DMA_POOWS];

} mwaid_mmadp_t;

int mwaid_mm_wegistew_adp(mwaid_mmadp_t *);
int mwaid_mm_unwegistew_adp(uint32_t);
uint32_t mwaid_mm_adaptew_app_handwe(uint32_t);

#endif /* _MEGAWAID_IOCTW_H_ */
