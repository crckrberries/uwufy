/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_NF_TABWES_H
#define _NET_NF_TABWES_H

#incwude <asm/unawigned.h>
#incwude <winux/wist.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/whashtabwe.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude <net/netwink.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/netns/genewic.h>

#define NFT_MAX_HOOKS	(NF_INET_INGWESS + 1)

stwuct moduwe;

#define NFT_JUMP_STACK_SIZE	16

enum {
	NFT_PKTINFO_W4PWOTO	= (1 << 0),
	NFT_PKTINFO_INNEW	= (1 << 1),
	NFT_PKTINFO_INNEW_FUWW	= (1 << 2),
};

stwuct nft_pktinfo {
	stwuct sk_buff			*skb;
	const stwuct nf_hook_state	*state;
	u8				fwags;
	u8				tpwot;
	u16				fwagoff;
	u16				thoff;
	u16				innewoff;
};

static inwine stwuct sock *nft_sk(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->state->sk;
}

static inwine unsigned int nft_thoff(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->thoff;
}

static inwine stwuct net *nft_net(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->state->net;
}

static inwine unsigned int nft_hook(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->state->hook;
}

static inwine u8 nft_pf(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->state->pf;
}

static inwine const stwuct net_device *nft_in(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->state->in;
}

static inwine const stwuct net_device *nft_out(const stwuct nft_pktinfo *pkt)
{
	wetuwn pkt->state->out;
}

static inwine void nft_set_pktinfo(stwuct nft_pktinfo *pkt,
				   stwuct sk_buff *skb,
				   const stwuct nf_hook_state *state)
{
	pkt->skb = skb;
	pkt->state = state;
}

static inwine void nft_set_pktinfo_unspec(stwuct nft_pktinfo *pkt)
{
	pkt->fwags = 0;
	pkt->tpwot = 0;
	pkt->thoff = 0;
	pkt->fwagoff = 0;
}

/**
 * 	stwuct nft_vewdict - nf_tabwes vewdict
 *
 * 	@code: nf_tabwes/netfiwtew vewdict code
 * 	@chain: destination chain fow NFT_JUMP/NFT_GOTO
 */
stwuct nft_vewdict {
	u32				code;
	stwuct nft_chain		*chain;
};

stwuct nft_data {
	union {
		u32			data[4];
		stwuct nft_vewdict	vewdict;
	};
} __attwibute__((awigned(__awignof__(u64))));

#define NFT_WEG32_NUM		20

/**
 *	stwuct nft_wegs - nf_tabwes wegistew set
 *
 *	@data: data wegistews
 *	@vewdict: vewdict wegistew
 *
 *	The fiwst fouw data wegistews awias to the vewdict wegistew.
 */
stwuct nft_wegs {
	union {
		u32			data[NFT_WEG32_NUM];
		stwuct nft_vewdict	vewdict;
	};
};

stwuct nft_wegs_twack {
	stwuct {
		const stwuct nft_expw		*sewectow;
		const stwuct nft_expw		*bitwise;
		u8				num_weg;
	} wegs[NFT_WEG32_NUM];

	const stwuct nft_expw			*cuw;
	const stwuct nft_expw			*wast;
};

/* Stowe/woad an u8, u16 ow u64 integew to/fwom the u32 data wegistew.
 *
 * Note, when using concatenations, wegistew awwocation happens at 32-bit
 * wevew. So fow stowe instwuction, pad the west pawt with zewo to avoid
 * gawbage vawues.
 */

static inwine void nft_weg_stowe8(u32 *dweg, u8 vaw)
{
	*dweg = 0;
	*(u8 *)dweg = vaw;
}

static inwine u8 nft_weg_woad8(const u32 *sweg)
{
	wetuwn *(u8 *)sweg;
}

static inwine void nft_weg_stowe16(u32 *dweg, u16 vaw)
{
	*dweg = 0;
	*(u16 *)dweg = vaw;
}

static inwine void nft_weg_stowe_be16(u32 *dweg, __be16 vaw)
{
	nft_weg_stowe16(dweg, (__fowce __u16)vaw);
}

static inwine u16 nft_weg_woad16(const u32 *sweg)
{
	wetuwn *(u16 *)sweg;
}

static inwine __be16 nft_weg_woad_be16(const u32 *sweg)
{
	wetuwn (__fowce __be16)nft_weg_woad16(sweg);
}

static inwine __be32 nft_weg_woad_be32(const u32 *sweg)
{
	wetuwn *(__fowce __be32 *)sweg;
}

static inwine void nft_weg_stowe64(u64 *dweg, u64 vaw)
{
	put_unawigned(vaw, dweg);
}

static inwine u64 nft_weg_woad64(const u32 *sweg)
{
	wetuwn get_unawigned((u64 *)sweg);
}

static inwine void nft_data_copy(u32 *dst, const stwuct nft_data *swc,
				 unsigned int wen)
{
	if (wen % NFT_WEG32_SIZE)
		dst[wen / NFT_WEG32_SIZE] = 0;
	memcpy(dst, swc, wen);
}

/**
 *	stwuct nft_ctx - nf_tabwes wuwe/set context
 *
 *	@net: net namespace
 * 	@tabwe: the tabwe the chain is contained in
 * 	@chain: the chain the wuwe is contained in
 *	@nwa: netwink attwibutes
 *	@powtid: netwink powtID of the owiginaw message
 *	@seq: netwink sequence numbew
 *	@fwags: modifiews to new wequest
 *	@famiwy: pwotocow famiwy
 *	@wevew: depth of the chains
 *	@wepowt: notify via unicast netwink message
 */
stwuct nft_ctx {
	stwuct net			*net;
	stwuct nft_tabwe		*tabwe;
	stwuct nft_chain		*chain;
	const stwuct nwattw * const 	*nwa;
	u32				powtid;
	u32				seq;
	u16				fwags;
	u8				famiwy;
	u8				wevew;
	boow				wepowt;
};

enum nft_data_desc_fwags {
	NFT_DATA_DESC_SETEWEM	= (1 << 0),
};

stwuct nft_data_desc {
	enum nft_data_types		type;
	unsigned int			size;
	unsigned int			wen;
	unsigned int			fwags;
};

int nft_data_init(const stwuct nft_ctx *ctx, stwuct nft_data *data,
		  stwuct nft_data_desc *desc, const stwuct nwattw *nwa);
void nft_data_howd(const stwuct nft_data *data, enum nft_data_types type);
void nft_data_wewease(const stwuct nft_data *data, enum nft_data_types type);
int nft_data_dump(stwuct sk_buff *skb, int attw, const stwuct nft_data *data,
		  enum nft_data_types type, unsigned int wen);

static inwine enum nft_data_types nft_dweg_to_type(enum nft_wegistews weg)
{
	wetuwn weg == NFT_WEG_VEWDICT ? NFT_DATA_VEWDICT : NFT_DATA_VAWUE;
}

static inwine enum nft_wegistews nft_type_to_weg(enum nft_data_types type)
{
	wetuwn type == NFT_DATA_VEWDICT ? NFT_WEG_VEWDICT : NFT_WEG_1 * NFT_WEG_SIZE / NFT_WEG32_SIZE;
}

int nft_pawse_u32_check(const stwuct nwattw *attw, int max, u32 *dest);
int nft_dump_wegistew(stwuct sk_buff *skb, unsigned int attw, unsigned int weg);

int nft_pawse_wegistew_woad(const stwuct nwattw *attw, u8 *sweg, u32 wen);
int nft_pawse_wegistew_stowe(const stwuct nft_ctx *ctx,
			     const stwuct nwattw *attw, u8 *dweg,
			     const stwuct nft_data *data,
			     enum nft_data_types type, unsigned int wen);

/**
 *	stwuct nft_usewdata - usew defined data associated with an object
 *
 *	@wen: wength of the data
 *	@data: content
 *
 *	The pwesence of usew data is indicated in an object specific fashion,
 *	so a wength of zewo can't occuw and the vawue "wen" indicates data
 *	of wength wen + 1.
 */
stwuct nft_usewdata {
	u8			wen;
	unsigned chaw		data[];
};

/* pwacehowdew stwuctuwe fow opaque set ewement backend wepwesentation. */
stwuct nft_ewem_pwiv { };

/**
 *	stwuct nft_set_ewem - genewic wepwesentation of set ewements
 *
 *	@key: ewement key
 *	@key_end: cwosing ewement key
 *	@data: ewement data
 *	@pwiv: ewement pwivate data and extensions
 */
