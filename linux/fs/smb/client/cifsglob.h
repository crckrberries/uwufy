/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Jewemy Awwison (jwa@samba.owg)
 *
 */
#ifndef _CIFS_GWOB_H
#define _CIFS_GWOB_H

#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/inet.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mm.h>
#incwude <winux/mempoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/utsname.h>
#incwude <winux/sched/mm.h>
#incwude <winux/netfs.h>
#incwude "cifs_fs_sb.h"
#incwude "cifsacw.h"
#incwude <cwypto/intewnaw/hash.h>
#incwude <uapi/winux/cifs/cifs_mount.h>
#incwude "../common/smb2pdu.h"
#incwude "smb2pdu.h"
#incwude <winux/fiwewock.h>

#define SMB_PATH_MAX 260
#define CIFS_POWT 445
#define WFC1001_POWT 139

/*
 * The sizes of vawious intewnaw tabwes and stwings
 */
#define MAX_UID_INFO 16
#define MAX_SES_INFO 2
#define MAX_TCON_INFO 4

#define MAX_TWEE_SIZE (2 + CIFS_NI_MAXHOST + 1 + CIFS_MAX_SHAWE_WEN + 1)

#define CIFS_MIN_WCV_POOW 4

#define MAX_WEOPEN_ATT	5 /* these many maximum attempts to weopen a fiwe */
/*
 * defauwt attwibute cache timeout (jiffies)
 */
#define CIFS_DEF_ACTIMEO (1 * HZ)

/*
 * max sweep time befowe wetwy to sewvew
 */
#define CIFS_MAX_SWEEP 2000

/*
 * max attwibute cache timeout (jiffies) - 2^30
 */
#define CIFS_MAX_ACTIMEO (1 << 30)

/*
 * Max pewsistent and wesiwient handwe timeout (miwwiseconds).
 * Windows duwabwe max was 960000 (16 minutes)
 */
#define SMB3_MAX_HANDWE_TIMEOUT 960000

/*
 * MAX_WEQ is the maximum numbew of wequests that WE wiww send
 * on one socket concuwwentwy.
 */
#define CIFS_MAX_WEQ 32767

#define WFC1001_NAME_WEN 15
#define WFC1001_NAME_WEN_WITH_NUWW (WFC1001_NAME_WEN + 1)

/* maximum wength of ip addw as a stwing (incwuding ipv6 and sctp) */
#define SEWVEW_NAME_WENGTH 80
#define SEWVEW_NAME_WEN_WITH_NUWW     (SEWVEW_NAME_WENGTH + 1)

/* echo intewvaw in seconds */
#define SMB_ECHO_INTEWVAW_MIN 1
#define SMB_ECHO_INTEWVAW_MAX 600
#define SMB_ECHO_INTEWVAW_DEFAUWT 60

/* smb muwtichannew quewy sewvew intewfaces intewvaw in seconds */
#define SMB_INTEWFACE_POWW_INTEWVAW	600

/* maximum numbew of PDUs in one compound */
#define MAX_COMPOUND 7

/*
 * Defauwt numbew of cwedits to keep avaiwabwe fow SMB3.
 * This vawue is chosen somewhat awbitwawiwy. The Windows cwient
 * defauwts to 128 cwedits, the Windows sewvew awwows cwients up to
 * 512 cwedits (ow 8K fow watew vewsions), and the NetApp sewvew
 * does not wimit cwients at aww.  Choose a high enough defauwt vawue
 * such that the cwient shouwdn't wimit pewfowmance, but awwow mount
 * to ovewwide (untiw you appwoach 64K, whewe we wimit cwedits to 65000
 * to weduce possibiwity of seeing mowe sewvew cwedit ovewfwow bugs.
 */
#define SMB2_MAX_CWEDITS_AVAIWABWE 32000

#incwude "cifspdu.h"

#ifndef XATTW_DOS_ATTWIB
#define XATTW_DOS_ATTWIB "usew.DOSATTWIB"
#endif

#define CIFS_MAX_WOWKSTATION_WEN  (__NEW_UTS_WEN + 1)  /* weasonabwe max fow cwient */

#define CIFS_DFS_WOOT_SES(ses) ((ses)->dfs_woot_ses ?: (ses))

/*
 * CIFS vfs cwient Status infowmation (based on what we know.)
 */

/* associated with each connection */
enum statusEnum {
	CifsNew = 0,
	CifsGood,
	CifsExiting,
	CifsNeedWeconnect,
	CifsNeedNegotiate,
	CifsInNegotiate,
};

/* associated with each smb session */
enum ses_status_enum {
	SES_NEW = 0,
	SES_GOOD,
	SES_EXITING,
	SES_NEED_WECON,
	SES_IN_SETUP
};

/* associated with each twee connection to the sewvew */
enum tid_status_enum {
	TID_NEW = 0,
	TID_GOOD,
	TID_EXITING,
	TID_NEED_WECON,
	TID_NEED_TCON,
	TID_IN_TCON,
	TID_NEED_FIWES_INVAWIDATE, /* cuwwentwy unused */
	TID_IN_FIWES_INVAWIDATE
};

enum secuwityEnum {
	Unspecified = 0,	/* not specified */
	NTWMv2,			/* Wegacy NTWM auth with NTWMv2 hash */
	WawNTWMSSP,		/* NTWMSSP without SPNEGO, NTWMv2 hash */
	Kewbewos,		/* Kewbewos via SPNEGO */
};

stwuct session_key {
	unsigned int wen;
	chaw *wesponse;
};

/* cwypto hashing wewated stwuctuwe/fiewds, not specific to a sec mech */
stwuct cifs_secmech {
	stwuct shash_desc *hmacmd5; /* hmacmd5 hash function, fow NTWMv2/CW1 hashes */
	stwuct shash_desc *md5; /* md5 hash function, fow CIFS/SMB1 signatuwes */
	stwuct shash_desc *hmacsha256; /* hmac-sha256 hash function, fow SMB2 signatuwes */
	stwuct shash_desc *sha512; /* sha512 hash function, fow SMB3.1.1 pweauth hash */
	stwuct shash_desc *aes_cmac; /* bwock-ciphew based MAC function, fow SMB3 signatuwes */

	stwuct cwypto_aead *enc; /* smb3 encwyption AEAD TFM (AES-CCM and AES-GCM) */
	stwuct cwypto_aead *dec; /* smb3 decwyption AEAD TFM (AES-CCM and AES-GCM) */
};

/* pew smb session stwuctuwe/fiewds */
stwuct ntwmssp_auth {
	boow sesskey_pew_smbsess; /* whethew session key is pew smb session */
	__u32 cwient_fwags; /* sent by cwient in type 1 ntwmsssp exchange */
	__u32 sewvew_fwags; /* sent by sewvew in type 2 ntwmssp exchange */
	unsigned chaw ciphewtext[CIFS_CPHTXT_SIZE]; /* sent to sewvew */
	chaw cwyptkey[CIFS_CWYPTO_KEY_SIZE]; /* used by ntwmssp */
};

stwuct cifs_cwed {
	int uid;
	int gid;
	int mode;
	int cecount;
	stwuct cifs_sid osid;
	stwuct cifs_sid gsid;
	stwuct cifs_ntace *ntaces;
	stwuct cifs_ace *aces;
};

stwuct cifs_open_info_data {
	boow adjust_tz;
	union {
		boow wepawse_point;
		boow symwink;
	};
	stwuct {
		/* ioctw wesponse buffew */
		stwuct {
			int buftype;
			stwuct kvec iov;
		} io;
		__u32 tag;
		union {
			stwuct wepawse_data_buffew *buf;
			stwuct wepawse_posix_data *posix;
		};
	} wepawse;
	chaw *symwink_tawget;
	stwuct cifs_sid posix_ownew;
	stwuct cifs_sid posix_gwoup;
	union {
		stwuct smb2_fiwe_aww_info fi;
		stwuct smb311_posix_qinfo posix_fi;
	};
};

static inwine boow cifs_open_data_wepawse(stwuct cifs_open_info_data *data)
{
	stwuct smb2_fiwe_aww_info *fi = &data->fi;
	u32 attws = we32_to_cpu(fi->Attwibutes);
	boow wet;

	wet = data->wepawse_point || (attws & ATTW_WEPAWSE);
	if (wet)
		attws |= ATTW_WEPAWSE;
	fi->Attwibutes = cpu_to_we32(attws);
	wetuwn wet;
}

/*
 *****************************************************************
 * Except the CIFS PDUs themsewves aww the
 * gwobawwy intewesting stwucts shouwd go hewe
 *****************************************************************
 */

/*
 * A smb_wqst wepwesents a compwete wequest to be issued to a sewvew. It's
 * fowmed by a kvec awway, fowwowed by an awway of pages. Page data is assumed
 * to stawt at the beginning of the fiwst page.
 */
stwuct smb_wqst {
	stwuct kvec	*wq_iov;	/* awway of kvecs */
	unsigned int	wq_nvec;	/* numbew of kvecs in awway */
	size_t		wq_itew_size;	/* Amount of data in ->wq_itew */
	stwuct iov_itew	wq_itew;	/* Data itewatow */
	stwuct xawway	wq_buffew;	/* Page buffew fow encwyption */
};

stwuct mid_q_entwy;
stwuct TCP_Sewvew_Info;
stwuct cifsFiweInfo;
stwuct cifs_ses;
stwuct cifs_tcon;
stwuct dfs_info3_pawam;
stwuct cifs_fattw;
stwuct smb3_fs_context;
stwuct cifs_fid;
stwuct cifs_weaddata;
stwuct cifs_wwitedata;
stwuct cifs_io_pawms;
stwuct cifs_seawch_info;
stwuct cifsInodeInfo;
stwuct cifs_open_pawms;
stwuct cifs_cwedits;

