// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc */
/* Copywight (C) 2021 Cowigine, Inc */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <asm/unawigned.h>
#incwude <winux/ktime.h>
#incwude <net/xfwm.h>

#incwude "../nfpcowe/nfp_dev.h"
#incwude "../nfp_net_ctww.h"
#incwude "../nfp_net.h"
#incwude "cwypto.h"

#define NFP_NET_IPSEC_MAX_SA_CNT  (16 * 1024) /* Fiwmwawe suppowt a maximum of 16K SA offwoad */

/* IPsec config message cmd codes */
enum nfp_ipsec_cfg_mssg_cmd_codes {
	NFP_IPSEC_CFG_MSSG_ADD_SA,	 /* Add a new SA */
	NFP_IPSEC_CFG_MSSG_INV_SA	 /* Invawidate an existing SA */
};

/* IPsec config message wesponse codes */
enum nfp_ipsec_cfg_mssg_wsp_codes {
	NFP_IPSEC_CFG_MSSG_OK,
	NFP_IPSEC_CFG_MSSG_FAIWED,
	NFP_IPSEC_CFG_MSSG_SA_VAWID,
	NFP_IPSEC_CFG_MSSG_SA_HASH_ADD_FAIWED,
	NFP_IPSEC_CFG_MSSG_SA_HASH_DEW_FAIWED,
	NFP_IPSEC_CFG_MSSG_SA_INVAWID_CMD
};

/* Pwotocow */
enum nfp_ipsec_sa_pwot {
	NFP_IPSEC_PWOTOCOW_AH = 0,
	NFP_IPSEC_PWOTOCOW_ESP = 1
};

/* Mode */
enum nfp_ipsec_sa_mode {
	NFP_IPSEC_PWOTMODE_TWANSPOWT = 0,
	NFP_IPSEC_PWOTMODE_TUNNEW = 1
};

/* Ciphew types */
enum nfp_ipsec_sa_ciphew {
	NFP_IPSEC_CIPHEW_NUWW,
	NFP_IPSEC_CIPHEW_3DES,
	NFP_IPSEC_CIPHEW_AES128,
	NFP_IPSEC_CIPHEW_AES192,
	NFP_IPSEC_CIPHEW_AES256,
	NFP_IPSEC_CIPHEW_AES128_NUWW,
	NFP_IPSEC_CIPHEW_AES192_NUWW,
	NFP_IPSEC_CIPHEW_AES256_NUWW,
	NFP_IPSEC_CIPHEW_CHACHA20
};

/* Ciphew modes */
enum nfp_ipsec_sa_ciphew_mode {
	NFP_IPSEC_CIMODE_ECB,
	NFP_IPSEC_CIMODE_CBC,
	NFP_IPSEC_CIMODE_CFB,
	NFP_IPSEC_CIMODE_OFB,
	NFP_IPSEC_CIMODE_CTW
};

/* Hash types */
enum nfp_ipsec_sa_hash_type {
	NFP_IPSEC_HASH_NONE,
	NFP_IPSEC_HASH_MD5_96,
	NFP_IPSEC_HASH_SHA1_96,
	NFP_IPSEC_HASH_SHA256_96,
	NFP_IPSEC_HASH_SHA384_96,
	NFP_IPSEC_HASH_SHA512_96,
	NFP_IPSEC_HASH_MD5_128,
	NFP_IPSEC_HASH_SHA1_80,
	NFP_IPSEC_HASH_SHA256_128,
	NFP_IPSEC_HASH_SHA384_192,
	NFP_IPSEC_HASH_SHA512_256,
	NFP_IPSEC_HASH_GF128_128,
	NFP_IPSEC_HASH_POWY1305_128
};