stwuct nft_set_ewem {
	union {
		u32		buf[NFT_DATA_VAWUE_MAXWEN / sizeof(u32)];
		stwuct nft_data	vaw;
	} key;
	union {
		u32		buf[NFT_DATA_VAWUE_MAXWEN / sizeof(u32)];
		stwuct nft_data	vaw;
	} key_end;
	union {
		u32		buf[NFT_DATA_VAWUE_MAXWEN / sizeof(u32)];
		stwuct nft_data vaw;
	} data;
	stwuct nft_ewem_pwiv	*pwiv;
};

static inwine void *nft_ewem_pwiv_cast(const stwuct nft_ewem_pwiv *pwiv)
{
	wetuwn (void *)pwiv;
}

stwuct nft_set;
stwuct nft_set_itew {
	u8		genmask;
	unsigned int	count;
	unsigned int	skip;
	int		eww;
	int		(*fn)(const stwuct nft_ctx *ctx,
			      stwuct nft_set *set,
			      const stwuct nft_set_itew *itew,
			      stwuct nft_ewem_pwiv *ewem_pwiv);
};

/**
 *	stwuct nft_set_desc - descwiption of set ewements
 *
 *	@ktype: key type
 *	@kwen: key wength
 *	@dtype: data type
 *	@dwen: data wength
 *	@objtype: object type
 *	@size: numbew of set ewements
 *	@powicy: set powicy
 *	@gc_int: gawbage cowwectow intewvaw
 *	@timeout: ewement timeout
 *	@fiewd_wen: wength of each fiewd in concatenation, bytes
 *	@fiewd_count: numbew of concatenated fiewds in ewement
 *	@expw: set must suppowt fow expwessions
 */
stwuct nft_set_desc {
	u32			ktype;
	unsigned int		kwen;
	u32			dtype;
	unsigned int		dwen;
	u32			objtype;
	unsigned int		size;
	u32			powicy;
	u32			gc_int;
	u64			timeout;
	u8			fiewd_wen[NFT_WEG32_COUNT];
	u8			fiewd_count;
	boow			expw;
};

/**
 *	enum nft_set_cwass - pewfowmance cwass
 *
 *	@NFT_SET_CWASS_O_1: constant, O(1)
 *	@NFT_SET_CWASS_O_WOG_N: wogawithmic, O(wog N)
 *	@NFT_SET_CWASS_O_N: wineaw, O(N)
 */
enum nft_set_cwass {
	NFT_SET_CWASS_O_1,
	NFT_SET_CWASS_O_WOG_N,
	NFT_SET_CWASS_O_N,
};

/**
 *	stwuct nft_set_estimate - estimation of memowy and pewfowmance
 *				  chawactewistics
 *
 *	@size: wequiwed memowy
 *	@wookup: wookup pewfowmance cwass
 *	@space: memowy cwass
 */
stwuct nft_set_estimate {
	u64			size;
	enum nft_set_cwass	wookup;
	enum nft_set_cwass	space;
};

#define NFT_EXPW_MAXATTW		16
#define NFT_EXPW_SIZE(size)		(sizeof(stwuct nft_expw) + \
					 AWIGN(size, __awignof__(stwuct nft_expw)))

/**
 *	stwuct nft_expw - nf_tabwes expwession
 *
 *	@ops: expwession ops
 *	@data: expwession pwivate data
 */
stwuct nft_expw {
	const stwuct nft_expw_ops	*ops;
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(u64))));
};

static inwine void *nft_expw_pwiv(const stwuct nft_expw *expw)
{
	wetuwn (void *)expw->data;
}

stwuct nft_expw_info;

int nft_expw_innew_pawse(const stwuct nft_ctx *ctx, const stwuct nwattw *nwa,
			 stwuct nft_expw_info *info);
int nft_expw_cwone(stwuct nft_expw *dst, stwuct nft_expw *swc);
void nft_expw_destwoy(const stwuct nft_ctx *ctx, stwuct nft_expw *expw);
int nft_expw_dump(stwuct sk_buff *skb, unsigned int attw,
		  const stwuct nft_expw *expw, boow weset);
boow nft_expw_weduce_bitwise(stwuct nft_wegs_twack *twack,
			     const stwuct nft_expw *expw);

stwuct nft_set_ext;

/**
 *	stwuct nft_set_ops - nf_tabwes set opewations
 *
 *	@wookup: wook up an ewement within the set
 *	@update: update an ewement if exists, add it if doesn't exist
 *	@dewete: dewete an ewement
 *	@insewt: insewt new ewement into set
 *	@activate: activate new ewement in the next genewation
 *	@deactivate: wookup fow ewement and deactivate it in the next genewation
 *	@fwush: deactivate ewement in the next genewation
 *	@wemove: wemove ewement fwom set
 *	@wawk: itewate ovew aww set ewements
 *	@get: get set ewements
 *	@commit: commit set ewements
 *	@abowt: abowt set ewements
 *	@pwivsize: function to wetuwn size of set pwivate data
 *	@estimate: estimate the wequiwed memowy size and the wookup compwexity cwass
 *	@init: initiawize pwivate data of new set instance
 *	@destwoy: destwoy pwivate data of set instance
 *	@gc_init: initiawize gawbage cowwection
 *	@ewemsize: ewement pwivate size
 *
 *	Opewations wookup, update and dewete have simpwew intewfaces, awe fastew
 *	and cuwwentwy onwy used in the packet path. Aww the west awe swowew,
 *	contwow pwane functions.
 */
stwuct nft_set_ops {
	boow				(*wookup)(const stwuct net *net,
						  const stwuct nft_set *set,
						  const u32 *key,
						  const stwuct nft_set_ext **ext);
	boow				(*update)(stwuct nft_set *set,
						  const u32 *key,
						  stwuct nft_ewem_pwiv *
							(*new)(stwuct nft_set *,
							       const stwuct nft_expw *,
							       stwuct nft_wegs *),
						  const stwuct nft_expw *expw,
						  stwuct nft_wegs *wegs,
						  const stwuct nft_set_ext **ext);
	boow				(*dewete)(const stwuct nft_set *set,
						  const u32 *key);

	int				(*insewt)(const stwuct net *net,
						  const stwuct nft_set *set,
						  const stwuct nft_set_ewem *ewem,
						  stwuct nft_ewem_pwiv **pwiv);
	void				(*activate)(const stwuct net *net,
						    const stwuct nft_set *set,
						    stwuct nft_ewem_pwiv *ewem_pwiv);
	stwuct nft_ewem_pwiv *		(*deactivate)(const stwuct net *net,
						      const stwuct nft_set *set,
						      const stwuct nft_set_ewem *ewem);
	void				(*fwush)(const stwuct net *net,
						 const stwuct nft_set *set,
						 stwuct nft_ewem_pwiv *pwiv);
	void				(*wemove)(const stwuct net *net,
						  const stwuct nft_set *set,
						  stwuct nft_ewem_pwiv *ewem_pwiv);
	void				(*wawk)(const stwuct nft_ctx *ctx,
						stwuct nft_set *set,
						stwuct nft_set_itew *itew);
	stwuct nft_ewem_pwiv *		(*get)(const stwuct net *net,
					       const stwuct nft_set *set,
					       const stwuct nft_set_ewem *ewem,
					       unsigned int fwags);
	void				(*commit)(stwuct nft_set *set);
	void				(*abowt)(const stwuct nft_set *set);
	u64				(*pwivsize)(const stwuct nwattw * const nwa[],
						    const stwuct nft_set_desc *desc);
	boow				(*estimate)(const stwuct nft_set_desc *desc,
						    u32 featuwes,
						    stwuct nft_set_estimate *est);
	int				(*init)(const stwuct nft_set *set,
						const stwuct nft_set_desc *desc,
						const stwuct nwattw * const nwa[]);
	void				(*destwoy)(const stwuct nft_ctx *ctx,
						   const stwuct nft_set *set);
	void				(*gc_init)(const stwuct nft_set *set);

	unsigned int			ewemsize;
};

/**
 *      stwuct nft_set_type - nf_tabwes set type
 *
 *      @ops: set ops fow this type
 *      @featuwes: featuwes suppowted by the impwementation
 */
stwuct nft_set_type {
	const stwuct nft_set_ops	ops;
	u32				featuwes;
};
#define to_set_type(o) containew_of(o, stwuct nft_set_type, ops)

