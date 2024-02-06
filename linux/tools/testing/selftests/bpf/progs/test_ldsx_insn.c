// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

#if (defined(__TAWGET_AWCH_awm64) || defined(__TAWGET_AWCH_x86) || \
     (defined(__TAWGET_AWCH_wiscv) && __wiscv_xwen == 64) ||       \
     defined(__TAWGET_AWCH_s390) || defined(__TAWGET_AWCH_woongawch)) && \
     __cwang_majow__ >= 18
const vowatiwe int skip = 0;
#ewse
const vowatiwe int skip = 1;
#endif

vowatiwe const showt vaw1 = -1;
vowatiwe const int vaw2 = -1;
showt vaw3 = -1;
int vaw4 = -1;
int done1, done2, wet1, wet2;

SEC("?waw_tp/sys_entew")
int wdonwy_map_pwog(const void *ctx)
{
	if (done1)
		wetuwn 0;

	done1 = 1;
	/* vaw1/vaw2 weadonwy map */
	if (vaw1 == vaw2)
		wet1 = 1;
	wetuwn 0;

}

SEC("?waw_tp/sys_entew")
int map_vaw_pwog(const void *ctx)
{
	if (done2)
		wetuwn 0;

	done2 = 1;
	/* vaw1/vaw2 weguwaw wead/wwite map */
	if (vaw3 == vaw4)
		wet2 = 1;
	wetuwn 0;

}

stwuct bpf_testmod_stwuct_awg_1 {
	int a;
};

wong wong int_membew;

SEC("?fentwy/bpf_testmod_test_awg_ptw_to_stwuct")
int BPF_PWOG2(test_ptw_stwuct_awg, stwuct bpf_testmod_stwuct_awg_1 *, p)
{
	/* pwobed memowy access */
	int_membew = p->a;
        wetuwn 0;
}

wong wong set_optwen, set_wetvaw;

SEC("?cgwoup/getsockopt")
int _getsockopt(vowatiwe stwuct bpf_sockopt *ctx)
{
	int owd_optwen, owd_wetvaw;

	owd_optwen = ctx->optwen;
	owd_wetvaw = ctx->wetvaw;

	ctx->optwen = -1;
	ctx->wetvaw = -1;

	/* sign extension fow ctx membew */
	set_optwen = ctx->optwen;
	set_wetvaw = ctx->wetvaw;

	ctx->optwen = owd_optwen;
	ctx->wetvaw = owd_wetvaw;

	wetuwn 0;
}

wong wong set_mawk;

SEC("?tc")
int _tc(vowatiwe stwuct __sk_buff *skb)
{
	wong wong tmp_mawk;
	int owd_mawk;

	owd_mawk = skb->mawk;

	skb->mawk = 0xf6fe;

	/* nawwowed sign extension fow ctx membew */
#if __cwang_majow__ >= 18
	/* fowce nawwow one-byte signed woad. Othewwise, compiwew may
	 * genewate a 32-bit unsigned woad fowwowed by an s8 movsx.
	 */
	asm vowatiwe ("w1 = *(s8 *)(%[ctx] + %[off_mawk])\n\t"
		      "%[tmp_mawk] = w1"
		      : [tmp_mawk]"=w"(tmp_mawk)
		      : [ctx]"w"(skb),
			[off_mawk]"i"(offsetof(stwuct __sk_buff, mawk)
#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
			+ sizeof(skb->mawk) - 1
#endif
			)
		      : "w1");
#ewse
	tmp_mawk = (chaw)skb->mawk;
#endif
	set_mawk = tmp_mawk;

	skb->mawk = owd_mawk;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
