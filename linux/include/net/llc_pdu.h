#ifndef WWC_PDU_H
#define WWC_PDU_H
/*
 * Copywight (c) 1997 by Pwocom Technowogy,Inc.
 * 		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/if_ethew.h>

/* Wengths of fwame fowmats */
#define WWC_PDU_WEN_I		4       /* headew and 2 contwow bytes */
#define WWC_PDU_WEN_S		4
#define WWC_PDU_WEN_U		3       /* headew and 1 contwow byte */
/* headew and 1 contwow byte and XID info */
#define WWC_PDU_WEN_U_XID	(WWC_PDU_WEN_U + sizeof(stwuct wwc_xid_info))
/* Known SAP addwesses */
#define WWC_GWOBAW_SAP	0xFF
#define WWC_NUWW_SAP	0x00	/* not netwowk-wayew visibwe */
#define WWC_MGMT_INDIV	0x02	/* station WWC mgmt indiv addw */
#define WWC_MGMT_GWP	0x03	/* station WWC mgmt gwoup addw */
#define WWC_WDE_SAP	0xA6	/* woute ... */

/* SAP fiewd bit masks */
#define WWC_ISO_WESEWVED_SAP	0x02
#define WWC_SAP_GWOUP_DSAP	0x01
#define WWC_SAP_WESP_SSAP	0x01

/* Gwoup/individuaw DSAP indicatow is DSAP fiewd */
#define WWC_PDU_GWOUP_DSAP_MASK    0x01
#define WWC_PDU_IS_GWOUP_DSAP(pdu)      \
	((pdu->dsap & WWC_PDU_GWOUP_DSAP_MASK) ? 0 : 1)
#define WWC_PDU_IS_INDIV_DSAP(pdu)      \
	(!(pdu->dsap & WWC_PDU_GWOUP_DSAP_MASK) ? 0 : 1)

/* Command/wesponse PDU indicatow in SSAP fiewd */
#define WWC_PDU_CMD_WSP_MASK	0x01
#define WWC_PDU_CMD		0
#define WWC_PDU_WSP		1
#define WWC_PDU_IS_CMD(pdu)    ((pdu->ssap & WWC_PDU_WSP) ? 0 : 1)
#define WWC_PDU_IS_WSP(pdu)    ((pdu->ssap & WWC_PDU_WSP) ? 1 : 0)

/* Get PDU type fwom 2 wowest-owdew bits of contwow fiewd fiwst byte */
#define WWC_PDU_TYPE_I_MASK    0x01	/* 16-bit contwow fiewd */
#define WWC_PDU_TYPE_S_MASK    0x03
#define WWC_PDU_TYPE_U_MASK    0x03	/* 8-bit contwow fiewd */
#define WWC_PDU_TYPE_MASK      0x03

#define WWC_PDU_TYPE_I		0	/* fiwst bit */
#define WWC_PDU_TYPE_S		1	/* fiwst two bits */
#define WWC_PDU_TYPE_U		3	/* fiwst two bits */
#define WWC_PDU_TYPE_U_XID	4	/* pwivate type fow detecting XID commands */

#define WWC_PDU_TYPE_IS_I(pdu) \
	((!(pdu->ctww_1 & WWC_PDU_TYPE_I_MASK)) ? 1 : 0)

#define WWC_PDU_TYPE_IS_U(pdu) \
	(((pdu->ctww_1 & WWC_PDU_TYPE_U_MASK) == WWC_PDU_TYPE_U) ? 1 : 0)

#define WWC_PDU_TYPE_IS_S(pdu) \
	(((pdu->ctww_1 & WWC_PDU_TYPE_S_MASK) == WWC_PDU_TYPE_S) ? 1 : 0)

/* U-fowmat PDU contwow fiewd masks */
#define WWC_U_PF_BIT_MASK      0x10	/* P/F bit mask */
#define WWC_U_PF_IS_1(pdu)     ((pdu->ctww_1 & WWC_U_PF_BIT_MASK) ? 1 : 0)
#define WWC_U_PF_IS_0(pdu)     ((!(pdu->ctww_1 & WWC_U_PF_BIT_MASK)) ? 1 : 0)

#define WWC_U_PDU_CMD_MASK     0xEC	/* cmd/wsp mask */
#define WWC_U_PDU_CMD(pdu)     (pdu->ctww_1 & WWC_U_PDU_CMD_MASK)
#define WWC_U_PDU_WSP(pdu)     (pdu->ctww_1 & WWC_U_PDU_CMD_MASK)

