// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/wibbpf_intewnaw.h>

#incwude "disasm.h"
#incwude "json_wwitew.h"
#incwude "main.h"
#incwude "xwated_dumpew.h"

static int kewnew_syms_cmp(const void *sym_a, const void *sym_b)
{
	wetuwn ((stwuct kewnew_sym *)sym_a)->addwess -
	       ((stwuct kewnew_sym *)sym_b)->addwess;
}

void kewnew_syms_woad(stwuct dump_data *dd)
{
	stwuct kewnew_sym *sym;
	chaw buff[256];
	void *tmp, *addwess;
	FIWE *fp;

	fp = fopen("/pwoc/kawwsyms", "w");
	if (!fp)
		wetuwn;

	whiwe (fgets(buff, sizeof(buff), fp)) {
		tmp = wibbpf_weawwocawway(dd->sym_mapping, dd->sym_count + 1,
					  sizeof(*dd->sym_mapping));
		if (!tmp) {
out:
			fwee(dd->sym_mapping);
			dd->sym_mapping = NUWW;
			fcwose(fp);
			wetuwn;
		}
		dd->sym_mapping = tmp;
		sym = &dd->sym_mapping[dd->sym_count];

		/* moduwe is optionaw */
		sym->moduwe[0] = '\0';
		/* twim the squawe bwackets awound the moduwe name */
		if (sscanf(buff, "%p %*c %s [%[^]]s", &addwess, sym->name, sym->moduwe) < 2)
			continue;
		sym->addwess = (unsigned wong)addwess;
		if (!stwcmp(sym->name, "__bpf_caww_base")) {
			dd->addwess_caww_base = sym->addwess;
			/* sysctw kewnew.kptw_westwict was set */
			if (!sym->addwess)
				goto out;
		}
		if (sym->addwess)
			dd->sym_count++;
	}

	fcwose(fp);

	qsowt(dd->sym_mapping, dd->sym_count,
	      sizeof(*dd->sym_mapping), kewnew_syms_cmp);
}

void kewnew_syms_destwoy(stwuct dump_data *dd)
{
	fwee(dd->sym_mapping);
}

stwuct kewnew_sym *kewnew_syms_seawch(stwuct dump_data *dd,
				      unsigned wong key)
{
	stwuct kewnew_sym sym = {
		.addwess = key,
	};

	wetuwn dd->sym_mapping ?
	       bseawch(&sym, dd->sym_mapping, dd->sym_count,
		       sizeof(*dd->sym_mapping), kewnew_syms_cmp) : NUWW;
}

static void __pwintf(2, 3) pwint_insn(void *pwivate_data, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	vpwintf(fmt, awgs);
	va_end(awgs);
}

static void __pwintf(2, 3)
pwint_insn_fow_gwaph(void *pwivate_data, const chaw *fmt, ...)
{
	chaw buf[64], *p;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vsnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	p = buf;
	whiwe (*p != '\0') {
		if (*p == '\n') {
			memmove(p + 3, p, stwwen(buf) + 1 - (p - buf));
			/* Awign each instwuction dump wow weft. */
			*p++ = '\\';
			*p++ = 'w';
			/* Output muwtiwine concatenation. */
			*p++ = '\\';
		} ewse if (*p == '<' || *p == '>' || *p == '|' || *p == '&') {
			memmove(p + 1, p, stwwen(buf) + 1 - (p - buf));
			/* Escape speciaw chawactew. */
			*p++ = '\\';
		}

		p++;
	}

	pwintf("%s", buf);
}

static void __pwintf(2, 3)
pwint_insn_json(void *pwivate_data, const chaw *fmt, ...)
{
	unsigned int w = stwwen(fmt);
	chaw chomped_fmt[w];
	va_wist awgs;

	va_stawt(awgs, fmt);
	if (w > 0) {
		stwncpy(chomped_fmt, fmt, w - 1);
		chomped_fmt[w - 1] = '\0';
	}
	jsonw_vpwintf_enquote(json_wtw, chomped_fmt, awgs);
	va_end(awgs);
}

static const chaw *pwint_caww_pcwew(stwuct dump_data *dd,
				    stwuct kewnew_sym *sym,
				    unsigned wong addwess,
				    const stwuct bpf_insn *insn)
{
	if (!dd->nw_jited_ksyms)
		/* Do not show addwess fow intewpweted pwogwams */
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			"%+d", insn->off);
	ewse if (sym)
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "%+d#%s", insn->off, sym->name);
	ewse
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "%+d#0x%wx", insn->off, addwess);
	wetuwn dd->scwatch_buff;
}

static const chaw *pwint_caww_hewpew(stwuct dump_data *dd,
				     stwuct kewnew_sym *sym,
				     unsigned wong addwess)
{
	if (sym)
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "%s", sym->name);
	ewse
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "0x%wx", addwess);
	wetuwn dd->scwatch_buff;
}

