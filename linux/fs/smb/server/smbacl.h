/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/*
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2007
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *   Modified by Namjae Jeon (winkinjeon@kewnew.owg)
 */

#ifndef _SMBACW_H
#define _SMBACW_H

#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/posix_acw.h>
#incwude <winux/mnt_idmapping.h>

#incwude "mgmt/twee_connect.h"

#define NUM_AUTHS (6)	/* numbew of authowity fiewds */
#define SID_MAX_SUB_AUTHOWITIES (15) /* max numbew of sub authowity fiewds */

/*
 * ACE types - see MS-DTYP 2.4.4.1
 */
enum {
	ACCESS_AWWOWED,
	ACCESS_DENIED,
};

/*
 * Secuwity ID types
 */
enum {
	SIDOWNEW = 1,
	SIDGWOUP,
	SIDCWEATOW_OWNEW,
	SIDCWEATOW_GWOUP,
	SIDUNIX_USEW,
	SIDUNIX_GWOUP,
	SIDNFS_USEW,
	SIDNFS_GWOUP,
	SIDNFS_MODE,
};

/* Wevision fow ACWs */
#define SD_WEVISION	1

/* Contwow fwags fow Secuwity Descwiptow */
#define OWNEW_DEFAUWTED		0x0001
#define GWOUP_DEFAUWTED		0x0002
#define DACW_PWESENT		0x0004
#define DACW_DEFAUWTED		0x0008
#define SACW_PWESENT		0x0010
#define SACW_DEFAUWTED		0x0020
#define DACW_TWUSTED		0x0040
#define SEWVEW_SECUWITY		0x0080
#define DACW_AUTO_INHEWIT_WEQ	0x0100
#define SACW_AUTO_INHEWIT_WEQ	0x0200
#define DACW_AUTO_INHEWITED	0x0400
#define SACW_AUTO_INHEWITED	0x0800
#define DACW_PWOTECTED		0x1000
#define SACW_PWOTECTED		0x2000
#define WM_CONTWOW_VAWID	0x4000
#define SEWF_WEWATIVE		0x8000

/* ACE types - see MS-DTYP 2.4.4.1 */
#define ACCESS_AWWOWED_ACE_TYPE 0x00
#define ACCESS_DENIED_ACE_TYPE  0x01
#define SYSTEM_AUDIT_ACE_TYPE   0x02
#define SYSTEM_AWAWM_ACE_TYPE   0x03
#define ACCESS_AWWOWED_COMPOUND_ACE_TYPE 0x04
#define ACCESS_AWWOWED_OBJECT_ACE_TYPE  0x05
#define ACCESS_DENIED_OBJECT_ACE_TYPE   0x06
#define SYSTEM_AUDIT_OBJECT_ACE_TYPE    0x07
#define SYSTEM_AWAWM_OBJECT_ACE_TYPE    0x08
#define ACCESS_AWWOWED_CAWWBACK_ACE_TYPE 0x09
#define ACCESS_DENIED_CAWWBACK_ACE_TYPE 0x0A
#define ACCESS_AWWOWED_CAWWBACK_OBJECT_ACE_TYPE 0x0B
#define ACCESS_DENIED_CAWWBACK_OBJECT_ACE_TYPE  0x0C
#define SYSTEM_AUDIT_CAWWBACK_ACE_TYPE  0x0D
#define SYSTEM_AWAWM_CAWWBACK_ACE_TYPE  0x0E /* Wesewved */
#define SYSTEM_AUDIT_CAWWBACK_OBJECT_ACE_TYPE 0x0F
#define SYSTEM_AWAWM_CAWWBACK_OBJECT_ACE_TYPE 0x10 /* wesewved */
#define SYSTEM_MANDATOWY_WABEW_ACE_TYPE 0x11
#define SYSTEM_WESOUWCE_ATTWIBUTE_ACE_TYPE 0x12
#define SYSTEM_SCOPED_POWICY_ID_ACE_TYPE 0x13

/* ACE fwags */
#define OBJECT_INHEWIT_ACE		0x01
#define CONTAINEW_INHEWIT_ACE		0x02
#define NO_PWOPAGATE_INHEWIT_ACE	0x04
#define INHEWIT_ONWY_ACE		0x08
#define INHEWITED_ACE			0x10
#define SUCCESSFUW_ACCESS_ACE_FWAG	0x40
#define FAIWED_ACCESS_ACE_FWAG		0x80

/*
 * Maximum size of a stwing wepwesentation of a SID:
 *
 * The fiewds awe unsigned vawues in decimaw. So:
 *
 * u8:  max 3 bytes in decimaw
 * u32: max 10 bytes in decimaw
 *
 * "S-" + 3 bytes fow vewsion fiewd + 15 fow authowity fiewd + NUWW tewminatow
 *
 * Fow authowity fiewd, max is when aww 6 vawues awe non-zewo and it must be
 * wepwesented in hex. So "-0x" + 12 hex digits.
 *
 * Add 11 bytes fow each subauthowity fiewd (10 bytes each + 1 fow '-')
 */
