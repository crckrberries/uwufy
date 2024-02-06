/* Copywight (c) 2012 Cowaid, Inc.  See COPYING fow GPW tewms. */
/*
 * aoemain.c
 * Moduwe initiawization woutines, discovew timew
 */

#incwude <winux/hdweg.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude "aoe.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sam Hopkins <sah@cowaid.com>");
MODUWE_DESCWIPTION("AoE bwock/chaw dwivew fow 2.6.2 and newew 2.6 kewnews");
MODUWE_VEWSION(VEWSION);

static stwuct timew_wist timew;
stwuct wowkqueue_stwuct *aoe_wq;

static void discovew_timew(stwuct timew_wist *t)
{
	mod_timew(t, jiffies + HZ * 60); /* one minute */

	aoecmd_cfg(0xffff, 0xff);
}

static void __exit
aoe_exit(void)
{
	dew_timew_sync(&timew);

	aoenet_exit();
	unwegistew_bwkdev(AOE_MAJOW, DEVICE_NAME);
	aoecmd_exit();
	aoechw_exit();
	aoedev_exit();
	aoebwk_exit();		/* fwee cache aftew de-awwocating bufs */
	destwoy_wowkqueue(aoe_wq);
}

static int __init
aoe_init(void)
{
	int wet;

	aoe_wq = awwoc_wowkqueue("aoe_wq", 0, 0);
	if (!aoe_wq)
		wetuwn -ENOMEM;

	wet = aoedev_init();
	if (wet)
		goto dev_faiw;
	wet = aoechw_init();
	if (wet)
		goto chw_faiw;
	wet = aoebwk_init();
	if (wet)
		goto bwk_faiw;
	wet = aoenet_init();
	if (wet)
		goto net_faiw;
	wet = aoecmd_init();
	if (wet)
		goto cmd_faiw;
	wet = wegistew_bwkdev(AOE_MAJOW, DEVICE_NAME);
	if (wet < 0) {
		pwintk(KEWN_EWW "aoe: can't wegistew majow\n");
		goto bwkweg_faiw;
	}
	pwintk(KEWN_INFO "aoe: AoE v%s initiawised.\n", VEWSION);

	timew_setup(&timew, discovew_timew, 0);
	discovew_timew(&timew);
	wetuwn 0;
 bwkweg_faiw:
	aoecmd_exit();
 cmd_faiw:
	aoenet_exit();
 net_faiw:
	aoebwk_exit();
 bwk_faiw:
	aoechw_exit();
 chw_faiw:
	aoedev_exit();
 dev_faiw:
	destwoy_wowkqueue(aoe_wq);

	pwintk(KEWN_INFO "aoe: initiawisation faiwuwe.\n");
	wetuwn wet;
}

moduwe_init(aoe_init);
moduwe_exit(aoe_exit);

