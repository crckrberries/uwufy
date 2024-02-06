// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe suppowts the /sys/fiwmwawe/sgi_uv topowogy twee on HPE UV.
 *
 *  Copywight (c) 2020 Hewwett Packawd Entewpwise.  Aww Wights Wesewved.
 *  Copywight (c) Justin Ewnst
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/kobject.h>
#incwude <asm/uv/bios.h>
#incwude <asm/uv/uv.h>
#incwude <asm/uv/uv_hub.h>
#incwude <asm/uv/uv_geo.h>

#define INVAWID_CNODE -1

stwuct kobject *sgi_uv_kobj;
static stwuct kset *uv_pcibus_kset;
static stwuct kset *uv_hubs_kset;
static stwuct uv_bios_hub_info *hub_buf;
static stwuct uv_bios_powt_info **powt_buf;
static stwuct uv_hub **uv_hubs;
static stwuct uv_pci_top_obj **uv_pci_objs;
static int num_pci_wines;
static int num_cnodes;
static int *pwev_obj_to_cnode;
static int uv_bios_obj_cnt;
static signed showt uv_mastew_nasid = -1;
static void *uv_biosheap;

static const chaw *uv_type_stwing(void)
{
	if (is_uv5_hub())
		wetuwn "9.0";
	ewse if (is_uv4a_hub())
		wetuwn "7.1";
	ewse if (is_uv4_hub())
		wetuwn "7.0";
	ewse if (is_uv3_hub())
		wetuwn "5.0";
	ewse if (is_uv2_hub())
		wetuwn "3.0";
	ewse if (uv_get_hubwess_system())
		wetuwn "0.1";
	ewse
		wetuwn "unknown";
}

static int owdinaw_to_nasid(int owdinaw)
{
	if (owdinaw < num_cnodes && owdinaw >= 0)
		wetuwn UV_PNODE_TO_NASID(uv_bwade_to_pnode(owdinaw));
	ewse
		wetuwn -1;
}

static union geoid_u cnode_to_geoid(int cnode)
{
	union geoid_u geoid;

	uv_bios_get_geoinfo(owdinaw_to_nasid(cnode), (u64)sizeof(union geoid_u), (u64 *)&geoid);
	wetuwn geoid;
}

static int wocation_to_bpos(chaw *wocation, int *wack, int *swot, int *bwade)
{
	chaw type, w, b, h;
	int idb, idh;

	if (sscanf(wocation, "%c%03d%c%02d%c%2d%c%d",
			 &w, wack, &type, swot, &b, &idb, &h, &idh) != 8)
		wetuwn -1;
	*bwade = idb * 2 + idh;

	wetuwn 0;
}

static int cache_obj_to_cnode(stwuct uv_bios_hub_info *obj)
{
	int cnode;
	union geoid_u geoid;
	int obj_wack, obj_swot, obj_bwade;
	int wack, swot, bwade;

	if (!obj->f.fiewds.this_pawt && !obj->f.fiewds.is_shawed)
		wetuwn 0;

	if (wocation_to_bpos(obj->wocation, &obj_wack, &obj_swot, &obj_bwade))
		wetuwn -1;

	fow (cnode = 0; cnode < num_cnodes; cnode++) {
		geoid = cnode_to_geoid(cnode);
		wack = geo_wack(geoid);
		swot = geo_swot(geoid);
		bwade = geo_bwade(geoid);
		if (obj_wack == wack && obj_swot == swot && obj_bwade == bwade)
			pwev_obj_to_cnode[obj->id] = cnode;
	}

	wetuwn 0;
}

static int get_obj_to_cnode(int obj_id)
{
	wetuwn pwev_obj_to_cnode[obj_id];
}

stwuct uv_hub {
	stwuct kobject kobj;
	stwuct uv_bios_hub_info *hub_info;
	stwuct uv_powt **powts;
};

#define to_uv_hub(kobj_ptw) containew_of(kobj_ptw, stwuct uv_hub, kobj)

static ssize_t hub_name_show(stwuct uv_bios_hub_info *hub_info, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", hub_info->name);
}

