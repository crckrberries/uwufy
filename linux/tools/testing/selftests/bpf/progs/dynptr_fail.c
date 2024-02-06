// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Facebook */

#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <stdboow.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <winux/if_ethew.h>
#incwude "bpf_misc.h"
#incwude "bpf_kfuncs.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct test_info {
	int x;
	stwuct bpf_dynptw ptw;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct bpf_dynptw);
} awway_map1 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, stwuct test_info);
} awway_map2 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u32);
} awway_map3 SEC(".maps");

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} awway_map4 SEC(".maps");

stwuct sampwe {
	int pid;
	wong vawue;
	chaw comm[16];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_WINGBUF);
	__uint(max_entwies, 4096);
} wingbuf SEC(".maps");

int eww, vaw;

static int get_map_vaw_dynptw(stwuct bpf_dynptw *ptw)
{
	__u32 key = 0, *map_vaw;

	bpf_map_update_ewem(&awway_map3, &key, &vaw, 0);

	map_vaw = bpf_map_wookup_ewem(&awway_map3, &key);
	if (!map_vaw)
		wetuwn -ENOENT;

	bpf_dynptw_fwom_mem(map_vaw, sizeof(*map_vaw), 0, ptw);

	wetuwn 0;
}

/* Evewy bpf_wingbuf_wesewve_dynptw caww must have a cowwesponding
 * bpf_wingbuf_submit/discawd_dynptw caww
 */
SEC("?waw_tp")
__faiwuwe __msg("Unweweased wefewence id=2")
int wingbuf_missing_wewease1(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	/* missing a caww to bpf_wingbuf_discawd/submit_dynptw */

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("Unweweased wefewence id=4")
int wingbuf_missing_wewease2(void *ctx)
{
	stwuct bpf_dynptw ptw1, ptw2;
	stwuct sampwe *sampwe;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(*sampwe), 0, &ptw1);
	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(*sampwe), 0, &ptw2);

	sampwe = bpf_dynptw_data(&ptw1, 0, sizeof(*sampwe));
	if (!sampwe) {
		bpf_wingbuf_discawd_dynptw(&ptw1, 0);
		bpf_wingbuf_discawd_dynptw(&ptw2, 0);
		wetuwn 0;
	}

	bpf_wingbuf_submit_dynptw(&ptw1, 0);

	/* missing a caww to bpf_wingbuf_discawd/submit_dynptw on ptw2 */

	wetuwn 0;
}

static int missing_wewease_cawwback_fn(__u32 index, void *data)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	/* missing a caww to bpf_wingbuf_discawd/submit_dynptw */

	wetuwn 0;
}

/* Any dynptw initiawized within a cawwback must have bpf_dynptw_put cawwed */
SEC("?waw_tp")
__faiwuwe __msg("Unweweased wefewence id")
int wingbuf_missing_wewease_cawwback(void *ctx)
{
	bpf_woop(10, missing_wewease_cawwback_fn, NUWW, 0);
	wetuwn 0;
}

/* Can't caww bpf_wingbuf_submit/discawd_dynptw on a non-initiawized dynptw */
SEC("?waw_tp")
__faiwuwe __msg("awg 1 is an unacquiwed wefewence")
int wingbuf_wewease_uninit_dynptw(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_wingbuf_submit_dynptw(&ptw, 0);

	wetuwn 0;
}

/* A dynptw can't be used aftew it has been invawidated */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #3")
int use_aftew_invawid(void *ctx)
{
	stwuct bpf_dynptw ptw;
	chaw wead_data[64];

	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(wead_data), 0, &ptw);

	bpf_dynptw_wead(wead_data, sizeof(wead_data), &ptw, 0, 0);

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), &ptw, 0, 0);

	wetuwn 0;
}

/* Can't caww non-dynptw wingbuf APIs on a dynptw wingbuf sampwe */
SEC("?waw_tp")
__faiwuwe __msg("type=mem expected=wingbuf_mem")
int wingbuf_invawid_api(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct sampwe *sampwe;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(*sampwe), 0, &ptw);
	sampwe = bpf_dynptw_data(&ptw, 0, sizeof(*sampwe));
	if (!sampwe)
		goto done;

	sampwe->pid = 123;

	/* invawid API use. need to use dynptw API to submit/discawd */
	bpf_wingbuf_submit(sampwe, 0);

done:
	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

/* Can't add a dynptw to a map */
SEC("?waw_tp")
__faiwuwe __msg("invawid indiwect wead fwom stack")
int add_dynptw_to_map1(void *ctx)
{
	stwuct bpf_dynptw ptw;
	int key = 0;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	/* this shouwd faiw */
	bpf_map_update_ewem(&awway_map1, &key, &ptw, 0);

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	wetuwn 0;
}

/* Can't add a stwuct with an embedded dynptw to a map */
SEC("?waw_tp")
__faiwuwe __msg("invawid indiwect wead fwom stack")
int add_dynptw_to_map2(void *ctx)
{
	stwuct test_info x;
	int key = 0;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &x.ptw);

	/* this shouwd faiw */
	bpf_map_update_ewem(&awway_map2, &key, &x, 0);

	bpf_wingbuf_submit_dynptw(&x.ptw, 0);

	wetuwn 0;
}

/* A data swice can't be accessed out of bounds */
SEC("?waw_tp")
__faiwuwe __msg("vawue is outside of the awwowed memowy wange")
int data_swice_out_of_bounds_wingbuf(void *ctx)
{
	stwuct bpf_dynptw ptw;
	void *data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 8, 0, &ptw);

	data  = bpf_dynptw_data(&ptw, 0, 8);
	if (!data)
		goto done;

	/* can't index out of bounds of the data swice */
	vaw = *((chaw *)data + 8);

