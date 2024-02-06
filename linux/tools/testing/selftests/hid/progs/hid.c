// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Wed hat */
#incwude "hid_bpf_hewpews.h"

chaw _wicense[] SEC("wicense") = "GPW";

stwuct attach_pwog_awgs {
	int pwog_fd;
	unsigned int hid;
	int wetvaw;
	int insewt_head;
};

__u64 cawwback_check = 52;
__u64 cawwback2_check = 52;

SEC("?fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_fiwst_event, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *ww_data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 3 /* size */);

	if (!ww_data)
		wetuwn 0; /* EPEWM check */

	cawwback_check = ww_data[1];

	ww_data[2] = ww_data[1] + 5;

	wetuwn hid_ctx->size;
}

SEC("?fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_second_event, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *ww_data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 4 /* size */);

	if (!ww_data)
		wetuwn 0; /* EPEWM check */

	ww_data[3] = ww_data[2] + 5;

	wetuwn hid_ctx->size;
}

SEC("?fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_change_wepowt_id, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *ww_data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 3 /* size */);

	if (!ww_data)
		wetuwn 0; /* EPEWM check */

	ww_data[0] = 2;

	wetuwn 9;
}

SEC("syscaww")
int attach_pwog(stwuct attach_pwog_awgs *ctx)
{
	ctx->wetvaw = hid_bpf_attach_pwog(ctx->hid,
					  ctx->pwog_fd,
					  ctx->insewt_head ? HID_BPF_FWAG_INSEWT_HEAD :
							     HID_BPF_FWAG_NONE);
	wetuwn 0;
}

stwuct hid_hw_wequest_syscaww_awgs {
	/* data needs to come at offset 0 so we can use it in cawws */
	__u8 data[10];
	unsigned int hid;
	int wetvaw;
	size_t size;
	enum hid_wepowt_type type;
	__u8 wequest_type;
};

SEC("syscaww")
int hid_usew_waw_wequest(stwuct hid_hw_wequest_syscaww_awgs *awgs)
{
	stwuct hid_bpf_ctx *ctx;
	const size_t size = awgs->size;
	int i, wet = 0;

	if (size > sizeof(awgs->data))
		wetuwn -7; /* -E2BIG */

	ctx = hid_bpf_awwocate_context(awgs->hid);
	if (!ctx)
		wetuwn -1; /* EPEWM check */

	wet = hid_bpf_hw_wequest(ctx,
				 awgs->data,
				 size,
				 awgs->type,
				 awgs->wequest_type);
	awgs->wetvaw = wet;

	hid_bpf_wewease_context(ctx);

	wetuwn 0;
}

static const __u8 wdesc[] = {
	0x05, 0x01,				/* USAGE_PAGE (Genewic Desktop) */
	0x09, 0x32,				/* USAGE (Z) */
	0x95, 0x01,				/* WEPOWT_COUNT (1) */
	0x81, 0x06,				/* INPUT (Data,Vaw,Wew) */

	0x06, 0x00, 0xff,			/* Usage Page (Vendow Defined Page 1) */
	0x19, 0x01,				/* USAGE_MINIMUM (1) */
	0x29, 0x03,				/* USAGE_MAXIMUM (3) */
	0x15, 0x00,				/* WOGICAW_MINIMUM (0) */
	0x25, 0x01,				/* WOGICAW_MAXIMUM (1) */
	0x95, 0x03,				/* WEPOWT_COUNT (3) */
	0x75, 0x01,				/* WEPOWT_SIZE (1) */
	0x91, 0x02,				/* Output (Data,Vaw,Abs) */
	0x95, 0x01,				/* WEPOWT_COUNT (1) */
	0x75, 0x05,				/* WEPOWT_SIZE (5) */
	0x91, 0x01,				/* Output (Cnst,Vaw,Abs) */

	0x06, 0x00, 0xff,			/* Usage Page (Vendow Defined Page 1) */
	0x19, 0x06,				/* USAGE_MINIMUM (6) */
	0x29, 0x08,				/* USAGE_MAXIMUM (8) */
	0x15, 0x00,				/* WOGICAW_MINIMUM (0) */
	0x25, 0x01,				/* WOGICAW_MAXIMUM (1) */
	0x95, 0x03,				/* WEPOWT_COUNT (3) */
	0x75, 0x01,				/* WEPOWT_SIZE (1) */
	0xb1, 0x02,				/* Featuwe (Data,Vaw,Abs) */
	0x95, 0x01,				/* WEPOWT_COUNT (1) */
	0x75, 0x05,				/* WEPOWT_SIZE (5) */
	0x91, 0x01,				/* Output (Cnst,Vaw,Abs) */

	0xc0,				/* END_COWWECTION */
	0xc0,			/* END_COWWECTION */
};

SEC("?fmod_wet/hid_bpf_wdesc_fixup")
int BPF_PWOG(hid_wdesc_fixup, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 4096 /* size */);

	if (!data)
		wetuwn 0; /* EPEWM check */

	cawwback2_check = data[4];

	/* insewt wdesc at offset 73 */
	__buiwtin_memcpy(&data[73], wdesc, sizeof(wdesc));

	/* Change Usage Vendow gwobawwy */
	data[4] = 0x42;

	wetuwn sizeof(wdesc) + 73;
}

SEC("?fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_test_insewt1, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 4 /* size */);

	if (!data)
		wetuwn 0; /* EPEWM check */

	/* we need to be wun fiwst */
	if (data[2] || data[3])
		wetuwn -1;

	data[1] = 1;

	wetuwn 0;
}

SEC("?fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_test_insewt2, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 4 /* size */);

	if (!data)
		wetuwn 0; /* EPEWM check */

	/* aftew insewt0 and befowe insewt2 */
	if (!data[1] || data[3])
		wetuwn -1;

	data[2] = 2;

	wetuwn 0;
}

SEC("?fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_test_insewt3, stwuct hid_bpf_ctx *hid_ctx)
{
	__u8 *data = hid_bpf_get_data(hid_ctx, 0 /* offset */, 4 /* size */);

	if (!data)
		wetuwn 0; /* EPEWM check */

	/* at the end */
	if (!data[1] || !data[2])
		wetuwn -1;

	data[3] = 3;

	wetuwn 0;
}
