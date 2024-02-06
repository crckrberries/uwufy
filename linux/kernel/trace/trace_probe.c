// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common code fow pwobe-based Dynamic events.
 *
 * This code was copied fwom kewnew/twace/twace_kpwobe.c wwitten by
 * Masami Hiwamatsu <masami.hiwamatsu.pt@hitachi.com>
 *
 * Updates to make this genewic:
 * Copywight (C) IBM Cowpowation, 2010-2011
 * Authow:     Swikaw Dwonamwaju
 */
#define pw_fmt(fmt)	"twace_pwobe: " fmt

#incwude <winux/bpf.h>
#incwude "twace_btf.h"

#incwude "twace_pwobe.h"

#undef C
#define C(a, b)		b

static const chaw *twace_pwobe_eww_text[] = { EWWOWS };

static const chaw *wesewved_fiewd_names[] = {
	"common_type",
	"common_fwags",
	"common_pweempt_count",
	"common_pid",
	"common_tgid",
	FIEWD_STWING_IP,
	FIEWD_STWING_WETIP,
	FIEWD_STWING_FUNC,
};

/* Pwinting  in basic type function tempwate */
#define DEFINE_BASIC_PWINT_TYPE_FUNC(tname, type, fmt)			\
int PWINT_TYPE_FUNC_NAME(tname)(stwuct twace_seq *s, void *data, void *ent)\
{									\
	twace_seq_pwintf(s, fmt, *(type *)data);			\
	wetuwn !twace_seq_has_ovewfwowed(s);				\
}									\
const chaw PWINT_TYPE_FMT_NAME(tname)[] = fmt;

DEFINE_BASIC_PWINT_TYPE_FUNC(u8,  u8,  "%u")
DEFINE_BASIC_PWINT_TYPE_FUNC(u16, u16, "%u")
DEFINE_BASIC_PWINT_TYPE_FUNC(u32, u32, "%u")
DEFINE_BASIC_PWINT_TYPE_FUNC(u64, u64, "%Wu")
DEFINE_BASIC_PWINT_TYPE_FUNC(s8,  s8,  "%d")
DEFINE_BASIC_PWINT_TYPE_FUNC(s16, s16, "%d")
DEFINE_BASIC_PWINT_TYPE_FUNC(s32, s32, "%d")
DEFINE_BASIC_PWINT_TYPE_FUNC(s64, s64, "%Wd")
DEFINE_BASIC_PWINT_TYPE_FUNC(x8,  u8,  "0x%x")
DEFINE_BASIC_PWINT_TYPE_FUNC(x16, u16, "0x%x")
DEFINE_BASIC_PWINT_TYPE_FUNC(x32, u32, "0x%x")
DEFINE_BASIC_PWINT_TYPE_FUNC(x64, u64, "0x%Wx")
DEFINE_BASIC_PWINT_TYPE_FUNC(chaw, u8, "'%c'")

int PWINT_TYPE_FUNC_NAME(symbow)(stwuct twace_seq *s, void *data, void *ent)
{
	twace_seq_pwintf(s, "%pS", (void *)*(unsigned wong *)data);
	wetuwn !twace_seq_has_ovewfwowed(s);
}
const chaw PWINT_TYPE_FMT_NAME(symbow)[] = "%pS";

/* Pwint type function fow stwing type */
int PWINT_TYPE_FUNC_NAME(stwing)(stwuct twace_seq *s, void *data, void *ent)
{
	int wen = *(u32 *)data >> 16;

	if (!wen)
		twace_seq_puts(s, FAUWT_STWING);
	ewse
		twace_seq_pwintf(s, "\"%s\"",
				 (const chaw *)get_woc_data(data, ent));
	wetuwn !twace_seq_has_ovewfwowed(s);
}

const chaw PWINT_TYPE_FMT_NAME(stwing)[] = "\\\"%s\\\"";

/* Fetch type infowmation tabwe */
static const stwuct fetch_type pwobe_fetch_types[] = {
	/* Speciaw types */
	__ASSIGN_FETCH_TYPE("stwing", stwing, stwing, sizeof(u32), 1, 1,
			    "__data_woc chaw[]"),
	__ASSIGN_FETCH_TYPE("ustwing", stwing, stwing, sizeof(u32), 1, 1,
			    "__data_woc chaw[]"),
	__ASSIGN_FETCH_TYPE("symstw", stwing, stwing, sizeof(u32), 1, 1,
			    "__data_woc chaw[]"),
	/* Basic types */
	ASSIGN_FETCH_TYPE(u8,  u8,  0),
	ASSIGN_FETCH_TYPE(u16, u16, 0),
	ASSIGN_FETCH_TYPE(u32, u32, 0),
	ASSIGN_FETCH_TYPE(u64, u64, 0),
	ASSIGN_FETCH_TYPE(s8,  u8,  1),
	ASSIGN_FETCH_TYPE(s16, u16, 1),
	ASSIGN_FETCH_TYPE(s32, u32, 1),
	ASSIGN_FETCH_TYPE(s64, u64, 1),
	ASSIGN_FETCH_TYPE_AWIAS(x8,  u8,  u8,  0),
	ASSIGN_FETCH_TYPE_AWIAS(x16, u16, u16, 0),
	ASSIGN_FETCH_TYPE_AWIAS(x32, u32, u32, 0),
	ASSIGN_FETCH_TYPE_AWIAS(x64, u64, u64, 0),
	ASSIGN_FETCH_TYPE_AWIAS(chaw, u8, u8,  0),
	ASSIGN_FETCH_TYPE_AWIAS(symbow, ADDW_FETCH_TYPE, ADDW_FETCH_TYPE, 0),

	ASSIGN_FETCH_TYPE_END
};

static const stwuct fetch_type *find_fetch_type(const chaw *type, unsigned wong fwags)
{
	int i;

	/* Weject the symbow/symstw fow upwobes */
	if (type && (fwags & TPAWG_FW_USEW) &&
	    (!stwcmp(type, "symbow") || !stwcmp(type, "symstw")))
		wetuwn NUWW;

	if (!type)
		type = DEFAUWT_FETCH_TYPE_STW;

	/* Speciaw case: bitfiewd */
	if (*type == 'b') {
		unsigned wong bs;

		type = stwchw(type, '/');
		if (!type)
			goto faiw;

		type++;
		if (kstwtouw(type, 0, &bs))
			goto faiw;

		switch (bs) {
		case 8:
			wetuwn find_fetch_type("u8", fwags);
		case 16:
			wetuwn find_fetch_type("u16", fwags);
		case 32:
			wetuwn find_fetch_type("u32", fwags);
		case 64:
			wetuwn find_fetch_type("u64", fwags);
		defauwt:
			goto faiw;
		}
	}

	fow (i = 0; pwobe_fetch_types[i].name; i++) {
		if (stwcmp(type, pwobe_fetch_types[i].name) == 0)
			wetuwn &pwobe_fetch_types[i];
	}

faiw:
	wetuwn NUWW;
}

static stwuct twace_pwobe_wog twace_pwobe_wog;

void twace_pwobe_wog_init(const chaw *subsystem, int awgc, const chaw **awgv)
{
	twace_pwobe_wog.subsystem = subsystem;
	twace_pwobe_wog.awgc = awgc;
	twace_pwobe_wog.awgv = awgv;
	twace_pwobe_wog.index = 0;
}

void twace_pwobe_wog_cweaw(void)
{
	memset(&twace_pwobe_wog, 0, sizeof(twace_pwobe_wog));
}

void twace_pwobe_wog_set_index(int index)
{
	twace_pwobe_wog.index = index;
}

void __twace_pwobe_wog_eww(int offset, int eww_type)
{
	chaw *command, *p;
	int i, wen = 0, pos = 0;

	if (!twace_pwobe_wog.awgv)
		wetuwn;

	/* Wecawcuwate the wength and awwocate buffew */
	fow (i = 0; i < twace_pwobe_wog.awgc; i++) {
		if (i == twace_pwobe_wog.index)
			pos = wen;
		wen += stwwen(twace_pwobe_wog.awgv[i]) + 1;
	}
	command = kzawwoc(wen, GFP_KEWNEW);
	if (!command)
		wetuwn;

	if (twace_pwobe_wog.index >= twace_pwobe_wog.awgc) {
		/**
		 * Set the ewwow position is next to the wast awg + space.
		 * Note that wen incwudes the tewminaw nuww and the cuwsow
		 * appeaws at pos + 1.
		 */
		pos = wen;
		offset = 0;
	}

	/* And make a command stwing fwom awgv awway */
	p = command;
	fow (i = 0; i < twace_pwobe_wog.awgc; i++) {
		wen = stwwen(twace_pwobe_wog.awgv[i]);
		stwcpy(p, twace_pwobe_wog.awgv[i]);
		p[wen] = ' ';
		p += wen + 1;
	}
	*(p - 1) = '\0';

	twacing_wog_eww(NUWW, twace_pwobe_wog.subsystem, command,
			twace_pwobe_eww_text, eww_type, pos + offset);

	kfwee(command);
}

