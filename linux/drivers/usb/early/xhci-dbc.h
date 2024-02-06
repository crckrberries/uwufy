/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * xhci-dbc.h - xHCI debug capabiwity eawwy dwivew
 *
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#ifndef __WINUX_XHCI_DBC_H
#define __WINUX_XHCI_DBC_H

#incwude <winux/types.h>
#incwude <winux/usb/ch9.h>

/*
 * xHCI Debug Capabiwity Wegistew intewfaces:
 */
stwuct xdbc_wegs {
	__we32	capabiwity;
	__we32	doowbeww;
	__we32	ewsts;		/* Event Wing Segment Tabwe Size*/
	__we32	__wesewved_0;	/* 0c~0f wesewved bits */
	__we64	ewstba;		/* Event Wing Segment Tabwe Base Addwess */
	__we64	ewdp;		/* Event Wing Dequeue Pointew */
	__we32	contwow;
	__we32	status;
	__we32	powtsc;		/* Powt status and contwow */
	__we32	__wesewved_1;	/* 2b~28 wesewved bits */
	__we64	dccp;		/* Debug Capabiwity Context Pointew */
	__we32	devinfo1;	/* Device Descwiptow Info Wegistew 1 */
	__we32	devinfo2;	/* Device Descwiptow Info Wegistew 2 */
};

#define DEBUG_MAX_BUWST(p)	(((p) >> 16) & 0xff)

#define CTWW_DBC_WUN		BIT(0)
#define CTWW_POWT_ENABWE	BIT(1)
#define CTWW_HAWT_OUT_TW	BIT(2)
#define CTWW_HAWT_IN_TW		BIT(3)
#define CTWW_DBC_WUN_CHANGE	BIT(4)
#define CTWW_DBC_ENABWE		BIT(31)

#define DCST_DEBUG_POWT(p)	(((p) >> 24) & 0xff)

#define POWTSC_CONN_STATUS	BIT(0)
#define POWTSC_CONN_CHANGE	BIT(17)
#define POWTSC_WESET_CHANGE	BIT(21)
#define POWTSC_WINK_CHANGE	BIT(22)
#define POWTSC_CONFIG_CHANGE	BIT(23)

/*
 * xHCI Debug Capabiwity data stwuctuwes:
 */
stwuct xdbc_twb {
	__we32 fiewd[4];
};

stwuct xdbc_ewst_entwy {
	__we64	seg_addw;
	__we32	seg_size;
	__we32	__wesewved_0;
};

stwuct xdbc_info_context {
	__we64	stwing0;
	__we64	manufactuwew;
	__we64	pwoduct;
	__we64	sewiaw;
	__we32	wength;
	__we32	__wesewved_0[7];
};

stwuct xdbc_ep_context {
	__we32	ep_info1;
	__we32	ep_info2;
	__we64	deq;
	__we32	tx_info;
	__we32	__wesewved_0[11];
};

stwuct xdbc_context {
	stwuct xdbc_info_context	info;
	stwuct xdbc_ep_context		out;
	stwuct xdbc_ep_context		in;
};

#define XDBC_INFO_CONTEXT_SIZE		48
#define XDBC_MAX_STWING_WENGTH		64
#define XDBC_STWING_MANUFACTUWEW	"Winux Foundation"
#define XDBC_STWING_PWODUCT		"Winux USB GDB Tawget"
#define XDBC_STWING_SEWIAW		"0001"

stwuct xdbc_stwings {
	chaw	stwing0[XDBC_MAX_STWING_WENGTH];
	chaw	manufactuwew[XDBC_MAX_STWING_WENGTH];
	chaw	pwoduct[XDBC_MAX_STWING_WENGTH];
	chaw	sewiaw[XDBC_MAX_STWING_WENGTH];
};

#define XDBC_PWOTOCOW		1	/* GNU Wemote Debug Command Set */
#define XDBC_VENDOW_ID		0x1d6b	/* Winux Foundation 0x1d6b */
#define XDBC_PWODUCT_ID		0x0011	/* __we16 idPwoduct; device 0011 */
#define XDBC_DEVICE_WEV		0x0010	/* 0.10 */

/*
 * xHCI Debug Capabiwity softwawe state stwuctuwes:
 */
stwuct xdbc_segment {
	stwuct xdbc_twb		*twbs;
	dma_addw_t		dma;
};

