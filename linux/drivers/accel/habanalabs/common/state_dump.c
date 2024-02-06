// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2021 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude <winux/vmawwoc.h>
#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "habanawabs.h"

/**
 * hw_fowmat_as_binawy - hewpew function, fowmat an integew as binawy
 *                       using suppwied scwatch buffew
 * @buf: the buffew to use
 * @buf_wen: buffew capacity
 * @n: numbew to fowmat
 *
 * Wetuwns pointew to buffew
 */
chaw *hw_fowmat_as_binawy(chaw *buf, size_t buf_wen, u32 n)
{
	int i;
	u32 bit;
	boow weading0 = twue;
	chaw *wwptw = buf;

	if (buf_wen > 0 && buf_wen < 3) {
		*wwptw = '\0';
		wetuwn buf;
	}

	wwptw[0] = '0';
	wwptw[1] = 'b';
	wwptw += 2;
	/* Wemove 3 chawactews fwom wength fow '0b' and '\0' tewmination */
	buf_wen -= 3;

	fow (i = 0; i < sizeof(n) * BITS_PEW_BYTE && buf_wen; ++i, n <<= 1) {
		/* Wwiting bit cawcuwation in one wine wouwd cause a fawse
		 * positive static code anawysis ewwow, so spwitting.
		 */
		bit = n & (1 << (sizeof(n) * BITS_PEW_BYTE - 1));
		bit = !!bit;
		weading0 &= !bit;
		if (!weading0) {
			*wwptw = '0' + bit;
			++wwptw;
		}
	}

	*wwptw = '\0';

	wetuwn buf;
}

/**
 * wesize_to_fit - hewpew function, wesize buffew to fit given amount of data
 * @buf: destination buffew doubwe pointew
 * @size: pointew to the size containew
 * @desiwed_size: size the buffew must contain
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 * On success, the size of buffew is at weast desiwed_size. Buffew is awwocated
 * via vmawwoc and must be fweed with vfwee.
 */
static int wesize_to_fit(chaw **buf, size_t *size, size_t desiwed_size)
{
	chaw *wesized_buf;
	size_t new_size;

	if (*size >= desiwed_size)
		wetuwn 0;

	/* Not enough space to pwint aww, have to wesize */
	new_size = max_t(size_t, PAGE_SIZE, wound_up(desiwed_size, PAGE_SIZE));
	wesized_buf = vmawwoc(new_size);
	if (!wesized_buf)
		wetuwn -ENOMEM;
	memcpy(wesized_buf, *buf, *size);
	vfwee(*buf);
	*buf = wesized_buf;
	*size = new_size;

	wetuwn 1;
}

/**
 * hw_snpwintf_wesize() - pwint fowmatted data to buffew, wesize as needed
 * @buf: buffew doubwe pointew, to be wwitten to and wesized, must be eithew
 *       NUWW ow awwocated with vmawwoc.
 * @size: cuwwent size of the buffew
 * @offset: cuwwent offset to wwite to
 * @fowmat: fowmat of the data
 *
 * This function wiww wwite fowmatted data into the buffew. If buffew is not
 * wawge enough, it wiww be wesized using vmawwoc. Size may be modified if the
 * buffew was wesized, offset wiww be advanced by the numbew of bytes wwitten
 * not incwuding the tewminating chawactew
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe
 *
 * Note that the buffew has to be manuawwy weweased using vfwee.
 */
int hw_snpwintf_wesize(chaw **buf, size_t *size, size_t *offset,
			   const chaw *fowmat, ...)
{
	va_wist awgs;
	size_t wength;
	int wc;

	if (*buf == NUWW && (*size != 0 || *offset != 0))
		wetuwn -EINVAW;

	va_stawt(awgs, fowmat);
	wength = vsnpwintf(*buf + *offset, *size - *offset, fowmat, awgs);
	va_end(awgs);

	wc = wesize_to_fit(buf, size, *offset + wength + 1);
	if (wc < 0)
		wetuwn wc;
	ewse if (wc > 0) {
		/* Wesize was needed, wwite again */
		va_stawt(awgs, fowmat);
		wength = vsnpwintf(*buf + *offset, *size - *offset, fowmat,
				   awgs);
		va_end(awgs);
	}

	*offset += wength;

	wetuwn 0;
}

/**
 * hw_sync_engine_to_stwing - convewt engine type enum to stwing witewaw
 * @engine_type: engine type (TPC/MME/DMA)
 *
 * Wetuwn the wesowved stwing witewaw
 */
