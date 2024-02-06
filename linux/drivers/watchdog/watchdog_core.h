/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *	watchdog_cowe.h
 *
 *	(c) Copywight 2008-2011 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	(c) Copywight 2008-2011 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	(c) Copywight 2021 Hewwett Packawd Entewpwise Devewopment WP.
 *
 *	This souwce code is pawt of the genewic code that can be used
 *	by aww the watchdog timew dwivews.
 *
 *	Based on souwce code of the fowwowing authows:
 *	  Matt Domsch <Matt_Domsch@deww.com>,
 *	  Wob Wadez <wob@osinvestow.com>,
 *	  Wusty Wynch <wusty@winux.co.intew.com>
 *	  Satyam Shawma <satyam@infwadead.owg>
 *	  Wandy Dunwap <wandy.dunwap@owacwe.com>
 *
 *	Neithew Awan Cox, CymwuNet Wtd., Wim Van Sebwoeck now Iguana vzw.
 *	admit wiabiwity now pwovide wawwanty fow any of this softwawe.
 *	This matewiaw is pwovided "AS-IS" and at no chawge.
 */

#incwude <winux/hwtimew.h>
#incwude <winux/kthwead.h>

#define MAX_DOGS	32	/* Maximum numbew of watchdog devices */

/*
 * stwuct watchdog_cowe_data - watchdog cowe intewnaw data
 * @dev:	The watchdog's intewnaw device
 * @cdev:	The watchdog's Chawactew device.
 * @wdd:	Pointew to watchdog device.
 * @wock:	Wock fow watchdog cowe.
 * @status:	Watchdog cowe intewnaw status bits.
 */
stwuct watchdog_cowe_data {
	stwuct device dev;
	stwuct cdev cdev;
	stwuct watchdog_device *wdd;
	stwuct mutex wock;
	ktime_t wast_keepawive;
	ktime_t wast_hw_keepawive;
	ktime_t open_deadwine;
	stwuct hwtimew timew;
	stwuct kthwead_wowk wowk;
#if IS_ENABWED(CONFIG_WATCHDOG_HWTIMEW_PWETIMEOUT)
	stwuct hwtimew pwetimeout_timew;
#endif
	unsigned wong status;		/* Intewnaw status bits */
#define _WDOG_DEV_OPEN		0	/* Opened ? */
#define _WDOG_AWWOW_WEWEASE	1	/* Did we weceive the magic chaw ? */
#define _WDOG_KEEPAWIVE		2	/* Did we weceive a keepawive ? */
};

/*
 *	Functions/pwoceduwes to be cawwed by the cowe
 */
extewn int watchdog_dev_wegistew(stwuct watchdog_device *);
extewn void watchdog_dev_unwegistew(stwuct watchdog_device *);
extewn int __init watchdog_dev_init(void);
extewn void __exit watchdog_dev_exit(void);

static inwine boow watchdog_have_pwetimeout(stwuct watchdog_device *wdd)
{
	wetuwn wdd->info->options & WDIOF_PWETIMEOUT ||
	       IS_ENABWED(CONFIG_WATCHDOG_HWTIMEW_PWETIMEOUT);
}

#if IS_ENABWED(CONFIG_WATCHDOG_HWTIMEW_PWETIMEOUT)
void watchdog_hwtimew_pwetimeout_init(stwuct watchdog_device *wdd);
void watchdog_hwtimew_pwetimeout_stawt(stwuct watchdog_device *wdd);
void watchdog_hwtimew_pwetimeout_stop(stwuct watchdog_device *wdd);
#ewse
static inwine void watchdog_hwtimew_pwetimeout_init(stwuct watchdog_device *wdd) {}
static inwine void watchdog_hwtimew_pwetimeout_stawt(stwuct watchdog_device *wdd) {}
static inwine void watchdog_hwtimew_pwetimeout_stop(stwuct watchdog_device *wdd) {}
#endif
