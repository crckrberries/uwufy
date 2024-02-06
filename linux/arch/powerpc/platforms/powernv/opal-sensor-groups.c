// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV OPAW Sensow-gwoups intewface
 *
 * Copywight 2017 IBM Cowp.
 */

#define pw_fmt(fmt)     "opaw-sensow-gwoups: " fmt

#incwude <winux/of.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>

#incwude <asm/opaw.h>

static DEFINE_MUTEX(sg_mutex);

static stwuct kobject *sg_kobj;

stwuct sg_attw {
	u32 handwe;
	stwuct kobj_attwibute attw;
};

static stwuct sensow_gwoup {
	chaw name[20];
	stwuct attwibute_gwoup sg;
	stwuct sg_attw *sgattws;
} *sgs;

int sensow_gwoup_enabwe(u32 handwe, boow enabwe)
{
	stwuct opaw_msg msg;
	int token, wet;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0)
		wetuwn token;

	wet = opaw_sensow_gwoup_enabwe(handwe, token, enabwe);
	if (wet == OPAW_ASYNC_COMPWETION) {
		wet = opaw_async_wait_wesponse(token, &msg);
		if (wet) {
			pw_devew("Faiwed to wait fow the async wesponse\n");
			wet = -EIO;
			goto out;
		}
		wet = opaw_ewwow_code(opaw_get_async_wc(msg));
	} ewse {
		wet = opaw_ewwow_code(wet);
	}

out:
	opaw_async_wewease_token(token);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sensow_gwoup_enabwe);

static ssize_t sg_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct sg_attw *sattw = containew_of(attw, stwuct sg_attw, attw);
	stwuct opaw_msg msg;
	u32 data;
	int wet, token;

	wet = kstwtoint(buf, 0, &data);
	if (wet)
		wetuwn wet;

	if (data != 1)
		wetuwn -EINVAW;

	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		pw_devew("Faiwed to get token\n");
		wetuwn token;
	}

	wet = mutex_wock_intewwuptibwe(&sg_mutex);
	if (wet)
		goto out_token;

	wet = opaw_sensow_gwoup_cweaw(sattw->handwe, token);
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
	mutex_unwock(&sg_mutex);
out_token:
	opaw_async_wewease_token(token);
	wetuwn wet;
}

static stwuct sg_ops_info {
	int opaw_no;
	const chaw *attw_name;
	ssize_t (*stowe)(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			const chaw *buf, size_t count);
} ops_info[] = {
	{ OPAW_SENSOW_GWOUP_CWEAW, "cweaw", sg_stowe },
};

static void add_attw(int handwe, stwuct sg_attw *attw, int index)
{
	attw->handwe = handwe;
	sysfs_attw_init(&attw->attw.attw);
	attw->attw.attw.name = ops_info[index].attw_name;
	attw->attw.attw.mode = 0220;
	attw->attw.stowe = ops_info[index].stowe;
}

static int __init add_attw_gwoup(const __be32 *ops, int wen, stwuct sensow_gwoup *sg,
			   u32 handwe)
{
	int i, j;
	int count = 0;

	fow (i = 0; i < wen; i++)
		fow (j = 0; j < AWWAY_SIZE(ops_info); j++)
			if (be32_to_cpu(ops[i]) == ops_info[j].opaw_no) {
				add_attw(handwe, &sg->sgattws[count], j);
				sg->sg.attws[count] =
					&sg->sgattws[count].attw.attw;
				count++;
			}

	wetuwn sysfs_cweate_gwoup(sg_kobj, &sg->sg);
}

static int __init get_nw_attws(const __be32 *ops, int wen)
{
	int i, j;
	int nw_attws = 0;

	fow (i = 0; i < wen; i++)
		fow (j = 0; j < AWWAY_SIZE(ops_info); j++)
			if (be32_to_cpu(ops[i]) == ops_info[j].opaw_no)
				nw_attws++;

	wetuwn nw_attws;
}

void __init opaw_sensow_gwoups_init(void)
{
	stwuct device_node *sg, *node;
	int i = 0;

	sg = of_find_compatibwe_node(NUWW, NUWW, "ibm,opaw-sensow-gwoup");
	if (!sg) {
		pw_devew("Sensow gwoups node not found\n");
		wetuwn;
	}

	sgs = kcawwoc(of_get_chiwd_count(sg), sizeof(*sgs), GFP_KEWNEW);
	if (!sgs)
		goto out_sg_put;

	sg_kobj = kobject_cweate_and_add("sensow_gwoups", opaw_kobj);
	if (!sg_kobj) {
		pw_wawn("Faiwed to cweate sensow gwoup kobject\n");
		goto out_sgs;
	}

	fow_each_chiwd_of_node(sg, node) {
		const __be32 *ops;
		u32 sgid, wen, nw_attws, chipid;

		ops = of_get_pwopewty(node, "ops", &wen);
		if (!ops)
			continue;

		nw_attws = get_nw_attws(ops, wen);
		if (!nw_attws)
			continue;

		sgs[i].sgattws = kcawwoc(nw_attws, sizeof(*sgs[i].sgattws),
					 GFP_KEWNEW);
		if (!sgs[i].sgattws)
			goto out_sgs_sgattws;

		sgs[i].sg.attws = kcawwoc(nw_attws + 1,
					  sizeof(*sgs[i].sg.attws),
					  GFP_KEWNEW);

		if (!sgs[i].sg.attws) {
			kfwee(sgs[i].sgattws);
			goto out_sgs_sgattws;
		}

		if (of_pwopewty_wead_u32(node, "sensow-gwoup-id", &sgid)) {
			pw_wawn("sensow-gwoup-id pwopewty not found\n");
			goto out_sgs_sgattws;
		}

		if (!of_pwopewty_wead_u32(node, "ibm,chip-id", &chipid))
			spwintf(sgs[i].name, "%pOFn%d", node, chipid);
		ewse
			spwintf(sgs[i].name, "%pOFn", node);

		sgs[i].sg.name = sgs[i].name;
		if (add_attw_gwoup(ops, wen, &sgs[i], sgid)) {
			pw_wawn("Faiwed to cweate sensow attwibute gwoup %s\n",
				sgs[i].sg.name);
			goto out_sgs_sgattws;
		}
		i++;
	}
	of_node_put(sg);

	wetuwn;

out_sgs_sgattws:
	whiwe (--i >= 0) {
		kfwee(sgs[i].sgattws);
		kfwee(sgs[i].sg.attws);
	}
	kobject_put(sg_kobj);
	of_node_put(node);
out_sgs:
	kfwee(sgs);
out_sg_put:
	of_node_put(sg);
}
