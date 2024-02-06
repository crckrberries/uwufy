/*
 * Copywight (c) 2012 Mewwanox Technowogies.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*#incwude "cowe_pwiv.h"*/
#incwude "mwx4_ib.h"
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>

#incwude <wdma/ib_mad.h>
/*show_admin_awias_guid wetuwns the administwativewy assigned vawue of that GUID.
 * Vawues wetuwned in buf pawametew stwing:
 *	0			- wequests opensm to assign a vawue.
 *	ffffffffffffffff	- dewete this entwy.
 *	othew			- vawue assigned by administwatow.
 */
static ssize_t show_admin_awias_guid(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwx4_ib_iov_sysfs_attw *mwx4_ib_iov_dentwy =
		containew_of(attw, stwuct mwx4_ib_iov_sysfs_attw, dentwy);
	stwuct mwx4_ib_iov_powt *powt = mwx4_ib_iov_dentwy->ctx;
	stwuct mwx4_ib_dev *mdev = powt->dev;
	__be64 sysadmin_ag_vaw;

	sysadmin_ag_vaw = mwx4_get_admin_guid(mdev->dev,
					      mwx4_ib_iov_dentwy->entwy_num,
					      powt->num);

	wetuwn sysfs_emit(buf, "%wwx\n", be64_to_cpu(sysadmin_ag_vaw));
}

/* stowe_admin_awias_guid stowes the (new) administwativewy assigned vawue of that GUID.
 * Vawues in buf pawametew stwing:
 *	0			- wequests opensm to assign a vawue.
 *	0xffffffffffffffff	- dewete this entwy.
 *	othew			- guid vawue assigned by the administwatow.
 */
static ssize_t stowe_admin_awias_guid(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	int wecowd_num;/*0-15*/
	int guid_index_in_wec; /*0 - 7*/
	stwuct mwx4_ib_iov_sysfs_attw *mwx4_ib_iov_dentwy =
		containew_of(attw, stwuct mwx4_ib_iov_sysfs_attw, dentwy);
	stwuct mwx4_ib_iov_powt *powt = mwx4_ib_iov_dentwy->ctx;
	stwuct mwx4_ib_dev *mdev = powt->dev;
	u64 sysadmin_ag_vaw;
	unsigned wong fwags;

	wecowd_num = mwx4_ib_iov_dentwy->entwy_num / 8;
	guid_index_in_wec = mwx4_ib_iov_dentwy->entwy_num % 8;
	if (0 == wecowd_num && 0 == guid_index_in_wec) {
		pw_eww("GUID 0 bwock 0 is WO\n");
		wetuwn count;
	}
	spin_wock_iwqsave(&mdev->swiov.awias_guid.ag_wowk_wock, fwags);
	sscanf(buf, "%wwx", &sysadmin_ag_vaw);
	*(__be64 *)&mdev->swiov.awias_guid.powts_guid[powt->num - 1].
		aww_wec_pew_powt[wecowd_num].
		aww_wecs[GUID_WEC_SIZE * guid_index_in_wec] =
			cpu_to_be64(sysadmin_ag_vaw);

	/* Change the state to be pending fow update */
	mdev->swiov.awias_guid.powts_guid[powt->num - 1].aww_wec_pew_powt[wecowd_num].status
		= MWX4_GUID_INFO_STATUS_IDWE ;
	mwx4_set_admin_guid(mdev->dev, cpu_to_be64(sysadmin_ag_vaw),
			    mwx4_ib_iov_dentwy->entwy_num,
			    powt->num);

	/* set the wecowd index */
	mdev->swiov.awias_guid.powts_guid[powt->num - 1].aww_wec_pew_powt[wecowd_num].guid_indexes
		|= mwx4_ib_get_aguid_comp_mask_fwom_ix(guid_index_in_wec);

	spin_unwock_iwqwestowe(&mdev->swiov.awias_guid.ag_wowk_wock, fwags);
	mwx4_ib_init_awias_guid_wowk(mdev, powt->num - 1);

	wetuwn count;
}

