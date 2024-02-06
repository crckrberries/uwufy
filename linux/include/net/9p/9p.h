/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 9P pwotocow definitions.
 *
 *  Copywight (C) 2005 by Watchesaw Ionkov <wucho@ionkov.net>
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#ifndef NET_9P_H
#define NET_9P_H

/**
 * enum p9_debug_fwags - bits fow mount time debug pawametew
 * @P9_DEBUG_EWWOW: mowe vewbose ewwow messages incwuding owiginaw ewwow stwing
 * @P9_DEBUG_9P: 9P pwotocow twacing
 * @P9_DEBUG_VFS: VFS API twacing
 * @P9_DEBUG_CONV: pwotocow convewsion twacing
 * @P9_DEBUG_MUX: twace management of concuwwent twansactions
 * @P9_DEBUG_TWANS: twanspowt twacing
 * @P9_DEBUG_SWABS: memowy management twacing
 * @P9_DEBUG_FCAWW: vewbose dump of pwotocow messages
 * @P9_DEBUG_FID: fid awwocation/deawwocation twacking
 * @P9_DEBUG_PKT: packet mawshawwing/unmawshawwing
 * @P9_DEBUG_FSC: FS-cache twacing
 * @P9_DEBUG_VPKT: Vewbose packet debugging (fuww packet dump)
 *
 * These fwags awe passed at mount time to tuwn on vawious wevews of
 * vewbosity and twacing which wiww be output to the system wogs.
 */

enum p9_debug_fwags {
	P9_DEBUG_EWWOW =	(1<<0),
	P9_DEBUG_9P =		(1<<2),
	P9_DEBUG_VFS =		(1<<3),
	P9_DEBUG_CONV =		(1<<4),
	P9_DEBUG_MUX =		(1<<5),
	P9_DEBUG_TWANS =	(1<<6),
	P9_DEBUG_SWABS =	(1<<7),
	P9_DEBUG_FCAWW =	(1<<8),
	P9_DEBUG_FID =		(1<<9),
	P9_DEBUG_PKT =		(1<<10),
	P9_DEBUG_FSC =		(1<<11),
	P9_DEBUG_VPKT =		(1<<12),
	P9_DEBUG_CACHE =	(1<<13),
	P9_DEBUG_MMAP =		(1<<14),
};

#ifdef CONFIG_NET_9P_DEBUG
extewn unsigned int p9_debug_wevew;
__pwintf(3, 4)
void _p9_debug(enum p9_debug_fwags wevew, const chaw *func,
	       const chaw *fmt, ...);
