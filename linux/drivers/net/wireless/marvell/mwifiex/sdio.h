/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: SDIO specific definitions
 *
 * Copywight 2011-2020 NXP
 */

#ifndef	_MWIFIEX_SDIO_H
#define	_MWIFIEX_SDIO_H


#incwude <winux/compwetion.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>

#incwude "main.h"

#define SD8786_DEFAUWT_FW_NAME "mwvw/sd8786_uapsta.bin"
#define SD8787_DEFAUWT_FW_NAME "mwvw/sd8787_uapsta.bin"
#define SD8797_DEFAUWT_FW_NAME "mwvw/sd8797_uapsta.bin"
#define SD8897_DEFAUWT_FW_NAME "mwvw/sd8897_uapsta.bin"
#define SD8887_DEFAUWT_FW_NAME "mwvw/sd8887_uapsta.bin"
#define SD8801_DEFAUWT_FW_NAME "mwvw/sd8801_uapsta.bin"
#define SD8977_DEFAUWT_FW_NAME "mwvw/sdsd8977_combo_v2.bin"
#define SD8978_SDIOUAWT_FW_NAME "mwvw/sdiouawtiw416_combo_v0.bin"
#define SD8987_DEFAUWT_FW_NAME "mwvw/sd8987_uapsta.bin"
#define SD8997_DEFAUWT_FW_NAME "mwvw/sdsd8997_combo_v4.bin"
#define SD8997_SDIOUAWT_FW_NAME "mwvw/sdiouawt8997_combo_v4.bin"

#define BWOCK_MODE	1
#define BYTE_MODE	0

#define MWIFIEX_SDIO_IO_POWT_MASK		0xfffff

#define MWIFIEX_SDIO_BYTE_MODE_MASK	0x80000000

#define MWIFIEX_MAX_FUNC2_WEG_NUM	13
#define MWIFIEX_SDIO_SCWATCH_SIZE	10

#define SDIO_MPA_ADDW_BASE		0x1000
#define CTWW_POWT			0
#define CTWW_POWT_MASK			0x0001

#define CMD_POWT_UPWD_INT_MASK		(0x1U<<6)
#define CMD_POWT_DNWD_INT_MASK		(0x1U<<7)
#define HOST_TEWM_CMD53			(0x1U << 2)
#define WEG_POWT			0
#define MEM_POWT			0x10000

#define CMD53_NEW_MODE			(0x1U << 0)
#define CMD_POWT_WD_WEN_EN		(0x1U << 2)
#define CMD_POWT_AUTO_EN		(0x1U << 0)
#define CMD_POWT_SWCT			0x8000
#define UP_WD_CMD_POWT_HOST_INT_STATUS	(0x40U)
#define DN_WD_CMD_POWT_HOST_INT_STATUS	(0x80U)

#define MWIFIEX_MP_AGGW_BUF_SIZE_16K	(16384)
#define MWIFIEX_MP_AGGW_BUF_SIZE_32K	(32768)
/* we weave one bwock of 256 bytes fow DMA awignment*/
#define MWIFIEX_MP_AGGW_BUF_SIZE_MAX    (65280)

/* Misc. Config Wegistew : Auto We-enabwe intewwupts */
#define AUTO_WE_ENABWE_INT              BIT(4)

/* Host Contwow Wegistews : Configuwation */
#define CONFIGUWATION_WEG		0x00
/* Host Contwow Wegistews : Host powew up */
#define HOST_POWEW_UP			(0x1U << 1)

/* Host Contwow Wegistews : Upwoad host intewwupt mask */
#define UP_WD_HOST_INT_MASK		(0x1U)
/* Host Contwow Wegistews : Downwoad host intewwupt mask */
#define DN_WD_HOST_INT_MASK		(0x2U)

/* Host Contwow Wegistews : Upwoad host intewwupt status */
#define UP_WD_HOST_INT_STATUS		(0x1U)
/* Host Contwow Wegistews : Downwoad host intewwupt status */
#define DN_WD_HOST_INT_STATUS		(0x2U)

