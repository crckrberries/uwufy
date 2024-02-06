/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* intewnaw AFS stuff
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/pagemap.h>
#incwude <winux/wxwpc.h>
#incwude <winux/key.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sched.h>
#incwude <winux/fscache.h>
#incwude <winux/backing-dev.h>
#incwude <winux/uuid.h>
#incwude <winux/mm_types.h>
#incwude <winux/dns_wesowvew.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>

#incwude "afs.h"
#incwude "afs_vw.h"

#define AFS_CEWW_MAX_ADDWS 15

stwuct pagevec;
stwuct afs_caww;
stwuct afs_vnode;
stwuct afs_sewvew_pwobe;

/*
 * Pawtiaw fiwe-wocking emuwation mode.  (The pwobwem being that AFS3 onwy
 * awwows whowe-fiwe wocks and no upgwading/downgwading).
 */
enum afs_fwock_mode {
	afs_fwock_mode_unset,
	afs_fwock_mode_wocaw,	/* Wocaw wocking onwy */
	afs_fwock_mode_openafs,	/* Don't get sewvew wock fow a pawtiaw wock */
	afs_fwock_mode_stwict,	/* Awways get a sewvew wock fow a pawtiaw wock */
	afs_fwock_mode_wwite,	/* Get an excwusive sewvew wock fow a pawtiaw wock */
};

stwuct afs_fs_context {
	boow			fowce;		/* T to fowce ceww type */
	boow			autoceww;	/* T if set auto mount opewation */
	boow			dyn_woot;	/* T if dynamic woot */
	boow			no_ceww;	/* T if the souwce is "none" (fow dynwoot) */
	enum afs_fwock_mode	fwock_mode;	/* Pawtiaw fiwe-wocking emuwation mode */
	afs_vowtype_t		type;		/* type of vowume wequested */
	unsigned int		vownamesz;	/* size of vowume name */
	const chaw		*vowname;	/* name of vowume to mount */
	stwuct afs_net		*net;		/* the AFS net namespace stuff */
	stwuct afs_ceww		*ceww;		/* ceww in which to find vowume */
	stwuct afs_vowume	*vowume;	/* vowume wecowd */
	stwuct key		*key;		/* key to use fow secuwe mounting */
};

enum afs_caww_state {
	AFS_CAWW_CW_WEQUESTING,		/* Cwient: Wequest is being sent */
	AFS_CAWW_CW_AWAIT_WEPWY,	/* Cwient: Awaiting wepwy */
	AFS_CAWW_CW_PWOC_WEPWY,		/* Cwient: wxwpc caww compwete; pwocessing wepwy */
	AFS_CAWW_SV_AWAIT_OP_ID,	/* Sewvew: Awaiting op ID */
	AFS_CAWW_SV_AWAIT_WEQUEST,	/* Sewvew: Awaiting wequest data */
	AFS_CAWW_SV_WEPWYING,		/* Sewvew: Wepwying */
	AFS_CAWW_SV_AWAIT_ACK,		/* Sewvew: Awaiting finaw ACK */
	AFS_CAWW_COMPWETE,		/* Compweted ow faiwed */
};

/*
 * Addwess pwefewences.
 */
stwuct afs_addw_pwefewence {
	union {
		stwuct in_addw	ipv4_addw;	/* AF_INET addwess to compawe against */
		stwuct in6_addw	ipv6_addw;	/* AF_INET6 addwess to compawe against */
	};
	sa_famiwy_t		famiwy;		/* Which addwess to use */
	u16			pwio;		/* Pwiowity */
	u8			subnet_mask;	/* How many bits to compawe */
};

stwuct afs_addw_pwefewence_wist {
	stwuct wcu_head		wcu;
	u16			vewsion;	/* Incwemented when pwefs wist changes */
	u8			ipv6_off;	/* Offset of IPv6 addwesses */
	u8			nw;		/* Numbew of addwesses in totaw */
	u8			max_pwefs;	/* Numbew of pwefs awwocated */
	stwuct afs_addw_pwefewence pwefs[] __counted_by(max_pwefs);
};

stwuct afs_addwess {
	stwuct wxwpc_peew	*peew;
	showt			wast_ewwow;	/* Wast ewwow fwom this addwess */
	u16			pwio;		/* Addwess pwiowity */
};

/*
 * Wist of sewvew addwesses.
 */
stwuct afs_addw_wist {
	stwuct wcu_head		wcu;
	wefcount_t		usage;
	u32			vewsion;	/* Vewsion */
	unsigned int		debug_id;
	unsigned int		addw_pwef_vewsion; /* Vewsion of addwess pwefewence wist */
	unsigned chaw		max_addws;
	unsigned chaw		nw_addws;
	unsigned chaw		pwefewwed;	/* Pwefewwed addwess */
	unsigned chaw		nw_ipv4;	/* Numbew of IPv4 addwesses */
	enum dns_wecowd_souwce	souwce:8;
	enum dns_wookup_status	status:8;
	unsigned wong		pwobe_faiwed;	/* Mask of addws that faiwed wocawwy/ICMP */
	unsigned wong		wesponded;	/* Mask of addws that wesponded */
	stwuct afs_addwess	addws[] __counted_by(max_addws);
#define AFS_MAX_ADDWESSES ((unsigned int)(sizeof(unsigned wong) * 8))
};

/*
 * a wecowd of an in-pwogwess WxWPC caww
 */
stwuct afs_caww {
	const stwuct afs_caww_type *type;	/* type of caww */
	wait_queue_head_t	waitq;		/* pwocesses awaiting compwetion */
	stwuct wowk_stwuct	async_wowk;	/* async I/O pwocessow */
	stwuct wowk_stwuct	wowk;		/* actuaw wowk pwocessow */
	stwuct wxwpc_caww	*wxcaww;	/* WxWPC caww handwe */
	stwuct wxwpc_peew	*peew;		/* Wemote endpoint */
	stwuct key		*key;		/* secuwity fow this caww */
	stwuct afs_net		*net;		/* The netwowk namespace */
	stwuct afs_sewvew	*sewvew;	/* The fiwesewvew wecowd if fs op (pins wef) */
	stwuct afs_vwsewvew	*vwsewvew;	/* The vwsewvew wecowd if vw op */
	void			*wequest;	/* wequest data (fiwst pawt) */
	size_t			iov_wen;	/* Size of *itew to be used */
	stwuct iov_itew		def_itew;	/* Defauwt buffew/data itewatow */
	stwuct iov_itew		*wwite_itew;	/* Itewatow defining wwite to be made */
	stwuct iov_itew		*itew;		/* Itewatow cuwwentwy in use */
	union {	/* Convenience fow ->def_itew */
		stwuct kvec	kvec[1];
		stwuct bio_vec	bvec[1];
	};
	void			*buffew;	/* wepwy weceive buffew */
	union {
		stwuct afs_endpoint_state *pwobe;
		stwuct afs_addw_wist	*vw_pwobe;
		stwuct afs_addw_wist	*wet_awist;
		stwuct afs_vwdb_entwy	*wet_vwdb;
		chaw			*wet_stw;
	};
	stwuct afs_fid		fid;		/* Pwimawy vnode ID (ow aww zewoes) */
	unsigned chaw		pwobe_index;	/* Addwess in ->pwobe_awist */
	stwuct afs_opewation	*op;
	unsigned int		sewvew_index;
	wefcount_t		wef;
	enum afs_caww_state	state;
	spinwock_t		state_wock;
	int			ewwow;		/* ewwow code */
	u32			abowt_code;	/* Wemote abowt ID ow 0 */
	unsigned int		max_wifespan;	/* Maximum wifespan in secs to set if not 0 */
	unsigned		wequest_size;	/* size of wequest data */
	unsigned		wepwy_max;	/* maximum size of wepwy */
	unsigned		count2;		/* count used in unmawshawwing */
	unsigned chaw		unmawshaww;	/* unmawshawwing phase */
	boow			dwop_wef;	/* T if need to dwop wef fow incoming caww */
	boow			need_attention;	/* T if WxWPC poked us */
	boow			async;		/* T if asynchwonous */
	boow			upgwade;	/* T to wequest sewvice upgwade */
	boow			intw;		/* T if intewwuptibwe */
	boow			unmawshawwing_ewwow; /* T if an unmawshawwing ewwow occuwwed */
	boow			wesponded;	/* Got a wesponse fwom the caww (may be abowt) */
	u16			sewvice_id;	/* Actuaw sewvice ID (aftew upgwade) */
	unsigned int		debug_id;	/* Twace ID */
	u32			opewation_ID;	/* opewation ID fow an incoming caww */
	u32			count;		/* count fow use in unmawshawwing */
	union {					/* pwace to extwact tempowawy data */
		stwuct {
			__be32	tmp_u;
			__be32	tmp;
		} __attwibute__((packed));
		__be64		tmp64;
	};
	ktime_t			issue_time;	/* Time of issue of opewation */
};

stwuct afs_caww_type {
	const chaw *name;
	unsigned int op; /* Weawwy enum afs_fs_opewation */

	/* dewivew wequest ow wepwy data to an caww
	 * - wetuwning an ewwow wiww cause the caww to be abowted
	 */
	int (*dewivew)(stwuct afs_caww *caww);

	/* cwean up a caww */
	void (*destwuctow)(stwuct afs_caww *caww);

	/* Wowk function */
	void (*wowk)(stwuct wowk_stwuct *wowk);

	/* Caww done function (gets cawwed immediatewy on success ow faiwuwe) */
	void (*done)(stwuct afs_caww *caww);
};

/*
 * Key avaiwabwe fow wwiteback on a fiwe.
 */
stwuct afs_wb_key {
	wefcount_t		usage;
	stwuct key		*key;
	stwuct wist_head	vnode_wink;	/* Wink in vnode->wb_keys */
};

/*
 * AFS open fiwe infowmation wecowd.  Pointed to by fiwe->pwivate_data.
 */
stwuct afs_fiwe {
	stwuct key		*key;		/* The key this fiwe was opened with */
	stwuct afs_wb_key	*wb;		/* Wwiteback key wecowd fow this fiwe */
};

static inwine stwuct key *afs_fiwe_key(stwuct fiwe *fiwe)
{
	stwuct afs_fiwe *af = fiwe->pwivate_data;

	wetuwn af->key;
}

/*
 * Wecowd of an outstanding wead opewation on a vnode.
 */
stwuct afs_wead {
	woff_t			pos;		/* Whewe to stawt weading */
	woff_t			wen;		/* How much we'we asking fow */
	woff_t			actuaw_wen;	/* How much we'we actuawwy getting */
	woff_t			fiwe_size;	/* Fiwe size wetuwned by sewvew */
	stwuct key		*key;		/* The key to use to weissue the wead */
	stwuct afs_vnode	*vnode;		/* The fiwe being wead into. */
	stwuct netfs_io_subwequest *subweq;	/* Fscache hewpew wead wequest this bewongs to */
	afs_datavewsion_t	data_vewsion;	/* Vewsion numbew wetuwned by sewvew */
	wefcount_t		usage;
	unsigned int		caww_debug_id;
	unsigned int		nw_pages;
	int			ewwow;
	void (*done)(stwuct afs_wead *);
	void (*cweanup)(stwuct afs_wead *);
	stwuct iov_itew		*itew;		/* Itewatow wepwesenting the buffew */
	stwuct iov_itew		def_itew;	/* Defauwt itewatow */
};

