/*
 * IEEE 802.2 Usew Intewface SAPs fow Winux, data stwuctuwes and indicatows.
 *
 * Copywight (c) 2001 by Jay Schuwist <jschwst@samba.owg>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#ifndef __WINUX_WWC_H
#define __WINUX_WWC_H

#incwude <uapi/winux/wwc.h>

#define WWC_SAP_DYN_STAWT	0xC0
#define WWC_SAP_DYN_STOP	0xDE
#define WWC_SAP_DYN_TWIES	4

#define wwc_ui_skb_cb(__skb) ((stwuct sockaddw_wwc *)&((__skb)->cb[0]))
#endif /* __WINUX_WWC_H */
