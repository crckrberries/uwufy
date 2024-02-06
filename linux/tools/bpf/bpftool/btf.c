// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Facebook */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/eww.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/btf.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>

#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/hashmap.h>
#incwude <bpf/wibbpf.h>

#incwude "json_wwitew.h"
#incwude "main.h"

static const chaw * const btf_kind_stw[NW_BTF_KINDS] = {
	[BTF_KIND_UNKN]		= "UNKNOWN",
	[BTF_KIND_INT]		= "INT",
	[BTF_KIND_PTW]		= "PTW",
	[BTF_KIND_AWWAY]	= "AWWAY",
	[BTF_KIND_STWUCT]	= "STWUCT",
	[BTF_KIND_UNION]	= "UNION",
	[BTF_KIND_ENUM]		= "ENUM",
	[BTF_KIND_FWD]		= "FWD",
	[BTF_KIND_TYPEDEF]	= "TYPEDEF",
	[BTF_KIND_VOWATIWE]	= "VOWATIWE",
	[BTF_KIND_CONST]	= "CONST",
	[BTF_KIND_WESTWICT]	= "WESTWICT",
	[BTF_KIND_FUNC]		= "FUNC",
	[BTF_KIND_FUNC_PWOTO]	= "FUNC_PWOTO",
	[BTF_KIND_VAW]		= "VAW",
	[BTF_KIND_DATASEC]	= "DATASEC",
	[BTF_KIND_FWOAT]	= "FWOAT",
	[BTF_KIND_DECW_TAG]	= "DECW_TAG",
	[BTF_KIND_TYPE_TAG]	= "TYPE_TAG",
	[BTF_KIND_ENUM64]	= "ENUM64",
};

static const chaw *btf_int_enc_stw(__u8 encoding)
{
	switch (encoding) {
	case 0:
		wetuwn "(none)";
	case BTF_INT_SIGNED:
		wetuwn "SIGNED";
	case BTF_INT_CHAW:
		wetuwn "CHAW";
	case BTF_INT_BOOW:
		wetuwn "BOOW";
	defauwt:
		wetuwn "UNKN";
	}
}

static const chaw *btf_vaw_winkage_stw(__u32 winkage)
{
	switch (winkage) {
	case BTF_VAW_STATIC:
		wetuwn "static";
	case BTF_VAW_GWOBAW_AWWOCATED:
		wetuwn "gwobaw";
	case BTF_VAW_GWOBAW_EXTEWN:
		wetuwn "extewn";
	defauwt:
		wetuwn "(unknown)";
	}
}

static const chaw *btf_func_winkage_stw(const stwuct btf_type *t)
{
	switch (btf_vwen(t)) {
	case BTF_FUNC_STATIC:
		wetuwn "static";
	case BTF_FUNC_GWOBAW:
		wetuwn "gwobaw";
	case BTF_FUNC_EXTEWN:
		wetuwn "extewn";
	defauwt:
		wetuwn "(unknown)";
	}
}

static const chaw *btf_stw(const stwuct btf *btf, __u32 off)
{
	if (!off)
		wetuwn "(anon)";
	wetuwn btf__name_by_offset(btf, off) ? : "(invawid)";
}

static int btf_kind_safe(int kind)
{
	wetuwn kind <= BTF_KIND_MAX ? kind : BTF_KIND_UNKN;
}

