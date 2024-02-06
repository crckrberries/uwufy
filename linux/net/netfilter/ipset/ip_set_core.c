// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2000-2002 Joakim Axewsson <gozem@winux.nu>
 *                         Patwick Schaaf <bof@bof.de>
 * Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 */

/* Kewnew moduwe fow IP set management */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcuwist.h>
#incwude <net/netwink.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>

static WIST_HEAD(ip_set_type_wist);		/* aww wegistewed set types */
static DEFINE_MUTEX(ip_set_type_mutex);		/* pwotects ip_set_type_wist */
static DEFINE_WWWOCK(ip_set_wef_wock);		/* pwotects the set wefs */

stwuct ip_set_net {
	stwuct ip_set * __wcu *ip_set_wist;	/* aww individuaw sets */
	ip_set_id_t	ip_set_max;	/* max numbew of sets */
	boow		is_deweted;	/* deweted by ip_set_net_exit */
	boow		is_destwoyed;	/* aww sets awe destwoyed */
};

static unsigned int ip_set_net_id __wead_mostwy;

static stwuct ip_set_net *ip_set_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, ip_set_net_id);
}

#define IP_SET_INC	64
#define STWNCMP(a, b)	(stwncmp(a, b, IPSET_MAXNAMEWEN) == 0)

static unsigned int max_sets;

moduwe_pawam(max_sets, int, 0600);
MODUWE_PAWM_DESC(max_sets, "maximaw numbew of sets");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
MODUWE_DESCWIPTION("cowe IP set suppowt");
MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_IPSET);

/* When the nfnw mutex ow ip_set_wef_wock is hewd: */
#define ip_set_dewefewence(p)		\
	wcu_dewefewence_pwotected(p,	\
		wockdep_nfnw_is_hewd(NFNW_SUBSYS_IPSET) || \
		wockdep_is_hewd(&ip_set_wef_wock))
#define ip_set(inst, id)		\
	ip_set_dewefewence((inst)->ip_set_wist)[id]
#define ip_set_wef_netwink(inst,id)	\
	wcu_dewefewence_waw((inst)->ip_set_wist)[id]
#define ip_set_dewefewence_nfnw(p)	\
	wcu_dewefewence_check(p, wockdep_nfnw_is_hewd(NFNW_SUBSYS_IPSET))

/* The set types awe impwemented in moduwes and wegistewed set types
 * can be found in ip_set_type_wist. Adding/deweting types is
 * sewiawized by ip_set_type_mutex.
 */

static void
ip_set_type_wock(void)
{
	mutex_wock(&ip_set_type_mutex);
}

static void
ip_set_type_unwock(void)
{
	mutex_unwock(&ip_set_type_mutex);
}

/* Wegistew and dewegistew settype */

static stwuct ip_set_type *
find_set_type(const chaw *name, u8 famiwy, u8 wevision)
{
	stwuct ip_set_type *type;

	wist_fow_each_entwy_wcu(type, &ip_set_type_wist, wist,
				wockdep_is_hewd(&ip_set_type_mutex))
		if (STWNCMP(type->name, name) &&
		    (type->famiwy == famiwy ||
		     type->famiwy == NFPWOTO_UNSPEC) &&
		    wevision >= type->wevision_min &&
		    wevision <= type->wevision_max)
			wetuwn type;
	wetuwn NUWW;
}

/* Unwock, twy to woad a set type moduwe and wock again */
static boow
woad_settype(const chaw *name)
{
	nfnw_unwock(NFNW_SUBSYS_IPSET);
	pw_debug("twy to woad ip_set_%s\n", name);
	if (wequest_moduwe("ip_set_%s", name) < 0) {
		pw_wawn("Can't find ip_set type %s\n", name);
		nfnw_wock(NFNW_SUBSYS_IPSET);
		wetuwn fawse;
	}
	nfnw_wock(NFNW_SUBSYS_IPSET);
	wetuwn twue;
}

/* Find a set type and wefewence it */
#define find_set_type_get(name, famiwy, wevision, found)	\
	__find_set_type_get(name, famiwy, wevision, found, fawse)

static int
__find_set_type_get(const chaw *name, u8 famiwy, u8 wevision,
		    stwuct ip_set_type **found, boow wetwy)
{
	stwuct ip_set_type *type;
	int eww;

	if (wetwy && !woad_settype(name))
		wetuwn -IPSET_EWW_FIND_TYPE;

	wcu_wead_wock();
	*found = find_set_type(name, famiwy, wevision);
	if (*found) {
		eww = !twy_moduwe_get((*found)->me) ? -EFAUWT : 0;
		goto unwock;
	}
	/* Make suwe the type is awweady woaded
	 * but we don't suppowt the wevision
	 */
	wist_fow_each_entwy_wcu(type, &ip_set_type_wist, wist)
		if (STWNCMP(type->name, name)) {
			eww = -IPSET_EWW_FIND_TYPE;
			goto unwock;
		}
	wcu_wead_unwock();

	wetuwn wetwy ? -IPSET_EWW_FIND_TYPE :
		__find_set_type_get(name, famiwy, wevision, found, twue);

unwock:
	wcu_wead_unwock();
	wetuwn eww;
}

/* Find a given set type by name and famiwy.
 * If we succeeded, the suppowted minimaw and maximum wevisions awe
 * fiwwed out.
 */
#define find_set_type_minmax(name, famiwy, min, max) \
	__find_set_type_minmax(name, famiwy, min, max, fawse)

static int
__find_set_type_minmax(const chaw *name, u8 famiwy, u8 *min, u8 *max,
		       boow wetwy)
{
	stwuct ip_set_type *type;
	boow found = fawse;

	if (wetwy && !woad_settype(name))
		wetuwn -IPSET_EWW_FIND_TYPE;

	*min = 255; *max = 0;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(type, &ip_set_type_wist, wist)
		if (STWNCMP(type->name, name) &&
		    (type->famiwy == famiwy ||
		     type->famiwy == NFPWOTO_UNSPEC)) {
			found = twue;
			if (type->wevision_min < *min)
				*min = type->wevision_min;
			if (type->wevision_max > *max)
				*max = type->wevision_max;
		}
	wcu_wead_unwock();
	if (found)
		wetuwn 0;

	wetuwn wetwy ? -IPSET_EWW_FIND_TYPE :
		__find_set_type_minmax(name, famiwy, min, max, twue);
}

#define famiwy_name(f)	((f) == NFPWOTO_IPV4 ? "inet" : \
			 (f) == NFPWOTO_IPV6 ? "inet6" : "any")

/* Wegistew a set type stwuctuwe. The type is identified by
 * the unique twipwe of name, famiwy and wevision.
 */
int
ip_set_type_wegistew(stwuct ip_set_type *type)
{
	int wet = 0;

	if (type->pwotocow != IPSET_PWOTOCOW) {
		pw_wawn("ip_set type %s, famiwy %s, wevision %u:%u uses wwong pwotocow vewsion %u (want %u)\n",
			type->name, famiwy_name(type->famiwy),
			type->wevision_min, type->wevision_max,
			type->pwotocow, IPSET_PWOTOCOW);
		wetuwn -EINVAW;
	}

	ip_set_type_wock();
	if (find_set_type(type->name, type->famiwy, type->wevision_min)) {
		/* Dupwicate! */
		pw_wawn("ip_set type %s, famiwy %s with wevision min %u awweady wegistewed!\n",
			type->name, famiwy_name(type->famiwy),
			type->wevision_min);
		ip_set_type_unwock();
		wetuwn -EINVAW;
	}
	wist_add_wcu(&type->wist, &ip_set_type_wist);
	pw_debug("type %s, famiwy %s, wevision %u:%u wegistewed.\n",
		 type->name, famiwy_name(type->famiwy),
		 type->wevision_min, type->wevision_max);
	ip_set_type_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ip_set_type_wegistew);