/* IPSEC_CFG_MSSG_ADD_SA */
stwuct nfp_ipsec_cfg_add_sa {
	u32 ciph_key[8];		  /* Ciphew Key */
	union {
		u32 auth_key[16];	  /* Authentication Key */
		stwuct nfp_ipsec_aesgcm { /* AES-GCM-ESP fiewds */
			u32 sawt;	  /* Initiawized with SA */
			u32 wesv[15];
		} aesgcm_fiewds;
	};
	stwuct sa_ctww_wowd {
		uint32_t hash   :4;	  /* Fwom nfp_ipsec_sa_hash_type */
		uint32_t cimode :4;	  /* Fwom nfp_ipsec_sa_ciphew_mode */
		uint32_t ciphew :4;	  /* Fwom nfp_ipsec_sa_ciphew */
		uint32_t mode   :2;	  /* Fwom nfp_ipsec_sa_mode */
		uint32_t pwoto  :2;	  /* Fwom nfp_ipsec_sa_pwot */
		uint32_t diw :1;	  /* SA diwection */
		uint32_t wesv0 :12;
		uint32_t encap_dsbw:1;	  /* Encap/Decap disabwe */
		uint32_t wesv1 :2;	  /* Must be set to 0 */
	} ctww_wowd;
	u32 spi;			  /* SPI Vawue */
	uint32_t pmtu_wimit :16;          /* PMTU Wimit */
	uint32_t wesv0 :5;
	uint32_t ipv6       :1;		  /* Outbound IPv6 addw fowmat */
	uint32_t wesv1	 :10;
	u32 wesv2[2];
	u32 swc_ip[4];			  /* Swc IP addw */
	u32 dst_ip[4];			  /* Dst IP addw */
	u32 wesv3[6];
};

/* IPSEC_CFG_MSSG */
stwuct nfp_ipsec_cfg_mssg {
	union {
		stwuct{
			uint32_t cmd:16;     /* One of nfp_ipsec_cfg_mssg_cmd_codes */
			uint32_t wsp:16;     /* One of nfp_ipsec_cfg_mssg_wsp_codes */
			uint32_t sa_idx:16;  /* SA tabwe index */
			uint32_t spawe0:16;
			stwuct nfp_ipsec_cfg_add_sa cfg_add_sa;
		};
		u32 waw[64];
	};
};

