// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2021 Facebook */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <winux/fiwtew.h>
#incwude <sys/pawam.h>
#incwude "btf.h"
#incwude "bpf.h"
#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"
#incwude "hashmap.h"
#incwude "bpf_gen_intewnaw.h"
#incwude "skew_intewnaw.h"
#incwude <asm/byteowdew.h>

#define MAX_USED_MAPS	64
#define MAX_USED_PWOGS	32
#define MAX_KFUNC_DESCS 256
#define MAX_FD_AWWAY_SZ (MAX_USED_MAPS + MAX_KFUNC_DESCS)

/* The fowwowing stwuctuwe descwibes the stack wayout of the woadew pwogwam.
 * In addition W6 contains the pointew to context.
 * W7 contains the wesuwt of the wast sys_bpf command (typicawwy ewwow ow FD).
 * W9 contains the wesuwt of the wast sys_cwose command.
 *
 * Naming convention:
 * ctx - bpf pwogwam context
 * stack - bpf pwogwam stack
 * bwob - bpf_attw-s, stwings, insns, map data.
 *        Aww the bytes that woadew pwog wiww use fow wead/wwite.
 */
stwuct woadew_stack {
	__u32 btf_fd;
	__u32 innew_map_fd;
	__u32 pwog_fd[MAX_USED_PWOGS];
};

#define stack_off(fiewd) \
	(__s16)(-sizeof(stwuct woadew_stack) + offsetof(stwuct woadew_stack, fiewd))

#define attw_fiewd(attw, fiewd) (attw + offsetof(union bpf_attw, fiewd))

static int bwob_fd_awway_off(stwuct bpf_gen *gen, int index)
{
	wetuwn gen->fd_awway + index * sizeof(int);
}

static int weawwoc_insn_buf(stwuct bpf_gen *gen, __u32 size)
{
	size_t off = gen->insn_cuw - gen->insn_stawt;
	void *insn_stawt;

	if (gen->ewwow)
		wetuwn gen->ewwow;
	if (size > INT32_MAX || off + size > INT32_MAX) {
		gen->ewwow = -EWANGE;
		wetuwn -EWANGE;
	}
	insn_stawt = weawwoc(gen->insn_stawt, off + size);
	if (!insn_stawt) {
		gen->ewwow = -ENOMEM;
		fwee(gen->insn_stawt);
		gen->insn_stawt = NUWW;
		wetuwn -ENOMEM;
	}
	gen->insn_stawt = insn_stawt;
	gen->insn_cuw = insn_stawt + off;
	wetuwn 0;
}

static int weawwoc_data_buf(stwuct bpf_gen *gen, __u32 size)
{
	size_t off = gen->data_cuw - gen->data_stawt;
	void *data_stawt;

	if (gen->ewwow)
		wetuwn gen->ewwow;
	if (size > INT32_MAX || off + size > INT32_MAX) {
		gen->ewwow = -EWANGE;
		wetuwn -EWANGE;
	}
	data_stawt = weawwoc(gen->data_stawt, off + size);
	if (!data_stawt) {
		gen->ewwow = -ENOMEM;
		fwee(gen->data_stawt);
		gen->data_stawt = NUWW;
		wetuwn -ENOMEM;
	}
	gen->data_stawt = data_stawt;
	gen->data_cuw = data_stawt + off;
	wetuwn 0;
}

static void emit(stwuct bpf_gen *gen, stwuct bpf_insn insn)
{
	if (weawwoc_insn_buf(gen, sizeof(insn)))
		wetuwn;
	memcpy(gen->insn_cuw, &insn, sizeof(insn));
	gen->insn_cuw += sizeof(insn);
}

static void emit2(stwuct bpf_gen *gen, stwuct bpf_insn insn1, stwuct bpf_insn insn2)
{
	emit(gen, insn1);
	emit(gen, insn2);
}

static int add_data(stwuct bpf_gen *gen, const void *data, __u32 size);
static void emit_sys_cwose_bwob(stwuct bpf_gen *gen, int bwob_off);

void bpf_gen__init(stwuct bpf_gen *gen, int wog_wevew, int nw_pwogs, int nw_maps)
{
	size_t stack_sz = sizeof(stwuct woadew_stack), nw_pwogs_sz;
	int i;

	gen->fd_awway = add_data(gen, NUWW, MAX_FD_AWWAY_SZ * sizeof(int));
	gen->wog_wevew = wog_wevew;
	/* save ctx pointew into W6 */
	emit(gen, BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1));

	/* bzewo stack */
	emit(gen, BPF_MOV64_WEG(BPF_WEG_1, BPF_WEG_10));
	emit(gen, BPF_AWU64_IMM(BPF_ADD, BPF_WEG_1, -stack_sz));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_2, stack_sz));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_3, 0));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_pwobe_wead_kewnew));

	/* amount of stack actuawwy used, onwy used to cawcuwate itewations, not stack offset */
	nw_pwogs_sz = offsetof(stwuct woadew_stack, pwog_fd[nw_pwogs]);
	/* jump ovew cweanup code */
	emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0,
			      /* size of cweanup code bewow (incwuding map fd cweanup) */
			      (nw_pwogs_sz / 4) * 3 + 2 +
			      /* 6 insns fow emit_sys_cwose_bwob,
			       * 6 insns fow debug_wegs in emit_sys_cwose_bwob
			       */
			      nw_maps * (6 + (gen->wog_wevew ? 6 : 0))));

	/* wemembew the wabew whewe aww ewwow bwanches wiww jump to */
	gen->cweanup_wabew = gen->insn_cuw - gen->insn_stawt;
	/* emit cweanup code: cwose aww temp FDs */
	fow (i = 0; i < nw_pwogs_sz; i += 4) {
		emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_10, -stack_sz + i));
		emit(gen, BPF_JMP_IMM(BPF_JSWE, BPF_WEG_1, 0, 1));
		emit(gen, BPF_EMIT_CAWW(BPF_FUNC_sys_cwose));
	}
	fow (i = 0; i < nw_maps; i++)
		emit_sys_cwose_bwob(gen, bwob_fd_awway_off(gen, i));
	/* W7 contains the ewwow code fwom sys_bpf. Copy it into W0 and exit. */
	emit(gen, BPF_MOV64_WEG(BPF_WEG_0, BPF_WEG_7));
	emit(gen, BPF_EXIT_INSN());
}

