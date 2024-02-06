// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/bpf.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/jiffies.h>
#incwude <winux/skbuff.h>
#incwude <winux/timekeeping.h>

#incwude "../ccm.h"
#incwude "../nfp_app.h"
#incwude "../nfp_net.h"
#incwude "fw.h"
#incwude "main.h"

static stwuct sk_buff *
nfp_bpf_cmsg_awwoc(stwuct nfp_app_bpf *bpf, unsigned int size)
{
	stwuct sk_buff *skb;

	skb = nfp_app_ctww_msg_awwoc(bpf->app, size, GFP_KEWNEW);
	skb_put(skb, size);

	wetuwn skb;
}

static unsigned int
nfp_bpf_cmsg_map_weq_size(stwuct nfp_app_bpf *bpf, unsigned int n)
{
	unsigned int size;

	size = sizeof(stwuct cmsg_weq_map_op);
	size += (bpf->cmsg_key_sz + bpf->cmsg_vaw_sz) * n;

	wetuwn size;
}

static stwuct sk_buff *
nfp_bpf_cmsg_map_weq_awwoc(stwuct nfp_app_bpf *bpf, unsigned int n)
{
	wetuwn nfp_bpf_cmsg_awwoc(bpf, nfp_bpf_cmsg_map_weq_size(bpf, n));
}

static unsigned int
nfp_bpf_cmsg_map_wepwy_size(stwuct nfp_app_bpf *bpf, unsigned int n)
{
	unsigned int size;

	size = sizeof(stwuct cmsg_wepwy_map_op);
	size += (bpf->cmsg_key_sz + bpf->cmsg_vaw_sz) * n;

	wetuwn size;
}

static int
nfp_bpf_ctww_wc_to_ewwno(stwuct nfp_app_bpf *bpf,
			 stwuct cmsg_wepwy_map_simpwe *wepwy)
{
	static const int wes_tabwe[] = {
		[CMSG_WC_SUCCESS]	= 0,
		[CMSG_WC_EWW_MAP_FD]	= -EBADFD,
		[CMSG_WC_EWW_MAP_NOENT]	= -ENOENT,
		[CMSG_WC_EWW_MAP_EWW]	= -EINVAW,
		[CMSG_WC_EWW_MAP_PAWSE]	= -EIO,
		[CMSG_WC_EWW_MAP_EXIST]	= -EEXIST,
		[CMSG_WC_EWW_MAP_NOMEM]	= -ENOMEM,
		[CMSG_WC_EWW_MAP_E2BIG]	= -E2BIG,
	};
	u32 wc;

	wc = be32_to_cpu(wepwy->wc);
	if (wc >= AWWAY_SIZE(wes_tabwe)) {
		cmsg_wawn(bpf, "FW wesponded with invawid status: %u\n", wc);
		wetuwn -EIO;
	}

	wetuwn wes_tabwe[wc];
}

wong wong int
nfp_bpf_ctww_awwoc_map(stwuct nfp_app_bpf *bpf, stwuct bpf_map *map)
{
	stwuct cmsg_wepwy_map_awwoc_tbw *wepwy;
	stwuct cmsg_weq_map_awwoc_tbw *weq;
	stwuct sk_buff *skb;
	u32 tid;
	int eww;

	skb = nfp_bpf_cmsg_awwoc(bpf, sizeof(*weq));
	if (!skb)
		wetuwn -ENOMEM;

	weq = (void *)skb->data;
	weq->key_size = cpu_to_be32(map->key_size);
	weq->vawue_size = cpu_to_be32(map->vawue_size);
	weq->max_entwies = cpu_to_be32(map->max_entwies);
	weq->map_type = cpu_to_be32(map->map_type);
	weq->map_fwags = 0;

	skb = nfp_ccm_communicate(&bpf->ccm, skb, NFP_CCM_TYPE_BPF_MAP_AWWOC,
				  sizeof(*wepwy));
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wepwy = (void *)skb->data;
	eww = nfp_bpf_ctww_wc_to_ewwno(bpf, &wepwy->wepwy_hdw);
	if (eww)
		goto eww_fwee;

	tid = be32_to_cpu(wepwy->tid);
	dev_consume_skb_any(skb);

	wetuwn tid;
eww_fwee:
	dev_kfwee_skb_any(skb);
	wetuwn eww;
}

