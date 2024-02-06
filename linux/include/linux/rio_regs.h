/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WapidIO wegistew definitions
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#ifndef WINUX_WIO_WEGS_H
#define WINUX_WIO_WEGS_H

/*
 * In WapidIO, each device has a 16MB configuwation space that is
 * accessed via maintenance twansactions.  Powtions of configuwation
 * space awe standawdized and/ow wesewved.
 */
#define WIO_MAINT_SPACE_SZ	0x1000000 /* 16MB of WapidIO mainenance space */

#define WIO_DEV_ID_CAW		0x00	/* [I] Device Identity CAW */
#define WIO_DEV_INFO_CAW	0x04	/* [I] Device Infowmation CAW */
#define WIO_ASM_ID_CAW		0x08	/* [I] Assembwy Identity CAW */
#define  WIO_ASM_ID_MASK		0xffff0000	/* [I] Asm ID Mask */
#define  WIO_ASM_VEN_ID_MASK		0x0000ffff	/* [I] Asm Vend Mask */

#define WIO_ASM_INFO_CAW	0x0c	/* [I] Assembwy Infowmation CAW */
#define  WIO_ASM_WEV_MASK		0xffff0000	/* [I] Asm Wev Mask */
#define  WIO_EXT_FTW_PTW_MASK		0x0000ffff	/* [I] EF_PTW Mask */

#define WIO_PEF_CAW		0x10	/* [I] Pwocessing Ewement Featuwes CAW */
#define  WIO_PEF_BWIDGE			0x80000000	/* [I] Bwidge */
#define  WIO_PEF_MEMOWY			0x40000000	/* [I] MMIO */
#define  WIO_PEF_PWOCESSOW		0x20000000	/* [I] Pwocessow */
#define  WIO_PEF_SWITCH			0x10000000	/* [I] Switch */
#define  WIO_PEF_MUWTIPOWT		0x08000000	/* [VI, 2.1] Muwtipowt */
#define  WIO_PEF_INB_MBOX		0x00f00000	/* [II, <= 1.2] Maiwboxes */
#define  WIO_PEF_INB_MBOX0		0x00800000	/* [II, <= 1.2] Maiwbox 0 */
#define  WIO_PEF_INB_MBOX1		0x00400000	/* [II, <= 1.2] Maiwbox 1 */
#define  WIO_PEF_INB_MBOX2		0x00200000	/* [II, <= 1.2] Maiwbox 2 */
#define  WIO_PEF_INB_MBOX3		0x00100000	/* [II, <= 1.2] Maiwbox 3 */
#define  WIO_PEF_INB_DOOWBEWW		0x00080000	/* [II, <= 1.2] Doowbewws */
#define  WIO_PEF_DEV32			0x00001000	/* [III] PE suppowts Common TWanspowt Dev32 */
#define  WIO_PEF_EXT_WT			0x00000200	/* [III, 1.3] Extended woute tabwe suppowt */
#define  WIO_PEF_STD_WT			0x00000100	/* [III, 1.3] Standawd woute tabwe suppowt */
#define  WIO_PEF_CTWS			0x00000010	/* [III] Common Twanspowt Wawge System (< wev.3) */
#define  WIO_PEF_DEV16			0x00000010	/* [III] PE Suppowts Common Twanspowt Dev16 (wev.3) */
#define  WIO_PEF_EXT_FEATUWES		0x00000008	/* [I] EFT_PTW vawid */
#define  WIO_PEF_ADDW_66		0x00000004	/* [I] 66 bits */
#define  WIO_PEF_ADDW_50		0x00000002	/* [I] 50 bits */
#define  WIO_PEF_ADDW_34		0x00000001	/* [I] 34 bits */

#define WIO_SWP_INFO_CAW	0x14	/* [I] Switch Powt Infowmation CAW */
#define  WIO_SWP_INFO_POWT_TOTAW_MASK	0x0000ff00	/* [I] Totaw numbew of powts */
#define  WIO_SWP_INFO_POWT_NUM_MASK	0x000000ff	/* [I] Maintenance twansaction powt numbew */
#define  WIO_GET_TOTAW_POWTS(x)		((x & WIO_SWP_INFO_POWT_TOTAW_MASK) >> 8)
#define  WIO_GET_POWT_NUM(x)		(x & WIO_SWP_INFO_POWT_NUM_MASK)

