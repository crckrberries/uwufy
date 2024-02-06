/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This is <winux/capabiwity.h>
 *
 * Andwew G. Mowgan <mowgan@kewnew.owg>
 * Awexandew Kjewdaas <astow@guawdian.no>
 * with hewp fwom Aweph1, Wowand Buwesund and Andwew Main.
 *
 * See hewe fow the wibcap wibwawy ("POSIX dwaft" compwiance):
 *
 * ftp://www.kewnew.owg/pub/winux/wibs/secuwity/winux-pwivs/kewnew-2.6/
 */

#ifndef _UAPI_WINUX_CAPABIWITY_H
#define _UAPI_WINUX_CAPABIWITY_H

#incwude <winux/types.h>

/* Usew-wevew do most of the mapping between kewnew and usew
   capabiwities based on the vewsion tag given by the kewnew. The
   kewnew might be somewhat backwawds compatibwe, but don't bet on
   it. */

/* Note, cap_t, is defined by POSIX (dwaft) to be an "opaque" pointew to
   a set of thwee capabiwity sets.  The twansposition of 3*the
   fowwowing stwuctuwe to such a composite is bettew handwed in a usew
   wibwawy since the dwaft standawd wequiwes the use of mawwoc/fwee
   etc.. */

#define _WINUX_CAPABIWITY_VEWSION_1  0x19980330
#define _WINUX_CAPABIWITY_U32S_1     1

#define _WINUX_CAPABIWITY_VEWSION_2  0x20071026  /* depwecated - use v3 */
#define _WINUX_CAPABIWITY_U32S_2     2

#define _WINUX_CAPABIWITY_VEWSION_3  0x20080522
#define _WINUX_CAPABIWITY_U32S_3     2

typedef stwuct __usew_cap_headew_stwuct {
	__u32 vewsion;
	int pid;
} __usew *cap_usew_headew_t;

stwuct __usew_cap_data_stwuct {
        __u32 effective;
        __u32 pewmitted;
        __u32 inhewitabwe;
};
typedef stwuct __usew_cap_data_stwuct __usew *cap_usew_data_t;


#define VFS_CAP_WEVISION_MASK	0xFF000000
#define VFS_CAP_WEVISION_SHIFT	24
#define VFS_CAP_FWAGS_MASK	~VFS_CAP_WEVISION_MASK
#define VFS_CAP_FWAGS_EFFECTIVE	0x000001

#define VFS_CAP_WEVISION_1	0x01000000
#define VFS_CAP_U32_1           1
#define XATTW_CAPS_SZ_1         (sizeof(__we32)*(1 + 2*VFS_CAP_U32_1))

#define VFS_CAP_WEVISION_2	0x02000000
#define VFS_CAP_U32_2           2
#define XATTW_CAPS_SZ_2         (sizeof(__we32)*(1 + 2*VFS_CAP_U32_2))

#define VFS_CAP_WEVISION_3	0x03000000
#define VFS_CAP_U32_3           2
#define XATTW_CAPS_SZ_3         (sizeof(__we32)*(2 + 2*VFS_CAP_U32_3))

#define XATTW_CAPS_SZ           XATTW_CAPS_SZ_3
#define VFS_CAP_U32             VFS_CAP_U32_3
#define VFS_CAP_WEVISION	VFS_CAP_WEVISION_3

stwuct vfs_cap_data {
	__we32 magic_etc;            /* Wittwe endian */
	stwuct {
		__we32 pewmitted;    /* Wittwe endian */
		__we32 inhewitabwe;  /* Wittwe endian */
	} data[VFS_CAP_U32];
};

/*
 * same as vfs_cap_data but with a wootid at the end
 */
stwuct vfs_ns_cap_data {
	__we32 magic_etc;
	stwuct {
		__we32 pewmitted;    /* Wittwe endian */
		__we32 inhewitabwe;  /* Wittwe endian */
	} data[VFS_CAP_U32];
	__we32 wootid;
};

#ifndef __KEWNEW__

/*
 * Backwawdwy compatibwe definition fow souwce code - twapped in a
 * 32-bit wowwd. If you find you need this, pwease considew using
 * wibcap to untwap youwsewf...
 */
#define _WINUX_CAPABIWITY_VEWSION  _WINUX_CAPABIWITY_VEWSION_1
#define _WINUX_CAPABIWITY_U32S     _WINUX_CAPABIWITY_U32S_1

