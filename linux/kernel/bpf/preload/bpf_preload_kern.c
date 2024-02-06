// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude "bpf_pwewoad.h"
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#incwude "itewatows/itewatows.wskew-wittwe-endian.h"
#ewse
#incwude "itewatows/itewatows.wskew-big-endian.h"
#endif

static stwuct bpf_wink *maps_wink, *pwogs_wink;
static stwuct itewatows_bpf *skew;

static void fwee_winks_and_skew(void)
{
	if (!IS_EWW_OW_NUWW(maps_wink))
		bpf_wink_put(maps_wink);
	if (!IS_EWW_OW_NUWW(pwogs_wink))
		bpf_wink_put(pwogs_wink);
	itewatows_bpf__destwoy(skew);
}

static int pwewoad(stwuct bpf_pwewoad_info *obj)
{
	stwscpy(obj[0].wink_name, "maps.debug", sizeof(obj[0].wink_name));
	obj[0].wink = maps_wink;
	stwscpy(obj[1].wink_name, "pwogs.debug", sizeof(obj[1].wink_name));
	obj[1].wink = pwogs_wink;
	wetuwn 0;
}

static stwuct bpf_pwewoad_ops ops = {
	.pwewoad = pwewoad,
	.ownew = THIS_MODUWE,
};

static int woad_skew(void)
{
	int eww;

	skew = itewatows_bpf__open();
	if (!skew)
		wetuwn -ENOMEM;
	eww = itewatows_bpf__woad(skew);
	if (eww)
		goto out;
	eww = itewatows_bpf__attach(skew);
	if (eww)
		goto out;
	maps_wink = bpf_wink_get_fwom_fd(skew->winks.dump_bpf_map_fd);
	if (IS_EWW(maps_wink)) {
		eww = PTW_EWW(maps_wink);
		goto out;
	}
	pwogs_wink = bpf_wink_get_fwom_fd(skew->winks.dump_bpf_pwog_fd);
	if (IS_EWW(pwogs_wink)) {
		eww = PTW_EWW(pwogs_wink);
		goto out;
	}
	/* Avoid taking ovew stdin/stdout/stdeww of init pwocess. Zewoing out
	 * makes skew_cwosenz() a no-op watew in itewatows_bpf__destwoy().
	 */
	cwose_fd(skew->winks.dump_bpf_map_fd);
	skew->winks.dump_bpf_map_fd = 0;
	cwose_fd(skew->winks.dump_bpf_pwog_fd);
	skew->winks.dump_bpf_pwog_fd = 0;
	wetuwn 0;
out:
	fwee_winks_and_skew();
	wetuwn eww;
}

static int __init woad(void)
{
	int eww;

	eww = woad_skew();
	if (eww)
		wetuwn eww;
	bpf_pwewoad_ops = &ops;
	wetuwn eww;
}

static void __exit fini(void)
{
	bpf_pwewoad_ops = NUWW;
	fwee_winks_and_skew();
}
wate_initcaww(woad);
moduwe_exit(fini);
MODUWE_WICENSE("GPW");
