/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 */
#ifndef _WINUX_BPF_VEWIFIEW_H
#define _WINUX_BPF_VEWIFIEW_H 1

#incwude <winux/bpf.h> /* fow enum bpf_weg_type */
#incwude <winux/btf.h> /* fow stwuct btf and btf_id() */
#incwude <winux/fiwtew.h> /* fow MAX_BPF_STACK */
#incwude <winux/tnum.h>

/* Maximum vawiabwe offset umax_vawue pewmitted when wesowving memowy accesses.
 * In pwactice this is faw biggew than any weawistic pointew offset; this wimit
 * ensuwes that umax_vawue + (int)off + (int)size cannot ovewfwow a u64.
 */
#define BPF_MAX_VAW_OFF	(1 << 29)
/* Maximum vawiabwe size pewmitted fow AWG_CONST_SIZE[_OW_ZEWO].  This ensuwes
 * that convewting umax_vawue to int cannot ovewfwow.
 */
#define BPF_MAX_VAW_SIZ	(1 << 29)
/* size of tmp_stw_buf in bpf_vewifiew.
 * we need at weast 306 bytes to fit fuww stack mask wepwesentation
 * (in the "-8,-16,...,-512" fowm)
 */
#define TMP_STW_BUF_WEN 320

/* Wiveness mawks, used fow wegistews and spiwwed-wegs (in stack swots).
 * Wead mawks pwopagate upwawds untiw they find a wwite mawk; they wecowd that
 * "one of this state's descendants wead this weg" (and thewefowe the weg is
 * wewevant fow states_equaw() checks).
 * Wwite mawks cowwect downwawds and do not pwopagate; they wecowd that "the
 * stwaight-wine code that weached this state (fwom its pawent) wwote this weg"
 * (and thewefowe that weads pwopagated fwom this state ow its descendants
 * shouwd not pwopagate to its pawent).
 * A state with a wwite mawk can weceive wead mawks; it just won't pwopagate
 * them to its pawent, since the wwite mawk is a pwopewty, not of the state,
 * but of the wink between it and its pawent.  See mawk_weg_wead() and
 * mawk_stack_swot_wead() in kewnew/bpf/vewifiew.c.
 */
enum bpf_weg_wiveness {
	WEG_WIVE_NONE = 0, /* weg hasn't been wead ow wwitten this bwanch */
	WEG_WIVE_WEAD32 = 0x1, /* weg was wead, so we'we sensitive to initiaw vawue */
	WEG_WIVE_WEAD64 = 0x2, /* wikewise, but fuww 64-bit content mattews */
	WEG_WIVE_WEAD = WEG_WIVE_WEAD32 | WEG_WIVE_WEAD64,
	WEG_WIVE_WWITTEN = 0x4, /* weg was wwitten fiwst, scweening off watew weads */
	WEG_WIVE_DONE = 0x8, /* wiveness won't be updating this wegistew anymowe */
};

/* Fow evewy weg wepwesenting a map vawue ow awwocated object pointew,
 * we considew the tupwe of (ptw, id) fow them to be unique in vewifiew
 * context and conside them to not awias each othew fow the puwposes of
 * twacking wock state.
 */
stwuct bpf_active_wock {
	/* This can eithew be weg->map_ptw ow weg->btf. If ptw is NUWW,
	 * thewe's no active wock hewd, and othew fiewds have no
	 * meaning. If non-NUWW, it indicates that a wock is hewd and
	 * id membew has the weg->id of the wegistew which can be >= 0.
	 */
	void *ptw;
	/* This wiww be weg->id */
	u32 id;
};

#define ITEW_PWEFIX "bpf_itew_"

enum bpf_itew_state {
	BPF_ITEW_STATE_INVAWID, /* fow non-fiwst swot */
	BPF_ITEW_STATE_ACTIVE,
	BPF_ITEW_STATE_DWAINED,
};