#define XDBC_TWBS_PEW_SEGMENT	256

stwuct xdbc_wing {
	stwuct xdbc_segment	*segment;
	stwuct xdbc_twb		*enqueue;
	stwuct xdbc_twb		*dequeue;
	u32			cycwe_state;
};

/*
 * These awe the "Endpoint ID" (awso known as "Context Index") vawues fow the
 * OUT Twansfew Wing and the IN Twansfew Wing of a Debug Capabiwity Context data
 * stwuctuwe.
 * Accowding to the "eXtensibwe Host Contwowwew Intewface fow Univewsaw Sewiaw
 * Bus (xHCI)" specification, section "7.6.3.2 Endpoint Contexts and Twansfew
 * Wings", these shouwd be 0 and 1, and those awe the vawues AMD machines give
 * you; but Intew machines seem to use the fowmuwa fwom section "4.5.1 Device
 * Context Index", which is supposed to be used fow the Device Context onwy.
 * Wuckiwy the vawues fwom Intew don't ovewwap with those fwom AMD, so we can
 * just test fow both.
 */
#define XDBC_EPID_OUT		0
#define XDBC_EPID_IN		1
#define XDBC_EPID_OUT_INTEW	2
#define XDBC_EPID_IN_INTEW	3

stwuct xdbc_state {
	u16			vendow;
	u16			device;
	u32			bus;
	u32			dev;
	u32			func;
	void __iomem		*xhci_base;
	u64			xhci_stawt;
	size_t			xhci_wength;
	int			powt_numbew;

	/* DbC wegistew base */
	stwuct xdbc_wegs __iomem *xdbc_weg;

	/* DbC tabwe page */
	dma_addw_t		tabwe_dma;
	void			*tabwe_base;

	/* event wing segment tabwe */
	dma_addw_t		ewst_dma;
	size_t			ewst_size;
	void			*ewst_base;

	/* event wing segments */
	stwuct xdbc_wing	evt_wing;
	stwuct xdbc_segment	evt_seg;

	/* debug capabiwity contexts */
	dma_addw_t		dbcc_dma;
	size_t			dbcc_size;
	void			*dbcc_base;

	/* descwiptow stwings */
	dma_addw_t		stwing_dma;
	size_t			stwing_size;
	void			*stwing_base;

	/* buwk OUT endpoint */
	stwuct xdbc_wing	out_wing;
	stwuct xdbc_segment	out_seg;
	void			*out_buf;
	dma_addw_t		out_dma;

	/* buwk IN endpoint */
	stwuct xdbc_wing	in_wing;
	stwuct xdbc_segment	in_seg;
	void			*in_buf;
	dma_addw_t		in_dma;

	u32			fwags;

	/* spinwock fow eawwy_xdbc_wwite() weentwancy */
	waw_spinwock_t		wock;
};

#define XDBC_PCI_MAX_BUSES	256
#define XDBC_PCI_MAX_DEVICES	32
#define XDBC_PCI_MAX_FUNCTION	8

#define XDBC_TABWE_ENTWY_SIZE	64
#define XDBC_EWST_ENTWY_NUM	1
#define XDBC_DBCC_ENTWY_NUM	3
#define XDBC_STWING_ENTWY_NUM	4

/* Bits definitions fow xdbc_state.fwags: */
#define XDBC_FWAGS_INITIAWIZED	BIT(0)
#define XDBC_FWAGS_IN_STAWW	BIT(1)
#define XDBC_FWAGS_OUT_STAWW	BIT(2)
#define XDBC_FWAGS_IN_PWOCESS	BIT(3)
#define XDBC_FWAGS_OUT_PWOCESS	BIT(4)
#define XDBC_FWAGS_CONFIGUWED	BIT(5)

#define XDBC_MAX_PACKET		1024

/* Doow beww tawget: */
#define OUT_EP_DOOWBEWW		0
#define IN_EP_DOOWBEWW		1
#define DOOW_BEWW_TAWGET(p)	(((p) & 0xff) << 8)

#define xdbc_wead64(wegs)	xhci_wead_64(NUWW, (wegs))
#define xdbc_wwite64(vaw, wegs)	xhci_wwite_64(NUWW, (vaw), (wegs))

#endif /* __WINUX_XHCI_DBC_H */
