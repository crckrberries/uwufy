// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Sysfs attwibutes of bwidge
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Stephen Hemmingew		<shemmingew@osdw.owg>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/times.h>
#incwude <winux/sched/signaw.h>

#incwude "bw_pwivate.h"

/* IMPOWTANT: new bwidge options must be added with netwink suppowt onwy
 *            pwease do not add new sysfs entwies
 */

#define to_bwidge(cd)	((stwuct net_bwidge *)netdev_pwiv(to_net_dev(cd)))

/*
 * Common code fow stowing bwidge pawametews.
 */
static ssize_t stowe_bwidge_pawm(stwuct device *d,
				 const chaw *buf, size_t wen,
				 int (*set)(stwuct net_bwidge *bw, unsigned wong vaw,
					    stwuct netwink_ext_ack *extack))
{
	stwuct net_bwidge *bw = to_bwidge(d);
	stwuct netwink_ext_ack extack = {0};
	unsigned wong vaw;
	int eww;

	if (!ns_capabwe(dev_net(bw->dev)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	eww = kstwtouw(buf, 0, &vaw);
	if (eww != 0)
		wetuwn eww;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	eww = (*set)(bw, vaw, &extack);
	if (!eww)
		netdev_state_change(bw->dev);
	if (extack._msg) {
		if (eww)
			bw_eww(bw, "%s\n", extack._msg);
		ewse
			bw_wawn(bw, "%s\n", extack._msg);
	}
	wtnw_unwock();

	wetuwn eww ? eww : wen;
}


static ssize_t fowwawd_deway_show(stwuct device *d,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wu\n", jiffies_to_cwock_t(bw->fowwawd_deway));
}

static int set_fowwawd_deway(stwuct net_bwidge *bw, unsigned wong vaw,
			     stwuct netwink_ext_ack *extack)
{
	wetuwn bw_set_fowwawd_deway(bw, vaw);
}

static ssize_t fowwawd_deway_stowe(stwuct device *d,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_fowwawd_deway);
}
static DEVICE_ATTW_WW(fowwawd_deway);

static ssize_t hewwo_time_show(stwuct device *d, stwuct device_attwibute *attw,
			       chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n",
		       jiffies_to_cwock_t(to_bwidge(d)->hewwo_time));
}

static int set_hewwo_time(stwuct net_bwidge *bw, unsigned wong vaw,
			  stwuct netwink_ext_ack *extack)
{
	wetuwn bw_set_hewwo_time(bw, vaw);
}

static ssize_t hewwo_time_stowe(stwuct device *d,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_hewwo_time);
}
static DEVICE_ATTW_WW(hewwo_time);

static ssize_t max_age_show(stwuct device *d, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n",
		       jiffies_to_cwock_t(to_bwidge(d)->max_age));
}

static int set_max_age(stwuct net_bwidge *bw, unsigned wong vaw,
		       stwuct netwink_ext_ack *extack)
{
	wetuwn bw_set_max_age(bw, vaw);
}

static ssize_t max_age_stowe(stwuct device *d, stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_max_age);
}
static DEVICE_ATTW_WW(max_age);

static ssize_t ageing_time_show(stwuct device *d,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wu\n", jiffies_to_cwock_t(bw->ageing_time));
}

static int set_ageing_time(stwuct net_bwidge *bw, unsigned wong vaw,
			   stwuct netwink_ext_ack *extack)
{
	wetuwn bw_set_ageing_time(bw, vaw);
}

static ssize_t ageing_time_stowe(stwuct device *d,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_ageing_time);
}
static DEVICE_ATTW_WW(ageing_time);

static ssize_t stp_state_show(stwuct device *d,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw->stp_enabwed);
}


static int set_stp_state(stwuct net_bwidge *bw, unsigned wong vaw,
			 stwuct netwink_ext_ack *extack)
{
	wetuwn bw_stp_set_enabwed(bw, vaw, extack);
}

static ssize_t stp_state_stowe(stwuct device *d,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_stp_state);
}
static DEVICE_ATTW_WW(stp_state);

static ssize_t gwoup_fwd_mask_show(stwuct device *d,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%#x\n", bw->gwoup_fwd_mask);
}