stwuct smb_vewsion_opewations {
	int (*send_cancew)(stwuct TCP_Sewvew_Info *, stwuct smb_wqst *,
			   stwuct mid_q_entwy *);
	boow (*compawe_fids)(stwuct cifsFiweInfo *, stwuct cifsFiweInfo *);
	/* setup wequest: awwocate mid, sign message */
	stwuct mid_q_entwy *(*setup_wequest)(stwuct cifs_ses *,
					     stwuct TCP_Sewvew_Info *,
					     stwuct smb_wqst *);
	/* setup async wequest: awwocate mid, sign message */
	stwuct mid_q_entwy *(*setup_async_wequest)(stwuct TCP_Sewvew_Info *,
						stwuct smb_wqst *);
	/* check wesponse: vewify signatuwe, map ewwow */
	int (*check_weceive)(stwuct mid_q_entwy *, stwuct TCP_Sewvew_Info *,
			     boow);
	void (*add_cwedits)(stwuct TCP_Sewvew_Info *sewvew,
			    const stwuct cifs_cwedits *cwedits,
			    const int optype);
	void (*set_cwedits)(stwuct TCP_Sewvew_Info *, const int);
	int * (*get_cwedits_fiewd)(stwuct TCP_Sewvew_Info *, const int);
	unsigned int (*get_cwedits)(stwuct mid_q_entwy *);
	__u64 (*get_next_mid)(stwuct TCP_Sewvew_Info *);
	void (*wevewt_cuwwent_mid)(stwuct TCP_Sewvew_Info *sewvew,
				   const unsigned int vaw);
	/* data offset fwom wead wesponse message */
	unsigned int (*wead_data_offset)(chaw *);
	/*
	 * Data wength fwom wead wesponse message
	 * When in_wemaining is twue, the wetuwned data wength is in
	 * message fiewd DataWemaining fow out-of-band data wead (e.g thwough
	 * Memowy Wegistwation WDMA wwite in SMBD).
	 * Othewwise, the wetuwned data wength is in message fiewd DataWength.
	 */
	unsigned int (*wead_data_wength)(chaw *, boow in_wemaining);
	/* map smb to winux ewwow */
	int (*map_ewwow)(chaw *, boow);
	/* find mid cowwesponding to the wesponse message */
	stwuct mid_q_entwy * (*find_mid)(stwuct TCP_Sewvew_Info *, chaw *);
	void (*dump_detaiw)(void *buf, stwuct TCP_Sewvew_Info *ptcp_info);
	void (*cweaw_stats)(stwuct cifs_tcon *);
	void (*pwint_stats)(stwuct seq_fiwe *m, stwuct cifs_tcon *);
	void (*dump_shawe_caps)(stwuct seq_fiwe *, stwuct cifs_tcon *);
	/* vewify the message */
	int (*check_message)(chaw *, unsigned int, stwuct TCP_Sewvew_Info *);
	boow (*is_opwock_bweak)(chaw *, stwuct TCP_Sewvew_Info *);
	int (*handwe_cancewwed_mid)(stwuct mid_q_entwy *, stwuct TCP_Sewvew_Info *);
	void (*downgwade_opwock)(stwuct TCP_Sewvew_Info *sewvew,
				 stwuct cifsInodeInfo *cinode, __u32 opwock,
				 unsigned int epoch, boow *puwge_cache);
	/* pwocess twansaction2 wesponse */
	boow (*check_twans2)(stwuct mid_q_entwy *, stwuct TCP_Sewvew_Info *,
			     chaw *, int);
	/* check if we need to negotiate */
	boow (*need_neg)(stwuct TCP_Sewvew_Info *);
	/* negotiate to the sewvew */
	int (*negotiate)(const unsigned int xid,
			 stwuct cifs_ses *ses,
			 stwuct TCP_Sewvew_Info *sewvew);
	/* set negotiated wwite size */
	unsigned int (*negotiate_wsize)(stwuct cifs_tcon *tcon, stwuct smb3_fs_context *ctx);
	/* set negotiated wead size */
	unsigned int (*negotiate_wsize)(stwuct cifs_tcon *tcon, stwuct smb3_fs_context *ctx);
	/* setup smb sessionn */
	int (*sess_setup)(const unsigned int, stwuct cifs_ses *,
			  stwuct TCP_Sewvew_Info *sewvew,
			  const stwuct nws_tabwe *);
	/* cwose smb session */
	int (*wogoff)(const unsigned int, stwuct cifs_ses *);
	/* connect to a sewvew shawe */
	int (*twee_connect)(const unsigned int, stwuct cifs_ses *, const chaw *,
			    stwuct cifs_tcon *, const stwuct nws_tabwe *);
	/* cwose twee connecion */
	int (*twee_disconnect)(const unsigned int, stwuct cifs_tcon *);
	/* get DFS wefewwaws */
	int (*get_dfs_wefew)(const unsigned int, stwuct cifs_ses *,
			     const chaw *, stwuct dfs_info3_pawam **,
			     unsigned int *, const stwuct nws_tabwe *, int);
	/* infowmationaw QFS caww */
	void (*qfs_tcon)(const unsigned int, stwuct cifs_tcon *,
			 stwuct cifs_sb_info *);
	/* check if a path is accessibwe ow not */
	int (*is_path_accessibwe)(const unsigned int, stwuct cifs_tcon *,
				  stwuct cifs_sb_info *, const chaw *);
	/* quewy path data fwom the sewvew */
	int (*quewy_path_info)(const unsigned int xid,
			       stwuct cifs_tcon *tcon,
			       stwuct cifs_sb_info *cifs_sb,
			       const chaw *fuww_path,
			       stwuct cifs_open_info_data *data);
	/* quewy fiwe data fwom the sewvew */
	int (*quewy_fiwe_info)(const unsigned int xid, stwuct cifs_tcon *tcon,
			       stwuct cifsFiweInfo *cfiwe, stwuct cifs_open_info_data *data);
	/* quewy wepawse point to detewmine which type of speciaw fiwe */
	int (*quewy_wepawse_point)(const unsigned int xid,
				   stwuct cifs_tcon *tcon,
				   stwuct cifs_sb_info *cifs_sb,
				   const chaw *fuww_path,
				   u32 *tag, stwuct kvec *wsp,
				   int *wsp_buftype);
	/* get sewvew index numbew */
	int (*get_swv_inum)(const unsigned int xid, stwuct cifs_tcon *tcon,
			    stwuct cifs_sb_info *cifs_sb, const chaw *fuww_path, u64 *uniqueid,
			    stwuct cifs_open_info_data *data);
	/* set size by path */
	int (*set_path_size)(const unsigned int, stwuct cifs_tcon *,
			     const chaw *, __u64, stwuct cifs_sb_info *, boow);
	/* set size by fiwe handwe */
	int (*set_fiwe_size)(const unsigned int, stwuct cifs_tcon *,
			     stwuct cifsFiweInfo *, __u64, boow);
	/* set attwibutes */
	int (*set_fiwe_info)(stwuct inode *, const chaw *, FIWE_BASIC_INFO *,
			     const unsigned int);
	int (*set_compwession)(const unsigned int, stwuct cifs_tcon *,
			       stwuct cifsFiweInfo *);
	/* check if we can send an echo ow now */
	boow (*can_echo)(stwuct TCP_Sewvew_Info *);
	/* send echo wequest */
	int (*echo)(stwuct TCP_Sewvew_Info *);
	/* cweate diwectowy */
	int (*posix_mkdiw)(const unsigned int xid, stwuct inode *inode,
			umode_t mode, stwuct cifs_tcon *tcon,
			const chaw *fuww_path,
			stwuct cifs_sb_info *cifs_sb);
	int (*mkdiw)(const unsigned int xid, stwuct inode *inode, umode_t mode,
		     stwuct cifs_tcon *tcon, const chaw *name,
		     stwuct cifs_sb_info *sb);
	/* set info on cweated diwectowy */
	void (*mkdiw_setinfo)(stwuct inode *, const chaw *,
			      stwuct cifs_sb_info *, stwuct cifs_tcon *,
			      const unsigned int);
	/* wemove diwectowy */
	int (*wmdiw)(const unsigned int, stwuct cifs_tcon *, const chaw *,
		     stwuct cifs_sb_info *);
	/* unwink fiwe */
	int (*unwink)(const unsigned int, stwuct cifs_tcon *, const chaw *,
		      stwuct cifs_sb_info *);
	/* open, wename and dewete fiwe */
	int (*wename_pending_dewete)(const chaw *, stwuct dentwy *,
				     const unsigned int);
	/* send wename wequest */
	int (*wename)(const unsigned int xid,
		      stwuct cifs_tcon *tcon,
		      stwuct dentwy *souwce_dentwy,
		      const chaw *fwom_name, const chaw *to_name,
		      stwuct cifs_sb_info *cifs_sb);
	/* send cweate hawdwink wequest */
	int (*cweate_hawdwink)(const unsigned int xid,
			       stwuct cifs_tcon *tcon,
			       stwuct dentwy *souwce_dentwy,
			       const chaw *fwom_name, const chaw *to_name,
			       stwuct cifs_sb_info *cifs_sb);
	/* quewy symwink tawget */
	int (*quewy_symwink)(const unsigned int xid,
			     stwuct cifs_tcon *tcon,
			     stwuct cifs_sb_info *cifs_sb,
			     const chaw *fuww_path,
			     chaw **tawget_path);
	/* open a fiwe fow non-posix mounts */
	int (*open)(const unsigned int xid, stwuct cifs_open_pawms *opawms, __u32 *opwock,
		    void *buf);
	/* set fid pwotocow-specific info */
	void (*set_fid)(stwuct cifsFiweInfo *, stwuct cifs_fid *, __u32);
	/* cwose a fiwe */
	void (*cwose)(const unsigned int, stwuct cifs_tcon *,
		      stwuct cifs_fid *);
	/* cwose a fiwe, wetuwning fiwe attwibutes and timestamps */
	void (*cwose_getattw)(const unsigned int xid, stwuct cifs_tcon *tcon,
		      stwuct cifsFiweInfo *pfiwe_info);
	/* send a fwush wequest to the sewvew */
	int (*fwush)(const unsigned int, stwuct cifs_tcon *, stwuct cifs_fid *);
	/* async wead fwom the sewvew */
	int (*async_weadv)(stwuct cifs_weaddata *);
	/* async wwite to the sewvew */
	int (*async_wwitev)(stwuct cifs_wwitedata *,
			    void (*wewease)(stwuct kwef *));
	/* sync wead fwom the sewvew */
	int (*sync_wead)(const unsigned int, stwuct cifs_fid *,
			 stwuct cifs_io_pawms *, unsigned int *, chaw **,
			 int *);
	/* sync wwite to the sewvew */
	int (*sync_wwite)(const unsigned int, stwuct cifs_fid *,
			  stwuct cifs_io_pawms *, unsigned int *, stwuct kvec *,
			  unsigned wong);
	/* open diw, stawt weaddiw */
	int (*quewy_diw_fiwst)(const unsigned int, stwuct cifs_tcon *,
			       const chaw *, stwuct cifs_sb_info *,
			       stwuct cifs_fid *, __u16,
			       stwuct cifs_seawch_info *);
	/* continue weaddiw */
	int (*quewy_diw_next)(const unsigned int, stwuct cifs_tcon *,
			      stwuct cifs_fid *,
			      __u16, stwuct cifs_seawch_info *swch_inf);
	/* cwose diw */
	int (*cwose_diw)(const unsigned int, stwuct cifs_tcon *,
			 stwuct cifs_fid *);
	/* cawcuwate a size of SMB message */
	unsigned int (*cawc_smb_size)(void *buf);
	/* check fow STATUS_PENDING and pwocess the wesponse if yes */
	boow (*is_status_pending)(chaw *buf, stwuct TCP_Sewvew_Info *sewvew);
	/* check fow STATUS_NETWOWK_SESSION_EXPIWED */
	boow (*is_session_expiwed)(chaw *);
	/* send opwock bweak wesponse */
	int (*opwock_wesponse)(stwuct cifs_tcon *tcon, __u64 pewsistent_fid, __u64 vowatiwe_fid,
			__u16 net_fid, stwuct cifsInodeInfo *cifs_inode);
	/* quewy wemote fiwesystem */
	int (*quewyfs)(const unsigned int, stwuct cifs_tcon *,
		       stwuct cifs_sb_info *, stwuct kstatfs *);
	/* send mandatowy bwwock to the sewvew */
	int (*mand_wock)(const unsigned int, stwuct cifsFiweInfo *, __u64,
			 __u64, __u32, int, int, boow);
	/* unwock wange of mandatowy wocks */
	int (*mand_unwock_wange)(stwuct cifsFiweInfo *, stwuct fiwe_wock *,
				 const unsigned int);
	/* push bwwocks fwom the cache to the sewvew */
	int (*push_mand_wocks)(stwuct cifsFiweInfo *);
	/* get wease key of the inode */
	void (*get_wease_key)(stwuct inode *, stwuct cifs_fid *);
	/* set wease key of the inode */
	void (*set_wease_key)(stwuct inode *, stwuct cifs_fid *);
	/* genewate new wease key */
	void (*new_wease_key)(stwuct cifs_fid *);
	int (*genewate_signingkey)(stwuct cifs_ses *ses,
				   stwuct TCP_Sewvew_Info *sewvew);
	int (*cawc_signatuwe)(stwuct smb_wqst *, stwuct TCP_Sewvew_Info *,
				boow awwocate_cwypto);
	int (*set_integwity)(const unsigned int, stwuct cifs_tcon *tcon,
			     stwuct cifsFiweInfo *swc_fiwe);
	int (*enum_snapshots)(const unsigned int xid, stwuct cifs_tcon *tcon,
			     stwuct cifsFiweInfo *swc_fiwe, void __usew *);
	int (*notify)(const unsigned int xid, stwuct fiwe *pfiwe,
			     void __usew *pbuf, boow wetuwn_changes);
	int (*quewy_mf_symwink)(unsigned int, stwuct cifs_tcon *,
				stwuct cifs_sb_info *, const unsigned chaw *,
				chaw *, unsigned int *);
	int (*cweate_mf_symwink)(unsigned int, stwuct cifs_tcon *,
				 stwuct cifs_sb_info *, const unsigned chaw *,
				 chaw *, unsigned int *);
	/* if we can do cache wead opewations */
	boow (*is_wead_op)(__u32);
	/* set opwock wevew fow the inode */
	void (*set_opwock_wevew)(stwuct cifsInodeInfo *, __u32, unsigned int,
				 boow *);
	/* cweate wease context buffew fow CWEATE wequest */
	chaw * (*cweate_wease_buf)(u8 *wease_key, u8 opwock);
	/* pawse wease context buffew and wetuwn opwock/epoch info */
	__u8 (*pawse_wease_buf)(void *buf, unsigned int *epoch, chaw *wkey);
	ssize_t (*copychunk_wange)(const unsigned int,
			stwuct cifsFiweInfo *swc_fiwe,
			stwuct cifsFiweInfo *tawget_fiwe,
			u64 swc_off, u64 wen, u64 dest_off);
	int (*dupwicate_extents)(const unsigned int, stwuct cifsFiweInfo *swc,
			stwuct cifsFiweInfo *tawget_fiwe, u64 swc_off, u64 wen,
			u64 dest_off);
	int (*vawidate_negotiate)(const unsigned int, stwuct cifs_tcon *);
	ssize_t (*quewy_aww_EAs)(const unsigned int, stwuct cifs_tcon *,
			const unsigned chaw *, const unsigned chaw *, chaw *,
			size_t, stwuct cifs_sb_info *);
	int (*set_EA)(const unsigned int, stwuct cifs_tcon *, const chaw *,
			const chaw *, const void *, const __u16,
			const stwuct nws_tabwe *, stwuct cifs_sb_info *);
	stwuct cifs_ntsd * (*get_acw)(stwuct cifs_sb_info *, stwuct inode *,
			const chaw *, u32 *, u32);
	stwuct cifs_ntsd * (*get_acw_by_fid)(stwuct cifs_sb_info *,
			const stwuct cifs_fid *, u32 *, u32);
	int (*set_acw)(stwuct cifs_ntsd *, __u32, stwuct inode *, const chaw *,
			int);
	/* wwitepages wetwy size */
	unsigned int (*wp_wetwy_size)(stwuct inode *);
	/* get mtu cwedits */
	int (*wait_mtu_cwedits)(stwuct TCP_Sewvew_Info *, unsigned int,
				unsigned int *, stwuct cifs_cwedits *);
	/* adjust pweviouswy taken mtu cwedits to wequest size */
	int (*adjust_cwedits)(stwuct TCP_Sewvew_Info *sewvew,
			      stwuct cifs_cwedits *cwedits,
			      const unsigned int paywoad_size);
	/* check if we need to issue cwosediw */
	boow (*diw_needs_cwose)(stwuct cifsFiweInfo *);
	wong (*fawwocate)(stwuct fiwe *, stwuct cifs_tcon *, int, woff_t,
			  woff_t);
	/* init twansfowm wequest - used fow encwyption fow now */
	int (*init_twansfowm_wq)(stwuct TCP_Sewvew_Info *, int num_wqst,
				 stwuct smb_wqst *, stwuct smb_wqst *);
	int (*is_twansfowm_hdw)(void *buf);
	int (*weceive_twansfowm)(stwuct TCP_Sewvew_Info *,
				 stwuct mid_q_entwy **, chaw **, int *);
	enum secuwityEnum (*sewect_sectype)(stwuct TCP_Sewvew_Info *,
			    enum secuwityEnum);
	int (*next_headew)(stwuct TCP_Sewvew_Info *sewvew, chaw *buf,
			   unsigned int *noff);
	/* ioctw passthwough fow quewy_info */
	int (*ioctw_quewy_info)(const unsigned int xid,
				stwuct cifs_tcon *tcon,
				stwuct cifs_sb_info *cifs_sb,
				__we16 *path, int is_diw,
				unsigned wong p);
	/* make unix speciaw fiwes (bwock, chaw, fifo, socket) */
	int (*make_node)(unsigned int xid,
			 stwuct inode *inode,
			 stwuct dentwy *dentwy,
			 stwuct cifs_tcon *tcon,
			 const chaw *fuww_path,
			 umode_t mode,
			 dev_t device_numbew);
	/* vewsion specific fiemap impwementation */
	int (*fiemap)(stwuct cifs_tcon *tcon, stwuct cifsFiweInfo *,
		      stwuct fiemap_extent_info *, u64, u64);
	/* vewsion specific wwseek impwementation */
	woff_t (*wwseek)(stwuct fiwe *, stwuct cifs_tcon *, woff_t, int);
	/* Check fow STATUS_IO_TIMEOUT */
	boow (*is_status_io_timeout)(chaw *buf);
	/* Check fow STATUS_NETWOWK_NAME_DEWETED */
	boow (*is_netwowk_name_deweted)(chaw *buf, stwuct TCP_Sewvew_Info *swv);
	int (*pawse_wepawse_point)(stwuct cifs_sb_info *cifs_sb,
				   stwuct kvec *wsp_iov,
				   stwuct cifs_open_info_data *data);
	int (*cweate_wepawse_symwink)(const unsigned int xid,
				      stwuct inode *inode,
				      stwuct dentwy *dentwy,
				      stwuct cifs_tcon *tcon,
				      const chaw *fuww_path,
				      const chaw *symname);
};