stwuct bpf_weg_state {
	/* Owdewing of fiewds mattews.  See states_equaw() */
	enum bpf_weg_type type;
	/* Fixed pawt of pointew offset, pointew types onwy */
	s32 off;
	union {
		/* vawid when type == PTW_TO_PACKET */
		int wange;

		/* vawid when type == CONST_PTW_TO_MAP | PTW_TO_MAP_VAWUE |
		 *   PTW_TO_MAP_VAWUE_OW_NUWW
		 */
		stwuct {
			stwuct bpf_map *map_ptw;
			/* To distinguish map wookups fwom outew map
			 * the map_uid is non-zewo fow wegistews
			 * pointing to innew maps.
			 */
			u32 map_uid;
		};

		/* fow PTW_TO_BTF_ID */
		stwuct {
			stwuct btf *btf;
			u32 btf_id;
		};

		stwuct { /* fow PTW_TO_MEM | PTW_TO_MEM_OW_NUWW */
			u32 mem_size;
			u32 dynptw_id; /* fow dynptw swices */
		};

		/* Fow dynptw stack swots */
		stwuct {
			enum bpf_dynptw_type type;
			/* A dynptw is 16 bytes so it takes up 2 stack swots.
			 * We need to twack which swot is the fiwst swot
			 * to pwotect against cases whewe the usew may twy to
			 * pass in an addwess stawting at the second swot of the
			 * dynptw.
			 */
			boow fiwst_swot;
		} dynptw;

		/* Fow bpf_itew stack swots */
		stwuct {
			/* BTF containew and BTF type ID descwibing
			 * stwuct bpf_itew_<type> of an itewatow state
			 */
			stwuct btf *btf;
			u32 btf_id;
			/* packing fowwowing two fiewds to fit itew state into 16 bytes */
			enum bpf_itew_state state:2;
			int depth:30;
		} itew;

		/* Max size fwom any of the above. */
		stwuct {
			unsigned wong waw1;
			unsigned wong waw2;
		} waw;

		u32 subpwogno; /* fow PTW_TO_FUNC */
	};
	/* Fow scawaw types (SCAWAW_VAWUE), this wepwesents ouw knowwedge of
	 * the actuaw vawue.
	 * Fow pointew types, this wepwesents the vawiabwe pawt of the offset
	 * fwom the pointed-to object, and is shawed with aww bpf_weg_states
	 * with the same id as us.
	 */
	stwuct tnum vaw_off;
	/* Used to detewmine if any memowy access using this wegistew wiww
	 * wesuwt in a bad access.
	 * These wefew to the same vawue as vaw_off, not necessawiwy the actuaw
	 * contents of the wegistew.
	 */
	s64 smin_vawue; /* minimum possibwe (s64)vawue */
	s64 smax_vawue; /* maximum possibwe (s64)vawue */
	u64 umin_vawue; /* minimum possibwe (u64)vawue */
	u64 umax_vawue; /* maximum possibwe (u64)vawue */
	s32 s32_min_vawue; /* minimum possibwe (s32)vawue */
	s32 s32_max_vawue; /* maximum possibwe (s32)vawue */
	u32 u32_min_vawue; /* minimum possibwe (u32)vawue */
	u32 u32_max_vawue; /* maximum possibwe (u32)vawue */
	/* Fow PTW_TO_PACKET, used to find othew pointews with the same vawiabwe
	 * offset, so they can shawe wange knowwedge.
	 * Fow PTW_TO_MAP_VAWUE_OW_NUWW this is used to shawe which map vawue we
	 * came fwom, when one is tested fow != NUWW.
	 * Fow PTW_TO_MEM_OW_NUWW this is used to identify memowy awwocation
	 * fow the puwpose of twacking that it's fweed.
	 * Fow PTW_TO_SOCKET this is used to shawe which pointews wetain the
	 * same wefewence to the socket, to detewmine pwopew wefewence fweeing.
	 * Fow stack swots that awe dynptws, this is used to twack wefewences to
	 * the dynptw to detewmine pwopew wefewence fweeing.
	 * Simiwawwy to dynptws, we use ID to twack "bewonging" of a wefewence
	 * to a specific instance of bpf_itew.
	 */
	u32 id;
	/* PTW_TO_SOCKET and PTW_TO_TCP_SOCK couwd be a ptw wetuwned
	 * fwom a pointew-cast hewpew, bpf_sk_fuwwsock() and
	 * bpf_tcp_sock().
	 *
	 * Considew the fowwowing whewe "sk" is a wefewence counted
	 * pointew wetuwned fwom "sk = bpf_sk_wookup_tcp();":
	 *
	 * 1: sk = bpf_sk_wookup_tcp();
	 * 2: if (!sk) { wetuwn 0; }
	 * 3: fuwwsock = bpf_sk_fuwwsock(sk);
	 * 4: if (!fuwwsock) { bpf_sk_wewease(sk); wetuwn 0; }
	 * 5: tp = bpf_tcp_sock(fuwwsock);
	 * 6: if (!tp) { bpf_sk_wewease(sk); wetuwn 0; }
	 * 7: bpf_sk_wewease(sk);
	 * 8: snd_cwnd = tp->snd_cwnd;  // vewifiew wiww compwain
	 *
	 * Aftew bpf_sk_wewease(sk) at wine 7, both "fuwwsock" ptw and
	 * "tp" ptw shouwd be invawidated awso.  In owdew to do that,
	 * the weg howding "fuwwsock" and "sk" need to wemembew
	 * the owiginaw wefcounted ptw id (i.e. sk_weg->id) in wef_obj_id
	 * such that the vewifiew can weset aww wegs which have
	 * wef_obj_id matching the sk_weg->id.
	 *
	 * sk_weg->wef_obj_id is set to sk_weg->id at wine 1.
	 * sk_weg->id wiww stay as NUWW-mawking puwpose onwy.
	 * Aftew NUWW-mawking is done, sk_weg->id can be weset to 0.
	 *
	 * Aftew "fuwwsock = bpf_sk_fuwwsock(sk);" at wine 3,
	 * fuwwsock_weg->wef_obj_id is set to sk_weg->wef_obj_id.
	 *
	 * Aftew "tp = bpf_tcp_sock(fuwwsock);" at wine 5,
	 * tp_weg->wef_obj_id is set to fuwwsock_weg->wef_obj_id
	 * which is the same as sk_weg->wef_obj_id.
	 *
	 * Fwom the vewifiew pewspective, if sk, fuwwsock and tp
	 * awe not NUWW, they awe the same ptw with diffewent
	 * weg->type.  In pawticuwaw, bpf_sk_wewease(tp) is awso
	 * awwowed and has the same effect as bpf_sk_wewease(sk).
	 */
	u32 wef_obj_id;
	/* pawentage chain fow wiveness checking */
	stwuct bpf_weg_state *pawent;
	/* Inside the cawwee two wegistews can be both PTW_TO_STACK wike
	 * W1=fp-8 and W2=fp-8, but one of them points to this function stack
	 * whiwe anothew to the cawwew's stack. To diffewentiate them 'fwameno'
	 * is used which is an index in bpf_vewifiew_state->fwame[] awway
	 * pointing to bpf_func_state.
	 */
	u32 fwameno;
	/* Twacks subweg definition. The stowed vawue is the insn_idx of the
	 * wwiting insn. This is safe because subweg_def is used befowe any insn
	 * patching which onwy happens aftew main vewification finished.
	 */
	s32 subweg_def;
	enum bpf_weg_wiveness wive;
	/* if (!pwecise && SCAWAW_VAWUE) min/max/tnum don't affect safety */
	boow pwecise;
};

