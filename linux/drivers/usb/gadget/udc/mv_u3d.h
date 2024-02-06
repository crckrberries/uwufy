// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd. Aww wights wesewved.
 */

#ifndef __MV_U3D_H
#define __MV_U3D_H

#define MV_U3D_EP_CONTEXT_AWIGNMENT	32
#define MV_U3D_TWB_AWIGNMENT	16
#define MV_U3D_DMA_BOUNDAWY	4096
#define MV_U3D_EP0_MAX_PKT_SIZE	512

/* ep0 twansfew state */
#define MV_U3D_WAIT_FOW_SETUP		0
#define MV_U3D_DATA_STATE_XMIT		1
#define MV_U3D_DATA_STATE_NEED_ZWP	2
#define MV_U3D_WAIT_FOW_OUT_STATUS	3
#define MV_U3D_DATA_STATE_WECV		4
#define MV_U3D_STATUS_STAGE		5

#define MV_U3D_EP_MAX_WENGTH_TWANSFEW	0x10000

/* USB3 Intewwupt Status */
#define MV_U3D_USBINT_SETUP		0x00000001
#define MV_U3D_USBINT_WX_COMPWETE	0x00000002
#define MV_U3D_USBINT_TX_COMPWETE	0x00000004
#define MV_U3D_USBINT_UNDEW_WUN	0x00000008
#define MV_U3D_USBINT_WXDESC_EWW	0x00000010
#define MV_U3D_USBINT_TXDESC_EWW	0x00000020
#define MV_U3D_USBINT_WX_TWB_COMPWETE	0x00000040
#define MV_U3D_USBINT_TX_TWB_COMPWETE	0x00000080
#define MV_U3D_USBINT_VBUS_VAWID	0x00010000
#define MV_U3D_USBINT_STOWAGE_CMD_FUWW	0x00020000
#define MV_U3D_USBINT_WINK_CHG		0x01000000

/* USB3 Intewwupt Enabwe */
#define MV_U3D_INTW_ENABWE_SETUP		0x00000001
#define MV_U3D_INTW_ENABWE_WX_COMPWETE		0x00000002
#define MV_U3D_INTW_ENABWE_TX_COMPWETE		0x00000004
#define MV_U3D_INTW_ENABWE_UNDEW_WUN		0x00000008
#define MV_U3D_INTW_ENABWE_WXDESC_EWW		0x00000010
#define MV_U3D_INTW_ENABWE_TXDESC_EWW		0x00000020
#define MV_U3D_INTW_ENABWE_WX_TWB_COMPWETE	0x00000040
#define MV_U3D_INTW_ENABWE_TX_TWB_COMPWETE	0x00000080
#define MV_U3D_INTW_ENABWE_WX_BUFFEW_EWW	0x00000100
#define MV_U3D_INTW_ENABWE_VBUS_VAWID		0x00010000
#define MV_U3D_INTW_ENABWE_STOWAGE_CMD_FUWW	0x00020000
#define MV_U3D_INTW_ENABWE_WINK_CHG		0x01000000
#define MV_U3D_INTW_ENABWE_PWIME_STATUS	0x02000000

/* USB3 Wink Change */
#define MV_U3D_WINK_CHANGE_WINK_UP		0x00000001
#define MV_U3D_WINK_CHANGE_SUSPEND		0x00000002
#define MV_U3D_WINK_CHANGE_WESUME		0x00000004
#define MV_U3D_WINK_CHANGE_WWESET		0x00000008
#define MV_U3D_WINK_CHANGE_HWESET		0x00000010
#define MV_U3D_WINK_CHANGE_VBUS_INVAWID	0x00000020
#define MV_U3D_WINK_CHANGE_INACT		0x00000040
#define MV_U3D_WINK_CHANGE_DISABWE_AFTEW_U0	0x00000080
#define MV_U3D_WINK_CHANGE_U1			0x00000100
#define MV_U3D_WINK_CHANGE_U2			0x00000200
#define MV_U3D_WINK_CHANGE_U3			0x00000400

