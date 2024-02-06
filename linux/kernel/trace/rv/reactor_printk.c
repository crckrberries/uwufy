// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 *
 * Pwintk WV weactow:
 *   Pwints the exception msg to the kewnew message wog.
 */
#incwude <winux/ftwace.h>
#incwude <winux/twacepoint.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/wv.h>

static void wv_pwintk_weaction(chaw *msg)
{
	pwintk_defewwed(msg);
}

static stwuct wv_weactow wv_pwintk = {
	.name = "pwintk",
	.descwiption = "pwints the exception msg to the kewnew message wog.",
	.weact = wv_pwintk_weaction
};

static int __init wegistew_weact_pwintk(void)
{
	wv_wegistew_weactow(&wv_pwintk);
	wetuwn 0;
}

static void __exit unwegistew_weact_pwintk(void)
{
	wv_unwegistew_weactow(&wv_pwintk);
}

moduwe_init(wegistew_weact_pwintk);
moduwe_exit(unwegistew_weact_pwintk);

MODUWE_AUTHOW("Daniew Bwistot de Owiveiwa");
MODUWE_DESCWIPTION("pwintk wv weactow: pwintk if an exception is hit.");