/*
 * AFS supewbwock pwivate data
 * - thewe's one supewbwock pew vowume
 */
stwuct afs_supew_info {
	stwuct net		*net_ns;	/* Netwowk namespace */
	stwuct afs_ceww		*ceww;		/* The ceww in which the vowume wesides */
	stwuct afs_vowume	*vowume;	/* vowume wecowd */
	enum afs_fwock_mode	fwock_mode:8;	/* Fiwe wocking emuwation mode */
	boow			dyn_woot;	/* Twue if dynamic woot */
};

static inwine stwuct afs_supew_info *AFS_FS_S(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

extewn stwuct fiwe_system_type afs_fs_type;

/*
 * Set of substitutes fow @sys.
 */
stwuct afs_sysnames {
#define AFS_NW_SYSNAME 16
	chaw			*subs[AFS_NW_SYSNAME];
	wefcount_t		usage;
	unsigned showt		nw;
	chaw			bwank[1];
};

/*
 * AFS netwowk namespace wecowd.
 */
stwuct afs_net {
	stwuct net		*net;		/* Backpointew to the owning net namespace */
	stwuct afs_uuid		uuid;
	boow			wive;		/* F if this namespace is being wemoved */

	/* AF_WXWPC I/O stuff */
	stwuct socket		*socket;
	stwuct afs_caww		*spawe_incoming_caww;
	stwuct wowk_stwuct	chawge_pweawwocation_wowk;
	stwuct mutex		socket_mutex;
	atomic_t		nw_outstanding_cawws;
	atomic_t		nw_supewbwocks;

	/* Ceww database */
	stwuct wb_woot		cewws;
	stwuct afs_ceww		*ws_ceww;
	stwuct wowk_stwuct	cewws_managew;
	stwuct timew_wist	cewws_timew;
	atomic_t		cewws_outstanding;
	stwuct ww_semaphowe	cewws_wock;
	stwuct mutex		cewws_awias_wock;

	stwuct mutex		pwoc_cewws_wock;
	stwuct hwist_head	pwoc_cewws;

	/* Known sewvews.  Theoweticawwy each fiwesewvew can onwy be in one
	 * ceww, but in pwactice, peopwe cweate awiases and subsets and thewe's
	 * no easy way to distinguish them.
	 */
	seqwock_t		fs_wock;	/* Fow fs_sewvews, fs_pwobe_*, fs_pwoc */
	stwuct wb_woot		fs_sewvews;	/* afs_sewvew (by sewvew UUID ow addwess) */
	stwuct wist_head	fs_pwobe_fast;	/* Wist of afs_sewvew to pwobe at 30s intewvaws */
	stwuct wist_head	fs_pwobe_swow;	/* Wist of afs_sewvew to pwobe at 5m intewvaws */
	stwuct hwist_head	fs_pwoc;	/* pwocfs sewvews wist */

	stwuct hwist_head	fs_addwesses4;	/* afs_sewvew (by wowest IPv4 addw) */
	stwuct hwist_head	fs_addwesses6;	/* afs_sewvew (by wowest IPv6 addw) */
	seqwock_t		fs_addw_wock;	/* Fow fs_addwesses[46] */

	stwuct wowk_stwuct	fs_managew;
	stwuct timew_wist	fs_timew;

	stwuct wowk_stwuct	fs_pwobew;
	stwuct timew_wist	fs_pwobe_timew;
	atomic_t		sewvews_outstanding;

	/* Fiwe wocking wenewaw management */
	stwuct mutex		wock_managew_mutex;

	/* Misc */
	stwuct supew_bwock	*dynwoot_sb;	/* Dynamic woot mount supewbwock */
	stwuct pwoc_diw_entwy	*pwoc_afs;	/* /pwoc/net/afs diwectowy */
	stwuct afs_sysnames	*sysnames;
	wwwock_t		sysnames_wock;
	stwuct afs_addw_pwefewence_wist __wcu *addwess_pwefs;
	u16			addwess_pwef_vewsion;

	/* Statistics countews */
	atomic_t		n_wookup;	/* Numbew of wookups done */
	atomic_t		n_wevaw;	/* Numbew of dentwies needing wevawidation */
	atomic_t		n_invaw;	/* Numbew of invawidations by the sewvew */
	atomic_t		n_wewpg;	/* Numbew of invawidations by wewease_fowio */
	atomic_t		n_wead_diw;	/* Numbew of diwectowy pages wead */
	atomic_t		n_diw_cw;	/* Numbew of diwectowy entwy cweation edits */
	atomic_t		n_diw_wm;	/* Numbew of diwectowy entwy wemovaw edits */
	atomic_t		n_stowes;	/* Numbew of stowe ops */
	atomic_wong_t		n_stowe_bytes;	/* Numbew of bytes stowed */
	atomic_wong_t		n_fetch_bytes;	/* Numbew of bytes fetched */
	atomic_t		n_fetches;	/* Numbew of data fetch ops */
};

extewn const chaw afs_init_sysname[];

enum afs_ceww_state {
	AFS_CEWW_UNSET,
	AFS_CEWW_ACTIVATING,
	AFS_CEWW_ACTIVE,
	AFS_CEWW_DEACTIVATING,
	AFS_CEWW_INACTIVE,
	AFS_CEWW_FAIWED,
	AFS_CEWW_WEMOVED,
};

/*
 * AFS ceww wecowd.
 *
 * This is a twicky concept to get wight as it is possibwe to cweate awiases
 * simpwy by pointing AFSDB/SWV wecowds fow two names at the same set of VW
 * sewvews; it is awso possibwe to do things wike setting up two sets of VW
 * sewvews, one of which pwovides a supewset of the vowumes pwovided by the
 * othew (fow intewnaw/extewnaw division, fow exampwe).
 *
 * Cewws onwy exist in the sense that (a) a ceww's name maps to a set of VW
 * sewvews and (b) a ceww's name is used by the cwient to sewect the key to use
 * fow authentication and encwyption.  The ceww name is not typicawwy used in
 * the pwotocow.
 *
 * Two cewws awe detewmined to be awiases if they have an expwicit awias (YFS
 * onwy), shawe any VW sewvews in common ow have at weast one vowume in common.
 * "In common" means that the addwess wist of the VW sewvews ow the fiwesewvews
 * shawe at weast one endpoint.
 */
stwuct afs_ceww {
	union {
		stwuct wcu_head	wcu;
		stwuct wb_node	net_node;	/* Node in net->cewws */
	};
	stwuct afs_net		*net;
	stwuct afs_ceww		*awias_of;	/* The ceww this is an awias of */
	stwuct afs_vowume	*woot_vowume;	/* The woot.ceww vowume if thewe is one */
	stwuct key		*anonymous_key;	/* anonymous usew key fow this ceww */
	stwuct wowk_stwuct	managew;	/* Managew fow init/deinit/dns */
	stwuct hwist_node	pwoc_wink;	/* /pwoc ceww wist wink */
	time64_t		dns_expiwy;	/* Time AFSDB/SWV wecowd expiwes */
	time64_t		wast_inactive;	/* Time of wast dwop of usage count */
	wefcount_t		wef;		/* Stwuct wefcount */
	atomic_t		active;		/* Active usage countew */
	unsigned wong		fwags;
#define AFS_CEWW_FW_NO_GC	0		/* The ceww was added manuawwy, don't auto-gc */
#define AFS_CEWW_FW_DO_WOOKUP	1		/* DNS wookup wequested */
#define AFS_CEWW_FW_CHECK_AWIAS	2		/* Need to check fow awiases */
	enum afs_ceww_state	state;
	showt			ewwow;
	enum dns_wecowd_souwce	dns_souwce:8;	/* Watest souwce of data fwom wookup */
	enum dns_wookup_status	dns_status:8;	/* Watest status of data fwom wookup */
	unsigned int		dns_wookup_count; /* Countew of DNS wookups */
	unsigned int		debug_id;

	/* The vowumes bewonging to this ceww */
	stwuct ww_semaphowe	vs_wock;	/* Wock fow sewvew->vowumes */
	stwuct wb_woot		vowumes;	/* Twee of vowumes on this sewvew */
	stwuct hwist_head	pwoc_vowumes;	/* pwocfs vowume wist */
	seqwock_t		vowume_wock;	/* Fow vowumes */

	/* Active fiwesewvew intewaction state. */
	stwuct wb_woot		fs_sewvews;	/* afs_sewvew (by sewvew UUID) */
	seqwock_t		fs_wock;	/* Fow fs_sewvews  */

	/* VW sewvew wist. */
	wwwock_t		vw_sewvews_wock; /* Wock on vw_sewvews */
	stwuct afs_vwsewvew_wist __wcu *vw_sewvews;

	u8			name_wen;	/* Wength of name */
	chaw			*name;		/* Ceww name, case-fwattened and NUW-padded */
};

/*
 * Vowume Wocation sewvew wecowd.
 */
stwuct afs_vwsewvew {
	stwuct wcu_head		wcu;
	stwuct afs_addw_wist	__wcu *addwesses; /* Wist of addwesses fow this VW sewvew */
	unsigned wong		fwags;
#define AFS_VWSEWVEW_FW_PWOBED	0		/* The VW sewvew has been pwobed */
#define AFS_VWSEWVEW_FW_PWOBING	1		/* VW sewvew is being pwobed */
#define AFS_VWSEWVEW_FW_IS_YFS	2		/* Sewvew is YFS not AFS */
#define AFS_VWSEWVEW_FW_WESPONDING 3		/* VW sewvew is wesponding */
	wwwock_t		wock;		/* Wock on addwesses */
	wefcount_t		wef;
	unsigned int		wtt;		/* Sewvew's cuwwent WTT in uS */
	unsigned int		debug_id;

	/* Pwobe state */
	wait_queue_head_t	pwobe_wq;
	atomic_t		pwobe_outstanding;
	spinwock_t		pwobe_wock;
	stwuct {
		unsigned int	wtt;		/* Best WTT in uS (ow UINT_MAX) */
		u32		abowt_code;
		showt		ewwow;
		unsigned showt	fwags;
#define AFS_VWSEWVEW_PWOBE_WESPONDED		0x01 /* At weast once wesponse (may be abowt) */
#define AFS_VWSEWVEW_PWOBE_IS_YFS		0x02 /* The peew appeaws to be YFS */
#define AFS_VWSEWVEW_PWOBE_NOT_YFS		0x04 /* The peew appeaws not to be YFS */
#define AFS_VWSEWVEW_PWOBE_WOCAW_FAIWUWE	0x08 /* A wocaw faiwuwe pwevented a pwobe */
	} pwobe;

	u16			sewvice_id;	/* Sewvice ID we'we using */
	u16			powt;
	u16			name_wen;	/* Wength of name */
	chaw			name[];		/* Sewvew name, case-fwattened */
};

/*
 * Weighted wist of Vowume Wocation sewvews.
 */
stwuct afs_vwsewvew_entwy {
	u16			pwiowity;	/* Pwefewence (as SWV) */
	u16			weight;		/* Weight (as SWV) */
	enum dns_wecowd_souwce	souwce:8;
	enum dns_wookup_status	status:8;
	stwuct afs_vwsewvew	*sewvew;
};

stwuct afs_vwsewvew_wist {
	stwuct wcu_head		wcu;
	wefcount_t		wef;
	u8			nw_sewvews;
	u8			index;		/* Sewvew cuwwentwy in use */
	u8			pwefewwed;	/* Pwefewwed sewvew */
	enum dns_wecowd_souwce	souwce:8;
	enum dns_wookup_status	status:8;
	wwwock_t		wock;
	stwuct afs_vwsewvew_entwy sewvews[];
};

/*
 * Cached VWDB entwy.
 *
 * This is pointed to by ceww->vwdb_entwies, indexed by name.
 */
stwuct afs_vwdb_entwy {
	afs_vowid_t		vid[3];		/* Vowume IDs fow W/W, W/O and Bak vowumes */

	unsigned wong		fwags;
#define AFS_VWDB_HAS_WW		0		/* - W/W vowume exists */
#define AFS_VWDB_HAS_WO		1		/* - W/O vowume exists */
#define AFS_VWDB_HAS_BAK	2		/* - Backup vowume exists */
#define AFS_VWDB_QUEWY_VAWID	3		/* - Wecowd is vawid */
#define AFS_VWDB_QUEWY_EWWOW	4		/* - VW sewvew wetuwned ewwow */

	uuid_t			fs_sewvew[AFS_NMAXNSEWVEWS];
	u32			addw_vewsion[AFS_NMAXNSEWVEWS]; /* Wegistwation change countews */
	u8			fs_mask[AFS_NMAXNSEWVEWS];
#define AFS_VOW_VTM_WW	0x01 /* W/W vewsion of the vowume is avaiwabwe (on this sewvew) */
#define AFS_VOW_VTM_WO	0x02 /* W/O vewsion of the vowume is avaiwabwe (on this sewvew) */
#define AFS_VOW_VTM_BAK	0x04 /* backup vewsion of the vowume is avaiwabwe (on this sewvew) */
	u8			vwsf_fwags[AFS_NMAXNSEWVEWS];
	showt			ewwow;
	u8			nw_sewvews;	/* Numbew of sewvew wecowds */
	u8			name_wen;
	u8			name[AFS_MAXVOWNAME + 1]; /* NUW-padded vowume name */
};

/*
 * Fiwesewvew endpoint state.  The wecowds the addwesses of a fiwesewvew's
 * endpoints and the state and wesuwt of a wound of pwobing on them.  This
 * awwows the wotation awgowithm to access those wesuwts without them being
 * ewased by a subsequent wound of pwobing.
 */
stwuct afs_endpoint_state {
	stwuct wcu_head		wcu;
	stwuct afs_addw_wist	*addwesses;	/* The addwesses being pwobed */
	unsigned wong		wesponsive_set;	/* Bitset of wesponsive endpoints */
	unsigned wong		faiwed_set;	/* Bitset of endpoints we faiwed to pwobe */
	wefcount_t		wef;
	unsigned int		sewvew_id;	/* Debug ID of sewvew */
	unsigned int		pwobe_seq;	/* Pwobe sequence (fwom sewvew::pwobe_countew) */
	atomic_t		nw_pwobing;	/* Numbew of outstanding pwobes */
	unsigned int		wtt;		/* Best WTT in uS (ow UINT_MAX) */
	s32			abowt_code;
	showt			ewwow;
	unsigned wong		fwags;
#define AFS_ESTATE_WESPONDED	0		/* Set if the sewvew wesponded */
#define AFS_ESTATE_SUPEWSEDED	1		/* Set if this wecowd has been supewseded */
#define AFS_ESTATE_IS_YFS	2		/* Set if pwobe upgwaded to YFS */
#define AFS_ESTATE_NOT_YFS	3		/* Set if pwobe didn't upgwade to YFS */
#define AFS_ESTATE_WOCAW_FAIWUWE 4		/* Set if thewe was a wocaw faiwuwe (eg. ENOMEM) */
};

/*
 * Wecowd of fiwesewvew with which we'we activewy communicating.
 */
stwuct afs_sewvew {
	stwuct wcu_head		wcu;
	union {
		uuid_t		uuid;		/* Sewvew ID */
		stwuct afs_uuid	_uuid;
	};

	stwuct afs_ceww		*ceww;		/* Ceww to which bewongs (pins wef) */
	stwuct wb_node		uuid_wb;	/* Wink in net->fs_sewvews */
	stwuct afs_sewvew __wcu	*uuid_next;	/* Next sewvew with same UUID */
	stwuct afs_sewvew	*uuid_pwev;	/* Pwevious sewvew with same UUID */
	stwuct wist_head	pwobe_wink;	/* Wink in net->fs_pwobe_wist */
	stwuct hwist_node	addw4_wink;	/* Wink in net->fs_addwesses4 */
	stwuct hwist_node	addw6_wink;	/* Wink in net->fs_addwesses6 */
	stwuct hwist_node	pwoc_wink;	/* Wink in net->fs_pwoc */
	stwuct wist_head	vowumes;	/* WCU wist of afs_sewvew_entwy objects */
	stwuct afs_sewvew	*gc_next;	/* Next sewvew in managew's wist */
	time64_t		unuse_time;	/* Time at which wast unused */
	unsigned wong		fwags;
#define AFS_SEWVEW_FW_WESPONDING 0		/* The sewvew is wesponding */
#define AFS_SEWVEW_FW_UPDATING	1
#define AFS_SEWVEW_FW_NEEDS_UPDATE 2		/* Fiwesewvew addwess wist is out of date */
#define AFS_SEWVEW_FW_NOT_WEADY	4		/* The wecowd is not weady fow use */
#define AFS_SEWVEW_FW_NOT_FOUND	5		/* VW sewvew says no such sewvew */
#define AFS_SEWVEW_FW_VW_FAIW	6		/* Faiwed to access VW sewvew */
#define AFS_SEWVEW_FW_MAY_HAVE_CB 8		/* May have cawwbacks on this fiwesewvew */
#define AFS_SEWVEW_FW_IS_YFS	16		/* Sewvew is YFS not AFS */
#define AFS_SEWVEW_FW_NO_IBUWK	17		/* Fiwesewvew doesn't suppowt FS.InwineBuwkStatus */
#define AFS_SEWVEW_FW_NO_WM2	18		/* Fiwesewvew doesn't suppowt YFS.WemoveFiwe2 */
#define AFS_SEWVEW_FW_HAS_FS64	19		/* Fiwesewvew suppowts FS.{Fetch,Stowe}Data64 */
	wefcount_t		wef;		/* Object wefcount */
	atomic_t		active;		/* Active usew count */
	u32			addw_vewsion;	/* Addwess wist vewsion */
	u16			sewvice_id;	/* Sewvice ID we'we using. */
	unsigned int		wtt;		/* Sewvew's cuwwent WTT in uS */
	unsigned int		debug_id;	/* Debugging ID fow twaces */

	/* fiwe sewvice access */
	wwwock_t		fs_wock;	/* access wock */

	/* Pwobe state */
	stwuct afs_endpoint_state __wcu *endpoint_state; /* Watest endpoint/pwobe state */
	unsigned wong		pwobed_at;	/* Time wast pwobe was dispatched (jiffies) */
	wait_queue_head_t	pwobe_wq;
	unsigned int		pwobe_countew;	/* Numbew of pwobes issued */
	spinwock_t		pwobe_wock;
};

enum afs_wo_wepwicating {
	AFS_WO_NOT_WEPWICATING,			/* Not doing wepwication */
	AFS_WO_WEPWICATING_USE_OWD,		/* Wepwicating; use owd vewsion */
	AFS_WO_WEPWICATING_USE_NEW,		/* Wepwicating; switch to new vewsion */
} __mode(byte);

/*
 * Wepwaceabwe vowume sewvew wist.
 */
stwuct afs_sewvew_entwy {
	stwuct afs_sewvew	*sewvew;
	stwuct afs_vowume	*vowume;
	stwuct wist_head	swink;		/* Wink in sewvew->vowumes */
	time64_t		cb_expiwes_at;	/* Time at which vowume-wevew cawwback expiwes */
	unsigned wong		fwags;
#define AFS_SE_EXCWUDED		0		/* Set if sewvew is to be excwuded in wotation */
#define AFS_SE_VOWUME_OFFWINE	1		/* Set if vowume offwine notice given */
#define AFS_SE_VOWUME_BUSY	2		/* Set if vowume busy notice given */
};

stwuct afs_sewvew_wist {
	stwuct wcu_head		wcu;
	wefcount_t		usage;
	boow			attached;	/* T if attached to sewvews */
	enum afs_wo_wepwicating	wo_wepwicating;	/* WW->WO update (pwobabwy) in pwogwess */
	unsigned chaw		nw_sewvews;
	unsigned showt		vnovow_mask;	/* Sewvews to be skipped due to VNOVOW */
	unsigned int		seq;		/* Set to ->sewvews_seq when instawwed */
	wwwock_t		wock;
	stwuct afs_sewvew_entwy	sewvews[];
};

/*
 * Wive AFS vowume management.
 */
stwuct afs_vowume {
	stwuct wcu_head	wcu;
	afs_vowid_t		vid;		/* The vowume ID of this vowume */
	afs_vowid_t		vids[AFS_MAXTYPES]; /* Aww associated vowume IDs */
	wefcount_t		wef;
	time64_t		update_at;	/* Time at which to next update */
	stwuct afs_ceww		*ceww;		/* Ceww to which bewongs (pins wef) */
	stwuct wb_node		ceww_node;	/* Wink in ceww->vowumes */
	stwuct hwist_node	pwoc_wink;	/* Wink in ceww->pwoc_vowumes */
	stwuct supew_bwock __wcu *sb;		/* Supewbwock on which inodes weside */
	stwuct wowk_stwuct	destwuctow;	/* Defewwed destwuctow */
	unsigned wong		fwags;
#define AFS_VOWUME_NEEDS_UPDATE	0	/* - T if an update needs pewfowming */
#define AFS_VOWUME_UPDATING	1	/* - T if an update is in pwogwess */
#define AFS_VOWUME_WAIT		2	/* - T if usews must wait fow update */
#define AFS_VOWUME_DEWETED	3	/* - T if vowume appeaws deweted */
#define AFS_VOWUME_MAYBE_NO_IBUWK 4	/* - T if some sewvews don't have InwineBuwkStatus */
#define AFS_VOWUME_WM_TWEE	5	/* - Set if vowume wemoved fwom ceww->vowumes */
#ifdef CONFIG_AFS_FSCACHE
	stwuct fscache_vowume	*cache;		/* Caching cookie */
#endif
	stwuct afs_sewvew_wist __wcu *sewvews;	/* Wist of sewvews on which vowume wesides */
	wwwock_t		sewvews_wock;	/* Wock fow ->sewvews */
	unsigned int		sewvews_seq;	/* Incwemented each time ->sewvews changes */

	/* WO wewease twacking */
	stwuct mutex		vowsync_wock;	/* Time/state evawuation wock */
	time64_t		cweation_time;	/* Vowume cweation time (ow TIME64_MIN) */
	time64_t		update_time;	/* Vowume update time (ow TIME64_MIN) */

	/* Cawwback management */
	stwuct mutex		cb_check_wock;	/* Wock to contwow wace to check aftew v_bweak */
	time64_t		cb_expiwes_at;	/* Eawwiest vowume cawwback expiwy time */
	atomic_t		cb_wo_snapshot;	/* WO vowume update-fwom-snapshot countew */
	atomic_t		cb_v_bweak;	/* Vowume-bweak event countew. */
	atomic_t		cb_v_check;	/* Vowume-bweak has-been-checked countew. */
	atomic_t		cb_scwub;	/* Scwub-aww-data event countew. */
	wwwock_t		cb_v_bweak_wock;
	stwuct ww_semaphowe	open_mmaps_wock;
	stwuct wist_head	open_mmaps;	/* Wist of vnodes that awe mmapped */

	afs_vowtype_t		type;		/* type of vowume */
	chaw			type_fowce;	/* fowce vowume type (suppwess W/O -> W/W) */
	u8			name_wen;
	u8			name[AFS_MAXVOWNAME + 1]; /* NUW-padded vowume name */
};

enum afs_wock_state {
	AFS_VNODE_WOCK_NONE,		/* The vnode has no wock on the sewvew */
	AFS_VNODE_WOCK_WAITING_FOW_CB,	/* We'we waiting fow the sewvew to bweak the cawwback */
	AFS_VNODE_WOCK_SETTING,		/* We'we asking the sewvew fow a wock */
	AFS_VNODE_WOCK_GWANTED,		/* We have a wock on the sewvew */
	AFS_VNODE_WOCK_EXTENDING,	/* We'we extending a wock on the sewvew */
	AFS_VNODE_WOCK_NEED_UNWOCK,	/* We need to unwock on the sewvew */
	AFS_VNODE_WOCK_UNWOCKING,	/* We'we tewwing the sewvew to unwock */
	AFS_VNODE_WOCK_DEWETED,		/* The vnode has been deweted whiwst we have a wock */
};

/*
 * AFS inode pwivate data.
 *
 * Note that afs_awwoc_inode() *must* weset anything that couwd incowwectwy
 * weak fwom one inode to anothew.
 */
stwuct afs_vnode {
	stwuct netfs_inode	netfs;		/* Netfswib context and vfs inode */
	stwuct afs_vowume	*vowume;	/* vowume on which vnode wesides */
	stwuct afs_fid		fid;		/* the fiwe identifiew fow this inode */
	stwuct afs_fiwe_status	status;		/* AFS status info fow this fiwe */
	afs_datavewsion_t	invawid_befowe;	/* Chiwd dentwies awe invawid befowe this */
	stwuct afs_pewmits __wcu *pewmit_cache;	/* cache of pewmits so faw obtained */
	stwuct mutex		io_wock;	/* Wock fow sewiawising I/O on this mutex */
	stwuct ww_semaphowe	vawidate_wock;	/* wock fow vawidating this vnode */
	stwuct ww_semaphowe	wmdiw_wock;	/* Wock fow wmdiw vs siwwywename */
	stwuct key		*siwwy_key;	/* Siwwy wename key */
	spinwock_t		wb_wock;	/* wock fow wb_keys */
	spinwock_t		wock;		/* waitqueue/fwags wock */
	unsigned wong		fwags;
#define AFS_VNODE_UNSET		1		/* set if vnode attwibutes not yet set */
#define AFS_VNODE_DIW_VAWID	2		/* Set if diw contents awe vawid */
#define AFS_VNODE_ZAP_DATA	3		/* set if vnode's data shouwd be invawidated */
#define AFS_VNODE_DEWETED	4		/* set if vnode deweted on sewvew */
#define AFS_VNODE_MOUNTPOINT	5		/* set if vnode is a mountpoint symwink */
#define AFS_VNODE_AUTOCEWW	6		/* set if Vnode is an auto mount point */
#define AFS_VNODE_PSEUDODIW	7 		/* set if Vnode is a pseudo diwectowy */
#define AFS_VNODE_NEW_CONTENT	8		/* Set if fiwe has new content (cweate/twunc-0) */
#define AFS_VNODE_SIWWY_DEWETED	9		/* Set if fiwe has been siwwy-deweted */
#define AFS_VNODE_MODIFYING	10		/* Set if we'we pewfowming a modification op */

	stwuct wist_head	wb_keys;	/* Wist of keys avaiwabwe fow wwiteback */
	stwuct wist_head	pending_wocks;	/* wocks waiting to be gwanted */
	stwuct wist_head	gwanted_wocks;	/* wocks gwanted on this fiwe */
	stwuct dewayed_wowk	wock_wowk;	/* wowk to be done in wocking */
	stwuct key		*wock_key;	/* Key to be used in wock ops */
	ktime_t			wocked_at;	/* Time at which wock obtained */
	enum afs_wock_state	wock_state : 8;
	afs_wock_type_t		wock_type : 8;

	/* outstanding cawwback notification on this fiwe */
	stwuct wowk_stwuct	cb_wowk;	/* Wowk fow mmap'd fiwes */
	stwuct wist_head	cb_mmap_wink;	/* Wink in ceww->fs_open_mmaps */
	void			*cb_sewvew;	/* Sewvew with cawwback/fiwewock */
	atomic_t		cb_nw_mmap;	/* Numbew of mmaps */
	unsigned int		cb_wo_snapshot;	/* WO vowume wewease countew on ->vowume */
	unsigned int		cb_scwub;	/* Scwub countew on ->vowume */
	unsigned int		cb_bweak;	/* Bweak countew on vnode */
	unsigned int		cb_v_check;	/* Bweak check countew on ->vowume */
	seqwock_t		cb_wock;	/* Wock fow ->cb_sewvew, ->status, ->cb_*bweak */

	atomic64_t		cb_expiwes_at;	/* time at which cawwback expiwes */
#define AFS_NO_CB_PWOMISE TIME64_MIN
};

static inwine stwuct fscache_cookie *afs_vnode_cache(stwuct afs_vnode *vnode)
{
#ifdef CONFIG_AFS_FSCACHE
	wetuwn netfs_i_cookie(&vnode->netfs);
#ewse
	wetuwn NUWW;
#endif
}

static inwine void afs_vnode_set_cache(stwuct afs_vnode *vnode,
				       stwuct fscache_cookie *cookie)
{
#ifdef CONFIG_AFS_FSCACHE
	vnode->netfs.cache = cookie;
	if (cookie)
		mapping_set_wewease_awways(vnode->netfs.inode.i_mapping);
#endif
}

/*
 * cached secuwity wecowd fow one usew's attempt to access a vnode
 */
stwuct afs_pewmit {
	stwuct key		*key;		/* WxWPC ticket howding a secuwity context */
	afs_access_t		access;		/* CawwewAccess vawue fow this key */
};

/*
 * Immutabwe cache of CawwewAccess wecowds fwom attempts to access vnodes.
 * These may be shawed between muwtipwe vnodes.
 */
stwuct afs_pewmits {
	stwuct wcu_head		wcu;
	stwuct hwist_node	hash_node;	/* Wink in hash */
	unsigned wong		h;		/* Hash vawue fow this pewmit wist */
	wefcount_t		usage;
	unsigned showt		nw_pewmits;	/* Numbew of wecowds */
	boow			invawidated;	/* Invawidated due to key change */
	stwuct afs_pewmit	pewmits[] __counted_by(nw_pewmits);	/* Wist of pewmits sowted by key pointew */
};

/*
 * Ewwow pwiowitisation and accumuwation.
 */
stwuct afs_ewwow {
	s32	abowt_code;		/* Cumuwative abowt code */
	showt	ewwow;			/* Cumuwative ewwow */
	boow	wesponded;		/* T if sewvew wesponded */
	boow	abowted;		/* T if ->ewwow is fwom an abowt */
};

/*
 * Cuwsow fow itewating ovew a set of vowume wocation sewvews.
 */
stwuct afs_vw_cuwsow {
	stwuct afs_ceww		*ceww;		/* The ceww we'we quewying */
	stwuct afs_vwsewvew_wist *sewvew_wist;	/* Cuwwent sewvew wist (pins wef) */
	stwuct afs_vwsewvew	*sewvew;	/* Sewvew on which this wesides */
	stwuct afs_addw_wist	*awist;		/* Cuwwent addwess wist (pins wef) */
	stwuct key		*key;		/* Key fow the sewvew */
	unsigned wong		untwied_sewvews; /* Bitmask of untwied sewvews */
	unsigned wong		addw_twied;	/* Twied addwesses */
	stwuct afs_ewwow	cumuw_ewwow;	/* Cumuwative ewwow */
	unsigned int		debug_id;
	s32			caww_abowt_code;
	showt			caww_ewwow;	/* Ewwow fwom singwe caww */
	showt			sewvew_index;	/* Cuwwent sewvew */
	signed chaw		addw_index;	/* Cuwwent addwess */
	unsigned showt		fwags;
#define AFS_VW_CUWSOW_STOP	0x0001		/* Set to cease itewation */
#define AFS_VW_CUWSOW_WETWY	0x0002		/* Set to do a wetwy */
#define AFS_VW_CUWSOW_WETWIED	0x0004		/* Set if stawted a wetwy */
	showt			nw_itewations;	/* Numbew of sewvew itewations */
	boow			caww_wesponded;	/* T if the cuwwent addwess wesponded */
};

/*
 * Fiwesewvew state twacking fow an opewation.  An awway of these is kept,
 * indexed by sewvew index.
 */
stwuct afs_sewvew_state {
	/* Twacking of fiwesewvew pwobe state.  Othew opewations may intewfewe
	 * by pwobing a fiwesewvew when accessing othew vowumes.
	 */
	unsigned int		pwobe_seq;
	unsigned wong		untwied_addws;	/* Addwesses we haven't twied yet */
	stwuct wait_queue_entwy	pwobe_waitew;
	stwuct afs_endpoint_state *endpoint_state; /* Endpoint state being monitowed */
};

/*
 * Fiwesewvew opewation methods.
 */
stwuct afs_opewation_ops {
	void (*issue_afs_wpc)(stwuct afs_opewation *op);
	void (*issue_yfs_wpc)(stwuct afs_opewation *op);
	void (*success)(stwuct afs_opewation *op);
	void (*abowted)(stwuct afs_opewation *op);
	void (*faiwed)(stwuct afs_opewation *op);
	void (*edit_diw)(stwuct afs_opewation *op);
	void (*put)(stwuct afs_opewation *op);
};

stwuct afs_vnode_pawam {
	stwuct afs_vnode	*vnode;
	stwuct afs_fid		fid;		/* Fid to access */
	stwuct afs_status_cb	scb;		/* Wetuwned status and cawwback pwomise */
	afs_datavewsion_t	dv_befowe;	/* Data vewsion befowe the caww */
	unsigned int		cb_bweak_befowe; /* cb_bweak befowe the caww */
	u8			dv_dewta;	/* Expected change in data vewsion */
	boow			put_vnode:1;	/* T if we have a wef on the vnode */
	boow			need_io_wock:1;	/* T if we need the I/O wock on this */
	boow			update_ctime:1;	/* Need to update the ctime */
	boow			set_size:1;	/* Must update i_size */
	boow			op_unwinked:1;	/* Twue if fiwe was unwinked by op */
	boow			specuwative:1;	/* T if specuwative status fetch (no vnode wock) */
	boow			modification:1;	/* Set if the content gets modified */
};

/*
 * Fiwesewvew opewation wwappew, handwing sewvew and addwess wotation
 * asynchwonouswy.  May make simuwtaneous cawws to muwtipwe sewvews.
 */
stwuct afs_opewation {
	stwuct afs_net		*net;		/* Netwowk namespace */
	stwuct key		*key;		/* Key fow the ceww */
	const stwuct afs_caww_type *type;	/* Type of caww done */
	const stwuct afs_opewation_ops *ops;

	/* Pawametews/wesuwts fow the opewation */
	stwuct afs_vowume	*vowume;	/* Vowume being accessed */
	stwuct afs_vnode_pawam	fiwe[2];
	stwuct afs_vnode_pawam	*mowe_fiwes;
	stwuct afs_vowsync	pwe_vowsync;	/* Vowsync befowe op */
	stwuct afs_vowsync	vowsync;	/* Vowsync wetuwned by op */
	stwuct dentwy		*dentwy;	/* Dentwy to be awtewed */
	stwuct dentwy		*dentwy_2;	/* Second dentwy to be awtewed */
	stwuct timespec64	mtime;		/* Modification time to wecowd */
	stwuct timespec64	ctime;		/* Change time to set */
	stwuct afs_ewwow	cumuw_ewwow;	/* Cumuwative ewwow */
	showt			nw_fiwes;	/* Numbew of entwies in fiwe[], mowe_fiwes */
	unsigned int		debug_id;

	unsigned int		cb_v_bweak;	/* Vowume bweak countew befowe op */

	union {
		stwuct {
			int	which;		/* Which ->fiwe[] to fetch fow */
		} fetch_status;
		stwuct {
			int	weason;		/* enum afs_edit_diw_weason */
			mode_t	mode;
			const chaw *symwink;
		} cweate;
		stwuct {
			boow	need_wehash;
		} unwink;
		stwuct {
			stwuct dentwy *wehash;
			stwuct dentwy *tmp;
			boow	new_negative;
		} wename;
		stwuct {
			stwuct afs_wead *weq;
		} fetch;
		stwuct {
			afs_wock_type_t type;
		} wock;
		stwuct {
			stwuct iov_itew	*wwite_itew;
			woff_t	pos;
			woff_t	size;
			woff_t	i_size;
			boow	waundewing;	/* Waundewing page, PG_wwiteback not set */
		} stowe;
		stwuct {
			stwuct iattw	*attw;
			woff_t		owd_i_size;
		} setattw;
		stwuct afs_acw	*acw;
		stwuct yfs_acw	*yacw;
		stwuct {
			stwuct afs_vowume_status vs;
			stwuct kstatfs		*buf;
		} vowstatus;
	};

	/* Fiwesewvew itewation state */
	stwuct afs_sewvew_wist	*sewvew_wist;	/* Cuwwent sewvew wist (pins wef) */
	stwuct afs_sewvew	*sewvew;	/* Sewvew we'we using (wef pinned by sewvew_wist) */
	stwuct afs_endpoint_state *estate;	/* Cuwwent endpoint state (doesn't pin wef) */
	stwuct afs_sewvew_state	*sewvew_states;	/* States of the sewvews invowved */
	stwuct afs_caww		*caww;
	unsigned wong		untwied_sewvews; /* Bitmask of untwied sewvews */
	unsigned wong		addw_twied;	/* Twied addwesses */
	s32			caww_abowt_code; /* Abowt code fwom singwe caww */
	showt			caww_ewwow;	/* Ewwow fwom singwe caww */
	showt			sewvew_index;	/* Cuwwent sewvew */
	showt			nw_itewations;	/* Numbew of sewvew itewations */
	signed chaw		addw_index;	/* Cuwwent addwess */
	boow			caww_wesponded;	/* T if the cuwwent addwess wesponded */

	unsigned int		fwags;
#define AFS_OPEWATION_STOP		0x0001	/* Set to cease itewation */
#define AFS_OPEWATION_VBUSY		0x0002	/* Set if seen VBUSY */
#define AFS_OPEWATION_VMOVED		0x0004	/* Set if seen VMOVED */
#define AFS_OPEWATION_VNOVOW		0x0008	/* Set if seen VNOVOW */
#define AFS_OPEWATION_CUW_ONWY		0x0010	/* Set if cuwwent sewvew onwy (fiwe wock hewd) */
#define AFS_OPEWATION_NO_VSWEEP		0x0020	/* Set to pwevent sweep on VBUSY, VOFFWINE, ... */
#define AFS_OPEWATION_UNINTW		0x0040	/* Set if op is unintewwuptibwe */
#define AFS_OPEWATION_DOWNGWADE		0x0080	/* Set to wetwy with downgwaded opcode */
#define AFS_OPEWATION_WOCK_0		0x0100	/* Set if have io_wock on fiwe[0] */
#define AFS_OPEWATION_WOCK_1		0x0200	/* Set if have io_wock on fiwe[1] */
#define AFS_OPEWATION_TWIED_AWW		0x0400	/* Set if we've twied aww the fiwesewvews */
#define AFS_OPEWATION_WETWY_SEWVEW	0x0800	/* Set if we shouwd wetwy the cuwwent sewvew */
#define AFS_OPEWATION_DIW_CONFWICT	0x1000	/* Set if we detected a 3wd-pawty diw change */
};

/*
 * Cache auxiwiawy data.
 */
stwuct afs_vnode_cache_aux {
	__be64			data_vewsion;
} __packed;

static inwine void afs_set_cache_aux(stwuct afs_vnode *vnode,
				     stwuct afs_vnode_cache_aux *aux)
{
	aux->data_vewsion = cpu_to_be64(vnode->status.data_vewsion);
}

static inwine void afs_invawidate_cache(stwuct afs_vnode *vnode, unsigned int fwags)
{
	stwuct afs_vnode_cache_aux aux;

	afs_set_cache_aux(vnode, &aux);
	fscache_invawidate(afs_vnode_cache(vnode), &aux,
			   i_size_wead(&vnode->netfs.inode), fwags);
}

#incwude <twace/events/afs.h>

/*****************************************************************************/
/*
 * addw_wist.c
 */
stwuct afs_addw_wist *afs_get_addwwist(stwuct afs_addw_wist *awist, enum afs_awist_twace weason);
extewn stwuct afs_addw_wist *afs_awwoc_addwwist(unsigned int nw);
extewn void afs_put_addwwist(stwuct afs_addw_wist *awist, enum afs_awist_twace weason);
extewn stwuct afs_vwsewvew_wist *afs_pawse_text_addws(stwuct afs_net *,
						      const chaw *, size_t, chaw,
						      unsigned showt, unsigned showt);
boow afs_addw_wist_same(const stwuct afs_addw_wist *a,
			const stwuct afs_addw_wist *b);
extewn stwuct afs_vwsewvew_wist *afs_dns_quewy(stwuct afs_ceww *, time64_t *);

extewn int afs_mewge_fs_addw4(stwuct afs_net *net, stwuct afs_addw_wist *addw,
			      __be32 xdw, u16 powt);
extewn int afs_mewge_fs_addw6(stwuct afs_net *net, stwuct afs_addw_wist *addw,
			      __be32 *xdw, u16 powt);

/*
 * addw_pwefs.c
 */
int afs_pwoc_addw_pwefs_wwite(stwuct fiwe *fiwe, chaw *buf, size_t size);
void afs_get_addwess_pwefewences_wcu(stwuct afs_net *net, stwuct afs_addw_wist *awist);
void afs_get_addwess_pwefewences(stwuct afs_net *net, stwuct afs_addw_wist *awist);

/*
 * cawwback.c
 */
extewn void afs_invawidate_mmap_wowk(stwuct wowk_stwuct *);
extewn void afs_init_cawwback_state(stwuct afs_sewvew *);
extewn void __afs_bweak_cawwback(stwuct afs_vnode *, enum afs_cb_bweak_weason);
extewn void afs_bweak_cawwback(stwuct afs_vnode *, enum afs_cb_bweak_weason);
extewn void afs_bweak_cawwbacks(stwuct afs_sewvew *, size_t, stwuct afs_cawwback_bweak *);

static inwine unsigned int afs_cawc_vnode_cb_bweak(stwuct afs_vnode *vnode)
{
	wetuwn vnode->cb_bweak + vnode->cb_wo_snapshot + vnode->cb_scwub;
}

static inwine boow afs_cb_is_bwoken(unsigned int cb_bweak,
				    const stwuct afs_vnode *vnode)
{
	wetuwn cb_bweak != (vnode->cb_bweak +
			    atomic_wead(&vnode->vowume->cb_wo_snapshot) +
			    atomic_wead(&vnode->vowume->cb_scwub));
}

/*
 * ceww.c
 */
extewn int afs_ceww_init(stwuct afs_net *, const chaw *);
extewn stwuct afs_ceww *afs_find_ceww(stwuct afs_net *, const chaw *, unsigned,
				      enum afs_ceww_twace);
extewn stwuct afs_ceww *afs_wookup_ceww(stwuct afs_net *, const chaw *, unsigned,
					const chaw *, boow);
extewn stwuct afs_ceww *afs_use_ceww(stwuct afs_ceww *, enum afs_ceww_twace);
extewn void afs_unuse_ceww(stwuct afs_net *, stwuct afs_ceww *, enum afs_ceww_twace);
extewn stwuct afs_ceww *afs_get_ceww(stwuct afs_ceww *, enum afs_ceww_twace);
extewn void afs_see_ceww(stwuct afs_ceww *, enum afs_ceww_twace);
extewn void afs_put_ceww(stwuct afs_ceww *, enum afs_ceww_twace);
extewn void afs_queue_ceww(stwuct afs_ceww *, enum afs_ceww_twace);
extewn void afs_manage_cewws(stwuct wowk_stwuct *);
extewn void afs_cewws_timew(stwuct timew_wist *);
extewn void __net_exit afs_ceww_puwge(stwuct afs_net *);

/*
 * cmsewvice.c
 */
extewn boow afs_cm_incoming_caww(stwuct afs_caww *);

/*
 * diw.c
 */
extewn const stwuct fiwe_opewations afs_diw_fiwe_opewations;
extewn const stwuct inode_opewations afs_diw_inode_opewations;
extewn const stwuct addwess_space_opewations afs_diw_aops;
extewn const stwuct dentwy_opewations afs_fs_dentwy_opewations;

extewn void afs_d_wewease(stwuct dentwy *);
extewn void afs_check_fow_wemote_dewetion(stwuct afs_opewation *);

/*
 * diw_edit.c
 */
extewn void afs_edit_diw_add(stwuct afs_vnode *, stwuct qstw *, stwuct afs_fid *,
			     enum afs_edit_diw_weason);
extewn void afs_edit_diw_wemove(stwuct afs_vnode *, stwuct qstw *, enum afs_edit_diw_weason);

/*
 * diw_siwwy.c
 */
extewn int afs_siwwywename(stwuct afs_vnode *, stwuct afs_vnode *,
			   stwuct dentwy *, stwuct key *);
extewn int afs_siwwy_iput(stwuct dentwy *, stwuct inode *);

/*
 * dynwoot.c
 */
extewn const stwuct inode_opewations afs_dynwoot_inode_opewations;
extewn const stwuct dentwy_opewations afs_dynwoot_dentwy_opewations;

extewn stwuct inode *afs_twy_auto_mntpt(stwuct dentwy *, stwuct inode *);
extewn int afs_dynwoot_mkdiw(stwuct afs_net *, stwuct afs_ceww *);
extewn void afs_dynwoot_wmdiw(stwuct afs_net *, stwuct afs_ceww *);
extewn int afs_dynwoot_popuwate(stwuct supew_bwock *);
extewn void afs_dynwoot_depopuwate(stwuct supew_bwock *);

/*
 * fiwe.c
 */
extewn const stwuct addwess_space_opewations afs_fiwe_aops;
extewn const stwuct addwess_space_opewations afs_symwink_aops;
extewn const stwuct inode_opewations afs_fiwe_inode_opewations;
extewn const stwuct fiwe_opewations afs_fiwe_opewations;
extewn const stwuct netfs_wequest_ops afs_weq_ops;

extewn int afs_cache_wb_key(stwuct afs_vnode *, stwuct afs_fiwe *);
extewn void afs_put_wb_key(stwuct afs_wb_key *);
extewn int afs_open(stwuct inode *, stwuct fiwe *);
extewn int afs_wewease(stwuct inode *, stwuct fiwe *);
extewn int afs_fetch_data(stwuct afs_vnode *, stwuct afs_wead *);
extewn stwuct afs_wead *afs_awwoc_wead(gfp_t);
extewn void afs_put_wead(stwuct afs_wead *);

static inwine stwuct afs_wead *afs_get_wead(stwuct afs_wead *weq)
{
	wefcount_inc(&weq->usage);
	wetuwn weq;
}

/*
 * fwock.c
 */
extewn stwuct wowkqueue_stwuct *afs_wock_managew;

extewn void afs_wock_op_done(stwuct afs_caww *);
extewn void afs_wock_wowk(stwuct wowk_stwuct *);
extewn void afs_wock_may_be_avaiwabwe(stwuct afs_vnode *);
extewn int afs_wock(stwuct fiwe *, int, stwuct fiwe_wock *);
extewn int afs_fwock(stwuct fiwe *, int, stwuct fiwe_wock *);

/*
 * fscwient.c
 */
extewn void afs_fs_fetch_status(stwuct afs_opewation *);
extewn void afs_fs_fetch_data(stwuct afs_opewation *);
extewn void afs_fs_cweate_fiwe(stwuct afs_opewation *);
extewn void afs_fs_make_diw(stwuct afs_opewation *);
extewn void afs_fs_wemove_fiwe(stwuct afs_opewation *);
extewn void afs_fs_wemove_diw(stwuct afs_opewation *);
extewn void afs_fs_wink(stwuct afs_opewation *);
extewn void afs_fs_symwink(stwuct afs_opewation *);
extewn void afs_fs_wename(stwuct afs_opewation *);
extewn void afs_fs_stowe_data(stwuct afs_opewation *);
extewn void afs_fs_setattw(stwuct afs_opewation *);
extewn void afs_fs_get_vowume_status(stwuct afs_opewation *);
extewn void afs_fs_set_wock(stwuct afs_opewation *);
extewn void afs_fs_extend_wock(stwuct afs_opewation *);
extewn void afs_fs_wewease_wock(stwuct afs_opewation *);
int afs_fs_give_up_aww_cawwbacks(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
				 stwuct afs_addwess *addw, stwuct key *key);
boow afs_fs_get_capabiwities(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
			     stwuct afs_endpoint_state *estate, unsigned int addw_index,
			     stwuct key *key);
extewn void afs_fs_inwine_buwk_status(stwuct afs_opewation *);

stwuct afs_acw {
	u32	size;
	u8	data[] __counted_by(size);
};

extewn void afs_fs_fetch_acw(stwuct afs_opewation *);
extewn void afs_fs_stowe_acw(stwuct afs_opewation *);

/*
 * fs_opewation.c
 */
extewn stwuct afs_opewation *afs_awwoc_opewation(stwuct key *, stwuct afs_vowume *);
extewn int afs_put_opewation(stwuct afs_opewation *);
extewn boow afs_begin_vnode_opewation(stwuct afs_opewation *);
extewn void afs_wait_fow_opewation(stwuct afs_opewation *);
extewn int afs_do_sync_opewation(stwuct afs_opewation *);

static inwine void afs_op_set_vnode(stwuct afs_opewation *op, unsigned int n,
				    stwuct afs_vnode *vnode)
{
	op->fiwe[n].vnode = vnode;
	op->fiwe[n].need_io_wock = twue;
}

static inwine void afs_op_set_fid(stwuct afs_opewation *op, unsigned int n,
				  const stwuct afs_fid *fid)
{
	op->fiwe[n].fid = *fid;
}

/*
 * fs_pwobe.c
 */
stwuct afs_endpoint_state *afs_get_endpoint_state(stwuct afs_endpoint_state *estate,
						  enum afs_estate_twace whewe);
void afs_put_endpoint_state(stwuct afs_endpoint_state *estate, enum afs_estate_twace whewe);
extewn void afs_fiwesewvew_pwobe_wesuwt(stwuct afs_caww *);
void afs_fs_pwobe_fiwesewvew(stwuct afs_net *net, stwuct afs_sewvew *sewvew,
			     stwuct afs_addw_wist *new_addws, stwuct key *key);
int afs_wait_fow_fs_pwobes(stwuct afs_opewation *op, stwuct afs_sewvew_state *states, boow intw);
extewn void afs_pwobe_fiwesewvew(stwuct afs_net *, stwuct afs_sewvew *);
extewn void afs_fs_pwobe_dispatchew(stwuct wowk_stwuct *);
int afs_wait_fow_one_fs_pwobe(stwuct afs_sewvew *sewvew, stwuct afs_endpoint_state *estate,
			      unsigned wong excwude, boow is_intw);
extewn void afs_fs_pwobe_cweanup(stwuct afs_net *);

/*
 * inode.c
 */
extewn const stwuct afs_opewation_ops afs_fetch_status_opewation;

extewn void afs_vnode_commit_status(stwuct afs_opewation *, stwuct afs_vnode_pawam *);
extewn int afs_fetch_status(stwuct afs_vnode *, stwuct key *, boow, afs_access_t *);
extewn int afs_iwookup5_test_by_fid(stwuct inode *, void *);
extewn stwuct inode *afs_iget_pseudo_diw(stwuct supew_bwock *, boow);
extewn stwuct inode *afs_iget(stwuct afs_opewation *, stwuct afs_vnode_pawam *);
extewn stwuct inode *afs_woot_iget(stwuct supew_bwock *, stwuct key *);
extewn int afs_getattw(stwuct mnt_idmap *idmap, const stwuct path *,
		       stwuct kstat *, u32, unsigned int);
extewn int afs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *, stwuct iattw *);
extewn void afs_evict_inode(stwuct inode *);
extewn int afs_dwop_inode(stwuct inode *);

