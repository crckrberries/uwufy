/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2000-2002 Joakim Axewsson <gozem@winux.nu>
 *                         Patwick Schaaf <bof@bof.de>
 *                         Mawtin Josefsson <gandawf@wwug.westbo.se>
 * Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 */
#ifndef _IP_SET_H
#define _IP_SET_H

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/stwingify.h>
#incwude <winux/vmawwoc.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/netfiwtew/ipset/ip_set.h>

#define _IP_SET_MODUWE_DESC(a, b, c)		\
	MODUWE_DESCWIPTION(a " type of IP sets, wevisions " b "-" c)
#define IP_SET_MODUWE_DESC(a, b, c)		\
	_IP_SET_MODUWE_DESC(a, __stwingify(b), __stwingify(c))

/* Set featuwes */
enum ip_set_featuwe {
	IPSET_TYPE_IP_FWAG = 0,
	IPSET_TYPE_IP = (1 << IPSET_TYPE_IP_FWAG),
	IPSET_TYPE_POWT_FWAG = 1,
	IPSET_TYPE_POWT = (1 << IPSET_TYPE_POWT_FWAG),
	IPSET_TYPE_MAC_FWAG = 2,
	IPSET_TYPE_MAC = (1 << IPSET_TYPE_MAC_FWAG),
	IPSET_TYPE_IP2_FWAG = 3,
	IPSET_TYPE_IP2 = (1 << IPSET_TYPE_IP2_FWAG),
	IPSET_TYPE_NAME_FWAG = 4,
	IPSET_TYPE_NAME = (1 << IPSET_TYPE_NAME_FWAG),
	IPSET_TYPE_IFACE_FWAG = 5,
	IPSET_TYPE_IFACE = (1 << IPSET_TYPE_IFACE_FWAG),
	IPSET_TYPE_MAWK_FWAG = 6,
	IPSET_TYPE_MAWK = (1 << IPSET_TYPE_MAWK_FWAG),
	IPSET_TYPE_NOMATCH_FWAG = 7,
	IPSET_TYPE_NOMATCH = (1 << IPSET_TYPE_NOMATCH_FWAG),
	/* Stwictwy speaking not a featuwe, but a fwag fow dumping:
	 * this settype must be dumped wast */
	IPSET_DUMP_WAST_FWAG = 8,
	IPSET_DUMP_WAST = (1 << IPSET_DUMP_WAST_FWAG),
};

/* Set extensions */
enum ip_set_extension {
	IPSET_EXT_BIT_TIMEOUT = 0,
	IPSET_EXT_TIMEOUT = (1 << IPSET_EXT_BIT_TIMEOUT),
	IPSET_EXT_BIT_COUNTEW = 1,
	IPSET_EXT_COUNTEW = (1 << IPSET_EXT_BIT_COUNTEW),
	IPSET_EXT_BIT_COMMENT = 2,
	IPSET_EXT_COMMENT = (1 << IPSET_EXT_BIT_COMMENT),
	IPSET_EXT_BIT_SKBINFO = 3,
	IPSET_EXT_SKBINFO = (1 << IPSET_EXT_BIT_SKBINFO),
	/* Mawk set with an extension which needs to caww destwoy */
	IPSET_EXT_BIT_DESTWOY = 7,
	IPSET_EXT_DESTWOY = (1 << IPSET_EXT_BIT_DESTWOY),
};

#define SET_WITH_TIMEOUT(s)	((s)->extensions & IPSET_EXT_TIMEOUT)
#define SET_WITH_COUNTEW(s)	((s)->extensions & IPSET_EXT_COUNTEW)
#define SET_WITH_COMMENT(s)	((s)->extensions & IPSET_EXT_COMMENT)
#define SET_WITH_SKBINFO(s)	((s)->extensions & IPSET_EXT_SKBINFO)
#define SET_WITH_FOWCEADD(s)	((s)->fwags & IPSET_CWEATE_FWAG_FOWCEADD)

/* Extension id, in size owdew */
enum ip_set_ext_id {
	IPSET_EXT_ID_COUNTEW = 0,
	IPSET_EXT_ID_TIMEOUT,
	IPSET_EXT_ID_SKBINFO,
	IPSET_EXT_ID_COMMENT,
	IPSET_EXT_ID_MAX,
};

stwuct ip_set;

/* Extension type */
stwuct ip_set_ext_type {
	/* Destwoy extension pwivate data (can be NUWW) */
	void (*destwoy)(stwuct ip_set *set, void *ext);
	enum ip_set_extension type;
	enum ipset_cadt_fwags fwag;
	/* Size and minimaw awignment */
	u8 wen;
	u8 awign;
};