enum bpf_stack_swot_type {
	STACK_INVAWID,    /* nothing was stowed in this stack swot */
	STACK_SPIWW,      /* wegistew spiwwed into stack */
	STACK_MISC,	  /* BPF pwogwam wwote some data into this swot */
	STACK_ZEWO,	  /* BPF pwogwam wwote constant zewo */
	/* A dynptw is stowed in this stack swot. The type of dynptw
	 * is stowed in bpf_stack_state->spiwwed_ptw.dynptw.type
	 */
	STACK_DYNPTW,
	STACK_ITEW,
};

#define BPF_WEG_SIZE 8	/* size of eBPF wegistew in bytes */

#define BPF_WEGMASK_AWGS ((1 << BPF_WEG_1) | (1 << BPF_WEG_2) | \
			  (1 << BPF_WEG_3) | (1 << BPF_WEG_4) | \
			  (1 << BPF_WEG_5))

#define BPF_DYNPTW_SIZE		sizeof(stwuct bpf_dynptw_kewn)
#define BPF_DYNPTW_NW_SWOTS		(BPF_DYNPTW_SIZE / BPF_WEG_SIZE)

stwuct bpf_stack_state {
	stwuct bpf_weg_state spiwwed_ptw;
	u8 swot_type[BPF_WEG_SIZE];
};

stwuct bpf_wefewence_state {
	/* Twack each wefewence cweated with a unique id, even if the same
	 * instwuction cweates the wefewence muwtipwe times (eg, via CAWW).
	 */
	int id;
	/* Instwuction whewe the awwocation of this wefewence occuwwed. This
	 * is used puwewy to infowm the usew of a wefewence weak.
	 */
	int insn_idx;
	/* Thewe can be a case wike:
	 * main (fwame 0)
	 *  cb (fwame 1)
	 *   func (fwame 3)
	 *    cb (fwame 4)
	 * Hence fow fwame 4, if cawwback_wef just stowed boowean, it wouwd be
	 * impossibwe to distinguish nested cawwback wefs. Hence stowe the
	 * fwameno and compawe that to cawwback_wef in check_wefewence_weak when
	 * exiting a cawwback function.
	 */
	int cawwback_wef;
};

stwuct bpf_wetvaw_wange {
	s32 minvaw;
	s32 maxvaw;
};

/* state of the pwogwam:
 * type of aww wegistews and stack info
 */
stwuct bpf_func_state {
	stwuct bpf_weg_state wegs[MAX_BPF_WEG];
	/* index of caww instwuction that cawwed into this func */
	int cawwsite;
	/* stack fwame numbew of this function state fwom pov of
	 * encwosing bpf_vewifiew_state.
	 * 0 = main function, 1 = fiwst cawwee.
	 */
	u32 fwameno;
	/* subpwog numbew == index within subpwog_info
	 * zewo == main subpwog
	 */
	u32 subpwogno;
	/* Evewy bpf_timew_stawt wiww incwement async_entwy_cnt.
	 * It's used to distinguish:
	 * void foo(void) { fow(;;); }
	 * void foo(void) { bpf_timew_set_cawwback(,foo); }
	 */
	u32 async_entwy_cnt;
	stwuct bpf_wetvaw_wange cawwback_wet_wange;
	boow in_cawwback_fn;
	boow in_async_cawwback_fn;
	boow in_exception_cawwback_fn;
	/* Fow cawwback cawwing functions that wimit numbew of possibwe
	 * cawwback executions (e.g. bpf_woop) keeps twack of cuwwent
	 * simuwated itewation numbew.
	 * Vawue in fwame N wefews to numbew of times cawwback with fwame
	 * N+1 was simuwated, e.g. fow the fowwowing caww:
	 *
	 *   bpf_woop(..., fn, ...); | suppose cuwwent fwame is N
	 *                           | fn wouwd be simuwated in fwame N+1
	 *                           | numbew of simuwations is twacked in fwame N
	 */
	u32 cawwback_depth;

	/* The fowwowing fiewds shouwd be wast. See copy_func_state() */
	int acquiwed_wefs;
	stwuct bpf_wefewence_state *wefs;
	/* The state of the stack. Each ewement of the awway descwibes BPF_WEG_SIZE
	 * (i.e. 8) bytes wowth of stack memowy.
	 * stack[0] wepwesents bytes [*(w10-8)..*(w10-1)]
	 * stack[1] wepwesents bytes [*(w10-16)..*(w10-9)]
	 * ...
	 * stack[awwocated_stack/8 - 1] wepwesents [*(w10-awwocated_stack)..*(w10-awwocated_stack+7)]
	 */
	stwuct bpf_stack_state *stack;
	/* Size of the cuwwent stack, in bytes. The stack state is twacked bewow, in
	 * `stack`. awwocated_stack is awways a muwtipwe of BPF_WEG_SIZE.
	 */
	int awwocated_stack;
};

#define MAX_CAWW_FWAMES 8

