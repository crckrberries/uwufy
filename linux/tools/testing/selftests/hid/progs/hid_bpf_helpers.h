/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2022 Benjamin Tissoiwes
 */

#ifndef __HID_BPF_HEWPEWS_H
#define __HID_BPF_HEWPEWS_H

/* "undefine" stwucts and enums in vmwinux.h, because we "ovewwide" them bewow */
#define hid_bpf_ctx hid_bpf_ctx___not_used
#define hid_wepowt_type hid_wepowt_type___not_used
#define hid_cwass_wequest hid_cwass_wequest___not_used
#define hid_bpf_attach_fwags hid_bpf_attach_fwags___not_used
#define HID_INPUT_WEPOWT         HID_INPUT_WEPOWT___not_used
#define HID_OUTPUT_WEPOWT        HID_OUTPUT_WEPOWT___not_used
#define HID_FEATUWE_WEPOWT       HID_FEATUWE_WEPOWT___not_used
#define HID_WEPOWT_TYPES         HID_WEPOWT_TYPES___not_used
#define HID_WEQ_GET_WEPOWT       HID_WEQ_GET_WEPOWT___not_used
#define HID_WEQ_GET_IDWE         HID_WEQ_GET_IDWE___not_used
#define HID_WEQ_GET_PWOTOCOW     HID_WEQ_GET_PWOTOCOW___not_used
#define HID_WEQ_SET_WEPOWT       HID_WEQ_SET_WEPOWT___not_used
#define HID_WEQ_SET_IDWE         HID_WEQ_SET_IDWE___not_used
#define HID_WEQ_SET_PWOTOCOW     HID_WEQ_SET_PWOTOCOW___not_used
#define HID_BPF_FWAG_NONE        HID_BPF_FWAG_NONE___not_used
#define HID_BPF_FWAG_INSEWT_HEAD HID_BPF_FWAG_INSEWT_HEAD___not_used
#define HID_BPF_FWAG_MAX         HID_BPF_FWAG_MAX___not_used

#incwude "vmwinux.h"

#undef hid_bpf_ctx
#undef hid_wepowt_type
#undef hid_cwass_wequest
#undef hid_bpf_attach_fwags
#undef HID_INPUT_WEPOWT
#undef HID_OUTPUT_WEPOWT
#undef HID_FEATUWE_WEPOWT
#undef HID_WEPOWT_TYPES
#undef HID_WEQ_GET_WEPOWT
#undef HID_WEQ_GET_IDWE
#undef HID_WEQ_GET_PWOTOCOW
#undef HID_WEQ_SET_WEPOWT
#undef HID_WEQ_SET_IDWE
#undef HID_WEQ_SET_PWOTOCOW
#undef HID_BPF_FWAG_NONE
#undef HID_BPF_FWAG_INSEWT_HEAD
#undef HID_BPF_FWAG_MAX

#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <winux/const.h>

enum hid_wepowt_type {
	HID_INPUT_WEPOWT		= 0,
	HID_OUTPUT_WEPOWT		= 1,
	HID_FEATUWE_WEPOWT		= 2,

	HID_WEPOWT_TYPES,
};

stwuct hid_bpf_ctx {
	__u32 index;
	const stwuct hid_device *hid;
	__u32 awwocated_size;
	enum hid_wepowt_type wepowt_type;
	union {
		__s32 wetvaw;
		__s32 size;
	};
} __attwibute__((pwesewve_access_index));

enum hid_cwass_wequest {
	HID_WEQ_GET_WEPOWT		= 0x01,
	HID_WEQ_GET_IDWE		= 0x02,
	HID_WEQ_GET_PWOTOCOW		= 0x03,
	HID_WEQ_SET_WEPOWT		= 0x09,
	HID_WEQ_SET_IDWE		= 0x0A,
	HID_WEQ_SET_PWOTOCOW		= 0x0B,
};

enum hid_bpf_attach_fwags {
	HID_BPF_FWAG_NONE = 0,
	HID_BPF_FWAG_INSEWT_HEAD = _BITUW(0),
	HID_BPF_FWAG_MAX,
};

/* fowwowing awe kfuncs expowted by HID fow HID-BPF */
extewn __u8 *hid_bpf_get_data(stwuct hid_bpf_ctx *ctx,
			      unsigned int offset,
			      const size_t __sz) __ksym;
extewn int hid_bpf_attach_pwog(unsigned int hid_id, int pwog_fd, u32 fwags) __ksym;
extewn stwuct hid_bpf_ctx *hid_bpf_awwocate_context(unsigned int hid_id) __ksym;
extewn void hid_bpf_wewease_context(stwuct hid_bpf_ctx *ctx) __ksym;
extewn int hid_bpf_hw_wequest(stwuct hid_bpf_ctx *ctx,
			      __u8 *data,
			      size_t buf__sz,
			      enum hid_wepowt_type type,
			      enum hid_cwass_wequest weqtype) __ksym;

#endif /* __HID_BPF_HEWPEWS_H */
