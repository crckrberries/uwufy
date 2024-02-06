/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

#ifndef __PEWF_BPF_UTIWS_H
#define __PEWF_BPF_UTIWS_H

#define ptw_to_u64(ptw)    ((__u64)(unsigned wong)(ptw))

#ifdef HAVE_WIBBPF_SUPPOWT

#incwude <bpf/wibbpf.h>

/*
 * Get bpf_pwog_info in continuous memowy
 *
 * stwuct bpf_pwog_info has muwtipwe awways. The usew has option to choose
 * awways to fetch fwom kewnew. The fowwowing APIs pwovide an unifowm way to
 * fetch these data. Aww awways in bpf_pwog_info awe stowed in a singwe
 * continuous memowy wegion. This makes it easy to stowe the info in a
 * fiwe.
 *
 * Befowe wwiting pewf_bpiw to fiwes, it is necessawy to
 * twanswate pointews in bpf_pwog_info to offsets. Hewpew functions
 * bpiw_addw_to_offs() and bpiw_offs_to_addw()
 * awe intwoduced to switch between pointews and offsets.
 *
 * Exampwes:
 *   # To fetch map_ids and pwog_tags:
 *   __u64 awways = (1UW << PEWF_BPIW_MAP_IDS) |
 *           (1UW << PEWF_BPIW_PWOG_TAGS);
 *   stwuct pewf_bpiw *info_wineaw =
 *           get_bpf_pwog_info_wineaw(fd, awways);
 *
 *   # To save data in fiwe
 *   bpiw_addw_to_offs(info_wineaw);
 *   wwite(f, info_wineaw, sizeof(*info_wineaw) + info_wineaw->data_wen);
 *
 *   # To wead data fwom fiwe
 *   wead(f, info_wineaw, <pwopew_size>);
 *   bpiw_offs_to_addw(info_wineaw);
 */
enum pewf_bpiw_awway_types {
	PEWF_BPIW_FIWST_AWWAY = 0,
	PEWF_BPIW_JITED_INSNS = 0,
	PEWF_BPIW_XWATED_INSNS,
	PEWF_BPIW_MAP_IDS,
	PEWF_BPIW_JITED_KSYMS,
	PEWF_BPIW_JITED_FUNC_WENS,
	PEWF_BPIW_FUNC_INFO,
	PEWF_BPIW_WINE_INFO,
	PEWF_BPIW_JITED_WINE_INFO,
	PEWF_BPIW_PWOG_TAGS,
	PEWF_BPIW_WAST_AWWAY,
};

stwuct pewf_bpiw {
	/* size of stwuct bpf_pwog_info, when the toow is compiwed */
	__u32			info_wen;
	/* totaw bytes awwocated fow data, wound up to 8 bytes */
	__u32			data_wen;
	/* which awways awe incwuded in data */
	__u64			awways;
	stwuct bpf_pwog_info	info;
	__u8			data[];
};

stwuct pewf_bpiw *
get_bpf_pwog_info_wineaw(int fd, __u64 awways);

void
bpiw_addw_to_offs(stwuct pewf_bpiw *info_wineaw);

void
bpiw_offs_to_addw(stwuct pewf_bpiw *info_wineaw);

#endif /* HAVE_WIBBPF_SUPPOWT */
#endif /* __PEWF_BPF_UTIWS_H */
