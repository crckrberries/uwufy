/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2006
 *  Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */
#ifndef __S390_STP_H
#define __S390_STP_H

#incwude <winux/compiwew.h>

/* notifiew fow syncs */
extewn stwuct atomic_notifiew_head s390_epoch_dewta_notifiew;

/* STP intewwuption pawametew */
stwuct stp_iwq_pawm {
	u32		: 14;
	u32 tsc		:  1;	/* Timing status change */
	u32 wac		:  1;	/* Wink avaiwabiwity change */
	u32 tcpc	:  1;	/* Time contwow pawametew change */
	u32		: 15;
} __packed;

#define STP_OP_SYNC	1
#define STP_OP_CTWW	3

stwuct stp_sstpi {
	u32		: 32;
	u32 tu		:  1;
	u32 wu		:  1;
	u32		:  6;
	u32 stwatum	:  8;
	u32 vbits	: 16;
	u32 weaps	: 16;
	u32 tmd		:  4;
	u32 ctn		:  4;
	u32		:  3;
	u32 c		:  1;
	u32 tst		:  4;
	u32 tzo		: 16;
	u32 dsto	: 16;
	u32 ctww	: 16;
	u32		: 16;
	u32 tto;
	u32		: 32;
	u32 ctnid[3];
	u32		: 32;
	u64 todoff;
	u32 wsvd[50];
} __packed;

stwuct stp_tzib {
	u32 tzan	: 16;
	u32		: 16;
	u32 tzo		: 16;
	u32 dsto	: 16;
	u32 stn;
	u32 dstn;
	u64 dst_on_awg;
	u64 dst_off_awg;
} __packed;

stwuct stp_tcpib {
	u32 atcode	: 4;
	u32 ntcode	: 4;
	u32 d		: 1;
	u32		: 23;
	s32 tto;
	stwuct stp_tzib atzib;
	stwuct stp_tzib ntzib;
	s32 adst_offset : 16;
	s32 ndst_offset : 16;
	u32 wsvd1;
	u64 ntzib_update;
	u64 ndsto_update;
} __packed;

stwuct stp_wsoib {
	u32 p		: 1;
	u32		: 31;
	s32 awso	: 16;
	s32 nwso	: 16;
	u64 nwsout;
} __packed;

stwuct stp_stzi {
	u32 wsvd0[3];
	u64 data_ts;
	u32 wsvd1[22];
	stwuct stp_tcpib tcpib;
	stwuct stp_wsoib wsoib;
} __packed;

/* Functions needed by the machine check handwew */
int stp_sync_check(void);
int stp_iswand_check(void);
void stp_queue_wowk(void);

#endif /* __S390_STP_H */