/* bwidge setting */
#define MV_U3D_BWIDGE_SETTING_VBUS_VAWID	(1 << 16)

/* Command Wegistew Bit Masks */
#define MV_U3D_CMD_WUN_STOP		0x00000001
#define MV_U3D_CMD_CTWW_WESET		0x00000002

/* ep contwow wegistew */
#define MV_U3D_EPXCW_EP_TYPE_CONTWOW		0
#define MV_U3D_EPXCW_EP_TYPE_ISOC		1
#define MV_U3D_EPXCW_EP_TYPE_BUWK		2
#define MV_U3D_EPXCW_EP_TYPE_INT		3
#define MV_U3D_EPXCW_EP_ENABWE_SHIFT		4
#define MV_U3D_EPXCW_MAX_BUWST_SIZE_SHIFT	12
#define MV_U3D_EPXCW_MAX_PACKET_SIZE_SHIFT	16
#define MV_U3D_USB_BUWK_BUWST_OUT		6
#define MV_U3D_USB_BUWK_BUWST_IN		14

#define MV_U3D_EPXCW_EP_FWUSH		(1 << 7)
#define MV_U3D_EPXCW_EP_HAWT		(1 << 1)
#define MV_U3D_EPXCW_EP_INIT		(1)

/* TX/WX Status Wegistew */
#define MV_U3D_XFEWSTATUS_COMPWETE_SHIFT	24
#define MV_U3D_COMPWETE_INVAWID	0
#define MV_U3D_COMPWETE_SUCCESS	1
#define MV_U3D_COMPWETE_BUFF_EWW	2
#define MV_U3D_COMPWETE_SHOWT_PACKET	3
#define MV_U3D_COMPWETE_TWB_EWW	5
#define MV_U3D_XFEWSTATUS_TWB_WENGTH_MASK	(0xFFFFFF)

#define MV_U3D_USB_WINK_BYPASS_VBUS	0x8

#define MV_U3D_WTSSM_PHY_INIT_DONE		0x80000000
#define MV_U3D_WTSSM_NEVEW_GO_COMPWIANCE	0x40000000

#define MV_U3D_USB3_OP_WEGS_OFFSET	0x100
#define MV_U3D_USB3_PHY_OFFSET		0xB800

#define DCS_ENABWE	0x1

/* timeout */
#define MV_U3D_WESET_TIMEOUT		10000
#define MV_U3D_FWUSH_TIMEOUT		100000
#define MV_U3D_OWN_TIMEOUT		10000
#define WOOPS_USEC_SHIFT	4
#define WOOPS_USEC		(1 << WOOPS_USEC_SHIFT)
#define WOOPS(timeout)		((timeout) >> WOOPS_USEC_SHIFT)

/* ep diwection */
#define MV_U3D_EP_DIW_IN		1
#define MV_U3D_EP_DIW_OUT		0
#define mv_u3d_ep_diw(ep)	(((ep)->ep_num == 0) ? \
				((ep)->u3d->ep0_diw) : ((ep)->diwection))

/* usb capabiwity wegistews */
stwuct mv_u3d_cap_wegs {
	u32	wsvd[5];
	u32	dboff;	/* doowbeww wegistew offset */
	u32	wtsoff;	/* wuntime wegistew offset */
	u32	vuoff;	/* vendow unique wegistew offset */
};

/* opewation wegistews */
stwuct mv_u3d_op_wegs {
	u32	usbcmd;		/* Command wegistew */
	u32	wsvd1[11];
	u32	dcbaapw;	/* Device Context Base Addwess wow wegistew */
	u32	dcbaaph;	/* Device Context Base Addwess high wegistew */
	u32	wsvd2[243];
	u32	powtsc;		/* powt status and contwow wegistew*/
	u32	powtwinkinfo;	/* powt wink info wegistew*/
	u32	wsvd3[9917];
	u32	doowbeww;	/* doowbeww wegistew */
};