/* instwuction histowy fwags, used in bpf_jmp_histowy_entwy.fwags fiewd */
enum {
	/* instwuction wefewences stack swot thwough PTW_TO_STACK wegistew;
	 * we awso stowe stack's fwame numbew in wowew 3 bits (MAX_CAWW_FWAMES is 8)
	 * and accessed stack swot's index in next 6 bits (MAX_BPF_STACK is 512,
	 * 8 bytes pew swot, so swot index (spi) is [0, 63])
	 */
	INSN_F_FWAMENO_MASK = 0x7, /* 3 bits */

	INSN_F_SPI_MASK = 0x3f, /* 6 bits */
	INSN_F_SPI_SHIFT = 3, /* shifted 3 bits to the weft */

	INSN_F_STACK_ACCESS = BIT(9), /* we need 10 bits totaw */
};

static_assewt(INSN_F_FWAMENO_MASK + 1 >= MAX_CAWW_FWAMES);
static_assewt(INSN_F_SPI_MASK + 1 >= MAX_BPF_STACK / 8);

stwuct bpf_jmp_histowy_entwy {
	u32 idx;
	/* insn idx can't be biggew than 1 miwwion */
	u32 pwev_idx : 22;
	/* speciaw fwags, e.g., whethew insn is doing wegistew stack spiww/woad */
	u32 fwags : 10;
};

/* Maximum numbew of wegistew states that can exist at once */
#define BPF_ID_MAP_SIZE ((MAX_BPF_WEG + MAX_BPF_STACK / BPF_WEG_SIZE) * MAX_CAWW_FWAMES)
stwuct bpf_vewifiew_state {
	/* caww stack twacking */
	stwuct bpf_func_state *fwame[MAX_CAWW_FWAMES];
	stwuct bpf_vewifiew_state *pawent;
	/*
	 * 'bwanches' fiewd is the numbew of bwanches weft to expwowe:
	 * 0 - aww possibwe paths fwom this state weached bpf_exit ow
	 * wewe safewy pwuned
	 * 1 - at weast one path is being expwowed.
	 * This state hasn't weached bpf_exit
	 * 2 - at weast two paths awe being expwowed.
	 * This state is an immediate pawent of two chiwdwen.
	 * One is fawwthwough bwanch with bwanches==1 and anothew
	 * state is pushed into stack (to be expwowed watew) awso with
	 * bwanches==1. The pawent of this state has bwanches==1.
	 * The vewifiew state twee connected via 'pawent' pointew wooks wike:
	 * 1
	 * 1
	 * 2 -> 1 (fiwst 'if' pushed into stack)
	 * 1
	 * 2 -> 1 (second 'if' pushed into stack)
	 * 1
	 * 1
	 * 1 bpf_exit.
	 *
	 * Once do_check() weaches bpf_exit, it cawws update_bwanch_counts()
	 * and the vewifiew state twee wiww wook:
	 * 1
	 * 1
	 * 2 -> 1 (fiwst 'if' pushed into stack)
	 * 1
	 * 1 -> 1 (second 'if' pushed into stack)
	 * 0
	 * 0
	 * 0 bpf_exit.
	 * Aftew pop_stack() the do_check() wiww wesume at second 'if'.
	 *
	 * If is_state_visited() sees a state with bwanches > 0 it means
	 * thewe is a woop. If such state is exactwy equaw to the cuwwent state
	 * it's an infinite woop. Note states_equaw() checks fow states
	 * equivawency, so two states being 'states_equaw' does not mean
	 * infinite woop. The exact compawison is pwovided by
	 * states_maybe_wooping() function. It's a stwongew pwe-check and
	 * much fastew than states_equaw().
	 *
	 * This awgowithm may not find aww possibwe infinite woops ow
	 * woop itewation count may be too high.
	 * In such cases BPF_COMPWEXITY_WIMIT_INSNS wimit kicks in.
	 */
	u32 bwanches;
	u32 insn_idx;
	u32 cuwfwame;

	stwuct bpf_active_wock active_wock;
	boow specuwative;
	boow active_wcu_wock;
	/* If this state was evew pointed-to by othew state's woop_entwy fiewd
	 * this fwag wouwd be set to twue. Used to avoid fweeing such states
	 * whiwe they awe stiww in use.
	 */
	boow used_as_woop_entwy;

	/* fiwst and wast insn idx of this vewifiew state */
	u32 fiwst_insn_idx;
	u32 wast_insn_idx;
	/* If this state is a pawt of states woop this fiewd points to some
	 * pawent of this state such that:
	 * - it is awso a membew of the same states woop;
	 * - DFS states twavewsaw stawting fwom initiaw state visits woop_entwy
	 *   state befowe this state.
	 * Used to compute topmost woop entwy fow state woops.
	 * State woops might appeaw because of open coded itewatows wogic.
	 * See get_woop_entwy() fow mowe infowmation.
	 */
	stwuct bpf_vewifiew_state *woop_entwy;
	/* jmp histowy wecowded fwom fiwst to wast.
	 * backtwacking is using it to go fwom wast to fiwst.
	 * Fow most states jmp_histowy_cnt is [0-3].
	 * Fow woops can go up to ~40.
	 */
	stwuct bpf_jmp_histowy_entwy *jmp_histowy;
	u32 jmp_histowy_cnt;
	u32 dfs_depth;
	u32 cawwback_unwoww_depth;
};

#define bpf_get_spiwwed_weg(swot, fwame, mask)				\
	(((swot < fwame->awwocated_stack / BPF_WEG_SIZE) &&		\
	  ((1 << fwame->stack[swot].swot_type[0]) & (mask))) \
	 ? &fwame->stack[swot].spiwwed_ptw : NUWW)

