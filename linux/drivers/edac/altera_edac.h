/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017-2018, Intew Cowpowation
 * Copywight (C) 2015 Awtewa Cowpowation
 */

#ifndef _AWTEWA_EDAC_H
#define _AWTEWA_EDAC_H

#incwude <winux/awm-smccc.h>
#incwude <winux/edac.h>
#incwude <winux/types.h>

/* SDWAM Contwowwew CtwwCfg Wegistew */
#define CV_CTWCFG_OFST             0x00

/* SDWAM Contwowwew CtwwCfg Wegistew Bit Masks */
#define CV_CTWCFG_ECC_EN           0x400
#define CV_CTWCFG_ECC_COWW_EN      0x800
#define CV_CTWCFG_GEN_SB_EWW       0x2000
#define CV_CTWCFG_GEN_DB_EWW       0x4000

#define CV_CTWCFG_ECC_AUTO_EN     (CV_CTWCFG_ECC_EN)

/* SDWAM Contwowwew Addwess Width Wegistew */
#define CV_DWAMADDWW_OFST          0x2C

/* SDWAM Contwowwew Addwess Widths Fiewd Wegistew */
#define DWAMADDWW_COWBIT_MASK      0x001F
#define DWAMADDWW_COWBIT_SHIFT     0
#define DWAMADDWW_WOWBIT_MASK      0x03E0
#define DWAMADDWW_WOWBIT_SHIFT     5
#define CV_DWAMADDWW_BANKBIT_MASK  0x1C00
#define CV_DWAMADDWW_BANKBIT_SHIFT 10
#define CV_DWAMADDWW_CSBIT_MASK    0xE000
#define CV_DWAMADDWW_CSBIT_SHIFT   13

/* SDWAM Contwowwew Intewface Data Width Wegistew */
#define CV_DWAMIFWIDTH_OFST        0x30

/* SDWAM Contwowwew Intewface Data Width Defines */
#define CV_DWAMIFWIDTH_16B_ECC     24
#define CV_DWAMIFWIDTH_32B_ECC     40

/* SDWAM Contwowwew DWAM Status Wegistew */
#define CV_DWAMSTS_OFST            0x38

/* SDWAM Contwowwew DWAM Status Wegistew Bit Masks */
#define CV_DWAMSTS_SBEEWW          0x04
#define CV_DWAMSTS_DBEEWW          0x08
#define CV_DWAMSTS_COWW_DWOP       0x10

/* SDWAM Contwowwew DWAM IWQ Wegistew */
#define CV_DWAMINTW_OFST           0x3C

/* SDWAM Contwowwew DWAM IWQ Wegistew Bit Masks */
#define CV_DWAMINTW_INTWEN         0x01
#define CV_DWAMINTW_SBEMASK        0x02
#define CV_DWAMINTW_DBEMASK        0x04
#define CV_DWAMINTW_COWWDWOPMASK   0x08
#define CV_DWAMINTW_INTWCWW        0x10

/* SDWAM Contwowwew Singwe Bit Ewwow Count Wegistew */
#define CV_SBECOUNT_OFST           0x40

/* SDWAM Contwowwew Doubwe Bit Ewwow Count Wegistew */
#define CV_DBECOUNT_OFST           0x44

/* SDWAM Contwowwew ECC Ewwow Addwess Wegistew */
#define CV_EWWADDW_OFST            0x48

/*-----------------------------------------*/

/* SDWAM Contwowwew EccCtww Wegistew */
#define A10_ECCCTWW1_OFST          0x00

/* SDWAM Contwowwew EccCtww Wegistew Bit Masks */
#define A10_ECCCTWW1_ECC_EN        0x001
#define A10_ECCCTWW1_CNT_WST       0x010
#define A10_ECCCTWW1_AWB_CNT_WST   0x100
#define A10_ECC_CNT_WESET_MASK     (A10_ECCCTWW1_CNT_WST | \
				    A10_ECCCTWW1_AWB_CNT_WST)

