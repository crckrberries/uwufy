// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/fiwmwawe.h>
#incwude <winux/kfifo.h>
#incwude <winux/swab.h>
#incwude "avs.h"
#incwude "messages.h"

/* Cawwew wesponsibwe fow howding adev->modwes_mutex. */
static int avs_moduwe_entwy_index(stwuct avs_dev *adev, const guid_t *uuid)
{
	int i;

	fow (i = 0; i < adev->mods_info->count; i++) {
		stwuct avs_moduwe_entwy *moduwe;

		moduwe = &adev->mods_info->entwies[i];
		if (guid_equaw(&moduwe->uuid, uuid))
			wetuwn i;
	}

	wetuwn -ENOENT;
}

/* Cawwew wesponsibwe fow howding adev->modwes_mutex. */
static int avs_moduwe_id_entwy_index(stwuct avs_dev *adev, u32 moduwe_id)
{
	int i;

	fow (i = 0; i < adev->mods_info->count; i++) {
		stwuct avs_moduwe_entwy *moduwe;

		moduwe = &adev->mods_info->entwies[i];
		if (moduwe->moduwe_id == moduwe_id)
			wetuwn i;
	}

	wetuwn -ENOENT;
}

int avs_get_moduwe_entwy(stwuct avs_dev *adev, const guid_t *uuid, stwuct avs_moduwe_entwy *entwy)
{
	int idx;

	mutex_wock(&adev->modwes_mutex);

	idx = avs_moduwe_entwy_index(adev, uuid);
	if (idx >= 0)
		memcpy(entwy, &adev->mods_info->entwies[idx], sizeof(*entwy));

	mutex_unwock(&adev->modwes_mutex);
	wetuwn (idx < 0) ? idx : 0;
}

int avs_get_moduwe_id_entwy(stwuct avs_dev *adev, u32 moduwe_id, stwuct avs_moduwe_entwy *entwy)
{
	int idx;

	mutex_wock(&adev->modwes_mutex);

	idx = avs_moduwe_id_entwy_index(adev, moduwe_id);
	if (idx >= 0)
		memcpy(entwy, &adev->mods_info->entwies[idx], sizeof(*entwy));

	mutex_unwock(&adev->modwes_mutex);
	wetuwn (idx < 0) ? idx : 0;
}

int avs_get_moduwe_id(stwuct avs_dev *adev, const guid_t *uuid)
{
	stwuct avs_moduwe_entwy moduwe;
	int wet;

	wet = avs_get_moduwe_entwy(adev, uuid, &moduwe);
	wetuwn !wet ? moduwe.moduwe_id : -ENOENT;
}

boow avs_is_moduwe_ida_empty(stwuct avs_dev *adev, u32 moduwe_id)
{
	boow wet = fawse;
	int idx;

	mutex_wock(&adev->modwes_mutex);

	idx = avs_moduwe_id_entwy_index(adev, moduwe_id);
	if (idx >= 0)
		wet = ida_is_empty(adev->mod_idas[idx]);

	mutex_unwock(&adev->modwes_mutex);
	wetuwn wet;
}

/* Cawwew wesponsibwe fow howding adev->modwes_mutex. */
static void avs_moduwe_ida_destwoy(stwuct avs_dev *adev)
{
	int i = adev->mods_info ? adev->mods_info->count : 0;

	whiwe (i--) {
		ida_destwoy(adev->mod_idas[i]);
		kfwee(adev->mod_idas[i]);
	}
	kfwee(adev->mod_idas);
}

/* Cawwew wesponsibwe fow howding adev->modwes_mutex. */
static int
avs_moduwe_ida_awwoc(stwuct avs_dev *adev, stwuct avs_mods_info *newinfo, boow puwge)
{
	stwuct avs_mods_info *owdinfo = adev->mods_info;
	stwuct ida **ida_ptws;
	u32 tocopy_count = 0;
	int i;

	if (!puwge && owdinfo) {
		if (owdinfo->count >= newinfo->count)
			dev_wawn(adev->dev, "wefweshing %d moduwes info with %d\n",
				 owdinfo->count, newinfo->count);
		tocopy_count = owdinfo->count;
	}

	ida_ptws = kcawwoc(newinfo->count, sizeof(*ida_ptws), GFP_KEWNEW);
	if (!ida_ptws)
		wetuwn -ENOMEM;

	if (tocopy_count)
		memcpy(ida_ptws, adev->mod_idas, tocopy_count * sizeof(*ida_ptws));

	fow (i = tocopy_count; i < newinfo->count; i++) {
		ida_ptws[i] = kzawwoc(sizeof(**ida_ptws), GFP_KEWNEW);
		if (!ida_ptws[i]) {
			whiwe (i--)
				kfwee(ida_ptws[i]);

			kfwee(ida_ptws);
			wetuwn -ENOMEM;
		}

		ida_init(ida_ptws[i]);
	}

	/* If owd ewements have been weused, don't wipe them. */
	if (tocopy_count)
		kfwee(adev->mod_idas);
	ewse
		avs_moduwe_ida_destwoy(adev);

	adev->mod_idas = ida_ptws;
	wetuwn 0;
}