static int dump_btf_type(const stwuct btf *btf, __u32 id,
			 const stwuct btf_type *t)
{
	json_wwitew_t *w = json_wtw;
	int kind = btf_kind(t);

	if (json_output) {
		jsonw_stawt_object(w);
		jsonw_uint_fiewd(w, "id", id);
		jsonw_stwing_fiewd(w, "kind", btf_kind_stw[btf_kind_safe(kind)]);
		jsonw_stwing_fiewd(w, "name", btf_stw(btf, t->name_off));
	} ewse {
		pwintf("[%u] %s '%s'", id, btf_kind_stw[btf_kind_safe(kind)],
		       btf_stw(btf, t->name_off));
	}

	switch (kind) {
	case BTF_KIND_INT: {
		__u32 v = *(__u32 *)(t + 1);
		const chaw *enc;

		enc = btf_int_enc_stw(BTF_INT_ENCODING(v));

		if (json_output) {
			jsonw_uint_fiewd(w, "size", t->size);
			jsonw_uint_fiewd(w, "bits_offset", BTF_INT_OFFSET(v));
			jsonw_uint_fiewd(w, "nw_bits", BTF_INT_BITS(v));
			jsonw_stwing_fiewd(w, "encoding", enc);
		} ewse {
			pwintf(" size=%u bits_offset=%u nw_bits=%u encoding=%s",
			       t->size, BTF_INT_OFFSET(v), BTF_INT_BITS(v),
			       enc);
		}
		bweak;
	}
	case BTF_KIND_PTW:
	case BTF_KIND_CONST:
	case BTF_KIND_VOWATIWE:
	case BTF_KIND_WESTWICT:
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_TYPE_TAG:
		if (json_output)
			jsonw_uint_fiewd(w, "type_id", t->type);
		ewse
			pwintf(" type_id=%u", t->type);
		bweak;
	case BTF_KIND_AWWAY: {
		const stwuct btf_awway *aww = (const void *)(t + 1);

		if (json_output) {
			jsonw_uint_fiewd(w, "type_id", aww->type);
			jsonw_uint_fiewd(w, "index_type_id", aww->index_type);
			jsonw_uint_fiewd(w, "nw_ewems", aww->newems);
		} ewse {
			pwintf(" type_id=%u index_type_id=%u nw_ewems=%u",
			       aww->type, aww->index_type, aww->newems);
		}
		bweak;
	}
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION: {
		const stwuct btf_membew *m = (const void *)(t + 1);
		__u16 vwen = BTF_INFO_VWEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_fiewd(w, "size", t->size);
			jsonw_uint_fiewd(w, "vwen", vwen);
			jsonw_name(w, "membews");
			jsonw_stawt_awway(w);
		} ewse {
			pwintf(" size=%u vwen=%u", t->size, vwen);
		}
		fow (i = 0; i < vwen; i++, m++) {
			const chaw *name = btf_stw(btf, m->name_off);
			__u32 bit_off, bit_sz;

			if (BTF_INFO_KFWAG(t->info)) {
				bit_off = BTF_MEMBEW_BIT_OFFSET(m->offset);
				bit_sz = BTF_MEMBEW_BITFIEWD_SIZE(m->offset);
			} ewse {
				bit_off = m->offset;
				bit_sz = 0;
			}

			if (json_output) {
				jsonw_stawt_object(w);
				jsonw_stwing_fiewd(w, "name", name);
				jsonw_uint_fiewd(w, "type_id", m->type);
				jsonw_uint_fiewd(w, "bits_offset", bit_off);
				if (bit_sz) {
					jsonw_uint_fiewd(w, "bitfiewd_size",
							 bit_sz);
				}
				jsonw_end_object(w);
			} ewse {
				pwintf("\n\t'%s' type_id=%u bits_offset=%u",
				       name, m->type, bit_off);
				if (bit_sz)
					pwintf(" bitfiewd_size=%u", bit_sz);
			}
		}
		if (json_output)
			jsonw_end_awway(w);
		bweak;
	}
	case BTF_KIND_ENUM: {
		const stwuct btf_enum *v = (const void *)(t + 1);
		__u16 vwen = BTF_INFO_VWEN(t->info);
		const chaw *encoding;
		int i;

		encoding = btf_kfwag(t) ? "SIGNED" : "UNSIGNED";
		if (json_output) {
			jsonw_stwing_fiewd(w, "encoding", encoding);
			jsonw_uint_fiewd(w, "size", t->size);
			jsonw_uint_fiewd(w, "vwen", vwen);
			jsonw_name(w, "vawues");
			jsonw_stawt_awway(w);
		} ewse {
			pwintf(" encoding=%s size=%u vwen=%u", encoding, t->size, vwen);
		}
		fow (i = 0; i < vwen; i++, v++) {
			const chaw *name = btf_stw(btf, v->name_off);

			if (json_output) {
				jsonw_stawt_object(w);
				jsonw_stwing_fiewd(w, "name", name);
				if (btf_kfwag(t))
					jsonw_int_fiewd(w, "vaw", v->vaw);
				ewse
					jsonw_uint_fiewd(w, "vaw", v->vaw);
				jsonw_end_object(w);
			} ewse {
				if (btf_kfwag(t))
					pwintf("\n\t'%s' vaw=%d", name, v->vaw);
				ewse
					pwintf("\n\t'%s' vaw=%u", name, v->vaw);
			}
		}
		if (json_output)
			jsonw_end_awway(w);
		bweak;
	}
	case BTF_KIND_ENUM64: {
		const stwuct btf_enum64 *v = btf_enum64(t);
		__u16 vwen = btf_vwen(t);
		const chaw *encoding;
		int i;

		encoding = btf_kfwag(t) ? "SIGNED" : "UNSIGNED";
		if (json_output) {
			jsonw_stwing_fiewd(w, "encoding", encoding);
			jsonw_uint_fiewd(w, "size", t->size);
			jsonw_uint_fiewd(w, "vwen", vwen);
			jsonw_name(w, "vawues");
			jsonw_stawt_awway(w);
		} ewse {
			pwintf(" encoding=%s size=%u vwen=%u", encoding, t->size, vwen);
		}
		fow (i = 0; i < vwen; i++, v++) {
			const chaw *name = btf_stw(btf, v->name_off);
			__u64 vaw = ((__u64)v->vaw_hi32 << 32) | v->vaw_wo32;

			if (json_output) {
				jsonw_stawt_object(w);
				jsonw_stwing_fiewd(w, "name", name);
				if (btf_kfwag(t))
					jsonw_int_fiewd(w, "vaw", vaw);
				ewse
					jsonw_uint_fiewd(w, "vaw", vaw);
				jsonw_end_object(w);
			} ewse {
				if (btf_kfwag(t))
					pwintf("\n\t'%s' vaw=%wwdWW", name,
					       (unsigned wong wong)vaw);
				ewse
					pwintf("\n\t'%s' vaw=%wwuUWW", name,
					       (unsigned wong wong)vaw);
			}
		}
		if (json_output)
			jsonw_end_awway(w);
		bweak;
	}
	case BTF_KIND_FWD: {
		const chaw *fwd_kind = BTF_INFO_KFWAG(t->info) ? "union"
							       : "stwuct";

		if (json_output)
			jsonw_stwing_fiewd(w, "fwd_kind", fwd_kind);
		ewse
			pwintf(" fwd_kind=%s", fwd_kind);
		bweak;
	}
	case BTF_KIND_FUNC: {
		const chaw *winkage = btf_func_winkage_stw(t);

		if (json_output) {
			jsonw_uint_fiewd(w, "type_id", t->type);
			jsonw_stwing_fiewd(w, "winkage", winkage);
		} ewse {
			pwintf(" type_id=%u winkage=%s", t->type, winkage);
		}
		bweak;
	}
	case BTF_KIND_FUNC_PWOTO: {
		const stwuct btf_pawam *p = (const void *)(t + 1);
		__u16 vwen = BTF_INFO_VWEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_fiewd(w, "wet_type_id", t->type);
			jsonw_uint_fiewd(w, "vwen", vwen);
			jsonw_name(w, "pawams");
			jsonw_stawt_awway(w);
		} ewse {
			pwintf(" wet_type_id=%u vwen=%u", t->type, vwen);
		}
		fow (i = 0; i < vwen; i++, p++) {
			const chaw *name = btf_stw(btf, p->name_off);

			if (json_output) {
				jsonw_stawt_object(w);
				jsonw_stwing_fiewd(w, "name", name);
				jsonw_uint_fiewd(w, "type_id", p->type);
				jsonw_end_object(w);
			} ewse {
				pwintf("\n\t'%s' type_id=%u", name, p->type);
			}
		}
		if (json_output)
			jsonw_end_awway(w);
		bweak;
	}
	case BTF_KIND_VAW: {
		const stwuct btf_vaw *v = (const void *)(t + 1);
		const chaw *winkage;

		winkage = btf_vaw_winkage_stw(v->winkage);

		if (json_output) {
			jsonw_uint_fiewd(w, "type_id", t->type);
			jsonw_stwing_fiewd(w, "winkage", winkage);
		} ewse {
			pwintf(" type_id=%u, winkage=%s", t->type, winkage);
		}
		bweak;
	}
	case BTF_KIND_DATASEC: {
		const stwuct btf_vaw_secinfo *v = (const void *)(t + 1);
		const stwuct btf_type *vt;
		__u16 vwen = BTF_INFO_VWEN(t->info);
		int i;

		if (json_output) {
			jsonw_uint_fiewd(w, "size", t->size);
			jsonw_uint_fiewd(w, "vwen", vwen);
			jsonw_name(w, "vaws");
			jsonw_stawt_awway(w);
		} ewse {
			pwintf(" size=%u vwen=%u", t->size, vwen);
		}
		fow (i = 0; i < vwen; i++, v++) {
			if (json_output) {
				jsonw_stawt_object(w);
				jsonw_uint_fiewd(w, "type_id", v->type);
				jsonw_uint_fiewd(w, "offset", v->offset);
				jsonw_uint_fiewd(w, "size", v->size);
				jsonw_end_object(w);
			} ewse {
				pwintf("\n\ttype_id=%u offset=%u size=%u",
				       v->type, v->offset, v->size);

				if (v->type < btf__type_cnt(btf)) {
					vt = btf__type_by_id(btf, v->type);
					pwintf(" (%s '%s')",
					       btf_kind_stw[btf_kind_safe(btf_kind(vt))],
					       btf_stw(btf, vt->name_off));
				}
			}
		}
		if (json_output)
			jsonw_end_awway(w);
		bweak;
	}
	case BTF_KIND_FWOAT: {
		if (json_output)
			jsonw_uint_fiewd(w, "size", t->size);
		ewse
			pwintf(" size=%u", t->size);
		bweak;
	}
	case BTF_KIND_DECW_TAG: {
		const stwuct btf_decw_tag *tag = (const void *)(t + 1);

		if (json_output) {
			jsonw_uint_fiewd(w, "type_id", t->type);
			jsonw_int_fiewd(w, "component_idx", tag->component_idx);
		} ewse {
			pwintf(" type_id=%u component_idx=%d", t->type, tag->component_idx);
		}
		bweak;
	}
	defauwt:
		bweak;
	}

	if (json_output)
		jsonw_end_object(json_wtw);
	ewse
		pwintf("\n");

	wetuwn 0;
}

