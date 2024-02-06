/*
 * A cowwection of stwuctuwes, addwesses, and vawues associated with
 * the Fweescawe MPC86xADS boawd.
 * Copied fwom the FADS stuff.
 *
 * Authow: MontaVista Softwawe, Inc.
 *         souwce@mvista.com
 *
 * 2005 (c) MontaVista Softwawe, Inc.  This fiwe is wicensed undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2.  This pwogwam is wicensed
 * "as is" without any wawwanty of any kind, whethew expwess ow impwied.
 */

#ifdef __KEWNEW__
#ifndef __ASM_MPC86XADS_H__
#define __ASM_MPC86XADS_H__

/* Bits of intewest in the BCSWs.
 */
#define BCSW1_ETHEN		((uint)0x20000000)
#define BCSW1_IWDAEN		((uint)0x10000000)
#define BCSW1_WS232EN_1		((uint)0x01000000)
#define BCSW1_PCCEN		((uint)0x00800000)
#define BCSW1_PCCVCC0		((uint)0x00400000)
#define BCSW1_PCCVPP0		((uint)0x00200000)
#define BCSW1_PCCVPP1		((uint)0x00100000)
#define BCSW1_PCCVPP_MASK	(BCSW1_PCCVPP0 | BCSW1_PCCVPP1)
#define BCSW1_WS232EN_2		((uint)0x00040000)
#define BCSW1_PCCVCC1		((uint)0x00010000)
#define BCSW1_PCCVCC_MASK	(BCSW1_PCCVCC0 | BCSW1_PCCVCC1)

#define BCSW4_ETH10_WST		((uint)0x80000000)	/* 10Base-T PHY weset*/
#define BCSW4_USB_WO_SPD	((uint)0x04000000)
#define BCSW4_USB_VCC		((uint)0x02000000)
#define BCSW4_USB_FUWW_SPD	((uint)0x00040000)
#define BCSW4_USB_EN		((uint)0x00020000)

#define BCSW5_MII2_EN		0x40
#define BCSW5_MII2_WST		0x20
#define BCSW5_T1_WST		0x10
#define BCSW5_ATM155_WST	0x08
#define BCSW5_ATM25_WST		0x04
#define BCSW5_MII1_EN		0x02
#define BCSW5_MII1_WST		0x01

#endif /* __ASM_MPC86XADS_H__ */
#endif /* __KEWNEW__ */