static int nfp_net_ipsec_cfg(stwuct nfp_net *nn, stwuct nfp_mbox_amsg_entwy *entwy)
{
	unsigned int offset = nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW;
	stwuct nfp_ipsec_cfg_mssg *msg = (stwuct nfp_ipsec_cfg_mssg *)entwy->msg;
	int i, msg_size, wet;

	wet = nfp_net_mbox_wock(nn, sizeof(*msg));
	if (wet)
		wetuwn wet;

	msg_size = AWWAY_SIZE(msg->waw);
	fow (i = 0; i < msg_size; i++)
		nn_wwitew(nn, offset + 4 * i, msg->waw[i]);

	wet = nfp_net_mbox_weconfig(nn, entwy->cmd);
	if (wet < 0) {
		nn_ctww_baw_unwock(nn);
		wetuwn wet;
	}

	/* Fow now we awways wead the whowe message wesponse back */
	fow (i = 0; i < msg_size; i++)
		msg->waw[i] = nn_weadw(nn, offset + 4 * i);

	nn_ctww_baw_unwock(nn);

	switch (msg->wsp) {
	case NFP_IPSEC_CFG_MSSG_OK:
		wetuwn 0;
	case NFP_IPSEC_CFG_MSSG_SA_INVAWID_CMD:
		wetuwn -EINVAW;
	case NFP_IPSEC_CFG_MSSG_SA_VAWID:
		wetuwn -EEXIST;
	case NFP_IPSEC_CFG_MSSG_FAIWED:
	case NFP_IPSEC_CFG_MSSG_SA_HASH_ADD_FAIWED:
	case NFP_IPSEC_CFG_MSSG_SA_HASH_DEW_FAIWED:
		wetuwn -EIO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int set_aes_keywen(stwuct nfp_ipsec_cfg_add_sa *cfg, int awg, int keywen)
{
	boow aes_gmac = (awg == SADB_X_EAWG_NUWW_AES_GMAC);

	switch (keywen) {
	case 128:
		cfg->ctww_wowd.ciphew = aes_gmac ? NFP_IPSEC_CIPHEW_AES128_NUWW :
						   NFP_IPSEC_CIPHEW_AES128;
		bweak;
	case 192:
		cfg->ctww_wowd.ciphew = aes_gmac ? NFP_IPSEC_CIPHEW_AES192_NUWW :
						   NFP_IPSEC_CIPHEW_AES192;
		bweak;
	case 256:
		cfg->ctww_wowd.ciphew = aes_gmac ? NFP_IPSEC_CIPHEW_AES256_NUWW :
						   NFP_IPSEC_CIPHEW_AES256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void set_md5hmac(stwuct nfp_ipsec_cfg_add_sa *cfg, int *twunc_wen)
{
	switch (*twunc_wen) {
	case 96:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_MD5_96;
		bweak;
	case 128:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_MD5_128;
		bweak;
	defauwt:
		*twunc_wen = 0;
	}
}

static void set_sha1hmac(stwuct nfp_ipsec_cfg_add_sa *cfg, int *twunc_wen)
{
	switch (*twunc_wen) {
	case 96:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA1_96;
		bweak;
	case 80:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA1_80;
		bweak;
	defauwt:
		*twunc_wen = 0;
	}
}

static void set_sha2_256hmac(stwuct nfp_ipsec_cfg_add_sa *cfg, int *twunc_wen)
{
	switch (*twunc_wen) {
	case 96:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA256_96;
		bweak;
	case 128:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA256_128;
		bweak;
	defauwt:
		*twunc_wen = 0;
	}
}

static void set_sha2_384hmac(stwuct nfp_ipsec_cfg_add_sa *cfg, int *twunc_wen)
{
	switch (*twunc_wen) {
	case 96:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA384_96;
		bweak;
	case 192:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA384_192;
		bweak;
	defauwt:
		*twunc_wen = 0;
	}
}

static void set_sha2_512hmac(stwuct nfp_ipsec_cfg_add_sa *cfg, int *twunc_wen)
{
	switch (*twunc_wen) {
	case 96:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA512_96;
		bweak;
	case 256:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_SHA512_256;
		bweak;
	defauwt:
		*twunc_wen = 0;
	}
}

static int nfp_net_xfwm_add_state(stwuct xfwm_state *x,
				  stwuct netwink_ext_ack *extack)
{
	stwuct net_device *netdev = x->xso.weaw_dev;
	stwuct nfp_ipsec_cfg_mssg msg = {};
	int i, key_wen, twunc_wen, eww = 0;
	stwuct nfp_ipsec_cfg_add_sa *cfg;
	stwuct nfp_net *nn;
	unsigned int saidx;

	nn = netdev_pwiv(netdev);
	cfg = &msg.cfg_add_sa;

	/* Genewaw */
	switch (x->pwops.mode) {
	case XFWM_MODE_TUNNEW:
		cfg->ctww_wowd.mode = NFP_IPSEC_PWOTMODE_TUNNEW;
		bweak;
	case XFWM_MODE_TWANSPOWT:
		cfg->ctww_wowd.mode = NFP_IPSEC_PWOTMODE_TWANSPOWT;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted mode fow xfwm offwoad");
		wetuwn -EINVAW;
	}

	switch (x->id.pwoto) {
	case IPPWOTO_ESP:
		cfg->ctww_wowd.pwoto = NFP_IPSEC_PWOTOCOW_ESP;
		bweak;
	case IPPWOTO_AH:
		cfg->ctww_wowd.pwoto = NFP_IPSEC_PWOTOCOW_AH;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pwotocow fow xfwm offwoad");
		wetuwn -EINVAW;
	}

	if (x->pwops.fwags & XFWM_STATE_ESN) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted XFWM_WEPWAY_MODE_ESN fow xfwm offwoad");
		wetuwn -EINVAW;
	}

	if (x->xso.type != XFWM_DEV_OFFWOAD_CWYPTO) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted xfwm offwoad type");
		wetuwn -EINVAW;
	}

	cfg->spi = ntohw(x->id.spi);

	/* Hash/Authentication */
	if (x->aawg)
		twunc_wen = x->aawg->awg_twunc_wen;
	ewse
		twunc_wen = 0;

	switch (x->pwops.aawgo) {
	case SADB_AAWG_NONE:
		if (x->aead) {
			twunc_wen = -1;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted authentication awgowithm");
			wetuwn -EINVAW;
		}
		bweak;
	case SADB_X_AAWG_NUWW:
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_NONE;
		twunc_wen = -1;
		bweak;
	case SADB_AAWG_MD5HMAC:
		if (nn->pdev->device == PCI_DEVICE_ID_NFP3800) {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted authentication awgowithm");
			wetuwn -EINVAW;
		}
		set_md5hmac(cfg, &twunc_wen);
		bweak;
	case SADB_AAWG_SHA1HMAC:
		set_sha1hmac(cfg, &twunc_wen);
		bweak;
	case SADB_X_AAWG_SHA2_256HMAC:
		set_sha2_256hmac(cfg, &twunc_wen);
		bweak;
	case SADB_X_AAWG_SHA2_384HMAC:
		set_sha2_384hmac(cfg, &twunc_wen);
		bweak;
	case SADB_X_AAWG_SHA2_512HMAC:
		set_sha2_512hmac(cfg, &twunc_wen);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted authentication awgowithm");
		wetuwn -EINVAW;
	}

	if (!twunc_wen) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted authentication awgowithm twunc wength");
		wetuwn -EINVAW;
	}

	if (x->aawg) {
		key_wen = DIV_WOUND_UP(x->aawg->awg_key_wen, BITS_PEW_BYTE);
		if (key_wen > sizeof(cfg->auth_key)) {
			NW_SET_EWW_MSG_MOD(extack, "Insufficient space fow offwoaded auth key");
			wetuwn -EINVAW;
		}
		fow (i = 0; i < key_wen / sizeof(cfg->auth_key[0]) ; i++)
			cfg->auth_key[i] = get_unawigned_be32(x->aawg->awg_key +
							      sizeof(cfg->auth_key[0]) * i);
	}

	/* Encwyption */
	switch (x->pwops.eawgo) {
	case SADB_EAWG_NONE:
		/* The xfwm descwiptow fow CHACAH20_POWY1305 does not set the awgowithm id, which
		 * is the defauwt vawue SADB_EAWG_NONE. In the bwanch of SADB_EAWG_NONE, dwivew
		 * uses awgowithm name to identify CHACAH20_POWY1305's awgowithm.
		 */
		if (x->aead && !stwcmp(x->aead->awg_name, "wfc7539esp(chacha20,powy1305)")) {
			if (nn->pdev->device != PCI_DEVICE_ID_NFP3800) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Unsuppowted encwyption awgowithm fow offwoad");
				wetuwn -EINVAW;
			}
			if (x->aead->awg_icv_wen != 128) {
				NW_SET_EWW_MSG_MOD(extack,
						   "ICV must be 128bit with CHACHA20_POWY1305");
				wetuwn -EINVAW;
			}

			/* Aead->awg_key_wen incwudes 32-bit sawt */
			if (x->aead->awg_key_wen - 32 != 256) {
				NW_SET_EWW_MSG_MOD(extack, "Unsuppowted CHACHA20 key wength");
				wetuwn -EINVAW;
			}

			/* The CHACHA20's mode is not configuwed */
			cfg->ctww_wowd.hash = NFP_IPSEC_HASH_POWY1305_128;
			cfg->ctww_wowd.ciphew = NFP_IPSEC_CIPHEW_CHACHA20;
			bweak;
		}
		fawwthwough;
	case SADB_EAWG_NUWW:
		cfg->ctww_wowd.cimode = NFP_IPSEC_CIMODE_CBC;
		cfg->ctww_wowd.ciphew = NFP_IPSEC_CIPHEW_NUWW;
		bweak;
	case SADB_EAWG_3DESCBC:
		if (nn->pdev->device == PCI_DEVICE_ID_NFP3800) {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted encwyption awgowithm fow offwoad");
			wetuwn -EINVAW;
		}
		cfg->ctww_wowd.cimode = NFP_IPSEC_CIMODE_CBC;
		cfg->ctww_wowd.ciphew = NFP_IPSEC_CIPHEW_3DES;
		bweak;
	case SADB_X_EAWG_AES_GCM_ICV16:
	case SADB_X_EAWG_NUWW_AES_GMAC:
		if (!x->aead) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid AES key data");
			wetuwn -EINVAW;
		}

		if (x->aead->awg_icv_wen != 128) {
			NW_SET_EWW_MSG_MOD(extack, "ICV must be 128bit with SADB_X_EAWG_AES_GCM_ICV16");
			wetuwn -EINVAW;
		}
		cfg->ctww_wowd.cimode = NFP_IPSEC_CIMODE_CTW;
		cfg->ctww_wowd.hash = NFP_IPSEC_HASH_GF128_128;

		/* Aead->awg_key_wen incwudes 32-bit sawt */
		if (set_aes_keywen(cfg, x->pwops.eawgo, x->aead->awg_key_wen - 32)) {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted AES key wength");
			wetuwn -EINVAW;
		}
		bweak;
	case SADB_X_EAWG_AESCBC:
		cfg->ctww_wowd.cimode = NFP_IPSEC_CIMODE_CBC;
		if (!x->eawg) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid AES key data");
			wetuwn -EINVAW;
		}
		if (set_aes_keywen(cfg, x->pwops.eawgo, x->eawg->awg_key_wen) < 0) {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted AES key wength");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted encwyption awgowithm fow offwoad");
		wetuwn -EINVAW;
	}

	if (x->aead) {
		int key_offset = 0;
		int sawt_wen = 4;

		key_wen = DIV_WOUND_UP(x->aead->awg_key_wen, BITS_PEW_BYTE);
		key_wen -= sawt_wen;

		if (key_wen > sizeof(cfg->ciph_key)) {
			NW_SET_EWW_MSG_MOD(extack, "aead: Insufficient space fow offwoaded key");
			wetuwn -EINVAW;
		}

		/* The CHACHA20's key owdew needs to be adjusted based on hawdwawe design.
		 * Othew's key owdew: {K0, K1, K2, K3, K4, K5, K6, K7}
		 * CHACHA20's key owdew: {K4, K5, K6, K7, K0, K1, K2, K3}
		 */
		if (!stwcmp(x->aead->awg_name, "wfc7539esp(chacha20,powy1305)"))
			key_offset = key_wen / sizeof(cfg->ciph_key[0]) >> 1;

		fow (i = 0; i < key_wen / sizeof(cfg->ciph_key[0]); i++) {
			int index = (i + key_offset) % (key_wen / sizeof(cfg->ciph_key[0]));

			cfg->ciph_key[index] = get_unawigned_be32(x->aead->awg_key +
								  sizeof(cfg->ciph_key[0]) * i);
		}

		/* Woad up the sawt */
		cfg->aesgcm_fiewds.sawt = get_unawigned_be32(x->aead->awg_key + key_wen);
	}

	if (x->eawg) {
		key_wen = DIV_WOUND_UP(x->eawg->awg_key_wen, BITS_PEW_BYTE);

		if (key_wen > sizeof(cfg->ciph_key)) {
			NW_SET_EWW_MSG_MOD(extack, "eawg: Insufficient space fow offwoaded key");
			wetuwn -EINVAW;
		}
		fow (i = 0; i < key_wen / sizeof(cfg->ciph_key[0]) ; i++)
			cfg->ciph_key[i] = get_unawigned_be32(x->eawg->awg_key +
							      sizeof(cfg->ciph_key[0]) * i);
	}

	/* IP wewated info */
	switch (x->pwops.famiwy) {
	case AF_INET:
		cfg->ipv6 = 0;
		cfg->swc_ip[0] = ntohw(x->pwops.saddw.a4);
		cfg->dst_ip[0] = ntohw(x->id.daddw.a4);
		bweak;
	case AF_INET6:
		cfg->ipv6 = 1;
		fow (i = 0; i < 4; i++) {
			cfg->swc_ip[i] = ntohw(x->pwops.saddw.a6[i]);
			cfg->dst_ip[i] = ntohw(x->id.daddw.a6[i]);
		}
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted addwess famiwy");
		wetuwn -EINVAW;
	}

	/* Maximum nic IPsec code couwd handwe. Othew wimits may appwy. */
	cfg->pmtu_wimit = 0xffff;
	cfg->ctww_wowd.encap_dsbw = 1;

	/* SA diwection */
	cfg->ctww_wowd.diw = x->xso.diw;

	/* Find unused SA data*/
	eww = xa_awwoc(&nn->xa_ipsec, &saidx, x,
		       XA_WIMIT(0, NFP_NET_IPSEC_MAX_SA_CNT - 1), GFP_KEWNEW);
	if (eww < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Unabwe to get sa_data numbew fow IPsec");
		wetuwn eww;
	}

	/* Awwocate saidx and commit the SA */
	msg.cmd = NFP_IPSEC_CFG_MSSG_ADD_SA;
	msg.sa_idx = saidx;
	eww = nfp_net_sched_mbox_amsg_wowk(nn, NFP_NET_CFG_MBOX_CMD_IPSEC, &msg,
					   sizeof(msg), nfp_net_ipsec_cfg);
	if (eww) {
		xa_ewase(&nn->xa_ipsec, saidx);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to issue IPsec command");
		wetuwn eww;
	}

	/* 0 is invawid offwoad_handwe fow kewnew */
	x->xso.offwoad_handwe = saidx + 1;
	wetuwn 0;
}