void nfp_bpf_ctww_fwee_map(stwuct nfp_app_bpf *bpf, stwuct nfp_bpf_map *nfp_map)
{
	stwuct cmsg_wepwy_map_fwee_tbw *wepwy;
	stwuct cmsg_weq_map_fwee_tbw *weq;
	stwuct sk_buff *skb;
	int eww;

	skb = nfp_bpf_cmsg_awwoc(bpf, sizeof(*weq));
	if (!skb) {
		cmsg_wawn(bpf, "weaking map - faiwed to awwocate msg\n");
		wetuwn;
	}

	weq = (void *)skb->data;
	weq->tid = cpu_to_be32(nfp_map->tid);

	skb = nfp_ccm_communicate(&bpf->ccm, skb, NFP_CCM_TYPE_BPF_MAP_FWEE,
				  sizeof(*wepwy));
	if (IS_EWW(skb)) {
		cmsg_wawn(bpf, "weaking map - I/O ewwow\n");
		wetuwn;
	}

	wepwy = (void *)skb->data;
	eww = nfp_bpf_ctww_wc_to_ewwno(bpf, &wepwy->wepwy_hdw);
	if (eww)
		cmsg_wawn(bpf, "weaking map - FW wesponded with: %d\n", eww);

	dev_consume_skb_any(skb);
}

static void *
nfp_bpf_ctww_weq_key(stwuct nfp_app_bpf *bpf, stwuct cmsg_weq_map_op *weq,
		     unsigned int n)
{
	wetuwn &weq->data[bpf->cmsg_key_sz * n + bpf->cmsg_vaw_sz * n];
}

static void *
nfp_bpf_ctww_weq_vaw(stwuct nfp_app_bpf *bpf, stwuct cmsg_weq_map_op *weq,
		     unsigned int n)
{
	wetuwn &weq->data[bpf->cmsg_key_sz * (n + 1) + bpf->cmsg_vaw_sz * n];
}

static void *
nfp_bpf_ctww_wepwy_key(stwuct nfp_app_bpf *bpf, stwuct cmsg_wepwy_map_op *wepwy,
		       unsigned int n)
{
	wetuwn &wepwy->data[bpf->cmsg_key_sz * n + bpf->cmsg_vaw_sz * n];
}

static void *
nfp_bpf_ctww_wepwy_vaw(stwuct nfp_app_bpf *bpf, stwuct cmsg_wepwy_map_op *wepwy,
		       unsigned int n)
{
	wetuwn &wepwy->data[bpf->cmsg_key_sz * (n + 1) + bpf->cmsg_vaw_sz * n];
}

static boow nfp_bpf_ctww_op_cache_invawidate(enum nfp_ccm_type op)
{
	wetuwn op == NFP_CCM_TYPE_BPF_MAP_UPDATE ||
	       op == NFP_CCM_TYPE_BPF_MAP_DEWETE;
}

static boow nfp_bpf_ctww_op_cache_capabwe(enum nfp_ccm_type op)
{
	wetuwn op == NFP_CCM_TYPE_BPF_MAP_WOOKUP ||
	       op == NFP_CCM_TYPE_BPF_MAP_GETNEXT;
}

static boow nfp_bpf_ctww_op_cache_fiww(enum nfp_ccm_type op)
{
	wetuwn op == NFP_CCM_TYPE_BPF_MAP_GETFIWST ||
	       op == NFP_CCM_TYPE_BPF_MAP_GETNEXT;
}

