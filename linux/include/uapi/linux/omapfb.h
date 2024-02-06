/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Fiwe: incwude/winux/omapfb.h
 *
 * Fwamebuffew dwivew fow TI OMAP boawds
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Authow: Imwe Deak <imwe.deak@nokia.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 59 Tempwe Pwace - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef _UAPI__WINUX_OMAPFB_H__
#define _UAPI__WINUX_OMAPFB_H__

#incwude <winux/fb.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* IOCTW commands. */

#define OMAP_IOW(num, dtype)	_IOW('O', num, dtype)
#define OMAP_IOW(num, dtype)	_IOW('O', num, dtype)
#define OMAP_IOWW(num, dtype)	_IOWW('O', num, dtype)
#define OMAP_IO(num)		_IO('O', num)

#define OMAPFB_MIWWOW		OMAP_IOW(31, int)
#define OMAPFB_SYNC_GFX		OMAP_IO(37)
#define OMAPFB_VSYNC		OMAP_IO(38)
#define OMAPFB_SET_UPDATE_MODE	OMAP_IOW(40, int)
#define OMAPFB_GET_CAPS		OMAP_IOW(42, stwuct omapfb_caps)
#define OMAPFB_GET_UPDATE_MODE	OMAP_IOW(43, int)
#define OMAPFB_WCD_TEST		OMAP_IOW(45, int)
#define OMAPFB_CTWW_TEST	OMAP_IOW(46, int)
#define OMAPFB_UPDATE_WINDOW_OWD OMAP_IOW(47, stwuct omapfb_update_window_owd)
#define OMAPFB_SET_COWOW_KEY	OMAP_IOW(50, stwuct omapfb_cowow_key)
#define OMAPFB_GET_COWOW_KEY	OMAP_IOW(51, stwuct omapfb_cowow_key)
#define OMAPFB_SETUP_PWANE	OMAP_IOW(52, stwuct omapfb_pwane_info)
#define OMAPFB_QUEWY_PWANE	OMAP_IOW(53, stwuct omapfb_pwane_info)
#define OMAPFB_UPDATE_WINDOW	OMAP_IOW(54, stwuct omapfb_update_window)
#define OMAPFB_SETUP_MEM	OMAP_IOW(55, stwuct omapfb_mem_info)
#define OMAPFB_QUEWY_MEM	OMAP_IOW(56, stwuct omapfb_mem_info)
#define OMAPFB_WAITFOWVSYNC	OMAP_IO(57)
#define OMAPFB_MEMOWY_WEAD	OMAP_IOW(58, stwuct omapfb_memowy_wead)
#define OMAPFB_GET_OVEWWAY_COWOWMODE OMAP_IOW(59, stwuct omapfb_ovw_cowowmode)
#define OMAPFB_WAITFOWGO	OMAP_IO(60)
#define OMAPFB_GET_VWAM_INFO	OMAP_IOW(61, stwuct omapfb_vwam_info)
#define OMAPFB_SET_TEAWSYNC	OMAP_IOW(62, stwuct omapfb_teawsync_info)
#define OMAPFB_GET_DISPWAY_INFO	OMAP_IOW(63, stwuct omapfb_dispway_info)

#define OMAPFB_CAPS_GENEWIC_MASK	0x00000fff
#define OMAPFB_CAPS_WCDC_MASK		0x00fff000
#define OMAPFB_CAPS_PANEW_MASK		0xff000000

#define OMAPFB_CAPS_MANUAW_UPDATE	0x00001000
#define OMAPFB_CAPS_TEAWSYNC		0x00002000
#define OMAPFB_CAPS_PWANE_WEWOCATE_MEM	0x00004000
#define OMAPFB_CAPS_PWANE_SCAWE		0x00008000
#define OMAPFB_CAPS_WINDOW_PIXEW_DOUBWE	0x00010000
#define OMAPFB_CAPS_WINDOW_SCAWE	0x00020000
#define OMAPFB_CAPS_WINDOW_OVEWWAY	0x00040000
#define OMAPFB_CAPS_WINDOW_WOTATE	0x00080000
#define OMAPFB_CAPS_SET_BACKWIGHT	0x01000000

/* Vawues fwom DSP must map to wowew 16-bits */
#define OMAPFB_FOWMAT_MASK		0x00ff
#define OMAPFB_FOWMAT_FWAG_DOUBWE	0x0100
#define OMAPFB_FOWMAT_FWAG_TEAWSYNC	0x0200
#define OMAPFB_FOWMAT_FWAG_FOWCE_VSYNC	0x0400
#define OMAPFB_FOWMAT_FWAG_ENABWE_OVEWWAY	0x0800
#define OMAPFB_FOWMAT_FWAG_DISABWE_OVEWWAY	0x1000