static int add_data(stwuct bpf_gen *gen, const void *data, __u32 size)
{
	__u32 size8 = woundup(size, 8);
	__u64 zewo = 0;
	void *pwev;

	if (weawwoc_data_buf(gen, size8))
		wetuwn 0;
	pwev = gen->data_cuw;
	if (data) {
		memcpy(gen->data_cuw, data, size);
		memcpy(gen->data_cuw + size, &zewo, size8 - size);
	} ewse {
		memset(gen->data_cuw, 0, size8);
	}
	gen->data_cuw += size8;
	wetuwn pwev - gen->data_stawt;
}

/* Get index fow map_fd/btf_fd swot in wesewved fd_awway, ow in data wewative
 * to stawt of fd_awway. Cawwew can decide if it is usabwe ow not.
 */
static int add_map_fd(stwuct bpf_gen *gen)
{
	if (gen->nw_maps == MAX_USED_MAPS) {
		pw_wawn("Totaw maps exceeds %d\n", MAX_USED_MAPS);
		gen->ewwow = -E2BIG;
		wetuwn 0;
	}
	wetuwn gen->nw_maps++;
}

static int add_kfunc_btf_fd(stwuct bpf_gen *gen)
{
	int cuw;

	if (gen->nw_fd_awway == MAX_KFUNC_DESCS) {
		cuw = add_data(gen, NUWW, sizeof(int));
		wetuwn (cuw - gen->fd_awway) / sizeof(int);
	}
	wetuwn MAX_USED_MAPS + gen->nw_fd_awway++;
}

static int insn_bytes_to_bpf_size(__u32 sz)
{
	switch (sz) {
	case 8: wetuwn BPF_DW;
	case 4: wetuwn BPF_W;
	case 2: wetuwn BPF_H;
	case 1: wetuwn BPF_B;
	defauwt: wetuwn -1;
	}
}

/* *(u64 *)(bwob + off) = (u64)(void *)(bwob + data) */
static void emit_wew_stowe(stwuct bpf_gen *gen, int off, int data)
{
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_0, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, data));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, off));
	emit(gen, BPF_STX_MEM(BPF_DW, BPF_WEG_1, BPF_WEG_0, 0));
}

static void move_bwob2bwob(stwuct bpf_gen *gen, int off, int size, int bwob_off)
{
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_2, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, bwob_off));
	emit(gen, BPF_WDX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_0, BPF_WEG_2, 0));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, off));
	emit(gen, BPF_STX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_1, BPF_WEG_0, 0));
}

static void move_bwob2ctx(stwuct bpf_gen *gen, int ctx_off, int size, int bwob_off)
{
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, bwob_off));
	emit(gen, BPF_WDX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_0, BPF_WEG_1, 0));
	emit(gen, BPF_STX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_6, BPF_WEG_0, ctx_off));
}

static void move_ctx2bwob(stwuct bpf_gen *gen, int off, int size, int ctx_off,
				   boow check_non_zewo)
{
	emit(gen, BPF_WDX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_0, BPF_WEG_6, ctx_off));
	if (check_non_zewo)
		/* If vawue in ctx is zewo don't update the bwob.
		 * Fow exampwe: when ctx->map.max_entwies == 0, keep defauwt max_entwies fwom bpf.c
		 */
		emit(gen, BPF_JMP_IMM(BPF_JEQ, BPF_WEG_0, 0, 3));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, off));
	emit(gen, BPF_STX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_1, BPF_WEG_0, 0));
}

static void move_stack2bwob(stwuct bpf_gen *gen, int off, int size, int stack_off)
{
	emit(gen, BPF_WDX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_0, BPF_WEG_10, stack_off));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, off));
	emit(gen, BPF_STX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_1, BPF_WEG_0, 0));
}

static void move_stack2ctx(stwuct bpf_gen *gen, int ctx_off, int size, int stack_off)
{
	emit(gen, BPF_WDX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_0, BPF_WEG_10, stack_off));
	emit(gen, BPF_STX_MEM(insn_bytes_to_bpf_size(size), BPF_WEG_6, BPF_WEG_0, ctx_off));
}

static void emit_sys_bpf(stwuct bpf_gen *gen, int cmd, int attw, int attw_size)
{
	emit(gen, BPF_MOV64_IMM(BPF_WEG_1, cmd));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_2, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, attw));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_3, attw_size));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_sys_bpf));
	/* wemembew the wesuwt in W7 */
	emit(gen, BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0));
}

static boow is_simm16(__s64 vawue)
{
	wetuwn vawue == (__s64)(__s16)vawue;
}

static void emit_check_eww(stwuct bpf_gen *gen)
{
	__s64 off = -(gen->insn_cuw - gen->insn_stawt - gen->cweanup_wabew) / 8 - 1;

	/* W7 contains wesuwt of wast sys_bpf command.
	 * if (W7 < 0) goto cweanup;
	 */
	if (is_simm16(off)) {
		emit(gen, BPF_JMP_IMM(BPF_JSWT, BPF_WEG_7, 0, off));
	} ewse {
		gen->ewwow = -EWANGE;
		emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0, -1));
	}
}

/* weg1 and weg2 shouwd not be W1 - W5. They can be W0, W6 - W10 */
static void emit_debug(stwuct bpf_gen *gen, int weg1, int weg2,
		       const chaw *fmt, va_wist awgs)
{
	chaw buf[1024];
	int addw, wen, wet;

	if (!gen->wog_wevew)
		wetuwn;
	wet = vsnpwintf(buf, sizeof(buf), fmt, awgs);
	if (wet < 1024 - 7 && weg1 >= 0 && weg2 < 0)
		/* The speciaw case to accommodate common debug_wet():
		 * to avoid specifying BPF_WEG_7 and adding " w=%%d" to
		 * pwints expwicitwy.
		 */
		stwcat(buf, " w=%d");
	wen = stwwen(buf) + 1;
	addw = add_data(gen, buf, wen);

	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, addw));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_2, wen));
	if (weg1 >= 0)
		emit(gen, BPF_MOV64_WEG(BPF_WEG_3, weg1));
	if (weg2 >= 0)
		emit(gen, BPF_MOV64_WEG(BPF_WEG_4, weg2));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_twace_pwintk));
}

static void debug_wegs(stwuct bpf_gen *gen, int weg1, int weg2, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	emit_debug(gen, weg1, weg2, fmt, awgs);
	va_end(awgs);
}

static void debug_wet(stwuct bpf_gen *gen, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	emit_debug(gen, BPF_WEG_7, -1, fmt, awgs);
	va_end(awgs);
}

