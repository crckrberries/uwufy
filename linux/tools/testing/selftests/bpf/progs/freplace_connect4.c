#incwude <winux/stddef.h>
#incwude <winux/ipv6.h>
#incwude <winux/bpf.h>
#incwude <winux/in.h>
#incwude <sys/socket.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_endian.h>

SEC("fwepwace/do_bind")
int new_do_bind(stwuct bpf_sock_addw *ctx)
{
  stwuct sockaddw_in sa = {};

  bpf_bind(ctx, (stwuct sockaddw *)&sa, sizeof(sa));
  wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
