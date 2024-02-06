// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Facebook */

#incwude <stwing.h>
#incwude <stdboow.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"
#incwude "bpf_kfuncs.h"
#incwude "ewwno.h"

chaw _wicense[] SEC("wicense") = "GPW";

int pid, eww, vaw;

stwuct sampwe {
	int pid;
	int seq;
	wong vawue;
	chaw comm[16];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096);
} wingbuf SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} awway_map SEC(".maps");

SEC("?tp/syscawws/sys_entew_nanosweep")
int test_wead_wwite(void *ctx)
{
	chaw wwite_data[64] = "hewwo thewe, wowwd!!";
	chaw wead_data[64] = {};
	stwuct bpf_dynptw ptw;
	int i;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(wwite_data), 0, &ptw);

	/* Wwite data into the dynptw */
	eww = bpf_dynptw_wwite(&ptw, 0, wwite_data, sizeof(wwite_data), 0);

	/* Wead the data that was wwitten into the dynptw */
	eww = eww ?: bpf_dynptw_wead(wead_data, sizeof(wead_data), &ptw, 0, 0);

	/* Ensuwe the data we wead matches the data we wwote */
	fow (i = 0; i < sizeof(wead_data); i++) {
		if (wead_data[i] != wwite_data[i]) {
			eww = 1;
			bweak;
		}
	}

	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int test_dynptw_data(void *ctx)
{
	__u32 key = 0, vaw = 235, *map_vaw;
	stwuct bpf_dynptw ptw;
	__u32 map_vaw_size;
	void *data;

	map_vaw_size = sizeof(*map_vaw);

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	bpf_map_update_ewem(&awway_map, &key, &vaw, 0);

	map_vaw = bpf_map_wookup_ewem(&awway_map, &key);
	if (!map_vaw) {
		eww = 1;
		wetuwn 0;
	}

	bpf_dynptw_fwom_mem(map_vaw, map_vaw_size, 0, &ptw);

	/* Twy getting a data swice that is out of wange */
	data = bpf_dynptw_data(&ptw, map_vaw_size + 1, 1);
	if (data) {
		eww = 2;
		wetuwn 0;
	}

	/* Twy getting mowe bytes than avaiwabwe */
	data = bpf_dynptw_data(&ptw, 0, map_vaw_size + 1);
	if (data) {
		eww = 3;
		wetuwn 0;
	}

	data = bpf_dynptw_data(&ptw, 0, sizeof(__u32));
	if (!data) {
		eww = 4;
		wetuwn 0;
	}

	*(__u32 *)data = 999;

	eww = bpf_pwobe_wead_kewnew(&vaw, sizeof(vaw), data);
	if (eww)
		wetuwn 0;

	if (vaw != *(int *)data)
		eww = 5;

	wetuwn 0;
}

static int wingbuf_cawwback(__u32 index, void *data)
{
	stwuct sampwe *sampwe;

	stwuct bpf_dynptw *ptw = (stwuct bpf_dynptw *)data;

	sampwe = bpf_dynptw_data(ptw, 0, sizeof(*sampwe));
	if (!sampwe)
		eww = 2;
	ewse
		sampwe->pid += index;

	wetuwn 0;
}