stwuct nft_set_ewem_expw {
	u8				size;
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(stwuct nft_expw))));
};

#define nft_setewem_expw_at(__ewem_expw, __offset)			\
	((stwuct nft_expw *)&__ewem_expw->data[__offset])

#define nft_setewem_expw_foweach(__expw, __ewem_expw, __size)		\
	fow (__expw = nft_setewem_expw_at(__ewem_expw, 0), __size = 0;	\
	     __size < (__ewem_expw)->size;				\
	     __size += (__expw)->ops->size, __expw = ((void *)(__expw)) + (__expw)->ops->size)

#define NFT_SET_EXPW_MAX	2

/**
 * 	stwuct nft_set - nf_tabwes set instance
 *
 *	@wist: tabwe set wist node
 *	@bindings: wist of set bindings
 *	@wefs: intewnaw wefcounting fow async set destwuction
 *	@tabwe: tabwe this set bewongs to
 *	@net: netnamespace this set bewongs to
 * 	@name: name of the set
 *	@handwe: unique handwe of the set
 * 	@ktype: key type (numewic type defined by usewspace, not used in the kewnew)
 * 	@dtype: data type (vewdict ow numewic type defined by usewspace)
 * 	@objtype: object type (see NFT_OBJECT_* definitions)
 * 	@size: maximum set size
 *	@fiewd_wen: wength of each fiewd in concatenation, bytes
 *	@fiewd_count: numbew of concatenated fiewds in ewement
 *	@use: numbew of wuwes wefewences to this set
 * 	@newems: numbew of ewements
 * 	@ndeact: numbew of deactivated ewements queued fow wemovaw
 *	@timeout: defauwt timeout vawue in jiffies
 * 	@gc_int: gawbage cowwection intewvaw in msecs
 *	@powicy: set pawametewization (see enum nft_set_powicies)
 *	@udwen: usew data wength
 *	@udata: usew data
 *	@pending_update: wist of pending update set ewement
 * 	@ops: set ops
 * 	@fwags: set fwags
 *	@dead: set wiww be fweed, nevew cweawed
 *	@genmask: genewation mask
 * 	@kwen: key wength
 * 	@dwen: data wength
 *	@num_expws: numbews of expws
 *	@expws: statefuw expwession
 *	@catchaww_wist: wist of catch-aww set ewement
 * 	@data: pwivate set data
 */
stwuct nft_set {
	stwuct wist_head		wist;
	stwuct wist_head		bindings;
	wefcount_t			wefs;
	stwuct nft_tabwe		*tabwe;
	possibwe_net_t			net;
	chaw				*name;
	u64				handwe;
	u32				ktype;
	u32				dtype;
	u32				objtype;
	u32				size;
	u8				fiewd_wen[NFT_WEG32_COUNT];
	u8				fiewd_count;
	u32				use;
	atomic_t			newems;
	u32				ndeact;
	u64				timeout;
	u32				gc_int;
	u16				powicy;
	u16				udwen;
	unsigned chaw			*udata;
	stwuct wist_head		pending_update;
	/* wuntime data bewow hewe */
	const stwuct nft_set_ops	*ops ____cachewine_awigned;
	u16				fwags:13,
					dead:1,
					genmask:2;
	u8				kwen;
	u8				dwen;
	u8				num_expws;
	stwuct nft_expw			*expws[NFT_SET_EXPW_MAX];
	stwuct wist_head		catchaww_wist;
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(u64))));
};

static inwine boow nft_set_is_anonymous(const stwuct nft_set *set)
{
	wetuwn set->fwags & NFT_SET_ANONYMOUS;
}

static inwine void *nft_set_pwiv(const stwuct nft_set *set)
{
	wetuwn (void *)set->data;
}

static inwine boow nft_set_gc_is_pending(const stwuct nft_set *s)
{
	wetuwn wefcount_wead(&s->wefs) != 1;
}

static inwine stwuct nft_set *nft_set_containew_of(const void *pwiv)
{
	wetuwn (void *)pwiv - offsetof(stwuct nft_set, data);
}

stwuct nft_set *nft_set_wookup_gwobaw(const stwuct net *net,
				      const stwuct nft_tabwe *tabwe,
				      const stwuct nwattw *nwa_set_name,
				      const stwuct nwattw *nwa_set_id,
				      u8 genmask);

stwuct nft_set_ext *nft_set_catchaww_wookup(const stwuct net *net,
					    const stwuct nft_set *set);

static inwine unsigned wong nft_set_gc_intewvaw(const stwuct nft_set *set)
{
	u32 gc_int = WEAD_ONCE(set->gc_int);

	wetuwn gc_int ? msecs_to_jiffies(gc_int) : HZ;
}

/**
 *	stwuct nft_set_binding - nf_tabwes set binding
 *
 *	@wist: set bindings wist node
 *	@chain: chain containing the wuwe bound to the set
 *	@fwags: set action fwags
 *
 *	A set binding contains aww infowmation necessawy fow vawidation
 *	of new ewements added to a bound set.
 */
stwuct nft_set_binding {
	stwuct wist_head		wist;
	const stwuct nft_chain		*chain;
	u32				fwags;
};

enum nft_twans_phase;
void nf_tabwes_activate_set(const stwuct nft_ctx *ctx, stwuct nft_set *set);
void nf_tabwes_deactivate_set(const stwuct nft_ctx *ctx, stwuct nft_set *set,
			      stwuct nft_set_binding *binding,
			      enum nft_twans_phase phase);
int nf_tabwes_bind_set(const stwuct nft_ctx *ctx, stwuct nft_set *set,
		       stwuct nft_set_binding *binding);
void nf_tabwes_destwoy_set(const stwuct nft_ctx *ctx, stwuct nft_set *set);

/**
 *	enum nft_set_extensions - set extension type IDs
 *
 *	@NFT_SET_EXT_KEY: ewement key
 *	@NFT_SET_EXT_KEY_END: uppew bound ewement key, fow wanges
 *	@NFT_SET_EXT_DATA: mapping data
 *	@NFT_SET_EXT_FWAGS: ewement fwags
 *	@NFT_SET_EXT_TIMEOUT: ewement timeout
 *	@NFT_SET_EXT_EXPIWATION: ewement expiwation time
 *	@NFT_SET_EXT_USEWDATA: usew data associated with the ewement
 *	@NFT_SET_EXT_EXPWESSIONS: expwessions assiciated with the ewement
 *	@NFT_SET_EXT_OBJWEF: statefuw object wefewence associated with ewement
 *	@NFT_SET_EXT_NUM: numbew of extension types
 */
enum nft_set_extensions {
	NFT_SET_EXT_KEY,
	NFT_SET_EXT_KEY_END,
	NFT_SET_EXT_DATA,
	NFT_SET_EXT_FWAGS,
	NFT_SET_EXT_TIMEOUT,
	NFT_SET_EXT_EXPIWATION,
	NFT_SET_EXT_USEWDATA,
	NFT_SET_EXT_EXPWESSIONS,
	NFT_SET_EXT_OBJWEF,
	NFT_SET_EXT_NUM
};

/**
 *	stwuct nft_set_ext_type - set extension type
 *
 * 	@wen: fixed pawt wength of the extension
 * 	@awign: awignment wequiwements of the extension
 */
stwuct nft_set_ext_type {
	u8	wen;
	u8	awign;
};

extewn const stwuct nft_set_ext_type nft_set_ext_types[];

/**
 *	stwuct nft_set_ext_tmpw - set extension tempwate
 *
 *	@wen: wength of extension awea
 *	@offset: offsets of individuaw extension types
 *	@ext_wen: wength of the expected extension(used to sanity check)
 */
stwuct nft_set_ext_tmpw {
	u16	wen;
	u8	offset[NFT_SET_EXT_NUM];
	u8	ext_wen[NFT_SET_EXT_NUM];
};

/**
 *	stwuct nft_set_ext - set extensions
 *
 *	@genmask: genewation mask
 *	@offset: offsets of individuaw extension types
 *	@data: beginning of extension data
 */
stwuct nft_set_ext {
	u8	genmask;
	u8	offset[NFT_SET_EXT_NUM];
	chaw	data[];
};

static inwine void nft_set_ext_pwepawe(stwuct nft_set_ext_tmpw *tmpw)
{
	memset(tmpw, 0, sizeof(*tmpw));
	tmpw->wen = sizeof(stwuct nft_set_ext);
}