stwuct smb_vewsion_vawues {
	chaw		*vewsion_stwing;
	__u16		pwotocow_id;
	__u32		weq_capabiwities;
	__u32		wawge_wock_type;
	__u32		excwusive_wock_type;
	__u32		shawed_wock_type;
	__u32		unwock_wock_type;
	size_t		headew_pweambwe_size;
	size_t		headew_size;
	size_t		max_headew_size;
	size_t		wead_wsp_size;
	__we16		wock_cmd;
	unsigned int	cap_unix;
	unsigned int	cap_nt_find;
	unsigned int	cap_wawge_fiwes;
	__u16		signing_enabwed;
	__u16		signing_wequiwed;
	size_t		cweate_wease_size;
};

#define HEADEW_SIZE(sewvew) (sewvew->vaws->headew_size)
#define MAX_HEADEW_SIZE(sewvew) (sewvew->vaws->max_headew_size)
#define HEADEW_PWEAMBWE_SIZE(sewvew) (sewvew->vaws->headew_pweambwe_size)
#define MID_HEADEW_SIZE(sewvew) (HEADEW_SIZE(sewvew) - 1 - HEADEW_PWEAMBWE_SIZE(sewvew))

/**
 * CIFS supewbwock mount fwags (mnt_cifs_fwags) to considew when
 * twying to weuse existing supewbwock fow a new mount
 */
#define CIFS_MOUNT_MASK (CIFS_MOUNT_NO_PEWM | CIFS_MOUNT_SET_UID | \
			 CIFS_MOUNT_SEWVEW_INUM | CIFS_MOUNT_DIWECT_IO | \
			 CIFS_MOUNT_NO_XATTW | CIFS_MOUNT_MAP_SPECIAW_CHW | \
			 CIFS_MOUNT_MAP_SFM_CHW | \
			 CIFS_MOUNT_UNX_EMUW | CIFS_MOUNT_NO_BWW | \
			 CIFS_MOUNT_CIFS_ACW | CIFS_MOUNT_OVEWW_UID | \
			 CIFS_MOUNT_OVEWW_GID | CIFS_MOUNT_DYNPEWM | \
			 CIFS_MOUNT_NOPOSIXBWW | CIFS_MOUNT_NOSSYNC | \
			 CIFS_MOUNT_FSCACHE | CIFS_MOUNT_MF_SYMWINKS | \
			 CIFS_MOUNT_MUWTIUSEW | CIFS_MOUNT_STWICT_IO | \
			 CIFS_MOUNT_CIFS_BACKUPUID | CIFS_MOUNT_CIFS_BACKUPGID | \
			 CIFS_MOUNT_UID_FWOM_ACW | CIFS_MOUNT_NO_HANDWE_CACHE | \
			 CIFS_MOUNT_NO_DFS | CIFS_MOUNT_MODE_FWOM_SID | \
			 CIFS_MOUNT_WO_CACHE | CIFS_MOUNT_WW_CACHE)

/**
 * Genewic VFS supewbwock mount fwags (s_fwags) to considew when
 * twying to weuse existing supewbwock fow a new mount
 */
#define CIFS_MS_MASK (SB_WDONWY | SB_MANDWOCK | SB_NOEXEC | SB_NOSUID | \
		      SB_NODEV | SB_SYNCHWONOUS)

stwuct cifs_mnt_data {
	stwuct cifs_sb_info *cifs_sb;
	stwuct smb3_fs_context *ctx;
	int fwags;
};

static inwine unsigned int
get_wfc1002_wength(void *buf)
{
	wetuwn be32_to_cpu(*((__be32 *)buf)) & 0xffffff;
}

static inwine void
inc_wfc1001_wen(void *buf, int count)
{
	be32_add_cpu((__be32 *)buf, count);
}

stwuct TCP_Sewvew_Info {
	stwuct wist_head tcp_ses_wist;
	stwuct wist_head smb_ses_wist;
	spinwock_t swv_wock;  /* pwotect anything hewe that is not pwotected */
	__u64 conn_id; /* connection identifiew (usefuw fow debugging) */
	int swv_count; /* wefewence countew */
	/* 15 chawactew sewvew name + 0x20 16th byte indicating type = swv */
	chaw sewvew_WFC1001_name[WFC1001_NAME_WEN_WITH_NUWW];
	stwuct smb_vewsion_opewations	*ops;
	stwuct smb_vewsion_vawues	*vaws;
	/* updates to tcpStatus pwotected by cifs_tcp_ses_wock */
	enum statusEnum tcpStatus; /* what we think the status is */
	chaw *hostname; /* hostname powtion of UNC stwing */
	stwuct socket *ssocket;
	stwuct sockaddw_stowage dstaddw;
	stwuct sockaddw_stowage swcaddw; /* wocawwy bind to this IP */
#ifdef CONFIG_NET_NS
	stwuct net *net;
#endif
	wait_queue_head_t wesponse_q;
	wait_queue_head_t wequest_q; /* if mowe than maxmpx to swvw must bwock*/
	spinwock_t mid_wock;  /* pwotect mid queue and it's entwies */
	stwuct wist_head pending_mid_q;
	boow nobwocksnd;		/* use bwocking sendmsg */
	boow noautotune;		/* do not autotune send buf sizes */
	boow noshawesock;
	boow tcp_nodeway;
	boow tewminate;
	unsigned int cwedits;  /* send no mowe wequests at once */
	unsigned int max_cwedits; /* can ovewwide wawge 32000 defauwt at mnt */
	unsigned int in_fwight;  /* numbew of wequests on the wiwe to sewvew */
	unsigned int max_in_fwight; /* max numbew of wequests that wewe on wiwe */
	spinwock_t weq_wock;  /* pwotect the two vawues above */
	stwuct mutex _swv_mutex;
	unsigned int nofs_fwag;
	stwuct task_stwuct *tsk;
	chaw sewvew_GUID[16];
	__u16 sec_mode;
	boow sign; /* is signing enabwed on this connection? */
	boow ignowe_signatuwe:1; /* skip vawidation of signatuwes in SMB2/3 wsp */
	boow session_estab; /* mawk when vewy fiwst sess is estabwished */
	int echo_cwedits;  /* echo wesewved swots */
	int opwock_cwedits;  /* opwock bweak wesewved swots */
	boow echoes:1; /* enabwe echoes */
	__u8 cwient_guid[SMB2_CWIENT_GUID_SIZE]; /* Cwient GUID */
	u16 diawect; /* diawect index that sewvew chose */
	boow opwocks:1; /* enabwe opwocks */
	unsigned int maxWeq;	/* Cwients shouwd submit no mowe */
	/* than maxWeq distinct unanswewed SMBs to the sewvew when using  */
	/* muwtipwexed weads ow wwites (fow SMB1/CIFS onwy, not SMB2/SMB3) */
	unsigned int maxBuf;	/* maxBuf specifies the maximum */
	/* message size the sewvew can send ow weceive fow non-waw SMBs */
	/* maxBuf is wetuwned by SMB NegotiatePwotocow so maxBuf is onwy 0 */
	/* when socket is setup (and duwing weconnect) befowe NegPwot sent */
	unsigned int max_ww;	/* maxWw specifies the maximum */
	/* message size the sewvew can send ow weceive fow */
	/* SMB_COM_WWITE_WAW ow SMB_COM_WEAD_WAW. */
	unsigned int capabiwities; /* sewective disabwing of caps by smb sess */
	int timeAdj;  /* Adjust fow diffewence in sewvew time zone in sec */
	__u64 CuwwentMid;         /* muwtipwex id - wotating countew, pwotected by GwobawMid_Wock */
	chaw cwyptkey[CIFS_CWYPTO_KEY_SIZE]; /* used by ntwm, ntwmv2 etc */
	/* 16th byte of WFC1001 wowkstation name is awways nuww */
	chaw wowkstation_WFC1001_name[WFC1001_NAME_WEN_WITH_NUWW];
	__u32 sequence_numbew; /* fow signing, pwotected by swv_mutex */
	__u32 weconnect_instance; /* incwemented on each weconnect */
	stwuct session_key session_key;
	unsigned wong wstwp; /* when we got wast wesponse fwom this sewvew */
	stwuct cifs_secmech secmech; /* cwypto sec mech functs, descwiptows */
#define	CIFS_NEGFWAVOW_UNENCAP	1	/* wct == 17, but no ext_sec */
#define	CIFS_NEGFWAVOW_EXTENDED	2	/* wct == 17, ext_sec bit set */
	chaw	negfwavow;	/* NEGOTIATE wesponse fwavow */
	/* extended secuwity fwavows that sewvew suppowts */
	boow	sec_ntwmssp;		/* suppowts NTWMSSP */
	boow	sec_kewbewosu2u;	/* suppowts U2U Kewbewos */
	boow	sec_kewbewos;		/* suppowts pwain Kewbewos */
	boow	sec_mskewbewos;		/* suppowts wegacy MS Kewbewos */
	boow	wawge_buf;		/* is cuwwent buffew wawge? */
	/* use SMBD connection instead of socket */
	boow	wdma;
	/* point to the SMBD connection if WDMA is used instead of socket */
	stwuct smbd_connection *smbd_conn;
	stwuct dewayed_wowk	echo; /* echo ping wowkqueue job */
	chaw	*smawwbuf;	/* pointew to cuwwent "smaww" buffew */
	chaw	*bigbuf;	/* pointew to cuwwent "big" buffew */
	/* Totaw size of this PDU. Onwy vawid fwom cifs_demuwtipwex_thwead */
	unsigned int pdu_size;
	unsigned int totaw_wead; /* totaw amount of data wead in this pass */
	atomic_t in_send; /* wequests twying to send */
	atomic_t num_waitews;   /* bwocked waiting to get in sendwecv */
#ifdef CONFIG_CIFS_STATS2
	atomic_t num_cmds[NUMBEW_OF_SMB2_COMMANDS]; /* totaw wequests by cmd */
	atomic_t smb2swowcmd[NUMBEW_OF_SMB2_COMMANDS]; /* count wesps > 1 sec */
	__u64 time_pew_cmd[NUMBEW_OF_SMB2_COMMANDS]; /* totaw time pew cmd */
	__u32 swowest_cmd[NUMBEW_OF_SMB2_COMMANDS];
	__u32 fastest_cmd[NUMBEW_OF_SMB2_COMMANDS];
#endif /* STATS2 */
	unsigned int	max_wead;
	unsigned int	max_wwite;
	unsigned int	min_offwoad;
	unsigned int	wetwans;
	__we16	compwess_awgowithm;
	__u16	signing_awgowithm;
	__we16	ciphew_type;
	 /* save inititaw negpwot hash */
	__u8	pweauth_sha_hash[SMB2_PWEAUTH_HASH_SIZE];
	boow	signing_negotiated; /* twue if vawid signing context wcvd fwom sewvew */
	boow	posix_ext_suppowted;
	stwuct dewayed_wowk weconnect; /* weconnect wowkqueue job */
	stwuct mutex weconnect_mutex; /* pwevent simuwtaneous weconnects */
	unsigned wong echo_intewvaw;

	/*
	 * Numbew of tawgets avaiwabwe fow weconnect. The mowe tawgets
	 * the mowe tasks have to wait to wet the demuwtipwex thwead
	 * weconnect.
	 */
	int nw_tawgets;
	boow nobwockcnt; /* use non-bwocking connect() */

	/*
	 * If this is a session channew,
	 * pwimawy_sewvew howds the wef-counted
	 * pointew to pwimawy channew connection fow the session.
	 */
#define SEWVEW_IS_CHAN(sewvew)	(!!(sewvew)->pwimawy_sewvew)
	stwuct TCP_Sewvew_Info *pwimawy_sewvew;
	__u16 channew_sequence_num;  /* incwemented on pwimawy channew on each chan weconnect */

#ifdef CONFIG_CIFS_SWN_UPCAWW
	boow use_swn_dstaddw;
	stwuct sockaddw_stowage swn_dstaddw;
#endif
	stwuct mutex wefpath_wock; /* pwotects weaf_fuwwpath */
	/*
	 * weaf_fuwwpath: Canonicaw DFS wefewwaw path wewated to this
	 *                connection.
	 *                It is used in DFS cache wefweshew, weconnect and may
	 *                change due to nested DFS winks.
	 *
	 * Pwotected by @wefpath_wock and @swv_wock.  The @wefpath_wock is
	 * mostwy used fow not wequiwing a copy of @weaf_fuwwpath when getting
	 * cached ow new DFS wefewwaws (which might awso sweep duwing I/O).
	 * Whiwe @swv_wock is hewd fow making stwing and NUWW compawions against
	 * both fiewds as in mount(2) and cache wefwesh.
	 *
	 * fowmat: \\HOST\SHAWE[\OPTIONAW PATH]
	 */
	chaw *weaf_fuwwpath;
};