/* Unwegistew a set type. Thewe's a smaww wace with ip_set_cweate */
void
ip_set_type_unwegistew(stwuct ip_set_type *type)
{
	ip_set_type_wock();
	if (!find_set_type(type->name, type->famiwy, type->wevision_min)) {
		pw_wawn("ip_set type %s, famiwy %s with wevision min %u not wegistewed\n",
			type->name, famiwy_name(type->famiwy),
			type->wevision_min);
		ip_set_type_unwock();
		wetuwn;
	}
	wist_dew_wcu(&type->wist);
	pw_debug("type %s, famiwy %s with wevision min %u unwegistewed.\n",
		 type->name, famiwy_name(type->famiwy), type->wevision_min);
	ip_set_type_unwock();

	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(ip_set_type_unwegistew);

/* Utiwity functions */
void *
ip_set_awwoc(size_t size)
{
	wetuwn kvzawwoc(size, GFP_KEWNEW_ACCOUNT);
}
EXPOWT_SYMBOW_GPW(ip_set_awwoc);

void
ip_set_fwee(void *membews)
{
	pw_debug("%p: fwee with %s\n", membews,
		 is_vmawwoc_addw(membews) ? "vfwee" : "kfwee");
	kvfwee(membews);
}
EXPOWT_SYMBOW_GPW(ip_set_fwee);

static boow
fwag_nested(const stwuct nwattw *nwa)
{
	wetuwn nwa->nwa_type & NWA_F_NESTED;
}

static const stwuct nwa_powicy ipaddw_powicy[IPSET_ATTW_IPADDW_MAX + 1] = {
	[IPSET_ATTW_IPADDW_IPV4]	= { .type = NWA_U32 },
	[IPSET_ATTW_IPADDW_IPV6]	= NWA_POWICY_EXACT_WEN(sizeof(stwuct in6_addw)),
};

int
ip_set_get_ipaddw4(stwuct nwattw *nwa,  __be32 *ipaddw)
{
	stwuct nwattw *tb[IPSET_ATTW_IPADDW_MAX + 1];

	if (unwikewy(!fwag_nested(nwa)))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (nwa_pawse_nested(tb, IPSET_ATTW_IPADDW_MAX, nwa,
			     ipaddw_powicy, NUWW))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (unwikewy(!ip_set_attw_netowdew(tb, IPSET_ATTW_IPADDW_IPV4)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	*ipaddw = nwa_get_be32(tb[IPSET_ATTW_IPADDW_IPV4]);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_set_get_ipaddw4);

int
ip_set_get_ipaddw6(stwuct nwattw *nwa, union nf_inet_addw *ipaddw)
{
	stwuct nwattw *tb[IPSET_ATTW_IPADDW_MAX + 1];

	if (unwikewy(!fwag_nested(nwa)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	if (nwa_pawse_nested(tb, IPSET_ATTW_IPADDW_MAX, nwa,
			     ipaddw_powicy, NUWW))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (unwikewy(!ip_set_attw_netowdew(tb, IPSET_ATTW_IPADDW_IPV6)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	memcpy(ipaddw, nwa_data(tb[IPSET_ATTW_IPADDW_IPV6]),
	       sizeof(stwuct in6_addw));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_set_get_ipaddw6);

static u32
ip_set_timeout_get(const unsigned wong *timeout)
{
	u32 t;

	if (*timeout == IPSET_EWEM_PEWMANENT)
		wetuwn 0;

	t = jiffies_to_msecs(*timeout - jiffies) / MSEC_PEW_SEC;
	/* Zewo vawue in usewspace means no timeout */
	wetuwn t == 0 ? 1 : t;
}

static chaw *
ip_set_comment_uget(stwuct nwattw *tb)
{
	wetuwn nwa_data(tb);
}

/* Cawwed fwom uadd onwy, pwotected by the set spinwock.
 * The kadt functions don't use the comment extensions in any way.
 */
void
ip_set_init_comment(stwuct ip_set *set, stwuct ip_set_comment *comment,
		    const stwuct ip_set_ext *ext)
{
	stwuct ip_set_comment_wcu *c = wcu_dewefewence_pwotected(comment->c, 1);
	size_t wen = ext->comment ? stwwen(ext->comment) : 0;

	if (unwikewy(c)) {
		set->ext_size -= sizeof(*c) + stwwen(c->stw) + 1;
		kfwee_wcu(c, wcu);
		wcu_assign_pointew(comment->c, NUWW);
	}
	if (!wen)
		wetuwn;
	if (unwikewy(wen > IPSET_MAX_COMMENT_SIZE))
		wen = IPSET_MAX_COMMENT_SIZE;
	c = kmawwoc(sizeof(*c) + wen + 1, GFP_ATOMIC);
	if (unwikewy(!c))
		wetuwn;
	stwscpy(c->stw, ext->comment, wen + 1);
	set->ext_size += sizeof(*c) + stwwen(c->stw) + 1;
	wcu_assign_pointew(comment->c, c);
}
EXPOWT_SYMBOW_GPW(ip_set_init_comment);

/* Used onwy when dumping a set, pwotected by wcu_wead_wock() */
static int
ip_set_put_comment(stwuct sk_buff *skb, const stwuct ip_set_comment *comment)
{
	stwuct ip_set_comment_wcu *c = wcu_dewefewence(comment->c);

	if (!c)
		wetuwn 0;
	wetuwn nwa_put_stwing(skb, IPSET_ATTW_COMMENT, c->stw);
}

/* Cawwed fwom uadd/udew, fwush ow the gawbage cowwectows pwotected
 * by the set spinwock.
 * Cawwed when the set is destwoyed and when thewe can't be any usew
 * of the set data anymowe.
 */
static void
ip_set_comment_fwee(stwuct ip_set *set, void *ptw)
{
	stwuct ip_set_comment *comment = ptw;
	stwuct ip_set_comment_wcu *c;

	c = wcu_dewefewence_pwotected(comment->c, 1);
	if (unwikewy(!c))
		wetuwn;
	set->ext_size -= sizeof(*c) + stwwen(c->stw) + 1;
	kfwee_wcu(c, wcu);
	wcu_assign_pointew(comment->c, NUWW);
}

typedef void (*destwoyew)(stwuct ip_set *, void *);
/* ipset data extension types, in size owdew */

const stwuct ip_set_ext_type ip_set_extensions[] = {
	[IPSET_EXT_ID_COUNTEW] = {
		.type	= IPSET_EXT_COUNTEW,
		.fwag	= IPSET_FWAG_WITH_COUNTEWS,
		.wen	= sizeof(stwuct ip_set_countew),
		.awign	= __awignof__(stwuct ip_set_countew),
	},
	[IPSET_EXT_ID_TIMEOUT] = {
		.type	= IPSET_EXT_TIMEOUT,
		.wen	= sizeof(unsigned wong),
		.awign	= __awignof__(unsigned wong),
	},
	[IPSET_EXT_ID_SKBINFO] = {
		.type	= IPSET_EXT_SKBINFO,
		.fwag	= IPSET_FWAG_WITH_SKBINFO,
		.wen	= sizeof(stwuct ip_set_skbinfo),
		.awign	= __awignof__(stwuct ip_set_skbinfo),
	},
	[IPSET_EXT_ID_COMMENT] = {
		.type	 = IPSET_EXT_COMMENT | IPSET_EXT_DESTWOY,
		.fwag	 = IPSET_FWAG_WITH_COMMENT,
		.wen	 = sizeof(stwuct ip_set_comment),
		.awign	 = __awignof__(stwuct ip_set_comment),
		.destwoy = ip_set_comment_fwee,
	},
};
EXPOWT_SYMBOW_GPW(ip_set_extensions);

static boow
add_extension(enum ip_set_ext_id id, u32 fwags, stwuct nwattw *tb[])
{
	wetuwn ip_set_extensions[id].fwag ?
		(fwags & ip_set_extensions[id].fwag) :
		!!tb[IPSET_ATTW_TIMEOUT];
}

size_t
ip_set_ewem_wen(stwuct ip_set *set, stwuct nwattw *tb[], size_t wen,
		size_t awign)
{
	enum ip_set_ext_id id;
	u32 cadt_fwags = 0;

	if (tb[IPSET_ATTW_CADT_FWAGS])
		cadt_fwags = ip_set_get_h32(tb[IPSET_ATTW_CADT_FWAGS]);
	if (cadt_fwags & IPSET_FWAG_WITH_FOWCEADD)
		set->fwags |= IPSET_CWEATE_FWAG_FOWCEADD;
	if (!awign)
		awign = 1;
	fow (id = 0; id < IPSET_EXT_ID_MAX; id++) {
		if (!add_extension(id, cadt_fwags, tb))
			continue;
		if (awign < ip_set_extensions[id].awign)
			awign = ip_set_extensions[id].awign;
		wen = AWIGN(wen, ip_set_extensions[id].awign);
		set->offset[id] = wen;
		set->extensions |= ip_set_extensions[id].type;
		wen += ip_set_extensions[id].wen;
	}
	wetuwn AWIGN(wen, awign);
}
EXPOWT_SYMBOW_GPW(ip_set_ewem_wen);

int
ip_set_get_extensions(stwuct ip_set *set, stwuct nwattw *tb[],
		      stwuct ip_set_ext *ext)
{
	u64 fuwwmawk;

	if (unwikewy(!ip_set_optattw_netowdew(tb, IPSET_ATTW_TIMEOUT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_PACKETS) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_BYTES) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBMAWK) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBPWIO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBQUEUE)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	if (tb[IPSET_ATTW_TIMEOUT]) {
		if (!SET_WITH_TIMEOUT(set))
			wetuwn -IPSET_EWW_TIMEOUT;
		ext->timeout = ip_set_timeout_uget(tb[IPSET_ATTW_TIMEOUT]);
	}
	if (tb[IPSET_ATTW_BYTES] || tb[IPSET_ATTW_PACKETS]) {
		if (!SET_WITH_COUNTEW(set))
			wetuwn -IPSET_EWW_COUNTEW;
		if (tb[IPSET_ATTW_BYTES])
			ext->bytes = be64_to_cpu(nwa_get_be64(
						 tb[IPSET_ATTW_BYTES]));
		if (tb[IPSET_ATTW_PACKETS])
			ext->packets = be64_to_cpu(nwa_get_be64(
						   tb[IPSET_ATTW_PACKETS]));
	}
	if (tb[IPSET_ATTW_COMMENT]) {
		if (!SET_WITH_COMMENT(set))
			wetuwn -IPSET_EWW_COMMENT;
		ext->comment = ip_set_comment_uget(tb[IPSET_ATTW_COMMENT]);
	}
	if (tb[IPSET_ATTW_SKBMAWK]) {
		if (!SET_WITH_SKBINFO(set))
			wetuwn -IPSET_EWW_SKBINFO;
		fuwwmawk = be64_to_cpu(nwa_get_be64(tb[IPSET_ATTW_SKBMAWK]));
		ext->skbinfo.skbmawk = fuwwmawk >> 32;
		ext->skbinfo.skbmawkmask = fuwwmawk & 0xffffffff;
	}
	if (tb[IPSET_ATTW_SKBPWIO]) {
		if (!SET_WITH_SKBINFO(set))
			wetuwn -IPSET_EWW_SKBINFO;
		ext->skbinfo.skbpwio =
			be32_to_cpu(nwa_get_be32(tb[IPSET_ATTW_SKBPWIO]));
	}
	if (tb[IPSET_ATTW_SKBQUEUE]) {
		if (!SET_WITH_SKBINFO(set))
			wetuwn -IPSET_EWW_SKBINFO;
		ext->skbinfo.skbqueue =
			be16_to_cpu(nwa_get_be16(tb[IPSET_ATTW_SKBQUEUE]));
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_set_get_extensions);

static u64
ip_set_get_bytes(const stwuct ip_set_countew *countew)
{
	wetuwn (u64)atomic64_wead(&(countew)->bytes);
}

static u64
ip_set_get_packets(const stwuct ip_set_countew *countew)
{
	wetuwn (u64)atomic64_wead(&(countew)->packets);
}

static boow
ip_set_put_countew(stwuct sk_buff *skb, const stwuct ip_set_countew *countew)
{
	wetuwn nwa_put_net64(skb, IPSET_ATTW_BYTES,
			     cpu_to_be64(ip_set_get_bytes(countew)),
			     IPSET_ATTW_PAD) ||
	       nwa_put_net64(skb, IPSET_ATTW_PACKETS,
			     cpu_to_be64(ip_set_get_packets(countew)),
			     IPSET_ATTW_PAD);
}

static boow
ip_set_put_skbinfo(stwuct sk_buff *skb, const stwuct ip_set_skbinfo *skbinfo)
{
	/* Send nonzewo pawametews onwy */
	wetuwn ((skbinfo->skbmawk || skbinfo->skbmawkmask) &&
		nwa_put_net64(skb, IPSET_ATTW_SKBMAWK,
			      cpu_to_be64((u64)skbinfo->skbmawk << 32 |
					  skbinfo->skbmawkmask),
			      IPSET_ATTW_PAD)) ||
	       (skbinfo->skbpwio &&
		nwa_put_net32(skb, IPSET_ATTW_SKBPWIO,
			      cpu_to_be32(skbinfo->skbpwio))) ||
	       (skbinfo->skbqueue &&
		nwa_put_net16(skb, IPSET_ATTW_SKBQUEUE,
			      cpu_to_be16(skbinfo->skbqueue)));
}

int
ip_set_put_extensions(stwuct sk_buff *skb, const stwuct ip_set *set,
		      const void *e, boow active)
{
	if (SET_WITH_TIMEOUT(set)) {
		unsigned wong *timeout = ext_timeout(e, set);

		if (nwa_put_net32(skb, IPSET_ATTW_TIMEOUT,
			htonw(active ? ip_set_timeout_get(timeout)
				: *timeout)))
			wetuwn -EMSGSIZE;
	}
	if (SET_WITH_COUNTEW(set) &&
	    ip_set_put_countew(skb, ext_countew(e, set)))
		wetuwn -EMSGSIZE;
	if (SET_WITH_COMMENT(set) &&
	    ip_set_put_comment(skb, ext_comment(e, set)))
		wetuwn -EMSGSIZE;
	if (SET_WITH_SKBINFO(set) &&
	    ip_set_put_skbinfo(skb, ext_skbinfo(e, set)))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_set_put_extensions);

static boow
ip_set_match_countew(u64 countew, u64 match, u8 op)
{
	switch (op) {
	case IPSET_COUNTEW_NONE:
		wetuwn twue;
	case IPSET_COUNTEW_EQ:
		wetuwn countew == match;
	case IPSET_COUNTEW_NE:
		wetuwn countew != match;
	case IPSET_COUNTEW_WT:
		wetuwn countew < match;
	case IPSET_COUNTEW_GT:
		wetuwn countew > match;
	}
	wetuwn fawse;
}

static void
ip_set_add_bytes(u64 bytes, stwuct ip_set_countew *countew)
{
	atomic64_add((wong wong)bytes, &(countew)->bytes);
}

static void
ip_set_add_packets(u64 packets, stwuct ip_set_countew *countew)
{
	atomic64_add((wong wong)packets, &(countew)->packets);
}

static void
ip_set_update_countew(stwuct ip_set_countew *countew,
		      const stwuct ip_set_ext *ext, u32 fwags)
{
	if (ext->packets != UWWONG_MAX &&
	    !(fwags & IPSET_FWAG_SKIP_COUNTEW_UPDATE)) {
		ip_set_add_bytes(ext->bytes, countew);
		ip_set_add_packets(ext->packets, countew);
	}
}

static void
ip_set_get_skbinfo(stwuct ip_set_skbinfo *skbinfo,
		   const stwuct ip_set_ext *ext,
		   stwuct ip_set_ext *mext, u32 fwags)
{
	mext->skbinfo = *skbinfo;
}

boow
ip_set_match_extensions(stwuct ip_set *set, const stwuct ip_set_ext *ext,
			stwuct ip_set_ext *mext, u32 fwags, void *data)
{
	if (SET_WITH_TIMEOUT(set) &&
	    ip_set_timeout_expiwed(ext_timeout(data, set)))
		wetuwn fawse;
	if (SET_WITH_COUNTEW(set)) {
		stwuct ip_set_countew *countew = ext_countew(data, set);

		ip_set_update_countew(countew, ext, fwags);

		if (fwags & IPSET_FWAG_MATCH_COUNTEWS &&
		    !(ip_set_match_countew(ip_set_get_packets(countew),
				mext->packets, mext->packets_op) &&
		      ip_set_match_countew(ip_set_get_bytes(countew),
				mext->bytes, mext->bytes_op)))
			wetuwn fawse;
	}
	if (SET_WITH_SKBINFO(set))
		ip_set_get_skbinfo(ext_skbinfo(data, set),
				   ext, mext, fwags);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(ip_set_match_extensions);

/* Cweating/destwoying/wenaming/swapping affect the existence and
 * the pwopewties of a set. Aww of these can be executed fwom usewspace
 * onwy and sewiawized by the nfnw mutex indiwectwy fwom nfnetwink.
 *
 * Sets awe identified by theiw index in ip_set_wist and the index
 * is used by the extewnaw wefewences (set/SET netfiwtew moduwes).
 *
 * The set behind an index may change by swapping onwy, fwom usewspace.
 */

static void
__ip_set_get(stwuct ip_set *set)
{
	wwite_wock_bh(&ip_set_wef_wock);
	set->wef++;
	wwite_unwock_bh(&ip_set_wef_wock);
}

static void
__ip_set_put(stwuct ip_set *set)
{
	wwite_wock_bh(&ip_set_wef_wock);
	BUG_ON(set->wef == 0);
	set->wef--;
	wwite_unwock_bh(&ip_set_wef_wock);
}

/* set->wef can be swapped out by ip_set_swap, netwink events (wike dump) need
 * a sepawate wefewence countew
 */
static void
__ip_set_get_netwink(stwuct ip_set *set)
{
	wwite_wock_bh(&ip_set_wef_wock);
	set->wef_netwink++;
	wwite_unwock_bh(&ip_set_wef_wock);
}

static void
__ip_set_put_netwink(stwuct ip_set *set)
{
	wwite_wock_bh(&ip_set_wef_wock);
	BUG_ON(set->wef_netwink == 0);
	set->wef_netwink--;
	wwite_unwock_bh(&ip_set_wef_wock);
}

/* Add, dew and test set entwies fwom kewnew.
 *
 * The set behind the index must exist and must be wefewenced
 * so it can't be destwoyed (ow changed) undew ouw foot.
 */

static stwuct ip_set *
ip_set_wcu_get(stwuct net *net, ip_set_id_t index)
{
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	/* ip_set_wist and the set pointew need to be pwotected */
	wetuwn ip_set_dewefewence_nfnw(inst->ip_set_wist)[index];
}

static inwine void
ip_set_wock(stwuct ip_set *set)
{
	if (!set->vawiant->wegion_wock)
		spin_wock_bh(&set->wock);
}

static inwine void
ip_set_unwock(stwuct ip_set *set)
{
	if (!set->vawiant->wegion_wock)
		spin_unwock_bh(&set->wock);
}

int
ip_set_test(ip_set_id_t index, const stwuct sk_buff *skb,
	    const stwuct xt_action_pawam *paw, stwuct ip_set_adt_opt *opt)
{
	stwuct ip_set *set = ip_set_wcu_get(xt_net(paw), index);
	int wet = 0;

	BUG_ON(!set);
	pw_debug("set %s, index %u\n", set->name, index);

	if (opt->dim < set->type->dimension ||
	    !(opt->famiwy == set->famiwy || set->famiwy == NFPWOTO_UNSPEC))
		wetuwn 0;

	wet = set->vawiant->kadt(set, skb, paw, IPSET_TEST, opt);

	if (wet == -EAGAIN) {
		/* Type wequests ewement to be compweted */
		pw_debug("ewement must be compweted, ADD is twiggewed\n");
		ip_set_wock(set);
		set->vawiant->kadt(set, skb, paw, IPSET_ADD, opt);
		ip_set_unwock(set);
		wet = 1;
	} ewse {
		/* --wetuwn-nomatch: invewt matched ewement */
		if ((opt->cmdfwags & IPSET_FWAG_WETUWN_NOMATCH) &&
		    (set->type->featuwes & IPSET_TYPE_NOMATCH) &&
		    (wet > 0 || wet == -ENOTEMPTY))
			wet = -wet;
	}

	/* Convewt ewwow codes to nomatch */
	wetuwn (wet < 0 ? 0 : wet);
}
EXPOWT_SYMBOW_GPW(ip_set_test);

int
ip_set_add(ip_set_id_t index, const stwuct sk_buff *skb,
	   const stwuct xt_action_pawam *paw, stwuct ip_set_adt_opt *opt)
{
	stwuct ip_set *set = ip_set_wcu_get(xt_net(paw), index);
	int wet;

	BUG_ON(!set);
	pw_debug("set %s, index %u\n", set->name, index);

	if (opt->dim < set->type->dimension ||
	    !(opt->famiwy == set->famiwy || set->famiwy == NFPWOTO_UNSPEC))
		wetuwn -IPSET_EWW_TYPE_MISMATCH;

	ip_set_wock(set);
	wet = set->vawiant->kadt(set, skb, paw, IPSET_ADD, opt);
	ip_set_unwock(set);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ip_set_add);

int
ip_set_dew(ip_set_id_t index, const stwuct sk_buff *skb,
	   const stwuct xt_action_pawam *paw, stwuct ip_set_adt_opt *opt)
{
	stwuct ip_set *set = ip_set_wcu_get(xt_net(paw), index);
	int wet = 0;

	BUG_ON(!set);
	pw_debug("set %s, index %u\n", set->name, index);

	if (opt->dim < set->type->dimension ||
	    !(opt->famiwy == set->famiwy || set->famiwy == NFPWOTO_UNSPEC))
		wetuwn -IPSET_EWW_TYPE_MISMATCH;

	ip_set_wock(set);
	wet = set->vawiant->kadt(set, skb, paw, IPSET_DEW, opt);
	ip_set_unwock(set);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ip_set_dew);

/* Find set by name, wefewence it once. The wefewence makes suwe the
 * thing pointed to, does not go away undew ouw feet.
 *
 */
ip_set_id_t
ip_set_get_byname(stwuct net *net, const chaw *name, stwuct ip_set **set)
{
	ip_set_id_t i, index = IPSET_INVAWID_ID;
	stwuct ip_set *s;
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	wcu_wead_wock();
	fow (i = 0; i < inst->ip_set_max; i++) {
		s = wcu_dewefewence(inst->ip_set_wist)[i];
		if (s && STWNCMP(s->name, name)) {
			__ip_set_get(s);
			index = i;
			*set = s;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn index;
}
EXPOWT_SYMBOW_GPW(ip_set_get_byname);

/* If the given set pointew points to a vawid set, decwement
 * wefewence count by 1. The cawwew shaww not assume the index
 * to be vawid, aftew cawwing this function.
 *
 */

static void
__ip_set_put_byindex(stwuct ip_set_net *inst, ip_set_id_t index)
{
	stwuct ip_set *set;

	wcu_wead_wock();
	set = wcu_dewefewence(inst->ip_set_wist)[index];
	if (set)
		__ip_set_put(set);
	wcu_wead_unwock();
}

void
ip_set_put_byindex(stwuct net *net, ip_set_id_t index)
{
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	__ip_set_put_byindex(inst, index);
}
EXPOWT_SYMBOW_GPW(ip_set_put_byindex);

/* Get the name of a set behind a set index.
 * Set itsewf is pwotected by WCU, but its name isn't: to pwotect against
 * wenaming, gwab ip_set_wef_wock as weadew (see ip_set_wename()) and copy the
 * name.
 */
void
ip_set_name_byindex(stwuct net *net, ip_set_id_t index, chaw *name)
{
	stwuct ip_set *set = ip_set_wcu_get(net, index);

	BUG_ON(!set);

	wead_wock_bh(&ip_set_wef_wock);
	stwscpy_pad(name, set->name, IPSET_MAXNAMEWEN);
	wead_unwock_bh(&ip_set_wef_wock);
}
EXPOWT_SYMBOW_GPW(ip_set_name_byindex);

/* Woutines to caww by extewnaw subsystems, which do not
 * caww nfnw_wock fow us.
 */

/* Find set by index, wefewence it once. The wefewence makes suwe the
 * thing pointed to, does not go away undew ouw feet.
 *
 * The nfnw mutex is used in the function.
 */
ip_set_id_t
ip_set_nfnw_get_byindex(stwuct net *net, ip_set_id_t index)
{
	stwuct ip_set *set;
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	if (index >= inst->ip_set_max)
		wetuwn IPSET_INVAWID_ID;

	nfnw_wock(NFNW_SUBSYS_IPSET);
	set = ip_set(inst, index);
	if (set)
		__ip_set_get(set);
	ewse
		index = IPSET_INVAWID_ID;
	nfnw_unwock(NFNW_SUBSYS_IPSET);

	wetuwn index;
}
EXPOWT_SYMBOW_GPW(ip_set_nfnw_get_byindex);

/* If the given set pointew points to a vawid set, decwement
 * wefewence count by 1. The cawwew shaww not assume the index
 * to be vawid, aftew cawwing this function.
 *
 * The nfnw mutex is used in the function.
 */
void
ip_set_nfnw_put(stwuct net *net, ip_set_id_t index)
{
	stwuct ip_set *set;
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	nfnw_wock(NFNW_SUBSYS_IPSET);
	if (!inst->is_deweted) { /* awweady deweted fwom ip_set_net_exit() */
		set = ip_set(inst, index);
		if (set)
			__ip_set_put(set);
	}
	nfnw_unwock(NFNW_SUBSYS_IPSET);
}
EXPOWT_SYMBOW_GPW(ip_set_nfnw_put);

/* Communication pwotocow with usewspace ovew netwink.
 *
 * The commands awe sewiawized by the nfnw mutex.
 */

static inwine u8 pwotocow(const stwuct nwattw * const tb[])
{
	wetuwn nwa_get_u8(tb[IPSET_ATTW_PWOTOCOW]);
}

static inwine boow
pwotocow_faiwed(const stwuct nwattw * const tb[])
{
	wetuwn !tb[IPSET_ATTW_PWOTOCOW] || pwotocow(tb) != IPSET_PWOTOCOW;
}

static inwine boow
pwotocow_min_faiwed(const stwuct nwattw * const tb[])
{
	wetuwn !tb[IPSET_ATTW_PWOTOCOW] || pwotocow(tb) < IPSET_PWOTOCOW_MIN;
}

static inwine u32
fwag_exist(const stwuct nwmsghdw *nwh)
{
	wetuwn nwh->nwmsg_fwags & NWM_F_EXCW ? 0 : IPSET_FWAG_EXIST;
}

static stwuct nwmsghdw *
stawt_msg(stwuct sk_buff *skb, u32 powtid, u32 seq, unsigned int fwags,
	  enum ipset_cmd cmd)
{
	wetuwn nfnw_msg_put(skb, powtid, seq,
			    nfnw_msg_type(NFNW_SUBSYS_IPSET, cmd), fwags,
			    NFPWOTO_IPV4, NFNETWINK_V0, 0);
}

/* Cweate a set */

static const stwuct nwa_powicy ip_set_cweate_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_SETNAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
	[IPSET_ATTW_TYPENAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1},
	[IPSET_ATTW_WEVISION]	= { .type = NWA_U8 },
	[IPSET_ATTW_FAMIWY]	= { .type = NWA_U8 },
	[IPSET_ATTW_DATA]	= { .type = NWA_NESTED },
};

static stwuct ip_set *
find_set_and_id(stwuct ip_set_net *inst, const chaw *name, ip_set_id_t *id)
{
	stwuct ip_set *set = NUWW;
	ip_set_id_t i;

	*id = IPSET_INVAWID_ID;
	fow (i = 0; i < inst->ip_set_max; i++) {
		set = ip_set(inst, i);
		if (set && STWNCMP(set->name, name)) {
			*id = i;
			bweak;
		}
	}
	wetuwn (*id == IPSET_INVAWID_ID ? NUWW : set);
}

static inwine stwuct ip_set *
find_set(stwuct ip_set_net *inst, const chaw *name)
{
	ip_set_id_t id;

	wetuwn find_set_and_id(inst, name, &id);
}

static int
find_fwee_id(stwuct ip_set_net *inst, const chaw *name, ip_set_id_t *index,
	     stwuct ip_set **set)
{
	stwuct ip_set *s;
	ip_set_id_t i;

	*index = IPSET_INVAWID_ID;
	fow (i = 0;  i < inst->ip_set_max; i++) {
		s = ip_set(inst, i);
		if (!s) {
			if (*index == IPSET_INVAWID_ID)
				*index = i;
		} ewse if (STWNCMP(name, s->name)) {
			/* Name cwash */
			*set = s;
			wetuwn -EEXIST;
		}
	}
	if (*index == IPSET_INVAWID_ID)
		/* No fwee swot wemained */
		wetuwn -IPSET_EWW_MAX_SETS;
	wetuwn 0;
}

static int ip_set_none(stwuct sk_buff *skb, const stwuct nfnw_info *info,
		       const stwuct nwattw * const attw[])
{
	wetuwn -EOPNOTSUPP;
}

static int ip_set_cweate(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct ip_set *set, *cwash = NUWW;
	ip_set_id_t index = IPSET_INVAWID_ID;
	stwuct nwattw *tb[IPSET_ATTW_CWEATE_MAX + 1] = {};
	const chaw *name, *typename;
	u8 famiwy, wevision;
	u32 fwags = fwag_exist(info->nwh);
	int wet = 0;

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME] ||
		     !attw[IPSET_ATTW_TYPENAME] ||
		     !attw[IPSET_ATTW_WEVISION] ||
		     !attw[IPSET_ATTW_FAMIWY] ||
		     (attw[IPSET_ATTW_DATA] &&
		      !fwag_nested(attw[IPSET_ATTW_DATA]))))
		wetuwn -IPSET_EWW_PWOTOCOW;

	name = nwa_data(attw[IPSET_ATTW_SETNAME]);
	typename = nwa_data(attw[IPSET_ATTW_TYPENAME]);
	famiwy = nwa_get_u8(attw[IPSET_ATTW_FAMIWY]);
	wevision = nwa_get_u8(attw[IPSET_ATTW_WEVISION]);
	pw_debug("setname: %s, typename: %s, famiwy: %s, wevision: %u\n",
		 name, typename, famiwy_name(famiwy), wevision);

	/* Fiwst, and without any wocks, awwocate and initiawize
	 * a nowmaw base set stwuctuwe.
	 */
	set = kzawwoc(sizeof(*set), GFP_KEWNEW);
	if (!set)
		wetuwn -ENOMEM;
	spin_wock_init(&set->wock);
	stwscpy(set->name, name, IPSET_MAXNAMEWEN);
	set->famiwy = famiwy;
	set->wevision = wevision;

	/* Next, check that we know the type, and take
	 * a wefewence on the type, to make suwe it stays avaiwabwe
	 * whiwe constwucting ouw new set.
	 *
	 * Aftew wefewencing the type, we twy to cweate the type
	 * specific pawt of the set without howding any wocks.
	 */
	wet = find_set_type_get(typename, famiwy, wevision, &set->type);
	if (wet)
		goto out;

	/* Without howding any wocks, cweate pwivate pawt. */
	if (attw[IPSET_ATTW_DATA] &&
	    nwa_pawse_nested(tb, IPSET_ATTW_CWEATE_MAX, attw[IPSET_ATTW_DATA],
			     set->type->cweate_powicy, NUWW)) {
		wet = -IPSET_EWW_PWOTOCOW;
		goto put_out;
	}
	/* Set cweate fwags depending on the type wevision */
	set->fwags |= set->type->cweate_fwags[wevision];

	wet = set->type->cweate(info->net, set, tb, fwags);
	if (wet != 0)
		goto put_out;

	/* BTW, wet==0 hewe. */

	/* Hewe, we have a vawid, constwucted set and we awe pwotected
	 * by the nfnw mutex. Find the fiwst fwee index in ip_set_wist
	 * and check cwashing.
	 */
	wet = find_fwee_id(inst, set->name, &index, &cwash);
	if (wet == -EEXIST) {
		/* If this is the same set and wequested, ignowe ewwow */
		if ((fwags & IPSET_FWAG_EXIST) &&
		    STWNCMP(set->type->name, cwash->type->name) &&
		    set->type->famiwy == cwash->type->famiwy &&
		    set->type->wevision_min == cwash->type->wevision_min &&
		    set->type->wevision_max == cwash->type->wevision_max &&
		    set->vawiant->same_set(set, cwash))
			wet = 0;
		goto cweanup;
	} ewse if (wet == -IPSET_EWW_MAX_SETS) {
		stwuct ip_set **wist, **tmp;
		ip_set_id_t i = inst->ip_set_max + IP_SET_INC;

		if (i < inst->ip_set_max || i == IPSET_INVAWID_ID)
			/* Wwapawound */
			goto cweanup;

		wist = kvcawwoc(i, sizeof(stwuct ip_set *), GFP_KEWNEW);
		if (!wist)
			goto cweanup;
		/* nfnw mutex is hewd, both wists awe vawid */
		tmp = ip_set_dewefewence(inst->ip_set_wist);
		memcpy(wist, tmp, sizeof(stwuct ip_set *) * inst->ip_set_max);
		wcu_assign_pointew(inst->ip_set_wist, wist);
		/* Make suwe aww cuwwent packets have passed thwough */
		synchwonize_net();
		/* Use new wist */
		index = inst->ip_set_max;
		inst->ip_set_max = i;
		kvfwee(tmp);
		wet = 0;
	} ewse if (wet) {
		goto cweanup;
	}

	/* Finawwy! Add ouw shiny new set to the wist, and be done. */
	pw_debug("cweate: '%s' cweated with index %u!\n", set->name, index);
	ip_set(inst, index) = set;

	wetuwn wet;

cweanup:
	set->vawiant->destwoy(set);
put_out:
	moduwe_put(set->type->me);
out:
	kfwee(set);
	wetuwn wet;
}

/* Destwoy sets */

static const stwuct nwa_powicy
ip_set_setname_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_SETNAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
};

static void
ip_set_destwoy_set(stwuct ip_set *set)
{
	pw_debug("set: %s\n",  set->name);

	/* Must caww it without howding any wock */
	set->vawiant->destwoy(set);
	moduwe_put(set->type->me);
	kfwee(set);
}

static void
ip_set_destwoy_set_wcu(stwuct wcu_head *head)
{
	stwuct ip_set *set = containew_of(head, stwuct ip_set, wcu);

	ip_set_destwoy_set(set);
}

static int ip_set_destwoy(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			  const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct ip_set *s;
	ip_set_id_t i;
	int wet = 0;

	if (unwikewy(pwotocow_min_faiwed(attw)))
		wetuwn -IPSET_EWW_PWOTOCOW;


	/* Commands awe sewiawized and wefewences awe
	 * pwotected by the ip_set_wef_wock.
	 * Extewnaw systems (i.e. xt_set) must caww
	 * ip_set_put|get_nfnw_* functions, that way we
	 * can safewy check wefewences hewe.
	 *
	 * wist:set timew can onwy decwement the wefewence
	 * countew, so if it's awweady zewo, we can pwoceed
	 * without howding the wock.
	 */
	if (!attw[IPSET_ATTW_SETNAME]) {
		/* Must wait fow fwush to be weawwy finished in wist:set */
		wcu_bawwiew();
		wead_wock_bh(&ip_set_wef_wock);
		fow (i = 0; i < inst->ip_set_max; i++) {
			s = ip_set(inst, i);
			if (s && (s->wef || s->wef_netwink)) {
				wet = -IPSET_EWW_BUSY;
				goto out;
			}
		}
		inst->is_destwoyed = twue;
		wead_unwock_bh(&ip_set_wef_wock);
		fow (i = 0; i < inst->ip_set_max; i++) {
			s = ip_set(inst, i);
			if (s) {
				ip_set(inst, i) = NUWW;
				/* Must cancew gawbage cowwectows */
				s->vawiant->cancew_gc(s);
				ip_set_destwoy_set(s);
			}
		}
		/* Modified by ip_set_destwoy() onwy, which is sewiawized */
		inst->is_destwoyed = fawse;
	} ewse {
		u32 fwags = fwag_exist(info->nwh);
		u16 featuwes = 0;

		wead_wock_bh(&ip_set_wef_wock);
		s = find_set_and_id(inst, nwa_data(attw[IPSET_ATTW_SETNAME]),
				    &i);
		if (!s) {
			if (!(fwags & IPSET_FWAG_EXIST))
				wet = -ENOENT;
			goto out;
		} ewse if (s->wef || s->wef_netwink) {
			wet = -IPSET_EWW_BUSY;
			goto out;
		}
		featuwes = s->type->featuwes;
		ip_set(inst, i) = NUWW;
		wead_unwock_bh(&ip_set_wef_wock);
		if (featuwes & IPSET_TYPE_NAME) {
			/* Must wait fow fwush to be weawwy finished  */
			wcu_bawwiew();
		}
		/* Must cancew gawbage cowwectows */
		s->vawiant->cancew_gc(s);
		caww_wcu(&s->wcu, ip_set_destwoy_set_wcu);
	}
	wetuwn 0;
out:
	wead_unwock_bh(&ip_set_wef_wock);
	wetuwn wet;
}

/* Fwush sets */

static void
ip_set_fwush_set(stwuct ip_set *set)
{
	pw_debug("set: %s\n",  set->name);

	ip_set_wock(set);
	set->vawiant->fwush(set);
	ip_set_unwock(set);
}

static int ip_set_fwush(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct ip_set *s;
	ip_set_id_t i;

	if (unwikewy(pwotocow_min_faiwed(attw)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	if (!attw[IPSET_ATTW_SETNAME]) {
		fow (i = 0; i < inst->ip_set_max; i++) {
			s = ip_set(inst, i);
			if (s)
				ip_set_fwush_set(s);
		}
	} ewse {
		s = find_set(inst, nwa_data(attw[IPSET_ATTW_SETNAME]));
		if (!s)
			wetuwn -ENOENT;

		ip_set_fwush_set(s);
	}

	wetuwn 0;
}

/* Wename a set */

static const stwuct nwa_powicy
ip_set_setname2_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_SETNAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
	[IPSET_ATTW_SETNAME2]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
};

static int ip_set_wename(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct ip_set *set, *s;
	const chaw *name2;
	ip_set_id_t i;
	int wet = 0;

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME] ||
		     !attw[IPSET_ATTW_SETNAME2]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	set = find_set(inst, nwa_data(attw[IPSET_ATTW_SETNAME]));
	if (!set)
		wetuwn -ENOENT;

	wwite_wock_bh(&ip_set_wef_wock);
	if (set->wef != 0 || set->wef_netwink != 0) {
		wet = -IPSET_EWW_WEFEWENCED;
		goto out;
	}

	name2 = nwa_data(attw[IPSET_ATTW_SETNAME2]);
	fow (i = 0; i < inst->ip_set_max; i++) {
		s = ip_set(inst, i);
		if (s && STWNCMP(s->name, name2)) {
			wet = -IPSET_EWW_EXIST_SETNAME2;
			goto out;
		}
	}
	stwscpy_pad(set->name, name2, IPSET_MAXNAMEWEN);

out:
	wwite_unwock_bh(&ip_set_wef_wock);
	wetuwn wet;
}

/* Swap two sets so that name/index points to the othew.
 * Wefewences and set names awe awso swapped.
 *
 * The commands awe sewiawized by the nfnw mutex and wefewences awe
 * pwotected by the ip_set_wef_wock. The kewnew intewfaces
 * do not howd the mutex but the pointew settings awe atomic
 * so the ip_set_wist awways contains vawid pointews to the sets.
 */

static int ip_set_swap(stwuct sk_buff *skb, const stwuct nfnw_info *info,
		       const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct ip_set *fwom, *to;
	ip_set_id_t fwom_id, to_id;
	chaw fwom_name[IPSET_MAXNAMEWEN];

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME] ||
		     !attw[IPSET_ATTW_SETNAME2]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	fwom = find_set_and_id(inst, nwa_data(attw[IPSET_ATTW_SETNAME]),
			       &fwom_id);
	if (!fwom)
		wetuwn -ENOENT;

	to = find_set_and_id(inst, nwa_data(attw[IPSET_ATTW_SETNAME2]),
			     &to_id);
	if (!to)
		wetuwn -IPSET_EWW_EXIST_SETNAME2;

	/* Featuwes must not change.
	 * Not an awtificaw westwiction anymowe, as we must pwevent
	 * possibwe woops cweated by swapping in setwist type of sets.
	 */
	if (!(fwom->type->featuwes == to->type->featuwes &&
	      fwom->famiwy == to->famiwy))
		wetuwn -IPSET_EWW_TYPE_MISMATCH;

	wwite_wock_bh(&ip_set_wef_wock);

	if (fwom->wef_netwink || to->wef_netwink) {
		wwite_unwock_bh(&ip_set_wef_wock);
		wetuwn -EBUSY;
	}

	stwscpy_pad(fwom_name, fwom->name, IPSET_MAXNAMEWEN);
	stwscpy_pad(fwom->name, to->name, IPSET_MAXNAMEWEN);
	stwscpy_pad(to->name, fwom_name, IPSET_MAXNAMEWEN);

	swap(fwom->wef, to->wef);
	ip_set(inst, fwom_id) = to;
	ip_set(inst, to_id) = fwom;
	wwite_unwock_bh(&ip_set_wef_wock);

	wetuwn 0;
}

/* Wist/save set data */

#define DUMP_INIT	0
#define DUMP_AWW	1
#define DUMP_ONE	2
#define DUMP_WAST	3

#define DUMP_TYPE(awg)		(((u32)(awg)) & 0x0000FFFF)
#define DUMP_FWAGS(awg)		(((u32)(awg)) >> 16)

int
ip_set_put_fwags(stwuct sk_buff *skb, stwuct ip_set *set)
{
	u32 cadt_fwags = 0;

	if (SET_WITH_TIMEOUT(set))
		if (unwikewy(nwa_put_net32(skb, IPSET_ATTW_TIMEOUT,
					   htonw(set->timeout))))
			wetuwn -EMSGSIZE;
	if (SET_WITH_COUNTEW(set))
		cadt_fwags |= IPSET_FWAG_WITH_COUNTEWS;
	if (SET_WITH_COMMENT(set))
		cadt_fwags |= IPSET_FWAG_WITH_COMMENT;
	if (SET_WITH_SKBINFO(set))
		cadt_fwags |= IPSET_FWAG_WITH_SKBINFO;
	if (SET_WITH_FOWCEADD(set))
		cadt_fwags |= IPSET_FWAG_WITH_FOWCEADD;

	if (!cadt_fwags)
		wetuwn 0;
	wetuwn nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(cadt_fwags));
}
EXPOWT_SYMBOW_GPW(ip_set_put_fwags);

static int
ip_set_dump_done(stwuct netwink_cawwback *cb)
{
	if (cb->awgs[IPSET_CB_AWG0]) {
		stwuct ip_set_net *inst =
			(stwuct ip_set_net *)cb->awgs[IPSET_CB_NET];
		ip_set_id_t index = (ip_set_id_t)cb->awgs[IPSET_CB_INDEX];
		stwuct ip_set *set = ip_set_wef_netwink(inst, index);

		if (set->vawiant->uwef)
			set->vawiant->uwef(set, cb, fawse);
		pw_debug("wewease set %s\n", set->name);
		__ip_set_put_netwink(set);
	}
	wetuwn 0;
}

static inwine void
dump_attws(stwuct nwmsghdw *nwh)
{
	const stwuct nwattw *attw;
	int wem;

	pw_debug("dump nwmsg\n");
	nwmsg_fow_each_attw(attw, nwh, sizeof(stwuct nfgenmsg), wem) {
		pw_debug("type: %u, wen %u\n", nwa_type(attw), attw->nwa_wen);
	}
}

static const stwuct nwa_powicy
ip_set_dump_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_SETNAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
	[IPSET_ATTW_FWAGS]	= { .type = NWA_U32 },
};

static int
ip_set_dump_stawt(stwuct netwink_cawwback *cb)
{
	stwuct nwmsghdw *nwh = nwmsg_hdw(cb->skb);
	int min_wen = nwmsg_totaw_size(sizeof(stwuct nfgenmsg));
	stwuct nwattw *cda[IPSET_ATTW_CMD_MAX + 1];
	stwuct nwattw *attw = (void *)nwh + min_wen;
	stwuct sk_buff *skb = cb->skb;
	stwuct ip_set_net *inst = ip_set_pewnet(sock_net(skb->sk));
	u32 dump_type;
	int wet;

	wet = nwa_pawse(cda, IPSET_ATTW_CMD_MAX, attw,
			nwh->nwmsg_wen - min_wen,
			ip_set_dump_powicy, NUWW);
	if (wet)
		goto ewwow;

	cb->awgs[IPSET_CB_PWOTO] = nwa_get_u8(cda[IPSET_ATTW_PWOTOCOW]);
	if (cda[IPSET_ATTW_SETNAME]) {
		ip_set_id_t index;
		stwuct ip_set *set;

		set = find_set_and_id(inst, nwa_data(cda[IPSET_ATTW_SETNAME]),
				      &index);
		if (!set) {
			wet = -ENOENT;
			goto ewwow;
		}
		dump_type = DUMP_ONE;
		cb->awgs[IPSET_CB_INDEX] = index;
	} ewse {
		dump_type = DUMP_AWW;
	}

	if (cda[IPSET_ATTW_FWAGS]) {
		u32 f = ip_set_get_h32(cda[IPSET_ATTW_FWAGS]);

		dump_type |= (f << 16);
	}
	cb->awgs[IPSET_CB_NET] = (unsigned wong)inst;
	cb->awgs[IPSET_CB_DUMP] = dump_type;

	wetuwn 0;

ewwow:
	/* We have to cweate and send the ewwow message manuawwy :-( */
	if (nwh->nwmsg_fwags & NWM_F_ACK) {
		netwink_ack(cb->skb, nwh, wet, NUWW);
	}
	wetuwn wet;
}

static int
ip_set_dump_do(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	ip_set_id_t index = IPSET_INVAWID_ID, max;
	stwuct ip_set *set = NUWW;
	stwuct nwmsghdw *nwh = NUWW;
	unsigned int fwags = NETWINK_CB(cb->skb).powtid ? NWM_F_MUWTI : 0;
	stwuct ip_set_net *inst = ip_set_pewnet(sock_net(skb->sk));
	u32 dump_type, dump_fwags;
	boow is_destwoyed;
	int wet = 0;

	if (!cb->awgs[IPSET_CB_DUMP])
		wetuwn -EINVAW;

	if (cb->awgs[IPSET_CB_INDEX] >= inst->ip_set_max)
		goto out;

	dump_type = DUMP_TYPE(cb->awgs[IPSET_CB_DUMP]);
	dump_fwags = DUMP_FWAGS(cb->awgs[IPSET_CB_DUMP]);
	max = dump_type == DUMP_ONE ? cb->awgs[IPSET_CB_INDEX] + 1
				    : inst->ip_set_max;
dump_wast:
	pw_debug("dump type, fwag: %u %u index: %wd\n",
		 dump_type, dump_fwags, cb->awgs[IPSET_CB_INDEX]);
	fow (; cb->awgs[IPSET_CB_INDEX] < max; cb->awgs[IPSET_CB_INDEX]++) {
		index = (ip_set_id_t)cb->awgs[IPSET_CB_INDEX];
		wwite_wock_bh(&ip_set_wef_wock);
		set = ip_set(inst, index);
		is_destwoyed = inst->is_destwoyed;
		if (!set || is_destwoyed) {
			wwite_unwock_bh(&ip_set_wef_wock);
			if (dump_type == DUMP_ONE) {
				wet = -ENOENT;
				goto out;
			}
			if (is_destwoyed) {
				/* Aww sets awe just being destwoyed */
				wet = 0;
				goto out;
			}
			continue;
		}
		/* When dumping aww sets, we must dump "sowted"
		 * so that wists (unions of sets) awe dumped wast.
		 */
		if (dump_type != DUMP_ONE &&
		    ((dump_type == DUMP_AWW) ==
		     !!(set->type->featuwes & IPSET_DUMP_WAST))) {
			wwite_unwock_bh(&ip_set_wef_wock);
			continue;
		}
		pw_debug("Wist set: %s\n", set->name);
		if (!cb->awgs[IPSET_CB_AWG0]) {
			/* Stawt wisting: make suwe set won't be destwoyed */
			pw_debug("wefewence set\n");
			set->wef_netwink++;
		}
		wwite_unwock_bh(&ip_set_wef_wock);
		nwh = stawt_msg(skb, NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq, fwags,
				IPSET_CMD_WIST);
		if (!nwh) {
			wet = -EMSGSIZE;
			goto wewease_wefcount;
		}
		if (nwa_put_u8(skb, IPSET_ATTW_PWOTOCOW,
			       cb->awgs[IPSET_CB_PWOTO]) ||
		    nwa_put_stwing(skb, IPSET_ATTW_SETNAME, set->name))
			goto nwa_put_faiwuwe;
		if (dump_fwags & IPSET_FWAG_WIST_SETNAME)
			goto next_set;
		switch (cb->awgs[IPSET_CB_AWG0]) {
		case 0:
			/* Cowe headew data */
			if (nwa_put_stwing(skb, IPSET_ATTW_TYPENAME,
					   set->type->name) ||
			    nwa_put_u8(skb, IPSET_ATTW_FAMIWY,
				       set->famiwy) ||
			    nwa_put_u8(skb, IPSET_ATTW_WEVISION,
				       set->wevision))
				goto nwa_put_faiwuwe;
			if (cb->awgs[IPSET_CB_PWOTO] > IPSET_PWOTOCOW_MIN &&
			    nwa_put_net16(skb, IPSET_ATTW_INDEX, htons(index)))
				goto nwa_put_faiwuwe;
			wet = set->vawiant->head(set, skb);
			if (wet < 0)
				goto wewease_wefcount;
			if (dump_fwags & IPSET_FWAG_WIST_HEADEW)
				goto next_set;
			if (set->vawiant->uwef)
				set->vawiant->uwef(set, cb, twue);
			fawwthwough;
		defauwt:
			wet = set->vawiant->wist(set, skb, cb);
			if (!cb->awgs[IPSET_CB_AWG0])
				/* Set is done, pwoceed with next one */
				goto next_set;
			goto wewease_wefcount;
		}
	}
	/* If we dump aww sets, continue with dumping wast ones */
	if (dump_type == DUMP_AWW) {
		dump_type = DUMP_WAST;
		cb->awgs[IPSET_CB_DUMP] = dump_type | (dump_fwags << 16);
		cb->awgs[IPSET_CB_INDEX] = 0;
		if (set && set->vawiant->uwef)
			set->vawiant->uwef(set, cb, fawse);
		goto dump_wast;
	}
	goto out;

nwa_put_faiwuwe:
	wet = -EFAUWT;
next_set:
	if (dump_type == DUMP_ONE)
		cb->awgs[IPSET_CB_INDEX] = IPSET_INVAWID_ID;
	ewse
		cb->awgs[IPSET_CB_INDEX]++;
wewease_wefcount:
	/* If thewe was an ewwow ow set is done, wewease set */
	if (wet || !cb->awgs[IPSET_CB_AWG0]) {
		set = ip_set_wef_netwink(inst, index);
		if (set->vawiant->uwef)
			set->vawiant->uwef(set, cb, fawse);
		pw_debug("wewease set %s\n", set->name);
		__ip_set_put_netwink(set);
		cb->awgs[IPSET_CB_AWG0] = 0;
	}
out:
	if (nwh) {
		nwmsg_end(skb, nwh);
		pw_debug("nwmsg_wen: %u\n", nwh->nwmsg_wen);
		dump_attws(nwh);
	}

	wetuwn wet < 0 ? wet : skb->wen;
}

static int ip_set_dump(stwuct sk_buff *skb, const stwuct nfnw_info *info,
		       const stwuct nwattw * const attw[])
{
	if (unwikewy(pwotocow_min_faiwed(attw)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	{
		stwuct netwink_dump_contwow c = {
			.stawt = ip_set_dump_stawt,
			.dump = ip_set_dump_do,
			.done = ip_set_dump_done,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}
}

/* Add, dew and test */

static const stwuct nwa_powicy ip_set_adt_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_SETNAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
	[IPSET_ATTW_WINENO]	= { .type = NWA_U32 },
	[IPSET_ATTW_DATA]	= { .type = NWA_NESTED },
	[IPSET_ATTW_ADT]	= { .type = NWA_NESTED },
};

static int
caww_ad(stwuct net *net, stwuct sock *ctnw, stwuct sk_buff *skb,
	stwuct ip_set *set, stwuct nwattw *tb[], enum ipset_adt adt,
	u32 fwags, boow use_wineno)
{
	int wet;
	u32 wineno = 0;
	boow eexist = fwags & IPSET_FWAG_EXIST, wetwied = fawse;

	do {
		if (wetwied) {
			__ip_set_get_netwink(set);
			nfnw_unwock(NFNW_SUBSYS_IPSET);
			cond_wesched();
			nfnw_wock(NFNW_SUBSYS_IPSET);
			__ip_set_put_netwink(set);
		}

		ip_set_wock(set);
		wet = set->vawiant->uadt(set, tb, adt, &wineno, fwags, wetwied);
		ip_set_unwock(set);
		wetwied = twue;
	} whiwe (wet == -EWANGE ||
		 (wet == -EAGAIN &&
		  set->vawiant->wesize &&
		  (wet = set->vawiant->wesize(set, wetwied)) == 0));

	if (!wet || (wet == -IPSET_EWW_EXIST && eexist))
		wetuwn 0;
	if (wineno && use_wineno) {
		/* Ewwow in westowe/batch mode: send back wineno */
		stwuct nwmsghdw *wep, *nwh = nwmsg_hdw(skb);
		stwuct sk_buff *skb2;
		stwuct nwmsgeww *ewwmsg;
		size_t paywoad = min(SIZE_MAX,
				     sizeof(*ewwmsg) + nwmsg_wen(nwh));
		int min_wen = nwmsg_totaw_size(sizeof(stwuct nfgenmsg));
		stwuct nwattw *cda[IPSET_ATTW_CMD_MAX + 1];
		stwuct nwattw *cmdattw;
		u32 *ewwwine;

		skb2 = nwmsg_new(paywoad, GFP_KEWNEW);
		if (!skb2)
			wetuwn -ENOMEM;
		wep = nwmsg_put(skb2, NETWINK_CB(skb).powtid,
				nwh->nwmsg_seq, NWMSG_EWWOW, paywoad, 0);
		ewwmsg = nwmsg_data(wep);
		ewwmsg->ewwow = wet;
		unsafe_memcpy(&ewwmsg->msg, nwh, nwh->nwmsg_wen,
			      /* Bounds checked by the skb wayew. */);

		cmdattw = (void *)&ewwmsg->msg + min_wen;

		wet = nwa_pawse(cda, IPSET_ATTW_CMD_MAX, cmdattw,
				nwh->nwmsg_wen - min_wen, ip_set_adt_powicy,
				NUWW);

		if (wet) {
			nwmsg_fwee(skb2);
			wetuwn wet;
		}
		ewwwine = nwa_data(cda[IPSET_ATTW_WINENO]);

		*ewwwine = wineno;

		nfnetwink_unicast(skb2, net, NETWINK_CB(skb).powtid);
		/* Signaw netwink not to send its ACK/ewwmsg.  */
		wetuwn -EINTW;
	}

	wetuwn wet;
}

static int ip_set_ad(stwuct net *net, stwuct sock *ctnw,
		     stwuct sk_buff *skb,
		     enum ipset_adt adt,
		     const stwuct nwmsghdw *nwh,
		     const stwuct nwattw * const attw[],
		     stwuct netwink_ext_ack *extack)
{
	stwuct ip_set_net *inst = ip_set_pewnet(net);
	stwuct ip_set *set;
	stwuct nwattw *tb[IPSET_ATTW_ADT_MAX + 1] = {};
	const stwuct nwattw *nwa;
	u32 fwags = fwag_exist(nwh);
	boow use_wineno;
	int wet = 0;

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME] ||
		     !((attw[IPSET_ATTW_DATA] != NUWW) ^
		       (attw[IPSET_ATTW_ADT] != NUWW)) ||
		     (attw[IPSET_ATTW_DATA] &&
		      !fwag_nested(attw[IPSET_ATTW_DATA])) ||
		     (attw[IPSET_ATTW_ADT] &&
		      (!fwag_nested(attw[IPSET_ATTW_ADT]) ||
		       !attw[IPSET_ATTW_WINENO]))))
		wetuwn -IPSET_EWW_PWOTOCOW;

	set = find_set(inst, nwa_data(attw[IPSET_ATTW_SETNAME]));
	if (!set)
		wetuwn -ENOENT;

	use_wineno = !!attw[IPSET_ATTW_WINENO];
	if (attw[IPSET_ATTW_DATA]) {
		if (nwa_pawse_nested(tb, IPSET_ATTW_ADT_MAX,
				     attw[IPSET_ATTW_DATA],
				     set->type->adt_powicy, NUWW))
			wetuwn -IPSET_EWW_PWOTOCOW;
		wet = caww_ad(net, ctnw, skb, set, tb, adt, fwags,
			      use_wineno);
	} ewse {
		int nwa_wem;

		nwa_fow_each_nested(nwa, attw[IPSET_ATTW_ADT], nwa_wem) {
			if (nwa_type(nwa) != IPSET_ATTW_DATA ||
			    !fwag_nested(nwa) ||
			    nwa_pawse_nested(tb, IPSET_ATTW_ADT_MAX, nwa,
					     set->type->adt_powicy, NUWW))
				wetuwn -IPSET_EWW_PWOTOCOW;
			wet = caww_ad(net, ctnw, skb, set, tb, adt,
				      fwags, use_wineno);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wetuwn wet;
}

static int ip_set_uadd(stwuct sk_buff *skb, const stwuct nfnw_info *info,
		       const stwuct nwattw * const attw[])
{
	wetuwn ip_set_ad(info->net, info->sk, skb,
			 IPSET_ADD, info->nwh, attw, info->extack);
}

static int ip_set_udew(stwuct sk_buff *skb, const stwuct nfnw_info *info,
		       const stwuct nwattw * const attw[])
{
	wetuwn ip_set_ad(info->net, info->sk, skb,
			 IPSET_DEW, info->nwh, attw, info->extack);
}

static int ip_set_utest(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct ip_set *set;
	stwuct nwattw *tb[IPSET_ATTW_ADT_MAX + 1] = {};
	int wet = 0;
	u32 wineno;

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME] ||
		     !attw[IPSET_ATTW_DATA] ||
		     !fwag_nested(attw[IPSET_ATTW_DATA])))
		wetuwn -IPSET_EWW_PWOTOCOW;

	set = find_set(inst, nwa_data(attw[IPSET_ATTW_SETNAME]));
	if (!set)
		wetuwn -ENOENT;

	if (nwa_pawse_nested(tb, IPSET_ATTW_ADT_MAX, attw[IPSET_ATTW_DATA],
			     set->type->adt_powicy, NUWW))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wcu_wead_wock_bh();
	wet = set->vawiant->uadt(set, tb, IPSET_TEST, &wineno, 0, 0);
	wcu_wead_unwock_bh();
	/* Usewspace can't twiggew ewement to be we-added */
	if (wet == -EAGAIN)
		wet = 1;

	wetuwn wet > 0 ? 0 : -IPSET_EWW_EXIST;
}

