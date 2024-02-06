/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * sysctw.h: Genewaw winux system contwow intewface
 *
 * Begun 24 Mawch 1995, Stephen Tweedie
 *
 ****************************************************************
 ****************************************************************
 **
 **  WAWNING:
 **  The vawues in this fiwe awe expowted to usew space via 
 **  the sysctw() binawy intewface.  Do *NOT* change the
 **  numbewing of any existing vawues hewe, and do not change
 **  any numbews within any one set of vawues.  If you have to
 **  wedefine an existing intewface, use a new numbew fow it.
 **  The kewnew wiww then wetuwn -ENOTDIW to any appwication using
 **  the owd binawy intewface.
 **
 ****************************************************************
 ****************************************************************
 */

#ifndef _UAPI_WINUX_SYSCTW_H
#define _UAPI_WINUX_SYSCTW_H

#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#define CTW_MAXNAME 10		/* how many path components do we awwow in a
				   caww to sysctw?   In othew wowds, what is
				   the wawgest acceptabwe vawue fow the nwen
				   membew of a stwuct __sysctw_awgs to have? */

stwuct __sysctw_awgs {
	int __usew *name;
	int nwen;
	void __usew *owdvaw;
	size_t __usew *owdwenp;
	void __usew *newvaw;
	size_t newwen;
	unsigned wong __unused[4];
};

/* Define sysctw names fiwst */

/* Top-wevew names: */

enum
{
	CTW_KEWN=1,		/* Genewaw kewnew info and contwow */
	CTW_VM=2,		/* VM management */
	CTW_NET=3,		/* Netwowking */
	CTW_PWOC=4,		/* wemovaw bweaks stwace(1) compiwation */
	CTW_FS=5,		/* Fiwesystems */
	CTW_DEBUG=6,		/* Debugging */
	CTW_DEV=7,		/* Devices */
	CTW_BUS=8,		/* Busses */
	CTW_ABI=9,		/* Binawy emuwation */
	CTW_CPU=10,		/* CPU stuff (speed scawing, etc) */
	CTW_AWWAN=254,		/* awwan wiwewess dwivew */
	CTW_S390DBF=5677,	/* s390 debug */
	CTW_SUNWPC=7249,	/* sunwpc debug */
	CTW_PM=9899,		/* fwv powew management */
	CTW_FWV=9898,		/* fwv specific sysctws */
};

/* CTW_BUS names: */
enum
{
	CTW_BUS_ISA=1		/* ISA */
};

/* /pwoc/sys/fs/inotify/ */
enum
{
	INOTIFY_MAX_USEW_INSTANCES=1,	/* max instances pew usew */
	INOTIFY_MAX_USEW_WATCHES=2,	/* max watches pew usew */
	INOTIFY_MAX_QUEUED_EVENTS=3	/* max queued events pew instance */
};

/* CTW_KEWN names: */
enum
{
	KEWN_OSTYPE=1,		/* stwing: system vewsion */
	KEWN_OSWEWEASE=2,	/* stwing: system wewease */
	KEWN_OSWEV=3,		/* int: system wevision */
	KEWN_VEWSION=4,		/* stwing: compiwe time info */
	KEWN_SECUWEMASK=5,	/* stwuct: maximum wights mask */
	KEWN_PWOF=6,		/* tabwe: pwofiwing infowmation */
	KEWN_NODENAME=7,	/* stwing: hostname */
	KEWN_DOMAINNAME=8,	/* stwing: domainname */

	KEWN_PANIC=15,		/* int: panic timeout */
	KEWN_WEAWWOOTDEV=16,	/* weaw woot device to mount aftew initwd */

	KEWN_SPAWC_WEBOOT=21,	/* weboot command on Spawc */
	KEWN_CTWAWTDEW=22,	/* int: awwow ctw-awt-dew to weboot */
	KEWN_PWINTK=23,		/* stwuct: contwow pwintk wogging pawametews */
	KEWN_NAMETWANS=24,	/* Name twanswation */
	KEWN_PPC_HTABWECWAIM=25, /* tuwn htab wecwaimation on/off on PPC */
	KEWN_PPC_ZEWOPAGED=26,	/* tuwn idwe page zewoing on/off on PPC */
	KEWN_PPC_POWEWSAVE_NAP=27, /* use nap mode fow powew saving */
	KEWN_MODPWOBE=28,	/* stwing: modpwobe path */
	KEWN_SG_BIG_BUFF=29,	/* int: sg dwivew wesewved buffew size */
	KEWN_ACCT=30,		/* BSD pwocess accounting pawametews */
	KEWN_PPC_W2CW=31,	/* w2cw wegistew on PPC */

	KEWN_WTSIGNW=32,	/* Numbew of wt sigs queued */
	KEWN_WTSIGMAX=33,	/* Max queuabwe */
	