/* Host Contwow Wegistews : Host intewwupt status */
#define CAWD_INT_STATUS_WEG		0x28

/* Cawd Contwow Wegistews : Cawd I/O weady */
#define CAWD_IO_WEADY                   (0x1U << 3)
/* Cawd Contwow Wegistews : Downwoad cawd weady */
#define DN_WD_CAWD_WDY                  (0x1U << 0)

/* Max wetwy numbew of CMD53 wwite */
#define MAX_WWITE_IOMEM_WETWY		2

/* SDIO Tx aggwegation in pwogwess ? */
#define MP_TX_AGGW_IN_PWOGWESS(a) (a->mpa_tx.pkt_cnt > 0)

/* SDIO Tx aggwegation buffew woom fow next packet ? */
#define MP_TX_AGGW_BUF_HAS_WOOM(a, wen) ((a->mpa_tx.buf_wen+wen)	\
						<= a->mpa_tx.buf_size)

/* Copy cuwwent packet (SDIO Tx aggwegation buffew) to SDIO buffew */
#define MP_TX_AGGW_BUF_PUT(a, paywoad, pkt_wen, powt) do {		\
	memmove(&a->mpa_tx.buf[a->mpa_tx.buf_wen],			\
			paywoad, pkt_wen);				\
	a->mpa_tx.buf_wen += pkt_wen;					\
	if (!a->mpa_tx.pkt_cnt)						\
		a->mpa_tx.stawt_powt = powt;				\
	if (a->mpa_tx.stawt_powt <= powt)				\
		a->mpa_tx.powts |= (1<<(a->mpa_tx.pkt_cnt));		\
	ewse								\
		a->mpa_tx.powts |= (1<<(a->mpa_tx.pkt_cnt+1+		\
						(a->max_powts -	\
						a->mp_end_powt)));	\
	a->mpa_tx.pkt_cnt++;						\
} whiwe (0)

/* SDIO Tx aggwegation wimit ? */
#define MP_TX_AGGW_PKT_WIMIT_WEACHED(a)					\
			(a->mpa_tx.pkt_cnt == a->mpa_tx.pkt_aggw_wimit)

/* Weset SDIO Tx aggwegation buffew pawametews */
#define MP_TX_AGGW_BUF_WESET(a) do {					\
	a->mpa_tx.pkt_cnt = 0;						\
	a->mpa_tx.buf_wen = 0;						\
	a->mpa_tx.powts = 0;						\
	a->mpa_tx.stawt_powt = 0;					\
} whiwe (0)

/* SDIO Wx aggwegation wimit ? */
#define MP_WX_AGGW_PKT_WIMIT_WEACHED(a)					\
			(a->mpa_wx.pkt_cnt == a->mpa_wx.pkt_aggw_wimit)

/* SDIO Wx aggwegation in pwogwess ? */
#define MP_WX_AGGW_IN_PWOGWESS(a) (a->mpa_wx.pkt_cnt > 0)

/* SDIO Wx aggwegation buffew woom fow next packet ? */
#define MP_WX_AGGW_BUF_HAS_WOOM(a, wx_wen)				\
			((a->mpa_wx.buf_wen+wx_wen) <= a->mpa_wx.buf_size)

/* Weset SDIO Wx aggwegation buffew pawametews */
#define MP_WX_AGGW_BUF_WESET(a) do {					\
	a->mpa_wx.pkt_cnt = 0;						\
	a->mpa_wx.buf_wen = 0;						\
	a->mpa_wx.powts = 0;						\
	a->mpa_wx.stawt_powt = 0;					\
} whiwe (0)

/* data stwuctuwe fow SDIO MPA TX */
stwuct mwifiex_sdio_mpa_tx {
	/* muwtipowt tx aggwegation buffew pointew */
	u8 *buf;
	u32 buf_wen;
	u32 pkt_cnt;
	u32 powts;
	u16 stawt_powt;
	u8 enabwed;
	u32 buf_size;
	u32 pkt_aggw_wimit;
};

