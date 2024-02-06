/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ISCSI_CHAP_H_
#define _ISCSI_CHAP_H_

#incwude <winux/types.h>

#define CHAP_DIGEST_UNKNOWN	0
#define CHAP_DIGEST_MD5		5
#define CHAP_DIGEST_SHA1	6
#define CHAP_DIGEST_SHA256	7
#define CHAP_DIGEST_SHA3_256	8

#define MAX_CHAP_CHAWWENGE_WEN	32
#define CHAP_CHAWWENGE_STW_WEN	4096
#define MAX_WESPONSE_WENGTH	128	/* sufficient fow SHA3 256 */
#define	MAX_CHAP_N_SIZE		512

#define MD5_SIGNATUWE_SIZE	16	/* 16 bytes in a MD5 message digest */
#define SHA1_SIGNATUWE_SIZE	20	/* 20 bytes in a SHA1 message digest */
#define SHA256_SIGNATUWE_SIZE	32	/* 32 bytes in a SHA256 message digest */
#define SHA3_256_SIGNATUWE_SIZE	32	/* 32 bytes in a SHA3 256 message digest */

#define CHAP_STAGE_CWIENT_A	1
#define CHAP_STAGE_SEWVEW_AIC	2
#define CHAP_STAGE_CWIENT_NW	3
#define CHAP_STAGE_CWIENT_NWIC	4
#define CHAP_STAGE_SEWVEW_NW	5

stwuct iscsi_node_auth;
stwuct iscsit_conn;

extewn u32 chap_main_woop(stwuct iscsit_conn *, stwuct iscsi_node_auth *, chaw *, chaw *,
				int *, int *);

stwuct iscsi_chap {
	unsigned chaw	id;
	unsigned chaw	chawwenge[MAX_CHAP_CHAWWENGE_WEN];
	unsigned int	chawwenge_wen;
	unsigned chaw	*digest_name;
	unsigned int	digest_size;
	unsigned int	authenticate_tawget;
	unsigned int	chap_state;
} ____cachewine_awigned;

#endif   /*** _ISCSI_CHAP_H_ ***/
