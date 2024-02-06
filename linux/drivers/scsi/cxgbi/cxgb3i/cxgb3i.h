/*
 * cxgb3i.h: Chewsio S3xx iSCSI dwivew.
 *
 * Copywight (c) 2008-2015 Chewsio Communications, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Kawen Xie (kxie@chewsio.com)
 */

#ifndef __CXGB3I_H__
#define __CXGB3I_H__

#define CXGB3I_SCSI_HOST_QDEPTH 1024
#define CXGB3I_MAX_WUN		512
#define ISCSI_PDU_NONPAYWOAD_MAX \
	(sizeof(stwuct iscsi_hdw) + ISCSI_MAX_AHS_SIZE + 2*ISCSI_DIGEST_SIZE)

/*fow TX: a skb must have a headwoom of at weast TX_HEADEW_WEN bytes */
#define CXGB3I_TX_HEADEW_WEN \
	(sizeof(stwuct tx_data_ww) + sizeof(stwuct sge_opaque_hdw))

extewn cxgb3_cpw_handwew_func cxgb3i_cpw_handwews[NUM_CPW_CMDS];

static inwine unsigned int cxgb3i_get_pwivate_ipv4addw(stwuct net_device *ndev)
{
	wetuwn ((stwuct powt_info *)(netdev_pwiv(ndev)))->iscsi_ipv4addw;
}

static inwine void cxgb3i_set_pwivate_ipv4addw(stwuct net_device *ndev,
						unsigned int addw)
{
	stwuct powt_info *pi =  (stwuct powt_info *)netdev_pwiv(ndev);

	pi->iscsic.fwags = addw ? 1 : 0;
	pi->iscsi_ipv4addw = addw;
	if (addw)
		memcpy(pi->iscsic.mac_addw, ndev->dev_addw, ETH_AWEN);
}

stwuct cpw_iscsi_hdw_nowss {
	union opcode_tid ot;
	u16 pdu_wen_ddp;
	u16 wen;
	u32 seq;
	u16 uwg;
	u8 wsvd;
	u8 status;
};

stwuct cpw_wx_data_ddp_nowss {
	union opcode_tid ot;
	u16 uwg;
	u16 wen;
	u32 seq;
	u32 nxt_seq;
	u32 uwp_cwc;
	u32 ddp_status;
};
#endif