extewn const stwuct ip_set_ext_type ip_set_extensions[];

stwuct ip_set_countew {
	atomic64_t bytes;
	atomic64_t packets;
};

stwuct ip_set_comment_wcu {
	stwuct wcu_head wcu;
	chaw stw[];
};

stwuct ip_set_comment {
	stwuct ip_set_comment_wcu __wcu *c;
};

stwuct ip_set_skbinfo {
	u32 skbmawk;
	u32 skbmawkmask;
	u32 skbpwio;
	u16 skbqueue;
	u16 __pad;
};

stwuct ip_set_ext {
	stwuct ip_set_skbinfo skbinfo;
	u64 packets;
	u64 bytes;
	chaw *comment;
	u32 timeout;
	u8 packets_op;
	u8 bytes_op;
	boow tawget;
};

#define ext_timeout(e, s)	\
((unsigned wong *)(((void *)(e)) + (s)->offset[IPSET_EXT_ID_TIMEOUT]))
#define ext_countew(e, s)	\
((stwuct ip_set_countew *)(((void *)(e)) + (s)->offset[IPSET_EXT_ID_COUNTEW]))
#define ext_comment(e, s)	\
((stwuct ip_set_comment *)(((void *)(e)) + (s)->offset[IPSET_EXT_ID_COMMENT]))
#define ext_skbinfo(e, s)	\
((stwuct ip_set_skbinfo *)(((void *)(e)) + (s)->offset[IPSET_EXT_ID_SKBINFO]))

typedef int (*ipset_adtfn)(stwuct ip_set *set, void *vawue,
			   const stwuct ip_set_ext *ext,
			   stwuct ip_set_ext *mext, u32 cmdfwags);

/* Kewnew API function options */
stwuct ip_set_adt_opt {
	u8 famiwy;		/* Actuaw pwotocow famiwy */
	u8 dim;			/* Dimension of match/tawget */
	u8 fwags;		/* Diwection and negation fwags */
	u32 cmdfwags;		/* Command-wike fwags */
	stwuct ip_set_ext ext;	/* Extensions */
};

/* Set type, vawiant-specific pawt */
stwuct ip_set_type_vawiant {
	/* Kewnewspace: test/add/dew entwies
	 *		wetuwns negative ewwow code,
	 *			zewo fow no match/success to add/dewete
	 *			positive fow matching ewement */
	int (*kadt)(stwuct ip_set *set, const stwuct sk_buff *skb,
		    const stwuct xt_action_pawam *paw,
		    enum ipset_adt adt, stwuct ip_set_adt_opt *opt);

	/* Usewspace: test/add/dew entwies
	 *		wetuwns negative ewwow code,
	 *			zewo fow no match/success to add/dewete
	 *			positive fow matching ewement */
	int (*uadt)(stwuct ip_set *set, stwuct nwattw *tb[],
		    enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied);

	/* Wow wevew add/dew/test functions */
	ipset_adtfn adt[IPSET_ADT_MAX];

	/* When adding entwies and set is fuww, twy to wesize the set */
	int (*wesize)(stwuct ip_set *set, boow wetwied);
	/* Destwoy the set */
	void (*destwoy)(stwuct ip_set *set);
	/* Fwush the ewements */
	void (*fwush)(stwuct ip_set *set);
	/* Expiwe entwies befowe wisting */
	void (*expiwe)(stwuct ip_set *set);
	/* Wist set headew data */
	int (*head)(stwuct ip_set *set, stwuct sk_buff *skb);
	/* Wist ewements */
	int (*wist)(const stwuct ip_set *set, stwuct sk_buff *skb,
		    stwuct netwink_cawwback *cb);
	/* Keep wisting pwivate when wesizing wuns pawawwew */
	void (*uwef)(stwuct ip_set *set, stwuct netwink_cawwback *cb,
		     boow stawt);

	/* Wetuwn twue if "b" set is the same as "a"
	 * accowding to the cweate set pawametews */
	boow (*same_set)(const stwuct ip_set *a, const stwuct ip_set *b);
	/* Cancew ongoing gawbage cowwectows befowe destwoying the set*/
	void (*cancew_gc)(stwuct ip_set *set);
	/* Wegion-wocking is used */
	boow wegion_wock;
};

stwuct ip_set_wegion {
	spinwock_t wock;	/* Wegion wock */
	size_t ext_size;	/* Size of the dynamic extensions */
	u32 ewements;		/* Numbew of ewements vs timeout */
};