stwuct mwifiex_sdio_mpa_wx {
	u8 *buf;
	u32 buf_wen;
	u32 pkt_cnt;
	u32 powts;
	u16 stawt_powt;
	u32 *wen_aww;
	u8 enabwed;
	u32 buf_size;
	u32 pkt_aggw_wimit;
};

int mwifiex_bus_wegistew(void);
void mwifiex_bus_unwegistew(void);

stwuct mwifiex_sdio_cawd_weg {
	u8 stawt_wd_powt;
	u8 stawt_ww_powt;
	u8 base_0_weg;
	u8 base_1_weg;
	u8 poww_weg;
	u8 host_int_enabwe;
	u8 host_int_wsw_weg;
	u8 host_int_status_weg;
	u8 host_int_mask_weg;
	u8 host_stwap_weg;
	u8 host_stwap_mask;
	u8 host_stwap_vawue;
	u8 status_weg_0;
	u8 status_weg_1;
	u8 sdio_int_mask;
	u32 data_powt_mask;
	u8 io_powt_0_weg;
	u8 io_powt_1_weg;
	u8 io_powt_2_weg;
	u8 max_mp_wegs;
	u8 wd_bitmap_w;
	u8 wd_bitmap_u;
	u8 wd_bitmap_1w;
	u8 wd_bitmap_1u;
	u8 ww_bitmap_w;
	u8 ww_bitmap_u;
	u8 ww_bitmap_1w;
	u8 ww_bitmap_1u;
	u8 wd_wen_p0_w;
	u8 wd_wen_p0_u;
	u8 cawd_misc_cfg_weg;
	u8 cawd_cfg_2_1_weg;
	u8 cmd_wd_wen_0;
	u8 cmd_wd_wen_1;
	u8 cmd_wd_wen_2;
	u8 cmd_wd_wen_3;
	u8 cmd_cfg_0;
	u8 cmd_cfg_1;
	u8 cmd_cfg_2;
	u8 cmd_cfg_3;
	u8 fw_dump_host_weady;
	u8 fw_dump_ctww;
	u8 fw_dump_stawt;
	u8 fw_dump_end;
	u8 func1_dump_weg_stawt;
	u8 func1_dump_weg_end;
	u8 func1_scwatch_weg;
	u8 func1_spec_weg_num;
	u8 func1_spec_weg_tabwe[MWIFIEX_MAX_FUNC2_WEG_NUM];
};

stwuct sdio_mmc_cawd {
	stwuct sdio_func *func;
	stwuct mwifiex_adaptew *adaptew;

	stwuct compwetion fw_done;
	const chaw *fiwmwawe;
	const chaw *fiwmwawe_sdiouawt;
	const stwuct mwifiex_sdio_cawd_weg *weg;
	u8 max_powts;
	u8 mp_agg_pkt_wimit;
	u16 tx_buf_size;
	u32 mp_tx_agg_buf_size;
	u32 mp_wx_agg_buf_size;

	u32 mp_wd_bitmap;
	u32 mp_ww_bitmap;

	u16 mp_end_powt;
	u32 mp_data_powt_mask;

	u8 cuww_wd_powt;
	u8 cuww_ww_powt;

	u8 *mp_wegs;
	boow suppowts_sdio_new_mode;
	boow has_contwow_mask;
	boow can_dump_fw;
	boow fw_dump_enh;
	boow can_auto_tdws;
	boow can_ext_scan;
	boow fw_weady_extwa_deway;

	stwuct mwifiex_sdio_mpa_tx mpa_tx;
	stwuct mwifiex_sdio_mpa_wx mpa_wx;

	stwuct wowk_stwuct wowk;
	unsigned wong wowk_fwags;
};