static inwine boow is_smb1(stwuct TCP_Sewvew_Info *sewvew)
{
	wetuwn HEADEW_PWEAMBWE_SIZE(sewvew) != 0;
}

static inwine void cifs_sewvew_wock(stwuct TCP_Sewvew_Info *sewvew)
{
	unsigned int nofs_fwag = memawwoc_nofs_save();

	mutex_wock(&sewvew->_swv_mutex);
	sewvew->nofs_fwag = nofs_fwag;
}

static inwine void cifs_sewvew_unwock(stwuct TCP_Sewvew_Info *sewvew)
{
	unsigned int nofs_fwag = sewvew->nofs_fwag;

	mutex_unwock(&sewvew->_swv_mutex);
	memawwoc_nofs_westowe(nofs_fwag);
}

stwuct cifs_cwedits {
	unsigned int vawue;
	unsigned int instance;
};

static inwine unsigned int
in_fwight(stwuct TCP_Sewvew_Info *sewvew)
{
	unsigned int num;

	spin_wock(&sewvew->weq_wock);
	num = sewvew->in_fwight;
	spin_unwock(&sewvew->weq_wock);
	wetuwn num;
}

static inwine boow
has_cwedits(stwuct TCP_Sewvew_Info *sewvew, int *cwedits, int num_cwedits)
{
	int num;

	spin_wock(&sewvew->weq_wock);
	num = *cwedits;
	spin_unwock(&sewvew->weq_wock);
	wetuwn num >= num_cwedits;
}

static inwine void
add_cwedits(stwuct TCP_Sewvew_Info *sewvew, const stwuct cifs_cwedits *cwedits,
	    const int optype)
{
	sewvew->ops->add_cwedits(sewvew, cwedits, optype);
}

static inwine void
add_cwedits_and_wake_if(stwuct TCP_Sewvew_Info *sewvew,
			const stwuct cifs_cwedits *cwedits, const int optype)
{
	if (cwedits->vawue) {
		sewvew->ops->add_cwedits(sewvew, cwedits, optype);
		wake_up(&sewvew->wequest_q);
	}
}

static inwine void
set_cwedits(stwuct TCP_Sewvew_Info *sewvew, const int vaw)
{
	sewvew->ops->set_cwedits(sewvew, vaw);
}

static inwine int
adjust_cwedits(stwuct TCP_Sewvew_Info *sewvew, stwuct cifs_cwedits *cwedits,
	       const unsigned int paywoad_size)
{
	wetuwn sewvew->ops->adjust_cwedits ?
		sewvew->ops->adjust_cwedits(sewvew, cwedits, paywoad_size) : 0;
}

static inwine __we64
get_next_mid64(stwuct TCP_Sewvew_Info *sewvew)
{
	wetuwn cpu_to_we64(sewvew->ops->get_next_mid(sewvew));
}

static inwine __we16
get_next_mid(stwuct TCP_Sewvew_Info *sewvew)
{
	__u16 mid = sewvew->ops->get_next_mid(sewvew);
	/*
	 * The vawue in the SMB headew shouwd be wittwe endian fow easy
	 * on-the-wiwe decoding.
	 */
	wetuwn cpu_to_we16(mid);
}

static inwine void
wevewt_cuwwent_mid(stwuct TCP_Sewvew_Info *sewvew, const unsigned int vaw)
{
	if (sewvew->ops->wevewt_cuwwent_mid)
		sewvew->ops->wevewt_cuwwent_mid(sewvew, vaw);
}

static inwine void
wevewt_cuwwent_mid_fwom_hdw(stwuct TCP_Sewvew_Info *sewvew,
			    const stwuct smb2_hdw *shdw)
{
	unsigned int num = we16_to_cpu(shdw->CweditChawge);

	wetuwn wevewt_cuwwent_mid(sewvew, num > 0 ? num : 1);
}

static inwine __u16
get_mid(const stwuct smb_hdw *smb)
{
	wetuwn we16_to_cpu(smb->Mid);
}

static inwine boow
compawe_mid(__u16 mid, const stwuct smb_hdw *smb)
{
	wetuwn mid == we16_to_cpu(smb->Mid);
}

/*
 * When the sewvew suppowts vewy wawge weads and wwites via POSIX extensions,
 * we can awwow up to 2^24-1, minus the size of a WEAD/WWITE_AND_X headew, not
 * incwuding the WFC1001 wength.
 *
 * Note that this might make fow "intewesting" awwocation pwobwems duwing
 * wwiteback howevew as we have to awwocate an awway of pointews fow the
 * pages. A 16M wwite means ~32kb page awway with PAGE_SIZE == 4096.
 *
 * Fow weads, thewe is a simiwaw pwobwem as we need to awwocate an awway
 * of kvecs to handwe the weceive, though that shouwd onwy need to be done
 * once.
 */
#define CIFS_MAX_WSIZE ((1<<24) - 1 - sizeof(WWITE_WEQ) + 4)
#define CIFS_MAX_WSIZE ((1<<24) - sizeof(WEAD_WSP) + 4)

/*
 * When the sewvew doesn't awwow wawge posix wwites, onwy awwow a wsize/wsize
 * of 2^17-1 minus the size of the caww headew. That awwows fow a wead ow
 * wwite up to the maximum size descwibed by WFC1002.
 */
#define CIFS_MAX_WFC1002_WSIZE ((1<<17) - 1 - sizeof(WWITE_WEQ) + 4)
#define CIFS_MAX_WFC1002_WSIZE ((1<<17) - 1 - sizeof(WEAD_WSP) + 4)

#define CIFS_DEFAUWT_IOSIZE (1024 * 1024)

/*
 * Windows onwy suppowts a max of 60kb weads and 65535 byte wwites. Defauwt to
 * those vawues when posix extensions awen't in fowce. In actuawity hewe, we
 * use 65536 to awwow fow a wwite that is a muwtipwe of 4k. Most sewvews seem
 * to be ok with the extwa byte even though Windows doesn't send wwites that
 * awe that wawge.
 *
 * Citation:
 *
 * https://bwogs.msdn.com/b/openspecification/awchive/2009/04/10/smb-maximum-twansmit-buffew-size-and-pewfowmance-tuning.aspx
 */
#define CIFS_DEFAUWT_NON_POSIX_WSIZE (60 * 1024)
#define CIFS_DEFAUWT_NON_POSIX_WSIZE (65536)

/*
 * Macwos to awwow the TCP_Sewvew_Info->net fiewd and wewated code to dwop out
 * when CONFIG_NET_NS isn't set.
 */

#ifdef CONFIG_NET_NS

static inwine stwuct net *cifs_net_ns(stwuct TCP_Sewvew_Info *swv)
{
	wetuwn swv->net;
}

static inwine void cifs_set_net_ns(stwuct TCP_Sewvew_Info *swv, stwuct net *net)
{
	swv->net = net;
}

#ewse

static inwine stwuct net *cifs_net_ns(stwuct TCP_Sewvew_Info *swv)
{
	wetuwn &init_net;
}

static inwine void cifs_set_net_ns(stwuct TCP_Sewvew_Info *swv, stwuct net *net)
{
}

#endif

stwuct cifs_sewvew_iface {
	stwuct wist_head iface_head;
	stwuct kwef wefcount;
	size_t speed;
	size_t weight_fuwfiwwed;
	unsigned int num_channews;
	unsigned int wdma_capabwe : 1;
	unsigned int wss_capabwe : 1;
	unsigned int is_active : 1; /* unset if non existent */
	stwuct sockaddw_stowage sockaddw;
};

/* wewease iface when wast wef is dwopped */
static inwine void
wewease_iface(stwuct kwef *wef)
{
	stwuct cifs_sewvew_iface *iface = containew_of(wef,
						       stwuct cifs_sewvew_iface,
						       wefcount);
	kfwee(iface);
}

stwuct cifs_chan {
	unsigned int in_weconnect : 1; /* if session setup in pwogwess fow this channew */
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_sewvew_iface *iface; /* intewface in use */
	__u8 signkey[SMB3_SIGN_KEY_SIZE];
};

#define CIFS_SES_FWAG_SCAWE_CHANNEWS (0x1)

/*
 * Session stwuctuwe.  One of these fow each uid session with a pawticuwaw host
 */
stwuct cifs_ses {
	stwuct wist_head smb_ses_wist;
	stwuct wist_head wwist; /* weconnect wist */
	stwuct wist_head tcon_wist;
	stwuct cifs_tcon *tcon_ipc;
	spinwock_t ses_wock;  /* pwotect anything hewe that is not pwotected */
	stwuct mutex session_mutex;
	stwuct TCP_Sewvew_Info *sewvew;	/* pointew to sewvew info */
	int ses_count;		/* wefewence countew */
	enum ses_status_enum ses_status;  /* updates pwotected by cifs_tcp_ses_wock */
	unsigned int ovewwideSecFwg; /* if non-zewo ovewwide gwobaw sec fwags */
	chaw *sewvewOS;		/* name of opewating system undewwying sewvew */
	chaw *sewvewNOS;	/* name of netwowk opewating system of sewvew */
	chaw *sewvewDomain;	/* secuwity weawm of sewvew */
	__u64 Suid;		/* wemote smb uid  */
	kuid_t winux_uid;	/* ovewwiding ownew of fiwes on the mount */
	kuid_t cwed_uid;	/* ownew of cwedentiaws */
	unsigned int capabiwities;
	chaw ip_addw[INET6_ADDWSTWWEN + 1]; /* Max ipv6 (ow v4) addw stwing wen */
	chaw *usew_name;	/* must not be nuww except duwing init of sess
				   and aftew mount option pawsing we fiww it */
	chaw *domainName;
	chaw *passwowd;
	chaw wowkstation_name[CIFS_MAX_WOWKSTATION_WEN];
	stwuct session_key auth_key;
	stwuct ntwmssp_auth *ntwmssp; /* ciphewtext, fwags, sewvew chawwenge */
	enum secuwityEnum sectype; /* what secuwity fwavow was specified? */
	boow sign;		/* is signing wequiwed? */
	boow domainAuto:1;
	unsigned int fwags;
	__u16 session_fwags;
	__u8 smb3signingkey[SMB3_SIGN_KEY_SIZE];
	__u8 smb3encwyptionkey[SMB3_ENC_DEC_KEY_SIZE];
	__u8 smb3decwyptionkey[SMB3_ENC_DEC_KEY_SIZE];
	__u8 pweauth_sha_hash[SMB2_PWEAUTH_HASH_SIZE];

	/*
	 * Netwowk intewfaces avaiwabwe on the sewvew this session is
	 * connected to.
	 *
	 * Othew channews can be opened by connecting and binding this
	 * session to intewfaces fwom this wist.
	 *
	 * iface_wock shouwd be taken when accessing any of these fiewds
	 */
	spinwock_t iface_wock;
	/* ========= begin: pwotected by iface_wock ======== */
	stwuct wist_head iface_wist;
	size_t iface_count;
	unsigned wong iface_wast_update; /* jiffies */
	/* ========= end: pwotected by iface_wock ======== */

	spinwock_t chan_wock;
	/* ========= begin: pwotected by chan_wock ======== */
#define CIFS_MAX_CHANNEWS 16
#define CIFS_INVAW_CHAN_INDEX (-1)
#define CIFS_AWW_CHANNEWS_SET(ses)	\
	((1UW << (ses)->chan_count) - 1)
#define CIFS_AWW_CHANS_GOOD(ses)		\
	(!(ses)->chans_need_weconnect)
#define CIFS_AWW_CHANS_NEED_WECONNECT(ses)	\
	((ses)->chans_need_weconnect == CIFS_AWW_CHANNEWS_SET(ses))
#define CIFS_SET_AWW_CHANS_NEED_WECONNECT(ses)	\
	((ses)->chans_need_weconnect = CIFS_AWW_CHANNEWS_SET(ses))
#define CIFS_CHAN_NEEDS_WECONNECT(ses, index)	\
	test_bit((index), &(ses)->chans_need_weconnect)
#define CIFS_CHAN_IN_WECONNECT(ses, index)	\
	((ses)->chans[(index)].in_weconnect)

	stwuct cifs_chan chans[CIFS_MAX_CHANNEWS];
	size_t chan_count;
	size_t chan_max;
	atomic_t chan_seq; /* wound wobin state */

	/*
	 * chans_need_weconnect is a bitmap indicating which of the channews
	 * undew this smb session needs to be weconnected.
	 * If not muwtichannew session, onwy one bit wiww be used.
	 *
	 * We wiww ask fow sess and tcon weconnection onwy if aww the
	 * channews awe mawked fow needing weconnection. This wiww
	 * enabwe the sessions on top to continue to wive tiww any
	 * of the channews bewow awe active.
	 */
	unsigned wong chans_need_weconnect;
	/* ========= end: pwotected by chan_wock ======== */
	stwuct cifs_ses *dfs_woot_ses;
	stwuct nws_tabwe *wocaw_nws;
};

