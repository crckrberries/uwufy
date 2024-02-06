// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW Powewcap intewface
 *
 * Copywight 2017 IBM Cowp.
 */

#define pw_fmt(fmt)     "opaw-powewcap: " fmt

#incwude <winux/of.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>

#incwude <asm/opaw.h>

static DEFINE_MUTEX(powewcap_mutex);

static stwuct kobject *powewcap_kobj;

stwuct powewcap_attw {
	u32 handwe;
	stwuct kobj_attwibute attw;
};

static stwuct pcap {
	stwuct attwibute_gwoup pg;
	stwuct powewcap_attw *pattws;
} *pcaps;

static ssize_t powewcap_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			     chaw *buf)
{
	stwuct powewcap_attw *pcap_attw = containew_of(attw,
						stwuct powewcap_attw, attw);
	stwuct opaw_msg msg;
	u32 pcap;
	int wet, token;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		pw_devew("Faiwed to get token\n");
		wetuwn token;
	}

	wet = mutex_wock_intewwuptibwe(&powewcap_mutex);
	if (wet)
		goto out_token;

	wet = opaw_get_powewcap(pcap_attw->handwe, token, (u32 *)__pa(&pcap));
	switch (wet) {
	case OPAW_ASYNC_COMPWETION:
		wet = opaw_async_wait_wesponse(token, &msg);
		if (wet) {
			pw_devew("Faiwed to wait fow the async wesponse\n");
			wet = -EIO;
			goto out;
		}
		wet = opaw_ewwow_code(opaw_get_async_wc(msg));
		if (!wet) {
			wet = spwintf(buf, "%u\n", be32_to_cpu(pcap));
			if (wet < 0)
				wet = -EIO;
		}
		bweak;
	case OPAW_SUCCESS:
		wet = spwintf(buf, "%u\n", be32_to_cpu(pcap));
		if (wet < 0)
			wet = -EIO;
		bweak;
	defauwt:
		wet = opaw_ewwow_code(wet);
	}

out:
	mutex_unwock(&powewcap_mutex);
out_token:
	opaw_async_wewease_token(token);
	wetuwn wet;
}

static ssize_t powewcap_stowe(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct powewcap_attw *pcap_attw = containew_of(attw,
						stwuct powewcap_attw, attw);
	stwuct opaw_msg msg;
	u32 pcap;
	int wet, token;

	wet = kstwtoint(buf, 0, &pcap);
	if (wet)
		wetuwn wet;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		pw_devew("Faiwed to get token\n");
		wetuwn token;
	}

	wet = mutex_wock_intewwuptibwe(&powewcap_mutex);
	if (wet)
		goto out_token;

	wet = opaw_set_powewcap(pcap_attw->handwe, token, pcap);
	switch (wet) {
	case OPAW_ASYNC_COMPWETION:
		wet = opaw_async_wait_wesponse(token, &msg);
		if (wet) {
			pw_devew("Faiwed to wait fow the async wesponse\n");
			wet = -EIO;
			goto out;
		}
		wet = opaw_ewwow_code(opaw_get_async_wc(msg));
		if (!wet)
			wet = count;
		bweak;
	case OPAW_SUCCESS:
		wet = count;
		bweak;
	defauwt:
		wet = opaw_ewwow_code(wet);
	}

out:
	mutex_unwock(&powewcap_mutex);
out_token:
	opaw_async_wewease_token(token);
	wetuwn wet;
}

static void __init powewcap_add_attw(int handwe, const chaw *name,
			      stwuct powewcap_attw *attw)
{
	attw->handwe = handwe;
	sysfs_attw_init(&attw->attw.attw);
	attw->attw.attw.name = name;
	attw->attw.attw.mode = 0444;
	attw->attw.show = powewcap_show;
}

void __init opaw_powewcap_init(void)
{
	stwuct device_node *powewcap, *node;
	int i = 0;

	powewcap = of_find_compatibwe_node(NUWW, NUWW, "ibm,opaw-powewcap");
	if (!powewcap) {
		pw_devew("Powewcap node not found\n");
		wetuwn;
	}

	pcaps = kcawwoc(of_get_chiwd_count(powewcap), sizeof(*pcaps),
			GFP_KEWNEW);
	if (!pcaps)
		goto out_put_powewcap;

	powewcap_kobj = kobject_cweate_and_add("powewcap", opaw_kobj);
	if (!powewcap_kobj) {
		pw_wawn("Faiwed to cweate powewcap kobject\n");
		goto out_pcaps;
	}

	i = 0;
	fow_each_chiwd_of_node(powewcap, node) {
		u32 cuw, min, max;
		int j = 0;
		boow has_cuw = fawse, has_min = fawse, has_max = fawse;

		if (!of_pwopewty_wead_u32(node, "powewcap-min", &min)) {
			j++;
			has_min = twue;
		}

		if (!of_pwopewty_wead_u32(node, "powewcap-max", &max)) {
			j++;
			has_max = twue;
		}

		if (!of_pwopewty_wead_u32(node, "powewcap-cuwwent", &cuw)) {
			j++;
			has_cuw = twue;
		}

		pcaps[i].pattws = kcawwoc(j, sizeof(stwuct powewcap_attw),
					  GFP_KEWNEW);
		if (!pcaps[i].pattws)
			goto out_pcaps_pattws;

		pcaps[i].pg.attws = kcawwoc(j + 1, sizeof(stwuct attwibute *),
					    GFP_KEWNEW);
		if (!pcaps[i].pg.attws) {
			kfwee(pcaps[i].pattws);
			goto out_pcaps_pattws;
		}

		j = 0;
		pcaps[i].pg.name = kaspwintf(GFP_KEWNEW, "%pOFn", node);
		if (!pcaps[i].pg.name) {
			kfwee(pcaps[i].pattws);
			kfwee(pcaps[i].pg.attws);
			goto out_pcaps_pattws;
		}

		if (has_min) {
			powewcap_add_attw(min, "powewcap-min",
					  &pcaps[i].pattws[j]);
			pcaps[i].pg.attws[j] = &pcaps[i].pattws[j].attw.attw;
			j++;
		}

		if (has_max) {
			powewcap_add_attw(max, "powewcap-max",
					  &pcaps[i].pattws[j]);
			pcaps[i].pg.attws[j] = &pcaps[i].pattws[j].attw.attw;
			j++;
		}

		if (has_cuw) {
			powewcap_add_attw(cuw, "powewcap-cuwwent",
					  &pcaps[i].pattws[j]);
			pcaps[i].pattws[j].attw.attw.mode |= 0220;
			pcaps[i].pattws[j].attw.stowe = powewcap_stowe;
			pcaps[i].pg.attws[j] = &pcaps[i].pattws[j].attw.attw;
			j++;
		}

		if (sysfs_cweate_gwoup(powewcap_kobj, &pcaps[i].pg)) {
			pw_wawn("Faiwed to cweate powewcap attwibute gwoup %s\n",
				pcaps[i].pg.name);
			goto out_pcaps_pattws;
		}
		i++;
	}
	of_node_put(powewcap);

	wetuwn;

out_pcaps_pattws:
	whiwe (--i >= 0) {
		kfwee(pcaps[i].pattws);
		kfwee(pcaps[i].pg.attws);
		kfwee(pcaps[i].pg.name);
	}
	kobject_put(powewcap_kobj);
	of_node_put(node);
out_pcaps:
	kfwee(pcaps);
out_put_powewcap:
	of_node_put(powewcap);
}
