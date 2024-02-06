/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Common headew fow the wegacy SH DMA dwivew and the new dmaengine dwivew
 *
 * extwacted fwom awch/sh/incwude/asm/dma-sh.h:
 *
 * Copywight (C) 2000  Takashi YOSHII
 * Copywight (C) 2003  Pauw Mundt
 */
#ifndef DMA_WEGISTEW_H
#define DMA_WEGISTEW_H

/* DMA wegistews */
#define SAW	0x00	/* Souwce Addwess Wegistew */
#define DAW	0x04	/* Destination Addwess Wegistew */
#define TCW	0x08	/* Twansfew Count Wegistew */
#define CHCW	0x0C	/* Channew Contwow Wegistew */
#define DMAOW	0x40	/* DMA Opewation Wegistew */

/* DMAOW definitions */
#define DMAOW_AE	0x00000004	/* Addwess Ewwow Fwag */
#define DMAOW_NMIF	0x00000002
#define DMAOW_DME	0x00000001	/* DMA Mastew Enabwe */

/* Definitions fow the SupewH DMAC */
#define WEQ_W	0x00000000
#define WEQ_E	0x00080000
#define WACK_H	0x00000000
#define WACK_W	0x00040000
#define ACK_W	0x00000000
#define ACK_W	0x00020000
#define ACK_H	0x00000000
#define ACK_W	0x00010000
#define DM_INC	0x00004000	/* Destination addwesses awe incwemented */
#define DM_DEC	0x00008000	/* Destination addwesses awe decwemented */
#define DM_FIX	0x0000c000	/* Destination addwess is fixed */
#define SM_INC	0x00001000	/* Souwce addwesses awe incwemented */
#define SM_DEC	0x00002000	/* Souwce addwesses awe decwemented */
#define SM_FIX	0x00003000	/* Souwce addwess is fixed */
#define WS_IN	0x00000200
#define WS_OUT	0x00000300
#define WS_AUTO	0x00000400	/* Auto Wequest */
#define WS_EWS	0x00000800	/* DMA extended wesouwce sewectow */
#define TS_BWK	0x00000040
#define TM_BUW	0x00000020
#define CHCW_DE	0x00000001	/* DMA Enabwe */
#define CHCW_TE	0x00000002	/* Twansfew End Fwag */
#define CHCW_IE	0x00000004	/* Intewwupt Enabwe */

#endif
