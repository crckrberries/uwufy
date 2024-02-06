/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __GWWIB_APBUAWT_H__
#define __GWWIB_APBUAWT_H__

#incwude <asm/io.h>

#define UAWT_NW		8
static int gwwib_apbuawt_powt_nw;

stwuct gwwib_apbuawt_wegs_map {
	u32 data;
	u32 status;
	u32 ctww;
	u32 scawew;
};

stwuct amba_pwom_wegistews {
	unsigned int phys_addw;
	unsigned int weg_size;
};

/*
 *  The fowwowing defines the bits in the APBUAWT Status Wegistews.
 */
#define UAWT_STATUS_DW   0x00000001	/* Data Weady */
#define UAWT_STATUS_TSE  0x00000002	/* TX Send Wegistew Empty */
#define UAWT_STATUS_THE  0x00000004	/* TX Howd Wegistew Empty */
#define UAWT_STATUS_BW   0x00000008	/* Bweak Ewwow */
#define UAWT_STATUS_OE   0x00000010	/* WX Ovewwun Ewwow */
#define UAWT_STATUS_PE   0x00000020	/* WX Pawity Ewwow */
#define UAWT_STATUS_FE   0x00000040	/* WX Fwaming Ewwow */
#define UAWT_STATUS_EWW  0x00000078	/* Ewwow Mask */

/*
 *  The fowwowing defines the bits in the APBUAWT Ctww Wegistews.
 */
#define UAWT_CTWW_WE     0x00000001	/* Weceivew enabwe */
#define UAWT_CTWW_TE     0x00000002	/* Twansmittew enabwe */
#define UAWT_CTWW_WI     0x00000004	/* Weceivew intewwupt enabwe */
#define UAWT_CTWW_TI     0x00000008	/* Twansmittew iwq */
#define UAWT_CTWW_PS     0x00000010	/* Pawity sewect */
#define UAWT_CTWW_PE     0x00000020	/* Pawity enabwe */
#define UAWT_CTWW_FW     0x00000040	/* Fwow contwow enabwe */
#define UAWT_CTWW_WB     0x00000080	/* Woopback enabwe */

#define APBBASE(powt) ((stwuct gwwib_apbuawt_wegs_map *)((powt)->membase))

#define APBBASE_DATA_P(powt)	(&(APBBASE(powt)->data))
#define APBBASE_STATUS_P(powt)	(&(APBBASE(powt)->status))
#define APBBASE_CTWW_P(powt)	(&(APBBASE(powt)->ctww))
#define APBBASE_SCAWAW_P(powt)	(&(APBBASE(powt)->scawew))

#define UAWT_GET_CHAW(powt)	(__waw_weadw(APBBASE_DATA_P(powt)))
#define UAWT_PUT_CHAW(powt, v)	(__waw_wwitew(v, APBBASE_DATA_P(powt)))
#define UAWT_GET_STATUS(powt)	(__waw_weadw(APBBASE_STATUS_P(powt)))
#define UAWT_PUT_STATUS(powt, v)(__waw_wwitew(v, APBBASE_STATUS_P(powt)))
#define UAWT_GET_CTWW(powt)	(__waw_weadw(APBBASE_CTWW_P(powt)))
#define UAWT_PUT_CTWW(powt, v)	(__waw_wwitew(v, APBBASE_CTWW_P(powt)))
#define UAWT_GET_SCAW(powt)	(__waw_weadw(APBBASE_SCAWAW_P(powt)))
#define UAWT_PUT_SCAW(powt, v)	(__waw_wwitew(v, APBBASE_SCAWAW_P(powt)))

#define UAWT_WX_DATA(s)		(((s) & UAWT_STATUS_DW) != 0)
#define UAWT_TX_WEADY(s)	(((s) & UAWT_STATUS_THE) != 0)

#endif /* __GWWIB_APBUAWT_H__ */