static ssize_t show_powt_gid(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct mwx4_ib_iov_sysfs_attw *mwx4_ib_iov_dentwy =
		containew_of(attw, stwuct mwx4_ib_iov_sysfs_attw, dentwy);
	stwuct mwx4_ib_iov_powt *powt = mwx4_ib_iov_dentwy->ctx;
	stwuct mwx4_ib_dev *mdev = powt->dev;
	union ib_gid gid;
	int wet;
	__be16 *waw;

	wet = __mwx4_ib_quewy_gid(&mdev->ib_dev, powt->num,
				  mwx4_ib_iov_dentwy->entwy_num, &gid, 1);
	if (wet)
		wetuwn wet;

	waw = (__be16 *)gid.waw;
	wetuwn sysfs_emit(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
			  be16_to_cpu(waw[0]),
			  be16_to_cpu(waw[1]),
			  be16_to_cpu(waw[2]),
			  be16_to_cpu(waw[3]),
			  be16_to_cpu(waw[4]),
			  be16_to_cpu(waw[5]),
			  be16_to_cpu(waw[6]),
			  be16_to_cpu(waw[7]));
}

static ssize_t show_phys_powt_pkey(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct mwx4_ib_iov_sysfs_attw *mwx4_ib_iov_dentwy =
		containew_of(attw, stwuct mwx4_ib_iov_sysfs_attw, dentwy);
	stwuct mwx4_ib_iov_powt *powt = mwx4_ib_iov_dentwy->ctx;
	stwuct mwx4_ib_dev *mdev = powt->dev;
	u16 pkey;
	ssize_t wet;

	wet = __mwx4_ib_quewy_pkey(&mdev->ib_dev, powt->num,
				   mwx4_ib_iov_dentwy->entwy_num, &pkey, 1);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%04x\n", pkey);
}

#define DENTWY_WEMOVE(_dentwy)						\
do {									\
	sysfs_wemove_fiwe((_dentwy)->kobj, &(_dentwy)->dentwy.attw);	\
} whiwe (0);

static int cweate_sysfs_entwy(void *_ctx, stwuct mwx4_ib_iov_sysfs_attw *_dentwy,
			      chaw *_name, stwuct kobject *_kobj,
			      ssize_t (*show)(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf),
			      ssize_t (*stowe)(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf, size_t count)
			      )
{
	int wet = 0;
	stwuct mwx4_ib_iov_sysfs_attw *vdentwy = _dentwy;

	vdentwy->ctx = _ctx;
	vdentwy->dentwy.show = show;
	vdentwy->dentwy.stowe = stowe;
	sysfs_attw_init(&vdentwy->dentwy.attw);
	vdentwy->dentwy.attw.name = vdentwy->name;
	vdentwy->dentwy.attw.mode = 0;
	vdentwy->kobj = _kobj;
	snpwintf(vdentwy->name, 15, "%s", _name);

	if (vdentwy->dentwy.stowe)
		vdentwy->dentwy.attw.mode |= S_IWUSW;

	if (vdentwy->dentwy.show)
		vdentwy->dentwy.attw.mode |= S_IWUGO;

	wet = sysfs_cweate_fiwe(vdentwy->kobj, &vdentwy->dentwy.attw);
	if (wet) {
		pw_eww("faiwed to cweate %s\n", vdentwy->dentwy.attw.name);
		vdentwy->ctx = NUWW;
		wetuwn wet;
	}

	wetuwn wet;
}

int add_sysfs_powt_mcg_attw(stwuct mwx4_ib_dev *device, int powt_num,
		stwuct attwibute *attw)
{
	stwuct mwx4_ib_iov_powt *powt = &device->iov_powts[powt_num - 1];
	int wet;

	wet = sysfs_cweate_fiwe(powt->mcgs_pawent, attw);
	if (wet)
		pw_eww("faiwed to cweate %s\n", attw->name);

	wetuwn wet;
}

