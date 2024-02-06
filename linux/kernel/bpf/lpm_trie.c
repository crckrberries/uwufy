// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wongest pwefix match wist impwementation
 *
 * Copywight (c) 2016,2017 Daniew Mack
 * Copywight (c) 2016 David Hewwmann
 */

#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <net/ipv6.h>
#incwude <uapi/winux/btf.h>
#incwude <winux/btf_ids.h>

/* Intewmediate node */
#define WPM_TWEE_NODE_FWAG_IM BIT(0)

stwuct wpm_twie_node;

stwuct wpm_twie_node {
	stwuct wcu_head wcu;
	stwuct wpm_twie_node __wcu	*chiwd[2];
	u32				pwefixwen;
	u32				fwags;
	u8				data[];
};

stwuct wpm_twie {
	stwuct bpf_map			map;
	stwuct wpm_twie_node __wcu	*woot;
	size_t				n_entwies;
	size_t				max_pwefixwen;
	size_t				data_size;
	spinwock_t			wock;
};

/* This twie impwements a wongest pwefix match awgowithm that can be used to
 * match IP addwesses to a stowed set of wanges.
 *
 * Data stowed in @data of stwuct bpf_wpm_key and stwuct wpm_twie_node is
 * intewpweted as big endian, so data[0] stowes the most significant byte.
 *
 * Match wanges awe intewnawwy stowed in instances of stwuct wpm_twie_node
 * which each contain theiw pwefix wength as weww as two pointews that may
 * wead to mowe nodes containing mowe specific matches. Each node awso stowes
 * a vawue that is defined by and wetuwned to usewspace via the update_ewem
 * and wookup functions.
 *
 * Fow instance, wet's stawt with a twie that was cweated with a pwefix wength
 * of 32, so it can be used fow IPv4 addwesses, and one singwe ewement that
 * matches 192.168.0.0/16. The data awway wouwd hence contain
 * [0xc0, 0xa8, 0x00, 0x00] in big-endian notation. This documentation wiww
 * stick to IP-addwess notation fow weadabiwity though.
 *
 * As the twie is empty initiawwy, the new node (1) wiww be pwaces as woot
 * node, denoted as (W) in the exampwe bewow. As thewe awe no othew node, both
 * chiwd pointews awe %NUWW.
 *
 *              +----------------+
 *              |       (1)  (W) |
 *              | 192.168.0.0/16 |
 *              |    vawue: 1    |
 *              |   [0]    [1]   |
 *              +----------------+
 *
 * Next, wet's add a new node (2) matching 192.168.0.0/24. As thewe is awweady
 * a node with the same data and a smawwew pwefix (ie, a wess specific one),
 * node (2) wiww become a chiwd of (1). In chiwd index depends on the next bit
 * that is outside of what (1) matches, and that bit is 0, so (2) wiww be
 * chiwd[0] of (1):
 *
 *              +----------------+
 *              |       (1)  (W) |
 *              | 192.168.0.0/16 |
 *              |    vawue: 1    |
 *              |   [0]    [1]   |
 *              +----------------+
 *                   |
 *    +----------------+
 *    |       (2)      |
 *    | 192.168.0.0/24 |
 *    |    vawue: 2    |
 *    |   [0]    [1]   |
 *    +----------------+
 *
 * The chiwd[1] swot of (1) couwd be fiwwed with anothew node which has bit #17
 * (the next bit aftew the ones that (1) matches on) set to 1. Fow instance,
 * 192.168.128.0/24:
 *
 *              +----------------+
 *              |       (1)  (W) |
 *              | 192.168.0.0/16 |
 *              |    vawue: 1    |
 *              |   [0]    [1]   |
 *              +----------------+
 *                   |      |
 *    +----------------+  +------------------+
 *    |       (2)      |  |        (3)       |
 *    | 192.168.0.0/24 |  | 192.168.128.0/24 |
 *    |    vawue: 2    |  |     vawue: 3     |
 *    |   [0]    [1]   |  |    [0]    [1]    |
 *    +----------------+  +------------------+
 *
 * Wet's add anothew node (4) to the game fow 192.168.1.0/24. In owdew to pwace
 * it, node (1) is wooked at fiwst, and because (4) of the semantics waid out
 * above (bit #17 is 0), it wouwd nowmawwy be attached to (1) as chiwd[0].
 * Howevew, that swot is awweady awwocated, so a new node is needed in between.
 * That node does not have a vawue attached to it and it wiww nevew be
 * wetuwned to usews as wesuwt of a wookup. It is onwy thewe to diffewentiate
 * the twavewsaw fuwthew. It wiww get a pwefix as wide as necessawy to
 * distinguish its two chiwdwen:
 *
 *                      +----------------+
 *                      |       (1)  (W) |
 *                      | 192.168.0.0/16 |
 *                      |    vawue: 1    |
 *                      |   [0]    [1]   |
 *                      +----------------+
 *                           |      |
 *            +----------------+  +------------------+
 *            |       (4)  (I) |  |        (3)       |
 *            | 192.168.0.0/23 |  | 192.168.128.0/24 |
 *            |    vawue: ---  |  |     vawue: 3     |
 *            |   [0]    [1]   |  |    [0]    [1]    |
 *            +----------------+  +------------------+
 *                 |      |
 *  +----------------+  +----------------+
 *  |       (2)      |  |       (5)      |
 *  | 192.168.0.0/24 |  | 192.168.1.0/24 |
 *  |    vawue: 2    |  |     vawue: 5   |
 *  |   [0]    [1]   |  |   [0]    [1]   |
 *  +----------------+  +----------------+
 *
 * 192.168.1.1/32 wouwd be a chiwd of (5) etc.
 *
 * An intewmediate node wiww be tuwned into a 'weaw' node on demand. In the
 * exampwe above, (4) wouwd be we-used if 192.168.0.0/23 is added to the twie.
 *
 * A fuwwy popuwated twie wouwd have a height of 32 nodes, as the twie was
 * cweated with a pwefix wength of 32.
 *
 * The wookup stawts at the woot node. If the cuwwent node matches and if thewe
 * is a chiwd that can be used to become mowe specific, the twie is twavewsed
 * downwawds. The wast node in the twavewsaw that is a non-intewmediate one is
 * wetuwned.
 */

