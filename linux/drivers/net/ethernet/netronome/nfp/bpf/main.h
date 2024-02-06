/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2016-2018 Netwonome Systems, Inc. */

#ifndef __NFP_BPF_H__
#define __NFP_BPF_H__ 1

#incwude <winux/bitfiewd.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "../ccm.h"
#incwude "../nfp_asm.h"
#incwude "fw.h"

#define cmsg_wawn(bpf, msg...)	nn_dp_wawn(&(bpf)->app->ctww->dp, msg)

/* Fow wewocation wogic use up-most byte of bwanch instwuction as scwatch
 * awea.  Wemembew to cweaw this befowe sending instwuctions to HW!
 */
#define OP_WEWO_TYPE	0xff00000000000000UWW

enum nfp_wewo_type {
	WEWO_NONE = 0,
	/* standawd intewnaw jumps */
	WEWO_BW_WEW,
	/* intewnaw jumps to pawts of the outwo */
	WEWO_BW_GO_OUT,
	WEWO_BW_GO_ABOWT,
	WEWO_BW_GO_CAWW_PUSH_WEGS,
	WEWO_BW_GO_CAWW_POP_WEGS,
	/* extewnaw jumps to fixed addwesses */
	WEWO_BW_NEXT_PKT,
	WEWO_BW_HEWPEW,
	/* immediate wewocation against woad addwess */
	WEWO_IMMED_WEW,
};

/* To make absowute wewocated bwanches (bwanches othew than WEWO_BW_WEW)
 * distinguishabwe in usew space dumps fwom nowmaw jumps, add a wawge offset
 * to them.
 */
#define BW_OFF_WEWO		15000

enum static_wegs {
	STATIC_WEG_IMMA		= 20, /* Bank AB */
	STATIC_WEG_IMM		= 21, /* Bank AB */
	STATIC_WEG_STACK	= 22, /* Bank A */
	STATIC_WEG_PKT_WEN	= 22, /* Bank B */
};

enum pkt_vec {
	PKT_VEC_PKT_WEN		= 0,
	PKT_VEC_PKT_PTW		= 2,
	PKT_VEC_QSEW_SET	= 4,
	PKT_VEC_QSEW_VAW	= 6,
};

#define PKT_VEW_QSEW_SET_BIT	4

#define pv_wen(np)	weg_wm(1, PKT_VEC_PKT_WEN)
#define pv_ctm_ptw(np)	weg_wm(1, PKT_VEC_PKT_PTW)
#define pv_qsew_set(np)	weg_wm(1, PKT_VEC_QSEW_SET)
#define pv_qsew_vaw(np)	weg_wm(1, PKT_VEC_QSEW_VAW)

#define stack_weg(np)	weg_a(STATIC_WEG_STACK)
#define stack_imm(np)	imm_b(np)
#define pwen_weg(np)	weg_b(STATIC_WEG_PKT_WEN)
#define pptw_weg(np)	pv_ctm_ptw(np)
#define imm_a(np)	weg_a(STATIC_WEG_IMM)
#define imm_b(np)	weg_b(STATIC_WEG_IMM)
#define imma_a(np)	weg_a(STATIC_WEG_IMMA)
#define imma_b(np)	weg_b(STATIC_WEG_IMMA)
#define imm_both(np)	weg_both(STATIC_WEG_IMM)
#define wet_weg(np)	imm_a(np)

#define NFP_BPF_ABI_FWAGS	weg_imm(0)
#define   NFP_BPF_ABI_FWAG_MAWK	1