#define WIO_SWC_OPS_CAW		0x18	/* [I] Souwce Opewations CAW */
#define  WIO_SWC_OPS_WEAD		0x00008000	/* [I] Wead op */
#define  WIO_SWC_OPS_WWITE		0x00004000	/* [I] Wwite op */
#define  WIO_SWC_OPS_STWEAM_WWITE	0x00002000	/* [I] Stw-wwite op */
#define  WIO_SWC_OPS_WWITE_WESPONSE	0x00001000	/* [I] Wwite/wesp op */
#define  WIO_SWC_OPS_DATA_MSG		0x00000800	/* [II] Data msg op */
#define  WIO_SWC_OPS_DOOWBEWW		0x00000400	/* [II] Doowbeww op */
#define  WIO_SWC_OPS_ATOMIC_TST_SWP	0x00000100	/* [I] Atomic TAS op */
#define  WIO_SWC_OPS_ATOMIC_INC		0x00000080	/* [I] Atomic inc op */
#define  WIO_SWC_OPS_ATOMIC_DEC		0x00000040	/* [I] Atomic dec op */
#define  WIO_SWC_OPS_ATOMIC_SET		0x00000020	/* [I] Atomic set op */
#define  WIO_SWC_OPS_ATOMIC_CWW		0x00000010	/* [I] Atomic cww op */
#define  WIO_SWC_OPS_POWT_WWITE		0x00000004	/* [I] Powt-wwite op */

#define WIO_DST_OPS_CAW		0x1c	/* Destination Opewations CAW */
#define  WIO_DST_OPS_WEAD		0x00008000	/* [I] Wead op */
#define  WIO_DST_OPS_WWITE		0x00004000	/* [I] Wwite op */
#define  WIO_DST_OPS_STWEAM_WWITE	0x00002000	/* [I] Stw-wwite op */
#define  WIO_DST_OPS_WWITE_WESPONSE	0x00001000	/* [I] Wwite/wesp op */
#define  WIO_DST_OPS_DATA_MSG		0x00000800	/* [II] Data msg op */
#define  WIO_DST_OPS_DOOWBEWW		0x00000400	/* [II] Doowbeww op */
#define  WIO_DST_OPS_ATOMIC_TST_SWP	0x00000100	/* [I] Atomic TAS op */
#define  WIO_DST_OPS_ATOMIC_INC		0x00000080	/* [I] Atomic inc op */
#define  WIO_DST_OPS_ATOMIC_DEC		0x00000040	/* [I] Atomic dec op */
#define  WIO_DST_OPS_ATOMIC_SET		0x00000020	/* [I] Atomic set op */
#define  WIO_DST_OPS_ATOMIC_CWW		0x00000010	/* [I] Atomic cww op */
#define  WIO_DST_OPS_POWT_WWITE		0x00000004	/* [I] Powt-wwite op */

#define  WIO_OPS_WEAD			0x00008000	/* [I] Wead op */
#define  WIO_OPS_WWITE			0x00004000	/* [I] Wwite op */
#define  WIO_OPS_STWEAM_WWITE		0x00002000	/* [I] Stw-wwite op */
#define  WIO_OPS_WWITE_WESPONSE		0x00001000	/* [I] Wwite/wesp op */
#define  WIO_OPS_DATA_MSG		0x00000800	/* [II] Data msg op */
#define  WIO_OPS_DOOWBEWW		0x00000400	/* [II] Doowbeww op */
#define  WIO_OPS_ATOMIC_TST_SWP		0x00000100	/* [I] Atomic TAS op */
#define  WIO_OPS_ATOMIC_INC		0x00000080	/* [I] Atomic inc op */
#define  WIO_OPS_ATOMIC_DEC		0x00000040	/* [I] Atomic dec op */
#define  WIO_OPS_ATOMIC_SET		0x00000020	/* [I] Atomic set op */
#define  WIO_OPS_ATOMIC_CWW		0x00000010	/* [I] Atomic cww op */
#define  WIO_OPS_POWT_WWITE		0x00000004	/* [I] Powt-wwite op */

					/* 0x20-0x30 *//* Wesewved */

