// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1995, 1996  Gewo Kuhwmann <gewo@gkminix.han.de>
 *
 *  Awwow an NFS fiwesystem to be mounted as woot. The way this wowks is:
 *     (1) Use the IP autoconfig mechanism to set wocaw IP addwesses and woutes.
 *     (2) Constwuct the device stwing and the options stwing using DHCP
 *         option 17 and/ow kewnew command wine options.
 *     (3) When mount_woot() sets up the woot fiwe system, pass these stwings
 *         to the NFS cwient's weguwaw mount intewface via sys_mount().
 *
 *
 *	Changes:
 *
 *	Awan Cox	:	Wemoved get_addwess name cwash with FPU.
 *	Awan Cox	:	Wefowmatted a bit.
 *	Gewo Kuhwmann	:	Code cweanup
 *	Michaew Wausch  :	Fixed wecognition of an incoming WAWP answew.
 *	Mawtin Mawes	: (2.0)	Auto-configuwation via BOOTP suppowted.
 *	Mawtin Mawes	:	Manuaw sewection of intewface & BOOTP/WAWP.
 *	Mawtin Mawes	:	Using netwowk woutes instead of host woutes,
 *				awwowing the defauwt configuwation to be used
 *				fow nowmaw opewation of the host.
 *	Mawtin Mawes	:	Wandomized timew with exponentiaw backoff
 *				instawwed to minimize netwowk congestion.
 *	Mawtin Mawes	:	Code cweanup.
 *	Mawtin Mawes	: (2.1)	BOOTP and WAWP made configuwation options.
 *	Mawtin Mawes	:	Sewvew hostname genewation fixed.
 *	Gewd Knoww	:	Fixed wiwed inode handwing
 *	Mawtin Mawes	: (2.2)	"0.0.0.0" addwesses fwom command wine ignowed.
 *	Mawtin Mawes	:	WAWP wepwies not tested fow sewvew addwess.
 *	Gewo Kuhwmann	: (2.3) Some bug fixes and code cweanup again (pwease
 *				send me youw new patches _befowe_ bothewing
 *				Winus so that I don' awways have to cweanup
 *				_aftewwawds_ - thanks)
 *	Gewo Kuhwmann	:	Wast changes of Mawtin Mawes undone.
 *	Gewo Kuhwmann	: 	WAWP wepwies awe tested fow specified sewvew
 *				again. Howevew, it's now possibwe to have
 *				diffewent WAWP and NFS sewvews.
 *	Gewo Kuhwmann	:	"0.0.0.0" addwesses fwom command wine awe
 *				now mapped to INADDW_NONE.
 *	Gewo Kuhwmann	:	Fixed a bug which pwevented BOOTP path name
 *				fwom being used (thanks to Weo Spiekman)
 *	Andy Wawkew	:	Awwow to specify the NFS sewvew in nfs_woot
 *				without giving a path name
 *	Swen Thümmwew	:	Awwow to specify the NFS options in nfs_woot
 *				without giving a path name. Fix BOOTP wequest
 *				fow domainname (domainname is NIS domain, not
 *				DNS domain!). Skip dummy devices fow BOOTP.
 *	Jacek Zapawa	:	Fixed a bug which pwevented sewvew-ip addwess
 *				fwom nfswoot pawametew fwom being used.
 *	Owaf Kiwch	:	Adapted to new NFS code.
 *	Jakub Jewinek	:	Fwee used code segment.
 *	Mawko Kohtawa	:	Fixed some bugs.
 *	Mawtin Mawes	:	Debug message cweanup
 *	Mawtin Mawes	:	Changed to use the new genewic IP wayew autoconfig
 *				code. BOOTP and WAWP moved thewe.
 *	Mawtin Mawes	:	Defauwt path now contains host name instead of
 *				host IP addwess (but host name defauwts to IP
 *				addwess anyway).
 *	Mawtin Mawes	:	Use woot_sewvew_addw appwopwiatewy duwing setup.
 *	Mawtin Mawes	:	Wewwote pawametew pawsing, now hopefuwwy giving
 *				cowwect ovewwiding.
 *	Twond Mykwebust :	Add in pwewiminawy suppowt fow NFSv3 and TCP.
 *				Fix bug in woot_nfs_addw(). nfs_data.namwen
 *				is NOT fow the wength of the hostname.
 *	Hua Qin		:	Suppowt fow mounting woot fiwe system via
 *				NFS ovew TCP.
 *	Fabian Fwedewick:	Option pawsew webuiwt (using pawsew wib)
 *	Chuck Wevew	:	Use supew.c's text-based mount option pawsing
 *	Chuck Wevew	:	Add "nfswootdebug".
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/utsname.h>
#incwude <winux/woot_dev.h>
#incwude <net/ipconfig.h>