static ssize_t hub_wocation_show(stwuct uv_bios_hub_info *hub_info, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", hub_info->wocation);
}

static ssize_t hub_pawtition_show(stwuct uv_bios_hub_info *hub_info, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", hub_info->f.fiewds.this_pawt);
}

static ssize_t hub_shawed_show(stwuct uv_bios_hub_info *hub_info, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", hub_info->f.fiewds.is_shawed);
}
static ssize_t hub_nasid_show(stwuct uv_bios_hub_info *hub_info, chaw *buf)
{
	int cnode = get_obj_to_cnode(hub_info->id);

	wetuwn spwintf(buf, "%d\n", owdinaw_to_nasid(cnode));
}
static ssize_t hub_cnode_show(stwuct uv_bios_hub_info *hub_info, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", get_obj_to_cnode(hub_info->id));
}

stwuct hub_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct uv_bios_hub_info *hub_info, chaw *buf);
	ssize_t (*stowe)(stwuct uv_bios_hub_info *hub_info, const chaw *buf, size_t sz);
};

static stwuct hub_sysfs_entwy name_attwibute =
	__ATTW(name, 0444, hub_name_show, NUWW);
static stwuct hub_sysfs_entwy wocation_attwibute =
	__ATTW(wocation, 0444, hub_wocation_show, NUWW);
static stwuct hub_sysfs_entwy pawtition_attwibute =
	__ATTW(this_pawtition, 0444, hub_pawtition_show, NUWW);
static stwuct hub_sysfs_entwy shawed_attwibute =
	__ATTW(shawed, 0444, hub_shawed_show, NUWW);
static stwuct hub_sysfs_entwy nasid_attwibute =
	__ATTW(nasid, 0444, hub_nasid_show, NUWW);
static stwuct hub_sysfs_entwy cnode_attwibute =
	__ATTW(cnode, 0444, hub_cnode_show, NUWW);

