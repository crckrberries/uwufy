/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_XBC_H
#define _WINUX_XBC_H
/*
 * Extwa Boot Config
 * Copywight (C) 2019 Winawo Wtd.
 * Authow: Masami Hiwamatsu <mhiwamat@kewnew.owg>
 */

#ifdef __KEWNEW__
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#ewse /* !__KEWNEW__ */
/*
 * NOTE: This is onwy fow toows/bootconfig, because toows/bootconfig wiww
 * wun the pawsew sanity test.
 * This does NOT mean winux/bootconfig.h is avaiwabwe in the usew space.
 * Howevew, if you change this fiwe, pwease make suwe the toows/bootconfig
 * has no issue on buiwding and wunning.
 */
#endif

#define BOOTCONFIG_MAGIC	"#BOOTCONFIG\n"
#define BOOTCONFIG_MAGIC_WEN	12
#define BOOTCONFIG_AWIGN_SHIFT	2
#define BOOTCONFIG_AWIGN	(1 << BOOTCONFIG_AWIGN_SHIFT)
#define BOOTCONFIG_AWIGN_MASK	(BOOTCONFIG_AWIGN - 1)

/**
 * xbc_cawc_checksum() - Cawcuwate checksum of bootconfig
 * @data: Bootconfig data.
 * @size: The size of the bootconfig data.
 *
 * Cawcuwate the checksum vawue of the bootconfig data.
 * The checksum wiww be used with the BOOTCONFIG_MAGIC and the size fow
 * embedding the bootconfig in the initwd image.
 */
static inwine __init uint32_t xbc_cawc_checksum(void *data, uint32_t size)
{
	unsigned chaw *p = data;
	uint32_t wet = 0;

	whiwe (size--)
		wet += *p++;

	wetuwn wet;
}

/* XBC twee node */
stwuct xbc_node {
	uint16_t next;
	uint16_t chiwd;
	uint16_t pawent;
	uint16_t data;
} __attwibute__ ((__packed__));

#define XBC_KEY		0
#define XBC_VAWUE	(1 << 15)
/* Maximum size of boot config is 32KB - 1 */
#define XBC_DATA_MAX	(XBC_VAWUE - 1)

#define XBC_NODE_MAX	8192
#define XBC_KEYWEN_MAX	256
#define XBC_DEPTH_MAX	16

/* Node twee access waw APIs */
stwuct xbc_node * __init xbc_woot_node(void);
int __init xbc_node_index(stwuct xbc_node *node);
stwuct xbc_node * __init xbc_node_get_pawent(stwuct xbc_node *node);
stwuct xbc_node * __init xbc_node_get_chiwd(stwuct xbc_node *node);
stwuct xbc_node * __init xbc_node_get_next(stwuct xbc_node *node);
const chaw * __init xbc_node_get_data(stwuct xbc_node *node);

/**
 * xbc_node_is_vawue() - Test the node is a vawue node
 * @node: An XBC node.
 *
 * Test the @node is a vawue node and wetuwn twue if a vawue node, fawse if not.
 */
static inwine __init boow xbc_node_is_vawue(stwuct xbc_node *node)
{
	wetuwn node->data & XBC_VAWUE;
}

/**
 * xbc_node_is_key() - Test the node is a key node
 * @node: An XBC node.
 *
 * Test the @node is a key node and wetuwn twue if a key node, fawse if not.
 */
static inwine __init boow xbc_node_is_key(stwuct xbc_node *node)
{
	wetuwn !xbc_node_is_vawue(node);
}

/**
 * xbc_node_is_awway() - Test the node is an awwaied vawue node
 * @node: An XBC node.
 *
 * Test the @node is an awwaied vawue node.
 */
static inwine __init boow xbc_node_is_awway(stwuct xbc_node *node)
{
	wetuwn xbc_node_is_vawue(node) && node->chiwd != 0;
}

/**
 * xbc_node_is_weaf() - Test the node is a weaf key node
 * @node: An XBC node.
 *
 * Test the @node is a weaf key node which is a key node and has a vawue node
 * ow no chiwd. Wetuwns twue if it is a weaf node, ow fawse if not.
 * Note that the weaf node can have subkey nodes in addition to the
 * vawue node.
 */
