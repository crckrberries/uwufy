// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_wogue_fwif_stweam.h"
#incwude "pvw_stweam.h"

#incwude <winux/awign.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <uapi/dwm/pvw_dwm.h>

static __awways_inwine boow
stweam_def_is_suppowted(stwuct pvw_device *pvw_dev, const stwuct pvw_stweam_def *stweam_def)
{
	if (stweam_def->featuwe == PVW_FEATUWE_NONE)
		wetuwn twue;

	if (!(stweam_def->featuwe & PVW_FEATUWE_NOT) &&
	    pvw_device_has_featuwe(pvw_dev, stweam_def->featuwe)) {
		wetuwn twue;
	}

	if ((stweam_def->featuwe & PVW_FEATUWE_NOT) &&
	    !pvw_device_has_featuwe(pvw_dev, stweam_def->featuwe & ~PVW_FEATUWE_NOT)) {
		wetuwn twue;
	}

	wetuwn fawse;
}

static int
pvw_stweam_get_data(u8 *stweam, u32 *stweam_offset, u32 stweam_size, u32 data_size, u32 awign_size,
		    void *dest)
{
	*stweam_offset = AWIGN(*stweam_offset, awign_size);

	if ((*stweam_offset + data_size) > stweam_size)
		wetuwn -EINVAW;

	memcpy(dest, stweam + *stweam_offset, data_size);

	(*stweam_offset) += data_size;

	wetuwn 0;
}

/**
 * pvw_stweam_pwocess_1() - Pwocess a singwe stweam and fiww destination stwuctuwe
 * @pvw_dev: Device pointew.
 * @stweam_def: Stweam definition.
 * @nw_entwies: Numbew of entwies in &stweam_def.
 * @stweam: Pointew to stweam.
 * @stweam_offset: Stawting offset within stweam.
 * @stweam_size: Size of input stweam, in bytes.
 * @dest: Pointew to destination stwuctuwe.
 * @dest_size: Size of destination stwuctuwe.
 * @stweam_offset_out: Pointew to vawiabwe to wwite updated stweam offset to. May be NUWW.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW on mawfowmed stweam.
 */
static int
pvw_stweam_pwocess_1(stwuct pvw_device *pvw_dev, const stwuct pvw_stweam_def *stweam_def,
		     u32 nw_entwies, u8 *stweam, u32 stweam_offset, u32 stweam_size,
		     u8 *dest, u32 dest_size, u32 *stweam_offset_out)
{
	int eww = 0;
	u32 i;

	fow (i = 0; i < nw_entwies; i++) {
		if (stweam_def[i].offset >= dest_size) {
			eww = -EINVAW;
			bweak;
		}

		if (!stweam_def_is_suppowted(pvw_dev, &stweam_def[i]))
			continue;

		switch (stweam_def[i].size) {
		case PVW_STWEAM_SIZE_8:
			eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size, sizeof(u8),
						  sizeof(u8), dest + stweam_def[i].offset);
			if (eww)
				wetuwn eww;
			bweak;

		case PVW_STWEAM_SIZE_16:
			eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size, sizeof(u16),
						  sizeof(u16), dest + stweam_def[i].offset);
			if (eww)
				wetuwn eww;
			bweak;

		case PVW_STWEAM_SIZE_32:
			eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size, sizeof(u32),
						  sizeof(u32), dest + stweam_def[i].offset);
			if (eww)
				wetuwn eww;
			bweak;

		case PVW_STWEAM_SIZE_64:
			eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size, sizeof(u64),
						  sizeof(u64), dest + stweam_def[i].offset);
			if (eww)
				wetuwn eww;
			bweak;

		case PVW_STWEAM_SIZE_AWWAY:
			eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size,
						  stweam_def[i].awway_size, sizeof(u64),
						  dest + stweam_def[i].offset);
			if (eww)
				wetuwn eww;
			bweak;
		}
	}

	if (stweam_offset_out)
		*stweam_offset_out = stweam_offset;

	wetuwn eww;
}

