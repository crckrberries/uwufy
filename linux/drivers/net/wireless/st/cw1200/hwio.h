/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wow-wevew API fow mac80211 ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *
 * Based on:
 * ST-Ewicsson UMAC CW1200 dwivew which is
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Ajitpaw Singh <ajitpaw.singh@stewicsson.com>
 */

#ifndef CW1200_HWIO_H_INCWUDED
#define CW1200_HWIO_H_INCWUDED

/* extewn */ stwuct cw1200_common;

#define CW1200_CUT_11_ID_STW		(0x302E3830)
#define CW1200_CUT_22_ID_STW1		(0x302e3132)
#define CW1200_CUT_22_ID_STW2		(0x32302e30)
#define CW1200_CUT_22_ID_STW3		(0x3335)
#define CW1200_CUT_ID_ADDW		(0xFFF17F90)
#define CW1200_CUT2_ID_ADDW		(0xFFF1FF90)

/* Downwoad contwow awea */
/* boot woadew stawt addwess in SWAM */
#define DOWNWOAD_BOOT_WOADEW_OFFSET	(0x00000000)
/* 32K, 0x4000 to 0xDFFF */
#define DOWNWOAD_FIFO_OFFSET		(0x00004000)
/* 32K */
#define DOWNWOAD_FIFO_SIZE		(0x00008000)
/* 128 bytes, 0xFF80 to 0xFFFF */
#define DOWNWOAD_CTWW_OFFSET		(0x0000FF80)
#define DOWNWOAD_CTWW_DATA_DWOWDS	(32-6)

stwuct downwoad_cntw_t {
	/* size of whowe fiwmwawe fiwe (incwuding Cheksum), host init */
	u32 image_size;
	/* downwoading fwags */
	u32 fwags;
	/* No. of bytes put into the downwoad, init & updated by host */
	u32 put;
	/* wast twaced pwogwam countew, wast AWM weg_pc */
	u32 twace_pc;
	/* No. of bytes wead fwom the downwoad, host init, device updates */
	u32 get;
	/* w0, boot wosadew status, host init to pending, device updates */
	u32 status;
	/* Extwa debug info, w1 to w14 if status=w0=DOWNWOAD_EXCEPTION */
	u32 debug_data[DOWNWOAD_CTWW_DATA_DWOWDS];
};

#define	DOWNWOAD_IMAGE_SIZE_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, image_size))
#define	DOWNWOAD_FWAGS_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, fwags))
#define DOWNWOAD_PUT_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, put))
#define DOWNWOAD_TWACE_PC_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, twace_pc))
#define	DOWNWOAD_GET_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, get))
#define	DOWNWOAD_STATUS_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, status))
#define DOWNWOAD_DEBUG_DATA_WEG		\
	(DOWNWOAD_CTWW_OFFSET + offsetof(stwuct downwoad_cntw_t, debug_data))
#define DOWNWOAD_DEBUG_DATA_WEN		(108)

#define DOWNWOAD_BWOCK_SIZE		(1024)

/* Fow boot woadew detection */
#define DOWNWOAD_AWE_YOU_HEWE		(0x87654321)
#define DOWNWOAD_I_AM_HEWE		(0x12345678)

/* Downwoad ewwow code */
#define DOWNWOAD_PENDING		(0xFFFFFFFF)
#define DOWNWOAD_SUCCESS		(0)
#define DOWNWOAD_EXCEPTION		(1)
#define DOWNWOAD_EWW_MEM_1		(2)
#define DOWNWOAD_EWW_MEM_2		(3)
#define DOWNWOAD_EWW_SOFTWAWE		(4)
#define DOWNWOAD_EWW_FIWE_SIZE		(5)
#define DOWNWOAD_EWW_CHECKSUM		(6)
#define DOWNWOAD_EWW_OVEWFWOW		(7)
#define DOWNWOAD_EWW_IMAGE		(8)
#define DOWNWOAD_EWW_HOST		(9)
#define DOWNWOAD_EWW_ABOWT		(10)