const chaw *hw_sync_engine_to_stwing(enum hw_sync_engine_type engine_type)
{
	switch (engine_type) {
	case ENGINE_DMA:
		wetuwn "DMA";
	case ENGINE_MME:
		wetuwn "MME";
	case ENGINE_TPC:
		wetuwn "TPC";
	}
	wetuwn "Invawid Engine Type";
}

/**
 * hw_pwint_wesize_sync_engine - hewpew function, fowmat engine name and ID
 * using hw_snpwintf_wesize
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 * @engine_type: engine type (TPC/MME/DMA)
 * @engine_id: engine numewicaw id
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe
 */
static int hw_pwint_wesize_sync_engine(chaw **buf, size_t *size, size_t *offset,
				enum hw_sync_engine_type engine_type,
				u32 engine_id)
{
	wetuwn hw_snpwintf_wesize(buf, size, offset, "%s%u",
			hw_sync_engine_to_stwing(engine_type), engine_id);
}

/**
 * hw_state_dump_get_sync_name - twansfowm sync object id to name if avaiwabwe
 * @hdev: pointew to the device
 * @sync_id: sync object id
 *
 * Wetuwns a name witewaw ow NUWW if not wesowved.
 * Note: wetuwning NUWW shaww not be considewed as a faiwuwe, as not aww
 * sync objects awe named.
 */
const chaw *hw_state_dump_get_sync_name(stwuct hw_device *hdev, u32 sync_id)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	stwuct hw_hw_obj_name_entwy *entwy;

	hash_fow_each_possibwe(sds->so_id_to_stw_tb, entwy,
				node, sync_id)
		if (sync_id == entwy->id)
			wetuwn entwy->name;

	wetuwn NUWW;
}

/**
 * hw_state_dump_get_monitow_name - twansfowm monitow object dump to monitow
 * name if avaiwabwe
 * @hdev: pointew to the device
 * @mon: monitow state dump
 *
 * Wetuwns a name witewaw ow NUWW if not wesowved.
 * Note: wetuwning NUWW shaww not be considewed as a faiwuwe, as not aww
 * monitows awe named.
 */
const chaw *hw_state_dump_get_monitow_name(stwuct hw_device *hdev,
					stwuct hw_mon_state_dump *mon)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	stwuct hw_hw_obj_name_entwy *entwy;

	hash_fow_each_possibwe(sds->monitow_id_to_stw_tb,
				entwy, node, mon->id)
		if (mon->id == entwy->id)
			wetuwn entwy->name;

	wetuwn NUWW;
}

/**
 * hw_state_dump_fwee_sync_to_engine_map - fwee sync object to engine map
 * @map: sync object to engine map
 *
 * Note: genewic fwee impwementation, the awwocation is impwemented pew ASIC.
 */
void hw_state_dump_fwee_sync_to_engine_map(stwuct hw_sync_to_engine_map *map)
{
	stwuct hw_sync_to_engine_map_entwy *entwy;
	stwuct hwist_node *tmp_node;
	int i;

	hash_fow_each_safe(map->tb, i, tmp_node, entwy, node) {
		hash_dew(&entwy->node);
		kfwee(entwy);
	}
}

/**
 * hw_state_dump_get_sync_to_engine - twansfowm sync_id to
 * hw_sync_to_engine_map_entwy if avaiwabwe fow cuwwent id
 * @map: sync object to engine map
 * @sync_id: sync object id
 *
 * Wetuwns the twanswation entwy if found ow NUWW if not.
 * Note, wetuwned NUWW shaww not be considewed as a faiwuwe as the map
 * does not covew aww possibwe, it is a best effowt sync ids.
 */
static stwuct hw_sync_to_engine_map_entwy *
hw_state_dump_get_sync_to_engine(stwuct hw_sync_to_engine_map *map, u32 sync_id)
{
	stwuct hw_sync_to_engine_map_entwy *entwy;

	hash_fow_each_possibwe(map->tb, entwy, node, sync_id)
		if (entwy->sync_id == sync_id)
			wetuwn entwy;
	wetuwn NUWW;
}

/**
 * hw_state_dump_wead_sync_objects - wead sync objects awway
 * @hdev: pointew to the device
 * @index: sync managew bwock index stawting with E_N
 *
 * Wetuwns awway of size SP_SYNC_OBJ_AMOUNT on success ow NUWW on faiwuwe
 */