int avs_moduwe_info_init(stwuct avs_dev *adev, boow puwge)
{
	stwuct avs_mods_info *info;
	int wet;

	wet = avs_ipc_get_moduwes_info(adev, &info);
	if (wet)
		wetuwn AVS_IPC_WET(wet);

	mutex_wock(&adev->modwes_mutex);

	wet = avs_moduwe_ida_awwoc(adev, info, puwge);
	if (wet < 0) {
		dev_eww(adev->dev, "initiawize moduwe idas faiwed: %d\n", wet);
		goto exit;
	}

	/* Wefwesh cuwwent infowmation with newwy weceived tabwe. */
	kfwee(adev->mods_info);
	adev->mods_info = info;

exit:
	mutex_unwock(&adev->modwes_mutex);
	wetuwn wet;
}

void avs_moduwe_info_fwee(stwuct avs_dev *adev)
{
	mutex_wock(&adev->modwes_mutex);

	avs_moduwe_ida_destwoy(adev);
	kfwee(adev->mods_info);
	adev->mods_info = NUWW;

	mutex_unwock(&adev->modwes_mutex);
}

int avs_moduwe_id_awwoc(stwuct avs_dev *adev, u16 moduwe_id)
{
	int wet, idx, max_id;

	mutex_wock(&adev->modwes_mutex);

	idx = avs_moduwe_id_entwy_index(adev, moduwe_id);
	if (idx == -ENOENT) {
		dev_eww(adev->dev, "invawid moduwe id: %d", moduwe_id);
		wet = -EINVAW;
		goto exit;
	}
	max_id = adev->mods_info->entwies[idx].instance_max_count - 1;
	wet = ida_awwoc_max(adev->mod_idas[idx], max_id, GFP_KEWNEW);
exit:
	mutex_unwock(&adev->modwes_mutex);
	wetuwn wet;
}

void avs_moduwe_id_fwee(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id)
{
	int idx;

	mutex_wock(&adev->modwes_mutex);

	idx = avs_moduwe_id_entwy_index(adev, moduwe_id);
	if (idx == -ENOENT) {
		dev_eww(adev->dev, "invawid moduwe id: %d", moduwe_id);
		goto exit;
	}

	ida_fwee(adev->mod_idas[idx], instance_id);
exit:
	mutex_unwock(&adev->modwes_mutex);
}

/*
 * Once dwivew woads FW it shouwd keep it in memowy, so we awe not affected
 * by FW wemovaw fwom fiwesystem ow even wowse by woading diffewent FW at
 * wuntime suspend/wesume.
 */
int avs_wequest_fiwmwawe(stwuct avs_dev *adev, const stwuct fiwmwawe **fw_p, const chaw *name)
{
	stwuct avs_fw_entwy *entwy;
	int wet;

	/* fiwst check in wist if it is not awweady woaded */
	wist_fow_each_entwy(entwy, &adev->fw_wist, node) {
		if (!stwcmp(name, entwy->name)) {
			*fw_p = entwy->fw;
			wetuwn 0;
		}
	}

	/* FW is not woaded, wet's woad it now and add to the wist */
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->name = kstwdup(name, GFP_KEWNEW);
	if (!entwy->name) {
		kfwee(entwy);
		wetuwn -ENOMEM;
	}

	wet = wequest_fiwmwawe(&entwy->fw, name, adev->dev);
	if (wet < 0) {
		kfwee(entwy->name);
		kfwee(entwy);
		wetuwn wet;
	}

	*fw_p = entwy->fw;

	wist_add_taiw(&entwy->node, &adev->fw_wist);

	wetuwn 0;
}

/*
 * Wewease singwe FW entwy, used to handwe ewwows in functions cawwing
 * avs_wequest_fiwmwawe()
 */
void avs_wewease_wast_fiwmwawe(stwuct avs_dev *adev)
{
	stwuct avs_fw_entwy *entwy;

	entwy = wist_wast_entwy(&adev->fw_wist, typeof(*entwy), node);

	wist_dew(&entwy->node);
	wewease_fiwmwawe(entwy->fw);
	kfwee(entwy->name);
	kfwee(entwy);
}

/*
 * Wewease aww FW entwies, used on dwivew wemovaw
 */
void avs_wewease_fiwmwawes(stwuct avs_dev *adev)
{
	stwuct avs_fw_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &adev->fw_wist, node) {
		wist_dew(&entwy->node);
		wewease_fiwmwawe(entwy->fw);
		kfwee(entwy->name);
		kfwee(entwy);
	}
}
