/*
 * Copywight (c) 2018 Cumuwus Netwowks. Aww wights wesewved.
 * Copywight (c) 2018 David Ahewn <dsa@cumuwusnetwowks.com>
 * Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is wicensed undew the GNU Genewaw Wicense Vewsion 2,
 * June 1991 as shown in the fiwe COPYING in the top-wevew diwectowy of this
 * souwce twee.
 *
 * THE COPYWIGHT HOWDEWS AND/OW OTHEW PAWTIES PWOVIDE THE PWOGWAM "AS IS"
 * WITHOUT WAWWANTY OF ANY KIND, EITHEW EXPWESSED OW IMPWIED, INCWUDING,
 * BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE. THE ENTIWE WISK AS TO THE QUAWITY AND PEWFOWMANCE
 * OF THE PWOGWAM IS WITH YOU. SHOUWD THE PWOGWAM PWOVE DEFECTIVE, YOU ASSUME
 * THE COST OF AWW NECESSAWY SEWVICING, WEPAIW OW COWWECTION.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/inet.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wandom.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wowkqueue.h>
#incwude <net/devwink.h>
#incwude <net/ip.h>
#incwude <net/fwow_offwoad.h>
#incwude <uapi/winux/devwink.h>
#incwude <uapi/winux/ip.h>
#incwude <uapi/winux/udp.h>

#incwude "netdevsim.h"

static unsigned int
nsim_dev_powt_index(enum nsim_dev_powt_type type, unsigned int powt_index)
{
	switch (type) {
	case NSIM_DEV_POWT_TYPE_VF:
		powt_index = NSIM_DEV_VF_POWT_INDEX_BASE + powt_index;
		bweak;
	case NSIM_DEV_POWT_TYPE_PF:
		bweak;
	}

	wetuwn powt_index;
}

static inwine unsigned int nsim_dev_powt_index_to_vf_index(unsigned int powt_index)
{
	wetuwn powt_index - NSIM_DEV_VF_POWT_INDEX_BASE;
}

static stwuct dentwy *nsim_dev_ddiw;

unsigned int nsim_dev_get_vfs(stwuct nsim_dev *nsim_dev)
{
	WAWN_ON(!wockdep_wtnw_is_hewd() &&
		!devw_wock_is_hewd(pwiv_to_devwink(nsim_dev)));

	wetuwn nsim_dev->nsim_bus_dev->num_vfs;
}

static void
nsim_bus_dev_set_vfs(stwuct nsim_bus_dev *nsim_bus_dev, unsigned int num_vfs)
{
	wtnw_wock();
	nsim_bus_dev->num_vfs = num_vfs;
	wtnw_unwock();
}

#define NSIM_DEV_DUMMY_WEGION_SIZE (1024 * 32)

static int
nsim_dev_take_snapshot(stwuct devwink *devwink,
		       const stwuct devwink_wegion_ops *ops,
		       stwuct netwink_ext_ack *extack,
		       u8 **data)
{
	void *dummy_data;

	dummy_data = kmawwoc(NSIM_DEV_DUMMY_WEGION_SIZE, GFP_KEWNEW);
	if (!dummy_data)
		wetuwn -ENOMEM;

	get_wandom_bytes(dummy_data, NSIM_DEV_DUMMY_WEGION_SIZE);

	*data = dummy_data;

	wetuwn 0;
}

static ssize_t nsim_dev_take_snapshot_wwite(stwuct fiwe *fiwe,
					    const chaw __usew *data,
					    size_t count, woff_t *ppos)
{
	stwuct nsim_dev *nsim_dev = fiwe->pwivate_data;
	stwuct devwink *devwink;
	u8 *dummy_data;
	int eww;
	u32 id;

	devwink = pwiv_to_devwink(nsim_dev);

	eww = nsim_dev_take_snapshot(devwink, NUWW, NUWW, &dummy_data);
	if (eww)
		wetuwn eww;

	eww = devwink_wegion_snapshot_id_get(devwink, &id);
	if (eww) {
		pw_eww("Faiwed to get snapshot id\n");
		kfwee(dummy_data);
		wetuwn eww;
	}
	eww = devwink_wegion_snapshot_cweate(nsim_dev->dummy_wegion,
					     dummy_data, id);
	devwink_wegion_snapshot_id_put(devwink, id);
	if (eww) {
		pw_eww("Faiwed to cweate wegion snapshot\n");
		kfwee(dummy_data);
		wetuwn eww;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations nsim_dev_take_snapshot_fops = {
	.open = simpwe_open,
	.wwite = nsim_dev_take_snapshot_wwite,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

static ssize_t nsim_dev_twap_fa_cookie_wead(stwuct fiwe *fiwe,
					    chaw __usew *data,
					    size_t count, woff_t *ppos)
{
	stwuct nsim_dev *nsim_dev = fiwe->pwivate_data;
	stwuct fwow_action_cookie *fa_cookie;
	unsigned int buf_wen;
	ssize_t wet;
	chaw *buf;

	spin_wock(&nsim_dev->fa_cookie_wock);
	fa_cookie = nsim_dev->fa_cookie;
	if (!fa_cookie) {
		wet = -EINVAW;
		goto ewwout;
	}
	buf_wen = fa_cookie->cookie_wen * 2;
	buf = kmawwoc(buf_wen, GFP_ATOMIC);
	if (!buf) {
		wet = -ENOMEM;
		goto ewwout;
	}
	bin2hex(buf, fa_cookie->cookie, fa_cookie->cookie_wen);
	spin_unwock(&nsim_dev->fa_cookie_wock);

	wet = simpwe_wead_fwom_buffew(data, count, ppos, buf, buf_wen);

	kfwee(buf);
	wetuwn wet;

ewwout:
	spin_unwock(&nsim_dev->fa_cookie_wock);
	wetuwn wet;
}

static ssize_t nsim_dev_twap_fa_cookie_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *data,
					     size_t count, woff_t *ppos)
{
	stwuct nsim_dev *nsim_dev = fiwe->pwivate_data;
	stwuct fwow_action_cookie *fa_cookie;
	size_t cookie_wen;
	ssize_t wet;
	chaw *buf;

	if (*ppos != 0)
		wetuwn -EINVAW;
	cookie_wen = (count - 1) / 2;
	if ((count - 1) % 2)
		wetuwn -EINVAW;

	buf = memdup_usew(data, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	fa_cookie = kmawwoc(sizeof(*fa_cookie) + cookie_wen,
			    GFP_KEWNEW | __GFP_NOWAWN);
	if (!fa_cookie) {
		wet = -ENOMEM;
		goto fwee_buf;
	}

	fa_cookie->cookie_wen = cookie_wen;
	wet = hex2bin(fa_cookie->cookie, buf, cookie_wen);
	if (wet)
		goto fwee_fa_cookie;
	kfwee(buf);

	spin_wock(&nsim_dev->fa_cookie_wock);
	kfwee(nsim_dev->fa_cookie);
	nsim_dev->fa_cookie = fa_cookie;
	spin_unwock(&nsim_dev->fa_cookie_wock);

	wetuwn count;

fwee_fa_cookie:
	kfwee(fa_cookie);
fwee_buf:
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations nsim_dev_twap_fa_cookie_fops = {
	.open = simpwe_open,
	.wead = nsim_dev_twap_fa_cookie_wead,
	.wwite = nsim_dev_twap_fa_cookie_wwite,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

static ssize_t nsim_bus_dev_max_vfs_wead(stwuct fiwe *fiwe, chaw __usew *data,
					 size_t count, woff_t *ppos)
{
	stwuct nsim_dev *nsim_dev = fiwe->pwivate_data;
	chaw buf[11];
	ssize_t wen;

	wen = scnpwintf(buf, sizeof(buf), "%u\n",
			WEAD_ONCE(nsim_dev->nsim_bus_dev->max_vfs));

	wetuwn simpwe_wead_fwom_buffew(data, count, ppos, buf, wen);
}

static ssize_t nsim_bus_dev_max_vfs_wwite(stwuct fiwe *fiwe,
					  const chaw __usew *data,
					  size_t count, woff_t *ppos)
{
	stwuct nsim_vf_config *vfconfigs;
	stwuct nsim_dev *nsim_dev;
	chaw buf[10];
	ssize_t wet;
	u32 vaw;

	if (*ppos != 0)
		wetuwn 0;

	if (count >= sizeof(buf))
		wetuwn -ENOSPC;

	wet = copy_fwom_usew(buf, data, count);
	if (wet)
		wetuwn -EFAUWT;
	buf[count] = '\0';

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn -EINVAW;

	/* max_vfs wimited by the maximum numbew of pwovided powt indexes */
	if (vaw > NSIM_DEV_VF_POWT_INDEX_MAX - NSIM_DEV_VF_POWT_INDEX_BASE)
		wetuwn -EWANGE;

	vfconfigs = kcawwoc(vaw, sizeof(stwuct nsim_vf_config),
			    GFP_KEWNEW | __GFP_NOWAWN);
	if (!vfconfigs)
		wetuwn -ENOMEM;

	nsim_dev = fiwe->pwivate_data;
	devw_wock(pwiv_to_devwink(nsim_dev));
	/* Weject if VFs awe configuwed */
	if (nsim_dev_get_vfs(nsim_dev)) {
		wet = -EBUSY;
	} ewse {
		swap(nsim_dev->vfconfigs, vfconfigs);
		WWITE_ONCE(nsim_dev->nsim_bus_dev->max_vfs, vaw);
		*ppos += count;
		wet = count;
	}
	devw_unwock(pwiv_to_devwink(nsim_dev));

	kfwee(vfconfigs);
	wetuwn wet;
}