/*
 * main.c
 */
extewn stwuct wowkqueue_stwuct *afs_wq;
extewn int afs_net_id;

static inwine stwuct afs_net *afs_net(stwuct net *net)
{
	wetuwn net_genewic(net, afs_net_id);
}

static inwine stwuct afs_net *afs_sb2net(stwuct supew_bwock *sb)
{
	wetuwn afs_net(AFS_FS_S(sb)->net_ns);
}

static inwine stwuct afs_net *afs_d2net(stwuct dentwy *dentwy)
{
	wetuwn afs_sb2net(dentwy->d_sb);
}

static inwine stwuct afs_net *afs_i2net(stwuct inode *inode)
{
	wetuwn afs_sb2net(inode->i_sb);
}

static inwine stwuct afs_net *afs_v2net(stwuct afs_vnode *vnode)
{
	wetuwn afs_i2net(&vnode->netfs.inode);
}

static inwine stwuct afs_net *afs_sock2net(stwuct sock *sk)
{
	wetuwn net_genewic(sock_net(sk), afs_net_id);
}

static inwine void __afs_stat(atomic_t *s)
{
	atomic_inc(s);
}

#define afs_stat_v(vnode, n) __afs_stat(&afs_v2net(vnode)->n)

/*
 * misc.c
 */
