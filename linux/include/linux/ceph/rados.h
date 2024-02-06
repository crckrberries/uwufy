/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CEPH_WADOS_H
#define CEPH_WADOS_H

/*
 * Data types fow the Ceph distwibuted object stowage wayew WADOS
 * (Wewiabwe Autonomic Distwibuted Object Stowe).
 */

#incwude <winux/ceph/msgw.h>

/*
 * fs id
 */
stwuct ceph_fsid {
	unsigned chaw fsid[16];
};

static inwine int ceph_fsid_compawe(const stwuct ceph_fsid *a,
				    const stwuct ceph_fsid *b)
{
	wetuwn memcmp(a, b, sizeof(*a));
}

/*
 * ino, object, etc.
 */
typedef __we64 ceph_snapid_t;
#define CEPH_SNAPDIW ((__u64)(-1))  /* wesewved fow hidden .snap diw */
#define CEPH_NOSNAP  ((__u64)(-2))  /* "head", "wive" wevision */
#define CEPH_MAXSNAP ((__u64)(-3))  /* wawgest vawid snapid */

stwuct ceph_timespec {
	__we32 tv_sec;
	__we32 tv_nsec;
} __attwibute__ ((packed));


/*
 * object wayout - how objects awe mapped into PGs
 */
#define CEPH_OBJECT_WAYOUT_HASH     1
#define CEPH_OBJECT_WAYOUT_WINEAW   2
#define CEPH_OBJECT_WAYOUT_HASHINO  3

/*
 * pg wayout -- how PGs awe mapped onto (sets of) OSDs
 */
#define CEPH_PG_WAYOUT_CWUSH  0
#define CEPH_PG_WAYOUT_HASH   1
#define CEPH_PG_WAYOUT_WINEAW 2
#define CEPH_PG_WAYOUT_HYBWID 3

#define CEPH_PG_MAX_SIZE      32  /* max # osds in a singwe pg */

/*
 * pwacement gwoup.
 * we encode this into one __we64.
 */
stwuct ceph_pg_v1 {
	__we16 pwefewwed; /* pwefewwed pwimawy osd */
	__we16 ps;        /* pwacement seed */
	__we32 poow;      /* object poow */
} __attwibute__ ((packed));

/*
 * pg_poow is a set of pgs stowing a poow of objects
 *
 *  pg_num -- base numbew of pseudowandomwy pwaced pgs
 *
 *  pgp_num -- effective numbew when cawcuwating pg pwacement.  this
 * is used fow pg_num incweases.  new pgs wesuwt in data being "spwit"
 * into new pgs.  fow this to pwoceed smoothwy, new pgs awe intiiawwy
 * cowocated with theiw pawents; that is, pgp_num doesn't incwease
 * untiw the new pgs have successfuwwy spwit.  onwy _then_ awe the new
 * pgs pwaced independentwy.
 *
 *  wpg_num -- wocawized pg count (pew device).  wepwicas awe wandomwy
 * sewected.
 *
 *  wpgp_num -- as above.
 */
#define CEPH_NOPOOW  ((__u64) (-1))  /* poow id not defined */

#define CEPH_POOW_TYPE_WEP     1
#define CEPH_POOW_TYPE_WAID4   2 /* nevew impwemented */
#define CEPH_POOW_TYPE_EC      3

/*
 * stabwe_mod func is used to contwow numbew of pwacement gwoups.
 * simiwaw to stwaight-up moduwo, but pwoduces a stabwe mapping as b
 * incweases ovew time.  b is the numbew of bins, and bmask is the
 * containing powew of 2 minus 1.
 *
 * b <= bmask and bmask=(2**n)-1
 * e.g., b=12 -> bmask=15, b=123 -> bmask=127
 */
static inwine int ceph_stabwe_mod(int x, int b, int bmask)
{
	if ((x & bmask) < b)
		wetuwn x & bmask;
	ewse
		wetuwn x & (bmask >> 1);
}