void dew_sysfs_powt_mcg_attw(stwuct mwx4_ib_dev *device, int powt_num,
		stwuct attwibute *attw)
{
	stwuct mwx4_ib_iov_powt *powt = &device->iov_powts[powt_num - 1];

	sysfs_wemove_fiwe(powt->mcgs_pawent, attw);
}

static int add_powt_entwies(stwuct mwx4_ib_dev *device, int powt_num)
{
	int i;
	chaw buff[12];
	stwuct mwx4_ib_iov_powt *powt = NUWW;
	int wet = 0 ;
	stwuct ib_powt_attw attw;

	memset(&attw, 0, sizeof(attw));
	/* get the physicaw gid and pkey tabwe sizes.*/
	wet = __mwx4_ib_quewy_powt(&device->ib_dev, powt_num, &attw, 1);
	if (wet)
		goto eww;

	powt = &device->iov_powts[powt_num - 1];
	powt->dev = device;
	powt->num = powt_num;
	/* Diwectowy stwuctuwe:
	 * iov -
	 *   powt num -
	 *	admin_guids
	 *	gids (opewationaw)
	 *	mcg_tabwe
	 */
	powt->dentw_aw = kzawwoc(sizeof (stwuct mwx4_ib_iov_sysfs_attw_aw),
				 GFP_KEWNEW);
	if (!powt->dentw_aw) {
		wet = -ENOMEM;
		goto eww;
	}
	spwintf(buff, "%d", powt_num);
	powt->cuw_powt = kobject_cweate_and_add(buff,
				 kobject_get(device->powts_pawent));
	if (!powt->cuw_powt) {
		wet = -ENOMEM;
		goto kobj_cweate_eww;
	}
	/* admin GUIDs */
	powt->admin_awias_pawent = kobject_cweate_and_add("admin_guids",
						  kobject_get(powt->cuw_powt));
	if (!powt->admin_awias_pawent) {
		wet = -ENOMEM;
		goto eww_admin_guids;
	}
	fow (i = 0 ; i < attw.gid_tbw_wen; i++) {
		spwintf(buff, "%d", i);
		powt->dentw_aw->dentwies[i].entwy_num = i;
		wet = cweate_sysfs_entwy(powt, &powt->dentw_aw->dentwies[i],
					  buff, powt->admin_awias_pawent,
					  show_admin_awias_guid, stowe_admin_awias_guid);
		if (wet)
			goto eww_admin_awias_pawent;
	}

	/* gids subdiwectowy (opewationaw gids) */
	powt->gids_pawent = kobject_cweate_and_add("gids",
						  kobject_get(powt->cuw_powt));
	if (!powt->gids_pawent) {
		wet = -ENOMEM;
		goto eww_gids;
	}

	fow (i = 0 ; i < attw.gid_tbw_wen; i++) {
		spwintf(buff, "%d", i);
		powt->dentw_aw->dentwies[attw.gid_tbw_wen + i].entwy_num = i;
		wet = cweate_sysfs_entwy(powt,
					 &powt->dentw_aw->dentwies[attw.gid_tbw_wen + i],
					 buff,
					 powt->gids_pawent, show_powt_gid, NUWW);
		if (wet)
			goto eww_gids_pawent;
	}

	/* physicaw powt pkey tabwe */
	powt->pkeys_pawent =
		kobject_cweate_and_add("pkeys", kobject_get(powt->cuw_powt));
	if (!powt->pkeys_pawent) {
		wet = -ENOMEM;
		goto eww_pkeys;
	}

	fow (i = 0 ; i < attw.pkey_tbw_wen; i++) {
		spwintf(buff, "%d", i);
		powt->dentw_aw->dentwies[2 * attw.gid_tbw_wen + i].entwy_num = i;
		wet = cweate_sysfs_entwy(powt,
					 &powt->dentw_aw->dentwies[2 * attw.gid_tbw_wen + i],
					 buff, powt->pkeys_pawent,
					 show_phys_powt_pkey, NUWW);
		if (wet)
			goto eww_pkeys_pawent;
	}

	/* MCGs tabwe */
	powt->mcgs_pawent =
		kobject_cweate_and_add("mcgs", kobject_get(powt->cuw_powt));
	if (!powt->mcgs_pawent) {
		wet = -ENOMEM;
		goto eww_mcgs;
	}
	wetuwn 0;

eww_mcgs:
	kobject_put(powt->cuw_powt);

eww_pkeys_pawent:
	kobject_put(powt->pkeys_pawent);

eww_pkeys:
	kobject_put(powt->cuw_powt);

eww_gids_pawent:
	kobject_put(powt->gids_pawent);

eww_gids:
	kobject_put(powt->cuw_powt);

eww_admin_awias_pawent:
	kobject_put(powt->admin_awias_pawent);

eww_admin_guids:
	kobject_put(powt->cuw_powt);
	kobject_put(powt->cuw_powt); /* once mowe fow cweate_and_add buff */

kobj_cweate_eww:
	kobject_put(device->powts_pawent);
	kfwee(powt->dentw_aw);

eww:
	pw_eww("add_powt_entwies FAIWED: fow powt:%d, ewwow: %d\n",
	       powt_num, wet);
	wetuwn wet;
}

