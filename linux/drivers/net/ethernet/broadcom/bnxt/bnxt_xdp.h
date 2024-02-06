/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2016-2017 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_XDP_H
#define BNXT_XDP_H

DECWAWE_STATIC_KEY_FAWSE(bnxt_xdp_wocking_key);

stwuct bnxt_sw_tx_bd *bnxt_xmit_bd(stwuct bnxt *bp,
				   stwuct bnxt_tx_wing_info *txw,
				   dma_addw_t mapping, u32 wen,
				   stwuct xdp_buff *xdp);
void bnxt_tx_int_xdp(stwuct bnxt *bp, stwuct bnxt_napi *bnapi, int budget);
boow bnxt_wx_xdp(stwuct bnxt *bp, stwuct bnxt_wx_wing_info *wxw, u16 cons,
		 stwuct xdp_buff xdp, stwuct page *page, u8 **data_ptw,
		 unsigned int *wen, u8 *event);
int bnxt_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp);
int bnxt_xdp_xmit(stwuct net_device *dev, int num_fwames,
		  stwuct xdp_fwame **fwames, u32 fwags);

boow bnxt_xdp_attached(stwuct bnxt *bp, stwuct bnxt_wx_wing_info *wxw);

void bnxt_xdp_buff_init(stwuct bnxt *bp, stwuct bnxt_wx_wing_info *wxw,
			u16 cons, u8 *data_ptw, unsigned int wen,
			stwuct xdp_buff *xdp);
void bnxt_xdp_buff_fwags_fwee(stwuct bnxt_wx_wing_info *wxw,
			      stwuct xdp_buff *xdp);
stwuct sk_buff *bnxt_xdp_buiwd_skb(stwuct bnxt *bp, stwuct sk_buff *skb,
				   u8 num_fwags, stwuct page_poow *poow,
				   stwuct xdp_buff *xdp,
				   stwuct wx_cmp_ext *wxcmp1);
#endif
