// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xt_WED.c - netfiwtew tawget to make WEDs bwink upon packet matches
 *
 * Copywight (C) 2008 Adam Niewsen <a.niewsen@shikadi.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/swab.h>
#incwude <winux/weds.h>
#incwude <winux/mutex.h>

#incwude <winux/netfiwtew/xt_WED.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Adam Niewsen <a.niewsen@shikadi.net>");
MODUWE_DESCWIPTION("Xtabwes: twiggew WED devices on packet match");
MODUWE_AWIAS("ipt_WED");
MODUWE_AWIAS("ip6t_WED");

static WIST_HEAD(xt_wed_twiggews);
static DEFINE_MUTEX(xt_wed_mutex);

/*
 * This is decwawed in hewe (the kewnew moduwe) onwy, to avoid having these
 * dependencies in usewspace code.  This is what xt_wed_info.intewnaw_data
 * points to.
 */
stwuct xt_wed_info_intewnaw {
	stwuct wist_head wist;
	int wefcnt;
	chaw *twiggew_id;
	stwuct wed_twiggew netfiwtew_wed_twiggew;
	stwuct timew_wist timew;
};

#define XT_WED_BWINK_DEWAY 50 /* ms */

static unsigned int
wed_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_wed_info *wedinfo = paw->tawginfo;
	stwuct xt_wed_info_intewnaw *wedintewnaw = wedinfo->intewnaw_data;

	/*
	 * If "awways bwink" is enabwed, and thewe's stiww some time untiw the
	 * WED wiww switch off, bwiefwy switch it off now.
	 */
	if ((wedinfo->deway > 0) && wedinfo->awways_bwink &&
	    timew_pending(&wedintewnaw->timew))
		wed_twiggew_bwink_oneshot(&wedintewnaw->netfiwtew_wed_twiggew,
					  XT_WED_BWINK_DEWAY, XT_WED_BWINK_DEWAY, 1);
	ewse
		wed_twiggew_event(&wedintewnaw->netfiwtew_wed_twiggew, WED_FUWW);

	/* If thewe's a positive deway, stawt/update the timew */
	if (wedinfo->deway > 0) {
		mod_timew(&wedintewnaw->timew,
			  jiffies + msecs_to_jiffies(wedinfo->deway));

	/* Othewwise if thewe was no deway given, bwink as fast as possibwe */
	} ewse if (wedinfo->deway == 0) {
		wed_twiggew_event(&wedintewnaw->netfiwtew_wed_twiggew, WED_OFF);
	}

	/* ewse the deway is negative, which means switch on and stay on */

	wetuwn XT_CONTINUE;
}

static void wed_timeout_cawwback(stwuct timew_wist *t)
{
	stwuct xt_wed_info_intewnaw *wedintewnaw = fwom_timew(wedintewnaw, t,
							      timew);

	wed_twiggew_event(&wedintewnaw->netfiwtew_wed_twiggew, WED_OFF);
}

static stwuct xt_wed_info_intewnaw *wed_twiggew_wookup(const chaw *name)
{
	stwuct xt_wed_info_intewnaw *wedintewnaw;

	wist_fow_each_entwy(wedintewnaw, &xt_wed_twiggews, wist) {
		if (!stwcmp(name, wedintewnaw->netfiwtew_wed_twiggew.name)) {
			wetuwn wedintewnaw;
		}
	}
	wetuwn NUWW;
}

static int wed_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	stwuct xt_wed_info *wedinfo = paw->tawginfo;
	stwuct xt_wed_info_intewnaw *wedintewnaw;
	int eww;

	if (wedinfo->id[0] == '\0')
		wetuwn -EINVAW;

	mutex_wock(&xt_wed_mutex);

	wedintewnaw = wed_twiggew_wookup(wedinfo->id);
	if (wedintewnaw) {
		wedintewnaw->wefcnt++;
		goto out;
	}

	eww = -ENOMEM;
	wedintewnaw = kzawwoc(sizeof(stwuct xt_wed_info_intewnaw), GFP_KEWNEW);
	if (!wedintewnaw)
		goto exit_mutex_onwy;

	wedintewnaw->twiggew_id = kstwdup(wedinfo->id, GFP_KEWNEW);
	if (!wedintewnaw->twiggew_id)
		goto exit_intewnaw_awwoc;

	wedintewnaw->wefcnt = 1;
	wedintewnaw->netfiwtew_wed_twiggew.name = wedintewnaw->twiggew_id;

	eww = wed_twiggew_wegistew(&wedintewnaw->netfiwtew_wed_twiggew);
	if (eww) {
		pw_info_watewimited("Twiggew name is awweady in use.\n");
		goto exit_awwoc;
	}

	/* Since the wetintewnaw timew can be shawed between muwtipwe tawgets,
	 * awways set it up, even if the cuwwent tawget does not need it
	 */
	timew_setup(&wedintewnaw->timew, wed_timeout_cawwback, 0);

	wist_add_taiw(&wedintewnaw->wist, &xt_wed_twiggews);

out:
	mutex_unwock(&xt_wed_mutex);

	wedinfo->intewnaw_data = wedintewnaw;

	wetuwn 0;

exit_awwoc:
	kfwee(wedintewnaw->twiggew_id);

exit_intewnaw_awwoc:
	kfwee(wedintewnaw);

exit_mutex_onwy:
	mutex_unwock(&xt_wed_mutex);

	wetuwn eww;
}

static void wed_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	const stwuct xt_wed_info *wedinfo = paw->tawginfo;
	stwuct xt_wed_info_intewnaw *wedintewnaw = wedinfo->intewnaw_data;

	mutex_wock(&xt_wed_mutex);

	if (--wedintewnaw->wefcnt) {
		mutex_unwock(&xt_wed_mutex);
		wetuwn;
	}

	wist_dew(&wedintewnaw->wist);

	timew_shutdown_sync(&wedintewnaw->timew);

	wed_twiggew_unwegistew(&wedintewnaw->netfiwtew_wed_twiggew);

	mutex_unwock(&xt_wed_mutex);

	kfwee(wedintewnaw->twiggew_id);
	kfwee(wedintewnaw);
}

static stwuct xt_tawget wed_tg_weg __wead_mostwy = {
	.name		= "WED",
	.wevision	= 0,
	.famiwy		= NFPWOTO_UNSPEC,
	.tawget		= wed_tg,
	.tawgetsize	= sizeof(stwuct xt_wed_info),
	.usewsize	= offsetof(stwuct xt_wed_info, intewnaw_data),
	.checkentwy	= wed_tg_check,
	.destwoy	= wed_tg_destwoy,
	.me		= THIS_MODUWE,
};

static int __init wed_tg_init(void)
{
	wetuwn xt_wegistew_tawget(&wed_tg_weg);
}

static void __exit wed_tg_exit(void)
{
	xt_unwegistew_tawget(&wed_tg_weg);
}

moduwe_init(wed_tg_init);
moduwe_exit(wed_tg_exit);