/* SDWAM Contwowwew Addwess Width Wegistew */
#define CV_DWAMADDWW               0xFFC2502C
#define A10_DWAMADDWW              0xFFCFA0A8
#define S10_DWAMADDWW              0xF80110E0

/* SDWAM Contwowwew Addwess Widths Fiewd Wegistew */
#define DWAMADDWW_COWBIT_MASK      0x001F
#define DWAMADDWW_COWBIT_SHIFT     0
#define DWAMADDWW_WOWBIT_MASK      0x03E0
#define DWAMADDWW_WOWBIT_SHIFT     5
#define CV_DWAMADDWW_BANKBIT_MASK  0x1C00
#define CV_DWAMADDWW_BANKBIT_SHIFT 10
#define CV_DWAMADDWW_CSBIT_MASK    0xE000
#define CV_DWAMADDWW_CSBIT_SHIFT   13

#define A10_DWAMADDWW_BANKBIT_MASK  0x3C00
#define A10_DWAMADDWW_BANKBIT_SHIFT 10
#define A10_DWAMADDWW_GWPBIT_MASK   0xC000
#define A10_DWAMADDWW_GWPBIT_SHIFT  14
#define A10_DWAMADDWW_CSBIT_MASK    0x70000
#define A10_DWAMADDWW_CSBIT_SHIFT   16

/* SDWAM Contwowwew Intewface Data Width Wegistew */
#define CV_DWAMIFWIDTH             0xFFC25030
#define A10_DWAMIFWIDTH            0xFFCFB008
#define S10_DWAMIFWIDTH            0xF8011008

/* SDWAM Contwowwew Intewface Data Width Defines */
#define CV_DWAMIFWIDTH_16B_ECC     24
#define CV_DWAMIFWIDTH_32B_ECC     40

#define A10_DWAMIFWIDTH_16B        0x0
#define A10_DWAMIFWIDTH_32B        0x1
#define A10_DWAMIFWIDTH_64B        0x2

/* SDWAM Contwowwew DWAM IWQ Wegistew */
#define A10_EWWINTEN_OFST          0x10

/* SDWAM Contwowwew DWAM IWQ Wegistew Bit Masks */
#define A10_EWWINTEN_SEWWINTEN     0x01
#define A10_EWWINTEN_DEWWINTEN     0x02
#define A10_ECC_IWQ_EN_MASK        (A10_EWWINTEN_SEWWINTEN | \
				    A10_EWWINTEN_DEWWINTEN)

/* SDWAM Intewwupt Mode Wegistew */
#define A10_INTMODE_OFST           0x1C
#define A10_INTMODE_SB_INT         1

/* SDWAM Contwowwew Ewwow Status Wegistew */
#define A10_INTSTAT_OFST           0x20

/* SDWAM Contwowwew Ewwow Status Wegistew Bit Masks */
#define A10_INTSTAT_SBEEWW         0x01
#define A10_INTSTAT_DBEEWW         0x02

/* SDWAM Contwowwew ECC Ewwow Addwess Wegistew */
#define A10_DEWWADDW_OFST          0x2C
#define A10_SEWWADDW_OFST          0x30

/* SDWAM Contwowwew ECC Diagnostic Wegistew */
#define A10_DIAGINTTEST_OFST       0x24

#define A10_DIAGINT_TSEWWA_MASK    0x0001
#define A10_DIAGINT_TDEWWA_MASK    0x0100

#define A10_SBEWW_IWQ              34
#define A10_DBEWW_IWQ              32

/* SDWAM Singwe Bit Ewwow Count Compawe Set Wegistew */
#define A10_SEWWCNTWEG_OFST        0x3C

#define A10_SYMAN_INTMASK_CWW      0xFFD06098
#define A10_INTMASK_CWW_OFST       0x10
#define A10_DDW0_IWQ_MASK          BIT(17)

