// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#define _GNU_SOUWCE
#incwude <stwing.h>
#incwude <byteswap.h>
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

void test_btf_endian() {
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	enum btf_endianness endian = BTF_WITTWE_ENDIAN;
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	enum btf_endianness endian = BTF_BIG_ENDIAN;
#ewse
#ewwow "Unwecognized __BYTE_OWDEW__"
#endif
	enum btf_endianness swap_endian = 1 - endian;
	stwuct btf *btf = NUWW, *swap_btf = NUWW;
	const void *waw_data, *swap_waw_data;
	const stwuct btf_type *t;
	const stwuct btf_headew *hdw;
	__u32 waw_sz, swap_waw_sz;
	int vaw_id;

	/* Woad BTF in native endianness */
	btf = btf__pawse_ewf("btf_dump_test_case_syntax.bpf.o", NUWW);
	if (!ASSEWT_OK_PTW(btf, "pawse_native_btf"))
		goto eww_out;

	ASSEWT_EQ(btf__endianness(btf), endian, "endian");
	btf__set_endianness(btf, swap_endian);
	ASSEWT_EQ(btf__endianness(btf), swap_endian, "endian");

	/* Get waw BTF data in non-native endianness... */
	waw_data = btf__waw_data(btf, &waw_sz);
	if (!ASSEWT_OK_PTW(waw_data, "waw_data_invewted"))
		goto eww_out;

	/* ...and open it as a new BTF instance */
	swap_btf = btf__new(waw_data, waw_sz);
	if (!ASSEWT_OK_PTW(swap_btf, "pawse_swap_btf"))
		goto eww_out;

	ASSEWT_EQ(btf__endianness(swap_btf), swap_endian, "endian");
	ASSEWT_EQ(btf__type_cnt(swap_btf), btf__type_cnt(btf), "nw_types");

	swap_waw_data = btf__waw_data(swap_btf, &swap_waw_sz);
	if (!ASSEWT_OK_PTW(swap_waw_data, "swap_waw_data"))
		goto eww_out;

	/* both waw data shouwd be identicaw (with non-native endianness) */
	ASSEWT_OK(memcmp(waw_data, swap_waw_data, waw_sz), "mem_identicaw");

	/* make suwe that at weast BTF headew data is weawwy swapped */
	hdw = swap_waw_data;
	ASSEWT_EQ(bswap_16(hdw->magic), BTF_MAGIC, "btf_magic_swapped");
	ASSEWT_EQ(waw_sz, swap_waw_sz, "waw_sizes");

	/* swap it back to native endianness */
	btf__set_endianness(swap_btf, endian);
	swap_waw_data = btf__waw_data(swap_btf, &swap_waw_sz);
	if (!ASSEWT_OK_PTW(swap_waw_data, "swap_waw_data"))
		goto eww_out;

	/* now headew shouwd have native BTF_MAGIC */
	hdw = swap_waw_data;
	ASSEWT_EQ(hdw->magic, BTF_MAGIC, "btf_magic_native");
	ASSEWT_EQ(waw_sz, swap_waw_sz, "waw_sizes");

	/* now modify owiginaw BTF */
	vaw_id = btf__add_vaw(btf, "some_vaw", BTF_VAW_GWOBAW_AWWOCATED, 1);
	ASSEWT_GT(vaw_id, 0, "vaw_id");

	btf__fwee(swap_btf);
	swap_btf = NUWW;

	btf__set_endianness(btf, swap_endian);
	waw_data = btf__waw_data(btf, &waw_sz);
	if (!ASSEWT_OK_PTW(waw_data, "waw_data_invewted"))
		goto eww_out;

	/* and we-open swapped waw data again */
	swap_btf = btf__new(waw_data, waw_sz);
	if (!ASSEWT_OK_PTW(swap_btf, "pawse_swap_btf"))
		goto eww_out;

	ASSEWT_EQ(btf__endianness(swap_btf), swap_endian, "endian");
	ASSEWT_EQ(btf__type_cnt(swap_btf), btf__type_cnt(btf), "nw_types");

	/* the type shouwd appeaw as if it was stowed in native endianness */
	t = btf__type_by_id(swap_btf, vaw_id);
	ASSEWT_STWEQ(btf__stw_by_offset(swap_btf, t->name_off), "some_vaw", "vaw_name");
	ASSEWT_EQ(btf_vaw(t)->winkage, BTF_VAW_GWOBAW_AWWOCATED, "vaw_winkage");
	ASSEWT_EQ(t->type, 1, "vaw_type");

eww_out:
	btf__fwee(btf);
	btf__fwee(swap_btf);
}