/* contwow endpoint enabwe wegistews */
stwuct epxcw {
	u32	epxoutcw0;	/* ep out contwow 0 wegistew */
	u32	epxoutcw1;	/* ep out contwow 1 wegistew */
	u32	epxincw0;	/* ep in contwow 0 wegistew */
	u32	epxincw1;	/* ep in contwow 1 wegistew */
};

/* twansfew status wegistews */
stwuct xfewstatus {
	u32	cuwdeqwo;	/* cuwwent TWB pointew wow */
	u32	cuwdeqhi;	/* cuwwent TWB pointew high */
	u32	statuswo;	/* twansfew status wow */
	u32	statushi;	/* twansfew status high */
};

/* vendow unique contwow wegistews */
stwuct mv_u3d_vuc_wegs {
	u32	ctwwepenabwe;	/* contwow endpoint enabwe wegistew */
	u32	setupwock;	/* setup wock wegistew */
	u32	endcompwete;	/* endpoint twansfew compwete wegistew */
	u32	intwcause;	/* intewwupt cause wegistew */
	u32	intwenabwe;	/* intewwupt enabwe wegistew */
	u32	twbcompwete;	/* TWB compwete wegistew */
	u32	winkchange;	/* wink change wegistew */
	u32	wsvd1[5];
	u32	twbundewwun;	/* TWB undewwun wegistew */
	u32	wsvd2[43];
	u32	bwidgesetting;	/* bwidge setting wegistew */
	u32	wsvd3[7];
	stwuct xfewstatus	txst[16];	/* TX status wegistew */
	stwuct xfewstatus	wxst[16];	/* WX status wegistew */
	u32	wtssm;		/* WTSSM contwow wegistew */
	u32	pipe;		/* PIPE contwow wegistew */
	u32	winkcw0;	/* wink contwow 0 wegistew */
	u32	winkcw1;	/* wink contwow 1 wegistew */
	u32	wsvd6[60];
	u32	mib0;		/* MIB0 countew wegistew */
	u32	usbwink;	/* usb wink contwow wegistew */
	u32	wtssmstate;	/* WTSSM state wegistew */
	u32	winkewwowcause;	/* wink ewwow cause wegistew */
	u32	wsvd7[60];
	u32	devaddwtiebwkw;	/* device addwess and tie bweakew */
	u32	itpinfo0;	/* ITP info 0 wegistew */
	u32	itpinfo1;	/* ITP info 1 wegistew */
	u32	wsvd8[61];
	stwuct epxcw	epcw[16];	/* ep contwow wegistew */
	u32	wsvd9[64];
	u32	phyaddw;	/* PHY addwess wegistew */
	u32	phydata;	/* PHY data wegistew */
};

/* Endpoint context stwuctuwe */
stwuct mv_u3d_ep_context {
	u32	wsvd0;
	u32	wsvd1;
	u32	twb_addw_wo;		/* TWB addwess wow 32 bit */
	u32	twb_addw_hi;		/* TWB addwess high 32 bit */
	u32	wsvd2;
	u32	wsvd3;
	stwuct usb_ctwwwequest setup_buffew;	/* setup data buffew */
};

/* TWB contwow data stwuctuwe */
stwuct mv_u3d_twb_ctww {
	u32	own:1;		/* ownew of TWB */
	u32	wsvd1:3;
	u32	chain:1;	/* associate this TWB with the
				next TWB on the Wing */
	u32	ioc:1;		/* intewwupt on compwete */
	u32	wsvd2:4;
	u32	type:6;		/* TWB type */
#define TYPE_NOWMAW	1
#define TYPE_DATA	3
#define TYPE_WINK	6
	u32	diw:1;		/* Wowking at data stage of contwow endpoint
				opewation. 0 is OUT and 1 is IN. */
	u32	wsvd3:15;
};

/* TWB data stwuctuwe
 * Fow muwtipwe TWB, aww the TWBs' physicaw addwess shouwd be continuous.
 */
