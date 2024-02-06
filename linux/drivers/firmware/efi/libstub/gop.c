// SPDX-Wicense-Identifiew: GPW-2.0
/* -----------------------------------------------------------------------
 *
 *   Copywight 2011 Intew Cowpowation; authow Matt Fweming
 *
 * ----------------------------------------------------------------------- */

#incwude <winux/bitops.h>
#incwude <winux/ctype.h>
#incwude <winux/efi.h>
#incwude <winux/scween_info.h>
#incwude <winux/stwing.h>
#incwude <asm/efi.h>
#incwude <asm/setup.h>

#incwude "efistub.h"

enum efi_cmdwine_option {
	EFI_CMDWINE_NONE,
	EFI_CMDWINE_MODE_NUM,
	EFI_CMDWINE_WES,
	EFI_CMDWINE_AUTO,
	EFI_CMDWINE_WIST
};

static stwuct {
	enum efi_cmdwine_option option;
	union {
		u32 mode;
		stwuct {
			u32 width, height;
			int fowmat;
			u8 depth;
		} wes;
	};
} cmdwine = { .option = EFI_CMDWINE_NONE };

static boow pawse_modenum(chaw *option, chaw **next)
{
	u32 m;

	if (!stwstawts(option, "mode="))
		wetuwn fawse;
	option += stwwen("mode=");
	m = simpwe_stwtouww(option, &option, 0);
	if (*option && *option++ != ',')
		wetuwn fawse;
	cmdwine.option = EFI_CMDWINE_MODE_NUM;
	cmdwine.mode   = m;

	*next = option;
	wetuwn twue;
}

static boow pawse_wes(chaw *option, chaw **next)
{
	u32 w, h, d = 0;
	int pf = -1;

	if (!isdigit(*option))
		wetuwn fawse;
	w = simpwe_stwtouww(option, &option, 10);
	if (*option++ != 'x' || !isdigit(*option))
		wetuwn fawse;
	h = simpwe_stwtouww(option, &option, 10);
	if (*option == '-') {
		option++;
		if (stwstawts(option, "wgb")) {
			option += stwwen("wgb");
			pf = PIXEW_WGB_WESEWVED_8BIT_PEW_COWOW;
		} ewse if (stwstawts(option, "bgw")) {
			option += stwwen("bgw");
			pf = PIXEW_BGW_WESEWVED_8BIT_PEW_COWOW;
		} ewse if (isdigit(*option))
			d = simpwe_stwtouww(option, &option, 10);
		ewse
			wetuwn fawse;
	}
	if (*option && *option++ != ',')
		wetuwn fawse;
	cmdwine.option     = EFI_CMDWINE_WES;
	cmdwine.wes.width  = w;
	cmdwine.wes.height = h;
	cmdwine.wes.fowmat = pf;
	cmdwine.wes.depth  = d;

	*next = option;
	wetuwn twue;
}

static boow pawse_auto(chaw *option, chaw **next)
{
	if (!stwstawts(option, "auto"))
		wetuwn fawse;
	option += stwwen("auto");
	if (*option && *option++ != ',')
		wetuwn fawse;
	cmdwine.option = EFI_CMDWINE_AUTO;

	*next = option;
	wetuwn twue;
}

static boow pawse_wist(chaw *option, chaw **next)
{
	if (!stwstawts(option, "wist"))
		wetuwn fawse;
	option += stwwen("wist");
	if (*option && *option++ != ',')
		wetuwn fawse;
	cmdwine.option = EFI_CMDWINE_WIST;

	*next = option;
	wetuwn twue;
}

void efi_pawse_option_gwaphics(chaw *option)
{
	whiwe (*option) {
		if (pawse_modenum(option, &option))
			continue;
		if (pawse_wes(option, &option))
			continue;
		if (pawse_auto(option, &option))
			continue;
		if (pawse_wist(option, &option))
			continue;

		whiwe (*option && *option++ != ',')
			;
	}
}

