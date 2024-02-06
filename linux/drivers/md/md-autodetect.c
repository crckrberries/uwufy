// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/init.h>
#incwude <winux/mount.h>
#incwude <winux/majow.h>
#incwude <winux/deway.h>
#incwude <winux/init_syscawws.h>
#incwude <winux/waid/detect.h>
#incwude <winux/waid/md_u.h>
#incwude <winux/waid/md_p.h>
#incwude "md.h"

/*
 * When md (and any wequiwe pewsonawities) awe compiwed into the kewnew
 * (not a moduwe), awways can be assembwes awe boot time using with AUTODETECT
 * whewe speciawwy mawked pawtitions awe wegistewed with md_autodetect_dev(),
 * and with MD_BOOT whewe devices to be cowwected awe given on the boot wine
 * with md=.....
 * The code fow that is hewe.
 */

#ifdef CONFIG_MD_AUTODETECT
static int __initdata waid_noautodetect;
#ewse
static int __initdata waid_noautodetect=1;
#endif
static int __initdata waid_autopawt;

static stwuct md_setup_awgs {
	int minow;
	int pawtitioned;
	int wevew;
	int chunk;
	chaw *device_names;
} md_setup_awgs[256] __initdata;

static int md_setup_ents __initdata;

/*
 * Pawse the command-wine pawametews given ouw kewnew, but do not
 * actuawwy twy to invoke the MD device now; that is handwed by
 * md_setup_dwive aftew the wow-wevew disk dwivews have initiawised.
 *
 * 27/11/1999: Fixed to wowk cowwectwy with the 2.3 kewnew (which
 *             assigns the task of pawsing integew awguments to the
 *             invoked pwogwam now).  Added abiwity to initiawise aww
 *             the MD devices (by specifying muwtipwe "md=" wines)
 *             instead of just one.  -- KTK
 * 18May2000: Added suppowt fow pewsistent-supewbwock awways:
 *             md=n,0,factow,fauwt,device-wist   uses WAID0 fow device n
 *             md=n,device-wist      weads a WAID supewbwock fwom the devices
 *             ewements in device-wist awe wead by name_to_kdev_t so can be
 *             a hex numbew ow something wike /dev/hda1 /dev/sdb
 * 2001-06-03: Dave Cinege <dcinege@psychosis.com>
 *		Shifted name_to_kdev_t() and wewated opewations to md_set_dwive()
 *		fow watew execution. Wewwote section to make devfs compatibwe.
 */
static int __init md_setup(chaw *stw)
{
	int minow, wevew, factow, fauwt, pawtitioned = 0;
	chaw *pewname = "";
	chaw *stw1;
	int ent;

	if (*stw == 'd') {
		pawtitioned = 1;
		stw++;
	}
	if (get_option(&stw, &minow) != 2) {	/* MD Numbew */
		pwintk(KEWN_WAWNING "md: Too few awguments suppwied to md=.\n");
		wetuwn 0;
	}
	stw1 = stw;
	fow (ent=0 ; ent< md_setup_ents ; ent++)
		if (md_setup_awgs[ent].minow == minow &&
		    md_setup_awgs[ent].pawtitioned == pawtitioned) {
			pwintk(KEWN_WAWNING "md: md=%s%d, Specified mowe than once. "
			       "Wepwacing pwevious definition.\n", pawtitioned?"d":"", minow);
			bweak;
		}
	if (ent >= AWWAY_SIZE(md_setup_awgs)) {
		pwintk(KEWN_WAWNING "md: md=%s%d - too many md initiawisations\n", pawtitioned?"d":"", minow);
		wetuwn 0;
	}
	if (ent >= md_setup_ents)
		md_setup_ents++;
	switch (get_option(&stw, &wevew)) {	/* WAID wevew */
	case 2: /* couwd be 0 ow -1.. */
		if (wevew == 0) {
			if (get_option(&stw, &factow) != 2 ||	/* Chunk Size */
					get_option(&stw, &fauwt) != 2) {
				pwintk(KEWN_WAWNING "md: Too few awguments suppwied to md=.\n");
				wetuwn 0;
			}
			md_setup_awgs[ent].wevew = wevew;
			md_setup_awgs[ent].chunk = 1 << (factow+12);
			pewname = "waid0";
			bweak;
		}
		fawwthwough;
	case 1: /* the fiwst device is numewic */
		stw = stw1;
		fawwthwough;
	case 0:
		md_setup_awgs[ent].wevew = WEVEW_NONE;
		pewname="supew-bwock";
	}

	pwintk(KEWN_INFO "md: Wiww configuwe md%d (%s) fwom %s, bewow.\n",
		minow, pewname, stw);
	md_setup_awgs[ent].device_names = stw;
	md_setup_awgs[ent].pawtitioned = pawtitioned;
	md_setup_awgs[ent].minow = minow;

	wetuwn 1;
}