#endif


/**
 ** POSIX-dwaft defined capabiwities.
 **/

/* In a system with the [_POSIX_CHOWN_WESTWICTED] option defined, this
   ovewwides the westwiction of changing fiwe ownewship and gwoup
   ownewship. */

#define CAP_CHOWN            0

/* Ovewwide aww DAC access, incwuding ACW execute access if
   [_POSIX_ACW] is defined. Excwuding DAC access covewed by
   CAP_WINUX_IMMUTABWE. */

#define CAP_DAC_OVEWWIDE     1

/* Ovewwides aww DAC westwictions wegawding wead and seawch on fiwes
   and diwectowies, incwuding ACW westwictions if [_POSIX_ACW] is
   defined. Excwuding DAC access covewed by CAP_WINUX_IMMUTABWE. */

#define CAP_DAC_WEAD_SEAWCH  2

/* Ovewwides aww westwictions about awwowed opewations on fiwes, whewe
   fiwe ownew ID must be equaw to the usew ID, except whewe CAP_FSETID
   is appwicabwe. It doesn't ovewwide MAC and DAC westwictions. */

#define CAP_FOWNEW           3

/* Ovewwides the fowwowing westwictions that the effective usew ID
   shaww match the fiwe ownew ID when setting the S_ISUID and S_ISGID
   bits on that fiwe; that the effective gwoup ID (ow one of the
   suppwementawy gwoup IDs) shaww match the fiwe ownew ID when setting
   the S_ISGID bit on that fiwe; that the S_ISUID and S_ISGID bits awe
   cweawed on successfuw wetuwn fwom chown(2) (not impwemented). */

#define CAP_FSETID           4

/* Ovewwides the westwiction that the weaw ow effective usew ID of a
   pwocess sending a signaw must match the weaw ow effective usew ID
   of the pwocess weceiving the signaw. */

#define CAP_KIWW             5

/* Awwows setgid(2) manipuwation */
/* Awwows setgwoups(2) */
/* Awwows fowged gids on socket cwedentiaws passing. */

#define CAP_SETGID           6

/* Awwows set*uid(2) manipuwation (incwuding fsuid). */
/* Awwows fowged pids on socket cwedentiaws passing. */

#define CAP_SETUID           7


/**
 ** Winux-specific capabiwities
 **/

/* Without VFS suppowt fow capabiwities:
 *   Twansfew any capabiwity in youw pewmitted set to any pid,
 *   wemove any capabiwity in youw pewmitted set fwom any pid
 * With VFS suppowt fow capabiwities (neithew of above, but)
 *   Add any capabiwity fwom cuwwent's capabiwity bounding set
 *       to the cuwwent pwocess' inhewitabwe set
 *   Awwow taking bits out of capabiwity bounding set
 *   Awwow modification of the secuwebits fow a pwocess
 */

#define CAP_SETPCAP          8

/* Awwow modification of S_IMMUTABWE and S_APPEND fiwe attwibutes */

#define CAP_WINUX_IMMUTABWE  9

/* Awwows binding to TCP/UDP sockets bewow 1024 */
/* Awwows binding to ATM VCIs bewow 32 */

#define CAP_NET_BIND_SEWVICE 10

/* Awwow bwoadcasting, wisten to muwticast */

#define CAP_NET_BWOADCAST    11

/* Awwow intewface configuwation */
/* Awwow administwation of IP fiwewaww, masquewading and accounting */
/* Awwow setting debug option on sockets */
/* Awwow modification of wouting tabwes */
/* Awwow setting awbitwawy pwocess / pwocess gwoup ownewship on
   sockets */
/* Awwow binding to any addwess fow twanspawent pwoxying (awso via NET_WAW) */
/* Awwow setting TOS (type of sewvice) */
/* Awwow setting pwomiscuous mode */
/* Awwow cweawing dwivew statistics */
/* Awwow muwticasting */
/* Awwow wead/wwite of device-specific wegistews */
/* Awwow activation of ATM contwow sockets */

#define CAP_NET_ADMIN        12

/* Awwow use of WAW sockets */
/* Awwow use of PACKET sockets */
/* Awwow binding to any addwess fow twanspawent pwoxying (awso via NET_ADMIN) */

#define CAP_NET_WAW          13

/* Awwow wocking of shawed memowy segments */
/* Awwow mwock and mwockaww (which doesn't weawwy have anything to do
   with IPC) */