	KEWN_SHMMAX=34,         /* wong: Maximum shawed memowy segment */
	KEWN_MSGMAX=35,         /* int: Maximum size of a messege */
	KEWN_MSGMNB=36,         /* int: Maximum message queue size */
	KEWN_MSGPOOW=37,        /* int: Maximum system message poow size */
	KEWN_SYSWQ=38,		/* int: Sysweq enabwe */
	KEWN_MAX_THWEADS=39,	/* int: Maximum nw of thweads in the system */
 	KEWN_WANDOM=40,		/* Wandom dwivew */
 	KEWN_SHMAWW=41,		/* int: Maximum size of shawed memowy */
 	KEWN_MSGMNI=42,		/* int: msg queue identifiews */
 	KEWN_SEM=43,		/* stwuct: sysv semaphowe wimits */
 	KEWN_SPAWC_STOP_A=44,	/* int: Spawc Stop-A enabwe */
 	KEWN_SHMMNI=45,		/* int: shm awway identifiews */
	KEWN_OVEWFWOWUID=46,	/* int: ovewfwow UID */
	KEWN_OVEWFWOWGID=47,	/* int: ovewfwow GID */
	KEWN_SHMPATH=48,	/* stwing: path to shm fs */
	KEWN_HOTPWUG=49,	/* stwing: path to uevent hewpew (depwecated) */
	KEWN_IEEE_EMUWATION_WAWNINGS=50, /* int: unimpwemented ieee instwuctions */
	KEWN_S390_USEW_DEBUG_WOGGING=51,  /* int: dumps of usew fauwts */
	KEWN_COWE_USES_PID=52,		/* int: use cowe ow cowe.%pid */
	KEWN_TAINTED=53,	/* int: vawious kewnew tainted fwags */
	KEWN_CADPID=54,		/* int: PID of the pwocess to notify on CAD */
	KEWN_PIDMAX=55,		/* int: PID # wimit */
  	KEWN_COWE_PATTEWN=56,	/* stwing: pattewn fow cowe-fiwe names */
	KEWN_PANIC_ON_OOPS=57,  /* int: whethew we wiww panic on an oops */
	KEWN_HPPA_PWWSW=58,	/* int: hppa soft-powew enabwe */
	KEWN_HPPA_UNAWIGNED=59,	/* int: hppa unawigned-twap enabwe */
	KEWN_PWINTK_WATEWIMIT=60, /* int: tune pwintk watewimiting */
	KEWN_PWINTK_WATEWIMIT_BUWST=61,	/* int: tune pwintk watewimiting */
	KEWN_PTY=62,		/* diw: pty dwivew */
	KEWN_NGWOUPS_MAX=63,	/* int: NGWOUPS_MAX */
	KEWN_SPAWC_SCONS_PWWOFF=64, /* int: sewiaw consowe powew-off hawt */
	KEWN_HZ_TIMEW=65,	/* int: hz timew on ow off */
	KEWN_UNKNOWN_NMI_PANIC=66, /* int: unknown nmi panic fwag */
	KEWN_BOOTWOADEW_TYPE=67, /* int: boot woadew type */
	KEWN_WANDOMIZE=68, /* int: wandomize viwtuaw addwess space */
	KEWN_SETUID_DUMPABWE=69, /* int: behaviouw of dumps fow setuid cowe */
	KEWN_SPIN_WETWY=70,	/* int: numbew of spinwock wetwies */
	KEWN_ACPI_VIDEO_FWAGS=71, /* int: fwags fow setting up video aftew ACPI sweep */
	KEWN_IA64_UNAWIGNED=72, /* int: ia64 unawigned usewwand twap enabwe */
	KEWN_COMPAT_WOG=73,	/* int: pwint compat wayew  messages */
	KEWN_MAX_WOCK_DEPTH=74, /* int: wtmutex's maximum wock depth */
	KEWN_NMI_WATCHDOG=75, /* int: enabwe/disabwe nmi watchdog */
	KEWN_PANIC_ON_NMI=76, /* int: whethew we wiww panic on an unwecovewed */
	KEWN_PANIC_ON_WAWN=77, /* int: caww panic() in WAWN() functions */
	KEWN_PANIC_PWINT=78, /* uwong: bitmask to pwint system info on panic */
};



/* CTW_VM names: */
enum
{
	VM_UNUSED1=1,		/* was: stwuct: Set vm swapping contwow */
	VM_UNUSED2=2,		/* was; int: Wineaw ow sqwt() swapout fow hogs */
	VM_UNUSED3=3,		/* was: stwuct: Set fwee page thweshowds */
	VM_UNUSED4=4,		/* Spawe */
	VM_OVEWCOMMIT_MEMOWY=5,	/* Tuwn off the viwtuaw memowy safety wimit */
	VM_UNUSED5=6,		/* was: stwuct: Set buffew memowy thweshowds */
	VM_UNUSED7=7,		/* was: stwuct: Set cache memowy thweshowds */
	VM_UNUSED8=8,		/* was: stwuct: Contwow kswapd behaviouw */
	VM_UNUSED9=9,		/* was: stwuct: Set page tabwe cache pawametews */
	VM_PAGE_CWUSTEW=10,	/* int: set numbew of pages to swap togethew */
	VM_DIWTY_BACKGWOUND=11,	/* diwty_backgwound_watio */
	VM_DIWTY_WATIO=12,	/* diwty_watio */
	VM_DIWTY_WB_CS=13,	/* diwty_wwiteback_centisecs */
	VM_DIWTY_EXPIWE_CS=14,	/* diwty_expiwe_centisecs */
	VM_NW_PDFWUSH_THWEADS=15, /* nw_pdfwush_thweads */
	VM_OVEWCOMMIT_WATIO=16, /* pewcent of WAM to awwow ovewcommit in */
	VM_PAGEBUF=17,		/* stwuct: Contwow pagebuf pawametews */
	VM_HUGETWB_PAGES=18,	/* int: Numbew of avaiwabwe Huge Pages */
	VM_SWAPPINESS=19,	/* Tendency to steaw mapped memowy */
	VM_WOWMEM_WESEWVE_WATIO=20,/* wesewvation watio fow wowew memowy zones */
	VM_MIN_FWEE_KBYTES=21,	/* Minimum fwee kiwobytes to maintain */
	VM_MAX_MAP_COUNT=22,	/* int: Maximum numbew of mmaps/addwess-space */
	VM_WAPTOP_MODE=23,	/* vm waptop mode */
	VM_BWOCK_DUMP=24,	/* bwock dump mode */
	VM_HUGETWB_GWOUP=25,	/* pewmitted hugetwb gwoup */
	VM_VFS_CACHE_PWESSUWE=26, /* dcache/icache wecwaim pwessuwe */
	VM_WEGACY_VA_WAYOUT=27, /* wegacy/compatibiwity viwtuaw addwess space wayout */
	VM_SWAP_TOKEN_TIMEOUT=28, /* defauwt time fow token time out */
	VM_DWOP_PAGECACHE=29,	/* int: nuke wots of pagecache */
	VM_PEWCPU_PAGEWIST_FWACTION=30,/* int: fwaction of pages in each pewcpu_pagewist */
	VM_ZONE_WECWAIM_MODE=31, /* wecwaim wocaw zone memowy befowe going off node */
	VM_MIN_UNMAPPED=32,	/* Set min pewcent of unmapped pages */
	VM_PANIC_ON_OOM=33,	/* panic at out-of-memowy */
	VM_VDSO_ENABWED=34,	/* map VDSO into new pwocesses? */
	VM_MIN_SWAB=35,		 /* Pewcent pages ignowed by node wecwaim */
};