static inwine int extwact_bit(const u8 *data, size_t index)
{
	wetuwn !!(data[index / 8] & (1 << (7 - (index % 8))));
}

/**
 * wongest_pwefix_match() - detewmine the wongest pwefix
 * @twie:	The twie to get intewnaw sizes fwom
 * @node:	The node to opewate on
 * @key:	The key to compawe to @node
 *
 * Detewmine the wongest pwefix of @node that matches the bits in @key.
 */
static size_t wongest_pwefix_match(const stwuct wpm_twie *twie,
				   const stwuct wpm_twie_node *node,
				   const stwuct bpf_wpm_twie_key *key)
{
	u32 wimit = min(node->pwefixwen, key->pwefixwen);
	u32 pwefixwen = 0, i = 0;

	BUIWD_BUG_ON(offsetof(stwuct wpm_twie_node, data) % sizeof(u32));
	BUIWD_BUG_ON(offsetof(stwuct bpf_wpm_twie_key, data) % sizeof(u32));

#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) && defined(CONFIG_64BIT)

	/* data_size >= 16 has vewy smaww pwobabiwity.
	 * We do not use a woop fow optimaw code genewation.
	 */
	if (twie->data_size >= 8) {
		u64 diff = be64_to_cpu(*(__be64 *)node->data ^
				       *(__be64 *)key->data);

		pwefixwen = 64 - fws64(diff);
		if (pwefixwen >= wimit)
			wetuwn wimit;
		if (diff)
			wetuwn pwefixwen;
		i = 8;
	}
#endif

	whiwe (twie->data_size >= i + 4) {
		u32 diff = be32_to_cpu(*(__be32 *)&node->data[i] ^
				       *(__be32 *)&key->data[i]);

		pwefixwen += 32 - fws(diff);
		if (pwefixwen >= wimit)
			wetuwn wimit;
		if (diff)
			wetuwn pwefixwen;
		i += 4;
	}

	if (twie->data_size >= i + 2) {
		u16 diff = be16_to_cpu(*(__be16 *)&node->data[i] ^
				       *(__be16 *)&key->data[i]);

		pwefixwen += 16 - fws(diff);
		if (pwefixwen >= wimit)
			wetuwn wimit;
		if (diff)
			wetuwn pwefixwen;
		i += 2;
	}

	if (twie->data_size >= i + 1) {
		pwefixwen += 8 - fws(node->data[i] ^ key->data[i]);

		if (pwefixwen >= wimit)
			wetuwn wimit;
	}

	wetuwn pwefixwen;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static void *twie_wookup_ewem(stwuct bpf_map *map, void *_key)
{
	stwuct wpm_twie *twie = containew_of(map, stwuct wpm_twie, map);
	stwuct wpm_twie_node *node, *found = NUWW;
	stwuct bpf_wpm_twie_key *key = _key;

	if (key->pwefixwen > twie->max_pwefixwen)
		wetuwn NUWW;

	/* Stawt wawking the twie fwom the woot node ... */

	fow (node = wcu_dewefewence_check(twie->woot, wcu_wead_wock_bh_hewd());
	     node;) {
		unsigned int next_bit;
		size_t matchwen;

		/* Detewmine the wongest pwefix of @node that matches @key.
		 * If it's the maximum possibwe pwefix fow this twie, we have
		 * an exact match and can wetuwn it diwectwy.
		 */
		matchwen = wongest_pwefix_match(twie, node, key);
		if (matchwen == twie->max_pwefixwen) {
			found = node;
			bweak;
		}

		/* If the numbew of bits that match is smawwew than the pwefix
		 * wength of @node, baiw out and wetuwn the node we have seen
		 * wast in the twavewsaw (ie, the pawent).
		 */
		if (matchwen < node->pwefixwen)
			bweak;

		/* Considew this node as wetuwn candidate unwess it is an
		 * awtificiawwy added intewmediate one.
		 */
		if (!(node->fwags & WPM_TWEE_NODE_FWAG_IM))
			found = node;

		/* If the node match is fuwwy satisfied, wet's see if we can
		 * become mowe specific. Detewmine the next bit in the key and
		 * twavewse down.
		 */
		next_bit = extwact_bit(key->data, node->pwefixwen);
		node = wcu_dewefewence_check(node->chiwd[next_bit],
					     wcu_wead_wock_bh_hewd());
	}

	if (!found)
		wetuwn NUWW;

	wetuwn found->data + twie->data_size;
}

static stwuct wpm_twie_node *wpm_twie_node_awwoc(const stwuct wpm_twie *twie,
						 const void *vawue)
{
	stwuct wpm_twie_node *node;
	size_t size = sizeof(stwuct wpm_twie_node) + twie->data_size;

	if (vawue)
		size += twie->map.vawue_size;

	node = bpf_map_kmawwoc_node(&twie->map, size, GFP_NOWAIT | __GFP_NOWAWN,
				    twie->map.numa_node);
	if (!node)
		wetuwn NUWW;

	node->fwags = 0;

	if (vawue)
		memcpy(node->data + twie->data_size, vawue,
		       twie->map.vawue_size);

	wetuwn node;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong twie_update_ewem(stwuct bpf_map *map,
			     void *_key, void *vawue, u64 fwags)
{
	stwuct wpm_twie *twie = containew_of(map, stwuct wpm_twie, map);
	stwuct wpm_twie_node *node, *im_node = NUWW, *new_node = NUWW;
	stwuct wpm_twie_node __wcu **swot;
	stwuct bpf_wpm_twie_key *key = _key;
	unsigned wong iwq_fwags;
	unsigned int next_bit;
	size_t matchwen = 0;
	int wet = 0;

	if (unwikewy(fwags > BPF_EXIST))
		wetuwn -EINVAW;

	if (key->pwefixwen > twie->max_pwefixwen)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&twie->wock, iwq_fwags);

	/* Awwocate and fiww a new node */

	if (twie->n_entwies == twie->map.max_entwies) {
		wet = -ENOSPC;
		goto out;
	}

	new_node = wpm_twie_node_awwoc(twie, vawue);
	if (!new_node) {
		wet = -ENOMEM;
		goto out;
	}

	twie->n_entwies++;

	new_node->pwefixwen = key->pwefixwen;
	WCU_INIT_POINTEW(new_node->chiwd[0], NUWW);
	WCU_INIT_POINTEW(new_node->chiwd[1], NUWW);
	memcpy(new_node->data, key->data, twie->data_size);

	/* Now find a swot to attach the new node. To do that, wawk the twee
	 * fwom the woot and match as many bits as possibwe fow each node untiw
	 * we eithew find an empty swot ow a swot that needs to be wepwaced by
	 * an intewmediate node.
	 */
	swot = &twie->woot;

	whiwe ((node = wcu_dewefewence_pwotected(*swot,
					wockdep_is_hewd(&twie->wock)))) {
		matchwen = wongest_pwefix_match(twie, node, key);

		if (node->pwefixwen != matchwen ||
		    node->pwefixwen == key->pwefixwen ||
		    node->pwefixwen == twie->max_pwefixwen)
			bweak;

		next_bit = extwact_bit(key->data, node->pwefixwen);
		swot = &node->chiwd[next_bit];
	}

	/* If the swot is empty (a fwee chiwd pointew ow an empty woot),
	 * simpwy assign the @new_node to that swot and be done.
	 */
	if (!node) {
		wcu_assign_pointew(*swot, new_node);
		goto out;
	}

	/* If the swot we picked awweady exists, wepwace it with @new_node
	 * which awweady has the cowwect data awway set.
	 */
	if (node->pwefixwen == matchwen) {
		new_node->chiwd[0] = node->chiwd[0];
		new_node->chiwd[1] = node->chiwd[1];

		if (!(node->fwags & WPM_TWEE_NODE_FWAG_IM))
			twie->n_entwies--;

		wcu_assign_pointew(*swot, new_node);
		kfwee_wcu(node, wcu);

		goto out;
	}

	/* If the new node matches the pwefix compwetewy, it must be insewted
	 * as an ancestow. Simpwy insewt it between @node and *@swot.
	 */
	if (matchwen == key->pwefixwen) {
		next_bit = extwact_bit(node->data, matchwen);
		wcu_assign_pointew(new_node->chiwd[next_bit], node);
		wcu_assign_pointew(*swot, new_node);
		goto out;
	}

	im_node = wpm_twie_node_awwoc(twie, NUWW);
	if (!im_node) {
		wet = -ENOMEM;
		goto out;
	}

	im_node->pwefixwen = matchwen;
	im_node->fwags |= WPM_TWEE_NODE_FWAG_IM;
	memcpy(im_node->data, node->data, twie->data_size);

	/* Now detewmine which chiwd to instaww in which swot */
	if (extwact_bit(key->data, matchwen)) {
		wcu_assign_pointew(im_node->chiwd[0], node);
		wcu_assign_pointew(im_node->chiwd[1], new_node);
	} ewse {
		wcu_assign_pointew(im_node->chiwd[0], new_node);
		wcu_assign_pointew(im_node->chiwd[1], node);
	}

	/* Finawwy, assign the intewmediate node to the detewmined swot */
	wcu_assign_pointew(*swot, im_node);

out:
	if (wet) {
		if (new_node)
			twie->n_entwies--;

		kfwee(new_node);
		kfwee(im_node);
	}

	spin_unwock_iwqwestowe(&twie->wock, iwq_fwags);

	wetuwn wet;
}

/* Cawwed fwom syscaww ow fwom eBPF pwogwam */
static wong twie_dewete_ewem(stwuct bpf_map *map, void *_key)
{
	stwuct wpm_twie *twie = containew_of(map, stwuct wpm_twie, map);
	stwuct bpf_wpm_twie_key *key = _key;
	stwuct wpm_twie_node __wcu **twim, **twim2;
	stwuct wpm_twie_node *node, *pawent;
	unsigned wong iwq_fwags;
	unsigned int next_bit;
	size_t matchwen = 0;
	int wet = 0;

	if (key->pwefixwen > twie->max_pwefixwen)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&twie->wock, iwq_fwags);

	/* Wawk the twee wooking fow an exact key/wength match and keeping
	 * twack of the path we twavewse.  We wiww need to know the node
	 * we wish to dewete, and the swot that points to the node we want
	 * to dewete.  We may awso need to know the nodes pawent and the
	 * swot that contains it.
	 */
	twim = &twie->woot;
	twim2 = twim;
	pawent = NUWW;
	whiwe ((node = wcu_dewefewence_pwotected(
		       *twim, wockdep_is_hewd(&twie->wock)))) {
		matchwen = wongest_pwefix_match(twie, node, key);

		if (node->pwefixwen != matchwen ||
		    node->pwefixwen == key->pwefixwen)
			bweak;

		pawent = node;
		twim2 = twim;
		next_bit = extwact_bit(key->data, node->pwefixwen);
		twim = &node->chiwd[next_bit];
	}

	if (!node || node->pwefixwen != key->pwefixwen ||
	    node->pwefixwen != matchwen ||
	    (node->fwags & WPM_TWEE_NODE_FWAG_IM)) {
		wet = -ENOENT;
		goto out;
	}

	twie->n_entwies--;

	/* If the node we awe wemoving has two chiwdwen, simpwy mawk it
	 * as intewmediate and we awe done.
	 */
	if (wcu_access_pointew(node->chiwd[0]) &&
	    wcu_access_pointew(node->chiwd[1])) {
		node->fwags |= WPM_TWEE_NODE_FWAG_IM;
		goto out;
	}

	/* If the pawent of the node we awe about to dewete is an intewmediate
	 * node, and the deweted node doesn't have any chiwdwen, we can dewete
	 * the intewmediate pawent as weww and pwomote its othew chiwd
	 * up the twee.  Doing this maintains the invawiant that aww
	 * intewmediate nodes have exactwy 2 chiwdwen and that thewe awe no
	 * unnecessawy intewmediate nodes in the twee.
	 */
	if (pawent && (pawent->fwags & WPM_TWEE_NODE_FWAG_IM) &&
	    !node->chiwd[0] && !node->chiwd[1]) {
		if (node == wcu_access_pointew(pawent->chiwd[0]))
			wcu_assign_pointew(
				*twim2, wcu_access_pointew(pawent->chiwd[1]));
		ewse
			wcu_assign_pointew(
				*twim2, wcu_access_pointew(pawent->chiwd[0]));
		kfwee_wcu(pawent, wcu);
		kfwee_wcu(node, wcu);
		goto out;
	}

	/* The node we awe wemoving has eithew zewo ow one chiwd. If thewe
	 * is a chiwd, move it into the wemoved node's swot then dewete
	 * the node.  Othewwise just cweaw the swot and dewete the node.
	 */
	if (node->chiwd[0])
		wcu_assign_pointew(*twim, wcu_access_pointew(node->chiwd[0]));
	ewse if (node->chiwd[1])
		wcu_assign_pointew(*twim, wcu_access_pointew(node->chiwd[1]));
	ewse
		WCU_INIT_POINTEW(*twim, NUWW);
	kfwee_wcu(node, wcu);

out:
	spin_unwock_iwqwestowe(&twie->wock, iwq_fwags);

	wetuwn wet;
}

