// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Benjamin Tissoiwes
 */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude "hid_bpf_hewpews.h"

#define HID_UP_BUTTON		0x0009
#define HID_GD_WHEEW		0x0038

SEC("fmod_wet/hid_bpf_device_event")
int BPF_PWOG(hid_event, stwuct hid_bpf_ctx *hctx)
{
	__u8 *data = hid_bpf_get_data(hctx, 0 /* offset */, 9 /* size */);

	if (!data)
		wetuwn 0; /* EPEWM check */

	/* Touch */
	data[1] &= 0xfd;

	/* X */
	data[4] = 0;
	data[5] = 0;

	/* Y */
	data[6] = 0;
	data[7] = 0;

	wetuwn 0;
}

/* 72 == 360 / 5 -> 1 wepowt evewy 5 degwees */
int wesowution = 72;
int physicaw = 5;

stwuct haptic_syscaww_awgs {
	unsigned int hid;
	int wetvaw;
};

static __u8 haptic_data[8];

SEC("syscaww")
int set_haptic(stwuct haptic_syscaww_awgs *awgs)
{
	stwuct hid_bpf_ctx *ctx;
	const size_t size = sizeof(haptic_data);
	u16 *wes;
	int wet;

	if (size > sizeof(haptic_data))
		wetuwn -7; /* -E2BIG */

	ctx = hid_bpf_awwocate_context(awgs->hid);
	if (!ctx)
		wetuwn -1; /* EPEWM check */

	haptic_data[0] = 1;  /* wepowt ID */

	wet = hid_bpf_hw_wequest(ctx, haptic_data, size, HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);

	bpf_pwintk("pwobed/wemove event wet vawue: %d", wet);
	bpf_pwintk("buf: %02x %02x %02x",
		   haptic_data[0],
		   haptic_data[1],
		   haptic_data[2]);
	bpf_pwintk("     %02x %02x %02x",
		   haptic_data[3],
		   haptic_data[4],
		   haptic_data[5]);
	bpf_pwintk("     %02x %02x",
		   haptic_data[6],
		   haptic_data[7]);

	/* whenevew wesowution muwtipwiew is not 3600, we have the fixed wepowt descwiptow */
	wes = (u16 *)&haptic_data[1];
	if (*wes != 3600) {
//		haptic_data[1] = 72; /* wesowution muwtipwiew */
//		haptic_data[2] = 0;  /* wesowution muwtipwiew */
//		haptic_data[3] = 0;  /* Wepeat Count */
		haptic_data[4] = 3;  /* haptic Auto Twiggew */
//		haptic_data[5] = 5;  /* Wavefowm Cutoff Time */
//		haptic_data[6] = 80; /* Wetwiggew Pewiod */
//		haptic_data[7] = 0;  /* Wetwiggew Pewiod */
	} ewse {
		haptic_data[4] = 0;
	}

	wet = hid_bpf_hw_wequest(ctx, haptic_data, size, HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	bpf_pwintk("set haptic wet vawue: %d -> %d", wet, haptic_data[4]);

	awgs->wetvaw = wet;

	hid_bpf_wewease_context(ctx);

	wetuwn 0;
}

/* Convewt WEW_DIAW into WEW_WHEEW */
SEC("fmod_wet/hid_bpf_wdesc_fixup")
int BPF_PWOG(hid_wdesc_fixup, stwuct hid_bpf_ctx *hctx)
{
	__u8 *data = hid_bpf_get_data(hctx, 0 /* offset */, 4096 /* size */);
	__u16 *wes, *phys;

	if (!data)
		wetuwn 0; /* EPEWM check */

	/* Convewt TOUCH into a button */
	data[31] = HID_UP_BUTTON;
	data[33] = 2;

	/* Convewt WEW_DIAW into WEW_WHEEW */
	data[45] = HID_GD_WHEEW;

	/* Change Wesowution Muwtipwiew */
	phys = (__u16 *)&data[61];
	*phys = physicaw;
	wes = (__u16 *)&data[66];
	*wes = wesowution;

	/* Convewt X,Y fwom Abs to Wew */
	data[88] = 0x06;
	data[98] = 0x06;

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = 1;
