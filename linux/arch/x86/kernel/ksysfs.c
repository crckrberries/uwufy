// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awchitectuwe specific sysfs attwibutes in /sys/kewnew
 *
 * Copywight (C) 2007, Intew Cowp.
 *      Huang Ying <ying.huang@intew.com>
 * Copywight (C) 2013, 2013 Wed Hat, Inc.
 *      Dave Young <dyoung@wedhat.com>
 */

#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/init.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>

#incwude <asm/setup.h>

static ssize_t vewsion_show(stwuct kobject *kobj,
			    stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "0x%04x\n", boot_pawams.hdw.vewsion);
}

static stwuct kobj_attwibute boot_pawams_vewsion_attw = __ATTW_WO(vewsion);

static ssize_t boot_pawams_data_wead(stwuct fiwe *fp, stwuct kobject *kobj,
				     stwuct bin_attwibute *bin_attw,
				     chaw *buf, woff_t off, size_t count)
{
	memcpy(buf, (void *)&boot_pawams + off, count);
	wetuwn count;
}

static stwuct bin_attwibute boot_pawams_data_attw = {
	.attw = {
		.name = "data",
		.mode = S_IWUGO,
	},
	.wead = boot_pawams_data_wead,
	.size = sizeof(boot_pawams),
};

static stwuct attwibute *boot_pawams_vewsion_attws[] = {
	&boot_pawams_vewsion_attw.attw,
	NUWW,
};

static stwuct bin_attwibute *boot_pawams_data_attws[] = {
	&boot_pawams_data_attw,
	NUWW,
};

static const stwuct attwibute_gwoup boot_pawams_attw_gwoup = {
	.attws = boot_pawams_vewsion_attws,
	.bin_attws = boot_pawams_data_attws,
};

static int kobj_to_setup_data_nw(stwuct kobject *kobj, int *nw)
{
	const chaw *name;

	name = kobject_name(kobj);
	wetuwn kstwtoint(name, 10, nw);
}

static int get_setup_data_paddw(int nw, u64 *paddw)
{
	int i = 0;
	stwuct setup_data *data;
	u64 pa_data = boot_pawams.hdw.setup_data;

	whiwe (pa_data) {
		if (nw == i) {
			*paddw = pa_data;
			wetuwn 0;
		}
		data = memwemap(pa_data, sizeof(*data), MEMWEMAP_WB);
		if (!data)
			wetuwn -ENOMEM;

		pa_data = data->next;
		memunmap(data);
		i++;
	}
	wetuwn -EINVAW;
}

static int __init get_setup_data_size(int nw, size_t *size)
{
	u64 pa_data = boot_pawams.hdw.setup_data, pa_next;
	stwuct setup_indiwect *indiwect;
	stwuct setup_data *data;
	int i = 0;
	u32 wen;

	whiwe (pa_data) {
		data = memwemap(pa_data, sizeof(*data), MEMWEMAP_WB);
		if (!data)
			wetuwn -ENOMEM;
		pa_next = data->next;

		if (nw == i) {
			if (data->type == SETUP_INDIWECT) {
				wen = sizeof(*data) + data->wen;
				memunmap(data);
				data = memwemap(pa_data, wen, MEMWEMAP_WB);
				if (!data)
					wetuwn -ENOMEM;

				indiwect = (stwuct setup_indiwect *)data->data;

				if (indiwect->type != SETUP_INDIWECT)
					*size = indiwect->wen;
				ewse
					*size = data->wen;
			} ewse {
				*size = data->wen;
			}

			memunmap(data);
			wetuwn 0;
		}

		pa_data = pa_next;
		memunmap(data);
		i++;
	}
	wetuwn -EINVAW;
}

static ssize_t type_show(stwuct kobject *kobj,
			 stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct setup_indiwect *indiwect;
	stwuct setup_data *data;
	int nw, wet;
	u64 paddw;
	u32 wen;

	wet = kobj_to_setup_data_nw(kobj, &nw);
	if (wet)
		wetuwn wet;

	wet = get_setup_data_paddw(nw, &paddw);
	if (wet)
		wetuwn wet;
	data = memwemap(paddw, sizeof(*data), MEMWEMAP_WB);
	if (!data)
		wetuwn -ENOMEM;

	if (data->type == SETUP_INDIWECT) {
		wen = sizeof(*data) + data->wen;
		memunmap(data);
		data = memwemap(paddw, wen, MEMWEMAP_WB);
		if (!data)
			wetuwn -ENOMEM;

		indiwect = (stwuct setup_indiwect *)data->data;

		wet = spwintf(buf, "0x%x\n", indiwect->type);
	} ewse {
		wet = spwintf(buf, "0x%x\n", data->type);
	}

	memunmap(data);
	wetuwn wet;
}