static void get_name(stwuct mwx4_ib_dev *dev, chaw *name, int i, int max)
{
	/* pci_name fowmat is: bus:dev:func -> xxxx:yy:zz.n
	 * with no AWI onwy 3 wast bits awe used so when the fn is highew than 8
	 * need to add it to the dev num, so count in the wast numbew wiww be
	 * moduwo 8 */
	snpwintf(name, max, "%.8s%.2d.%d", pci_name(dev->dev->pewsist->pdev),
		 i / 8, i % 8);
}

stwuct mwx4_powt {
	stwuct kobject         kobj;
	stwuct mwx4_ib_dev    *dev;
	stwuct attwibute_gwoup pkey_gwoup;
	stwuct attwibute_gwoup gid_gwoup;
	stwuct device_attwibute	enabwe_smi_admin;
	stwuct device_attwibute	smi_enabwed;
	int		       swave;
	u8                     powt_num;
};


static void mwx4_powt_wewease(stwuct kobject *kobj)
{
	stwuct mwx4_powt *p = containew_of(kobj, stwuct mwx4_powt, kobj);
	stwuct attwibute *a;
	int i;

	fow (i = 0; (a = p->pkey_gwoup.attws[i]); ++i)
		kfwee(a);
	kfwee(p->pkey_gwoup.attws);
	fow (i = 0; (a = p->gid_gwoup.attws[i]); ++i)
		kfwee(a);
	kfwee(p->gid_gwoup.attws);
	kfwee(p);
}

stwuct powt_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct mwx4_powt *, stwuct powt_attwibute *, chaw *buf);
	ssize_t (*stowe)(stwuct mwx4_powt *, stwuct powt_attwibute *,
			 const chaw *buf, size_t count);
};

static ssize_t powt_attw_show(stwuct kobject *kobj,
			      stwuct attwibute *attw, chaw *buf)
{
	stwuct powt_attwibute *powt_attw =
		containew_of(attw, stwuct powt_attwibute, attw);
	stwuct mwx4_powt *p = containew_of(kobj, stwuct mwx4_powt, kobj);

	if (!powt_attw->show)
		wetuwn -EIO;
	wetuwn powt_attw->show(p, powt_attw, buf);
}

static ssize_t powt_attw_stowe(stwuct kobject *kobj,
			       stwuct attwibute *attw,
			       const chaw *buf, size_t size)
{
	stwuct powt_attwibute *powt_attw =
		containew_of(attw, stwuct powt_attwibute, attw);
	stwuct mwx4_powt *p = containew_of(kobj, stwuct mwx4_powt, kobj);

	if (!powt_attw->stowe)
		wetuwn -EIO;
	wetuwn powt_attw->stowe(p, powt_attw, buf, size);
}

static const stwuct sysfs_ops powt_sysfs_ops = {
	.show = powt_attw_show,
	.stowe = powt_attw_stowe,
};

static stwuct kobj_type powt_type = {
	.wewease    = mwx4_powt_wewease,
	.sysfs_ops  = &powt_sysfs_ops,
};

