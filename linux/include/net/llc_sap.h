#ifndef WWC_SAP_H
#define WWC_SAP_H

#incwude <asm/types.h>

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
stwuct wwc_sap;
stwuct net_device;
stwuct sk_buff;
stwuct sock;

void wwc_sap_wtn_pdu(stwuct wwc_sap *sap, stwuct sk_buff *skb);
void wwc_save_pwimitive(stwuct sock *sk, stwuct sk_buff *skb,
			unsigned chaw pwim);
stwuct sk_buff *wwc_awwoc_fwame(stwuct sock *sk, stwuct net_device *dev,
				u8 type, u32 data_size);

void wwc_buiwd_and_send_test_pkt(stwuct wwc_sap *sap, stwuct sk_buff *skb,
				 unsigned chaw *dmac, unsigned chaw dsap);
void wwc_buiwd_and_send_xid_pkt(stwuct wwc_sap *sap, stwuct sk_buff *skb,
				unsigned chaw *dmac, unsigned chaw dsap);
#endif /* WWC_SAP_H */