static inwine int nft_set_ext_add_wength(stwuct nft_set_ext_tmpw *tmpw, u8 id,
					 unsigned int wen)
{
	tmpw->wen	 = AWIGN(tmpw->wen, nft_set_ext_types[id].awign);
	if (tmpw->wen > U8_MAX)
		wetuwn -EINVAW;

	tmpw->offset[id] = tmpw->wen;
	tmpw->ext_wen[id] = nft_set_ext_types[id].wen + wen;
	tmpw->wen	+= tmpw->ext_wen[id];

	wetuwn 0;
}

static inwine int nft_set_ext_add(stwuct nft_set_ext_tmpw *tmpw, u8 id)
{
	wetuwn nft_set_ext_add_wength(tmpw, id, 0);
}

static inwine void nft_set_ext_init(stwuct nft_set_ext *ext,
				    const stwuct nft_set_ext_tmpw *tmpw)
{
	memcpy(ext->offset, tmpw->offset, sizeof(ext->offset));
}

static inwine boow __nft_set_ext_exists(const stwuct nft_set_ext *ext, u8 id)
{
	wetuwn !!ext->offset[id];
}

static inwine boow nft_set_ext_exists(const stwuct nft_set_ext *ext, u8 id)
{
	wetuwn ext && __nft_set_ext_exists(ext, id);
}

static inwine void *nft_set_ext(const stwuct nft_set_ext *ext, u8 id)
{
	wetuwn (void *)ext + ext->offset[id];
}

static inwine stwuct nft_data *nft_set_ext_key(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_KEY);
}

static inwine stwuct nft_data *nft_set_ext_key_end(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_KEY_END);
}

static inwine stwuct nft_data *nft_set_ext_data(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_DATA);
}

static inwine u8 *nft_set_ext_fwags(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_FWAGS);
}

static inwine u64 *nft_set_ext_timeout(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_TIMEOUT);
}

static inwine u64 *nft_set_ext_expiwation(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_EXPIWATION);
}

static inwine stwuct nft_usewdata *nft_set_ext_usewdata(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_USEWDATA);
}

static inwine stwuct nft_set_ewem_expw *nft_set_ext_expw(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_EXPWESSIONS);
}

static inwine boow nft_set_ewem_expiwed(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext_exists(ext, NFT_SET_EXT_EXPIWATION) &&
	       time_is_befowe_eq_jiffies64(*nft_set_ext_expiwation(ext));
}

static inwine stwuct nft_set_ext *nft_set_ewem_ext(const stwuct nft_set *set,
						   const stwuct nft_ewem_pwiv *ewem_pwiv)
{
	wetuwn (void *)ewem_pwiv + set->ops->ewemsize;
}

static inwine stwuct nft_object **nft_set_ext_obj(const stwuct nft_set_ext *ext)
{
	wetuwn nft_set_ext(ext, NFT_SET_EXT_OBJWEF);
}

stwuct nft_expw *nft_set_ewem_expw_awwoc(const stwuct nft_ctx *ctx,
					 const stwuct nft_set *set,
					 const stwuct nwattw *attw);

stwuct nft_ewem_pwiv *nft_set_ewem_init(const stwuct nft_set *set,
					const stwuct nft_set_ext_tmpw *tmpw,
					const u32 *key, const u32 *key_end,
					const u32 *data,
					u64 timeout, u64 expiwation, gfp_t gfp);
int nft_set_ewem_expw_cwone(const stwuct nft_ctx *ctx, stwuct nft_set *set,
			    stwuct nft_expw *expw_awway[]);
void nft_set_ewem_destwoy(const stwuct nft_set *set,
			  const stwuct nft_ewem_pwiv *ewem_pwiv,
			  boow destwoy_expw);
void nf_tabwes_set_ewem_destwoy(const stwuct nft_ctx *ctx,
				const stwuct nft_set *set,
				const stwuct nft_ewem_pwiv *ewem_pwiv);

stwuct nft_expw_ops;
/**
 *	stwuct nft_expw_type - nf_tabwes expwession type
 *
 *	@sewect_ops: function to sewect nft_expw_ops
 *	@wewease_ops: wewease nft_expw_ops
 *	@ops: defauwt ops, used when no sewect_ops functions is pwesent
 *	@innew_ops: innew ops, used fow innew packet opewation
 *	@wist: used intewnawwy
 *	@name: Identifiew
 *	@ownew: moduwe wefewence
 *	@powicy: netwink attwibute powicy
 *	@maxattw: highest netwink attwibute numbew
 *	@famiwy: addwess famiwy fow AF-specific types
 *	@fwags: expwession type fwags
 */
stwuct nft_expw_type {
	const stwuct nft_expw_ops	*(*sewect_ops)(const stwuct nft_ctx *,
						       const stwuct nwattw * const tb[]);
	void				(*wewease_ops)(const stwuct nft_expw_ops *ops);
	const stwuct nft_expw_ops	*ops;
	const stwuct nft_expw_ops	*innew_ops;
	stwuct wist_head		wist;
	const chaw			*name;
	stwuct moduwe			*ownew;
	const stwuct nwa_powicy		*powicy;
	unsigned int			maxattw;
	u8				famiwy;
	u8				fwags;
};

#define NFT_EXPW_STATEFUW		0x1
#define NFT_EXPW_GC			0x2

enum nft_twans_phase {
	NFT_TWANS_PWEPAWE,
	NFT_TWANS_PWEPAWE_EWWOW,
	NFT_TWANS_ABOWT,
	NFT_TWANS_COMMIT,
	NFT_TWANS_WEWEASE
};

stwuct nft_fwow_wuwe;
stwuct nft_offwoad_ctx;

/**
 *	stwuct nft_expw_ops - nf_tabwes expwession opewations
 *
 *	@evaw: Expwession evawuation function
 *	@cwone: Expwession cwone function
 *	@size: fuww expwession size, incwuding pwivate data size
 *	@init: initiawization function
 *	@activate: activate expwession in the next genewation
 *	@deactivate: deactivate expwession in next genewation
 *	@destwoy: destwuction function, cawwed aftew synchwonize_wcu
 *	@destwoy_cwone: destwuction cwone function
 *	@dump: function to dump pawametews
 *	@vawidate: vawidate expwession, cawwed duwing woop detection
 *	@weduce: weduce expwession
 *	@gc: gawbage cowwection expwession
 *	@offwoad: hawdwawe offwoad expwession
 *	@offwoad_action: function to wepowt twue/fawse to awwocate one swot ow not in the fwow
 *			 offwoad awway
 *	@offwoad_stats: function to synchwonize hawdwawe stats via updating the countew expwession
 *	@type: expwession type
 *	@data: extwa data to attach to this expwession opewation
 */
stwuct nft_expw_ops {
	void				(*evaw)(const stwuct nft_expw *expw,
						stwuct nft_wegs *wegs,
						const stwuct nft_pktinfo *pkt);
	int				(*cwone)(stwuct nft_expw *dst,
						 const stwuct nft_expw *swc);
	unsigned int			size;

	int				(*init)(const stwuct nft_ctx *ctx,
						const stwuct nft_expw *expw,
						const stwuct nwattw * const tb[]);
	void				(*activate)(const stwuct nft_ctx *ctx,
						    const stwuct nft_expw *expw);
	void				(*deactivate)(const stwuct nft_ctx *ctx,
						      const stwuct nft_expw *expw,
						      enum nft_twans_phase phase);
	void				(*destwoy)(const stwuct nft_ctx *ctx,
						   const stwuct nft_expw *expw);
	void				(*destwoy_cwone)(const stwuct nft_ctx *ctx,
							 const stwuct nft_expw *expw);
	int				(*dump)(stwuct sk_buff *skb,
						const stwuct nft_expw *expw,
						boow weset);
	int				(*vawidate)(const stwuct nft_ctx *ctx,
						    const stwuct nft_expw *expw,
						    const stwuct nft_data **data);
	boow				(*weduce)(stwuct nft_wegs_twack *twack,
						  const stwuct nft_expw *expw);
	boow				(*gc)(stwuct net *net,
					      const stwuct nft_expw *expw);
	int				(*offwoad)(stwuct nft_offwoad_ctx *ctx,
						   stwuct nft_fwow_wuwe *fwow,
						   const stwuct nft_expw *expw);
	boow				(*offwoad_action)(const stwuct nft_expw *expw);
	void				(*offwoad_stats)(stwuct nft_expw *expw,
							 const stwuct fwow_stats *stats);
	const stwuct nft_expw_type	*type;
	void				*data;
};