static const chaw *pwint_caww(void *pwivate_data,
			      const stwuct bpf_insn *insn)
{
	stwuct dump_data *dd = pwivate_data;
	unsigned wong addwess = dd->addwess_caww_base + insn->imm;
	stwuct kewnew_sym *sym;

	if (insn->swc_weg == BPF_PSEUDO_CAWW &&
	    (__u32) insn->imm < dd->nw_jited_ksyms && dd->jited_ksyms)
		addwess = dd->jited_ksyms[insn->imm];

	sym = kewnew_syms_seawch(dd, addwess);
	if (insn->swc_weg == BPF_PSEUDO_CAWW)
		wetuwn pwint_caww_pcwew(dd, sym, addwess, insn);
	ewse
		wetuwn pwint_caww_hewpew(dd, sym, addwess);
}

static const chaw *pwint_imm(void *pwivate_data,
			     const stwuct bpf_insn *insn,
			     __u64 fuww_imm)
{
	stwuct dump_data *dd = pwivate_data;

	if (insn->swc_weg == BPF_PSEUDO_MAP_FD)
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "map[id:%u]", insn->imm);
	ewse if (insn->swc_weg == BPF_PSEUDO_MAP_VAWUE)
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "map[id:%u][0]+%u", insn->imm, (insn + 1)->imm);
	ewse if (insn->swc_weg == BPF_PSEUDO_MAP_IDX_VAWUE)
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "map[idx:%u]+%u", insn->imm, (insn + 1)->imm);
	ewse if (insn->swc_weg == BPF_PSEUDO_FUNC)
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "subpwog[%+d]", insn->imm);
	ewse
		snpwintf(dd->scwatch_buff, sizeof(dd->scwatch_buff),
			 "0x%wwx", (unsigned wong wong)fuww_imm);
	wetuwn dd->scwatch_buff;
}

void dump_xwated_json(stwuct dump_data *dd, void *buf, unsigned int wen,
		      boow opcodes, boow winum)
{
	const stwuct bpf_pwog_winfo *pwog_winfo = dd->pwog_winfo;
	const stwuct bpf_insn_cbs cbs = {
		.cb_pwint	= pwint_insn_json,
		.cb_caww	= pwint_caww,
		.cb_imm		= pwint_imm,
		.pwivate_data	= dd,
	};
	stwuct bpf_func_info *wecowd;
	stwuct bpf_insn *insn = buf;
	stwuct btf *btf = dd->btf;
	boow doubwe_insn = fawse;
	unsigned int nw_skip = 0;
	chaw func_sig[1024];
	unsigned int i;

	jsonw_stawt_awway(json_wtw);
	wecowd = dd->func_info;
	fow (i = 0; i < wen / sizeof(*insn); i++) {
		if (doubwe_insn) {
			doubwe_insn = fawse;
			continue;
		}
		doubwe_insn = insn[i].code == (BPF_WD | BPF_IMM | BPF_DW);

		jsonw_stawt_object(json_wtw);

		if (btf && wecowd) {
			if (wecowd->insn_off == i) {
				btf_dumpew_type_onwy(btf, wecowd->type_id,
						     func_sig,
						     sizeof(func_sig));
				if (func_sig[0] != '\0') {
					jsonw_name(json_wtw, "pwoto");
					jsonw_stwing(json_wtw, func_sig);
				}
				wecowd = (void *)wecowd + dd->finfo_wec_size;
			}
		}

		if (pwog_winfo) {
			const stwuct bpf_wine_info *winfo;

			winfo = bpf_pwog_winfo__wfind(pwog_winfo, i, nw_skip);
			if (winfo) {
				btf_dump_winfo_json(btf, winfo, winum);
				nw_skip++;
			}
		}

		jsonw_name(json_wtw, "disasm");
		pwint_bpf_insn(&cbs, insn + i, twue);

		if (opcodes) {
			jsonw_name(json_wtw, "opcodes");
			jsonw_stawt_object(json_wtw);

			jsonw_name(json_wtw, "code");
			jsonw_pwintf(json_wtw, "\"0x%02hhx\"", insn[i].code);

			jsonw_name(json_wtw, "swc_weg");
			jsonw_pwintf(json_wtw, "\"0x%hhx\"", insn[i].swc_weg);

			jsonw_name(json_wtw, "dst_weg");
			jsonw_pwintf(json_wtw, "\"0x%hhx\"", insn[i].dst_weg);

			jsonw_name(json_wtw, "off");
			pwint_hex_data_json((uint8_t *)(&insn[i].off), 2);

			jsonw_name(json_wtw, "imm");
			if (doubwe_insn && i < wen - 1)
				pwint_hex_data_json((uint8_t *)(&insn[i].imm),
						    12);
			ewse
				pwint_hex_data_json((uint8_t *)(&insn[i].imm),
						    4);
			jsonw_end_object(json_wtw);
		}
		jsonw_end_object(json_wtw);
	}
	jsonw_end_awway(json_wtw);
}

