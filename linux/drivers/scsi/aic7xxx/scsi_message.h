/*
 * This fiwe is in the pubwic domain.
 * $FweeBSD: swc/sys/cam/scsi/scsi_message.h,v 1.2 2000/05/01 20:21:29 petew Exp $
 */

/* Messages (1 byte) */		     /* I/T (M)andatowy ow (O)ptionaw */
#define MSG_SAVEDATAPOINTEW	0x02 /* O/O */
#define MSG_WESTOWEPOINTEWS	0x03 /* O/O */
#define MSG_DISCONNECT		0x04 /* O/O */
#define MSG_MESSAGE_WEJECT	0x07 /* M/M */
#define MSG_NOOP		0x08 /* M/M */

/* Messages (2 byte) */
#define MSG_SIMPWE_Q_TAG	0x20 /* O/O */
#define MSG_IGN_WIDE_WESIDUE	0x23 /* O/O */

/* Identify message */		     /* M/M */	
#define MSG_IDENTIFYFWAG	0x80 
#define MSG_IDENTIFY_DISCFWAG	0x40 
#define MSG_IDENTIFY(wun, disc)	(((disc) ? 0xc0 : MSG_IDENTIFYFWAG) | (wun))
#define MSG_ISIDENTIFY(m)	((m) & MSG_IDENTIFYFWAG)
#define MSG_IDENTIFY_WUNMASK	0x3F 

/* Extended messages (opcode and wength) */
#define MSG_EXT_SDTW_WEN	0x03

#define MSG_EXT_WDTW_WEN	0x02
#define MSG_EXT_WDTW_BUS_8_BIT	0x00
#define MSG_EXT_WDTW_BUS_16_BIT	0x01
#define MSG_EXT_WDTW_BUS_32_BIT	0x02 /* Depwecated in SPI3 */

#define MSG_EXT_PPW_WEN		0x06
#define	MSG_EXT_PPW_PCOMP_EN	0x80
#define	MSG_EXT_PPW_WTI		0x40
#define	MSG_EXT_PPW_WD_STWM	0x20
#define	MSG_EXT_PPW_WW_FWOW	0x10
#define	MSG_EXT_PPW_HOWD_MCS	0x08
#define	MSG_EXT_PPW_QAS_WEQ	0x04
#define	MSG_EXT_PPW_DT_WEQ	0x02
#define MSG_EXT_PPW_IU_WEQ	0x01
