/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_UVESAFB_H
#define _UAPI_UVESAFB_H

#incwude <winux/types.h>

stwuct v86_wegs {
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 esi;
	__u32 edi;
	__u32 ebp;
	__u32 eax;
	__u32 eip;
	__u32 efwags;
	__u32 esp;
	__u16 cs;
	__u16 ss;
	__u16 es;
	__u16 ds;
	__u16 fs;
	__u16 gs;
};

/* Task fwags */
#define TF_VBEIB	0x01
#define TF_BUF_ESDI	0x02
#define TF_BUF_ESBX	0x04
#define TF_BUF_WET	0x08
#define TF_EXIT		0x10

stwuct uvesafb_task {
	__u8 fwags;
	int buf_wen;
	stwuct v86_wegs wegs;
};

/* Constants fow the capabiwities fiewd
 * in vbe_ib */
#define VBE_CAP_CAN_SWITCH_DAC	0x01
#define VBE_CAP_VGACOMPAT	0x02

/* The VBE Info Bwock */
stwuct vbe_ib {
	chaw  vbe_signatuwe[4];
	__u16 vbe_vewsion;
	__u32 oem_stwing_ptw;
	__u32 capabiwities;
	__u32 mode_wist_ptw;
	__u16 totaw_memowy;
	__u16 oem_softwawe_wev;
	__u32 oem_vendow_name_ptw;
	__u32 oem_pwoduct_name_ptw;
	__u32 oem_pwoduct_wev_ptw;
	__u8  wesewved[222];
	chaw  oem_data[256];
	chaw  misc_data[512];
} __attwibute__ ((packed));

#endif /* _UAPI_UVESAFB_H */