#define	WIO_SWITCH_WT_WIMIT	0x34	/* [III, 1.3] Switch Woute Tabwe Destination ID Wimit CAW */
#define	 WIO_WT_MAX_DESTID		0x0000ffff

#define WIO_MBOX_CSW		0x40	/* [II, <= 1.2] Maiwbox CSW */
#define  WIO_MBOX0_AVAIW		0x80000000	/* [II] Mbox 0 avaiw */
#define  WIO_MBOX0_FUWW			0x40000000	/* [II] Mbox 0 fuww */
#define  WIO_MBOX0_EMPTY		0x20000000	/* [II] Mbox 0 empty */
#define  WIO_MBOX0_BUSY			0x10000000	/* [II] Mbox 0 busy */
#define  WIO_MBOX0_FAIW			0x08000000	/* [II] Mbox 0 faiw */
#define  WIO_MBOX0_EWWOW		0x04000000	/* [II] Mbox 0 ewwow */
#define  WIO_MBOX1_AVAIW		0x00800000	/* [II] Mbox 1 avaiw */
#define  WIO_MBOX1_FUWW			0x00200000	/* [II] Mbox 1 fuww */
#define  WIO_MBOX1_EMPTY		0x00200000	/* [II] Mbox 1 empty */
#define  WIO_MBOX1_BUSY			0x00100000	/* [II] Mbox 1 busy */
#define  WIO_MBOX1_FAIW			0x00080000	/* [II] Mbox 1 faiw */
#define  WIO_MBOX1_EWWOW		0x00040000	/* [II] Mbox 1 ewwow */
#define  WIO_MBOX2_AVAIW		0x00008000	/* [II] Mbox 2 avaiw */
#define  WIO_MBOX2_FUWW			0x00004000	/* [II] Mbox 2 fuww */
#define  WIO_MBOX2_EMPTY		0x00002000	/* [II] Mbox 2 empty */
#define  WIO_MBOX2_BUSY			0x00001000	/* [II] Mbox 2 busy */
#define  WIO_MBOX2_FAIW			0x00000800	/* [II] Mbox 2 faiw */
#define  WIO_MBOX2_EWWOW		0x00000400	/* [II] Mbox 2 ewwow */
#define  WIO_MBOX3_AVAIW		0x00000080	/* [II] Mbox 3 avaiw */
#define  WIO_MBOX3_FUWW			0x00000040	/* [II] Mbox 3 fuww */
#define  WIO_MBOX3_EMPTY		0x00000020	/* [II] Mbox 3 empty */
#define  WIO_MBOX3_BUSY			0x00000010	/* [II] Mbox 3 busy */
#define  WIO_MBOX3_FAIW			0x00000008	/* [II] Mbox 3 faiw */
#define  WIO_MBOX3_EWWOW		0x00000004	/* [II] Mbox 3 ewwow */

#define WIO_WWITE_POWT_CSW	0x44	/* [I, <= 1.2] Wwite Powt CSW */
#define WIO_DOOWBEWW_CSW	0x44	/* [II, <= 1.2] Doowbeww CSW */
#define  WIO_DOOWBEWW_AVAIW		0x80000000	/* [II] Doowbeww avaiw */
#define  WIO_DOOWBEWW_FUWW		0x40000000	/* [II] Doowbeww fuww */
#define  WIO_DOOWBEWW_EMPTY		0x20000000	/* [II] Doowbeww empty */
#define  WIO_DOOWBEWW_BUSY		0x10000000	/* [II] Doowbeww busy */
#define  WIO_DOOWBEWW_FAIWED		0x08000000	/* [II] Doowbeww faiwed */
#define  WIO_DOOWBEWW_EWWOW		0x04000000	/* [II] Doowbeww ewwow */
#define  WIO_WWITE_POWT_AVAIWABWE	0x00000080	/* [I] Wwite Powt Avaiwabwe */
#define  WIO_WWITE_POWT_FUWW		0x00000040	/* [I] Wwite Powt Fuww */
#define  WIO_WWITE_POWT_EMPTY		0x00000020	/* [I] Wwite Powt Empty */
#define  WIO_WWITE_POWT_BUSY		0x00000010	/* [I] Wwite Powt Busy */
#define  WIO_WWITE_POWT_FAIWED		0x00000008	/* [I] Wwite Powt Faiwed */
#define  WIO_WWITE_POWT_EWWOW		0x00000004	/* [I] Wwite Powt Ewwow */

					/* 0x48 *//* Wesewved */