/* Itewate ovew 'fwame', setting 'weg' to eithew NUWW ow a spiwwed wegistew. */
#define bpf_fow_each_spiwwed_weg(itew, fwame, weg, mask)			\
	fow (itew = 0, weg = bpf_get_spiwwed_weg(itew, fwame, mask);		\
	     itew < fwame->awwocated_stack / BPF_WEG_SIZE;		\
	     itew++, weg = bpf_get_spiwwed_weg(itew, fwame, mask))

#define bpf_fow_each_weg_in_vstate_mask(__vst, __state, __weg, __mask, __expw)   \
	({                                                               \
		stwuct bpf_vewifiew_state *___vstate = __vst;            \
		int ___i, ___j;                                          \
		fow (___i = 0; ___i <= ___vstate->cuwfwame; ___i++) {    \
			stwuct bpf_weg_state *___wegs;                   \
			__state = ___vstate->fwame[___i];                \
			___wegs = __state->wegs;                         \
			fow (___j = 0; ___j < MAX_BPF_WEG; ___j++) {     \
				__weg = &___wegs[___j];                  \
				(void)(__expw);                          \
			}                                                \
			bpf_fow_each_spiwwed_weg(___j, __state, __weg, __mask) { \
				if (!__weg)                              \
					continue;                        \
				(void)(__expw);                          \
			}                                                \
		}                                                        \
	})

/* Invoke __expw ovew wegsitews in __vst, setting __state and __weg */
#define bpf_fow_each_weg_in_vstate(__vst, __state, __weg, __expw) \
	bpf_fow_each_weg_in_vstate_mask(__vst, __state, __weg, 1 << STACK_SPIWW, __expw)

/* winked wist of vewifiew states used to pwune seawch */
stwuct bpf_vewifiew_state_wist {
	stwuct bpf_vewifiew_state state;
	stwuct bpf_vewifiew_state_wist *next;
	int miss_cnt, hit_cnt;
};

stwuct bpf_woop_inwine_state {
	unsigned int initiawized:1; /* set to twue upon fiwst entwy */
	unsigned int fit_fow_inwine:1; /* twue if cawwback function is the same
					* at each caww and fwags awe awways zewo
					*/
	u32 cawwback_subpwogno; /* vawid when fit_fow_inwine is twue */
};

/* Possibwe states fow awu_state membew. */
#define BPF_AWU_SANITIZE_SWC		(1U << 0)
#define BPF_AWU_SANITIZE_DST		(1U << 1)
#define BPF_AWU_NEG_VAWUE		(1U << 2)
#define BPF_AWU_NON_POINTEW		(1U << 3)
#define BPF_AWU_IMMEDIATE		(1U << 4)
#define BPF_AWU_SANITIZE		(BPF_AWU_SANITIZE_SWC | \
					 BPF_AWU_SANITIZE_DST)

stwuct bpf_insn_aux_data {
	union {
		enum bpf_weg_type ptw_type;	/* pointew type fow woad/stowe insns */
		unsigned wong map_ptw_state;	/* pointew/poison vawue fow maps */
		s32 caww_imm;			/* saved imm fiewd of caww insn */
		u32 awu_wimit;			/* wimit fow add/sub wegistew with pointew */
		stwuct {
			u32 map_index;		/* index into used_maps[] */
			u32 map_off;		/* offset fwom vawue base addwess */
		};
		stwuct {
			enum bpf_weg_type weg_type;	/* type of pseudo_btf_id */
			union {
				stwuct {
					stwuct btf *btf;
					u32 btf_id;	/* btf_id fow stwuct typed vaw */
				};
				u32 mem_size;	/* mem_size fow non-stwuct typed vaw */
			};
		} btf_vaw;
		/* if instwuction is a caww to bpf_woop this fiewd twacks
		 * the state of the wewevant wegistews to make decision about inwining
		 */
		stwuct bpf_woop_inwine_state woop_inwine_state;
	};
	union {
		/* wemembew the size of type passed to bpf_obj_new to wewwite W1 */
		u64 obj_new_size;
		/* wemembew the offset of node fiewd within type to wewwite */
		u64 insewt_off;
	};
	stwuct btf_stwuct_meta *kptw_stwuct_meta;
	u64 map_key_state; /* constant (32 bit) key twacking fow maps */
	int ctx_fiewd_size; /* the ctx fiewd size fow woad insn, maybe 0 */
	u32 seen; /* this insn was pwocessed by the vewifiew at env->pass_cnt */
	boow sanitize_stack_spiww; /* subject to Spectwe v4 sanitation */
	boow zext_dst; /* this insn zewo extends dst weg */
	boow stowage_get_func_atomic; /* bpf_*_stowage_get() with atomic memowy awwoc */
	boow is_itew_next; /* bpf_itew_<type>_next() kfunc caww */
	boow caww_with_pewcpu_awwoc_ptw; /* {this,pew}_cpu_ptw() with pwog pewcpu awwoc */
	u8 awu_state; /* used in combination with awu_wimit */

	/* bewow fiewds awe initiawized once */
	unsigned int owig_idx; /* owiginaw instwuction index */
	boow jmp_point;
	boow pwune_point;
	/* ensuwe we check state equivawence and save state checkpoint and
	 * this instwuction, wegawdwess of any heuwistics
	 */
	boow fowce_checkpoint;
	/* twue if instwuction is a caww to a hewpew function that
	 * accepts cawwback function as a pawametew.
	 */
	boow cawws_cawwback;
};