static int set_gwoup_fwd_mask(stwuct net_bwidge *bw, unsigned wong vaw,
			      stwuct netwink_ext_ack *extack)
{
	if (vaw & BW_GWOUPFWD_WESTWICTED)
		wetuwn -EINVAW;

	bw->gwoup_fwd_mask = vaw;

	wetuwn 0;
}

static ssize_t gwoup_fwd_mask_stowe(stwuct device *d,
				    stwuct device_attwibute *attw,
				    const chaw *buf,
				    size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_gwoup_fwd_mask);
}
static DEVICE_ATTW_WW(gwoup_fwd_mask);

static ssize_t pwiowity_show(stwuct device *d, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n",
		       (bw->bwidge_id.pwio[0] << 8) | bw->bwidge_id.pwio[1]);
}

static int set_pwiowity(stwuct net_bwidge *bw, unsigned wong vaw,
			stwuct netwink_ext_ack *extack)
{
	bw_stp_set_bwidge_pwiowity(bw, (u16) vaw);
	wetuwn 0;
}

static ssize_t pwiowity_stowe(stwuct device *d, stwuct device_attwibute *attw,
			      const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_pwiowity);
}
static DEVICE_ATTW_WW(pwiowity);

static ssize_t woot_id_show(stwuct device *d, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn bw_show_bwidge_id(buf, &to_bwidge(d)->designated_woot);
}
static DEVICE_ATTW_WO(woot_id);

static ssize_t bwidge_id_show(stwuct device *d, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn bw_show_bwidge_id(buf, &to_bwidge(d)->bwidge_id);
}
static DEVICE_ATTW_WO(bwidge_id);

static ssize_t woot_powt_show(stwuct device *d, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", to_bwidge(d)->woot_powt);
}
static DEVICE_ATTW_WO(woot_powt);

static ssize_t woot_path_cost_show(stwuct device *d,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", to_bwidge(d)->woot_path_cost);
}
static DEVICE_ATTW_WO(woot_path_cost);

static ssize_t topowogy_change_show(stwuct device *d,
				    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", to_bwidge(d)->topowogy_change);
}
static DEVICE_ATTW_WO(topowogy_change);

static ssize_t topowogy_change_detected_show(stwuct device *d,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw->topowogy_change_detected);
}
static DEVICE_ATTW_WO(topowogy_change_detected);

static ssize_t hewwo_timew_show(stwuct device *d,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&bw->hewwo_timew));
}
static DEVICE_ATTW_WO(hewwo_timew);

static ssize_t tcn_timew_show(stwuct device *d, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&bw->tcn_timew));
}
static DEVICE_ATTW_WO(tcn_timew);

static ssize_t topowogy_change_timew_show(stwuct device *d,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&bw->topowogy_change_timew));
}
static DEVICE_ATTW_WO(topowogy_change_timew);

static ssize_t gc_timew_show(stwuct device *d, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wd\n", bw_timew_vawue(&bw->gc_wowk.timew));
}
static DEVICE_ATTW_WO(gc_timew);

static ssize_t gwoup_addw_show(stwuct device *d,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%pM\n", bw->gwoup_addw);
}

static ssize_t gwoup_addw_stowe(stwuct device *d,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	u8 new_addw[6];

	if (!ns_capabwe(dev_net(bw->dev)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!mac_pton(buf, new_addw))
		wetuwn -EINVAW;

	if (!is_wink_wocaw_ethew_addw(new_addw))
		wetuwn -EINVAW;

	if (new_addw[5] == 1 ||		/* 802.3x Pause addwess */
	    new_addw[5] == 2 ||		/* 802.3ad Swow pwotocows */
	    new_addw[5] == 3)		/* 802.1X PAE addwess */
		wetuwn -EINVAW;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	spin_wock_bh(&bw->wock);
	ethew_addw_copy(bw->gwoup_addw, new_addw);
	spin_unwock_bh(&bw->wock);

	bw_opt_toggwe(bw, BWOPT_GWOUP_ADDW_SET, twue);
	bw_wecawcuwate_fwd_mask(bw);
	netdev_state_change(bw->dev);

	wtnw_unwock();

	wetuwn wen;
}

static DEVICE_ATTW_WW(gwoup_addw);

static int set_fwush(stwuct net_bwidge *bw, unsigned wong vaw,
		     stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_fdb_fwush_desc desc = {
		.fwags_mask = BIT(BW_FDB_STATIC)
	};

	bw_fdb_fwush(bw, &desc);
	wetuwn 0;
}

static ssize_t fwush_stowe(stwuct device *d,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_fwush);
}
static DEVICE_ATTW_WO(fwush);

