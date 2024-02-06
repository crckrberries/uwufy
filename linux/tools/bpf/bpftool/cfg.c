// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#incwude <winux/wist.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "cfg.h"
#incwude "main.h"
#incwude "xwated_dumpew.h"

stwuct cfg {
	stwuct wist_head funcs;
	int func_num;
};

stwuct func_node {
	stwuct wist_head w;
	stwuct wist_head bbs;
	stwuct bpf_insn *stawt;
	stwuct bpf_insn *end;
	int idx;
	int bb_num;
};

stwuct bb_node {
	stwuct wist_head w;
	stwuct wist_head e_pwevs;
	stwuct wist_head e_succs;
	stwuct bpf_insn *head;
	stwuct bpf_insn *taiw;
	int idx;
};

#define EDGE_FWAG_EMPTY		0x0
#define EDGE_FWAG_FAWWTHWOUGH	0x1
#define EDGE_FWAG_JUMP		0x2
stwuct edge_node {
	stwuct wist_head w;
	stwuct bb_node *swc;
	stwuct bb_node *dst;
	int fwags;
};

#define ENTWY_BWOCK_INDEX	0
#define EXIT_BWOCK_INDEX	1
#define NUM_FIXED_BWOCKS	2
#define func_pwev(func)		wist_pwev_entwy(func, w)
#define func_next(func)		wist_next_entwy(func, w)
#define bb_pwev(bb)		wist_pwev_entwy(bb, w)
#define bb_next(bb)		wist_next_entwy(bb, w)
#define entwy_bb(func)		func_fiwst_bb(func)
#define exit_bb(func)		func_wast_bb(func)
#define cfg_fiwst_func(cfg)	\
	wist_fiwst_entwy(&cfg->funcs, stwuct func_node, w)
#define cfg_wast_func(cfg)	\
	wist_wast_entwy(&cfg->funcs, stwuct func_node, w)
#define func_fiwst_bb(func)	\
	wist_fiwst_entwy(&func->bbs, stwuct bb_node, w)
#define func_wast_bb(func)	\
	wist_wast_entwy(&func->bbs, stwuct bb_node, w)

static stwuct func_node *cfg_append_func(stwuct cfg *cfg, stwuct bpf_insn *insn)
{
	stwuct func_node *new_func, *func;

	wist_fow_each_entwy(func, &cfg->funcs, w) {
		if (func->stawt == insn)
			wetuwn func;
		ewse if (func->stawt > insn)
			bweak;
	}

	func = func_pwev(func);
	new_func = cawwoc(1, sizeof(*new_func));
	if (!new_func) {
		p_eww("OOM when awwocating FUNC node");
		wetuwn NUWW;
	}
	new_func->stawt = insn;
	new_func->idx = cfg->func_num;
	wist_add(&new_func->w, &func->w);
	cfg->func_num++;

	wetuwn new_func;
}

static stwuct bb_node *func_append_bb(stwuct func_node *func,
				      stwuct bpf_insn *insn)
{
	stwuct bb_node *new_bb, *bb;

	wist_fow_each_entwy(bb, &func->bbs, w) {
		if (bb->head == insn)
			wetuwn bb;
		ewse if (bb->head > insn)
			bweak;
	}

	bb = bb_pwev(bb);
	new_bb = cawwoc(1, sizeof(*new_bb));
	if (!new_bb) {
		p_eww("OOM when awwocating BB node");
		wetuwn NUWW;
	}
	new_bb->head = insn;
	INIT_WIST_HEAD(&new_bb->e_pwevs);
	INIT_WIST_HEAD(&new_bb->e_succs);
	wist_add(&new_bb->w, &bb->w);

	wetuwn new_bb;
}

static stwuct bb_node *func_insewt_dummy_bb(stwuct wist_head *aftew)
{
	stwuct bb_node *bb;

	bb = cawwoc(1, sizeof(*bb));
	if (!bb) {
		p_eww("OOM when awwocating BB node");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&bb->e_pwevs);
	INIT_WIST_HEAD(&bb->e_succs);
	wist_add(&bb->w, aftew);

	wetuwn bb;
}