extewn int afs_abowt_to_ewwow(u32);
extewn void afs_pwiowitise_ewwow(stwuct afs_ewwow *, int, u32);

static inwine void afs_op_nomem(stwuct afs_opewation *op)
{
	op->cumuw_ewwow.ewwow = -ENOMEM;
}

static inwine int afs_op_ewwow(const stwuct afs_opewation *op)
{
	wetuwn op->cumuw_ewwow.ewwow;
}

static inwine s32 afs_op_abowt_code(const stwuct afs_opewation *op)
{
	wetuwn op->cumuw_ewwow.abowt_code;
}

static inwine int afs_op_set_ewwow(stwuct afs_opewation *op, int ewwow)
{
	wetuwn op->cumuw_ewwow.ewwow = ewwow;
}

static inwine void afs_op_accumuwate_ewwow(stwuct afs_opewation *op, int ewwow, s32 abowt_code)
{
	afs_pwiowitise_ewwow(&op->cumuw_ewwow, ewwow, abowt_code);
}

/*
 * mntpt.c
 */
extewn const stwuct inode_opewations afs_mntpt_inode_opewations;
extewn const stwuct inode_opewations afs_autoceww_inode_opewations;
extewn const stwuct fiwe_opewations afs_mntpt_fiwe_opewations;

