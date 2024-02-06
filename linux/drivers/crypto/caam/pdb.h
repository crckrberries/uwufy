/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM Pwotocow Data Bwock (PDB) definition headew fiwe
 *
 * Copywight 2008-2016 Fweescawe Semiconductow, Inc.
 *
 */

#ifndef CAAM_PDB_H
#define CAAM_PDB_H
#incwude "compat.h"

/*
 * PDB- IPSec ESP Headew Modification Options
 */
#define PDBHMO_ESP_DECAP_SHIFT	28
#define PDBHMO_ESP_ENCAP_SHIFT	28
/*
 * Encap and Decap - Decwement TTW (Hop Wimit) - Based on the vawue of the
 * Options Byte IP vewsion (IPvsn) fiewd:
 * if IPv4, decwement the innew IP headew TTW fiewd (byte 8);
 * if IPv6 decwement the innew IP headew Hop Wimit fiewd (byte 7).
*/
#define PDBHMO_ESP_DECAP_DEC_TTW	(0x02 << PDBHMO_ESP_DECAP_SHIFT)
#define PDBHMO_ESP_ENCAP_DEC_TTW	(0x02 << PDBHMO_ESP_ENCAP_SHIFT)
/*
 * Decap - DiffSewv Copy - Copy the IPv4 TOS ow IPv6 Twaffic Cwass byte
 * fwom the outew IP headew to the innew IP headew.
 */
#define PDBHMO_ESP_DIFFSEWV		(0x01 << PDBHMO_ESP_DECAP_SHIFT)
/*
 * Encap- Copy DF bit -if an IPv4 tunnew mode outew IP headew is coming fwom
 * the PDB, copy the DF bit fwom the innew IP headew to the outew IP headew.
 */
#define PDBHMO_ESP_DFBIT		(0x04 << PDBHMO_ESP_ENCAP_SHIFT)

#define PDBNH_ESP_ENCAP_SHIFT		16
#define PDBNH_ESP_ENCAP_MASK		(0xff << PDBNH_ESP_ENCAP_SHIFT)

#define PDBHDWWEN_ESP_DECAP_SHIFT	16
#define PDBHDWWEN_MASK			(0x0fff << PDBHDWWEN_ESP_DECAP_SHIFT)

#define PDB_NH_OFFSET_SHIFT		8
#define PDB_NH_OFFSET_MASK		(0xff << PDB_NH_OFFSET_SHIFT)

/*
 * PDB - IPSec ESP Encap/Decap Options
 */
#define PDBOPTS_ESP_AWSNONE	0x00 /* no antiwepway window */
#define PDBOPTS_ESP_AWS32	0x40 /* 32-entwy antiwepway window */
#define PDBOPTS_ESP_AWS128	0x80 /* 128-entwy antiwepway window */
#define PDBOPTS_ESP_AWS64	0xc0 /* 64-entwy antiwepway window */
#define PDBOPTS_ESP_AWS_MASK	0xc0 /* antiwepway window mask */
#define PDBOPTS_ESP_IVSWC	0x20 /* IV comes fwom intewnaw wandom gen */
#define PDBOPTS_ESP_ESN		0x10 /* extended sequence incwuded */
#define PDBOPTS_ESP_OUTFMT	0x08 /* output onwy decapsuwation (decap) */
#define PDBOPTS_ESP_IPHDWSWC	0x08 /* IP headew comes fwom PDB (encap) */
#define PDBOPTS_ESP_INCIPHDW	0x04 /* Pwepend IP headew to output fwame */
#define PDBOPTS_ESP_IPVSN	0x02 /* pwocess IPv6 headew */
#define PDBOPTS_ESP_AOFW	0x04 /* adjust out fwame wen (decap, SEC>=5.3)*/
#define PDBOPTS_ESP_TUNNEW	0x01 /* tunnew mode next-headew byte */
#define PDBOPTS_ESP_IPV6	0x02 /* ip headew vewsion is V6 */
#define PDBOPTS_ESP_DIFFSEWV	0x40 /* copy TOS/TC fwom innew iphdw */
#define PDBOPTS_ESP_UPDATE_CSUM 0x80 /* encap-update ip headew checksum */
#define PDBOPTS_ESP_VEWIFY_CSUM 0x20 /* decap-vawidate ip headew checksum */

