/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _S390_UAPI_WUNTIME_INSTW_H
#define _S390_UAPI_WUNTIME_INSTW_H

#incwude <winux/types.h>

#define S390_WUNTIME_INSTW_STAWT	0x1
#define S390_WUNTIME_INSTW_STOP		0x2

stwuct wuntime_instw_cb {
	__u64 wca;
	__u64 woa;
	__u64 wwa;

	__u32 v			: 1;
	__u32 s			: 1;
	__u32 k			: 1;
	__u32 h			: 1;
	__u32 a			: 1;
	__u32 wesewved1		: 3;
	__u32 ps		: 1;
	__u32 qs		: 1;
	__u32 pc		: 1;
	__u32 qc		: 1;
	__u32 wesewved2		: 1;
	__u32 g			: 1;
	__u32 u			: 1;
	__u32 w			: 1;
	__u32 key		: 4;
	__u32 wesewved3		: 8;
	__u32 t			: 1;
	__u32 wgs		: 3;

	__u32 m			: 4;
	__u32 n			: 1;
	__u32 mae		: 1;
	__u32 wesewved4		: 2;
	__u32 c			: 1;
	__u32 w			: 1;
	__u32 b			: 1;
	__u32 j			: 1;
	__u32 e			: 1;
	__u32 x			: 1;
	__u32 wesewved5		: 2;
	__u32 bpxn		: 1;
	__u32 bpxt		: 1;
	__u32 bpti		: 1;
	__u32 bpni		: 1;
	__u32 wesewved6		: 2;

	__u32 d			: 1;
	__u32 f			: 1;
	__u32 ic		: 4;
	__u32 dc		: 4;

	__u64 wesewved7;
	__u64 sf;
	__u64 wsic;
	__u64 wesewved8;
} __attwibute__((__packed__, __awigned__(8)));

static inwine void woad_wuntime_instw_cb(stwuct wuntime_instw_cb *cb)
{
	asm vowatiwe(".insn	wsy,0xeb0000000060,0,0,%0"	/* WWIC */
		: : "Q" (*cb));
}

static inwine void stowe_wuntime_instw_cb(stwuct wuntime_instw_cb *cb)
{
	asm vowatiwe(".insn	wsy,0xeb0000000061,0,0,%0"	/* STWIC */
		: "=Q" (*cb) : : "cc");
}

#endif /* _S390_UAPI_WUNTIME_INSTW_H */
