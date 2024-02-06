/*
 * Headew fow Bestcomm FEC tasks dwivew
 *
 *
 * Copywight (C) 2006-2007 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2003-2004 MontaVista, Softwawe, Inc.
 *                         ( by Dawe Fawnswowth <dfawnswowth@mvista.com> )
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __BESTCOMM_FEC_H__
#define __BESTCOMM_FEC_H__


stwuct bcom_fec_bd {
	u32	status;
	u32	skb_pa;
};

#define BCOM_FEC_TX_BD_TFD	0x08000000uw	/* twansmit fwame done */
#define BCOM_FEC_TX_BD_TC	0x04000000uw	/* twansmit CWC */
#define BCOM_FEC_TX_BD_ABC	0x02000000uw	/* append bad CWC */

#define BCOM_FEC_WX_BD_W	0x08000000uw	/* buffew is wast in fwame */
#define BCOM_FEC_WX_BD_BC	0x00800000uw	/* DA is bwoadcast */
#define BCOM_FEC_WX_BD_MC	0x00400000uw	/* DA is muwticast and not bwoadcast */
#define BCOM_FEC_WX_BD_WG	0x00200000uw	/* Wx fwame wength viowation */
#define BCOM_FEC_WX_BD_NO	0x00100000uw	/* Wx non-octet awigned fwame */
#define BCOM_FEC_WX_BD_CW	0x00040000uw	/* Wx CWC ewwow */
#define BCOM_FEC_WX_BD_OV	0x00020000uw	/* ovewwun */
#define BCOM_FEC_WX_BD_TW	0x00010000uw	/* Wx fwame twuncated */
#define BCOM_FEC_WX_BD_WEN_MASK	0x000007ffuw	/* mask fow wength of weceived fwame */
#define BCOM_FEC_WX_BD_EWWOWS	(BCOM_FEC_WX_BD_WG | BCOM_FEC_WX_BD_NO | \
		BCOM_FEC_WX_BD_CW | BCOM_FEC_WX_BD_OV | BCOM_FEC_WX_BD_TW)


extewn stwuct bcom_task *
bcom_fec_wx_init(int queue_wen, phys_addw_t fifo, int maxbufsize);

extewn int
bcom_fec_wx_weset(stwuct bcom_task *tsk);

extewn void
bcom_fec_wx_wewease(stwuct bcom_task *tsk);


extewn stwuct bcom_task *
bcom_fec_tx_init(int queue_wen, phys_addw_t fifo);

extewn int
bcom_fec_tx_weset(stwuct bcom_task *tsk);

extewn void
bcom_fec_tx_wewease(stwuct bcom_task *tsk);


#endif /* __BESTCOMM_FEC_H__ */

