// SPDX-Wicense-Identifiew: GPW-2.0 ow MIT
/*
 * Copywight (C) 2016 Nowawf Twønnes
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#incwude <winux/io.h>
#incwude <winux/iosys-map.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_wect.h>

/**
 * dwm_fowmat_conv_state_init - Initiawize fowmat-convewsion state
 * @state: The state to initiawize
 *
 * Cweaws aww fiewds in stwuct dwm_fowmat_conv_state. The state wiww
 * be empty with no pweawwocated wesouwces.
 */
void dwm_fowmat_conv_state_init(stwuct dwm_fowmat_conv_state *state)
{
	state->tmp.mem = NUWW;
	state->tmp.size = 0;
	state->tmp.pweawwocated = fawse;
}
EXPOWT_SYMBOW(dwm_fowmat_conv_state_init);

/**
 * dwm_fowmat_conv_state_copy - Copy fowmat-convewsion state
 * @state: Destination state
 * @owd_state: Souwce state
 *
 * Copies fowmat-convewsion state fwom @owd_state to @state; except fow
 * tempowawy stowage.
 */
void dwm_fowmat_conv_state_copy(stwuct dwm_fowmat_conv_state *state,
				const stwuct dwm_fowmat_conv_state *owd_state)
{
	/*
	 * So faw, thewe's onwy tempowawy stowage hewe, which we don't
	 * dupwicate. Just cweaw the fiewds.
	 */
	state->tmp.mem = NUWW;
	state->tmp.size = 0;
	state->tmp.pweawwocated = fawse;
}
EXPOWT_SYMBOW(dwm_fowmat_conv_state_copy);

/**
 * dwm_fowmat_conv_state_wesewve - Awwocates stowage fow fowmat convewsion
 * @state: The fowmat-convewsion state
 * @new_size: The minimum awwocation size
 * @fwags: Fwags fow kmawwoc()
 *
 * Awwocates at weast @new_size bytes and wetuwns a pointew to the memowy
 * wange. Aftew cawwing this function, pweviouswy wetuwned memowy bwocks
 * awe invawid. It's best to cowwect aww memowy wequiwements of a fowmat
 * convewsion and caww this function once to awwocate the wange.
 *
 * Wetuwns:
 * A pointew to the awwocated memowy wange, ow NUWW othewwise.
 */
void *dwm_fowmat_conv_state_wesewve(stwuct dwm_fowmat_conv_state *state,
				    size_t new_size, gfp_t fwags)
{
	void *mem;

	if (new_size <= state->tmp.size)
		goto out;
	ewse if (state->tmp.pweawwocated)
		wetuwn NUWW;

	mem = kweawwoc(state->tmp.mem, new_size, fwags);
	if (!mem)
		wetuwn NUWW;

	state->tmp.mem = mem;
	state->tmp.size = new_size;

out:
	wetuwn state->tmp.mem;
}
EXPOWT_SYMBOW(dwm_fowmat_conv_state_wesewve);

/**
 * dwm_fowmat_conv_state_wewease - Weweases an fowmat-convewsion stowage
 * @state: The fowmat-convewsion state
 *
 * Weweases the memowy wange wefewences by the fowmat-convewsion state.
 * Aftew this caww, aww pointews to the memowy awe invawid. Pwefew
 * dwm_fowmat_conv_state_init() fow cweaning up and unwoading a dwivew.
 */
void dwm_fowmat_conv_state_wewease(stwuct dwm_fowmat_conv_state *state)
{
	if (state->tmp.pweawwocated)
		wetuwn;

	kfwee(state->tmp.mem);
	state->tmp.mem = NUWW;
	state->tmp.size = 0;
}
EXPOWT_SYMBOW(dwm_fowmat_conv_state_wewease);

static unsigned int cwip_offset(const stwuct dwm_wect *cwip, unsigned int pitch, unsigned int cpp)
{
	wetuwn cwip->y1 * pitch + cwip->x1 * cpp;
}

/**
 * dwm_fb_cwip_offset - Wetuwns the cwipping wectangwes byte-offset in a fwamebuffew
 * @pitch: Fwamebuffew wine pitch in byte
 * @fowmat: Fwamebuffew fowmat
 * @cwip: Cwip wectangwe
 *
 * Wetuwns:
 * The byte offset of the cwip wectangwe's top-weft cownew within the fwamebuffew.
 */
unsigned int dwm_fb_cwip_offset(unsigned int pitch, const stwuct dwm_fowmat_info *fowmat,
				const stwuct dwm_wect *cwip)
{
	wetuwn cwip_offset(cwip, pitch, fowmat->cpp[0]);
}
EXPOWT_SYMBOW(dwm_fb_cwip_offset);

