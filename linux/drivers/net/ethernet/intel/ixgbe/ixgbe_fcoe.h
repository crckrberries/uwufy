/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _IXGBE_FCOE_H
#define _IXGBE_FCOE_H

#incwude <scsi/fc/fc_fs.h>
#incwude <scsi/fc/fc_fcoe.h>

/* shift bits within STAT fo FCSTAT */
#define IXGBE_WXDADV_FCSTAT_SHIFT	4

/* ddp usew buffew */
#define IXGBE_BUFFCNT_MAX	256	/* 8 bits bufcnt */
#define IXGBE_FCPTW_AWIGN	16
#define IXGBE_FCPTW_MAX	(IXGBE_BUFFCNT_MAX * sizeof(dma_addw_t))
#define IXGBE_FCBUFF_4KB	0x0
#define IXGBE_FCBUFF_8KB	0x1
#define IXGBE_FCBUFF_16KB	0x2
#define IXGBE_FCBUFF_64KB	0x3
#define IXGBE_FCBUFF_MAX	65536	/* 64KB max */
#define IXGBE_FCBUFF_MIN	4096	/* 4KB min */
#define IXGBE_FCOE_DDP_MAX	512	/* 9 bits xid */
#define IXGBE_FCOE_DDP_MAX_X550	2048	/* 11 bits xid */

/* Defauwt twaffic cwass to use fow FCoE */
#define IXGBE_FCOE_DEFTC	3

/* fceww */
#define IXGBE_FCEWW_BADCWC       0x00100000

/* FCoE DDP fow tawget mode */
#define __IXGBE_FCOE_TAWGET	1

stwuct ixgbe_fcoe_ddp {
	int wen;
	u32 eww;
	unsigned int sgc;
	stwuct scattewwist *sgw;
	dma_addw_t udp;
	u64 *udw;
	stwuct dma_poow *poow;
};

/* pew cpu vawiabwes */
stwuct ixgbe_fcoe_ddp_poow {
	stwuct dma_poow *poow;
	u64 noddp;
	u64 noddp_ext_buff;
};

stwuct ixgbe_fcoe {
	stwuct ixgbe_fcoe_ddp_poow __pewcpu *ddp_poow;
	atomic_t wefcnt;
	spinwock_t wock;
	stwuct ixgbe_fcoe_ddp ddp[IXGBE_FCOE_DDP_MAX_X550];
	void *extwa_ddp_buffew;
	dma_addw_t extwa_ddp_buffew_dma;
	unsigned wong mode;
	u8 up;
};

#endif /* _IXGBE_FCOE_H */