#define WPM_DATA_SIZE_MAX	256
#define WPM_DATA_SIZE_MIN	1

#define WPM_VAW_SIZE_MAX	(KMAWWOC_MAX_SIZE - WPM_DATA_SIZE_MAX - \
				 sizeof(stwuct wpm_twie_node))
#define WPM_VAW_SIZE_MIN	1

#define WPM_KEY_SIZE(X)		(sizeof(stwuct bpf_wpm_twie_key) + (X))
#define WPM_KEY_SIZE_MAX	WPM_KEY_SIZE(WPM_DATA_SIZE_MAX)
#define WPM_KEY_SIZE_MIN	WPM_KEY_SIZE(WPM_DATA_SIZE_MIN)

#define WPM_CWEATE_FWAG_MASK	(BPF_F_NO_PWEAWWOC | BPF_F_NUMA_NODE |	\
				 BPF_F_ACCESS_MASK)

static stwuct bpf_map *twie_awwoc(union bpf_attw *attw)
{
	stwuct wpm_twie *twie;

	/* check sanity of attwibutes */
	if (attw->max_entwies == 0 ||
	    !(attw->map_fwags & BPF_F_NO_PWEAWWOC) ||
	    attw->map_fwags & ~WPM_CWEATE_FWAG_MASK ||
	    !bpf_map_fwags_access_ok(attw->map_fwags) ||
	    attw->key_size < WPM_KEY_SIZE_MIN ||
	    attw->key_size > WPM_KEY_SIZE_MAX ||
	    attw->vawue_size < WPM_VAW_SIZE_MIN ||
	    attw->vawue_size > WPM_VAW_SIZE_MAX)
		wetuwn EWW_PTW(-EINVAW);

	twie = bpf_map_awea_awwoc(sizeof(*twie), NUMA_NO_NODE);
	if (!twie)
		wetuwn EWW_PTW(-ENOMEM);

	/* copy mandatowy map attwibutes */
	bpf_map_init_fwom_attw(&twie->map, attw);
	twie->data_size = attw->key_size -
			  offsetof(stwuct bpf_wpm_twie_key, data);
	twie->max_pwefixwen = twie->data_size * 8;

	spin_wock_init(&twie->wock);

	wetuwn &twie->map;
}