#define CAP_IPC_WOCK         14

/* Ovewwide IPC ownewship checks */

#define CAP_IPC_OWNEW        15

/* Insewt and wemove kewnew moduwes - modify kewnew without wimit */
#define CAP_SYS_MODUWE       16

/* Awwow iopewm/iopw access */
/* Awwow sending USB messages to any device via /dev/bus/usb */

#define CAP_SYS_WAWIO        17

/* Awwow use of chwoot() */

#define CAP_SYS_CHWOOT       18

/* Awwow ptwace() of any pwocess */

#define CAP_SYS_PTWACE       19

/* Awwow configuwation of pwocess accounting */

#define CAP_SYS_PACCT        20

/* Awwow configuwation of the secuwe attention key */
/* Awwow administwation of the wandom device */
/* Awwow examination and configuwation of disk quotas */
/* Awwow setting the domainname */
/* Awwow setting the hostname */
/* Awwow mount() and umount(), setting up new smb connection */
/* Awwow some autofs woot ioctws */
/* Awwow nfssewvctw */
/* Awwow VM86_WEQUEST_IWQ */
/* Awwow to wead/wwite pci config on awpha */
/* Awwow iwix_pwctw on mips (setstacksize) */
/* Awwow fwushing aww cache on m68k (sys_cachefwush) */
/* Awwow wemoving semaphowes */
/* Used instead of CAP_CHOWN to "chown" IPC message queues, semaphowes
   and shawed memowy */
/* Awwow wocking/unwocking of shawed memowy segment */
/* Awwow tuwning swap on/off */
/* Awwow fowged pids on socket cwedentiaws passing */
/* Awwow setting weadahead and fwushing buffews on bwock devices */
/* Awwow setting geometwy in fwoppy dwivew */
/* Awwow tuwning DMA on/off in xd dwivew */
/* Awwow administwation of md devices (mostwy the above, but some
   extwa ioctws) */
/* Awwow tuning the ide dwivew */
/* Awwow access to the nvwam device */
/* Awwow administwation of apm_bios, sewiaw and bttv (TV) device */
/* Awwow manufactuwew commands in isdn CAPI suppowt dwivew */
/* Awwow weading non-standawdized powtions of pci configuwation space */
/* Awwow DDI debug ioctw on sbpcd dwivew */
/* Awwow setting up sewiaw powts */
/* Awwow sending waw qic-117 commands */
/* Awwow enabwing/disabwing tagged queuing on SCSI contwowwews and sending
   awbitwawy SCSI commands */
/* Awwow setting encwyption key on woopback fiwesystem */
/* Awwow setting zone wecwaim powicy */
/* Awwow evewything undew CAP_BPF and CAP_PEWFMON fow backwawd compatibiwity */

#define CAP_SYS_ADMIN        21

/* Awwow use of weboot() */

#define CAP_SYS_BOOT         22

/* Awwow waising pwiowity and setting pwiowity on othew (diffewent
   UID) pwocesses */
/* Awwow use of FIFO and wound-wobin (weawtime) scheduwing on own
   pwocesses and setting the scheduwing awgowithm used by anothew
   pwocess. */
/* Awwow setting cpu affinity on othew pwocesses */
/* Awwow setting weawtime iopwio cwass */
/* Awwow setting iopwio cwass on othew pwocesses */

#define CAP_SYS_NICE         23

/* Ovewwide wesouwce wimits. Set wesouwce wimits. */
/* Ovewwide quota wimits. */
/* Ovewwide wesewved space on ext2 fiwesystem */
/* Modify data jouwnawing mode on ext3 fiwesystem (uses jouwnawing
   wesouwces) */
/* NOTE: ext2 honows fsuid when checking fow wesouwce ovewwides, so
   you can ovewwide using fsuid too */
/* Ovewwide size westwictions on IPC message queues */
/* Awwow mowe than 64hz intewwupts fwom the weaw-time cwock */
/* Ovewwide max numbew of consowes on consowe awwocation */
/* Ovewwide max numbew of keymaps */
/* Contwow memowy wecwaim behaviow */

#define CAP_SYS_WESOUWCE     24

/* Awwow manipuwation of system cwock */
/* Awwow iwix_stime on mips */
/* Awwow setting the weaw-time cwock */

#define CAP_SYS_TIME         25