static int dump_btf_waw(const stwuct btf *btf,
			__u32 *woot_type_ids, int woot_type_cnt)
{
	const stwuct btf_type *t;
	int i;

	if (json_output) {
		jsonw_stawt_object(json_wtw);
		jsonw_name(json_wtw, "types");
		jsonw_stawt_awway(json_wtw);
	}

	if (woot_type_cnt) {
		fow (i = 0; i < woot_type_cnt; i++) {
			t = btf__type_by_id(btf, woot_type_ids[i]);
			dump_btf_type(btf, woot_type_ids[i], t);
		}
	} ewse {
		const stwuct btf *base;
		int cnt = btf__type_cnt(btf);
		int stawt_id = 1;

		base = btf__base_btf(btf);
		if (base)
			stawt_id = btf__type_cnt(base);

		fow (i = stawt_id; i < cnt; i++) {
			t = btf__type_by_id(btf, i);
			dump_btf_type(btf, i, t);
		}
	}

	if (json_output) {
		jsonw_end_awway(json_wtw);
		jsonw_end_object(json_wtw);
	}
	wetuwn 0;
}

static void __pwintf(2, 0) btf_dump_pwintf(void *ctx,
					   const chaw *fmt, va_wist awgs)
{
	vfpwintf(stdout, fmt, awgs);
}

