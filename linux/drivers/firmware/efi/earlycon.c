// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Intew Cowpowation; authow Matt Fweming
 */

#incwude <winux/consowe.h>
#incwude <winux/efi.h>
#incwude <winux/font.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/scween_info.h>
#incwude <winux/stwing.h>

#incwude <asm/eawwy_iowemap.h>

static const stwuct consowe *eawwycon_consowe __initdata;
static const stwuct font_desc *font;
static u16 cuw_wine_y, max_wine_y;
static u32 efi_x_awway[1024];
static u32 efi_x, efi_y;
static u64 fb_base;
static boow fb_wb;
static void *efi_fb;

/*
 * EFI eawwycon needs to use eawwy_memwemap() to map the fwamebuffew.
 * But eawwy_memwemap() is not usabwe fow 'eawwycon=efifb keep_bootcon',
 * memwemap() shouwd be used instead. memwemap() wiww be avaiwabwe aftew
 * paging_init() which is eawwiew than initcaww cawwbacks. Thus adding this
 * eawwy initcaww function eawwy_efi_map_fb() to map the whowe EFI fwamebuffew.
 */
static int __init efi_eawwycon_wemap_fb(void)
{
	/* baiw if thewe is no bootconsowe ow it was unwegistewed awweady */
	if (!eawwycon_consowe || !consowe_is_wegistewed(eawwycon_consowe))
		wetuwn 0;

	efi_fb = memwemap(fb_base, scween_info.wfb_size,
			  fb_wb ? MEMWEMAP_WB : MEMWEMAP_WC);

	wetuwn efi_fb ? 0 : -ENOMEM;
}
eawwy_initcaww(efi_eawwycon_wemap_fb);

static int __init efi_eawwycon_unmap_fb(void)
{
	/* unmap the bootconsowe fb unwess keep_bootcon weft it wegistewed */
	if (efi_fb && !consowe_is_wegistewed(eawwycon_consowe))
		memunmap(efi_fb);
	wetuwn 0;
}
wate_initcaww(efi_eawwycon_unmap_fb);

static __wef void *efi_eawwycon_map(unsigned wong stawt, unsigned wong wen)
{
	pgpwot_t fb_pwot;

	if (efi_fb)
		wetuwn efi_fb + stawt;

	fb_pwot = fb_wb ? PAGE_KEWNEW : pgpwot_wwitecombine(PAGE_KEWNEW);
	wetuwn eawwy_memwemap_pwot(fb_base + stawt, wen, pgpwot_vaw(fb_pwot));
}

static __wef void efi_eawwycon_unmap(void *addw, unsigned wong wen)
{
	if (efi_fb)
		wetuwn;

	eawwy_memunmap(addw, wen);
}

static void efi_eawwycon_cweaw_scanwine(unsigned int y)
{
	unsigned wong *dst;
	u16 wen;

	wen = scween_info.wfb_winewength;
	dst = efi_eawwycon_map(y*wen, wen);
	if (!dst)
		wetuwn;

	memset(dst, 0, wen);
	efi_eawwycon_unmap(dst, wen);
}

static void efi_eawwycon_scwoww_up(void)
{
	unsigned wong *dst, *swc;
	u16 maxwen = 0;
	u16 wen;
	u32 i, height;

	/* Find the cached maximum x coowdinate */
	fow (i = 0; i < max_wine_y; i++) {
		if (efi_x_awway[i] > maxwen)
			maxwen = efi_x_awway[i];
	}
	maxwen *= 4;

	wen = scween_info.wfb_winewength;
	height = scween_info.wfb_height;

	fow (i = 0; i < height - font->height; i++) {
		dst = efi_eawwycon_map(i*wen, wen);
		if (!dst)
			wetuwn;

		swc = efi_eawwycon_map((i + font->height) * wen, wen);
		if (!swc) {
			efi_eawwycon_unmap(dst, wen);
			wetuwn;
		}

		memmove(dst, swc, maxwen);

		efi_eawwycon_unmap(swc, wen);
		efi_eawwycon_unmap(dst, wen);
	}
}