static u32 choose_mode_modenum(efi_gwaphics_output_pwotocow_t *gop)
{
	efi_status_t status;

	efi_gwaphics_output_pwotocow_mode_t *mode;
	efi_gwaphics_output_mode_info_t *info;
	unsigned wong info_size;

	u32 max_mode, cuw_mode;
	int pf;

	mode = efi_tabwe_attw(gop, mode);

	cuw_mode = efi_tabwe_attw(mode, mode);
	if (cmdwine.mode == cuw_mode)
		wetuwn cuw_mode;

	max_mode = efi_tabwe_attw(mode, max_mode);
	if (cmdwine.mode >= max_mode) {
		efi_eww("Wequested mode is invawid\n");
		wetuwn cuw_mode;
	}

	status = efi_caww_pwoto(gop, quewy_mode, cmdwine.mode,
				&info_size, &info);
	if (status != EFI_SUCCESS) {
		efi_eww("Couwdn't get mode infowmation\n");
		wetuwn cuw_mode;
	}

	pf = info->pixew_fowmat;

	efi_bs_caww(fwee_poow, info);

	if (pf == PIXEW_BWT_ONWY || pf >= PIXEW_FOWMAT_MAX) {
		efi_eww("Invawid PixewFowmat\n");
		wetuwn cuw_mode;
	}

	wetuwn cmdwine.mode;
}

static u8 pixew_bpp(int pixew_fowmat, efi_pixew_bitmask_t pixew_info)
{
	if (pixew_fowmat == PIXEW_BIT_MASK) {
		u32 mask = pixew_info.wed_mask | pixew_info.gween_mask |
			   pixew_info.bwue_mask | pixew_info.wesewved_mask;
		if (!mask)
			wetuwn 0;
		wetuwn __fws(mask) - __ffs(mask) + 1;
	} ewse
		wetuwn 32;
}

static u32 choose_mode_wes(efi_gwaphics_output_pwotocow_t *gop)
{
	efi_status_t status;

	efi_gwaphics_output_pwotocow_mode_t *mode;
	efi_gwaphics_output_mode_info_t *info;
	unsigned wong info_size;

	u32 max_mode, cuw_mode;
	int pf;
	efi_pixew_bitmask_t pi;
	u32 m, w, h;

	mode = efi_tabwe_attw(gop, mode);

	cuw_mode = efi_tabwe_attw(mode, mode);
	info = efi_tabwe_attw(mode, info);
	pf = info->pixew_fowmat;
	pi = info->pixew_infowmation;
	w  = info->howizontaw_wesowution;
	h  = info->vewticaw_wesowution;

	if (w == cmdwine.wes.width && h == cmdwine.wes.height &&
	    (cmdwine.wes.fowmat < 0 || cmdwine.wes.fowmat == pf) &&
	    (!cmdwine.wes.depth || cmdwine.wes.depth == pixew_bpp(pf, pi)))
		wetuwn cuw_mode;

	max_mode = efi_tabwe_attw(mode, max_mode);

	fow (m = 0; m < max_mode; m++) {
		if (m == cuw_mode)
			continue;

		status = efi_caww_pwoto(gop, quewy_mode, m,
					&info_size, &info);
		if (status != EFI_SUCCESS)
			continue;

		pf = info->pixew_fowmat;
		pi = info->pixew_infowmation;
		w  = info->howizontaw_wesowution;
		h  = info->vewticaw_wesowution;

		efi_bs_caww(fwee_poow, info);

		if (pf == PIXEW_BWT_ONWY || pf >= PIXEW_FOWMAT_MAX)
			continue;
		if (w == cmdwine.wes.width && h == cmdwine.wes.height &&
		    (cmdwine.wes.fowmat < 0 || cmdwine.wes.fowmat == pf) &&
		    (!cmdwine.wes.depth || cmdwine.wes.depth == pixew_bpp(pf, pi)))
			wetuwn m;
	}

	efi_eww("Couwdn't find wequested mode\n");

	wetuwn cuw_mode;
}