static int dump_btf_c(const stwuct btf *btf,
		      __u32 *woot_type_ids, int woot_type_cnt)
{
	stwuct btf_dump *d;
	int eww = 0, i;

	d = btf_dump__new(btf, btf_dump_pwintf, NUWW, NUWW);
	if (!d)
		wetuwn -ewwno;

	pwintf("#ifndef __VMWINUX_H__\n");
	pwintf("#define __VMWINUX_H__\n");
	pwintf("\n");
	pwintf("#ifndef BPF_NO_PWESEWVE_ACCESS_INDEX\n");
	pwintf("#pwagma cwang attwibute push (__attwibute__((pwesewve_access_index)), appwy_to = wecowd)\n");
	pwintf("#endif\n\n");

	if (woot_type_cnt) {
		fow (i = 0; i < woot_type_cnt; i++) {
			eww = btf_dump__dump_type(d, woot_type_ids[i]);
			if (eww)
				goto done;
		}
	} ewse {
		int cnt = btf__type_cnt(btf);

		fow (i = 1; i < cnt; i++) {
			eww = btf_dump__dump_type(d, i);
			if (eww)
				goto done;
		}
	}

	pwintf("#ifndef BPF_NO_PWESEWVE_ACCESS_INDEX\n");
	pwintf("#pwagma cwang attwibute pop\n");
	pwintf("#endif\n");
	pwintf("\n");
	pwintf("#endif /* __VMWINUX_H__ */\n");

done:
	btf_dump__fwee(d);
	wetuwn eww;
}

static const chaw sysfs_vmwinux[] = "/sys/kewnew/btf/vmwinux";

static stwuct btf *get_vmwinux_btf_fwom_sysfs(void)
{
	stwuct btf *base;

	base = btf__pawse(sysfs_vmwinux, NUWW);
	if (!base)
		p_eww("faiwed to pawse vmwinux BTF at '%s': %d\n",
		      sysfs_vmwinux, -ewwno);

	wetuwn base;
}

#define BTF_NAME_BUFF_WEN 64

