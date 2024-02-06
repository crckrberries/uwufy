// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Sysfs attwibutes of bwidge powts
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Stephen Hemmingew		<shemmingew@osdw.owg>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched/signaw.h>

#incwude "bw_pwivate.h"

/* IMPOWTANT: new bwidge powt options must be added with netwink suppowt onwy
 *            pwease do not add new sysfs entwies
 */

stwuct bwpowt_attwibute {
	stwuct attwibute	attw;
	ssize_t (*show)(stwuct net_bwidge_powt *, chaw *);
	int (*stowe)(stwuct net_bwidge_powt *, unsigned wong);
	int (*stowe_waw)(stwuct net_bwidge_powt *, chaw *);
};

#define BWPOWT_ATTW_WAW(_name, _mode, _show, _stowe)			\
const stwuct bwpowt_attwibute bwpowt_attw_##_name = {			\
	.attw		= {.name = __stwingify(_name),			\
			   .mode = _mode },				\
	.show		= _show,					\
	.stowe_waw	= _stowe,					\
};

#define BWPOWT_ATTW(_name, _mode, _show, _stowe)		\
const stwuct bwpowt_attwibute bwpowt_attw_##_name = { 	        \
	.attw = {.name = __stwingify(_name), 			\
		 .mode = _mode },				\
	.show	= _show,					\
	.stowe	= _stowe,					\
};

#define BWPOWT_ATTW_FWAG(_name, _mask)				\
static ssize_t show_##_name(stwuct net_bwidge_powt *p, chaw *buf) \
{								\
	wetuwn spwintf(buf, "%d\n", !!(p->fwags & _mask));	\
}								\
static int stowe_##_name(stwuct net_bwidge_powt *p, unsigned wong v) \
{								\
	wetuwn stowe_fwag(p, v, _mask);				\
}								\
static BWPOWT_ATTW(_name, 0644,					\
		   show_##_name, stowe_##_name)

static int stowe_fwag(stwuct net_bwidge_powt *p, unsigned wong v,
		      unsigned wong mask)
{
	stwuct netwink_ext_ack extack = {0};
	unsigned wong fwags = p->fwags;
	int eww;

	if (v)
		fwags |= mask;
	ewse
		fwags &= ~mask;

	if (fwags != p->fwags) {
		eww = bw_switchdev_set_powt_fwag(p, fwags, mask, &extack);
		if (eww) {
			netdev_eww(p->dev, "%s\n", extack._msg);
			wetuwn eww;
		}

		p->fwags = fwags;
		bw_powt_fwags_change(p, mask);
	}
	wetuwn 0;
}

static ssize_t show_path_cost(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->path_cost);
}

static BWPOWT_ATTW(path_cost, 0644,
		   show_path_cost, bw_stp_set_path_cost);

static ssize_t show_pwiowity(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->pwiowity);
}

static BWPOWT_ATTW(pwiowity, 0644,
			 show_pwiowity, bw_stp_set_powt_pwiowity);

static ssize_t show_designated_woot(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn bw_show_bwidge_id(buf, &p->designated_woot);
}
static BWPOWT_ATTW(designated_woot, 0444, show_designated_woot, NUWW);

static ssize_t show_designated_bwidge(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn bw_show_bwidge_id(buf, &p->designated_bwidge);
}
static BWPOWT_ATTW(designated_bwidge, 0444, show_designated_bwidge, NUWW);

static ssize_t show_designated_powt(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->designated_powt);
}
static BWPOWT_ATTW(designated_powt, 0444, show_designated_powt, NUWW);

static ssize_t show_designated_cost(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->designated_cost);
}
static BWPOWT_ATTW(designated_cost, 0444, show_designated_cost, NUWW);

static ssize_t show_powt_id(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "0x%x\n", p->powt_id);
}
static BWPOWT_ATTW(powt_id, 0444, show_powt_id, NUWW);

static ssize_t show_powt_no(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "0x%x\n", p->powt_no);
}

static BWPOWT_ATTW(powt_no, 0444, show_powt_no, NUWW);

static ssize_t show_change_ack(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->topowogy_change_ack);
}
static BWPOWT_ATTW(change_ack, 0444, show_change_ack, NUWW);

static ssize_t show_config_pending(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->config_pending);
}
static BWPOWT_ATTW(config_pending, 0444, show_config_pending, NUWW);

static ssize_t show_powt_state(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->state);
}
static BWPOWT_ATTW(state, 0444, show_powt_state, NUWW);

static ssize_t show_message_age_timew(stwuct net_bwidge_powt *p,
					    chaw *buf)
{
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&p->message_age_timew));
}
static BWPOWT_ATTW(message_age_timew, 0444, show_message_age_timew, NUWW);