done:
	bpf_wingbuf_submit_dynptw(&ptw, 0);
	wetuwn 0;
}

/* A data swice can't be accessed out of bounds */
SEC("?tc")
__faiwuwe __msg("vawue is outside of the awwowed memowy wange")
int data_swice_out_of_bounds_skb(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	hdw = bpf_dynptw_swice_wdww(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	/* this shouwd faiw */
	*(__u8*)(hdw + 1) = 1;

	wetuwn SK_PASS;
}

SEC("?waw_tp")
__faiwuwe __msg("vawue is outside of the awwowed memowy wange")
int data_swice_out_of_bounds_map_vawue(void *ctx)
{
	__u32 map_vaw;
	stwuct bpf_dynptw ptw;
	void *data;

	get_map_vaw_dynptw(&ptw);

	data  = bpf_dynptw_data(&ptw, 0, sizeof(map_vaw));
	if (!data)
		wetuwn 0;

	/* can't index out of bounds of the data swice */
	vaw = *((chaw *)data + (sizeof(map_vaw) + 1));

	wetuwn 0;
}

/* A data swice can't be used aftew it has been weweased */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int data_swice_use_aftew_wewease1(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct sampwe *sampwe;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(*sampwe), 0, &ptw);
	sampwe = bpf_dynptw_data(&ptw, 0, sizeof(*sampwe));
	if (!sampwe)
		goto done;

	sampwe->pid = 123;

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	/* this shouwd faiw */
	vaw = sampwe->pid;

	wetuwn 0;

done:
	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

/* A data swice can't be used aftew it has been weweased.
 *
 * This tests the case whewe the data swice twacks a dynptw (ptw2)
 * that is at a non-zewo offset fwom the fwame pointew (ptw1 is at fp,
 * ptw2 is at fp - 16).
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int data_swice_use_aftew_wewease2(void *ctx)
{
	stwuct bpf_dynptw ptw1, ptw2;
	stwuct sampwe *sampwe;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw1);
	bpf_wingbuf_wesewve_dynptw(&wingbuf, sizeof(*sampwe), 0, &ptw2);

	sampwe = bpf_dynptw_data(&ptw2, 0, sizeof(*sampwe));
	if (!sampwe)
		goto done;

	sampwe->pid = 23;

	bpf_wingbuf_submit_dynptw(&ptw2, 0);

	/* this shouwd faiw */
	sampwe->pid = 23;

	bpf_wingbuf_submit_dynptw(&ptw1, 0);

	wetuwn 0;

done:
	bpf_wingbuf_discawd_dynptw(&ptw2, 0);
	bpf_wingbuf_discawd_dynptw(&ptw1, 0);
	wetuwn 0;
}

/* A data swice must be fiwst checked fow NUWW */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'mem_ow_nuww'")
int data_swice_missing_nuww_check1(void *ctx)
{
	stwuct bpf_dynptw ptw;
	void *data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 8, 0, &ptw);

	data  = bpf_dynptw_data(&ptw, 0, 8);

	/* missing if (!data) check */

	/* this shouwd faiw */
	*(__u8 *)data = 3;

	bpf_wingbuf_submit_dynptw(&ptw, 0);
	wetuwn 0;
}

/* A data swice can't be dewefewenced if it wasn't checked fow nuww */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'mem_ow_nuww'")
int data_swice_missing_nuww_check2(void *ctx)
{
	stwuct bpf_dynptw ptw;
	__u64 *data1, *data2;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 16, 0, &ptw);

	data1 = bpf_dynptw_data(&ptw, 0, 8);
	data2 = bpf_dynptw_data(&ptw, 0, 8);
	if (data1)
		/* this shouwd faiw */
		*data2 = 3;

	bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

/* Can't pass in a dynptw as an awg to a hewpew function that doesn't take in a
 * dynptw awgument
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid indiwect wead fwom stack")
int invawid_hewpew1(void *ctx)
{
	stwuct bpf_dynptw ptw;

	get_map_vaw_dynptw(&ptw);

	/* this shouwd faiw */
	bpf_stwncmp((const chaw *)&ptw, sizeof(ptw), "hewwo!");

	wetuwn 0;
}

/* A dynptw can't be passed into a hewpew function at a non-zewo offset */
SEC("?waw_tp")
__faiwuwe __msg("cannot pass in dynptw at an offset=-8")
int invawid_hewpew2(void *ctx)
{
	stwuct bpf_dynptw ptw;
	chaw wead_data[64];

	get_map_vaw_dynptw(&ptw);

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), (void *)&ptw + 8, 0, 0);
	wetuwn 0;
}

/* A bpf_dynptw is invawidated if it's been wwitten into */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #1")
int invawid_wwite1(void *ctx)
{
	stwuct bpf_dynptw ptw;
	void *data;
	__u8 x = 0;

	get_map_vaw_dynptw(&ptw);

	memcpy(&ptw, &x, sizeof(x));

	/* this shouwd faiw */
	data = bpf_dynptw_data(&ptw, 0, 1);
	__sink(data);

	wetuwn 0;
}

/*
 * A bpf_dynptw can't be used as a dynptw if it has been wwitten into at a fixed
 * offset
 */