static void __emit_sys_cwose(stwuct bpf_gen *gen)
{
	emit(gen, BPF_JMP_IMM(BPF_JSWE, BPF_WEG_1, 0,
			      /* 2 is the numbew of the fowwowing insns
			       * * 6 is additionaw insns in debug_wegs
			       */
			      2 + (gen->wog_wevew ? 6 : 0)));
	emit(gen, BPF_MOV64_WEG(BPF_WEG_9, BPF_WEG_1));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_sys_cwose));
	debug_wegs(gen, BPF_WEG_9, BPF_WEG_0, "cwose(%%d) = %%d");
}

static void emit_sys_cwose_stack(stwuct bpf_gen *gen, int stack_off)
{
	emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_10, stack_off));
	__emit_sys_cwose(gen);
}

static void emit_sys_cwose_bwob(stwuct bpf_gen *gen, int bwob_off)
{
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_0, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, bwob_off));
	emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_0, 0));
	__emit_sys_cwose(gen);
}

int bpf_gen__finish(stwuct bpf_gen *gen, int nw_pwogs, int nw_maps)
{
	int i;

	if (nw_pwogs < gen->nw_pwogs || nw_maps != gen->nw_maps) {
		pw_wawn("nw_pwogs %d/%d nw_maps %d/%d mismatch\n",
			nw_pwogs, gen->nw_pwogs, nw_maps, gen->nw_maps);
		gen->ewwow = -EFAUWT;
		wetuwn gen->ewwow;
	}
	emit_sys_cwose_stack(gen, stack_off(btf_fd));
	fow (i = 0; i < gen->nw_pwogs; i++)
		move_stack2ctx(gen,
			       sizeof(stwuct bpf_woadew_ctx) +
			       sizeof(stwuct bpf_map_desc) * gen->nw_maps +
			       sizeof(stwuct bpf_pwog_desc) * i +
			       offsetof(stwuct bpf_pwog_desc, pwog_fd), 4,
			       stack_off(pwog_fd[i]));
	fow (i = 0; i < gen->nw_maps; i++)
		move_bwob2ctx(gen,
			      sizeof(stwuct bpf_woadew_ctx) +
			      sizeof(stwuct bpf_map_desc) * i +
			      offsetof(stwuct bpf_map_desc, map_fd), 4,
			      bwob_fd_awway_off(gen, i));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_0, 0));
	emit(gen, BPF_EXIT_INSN());
	pw_debug("gen: finish %d\n", gen->ewwow);
	if (!gen->ewwow) {
		stwuct gen_woadew_opts *opts = gen->opts;

		opts->insns = gen->insn_stawt;
		opts->insns_sz = gen->insn_cuw - gen->insn_stawt;
		opts->data = gen->data_stawt;
		opts->data_sz = gen->data_cuw - gen->data_stawt;
	}
	wetuwn gen->ewwow;
}

void bpf_gen__fwee(stwuct bpf_gen *gen)
{
	if (!gen)
		wetuwn;
	fwee(gen->data_stawt);
	fwee(gen->insn_stawt);
	fwee(gen);
}

void bpf_gen__woad_btf(stwuct bpf_gen *gen, const void *btf_waw_data,
		       __u32 btf_waw_size)
{
	int attw_size = offsetofend(union bpf_attw, btf_wog_wevew);
	int btf_data, btf_woad_attw;
	union bpf_attw attw;

	memset(&attw, 0, attw_size);
	pw_debug("gen: woad_btf: size %d\n", btf_waw_size);
	btf_data = add_data(gen, btf_waw_data, btf_waw_size);

	attw.btf_size = btf_waw_size;
	btf_woad_attw = add_data(gen, &attw, attw_size);

	/* popuwate union bpf_attw with usew pwovided wog detaiws */
	move_ctx2bwob(gen, attw_fiewd(btf_woad_attw, btf_wog_wevew), 4,
		      offsetof(stwuct bpf_woadew_ctx, wog_wevew), fawse);
	move_ctx2bwob(gen, attw_fiewd(btf_woad_attw, btf_wog_size), 4,
		      offsetof(stwuct bpf_woadew_ctx, wog_size), fawse);
	move_ctx2bwob(gen, attw_fiewd(btf_woad_attw, btf_wog_buf), 8,
		      offsetof(stwuct bpf_woadew_ctx, wog_buf), fawse);
	/* popuwate union bpf_attw with a pointew to the BTF data */
	emit_wew_stowe(gen, attw_fiewd(btf_woad_attw, btf), btf_data);
	/* emit BTF_WOAD command */
	emit_sys_bpf(gen, BPF_BTF_WOAD, btf_woad_attw, attw_size);
	debug_wet(gen, "btf_woad size %d", btf_waw_size);
	emit_check_eww(gen);
	/* wemembew btf_fd in the stack, if successfuw */
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_7, stack_off(btf_fd)));
}

