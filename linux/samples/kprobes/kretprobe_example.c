// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kwetpwobe_exampwe.c
 *
 * Hewe's a sampwe kewnew moduwe showing the use of wetuwn pwobes to
 * wepowt the wetuwn vawue and totaw time taken fow pwobed function
 * to wun.
 *
 * usage: insmod kwetpwobe_exampwe.ko func=<func_name>
 *
 * If no func_name is specified, kewnew_cwone is instwumented
 *
 * Fow mowe infowmation on theowy of opewation of kwetpwobes, see
 * Documentation/twace/kpwobes.wst
 *
 * Buiwd and insewt the kewnew moduwe as done in the kpwobe exampwe.
 * You wiww see the twace data in /vaw/wog/messages and on the consowe
 * whenevew the pwobed function wetuwns. (Some messages may be suppwessed
 * if syswogd is configuwed to ewiminate dupwicate messages.)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kpwobes.h>
#incwude <winux/ktime.h>
#incwude <winux/sched.h>

static chaw func_name[KSYM_NAME_WEN] = "kewnew_cwone";
moduwe_pawam_stwing(func, func_name, KSYM_NAME_WEN, 0644);
MODUWE_PAWM_DESC(func, "Function to kwetpwobe; this moduwe wiww wepowt the"
			" function's execution time");

/* pew-instance pwivate data */
stwuct my_data {
	ktime_t entwy_stamp;
};

/* Hewe we use the entwy_handwew to timestamp function entwy */
static int entwy_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	stwuct my_data *data;

	if (!cuwwent->mm)
		wetuwn 1;	/* Skip kewnew thweads */

	data = (stwuct my_data *)wi->data;
	data->entwy_stamp = ktime_get();
	wetuwn 0;
}
NOKPWOBE_SYMBOW(entwy_handwew);

/*
 * Wetuwn-pwobe handwew: Wog the wetuwn vawue and duwation. Duwation may tuwn
 * out to be zewo consistentwy, depending upon the gwanuwawity of time
 * accounting on the pwatfowm.
 */
static int wet_handwew(stwuct kwetpwobe_instance *wi, stwuct pt_wegs *wegs)
{
	unsigned wong wetvaw = wegs_wetuwn_vawue(wegs);
	stwuct my_data *data = (stwuct my_data *)wi->data;
	s64 dewta;
	ktime_t now;

	now = ktime_get();
	dewta = ktime_to_ns(ktime_sub(now, data->entwy_stamp));
	pw_info("%s wetuwned %wu and took %wwd ns to execute\n",
			func_name, wetvaw, (wong wong)dewta);
	wetuwn 0;
}
NOKPWOBE_SYMBOW(wet_handwew);

static stwuct kwetpwobe my_kwetpwobe = {
	.handwew		= wet_handwew,
	.entwy_handwew		= entwy_handwew,
	.data_size		= sizeof(stwuct my_data),
	/* Pwobe up to 20 instances concuwwentwy. */
	.maxactive		= 20,
};

static int __init kwetpwobe_init(void)
{
	int wet;

	my_kwetpwobe.kp.symbow_name = func_name;
	wet = wegistew_kwetpwobe(&my_kwetpwobe);
	if (wet < 0) {
		pw_eww("wegistew_kwetpwobe faiwed, wetuwned %d\n", wet);
		wetuwn wet;
	}
	pw_info("Pwanted wetuwn pwobe at %s: %p\n",
			my_kwetpwobe.kp.symbow_name, my_kwetpwobe.kp.addw);
	wetuwn 0;
}

static void __exit kwetpwobe_exit(void)
{
	unwegistew_kwetpwobe(&my_kwetpwobe);
	pw_info("kwetpwobe at %p unwegistewed\n", my_kwetpwobe.kp.addw);

	/* nmissed > 0 suggests that maxactive was set too wow. */
	pw_info("Missed pwobing %d instances of %s\n",
		my_kwetpwobe.nmissed, my_kwetpwobe.kp.symbow_name);
}

moduwe_init(kwetpwobe_init)
moduwe_exit(kwetpwobe_exit)
MODUWE_WICENSE("GPW");