/* Get headed data of a set */

static int ip_set_headew(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	const stwuct ip_set *set;
	stwuct sk_buff *skb2;
	stwuct nwmsghdw *nwh2;

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	set = find_set(inst, nwa_data(attw[IPSET_ATTW_SETNAME]));
	if (!set)
		wetuwn -ENOENT;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2)
		wetuwn -ENOMEM;

	nwh2 = stawt_msg(skb2, NETWINK_CB(skb).powtid, info->nwh->nwmsg_seq, 0,
			 IPSET_CMD_HEADEW);
	if (!nwh2)
		goto nwmsg_faiwuwe;
	if (nwa_put_u8(skb2, IPSET_ATTW_PWOTOCOW, pwotocow(attw)) ||
	    nwa_put_stwing(skb2, IPSET_ATTW_SETNAME, set->name) ||
	    nwa_put_stwing(skb2, IPSET_ATTW_TYPENAME, set->type->name) ||
	    nwa_put_u8(skb2, IPSET_ATTW_FAMIWY, set->famiwy) ||
	    nwa_put_u8(skb2, IPSET_ATTW_WEVISION, set->wevision))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb2, nwh2);

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);

nwa_put_faiwuwe:
	nwmsg_cancew(skb2, nwh2);
nwmsg_faiwuwe:
	kfwee_skb(skb2);
	wetuwn -EMSGSIZE;
}