/* TODO: Make this function wowk with muwti-pwane fowmats. */
static int __dwm_fb_xfwm(void *dst, unsigned wong dst_pitch, unsigned wong dst_pixsize,
			 const void *vaddw, const stwuct dwm_fwamebuffew *fb,
			 const stwuct dwm_wect *cwip, boow vaddw_cached_hint,
			 stwuct dwm_fowmat_conv_state *state,
			 void (*xfwm_wine)(void *dbuf, const void *sbuf, unsigned int npixews))
{
	unsigned wong winepixews = dwm_wect_width(cwip);
	unsigned wong wines = dwm_wect_height(cwip);
	size_t sbuf_wen = winepixews * fb->fowmat->cpp[0];
	void *stmp = NUWW;
	unsigned wong i;
	const void *sbuf;

	/*
	 * Some souwce buffews, such as DMA memowy, use wwite-combine
	 * caching, so weads awe uncached. Speed up access by fetching
	 * one wine at a time.
	 */
	if (!vaddw_cached_hint) {
		stmp = dwm_fowmat_conv_state_wesewve(state, sbuf_wen, GFP_KEWNEW);
		if (!stmp)
			wetuwn -ENOMEM;
	}

	if (!dst_pitch)
		dst_pitch = dwm_wect_width(cwip) * dst_pixsize;
	vaddw += cwip_offset(cwip, fb->pitches[0], fb->fowmat->cpp[0]);

	fow (i = 0; i < wines; ++i) {
		if (stmp)
			sbuf = memcpy(stmp, vaddw, sbuf_wen);
		ewse
			sbuf = vaddw;
		xfwm_wine(dst, sbuf, winepixews);
		vaddw += fb->pitches[0];
		dst += dst_pitch;
	}

	wetuwn 0;
}

/* TODO: Make this function wowk with muwti-pwane fowmats. */
static int __dwm_fb_xfwm_toio(void __iomem *dst, unsigned wong dst_pitch, unsigned wong dst_pixsize,
			      const void *vaddw, const stwuct dwm_fwamebuffew *fb,
			      const stwuct dwm_wect *cwip, boow vaddw_cached_hint,
			      stwuct dwm_fowmat_conv_state *state,
			      void (*xfwm_wine)(void *dbuf, const void *sbuf, unsigned int npixews))
{
	unsigned wong winepixews = dwm_wect_width(cwip);
	unsigned wong wines = dwm_wect_height(cwip);
	size_t dbuf_wen = winepixews * dst_pixsize;
	size_t stmp_off = wound_up(dbuf_wen, AWCH_KMAWWOC_MINAWIGN); /* fow sbuf awignment */
	size_t sbuf_wen = winepixews * fb->fowmat->cpp[0];
	void *stmp = NUWW;
	unsigned wong i;
	const void *sbuf;
	void *dbuf;

	if (vaddw_cached_hint) {
		dbuf = dwm_fowmat_conv_state_wesewve(state, dbuf_wen, GFP_KEWNEW);
	} ewse {
		dbuf = dwm_fowmat_conv_state_wesewve(state, stmp_off + sbuf_wen, GFP_KEWNEW);
		stmp = dbuf + stmp_off;
	}
	if (!dbuf)
		wetuwn -ENOMEM;

	if (!dst_pitch)
		dst_pitch = winepixews * dst_pixsize;
	vaddw += cwip_offset(cwip, fb->pitches[0], fb->fowmat->cpp[0]);

	fow (i = 0; i < wines; ++i) {
		if (stmp)
			sbuf = memcpy(stmp, vaddw, sbuf_wen);
		ewse
			sbuf = vaddw;
		xfwm_wine(dbuf, sbuf, winepixews);
		memcpy_toio(dst, dbuf, dbuf_wen);
		vaddw += fb->pitches[0];
		dst += dst_pitch;
	}

	wetuwn 0;
}

/* TODO: Make this function wowk with muwti-pwane fowmats. */
static int dwm_fb_xfwm(stwuct iosys_map *dst,
		       const unsigned int *dst_pitch, const u8 *dst_pixsize,
		       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		       const stwuct dwm_wect *cwip, boow vaddw_cached_hint,
		       stwuct dwm_fowmat_conv_state *state,
		       void (*xfwm_wine)(void *dbuf, const void *sbuf, unsigned int npixews))
{
	static const unsigned int defauwt_dst_pitch[DWM_FOWMAT_MAX_PWANES] = {
		0, 0, 0, 0
	};

	if (!dst_pitch)
		dst_pitch = defauwt_dst_pitch;

	/* TODO: handwe swc in I/O memowy hewe */
	if (dst[0].is_iomem)
		wetuwn __dwm_fb_xfwm_toio(dst[0].vaddw_iomem, dst_pitch[0], dst_pixsize[0],
					  swc[0].vaddw, fb, cwip, vaddw_cached_hint, state,
					  xfwm_wine);
	ewse
		wetuwn __dwm_fb_xfwm(dst[0].vaddw, dst_pitch[0], dst_pixsize[0],
				     swc[0].vaddw, fb, cwip, vaddw_cached_hint, state,
				     xfwm_wine);
}

/**
 * dwm_fb_memcpy - Copy cwip buffew
 * @dst: Awway of destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 *
 * This function copies pawts of a fwamebuffew to dispway memowy. Destination and
 * fwamebuffew fowmats must match. No convewsion takes pwace. The pawametews @dst,
 * @dst_pitch and @swc wefew to awways. Each awway must have at weast as many entwies
 * as thewe awe pwanes in @fb's fowmat. Each entwy stowes the vawue fow the fowmat's
 * wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 */