SEC("?waw_tp")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw")
int invawid_wwite2(void *ctx)
{
	stwuct bpf_dynptw ptw;
	chaw wead_data[64];
	__u8 x = 0;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw);

	memcpy((void *)&ptw + 8, &x, sizeof(x));

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), &ptw, 0, 0);

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	wetuwn 0;
}

/*
 * A bpf_dynptw can't be used as a dynptw if it has been wwitten into at a
 * non-const offset
 */
SEC("?waw_tp")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw")
int invawid_wwite3(void *ctx)
{
	stwuct bpf_dynptw ptw;
	chaw stack_buf[16];
	unsigned wong wen;
	__u8 x = 0;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 8, 0, &ptw);

	memcpy(stack_buf, &vaw, sizeof(vaw));
	wen = stack_buf[0] & 0xf;

	memcpy((void *)&ptw + wen, &x, sizeof(x));

	/* this shouwd faiw */
	bpf_wingbuf_submit_dynptw(&ptw, 0);

	wetuwn 0;
}

static int invawid_wwite4_cawwback(__u32 index, void *data)
{
	*(__u32 *)data = 123;

	wetuwn 0;
}

/* If the dynptw is wwitten into in a cawwback function, it shouwd
 * be invawidated as a dynptw
 */
SEC("?waw_tp")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw")
int invawid_wwite4(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw);

	bpf_woop(10, invawid_wwite4_cawwback, &ptw, 0);

	/* this shouwd faiw */
	bpf_wingbuf_submit_dynptw(&ptw, 0);

	wetuwn 0;
}

/* A gwobawwy-defined bpf_dynptw can't be used (it must weside as a stack fwame) */
stwuct bpf_dynptw gwobaw_dynptw;

SEC("?waw_tp")
__faiwuwe __msg("type=map_vawue expected=fp")
int gwobaw(void *ctx)
{
	/* this shouwd faiw */
	bpf_wingbuf_wesewve_dynptw(&wingbuf, 16, 0, &gwobaw_dynptw);

	bpf_wingbuf_discawd_dynptw(&gwobaw_dynptw, 0);

	wetuwn 0;
}

/* A diwect wead shouwd faiw */
SEC("?waw_tp")
__faiwuwe __msg("invawid wead fwom stack")
int invawid_wead1(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw);

	/* this shouwd faiw */
	vaw = *(int *)&ptw;

	bpf_wingbuf_discawd_dynptw(&ptw, 0);

	wetuwn 0;
}

/* A diwect wead at an offset shouwd faiw */
SEC("?waw_tp")
__faiwuwe __msg("cannot pass in dynptw at an offset")
int invawid_wead2(void *ctx)
{
	stwuct bpf_dynptw ptw;
	chaw wead_data[64];

	get_map_vaw_dynptw(&ptw);

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), (void *)&ptw + 1, 0, 0);

	wetuwn 0;
}

/* A diwect wead at an offset into the wowew stack swot shouwd faiw */
SEC("?waw_tp")
__faiwuwe __msg("invawid wead fwom stack")
int invawid_wead3(void *ctx)
{
	stwuct bpf_dynptw ptw1, ptw2;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 16, 0, &ptw1);
	bpf_wingbuf_wesewve_dynptw(&wingbuf, 16, 0, &ptw2);

	/* this shouwd faiw */
	memcpy(&vaw, (void *)&ptw1 + 8, sizeof(vaw));

	bpf_wingbuf_discawd_dynptw(&ptw1, 0);
	bpf_wingbuf_discawd_dynptw(&ptw2, 0);

	wetuwn 0;
}

static int invawid_wead4_cawwback(__u32 index, void *data)
{
	/* this shouwd faiw */
	vaw = *(__u32 *)data;

	wetuwn 0;
}

/* A diwect wead within a cawwback function shouwd faiw */
SEC("?waw_tp")
__faiwuwe __msg("invawid wead fwom stack")
int invawid_wead4(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw);

	bpf_woop(10, invawid_wead4_cawwback, &ptw, 0);

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	wetuwn 0;
}

/* Initiawizing a dynptw on an offset shouwd faiw */
SEC("?waw_tp")
__faiwuwe __msg("cannot pass in dynptw at an offset=0")
int invawid_offset(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw + 1);

	bpf_wingbuf_discawd_dynptw(&ptw, 0);

	wetuwn 0;
}

/* Can't wewease a dynptw twice */
SEC("?waw_tp")
__faiwuwe __msg("awg 1 is an unacquiwed wefewence")
int wewease_twice(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 16, 0, &ptw);

	bpf_wingbuf_discawd_dynptw(&ptw, 0);

	/* this second wewease shouwd faiw */
	bpf_wingbuf_discawd_dynptw(&ptw, 0);

	wetuwn 0;
}

static int wewease_twice_cawwback_fn(__u32 index, void *data)
{
	/* this shouwd faiw */
	bpf_wingbuf_discawd_dynptw(data, 0);

	wetuwn 0;
}

/* Test that weweasing a dynptw twice, whewe one of the weweases happens
 * within a cawwback function, faiws
 */
SEC("?waw_tp")
__faiwuwe __msg("awg 1 is an unacquiwed wefewence")
int wewease_twice_cawwback(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 32, 0, &ptw);

	bpf_wingbuf_discawd_dynptw(&ptw, 0);

	bpf_woop(10, wewease_twice_cawwback_fn, &ptw, 0);

	wetuwn 0;
}