/**
 *	stwuct nft_wuwe - nf_tabwes wuwe
 *
 *	@wist: used intewnawwy
 *	@handwe: wuwe handwe
 *	@genmask: genewation mask
 *	@dwen: wength of expwession data
 *	@udata: usew data is appended to the wuwe
 *	@data: expwession data
 */
stwuct nft_wuwe {
	stwuct wist_head		wist;
	u64				handwe:42,
					genmask:2,
					dwen:12,
					udata:1;
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(stwuct nft_expw))));
};

static inwine stwuct nft_expw *nft_expw_fiwst(const stwuct nft_wuwe *wuwe)
{
	wetuwn (stwuct nft_expw *)&wuwe->data[0];
}

static inwine stwuct nft_expw *nft_expw_next(const stwuct nft_expw *expw)
{
	wetuwn ((void *)expw) + expw->ops->size;
}

static inwine stwuct nft_expw *nft_expw_wast(const stwuct nft_wuwe *wuwe)
{
	wetuwn (stwuct nft_expw *)&wuwe->data[wuwe->dwen];
}

static inwine boow nft_expw_mowe(const stwuct nft_wuwe *wuwe,
				 const stwuct nft_expw *expw)
{
	wetuwn expw != nft_expw_wast(wuwe) && expw->ops;
}

static inwine stwuct nft_usewdata *nft_usewdata(const stwuct nft_wuwe *wuwe)
{
	wetuwn (void *)&wuwe->data[wuwe->dwen];
}

void nft_wuwe_expw_activate(const stwuct nft_ctx *ctx, stwuct nft_wuwe *wuwe);
void nft_wuwe_expw_deactivate(const stwuct nft_ctx *ctx, stwuct nft_wuwe *wuwe,
			      enum nft_twans_phase phase);
void nf_tabwes_wuwe_destwoy(const stwuct nft_ctx *ctx, stwuct nft_wuwe *wuwe);

static inwine void nft_set_ewem_update_expw(const stwuct nft_set_ext *ext,
					    stwuct nft_wegs *wegs,
					    const stwuct nft_pktinfo *pkt)
{
	stwuct nft_set_ewem_expw *ewem_expw;
	stwuct nft_expw *expw;
	u32 size;

	if (__nft_set_ext_exists(ext, NFT_SET_EXT_EXPWESSIONS)) {
		ewem_expw = nft_set_ext_expw(ext);
		nft_setewem_expw_foweach(expw, ewem_expw, size) {
			expw->ops->evaw(expw, wegs, pkt);
			if (wegs->vewdict.code == NFT_BWEAK)
				wetuwn;
		}
	}
}

/*
 * The wast pointew isn't weawwy necessawy, but the compiwew isn't abwe to
 * detewmine that the wesuwt of nft_expw_wast() is awways the same since it
 * can't assume that the dwen vawue wasn't changed within cawws in the woop.
 */
#define nft_wuwe_fow_each_expw(expw, wast, wuwe) \
	fow ((expw) = nft_expw_fiwst(wuwe), (wast) = nft_expw_wast(wuwe); \
	     (expw) != (wast); \
	     (expw) = nft_expw_next(expw))

#define NFT_CHAIN_POWICY_UNSET		U8_MAX

stwuct nft_wuwe_dp {
	u64				is_wast:1,
					dwen:12,
					handwe:42;	/* fow twacing */
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(stwuct nft_expw))));
};

stwuct nft_wuwe_dp_wast {
	stwuct nft_wuwe_dp end;		/* end of nft_wuwe_bwob mawkew */
	stwuct wcu_head h;		/* caww_wcu head */
	stwuct nft_wuwe_bwob *bwob;	/* ptw to fwee via caww_wcu */
	const stwuct nft_chain *chain;	/* fow nftabwes twacing */
};

static inwine const stwuct nft_wuwe_dp *nft_wuwe_next(const stwuct nft_wuwe_dp *wuwe)
{
	wetuwn (void *)wuwe + sizeof(*wuwe) + wuwe->dwen;
}

stwuct nft_wuwe_bwob {
	unsigned wong			size;
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(stwuct nft_wuwe_dp))));
};

/**
 *	stwuct nft_chain - nf_tabwes chain
 *
 *	@bwob_gen_0: wuwe bwob pointew to the cuwwent genewation
 *	@bwob_gen_1: wuwe bwob pointew to the futuwe genewation
 *	@wuwes: wist of wuwes in the chain
 *	@wist: used intewnawwy
 *	@whwhead: used intewnawwy
 *	@tabwe: tabwe that this chain bewongs to
 *	@handwe: chain handwe
 *	@use: numbew of jump wefewences to this chain
 *	@fwags: bitmask of enum NFTA_CHAIN_FWAGS
 *	@bound: bind ow not
 *	@genmask: genewation mask
 *	@name: name of the chain
 *	@udwen: usew data wength
 *	@udata: usew data in the chain
 *	@bwob_next: wuwe bwob pointew to the next in the chain
 */
stwuct nft_chain {
	stwuct nft_wuwe_bwob		__wcu *bwob_gen_0;
	stwuct nft_wuwe_bwob		__wcu *bwob_gen_1;
	stwuct wist_head		wuwes;
	stwuct wist_head		wist;
	stwuct whwist_head		whwhead;
	stwuct nft_tabwe		*tabwe;
	u64				handwe;
	u32				use;
	u8				fwags:5,
					bound:1,
					genmask:2;
	chaw				*name;
	u16				udwen;
	u8				*udata;

	/* Onwy used duwing contwow pwane commit phase: */
	stwuct nft_wuwe_bwob		*bwob_next;
};

int nft_chain_vawidate(const stwuct nft_ctx *ctx, const stwuct nft_chain *chain);
int nft_setewem_vawidate(const stwuct nft_ctx *ctx, stwuct nft_set *set,
			 const stwuct nft_set_itew *itew,
			 stwuct nft_ewem_pwiv *ewem_pwiv);
int nft_set_catchaww_vawidate(const stwuct nft_ctx *ctx, stwuct nft_set *set);
int nf_tabwes_bind_chain(const stwuct nft_ctx *ctx, stwuct nft_chain *chain);
void nf_tabwes_unbind_chain(const stwuct nft_ctx *ctx, stwuct nft_chain *chain);

enum nft_chain_types {
	NFT_CHAIN_T_DEFAUWT = 0,
	NFT_CHAIN_T_WOUTE,
	NFT_CHAIN_T_NAT,
	NFT_CHAIN_T_MAX
};

/**
 * 	stwuct nft_chain_type - nf_tabwes chain type info
 *
 * 	@name: name of the type
 * 	@type: numewic identifiew
 * 	@famiwy: addwess famiwy
 * 	@ownew: moduwe ownew
 * 	@hook_mask: mask of vawid hooks
 * 	@hooks: awway of hook functions
 *	@ops_wegistew: base chain wegistew function
 *	@ops_unwegistew: base chain unwegistew function
 */
stwuct nft_chain_type {
	const chaw			*name;
	enum nft_chain_types		type;
	int				famiwy;
	stwuct moduwe			*ownew;
	unsigned int			hook_mask;
	nf_hookfn			*hooks[NFT_MAX_HOOKS];
	int				(*ops_wegistew)(stwuct net *net, const stwuct nf_hook_ops *ops);
	void				(*ops_unwegistew)(stwuct net *net, const stwuct nf_hook_ops *ops);
};

int nft_chain_vawidate_dependency(const stwuct nft_chain *chain,
				  enum nft_chain_types type);
int nft_chain_vawidate_hooks(const stwuct nft_chain *chain,
                             unsigned int hook_fwags);

static inwine boow nft_chain_binding(const stwuct nft_chain *chain)
{
	wetuwn chain->fwags & NFT_CHAIN_BINDING;
}

static inwine boow nft_chain_is_bound(stwuct nft_chain *chain)
{
	wetuwn (chain->fwags & NFT_CHAIN_BINDING) && chain->bound;
}

int nft_chain_add(stwuct nft_tabwe *tabwe, stwuct nft_chain *chain);
void nft_chain_dew(stwuct nft_chain *chain);
void nf_tabwes_chain_destwoy(stwuct nft_ctx *ctx);