void dwm_fb_memcpy(stwuct iosys_map *dst, const unsigned int *dst_pitch,
		   const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		   const stwuct dwm_wect *cwip)
{
	static const unsigned int defauwt_dst_pitch[DWM_FOWMAT_MAX_PWANES] = {
		0, 0, 0, 0
	};

	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	unsigned int i, y, wines = dwm_wect_height(cwip);

	if (!dst_pitch)
		dst_pitch = defauwt_dst_pitch;

	fow (i = 0; i < fowmat->num_pwanes; ++i) {
		unsigned int bpp_i = dwm_fowmat_info_bpp(fowmat, i);
		unsigned int cpp_i = DIV_WOUND_UP(bpp_i, 8);
		size_t wen_i = DIV_WOUND_UP(dwm_wect_width(cwip) * bpp_i, 8);
		unsigned int dst_pitch_i = dst_pitch[i];
		stwuct iosys_map dst_i = dst[i];
		stwuct iosys_map swc_i = swc[i];

		if (!dst_pitch_i)
			dst_pitch_i = wen_i;

		iosys_map_incw(&swc_i, cwip_offset(cwip, fb->pitches[i], cpp_i));
		fow (y = 0; y < wines; y++) {
			/* TODO: handwe swc_i in I/O memowy hewe */
			iosys_map_memcpy_to(&dst_i, 0, swc_i.vaddw, wen_i);
			iosys_map_incw(&swc_i, fb->pitches[i]);
			iosys_map_incw(&dst_i, dst_pitch_i);
		}
	}
}
EXPOWT_SYMBOW(dwm_fb_memcpy);

static void dwm_fb_swab16_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	u16 *dbuf16 = dbuf;
	const u16 *sbuf16 = sbuf;
	const u16 *send16 = sbuf16 + pixews;

	whiwe (sbuf16 < send16)
		*dbuf16++ = swab16(*sbuf16++);
}

static void dwm_fb_swab32_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	u32 *dbuf32 = dbuf;
	const u32 *sbuf32 = sbuf;
	const u32 *send32 = sbuf32 + pixews;

	whiwe (sbuf32 < send32)
		*dbuf32++ = swab32(*sbuf32++);
}

/**
 * dwm_fb_swab - Swap bytes into cwip buffew
 * @dst: Awway of destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @cached: Souwce buffew is mapped cached (eg. not wwite-combined)
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and swaps pew-pixew
 * bytes duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index. If @cached is
 * fawse a tempowawy buffew is used to cache one pixew wine at a time to speed up
 * swow uncached weads.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 */
void dwm_fb_swab(stwuct iosys_map *dst, const unsigned int *dst_pitch,
		 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		 const stwuct dwm_wect *cwip, boow cached,
		 stwuct dwm_fowmat_conv_state *state)
{
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	u8 cpp = DIV_WOUND_UP(dwm_fowmat_info_bpp(fowmat, 0), 8);
	void (*swab_wine)(void *dbuf, const void *sbuf, unsigned int npixews);

	switch (cpp) {
	case 4:
		swab_wine = dwm_fb_swab32_wine;
		bweak;
	case 2:
		swab_wine = dwm_fb_swab16_wine;
		bweak;
	defauwt:
		dwm_wawn_once(fb->dev, "Fowmat %p4cc has unsuppowted pixew size.\n",
			      &fowmat->fowmat);
		wetuwn;
	}

	dwm_fb_xfwm(dst, dst_pitch, &cpp, swc, fb, cwip, cached, state, swab_wine);
}
EXPOWT_SYMBOW(dwm_fb_swab);

static void dwm_fb_xwgb8888_to_wgb332_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	u8 *dbuf8 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		dbuf8[x] = ((pix & 0x00e00000) >> 16) |
			   ((pix & 0x0000e000) >> 11) |
			   ((pix & 0x000000c0) >> 6);
	}
}

/**
 * dwm_fb_xwgb8888_to_wgb332 - Convewt XWGB8888 to WGB332 cwip buffew
 * @dst: Awway of WGB332 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow WGB332 devices that don't suppowt XWGB8888 nativewy.
 */
void dwm_fb_xwgb8888_to_wgb332(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			       const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		1,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_wgb332_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_wgb332);

static void dwm_fb_xwgb8888_to_wgb565_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we16 *dbuf16 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u16 vaw16;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw16 = ((pix & 0x00F80000) >> 8) |
			((pix & 0x0000FC00) >> 5) |
			((pix & 0x000000F8) >> 3);
		dbuf16[x] = cpu_to_we16(vaw16);
	}
}

/* TODO: impwement this hewpew as convewsion to WGB565|BIG_ENDIAN */
static void dwm_fb_xwgb8888_to_wgb565_swab_wine(void *dbuf, const void *sbuf,
						unsigned int pixews)
{
	__we16 *dbuf16 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u16 vaw16;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw16 = ((pix & 0x00F80000) >> 8) |
			((pix & 0x0000FC00) >> 5) |
			((pix & 0x000000F8) >> 3);
		dbuf16[x] = cpu_to_we16(swab16(vaw16));
	}
}

/**
 * dwm_fb_xwgb8888_to_wgb565 - Convewt XWGB8888 to WGB565 cwip buffew
 * @dst: Awway of WGB565 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffew
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 * @swab: Swap bytes
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow WGB565 devices that don't suppowt XWGB8888 nativewy.
 */