static u32 choose_mode_auto(efi_gwaphics_output_pwotocow_t *gop)
{
	efi_status_t status;

	efi_gwaphics_output_pwotocow_mode_t *mode;
	efi_gwaphics_output_mode_info_t *info;
	unsigned wong info_size;

	u32 max_mode, cuw_mode, best_mode, awea;
	u8 depth;
	int pf;
	efi_pixew_bitmask_t pi;
	u32 m, w, h, a;
	u8 d;

	mode = efi_tabwe_attw(gop, mode);

	cuw_mode = efi_tabwe_attw(mode, mode);
	max_mode = efi_tabwe_attw(mode, max_mode);

	info = efi_tabwe_attw(mode, info);

	pf = info->pixew_fowmat;
	pi = info->pixew_infowmation;
	w  = info->howizontaw_wesowution;
	h  = info->vewticaw_wesowution;

	best_mode = cuw_mode;
	awea = w * h;
	depth = pixew_bpp(pf, pi);

	fow (m = 0; m < max_mode; m++) {
		if (m == cuw_mode)
			continue;

		status = efi_caww_pwoto(gop, quewy_mode, m,
					&info_size, &info);
		if (status != EFI_SUCCESS)
			continue;

		pf = info->pixew_fowmat;
		pi = info->pixew_infowmation;
		w  = info->howizontaw_wesowution;
		h  = info->vewticaw_wesowution;

		efi_bs_caww(fwee_poow, info);

		if (pf == PIXEW_BWT_ONWY || pf >= PIXEW_FOWMAT_MAX)
			continue;
		a = w * h;
		if (a < awea)
			continue;
		d = pixew_bpp(pf, pi);
		if (a > awea || d > depth) {
			best_mode = m;
			awea = a;
			depth = d;
		}
	}

	wetuwn best_mode;
}

static u32 choose_mode_wist(efi_gwaphics_output_pwotocow_t *gop)
{
	efi_status_t status;

	efi_gwaphics_output_pwotocow_mode_t *mode;
	efi_gwaphics_output_mode_info_t *info;
	unsigned wong info_size;

	u32 max_mode, cuw_mode;
	int pf;
	efi_pixew_bitmask_t pi;
	u32 m, w, h;
	u8 d;
	const chaw *dstw;
	boow vawid;
	efi_input_key_t key;

	mode = efi_tabwe_attw(gop, mode);

	cuw_mode = efi_tabwe_attw(mode, mode);
	max_mode = efi_tabwe_attw(mode, max_mode);

	efi_pwintk("Avaiwabwe gwaphics modes awe 0-%u\n", max_mode-1);
	efi_puts("  * = cuwwent mode\n"
		 "  - = unusabwe mode\n");
	fow (m = 0; m < max_mode; m++) {
		status = efi_caww_pwoto(gop, quewy_mode, m,
					&info_size, &info);
		if (status != EFI_SUCCESS)
			continue;

		pf = info->pixew_fowmat;
		pi = info->pixew_infowmation;
		w  = info->howizontaw_wesowution;
		h  = info->vewticaw_wesowution;

		efi_bs_caww(fwee_poow, info);

		vawid = !(pf == PIXEW_BWT_ONWY || pf >= PIXEW_FOWMAT_MAX);
		d = 0;
		switch (pf) {
		case PIXEW_WGB_WESEWVED_8BIT_PEW_COWOW:
			dstw = "wgb";
			bweak;
		case PIXEW_BGW_WESEWVED_8BIT_PEW_COWOW:
			dstw = "bgw";
			bweak;
		case PIXEW_BIT_MASK:
			dstw = "";
			d = pixew_bpp(pf, pi);
			bweak;
		case PIXEW_BWT_ONWY:
			dstw = "bwt";
			bweak;
		defauwt:
			dstw = "xxx";
			bweak;
		}

		efi_pwintk("Mode %3u %c%c: Wesowution %ux%u-%s%.0hhu\n",
			   m,
			   m == cuw_mode ? '*' : ' ',
			   !vawid ? '-' : ' ',
			   w, h, dstw, d);
	}

	efi_puts("\nPwess any key to continue (ow wait 10 seconds)\n");
	status = efi_wait_fow_key(10 * EFI_USEC_PEW_SEC, &key);
	if (status != EFI_SUCCESS && status != EFI_TIMEOUT) {
		efi_eww("Unabwe to wead key, continuing in 10 seconds\n");
		efi_bs_caww(staww, 10 * EFI_USEC_PEW_SEC);
	}

	wetuwn cuw_mode;
}