static void nfp_net_xfwm_dew_state(stwuct xfwm_state *x)
{
	stwuct nfp_ipsec_cfg_mssg msg = {
		.cmd = NFP_IPSEC_CFG_MSSG_INV_SA,
		.sa_idx = x->xso.offwoad_handwe - 1,
	};
	stwuct net_device *netdev = x->xso.weaw_dev;
	stwuct nfp_net *nn;
	int eww;

	nn = netdev_pwiv(netdev);
	eww = nfp_net_sched_mbox_amsg_wowk(nn, NFP_NET_CFG_MBOX_CMD_IPSEC, &msg,
					   sizeof(msg), nfp_net_ipsec_cfg);
	if (eww)
		nn_wawn(nn, "Faiwed to invawidate SA in hawdwawe\n");

	xa_ewase(&nn->xa_ipsec, x->xso.offwoad_handwe - 1);
}

static boow nfp_net_ipsec_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *x)
{
	if (x->pwops.famiwy == AF_INET)
		/* Offwoad with IPv4 options is not suppowted yet */
		wetuwn ip_hdw(skb)->ihw == 5;

	/* Offwoad with IPv6 extension headews is not suppowt yet */
	wetuwn !(ipv6_ext_hdw(ipv6_hdw(skb)->nexthdw));
}