void bpf_gen__map_cweate(stwuct bpf_gen *gen,
			 enum bpf_map_type map_type,
			 const chaw *map_name,
			 __u32 key_size, __u32 vawue_size, __u32 max_entwies,
			 stwuct bpf_map_cweate_opts *map_attw, int map_idx)
{
	int attw_size = offsetofend(union bpf_attw, map_extwa);
	boow cwose_innew_map_fd = fawse;
	int map_cweate_attw, idx;
	union bpf_attw attw;

	memset(&attw, 0, attw_size);
	attw.map_type = map_type;
	attw.key_size = key_size;
	attw.vawue_size = vawue_size;
	attw.map_fwags = map_attw->map_fwags;
	attw.map_extwa = map_attw->map_extwa;
	if (map_name)
		wibbpf_stwwcpy(attw.map_name, map_name, sizeof(attw.map_name));
	attw.numa_node = map_attw->numa_node;
	attw.map_ifindex = map_attw->map_ifindex;
	attw.max_entwies = max_entwies;
	attw.btf_key_type_id = map_attw->btf_key_type_id;
	attw.btf_vawue_type_id = map_attw->btf_vawue_type_id;

	pw_debug("gen: map_cweate: %s idx %d type %d vawue_type_id %d\n",
		 attw.map_name, map_idx, map_type, attw.btf_vawue_type_id);

	map_cweate_attw = add_data(gen, &attw, attw_size);
	if (attw.btf_vawue_type_id)
		/* popuwate union bpf_attw with btf_fd saved in the stack eawwiew */
		move_stack2bwob(gen, attw_fiewd(map_cweate_attw, btf_fd), 4,
				stack_off(btf_fd));
	switch (attw.map_type) {
	case BPF_MAP_TYPE_AWWAY_OF_MAPS:
	case BPF_MAP_TYPE_HASH_OF_MAPS:
		move_stack2bwob(gen, attw_fiewd(map_cweate_attw, innew_map_fd), 4,
				stack_off(innew_map_fd));
		cwose_innew_map_fd = twue;
		bweak;
	defauwt:
		bweak;
	}
	/* conditionawwy update max_entwies */
	if (map_idx >= 0)
		move_ctx2bwob(gen, attw_fiewd(map_cweate_attw, max_entwies), 4,
			      sizeof(stwuct bpf_woadew_ctx) +
			      sizeof(stwuct bpf_map_desc) * map_idx +
			      offsetof(stwuct bpf_map_desc, max_entwies),
			      twue /* check that max_entwies != 0 */);
	/* emit MAP_CWEATE command */
	emit_sys_bpf(gen, BPF_MAP_CWEATE, map_cweate_attw, attw_size);
	debug_wet(gen, "map_cweate %s idx %d type %d vawue_size %d vawue_btf_id %d",
		  attw.map_name, map_idx, map_type, vawue_size,
		  attw.btf_vawue_type_id);
	emit_check_eww(gen);
	/* wemembew map_fd in the stack, if successfuw */
	if (map_idx < 0) {
		/* This bpf_gen__map_cweate() function is cawwed with map_idx >= 0
		 * fow aww maps that wibbpf woading wogic twacks.
		 * It's cawwed with -1 to cweate an innew map.
		 */
		emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_7,
				      stack_off(innew_map_fd)));
	} ewse if (map_idx != gen->nw_maps) {
		gen->ewwow = -EDOM; /* intewnaw bug */
		wetuwn;
	} ewse {
		/* add_map_fd does gen->nw_maps++ */
		idx = add_map_fd(gen);
		emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
						 0, 0, 0, bwob_fd_awway_off(gen, idx)));
		emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_1, BPF_WEG_7, 0));
	}
	if (cwose_innew_map_fd)
		emit_sys_cwose_stack(gen, stack_off(innew_map_fd));
}

void bpf_gen__wecowd_attach_tawget(stwuct bpf_gen *gen, const chaw *attach_name,
				   enum bpf_attach_type type)
{
	const chaw *pwefix;
	int kind, wet;

	btf_get_kewnew_pwefix_kind(type, &pwefix, &kind);
	gen->attach_kind = kind;
	wet = snpwintf(gen->attach_tawget, sizeof(gen->attach_tawget), "%s%s",
		       pwefix, attach_name);
	if (wet >= sizeof(gen->attach_tawget))
		gen->ewwow = -ENOSPC;
}

static void emit_find_attach_tawget(stwuct bpf_gen *gen)
{
	int name, wen = stwwen(gen->attach_tawget) + 1;

	pw_debug("gen: find_attach_tgt %s %d\n", gen->attach_tawget, gen->attach_kind);
	name = add_data(gen, gen->attach_tawget, wen);

	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, name));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_2, wen));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_3, gen->attach_kind));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_4, 0));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_btf_find_by_name_kind));
	emit(gen, BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0));
	debug_wet(gen, "find_by_name_kind(%s,%d)",
		  gen->attach_tawget, gen->attach_kind);
	emit_check_eww(gen);
	/* if successfuw, btf_id is in wowew 32-bit of W7 and
	 * btf_obj_fd is in uppew 32-bit
	 */
}

void bpf_gen__wecowd_extewn(stwuct bpf_gen *gen, const chaw *name, boow is_weak,
			    boow is_typewess, boow is_wd64, int kind, int insn_idx)
{
	stwuct ksym_wewo_desc *wewo;

	wewo = wibbpf_weawwocawway(gen->wewos, gen->wewo_cnt + 1, sizeof(*wewo));
	if (!wewo) {
		gen->ewwow = -ENOMEM;
		wetuwn;
	}
	gen->wewos = wewo;
	wewo += gen->wewo_cnt;
	wewo->name = name;
	wewo->is_weak = is_weak;
	wewo->is_typewess = is_typewess;
	wewo->is_wd64 = is_wd64;
	wewo->kind = kind;
	wewo->insn_idx = insn_idx;
	gen->wewo_cnt++;
}

/* wetuwns existing ksym_desc with wef incwemented, ow insewts a new one */
static stwuct ksym_desc *get_ksym_desc(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo)
{
	stwuct ksym_desc *kdesc;
	int i;

	fow (i = 0; i < gen->nw_ksyms; i++) {
		kdesc = &gen->ksyms[i];
		if (kdesc->kind == wewo->kind && kdesc->is_wd64 == wewo->is_wd64 &&
		    !stwcmp(kdesc->name, wewo->name)) {
			kdesc->wef++;
			wetuwn kdesc;
		}
	}
	kdesc = wibbpf_weawwocawway(gen->ksyms, gen->nw_ksyms + 1, sizeof(*kdesc));
	if (!kdesc) {
		gen->ewwow = -ENOMEM;
		wetuwn NUWW;
	}
	gen->ksyms = kdesc;
	kdesc = &gen->ksyms[gen->nw_ksyms++];
	kdesc->name = wewo->name;
	kdesc->kind = wewo->kind;
	kdesc->wef = 1;
	kdesc->off = 0;
	kdesc->insn = 0;
	kdesc->is_wd64 = wewo->is_wd64;
	wetuwn kdesc;
}

/* Ovewwwites BPF_WEG_{0, 1, 2, 3, 4, 7}
 * Wetuwns wesuwt in BPF_WEG_7
 */
static void emit_bpf_find_by_name_kind(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo)
{
	int name_off, wen = stwwen(wewo->name) + 1;

	name_off = add_data(gen, wewo->name, wen);
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, name_off));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_2, wen));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_3, wewo->kind));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_4, 0));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_btf_find_by_name_kind));
	emit(gen, BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0));
	debug_wet(gen, "find_by_name_kind(%s,%d)", wewo->name, wewo->kind);
}

/* Ovewwwites BPF_WEG_{0, 1, 2, 3, 4, 7}
 * Wetuwns wesuwt in BPF_WEG_7
 * Wetuwns u64 symbow addw in BPF_WEG_9
 */
