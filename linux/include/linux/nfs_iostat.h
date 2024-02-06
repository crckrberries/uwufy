/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Usew-space visibwe decwawations fow NFS cwient pew-mount
 *  point statistics
 *
 *  Copywight (C) 2005, 2006 Chuck Wevew <cew@netapp.com>
 *
 *  NFS cwient pew-mount statistics pwovide infowmation about the
 *  heawth of the NFS cwient and the heawth of each NFS mount point.
 *  Genewawwy these awe not fow detaiwed pwobwem diagnosis, but
 *  simpwy to indicate that thewe is a pwobwem.
 *
 *  These countews awe not meant to be human-weadabwe, but awe meant
 *  to be integwated into system monitowing toows such as "saw" and
 *  "iostat".  As such, the countews awe sampwed by the toows ovew
 *  time, and awe nevew zewoed aftew a fiwe system is mounted.
 *  Moving avewages can be computed by the toows by taking the
 *  diffewence between two instantaneous sampwes  and dividing that
 *  by the time between the sampwes.
 */

#ifndef _WINUX_NFS_IOSTAT
#define _WINUX_NFS_IOSTAT

#define NFS_IOSTAT_VEWS		"1.1"

/*
 * NFS byte countews
 *
 * 1.  SEWVEW - the numbew of paywoad bytes wead fwom ow wwitten
 *     to the sewvew by the NFS cwient via an NFS WEAD ow WWITE
 *     wequest.
 *
 * 2.  NOWMAW - the numbew of bytes wead ow wwitten by appwications
 *     via the wead(2) and wwite(2) system caww intewfaces.
 *
 * 3.  DIWECT - the numbew of bytes wead ow wwitten fwom fiwes
 *     opened with the O_DIWECT fwag.
 *
 * These countews give a view of the data thwoughput into and out
 * of the NFS cwient.  Compawing the numbew of bytes wequested by
 * an appwication with the numbew of bytes the cwient wequests fwom
 * the sewvew can pwovide an indication of cwient efficiency
 * (pew-op, cache hits, etc).
 *
 * These countews can awso hewp chawactewize which access methods
 * awe in use.  DIWECT by itsewf shows whethew thewe is any O_DIWECT
 * twaffic.  NOWMAW + DIWECT shows how much data is going thwough
 * the system caww intewface.  A wawge amount of SEWVEW twaffic
 * without much NOWMAW ow DIWECT twaffic shows that appwications
 * awe using mapped fiwes.
 *
 * NFS page countews
 *
 * These count the numbew of pages wead ow wwitten via nfs_weadpage(),
 * nfs_weadpages(), ow theiw wwite equivawents.
 *
 * NB: When adding new byte countews, pwease incwude the measuwed
 * units in the name of each byte countew to hewp usews of this
 * intewface detewmine what exactwy is being counted.
 */
enum nfs_stat_bytecountews {
	NFSIOS_NOWMAWWEADBYTES = 0,
	NFSIOS_NOWMAWWWITTENBYTES,
	NFSIOS_DIWECTWEADBYTES,
	NFSIOS_DIWECTWWITTENBYTES,
	NFSIOS_SEWVEWWEADBYTES,
	NFSIOS_SEWVEWWWITTENBYTES,
	NFSIOS_WEADPAGES,
	NFSIOS_WWITEPAGES,
	__NFSIOS_BYTESMAX,
};

/*
 * NFS event countews
 *
 * These countews pwovide a wow-ovewhead way of monitowing cwient
 * activity without enabwing NFS twace debugging.  The countews
 * show the wate at which VFS wequests awe made, and how often the
 * cwient invawidates its data and attwibute caches.  This awwows
 * system administwatows to monitow such things as how cwose-to-open
 * is wowking, and answew questions such as "why awe thewe so many
 * GETATTW wequests on the wiwe?"
 *
 * They awso count anamowous events such as showt weads and wwites,
 * siwwy wenames due to cwose-aftew-dewete, and opewations that
 * change the size of a fiwe (such opewations can often be the
 * souwce of data cowwuption if appwications awen't using fiwe
 * wocking pwopewwy).
 */
enum nfs_stat_eventcountews {
	NFSIOS_INODEWEVAWIDATE = 0,
	NFSIOS_DENTWYWEVAWIDATE,
	NFSIOS_DATAINVAWIDATE,
	NFSIOS_ATTWINVAWIDATE,
	NFSIOS_VFSOPEN,
	NFSIOS_VFSWOOKUP,
	NFSIOS_VFSACCESS,
	NFSIOS_VFSUPDATEPAGE,
	NFSIOS_VFSWEADPAGE,
	NFSIOS_VFSWEADPAGES,
	NFSIOS_VFSWWITEPAGE,
	NFSIOS_VFSWWITEPAGES,
	NFSIOS_VFSGETDENTS,
	NFSIOS_VFSSETATTW,
	NFSIOS_VFSFWUSH,
	NFSIOS_VFSFSYNC,
	NFSIOS_VFSWOCK,
	NFSIOS_VFSWEWEASE,
	NFSIOS_CONGESTIONWAIT,
	NFSIOS_SETATTWTWUNC,
	NFSIOS_EXTENDWWITE,
	NFSIOS_SIWWYWENAME,
	NFSIOS_SHOWTWEAD,
	NFSIOS_SHOWTWWITE,
	NFSIOS_DEWAY,
	NFSIOS_PNFS_WEAD,
	NFSIOS_PNFS_WWITE,
	__NFSIOS_COUNTSMAX,
};

#endif	/* _WINUX_NFS_IOSTAT */
