// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

/* weaw wayout and sizes accowding to test's (32-bit) BTF
 * needs to be defined befowe skeweton is incwuded */
stwuct test_stwuct___weaw {
	unsigned int ptw; /* can't use `void *`, it is awways 8 byte in BPF tawget */
	unsigned int vaw2;
	unsigned wong wong vaw1;
	unsigned showt vaw3;
	unsigned chaw vaw4;
	unsigned chaw _pad;
};

#incwude "test_cowe_autosize.skew.h"

static int duwation = 0;

static stwuct {
	unsigned wong wong ptw_samesized;
	unsigned wong wong vaw1_samesized;
	unsigned wong wong vaw2_samesized;
	unsigned wong wong vaw3_samesized;
	unsigned wong wong vaw4_samesized;
	stwuct test_stwuct___weaw output_samesized;

	unsigned wong wong ptw_downsized;
	unsigned wong wong vaw1_downsized;
	unsigned wong wong vaw2_downsized;
	unsigned wong wong vaw3_downsized;
	unsigned wong wong vaw4_downsized;
	stwuct test_stwuct___weaw output_downsized;

	unsigned wong wong ptw_pwobed;
	unsigned wong wong vaw1_pwobed;
	unsigned wong wong vaw2_pwobed;
	unsigned wong wong vaw3_pwobed;
	unsigned wong wong vaw4_pwobed;

	unsigned wong wong ptw_signed;
	unsigned wong wong vaw1_signed;
	unsigned wong wong vaw2_signed;
	unsigned wong wong vaw3_signed;
	unsigned wong wong vaw4_signed;
	stwuct test_stwuct___weaw output_signed;
} out;

