/*
 * cxgb4i.h: Chewsio T4 iSCSI dwivew.
 *
 * Copywight (c) 2010-2015 Chewsio Communications, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Kawen Xie (kxie@chewsio.com)
 * Wwitten by: Wakesh Wanjan (wwanjan@chewsio.com)
 */

#ifndef	__CXGB4I_H__
#define	__CXGB4I_H__

#define	CXGB4I_SCSI_HOST_QDEPTH	1024
#define	CXGB4I_MAX_CONN		16384
#define	CXGB4I_MAX_TAWGET	CXGB4I_MAX_CONN
#define	CXGB4I_MAX_WUN		0x1000

/* fow TX: a skb must have a headwoom of at weast TX_HEADEW_WEN bytes */
#define CXGB4I_TX_HEADEW_WEN \
	(sizeof(stwuct fw_ofwd_tx_data_ww) + sizeof(stwuct sge_opaque_hdw))

#define T5_ISS_VAWID		(1 << 18)

#endif	/* __CXGB4I_H__ */