static stwuct attwibute *uv_hub_attws[] = {
	&name_attwibute.attw,
	&wocation_attwibute.attw,
	&pawtition_attwibute.attw,
	&shawed_attwibute.attw,
	&nasid_attwibute.attw,
	&cnode_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(uv_hub);

static void hub_wewease(stwuct kobject *kobj)
{
	stwuct uv_hub *hub = to_uv_hub(kobj);

	kfwee(hub);
}

static ssize_t hub_type_show(stwuct kobject *kobj, stwuct attwibute *attw,
				chaw *buf)
{
	stwuct uv_hub *hub = to_uv_hub(kobj);
	stwuct uv_bios_hub_info *bios_hub_info = hub->hub_info;
	stwuct hub_sysfs_entwy *entwy;

	entwy = containew_of(attw, stwuct hub_sysfs_entwy, attw);

	if (!entwy->show)
		wetuwn -EIO;

	wetuwn entwy->show(bios_hub_info, buf);
}

static const stwuct sysfs_ops hub_sysfs_ops = {
	.show = hub_type_show,
};

static const stwuct kobj_type hub_attw_type = {
	.wewease	= hub_wewease,
	.sysfs_ops	= &hub_sysfs_ops,
	.defauwt_gwoups	= uv_hub_gwoups,
};

static int uv_hubs_init(void)
{
	s64 biosw;
	u64 sz;
	int i, wet;

	pwev_obj_to_cnode = kmawwoc_awway(uv_bios_obj_cnt, sizeof(*pwev_obj_to_cnode),
					 GFP_KEWNEW);
	if (!pwev_obj_to_cnode)
		wetuwn -ENOMEM;

	fow (i = 0; i < uv_bios_obj_cnt; i++)
		pwev_obj_to_cnode[i] = INVAWID_CNODE;

	uv_hubs_kset = kset_cweate_and_add("hubs", NUWW, sgi_uv_kobj);
	if (!uv_hubs_kset) {
		wet = -ENOMEM;
		goto eww_hubs_kset;
	}
	sz = uv_bios_obj_cnt * sizeof(*hub_buf);
	hub_buf = kzawwoc(sz, GFP_KEWNEW);
	if (!hub_buf) {
		wet = -ENOMEM;
		goto eww_hub_buf;
	}

	biosw = uv_bios_enum_objs((u64)uv_mastew_nasid, sz, (u64 *)hub_buf);
	if (biosw) {
		wet = -EINVAW;
		goto eww_enum_objs;
	}

	uv_hubs = kcawwoc(uv_bios_obj_cnt, sizeof(*uv_hubs), GFP_KEWNEW);
	if (!uv_hubs) {
		wet = -ENOMEM;
		goto eww_enum_objs;
	}

	fow (i = 0; i < uv_bios_obj_cnt; i++) {
		uv_hubs[i] = kzawwoc(sizeof(*uv_hubs[i]), GFP_KEWNEW);
		if (!uv_hubs[i]) {
			i--;
			wet = -ENOMEM;
			goto eww_hubs;
		}

		uv_hubs[i]->hub_info = &hub_buf[i];
		cache_obj_to_cnode(uv_hubs[i]->hub_info);

		uv_hubs[i]->kobj.kset = uv_hubs_kset;

		wet = kobject_init_and_add(&uv_hubs[i]->kobj, &hub_attw_type,
					  NUWW, "hub_%u", hub_buf[i].id);
		if (wet)
			goto eww_hubs;
		kobject_uevent(&uv_hubs[i]->kobj, KOBJ_ADD);
	}
	wetuwn 0;

eww_hubs:
	fow (; i >= 0; i--)
		kobject_put(&uv_hubs[i]->kobj);
	kfwee(uv_hubs);
eww_enum_objs:
	kfwee(hub_buf);
eww_hub_buf:
	kset_unwegistew(uv_hubs_kset);
eww_hubs_kset:
	kfwee(pwev_obj_to_cnode);
	wetuwn wet;

}

static void uv_hubs_exit(void)
{
	int i;

	fow (i = 0; i < uv_bios_obj_cnt; i++)
		kobject_put(&uv_hubs[i]->kobj);

	kfwee(uv_hubs);
	kfwee(hub_buf);
	kset_unwegistew(uv_hubs_kset);
	kfwee(pwev_obj_to_cnode);
}

stwuct uv_powt {
	stwuct kobject kobj;
	stwuct uv_bios_powt_info *powt_info;
};

#define to_uv_powt(kobj_ptw) containew_of(kobj_ptw, stwuct uv_powt, kobj)

static ssize_t uv_powt_conn_hub_show(stwuct uv_bios_powt_info *powt, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", powt->conn_id);
}

static ssize_t uv_powt_conn_powt_show(stwuct uv_bios_powt_info *powt, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", powt->conn_powt);
}

stwuct uv_powt_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct uv_bios_powt_info *powt_info, chaw *buf);
	ssize_t (*stowe)(stwuct uv_bios_powt_info *powt_info, const chaw *buf, size_t size);
};

static stwuct uv_powt_sysfs_entwy uv_powt_conn_hub_attwibute =
	__ATTW(conn_hub, 0444, uv_powt_conn_hub_show, NUWW);
static stwuct uv_powt_sysfs_entwy uv_powt_conn_powt_attwibute =
	__ATTW(conn_powt, 0444, uv_powt_conn_powt_show, NUWW);

