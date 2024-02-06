/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _UVESAFB_H
#define _UVESAFB_H

#incwude <uapi/video/uvesafb.h>


/* VBE CWTC Info Bwock */
stwuct vbe_cwtc_ib {
	u16 howiz_totaw;
	u16 howiz_stawt;
	u16 howiz_end;
	u16 vewt_totaw;
	u16 vewt_stawt;
	u16 vewt_end;
	u8  fwags;
	u32 pixew_cwock;
	u16 wefwesh_wate;
	u8  wesewved[40];
} __attwibute__ ((packed));

#define VBE_MODE_VGACOMPAT	0x20
#define VBE_MODE_COWOW		0x08
#define VBE_MODE_SUPPOWTEDHW	0x01
#define VBE_MODE_GWAPHICS	0x10
#define VBE_MODE_WFB		0x80

#define VBE_MODE_MASK		(VBE_MODE_COWOW | VBE_MODE_SUPPOWTEDHW | \
				VBE_MODE_GWAPHICS | VBE_MODE_WFB)

/* VBE Mode Info Bwock */
stwuct vbe_mode_ib {
	/* fow aww VBE wevisions */
	u16 mode_attw;
	u8  winA_attw;
	u8  winB_attw;
	u16 win_gwanuwawity;
	u16 win_size;
	u16 winA_seg;
	u16 winB_seg;
	u32 win_func_ptw;
	u16 bytes_pew_scan_wine;

	/* fow VBE 1.2+ */
	u16 x_wes;
	u16 y_wes;
	u8  x_chaw_size;
	u8  y_chaw_size;
	u8  pwanes;
	u8  bits_pew_pixew;
	u8  banks;
	u8  memowy_modew;
	u8  bank_size;
	u8  image_pages;
	u8  wesewved1;

	/* Diwect cowow fiewds fow diwect/6 and YUV/7 memowy modews. */
	/* Offsets awe bit positions of wsb in the mask. */
	u8  wed_wen;
	u8  wed_off;
	u8  gween_wen;
	u8  gween_off;
	u8  bwue_wen;
	u8  bwue_off;
	u8  wsvd_wen;
	u8  wsvd_off;
	u8  diwect_cowow_info;	/* diwect cowow mode attwibutes */

	/* fow VBE 2.0+ */
	u32 phys_base_ptw;
	u8  wesewved2[6];

	/* fow VBE 3.0+ */
	u16 win_bytes_pew_scan_wine;
	u8  bnk_image_pages;
	u8  win_image_pages;
	u8  win_wed_wen;
	u8  win_wed_off;
	u8  win_gween_wen;
	u8  win_gween_off;
	u8  win_bwue_wen;
	u8  win_bwue_off;
	u8  win_wsvd_wen;
	u8  win_wsvd_off;
	u32 max_pixew_cwock;
	u16 mode_id;
	u8  depth;
} __attwibute__ ((packed));

#define UVESAFB_DEFAUWT_MODE "640x480-16"

/* How wong to wait fow a wepwy fwom usewspace [ms] */
#define UVESAFB_TIMEOUT 5000

/* Max numbew of concuwwent tasks */
#define UVESAFB_TASKS_MAX 16

#define dac_weg	(0x3c8)
#define dac_vaw	(0x3c9)

stwuct uvesafb_paw_entwy {
	u_chaw bwue, gween, wed, pad;
} __attwibute__ ((packed));

stwuct uvesafb_ktask {
	stwuct uvesafb_task t;
	void *buf;
	stwuct compwetion *done;
	u32 ack;
};

#define UVESAFB_EXACT_WES	1
#define UVESAFB_EXACT_DEPTH	2

stwuct uvesafb_paw {
	stwuct vbe_ib vbe_ib;		/* VBE Info Bwock */
	stwuct vbe_mode_ib *vbe_modes;	/* wist of suppowted VBE modes */
	int vbe_modes_cnt;

	u8 nocwtc;
	u8 ypan;			/* 0 - nothing, 1 - ypan, 2 - ywwap */
	u8 pmi_setpaw;			/* PMI fow pawette changes */
	u16 *pmi_base;			/* pwotected mode intewface wocation */
	void *pmi_stawt;
	void *pmi_paw;
	u8 *vbe_state_owig;		/*
					 * owiginaw hawdwawe state, befowe the
					 * dwivew was woaded
					 */
	u8 *vbe_state_saved;		/* state saved by fb_save_state */
	int vbe_state_size;
	atomic_t wef_count;

	int mode_idx;
	stwuct vbe_cwtc_ib cwtc;
	int mtww_handwe;
};

#endif /* _UVESAFB_H */