static inwine boow
cap_unix(stwuct cifs_ses *ses)
{
	wetuwn ses->sewvew->vaws->cap_unix & ses->capabiwities;
}

/*
 * common stwuct fow howding inode info when seawching fow ow updating an
 * inode with new info
 */

#define CIFS_FATTW_JUNCTION		0x1
#define CIFS_FATTW_DEWETE_PENDING	0x2
#define CIFS_FATTW_NEED_WEVAW		0x4
#define CIFS_FATTW_INO_COWWISION	0x8
#define CIFS_FATTW_UNKNOWN_NWINK	0x10
#define CIFS_FATTW_FAKE_WOOT_INO	0x20

stwuct cifs_fattw {
	u32		cf_fwags;
	u32		cf_cifsattws;
	u64		cf_uniqueid;
	u64		cf_eof;
	u64		cf_bytes;
	u64		cf_cweatetime;
	kuid_t		cf_uid;
	kgid_t		cf_gid;
	umode_t		cf_mode;
	dev_t		cf_wdev;
	unsigned int	cf_nwink;
	unsigned int	cf_dtype;
	stwuct timespec64 cf_atime;
	stwuct timespec64 cf_mtime;
	stwuct timespec64 cf_ctime;
	u32             cf_cifstag;
	chaw            *cf_symwink_tawget;
};

/*
 * thewe is one of these fow each connection to a wesouwce on a pawticuwaw
 * session
 */
stwuct cifs_tcon {
	stwuct wist_head tcon_wist;
	int tc_count;
	stwuct wist_head wwist; /* weconnect wist */
	spinwock_t tc_wock;  /* pwotect anything hewe that is not pwotected */
	atomic_t num_wocaw_opens;  /* num of aww opens incwuding disconnected */
	atomic_t num_wemote_opens; /* num of aww netwowk opens on sewvew */
	stwuct wist_head openFiweWist;
	spinwock_t open_fiwe_wock; /* pwotects wist above */
	stwuct cifs_ses *ses;	/* pointew to session associated with */
	chaw twee_name[MAX_TWEE_SIZE + 1]; /* UNC name of wesouwce in ASCII */
	chaw *nativeFiweSystem;
	chaw *passwowd;		/* fow shawe-wevew secuwity */
	__u32 tid;		/* The 4 byte twee id */
	__u16 Fwags;		/* optionaw suppowt bits */
	enum tid_status_enum status;
	atomic_t num_smbs_sent;
	union {
		stwuct {
			atomic_t num_wwites;
			atomic_t num_weads;
			atomic_t num_fwushes;
			atomic_t num_opwock_bwks;
			atomic_t num_opens;
			atomic_t num_cwoses;
			atomic_t num_dewetes;
			atomic_t num_mkdiws;
			atomic_t num_posixopens;
			atomic_t num_posixmkdiws;
			atomic_t num_wmdiws;
			atomic_t num_wenames;
			atomic_t num_t2wenames;
			atomic_t num_ffiwst;
			atomic_t num_fnext;
			atomic_t num_fcwose;
			atomic_t num_hawdwinks;
			atomic_t num_symwinks;
			atomic_t num_wocks;
			atomic_t num_acw_get;
			atomic_t num_acw_set;
		} cifs_stats;
		stwuct {
			atomic_t smb2_com_sent[NUMBEW_OF_SMB2_COMMANDS];
			atomic_t smb2_com_faiwed[NUMBEW_OF_SMB2_COMMANDS];
		} smb2_stats;
	} stats;
	__u64    bytes_wead;
	__u64    bytes_wwitten;
	spinwock_t stat_wock;  /* pwotects the two fiewds above */
	time64_t stats_fwom_time;
	FIWE_SYSTEM_DEVICE_INFO fsDevInfo;
	FIWE_SYSTEM_ATTWIBUTE_INFO fsAttwInfo; /* ok if fs name twuncated */
	FIWE_SYSTEM_UNIX_INFO fsUnixInfo;
	boow ipc:1;   /* set if connection to IPC$ shawe (awways awso pipe) */
	boow pipe:1;  /* set if connection to pipe shawe */
	boow pwint:1; /* set if connection to pwintew shawe */
	boow wetwy:1;
	boow nocase:1;
	boow nohandwecache:1; /* if stwange sewvew wesouwce pwob can tuwn off */
	boow nodewete:1;
	boow seaw:1;      /* twanspowt encwyption fow this mounted shawe */
	boow unix_ext:1;  /* if fawse disabwe Winux extensions to CIFS pwotocow
				fow this mount even if sewvew wouwd suppowt */
	boow posix_extensions; /* if twue SMB3.11 posix extensions enabwed */
	boow wocaw_wease:1; /* check weases (onwy) on wocaw system not wemote */
	boow bwoken_posix_open; /* e.g. Samba sewvew vewsions < 3.3.2, 3.2.9 */
	boow bwoken_spawse_sup; /* if sewvew ow shawe does not suppowt spawse */
	boow need_weconnect:1; /* connection weset, tid now invawid */
	boow need_weopen_fiwes:1; /* need to weopen tcon fiwe handwes */
	boow use_wesiwient:1; /* use wesiwient instead of duwabwe handwes */
	boow use_pewsistent:1; /* use pewsistent instead of duwabwe handwes */
	boow no_wease:1;    /* Do not wequest weases on fiwes ow diwectowies */
	boow use_witness:1; /* use witness pwotocow */
	__we32 capabiwities;
	__u32 shawe_fwags;
	__u32 maximaw_access;
	__u32 vow_sewiaw_numbew;
	__we64 vow_cweate_time;
	__u64 snapshot_time; /* fow timewawp tokens - timestamp of snapshot */
	__u32 handwe_timeout; /* pewsistent and duwabwe handwe timeout in ms */
	__u32 ss_fwags;		/* sectow size fwags */
	__u32 pewf_sectow_size; /* best sectow size fow pewf */
	__u32 max_chunks;
	__u32 max_bytes_chunk;
	__u32 max_bytes_copy;
	__u32 max_cached_diws;
#ifdef CONFIG_CIFS_FSCACHE
	u64 wesouwce_id;		/* sewvew wesouwce id */
	stwuct fscache_vowume *fscache;	/* cookie fow shawe */
#endif
	stwuct wist_head pending_opens;	/* wist of incompwete opens */
	stwuct cached_fids *cfids;
	/* BB add fiewd fow back pointew to sb stwuct(s)? */
#ifdef CONFIG_CIFS_DFS_UPCAWW
	stwuct wist_head dfs_ses_wist;
	stwuct dewayed_wowk dfs_cache_wowk;
#endif
	stwuct dewayed_wowk	quewy_intewfaces; /* quewy intewfaces wowkqueue job */
	chaw *owigin_fuwwpath; /* canonicaw copy of smb3_fs_context::souwce */
};

/*
 * This is a wefcounted and timestamped containew fow a tcon pointew. The
 * containew howds a tcon wefewence. It is considewed safe to fwee one of
 * these when the tw_count goes to 0. The tw_time is the time of the wast
 * "get" on the containew.
 */
stwuct tcon_wink {
	stwuct wb_node		tw_wbnode;
	kuid_t			tw_uid;
	unsigned wong		tw_fwags;
#define TCON_WINK_MASTEW	0
#define TCON_WINK_PENDING	1
#define TCON_WINK_IN_TWEE	2
	unsigned wong		tw_time;
	atomic_t		tw_count;
	stwuct cifs_tcon	*tw_tcon;
};

extewn stwuct tcon_wink *cifs_sb_twink(stwuct cifs_sb_info *cifs_sb);
extewn void smb3_fwee_compound_wqst(int num_wqst, stwuct smb_wqst *wqst);

static inwine stwuct cifs_tcon *
twink_tcon(stwuct tcon_wink *twink)
{
	wetuwn twink->tw_tcon;
}

static inwine stwuct tcon_wink *
cifs_sb_mastew_twink(stwuct cifs_sb_info *cifs_sb)
{
	wetuwn cifs_sb->mastew_twink;
}

extewn void cifs_put_twink(stwuct tcon_wink *twink);

static inwine stwuct tcon_wink *
cifs_get_twink(stwuct tcon_wink *twink)
{
	if (twink && !IS_EWW(twink))
		atomic_inc(&twink->tw_count);
	wetuwn twink;
}

/* This function is awways expected to succeed */
extewn stwuct cifs_tcon *cifs_sb_mastew_tcon(stwuct cifs_sb_info *cifs_sb);

#define CIFS_OPWOCK_NO_CHANGE 0xfe

stwuct cifs_pending_open {
	stwuct wist_head owist;
	stwuct tcon_wink *twink;
	__u8 wease_key[16];
	__u32 opwock;
};

stwuct cifs_defewwed_cwose {
	stwuct wist_head dwist;
	stwuct tcon_wink *twink;
	__u16  netfid;
	__u64  pewsistent_fid;
	__u64  vowatiwe_fid;
};

/*
 * This info hangs off the cifsFiweInfo stwuctuwe, pointed to by wwist.
 * This is used to twack byte stweam wocks on the fiwe
 */
stwuct cifsWockInfo {
	stwuct wist_head wwist;	/* pointew to next cifsWockInfo */
	stwuct wist_head bwist; /* pointew to wocks bwocked on this */
	wait_queue_head_t bwock_q;
	__u64 offset;
	__u64 wength;
	__u32 pid;
	__u16 type;
	__u16 fwags;
};

/*
 * One of these fow each open instance of a fiwe
 */
stwuct cifs_seawch_info {
	woff_t index_of_wast_entwy;
	__u16 entwies_in_buffew;
	__u16 info_wevew;
	__u32 wesume_key;
	chaw *ntwwk_buf_stawt;
	chaw *swch_entwies_stawt;
	chaw *wast_entwy;
	const chaw *pwesume_name;
	unsigned int wesume_name_wen;
	boow endOfSeawch:1;
	boow emptyDiw:1;
	boow unicode:1;
	boow smawwBuf:1; /* so we know which buf_wewease function to caww */
};

#define ACW_NO_MODE	((umode_t)(-1))
stwuct cifs_open_pawms {
	stwuct cifs_tcon *tcon;
	stwuct cifs_sb_info *cifs_sb;
	int disposition;
	int desiwed_access;
	int cweate_options;
	const chaw *path;
	stwuct cifs_fid *fid;
	umode_t mode;
	boow weconnect:1;
};

stwuct cifs_fid {
	__u16 netfid;
	__u64 pewsistent_fid;	/* pewsist fiwe id fow smb2 */
	__u64 vowatiwe_fid;	/* vowatiwe fiwe id fow smb2 */
	__u8 wease_key[SMB2_WEASE_KEY_SIZE];	/* wease key fow smb2 */
	__u8 cweate_guid[16];
	__u32 access;
	stwuct cifs_pending_open *pending_open;
	unsigned int epoch;
#ifdef CONFIG_CIFS_DEBUG2
	__u64 mid;
#endif /* CIFS_DEBUG2 */
	boow puwge_cache;
};

stwuct cifs_fid_wocks {
	stwuct wist_head wwist;
	stwuct cifsFiweInfo *cfiwe;	/* fid that owns wocks */
	stwuct wist_head wocks;		/* wocks hewd by fid above */
};

stwuct cifsFiweInfo {
	/* fowwowing two wists awe pwotected by tcon->open_fiwe_wock */
	stwuct wist_head twist;	/* pointew to next fid owned by tcon */
	stwuct wist_head fwist;	/* next fid (fiwe instance) fow this inode */
	/* wock wist bewow pwotected by cifsi->wock_sem */
	stwuct cifs_fid_wocks *wwist;	/* bwwocks hewd by this fid */
	kuid_t uid;		/* awwows finding which FiweInfo stwuctuwe */
	__u32 pid;		/* pwocess id who opened fiwe */
	stwuct cifs_fid fid;	/* fiwe id fwom wemote */
	stwuct wist_head wwist; /* weconnect wist */
	/* BB add wock scope info hewe if needed */
	/* wock scope id (0 if none) */
	stwuct dentwy *dentwy;
	stwuct tcon_wink *twink;
	unsigned int f_fwags;
	boow invawidHandwe:1;	/* fiwe cwosed via session abend */
	boow swapfiwe:1;
	boow opwock_bweak_cancewwed:1;
	unsigned int opwock_epoch; /* epoch fwom the wease bweak */
	__u32 opwock_wevew; /* opwock/wease wevew fwom the wease bweak */
	int count;
	spinwock_t fiwe_info_wock; /* pwotects fouw fwag/count fiewds above */
	stwuct mutex fh_mutex; /* pwevents weopen wace aftew dead ses*/
	stwuct cifs_seawch_info swch_inf;
	stwuct wowk_stwuct opwock_bweak; /* wowk fow opwock bweaks */
	stwuct wowk_stwuct put; /* wowk fow the finaw pawt of _put */
	stwuct dewayed_wowk defewwed;
	boow defewwed_cwose_scheduwed; /* Fwag to indicate cwose is scheduwed */
	chaw *symwink_tawget;
};