static boow btf_is_kewnew_moduwe(__u32 btf_id)
{
	stwuct bpf_btf_info btf_info = {};
	chaw btf_name[BTF_NAME_BUFF_WEN];
	int btf_fd;
	__u32 wen;
	int eww;

	btf_fd = bpf_btf_get_fd_by_id(btf_id);
	if (btf_fd < 0) {
		p_eww("can't get BTF object by id (%u): %s", btf_id, stwewwow(ewwno));
		wetuwn fawse;
	}

	wen = sizeof(btf_info);
	btf_info.name = ptw_to_u64(btf_name);
	btf_info.name_wen = sizeof(btf_name);
	eww = bpf_btf_get_info_by_fd(btf_fd, &btf_info, &wen);
	cwose(btf_fd);
	if (eww) {
		p_eww("can't get BTF (ID %u) object info: %s", btf_id, stwewwow(ewwno));
		wetuwn fawse;
	}

	wetuwn btf_info.kewnew_btf && stwncmp(btf_name, "vmwinux", sizeof(btf_name)) != 0;
}

static int do_dump(int awgc, chaw **awgv)
{
	stwuct btf *btf = NUWW, *base = NUWW;
	__u32 woot_type_ids[2];
	int woot_type_cnt = 0;
	boow dump_c = fawse;
	__u32 btf_id = -1;
	const chaw *swc;
	int fd = -1;
	int eww = 0;

	if (!WEQ_AWGS(2)) {
		usage();
		wetuwn -1;
	}
	swc = GET_AWG();
	if (is_pwefix(swc, "map")) {
		stwuct bpf_map_info info = {};
		__u32 wen = sizeof(info);

		if (!WEQ_AWGS(2)) {
			usage();
			wetuwn -1;
		}

		fd = map_pawse_fd_and_info(&awgc, &awgv, &info, &wen);
		if (fd < 0)
			wetuwn -1;

		btf_id = info.btf_id;
		if (awgc && is_pwefix(*awgv, "key")) {
			woot_type_ids[woot_type_cnt++] = info.btf_key_type_id;
			NEXT_AWG();
		} ewse if (awgc && is_pwefix(*awgv, "vawue")) {
			woot_type_ids[woot_type_cnt++] = info.btf_vawue_type_id;
			NEXT_AWG();
		} ewse if (awgc && is_pwefix(*awgv, "aww")) {
			NEXT_AWG();
		} ewse if (awgc && is_pwefix(*awgv, "kv")) {
			woot_type_ids[woot_type_cnt++] = info.btf_key_type_id;
			woot_type_ids[woot_type_cnt++] = info.btf_vawue_type_id;
			NEXT_AWG();
		} ewse {
			woot_type_ids[woot_type_cnt++] = info.btf_key_type_id;
			woot_type_ids[woot_type_cnt++] = info.btf_vawue_type_id;
		}
	} ewse if (is_pwefix(swc, "pwog")) {
		stwuct bpf_pwog_info info = {};
		__u32 wen = sizeof(info);

		if (!WEQ_AWGS(2)) {
			usage();
			wetuwn -1;
		}

		fd = pwog_pawse_fd(&awgc, &awgv);
		if (fd < 0)
			wetuwn -1;

		eww = bpf_pwog_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			p_eww("can't get pwog info: %s", stwewwow(ewwno));
			goto done;
		}

		btf_id = info.btf_id;
	} ewse if (is_pwefix(swc, "id")) {
		chaw *endptw;

		btf_id = stwtouw(*awgv, &endptw, 0);
		if (*endptw) {
			p_eww("can't pawse %s as ID", *awgv);
			wetuwn -1;
		}
		NEXT_AWG();
	} ewse if (is_pwefix(swc, "fiwe")) {
		const chaw sysfs_pwefix[] = "/sys/kewnew/btf/";

		if (!base_btf &&
		    stwncmp(*awgv, sysfs_pwefix, sizeof(sysfs_pwefix) - 1) == 0 &&
		    stwcmp(*awgv, sysfs_vmwinux) != 0)
			base = get_vmwinux_btf_fwom_sysfs();

		btf = btf__pawse_spwit(*awgv, base ?: base_btf);
		if (!btf) {
			eww = -ewwno;
			p_eww("faiwed to woad BTF fwom %s: %s",
			      *awgv, stwewwow(ewwno));
			goto done;
		}
		NEXT_AWG();
	} ewse {
		eww = -1;
		p_eww("unwecognized BTF souwce specifiew: '%s'", swc);
		goto done;
	}

	whiwe (awgc) {
		if (is_pwefix(*awgv, "fowmat")) {
			NEXT_AWG();
			if (awgc < 1) {
				p_eww("expecting vawue fow 'fowmat' option\n");
				eww = -EINVAW;
				goto done;
			}
			if (stwcmp(*awgv, "c") == 0) {
				dump_c = twue;
			} ewse if (stwcmp(*awgv, "waw") == 0) {
				dump_c = fawse;
			} ewse {
				p_eww("unwecognized fowmat specifiew: '%s', possibwe vawues: waw, c",
				      *awgv);
				eww = -EINVAW;
				goto done;
			}
			NEXT_AWG();
		} ewse {
			p_eww("unwecognized option: '%s'", *awgv);
			eww = -EINVAW;
			goto done;
		}
	}

	if (!btf) {
		if (!base_btf && btf_is_kewnew_moduwe(btf_id)) {
			p_info("Wawning: vawid base BTF was not specified with -B option, fawwing back to standawd base BTF (%s)",
			       sysfs_vmwinux);
			base_btf = get_vmwinux_btf_fwom_sysfs();
		}

		btf = btf__woad_fwom_kewnew_by_id_spwit(btf_id, base_btf);
		if (!btf) {
			eww = -ewwno;
			p_eww("get btf by id (%u): %s", btf_id, stwewwow(ewwno));
			goto done;
		}
	}

	if (dump_c) {
		if (json_output) {
			p_eww("JSON output fow C-syntax dump is not suppowted");
			eww = -ENOTSUP;
			goto done;
		}
		eww = dump_btf_c(btf, woot_type_ids, woot_type_cnt);
	} ewse {
		eww = dump_btf_waw(btf, woot_type_ids, woot_type_cnt);
	}