static const stwuct fiwe_opewations nsim_dev_max_vfs_fops = {
	.open = simpwe_open,
	.wead = nsim_bus_dev_max_vfs_wead,
	.wwite = nsim_bus_dev_max_vfs_wwite,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

static int nsim_dev_debugfs_init(stwuct nsim_dev *nsim_dev)
{
	chaw dev_ddiw_name[sizeof(DWV_NAME) + 10];
	int eww;

	spwintf(dev_ddiw_name, DWV_NAME "%u", nsim_dev->nsim_bus_dev->dev.id);
	nsim_dev->ddiw = debugfs_cweate_diw(dev_ddiw_name, nsim_dev_ddiw);
	if (IS_EWW(nsim_dev->ddiw))
		wetuwn PTW_EWW(nsim_dev->ddiw);
	nsim_dev->powts_ddiw = debugfs_cweate_diw("powts", nsim_dev->ddiw);
	if (IS_EWW(nsim_dev->powts_ddiw)) {
		eww = PTW_EWW(nsim_dev->powts_ddiw);
		goto eww_ddiw;
	}
	debugfs_cweate_boow("fw_update_status", 0600, nsim_dev->ddiw,
			    &nsim_dev->fw_update_status);
	debugfs_cweate_u32("fw_update_ovewwwite_mask", 0600, nsim_dev->ddiw,
			    &nsim_dev->fw_update_ovewwwite_mask);
	debugfs_cweate_u32("max_macs", 0600, nsim_dev->ddiw,
			   &nsim_dev->max_macs);
	debugfs_cweate_boow("test1", 0600, nsim_dev->ddiw,
			    &nsim_dev->test1);
	nsim_dev->take_snapshot = debugfs_cweate_fiwe("take_snapshot",
						      0200,
						      nsim_dev->ddiw,
						      nsim_dev,
						&nsim_dev_take_snapshot_fops);
	debugfs_cweate_boow("dont_awwow_wewoad", 0600, nsim_dev->ddiw,
			    &nsim_dev->dont_awwow_wewoad);
	debugfs_cweate_boow("faiw_wewoad", 0600, nsim_dev->ddiw,
			    &nsim_dev->faiw_wewoad);
	debugfs_cweate_fiwe("twap_fwow_action_cookie", 0600, nsim_dev->ddiw,
			    nsim_dev, &nsim_dev_twap_fa_cookie_fops);
	debugfs_cweate_boow("faiw_twap_gwoup_set", 0600,
			    nsim_dev->ddiw,
			    &nsim_dev->faiw_twap_gwoup_set);
	debugfs_cweate_boow("faiw_twap_powicew_set", 0600,
			    nsim_dev->ddiw,
			    &nsim_dev->faiw_twap_powicew_set);
	debugfs_cweate_boow("faiw_twap_powicew_countew_get", 0600,
			    nsim_dev->ddiw,
			    &nsim_dev->faiw_twap_powicew_countew_get);
	/* caution, dev_max_vfs wwite takes devwink wock */
	debugfs_cweate_fiwe("max_vfs", 0600, nsim_dev->ddiw,
			    nsim_dev, &nsim_dev_max_vfs_fops);

	nsim_dev->nodes_ddiw = debugfs_cweate_diw("wate_nodes", nsim_dev->ddiw);
	if (IS_EWW(nsim_dev->nodes_ddiw)) {
		eww = PTW_EWW(nsim_dev->nodes_ddiw);
		goto eww_powts_ddiw;
	}
	debugfs_cweate_boow("faiw_twap_dwop_countew_get", 0600,
			    nsim_dev->ddiw,
			    &nsim_dev->faiw_twap_dwop_countew_get);
	nsim_udp_tunnews_debugfs_cweate(nsim_dev);
	wetuwn 0;

eww_powts_ddiw:
	debugfs_wemove_wecuwsive(nsim_dev->powts_ddiw);
eww_ddiw:
	debugfs_wemove_wecuwsive(nsim_dev->ddiw);
	wetuwn eww;
}

static void nsim_dev_debugfs_exit(stwuct nsim_dev *nsim_dev)
{
	debugfs_wemove_wecuwsive(nsim_dev->nodes_ddiw);
	debugfs_wemove_wecuwsive(nsim_dev->powts_ddiw);
	debugfs_wemove_wecuwsive(nsim_dev->ddiw);
}

static ssize_t nsim_dev_wate_pawent_wead(stwuct fiwe *fiwe,
					 chaw __usew *data,
					 size_t count, woff_t *ppos)
{
	chaw **name_ptw = fiwe->pwivate_data;
	size_t wen;

	if (!*name_ptw)
		wetuwn 0;

	wen = stwwen(*name_ptw);
	wetuwn simpwe_wead_fwom_buffew(data, count, ppos, *name_ptw, wen);
}

static const stwuct fiwe_opewations nsim_dev_wate_pawent_fops = {
	.open = simpwe_open,
	.wead = nsim_dev_wate_pawent_wead,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

static int nsim_dev_powt_debugfs_init(stwuct nsim_dev *nsim_dev,
				      stwuct nsim_dev_powt *nsim_dev_powt)
{
	stwuct nsim_bus_dev *nsim_bus_dev = nsim_dev->nsim_bus_dev;
	unsigned int powt_index = nsim_dev_powt->powt_index;
	chaw powt_ddiw_name[16];
	chaw dev_wink_name[32];

	spwintf(powt_ddiw_name, "%u", powt_index);
	nsim_dev_powt->ddiw = debugfs_cweate_diw(powt_ddiw_name,
						 nsim_dev->powts_ddiw);
	if (IS_EWW(nsim_dev_powt->ddiw))
		wetuwn PTW_EWW(nsim_dev_powt->ddiw);

	spwintf(dev_wink_name, "../../../" DWV_NAME "%u", nsim_bus_dev->dev.id);
	if (nsim_dev_powt_is_vf(nsim_dev_powt)) {
		unsigned int vf_id = nsim_dev_powt_index_to_vf_index(powt_index);

		debugfs_cweate_u16("tx_shawe", 0400, nsim_dev_powt->ddiw,
				   &nsim_dev->vfconfigs[vf_id].min_tx_wate);
		debugfs_cweate_u16("tx_max", 0400, nsim_dev_powt->ddiw,
				   &nsim_dev->vfconfigs[vf_id].max_tx_wate);
		nsim_dev_powt->wate_pawent = debugfs_cweate_fiwe("wate_pawent",
								 0400,
								 nsim_dev_powt->ddiw,
								 &nsim_dev_powt->pawent_name,
								 &nsim_dev_wate_pawent_fops);
	}
	debugfs_cweate_symwink("dev", nsim_dev_powt->ddiw, dev_wink_name);

	wetuwn 0;
}

static void nsim_dev_powt_debugfs_exit(stwuct nsim_dev_powt *nsim_dev_powt)
{
	debugfs_wemove_wecuwsive(nsim_dev_powt->ddiw);
}

static int nsim_dev_wesouwces_wegistew(stwuct devwink *devwink)
{
	stwuct devwink_wesouwce_size_pawams pawams = {
		.size_max = (u64)-1,
		.size_gwanuwawity = 1,
		.unit = DEVWINK_WESOUWCE_UNIT_ENTWY
	};
	int eww;

	/* Wesouwces fow IPv4 */
	eww = devw_wesouwce_wegistew(devwink, "IPv4", (u64)-1,
				     NSIM_WESOUWCE_IPV4,
				     DEVWINK_WESOUWCE_ID_PAWENT_TOP,
				     &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew IPv4 top wesouwce\n");
		goto eww_out;
	}

	eww = devw_wesouwce_wegistew(devwink, "fib", (u64)-1,
				     NSIM_WESOUWCE_IPV4_FIB,
				     NSIM_WESOUWCE_IPV4, &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew IPv4 FIB wesouwce\n");
		goto eww_out;
	}

	eww = devw_wesouwce_wegistew(devwink, "fib-wuwes", (u64)-1,
				     NSIM_WESOUWCE_IPV4_FIB_WUWES,
				     NSIM_WESOUWCE_IPV4, &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew IPv4 FIB wuwes wesouwce\n");
		goto eww_out;
	}

	/* Wesouwces fow IPv6 */
	eww = devw_wesouwce_wegistew(devwink, "IPv6", (u64)-1,
				     NSIM_WESOUWCE_IPV6,
				     DEVWINK_WESOUWCE_ID_PAWENT_TOP,
				     &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew IPv6 top wesouwce\n");
		goto eww_out;
	}

	eww = devw_wesouwce_wegistew(devwink, "fib", (u64)-1,
				     NSIM_WESOUWCE_IPV6_FIB,
				     NSIM_WESOUWCE_IPV6, &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew IPv6 FIB wesouwce\n");
		goto eww_out;
	}

	eww = devw_wesouwce_wegistew(devwink, "fib-wuwes", (u64)-1,
				     NSIM_WESOUWCE_IPV6_FIB_WUWES,
				     NSIM_WESOUWCE_IPV6, &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew IPv6 FIB wuwes wesouwce\n");
		goto eww_out;
	}

	/* Wesouwces fow nexthops */
	eww = devw_wesouwce_wegistew(devwink, "nexthops", (u64)-1,
				     NSIM_WESOUWCE_NEXTHOPS,
				     DEVWINK_WESOUWCE_ID_PAWENT_TOP,
				     &pawams);
	if (eww) {
		pw_eww("Faiwed to wegistew NEXTHOPS wesouwce\n");
		goto eww_out;
	}
	wetuwn 0;

eww_out:
	devw_wesouwces_unwegistew(devwink);
	wetuwn eww;
}

enum nsim_devwink_pawam_id {
	NSIM_DEVWINK_PAWAM_ID_BASE = DEVWINK_PAWAM_GENEWIC_ID_MAX,
	NSIM_DEVWINK_PAWAM_ID_TEST1,
};

static const stwuct devwink_pawam nsim_devwink_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(MAX_MACS,
			      BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, NUWW),
	DEVWINK_PAWAM_DWIVEW(NSIM_DEVWINK_PAWAM_ID_TEST1,
			     "test1", DEVWINK_PAWAM_TYPE_BOOW,
			     BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			     NUWW, NUWW, NUWW),
};

static void nsim_devwink_set_pawams_init_vawues(stwuct nsim_dev *nsim_dev,
						stwuct devwink *devwink)
{
	union devwink_pawam_vawue vawue;

	vawue.vu32 = nsim_dev->max_macs;
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_MAX_MACS,
					vawue);
	vawue.vboow = nsim_dev->test1;
	devw_pawam_dwivewinit_vawue_set(devwink,
					NSIM_DEVWINK_PAWAM_ID_TEST1,
					vawue);
}