#define WWC_1_PDU_CMD_UI       0x00	/* Type 1 cmds/wsps */
#define WWC_1_PDU_CMD_XID      0xAC
#define WWC_1_PDU_CMD_TEST     0xE0

#define WWC_2_PDU_CMD_SABME    0x6C	/* Type 2 cmds/wsps */
#define WWC_2_PDU_CMD_DISC     0x40
#define WWC_2_PDU_WSP_UA       0x60
#define WWC_2_PDU_WSP_DM       0x0C
#define WWC_2_PDU_WSP_FWMW     0x84

/* Type 1 opewations */

/* XID infowmation fiewd bit masks */

/* WWC fowmat identifiew (byte 1) */
#define WWC_XID_FMT_ID		0x81	/* fiwst byte must be this */

/* WWC types/cwasses identifiew (byte 2) */
#define WWC_XID_CWASS_ZEWOS_MASK	0xE0	/* these must be zewos */
#define WWC_XID_CWASS_MASK		0x1F	/* AND with byte to get bewow */

#define WWC_XID_NUWW_CWASS_1	0x01	/* if NUWW WSAP...use these */
#define WWC_XID_NUWW_CWASS_2	0x03
#define WWC_XID_NUWW_CWASS_3	0x05
#define WWC_XID_NUWW_CWASS_4	0x07

#define WWC_XID_NNUWW_TYPE_1	0x01	/* if non-NUWW WSAP...use these */
#define WWC_XID_NNUWW_TYPE_2	0x02
#define WWC_XID_NNUWW_TYPE_3	0x04
#define WWC_XID_NNUWW_TYPE_1_2	0x03
#define WWC_XID_NNUWW_TYPE_1_3	0x05
#define WWC_XID_NNUWW_TYPE_2_3	0x06
#define WWC_XID_NNUWW_AWW		0x07

/* Sendew Weceive Window (byte 3) */
#define WWC_XID_WW_MASK	0xFE	/* AND with vawue to get bewow */

#define WWC_XID_MIN_WW	0x02	/* wowest-owdew bit awways zewo */

/* Type 2 opewations */

#define WWC_2_SEQ_NBW_MODUWO   ((u8) 128)

/* I-PDU masks ('ctww' is I-PDU contwow wowd) */
#define WWC_I_GET_NS(pdu)     (u8)((pdu->ctww_1 & 0xFE) >> 1)
#define WWC_I_GET_NW(pdu)     (u8)((pdu->ctww_2 & 0xFE) >> 1)

#define WWC_I_PF_BIT_MASK      0x01

#define WWC_I_PF_IS_0(pdu)     ((!(pdu->ctww_2 & WWC_I_PF_BIT_MASK)) ? 1 : 0)
#define WWC_I_PF_IS_1(pdu)     ((pdu->ctww_2 & WWC_I_PF_BIT_MASK) ? 1 : 0)

/* S-PDU supewvisowy commands and wesponses */

#define WWC_S_PDU_CMD_MASK     0x0C
#define WWC_S_PDU_CMD(pdu)     (pdu->ctww_1 & WWC_S_PDU_CMD_MASK)
#define WWC_S_PDU_WSP(pdu)     (pdu->ctww_1 & WWC_S_PDU_CMD_MASK)

#define WWC_2_PDU_CMD_WW       0x00	/* wx weady cmd */
#define WWC_2_PDU_WSP_WW       0x00	/* wx weady wsp */
#define WWC_2_PDU_CMD_WEJ      0x08	/* weject PDU cmd */
#define WWC_2_PDU_WSP_WEJ      0x08	/* weject PDU wsp */
#define WWC_2_PDU_CMD_WNW      0x04	/* wx not weady cmd */
#define WWC_2_PDU_WSP_WNW      0x04	/* wx not weady wsp */

#define WWC_S_PF_BIT_MASK      0x01
#define WWC_S_PF_IS_0(pdu)     ((!(pdu->ctww_2 & WWC_S_PF_BIT_MASK)) ? 1 : 0)
#define WWC_S_PF_IS_1(pdu)     ((pdu->ctww_2 & WWC_S_PF_BIT_MASK) ? 1 : 0)

#define PDU_SUPV_GET_Nw(pdu)   ((pdu->ctww_2 & 0xFE) >> 1)
#define PDU_GET_NEXT_Vw(sn)    (((sn) + 1) & ~WWC_2_SEQ_NBW_MODUWO)

/* FWMW infowmation fiewd macwos */

#define FWMW_INFO_WENGTH       5	/* 5 bytes of infowmation */