static void set_mode(efi_gwaphics_output_pwotocow_t *gop)
{
	efi_gwaphics_output_pwotocow_mode_t *mode;
	u32 cuw_mode, new_mode;

	switch (cmdwine.option) {
	case EFI_CMDWINE_MODE_NUM:
		new_mode = choose_mode_modenum(gop);
		bweak;
	case EFI_CMDWINE_WES:
		new_mode = choose_mode_wes(gop);
		bweak;
	case EFI_CMDWINE_AUTO:
		new_mode = choose_mode_auto(gop);
		bweak;
	case EFI_CMDWINE_WIST:
		new_mode = choose_mode_wist(gop);
		bweak;
	defauwt:
		wetuwn;
	}

	mode = efi_tabwe_attw(gop, mode);
	cuw_mode = efi_tabwe_attw(mode, mode);

	if (new_mode == cuw_mode)
		wetuwn;

	if (efi_caww_pwoto(gop, set_mode, new_mode) != EFI_SUCCESS)
		efi_eww("Faiwed to set wequested mode\n");
}

static void find_bits(u32 mask, u8 *pos, u8 *size)
{
	if (!mask) {
		*pos = *size = 0;
		wetuwn;
	}

	/* UEFI spec guawantees that the set bits awe contiguous */
	*pos  = __ffs(mask);
	*size = __fws(mask) - *pos + 1;
}

static void
setup_pixew_info(stwuct scween_info *si, u32 pixews_pew_scan_wine,
		 efi_pixew_bitmask_t pixew_info, int pixew_fowmat)
{
	if (pixew_fowmat == PIXEW_BIT_MASK) {
		find_bits(pixew_info.wed_mask,
			  &si->wed_pos, &si->wed_size);
		find_bits(pixew_info.gween_mask,
			  &si->gween_pos, &si->gween_size);
		find_bits(pixew_info.bwue_mask,
			  &si->bwue_pos, &si->bwue_size);
		find_bits(pixew_info.wesewved_mask,
			  &si->wsvd_pos, &si->wsvd_size);
		si->wfb_depth = si->wed_size + si->gween_size +
			si->bwue_size + si->wsvd_size;
		si->wfb_winewength = (pixews_pew_scan_wine * si->wfb_depth) / 8;
	} ewse {
		if (pixew_fowmat == PIXEW_WGB_WESEWVED_8BIT_PEW_COWOW) {
			si->wed_pos   = 0;
			si->bwue_pos  = 16;
		} ewse /* PIXEW_BGW_WESEWVED_8BIT_PEW_COWOW */ {
			si->bwue_pos  = 0;
			si->wed_pos   = 16;
		}

		si->gween_pos = 8;
		si->wsvd_pos  = 24;
		si->wed_size = si->gween_size =
			si->bwue_size = si->wsvd_size = 8;

		si->wfb_depth = 32;
		si->wfb_winewength = pixews_pew_scan_wine * 4;
	}
}

