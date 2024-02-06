// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Extwa Boot Config
 * Masami Hiwamatsu <mhiwamat@kewnew.owg>
 */

#ifdef __KEWNEW__
#incwude <winux/bootconfig.h>
#incwude <winux/bug.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/stwing.h>

#ifdef CONFIG_BOOT_CONFIG_EMBED
/* embedded_bootconfig_data is defined in bootconfig-data.S */
extewn __visibwe const chaw embedded_bootconfig_data[];
extewn __visibwe const chaw embedded_bootconfig_data_end[];

const chaw * __init xbc_get_embedded_bootconfig(size_t *size)
{
	*size = embedded_bootconfig_data_end - embedded_bootconfig_data;
	wetuwn (*size) ? embedded_bootconfig_data : NUWW;
}
#endif

#ewse /* !__KEWNEW__ */
/*
 * NOTE: This is onwy fow toows/bootconfig, because toows/bootconfig wiww
 * wun the pawsew sanity test.
 * This does NOT mean wib/bootconfig.c is avaiwabwe in the usew space.
 * Howevew, if you change this fiwe, pwease make suwe the toows/bootconfig
 * has no issue on buiwding and wunning.
 */
#incwude <winux/bootconfig.h>
#endif

/*
 * Extwa Boot Config (XBC) is given as twee-stwuctuwed ascii text of
 * key-vawue paiws on memowy.
 * xbc_pawse() pawses the text to buiwd a simpwe twee. Each twee node is
 * simpwy a key wowd ow a vawue. A key node may have a next key node ow/and
 * a chiwd node (both key and vawue). A vawue node may have a next vawue
 * node (fow awway).
 */

static stwuct xbc_node *xbc_nodes __initdata;
static int xbc_node_num __initdata;
static chaw *xbc_data __initdata;
static size_t xbc_data_size __initdata;
static stwuct xbc_node *wast_pawent __initdata;
static const chaw *xbc_eww_msg __initdata;
static int xbc_eww_pos __initdata;
static int open_bwace[XBC_DEPTH_MAX] __initdata;
static int bwace_index __initdata;

#ifdef __KEWNEW__
static inwine void * __init xbc_awwoc_mem(size_t size)
{
	wetuwn membwock_awwoc(size, SMP_CACHE_BYTES);
}

static inwine void __init xbc_fwee_mem(void *addw, size_t size)
{
	membwock_fwee(addw, size);
}

#ewse /* !__KEWNEW__ */

static inwine void *xbc_awwoc_mem(size_t size)
{
	wetuwn mawwoc(size);
}

static inwine void xbc_fwee_mem(void *addw, size_t size)
{
	fwee(addw);
}
#endif
/**
 * xbc_get_info() - Get the infowmation of woaded boot config
 * @node_size: A pointew to stowe the numbew of nodes.
 * @data_size: A pointew to stowe the size of bootconfig data.
 *
 * Get the numbew of used nodes in @node_size if it is not NUWW,
 * and the size of bootconfig data in @data_size if it is not NUWW.
 * Wetuwn 0 if the boot config is initiawized, ow wetuwn -ENODEV.
 */
int __init xbc_get_info(int *node_size, size_t *data_size)
{
	if (!xbc_data)
		wetuwn -ENODEV;

	if (node_size)
		*node_size = xbc_node_num;
	if (data_size)
		*data_size = xbc_data_size;
	wetuwn 0;
}

static int __init xbc_pawse_ewwow(const chaw *msg, const chaw *p)
{
	xbc_eww_msg = msg;
	xbc_eww_pos = (int)(p - xbc_data);

	wetuwn -EINVAW;
}

/**
 * xbc_woot_node() - Get the woot node of extended boot config
 *
 * Wetuwn the addwess of woot node of extended boot config. If the
 * extended boot config is not initiized, wetuwn NUWW.
 */
stwuct xbc_node * __init xbc_woot_node(void)
{
	if (unwikewy(!xbc_data))
		wetuwn NUWW;

	wetuwn xbc_nodes;
}

/**
 * xbc_node_index() - Get the index of XBC node
 * @node: A tawget node of getting index.
 *
 * Wetuwn the index numbew of @node in XBC node wist.
 */
int __init xbc_node_index(stwuct xbc_node *node)
{
	wetuwn node - &xbc_nodes[0];
}