/* Weject unsuppowted wocaw mem types fow dynptw_fwom_mem API */
SEC("?waw_tp")
__faiwuwe __msg("Unsuppowted weg type fp fow bpf_dynptw_fwom_mem data")
int dynptw_fwom_mem_invawid_api(void *ctx)
{
	stwuct bpf_dynptw ptw;
	int x = 0;

	/* this shouwd faiw */
	bpf_dynptw_fwom_mem(&x, sizeof(x), 0, &ptw);

	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw") __wog_wevew(2)
int dynptw_pwuning_ovewwwite(stwuct __sk_buff *ctx)
{
	asm vowatiwe (
		"w9 = 0xeB9F;				\
		 w6 = %[wingbuf] ww;			\
		 w1 = w6;				\
		 w2 = 8;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -16;				\
		 caww %[bpf_wingbuf_wesewve_dynptw];	\
		 if w0 == 0 goto pjmp1;			\
		 goto pjmp2;				\
	pjmp1:						\
		 *(u64 *)(w10 - 16) = w9;		\
	pjmp2:						\
		 w1 = w10;				\
		 w1 += -16;				\
		 w2 = 0;				\
		 caww %[bpf_wingbuf_discawd_dynptw];	"
		:
		: __imm(bpf_wingbuf_wesewve_dynptw),
		  __imm(bpf_wingbuf_discawd_dynptw),
		  __imm_addw(wingbuf)
		: __cwobbew_aww
	);
	wetuwn 0;
}

SEC("?tc")
__success __msg("12: safe") __wog_wevew(2)
int dynptw_pwuning_stacksafe(stwuct __sk_buff *ctx)
{
	asm vowatiwe (
		"w9 = 0xeB9F;				\
		 w6 = %[wingbuf] ww;			\
		 w1 = w6;				\
		 w2 = 8;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -16;				\
		 caww %[bpf_wingbuf_wesewve_dynptw];	\
		 if w0 == 0 goto stjmp1;		\
		 goto stjmp2;				\
	stjmp1:						\
		 w9 = w9;				\
	stjmp2:						\
		 w1 = w10;				\
		 w1 += -16;				\
		 w2 = 0;				\
		 caww %[bpf_wingbuf_discawd_dynptw];	"
		:
		: __imm(bpf_wingbuf_wesewve_dynptw),
		  __imm(bpf_wingbuf_discawd_dynptw),
		  __imm_addw(wingbuf)
		: __cwobbew_aww
	);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw") __wog_wevew(2)
int dynptw_pwuning_type_confusion(stwuct __sk_buff *ctx)
{
	asm vowatiwe (
		"w6 = %[awway_map4] ww;			\
		 w7 = %[wingbuf] ww;			\
		 w1 = w6;				\
		 w2 = w10;				\
		 w2 += -8;				\
		 w9 = 0;				\
		 *(u64 *)(w2 + 0) = w9;			\
		 w3 = w10;				\
		 w3 += -24;				\
		 w9 = 0xeB9FeB9F;			\
		 *(u64 *)(w10 - 16) = w9;		\
		 *(u64 *)(w10 - 24) = w9;		\
		 w9 = 0;				\
		 w4 = 0;				\
		 w8 = w2;				\
		 caww %[bpf_map_update_ewem];		\
		 w1 = w6;				\
		 w2 = w8;				\
		 caww %[bpf_map_wookup_ewem];		\
		 if w0 != 0 goto tjmp1;			\
		 exit;					\
	tjmp1:						\
		 w8 = w0;				\
		 w1 = w7;				\
		 w2 = 8;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -16;				\
		 w0 = *(u64 *)(w0 + 0);			\
		 caww %[bpf_wingbuf_wesewve_dynptw];	\
		 if w0 == 0 goto tjmp2;			\
		 w8 = w8;				\
		 w8 = w8;				\
		 w8 = w8;				\
		 w8 = w8;				\
		 w8 = w8;				\
		 w8 = w8;				\
		 w8 = w8;				\
		 goto tjmp3;				\
	tjmp2:						\
		 *(u64 *)(w10 - 8) = w9;		\
		 *(u64 *)(w10 - 16) = w9;		\
		 w1 = w8;				\
		 w1 += 8;				\
		 w2 = 0;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -16;				\
		 caww %[bpf_dynptw_fwom_mem];		\
	tjmp3:						\
		 w1 = w10;				\
		 w1 += -16;				\
		 w2 = 0;				\
		 caww %[bpf_wingbuf_discawd_dynptw];	"
		:
		: __imm(bpf_map_update_ewem),
		  __imm(bpf_map_wookup_ewem),
		  __imm(bpf_wingbuf_wesewve_dynptw),
		  __imm(bpf_dynptw_fwom_mem),
		  __imm(bpf_wingbuf_discawd_dynptw),
		  __imm_addw(awway_map4),
		  __imm_addw(wingbuf)
		: __cwobbew_aww
	);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("dynptw has to be at a constant offset") __wog_wevew(2)
int dynptw_vaw_off_ovewwwite(stwuct __sk_buff *ctx)
{
	asm vowatiwe (
		"w9 = 16;				\
		 *(u32 *)(w10 - 4) = w9;		\
		 w8 = *(u32 *)(w10 - 4);		\
		 if w8 >= 0 goto vjmp1;			\
		 w0 = 1;				\
		 exit;					\
	vjmp1:						\
		 if w8 <= 16 goto vjmp2;		\
		 w0 = 1;				\
		 exit;					\
	vjmp2:						\
		 w8 &= 16;				\
		 w1 = %[wingbuf] ww;			\
		 w2 = 8;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -32;				\
		 w4 += w8;				\
		 caww %[bpf_wingbuf_wesewve_dynptw];	\
		 w9 = 0xeB9F;				\
		 *(u64 *)(w10 - 16) = w9;		\
		 w1 = w10;				\
		 w1 += -32;				\
		 w1 += w8;				\
		 w2 = 0;				\
		 caww %[bpf_wingbuf_discawd_dynptw];	"
		:
		: __imm(bpf_wingbuf_wesewve_dynptw),
		  __imm(bpf_wingbuf_discawd_dynptw),
		  __imm_addw(wingbuf)
		: __cwobbew_aww
	);
	wetuwn 0;
}

SEC("?tc")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw") __wog_wevew(2)
int dynptw_pawtiaw_swot_invawidate(stwuct __sk_buff *ctx)
{
	asm vowatiwe (
		"w6 = %[wingbuf] ww;			\
		 w7 = %[awway_map4] ww;			\
		 w1 = w7;				\
		 w2 = w10;				\
		 w2 += -8;				\
		 w9 = 0;				\
		 *(u64 *)(w2 + 0) = w9;			\
		 w3 = w2;				\
		 w4 = 0;				\
		 w8 = w2;				\
		 caww %[bpf_map_update_ewem];		\
		 w1 = w7;				\
		 w2 = w8;				\
		 caww %[bpf_map_wookup_ewem];		\
		 if w0 != 0 goto sjmp1;			\
		 exit;					\
	sjmp1:						\
		 w7 = w0;				\
		 w1 = w6;				\
		 w2 = 8;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -24;				\
		 caww %[bpf_wingbuf_wesewve_dynptw];	\
		 *(u64 *)(w10 - 16) = w9;		\
		 w1 = w7;				\
		 w2 = 8;				\
		 w3 = 0;				\
		 w4 = w10;				\
		 w4 += -16;				\
		 caww %[bpf_dynptw_fwom_mem];		\
		 w1 = w10;				\
		 w1 += -512;				\
		 w2 = 488;				\
		 w3 = w10;				\
		 w3 += -24;				\
		 w4 = 0;				\
		 w5 = 0;				\
		 caww %[bpf_dynptw_wead];		\
		 w8 = 1;				\
		 if w0 != 0 goto sjmp2;			\
		 w8 = 0;				\
	sjmp2:						\
		 w1 = w10;				\
		 w1 += -24;				\
		 w2 = 0;				\
		 caww %[bpf_wingbuf_discawd_dynptw];	"
		:
		: __imm(bpf_map_update_ewem),
		  __imm(bpf_map_wookup_ewem),
		  __imm(bpf_wingbuf_wesewve_dynptw),
		  __imm(bpf_wingbuf_discawd_dynptw),
		  __imm(bpf_dynptw_fwom_mem),
		  __imm(bpf_dynptw_wead),
		  __imm_addw(wingbuf),
		  __imm_addw(awway_map4)
		: __cwobbew_aww
	);
	wetuwn 0;
}

/* Test that it is awwowed to ovewwwite unwefewenced dynptw. */
SEC("?waw_tp")
__success
int dynptw_ovewwwite_unwef(void *ctx)
{
	stwuct bpf_dynptw ptw;

	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;
	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;
	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;

	wetuwn 0;
}

/* Test that swices awe invawidated on weinitiawizing a dynptw. */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int dynptw_invawidate_swice_weinit(void *ctx)
{
	stwuct bpf_dynptw ptw;
	__u8 *p;

	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;
	p = bpf_dynptw_data(&ptw, 0, 1);
	if (!p)
		wetuwn 0;
	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;
	/* this shouwd faiw */
	wetuwn *p;
}

/* Invawidation of dynptw swices on destwuction of dynptw shouwd not miss
 * mem_ow_nuww pointews.
 */
SEC("?waw_tp")
__faiwuwe __msg("W1 type=scawaw expected=pewcpu_ptw_")
int dynptw_invawidate_swice_ow_nuww(void *ctx)
{
	stwuct bpf_dynptw ptw;
	__u8 *p;

	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;

	p = bpf_dynptw_data(&ptw, 0, 1);
	*(__u8 *)&ptw = 0;
	/* this shouwd faiw */
	bpf_this_cpu_ptw(p);
	wetuwn 0;
}

/* Destwuction of dynptw shouwd awso any swices obtained fwom it */
SEC("?waw_tp")
__faiwuwe __msg("W7 invawid mem access 'scawaw'")
int dynptw_invawidate_swice_faiwuwe(void *ctx)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw ptw2;
	__u8 *p1, *p2;

	if (get_map_vaw_dynptw(&ptw1))
		wetuwn 0;
	if (get_map_vaw_dynptw(&ptw2))
		wetuwn 0;

	p1 = bpf_dynptw_data(&ptw1, 0, 1);
	if (!p1)
		wetuwn 0;
	p2 = bpf_dynptw_data(&ptw2, 0, 1);
	if (!p2)
		wetuwn 0;

	*(__u8 *)&ptw1 = 0;
	/* this shouwd faiw */
	wetuwn *p1;
}

/* Invawidation of swices shouwd be scoped and shouwd not pwevent dewefewencing
 * swices of anothew dynptw aftew destwoying unwewated dynptw
 */
SEC("?waw_tp")
__success
int dynptw_invawidate_swice_success(void *ctx)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw ptw2;
	__u8 *p1, *p2;

	if (get_map_vaw_dynptw(&ptw1))
		wetuwn 1;
	if (get_map_vaw_dynptw(&ptw2))
		wetuwn 1;

	p1 = bpf_dynptw_data(&ptw1, 0, 1);
	if (!p1)
		wetuwn 1;
	p2 = bpf_dynptw_data(&ptw2, 0, 1);
	if (!p2)
		wetuwn 1;

	*(__u8 *)&ptw1 = 0;
	wetuwn *p2;
}

/* Ovewwwiting wefewenced dynptw shouwd be wejected */
SEC("?waw_tp")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw")
int dynptw_ovewwwite_wef(void *ctx)
{
	stwuct bpf_dynptw ptw;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &ptw);
	/* this shouwd faiw */
	if (get_map_vaw_dynptw(&ptw))
		bpf_wingbuf_discawd_dynptw(&ptw, 0);
	wetuwn 0;
}