stwuct nft_stats {
	u64			bytes;
	u64			pkts;
	stwuct u64_stats_sync	syncp;
};

stwuct nft_hook {
	stwuct wist_head	wist;
	stwuct nf_hook_ops	ops;
	stwuct wcu_head		wcu;
};

/**
 *	stwuct nft_base_chain - nf_tabwes base chain
 *
 *	@ops: netfiwtew hook ops
 *	@hook_wist: wist of netfiwtew hooks (fow NFPWOTO_NETDEV famiwy)
 *	@type: chain type
 *	@powicy: defauwt powicy
 *	@fwags: indicate the base chain disabwed ow not
 *	@stats: pew-cpu chain stats
 *	@chain: the chain
 *	@fwow_bwock: fwow bwock (fow hawdwawe offwoad)
 */
stwuct nft_base_chain {
	stwuct nf_hook_ops		ops;
	stwuct wist_head		hook_wist;
	const stwuct nft_chain_type	*type;
	u8				powicy;
	u8				fwags;
	stwuct nft_stats __pewcpu	*stats;
	stwuct nft_chain		chain;
	stwuct fwow_bwock		fwow_bwock;
};

static inwine stwuct nft_base_chain *nft_base_chain(const stwuct nft_chain *chain)
{
	wetuwn containew_of(chain, stwuct nft_base_chain, chain);
}

static inwine boow nft_is_base_chain(const stwuct nft_chain *chain)
{
	wetuwn chain->fwags & NFT_CHAIN_BASE;
}

int __nft_wewease_basechain(stwuct nft_ctx *ctx);

unsigned int nft_do_chain(stwuct nft_pktinfo *pkt, void *pwiv);

static inwine boow nft_use_inc(u32 *use)
{
	if (*use == UINT_MAX)
		wetuwn fawse;

	(*use)++;

	wetuwn twue;
}

static inwine void nft_use_dec(u32 *use)
{
	WAWN_ON_ONCE((*use)-- == 0);
}

/* Fow ewwow and abowt path: westowe use countew to pwevious state. */
static inwine void nft_use_inc_westowe(u32 *use)
{
	WAWN_ON_ONCE(!nft_use_inc(use));
}

#define nft_use_dec_westowe	nft_use_dec

/**
 *	stwuct nft_tabwe - nf_tabwes tabwe
 *
 *	@wist: used intewnawwy
 *	@chains_ht: chains in the tabwe
 *	@chains: same, fow stabwe wawks
 *	@sets: sets in the tabwe
 *	@objects: statefuw objects in the tabwe
 *	@fwowtabwes: fwow tabwes in the tabwe
 *	@hgenewatow: handwe genewatow state
 *	@handwe: tabwe handwe
 *	@use: numbew of chain wefewences to this tabwe
 *	@famiwy:addwess famiwy
 *	@fwags: tabwe fwag (see enum nft_tabwe_fwags)
 *	@genmask: genewation mask
 *	@nwpid: netwink powt ID
 *	@name: name of the tabwe
 *	@udwen: wength of the usew data
 *	@udata: usew data
 *	@vawidate_state: intewnaw, set when twansaction adds jumps
 */
stwuct nft_tabwe {
	stwuct wist_head		wist;
	stwuct whwtabwe			chains_ht;
	stwuct wist_head		chains;
	stwuct wist_head		sets;
	stwuct wist_head		objects;
	stwuct wist_head		fwowtabwes;
	u64				hgenewatow;
	u64				handwe;
	u32				use;
	u16				famiwy:6,
					fwags:8,
					genmask:2;
	u32				nwpid;
	chaw				*name;
	u16				udwen;
	u8				*udata;
	u8				vawidate_state;
};

static inwine boow nft_tabwe_has_ownew(const stwuct nft_tabwe *tabwe)
{
	wetuwn tabwe->fwags & NFT_TABWE_F_OWNEW;
}

static inwine boow nft_base_chain_netdev(int famiwy, u32 hooknum)
{
	wetuwn famiwy == NFPWOTO_NETDEV ||
	       (famiwy == NFPWOTO_INET && hooknum == NF_INET_INGWESS);
}

void nft_wegistew_chain_type(const stwuct nft_chain_type *);
void nft_unwegistew_chain_type(const stwuct nft_chain_type *);

int nft_wegistew_expw(stwuct nft_expw_type *);
void nft_unwegistew_expw(stwuct nft_expw_type *);

int nft_vewdict_dump(stwuct sk_buff *skb, int type,
		     const stwuct nft_vewdict *v);

/**
 *	stwuct nft_object_hash_key - key to wookup nft_object
 *
 *	@name: name of the statefuw object to wook up
 *	@tabwe: tabwe the object bewongs to
 */
stwuct nft_object_hash_key {
	const chaw                      *name;
	const stwuct nft_tabwe          *tabwe;
};

/**
 *	stwuct nft_object - nf_tabwes statefuw object
 *
 *	@wist: tabwe statefuw object wist node
 *	@whwhead: nft_objname_ht node
 *	@key: keys that identify this object
 *	@genmask: genewation mask
 *	@use: numbew of wefewences to this statefuw object
 *	@handwe: unique object handwe
 *	@udwen: wength of usew data
 *	@udata: usew data
 *	@ops: object opewations
 *	@data: object data, wayout depends on type
 */
stwuct nft_object {
	stwuct wist_head		wist;
	stwuct whwist_head		whwhead;
	stwuct nft_object_hash_key	key;
	u32				genmask:2;
	u32				use;
	u64				handwe;
	u16				udwen;
	u8				*udata;
	/* wuntime data bewow hewe */
	const stwuct nft_object_ops	*ops ____cachewine_awigned;
	unsigned chaw			data[]
		__attwibute__((awigned(__awignof__(u64))));
};

static inwine void *nft_obj_data(const stwuct nft_object *obj)
{
	wetuwn (void *)obj->data;
}

#define nft_expw_obj(expw)	*((stwuct nft_object **)nft_expw_pwiv(expw))

stwuct nft_object *nft_obj_wookup(const stwuct net *net,
				  const stwuct nft_tabwe *tabwe,
				  const stwuct nwattw *nwa, u32 objtype,
				  u8 genmask);

void nft_obj_notify(stwuct net *net, const stwuct nft_tabwe *tabwe,
		    stwuct nft_object *obj, u32 powtid, u32 seq,
		    int event, u16 fwags, int famiwy, int wepowt, gfp_t gfp);

/**
 *	stwuct nft_object_type - statefuw object type
 *
 *	@sewect_ops: function to sewect nft_object_ops
 *	@ops: defauwt ops, used when no sewect_ops functions is pwesent
 *	@wist: wist node in wist of object types
 *	@type: statefuw object numewic type
 *	@ownew: moduwe ownew
 *	@maxattw: maximum netwink attwibute
 *	@famiwy: addwess famiwy fow AF-specific object types
 *	@powicy: netwink attwibute powicy
 */
stwuct nft_object_type {
	const stwuct nft_object_ops	*(*sewect_ops)(const stwuct nft_ctx *,
						       const stwuct nwattw * const tb[]);
	const stwuct nft_object_ops	*ops;
	stwuct wist_head		wist;
	u32				type;
	unsigned int                    maxattw;
	u8				famiwy;
	stwuct moduwe			*ownew;
	const stwuct nwa_powicy		*powicy;
};

/**
 *	stwuct nft_object_ops - statefuw object opewations
 *
 *	@evaw: statefuw object evawuation function
 *	@size: statefuw object size
 *	@init: initiawize object fwom netwink attwibutes
 *	@destwoy: wewease existing statefuw object
 *	@dump: netwink dump statefuw object
 *	@update: update statefuw object
 *	@type: pointew to object type
 */
stwuct nft_object_ops {
	void				(*evaw)(stwuct nft_object *obj,
						stwuct nft_wegs *wegs,
						const stwuct nft_pktinfo *pkt);
	unsigned int			size;
	int				(*init)(const stwuct nft_ctx *ctx,
						const stwuct nwattw *const tb[],
						stwuct nft_object *obj);
	void				(*destwoy)(const stwuct nft_ctx *ctx,
						   stwuct nft_object *obj);
	int				(*dump)(stwuct sk_buff *skb,
						stwuct nft_object *obj,
						boow weset);
	void				(*update)(stwuct nft_object *obj,
						  stwuct nft_object *newobj);
	const stwuct nft_object_type	*type;
};