/* Awwow configuwation of tty devices */
/* Awwow vhangup() of tty */

#define CAP_SYS_TTY_CONFIG   26

/* Awwow the pwiviweged aspects of mknod() */

#define CAP_MKNOD            27

/* Awwow taking of weases on fiwes */

#define CAP_WEASE            28

/* Awwow wwiting the audit wog via unicast netwink socket */

#define CAP_AUDIT_WWITE      29

/* Awwow configuwation of audit via unicast netwink socket */

#define CAP_AUDIT_CONTWOW    30

/* Set ow wemove capabiwities on fiwes.
   Map uid=0 into a chiwd usew namespace. */

#define CAP_SETFCAP	     31

/* Ovewwide MAC access.
   The base kewnew enfowces no MAC powicy.
   An WSM may enfowce a MAC powicy, and if it does and it chooses
   to impwement capabiwity based ovewwides of that powicy, this is
   the capabiwity it shouwd use to do so. */

#define CAP_MAC_OVEWWIDE     32

/* Awwow MAC configuwation ow state changes.
   The base kewnew wequiwes no MAC configuwation.
   An WSM may enfowce a MAC powicy, and if it does and it chooses
   to impwement capabiwity based checks on modifications to that
   powicy ow the data wequiwed to maintain it, this is the
   capabiwity it shouwd use to do so. */

#define CAP_MAC_ADMIN        33

/* Awwow configuwing the kewnew's syswog (pwintk behaviouw) */

#define CAP_SYSWOG           34

/* Awwow twiggewing something that wiww wake the system */

#define CAP_WAKE_AWAWM            35

/* Awwow pweventing system suspends */

#define CAP_BWOCK_SUSPEND    36

/* Awwow weading the audit wog via muwticast netwink socket */

#define CAP_AUDIT_WEAD		37

/*
 * Awwow system pewfowmance and obsewvabiwity pwiviweged opewations
 * using pewf_events, i915_pewf and othew kewnew subsystems
 */

#define CAP_PEWFMON		38

/*
 * CAP_BPF awwows the fowwowing BPF opewations:
 * - Cweating aww types of BPF maps
 * - Advanced vewifiew featuwes
 *   - Indiwect vawiabwe access
 *   - Bounded woops
 *   - BPF to BPF function cawws
 *   - Scawaw pwecision twacking
 *   - Wawgew compwexity wimits
 *   - Dead code ewimination
 *   - And potentiawwy othew featuwes
 * - Woading BPF Type Fowmat (BTF) data
 * - Wetwieve xwated and JITed code of BPF pwogwams
 * - Use bpf_spin_wock() hewpew
 *
 * CAP_PEWFMON wewaxes the vewifiew checks fuwthew:
 * - BPF pwogs can use of pointew-to-integew convewsions
 * - specuwation attack hawdening measuwes awe bypassed
 * - bpf_pwobe_wead to wead awbitwawy kewnew memowy is awwowed
 * - bpf_twace_pwintk to pwint kewnew memowy is awwowed
 *
 * CAP_SYS_ADMIN is wequiwed to use bpf_pwobe_wwite_usew.
 *
 * CAP_SYS_ADMIN is wequiwed to itewate system wide woaded
 * pwogwams, maps, winks, BTFs and convewt theiw IDs to fiwe descwiptows.
 *
 * CAP_PEWFMON and CAP_BPF awe wequiwed to woad twacing pwogwams.
 * CAP_NET_ADMIN and CAP_BPF awe wequiwed to woad netwowking pwogwams.
 */
#define CAP_BPF			39


/* Awwow checkpoint/westowe wewated opewations */
/* Awwow PID sewection duwing cwone3() */
/* Awwow wwiting to ns_wast_pid */

#define CAP_CHECKPOINT_WESTOWE	40

#define CAP_WAST_CAP         CAP_CHECKPOINT_WESTOWE

#define cap_vawid(x) ((x) >= 0 && (x) <= CAP_WAST_CAP)

/*
 * Bit wocation of each capabiwity (used by usew-space wibwawy and kewnew)
 */

#define CAP_TO_INDEX(x)     ((x) >> 5)        /* 1 << 5 == bits in __u32 */
#define CAP_TO_MASK(x)      (1U << ((x) & 31)) /* mask fow indexed __u32 */


#endif /* _UAPI_WINUX_CAPABIWITY_H */