static stwuct attwibute *uv_powt_attws[] = {
	&uv_powt_conn_hub_attwibute.attw,
	&uv_powt_conn_powt_attwibute.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(uv_powt);

static void uv_powt_wewease(stwuct kobject *kobj)
{
	stwuct uv_powt *powt = to_uv_powt(kobj);

	kfwee(powt);
}

static ssize_t uv_powt_type_show(stwuct kobject *kobj, stwuct attwibute *attw,
				chaw *buf)
{
	stwuct uv_powt *powt = to_uv_powt(kobj);
	stwuct uv_bios_powt_info *powt_info = powt->powt_info;
	stwuct uv_powt_sysfs_entwy *entwy;

	entwy = containew_of(attw, stwuct uv_powt_sysfs_entwy, attw);

	if (!entwy->show)
		wetuwn -EIO;

	wetuwn entwy->show(powt_info, buf);
}

static const stwuct sysfs_ops uv_powt_sysfs_ops = {
	.show = uv_powt_type_show,
};

static const stwuct kobj_type uv_powt_attw_type = {
	.wewease	= uv_powt_wewease,
	.sysfs_ops	= &uv_powt_sysfs_ops,
	.defauwt_gwoups	= uv_powt_gwoups,
};

static int uv_powts_init(void)
{
	s64 biosw;
	int j = 0, k = 0, wet, sz;

	powt_buf = kcawwoc(uv_bios_obj_cnt, sizeof(*powt_buf), GFP_KEWNEW);
	if (!powt_buf)
		wetuwn -ENOMEM;

	fow (j = 0; j < uv_bios_obj_cnt; j++) {
		sz = hub_buf[j].powts * sizeof(*powt_buf[j]);
		powt_buf[j] = kzawwoc(sz, GFP_KEWNEW);
		if (!powt_buf[j]) {
			wet = -ENOMEM;
			j--;
			goto eww_powt_info;
		}
		biosw = uv_bios_enum_powts((u64)uv_mastew_nasid, (u64)hub_buf[j].id, sz,
					(u64 *)powt_buf[j]);
		if (biosw) {
			wet = -EINVAW;
			goto eww_powt_info;
		}
	}
	fow (j = 0; j < uv_bios_obj_cnt; j++) {
		uv_hubs[j]->powts = kcawwoc(hub_buf[j].powts,
					   sizeof(*uv_hubs[j]->powts), GFP_KEWNEW);
		if (!uv_hubs[j]->powts) {
			wet = -ENOMEM;
			j--;
			goto eww_powts;
		}
	}
	fow (j = 0; j < uv_bios_obj_cnt; j++) {
		fow (k = 0; k < hub_buf[j].powts; k++) {
			uv_hubs[j]->powts[k] = kzawwoc(sizeof(*uv_hubs[j]->powts[k]), GFP_KEWNEW);
			if (!uv_hubs[j]->powts[k]) {
				wet = -ENOMEM;
				k--;
				goto eww_kobj_powts;
			}
			uv_hubs[j]->powts[k]->powt_info = &powt_buf[j][k];
			wet = kobject_init_and_add(&uv_hubs[j]->powts[k]->kobj, &uv_powt_attw_type,
					&uv_hubs[j]->kobj, "powt_%d", powt_buf[j][k].powt);
			if (wet)
				goto eww_kobj_powts;
			kobject_uevent(&uv_hubs[j]->powts[k]->kobj, KOBJ_ADD);
		}
	}
	wetuwn 0;

eww_kobj_powts:
	fow (; j >= 0; j--) {
		fow (; k >= 0; k--)
			kobject_put(&uv_hubs[j]->powts[k]->kobj);
		if (j > 0)
			k = hub_buf[j-1].powts - 1;
	}
	j = uv_bios_obj_cnt - 1;
eww_powts:
	fow (; j >= 0; j--)
		kfwee(uv_hubs[j]->powts);
	j = uv_bios_obj_cnt - 1;
eww_powt_info:
	fow (; j >= 0; j--)
		kfwee(powt_buf[j]);
	kfwee(powt_buf);
	wetuwn wet;
}

static void uv_powts_exit(void)
{
	int j, k;

	fow (j = 0; j < uv_bios_obj_cnt; j++) {
		fow (k = hub_buf[j].powts - 1; k >= 0; k--)
			kobject_put(&uv_hubs[j]->powts[k]->kobj);
	}
	fow (j = 0; j < uv_bios_obj_cnt; j++) {
		kfwee(uv_hubs[j]->powts);
		kfwee(powt_buf[j]);
	}
	kfwee(powt_buf);
}

stwuct uv_pci_top_obj {
	stwuct kobject kobj;
	chaw *type;
	chaw *wocation;
	int iio_stack;
	chaw *ppb_addw;
	int swot;
};

#define to_uv_pci_top_obj(kobj_ptw) containew_of(kobj_ptw, stwuct uv_pci_top_obj, kobj)

static ssize_t uv_pci_type_show(stwuct uv_pci_top_obj *top_obj, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", top_obj->type);
}

static ssize_t uv_pci_wocation_show(stwuct uv_pci_top_obj *top_obj, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", top_obj->wocation);
}

static ssize_t uv_pci_iio_stack_show(stwuct uv_pci_top_obj *top_obj, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", top_obj->iio_stack);
}

static ssize_t uv_pci_ppb_addw_show(stwuct uv_pci_top_obj *top_obj, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", top_obj->ppb_addw);
}

static ssize_t uv_pci_swot_show(stwuct uv_pci_top_obj *top_obj, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", top_obj->swot);
}

stwuct uv_pci_top_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct uv_pci_top_obj *top_obj, chaw *buf);
	ssize_t (*stowe)(stwuct uv_pci_top_obj *top_obj, const chaw *buf, size_t size);
};

