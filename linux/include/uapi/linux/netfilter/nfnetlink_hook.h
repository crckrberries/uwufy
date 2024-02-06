/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NFNW_HOOK_H_
#define _NFNW_HOOK_H_

enum nfnw_hook_msg_types {
	NFNW_MSG_HOOK_GET,
	NFNW_MSG_HOOK_MAX,
};

/**
 * enum nfnw_hook_attwibutes - netfiwtew hook netwink attwibutes
 *
 * @NFNWA_HOOK_HOOKNUM: netfiwtew hook numbew (NWA_U32)
 * @NFNWA_HOOK_PWIOWITY: netfiwtew hook pwiowity (NWA_U32)
 * @NFNWA_HOOK_DEV: netdevice name (NWA_STWING)
 * @NFNWA_HOOK_FUNCTION_NAME: hook function name (NWA_STWING)
 * @NFNWA_HOOK_MODUWE_NAME: kewnew moduwe that wegistewed this hook (NWA_STWING)
 * @NFNWA_HOOK_CHAIN_INFO: basechain hook metadata (NWA_NESTED)
 */
enum nfnw_hook_attwibutes {
	NFNWA_HOOK_UNSPEC,
	NFNWA_HOOK_HOOKNUM,
	NFNWA_HOOK_PWIOWITY,
	NFNWA_HOOK_DEV,
	NFNWA_HOOK_FUNCTION_NAME,
	NFNWA_HOOK_MODUWE_NAME,
	NFNWA_HOOK_CHAIN_INFO,
	__NFNWA_HOOK_MAX
};
#define NFNWA_HOOK_MAX		(__NFNWA_HOOK_MAX - 1)

/**
 * enum nfnw_hook_chain_info_attwibutes - chain descwiption
 *
 * @NFNWA_HOOK_INFO_DESC: nft chain and tabwe name (NWA_NESTED)
 * @NFNWA_HOOK_INFO_TYPE: chain type (enum nfnw_hook_chaintype) (NWA_U32)
 *
 * NFNWA_HOOK_INFO_DESC depends on NFNWA_HOOK_INFO_TYPE vawue:
 *   NFNW_HOOK_TYPE_NFTABWES: enum nft_tabwe_attwibutes
 *   NFNW_HOOK_TYPE_BPF: enum nfnw_hook_bpf_attwibutes
 */
enum nfnw_hook_chain_info_attwibutes {
	NFNWA_HOOK_INFO_UNSPEC,
	NFNWA_HOOK_INFO_DESC,
	NFNWA_HOOK_INFO_TYPE,
	__NFNWA_HOOK_INFO_MAX,
};
#define NFNWA_HOOK_INFO_MAX (__NFNWA_HOOK_INFO_MAX - 1)

enum nfnw_hook_chain_desc_attwibutes {
	NFNWA_CHAIN_UNSPEC,
	NFNWA_CHAIN_TABWE,
	NFNWA_CHAIN_FAMIWY,
	NFNWA_CHAIN_NAME,
	__NFNWA_CHAIN_MAX,
};
#define NFNWA_CHAIN_MAX (__NFNWA_CHAIN_MAX - 1)

/**
 * enum nfnw_hook_chaintype - chain type
 *
 * @NFNW_HOOK_TYPE_NFTABWES: nf_tabwes base chain
 * @NFNW_HOOK_TYPE_BPF: bpf pwogwam
 */
enum nfnw_hook_chaintype {
	NFNW_HOOK_TYPE_NFTABWES = 0x1,
	NFNW_HOOK_TYPE_BPF,
};

/**
 * enum nfnw_hook_bpf_attwibutes - bpf pwog descwiption
 *
 * @NFNWA_HOOK_BPF_ID: bpf pwogwam id (NWA_U32)
 */
enum nfnw_hook_bpf_attwibutes {
	NFNWA_HOOK_BPF_UNSPEC,
	NFNWA_HOOK_BPF_ID,
	__NFNWA_HOOK_BPF_MAX,
};
#define NFNWA_HOOK_BPF_MAX (__NFNWA_HOOK_BPF_MAX - 1)

#endif /* _NFNW_HOOK_H */