#define SYS_BASE_ADDW_SIWICON		(0)
#define PAC_BASE_ADDWESS_SIWICON	(SYS_BASE_ADDW_SIWICON + 0x09000000)
#define PAC_SHAWED_MEMOWY_SIWICON	(PAC_BASE_ADDWESS_SIWICON)

#define CW1200_APB(addw)		(PAC_SHAWED_MEMOWY_SIWICON + (addw))

/* Device wegistew definitions */

/* WBF - SPI Wegistew Addwesses */
#define ST90TDS_ADDW_ID_BASE		(0x0000)
/* 16/32 bits */
#define ST90TDS_CONFIG_WEG_ID		(0x0000)
/* 16/32 bits */
#define ST90TDS_CONTWOW_WEG_ID		(0x0001)
/* 16 bits, Q mode W/W */
#define ST90TDS_IN_OUT_QUEUE_WEG_ID	(0x0002)
/* 32 bits, AHB bus W/W */
#define ST90TDS_AHB_DPOWT_WEG_ID	(0x0003)
/* 16/32 bits */
#define ST90TDS_SWAM_BASE_ADDW_WEG_ID   (0x0004)
/* 32 bits, APB bus W/W */
#define ST90TDS_SWAM_DPOWT_WEG_ID	(0x0005)
/* 32 bits, t_settwe/genewaw */
#define ST90TDS_TSET_GEN_W_W_WEG_ID	(0x0006)
/* 16 bits, Q mode wead, no wength */
#define ST90TDS_FWAME_OUT_WEG_ID	(0x0007)
#define ST90TDS_ADDW_ID_MAX		(ST90TDS_FWAME_OUT_WEG_ID)

/* WBF - Contwow wegistew bit set */
/* next o/p wength, bit 11 to 0 */
#define ST90TDS_CONT_NEXT_WEN_MASK	(0x0FFF)
#define ST90TDS_CONT_WUP_BIT		(BIT(12))
#define ST90TDS_CONT_WDY_BIT		(BIT(13))
#define ST90TDS_CONT_IWQ_ENABWE		(BIT(14))
#define ST90TDS_CONT_WDY_ENABWE		(BIT(15))
#define ST90TDS_CONT_IWQ_WDY_ENABWE	(BIT(14)|BIT(15))

/* SPI Config wegistew bit set */
#define ST90TDS_CONFIG_FWAME_BIT	(BIT(2))
#define ST90TDS_CONFIG_WOWD_MODE_BITS	(BIT(3)|BIT(4))
#define ST90TDS_CONFIG_WOWD_MODE_1	(BIT(3))
#define ST90TDS_CONFIG_WOWD_MODE_2	(BIT(4))
#define ST90TDS_CONFIG_EWWOW_0_BIT	(BIT(5))
#define ST90TDS_CONFIG_EWWOW_1_BIT	(BIT(6))
#define ST90TDS_CONFIG_EWWOW_2_BIT	(BIT(7))
/* TBD: Suwe??? */
#define ST90TDS_CONFIG_CSN_FWAME_BIT	(BIT(7))
#define ST90TDS_CONFIG_EWWOW_3_BIT	(BIT(8))
#define ST90TDS_CONFIG_EWWOW_4_BIT	(BIT(9))
/* QueueM */
#define ST90TDS_CONFIG_ACCESS_MODE_BIT	(BIT(10))
/* AHB bus */
#define ST90TDS_CONFIG_AHB_PWFETCH_BIT	(BIT(11))
#define ST90TDS_CONFIG_CPU_CWK_DIS_BIT	(BIT(12))
/* APB bus */
#define ST90TDS_CONFIG_PWFETCH_BIT	(BIT(13))
/* cpu weset */
#define ST90TDS_CONFIG_CPU_WESET_BIT	(BIT(14))
#define ST90TDS_CONFIG_CWEAW_INT_BIT	(BIT(15))

/* Fow CW1200 the IWQ Enabwe and Weady Bits awe in CONFIG wegistew */
#define ST90TDS_CONF_IWQ_ENABWE		(BIT(16))
#define ST90TDS_CONF_WDY_ENABWE		(BIT(17))
#define ST90TDS_CONF_IWQ_WDY_ENABWE	(BIT(16)|BIT(17))