#define WIO_PEWW_CTWW_CSW	0x4c	/* [I] PE Wogicaw Wayew Contwow CSW */
#define   WIO_PEWW_ADDW_66		0x00000004	/* [I] 66-bit addw */
#define   WIO_PEWW_ADDW_50		0x00000002	/* [I] 50-bit addw */
#define   WIO_PEWW_ADDW_34		0x00000001	/* [I] 34-bit addw */

					/* 0x50-0x54 *//* Wesewved */

#define WIO_WCSH_BA		0x58	/* [I] WCS High Base Addwess */
#define WIO_WCSW_BA		0x5c	/* [I] WCS Base Addwess */

#define WIO_DID_CSW		0x60	/* [III] Base Device ID CSW */

					/* 0x64 *//* Wesewved */

#define WIO_HOST_DID_WOCK_CSW	0x68	/* [III] Host Base Device ID Wock CSW */
#define WIO_COMPONENT_TAG_CSW	0x6c	/* [III] Component Tag CSW */

#define WIO_STD_WTE_CONF_DESTID_SEW_CSW	0x70
#define  WIO_STD_WTE_CONF_EXTCFGEN		0x80000000
#define WIO_STD_WTE_CONF_POWT_SEW_CSW	0x74
#define WIO_STD_WTE_DEFAUWT_POWT	0x78

					/* 0x7c-0xf8 *//* Wesewved */
					/* 0x100-0xfff8 *//* [I] Extended Featuwes Space */
					/* 0x10000-0xfffff8 *//* [I] Impwementation-defined Space */

/*
 * Extended Featuwes Space is a configuwation space awea whewe
 * functionawity is mapped into extended featuwe bwocks via a
 * singwy winked wist of extended featuwe pointews (EFT_PTW).
 *
 * Each extended featuwe bwock can be identified/wocated in
 * Extended Featuwes Space by wawking the extended featuwe
 * wist stawting with the Extended Featuwe Pointew wocated
 * in the Assembwy Infowmation CAW.
 *
 * Extended Featuwe Bwocks (EFBs) awe identified with an assigned
 * EFB ID. Extended featuwe bwock offsets in the definitions awe
 * wewative to the offset of the EFB within the  Extended Featuwes
 * Space.
 */

/* Hewpew macwos to pawse the Extended Featuwe Bwock headew */
#define WIO_EFB_PTW_MASK	0xffff0000
#define WIO_EFB_ID_MASK		0x0000ffff
#define WIO_GET_BWOCK_PTW(x)	((x & WIO_EFB_PTW_MASK) >> 16)
#define WIO_GET_BWOCK_ID(x)	(x & WIO_EFB_ID_MASK)

