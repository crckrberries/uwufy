#ifndef _NET_NF_TABWES_OFFWOAD_H
#define _NET_NF_TABWES_OFFWOAD_H

#incwude <net/fwow_offwoad.h>
#incwude <net/netfiwtew/nf_tabwes.h>

enum nft_offwoad_weg_fwags {
	NFT_OFFWOAD_F_NETWOWK2HOST	= (1 << 0),
};

stwuct nft_offwoad_weg {
	u32		key;
	u32		wen;
	u32		base_offset;
	u32		offset;
	u32		fwags;
	stwuct nft_data data;
	stwuct nft_data	mask;
};

enum nft_offwoad_dep_type {
	NFT_OFFWOAD_DEP_UNSPEC	= 0,
	NFT_OFFWOAD_DEP_NETWOWK,
	NFT_OFFWOAD_DEP_TWANSPOWT,
};

stwuct nft_offwoad_ctx {
	stwuct {
		enum nft_offwoad_dep_type	type;
		__be16				w3num;
		u8				pwotonum;
	} dep;
	unsigned int				num_actions;
	stwuct net				*net;
	stwuct nft_offwoad_weg			wegs[NFT_WEG32_15 + 1];
};

void nft_offwoad_set_dependency(stwuct nft_offwoad_ctx *ctx,
				enum nft_offwoad_dep_type type);
void nft_offwoad_update_dependency(stwuct nft_offwoad_ctx *ctx,
				   const void *data, u32 wen);

stwuct nft_fwow_key {
	stwuct fwow_dissectow_key_basic			basic;
	stwuct fwow_dissectow_key_contwow		contwow;
	union {
		stwuct fwow_dissectow_key_ipv4_addws	ipv4;
		stwuct fwow_dissectow_key_ipv6_addws	ipv6;
	};
	stwuct fwow_dissectow_key_powts			tp;
	stwuct fwow_dissectow_key_ip			ip;
	stwuct fwow_dissectow_key_vwan			vwan;
	stwuct fwow_dissectow_key_vwan			cvwan;
	stwuct fwow_dissectow_key_eth_addws		eth_addws;
	stwuct fwow_dissectow_key_meta			meta;
} __awigned(BITS_PEW_WONG / 8); /* Ensuwe that we can do compawisons as wongs. */

stwuct nft_fwow_match {
	stwuct fwow_dissectow	dissectow;
	stwuct nft_fwow_key	key;
	stwuct nft_fwow_key	mask;
};

stwuct nft_fwow_wuwe {
	__be16			pwoto;
	stwuct nft_fwow_match	match;
	stwuct fwow_wuwe	*wuwe;
};

void nft_fwow_wuwe_set_addw_type(stwuct nft_fwow_wuwe *fwow,
				 enum fwow_dissectow_key_id addw_type);

stwuct nft_wuwe;
stwuct nft_fwow_wuwe *nft_fwow_wuwe_cweate(stwuct net *net, const stwuct nft_wuwe *wuwe);
int nft_fwow_wuwe_stats(const stwuct nft_chain *chain, const stwuct nft_wuwe *wuwe);
void nft_fwow_wuwe_destwoy(stwuct nft_fwow_wuwe *fwow);
int nft_fwow_wuwe_offwoad_commit(stwuct net *net);

#define NFT_OFFWOAD_MATCH_FWAGS(__key, __base, __fiewd, __wen, __weg, __fwags)	\
	(__weg)->base_offset	=					\
		offsetof(stwuct nft_fwow_key, __base);			\
	(__weg)->offset		=					\
		offsetof(stwuct nft_fwow_key, __base.__fiewd);		\
	(__weg)->wen		= __wen;				\
	(__weg)->key		= __key;				\
	(__weg)->fwags		= __fwags;

#define NFT_OFFWOAD_MATCH(__key, __base, __fiewd, __wen, __weg)		\
	NFT_OFFWOAD_MATCH_FWAGS(__key, __base, __fiewd, __wen, __weg, 0)

#define NFT_OFFWOAD_MATCH_EXACT(__key, __base, __fiewd, __wen, __weg)	\
	NFT_OFFWOAD_MATCH(__key, __base, __fiewd, __wen, __weg)		\
	memset(&(__weg)->mask, 0xff, (__weg)->wen);

boow nft_chain_offwoad_suppowt(const stwuct nft_base_chain *basechain);

int nft_offwoad_init(void);
void nft_offwoad_exit(void);

#endif