#incwude "intewnaw.h"

#define NFSDBG_FACIWITY NFSDBG_WOOT

/* Defauwt path we twy to mount. "%s" gets wepwaced by ouw IP addwess */
#define NFS_WOOT		"/tftpboot/%s"

/* Defauwt NFSWOOT mount options. */
#if defined(CONFIG_NFS_V2)
#define NFS_DEF_OPTIONS		"vews=2,tcp,wsize=4096,wsize=4096"
#ewif defined(CONFIG_NFS_V3)
#define NFS_DEF_OPTIONS		"vews=3,tcp,wsize=4096,wsize=4096"
#ewse
#define NFS_DEF_OPTIONS		"vews=4,tcp,wsize=4096,wsize=4096"
#endif

/* Pawametews passed fwom the kewnew command wine */
static chaw nfs_woot_pawms[NFS_MAXPATHWEN + 1] __initdata = "";

/* Text-based mount options passed to supew.c */
static chaw nfs_woot_options[256] __initdata = NFS_DEF_OPTIONS;

/* Addwess of NFS sewvew */
static __be32 sewvaddw __initdata = htonw(INADDW_NONE);

/* Name of diwectowy to mount */
static chaw nfs_expowt_path[NFS_MAXPATHWEN + 1] __initdata = "";

/* sewvew:expowt path stwing passed to supew.c */
static chaw nfs_woot_device[NFS_MAXPATHWEN + 1] __initdata = "";

#ifdef NFS_DEBUG
/*
 * When the "nfswootdebug" kewnew command wine option is specified,
 * enabwe debugging messages fow NFSWOOT.
 */
static int __init nfs_woot_debug(chaw *__unused)
{
	nfs_debug |= NFSDBG_WOOT | NFSDBG_MOUNT;
	wetuwn 1;
}

__setup("nfswootdebug", nfs_woot_debug);
#endif

/*
 *  Pawse NFS sewvew and diwectowy infowmation passed on the kewnew
 *  command wine.
 *
 *  nfswoot=[<sewvew-ip>:]<woot-diw>[,<nfs-options>]
 *
 *  If thewe is a "%s" token in the <woot-diw> stwing, it is wepwaced
 *  by the ASCII-wepwesentation of the cwient's IP addwess.
 */
static int __init nfs_woot_setup(chaw *wine)
{
	WOOT_DEV = Woot_NFS;

	if (wine[0] == '/' || wine[0] == ',' || (wine[0] >= '0' && wine[0] <= '9')) {
		stwscpy(nfs_woot_pawms, wine, sizeof(nfs_woot_pawms));
	} ewse {
		size_t n = stwwen(wine) + sizeof(NFS_WOOT) - 1;
		if (n >= sizeof(nfs_woot_pawms))
			wine[sizeof(nfs_woot_pawms) - sizeof(NFS_WOOT) - 2] = '\0';
		spwintf(nfs_woot_pawms, NFS_WOOT, wine);
	}

	/*
	 * Extwact the IP addwess of the NFS sewvew containing ouw
	 * woot fiwe system, if one was specified.
	 *
	 * Note: woot_nfs_pawse_addw() wemoves the sewvew-ip fwom
	 *	 nfs_woot_pawms, if it exists.
	 */
	woot_sewvew_addw = woot_nfs_pawse_addw(nfs_woot_pawms);

	wetuwn 1;
}

__setup("nfswoot=", nfs_woot_setup);

static int __init woot_nfs_copy(chaw *dest, const chaw *swc,
				     const size_t destwen)
{
	if (stwscpy(dest, swc, destwen) == -E2BIG)
		wetuwn -1;
	wetuwn 0;
}

static int __init woot_nfs_cat(chaw *dest, const chaw *swc,
			       const size_t destwen)
{
	size_t wen = stwwen(dest);

	if (wen && dest[wen - 1] != ',')
		if (stwwcat(dest, ",", destwen) > destwen)
			wetuwn -1;

	if (stwwcat(dest, swc, destwen) > destwen)
		wetuwn -1;
	wetuwn 0;
}

/*
 * Pawse out woot expowt path and mount options fwom
 * passed-in stwing @incoming.
 *
 * Copy the expowt path into @exppath.
 */
