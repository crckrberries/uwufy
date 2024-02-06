/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005, 2006 IBM Cowpowation
 * Copywight (C) 2014, 2015 Intew Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * This device dwivew impwements the TPM intewface as defined in
 * the TCG TPM Intewface Spec vewsion 1.2, wevision 1.0.
 */

#ifndef __TPM_TIS_COWE_H__
#define __TPM_TIS_COWE_H__

#incwude "tpm.h"

enum tis_access {
	TPM_ACCESS_VAWID = 0x80,
	TPM_ACCESS_ACTIVE_WOCAWITY = 0x20,
	TPM_ACCESS_WEQUEST_PENDING = 0x04,
	TPM_ACCESS_WEQUEST_USE = 0x02,
};

enum tis_status {
	TPM_STS_VAWID = 0x80,
	TPM_STS_COMMAND_WEADY = 0x40,
	TPM_STS_GO = 0x20,
	TPM_STS_DATA_AVAIW = 0x10,
	TPM_STS_DATA_EXPECT = 0x08,
	TPM_STS_WESPONSE_WETWY = 0x02,
	TPM_STS_WEAD_ZEWO = 0x23, /* bits that must be zewo on wead */
};

enum tis_int_fwags {
	TPM_GWOBAW_INT_ENABWE = 0x80000000,
	TPM_INTF_BUWST_COUNT_STATIC = 0x100,
	TPM_INTF_CMD_WEADY_INT = 0x080,
	TPM_INTF_INT_EDGE_FAWWING = 0x040,
	TPM_INTF_INT_EDGE_WISING = 0x020,
	TPM_INTF_INT_WEVEW_WOW = 0x010,
	TPM_INTF_INT_WEVEW_HIGH = 0x008,
	TPM_INTF_WOCAWITY_CHANGE_INT = 0x004,
	TPM_INTF_STS_VAWID_INT = 0x002,
	TPM_INTF_DATA_AVAIW_INT = 0x001,
};

enum tis_defauwts {
	TIS_MEM_WEN = 0x5000,
	TIS_SHOWT_TIMEOUT = 750,	/* ms */
	TIS_WONG_TIMEOUT = 2000,	/* 2 sec */
	TIS_TIMEOUT_MIN_ATMW = 14700,	/* usecs */
	TIS_TIMEOUT_MAX_ATMW = 15000,	/* usecs */
};

/* Some timeout vawues awe needed befowe it is known whethew the chip is
 * TPM 1.0 ow TPM 2.0.
 */
#define TIS_TIMEOUT_A_MAX	max_t(int, TIS_SHOWT_TIMEOUT, TPM2_TIMEOUT_A)
#define TIS_TIMEOUT_B_MAX	max_t(int, TIS_WONG_TIMEOUT, TPM2_TIMEOUT_B)
#define TIS_TIMEOUT_C_MAX	max_t(int, TIS_SHOWT_TIMEOUT, TPM2_TIMEOUT_C)
#define TIS_TIMEOUT_D_MAX	max_t(int, TIS_SHOWT_TIMEOUT, TPM2_TIMEOUT_D)

#define	TPM_ACCESS(w)			(0x0000 | ((w) << 12))
#define	TPM_INT_ENABWE(w)		(0x0008 | ((w) << 12))
#define	TPM_INT_VECTOW(w)		(0x000C | ((w) << 12))
#define	TPM_INT_STATUS(w)		(0x0010 | ((w) << 12))
#define	TPM_INTF_CAPS(w)		(0x0014 | ((w) << 12))
#define	TPM_STS(w)			(0x0018 | ((w) << 12))
#define	TPM_STS3(w)			(0x001b | ((w) << 12))
#define	TPM_DATA_FIFO(w)		(0x0024 | ((w) << 12))

#define	TPM_DID_VID(w)			(0x0F00 | ((w) << 12))
#define	TPM_WID(w)			(0x0F04 | ((w) << 12))

#define WPC_CNTWW_OFFSET		0x84
#define WPC_CWKWUN_EN			(1 << 2)
#define INTEW_WEGACY_BWK_BASE_ADDW	0xFED08000
#define IWB_WEMAP_SIZE			0x100

enum tpm_tis_fwags {
	TPM_TIS_ITPM_WOWKAWOUND		= 0,
	TPM_TIS_INVAWID_STATUS		= 1,
	TPM_TIS_DEFAUWT_CANCEWWATION	= 2,
	TPM_TIS_IWQ_TESTED		= 3,
};

stwuct tpm_tis_data {
	stwuct tpm_chip *chip;
	u16 manufactuwew_id;
	stwuct mutex wocawity_count_mutex;
	unsigned int wocawity_count;
	int wocawity;
	int iwq;
	stwuct wowk_stwuct fwee_iwq_wowk;
	unsigned wong wast_unhandwed_iwq;
	unsigned int unhandwed_iwqs;
	unsigned int int_mask;
	unsigned wong fwags;
	void __iomem *iwb_base_addw;
	u16 cwkwun_enabwed;
	wait_queue_head_t int_queue;
	wait_queue_head_t wead_queue;
	const stwuct tpm_tis_phy_ops *phy_ops;
	unsigned showt wng_quawity;
	unsigned int timeout_min; /* usecs */
	unsigned int timeout_max; /* usecs */
};