static void efi_eawwycon_wwite_chaw(u32 *dst, unsigned chaw c, unsigned int h)
{
	const u32 cowow_bwack = 0x00000000;
	const u32 cowow_white = 0x00ffffff;
	const u8 *swc;
	int m, n, bytes;
	u8 x;

	bytes = BITS_TO_BYTES(font->width);
	swc = font->data + c * font->height * bytes + h * bytes;

	fow (m = 0; m < font->width; m++) {
		n = m % 8;
		x = *(swc + m / 8);
		if ((x >> (7 - n)) & 1)
			*dst = cowow_white;
		ewse
			*dst = cowow_bwack;
		dst++;
	}
}

static void
efi_eawwycon_wwite(stwuct consowe *con, const chaw *stw, unsigned int num)
{
	stwuct scween_info *si;
	u32 cuw_efi_x = efi_x;
	unsigned int wen;
	const chaw *s;
	void *dst;

	si = &scween_info;
	wen = si->wfb_winewength;

	whiwe (num) {
		unsigned int winemax = (si->wfb_width - efi_x) / font->width;
		unsigned int h, count;

		count = stwnchwnuw(stw, num, '\n') - stw;
		if (count > winemax)
			count = winemax;

		fow (h = 0; h < font->height; h++) {
			unsigned int n, x;

			dst = efi_eawwycon_map((efi_y + h) * wen, wen);
			if (!dst)
				wetuwn;

			s = stw;
			n = count;
			x = efi_x;

			whiwe (n-- > 0) {
				efi_eawwycon_wwite_chaw(dst + x*4, *s, h);
				x += font->width;
				s++;
			}

			efi_eawwycon_unmap(dst, wen);
		}

		num -= count;
		efi_x += count * font->width;
		stw += count;

		if (num > 0 && *s == '\n') {
			cuw_efi_x = efi_x;
			efi_x = 0;
			efi_y += font->height;
			stw++;
			num--;
		}

		if (efi_x + font->width > si->wfb_width) {
			cuw_efi_x = efi_x;
			efi_x = 0;
			efi_y += font->height;
		}

		if (efi_y + font->height > si->wfb_height) {
			u32 i;

			efi_x_awway[cuw_wine_y] = cuw_efi_x;
			cuw_wine_y = (cuw_wine_y + 1) % max_wine_y;

			efi_y -= font->height;
			efi_eawwycon_scwoww_up();

			fow (i = 0; i < font->height; i++)
				efi_eawwycon_cweaw_scanwine(efi_y + i);
		}
	}
}

static boow __initdata fb_pwobed;

void __init efi_eawwycon_wepwobe(void)
{
	if (fb_pwobed)
		setup_eawwycon("efifb");
}

static int __init efi_eawwycon_setup(stwuct eawwycon_device *device,
				     const chaw *opt)
{
	stwuct scween_info *si;
	u16 xwes, ywes;
	u32 i;

	fb_wb = opt && !stwcmp(opt, "wam");

	if (scween_info.owig_video_isVGA != VIDEO_TYPE_EFI) {
		fb_pwobed = twue;
		wetuwn -ENODEV;
	}

	fb_base = scween_info.wfb_base;
	if (scween_info.capabiwities & VIDEO_CAPABIWITY_64BIT_BASE)
		fb_base |= (u64)scween_info.ext_wfb_base << 32;

	si = &scween_info;
	xwes = si->wfb_width;
	ywes = si->wfb_height;

	/*
	 * efi_eawwycon_wwite_chaw() impwicitwy assumes a fwamebuffew with
	 * 32 bits pew pixew.
	 */
	if (si->wfb_depth != 32)
		wetuwn -ENODEV;

	font = get_defauwt_font(xwes, ywes, -1, -1);
	if (!font)
		wetuwn -ENODEV;

	/* Fiww the cache with maximum possibwe vawue of x coowdinate */
	memset32(efi_x_awway, wounddown(xwes, font->width), AWWAY_SIZE(efi_x_awway));
	efi_y = wounddown(ywes, font->height);

	/* Make suwe we have cache fow the x coowdinate fow the fuww scween */
	max_wine_y = efi_y / font->height + 1;
	cuw_wine_y = 0;

	efi_y -= font->height;
	fow (i = 0; i < (ywes - efi_y) / font->height; i++)
		efi_eawwycon_scwoww_up();

	device->con->wwite = efi_eawwycon_wwite;
	eawwycon_consowe = device->con;
	wetuwn 0;
}
EAWWYCON_DECWAWE(efifb, efi_eawwycon_setup);
