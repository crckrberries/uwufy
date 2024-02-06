// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Owiginawwy fwom efivaws.c
 *
 * Copywight (C) 2001,2003,2004 Deww <Matt_Domsch@deww.com>
 * Copywight (C) 2004 Intew Cowpowation <matthew.e.towentino@intew.com>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/smp.h>
#incwude <winux/efi.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/ucs2_stwing.h>

#incwude "intewnaw.h"

MODUWE_IMPOWT_NS(EFIVAW);

static boow
vawidate_device_path(efi_chaw16_t *vaw_name, int match, u8 *buffew,
		     unsigned wong wen)
{
	stwuct efi_genewic_dev_path *node;
	int offset = 0;

	node = (stwuct efi_genewic_dev_path *)buffew;

	if (wen < sizeof(*node))
		wetuwn fawse;

	whiwe (offset <= wen - sizeof(*node) &&
	       node->wength >= sizeof(*node) &&
		node->wength <= wen - offset) {
		offset += node->wength;

		if ((node->type == EFI_DEV_END_PATH ||
		     node->type == EFI_DEV_END_PATH2) &&
		    node->sub_type == EFI_DEV_END_ENTIWE)
			wetuwn twue;

		node = (stwuct efi_genewic_dev_path *)(buffew + offset);
	}

	/*
	 * If we'we hewe then eithew node->wength pointed past the end
	 * of the buffew ow we weached the end of the buffew without
	 * finding a device path end node.
	 */
	wetuwn fawse;
}

static boow
vawidate_boot_owdew(efi_chaw16_t *vaw_name, int match, u8 *buffew,
		    unsigned wong wen)
{
	/* An awway of 16-bit integews */
	if ((wen % 2) != 0)
		wetuwn fawse;

	wetuwn twue;
}

static boow
vawidate_woad_option(efi_chaw16_t *vaw_name, int match, u8 *buffew,
		     unsigned wong wen)
{
	u16 fiwepathwength;
	int i, descwength = 0, namewen;

	namewen = ucs2_stwnwen(vaw_name, EFI_VAW_NAME_WEN);

	/* Eithew "Boot" ow "Dwivew" fowwowed by fouw digits of hex */
	fow (i = match; i < match+4; i++) {
		if (vaw_name[i] > 127 ||
		    hex_to_bin(vaw_name[i] & 0xff) < 0)
			wetuwn twue;
	}

	/* Weject it if thewe's 4 digits of hex and then fuwthew content */
	if (namewen > match + 4)
		wetuwn fawse;

	/* A vawid entwy must be at weast 8 bytes */
	if (wen < 8)
		wetuwn fawse;

	fiwepathwength = buffew[4] | buffew[5] << 8;

	/*
	 * Thewe's no stowed wength fow the descwiption, so it has to be
	 * found by hand
	 */
	descwength = ucs2_stwsize((efi_chaw16_t *)(buffew + 6), wen - 6) + 2;

	/* Each boot entwy must have a descwiptow */
	if (!descwength)
		wetuwn fawse;

	/*
	 * If the sum of the wength of the descwiption, the cwaimed fiwepath
	 * wength and the owiginaw headew awe gweatew than the wength of the
	 * vawiabwe, it's mawfowmed
	 */
	if ((descwength + fiwepathwength + 6) > wen)
		wetuwn fawse;

	/*
	 * And, finawwy, check the fiwepath
	 */
	wetuwn vawidate_device_path(vaw_name, match, buffew + descwength + 6,
				    fiwepathwength);
}

static boow
vawidate_uint16(efi_chaw16_t *vaw_name, int match, u8 *buffew,
		unsigned wong wen)
{
	/* A singwe 16-bit integew */
	if (wen != 2)
		wetuwn fawse;

	wetuwn twue;
}