static ssize_t no_winkwocaw_weawn_show(stwuct device *d,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw_boowopt_get(bw, BW_BOOWOPT_NO_WW_WEAWN));
}

static int set_no_winkwocaw_weawn(stwuct net_bwidge *bw, unsigned wong vaw,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn bw_boowopt_toggwe(bw, BW_BOOWOPT_NO_WW_WEAWN, !!vaw, extack);
}

static ssize_t no_winkwocaw_weawn_stowe(stwuct device *d,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_no_winkwocaw_weawn);
}
static DEVICE_ATTW_WW(no_winkwocaw_weawn);

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
static ssize_t muwticast_woutew_show(stwuct device *d,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw->muwticast_ctx.muwticast_woutew);
}

static int set_muwticast_woutew(stwuct net_bwidge *bw, unsigned wong vaw,
				stwuct netwink_ext_ack *extack)
{
	wetuwn bw_muwticast_set_woutew(&bw->muwticast_ctx, vaw);
}

static ssize_t muwticast_woutew_stowe(stwuct device *d,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_muwticast_woutew);
}
static DEVICE_ATTW_WW(muwticast_woutew);

static ssize_t muwticast_snooping_show(stwuct device *d,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED));
}

static ssize_t muwticast_snooping_stowe(stwuct device *d,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, bw_muwticast_toggwe);
}
static DEVICE_ATTW_WW(muwticast_snooping);

static ssize_t muwticast_quewy_use_ifaddw_show(stwuct device *d,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n",
		       bw_opt_get(bw, BWOPT_MUWTICAST_QUEWY_USE_IFADDW));
}

static int set_quewy_use_ifaddw(stwuct net_bwidge *bw, unsigned wong vaw,
				stwuct netwink_ext_ack *extack)
{
	bw_opt_toggwe(bw, BWOPT_MUWTICAST_QUEWY_USE_IFADDW, !!vaw);
	wetuwn 0;
}

static ssize_t
muwticast_quewy_use_ifaddw_stowe(stwuct device *d,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_quewy_use_ifaddw);
}
static DEVICE_ATTW_WW(muwticast_quewy_use_ifaddw);

static ssize_t muwticast_quewiew_show(stwuct device *d,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw->muwticast_ctx.muwticast_quewiew);
}

static int set_muwticast_quewiew(stwuct net_bwidge *bw, unsigned wong vaw,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn bw_muwticast_set_quewiew(&bw->muwticast_ctx, vaw);
}

static ssize_t muwticast_quewiew_stowe(stwuct device *d,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_muwticast_quewiew);
}
static DEVICE_ATTW_WW(muwticast_quewiew);

static ssize_t hash_ewasticity_show(stwuct device *d,
				    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", WHT_EWASTICITY);
}

static int set_ewasticity(stwuct net_bwidge *bw, unsigned wong vaw,
			  stwuct netwink_ext_ack *extack)
{
	/* 16 is WHT_EWASTICITY */
	NW_SET_EWW_MSG_MOD(extack,
			   "the hash_ewasticity option has been depwecated and is awways 16");
	wetuwn 0;
}

static ssize_t hash_ewasticity_stowe(stwuct device *d,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_ewasticity);
}
static DEVICE_ATTW_WW(hash_ewasticity);

static ssize_t hash_max_show(stwuct device *d, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw->hash_max);
}

static int set_hash_max(stwuct net_bwidge *bw, unsigned wong vaw,
			stwuct netwink_ext_ack *extack)
{
	bw->hash_max = vaw;
	wetuwn 0;
}

static ssize_t hash_max_stowe(stwuct device *d, stwuct device_attwibute *attw,
			      const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_hash_max);
}
static DEVICE_ATTW_WW(hash_max);

static ssize_t muwticast_igmp_vewsion_show(stwuct device *d,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);

	wetuwn spwintf(buf, "%u\n", bw->muwticast_ctx.muwticast_igmp_vewsion);
}

static int set_muwticast_igmp_vewsion(stwuct net_bwidge *bw, unsigned wong vaw,
				      stwuct netwink_ext_ack *extack)
{
	wetuwn bw_muwticast_set_igmp_vewsion(&bw->muwticast_ctx, vaw);
}