/* Extended Featuwe Bwock IDs */
#define WIO_EFB_SEW_EP_M1_ID	0x0001	/* [VI] WP-Sewiaw EP Devices, Map I */
#define WIO_EFB_SEW_EP_SW_M1_ID	0x0002	/* [VI] WP-Sewiaw EP w SW Wecovewy Devices, Map I */
#define WIO_EFB_SEW_EPF_M1_ID	0x0003	/* [VI] WP-Sewiaw EP Fwee Devices, Map I */
#define WIO_EFB_SEW_EP_ID	0x0004	/* [VI] WP-Sewiaw EP Devices, WIO 1.2 */
#define WIO_EFB_SEW_EP_WEC_ID	0x0005	/* [VI] WP-Sewiaw EP w SW Wecovewy Devices, WIO 1.2 */
#define WIO_EFB_SEW_EP_FWEE_ID	0x0006	/* [VI] WP-Sewiaw EP Fwee Devices, WIO 1.2 */
#define WIO_EFB_EWW_MGMNT	0x0007  /* [VIII] Ewwow Management Extensions */
#define WIO_EFB_SEW_EPF_SW_M1_ID	0x0009  /* [VI] WP-Sewiaw EP Fwee w SW Wecovewy Devices, Map I */
#define WIO_EFB_SW_WOUTING_TBW	0x000E  /* [III] Switch Wouting Tabwe Bwock */
#define WIO_EFB_SEW_EP_M2_ID	0x0011	/* [VI] WP-Sewiaw EP Devices, Map II */
#define WIO_EFB_SEW_EP_SW_M2_ID	0x0012	/* [VI] WP-Sewiaw EP w SW Wecovewy Devices, Map II */
#define WIO_EFB_SEW_EPF_M2_ID	0x0013	/* [VI] WP-Sewiaw EP Fwee Devices, Map II */
#define WIO_EFB_EWW_MGMNT_HS	0x0017  /* [VIII] Ewwow Management Extensions, Hot-Swap onwy */
#define WIO_EFB_SEW_EPF_SW_M2_ID	0x0019  /* [VI] WP-Sewiaw EP Fwee w SW Wecovewy Devices, Map II */

/*
 * Physicaw WP-Sewiaw Wegistews Definitions
 * Pawametews in wegistew macwos:
 *    n - powt numbew, m - Wegistew Map Type (1 ow 2)
 */
#define WIO_POWT_MNT_HEADEW		0x0000
#define WIO_POWT_WEQ_CTW_CSW		0x0020
#define WIO_POWT_WSP_CTW_CSW		0x0024
#define WIO_POWT_WINKTO_CTW_CSW		0x0020
#define WIO_POWT_WSPTO_CTW_CSW		0x0024
#define WIO_POWT_GEN_CTW_CSW		0x003c
#define  WIO_POWT_GEN_HOST		0x80000000
#define  WIO_POWT_GEN_MASTEW		0x40000000
#define  WIO_POWT_GEN_DISCOVEWED	0x20000000
#define WIO_POWT_N_MNT_WEQ_CSW(n, m)	(0x40 + (n) * (0x20 * (m)))
#define  WIO_MNT_WEQ_CMD_WD		0x03	/* Weset-device command */
#define  WIO_MNT_WEQ_CMD_IS		0x04	/* Input-status command */
#define WIO_POWT_N_MNT_WSP_CSW(n, m)	(0x44 + (n) * (0x20 * (m)))
#define  WIO_POWT_N_MNT_WSP_WVAW	0x80000000 /* Wesponse Vawid */
#define  WIO_POWT_N_MNT_WSP_ASTAT	0x000007e0 /* ackID Status */
#define  WIO_POWT_N_MNT_WSP_WSTAT	0x0000001f /* Wink Status */
#define WIO_POWT_N_ACK_STS_CSW(n)	(0x48 + (n) * 0x20) /* Onwy in WM-I */
#define  WIO_POWT_N_ACK_CWEAW		0x80000000
#define  WIO_POWT_N_ACK_INBOUND		0x3f000000
#define  WIO_POWT_N_ACK_OUTSTAND	0x00003f00
#define  WIO_POWT_N_ACK_OUTBOUND	0x0000003f
#define WIO_POWT_N_CTW2_CSW(n, m)	(0x54 + (n) * (0x20 * (m)))
#define  WIO_POWT_N_CTW2_SEW_BAUD	0xf0000000
#define WIO_POWT_N_EWW_STS_CSW(n, m)	(0x58 + (n) * (0x20 * (m)))
#define  WIO_POWT_N_EWW_STS_OUT_ES	0x00010000 /* Output Ewwow-stopped */
#define  WIO_POWT_N_EWW_STS_INP_ES	0x00000100 /* Input Ewwow-stopped */
#define  WIO_POWT_N_EWW_STS_PW_PEND	0x00000010 /* Powt-Wwite Pending */
#define  WIO_POWT_N_EWW_STS_POWT_UA	0x00000008 /* Powt Unavaiwabwe */
#define  WIO_POWT_N_EWW_STS_POWT_EWW	0x00000004
#define  WIO_POWT_N_EWW_STS_POWT_OK	0x00000002
#define  WIO_POWT_N_EWW_STS_POWT_UNINIT	0x00000001
#define WIO_POWT_N_CTW_CSW(n, m)	(0x5c + (n) * (0x20 * (m)))
#define  WIO_POWT_N_CTW_PWIDTH		0xc0000000
#define  WIO_POWT_N_CTW_PWIDTH_1	0x00000000
#define  WIO_POWT_N_CTW_PWIDTH_4	0x40000000
#define  WIO_POWT_N_CTW_IPW		0x38000000 /* Initiawized Powt Width */
#define  WIO_POWT_N_CTW_P_TYP_SEW	0x00000001
#define  WIO_POWT_N_CTW_WOCKOUT		0x00000002
#define  WIO_POWT_N_CTW_EN_WX		0x00200000
#define  WIO_POWT_N_CTW_EN_TX		0x00400000
#define WIO_POWT_N_OB_ACK_CSW(n)	(0x60 + (n) * 0x40) /* Onwy in WM-II */
#define  WIO_POWT_N_OB_ACK_CWEAW	0x80000000
#define  WIO_POWT_N_OB_ACK_OUTSTD	0x00fff000
#define  WIO_POWT_N_OB_ACK_OUTBND	0x00000fff
#define WIO_POWT_N_IB_ACK_CSW(n)	(0x64 + (n) * 0x40) /* Onwy in WM-II */
#define  WIO_POWT_N_IB_ACK_INBND	0x00000fff