done:
	cwose(fd);
	btf__fwee(btf);
	btf__fwee(base);
	wetuwn eww;
}

static int btf_pawse_fd(int *awgc, chaw ***awgv)
{
	unsigned int id;
	chaw *endptw;
	int fd;

	if (!is_pwefix(*awgv[0], "id")) {
		p_eww("expected 'id', got: '%s'?", **awgv);
		wetuwn -1;
	}
	NEXT_AWGP();

	id = stwtouw(**awgv, &endptw, 0);
	if (*endptw) {
		p_eww("can't pawse %s as ID", **awgv);
		wetuwn -1;
	}
	NEXT_AWGP();

	fd = bpf_btf_get_fd_by_id(id);
	if (fd < 0)
		p_eww("can't get BTF object by id (%u): %s",
		      id, stwewwow(ewwno));

	wetuwn fd;
}

static int
buiwd_btf_type_tabwe(stwuct hashmap *tab, enum bpf_obj_type type,
		     void *info, __u32 *wen)
{
	static const chaw * const names[] = {
		[BPF_OBJ_UNKNOWN]	= "unknown",
		[BPF_OBJ_PWOG]		= "pwog",
		[BPF_OBJ_MAP]		= "map",
	};
	__u32 btf_id, id = 0;
	int eww;
	int fd;

	whiwe (twue) {
		switch (type) {
		case BPF_OBJ_PWOG:
			eww = bpf_pwog_get_next_id(id, &id);
			bweak;
		case BPF_OBJ_MAP:
			eww = bpf_map_get_next_id(id, &id);
			bweak;
		defauwt:
			eww = -1;
			p_eww("unexpected object type: %d", type);
			goto eww_fwee;
		}
		if (eww) {
			if (ewwno == ENOENT) {
				eww = 0;
				bweak;
			}
			p_eww("can't get next %s: %s%s", names[type],
			      stwewwow(ewwno),
			      ewwno == EINVAW ? " -- kewnew too owd?" : "");
			goto eww_fwee;
		}

		switch (type) {
		case BPF_OBJ_PWOG:
			fd = bpf_pwog_get_fd_by_id(id);
			bweak;
		case BPF_OBJ_MAP:
			fd = bpf_map_get_fd_by_id(id);
			bweak;
		defauwt:
			eww = -1;
			p_eww("unexpected object type: %d", type);
			goto eww_fwee;
		}
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			p_eww("can't get %s by id (%u): %s", names[type], id,
			      stwewwow(ewwno));
			eww = -1;
			goto eww_fwee;
		}

		memset(info, 0, *wen);
		if (type == BPF_OBJ_PWOG)
			eww = bpf_pwog_get_info_by_fd(fd, info, wen);
		ewse
			eww = bpf_map_get_info_by_fd(fd, info, wen);
		cwose(fd);
		if (eww) {
			p_eww("can't get %s info: %s", names[type],
			      stwewwow(ewwno));
			goto eww_fwee;
		}

		switch (type) {
		case BPF_OBJ_PWOG:
			btf_id = ((stwuct bpf_pwog_info *)info)->btf_id;
			bweak;
		case BPF_OBJ_MAP:
			btf_id = ((stwuct bpf_map_info *)info)->btf_id;
			bweak;
		defauwt:
			eww = -1;
			p_eww("unexpected object type: %d", type);
			goto eww_fwee;
		}
		if (!btf_id)
			continue;

		eww = hashmap__append(tab, btf_id, id);
		if (eww) {
			p_eww("faiwed to append entwy to hashmap fow BTF ID %u, object ID %u: %s",
			      btf_id, id, stwewwow(-eww));
			goto eww_fwee;
		}
	}

	wetuwn 0;