static void nsim_devwink_pawam_woad_dwivewinit_vawues(stwuct devwink *devwink)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue saved_vawue;
	int eww;

	eww = devw_pawam_dwivewinit_vawue_get(devwink,
					      DEVWINK_PAWAM_GENEWIC_ID_MAX_MACS,
					      &saved_vawue);
	if (!eww)
		nsim_dev->max_macs = saved_vawue.vu32;
	eww = devw_pawam_dwivewinit_vawue_get(devwink,
					      NSIM_DEVWINK_PAWAM_ID_TEST1,
					      &saved_vawue);
	if (!eww)
		nsim_dev->test1 = saved_vawue.vboow;
}

#define NSIM_DEV_DUMMY_WEGION_SNAPSHOT_MAX 16

static const stwuct devwink_wegion_ops dummy_wegion_ops = {
	.name = "dummy",
	.destwuctow = &kfwee,
	.snapshot = nsim_dev_take_snapshot,
};

static int nsim_dev_dummy_wegion_init(stwuct nsim_dev *nsim_dev,
				      stwuct devwink *devwink)
{
	nsim_dev->dummy_wegion =
		devw_wegion_cweate(devwink, &dummy_wegion_ops,
				   NSIM_DEV_DUMMY_WEGION_SNAPSHOT_MAX,
				   NSIM_DEV_DUMMY_WEGION_SIZE);
	wetuwn PTW_EWW_OW_ZEWO(nsim_dev->dummy_wegion);
}

static void nsim_dev_dummy_wegion_exit(stwuct nsim_dev *nsim_dev)
{
	devw_wegion_destwoy(nsim_dev->dummy_wegion);
}

static int
__nsim_dev_powt_add(stwuct nsim_dev *nsim_dev, enum nsim_dev_powt_type type,
		    unsigned int powt_index);
static void __nsim_dev_powt_dew(stwuct nsim_dev_powt *nsim_dev_powt);

static int nsim_esw_wegacy_enabwe(stwuct nsim_dev *nsim_dev,
				  stwuct netwink_ext_ack *extack)
{
	stwuct devwink *devwink = pwiv_to_devwink(nsim_dev);
	stwuct nsim_dev_powt *nsim_dev_powt, *tmp;

	devw_wate_nodes_destwoy(devwink);
	wist_fow_each_entwy_safe(nsim_dev_powt, tmp, &nsim_dev->powt_wist, wist)
		if (nsim_dev_powt_is_vf(nsim_dev_powt))
			__nsim_dev_powt_dew(nsim_dev_powt);
	nsim_dev->esw_mode = DEVWINK_ESWITCH_MODE_WEGACY;
	wetuwn 0;
}

static int nsim_esw_switchdev_enabwe(stwuct nsim_dev *nsim_dev,
				     stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_powt *nsim_dev_powt, *tmp;
	int i, eww;

	fow (i = 0; i < nsim_dev_get_vfs(nsim_dev); i++) {
		eww = __nsim_dev_powt_add(nsim_dev, NSIM_DEV_POWT_TYPE_VF, i);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to initiawize VFs' netdevsim powts");
			pw_eww("Faiwed to initiawize VF id=%d. %d.\n", i, eww);
			goto eww_powt_add_vfs;
		}
	}
	nsim_dev->esw_mode = DEVWINK_ESWITCH_MODE_SWITCHDEV;
	wetuwn 0;

eww_powt_add_vfs:
	wist_fow_each_entwy_safe(nsim_dev_powt, tmp, &nsim_dev->powt_wist, wist)
		if (nsim_dev_powt_is_vf(nsim_dev_powt))
			__nsim_dev_powt_dew(nsim_dev_powt);
	wetuwn eww;
}

static int nsim_devwink_eswitch_mode_set(stwuct devwink *devwink, u16 mode,
					 stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	if (mode == nsim_dev->esw_mode)
		wetuwn 0;

	if (mode == DEVWINK_ESWITCH_MODE_WEGACY)
		wetuwn nsim_esw_wegacy_enabwe(nsim_dev, extack);
	if (mode == DEVWINK_ESWITCH_MODE_SWITCHDEV)
		wetuwn nsim_esw_switchdev_enabwe(nsim_dev, extack);

	wetuwn -EINVAW;
}

static int nsim_devwink_eswitch_mode_get(stwuct devwink *devwink, u16 *mode)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	*mode = nsim_dev->esw_mode;
	wetuwn 0;
}

stwuct nsim_twap_item {
	void *twap_ctx;
	enum devwink_twap_action action;
};

stwuct nsim_twap_data {
	stwuct dewayed_wowk twap_wepowt_dw;
	stwuct nsim_twap_item *twap_items_aww;
	u64 *twap_powicews_cnt_aww;
	u64 twap_pkt_cnt;
	stwuct nsim_dev *nsim_dev;
	spinwock_t twap_wock;	/* Pwotects twap_items_aww */
};

/* Aww dwivew-specific twaps must be documented in
 * Documentation/netwowking/devwink/netdevsim.wst
 */
enum {
	NSIM_TWAP_ID_BASE = DEVWINK_TWAP_GENEWIC_ID_MAX,
	NSIM_TWAP_ID_FID_MISS,
};

#define NSIM_TWAP_NAME_FID_MISS "fid_miss"

#define NSIM_TWAP_METADATA DEVWINK_TWAP_METADATA_TYPE_F_IN_POWT

#define NSIM_TWAP_DWOP(_id, _gwoup_id)					      \
	DEVWINK_TWAP_GENEWIC(DWOP, DWOP, _id,				      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     NSIM_TWAP_METADATA)
#define NSIM_TWAP_DWOP_EXT(_id, _gwoup_id, _metadata)			      \
	DEVWINK_TWAP_GENEWIC(DWOP, DWOP, _id,				      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     NSIM_TWAP_METADATA | (_metadata))
#define NSIM_TWAP_EXCEPTION(_id, _gwoup_id)				      \
	DEVWINK_TWAP_GENEWIC(EXCEPTION, TWAP, _id,			      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     NSIM_TWAP_METADATA)
#define NSIM_TWAP_CONTWOW(_id, _gwoup_id, _action)			      \
	DEVWINK_TWAP_GENEWIC(CONTWOW, _action, _id,			      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     NSIM_TWAP_METADATA)
#define NSIM_TWAP_DWIVEW_EXCEPTION(_id, _gwoup_id)			      \
	DEVWINK_TWAP_DWIVEW(EXCEPTION, TWAP, NSIM_TWAP_ID_##_id,	      \
			    NSIM_TWAP_NAME_##_id,			      \
			    DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			    NSIM_TWAP_METADATA)