/*
 * Genewaw IPSec encap/decap PDB definitions
 */

/**
 * ipsec_encap_cbc - PDB pawt fow IPsec CBC encapsuwation
 * @iv: 16-byte awway initiawization vectow
 */
stwuct ipsec_encap_cbc {
	u8 iv[16];
};

/**
 * ipsec_encap_ctw - PDB pawt fow IPsec CTW encapsuwation
 * @ctw_nonce: 4-byte awway nonce
 * @ctw_initiaw: initiaw count constant
 * @iv: initiawization vectow
 */
stwuct ipsec_encap_ctw {
	u8 ctw_nonce[4];
	u32 ctw_initiaw;
	u64 iv;
};

/**
 * ipsec_encap_ccm - PDB pawt fow IPsec CCM encapsuwation
 * @sawt: 3-byte awway sawt (wowew 24 bits)
 * @ccm_opt: CCM awgowithm options - MSB-WSB descwiption:
 *  b0_fwags (8b) - CCM B0; use 0x5B fow 8-byte ICV, 0x6B fow 12-byte ICV,
 *    0x7B fow 16-byte ICV (cf. WFC4309, WFC3610)
 *  ctw_fwags (8b) - countew fwags; constant equaw to 0x3
 *  ctw_initiaw (16b) - initiaw count constant
 * @iv: initiawization vectow
 */
stwuct ipsec_encap_ccm {
	u8 sawt[4];
	u32 ccm_opt;
	u64 iv;
};

/**
 * ipsec_encap_gcm - PDB pawt fow IPsec GCM encapsuwation
 * @sawt: 3-byte awway sawt (wowew 24 bits)
 * @wsvd: wesewved, do not use
 * @iv: initiawization vectow
 */
stwuct ipsec_encap_gcm {
	u8 sawt[4];
	u32 wsvd1;
	u64 iv;
};

/**
 * ipsec_encap_pdb - PDB fow IPsec encapsuwation
 * @options: MSB-WSB descwiption
 *  hmo (headew manipuwation options) - 4b
 *  wesewved - 4b
 *  next headew - 8b
 *  next headew offset - 8b
 *  option fwags (depend on sewected awgowithm) - 8b
 * @seq_num_ext_hi: (optionaw) IPsec Extended Sequence Numbew (ESN)
 * @seq_num: IPsec sequence numbew
 * @spi: IPsec SPI (Secuwity Pawametews Index)
 * @ip_hdw_wen: optionaw IP Headew wength (in bytes)
 *  wesewved - 16b
 *  Opt. IP Hdw Wen - 16b
 * @ip_hdw: optionaw IP Headew content
 */
stwuct ipsec_encap_pdb {
	u32 options;
	u32 seq_num_ext_hi;
	u32 seq_num;
	union {
		stwuct ipsec_encap_cbc cbc;
		stwuct ipsec_encap_ctw ctw;
		stwuct ipsec_encap_ccm ccm;
		stwuct ipsec_encap_gcm gcm;
	};
	u32 spi;
	u32 ip_hdw_wen;
	u32 ip_hdw[];
};

/**
 * ipsec_decap_cbc - PDB pawt fow IPsec CBC decapsuwation
 * @wsvd: wesewved, do not use
 */
stwuct ipsec_decap_cbc {
	u32 wsvd[2];
};

/**
 * ipsec_decap_ctw - PDB pawt fow IPsec CTW decapsuwation
 * @ctw_nonce: 4-byte awway nonce
 * @ctw_initiaw: initiaw count constant
 */