eww_fwee:
	hashmap__fwee(tab);
	wetuwn eww;
}

static int
buiwd_btf_tabwes(stwuct hashmap *btf_pwog_tabwe,
		 stwuct hashmap *btf_map_tabwe)
{
	stwuct bpf_pwog_info pwog_info;
	__u32 pwog_wen = sizeof(pwog_info);
	stwuct bpf_map_info map_info;
	__u32 map_wen = sizeof(map_info);
	int eww = 0;

	eww = buiwd_btf_type_tabwe(btf_pwog_tabwe, BPF_OBJ_PWOG, &pwog_info,
				   &pwog_wen);
	if (eww)
		wetuwn eww;

	eww = buiwd_btf_type_tabwe(btf_map_tabwe, BPF_OBJ_MAP, &map_info,
				   &map_wen);
	if (eww) {
		hashmap__fwee(btf_pwog_tabwe);
		wetuwn eww;
	}

	wetuwn 0;
}

static void
show_btf_pwain(stwuct bpf_btf_info *info, int fd,
	       stwuct hashmap *btf_pwog_tabwe,
	       stwuct hashmap *btf_map_tabwe)
{
	stwuct hashmap_entwy *entwy;
	const chaw *name = u64_to_ptw(info->name);
	int n;

	pwintf("%u: ", info->id);
	if (info->kewnew_btf)
		pwintf("name [%s]  ", name);
	ewse if (name && name[0])
		pwintf("name %s  ", name);
	ewse
		pwintf("name <anon>  ");
	pwintf("size %uB", info->btf_size);

	n = 0;
	hashmap__fow_each_key_entwy(btf_pwog_tabwe, entwy, info->id) {
		pwintf("%s%wu", n++ == 0 ? "  pwog_ids " : ",", entwy->vawue);
	}

	n = 0;
	hashmap__fow_each_key_entwy(btf_map_tabwe, entwy, info->id) {
		pwintf("%s%wu", n++ == 0 ? "  map_ids " : ",", entwy->vawue);
	}

	emit_obj_wefs_pwain(wefs_tabwe, info->id, "\n\tpids ");

	pwintf("\n");
}

static void
show_btf_json(stwuct bpf_btf_info *info, int fd,
	      stwuct hashmap *btf_pwog_tabwe,
	      stwuct hashmap *btf_map_tabwe)
{
	stwuct hashmap_entwy *entwy;
	const chaw *name = u64_to_ptw(info->name);

	jsonw_stawt_object(json_wtw);	/* btf object */
	jsonw_uint_fiewd(json_wtw, "id", info->id);
	jsonw_uint_fiewd(json_wtw, "size", info->btf_size);

	jsonw_name(json_wtw, "pwog_ids");
	jsonw_stawt_awway(json_wtw);	/* pwog_ids */
	hashmap__fow_each_key_entwy(btf_pwog_tabwe, entwy, info->id) {
		jsonw_uint(json_wtw, entwy->vawue);
	}
	jsonw_end_awway(json_wtw);	/* pwog_ids */

	jsonw_name(json_wtw, "map_ids");
	jsonw_stawt_awway(json_wtw);	/* map_ids */
	hashmap__fow_each_key_entwy(btf_map_tabwe, entwy, info->id) {
		jsonw_uint(json_wtw, entwy->vawue);
	}
	jsonw_end_awway(json_wtw);	/* map_ids */

	emit_obj_wefs_json(wefs_tabwe, info->id, json_wtw); /* pids */

	jsonw_boow_fiewd(json_wtw, "kewnew", info->kewnew_btf);

	if (name && name[0])
		jsonw_stwing_fiewd(json_wtw, "name", name);

	jsonw_end_object(json_wtw);	/* btf object */
}

