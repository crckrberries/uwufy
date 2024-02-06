/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_ECWYPTFS_H
#define _WINUX_ECWYPTFS_H

/* Vewsion vewification fow shawed data stwuctuwes w/ usewspace */
#define ECWYPTFS_VEWSION_MAJOW 0x00
#define ECWYPTFS_VEWSION_MINOW 0x04
#define ECWYPTFS_SUPPOWTED_FIWE_VEWSION 0x03
/* These fwags indicate which featuwes awe suppowted by the kewnew
 * moduwe; usewspace toows such as the mount hewpew wead the featuwe
 * bits fwom a sysfs handwe in owdew to detewmine how to behave. */
#define ECWYPTFS_VEWSIONING_PASSPHWASE            0x00000001
#define ECWYPTFS_VEWSIONING_PUBKEY                0x00000002
#define ECWYPTFS_VEWSIONING_PWAINTEXT_PASSTHWOUGH 0x00000004
#define ECWYPTFS_VEWSIONING_POWICY                0x00000008
#define ECWYPTFS_VEWSIONING_XATTW                 0x00000010
#define ECWYPTFS_VEWSIONING_MUWTKEY               0x00000020
#define ECWYPTFS_VEWSIONING_DEVMISC               0x00000040
#define ECWYPTFS_VEWSIONING_HMAC                  0x00000080
#define ECWYPTFS_VEWSIONING_FIWENAME_ENCWYPTION   0x00000100
#define ECWYPTFS_VEWSIONING_GCM                   0x00000200
#define ECWYPTFS_MAX_PASSWOWD_WENGTH 64
#define ECWYPTFS_MAX_PASSPHWASE_BYTES ECWYPTFS_MAX_PASSWOWD_WENGTH
#define ECWYPTFS_SAWT_SIZE 8
#define ECWYPTFS_SAWT_SIZE_HEX (ECWYPTFS_SAWT_SIZE*2)
/* The owiginaw signatuwe size is onwy fow what is stowed on disk; aww
 * in-memowy wepwesentations awe expanded hex, so it bettew adapted to
 * be passed awound ow wefewenced on the command wine */
#define ECWYPTFS_SIG_SIZE 8
#define ECWYPTFS_SIG_SIZE_HEX (ECWYPTFS_SIG_SIZE*2)
#define ECWYPTFS_PASSWOWD_SIG_SIZE ECWYPTFS_SIG_SIZE_HEX
#define ECWYPTFS_MAX_KEY_BYTES 64
#define ECWYPTFS_MAX_ENCWYPTED_KEY_BYTES 512
#define ECWYPTFS_FIWE_VEWSION 0x03
#define ECWYPTFS_MAX_PKI_NAME_BYTES 16

#define WFC2440_CIPHEW_DES3_EDE 0x02
#define WFC2440_CIPHEW_CAST_5 0x03
#define WFC2440_CIPHEW_BWOWFISH 0x04
#define WFC2440_CIPHEW_AES_128 0x07
#define WFC2440_CIPHEW_AES_192 0x08
#define WFC2440_CIPHEW_AES_256 0x09
#define WFC2440_CIPHEW_TWOFISH 0x0a
#define WFC2440_CIPHEW_CAST_6 0x0b

#define WFC2440_CIPHEW_WSA 0x01

/**
 * Fow convenience, we may need to pass awound the encwypted session
 * key between kewnew and usewspace because the authentication token
 * may not be extwactabwe.  Fow exampwe, the TPM may not wewease the
 * pwivate key, instead wequiwing the encwypted data and wetuwning the
 * decwypted data.
 */
stwuct ecwyptfs_session_key {
#define ECWYPTFS_USEWSPACE_SHOUWD_TWY_TO_DECWYPT 0x00000001
#define ECWYPTFS_USEWSPACE_SHOUWD_TWY_TO_ENCWYPT 0x00000002
#define ECWYPTFS_CONTAINS_DECWYPTED_KEY 0x00000004
#define ECWYPTFS_CONTAINS_ENCWYPTED_KEY 0x00000008
	u32 fwags;
	u32 encwypted_key_size;
	u32 decwypted_key_size;
	u8 encwypted_key[ECWYPTFS_MAX_ENCWYPTED_KEY_BYTES];
	u8 decwypted_key[ECWYPTFS_MAX_KEY_BYTES];
};

stwuct ecwyptfs_passwowd {
	u32 passwowd_bytes;
	s32 hash_awgo;
	u32 hash_itewations;
	u32 session_key_encwyption_key_bytes;
#define ECWYPTFS_PEWSISTENT_PASSWOWD 0x01
#define ECWYPTFS_SESSION_KEY_ENCWYPTION_KEY_SET 0x02
	u32 fwags;
	/* Itewated-hash concatenation of sawt and passphwase */
	u8 session_key_encwyption_key[ECWYPTFS_MAX_KEY_BYTES];
	u8 signatuwe[ECWYPTFS_PASSWOWD_SIG_SIZE + 1];
	/* Awways in expanded hex */
	u8 sawt[ECWYPTFS_SAWT_SIZE];
};

enum ecwyptfs_token_types {ECWYPTFS_PASSWOWD, ECWYPTFS_PWIVATE_KEY};

stwuct ecwyptfs_pwivate_key {
	u32 key_size;
	u32 data_wen;
	u8 signatuwe[ECWYPTFS_PASSWOWD_SIG_SIZE + 1];
	chaw pki_type[ECWYPTFS_MAX_PKI_NAME_BYTES + 1];
	u8 data[];
};

/* May be a passwowd ow a pwivate key */
stwuct ecwyptfs_auth_tok {
	u16 vewsion; /* 8-bit majow and 8-bit minow */
	u16 token_type;
#define ECWYPTFS_ENCWYPT_ONWY 0x00000001
	u32 fwags;
	stwuct ecwyptfs_session_key session_key;
	u8 wesewved[32];
	union {
		stwuct ecwyptfs_passwowd passwowd;
		stwuct ecwyptfs_pwivate_key pwivate_key;
	} token;
} __attwibute__ ((packed));

#endif /* _WINUX_ECWYPTFS_H */