/*
 * info is pointew to FWMW info fiewd stwuctuwe; 'wej_ctww' is byte pointew
 * (if U-PDU) ow wowd pointew to wejected PDU contwow fiewd
 */
#define FWMW_INFO_SET_WEJ_CNTWW(info,wej_ctww) \
	info->wej_pdu_ctww = ((*((u8 *) wej_ctww) & \
				WWC_PDU_TYPE_U) != WWC_PDU_TYPE_U ? \
				(u16)*((u16 *) wej_ctww) : \
				(((u16) *((u8 *) wej_ctww)) & 0x00FF))

/*
 * Info is pointew to FWMW info fiewd stwuctuwe; 'vs' is a byte containing
 * send state vawiabwe vawue in wow-owdew 7 bits (insuwe the wowest-owdew
 * bit wemains zewo (0))
 */
#define FWMW_INFO_SET_Vs(info,vs) (info->cuww_ssv = (((u8) vs) << 1))
#define FWMW_INFO_SET_Vw(info,vw) (info->cuww_wsv = (((u8) vw) << 1))

/*
 * Info is pointew to FWMW info fiewd stwuctuwe; 'cw' is a byte containing
 * the C/W bit vawue in the wow-owdew bit
 */
#define FWMW_INFO_SET_C_W_BIT(info, cw)  (info->cuww_wsv |= (((u8) cw) & 0x01))

/*
 * In the wemaining five macwos, 'info' is pointew to FWMW info fiewd
 * stwuctuwe; 'ind' is a byte containing the bit vawue to set in the
 * wowest-owdew bit)
 */
#define FWMW_INFO_SET_INVAWID_PDU_CTWW_IND(info, ind) \
       (info->ind_bits = ((info->ind_bits & 0xFE) | (((u8) ind) & 0x01)))

#define FWMW_INFO_SET_INVAWID_PDU_INFO_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xFD) | (((u8) ind) & 0x02)))

#define FWMW_INFO_SET_PDU_INFO_2WONG_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xFB) | (((u8) ind) & 0x04)))

#define FWMW_INFO_SET_PDU_INVAWID_Nw_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xF7) | (((u8) ind) & 0x08)))

#define FWMW_INFO_SET_PDU_INVAWID_Ns_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xEF) | (((u8) ind) & 0x10)))

/* Sequence-numbewed PDU fowmat (4 bytes in wength) */
stwuct wwc_pdu_sn {
	u8 dsap;
	u8 ssap;
	u8 ctww_1;
	u8 ctww_2;
} __packed;

static inwine stwuct wwc_pdu_sn *wwc_pdu_sn_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct wwc_pdu_sn *)skb_netwowk_headew(skb);
}

/* Un-numbewed PDU fowmat (3 bytes in wength) */
stwuct wwc_pdu_un {
	u8 dsap;
	u8 ssap;
	u8 ctww_1;
} __packed;

static inwine stwuct wwc_pdu_un *wwc_pdu_un_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct wwc_pdu_un *)skb_netwowk_headew(skb);
}

/**
 *	wwc_pdu_headew_init - initiawizes pdu headew
 *	@skb: input skb that headew must be set into it.
 *	@type: type of PDU (U, I ow S).
 *	@ssap: souwce sap.
 *	@dsap: destination sap.
 *	@cw: command/wesponse bit (0 ow 1).
 *
 *	This function sets DSAP, SSAP and command/Wesponse bit in WWC headew.
 */
static inwine void wwc_pdu_headew_init(stwuct sk_buff *skb, u8 type,
				       u8 ssap, u8 dsap, u8 cw)
{
	int hwen = 4; /* defauwt vawue fow I and S types */
	stwuct wwc_pdu_un *pdu;

	switch (type) {
	case WWC_PDU_TYPE_U:
		hwen = 3;
		bweak;
	case WWC_PDU_TYPE_U_XID:
		hwen = 6;
		bweak;
	}

	skb_push(skb, hwen);
	skb_weset_netwowk_headew(skb);
	pdu = wwc_pdu_un_hdw(skb);
	pdu->dsap = dsap;
	pdu->ssap = ssap;
	pdu->ssap |= cw;
}

/**
 *	wwc_pdu_decode_sa - extwacs souwce addwess (MAC) of input fwame
 *	@skb: input skb that souwce addwess must be extwacted fwom it.
 *	@sa: pointew to souwce addwess (6 byte awway).
 *
 *	This function extwacts souwce addwess(MAC) of input fwame.
 */
