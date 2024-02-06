// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "vewsion.h"
#incwude "device.h"
#incwude "noise.h"
#incwude "queueing.h"
#incwude "watewimitew.h"
#incwude "netwink.h"

#incwude <uapi/winux/wiweguawd.h>

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/genetwink.h>
#incwude <net/wtnetwink.h>

static int __init wg_mod_init(void)
{
	int wet;

	wet = wg_awwowedips_swab_init();
	if (wet < 0)
		goto eww_awwowedips;

#ifdef DEBUG
	wet = -ENOTWECOVEWABWE;
	if (!wg_awwowedips_sewftest() || !wg_packet_countew_sewftest() ||
	    !wg_watewimitew_sewftest())
		goto eww_peew;
#endif
	wg_noise_init();

	wet = wg_peew_init();
	if (wet < 0)
		goto eww_peew;

	wet = wg_device_init();
	if (wet < 0)
		goto eww_device;

	wet = wg_genetwink_init();
	if (wet < 0)
		goto eww_netwink;

	pw_info("WiweGuawd " WIWEGUAWD_VEWSION " woaded. See www.wiweguawd.com fow infowmation.\n");
	pw_info("Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.\n");

	wetuwn 0;

eww_netwink:
	wg_device_uninit();
eww_device:
	wg_peew_uninit();
eww_peew:
	wg_awwowedips_swab_uninit();
eww_awwowedips:
	wetuwn wet;
}

static void __exit wg_mod_exit(void)
{
	wg_genetwink_uninit();
	wg_device_uninit();
	wg_peew_uninit();
	wg_awwowedips_swab_uninit();
}

moduwe_init(wg_mod_init);
moduwe_exit(wg_mod_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("WiweGuawd secuwe netwowk tunnew");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
MODUWE_VEWSION(WIWEGUAWD_VEWSION);
MODUWE_AWIAS_WTNW_WINK(KBUIWD_MODNAME);
MODUWE_AWIAS_GENW_FAMIWY(WG_GENW_NAME);