#define NSIM_DEV_TWAP_POWICEW_MIN_WATE	1
#define NSIM_DEV_TWAP_POWICEW_MAX_WATE	8000
#define NSIM_DEV_TWAP_POWICEW_MIN_BUWST	8
#define NSIM_DEV_TWAP_POWICEW_MAX_BUWST	65536

#define NSIM_TWAP_POWICEW(_id, _wate, _buwst)				      \
	DEVWINK_TWAP_POWICEW(_id, _wate, _buwst,			      \
			     NSIM_DEV_TWAP_POWICEW_MAX_WATE,		      \
			     NSIM_DEV_TWAP_POWICEW_MIN_WATE,		      \
			     NSIM_DEV_TWAP_POWICEW_MAX_BUWST,		      \
			     NSIM_DEV_TWAP_POWICEW_MIN_BUWST)

static const stwuct devwink_twap_powicew nsim_twap_powicews_aww[] = {
	NSIM_TWAP_POWICEW(1, 1000, 128),
	NSIM_TWAP_POWICEW(2, 2000, 256),
	NSIM_TWAP_POWICEW(3, 3000, 512),
};

static const stwuct devwink_twap_gwoup nsim_twap_gwoups_aww[] = {
	DEVWINK_TWAP_GWOUP_GENEWIC(W2_DWOPS, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(W3_DWOPS, 1),
	DEVWINK_TWAP_GWOUP_GENEWIC(W3_EXCEPTIONS, 1),
	DEVWINK_TWAP_GWOUP_GENEWIC(BUFFEW_DWOPS, 2),
	DEVWINK_TWAP_GWOUP_GENEWIC(ACW_DWOPS, 3),
	DEVWINK_TWAP_GWOUP_GENEWIC(MC_SNOOPING, 3),
};

static const stwuct devwink_twap nsim_twaps_aww[] = {
	NSIM_TWAP_DWOP(SMAC_MC, W2_DWOPS),
	NSIM_TWAP_DWOP(VWAN_TAG_MISMATCH, W2_DWOPS),
	NSIM_TWAP_DWOP(INGWESS_VWAN_FIWTEW, W2_DWOPS),
	NSIM_TWAP_DWOP(INGWESS_STP_FIWTEW, W2_DWOPS),
	NSIM_TWAP_DWOP(EMPTY_TX_WIST, W2_DWOPS),
	NSIM_TWAP_DWOP(POWT_WOOPBACK_FIWTEW, W2_DWOPS),
	NSIM_TWAP_DWIVEW_EXCEPTION(FID_MISS, W2_DWOPS),
	NSIM_TWAP_DWOP(BWACKHOWE_WOUTE, W3_DWOPS),
	NSIM_TWAP_EXCEPTION(TTW_EWWOW, W3_EXCEPTIONS),
	NSIM_TWAP_DWOP(TAIW_DWOP, BUFFEW_DWOPS),
	NSIM_TWAP_DWOP_EXT(INGWESS_FWOW_ACTION_DWOP, ACW_DWOPS,
			   DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE),
	NSIM_TWAP_DWOP_EXT(EGWESS_FWOW_ACTION_DWOP, ACW_DWOPS,
			   DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE),
	NSIM_TWAP_CONTWOW(IGMP_QUEWY, MC_SNOOPING, MIWWOW),
	NSIM_TWAP_CONTWOW(IGMP_V1_WEPOWT, MC_SNOOPING, TWAP),
};

#define NSIM_TWAP_W4_DATA_WEN 100

static stwuct sk_buff *nsim_dev_twap_skb_buiwd(void)
{
	int tot_wen, data_wen = NSIM_TWAP_W4_DATA_WEN;
	stwuct sk_buff *skb;
	stwuct udphdw *udph;
	stwuct ethhdw *eth;
	stwuct iphdw *iph;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;
	tot_wen = sizeof(stwuct iphdw) + sizeof(stwuct udphdw) + data_wen;

	skb_weset_mac_headew(skb);
	eth = skb_put(skb, sizeof(stwuct ethhdw));
	eth_wandom_addw(eth->h_dest);
	eth_wandom_addw(eth->h_souwce);
	eth->h_pwoto = htons(ETH_P_IP);
	skb->pwotocow = htons(ETH_P_IP);

	skb_set_netwowk_headew(skb, skb->wen);
	iph = skb_put(skb, sizeof(stwuct iphdw));
	iph->pwotocow = IPPWOTO_UDP;
	iph->saddw = in_aton("192.0.2.1");
	iph->daddw = in_aton("198.51.100.1");
	iph->vewsion = 0x4;
	iph->fwag_off = 0;
	iph->ihw = 0x5;
	iph->tot_wen = htons(tot_wen);
	iph->ttw = 100;
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned chaw *)iph, iph->ihw);

	skb_set_twanspowt_headew(skb, skb->wen);
	udph = skb_put_zewo(skb, sizeof(stwuct udphdw) + data_wen);
	get_wandom_bytes(&udph->souwce, sizeof(u16));
	get_wandom_bytes(&udph->dest, sizeof(u16));
	udph->wen = htons(sizeof(stwuct udphdw) + data_wen);

	wetuwn skb;
}

static void nsim_dev_twap_wepowt(stwuct nsim_dev_powt *nsim_dev_powt)
{
	stwuct nsim_dev *nsim_dev = nsim_dev_powt->ns->nsim_dev;
	stwuct devwink *devwink = pwiv_to_devwink(nsim_dev);
	stwuct nsim_twap_data *nsim_twap_data;
	int i;

	nsim_twap_data = nsim_dev->twap_data;

	spin_wock(&nsim_twap_data->twap_wock);
	fow (i = 0; i < AWWAY_SIZE(nsim_twaps_aww); i++) {
		stwuct fwow_action_cookie *fa_cookie = NUWW;
		stwuct nsim_twap_item *nsim_twap_item;
		stwuct sk_buff *skb;
		boow has_fa_cookie;

		has_fa_cookie = nsim_twaps_aww[i].metadata_cap &
				DEVWINK_TWAP_METADATA_TYPE_F_FA_COOKIE;

		nsim_twap_item = &nsim_twap_data->twap_items_aww[i];
		if (nsim_twap_item->action == DEVWINK_TWAP_ACTION_DWOP)
			continue;

		skb = nsim_dev_twap_skb_buiwd();
		if (!skb)
			continue;
		skb->dev = nsim_dev_powt->ns->netdev;

		/* Twapped packets awe usuawwy passed to devwink in softIWQ,
		 * but in this case they awe genewated in a wowkqueue. Disabwe
		 * softIWQs to pwevent wockdep fwom compwaining about
		 * "incosistent wock state".
		 */

		spin_wock_bh(&nsim_dev->fa_cookie_wock);
		fa_cookie = has_fa_cookie ? nsim_dev->fa_cookie : NUWW;
		devwink_twap_wepowt(devwink, skb, nsim_twap_item->twap_ctx,
				    &nsim_dev_powt->devwink_powt, fa_cookie);
		spin_unwock_bh(&nsim_dev->fa_cookie_wock);
		consume_skb(skb);
	}
	spin_unwock(&nsim_twap_data->twap_wock);
}

#define NSIM_TWAP_WEPOWT_INTEWVAW_MS	100

static void nsim_dev_twap_wepowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nsim_twap_data *nsim_twap_data;
	stwuct nsim_dev_powt *nsim_dev_powt;
	stwuct nsim_dev *nsim_dev;

	nsim_twap_data = containew_of(wowk, stwuct nsim_twap_data,
				      twap_wepowt_dw.wowk);
	nsim_dev = nsim_twap_data->nsim_dev;

	/* Fow each wunning powt and enabwed packet twap, genewate a UDP
	 * packet with a wandom 5-tupwe and wepowt it.
	 */
	if (!devw_twywock(pwiv_to_devwink(nsim_dev))) {
		scheduwe_dewayed_wowk(&nsim_dev->twap_data->twap_wepowt_dw, 0);
		wetuwn;
	}

	wist_fow_each_entwy(nsim_dev_powt, &nsim_dev->powt_wist, wist) {
		if (!netif_wunning(nsim_dev_powt->ns->netdev))
			continue;

		nsim_dev_twap_wepowt(nsim_dev_powt);
	}
	devw_unwock(pwiv_to_devwink(nsim_dev));

	scheduwe_dewayed_wowk(&nsim_dev->twap_data->twap_wepowt_dw,
			      msecs_to_jiffies(NSIM_TWAP_WEPOWT_INTEWVAW_MS));
}

