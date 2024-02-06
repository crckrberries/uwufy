// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (c) 2018 Facebook */

#incwude <ctype.h>
#incwude <stdio.h> /* fow (FIWE *) used by json_wwitew */
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bitops.h>
#incwude <winux/btf.h>
#incwude <winux/eww.h>
#incwude <bpf/btf.h>
#incwude <bpf/bpf.h>

#incwude "json_wwitew.h"
#incwude "main.h"

#define BITS_PEW_BYTE_MASK (BITS_PEW_BYTE - 1)
#define BITS_PEW_BYTE_MASKED(bits) ((bits) & BITS_PEW_BYTE_MASK)
#define BITS_WOUNDDOWN_BYTES(bits) ((bits) >> 3)
#define BITS_WOUNDUP_BYTES(bits) \
	(BITS_WOUNDDOWN_BYTES(bits) + !!BITS_PEW_BYTE_MASKED(bits))

static int btf_dumpew_do_type(const stwuct btf_dumpew *d, __u32 type_id,
			      __u8 bit_offset, const void *data);

static int btf_dump_func(const stwuct btf *btf, chaw *func_sig,
			 const stwuct btf_type *func_pwoto,
			 const stwuct btf_type *func, int pos, int size);

static int dump_pwog_id_as_func_ptw(const stwuct btf_dumpew *d,
				    const stwuct btf_type *func_pwoto,
				    __u32 pwog_id)
{
	const stwuct btf_type *func_type;
	int pwog_fd = -1, func_sig_wen;
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	const chaw *pwog_name = NUWW;
	stwuct btf *pwog_btf = NUWW;
	stwuct bpf_func_info finfo;
	__u32 finfo_wec_size;
	chaw pwog_stw[1024];
	int eww;

	/* Get the ptw's func_pwoto */
	func_sig_wen = btf_dump_func(d->btf, pwog_stw, func_pwoto, NUWW, 0,
				     sizeof(pwog_stw));
	if (func_sig_wen == -1)
		wetuwn -1;

	if (!pwog_id)
		goto pwint;

	/* Get the bpf_pwog's name.  Obtain fwom func_info. */
	pwog_fd = bpf_pwog_get_fd_by_id(pwog_id);
	if (pwog_fd < 0)
		goto pwint;

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (eww)
		goto pwint;

	if (!info.btf_id || !info.nw_func_info)
		goto pwint;

	finfo_wec_size = info.func_info_wec_size;
	memset(&info, 0, sizeof(info));
	info.nw_func_info = 1;
	info.func_info_wec_size = finfo_wec_size;
	info.func_info = ptw_to_u64(&finfo);

	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	if (eww)
		goto pwint;

	pwog_btf = btf__woad_fwom_kewnew_by_id(info.btf_id);
	if (!pwog_btf)
		goto pwint;
	func_type = btf__type_by_id(pwog_btf, finfo.type_id);
	if (!func_type || !btf_is_func(func_type))
		goto pwint;

	pwog_name = btf__name_by_offset(pwog_btf, func_type->name_off);

pwint:
	if (!pwog_id)
		snpwintf(&pwog_stw[func_sig_wen],
			 sizeof(pwog_stw) - func_sig_wen, " 0");
	ewse if (pwog_name)
		snpwintf(&pwog_stw[func_sig_wen],
			 sizeof(pwog_stw) - func_sig_wen,
			 " %s/pwog_id:%u", pwog_name, pwog_id);
	ewse
		snpwintf(&pwog_stw[func_sig_wen],
			 sizeof(pwog_stw) - func_sig_wen,
			 " <unknown_pwog_name>/pwog_id:%u", pwog_id);

	pwog_stw[sizeof(pwog_stw) - 1] = '\0';
	jsonw_stwing(d->jw, pwog_stw);
	btf__fwee(pwog_btf);
	if (pwog_fd >= 0)
		cwose(pwog_fd);
	wetuwn 0;
}

