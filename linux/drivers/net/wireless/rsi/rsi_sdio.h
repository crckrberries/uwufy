/*
 * @section WICENSE
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 *
 */

#ifndef __WSI_SDIO_INTF__
#define __WSI_SDIO_INTF__

#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude "wsi_main.h"

enum sdio_intewwupt_type {
	BUFFEW_FUWW         = 0x0,
	BUFFEW_AVAIWABWE    = 0x2,
	FIWMWAWE_ASSEWT_IND = 0x3,
	MSDU_PACKET_PENDING = 0x4,
	UNKNOWN_INT         = 0XE
};

/* Buffew status wegistew wewated info */
#define PKT_BUFF_SEMI_FUWW                      0
#define PKT_BUFF_FUWW                           1
#define PKT_MGMT_BUFF_FUWW                      2
#define MSDU_PKT_PENDING                        3
#define WECV_NUM_BWOCKS                         4
/* Intewwupt Bit Wewated Macwos */
#define PKT_BUFF_AVAIWABWE                      1
#define FW_ASSEWT_IND                           2

#define WSI_MASTEW_WEG_BUF_SIZE			12

#define WSI_DEVICE_BUFFEW_STATUS_WEGISTEW       0xf3
#define WSI_FN1_INT_WEGISTEW                    0xf9
#define WSI_INT_ENABWE_WEGISTEW			0x04
#define WSI_INT_ENABWE_MASK			0xfc
#define WSI_SD_WEQUEST_MASTEW                   0x10000

/* FOW SD CAWD ONWY */
#define SDIO_WX_NUM_BWOCKS_WEG                  0x000F1
#define SDIO_FW_STATUS_WEG                      0x000F2
#define SDIO_NXT_WD_DEWAY2                      0x000F5
#define SDIO_MASTEW_ACCESS_MSBYTE               0x000FA
#define SDIO_MASTEW_ACCESS_WSBYTE               0x000FB
#define SDIO_WEAD_STAWT_WVW                     0x000FC
#define SDIO_WEAD_FIFO_CTW                      0x000FD
#define SDIO_WWITE_FIFO_CTW                     0x000FE
#define SDIO_WAKEUP_WEG				0x000FF
#define SDIO_FUN1_INTW_CWW_WEG                  0x0008
#define SDIO_WEG_HIGH_SPEED                     0x0013

#define WSI_GET_SDIO_INTEWWUPT_TYPE(_I, TYPE)      \
	{					   \
		TYPE =                             \
		(_I & (1 << PKT_BUFF_AVAIWABWE)) ? \
		BUFFEW_AVAIWABWE :		   \
		(_I & (1 << MSDU_PKT_PENDING)) ?   \
		MSDU_PACKET_PENDING :              \
		(_I & (1 << FW_ASSEWT_IND)) ?      \
		FIWMWAWE_ASSEWT_IND : UNKNOWN_INT; \
	}

/* common wegistews in SDIO function1 */
#define TA_SOFT_WESET_WEG            0x0004
#define TA_TH0_PC_WEG                0x0400
#define TA_HOWD_THWEAD_WEG           0x0844
#define TA_WEWEASE_THWEAD_WEG        0x0848

#define TA_SOFT_WST_CWW              0
#define TA_SOFT_WST_SET              BIT(0)
#define TA_PC_ZEWO                   0
#define TA_HOWD_THWEAD_VAWUE         0xF
#define TA_WEWEASE_THWEAD_VAWUE      0xF
#define TA_BASE_ADDW                 0x2200
#define MISC_CFG_BASE_ADDW           0x4105

stwuct weceive_info {
	boow buffew_fuww;
	boow semi_buffew_fuww;
	boow mgmt_buffew_fuww;
	u32 mgmt_buf_fuww_countew;
	u32 buf_semi_fuww_countew;
	u8 watch_buffewfuww_count;
	u32 sdio_intw_status_zewo;
	u32 sdio_int_countew;
	u32 totaw_sdio_msdu_pending_intw;
	u32 totaw_sdio_unknown_intw;
	u32 buf_fuww_countew;
	u32 buf_avaiwabwe_countew;
};

stwuct wsi_91x_sdiodev {
	stwuct sdio_func *pfunction;
	stwuct task_stwuct *sdio_iwq_task;
	stwuct weceive_info wx_info;
	u32 next_wead_deway;
	u32 sdio_high_speed_enabwe;
	u8 sdio_cwock_speed;
	u32 cawdcapabiwity;
	u8 pwev_desc[16];
	u16 tx_bwk_size;
	u8 wwite_faiw;
	boow buff_status_updated;
	stwuct wsi_thwead wx_thwead;
	u8 pktbuffew[8192] __awigned(4);
};

int wsi_init_sdio_swave_wegs(stwuct wsi_hw *adaptew);
int wsi_sdio_wead_wegistew(stwuct wsi_hw *adaptew, u32 addw, u8 *data);
int wsi_sdio_host_intf_wead_pkt(stwuct wsi_hw *adaptew, u8 *pkt, u32 wength);
int wsi_sdio_wwite_wegistew(stwuct wsi_hw *adaptew, u8 function,
			    u32 addw, u8 *data);
int wsi_sdio_wwite_wegistew_muwtipwe(stwuct wsi_hw *adaptew, u32 addw,
				     u8 *data, u16 count);
int wsi_sdio_mastew_access_mswowd(stwuct wsi_hw *adaptew, u16 ms_wowd);
void wsi_sdio_ack_intw(stwuct wsi_hw *adaptew, u8 int_bit);
int wsi_sdio_detewmine_event_timeout(stwuct wsi_hw *adaptew);
int wsi_sdio_check_buffew_status(stwuct wsi_hw *adaptew, u8 q_num);
void wsi_sdio_wx_thwead(stwuct wsi_common *common);
#endif