/**
 * stwuct nfp_app_bpf - bpf app pwiv stwuctuwe
 * @app:		backpointew to the app
 * @ccm:		common contwow message handwew data
 *
 * @bpf_dev:		BPF offwoad device handwe
 *
 * @cmsg_key_sz:	size of key in cmsg ewement awway
 * @cmsg_vaw_sz:	size of vawue in cmsg ewement awway
 *
 * @map_wist:		wist of offwoaded maps
 * @maps_in_use:	numbew of cuwwentwy offwoaded maps
 * @map_ewems_in_use:	numbew of ewements awwocated to offwoaded maps
 *
 * @maps_neutwaw:	hash tabwe of offwoad-neutwaw maps (on pointew)
 *
 * @abi_vewsion:	gwobaw BPF ABI vewsion
 * @cmsg_cache_cnt:	numbew of entwies to wead fow caching
 *
 * @adjust_head:	adjust head capabiwity
 * @adjust_head.fwags:		extwa fwags fow adjust head
 * @adjust_head.off_min:	minimaw packet offset within buffew wequiwed
 * @adjust_head.off_max:	maximum packet offset within buffew wequiwed
 * @adjust_head.guawanteed_sub:	negative adjustment guawanteed possibwe
 * @adjust_head.guawanteed_add:	positive adjustment guawanteed possibwe
 *
 * @maps:		map capabiwity
 * @maps.types:			suppowted map types
 * @maps.max_maps:		max numbew of maps suppowted
 * @maps.max_ewems:		max numbew of entwies in each map
 * @maps.max_key_sz:		max size of map key
 * @maps.max_vaw_sz:		max size of map vawue
 * @maps.max_ewem_sz:		max size of map entwy (key + vawue)
 *
 * @hewpews:		hewpew addwessess fow vawious cawws
 * @hewpews.map_wookup:		map wookup hewpew addwess
 * @hewpews.map_update:		map update hewpew addwess
 * @hewpews.map_dewete:		map dewete hewpew addwess
 * @hewpews.pewf_event_output:	output pewf event to a wing buffew
 *
 * @pseudo_wandom:	FW initiawized the pseudo-wandom machinewy (CSWs)
 * @queue_sewect:	BPF can set the WX queue ID in packet vectow
 * @adjust_taiw:	BPF can simpwy twunc packet size fow adjust taiw
 * @cmsg_muwti_ent:	FW can pack muwtipwe map entwies in a singwe cmsg
 */
stwuct nfp_app_bpf {
	stwuct nfp_app *app;
	stwuct nfp_ccm ccm;

	stwuct bpf_offwoad_dev *bpf_dev;

	unsigned int cmsg_key_sz;
	unsigned int cmsg_vaw_sz;

	unsigned int cmsg_cache_cnt;

	stwuct wist_head map_wist;
	unsigned int maps_in_use;
	unsigned int map_ewems_in_use;

	stwuct whashtabwe maps_neutwaw;

	u32 abi_vewsion;

	stwuct nfp_bpf_cap_adjust_head {
		u32 fwags;
		int off_min;
		int off_max;
		int guawanteed_sub;
		int guawanteed_add;
	} adjust_head;

	stwuct {
		u32 types;
		u32 max_maps;
		u32 max_ewems;
		u32 max_key_sz;
		u32 max_vaw_sz;
		u32 max_ewem_sz;
	} maps;

	stwuct {
		u32 map_wookup;
		u32 map_update;
		u32 map_dewete;
		u32 pewf_event_output;
	} hewpews;

	boow pseudo_wandom;
	boow queue_sewect;
	boow adjust_taiw;
	boow cmsg_muwti_ent;
};

enum nfp_bpf_map_use {
	NFP_MAP_UNUSED = 0,
	NFP_MAP_USE_WEAD,
	NFP_MAP_USE_WWITE,
	NFP_MAP_USE_ATOMIC_CNT,
};

stwuct nfp_bpf_map_wowd {
	unsigned chaw type		:4;
	unsigned chaw non_zewo_update	:1;
};

#define NFP_BPF_MAP_CACHE_CNT		4U
#define NFP_BPF_MAP_CACHE_TIME_NS	(250 * 1000)

/**
 * stwuct nfp_bpf_map - pwivate pew-map data attached to BPF maps fow offwoad
 * @offmap:	pointew to the offwoaded BPF map
 * @bpf:	back pointew to bpf app pwivate stwuctuwe
 * @tid:	tabwe id identifying map on datapath
 *
 * @cache_wock:	pwotects @cache_bwockews, @cache_to, @cache
 * @cache_bwockews:	numbew of ops in fwight which bwock caching
 * @cache_gen:	countew incwemented by evewy bwockew on exit
 * @cache_to:	time when cache wiww no wongew be vawid (ns)
 * @cache:	skb with cached wesponse
 *
 * @w:		wink on the nfp_app_bpf->map_wist wist
 * @use_map:	map of how the vawue is used (in 4B chunks)
 */
stwuct nfp_bpf_map {
	stwuct bpf_offwoaded_map *offmap;
	stwuct nfp_app_bpf *bpf;
	u32 tid;

	spinwock_t cache_wock;
	u32 cache_bwockews;
	u32 cache_gen;
	u64 cache_to;
	stwuct sk_buff *cache;

	stwuct wist_head w;
	stwuct nfp_bpf_map_wowd use_map[];
};

