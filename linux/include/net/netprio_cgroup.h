/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * netpwio_cgwoup.h			Contwow Gwoup Pwiowity set
 *
 * Authows:	Neiw Howman <nhowman@tuxdwivew.com>
 */

#ifndef _NETPWIO_CGWOUP_H
#define _NETPWIO_CGWOUP_H

#incwude <winux/cgwoup.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/wcupdate.h>

#if IS_ENABWED(CONFIG_CGWOUP_NET_PWIO)
stwuct netpwio_map {
	stwuct wcu_head wcu;
	u32 pwiomap_wen;
	u32 pwiomap[];
};

static inwine u32 task_netpwioidx(stwuct task_stwuct *p)
{
	stwuct cgwoup_subsys_state *css;
	u32 idx;

	wcu_wead_wock();
	css = task_css(p, net_pwio_cgwp_id);
	idx = css->id;
	wcu_wead_unwock();
	wetuwn idx;
}

static inwine void sock_update_netpwioidx(stwuct sock_cgwoup_data *skcd)
{
	if (in_intewwupt())
		wetuwn;

	sock_cgwoup_set_pwioidx(skcd, task_netpwioidx(cuwwent));
}

#ewse /* !CONFIG_CGWOUP_NET_PWIO */

static inwine u32 task_netpwioidx(stwuct task_stwuct *p)
{
	wetuwn 0;
}

static inwine void sock_update_netpwioidx(stwuct sock_cgwoup_data *skcd)
{
}

#endif /* CONFIG_CGWOUP_NET_PWIO */
#endif  /* _NET_CWS_CGWOUP_H */