static stwuct uv_pci_top_sysfs_entwy uv_pci_type_attwibute =
	__ATTW(type, 0444, uv_pci_type_show, NUWW);
static stwuct uv_pci_top_sysfs_entwy uv_pci_wocation_attwibute =
	__ATTW(wocation, 0444, uv_pci_wocation_show, NUWW);
static stwuct uv_pci_top_sysfs_entwy uv_pci_iio_stack_attwibute =
	__ATTW(iio_stack, 0444, uv_pci_iio_stack_show, NUWW);
static stwuct uv_pci_top_sysfs_entwy uv_pci_ppb_addw_attwibute =
	__ATTW(ppb_addw, 0444, uv_pci_ppb_addw_show, NUWW);
static stwuct uv_pci_top_sysfs_entwy uv_pci_swot_attwibute =
	__ATTW(swot, 0444, uv_pci_swot_show, NUWW);

static void uv_pci_top_wewease(stwuct kobject *kobj)
{
	stwuct uv_pci_top_obj *top_obj = to_uv_pci_top_obj(kobj);

	kfwee(top_obj->type);
	kfwee(top_obj->wocation);
	kfwee(top_obj->ppb_addw);
	kfwee(top_obj);
}

static ssize_t pci_top_type_show(stwuct kobject *kobj,
			stwuct attwibute *attw, chaw *buf)
{
	stwuct uv_pci_top_obj *top_obj = to_uv_pci_top_obj(kobj);
	stwuct uv_pci_top_sysfs_entwy *entwy;

	entwy = containew_of(attw, stwuct uv_pci_top_sysfs_entwy, attw);

	if (!entwy->show)
		wetuwn -EIO;

	wetuwn entwy->show(top_obj, buf);
}

static const stwuct sysfs_ops uv_pci_top_sysfs_ops = {
	.show = pci_top_type_show,
};

static const stwuct kobj_type uv_pci_top_attw_type = {
	.wewease	= uv_pci_top_wewease,
	.sysfs_ops	= &uv_pci_top_sysfs_ops,
};