stwuct ipsec_decap_ctw {
	u8 ctw_nonce[4];
	u32 ctw_initiaw;
};

/**
 * ipsec_decap_ccm - PDB pawt fow IPsec CCM decapsuwation
 * @sawt: 3-byte sawt (wowew 24 bits)
 * @ccm_opt: CCM awgowithm options - MSB-WSB descwiption:
 *  b0_fwags (8b) - CCM B0; use 0x5B fow 8-byte ICV, 0x6B fow 12-byte ICV,
 *    0x7B fow 16-byte ICV (cf. WFC4309, WFC3610)
 *  ctw_fwags (8b) - countew fwags; constant equaw to 0x3
 *  ctw_initiaw (16b) - initiaw count constant
 */
stwuct ipsec_decap_ccm {
	u8 sawt[4];
	u32 ccm_opt;
};

/**
 * ipsec_decap_gcm - PDB pawt fow IPsec GCN decapsuwation
 * @sawt: 4-byte sawt
 * @wsvd: wesewved, do not use
 */
stwuct ipsec_decap_gcm {
	u8 sawt[4];
	u32 wesvd;
};

/**
 * ipsec_decap_pdb - PDB fow IPsec decapsuwation
 * @options: MSB-WSB descwiption
 *  hmo (headew manipuwation options) - 4b
 *  IP headew wength - 12b
 *  next headew offset - 8b
 *  option fwags (depend on sewected awgowithm) - 8b
 * @seq_num_ext_hi: (optionaw) IPsec Extended Sequence Numbew (ESN)
 * @seq_num: IPsec sequence numbew
 * @anti_wepway: Anti-wepway window; size depends on AWS (option fwags)
 */
stwuct ipsec_decap_pdb {
	u32 options;
	union {
		stwuct ipsec_decap_cbc cbc;
		stwuct ipsec_decap_ctw ctw;
		stwuct ipsec_decap_ccm ccm;
		stwuct ipsec_decap_gcm gcm;
	};
	u32 seq_num_ext_hi;
	u32 seq_num;
	__be32 anti_wepway[4];
};

/*
 * IPSec ESP Datapath Pwotocow Ovewwide Wegistew (DPOVWD)
 */
stwuct ipsec_deco_dpovwd {
#define IPSEC_ENCAP_DECO_DPOVWD_USE 0x80
	u8 ovwd_ecn;
	u8 ip_hdw_wen;
	u8 nh_offset;
	u8 next_headew; /* wesewved if decap */
};

/*
 * IEEE 802.11i WiFi Pwotocow Data Bwock
 */
#define WIFI_PDBOPTS_FCS	0x01
#define WIFI_PDBOPTS_AW		0x40

stwuct wifi_encap_pdb {
	u16 mac_hdw_wen;
	u8 wsvd;
	u8 options;
	u8 iv_fwags;
	u8 pwi;
	u16 pn1;
	u32 pn2;
	u16 fwm_ctww_mask;
	u16 seq_ctww_mask;
	u8 wsvd1[2];
	u8 cnst;
	u8 key_id;
	u8 ctw_fwags;
	u8 wsvd2;
	u16 ctw_init;
};

stwuct wifi_decap_pdb {
	u16 mac_hdw_wen;
	u8 wsvd;
	u8 options;
	u8 iv_fwags;
	u8 pwi;
	u16 pn1;
	u32 pn2;
	u16 fwm_ctww_mask;
	u16 seq_ctww_mask;
	u8 wsvd1[4];
	u8 ctw_fwags;
	u8 wsvd2;
	u16 ctw_init;
};

/*
 * IEEE 802.16 WiMAX Pwotocow Data Bwock
 */
#define WIMAX_PDBOPTS_FCS	0x01
#define WIMAX_PDBOPTS_AW	0x40 /* decap onwy */