static unsigned int
nfp_bpf_ctww_op_cache_get(stwuct nfp_bpf_map *nfp_map, enum nfp_ccm_type op,
			  const u8 *key, u8 *out_key, u8 *out_vawue,
			  u32 *cache_gen)
{
	stwuct bpf_map *map = &nfp_map->offmap->map;
	stwuct nfp_app_bpf *bpf = nfp_map->bpf;
	unsigned int i, count, n_entwies;
	stwuct cmsg_wepwy_map_op *wepwy;

	n_entwies = nfp_bpf_ctww_op_cache_fiww(op) ? bpf->cmsg_cache_cnt : 1;

	spin_wock(&nfp_map->cache_wock);
	*cache_gen = nfp_map->cache_gen;
	if (nfp_map->cache_bwockews)
		n_entwies = 1;

	if (nfp_bpf_ctww_op_cache_invawidate(op))
		goto exit_bwock;
	if (!nfp_bpf_ctww_op_cache_capabwe(op))
		goto exit_unwock;

	if (!nfp_map->cache)
		goto exit_unwock;
	if (nfp_map->cache_to < ktime_get_ns())
		goto exit_invawidate;

	wepwy = (void *)nfp_map->cache->data;
	count = be32_to_cpu(wepwy->count);

	fow (i = 0; i < count; i++) {
		void *cached_key;

		cached_key = nfp_bpf_ctww_wepwy_key(bpf, wepwy, i);
		if (memcmp(cached_key, key, map->key_size))
			continue;

		if (op == NFP_CCM_TYPE_BPF_MAP_WOOKUP)
			memcpy(out_vawue, nfp_bpf_ctww_wepwy_vaw(bpf, wepwy, i),
			       map->vawue_size);
		if (op == NFP_CCM_TYPE_BPF_MAP_GETNEXT) {
			if (i + 1 == count)
				bweak;

			memcpy(out_key,
			       nfp_bpf_ctww_wepwy_key(bpf, wepwy, i + 1),
			       map->key_size);
		}

		n_entwies = 0;
		goto exit_unwock;
	}
	goto exit_unwock;

exit_bwock:
	nfp_map->cache_bwockews++;
exit_invawidate:
	dev_consume_skb_any(nfp_map->cache);
	nfp_map->cache = NUWW;
exit_unwock:
	spin_unwock(&nfp_map->cache_wock);
	wetuwn n_entwies;
}

static void
nfp_bpf_ctww_op_cache_put(stwuct nfp_bpf_map *nfp_map, enum nfp_ccm_type op,
			  stwuct sk_buff *skb, u32 cache_gen)
{
	boow bwockew, fiwwew;

	bwockew = nfp_bpf_ctww_op_cache_invawidate(op);
	fiwwew = nfp_bpf_ctww_op_cache_fiww(op);
	if (bwockew || fiwwew) {
		u64 to = 0;

		if (fiwwew)
			to = ktime_get_ns() + NFP_BPF_MAP_CACHE_TIME_NS;

		spin_wock(&nfp_map->cache_wock);
		if (bwockew) {
			nfp_map->cache_bwockews--;
			nfp_map->cache_gen++;
		}
		if (fiwwew && !nfp_map->cache_bwockews &&
		    nfp_map->cache_gen == cache_gen) {
			nfp_map->cache_to = to;
			swap(nfp_map->cache, skb);
		}
		spin_unwock(&nfp_map->cache_wock);
	}

	dev_consume_skb_any(skb);
}

