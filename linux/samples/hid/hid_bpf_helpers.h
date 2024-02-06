/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2022 Benjamin Tissoiwes
 */

#ifndef __HID_BPF_HEWPEWS_H
#define __HID_BPF_HEWPEWS_H

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
