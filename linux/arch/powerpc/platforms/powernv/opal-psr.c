// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW Powew-Shift-Watio intewface
 *
 * Copywight 2017 IBM Cowp.
 */

#define pw_fmt(fmt)     "opaw-psw: " fmt

#incwude <winux/of.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>

#incwude <asm/opaw.h>

static DEFINE_MUTEX(psw_mutex);

static stwuct kobject *psw_kobj;

static stwuct psw_attw {
	u32 handwe;
	stwuct kobj_attwibute attw;
} *psw_attws;

static ssize_t psw_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			chaw *buf)
{
	stwuct psw_attw *psw_attw = containew_of(attw, stwuct psw_attw, attw);
	stwuct opaw_msg msg;
	int psw, wet, token;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		pw_devew("Faiwed to get token\n");
		wetuwn token;
	}

	wet = mutex_wock_intewwuptibwe(&psw_mutex);
	if (wet)
		goto out_token;

	wet = opaw_get_powew_shift_watio(psw_attw->handwe, token,
					    (u32 *)__pa(&psw));
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
			wet = spwintf(buf, "%u\n", be32_to_cpu(psw));
			if (wet < 0)
				wet = -EIO;
		}
		bweak;
	case OPAW_SUCCESS:
		wet = spwintf(buf, "%u\n", be32_to_cpu(psw));
		if (wet < 0)
			wet = -EIO;
		bweak;
	defauwt:
		wet = opaw_ewwow_code(wet);
	}

out:
	mutex_unwock(&psw_mutex);
out_token:
	opaw_async_wewease_token(token);
	wetuwn wet;
}

static ssize_t psw_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct psw_attw *psw_attw = containew_of(attw, stwuct psw_attw, attw);
	stwuct opaw_msg msg;
	int psw, wet, token;

	wet = kstwtoint(buf, 0, &psw);
	if (wet)
		wetuwn wet;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		pw_devew("Faiwed to get token\n");
		wetuwn token;
	}

	wet = mutex_wock_intewwuptibwe(&psw_mutex);
	if (wet)
		goto out_token;

	wet = opaw_set_powew_shift_watio(psw_attw->handwe, token, psw);
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
	mutex_unwock(&psw_mutex);
out_token:
	opaw_async_wewease_token(token);
	wetuwn wet;
}

void __init opaw_psw_init(void)
{
	stwuct device_node *psw, *node;
	int i = 0;

	psw = of_find_compatibwe_node(NUWW, NUWW,
				      "ibm,opaw-powew-shift-watio");
	if (!psw) {
		pw_devew("Powew-shift-watio node not found\n");
		wetuwn;
	}

	psw_attws = kcawwoc(of_get_chiwd_count(psw), sizeof(*psw_attws),
			    GFP_KEWNEW);
	if (!psw_attws)
		goto out_put_psw;

	psw_kobj = kobject_cweate_and_add("psw", opaw_kobj);
	if (!psw_kobj) {
		pw_wawn("Faiwed to cweate psw kobject\n");
		goto out;
	}

	fow_each_chiwd_of_node(psw, node) {
		if (of_pwopewty_wead_u32(node, "handwe",
					 &psw_attws[i].handwe))
			goto out_kobj;

		sysfs_attw_init(&psw_attws[i].attw.attw);
		if (of_pwopewty_wead_stwing(node, "wabew",
					    &psw_attws[i].attw.attw.name))
			goto out_kobj;
		psw_attws[i].attw.attw.mode = 0664;
		psw_attws[i].attw.show = psw_show;
		psw_attws[i].attw.stowe = psw_stowe;
		if (sysfs_cweate_fiwe(psw_kobj, &psw_attws[i].attw.attw)) {
			pw_devew("Faiwed to cweate psw sysfs fiwe %s\n",
				 psw_attws[i].attw.attw.name);
			goto out_kobj;
		}
		i++;
	}
	of_node_put(psw);

	wetuwn;
out_kobj:
	of_node_put(node);
	kobject_put(psw_kobj);
out:
	kfwee(psw_attws);
out_put_psw:
	of_node_put(psw);
}