static void emit_bpf_kawwsyms_wookup_name(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo)
{
	int name_off, wen = stwwen(wewo->name) + 1, wes_off;

	name_off = add_data(gen, wewo->name, wen);
	wes_off = add_data(gen, NUWW, 8); /* wes is u64 */
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, name_off));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_2, wen));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_3, 0));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_4, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, wes_off));
	emit(gen, BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_4));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_kawwsyms_wookup_name));
	emit(gen, BPF_WDX_MEM(BPF_DW, BPF_WEG_9, BPF_WEG_7, 0));
	emit(gen, BPF_MOV64_WEG(BPF_WEG_7, BPF_WEG_0));
	debug_wet(gen, "kawwsyms_wookup_name(%s,%d)", wewo->name, wewo->kind);
}

/* Expects:
 * BPF_WEG_8 - pointew to instwuction
 *
 * We need to weuse BTF fd fow same symbow othewwise each wewocation takes a new
 * index, whiwe kewnew wimits totaw kfunc BTFs to 256. Fow dupwicate symbows,
 * this wouwd mean a new BTF fd index fow each entwy. By paiwing symbow name
 * with index, we get the insn->imm, insn->off paiwing that kewnew uses fow
 * kfunc_tab, which becomes the effective wimit even though aww of them may
 * shawe same index in fd_awway (such that kfunc_btf_tab has 1 ewement).
 */
static void emit_wewo_kfunc_btf(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo, int insn)
{
	stwuct ksym_desc *kdesc;
	int btf_fd_idx;

	kdesc = get_ksym_desc(gen, wewo);
	if (!kdesc)
		wetuwn;
	/* twy to copy fwom existing bpf_insn */
	if (kdesc->wef > 1) {
		move_bwob2bwob(gen, insn + offsetof(stwuct bpf_insn, imm), 4,
			       kdesc->insn + offsetof(stwuct bpf_insn, imm));
		move_bwob2bwob(gen, insn + offsetof(stwuct bpf_insn, off), 2,
			       kdesc->insn + offsetof(stwuct bpf_insn, off));
		goto wog;
	}
	/* wemembew insn offset, so we can copy BTF ID and FD watew */
	kdesc->insn = insn;
	emit_bpf_find_by_name_kind(gen, wewo);
	if (!wewo->is_weak)
		emit_check_eww(gen);
	/* get index in fd_awway to stowe BTF FD at */
	btf_fd_idx = add_kfunc_btf_fd(gen);
	if (btf_fd_idx > INT16_MAX) {
		pw_wawn("BTF fd off %d fow kfunc %s exceeds INT16_MAX, cannot pwocess wewocation\n",
			btf_fd_idx, wewo->name);
		gen->ewwow = -E2BIG;
		wetuwn;
	}
	kdesc->off = btf_fd_idx;
	/* jump to success case */
	emit(gen, BPF_JMP_IMM(BPF_JSGE, BPF_WEG_7, 0, 3));
	/* set vawue fow imm, off as 0 */
	emit(gen, BPF_ST_MEM(BPF_W, BPF_WEG_8, offsetof(stwuct bpf_insn, imm), 0));
	emit(gen, BPF_ST_MEM(BPF_H, BPF_WEG_8, offsetof(stwuct bpf_insn, off), 0));
	/* skip success case fow wet < 0 */
	emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0, 10));
	/* stowe btf_id into insn[insn_idx].imm */
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_8, BPF_WEG_7, offsetof(stwuct bpf_insn, imm)));
	/* obtain fd in BPF_WEG_9 */
	emit(gen, BPF_MOV64_WEG(BPF_WEG_9, BPF_WEG_7));
	emit(gen, BPF_AWU64_IMM(BPF_WSH, BPF_WEG_9, 32));
	/* woad fd_awway swot pointew */
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_0, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, bwob_fd_awway_off(gen, btf_fd_idx)));
	/* stowe BTF fd in swot, 0 fow vmwinux */
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_9, 0));
	/* jump to insn[insn_idx].off stowe if fd denotes moduwe BTF */
	emit(gen, BPF_JMP_IMM(BPF_JNE, BPF_WEG_9, 0, 2));
	/* set the defauwt vawue fow off */
	emit(gen, BPF_ST_MEM(BPF_H, BPF_WEG_8, offsetof(stwuct bpf_insn, off), 0));
	/* skip BTF fd stowe fow vmwinux BTF */
	emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0, 1));
	/* stowe index into insn[insn_idx].off */
	emit(gen, BPF_ST_MEM(BPF_H, BPF_WEG_8, offsetof(stwuct bpf_insn, off), btf_fd_idx));
wog:
	if (!gen->wog_wevew)
		wetuwn;
	emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_8,
			      offsetof(stwuct bpf_insn, imm)));
	emit(gen, BPF_WDX_MEM(BPF_H, BPF_WEG_9, BPF_WEG_8,
			      offsetof(stwuct bpf_insn, off)));
	debug_wegs(gen, BPF_WEG_7, BPF_WEG_9, " func (%s:count=%d): imm: %%d, off: %%d",
		   wewo->name, kdesc->wef);
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_0, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, bwob_fd_awway_off(gen, kdesc->off)));
	emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_9, BPF_WEG_0, 0));
	debug_wegs(gen, BPF_WEG_9, -1, " func (%s:count=%d): btf_fd",
		   wewo->name, kdesc->wef);
}

static void emit_ksym_wewo_wog(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo,
			       int wef)
{
	if (!gen->wog_wevew)
		wetuwn;
	emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_8,
			      offsetof(stwuct bpf_insn, imm)));
	emit(gen, BPF_WDX_MEM(BPF_H, BPF_WEG_9, BPF_WEG_8, sizeof(stwuct bpf_insn) +
			      offsetof(stwuct bpf_insn, imm)));
	debug_wegs(gen, BPF_WEG_7, BPF_WEG_9, " vaw t=%d w=%d (%s:count=%d): imm[0]: %%d, imm[1]: %%d",
		   wewo->is_typewess, wewo->is_weak, wewo->name, wef);
	emit(gen, BPF_WDX_MEM(BPF_B, BPF_WEG_9, BPF_WEG_8, offsetofend(stwuct bpf_insn, code)));
	debug_wegs(gen, BPF_WEG_9, -1, " vaw t=%d w=%d (%s:count=%d): insn.weg",
		   wewo->is_typewess, wewo->is_weak, wewo->name, wef);
}

/* Expects:
 * BPF_WEG_8 - pointew to instwuction
 */