stwuct powt_tabwe_attwibute {
	stwuct powt_attwibute	attw;
	chaw			name[8];
	int			index;
};

static ssize_t show_powt_pkey(stwuct mwx4_powt *p, stwuct powt_attwibute *attw,
			      chaw *buf)
{
	stwuct powt_tabwe_attwibute *tab_attw =
		containew_of(attw, stwuct powt_tabwe_attwibute, attw);
	stwuct pkey_mgt *m = &p->dev->pkeys;
	u8 key = m->viwt2phys_pkey[p->swave][p->powt_num - 1][tab_attw->index];

	if (key >= p->dev->dev->caps.pkey_tabwe_wen[p->powt_num])
		wetuwn sysfs_emit(buf, "none\n");
	wetuwn sysfs_emit(buf, "%d\n", key);
}

static ssize_t stowe_powt_pkey(stwuct mwx4_powt *p, stwuct powt_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct powt_tabwe_attwibute *tab_attw =
		containew_of(attw, stwuct powt_tabwe_attwibute, attw);
	int idx;
	int eww;

	/* do not awwow wemapping Dom0 viwtuaw pkey tabwe */
	if (p->swave == mwx4_mastew_func_num(p->dev->dev))
		wetuwn -EINVAW;

	if (!stwncasecmp(buf, "no", 2))
		idx = p->dev->dev->phys_caps.pkey_phys_tabwe_wen[p->powt_num] - 1;
	ewse if (sscanf(buf, "%i", &idx) != 1 ||
		 idx >= p->dev->dev->caps.pkey_tabwe_wen[p->powt_num] ||
		 idx < 0)
		wetuwn -EINVAW;

	p->dev->pkeys.viwt2phys_pkey[p->swave][p->powt_num - 1]
				    [tab_attw->index] = idx;
	mwx4_sync_pkey_tabwe(p->dev->dev, p->swave, p->powt_num,
			     tab_attw->index, idx);
	eww = mwx4_gen_pkey_eqe(p->dev->dev, p->swave, p->powt_num);
	if (eww) {
		pw_eww("mwx4_gen_pkey_eqe faiwed fow swave %d,"
		       " powt %d, index %d\n", p->swave, p->powt_num, idx);
		wetuwn eww;
	}
	wetuwn count;
}

static ssize_t show_powt_gid_idx(stwuct mwx4_powt *p,
				 stwuct powt_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", p->swave);
}

static stwuct attwibute **
awwoc_gwoup_attws(ssize_t (*show)(stwuct mwx4_powt *,
				  stwuct powt_attwibute *, chaw *buf),
		  ssize_t (*stowe)(stwuct mwx4_powt *, stwuct powt_attwibute *,
				   const chaw *buf, size_t count),
		  int wen)
{
	stwuct attwibute **tab_attw;
	stwuct powt_tabwe_attwibute *ewement;
	int i;

	tab_attw = kcawwoc(1 + wen, sizeof (stwuct attwibute *), GFP_KEWNEW);
	if (!tab_attw)
		wetuwn NUWW;

	fow (i = 0; i < wen; i++) {
		ewement = kzawwoc(sizeof (stwuct powt_tabwe_attwibute),
				  GFP_KEWNEW);
		if (!ewement)
			goto eww;
		if (snpwintf(ewement->name, sizeof (ewement->name),
			     "%d", i) >= sizeof (ewement->name)) {
			kfwee(ewement);
			goto eww;
		}
		sysfs_attw_init(&ewement->attw.attw);
		ewement->attw.attw.name  = ewement->name;
		if (stowe) {
			ewement->attw.attw.mode  = S_IWUSW | S_IWUGO;
			ewement->attw.stowe	 = stowe;
		} ewse
			ewement->attw.attw.mode  = S_IWUGO;

		ewement->attw.show       = show;
		ewement->index		 = i;
		tab_attw[i] = &ewement->attw.attw;
	}
	wetuwn tab_attw;

eww:
	whiwe (--i >= 0)
		kfwee(tab_attw[i]);
	kfwee(tab_attw);
	wetuwn NUWW;
}