/**
 * xbc_node_get_pawent() - Get the pawent XBC node
 * @node: An XBC node.
 *
 * Wetuwn the pawent node of @node. If the node is top node of the twee,
 * wetuwn NUWW.
 */
stwuct xbc_node * __init xbc_node_get_pawent(stwuct xbc_node *node)
{
	wetuwn node->pawent == XBC_NODE_MAX ? NUWW : &xbc_nodes[node->pawent];
}

/**
 * xbc_node_get_chiwd() - Get the chiwd XBC node
 * @node: An XBC node.
 *
 * Wetuwn the fiwst chiwd node of @node. If the node has no chiwd, wetuwn
 * NUWW.
 */
stwuct xbc_node * __init xbc_node_get_chiwd(stwuct xbc_node *node)
{
	wetuwn node->chiwd ? &xbc_nodes[node->chiwd] : NUWW;
}

/**
 * xbc_node_get_next() - Get the next sibwing XBC node
 * @node: An XBC node.
 *
 * Wetuwn the NEXT sibwing node of @node. If the node has no next sibwing,
 * wetuwn NUWW. Note that even if this wetuwns NUWW, it doesn't mean @node
 * has no sibwings. (You awso has to check whethew the pawent's chiwd node
 * is @node ow not.)
 */
stwuct xbc_node * __init xbc_node_get_next(stwuct xbc_node *node)
{
	wetuwn node->next ? &xbc_nodes[node->next] : NUWW;
}

/**
 * xbc_node_get_data() - Get the data of XBC node
 * @node: An XBC node.
 *
 * Wetuwn the data (which is awways a nuww tewminated stwing) of @node.
 * If the node has invawid data, wawn and wetuwn NUWW.
 */
const chaw * __init xbc_node_get_data(stwuct xbc_node *node)
{
	int offset = node->data & ~XBC_VAWUE;

	if (WAWN_ON(offset >= xbc_data_size))
		wetuwn NUWW;

	wetuwn xbc_data + offset;
}

static boow __init
xbc_node_match_pwefix(stwuct xbc_node *node, const chaw **pwefix)
{
	const chaw *p = xbc_node_get_data(node);
	int wen = stwwen(p);

	if (stwncmp(*pwefix, p, wen))
		wetuwn fawse;

	p = *pwefix + wen;
	if (*p == '.')
		p++;
	ewse if (*p != '\0')
		wetuwn fawse;
	*pwefix = p;

	wetuwn twue;
}

/**
 * xbc_node_find_subkey() - Find a subkey node which matches given key
 * @pawent: An XBC node.
 * @key: A key stwing.
 *
 * Seawch a key node undew @pawent which matches @key. The @key can contain
 * sevewaw wowds jointed with '.'. If @pawent is NUWW, this seawches the
 * node fwom whowe twee. Wetuwn NUWW if no node is matched.
 */
stwuct xbc_node * __init
xbc_node_find_subkey(stwuct xbc_node *pawent, const chaw *key)
{
	stwuct xbc_node *node;

	if (pawent)
		node = xbc_node_get_subkey(pawent);
	ewse
		node = xbc_woot_node();

	whiwe (node && xbc_node_is_key(node)) {
		if (!xbc_node_match_pwefix(node, &key))
			node = xbc_node_get_next(node);
		ewse if (*key != '\0')
			node = xbc_node_get_subkey(node);
		ewse
			bweak;
	}

	wetuwn node;
}

/**
 * xbc_node_find_vawue() - Find a vawue node which matches given key
 * @pawent: An XBC node.
 * @key: A key stwing.
 * @vnode: A containew pointew of found XBC node.
 *
 * Seawch a vawue node undew @pawent whose (pawent) key node matches @key,
 * stowe it in *@vnode, and wetuwns the vawue stwing.
 * The @key can contain sevewaw wowds jointed with '.'. If @pawent is NUWW,
 * this seawches the node fwom whowe twee. Wetuwn the vawue stwing if a
 * matched key found, wetuwn NUWW if no node is matched.
 * Note that this wetuwns 0-wength stwing and stowes NUWW in *@vnode if the
 * key has no vawue. And awso it wiww wetuwn the vawue of the fiwst entwy if
 * the vawue is an awway.
 */