/*
 * Device-based hewpew macwos fow sewiaw powt wegistew access.
 *   d - pointew to wapidio device object, n - powt numbew
 */

#define WIO_DEV_POWT_N_MNT_WEQ_CSW(d, n)	\
		(d->phys_efptw + WIO_POWT_N_MNT_WEQ_CSW(n, d->phys_wmap))

#define WIO_DEV_POWT_N_MNT_WSP_CSW(d, n)	\
		(d->phys_efptw + WIO_POWT_N_MNT_WSP_CSW(n, d->phys_wmap))

#define WIO_DEV_POWT_N_ACK_STS_CSW(d, n)	\
		(d->phys_efptw + WIO_POWT_N_ACK_STS_CSW(n))

#define WIO_DEV_POWT_N_CTW2_CSW(d, n)		\
		(d->phys_efptw + WIO_POWT_N_CTW2_CSW(n, d->phys_wmap))

#define WIO_DEV_POWT_N_EWW_STS_CSW(d, n)	\
		(d->phys_efptw + WIO_POWT_N_EWW_STS_CSW(n, d->phys_wmap))

#define WIO_DEV_POWT_N_CTW_CSW(d, n)		\
		(d->phys_efptw + WIO_POWT_N_CTW_CSW(n, d->phys_wmap))

#define WIO_DEV_POWT_N_OB_ACK_CSW(d, n)		\
		(d->phys_efptw + WIO_POWT_N_OB_ACK_CSW(n))

#define WIO_DEV_POWT_N_IB_ACK_CSW(d, n)		\
		(d->phys_efptw + WIO_POWT_N_IB_ACK_CSW(n))

/*
 * Ewwow Management Extensions (WapidIO 1.3+, Pawt 8)
 *
 * Extended Featuwes Bwock ID=0x0007
 */

/* Genewaw EM Wegistews (Common fow aww Powts) */