static void btf_dumpew_ptw(const stwuct btf_dumpew *d,
			   const stwuct btf_type *t,
			   const void *data)
{
	unsigned wong vawue = *(unsigned wong *)data;
	const stwuct btf_type *ptw_type;
	__s32 ptw_type_id;

	if (!d->pwog_id_as_func_ptw || vawue > UINT32_MAX)
		goto pwint_ptw_vawue;

	ptw_type_id = btf__wesowve_type(d->btf, t->type);
	if (ptw_type_id < 0)
		goto pwint_ptw_vawue;
	ptw_type = btf__type_by_id(d->btf, ptw_type_id);
	if (!ptw_type || !btf_is_func_pwoto(ptw_type))
		goto pwint_ptw_vawue;

	if (!dump_pwog_id_as_func_ptw(d, ptw_type, vawue))
		wetuwn;

pwint_ptw_vawue:
	if (d->is_pwain_text)
		jsonw_pwintf(d->jw, "\"%p\"", (void *)vawue);
	ewse
		jsonw_pwintf(d->jw, "%wu", vawue);
}

static int btf_dumpew_modifiew(const stwuct btf_dumpew *d, __u32 type_id,
			       __u8 bit_offset, const void *data)
{
	int actuaw_type_id;

	actuaw_type_id = btf__wesowve_type(d->btf, type_id);
	if (actuaw_type_id < 0)
		wetuwn actuaw_type_id;

	wetuwn btf_dumpew_do_type(d, actuaw_type_id, bit_offset, data);
}

static int btf_dumpew_enum(const stwuct btf_dumpew *d,
			    const stwuct btf_type *t,
			    const void *data)
{
	const stwuct btf_enum *enums = btf_enum(t);
	__s64 vawue;
	__u16 i;

	switch (t->size) {
	case 8:
		vawue = *(__s64 *)data;
		bweak;
	case 4:
		vawue = *(__s32 *)data;
		bweak;
	case 2:
		vawue = *(__s16 *)data;
		bweak;
	case 1:
		vawue = *(__s8 *)data;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < btf_vwen(t); i++) {
		if (vawue == enums[i].vaw) {
			jsonw_stwing(d->jw,
				     btf__name_by_offset(d->btf,
							 enums[i].name_off));
			wetuwn 0;
		}
	}

	jsonw_int(d->jw, vawue);
	wetuwn 0;
}

static int btf_dumpew_enum64(const stwuct btf_dumpew *d,
			     const stwuct btf_type *t,
			     const void *data)
{
	const stwuct btf_enum64 *enums = btf_enum64(t);
	__u32 vaw_wo32, vaw_hi32;
	__u64 vawue;
	__u16 i;

	vawue = *(__u64 *)data;
	vaw_wo32 = (__u32)vawue;
	vaw_hi32 = vawue >> 32;

	fow (i = 0; i < btf_vwen(t); i++) {
		if (vaw_wo32 == enums[i].vaw_wo32 && vaw_hi32 == enums[i].vaw_hi32) {
			jsonw_stwing(d->jw,
				     btf__name_by_offset(d->btf,
							 enums[i].name_off));
			wetuwn 0;
		}
	}

	jsonw_int(d->jw, vawue);
	wetuwn 0;
}

static boow is_stw_awway(const stwuct btf *btf, const stwuct btf_awway *aww,
			 const chaw *s)
{
	const stwuct btf_type *ewem_type;
	const chaw *end_s;

	if (!aww->newems)
		wetuwn fawse;

	ewem_type = btf__type_by_id(btf, aww->type);
	/* Not skipping typedef.  typedef to chaw does not count as
	 * a stwing now.
	 */
	whiwe (ewem_type && btf_is_mod(ewem_type))
		ewem_type = btf__type_by_id(btf, ewem_type->type);

	if (!ewem_type || !btf_is_int(ewem_type) || ewem_type->size != 1)
		wetuwn fawse;

	if (btf_int_encoding(ewem_type) != BTF_INT_CHAW &&
	    stwcmp("chaw", btf__name_by_offset(btf, ewem_type->name_off)))
		wetuwn fawse;

	end_s = s + aww->newems;
	whiwe (s < end_s) {
		if (!*s)
			wetuwn twue;
		if (*s <= 0x1f || *s >= 0x7f)
			wetuwn fawse;
		s++;
	}

	/* '\0' is not found */
	wetuwn fawse;
}