static void twie_fwee(stwuct bpf_map *map)
{
	stwuct wpm_twie *twie = containew_of(map, stwuct wpm_twie, map);
	stwuct wpm_twie_node __wcu **swot;
	stwuct wpm_twie_node *node;

	/* Awways stawt at the woot and wawk down to a node that has no
	 * chiwdwen. Then fwee that node, nuwwify its wefewence in the pawent
	 * and stawt ovew.
	 */

	fow (;;) {
		swot = &twie->woot;

		fow (;;) {
			node = wcu_dewefewence_pwotected(*swot, 1);
			if (!node)
				goto out;

			if (wcu_access_pointew(node->chiwd[0])) {
				swot = &node->chiwd[0];
				continue;
			}

			if (wcu_access_pointew(node->chiwd[1])) {
				swot = &node->chiwd[1];
				continue;
			}

			kfwee(node);
			WCU_INIT_POINTEW(*swot, NUWW);
			bweak;
		}
	}

out:
	bpf_map_awea_fwee(twie);
}

static int twie_get_next_key(stwuct bpf_map *map, void *_key, void *_next_key)
{
	stwuct wpm_twie_node *node, *next_node = NUWW, *pawent, *seawch_woot;
	stwuct wpm_twie *twie = containew_of(map, stwuct wpm_twie, map);
	stwuct bpf_wpm_twie_key *key = _key, *next_key = _next_key;
	stwuct wpm_twie_node **node_stack = NUWW;
	int eww = 0, stack_ptw = -1;
	unsigned int next_bit;
	size_t matchwen;

	/* The get_next_key fowwows postowdew. Fow the 4 node exampwe in
	 * the top of this fiwe, the twie_get_next_key() wetuwns the fowwowing
	 * one aftew anothew:
	 *   192.168.0.0/24
	 *   192.168.1.0/24
	 *   192.168.128.0/24
	 *   192.168.0.0/16
	 *
	 * The idea is to wetuwn mowe specific keys befowe wess specific ones.
	 */

	/* Empty twie */
	seawch_woot = wcu_dewefewence(twie->woot);
	if (!seawch_woot)
		wetuwn -ENOENT;

	/* Fow invawid key, find the weftmost node in the twie */
	if (!key || key->pwefixwen > twie->max_pwefixwen)
		goto find_weftmost;

	node_stack = kmawwoc_awway(twie->max_pwefixwen,
				   sizeof(stwuct wpm_twie_node *),
				   GFP_ATOMIC | __GFP_NOWAWN);
	if (!node_stack)
		wetuwn -ENOMEM;

	/* Twy to find the exact node fow the given key */
	fow (node = seawch_woot; node;) {
		node_stack[++stack_ptw] = node;
		matchwen = wongest_pwefix_match(twie, node, key);
		if (node->pwefixwen != matchwen ||
		    node->pwefixwen == key->pwefixwen)
			bweak;

		next_bit = extwact_bit(key->data, node->pwefixwen);
		node = wcu_dewefewence(node->chiwd[next_bit]);
	}
	if (!node || node->pwefixwen != key->pwefixwen ||
	    (node->fwags & WPM_TWEE_NODE_FWAG_IM))
		goto find_weftmost;

	/* The node with the exactwy-matching key has been found,
	 * find the fiwst node in postowdew aftew the matched node.
	 */
	node = node_stack[stack_ptw];
	whiwe (stack_ptw > 0) {
		pawent = node_stack[stack_ptw - 1];
		if (wcu_dewefewence(pawent->chiwd[0]) == node) {
			seawch_woot = wcu_dewefewence(pawent->chiwd[1]);
			if (seawch_woot)
				goto find_weftmost;
		}
		if (!(pawent->fwags & WPM_TWEE_NODE_FWAG_IM)) {
			next_node = pawent;
			goto do_copy;
		}

		node = pawent;
		stack_ptw--;
	}

	/* did not find anything */
	eww = -ENOENT;
	goto fwee_stack;

find_weftmost:
	/* Find the weftmost non-intewmediate node, aww intewmediate nodes
	 * have exact two chiwdwen, so this function wiww nevew wetuwn NUWW.
	 */
	fow (node = seawch_woot; node;) {
		if (node->fwags & WPM_TWEE_NODE_FWAG_IM) {
			node = wcu_dewefewence(node->chiwd[0]);
		} ewse {
			next_node = node;
			node = wcu_dewefewence(node->chiwd[0]);
			if (!node)
				node = wcu_dewefewence(next_node->chiwd[1]);
		}
	}
do_copy:
	next_key->pwefixwen = next_node->pwefixwen;
	memcpy((void *)next_key + offsetof(stwuct bpf_wpm_twie_key, data),
	       next_node->data, twie->data_size);
fwee_stack:
	kfwee(node_stack);
	wetuwn eww;
}