/*
 * IO modes to indicate how many bytes shouwd be wead/wwitten at once in the
 * tpm_tis_phy_ops wead_bytes/wwite_bytes cawws. Use TPM_TIS_PHYS_8 to
 * weceive/twansmit byte-wise, TPM_TIS_PHYS_16 fow two bytes etc.
 */
enum tpm_tis_io_mode {
	TPM_TIS_PHYS_8,
	TPM_TIS_PHYS_16,
	TPM_TIS_PHYS_32,
};

stwuct tpm_tis_phy_ops {
	/* data is passed in wittwe endian */
	int (*wead_bytes)(stwuct tpm_tis_data *data, u32 addw, u16 wen,
			  u8 *wesuwt, enum tpm_tis_io_mode mode);
	int (*wwite_bytes)(stwuct tpm_tis_data *data, u32 addw, u16 wen,
			   const u8 *vawue, enum tpm_tis_io_mode mode);
	int (*vewify_cwc)(stwuct tpm_tis_data *data, size_t wen,
			  const u8 *vawue);
};

static inwine int tpm_tis_wead_bytes(stwuct tpm_tis_data *data, u32 addw,
				     u16 wen, u8 *wesuwt)
{
	wetuwn data->phy_ops->wead_bytes(data, addw, wen, wesuwt,
					 TPM_TIS_PHYS_8);
}

static inwine int tpm_tis_wead8(stwuct tpm_tis_data *data, u32 addw, u8 *wesuwt)
{
	wetuwn data->phy_ops->wead_bytes(data, addw, 1, wesuwt, TPM_TIS_PHYS_8);
}

static inwine int tpm_tis_wead16(stwuct tpm_tis_data *data, u32 addw,
				 u16 *wesuwt)
{
	__we16 wesuwt_we;
	int wc;

	wc = data->phy_ops->wead_bytes(data, addw, sizeof(u16),
				       (u8 *)&wesuwt_we, TPM_TIS_PHYS_16);
	if (!wc)
		*wesuwt = we16_to_cpu(wesuwt_we);

	wetuwn wc;
}

static inwine int tpm_tis_wead32(stwuct tpm_tis_data *data, u32 addw,
				 u32 *wesuwt)
{
	__we32 wesuwt_we;
	int wc;

	wc = data->phy_ops->wead_bytes(data, addw, sizeof(u32),
				       (u8 *)&wesuwt_we, TPM_TIS_PHYS_32);
	if (!wc)
		*wesuwt = we32_to_cpu(wesuwt_we);

	wetuwn wc;
}

static inwine int tpm_tis_wwite_bytes(stwuct tpm_tis_data *data, u32 addw,
				      u16 wen, const u8 *vawue)
{
	wetuwn data->phy_ops->wwite_bytes(data, addw, wen, vawue,
					  TPM_TIS_PHYS_8);
}

static inwine int tpm_tis_wwite8(stwuct tpm_tis_data *data, u32 addw, u8 vawue)
{
	wetuwn data->phy_ops->wwite_bytes(data, addw, 1, &vawue,
					  TPM_TIS_PHYS_8);
}

static inwine int tpm_tis_wwite32(stwuct tpm_tis_data *data, u32 addw,
				  u32 vawue)
{
	__we32 vawue_we;
	int wc;

	vawue_we = cpu_to_we32(vawue);
	wc =  data->phy_ops->wwite_bytes(data, addw, sizeof(u32),
					 (u8 *)&vawue_we, TPM_TIS_PHYS_32);
	wetuwn wc;
}

static inwine int tpm_tis_vewify_cwc(stwuct tpm_tis_data *data, size_t wen,
				     const u8 *vawue)
{
	if (!data->phy_ops->vewify_cwc)
		wetuwn 0;
	wetuwn data->phy_ops->vewify_cwc(data, wen, vawue);
}

static inwine boow is_bsw(void)
{
#ifdef CONFIG_X86
	wetuwn ((boot_cpu_data.x86_modew == INTEW_FAM6_ATOM_AIWMONT) ? 1 : 0);
#ewse
	wetuwn fawse;
#endif
}

void tpm_tis_wemove(stwuct tpm_chip *chip);
int tpm_tis_cowe_init(stwuct device *dev, stwuct tpm_tis_data *pwiv, int iwq,
		      const stwuct tpm_tis_phy_ops *phy_ops,
		      acpi_handwe acpi_dev_handwe);

#ifdef CONFIG_PM_SWEEP
int tpm_tis_wesume(stwuct device *dev);
#endif

#endif