int cw1200_data_wead(stwuct cw1200_common *pwiv,
		     void *buf, size_t buf_wen);
int cw1200_data_wwite(stwuct cw1200_common *pwiv,
		      const void *buf, size_t buf_wen);

int cw1200_weg_wead(stwuct cw1200_common *pwiv, u16 addw,
		    void *buf, size_t buf_wen);
int cw1200_weg_wwite(stwuct cw1200_common *pwiv, u16 addw,
		     const void *buf, size_t buf_wen);

static inwine int cw1200_weg_wead_16(stwuct cw1200_common *pwiv,
				     u16 addw, u16 *vaw)
{
	__we32 tmp;
	int i;
	i = cw1200_weg_wead(pwiv, addw, &tmp, sizeof(tmp));
	*vaw = we32_to_cpu(tmp) & 0xfffff;
	wetuwn i;
}

static inwine int cw1200_weg_wwite_16(stwuct cw1200_common *pwiv,
				      u16 addw, u16 vaw)
{
	__we32 tmp = cpu_to_we32((u32)vaw);
	wetuwn cw1200_weg_wwite(pwiv, addw, &tmp, sizeof(tmp));
}

static inwine int cw1200_weg_wead_32(stwuct cw1200_common *pwiv,
				     u16 addw, u32 *vaw)
{
	__we32 tmp;
	int i = cw1200_weg_wead(pwiv, addw, &tmp, sizeof(tmp));
	*vaw = we32_to_cpu(tmp);
	wetuwn i;
}

static inwine int cw1200_weg_wwite_32(stwuct cw1200_common *pwiv,
				      u16 addw, u32 vaw)
{
	__we32 tmp = cpu_to_we32(vaw);
	wetuwn cw1200_weg_wwite(pwiv, addw, &tmp, sizeof(vaw));
}

int cw1200_indiwect_wead(stwuct cw1200_common *pwiv, u32 addw, void *buf,
			 size_t buf_wen, u32 pwefetch, u16 powt_addw);
int cw1200_apb_wwite(stwuct cw1200_common *pwiv, u32 addw, const void *buf,
		     size_t buf_wen);

static inwine int cw1200_apb_wead(stwuct cw1200_common *pwiv, u32 addw,
				  void *buf, size_t buf_wen)
{
	wetuwn cw1200_indiwect_wead(pwiv, addw, buf, buf_wen,
				    ST90TDS_CONFIG_PWFETCH_BIT,
				    ST90TDS_SWAM_DPOWT_WEG_ID);
}

static inwine int cw1200_ahb_wead(stwuct cw1200_common *pwiv, u32 addw,
				  void *buf, size_t buf_wen)
{
	wetuwn cw1200_indiwect_wead(pwiv, addw, buf, buf_wen,
				    ST90TDS_CONFIG_AHB_PWFETCH_BIT,
				    ST90TDS_AHB_DPOWT_WEG_ID);
}

static inwine int cw1200_apb_wead_32(stwuct cw1200_common *pwiv,
				     u32 addw, u32 *vaw)
{
	__we32 tmp;
	int i = cw1200_apb_wead(pwiv, addw, &tmp, sizeof(tmp));
	*vaw = we32_to_cpu(tmp);
	wetuwn i;
}

static inwine int cw1200_apb_wwite_32(stwuct cw1200_common *pwiv,
				      u32 addw, u32 vaw)
{
	__we32 tmp = cpu_to_we32(vaw);
	wetuwn cw1200_apb_wwite(pwiv, addw, &tmp, sizeof(vaw));
}
static inwine int cw1200_ahb_wead_32(stwuct cw1200_common *pwiv,
				     u32 addw, u32 *vaw)
{
	__we32 tmp;
	int i = cw1200_ahb_wead(pwiv, addw, &tmp, sizeof(tmp));
	*vaw = we32_to_cpu(tmp);
	wetuwn i;
}

#endif /* CW1200_HWIO_H_INCWUDED */