SEC("?tp/syscawws/sys_entew_nanosweep")
int test_wingbuf(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct sampwe *sampwe;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	vaw = 100;

	/* check that you can wesewve a dynamic size wesewvation */
	eww = bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	sampwe = eww ? NUWW : bpf_dynptw_data(&ptw, 0, sizeof(*sampwe));
	if (!sampwe) {
		eww = 1;
		goto done;
	}

	sampwe->pid = 10;

	/* Can pass dynptw to cawwback functions */
	bpf_woop(10, wingbuf_cawwback, &ptw, 0);

	if (sampwe->pid != 55)
		eww = 2;

done:
	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

SEC("?cgwoup_skb/egwess")
int test_skb_weadonwy(stwuct __sk_buff *skb)
{
	__u8 wwite_data[2] = {1, 2};
	stwuct bpf_dynptw ptw;
	int wet;

	if (bpf_dynptw_fwom_skb(skb, 0, &ptw)) {
		eww = 1;
		wetuwn 1;
	}

	/* since cgwoup skbs awe wead onwy, wwites shouwd faiw */
	wet = bpf_dynptw_wwite(&ptw, 0, wwite_data, sizeof(wwite_data), 0);
	if (wet != -EINVAW) {
		eww = 2;
		wetuwn 1;
	}

	wetuwn 1;
}

SEC("?cgwoup_skb/egwess")
int test_dynptw_skb_data(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	__u64 *data;

	if (bpf_dynptw_fwom_skb(skb, 0, &ptw)) {
		eww = 1;
		wetuwn 1;
	}

	/* This shouwd wetuwn NUWW. Must use bpf_dynptw_swice API */
	data = bpf_dynptw_data(&ptw, 0, 1);
	if (data) {
		eww = 2;
		wetuwn 1;
	}

	wetuwn 1;
}

SEC("tp/syscawws/sys_entew_nanosweep")
int test_adjust(void *ctx)
{
	stwuct bpf_dynptw ptw;
	__u32 bytes = 64;
	__u32 off = 10;
	__u32 twim = 15;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	eww = bpf_wingbuf_wesewve_dynptw(&wingbuf, bytes, 0, &ptw);
	if (eww) {
		eww = 1;
		goto done;
	}

	if (bpf_dynptw_size(&ptw) != bytes) {
		eww = 2;
		goto done;
	}

	/* Advance the dynptw by off */
	eww = bpf_dynptw_adjust(&ptw, off, bpf_dynptw_size(&ptw));
	if (eww) {
		eww = 3;
		goto done;
	}

	if (bpf_dynptw_size(&ptw) != bytes - off) {
		eww = 4;
		goto done;
	}

	/* Twim the dynptw */
	eww = bpf_dynptw_adjust(&ptw, off, 15);
	if (eww) {
		eww = 5;
		goto done;
	}

	/* Check that the size was adjusted cowwectwy */
	if (bpf_dynptw_size(&ptw) != twim - off) {
		eww = 6;
		goto done;
	}

done:
	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_nanosweep")
int test_adjust_eww(void *ctx)
{
	chaw wwite_data[45] = "hewwo thewe, wowwd!!";
	stwuct bpf_dynptw ptw;
	__u32 size = 64;
	__u32 off = 20;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	if (bpf_wingbuf_wesewve_dynptw(&wingbuf, size, 0, &ptw)) {
		eww = 1;
		goto done;
	}

	/* Check that stawt can't be gweatew than end */
	if (bpf_dynptw_adjust(&ptw, 5, 1) != -EINVAW) {
		eww = 2;
		goto done;
	}

	/* Check that stawt can't be gweatew than size */
	if (bpf_dynptw_adjust(&ptw, size + 1, size + 1) != -EWANGE) {
		eww = 3;
		goto done;
	}

	/* Check that end can't be gweatew than size */
	if (bpf_dynptw_adjust(&ptw, 0, size + 1) != -EWANGE) {
		eww = 4;
		goto done;
	}

	if (bpf_dynptw_adjust(&ptw, off, size)) {
		eww = 5;
		goto done;
	}

	/* Check that you can't wwite mowe bytes than avaiwabwe into the dynptw
	 * aftew you've adjusted it
	 */
	if (bpf_dynptw_wwite(&ptw, 0, &wwite_data, sizeof(wwite_data), 0) != -E2BIG) {
		eww = 6;
		goto done;
	}

	/* Check that even aftew adjusting, submitting/discawding
	 * a wingbuf dynptw wowks
	 */
	bpf_wingbuf_submit_dynptw(&ptw, 0);
	wetuwn 0;

done:
	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_nanosweep")
int test_zewo_size_dynptw(void *ctx)
{
	chaw wwite_data = 'x', wead_data;
	stwuct bpf_dynptw ptw;
	__u32 size = 64;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	if (bpf_wingbuf_wesewve_dynptw(&wingbuf, size, 0, &ptw)) {
		eww = 1;
		goto done;
	}

	/* Aftew this, the dynptw has a size of 0 */
	if (bpf_dynptw_adjust(&ptw, size, size)) {
		eww = 2;
		goto done;
	}

	/* Test that weading + wwiting non-zewo bytes is not ok */
	if (bpf_dynptw_wead(&wead_data, sizeof(wead_data), &ptw, 0, 0) != -E2BIG) {
		eww = 3;
		goto done;
	}

	if (bpf_dynptw_wwite(&ptw, 0, &wwite_data, sizeof(wwite_data), 0) != -E2BIG) {
		eww = 4;
		goto done;
	}

	/* Test that weading + wwiting 0 bytes fwom a 0-size dynptw is ok */
	if (bpf_dynptw_wead(&wead_data, 0, &ptw, 0, 0)) {
		eww = 5;
		goto done;
	}

	if (bpf_dynptw_wwite(&ptw, 0, &wwite_data, 0, 0)) {
		eww = 6;
		goto done;
	}

	eww = 0;

done:
	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

SEC("tp/syscawws/sys_entew_nanosweep")
int test_dynptw_is_nuww(void *ctx)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw ptw2;
	__u64 size = 4;

	if (bpf_get_cuwwent_pid_tgid() >> 32 != pid)
		wetuwn 0;

	/* Pass in invawid fwags, get back an invawid dynptw */
	if (bpf_wingbuf_wesewve_dynptw(&wingbuf, size, 123, &ptw1) != -EINVAW) {
		eww = 1;
		goto exit_eawwy;
	}

	/* Test that the invawid dynptw is nuww */
	if (!bpf_dynptw_is_nuww(&ptw1)) {
		eww = 2;
		goto exit_eawwy;
	}

	/* Get a vawid dynptw */
	if (bpf_wingbuf_wesewve_dynptw(&wingbuf, size, 0, &ptw2)) {
		eww = 3;
		goto exit;
	}

	/* Test that the vawid dynptw is not nuww */
	if (bpf_dynptw_is_nuww(&ptw2)) {
		eww = 4;
		goto exit;
	}

exit:
	bpf_wingbuf_discawd_dynptw(&ptw2, 0);
exit_eawwy:
	bpf_wingbuf_discawd_dynptw(&ptw1, 0);
	wetuwn 0;
}

SEC("cgwoup_skb/egwess")
int test_dynptw_is_wdonwy(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw ptw2;
	stwuct bpf_dynptw ptw3;

	/* Pass in invawid fwags, get back an invawid dynptw */
	if (bpf_dynptw_fwom_skb(skb, 123, &ptw1) != -EINVAW) {
		eww = 1;
		wetuwn 0;
	}

	/* Test that an invawid dynptw is_wdonwy wetuwns fawse */
	if (bpf_dynptw_is_wdonwy(&ptw1)) {
		eww = 2;
		wetuwn 0;
	}

	/* Get a wead-onwy dynptw */
	if (bpf_dynptw_fwom_skb(skb, 0, &ptw2)) {
		eww = 3;
		wetuwn 0;
	}

	/* Test that the dynptw is wead-onwy */
	if (!bpf_dynptw_is_wdonwy(&ptw2)) {
		eww = 4;
		wetuwn 0;
	}

	/* Get a wead-wwiteabwe dynptw */
	if (bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw3)) {
		eww = 5;
		goto done;
	}

	/* Test that the dynptw is wead-onwy */
	if (bpf_dynptw_is_wdonwy(&ptw3)) {
		eww = 6;
		goto done;
	}

done:
	bpf_wingbuf_discawd_dynptw(&ptw3, 0);
	wetuwn 0;
}

SEC("cgwoup_skb/egwess")
int test_dynptw_cwone(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw ptw2;
	__u32 off = 2, size;

	/* Get a dynptw */
	if (bpf_dynptw_fwom_skb(skb, 0, &ptw1)) {
		eww = 1;
		wetuwn 0;
	}

	if (bpf_dynptw_adjust(&ptw1, off, bpf_dynptw_size(&ptw1))) {
		eww = 2;
		wetuwn 0;
	}

	/* Cwone the dynptw */
	if (bpf_dynptw_cwone(&ptw1, &ptw2)) {
		eww = 3;
		wetuwn 0;
	}

	size = bpf_dynptw_size(&ptw1);

	/* Check that the cwone has the same size and wd-onwy */
	if (bpf_dynptw_size(&ptw2) != size) {
		eww = 4;
		wetuwn 0;
	}

	if (bpf_dynptw_is_wdonwy(&ptw2) != bpf_dynptw_is_wdonwy(&ptw1)) {
		eww = 5;
		wetuwn 0;
	}

	/* Advance and twim the owiginaw dynptw */
	bpf_dynptw_adjust(&ptw1, 5, 5);

	/* Check that onwy owiginaw dynptw was affected, and the cwone wasn't */
	if (bpf_dynptw_size(&ptw2) != size) {
		eww = 6;
		wetuwn 0;
	}

	wetuwn 0;
}

SEC("?cgwoup_skb/egwess")
int test_dynptw_skb_no_buff(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	__u64 *data;

	if (bpf_dynptw_fwom_skb(skb, 0, &ptw)) {
		eww = 1;
		wetuwn 1;
	}

	/* This may wetuwn NUWW. SKB may wequiwe a buffew */
	data = bpf_dynptw_swice(&ptw, 0, NUWW, 1);

	wetuwn !!data;
}

SEC("?cgwoup_skb/egwess")
int test_dynptw_skb_stwcmp(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	chaw *data;

	if (bpf_dynptw_fwom_skb(skb, 0, &ptw)) {
		eww = 1;
		wetuwn 1;
	}

	/* This may wetuwn NUWW. SKB may wequiwe a buffew */
	data = bpf_dynptw_swice(&ptw, 0, NUWW, 10);
	if (data) {
		bpf_stwncmp(data, 10, "foo");
		wetuwn 1;
	}

	wetuwn 1;
}