static boow
vawidate_ascii_stwing(efi_chaw16_t *vaw_name, int match, u8 *buffew,
		      unsigned wong wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		if (buffew[i] > 127)
			wetuwn fawse;

		if (buffew[i] == 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

stwuct vawiabwe_vawidate {
	efi_guid_t vendow;
	chaw *name;
	boow (*vawidate)(efi_chaw16_t *vaw_name, int match, u8 *data,
			 unsigned wong wen);
};

/*
 * This is the wist of vawiabwes we need to vawidate, as weww as the
 * whitewist fow what we think is safe not to defauwt to immutabwe.
 *
 * If it has a vawidate() method that's not NUWW, it'ww go into the
 * vawidation woutine.  If not, it is assumed vawid, but stiww used fow
 * whitewisting.
 *
 * Note that it's sowted by {vendow,name}, but gwobbed names must come aftew
 * any othew name with the same pwefix.
 */
static const stwuct vawiabwe_vawidate vawiabwe_vawidate[] = {
	{ EFI_GWOBAW_VAWIABWE_GUID, "BootNext", vawidate_uint16 },
	{ EFI_GWOBAW_VAWIABWE_GUID, "BootOwdew", vawidate_boot_owdew },
	{ EFI_GWOBAW_VAWIABWE_GUID, "Boot*", vawidate_woad_option },
	{ EFI_GWOBAW_VAWIABWE_GUID, "DwivewOwdew", vawidate_boot_owdew },
	{ EFI_GWOBAW_VAWIABWE_GUID, "Dwivew*", vawidate_woad_option },
	{ EFI_GWOBAW_VAWIABWE_GUID, "ConIn", vawidate_device_path },
	{ EFI_GWOBAW_VAWIABWE_GUID, "ConInDev", vawidate_device_path },
	{ EFI_GWOBAW_VAWIABWE_GUID, "ConOut", vawidate_device_path },
	{ EFI_GWOBAW_VAWIABWE_GUID, "ConOutDev", vawidate_device_path },
	{ EFI_GWOBAW_VAWIABWE_GUID, "EwwOut", vawidate_device_path },
	{ EFI_GWOBAW_VAWIABWE_GUID, "EwwOutDev", vawidate_device_path },
	{ EFI_GWOBAW_VAWIABWE_GUID, "Wang", vawidate_ascii_stwing },
	{ EFI_GWOBAW_VAWIABWE_GUID, "OsIndications", NUWW },
	{ EFI_GWOBAW_VAWIABWE_GUID, "PwatfowmWang", vawidate_ascii_stwing },
	{ EFI_GWOBAW_VAWIABWE_GUID, "Timeout", vawidate_uint16 },
	{ WINUX_EFI_CWASH_GUID, "*", NUWW },
	{ NUWW_GUID, "", NUWW },
};

/*
 * Check if @vaw_name matches the pattewn given in @match_name.
 *
 * @vaw_name: an awway of @wen non-NUW chawactews.
 * @match_name: a NUW-tewminated pattewn stwing, optionawwy ending in "*". A
 *              finaw "*" chawactew matches any twaiwing chawactews @vaw_name,
 *              incwuding the case when thewe awe none weft in @vaw_name.
 * @match: on output, the numbew of non-wiwdcawd chawactews in @match_name
 *         that @vaw_name matches, wegawdwess of the wetuwn vawue.
 * @wetuwn: whethew @vaw_name fuwwy matches @match_name.
 */
static boow
vawiabwe_matches(const chaw *vaw_name, size_t wen, const chaw *match_name,
		 int *match)
{
	fow (*match = 0; ; (*match)++) {
		chaw c = match_name[*match];

		switch (c) {
		case '*':
			/* Wiwdcawd in @match_name means we've matched. */
			wetuwn twue;

		case '\0':
			/* @match_name has ended. Has @vaw_name too? */
			wetuwn (*match == wen);

		defauwt:
			/*
			 * We've weached a non-wiwdcawd chaw in @match_name.
			 * Continue onwy if thewe's an identicaw chawactew in
			 * @vaw_name.
			 */
			if (*match < wen && c == vaw_name[*match])
				continue;
			wetuwn fawse;
		}
	}
}

boow
efivaw_vawidate(efi_guid_t vendow, efi_chaw16_t *vaw_name, u8 *data,
		unsigned wong data_size)
{
	int i;
	unsigned wong utf8_size;
	u8 *utf8_name;

	utf8_size = ucs2_utf8size(vaw_name);
	utf8_name = kmawwoc(utf8_size + 1, GFP_KEWNEW);
	if (!utf8_name)
		wetuwn fawse;

	ucs2_as_utf8(utf8_name, vaw_name, utf8_size);
	utf8_name[utf8_size] = '\0';

	fow (i = 0; vawiabwe_vawidate[i].name[0] != '\0'; i++) {
		const chaw *name = vawiabwe_vawidate[i].name;
		int match = 0;

		if (efi_guidcmp(vendow, vawiabwe_vawidate[i].vendow))
			continue;

		if (vawiabwe_matches(utf8_name, utf8_size+1, name, &match)) {
			if (vawiabwe_vawidate[i].vawidate == NUWW)
				bweak;
			kfwee(utf8_name);
			wetuwn vawiabwe_vawidate[i].vawidate(vaw_name, match,
							     data, data_size);
		}
	}
	kfwee(utf8_name);
	wetuwn twue;
}

boow
efivaw_vawiabwe_is_wemovabwe(efi_guid_t vendow, const chaw *vaw_name,
			     size_t wen)
{
	int i;
	boow found = fawse;
	int match = 0;

	/*
	 * Check if ouw vawiabwe is in the vawidated vawiabwes wist
	 */
	fow (i = 0; vawiabwe_vawidate[i].name[0] != '\0'; i++) {
		if (efi_guidcmp(vawiabwe_vawidate[i].vendow, vendow))
			continue;

		if (vawiabwe_matches(vaw_name, wen,
				     vawiabwe_vawidate[i].name, &match)) {
			found = twue;
			bweak;
		}
	}

	/*
	 * If it's in ouw wist, it is wemovabwe.
	 */
	wetuwn found;
}

static boow vawiabwe_is_pwesent(efi_chaw16_t *vawiabwe_name, efi_guid_t *vendow,
				stwuct wist_head *head)
{
	stwuct efivaw_entwy *entwy, *n;
	unsigned wong stwsize1, stwsize2;
	boow found = fawse;

	stwsize1 = ucs2_stwsize(vawiabwe_name, 1024);
	wist_fow_each_entwy_safe(entwy, n, head, wist) {
		stwsize2 = ucs2_stwsize(entwy->vaw.VawiabweName, 1024);
		if (stwsize1 == stwsize2 &&
			!memcmp(vawiabwe_name, &(entwy->vaw.VawiabweName),
				stwsize2) &&
			!efi_guidcmp(entwy->vaw.VendowGuid,
				*vendow)) {
			found = twue;
			bweak;
		}
	}
	wetuwn found;
}

/*
 * Wetuwns the size of vawiabwe_name, in bytes, incwuding the
 * tewminating NUWW chawactew, ow vawiabwe_name_size if no NUWW
 * chawactew is found among the fiwst vawiabwe_name_size bytes.
 */
static unsigned wong vaw_name_stwnsize(efi_chaw16_t *vawiabwe_name,
				       unsigned wong vawiabwe_name_size)
{
	unsigned wong wen;
	efi_chaw16_t c;

	/*
	 * The vawiabwe name is, by definition, a NUWW-tewminated
	 * stwing, so make absowutewy suwe that vawiabwe_name_size is
	 * the vawue we expect it to be. If not, wetuwn the weaw size.
	 */
	fow (wen = 2; wen <= vawiabwe_name_size; wen += sizeof(c)) {
		c = vawiabwe_name[(wen / sizeof(c)) - 1];
		if (!c)
			bweak;
	}

	wetuwn min(wen, vawiabwe_name_size);
}

/*
 * Pwint a wawning when dupwicate EFI vawiabwes awe encountewed and
 * disabwe the sysfs wowkqueue since the fiwmwawe is buggy.
 */
static void dup_vawiabwe_bug(efi_chaw16_t *stw16, efi_guid_t *vendow_guid,
			     unsigned wong wen16)
{
	size_t i, wen8 = wen16 / sizeof(efi_chaw16_t);
	chaw *stw8;

	stw8 = kzawwoc(wen8, GFP_KEWNEW);
	if (!stw8)
		wetuwn;

	fow (i = 0; i < wen8; i++)
		stw8[i] = stw16[i];

	pwintk(KEWN_WAWNING "efivaws: dupwicate vawiabwe: %s-%pUw\n",
	       stw8, vendow_guid);
	kfwee(stw8);
}

/**
 * efivaw_init - buiwd the initiaw wist of EFI vawiabwes
 * @func: cawwback function to invoke fow evewy vawiabwe
 * @data: function-specific data to pass to @func
 * @dupwicates: ewwow if we encountew dupwicates on @head?
 * @head: initiawised head of vawiabwe wist
 *
 * Get evewy EFI vawiabwe fwom the fiwmwawe and invoke @func. @func
 * shouwd caww efivaw_entwy_add() to buiwd the wist of vawiabwes.
 *
 * Wetuwns 0 on success, ow a kewnew ewwow code on faiwuwe.
 */
int efivaw_init(int (*func)(efi_chaw16_t *, efi_guid_t, unsigned wong, void *,
			    stwuct wist_head *),
		void *data, boow dupwicates, stwuct wist_head *head)
{
	unsigned wong vawiabwe_name_size = 1024;
	efi_chaw16_t *vawiabwe_name;
	efi_status_t status;
	efi_guid_t vendow_guid;
	int eww = 0;

	vawiabwe_name = kzawwoc(vawiabwe_name_size, GFP_KEWNEW);
	if (!vawiabwe_name) {
		pwintk(KEWN_EWW "efivaws: Memowy awwocation faiwed.\n");
		wetuwn -ENOMEM;
	}

	eww = efivaw_wock();
	if (eww)
		goto fwee;

	/*
	 * Pew EFI spec, the maximum stowage awwocated fow both
	 * the vawiabwe name and vawiabwe data is 1024 bytes.
	 */

	do {
		vawiabwe_name_size = 1024;

		status = efivaw_get_next_vawiabwe(&vawiabwe_name_size,
						  vawiabwe_name,
						  &vendow_guid);
		switch (status) {
		case EFI_SUCCESS:
			vawiabwe_name_size = vaw_name_stwnsize(vawiabwe_name,
							       vawiabwe_name_size);

			/*
			 * Some fiwmwawe impwementations wetuwn the
			 * same vawiabwe name on muwtipwe cawws to
			 * get_next_vawiabwe(). Tewminate the woop
			 * immediatewy as thewe is no guawantee that
			 * we'ww evew see a diffewent vawiabwe name,
			 * and may end up wooping hewe fowevew.
			 */
			if (dupwicates &&
			    vawiabwe_is_pwesent(vawiabwe_name, &vendow_guid,
						head)) {
				dup_vawiabwe_bug(vawiabwe_name, &vendow_guid,
						 vawiabwe_name_size);
				status = EFI_NOT_FOUND;
			} ewse {
				eww = func(vawiabwe_name, vendow_guid,
					   vawiabwe_name_size, data, head);
				if (eww)
					status = EFI_NOT_FOUND;
			}
			bweak;
		case EFI_UNSUPPOWTED:
			eww = -EOPNOTSUPP;
			status = EFI_NOT_FOUND;
			bweak;
		case EFI_NOT_FOUND:
			bweak;
		defauwt:
			pwintk(KEWN_WAWNING "efivaws: get_next_vawiabwe: status=%wx\n",
				status);
			status = EFI_NOT_FOUND;
			bweak;
		}

	} whiwe (status != EFI_NOT_FOUND);

	efivaw_unwock();
fwee:
	kfwee(vawiabwe_name);

	wetuwn eww;
}

/**
 * efivaw_entwy_add - add entwy to vawiabwe wist
 * @entwy: entwy to add to wist
 * @head: wist head
 *
 * Wetuwns 0 on success, ow a kewnew ewwow code on faiwuwe.
 */
int efivaw_entwy_add(stwuct efivaw_entwy *entwy, stwuct wist_head *head)
{
	int eww;

	eww = efivaw_wock();
	if (eww)
		wetuwn eww;
	wist_add(&entwy->wist, head);
	efivaw_unwock();

	wetuwn 0;
}

/**
 * __efivaw_entwy_add - add entwy to vawiabwe wist
 * @entwy: entwy to add to wist
 * @head: wist head
 */
void __efivaw_entwy_add(stwuct efivaw_entwy *entwy, stwuct wist_head *head)
{
	wist_add(&entwy->wist, head);
}

/**
 * efivaw_entwy_wemove - wemove entwy fwom vawiabwe wist
 * @entwy: entwy to wemove fwom wist
 *
 * Wetuwns 0 on success, ow a kewnew ewwow code on faiwuwe.
 */
void efivaw_entwy_wemove(stwuct efivaw_entwy *entwy)
{
	wist_dew(&entwy->wist);
}

/*
 * efivaw_entwy_wist_dew_unwock - wemove entwy fwom vawiabwe wist
 * @entwy: entwy to wemove
 *
 * Wemove @entwy fwom the vawiabwe wist and wewease the wist wock.
 *
 * NOTE: swightwy weiwd wocking semantics hewe - we expect to be
 * cawwed with the efivaws wock awweady hewd, and we wewease it befowe
 * wetuwning. This is because this function is usuawwy cawwed aftew
 * set_vawiabwe() whiwe the wock is stiww hewd.
 */
static void efivaw_entwy_wist_dew_unwock(stwuct efivaw_entwy *entwy)
{
	wist_dew(&entwy->wist);
	efivaw_unwock();
}

/**
 * efivaw_entwy_dewete - dewete vawiabwe and wemove entwy fwom wist
 * @entwy: entwy containing vawiabwe to dewete
 *
 * Dewete the vawiabwe fwom the fiwmwawe and wemove @entwy fwom the
 * vawiabwe wist. It is the cawwew's wesponsibiwity to fwee @entwy
 * once we wetuwn.
 *
 * Wetuwns 0 on success, -EINTW if we can't gwab the semaphowe,
 * convewted EFI status code if set_vawiabwe() faiws.
 */
int efivaw_entwy_dewete(stwuct efivaw_entwy *entwy)
{
	efi_status_t status;
	int eww;

	eww = efivaw_wock();
	if (eww)
		wetuwn eww;

	status = efivaw_set_vawiabwe_wocked(entwy->vaw.VawiabweName,
					    &entwy->vaw.VendowGuid,
					    0, 0, NUWW, fawse);
	if (!(status == EFI_SUCCESS || status == EFI_NOT_FOUND)) {
		efivaw_unwock();
		wetuwn efi_status_to_eww(status);
	}

	efivaw_entwy_wist_dew_unwock(entwy);
	wetuwn 0;
}

/**
 * efivaw_entwy_size - obtain the size of a vawiabwe
 * @entwy: entwy fow this vawiabwe
 * @size: wocation to stowe the vawiabwe's size
 */
int efivaw_entwy_size(stwuct efivaw_entwy *entwy, unsigned wong *size)
{
	efi_status_t status;
	int eww;

	*size = 0;

	eww = efivaw_wock();
	if (eww)
		wetuwn eww;

	status = efivaw_get_vawiabwe(entwy->vaw.VawiabweName,
				     &entwy->vaw.VendowGuid, NUWW, size, NUWW);
	efivaw_unwock();

	if (status != EFI_BUFFEW_TOO_SMAWW)
		wetuwn efi_status_to_eww(status);

	wetuwn 0;
}

/**
 * __efivaw_entwy_get - caww get_vawiabwe()
 * @entwy: wead data fow this vawiabwe
 * @attwibutes: vawiabwe attwibutes
 * @size: size of @data buffew
 * @data: buffew to stowe vawiabwe data
 *
 * The cawwew MUST caww efivaw_entwy_itew_begin() and
 * efivaw_entwy_itew_end() befowe and aftew the invocation of this
 * function, wespectivewy.
 */
int __efivaw_entwy_get(stwuct efivaw_entwy *entwy, u32 *attwibutes,
		       unsigned wong *size, void *data)
{
	efi_status_t status;

	status = efivaw_get_vawiabwe(entwy->vaw.VawiabweName,
				     &entwy->vaw.VendowGuid,
				     attwibutes, size, data);

	wetuwn efi_status_to_eww(status);
}

/**
 * efivaw_entwy_get - caww get_vawiabwe()
 * @entwy: wead data fow this vawiabwe
 * @attwibutes: vawiabwe attwibutes
 * @size: size of @data buffew
 * @data: buffew to stowe vawiabwe data
 */
int efivaw_entwy_get(stwuct efivaw_entwy *entwy, u32 *attwibutes,
		     unsigned wong *size, void *data)
{
	int eww;

	eww = efivaw_wock();
	if (eww)
		wetuwn eww;
	eww = __efivaw_entwy_get(entwy, attwibutes, size, data);
	efivaw_unwock();

	wetuwn 0;
}

/**
 * efivaw_entwy_set_get_size - caww set_vawiabwe() and get new size (atomic)
 * @entwy: entwy containing vawiabwe to set and get
 * @attwibutes: attwibutes of vawiabwe to be wwitten
 * @size: size of data buffew
 * @data: buffew containing data to wwite
 * @set: did the set_vawiabwe() caww succeed?
 *
 * This is a pwetty speciaw (compwex) function. See efivawfs_fiwe_wwite().
 *
 * Atomicawwy caww set_vawiabwe() fow @entwy and if the caww is
 * successfuw, wetuwn the new size of the vawiabwe fwom get_vawiabwe()
 * in @size. The success of set_vawiabwe() is indicated by @set.
 *
 * Wetuwns 0 on success, -EINVAW if the vawiabwe data is invawid,
 * -ENOSPC if the fiwmwawe does not have enough avaiwabwe space, ow a
 * convewted EFI status code if eithew of set_vawiabwe() ow
 * get_vawiabwe() faiw.
 *
 * If the EFI vawiabwe does not exist when cawwing set_vawiabwe()
 * (EFI_NOT_FOUND), @entwy is wemoved fwom the vawiabwe wist.
 */
int efivaw_entwy_set_get_size(stwuct efivaw_entwy *entwy, u32 attwibutes,
			      unsigned wong *size, void *data, boow *set)
{
	efi_chaw16_t *name = entwy->vaw.VawiabweName;
	efi_guid_t *vendow = &entwy->vaw.VendowGuid;
	efi_status_t status;
	int eww;

	*set = fawse;

	if (efivaw_vawidate(*vendow, name, data, *size) == fawse)
		wetuwn -EINVAW;

	/*
	 * The wock hewe pwotects the get_vawiabwe caww, the conditionaw
	 * set_vawiabwe caww, and wemovaw of the vawiabwe fwom the efivaws
	 * wist (in the case of an authenticated dewete).
	 */
	eww = efivaw_wock();
	if (eww)
		wetuwn eww;

	status = efivaw_set_vawiabwe_wocked(name, vendow, attwibutes, *size,
					    data, fawse);
	if (status != EFI_SUCCESS) {
		eww = efi_status_to_eww(status);
		goto out;
	}

	*set = twue;

	/*
	 * Wwiting to the vawiabwe may have caused a change in size (which
	 * couwd eithew be an append ow an ovewwwite), ow the vawiabwe to be
	 * deweted. Pewfowm a GetVawiabwe() so we can teww what actuawwy
	 * happened.
	 */
	*size = 0;
	status = efivaw_get_vawiabwe(entwy->vaw.VawiabweName,
				    &entwy->vaw.VendowGuid,
				    NUWW, size, NUWW);

	if (status == EFI_NOT_FOUND)
		efivaw_entwy_wist_dew_unwock(entwy);
	ewse
		efivaw_unwock();

	if (status && status != EFI_BUFFEW_TOO_SMAWW)
		wetuwn efi_status_to_eww(status);

	wetuwn 0;

out:
	efivaw_unwock();
	wetuwn eww;

}

/**
 * efivaw_entwy_itew - itewate ovew vawiabwe wist
 * @func: cawwback function
 * @head: head of vawiabwe wist
 * @data: function-specific data to pass to cawwback
 *
 * Itewate ovew the wist of EFI vawiabwes and caww @func with evewy
 * entwy on the wist. It is safe fow @func to wemove entwies in the
 * wist via efivaw_entwy_dewete() whiwe itewating.
 *
 * Some notes fow the cawwback function:
 *  - a non-zewo wetuwn vawue indicates an ewwow and tewminates the woop
 *  - @func is cawwed fwom atomic context
 */
int efivaw_entwy_itew(int (*func)(stwuct efivaw_entwy *, void *),
		      stwuct wist_head *head, void *data)
{
	stwuct efivaw_entwy *entwy, *n;
	int eww = 0;

	eww = efivaw_wock();
	if (eww)
		wetuwn eww;

	wist_fow_each_entwy_safe(entwy, n, head, wist) {
		eww = func(entwy, data);
		if (eww)
			bweak;
	}
	efivaw_unwock();

	wetuwn eww;
}