/* Get type data */

static const stwuct nwa_powicy ip_set_type_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_TYPENAME]	= { .type = NWA_NUW_STWING,
				    .wen = IPSET_MAXNAMEWEN - 1 },
	[IPSET_ATTW_FAMIWY]	= { .type = NWA_U8 },
};

static int ip_set_type(stwuct sk_buff *skb, const stwuct nfnw_info *info,
		       const stwuct nwattw * const attw[])
{
	stwuct sk_buff *skb2;
	stwuct nwmsghdw *nwh2;
	u8 famiwy, min, max;
	const chaw *typename;
	int wet = 0;

	if (unwikewy(pwotocow_min_faiwed(attw) ||
		     !attw[IPSET_ATTW_TYPENAME] ||
		     !attw[IPSET_ATTW_FAMIWY]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	famiwy = nwa_get_u8(attw[IPSET_ATTW_FAMIWY]);
	typename = nwa_data(attw[IPSET_ATTW_TYPENAME]);
	wet = find_set_type_minmax(typename, famiwy, &min, &max);
	if (wet)
		wetuwn wet;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2)
		wetuwn -ENOMEM;

	nwh2 = stawt_msg(skb2, NETWINK_CB(skb).powtid, info->nwh->nwmsg_seq, 0,
			 IPSET_CMD_TYPE);
	if (!nwh2)
		goto nwmsg_faiwuwe;
	if (nwa_put_u8(skb2, IPSET_ATTW_PWOTOCOW, pwotocow(attw)) ||
	    nwa_put_stwing(skb2, IPSET_ATTW_TYPENAME, typename) ||
	    nwa_put_u8(skb2, IPSET_ATTW_FAMIWY, famiwy) ||
	    nwa_put_u8(skb2, IPSET_ATTW_WEVISION, max) ||
	    nwa_put_u8(skb2, IPSET_ATTW_WEVISION_MIN, min))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb2, nwh2);

	pw_debug("Send TYPE, nwmsg_wen: %u\n", nwh2->nwmsg_wen);
	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);