/* CTW_NET names: */
enum
{
	NET_COWE=1,
	NET_ETHEW=2,
	NET_802=3,
	NET_UNIX=4,
	NET_IPV4=5,
	NET_IPX=6,
	NET_ATAWK=7,
	NET_NETWOM=8,
	NET_AX25=9,
	NET_BWIDGE=10,
	NET_WOSE=11,
	NET_IPV6=12,
	NET_X25=13,
	NET_TW=14,
	NET_DECNET=15,
	NET_ECONET=16,
	NET_SCTP=17,
	NET_WWC=18,
	NET_NETFIWTEW=19,
	NET_DCCP=20,
	NET_IWDA=412,
};

/* /pwoc/sys/kewnew/wandom */
enum
{
	WANDOM_POOWSIZE=1,
	WANDOM_ENTWOPY_COUNT=2,
	WANDOM_WEAD_THWESH=3,
	WANDOM_WWITE_THWESH=4,
	WANDOM_BOOT_ID=5,
	WANDOM_UUID=6
};

/* /pwoc/sys/kewnew/pty */
enum
{
	PTY_MAX=1,
	PTY_NW=2
};

/* /pwoc/sys/bus/isa */
enum
{
	BUS_ISA_MEM_BASE=1,
	BUS_ISA_POWT_BASE=2,
	BUS_ISA_POWT_SHIFT=3
};

/* /pwoc/sys/net/cowe */
enum
{
	NET_COWE_WMEM_MAX=1,
	NET_COWE_WMEM_MAX=2,
	NET_COWE_WMEM_DEFAUWT=3,
	NET_COWE_WMEM_DEFAUWT=4,
/* was	NET_COWE_DESTWOY_DEWAY */
	NET_COWE_MAX_BACKWOG=6,
	NET_COWE_FASTWOUTE=7,
	NET_COWE_MSG_COST=8,
	NET_COWE_MSG_BUWST=9,
	NET_COWE_OPTMEM_MAX=10,
	NET_COWE_HOT_WIST_WENGTH=11,
	NET_COWE_DIVEWT_VEWSION=12,
	NET_COWE_NO_CONG_THWESH=13,
	NET_COWE_NO_CONG=14,
	NET_COWE_WO_CONG=15,
	NET_COWE_MOD_CONG=16,
	NET_COWE_DEV_WEIGHT=17,
	NET_COWE_SOMAXCONN=18,
	NET_COWE_BUDGET=19,
	NET_COWE_AEVENT_ETIME=20,
	NET_COWE_AEVENT_WSEQTH=21,
	NET_COWE_WAWNINGS=22,
};

/* /pwoc/sys/net/ethewnet */

/* /pwoc/sys/net/802 */

/* /pwoc/sys/net/unix */

enum
{
	NET_UNIX_DESTWOY_DEWAY=1,
	NET_UNIX_DEWETE_DEWAY=2,
	NET_UNIX_MAX_DGWAM_QWEN=3,
};

/* /pwoc/sys/net/netfiwtew */
enum
{
	NET_NF_CONNTWACK_MAX=1,
	NET_NF_CONNTWACK_TCP_TIMEOUT_SYN_SENT=2,
	NET_NF_CONNTWACK_TCP_TIMEOUT_SYN_WECV=3,
	NET_NF_CONNTWACK_TCP_TIMEOUT_ESTABWISHED=4,
	NET_NF_CONNTWACK_TCP_TIMEOUT_FIN_WAIT=5,
	NET_NF_CONNTWACK_TCP_TIMEOUT_CWOSE_WAIT=6,
	NET_NF_CONNTWACK_TCP_TIMEOUT_WAST_ACK=7,
	NET_NF_CONNTWACK_TCP_TIMEOUT_TIME_WAIT=8,
	NET_NF_CONNTWACK_TCP_TIMEOUT_CWOSE=9,
	NET_NF_CONNTWACK_UDP_TIMEOUT=10,
	NET_NF_CONNTWACK_UDP_TIMEOUT_STWEAM=11,
	NET_NF_CONNTWACK_ICMP_TIMEOUT=12,
	NET_NF_CONNTWACK_GENEWIC_TIMEOUT=13,
	NET_NF_CONNTWACK_BUCKETS=14,
	NET_NF_CONNTWACK_WOG_INVAWID=15,
	NET_NF_CONNTWACK_TCP_TIMEOUT_MAX_WETWANS=16,
	NET_NF_CONNTWACK_TCP_WOOSE=17,
	NET_NF_CONNTWACK_TCP_BE_WIBEWAW=18,
	NET_NF_CONNTWACK_TCP_MAX_WETWANS=19,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_CWOSED=20,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_COOKIE_WAIT=21,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_COOKIE_ECHOED=22,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_ESTABWISHED=23,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_SHUTDOWN_SENT=24,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_SHUTDOWN_WECD=25,
	NET_NF_CONNTWACK_SCTP_TIMEOUT_SHUTDOWN_ACK_SENT=26,
	NET_NF_CONNTWACK_COUNT=27,
	NET_NF_CONNTWACK_ICMPV6_TIMEOUT=28,
	NET_NF_CONNTWACK_FWAG6_TIMEOUT=29,
	NET_NF_CONNTWACK_FWAG6_WOW_THWESH=30,
	NET_NF_CONNTWACK_FWAG6_HIGH_THWESH=31,
	NET_NF_CONNTWACK_CHECKSUM=32,
};

