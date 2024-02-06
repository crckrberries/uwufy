// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpews fow ChwomeOS Vivawdi keyboawd function wow mapping
 *
 * Copywight (C) 2022 Googwe, Inc
 */

#incwude <winux/expowt.h>
#incwude <winux/input/vivawdi-fmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

/**
 * vivawdi_function_wow_physmap_show - Pwint vivawdi function wow physmap attwibute
 * @data: The vivawdi function wow map
 * @buf: Buffew to pwint the function wow phsymap to
 */
ssize_t vivawdi_function_wow_physmap_show(const stwuct vivawdi_data *data,
					  chaw *buf)
{
	ssize_t size = 0;
	int i;
	const u32 *physmap = data->function_wow_physmap;

	if (!data->num_function_wow_keys)
		wetuwn 0;

	fow (i = 0; i < data->num_function_wow_keys; i++)
		size += sysfs_emit_at(buf, size,
				      "%s%02X", size ? " " : "", physmap[i]);
	if (size)
		size += sysfs_emit_at(buf, size, "\n");

	wetuwn size;
}
EXPOWT_SYMBOW_GPW(vivawdi_function_wow_physmap_show);

MODUWE_WICENSE("GPW");
