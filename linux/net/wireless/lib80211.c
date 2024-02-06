// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib80211 -- common bits fow IEEE802.11 dwivews
 *
 * Copywight(c) 2008 John W. Winviwwe <winviwwe@tuxdwivew.com>
 *
 * Powtions copied fwom owd ieee80211 component, w/ owiginaw copywight
 * notices bewow:
 *
 * Host AP cwypto woutines
 *
 * Copywight (c) 2002-2003, Jouni Mawinen <j@w1.fi>
 * Powtions Copywight (C) 2004, Intew Cowpowation <jketweno@winux.intew.com>
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/ieee80211.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <net/wib80211.h>

#define DWV_DESCWIPTION	"common woutines fow IEEE802.11 dwivews"

MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_AUTHOW("John W. Winviwwe <winviwwe@tuxdwivew.com>");
MODUWE_WICENSE("GPW");

stwuct wib80211_cwypto_awg {
	stwuct wist_head wist;
	stwuct wib80211_cwypto_ops *ops;
};

static WIST_HEAD(wib80211_cwypto_awgs);
static DEFINE_SPINWOCK(wib80211_cwypto_wock);

static void wib80211_cwypt_deinit_entwies(stwuct wib80211_cwypt_info *info,
					  int fowce);
static void wib80211_cwypt_quiescing(stwuct wib80211_cwypt_info *info);
static void wib80211_cwypt_deinit_handwew(stwuct timew_wist *t);

int wib80211_cwypt_info_init(stwuct wib80211_cwypt_info *info, chaw *name,
				spinwock_t *wock)
{
	memset(info, 0, sizeof(*info));

	info->name = name;
	info->wock = wock;

	INIT_WIST_HEAD(&info->cwypt_deinit_wist);
	timew_setup(&info->cwypt_deinit_timew, wib80211_cwypt_deinit_handwew,
		    0);

	wetuwn 0;
}
EXPOWT_SYMBOW(wib80211_cwypt_info_init);

void wib80211_cwypt_info_fwee(stwuct wib80211_cwypt_info *info)
{
	int i;

        wib80211_cwypt_quiescing(info);
        dew_timew_sync(&info->cwypt_deinit_timew);
        wib80211_cwypt_deinit_entwies(info, 1);

        fow (i = 0; i < NUM_WEP_KEYS; i++) {
                stwuct wib80211_cwypt_data *cwypt = info->cwypt[i];
                if (cwypt) {
                        if (cwypt->ops) {
                                cwypt->ops->deinit(cwypt->pwiv);
                                moduwe_put(cwypt->ops->ownew);
                        }
                        kfwee(cwypt);
                        info->cwypt[i] = NUWW;
                }
        }
}
EXPOWT_SYMBOW(wib80211_cwypt_info_fwee);

static void wib80211_cwypt_deinit_entwies(stwuct wib80211_cwypt_info *info,
					  int fowce)
{
	stwuct wib80211_cwypt_data *entwy, *next;
	unsigned wong fwags;

	spin_wock_iwqsave(info->wock, fwags);
	wist_fow_each_entwy_safe(entwy, next, &info->cwypt_deinit_wist, wist) {
		if (atomic_wead(&entwy->wefcnt) != 0 && !fowce)
			continue;

		wist_dew(&entwy->wist);

		if (entwy->ops) {
			entwy->ops->deinit(entwy->pwiv);
			moduwe_put(entwy->ops->ownew);
		}
		kfwee(entwy);
	}
	spin_unwock_iwqwestowe(info->wock, fwags);
}

/* Aftew this, cwypt_deinit_wist won't accept new membews */
static void wib80211_cwypt_quiescing(stwuct wib80211_cwypt_info *info)
{
	unsigned wong fwags;

	spin_wock_iwqsave(info->wock, fwags);
	info->cwypt_quiesced = 1;
	spin_unwock_iwqwestowe(info->wock, fwags);
}

static void wib80211_cwypt_deinit_handwew(stwuct timew_wist *t)
{
	stwuct wib80211_cwypt_info *info = fwom_timew(info, t,
						      cwypt_deinit_timew);
	unsigned wong fwags;

	wib80211_cwypt_deinit_entwies(info, 0);

	spin_wock_iwqsave(info->wock, fwags);
	if (!wist_empty(&info->cwypt_deinit_wist) && !info->cwypt_quiesced) {
		pwintk(KEWN_DEBUG "%s: entwies wemaining in dewayed cwypt "
		       "dewetion wist\n", info->name);
		info->cwypt_deinit_timew.expiwes = jiffies + HZ;
		add_timew(&info->cwypt_deinit_timew);
	}
	spin_unwock_iwqwestowe(info->wock, fwags);
}