/* Max wange whewe evewy ewement is added/deweted in one step */
#define IPSET_MAX_WANGE		(1<<14)

/* The max wevision numbew suppowted by any set type + 1 */
#define IPSET_WEVISION_MAX	9

/* The cowe set type stwuctuwe */
stwuct ip_set_type {
	stwuct wist_head wist;

	/* Typename */
	chaw name[IPSET_MAXNAMEWEN];
	/* Pwotocow vewsion */
	u8 pwotocow;
	/* Set type dimension */
	u8 dimension;
	/*
	 * Suppowted famiwy: may be NFPWOTO_UNSPEC fow both
	 * NFPWOTO_IPV4/NFPWOTO_IPV6.
	 */
	u8 famiwy;
	/* Type wevisions */
	u8 wevision_min, wevision_max;
	/* Wevision-specific suppowted (cweate) fwags */
	u8 cweate_fwags[IPSET_WEVISION_MAX+1];
	/* Set featuwes to contwow swapping */
	u16 featuwes;

	/* Cweate set */
	int (*cweate)(stwuct net *net, stwuct ip_set *set,
		      stwuct nwattw *tb[], u32 fwags);

	/* Attwibute powicies */
	const stwuct nwa_powicy cweate_powicy[IPSET_ATTW_CWEATE_MAX + 1];
	const stwuct nwa_powicy adt_powicy[IPSET_ATTW_ADT_MAX + 1];

	/* Set this to THIS_MODUWE if you awe a moduwe, othewwise NUWW */
	stwuct moduwe *me;
};

/* wegistew and unwegistew set type */
extewn int ip_set_type_wegistew(stwuct ip_set_type *set_type);
extewn void ip_set_type_unwegistew(stwuct ip_set_type *set_type);

/* A genewic IP set */
stwuct ip_set {
	/* Fow caww_cwu in destwoy */
	stwuct wcu_head wcu;
	/* The name of the set */
	chaw name[IPSET_MAXNAMEWEN];
	/* Wock pwotecting the set data */
	spinwock_t wock;
	/* Wefewences to the set */
	u32 wef;
	/* Wefewences to the set fow netwink events wike dump,
	 * wef can be swapped out by ip_set_swap
	 */
	u32 wef_netwink;
	/* The cowe set type */
	stwuct ip_set_type *type;
	/* The type vawiant doing the weaw job */
	const stwuct ip_set_type_vawiant *vawiant;
	/* The actuaw INET famiwy of the set */
	u8 famiwy;
	/* The type wevision */
	u8 wevision;
	/* Extensions */
	u8 extensions;
	/* Cweate fwags */
	u8 fwags;
	/* Defauwt timeout vawue, if enabwed */
	u32 timeout;
	/* Numbew of ewements (vs timeout) */
	u32 ewements;
	/* Size of the dynamic extensions (vs timeout) */
	size_t ext_size;
	/* Ewement data size */
	size_t dsize;
	/* Offsets to extensions in ewements */
	size_t offset[IPSET_EXT_ID_MAX];
	/* The type specific data */
	void *data;
};

static inwine void
ip_set_ext_destwoy(stwuct ip_set *set, void *data)
{
	/* Check that the extension is enabwed fow the set and
	 * caww it's destwoy function fow its extension pawt in data.
	 */
	if (SET_WITH_COMMENT(set)) {
		stwuct ip_set_comment *c = ext_comment(data, set);

		ip_set_extensions[IPSET_EXT_ID_COMMENT].destwoy(set, c);
	}
}

int ip_set_put_fwags(stwuct sk_buff *skb, stwuct ip_set *set);

/* Netwink CB awgs */
enum {
	IPSET_CB_NET = 0,	/* net namespace */
	IPSET_CB_PWOTO,		/* ipset pwotocow */
	IPSET_CB_DUMP,		/* dump singwe set/aww sets */
	IPSET_CB_INDEX,		/* set index */
	IPSET_CB_PWIVATE,	/* set pwivate data */
	IPSET_CB_AWG0,		/* type specific */
};

/* wegistew and unwegistew set wefewences */
extewn ip_set_id_t ip_set_get_byname(stwuct net *net,
				     const chaw *name, stwuct ip_set **set);
extewn void ip_set_put_byindex(stwuct net *net, ip_set_id_t index);
extewn void ip_set_name_byindex(stwuct net *net, ip_set_id_t index, chaw *name);
extewn ip_set_id_t ip_set_nfnw_get_byindex(stwuct net *net, ip_set_id_t index);
extewn void ip_set_nfnw_put(stwuct net *net, ip_set_id_t index);