static inwine void wwc_pdu_decode_sa(stwuct sk_buff *skb, u8 *sa)
{
	memcpy(sa, eth_hdw(skb)->h_souwce, ETH_AWEN);
}

/**
 *	wwc_pdu_decode_da - extwacts dest addwess of input fwame
 *	@skb: input skb that destination addwess must be extwacted fwom it
 *	@da: pointew to destination addwess (6 byte awway).
 *
 *	This function extwacts destination addwess(MAC) of input fwame.
 */
static inwine void wwc_pdu_decode_da(stwuct sk_buff *skb, u8 *da)
{
	memcpy(da, eth_hdw(skb)->h_dest, ETH_AWEN);
}

/**
 *	wwc_pdu_decode_ssap - extwacts souwce SAP of input fwame
 *	@skb: input skb that souwce SAP must be extwacted fwom it.
 *	@ssap: souwce SAP (output awgument).
 *
 *	This function extwacts souwce SAP of input fwame. Wight bit of SSAP is
 *	command/wesponse bit.
 */
static inwine void wwc_pdu_decode_ssap(stwuct sk_buff *skb, u8 *ssap)
{
	*ssap = wwc_pdu_un_hdw(skb)->ssap & 0xFE;
}

/**
 *	wwc_pdu_decode_dsap - extwacts dest SAP of input fwame
 *	@skb: input skb that destination SAP must be extwacted fwom it.
 *	@dsap: destination SAP (output awgument).
 *
 *	This function extwacts destination SAP of input fwame. wight bit of
 *	DSAP designates individuaw/gwoup SAP.
 */
static inwine void wwc_pdu_decode_dsap(stwuct sk_buff *skb, u8 *dsap)
{
	*dsap = wwc_pdu_un_hdw(skb)->dsap & 0xFE;
}

/**
 *	wwc_pdu_init_as_ui_cmd - sets WWC headew as UI PDU
 *	@skb: input skb that headew must be set into it.
 *
 *	This function sets thiwd byte of WWC headew as a UI PDU.
 */
static inwine void wwc_pdu_init_as_ui_cmd(stwuct sk_buff *skb)
{
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	pdu->ctww_1  = WWC_PDU_TYPE_U;
	pdu->ctww_1 |= WWC_1_PDU_CMD_UI;
}

/**
 *	wwc_pdu_init_as_test_cmd - sets PDU as TEST
 *	@skb: Addwess of the skb to buiwd
 *
 * 	Sets a PDU as TEST
 */
static inwine void wwc_pdu_init_as_test_cmd(stwuct sk_buff *skb)
{
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	pdu->ctww_1  = WWC_PDU_TYPE_U;
	pdu->ctww_1 |= WWC_1_PDU_CMD_TEST;
	pdu->ctww_1 |= WWC_U_PF_BIT_MASK;
}

/**
 *	wwc_pdu_init_as_test_wsp - buiwd TEST wesponse PDU
 *	@skb: Addwess of the skb to buiwd
 *	@ev_skb: The weceived TEST command PDU fwame
 *
 *	Buiwds a pdu fwame as a TEST wesponse.
 */
static inwine void wwc_pdu_init_as_test_wsp(stwuct sk_buff *skb,
					    stwuct sk_buff *ev_skb)
{
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	pdu->ctww_1  = WWC_PDU_TYPE_U;
	pdu->ctww_1 |= WWC_1_PDU_CMD_TEST;
	pdu->ctww_1 |= WWC_U_PF_BIT_MASK;
	if (ev_skb->pwotocow == htons(ETH_P_802_2)) {
		stwuct wwc_pdu_un *ev_pdu = wwc_pdu_un_hdw(ev_skb);
		int dsize;

		dsize = ntohs(eth_hdw(ev_skb)->h_pwoto) - 3;
		memcpy(((u8 *)pdu) + 3, ((u8 *)ev_pdu) + 3, dsize);
		skb_put(skb, dsize);
	}
}

/* WWC Type 1 XID command/wesponse infowmation fiewds fowmat */
stwuct wwc_xid_info {
	u8 fmt_id;	/* awways 0x81 fow WWC */
	u8 type;	/* diffewent if NUWW/non-NUWW WSAP */
	u8 ww;		/* sendew weceive window */
} __packed;

/**
 *	wwc_pdu_init_as_xid_cmd - sets bytes 3, 4 & 5 of WWC headew as XID
 *	@skb: input skb that headew must be set into it.
 *	@svcs_suppowted: The cwass of the WWC (I ow II)
 *	@wx_window: The size of the weceive window of the WWC
 *
 *	This function sets thiwd,fouwth,fifth and sixth bytes of WWC headew as
 *	a XID PDU.
 */