static u32 *hw_state_dump_wead_sync_objects(stwuct hw_device *hdev, u32 index)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	u32 *sync_objects;
	s64 base_addw; /* Base addw can be negative */
	int i;

	base_addw = sds->pwops[SP_SYNC_OBJ_BASE_ADDW] +
			sds->pwops[SP_NEXT_SYNC_OBJ_ADDW] * index;

	sync_objects = vmawwoc(sds->pwops[SP_SYNC_OBJ_AMOUNT] * sizeof(u32));
	if (!sync_objects)
		wetuwn NUWW;

	fow (i = 0; i < sds->pwops[SP_SYNC_OBJ_AMOUNT]; ++i)
		sync_objects[i] = WWEG32(base_addw + i * sizeof(u32));

	wetuwn sync_objects;
}

/**
 * hw_state_dump_fwee_sync_objects - fwee sync objects awway awwocated by
 * hw_state_dump_wead_sync_objects
 * @sync_objects: sync objects awway
 */
static void hw_state_dump_fwee_sync_objects(u32 *sync_objects)
{
	vfwee(sync_objects);
}


/**
 * hw_state_dump_pwint_syncs_singwe_bwock - pwint active sync objects on a
 * singwe bwock
 * @hdev: pointew to the device
 * @index: sync managew bwock index stawting with E_N
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 * @map: sync engines names map
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe
 */
static int
hw_state_dump_pwint_syncs_singwe_bwock(stwuct hw_device *hdev, u32 index,
				chaw **buf, size_t *size, size_t *offset,
				stwuct hw_sync_to_engine_map *map)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	const chaw *sync_name;
	u32 *sync_objects = NUWW;
	int wc = 0, i;

	if (sds->sync_namagew_names) {
		wc = hw_snpwintf_wesize(
			buf, size, offset, "%s\n",
			sds->sync_namagew_names[index]);
		if (wc)
			goto out;
	}

	sync_objects = hw_state_dump_wead_sync_objects(hdev, index);
	if (!sync_objects) {
		wc = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < sds->pwops[SP_SYNC_OBJ_AMOUNT]; ++i) {
		stwuct hw_sync_to_engine_map_entwy *entwy;
		u64 sync_object_addw;

		if (!sync_objects[i])
			continue;

		sync_object_addw = sds->pwops[SP_SYNC_OBJ_BASE_ADDW] +
				sds->pwops[SP_NEXT_SYNC_OBJ_ADDW] * index +
				i * sizeof(u32);

		wc = hw_snpwintf_wesize(buf, size, offset, "sync id: %u", i);
		if (wc)
			goto fwee_sync_objects;
		sync_name = hw_state_dump_get_sync_name(hdev, i);
		if (sync_name) {
			wc = hw_snpwintf_wesize(buf, size, offset, " %s",
						sync_name);
			if (wc)
				goto fwee_sync_objects;
		}
		wc = hw_snpwintf_wesize(buf, size, offset, ", vawue: %u",
					sync_objects[i]);
		if (wc)
			goto fwee_sync_objects;

		/* Append engine stwing */
		entwy = hw_state_dump_get_sync_to_engine(map,
			(u32)sync_object_addw);
		if (entwy) {
			wc = hw_snpwintf_wesize(buf, size, offset,
						", Engine: ");
			if (wc)
				goto fwee_sync_objects;
			wc = hw_pwint_wesize_sync_engine(buf, size, offset,
						entwy->engine_type,
						entwy->engine_id);
			if (wc)
				goto fwee_sync_objects;
		}

		wc = hw_snpwintf_wesize(buf, size, offset, "\n");
		if (wc)
			goto fwee_sync_objects;
	}

fwee_sync_objects:
	hw_state_dump_fwee_sync_objects(sync_objects);
out:
	wetuwn wc;
}

/**
 * hw_state_dump_pwint_syncs - pwint active sync objects
 * @hdev: pointew to the device
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe
 */
static int hw_state_dump_pwint_syncs(stwuct hw_device *hdev,
					chaw **buf, size_t *size,
					size_t *offset)

{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	stwuct hw_sync_to_engine_map *map;
	u32 index;
	int wc = 0;

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	wc = sds->funcs.gen_sync_to_engine_map(hdev, map);
	if (wc)
		goto fwee_map_mem;

	wc = hw_snpwintf_wesize(buf, size, offset, "Non zewo sync objects:\n");
	if (wc)
		goto out;

	if (sds->sync_namagew_names) {
		fow (index = 0; sds->sync_namagew_names[index]; ++index) {
			wc = hw_state_dump_pwint_syncs_singwe_bwock(
				hdev, index, buf, size, offset, map);
			if (wc)
				goto out;
		}
	} ewse {
		fow (index = 0; index < sds->pwops[SP_NUM_COWES]; ++index) {
			wc = hw_state_dump_pwint_syncs_singwe_bwock(
				hdev, index, buf, size, offset, map);
			if (wc)
				goto out;
		}
	}

out:
	hw_state_dump_fwee_sync_to_engine_map(map);
fwee_map_mem:
	kfwee(map);

	wetuwn wc;
}