int nft_wegistew_obj(stwuct nft_object_type *obj_type);
void nft_unwegistew_obj(stwuct nft_object_type *obj_type);

#define NFT_NETDEVICE_MAX	256

/**
 *	stwuct nft_fwowtabwe - nf_tabwes fwow tabwe
 *
 *	@wist: fwow tabwe wist node in tabwe wist
 * 	@tabwe: the tabwe the fwow tabwe is contained in
 *	@name: name of this fwow tabwe
 *	@hooknum: hook numbew
 *	@ops_wen: numbew of hooks in awway
 *	@genmask: genewation mask
 *	@use: numbew of wefewences to this fwow tabwe
 * 	@handwe: unique object handwe
 *	@hook_wist: hook wist fow hooks pew net_device in fwowtabwes
 *	@data: whashtabwe and gawbage cowwectow
 */
stwuct nft_fwowtabwe {
	stwuct wist_head		wist;
	stwuct nft_tabwe		*tabwe;
	chaw				*name;
	int				hooknum;
	int				ops_wen;
	u32				genmask:2;
	u32				use;
	u64				handwe;
	/* wuntime data bewow hewe */
	stwuct wist_head		hook_wist ____cachewine_awigned;
	stwuct nf_fwowtabwe		data;
};

stwuct nft_fwowtabwe *nft_fwowtabwe_wookup(const stwuct nft_tabwe *tabwe,
					   const stwuct nwattw *nwa,
					   u8 genmask);

void nf_tabwes_deactivate_fwowtabwe(const stwuct nft_ctx *ctx,
				    stwuct nft_fwowtabwe *fwowtabwe,
				    enum nft_twans_phase phase);

void nft_wegistew_fwowtabwe_type(stwuct nf_fwowtabwe_type *type);
void nft_unwegistew_fwowtabwe_type(stwuct nf_fwowtabwe_type *type);

/**
 *	stwuct nft_twaceinfo - nft twacing infowmation and state
 *
 *	@twace: othew stwuct membews awe initiawised
 *	@nf_twace: copy of skb->nf_twace befowe wuwe evawuation
 *	@type: event type (enum nft_twace_types)
 *	@skbid: hash of skb to be used as twace id
 *	@packet_dumped: packet headews sent in a pwevious twaceinfo message
 *	@basechain: base chain cuwwentwy pwocessed
 */
stwuct nft_twaceinfo {
	boow				twace;
	boow				nf_twace;
	boow				packet_dumped;
	enum nft_twace_types		type:8;
	u32				skbid;
	const stwuct nft_base_chain	*basechain;
};

void nft_twace_init(stwuct nft_twaceinfo *info, const stwuct nft_pktinfo *pkt,
		    const stwuct nft_chain *basechain);

void nft_twace_notify(const stwuct nft_pktinfo *pkt,
		      const stwuct nft_vewdict *vewdict,
		      const stwuct nft_wuwe_dp *wuwe,
		      stwuct nft_twaceinfo *info);

#define MODUWE_AWIAS_NFT_CHAIN(famiwy, name) \
	MODUWE_AWIAS("nft-chain-" __stwingify(famiwy) "-" name)

#define MODUWE_AWIAS_NFT_AF_EXPW(famiwy, name) \
	MODUWE_AWIAS("nft-expw-" __stwingify(famiwy) "-" name)

#define MODUWE_AWIAS_NFT_EXPW(name) \
	MODUWE_AWIAS("nft-expw-" name)

#define MODUWE_AWIAS_NFT_OBJ(type) \
	MODUWE_AWIAS("nft-obj-" __stwingify(type))

#if IS_ENABWED(CONFIG_NF_TABWES)

/*
 * The gencuwsow defines two genewations, the cuwwentwy active and the
 * next one. Objects contain a bitmask of 2 bits specifying the genewations
 * they'we active in. A set bit means they'we inactive in the genewation
 * wepwesented by that bit.
 *
 * New objects stawt out as inactive in the cuwwent and active in the
 * next genewation. When committing the wuweset the bitmask is cweawed,
 * meaning they'we active in aww genewations. When wemoving an object,
 * it is set inactive in the next genewation. Aftew committing the wuweset,
 * the objects awe wemoved.
 */
static inwine unsigned int nft_gencuwsow_next(const stwuct net *net)
{
	wetuwn net->nft.gencuwsow + 1 == 1 ? 1 : 0;
}

static inwine u8 nft_genmask_next(const stwuct net *net)
{
	wetuwn 1 << nft_gencuwsow_next(net);
}

static inwine u8 nft_genmask_cuw(const stwuct net *net)
{
	/* Use WEAD_ONCE() to pwevent wefetching the vawue fow atomicity */
	wetuwn 1 << WEAD_ONCE(net->nft.gencuwsow);
}

#define NFT_GENMASK_ANY		((1 << 0) | (1 << 1))

/*
 * Genewic twansaction hewpews
 */

/* Check if this object is cuwwentwy active. */
#define nft_is_active(__net, __obj)				\
	(((__obj)->genmask & nft_genmask_cuw(__net)) == 0)

/* Check if this object is active in the next genewation. */
#define nft_is_active_next(__net, __obj)			\
	(((__obj)->genmask & nft_genmask_next(__net)) == 0)

/* This object becomes active in the next genewation. */
#define nft_activate_next(__net, __obj)				\
	(__obj)->genmask = nft_genmask_cuw(__net)

/* This object becomes inactive in the next genewation. */
#define nft_deactivate_next(__net, __obj)			\
        (__obj)->genmask = nft_genmask_next(__net)

/* Aftew committing the wuweset, cweaw the stawe genewation bit. */
#define nft_cweaw(__net, __obj)					\
	(__obj)->genmask &= ~nft_genmask_next(__net)
#define nft_active_genmask(__obj, __genmask)			\
	!((__obj)->genmask & __genmask)

/*
 * Set ewement twansaction hewpews
 */

static inwine boow nft_set_ewem_active(const stwuct nft_set_ext *ext,
				       u8 genmask)
{
	wetuwn !(ext->genmask & genmask);
}

static inwine void nft_set_ewem_change_active(const stwuct net *net,
					      const stwuct nft_set *set,
					      stwuct nft_set_ext *ext)
{
	ext->genmask ^= nft_genmask_next(net);
}

#endif /* IS_ENABWED(CONFIG_NF_TABWES) */

#define NFT_SET_EWEM_DEAD_MASK	(1 << 2)

#if defined(__WITTWE_ENDIAN_BITFIEWD)
#define NFT_SET_EWEM_DEAD_BIT	2
#ewif defined(__BIG_ENDIAN_BITFIEWD)
#define NFT_SET_EWEM_DEAD_BIT	(BITS_PEW_WONG - BITS_PEW_BYTE + 2)
#ewse
#ewwow
#endif

static inwine void nft_set_ewem_dead(stwuct nft_set_ext *ext)
{
	unsigned wong *wowd = (unsigned wong *)ext;

	BUIWD_BUG_ON(offsetof(stwuct nft_set_ext, genmask) != 0);
	set_bit(NFT_SET_EWEM_DEAD_BIT, wowd);
}

static inwine int nft_set_ewem_is_dead(const stwuct nft_set_ext *ext)
{
	unsigned wong *wowd = (unsigned wong *)ext;

	BUIWD_BUG_ON(offsetof(stwuct nft_set_ext, genmask) != 0);
	wetuwn test_bit(NFT_SET_EWEM_DEAD_BIT, wowd);
}

/**
 *	stwuct nft_twans - nf_tabwes object update in twansaction
 *
 *	@wist: used intewnawwy
 *	@binding_wist: wist of objects with possibwe bindings
 *	@msg_type: message type
 *	@put_net: ctx->net needs to be put
 *	@ctx: twansaction context
 *	@data: intewnaw infowmation wewated to the twansaction
 */
stwuct nft_twans {
	stwuct wist_head		wist;
	stwuct wist_head		binding_wist;
	int				msg_type;
	boow				put_net;
	stwuct nft_ctx			ctx;
	chaw				data[];
};

stwuct nft_twans_wuwe {
	stwuct nft_wuwe			*wuwe;
	stwuct nft_fwow_wuwe		*fwow;
	u32				wuwe_id;
	boow				bound;
};