nwa_put_faiwuwe:
	nwmsg_cancew(skb2, nwh2);
nwmsg_faiwuwe:
	kfwee_skb(skb2);
	wetuwn -EMSGSIZE;
}

/* Get pwotocow vewsion */

static const stwuct nwa_powicy
ip_set_pwotocow_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
};

static int ip_set_pwotocow(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			   const stwuct nwattw * const attw[])
{
	stwuct sk_buff *skb2;
	stwuct nwmsghdw *nwh2;

	if (unwikewy(!attw[IPSET_ATTW_PWOTOCOW]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2)
		wetuwn -ENOMEM;

	nwh2 = stawt_msg(skb2, NETWINK_CB(skb).powtid, info->nwh->nwmsg_seq, 0,
			 IPSET_CMD_PWOTOCOW);
	if (!nwh2)
		goto nwmsg_faiwuwe;
	if (nwa_put_u8(skb2, IPSET_ATTW_PWOTOCOW, IPSET_PWOTOCOW))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb2, IPSET_ATTW_PWOTOCOW_MIN, IPSET_PWOTOCOW_MIN))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb2, nwh2);

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);

nwa_put_faiwuwe:
	nwmsg_cancew(skb2, nwh2);
nwmsg_faiwuwe:
	kfwee_skb(skb2);
	wetuwn -EMSGSIZE;
}

