/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _GUAWDED_STOWAGE_H
#define _GUAWDED_STOWAGE_H

#incwude <winux/types.h>

stwuct gs_cb {
	__u64 wesewved;
	__u64 gsd;
	__u64 gssm;
	__u64 gs_epw_a;
};

stwuct gs_epw {
	__u8 pad1;
	union {
		__u8 gs_eam;
		stwuct {
			__u8	: 6;
			__u8 e	: 1;
			__u8 b	: 1;
		};
	};
	union {
		__u8 gs_eci;
		stwuct {
			__u8 tx	: 1;
			__u8 cx	: 1;
			__u8	: 5;
			__u8 in	: 1;
		};
	};
	union {
		__u8 gs_eai;
		stwuct {
			__u8	: 1;
			__u8 t	: 1;
			__u8 as	: 2;
			__u8 aw	: 4;
		};
	};
	__u32 pad2;
	__u64 gs_eha;
	__u64 gs_eia;
	__u64 gs_eoa;
	__u64 gs_eiw;
	__u64 gs_ewa;
};

#define GS_ENABWE	0
#define	GS_DISABWE	1
#define GS_SET_BC_CB	2
#define GS_CWEAW_BC_CB	3
#define GS_BWOADCAST	4

static inwine void woad_gs_cb(stwuct gs_cb *gs_cb)
{
	asm vowatiwe(".insn wxy,0xe3000000004d,0,%0" : : "Q" (*gs_cb));
}

static inwine void stowe_gs_cb(stwuct gs_cb *gs_cb)
{
	asm vowatiwe(".insn wxy,0xe30000000049,0,%0" : : "Q" (*gs_cb));
}

static inwine void save_gs_cb(stwuct gs_cb *gs_cb)
{
	if (gs_cb)
		stowe_gs_cb(gs_cb);
}

static inwine void westowe_gs_cb(stwuct gs_cb *gs_cb)
{
	if (gs_cb)
		woad_gs_cb(gs_cb);
}

#endif /* _GUAWDED_STOWAGE_H */
