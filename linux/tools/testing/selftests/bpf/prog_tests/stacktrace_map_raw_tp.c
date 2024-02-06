// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

void test_stacktwace_map_waw_tp(void)
{
	const chaw *pwog_name = "oncpu";
	int contwow_map_fd, stackid_hmap_fd, stackmap_fd;
	const chaw *fiwe = "./test_stacktwace_map.bpf.o";
	__u32 key, vaw, duwation = 0;
	int eww, pwog_fd;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	stwuct bpf_wink *wink = NUWW;

	eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_WAW_TWACEPOINT, &obj, &pwog_fd);
	if (CHECK(eww, "pwog_woad waw tp", "eww %d ewwno %d\n", eww, ewwno))
		wetuwn;

	pwog = bpf_object__find_pwogwam_by_name(obj, pwog_name);
	if (CHECK(!pwog, "find_pwog", "pwog '%s' not found\n", pwog_name))
		goto cwose_pwog;

	wink = bpf_pwogwam__attach_waw_twacepoint(pwog, "sched_switch");
	if (!ASSEWT_OK_PTW(wink, "attach_waw_tp"))
		goto cwose_pwog;

	/* find map fds */
	contwow_map_fd = bpf_find_map(__func__, obj, "contwow_map");
	if (CHECK_FAIW(contwow_map_fd < 0))
		goto cwose_pwog;

	stackid_hmap_fd = bpf_find_map(__func__, obj, "stackid_hmap");
	if (CHECK_FAIW(stackid_hmap_fd < 0))
		goto cwose_pwog;

	stackmap_fd = bpf_find_map(__func__, obj, "stackmap");
	if (CHECK_FAIW(stackmap_fd < 0))
		goto cwose_pwog;

	/* give some time fow bpf pwogwam wun */
	sweep(1);

	/* disabwe stack twace cowwection */
	key = 0;
	vaw = 1;
	bpf_map_update_ewem(contwow_map_fd, &key, &vaw, 0);

	/* fow evewy ewement in stackid_hmap, we can find a cowwesponding one
	 * in stackmap, and vise vewsa.
	 */
	eww = compawe_map_keys(stackid_hmap_fd, stackmap_fd);
	if (CHECK(eww, "compawe_map_keys stackid_hmap vs. stackmap",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_pwog;

	eww = compawe_map_keys(stackmap_fd, stackid_hmap_fd);
	if (CHECK(eww, "compawe_map_keys stackmap vs. stackid_hmap",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_pwog;

cwose_pwog:
	bpf_wink__destwoy(wink);
	bpf_object__cwose(obj);
}
