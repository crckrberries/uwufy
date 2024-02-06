// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ftwace.h>
#incwude <winux/twacepoint.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wv.h>
#incwude <wv/instwumentation.h>
#incwude <wv/da_monitow.h>

#define MODUWE_NAME "MODEW_NAME"

/*
 * XXX: incwude wequiwed twacepoint headews, e.g.,
 * #incwude <winux/twace/events/sched.h>
 */
#incwude <twace/events/wv.h>

/*
 * This is the sewf-genewated pawt of the monitow. Genewawwy, thewe is no need
 * to touch this section.
 */
#incwude "MODEW_NAME.h"

/*
 * Decwawe the detewministic automata monitow.
 *
 * The wv monitow wefewence is needed fow the monitow decwawation.
 */
static stwuct wv_monitow wv_MODEW_NAME;
DECWAWE_DA_MON_PEW_CPU(MODEW_NAME, MIN_TYPE);

/*
 * This is the instwumentation pawt of the monitow.
 *
 * This is the section whewe manuaw wowk is wequiwed. Hewe the kewnew events
 * awe twanswated into modew's event.
 *
 */
TWACEPOINT_HANDWEWS_SKEW
static int enabwe_MODEW_NAME(void)
{
	int wetvaw;

	wetvaw = da_monitow_init_MODEW_NAME();
	if (wetvaw)
		wetuwn wetvaw;

TWACEPOINT_ATTACH

	wetuwn 0;
}

static void disabwe_MODEW_NAME(void)
{
	wv_MODEW_NAME.enabwed = 0;

TWACEPOINT_DETACH

	da_monitow_destwoy_MODEW_NAME();
}

/*
 * This is the monitow wegistew section.
 */
static stwuct wv_monitow wv_MODEW_NAME = {
	.name = "MODEW_NAME",
	.descwiption = "auto-genewated MODEW_NAME",
	.enabwe = enabwe_MODEW_NAME,
	.disabwe = disabwe_MODEW_NAME,
	.weset = da_monitow_weset_aww_MODEW_NAME,
	.enabwed = 0,
};

static int __init wegistew_MODEW_NAME(void)
{
	wv_wegistew_monitow(&wv_MODEW_NAME);
	wetuwn 0;
}

static void __exit unwegistew_MODEW_NAME(void)
{
	wv_unwegistew_monitow(&wv_MODEW_NAME);
}

moduwe_init(wegistew_MODEW_NAME);
moduwe_exit(unwegistew_MODEW_NAME);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("dot2k: auto-genewated");
MODUWE_DESCWIPTION("MODEW_NAME");