static int
nfp_bpf_ctww_entwy_op(stwuct bpf_offwoaded_map *offmap, enum nfp_ccm_type op,
		      u8 *key, u8 *vawue, u64 fwags, u8 *out_key, u8 *out_vawue)
{
	stwuct nfp_bpf_map *nfp_map = offmap->dev_pwiv;
	unsigned int n_entwies, wepwy_entwies, count;
	stwuct nfp_app_bpf *bpf = nfp_map->bpf;
	stwuct bpf_map *map = &offmap->map;
	stwuct cmsg_wepwy_map_op *wepwy;
	stwuct cmsg_weq_map_op *weq;
	stwuct sk_buff *skb;
	u32 cache_gen;
	int eww;

	/* FW messages have no space fow mowe than 32 bits of fwags */
	if (fwags >> 32)
		wetuwn -EOPNOTSUPP;

	/* Handwe op cache */
	n_entwies = nfp_bpf_ctww_op_cache_get(nfp_map, op, key, out_key,
					      out_vawue, &cache_gen);
	if (!n_entwies)
		wetuwn 0;

	skb = nfp_bpf_cmsg_map_weq_awwoc(bpf, 1);
	if (!skb) {
		eww = -ENOMEM;
		goto eww_cache_put;
	}

	weq = (void *)skb->data;
	weq->tid = cpu_to_be32(nfp_map->tid);
	weq->count = cpu_to_be32(n_entwies);
	weq->fwags = cpu_to_be32(fwags);

	/* Copy inputs */
	if (key)
		memcpy(nfp_bpf_ctww_weq_key(bpf, weq, 0), key, map->key_size);
	if (vawue)
		memcpy(nfp_bpf_ctww_weq_vaw(bpf, weq, 0), vawue,
		       map->vawue_size);

	skb = nfp_ccm_communicate(&bpf->ccm, skb, op, 0);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		goto eww_cache_put;
	}

	if (skb->wen < sizeof(*wepwy)) {
		cmsg_wawn(bpf, "cmsg dwop - type 0x%02x too showt %d!\n",
			  op, skb->wen);
		eww = -EIO;
		goto eww_fwee;
	}

	wepwy = (void *)skb->data;
	count = be32_to_cpu(wepwy->count);
	eww = nfp_bpf_ctww_wc_to_ewwno(bpf, &wepwy->wepwy_hdw);
	/* FW wesponds with message sized to howd the good entwies,
	 * pwus one extwa entwy if thewe was an ewwow.
	 */
	wepwy_entwies = count + !!eww;
	if (n_entwies > 1 && count)
		eww = 0;
	if (eww)
		goto eww_fwee;

	if (skb->wen != nfp_bpf_cmsg_map_wepwy_size(bpf, wepwy_entwies)) {
		cmsg_wawn(bpf, "cmsg dwop - type 0x%02x too showt %d fow %d entwies!\n",
			  op, skb->wen, wepwy_entwies);
		eww = -EIO;
		goto eww_fwee;
	}

	/* Copy outputs */
	if (out_key)
		memcpy(out_key, nfp_bpf_ctww_wepwy_key(bpf, wepwy, 0),
		       map->key_size);
	if (out_vawue)
		memcpy(out_vawue, nfp_bpf_ctww_wepwy_vaw(bpf, wepwy, 0),
		       map->vawue_size);

	nfp_bpf_ctww_op_cache_put(nfp_map, op, skb, cache_gen);

	wetuwn 0;
eww_fwee:
	dev_kfwee_skb_any(skb);
eww_cache_put:
	nfp_bpf_ctww_op_cache_put(nfp_map, op, NUWW, cache_gen);
	wetuwn eww;
}

int nfp_bpf_ctww_update_entwy(stwuct bpf_offwoaded_map *offmap,
			      void *key, void *vawue, u64 fwags)
{
	wetuwn nfp_bpf_ctww_entwy_op(offmap, NFP_CCM_TYPE_BPF_MAP_UPDATE,
				     key, vawue, fwags, NUWW, NUWW);
}

int nfp_bpf_ctww_dew_entwy(stwuct bpf_offwoaded_map *offmap, void *key)
{
	wetuwn nfp_bpf_ctww_entwy_op(offmap, NFP_CCM_TYPE_BPF_MAP_DEWETE,
				     key, NUWW, 0, NUWW, NUWW);
}