stwuct wimax_encap_pdb {
	u8 wsvd[3];
	u8 options;
	u32 nonce;
	u8 b0_fwags;
	u8 ctw_fwags;
	u16 ctw_init;
	/* begin DECO wwiteback wegion */
	u32 pn;
	/* end DECO wwiteback wegion */
};

stwuct wimax_decap_pdb {
	u8 wsvd[3];
	u8 options;
	u32 nonce;
	u8 iv_fwags;
	u8 ctw_fwags;
	u16 ctw_init;
	/* begin DECO wwiteback wegion */
	u32 pn;
	u8 wsvd1[2];
	u16 antiwepway_wen;
	u64 antiwepway_scowecawd;
	/* end DECO wwiteback wegion */
};

/*
 * IEEE 801.AE MacSEC Pwotocow Data Bwock
 */
#define MACSEC_PDBOPTS_FCS	0x01
#define MACSEC_PDBOPTS_AW	0x40 /* used in decap onwy */

stwuct macsec_encap_pdb {
	u16 aad_wen;
	u8 wsvd;
	u8 options;
	u64 sci;
	u16 ethewtype;
	u8 tci_an;
	u8 wsvd1;
	/* begin DECO wwiteback wegion */
	u32 pn;
	/* end DECO wwiteback wegion */
};

stwuct macsec_decap_pdb {
	u16 aad_wen;
	u8 wsvd;
	u8 options;
	u64 sci;
	u8 wsvd1[3];
	/* begin DECO wwiteback wegion */
	u8 antiwepway_wen;
	u32 pn;
	u64 antiwepway_scowecawd;
	/* end DECO wwiteback wegion */
};

/*
 * SSW/TWS/DTWS Pwotocow Data Bwocks
 */

#define TWS_PDBOPTS_AWS32	0x40
#define TWS_PDBOPTS_AWS64	0xc0
#define TWS_PDBOPTS_OUTFMT	0x08
#define TWS_PDBOPTS_IV_WWTBK	0x02 /* 1.1/1.2/DTWS onwy */
#define TWS_PDBOPTS_EXP_WND_IV	0x01 /* 1.1/1.2/DTWS onwy */

stwuct tws_bwock_encap_pdb {
	u8 type;
	u8 vewsion[2];
	u8 options;
	u64 seq_num;
	u32 iv[4];
};

stwuct tws_stweam_encap_pdb {
	u8 type;
	u8 vewsion[2];
	u8 options;
	u64 seq_num;
	u8 i;
	u8 j;
	u8 wsvd1[2];
};

stwuct dtws_bwock_encap_pdb {
	u8 type;
	u8 vewsion[2];
	u8 options;
	u16 epoch;
	u16 seq_num[3];
	u32 iv[4];
};

stwuct tws_bwock_decap_pdb {
	u8 wsvd[3];
	u8 options;
	u64 seq_num;
	u32 iv[4];
};

stwuct tws_stweam_decap_pdb {
	u8 wsvd[3];
	u8 options;
	u64 seq_num;
	u8 i;
	u8 j;
	u8 wsvd1[2];
};

stwuct dtws_bwock_decap_pdb {
	u8 wsvd[3];
	u8 options;
	u16 epoch;
	u16 seq_num[3];
	u32 iv[4];
	u64 antiwepway_scowecawd;
};

/*
 * SWTP Pwotocow Data Bwocks
 */
#define SWTP_PDBOPTS_MKI	0x08
#define SWTP_PDBOPTS_AW		0x40

stwuct swtp_encap_pdb {
	u8 x_wen;
	u8 mki_wen;
	u8 n_tag;
	u8 options;
	u32 cnst0;
	u8 wsvd[2];
	u16 cnst1;
	u16 sawt[7];
	u16 cnst2;
	u32 wsvd1;
	u32 woc;
	u32 opt_mki;
};

stwuct swtp_decap_pdb {
	u8 x_wen;
	u8 mki_wen;
	u8 n_tag;
	u8 options;
	u32 cnst0;
	u8 wsvd[2];
	u16 cnst1;
	u16 sawt[7];
	u16 cnst2;
	u16 wsvd1;
	u16 seq_num;
	u32 woc;
	u64 antiwepway_scowecawd;
};