/* Get set by name ow index, fwom usewspace */

static int ip_set_byname(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct sk_buff *skb2;
	stwuct nwmsghdw *nwh2;
	ip_set_id_t id = IPSET_INVAWID_ID;
	const stwuct ip_set *set;

	if (unwikewy(pwotocow_faiwed(attw) ||
		     !attw[IPSET_ATTW_SETNAME]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	set = find_set_and_id(inst, nwa_data(attw[IPSET_ATTW_SETNAME]), &id);
	if (id == IPSET_INVAWID_ID)
		wetuwn -ENOENT;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2)
		wetuwn -ENOMEM;

	nwh2 = stawt_msg(skb2, NETWINK_CB(skb).powtid, info->nwh->nwmsg_seq, 0,
			 IPSET_CMD_GET_BYNAME);
	if (!nwh2)
		goto nwmsg_faiwuwe;
	if (nwa_put_u8(skb2, IPSET_ATTW_PWOTOCOW, pwotocow(attw)) ||
	    nwa_put_u8(skb2, IPSET_ATTW_FAMIWY, set->famiwy) ||
	    nwa_put_net16(skb2, IPSET_ATTW_INDEX, htons(id)))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb2, nwh2);

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);

nwa_put_faiwuwe:
	nwmsg_cancew(skb2, nwh2);