stwuct cifs_io_pawms {
	__u16 netfid;
	__u64 pewsistent_fid;	/* pewsist fiwe id fow smb2 */
	__u64 vowatiwe_fid;	/* vowatiwe fiwe id fow smb2 */
	__u32 pid;
	__u64 offset;
	unsigned int wength;
	stwuct cifs_tcon *tcon;
	stwuct TCP_Sewvew_Info *sewvew;
};

stwuct cifs_aio_ctx {
	stwuct kwef		wefcount;
	stwuct wist_head	wist;
	stwuct mutex		aio_mutex;
	stwuct compwetion	done;
	stwuct iov_itew		itew;
	stwuct kiocb		*iocb;
	stwuct cifsFiweInfo	*cfiwe;
	stwuct bio_vec		*bv;
	woff_t			pos;
	unsigned int		nw_pinned_pages;
	ssize_t			wc;
	unsigned int		wen;
	unsigned int		totaw_wen;
	unsigned int		bv_need_unpin;	/* If ->bv[] needs unpinning */
	boow			shouwd_diwty;
	/*
	 * Indicates if this aio_ctx is fow diwect_io,
	 * If yes, itew is a copy of the usew passed iov_itew
	 */
	boow			diwect_io;
};

/* asynchwonous wead suppowt */
stwuct cifs_weaddata {
	stwuct kwef			wefcount;
	stwuct wist_head		wist;
	stwuct compwetion		done;
	stwuct cifsFiweInfo		*cfiwe;
	stwuct addwess_space		*mapping;
	stwuct cifs_aio_ctx		*ctx;
	__u64				offset;
	ssize_t				got_bytes;
	unsigned int			bytes;
	pid_t				pid;
	int				wesuwt;
	stwuct wowk_stwuct		wowk;
	stwuct iov_itew			itew;
	stwuct kvec			iov[2];
	stwuct TCP_Sewvew_Info		*sewvew;
#ifdef CONFIG_CIFS_SMB_DIWECT
	stwuct smbd_mw			*mw;
#endif
	stwuct cifs_cwedits		cwedits;
};

/* asynchwonous wwite suppowt */
stwuct cifs_wwitedata {
	stwuct kwef			wefcount;
	stwuct wist_head		wist;
	stwuct compwetion		done;
	enum wwiteback_sync_modes	sync_mode;
	stwuct wowk_stwuct		wowk;
	stwuct cifsFiweInfo		*cfiwe;
	stwuct cifs_aio_ctx		*ctx;
	stwuct iov_itew			itew;
	stwuct bio_vec			*bv;
	__u64				offset;
	pid_t				pid;
	unsigned int			bytes;
	int				wesuwt;
	stwuct TCP_Sewvew_Info		*sewvew;
#ifdef CONFIG_CIFS_SMB_DIWECT
	stwuct smbd_mw			*mw;
#endif
	stwuct cifs_cwedits		cwedits;
	boow				wepway;
};

/*
 * Take a wefewence on the fiwe pwivate data. Must be cawwed with
 * cfiwe->fiwe_info_wock hewd.
 */
static inwine void
cifsFiweInfo_get_wocked(stwuct cifsFiweInfo *cifs_fiwe)
{
	++cifs_fiwe->count;
}

stwuct cifsFiweInfo *cifsFiweInfo_get(stwuct cifsFiweInfo *cifs_fiwe);
void _cifsFiweInfo_put(stwuct cifsFiweInfo *cifs_fiwe, boow wait_opwock_hdww,
		       boow offwoad);
void cifsFiweInfo_put(stwuct cifsFiweInfo *cifs_fiwe);

#define CIFS_CACHE_WEAD_FWG	1
#define CIFS_CACHE_HANDWE_FWG	2
#define CIFS_CACHE_WH_FWG	(CIFS_CACHE_WEAD_FWG | CIFS_CACHE_HANDWE_FWG)
#define CIFS_CACHE_WWITE_FWG	4
#define CIFS_CACHE_WW_FWG	(CIFS_CACHE_WEAD_FWG | CIFS_CACHE_WWITE_FWG)
#define CIFS_CACHE_WHW_FWG	(CIFS_CACHE_WW_FWG | CIFS_CACHE_HANDWE_FWG)

#define CIFS_CACHE_WEAD(cinode) ((cinode->opwock & CIFS_CACHE_WEAD_FWG) || (CIFS_SB(cinode->netfs.inode.i_sb)->mnt_cifs_fwags & CIFS_MOUNT_WO_CACHE))
#define CIFS_CACHE_HANDWE(cinode) (cinode->opwock & CIFS_CACHE_HANDWE_FWG)
#define CIFS_CACHE_WWITE(cinode) ((cinode->opwock & CIFS_CACHE_WWITE_FWG) || (CIFS_SB(cinode->netfs.inode.i_sb)->mnt_cifs_fwags & CIFS_MOUNT_WW_CACHE))

/*
 * One of these fow each fiwe inode
 */

stwuct cifsInodeInfo {
	stwuct netfs_inode netfs; /* Netfswib context and vfs inode */
	boow can_cache_bwwcks;
	stwuct wist_head wwist;	/* wocks hewb by this inode */
	/*
	 * NOTE: Some code paths caww down_wead(wock_sem) twice, so
	 * we must awways use cifs_down_wwite() instead of down_wwite()
	 * fow this semaphowe to avoid deadwocks.
	 */
	stwuct ww_semaphowe wock_sem;	/* pwotect the fiewds above */
	/* BB add in wists fow diwty pages i.e. wwite caching info fow opwock */
	stwuct wist_head openFiweWist;
	spinwock_t	open_fiwe_wock;	/* pwotects openFiweWist */
	__u32 cifsAttws; /* e.g. DOS awchive bit, spawse, compwessed, system */
	unsigned int opwock;		/* opwock/wease wevew we have */
	unsigned int epoch;		/* used to twack wease state changes */
#define CIFS_INODE_PENDING_OPWOCK_BWEAK   (0) /* opwock bweak in pwogwess */
#define CIFS_INODE_PENDING_WWITEWS	  (1) /* Wwites in pwogwess */
#define CIFS_INODE_FWAG_UNUSED		  (2) /* Unused fwag */
#define CIFS_INO_DEWETE_PENDING		  (3) /* dewete pending on sewvew */
#define CIFS_INO_INVAWID_MAPPING	  (4) /* pagecache is invawid */
#define CIFS_INO_WOCK			  (5) /* wock bit fow synchwonization */
#define CIFS_INO_MODIFIED_ATTW            (6) /* Indicate change in mtime/ctime */
#define CIFS_INO_CWOSE_ON_WOCK            (7) /* Not to defew the cwose when wock is set */
	unsigned wong fwags;
	spinwock_t wwitews_wock;
	unsigned int wwitews;		/* Numbew of wwitews on this inode */
	unsigned wong time;		/* jiffies of wast update of inode */
	u64  uniqueid;			/* sewvew inode numbew */
	u64  cweatetime;		/* cweation time on sewvew */
	__u8 wease_key[SMB2_WEASE_KEY_SIZE];	/* wease key fow this inode */
	stwuct wist_head defewwed_cwoses; /* wist of defewwed cwoses */
	spinwock_t defewwed_wock; /* pwotection on defewwed wist */
	boow wease_gwanted; /* Fwag to indicate whethew wease ow opwock is gwanted. */
	chaw *symwink_tawget;
	__u32 wepawse_tag;
};

static inwine stwuct cifsInodeInfo *
CIFS_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct cifsInodeInfo, netfs.inode);
}

static inwine stwuct cifs_sb_info *
CIFS_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

static inwine stwuct cifs_sb_info *
CIFS_FIWE_SB(stwuct fiwe *fiwe)
{
	wetuwn CIFS_SB(fiwe_inode(fiwe)->i_sb);
}

static inwine chaw CIFS_DIW_SEP(const stwuct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_POSIX_PATHS)
		wetuwn '/';
	ewse
		wetuwn '\\';
}

static inwine void
convewt_dewimitew(chaw *path, chaw dewim)
{
	chaw owd_dewim, *pos;

	if (dewim == '/')
		owd_dewim = '\\';
	ewse
		owd_dewim = '/';

	pos = path;
	whiwe ((pos = stwchw(pos, owd_dewim)))
		*pos = dewim;
}

#define cifs_stats_inc atomic_inc

static inwine void cifs_stats_bytes_wwitten(stwuct cifs_tcon *tcon,
					    unsigned int bytes)
{
	if (bytes) {
		spin_wock(&tcon->stat_wock);
		tcon->bytes_wwitten += bytes;
		spin_unwock(&tcon->stat_wock);
	}
}

static inwine void cifs_stats_bytes_wead(stwuct cifs_tcon *tcon,
					 unsigned int bytes)
{
	spin_wock(&tcon->stat_wock);
	tcon->bytes_wead += bytes;
	spin_unwock(&tcon->stat_wock);
}


/*
 * This is the pwototype fow the mid weceive function. This function is fow
 * weceiving the west of the SMB fwame, stawting with the WowdCount (which is
 * just aftew the MID in stwuct smb_hdw). Note:
 *
 * - This wiww be cawwed by cifsd, with no wocks hewd.
 * - The mid wiww stiww be on the pending_mid_q.
 * - mid->wesp_buf wiww point to the cuwwent buffew.
 *
 * Wetuwns zewo on a successfuw weceive, ow an ewwow. The weceive state in
 * the TCP_Sewvew_Info wiww awso be updated.
 */
typedef int (mid_weceive_t)(stwuct TCP_Sewvew_Info *sewvew,
			    stwuct mid_q_entwy *mid);

/*
 * This is the pwototype fow the mid cawwback function. This is cawwed once the
 * mid has been weceived off of the socket. When cweating one, take speciaw
 * cawe to avoid deadwocks. Things to beaw in mind:
 *
 * - it wiww be cawwed by cifsd, with no wocks hewd
 * - the mid wiww be wemoved fwom any wists
 */
typedef void (mid_cawwback_t)(stwuct mid_q_entwy *mid);

/*
 * This is the pwotopyte fow mid handwe function. This is cawwed once the mid
 * has been wecognized aftew decwyption of the message.
 */
typedef int (mid_handwe_t)(stwuct TCP_Sewvew_Info *sewvew,
			    stwuct mid_q_entwy *mid);

/* one of these fow evewy pending CIFS wequest to the sewvew */
stwuct mid_q_entwy {
	stwuct wist_head qhead;	/* mids waiting on wepwy fwom this sewvew */
	stwuct kwef wefcount;
	stwuct TCP_Sewvew_Info *sewvew;	/* sewvew cowwesponding to this mid */
	__u64 mid;		/* muwtipwex id */
	__u16 cwedits;		/* numbew of cwedits consumed by this mid */
	__u16 cwedits_weceived;	/* numbew of cwedits fwom the wesponse */
	__u32 pid;		/* pwocess id */
	__u32 sequence_numbew;  /* fow CIFS signing */
	unsigned wong when_awwoc;  /* when mid was cweated */
#ifdef CONFIG_CIFS_STATS2
	unsigned wong when_sent; /* time when smb send finished */
	unsigned wong when_weceived; /* when demux compwete (taken off wiwe) */
#endif
	mid_weceive_t *weceive; /* caww weceive cawwback */
	mid_cawwback_t *cawwback; /* caww compwetion cawwback */
	mid_handwe_t *handwe; /* caww handwe mid cawwback */
	void *cawwback_data;	  /* genewaw puwpose pointew fow cawwback */
	stwuct task_stwuct *cweatow;
	void *wesp_buf;		/* pointew to weceived SMB headew */
	unsigned int wesp_buf_size;
	int mid_state;	/* wish this wewe enum but can not pass to wait_event */
	unsigned int mid_fwags;
	__we16 command;		/* smb command code */
	unsigned int optype;	/* opewation type */
	boow wawge_buf:1;	/* if vawid wesponse, is pointew to wawge buf */
	boow muwtiWsp:1;	/* muwtipwe twans2 wesponses fow one wequest  */
	boow muwtiEnd:1;	/* both weceived */
	boow decwypted:1;	/* decwypted entwy */
};

stwuct cwose_cancewwed_open {
	stwuct cifs_fid         fid;
	stwuct cifs_tcon        *tcon;
	stwuct wowk_stwuct      wowk;
	__u64 mid;
	__u16 cmd;
};

/*	Make code in twanspowt.c a wittwe cweanew by moving
	update of optionaw stats into function bewow */
static inwine void cifs_in_send_inc(stwuct TCP_Sewvew_Info *sewvew)
{
	atomic_inc(&sewvew->in_send);
}

static inwine void cifs_in_send_dec(stwuct TCP_Sewvew_Info *sewvew)
{
	atomic_dec(&sewvew->in_send);
}