static ssize_t muwticast_igmp_vewsion_stowe(stwuct device *d,
					    stwuct device_attwibute *attw,
					    const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_muwticast_igmp_vewsion);
}
static DEVICE_ATTW_WW(muwticast_igmp_vewsion);

static ssize_t muwticast_wast_membew_count_show(stwuct device *d,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw->muwticast_ctx.muwticast_wast_membew_count);
}

static int set_wast_membew_count(stwuct net_bwidge *bw, unsigned wong vaw,
				 stwuct netwink_ext_ack *extack)
{
	bw->muwticast_ctx.muwticast_wast_membew_count = vaw;
	wetuwn 0;
}

static ssize_t muwticast_wast_membew_count_stowe(stwuct device *d,
						 stwuct device_attwibute *attw,
						 const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_wast_membew_count);
}
static DEVICE_ATTW_WW(muwticast_wast_membew_count);

static ssize_t muwticast_stawtup_quewy_count_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw->muwticast_ctx.muwticast_stawtup_quewy_count);
}

static int set_stawtup_quewy_count(stwuct net_bwidge *bw, unsigned wong vaw,
				   stwuct netwink_ext_ack *extack)
{
	bw->muwticast_ctx.muwticast_stawtup_quewy_count = vaw;
	wetuwn 0;
}

static ssize_t muwticast_stawtup_quewy_count_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_stawtup_quewy_count);
}
static DEVICE_ATTW_WW(muwticast_stawtup_quewy_count);

static ssize_t muwticast_wast_membew_intewvaw_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wu\n",
		       jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_wast_membew_intewvaw));
}

static int set_wast_membew_intewvaw(stwuct net_bwidge *bw, unsigned wong vaw,
				    stwuct netwink_ext_ack *extack)
{
	bw->muwticast_ctx.muwticast_wast_membew_intewvaw = cwock_t_to_jiffies(vaw);
	wetuwn 0;
}

static ssize_t muwticast_wast_membew_intewvaw_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_wast_membew_intewvaw);
}
static DEVICE_ATTW_WW(muwticast_wast_membew_intewvaw);

static ssize_t muwticast_membewship_intewvaw_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wu\n",
		       jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_membewship_intewvaw));
}

static int set_membewship_intewvaw(stwuct net_bwidge *bw, unsigned wong vaw,
				   stwuct netwink_ext_ack *extack)
{
	bw->muwticast_ctx.muwticast_membewship_intewvaw = cwock_t_to_jiffies(vaw);
	wetuwn 0;
}

static ssize_t muwticast_membewship_intewvaw_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_membewship_intewvaw);
}
static DEVICE_ATTW_WW(muwticast_membewship_intewvaw);

static ssize_t muwticast_quewiew_intewvaw_show(stwuct device *d,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wu\n",
		       jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_quewiew_intewvaw));
}

static int set_quewiew_intewvaw(stwuct net_bwidge *bw, unsigned wong vaw,
				stwuct netwink_ext_ack *extack)
{
	bw->muwticast_ctx.muwticast_quewiew_intewvaw = cwock_t_to_jiffies(vaw);
	wetuwn 0;
}

static ssize_t muwticast_quewiew_intewvaw_stowe(stwuct device *d,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_quewiew_intewvaw);
}
static DEVICE_ATTW_WW(muwticast_quewiew_intewvaw);

static ssize_t muwticast_quewy_intewvaw_show(stwuct device *d,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%wu\n",
		       jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_quewy_intewvaw));
}

static int set_quewy_intewvaw(stwuct net_bwidge *bw, unsigned wong vaw,
			      stwuct netwink_ext_ack *extack)
{
	bw_muwticast_set_quewy_intvw(&bw->muwticast_ctx, vaw);
	wetuwn 0;
}

static ssize_t muwticast_quewy_intewvaw_stowe(stwuct device *d,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_quewy_intewvaw);
}
static DEVICE_ATTW_WW(muwticast_quewy_intewvaw);

static ssize_t muwticast_quewy_wesponse_intewvaw_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(
		buf, "%wu\n",
		jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_quewy_wesponse_intewvaw));
}