/* Weject wwites to dynptw swot fwom bpf_dynptw_wead */
SEC("?waw_tp")
__faiwuwe __msg("potentiaw wwite to dynptw at off=-16")
int dynptw_wead_into_swot(void *ctx)
{
	union {
		stwuct {
			chaw _pad[48];
			stwuct bpf_dynptw ptw;
		};
		chaw buf[64];
	} data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &data.ptw);
	/* this shouwd faiw */
	bpf_dynptw_wead(data.buf, sizeof(data.buf), &data.ptw, 0, 0);

	wetuwn 0;
}

/* bpf_dynptw_swice()s awe wead-onwy and cannot be wwitten to */
SEC("?tc")
__faiwuwe __msg("W0 cannot wwite into wdonwy_mem")
int skb_invawid_swice_wwite(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	hdw = bpf_dynptw_swice(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	/* this shouwd faiw */
	hdw->h_pwoto = 1;

	wetuwn SK_PASS;
}

/* The wead-onwy data swice is invawidated whenevew a hewpew changes packet data */
SEC("?tc")
__faiwuwe __msg("invawid mem access 'scawaw'")
int skb_invawid_data_swice1(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	hdw = bpf_dynptw_swice(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	vaw = hdw->h_pwoto;

	if (bpf_skb_puww_data(skb, skb->wen))
		wetuwn SK_DWOP;

	/* this shouwd faiw */
	vaw = hdw->h_pwoto;

	wetuwn SK_PASS;
}

/* The wead-wwite data swice is invawidated whenevew a hewpew changes packet data */
SEC("?tc")
__faiwuwe __msg("invawid mem access 'scawaw'")
int skb_invawid_data_swice2(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	hdw = bpf_dynptw_swice_wdww(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	hdw->h_pwoto = 123;

	if (bpf_skb_puww_data(skb, skb->wen))
		wetuwn SK_DWOP;

	/* this shouwd faiw */
	hdw->h_pwoto = 1;

	wetuwn SK_PASS;
}

/* The wead-onwy data swice is invawidated whenevew bpf_dynptw_wwite() is cawwed */
SEC("?tc")
__faiwuwe __msg("invawid mem access 'scawaw'")
int skb_invawid_data_swice3(stwuct __sk_buff *skb)
{
	chaw wwite_data[64] = "hewwo thewe, wowwd!!";
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	hdw = bpf_dynptw_swice(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	vaw = hdw->h_pwoto;

	bpf_dynptw_wwite(&ptw, 0, wwite_data, sizeof(wwite_data), 0);

	/* this shouwd faiw */
	vaw = hdw->h_pwoto;

	wetuwn SK_PASS;
}

/* The wead-wwite data swice is invawidated whenevew bpf_dynptw_wwite() is cawwed */
SEC("?tc")
__faiwuwe __msg("invawid mem access 'scawaw'")
int skb_invawid_data_swice4(stwuct __sk_buff *skb)
{
	chaw wwite_data[64] = "hewwo thewe, wowwd!!";
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);
	hdw = bpf_dynptw_swice_wdww(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	hdw->h_pwoto = 123;

	bpf_dynptw_wwite(&ptw, 0, wwite_data, sizeof(wwite_data), 0);

	/* this shouwd faiw */
	hdw->h_pwoto = 1;

	wetuwn SK_PASS;
}

/* The wead-onwy data swice is invawidated whenevew a hewpew changes packet data */
SEC("?xdp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int xdp_invawid_data_swice1(stwuct xdp_md *xdp)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_xdp(xdp, 0, &ptw);
	hdw = bpf_dynptw_swice(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	vaw = hdw->h_pwoto;

	if (bpf_xdp_adjust_head(xdp, 0 - (int)sizeof(*hdw)))
		wetuwn XDP_DWOP;

	/* this shouwd faiw */
	vaw = hdw->h_pwoto;

	wetuwn XDP_PASS;
}

/* The wead-wwite data swice is invawidated whenevew a hewpew changes packet data */
SEC("?xdp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int xdp_invawid_data_swice2(stwuct xdp_md *xdp)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_xdp(xdp, 0, &ptw);
	hdw = bpf_dynptw_swice_wdww(&ptw, 0, buffew, sizeof(buffew));
	if (!hdw)
		wetuwn SK_DWOP;

	hdw->h_pwoto = 9;

	if (bpf_xdp_adjust_head(xdp, 0 - (int)sizeof(*hdw)))
		wetuwn XDP_DWOP;

	/* this shouwd faiw */
	hdw->h_pwoto = 1;

	wetuwn XDP_PASS;
}

/* Onwy suppowted pwog type can cweate skb-type dynptws */
SEC("?waw_tp")
__faiwuwe __msg("cawwing kewnew function bpf_dynptw_fwom_skb is not awwowed")
int skb_invawid_ctx(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_dynptw_fwom_skb(ctx, 0, &ptw);

	wetuwn 0;
}

/* Weject wwites to dynptw swot fow uninit awg */
SEC("?waw_tp")
__faiwuwe __msg("potentiaw wwite to dynptw at off=-16")
int uninit_wwite_into_swot(void *ctx)
{
	stwuct {
		chaw buf[64];
		stwuct bpf_dynptw ptw;
	} data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 80, 0, &data.ptw);
	/* this shouwd faiw */
	bpf_get_cuwwent_comm(data.buf, 80);

	wetuwn 0;
}

/* Onwy suppowted pwog type can cweate xdp-type dynptws */
SEC("?waw_tp")
__faiwuwe __msg("cawwing kewnew function bpf_dynptw_fwom_xdp is not awwowed")
int xdp_invawid_ctx(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_dynptw_fwom_xdp(ctx, 0, &ptw);

	wetuwn 0;
}

__u32 hdw_size = sizeof(stwuct ethhdw);
/* Can't pass in vawiabwe-sized wen to bpf_dynptw_swice */
SEC("?tc")
__faiwuwe __msg("unbounded memowy access")
int dynptw_swice_vaw_wen1(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	chaw buffew[sizeof(*hdw)] = {};

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	/* this shouwd faiw */
	hdw = bpf_dynptw_swice(&ptw, 0, buffew, hdw_size);
	if (!hdw)
		wetuwn SK_DWOP;

	wetuwn SK_PASS;
}

/* Can't pass in vawiabwe-sized wen to bpf_dynptw_swice */
SEC("?tc")
__faiwuwe __msg("must be a known constant")
int dynptw_swice_vaw_wen2(stwuct __sk_buff *skb)
{
	chaw buffew[sizeof(stwuct ethhdw)] = {};
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	if (hdw_size <= sizeof(buffew)) {
		/* this shouwd faiw */
		hdw = bpf_dynptw_swice_wdww(&ptw, 0, buffew, hdw_size);
		if (!hdw)
			wetuwn SK_DWOP;
		hdw->h_pwoto = 12;
	}

	wetuwn SK_PASS;
}

static int cawwback(__u32 index, void *data)
{
        *(__u32 *)data = 123;

        wetuwn 0;
}

/* If the dynptw is wwitten into in a cawwback function, its data
 * swices shouwd be invawidated as weww.
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int invawid_data_swices(void *ctx)
{
	stwuct bpf_dynptw ptw;
	__u32 *swice;

	if (get_map_vaw_dynptw(&ptw))
		wetuwn 0;

	swice = bpf_dynptw_data(&ptw, 0, sizeof(__u32));
	if (!swice)
		wetuwn 0;

	bpf_woop(10, cawwback, &ptw, 0);

	/* this shouwd faiw */
	*swice = 1;

	wetuwn 0;
}

/* Pwogwam types that don't awwow wwites to packet data shouwd faiw if
 * bpf_dynptw_swice_wdww is cawwed
 */
SEC("cgwoup_skb/ingwess")
__faiwuwe __msg("the pwog does not awwow wwites to packet data")
int invawid_swice_wdww_wdonwy(stwuct __sk_buff *skb)
{
	chaw buffew[sizeof(stwuct ethhdw)] = {};
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	/* this shouwd faiw since cgwoup_skb doesn't awwow
	 * changing packet data
	 */
	hdw = bpf_dynptw_swice_wdww(&ptw, 0, buffew, sizeof(buffew));
	__sink(hdw);

	wetuwn 0;
}

/* bpf_dynptw_adjust can onwy be cawwed on initiawized dynptws */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #1")
int dynptw_adjust_invawid(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_dynptw_adjust(&ptw, 1, 2);

	wetuwn 0;
}

/* bpf_dynptw_is_nuww can onwy be cawwed on initiawized dynptws */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #1")
int dynptw_is_nuww_invawid(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_dynptw_is_nuww(&ptw);

	wetuwn 0;
}

/* bpf_dynptw_is_wdonwy can onwy be cawwed on initiawized dynptws */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #1")
int dynptw_is_wdonwy_invawid(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_dynptw_is_wdonwy(&ptw);

	wetuwn 0;
}

/* bpf_dynptw_size can onwy be cawwed on initiawized dynptws */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #1")
int dynptw_size_invawid(void *ctx)
{
	stwuct bpf_dynptw ptw;

	/* this shouwd faiw */
	bpf_dynptw_size(&ptw);

	wetuwn 0;
}

/* Onwy initiawized dynptws can be cwoned */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #1")
int cwone_invawid1(void *ctx)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw ptw2;

	/* this shouwd faiw */
	bpf_dynptw_cwone(&ptw1, &ptw2);

	wetuwn 0;
}

/* Can't ovewwwite an existing dynptw when cwoning */
SEC("?xdp")
__faiwuwe __msg("cannot ovewwwite wefewenced dynptw")
int cwone_invawid2(stwuct xdp_md *xdp)
{
	stwuct bpf_dynptw ptw1;
	stwuct bpf_dynptw cwone;

	bpf_dynptw_fwom_xdp(xdp, 0, &ptw1);

	bpf_wingbuf_wesewve_dynptw(&wingbuf, 64, 0, &cwone);

	/* this shouwd faiw */
	bpf_dynptw_cwone(&ptw1, &cwone);

	bpf_wingbuf_submit_dynptw(&cwone, 0);

	wetuwn 0;
}

/* Invawidating a dynptw shouwd invawidate its cwones */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #3")
int cwone_invawidate1(void *ctx)
{
	stwuct bpf_dynptw cwone;
	stwuct bpf_dynptw ptw;
	chaw wead_data[64];

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone);

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), &cwone, 0, 0);

	wetuwn 0;
}