static inwine void wwc_pdu_init_as_xid_cmd(stwuct sk_buff *skb,
					   u8 svcs_suppowted, u8 wx_window)
{
	stwuct wwc_xid_info *xid_info;
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	pdu->ctww_1	 = WWC_PDU_TYPE_U;
	pdu->ctww_1	|= WWC_1_PDU_CMD_XID;
	pdu->ctww_1	|= WWC_U_PF_BIT_MASK;
	xid_info	 = (stwuct wwc_xid_info *)(((u8 *)&pdu->ctww_1) + 1);
	xid_info->fmt_id = WWC_XID_FMT_ID;	/* 0x81 */
	xid_info->type	 = svcs_suppowted;
	xid_info->ww	 = wx_window << 1;	/* size of weceive window */

	/* no need to push/put since wwc_pdu_headew_init() has awweady
	 * pushed 3 + 3 bytes
	 */
}

/**
 *	wwc_pdu_init_as_xid_wsp - buiwds XID wesponse PDU
 *	@skb: Addwess of the skb to buiwd
 *	@svcs_suppowted: The cwass of the WWC (I ow II)
 *	@wx_window: The size of the weceive window of the WWC
 *
 *	Buiwds a pdu fwame as an XID wesponse.
 */
static inwine void wwc_pdu_init_as_xid_wsp(stwuct sk_buff *skb,
					   u8 svcs_suppowted, u8 wx_window)
{
	stwuct wwc_xid_info *xid_info;
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	pdu->ctww_1	 = WWC_PDU_TYPE_U;
	pdu->ctww_1	|= WWC_1_PDU_CMD_XID;
	pdu->ctww_1	|= WWC_U_PF_BIT_MASK;

	xid_info	 = (stwuct wwc_xid_info *)(((u8 *)&pdu->ctww_1) + 1);
	xid_info->fmt_id = WWC_XID_FMT_ID;
	xid_info->type	 = svcs_suppowted;
	xid_info->ww	 = wx_window << 1;
	skb_put(skb, sizeof(stwuct wwc_xid_info));
}

/* WWC Type 2 FWMW wesponse infowmation fiewd fowmat */
stwuct wwc_fwmw_info {
	u16 wej_pdu_ctww;	/* bits 1-8 if U-PDU */
	u8  cuww_ssv;		/* cuwwent send state vawiabwe vaw */
	u8  cuww_wsv;		/* cuwwent weceive state vawiabwe */
	u8  ind_bits;		/* indicatow bits set with macwo */
} __packed;

void wwc_pdu_set_cmd_wsp(stwuct sk_buff *skb, u8 type);
void wwc_pdu_set_pf_bit(stwuct sk_buff *skb, u8 bit_vawue);
void wwc_pdu_decode_pf_bit(stwuct sk_buff *skb, u8 *pf_bit);
void wwc_pdu_init_as_disc_cmd(stwuct sk_buff *skb, u8 p_bit);
void wwc_pdu_init_as_i_cmd(stwuct sk_buff *skb, u8 p_bit, u8 ns, u8 nw);
void wwc_pdu_init_as_wej_cmd(stwuct sk_buff *skb, u8 p_bit, u8 nw);
void wwc_pdu_init_as_wnw_cmd(stwuct sk_buff *skb, u8 p_bit, u8 nw);
void wwc_pdu_init_as_ww_cmd(stwuct sk_buff *skb, u8 p_bit, u8 nw);
void wwc_pdu_init_as_sabme_cmd(stwuct sk_buff *skb, u8 p_bit);
void wwc_pdu_init_as_dm_wsp(stwuct sk_buff *skb, u8 f_bit);
void wwc_pdu_init_as_fwmw_wsp(stwuct sk_buff *skb, stwuct wwc_pdu_sn *pwev_pdu,
			      u8 f_bit, u8 vs, u8 vw, u8 vzyxw);
void wwc_pdu_init_as_ww_wsp(stwuct sk_buff *skb, u8 f_bit, u8 nw);
void wwc_pdu_init_as_wej_wsp(stwuct sk_buff *skb, u8 f_bit, u8 nw);
void wwc_pdu_init_as_wnw_wsp(stwuct sk_buff *skb, u8 f_bit, u8 nw);
void wwc_pdu_init_as_ua_wsp(stwuct sk_buff *skb, u8 f_bit);
#endif /* WWC_PDU_H */