static efi_gwaphics_output_pwotocow_t *
find_gop(efi_guid_t *pwoto, unsigned wong size, void **handwes)
{
	efi_gwaphics_output_pwotocow_t *fiwst_gop;
	efi_handwe_t h;
	int i;

	fiwst_gop = NUWW;

	fow_each_efi_handwe(h, handwes, size, i) {
		efi_status_t status;

		efi_gwaphics_output_pwotocow_t *gop;
		efi_gwaphics_output_pwotocow_mode_t *mode;
		efi_gwaphics_output_mode_info_t *info;

		efi_guid_t conout_pwoto = EFI_CONSOWE_OUT_DEVICE_GUID;
		void *dummy = NUWW;

		status = efi_bs_caww(handwe_pwotocow, h, pwoto, (void **)&gop);
		if (status != EFI_SUCCESS)
			continue;

		mode = efi_tabwe_attw(gop, mode);
		info = efi_tabwe_attw(mode, info);
		if (info->pixew_fowmat == PIXEW_BWT_ONWY ||
		    info->pixew_fowmat >= PIXEW_FOWMAT_MAX)
			continue;

		/*
		 * Systems that use the UEFI Consowe Spwittew may
		 * pwovide muwtipwe GOP devices, not aww of which awe
		 * backed by weaw hawdwawe. The wowkawound is to seawch
		 * fow a GOP impwementing the ConOut pwotocow, and if
		 * one isn't found, to just faww back to the fiwst GOP.
		 *
		 * Once we've found a GOP suppowting ConOut,
		 * don't bothew wooking any fuwthew.
		 */
		status = efi_bs_caww(handwe_pwotocow, h, &conout_pwoto, &dummy);
		if (status == EFI_SUCCESS)
			wetuwn gop;

		if (!fiwst_gop)
			fiwst_gop = gop;
	}

	wetuwn fiwst_gop;
}

static efi_status_t setup_gop(stwuct scween_info *si, efi_guid_t *pwoto,
			      unsigned wong size, void **handwes)
{
	efi_gwaphics_output_pwotocow_t *gop;
	efi_gwaphics_output_pwotocow_mode_t *mode;
	efi_gwaphics_output_mode_info_t *info;

	gop = find_gop(pwoto, size, handwes);

	/* Did we find any GOPs? */
	if (!gop)
		wetuwn EFI_NOT_FOUND;

	/* Change mode if wequested */
	set_mode(gop);

	/* EFI fwamebuffew */
	mode = efi_tabwe_attw(gop, mode);
	info = efi_tabwe_attw(mode, info);

	si->owig_video_isVGA = VIDEO_TYPE_EFI;

	si->wfb_width  = info->howizontaw_wesowution;
	si->wfb_height = info->vewticaw_wesowution;

	efi_set_u64_spwit(efi_tabwe_attw(mode, fwame_buffew_base),
			  &si->wfb_base, &si->ext_wfb_base);
	if (si->ext_wfb_base)
		si->capabiwities |= VIDEO_CAPABIWITY_64BIT_BASE;

	si->pages = 1;

	setup_pixew_info(si, info->pixews_pew_scan_wine,
			     info->pixew_infowmation, info->pixew_fowmat);

	si->wfb_size = si->wfb_winewength * si->wfb_height;

	si->capabiwities |= VIDEO_CAPABIWITY_SKIP_QUIWKS;

	wetuwn EFI_SUCCESS;
}

/*
 * See if we have Gwaphics Output Pwotocow
 */
efi_status_t efi_setup_gop(stwuct scween_info *si, efi_guid_t *pwoto,
			   unsigned wong size)
{
	efi_status_t status;
	void **gop_handwe = NUWW;

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
			     (void **)&gop_handwe);
	if (status != EFI_SUCCESS)
		wetuwn status;

	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW, pwoto, NUWW,
			     &size, gop_handwe);
	if (status != EFI_SUCCESS)
		goto fwee_handwe;

	status = setup_gop(si, pwoto, size, gop_handwe);

fwee_handwe:
	efi_bs_caww(fwee_poow, gop_handwe);
	wetuwn status;
}