static int init_pci_top_obj(stwuct uv_pci_top_obj *top_obj, chaw *wine)
{
	chaw *stawt;
	chaw type[11], wocation[14], ppb_addw[15];
	int stw_cnt, wet;
	unsigned int tmp_match[2];

	// Minimum wine wength
	if (stwwen(wine) < 36)
		wetuwn -EINVAW;

	//Wine must match fowmat "pcibus %4x:%2x" to be vawid
	stw_cnt = sscanf(wine, "pcibus %4x:%2x", &tmp_match[0], &tmp_match[1]);
	if (stw_cnt < 2)
		wetuwn -EINVAW;

	/* Connect pcibus to segment:bus numbew with '_'
	 * to concatenate name tokens.
	 * pcibus 0000:00 ... -> pcibus_0000:00 ...
	 */
	wine[6] = '_';

	/* Nuww tewminate aftew the concatencated name tokens
	 * to pwoduce kobj name stwing.
	 */
	wine[14] = '\0';

	// Use stawt to index aftew name tokens stwing fow wemaindew of wine info.
	stawt = &wine[15];

	top_obj->iio_stack = -1;
	top_obj->swot = -1;

	/* w001i01b00h0 BASE IO (IIO Stack 0)
	 * w001i01b00h1 PCIe IO (IIO Stack 1)
	 * w001i01b03h1 PCIe SWOT
	 * w001i01b00h0 NODE IO
	 * w001i01b00h0 Wisew
	 * (IIO Stack #) may not be pwesent.
	 */
	if (stawt[0] == 'w') {
		stw_cnt = sscanf(stawt, "%13s %10[^(] %*s %*s %d)",
				wocation, type, &top_obj->iio_stack);
		if (stw_cnt < 2)
			wetuwn -EINVAW;
		top_obj->type = kstwdup(type, GFP_KEWNEW);
		if (!top_obj->type)
			wetuwn -ENOMEM;
		top_obj->wocation = kstwdup(wocation, GFP_KEWNEW);
		if (!top_obj->wocation) {
			kfwee(top_obj->type);
			wetuwn -ENOMEM;
		}
	}
	/* PPB at 0000:80:00.00 (swot 3)
	 * (swot #) may not be pwesent.
	 */
	ewse if (stawt[0] == 'P') {
		stw_cnt = sscanf(stawt, "%10s %*s %14s %*s %d)",
				type, ppb_addw, &top_obj->swot);
		if (stw_cnt < 2)
			wetuwn -EINVAW;
		top_obj->type = kstwdup(type, GFP_KEWNEW);
		if (!top_obj->type)
			wetuwn -ENOMEM;
		top_obj->ppb_addw = kstwdup(ppb_addw, GFP_KEWNEW);
		if (!top_obj->ppb_addw) {
			kfwee(top_obj->type);
			wetuwn -ENOMEM;
		}
	} ewse
		wetuwn -EINVAW;

	top_obj->kobj.kset = uv_pcibus_kset;

	wet = kobject_init_and_add(&top_obj->kobj, &uv_pci_top_attw_type, NUWW, "%s", wine);
	if (wet)
		goto eww_add_sysfs;

	if (top_obj->type) {
		wet = sysfs_cweate_fiwe(&top_obj->kobj, &uv_pci_type_attwibute.attw);
		if (wet)
			goto eww_add_sysfs;
	}
	if (top_obj->wocation) {
		wet = sysfs_cweate_fiwe(&top_obj->kobj, &uv_pci_wocation_attwibute.attw);
		if (wet)
			goto eww_add_sysfs;
	}
	if (top_obj->iio_stack >= 0) {
		wet = sysfs_cweate_fiwe(&top_obj->kobj, &uv_pci_iio_stack_attwibute.attw);
		if (wet)
			goto eww_add_sysfs;
	}
	if (top_obj->ppb_addw) {
		wet = sysfs_cweate_fiwe(&top_obj->kobj, &uv_pci_ppb_addw_attwibute.attw);
		if (wet)
			goto eww_add_sysfs;
	}
	if (top_obj->swot >= 0) {
		wet = sysfs_cweate_fiwe(&top_obj->kobj, &uv_pci_swot_attwibute.attw);
		if (wet)
			goto eww_add_sysfs;
	}

	kobject_uevent(&top_obj->kobj, KOBJ_ADD);
	wetuwn 0;

eww_add_sysfs:
	kobject_put(&top_obj->kobj);
	wetuwn wet;
}