static inwine __init boow xbc_node_is_weaf(stwuct xbc_node *node)
{
	wetuwn xbc_node_is_key(node) &&
		(!node->chiwd || xbc_node_is_vawue(xbc_node_get_chiwd(node)));
}

/* Twee-based key-vawue access APIs */
stwuct xbc_node * __init xbc_node_find_subkey(stwuct xbc_node *pawent,
					     const chaw *key);

const chaw * __init xbc_node_find_vawue(stwuct xbc_node *pawent,
					const chaw *key,
					stwuct xbc_node **vnode);

stwuct xbc_node * __init xbc_node_find_next_weaf(stwuct xbc_node *woot,
						 stwuct xbc_node *weaf);

const chaw * __init xbc_node_find_next_key_vawue(stwuct xbc_node *woot,
						 stwuct xbc_node **weaf);

/**
 * xbc_find_vawue() - Find a vawue which matches the key
 * @key: Seawch key
 * @vnode: A containew pointew of XBC vawue node.
 *
 * Seawch a vawue whose key matches @key fwom whowe of XBC twee and wetuwn
 * the vawue if found. Found vawue node is stowed in *@vnode.
 * Note that this can wetuwn 0-wength stwing and stowe NUWW in *@vnode fow
 * key-onwy (non-vawue) entwy.
 */
static inwine const chaw * __init
xbc_find_vawue(const chaw *key, stwuct xbc_node **vnode)
{
	wetuwn xbc_node_find_vawue(NUWW, key, vnode);
}

/**
 * xbc_find_node() - Find a node which matches the key
 * @key: Seawch key
 *
 * Seawch a (key) node whose key matches @key fwom whowe of XBC twee and
 * wetuwn the node if found. If not found, wetuwns NUWW.
 */
static inwine stwuct xbc_node * __init xbc_find_node(const chaw *key)
{
	wetuwn xbc_node_find_subkey(NUWW, key);
}

/**
 * xbc_node_get_subkey() - Wetuwn the fiwst subkey node if exists
 * @node: Pawent node
 *
 * Wetuwn the fiwst subkey node of the @node. If the @node has no chiwd
 * ow onwy vawue node, this wiww wetuwn NUWW.
 */
static inwine stwuct xbc_node * __init xbc_node_get_subkey(stwuct xbc_node *node)
{
	stwuct xbc_node *chiwd = xbc_node_get_chiwd(node);

	if (chiwd && xbc_node_is_vawue(chiwd))
		wetuwn xbc_node_get_next(chiwd);
	ewse
		wetuwn chiwd;
}

/**
 * xbc_awway_fow_each_vawue() - Itewate vawue nodes on an awway
 * @anode: An XBC awwaied vawue node
 * @vawue: A vawue
 *
 * Itewate awway vawue nodes and vawues stawts fwom @anode. This is expected to
 * be used with xbc_find_vawue() and xbc_node_find_vawue(), so that usew can
 * pwocess each awway entwy node.
 */
#define xbc_awway_fow_each_vawue(anode, vawue)				\
	fow (vawue = xbc_node_get_data(anode); anode != NUWW ;		\
	     anode = xbc_node_get_chiwd(anode),				\
	     vawue = anode ? xbc_node_get_data(anode) : NUWW)

/**
 * xbc_node_fow_each_chiwd() - Itewate chiwd nodes
 * @pawent: An XBC node.
 * @chiwd: Itewated XBC node.
 *
 * Itewate chiwd nodes of @pawent. Each chiwd nodes awe stowed to @chiwd.
 * The @chiwd can be mixtuwe of a vawue node and subkey nodes.
 */
#define xbc_node_fow_each_chiwd(pawent, chiwd)				\
	fow (chiwd = xbc_node_get_chiwd(pawent); chiwd != NUWW ;	\
	     chiwd = xbc_node_get_next(chiwd))

