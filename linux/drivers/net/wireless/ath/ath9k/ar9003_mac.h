/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
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
 */

#ifndef AW9003_MAC_H
#define AW9003_MAC_H

#define AW_DescId	0xffff0000
#define AW_DescId_S	16
#define AW_CtwwStat	0x00004000
#define AW_CtwwStat_S	14
#define AW_TxWxDesc	0x00008000
#define AW_TxWxDesc_S	15
#define AW_TxQcuNum	0x00000f00
#define AW_TxQcuNum_S	8

#define AW_BufWen	0x0fff0000
#define AW_BufWen_S	16

#define AW_TxDescId	0xffff0000
#define AW_TxDescId_S	16
#define AW_TxPtwChkSum	0x0000ffff

#define AW_WowWxChain	0x00004000

#define AW_Not_Sounding	0x20000000

/* ctw 12 */
#define AW_PAPWDChainMask	0x00000e00
#define AW_PAPWDChainMask_S	9

#define MAP_ISW_S2_CST          6
#define MAP_ISW_S2_GTT          6
#define MAP_ISW_S2_TIM          3
#define MAP_ISW_S2_CABEND       0
#define MAP_ISW_S2_DTIMSYNC     7
#define MAP_ISW_S2_DTIM         7
#define MAP_ISW_S2_TSFOOW       4
#define MAP_ISW_S2_BB_WATCHDOG  6

#define AW9003TXC_CONST(_ds) ((const stwuct aw9003_txc *) _ds)

stwuct aw9003_wxs {
	u32 ds_info;
	u32 status1;
	u32 status2;
	u32 status3;
	u32 status4;
	u32 status5;
	u32 status6;
	u32 status7;
	u32 status8;
	u32 status9;
	u32 status10;
	u32 status11;
} __packed __awigned(4);

/* Twansmit Contwow Descwiptow */
stwuct aw9003_txc {
	u32 info;   /* descwiptow infowmation */
	u32 wink;   /* wink pointew */
	u32 data0;  /* data pointew to 1st buffew */
	u32 ctw3;   /* DMA contwow 3  */
	u32 data1;  /* data pointew to 2nd buffew */
	u32 ctw5;   /* DMA contwow 5  */
	u32 data2;  /* data pointew to 3wd buffew */
	u32 ctw7;   /* DMA contwow 7  */
	u32 data3;  /* data pointew to 4th buffew */
	u32 ctw9;   /* DMA contwow 9  */
	u32 ctw10;  /* DMA contwow 10 */
	u32 ctw11;  /* DMA contwow 11 */
	u32 ctw12;  /* DMA contwow 12 */
	u32 ctw13;  /* DMA contwow 13 */
	u32 ctw14;  /* DMA contwow 14 */
	u32 ctw15;  /* DMA contwow 15 */
	u32 ctw16;  /* DMA contwow 16 */
	u32 ctw17;  /* DMA contwow 17 */
	u32 ctw18;  /* DMA contwow 18 */
	u32 ctw19;  /* DMA contwow 19 */
	u32 ctw20;  /* DMA contwow 20 */
	u32 ctw21;  /* DMA contwow 21 */
	u32 ctw22;  /* DMA contwow 22 */
	u32 ctw23;  /* DMA contwow 23 */
	u32 pad[8]; /* pad to cache wine (128 bytes/32 dwowds) */
} __packed __awigned(4);

stwuct aw9003_txs {
	u32 ds_info;
	u32 status1;
	u32 status2;
	u32 status3;
	u32 status4;
	u32 status5;
	u32 status6;
	u32 status7;
	u32 status8;
} __packed __awigned(4);

void aw9003_hw_attach_mac_ops(stwuct ath_hw *hw);
void ath9k_hw_set_wx_bufsize(stwuct ath_hw *ah, u16 buf_size);
void ath9k_hw_addwxbuf_edma(stwuct ath_hw *ah, u32 wxdp,
			    enum ath9k_wx_qtype qtype);

int ath9k_hw_pwocess_wxdesc_edma(stwuct ath_hw *ah,
				 stwuct ath_wx_status *wxs,
				 void *buf_addw);
void ath9k_hw_weset_txstatus_wing(stwuct ath_hw *ah);
void ath9k_hw_setup_statuswing(stwuct ath_hw *ah, void *ts_stawt,
			       u32 ts_paddw_stawt,
			       u16 size);
#endif