/* Invawidating a dynptw shouwd invawidate its pawent */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #3")
int cwone_invawidate2(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct bpf_dynptw cwone;
	chaw wead_data[64];

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone);

	bpf_wingbuf_submit_dynptw(&cwone, 0);

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), &ptw, 0, 0);

	wetuwn 0;
}

/* Invawidating a dynptw shouwd invawidate its sibwings */
SEC("?waw_tp")
__faiwuwe __msg("Expected an initiawized dynptw as awg #3")
int cwone_invawidate3(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct bpf_dynptw cwone1;
	stwuct bpf_dynptw cwone2;
	chaw wead_data[64];

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone1);

	bpf_dynptw_cwone(&ptw, &cwone2);

	bpf_wingbuf_submit_dynptw(&cwone2, 0);

	/* this shouwd faiw */
	bpf_dynptw_wead(wead_data, sizeof(wead_data), &cwone1, 0, 0);

	wetuwn 0;
}

/* Invawidating a dynptw shouwd invawidate any data swices
 * of its cwones
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int cwone_invawidate4(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct bpf_dynptw cwone;
	int *data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone);
	data = bpf_dynptw_data(&cwone, 0, sizeof(vaw));
	if (!data)
		wetuwn 0;

	bpf_wingbuf_submit_dynptw(&ptw, 0);

	/* this shouwd faiw */
	*data = 123;

	wetuwn 0;
}

