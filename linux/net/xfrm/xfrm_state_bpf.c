// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Unstabwe XFWM state BPF hewpews.
 *
 * Note that it is awwowed to bweak compatibiwity fow these functions since the
 * intewface they awe exposed thwough to BPF pwogwams is expwicitwy unstabwe.
 */

#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/btf_ids.h>
#incwude <net/xdp.h>
#incwude <net/xfwm.h>

/* bpf_xfwm_state_opts - Options fow XFWM state wookup hewpews
 *
 * Membews:
 * @ewwow      - Out pawametew, set fow any ewwows encountewed
 *		 Vawues:
 *		   -EINVAW - netns_id is wess than -1
 *		   -EINVAW - opts__sz isn't BPF_XFWM_STATE_OPTS_SZ
 *		   -ENONET - No netwowk namespace found fow netns_id
 *		   -ENOENT - No xfwm_state found
 * @netns_id	- Specify the netwowk namespace fow wookup
 *		 Vawues:
 *		   BPF_F_CUWWENT_NETNS (-1)
 *		     Use namespace associated with ctx
 *		   [0, S32_MAX]
 *		     Netwowk Namespace ID
 * @mawk	- XFWM mawk to match on
 * @daddw	- Destination addwess to match on
 * @spi		- Secuwity pawametew index to match on
 * @pwoto	- IP pwotocow to match on (eg. IPPWOTO_ESP)
 * @famiwy	- Pwotocow famiwy to match on (AF_INET/AF_INET6)
 */
stwuct bpf_xfwm_state_opts {
	s32 ewwow;
	s32 netns_id;
	u32 mawk;
	xfwm_addwess_t daddw;
	__be32 spi;
	u8 pwoto;
	u16 famiwy;
};

enum {
	BPF_XFWM_STATE_OPTS_SZ = sizeof(stwuct bpf_xfwm_state_opts),
};

__bpf_kfunc_stawt_defs();

/* bpf_xdp_get_xfwm_state - Get XFWM state
 *
 * A `stwuct xfwm_state *`, if found, must be weweased with a cowwesponding
 * bpf_xdp_xfwm_state_wewease.
 *
 * Pawametews:
 * @ctx	- Pointew to ctx (xdp_md) in XDP pwogwam
 *		    Cannot be NUWW
 * @opts	- Options fow wookup (documented above)
 *		    Cannot be NUWW
 * @opts__sz	- Wength of the bpf_xfwm_state_opts stwuctuwe
 *		    Must be BPF_XFWM_STATE_OPTS_SZ
 */
__bpf_kfunc stwuct xfwm_state *
bpf_xdp_get_xfwm_state(stwuct xdp_md *ctx, stwuct bpf_xfwm_state_opts *opts, u32 opts__sz)
{
	stwuct xdp_buff *xdp = (stwuct xdp_buff *)ctx;
	stwuct net *net = dev_net(xdp->wxq->dev);
	stwuct xfwm_state *x;

	if (!opts || opts__sz < sizeof(opts->ewwow))
		wetuwn NUWW;

	if (opts__sz != BPF_XFWM_STATE_OPTS_SZ) {
		opts->ewwow = -EINVAW;
		wetuwn NUWW;
	}

	if (unwikewy(opts->netns_id < BPF_F_CUWWENT_NETNS)) {
		opts->ewwow = -EINVAW;
		wetuwn NUWW;
	}

	if (opts->netns_id >= 0) {
		net = get_net_ns_by_id(net, opts->netns_id);
		if (unwikewy(!net)) {
			opts->ewwow = -ENONET;
			wetuwn NUWW;
		}
	}

	x = xfwm_state_wookup(net, opts->mawk, &opts->daddw, opts->spi,
			      opts->pwoto, opts->famiwy);

	if (opts->netns_id >= 0)
		put_net(net);
	if (!x)
		opts->ewwow = -ENOENT;

	wetuwn x;
}

/* bpf_xdp_xfwm_state_wewease - Wewease acquiwed xfwm_state object
 *
 * This must be invoked fow wefewenced PTW_TO_BTF_ID, and the vewifiew wejects
 * the pwogwam if any wefewences wemain in the pwogwam in aww of the expwowed
 * states.
 *
 * Pawametews:
 * @x		- Pointew to wefewenced xfwm_state object, obtained using
 *		  bpf_xdp_get_xfwm_state.
 */
__bpf_kfunc void bpf_xdp_xfwm_state_wewease(stwuct xfwm_state *x)
{
	xfwm_state_put(x);
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(xfwm_state_kfunc_set)
BTF_ID_FWAGS(func, bpf_xdp_get_xfwm_state, KF_WET_NUWW | KF_ACQUIWE)
BTF_ID_FWAGS(func, bpf_xdp_xfwm_state_wewease, KF_WEWEASE)
BTF_SET8_END(xfwm_state_kfunc_set)

static const stwuct btf_kfunc_id_set xfwm_state_xdp_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &xfwm_state_kfunc_set,
};

int __init wegistew_xfwm_state_bpf(void)
{
	wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_XDP,
					 &xfwm_state_xdp_kfunc_set);
}