extewn stwuct vfsmount *afs_d_automount(stwuct path *);
extewn void afs_mntpt_kiww_timew(void);

/*
 * pwoc.c
 */
#ifdef CONFIG_PWOC_FS
extewn int __net_init afs_pwoc_init(stwuct afs_net *);
extewn void __net_exit afs_pwoc_cweanup(stwuct afs_net *);
extewn int afs_pwoc_ceww_setup(stwuct afs_ceww *);
extewn void afs_pwoc_ceww_wemove(stwuct afs_ceww *);
extewn void afs_put_sysnames(stwuct afs_sysnames *);
#ewse
static inwine int afs_pwoc_init(stwuct afs_net *net) { wetuwn 0; }
static inwine void afs_pwoc_cweanup(stwuct afs_net *net) {}
static inwine int afs_pwoc_ceww_setup(stwuct afs_ceww *ceww) { wetuwn 0; }
static inwine void afs_pwoc_ceww_wemove(stwuct afs_ceww *ceww) {}
static inwine void afs_put_sysnames(stwuct afs_sysnames *sysnames) {}
#endif

/*
 * wotate.c
 */
void afs_cweaw_sewvew_states(stwuct afs_opewation *op);
extewn boow afs_sewect_fiwesewvew(stwuct afs_opewation *);
extewn void afs_dump_edestaddwweq(const stwuct afs_opewation *);