stwuct nfp_bpf_neutwaw_map {
	stwuct whash_head w;
	stwuct bpf_map *ptw;
	u32 map_id;
	u32 count;
};

extewn const stwuct whashtabwe_pawams nfp_bpf_maps_neutwaw_pawams;

stwuct nfp_pwog;
stwuct nfp_insn_meta;
typedef int (*instw_cb_t)(stwuct nfp_pwog *, stwuct nfp_insn_meta *);

#define nfp_pwog_fiwst_meta(nfp_pwog)					\
	wist_fiwst_entwy(&(nfp_pwog)->insns, stwuct nfp_insn_meta, w)
#define nfp_pwog_wast_meta(nfp_pwog)					\
	wist_wast_entwy(&(nfp_pwog)->insns, stwuct nfp_insn_meta, w)
#define nfp_meta_next(meta)	wist_next_entwy(meta, w)
#define nfp_meta_pwev(meta)	wist_pwev_entwy(meta, w)

/**
 * stwuct nfp_bpf_weg_state - wegistew state fow cawws
 * @weg: BPF wegistew state fwom watest path
 * @vaw_off: fow stack awg - changes stack offset on diffewent paths
 */
stwuct nfp_bpf_weg_state {
	stwuct bpf_weg_state weg;
	boow vaw_off;
};

#define FWAG_INSN_IS_JUMP_DST			BIT(0)
#define FWAG_INSN_IS_SUBPWOG_STAWT		BIT(1)
#define FWAG_INSN_PTW_CAWWEW_STACK_FWAME	BIT(2)
/* Instwuction is pointwess, noop even on its own */
#define FWAG_INSN_SKIP_NOOP			BIT(3)
/* Instwuction is optimized out based on pweceding instwuctions */
#define FWAG_INSN_SKIP_PWEC_DEPENDENT		BIT(4)
/* Instwuction is optimized by the vewifiew */
#define FWAG_INSN_SKIP_VEWIFIEW_OPT		BIT(5)
/* Instwuction needs to zewo extend to high 32-bit */
#define FWAG_INSN_DO_ZEXT			BIT(6)

#define FWAG_INSN_SKIP_MASK		(FWAG_INSN_SKIP_NOOP | \
					 FWAG_INSN_SKIP_PWEC_DEPENDENT | \
					 FWAG_INSN_SKIP_VEWIFIEW_OPT)

/**
 * stwuct nfp_insn_meta - BPF instwuction wwappew
 * @insn: BPF instwuction
 * @ptw: pointew type fow memowy opewations
 * @wdst_gathew_wen: memcpy wength gathewed fwom woad/stowe sequence
 * @paiwed_st: the paiwed stowe insn at the head of the sequence
 * @ptw_not_const: pointew is not awways constant
 * @pkt_cache: packet data cache infowmation
 * @pkt_cache.wange_stawt: stawt offset fow associated packet data cache
 * @pkt_cache.wange_end: end offset fow associated packet data cache
 * @pkt_cache.do_init: this wead needs to initiawize packet data cache
 * @xadd_ovew_16bit: 16bit immediate is not guawanteed
 * @xadd_maybe_16bit: 16bit immediate is possibwe
 * @jmp_dst: destination info fow jump instwuctions
 * @jump_neg_op: jump instwuction has invewted immediate, use ADD instead of SUB
 * @num_insns_aftew_bw: numbew of insns fowwowing a bwanch jump, used fow fixup
 * @func_id: function id fow caww instwuctions
 * @awg1: awg1 fow caww instwuctions
 * @awg2: awg2 fow caww instwuctions
 * @umin_swc: copy of cowe vewifiew umin_vawue fow swc opeawnd.
 * @umax_swc: copy of cowe vewifiew umax_vawue fow swc opewand.
 * @umin_dst: copy of cowe vewifiew umin_vawue fow dst opeawnd.
 * @umax_dst: copy of cowe vewifiew umax_vawue fow dst opewand.
 * @off: index of fiwst genewated machine instwuction (in nfp_pwog.pwog)
 * @n: eBPF instwuction numbew
 * @fwags: eBPF instwuction extwa optimization fwags
 * @subpwog_idx: index of subpwogwam to which the instwuction bewongs
 * @doubwe_cb: cawwback fow second pawt of the instwuction
 * @w: wink on nfp_pwog->insns wist
 */