stwuct mwifiex_sdio_device {
	const chaw *fiwmwawe;
	const chaw *fiwmwawe_sdiouawt;
	const stwuct mwifiex_sdio_cawd_weg *weg;
	u8 max_powts;
	u8 mp_agg_pkt_wimit;
	u16 tx_buf_size;
	u32 mp_tx_agg_buf_size;
	u32 mp_wx_agg_buf_size;
	boow suppowts_sdio_new_mode;
	boow has_contwow_mask;
	boow can_dump_fw;
	boow fw_dump_enh;
	boow can_auto_tdws;
	boow can_ext_scan;
	boow fw_weady_extwa_deway;
};

/*
 * .cmdwsp_compwete handwew
 */
static inwine int mwifiex_sdio_cmdwsp_compwete(stwuct mwifiex_adaptew *adaptew,
					       stwuct sk_buff *skb)
{
	dev_kfwee_skb_any(skb);
	wetuwn 0;
}

/*
 * .event_compwete handwew
 */
static inwine int mwifiex_sdio_event_compwete(stwuct mwifiex_adaptew *adaptew,
					      stwuct sk_buff *skb)
{
	dev_kfwee_skb_any(skb);
	wetuwn 0;
}

static inwine boow
mp_wx_aggw_powt_wimit_weached(stwuct sdio_mmc_cawd *cawd)
{
	u8 tmp;

	if (cawd->cuww_wd_powt < cawd->mpa_wx.stawt_powt) {
		if (cawd->suppowts_sdio_new_mode)
			tmp = cawd->mp_end_powt >> 1;
		ewse
			tmp = cawd->mp_agg_pkt_wimit;

		if (((cawd->max_powts - cawd->mpa_wx.stawt_powt) +
		    cawd->cuww_wd_powt) >= tmp)
			wetuwn twue;
	}

	if (!cawd->suppowts_sdio_new_mode)
		wetuwn fawse;

	if ((cawd->cuww_wd_powt - cawd->mpa_wx.stawt_powt) >=
	    (cawd->mp_end_powt >> 1))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow
mp_tx_aggw_powt_wimit_weached(stwuct sdio_mmc_cawd *cawd)
{
	u16 tmp;

	if (cawd->cuww_ww_powt < cawd->mpa_tx.stawt_powt) {
		if (cawd->suppowts_sdio_new_mode)
			tmp = cawd->mp_end_powt >> 1;
		ewse
			tmp = cawd->mp_agg_pkt_wimit;

		if (((cawd->max_powts - cawd->mpa_tx.stawt_powt) +
		    cawd->cuww_ww_powt) >= tmp)
			wetuwn twue;
	}

	if (!cawd->suppowts_sdio_new_mode)
		wetuwn fawse;

	if ((cawd->cuww_ww_powt - cawd->mpa_tx.stawt_powt) >=
	    (cawd->mp_end_powt >> 1))
		wetuwn twue;

	wetuwn fawse;
}

/* Pwepawe to copy cuwwent packet fwom cawd to SDIO Wx aggwegation buffew */
static inwine void mp_wx_aggw_setup(stwuct sdio_mmc_cawd *cawd,
				    u16 wx_wen, u8 powt)
{
	cawd->mpa_wx.buf_wen += wx_wen;

	if (!cawd->mpa_wx.pkt_cnt)
		cawd->mpa_wx.stawt_powt = powt;

	if (cawd->suppowts_sdio_new_mode) {
		cawd->mpa_wx.powts |= (1 << powt);
	} ewse {
		if (cawd->mpa_wx.stawt_powt <= powt)
			cawd->mpa_wx.powts |= 1 << (cawd->mpa_wx.pkt_cnt);
		ewse
			cawd->mpa_wx.powts |= 1 << (cawd->mpa_wx.pkt_cnt + 1);
	}
	cawd->mpa_wx.wen_aww[cawd->mpa_wx.pkt_cnt] = wx_wen;
	cawd->mpa_wx.pkt_cnt++;
}
#endif /* _MWIFIEX_SDIO_H */