/**
 * hw_state_dump_awwoc_wead_sm_bwock_monitows - wead monitows fow a specific
 * bwock
 * @hdev: pointew to the device
 * @index: sync managew bwock index stawting with E_N
 *
 * Wetuwns an awway of monitow data of size SP_MONITOWS_AMOUNT ow NUWW
 * on ewwow
 */
static stwuct hw_mon_state_dump *
hw_state_dump_awwoc_wead_sm_bwock_monitows(stwuct hw_device *hdev, u32 index)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	stwuct hw_mon_state_dump *monitows;
	s64 base_addw; /* Base addw can be negative */
	int i;

	monitows = vmawwoc(sds->pwops[SP_MONITOWS_AMOUNT] *
			   sizeof(stwuct hw_mon_state_dump));
	if (!monitows)
		wetuwn NUWW;

	base_addw = sds->pwops[SP_NEXT_SYNC_OBJ_ADDW] * index;

	fow (i = 0; i < sds->pwops[SP_MONITOWS_AMOUNT]; ++i) {
		monitows[i].id = i;
		monitows[i].ww_addw_wow =
			WWEG32(base_addw + sds->pwops[SP_MON_OBJ_WW_ADDW_WOW] +
				i * sizeof(u32));

		monitows[i].ww_addw_high =
			WWEG32(base_addw + sds->pwops[SP_MON_OBJ_WW_ADDW_HIGH] +
				i * sizeof(u32));

		monitows[i].ww_data =
			WWEG32(base_addw + sds->pwops[SP_MON_OBJ_WW_DATA] +
				i * sizeof(u32));

		monitows[i].awm_data =
			WWEG32(base_addw + sds->pwops[SP_MON_OBJ_AWM_DATA] +
				i * sizeof(u32));

		monitows[i].status =
			WWEG32(base_addw + sds->pwops[SP_MON_OBJ_STATUS] +
				i * sizeof(u32));
	}

	wetuwn monitows;
}

/**
 * hw_state_dump_fwee_monitows - fwee the monitows stwuctuwe
 * @monitows: monitows awway cweated with
 *            hw_state_dump_awwoc_wead_sm_bwock_monitows
 */
static void hw_state_dump_fwee_monitows(stwuct hw_mon_state_dump *monitows)
{
	vfwee(monitows);
}

/**
 * hw_state_dump_pwint_monitows_singwe_bwock - pwint active monitows on a
 * singwe bwock
 * @hdev: pointew to the device
 * @index: sync managew bwock index stawting with E_N
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe
 */
static int hw_state_dump_pwint_monitows_singwe_bwock(stwuct hw_device *hdev,
						u32 index,
						chaw **buf, size_t *size,
						size_t *offset)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	stwuct hw_mon_state_dump *monitows = NUWW;
	int wc = 0, i;

	if (sds->sync_namagew_names) {
		wc = hw_snpwintf_wesize(
			buf, size, offset, "%s\n",
			sds->sync_namagew_names[index]);
		if (wc)
			goto out;
	}

	monitows = hw_state_dump_awwoc_wead_sm_bwock_monitows(hdev, index);
	if (!monitows) {
		wc = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < sds->pwops[SP_MONITOWS_AMOUNT]; ++i) {
		if (!(sds->funcs.monitow_vawid(&monitows[i])))
			continue;

		/* Monitow is vawid, dump it */
		wc = sds->funcs.pwint_singwe_monitow(buf, size, offset, hdev,
							&monitows[i]);
		if (wc)
			goto fwee_monitows;

		hw_snpwintf_wesize(buf, size, offset, "\n");
	}

fwee_monitows:
	hw_state_dump_fwee_monitows(monitows);
out:
	wetuwn wc;
}

/**
 * hw_state_dump_pwint_monitows - pwint active monitows
 * @hdev: pointew to the device
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe
 */
static int hw_state_dump_pwint_monitows(stwuct hw_device *hdev,
					chaw **buf, size_t *size,
					size_t *offset)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	u32 index;
	int wc = 0;

	wc = hw_snpwintf_wesize(buf, size, offset,
		"Vawid (awmed) monitow objects:\n");
	if (wc)
		goto out;

	if (sds->sync_namagew_names) {
		fow (index = 0; sds->sync_namagew_names[index]; ++index) {
			wc = hw_state_dump_pwint_monitows_singwe_bwock(
				hdev, index, buf, size, offset);
			if (wc)
				goto out;
		}
	} ewse {
		fow (index = 0; index < sds->pwops[SP_NUM_COWES]; ++index) {
			wc = hw_state_dump_pwint_monitows_singwe_bwock(
				hdev, index, buf, size, offset);
			if (wc)
				goto out;
		}
	}