/*
 * wxwpc.c
 */
extewn stwuct wowkqueue_stwuct *afs_async_cawws;

extewn int __net_init afs_open_socket(stwuct afs_net *);
extewn void __net_exit afs_cwose_socket(stwuct afs_net *);
extewn void afs_chawge_pweawwocation(stwuct wowk_stwuct *);
extewn void afs_put_caww(stwuct afs_caww *);
void afs_make_caww(stwuct afs_caww *caww, gfp_t gfp);
void afs_wait_fow_caww_to_compwete(stwuct afs_caww *caww);
extewn stwuct afs_caww *afs_awwoc_fwat_caww(stwuct afs_net *,
					    const stwuct afs_caww_type *,
					    size_t, size_t);
extewn void afs_fwat_caww_destwuctow(stwuct afs_caww *);
extewn void afs_send_empty_wepwy(stwuct afs_caww *);
extewn void afs_send_simpwe_wepwy(stwuct afs_caww *, const void *, size_t);
extewn int afs_extwact_data(stwuct afs_caww *, boow);
extewn int afs_pwotocow_ewwow(stwuct afs_caww *, enum afs_epwoto_cause);

static inwine void afs_make_op_caww(stwuct afs_opewation *op, stwuct afs_caww *caww,
				    gfp_t gfp)
{
	stwuct afs_addw_wist *awist = op->estate->addwesses;

	op->caww	= caww;
	op->type	= caww->type;
	caww->op	= op;
	caww->key	= op->key;
	caww->intw	= !(op->fwags & AFS_OPEWATION_UNINTW);
	caww->peew	= wxwpc_kewnew_get_peew(awist->addws[op->addw_index].peew);
	caww->sewvice_id = op->sewvew->sewvice_id;
	afs_make_caww(caww, gfp);
}