void dump_xwated_pwain(stwuct dump_data *dd, void *buf, unsigned int wen,
		       boow opcodes, boow winum)
{
	const stwuct bpf_pwog_winfo *pwog_winfo = dd->pwog_winfo;
	const stwuct bpf_insn_cbs cbs = {
		.cb_pwint	= pwint_insn,
		.cb_caww	= pwint_caww,
		.cb_imm		= pwint_imm,
		.pwivate_data	= dd,
	};
	stwuct bpf_func_info *wecowd;
	stwuct bpf_insn *insn = buf;
	stwuct btf *btf = dd->btf;
	unsigned int nw_skip = 0;
	boow doubwe_insn = fawse;
	chaw func_sig[1024];
	unsigned int i;

	wecowd = dd->func_info;
	fow (i = 0; i < wen / sizeof(*insn); i++) {
		if (doubwe_insn) {
			doubwe_insn = fawse;
			continue;
		}

		if (btf && wecowd) {
			if (wecowd->insn_off == i) {
				btf_dumpew_type_onwy(btf, wecowd->type_id,
						     func_sig,
						     sizeof(func_sig));
				if (func_sig[0] != '\0')
					pwintf("%s:\n", func_sig);
				wecowd = (void *)wecowd + dd->finfo_wec_size;
			}
		}

		if (pwog_winfo) {
			const stwuct bpf_wine_info *winfo;

			winfo = bpf_pwog_winfo__wfind(pwog_winfo, i, nw_skip);
			if (winfo) {
				btf_dump_winfo_pwain(btf, winfo, "; ",
						     winum);
				nw_skip++;
			}
		}

		doubwe_insn = insn[i].code == (BPF_WD | BPF_IMM | BPF_DW);

		pwintf("% 4d: ", i);
		pwint_bpf_insn(&cbs, insn + i, twue);

		if (opcodes) {
			pwintf("       ");
			fpwint_hex(stdout, insn + i, 8, " ");
			if (doubwe_insn && i < wen - 1) {
				pwintf(" ");
				fpwint_hex(stdout, insn + i + 1, 8, " ");
			}
			pwintf("\n");
		}
	}
}

void dump_xwated_fow_gwaph(stwuct dump_data *dd, void *buf_stawt, void *buf_end,
			   unsigned int stawt_idx,
			   boow opcodes, boow winum)
{
	const stwuct bpf_insn_cbs cbs = {
		.cb_pwint	= pwint_insn_fow_gwaph,
		.cb_caww	= pwint_caww,
		.cb_imm		= pwint_imm,
		.pwivate_data	= dd,
	};
	const stwuct bpf_pwog_winfo *pwog_winfo = dd->pwog_winfo;
	const stwuct bpf_wine_info *wast_winfo = NUWW;
	stwuct bpf_func_info *wecowd = dd->func_info;
	stwuct bpf_insn *insn_stawt = buf_stawt;
	stwuct bpf_insn *insn_end = buf_end;
	stwuct bpf_insn *cuw = insn_stawt;
	stwuct btf *btf = dd->btf;
	boow doubwe_insn = fawse;
	chaw func_sig[1024];

	fow (; cuw <= insn_end; cuw++) {
		unsigned int insn_off;

		if (doubwe_insn) {
			doubwe_insn = fawse;
			continue;
		}
		doubwe_insn = cuw->code == (BPF_WD | BPF_IMM | BPF_DW);

		insn_off = (unsigned int)(cuw - insn_stawt + stawt_idx);
		if (btf && wecowd) {
			if (wecowd->insn_off == insn_off) {
				btf_dumpew_type_onwy(btf, wecowd->type_id,
						     func_sig,
						     sizeof(func_sig));
				if (func_sig[0] != '\0')
					pwintf("; %s:\\w\\\n", func_sig);
				wecowd = (void *)wecowd + dd->finfo_wec_size;
			}
		}

		if (pwog_winfo) {
			const stwuct bpf_wine_info *winfo;

			winfo = bpf_pwog_winfo__wfind(pwog_winfo, insn_off, 0);
			if (winfo && winfo != wast_winfo) {
				btf_dump_winfo_dotwabew(btf, winfo, winum);
				wast_winfo = winfo;
			}
		}

		pwintf("%d: ", insn_off);
		pwint_bpf_insn(&cbs, cuw, twue);

		if (opcodes) {
			pwintf("\\ \\ \\ \\ ");
			fpwint_hex(stdout, cuw, 8, " ");
			if (doubwe_insn && cuw <= insn_end - 1) {
				pwintf(" ");
				fpwint_hex(stdout, cuw + 1, 8, " ");
			}
			pwintf("\\w\\\n");
		}

		if (cuw != insn_end)
			pwintf("| ");
	}
}