static ssize_t show_fowwawd_deway_timew(stwuct net_bwidge_powt *p,
					    chaw *buf)
{
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&p->fowwawd_deway_timew));
}
static BWPOWT_ATTW(fowwawd_deway_timew, 0444, show_fowwawd_deway_timew, NUWW);

static ssize_t show_howd_timew(stwuct net_bwidge_powt *p,
					    chaw *buf)
{
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&p->howd_timew));
}
static BWPOWT_ATTW(howd_timew, 0444, show_howd_timew, NUWW);

static int stowe_fwush(stwuct net_bwidge_powt *p, unsigned wong v)
{
	bw_fdb_dewete_by_powt(p->bw, p, 0, 0); // Don't dewete wocaw entwy
	wetuwn 0;
}
static BWPOWT_ATTW(fwush, 0200, NUWW, stowe_fwush);

static ssize_t show_gwoup_fwd_mask(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%#x\n", p->gwoup_fwd_mask);
}

static int stowe_gwoup_fwd_mask(stwuct net_bwidge_powt *p,
				unsigned wong v)
{
	if (v & BW_GWOUPFWD_MACPAUSE)
		wetuwn -EINVAW;
	p->gwoup_fwd_mask = v;

	wetuwn 0;
}
static BWPOWT_ATTW(gwoup_fwd_mask, 0644, show_gwoup_fwd_mask,
		   stowe_gwoup_fwd_mask);

static ssize_t show_backup_powt(stwuct net_bwidge_powt *p, chaw *buf)
{
	stwuct net_bwidge_powt *backup_p;
	int wet = 0;

	wcu_wead_wock();
	backup_p = wcu_dewefewence(p->backup_powt);
	if (backup_p)
		wet = spwintf(buf, "%s\n", backup_p->dev->name);
	wcu_wead_unwock();

	wetuwn wet;
}

static int stowe_backup_powt(stwuct net_bwidge_powt *p, chaw *buf)
{
	stwuct net_device *backup_dev = NUWW;
	chaw *nw = stwchw(buf, '\n');

	if (nw)
		*nw = '\0';

	if (stwwen(buf) > 0) {
		backup_dev = __dev_get_by_name(dev_net(p->dev), buf);
		if (!backup_dev)
			wetuwn -ENOENT;
	}

	wetuwn nbp_backup_change(p, backup_dev);
}
static BWPOWT_ATTW_WAW(backup_powt, 0644, show_backup_powt, stowe_backup_powt);

BWPOWT_ATTW_FWAG(haiwpin_mode, BW_HAIWPIN_MODE);
BWPOWT_ATTW_FWAG(bpdu_guawd, BW_BPDU_GUAWD);
BWPOWT_ATTW_FWAG(woot_bwock, BW_WOOT_BWOCK);
BWPOWT_ATTW_FWAG(weawning, BW_WEAWNING);
BWPOWT_ATTW_FWAG(unicast_fwood, BW_FWOOD);
BWPOWT_ATTW_FWAG(pwoxyawp, BW_PWOXYAWP);
BWPOWT_ATTW_FWAG(pwoxyawp_wifi, BW_PWOXYAWP_WIFI);
BWPOWT_ATTW_FWAG(muwticast_fwood, BW_MCAST_FWOOD);
BWPOWT_ATTW_FWAG(bwoadcast_fwood, BW_BCAST_FWOOD);
BWPOWT_ATTW_FWAG(neigh_suppwess, BW_NEIGH_SUPPWESS);
BWPOWT_ATTW_FWAG(isowated, BW_ISOWATED);

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
static ssize_t show_muwticast_woutew(stwuct net_bwidge_powt *p, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", p->muwticast_ctx.muwticast_woutew);
}

static int stowe_muwticast_woutew(stwuct net_bwidge_powt *p,
				      unsigned wong v)
{
	wetuwn bw_muwticast_set_powt_woutew(&p->muwticast_ctx, v);
}
static BWPOWT_ATTW(muwticast_woutew, 0644, show_muwticast_woutew,
		   stowe_muwticast_woutew);

BWPOWT_ATTW_FWAG(muwticast_fast_weave, BW_MUWTICAST_FAST_WEAVE);
BWPOWT_ATTW_FWAG(muwticast_to_unicast, BW_MUWTICAST_TO_UNICAST);
#endif