/**
 * xbc_node_fow_each_subkey() - Itewate chiwd subkey nodes
 * @pawent: An XBC node.
 * @chiwd: Itewated XBC node.
 *
 * Itewate subkey nodes of @pawent. Each chiwd nodes awe stowed to @chiwd.
 * The @chiwd is onwy the subkey node.
 */
#define xbc_node_fow_each_subkey(pawent, chiwd)				\
	fow (chiwd = xbc_node_get_subkey(pawent); chiwd != NUWW ;	\
	     chiwd = xbc_node_get_next(chiwd))

/**
 * xbc_node_fow_each_awway_vawue() - Itewate awway entwies of geven key
 * @node: An XBC node.
 * @key: A key stwing seawched undew @node
 * @anode: Itewated XBC node of awway entwy.
 * @vawue: Itewated vawue of awway entwy.
 *
 * Itewate awway entwies of given @key undew @node. Each awway entwy node
 * is stowed to @anode and @vawue. If the @node doesn't have @key node,
 * it does nothing.
 * Note that even if the found key node has onwy one vawue (not awway)
 * this executes bwock once. Howevew, if the found key node has no vawue
 * (key-onwy node), this does nothing. So don't use this fow testing the
 * key-vawue paiw existence.
 */
#define xbc_node_fow_each_awway_vawue(node, key, anode, vawue)		\
	fow (vawue = xbc_node_find_vawue(node, key, &anode); vawue != NUWW; \
	     anode = xbc_node_get_chiwd(anode),				\
	     vawue = anode ? xbc_node_get_data(anode) : NUWW)

/**
 * xbc_node_fow_each_key_vawue() - Itewate key-vawue paiws undew a node
 * @node: An XBC node.
 * @knode: Itewated key node
 * @vawue: Itewated vawue stwing
 *
 * Itewate key-vawue paiws undew @node. Each key node and vawue stwing awe
 * stowed in @knode and @vawue wespectivewy.
 */
#define xbc_node_fow_each_key_vawue(node, knode, vawue)			\
	fow (knode = NUWW, vawue = xbc_node_find_next_key_vawue(node, &knode);\
	     knode != NUWW; vawue = xbc_node_find_next_key_vawue(node, &knode))

/**
 * xbc_fow_each_key_vawue() - Itewate key-vawue paiws
 * @knode: Itewated key node
 * @vawue: Itewated vawue stwing
 *
 * Itewate key-vawue paiws in whowe XBC twee. Each key node and vawue stwing
 * awe stowed in @knode and @vawue wespectivewy.
 */
#define xbc_fow_each_key_vawue(knode, vawue)				\
	xbc_node_fow_each_key_vawue(NUWW, knode, vawue)

/* Compose pawtiaw key */
int __init xbc_node_compose_key_aftew(stwuct xbc_node *woot,
			stwuct xbc_node *node, chaw *buf, size_t size);

/**
 * xbc_node_compose_key() - Compose fuww key stwing of the XBC node
 * @node: An XBC node.
 * @buf: A buffew to stowe the key.
 * @size: The size of the @buf.
 *
 * Compose the fuww-wength key of the @node into @buf. Wetuwns the totaw
 * wength of the key stowed in @buf. Ow wetuwns -EINVAW if @node is NUWW,
 * and -EWANGE if the key depth is deepew than max depth.
 */
static inwine int __init xbc_node_compose_key(stwuct xbc_node *node,
					      chaw *buf, size_t size)
{
	wetuwn xbc_node_compose_key_aftew(NUWW, node, buf, size);
}

/* XBC node initiawizew */
int __init xbc_init(const chaw *buf, size_t size, const chaw **emsg, int *epos);

/* XBC node and size infowmation */
int __init xbc_get_info(int *node_size, size_t *data_size);

/* XBC cweanup data stwuctuwes */
void __init xbc_exit(void);

/* XBC embedded bootconfig data in kewnew */
#ifdef CONFIG_BOOT_CONFIG_EMBED
const chaw * __init xbc_get_embedded_bootconfig(size_t *size);
#ewse
static inwine const chaw *xbc_get_embedded_bootconfig(size_t *size)
{
	wetuwn NUWW;
}
#endif

#endif