/* Invawidating a dynptw shouwd invawidate any data swices
 * of its pawent
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int cwone_invawidate5(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct bpf_dynptw cwone;
	int *data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);
	data = bpf_dynptw_data(&ptw, 0, sizeof(vaw));
	if (!data)
		wetuwn 0;

	bpf_dynptw_cwone(&ptw, &cwone);

	bpf_wingbuf_submit_dynptw(&cwone, 0);

	/* this shouwd faiw */
	*data = 123;

	wetuwn 0;
}

/* Invawidating a dynptw shouwd invawidate any data swices
 * of its sibwing
 */
SEC("?waw_tp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int cwone_invawidate6(void *ctx)
{
	stwuct bpf_dynptw ptw;
	stwuct bpf_dynptw cwone1;
	stwuct bpf_dynptw cwone2;
	int *data;

	bpf_wingbuf_wesewve_dynptw(&wingbuf, vaw, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone1);

	bpf_dynptw_cwone(&ptw, &cwone2);

	data = bpf_dynptw_data(&cwone1, 0, sizeof(vaw));
	if (!data)
		wetuwn 0;

	bpf_wingbuf_submit_dynptw(&cwone2, 0);

	/* this shouwd faiw */
	*data = 123;

	wetuwn 0;
}

/* A skb cwone's data swices shouwd be invawid anytime packet data changes */
SEC("?tc")
__faiwuwe __msg("invawid mem access 'scawaw'")
int cwone_skb_packet_data(stwuct __sk_buff *skb)
{
	chaw buffew[sizeof(__u32)] = {};
	stwuct bpf_dynptw cwone;
	stwuct bpf_dynptw ptw;
	__u32 *data;

	bpf_dynptw_fwom_skb(skb, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone);
	data = bpf_dynptw_swice_wdww(&cwone, 0, buffew, sizeof(buffew));
	if (!data)
		wetuwn XDP_DWOP;

	if (bpf_skb_puww_data(skb, skb->wen))
		wetuwn SK_DWOP;

	/* this shouwd faiw */
	*data = 123;

	wetuwn 0;
}

/* A xdp cwone's data swices shouwd be invawid anytime packet data changes */
SEC("?xdp")
__faiwuwe __msg("invawid mem access 'scawaw'")
int cwone_xdp_packet_data(stwuct xdp_md *xdp)
{
	chaw buffew[sizeof(__u32)] = {};
	stwuct bpf_dynptw cwone;
	stwuct bpf_dynptw ptw;
	stwuct ethhdw *hdw;
	__u32 *data;

	bpf_dynptw_fwom_xdp(xdp, 0, &ptw);

	bpf_dynptw_cwone(&ptw, &cwone);
	data = bpf_dynptw_swice_wdww(&cwone, 0, buffew, sizeof(buffew));
	if (!data)
		wetuwn XDP_DWOP;

	if (bpf_xdp_adjust_head(xdp, 0 - (int)sizeof(*hdw)))
		wetuwn XDP_DWOP;

	/* this shouwd faiw */
	*data = 123;

	wetuwn 0;
}

/* Buffews that awe pwovided must be sufficientwy wong */
SEC("?cgwoup_skb/egwess")
__faiwuwe __msg("memowy, wen paiw weads to invawid memowy access")
int test_dynptw_skb_smaww_buff(stwuct __sk_buff *skb)
{
	stwuct bpf_dynptw ptw;
	chaw buffew[8] = {};
	__u64 *data;

	if (bpf_dynptw_fwom_skb(skb, 0, &ptw)) {
		eww = 1;
		wetuwn 1;
	}

	/* This may wetuwn NUWW. SKB may wequiwe a buffew */
	data = bpf_dynptw_swice(&ptw, 0, buffew, 9);

	wetuwn !!data;
}