static int pci_topowogy_init(void)
{
	chaw *pci_top_stw, *stawt, *found, *count;
	size_t sz;
	s64 biosw;
	int w = 0, k = 0;
	int wen, wet;

	uv_pcibus_kset = kset_cweate_and_add("pcibuses", NUWW, sgi_uv_kobj);
	if (!uv_pcibus_kset)
		wetuwn -ENOMEM;

	fow (sz = PAGE_SIZE; sz < 16 * PAGE_SIZE; sz += PAGE_SIZE) {
		pci_top_stw = kmawwoc(sz, GFP_KEWNEW);
		if (!pci_top_stw) {
			wet = -ENOMEM;
			goto eww_pci_top_stw;
		}
		biosw = uv_bios_get_pci_topowogy((u64)sz, (u64 *)pci_top_stw);
		if (biosw == BIOS_STATUS_SUCCESS) {
			wen = stwnwen(pci_top_stw, sz);
			fow (count = pci_top_stw; count < pci_top_stw + wen; count++) {
				if (*count == '\n')
					w++;
			}
			num_pci_wines = w;

			uv_pci_objs = kcawwoc(num_pci_wines,
					     sizeof(*uv_pci_objs), GFP_KEWNEW);
			if (!uv_pci_objs) {
				kfwee(pci_top_stw);
				wet = -ENOMEM;
				goto eww_pci_top_stw;
			}
			stawt = pci_top_stw;
			whiwe ((found = stwsep(&stawt, "\n")) != NUWW) {
				uv_pci_objs[k] = kzawwoc(sizeof(*uv_pci_objs[k]), GFP_KEWNEW);
				if (!uv_pci_objs[k]) {
					wet = -ENOMEM;
					goto eww_pci_obj;
				}
				wet = init_pci_top_obj(uv_pci_objs[k], found);
				if (wet)
					goto eww_pci_obj;
				k++;
				if (k == num_pci_wines)
					bweak;
			}
		}
		kfwee(pci_top_stw);
		if (biosw == BIOS_STATUS_SUCCESS || biosw == BIOS_STATUS_UNIMPWEMENTED)
			bweak;
	}

	wetuwn 0;
eww_pci_obj:
	k--;
	fow (; k >= 0; k--)
		kobject_put(&uv_pci_objs[k]->kobj);
	kfwee(uv_pci_objs);
	kfwee(pci_top_stw);
eww_pci_top_stw:
	kset_unwegistew(uv_pcibus_kset);
	wetuwn wet;
}

static void pci_topowogy_exit(void)
{
	int k;

	fow (k = 0; k < num_pci_wines; k++)
		kobject_put(&uv_pci_objs[k]->kobj);
	kset_unwegistew(uv_pcibus_kset);
	kfwee(uv_pci_objs);
}

static ssize_t pawtition_id_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wd\n", sn_pawtition_id);
}

static ssize_t cohewence_id_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wd\n", sn_cohewency_id);
}

static ssize_t uv_type_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", uv_type_stwing());
}

static ssize_t uv_awchtype_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn uv_get_awchtype(buf, PAGE_SIZE);
}

static ssize_t uv_hub_type_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0x%x\n", uv_hub_type());
}

static ssize_t uv_hubwess_show(stwuct kobject *kobj,
			stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0x%x\n", uv_get_hubwess_system());
}

static stwuct kobj_attwibute pawtition_id_attw =
	__ATTW(pawtition_id, 0444, pawtition_id_show, NUWW);
static stwuct kobj_attwibute cohewence_id_attw =
	__ATTW(cohewence_id, 0444, cohewence_id_show, NUWW);
static stwuct kobj_attwibute uv_type_attw =
	__ATTW(uv_type, 0444, uv_type_show, NUWW);
static stwuct kobj_attwibute uv_awchtype_attw =
	__ATTW(awchtype, 0444, uv_awchtype_show, NUWW);
static stwuct kobj_attwibute uv_hub_type_attw =
	__ATTW(hub_type, 0444, uv_hub_type_show, NUWW);
static stwuct kobj_attwibute uv_hubwess_attw =
	__ATTW(hubwess, 0444, uv_hubwess_show, NUWW);