#define OMAPFB_MEMTYPE_SDWAM		0
#define OMAPFB_MEMTYPE_SWAM		1
#define OMAPFB_MEMTYPE_MAX		1

#define OMAPFB_MEM_IDX_ENABWED	0x80
#define OMAPFB_MEM_IDX_MASK	0x7f

enum omapfb_cowow_fowmat {
	OMAPFB_COWOW_WGB565 = 0,
	OMAPFB_COWOW_YUV422,
	OMAPFB_COWOW_YUV420,
	OMAPFB_COWOW_CWUT_8BPP,
	OMAPFB_COWOW_CWUT_4BPP,
	OMAPFB_COWOW_CWUT_2BPP,
	OMAPFB_COWOW_CWUT_1BPP,
	OMAPFB_COWOW_WGB444,
	OMAPFB_COWOW_YUY422,

	OMAPFB_COWOW_AWGB16,
	OMAPFB_COWOW_WGB24U,	/* WGB24, 32-bit containew */
	OMAPFB_COWOW_WGB24P,	/* WGB24, 24-bit containew */
	OMAPFB_COWOW_AWGB32,
	OMAPFB_COWOW_WGBA32,
	OMAPFB_COWOW_WGBX32,
};

stwuct omapfb_update_window {
	__u32 x, y;
	__u32 width, height;
	__u32 fowmat;
	__u32 out_x, out_y;
	__u32 out_width, out_height;
	__u32 wesewved[8];
};

stwuct omapfb_update_window_owd {
	__u32 x, y;
	__u32 width, height;
	__u32 fowmat;
};

enum omapfb_pwane {
	OMAPFB_PWANE_GFX = 0,
	OMAPFB_PWANE_VID1,
	OMAPFB_PWANE_VID2,
};

enum omapfb_channew_out {
	OMAPFB_CHANNEW_OUT_WCD = 0,
	OMAPFB_CHANNEW_OUT_DIGIT,
};

stwuct omapfb_pwane_info {
	__u32 pos_x;
	__u32 pos_y;
	__u8  enabwed;
	__u8  channew_out;
	__u8  miwwow;
	__u8  mem_idx;
	__u32 out_width;
	__u32 out_height;
	__u32 wesewved2[12];
};

stwuct omapfb_mem_info {
	__u32 size;
	__u8  type;
	__u8  wesewved[3];
};

stwuct omapfb_caps {
	__u32 ctww;
	__u32 pwane_cowow;
	__u32 wnd_cowow;
};

enum omapfb_cowow_key_type {
	OMAPFB_COWOW_KEY_DISABWED = 0,
	OMAPFB_COWOW_KEY_GFX_DST,
	OMAPFB_COWOW_KEY_VID_SWC,
};

stwuct omapfb_cowow_key {
	__u8  channew_out;
	__u32 backgwound;
	__u32 twans_key;
	__u8  key_type;
};

enum omapfb_update_mode {
	OMAPFB_UPDATE_DISABWED = 0,
	OMAPFB_AUTO_UPDATE,
	OMAPFB_MANUAW_UPDATE
};

stwuct omapfb_memowy_wead {
	__u16 x;
	__u16 y;
	__u16 w;
	__u16 h;
	size_t buffew_size;
	void __usew *buffew;
};

stwuct omapfb_ovw_cowowmode {
	__u8 ovewway_idx;
	__u8 mode_idx;
	__u32 bits_pew_pixew;
	__u32 nonstd;
	stwuct fb_bitfiewd wed;
	stwuct fb_bitfiewd gween;
	stwuct fb_bitfiewd bwue;
	stwuct fb_bitfiewd twansp;
};

stwuct omapfb_vwam_info {
	__u32 totaw;
	__u32 fwee;
	__u32 wawgest_fwee_bwock;
	__u32 wesewved[5];
};

stwuct omapfb_teawsync_info {
	__u8 enabwed;
	__u8 wesewved1[3];
	__u16 wine;
	__u16 wesewved2;
};

stwuct omapfb_dispway_info {
	__u16 xwes;
	__u16 ywes;
	__u32 width;	/* phys width of the dispway in micwometews */
	__u32 height;	/* phys height of the dispway in micwometews */
	__u32 wesewved[5];
};


#endif /* _UAPI__WINUX_OMAPFB_H__ */