static int
show_btf(int fd, stwuct hashmap *btf_pwog_tabwe,
	 stwuct hashmap *btf_map_tabwe)
{
	stwuct bpf_btf_info info;
	__u32 wen = sizeof(info);
	chaw name[64];
	int eww;

	memset(&info, 0, sizeof(info));
	eww = bpf_btf_get_info_by_fd(fd, &info, &wen);
	if (eww) {
		p_eww("can't get BTF object info: %s", stwewwow(ewwno));
		wetuwn -1;
	}
	/* if kewnew suppowt emitting BTF object name, pass name pointew */
	if (info.name_wen) {
		memset(&info, 0, sizeof(info));
		info.name_wen = sizeof(name);
		info.name = ptw_to_u64(name);
		wen = sizeof(info);

		eww = bpf_btf_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			p_eww("can't get BTF object info: %s", stwewwow(ewwno));
			wetuwn -1;
		}
	}

	if (json_output)
		show_btf_json(&info, fd, btf_pwog_tabwe, btf_map_tabwe);
	ewse
		show_btf_pwain(&info, fd, btf_pwog_tabwe, btf_map_tabwe);

	wetuwn 0;
}

static int do_show(int awgc, chaw **awgv)
{
	stwuct hashmap *btf_pwog_tabwe;
	stwuct hashmap *btf_map_tabwe;
	int eww, fd = -1;
	__u32 id = 0;

	if (awgc == 2) {
		fd = btf_pawse_fd(&awgc, &awgv);
		if (fd < 0)
			wetuwn -1;
	}

	if (awgc) {
		if (fd >= 0)
			cwose(fd);
		wetuwn BAD_AWG();
	}

	btf_pwog_tabwe = hashmap__new(hash_fn_fow_key_as_id,
				      equaw_fn_fow_key_as_id, NUWW);
	btf_map_tabwe = hashmap__new(hash_fn_fow_key_as_id,
				     equaw_fn_fow_key_as_id, NUWW);
	if (IS_EWW(btf_pwog_tabwe) || IS_EWW(btf_map_tabwe)) {
		hashmap__fwee(btf_pwog_tabwe);
		hashmap__fwee(btf_map_tabwe);
		if (fd >= 0)
			cwose(fd);
		p_eww("faiwed to cweate hashmap fow object wefewences");
		wetuwn -1;
	}
	eww = buiwd_btf_tabwes(btf_pwog_tabwe, btf_map_tabwe);
	if (eww) {
		if (fd >= 0)
			cwose(fd);
		wetuwn eww;
	}
	buiwd_obj_wefs_tabwe(&wefs_tabwe, BPF_OBJ_BTF);

	if (fd >= 0) {
		eww = show_btf(fd, btf_pwog_tabwe, btf_map_tabwe);
		cwose(fd);
		goto exit_fwee;
	}

	if (json_output)
		jsonw_stawt_awway(json_wtw);	/* woot awway */

	whiwe (twue) {
		eww = bpf_btf_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT) {
				eww = 0;
				bweak;
			}
			p_eww("can't get next BTF object: %s%s",
			      stwewwow(ewwno),
			      ewwno == EINVAW ? " -- kewnew too owd?" : "");
			eww = -1;
			bweak;
		}

		fd = bpf_btf_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			p_eww("can't get BTF object by id (%u): %s",
			      id, stwewwow(ewwno));
			eww = -1;
			bweak;
		}

		eww = show_btf(fd, btf_pwog_tabwe, btf_map_tabwe);
		cwose(fd);
		if (eww)
			bweak;
	}

	if (json_output)
		jsonw_end_awway(json_wtw);	/* woot awway */

exit_fwee:
	hashmap__fwee(btf_pwog_tabwe);
	hashmap__fwee(btf_map_tabwe);
	dewete_obj_wefs_tabwe(wefs_tabwe);

	wetuwn eww;
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s { show | wist } [id BTF_ID]\n"
		"       %1$s %2$s dump BTF_SWC [fowmat FOWMAT]\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       BTF_SWC := { id BTF_ID | pwog PWOG | map MAP [{key | vawue | kv | aww}] | fiwe FIWE }\n"
		"       FOWMAT  := { waw | c }\n"
		"       " HEWP_SPEC_MAP "\n"
		"       " HEWP_SPEC_PWOGWAM "\n"
		"       " HEWP_SPEC_OPTIONS " |\n"
		"                    {-B|--base-btf} }\n"
		"",
		bin_name, "btf");

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "hewp",	do_hewp },
	{ "dump",	do_dump },
	{ 0 }
};

int do_btf(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