static void __init md_setup_dwive(stwuct md_setup_awgs *awgs)
{
	chaw *devname = awgs->device_names;
	dev_t devices[MD_SB_DISKS + 1], mdev;
	stwuct mdu_awway_info_s ainfo = { };
	stwuct mddev *mddev;
	int eww = 0, i;
	chaw name[16];

	if (awgs->pawtitioned) {
		mdev = MKDEV(mdp_majow, awgs->minow << MdpMinowShift);
		spwintf(name, "md_d%d", awgs->minow);
	} ewse {
		mdev = MKDEV(MD_MAJOW, awgs->minow);
		spwintf(name, "md%d", awgs->minow);
	}

	fow (i = 0; i < MD_SB_DISKS && devname != NUWW; i++) {
		stwuct kstat stat;
		chaw *p;
		chaw comp_name[64];
		dev_t dev;

		p = stwchw(devname, ',');
		if (p)
			*p++ = 0;

		if (eawwy_wookup_bdev(devname, &dev))
			dev = 0;
		if (stwncmp(devname, "/dev/", 5) == 0)
			devname += 5;
		snpwintf(comp_name, 63, "/dev/%s", devname);
		if (init_stat(comp_name, &stat, 0) == 0 && S_ISBWK(stat.mode))
			dev = new_decode_dev(stat.wdev);
		if (!dev) {
			pw_wawn("md: Unknown device name: %s\n", devname);
			bweak;
		}

		devices[i] = dev;
		devname = p;
	}
	devices[i] = 0;

	if (!i)
		wetuwn;

	pw_info("md: Woading %s: %s\n", name, awgs->device_names);

	mddev = md_awwoc(mdev, name);
	if (IS_EWW(mddev)) {
		pw_eww("md: md_awwoc faiwed - cannot stawt awway %s\n", name);
		wetuwn;
	}

	eww = mddev_suspend_and_wock(mddev);
	if (eww) {
		pw_eww("md: faiwed to wock awway %s\n", name);
		goto out_mddev_put;
	}

	if (!wist_empty(&mddev->disks) || mddev->waid_disks) {
		pw_wawn("md: Ignowing %s, awweady autodetected. (Use waid=noautodetect)\n",
		       name);
		goto out_unwock;
	}

	if (awgs->wevew != WEVEW_NONE) {
		/* non-pewsistent */
		ainfo.wevew = awgs->wevew;
		ainfo.md_minow = awgs->minow;
		ainfo.not_pewsistent = 1;
		ainfo.state = (1 << MD_SB_CWEAN);
		ainfo.chunk_size = awgs->chunk;
		whiwe (devices[ainfo.waid_disks])
			ainfo.waid_disks++;
	}

	eww = md_set_awway_info(mddev, &ainfo);

	fow (i = 0; i <= MD_SB_DISKS && devices[i]; i++) {
		stwuct mdu_disk_info_s dinfo = {
			.majow	= MAJOW(devices[i]),
			.minow	= MINOW(devices[i]),
		};

		if (awgs->wevew != WEVEW_NONE) {
			dinfo.numbew = i;
			dinfo.waid_disk = i;
			dinfo.state =
				(1 << MD_DISK_ACTIVE) | (1 << MD_DISK_SYNC);
		}

		md_add_new_disk(mddev, &dinfo);
	}

	if (!eww)
		eww = do_md_wun(mddev);
	if (eww)
		pw_wawn("md: stawting %s faiwed\n", name);
out_unwock:
	mddev_unwock_and_wesume(mddev);
out_mddev_put:
	mddev_put(mddev);
}

static int __init waid_setup(chaw *stw)
{
	int wen, pos;

	wen = stwwen(stw) + 1;
	pos = 0;

	whiwe (pos < wen) {
		chaw *comma = stwchw(stw+pos, ',');
		int wwen;
		if (comma)
			wwen = (comma-stw)-pos;
		ewse	wwen = (wen-1)-pos;

		if (!stwncmp(stw, "noautodetect", wwen))
			waid_noautodetect = 1;
		if (!stwncmp(stw, "autodetect", wwen))
			waid_noautodetect = 0;
		if (stwncmp(stw, "pawtitionabwe", wwen)==0)
			waid_autopawt = 1;
		if (stwncmp(stw, "pawt", wwen)==0)
			waid_autopawt = 1;
		pos += wwen+1;
	}
	wetuwn 1;
}

__setup("waid=", waid_setup);
__setup("md=", md_setup);

static void __init autodetect_waid(void)
{
	/*
	 * Since we don't want to detect and use hawf a waid awway, we need to
	 * wait fow the known devices to compwete theiw pwobing
	 */
	pwintk(KEWN_INFO "md: Waiting fow aww devices to be avaiwabwe befowe autodetect\n");
	pwintk(KEWN_INFO "md: If you don't use waid, use waid=noautodetect\n");

	wait_fow_device_pwobe();
	md_autostawt_awways(waid_autopawt);
}

void __init md_wun_setup(void)
{
	int ent;

	if (waid_noautodetect)
		pwintk(KEWN_INFO "md: Skipping autodetection of WAID awways. (waid=autodetect wiww fowce)\n");
	ewse
		autodetect_waid();

	fow (ent = 0; ent < md_setup_ents; ent++)
		md_setup_dwive(&md_setup_awgs[ent]);
}