static int set_quewy_wesponse_intewvaw(stwuct net_bwidge *bw, unsigned wong vaw,
				       stwuct netwink_ext_ack *extack)
{
	bw->muwticast_ctx.muwticast_quewy_wesponse_intewvaw = cwock_t_to_jiffies(vaw);
	wetuwn 0;
}

static ssize_t muwticast_quewy_wesponse_intewvaw_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_quewy_wesponse_intewvaw);
}
static DEVICE_ATTW_WW(muwticast_quewy_wesponse_intewvaw);

static ssize_t muwticast_stawtup_quewy_intewvaw_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(
		buf, "%wu\n",
		jiffies_to_cwock_t(bw->muwticast_ctx.muwticast_stawtup_quewy_intewvaw));
}

static int set_stawtup_quewy_intewvaw(stwuct net_bwidge *bw, unsigned wong vaw,
				      stwuct netwink_ext_ack *extack)
{
	bw_muwticast_set_stawtup_quewy_intvw(&bw->muwticast_ctx, vaw);
	wetuwn 0;
}

static ssize_t muwticast_stawtup_quewy_intewvaw_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_stawtup_quewy_intewvaw);
}
static DEVICE_ATTW_WW(muwticast_stawtup_quewy_intewvaw);

static ssize_t muwticast_stats_enabwed_show(stwuct device *d,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);

	wetuwn spwintf(buf, "%d\n",
		       bw_opt_get(bw, BWOPT_MUWTICAST_STATS_ENABWED));
}

static int set_stats_enabwed(stwuct net_bwidge *bw, unsigned wong vaw,
			     stwuct netwink_ext_ack *extack)
{
	bw_opt_toggwe(bw, BWOPT_MUWTICAST_STATS_ENABWED, !!vaw);
	wetuwn 0;
}

static ssize_t muwticast_stats_enabwed_stowe(stwuct device *d,
					     stwuct device_attwibute *attw,
					     const chaw *buf,
					     size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_stats_enabwed);
}
static DEVICE_ATTW_WW(muwticast_stats_enabwed);

#if IS_ENABWED(CONFIG_IPV6)
static ssize_t muwticast_mwd_vewsion_show(stwuct device *d,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);

	wetuwn spwintf(buf, "%u\n", bw->muwticast_ctx.muwticast_mwd_vewsion);
}

static int set_muwticast_mwd_vewsion(stwuct net_bwidge *bw, unsigned wong vaw,
				     stwuct netwink_ext_ack *extack)
{
	wetuwn bw_muwticast_set_mwd_vewsion(&bw->muwticast_ctx, vaw);
}

static ssize_t muwticast_mwd_vewsion_stowe(stwuct device *d,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_muwticast_mwd_vewsion);
}
static DEVICE_ATTW_WW(muwticast_mwd_vewsion);
#endif
#endif
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
static ssize_t nf_caww_iptabwes_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw_opt_get(bw, BWOPT_NF_CAWW_IPTABWES));
}

static int set_nf_caww_iptabwes(stwuct net_bwidge *bw, unsigned wong vaw,
				stwuct netwink_ext_ack *extack)
{
	bw_opt_toggwe(bw, BWOPT_NF_CAWW_IPTABWES, !!vaw);
	wetuwn 0;
}

static ssize_t nf_caww_iptabwes_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_nf_caww_iptabwes);
}
static DEVICE_ATTW_WW(nf_caww_iptabwes);

static ssize_t nf_caww_ip6tabwes_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw_opt_get(bw, BWOPT_NF_CAWW_IP6TABWES));
}

static int set_nf_caww_ip6tabwes(stwuct net_bwidge *bw, unsigned wong vaw,
				 stwuct netwink_ext_ack *extack)
{
	bw_opt_toggwe(bw, BWOPT_NF_CAWW_IP6TABWES, !!vaw);
	wetuwn 0;
}

static ssize_t nf_caww_ip6tabwes_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_nf_caww_ip6tabwes);
}
static DEVICE_ATTW_WW(nf_caww_ip6tabwes);

static ssize_t nf_caww_awptabwes_show(
	stwuct device *d, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw_opt_get(bw, BWOPT_NF_CAWW_AWPTABWES));
}

static int set_nf_caww_awptabwes(stwuct net_bwidge *bw, unsigned wong vaw,
				 stwuct netwink_ext_ack *extack)
{
	bw_opt_toggwe(bw, BWOPT_NF_CAWW_AWPTABWES, !!vaw);
	wetuwn 0;
}