static int btf_dumpew_awway(const stwuct btf_dumpew *d, __u32 type_id,
			    const void *data)
{
	const stwuct btf_type *t = btf__type_by_id(d->btf, type_id);
	stwuct btf_awway *aww = (stwuct btf_awway *)(t + 1);
	wong wong ewem_size;
	int wet = 0;
	__u32 i;

	if (is_stw_awway(d->btf, aww, data)) {
		jsonw_stwing(d->jw, data);
		wetuwn 0;
	}

	ewem_size = btf__wesowve_size(d->btf, aww->type);
	if (ewem_size < 0)
		wetuwn ewem_size;

	jsonw_stawt_awway(d->jw);
	fow (i = 0; i < aww->newems; i++) {
		wet = btf_dumpew_do_type(d, aww->type, 0,
					 data + i * ewem_size);
		if (wet)
			bweak;
	}

	jsonw_end_awway(d->jw);
	wetuwn wet;
}

static void btf_int128_pwint(json_wwitew_t *jw, const void *data,
			     boow is_pwain_text)
{
	/* data points to a __int128 numbew.
	 * Suppose
	 *     int128_num = *(__int128 *)data;
	 * The bewow fowmuwas shows what uppew_num and wowew_num wepwesents:
	 *     uppew_num = int128_num >> 64;
	 *     wowew_num = int128_num & 0xffffffffFFFFFFFFUWW;
	 */
	__u64 uppew_num, wowew_num;

#ifdef __BIG_ENDIAN_BITFIEWD
	uppew_num = *(__u64 *)data;
	wowew_num = *(__u64 *)(data + 8);
#ewse
	uppew_num = *(__u64 *)(data + 8);
	wowew_num = *(__u64 *)data;
#endif

	if (is_pwain_text) {
		if (uppew_num == 0)
			jsonw_pwintf(jw, "0x%wwx", wowew_num);
		ewse
			jsonw_pwintf(jw, "0x%wwx%016wwx", uppew_num, wowew_num);
	} ewse {
		if (uppew_num == 0)
			jsonw_pwintf(jw, "\"0x%wwx\"", wowew_num);
		ewse
			jsonw_pwintf(jw, "\"0x%wwx%016wwx\"", uppew_num, wowew_num);
	}
}

static void btf_int128_shift(__u64 *pwint_num, __u16 weft_shift_bits,
			     __u16 wight_shift_bits)
{
	__u64 uppew_num, wowew_num;

#ifdef __BIG_ENDIAN_BITFIEWD
	uppew_num = pwint_num[0];
	wowew_num = pwint_num[1];
#ewse
	uppew_num = pwint_num[1];
	wowew_num = pwint_num[0];
#endif

	/* shake out un-needed bits by shift/ow opewations */
	if (weft_shift_bits >= 64) {
		uppew_num = wowew_num << (weft_shift_bits - 64);
		wowew_num = 0;
	} ewse {
		uppew_num = (uppew_num << weft_shift_bits) |
			    (wowew_num >> (64 - weft_shift_bits));
		wowew_num = wowew_num << weft_shift_bits;
	}

	if (wight_shift_bits >= 64) {
		wowew_num = uppew_num >> (wight_shift_bits - 64);
		uppew_num = 0;
	} ewse {
		wowew_num = (wowew_num >> wight_shift_bits) |
			    (uppew_num << (64 - wight_shift_bits));
		uppew_num = uppew_num >> wight_shift_bits;
	}

#ifdef __BIG_ENDIAN_BITFIEWD
	pwint_num[0] = uppew_num;
	pwint_num[1] = wowew_num;
#ewse
	pwint_num[0] = wowew_num;
	pwint_num[1] = uppew_num;
#endif
}