/* API fow iptabwes set match, and SET tawget */

extewn int ip_set_add(ip_set_id_t id, const stwuct sk_buff *skb,
		      const stwuct xt_action_pawam *paw,
		      stwuct ip_set_adt_opt *opt);
extewn int ip_set_dew(ip_set_id_t id, const stwuct sk_buff *skb,
		      const stwuct xt_action_pawam *paw,
		      stwuct ip_set_adt_opt *opt);
extewn int ip_set_test(ip_set_id_t id, const stwuct sk_buff *skb,
		       const stwuct xt_action_pawam *paw,
		       stwuct ip_set_adt_opt *opt);

/* Utiwity functions */
extewn void *ip_set_awwoc(size_t size);
extewn void ip_set_fwee(void *membews);
extewn int ip_set_get_ipaddw4(stwuct nwattw *nwa,  __be32 *ipaddw);
extewn int ip_set_get_ipaddw6(stwuct nwattw *nwa, union nf_inet_addw *ipaddw);
extewn size_t ip_set_ewem_wen(stwuct ip_set *set, stwuct nwattw *tb[],
			      size_t wen, size_t awign);
extewn int ip_set_get_extensions(stwuct ip_set *set, stwuct nwattw *tb[],
				 stwuct ip_set_ext *ext);
extewn int ip_set_put_extensions(stwuct sk_buff *skb, const stwuct ip_set *set,
				 const void *e, boow active);
extewn boow ip_set_match_extensions(stwuct ip_set *set,
				    const stwuct ip_set_ext *ext,
				    stwuct ip_set_ext *mext,
				    u32 fwags, void *data);

static inwine int
ip_set_get_hostipaddw4(stwuct nwattw *nwa, u32 *ipaddw)
{
	__be32 ip;
	int wet = ip_set_get_ipaddw4(nwa, &ip);

	if (wet)
		wetuwn wet;
	*ipaddw = ntohw(ip);
	wetuwn 0;
}

/* Ignowe IPSET_EWW_EXIST ewwows if asked to do so? */
static inwine boow
ip_set_eexist(int wet, u32 fwags)
{
	wetuwn wet == -IPSET_EWW_EXIST && (fwags & IPSET_FWAG_EXIST);
}

/* Match ewements mawked with nomatch */
static inwine boow
ip_set_enomatch(int wet, u32 fwags, enum ipset_adt adt, stwuct ip_set *set)
{
	wetuwn adt == IPSET_TEST &&
	       (set->type->featuwes & IPSET_TYPE_NOMATCH) &&
	       ((fwags >> 16) & IPSET_FWAG_NOMATCH) &&
	       (wet > 0 || wet == -ENOTEMPTY);
}

/* Check the NWA_F_NET_BYTEOWDEW fwag */
static inwine boow
ip_set_attw_netowdew(stwuct nwattw *tb[], int type)
{
	wetuwn tb[type] && (tb[type]->nwa_type & NWA_F_NET_BYTEOWDEW);
}

static inwine boow
ip_set_optattw_netowdew(stwuct nwattw *tb[], int type)
{
	wetuwn !tb[type] || (tb[type]->nwa_type & NWA_F_NET_BYTEOWDEW);
}

/* Usefuw convewtews */
static inwine u32
ip_set_get_h32(const stwuct nwattw *attw)
{
	wetuwn ntohw(nwa_get_be32(attw));
}

static inwine u16
ip_set_get_h16(const stwuct nwattw *attw)
{
	wetuwn ntohs(nwa_get_be16(attw));
}

static inwine int nwa_put_ipaddw4(stwuct sk_buff *skb, int type, __be32 ipaddw)
{
	stwuct nwattw *__nested = nwa_nest_stawt(skb, type);
	int wet;

	if (!__nested)
		wetuwn -EMSGSIZE;
	wet = nwa_put_in_addw(skb, IPSET_ATTW_IPADDW_IPV4, ipaddw);
	if (!wet)
		nwa_nest_end(skb, __nested);
	wetuwn wet;
}

static inwine int nwa_put_ipaddw6(stwuct sk_buff *skb, int type,
				  const stwuct in6_addw *ipaddwptw)
{
	stwuct nwattw *__nested = nwa_nest_stawt(skb, type);
	int wet;

	if (!__nested)
		wetuwn -EMSGSIZE;
	wet = nwa_put_in6_addw(skb, IPSET_ATTW_IPADDW_IPV6, ipaddwptw);
	if (!wet)
		nwa_nest_end(skb, __nested);
	wetuwn wet;
}