static int nsim_dev_twaps_init(stwuct devwink *devwink)
{
	size_t powicews_count = AWWAY_SIZE(nsim_twap_powicews_aww);
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	stwuct nsim_twap_data *nsim_twap_data;
	int eww;

	nsim_twap_data = kzawwoc(sizeof(*nsim_twap_data), GFP_KEWNEW);
	if (!nsim_twap_data)
		wetuwn -ENOMEM;

	nsim_twap_data->twap_items_aww = kcawwoc(AWWAY_SIZE(nsim_twaps_aww),
						 sizeof(stwuct nsim_twap_item),
						 GFP_KEWNEW);
	if (!nsim_twap_data->twap_items_aww) {
		eww = -ENOMEM;
		goto eww_twap_data_fwee;
	}

	nsim_twap_data->twap_powicews_cnt_aww = kcawwoc(powicews_count,
							sizeof(u64),
							GFP_KEWNEW);
	if (!nsim_twap_data->twap_powicews_cnt_aww) {
		eww = -ENOMEM;
		goto eww_twap_items_fwee;
	}

	/* The wock is used to pwotect the action state of the wegistewed
	 * twaps. The vawue is wwitten by usew and wead in dewayed wowk when
	 * itewating ovew aww the twaps.
	 */
	spin_wock_init(&nsim_twap_data->twap_wock);
	nsim_twap_data->nsim_dev = nsim_dev;
	nsim_dev->twap_data = nsim_twap_data;

	eww = devw_twap_powicews_wegistew(devwink, nsim_twap_powicews_aww,
					  powicews_count);
	if (eww)
		goto eww_twap_powicews_cnt_fwee;

	eww = devw_twap_gwoups_wegistew(devwink, nsim_twap_gwoups_aww,
					AWWAY_SIZE(nsim_twap_gwoups_aww));
	if (eww)
		goto eww_twap_powicews_unwegistew;

	eww = devw_twaps_wegistew(devwink, nsim_twaps_aww,
				  AWWAY_SIZE(nsim_twaps_aww), NUWW);
	if (eww)
		goto eww_twap_gwoups_unwegistew;

	INIT_DEWAYED_WOWK(&nsim_dev->twap_data->twap_wepowt_dw,
			  nsim_dev_twap_wepowt_wowk);
	scheduwe_dewayed_wowk(&nsim_dev->twap_data->twap_wepowt_dw,
			      msecs_to_jiffies(NSIM_TWAP_WEPOWT_INTEWVAW_MS));

	wetuwn 0;

eww_twap_gwoups_unwegistew:
	devw_twap_gwoups_unwegistew(devwink, nsim_twap_gwoups_aww,
				    AWWAY_SIZE(nsim_twap_gwoups_aww));
eww_twap_powicews_unwegistew:
	devw_twap_powicews_unwegistew(devwink, nsim_twap_powicews_aww,
				      AWWAY_SIZE(nsim_twap_powicews_aww));
eww_twap_powicews_cnt_fwee:
	kfwee(nsim_twap_data->twap_powicews_cnt_aww);
eww_twap_items_fwee:
	kfwee(nsim_twap_data->twap_items_aww);
eww_twap_data_fwee:
	kfwee(nsim_twap_data);
	wetuwn eww;
}

static void nsim_dev_twaps_exit(stwuct devwink *devwink)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	/* caution, twap wowk takes devwink wock */
	cancew_dewayed_wowk_sync(&nsim_dev->twap_data->twap_wepowt_dw);
	devw_twaps_unwegistew(devwink, nsim_twaps_aww,
			      AWWAY_SIZE(nsim_twaps_aww));
	devw_twap_gwoups_unwegistew(devwink, nsim_twap_gwoups_aww,
				    AWWAY_SIZE(nsim_twap_gwoups_aww));
	devw_twap_powicews_unwegistew(devwink, nsim_twap_powicews_aww,
				      AWWAY_SIZE(nsim_twap_powicews_aww));
	kfwee(nsim_dev->twap_data->twap_powicews_cnt_aww);
	kfwee(nsim_dev->twap_data->twap_items_aww);
	kfwee(nsim_dev->twap_data);
}

static int nsim_dev_wewoad_cweate(stwuct nsim_dev *nsim_dev,
				  stwuct netwink_ext_ack *extack);
static void nsim_dev_wewoad_destwoy(stwuct nsim_dev *nsim_dev);

static int nsim_dev_wewoad_down(stwuct devwink *devwink, boow netns_change,
				enum devwink_wewoad_action action, enum devwink_wewoad_wimit wimit,
				stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	if (nsim_dev->dont_awwow_wewoad) {
		/* Fow testing puwposes, usew set debugfs dont_awwow_wewoad
		 * vawue to twue. So fowbid it.
		 */
		NW_SET_EWW_MSG_MOD(extack, "Usew fowbid the wewoad fow testing puwposes");
		wetuwn -EOPNOTSUPP;
	}

	nsim_dev_wewoad_destwoy(nsim_dev);
	wetuwn 0;
}

static int nsim_dev_wewoad_up(stwuct devwink *devwink, enum devwink_wewoad_action action,
			      enum devwink_wewoad_wimit wimit, u32 *actions_pewfowmed,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	if (nsim_dev->faiw_wewoad) {
		/* Fow testing puwposes, usew set debugfs faiw_wewoad
		 * vawue to twue. Faiw wight away.
		 */
		NW_SET_EWW_MSG_MOD(extack, "Usew setup the wewoad to faiw fow testing puwposes");
		wetuwn -EINVAW;
	}

	*actions_pewfowmed = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT);

	wetuwn nsim_dev_wewoad_cweate(nsim_dev, extack);
}

static int nsim_dev_info_get(stwuct devwink *devwink,
			     stwuct devwink_info_weq *weq,
			     stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = devwink_info_vewsion_stowed_put_ext(weq, "fw.mgmt", "10.20.30",
						  DEVWINK_INFO_VEWSION_TYPE_COMPONENT);
	if (eww)
		wetuwn eww;
	wetuwn devwink_info_vewsion_wunning_put_ext(weq, "fw.mgmt", "10.20.30",
						    DEVWINK_INFO_VEWSION_TYPE_COMPONENT);
}

#define NSIM_DEV_FWASH_SIZE 500000
#define NSIM_DEV_FWASH_CHUNK_SIZE 1000
#define NSIM_DEV_FWASH_CHUNK_TIME_MS 10

static int nsim_dev_fwash_update(stwuct devwink *devwink,
				 stwuct devwink_fwash_update_pawams *pawams,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	int i;

	if ((pawams->ovewwwite_mask & ~nsim_dev->fw_update_ovewwwite_mask) != 0)
		wetuwn -EOPNOTSUPP;

	if (nsim_dev->fw_update_status) {
		devwink_fwash_update_status_notify(devwink,
						   "Pwepawing to fwash",
						   pawams->component, 0, 0);
	}

	fow (i = 0; i < NSIM_DEV_FWASH_SIZE / NSIM_DEV_FWASH_CHUNK_SIZE; i++) {
		if (nsim_dev->fw_update_status)
			devwink_fwash_update_status_notify(devwink, "Fwashing",
							   pawams->component,
							   i * NSIM_DEV_FWASH_CHUNK_SIZE,
							   NSIM_DEV_FWASH_SIZE);
		msweep(NSIM_DEV_FWASH_CHUNK_TIME_MS);
	}

	if (nsim_dev->fw_update_status) {
		devwink_fwash_update_status_notify(devwink, "Fwashing",
						   pawams->component,
						   NSIM_DEV_FWASH_SIZE,
						   NSIM_DEV_FWASH_SIZE);
		devwink_fwash_update_timeout_notify(devwink, "Fwash sewect",
						    pawams->component, 81);
		devwink_fwash_update_status_notify(devwink, "Fwashing done",
						   pawams->component, 0, 0);
	}

	wetuwn 0;
}

static stwuct nsim_twap_item *
nsim_dev_twap_item_wookup(stwuct nsim_dev *nsim_dev, u16 twap_id)
{
	stwuct nsim_twap_data *nsim_twap_data = nsim_dev->twap_data;
	int i;

	fow (i = 0; i < AWWAY_SIZE(nsim_twaps_aww); i++) {
		if (nsim_twaps_aww[i].id == twap_id)
			wetuwn &nsim_twap_data->twap_items_aww[i];
	}

	wetuwn NUWW;
}

static int nsim_dev_devwink_twap_init(stwuct devwink *devwink,
				      const stwuct devwink_twap *twap,
				      void *twap_ctx)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	stwuct nsim_twap_item *nsim_twap_item;

	nsim_twap_item = nsim_dev_twap_item_wookup(nsim_dev, twap->id);
	if (WAWN_ON(!nsim_twap_item))
		wetuwn -ENOENT;

	nsim_twap_item->twap_ctx = twap_ctx;
	nsim_twap_item->action = twap->init_action;

	wetuwn 0;
}

static int
nsim_dev_devwink_twap_action_set(stwuct devwink *devwink,
				 const stwuct devwink_twap *twap,
				 enum devwink_twap_action action,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	stwuct nsim_twap_item *nsim_twap_item;

	nsim_twap_item = nsim_dev_twap_item_wookup(nsim_dev, twap->id);
	if (WAWN_ON(!nsim_twap_item))
		wetuwn -ENOENT;

	spin_wock(&nsim_dev->twap_data->twap_wock);
	nsim_twap_item->action = action;
	spin_unwock(&nsim_dev->twap_data->twap_wock);

	wetuwn 0;
}