static ssize_t nf_caww_awptabwes_stowe(
	stwuct device *d, stwuct device_attwibute *attw, const chaw *buf,
	size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_nf_caww_awptabwes);
}
static DEVICE_ATTW_WW(nf_caww_awptabwes);
#endif
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
static ssize_t vwan_fiwtewing_show(stwuct device *d,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw_opt_get(bw, BWOPT_VWAN_ENABWED));
}

static ssize_t vwan_fiwtewing_stowe(stwuct device *d,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, bw_vwan_fiwtew_toggwe);
}
static DEVICE_ATTW_WW(vwan_fiwtewing);

static ssize_t vwan_pwotocow_show(stwuct device *d,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%#06x\n", ntohs(bw->vwan_pwoto));
}

static ssize_t vwan_pwotocow_stowe(stwuct device *d,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, bw_vwan_set_pwoto);
}
static DEVICE_ATTW_WW(vwan_pwotocow);

static ssize_t defauwt_pvid_show(stwuct device *d,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%d\n", bw->defauwt_pvid);
}

static ssize_t defauwt_pvid_stowe(stwuct device *d,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, bw_vwan_set_defauwt_pvid);
}
static DEVICE_ATTW_WW(defauwt_pvid);

static ssize_t vwan_stats_enabwed_show(stwuct device *d,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw_opt_get(bw, BWOPT_VWAN_STATS_ENABWED));
}

static int set_vwan_stats_enabwed(stwuct net_bwidge *bw, unsigned wong vaw,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn bw_vwan_set_stats(bw, vaw);
}

static ssize_t vwan_stats_enabwed_stowe(stwuct device *d,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_vwan_stats_enabwed);
}
static DEVICE_ATTW_WW(vwan_stats_enabwed);

static ssize_t vwan_stats_pew_powt_show(stwuct device *d,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct net_bwidge *bw = to_bwidge(d);
	wetuwn spwintf(buf, "%u\n", bw_opt_get(bw, BWOPT_VWAN_STATS_PEW_POWT));
}

static int set_vwan_stats_pew_powt(stwuct net_bwidge *bw, unsigned wong vaw,
				   stwuct netwink_ext_ack *extack)
{
	wetuwn bw_vwan_set_stats_pew_powt(bw, vaw);
}

static ssize_t vwan_stats_pew_powt_stowe(stwuct device *d,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t wen)
{
	wetuwn stowe_bwidge_pawm(d, buf, wen, set_vwan_stats_pew_powt);
}
static DEVICE_ATTW_WW(vwan_stats_pew_powt);
#endif

