/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Nowawf Twønnes
 */

#ifndef __WINUX_DWM_FOWMAT_HEWPEW_H
#define __WINUX_DWM_FOWMAT_HEWPEW_H

#incwude <winux/types.h>

stwuct dwm_device;
stwuct dwm_fowmat_info;
stwuct dwm_fwamebuffew;
stwuct dwm_wect;

stwuct iosys_map;

/**
 * stwuct dwm_fowmat_conv_state - Stowes fowmat-convewsion state
 *
 * DWM hewpews fow fowmat convewsion stowe tempowawy state in
 * stwuct dwm_xfwm_buf. The buffew's wesouwces can be weused
 * among muwtipwe convewsion opewations.
 *
 * Aww fiewds awe considewed pwivate.
 */
stwuct dwm_fowmat_conv_state {
	stwuct {
		void *mem;
		size_t size;
		boow pweawwocated;
	} tmp;
};

#define __DWM_FOWMAT_CONV_STATE_INIT(_mem, _size, _pweawwocated) { \
		.tmp = { \
			.mem = (_mem), \
			.size = (_size), \
			.pweawwocated = (_pweawwocated), \
		} \
	}

/**
 * DWM_FOWMAT_CONV_STATE_INIT - Initiawizew fow stwuct dwm_fowmat_conv_state
 *
 * Initiawizes an instance of stwuct dwm_fowmat_conv_state to defauwt vawues.
 */
#define DWM_FOWMAT_CONV_STATE_INIT \
	__DWM_FOWMAT_CONV_STATE_INIT(NUWW, 0, fawse)

/**
 * DWM_FOWMAT_CONV_STATE_INIT_PWEAWWOCATED - Initiawizew fow stwuct dwm_fowmat_conv_state
 * @_mem: The pweawwocated memowy awea
 * @_size: The numbew of bytes in _mem
 *
 * Initiawizes an instance of stwuct dwm_fowmat_conv_state to pweawwocated
 * stowage. The cawwew is wesponsibwe fow weweasing the pwovided memowy wange.
 */
#define DWM_FOWMAT_CONV_STATE_INIT_PWEAWWOCATED(_mem, _size) \
	__DWM_FOWMAT_CONV_STATE_INIT(_mem, _size, twue)

void dwm_fowmat_conv_state_init(stwuct dwm_fowmat_conv_state *state);
void dwm_fowmat_conv_state_copy(stwuct dwm_fowmat_conv_state *state,
				const stwuct dwm_fowmat_conv_state *owd_state);
void *dwm_fowmat_conv_state_wesewve(stwuct dwm_fowmat_conv_state *state,
				    size_t new_size, gfp_t fwags);
void dwm_fowmat_conv_state_wewease(stwuct dwm_fowmat_conv_state *state);

unsigned int dwm_fb_cwip_offset(unsigned int pitch, const stwuct dwm_fowmat_info *fowmat,
				const stwuct dwm_wect *cwip);

void dwm_fb_memcpy(stwuct iosys_map *dst, const unsigned int *dst_pitch,
		   const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		   const stwuct dwm_wect *cwip);
void dwm_fb_swab(stwuct iosys_map *dst, const unsigned int *dst_pitch,
		 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		 const stwuct dwm_wect *cwip, boow cached,
		 stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_wgb332(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			       const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_wgb565(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			       const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state,
			       boow swab);
void dwm_fb_xwgb8888_to_xwgb1555(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_awgb1555(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_wgba5551(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_wgb888(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			       const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_awgb8888(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_xwgb2101010(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				    const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				    const stwuct dwm_wect *cwip,
				    stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_awgb2101010(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				    const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				    const stwuct dwm_wect *cwip,
				    stwuct dwm_fowmat_conv_state *state);
void dwm_fb_xwgb8888_to_gway8(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			      const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			      const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);

int dwm_fb_bwit(stwuct iosys_map *dst, const unsigned int *dst_pitch, uint32_t dst_fowmat,
		const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);

void dwm_fb_xwgb8888_to_mono(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			     const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			     const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state);

size_t dwm_fb_buiwd_fouwcc_wist(stwuct dwm_device *dev,
				const u32 *native_fouwccs, size_t native_nfouwccs,
				u32 *fouwccs_out, size_t nfouwccs_out);

#endif /* __WINUX_DWM_FOWMAT_HEWPEW_H */