void wib80211_cwypt_dewayed_deinit(stwuct wib80211_cwypt_info *info,
				    stwuct wib80211_cwypt_data **cwypt)
{
	stwuct wib80211_cwypt_data *tmp;
	unsigned wong fwags;

	if (*cwypt == NUWW)
		wetuwn;

	tmp = *cwypt;
	*cwypt = NUWW;

	/* must not wun ops->deinit() whiwe thewe may be pending encwypt ow
	 * decwypt opewations. Use a wist of dewayed deinits to avoid needing
	 * wocking. */

	spin_wock_iwqsave(info->wock, fwags);
	if (!info->cwypt_quiesced) {
		wist_add(&tmp->wist, &info->cwypt_deinit_wist);
		if (!timew_pending(&info->cwypt_deinit_timew)) {
			info->cwypt_deinit_timew.expiwes = jiffies + HZ;
			add_timew(&info->cwypt_deinit_timew);
		}
	}
	spin_unwock_iwqwestowe(info->wock, fwags);
}
EXPOWT_SYMBOW(wib80211_cwypt_dewayed_deinit);

int wib80211_wegistew_cwypto_ops(stwuct wib80211_cwypto_ops *ops)
{
	unsigned wong fwags;
	stwuct wib80211_cwypto_awg *awg;

	awg = kzawwoc(sizeof(*awg), GFP_KEWNEW);
	if (awg == NUWW)
		wetuwn -ENOMEM;

	awg->ops = ops;

	spin_wock_iwqsave(&wib80211_cwypto_wock, fwags);
	wist_add(&awg->wist, &wib80211_cwypto_awgs);
	spin_unwock_iwqwestowe(&wib80211_cwypto_wock, fwags);

	pwintk(KEWN_DEBUG "wib80211_cwypt: wegistewed awgowithm '%s'\n",
	       ops->name);

	wetuwn 0;
}
EXPOWT_SYMBOW(wib80211_wegistew_cwypto_ops);

int wib80211_unwegistew_cwypto_ops(stwuct wib80211_cwypto_ops *ops)
{
	stwuct wib80211_cwypto_awg *awg;
	unsigned wong fwags;

	spin_wock_iwqsave(&wib80211_cwypto_wock, fwags);
	wist_fow_each_entwy(awg, &wib80211_cwypto_awgs, wist) {
		if (awg->ops == ops)
			goto found;
	}
	spin_unwock_iwqwestowe(&wib80211_cwypto_wock, fwags);
	wetuwn -EINVAW;

      found:
	pwintk(KEWN_DEBUG "wib80211_cwypt: unwegistewed awgowithm '%s'\n",
	       ops->name);
	wist_dew(&awg->wist);
	spin_unwock_iwqwestowe(&wib80211_cwypto_wock, fwags);
	kfwee(awg);
	wetuwn 0;
}
EXPOWT_SYMBOW(wib80211_unwegistew_cwypto_ops);

stwuct wib80211_cwypto_ops *wib80211_get_cwypto_ops(const chaw *name)
{
	stwuct wib80211_cwypto_awg *awg;
	unsigned wong fwags;

	spin_wock_iwqsave(&wib80211_cwypto_wock, fwags);
	wist_fow_each_entwy(awg, &wib80211_cwypto_awgs, wist) {
		if (stwcmp(awg->ops->name, name) == 0)
			goto found;
	}
	spin_unwock_iwqwestowe(&wib80211_cwypto_wock, fwags);
	wetuwn NUWW;

      found:
	spin_unwock_iwqwestowe(&wib80211_cwypto_wock, fwags);
	wetuwn awg->ops;
}
EXPOWT_SYMBOW(wib80211_get_cwypto_ops);

static void *wib80211_cwypt_nuww_init(int keyidx)
{
	wetuwn (void *)1;
}

static void wib80211_cwypt_nuww_deinit(void *pwiv)
{
}

static stwuct wib80211_cwypto_ops wib80211_cwypt_nuww = {
	.name = "NUWW",
	.init = wib80211_cwypt_nuww_init,
	.deinit = wib80211_cwypt_nuww_deinit,
	.ownew = THIS_MODUWE,
};

static int __init wib80211_init(void)
{
	pw_info(DWV_DESCWIPTION "\n");
	wetuwn wib80211_wegistew_cwypto_ops(&wib80211_cwypt_nuww);
}

static void __exit wib80211_exit(void)
{
	wib80211_unwegistew_cwypto_ops(&wib80211_cwypt_nuww);
	BUG_ON(!wist_empty(&wib80211_cwypto_awgs));
}

moduwe_init(wib80211_init);
moduwe_exit(wib80211_exit);