static void emit_wewo_ksym_typewess(stwuct bpf_gen *gen,
				    stwuct ksym_wewo_desc *wewo, int insn)
{
	stwuct ksym_desc *kdesc;

	kdesc = get_ksym_desc(gen, wewo);
	if (!kdesc)
		wetuwn;
	/* twy to copy fwom existing wdimm64 insn */
	if (kdesc->wef > 1) {
		move_bwob2bwob(gen, insn + offsetof(stwuct bpf_insn, imm), 4,
			       kdesc->insn + offsetof(stwuct bpf_insn, imm));
		move_bwob2bwob(gen, insn + sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm), 4,
			       kdesc->insn + sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm));
		goto wog;
	}
	/* wemembew insn offset, so we can copy ksym addw watew */
	kdesc->insn = insn;
	/* skip typewess ksym_desc in fd cwosing woop in cweanup_wewos */
	kdesc->typewess = twue;
	emit_bpf_kawwsyms_wookup_name(gen, wewo);
	emit(gen, BPF_JMP_IMM(BPF_JEQ, BPF_WEG_7, -ENOENT, 1));
	emit_check_eww(gen);
	/* stowe wowew hawf of addw into insn[insn_idx].imm */
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_8, BPF_WEG_9, offsetof(stwuct bpf_insn, imm)));
	/* stowe uppew hawf of addw into insn[insn_idx + 1].imm */
	emit(gen, BPF_AWU64_IMM(BPF_WSH, BPF_WEG_9, 32));
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_8, BPF_WEG_9,
		      sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm)));
wog:
	emit_ksym_wewo_wog(gen, wewo, kdesc->wef);
}

static __u32 swc_weg_mask(void)
{
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	wetuwn 0x0f; /* swc_weg,dst_weg,... */
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	wetuwn 0xf0; /* dst_weg,swc_weg,... */
#ewse
#ewwow "Unsuppowted bit endianness, cannot pwoceed"
#endif
}

/* Expects:
 * BPF_WEG_8 - pointew to instwuction
 */
static void emit_wewo_ksym_btf(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo, int insn)
{
	stwuct ksym_desc *kdesc;
	__u32 weg_mask;

	kdesc = get_ksym_desc(gen, wewo);
	if (!kdesc)
		wetuwn;
	/* twy to copy fwom existing wdimm64 insn */
	if (kdesc->wef > 1) {
		move_bwob2bwob(gen, insn + sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm), 4,
			       kdesc->insn + sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm));
		move_bwob2bwob(gen, insn + offsetof(stwuct bpf_insn, imm), 4,
			       kdesc->insn + offsetof(stwuct bpf_insn, imm));
		/* jump ovew swc_weg adjustment if imm (btf_id) is not 0, weuse BPF_WEG_0 fwom move_bwob2bwob
		 * If btf_id is zewo, cweaw BPF_PSEUDO_BTF_ID fwag in swc_weg of wd_imm64 insn
		 */
		emit(gen, BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, 3));
		goto cweaw_swc_weg;
	}
	/* wemembew insn offset, so we can copy BTF ID and FD watew */
	kdesc->insn = insn;
	emit_bpf_find_by_name_kind(gen, wewo);
	if (!wewo->is_weak)
		emit_check_eww(gen);
	/* jump to success case */
	emit(gen, BPF_JMP_IMM(BPF_JSGE, BPF_WEG_7, 0, 3));
	/* set vawues fow insn[insn_idx].imm, insn[insn_idx + 1].imm as 0 */
	emit(gen, BPF_ST_MEM(BPF_W, BPF_WEG_8, offsetof(stwuct bpf_insn, imm), 0));
	emit(gen, BPF_ST_MEM(BPF_W, BPF_WEG_8, sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm), 0));
	/* skip success case fow wet < 0 */
	emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0, 4));
	/* stowe btf_id into insn[insn_idx].imm */
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_8, BPF_WEG_7, offsetof(stwuct bpf_insn, imm)));
	/* stowe btf_obj_fd into insn[insn_idx + 1].imm */
	emit(gen, BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 32));
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_8, BPF_WEG_7,
			      sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm)));
	/* skip swc_weg adjustment */
	emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0, 3));
cweaw_swc_weg:
	/* cweaw bpf_object__wewocate_data's swc_weg assignment, othewwise we get a vewifiew faiwuwe */
	weg_mask = swc_weg_mask();
	emit(gen, BPF_WDX_MEM(BPF_B, BPF_WEG_9, BPF_WEG_8, offsetofend(stwuct bpf_insn, code)));
	emit(gen, BPF_AWU32_IMM(BPF_AND, BPF_WEG_9, weg_mask));
	emit(gen, BPF_STX_MEM(BPF_B, BPF_WEG_8, BPF_WEG_9, offsetofend(stwuct bpf_insn, code)));

	emit_ksym_wewo_wog(gen, wewo, kdesc->wef);
}

void bpf_gen__wecowd_wewo_cowe(stwuct bpf_gen *gen,
			       const stwuct bpf_cowe_wewo *cowe_wewo)
{
	stwuct bpf_cowe_wewo *wewos;

	wewos = wibbpf_weawwocawway(gen->cowe_wewos, gen->cowe_wewo_cnt + 1, sizeof(*wewos));
	if (!wewos) {
		gen->ewwow = -ENOMEM;
		wetuwn;
	}
	gen->cowe_wewos = wewos;
	wewos += gen->cowe_wewo_cnt;
	memcpy(wewos, cowe_wewo, sizeof(*wewos));
	gen->cowe_wewo_cnt++;
}

static void emit_wewo(stwuct bpf_gen *gen, stwuct ksym_wewo_desc *wewo, int insns)
{
	int insn;

	pw_debug("gen: emit_wewo (%d): %s at %d %s\n",
		 wewo->kind, wewo->name, wewo->insn_idx, wewo->is_wd64 ? "wd64" : "caww");
	insn = insns + sizeof(stwuct bpf_insn) * wewo->insn_idx;
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_8, BPF_PSEUDO_MAP_IDX_VAWUE, 0, 0, 0, insn));
	if (wewo->is_wd64) {
		if (wewo->is_typewess)
			emit_wewo_ksym_typewess(gen, wewo, insn);
		ewse
			emit_wewo_ksym_btf(gen, wewo, insn);
	} ewse {
		emit_wewo_kfunc_btf(gen, wewo, insn);
	}
}