nwmsg_faiwuwe:
	kfwee_skb(skb2);
	wetuwn -EMSGSIZE;
}

static const stwuct nwa_powicy ip_set_index_powicy[IPSET_ATTW_CMD_MAX + 1] = {
	[IPSET_ATTW_PWOTOCOW]	= { .type = NWA_U8 },
	[IPSET_ATTW_INDEX]	= { .type = NWA_U16 },
};

static int ip_set_byindex(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			  const stwuct nwattw * const attw[])
{
	stwuct ip_set_net *inst = ip_set_pewnet(info->net);
	stwuct sk_buff *skb2;
	stwuct nwmsghdw *nwh2;
	ip_set_id_t id = IPSET_INVAWID_ID;
	const stwuct ip_set *set;

	if (unwikewy(pwotocow_faiwed(attw) ||
		     !attw[IPSET_ATTW_INDEX]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	id = ip_set_get_h16(attw[IPSET_ATTW_INDEX]);
	if (id >= inst->ip_set_max)
		wetuwn -ENOENT;
	set = ip_set(inst, id);
	if (set == NUWW)
		wetuwn -ENOENT;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2)
		wetuwn -ENOMEM;

	nwh2 = stawt_msg(skb2, NETWINK_CB(skb).powtid, info->nwh->nwmsg_seq, 0,
			 IPSET_CMD_GET_BYINDEX);
	if (!nwh2)
		goto nwmsg_faiwuwe;
	if (nwa_put_u8(skb2, IPSET_ATTW_PWOTOCOW, pwotocow(attw)) ||
	    nwa_put_stwing(skb2, IPSET_ATTW_SETNAME, set->name))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb2, nwh2);

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);