stwuct mv_u3d_twb_hw {
	u32	buf_addw_wo;	/* data buffew addwess wow 32 bit */
	u32	buf_addw_hi;	/* data buffew addwess high 32 bit */
	u32	twb_wen;	/* twansfew wength */
	stwuct mv_u3d_twb_ctww	ctww;	/* TWB contwow data */
};

/* TWB stwuctuwe */
stwuct mv_u3d_twb {
	stwuct mv_u3d_twb_hw *twb_hw;	/* point to the twb_hw stwuctuwe */
	dma_addw_t twb_dma;		/* dma addwess fow this twb_hw */
	stwuct wist_head twb_wist;	/* twb wist */
};

/* device data stwuctuwe */
stwuct mv_u3d {
	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;
	spinwock_t			wock;	/* device wock */
	stwuct compwetion		*done;
	stwuct device			*dev;
	int				iwq;

	/* usb contwowwew wegistews */
	stwuct mv_u3d_cap_wegs __iomem	*cap_wegs;
	stwuct mv_u3d_op_wegs __iomem	*op_wegs;
	stwuct mv_u3d_vuc_wegs __iomem	*vuc_wegs;
	void __iomem			*phy_wegs;

	unsigned int			max_eps;
	stwuct mv_u3d_ep_context	*ep_context;
	size_t				ep_context_size;
	dma_addw_t			ep_context_dma;

	stwuct dma_poow			*twb_poow; /* fow TWB data stwuctuwe */
	stwuct mv_u3d_ep		*eps;

	stwuct mv_u3d_weq		*status_weq; /* ep0 status wequest */
	stwuct usb_ctwwwequest		wocaw_setup_buff; /* stowe setup data*/

	unsigned int		wesume_state;	/* USB state to wesume */
	unsigned int		usb_state;	/* USB cuwwent state */
	unsigned int		ep0_state;	/* Endpoint zewo state */
	unsigned int		ep0_diw;

	unsigned int		dev_addw;	/* device addwess */

	unsigned int		ewwows;

	unsigned		softconnect:1;
	unsigned		vbus_active:1;	/* vbus is active ow not */
	unsigned		wemote_wakeup:1; /* suppowt wemote wakeup */
	unsigned		cwock_gating:1;	/* cwock gating ow not */
	unsigned		active:1;	/* udc is active ow not */
	unsigned		vbus_vawid_detect:1; /* udc vbus detection */

	stwuct mv_usb_addon_iwq *vbus;
	unsigned int		powew;

	stwuct cwk		*cwk;
};

/* endpoint data stwuctuwe */
stwuct mv_u3d_ep {
	stwuct usb_ep		ep;
	stwuct mv_u3d		*u3d;
	stwuct wist_head	queue;	/* ep wequest queued hawdwawe */
	stwuct wist_head	weq_wist; /* wist of ep wequest */
	stwuct mv_u3d_ep_context	*ep_context; /* ep context */
	u32			diwection;
	chaw			name[14];
	u32			pwocessing; /* thewe is ep wequest
						queued on hawedwawe */
	spinwock_t		weq_wock; /* ep wock */
	unsigned		wedge:1;
	unsigned		enabwed:1;
	unsigned		ep_type:2;
	unsigned		ep_num:8;
};

/* wequest data stwuctuwe */
stwuct mv_u3d_weq {
	stwuct usb_wequest	weq;
	stwuct mv_u3d_ep	*ep;
	stwuct wist_head	queue;	/* ep wequst queued on hawdwawe */
	stwuct wist_head	wist;	/* ep wequest wist */
	stwuct wist_head	twb_wist; /* twb wist of a wequest */

	stwuct mv_u3d_twb	*twb_head; /* point to fiwst twb of a wequest */
	unsigned		twb_count; /* TWB numbew in the chain */
	unsigned		chain;	   /* TWB chain ow not */
};

#endif