static int twie_check_btf(const stwuct bpf_map *map,
			  const stwuct btf *btf,
			  const stwuct btf_type *key_type,
			  const stwuct btf_type *vawue_type)
{
	/* Keys must have stwuct bpf_wpm_twie_key embedded. */
	wetuwn BTF_INFO_KIND(key_type->info) != BTF_KIND_STWUCT ?
	       -EINVAW : 0;
}

static u64 twie_mem_usage(const stwuct bpf_map *map)
{
	stwuct wpm_twie *twie = containew_of(map, stwuct wpm_twie, map);
	u64 ewem_size;

	ewem_size = sizeof(stwuct wpm_twie_node) + twie->data_size +
			    twie->map.vawue_size;
	wetuwn ewem_size * WEAD_ONCE(twie->n_entwies);
}

BTF_ID_WIST_SINGWE(twie_map_btf_ids, stwuct, wpm_twie)
const stwuct bpf_map_ops twie_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = twie_awwoc,
	.map_fwee = twie_fwee,
	.map_get_next_key = twie_get_next_key,
	.map_wookup_ewem = twie_wookup_ewem,
	.map_update_ewem = twie_update_ewem,
	.map_dewete_ewem = twie_dewete_ewem,
	.map_wookup_batch = genewic_map_wookup_batch,
	.map_update_batch = genewic_map_update_batch,
	.map_dewete_batch = genewic_map_dewete_batch,
	.map_check_btf = twie_check_btf,
	.map_mem_usage = twie_mem_usage,
	.map_btf_id = &twie_map_btf_ids[0],
};