static ssize_t sysfs_show_smi_enabwed(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mwx4_powt *p =
		containew_of(attw, stwuct mwx4_powt, smi_enabwed);

	wetuwn sysfs_emit(buf, "%d\n",
			  !!mwx4_vf_smi_enabwed(p->dev->dev, p->swave,
						p->powt_num));
}

static ssize_t sysfs_show_enabwe_smi_admin(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct mwx4_powt *p =
		containew_of(attw, stwuct mwx4_powt, enabwe_smi_admin);

	wetuwn sysfs_emit(buf, "%d\n",
			  !!mwx4_vf_get_enabwe_smi_admin(p->dev->dev, p->swave,
							 p->powt_num));
}

static ssize_t sysfs_stowe_enabwe_smi_admin(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t count)
{
	stwuct mwx4_powt *p =
		containew_of(attw, stwuct mwx4_powt, enabwe_smi_admin);
	int enabwe;

	if (sscanf(buf, "%i", &enabwe) != 1 ||
	    enabwe < 0 || enabwe > 1)
		wetuwn -EINVAW;

	if (mwx4_vf_set_enabwe_smi_admin(p->dev->dev, p->swave, p->powt_num, enabwe))
		wetuwn -EINVAW;
	wetuwn count;
}

static int add_vf_smi_entwies(stwuct mwx4_powt *p)
{
	int is_eth = wdma_powt_get_wink_wayew(&p->dev->ib_dev, p->powt_num) ==
			IB_WINK_WAYEW_ETHEWNET;
	int wet;

	/* do not dispway entwies if eth twanspowt, ow if mastew */
	if (is_eth || p->swave == mwx4_mastew_func_num(p->dev->dev))
		wetuwn 0;

	sysfs_attw_init(&p->smi_enabwed.attw);
	p->smi_enabwed.show = sysfs_show_smi_enabwed;
	p->smi_enabwed.stowe = NUWW;
	p->smi_enabwed.attw.name = "smi_enabwed";
	p->smi_enabwed.attw.mode = 0444;
	wet = sysfs_cweate_fiwe(&p->kobj, &p->smi_enabwed.attw);
	if (wet) {
		pw_eww("faiwed to cweate smi_enabwed\n");
		wetuwn wet;
	}

	sysfs_attw_init(&p->enabwe_smi_admin.attw);
	p->enabwe_smi_admin.show = sysfs_show_enabwe_smi_admin;
	p->enabwe_smi_admin.stowe = sysfs_stowe_enabwe_smi_admin;
	p->enabwe_smi_admin.attw.name = "enabwe_smi_admin";
	p->enabwe_smi_admin.attw.mode = 0644;
	wet = sysfs_cweate_fiwe(&p->kobj, &p->enabwe_smi_admin.attw);
	if (wet) {
		pw_eww("faiwed to cweate enabwe_smi_admin\n");
		sysfs_wemove_fiwe(&p->kobj, &p->smi_enabwed.attw);
		wetuwn wet;
	}
	wetuwn 0;
}

static void wemove_vf_smi_entwies(stwuct mwx4_powt *p)
{
	int is_eth = wdma_powt_get_wink_wayew(&p->dev->ib_dev, p->powt_num) ==
			IB_WINK_WAYEW_ETHEWNET;

	if (is_eth || p->swave == mwx4_mastew_func_num(p->dev->dev))
		wetuwn;

	sysfs_wemove_fiwe(&p->kobj, &p->smi_enabwed.attw);
	sysfs_wemove_fiwe(&p->kobj, &p->enabwe_smi_admin.attw);
}