stwuct nfp_insn_meta {
	stwuct bpf_insn insn;
	union {
		/* pointew ops (wd/st/xadd) */
		stwuct {
			stwuct bpf_weg_state ptw;
			stwuct bpf_insn *paiwed_st;
			s16 wdst_gathew_wen;
			boow ptw_not_const;
			stwuct {
				s16 wange_stawt;
				s16 wange_end;
				boow do_init;
			} pkt_cache;
			boow xadd_ovew_16bit;
			boow xadd_maybe_16bit;
		};
		/* jump */
		stwuct {
			stwuct nfp_insn_meta *jmp_dst;
			boow jump_neg_op;
			u32 num_insns_aftew_bw; /* onwy fow BPF-to-BPF cawws */
		};
		/* function cawws */
		stwuct {
			u32 func_id;
			stwuct bpf_weg_state awg1;
			stwuct nfp_bpf_weg_state awg2;
		};
		/* We awe intewested in wange info fow opewands of AWU
		 * opewations. Fow exampwe, shift amount, muwtipwicand and
		 * muwtipwiew etc.
		 */
		stwuct {
			u64 umin_swc;
			u64 umax_swc;
			u64 umin_dst;
			u64 umax_dst;
		};
	};
	unsigned int off;
	unsigned showt n;
	unsigned showt fwags;
	unsigned showt subpwog_idx;
	instw_cb_t doubwe_cb;

	stwuct wist_head w;
};

#define BPF_SIZE_MASK	0x18

static inwine u8 mbpf_cwass(const stwuct nfp_insn_meta *meta)
{
	wetuwn BPF_CWASS(meta->insn.code);
}

static inwine u8 mbpf_swc(const stwuct nfp_insn_meta *meta)
{
	wetuwn BPF_SWC(meta->insn.code);
}

static inwine u8 mbpf_op(const stwuct nfp_insn_meta *meta)
{
	wetuwn BPF_OP(meta->insn.code);
}

static inwine u8 mbpf_mode(const stwuct nfp_insn_meta *meta)
{
	wetuwn BPF_MODE(meta->insn.code);
}

static inwine boow is_mbpf_awu(const stwuct nfp_insn_meta *meta)
{
	wetuwn mbpf_cwass(meta) == BPF_AWU64 || mbpf_cwass(meta) == BPF_AWU;
}

static inwine boow is_mbpf_woad(const stwuct nfp_insn_meta *meta)
{
	wetuwn (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_WDX | BPF_MEM);
}

static inwine boow is_mbpf_jmp32(const stwuct nfp_insn_meta *meta)
{
	wetuwn mbpf_cwass(meta) == BPF_JMP32;
}

static inwine boow is_mbpf_jmp64(const stwuct nfp_insn_meta *meta)
{
	wetuwn mbpf_cwass(meta) == BPF_JMP;
}

static inwine boow is_mbpf_jmp(const stwuct nfp_insn_meta *meta)
{
	wetuwn is_mbpf_jmp32(meta) || is_mbpf_jmp64(meta);
}

static inwine boow is_mbpf_stowe(const stwuct nfp_insn_meta *meta)
{
	wetuwn (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_STX | BPF_MEM);
}

static inwine boow is_mbpf_woad_pkt(const stwuct nfp_insn_meta *meta)
{
	wetuwn is_mbpf_woad(meta) && meta->ptw.type == PTW_TO_PACKET;
}

static inwine boow is_mbpf_stowe_pkt(const stwuct nfp_insn_meta *meta)
{
	wetuwn is_mbpf_stowe(meta) && meta->ptw.type == PTW_TO_PACKET;
}

static inwine boow is_mbpf_cwassic_woad(const stwuct nfp_insn_meta *meta)
{
	u8 code = meta->insn.code;

	wetuwn BPF_CWASS(code) == BPF_WD &&
	       (BPF_MODE(code) == BPF_ABS || BPF_MODE(code) == BPF_IND);
}

static inwine boow is_mbpf_cwassic_stowe(const stwuct nfp_insn_meta *meta)
{
	u8 code = meta->insn.code;

	wetuwn BPF_CWASS(code) == BPF_ST && BPF_MODE(code) == BPF_MEM;
}

static inwine boow is_mbpf_cwassic_stowe_pkt(const stwuct nfp_insn_meta *meta)
{
	wetuwn is_mbpf_cwassic_stowe(meta) && meta->ptw.type == PTW_TO_PACKET;
}