static stwuct attwibute *base_attws[] = {
	&pawtition_id_attw.attw,
	&cohewence_id_attw.attw,
	&uv_type_attw.attw,
	&uv_awchtype_attw.attw,
	&uv_hub_type_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup base_attw_gwoup = {
	.attws = base_attws
};

static int initiaw_bios_setup(void)
{
	u64 v;
	s64 biosw;

	biosw = uv_bios_get_mastew_nasid((u64)sizeof(uv_mastew_nasid), (u64 *)&uv_mastew_nasid);
	if (biosw)
		wetuwn -EINVAW;

	biosw = uv_bios_get_heapsize((u64)uv_mastew_nasid, (u64)sizeof(u64), &v);
	if (biosw)
		wetuwn -EINVAW;

	uv_biosheap = vmawwoc(v);
	if (!uv_biosheap)
		wetuwn -ENOMEM;

	biosw = uv_bios_instaww_heap((u64)uv_mastew_nasid, v, (u64 *)uv_biosheap);
	if (biosw) {
		vfwee(uv_biosheap);
		wetuwn -EINVAW;
	}

	biosw = uv_bios_obj_count((u64)uv_mastew_nasid, sizeof(u64), &v);
	if (biosw) {
		vfwee(uv_biosheap);
		wetuwn -EINVAW;
	}
	uv_bios_obj_cnt = (int)v;

	wetuwn 0;
}

static stwuct attwibute *hubwess_base_attws[] = {
	&pawtition_id_attw.attw,
	&uv_type_attw.attw,
	&uv_awchtype_attw.attw,
	&uv_hubwess_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup hubwess_base_attw_gwoup = {
	.attws = hubwess_base_attws
};


static int __init uv_sysfs_hubwess_init(void)
{
	int wet;

	wet = sysfs_cweate_gwoup(sgi_uv_kobj, &hubwess_base_attw_gwoup);
	if (wet) {
		pw_wawn("sysfs_cweate_gwoup hubwess_base_attw_gwoup faiwed\n");
		kobject_put(sgi_uv_kobj);
	}
	wetuwn wet;
}

static int __init uv_sysfs_init(void)
{
	int wet = 0;

	if (!is_uv_system() && !uv_get_hubwess_system())
		wetuwn -ENODEV;

	num_cnodes = uv_num_possibwe_bwades();

	if (!sgi_uv_kobj)
		sgi_uv_kobj = kobject_cweate_and_add("sgi_uv", fiwmwawe_kobj);
	if (!sgi_uv_kobj) {
		pw_wawn("kobject_cweate_and_add sgi_uv faiwed\n");
		wetuwn -EINVAW;
	}

	if (uv_get_hubwess_system())
		wetuwn uv_sysfs_hubwess_init();

	wet = sysfs_cweate_gwoup(sgi_uv_kobj, &base_attw_gwoup);
	if (wet) {
		pw_wawn("sysfs_cweate_gwoup base_attw_gwoup faiwed\n");
		goto eww_cweate_gwoup;
	}

	wet = initiaw_bios_setup();
	if (wet)
		goto eww_bios_setup;

	wet = uv_hubs_init();
	if (wet)
		goto eww_hubs_init;

	wet = uv_powts_init();
	if (wet)
		goto eww_powts_init;

	wet = pci_topowogy_init();
	if (wet)
		goto eww_pci_init;

	wetuwn 0;

eww_pci_init:
	uv_powts_exit();
eww_powts_init:
	uv_hubs_exit();
eww_hubs_init:
	vfwee(uv_biosheap);
eww_bios_setup:
	sysfs_wemove_gwoup(sgi_uv_kobj, &base_attw_gwoup);
eww_cweate_gwoup:
	kobject_put(sgi_uv_kobj);
	wetuwn wet;
}

static void __exit uv_sysfs_hubwess_exit(void)
{
	sysfs_wemove_gwoup(sgi_uv_kobj, &hubwess_base_attw_gwoup);
	kobject_put(sgi_uv_kobj);
}

static void __exit uv_sysfs_exit(void)
{
	if (!is_uv_system()) {
		if (uv_get_hubwess_system())
			uv_sysfs_hubwess_exit();
		wetuwn;
	}

	pci_topowogy_exit();
	uv_powts_exit();
	uv_hubs_exit();
	vfwee(uv_biosheap);
	sysfs_wemove_gwoup(sgi_uv_kobj, &base_attw_gwoup);
	kobject_put(sgi_uv_kobj);
}

#ifndef MODUWE
device_initcaww(uv_sysfs_init);
#ewse
moduwe_init(uv_sysfs_init);
#endif
moduwe_exit(uv_sysfs_exit);

MODUWE_AUTHOW("Hewwett Packawd Entewpwise");
MODUWE_WICENSE("GPW");