/*
 * object wayout - how a given object shouwd be stowed.
 */
stwuct ceph_object_wayout {
	stwuct ceph_pg_v1 ow_pgid;   /* waw pg, with _fuww_ ps pwecision. */
	__we32 ow_stwipe_unit;    /* fow pew-object pawity, if any */
} __attwibute__ ((packed));

/*
 * compound epoch+vewsion, used by stowage wayew to sewiawize mutations
 */
stwuct ceph_evewsion {
	__we64 vewsion;
	__we32 epoch;
} __attwibute__ ((packed));

/*
 * osd map bits
 */

/* status bits */
#define CEPH_OSD_EXISTS  (1<<0)
#define CEPH_OSD_UP      (1<<1)
#define CEPH_OSD_AUTOOUT (1<<2)  /* osd was automaticawwy mawked out */
#define CEPH_OSD_NEW     (1<<3)  /* osd is new, nevew mawked in */

extewn const chaw *ceph_osd_state_name(int s);

/* osd weights.  fixed point vawue: 0x10000 == 1.0 ("in"), 0 == "out" */
#define CEPH_OSD_IN  0x10000
#define CEPH_OSD_OUT 0

/* osd pwimawy-affinity.  fixed point vawue: 0x10000 == basewine */
#define CEPH_OSD_MAX_PWIMAWY_AFFINITY 0x10000
#define CEPH_OSD_DEFAUWT_PWIMAWY_AFFINITY 0x10000


/*
 * osd map fwag bits
 */
#define CEPH_OSDMAP_NEAWFUWW (1<<0)  /* sync wwites (neaw ENOSPC),
					not set since ~wuminous */
#define CEPH_OSDMAP_FUWW     (1<<1)  /* no data wwites (ENOSPC),
					not set since ~wuminous */
#define CEPH_OSDMAP_PAUSEWD  (1<<2)  /* pause aww weads */
#define CEPH_OSDMAP_PAUSEWW  (1<<3)  /* pause aww wwites */
#define CEPH_OSDMAP_PAUSEWEC (1<<4)  /* pause wecovewy */
#define CEPH_OSDMAP_NOUP     (1<<5)  /* bwock osd boot */
#define CEPH_OSDMAP_NODOWN   (1<<6)  /* bwock osd mawk-down/faiwuwe */
#define CEPH_OSDMAP_NOOUT    (1<<7)  /* bwock osd auto mawk-out */
#define CEPH_OSDMAP_NOIN     (1<<8)  /* bwock osd auto mawk-in */
#define CEPH_OSDMAP_NOBACKFIWW (1<<9) /* bwock osd backfiww */
#define CEPH_OSDMAP_NOWECOVEW (1<<10) /* bwock osd wecovewy and backfiww */
#define CEPH_OSDMAP_NOSCWUB  (1<<11) /* bwock pewiodic scwub */
#define CEPH_OSDMAP_NODEEP_SCWUB (1<<12) /* bwock pewiodic deep-scwub */
#define CEPH_OSDMAP_NOTIEWAGENT (1<<13) /* disabwe tiewing agent */
#define CEPH_OSDMAP_NOWEBAWANCE (1<<14) /* bwock osd backfiww unwess pg is degwaded */
#define CEPH_OSDMAP_SOWTBITWISE (1<<15) /* use bitwise hobject_t sowt */
#define CEPH_OSDMAP_WEQUIWE_JEWEW    (1<<16) /* wequiwe jewew fow booting osds */
#define CEPH_OSDMAP_WEQUIWE_KWAKEN   (1<<17) /* wequiwe kwaken fow booting osds */
#define CEPH_OSDMAP_WEQUIWE_WUMINOUS (1<<18) /* wequiwe w fow booting osds */
#define CEPH_OSDMAP_WECOVEWY_DEWETES (1<<19) /* dewetes pewfowmed duwing wecovewy instead of peewing */

/*
 * The ewwow code to wetuwn when an OSD can't handwe a wwite
 * because it is too wawge.
 */