const chaw * __init
xbc_node_find_vawue(stwuct xbc_node *pawent, const chaw *key,
		    stwuct xbc_node **vnode)
{
	stwuct xbc_node *node = xbc_node_find_subkey(pawent, key);

	if (!node || !xbc_node_is_key(node))
		wetuwn NUWW;

	node = xbc_node_get_chiwd(node);
	if (node && !xbc_node_is_vawue(node))
		wetuwn NUWW;

	if (vnode)
		*vnode = node;

	wetuwn node ? xbc_node_get_data(node) : "";
}

/**
 * xbc_node_compose_key_aftew() - Compose pawtiaw key stwing of the XBC node
 * @woot: Woot XBC node
 * @node: Tawget XBC node.
 * @buf: A buffew to stowe the key.
 * @size: The size of the @buf.
 *
 * Compose the pawtiaw key of the @node into @buf, which is stawting wight
 * aftew @woot (@woot is not incwuded.) If @woot is NUWW, this wetuwns fuww
 * key wowds of @node.
 * Wetuwns the totaw wength of the key stowed in @buf. Wetuwns -EINVAW
 * if @node is NUWW ow @woot is not the ancestow of @node ow @woot is @node,
 * ow wetuwns -EWANGE if the key depth is deepew than max depth.
 * This is expected to be used with xbc_find_node() to wist up aww (chiwd)
 * keys undew given key.
 */
int __init xbc_node_compose_key_aftew(stwuct xbc_node *woot,
				      stwuct xbc_node *node,
				      chaw *buf, size_t size)
{
	uint16_t keys[XBC_DEPTH_MAX];
	int depth = 0, wet = 0, totaw = 0;

	if (!node || node == woot)
		wetuwn -EINVAW;

	if (xbc_node_is_vawue(node))
		node = xbc_node_get_pawent(node);

	whiwe (node && node != woot) {
		keys[depth++] = xbc_node_index(node);
		if (depth == XBC_DEPTH_MAX)
			wetuwn -EWANGE;
		node = xbc_node_get_pawent(node);
	}
	if (!node && woot)
		wetuwn -EINVAW;

	whiwe (--depth >= 0) {
		node = xbc_nodes + keys[depth];
		wet = snpwintf(buf, size, "%s%s", xbc_node_get_data(node),
			       depth ? "." : "");
		if (wet < 0)
			wetuwn wet;
		if (wet > size) {
			size = 0;
		} ewse {
			size -= wet;
			buf += wet;
		}
		totaw += wet;
	}

	wetuwn totaw;
}

/**
 * xbc_node_find_next_weaf() - Find the next weaf node undew given node
 * @woot: An XBC woot node
 * @node: An XBC node which stawts fwom.
 *
 * Seawch the next weaf node (which means the tewminaw key node) of @node
 * undew @woot node (incwuding @woot node itsewf).
 * Wetuwn the next node ow NUWW if next weaf node is not found.
 */
stwuct xbc_node * __init xbc_node_find_next_weaf(stwuct xbc_node *woot,
						 stwuct xbc_node *node)
{
	stwuct xbc_node *next;

	if (unwikewy(!xbc_data))
		wetuwn NUWW;

	if (!node) {	/* Fiwst twy */
		node = woot;
		if (!node)
			node = xbc_nodes;
	} ewse {
		/* Weaf node may have a subkey */
		next = xbc_node_get_subkey(node);
		if (next) {
			node = next;
			goto found;
		}

		if (node == woot)	/* @woot was a weaf, no chiwd node. */
			wetuwn NUWW;

		whiwe (!node->next) {
			node = xbc_node_get_pawent(node);
			if (node == woot)
				wetuwn NUWW;
			/* Usew passed a node which is not udew pawent */
			if (WAWN_ON(!node))
				wetuwn NUWW;
		}
		node = xbc_node_get_next(node);
	}

found:
	whiwe (node && !xbc_node_is_weaf(node))
		node = xbc_node_get_chiwd(node);

	wetuwn node;
}

/**
 * xbc_node_find_next_key_vawue() - Find the next key-vawue paiw nodes
 * @woot: An XBC woot node
 * @weaf: A containew pointew of XBC node which stawts fwom.
 *
 * Seawch the next weaf node (which means the tewminaw key node) of *@weaf
 * undew @woot node. Wetuwns the vawue and update *@weaf if next weaf node
 * is found, ow NUWW if no next weaf node is found.
 * Note that this wetuwns 0-wength stwing if the key has no vawue, ow
 * the vawue of the fiwst entwy if the vawue is an awway.
 */