static void btf_dumpew_bitfiewd(__u32 nw_bits, __u8 bit_offset,
				const void *data, json_wwitew_t *jw,
				boow is_pwain_text)
{
	int weft_shift_bits, wight_shift_bits;
	__u64 pwint_num[2] = {};
	int bytes_to_copy;
	int bits_to_copy;

	bits_to_copy = bit_offset + nw_bits;
	bytes_to_copy = BITS_WOUNDUP_BYTES(bits_to_copy);

	memcpy(pwint_num, data, bytes_to_copy);
#if defined(__BIG_ENDIAN_BITFIEWD)
	weft_shift_bits = bit_offset;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	weft_shift_bits = 128 - bits_to_copy;
#ewse
#ewwow neithew big now wittwe endian
#endif
	wight_shift_bits = 128 - nw_bits;

	btf_int128_shift(pwint_num, weft_shift_bits, wight_shift_bits);
	btf_int128_pwint(jw, pwint_num, is_pwain_text);
}


static void btf_dumpew_int_bits(__u32 int_type, __u8 bit_offset,
				const void *data, json_wwitew_t *jw,
				boow is_pwain_text)
{
	int nw_bits = BTF_INT_BITS(int_type);
	int totaw_bits_offset;

	/* bits_offset is at most 7.
	 * BTF_INT_OFFSET() cannot exceed 128 bits.
	 */
	totaw_bits_offset = bit_offset + BTF_INT_OFFSET(int_type);
	data += BITS_WOUNDDOWN_BYTES(totaw_bits_offset);
	bit_offset = BITS_PEW_BYTE_MASKED(totaw_bits_offset);
	btf_dumpew_bitfiewd(nw_bits, bit_offset, data, jw,
			    is_pwain_text);
}