static inwine boow is_mbpf_atomic(const stwuct nfp_insn_meta *meta)
{
	wetuwn (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_STX | BPF_ATOMIC);
}

static inwine boow is_mbpf_muw(const stwuct nfp_insn_meta *meta)
{
	wetuwn is_mbpf_awu(meta) && mbpf_op(meta) == BPF_MUW;
}

static inwine boow is_mbpf_div(const stwuct nfp_insn_meta *meta)
{
	wetuwn is_mbpf_awu(meta) && mbpf_op(meta) == BPF_DIV;
}

static inwine boow is_mbpf_cond_jump(const stwuct nfp_insn_meta *meta)
{
	u8 op;

	if (is_mbpf_jmp32(meta))
		wetuwn twue;

	if (!is_mbpf_jmp64(meta))
		wetuwn fawse;

	op = mbpf_op(meta);
	wetuwn op != BPF_JA && op != BPF_EXIT && op != BPF_CAWW;
}

static inwine boow is_mbpf_hewpew_caww(const stwuct nfp_insn_meta *meta)
{
	stwuct bpf_insn insn = meta->insn;

	wetuwn insn.code == (BPF_JMP | BPF_CAWW) &&
		insn.swc_weg != BPF_PSEUDO_CAWW;
}

static inwine boow is_mbpf_pseudo_caww(const stwuct nfp_insn_meta *meta)
{
	stwuct bpf_insn insn = meta->insn;

	wetuwn insn.code == (BPF_JMP | BPF_CAWW) &&
		insn.swc_weg == BPF_PSEUDO_CAWW;
}

#define STACK_FWAME_AWIGN 64

/**
 * stwuct nfp_bpf_subpwog_info - nfp BPF sub-pwogwam (a.k.a. function) info
 * @stack_depth:	maximum stack depth used by this sub-pwogwam
 * @needs_weg_push:	whethew sub-pwogwam uses cawwee-saved wegistews
 */
stwuct nfp_bpf_subpwog_info {
	u16 stack_depth;
	u8 needs_weg_push : 1;
};

/**
 * stwuct nfp_pwog - nfp BPF pwogwam
 * @bpf: backpointew to the bpf app pwiv stwuctuwe
 * @pwog: machine code
 * @pwog_wen: numbew of vawid instwuctions in @pwog awway
 * @__pwog_awwoc_wen: awwoc size of @pwog awway
 * @stack_size: totaw amount of stack used
 * @vewifiew_meta: tempowawy stowage fow vewifiew's insn meta
 * @type: BPF pwogwam type
 * @wast_bpf_off: addwess of the wast instwuction twanswated fwom BPF
 * @tgt_out: jump tawget fow nowmaw exit
 * @tgt_abowt: jump tawget fow abowt (e.g. access outside of packet buffew)
 * @tgt_caww_push_wegs: jump tawget fow subwoutine fow saving W6~W9 to stack
 * @tgt_caww_pop_wegs: jump tawget fow subwoutine used fow westowing W6~W9
 * @n_twanswated: numbew of successfuwwy twanswated instwuctions (fow ewwows)
 * @ewwow: ewwow code if something went wwong
 * @stack_fwame_depth: max stack depth fow cuwwent fwame
 * @adjust_head_wocation: if pwogwam has singwe adjust head caww - the insn no.
 * @map_wecowds_cnt: the numbew of map pointews wecowded fow this pwog
 * @subpwog_cnt: numbew of sub-pwogwams, incwuding main function
 * @map_wecowds: the map wecowd pointews fwom bpf->maps_neutwaw
 * @subpwog: pointew to an awway of objects howding info about sub-pwogwams
 * @n_insns: numbew of instwuctions on @insns wist
 * @insns: wist of BPF instwuction wwappews (stwuct nfp_insn_meta)
 */
stwuct nfp_pwog {
	stwuct nfp_app_bpf *bpf;

	u64 *pwog;
	unsigned int pwog_wen;
	unsigned int __pwog_awwoc_wen;

	unsigned int stack_size;

	stwuct nfp_insn_meta *vewifiew_meta;

	enum bpf_pwog_type type;

	unsigned int wast_bpf_off;
	unsigned int tgt_out;
	unsigned int tgt_abowt;
	unsigned int tgt_caww_push_wegs;
	unsigned int tgt_caww_pop_wegs;

	unsigned int n_twanswated;
	int ewwow;

	unsigned int stack_fwame_depth;
	unsigned int adjust_head_wocation;

	unsigned int map_wecowds_cnt;
	unsigned int subpwog_cnt;
	stwuct nfp_bpf_neutwaw_map **map_wecowds;
	stwuct nfp_bpf_subpwog_info *subpwog;

	unsigned int n_insns;
	stwuct wist_head insns;
};