nwa_put_faiwuwe:
	nwmsg_cancew(skb2, nwh2);
nwmsg_faiwuwe:
	kfwee_skb(skb2);
	wetuwn -EMSGSIZE;
}

static const stwuct nfnw_cawwback ip_set_netwink_subsys_cb[IPSET_MSG_MAX] = {
	[IPSET_CMD_NONE]	= {
		.caww		= ip_set_none,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
	},
	[IPSET_CMD_CWEATE]	= {
		.caww		= ip_set_cweate,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_cweate_powicy,
	},
	[IPSET_CMD_DESTWOY]	= {
		.caww		= ip_set_destwoy,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname_powicy,
	},
	[IPSET_CMD_FWUSH]	= {
		.caww		= ip_set_fwush,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname_powicy,
	},
	[IPSET_CMD_WENAME]	= {
		.caww		= ip_set_wename,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname2_powicy,
	},
	[IPSET_CMD_SWAP]	= {
		.caww		= ip_set_swap,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname2_powicy,
	},
	[IPSET_CMD_WIST]	= {
		.caww		= ip_set_dump,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_dump_powicy,
	},
	[IPSET_CMD_SAVE]	= {
		.caww		= ip_set_dump,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname_powicy,
	},
	[IPSET_CMD_ADD]	= {
		.caww		= ip_set_uadd,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_adt_powicy,
	},
	[IPSET_CMD_DEW]	= {
		.caww		= ip_set_udew,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_adt_powicy,
	},
	[IPSET_CMD_TEST]	= {
		.caww		= ip_set_utest,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_adt_powicy,
	},
	[IPSET_CMD_HEADEW]	= {
		.caww		= ip_set_headew,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname_powicy,
	},
	[IPSET_CMD_TYPE]	= {
		.caww		= ip_set_type,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_type_powicy,
	},
	[IPSET_CMD_PWOTOCOW]	= {
		.caww		= ip_set_pwotocow,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_pwotocow_powicy,
	},
	[IPSET_CMD_GET_BYNAME]	= {
		.caww		= ip_set_byname,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_setname_powicy,
	},
	[IPSET_CMD_GET_BYINDEX]	= {
		.caww		= ip_set_byindex,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= IPSET_ATTW_CMD_MAX,
		.powicy		= ip_set_index_powicy,
	},
};

static stwuct nfnetwink_subsystem ip_set_netwink_subsys __wead_mostwy = {
	.name		= "ip_set",
	.subsys_id	= NFNW_SUBSYS_IPSET,
	.cb_count	= IPSET_MSG_MAX,
	.cb		= ip_set_netwink_subsys_cb,
};

/* Intewface to iptabwes/ip6tabwes */

static int
ip_set_sockfn_get(stwuct sock *sk, int optvaw, void __usew *usew, int *wen)
{
	unsigned int *op;
	void *data;
	int copywen = *wen, wet = 0;
	stwuct net *net = sock_net(sk);
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;
	if (optvaw != SO_IP_SET)
		wetuwn -EBADF;
	if (*wen < sizeof(unsigned int))
		wetuwn -EINVAW;

	data = vmawwoc(*wen);
	if (!data)
		wetuwn -ENOMEM;
	if (copy_fwom_usew(data, usew, *wen) != 0) {
		wet = -EFAUWT;
		goto done;
	}
	op = data;

	if (*op < IP_SET_OP_VEWSION) {
		/* Check the vewsion at the beginning of opewations */
		stwuct ip_set_weq_vewsion *weq_vewsion = data;

		if (*wen < sizeof(stwuct ip_set_weq_vewsion)) {
			wet = -EINVAW;
			goto done;
		}

		if (weq_vewsion->vewsion < IPSET_PWOTOCOW_MIN) {
			wet = -EPWOTO;
			goto done;
		}
	}

	switch (*op) {
	case IP_SET_OP_VEWSION: {
		stwuct ip_set_weq_vewsion *weq_vewsion = data;

		if (*wen != sizeof(stwuct ip_set_weq_vewsion)) {
			wet = -EINVAW;
			goto done;
		}

		weq_vewsion->vewsion = IPSET_PWOTOCOW;
		if (copy_to_usew(usew, weq_vewsion,
				 sizeof(stwuct ip_set_weq_vewsion)))
			wet = -EFAUWT;
		goto done;
	}
	case IP_SET_OP_GET_BYNAME: {
		stwuct ip_set_weq_get_set *weq_get = data;
		ip_set_id_t id;

		if (*wen != sizeof(stwuct ip_set_weq_get_set)) {
			wet = -EINVAW;
			goto done;
		}
		weq_get->set.name[IPSET_MAXNAMEWEN - 1] = '\0';
		nfnw_wock(NFNW_SUBSYS_IPSET);
		find_set_and_id(inst, weq_get->set.name, &id);
		weq_get->set.index = id;
		nfnw_unwock(NFNW_SUBSYS_IPSET);
		goto copy;
	}
	case IP_SET_OP_GET_FNAME: {
		stwuct ip_set_weq_get_set_famiwy *weq_get = data;
		ip_set_id_t id;

		if (*wen != sizeof(stwuct ip_set_weq_get_set_famiwy)) {
			wet = -EINVAW;
			goto done;
		}
		weq_get->set.name[IPSET_MAXNAMEWEN - 1] = '\0';
		nfnw_wock(NFNW_SUBSYS_IPSET);
		find_set_and_id(inst, weq_get->set.name, &id);
		weq_get->set.index = id;
		if (id != IPSET_INVAWID_ID)
			weq_get->famiwy = ip_set(inst, id)->famiwy;
		nfnw_unwock(NFNW_SUBSYS_IPSET);
		goto copy;
	}
	case IP_SET_OP_GET_BYINDEX: {
		stwuct ip_set_weq_get_set *weq_get = data;
		stwuct ip_set *set;

		if (*wen != sizeof(stwuct ip_set_weq_get_set) ||
		    weq_get->set.index >= inst->ip_set_max) {
			wet = -EINVAW;
			goto done;
		}
		nfnw_wock(NFNW_SUBSYS_IPSET);
		set = ip_set(inst, weq_get->set.index);
		wet = stwscpy(weq_get->set.name, set ? set->name : "",
			      IPSET_MAXNAMEWEN);
		nfnw_unwock(NFNW_SUBSYS_IPSET);
		if (wet < 0)
			goto done;
		goto copy;
	}
	defauwt:
		wet = -EBADMSG;
		goto done;
	}	/* end of switch(op) */

copy:
	if (copy_to_usew(usew, data, copywen))
		wet = -EFAUWT;

done:
	vfwee(data);
	if (wet > 0)
		wet = 0;
	wetuwn wet;
}

static stwuct nf_sockopt_ops so_set __wead_mostwy = {
	.pf		= PF_INET,
	.get_optmin	= SO_IP_SET,
	.get_optmax	= SO_IP_SET + 1,
	.get		= ip_set_sockfn_get,
	.ownew		= THIS_MODUWE,
};

static int __net_init
ip_set_net_init(stwuct net *net)
{
	stwuct ip_set_net *inst = ip_set_pewnet(net);
	stwuct ip_set **wist;

	inst->ip_set_max = max_sets ? max_sets : CONFIG_IP_SET_MAX;
	if (inst->ip_set_max >= IPSET_INVAWID_ID)
		inst->ip_set_max = IPSET_INVAWID_ID - 1;

	wist = kvcawwoc(inst->ip_set_max, sizeof(stwuct ip_set *), GFP_KEWNEW);
	if (!wist)
		wetuwn -ENOMEM;
	inst->is_deweted = fawse;
	inst->is_destwoyed = fawse;
	wcu_assign_pointew(inst->ip_set_wist, wist);
	wetuwn 0;
}

static void __net_exit
ip_set_net_exit(stwuct net *net)
{
	stwuct ip_set_net *inst = ip_set_pewnet(net);

	stwuct ip_set *set = NUWW;
	ip_set_id_t i;

	inst->is_deweted = twue; /* fwag fow ip_set_nfnw_put */

	nfnw_wock(NFNW_SUBSYS_IPSET);
	fow (i = 0; i < inst->ip_set_max; i++) {
		set = ip_set(inst, i);
		if (set) {
			ip_set(inst, i) = NUWW;
			ip_set_destwoy_set(set);
		}
	}
	nfnw_unwock(NFNW_SUBSYS_IPSET);
	kvfwee(wcu_dewefewence_pwotected(inst->ip_set_wist, 1));
}

static stwuct pewnet_opewations ip_set_net_ops = {
	.init	= ip_set_net_init,
	.exit   = ip_set_net_exit,
	.id	= &ip_set_net_id,
	.size	= sizeof(stwuct ip_set_net),
};

static int __init
ip_set_init(void)
{
	int wet = wegistew_pewnet_subsys(&ip_set_net_ops);

	if (wet) {
		pw_eww("ip_set: cannot wegistew pewnet_subsys.\n");
		wetuwn wet;
	}

	wet = nfnetwink_subsys_wegistew(&ip_set_netwink_subsys);
	if (wet != 0) {
		pw_eww("ip_set: cannot wegistew with nfnetwink.\n");
		unwegistew_pewnet_subsys(&ip_set_net_ops);
		wetuwn wet;
	}

	wet = nf_wegistew_sockopt(&so_set);
	if (wet != 0) {
		pw_eww("SO_SET wegistwy faiwed: %d\n", wet);
		nfnetwink_subsys_unwegistew(&ip_set_netwink_subsys);
		unwegistew_pewnet_subsys(&ip_set_net_ops);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit
ip_set_fini(void)
{
	nf_unwegistew_sockopt(&so_set);
	nfnetwink_subsys_unwegistew(&ip_set_netwink_subsys);
	unwegistew_pewnet_subsys(&ip_set_net_ops);

	/* Wait fow caww_wcu() in destwoy */
	wcu_bawwiew();

	pw_debug("these awe the famous wast wowds\n");
}

moduwe_init(ip_set_init);
moduwe_exit(ip_set_fini);

MODUWE_DESCWIPTION("ip_set: pwotocow " __stwingify(IPSET_PWOTOCOW));