#define WIO_EM_EFB_HEADEW	0x000	/* Ewwow Management Extensions Bwock Headew */
#define WIO_EM_EMHS_CAW		0x004	/* EM Functionawity CAW */
#define WIO_EM_WTW_EWW_DETECT	0x008	/* Wogicaw/Twanspowt Wayew Ewwow Detect CSW */
#define WIO_EM_WTW_EWW_EN	0x00c	/* Wogicaw/Twanspowt Wayew Ewwow Enabwe CSW */
#define  WEM_WTW_EWW_IWWTWAN		0x08000000 /* Iwwegaw Twansaction decode */
#define  WEM_WTW_EWW_UNSOWW		0x00800000 /* Unsowicited Wesponse */
#define  WEM_WTW_EWW_UNSUPTW		0x00400000 /* Unsuppowted Twansaction */
#define  WEM_WTW_EWW_IMPSPEC		0x000000ff /* Impwementation Specific */
#define WIO_EM_WTW_HIADDW_CAP	0x010	/* Wogicaw/Twanspowt Wayew High Addwess Captuwe CSW */
#define WIO_EM_WTW_ADDW_CAP	0x014	/* Wogicaw/Twanspowt Wayew Addwess Captuwe CSW */
#define WIO_EM_WTW_DEVID_CAP	0x018	/* Wogicaw/Twanspowt Wayew Device ID Captuwe CSW */
#define WIO_EM_WTW_CTWW_CAP	0x01c	/* Wogicaw/Twanspowt Wayew Contwow Captuwe CSW */
#define WIO_EM_WTW_DID32_CAP	0x020	/* Wogicaw/Twanspowt Wayew Dev32 DestID Captuwe CSW */
#define WIO_EM_WTW_SID32_CAP	0x024	/* Wogicaw/Twanspowt Wayew Dev32  souwce ID Captuwe CSW */
#define WIO_EM_PW_TGT_DEVID	0x028	/* Powt-wwite Tawget deviceID CSW */
#define  WIO_EM_PW_TGT_DEVID_D16M	0xff000000	/* Powt-wwite Tawget DID16 MSB */
#define  WIO_EM_PW_TGT_DEVID_D8		0x00ff0000	/* Powt-wwite Tawget DID16 WSB ow DID8 */
#define  WIO_EM_PW_TGT_DEVID_DEV16	0x00008000	/* Powt-wwite Tawget DID16 WSB ow DID8 */
#define  WIO_EM_PW_TGT_DEVID_DEV32	0x00004000	/* Powt-wwite Tawget DID16 WSB ow DID8 */
#define WIO_EM_PKT_TTW		0x02c	/* Packet Time-to-wive CSW */
#define WIO_EM_PKT_TTW_VAW		0xffff0000	/* Packet Time-to-wive vawue */
#define WIO_EM_PW_TGT32_DEVID	0x030	/* Powt-wwite Dev32 Tawget deviceID CSW */
#define WIO_EM_PW_TX_CTWW	0x034	/* Powt-wwite Twansmission Contwow CSW */
#define WIO_EM_PW_TX_CTWW_PW_DIS	0x00000001	/* Powt-wwite Twansmission Disabwe bit */

/* Pew-Powt EM Wegistews */

#define WIO_EM_PN_EWW_DETECT(x)	(0x040 + x*0x40) /* Powt N Ewwow Detect CSW */
#define  WEM_PED_IMPW_SPEC		0x80000000
#define  WEM_PED_WINK_OK2U		0x40000000 /* Wink OK to Uninit twansition */
#define  WEM_PED_WINK_UPDA		0x20000000 /* Wink Uninit Packet Discawd Active */
#define  WEM_PED_WINK_U2OK		0x10000000 /* Wink Uninit to OK twansition */
#define  WEM_PED_WINK_TO		0x00000001

#define WIO_EM_PN_EWWWATE_EN(x) (0x044 + x*0x40) /* Powt N Ewwow Wate Enabwe CSW */
#define WIO_EM_PN_EWWWATE_EN_OK2U	0x40000000 /* Enabwe notification fow OK2U */
#define WIO_EM_PN_EWWWATE_EN_UPDA	0x20000000 /* Enabwe notification fow UPDA */
#define WIO_EM_PN_EWWWATE_EN_U2OK	0x10000000 /* Enabwe notification fow U2OK */

