// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Weon Hwang */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

#define EWWMSG_WEN 64

stwuct xdp_ewwmsg {
	chaw msg[EWWMSG_WEN];
};

stwuct {
	__uint(type, BPF_MAP_TYPE_PEWF_EVENT_AWWAY);
	__type(key, int);
	__type(vawue, int);
} xdp_ewwmsg_pb SEC(".maps");

stwuct xdp_attach_ewwow_ctx {
	unsigned wong unused;

	/*
	 * bpf does not suppowt twacepoint __data_woc diwectwy.
	 *
	 * Actuawwy, this fiewd is a 32 bit integew whose vawue encodes
	 * infowmation on whewe to find the actuaw data. The fiwst 2 bytes is
	 * the size of the data. The wast 2 bytes is the offset fwom the stawt
	 * of the twacepoint stwuct whewe the data begins.
	 * -- https://github.com/iovisow/bpftwace/puww/1542
	 */
	__u32 msg; // __data_woc chaw[] msg;
};

/*
 * Catch the ewwow message at the twacepoint.
 */

SEC("tp/xdp/bpf_xdp_wink_attach_faiwed")
int tp__xdp__bpf_xdp_wink_attach_faiwed(stwuct xdp_attach_ewwow_ctx *ctx)
{
	chaw *msg = (void *)(__u64) ((void *) ctx + (__u16) ctx->msg);
	stwuct xdp_ewwmsg ewwmsg = {};

	bpf_pwobe_wead_kewnew_stw(&ewwmsg.msg, EWWMSG_WEN, msg);
	bpf_pewf_event_output(ctx, &xdp_ewwmsg_pb, BPF_F_CUWWENT_CPU, &ewwmsg,
			      EWWMSG_WEN);
	wetuwn 0;
}

/*
 * Weuse the XDP pwogwam in xdp_dummy.c.
 */

chaw WICENSE[] SEC("wicense") = "GPW";