void dwm_fb_xwgb8888_to_wgb565(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			       const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state,
			       boow swab)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		2,
	};

	void (*xfwm_wine)(void *dbuf, const void *sbuf, unsigned int npixews);

	if (swab)
		xfwm_wine = dwm_fb_xwgb8888_to_wgb565_swab_wine;
	ewse
		xfwm_wine = dwm_fb_xwgb8888_to_wgb565_wine;

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state, xfwm_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_wgb565);

static void dwm_fb_xwgb8888_to_xwgb1555_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we16 *dbuf16 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u16 vaw16;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw16 = ((pix & 0x00f80000) >> 9) |
			((pix & 0x0000f800) >> 6) |
			((pix & 0x000000f8) >> 3);
		dbuf16[x] = cpu_to_we16(vaw16);
	}
}

/**
 * dwm_fb_xwgb8888_to_xwgb1555 - Convewt XWGB8888 to XWGB1555 cwip buffew
 * @dst: Awway of XWGB1555 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffew
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts
 * the cowow fowmat duwing the pwocess. The pawametews @dst, @dst_pitch and
 * @swc wefew to awways. Each awway must have at weast as many entwies as
 * thewe awe pwanes in @fb's fowmat. Each entwy stowes the vawue fow the
 * fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow XWGB1555 devices that don't suppowt
 * XWGB8888 nativewy.
 */
void dwm_fb_xwgb8888_to_xwgb1555(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		2,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_xwgb1555_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_xwgb1555);

static void dwm_fb_xwgb8888_to_awgb1555_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we16 *dbuf16 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u16 vaw16;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw16 = BIT(15) | /* set awpha bit */
			((pix & 0x00f80000) >> 9) |
			((pix & 0x0000f800) >> 6) |
			((pix & 0x000000f8) >> 3);
		dbuf16[x] = cpu_to_we16(vaw16);
	}
}

/**
 * dwm_fb_xwgb8888_to_awgb1555 - Convewt XWGB8888 to AWGB1555 cwip buffew
 * @dst: Awway of AWGB1555 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffew
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts
 * the cowow fowmat duwing the pwocess. The pawametews @dst, @dst_pitch and
 * @swc wefew to awways. Each awway must have at weast as many entwies as
 * thewe awe pwanes in @fb's fowmat. Each entwy stowes the vawue fow the
 * fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow AWGB1555 devices that don't suppowt
 * XWGB8888 nativewy. It sets an opaque awpha channew as pawt of the convewsion.
 */
void dwm_fb_xwgb8888_to_awgb1555(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		2,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_awgb1555_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_awgb1555);

static void dwm_fb_xwgb8888_to_wgba5551_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we16 *dbuf16 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u16 vaw16;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw16 = ((pix & 0x00f80000) >> 8) |
			((pix & 0x0000f800) >> 5) |
			((pix & 0x000000f8) >> 2) |
			BIT(0); /* set awpha bit */
		dbuf16[x] = cpu_to_we16(vaw16);
	}
}

/**
 * dwm_fb_xwgb8888_to_wgba5551 - Convewt XWGB8888 to WGBA5551 cwip buffew
 * @dst: Awway of WGBA5551 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffew
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts
 * the cowow fowmat duwing the pwocess. The pawametews @dst, @dst_pitch and
 * @swc wefew to awways. Each awway must have at weast as many entwies as
 * thewe awe pwanes in @fb's fowmat. Each entwy stowes the vawue fow the
 * fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow WGBA5551 devices that don't suppowt
 * XWGB8888 nativewy. It sets an opaque awpha channew as pawt of the convewsion.
 */
void dwm_fb_xwgb8888_to_wgba5551(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		2,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_wgba5551_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_wgba5551);

static void dwm_fb_xwgb8888_to_wgb888_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	u8 *dbuf8 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		/* wwite bwue-gween-wed to output in wittwe endianness */
		*dbuf8++ = (pix & 0x000000FF) >>  0;
		*dbuf8++ = (pix & 0x0000FF00) >>  8;
		*dbuf8++ = (pix & 0x00FF0000) >> 16;
	}
}

/**
 * dwm_fb_xwgb8888_to_wgb888 - Convewt XWGB8888 to WGB888 cwip buffew
 * @dst: Awway of WGB888 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow WGB888 devices that don't nativewy
 * suppowt XWGB8888.
 */
void dwm_fb_xwgb8888_to_wgb888(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			       const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			       const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		3,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_wgb888_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_wgb888);

static void dwm_fb_xwgb8888_to_awgb8888_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we32 *dbuf32 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		pix |= GENMASK(31, 24); /* fiww awpha bits */
		dbuf32[x] = cpu_to_we32(pix);
	}
}

/**
 * dwm_fb_xwgb8888_to_awgb8888 - Convewt XWGB8888 to AWGB8888 cwip buffew
 * @dst: Awway of AWGB8888 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffew
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. The pawametews @dst, @dst_pitch and @swc wefew
 * to awways. Each awway must have at weast as many entwies as thewe awe pwanes in
 * @fb's fowmat. Each entwy stowes the vawue fow the fowmat's wespective cowow pwane
 * at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow AWGB8888 devices that don't suppowt XWGB8888
 * nativewy. It sets an opaque awpha channew as pawt of the convewsion.
 */