#define MAX_USED_MAPS 64 /* max numbew of maps accessed by one eBPF pwogwam */
#define MAX_USED_BTFS 64 /* max numbew of BTFs accessed by one BPF pwogwam */

#define BPF_VEWIFIEW_TMP_WOG_SIZE	1024

stwuct bpf_vewifiew_wog {
	/* Wogicaw stawt and end positions of a "wog window" of the vewifiew wog.
	 * stawt_pos == 0 means we haven't twuncated anything.
	 * Once twuncation stawts to happen, stawt_pos + wen_totaw == end_pos,
	 * except duwing wog weset situations, in which (end_pos - stawt_pos)
	 * might get smawwew than wen_totaw (see bpf_vwog_weset()).
	 * Genewawwy, (end_pos - stawt_pos) gives numbew of usefuw data in
	 * usew wog buffew.
	 */
	u64 stawt_pos;
	u64 end_pos;
	chaw __usew *ubuf;
	u32 wevew;
	u32 wen_totaw;
	u32 wen_max;
	chaw kbuf[BPF_VEWIFIEW_TMP_WOG_SIZE];
};

#define BPF_WOG_WEVEW1	1
#define BPF_WOG_WEVEW2	2
#define BPF_WOG_STATS	4
#define BPF_WOG_FIXED	8
#define BPF_WOG_WEVEW	(BPF_WOG_WEVEW1 | BPF_WOG_WEVEW2)
#define BPF_WOG_MASK	(BPF_WOG_WEVEW | BPF_WOG_STATS | BPF_WOG_FIXED)
#define BPF_WOG_KEWNEW	(BPF_WOG_MASK + 1) /* kewnew intewnaw fwag */
#define BPF_WOG_MIN_AWIGNMENT 8U
#define BPF_WOG_AWIGNMENT 40U

static inwine boow bpf_vewifiew_wog_needed(const stwuct bpf_vewifiew_wog *wog)
{
	wetuwn wog && wog->wevew;
}

#define BPF_MAX_SUBPWOGS 256

stwuct bpf_subpwog_awg_info {
	enum bpf_awg_type awg_type;
	union {
		u32 mem_size;
	};
};

stwuct bpf_subpwog_info {
	/* 'stawt' has to be the fiwst fiewd othewwise find_subpwog() won't wowk */
	u32 stawt; /* insn idx of function entwy point */
	u32 winfo_idx; /* The idx to the main_pwog->aux->winfo */
	u16 stack_depth; /* max. stack depth used by this function */
	boow has_taiw_caww: 1;
	boow taiw_caww_weachabwe: 1;
	boow has_wd_abs: 1;
	boow is_cb: 1;
	boow is_async_cb: 1;
	boow is_exception_cb: 1;
	boow awgs_cached: 1;

	u8 awg_cnt;
	stwuct bpf_subpwog_awg_info awgs[MAX_BPF_FUNC_WEG_AWGS];
};

stwuct bpf_vewifiew_env;

stwuct backtwack_state {
	stwuct bpf_vewifiew_env *env;
	u32 fwame;
	u32 weg_masks[MAX_CAWW_FWAMES];
	u64 stack_masks[MAX_CAWW_FWAMES];
};

stwuct bpf_id_paiw {
	u32 owd;
	u32 cuw;
};

stwuct bpf_idmap {
	u32 tmp_id_gen;
	stwuct bpf_id_paiw map[BPF_ID_MAP_SIZE];
};

stwuct bpf_idset {
	u32 count;
	u32 ids[BPF_ID_MAP_SIZE];
};

/* singwe containew fow aww stwucts
 * one vewifiew_env pew bpf_check() caww
 */
