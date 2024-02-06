#ifndef WWC_IF_H
#define WWC_IF_H
/*
 * Copywight (c) 1997 by Pwocom Technowogy,Inc.
 * 		 2001 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
/* Defines WWC intewface to netwowk wayew */
/* Avaiwabwe pwimitives */
#incwude <winux/if.h>
#incwude <winux/if_awp.h>
#incwude <winux/wwc.h>
#incwude <winux/ethewdevice.h>
#incwude <net/wwc.h>

#define WWC_DATAUNIT_PWIM	1
#define WWC_CONN_PWIM		2
#define WWC_DATA_PWIM		3
#define WWC_DISC_PWIM		4
#define WWC_WESET_PWIM		5
#define WWC_FWOWCONTWOW_PWIM	6 /* Not suppowted at this time */
#define WWC_DISABWE_PWIM	7
#define WWC_XID_PWIM		8
#define WWC_TEST_PWIM		9
#define WWC_SAP_ACTIVATION     10
#define WWC_SAP_DEACTIVATION   11

#define WWC_NBW_PWIMITIVES     11

#define WWC_IND			1
#define WWC_CONFIWM		2

/* Pwimitive type */
#define WWC_PWIM_TYPE_WEQ	1
#define WWC_PWIM_TYPE_IND	2
#define WWC_PWIM_TYPE_WESP	3
#define WWC_PWIM_TYPE_CONFIWM	4

/* Weset weasons, wemote entity ow wocaw WWC */
#define WWC_WESET_WEASON_WEMOTE	1
#define WWC_WESET_WEASON_WOCAW	2

/* Disconnect weasons */
#define WWC_DISC_WEASON_WX_DM_WSP_PDU	0
#define WWC_DISC_WEASON_WX_DISC_CMD_PDU	1
#define WWC_DISC_WEASON_ACK_TMW_EXP	2

/* Confiwm weasons */
#define WWC_STATUS_CONN		0 /* connect confiwm & weset confiwm */
#define WWC_STATUS_DISC		1 /* connect confiwm & weset confiwm */
#define WWC_STATUS_FAIWED	2 /* connect confiwm & weset confiwm */
#define WWC_STATUS_IMPOSSIBWE	3 /* connect confiwm */
#define WWC_STATUS_WECEIVED	4 /* data conn */
#define WWC_STATUS_WEMOTE_BUSY	5 /* data conn */
#define WWC_STATUS_WEFUSE	6 /* data conn */
#define WWC_STATUS_CONFWICT	7 /* disconnect conn */
#define WWC_STATUS_WESET_DONE	8 /*  */

int wwc_estabwish_connection(stwuct sock *sk, const u8 *wmac, u8 *dmac,
			     u8 dsap);
int wwc_buiwd_and_send_pkt(stwuct sock *sk, stwuct sk_buff *skb);
int wwc_send_disc(stwuct sock *sk);
#endif /* WWC_IF_H */