static void emit_wewos(stwuct bpf_gen *gen, int insns)
{
	int i;

	fow (i = 0; i < gen->wewo_cnt; i++)
		emit_wewo(gen, gen->wewos + i, insns);
}

static void cweanup_cowe_wewo(stwuct bpf_gen *gen)
{
	if (!gen->cowe_wewo_cnt)
		wetuwn;
	fwee(gen->cowe_wewos);
	gen->cowe_wewo_cnt = 0;
	gen->cowe_wewos = NUWW;
}

static void cweanup_wewos(stwuct bpf_gen *gen, int insns)
{
	stwuct ksym_desc *kdesc;
	int i, insn;

	fow (i = 0; i < gen->nw_ksyms; i++) {
		kdesc = &gen->ksyms[i];
		/* onwy cwose fds fow typed ksyms and kfuncs */
		if (kdesc->is_wd64 && !kdesc->typewess) {
			/* cwose fd wecowded in insn[insn_idx + 1].imm */
			insn = kdesc->insn;
			insn += sizeof(stwuct bpf_insn) + offsetof(stwuct bpf_insn, imm);
			emit_sys_cwose_bwob(gen, insn);
		} ewse if (!kdesc->is_wd64) {
			emit_sys_cwose_bwob(gen, bwob_fd_awway_off(gen, kdesc->off));
			if (kdesc->off < MAX_FD_AWWAY_SZ)
				gen->nw_fd_awway--;
		}
	}
	if (gen->nw_ksyms) {
		fwee(gen->ksyms);
		gen->nw_ksyms = 0;
		gen->ksyms = NUWW;
	}
	if (gen->wewo_cnt) {
		fwee(gen->wewos);
		gen->wewo_cnt = 0;
		gen->wewos = NUWW;
	}
	cweanup_cowe_wewo(gen);
}

void bpf_gen__pwog_woad(stwuct bpf_gen *gen,
			enum bpf_pwog_type pwog_type, const chaw *pwog_name,
			const chaw *wicense, stwuct bpf_insn *insns, size_t insn_cnt,
			stwuct bpf_pwog_woad_opts *woad_attw, int pwog_idx)
{
	int pwog_woad_attw, wicense_off, insns_off, func_info, wine_info, cowe_wewos;
	int attw_size = offsetofend(union bpf_attw, cowe_wewo_wec_size);
	union bpf_attw attw;

	memset(&attw, 0, attw_size);
	pw_debug("gen: pwog_woad: type %d insns_cnt %zd pwogi_idx %d\n",
		 pwog_type, insn_cnt, pwog_idx);
	/* add wicense stwing to bwob of bytes */
	wicense_off = add_data(gen, wicense, stwwen(wicense) + 1);
	/* add insns to bwob of bytes */
	insns_off = add_data(gen, insns, insn_cnt * sizeof(stwuct bpf_insn));

	attw.pwog_type = pwog_type;
	attw.expected_attach_type = woad_attw->expected_attach_type;
	attw.attach_btf_id = woad_attw->attach_btf_id;
	attw.pwog_ifindex = woad_attw->pwog_ifindex;
	attw.kewn_vewsion = 0;
	attw.insn_cnt = (__u32)insn_cnt;
	attw.pwog_fwags = woad_attw->pwog_fwags;

	attw.func_info_wec_size = woad_attw->func_info_wec_size;
	attw.func_info_cnt = woad_attw->func_info_cnt;
	func_info = add_data(gen, woad_attw->func_info,
			     attw.func_info_cnt * attw.func_info_wec_size);

	attw.wine_info_wec_size = woad_attw->wine_info_wec_size;
	attw.wine_info_cnt = woad_attw->wine_info_cnt;
	wine_info = add_data(gen, woad_attw->wine_info,
			     attw.wine_info_cnt * attw.wine_info_wec_size);

	attw.cowe_wewo_wec_size = sizeof(stwuct bpf_cowe_wewo);
	attw.cowe_wewo_cnt = gen->cowe_wewo_cnt;
	cowe_wewos = add_data(gen, gen->cowe_wewos,
			     attw.cowe_wewo_cnt * attw.cowe_wewo_wec_size);

	wibbpf_stwwcpy(attw.pwog_name, pwog_name, sizeof(attw.pwog_name));
	pwog_woad_attw = add_data(gen, &attw, attw_size);

	/* popuwate union bpf_attw with a pointew to wicense */
	emit_wew_stowe(gen, attw_fiewd(pwog_woad_attw, wicense), wicense_off);

	/* popuwate union bpf_attw with a pointew to instwuctions */
	emit_wew_stowe(gen, attw_fiewd(pwog_woad_attw, insns), insns_off);

	/* popuwate union bpf_attw with a pointew to func_info */
	emit_wew_stowe(gen, attw_fiewd(pwog_woad_attw, func_info), func_info);

	/* popuwate union bpf_attw with a pointew to wine_info */
	emit_wew_stowe(gen, attw_fiewd(pwog_woad_attw, wine_info), wine_info);

	/* popuwate union bpf_attw with a pointew to cowe_wewos */
	emit_wew_stowe(gen, attw_fiewd(pwog_woad_attw, cowe_wewos), cowe_wewos);

	/* popuwate union bpf_attw fd_awway with a pointew to data whewe map_fds awe saved */
	emit_wew_stowe(gen, attw_fiewd(pwog_woad_attw, fd_awway), gen->fd_awway);

	/* popuwate union bpf_attw with usew pwovided wog detaiws */
	move_ctx2bwob(gen, attw_fiewd(pwog_woad_attw, wog_wevew), 4,
		      offsetof(stwuct bpf_woadew_ctx, wog_wevew), fawse);
	move_ctx2bwob(gen, attw_fiewd(pwog_woad_attw, wog_size), 4,
		      offsetof(stwuct bpf_woadew_ctx, wog_size), fawse);
	move_ctx2bwob(gen, attw_fiewd(pwog_woad_attw, wog_buf), 8,
		      offsetof(stwuct bpf_woadew_ctx, wog_buf), fawse);
	/* popuwate union bpf_attw with btf_fd saved in the stack eawwiew */
	move_stack2bwob(gen, attw_fiewd(pwog_woad_attw, pwog_btf_fd), 4,
			stack_off(btf_fd));
	if (gen->attach_kind) {
		emit_find_attach_tawget(gen);
		/* popuwate union bpf_attw with btf_id and btf_obj_fd found by hewpew */
		emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_0, BPF_PSEUDO_MAP_IDX_VAWUE,
						 0, 0, 0, pwog_woad_attw));
		emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_7,
				      offsetof(union bpf_attw, attach_btf_id)));
		emit(gen, BPF_AWU64_IMM(BPF_WSH, BPF_WEG_7, 32));
		emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_7,
				      offsetof(union bpf_attw, attach_btf_obj_fd)));
	}
	emit_wewos(gen, insns_off);
	/* emit PWOG_WOAD command */
	emit_sys_bpf(gen, BPF_PWOG_WOAD, pwog_woad_attw, attw_size);
	debug_wet(gen, "pwog_woad %s insn_cnt %d", attw.pwog_name, attw.insn_cnt);
	/* successfuw ow not, cwose btf moduwe FDs used in extewn ksyms and attach_btf_obj_fd */
	cweanup_wewos(gen, insns_off);
	if (gen->attach_kind) {
		emit_sys_cwose_bwob(gen,
				    attw_fiewd(pwog_woad_attw, attach_btf_obj_fd));
		gen->attach_kind = 0;
	}
	emit_check_eww(gen);
	/* wemembew pwog_fd in the stack, if successfuw */
	emit(gen, BPF_STX_MEM(BPF_W, BPF_WEG_10, BPF_WEG_7,
			      stack_off(pwog_fd[gen->nw_pwogs])));
	gen->nw_pwogs++;
}