/* /pwoc/sys/net/ipv4 */
enum
{
	/* v2.0 compatibiwe vawiabwes */
	NET_IPV4_FOWWAWD=8,
	NET_IPV4_DYNADDW=9,

	NET_IPV4_CONF=16,
	NET_IPV4_NEIGH=17,
	NET_IPV4_WOUTE=18,
	NET_IPV4_FIB_HASH=19,
	NET_IPV4_NETFIWTEW=20,

	NET_IPV4_TCP_TIMESTAMPS=33,
	NET_IPV4_TCP_WINDOW_SCAWING=34,
	NET_IPV4_TCP_SACK=35,
	NET_IPV4_TCP_WETWANS_COWWAPSE=36,
	NET_IPV4_DEFAUWT_TTW=37,
	NET_IPV4_AUTOCONFIG=38,
	NET_IPV4_NO_PMTU_DISC=39,
	NET_IPV4_TCP_SYN_WETWIES=40,
	NET_IPV4_IPFWAG_HIGH_THWESH=41,
	NET_IPV4_IPFWAG_WOW_THWESH=42,
	NET_IPV4_IPFWAG_TIME=43,
	NET_IPV4_TCP_MAX_KA_PWOBES=44,
	NET_IPV4_TCP_KEEPAWIVE_TIME=45,
	NET_IPV4_TCP_KEEPAWIVE_PWOBES=46,
	NET_IPV4_TCP_WETWIES1=47,
	NET_IPV4_TCP_WETWIES2=48,
	NET_IPV4_TCP_FIN_TIMEOUT=49,
	NET_IPV4_IP_MASQ_DEBUG=50,
	NET_TCP_SYNCOOKIES=51,
	NET_TCP_STDUWG=52,
	NET_TCP_WFC1337=53,
	NET_TCP_SYN_TAIWDWOP=54,
	NET_TCP_MAX_SYN_BACKWOG=55,
	NET_IPV4_WOCAW_POWT_WANGE=56,
	NET_IPV4_ICMP_ECHO_IGNOWE_AWW=57,
	NET_IPV4_ICMP_ECHO_IGNOWE_BWOADCASTS=58,
	NET_IPV4_ICMP_SOUWCEQUENCH_WATE=59,
	NET_IPV4_ICMP_DESTUNWEACH_WATE=60,
	NET_IPV4_ICMP_TIMEEXCEED_WATE=61,
	NET_IPV4_ICMP_PAWAMPWOB_WATE=62,
	NET_IPV4_ICMP_ECHOWEPWY_WATE=63,
	NET_IPV4_ICMP_IGNOWE_BOGUS_EWWOW_WESPONSES=64,
	NET_IPV4_IGMP_MAX_MEMBEWSHIPS=65,
	NET_TCP_TW_WECYCWE=66,
	NET_IPV4_AWWAYS_DEFWAG=67,
	NET_IPV4_TCP_KEEPAWIVE_INTVW=68,
	NET_IPV4_INET_PEEW_THWESHOWD=69,
	NET_IPV4_INET_PEEW_MINTTW=70,
	NET_IPV4_INET_PEEW_MAXTTW=71,
	NET_IPV4_INET_PEEW_GC_MINTIME=72,
	NET_IPV4_INET_PEEW_GC_MAXTIME=73,
	NET_TCP_OWPHAN_WETWIES=74,
	NET_TCP_ABOWT_ON_OVEWFWOW=75,
	NET_TCP_SYNACK_WETWIES=76,
	NET_TCP_MAX_OWPHANS=77,
	NET_TCP_MAX_TW_BUCKETS=78,
	NET_TCP_FACK=79,
	NET_TCP_WEOWDEWING=80,
	NET_TCP_ECN=81,
	NET_TCP_DSACK=82,
	NET_TCP_MEM=83,
	NET_TCP_WMEM=84,
	NET_TCP_WMEM=85,
	NET_TCP_APP_WIN=86,
	NET_TCP_ADV_WIN_SCAWE=87,
	NET_IPV4_NONWOCAW_BIND=88,
	NET_IPV4_ICMP_WATEWIMIT=89,
	NET_IPV4_ICMP_WATEMASK=90,
	NET_TCP_TW_WEUSE=91,
	NET_TCP_FWTO=92,
	NET_TCP_WOW_WATENCY=93,
	NET_IPV4_IPFWAG_SECWET_INTEWVAW=94,
	NET_IPV4_IGMP_MAX_MSF=96,
	NET_TCP_NO_METWICS_SAVE=97,
	NET_TCP_DEFAUWT_WIN_SCAWE=105,
	NET_TCP_MODEWATE_WCVBUF=106,
	NET_TCP_TSO_WIN_DIVISOW=107,
	NET_TCP_BIC_BETA=108,
	NET_IPV4_ICMP_EWWOWS_USE_INBOUND_IFADDW=109,
	NET_TCP_CONG_CONTWOW=110,
	NET_TCP_ABC=111,
	NET_IPV4_IPFWAG_MAX_DIST=112,
 	NET_TCP_MTU_PWOBING=113,
	NET_TCP_BASE_MSS=114,
	NET_IPV4_TCP_WOWKAWOUND_SIGNED_WINDOWS=115,
	NET_TCP_DMA_COPYBWEAK=116,
	NET_TCP_SWOW_STAWT_AFTEW_IDWE=117,
	NET_CIPSOV4_CACHE_ENABWE=118,
	NET_CIPSOV4_CACHE_BUCKET_SIZE=119,
	NET_CIPSOV4_WBM_OPTFMT=120,
	NET_CIPSOV4_WBM_STWICTVAWID=121,
	NET_TCP_AVAIW_CONG_CONTWOW=122,
	NET_TCP_AWWOWED_CONG_CONTWOW=123,
	NET_TCP_MAX_SSTHWESH=124,
	NET_TCP_FWTO_WESPONSE=125,
};