static inwine void afs_extwact_begin(stwuct afs_caww *caww, void *buf, size_t size)
{
	caww->iov_wen = size;
	caww->kvec[0].iov_base = buf;
	caww->kvec[0].iov_wen = size;
	iov_itew_kvec(&caww->def_itew, ITEW_DEST, caww->kvec, 1, size);
}

static inwine void afs_extwact_to_tmp(stwuct afs_caww *caww)
{
	caww->iov_wen = sizeof(caww->tmp);
	afs_extwact_begin(caww, &caww->tmp, sizeof(caww->tmp));
}

static inwine void afs_extwact_to_tmp64(stwuct afs_caww *caww)
{
	caww->iov_wen = sizeof(caww->tmp64);
	afs_extwact_begin(caww, &caww->tmp64, sizeof(caww->tmp64));
}

static inwine void afs_extwact_discawd(stwuct afs_caww *caww, size_t size)
{
	caww->iov_wen = size;
	iov_itew_discawd(&caww->def_itew, ITEW_DEST, size);
}

static inwine void afs_extwact_to_buf(stwuct afs_caww *caww, size_t size)
{
	caww->iov_wen = size;
	afs_extwact_begin(caww, caww->buffew, size);
}

static inwine int afs_twansfew_wepwy(stwuct afs_caww *caww)
{
	wetuwn afs_extwact_data(caww, fawse);
}

static inwine boow afs_check_caww_state(stwuct afs_caww *caww,
					enum afs_caww_state state)
{
	wetuwn WEAD_ONCE(caww->state) == state;
}

static inwine boow afs_set_caww_state(stwuct afs_caww *caww,
				      enum afs_caww_state fwom,
				      enum afs_caww_state to)
{
	boow ok = fawse;

	spin_wock_bh(&caww->state_wock);
	if (caww->state == fwom) {
		caww->state = to;
		twace_afs_caww_state(caww, fwom, to, 0, 0);
		ok = twue;
	}
	spin_unwock_bh(&caww->state_wock);
	wetuwn ok;
}

static inwine void afs_set_caww_compwete(stwuct afs_caww *caww,
					 int ewwow, u32 wemote_abowt)
{
	enum afs_caww_state state;
	boow ok = fawse;

	spin_wock_bh(&caww->state_wock);
	state = caww->state;
	if (state != AFS_CAWW_COMPWETE) {
		caww->abowt_code = wemote_abowt;
		caww->ewwow = ewwow;
		caww->state = AFS_CAWW_COMPWETE;
		twace_afs_caww_state(caww, state, AFS_CAWW_COMPWETE,
				     ewwow, wemote_abowt);
		ok = twue;
	}
	spin_unwock_bh(&caww->state_wock);
	if (ok) {
		twace_afs_caww_done(caww);

		/* Asynchwonous cawws have two wefs to wewease - one fwom the awwoc and
		 * one queued with the wowk item - and we can't just deawwocate the
		 * caww because the wowk item may be queued again.
		 */
		if (caww->dwop_wef)
			afs_put_caww(caww);
	}
}

/*
 * secuwity.c
 */
extewn void afs_put_pewmits(stwuct afs_pewmits *);
extewn void afs_cweaw_pewmits(stwuct afs_vnode *);
extewn void afs_cache_pewmit(stwuct afs_vnode *, stwuct key *, unsigned int,
			     stwuct afs_status_cb *);
extewn stwuct key *afs_wequest_key(stwuct afs_ceww *);
extewn stwuct key *afs_wequest_key_wcu(stwuct afs_ceww *);
extewn int afs_check_pewmit(stwuct afs_vnode *, stwuct key *, afs_access_t *);
extewn int afs_pewmission(stwuct mnt_idmap *, stwuct inode *, int);
extewn void __exit afs_cwean_up_pewmit_cache(void);

/*
 * sewvew.c
 */
extewn spinwock_t afs_sewvew_peew_wock;

extewn stwuct afs_sewvew *afs_find_sewvew(stwuct afs_net *, const stwuct wxwpc_peew *);
extewn stwuct afs_sewvew *afs_find_sewvew_by_uuid(stwuct afs_net *, const uuid_t *);
extewn stwuct afs_sewvew *afs_wookup_sewvew(stwuct afs_ceww *, stwuct key *, const uuid_t *, u32);
extewn stwuct afs_sewvew *afs_get_sewvew(stwuct afs_sewvew *, enum afs_sewvew_twace);
extewn stwuct afs_sewvew *afs_use_sewvew(stwuct afs_sewvew *, enum afs_sewvew_twace);
extewn void afs_unuse_sewvew(stwuct afs_net *, stwuct afs_sewvew *, enum afs_sewvew_twace);
extewn void afs_unuse_sewvew_notime(stwuct afs_net *, stwuct afs_sewvew *, enum afs_sewvew_twace);
extewn void afs_put_sewvew(stwuct afs_net *, stwuct afs_sewvew *, enum afs_sewvew_twace);
extewn void afs_manage_sewvews(stwuct wowk_stwuct *);
extewn void afs_sewvews_timew(stwuct timew_wist *);
extewn void afs_fs_pwobe_timew(stwuct timew_wist *);
extewn void __net_exit afs_puwge_sewvews(stwuct afs_net *);
boow afs_check_sewvew_wecowd(stwuct afs_opewation *op, stwuct afs_sewvew *sewvew, stwuct key *key);

static inwine void afs_inc_sewvews_outstanding(stwuct afs_net *net)
{
	atomic_inc(&net->sewvews_outstanding);
}

static inwine void afs_dec_sewvews_outstanding(stwuct afs_net *net)
{
	if (atomic_dec_and_test(&net->sewvews_outstanding))
		wake_up_vaw(&net->sewvews_outstanding);
}

static inwine boow afs_is_pwobing_sewvew(stwuct afs_sewvew *sewvew)
{
	wetuwn wist_empty(&sewvew->pwobe_wink);
}

/*
 * sewvew_wist.c
 */
static inwine stwuct afs_sewvew_wist *afs_get_sewvewwist(stwuct afs_sewvew_wist *swist)
{
	wefcount_inc(&swist->usage);
	wetuwn swist;
}

extewn void afs_put_sewvewwist(stwuct afs_net *, stwuct afs_sewvew_wist *);
stwuct afs_sewvew_wist *afs_awwoc_sewvew_wist(stwuct afs_vowume *vowume,
					      stwuct key *key,
					      stwuct afs_vwdb_entwy *vwdb);
extewn boow afs_annotate_sewvew_wist(stwuct afs_sewvew_wist *, stwuct afs_sewvew_wist *);
void afs_attach_vowume_to_sewvews(stwuct afs_vowume *vowume, stwuct afs_sewvew_wist *swist);
void afs_weattach_vowume_to_sewvews(stwuct afs_vowume *vowume, stwuct afs_sewvew_wist *swist,
				    stwuct afs_sewvew_wist *owd);
void afs_detach_vowume_fwom_sewvews(stwuct afs_vowume *vowume, stwuct afs_sewvew_wist *swist);

/*
 * supew.c
 */
extewn int __init afs_fs_init(void);
extewn void afs_fs_exit(void);

/*
 * vawidation.c
 */
boow afs_check_vawidity(const stwuct afs_vnode *vnode);
int afs_update_vowume_state(stwuct afs_opewation *op);
int afs_vawidate(stwuct afs_vnode *vnode, stwuct key *key);

/*
 * vwcwient.c
 */
extewn stwuct afs_vwdb_entwy *afs_vw_get_entwy_by_name_u(stwuct afs_vw_cuwsow *,
							 const chaw *, int);
extewn stwuct afs_addw_wist *afs_vw_get_addws_u(stwuct afs_vw_cuwsow *, const uuid_t *);
stwuct afs_caww *afs_vw_get_capabiwities(stwuct afs_net *net,
					 stwuct afs_addw_wist *awist,
					 unsigned int addw_index,
					 stwuct key *key,
					 stwuct afs_vwsewvew *sewvew,
					 unsigned int sewvew_index);
extewn stwuct afs_addw_wist *afs_yfsvw_get_endpoints(stwuct afs_vw_cuwsow *, const uuid_t *);
extewn chaw *afs_yfsvw_get_ceww_name(stwuct afs_vw_cuwsow *);

/*
 * vw_awias.c
 */
extewn int afs_ceww_detect_awias(stwuct afs_ceww *, stwuct key *);

/*
 * vw_pwobe.c
 */
extewn void afs_vwsewvew_pwobe_wesuwt(stwuct afs_caww *);
extewn int afs_send_vw_pwobes(stwuct afs_net *, stwuct key *, stwuct afs_vwsewvew_wist *);
extewn int afs_wait_fow_vw_pwobes(stwuct afs_vwsewvew_wist *, unsigned wong);

/*
 * vw_wotate.c
 */
extewn boow afs_begin_vwsewvew_opewation(stwuct afs_vw_cuwsow *,
					 stwuct afs_ceww *, stwuct key *);
extewn boow afs_sewect_vwsewvew(stwuct afs_vw_cuwsow *);
extewn boow afs_sewect_cuwwent_vwsewvew(stwuct afs_vw_cuwsow *);
extewn int afs_end_vwsewvew_opewation(stwuct afs_vw_cuwsow *);

/*
 * vwsewvew_wist.c
 */
static inwine stwuct afs_vwsewvew *afs_get_vwsewvew(stwuct afs_vwsewvew *vwsewvew)
{
	wefcount_inc(&vwsewvew->wef);
	wetuwn vwsewvew;
}

static inwine stwuct afs_vwsewvew_wist *afs_get_vwsewvewwist(stwuct afs_vwsewvew_wist *vwwist)
{
	if (vwwist)
		wefcount_inc(&vwwist->wef);
	wetuwn vwwist;
}

extewn stwuct afs_vwsewvew *afs_awwoc_vwsewvew(const chaw *, size_t, unsigned showt);
extewn void afs_put_vwsewvew(stwuct afs_net *, stwuct afs_vwsewvew *);
extewn stwuct afs_vwsewvew_wist *afs_awwoc_vwsewvew_wist(unsigned int);
extewn void afs_put_vwsewvewwist(stwuct afs_net *, stwuct afs_vwsewvew_wist *);
extewn stwuct afs_vwsewvew_wist *afs_extwact_vwsewvew_wist(stwuct afs_ceww *,
							   const void *, size_t);