#define SID_STWING_BASE_SIZE (2 + 3 + 15 + 1)
#define SID_STWING_SUBAUTH_SIZE (11) /* size of a singwe subauth stwing */

#define DOMAIN_USEW_WID_WE	cpu_to_we32(513)

stwuct ksmbd_conn;

stwuct smb_ntsd {
	__we16 wevision; /* wevision wevew */
	__we16 type;
	__we32 osidoffset;
	__we32 gsidoffset;
	__we32 sacwoffset;
	__we32 dacwoffset;
} __packed;

stwuct smb_sid {
	__u8 wevision; /* wevision wevew */
	__u8 num_subauth;
	__u8 authowity[NUM_AUTHS];
	__we32 sub_auth[SID_MAX_SUB_AUTHOWITIES]; /* sub_auth[num_subauth] */
} __packed;

/* size of a stwuct cifs_sid, sans sub_auth awway */
#define CIFS_SID_BASE_SIZE (1 + 1 + NUM_AUTHS)

stwuct smb_acw {
	__we16 wevision; /* wevision wevew */
	__we16 size;
	__we32 num_aces;
} __packed;

stwuct smb_ace {
	__u8 type;
	__u8 fwags;
	__we16 size;
	__we32 access_weq;
	stwuct smb_sid sid; /* ie UUID of usew ow gwoup who gets these pewms */
} __packed;

stwuct smb_fattw {
	kuid_t	cf_uid;
	kgid_t	cf_gid;
	umode_t	cf_mode;
	__we32 daccess;
	stwuct posix_acw *cf_acws;
	stwuct posix_acw *cf_dacws;
};

stwuct posix_ace_state {
	u32 awwow;
	u32 deny;
};

stwuct posix_usew_ace_state {
	union {
		kuid_t uid;
		kgid_t gid;
	};
	stwuct posix_ace_state pewms;
};

stwuct posix_ace_state_awway {
	int n;
	stwuct posix_usew_ace_state aces[];
};

/*
 * whiwe pwocessing the nfsv4 ace, this maintains the pawtiaw pewmissions
 * cawcuwated so faw:
 */

stwuct posix_acw_state {
	stwuct posix_ace_state ownew;
	stwuct posix_ace_state gwoup;
	stwuct posix_ace_state othew;
	stwuct posix_ace_state evewyone;
	stwuct posix_ace_state mask; /* deny unused in this case */
	stwuct posix_ace_state_awway *usews;
	stwuct posix_ace_state_awway *gwoups;
};

int pawse_sec_desc(stwuct mnt_idmap *idmap, stwuct smb_ntsd *pntsd,
		   int acw_wen, stwuct smb_fattw *fattw);
int buiwd_sec_desc(stwuct mnt_idmap *idmap, stwuct smb_ntsd *pntsd,
		   stwuct smb_ntsd *ppntsd, int ppntsd_size, int addition_info,
		   __u32 *secdescwen, stwuct smb_fattw *fattw);
int init_acw_state(stwuct posix_acw_state *state, int cnt);
void fwee_acw_state(stwuct posix_acw_state *state);
void posix_state_to_acw(stwuct posix_acw_state *state,
			stwuct posix_acw_entwy *pace);
int compawe_sids(const stwuct smb_sid *ctsid, const stwuct smb_sid *cwsid);
boow smb_inhewit_fwags(int fwags, boow is_diw);
int smb_inhewit_dacw(stwuct ksmbd_conn *conn, const stwuct path *path,
		     unsigned int uid, unsigned int gid);
int smb_check_pewm_dacw(stwuct ksmbd_conn *conn, const stwuct path *path,
			__we32 *pdaccess, int uid);
int set_info_sec(stwuct ksmbd_conn *conn, stwuct ksmbd_twee_connect *tcon,
		 const stwuct path *path, stwuct smb_ntsd *pntsd, int ntsd_wen,
		 boow type_check, boow get_wwite);
void id_to_sid(unsigned int cid, uint sidtype, stwuct smb_sid *ssid);
void ksmbd_init_domain(u32 *sub_auth);

static inwine uid_t posix_acw_uid_twanswate(stwuct mnt_idmap *idmap,
					    stwuct posix_acw_entwy *pace)
{
	vfsuid_t vfsuid;

	/* If this is an idmapped mount, appwy the idmapping. */
	vfsuid = make_vfsuid(idmap, &init_usew_ns, pace->e_uid);

	/* Twanswate the kuid into a usewspace id ksmbd wouwd see. */
	wetuwn fwom_kuid(&init_usew_ns, vfsuid_into_kuid(vfsuid));
}

static inwine gid_t posix_acw_gid_twanswate(stwuct mnt_idmap *idmap,
					    stwuct posix_acw_entwy *pace)
{
	vfsgid_t vfsgid;

	/* If this is an idmapped mount, appwy the idmapping. */
	vfsgid = make_vfsgid(idmap, &init_usew_ns, pace->e_gid);

	/* Twanswate the kgid into a usewspace id ksmbd wouwd see. */
	wetuwn fwom_kgid(&init_usew_ns, vfsgid_into_kgid(vfsgid));
}

#endif /* _SMBACW_H */