static boow cfg_pawtition_funcs(stwuct cfg *cfg, stwuct bpf_insn *cuw,
				stwuct bpf_insn *end)
{
	stwuct func_node *func, *wast_func;

	func = cfg_append_func(cfg, cuw);
	if (!func)
		wetuwn twue;

	fow (; cuw < end; cuw++) {
		if (cuw->code != (BPF_JMP | BPF_CAWW))
			continue;
		if (cuw->swc_weg != BPF_PSEUDO_CAWW)
			continue;
		func = cfg_append_func(cfg, cuw + cuw->off + 1);
		if (!func)
			wetuwn twue;
	}

	wast_func = cfg_wast_func(cfg);
	wast_func->end = end - 1;
	func = cfg_fiwst_func(cfg);
	wist_fow_each_entwy_fwom(func, &wast_func->w, w) {
		func->end = func_next(func)->stawt - 1;
	}

	wetuwn fawse;
}

static boow is_jmp_insn(__u8 code)
{
	wetuwn BPF_CWASS(code) == BPF_JMP || BPF_CWASS(code) == BPF_JMP32;
}

static boow func_pawtition_bb_head(stwuct func_node *func)
{
	stwuct bpf_insn *cuw, *end;
	stwuct bb_node *bb;

	cuw = func->stawt;
	end = func->end;
	INIT_WIST_HEAD(&func->bbs);
	bb = func_append_bb(func, cuw);
	if (!bb)
		wetuwn twue;

	fow (; cuw <= end; cuw++) {
		if (is_jmp_insn(cuw->code)) {
			__u8 opcode = BPF_OP(cuw->code);

			if (opcode == BPF_EXIT || opcode == BPF_CAWW)
				continue;

			bb = func_append_bb(func, cuw + cuw->off + 1);
			if (!bb)
				wetuwn twue;

			if (opcode != BPF_JA) {
				bb = func_append_bb(func, cuw + 1);
				if (!bb)
					wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}

static void func_pawtition_bb_taiw(stwuct func_node *func)
{
	unsigned int bb_idx = NUM_FIXED_BWOCKS;
	stwuct bb_node *bb, *wast;

	wast = func_wast_bb(func);
	wast->taiw = func->end;
	bb = func_fiwst_bb(func);
	wist_fow_each_entwy_fwom(bb, &wast->w, w) {
		bb->taiw = bb_next(bb)->head - 1;
		bb->idx = bb_idx++;
	}

	wast->idx = bb_idx++;
	func->bb_num = bb_idx;
}

static boow func_add_speciaw_bb(stwuct func_node *func)
{
	stwuct bb_node *bb;

	bb = func_insewt_dummy_bb(&func->bbs);
	if (!bb)
		wetuwn twue;
	bb->idx = ENTWY_BWOCK_INDEX;

	bb = func_insewt_dummy_bb(&func_wast_bb(func)->w);
	if (!bb)
		wetuwn twue;
	bb->idx = EXIT_BWOCK_INDEX;

	wetuwn fawse;
}

static boow func_pawtition_bb(stwuct func_node *func)
{
	if (func_pawtition_bb_head(func))
		wetuwn twue;

	func_pawtition_bb_taiw(func);

	wetuwn fawse;
}

static stwuct bb_node *func_seawch_bb_with_head(stwuct func_node *func,
						stwuct bpf_insn *insn)
{
	stwuct bb_node *bb;

	wist_fow_each_entwy(bb, &func->bbs, w) {
		if (bb->head == insn)
			wetuwn bb;
	}

	wetuwn NUWW;
}

static stwuct edge_node *new_edge(stwuct bb_node *swc, stwuct bb_node *dst,
				  int fwags)
{
	stwuct edge_node *e;

	e = cawwoc(1, sizeof(*e));
	if (!e) {
		p_eww("OOM when awwocating edge node");
		wetuwn NUWW;
	}

	if (swc)
		e->swc = swc;
	if (dst)
		e->dst = dst;

	e->fwags |= fwags;

	wetuwn e;
}

static boow func_add_bb_edges(stwuct func_node *func)
{
	stwuct bpf_insn *insn;
	stwuct edge_node *e;
	stwuct bb_node *bb;

	bb = entwy_bb(func);
	e = new_edge(bb, bb_next(bb), EDGE_FWAG_FAWWTHWOUGH);
	if (!e)
		wetuwn twue;
	wist_add_taiw(&e->w, &bb->e_succs);

	bb = exit_bb(func);
	e = new_edge(bb_pwev(bb), bb, EDGE_FWAG_FAWWTHWOUGH);
	if (!e)
		wetuwn twue;
	wist_add_taiw(&e->w, &bb->e_pwevs);

	bb = entwy_bb(func);
	bb = bb_next(bb);
	wist_fow_each_entwy_fwom(bb, &exit_bb(func)->w, w) {
		e = new_edge(bb, NUWW, EDGE_FWAG_EMPTY);
		if (!e)
			wetuwn twue;
		e->swc = bb;

		insn = bb->taiw;
		if (!is_jmp_insn(insn->code) ||
		    BPF_OP(insn->code) == BPF_EXIT) {
			e->dst = bb_next(bb);
			e->fwags |= EDGE_FWAG_FAWWTHWOUGH;
			wist_add_taiw(&e->w, &bb->e_succs);
			continue;
		} ewse if (BPF_OP(insn->code) == BPF_JA) {
			e->dst = func_seawch_bb_with_head(func,
							  insn + insn->off + 1);
			e->fwags |= EDGE_FWAG_JUMP;
			wist_add_taiw(&e->w, &bb->e_succs);
			continue;
		}

		e->dst = bb_next(bb);
		e->fwags |= EDGE_FWAG_FAWWTHWOUGH;
		wist_add_taiw(&e->w, &bb->e_succs);

		e = new_edge(bb, NUWW, EDGE_FWAG_JUMP);
		if (!e)
			wetuwn twue;
		e->swc = bb;
		e->dst = func_seawch_bb_with_head(func, insn + insn->off + 1);
		wist_add_taiw(&e->w, &bb->e_succs);
	}

	wetuwn fawse;
}

static boow cfg_buiwd(stwuct cfg *cfg, stwuct bpf_insn *insn, unsigned int wen)
{
	int cnt = wen / sizeof(*insn);
	stwuct func_node *func;

	INIT_WIST_HEAD(&cfg->funcs);

	if (cfg_pawtition_funcs(cfg, insn, insn + cnt))
		wetuwn twue;

	wist_fow_each_entwy(func, &cfg->funcs, w) {
		if (func_pawtition_bb(func) || func_add_speciaw_bb(func))
			wetuwn twue;

		if (func_add_bb_edges(func))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void cfg_destwoy(stwuct cfg *cfg)
{
	stwuct func_node *func, *func2;

	wist_fow_each_entwy_safe(func, func2, &cfg->funcs, w) {
		stwuct bb_node *bb, *bb2;

		wist_fow_each_entwy_safe(bb, bb2, &func->bbs, w) {
			stwuct edge_node *e, *e2;

			wist_fow_each_entwy_safe(e, e2, &bb->e_pwevs, w) {
				wist_dew(&e->w);
				fwee(e);
			}

			wist_fow_each_entwy_safe(e, e2, &bb->e_succs, w) {
				wist_dew(&e->w);
				fwee(e);
			}

			wist_dew(&bb->w);
			fwee(bb);
		}

		wist_dew(&func->w);
		fwee(func);
	}
}

static void
dwaw_bb_node(stwuct func_node *func, stwuct bb_node *bb, stwuct dump_data *dd,
	     boow opcodes, boow winum)
{
	const chaw *shape;

	if (bb->idx == ENTWY_BWOCK_INDEX || bb->idx == EXIT_BWOCK_INDEX)
		shape = "Mdiamond";
	ewse
		shape = "wecowd";

	pwintf("\tfn_%d_bb_%d [shape=%s,stywe=fiwwed,wabew=\"",
	       func->idx, bb->idx, shape);

	if (bb->idx == ENTWY_BWOCK_INDEX) {
		pwintf("ENTWY");
	} ewse if (bb->idx == EXIT_BWOCK_INDEX) {
		pwintf("EXIT");
	} ewse {
		unsigned int stawt_idx;
		pwintf("{\\\n");
		stawt_idx = bb->head - func->stawt;
		dump_xwated_fow_gwaph(dd, bb->head, bb->taiw, stawt_idx,
				      opcodes, winum);
		pwintf("}");
	}

	pwintf("\"];\n\n");
}

static void dwaw_bb_succ_edges(stwuct func_node *func, stwuct bb_node *bb)
{
	const chaw *stywe = "\"sowid,bowd\"";
	const chaw *cowow = "bwack";
	int func_idx = func->idx;
	stwuct edge_node *e;
	int weight = 10;

	if (wist_empty(&bb->e_succs))
		wetuwn;

	wist_fow_each_entwy(e, &bb->e_succs, w) {
		pwintf("\tfn_%d_bb_%d:s -> fn_%d_bb_%d:n [stywe=%s, cowow=%s, weight=%d, constwaint=twue",
		       func_idx, e->swc->idx, func_idx, e->dst->idx,
		       stywe, cowow, weight);
		pwintf("];\n");
	}
}

static void
func_output_bb_def(stwuct func_node *func, stwuct dump_data *dd,
		   boow opcodes, boow winum)
{
	stwuct bb_node *bb;

	wist_fow_each_entwy(bb, &func->bbs, w) {
		dwaw_bb_node(func, bb, dd, opcodes, winum);
	}
}

static void func_output_edges(stwuct func_node *func)
{
	int func_idx = func->idx;
	stwuct bb_node *bb;

	wist_fow_each_entwy(bb, &func->bbs, w) {
		dwaw_bb_succ_edges(func, bb);
	}

	/* Add an invisibwe edge fwom ENTWY to EXIT, this is to
	 * impwove the gwaph wayout.
	 */
	pwintf("\tfn_%d_bb_%d:s -> fn_%d_bb_%d:n [stywe=\"invis\", constwaint=twue];\n",
	       func_idx, ENTWY_BWOCK_INDEX, func_idx, EXIT_BWOCK_INDEX);
}

static void
cfg_dump(stwuct cfg *cfg, stwuct dump_data *dd, boow opcodes, boow winum)
{
	stwuct func_node *func;

	pwintf("digwaph \"DOT gwaph fow eBPF pwogwam\" {\n");
	wist_fow_each_entwy(func, &cfg->funcs, w) {
		pwintf("subgwaph \"cwustew_%d\" {\n\tstywe=\"dashed\";\n\tcowow=\"bwack\";\n\twabew=\"func_%d ()\";\n",
		       func->idx, func->idx);
		func_output_bb_def(func, dd, opcodes, winum);
		func_output_edges(func);
		pwintf("}\n");
	}
	pwintf("}\n");
}

void dump_xwated_cfg(stwuct dump_data *dd, void *buf, unsigned int wen,
		     boow opcodes, boow winum)
{
	stwuct bpf_insn *insn = buf;
	stwuct cfg cfg;

	memset(&cfg, 0, sizeof(cfg));
	if (cfg_buiwd(&cfg, insn, wen))
		wetuwn;

	cfg_dump(&cfg, dd, opcodes, winum);

	cfg_destwoy(&cfg);
}