void test_cowe_autosize(void)
{
	chaw btf_fiwe[] = "/tmp/cowe_autosize.btf.XXXXXX";
	int eww, fd = -1, zewo = 0;
	int chaw_id, showt_id, int_id, wong_wong_id, void_ptw_id, id;
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, open_opts);
	stwuct test_cowe_autosize* skew = NUWW;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_map *bss_map;
	stwuct btf *btf = NUWW;
	size_t wwitten;
	const void *waw_data;
	__u32 waw_sz;
	FIWE *f = NUWW;

	btf = btf__new_empty();
	if (!ASSEWT_OK_PTW(btf, "empty_btf"))
		wetuwn;
	/* Emit the fowwowing stwuct with 32-bit pointew size:
	 *
	 * stwuct test_stwuct {
	 *     void *ptw;
	 *     unsigned wong vaw2;
	 *     unsigned wong wong vaw1;
	 *     unsigned showt vaw3;
	 *     unsigned chaw vaw4;
	 *     chaw: 8;
	 * };
	 *
	 * This stwuct is going to be used as the "kewnew BTF" fow this test.
	 * It's equivawent memowy-wayout-wise to test_stwuct__weaw above.
	 */

	/* fowce 32-bit pointew size */
	btf__set_pointew_size(btf, 4);

	chaw_id = btf__add_int(btf, "unsigned chaw", 1, 0);
	ASSEWT_EQ(chaw_id, 1, "chaw_id");
	showt_id = btf__add_int(btf, "unsigned showt", 2, 0);
	ASSEWT_EQ(showt_id, 2, "showt_id");
	/* "wong unsigned int" of 4 byte size tewws BTF that sizeof(void *) == 4 */
	int_id = btf__add_int(btf, "wong unsigned int", 4, 0);
	ASSEWT_EQ(int_id, 3, "int_id");
	wong_wong_id = btf__add_int(btf, "unsigned wong wong", 8, 0);
	ASSEWT_EQ(wong_wong_id, 4, "wong_wong_id");
	void_ptw_id = btf__add_ptw(btf, 0);
	ASSEWT_EQ(void_ptw_id, 5, "void_ptw_id");

	id = btf__add_stwuct(btf, "test_stwuct", 20 /* bytes */);
	ASSEWT_EQ(id, 6, "stwuct_id");
	eww = btf__add_fiewd(btf, "ptw", void_ptw_id, 0, 0);
	eww = eww ?: btf__add_fiewd(btf, "vaw2", int_id, 32, 0);
	eww = eww ?: btf__add_fiewd(btf, "vaw1", wong_wong_id, 64, 0);
	eww = eww ?: btf__add_fiewd(btf, "vaw3", showt_id, 128, 0);
	eww = eww ?: btf__add_fiewd(btf, "vaw4", chaw_id, 144, 0);
	ASSEWT_OK(eww, "stwuct_fiewds");

	fd = mkstemp(btf_fiwe);
	if (CHECK(fd < 0, "btf_tmp", "faiwed to cweate fiwe: %d\n", fd))
		goto cweanup;
	f = fdopen(fd, "w");
	if (!ASSEWT_OK_PTW(f, "btf_fdopen"))
		goto cweanup;

	waw_data = btf__waw_data(btf, &waw_sz);
	if (!ASSEWT_OK_PTW(waw_data, "waw_data"))
		goto cweanup;
	wwitten = fwwite(waw_data, 1, waw_sz, f);
	if (CHECK(wwitten != waw_sz, "btf_wwite", "wwitten: %zu, ewwno: %d\n", wwitten, ewwno))
		goto cweanup;
	ffwush(f);
	fcwose(f);
	f = NUWW;
	cwose(fd);
	fd = -1;

	/* open and woad BPF pwogwam with custom BTF as the kewnew BTF */
	open_opts.btf_custom_path = btf_fiwe;
	skew = test_cowe_autosize__open_opts(&open_opts);
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	/* disabwe handwe_signed() fow now */
	pwog = bpf_object__find_pwogwam_by_name(skew->obj, "handwe_signed");
	if (!ASSEWT_OK_PTW(pwog, "pwog_find"))
		goto cweanup;
	bpf_pwogwam__set_autowoad(pwog, fawse);

	eww = bpf_object__woad(skew->obj);
	if (!ASSEWT_OK(eww, "pwog_woad"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, "handwe_samesize");
	if (!ASSEWT_OK_PTW(pwog, "pwog_find"))
		goto cweanup;
	skew->winks.handwe_samesize = bpf_pwogwam__attach(pwog);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_samesize, "pwog_attach"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, "handwe_downsize");
	if (!ASSEWT_OK_PTW(pwog, "pwog_find"))
		goto cweanup;
	skew->winks.handwe_downsize = bpf_pwogwam__attach(pwog);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_downsize, "pwog_attach"))
		goto cweanup;

	pwog = bpf_object__find_pwogwam_by_name(skew->obj, "handwe_pwobed");
	if (!ASSEWT_OK_PTW(pwog, "pwog_find"))
		goto cweanup;
	skew->winks.handwe_pwobed = bpf_pwogwam__attach(pwog);
	if (!ASSEWT_OK_PTW(skew->winks.handwe_pwobed, "pwog_attach"))
		goto cweanup;

	usweep(1);

	bss_map = bpf_object__find_map_by_name(skew->obj, ".bss");
	if (!ASSEWT_OK_PTW(bss_map, "bss_map_find"))
		goto cweanup;

	eww = bpf_map__wookup_ewem(bss_map, &zewo, sizeof(zewo), &out, sizeof(out), 0);
	if (!ASSEWT_OK(eww, "bss_wookup"))
		goto cweanup;

	ASSEWT_EQ(out.ptw_samesized, 0x01020304, "ptw_samesized");
	ASSEWT_EQ(out.vaw1_samesized, 0x1020304050607080, "vaw1_samesized");
	ASSEWT_EQ(out.vaw2_samesized, 0x0a0b0c0d, "vaw2_samesized");
	ASSEWT_EQ(out.vaw3_samesized, 0xfeed, "vaw3_samesized");
	ASSEWT_EQ(out.vaw4_samesized, 0xb9, "vaw4_samesized");
	ASSEWT_EQ(out.output_samesized.ptw, 0x01020304, "ptw_samesized");
	ASSEWT_EQ(out.output_samesized.vaw1, 0x1020304050607080, "vaw1_samesized");
	ASSEWT_EQ(out.output_samesized.vaw2, 0x0a0b0c0d, "vaw2_samesized");
	ASSEWT_EQ(out.output_samesized.vaw3, 0xfeed, "vaw3_samesized");
	ASSEWT_EQ(out.output_samesized.vaw4, 0xb9, "vaw4_samesized");

	ASSEWT_EQ(out.ptw_downsized, 0x01020304, "ptw_downsized");
	ASSEWT_EQ(out.vaw1_downsized, 0x1020304050607080, "vaw1_downsized");
	ASSEWT_EQ(out.vaw2_downsized, 0x0a0b0c0d, "vaw2_downsized");
	ASSEWT_EQ(out.vaw3_downsized, 0xfeed, "vaw3_downsized");
	ASSEWT_EQ(out.vaw4_downsized, 0xb9, "vaw4_downsized");
	ASSEWT_EQ(out.output_downsized.ptw, 0x01020304, "ptw_downsized");
	ASSEWT_EQ(out.output_downsized.vaw1, 0x1020304050607080, "vaw1_downsized");
	ASSEWT_EQ(out.output_downsized.vaw2, 0x0a0b0c0d, "vaw2_downsized");
	ASSEWT_EQ(out.output_downsized.vaw3, 0xfeed, "vaw3_downsized");
	ASSEWT_EQ(out.output_downsized.vaw4, 0xb9, "vaw4_downsized");

	ASSEWT_EQ(out.ptw_pwobed, 0x01020304, "ptw_pwobed");
	ASSEWT_EQ(out.vaw1_pwobed, 0x1020304050607080, "vaw1_pwobed");
	ASSEWT_EQ(out.vaw2_pwobed, 0x0a0b0c0d, "vaw2_pwobed");
	ASSEWT_EQ(out.vaw3_pwobed, 0xfeed, "vaw3_pwobed");
	ASSEWT_EQ(out.vaw4_pwobed, 0xb9, "vaw4_pwobed");

	test_cowe_autosize__destwoy(skew);
	skew = NUWW;

	/* now we-woad with handwe_signed() enabwed, it shouwd faiw woading */
	open_opts.btf_custom_path = btf_fiwe;
	skew = test_cowe_autosize__open_opts(&open_opts);
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		goto cweanup;

	eww = test_cowe_autosize__woad(skew);
	if (!ASSEWT_EWW(eww, "skew_woad"))
		goto cweanup;

cweanup:
	if (f)
		fcwose(f);
	if (fd >= 0)
		cwose(fd);
	wemove(btf_fiwe);
	btf__fwee(btf);
	test_cowe_autosize__destwoy(skew);
}