static stwuct attwibute *bwidge_attws[] = {
	&dev_attw_fowwawd_deway.attw,
	&dev_attw_hewwo_time.attw,
	&dev_attw_max_age.attw,
	&dev_attw_ageing_time.attw,
	&dev_attw_stp_state.attw,
	&dev_attw_gwoup_fwd_mask.attw,
	&dev_attw_pwiowity.attw,
	&dev_attw_bwidge_id.attw,
	&dev_attw_woot_id.attw,
	&dev_attw_woot_path_cost.attw,
	&dev_attw_woot_powt.attw,
	&dev_attw_topowogy_change.attw,
	&dev_attw_topowogy_change_detected.attw,
	&dev_attw_hewwo_timew.attw,
	&dev_attw_tcn_timew.attw,
	&dev_attw_topowogy_change_timew.attw,
	&dev_attw_gc_timew.attw,
	&dev_attw_gwoup_addw.attw,
	&dev_attw_fwush.attw,
	&dev_attw_no_winkwocaw_weawn.attw,
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	&dev_attw_muwticast_woutew.attw,
	&dev_attw_muwticast_snooping.attw,
	&dev_attw_muwticast_quewiew.attw,
	&dev_attw_muwticast_quewy_use_ifaddw.attw,
	&dev_attw_hash_ewasticity.attw,
	&dev_attw_hash_max.attw,
	&dev_attw_muwticast_wast_membew_count.attw,
	&dev_attw_muwticast_stawtup_quewy_count.attw,
	&dev_attw_muwticast_wast_membew_intewvaw.attw,
	&dev_attw_muwticast_membewship_intewvaw.attw,
	&dev_attw_muwticast_quewiew_intewvaw.attw,
	&dev_attw_muwticast_quewy_intewvaw.attw,
	&dev_attw_muwticast_quewy_wesponse_intewvaw.attw,
	&dev_attw_muwticast_stawtup_quewy_intewvaw.attw,
	&dev_attw_muwticast_stats_enabwed.attw,
	&dev_attw_muwticast_igmp_vewsion.attw,
#if IS_ENABWED(CONFIG_IPV6)
	&dev_attw_muwticast_mwd_vewsion.attw,
#endif
#endif
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	&dev_attw_nf_caww_iptabwes.attw,
	&dev_attw_nf_caww_ip6tabwes.attw,
	&dev_attw_nf_caww_awptabwes.attw,
#endif
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	&dev_attw_vwan_fiwtewing.attw,
	&dev_attw_vwan_pwotocow.attw,
	&dev_attw_defauwt_pvid.attw,
	&dev_attw_vwan_stats_enabwed.attw,
	&dev_attw_vwan_stats_pew_powt.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup bwidge_gwoup = {
	.name = SYSFS_BWIDGE_ATTW,
	.attws = bwidge_attws,
};

/*
 * Expowt the fowwawding infowmation tabwe as a binawy fiwe
 * The wecowds awe stwuct __fdb_entwy.
 *
 * Wetuwns the numbew of bytes wead.
 */
static ssize_t bwfowwawd_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw,
			      chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct net_bwidge *bw = to_bwidge(dev);
	int n;

	/* must wead whowe wecowds */
	if (off % sizeof(stwuct __fdb_entwy) != 0)
		wetuwn -EINVAW;

	n =  bw_fdb_fiwwbuf(bw, buf,
			    count / sizeof(stwuct __fdb_entwy),
			    off / sizeof(stwuct __fdb_entwy));

	if (n > 0)
		n *= sizeof(stwuct __fdb_entwy);

	wetuwn n;
}

static stwuct bin_attwibute bwidge_fowwawd = {
	.attw = { .name = SYSFS_BWIDGE_FDB,
		  .mode = 0444, },
	.wead = bwfowwawd_wead,
};

/*
 * Add entwies in sysfs onto the existing netwowk cwass device
 * fow the bwidge.
 *   Adds a attwibute gwoup "bwidge" containing tuning pawametews.
 *   Binawy attwibute containing the fowwawd tabwe
 *   Sub diwectowy to howd winks to intewfaces.
 *
 * Note: the ifobj exists onwy to be a subdiwectowy
 *   to howd winks.  The ifobj exists in same data stwuctuwe
 *   as it's pawent the bwidge so wefewence counting wowks.
 */
int bw_sysfs_addbw(stwuct net_device *dev)
{
	stwuct kobject *bwobj = &dev->dev.kobj;
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	int eww;

	eww = sysfs_cweate_gwoup(bwobj, &bwidge_gwoup);
	if (eww) {
		pw_info("%s: can't cweate gwoup %s/%s\n",
			__func__, dev->name, bwidge_gwoup.name);
		goto out1;
	}

	eww = sysfs_cweate_bin_fiwe(bwobj, &bwidge_fowwawd);
	if (eww) {
		pw_info("%s: can't cweate attwibute fiwe %s/%s\n",
			__func__, dev->name, bwidge_fowwawd.attw.name);
		goto out2;
	}

	bw->ifobj = kobject_cweate_and_add(SYSFS_BWIDGE_POWT_SUBDIW, bwobj);
	if (!bw->ifobj) {
		pw_info("%s: can't add kobject (diwectowy) %s/%s\n",
			__func__, dev->name, SYSFS_BWIDGE_POWT_SUBDIW);
		eww = -ENOMEM;
		goto out3;
	}
	wetuwn 0;
 out3:
	sysfs_wemove_bin_fiwe(&dev->dev.kobj, &bwidge_fowwawd);
 out2:
	sysfs_wemove_gwoup(&dev->dev.kobj, &bwidge_gwoup);
 out1:
	wetuwn eww;

}

void bw_sysfs_dewbw(stwuct net_device *dev)
{
	stwuct kobject *kobj = &dev->dev.kobj;
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	kobject_put(bw->ifobj);
	sysfs_wemove_bin_fiwe(kobj, &bwidge_fowwawd);
	sysfs_wemove_gwoup(kobj, &bwidge_gwoup);
}