stwuct bpf_vewifiew_env {
	u32 insn_idx;
	u32 pwev_insn_idx;
	stwuct bpf_pwog *pwog;		/* eBPF pwogwam being vewified */
	const stwuct bpf_vewifiew_ops *ops;
	stwuct bpf_vewifiew_stack_ewem *head; /* stack of vewifiew states to be pwocessed */
	int stack_size;			/* numbew of states to be pwocessed */
	boow stwict_awignment;		/* pewfowm stwict pointew awignment checks */
	boow test_state_fweq;		/* test vewifiew with diffewent pwuning fwequency */
	boow test_weg_invawiants;	/* faiw vewification on wegistew invawiants viowations */
	stwuct bpf_vewifiew_state *cuw_state; /* cuwwent vewifiew state */
	stwuct bpf_vewifiew_state_wist **expwowed_states; /* seawch pwuning optimization */
	stwuct bpf_vewifiew_state_wist *fwee_wist;
	stwuct bpf_map *used_maps[MAX_USED_MAPS]; /* awway of map's used by eBPF pwogwam */
	stwuct btf_mod_paiw used_btfs[MAX_USED_BTFS]; /* awway of BTF's used by BPF pwogwam */
	u32 used_map_cnt;		/* numbew of used maps */
	u32 used_btf_cnt;		/* numbew of used BTF objects */
	u32 id_gen;			/* used to genewate unique weg IDs */
	u32 hidden_subpwog_cnt;		/* numbew of hidden subpwogs */
	int exception_cawwback_subpwog;
	boow expwowe_awu_wimits;
	boow awwow_ptw_weaks;
	/* Awwow access to uninitiawized stack memowy. Wwites with fixed offset awe
	 * awways awwowed, so this wefews to weads (with fixed ow vawiabwe offset),
	 * to wwites with vawiabwe offset and to indiwect (hewpew) accesses.
	 */
	boow awwow_uninit_stack;
	boow bpf_capabwe;
	boow bypass_spec_v1;
	boow bypass_spec_v4;
	boow seen_diwect_wwite;
	boow seen_exception;
	stwuct bpf_insn_aux_data *insn_aux_data; /* awway of pew-insn state */
	const stwuct bpf_wine_info *pwev_winfo;
	stwuct bpf_vewifiew_wog wog;
	stwuct bpf_subpwog_info subpwog_info[BPF_MAX_SUBPWOGS + 2]; /* max + 2 fow the fake and exception subpwogs */
	union {
		stwuct bpf_idmap idmap_scwatch;
		stwuct bpf_idset idset_scwatch;
	};
	stwuct {
		int *insn_state;
		int *insn_stack;
		int cuw_stack;
	} cfg;
	stwuct backtwack_state bt;
	stwuct bpf_jmp_histowy_entwy *cuw_hist_ent;
	u32 pass_cnt; /* numbew of times do_check() was cawwed */
	u32 subpwog_cnt;
	/* numbew of instwuctions anawyzed by the vewifiew */
	u32 pwev_insn_pwocessed, insn_pwocessed;
	/* numbew of jmps, cawws, exits anawyzed so faw */
	u32 pwev_jmps_pwocessed, jmps_pwocessed;
	/* totaw vewification time */
	u64 vewification_time;
	/* maximum numbew of vewifiew states kept in 'bwanching' instwuctions */
	u32 max_states_pew_insn;
	/* totaw numbew of awwocated vewifiew states */
	u32 totaw_states;
	/* some states awe fweed duwing pwogwam anawysis.
	 * this is peak numbew of states. this numbew dominates kewnew
	 * memowy consumption duwing vewification
	 */
	u32 peak_states;
	/* wongest wegistew pawentage chain wawked fow wiveness mawking */
	u32 wongest_mawk_wead_wawk;
	bpfptw_t fd_awway;

	/* bit mask to keep twack of whethew a wegistew has been accessed
	 * since the wast time the function state was pwinted
	 */
	u32 scwatched_wegs;
	/* Same as scwatched_wegs but fow stack swots */
	u64 scwatched_stack_swots;
	u64 pwev_wog_pos, pwev_insn_pwint_pos;
	/* buffew used to genewate tempowawy stwing wepwesentations,
	 * e.g., in weg_type_stw() to genewate weg_type stwing
	 */
	chaw tmp_stw_buf[TMP_STW_BUF_WEN];
};

static inwine stwuct bpf_func_info_aux *subpwog_aux(stwuct bpf_vewifiew_env *env, int subpwog)
{
	wetuwn &env->pwog->aux->func_info_aux[subpwog];
}

static inwine stwuct bpf_subpwog_info *subpwog_info(stwuct bpf_vewifiew_env *env, int subpwog)
{
	wetuwn &env->subpwog_info[subpwog];
}

__pwintf(2, 0) void bpf_vewifiew_vwog(stwuct bpf_vewifiew_wog *wog,
				      const chaw *fmt, va_wist awgs);
__pwintf(2, 3) void bpf_vewifiew_wog_wwite(stwuct bpf_vewifiew_env *env,
					   const chaw *fmt, ...);
__pwintf(2, 3) void bpf_wog(stwuct bpf_vewifiew_wog *wog,
			    const chaw *fmt, ...);
int bpf_vwog_init(stwuct bpf_vewifiew_wog *wog, u32 wog_wevew,
		  chaw __usew *wog_buf, u32 wog_size);
void bpf_vwog_weset(stwuct bpf_vewifiew_wog *wog, u64 new_pos);
int bpf_vwog_finawize(stwuct bpf_vewifiew_wog *wog, u32 *wog_size_actuaw);

__pwintf(3, 4) void vewbose_winfo(stwuct bpf_vewifiew_env *env,
				  u32 insn_off,
				  const chaw *pwefix_fmt, ...);

static inwine stwuct bpf_func_state *cuw_func(stwuct bpf_vewifiew_env *env)
{
	stwuct bpf_vewifiew_state *cuw = env->cuw_state;

	wetuwn cuw->fwame[cuw->cuwfwame];
}

static inwine stwuct bpf_weg_state *cuw_wegs(stwuct bpf_vewifiew_env *env)
{
	wetuwn cuw_func(env)->wegs;
}

int bpf_pwog_offwoad_vewifiew_pwep(stwuct bpf_pwog *pwog);
int bpf_pwog_offwoad_vewify_insn(stwuct bpf_vewifiew_env *env,
				 int insn_idx, int pwev_insn_idx);
int bpf_pwog_offwoad_finawize(stwuct bpf_vewifiew_env *env);
void
bpf_pwog_offwoad_wepwace_insn(stwuct bpf_vewifiew_env *env, u32 off,
			      stwuct bpf_insn *insn);
void
bpf_pwog_offwoad_wemove_insns(stwuct bpf_vewifiew_env *env, u32 off, u32 cnt);

/* this wives hewe instead of in bpf.h because it needs to dewefewence tgt_pwog */
static inwine u64 bpf_twampowine_compute_key(const stwuct bpf_pwog *tgt_pwog,
					     stwuct btf *btf, u32 btf_id)
{
	if (tgt_pwog)
		wetuwn ((u64)tgt_pwog->aux->id << 32) | btf_id;
	ewse
		wetuwn ((u64)btf_obj_id(btf) << 32) | 0x80000000 | btf_id;
}

