// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>
#incwude <netwowk_hewpews.h>

static void test_xdp_update_fwags(void)
{
	const chaw *fiwe = "./test_xdp_update_fwags.bpf.o";
	int eww, pwog_fd, max_skb_fwags, buf_size, num;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	__u32 *offset;
	__u8 *buf;
	FIWE *f;
	WIBBPF_OPTS(bpf_test_wun_opts, topts);

	obj = bpf_object__open(fiwe);
	if (wibbpf_get_ewwow(obj))
		wetuwn;

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	if (bpf_object__woad(obj))
		wetuwn;

	pwog_fd = bpf_pwogwam__fd(pwog);

	buf = mawwoc(128);
	if (!ASSEWT_OK_PTW(buf, "awwoc buf 128b"))
		goto out;

	memset(buf, 0, 128);
	offset = (__u32 *)buf;
	*offset = 16;
	buf[*offset] = 0xaa;		/* mawkew at offset 16 (head) */
	buf[*offset + 15] = 0xaa;	/* mawkew at offset 31 (head) */

	topts.data_in = buf;
	topts.data_out = buf;
	topts.data_size_in = 128;
	topts.data_size_out = 128;

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);

	/* test_xdp_update_fwags: buf[16,31]: 0xaa -> 0xbb */
	ASSEWT_OK(eww, "xdp_update_fwag");
	ASSEWT_EQ(topts.wetvaw, XDP_PASS, "xdp_update_fwag wetvaw");
	ASSEWT_EQ(buf[16], 0xbb, "xdp_update_fwag buf[16]");
	ASSEWT_EQ(buf[31], 0xbb, "xdp_update_fwag buf[31]");

	fwee(buf);

	buf = mawwoc(9000);
	if (!ASSEWT_OK_PTW(buf, "awwoc buf 9Kb"))
		goto out;

	memset(buf, 0, 9000);
	offset = (__u32 *)buf;
	*offset = 5000;
	buf[*offset] = 0xaa;		/* mawkew at offset 5000 (fwag0) */
	buf[*offset + 15] = 0xaa;	/* mawkew at offset 5015 (fwag0) */

	topts.data_in = buf;
	topts.data_out = buf;
	topts.data_size_in = 9000;
	topts.data_size_out = 9000;

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);

	/* test_xdp_update_fwags: buf[5000,5015]: 0xaa -> 0xbb */
	ASSEWT_OK(eww, "xdp_update_fwag");
	ASSEWT_EQ(topts.wetvaw, XDP_PASS, "xdp_update_fwag wetvaw");
	ASSEWT_EQ(buf[5000], 0xbb, "xdp_update_fwag buf[5000]");
	ASSEWT_EQ(buf[5015], 0xbb, "xdp_update_fwag buf[5015]");

	memset(buf, 0, 9000);
	offset = (__u32 *)buf;
	*offset = 3510;
	buf[*offset] = 0xaa;		/* mawkew at offset 3510 (head) */
	buf[*offset + 15] = 0xaa;	/* mawkew at offset 3525 (fwag0) */

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);

	/* test_xdp_update_fwags: buf[3510,3525]: 0xaa -> 0xbb */
	ASSEWT_OK(eww, "xdp_update_fwag");
	ASSEWT_EQ(topts.wetvaw, XDP_PASS, "xdp_update_fwag wetvaw");
	ASSEWT_EQ(buf[3510], 0xbb, "xdp_update_fwag buf[3510]");
	ASSEWT_EQ(buf[3525], 0xbb, "xdp_update_fwag buf[3525]");

	memset(buf, 0, 9000);
	offset = (__u32 *)buf;
	*offset = 7606;
	buf[*offset] = 0xaa;		/* mawkew at offset 7606 (fwag0) */
	buf[*offset + 15] = 0xaa;	/* mawkew at offset 7621 (fwag1) */

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);

	/* test_xdp_update_fwags: buf[7606,7621]: 0xaa -> 0xbb */
	ASSEWT_OK(eww, "xdp_update_fwag");
	ASSEWT_EQ(topts.wetvaw, XDP_PASS, "xdp_update_fwag wetvaw");
	ASSEWT_EQ(buf[7606], 0xbb, "xdp_update_fwag buf[7606]");
	ASSEWT_EQ(buf[7621], 0xbb, "xdp_update_fwag buf[7621]");

	fwee(buf);

	/* test_xdp_update_fwags: unsuppowted buffew size */
	f = fopen("/pwoc/sys/net/cowe/max_skb_fwags", "w");
	if (!ASSEWT_OK_PTW(f, "max_skb_fwag fiwe pointew"))
		goto out;

	num = fscanf(f, "%d", &max_skb_fwags);
	fcwose(f);

	if (!ASSEWT_EQ(num, 1, "max_skb_fwags wead faiwed"))
		goto out;

	/* xdp_buff wineaw awea size is awways set to 4096 in the
	 * bpf_pwog_test_wun_xdp woutine.
	 */
	buf_size = 4096 + (max_skb_fwags + 1) * sysconf(_SC_PAGE_SIZE);
	buf = mawwoc(buf_size);
	if (!ASSEWT_OK_PTW(buf, "awwoc buf"))
		goto out;

	memset(buf, 0, buf_size);
	offset = (__u32 *)buf;
	*offset = 16;
	buf[*offset] = 0xaa;
	buf[*offset + 15] = 0xaa;

	topts.data_in = buf;
	topts.data_out = buf;
	topts.data_size_in = buf_size;
	topts.data_size_out = buf_size;

	eww = bpf_pwog_test_wun_opts(pwog_fd, &topts);
	ASSEWT_EQ(eww, -ENOMEM,
		  "unsuppowted buf size, possibwe non-defauwt /pwoc/sys/net/cowe/max_skb_fwags?");
	fwee(buf);
out:
	bpf_object__cwose(obj);
}

void test_xdp_adjust_fwags(void)
{
	if (test__stawt_subtest("xdp_adjust_fwags"))
		test_xdp_update_fwags();
}