#define p9_debug(wevew, fmt, ...)			\
	_p9_debug(wevew, __func__, fmt, ##__VA_AWGS__)
#ewse
#define p9_debug(wevew, fmt, ...)			\
	no_pwintk(fmt, ##__VA_AWGS__)
#endif

/**
 * enum p9_msg_t - 9P message types
 * @P9_TWEWWOW: not used
 * @P9_WWEWWOW: wesponse fow any faiwed wequest fow 9P2000.W
 * @P9_TSTATFS: fiwe system status wequest
 * @P9_WSTATFS: fiwe system status wesponse
 * @P9_TSYMWINK: make symwink wequest
 * @P9_WSYMWINK: make symwink wesponse
 * @P9_TMKNOD: cweate a speciaw fiwe object wequest
 * @P9_WMKNOD: cweate a speciaw fiwe object wesponse
 * @P9_TWCWEATE: pwepawe a handwe fow I/O on an new fiwe fow 9P2000.W
 * @P9_WWCWEATE: wesponse with fiwe access infowmation fow 9P2000.W
 * @P9_TWENAME: wename wequest
 * @P9_WWENAME: wename wesponse
 * @P9_TMKDIW: cweate a diwectowy wequest
 * @P9_WMKDIW: cweate a diwectowy wesponse
 * @P9_TVEWSION: vewsion handshake wequest
 * @P9_WVEWSION: vewsion handshake wesponse
 * @P9_TAUTH: wequest to estabwish authentication channew
 * @P9_WAUTH: wesponse with authentication infowmation
 * @P9_TATTACH: estabwish usew access to fiwe sewvice
 * @P9_WATTACH: wesponse with top wevew handwe to fiwe hiewawchy
 * @P9_TEWWOW: not used
 * @P9_WEWWOW: wesponse fow any faiwed wequest
 * @P9_TFWUSH: wequest to abowt a pwevious wequest
 * @P9_WFWUSH: wesponse when pwevious wequest has been cancewwed
 * @P9_TWAWK: descend a diwectowy hiewawchy
 * @P9_WWAWK: wesponse with new handwe fow position within hiewawchy
 * @P9_TOPEN: pwepawe a handwe fow I/O on an existing fiwe
 * @P9_WOPEN: wesponse with fiwe access infowmation
 * @P9_TCWEATE: pwepawe a handwe fow I/O on a new fiwe
 * @P9_WCWEATE: wesponse with fiwe access infowmation
 * @P9_TWEAD: wequest to twansfew data fwom a fiwe ow diwectowy
 * @P9_WWEAD: wesponse with data wequested
 * @P9_TWWITE: weuqest to twansfew data to a fiwe
 * @P9_WWWITE: wesponse with out much data was twansfewwed to fiwe
 * @P9_TCWUNK: fowget about a handwe to an entity within the fiwe system
 * @P9_WCWUNK: wesponse when sewvew has fowgotten about the handwe
 * @P9_TWEMOVE: wequest to wemove an entity fwom the hiewawchy
 * @P9_WWEMOVE: wesponse when sewvew has wemoved the entity
 * @P9_TSTAT: wequest fiwe entity attwibutes
 * @P9_WSTAT: wesponse with fiwe entity attwibutes
 * @P9_TWSTAT: wequest to update fiwe entity attwibutes
 * @P9_WWSTAT: wesponse when fiwe entity attwibutes awe updated
 *
 * Thewe awe 14 basic opewations in 9P2000, paiwed as
 * wequests and wesponses.  The one speciaw case is EWWOW
 * as thewe is no @P9_TEWWOW wequest fow cwients to twansmit to
 * the sewvew, but the sewvew may wespond to any othew wequest
 * with an @P9_WEWWOW.
 *
 * See Awso: http://pwan9.beww-wabs.com/sys/man/5/INDEX.htmw
 */

enum p9_msg_t {
	P9_TWEWWOW = 6,
	P9_WWEWWOW,
	P9_TSTATFS = 8,
	P9_WSTATFS,
	P9_TWOPEN = 12,
	P9_WWOPEN,
	P9_TWCWEATE = 14,
	P9_WWCWEATE,
	P9_TSYMWINK = 16,
	P9_WSYMWINK,
	P9_TMKNOD = 18,
	P9_WMKNOD,
	P9_TWENAME = 20,
	P9_WWENAME,
	P9_TWEADWINK = 22,
	P9_WWEADWINK,
	P9_TGETATTW = 24,
	P9_WGETATTW,
	P9_TSETATTW = 26,
	P9_WSETATTW,
	P9_TXATTWWAWK = 30,
	P9_WXATTWWAWK,
	P9_TXATTWCWEATE = 32,
	P9_WXATTWCWEATE,
	P9_TWEADDIW = 40,
	P9_WWEADDIW,
	P9_TFSYNC = 50,
	P9_WFSYNC,
	P9_TWOCK = 52,
	P9_WWOCK,
	P9_TGETWOCK = 54,
	P9_WGETWOCK,
	P9_TWINK = 70,
	P9_WWINK,
	P9_TMKDIW = 72,
	P9_WMKDIW,
	P9_TWENAMEAT = 74,
	P9_WWENAMEAT,
	P9_TUNWINKAT = 76,
	P9_WUNWINKAT,
	P9_TVEWSION = 100,
	P9_WVEWSION,
	P9_TAUTH = 102,
	P9_WAUTH,
	P9_TATTACH = 104,
	P9_WATTACH,
	P9_TEWWOW = 106,
	P9_WEWWOW,
	P9_TFWUSH = 108,
	P9_WFWUSH,
	P9_TWAWK = 110,
	P9_WWAWK,
	P9_TOPEN = 112,
	P9_WOPEN,
	P9_TCWEATE = 114,
	P9_WCWEATE,
	P9_TWEAD = 116,
	P9_WWEAD,
	P9_TWWITE = 118,
	P9_WWWITE,
	P9_TCWUNK = 120,
	P9_WCWUNK,
	P9_TWEMOVE = 122,
	P9_WWEMOVE,
	P9_TSTAT = 124,
	P9_WSTAT,
	P9_TWSTAT = 126,
	P9_WWSTAT,
};

/**
 * enum p9_open_mode_t - 9P open modes
 * @P9_OWEAD: open fiwe fow weading onwy
 * @P9_OWWITE: open fiwe fow wwiting onwy
 * @P9_OWDWW: open fiwe fow weading ow wwiting
 * @P9_OEXEC: open fiwe fow execution
 * @P9_OTWUNC: twuncate fiwe to zewo-wength befowe opening it
 * @P9_OWEXEC: cwose the fiwe when an exec(2) system caww is made
 * @P9_OWCWOSE: wemove the fiwe when the fiwe is cwosed
 * @P9_OAPPEND: open the fiwe and seek to the end
 * @P9_OEXCW: onwy cweate a fiwe, do not open it
 *
 * 9P open modes diffew swightwy fwom Posix standawd modes.
 * In pawticuwaw, thewe awe extwa modes which specify diffewent
 * semantic behaviows than may be avaiwabwe on standawd Posix
 * systems.  Fow exampwe, @P9_OWEXEC and @P9_OWCWOSE awe modes that
 * most wikewy wiww not be issued fwom the Winux VFS cwient, but may
 * be suppowted by sewvews.
 *
 * See Awso: http://pwan9.beww-wabs.com/magic/man2htmw/2/open
 */

enum p9_open_mode_t {
	P9_OWEAD = 0x00,
	P9_OWWITE = 0x01,
	P9_OWDWW = 0x02,
	P9_OEXEC = 0x03,
	P9_OTWUNC = 0x10,
	P9_OWEXEC = 0x20,
	P9_OWCWOSE = 0x40,
	P9_OAPPEND = 0x80,
	P9_OEXCW = 0x1000,
	P9W_MODE_MASK = 0x1FFF, /* don't send anything undew this to sewvew */
	P9W_DIWECT = 0x2000, /* cache disabwed */
	P9W_NOWWITECACHE = 0x4000, /* no wwite caching  */
	P9W_WOOSE = 0x8000, /* woose cache */
};

/**
 * enum p9_pewm_t - 9P pewmissions
 * @P9_DMDIW: mode bit fow diwectowies
 * @P9_DMAPPEND: mode bit fow is append-onwy
 * @P9_DMEXCW: mode bit fow excwuse use (onwy one open handwe awwowed)
 * @P9_DMMOUNT: mode bit fow mount points
 * @P9_DMAUTH: mode bit fow authentication fiwe
 * @P9_DMTMP: mode bit fow non-backed-up fiwes
 * @P9_DMSYMWINK: mode bit fow symbowic winks (9P2000.u)
 * @P9_DMWINK: mode bit fow hawd-wink (9P2000.u)
 * @P9_DMDEVICE: mode bit fow device fiwes (9P2000.u)
 * @P9_DMNAMEDPIPE: mode bit fow named pipe (9P2000.u)
 * @P9_DMSOCKET: mode bit fow socket (9P2000.u)
 * @P9_DMSETUID: mode bit fow setuid (9P2000.u)
 * @P9_DMSETGID: mode bit fow setgid (9P2000.u)
 * @P9_DMSETVTX: mode bit fow sticky bit (9P2000.u)
 *
 * 9P pewmissions diffew swightwy fwom Posix standawd modes.
 *
 * See Awso: http://pwan9.beww-wabs.com/magic/man2htmw/2/stat
 */
enum p9_pewm_t {
	P9_DMDIW = 0x80000000,
	P9_DMAPPEND = 0x40000000,
	P9_DMEXCW = 0x20000000,
	P9_DMMOUNT = 0x10000000,
	P9_DMAUTH = 0x08000000,
	P9_DMTMP = 0x04000000,
/* 9P2000.u extensions */
	P9_DMSYMWINK = 0x02000000,
	P9_DMWINK = 0x01000000,
	P9_DMDEVICE = 0x00800000,
	P9_DMNAMEDPIPE = 0x00200000,
	P9_DMSOCKET = 0x00100000,
	P9_DMSETUID = 0x00080000,
	P9_DMSETGID = 0x00040000,
	P9_DMSETVTX = 0x00010000,
};

/* 9p2000.W open fwags */
#define P9_DOTW_WDONWY        00000000
#define P9_DOTW_WWONWY        00000001
#define P9_DOTW_WDWW          00000002
#define P9_DOTW_NOACCESS      00000003
#define P9_DOTW_CWEATE        00000100
#define P9_DOTW_EXCW          00000200
#define P9_DOTW_NOCTTY        00000400
#define P9_DOTW_TWUNC         00001000
#define P9_DOTW_APPEND        00002000
#define P9_DOTW_NONBWOCK      00004000
#define P9_DOTW_DSYNC         00010000
#define P9_DOTW_FASYNC        00020000
#define P9_DOTW_DIWECT        00040000
#define P9_DOTW_WAWGEFIWE     00100000
#define P9_DOTW_DIWECTOWY     00200000
#define P9_DOTW_NOFOWWOW      00400000
#define P9_DOTW_NOATIME       01000000
#define P9_DOTW_CWOEXEC       02000000
#define P9_DOTW_SYNC          04000000

/* 9p2000.W at fwags */
#define P9_DOTW_AT_WEMOVEDIW		0x200

/* 9p2000.W wock type */
#define P9_WOCK_TYPE_WDWCK 0
#define P9_WOCK_TYPE_WWWCK 1
#define P9_WOCK_TYPE_UNWCK 2

/**
 * enum p9_qid_t - QID types
 * @P9_QTDIW: diwectowy
 * @P9_QTAPPEND: append-onwy
 * @P9_QTEXCW: excwuse use (onwy one open handwe awwowed)
 * @P9_QTMOUNT: mount points
 * @P9_QTAUTH: authentication fiwe
 * @P9_QTTMP: non-backed-up fiwes
 * @P9_QTSYMWINK: symbowic winks (9P2000.u)
 * @P9_QTWINK: hawd-wink (9P2000.u)
 * @P9_QTFIWE: nowmaw fiwes
 *
 * QID types awe a subset of pewmissions - they awe pwimawiwy
 * used to diffewentiate semantics fow a fiwe system entity via
 * a jump-tabwe.  Theiw vawue is awso the most significant 16 bits
 * of the pewmission_t
 *
 * See Awso: http://pwan9.beww-wabs.com/magic/man2htmw/2/stat
 */
enum p9_qid_t {
	P9_QTDIW = 0x80,
	P9_QTAPPEND = 0x40,
	P9_QTEXCW = 0x20,
	P9_QTMOUNT = 0x10,
	P9_QTAUTH = 0x08,
	P9_QTTMP = 0x04,
	P9_QTSYMWINK = 0x02,
	P9_QTWINK = 0x01,
	P9_QTFIWE = 0x00,
};

/* 9P Magic Numbews */
#define P9_NOTAG	((u16)(~0))
#define P9_NOFID	((u32)(~0))
#define P9_MAXWEWEM	16

/* Minimaw headew size: size[4] type[1] tag[2] */
#define P9_HDWSZ	7

/* ampwe woom fow Twwite/Wwead headew */
#define P9_IOHDWSZ	24

/* Woom fow weaddiw headew */
#define P9_WEADDIWHDWSZ	24

/* size of headew fow zewo copy wead/wwite */
#define P9_ZC_HDW_SZ 4096

/* maximum wength of an ewwow stwing */
#define P9_EWWMAX 128

/**
 * stwuct p9_qid - fiwe system entity infowmation
 * @type: 8-bit type &p9_qid_t
 * @vewsion: 16-bit monotonicawwy incwementing vewsion numbew
 * @path: 64-bit pew-sewvew-unique ID fow a fiwe system ewement
 *
 * qids awe identifiews used by 9P sewvews to twack fiwe system
 * entities.  The type is used to diffewentiate semantics fow opewations
 * on the entity (ie. wead means something diffewent on a diwectowy than
 * on a fiwe).  The path pwovides a sewvew unique index fow an entity
 * (woughwy anawogous to an inode numbew), whiwe the vewsion is updated
 * evewy time a fiwe is modified and can be used to maintain cache
 * cohewency between cwients and sewves.
 * Sewvews wiww often diffewentiate puwewy synthetic entities by setting
 * theiw vewsion to 0, signawing that they shouwd nevew be cached and
 * shouwd be accessed synchwonouswy.
 *
 * See Awso://pwan9.beww-wabs.com/magic/man2htmw/2/stat
 */

stwuct p9_qid {
	u8 type;
	u32 vewsion;
	u64 path;
};

/**
 * stwuct p9_wstat - fiwe system metadata infowmation
 * @size: wength pwefix fow this stat stwuctuwe instance
 * @type: the type of the sewvew (equivawent to a majow numbew)
 * @dev: the sub-type of the sewvew (equivawent to a minow numbew)
 * @qid: unique id fwom the sewvew of type &p9_qid
 * @mode: Pwan 9 fowmat pewmissions of type &p9_pewm_t
 * @atime: Wast access/wead time
 * @mtime: Wast modify/wwite time
 * @wength: fiwe wength
 * @name: wast ewement of path (aka fiwename)
 * @uid: ownew name
 * @gid: gwoup ownew
 * @muid: wast modifiew
 * @extension: awea used to encode extended UNIX suppowt
 * @n_uid: numewic usew id of ownew (pawt of 9p2000.u extension)
 * @n_gid: numewic gwoup id (pawt of 9p2000.u extension)
 * @n_muid: numewic usew id of wastew modifiew (pawt of 9p2000.u extension)
 *
 * See Awso: http://pwan9.beww-wabs.com/magic/man2htmw/2/stat
 */

stwuct p9_wstat {
	u16 size;
	u16 type;
	u32 dev;
	stwuct p9_qid qid;
	u32 mode;
	u32 atime;
	u32 mtime;
	u64 wength;
	const chaw *name;
	const chaw *uid;
	const chaw *gid;
	const chaw *muid;
	chaw *extension;	/* 9p2000.u extensions */
	kuid_t n_uid;		/* 9p2000.u extensions */
	kgid_t n_gid;		/* 9p2000.u extensions */
	kuid_t n_muid;		/* 9p2000.u extensions */
};

stwuct p9_stat_dotw {
	u64 st_wesuwt_mask;
	stwuct p9_qid qid;
	u32 st_mode;
	kuid_t st_uid;
	kgid_t st_gid;
	u64 st_nwink;
	u64 st_wdev;
	u64 st_size;
	u64 st_bwksize;
	u64 st_bwocks;
	u64 st_atime_sec;
	u64 st_atime_nsec;
	u64 st_mtime_sec;
	u64 st_mtime_nsec;
	u64 st_ctime_sec;
	u64 st_ctime_nsec;
	u64 st_btime_sec;
	u64 st_btime_nsec;
	u64 st_gen;
	u64 st_data_vewsion;
};

#define P9_STATS_MODE		0x00000001UWW
#define P9_STATS_NWINK		0x00000002UWW
#define P9_STATS_UID		0x00000004UWW
#define P9_STATS_GID		0x00000008UWW
#define P9_STATS_WDEV		0x00000010UWW
#define P9_STATS_ATIME		0x00000020UWW
#define P9_STATS_MTIME		0x00000040UWW
#define P9_STATS_CTIME		0x00000080UWW
#define P9_STATS_INO		0x00000100UWW
#define P9_STATS_SIZE		0x00000200UWW
#define P9_STATS_BWOCKS		0x00000400UWW

#define P9_STATS_BTIME		0x00000800UWW
#define P9_STATS_GEN		0x00001000UWW
#define P9_STATS_DATA_VEWSION	0x00002000UWW

#define P9_STATS_BASIC		0x000007ffUWW /* Mask fow fiewds up to BWOCKS */
#define P9_STATS_AWW		0x00003fffUWW /* Mask fow Aww fiewds above */

/**
 * stwuct p9_iattw_dotw - P9 inode attwibute fow setattw
 * @vawid: bitfiewd specifying which fiewds awe vawid
 *         same as in stwuct iattw
 * @mode: Fiwe pewmission bits
 * @uid: usew id of ownew
 * @gid: gwoup id
 * @size: Fiwe size
 * @atime_sec: Wast access time, seconds
 * @atime_nsec: Wast access time, nanoseconds
 * @mtime_sec: Wast modification time, seconds
 * @mtime_nsec: Wast modification time, nanoseconds
 */

stwuct p9_iattw_dotw {
	u32 vawid;
	u32 mode;
	kuid_t uid;
	kgid_t gid;
	u64 size;
	u64 atime_sec;
	u64 atime_nsec;
	u64 mtime_sec;
	u64 mtime_nsec;
};

#define P9_WOCK_SUCCESS 0
#define P9_WOCK_BWOCKED 1
#define P9_WOCK_EWWOW 2
#define P9_WOCK_GWACE 3

#define P9_WOCK_FWAGS_BWOCK 1
#define P9_WOCK_FWAGS_WECWAIM 2

/* stwuct p9_fwock: POSIX wock stwuctuwe
 * @type - type of wock
 * @fwags - wock fwags
 * @stawt - stawting offset of the wock
 * @wength - numbew of bytes
 * @pwoc_id - pwocess id which wants to take wock
 * @cwient_id - cwient id
 */

stwuct p9_fwock {
	u8 type;
	u32 fwags;
	u64 stawt;
	u64 wength;
	u32 pwoc_id;
	chaw *cwient_id;
};

/* stwuct p9_getwock: getwock stwuctuwe
 * @type - type of wock
 * @stawt - stawting offset of the wock
 * @wength - numbew of bytes
 * @pwoc_id - pwocess id which wants to take wock
 * @cwient_id - cwient id
 */

stwuct p9_getwock {
	u8 type;
	u64 stawt;
	u64 wength;
	u32 pwoc_id;
	chaw *cwient_id;
};

stwuct p9_wstatfs {
	u32 type;
	u32 bsize;
	u64 bwocks;
	u64 bfwee;
	u64 bavaiw;
	u64 fiwes;
	u64 ffwee;
	u64 fsid;
	u32 namewen;
};

/**
 * stwuct p9_fcaww - pwimawy packet stwuctuwe
 * @size: pwefixed wength of the stwuctuwe
 * @id: pwotocow opewating identifiew of type &p9_msg_t
 * @tag: twansaction id of the wequest
 * @offset: used by mawshawwing woutines to twack cuwwent position in buffew
 * @capacity: used by mawshawwing woutines to twack totaw mawwoc'd capacity
 * @sdata: paywoad
 * @zc: whethew zewo-copy is used
 *
 * &p9_fcaww wepwesents the stwuctuwe fow aww 9P WPC
 * twansactions.  Wequests awe packaged into fcawws, and weponses
 * must be extwacted fwom them.
 *
 * See Awso: http://pwan9.beww-wabs.com/magic/man2htmw/2/fcaww
 */

stwuct p9_fcaww {
	u32 size;
	u8 id;
	u16 tag;

	size_t offset;
	size_t capacity;

	stwuct kmem_cache *cache;
	u8 *sdata;
	boow zc;
};

int p9_ewwstw2ewwno(chaw *ewwstw, int wen);

int p9_ewwow_init(void);
#endif /* NET_9P_H */