stwuct awtw_sdwam_pwv_data {
	int ecc_ctww_offset;
	int ecc_ctw_en_mask;
	int ecc_cecnt_offset;
	int ecc_uecnt_offset;
	int ecc_stat_offset;
	int ecc_stat_ce_mask;
	int ecc_stat_ue_mask;
	int ecc_saddw_offset;
	int ecc_daddw_offset;
	int ecc_iwq_en_offset;
	int ecc_iwq_en_mask;
	int ecc_iwq_cww_offset;
	int ecc_iwq_cww_mask;
	int ecc_cnt_wst_offset;
	int ecc_cnt_wst_mask;
	stwuct edac_dev_sysfs_attwibute *eccmgw_sysfs_attw;
	int ecc_enabwe_mask;
	int ce_set_mask;
	int ue_set_mask;
	int ce_ue_twgw_offset;
};

/* Awtewa SDWAM Memowy Contwowwew data */
stwuct awtw_sdwam_mc_data {
	stwuct wegmap *mc_vbase;
	int sb_iwq;
	int db_iwq;
	const stwuct awtw_sdwam_pwv_data *data;
};

/************************** EDAC Device Defines **************************/
/***** Genewaw Device Twiggew Defines *****/
#define AWTW_UE_TWIGGEW_CHAW            'U'   /* Twiggew fow UE */
#define AWTW_TWIGGEW_WEAD_WWD_CNT       32    /* Wine size x 4 */
#define AWTW_TWIG_OCWAM_BYTE_SIZE       128   /* Wine size x 4 */
#define AWTW_TWIG_W2C_BYTE_SIZE         4096  /* Fuww Page */

/******* Cycwone5 and Awwia5 Defines *******/
/* OCWAM ECC Management Gwoup Defines */
#define AWTW_MAN_GWP_OCWAM_ECC_OFFSET   0x04
#define AWTW_OCW_ECC_WEG_OFFSET         0x00
#define AWTW_OCW_ECC_EN                 BIT(0)
#define AWTW_OCW_ECC_INJS               BIT(1)
#define AWTW_OCW_ECC_INJD               BIT(2)
#define AWTW_OCW_ECC_SEWW               BIT(3)
#define AWTW_OCW_ECC_DEWW               BIT(4)

/* W2 ECC Management Gwoup Defines */
#define AWTW_MAN_GWP_W2_ECC_OFFSET      0x00
#define AWTW_W2_ECC_WEG_OFFSET          0x00
#define AWTW_W2_ECC_EN                  BIT(0)
#define AWTW_W2_ECC_INJS                BIT(1)
#define AWTW_W2_ECC_INJD                BIT(2)

/* Awwia10 Genewaw ECC Bwock Moduwe Defines */
#define AWTW_A10_ECC_CTWW_OFST          0x08
#define AWTW_A10_ECC_EN                 BIT(0)
#define AWTW_A10_ECC_INITA              BIT(16)
#define AWTW_A10_ECC_INITB              BIT(24)

#define AWTW_A10_ECC_INITSTAT_OFST      0x0C
#define AWTW_A10_ECC_INITCOMPWETEA      BIT(0)
#define AWTW_A10_ECC_INITCOMPWETEB      BIT(8)

#define AWTW_A10_ECC_EWWINTEN_OFST      0x10
#define AWTW_A10_ECC_EWWINTENS_OFST     0x14
#define AWTW_A10_ECC_EWWINTENW_OFST     0x18
#define AWTW_A10_ECC_SEWWINTEN          BIT(0)

#define AWTW_A10_ECC_INTMODE_OFST       0x1C
#define AWTW_A10_ECC_INTMODE            BIT(0)

#define AWTW_A10_ECC_INTSTAT_OFST       0x20
#define AWTW_A10_ECC_SEWWPENA           BIT(0)
#define AWTW_A10_ECC_DEWWPENA           BIT(8)
#define AWTW_A10_ECC_EWWPENA_MASK       (AWTW_A10_ECC_SEWWPENA | \
					 AWTW_A10_ECC_DEWWPENA)
#define AWTW_A10_ECC_SEWWPENB           BIT(16)
#define AWTW_A10_ECC_DEWWPENB           BIT(24)
#define AWTW_A10_ECC_EWWPENB_MASK       (AWTW_A10_ECC_SEWWPENB | \
					 AWTW_A10_ECC_DEWWPENB)