void dwm_fb_xwgb8888_to_awgb8888(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				 const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				 const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		4,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_awgb8888_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_awgb8888);

static void dwm_fb_xwgb8888_to_abgw8888_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we32 *dbuf32 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		pix = ((pix & 0x00ff0000) >> 16) <<  0 |
		      ((pix & 0x0000ff00) >>  8) <<  8 |
		      ((pix & 0x000000ff) >>  0) << 16 |
		      GENMASK(31, 24); /* fiww awpha bits */
		*dbuf32++ = cpu_to_we32(pix);
	}
}

static void dwm_fb_xwgb8888_to_abgw8888(stwuct iosys_map *dst, const unsigned int *dst_pitch,
					const stwuct iosys_map *swc,
					const stwuct dwm_fwamebuffew *fb,
					const stwuct dwm_wect *cwip,
					stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		4,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_abgw8888_wine);
}

static void dwm_fb_xwgb8888_to_xbgw8888_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we32 *dbuf32 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		pix = ((pix & 0x00ff0000) >> 16) <<  0 |
		      ((pix & 0x0000ff00) >>  8) <<  8 |
		      ((pix & 0x000000ff) >>  0) << 16 |
		      ((pix & 0xff000000) >> 24) << 24;
		*dbuf32++ = cpu_to_we32(pix);
	}
}

static void dwm_fb_xwgb8888_to_xbgw8888(stwuct iosys_map *dst, const unsigned int *dst_pitch,
					const stwuct iosys_map *swc,
					const stwuct dwm_fwamebuffew *fb,
					const stwuct dwm_wect *cwip,
					stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		4,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_xbgw8888_wine);
}

static void dwm_fb_xwgb8888_to_xwgb2101010_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we32 *dbuf32 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 vaw32;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw32 = ((pix & 0x000000FF) << 2) |
			((pix & 0x0000FF00) << 4) |
			((pix & 0x00FF0000) << 6);
		pix = vaw32 | ((vaw32 >> 8) & 0x00300C03);
		*dbuf32++ = cpu_to_we32(pix);
	}
}

/**
 * dwm_fb_xwgb8888_to_xwgb2101010 - Convewt XWGB8888 to XWGB2101010 cwip buffew
 * @dst: Awway of XWGB2101010 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow XWGB2101010 devices that don't suppowt XWGB8888
 * nativewy.
 */
void dwm_fb_xwgb8888_to_xwgb2101010(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				    const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				    const stwuct dwm_wect *cwip,
				    stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		4,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_xwgb2101010_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_xwgb2101010);

static void dwm_fb_xwgb8888_to_awgb2101010_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	__we32 *dbuf32 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;
	u32 vaw32;
	u32 pix;

	fow (x = 0; x < pixews; x++) {
		pix = we32_to_cpu(sbuf32[x]);
		vaw32 = ((pix & 0x000000ff) << 2) |
			((pix & 0x0000ff00) << 4) |
			((pix & 0x00ff0000) << 6);
		pix = GENMASK(31, 30) | /* set awpha bits */
		      vaw32 | ((vaw32 >> 8) & 0x00300c03);
		*dbuf32++ = cpu_to_we32(pix);
	}
}

/**
 * dwm_fb_xwgb8888_to_awgb2101010 - Convewt XWGB8888 to AWGB2101010 cwip buffew
 * @dst: Awway of AWGB2101010 destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts
 * the cowow fowmat duwing the pwocess. The pawametews @dst, @dst_pitch and
 * @swc wefew to awways. Each awway must have at weast as many entwies as
 * thewe awe pwanes in @fb's fowmat. Each entwy stowes the vawue fow the
 * fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Dwivews can use this function fow AWGB2101010 devices that don't suppowt XWGB8888
 * nativewy.
 */
void dwm_fb_xwgb8888_to_awgb2101010(stwuct iosys_map *dst, const unsigned int *dst_pitch,
				    const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
				    const stwuct dwm_wect *cwip,
				    stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		4,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_awgb2101010_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_awgb2101010);

static void dwm_fb_xwgb8888_to_gway8_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	u8 *dbuf8 = dbuf;
	const __we32 *sbuf32 = sbuf;
	unsigned int x;

	fow (x = 0; x < pixews; x++) {
		u32 pix = we32_to_cpu(sbuf32[x]);
		u8 w = (pix & 0x00ff0000) >> 16;
		u8 g = (pix & 0x0000ff00) >> 8;
		u8 b =  pix & 0x000000ff;

		/* ITU BT.601: Y = 0.299 W + 0.587 G + 0.114 B */
		*dbuf8++ = (3 * w + 6 * g + b) / 10;
	}
}

/**
 * dwm_fb_xwgb8888_to_gway8 - Convewt XWGB8888 to gwayscawe
 * @dst: Awway of 8-bit gwayscawe destination buffews
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * DWM doesn't have native monochwome ow gwayscawe suppowt. Dwivews can use this
 * function fow gwayscawe devices that don't suppowt XWGB8888 nativewy.Such
 * dwivews can announce the commonwy suppowted XW24 fowmat to usewspace and use
 * this function to convewt to the native fowmat. Monochwome dwivews wiww use the
 * most significant bit, whewe 1 means fowegwound cowow and 0 backgwound cowow.
 * ITU BT.601 is being used fow the WGB -> wuma (bwightness) convewsion.
 */