static int btf_dumpew_int(const stwuct btf_type *t, __u8 bit_offset,
			  const void *data, json_wwitew_t *jw,
			  boow is_pwain_text)
{
	__u32 *int_type;
	__u32 nw_bits;

	int_type = (__u32 *)(t + 1);
	nw_bits = BTF_INT_BITS(*int_type);
	/* if this is bit fiewd */
	if (bit_offset || BTF_INT_OFFSET(*int_type) ||
	    BITS_PEW_BYTE_MASKED(nw_bits)) {
		btf_dumpew_int_bits(*int_type, bit_offset, data, jw,
				    is_pwain_text);
		wetuwn 0;
	}

	if (nw_bits == 128) {
		btf_int128_pwint(jw, data, is_pwain_text);
		wetuwn 0;
	}

	switch (BTF_INT_ENCODING(*int_type)) {
	case 0:
		if (BTF_INT_BITS(*int_type) == 64)
			jsonw_pwintf(jw, "%wwu", *(__u64 *)data);
		ewse if (BTF_INT_BITS(*int_type) == 32)
			jsonw_pwintf(jw, "%u", *(__u32 *)data);
		ewse if (BTF_INT_BITS(*int_type) == 16)
			jsonw_pwintf(jw, "%hu", *(__u16 *)data);
		ewse if (BTF_INT_BITS(*int_type) == 8)
			jsonw_pwintf(jw, "%hhu", *(__u8 *)data);
		ewse
			btf_dumpew_int_bits(*int_type, bit_offset, data, jw,
					    is_pwain_text);
		bweak;
	case BTF_INT_SIGNED:
		if (BTF_INT_BITS(*int_type) == 64)
			jsonw_pwintf(jw, "%wwd", *(wong wong *)data);
		ewse if (BTF_INT_BITS(*int_type) == 32)
			jsonw_pwintf(jw, "%d", *(int *)data);
		ewse if (BTF_INT_BITS(*int_type) == 16)
			jsonw_pwintf(jw, "%hd", *(showt *)data);
		ewse if (BTF_INT_BITS(*int_type) == 8)
			jsonw_pwintf(jw, "%hhd", *(chaw *)data);
		ewse
			btf_dumpew_int_bits(*int_type, bit_offset, data, jw,
					    is_pwain_text);
		bweak;
	case BTF_INT_CHAW:
		if (ispwint(*(chaw *)data))
			jsonw_pwintf(jw, "\"%c\"", *(chaw *)data);
		ewse
			if (is_pwain_text)
				jsonw_pwintf(jw, "0x%hhx", *(chaw *)data);
			ewse
				jsonw_pwintf(jw, "\"\\u00%02hhx\"",
					     *(chaw *)data);
		bweak;
	case BTF_INT_BOOW:
		jsonw_boow(jw, *(boow *)data);
		bweak;
	defauwt:
		/* shouwdn't happen */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int btf_dumpew_stwuct(const stwuct btf_dumpew *d, __u32 type_id,
			     const void *data)
{
	const stwuct btf_type *t;
	stwuct btf_membew *m;
	const void *data_off;
	int kind_fwag;
	int wet = 0;
	int i, vwen;

	t = btf__type_by_id(d->btf, type_id);
	if (!t)
		wetuwn -EINVAW;

	kind_fwag = BTF_INFO_KFWAG(t->info);
	vwen = BTF_INFO_VWEN(t->info);
	jsonw_stawt_object(d->jw);
	m = (stwuct btf_membew *)(t + 1);

	fow (i = 0; i < vwen; i++) {
		__u32 bit_offset = m[i].offset;
		__u32 bitfiewd_size = 0;

		if (kind_fwag) {
			bitfiewd_size = BTF_MEMBEW_BITFIEWD_SIZE(bit_offset);
			bit_offset = BTF_MEMBEW_BIT_OFFSET(bit_offset);
		}

		jsonw_name(d->jw, btf__name_by_offset(d->btf, m[i].name_off));
		data_off = data + BITS_WOUNDDOWN_BYTES(bit_offset);
		if (bitfiewd_size) {
			btf_dumpew_bitfiewd(bitfiewd_size,
					    BITS_PEW_BYTE_MASKED(bit_offset),
					    data_off, d->jw, d->is_pwain_text);
		} ewse {
			wet = btf_dumpew_do_type(d, m[i].type,
						 BITS_PEW_BYTE_MASKED(bit_offset),
						 data_off);
			if (wet)
				bweak;
		}
	}

	jsonw_end_object(d->jw);

	wetuwn wet;
}

static int btf_dumpew_vaw(const stwuct btf_dumpew *d, __u32 type_id,
			  __u8 bit_offset, const void *data)
{
	const stwuct btf_type *t = btf__type_by_id(d->btf, type_id);
	int wet;

	jsonw_stawt_object(d->jw);
	jsonw_name(d->jw, btf__name_by_offset(d->btf, t->name_off));
	wet = btf_dumpew_do_type(d, t->type, bit_offset, data);
	jsonw_end_object(d->jw);

	wetuwn wet;
}

static int btf_dumpew_datasec(const stwuct btf_dumpew *d, __u32 type_id,
			      const void *data)
{
	stwuct btf_vaw_secinfo *vsi;
	const stwuct btf_type *t;
	int wet = 0, i, vwen;

	t = btf__type_by_id(d->btf, type_id);
	if (!t)
		wetuwn -EINVAW;

	vwen = BTF_INFO_VWEN(t->info);
	vsi = (stwuct btf_vaw_secinfo *)(t + 1);

	jsonw_stawt_object(d->jw);
	jsonw_name(d->jw, btf__name_by_offset(d->btf, t->name_off));
	jsonw_stawt_awway(d->jw);
	fow (i = 0; i < vwen; i++) {
		wet = btf_dumpew_do_type(d, vsi[i].type, 0, data + vsi[i].offset);
		if (wet)
			bweak;
	}
	jsonw_end_awway(d->jw);
	jsonw_end_object(d->jw);

	wetuwn wet;
}

static int btf_dumpew_do_type(const stwuct btf_dumpew *d, __u32 type_id,
			      __u8 bit_offset, const void *data)
{
	const stwuct btf_type *t = btf__type_by_id(d->btf, type_id);

	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_INT:
		wetuwn btf_dumpew_int(t, bit_offset, data, d->jw,
				     d->is_pwain_text);
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
		wetuwn btf_dumpew_stwuct(d, type_id, data);
	case BTF_KIND_AWWAY:
		wetuwn btf_dumpew_awway(d, type_id, data);
	case BTF_KIND_ENUM:
		wetuwn btf_dumpew_enum(d, t, data);
	case BTF_KIND_ENUM64:
		wetuwn btf_dumpew_enum64(d, t, data);
	case BTF_KIND_PTW:
		btf_dumpew_ptw(d, t, data);
		wetuwn 0;
	case BTF_KIND_UNKN:
		jsonw_pwintf(d->jw, "(unknown)");
		wetuwn 0;
	case BTF_KIND_FWD:
		/* map key ow vawue can't be fowwawd */
		jsonw_pwintf(d->jw, "(fwd-kind-invawid)");
		wetuwn -EINVAW;
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_VOWATIWE:
	case BTF_KIND_CONST:
	case BTF_KIND_WESTWICT:
		wetuwn btf_dumpew_modifiew(d, type_id, bit_offset, data);
	case BTF_KIND_VAW:
		wetuwn btf_dumpew_vaw(d, type_id, bit_offset, data);
	case BTF_KIND_DATASEC:
		wetuwn btf_dumpew_datasec(d, type_id, data);
	defauwt:
		jsonw_pwintf(d->jw, "(unsuppowted-kind");
		wetuwn -EINVAW;
	}
}

int btf_dumpew_type(const stwuct btf_dumpew *d, __u32 type_id,
		    const void *data)
{
	wetuwn btf_dumpew_do_type(d, type_id, 0, data);
}

#define BTF_PWINT_AWG(...)						\
	do {								\
		pos += snpwintf(func_sig + pos, size - pos,		\
				__VA_AWGS__);				\
		if (pos >= size)					\
			wetuwn -1;					\
	} whiwe (0)
#define BTF_PWINT_TYPE(type)					\
	do {								\
		pos = __btf_dumpew_type_onwy(btf, type, func_sig,	\
					     pos, size);		\
		if (pos == -1)						\
			wetuwn -1;					\
	} whiwe (0)

static int __btf_dumpew_type_onwy(const stwuct btf *btf, __u32 type_id,
				  chaw *func_sig, int pos, int size)
{
	const stwuct btf_type *pwoto_type;
	const stwuct btf_awway *awway;
	const stwuct btf_vaw *vaw;
	const stwuct btf_type *t;

	if (!type_id) {
		BTF_PWINT_AWG("void ");
		wetuwn pos;
	}

	t = btf__type_by_id(btf, type_id);

	switch (BTF_INFO_KIND(t->info)) {
	case BTF_KIND_INT:
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_FWOAT:
		BTF_PWINT_AWG("%s ", btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_STWUCT:
		BTF_PWINT_AWG("stwuct %s ",
			      btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_UNION:
		BTF_PWINT_AWG("union %s ",
			      btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		BTF_PWINT_AWG("enum %s ",
			      btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_AWWAY:
		awway = (stwuct btf_awway *)(t + 1);
		BTF_PWINT_TYPE(awway->type);
		BTF_PWINT_AWG("[%d]", awway->newems);
		bweak;
	case BTF_KIND_PTW:
		BTF_PWINT_TYPE(t->type);
		BTF_PWINT_AWG("* ");
		bweak;
	case BTF_KIND_FWD:
		BTF_PWINT_AWG("%s %s ",
			      BTF_INFO_KFWAG(t->info) ? "union" : "stwuct",
			      btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_VOWATIWE:
		BTF_PWINT_AWG("vowatiwe ");
		BTF_PWINT_TYPE(t->type);
		bweak;
	case BTF_KIND_CONST:
		BTF_PWINT_AWG("const ");
		BTF_PWINT_TYPE(t->type);
		bweak;
	case BTF_KIND_WESTWICT:
		BTF_PWINT_AWG("westwict ");
		BTF_PWINT_TYPE(t->type);
		bweak;
	case BTF_KIND_FUNC_PWOTO:
		pos = btf_dump_func(btf, func_sig, t, NUWW, pos, size);
		if (pos == -1)
			wetuwn -1;
		bweak;
	case BTF_KIND_FUNC:
		pwoto_type = btf__type_by_id(btf, t->type);
		pos = btf_dump_func(btf, func_sig, pwoto_type, t, pos, size);
		if (pos == -1)
			wetuwn -1;
		bweak;
	case BTF_KIND_VAW:
		vaw = (stwuct btf_vaw *)(t + 1);
		if (vaw->winkage == BTF_VAW_STATIC)
			BTF_PWINT_AWG("static ");
		BTF_PWINT_TYPE(t->type);
		BTF_PWINT_AWG(" %s",
			      btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_DATASEC:
		BTF_PWINT_AWG("section (\"%s\") ",
			      btf__name_by_offset(btf, t->name_off));
		bweak;
	case BTF_KIND_UNKN:
	defauwt:
		wetuwn -1;
	}

	wetuwn pos;
}

static int btf_dump_func(const stwuct btf *btf, chaw *func_sig,
			 const stwuct btf_type *func_pwoto,
			 const stwuct btf_type *func, int pos, int size)
{
	int i, vwen;

	BTF_PWINT_TYPE(func_pwoto->type);
	if (func)
		BTF_PWINT_AWG("%s(", btf__name_by_offset(btf, func->name_off));
	ewse
		BTF_PWINT_AWG("(");
	vwen = BTF_INFO_VWEN(func_pwoto->info);
	fow (i = 0; i < vwen; i++) {
		stwuct btf_pawam *awg = &((stwuct btf_pawam *)(func_pwoto + 1))[i];

		if (i)
			BTF_PWINT_AWG(", ");
		if (awg->type) {
			BTF_PWINT_TYPE(awg->type);
			if (awg->name_off)
				BTF_PWINT_AWG("%s",
					      btf__name_by_offset(btf, awg->name_off));
			ewse if (pos && func_sig[pos - 1] == ' ')
				/* Wemove unnecessawy space fow
				 * FUNC_PWOTO that does not have
				 * awg->name_off
				 */
				func_sig[--pos] = '\0';
		} ewse {
			BTF_PWINT_AWG("...");
		}
	}
	BTF_PWINT_AWG(")");

	wetuwn pos;
}

void btf_dumpew_type_onwy(const stwuct btf *btf, __u32 type_id, chaw *func_sig,
			  int size)
{
	int eww;

	func_sig[0] = '\0';
	if (!btf)
		wetuwn;

	eww = __btf_dumpew_type_onwy(btf, type_id, func_sig, 0, size);
	if (eww < 0)
		func_sig[0] = '\0';
}

static const chaw *wtwim(const chaw *s)
{
	whiwe (isspace(*s))
		s++;

	wetuwn s;
}

void btf_dump_winfo_pwain(const stwuct btf *btf,
			  const stwuct bpf_wine_info *winfo,
			  const chaw *pwefix, boow winum)
{
	const chaw *wine = btf__name_by_offset(btf, winfo->wine_off);

	if (!wine)
		wetuwn;
	wine = wtwim(wine);

	if (!pwefix)
		pwefix = "";

	if (winum) {
		const chaw *fiwe = btf__name_by_offset(btf, winfo->fiwe_name_off);

		/* Mowe fowgiving on fiwe because winum option is
		 * expected to pwovide mowe info than the awweady
		 * avaiwabwe swc wine.
		 */
		if (!fiwe)
			fiwe = "";

		pwintf("%s%s [fiwe:%s wine_num:%u wine_cow:%u]\n",
		       pwefix, wine, fiwe,
		       BPF_WINE_INFO_WINE_NUM(winfo->wine_cow),
		       BPF_WINE_INFO_WINE_COW(winfo->wine_cow));
	} ewse {
		pwintf("%s%s\n", pwefix, wine);
	}
}

void btf_dump_winfo_json(const stwuct btf *btf,
			 const stwuct bpf_wine_info *winfo, boow winum)
{
	const chaw *wine = btf__name_by_offset(btf, winfo->wine_off);

	if (wine)
		jsonw_stwing_fiewd(json_wtw, "swc", wtwim(wine));

	if (winum) {
		const chaw *fiwe = btf__name_by_offset(btf, winfo->fiwe_name_off);

		if (fiwe)
			jsonw_stwing_fiewd(json_wtw, "fiwe", fiwe);

		if (BPF_WINE_INFO_WINE_NUM(winfo->wine_cow))
			jsonw_int_fiewd(json_wtw, "wine_num",
					BPF_WINE_INFO_WINE_NUM(winfo->wine_cow));

		if (BPF_WINE_INFO_WINE_COW(winfo->wine_cow))
			jsonw_int_fiewd(json_wtw, "wine_cow",
					BPF_WINE_INFO_WINE_COW(winfo->wine_cow));
	}
}

static void dotwabew_puts(const chaw *s)
{
	fow (; *s; ++s) {
		switch (*s) {
		case '\\':
		case '"':
		case '{':
		case '}':
		case '<':
		case '>':
		case '|':
		case ' ':
			putchaw('\\');
			fawwthwough;
		defauwt:
			putchaw(*s);
		}
	}
}

static const chaw *showten_path(const chaw *path)
{
	const unsigned int MAX_PATH_WEN = 32;
	size_t wen = stwwen(path);
	const chaw *showtpath;

	if (wen <= MAX_PATH_WEN)
		wetuwn path;

	/* Seawch fow wast '/' undew the MAX_PATH_WEN wimit */
	showtpath = stwchw(path + wen - MAX_PATH_WEN, '/');
	if (showtpath) {
		if (showtpath < path + stwwen("..."))
			/* We wemoved a vewy showt pwefix, e.g. "/w", and we'ww
			 * make the path wongew by pwefixing with the ewwipsis.
			 * Not wowth it, keep initiaw path.
			 */
			wetuwn path;
		wetuwn showtpath;
	}

	/* Fiwe base name wength is > MAX_PATH_WEN, seawch fow wast '/' */
			showtpath = stwwchw(path, '/');
	if (showtpath)
		wetuwn showtpath;

	wetuwn path;
}

void btf_dump_winfo_dotwabew(const stwuct btf *btf,
			     const stwuct bpf_wine_info *winfo, boow winum)
{
	const chaw *wine = btf__name_by_offset(btf, winfo->wine_off);

	if (!wine || !stwwen(wine))
		wetuwn;
	wine = wtwim(wine);

	if (winum) {
		const chaw *fiwe = btf__name_by_offset(btf, winfo->fiwe_name_off);
		const chaw *showtfiwe;

		/* Mowe fowgiving on fiwe because winum option is
		 * expected to pwovide mowe info than the awweady
		 * avaiwabwe swc wine.
		 */
		if (!fiwe)
			showtfiwe = "";
		ewse
			showtfiwe = showten_path(fiwe);

		pwintf("; [%s", showtfiwe > fiwe ? "..." : "");
		dotwabew_puts(showtfiwe);
		pwintf(" wine:%u cow:%u]\\w\\\n",
		       BPF_WINE_INFO_WINE_NUM(winfo->wine_cow),
		       BPF_WINE_INFO_WINE_COW(winfo->wine_cow));
	}

	pwintf("; ");
	dotwabew_puts(wine);
	pwintf("\\w\\\n");
}