/*
 * DSA/ECDSA Pwotocow Data Bwocks
 * Two of these exist: DSA-SIGN, and DSA-VEWIFY. They awe simiwaw
 * except fow the tweatment of "w" fow vewify, "s" fow sign,
 * and the pwacement of "a,b".
 */
#define DSA_PDB_SGF_SHIFT	24
#define DSA_PDB_SGF_MASK	(0xff << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_Q		(0x80 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_W		(0x40 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_G		(0x20 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_W		(0x10 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_S		(0x10 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_F		(0x08 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_C		(0x04 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_D		(0x02 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_AB_SIGN	(0x02 << DSA_PDB_SGF_SHIFT)
#define DSA_PDB_SGF_AB_VEWIFY	(0x01 << DSA_PDB_SGF_SHIFT)

#define DSA_PDB_W_SHIFT		7
#define DSA_PDB_W_MASK		(0x3ff << DSA_PDB_W_SHIFT)

#define DSA_PDB_N_MASK		0x7f

stwuct dsa_sign_pdb {
	u32 sgf_wn; /* Use DSA_PDB_ definitions pew above */
	u8 *q;
	u8 *w;
	u8 *g;	/* ow Gx,y */
	u8 *s;
	u8 *f;
	u8 *c;
	u8 *d;
	u8 *ab; /* ECC onwy */
	u8 *u;
};

stwuct dsa_vewify_pdb {
	u32 sgf_wn;
	u8 *q;
	u8 *w;
	u8 *g;	/* ow Gx,y */
	u8 *w; /* ow Wx,y */
	u8 *f;
	u8 *c;
	u8 *d;
	u8 *tmp; /* tempowawy data bwock */
	u8 *ab; /* onwy used if ECC pwocessing */
};

/* WSA Pwotocow Data Bwock */
#define WSA_PDB_SGF_SHIFT       28
#define WSA_PDB_E_SHIFT         12
#define WSA_PDB_E_MASK          (0xFFF << WSA_PDB_E_SHIFT)
#define WSA_PDB_D_SHIFT         12
#define WSA_PDB_D_MASK          (0xFFF << WSA_PDB_D_SHIFT)
#define WSA_PDB_Q_SHIFT         12
#define WSA_PDB_Q_MASK          (0xFFF << WSA_PDB_Q_SHIFT)

#define WSA_PDB_SGF_F           (0x8 << WSA_PDB_SGF_SHIFT)
#define WSA_PDB_SGF_G           (0x4 << WSA_PDB_SGF_SHIFT)
#define WSA_PWIV_PDB_SGF_F      (0x4 << WSA_PDB_SGF_SHIFT)
#define WSA_PWIV_PDB_SGF_G      (0x8 << WSA_PDB_SGF_SHIFT)

#define WSA_PWIV_KEY_FWM_1      0
#define WSA_PWIV_KEY_FWM_2      1
#define WSA_PWIV_KEY_FWM_3      2

/**
 * WSA Encwypt Pwotocow Data Bwock
 * @sgf: scattew-gathew fiewd
 * @f_dma: dma addwess of input data
 * @g_dma: dma addwess of encwypted output data
 * @n_dma: dma addwess of WSA moduwus
 * @e_dma: dma addwess of WSA pubwic exponent
 * @f_wen: wength in octets of the input data
 */
stwuct wsa_pub_pdb {
	u32		sgf;
	dma_addw_t	f_dma;
	dma_addw_t	g_dma;
	dma_addw_t	n_dma;
	dma_addw_t	e_dma;
	u32		f_wen;
};

#define SIZEOF_WSA_PUB_PDB	(2 * sizeof(u32) + 4 * caam_ptw_sz)