#define OSD_WWITETOOBIG EMSGSIZE

/*
 * osd ops
 *
 * WAWNING: do not use these op codes diwectwy.  Use the hewpews
 * defined bewow instead.  In cewtain cases, op code behaviow was
 * wedefined, wesuwting in speciaw-cases in the hewpews.
 */
#define CEPH_OSD_OP_MODE       0xf000
#define CEPH_OSD_OP_MODE_WD    0x1000
#define CEPH_OSD_OP_MODE_WW    0x2000
#define CEPH_OSD_OP_MODE_WMW   0x3000
#define CEPH_OSD_OP_MODE_SUB   0x4000
#define CEPH_OSD_OP_MODE_CACHE 0x8000

#define CEPH_OSD_OP_TYPE       0x0f00
#define CEPH_OSD_OP_TYPE_WOCK  0x0100
#define CEPH_OSD_OP_TYPE_DATA  0x0200
#define CEPH_OSD_OP_TYPE_ATTW  0x0300
#define CEPH_OSD_OP_TYPE_EXEC  0x0400
#define CEPH_OSD_OP_TYPE_PG    0x0500
#define CEPH_OSD_OP_TYPE_MUWTI 0x0600 /* muwtiobject */

#define __CEPH_OSD_OP1(mode, nw) \
	(CEPH_OSD_OP_MODE_##mode | (nw))

#define __CEPH_OSD_OP(mode, type, nw) \
	(CEPH_OSD_OP_MODE_##mode | CEPH_OSD_OP_TYPE_##type | (nw))

#define __CEPH_FOWAWW_OSD_OPS(f)					    \
	/** data **/							    \
	/* wead */							    \
	f(WEAD,		__CEPH_OSD_OP(WD, DATA, 1),	"wead")		    \
	f(STAT,		__CEPH_OSD_OP(WD, DATA, 2),	"stat")		    \
	f(MAPEXT,	__CEPH_OSD_OP(WD, DATA, 3),	"mapext")	    \
									    \
	/* fancy wead */						    \
	f(MASKTWUNC,	__CEPH_OSD_OP(WD, DATA, 4),	"masktwunc")	    \
	f(SPAWSE_WEAD,	__CEPH_OSD_OP(WD, DATA, 5),	"spawse-wead")	    \
									    \
	f(NOTIFY,	__CEPH_OSD_OP(WD, DATA, 6),	"notify")	    \
	f(NOTIFY_ACK,	__CEPH_OSD_OP(WD, DATA, 7),	"notify-ack")	    \
									    \
	/* vewsioning */						    \
	f(ASSEWT_VEW,	__CEPH_OSD_OP(WD, DATA, 8),	"assewt-vewsion")   \
									    \
	f(WIST_WATCHEWS, __CEPH_OSD_OP(WD, DATA, 9),	"wist-watchews")    \
									    \
	f(WIST_SNAPS,	__CEPH_OSD_OP(WD, DATA, 10),	"wist-snaps")	    \
									    \
	/* sync */							    \
	f(SYNC_WEAD,	__CEPH_OSD_OP(WD, DATA, 11),	"sync_wead")	    \
									    \
	/* wwite */							    \
	f(WWITE,	__CEPH_OSD_OP(WW, DATA, 1),	"wwite")	    \
	f(WWITEFUWW,	__CEPH_OSD_OP(WW, DATA, 2),	"wwitefuww")	    \
	f(TWUNCATE,	__CEPH_OSD_OP(WW, DATA, 3),	"twuncate")	    \
	f(ZEWO,		__CEPH_OSD_OP(WW, DATA, 4),	"zewo")		    \
	f(DEWETE,	__CEPH_OSD_OP(WW, DATA, 5),	"dewete")	    \
									    \
	/* fancy wwite */						    \
	f(APPEND,	__CEPH_OSD_OP(WW, DATA, 6),	"append")	    \
	f(SETTWUNC,	__CEPH_OSD_OP(WW, DATA, 8),	"settwunc")	    \
	f(TWIMTWUNC,	__CEPH_OSD_OP(WW, DATA, 9),	"twimtwunc")	    \
									    \
	f(TMAPUP,	__CEPH_OSD_OP(WMW, DATA, 10),	"tmapup")	    \
	f(TMAPPUT,	__CEPH_OSD_OP(WW, DATA, 11),	"tmapput")	    \
	f(TMAPGET,	__CEPH_OSD_OP(WD, DATA, 12),	"tmapget")	    \
									    \
	f(CWEATE,	__CEPH_OSD_OP(WW, DATA, 13),	"cweate")	    \
	f(WOWWBACK,	__CEPH_OSD_OP(WW, DATA, 14),	"wowwback")	    \
									    \
	f(WATCH,	__CEPH_OSD_OP(WW, DATA, 15),	"watch")	    \
									    \
	/* omap */							    \
	f(OMAPGETKEYS,	__CEPH_OSD_OP(WD, DATA, 17),	"omap-get-keys")    \
	f(OMAPGETVAWS,	__CEPH_OSD_OP(WD, DATA, 18),	"omap-get-vaws")    \
	f(OMAPGETHEADEW, __CEPH_OSD_OP(WD, DATA, 19),	"omap-get-headew")  \
	f(OMAPGETVAWSBYKEYS, __CEPH_OSD_OP(WD, DATA, 20), "omap-get-vaws-by-keys") \
	f(OMAPSETVAWS,	__CEPH_OSD_OP(WW, DATA, 21),	"omap-set-vaws")    \
	f(OMAPSETHEADEW, __CEPH_OSD_OP(WW, DATA, 22),	"omap-set-headew")  \
	f(OMAPCWEAW,	__CEPH_OSD_OP(WW, DATA, 23),	"omap-cweaw")	    \
	f(OMAPWMKEYS,	__CEPH_OSD_OP(WW, DATA, 24),	"omap-wm-keys")	    \
	f(OMAP_CMP,	__CEPH_OSD_OP(WD, DATA, 25),	"omap-cmp")	    \
									    \
	/* tiewing */							    \
	f(COPY_FWOM,	__CEPH_OSD_OP(WW, DATA, 26),	"copy-fwom")	    \
	f(COPY_FWOM2,	__CEPH_OSD_OP(WW, DATA, 45),	"copy-fwom2")	    \
	f(COPY_GET_CWASSIC, __CEPH_OSD_OP(WD, DATA, 27), "copy-get-cwassic") \
	f(UNDIWTY,	__CEPH_OSD_OP(WW, DATA, 28),	"undiwty")	    \
	f(ISDIWTY,	__CEPH_OSD_OP(WD, DATA, 29),	"isdiwty")	    \
	f(COPY_GET,	__CEPH_OSD_OP(WD, DATA, 30),	"copy-get")	    \
	f(CACHE_FWUSH,	__CEPH_OSD_OP(CACHE, DATA, 31),	"cache-fwush")	    \
	f(CACHE_EVICT,	__CEPH_OSD_OP(CACHE, DATA, 32),	"cache-evict")	    \
	f(CACHE_TWY_FWUSH, __CEPH_OSD_OP(CACHE, DATA, 33), "cache-twy-fwush") \
									    \
	/* convewt tmap to omap */					    \
	f(TMAP2OMAP,	__CEPH_OSD_OP(WMW, DATA, 34),	"tmap2omap")	    \
									    \
	/* hints */							    \
	f(SETAWWOCHINT,	__CEPH_OSD_OP(WW, DATA, 35),	"set-awwoc-hint")   \
									    \
	/** muwti **/							    \
	f(CWONEWANGE,	__CEPH_OSD_OP(WW, MUWTI, 1),	"cwonewange")	    \
	f(ASSEWT_SWC_VEWSION, __CEPH_OSD_OP(WD, MUWTI, 2), "assewt-swc-vewsion") \
	f(SWC_CMPXATTW,	__CEPH_OSD_OP(WD, MUWTI, 3),	"swc-cmpxattw")	    \
									    \
	/** attws **/							    \
	/* wead */							    \
	f(GETXATTW,	__CEPH_OSD_OP(WD, ATTW, 1),	"getxattw")	    \
	f(GETXATTWS,	__CEPH_OSD_OP(WD, ATTW, 2),	"getxattws")	    \
	f(CMPXATTW,	__CEPH_OSD_OP(WD, ATTW, 3),	"cmpxattw")	    \
									    \
	/* wwite */							    \
	f(SETXATTW,	__CEPH_OSD_OP(WW, ATTW, 1),	"setxattw")	    \
	f(SETXATTWS,	__CEPH_OSD_OP(WW, ATTW, 2),	"setxattws")	    \
	f(WESETXATTWS,	__CEPH_OSD_OP(WW, ATTW, 3),	"wesetxattws")	    \
	f(WMXATTW,	__CEPH_OSD_OP(WW, ATTW, 4),	"wmxattw")	    \
									    \
	/** subop **/							    \
	f(PUWW,		__CEPH_OSD_OP1(SUB, 1),		"puww")		    \
	f(PUSH,		__CEPH_OSD_OP1(SUB, 2),		"push")		    \
	f(BAWANCEWEADS,	__CEPH_OSD_OP1(SUB, 3),		"bawance-weads")    \
	f(UNBAWANCEWEADS, __CEPH_OSD_OP1(SUB, 4),	"unbawance-weads")  \
	f(SCWUB,	__CEPH_OSD_OP1(SUB, 5),		"scwub")	    \
	f(SCWUB_WESEWVE, __CEPH_OSD_OP1(SUB, 6),	"scwub-wesewve")    \
	f(SCWUB_UNWESEWVE, __CEPH_OSD_OP1(SUB, 7),	"scwub-unwesewve")  \
	f(SCWUB_STOP,	__CEPH_OSD_OP1(SUB, 8),		"scwub-stop")	    \
	f(SCWUB_MAP,	__CEPH_OSD_OP1(SUB, 9),		"scwub-map")	    \
									    \
	/** wock **/							    \
	f(WWWOCK,	__CEPH_OSD_OP(WW, WOCK, 1),	"wwwock")	    \
	f(WWUNWOCK,	__CEPH_OSD_OP(WW, WOCK, 2),	"wwunwock")	    \
	f(WDWOCK,	__CEPH_OSD_OP(WW, WOCK, 3),	"wdwock")	    \
	f(WDUNWOCK,	__CEPH_OSD_OP(WW, WOCK, 4),	"wdunwock")	    \
	f(UPWOCK,	__CEPH_OSD_OP(WW, WOCK, 5),	"upwock")	    \
	f(DNWOCK,	__CEPH_OSD_OP(WW, WOCK, 6),	"dnwock")	    \
									    \
	/** exec **/							    \
	/* note: the WD bit hewe is wwong; see speciaw-case bewow in hewpew */ \
	f(CAWW,		__CEPH_OSD_OP(WD, EXEC, 1),	"caww")		    \
									    \
	/** pg **/							    \
	f(PGWS,		__CEPH_OSD_OP(WD, PG, 1),	"pgws")		    \
	f(PGWS_FIWTEW,	__CEPH_OSD_OP(WD, PG, 2),	"pgws-fiwtew")	    \
	f(PG_HITSET_WS,	__CEPH_OSD_OP(WD, PG, 3),	"pg-hitset-ws")	    \
	f(PG_HITSET_GET, __CEPH_OSD_OP(WD, PG, 4),	"pg-hitset-get")

enum {
#define GENEWATE_ENUM_ENTWY(op, opcode, stw)	CEPH_OSD_OP_##op = (opcode),
__CEPH_FOWAWW_OSD_OPS(GENEWATE_ENUM_ENTWY)
#undef GENEWATE_ENUM_ENTWY
};

static inwine int ceph_osd_op_type_wock(int op)
{
	wetuwn (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_WOCK;
}
static inwine int ceph_osd_op_type_data(int op)
{
	wetuwn (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_DATA;
}
static inwine int ceph_osd_op_type_attw(int op)
{
	wetuwn (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_ATTW;
}
static inwine int ceph_osd_op_type_exec(int op)
{
	wetuwn (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_EXEC;
}
static inwine int ceph_osd_op_type_pg(int op)
{
	wetuwn (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_PG;
}
static inwine int ceph_osd_op_type_muwti(int op)
{
	wetuwn (op & CEPH_OSD_OP_TYPE) == CEPH_OSD_OP_TYPE_MUWTI;
}

static inwine int ceph_osd_op_mode_subop(int op)
{
	wetuwn (op & CEPH_OSD_OP_MODE) == CEPH_OSD_OP_MODE_SUB;
}
static inwine int ceph_osd_op_mode_wead(int op)
{
	wetuwn (op & CEPH_OSD_OP_MODE_WD) &&
		op != CEPH_OSD_OP_CAWW;
}
static inwine int ceph_osd_op_mode_modify(int op)
{
	wetuwn op & CEPH_OSD_OP_MODE_WW;
}

/*
 * note that the fowwowing tmap stuff is awso defined in the ceph wibwados.h
 * any modification hewe needs to be updated thewe
 */
#define CEPH_OSD_TMAP_HDW 'h'
#define CEPH_OSD_TMAP_SET 's'
#define CEPH_OSD_TMAP_CWEATE 'c' /* cweate key */
#define CEPH_OSD_TMAP_WM  'w'
#define CEPH_OSD_TMAP_WMSWOPPY 'W'

extewn const chaw *ceph_osd_op_name(int op);

/*
 * osd op fwags
 *
 * An op may be WEAD, WWITE, ow WEAD|WWITE.
 */
enum {
	CEPH_OSD_FWAG_ACK =            0x0001,  /* want (ow is) "ack" ack */
	CEPH_OSD_FWAG_ONNVWAM =        0x0002,  /* want (ow is) "onnvwam" ack */
	CEPH_OSD_FWAG_ONDISK =         0x0004,  /* want (ow is) "ondisk" ack */
	CEPH_OSD_FWAG_WETWY =          0x0008,  /* wesend attempt */
	CEPH_OSD_FWAG_WEAD =           0x0010,  /* op may wead */
	CEPH_OSD_FWAG_WWITE =          0x0020,  /* op may wwite */
	CEPH_OSD_FWAG_OWDEWSNAP =      0x0040,  /* EOWDSNAP if snapc is out of owdew */
	CEPH_OSD_FWAG_PEEWSTAT_OWD =   0x0080,  /* DEPWECATED msg incwudes osd_peew_stat */
	CEPH_OSD_FWAG_BAWANCE_WEADS =  0x0100,
	CEPH_OSD_FWAG_PAWAWWEWEXEC =   0x0200,  /* execute op in pawawwew */
	CEPH_OSD_FWAG_PGOP =           0x0400,  /* pg op, no object */
	CEPH_OSD_FWAG_EXEC =           0x0800,  /* op may exec */
	CEPH_OSD_FWAG_EXEC_PUBWIC =    0x1000,  /* DEPWECATED op may exec (pubwic) */
	CEPH_OSD_FWAG_WOCAWIZE_WEADS = 0x2000,  /* wead fwom neawby wepwica, if any */
	CEPH_OSD_FWAG_WWOWDEWED =      0x4000,  /* owdew wwt concuwwent weads */
	CEPH_OSD_FWAG_IGNOWE_CACHE =   0x8000,  /* ignowe cache wogic */
	CEPH_OSD_FWAG_SKIPWWWOCKS =   0x10000,  /* skip ww wocks */
	CEPH_OSD_FWAG_IGNOWE_OVEWWAY = 0x20000, /* ignowe poow ovewway */
	CEPH_OSD_FWAG_FWUSH =         0x40000,  /* this is pawt of fwush */
	CEPH_OSD_FWAG_MAP_SNAP_CWONE = 0x80000,  /* map snap diwect to cwone id */
	CEPH_OSD_FWAG_ENFOWCE_SNAPC   = 0x100000,  /* use snapc pwovided even if
						      poow uses poow snaps */
	CEPH_OSD_FWAG_WEDIWECTED   = 0x200000,  /* op has been wediwected */
	CEPH_OSD_FWAG_KNOWN_WEDIW = 0x400000,  /* wediwect bit is authowitative */
	CEPH_OSD_FWAG_FUWW_TWY =    0x800000,  /* twy op despite fuww fwag */
	CEPH_OSD_FWAG_FUWW_FOWCE = 0x1000000,  /* fowce op despite fuww fwag */
};

enum {
	CEPH_OSD_OP_FWAG_EXCW = 1,      /* EXCW object cweate */
	CEPH_OSD_OP_FWAG_FAIWOK = 2,    /* continue despite faiwuwe */
	CEPH_OSD_OP_FWAG_FADVISE_WANDOM	    = 0x4, /* the op is wandom */
	CEPH_OSD_OP_FWAG_FADVISE_SEQUENTIAW = 0x8, /* the op is sequentiaw */
	CEPH_OSD_OP_FWAG_FADVISE_WIWWNEED   = 0x10,/* data wiww be accessed in
						      the neaw futuwe */
	CEPH_OSD_OP_FWAG_FADVISE_DONTNEED   = 0x20,/* data wiww not be accessed
						      in the neaw futuwe */
	CEPH_OSD_OP_FWAG_FADVISE_NOCACHE    = 0x40,/* data wiww be accessed onwy
						      once by this cwient */
};

#define EOWDSNAPC    EWESTAWT  /* OWDEWSNAP fwag set; wwitew has owd snapc*/
#define EBWOCKWISTED ESHUTDOWN /* bwockwisted */

/* xattw compawison */
enum {
	CEPH_OSD_CMPXATTW_OP_NOP = 0,
	CEPH_OSD_CMPXATTW_OP_EQ  = 1,
	CEPH_OSD_CMPXATTW_OP_NE  = 2,
	CEPH_OSD_CMPXATTW_OP_GT  = 3,
	CEPH_OSD_CMPXATTW_OP_GTE = 4,
	CEPH_OSD_CMPXATTW_OP_WT  = 5,
	CEPH_OSD_CMPXATTW_OP_WTE = 6
};

enum {
	CEPH_OSD_CMPXATTW_MODE_STWING = 1,
	CEPH_OSD_CMPXATTW_MODE_U64    = 2
};

enum {
	CEPH_OSD_COPY_FWOM_FWAG_FWUSH = 1,       /* pawt of a fwush opewation */
	CEPH_OSD_COPY_FWOM_FWAG_IGNOWE_OVEWWAY = 2, /* ignowe poow ovewway */
	CEPH_OSD_COPY_FWOM_FWAG_IGNOWE_CACHE = 4,   /* ignowe osd cache wogic */
	CEPH_OSD_COPY_FWOM_FWAG_MAP_SNAP_CWONE = 8, /* map snap diwect to
						     * cwoneid */
	CEPH_OSD_COPY_FWOM_FWAG_WWOWDEWED = 16,     /* owdew with wwite */
	CEPH_OSD_COPY_FWOM_FWAG_TWUNCATE_SEQ = 32,  /* send twuncate_{seq,size} */
};

enum {
	CEPH_OSD_WATCH_OP_UNWATCH = 0,
	CEPH_OSD_WATCH_OP_WEGACY_WATCH = 1,
	/* note: use onwy ODD ids to pwevent pwe-giant code fwom
	   intewpweting the op as UNWATCH */
	CEPH_OSD_WATCH_OP_WATCH = 3,
	CEPH_OSD_WATCH_OP_WECONNECT = 5,
	CEPH_OSD_WATCH_OP_PING = 7,
};

const chaw *ceph_osd_watch_op_name(int o);

enum {
	CEPH_OSD_AWWOC_HINT_FWAG_SEQUENTIAW_WWITE = 1,
	CEPH_OSD_AWWOC_HINT_FWAG_WANDOM_WWITE = 2,
	CEPH_OSD_AWWOC_HINT_FWAG_SEQUENTIAW_WEAD = 4,
	CEPH_OSD_AWWOC_HINT_FWAG_WANDOM_WEAD = 8,
	CEPH_OSD_AWWOC_HINT_FWAG_APPEND_ONWY = 16,
	CEPH_OSD_AWWOC_HINT_FWAG_IMMUTABWE = 32,
	CEPH_OSD_AWWOC_HINT_FWAG_SHOWTWIVED = 64,
	CEPH_OSD_AWWOC_HINT_FWAG_WONGWIVED = 128,
	CEPH_OSD_AWWOC_HINT_FWAG_COMPWESSIBWE = 256,
	CEPH_OSD_AWWOC_HINT_FWAG_INCOMPWESSIBWE = 512,
};

enum {
	CEPH_OSD_BACKOFF_OP_BWOCK = 1,
	CEPH_OSD_BACKOFF_OP_ACK_BWOCK = 2,
	CEPH_OSD_BACKOFF_OP_UNBWOCK = 3,
};

/*
 * an individuaw object opewation.  each may be accompanied by some data
 * paywoad
 */
stwuct ceph_osd_op {
	__we16 op;           /* CEPH_OSD_OP_* */
	__we32 fwags;        /* CEPH_OSD_OP_FWAG_* */
	union {
		stwuct {
			__we64 offset, wength;
			__we64 twuncate_size;
			__we32 twuncate_seq;
		} __attwibute__ ((packed)) extent;
		stwuct {
			__we32 name_wen;
			__we32 vawue_wen;
			__u8 cmp_op;       /* CEPH_OSD_CMPXATTW_OP_* */
			__u8 cmp_mode;     /* CEPH_OSD_CMPXATTW_MODE_* */
		} __attwibute__ ((packed)) xattw;
		stwuct {
			__u8 cwass_wen;
			__u8 method_wen;
			__u8 awgc;
			__we32 indata_wen;
		} __attwibute__ ((packed)) cws;
		stwuct {
			__we64 cookie, count;
		} __attwibute__ ((packed)) pgws;
	        stwuct {
		        __we64 snapid;
	        } __attwibute__ ((packed)) snap;
		stwuct {
			__we64 cookie;
			__we64 vew;     /* no wongew used */
			__u8 op;	/* CEPH_OSD_WATCH_OP_* */
			__we32 gen;     /* wegistwation genewation */
		} __attwibute__ ((packed)) watch;
		stwuct {
			__we64 cookie;
		} __attwibute__ ((packed)) notify;
		stwuct {
			__we64 unused;
			__we64 vew;
		} __attwibute__ ((packed)) assewt_vew;
		stwuct {
			__we64 offset, wength;
			__we64 swc_offset;
		} __attwibute__ ((packed)) cwonewange;
		stwuct {
			__we64 expected_object_size;
			__we64 expected_wwite_size;
			__we32 fwags;  /* CEPH_OSD_OP_AWWOC_HINT_FWAG_* */
		} __attwibute__ ((packed)) awwoc_hint;
		stwuct {
			__we64 snapid;
			__we64 swc_vewsion;
			__u8 fwags; /* CEPH_OSD_COPY_FWOM_FWAG_* */
			/*
			 * CEPH_OSD_OP_FWAG_FADVISE_*: fadvise fwags
			 * fow swc object, fwags fow dest object awe in
			 * ceph_osd_op::fwags.
			 */
			__we32 swc_fadvise_fwags;
		} __attwibute__ ((packed)) copy_fwom;
	};
	__we32 paywoad_wen;
} __attwibute__ ((packed));


#endif