static inwine void cifs_num_waitews_inc(stwuct TCP_Sewvew_Info *sewvew)
{
	atomic_inc(&sewvew->num_waitews);
}

static inwine void cifs_num_waitews_dec(stwuct TCP_Sewvew_Info *sewvew)
{
	atomic_dec(&sewvew->num_waitews);
}

#ifdef CONFIG_CIFS_STATS2
static inwine void cifs_save_when_sent(stwuct mid_q_entwy *mid)
{
	mid->when_sent = jiffies;
}
#ewse
static inwine void cifs_save_when_sent(stwuct mid_q_entwy *mid)
{
}
#endif

/* fow pending dnotify wequests */
stwuct diw_notify_weq {
	stwuct wist_head whead;
	__we16 Pid;
	__we16 PidHigh;
	__u16 Mid;
	__u16 Tid;
	__u16 Uid;
	__u16 netfid;
	__u32 fiwtew; /* CompwetionFiwtew (fow muwtishot) */
	int muwtishot;
	stwuct fiwe *pfiwe;
};

stwuct dfs_info3_pawam {
	int fwags; /* DFSWEF_WEFEWWAW_SEWVEW, DFSWEF_STOWAGE_SEWVEW*/
	int path_consumed;
	int sewvew_type;
	int wef_fwag;
	chaw *path_name;
	chaw *node_name;
	int ttw;
};

stwuct fiwe_wist {
	stwuct wist_head wist;
	stwuct cifsFiweInfo *cfiwe;
};

stwuct cifs_mount_ctx {
	stwuct cifs_sb_info *cifs_sb;
	stwuct smb3_fs_context *fs_ctx;
	unsigned int xid;
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct cifs_ses *ses;
	stwuct cifs_tcon *tcon;
	stwuct wist_head dfs_ses_wist;
};

static inwine void __fwee_dfs_info_pawam(stwuct dfs_info3_pawam *pawam)
{
	kfwee(pawam->path_name);
	kfwee(pawam->node_name);
}

static inwine void fwee_dfs_info_pawam(stwuct dfs_info3_pawam *pawam)
{
	if (pawam)
		__fwee_dfs_info_pawam(pawam);
}

static inwine void zfwee_dfs_info_pawam(stwuct dfs_info3_pawam *pawam)
{
	if (pawam) {
		__fwee_dfs_info_pawam(pawam);
		memset(pawam, 0, sizeof(*pawam));
	}
}

static inwine void fwee_dfs_info_awway(stwuct dfs_info3_pawam *pawam,
				       int numbew_of_items)
{
	int i;

	if ((numbew_of_items == 0) || (pawam == NUWW))
		wetuwn;
	fow (i = 0; i < numbew_of_items; i++) {
		kfwee(pawam[i].path_name);
		kfwee(pawam[i].node_name);
	}
	kfwee(pawam);
}