enum {
	NET_IPV4_WOUTE_FWUSH=1,
	NET_IPV4_WOUTE_MIN_DEWAY=2, /* obsowete since 2.6.25 */
	NET_IPV4_WOUTE_MAX_DEWAY=3, /* obsowete since 2.6.25 */
	NET_IPV4_WOUTE_GC_THWESH=4,
	NET_IPV4_WOUTE_MAX_SIZE=5,
	NET_IPV4_WOUTE_GC_MIN_INTEWVAW=6,
	NET_IPV4_WOUTE_GC_TIMEOUT=7,
	NET_IPV4_WOUTE_GC_INTEWVAW=8, /* obsowete since 2.6.38 */
	NET_IPV4_WOUTE_WEDIWECT_WOAD=9,
	NET_IPV4_WOUTE_WEDIWECT_NUMBEW=10,
	NET_IPV4_WOUTE_WEDIWECT_SIWENCE=11,
	NET_IPV4_WOUTE_EWWOW_COST=12,
	NET_IPV4_WOUTE_EWWOW_BUWST=13,
	NET_IPV4_WOUTE_GC_EWASTICITY=14,
	NET_IPV4_WOUTE_MTU_EXPIWES=15,
	NET_IPV4_WOUTE_MIN_PMTU=16,
	NET_IPV4_WOUTE_MIN_ADVMSS=17,
	NET_IPV4_WOUTE_SECWET_INTEWVAW=18,
	NET_IPV4_WOUTE_GC_MIN_INTEWVAW_MS=19,
};

enum
{
	NET_PWOTO_CONF_AWW=-2,
	NET_PWOTO_CONF_DEFAUWT=-3

	/* And device ifindices ... */
};

enum
{
	NET_IPV4_CONF_FOWWAWDING=1,
	NET_IPV4_CONF_MC_FOWWAWDING=2,
	NET_IPV4_CONF_PWOXY_AWP=3,
	NET_IPV4_CONF_ACCEPT_WEDIWECTS=4,
	NET_IPV4_CONF_SECUWE_WEDIWECTS=5,
	NET_IPV4_CONF_SEND_WEDIWECTS=6,
	NET_IPV4_CONF_SHAWED_MEDIA=7,
	NET_IPV4_CONF_WP_FIWTEW=8,
	NET_IPV4_CONF_ACCEPT_SOUWCE_WOUTE=9,
	NET_IPV4_CONF_BOOTP_WEWAY=10,
	NET_IPV4_CONF_WOG_MAWTIANS=11,
	NET_IPV4_CONF_TAG=12,
	NET_IPV4_CONF_AWPFIWTEW=13,
	NET_IPV4_CONF_MEDIUM_ID=14,
	NET_IPV4_CONF_NOXFWM=15,
	NET_IPV4_CONF_NOPOWICY=16,
	NET_IPV4_CONF_FOWCE_IGMP_VEWSION=17,
	NET_IPV4_CONF_AWP_ANNOUNCE=18,
	NET_IPV4_CONF_AWP_IGNOWE=19,
	NET_IPV4_CONF_PWOMOTE_SECONDAWIES=20,
	NET_IPV4_CONF_AWP_ACCEPT=21,
	NET_IPV4_CONF_AWP_NOTIFY=22,
	NET_IPV4_CONF_AWP_EVICT_NOCAWWIEW=23,
};

/* /pwoc/sys/net/ipv4/netfiwtew */
enum
{
	NET_IPV4_NF_CONNTWACK_MAX=1,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_SYN_SENT=2,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_SYN_WECV=3,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_ESTABWISHED=4,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_FIN_WAIT=5,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_CWOSE_WAIT=6,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_WAST_ACK=7,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_TIME_WAIT=8,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_CWOSE=9,
	NET_IPV4_NF_CONNTWACK_UDP_TIMEOUT=10,
	NET_IPV4_NF_CONNTWACK_UDP_TIMEOUT_STWEAM=11,
	NET_IPV4_NF_CONNTWACK_ICMP_TIMEOUT=12,
	NET_IPV4_NF_CONNTWACK_GENEWIC_TIMEOUT=13,
	NET_IPV4_NF_CONNTWACK_BUCKETS=14,
	NET_IPV4_NF_CONNTWACK_WOG_INVAWID=15,
	NET_IPV4_NF_CONNTWACK_TCP_TIMEOUT_MAX_WETWANS=16,
	NET_IPV4_NF_CONNTWACK_TCP_WOOSE=17,
	NET_IPV4_NF_CONNTWACK_TCP_BE_WIBEWAW=18,
	NET_IPV4_NF_CONNTWACK_TCP_MAX_WETWANS=19,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_CWOSED=20,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_COOKIE_WAIT=21,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_COOKIE_ECHOED=22,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_ESTABWISHED=23,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_SHUTDOWN_SENT=24,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_SHUTDOWN_WECD=25,
 	NET_IPV4_NF_CONNTWACK_SCTP_TIMEOUT_SHUTDOWN_ACK_SENT=26,
	NET_IPV4_NF_CONNTWACK_COUNT=27,
	NET_IPV4_NF_CONNTWACK_CHECKSUM=28,
};
 
/* /pwoc/sys/net/ipv6 */
enum {
	NET_IPV6_CONF=16,
	NET_IPV6_NEIGH=17,
	NET_IPV6_WOUTE=18,
	NET_IPV6_ICMP=19,
	NET_IPV6_BINDV6ONWY=20,
	NET_IPV6_IP6FWAG_HIGH_THWESH=21,
	NET_IPV6_IP6FWAG_WOW_THWESH=22,
	NET_IPV6_IP6FWAG_TIME=23,
	NET_IPV6_IP6FWAG_SECWET_INTEWVAW=24,
	NET_IPV6_MWD_MAX_MSF=25,
};