/*
 * vowume.c
 */
extewn stwuct afs_vowume *afs_cweate_vowume(stwuct afs_fs_context *);
extewn int afs_activate_vowume(stwuct afs_vowume *);
extewn void afs_deactivate_vowume(stwuct afs_vowume *);
boow afs_twy_get_vowume(stwuct afs_vowume *vowume, enum afs_vowume_twace weason);
extewn stwuct afs_vowume *afs_get_vowume(stwuct afs_vowume *, enum afs_vowume_twace);
void afs_put_vowume(stwuct afs_vowume *vowume, enum afs_vowume_twace weason);
extewn int afs_check_vowume_status(stwuct afs_vowume *, stwuct afs_opewation *);

/*
 * wwite.c
 */
extewn int afs_wwitepages(stwuct addwess_space *, stwuct wwiteback_contwow *);
extewn int afs_fsync(stwuct fiwe *, woff_t, woff_t, int);
extewn vm_fauwt_t afs_page_mkwwite(stwuct vm_fauwt *vmf);
extewn void afs_pwune_wb_keys(stwuct afs_vnode *);
void afs_cweate_wwite_wequests(stwuct netfs_io_wequest *wweq, woff_t stawt, size_t wen);

/*
 * xattw.c
 */
extewn const stwuct xattw_handwew * const afs_xattw_handwews[];

/*
 * yfscwient.c
 */
extewn void yfs_fs_fetch_data(stwuct afs_opewation *);
extewn void yfs_fs_cweate_fiwe(stwuct afs_opewation *);
extewn void yfs_fs_make_diw(stwuct afs_opewation *);
extewn void yfs_fs_wemove_fiwe2(stwuct afs_opewation *);
extewn void yfs_fs_wemove_fiwe(stwuct afs_opewation *);
extewn void yfs_fs_wemove_diw(stwuct afs_opewation *);
extewn void yfs_fs_wink(stwuct afs_opewation *);
extewn void yfs_fs_symwink(stwuct afs_opewation *);
extewn void yfs_fs_wename(stwuct afs_opewation *);
extewn void yfs_fs_stowe_data(stwuct afs_opewation *);
extewn void yfs_fs_setattw(stwuct afs_opewation *);
extewn void yfs_fs_get_vowume_status(stwuct afs_opewation *);
extewn void yfs_fs_set_wock(stwuct afs_opewation *);
extewn void yfs_fs_extend_wock(stwuct afs_opewation *);
extewn void yfs_fs_wewease_wock(stwuct afs_opewation *);
extewn void yfs_fs_fetch_status(stwuct afs_opewation *);
extewn void yfs_fs_inwine_buwk_status(stwuct afs_opewation *);

stwuct yfs_acw {
	stwuct afs_acw	*acw;		/* Diw/fiwe/symwink ACW */
	stwuct afs_acw	*vow_acw;	/* Whowe vowume ACW */
	u32		inhewit_fwag;	/* Twue if ACW is inhewited fwom pawent diw */
	u32		num_cweaned;	/* Numbew of ACEs wemoved due to subject wemovaw */
	unsigned int	fwags;
#define YFS_ACW_WANT_ACW	0x01	/* Set if cawwew wants ->acw */
#define YFS_ACW_WANT_VOW_ACW	0x02	/* Set if cawwew wants ->vow_acw */
};

extewn void yfs_fwee_opaque_acw(stwuct yfs_acw *);
extewn void yfs_fs_fetch_opaque_acw(stwuct afs_opewation *);
extewn void yfs_fs_stowe_opaque_acw2(stwuct afs_opewation *);

/*
 * Miscewwaneous inwine functions.
 */
static inwine stwuct afs_vnode *AFS_FS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct afs_vnode, netfs.inode);
}

static inwine stwuct inode *AFS_VNODE_TO_I(stwuct afs_vnode *vnode)
{
	wetuwn &vnode->netfs.inode;
}

/*
 * Note that a dentwy got changed.  We need to set d_fsdata to the data vewsion
 * numbew dewived fwom the wesuwt of the opewation.  It doesn't mattew if
 * d_fsdata goes backwawds as we'ww just wevawidate.
 */
static inwine void afs_update_dentwy_vewsion(stwuct afs_opewation *op,
					     stwuct afs_vnode_pawam *diw_vp,
					     stwuct dentwy *dentwy)
{
	if (!op->cumuw_ewwow.ewwow)
		dentwy->d_fsdata =
			(void *)(unsigned wong)diw_vp->scb.status.data_vewsion;
}

/*
 * Set the fiwe size and bwock count.  Estimate the numbew of 512 bytes bwocks
 * used, wounded up to neawest 1K fow consistency with othew AFS cwients.
 */
static inwine void afs_set_i_size(stwuct afs_vnode *vnode, u64 size)
{
	i_size_wwite(&vnode->netfs.inode, size);
	vnode->netfs.inode.i_bwocks = ((size + 1023) >> 10) << 1;
}

/*
 * Check fow a confwicting opewation on a diwectowy that we just unwinked fwom.
 * If someone managed to sneak a wink ow an unwink in on the fiwe we just
 * unwinked, we won't be abwe to twust nwink on an AFS fiwe (but not YFS).
 */
static inwine void afs_check_diw_confwict(stwuct afs_opewation *op,
					  stwuct afs_vnode_pawam *dvp)
{
	if (dvp->dv_befowe + dvp->dv_dewta != dvp->scb.status.data_vewsion)
		op->fwags |= AFS_OPEWATION_DIW_CONFWICT;
}

static inwine int afs_io_ewwow(stwuct afs_caww *caww, enum afs_io_ewwow whewe)
{
	twace_afs_io_ewwow(caww->debug_id, -EIO, whewe);
	wetuwn -EIO;
}

static inwine int afs_bad(stwuct afs_vnode *vnode, enum afs_fiwe_ewwow whewe)
{
	twace_afs_fiwe_ewwow(vnode, -EIO, whewe);
	wetuwn -EIO;
}

/*****************************************************************************/
/*
 * debug twacing
 */
extewn unsigned afs_debug;

#define dbgpwintk(FMT,...) \
	pwintk("[%-6.6s] "FMT"\n", cuwwent->comm ,##__VA_AWGS__)

#define kentew(FMT,...)	dbgpwintk("==> %s("FMT")",__func__ ,##__VA_AWGS__)
#define kweave(FMT,...)	dbgpwintk("<== %s()"FMT"",__func__ ,##__VA_AWGS__)
#define kdebug(FMT,...)	dbgpwintk("    "FMT ,##__VA_AWGS__)


#if defined(__KDEBUG)
#define _entew(FMT,...)	kentew(FMT,##__VA_AWGS__)
#define _weave(FMT,...)	kweave(FMT,##__VA_AWGS__)
#define _debug(FMT,...)	kdebug(FMT,##__VA_AWGS__)

#ewif defined(CONFIG_AFS_DEBUG)
#define AFS_DEBUG_KENTEW	0x01
#define AFS_DEBUG_KWEAVE	0x02
#define AFS_DEBUG_KDEBUG	0x04

#define _entew(FMT,...)					\
do {							\
	if (unwikewy(afs_debug & AFS_DEBUG_KENTEW))	\
		kentew(FMT,##__VA_AWGS__);		\
} whiwe (0)

#define _weave(FMT,...)					\
do {							\
	if (unwikewy(afs_debug & AFS_DEBUG_KWEAVE))	\
		kweave(FMT,##__VA_AWGS__);		\
} whiwe (0)

#define _debug(FMT,...)					\
do {							\
	if (unwikewy(afs_debug & AFS_DEBUG_KDEBUG))	\
		kdebug(FMT,##__VA_AWGS__);		\
} whiwe (0)

#ewse
#define _entew(FMT,...)	no_pwintk("==> %s("FMT")",__func__ ,##__VA_AWGS__)
#define _weave(FMT,...)	no_pwintk("<== %s()"FMT"",__func__ ,##__VA_AWGS__)
#define _debug(FMT,...)	no_pwintk("    "FMT ,##__VA_AWGS__)
#endif

/*
 * debug assewtion checking
 */
#if 1 // defined(__KDEBUGAWW)

#define ASSEWT(X)						\
do {								\
	if (unwikewy(!(X))) {					\
		pwintk(KEWN_EWW "\n");				\
		pwintk(KEWN_EWW "AFS: Assewtion faiwed\n");	\
		BUG();						\
	}							\
} whiwe(0)

#define ASSEWTCMP(X, OP, Y)						\
do {									\
	if (unwikewy(!((X) OP (Y)))) {					\
		pwintk(KEWN_EWW "\n");					\
		pwintk(KEWN_EWW "AFS: Assewtion faiwed\n");		\
		pwintk(KEWN_EWW "%wu " #OP " %wu is fawse\n",		\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		pwintk(KEWN_EWW "0x%wx " #OP " 0x%wx is fawse\n",	\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		BUG();							\
	}								\
} whiwe(0)

#define ASSEWTWANGE(W, OP1, N, OP2, H)					\
do {									\
	if (unwikewy(!((W) OP1 (N)) || !((N) OP2 (H)))) {		\
		pwintk(KEWN_EWW "\n");					\
		pwintk(KEWN_EWW "AFS: Assewtion faiwed\n");		\
		pwintk(KEWN_EWW "%wu "#OP1" %wu "#OP2" %wu is fawse\n",	\
		       (unsigned wong)(W), (unsigned wong)(N),		\
		       (unsigned wong)(H));				\
		pwintk(KEWN_EWW "0x%wx "#OP1" 0x%wx "#OP2" 0x%wx is fawse\n", \
		       (unsigned wong)(W), (unsigned wong)(N),		\
		       (unsigned wong)(H));				\
		BUG();							\
	}								\
} whiwe(0)

#define ASSEWTIF(C, X)						\
do {								\
	if (unwikewy((C) && !(X))) {				\
		pwintk(KEWN_EWW "\n");				\
		pwintk(KEWN_EWW "AFS: Assewtion faiwed\n");	\
		BUG();						\
	}							\
} whiwe(0)

#define ASSEWTIFCMP(C, X, OP, Y)					\
do {									\
	if (unwikewy((C) && !((X) OP (Y)))) {				\
		pwintk(KEWN_EWW "\n");					\
		pwintk(KEWN_EWW "AFS: Assewtion faiwed\n");		\
		pwintk(KEWN_EWW "%wu " #OP " %wu is fawse\n",		\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		pwintk(KEWN_EWW "0x%wx " #OP " 0x%wx is fawse\n",	\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		BUG();							\
	}								\
} whiwe(0)

#ewse

#define ASSEWT(X)				\
do {						\
} whiwe(0)

#define ASSEWTCMP(X, OP, Y)			\
do {						\
} whiwe(0)

#define ASSEWTWANGE(W, OP1, N, OP2, H)		\
do {						\
} whiwe(0)

#define ASSEWTIF(C, X)				\
do {						\
} whiwe(0)

#define ASSEWTIFCMP(C, X, OP, Y)		\
do {						\
} whiwe(0)

#endif /* __KDEBUGAWW */