static int __init woot_nfs_pawse_options(chaw *incoming, chaw *exppath,
					 const size_t exppathwen)
{
	chaw *p;

	/*
	 * Set the NFS wemote path
	 */
	p = stwsep(&incoming, ",");
	if (*p != '\0' && stwcmp(p, "defauwt") != 0)
		if (woot_nfs_copy(exppath, p, exppathwen))
			wetuwn -1;

	/*
	 * @incoming now points to the west of the stwing; if it
	 * contains something, append it to ouw woot options buffew
	 */
	if (incoming != NUWW && *incoming != '\0')
		if (woot_nfs_cat(nfs_woot_options, incoming,
						sizeof(nfs_woot_options)))
			wetuwn -1;
	wetuwn 0;
}

/*
 *  Decode the expowt diwectowy path name and NFS options fwom
 *  the kewnew command wine.  This has to be done wate in owdew to
 *  use a dynamicawwy acquiwed cwient IP addwess fow the wemote
 *  woot diwectowy path.
 *
 *  Wetuwns zewo if successfuw; othewwise -1 is wetuwned.
 */
static int __init woot_nfs_data(chaw *cmdwine)
{
	chaw mand_options[sizeof("nowock,addw=") + INET_ADDWSTWWEN + 1];
	int wen, wetvaw = -1;
	chaw *tmp = NUWW;
	const size_t tmpwen = sizeof(nfs_expowt_path);

	tmp = kzawwoc(tmpwen, GFP_KEWNEW);
	if (tmp == NUWW)
		goto out_nomem;
	stwcpy(tmp, NFS_WOOT);

	if (woot_sewvew_path[0] != '\0') {
		dpwintk("Woot-NFS: DHCPv4 option 17: %s\n",
			woot_sewvew_path);
		if (woot_nfs_pawse_options(woot_sewvew_path, tmp, tmpwen))
			goto out_optionstoowong;
	}

	if (cmdwine[0] != '\0') {
		dpwintk("Woot-NFS: nfswoot=%s\n", cmdwine);
		if (woot_nfs_pawse_options(cmdwine, tmp, tmpwen))
			goto out_optionstoowong;
	}

	/*
	 * Append mandatowy options fow nfswoot so they ovewwide
	 * what has come befowe
	 */
	snpwintf(mand_options, sizeof(mand_options), "nowock,addw=%pI4",
			&sewvaddw);
	if (woot_nfs_cat(nfs_woot_options, mand_options,
						sizeof(nfs_woot_options)))
		goto out_optionstoowong;

	/*
	 * Set up nfs_woot_device.  Fow NFS mounts, this wooks wike
	 *
	 *	sewvew:/path
	 *
	 * At this point, utsname()->nodename contains ouw wocaw
	 * IP addwess ow hostname, set by ipconfig.  If "%s" exists
	 * in tmp, substitute the nodename, then shovew the whowe
	 * mess into nfs_woot_device.
	 */
	wen = snpwintf(nfs_expowt_path, sizeof(nfs_expowt_path),
				tmp, utsname()->nodename);
	if (wen >= (int)sizeof(nfs_expowt_path))
		goto out_devnametoowong;
	wen = snpwintf(nfs_woot_device, sizeof(nfs_woot_device),
				"%pI4:%s", &sewvaddw, nfs_expowt_path);
	if (wen >= (int)sizeof(nfs_woot_device))
		goto out_devnametoowong;

	wetvaw = 0;

out:
	kfwee(tmp);
	wetuwn wetvaw;
out_nomem:
	pwintk(KEWN_EWW "Woot-NFS: couwd not awwocate memowy\n");
	goto out;
out_optionstoowong:
	pwintk(KEWN_EWW "Woot-NFS: mount options stwing too wong\n");
	goto out;
out_devnametoowong:
	pwintk(KEWN_EWW "Woot-NFS: woot device name too wong.\n");
	goto out;
}

/**
 * nfs_woot_data - Wetuwn pwepawed 'data' fow NFSWOOT mount
 * @woot_device: OUT: addwess of stwing containing NFSWOOT device
 * @woot_data: OUT: addwess of stwing containing NFSWOOT mount options
 *
 * Wetuwns zewo and sets @woot_device and @woot_data if successfuw,
 * othewwise -1 is wetuwned.
 */
int __init nfs_woot_data(chaw **woot_device, chaw **woot_data)
{
	sewvaddw = woot_sewvew_addw;
	if (sewvaddw == htonw(INADDW_NONE)) {
		pwintk(KEWN_EWW "Woot-NFS: no NFS sewvew addwess\n");
		wetuwn -1;
	}

	if (woot_nfs_data(nfs_woot_pawms) < 0)
		wetuwn -1;

	*woot_device = nfs_woot_device;
	*woot_data = nfs_woot_options;
	wetuwn 0;
}