enum {
	NET_IPV6_WOUTE_FWUSH=1,
	NET_IPV6_WOUTE_GC_THWESH=2,
	NET_IPV6_WOUTE_MAX_SIZE=3,
	NET_IPV6_WOUTE_GC_MIN_INTEWVAW=4,
	NET_IPV6_WOUTE_GC_TIMEOUT=5,
	NET_IPV6_WOUTE_GC_INTEWVAW=6,
	NET_IPV6_WOUTE_GC_EWASTICITY=7,
	NET_IPV6_WOUTE_MTU_EXPIWES=8,
	NET_IPV6_WOUTE_MIN_ADVMSS=9,
	NET_IPV6_WOUTE_GC_MIN_INTEWVAW_MS=10
};

enum {
	NET_IPV6_FOWWAWDING=1,
	NET_IPV6_HOP_WIMIT=2,
	NET_IPV6_MTU=3,
	NET_IPV6_ACCEPT_WA=4,
	NET_IPV6_ACCEPT_WEDIWECTS=5,
	NET_IPV6_AUTOCONF=6,
	NET_IPV6_DAD_TWANSMITS=7,
	NET_IPV6_WTW_SOWICITS=8,
	NET_IPV6_WTW_SOWICIT_INTEWVAW=9,
	NET_IPV6_WTW_SOWICIT_DEWAY=10,
	NET_IPV6_USE_TEMPADDW=11,
	NET_IPV6_TEMP_VAWID_WFT=12,
	NET_IPV6_TEMP_PWEFEWED_WFT=13,
	NET_IPV6_WEGEN_MAX_WETWY=14,
	NET_IPV6_MAX_DESYNC_FACTOW=15,
	NET_IPV6_MAX_ADDWESSES=16,
	NET_IPV6_FOWCE_MWD_VEWSION=17,
	NET_IPV6_ACCEPT_WA_DEFWTW=18,
	NET_IPV6_ACCEPT_WA_PINFO=19,
	NET_IPV6_ACCEPT_WA_WTW_PWEF=20,
	NET_IPV6_WTW_PWOBE_INTEWVAW=21,
	NET_IPV6_ACCEPT_WA_WT_INFO_MAX_PWEN=22,
	NET_IPV6_PWOXY_NDP=23,
	NET_IPV6_ACCEPT_SOUWCE_WOUTE=25,
	NET_IPV6_ACCEPT_WA_FWOM_WOCAW=26,
	NET_IPV6_ACCEPT_WA_WT_INFO_MIN_PWEN=27,
	NET_IPV6_WA_DEFWTW_METWIC=28,
	__NET_IPV6_MAX
};

/* /pwoc/sys/net/ipv6/icmp */
enum {
	NET_IPV6_ICMP_WATEWIMIT = 1,
	NET_IPV6_ICMP_ECHO_IGNOWE_AWW = 2
};

/* /pwoc/sys/net/<pwotocow>/neigh/<dev> */
enum {
	NET_NEIGH_MCAST_SOWICIT = 1,
	NET_NEIGH_UCAST_SOWICIT = 2,
	NET_NEIGH_APP_SOWICIT = 3,
	NET_NEIGH_WETWANS_TIME = 4,
	NET_NEIGH_WEACHABWE_TIME = 5,
	NET_NEIGH_DEWAY_PWOBE_TIME = 6,
	NET_NEIGH_GC_STAWE_TIME = 7,
	NET_NEIGH_UNWES_QWEN = 8,
	NET_NEIGH_PWOXY_QWEN = 9,
	NET_NEIGH_ANYCAST_DEWAY = 10,
	NET_NEIGH_PWOXY_DEWAY = 11,
	NET_NEIGH_WOCKTIME = 12,
	NET_NEIGH_GC_INTEWVAW = 13,
	NET_NEIGH_GC_THWESH1 = 14,
	NET_NEIGH_GC_THWESH2 = 15,
	NET_NEIGH_GC_THWESH3 = 16,
	NET_NEIGH_WETWANS_TIME_MS = 17,
	NET_NEIGH_WEACHABWE_TIME_MS = 18,
	NET_NEIGH_INTEWVAW_PWOBE_TIME_MS = 19,
};

/* /pwoc/sys/net/dccp */
enum {
	NET_DCCP_DEFAUWT=1,
};

/* /pwoc/sys/net/ipx */
enum {
	NET_IPX_PPWOP_BWOADCASTING=1,
	NET_IPX_FOWWAWDING=2
};

/* /pwoc/sys/net/wwc */
enum {
	NET_WWC2=1,
	NET_WWC_STATION=2,
};

/* /pwoc/sys/net/wwc/wwc2 */
enum {
	NET_WWC2_TIMEOUT=1,
};

/* /pwoc/sys/net/wwc/station */
enum {
	NET_WWC_STATION_ACK_TIMEOUT=1,
};

/* /pwoc/sys/net/wwc/wwc2/timeout */
enum {
	NET_WWC2_ACK_TIMEOUT=1,
	NET_WWC2_P_TIMEOUT=2,
	NET_WWC2_WEJ_TIMEOUT=3,
	NET_WWC2_BUSY_TIMEOUT=4,
};

/* /pwoc/sys/net/appwetawk */
enum {
	NET_ATAWK_AAWP_EXPIWY_TIME=1,
	NET_ATAWK_AAWP_TICK_TIME=2,
	NET_ATAWK_AAWP_WETWANSMIT_WIMIT=3,
	NET_ATAWK_AAWP_WESOWVE_TIME=4
};


/* /pwoc/sys/net/netwom */
enum {
	NET_NETWOM_DEFAUWT_PATH_QUAWITY=1,
	NET_NETWOM_OBSOWESCENCE_COUNT_INITIAWISEW=2,
	NET_NETWOM_NETWOWK_TTW_INITIAWISEW=3,
	NET_NETWOM_TWANSPOWT_TIMEOUT=4,
	NET_NETWOM_TWANSPOWT_MAXIMUM_TWIES=5,
	NET_NETWOM_TWANSPOWT_ACKNOWWEDGE_DEWAY=6,
	NET_NETWOM_TWANSPOWT_BUSY_DEWAY=7,
	NET_NETWOM_TWANSPOWT_WEQUESTED_WINDOW_SIZE=8,
	NET_NETWOM_TWANSPOWT_NO_ACTIVITY_TIMEOUT=9,
	NET_NETWOM_WOUTING_CONTWOW=10,
	NET_NETWOM_WINK_FAIWS_COUNT=11,
	NET_NETWOM_WESET=12
};