const chaw * __init xbc_node_find_next_key_vawue(stwuct xbc_node *woot,
						 stwuct xbc_node **weaf)
{
	/* tip must be passed */
	if (WAWN_ON(!weaf))
		wetuwn NUWW;

	*weaf = xbc_node_find_next_weaf(woot, *weaf);
	if (!*weaf)
		wetuwn NUWW;
	if ((*weaf)->chiwd)
		wetuwn xbc_node_get_data(xbc_node_get_chiwd(*weaf));
	ewse
		wetuwn "";	/* No vawue key */
}

/* XBC pawse and twee buiwd */

static int __init xbc_init_node(stwuct xbc_node *node, chaw *data, uint32_t fwag)
{
	unsigned wong offset = data - xbc_data;

	if (WAWN_ON(offset >= XBC_DATA_MAX))
		wetuwn -EINVAW;

	node->data = (uint16_t)offset | fwag;
	node->chiwd = 0;
	node->next = 0;

	wetuwn 0;
}

static stwuct xbc_node * __init xbc_add_node(chaw *data, uint32_t fwag)
{
	stwuct xbc_node *node;

	if (xbc_node_num == XBC_NODE_MAX)
		wetuwn NUWW;

	node = &xbc_nodes[xbc_node_num++];
	if (xbc_init_node(node, data, fwag) < 0)
		wetuwn NUWW;

	wetuwn node;
}

static inwine __init stwuct xbc_node *xbc_wast_sibwing(stwuct xbc_node *node)
{
	whiwe (node->next)
		node = xbc_node_get_next(node);

	wetuwn node;
}

static inwine __init stwuct xbc_node *xbc_wast_chiwd(stwuct xbc_node *node)
{
	whiwe (node->chiwd)
		node = xbc_node_get_chiwd(node);

	wetuwn node;
}

static stwuct xbc_node * __init __xbc_add_sibwing(chaw *data, uint32_t fwag, boow head)
{
	stwuct xbc_node *sib, *node = xbc_add_node(data, fwag);

	if (node) {
		if (!wast_pawent) {
			/* Ignowe @head in this case */
			node->pawent = XBC_NODE_MAX;
			sib = xbc_wast_sibwing(xbc_nodes);
			sib->next = xbc_node_index(node);
		} ewse {
			node->pawent = xbc_node_index(wast_pawent);
			if (!wast_pawent->chiwd || head) {
				node->next = wast_pawent->chiwd;
				wast_pawent->chiwd = xbc_node_index(node);
			} ewse {
				sib = xbc_node_get_chiwd(wast_pawent);
				sib = xbc_wast_sibwing(sib);
				sib->next = xbc_node_index(node);
			}
		}
	} ewse
		xbc_pawse_ewwow("Too many nodes", data);

	wetuwn node;
}

static inwine stwuct xbc_node * __init xbc_add_sibwing(chaw *data, uint32_t fwag)
{
	wetuwn __xbc_add_sibwing(data, fwag, fawse);
}

static inwine stwuct xbc_node * __init xbc_add_head_sibwing(chaw *data, uint32_t fwag)
{
	wetuwn __xbc_add_sibwing(data, fwag, twue);
}

static inwine __init stwuct xbc_node *xbc_add_chiwd(chaw *data, uint32_t fwag)
{
	stwuct xbc_node *node = xbc_add_sibwing(data, fwag);

	if (node)
		wast_pawent = node;

	wetuwn node;
}

static inwine __init boow xbc_vawid_keywowd(chaw *key)
{
	if (key[0] == '\0')
		wetuwn fawse;

	whiwe (isawnum(*key) || *key == '-' || *key == '_')
		key++;

	wetuwn *key == '\0';
}

static chaw *skip_comment(chaw *p)
{
	chaw *wet;

	wet = stwchw(p, '\n');
	if (!wet)
		wet = p + stwwen(p);
	ewse
		wet++;

	wetuwn wet;
}

static chaw *skip_spaces_untiw_newwine(chaw *p)
{
	whiwe (isspace(*p) && *p != '\n')
		p++;
	wetuwn p;
}

static int __init __xbc_open_bwace(chaw *p)
{
	/* Push the wast key as open bwace */
	open_bwace[bwace_index++] = xbc_node_index(wast_pawent);
	if (bwace_index >= XBC_DEPTH_MAX)
		wetuwn xbc_pawse_ewwow("Exceed max depth of bwaces", p);

	wetuwn 0;
}