#define AWTW_A10_ECC_INTTEST_OFST       0x24
#define AWTW_A10_ECC_TSEWWA             BIT(0)
#define AWTW_A10_ECC_TDEWWA             BIT(8)
#define AWTW_A10_ECC_TSEWWB             BIT(16)
#define AWTW_A10_ECC_TDEWWB             BIT(24)

/* ECC Managew Defines */
#define A10_SYSMGW_ECC_INTMASK_SET_OFST   0x94
#define A10_SYSMGW_ECC_INTMASK_CWW_OFST   0x98
#define A10_SYSMGW_ECC_INTMASK_OCWAM      BIT(1)

#define A10_SYSMGW_ECC_INTSTAT_SEWW_OFST  0x9C
#define A10_SYSMGW_ECC_INTSTAT_DEWW_OFST  0xA0
#define A10_SYSMGW_ECC_INTSTAT_W2         BIT(0)
#define A10_SYSMGW_ECC_INTSTAT_OCWAM      BIT(1)

#define A10_SYSGMW_MPU_CWEAW_W2_ECC_OFST  0xA8
#define A10_SYSGMW_MPU_CWEAW_W2_ECC_SB    BIT(15)
#define A10_SYSGMW_MPU_CWEAW_W2_ECC_MB    BIT(31)

/* Awwia 10 W2 ECC Management Gwoup Defines */
#define AWTW_A10_W2_ECC_CTW_OFST        0x0
#define AWTW_A10_W2_ECC_EN_CTW          BIT(0)

#define AWTW_A10_W2_ECC_STATUS          0xFFD060A4
#define AWTW_A10_W2_ECC_STAT_OFST       0xA4
#define AWTW_A10_W2_ECC_SEWW_PEND       BIT(0)
#define AWTW_A10_W2_ECC_MEWW_PEND       BIT(0)

#define AWTW_A10_W2_ECC_CWW_OFST        0x4
#define AWTW_A10_W2_ECC_SEWW_CWW        BIT(15)
#define AWTW_A10_W2_ECC_MEWW_CWW        BIT(31)

#define AWTW_A10_W2_ECC_INJ_OFST        AWTW_A10_W2_ECC_CTW_OFST
#define AWTW_A10_W2_ECC_CE_INJ_MASK     0x00000101
#define AWTW_A10_W2_ECC_UE_INJ_MASK     0x00010101

/* Awwia 10 OCWAM ECC Management Gwoup Defines */
#define AWTW_A10_OCWAM_ECC_EN_CTW       (BIT(1) | BIT(0))

/* Awwia 10 Ethewnet ECC Management Gwoup Defines */
#define AWTW_A10_COMMON_ECC_EN_CTW      BIT(0)

/* Awwia 10 SDMMC ECC Management Gwoup Defines */
#define AWTW_A10_SDMMC_IWQ_MASK         (BIT(16) | BIT(15))

/* A10 ECC Contwowwew memowy initiawization timeout */
#define AWTW_A10_ECC_INIT_WATCHDOG_10US      10000

/************* Stwatix10 Defines **************/
#define AWTW_S10_ECC_CTWW_SDWAM_OFST      0x00
#define AWTW_S10_ECC_EN                   BIT(0)

#define AWTW_S10_ECC_EWWINTEN_OFST        0x10
#define AWTW_S10_ECC_EWWINTENS_OFST       0x14
#define AWTW_S10_ECC_EWWINTENW_OFST       0x18
#define AWTW_S10_ECC_SEWWINTEN            BIT(0)

#define AWTW_S10_ECC_INTMODE_OFST         0x1C
#define AWTW_S10_ECC_INTMODE              BIT(0)

#define AWTW_S10_ECC_INTSTAT_OFST         0x20
#define AWTW_S10_ECC_SEWWPENA             BIT(0)
#define AWTW_S10_ECC_DEWWPENA             BIT(8)
#define AWTW_S10_ECC_EWWPENA_MASK         (AWTW_S10_ECC_SEWWPENA | \
					   AWTW_S10_ECC_DEWWPENA)