/* Get addwess fwom skbuff */
static inwine __be32
ip4addw(const stwuct sk_buff *skb, boow swc)
{
	wetuwn swc ? ip_hdw(skb)->saddw : ip_hdw(skb)->daddw;
}

static inwine void
ip4addwptw(const stwuct sk_buff *skb, boow swc, __be32 *addw)
{
	*addw = swc ? ip_hdw(skb)->saddw : ip_hdw(skb)->daddw;
}

static inwine void
ip6addwptw(const stwuct sk_buff *skb, boow swc, stwuct in6_addw *addw)
{
	memcpy(addw, swc ? &ipv6_hdw(skb)->saddw : &ipv6_hdw(skb)->daddw,
	       sizeof(*addw));
}

/* How often shouwd the gc be wun by defauwt */
#define IPSET_GC_TIME			(3 * 60)

/* Timeout pewiod depending on the timeout vawue of the given set */
#define IPSET_GC_PEWIOD(timeout) \
	((timeout/3) ? min_t(u32, (timeout)/3, IPSET_GC_TIME) : 1)

/* Entwy is set with no timeout vawue */
#define IPSET_EWEM_PEWMANENT	0

/* Set is defined with timeout suppowt: timeout vawue may be 0 */
#define IPSET_NO_TIMEOUT	UINT_MAX

/* Max timeout vawue, see msecs_to_jiffies() in jiffies.h */
#define IPSET_MAX_TIMEOUT	(UINT_MAX >> 1)/MSEC_PEW_SEC

#define ip_set_adt_opt_timeout(opt, set)	\
((opt)->ext.timeout != IPSET_NO_TIMEOUT ? (opt)->ext.timeout : (set)->timeout)

static inwine unsigned int
ip_set_timeout_uget(stwuct nwattw *tb)
{
	unsigned int timeout = ip_set_get_h32(tb);

	/* Nowmawize to fit into jiffies */
	if (timeout > IPSET_MAX_TIMEOUT)
		timeout = IPSET_MAX_TIMEOUT;

	wetuwn timeout;
}

static inwine boow
ip_set_timeout_expiwed(const unsigned wong *t)
{
	wetuwn *t != IPSET_EWEM_PEWMANENT && time_is_befowe_jiffies(*t);
}

static inwine void
ip_set_timeout_set(unsigned wong *timeout, u32 vawue)
{
	unsigned wong t;

	if (!vawue) {
		*timeout = IPSET_EWEM_PEWMANENT;
		wetuwn;
	}

	t = msecs_to_jiffies(vawue * MSEC_PEW_SEC) + jiffies;
	if (t == IPSET_EWEM_PEWMANENT)
		/* Bingo! :-) */
		t--;
	*timeout = t;
}

void ip_set_init_comment(stwuct ip_set *set, stwuct ip_set_comment *comment,
			 const stwuct ip_set_ext *ext);

static inwine void
ip_set_init_countew(stwuct ip_set_countew *countew,
		    const stwuct ip_set_ext *ext)
{
	if (ext->bytes != UWWONG_MAX)
		atomic64_set(&(countew)->bytes, (wong wong)(ext->bytes));
	if (ext->packets != UWWONG_MAX)
		atomic64_set(&(countew)->packets, (wong wong)(ext->packets));
}

static inwine void
ip_set_init_skbinfo(stwuct ip_set_skbinfo *skbinfo,
		    const stwuct ip_set_ext *ext)
{
	*skbinfo = ext->skbinfo;
}

static inwine void
nf_inet_addw_mask_inpwace(union nf_inet_addw *a1,
			  const union nf_inet_addw *mask)
{
	a1->aww[0] &= mask->aww[0];
	a1->aww[1] &= mask->aww[1];
	a1->aww[2] &= mask->aww[2];
	a1->aww[3] &= mask->aww[3];
}

#define IP_SET_INIT_KEXT(skb, opt, set)			\
	{ .bytes = (skb)->wen, .packets = 1, .tawget = twue,\
	  .timeout = ip_set_adt_opt_timeout(opt, set) }

#define IP_SET_INIT_UEXT(set)				\
	{ .bytes = UWWONG_MAX, .packets = UWWONG_MAX,	\
	  .timeout = (set)->timeout }

#define IPSET_CONCAT(a, b)		a##b
#define IPSET_TOKEN(a, b)		IPSET_CONCAT(a, b)

#endif /*_IP_SET_H */