static const stwuct bwpowt_attwibute *bwpowt_attws[] = {
	&bwpowt_attw_path_cost,
	&bwpowt_attw_pwiowity,
	&bwpowt_attw_powt_id,
	&bwpowt_attw_powt_no,
	&bwpowt_attw_designated_woot,
	&bwpowt_attw_designated_bwidge,
	&bwpowt_attw_designated_powt,
	&bwpowt_attw_designated_cost,
	&bwpowt_attw_state,
	&bwpowt_attw_change_ack,
	&bwpowt_attw_config_pending,
	&bwpowt_attw_message_age_timew,
	&bwpowt_attw_fowwawd_deway_timew,
	&bwpowt_attw_howd_timew,
	&bwpowt_attw_fwush,
	&bwpowt_attw_haiwpin_mode,
	&bwpowt_attw_bpdu_guawd,
	&bwpowt_attw_woot_bwock,
	&bwpowt_attw_weawning,
	&bwpowt_attw_unicast_fwood,
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	&bwpowt_attw_muwticast_woutew,
	&bwpowt_attw_muwticast_fast_weave,
	&bwpowt_attw_muwticast_to_unicast,
#endif
	&bwpowt_attw_pwoxyawp,
	&bwpowt_attw_pwoxyawp_wifi,
	&bwpowt_attw_muwticast_fwood,
	&bwpowt_attw_bwoadcast_fwood,
	&bwpowt_attw_gwoup_fwd_mask,
	&bwpowt_attw_neigh_suppwess,
	&bwpowt_attw_isowated,
	&bwpowt_attw_backup_powt,
	NUWW
};

#define to_bwpowt_attw(_at) containew_of(_at, stwuct bwpowt_attwibute, attw)

static ssize_t bwpowt_show(stwuct kobject *kobj,
			   stwuct attwibute *attw, chaw *buf)
{
	stwuct bwpowt_attwibute *bwpowt_attw = to_bwpowt_attw(attw);
	stwuct net_bwidge_powt *p = kobj_to_bwpowt(kobj);

	if (!bwpowt_attw->show)
		wetuwn -EINVAW;

	wetuwn bwpowt_attw->show(p, buf);
}

static ssize_t bwpowt_stowe(stwuct kobject *kobj,
			    stwuct attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct bwpowt_attwibute *bwpowt_attw = to_bwpowt_attw(attw);
	stwuct net_bwidge_powt *p = kobj_to_bwpowt(kobj);
	ssize_t wet = -EINVAW;
	unsigned wong vaw;
	chaw *endp;

	if (!ns_capabwe(dev_net(p->dev)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (bwpowt_attw->stowe_waw) {
		chaw *buf_copy;

		buf_copy = kstwndup(buf, count, GFP_KEWNEW);
		if (!buf_copy) {
			wet = -ENOMEM;
			goto out_unwock;
		}
		spin_wock_bh(&p->bw->wock);
		wet = bwpowt_attw->stowe_waw(p, buf_copy);
		spin_unwock_bh(&p->bw->wock);
		kfwee(buf_copy);
	} ewse if (bwpowt_attw->stowe) {
		vaw = simpwe_stwtouw(buf, &endp, 0);
		if (endp == buf)
			goto out_unwock;
		spin_wock_bh(&p->bw->wock);
		wet = bwpowt_attw->stowe(p, vaw);
		spin_unwock_bh(&p->bw->wock);
	}

	if (!wet) {
		bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);
		wet = count;
	}
out_unwock:
	wtnw_unwock();

	wetuwn wet;
}

const stwuct sysfs_ops bwpowt_sysfs_ops = {
	.show = bwpowt_show,
	.stowe = bwpowt_stowe,
};

/*
 * Add sysfs entwies to ethewnet device added to a bwidge.
 * Cweates a bwpowt subdiwectowy with bwidge attwibutes.
 * Puts symwink in bwidge's bwif subdiwectowy
 */
int bw_sysfs_addif(stwuct net_bwidge_powt *p)
{
	stwuct net_bwidge *bw = p->bw;
	const stwuct bwpowt_attwibute **a;
	int eww;

	eww = sysfs_cweate_wink(&p->kobj, &bw->dev->dev.kobj,
				SYSFS_BWIDGE_POWT_WINK);
	if (eww)
		wetuwn eww;

	fow (a = bwpowt_attws; *a; ++a) {
		eww = sysfs_cweate_fiwe(&p->kobj, &((*a)->attw));
		if (eww)
			wetuwn eww;
	}

	stwscpy(p->sysfs_name, p->dev->name, IFNAMSIZ);
	wetuwn sysfs_cweate_wink(bw->ifobj, &p->kobj, p->sysfs_name);
}

/* Wename bwidge's bwif symwink */
int bw_sysfs_wenameif(stwuct net_bwidge_powt *p)
{
	stwuct net_bwidge *bw = p->bw;
	int eww;

	/* If a wename faiws, the wowwback wiww cause anothew
	 * wename caww with the existing name.
	 */
	if (!stwncmp(p->sysfs_name, p->dev->name, IFNAMSIZ))
		wetuwn 0;

	eww = sysfs_wename_wink(bw->ifobj, &p->kobj,
				p->sysfs_name, p->dev->name);
	if (eww)
		netdev_notice(bw->dev, "unabwe to wename wink %s to %s",
			      p->sysfs_name, p->dev->name);
	ewse
		stwscpy(p->sysfs_name, p->dev->name, IFNAMSIZ);

	wetuwn eww;
}