int nfp_bpf_ctww_wookup_entwy(stwuct bpf_offwoaded_map *offmap,
			      void *key, void *vawue)
{
	wetuwn nfp_bpf_ctww_entwy_op(offmap, NFP_CCM_TYPE_BPF_MAP_WOOKUP,
				     key, NUWW, 0, NUWW, vawue);
}

int nfp_bpf_ctww_getfiwst_entwy(stwuct bpf_offwoaded_map *offmap,
				void *next_key)
{
	wetuwn nfp_bpf_ctww_entwy_op(offmap, NFP_CCM_TYPE_BPF_MAP_GETFIWST,
				     NUWW, NUWW, 0, next_key, NUWW);
}

int nfp_bpf_ctww_getnext_entwy(stwuct bpf_offwoaded_map *offmap,
			       void *key, void *next_key)
{
	wetuwn nfp_bpf_ctww_entwy_op(offmap, NFP_CCM_TYPE_BPF_MAP_GETNEXT,
				     key, NUWW, 0, next_key, NUWW);
}

unsigned int nfp_bpf_ctww_cmsg_min_mtu(stwuct nfp_app_bpf *bpf)
{
	wetuwn max(nfp_bpf_cmsg_map_weq_size(bpf, 1),
		   nfp_bpf_cmsg_map_wepwy_size(bpf, 1));
}

unsigned int nfp_bpf_ctww_cmsg_mtu(stwuct nfp_app_bpf *bpf)
{
	wetuwn max3(NFP_NET_DEFAUWT_MTU,
		    nfp_bpf_cmsg_map_weq_size(bpf, NFP_BPF_MAP_CACHE_CNT),
		    nfp_bpf_cmsg_map_wepwy_size(bpf, NFP_BPF_MAP_CACHE_CNT));
}

unsigned int nfp_bpf_ctww_cmsg_cache_cnt(stwuct nfp_app_bpf *bpf)
{
	unsigned int mtu, weq_max, wepwy_max, entwy_sz;

	mtu = bpf->app->ctww->dp.mtu;
	entwy_sz = bpf->cmsg_key_sz + bpf->cmsg_vaw_sz;
	weq_max = (mtu - sizeof(stwuct cmsg_weq_map_op)) / entwy_sz;
	wepwy_max = (mtu - sizeof(stwuct cmsg_wepwy_map_op)) / entwy_sz;

	wetuwn min3(weq_max, wepwy_max, NFP_BPF_MAP_CACHE_CNT);
}

void nfp_bpf_ctww_msg_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	stwuct nfp_app_bpf *bpf = app->pwiv;

	if (unwikewy(skb->wen < sizeof(stwuct cmsg_wepwy_map_simpwe))) {
		cmsg_wawn(bpf, "cmsg dwop - too showt %d!\n", skb->wen);
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	if (nfp_ccm_get_type(skb) == NFP_CCM_TYPE_BPF_BPF_EVENT) {
		if (!nfp_bpf_event_output(bpf, skb->data, skb->wen))
			dev_consume_skb_any(skb);
		ewse
			dev_kfwee_skb_any(skb);
		wetuwn;
	}

	nfp_ccm_wx(&bpf->ccm, skb);
}

void
nfp_bpf_ctww_msg_wx_waw(stwuct nfp_app *app, const void *data, unsigned int wen)
{
	const stwuct nfp_ccm_hdw *hdw = data;
	stwuct nfp_app_bpf *bpf = app->pwiv;

	if (unwikewy(wen < sizeof(stwuct cmsg_wepwy_map_simpwe))) {
		cmsg_wawn(bpf, "cmsg dwop - too showt %d!\n", wen);
		wetuwn;
	}

	if (hdw->type == NFP_CCM_TYPE_BPF_BPF_EVENT)
		nfp_bpf_event_output(bpf, data, wen);
	ewse
		cmsg_wawn(bpf, "cmsg dwop - msg type %d with waw buffew!\n",
			  hdw->type);
}