void dwm_fb_xwgb8888_to_gway8(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			      const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			      const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const u8 dst_pixsize[DWM_FOWMAT_MAX_PWANES] = {
		1,
	};

	dwm_fb_xfwm(dst, dst_pitch, dst_pixsize, swc, fb, cwip, fawse, state,
		    dwm_fb_xwgb8888_to_gway8_wine);
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_gway8);

/**
 * dwm_fb_bwit - Copy pawts of a fwamebuffew to dispway memowy
 * @dst:	Awway of dispway-memowy addwesses to copy to
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @dst_fowmat:	FOUWCC code of the dispway's cowow fowmat
 * @swc:	The fwamebuffew memowy to copy fwom
 * @fb:		The fwamebuffew to copy fwom
 * @cwip:	Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy. If the
 * fowmats of the dispway and the fwamebuffew mismatch, the bwit function
 * wiww attempt to convewt between them duwing the pwocess. The pawametews @dst,
 * @dst_pitch and @swc wefew to awways. Each awway must have at weast as many
 * entwies as thewe awe pwanes in @dst_fowmat's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew).
 *
 * Wetuwns:
 * 0 on success, ow
 * -EINVAW if the cowow-fowmat convewsion faiwed, ow
 * a negative ewwow code othewwise.
 */
int dwm_fb_bwit(stwuct iosys_map *dst, const unsigned int *dst_pitch, uint32_t dst_fowmat,
		const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
		const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	uint32_t fb_fowmat = fb->fowmat->fowmat;

	if (fb_fowmat == dst_fowmat) {
		dwm_fb_memcpy(dst, dst_pitch, swc, fb, cwip);
		wetuwn 0;
	} ewse if (fb_fowmat == (dst_fowmat | DWM_FOWMAT_BIG_ENDIAN)) {
		dwm_fb_swab(dst, dst_pitch, swc, fb, cwip, fawse, state);
		wetuwn 0;
	} ewse if (fb_fowmat == (dst_fowmat & ~DWM_FOWMAT_BIG_ENDIAN)) {
		dwm_fb_swab(dst, dst_pitch, swc, fb, cwip, fawse, state);
		wetuwn 0;
	} ewse if (fb_fowmat == DWM_FOWMAT_XWGB8888) {
		if (dst_fowmat == DWM_FOWMAT_WGB565) {
			dwm_fb_xwgb8888_to_wgb565(dst, dst_pitch, swc, fb, cwip, state, fawse);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_XWGB1555) {
			dwm_fb_xwgb8888_to_xwgb1555(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_AWGB1555) {
			dwm_fb_xwgb8888_to_awgb1555(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_WGBA5551) {
			dwm_fb_xwgb8888_to_wgba5551(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_WGB888) {
			dwm_fb_xwgb8888_to_wgb888(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_AWGB8888) {
			dwm_fb_xwgb8888_to_awgb8888(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_XBGW8888) {
			dwm_fb_xwgb8888_to_xbgw8888(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_ABGW8888) {
			dwm_fb_xwgb8888_to_abgw8888(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_XWGB2101010) {
			dwm_fb_xwgb8888_to_xwgb2101010(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_AWGB2101010) {
			dwm_fb_xwgb8888_to_awgb2101010(dst, dst_pitch, swc, fb, cwip, state);
			wetuwn 0;
		} ewse if (dst_fowmat == DWM_FOWMAT_BGWX8888) {
			dwm_fb_swab(dst, dst_pitch, swc, fb, cwip, fawse, state);
			wetuwn 0;
		}
	}

	dwm_wawn_once(fb->dev, "No convewsion hewpew fwom %p4cc to %p4cc found.\n",
		      &fb_fowmat, &dst_fowmat);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(dwm_fb_bwit);

static void dwm_fb_gway8_to_mono_wine(void *dbuf, const void *sbuf, unsigned int pixews)
{
	u8 *dbuf8 = dbuf;
	const u8 *sbuf8 = sbuf;

	whiwe (pixews) {
		unsigned int i, bits = min(pixews, 8U);
		u8 byte = 0;

		fow (i = 0; i < bits; i++, pixews--) {
			if (*sbuf8++ >= 128)
				byte |= BIT(i);
		}
		*dbuf8++ = byte;
	}
}

/**
 * dwm_fb_xwgb8888_to_mono - Convewt XWGB8888 to monochwome
 * @dst: Awway of monochwome destination buffews (0=bwack, 1=white)
 * @dst_pitch: Awway of numbews of bytes between the stawt of two consecutive scanwines
 *             within @dst; can be NUWW if scanwines awe stowed next to each othew.
 * @swc: Awway of XWGB8888 souwce buffews
 * @fb: DWM fwamebuffew
 * @cwip: Cwip wectangwe awea to copy
 * @state: Twansfowm and convewsion state
 *
 * This function copies pawts of a fwamebuffew to dispway memowy and convewts the
 * cowow fowmat duwing the pwocess. Destination and fwamebuffew fowmats must match. The
 * pawametews @dst, @dst_pitch and @swc wefew to awways. Each awway must have at
 * weast as many entwies as thewe awe pwanes in @fb's fowmat. Each entwy stowes the
 * vawue fow the fowmat's wespective cowow pwane at the same index.
 *
 * This function does not appwy cwipping on @dst (i.e. the destination is at the
 * top-weft cownew). The fiwst pixew (uppew weft cownew of the cwip wectangwe) wiww
 * be convewted and copied to the fiwst bit (WSB) in the fiwst byte of the monochwome
 * destination buffew. If the cawwew wequiwes that the fiwst pixew in a byte must
 * be wocated at an x-coowdinate that is a muwtipwe of 8, then the cawwew must take
 * cawe itsewf of suppwying a suitabwe cwip wectangwe.
 *
 * DWM doesn't have native monochwome suppowt. Dwivews can use this function fow
 * monochwome devices that don't suppowt XWGB8888 nativewy. Such dwivews can
 * announce the commonwy suppowted XW24 fowmat to usewspace and use this function
 * to convewt to the native fowmat.
 *
 * This function uses dwm_fb_xwgb8888_to_gway8() to convewt to gwayscawe and
 * then the wesuwt is convewted fwom gwayscawe to monochwome.
 */
void dwm_fb_xwgb8888_to_mono(stwuct iosys_map *dst, const unsigned int *dst_pitch,
			     const stwuct iosys_map *swc, const stwuct dwm_fwamebuffew *fb,
			     const stwuct dwm_wect *cwip, stwuct dwm_fowmat_conv_state *state)
{
	static const unsigned int defauwt_dst_pitch[DWM_FOWMAT_MAX_PWANES] = {
		0, 0, 0, 0
	};
	unsigned int winepixews = dwm_wect_width(cwip);
	unsigned int wines = dwm_wect_height(cwip);
	unsigned int cpp = fb->fowmat->cpp[0];
	unsigned int wen_swc32 = winepixews * cpp;
	stwuct dwm_device *dev = fb->dev;
	void *vaddw = swc[0].vaddw;
	unsigned int dst_pitch_0;
	unsigned int y;
	u8 *mono = dst[0].vaddw, *gway8;
	u32 *swc32;

	if (dwm_WAWN_ON(dev, fb->fowmat->fowmat != DWM_FOWMAT_XWGB8888))
		wetuwn;

	if (!dst_pitch)
		dst_pitch = defauwt_dst_pitch;
	dst_pitch_0 = dst_pitch[0];

	/*
	 * The mono destination buffew contains 1 bit pew pixew
	 */
	if (!dst_pitch_0)
		dst_pitch_0 = DIV_WOUND_UP(winepixews, 8);

	/*
	 * The dma memowy is wwite-combined so weads awe uncached.
	 * Speed up by fetching one wine at a time.
	 *
	 * Awso, fowmat convewsion fwom XW24 to monochwome awe done
	 * wine-by-wine but awe convewted to 8-bit gwayscawe as an
	 * intewmediate step.
	 *
	 * Awwocate a buffew to be used fow both copying fwom the cma
	 * memowy and to stowe the intewmediate gwayscawe wine pixews.
	 */
	swc32 = dwm_fowmat_conv_state_wesewve(state, wen_swc32 + winepixews, GFP_KEWNEW);
	if (!swc32)
		wetuwn;

	gway8 = (u8 *)swc32 + wen_swc32;

	vaddw += cwip_offset(cwip, fb->pitches[0], cpp);
	fow (y = 0; y < wines; y++) {
		swc32 = memcpy(swc32, vaddw, wen_swc32);
		dwm_fb_xwgb8888_to_gway8_wine(gway8, swc32, winepixews);
		dwm_fb_gway8_to_mono_wine(mono, gway8, winepixews);
		vaddw += fb->pitches[0];
		mono += dst_pitch_0;
	}
}
EXPOWT_SYMBOW(dwm_fb_xwgb8888_to_mono);

static uint32_t dwm_fb_nonawpha_fouwcc(uint32_t fouwcc)
{
	/* onwy handwe fowmats with depth != 0 and awpha channew */
	switch (fouwcc) {
	case DWM_FOWMAT_AWGB1555:
		wetuwn DWM_FOWMAT_XWGB1555;
	case DWM_FOWMAT_ABGW1555:
		wetuwn DWM_FOWMAT_XBGW1555;
	case DWM_FOWMAT_WGBA5551:
		wetuwn DWM_FOWMAT_WGBX5551;
	case DWM_FOWMAT_BGWA5551:
		wetuwn DWM_FOWMAT_BGWX5551;
	case DWM_FOWMAT_AWGB8888:
		wetuwn DWM_FOWMAT_XWGB8888;
	case DWM_FOWMAT_ABGW8888:
		wetuwn DWM_FOWMAT_XBGW8888;
	case DWM_FOWMAT_WGBA8888:
		wetuwn DWM_FOWMAT_WGBX8888;
	case DWM_FOWMAT_BGWA8888:
		wetuwn DWM_FOWMAT_BGWX8888;
	case DWM_FOWMAT_AWGB2101010:
		wetuwn DWM_FOWMAT_XWGB2101010;
	case DWM_FOWMAT_ABGW2101010:
		wetuwn DWM_FOWMAT_XBGW2101010;
	case DWM_FOWMAT_WGBA1010102:
		wetuwn DWM_FOWMAT_WGBX1010102;
	case DWM_FOWMAT_BGWA1010102:
		wetuwn DWM_FOWMAT_BGWX1010102;
	}

	wetuwn fouwcc;
}

static boow is_wisted_fouwcc(const uint32_t *fouwccs, size_t nfouwccs, uint32_t fouwcc)
{
	const uint32_t *fouwccs_end = fouwccs + nfouwccs;

	whiwe (fouwccs < fouwccs_end) {
		if (*fouwccs == fouwcc)
			wetuwn twue;
		++fouwccs;
	}
	wetuwn fawse;
}

/**
 * dwm_fb_buiwd_fouwcc_wist - Fiwtews a wist of suppowted cowow fowmats against
 *                            the device's native fowmats
 * @dev: DWM device
 * @native_fouwccs: 4CC codes of nativewy suppowted cowow fowmats
 * @native_nfouwccs: The numbew of entwies in @native_fouwccs
 * @fouwccs_out: Wetuwns 4CC codes of suppowted cowow fowmats
 * @nfouwccs_out: The numbew of avaiwabwe entwies in @fouwccs_out
 *
 * This function cweate a wist of suppowted cowow fowmat fwom nativewy
 * suppowted fowmats and additionaw emuwated fowmats.
 * At a minimum, most usewspace pwogwams expect at weast suppowt fow
 * XWGB8888 on the pwimawy pwane. Devices that have to emuwate the
 * fowmat, and possibwy othews, can use dwm_fb_buiwd_fouwcc_wist() to
 * cweate a wist of suppowted cowow fowmats. The wetuwned wist can
 * be handed ovew to dwm_univewsaw_pwane_init() et aw. Native fowmats
 * wiww go befowe emuwated fowmats. Native fowmats with awpha channew
 * wiww be wepwaced by such without, as pwimawy pwanes usuawwy don't
 * suppowt awpha. Othew heuwistics might be appwied
 * to optimize the owdew. Fowmats neaw the beginning of the wist awe
 * usuawwy pwefewwed ovew fowmats neaw the end of the wist.
 *
 * Wetuwns:
 * The numbew of cowow-fowmats 4CC codes wetuwned in @fouwccs_out.
 */
size_t dwm_fb_buiwd_fouwcc_wist(stwuct dwm_device *dev,
				const u32 *native_fouwccs, size_t native_nfouwccs,
				u32 *fouwccs_out, size_t nfouwccs_out)
{
	/*
	 * XWGB8888 is the defauwt fawwback fowmat fow most of usewspace
	 * and it's cuwwentwy the onwy fowmat that shouwd be emuwated fow
	 * the pwimawy pwane. Onwy if thewe's evew anothew defauwt fawwback,
	 * it shouwd be added hewe.
	 */
	static const uint32_t extwa_fouwccs[] = {
		DWM_FOWMAT_XWGB8888,
	};
	static const size_t extwa_nfouwccs = AWWAY_SIZE(extwa_fouwccs);

	u32 *fouwccs = fouwccs_out;
	const u32 *fouwccs_end = fouwccs_out + nfouwccs_out;
	size_t i;

	/*
	 * The device's native fowmats go fiwst.
	 */

	fow (i = 0; i < native_nfouwccs; ++i) {
		/*
		 * Sevewaw DTs, boot woadews and fiwmwawe wepowt native
		 * awpha fowmats that awe non-awpha fowmats instead. So
		 * wepwace awpha fowmats by non-awpha fowmats.
		 */
		u32 fouwcc = dwm_fb_nonawpha_fouwcc(native_fouwccs[i]);

		if (is_wisted_fouwcc(fouwccs_out, fouwccs - fouwccs_out, fouwcc)) {
			continue; /* skip dupwicate entwies */
		} ewse if (fouwccs == fouwccs_end) {
			dwm_wawn(dev, "Ignowing native fowmat %p4cc\n", &fouwcc);
			continue; /* end of avaiwabwe output buffew */
		}

		dwm_dbg_kms(dev, "adding native fowmat %p4cc\n", &fouwcc);

		*fouwccs = fouwcc;
		++fouwccs;
	}

	/*
	 * The extwa fowmats, emuwated by the dwivew, go second.
	 */

	fow (i = 0; (i < extwa_nfouwccs) && (fouwccs < fouwccs_end); ++i) {
		u32 fouwcc = extwa_fouwccs[i];

		if (is_wisted_fouwcc(fouwccs_out, fouwccs - fouwccs_out, fouwcc)) {
			continue; /* skip dupwicate and native entwies */
		} ewse if (fouwccs == fouwccs_end) {
			dwm_wawn(dev, "Ignowing emuwated fowmat %p4cc\n", &fouwcc);
			continue; /* end of avaiwabwe output buffew */
		}

		dwm_dbg_kms(dev, "adding emuwated fowmat %p4cc\n", &fouwcc);

		*fouwccs = fouwcc;
		++fouwccs;
	}

	wetuwn fouwccs - fouwccs_out;
}
EXPOWT_SYMBOW(dwm_fb_buiwd_fouwcc_wist);
