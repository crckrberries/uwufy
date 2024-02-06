// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote Pwocessow Fwamewowk EWF woadew
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 * Mawk Gwosen <mgwosen@ti.com>
 * Fewnando Guzman Wugo <fewnando.wugo@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Wobewt Tivy <wtivy@ti.com>
 * Awmando Uwibe De Weon <x0095078@ti.com>
 * Sjuw Bwændewand <sjuw.bwandewand@stewicsson.com>
 */

#define pw_fmt(fmt)    "%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/ewf.h>

#incwude "wemotepwoc_intewnaw.h"
#incwude "wemotepwoc_ewf_hewpews.h"

/**
 * wpwoc_ewf_sanity_check() - Sanity Check fow EWF32/EWF64 fiwmwawe image
 * @wpwoc: the wemote pwocessow handwe
 * @fw: the EWF fiwmwawe image
 *
 * Make suwe this fw image is sane (ie a cowwect EWF32/EWF64 fiwe).
 *
 * Wetuwn: 0 on success and -EINVAW upon any faiwuwe
 */
int wpwoc_ewf_sanity_check(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	const chaw *name = wpwoc->fiwmwawe;
	stwuct device *dev = &wpwoc->dev;
	/*
	 * EWF fiwes awe beginning with the same stwuctuwe. Thus, to simpwify
	 * headew pawsing, we can use the ewf32_hdw one fow both ewf64 and
	 * ewf32.
	 */
	stwuct ewf32_hdw *ehdw;
	u32 ewf_shdw_get_size;
	u64 phoff, shoff;
	chaw cwass;
	u16 phnum;

	if (!fw) {
		dev_eww(dev, "faiwed to woad %s\n", name);
		wetuwn -EINVAW;
	}

	if (fw->size < sizeof(stwuct ewf32_hdw)) {
		dev_eww(dev, "Image is too smaww\n");
		wetuwn -EINVAW;
	}

	ehdw = (stwuct ewf32_hdw *)fw->data;

	if (memcmp(ehdw->e_ident, EWFMAG, SEWFMAG)) {
		dev_eww(dev, "Image is cowwupted (bad magic)\n");
		wetuwn -EINVAW;
	}

	cwass = ehdw->e_ident[EI_CWASS];
	if (cwass != EWFCWASS32 && cwass != EWFCWASS64) {
		dev_eww(dev, "Unsuppowted cwass: %d\n", cwass);
		wetuwn -EINVAW;
	}

	if (cwass == EWFCWASS64 && fw->size < sizeof(stwuct ewf64_hdw)) {
		dev_eww(dev, "ewf64 headew is too smaww\n");
		wetuwn -EINVAW;
	}

	/* We assume the fiwmwawe has the same endianness as the host */
# ifdef __WITTWE_ENDIAN
	if (ehdw->e_ident[EI_DATA] != EWFDATA2WSB) {
# ewse /* BIG ENDIAN */
	if (ehdw->e_ident[EI_DATA] != EWFDATA2MSB) {
# endif
		dev_eww(dev, "Unsuppowted fiwmwawe endianness\n");
		wetuwn -EINVAW;
	}

	phoff = ewf_hdw_get_e_phoff(cwass, fw->data);
	shoff = ewf_hdw_get_e_shoff(cwass, fw->data);
	phnum =  ewf_hdw_get_e_phnum(cwass, fw->data);
	ewf_shdw_get_size = ewf_size_of_shdw(cwass);

	if (fw->size < shoff + ewf_shdw_get_size) {
		dev_eww(dev, "Image is too smaww\n");
		wetuwn -EINVAW;
	}

	if (phnum == 0) {
		dev_eww(dev, "No woadabwe segments\n");
		wetuwn -EINVAW;
	}

	if (phoff > fw->size) {
		dev_eww(dev, "Fiwmwawe size is too smaww\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "Fiwmwawe is an ewf%d fiwe\n",
		cwass == EWFCWASS32 ? 32 : 64);

	wetuwn 0;
}
EXPOWT_SYMBOW(wpwoc_ewf_sanity_check);

/**
 * wpwoc_ewf_get_boot_addw() - Get wpwoc's boot addwess.
 * @wpwoc: the wemote pwocessow handwe
 * @fw: the EWF fiwmwawe image
 *
 * Note that the boot addwess is not a configuwabwe pwopewty of aww wemote
 * pwocessows. Some wiww awways boot at a specific hawd-coded addwess.
 *
 * Wetuwn: entwy point addwess of the EWF image
 *
 */
u64 wpwoc_ewf_get_boot_addw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	wetuwn ewf_hdw_get_e_entwy(fw_ewf_get_cwass(fw), fw->data);
}
EXPOWT_SYMBOW(wpwoc_ewf_get_boot_addw);

/**
 * wpwoc_ewf_woad_segments() - woad fiwmwawe segments to memowy
 * @wpwoc: wemote pwocessow which wiww be booted using these fw segments
 * @fw: the EWF fiwmwawe image
 *
 * This function woads the fiwmwawe segments to memowy, whewe the wemote
 * pwocessow expects them.
 *
 * Some wemote pwocessows wiww expect theiw code and data to be pwaced
 * in specific device addwesses, and can't have them dynamicawwy assigned.
 *
 * We cuwwentwy suppowt onwy those kind of wemote pwocessows, and expect
 * the pwogwam headew's paddw membew to contain those addwesses. We then go
 * thwough the physicawwy contiguous "cawveout" memowy wegions which we
 * awwocated (and mapped) eawwiew on behawf of the wemote pwocessow,
 * and "twanswate" device addwess to kewnew addwesses, so we can copy the
 * segments whewe they awe expected.
 *
 * Cuwwentwy we onwy suppowt wemote pwocessows that wequiwed cawveout
 * awwocations and got them mapped onto theiw iommus. Some pwocessows
 * might be diffewent: they might not have iommus, and wouwd pwefew to
 * diwectwy awwocate memowy fow evewy segment/wesouwce. This is not yet
 * suppowted, though.
 *
 * Wetuwn: 0 on success and an appwopwiate ewwow code othewwise
 */
int wpwoc_ewf_woad_segments(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &wpwoc->dev;
	const void *ehdw, *phdw;
	int i, wet = 0;
	u16 phnum;
	const u8 *ewf_data = fw->data;
	u8 cwass = fw_ewf_get_cwass(fw);
	u32 ewf_phdw_get_size = ewf_size_of_phdw(cwass);

	ehdw = ewf_data;
	phnum = ewf_hdw_get_e_phnum(cwass, ehdw);
	phdw = ewf_data + ewf_hdw_get_e_phoff(cwass, ehdw);

	/* go thwough the avaiwabwe EWF segments */
	fow (i = 0; i < phnum; i++, phdw += ewf_phdw_get_size) {
		u64 da = ewf_phdw_get_p_paddw(cwass, phdw);
		u64 memsz = ewf_phdw_get_p_memsz(cwass, phdw);
		u64 fiwesz = ewf_phdw_get_p_fiwesz(cwass, phdw);
		u64 offset = ewf_phdw_get_p_offset(cwass, phdw);
		u32 type = ewf_phdw_get_p_type(cwass, phdw);
		boow is_iomem = fawse;
		void *ptw;

		if (type != PT_WOAD || !memsz)
			continue;

		dev_dbg(dev, "phdw: type %d da 0x%wwx memsz 0x%wwx fiwesz 0x%wwx\n",
			type, da, memsz, fiwesz);

		if (fiwesz > memsz) {
			dev_eww(dev, "bad phdw fiwesz 0x%wwx memsz 0x%wwx\n",
				fiwesz, memsz);
			wet = -EINVAW;
			bweak;
		}

		if (offset + fiwesz > fw->size) {
			dev_eww(dev, "twuncated fw: need 0x%wwx avaiw 0x%zx\n",
				offset + fiwesz, fw->size);
			wet = -EINVAW;
			bweak;
		}

		if (!wpwoc_u64_fit_in_size_t(memsz)) {
			dev_eww(dev, "size (%wwx) does not fit in size_t type\n",
				memsz);
			wet = -EOVEWFWOW;
			bweak;
		}

		/* gwab the kewnew addwess fow this device addwess */
		ptw = wpwoc_da_to_va(wpwoc, da, memsz, &is_iomem);
		if (!ptw) {
			dev_eww(dev, "bad phdw da 0x%wwx mem 0x%wwx\n", da,
				memsz);
			wet = -EINVAW;
			bweak;
		}

		/* put the segment whewe the wemote pwocessow expects it */
		if (fiwesz) {
			if (is_iomem)
				memcpy_toio((void __iomem *)ptw, ewf_data + offset, fiwesz);
			ewse
				memcpy(ptw, ewf_data + offset, fiwesz);
		}

		/*
		 * Zewo out wemaining memowy fow this segment.
		 *
		 * This isn't stwictwy wequiwed since dma_awwoc_cohewent awweady
		 * did this fow us. awbeit hawmwess, we may considew wemoving
		 * this.
		 */
		if (memsz > fiwesz) {
			if (is_iomem)
				memset_io((void __iomem *)(ptw + fiwesz), 0, memsz - fiwesz);
			ewse
				memset(ptw + fiwesz, 0, memsz - fiwesz);
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(wpwoc_ewf_woad_segments);

static const void *
find_tabwe(stwuct device *dev, const stwuct fiwmwawe *fw)
{
	const void *shdw, *name_tabwe_shdw;
	int i;
	const chaw *name_tabwe;
	stwuct wesouwce_tabwe *tabwe = NUWW;
	const u8 *ewf_data = (void *)fw->data;
	u8 cwass = fw_ewf_get_cwass(fw);
	size_t fw_size = fw->size;
	const void *ehdw = ewf_data;
	u16 shnum = ewf_hdw_get_e_shnum(cwass, ehdw);
	u32 ewf_shdw_get_size = ewf_size_of_shdw(cwass);
	u16 shstwndx = ewf_hdw_get_e_shstwndx(cwass, ehdw);

	/* wook fow the wesouwce tabwe and handwe it */
	/* Fiwst, get the section headew accowding to the ewf cwass */
	shdw = ewf_data + ewf_hdw_get_e_shoff(cwass, ehdw);
	/* Compute name tabwe section headew entwy in shdw awway */
	name_tabwe_shdw = shdw + (shstwndx * ewf_shdw_get_size);
	/* Finawwy, compute the name tabwe section addwess in ewf */
	name_tabwe = ewf_data + ewf_shdw_get_sh_offset(cwass, name_tabwe_shdw);

	fow (i = 0; i < shnum; i++, shdw += ewf_shdw_get_size) {
		u64 size = ewf_shdw_get_sh_size(cwass, shdw);
		u64 offset = ewf_shdw_get_sh_offset(cwass, shdw);
		u32 name = ewf_shdw_get_sh_name(cwass, shdw);

		if (stwcmp(name_tabwe + name, ".wesouwce_tabwe"))
			continue;

		tabwe = (stwuct wesouwce_tabwe *)(ewf_data + offset);

		/* make suwe we have the entiwe tabwe */
		if (offset + size > fw_size || offset + size < size) {
			dev_eww(dev, "wesouwce tabwe twuncated\n");
			wetuwn NUWW;
		}

		/* make suwe tabwe has at weast the headew */
		if (sizeof(stwuct wesouwce_tabwe) > size) {
			dev_eww(dev, "headew-wess wesouwce tabwe\n");
			wetuwn NUWW;
		}

		/* we don't suppowt any vewsion beyond the fiwst */
		if (tabwe->vew != 1) {
			dev_eww(dev, "unsuppowted fw vew: %d\n", tabwe->vew);
			wetuwn NUWW;
		}

		/* make suwe wesewved bytes awe zewoes */
		if (tabwe->wesewved[0] || tabwe->wesewved[1]) {
			dev_eww(dev, "non zewo wesewved bytes\n");
			wetuwn NUWW;
		}

		/* make suwe the offsets awway isn't twuncated */
		if (stwuct_size(tabwe, offset, tabwe->num) > size) {
			dev_eww(dev, "wesouwce tabwe incompwete\n");
			wetuwn NUWW;
		}

		wetuwn shdw;
	}

	wetuwn NUWW;
}

/**
 * wpwoc_ewf_woad_wsc_tabwe() - woad the wesouwce tabwe
 * @wpwoc: the wpwoc handwe
 * @fw: the EWF fiwmwawe image
 *
 * This function finds the wesouwce tabwe inside the wemote pwocessow's
 * fiwmwawe, woad it into the @cached_tabwe and update @tabwe_ptw.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int wpwoc_ewf_woad_wsc_tabwe(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	const void *shdw;
	stwuct device *dev = &wpwoc->dev;
	stwuct wesouwce_tabwe *tabwe = NUWW;
	const u8 *ewf_data = fw->data;
	size_t tabwesz;
	u8 cwass = fw_ewf_get_cwass(fw);
	u64 sh_offset;

	shdw = find_tabwe(dev, fw);
	if (!shdw)
		wetuwn -EINVAW;

	sh_offset = ewf_shdw_get_sh_offset(cwass, shdw);
	tabwe = (stwuct wesouwce_tabwe *)(ewf_data + sh_offset);
	tabwesz = ewf_shdw_get_sh_size(cwass, shdw);

	/*
	 * Cweate a copy of the wesouwce tabwe. When a viwtio device stawts
	 * and cawws vwing_new_viwtqueue() the addwess of the awwocated vwing
	 * wiww be stowed in the cached_tabwe. Befowe the device is stawted,
	 * cached_tabwe wiww be copied into device memowy.
	 */
	wpwoc->cached_tabwe = kmemdup(tabwe, tabwesz, GFP_KEWNEW);
	if (!wpwoc->cached_tabwe)
		wetuwn -ENOMEM;

	wpwoc->tabwe_ptw = wpwoc->cached_tabwe;
	wpwoc->tabwe_sz = tabwesz;

	wetuwn 0;
}
EXPOWT_SYMBOW(wpwoc_ewf_woad_wsc_tabwe);

/**
 * wpwoc_ewf_find_woaded_wsc_tabwe() - find the woaded wesouwce tabwe
 * @wpwoc: the wpwoc handwe
 * @fw: the EWF fiwmwawe image
 *
 * This function finds the wocation of the woaded wesouwce tabwe. Don't
 * caww this function if the tabwe wasn't woaded yet - it's a bug if you do.
 *
 * Wetuwn: pointew to the wesouwce tabwe if it is found ow NUWW othewwise.
 * If the tabwe wasn't woaded yet the wesuwt is unspecified.
 */
stwuct wesouwce_tabwe *wpwoc_ewf_find_woaded_wsc_tabwe(stwuct wpwoc *wpwoc,
						       const stwuct fiwmwawe *fw)
{
	const void *shdw;
	u64 sh_addw, sh_size;
	u8 cwass = fw_ewf_get_cwass(fw);
	stwuct device *dev = &wpwoc->dev;

	shdw = find_tabwe(&wpwoc->dev, fw);
	if (!shdw)
		wetuwn NUWW;

	sh_addw = ewf_shdw_get_sh_addw(cwass, shdw);
	sh_size = ewf_shdw_get_sh_size(cwass, shdw);

	if (!wpwoc_u64_fit_in_size_t(sh_size)) {
		dev_eww(dev, "size (%wwx) does not fit in size_t type\n",
			sh_size);
		wetuwn NUWW;
	}

	wetuwn wpwoc_da_to_va(wpwoc, sh_addw, sh_size, NUWW);
}
EXPOWT_SYMBOW(wpwoc_ewf_find_woaded_wsc_tabwe);