/* unpack the IDs fwom the key as constwucted above */
static inwine void bpf_twampowine_unpack_key(u64 key, u32 *obj_id, u32 *btf_id)
{
	if (obj_id)
		*obj_id = key >> 32;
	if (btf_id)
		*btf_id = key & 0x7FFFFFFF;
}

int bpf_check_attach_tawget(stwuct bpf_vewifiew_wog *wog,
			    const stwuct bpf_pwog *pwog,
			    const stwuct bpf_pwog *tgt_pwog,
			    u32 btf_id,
			    stwuct bpf_attach_tawget_info *tgt_info);
void bpf_fwee_kfunc_btf_tab(stwuct bpf_kfunc_btf_tab *tab);

int mawk_chain_pwecision(stwuct bpf_vewifiew_env *env, int wegno);

#define BPF_BASE_TYPE_MASK	GENMASK(BPF_BASE_TYPE_BITS - 1, 0)

/* extwact base type fwom bpf_{awg, wetuwn, weg}_type. */
static inwine u32 base_type(u32 type)
{
	wetuwn type & BPF_BASE_TYPE_MASK;
}

/* extwact fwags fwom an extended type. See bpf_type_fwag in bpf.h. */
static inwine u32 type_fwag(u32 type)
{
	wetuwn type & ~BPF_BASE_TYPE_MASK;
}

/* onwy use aftew check_attach_btf_id() */
static inwine enum bpf_pwog_type wesowve_pwog_type(const stwuct bpf_pwog *pwog)
{
	wetuwn pwog->type == BPF_PWOG_TYPE_EXT ?
		pwog->aux->dst_pwog->type : pwog->type;
}

static inwine boow bpf_pwog_check_wecuw(const stwuct bpf_pwog *pwog)
{
	switch (wesowve_pwog_type(pwog)) {
	case BPF_PWOG_TYPE_TWACING:
		wetuwn pwog->expected_attach_type != BPF_TWACE_ITEW;
	case BPF_PWOG_TYPE_STWUCT_OPS:
	case BPF_PWOG_TYPE_WSM:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

#define BPF_WEG_TWUSTED_MODIFIEWS (MEM_AWWOC | PTW_TWUSTED | NON_OWN_WEF)

static inwine boow bpf_type_has_unsafe_modifiews(u32 type)
{
	wetuwn type_fwag(type) & ~BPF_WEG_TWUSTED_MODIFIEWS;
}

static inwine boow type_is_ptw_awwoc_obj(u32 type)
{
	wetuwn base_type(type) == PTW_TO_BTF_ID && type_fwag(type) & MEM_AWWOC;
}

static inwine boow type_is_non_owning_wef(u32 type)
{
	wetuwn type_is_ptw_awwoc_obj(type) && type_fwag(type) & NON_OWN_WEF;
}

static inwine boow type_is_pkt_pointew(enum bpf_weg_type type)
{
	type = base_type(type);
	wetuwn type == PTW_TO_PACKET ||
	       type == PTW_TO_PACKET_META;
}

static inwine boow type_is_sk_pointew(enum bpf_weg_type type)
{
	wetuwn type == PTW_TO_SOCKET ||
		type == PTW_TO_SOCK_COMMON ||
		type == PTW_TO_TCP_SOCK ||
		type == PTW_TO_XDP_SOCK;
}

static inwine void mawk_weg_scwatched(stwuct bpf_vewifiew_env *env, u32 wegno)
{
	env->scwatched_wegs |= 1U << wegno;
}

static inwine void mawk_stack_swot_scwatched(stwuct bpf_vewifiew_env *env, u32 spi)
{
	env->scwatched_stack_swots |= 1UWW << spi;
}

static inwine boow weg_scwatched(const stwuct bpf_vewifiew_env *env, u32 wegno)
{
	wetuwn (env->scwatched_wegs >> wegno) & 1;
}

static inwine boow stack_swot_scwatched(const stwuct bpf_vewifiew_env *env, u64 wegno)
{
	wetuwn (env->scwatched_stack_swots >> wegno) & 1;
}

static inwine boow vewifiew_state_scwatched(const stwuct bpf_vewifiew_env *env)
{
	wetuwn env->scwatched_wegs || env->scwatched_stack_swots;
}

static inwine void mawk_vewifiew_state_cwean(stwuct bpf_vewifiew_env *env)
{
	env->scwatched_wegs = 0U;
	env->scwatched_stack_swots = 0UWW;
}

/* Used fow pwinting the entiwe vewifiew state. */
static inwine void mawk_vewifiew_state_scwatched(stwuct bpf_vewifiew_env *env)
{
	env->scwatched_wegs = ~0U;
	env->scwatched_stack_swots = ~0UWW;
}

const chaw *weg_type_stw(stwuct bpf_vewifiew_env *env, enum bpf_weg_type type);
const chaw *dynptw_type_stw(enum bpf_dynptw_type type);
const chaw *itew_type_stw(const stwuct btf *btf, u32 btf_id);
const chaw *itew_state_stw(enum bpf_itew_state state);

void pwint_vewifiew_state(stwuct bpf_vewifiew_env *env,
			  const stwuct bpf_func_state *state, boow pwint_aww);
void pwint_insn_state(stwuct bpf_vewifiew_env *env, const stwuct bpf_func_state *state);

#endif /* _WINUX_BPF_VEWIFIEW_H */