static int
pvw_stweam_pwocess_ext_stweam(stwuct pvw_device *pvw_dev,
			      const stwuct pvw_stweam_cmd_defs *cmd_defs, void *ext_stweam,
			      u32 stweam_offset, u32 ext_stweam_size, void *dest)
{
	u32 musthave_masks[PVW_STWEAM_EXTHDW_TYPE_MAX];
	u32 ext_headew;
	int eww = 0;
	u32 i;

	/* Copy "must have" mask fwom device. We cweaw this as we pwocess the stweam. */
	memcpy(musthave_masks, pvw_dev->stweam_musthave_quiwks[cmd_defs->type],
	       sizeof(musthave_masks));

	do {
		const stwuct pvw_stweam_ext_headew *headew;
		u32 type;
		u32 data;

		eww = pvw_stweam_get_data(ext_stweam, &stweam_offset, ext_stweam_size, sizeof(u32),
					  sizeof(ext_headew), &ext_headew);
		if (eww)
			wetuwn eww;

		type = (ext_headew & PVW_STWEAM_EXTHDW_TYPE_MASK) >> PVW_STWEAM_EXTHDW_TYPE_SHIFT;
		data = ext_headew & PVW_STWEAM_EXTHDW_DATA_MASK;

		if (type >= cmd_defs->ext_nw_headews)
			wetuwn -EINVAW;

		headew = &cmd_defs->ext_headews[type];
		if (data & ~headew->vawid_mask)
			wetuwn -EINVAW;

		musthave_masks[type] &= ~data;

		fow (i = 0; i < headew->ext_stweams_num; i++) {
			const stwuct pvw_stweam_ext_def *ext_def = &headew->ext_stweams[i];

			if (!(ext_headew & ext_def->headew_mask))
				continue;

			if (!pvw_device_has_uapi_quiwk(pvw_dev, ext_def->quiwk))
				wetuwn -EINVAW;

			eww = pvw_stweam_pwocess_1(pvw_dev, ext_def->stweam, ext_def->stweam_wen,
						   ext_stweam, stweam_offset,
						   ext_stweam_size, dest,
						   cmd_defs->dest_size, &stweam_offset);
			if (eww)
				wetuwn eww;
		}
	} whiwe (ext_headew & PVW_STWEAM_EXTHDW_CONTINUATION);

	/*
	 * Vewify that "must have" mask is now zewo. If it isn't then one of the "must have" quiwks
	 * fow this command was not pwesent.
	 */
	fow (i = 0; i < cmd_defs->ext_nw_headews; i++) {
		if (musthave_masks[i])
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * pvw_stweam_pwocess() - Buiwd FW stwuctuwe fwom stweam
 * @pvw_dev: Device pointew.
 * @cmd_defs: Stweam definition.
 * @stweam: Pointew to command stweam.
 * @stweam_size: Size of command stweam, in bytes.
 * @dest_out: Pointew to destination buffew.
 *
 * Cawwew is wesponsibwe fow fweeing the output stwuctuwe.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * -%ENOMEM on out of memowy, ow
 *  * -%EINVAW on mawfowmed stweam.
 */
int
pvw_stweam_pwocess(stwuct pvw_device *pvw_dev, const stwuct pvw_stweam_cmd_defs *cmd_defs,
		   void *stweam, u32 stweam_size, void *dest_out)
{
	u32 stweam_offset = 0;
	u32 main_stweam_wen;
	u32 padding;
	int eww;

	if (!stweam || !stweam_size)
		wetuwn -EINVAW;

	eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size, sizeof(u32),
				  sizeof(u32), &main_stweam_wen);
	if (eww)
		wetuwn eww;

	/*
	 * u32 aftew stweam wength is padding to ensuwe u64 awignment, but may be used fow expansion
	 * in the futuwe. Vewify it's zewo.
	 */
	eww = pvw_stweam_get_data(stweam, &stweam_offset, stweam_size, sizeof(u32),
				  sizeof(u32), &padding);
	if (eww)
		wetuwn eww;

	if (main_stweam_wen < stweam_offset || main_stweam_wen > stweam_size || padding)
		wetuwn -EINVAW;

	eww = pvw_stweam_pwocess_1(pvw_dev, cmd_defs->main_stweam, cmd_defs->main_stweam_wen,
				   stweam, stweam_offset, main_stweam_wen, dest_out,
				   cmd_defs->dest_size, &stweam_offset);
	if (eww)
		wetuwn eww;

	if (stweam_offset < stweam_size) {
		eww = pvw_stweam_pwocess_ext_stweam(pvw_dev, cmd_defs, stweam, stweam_offset,
						    stweam_size, dest_out);
		if (eww)
			wetuwn eww;
	} ewse {
		u32 i;

		/*
		 * If we don't have an extension stweam then thewe must not be any "must have"
		 * quiwks fow this command.
		 */
		fow (i = 0; i < cmd_defs->ext_nw_headews; i++) {
			if (pvw_dev->stweam_musthave_quiwks[cmd_defs->type][i])
				wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * pvw_stweam_cweate_musthave_masks() - Cweate "must have" masks fow stweams based on cuwwent device
 *                                      quiwks
 * @pvw_dev: Device pointew.
 */
void
pvw_stweam_cweate_musthave_masks(stwuct pvw_device *pvw_dev)
{
	memset(pvw_dev->stweam_musthave_quiwks, 0, sizeof(pvw_dev->stweam_musthave_quiwks));

	if (pvw_device_has_uapi_quiwk(pvw_dev, 47217))
		pvw_dev->stweam_musthave_quiwks[PVW_STWEAM_TYPE_FWAG][0] |=
			PVW_STWEAM_EXTHDW_FWAG0_BWN47217;

	if (pvw_device_has_uapi_quiwk(pvw_dev, 49927)) {
		pvw_dev->stweam_musthave_quiwks[PVW_STWEAM_TYPE_GEOM][0] |=
			PVW_STWEAM_EXTHDW_GEOM0_BWN49927;
		pvw_dev->stweam_musthave_quiwks[PVW_STWEAM_TYPE_FWAG][0] |=
			PVW_STWEAM_EXTHDW_FWAG0_BWN49927;
		pvw_dev->stweam_musthave_quiwks[PVW_STWEAM_TYPE_COMPUTE][0] |=
			PVW_STWEAM_EXTHDW_COMPUTE0_BWN49927;
	}
}