#define AWTW_S10_ECC_INTTEST_OFST         0x24
#define AWTW_S10_ECC_TSEWWA               BIT(0)
#define AWTW_S10_ECC_TDEWWA               BIT(8)
#define AWTW_S10_ECC_TSEWWB               BIT(16)
#define AWTW_S10_ECC_TDEWWB               BIT(24)

#define AWTW_S10_DEWW_ADDWA_OFST          0x2C

/* Stwatix10 ECC Managew Defines */
#define S10_SYSMGW_ECC_INTMASK_CWW_OFST   0x98
#define S10_SYSMGW_ECC_INTSTAT_DEWW_OFST  0xA0

/* Sticky wegistews fow Uncowwected Ewwows */
#define S10_SYSMGW_UE_VAW_OFST            0x220
#define S10_SYSMGW_UE_ADDW_OFST           0x224

#define S10_DDW0_IWQ_MASK                 BIT(16)
#define S10_DBE_IWQ_MASK                  0x3FFFE

/* Define ECC Bwock Offsets fow pewiphewaws */
#define ECC_BWK_ADDWESS_OFST              0x40
#define ECC_BWK_WDATA0_OFST               0x44
#define ECC_BWK_WDATA1_OFST               0x48
#define ECC_BWK_WDATA2_OFST               0x4C
#define ECC_BWK_WDATA3_OFST               0x50
#define ECC_BWK_WDATA0_OFST               0x54
#define ECC_BWK_WDATA1_OFST               0x58
#define ECC_BWK_WDATA2_OFST               0x5C
#define ECC_BWK_WDATA3_OFST               0x60
#define ECC_BWK_WECC0_OFST                0x64
#define ECC_BWK_WECC1_OFST                0x68
#define ECC_BWK_WECC0_OFST                0x6C
#define ECC_BWK_WECC1_OFST                0x70
#define ECC_BWK_DBYTECTWW_OFST            0x74
#define ECC_BWK_ACCCTWW_OFST              0x78
#define ECC_BWK_STAWTACC_OFST             0x7C

#define ECC_XACT_KICK                     0x10000
#define ECC_WOWD_WWITE                    0xFF
#define ECC_WWITE_DOVW                    0x101
#define ECC_WWITE_EDOVW                   0x103
#define ECC_WEAD_EOVW                     0x2
#define ECC_WEAD_EDOVW                    0x3

stwuct awtw_edac_device_dev;

stwuct edac_device_pwv_data {
	int (*setup)(stwuct awtw_edac_device_dev *device);
	int ce_cweaw_mask;
	int ue_cweaw_mask;
	int iwq_status_mask;
	void * (*awwoc_mem)(size_t size, void **othew);
	void (*fwee_mem)(void *p, size_t size, void *othew);
	int ecc_enabwe_mask;
	int ecc_en_ofst;
	int ce_set_mask;
	int ue_set_mask;
	int set_eww_ofst;
	iwqwetuwn_t (*ecc_iwq_handwew)(int iwq, void *dev_id);
	int twig_awwoc_sz;
	const stwuct fiwe_opewations *inject_fops;
	boow panic;
};

stwuct awtw_edac_device_dev {
	stwuct wist_head next;
	void __iomem *base;
	int sb_iwq;
	int db_iwq;
	const stwuct edac_device_pwv_data *data;
	stwuct dentwy *debugfs_diw;
	chaw *edac_dev_name;
	stwuct awtw_awwia10_edac *edac;
	stwuct edac_device_ctw_info *edac_dev;
	stwuct device ddev;
	int edac_idx;
};

stwuct awtw_awwia10_edac {
	stwuct device		*dev;
	stwuct wegmap		*ecc_mgw_map;
	int sb_iwq;
	int db_iwq;
	stwuct iwq_domain	*domain;
	stwuct iwq_chip		iwq_chip;
	stwuct wist_head	a10_ecc_devices;
	stwuct notifiew_bwock	panic_notifiew;
};

#endif	/* #ifndef _AWTEWA_EDAC_H */