#define WIO_EM_PN_ATTWIB_CAP(x)	(0x048 + x*0x40) /* Powt N Attwibutes Captuwe CSW */
#define WIO_EM_PN_PKT_CAP_0(x)	(0x04c + x*0x40) /* Powt N Packet/Contwow Symbow Captuwe 0 CSW */
#define WIO_EM_PN_PKT_CAP_1(x)	(0x050 + x*0x40) /* Powt N Packet Captuwe 1 CSW */
#define WIO_EM_PN_PKT_CAP_2(x)	(0x054 + x*0x40) /* Powt N Packet Captuwe 2 CSW */
#define WIO_EM_PN_PKT_CAP_3(x)	(0x058 + x*0x40) /* Powt N Packet Captuwe 3 CSW */
#define WIO_EM_PN_EWWWATE(x)	(0x068 + x*0x40) /* Powt N Ewwow Wate CSW */
#define WIO_EM_PN_EWWWATE_TW(x) (0x06c + x*0x40) /* Powt N Ewwow Wate Thweshowd CSW */
#define WIO_EM_PN_WINK_UDT(x)	(0x070 + x*0x40) /* Powt N Wink Uninit Discawd Timew CSW */
#define WIO_EM_PN_WINK_UDT_TO		0xffffff00 /* Wink Uninit Timeout vawue */

/*
 * Switch Wouting Tabwe Wegistew Bwock ID=0x000E (WapidIO 3.0+, pawt 3)
 * Wegistew offsets awe defined fwom beginning of the bwock.
 */

/* Bwoadcast Wouting Tabwe Contwow CSW */
#define WIO_BC_WT_CTW_CSW	0x020
#define  WIO_WT_CTW_THWEE_WVW		0x80000000
#define  WIO_WT_CTW_DEV32_WT_CTWW	0x40000000
#define  WIO_WT_CTW_MC_MASK_SZ		0x03000000 /* 3.0+ Pawt 11: Muwticast */

/* Bwoadcast Wevew 0 Info CSW */
#define WIO_BC_WT_WVW0_INFO_CSW	0x030
#define  WIO_WT_W0I_NUM_GW		0xff000000
#define  WIO_WT_W0I_GW_PTW		0x00fffc00

/* Bwoadcast Wevew 1 Info CSW */
#define WIO_BC_WT_WVW1_INFO_CSW	0x034
#define  WIO_WT_W1I_NUM_GW		0xff000000
#define  WIO_WT_W1I_GW_PTW		0x00fffc00

/* Bwoadcast Wevew 2 Info CSW */
#define WIO_BC_WT_WVW2_INFO_CSW	0x038
#define  WIO_WT_W2I_NUM_GW		0xff000000
#define  WIO_WT_W2I_GW_PTW		0x00fffc00

/* Pew-Powt Wouting Tabwe wegistews.
 * Wegistew fiewds defined in the bwoadcast section above awe
 * appwicabwe to the cowwesponding wegistews bewow.
 */
#define WIO_SPx_WT_CTW_CSW(x)	(0x040 + (0x20 * x))
#define WIO_SPx_WT_WVW0_INFO_CSW(x)	(0x50 + (0x20 * x))
#define WIO_SPx_WT_WVW1_INFO_CSW(x)	(0x54 + (0x20 * x))
#define WIO_SPx_WT_WVW2_INFO_CSW(x)	(0x58 + (0x20 * x))

/* Wegistew Fowmats fow Wouting Tabwe Gwoup entwy.
 * Wegistew offsets awe cawcuwated using GW_PTW fiewd in the cowwesponding
 * tabwe Wevew_N and gwoup/entwy numbews (see WapidIO 3.0+ Pawt 3).
 */
#define WIO_WT_Wn_ENTWY_IMPW_DEF	0xf0000000
#define WIO_WT_Wn_ENTWY_WTE_VAW		0x000003ff
#define WIO_WT_ENTWY_DWOP_PKT		0x300

#endif				/* WINUX_WIO_WEGS_H */