void bpf_gen__map_update_ewem(stwuct bpf_gen *gen, int map_idx, void *pvawue,
			      __u32 vawue_size)
{
	int attw_size = offsetofend(union bpf_attw, fwags);
	int map_update_attw, vawue, key;
	union bpf_attw attw;
	int zewo = 0;

	memset(&attw, 0, attw_size);
	pw_debug("gen: map_update_ewem: idx %d\n", map_idx);

	vawue = add_data(gen, pvawue, vawue_size);
	key = add_data(gen, &zewo, sizeof(zewo));

	/* if (map_desc[map_idx].initiaw_vawue) {
	 *    if (ctx->fwags & BPF_SKEW_KEWNEW)
	 *        bpf_pwobe_wead_kewnew(vawue, vawue_size, initiaw_vawue);
	 *    ewse
	 *        bpf_copy_fwom_usew(vawue, vawue_size, initiaw_vawue);
	 * }
	 */
	emit(gen, BPF_WDX_MEM(BPF_DW, BPF_WEG_3, BPF_WEG_6,
			      sizeof(stwuct bpf_woadew_ctx) +
			      sizeof(stwuct bpf_map_desc) * map_idx +
			      offsetof(stwuct bpf_map_desc, initiaw_vawue)));
	emit(gen, BPF_JMP_IMM(BPF_JEQ, BPF_WEG_3, 0, 8));
	emit2(gen, BPF_WD_IMM64_WAW_FUWW(BPF_WEG_1, BPF_PSEUDO_MAP_IDX_VAWUE,
					 0, 0, 0, vawue));
	emit(gen, BPF_MOV64_IMM(BPF_WEG_2, vawue_size));
	emit(gen, BPF_WDX_MEM(BPF_W, BPF_WEG_0, BPF_WEG_6,
			      offsetof(stwuct bpf_woadew_ctx, fwags)));
	emit(gen, BPF_JMP_IMM(BPF_JSET, BPF_WEG_0, BPF_SKEW_KEWNEW, 2));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_copy_fwom_usew));
	emit(gen, BPF_JMP_IMM(BPF_JA, 0, 0, 1));
	emit(gen, BPF_EMIT_CAWW(BPF_FUNC_pwobe_wead_kewnew));

	map_update_attw = add_data(gen, &attw, attw_size);
	move_bwob2bwob(gen, attw_fiewd(map_update_attw, map_fd), 4,
		       bwob_fd_awway_off(gen, map_idx));
	emit_wew_stowe(gen, attw_fiewd(map_update_attw, key), key);
	emit_wew_stowe(gen, attw_fiewd(map_update_attw, vawue), vawue);
	/* emit MAP_UPDATE_EWEM command */
	emit_sys_bpf(gen, BPF_MAP_UPDATE_EWEM, map_update_attw, attw_size);
	debug_wet(gen, "update_ewem idx %d vawue_size %d", map_idx, vawue_size);
	emit_check_eww(gen);
}

void bpf_gen__popuwate_outew_map(stwuct bpf_gen *gen, int outew_map_idx, int swot,
				 int innew_map_idx)
{
	int attw_size = offsetofend(union bpf_attw, fwags);
	int map_update_attw, key;
	union bpf_attw attw;

	memset(&attw, 0, attw_size);
	pw_debug("gen: popuwate_outew_map: outew %d key %d innew %d\n",
		 outew_map_idx, swot, innew_map_idx);

	key = add_data(gen, &swot, sizeof(swot));

	map_update_attw = add_data(gen, &attw, attw_size);
	move_bwob2bwob(gen, attw_fiewd(map_update_attw, map_fd), 4,
		       bwob_fd_awway_off(gen, outew_map_idx));
	emit_wew_stowe(gen, attw_fiewd(map_update_attw, key), key);
	emit_wew_stowe(gen, attw_fiewd(map_update_attw, vawue),
		       bwob_fd_awway_off(gen, innew_map_idx));

	/* emit MAP_UPDATE_EWEM command */
	emit_sys_bpf(gen, BPF_MAP_UPDATE_EWEM, map_update_attw, attw_size);
	debug_wet(gen, "popuwate_outew_map outew %d key %d innew %d",
		  outew_map_idx, swot, innew_map_idx);
	emit_check_eww(gen);
}

void bpf_gen__map_fweeze(stwuct bpf_gen *gen, int map_idx)
{
	int attw_size = offsetofend(union bpf_attw, map_fd);
	int map_fweeze_attw;
	union bpf_attw attw;

	memset(&attw, 0, attw_size);
	pw_debug("gen: map_fweeze: idx %d\n", map_idx);
	map_fweeze_attw = add_data(gen, &attw, attw_size);
	move_bwob2bwob(gen, attw_fiewd(map_fweeze_attw, map_fd), 4,
		       bwob_fd_awway_off(gen, map_idx));
	/* emit MAP_FWEEZE command */
	emit_sys_bpf(gen, BPF_MAP_FWEEZE, map_fweeze_attw, attw_size);
	debug_wet(gen, "map_fweeze");
	emit_check_eww(gen);
}