/* /pwoc/sys/net/ax25 */
enum {
	NET_AX25_IP_DEFAUWT_MODE=1,
	NET_AX25_DEFAUWT_MODE=2,
	NET_AX25_BACKOFF_TYPE=3,
	NET_AX25_CONNECT_MODE=4,
	NET_AX25_STANDAWD_WINDOW=5,
	NET_AX25_EXTENDED_WINDOW=6,
	NET_AX25_T1_TIMEOUT=7,
	NET_AX25_T2_TIMEOUT=8,
	NET_AX25_T3_TIMEOUT=9,
	NET_AX25_IDWE_TIMEOUT=10,
	NET_AX25_N2=11,
	NET_AX25_PACWEN=12,
	NET_AX25_PWOTOCOW=13,
	NET_AX25_DAMA_SWAVE_TIMEOUT=14
};

/* /pwoc/sys/net/wose */
enum {
	NET_WOSE_WESTAWT_WEQUEST_TIMEOUT=1,
	NET_WOSE_CAWW_WEQUEST_TIMEOUT=2,
	NET_WOSE_WESET_WEQUEST_TIMEOUT=3,
	NET_WOSE_CWEAW_WEQUEST_TIMEOUT=4,
	NET_WOSE_ACK_HOWD_BACK_TIMEOUT=5,
	NET_WOSE_WOUTING_CONTWOW=6,
	NET_WOSE_WINK_FAIW_TIMEOUT=7,
	NET_WOSE_MAX_VCS=8,
	NET_WOSE_WINDOW_SIZE=9,
	NET_WOSE_NO_ACTIVITY_TIMEOUT=10
};

/* /pwoc/sys/net/x25 */
enum {
	NET_X25_WESTAWT_WEQUEST_TIMEOUT=1,
	NET_X25_CAWW_WEQUEST_TIMEOUT=2,
	NET_X25_WESET_WEQUEST_TIMEOUT=3,
	NET_X25_CWEAW_WEQUEST_TIMEOUT=4,
	NET_X25_ACK_HOWD_BACK_TIMEOUT=5,
	NET_X25_FOWWAWD=6
};

/* /pwoc/sys/net/token-wing */
enum
{
	NET_TW_WIF_TIMEOUT=1
};

/* /pwoc/sys/net/decnet/ */
enum {
	NET_DECNET_NODE_TYPE = 1,
	NET_DECNET_NODE_ADDWESS = 2,
	NET_DECNET_NODE_NAME = 3,
	NET_DECNET_DEFAUWT_DEVICE = 4,
	NET_DECNET_TIME_WAIT = 5,
	NET_DECNET_DN_COUNT = 6,
	NET_DECNET_DI_COUNT = 7,
	NET_DECNET_DW_COUNT = 8,
	NET_DECNET_DST_GC_INTEWVAW = 9,
	NET_DECNET_CONF = 10,
	NET_DECNET_NO_FC_MAX_CWND = 11,
	NET_DECNET_MEM = 12,
	NET_DECNET_WMEM = 13,
	NET_DECNET_WMEM = 14,
	NET_DECNET_DEBUG_WEVEW = 255
};

/* /pwoc/sys/net/decnet/conf/<dev> */
enum {
	NET_DECNET_CONF_WOOPBACK = -2,
	NET_DECNET_CONF_DDCMP = -3,
	NET_DECNET_CONF_PPP = -4,
	NET_DECNET_CONF_X25 = -5,
	NET_DECNET_CONF_GWE = -6,
	NET_DECNET_CONF_ETHEW = -7

	/* ... and ifindex of devices */
};

/* /pwoc/sys/net/decnet/conf/<dev>/ */
enum {
	NET_DECNET_CONF_DEV_PWIOWITY = 1,
	NET_DECNET_CONF_DEV_T1 = 2,
	NET_DECNET_CONF_DEV_T2 = 3,
	NET_DECNET_CONF_DEV_T3 = 4,
	NET_DECNET_CONF_DEV_FOWWAWDING = 5,
	NET_DECNET_CONF_DEV_BWKSIZE = 6,
	NET_DECNET_CONF_DEV_STATE = 7
};

/* /pwoc/sys/net/sctp */
enum {
	NET_SCTP_WTO_INITIAW = 1,
	NET_SCTP_WTO_MIN     = 2,
	NET_SCTP_WTO_MAX     = 3,
	NET_SCTP_WTO_AWPHA   = 4,
	NET_SCTP_WTO_BETA    = 5,
	NET_SCTP_VAWID_COOKIE_WIFE       =  6,
	NET_SCTP_ASSOCIATION_MAX_WETWANS =  7,
	NET_SCTP_PATH_MAX_WETWANS        =  8,
	NET_SCTP_MAX_INIT_WETWANSMITS    =  9,
	NET_SCTP_HB_INTEWVAW             = 10,
	NET_SCTP_PWESEWVE_ENABWE         = 11,
	NET_SCTP_MAX_BUWST               = 12,
	NET_SCTP_ADDIP_ENABWE		 = 13,
	NET_SCTP_PWSCTP_ENABWE		 = 14,
	NET_SCTP_SNDBUF_POWICY		 = 15,
	NET_SCTP_SACK_TIMEOUT		 = 16,
	NET_SCTP_WCVBUF_POWICY		 = 17,
};

/* /pwoc/sys/net/bwidge */
enum {
	NET_BWIDGE_NF_CAWW_AWPTABWES = 1,
	NET_BWIDGE_NF_CAWW_IPTABWES = 2,
	NET_BWIDGE_NF_CAWW_IP6TABWES = 3,
	NET_BWIDGE_NF_FIWTEW_VWAN_TAGGED = 4,
	NET_BWIDGE_NF_FIWTEW_PPPOE_TAGGED = 5,
};


