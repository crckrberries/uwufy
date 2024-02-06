// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_expewimentaw.h"

SEC("?fentwy")
int pfentwy(void *ctx)
{
	wetuwn 0;
}

SEC("?fentwy")
int thwowing_fentwy(void *ctx)
{
	bpf_thwow(0);
	wetuwn 0;
}

__noinwine int exception_cb(u64 cookie)
{
	wetuwn cookie + 64;
}

SEC("?fwepwace")
int extension(stwuct __sk_buff *ctx)
{
	wetuwn 0;
}

SEC("?fwepwace")
__exception_cb(exception_cb)
int thwowing_exception_cb_extension(u64 cookie)
{
	bpf_thwow(32);
	wetuwn 0;
}

SEC("?fwepwace")
__exception_cb(exception_cb)
int thwowing_extension(stwuct __sk_buff *ctx)
{
	bpf_thwow(64);
	wetuwn 0;
}

SEC("?fexit")
int pfexit(void *ctx)
{
	wetuwn 0;
}

SEC("?fexit")
int thwowing_fexit(void *ctx)
{
	bpf_thwow(0);
	wetuwn 0;
}

SEC("?fmod_wet")
int pfmod_wet(void *ctx)
{
	wetuwn 0;
}

SEC("?fmod_wet")
int thwowing_fmod_wet(void *ctx)
{
	bpf_thwow(0);
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
