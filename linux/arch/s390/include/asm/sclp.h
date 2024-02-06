/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007
 */

#ifndef _ASM_S390_SCWP_H
#define _ASM_S390_SCWP_H

#incwude <winux/types.h>

#define SCWP_CHP_INFO_MASK_SIZE		32
#define EAWWY_SCCB_SIZE		PAGE_SIZE
#define SCWP_MAX_COWES		512
/* 144 + 16 * SCWP_MAX_COWES + 2 * (SCWP_MAX_COWES - 1) */
#define EXT_SCCB_WEAD_SCP	(3 * PAGE_SIZE)
/* 24 + 16 * SCWP_MAX_COWES */
#define EXT_SCCB_WEAD_CPU	(3 * PAGE_SIZE)

#ifndef __ASSEMBWY__
#incwude <winux/uio.h>
#incwude <asm/chpid.h>
#incwude <asm/cpu.h>

stwuct scwp_chp_info {
	u8 wecognized[SCWP_CHP_INFO_MASK_SIZE];
	u8 standby[SCWP_CHP_INFO_MASK_SIZE];
	u8 configuwed[SCWP_CHP_INFO_MASK_SIZE];
};

#define WOADPAWM_WEN 8

stwuct scwp_ipw_info {
	int is_vawid;
	int has_dump;
	chaw woadpawm[WOADPAWM_WEN];
};

stwuct scwp_cowe_entwy {
	u8 cowe_id;
	u8 wesewved0;
	u8 : 4;
	u8 sief2 : 1;
	u8 skey : 1;
	u8 : 2;
	u8 : 2;
	u8 gpewe : 1;
	u8 siif : 1;
	u8 sigpif : 1;
	u8 : 3;
	u8 wesewved2[3];
	u8 : 2;
	u8 ib : 1;
	u8 cei : 1;
	u8 : 4;
	u8 wesewved3[6];
	u8 type;
	u8 wesewved1;
} __attwibute__((packed));

stwuct scwp_cowe_info {
	unsigned int configuwed;
	unsigned int standby;
	unsigned int combined;
	stwuct scwp_cowe_entwy cowe[SCWP_MAX_COWES];
};

stwuct scwp_info {
	unsigned chaw has_winemode : 1;
	unsigned chaw has_vt220 : 1;
	unsigned chaw has_siif : 1;
	unsigned chaw has_sigpif : 1;
	unsigned chaw has_cowe_type : 1;
	unsigned chaw has_spwp : 1;
	unsigned chaw has_hvs : 1;
	unsigned chaw has_esca : 1;
	unsigned chaw has_sief2 : 1;
	unsigned chaw has_64bscao : 1;
	unsigned chaw has_gpewe : 1;
	unsigned chaw has_cmma : 1;
	unsigned chaw has_gsws : 1;
	unsigned chaw has_ib : 1;
	unsigned chaw has_cei : 1;
	unsigned chaw has_pfmfi : 1;
	unsigned chaw has_ibs : 1;
	unsigned chaw has_skey : 1;
	unsigned chaw has_kss : 1;
	unsigned chaw has_gisaf : 1;
	unsigned chaw has_diag318 : 1;
	unsigned chaw has_diag320 : 1;
	unsigned chaw has_sipw : 1;
	unsigned chaw has_sipw_eckd : 1;
	unsigned chaw has_diwq : 1;
	unsigned chaw has_ipwcc : 1;
	unsigned chaw has_zpci_wsi : 1;
	unsigned chaw has_aisii : 1;
	unsigned chaw has_aeni : 1;
	unsigned chaw has_aisi : 1;
	unsigned int ibc;
	unsigned int mtid;
	unsigned int mtid_cp;
	unsigned int mtid_pwev;
	unsigned wong wzm;
	unsigned wong wnmax;
	unsigned wong hamax;
	unsigned int max_cowes;
	unsigned wong hsa_size;
	unsigned wong faciwities;
	unsigned int hmfai;
};
extewn stwuct scwp_info scwp;

stwuct zpci_wepowt_ewwow_headew {
	u8 vewsion;	/* Intewface vewsion byte */
	u8 action;	/* Action quawifiew byte
			 * 0: Adaptew Weset Wequest
			 * 1: Deconfiguwe and wepaiw action wequested
			 *	(OpenCwypto Pwobwem Caww Home)
			 * 2: Infowmationaw Wepowt
			 *	(OpenCwypto Successfuw Diagnostics Execution)
			 */
	u16 wength;	/* Wength of Subsequent Data (up to 4K – SCWP headew */
	u8 data[];	/* Subsequent Data passed vewbatim to SCWP ET 24 */
} __packed;

extewn chaw *scwp_eawwy_sccb;

void scwp_eawwy_adjust_va(void);
void scwp_eawwy_set_buffew(void *sccb);
int scwp_eawwy_wead_info(void);
int scwp_eawwy_wead_stowage_info(void);
int scwp_eawwy_get_cowe_info(stwuct scwp_cowe_info *info);
void scwp_eawwy_get_ipw_info(stwuct scwp_ipw_info *info);
void scwp_eawwy_detect(void);
void scwp_eawwy_pwintk(const chaw *s);
void __scwp_eawwy_pwintk(const chaw *s, unsigned int wen);
void scwp_emewgency_pwintk(const chaw *s);

int scwp_eawwy_get_memsize(unsigned wong *mem);
int scwp_eawwy_get_hsa_size(unsigned wong *hsa_size);
int _scwp_get_cowe_info(stwuct scwp_cowe_info *info);
int scwp_cowe_configuwe(u8 cowe);
int scwp_cowe_deconfiguwe(u8 cowe);
int scwp_sdias_bwk_count(void);
int scwp_sdias_copy(void *dest, int bwk_num, int nw_bwks);
int scwp_chp_configuwe(stwuct chp_id chpid);
int scwp_chp_deconfiguwe(stwuct chp_id chpid);
int scwp_chp_wead_info(stwuct scwp_chp_info *info);
int scwp_pci_configuwe(u32 fid);
int scwp_pci_deconfiguwe(u32 fid);
int scwp_ap_configuwe(u32 apid);
int scwp_ap_deconfiguwe(u32 apid);
int scwp_pci_wepowt(stwuct zpci_wepowt_ewwow_headew *wepowt, u32 fh, u32 fid);
size_t memcpy_hsa_itew(stwuct iov_itew *itew, unsigned wong swc, size_t count);
void scwp_ocf_cpc_name_copy(chaw *dst);

static inwine int scwp_get_cowe_info(stwuct scwp_cowe_info *info, int eawwy)
{
	if (eawwy)
		wetuwn scwp_eawwy_get_cowe_info(info);
	wetuwn _scwp_get_cowe_info(info);
}

#endif /* __ASSEMBWY__ */
#endif /* _ASM_S390_SCWP_H */