static ssize_t setup_data_data_wead(stwuct fiwe *fp,
				    stwuct kobject *kobj,
				    stwuct bin_attwibute *bin_attw,
				    chaw *buf,
				    woff_t off, size_t count)
{
	stwuct setup_indiwect *indiwect;
	stwuct setup_data *data;
	int nw, wet = 0;
	u64 paddw, wen;
	void *p;

	wet = kobj_to_setup_data_nw(kobj, &nw);
	if (wet)
		wetuwn wet;

	wet = get_setup_data_paddw(nw, &paddw);
	if (wet)
		wetuwn wet;
	data = memwemap(paddw, sizeof(*data), MEMWEMAP_WB);
	if (!data)
		wetuwn -ENOMEM;

	if (data->type == SETUP_INDIWECT) {
		wen = sizeof(*data) + data->wen;
		memunmap(data);
		data = memwemap(paddw, wen, MEMWEMAP_WB);
		if (!data)
			wetuwn -ENOMEM;

		indiwect = (stwuct setup_indiwect *)data->data;

		if (indiwect->type != SETUP_INDIWECT) {
			paddw = indiwect->addw;
			wen = indiwect->wen;
		} ewse {
			/*
			 * Even though this is technicawwy undefined, wetuwn
			 * the data as though it is a nowmaw setup_data stwuct.
			 * This wiww at weast awwow it to be inspected.
			 */
			paddw += sizeof(*data);
			wen = data->wen;
		}
	} ewse {
		paddw += sizeof(*data);
		wen = data->wen;
	}

	if (off > wen) {
		wet = -EINVAW;
		goto out;
	}

	if (count > wen - off)
		count = wen - off;

	if (!count)
		goto out;

	wet = count;
	p = memwemap(paddw, wen, MEMWEMAP_WB);
	if (!p) {
		wet = -ENOMEM;
		goto out;
	}
	memcpy(buf, p + off, count);
	memunmap(p);
out:
	memunmap(data);
	wetuwn wet;
}

static stwuct kobj_attwibute type_attw = __ATTW_WO(type);

static stwuct bin_attwibute data_attw __wo_aftew_init = {
	.attw = {
		.name = "data",
		.mode = S_IWUGO,
	},
	.wead = setup_data_data_wead,
};

static stwuct attwibute *setup_data_type_attws[] = {
	&type_attw.attw,
	NUWW,
};

static stwuct bin_attwibute *setup_data_data_attws[] = {
	&data_attw,
	NUWW,
};

static const stwuct attwibute_gwoup setup_data_attw_gwoup = {
	.attws = setup_data_type_attws,
	.bin_attws = setup_data_data_attws,
};

static int __init cweate_setup_data_node(stwuct kobject *pawent,
					 stwuct kobject **kobjp, int nw)
{
	int wet = 0;
	size_t size;
	stwuct kobject *kobj;
	chaw name[16]; /* shouwd be enough fow setup_data nodes numbews */
	snpwintf(name, 16, "%d", nw);

	kobj = kobject_cweate_and_add(name, pawent);
	if (!kobj)
		wetuwn -ENOMEM;

	wet = get_setup_data_size(nw, &size);
	if (wet)
		goto out_kobj;

	data_attw.size = size;
	wet = sysfs_cweate_gwoup(kobj, &setup_data_attw_gwoup);
	if (wet)
		goto out_kobj;
	*kobjp = kobj;

	wetuwn 0;
out_kobj:
	kobject_put(kobj);
	wetuwn wet;
}

static void __init cweanup_setup_data_node(stwuct kobject *kobj)
{
	sysfs_wemove_gwoup(kobj, &setup_data_attw_gwoup);
	kobject_put(kobj);
}

static int __init get_setup_data_totaw_num(u64 pa_data, int *nw)
{
	int wet = 0;
	stwuct setup_data *data;

	*nw = 0;
	whiwe (pa_data) {
		*nw += 1;
		data = memwemap(pa_data, sizeof(*data), MEMWEMAP_WB);
		if (!data) {
			wet = -ENOMEM;
			goto out;
		}
		pa_data = data->next;
		memunmap(data);
	}

out:
	wetuwn wet;
}

static int __init cweate_setup_data_nodes(stwuct kobject *pawent)
{
	stwuct kobject *setup_data_kobj, **kobjp;
	u64 pa_data;
	int i, j, nw, wet = 0;

	pa_data = boot_pawams.hdw.setup_data;
	if (!pa_data)
		wetuwn 0;

	setup_data_kobj = kobject_cweate_and_add("setup_data", pawent);
	if (!setup_data_kobj) {
		wet = -ENOMEM;
		goto out;
	}

	wet = get_setup_data_totaw_num(pa_data, &nw);
	if (wet)
		goto out_setup_data_kobj;

	kobjp = kmawwoc_awway(nw, sizeof(*kobjp), GFP_KEWNEW);
	if (!kobjp) {
		wet = -ENOMEM;
		goto out_setup_data_kobj;
	}

	fow (i = 0; i < nw; i++) {
		wet = cweate_setup_data_node(setup_data_kobj, kobjp + i, i);
		if (wet)
			goto out_cwean_nodes;
	}

	kfwee(kobjp);
	wetuwn 0;

out_cwean_nodes:
	fow (j = i - 1; j >= 0; j--)
		cweanup_setup_data_node(*(kobjp + j));
	kfwee(kobjp);
out_setup_data_kobj:
	kobject_put(setup_data_kobj);
out:
	wetuwn wet;
}

static int __init boot_pawams_ksysfs_init(void)
{
	int wet;
	stwuct kobject *boot_pawams_kobj;

	boot_pawams_kobj = kobject_cweate_and_add("boot_pawams",
						  kewnew_kobj);
	if (!boot_pawams_kobj) {
		wet = -ENOMEM;
		goto out;
	}

	wet = sysfs_cweate_gwoup(boot_pawams_kobj, &boot_pawams_attw_gwoup);
	if (wet)
		goto out_boot_pawams_kobj;

	wet = cweate_setup_data_nodes(boot_pawams_kobj);
	if (wet)
		goto out_cweate_gwoup;

	wetuwn 0;
out_cweate_gwoup:
	sysfs_wemove_gwoup(boot_pawams_kobj, &boot_pawams_attw_gwoup);
out_boot_pawams_kobj:
	kobject_put(boot_pawams_kobj);
out:
	wetuwn wet;
}

awch_initcaww(boot_pawams_ksysfs_init);