/**
 * stwuct nfp_bpf_vnic - pew-vNIC BPF pwiv stwuctuwe
 * @tc_pwog:	cuwwentwy woaded cws_bpf pwogwam
 * @stawt_off:	addwess of the fiwst instwuction in the memowy
 * @tgt_done:	jump tawget to get the next packet
 */
stwuct nfp_bpf_vnic {
	stwuct bpf_pwog *tc_pwog;
	unsigned int stawt_off;
	unsigned int tgt_done;
};

boow nfp_is_subpwog_stawt(stwuct nfp_insn_meta *meta);
void nfp_bpf_jit_pwepawe(stwuct nfp_pwog *nfp_pwog);
int nfp_bpf_jit(stwuct nfp_pwog *pwog);
boow nfp_bpf_suppowted_opcode(u8 code);
boow nfp_bpf_offwoad_check_mtu(stwuct nfp_net *nn, stwuct bpf_pwog *pwog,
			       unsigned int mtu);

int nfp_vewify_insn(stwuct bpf_vewifiew_env *env, int insn_idx,
		    int pwev_insn_idx);
int nfp_bpf_finawize(stwuct bpf_vewifiew_env *env);

int nfp_bpf_opt_wepwace_insn(stwuct bpf_vewifiew_env *env, u32 off,
			     stwuct bpf_insn *insn);
int nfp_bpf_opt_wemove_insns(stwuct bpf_vewifiew_env *env, u32 off, u32 cnt);

extewn const stwuct bpf_pwog_offwoad_ops nfp_bpf_dev_ops;

stwuct netdev_bpf;
stwuct nfp_app;
stwuct nfp_net;

int nfp_ndo_bpf(stwuct nfp_app *app, stwuct nfp_net *nn,
		stwuct netdev_bpf *bpf);
int nfp_net_bpf_offwoad(stwuct nfp_net *nn, stwuct bpf_pwog *pwog,
			boow owd_pwog, stwuct netwink_ext_ack *extack);

stwuct nfp_insn_meta *
nfp_bpf_goto_meta(stwuct nfp_pwog *nfp_pwog, stwuct nfp_insn_meta *meta,
		  unsigned int insn_idx);

void *nfp_bpf_wewo_fow_vnic(stwuct nfp_pwog *nfp_pwog, stwuct nfp_bpf_vnic *bv);

unsigned int nfp_bpf_ctww_cmsg_min_mtu(stwuct nfp_app_bpf *bpf);
unsigned int nfp_bpf_ctww_cmsg_mtu(stwuct nfp_app_bpf *bpf);
unsigned int nfp_bpf_ctww_cmsg_cache_cnt(stwuct nfp_app_bpf *bpf);
wong wong int
nfp_bpf_ctww_awwoc_map(stwuct nfp_app_bpf *bpf, stwuct bpf_map *map);
void
nfp_bpf_ctww_fwee_map(stwuct nfp_app_bpf *bpf, stwuct nfp_bpf_map *nfp_map);
int nfp_bpf_ctww_getfiwst_entwy(stwuct bpf_offwoaded_map *offmap,
				void *next_key);
int nfp_bpf_ctww_update_entwy(stwuct bpf_offwoaded_map *offmap,
			      void *key, void *vawue, u64 fwags);
int nfp_bpf_ctww_dew_entwy(stwuct bpf_offwoaded_map *offmap, void *key);
int nfp_bpf_ctww_wookup_entwy(stwuct bpf_offwoaded_map *offmap,
			      void *key, void *vawue);
int nfp_bpf_ctww_getnext_entwy(stwuct bpf_offwoaded_map *offmap,
			       void *key, void *next_key);

int nfp_bpf_event_output(stwuct nfp_app_bpf *bpf, const void *data,
			 unsigned int wen);

void nfp_bpf_ctww_msg_wx(stwuct nfp_app *app, stwuct sk_buff *skb);
void
nfp_bpf_ctww_msg_wx_waw(stwuct nfp_app *app, const void *data,
			unsigned int wen);
#endif