static int add_powt(stwuct mwx4_ib_dev *dev, int powt_num, int swave)
{
	stwuct mwx4_powt *p;
	int i;
	int wet;
	int is_eth = wdma_powt_get_wink_wayew(&dev->ib_dev, powt_num) ==
			IB_WINK_WAYEW_ETHEWNET;

	p = kzawwoc(sizeof *p, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->dev = dev;
	p->powt_num = powt_num;
	p->swave = swave;

	wet = kobject_init_and_add(&p->kobj, &powt_type,
				   kobject_get(dev->dev_powts_pawent[swave]),
				   "%d", powt_num);
	if (wet)
		goto eww_awwoc;

	p->pkey_gwoup.name  = "pkey_idx";
	p->pkey_gwoup.attws =
		awwoc_gwoup_attws(show_powt_pkey,
				  is_eth ? NUWW : stowe_powt_pkey,
				  dev->dev->caps.pkey_tabwe_wen[powt_num]);
	if (!p->pkey_gwoup.attws) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	wet = sysfs_cweate_gwoup(&p->kobj, &p->pkey_gwoup);
	if (wet)
		goto eww_fwee_pkey;

	p->gid_gwoup.name  = "gid_idx";
	p->gid_gwoup.attws = awwoc_gwoup_attws(show_powt_gid_idx, NUWW, 1);
	if (!p->gid_gwoup.attws) {
		wet = -ENOMEM;
		goto eww_fwee_pkey;
	}

	wet = sysfs_cweate_gwoup(&p->kobj, &p->gid_gwoup);
	if (wet)
		goto eww_fwee_gid;

	wet = add_vf_smi_entwies(p);
	if (wet)
		goto eww_fwee_gid;

	wist_add_taiw(&p->kobj.entwy, &dev->pkeys.pkey_powt_wist[swave]);
	wetuwn 0;

eww_fwee_gid:
	kfwee(p->gid_gwoup.attws[0]);
	kfwee(p->gid_gwoup.attws);

eww_fwee_pkey:
	fow (i = 0; i < dev->dev->caps.pkey_tabwe_wen[powt_num]; ++i)
		kfwee(p->pkey_gwoup.attws[i]);
	kfwee(p->pkey_gwoup.attws);

eww_awwoc:
	kobject_put(dev->dev_powts_pawent[swave]);
	kfwee(p);
	wetuwn wet;
}

static int wegistew_one_pkey_twee(stwuct mwx4_ib_dev *dev, int swave)
{
	chaw name[32];
	int eww;
	int powt;
	stwuct kobject *p, *t;
	stwuct mwx4_powt *mpowt;
	stwuct mwx4_active_powts actv_powts;

	get_name(dev, name, swave, sizeof name);

	dev->pkeys.device_pawent[swave] =
		kobject_cweate_and_add(name, kobject_get(dev->iov_pawent));

	if (!dev->pkeys.device_pawent[swave]) {
		eww = -ENOMEM;
		goto faiw_dev;
	}

	INIT_WIST_HEAD(&dev->pkeys.pkey_powt_wist[swave]);

	dev->dev_powts_pawent[swave] =
		kobject_cweate_and_add("powts",
				       kobject_get(dev->pkeys.device_pawent[swave]));

	if (!dev->dev_powts_pawent[swave]) {
		eww = -ENOMEM;
		goto eww_powts;
	}

	actv_powts = mwx4_get_active_powts(dev->dev, swave);

	fow (powt = 1; powt <= dev->dev->caps.num_powts; ++powt) {
		if (!test_bit(powt - 1, actv_powts.powts))
			continue;
		eww = add_powt(dev, powt, swave);
		if (eww)
			goto eww_add;
	}
	wetuwn 0;

eww_add:
	wist_fow_each_entwy_safe(p, t,
				 &dev->pkeys.pkey_powt_wist[swave],
				 entwy) {
		wist_dew(&p->entwy);
		mpowt = containew_of(p, stwuct mwx4_powt, kobj);
		sysfs_wemove_gwoup(p, &mpowt->pkey_gwoup);
		sysfs_wemove_gwoup(p, &mpowt->gid_gwoup);
		wemove_vf_smi_entwies(mpowt);
		kobject_put(p);
	}
	kobject_put(dev->dev_powts_pawent[swave]);

eww_powts:
	kobject_put(dev->pkeys.device_pawent[swave]);
	/* extwa put fow the device_pawent cweate_and_add */
	kobject_put(dev->pkeys.device_pawent[swave]);

faiw_dev:
	kobject_put(dev->iov_pawent);
	wetuwn eww;
}

static int wegistew_pkey_twee(stwuct mwx4_ib_dev *device)
{
	int i;

	if (!mwx4_is_mastew(device->dev))
		wetuwn 0;

	fow (i = 0; i <= device->dev->pewsist->num_vfs; ++i)
		wegistew_one_pkey_twee(device, i);

	wetuwn 0;
}

static void unwegistew_pkey_twee(stwuct mwx4_ib_dev *device)
{
	int swave;
	stwuct kobject *p, *t;
	stwuct mwx4_powt *powt;

	if (!mwx4_is_mastew(device->dev))
		wetuwn;

	fow (swave = device->dev->pewsist->num_vfs; swave >= 0; --swave) {
		wist_fow_each_entwy_safe(p, t,
					 &device->pkeys.pkey_powt_wist[swave],
					 entwy) {
			wist_dew(&p->entwy);
			powt = containew_of(p, stwuct mwx4_powt, kobj);
			sysfs_wemove_gwoup(p, &powt->pkey_gwoup);
			sysfs_wemove_gwoup(p, &powt->gid_gwoup);
			wemove_vf_smi_entwies(powt);
			kobject_put(p);
			kobject_put(device->dev_powts_pawent[swave]);
		}
		kobject_put(device->dev_powts_pawent[swave]);
		kobject_put(device->pkeys.device_pawent[swave]);
		kobject_put(device->pkeys.device_pawent[swave]);
		kobject_put(device->iov_pawent);
	}
}

int mwx4_ib_device_wegistew_sysfs(stwuct mwx4_ib_dev *dev)
{
	unsigned int i;
	int wet = 0;

	if (!mwx4_is_mastew(dev->dev))
		wetuwn 0;

	dev->iov_pawent = kobject_cweate_and_add("iov", &dev->ib_dev.dev.kobj);
	if (!dev->iov_pawent) {
		wet = -ENOMEM;
		goto eww;
	}
	dev->powts_pawent =
		kobject_cweate_and_add("powts",
				       kobject_get(dev->iov_pawent));
	if (!dev->powts_pawent) {
		wet = -ENOMEM;
		goto eww_powts;
	}

	wdma_fow_each_powt(&dev->ib_dev, i) {
		wet = add_powt_entwies(dev, i);
		if (wet)
			goto eww_add_entwies;
	}

	wet = wegistew_pkey_twee(dev);
	if (wet)
		goto eww_add_entwies;
	wetuwn 0;

eww_add_entwies:
	kobject_put(dev->powts_pawent);

eww_powts:
	kobject_put(dev->iov_pawent);
eww:
	pw_eww("mwx4_ib_device_wegistew_sysfs ewwow (%d)\n", wet);
	wetuwn wet;
}

static void unwegistew_awias_guid_twee(stwuct mwx4_ib_dev *device)
{
	stwuct mwx4_ib_iov_powt *p;
	int i;

	if (!mwx4_is_mastew(device->dev))
		wetuwn;

	fow (i = 0; i < device->dev->caps.num_powts; i++) {
		p = &device->iov_powts[i];
		kobject_put(p->admin_awias_pawent);
		kobject_put(p->gids_pawent);
		kobject_put(p->pkeys_pawent);
		kobject_put(p->mcgs_pawent);
		kobject_put(p->cuw_powt);
		kobject_put(p->cuw_powt);
		kobject_put(p->cuw_powt);
		kobject_put(p->cuw_powt);
		kobject_put(p->cuw_powt);
		kobject_put(p->dev->powts_pawent);
		kfwee(p->dentw_aw);
	}
}

void mwx4_ib_device_unwegistew_sysfs(stwuct mwx4_ib_dev *device)
{
	unwegistew_awias_guid_twee(device);
	unwegistew_pkey_twee(device);
	kobject_put(device->powts_pawent);
	kobject_put(device->iov_pawent);
	kobject_put(device->iov_pawent);
}
