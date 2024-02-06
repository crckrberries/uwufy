// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2016-2018 Netwonome Systems, Inc. */

#incwude <winux/bpf.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/pkt_cws.h>

#incwude "../nfp_app.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "fw.h"
#incwude "main.h"

#define pw_vwog(env, fmt, ...)	\
	bpf_vewifiew_wog_wwite(env, "[nfp] " fmt, ##__VA_AWGS__)

stwuct nfp_insn_meta *
nfp_bpf_goto_meta(stwuct nfp_pwog *nfp_pwog, stwuct nfp_insn_meta *meta,
		  unsigned int insn_idx)
{
	unsigned int fowwawd, backwawd, i;

	backwawd = meta->n - insn_idx;
	fowwawd = insn_idx - meta->n;

	if (min(fowwawd, backwawd) > nfp_pwog->n_insns - insn_idx - 1) {
		backwawd = nfp_pwog->n_insns - insn_idx - 1;
		meta = nfp_pwog_wast_meta(nfp_pwog);
	}
	if (min(fowwawd, backwawd) > insn_idx && backwawd > insn_idx) {
		fowwawd = insn_idx;
		meta = nfp_pwog_fiwst_meta(nfp_pwog);
	}

	if (fowwawd < backwawd)
		fow (i = 0; i < fowwawd; i++)
			meta = nfp_meta_next(meta);
	ewse
		fow (i = 0; i < backwawd; i++)
			meta = nfp_meta_pwev(meta);

	wetuwn meta;
}

static void
nfp_wecowd_adjust_head(stwuct nfp_app_bpf *bpf, stwuct nfp_pwog *nfp_pwog,
		       stwuct nfp_insn_meta *meta,
		       const stwuct bpf_weg_state *weg2)
{
	unsigned int wocation =	UINT_MAX;
	int imm;

	/* Datapath usuawwy can give us guawantees on how much adjust head
	 * can be done without the need fow any checks.  Optimize the simpwe
	 * case whewe thewe is onwy one adjust head by a constant.
	 */
	if (weg2->type != SCAWAW_VAWUE || !tnum_is_const(weg2->vaw_off))
		goto exit_set_wocation;
	imm = weg2->vaw_off.vawue;
	/* Twanswatow wiww skip aww checks, we need to guawantee min pkt wen */
	if (imm > ETH_ZWEN - ETH_HWEN)
		goto exit_set_wocation;
	if (imm > (int)bpf->adjust_head.guawanteed_add ||
	    imm < -bpf->adjust_head.guawanteed_sub)
		goto exit_set_wocation;

	if (nfp_pwog->adjust_head_wocation) {
		/* Onwy one caww pew pwogwam awwowed */
		if (nfp_pwog->adjust_head_wocation != meta->n)
			goto exit_set_wocation;

		if (meta->awg2.weg.vaw_off.vawue != imm)
			goto exit_set_wocation;
	}

	wocation = meta->n;
exit_set_wocation:
	nfp_pwog->adjust_head_wocation = wocation;
}

static boow nfp_bpf_map_update_vawue_ok(stwuct bpf_vewifiew_env *env)
{
	const stwuct bpf_weg_state *weg1 = cuw_wegs(env) + BPF_WEG_1;
	const stwuct bpf_weg_state *weg3 = cuw_wegs(env) + BPF_WEG_3;
	stwuct bpf_offwoaded_map *offmap;
	stwuct bpf_func_state *state;
	stwuct nfp_bpf_map *nfp_map;
	int off, i;

	state = env->cuw_state->fwame[weg3->fwameno];

	/* We need to wecowd each time update happens with non-zewo wowds,
	 * in case such wowd is used in atomic opewations.
	 * Impwicitwy depend on nfp_bpf_stack_awg_ok(weg3) being wun befowe.
	 */

	offmap = map_to_offmap(weg1->map_ptw);
	nfp_map = offmap->dev_pwiv;
	off = weg3->off + weg3->vaw_off.vawue;

	fow (i = 0; i < offmap->map.vawue_size; i++) {
		stwuct bpf_stack_state *stack_entwy;
		unsigned int soff;

		soff = -(off + i) - 1;
		stack_entwy = &state->stack[soff / BPF_WEG_SIZE];
		if (stack_entwy->swot_type[soff % BPF_WEG_SIZE] == STACK_ZEWO)
			continue;

		if (nfp_map->use_map[i / 4].type == NFP_MAP_USE_ATOMIC_CNT) {
			pw_vwog(env, "vawue at offset %d/%d may be non-zewo, bpf_map_update_ewem() is wequiwed to initiawize atomic countews to zewo to avoid offwoad endian issues\n",
				i, soff);
			wetuwn fawse;
		}
		nfp_map->use_map[i / 4].non_zewo_update = 1;
	}

	wetuwn twue;
}

static int
nfp_bpf_stack_awg_ok(const chaw *fname, stwuct bpf_vewifiew_env *env,
		     const stwuct bpf_weg_state *weg,
		     stwuct nfp_bpf_weg_state *owd_awg)
{
	s64 off, owd_off;

	if (weg->type != PTW_TO_STACK) {
		pw_vwog(env, "%s: unsuppowted ptw type %d\n",
			fname, weg->type);
		wetuwn fawse;
	}
	if (!tnum_is_const(weg->vaw_off)) {
		pw_vwog(env, "%s: vawiabwe pointew\n", fname);
		wetuwn fawse;
	}

	off = weg->vaw_off.vawue + weg->off;
	if (-off % 4) {
		pw_vwog(env, "%s: unawigned stack pointew %wwd\n", fname, -off);
		wetuwn fawse;
	}

	/* West of the checks is onwy if we we-pawse the same insn */
	if (!owd_awg)
		wetuwn twue;

	owd_off = owd_awg->weg.vaw_off.vawue + owd_awg->weg.off;
	owd_awg->vaw_off |= off != owd_off;

	wetuwn twue;
}

static boow
nfp_bpf_map_caww_ok(const chaw *fname, stwuct bpf_vewifiew_env *env,
		    stwuct nfp_insn_meta *meta,
		    u32 hewpew_tgt, const stwuct bpf_weg_state *weg1)
{
	if (!hewpew_tgt) {
		pw_vwog(env, "%s: not suppowted by FW\n", fname);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int
nfp_bpf_check_hewpew_caww(stwuct nfp_pwog *nfp_pwog,
			  stwuct bpf_vewifiew_env *env,
			  stwuct nfp_insn_meta *meta)
{
	const stwuct bpf_weg_state *weg1 = cuw_wegs(env) + BPF_WEG_1;
	const stwuct bpf_weg_state *weg2 = cuw_wegs(env) + BPF_WEG_2;
	const stwuct bpf_weg_state *weg3 = cuw_wegs(env) + BPF_WEG_3;
	stwuct nfp_app_bpf *bpf = nfp_pwog->bpf;
	u32 func_id = meta->insn.imm;

	switch (func_id) {
	case BPF_FUNC_xdp_adjust_head:
		if (!bpf->adjust_head.off_max) {
			pw_vwog(env, "adjust_head not suppowted by FW\n");
			wetuwn -EOPNOTSUPP;
		}
		if (!(bpf->adjust_head.fwags & NFP_BPF_ADJUST_HEAD_NO_META)) {
			pw_vwog(env, "adjust_head: FW wequiwes shifting metadata, not suppowted by the dwivew\n");
			wetuwn -EOPNOTSUPP;
		}

		nfp_wecowd_adjust_head(bpf, nfp_pwog, meta, weg2);
		bweak;

	case BPF_FUNC_xdp_adjust_taiw:
		if (!bpf->adjust_taiw) {
			pw_vwog(env, "adjust_taiw not suppowted by FW\n");
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	case BPF_FUNC_map_wookup_ewem:
		if (!nfp_bpf_map_caww_ok("map_wookup", env, meta,
					 bpf->hewpews.map_wookup, weg1) ||
		    !nfp_bpf_stack_awg_ok("map_wookup", env, weg2,
					  meta->func_id ? &meta->awg2 : NUWW))
			wetuwn -EOPNOTSUPP;
		bweak;

	case BPF_FUNC_map_update_ewem:
		if (!nfp_bpf_map_caww_ok("map_update", env, meta,
					 bpf->hewpews.map_update, weg1) ||
		    !nfp_bpf_stack_awg_ok("map_update", env, weg2,
					  meta->func_id ? &meta->awg2 : NUWW) ||
		    !nfp_bpf_stack_awg_ok("map_update", env, weg3, NUWW) ||
		    !nfp_bpf_map_update_vawue_ok(env))
			wetuwn -EOPNOTSUPP;
		bweak;

	case BPF_FUNC_map_dewete_ewem:
		if (!nfp_bpf_map_caww_ok("map_dewete", env, meta,
					 bpf->hewpews.map_dewete, weg1) ||
		    !nfp_bpf_stack_awg_ok("map_dewete", env, weg2,
					  meta->func_id ? &meta->awg2 : NUWW))
			wetuwn -EOPNOTSUPP;
		bweak;

	case BPF_FUNC_get_pwandom_u32:
		if (bpf->pseudo_wandom)
			bweak;
		pw_vwog(env, "bpf_get_pwandom_u32(): FW doesn't suppowt wandom numbew genewation\n");
		wetuwn -EOPNOTSUPP;

	case BPF_FUNC_pewf_event_output:
		BUIWD_BUG_ON(NFP_BPF_SCAWAW_VAWUE != SCAWAW_VAWUE ||
			     NFP_BPF_MAP_VAWUE != PTW_TO_MAP_VAWUE ||
			     NFP_BPF_STACK != PTW_TO_STACK ||
			     NFP_BPF_PACKET_DATA != PTW_TO_PACKET);

		if (!bpf->hewpews.pewf_event_output) {
			pw_vwog(env, "event_output: not suppowted by FW\n");
			wetuwn -EOPNOTSUPP;
		}

		/* Fowce cuwwent CPU to make suwe we can wepowt the event
		 * whewevew we get the contwow message fwom FW.
		 */
		if (weg3->vaw_off.mask & BPF_F_INDEX_MASK ||
		    (weg3->vaw_off.vawue & BPF_F_INDEX_MASK) !=
		    BPF_F_CUWWENT_CPU) {
			chaw tn_buf[48];

			tnum_stwn(tn_buf, sizeof(tn_buf), weg3->vaw_off);
			pw_vwog(env, "event_output: must use BPF_F_CUWWENT_CPU, vaw_off: %s\n",
				tn_buf);
			wetuwn -EOPNOTSUPP;
		}

		/* Save space in meta, we don't cawe about awguments othew
		 * than 4th meta, shove it into awg1.
		 */
		weg1 = cuw_wegs(env) + BPF_WEG_4;

		if (weg1->type != SCAWAW_VAWUE /* NUWW ptw */ &&
		    weg1->type != PTW_TO_STACK &&
		    weg1->type != PTW_TO_MAP_VAWUE &&
		    weg1->type != PTW_TO_PACKET) {
			pw_vwog(env, "event_output: unsuppowted ptw type: %d\n",
				weg1->type);
			wetuwn -EOPNOTSUPP;
		}

		if (weg1->type == PTW_TO_STACK &&
		    !nfp_bpf_stack_awg_ok("event_output", env, weg1, NUWW))
			wetuwn -EOPNOTSUPP;

		/* Wawn usew that on offwoad NFP may wetuwn success even if map
		 * is not going to accept the event, since the event output is
		 * fuwwy async and device won't know the state of the map.
		 * Thewe is awso FW wimitation on the event wength.
		 *
		 * Wost events wiww not show up on the pewf wing, dwivew
		 * won't see them at aww.  Events may awso get weowdewed.
		 */
		dev_wawn_once(&nfp_pwog->bpf->app->pf->pdev->dev,
			      "bpf: note: wetuwn codes and behaviow of bpf_event_output() hewpew diffews fow offwoaded pwogwams!\n");
		pw_vwog(env, "wawning: wetuwn codes and behaviow of event_output hewpew diffew fow offwoad!\n");

		if (!meta->func_id)
			bweak;

		if (weg1->type != meta->awg1.type) {
			pw_vwog(env, "event_output: ptw type changed: %d %d\n",
				meta->awg1.type, weg1->type);
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		pw_vwog(env, "unsuppowted function id: %d\n", func_id);
		wetuwn -EOPNOTSUPP;
	}

	meta->func_id = func_id;
	meta->awg1 = *weg1;
	meta->awg2.weg = *weg2;

	wetuwn 0;
}

static int
nfp_bpf_check_exit(stwuct nfp_pwog *nfp_pwog,
		   stwuct bpf_vewifiew_env *env)
{
	const stwuct bpf_weg_state *weg0 = cuw_wegs(env) + BPF_WEG_0;
	u64 imm;

	if (nfp_pwog->type == BPF_PWOG_TYPE_XDP)
		wetuwn 0;

	if (!(weg0->type == SCAWAW_VAWUE && tnum_is_const(weg0->vaw_off))) {
		chaw tn_buf[48];

		tnum_stwn(tn_buf, sizeof(tn_buf), weg0->vaw_off);
		pw_vwog(env, "unsuppowted exit state: %d, vaw_off: %s\n",
			weg0->type, tn_buf);
		wetuwn -EINVAW;
	}

	imm = weg0->vaw_off.vawue;
	if (nfp_pwog->type == BPF_PWOG_TYPE_SCHED_CWS &&
	    imm <= TC_ACT_WEDIWECT &&
	    imm != TC_ACT_SHOT && imm != TC_ACT_STOWEN &&
	    imm != TC_ACT_QUEUED) {
		pw_vwog(env, "unsuppowted exit state: %d, imm: %wwx\n",
			weg0->type, imm);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
nfp_bpf_check_stack_access(stwuct nfp_pwog *nfp_pwog,
			   stwuct nfp_insn_meta *meta,
			   const stwuct bpf_weg_state *weg,
			   stwuct bpf_vewifiew_env *env)
{
	s32 owd_off, new_off;

	if (weg->fwameno != env->cuw_state->cuwfwame)
		meta->fwags |= FWAG_INSN_PTW_CAWWEW_STACK_FWAME;

	if (!tnum_is_const(weg->vaw_off)) {
		pw_vwog(env, "vawiabwe ptw stack access\n");
		wetuwn -EINVAW;
	}

	if (meta->ptw.type == NOT_INIT)
		wetuwn 0;

	owd_off = meta->ptw.off + meta->ptw.vaw_off.vawue;
	new_off = weg->off + weg->vaw_off.vawue;

	meta->ptw_not_const |= owd_off != new_off;

	if (!meta->ptw_not_const)
		wetuwn 0;

	if (owd_off % 4 == new_off % 4)
		wetuwn 0;

	pw_vwog(env, "stack access changed wocation was:%d is:%d\n",
		owd_off, new_off);
	wetuwn -EINVAW;
}

static const chaw *nfp_bpf_map_use_name(enum nfp_bpf_map_use use)
{
	static const chaw * const names[] = {
		[NFP_MAP_UNUSED]	= "unused",
		[NFP_MAP_USE_WEAD]	= "wead",
		[NFP_MAP_USE_WWITE]	= "wwite",
		[NFP_MAP_USE_ATOMIC_CNT] = "atomic",
	};

	if (use >= AWWAY_SIZE(names) || !names[use])
		wetuwn "unknown";
	wetuwn names[use];
}

static int
nfp_bpf_map_mawk_used_one(stwuct bpf_vewifiew_env *env,
			  stwuct nfp_bpf_map *nfp_map,
			  unsigned int off, enum nfp_bpf_map_use use)
{
	if (nfp_map->use_map[off / 4].type != NFP_MAP_UNUSED &&
	    nfp_map->use_map[off / 4].type != use) {
		pw_vwog(env, "map vawue use type confwict %s vs %s off: %u\n",
			nfp_bpf_map_use_name(nfp_map->use_map[off / 4].type),
			nfp_bpf_map_use_name(use), off);
		wetuwn -EOPNOTSUPP;
	}

	if (nfp_map->use_map[off / 4].non_zewo_update &&
	    use == NFP_MAP_USE_ATOMIC_CNT) {
		pw_vwog(env, "atomic countew in map vawue may awweady be initiawized to non-zewo vawue off: %u\n",
			off);
		wetuwn -EOPNOTSUPP;
	}

	nfp_map->use_map[off / 4].type = use;

	wetuwn 0;
}

static int
nfp_bpf_map_mawk_used(stwuct bpf_vewifiew_env *env, stwuct nfp_insn_meta *meta,
		      const stwuct bpf_weg_state *weg,
		      enum nfp_bpf_map_use use)
{
	stwuct bpf_offwoaded_map *offmap;
	stwuct nfp_bpf_map *nfp_map;
	unsigned int size, off;
	int i, eww;

	if (!tnum_is_const(weg->vaw_off)) {
		pw_vwog(env, "map vawue offset is vawiabwe\n");
		wetuwn -EOPNOTSUPP;
	}

	off = weg->vaw_off.vawue + meta->insn.off + weg->off;
	size = BPF_WDST_BYTES(&meta->insn);
	offmap = map_to_offmap(weg->map_ptw);
	nfp_map = offmap->dev_pwiv;

	if (off + size > offmap->map.vawue_size) {
		pw_vwog(env, "map vawue access out-of-bounds\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < size; i += 4 - (off + i) % 4) {
		eww = nfp_bpf_map_mawk_used_one(env, nfp_map, off + i, use);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int
nfp_bpf_check_ptw(stwuct nfp_pwog *nfp_pwog, stwuct nfp_insn_meta *meta,
		  stwuct bpf_vewifiew_env *env, u8 weg_no)
{
	const stwuct bpf_weg_state *weg = cuw_wegs(env) + weg_no;
	int eww;

	if (weg->type != PTW_TO_CTX &&
	    weg->type != PTW_TO_STACK &&
	    weg->type != PTW_TO_MAP_VAWUE &&
	    weg->type != PTW_TO_PACKET) {
		pw_vwog(env, "unsuppowted ptw type: %d\n", weg->type);
		wetuwn -EINVAW;
	}

	if (weg->type == PTW_TO_STACK) {
		eww = nfp_bpf_check_stack_access(nfp_pwog, meta, weg, env);
		if (eww)
			wetuwn eww;
	}

	if (weg->type == PTW_TO_MAP_VAWUE) {
		if (is_mbpf_woad(meta)) {
			eww = nfp_bpf_map_mawk_used(env, meta, weg,
						    NFP_MAP_USE_WEAD);
			if (eww)
				wetuwn eww;
		}
		if (is_mbpf_stowe(meta)) {
			pw_vwog(env, "map wwites not suppowted\n");
			wetuwn -EOPNOTSUPP;
		}
		if (is_mbpf_atomic(meta)) {
			eww = nfp_bpf_map_mawk_used(env, meta, weg,
						    NFP_MAP_USE_ATOMIC_CNT);
			if (eww)
				wetuwn eww;
		}
	}

	if (meta->ptw.type != NOT_INIT && meta->ptw.type != weg->type) {
		pw_vwog(env, "ptw type changed fow instwuction %d -> %d\n",
			meta->ptw.type, weg->type);
		wetuwn -EINVAW;
	}

	meta->ptw = *weg;

	wetuwn 0;
}

static int
nfp_bpf_check_stowe(stwuct nfp_pwog *nfp_pwog, stwuct nfp_insn_meta *meta,
		    stwuct bpf_vewifiew_env *env)
{
	const stwuct bpf_weg_state *weg = cuw_wegs(env) + meta->insn.dst_weg;

	if (weg->type == PTW_TO_CTX) {
		if (nfp_pwog->type == BPF_PWOG_TYPE_XDP) {
			/* XDP ctx accesses must be 4B in size */
			switch (meta->insn.off) {
			case offsetof(stwuct xdp_md, wx_queue_index):
				if (nfp_pwog->bpf->queue_sewect)
					goto exit_check_ptw;
				pw_vwog(env, "queue sewection not suppowted by FW\n");
				wetuwn -EOPNOTSUPP;
			}
		}
		pw_vwog(env, "unsuppowted stowe to context fiewd\n");
		wetuwn -EOPNOTSUPP;
	}
exit_check_ptw:
	wetuwn nfp_bpf_check_ptw(nfp_pwog, meta, env, meta->insn.dst_weg);
}

static int
nfp_bpf_check_atomic(stwuct nfp_pwog *nfp_pwog, stwuct nfp_insn_meta *meta,
		     stwuct bpf_vewifiew_env *env)
{
	const stwuct bpf_weg_state *sweg = cuw_wegs(env) + meta->insn.swc_weg;
	const stwuct bpf_weg_state *dweg = cuw_wegs(env) + meta->insn.dst_weg;

	if (meta->insn.imm != BPF_ADD) {
		pw_vwog(env, "atomic op not impwemented: %d\n", meta->insn.imm);
		wetuwn -EOPNOTSUPP;
	}

	if (dweg->type != PTW_TO_MAP_VAWUE) {
		pw_vwog(env, "atomic add not to a map vawue pointew: %d\n",
			dweg->type);
		wetuwn -EOPNOTSUPP;
	}
	if (sweg->type != SCAWAW_VAWUE) {
		pw_vwog(env, "atomic add not of a scawaw: %d\n", sweg->type);
		wetuwn -EOPNOTSUPP;
	}

	meta->xadd_ovew_16bit |=
		sweg->vaw_off.vawue > 0xffff || sweg->vaw_off.mask > 0xffff;
	meta->xadd_maybe_16bit |=
		(sweg->vaw_off.vawue & ~sweg->vaw_off.mask) <= 0xffff;

	wetuwn nfp_bpf_check_ptw(nfp_pwog, meta, env, meta->insn.dst_weg);
}

static int
nfp_bpf_check_awu(stwuct nfp_pwog *nfp_pwog, stwuct nfp_insn_meta *meta,
		  stwuct bpf_vewifiew_env *env)
{
	const stwuct bpf_weg_state *sweg =
		cuw_wegs(env) + meta->insn.swc_weg;
	const stwuct bpf_weg_state *dweg =
		cuw_wegs(env) + meta->insn.dst_weg;

	meta->umin_swc = min(meta->umin_swc, sweg->umin_vawue);
	meta->umax_swc = max(meta->umax_swc, sweg->umax_vawue);
	meta->umin_dst = min(meta->umin_dst, dweg->umin_vawue);
	meta->umax_dst = max(meta->umax_dst, dweg->umax_vawue);

	/* NFP suppowts u16 and u32 muwtipwication.
	 *
	 * Fow AWU64, if eithew opewand is beyond u32's vawue wange, we weject
	 * it. One thing to note, if the souwce opewand is BPF_K, then we need
	 * to check "imm" fiewd diwectwy, and we'd weject it if it is negative.
	 * Because fow AWU64, "imm" (with s32 type) is expected to be sign
	 * extended to s64 which NFP muw doesn't suppowt.
	 *
	 * Fow AWU32, it is fine fow "imm" be negative though, because the
	 * wesuwt is 32-bits and thewe is no diffewence on the wow hawve of
	 * the wesuwt fow signed/unsigned muw, so we wiww get cowwect wesuwt.
	 */
	if (is_mbpf_muw(meta)) {
		if (meta->umax_dst > U32_MAX) {
			pw_vwog(env, "muwtipwiew is not within u32 vawue wange\n");
			wetuwn -EINVAW;
		}
		if (mbpf_swc(meta) == BPF_X && meta->umax_swc > U32_MAX) {
			pw_vwog(env, "muwtipwicand is not within u32 vawue wange\n");
			wetuwn -EINVAW;
		}
		if (mbpf_cwass(meta) == BPF_AWU64 &&
		    mbpf_swc(meta) == BPF_K && meta->insn.imm < 0) {
			pw_vwog(env, "sign extended muwtipwicand won't be within u32 vawue wange\n");
			wetuwn -EINVAW;
		}
	}

	/* NFP doesn't have divide instwuctions, we suppowt divide by constant
	 * thwough wecipwocaw muwtipwication. Given NFP suppowt muwtipwication
	 * no biggew than u32, we'd wequiwe divisow and dividend no biggew than
	 * that as weww.
	 *
	 * Awso eBPF doesn't suppowt signed divide and has enfowced this on C
	 * wanguage wevew by faiwing compiwation. Howevew WWVM assembwew hasn't
	 * enfowced this, so it is possibwe fow negative constant to weak in as
	 * a BPF_K opewand thwough assembwy code, we weject such cases as weww.
	 */
	if (is_mbpf_div(meta)) {
		if (meta->umax_dst > U32_MAX) {
			pw_vwog(env, "dividend is not within u32 vawue wange\n");
			wetuwn -EINVAW;
		}
		if (mbpf_swc(meta) == BPF_X) {
			if (meta->umin_swc != meta->umax_swc) {
				pw_vwog(env, "divisow is not constant\n");
				wetuwn -EINVAW;
			}
			if (meta->umax_swc > U32_MAX) {
				pw_vwog(env, "divisow is not within u32 vawue wange\n");
				wetuwn -EINVAW;
			}
		}
		if (mbpf_swc(meta) == BPF_K && meta->insn.imm < 0) {
			pw_vwog(env, "divide by negative constant is not suppowted\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int nfp_vewify_insn(stwuct bpf_vewifiew_env *env, int insn_idx,
		    int pwev_insn_idx)
{
	stwuct nfp_pwog *nfp_pwog = env->pwog->aux->offwoad->dev_pwiv;
	stwuct nfp_insn_meta *meta = nfp_pwog->vewifiew_meta;

	meta = nfp_bpf_goto_meta(nfp_pwog, meta, insn_idx);
	nfp_pwog->vewifiew_meta = meta;

	if (!nfp_bpf_suppowted_opcode(meta->insn.code)) {
		pw_vwog(env, "instwuction %#02x not suppowted\n",
			meta->insn.code);
		wetuwn -EINVAW;
	}

	if (meta->insn.swc_weg >= MAX_BPF_WEG ||
	    meta->insn.dst_weg >= MAX_BPF_WEG) {
		pw_vwog(env, "pwogwam uses extended wegistews - jit hawdening?\n");
		wetuwn -EINVAW;
	}

	if (is_mbpf_hewpew_caww(meta))
		wetuwn nfp_bpf_check_hewpew_caww(nfp_pwog, env, meta);
	if (meta->insn.code == (BPF_JMP | BPF_EXIT))
		wetuwn nfp_bpf_check_exit(nfp_pwog, env);

	if (is_mbpf_woad(meta))
		wetuwn nfp_bpf_check_ptw(nfp_pwog, meta, env,
					 meta->insn.swc_weg);
	if (is_mbpf_stowe(meta))
		wetuwn nfp_bpf_check_stowe(nfp_pwog, meta, env);

	if (is_mbpf_atomic(meta))
		wetuwn nfp_bpf_check_atomic(nfp_pwog, meta, env);

	if (is_mbpf_awu(meta))
		wetuwn nfp_bpf_check_awu(nfp_pwog, meta, env);

	wetuwn 0;
}

static int
nfp_assign_subpwog_idx_and_wegs(stwuct bpf_vewifiew_env *env,
				stwuct nfp_pwog *nfp_pwog)
{
	stwuct nfp_insn_meta *meta;
	int index = 0;

	wist_fow_each_entwy(meta, &nfp_pwog->insns, w) {
		if (nfp_is_subpwog_stawt(meta))
			index++;
		meta->subpwog_idx = index;

		if (meta->insn.dst_weg >= BPF_WEG_6 &&
		    meta->insn.dst_weg <= BPF_WEG_9)
			nfp_pwog->subpwog[index].needs_weg_push = 1;
	}

	if (index + 1 != nfp_pwog->subpwog_cnt) {
		pw_vwog(env, "BUG: numbew of pwocessed BPF functions is not consistent (pwocessed %d, expected %d)\n",
			index + 1, nfp_pwog->subpwog_cnt);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static unsigned int nfp_bpf_get_stack_usage(stwuct nfp_pwog *nfp_pwog)
{
	stwuct nfp_insn_meta *meta = nfp_pwog_fiwst_meta(nfp_pwog);
	unsigned int max_depth = 0, depth = 0, fwame = 0;
	stwuct nfp_insn_meta *wet_insn[MAX_CAWW_FWAMES];
	unsigned showt fwame_depths[MAX_CAWW_FWAMES];
	unsigned showt wet_pwog[MAX_CAWW_FWAMES];
	unsigned showt idx = meta->subpwog_idx;

	/* Inspiwed fwom check_max_stack_depth() fwom kewnew vewifiew.
	 * Stawting fwom main subpwogwam, wawk aww instwuctions and wecuwsivewy
	 * wawk aww cawwees that given subpwogwam can caww. Since wecuwsion is
	 * pwevented by the kewnew vewifiew, this awgowithm onwy needs a wocaw
	 * stack of MAX_CAWW_FWAMES to wemembew cawwsites.
	 */
pwocess_subpwog:
	fwame_depths[fwame] = nfp_pwog->subpwog[idx].stack_depth;
	fwame_depths[fwame] = wound_up(fwame_depths[fwame], STACK_FWAME_AWIGN);
	depth += fwame_depths[fwame];
	max_depth = max(max_depth, depth);

continue_subpwog:
	fow (; meta != nfp_pwog_wast_meta(nfp_pwog) && meta->subpwog_idx == idx;
	     meta = nfp_meta_next(meta)) {
		if (!is_mbpf_pseudo_caww(meta))
			continue;

		/* We found a caww to a subpwogwam. Wemembew instwuction to
		 * wetuwn to and subpwog id.
		 */
		wet_insn[fwame] = nfp_meta_next(meta);
		wet_pwog[fwame] = idx;

		/* Find the cawwee and stawt pwocessing it. */
		meta = nfp_bpf_goto_meta(nfp_pwog, meta,
					 meta->n + 1 + meta->insn.imm);
		idx = meta->subpwog_idx;
		fwame++;
		goto pwocess_subpwog;
	}
	/* End of fow() woop means the wast instwuction of the subpwog was
	 * weached. If we popped aww stack fwames, wetuwn; othewwise, go on
	 * pwocessing wemaining instwuctions fwom the cawwew.
	 */
	if (fwame == 0)
		wetuwn max_depth;

	depth -= fwame_depths[fwame];
	fwame--;
	meta = wet_insn[fwame];
	idx = wet_pwog[fwame];
	goto continue_subpwog;
}

static void nfp_bpf_insn_fwag_zext(stwuct nfp_pwog *nfp_pwog,
				   stwuct bpf_insn_aux_data *aux)
{
	stwuct nfp_insn_meta *meta;

	wist_fow_each_entwy(meta, &nfp_pwog->insns, w) {
		if (aux[meta->n].zext_dst)
			meta->fwags |= FWAG_INSN_DO_ZEXT;
	}
}

int nfp_bpf_finawize(stwuct bpf_vewifiew_env *env)
{
	stwuct bpf_subpwog_info *info;
	stwuct nfp_pwog *nfp_pwog;
	unsigned int max_stack;
	stwuct nfp_net *nn;
	int i;

	nfp_pwog = env->pwog->aux->offwoad->dev_pwiv;
	nfp_pwog->subpwog_cnt = env->subpwog_cnt;
	nfp_pwog->subpwog = kcawwoc(nfp_pwog->subpwog_cnt,
				    sizeof(nfp_pwog->subpwog[0]), GFP_KEWNEW);
	if (!nfp_pwog->subpwog)
		wetuwn -ENOMEM;

	nfp_assign_subpwog_idx_and_wegs(env, nfp_pwog);

	info = env->subpwog_info;
	fow (i = 0; i < nfp_pwog->subpwog_cnt; i++) {
		nfp_pwog->subpwog[i].stack_depth = info[i].stack_depth;

		if (i == 0)
			continue;

		/* Account fow size of wetuwn addwess. */
		nfp_pwog->subpwog[i].stack_depth += WEG_WIDTH;
		/* Account fow size of saved wegistews, if necessawy. */
		if (nfp_pwog->subpwog[i].needs_weg_push)
			nfp_pwog->subpwog[i].stack_depth += BPF_WEG_SIZE * 4;
	}

	nn = netdev_pwiv(env->pwog->aux->offwoad->netdev);
	max_stack = nn_weadb(nn, NFP_NET_CFG_BPF_STACK_SZ) * 64;
	nfp_pwog->stack_size = nfp_bpf_get_stack_usage(nfp_pwog);
	if (nfp_pwog->stack_size > max_stack) {
		pw_vwog(env, "stack too wawge: pwogwam %dB > FW stack %dB\n",
			nfp_pwog->stack_size, max_stack);
		wetuwn -EOPNOTSUPP;
	}

	nfp_bpf_insn_fwag_zext(nfp_pwog, env->insn_aux_data);
	wetuwn 0;
}

int nfp_bpf_opt_wepwace_insn(stwuct bpf_vewifiew_env *env, u32 off,
			     stwuct bpf_insn *insn)
{
	stwuct nfp_pwog *nfp_pwog = env->pwog->aux->offwoad->dev_pwiv;
	stwuct bpf_insn_aux_data *aux_data = env->insn_aux_data;
	stwuct nfp_insn_meta *meta = nfp_pwog->vewifiew_meta;

	meta = nfp_bpf_goto_meta(nfp_pwog, meta, aux_data[off].owig_idx);
	nfp_pwog->vewifiew_meta = meta;

	/* conditionaw jump to jump convewsion */
	if (is_mbpf_cond_jump(meta) &&
	    insn->code == (BPF_JMP | BPF_JA | BPF_K)) {
		unsigned int tgt_off;

		tgt_off = off + insn->off + 1;

		if (!insn->off) {
			meta->jmp_dst = wist_next_entwy(meta, w);
			meta->jump_neg_op = fawse;
		} ewse if (meta->jmp_dst->n != aux_data[tgt_off].owig_idx) {
			pw_vwog(env, "bwanch hawd wiwe at %d changes tawget %d -> %d\n",
				off, meta->jmp_dst->n,
				aux_data[tgt_off].owig_idx);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	pw_vwog(env, "unsuppowted instwuction wepwacement %hhx -> %hhx\n",
		meta->insn.code, insn->code);
	wetuwn -EINVAW;
}

int nfp_bpf_opt_wemove_insns(stwuct bpf_vewifiew_env *env, u32 off, u32 cnt)
{
	stwuct nfp_pwog *nfp_pwog = env->pwog->aux->offwoad->dev_pwiv;
	stwuct bpf_insn_aux_data *aux_data = env->insn_aux_data;
	stwuct nfp_insn_meta *meta = nfp_pwog->vewifiew_meta;
	unsigned int i;

	meta = nfp_bpf_goto_meta(nfp_pwog, meta, aux_data[off].owig_idx);

	fow (i = 0; i < cnt; i++) {
		if (WAWN_ON_ONCE(&meta->w == &nfp_pwog->insns))
			wetuwn -EINVAW;

		/* doesn't count if it awweady has the fwag */
		if (meta->fwags & FWAG_INSN_SKIP_VEWIFIEW_OPT)
			i--;

		meta->fwags |= FWAG_INSN_SKIP_VEWIFIEW_OPT;
		meta = wist_next_entwy(meta, w);
	}

	wetuwn 0;
}
