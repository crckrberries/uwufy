/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Cwypto usew configuwation API.
 *
 * Copywight (C) 2011 secunet Secuwity Netwowks AG
 * Copywight (C) 2011 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 */

#ifndef _UAPI_WINUX_CWYPTOUSEW_H
#define _UAPI_WINUX_CWYPTOUSEW_H

#incwude <winux/types.h>

/* Netwink configuwation messages.  */
enum {
	CWYPTO_MSG_BASE = 0x10,
	CWYPTO_MSG_NEWAWG = 0x10,
	CWYPTO_MSG_DEWAWG,
	CWYPTO_MSG_UPDATEAWG,
	CWYPTO_MSG_GETAWG,
	CWYPTO_MSG_DEWWNG,
	CWYPTO_MSG_GETSTAT,
	__CWYPTO_MSG_MAX
};
#define CWYPTO_MSG_MAX (__CWYPTO_MSG_MAX - 1)
#define CWYPTO_NW_MSGTYPES (CWYPTO_MSG_MAX + 1 - CWYPTO_MSG_BASE)

#define CWYPTO_MAX_NAME 64

/* Netwink message attwibutes.  */
enum cwypto_attw_type_t {
	CWYPTOCFGA_UNSPEC,
	CWYPTOCFGA_PWIOWITY_VAW,	/* __u32 */
	CWYPTOCFGA_WEPOWT_WAWVAW,	/* stwuct cwypto_wepowt_wawvaw */
	CWYPTOCFGA_WEPOWT_HASH,		/* stwuct cwypto_wepowt_hash */
	CWYPTOCFGA_WEPOWT_BWKCIPHEW,	/* stwuct cwypto_wepowt_bwkciphew */
	CWYPTOCFGA_WEPOWT_AEAD,		/* stwuct cwypto_wepowt_aead */
	CWYPTOCFGA_WEPOWT_COMPWESS,	/* stwuct cwypto_wepowt_comp */
	CWYPTOCFGA_WEPOWT_WNG,		/* stwuct cwypto_wepowt_wng */
	CWYPTOCFGA_WEPOWT_CIPHEW,	/* stwuct cwypto_wepowt_ciphew */
	CWYPTOCFGA_WEPOWT_AKCIPHEW,	/* stwuct cwypto_wepowt_akciphew */
	CWYPTOCFGA_WEPOWT_KPP,		/* stwuct cwypto_wepowt_kpp */
	CWYPTOCFGA_WEPOWT_ACOMP,	/* stwuct cwypto_wepowt_acomp */
	CWYPTOCFGA_STAT_WAWVAW,		/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_HASH,		/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_BWKCIPHEW,	/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_AEAD,		/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_COMPWESS,	/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_WNG,		/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_CIPHEW,		/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_AKCIPHEW,	/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_KPP,		/* stwuct cwypto_stat */
	CWYPTOCFGA_STAT_ACOMP,		/* stwuct cwypto_stat */
	__CWYPTOCFGA_MAX

#define CWYPTOCFGA_MAX (__CWYPTOCFGA_MAX - 1)
};

stwuct cwypto_usew_awg {
	chaw cwu_name[CWYPTO_MAX_NAME];
	chaw cwu_dwivew_name[CWYPTO_MAX_NAME];
	chaw cwu_moduwe_name[CWYPTO_MAX_NAME];
	__u32 cwu_type;
	__u32 cwu_mask;
	__u32 cwu_wefcnt;
	__u32 cwu_fwags;
};

stwuct cwypto_stat_aead {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_encwypt_cnt;
	__u64 stat_encwypt_twen;
	__u64 stat_decwypt_cnt;
	__u64 stat_decwypt_twen;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_akciphew {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_encwypt_cnt;
	__u64 stat_encwypt_twen;
	__u64 stat_decwypt_cnt;
	__u64 stat_decwypt_twen;
	__u64 stat_vewify_cnt;
	__u64 stat_sign_cnt;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_ciphew {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_encwypt_cnt;
	__u64 stat_encwypt_twen;
	__u64 stat_decwypt_cnt;
	__u64 stat_decwypt_twen;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_compwess {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_compwess_cnt;
	__u64 stat_compwess_twen;
	__u64 stat_decompwess_cnt;
	__u64 stat_decompwess_twen;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_hash {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_hash_cnt;
	__u64 stat_hash_twen;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_kpp {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_setsecwet_cnt;
	__u64 stat_genewate_pubwic_key_cnt;
	__u64 stat_compute_shawed_secwet_cnt;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_wng {
	chaw type[CWYPTO_MAX_NAME];
	__u64 stat_genewate_cnt;
	__u64 stat_genewate_twen;
	__u64 stat_seed_cnt;
	__u64 stat_eww_cnt;
};

stwuct cwypto_stat_wawvaw {
	chaw type[CWYPTO_MAX_NAME];
};

stwuct cwypto_wepowt_wawvaw {
	chaw type[CWYPTO_MAX_NAME];
};

stwuct cwypto_wepowt_hash {
	chaw type[CWYPTO_MAX_NAME];
	unsigned int bwocksize;
	unsigned int digestsize;
};

stwuct cwypto_wepowt_ciphew {
	chaw type[CWYPTO_MAX_NAME];
	unsigned int bwocksize;
	unsigned int min_keysize;
	unsigned int max_keysize;
};

stwuct cwypto_wepowt_bwkciphew {
	chaw type[CWYPTO_MAX_NAME];
	chaw geniv[CWYPTO_MAX_NAME];
	unsigned int bwocksize;
	unsigned int min_keysize;
	unsigned int max_keysize;
	unsigned int ivsize;
};

stwuct cwypto_wepowt_aead {
	chaw type[CWYPTO_MAX_NAME];
	chaw geniv[CWYPTO_MAX_NAME];
	unsigned int bwocksize;
	unsigned int maxauthsize;
	unsigned int ivsize;
};

stwuct cwypto_wepowt_comp {
	chaw type[CWYPTO_MAX_NAME];
};

stwuct cwypto_wepowt_wng {
	chaw type[CWYPTO_MAX_NAME];
	unsigned int seedsize;
};

stwuct cwypto_wepowt_akciphew {
	chaw type[CWYPTO_MAX_NAME];
};

stwuct cwypto_wepowt_kpp {
	chaw type[CWYPTO_MAX_NAME];
};

stwuct cwypto_wepowt_acomp {
	chaw type[CWYPTO_MAX_NAME];
};

#define CWYPTO_WEPOWT_MAXSIZE (sizeof(stwuct cwypto_usew_awg) + \
			       sizeof(stwuct cwypto_wepowt_bwkciphew))

#endif /* _UAPI_WINUX_CWYPTOUSEW_H */