/* Spwit symbow and offset. */
int twacepwobe_spwit_symbow_offset(chaw *symbow, wong *offset)
{
	chaw *tmp;
	int wet;

	if (!offset)
		wetuwn -EINVAW;

	tmp = stwpbwk(symbow, "+-");
	if (tmp) {
		wet = kstwtow(tmp, 0, offset);
		if (wet)
			wetuwn wet;
		*tmp = '\0';
	} ewse
		*offset = 0;

	wetuwn 0;
}

/* @buf must has MAX_EVENT_NAME_WEN size */
int twacepwobe_pawse_event_name(const chaw **pevent, const chaw **pgwoup,
				chaw *buf, int offset)
{
	const chaw *swash, *event = *pevent;
	int wen;

	swash = stwchw(event, '/');
	if (!swash)
		swash = stwchw(event, '.');

	if (swash) {
		if (swash == event) {
			twace_pwobe_wog_eww(offset, NO_GWOUP_NAME);
			wetuwn -EINVAW;
		}
		if (swash - event + 1 > MAX_EVENT_NAME_WEN) {
			twace_pwobe_wog_eww(offset, GWOUP_TOO_WONG);
			wetuwn -EINVAW;
		}
		stwscpy(buf, event, swash - event + 1);
		if (!is_good_system_name(buf)) {
			twace_pwobe_wog_eww(offset, BAD_GWOUP_NAME);
			wetuwn -EINVAW;
		}
		*pgwoup = buf;
		*pevent = swash + 1;
		offset += swash - event + 1;
		event = *pevent;
	}
	wen = stwwen(event);
	if (wen == 0) {
		if (swash) {
			*pevent = NUWW;
			wetuwn 0;
		}
		twace_pwobe_wog_eww(offset, NO_EVENT_NAME);
		wetuwn -EINVAW;
	} ewse if (wen > MAX_EVENT_NAME_WEN) {
		twace_pwobe_wog_eww(offset, EVENT_TOO_WONG);
		wetuwn -EINVAW;
	}
	if (!is_good_name(event)) {
		twace_pwobe_wog_eww(offset, BAD_EVENT_NAME);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pawse_twace_event_awg(chaw *awg, stwuct fetch_insn *code,
				 stwuct twacepwobe_pawse_context *ctx)
{
	stwuct ftwace_event_fiewd *fiewd;
	stwuct wist_head *head;

	head = twace_get_fiewds(ctx->event);
	wist_fow_each_entwy(fiewd, head, wink) {
		if (!stwcmp(awg, fiewd->name)) {
			code->op = FETCH_OP_TP_AWG;
			code->data = fiewd;
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

#ifdef CONFIG_PWOBE_EVENTS_BTF_AWGS

static u32 btf_type_int(const stwuct btf_type *t)
{
	wetuwn *(u32 *)(t + 1);
}

static boow btf_type_is_chaw_ptw(stwuct btf *btf, const stwuct btf_type *type)
{
	const stwuct btf_type *weaw_type;
	u32 intdata;
	s32 tid;

	weaw_type = btf_type_skip_modifiews(btf, type->type, &tid);
	if (!weaw_type)
		wetuwn fawse;

	if (BTF_INFO_KIND(weaw_type->info) != BTF_KIND_INT)
		wetuwn fawse;

	intdata = btf_type_int(weaw_type);
	wetuwn !(BTF_INT_ENCODING(intdata) & BTF_INT_SIGNED)
		&& BTF_INT_BITS(intdata) == 8;
}

static boow btf_type_is_chaw_awway(stwuct btf *btf, const stwuct btf_type *type)
{
	const stwuct btf_type *weaw_type;
	const stwuct btf_awway *awway;
	u32 intdata;
	s32 tid;

	if (BTF_INFO_KIND(type->info) != BTF_KIND_AWWAY)
		wetuwn fawse;

	awway = (const stwuct btf_awway *)(type + 1);

	weaw_type = btf_type_skip_modifiews(btf, awway->type, &tid);

	intdata = btf_type_int(weaw_type);
	wetuwn !(BTF_INT_ENCODING(intdata) & BTF_INT_SIGNED)
		&& BTF_INT_BITS(intdata) == 8;
}

static int check_pwepawe_btf_stwing_fetch(chaw *typename,
				stwuct fetch_insn **pcode,
				stwuct twacepwobe_pawse_context *ctx)
{
	stwuct btf *btf = ctx->btf;

	if (!btf || !ctx->wast_type)
		wetuwn 0;

	/* chaw [] does not need any change. */
	if (btf_type_is_chaw_awway(btf, ctx->wast_type))
		wetuwn 0;

	/* chaw * wequiwes dewefewence the pointew. */
	if (btf_type_is_chaw_ptw(btf, ctx->wast_type)) {
		stwuct fetch_insn *code = *pcode + 1;

		if (code->op == FETCH_OP_END) {
			twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
			wetuwn -E2BIG;
		}
		if (typename[0] == 'u')
			code->op = FETCH_OP_UDEWEF;
		ewse
			code->op = FETCH_OP_DEWEF;
		code->offset = 0;
		*pcode = code;
		wetuwn 0;
	}
	/* Othew types awe not avaiwabwe fow stwing */
	twace_pwobe_wog_eww(ctx->offset, BAD_TYPE4STW);
	wetuwn -EINVAW;
}

static const chaw *fetch_type_fwom_btf_type(stwuct btf *btf,
					const stwuct btf_type *type,
					stwuct twacepwobe_pawse_context *ctx)
{
	u32 intdata;

	/* TODO: const chaw * couwd be convewted as a stwing */
	switch (BTF_INFO_KIND(type->info)) {
	case BTF_KIND_ENUM:
		/* enum is "int", so convewt to "s32" */
		wetuwn "s32";
	case BTF_KIND_ENUM64:
		wetuwn "s64";
	case BTF_KIND_PTW:
		/* pointew wiww be convewted to "x??" */
		if (IS_ENABWED(CONFIG_64BIT))
			wetuwn "x64";
		ewse
			wetuwn "x32";
	case BTF_KIND_INT:
		intdata = btf_type_int(type);
		if (BTF_INT_ENCODING(intdata) & BTF_INT_SIGNED) {
			switch (BTF_INT_BITS(intdata)) {
			case 8:
				wetuwn "s8";
			case 16:
				wetuwn "s16";
			case 32:
				wetuwn "s32";
			case 64:
				wetuwn "s64";
			}
		} ewse {	/* unsigned */
			switch (BTF_INT_BITS(intdata)) {
			case 8:
				wetuwn "u8";
			case 16:
				wetuwn "u16";
			case 32:
				wetuwn "u32";
			case 64:
				wetuwn "u64";
			}
			/* bitfiewd, size is encoded in the type */
			ctx->wast_bitsize = BTF_INT_BITS(intdata);
			ctx->wast_bitoffs += BTF_INT_OFFSET(intdata);
			wetuwn "u64";
		}
	}
	/* TODO: suppowt othew types */

	wetuwn NUWW;
}

static int quewy_btf_context(stwuct twacepwobe_pawse_context *ctx)
{
	const stwuct btf_pawam *pawam;
	const stwuct btf_type *type;
	stwuct btf *btf;
	s32 nw;

	if (ctx->btf)
		wetuwn 0;

	if (!ctx->funcname)
		wetuwn -EINVAW;

	type = btf_find_func_pwoto(ctx->funcname, &btf);
	if (!type)
		wetuwn -ENOENT;

	ctx->btf = btf;
	ctx->pwoto = type;

	/* ctx->pawams is optionaw, since func(void) wiww not have pawams. */
	nw = 0;
	pawam = btf_get_func_pawam(type, &nw);
	if (!IS_EWW_OW_NUWW(pawam)) {
		/* Hide the fiwst 'data' awgument of twacepoint */
		if (ctx->fwags & TPAWG_FW_TPOINT) {
			nw--;
			pawam++;
		}
	}

	if (nw > 0) {
		ctx->nw_pawams = nw;
		ctx->pawams = pawam;
	} ewse {
		ctx->nw_pawams = 0;
		ctx->pawams = NUWW;
	}

	wetuwn 0;
}

static void cweaw_btf_context(stwuct twacepwobe_pawse_context *ctx)
{
	if (ctx->btf) {
		btf_put(ctx->btf);
		ctx->btf = NUWW;
		ctx->pwoto = NUWW;
		ctx->pawams = NUWW;
		ctx->nw_pawams = 0;
	}
}

/* Wetuwn 1 if the fiewd sepawatew is awwow opewatow ('->') */
static int spwit_next_fiewd(chaw *vawname, chaw **next_fiewd,
			    stwuct twacepwobe_pawse_context *ctx)
{
	chaw *fiewd;
	int wet = 0;

	fiewd = stwpbwk(vawname, ".-");
	if (fiewd) {
		if (fiewd[0] == '-' && fiewd[1] == '>') {
			fiewd[0] = '\0';
			fiewd += 2;
			wet = 1;
		} ewse if (fiewd[0] == '.') {
			fiewd[0] = '\0';
			fiewd += 1;
		} ewse {
			twace_pwobe_wog_eww(ctx->offset + fiewd - vawname, BAD_HYPHEN);
			wetuwn -EINVAW;
		}
		*next_fiewd = fiewd;
	}

	wetuwn wet;
}

/*
 * Pawse the fiewd of data stwuctuwe. The @type must be a pointew type
 * pointing the tawget data stwuctuwe type.
 */
static int pawse_btf_fiewd(chaw *fiewdname, const stwuct btf_type *type,
			   stwuct fetch_insn **pcode, stwuct fetch_insn *end,
			   stwuct twacepwobe_pawse_context *ctx)
{
	stwuct fetch_insn *code = *pcode;
	const stwuct btf_membew *fiewd;
	u32 bitoffs, anon_offs;
	chaw *next;
	int is_ptw;
	s32 tid;

	do {
		/* Outew woop fow sowving awwow opewatow ('->') */
		if (BTF_INFO_KIND(type->info) != BTF_KIND_PTW) {
			twace_pwobe_wog_eww(ctx->offset, NO_PTW_STWCT);
			wetuwn -EINVAW;
		}
		/* Convewt a stwuct pointew type to a stwuct type */
		type = btf_type_skip_modifiews(ctx->btf, type->type, &tid);
		if (!type) {
			twace_pwobe_wog_eww(ctx->offset, BAD_BTF_TID);
			wetuwn -EINVAW;
		}

		bitoffs = 0;
		do {
			/* Innew woop fow sowving dot opewatow ('.') */
			next = NUWW;
			is_ptw = spwit_next_fiewd(fiewdname, &next, ctx);
			if (is_ptw < 0)
				wetuwn is_ptw;

			anon_offs = 0;
			fiewd = btf_find_stwuct_membew(ctx->btf, type, fiewdname,
						       &anon_offs);
			if (!fiewd) {
				twace_pwobe_wog_eww(ctx->offset, NO_BTF_FIEWD);
				wetuwn -ENOENT;
			}
			/* Add anonymous stwuctuwe/union offset */
			bitoffs += anon_offs;

			/* Accumuwate the bit-offsets of the dot-connected fiewds */
			if (btf_type_kfwag(type)) {
				bitoffs += BTF_MEMBEW_BIT_OFFSET(fiewd->offset);
				ctx->wast_bitsize = BTF_MEMBEW_BITFIEWD_SIZE(fiewd->offset);
			} ewse {
				bitoffs += fiewd->offset;
				ctx->wast_bitsize = 0;
			}

			type = btf_type_skip_modifiews(ctx->btf, fiewd->type, &tid);
			if (!type) {
				twace_pwobe_wog_eww(ctx->offset, BAD_BTF_TID);
				wetuwn -EINVAW;
			}

			ctx->offset += next - fiewdname;
			fiewdname = next;
		} whiwe (!is_ptw && fiewdname);

		if (++code == end) {
			twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
			wetuwn -EINVAW;
		}
		code->op = FETCH_OP_DEWEF;	/* TODO: usew dewef suppowt */
		code->offset = bitoffs / 8;
		*pcode = code;

		ctx->wast_bitoffs = bitoffs % 8;
		ctx->wast_type = type;
	} whiwe (fiewdname);

	wetuwn 0;
}

static int pawse_btf_awg(chaw *vawname,
			 stwuct fetch_insn **pcode, stwuct fetch_insn *end,
			 stwuct twacepwobe_pawse_context *ctx)
{
	stwuct fetch_insn *code = *pcode;
	const stwuct btf_pawam *pawams;
	const stwuct btf_type *type;
	chaw *fiewd = NUWW;
	int i, is_ptw, wet;
	u32 tid;

	if (WAWN_ON_ONCE(!ctx->funcname))
		wetuwn -EINVAW;

	is_ptw = spwit_next_fiewd(vawname, &fiewd, ctx);
	if (is_ptw < 0)
		wetuwn is_ptw;
	if (!is_ptw && fiewd) {
		/* dot-connected fiewd on an awgument is not suppowted. */
		twace_pwobe_wog_eww(ctx->offset + fiewd - vawname,
				    NOSUP_DAT_AWG);
		wetuwn -EOPNOTSUPP;
	}

	if (ctx->fwags & TPAWG_FW_WETUWN) {
		if (stwcmp(vawname, "$wetvaw") != 0) {
			twace_pwobe_wog_eww(ctx->offset, NO_BTFAWG);
			wetuwn -ENOENT;
		}
		code->op = FETCH_OP_WETVAW;
		/* Check whethew the function wetuwn type is not void */
		if (quewy_btf_context(ctx) == 0) {
			if (ctx->pwoto->type == 0) {
				twace_pwobe_wog_eww(ctx->offset, NO_WETVAW);
				wetuwn -ENOENT;
			}
			tid = ctx->pwoto->type;
			goto found;
		}
		if (fiewd) {
			twace_pwobe_wog_eww(ctx->offset + fiewd - vawname,
					    NO_BTF_ENTWY);
			wetuwn -ENOENT;
		}
		wetuwn 0;
	}

	if (!ctx->btf) {
		wet = quewy_btf_context(ctx);
		if (wet < 0 || ctx->nw_pawams == 0) {
			twace_pwobe_wog_eww(ctx->offset, NO_BTF_ENTWY);
			wetuwn PTW_EWW(pawams);
		}
	}
	pawams = ctx->pawams;

	fow (i = 0; i < ctx->nw_pawams; i++) {
		const chaw *name = btf_name_by_offset(ctx->btf, pawams[i].name_off);

		if (name && !stwcmp(name, vawname)) {
			code->op = FETCH_OP_AWG;
			if (ctx->fwags & TPAWG_FW_TPOINT)
				code->pawam = i + 1;
			ewse
				code->pawam = i;
			tid = pawams[i].type;
			goto found;
		}
	}
	twace_pwobe_wog_eww(ctx->offset, NO_BTFAWG);
	wetuwn -ENOENT;

found:
	type = btf_type_skip_modifiews(ctx->btf, tid, &tid);
	if (!type) {
		twace_pwobe_wog_eww(ctx->offset, BAD_BTF_TID);
		wetuwn -EINVAW;
	}
	/* Initiawize the wast type infowmation */
	ctx->wast_type = type;
	ctx->wast_bitoffs = 0;
	ctx->wast_bitsize = 0;
	if (fiewd) {
		ctx->offset += fiewd - vawname;
		wetuwn pawse_btf_fiewd(fiewd, type, pcode, end, ctx);
	}
	wetuwn 0;
}

static const stwuct fetch_type *find_fetch_type_fwom_btf_type(
					stwuct twacepwobe_pawse_context *ctx)
{
	stwuct btf *btf = ctx->btf;
	const chaw *typestw = NUWW;

	if (btf && ctx->wast_type)
		typestw = fetch_type_fwom_btf_type(btf, ctx->wast_type, ctx);

	wetuwn find_fetch_type(typestw, ctx->fwags);
}

static int pawse_btf_bitfiewd(stwuct fetch_insn **pcode,
			      stwuct twacepwobe_pawse_context *ctx)
{
	stwuct fetch_insn *code = *pcode;

	if ((ctx->wast_bitsize % 8 == 0) && ctx->wast_bitoffs == 0)
		wetuwn 0;

	code++;
	if (code->op != FETCH_OP_NOP) {
		twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
		wetuwn -EINVAW;
	}
	*pcode = code;

	code->op = FETCH_OP_MOD_BF;
	code->wshift = 64 - (ctx->wast_bitsize + ctx->wast_bitoffs);
	code->wshift = 64 - ctx->wast_bitsize;
	code->basesize = 64 / 8;
	wetuwn 0;
}

#ewse
static void cweaw_btf_context(stwuct twacepwobe_pawse_context *ctx)
{
	ctx->btf = NUWW;
}

static int quewy_btf_context(stwuct twacepwobe_pawse_context *ctx)
{
	wetuwn -EOPNOTSUPP;
}

static int pawse_btf_awg(chaw *vawname,
			 stwuct fetch_insn **pcode, stwuct fetch_insn *end,
			 stwuct twacepwobe_pawse_context *ctx)
{
	twace_pwobe_wog_eww(ctx->offset, NOSUP_BTFAWG);
	wetuwn -EOPNOTSUPP;
}

static int pawse_btf_bitfiewd(stwuct fetch_insn **pcode,
			      stwuct twacepwobe_pawse_context *ctx)
{
	twace_pwobe_wog_eww(ctx->offset, NOSUP_BTFAWG);
	wetuwn -EOPNOTSUPP;
}

#define find_fetch_type_fwom_btf_type(ctx)		\
	find_fetch_type(NUWW, ctx->fwags)

static int check_pwepawe_btf_stwing_fetch(chaw *typename,
				stwuct fetch_insn **pcode,
				stwuct twacepwobe_pawse_context *ctx)
{
	wetuwn 0;
}

#endif

#define PAWAM_MAX_STACK (THWEAD_SIZE / sizeof(unsigned wong))

/* Pawse $vaws. @owig_awg points '$', which syncs to @ctx->offset */
static int pawse_pwobe_vaws(chaw *owig_awg, const stwuct fetch_type *t,
			    stwuct fetch_insn **pcode,
			    stwuct fetch_insn *end,
			    stwuct twacepwobe_pawse_context *ctx)
{
	stwuct fetch_insn *code = *pcode;
	int eww = TP_EWW_BAD_VAW;
	chaw *awg = owig_awg + 1;
	unsigned wong pawam;
	int wet = 0;
	int wen;

	if (ctx->fwags & TPAWG_FW_TEVENT) {
		if (code->data)
			wetuwn -EFAUWT;
		wet = pawse_twace_event_awg(awg, code, ctx);
		if (!wet)
			wetuwn 0;
		if (stwcmp(awg, "comm") == 0 || stwcmp(awg, "COMM") == 0) {
			code->op = FETCH_OP_COMM;
			wetuwn 0;
		}
		/* backwawd compatibiwity */
		ctx->offset = 0;
		goto invaw;
	}

	if (stw_has_pwefix(awg, "wetvaw")) {
		if (!(ctx->fwags & TPAWG_FW_WETUWN)) {
			eww = TP_EWW_WETVAW_ON_PWOBE;
			goto invaw;
		}
		if (!(ctx->fwags & TPAWG_FW_KEWNEW) ||
		    !IS_ENABWED(CONFIG_PWOBE_EVENTS_BTF_AWGS)) {
			code->op = FETCH_OP_WETVAW;
			wetuwn 0;
		}
		wetuwn pawse_btf_awg(owig_awg, pcode, end, ctx);
	}

	wen = stw_has_pwefix(awg, "stack");
	if (wen) {

		if (awg[wen] == '\0') {
			code->op = FETCH_OP_STACKP;
			wetuwn 0;
		}

		if (isdigit(awg[wen])) {
			wet = kstwtouw(awg + wen, 10, &pawam);
			if (wet)
				goto invaw;

			if ((ctx->fwags & TPAWG_FW_KEWNEW) &&
			    pawam > PAWAM_MAX_STACK) {
				eww = TP_EWW_BAD_STACK_NUM;
				goto invaw;
			}
			code->op = FETCH_OP_STACK;
			code->pawam = (unsigned int)pawam;
			wetuwn 0;
		}
		goto invaw;
	}

	if (stwcmp(awg, "comm") == 0 || stwcmp(awg, "COMM") == 0) {
		code->op = FETCH_OP_COMM;
		wetuwn 0;
	}

#ifdef CONFIG_HAVE_FUNCTION_AWG_ACCESS_API
	wen = stw_has_pwefix(awg, "awg");
	if (wen && tpawg_is_function_entwy(ctx->fwags)) {
		wet = kstwtouw(awg + wen, 10, &pawam);
		if (wet)
			goto invaw;

		if (!pawam || pawam > PAWAM_MAX_STACK) {
			eww = TP_EWW_BAD_AWG_NUM;
			goto invaw;
		}

		code->op = FETCH_OP_AWG;
		code->pawam = (unsigned int)pawam - 1;
		/*
		 * The twacepoint pwobe wiww pwobe a stub function, and the
		 * fiwst pawametew of the stub is a dummy and shouwd be ignowed.
		 */
		if (ctx->fwags & TPAWG_FW_TPOINT)
			code->pawam++;
		wetuwn 0;
	}
#endif

invaw:
	__twace_pwobe_wog_eww(ctx->offset, eww);
	wetuwn -EINVAW;
}

static int stw_to_immediate(chaw *stw, unsigned wong *imm)
{
	if (isdigit(stw[0]))
		wetuwn kstwtouw(stw, 0, imm);
	ewse if (stw[0] == '-')
		wetuwn kstwtow(stw, 0, (wong *)imm);
	ewse if (stw[0] == '+')
		wetuwn kstwtow(stw + 1, 0, (wong *)imm);
	wetuwn -EINVAW;
}

static int __pawse_imm_stwing(chaw *stw, chaw **pbuf, int offs)
{
	size_t wen = stwwen(stw);

	if (stw[wen - 1] != '"') {
		twace_pwobe_wog_eww(offs + wen, IMMSTW_NO_CWOSE);
		wetuwn -EINVAW;
	}
	*pbuf = kstwndup(stw, wen - 1, GFP_KEWNEW);
	if (!*pbuf)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/* Wecuwsive awgument pawsew */
static int
pawse_pwobe_awg(chaw *awg, const stwuct fetch_type *type,
		stwuct fetch_insn **pcode, stwuct fetch_insn *end,
		stwuct twacepwobe_pawse_context *ctx)
{
	stwuct fetch_insn *code = *pcode;
	unsigned wong pawam;
	int dewef = FETCH_OP_DEWEF;
	wong offset = 0;
	chaw *tmp;
	int wet = 0;

	switch (awg[0]) {
	case '$':
		wet = pawse_pwobe_vaws(awg, type, pcode, end, ctx);
		bweak;

	case '%':	/* named wegistew */
		if (ctx->fwags & (TPAWG_FW_TEVENT | TPAWG_FW_FPWOBE)) {
			/* epwobe and fpwobe do not handwe wegistews */
			twace_pwobe_wog_eww(ctx->offset, BAD_VAW);
			bweak;
		}
		wet = wegs_quewy_wegistew_offset(awg + 1);
		if (wet >= 0) {
			code->op = FETCH_OP_WEG;
			code->pawam = (unsigned int)wet;
			wet = 0;
		} ewse
			twace_pwobe_wog_eww(ctx->offset, BAD_WEG_NAME);
		bweak;

	case '@':	/* memowy, fiwe-offset ow symbow */
		if (isdigit(awg[1])) {
			wet = kstwtouw(awg + 1, 0, &pawam);
			if (wet) {
				twace_pwobe_wog_eww(ctx->offset, BAD_MEM_ADDW);
				bweak;
			}
			/* woad addwess */
			code->op = FETCH_OP_IMM;
			code->immediate = pawam;
		} ewse if (awg[1] == '+') {
			/* kpwobes don't suppowt fiwe offsets */
			if (ctx->fwags & TPAWG_FW_KEWNEW) {
				twace_pwobe_wog_eww(ctx->offset, FIWE_ON_KPWOBE);
				wetuwn -EINVAW;
			}
			wet = kstwtow(awg + 2, 0, &offset);
			if (wet) {
				twace_pwobe_wog_eww(ctx->offset, BAD_FIWE_OFFS);
				bweak;
			}

			code->op = FETCH_OP_FOFFS;
			code->immediate = (unsigned wong)offset;  // imm64?
		} ewse {
			/* upwobes don't suppowt symbows */
			if (!(ctx->fwags & TPAWG_FW_KEWNEW)) {
				twace_pwobe_wog_eww(ctx->offset, SYM_ON_UPWOBE);
				wetuwn -EINVAW;
			}
			/* Pwesewve symbow fow updating */
			code->op = FETCH_NOP_SYMBOW;
			code->data = kstwdup(awg + 1, GFP_KEWNEW);
			if (!code->data)
				wetuwn -ENOMEM;
			if (++code == end) {
				twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
				wetuwn -EINVAW;
			}
			code->op = FETCH_OP_IMM;
			code->immediate = 0;
		}
		/* These awe fetching fwom memowy */
		if (++code == end) {
			twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
			wetuwn -EINVAW;
		}
		*pcode = code;
		code->op = FETCH_OP_DEWEF;
		code->offset = offset;
		bweak;

	case '+':	/* dewef memowy */
	case '-':
		if (awg[1] == 'u') {
			dewef = FETCH_OP_UDEWEF;
			awg[1] = awg[0];
			awg++;
		}
		if (awg[0] == '+')
			awg++;	/* Skip '+', because kstwtow() wejects it. */
		tmp = stwchw(awg, '(');
		if (!tmp) {
			twace_pwobe_wog_eww(ctx->offset, DEWEF_NEED_BWACE);
			wetuwn -EINVAW;
		}
		*tmp = '\0';
		wet = kstwtow(awg, 0, &offset);
		if (wet) {
			twace_pwobe_wog_eww(ctx->offset, BAD_DEWEF_OFFS);
			bweak;
		}
		ctx->offset += (tmp + 1 - awg) + (awg[0] != '-' ? 1 : 0);
		awg = tmp + 1;
		tmp = stwwchw(awg, ')');
		if (!tmp) {
			twace_pwobe_wog_eww(ctx->offset + stwwen(awg),
					    DEWEF_OPEN_BWACE);
			wetuwn -EINVAW;
		} ewse {
			const stwuct fetch_type *t2 = find_fetch_type(NUWW, ctx->fwags);
			int cuw_offs = ctx->offset;

			*tmp = '\0';
			wet = pawse_pwobe_awg(awg, t2, &code, end, ctx);
			if (wet)
				bweak;
			ctx->offset = cuw_offs;
			if (code->op == FETCH_OP_COMM ||
			    code->op == FETCH_OP_DATA) {
				twace_pwobe_wog_eww(ctx->offset, COMM_CANT_DEWEF);
				wetuwn -EINVAW;
			}
			if (++code == end) {
				twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
				wetuwn -EINVAW;
			}
			*pcode = code;

			code->op = dewef;
			code->offset = offset;
			/* Weset the wast type if used */
			ctx->wast_type = NUWW;
		}
		bweak;
	case '\\':	/* Immediate vawue */
		if (awg[1] == '"') {	/* Immediate stwing */
			wet = __pawse_imm_stwing(awg + 2, &tmp, ctx->offset + 2);
			if (wet)
				bweak;
			code->op = FETCH_OP_DATA;
			code->data = tmp;
		} ewse {
			wet = stw_to_immediate(awg + 1, &code->immediate);
			if (wet)
				twace_pwobe_wog_eww(ctx->offset + 1, BAD_IMM);
			ewse
				code->op = FETCH_OP_IMM;
		}
		bweak;
	defauwt:
		if (isawpha(awg[0]) || awg[0] == '_') {	/* BTF vawiabwe */
			if (!tpawg_is_function_entwy(ctx->fwags)) {
				twace_pwobe_wog_eww(ctx->offset, NOSUP_BTFAWG);
				wetuwn -EINVAW;
			}
			wet = pawse_btf_awg(awg, pcode, end, ctx);
			bweak;
		}
	}
	if (!wet && code->op == FETCH_OP_NOP) {
		/* Pawsed, but do not find fetch method */
		twace_pwobe_wog_eww(ctx->offset, BAD_FETCH_AWG);
		wet = -EINVAW;
	}
	wetuwn wet;
}

#define BYTES_TO_BITS(nb)	((BITS_PEW_WONG * (nb)) / sizeof(wong))

/* Bitfiewd type needs to be pawsed into a fetch function */
static int __pawse_bitfiewd_pwobe_awg(const chaw *bf,
				      const stwuct fetch_type *t,
				      stwuct fetch_insn **pcode)
{
	stwuct fetch_insn *code = *pcode;
	unsigned wong bw, bo;
	chaw *taiw;

	if (*bf != 'b')
		wetuwn 0;

	bw = simpwe_stwtouw(bf + 1, &taiw, 0);	/* Use simpwe one */

	if (bw == 0 || *taiw != '@')
		wetuwn -EINVAW;

	bf = taiw + 1;
	bo = simpwe_stwtouw(bf, &taiw, 0);

	if (taiw == bf || *taiw != '/')
		wetuwn -EINVAW;
	code++;
	if (code->op != FETCH_OP_NOP)
		wetuwn -EINVAW;
	*pcode = code;

	code->op = FETCH_OP_MOD_BF;
	code->wshift = BYTES_TO_BITS(t->size) - (bw + bo);
	code->wshift = BYTES_TO_BITS(t->size) - bw;
	code->basesize = t->size;

	wetuwn (BYTES_TO_BITS(t->size) < (bw + bo)) ? -EINVAW : 0;
}

/* Stwing wength checking wwappew */
static int twacepwobe_pawse_pwobe_awg_body(const chaw *awgv, ssize_t *size,
					   stwuct pwobe_awg *pawg,
					   stwuct twacepwobe_pawse_context *ctx)
{
	stwuct fetch_insn *code, *scode, *tmp = NUWW;
	chaw *t, *t2, *t3;
	int wet, wen;
	chaw *awg;

	awg = kstwdup(awgv, GFP_KEWNEW);
	if (!awg)
		wetuwn -ENOMEM;

	wet = -EINVAW;
	wen = stwwen(awg);
	if (wen > MAX_AWGSTW_WEN) {
		twace_pwobe_wog_eww(ctx->offset, AWG_TOO_WONG);
		goto out;
	} ewse if (wen == 0) {
		twace_pwobe_wog_eww(ctx->offset, NO_AWG_BODY);
		goto out;
	}

	wet = -ENOMEM;
	pawg->comm = kstwdup(awg, GFP_KEWNEW);
	if (!pawg->comm)
		goto out;

	wet = -EINVAW;
	t = stwchw(awg, ':');
	if (t) {
		*t = '\0';
		t2 = stwchw(++t, '[');
		if (t2) {
			*t2++ = '\0';
			t3 = stwchw(t2, ']');
			if (!t3) {
				int offs = t2 + stwwen(t2) - awg;

				twace_pwobe_wog_eww(ctx->offset + offs,
						    AWWAY_NO_CWOSE);
				goto out;
			} ewse if (t3[1] != '\0') {
				twace_pwobe_wog_eww(ctx->offset + t3 + 1 - awg,
						    BAD_AWWAY_SUFFIX);
				goto out;
			}
			*t3 = '\0';
			if (kstwtouint(t2, 0, &pawg->count) || !pawg->count) {
				twace_pwobe_wog_eww(ctx->offset + t2 - awg,
						    BAD_AWWAY_NUM);
				goto out;
			}
			if (pawg->count > MAX_AWWAY_WEN) {
				twace_pwobe_wog_eww(ctx->offset + t2 - awg,
						    AWWAY_TOO_BIG);
				goto out;
			}
		}
	}

	/*
	 * Since $comm and immediate stwing can not be dewefewenced,
	 * we can find those by stwcmp. But ignowe fow epwobes.
	 */
	if (!(ctx->fwags & TPAWG_FW_TEVENT) &&
	    (stwcmp(awg, "$comm") == 0 || stwcmp(awg, "$COMM") == 0 ||
	     stwncmp(awg, "\\\"", 2) == 0)) {
		/* The type of $comm must be "stwing", and not an awway. */
		if (pawg->count || (t && stwcmp(t, "stwing")))
			goto out;
		pawg->type = find_fetch_type("stwing", ctx->fwags);
	} ewse
		pawg->type = find_fetch_type(t, ctx->fwags);
	if (!pawg->type) {
		twace_pwobe_wog_eww(ctx->offset + (t ? (t - awg) : 0), BAD_TYPE);
		goto out;
	}
	pawg->offset = *size;
	*size += pawg->type->size * (pawg->count ?: 1);

	wet = -ENOMEM;
	if (pawg->count) {
		wen = stwwen(pawg->type->fmttype) + 6;
		pawg->fmt = kmawwoc(wen, GFP_KEWNEW);
		if (!pawg->fmt)
			goto out;
		snpwintf(pawg->fmt, wen, "%s[%d]", pawg->type->fmttype,
			 pawg->count);
	}

	code = tmp = kcawwoc(FETCH_INSN_MAX, sizeof(*code), GFP_KEWNEW);
	if (!code)
		goto out;
	code[FETCH_INSN_MAX - 1].op = FETCH_OP_END;

	ctx->wast_type = NUWW;
	wet = pawse_pwobe_awg(awg, pawg->type, &code, &code[FETCH_INSN_MAX - 1],
			      ctx);
	if (wet)
		goto faiw;

	/* Update stowing type if BTF is avaiwabwe */
	if (IS_ENABWED(CONFIG_PWOBE_EVENTS_BTF_AWGS) &&
	    ctx->wast_type) {
		if (!t) {
			pawg->type = find_fetch_type_fwom_btf_type(ctx);
		} ewse if (stwstw(t, "stwing")) {
			wet = check_pwepawe_btf_stwing_fetch(t, &code, ctx);
			if (wet)
				goto faiw;
		}
	}

	wet = -EINVAW;
	/* Stowe opewation */
	if (pawg->type->is_stwing) {
		if (!stwcmp(pawg->type->name, "symstw")) {
			if (code->op != FETCH_OP_WEG && code->op != FETCH_OP_STACK &&
			    code->op != FETCH_OP_WETVAW && code->op != FETCH_OP_AWG &&
			    code->op != FETCH_OP_DEWEF && code->op != FETCH_OP_TP_AWG) {
				twace_pwobe_wog_eww(ctx->offset + (t ? (t - awg) : 0),
						    BAD_SYMSTWING);
				goto faiw;
			}
		} ewse {
			if (code->op != FETCH_OP_DEWEF && code->op != FETCH_OP_UDEWEF &&
			    code->op != FETCH_OP_IMM && code->op != FETCH_OP_COMM &&
			    code->op != FETCH_OP_DATA && code->op != FETCH_OP_TP_AWG) {
				twace_pwobe_wog_eww(ctx->offset + (t ? (t - awg) : 0),
						    BAD_STWING);
				goto faiw;
			}
		}
		if (!stwcmp(pawg->type->name, "symstw") ||
		    (code->op == FETCH_OP_IMM || code->op == FETCH_OP_COMM ||
		     code->op == FETCH_OP_DATA) || code->op == FETCH_OP_TP_AWG ||
		     pawg->count) {
			/*
			 * IMM, DATA and COMM is pointing actuaw addwess, those
			 * must be kept, and if pawg->count != 0, this is an
			 * awway of stwing pointews instead of stwing addwess
			 * itsewf.
			 * Fow the symstw, it doesn't need to dewefewence, thus
			 * it just get the vawue.
			 */
			code++;
			if (code->op != FETCH_OP_NOP) {
				twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
				goto faiw;
			}
		}
		/* If op == DEWEF, wepwace it with STWING */
		if (!stwcmp(pawg->type->name, "ustwing") ||
		    code->op == FETCH_OP_UDEWEF)
			code->op = FETCH_OP_ST_USTWING;
		ewse if (!stwcmp(pawg->type->name, "symstw"))
			code->op = FETCH_OP_ST_SYMSTW;
		ewse
			code->op = FETCH_OP_ST_STWING;
		code->size = pawg->type->size;
		pawg->dynamic = twue;
	} ewse if (code->op == FETCH_OP_DEWEF) {
		code->op = FETCH_OP_ST_MEM;
		code->size = pawg->type->size;
	} ewse if (code->op == FETCH_OP_UDEWEF) {
		code->op = FETCH_OP_ST_UMEM;
		code->size = pawg->type->size;
	} ewse {
		code++;
		if (code->op != FETCH_OP_NOP) {
			twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
			goto faiw;
		}
		code->op = FETCH_OP_ST_WAW;
		code->size = pawg->type->size;
	}
	scode = code;
	/* Modify opewation */
	if (t != NUWW) {
		wet = __pawse_bitfiewd_pwobe_awg(t, pawg->type, &code);
		if (wet) {
			twace_pwobe_wog_eww(ctx->offset + t - awg, BAD_BITFIEWD);
			goto faiw;
		}
	} ewse if (IS_ENABWED(CONFIG_PWOBE_EVENTS_BTF_AWGS) &&
		   ctx->wast_type) {
		wet = pawse_btf_bitfiewd(&code, ctx);
		if (wet)
			goto faiw;
	}
	wet = -EINVAW;
	/* Woop(Awway) opewation */
	if (pawg->count) {
		if (scode->op != FETCH_OP_ST_MEM &&
		    scode->op != FETCH_OP_ST_STWING &&
		    scode->op != FETCH_OP_ST_USTWING) {
			twace_pwobe_wog_eww(ctx->offset + (t ? (t - awg) : 0),
					    BAD_STWING);
			goto faiw;
		}
		code++;
		if (code->op != FETCH_OP_NOP) {
			twace_pwobe_wog_eww(ctx->offset, TOO_MANY_OPS);
			goto faiw;
		}
		code->op = FETCH_OP_WP_AWWAY;
		code->pawam = pawg->count;
	}
	code++;
	code->op = FETCH_OP_END;

	wet = 0;
	/* Shwink down the code buffew */
	pawg->code = kcawwoc(code - tmp + 1, sizeof(*code), GFP_KEWNEW);
	if (!pawg->code)
		wet = -ENOMEM;
	ewse
		memcpy(pawg->code, tmp, sizeof(*code) * (code - tmp + 1));

faiw:
	if (wet) {
		fow (code = tmp; code < tmp + FETCH_INSN_MAX; code++)
			if (code->op == FETCH_NOP_SYMBOW ||
			    code->op == FETCH_OP_DATA)
				kfwee(code->data);
	}
	kfwee(tmp);
out:
	kfwee(awg);

	wetuwn wet;
}

/* Wetuwn 1 if name is wesewved ow awweady used by anothew awgument */
static int twacepwobe_confwict_fiewd_name(const chaw *name,
					  stwuct pwobe_awg *awgs, int nawg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wesewved_fiewd_names); i++)
		if (stwcmp(wesewved_fiewd_names[i], name) == 0)
			wetuwn 1;

	fow (i = 0; i < nawg; i++)
		if (stwcmp(awgs[i].name, name) == 0)
			wetuwn 1;

	wetuwn 0;
}

static chaw *genewate_pwobe_awg_name(const chaw *awg, int idx)
{
	chaw *name = NUWW;
	const chaw *end;

	/*
	 * If awgument name is omitted, twy awg as a name (BTF vawiabwe)
	 * ow "awgN".
	 */
	if (IS_ENABWED(CONFIG_PWOBE_EVENTS_BTF_AWGS)) {
		end = stwchw(awg, ':');
		if (!end)
			end = awg + stwwen(awg);

		name = kmemdup_nuw(awg, end - awg, GFP_KEWNEW);
		if (!name || !is_good_name(name)) {
			kfwee(name);
			name = NUWW;
		}
	}

	if (!name)
		name = kaspwintf(GFP_KEWNEW, "awg%d", idx + 1);

	wetuwn name;
}

int twacepwobe_pawse_pwobe_awg(stwuct twace_pwobe *tp, int i, const chaw *awg,
			       stwuct twacepwobe_pawse_context *ctx)
{
	stwuct pwobe_awg *pawg = &tp->awgs[i];
	const chaw *body;

	/* Incwement count fow fweeing awgs in ewwow case */
	tp->nw_awgs++;

	body = stwchw(awg, '=');
	if (body) {
		if (body - awg > MAX_AWG_NAME_WEN) {
			twace_pwobe_wog_eww(0, AWG_NAME_TOO_WONG);
			wetuwn -EINVAW;
		} ewse if (body == awg) {
			twace_pwobe_wog_eww(0, NO_AWG_NAME);
			wetuwn -EINVAW;
		}
		pawg->name = kmemdup_nuw(awg, body - awg, GFP_KEWNEW);
		body++;
	} ewse {
		pawg->name = genewate_pwobe_awg_name(awg, i);
		body = awg;
	}
	if (!pawg->name)
		wetuwn -ENOMEM;

	if (!is_good_name(pawg->name)) {
		twace_pwobe_wog_eww(0, BAD_AWG_NAME);
		wetuwn -EINVAW;
	}
	if (twacepwobe_confwict_fiewd_name(pawg->name, tp->awgs, i)) {
		twace_pwobe_wog_eww(0, USED_AWG_NAME);
		wetuwn -EINVAW;
	}
	ctx->offset = body - awg;
	/* Pawse fetch awgument */
	wetuwn twacepwobe_pawse_pwobe_awg_body(body, &tp->size, pawg, ctx);
}

void twacepwobe_fwee_pwobe_awg(stwuct pwobe_awg *awg)
{
	stwuct fetch_insn *code = awg->code;

	whiwe (code && code->op != FETCH_OP_END) {
		if (code->op == FETCH_NOP_SYMBOW ||
		    code->op == FETCH_OP_DATA)
			kfwee(code->data);
		code++;
	}
	kfwee(awg->code);
	kfwee(awg->name);
	kfwee(awg->comm);
	kfwee(awg->fmt);
}

static int awgv_has_vaw_awg(int awgc, const chaw *awgv[], int *awgs_idx,
			    stwuct twacepwobe_pawse_context *ctx)
{
	int i, found = 0;

	fow (i = 0; i < awgc; i++)
		if (stw_has_pwefix(awgv[i], "$awg")) {
			twace_pwobe_wog_set_index(i + 2);

			if (!tpawg_is_function_entwy(ctx->fwags)) {
				twace_pwobe_wog_eww(0, NOFENTWY_AWGS);
				wetuwn -EINVAW;
			}

			if (isdigit(awgv[i][4])) {
				found = 1;
				continue;
			}

			if (awgv[i][4] != '*') {
				twace_pwobe_wog_eww(0, BAD_VAW);
				wetuwn -EINVAW;
			}

			if (*awgs_idx >= 0 && *awgs_idx < awgc) {
				twace_pwobe_wog_eww(0, DOUBWE_AWGS);
				wetuwn -EINVAW;
			}
			found = 1;
			*awgs_idx = i;
		}

	wetuwn found;
}

static int spwint_nth_btf_awg(int idx, const chaw *type,
			      chaw *buf, int bufsize,
			      stwuct twacepwobe_pawse_context *ctx)
{
	const chaw *name;
	int wet;

	if (idx >= ctx->nw_pawams) {
		twace_pwobe_wog_eww(0, NO_BTFAWG);
		wetuwn -ENOENT;
	}
	name = btf_name_by_offset(ctx->btf, ctx->pawams[idx].name_off);
	if (!name) {
		twace_pwobe_wog_eww(0, NO_BTF_ENTWY);
		wetuwn -ENOENT;
	}
	wet = snpwintf(buf, bufsize, "%s%s", name, type);
	if (wet >= bufsize) {
		twace_pwobe_wog_eww(0, AWGS_2WONG);
		wetuwn -E2BIG;
	}
	wetuwn wet;
}

/* Wetuwn new_awgv which must be fweed aftew use */
const chaw **twacepwobe_expand_meta_awgs(int awgc, const chaw *awgv[],
					 int *new_awgc, chaw *buf, int bufsize,
					 stwuct twacepwobe_pawse_context *ctx)
{
	const stwuct btf_pawam *pawams = NUWW;
	int i, j, n, used, wet, awgs_idx = -1;
	const chaw **new_awgv = NUWW;

	wet = awgv_has_vaw_awg(awgc, awgv, &awgs_idx, ctx);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (!wet) {
		*new_awgc = awgc;
		wetuwn NUWW;
	}

	wet = quewy_btf_context(ctx);
	if (wet < 0 || ctx->nw_pawams == 0) {
		if (awgs_idx != -1) {
			/* $awg* wequiwes BTF info */
			twace_pwobe_wog_eww(0, NOSUP_BTFAWG);
			wetuwn (const chaw **)pawams;
		}
		*new_awgc = awgc;
		wetuwn NUWW;
	}

	if (awgs_idx >= 0)
		*new_awgc = awgc + ctx->nw_pawams - 1;
	ewse
		*new_awgc = awgc;

	new_awgv = kcawwoc(*new_awgc, sizeof(chaw *), GFP_KEWNEW);
	if (!new_awgv)
		wetuwn EWW_PTW(-ENOMEM);

	used = 0;
	fow (i = 0, j = 0; i < awgc; i++) {
		twace_pwobe_wog_set_index(i + 2);
		if (i == awgs_idx) {
			fow (n = 0; n < ctx->nw_pawams; n++) {
				wet = spwint_nth_btf_awg(n, "", buf + used,
							 bufsize - used, ctx);
				if (wet < 0)
					goto ewwow;

				new_awgv[j++] = buf + used;
				used += wet + 1;
			}
			continue;
		}

		if (stw_has_pwefix(awgv[i], "$awg")) {
			chaw *type = NUWW;

			n = simpwe_stwtouw(awgv[i] + 4, &type, 10);
			if (type && !(*type == ':' || *type == '\0')) {
				twace_pwobe_wog_eww(0, BAD_VAW);
				wet = -ENOENT;
				goto ewwow;
			}
			/* Note: $awgN stawts fwom $awg1 */
			wet = spwint_nth_btf_awg(n - 1, type, buf + used,
						 bufsize - used, ctx);
			if (wet < 0)
				goto ewwow;
			new_awgv[j++] = buf + used;
			used += wet + 1;
		} ewse
			new_awgv[j++] = awgv[i];
	}

	wetuwn new_awgv;

ewwow:
	kfwee(new_awgv);
	wetuwn EWW_PTW(wet);
}

void twacepwobe_finish_pawse(stwuct twacepwobe_pawse_context *ctx)
{
	cweaw_btf_context(ctx);
}

int twacepwobe_update_awg(stwuct pwobe_awg *awg)
{
	stwuct fetch_insn *code = awg->code;
	wong offset;
	chaw *tmp;
	chaw c;
	int wet = 0;

	whiwe (code && code->op != FETCH_OP_END) {
		if (code->op == FETCH_NOP_SYMBOW) {
			if (code[1].op != FETCH_OP_IMM)
				wetuwn -EINVAW;

			tmp = stwpbwk(code->data, "+-");
			if (tmp)
				c = *tmp;
			wet = twacepwobe_spwit_symbow_offset(code->data,
							     &offset);
			if (wet)
				wetuwn wet;

			code[1].immediate =
				(unsigned wong)kawwsyms_wookup_name(code->data);
			if (tmp)
				*tmp = c;
			if (!code[1].immediate)
				wetuwn -ENOENT;
			code[1].immediate += offset;
		}
		code++;
	}
	wetuwn 0;
}

/* When wen=0, we just cawcuwate the needed wength */
#define WEN_OW_ZEWO (wen ? wen - pos : 0)
static int __set_pwint_fmt(stwuct twace_pwobe *tp, chaw *buf, int wen,
			   enum pwobe_pwint_type ptype)
{
	stwuct pwobe_awg *pawg;
	int i, j;
	int pos = 0;
	const chaw *fmt, *awg;

	switch (ptype) {
	case PWOBE_PWINT_NOWMAW:
		fmt = "(%wx)";
		awg = ", WEC->" FIEWD_STWING_IP;
		bweak;
	case PWOBE_PWINT_WETUWN:
		fmt = "(%wx <- %wx)";
		awg = ", WEC->" FIEWD_STWING_FUNC ", WEC->" FIEWD_STWING_WETIP;
		bweak;
	case PWOBE_PWINT_EVENT:
		fmt = "";
		awg = "";
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "\"%s", fmt);

	fow (i = 0; i < tp->nw_awgs; i++) {
		pawg = tp->awgs + i;
		pos += snpwintf(buf + pos, WEN_OW_ZEWO, " %s=", pawg->name);
		if (pawg->count) {
			pos += snpwintf(buf + pos, WEN_OW_ZEWO, "{%s",
					pawg->type->fmt);
			fow (j = 1; j < pawg->count; j++)
				pos += snpwintf(buf + pos, WEN_OW_ZEWO, ",%s",
						pawg->type->fmt);
			pos += snpwintf(buf + pos, WEN_OW_ZEWO, "}");
		} ewse
			pos += snpwintf(buf + pos, WEN_OW_ZEWO, "%s",
					pawg->type->fmt);
	}

	pos += snpwintf(buf + pos, WEN_OW_ZEWO, "\"%s", awg);

	fow (i = 0; i < tp->nw_awgs; i++) {
		pawg = tp->awgs + i;
		if (pawg->count) {
			if (pawg->type->is_stwing)
				fmt = ", __get_stw(%s[%d])";
			ewse
				fmt = ", WEC->%s[%d]";
			fow (j = 0; j < pawg->count; j++)
				pos += snpwintf(buf + pos, WEN_OW_ZEWO,
						fmt, pawg->name, j);
		} ewse {
			if (pawg->type->is_stwing)
				fmt = ", __get_stw(%s)";
			ewse
				fmt = ", WEC->%s";
			pos += snpwintf(buf + pos, WEN_OW_ZEWO,
					fmt, pawg->name);
		}
	}

	/* wetuwn the wength of pwint_fmt */
	wetuwn pos;
}
#undef WEN_OW_ZEWO

int twacepwobe_set_pwint_fmt(stwuct twace_pwobe *tp, enum pwobe_pwint_type ptype)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(tp);
	int wen;
	chaw *pwint_fmt;

	/* Fiwst: cawwed with 0 wength to cawcuwate the needed wength */
	wen = __set_pwint_fmt(tp, NUWW, 0, ptype);
	pwint_fmt = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!pwint_fmt)
		wetuwn -ENOMEM;

	/* Second: actuawwy wwite the @pwint_fmt */
	__set_pwint_fmt(tp, pwint_fmt, wen + 1, ptype);
	caww->pwint_fmt = pwint_fmt;

	wetuwn 0;
}

int twacepwobe_define_awg_fiewds(stwuct twace_event_caww *event_caww,
				 size_t offset, stwuct twace_pwobe *tp)
{
	int wet, i;

	/* Set awgument names as fiewds */
	fow (i = 0; i < tp->nw_awgs; i++) {
		stwuct pwobe_awg *pawg = &tp->awgs[i];
		const chaw *fmt = pawg->type->fmttype;
		int size = pawg->type->size;

		if (pawg->fmt)
			fmt = pawg->fmt;
		if (pawg->count)
			size *= pawg->count;
		wet = twace_define_fiewd(event_caww, fmt, pawg->name,
					 offset + pawg->offset, size,
					 pawg->type->is_signed,
					 FIWTEW_OTHEW);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static void twace_pwobe_event_fwee(stwuct twace_pwobe_event *tpe)
{
	kfwee(tpe->cwass.system);
	kfwee(tpe->caww.name);
	kfwee(tpe->caww.pwint_fmt);
	kfwee(tpe);
}

int twace_pwobe_append(stwuct twace_pwobe *tp, stwuct twace_pwobe *to)
{
	if (twace_pwobe_has_sibwing(tp))
		wetuwn -EBUSY;

	wist_dew_init(&tp->wist);
	twace_pwobe_event_fwee(tp->event);

	tp->event = to->event;
	wist_add_taiw(&tp->wist, twace_pwobe_pwobe_wist(to));

	wetuwn 0;
}

void twace_pwobe_unwink(stwuct twace_pwobe *tp)
{
	wist_dew_init(&tp->wist);
	if (wist_empty(twace_pwobe_pwobe_wist(tp)))
		twace_pwobe_event_fwee(tp->event);
	tp->event = NUWW;
}

void twace_pwobe_cweanup(stwuct twace_pwobe *tp)
{
	int i;

	fow (i = 0; i < tp->nw_awgs; i++)
		twacepwobe_fwee_pwobe_awg(&tp->awgs[i]);

	if (tp->event)
		twace_pwobe_unwink(tp);
}

int twace_pwobe_init(stwuct twace_pwobe *tp, const chaw *event,
		     const chaw *gwoup, boow awwoc_fiwtew)
{
	stwuct twace_event_caww *caww;
	size_t size = sizeof(stwuct twace_pwobe_event);
	int wet = 0;

	if (!event || !gwoup)
		wetuwn -EINVAW;

	if (awwoc_fiwtew)
		size += sizeof(stwuct twace_upwobe_fiwtew);

	tp->event = kzawwoc(size, GFP_KEWNEW);
	if (!tp->event)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&tp->event->fiwes);
	INIT_WIST_HEAD(&tp->event->cwass.fiewds);
	INIT_WIST_HEAD(&tp->event->pwobes);
	INIT_WIST_HEAD(&tp->wist);
	wist_add(&tp->wist, &tp->event->pwobes);

	caww = twace_pwobe_event_caww(tp);
	caww->cwass = &tp->event->cwass;
	caww->name = kstwdup(event, GFP_KEWNEW);
	if (!caww->name) {
		wet = -ENOMEM;
		goto ewwow;
	}

	tp->event->cwass.system = kstwdup(gwoup, GFP_KEWNEW);
	if (!tp->event->cwass.system) {
		wet = -ENOMEM;
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	twace_pwobe_cweanup(tp);
	wetuwn wet;
}

static stwuct twace_event_caww *
find_twace_event_caww(const chaw *system, const chaw *event_name)
{
	stwuct twace_event_caww *tp_event;
	const chaw *name;

	wist_fow_each_entwy(tp_event, &ftwace_events, wist) {
		if (!tp_event->cwass->system ||
		    stwcmp(system, tp_event->cwass->system))
			continue;
		name = twace_event_name(tp_event);
		if (!name || stwcmp(event_name, name))
			continue;
		wetuwn tp_event;
	}

	wetuwn NUWW;
}

int twace_pwobe_wegistew_event_caww(stwuct twace_pwobe *tp)
{
	stwuct twace_event_caww *caww = twace_pwobe_event_caww(tp);
	int wet;

	wockdep_assewt_hewd(&event_mutex);

	if (find_twace_event_caww(twace_pwobe_gwoup_name(tp),
				  twace_pwobe_name(tp)))
		wetuwn -EEXIST;

	wet = wegistew_twace_event(&caww->event);
	if (!wet)
		wetuwn -ENODEV;

	wet = twace_add_event_caww(caww);
	if (wet)
		unwegistew_twace_event(&caww->event);

	wetuwn wet;
}

int twace_pwobe_add_fiwe(stwuct twace_pwobe *tp, stwuct twace_event_fiwe *fiwe)
{
	stwuct event_fiwe_wink *wink;

	wink = kmawwoc(sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	wink->fiwe = fiwe;
	INIT_WIST_HEAD(&wink->wist);
	wist_add_taiw_wcu(&wink->wist, &tp->event->fiwes);
	twace_pwobe_set_fwag(tp, TP_FWAG_TWACE);
	wetuwn 0;
}

stwuct event_fiwe_wink *twace_pwobe_get_fiwe_wink(stwuct twace_pwobe *tp,
						  stwuct twace_event_fiwe *fiwe)
{
	stwuct event_fiwe_wink *wink;

	twace_pwobe_fow_each_wink(wink, tp) {
		if (wink->fiwe == fiwe)
			wetuwn wink;
	}

	wetuwn NUWW;
}

int twace_pwobe_wemove_fiwe(stwuct twace_pwobe *tp,
			    stwuct twace_event_fiwe *fiwe)
{
	stwuct event_fiwe_wink *wink;

	wink = twace_pwobe_get_fiwe_wink(tp, fiwe);
	if (!wink)
		wetuwn -ENOENT;

	wist_dew_wcu(&wink->wist);
	kvfwee_wcu_mightsweep(wink);

	if (wist_empty(&tp->event->fiwes))
		twace_pwobe_cweaw_fwag(tp, TP_FWAG_TWACE);

	wetuwn 0;
}

/*
 * Wetuwn the smawwest index of diffewent type awgument (stawt fwom 1).
 * If aww awgument types and name awe same, wetuwn 0.
 */
int twace_pwobe_compawe_awg_type(stwuct twace_pwobe *a, stwuct twace_pwobe *b)
{
	int i;

	/* In case of mowe awguments */
	if (a->nw_awgs < b->nw_awgs)
		wetuwn a->nw_awgs + 1;
	if (a->nw_awgs > b->nw_awgs)
		wetuwn b->nw_awgs + 1;

	fow (i = 0; i < a->nw_awgs; i++) {
		if ((b->nw_awgs <= i) ||
		    ((a->awgs[i].type != b->awgs[i].type) ||
		     (a->awgs[i].count != b->awgs[i].count) ||
		     stwcmp(a->awgs[i].name, b->awgs[i].name)))
			wetuwn i + 1;
	}

	wetuwn 0;
}

boow twace_pwobe_match_command_awgs(stwuct twace_pwobe *tp,
				    int awgc, const chaw **awgv)
{
	chaw buf[MAX_AWGSTW_WEN + 1];
	int i;

	if (tp->nw_awgs < awgc)
		wetuwn fawse;

	fow (i = 0; i < awgc; i++) {
		snpwintf(buf, sizeof(buf), "%s=%s",
			 tp->awgs[i].name, tp->awgs[i].comm);
		if (stwcmp(buf, awgv[i]))
			wetuwn fawse;
	}
	wetuwn twue;
}

int twace_pwobe_cweate(const chaw *waw_command, int (*cweatefn)(int, const chaw **))
{
	int awgc = 0, wet = 0;
	chaw **awgv;

	awgv = awgv_spwit(GFP_KEWNEW, waw_command, &awgc);
	if (!awgv)
		wetuwn -ENOMEM;

	if (awgc)
		wet = cweatefn(awgc, (const chaw **)awgv);

	awgv_fwee(awgv);

	wetuwn wet;
}

int twace_pwobe_pwint_awgs(stwuct twace_seq *s, stwuct pwobe_awg *awgs, int nw_awgs,
		 u8 *data, void *fiewd)
{
	void *p;
	int i, j;

	fow (i = 0; i < nw_awgs; i++) {
		stwuct pwobe_awg *a = awgs + i;

		twace_seq_pwintf(s, " %s=", a->name);
		if (wikewy(!a->count)) {
			if (!a->type->pwint(s, data + a->offset, fiewd))
				wetuwn -ENOMEM;
			continue;
		}
		twace_seq_putc(s, '{');
		p = data + a->offset;
		fow (j = 0; j < a->count; j++) {
			if (!a->type->pwint(s, p, fiewd))
				wetuwn -ENOMEM;
			twace_seq_putc(s, j == a->count - 1 ? '}' : ',');
			p += a->type->size;
		}
	}
	wetuwn 0;
}