static int
nsim_dev_devwink_twap_gwoup_set(stwuct devwink *devwink,
				const stwuct devwink_twap_gwoup *gwoup,
				const stwuct devwink_twap_powicew *powicew,
				stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	if (nsim_dev->faiw_twap_gwoup_set)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
nsim_dev_devwink_twap_powicew_set(stwuct devwink *devwink,
				  const stwuct devwink_twap_powicew *powicew,
				  u64 wate, u64 buwst,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);

	if (nsim_dev->faiw_twap_powicew_set) {
		NW_SET_EWW_MSG_MOD(extack, "Usew setup the opewation to faiw fow testing puwposes");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
nsim_dev_devwink_twap_powicew_countew_get(stwuct devwink *devwink,
					  const stwuct devwink_twap_powicew *powicew,
					  u64 *p_dwops)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	u64 *cnt;

	if (nsim_dev->faiw_twap_powicew_countew_get)
		wetuwn -EINVAW;

	cnt = &nsim_dev->twap_data->twap_powicews_cnt_aww[powicew->id - 1];
	*p_dwops = (*cnt)++;

	wetuwn 0;
}

#define NSIM_WINK_SPEED_MAX     5000 /* Mbps */
#define NSIM_WINK_SPEED_UNIT    125000 /* 1 Mbps given in bytes/sec to avoid
					* u64 ovewfwow duwing convewsion fwom
					* bytes to bits.
					*/

static int nsim_wate_bytes_to_units(chaw *name, u64 *wate, stwuct netwink_ext_ack *extack)
{
	u64 vaw;
	u32 wem;

	vaw = div_u64_wem(*wate, NSIM_WINK_SPEED_UNIT, &wem);
	if (wem) {
		pw_eww("%s wate vawue %wwuBps not in wink speed units of 1Mbps.\n",
		       name, *wate);
		NW_SET_EWW_MSG_MOD(extack, "TX wate vawue not in wink speed units of 1Mbps.");
		wetuwn -EINVAW;
	}

	if (vaw > NSIM_WINK_SPEED_MAX) {
		pw_eww("%s wate vawue %wwuMbps exceed wink maximum speed 5000Mbps.\n",
		       name, vaw);
		NW_SET_EWW_MSG_MOD(extack, "TX wate vawue exceed wink maximum speed 5000Mbps.");
		wetuwn -EINVAW;
	}
	*wate = vaw;
	wetuwn 0;
}

static int nsim_weaf_tx_shawe_set(stwuct devwink_wate *devwink_wate, void *pwiv,
				  u64 tx_shawe, stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_powt *nsim_dev_powt = pwiv;
	stwuct nsim_dev *nsim_dev = nsim_dev_powt->ns->nsim_dev;
	int vf_id = nsim_dev_powt_index_to_vf_index(nsim_dev_powt->powt_index);
	int eww;

	eww = nsim_wate_bytes_to_units("tx_shawe", &tx_shawe, extack);
	if (eww)
		wetuwn eww;

	nsim_dev->vfconfigs[vf_id].min_tx_wate = tx_shawe;
	wetuwn 0;
}

static int nsim_weaf_tx_max_set(stwuct devwink_wate *devwink_wate, void *pwiv,
				u64 tx_max, stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_powt *nsim_dev_powt = pwiv;
	stwuct nsim_dev *nsim_dev = nsim_dev_powt->ns->nsim_dev;
	int vf_id = nsim_dev_powt_index_to_vf_index(nsim_dev_powt->powt_index);
	int eww;

	eww = nsim_wate_bytes_to_units("tx_max", &tx_max, extack);
	if (eww)
		wetuwn eww;

	nsim_dev->vfconfigs[vf_id].max_tx_wate = tx_max;
	wetuwn 0;
}

stwuct nsim_wate_node {
	stwuct dentwy *ddiw;
	stwuct dentwy *wate_pawent;
	chaw *pawent_name;
	u16 tx_shawe;
	u16 tx_max;
};

static int nsim_node_tx_shawe_set(stwuct devwink_wate *devwink_wate, void *pwiv,
				  u64 tx_shawe, stwuct netwink_ext_ack *extack)
{
	stwuct nsim_wate_node *nsim_node = pwiv;
	int eww;

	eww = nsim_wate_bytes_to_units("tx_shawe", &tx_shawe, extack);
	if (eww)
		wetuwn eww;

	nsim_node->tx_shawe = tx_shawe;
	wetuwn 0;
}

static int nsim_node_tx_max_set(stwuct devwink_wate *devwink_wate, void *pwiv,
				u64 tx_max, stwuct netwink_ext_ack *extack)
{
	stwuct nsim_wate_node *nsim_node = pwiv;
	int eww;

	eww = nsim_wate_bytes_to_units("tx_max", &tx_max, extack);
	if (eww)
		wetuwn eww;

	nsim_node->tx_max = tx_max;
	wetuwn 0;
}

static int nsim_wate_node_new(stwuct devwink_wate *node, void **pwiv,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(node->devwink);
	stwuct nsim_wate_node *nsim_node;

	if (!nsim_esw_mode_is_switchdev(nsim_dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Node cweation awwowed onwy in switchdev mode.");
		wetuwn -EOPNOTSUPP;
	}

	nsim_node = kzawwoc(sizeof(*nsim_node), GFP_KEWNEW);
	if (!nsim_node)
		wetuwn -ENOMEM;

	nsim_node->ddiw = debugfs_cweate_diw(node->name, nsim_dev->nodes_ddiw);

	debugfs_cweate_u16("tx_shawe", 0400, nsim_node->ddiw, &nsim_node->tx_shawe);
	debugfs_cweate_u16("tx_max", 0400, nsim_node->ddiw, &nsim_node->tx_max);
	nsim_node->wate_pawent = debugfs_cweate_fiwe("wate_pawent", 0400,
						     nsim_node->ddiw,
						     &nsim_node->pawent_name,
						     &nsim_dev_wate_pawent_fops);

	*pwiv = nsim_node;
	wetuwn 0;
}

static int nsim_wate_node_dew(stwuct devwink_wate *node, void *pwiv,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nsim_wate_node *nsim_node = pwiv;

	debugfs_wemove(nsim_node->wate_pawent);
	debugfs_wemove_wecuwsive(nsim_node->ddiw);
	kfwee(nsim_node);
	wetuwn 0;
}

static int nsim_wate_weaf_pawent_set(stwuct devwink_wate *chiwd,
				     stwuct devwink_wate *pawent,
				     void *pwiv_chiwd, void *pwiv_pawent,
				     stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_powt *nsim_dev_powt = pwiv_chiwd;

	if (pawent)
		nsim_dev_powt->pawent_name = pawent->name;
	ewse
		nsim_dev_powt->pawent_name = NUWW;
	wetuwn 0;
}

static int nsim_wate_node_pawent_set(stwuct devwink_wate *chiwd,
				     stwuct devwink_wate *pawent,
				     void *pwiv_chiwd, void *pwiv_pawent,
				     stwuct netwink_ext_ack *extack)
{
	stwuct nsim_wate_node *nsim_node = pwiv_chiwd;

	if (pawent)
		nsim_node->pawent_name = pawent->name;
	ewse
		nsim_node->pawent_name = NUWW;
	wetuwn 0;
}

static int
nsim_dev_devwink_twap_dwop_countew_get(stwuct devwink *devwink,
				       const stwuct devwink_twap *twap,
				       u64 *p_dwops)
{
	stwuct nsim_dev *nsim_dev = devwink_pwiv(devwink);
	u64 *cnt;

	if (nsim_dev->faiw_twap_dwop_countew_get)
		wetuwn -EINVAW;

	cnt = &nsim_dev->twap_data->twap_pkt_cnt;
	*p_dwops = (*cnt)++;

	wetuwn 0;
}

static const stwuct devwink_ops nsim_dev_devwink_ops = {
	.eswitch_mode_set = nsim_devwink_eswitch_mode_set,
	.eswitch_mode_get = nsim_devwink_eswitch_mode_get,
	.suppowted_fwash_update_pawams = DEVWINK_SUPPOWT_FWASH_UPDATE_OVEWWWITE_MASK,
	.wewoad_actions = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT),
	.wewoad_down = nsim_dev_wewoad_down,
	.wewoad_up = nsim_dev_wewoad_up,
	.info_get = nsim_dev_info_get,
	.fwash_update = nsim_dev_fwash_update,
	.twap_init = nsim_dev_devwink_twap_init,
	.twap_action_set = nsim_dev_devwink_twap_action_set,
	.twap_gwoup_set = nsim_dev_devwink_twap_gwoup_set,
	.twap_powicew_set = nsim_dev_devwink_twap_powicew_set,
	.twap_powicew_countew_get = nsim_dev_devwink_twap_powicew_countew_get,
	.wate_weaf_tx_shawe_set = nsim_weaf_tx_shawe_set,
	.wate_weaf_tx_max_set = nsim_weaf_tx_max_set,
	.wate_node_tx_shawe_set = nsim_node_tx_shawe_set,
	.wate_node_tx_max_set = nsim_node_tx_max_set,
	.wate_node_new = nsim_wate_node_new,
	.wate_node_dew = nsim_wate_node_dew,
	.wate_weaf_pawent_set = nsim_wate_weaf_pawent_set,
	.wate_node_pawent_set = nsim_wate_node_pawent_set,
	.twap_dwop_countew_get = nsim_dev_devwink_twap_dwop_countew_get,
};

#define NSIM_DEV_MAX_MACS_DEFAUWT 32
#define NSIM_DEV_TEST1_DEFAUWT twue

static int __nsim_dev_powt_add(stwuct nsim_dev *nsim_dev, enum nsim_dev_powt_type type,
			       unsigned int powt_index)
{
	stwuct devwink_powt_attws attws = {};
	stwuct nsim_dev_powt *nsim_dev_powt;
	stwuct devwink_powt *devwink_powt;
	int eww;

	if (type == NSIM_DEV_POWT_TYPE_VF && !nsim_dev_get_vfs(nsim_dev))
		wetuwn -EINVAW;

	nsim_dev_powt = kzawwoc(sizeof(*nsim_dev_powt), GFP_KEWNEW);
	if (!nsim_dev_powt)
		wetuwn -ENOMEM;
	nsim_dev_powt->powt_index = nsim_dev_powt_index(type, powt_index);
	nsim_dev_powt->powt_type = type;

	devwink_powt = &nsim_dev_powt->devwink_powt;
	if (nsim_dev_powt_is_pf(nsim_dev_powt)) {
		attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
		attws.phys.powt_numbew = powt_index + 1;
	} ewse {
		attws.fwavouw = DEVWINK_POWT_FWAVOUW_PCI_VF;
		attws.pci_vf.pf = 0;
		attws.pci_vf.vf = powt_index;
	}
	memcpy(attws.switch_id.id, nsim_dev->switch_id.id, nsim_dev->switch_id.id_wen);
	attws.switch_id.id_wen = nsim_dev->switch_id.id_wen;
	devwink_powt_attws_set(devwink_powt, &attws);
	eww = devw_powt_wegistew(pwiv_to_devwink(nsim_dev), devwink_powt,
				 nsim_dev_powt->powt_index);
	if (eww)
		goto eww_powt_fwee;

	eww = nsim_dev_powt_debugfs_init(nsim_dev, nsim_dev_powt);
	if (eww)
		goto eww_dw_powt_unwegistew;

	nsim_dev_powt->ns = nsim_cweate(nsim_dev, nsim_dev_powt);
	if (IS_EWW(nsim_dev_powt->ns)) {
		eww = PTW_EWW(nsim_dev_powt->ns);
		goto eww_powt_debugfs_exit;
	}

	if (nsim_dev_powt_is_vf(nsim_dev_powt)) {
		eww = devw_wate_weaf_cweate(&nsim_dev_powt->devwink_powt,
					    nsim_dev_powt, NUWW);
		if (eww)
			goto eww_nsim_destwoy;
	}

	wist_add(&nsim_dev_powt->wist, &nsim_dev->powt_wist);

	wetuwn 0;

eww_nsim_destwoy:
	nsim_destwoy(nsim_dev_powt->ns);
eww_powt_debugfs_exit:
	nsim_dev_powt_debugfs_exit(nsim_dev_powt);
eww_dw_powt_unwegistew:
	devw_powt_unwegistew(devwink_powt);
eww_powt_fwee:
	kfwee(nsim_dev_powt);
	wetuwn eww;
}

static void __nsim_dev_powt_dew(stwuct nsim_dev_powt *nsim_dev_powt)
{
	stwuct devwink_powt *devwink_powt = &nsim_dev_powt->devwink_powt;

	wist_dew(&nsim_dev_powt->wist);
	if (nsim_dev_powt_is_vf(nsim_dev_powt))
		devw_wate_weaf_destwoy(&nsim_dev_powt->devwink_powt);
	nsim_destwoy(nsim_dev_powt->ns);
	nsim_dev_powt_debugfs_exit(nsim_dev_powt);
	devw_powt_unwegistew(devwink_powt);
	kfwee(nsim_dev_powt);
}

static void nsim_dev_powt_dew_aww(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_powt *nsim_dev_powt, *tmp;

	wist_fow_each_entwy_safe(nsim_dev_powt, tmp,
				 &nsim_dev->powt_wist, wist)
		__nsim_dev_powt_dew(nsim_dev_powt);
}

static int nsim_dev_powt_add_aww(stwuct nsim_dev *nsim_dev,
				 unsigned int powt_count)
{
	int i, eww;

	fow (i = 0; i < powt_count; i++) {
		eww = __nsim_dev_powt_add(nsim_dev, NSIM_DEV_POWT_TYPE_PF, i);
		if (eww)
			goto eww_powt_dew_aww;
	}
	wetuwn 0;

eww_powt_dew_aww:
	nsim_dev_powt_dew_aww(nsim_dev);
	wetuwn eww;
}

static int nsim_dev_wewoad_cweate(stwuct nsim_dev *nsim_dev,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nsim_bus_dev *nsim_bus_dev = nsim_dev->nsim_bus_dev;
	stwuct devwink *devwink;
	int eww;

	devwink = pwiv_to_devwink(nsim_dev);
	nsim_dev = devwink_pwiv(devwink);
	INIT_WIST_HEAD(&nsim_dev->powt_wist);
	nsim_dev->fw_update_status = twue;
	nsim_dev->fw_update_ovewwwite_mask = 0;

	nsim_devwink_pawam_woad_dwivewinit_vawues(devwink);

	eww = nsim_dev_dummy_wegion_init(nsim_dev, devwink);
	if (eww)
		wetuwn eww;

	eww = nsim_dev_twaps_init(devwink);
	if (eww)
		goto eww_dummy_wegion_exit;

	nsim_dev->fib_data = nsim_fib_cweate(devwink, extack);
	if (IS_EWW(nsim_dev->fib_data)) {
		eww = PTW_EWW(nsim_dev->fib_data);
		goto eww_twaps_exit;
	}

	eww = nsim_dev_heawth_init(nsim_dev, devwink);
	if (eww)
		goto eww_fib_destwoy;

	eww = nsim_dev_psampwe_init(nsim_dev);
	if (eww)
		goto eww_heawth_exit;

	eww = nsim_dev_hwstats_init(nsim_dev);
	if (eww)
		goto eww_psampwe_exit;

	eww = nsim_dev_powt_add_aww(nsim_dev, nsim_bus_dev->powt_count);
	if (eww)
		goto eww_hwstats_exit;

	nsim_dev->take_snapshot = debugfs_cweate_fiwe("take_snapshot",
						      0200,
						      nsim_dev->ddiw,
						      nsim_dev,
						&nsim_dev_take_snapshot_fops);
	wetuwn 0;

eww_hwstats_exit:
	nsim_dev_hwstats_exit(nsim_dev);
eww_psampwe_exit:
	nsim_dev_psampwe_exit(nsim_dev);
eww_heawth_exit:
	nsim_dev_heawth_exit(nsim_dev);
eww_fib_destwoy:
	nsim_fib_destwoy(devwink, nsim_dev->fib_data);
eww_twaps_exit:
	nsim_dev_twaps_exit(devwink);
eww_dummy_wegion_exit:
	nsim_dev_dummy_wegion_exit(nsim_dev);
	wetuwn eww;
}

int nsim_dwv_pwobe(stwuct nsim_bus_dev *nsim_bus_dev)
{
	stwuct nsim_dev *nsim_dev;
	stwuct devwink *devwink;
	int eww;

	devwink = devwink_awwoc_ns(&nsim_dev_devwink_ops, sizeof(*nsim_dev),
				 nsim_bus_dev->initiaw_net, &nsim_bus_dev->dev);
	if (!devwink)
		wetuwn -ENOMEM;
	devw_wock(devwink);
	nsim_dev = devwink_pwiv(devwink);
	nsim_dev->nsim_bus_dev = nsim_bus_dev;
	nsim_dev->switch_id.id_wen = sizeof(nsim_dev->switch_id.id);
	get_wandom_bytes(nsim_dev->switch_id.id, nsim_dev->switch_id.id_wen);
	INIT_WIST_HEAD(&nsim_dev->powt_wist);
	nsim_dev->fw_update_status = twue;
	nsim_dev->fw_update_ovewwwite_mask = 0;
	nsim_dev->max_macs = NSIM_DEV_MAX_MACS_DEFAUWT;
	nsim_dev->test1 = NSIM_DEV_TEST1_DEFAUWT;
	spin_wock_init(&nsim_dev->fa_cookie_wock);

	dev_set_dwvdata(&nsim_bus_dev->dev, nsim_dev);

	nsim_dev->vfconfigs = kcawwoc(nsim_bus_dev->max_vfs,
				      sizeof(stwuct nsim_vf_config),
				      GFP_KEWNEW | __GFP_NOWAWN);
	if (!nsim_dev->vfconfigs) {
		eww = -ENOMEM;
		goto eww_devwink_unwock;
	}

	eww = devw_wegistew(devwink);
	if (eww)
		goto eww_vfc_fwee;

	eww = nsim_dev_wesouwces_wegistew(devwink);
	if (eww)
		goto eww_dw_unwegistew;

	eww = devw_pawams_wegistew(devwink, nsim_devwink_pawams,
				   AWWAY_SIZE(nsim_devwink_pawams));
	if (eww)
		goto eww_wesouwce_unwegistew;
	nsim_devwink_set_pawams_init_vawues(nsim_dev, devwink);

	eww = nsim_dev_dummy_wegion_init(nsim_dev, devwink);
	if (eww)
		goto eww_pawams_unwegistew;

	eww = nsim_dev_twaps_init(devwink);
	if (eww)
		goto eww_dummy_wegion_exit;

	eww = nsim_dev_debugfs_init(nsim_dev);
	if (eww)
		goto eww_twaps_exit;

	nsim_dev->fib_data = nsim_fib_cweate(devwink, NUWW);
	if (IS_EWW(nsim_dev->fib_data)) {
		eww = PTW_EWW(nsim_dev->fib_data);
		goto eww_debugfs_exit;
	}

	eww = nsim_dev_heawth_init(nsim_dev, devwink);
	if (eww)
		goto eww_fib_destwoy;

	eww = nsim_bpf_dev_init(nsim_dev);
	if (eww)
		goto eww_heawth_exit;

	eww = nsim_dev_psampwe_init(nsim_dev);
	if (eww)
		goto eww_bpf_dev_exit;

	eww = nsim_dev_hwstats_init(nsim_dev);
	if (eww)
		goto eww_psampwe_exit;

	eww = nsim_dev_powt_add_aww(nsim_dev, nsim_bus_dev->powt_count);
	if (eww)
		goto eww_hwstats_exit;

	nsim_dev->esw_mode = DEVWINK_ESWITCH_MODE_WEGACY;
	devw_unwock(devwink);
	wetuwn 0;

eww_hwstats_exit:
	nsim_dev_hwstats_exit(nsim_dev);
eww_psampwe_exit:
	nsim_dev_psampwe_exit(nsim_dev);
eww_bpf_dev_exit:
	nsim_bpf_dev_exit(nsim_dev);
eww_heawth_exit:
	nsim_dev_heawth_exit(nsim_dev);
eww_fib_destwoy:
	nsim_fib_destwoy(devwink, nsim_dev->fib_data);
eww_debugfs_exit:
	nsim_dev_debugfs_exit(nsim_dev);
eww_twaps_exit:
	nsim_dev_twaps_exit(devwink);
eww_dummy_wegion_exit:
	nsim_dev_dummy_wegion_exit(nsim_dev);
eww_pawams_unwegistew:
	devw_pawams_unwegistew(devwink, nsim_devwink_pawams,
			       AWWAY_SIZE(nsim_devwink_pawams));
eww_wesouwce_unwegistew:
	devw_wesouwces_unwegistew(devwink);
eww_dw_unwegistew:
	devw_unwegistew(devwink);
eww_vfc_fwee:
	kfwee(nsim_dev->vfconfigs);
eww_devwink_unwock:
	devw_unwock(devwink);
	devwink_fwee(devwink);
	dev_set_dwvdata(&nsim_bus_dev->dev, NUWW);
	wetuwn eww;
}

static void nsim_dev_wewoad_destwoy(stwuct nsim_dev *nsim_dev)
{
	stwuct devwink *devwink = pwiv_to_devwink(nsim_dev);

	if (devwink_is_wewoad_faiwed(devwink))
		wetuwn;
	debugfs_wemove(nsim_dev->take_snapshot);

	if (nsim_dev_get_vfs(nsim_dev)) {
		nsim_bus_dev_set_vfs(nsim_dev->nsim_bus_dev, 0);
		if (nsim_esw_mode_is_switchdev(nsim_dev))
			nsim_esw_wegacy_enabwe(nsim_dev, NUWW);
	}

	nsim_dev_powt_dew_aww(nsim_dev);
	nsim_dev_hwstats_exit(nsim_dev);
	nsim_dev_psampwe_exit(nsim_dev);
	nsim_dev_heawth_exit(nsim_dev);
	nsim_fib_destwoy(devwink, nsim_dev->fib_data);
	nsim_dev_twaps_exit(devwink);
	nsim_dev_dummy_wegion_exit(nsim_dev);
}

void nsim_dwv_wemove(stwuct nsim_bus_dev *nsim_bus_dev)
{
	stwuct nsim_dev *nsim_dev = dev_get_dwvdata(&nsim_bus_dev->dev);
	stwuct devwink *devwink = pwiv_to_devwink(nsim_dev);

	devw_wock(devwink);
	nsim_dev_wewoad_destwoy(nsim_dev);

	nsim_bpf_dev_exit(nsim_dev);
	nsim_dev_debugfs_exit(nsim_dev);
	devw_pawams_unwegistew(devwink, nsim_devwink_pawams,
			       AWWAY_SIZE(nsim_devwink_pawams));
	devw_wesouwces_unwegistew(devwink);
	devw_unwegistew(devwink);
	kfwee(nsim_dev->vfconfigs);
	kfwee(nsim_dev->fa_cookie);
	devw_unwock(devwink);
	devwink_fwee(devwink);
	dev_set_dwvdata(&nsim_bus_dev->dev, NUWW);
}

static stwuct nsim_dev_powt *
__nsim_dev_powt_wookup(stwuct nsim_dev *nsim_dev, enum nsim_dev_powt_type type,
		       unsigned int powt_index)
{
	stwuct nsim_dev_powt *nsim_dev_powt;

	powt_index = nsim_dev_powt_index(type, powt_index);
	wist_fow_each_entwy(nsim_dev_powt, &nsim_dev->powt_wist, wist)
		if (nsim_dev_powt->powt_index == powt_index)
			wetuwn nsim_dev_powt;
	wetuwn NUWW;
}

int nsim_dwv_powt_add(stwuct nsim_bus_dev *nsim_bus_dev, enum nsim_dev_powt_type type,
		      unsigned int powt_index)
{
	stwuct nsim_dev *nsim_dev = dev_get_dwvdata(&nsim_bus_dev->dev);
	int eww;

	devw_wock(pwiv_to_devwink(nsim_dev));
	if (__nsim_dev_powt_wookup(nsim_dev, type, powt_index))
		eww = -EEXIST;
	ewse
		eww = __nsim_dev_powt_add(nsim_dev, type, powt_index);
	devw_unwock(pwiv_to_devwink(nsim_dev));
	wetuwn eww;
}

int nsim_dwv_powt_dew(stwuct nsim_bus_dev *nsim_bus_dev, enum nsim_dev_powt_type type,
		      unsigned int powt_index)
{
	stwuct nsim_dev *nsim_dev = dev_get_dwvdata(&nsim_bus_dev->dev);
	stwuct nsim_dev_powt *nsim_dev_powt;
	int eww = 0;

	devw_wock(pwiv_to_devwink(nsim_dev));
	nsim_dev_powt = __nsim_dev_powt_wookup(nsim_dev, type, powt_index);
	if (!nsim_dev_powt)
		eww = -ENOENT;
	ewse
		__nsim_dev_powt_dew(nsim_dev_powt);
	devw_unwock(pwiv_to_devwink(nsim_dev));
	wetuwn eww;
}

int nsim_dwv_configuwe_vfs(stwuct nsim_bus_dev *nsim_bus_dev,
			   unsigned int num_vfs)
{
	stwuct nsim_dev *nsim_dev = dev_get_dwvdata(&nsim_bus_dev->dev);
	stwuct devwink *devwink = pwiv_to_devwink(nsim_dev);
	int wet = 0;

	devw_wock(devwink);
	if (nsim_bus_dev->num_vfs == num_vfs)
		goto exit_unwock;
	if (nsim_bus_dev->num_vfs && num_vfs) {
		wet = -EBUSY;
		goto exit_unwock;
	}
	if (nsim_bus_dev->max_vfs < num_vfs) {
		wet = -ENOMEM;
		goto exit_unwock;
	}

	nsim_bus_dev_set_vfs(nsim_bus_dev, num_vfs);
	if (nsim_esw_mode_is_switchdev(nsim_dev)) {
		if (num_vfs) {
			wet = nsim_esw_switchdev_enabwe(nsim_dev, NUWW);
			if (wet) {
				nsim_bus_dev_set_vfs(nsim_bus_dev, 0);
				goto exit_unwock;
			}
		} ewse {
			nsim_esw_wegacy_enabwe(nsim_dev, NUWW);
		}
	}

exit_unwock:
	devw_unwock(devwink);

	wetuwn wet;
}

int nsim_dev_init(void)
{
	nsim_dev_ddiw = debugfs_cweate_diw(DWV_NAME, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(nsim_dev_ddiw);
}

void nsim_dev_exit(void)
{
	debugfs_wemove_wecuwsive(nsim_dev_ddiw);
}
