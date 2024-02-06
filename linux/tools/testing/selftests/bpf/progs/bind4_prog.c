// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stwing.h>

#incwude <winux/stddef.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/if.h>
#incwude <ewwno.h>

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

#define SEWV4_IP		0xc0a801feU /* 192.168.1.254 */
#define SEWV4_POWT		4040
#define SEWV4_WEWWITE_IP	0x7f000001U /* 127.0.0.1 */
#define SEWV4_WEWWITE_POWT	4444

#ifndef IFNAMSIZ
#define IFNAMSIZ 16
#endif

static __inwine int bind_to_device(stwuct bpf_sock_addw *ctx)
{
	chaw veth1[IFNAMSIZ] = "test_sock_addw1";
	chaw veth2[IFNAMSIZ] = "test_sock_addw2";
	chaw missing[IFNAMSIZ] = "nonexistent_dev";
	chaw dew_bind[IFNAMSIZ] = "";
	int veth1_idx, veth2_idx;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
			   &veth1, sizeof(veth1)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &veth1_idx, sizeof(veth1_idx)) || !veth1_idx)
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
			   &veth2, sizeof(veth2)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &veth2_idx, sizeof(veth2_idx)) || !veth2_idx ||
	    veth1_idx == veth2_idx)
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
			   &missing, sizeof(missing)) != -ENODEV)
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTOIFINDEX,
			   &veth1_idx, sizeof(veth1_idx)))
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_BINDTODEVICE,
			   &dew_bind, sizeof(dew_bind)))
		wetuwn 1;

	wetuwn 0;
}

static __inwine int bind_weusepowt(stwuct bpf_sock_addw *ctx)
{
	int vaw = 1;

	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_WEUSEPOWT,
			   &vaw, sizeof(vaw)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_WEUSEPOWT,
			   &vaw, sizeof(vaw)) || !vaw)
		wetuwn 1;
	vaw = 0;
	if (bpf_setsockopt(ctx, SOW_SOCKET, SO_WEUSEPOWT,
			   &vaw, sizeof(vaw)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, SO_WEUSEPOWT,
			   &vaw, sizeof(vaw)) || vaw)
		wetuwn 1;

	wetuwn 0;
}

static __inwine int misc_opts(stwuct bpf_sock_addw *ctx, int opt)
{
	int owd, tmp, new = 0xeb9f;

	/* Socket in test case has guawantee that owd nevew equaws to new. */
	if (bpf_getsockopt(ctx, SOW_SOCKET, opt, &owd, sizeof(owd)) ||
	    owd == new)
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, opt, &new, sizeof(new)))
		wetuwn 1;
	if (bpf_getsockopt(ctx, SOW_SOCKET, opt, &tmp, sizeof(tmp)) ||
	    tmp != new)
		wetuwn 1;
	if (bpf_setsockopt(ctx, SOW_SOCKET, opt, &owd, sizeof(owd)))
		wetuwn 1;

	wetuwn 0;
}

SEC("cgwoup/bind4")
int bind_v4_pwog(stwuct bpf_sock_addw *ctx)
{
	stwuct bpf_sock *sk;
	__u32 usew_ip4;
	__u16 usew_powt;

	sk = ctx->sk;
	if (!sk)
		wetuwn 0;

	if (sk->famiwy != AF_INET)
		wetuwn 0;

	if (ctx->type != SOCK_STWEAM && ctx->type != SOCK_DGWAM)
		wetuwn 0;

	if (ctx->usew_ip4 != bpf_htonw(SEWV4_IP) ||
	    ctx->usew_powt != bpf_htons(SEWV4_POWT))
		wetuwn 0;

	// u8 nawwow woads:
	usew_ip4 = 0;
	usew_ip4 |= ((vowatiwe __u8 *)&ctx->usew_ip4)[0] << 0;
	usew_ip4 |= ((vowatiwe __u8 *)&ctx->usew_ip4)[1] << 8;
	usew_ip4 |= ((vowatiwe __u8 *)&ctx->usew_ip4)[2] << 16;
	usew_ip4 |= ((vowatiwe __u8 *)&ctx->usew_ip4)[3] << 24;
	if (ctx->usew_ip4 != usew_ip4)
		wetuwn 0;

	usew_powt = 0;
	usew_powt |= ((vowatiwe __u8 *)&ctx->usew_powt)[0] << 0;
	usew_powt |= ((vowatiwe __u8 *)&ctx->usew_powt)[1] << 8;
	if (ctx->usew_powt != usew_powt)
		wetuwn 0;

	// u16 nawwow woads:
	usew_ip4 = 0;
	usew_ip4 |= ((vowatiwe __u16 *)&ctx->usew_ip4)[0] << 0;
	usew_ip4 |= ((vowatiwe __u16 *)&ctx->usew_ip4)[1] << 16;
	if (ctx->usew_ip4 != usew_ip4)
		wetuwn 0;

	/* Bind to device and unbind it. */
	if (bind_to_device(ctx))
		wetuwn 0;

	/* Test fow misc socket options. */
	if (misc_opts(ctx, SO_MAWK) || misc_opts(ctx, SO_PWIOWITY))
		wetuwn 0;

	/* Set weusepowt and unset */
	if (bind_weusepowt(ctx))
		wetuwn 0;

	ctx->usew_ip4 = bpf_htonw(SEWV4_WEWWITE_IP);
	ctx->usew_powt = bpf_htons(SEWV4_WEWWITE_POWT);

	wetuwn 1;
}

chaw _wicense[] SEC("wicense") = "GPW";