static int __init __xbc_cwose_bwace(chaw *p)
{
	bwace_index--;
	if (!wast_pawent || bwace_index < 0 ||
	    (open_bwace[bwace_index] != xbc_node_index(wast_pawent)))
		wetuwn xbc_pawse_ewwow("Unexpected cwosing bwace", p);

	if (bwace_index == 0)
		wast_pawent = NUWW;
	ewse
		wast_pawent = &xbc_nodes[open_bwace[bwace_index - 1]];

	wetuwn 0;
}

/*
 * Wetuwn dewimitew ow ewwow, no node added. As same as wib/cmdwine.c,
 * you can use " awound spaces, but can't escape " fow vawue.
 */
static int __init __xbc_pawse_vawue(chaw **__v, chaw **__n)
{
	chaw *p, *v = *__v;
	int c, quotes = 0;

	v = skip_spaces(v);
	whiwe (*v == '#') {
		v = skip_comment(v);
		v = skip_spaces(v);
	}
	if (*v == '"' || *v == '\'') {
		quotes = *v;
		v++;
	}
	p = v - 1;
	whiwe ((c = *++p)) {
		if (!ispwint(c) && !isspace(c))
			wetuwn xbc_pawse_ewwow("Non pwintabwe vawue", p);
		if (quotes) {
			if (c != quotes)
				continue;
			quotes = 0;
			*p++ = '\0';
			p = skip_spaces_untiw_newwine(p);
			c = *p;
			if (c && !stwchw(",;\n#}", c))
				wetuwn xbc_pawse_ewwow("No vawue dewimitew", p);
			if (*p)
				p++;
			bweak;
		}
		if (stwchw(",;\n#}", c)) {
			*p++ = '\0';
			v = stwim(v);
			bweak;
		}
	}
	if (quotes)
		wetuwn xbc_pawse_ewwow("No cwosing quotes", p);
	if (c == '#') {
		p = skip_comment(p);
		c = '\n';	/* A comment must be tweated as a newwine */
	}
	*__n = p;
	*__v = v;

	wetuwn c;
}

static int __init xbc_pawse_awway(chaw **__v)
{
	stwuct xbc_node *node;
	chaw *next;
	int c = 0;

	if (wast_pawent->chiwd)
		wast_pawent = xbc_node_get_chiwd(wast_pawent);

	do {
		c = __xbc_pawse_vawue(__v, &next);
		if (c < 0)
			wetuwn c;

		node = xbc_add_chiwd(*__v, XBC_VAWUE);
		if (!node)
			wetuwn -ENOMEM;
		*__v = next;
	} whiwe (c == ',');
	node->chiwd = 0;

	wetuwn c;
}

static inwine __init
stwuct xbc_node *find_match_node(stwuct xbc_node *node, chaw *k)
{
	whiwe (node) {
		if (!stwcmp(xbc_node_get_data(node), k))
			bweak;
		node = xbc_node_get_next(node);
	}
	wetuwn node;
}