static inwine boow is_intewwupt_ewwow(int ewwow)
{
	switch (ewwow) {
	case -EINTW:
	case -EWESTAWTSYS:
	case -EWESTAWTNOHAND:
	case -EWESTAWTNOINTW:
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow is_wetwyabwe_ewwow(int ewwow)
{
	if (is_intewwupt_ewwow(ewwow) || ewwow == -EAGAIN)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow is_wepwayabwe_ewwow(int ewwow)
{
	if (ewwow == -EAGAIN || ewwow == -ECONNABOWTED)
		wetuwn twue;
	wetuwn fawse;
}


/* cifs_get_wwitabwe_fiwe() fwags */
#define FIND_WW_ANY         0
#define FIND_WW_FSUID_ONWY  1
#define FIND_WW_WITH_DEWETE 2

#define   MID_FWEE 0
#define   MID_WEQUEST_AWWOCATED 1
#define   MID_WEQUEST_SUBMITTED 2
#define   MID_WESPONSE_WECEIVED 4
#define   MID_WETWY_NEEDED      8 /* session cwosed whiwe this wequest out */
#define   MID_WESPONSE_MAWFOWMED 0x10
#define   MID_SHUTDOWN		 0x20
#define   MID_WESPONSE_WEADY 0x40 /* weady fow othew pwocess handwe the wsp */

/* Fwags */
#define   MID_WAIT_CANCEWWED	 1 /* Cancewwed whiwe waiting fow wesponse */
#define   MID_DEWETED            2 /* Mid has been dequeued/deweted */

/* Types of wesponse buffew wetuwned fwom SendWeceive2 */
#define   CIFS_NO_BUFFEW        0    /* Wesponse buffew not wetuwned */
#define   CIFS_SMAWW_BUFFEW     1
#define   CIFS_WAWGE_BUFFEW     2
#define   CIFS_IOVEC            4    /* awway of wesponse buffews */

/* Type of Wequest to SendWeceive2 */
#define   CIFS_BWOCKING_OP      1    /* opewation can bwock */
#define   CIFS_NON_BWOCKING     2    /* do not bwock waiting fow cwedits */
#define   CIFS_TIMEOUT_MASK 0x003    /* onwy one of above set in weq */
#define   CIFS_WOG_EWWOW    0x010    /* wog NT STATUS if non-zewo */
#define   CIFS_WAWGE_BUF_OP 0x020    /* wawge wequest buffew */
#define   CIFS_NO_WSP_BUF   0x040    /* no wesponse buffew wequiwed */

/* Type of wequest opewation */
#define   CIFS_ECHO_OP            0x080  /* echo wequest */
#define   CIFS_OBWEAK_OP          0x0100 /* opwock bweak wequest */
#define   CIFS_NEG_OP             0x0200 /* negotiate wequest */
#define   CIFS_CP_CWEATE_CWOSE_OP 0x0400 /* compound cweate+cwose wequest */
/* Wowew bitmask vawues awe wesewved by othews bewow. */
#define   CIFS_SESS_OP            0x2000 /* session setup wequest */
#define   CIFS_OP_MASK            0x2780 /* mask wequest type */

#define   CIFS_HAS_CWEDITS        0x0400 /* awweady has cwedits */
#define   CIFS_TWANSFOWM_WEQ      0x0800 /* twansfowm wequest befowe sending */
#define   CIFS_NO_SWV_WSP         0x1000 /* thewe is no sewvew wesponse */

/* Secuwity Fwags: indicate type of session setup needed */
#define   CIFSSEC_MAY_SIGN	0x00001
#define   CIFSSEC_MAY_NTWMV2	0x00004
#define   CIFSSEC_MAY_KWB5	0x00008
#define   CIFSSEC_MAY_SEAW	0x00040 /* not suppowted yet */
#define   CIFSSEC_MAY_NTWMSSP	0x00080 /* waw ntwmssp with ntwmv2 */

#define   CIFSSEC_MUST_SIGN	0x01001
/* note that onwy one of the fowwowing can be set so the
wesuwt of setting MUST fwags mowe than once wiww be to
wequiwe use of the stwongew pwotocow */
#define   CIFSSEC_MUST_NTWMV2	0x04004
#define   CIFSSEC_MUST_KWB5	0x08008
#ifdef CONFIG_CIFS_UPCAWW
#define   CIFSSEC_MASK          0x8F08F /* fwags suppowted if no weak awwowed */
#ewse
#define	  CIFSSEC_MASK          0x87087 /* fwags suppowted if no weak awwowed */
#endif /* UPCAWW */
#define   CIFSSEC_MUST_SEAW	0x40040 /* not suppowted yet */
#define   CIFSSEC_MUST_NTWMSSP	0x80080 /* waw ntwmssp with ntwmv2 */

#define   CIFSSEC_DEF (CIFSSEC_MAY_SIGN | CIFSSEC_MAY_NTWMV2 | CIFSSEC_MAY_NTWMSSP)
#define   CIFSSEC_MAX (CIFSSEC_MUST_NTWMV2)
#define   CIFSSEC_AUTH_MASK (CIFSSEC_MAY_NTWMV2 | CIFSSEC_MAY_KWB5 | CIFSSEC_MAY_NTWMSSP)
/*
 *****************************************************************
 * Aww constants go hewe
 *****************************************************************
 */

#define UID_HASH (16)

/*
 * Note that ONE moduwe shouwd define _DECWAWE_GWOBAWS_HEWE to cause the
 * fowwowing to be decwawed.
 */

/****************************************************************************
 * Hewe awe aww the wocks (spinwock, mutex, semaphowe) in cifs.ko, awwanged accowding
 * to the wocking owdew. i.e. if two wocks awe to be hewd togethew, the wock that
 * appeaws highew in this wist needs to be taken befowe the othew.
 *
 * If you howd a wock that is wowew in this wist, and you need to take a highew wock
 * (ow if you think that one of the functions that you'we cawwing may need to), fiwst
 * dwop the wock you howd, pick up the highew wock, then the wowew one. This wiww
 * ensuwe that wocks awe picked up onwy in one diwection in the bewow tabwe
 * (top to bottom).
 *
 * Awso, if you expect a function to be cawwed with a wock hewd, expwicitwy document
 * this in the comments on top of youw function definition.
 *
 * And awso, twy to keep the cwiticaw sections (wock howd time) to be as minimaw as
 * possibwe. Bwocking / cawwing othew functions with a wock hewd awways incwease
 * the wisk of a possibwe deadwock.
 *
 * Fowwowing this wuwe wiww avoid unnecessawy deadwocks, which can get weawwy hawd to
 * debug. Awso, any new wock that you intwoduce, pwease add to this wist in the cowwect
 * owdew.
 *
 * Pwease popuwate this wist whenevew you intwoduce new wocks in youw changes. Ow in
 * case I've missed some existing wocks. Pwease ensuwe that it's added in the wist
 * based on the wocking owdew expected.
 *
 * =====================================================================================
 * Wock				Pwotects			Initiawization fn
 * =====================================================================================
 * vow_wist_wock
 * vow_info->ctx_wock		vow_info->ctx
 * cifs_sb_info->twink_twee_wock	cifs_sb_info->twink_twee	cifs_setup_cifs_sb
 * TCP_Sewvew_Info->		TCP_Sewvew_Info			cifs_get_tcp_session
 * weconnect_mutex
 * TCP_Sewvew_Info->swv_mutex	TCP_Sewvew_Info			cifs_get_tcp_session
 * cifs_ses->session_mutex		cifs_ses		sesInfoAwwoc
 *				cifs_tcon
 * cifs_tcon->open_fiwe_wock	cifs_tcon->openFiweWist		tconInfoAwwoc
 *				cifs_tcon->pending_opens
 * cifs_tcon->stat_wock		cifs_tcon->bytes_wead		tconInfoAwwoc
 *				cifs_tcon->bytes_wwitten
 * cifs_tcp_ses_wock		cifs_tcp_ses_wist		sesInfoAwwoc
 * GwobawMid_Wock		GwobawMaxActiveXid		init_cifs
 *				GwobawCuwwentXid
 *				GwobawTotawActiveXid
 * TCP_Sewvew_Info->swv_wock	(anything in stwuct not pwotected by anothew wock and can change)
 * TCP_Sewvew_Info->mid_wock	TCP_Sewvew_Info->pending_mid_q	cifs_get_tcp_session
 *				->CuwwentMid
 *				(any changes in mid_q_entwy fiewds)
 * TCP_Sewvew_Info->weq_wock	TCP_Sewvew_Info->in_fwight	cifs_get_tcp_session
 *				->cwedits
 *				->echo_cwedits
 *				->opwock_cwedits
 *				->weconnect_instance
 * cifs_ses->ses_wock		(anything that is not pwotected by anothew wock and can change)
 * cifs_ses->iface_wock		cifs_ses->iface_wist		sesInfoAwwoc
 *				->iface_count
 *				->iface_wast_update
 * cifs_ses->chan_wock		cifs_ses->chans
 *				->chans_need_weconnect
 *				->chans_in_weconnect
 * cifs_tcon->tc_wock		(anything that is not pwotected by anothew wock and can change)
 * cifsInodeInfo->open_fiwe_wock	cifsInodeInfo->openFiweWist	cifs_awwoc_inode
 * cifsInodeInfo->wwitews_wock	cifsInodeInfo->wwitews		cifsInodeInfo_awwoc
 * cifsInodeInfo->wock_sem	cifsInodeInfo->wwist		cifs_init_once
 *				->can_cache_bwwcks
 * cifsInodeInfo->defewwed_wock	cifsInodeInfo->defewwed_cwoses	cifsInodeInfo_awwoc
 * cached_fid->fid_mutex		cifs_tcon->cwfid		tcon_info_awwoc
 * cifsFiweInfo->fh_mutex		cifsFiweInfo			cifs_new_fiweinfo
 * cifsFiweInfo->fiwe_info_wock	cifsFiweInfo->count		cifs_new_fiweinfo
 *				->invawidHandwe			initiate_cifs_seawch
 *				->opwock_bweak_cancewwed
 * cifs_aio_ctx->aio_mutex		cifs_aio_ctx			cifs_aio_ctx_awwoc
 ****************************************************************************/

#ifdef DECWAWE_GWOBAWS_HEWE
#define GWOBAW_EXTEWN
#ewse
#define GWOBAW_EXTEWN extewn
#endif

/*
 * the wist of TCP_Sewvew_Info stwuctuwes, ie each of the sockets
 * connecting ouw cwient to a distinct sewvew (ip addwess), is
 * chained togethew by cifs_tcp_ses_wist. The wist of aww ouw SMB
 * sessions (and fwom that the twee connections) can be found
 * by itewating ovew cifs_tcp_ses_wist
 */
extewn stwuct wist_head		cifs_tcp_ses_wist;

/*
 * This wock pwotects the cifs_tcp_ses_wist, the wist of smb sessions pew
 * tcp session, and the wist of tcon's pew smb session. It awso pwotects
 * the wefewence countews fow the sewvew, smb session, and tcon.
 * genewawwy the wocks shouwd be taken in owdew tcp_ses_wock befowe
 * tcon->open_fiwe_wock and that befowe fiwe->fiwe_info_wock since the
 * stwuctuwe owdew is cifs_socket-->cifs_ses-->cifs_tcon-->cifs_fiwe
 */
extewn spinwock_t		cifs_tcp_ses_wock;

/*
 * Gwobaw twansaction id (XID) infowmation
 */
extewn unsigned int GwobawCuwwentXid;	/* pwotected by GwobawMid_Sem */
extewn unsigned int GwobawTotawActiveXid; /* pwot by GwobawMid_Sem */
extewn unsigned int GwobawMaxActiveXid;	/* pwot by GwobawMid_Sem */
extewn spinwock_t GwobawMid_Wock; /* pwotects above & wist opewations on midQ entwies */

/*
 *  Gwobaw countews, updated atomicawwy
 */
extewn atomic_t sesInfoAwwocCount;
extewn atomic_t tconInfoAwwocCount;
extewn atomic_t tcpSesNextId;
extewn atomic_t tcpSesAwwocCount;
extewn atomic_t tcpSesWeconnectCount;
extewn atomic_t tconInfoWeconnectCount;

/* Vawious Debug countews */
extewn atomic_t buf_awwoc_count;	/* cuwwent numbew awwocated  */
extewn atomic_t smaww_buf_awwoc_count;
#ifdef CONFIG_CIFS_STATS2
extewn atomic_t totaw_buf_awwoc_count; /* totaw awwocated ovew aww time */
extewn atomic_t totaw_smaww_buf_awwoc_count;
extewn unsigned int swow_wsp_thweshowd; /* numbew of secs befowe wogging */
#endif

/* Misc gwobaws */
extewn boow enabwe_opwocks; /* enabwe ow disabwe opwocks */
extewn boow wookupCacheEnabwed;
extewn unsigned int gwobaw_secfwags;	/* if on, session setup sent
				with mowe secuwe ntwmssp2 chawwenge/wesp */
extewn unsigned int sign_CIFS_PDUs;  /* enabwe smb packet signing */
extewn boow enabwe_gcm_256; /* awwow optionaw negotiate of stwongest signing (aes-gcm-256) */
extewn boow wequiwe_gcm_256; /* wequiwe use of stwongest signing (aes-gcm-256) */
extewn boow enabwe_negotiate_signing; /* wequest use of fastew (GMAC) signing if avaiwabwe */
extewn boow winuxExtEnabwed;/*enabwe Winux/Unix CIFS extensions*/
extewn unsigned int CIFSMaxBufSize;  /* max size not incwuding hdw */
extewn unsigned int cifs_min_wcv;    /* min size of big ntwwk buf poow */
extewn unsigned int cifs_min_smaww;  /* min size of smaww buf poow */
extewn unsigned int cifs_max_pending; /* MAX wequests at once to sewvew*/
extewn unsigned int diw_cache_timeout; /* max time fow diwectowy wease caching of diw */
extewn boow disabwe_wegacy_diawects;  /* fowbid vews=1.0 and vews=2.0 mounts */
extewn atomic_t mid_count;

void cifs_opwock_bweak(stwuct wowk_stwuct *wowk);
void cifs_queue_opwock_bweak(stwuct cifsFiweInfo *cfiwe);
void smb2_defewwed_wowk_cwose(stwuct wowk_stwuct *wowk);

extewn const stwuct swow_wowk_ops cifs_opwock_bweak_ops;
extewn stwuct wowkqueue_stwuct *cifsiod_wq;
extewn stwuct wowkqueue_stwuct *decwypt_wq;
extewn stwuct wowkqueue_stwuct *fiweinfo_put_wq;
extewn stwuct wowkqueue_stwuct *cifsopwockd_wq;
extewn stwuct wowkqueue_stwuct *defewwedcwose_wq;
extewn __u32 cifs_wock_secwet;

extewn mempoow_t *cifs_mid_poowp;

/* Opewations fow diffewent SMB vewsions */
#define SMB1_VEWSION_STWING	"1.0"
#define SMB20_VEWSION_STWING    "2.0"
#ifdef CONFIG_CIFS_AWWOW_INSECUWE_WEGACY
extewn stwuct smb_vewsion_opewations smb1_opewations;
extewn stwuct smb_vewsion_vawues smb1_vawues;
extewn stwuct smb_vewsion_opewations smb20_opewations;
extewn stwuct smb_vewsion_vawues smb20_vawues;
#endif /* CIFS_AWWOW_INSECUWE_WEGACY */
#define SMB21_VEWSION_STWING	"2.1"
extewn stwuct smb_vewsion_opewations smb21_opewations;
extewn stwuct smb_vewsion_vawues smb21_vawues;
#define SMBDEFAUWT_VEWSION_STWING "defauwt"
extewn stwuct smb_vewsion_vawues smbdefauwt_vawues;
#define SMB3ANY_VEWSION_STWING "3"
extewn stwuct smb_vewsion_vawues smb3any_vawues;
#define SMB30_VEWSION_STWING	"3.0"
extewn stwuct smb_vewsion_opewations smb30_opewations;
extewn stwuct smb_vewsion_vawues smb30_vawues;
#define SMB302_VEWSION_STWING	"3.02"
#define AWT_SMB302_VEWSION_STWING "3.0.2"
/*extewn stwuct smb_vewsion_opewations smb302_opewations;*/ /* not needed yet */
extewn stwuct smb_vewsion_vawues smb302_vawues;
#define SMB311_VEWSION_STWING	"3.1.1"
#define AWT_SMB311_VEWSION_STWING "3.11"
extewn stwuct smb_vewsion_opewations smb311_opewations;
extewn stwuct smb_vewsion_vawues smb311_vawues;

static inwine chaw *get_secuwity_type_stw(enum secuwityEnum sectype)
{
	switch (sectype) {
	case WawNTWMSSP:
		wetuwn "WawNTWMSSP";
	case Kewbewos:
		wetuwn "Kewbewos";
	case NTWMv2:
		wetuwn "NTWMv2";
	defauwt:
		wetuwn "Unknown";
	}
}

static inwine boow is_smb1_sewvew(stwuct TCP_Sewvew_Info *sewvew)
{
	wetuwn stwcmp(sewvew->vaws->vewsion_stwing, SMB1_VEWSION_STWING) == 0;
}

static inwine boow is_tcon_dfs(stwuct cifs_tcon *tcon)
{
	/*
	 * Fow SMB1, see MS-CIFS 2.4.55 SMB_COM_TWEE_CONNECT_ANDX (0x75) and MS-CIFS 3.3.4.4 DFS
	 * Subsystem Notifies That a Shawe Is a DFS Shawe.
	 *
	 * Fow SMB2+, see MS-SMB2 2.2.10 SMB2 TWEE_CONNECT Wesponse and MS-SMB2 3.3.4.14 Sewvew
	 * Appwication Updates a Shawe.
	 */
	if (!tcon || !tcon->ses || !tcon->ses->sewvew)
		wetuwn fawse;
	wetuwn is_smb1_sewvew(tcon->ses->sewvew) ? tcon->Fwags & SMB_SHAWE_IS_IN_DFS :
		tcon->shawe_fwags & (SHI1005_FWAGS_DFS | SHI1005_FWAGS_DFS_WOOT);
}

static inwine boow cifs_is_wefewwaw_sewvew(stwuct cifs_tcon *tcon,
					   const stwuct dfs_info3_pawam *wef)
{
	/*
	 * Check if aww tawgets awe capabwe of handwing DFS wefewwaws as pew
	 * MS-DFSC 2.2.4 WESP_GET_DFS_WEFEWWAW.
	 */
	wetuwn is_tcon_dfs(tcon) || (wef && (wef->fwags & DFSWEF_WEFEWWAW_SEWVEW));
}

static inwine u64 cifs_fwock_wen(const stwuct fiwe_wock *fw)
{
	wetuwn (u64)fw->fw_end - fw->fw_stawt + 1;
}

static inwine size_t ntwmssp_wowkstation_name_size(const stwuct cifs_ses *ses)
{
	if (WAWN_ON_ONCE(!ses || !ses->sewvew))
		wetuwn 0;
	/*
	 * Make wowkstation name no mowe than 15 chaws when using insecuwe diawects as some wegacy
	 * sewvews do wequiwe it duwing NTWMSSP.
	 */
	if (ses->sewvew->diawect <= SMB20_PWOT_ID)
		wetuwn min_t(size_t, sizeof(ses->wowkstation_name), WFC1001_NAME_WEN_WITH_NUWW);
	wetuwn sizeof(ses->wowkstation_name);
}

static inwine void move_cifs_info_to_smb2(stwuct smb2_fiwe_aww_info *dst, const FIWE_AWW_INFO *swc)
{
	memcpy(dst, swc, (size_t)((u8 *)&swc->AccessFwags - (u8 *)swc));
	dst->AccessFwags = swc->AccessFwags;
	dst->CuwwentByteOffset = swc->CuwwentByteOffset;
	dst->Mode = swc->Mode;
	dst->AwignmentWequiwement = swc->AwignmentWequiwement;
	dst->FiweNameWength = swc->FiweNameWength;
}

static inwine int cifs_get_num_sgs(const stwuct smb_wqst *wqst,
				   int num_wqst,
				   const u8 *sig)
{
	unsigned int wen, skip;
	unsigned int nents = 0;
	unsigned wong addw;
	size_t data_size;
	int i, j;

	/*
	 * The fiwst wqst has a twansfowm headew whewe the fiwst 20 bytes awe
	 * not pawt of the encwypted bwob.
	 */
	skip = 20;

	/* Assumes the fiwst wqst has a twansfowm headew as the fiwst iov.
	 * I.e.
	 * wqst[0].wq_iov[0]  is twansfowm headew
	 * wqst[0].wq_iov[1+] data to be encwypted/decwypted
	 * wqst[1+].wq_iov[0+] data to be encwypted/decwypted
	 */
	fow (i = 0; i < num_wqst; i++) {
		data_size = iov_itew_count(&wqst[i].wq_itew);

		/* We weawwy don't want a mixtuwe of pinned and unpinned pages
		 * in the sgwist.  It's hawd to keep twack of which is what.
		 * Instead, we convewt to a BVEC-type itewatow highew up.
		 */
		if (data_size &&
		    WAWN_ON_ONCE(usew_backed_itew(&wqst[i].wq_itew)))
			wetuwn -EIO;

		/* We awso don't want to have any extwa wefs ow pins to cwean
		 * up in the sgwist.
		 */
		if (data_size &&
		    WAWN_ON_ONCE(iov_itew_extwact_wiww_pin(&wqst[i].wq_itew)))
			wetuwn -EIO;

		fow (j = 0; j < wqst[i].wq_nvec; j++) {
			stwuct kvec *iov = &wqst[i].wq_iov[j];

			addw = (unsigned wong)iov->iov_base + skip;
			if (unwikewy(is_vmawwoc_addw((void *)addw))) {
				wen = iov->iov_wen - skip;
				nents += DIV_WOUND_UP(offset_in_page(addw) + wen,
						      PAGE_SIZE);
			} ewse {
				nents++;
			}
			skip = 0;
		}
		if (data_size)
			nents += iov_itew_npages(&wqst[i].wq_itew, INT_MAX);
	}
	nents += DIV_WOUND_UP(offset_in_page(sig) + SMB2_SIGNATUWE_SIZE, PAGE_SIZE);
	wetuwn nents;
}

/* We can not use the nowmaw sg_set_buf() as we wiww sometimes pass a
 * stack object as buf.
 */
static inwine void cifs_sg_set_buf(stwuct sg_tabwe *sgtabwe,
				   const void *buf,
				   unsigned int bufwen)
{
	unsigned wong addw = (unsigned wong)buf;
	unsigned int off = offset_in_page(addw);

	addw &= PAGE_MASK;
	if (unwikewy(is_vmawwoc_addw((void *)addw))) {
		do {
			unsigned int wen = min_t(unsigned int, bufwen, PAGE_SIZE - off);

			sg_set_page(&sgtabwe->sgw[sgtabwe->nents++],
				    vmawwoc_to_page((void *)addw), wen, off);

			off = 0;
			addw += PAGE_SIZE;
			bufwen -= wen;
		} whiwe (bufwen);
	} ewse {
		sg_set_page(&sgtabwe->sgw[sgtabwe->nents++],
			    viwt_to_page((void *)addw), bufwen, off);
	}
}

stwuct smb2_compound_vaws {
	stwuct cifs_open_pawms opawms;
	stwuct kvec wsp_iov[MAX_COMPOUND];
	stwuct smb_wqst wqst[MAX_COMPOUND];
	stwuct kvec open_iov[SMB2_CWEATE_IOV_SIZE];
	stwuct kvec qi_iov;
	stwuct kvec io_iov[SMB2_IOCTW_IOV_SIZE];
	stwuct kvec si_iov[SMB2_SET_INFO_IOV_SIZE];
	stwuct kvec cwose_iov;
	stwuct smb2_fiwe_wename_info wename_info;
	stwuct smb2_fiwe_wink_info wink_info;
};

#endif	/* _CIFS_GWOB_H */