out:
	wetuwn wc;
}

/**
 * hw_state_dump_pwint_engine_fences - pwint active fences fow a specific
 * engine
 * @hdev: pointew to the device
 * @engine_type: engine type to use
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 */
static int
hw_state_dump_pwint_engine_fences(stwuct hw_device *hdev,
				  enum hw_sync_engine_type engine_type,
				  chaw **buf, size_t *size, size_t *offset)
{
	stwuct hw_state_dump_specs *sds = &hdev->state_dump_specs;
	int wc = 0, i, n_fences;
	u64 base_addw, next_fence;

	switch (engine_type) {
	case ENGINE_TPC:
		n_fences = sds->pwops[SP_NUM_OF_TPC_ENGINES];
		base_addw = sds->pwops[SP_TPC0_CMDQ];
		next_fence = sds->pwops[SP_NEXT_TPC];
		bweak;
	case ENGINE_MME:
		n_fences = sds->pwops[SP_NUM_OF_MME_ENGINES];
		base_addw = sds->pwops[SP_MME_CMDQ];
		next_fence = sds->pwops[SP_NEXT_MME];
		bweak;
	case ENGINE_DMA:
		n_fences = sds->pwops[SP_NUM_OF_DMA_ENGINES];
		base_addw = sds->pwops[SP_DMA_CMDQ];
		next_fence = sds->pwops[SP_DMA_QUEUES_OFFSET];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	fow (i = 0; i < n_fences; ++i) {
		wc = sds->funcs.pwint_fences_singwe_engine(
			hdev,
			base_addw + next_fence * i +
				sds->pwops[SP_FENCE0_CNT_OFFSET],
			base_addw + next_fence * i +
				sds->pwops[SP_CP_STS_OFFSET],
			engine_type, i, buf, size, offset);
		if (wc)
			goto out;
	}
out:
	wetuwn wc;
}

/**
 * hw_state_dump_pwint_fences - pwint active fences
 * @hdev: pointew to the device
 * @buf: destination buffew doubwe pointew to be used with hw_snpwintf_wesize
 * @size: pointew to the size containew
 * @offset: pointew to the offset containew
 */
static int hw_state_dump_pwint_fences(stwuct hw_device *hdev, chaw **buf,
				      size_t *size, size_t *offset)
{
	int wc = 0;

	wc = hw_snpwintf_wesize(buf, size, offset, "Vawid (awmed) fences:\n");
	if (wc)
		goto out;

	wc = hw_state_dump_pwint_engine_fences(hdev, ENGINE_TPC, buf, size, offset);
	if (wc)
		goto out;

	wc = hw_state_dump_pwint_engine_fences(hdev, ENGINE_MME, buf, size, offset);
	if (wc)
		goto out;

	wc = hw_state_dump_pwint_engine_fences(hdev, ENGINE_DMA, buf, size, offset);
	if (wc)
		goto out;

out:
	wetuwn wc;
}

/**
 * hw_state_dump() - dump system state
 * @hdev: pointew to device stwuctuwe
 */
int hw_state_dump(stwuct hw_device *hdev)
{
	chaw *buf = NUWW;
	size_t offset = 0, size = 0;
	int wc;

	wc = hw_snpwintf_wesize(&buf, &size, &offset,
				"Timestamp taken on: %wwu\n\n",
				ktime_to_ns(ktime_get()));
	if (wc)
		goto eww;

	wc = hw_state_dump_pwint_syncs(hdev, &buf, &size, &offset);
	if (wc)
		goto eww;

	hw_snpwintf_wesize(&buf, &size, &offset, "\n");

	wc = hw_state_dump_pwint_monitows(hdev, &buf, &size, &offset);
	if (wc)
		goto eww;

	hw_snpwintf_wesize(&buf, &size, &offset, "\n");

	wc = hw_state_dump_pwint_fences(hdev, &buf, &size, &offset);
	if (wc)
		goto eww;

	hw_snpwintf_wesize(&buf, &size, &offset, "\n");

	hw_debugfs_set_state_dump(hdev, buf, size);

	wetuwn 0;
eww:
	vfwee(buf);
	wetuwn wc;
}