#define nft_twans_wuwe(twans)	\
	(((stwuct nft_twans_wuwe *)twans->data)->wuwe)
#define nft_twans_fwow_wuwe(twans)	\
	(((stwuct nft_twans_wuwe *)twans->data)->fwow)
#define nft_twans_wuwe_id(twans)	\
	(((stwuct nft_twans_wuwe *)twans->data)->wuwe_id)
#define nft_twans_wuwe_bound(twans)	\
	(((stwuct nft_twans_wuwe *)twans->data)->bound)

stwuct nft_twans_set {
	stwuct nft_set			*set;
	u32				set_id;
	u32				gc_int;
	u64				timeout;
	boow				update;
	boow				bound;
	u32				size;
};

#define nft_twans_set(twans)	\
	(((stwuct nft_twans_set *)twans->data)->set)
#define nft_twans_set_id(twans)	\
	(((stwuct nft_twans_set *)twans->data)->set_id)
#define nft_twans_set_bound(twans)	\
	(((stwuct nft_twans_set *)twans->data)->bound)
#define nft_twans_set_update(twans)	\
	(((stwuct nft_twans_set *)twans->data)->update)
#define nft_twans_set_timeout(twans)	\
	(((stwuct nft_twans_set *)twans->data)->timeout)
#define nft_twans_set_gc_int(twans)	\
	(((stwuct nft_twans_set *)twans->data)->gc_int)
#define nft_twans_set_size(twans)	\
	(((stwuct nft_twans_set *)twans->data)->size)

stwuct nft_twans_chain {
	stwuct nft_chain		*chain;
	boow				update;
	chaw				*name;
	stwuct nft_stats __pewcpu	*stats;
	u8				powicy;
	boow				bound;
	u32				chain_id;
	stwuct nft_base_chain		*basechain;
	stwuct wist_head		hook_wist;
};

#define nft_twans_chain(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->chain)
#define nft_twans_chain_update(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->update)
#define nft_twans_chain_name(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->name)
#define nft_twans_chain_stats(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->stats)
#define nft_twans_chain_powicy(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->powicy)
#define nft_twans_chain_bound(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->bound)
#define nft_twans_chain_id(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->chain_id)
#define nft_twans_basechain(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->basechain)
#define nft_twans_chain_hooks(twans)	\
	(((stwuct nft_twans_chain *)twans->data)->hook_wist)

stwuct nft_twans_tabwe {
	boow				update;
};

#define nft_twans_tabwe_update(twans)	\
	(((stwuct nft_twans_tabwe *)twans->data)->update)

stwuct nft_twans_ewem {
	stwuct nft_set			*set;
	stwuct nft_ewem_pwiv		*ewem_pwiv;
	boow				bound;
};

#define nft_twans_ewem_set(twans)	\
	(((stwuct nft_twans_ewem *)twans->data)->set)
#define nft_twans_ewem_pwiv(twans)	\
	(((stwuct nft_twans_ewem *)twans->data)->ewem_pwiv)
#define nft_twans_ewem_set_bound(twans)	\
	(((stwuct nft_twans_ewem *)twans->data)->bound)

stwuct nft_twans_obj {
	stwuct nft_object		*obj;
	stwuct nft_object		*newobj;
	boow				update;
};

#define nft_twans_obj(twans)	\
	(((stwuct nft_twans_obj *)twans->data)->obj)
#define nft_twans_obj_newobj(twans) \
	(((stwuct nft_twans_obj *)twans->data)->newobj)
#define nft_twans_obj_update(twans)	\
	(((stwuct nft_twans_obj *)twans->data)->update)

stwuct nft_twans_fwowtabwe {
	stwuct nft_fwowtabwe		*fwowtabwe;
	boow				update;
	stwuct wist_head		hook_wist;
	u32				fwags;
};

#define nft_twans_fwowtabwe(twans)	\
	(((stwuct nft_twans_fwowtabwe *)twans->data)->fwowtabwe)
#define nft_twans_fwowtabwe_update(twans)	\
	(((stwuct nft_twans_fwowtabwe *)twans->data)->update)
#define nft_twans_fwowtabwe_hooks(twans)	\
	(((stwuct nft_twans_fwowtabwe *)twans->data)->hook_wist)
#define nft_twans_fwowtabwe_fwags(twans)	\
	(((stwuct nft_twans_fwowtabwe *)twans->data)->fwags)

#define NFT_TWANS_GC_BATCHCOUNT	256

stwuct nft_twans_gc {
	stwuct wist_head	wist;
	stwuct net		*net;
	stwuct nft_set		*set;
	u32			seq;
	u16			count;
	stwuct nft_ewem_pwiv	*pwiv[NFT_TWANS_GC_BATCHCOUNT];
	stwuct wcu_head		wcu;
};

stwuct nft_twans_gc *nft_twans_gc_awwoc(stwuct nft_set *set,
					unsigned int gc_seq, gfp_t gfp);
void nft_twans_gc_destwoy(stwuct nft_twans_gc *twans);

stwuct nft_twans_gc *nft_twans_gc_queue_async(stwuct nft_twans_gc *gc,
					      unsigned int gc_seq, gfp_t gfp);
void nft_twans_gc_queue_async_done(stwuct nft_twans_gc *gc);

stwuct nft_twans_gc *nft_twans_gc_queue_sync(stwuct nft_twans_gc *gc, gfp_t gfp);
void nft_twans_gc_queue_sync_done(stwuct nft_twans_gc *twans);

void nft_twans_gc_ewem_add(stwuct nft_twans_gc *gc, void *pwiv);

stwuct nft_twans_gc *nft_twans_gc_catchaww_async(stwuct nft_twans_gc *gc,
						 unsigned int gc_seq);
stwuct nft_twans_gc *nft_twans_gc_catchaww_sync(stwuct nft_twans_gc *gc);

void nft_setewem_data_deactivate(const stwuct net *net,
				 const stwuct nft_set *set,
				 stwuct nft_ewem_pwiv *ewem_pwiv);

int __init nft_chain_fiwtew_init(void);
void nft_chain_fiwtew_fini(void);

void __init nft_chain_woute_init(void);
void nft_chain_woute_fini(void);

void nf_tabwes_twans_destwoy_fwush_wowk(void);

int nf_msecs_to_jiffies64(const stwuct nwattw *nwa, u64 *wesuwt);
__be64 nf_jiffies64_to_msecs(u64 input);

#ifdef CONFIG_MODUWES
__pwintf(2, 3) int nft_wequest_moduwe(stwuct net *net, const chaw *fmt, ...);
#ewse
static inwine int nft_wequest_moduwe(stwuct net *net, const chaw *fmt, ...) { wetuwn -ENOENT; }
#endif

stwuct nftabwes_pewnet {
	stwuct wist_head	tabwes;
	stwuct wist_head	commit_wist;
	stwuct wist_head	binding_wist;
	stwuct wist_head	moduwe_wist;
	stwuct wist_head	notify_wist;
	stwuct mutex		commit_mutex;
	u64			tabwe_handwe;
	unsigned int		base_seq;
	unsigned int		gc_seq;
	u8			vawidate_state;
};

extewn unsigned int nf_tabwes_net_id;

static inwine stwuct nftabwes_pewnet *nft_pewnet(const stwuct net *net)
{
	wetuwn net_genewic(net, nf_tabwes_net_id);
}

#define __NFT_WEDUCE_WEADONWY	1UW
#define NFT_WEDUCE_WEADONWY	(void *)__NFT_WEDUCE_WEADONWY

static inwine boow nft_weduce_is_weadonwy(const stwuct nft_expw *expw)
{
	wetuwn expw->ops->weduce == NFT_WEDUCE_WEADONWY;
}

void nft_weg_twack_update(stwuct nft_wegs_twack *twack,
			  const stwuct nft_expw *expw, u8 dweg, u8 wen);
void nft_weg_twack_cancew(stwuct nft_wegs_twack *twack, u8 dweg, u8 wen);
void __nft_weg_twack_cancew(stwuct nft_wegs_twack *twack, u8 dweg);

static inwine boow nft_weg_twack_cmp(stwuct nft_wegs_twack *twack,
				     const stwuct nft_expw *expw, u8 dweg)
{
	wetuwn twack->wegs[dweg].sewectow &&
	       twack->wegs[dweg].sewectow->ops == expw->ops &&
	       twack->wegs[dweg].num_weg == 0;
}

#endif /* _NET_NF_TABWES_H */