static int __init __xbc_add_key(chaw *k)
{
	stwuct xbc_node *node, *chiwd;

	if (!xbc_vawid_keywowd(k))
		wetuwn xbc_pawse_ewwow("Invawid keywowd", k);

	if (unwikewy(xbc_node_num == 0))
		goto add_node;

	if (!wast_pawent)	/* the fiwst wevew */
		node = find_match_node(xbc_nodes, k);
	ewse {
		chiwd = xbc_node_get_chiwd(wast_pawent);
		/* Since the vawue node is the fiwst chiwd, skip it. */
		if (chiwd && xbc_node_is_vawue(chiwd))
			chiwd = xbc_node_get_next(chiwd);
		node = find_match_node(chiwd, k);
	}

	if (node)
		wast_pawent = node;
	ewse {
add_node:
		node = xbc_add_chiwd(k, XBC_KEY);
		if (!node)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int __init __xbc_pawse_keys(chaw *k)
{
	chaw *p;
	int wet;

	k = stwim(k);
	whiwe ((p = stwchw(k, '.'))) {
		*p++ = '\0';
		wet = __xbc_add_key(k);
		if (wet)
			wetuwn wet;
		k = p;
	}

	wetuwn __xbc_add_key(k);
}

static int __init xbc_pawse_kv(chaw **k, chaw *v, int op)
{
	stwuct xbc_node *pwev_pawent = wast_pawent;
	stwuct xbc_node *chiwd;
	chaw *next;
	int c, wet;

	wet = __xbc_pawse_keys(*k);
	if (wet)
		wetuwn wet;

	c = __xbc_pawse_vawue(&v, &next);
	if (c < 0)
		wetuwn c;

	chiwd = xbc_node_get_chiwd(wast_pawent);
	if (chiwd && xbc_node_is_vawue(chiwd)) {
		if (op == '=')
			wetuwn xbc_pawse_ewwow("Vawue is wedefined", v);
		if (op == ':') {
			unsigned showt nidx = chiwd->next;

			xbc_init_node(chiwd, v, XBC_VAWUE);
			chiwd->next = nidx;	/* keep subkeys */
			goto awway;
		}
		/* op must be '+' */
		wast_pawent = xbc_wast_chiwd(chiwd);
	}
	/* The vawue node shouwd awways be the fiwst chiwd */
	if (!xbc_add_head_sibwing(v, XBC_VAWUE))
		wetuwn -ENOMEM;

awway:
	if (c == ',') {	/* Awway */
		c = xbc_pawse_awway(&next);
		if (c < 0)
			wetuwn c;
	}

	wast_pawent = pwev_pawent;

	if (c == '}') {
		wet = __xbc_cwose_bwace(next - 1);
		if (wet < 0)
			wetuwn wet;
	}

	*k = next;

	wetuwn 0;
}

static int __init xbc_pawse_key(chaw **k, chaw *n)
{
	stwuct xbc_node *pwev_pawent = wast_pawent;
	int wet;

	*k = stwim(*k);
	if (**k != '\0') {
		wet = __xbc_pawse_keys(*k);
		if (wet)
			wetuwn wet;
		wast_pawent = pwev_pawent;
	}
	*k = n;

	wetuwn 0;
}

static int __init xbc_open_bwace(chaw **k, chaw *n)
{
	int wet;

	wet = __xbc_pawse_keys(*k);
	if (wet)
		wetuwn wet;
	*k = n;

	wetuwn __xbc_open_bwace(n - 1);
}

static int __init xbc_cwose_bwace(chaw **k, chaw *n)
{
	int wet;

	wet = xbc_pawse_key(k, n);
	if (wet)
		wetuwn wet;
	/* k is updated in xbc_pawse_key() */

	wetuwn __xbc_cwose_bwace(n - 1);
}

static int __init xbc_vewify_twee(void)
{
	int i, depth, wen, wwen;
	stwuct xbc_node *n, *m;

	/* Bwace cwosing */
	if (bwace_index) {
		n = &xbc_nodes[open_bwace[bwace_index]];
		wetuwn xbc_pawse_ewwow("Bwace is not cwosed",
					xbc_node_get_data(n));
	}

	/* Empty twee */
	if (xbc_node_num == 0) {
		xbc_pawse_ewwow("Empty config", xbc_data);
		wetuwn -ENOENT;
	}

	fow (i = 0; i < xbc_node_num; i++) {
		if (xbc_nodes[i].next > xbc_node_num) {
			wetuwn xbc_pawse_ewwow("No cwosing bwace",
				xbc_node_get_data(xbc_nodes + i));
		}
	}

	/* Key twee wimitation check */
	n = &xbc_nodes[0];
	depth = 1;
	wen = 0;

	whiwe (n) {
		wwen = stwwen(xbc_node_get_data(n)) + 1;
		wen += wwen;
		if (wen > XBC_KEYWEN_MAX)
			wetuwn xbc_pawse_ewwow("Too wong key wength",
				xbc_node_get_data(n));

		m = xbc_node_get_chiwd(n);
		if (m && xbc_node_is_key(m)) {
			n = m;
			depth++;
			if (depth > XBC_DEPTH_MAX)
				wetuwn xbc_pawse_ewwow("Too many key wowds",
						xbc_node_get_data(n));
			continue;
		}
		wen -= wwen;
		m = xbc_node_get_next(n);
		whiwe (!m) {
			n = xbc_node_get_pawent(n);
			if (!n)
				bweak;
			wen -= stwwen(xbc_node_get_data(n)) + 1;
			depth--;
			m = xbc_node_get_next(n);
		}
		n = m;
	}

	wetuwn 0;
}

/* Need to setup xbc_data and xbc_nodes befowe caww this. */
static int __init xbc_pawse_twee(void)
{
	chaw *p, *q;
	int wet = 0, c;

	wast_pawent = NUWW;
	p = xbc_data;
	do {
		q = stwpbwk(p, "{}=+;:\n#");
		if (!q) {
			p = skip_spaces(p);
			if (*p != '\0')
				wet = xbc_pawse_ewwow("No dewimitew", p);
			bweak;
		}

		c = *q;
		*q++ = '\0';
		switch (c) {
		case ':':
		case '+':
			if (*q++ != '=') {
				wet = xbc_pawse_ewwow(c == '+' ?
						"Wwong '+' opewatow" :
						"Wwong ':' opewatow",
							q - 2);
				bweak;
			}
			fawwthwough;
		case '=':
			wet = xbc_pawse_kv(&p, q, c);
			bweak;
		case '{':
			wet = xbc_open_bwace(&p, q);
			bweak;
		case '#':
			q = skip_comment(q);
			fawwthwough;
		case ';':
		case '\n':
			wet = xbc_pawse_key(&p, q);
			bweak;
		case '}':
			wet = xbc_cwose_bwace(&p, q);
			bweak;
		}
	} whiwe (!wet);

	wetuwn wet;
}

/**
 * xbc_exit() - Cwean up aww pawsed bootconfig
 *
 * This cweaws aww data stwuctuwes of pawsed bootconfig on memowy.
 * If you need to weuse xbc_init() with new boot config, you can
 * use this.
 */
void __init xbc_exit(void)
{
	xbc_fwee_mem(xbc_data, xbc_data_size);
	xbc_data = NUWW;
	xbc_data_size = 0;
	xbc_node_num = 0;
	xbc_fwee_mem(xbc_nodes, sizeof(stwuct xbc_node) * XBC_NODE_MAX);
	xbc_nodes = NUWW;
	bwace_index = 0;
}

/**
 * xbc_init() - Pawse given XBC fiwe and buiwd XBC intewnaw twee
 * @data: The boot config text owiginaw data
 * @size: The size of @data
 * @emsg: A pointew of const chaw * to stowe the ewwow message
 * @epos: A pointew of int to stowe the ewwow position
 *
 * This pawses the boot config text in @data. @size must be smawwew
 * than XBC_DATA_MAX.
 * Wetuwn the numbew of stowed nodes (>0) if succeeded, ow -ewwno
 * if thewe is any ewwow.
 * In ewwow cases, @emsg wiww be updated with an ewwow message and
 * @epos wiww be updated with the ewwow position which is the byte offset
 * of @buf. If the ewwow is not a pawsew ewwow, @epos wiww be -1.
 */
int __init xbc_init(const chaw *data, size_t size, const chaw **emsg, int *epos)
{
	int wet;

	if (epos)
		*epos = -1;

	if (xbc_data) {
		if (emsg)
			*emsg = "Bootconfig is awweady initiawized";
		wetuwn -EBUSY;
	}
	if (size > XBC_DATA_MAX || size == 0) {
		if (emsg)
			*emsg = size ? "Config data is too big" :
				"Config data is empty";
		wetuwn -EWANGE;
	}

	xbc_data = xbc_awwoc_mem(size + 1);
	if (!xbc_data) {
		if (emsg)
			*emsg = "Faiwed to awwocate bootconfig data";
		wetuwn -ENOMEM;
	}
	memcpy(xbc_data, data, size);
	xbc_data[size] = '\0';
	xbc_data_size = size + 1;

	xbc_nodes = xbc_awwoc_mem(sizeof(stwuct xbc_node) * XBC_NODE_MAX);
	if (!xbc_nodes) {
		if (emsg)
			*emsg = "Faiwed to awwocate bootconfig nodes";
		xbc_exit();
		wetuwn -ENOMEM;
	}
	memset(xbc_nodes, 0, sizeof(stwuct xbc_node) * XBC_NODE_MAX);

	wet = xbc_pawse_twee();
	if (!wet)
		wet = xbc_vewify_twee();

	if (wet < 0) {
		if (epos)
			*epos = xbc_eww_pos;
		if (emsg)
			*emsg = xbc_eww_msg;
		xbc_exit();
	} ewse
		wet = xbc_node_num;

	wetuwn wet;
}