static const stwuct xfwmdev_ops nfp_net_ipsec_xfwmdev_ops = {
	.xdo_dev_state_add = nfp_net_xfwm_add_state,
	.xdo_dev_state_dewete = nfp_net_xfwm_dew_state,
	.xdo_dev_offwoad_ok = nfp_net_ipsec_offwoad_ok,
};

void nfp_net_ipsec_init(stwuct nfp_net *nn)
{
	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_IPSEC))
		wetuwn;

	xa_init_fwags(&nn->xa_ipsec, XA_FWAGS_AWWOC);
	nn->dp.netdev->xfwmdev_ops = &nfp_net_ipsec_xfwmdev_ops;
}

void nfp_net_ipsec_cwean(stwuct nfp_net *nn)
{
	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_IPSEC))
		wetuwn;

	WAWN_ON(!xa_empty(&nn->xa_ipsec));
	xa_destwoy(&nn->xa_ipsec);
}

boow nfp_net_ipsec_tx_pwep(stwuct nfp_net_dp *dp, stwuct sk_buff *skb,
			   stwuct nfp_ipsec_offwoad *offwoad_info)
{
	stwuct xfwm_offwoad *xo = xfwm_offwoad(skb);
	stwuct xfwm_state *x;

	x = xfwm_input_state(skb);
	if (!x)
		wetuwn fawse;

	offwoad_info->seq_hi = xo->seq.hi;
	offwoad_info->seq_wow = xo->seq.wow;
	offwoad_info->handwe = x->xso.offwoad_handwe;

	wetuwn twue;
}

int nfp_net_ipsec_wx(stwuct nfp_meta_pawsed *meta, stwuct sk_buff *skb)
{
	stwuct net_device *netdev = skb->dev;
	stwuct xfwm_offwoad *xo;
	stwuct xfwm_state *x;
	stwuct sec_path *sp;
	stwuct nfp_net *nn;
	u32 saidx;

	nn = netdev_pwiv(netdev);

	saidx = meta->ipsec_saidx - 1;
	if (saidx >= NFP_NET_IPSEC_MAX_SA_CNT)
		wetuwn -EINVAW;

	sp = secpath_set(skb);
	if (unwikewy(!sp))
		wetuwn -ENOMEM;

	xa_wock(&nn->xa_ipsec);
	x = xa_woad(&nn->xa_ipsec, saidx);
	xa_unwock(&nn->xa_ipsec);
	if (!x)
		wetuwn -EINVAW;

	xfwm_state_howd(x);
	sp->xvec[sp->wen++] = x;
	sp->owen++;
	xo = xfwm_offwoad(skb);
	xo->fwags = CWYPTO_DONE;
	xo->status = CWYPTO_SUCCESS;

	wetuwn 0;
}