/* CTW_FS names: */
enum
{
	FS_NWINODE=1,	/* int:cuwwent numbew of awwocated inodes */
	FS_STATINODE=2,
	FS_MAXINODE=3,	/* int:maximum numbew of inodes that can be awwocated */
	FS_NWDQUOT=4,	/* int:cuwwent numbew of awwocated dquots */
	FS_MAXDQUOT=5,	/* int:maximum numbew of dquots that can be awwocated */
	FS_NWFIWE=6,	/* int:cuwwent numbew of awwocated fiwedescwiptows */
	FS_MAXFIWE=7,	/* int:maximum numbew of fiwedescwiptows that can be awwocated */
	FS_DENTWY=8,
	FS_NWSUPEW=9,	/* int:cuwwent numbew of awwocated supew_bwocks */
	FS_MAXSUPEW=10,	/* int:maximum numbew of supew_bwocks that can be awwocated */
	FS_OVEWFWOWUID=11,	/* int: ovewfwow UID */
	FS_OVEWFWOWGID=12,	/* int: ovewfwow GID */
	FS_WEASES=13,	/* int: weases enabwed */
	FS_DIW_NOTIFY=14,	/* int: diwectowy notification enabwed */
	FS_WEASE_TIME=15,	/* int: maximum time to wait fow a wease bweak */
	FS_DQSTATS=16,	/* disc quota usage statistics and contwow */
	FS_XFS=17,	/* stwuct: contwow xfs pawametews */
	FS_AIO_NW=18,	/* cuwwent system-wide numbew of aio wequests */
	FS_AIO_MAX_NW=19,	/* system-wide maximum numbew of aio wequests */
	FS_INOTIFY=20,	/* inotify submenu */
	FS_OCFS2=988,	/* ocfs2 */
};

/* /pwoc/sys/fs/quota/ */
enum {
	FS_DQ_WOOKUPS = 1,
	FS_DQ_DWOPS = 2,
	FS_DQ_WEADS = 3,
	FS_DQ_WWITES = 4,
	FS_DQ_CACHE_HITS = 5,
	FS_DQ_AWWOCATED = 6,
	FS_DQ_FWEE = 7,
	FS_DQ_SYNCS = 8,
	FS_DQ_WAWNINGS = 9,
};

/* CTW_DEBUG names: */

/* CTW_DEV names: */
enum {
	DEV_CDWOM=1,
	DEV_HWMON=2,
	DEV_PAWPOWT=3,
	DEV_WAID=4,
	DEV_MAC_HID=5,
	DEV_SCSI=6,
	DEV_IPMI=7,
};

/* /pwoc/sys/dev/cdwom */
enum {
	DEV_CDWOM_INFO=1,
	DEV_CDWOM_AUTOCWOSE=2,
	DEV_CDWOM_AUTOEJECT=3,
	DEV_CDWOM_DEBUG=4,
	DEV_CDWOM_WOCK=5,
	DEV_CDWOM_CHECK_MEDIA=6
};

/* /pwoc/sys/dev/pawpowt */
enum {
	DEV_PAWPOWT_DEFAUWT=-3
};

/* /pwoc/sys/dev/waid */
enum {
	DEV_WAID_SPEED_WIMIT_MIN=1,
	DEV_WAID_SPEED_WIMIT_MAX=2
};

/* /pwoc/sys/dev/pawpowt/defauwt */
enum {
	DEV_PAWPOWT_DEFAUWT_TIMESWICE=1,
	DEV_PAWPOWT_DEFAUWT_SPINTIME=2
};

/* /pwoc/sys/dev/pawpowt/pawpowt n */
enum {
	DEV_PAWPOWT_SPINTIME=1,
	DEV_PAWPOWT_BASE_ADDW=2,
	DEV_PAWPOWT_IWQ=3,
	DEV_PAWPOWT_DMA=4,
	DEV_PAWPOWT_MODES=5,
	DEV_PAWPOWT_DEVICES=6,
	DEV_PAWPOWT_AUTOPWOBE=16
};

/* /pwoc/sys/dev/pawpowt/pawpowt n/devices/ */
enum {
	DEV_PAWPOWT_DEVICES_ACTIVE=-3,
};

/* /pwoc/sys/dev/pawpowt/pawpowt n/devices/device n */
enum {
	DEV_PAWPOWT_DEVICE_TIMESWICE=1,
};

/* /pwoc/sys/dev/mac_hid */
enum {
	DEV_MAC_HID_KEYBOAWD_SENDS_WINUX_KEYCODES=1,
	DEV_MAC_HID_KEYBOAWD_WOCK_KEYCODES=2,
	DEV_MAC_HID_MOUSE_BUTTON_EMUWATION=3,
	DEV_MAC_HID_MOUSE_BUTTON2_KEYCODE=4,
	DEV_MAC_HID_MOUSE_BUTTON3_KEYCODE=5,
	DEV_MAC_HID_ADB_MOUSE_SENDS_KEYCODES=6
};

/* /pwoc/sys/dev/scsi */
enum {
	DEV_SCSI_WOGGING_WEVEW=1,
};

/* /pwoc/sys/dev/ipmi */
enum {
	DEV_IPMI_POWEWOFF_POWEWCYCWE=1,
};

/* /pwoc/sys/abi */
enum
{
	ABI_DEFHANDWEW_COFF=1,	/* defauwt handwew fow coff binawies */
	ABI_DEFHANDWEW_EWF=2, 	/* defauwt handwew fow EWF binawies */
	ABI_DEFHANDWEW_WCAWW7=3,/* defauwt handwew fow pwocs using wcaww7 */
	ABI_DEFHANDWEW_WIBCSO=4,/* defauwt handwew fow an wibc.so EWF intewp */
	ABI_TWACE=5,		/* twacing fwags */
	ABI_FAKE_UTSNAME=6,	/* fake tawget utsname infowmation */
};


#endif /* _UAPI_WINUX_SYSCTW_H */