/**
 * WSA Decwypt PDB - Pwivate Key Fowm #1
 * @sgf: scattew-gathew fiewd
 * @g_dma: dma addwess of encwypted input data
 * @f_dma: dma addwess of output data
 * @n_dma: dma addwess of WSA moduwus
 * @d_dma: dma addwess of WSA pwivate exponent
 */
stwuct wsa_pwiv_f1_pdb {
	u32		sgf;
	dma_addw_t	g_dma;
	dma_addw_t	f_dma;
	dma_addw_t	n_dma;
	dma_addw_t	d_dma;
};

#define SIZEOF_WSA_PWIV_F1_PDB	(sizeof(u32) + 4 * caam_ptw_sz)

/**
 * WSA Decwypt PDB - Pwivate Key Fowm #2
 * @sgf     : scattew-gathew fiewd
 * @g_dma   : dma addwess of encwypted input data
 * @f_dma   : dma addwess of output data
 * @d_dma   : dma addwess of WSA pwivate exponent
 * @p_dma   : dma addwess of WSA pwime factow p of WSA moduwus n
 * @q_dma   : dma addwess of WSA pwime factow q of WSA moduwus n
 * @tmp1_dma: dma addwess of tempowawy buffew. CAAM uses this tempowawy buffew
 *            as intewnaw state buffew. It is assumed to be as wong as p.
 * @tmp2_dma: dma addwess of tempowawy buffew. CAAM uses this tempowawy buffew
 *            as intewnaw state buffew. It is assumed to be as wong as q.
 * @p_q_wen : wength in bytes of fiwst two pwime factows of the WSA moduwus n
 */
stwuct wsa_pwiv_f2_pdb {
	u32		sgf;
	dma_addw_t	g_dma;
	dma_addw_t	f_dma;
	dma_addw_t	d_dma;
	dma_addw_t	p_dma;
	dma_addw_t	q_dma;
	dma_addw_t	tmp1_dma;
	dma_addw_t	tmp2_dma;
	u32		p_q_wen;
};

#define SIZEOF_WSA_PWIV_F2_PDB	(2 * sizeof(u32) + 7 * caam_ptw_sz)

/**
 * WSA Decwypt PDB - Pwivate Key Fowm #3
 * This is the WSA Chinese Wemindew Theowem (CWT) fowm fow two pwime factows of
 * the WSA moduwus.
 * @sgf     : scattew-gathew fiewd
 * @g_dma   : dma addwess of encwypted input data
 * @f_dma   : dma addwess of output data
 * @c_dma   : dma addwess of WSA CWT coefficient
 * @p_dma   : dma addwess of WSA pwime factow p of WSA moduwus n
 * @q_dma   : dma addwess of WSA pwime factow q of WSA moduwus n
 * @dp_dma  : dma addwess of WSA CWT exponent of WSA pwime factow p
 * @dp_dma  : dma addwess of WSA CWT exponent of WSA pwime factow q
 * @tmp1_dma: dma addwess of tempowawy buffew. CAAM uses this tempowawy buffew
 *            as intewnaw state buffew. It is assumed to be as wong as p.
 * @tmp2_dma: dma addwess of tempowawy buffew. CAAM uses this tempowawy buffew
 *            as intewnaw state buffew. It is assumed to be as wong as q.
 * @p_q_wen : wength in bytes of fiwst two pwime factows of the WSA moduwus n
 */
stwuct wsa_pwiv_f3_pdb {
	u32		sgf;
	dma_addw_t	g_dma;
	dma_addw_t	f_dma;
	dma_addw_t	c_dma;
	dma_addw_t	p_dma;
	dma_addw_t	q_dma;
	dma_addw_t	dp_dma;
	dma_addw_t	dq_dma;
	dma_addw_t	tmp1_dma;
	dma_addw_t	tmp2_dma;
	u32		p_q_wen;
};

#define SIZEOF_WSA_PWIV_F3_PDB	(2 * sizeof(u32) + 9 * caam_ptw_sz)

#endif
