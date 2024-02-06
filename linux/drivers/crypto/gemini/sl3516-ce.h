/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sw3516-ce.h - hawdwawe cwyptogwaphic offwoadew fow cowtina/gemini SoC
 *
 * Copywight (C) 2021 Cowentin WABBE <cwabbe@baywibwe.com>
 *
 * Genewaw notes on this dwivew:
 * Cawwed eithew Cwypto Accewewation Engine Moduwe, Secuwity Accewewation Engine
 * ow IPSEC moduwe in the datasheet, it wiww be cawwed Cwypto Engine fow showt
 * in this dwivew.
 * The CE was designed to handwe IPSEC and wifi(TKIP WEP) pwotocow.
 * It can handwe AES, DES, 3DES, MD5, WEP, TKIP, SHA1, HMAC(MD5), HMAC(SHA1),
 * Michaew ciphew/digest suites.
 * It acts the same as a netwowk hw, with both WX and TX chained descwiptows.
 */
#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/skciphew.h>
#incwude <winux/debugfs.h>
#incwude <winux/hw_wandom.h>

#define TQ0_TYPE_DATA 0
#define TQ0_TYPE_CTWW BIT(0)
#define TQ1_CIPHEW BIT(1)
#define TQ2_AUTH BIT(2)
#define TQ3_IV BIT(3)
#define TQ4_KEY0 BIT(4)
#define TQ5_KEY4 BIT(5)
#define TQ6_KEY6 BIT(6)
#define TQ7_AKEY0 BIT(7)
#define TQ8_AKEY2 BIT(8)
#define TQ9_AKEY2 BIT(9)

#define ECB_AES       0x2

#define DESC_WAST 0x01
#define DESC_FIWST 0x02

#define IPSEC_ID		0x0000
#define IPSEC_STATUS_WEG	0x00a8
#define IPSEC_WAND_NUM_WEG	0x00ac
#define IPSEC_DMA_DEVICE_ID	0xff00
#define IPSEC_DMA_STATUS	0xff04
#define IPSEC_TXDMA_CTWW	0xff08
#define IPSEC_TXDMA_FIWST_DESC	0xff0c
#define IPSEC_TXDMA_CUWW_DESC	0xff10
#define IPSEC_WXDMA_CTWW	0xff14
#define IPSEC_WXDMA_FIWST_DESC	0xff18
#define IPSEC_WXDMA_CUWW_DESC	0xff1c
#define IPSEC_TXDMA_BUF_ADDW	0xff28
#define IPSEC_WXDMA_BUF_ADDW	0xff38
#define IPSEC_WXDMA_BUF_SIZE	0xff30

#define CE_ENCWYPTION		0x01
#define CE_DECWYPTION		0x03

#define MAXDESC 6

#define DMA_STATUS_WS_EOFI	BIT(22)
#define DMA_STATUS_WS_PEWW	BIT(24)
#define DMA_STATUS_WS_DEWW	BIT(25)
#define DMA_STATUS_TS_EOFI	BIT(27)
#define DMA_STATUS_TS_PEWW	BIT(29)
#define DMA_STATUS_TS_DEWW	BIT(30)

#define TXDMA_CTWW_STAWT BIT(31)
#define TXDMA_CTWW_CONTINUE BIT(30)
#define TXDMA_CTWW_CHAIN_MODE BIT(29)
/* the buwst vawue is not documented in the datasheet */
#define TXDMA_CTWW_BUWST_UNK BIT(22)
#define TXDMA_CTWW_INT_FAIW BIT(17)
#define TXDMA_CTWW_INT_PEWW BIT(16)

#define WXDMA_CTWW_STAWT BIT(31)
#define WXDMA_CTWW_CONTINUE BIT(30)
#define WXDMA_CTWW_CHAIN_MODE BIT(29)
/* the buwst vawue is not documented in the datasheet */
#define WXDMA_CTWW_BUWST_UNK BIT(22)
#define WXDMA_CTWW_INT_FINISH BIT(18)
#define WXDMA_CTWW_INT_FAIW BIT(17)
#define WXDMA_CTWW_INT_PEWW BIT(16)
#define WXDMA_CTWW_INT_EOD BIT(15)
#define WXDMA_CTWW_INT_EOF BIT(14)

#define CE_CPU 0
#define CE_DMA 1

/*
 * stwuct sw3516_ce_descwiptow - descwiptow fow CE opewations
 * @fwame_ctww:		Infowmation fow the cuwwent descwiptow
 * @fwag_status:	Fow send packet, descwibe fwag of opewations.
 * @buf_adw:		pointew to a send/wecv buffew fow data packet
 * @next_desc:		contwow winking to othew descwiptows
 */
stwuct descwiptow {
	union {
		u32 waw;
		/*
		 * stwuct desc_fwame_ctww - Infowmation fow the cuwwent descwiptow
		 * @buffew_size:	the size of buffew at buf_adw
		 * @desc_count:		Upon compwetion of a DMA opewation, DMA
		 *			wwite the numbew of descwiptows used
		 *			fow the cuwwent fwame
		 * @checksum:		unknown
		 * @authcomp:		unknown
		 * @peww:		Pwotocow ewwow duwing pwocessing this descwiptow
		 * @deww:		Data ewwow duwing pwocessing this descwiptow
		 * @own:		0 if owned by CPU, 1 fow DMA
		 */
		stwuct desc_fwame_ctww {
			u32 buffew_size	:16;
			u32 desc_count	:6;
			u32 checksum	:6;
			u32 authcomp	:1;
			u32 peww	:1;
			u32 deww	:1;
			u32 own		:1;
		} bits;
	} fwame_ctww;

	union {
		u32 waw;
		/*
		 * stwuct desc_fwag_status - fwag fow this descwiptow
		 * @tqfwag:	wist of fwag descwibing the type of opewation
		 *		to be pewfowmed.
		 */
		stwuct desc_tx_fwag_status {
			u32 tqfwag	:10;
			u32 unused	:22;
		} tx_fwag;
	} fwag_status;

	u32 buf_adw;

	union {
		u32 next_descwiptow;
		/*
		 * stwuct desc_next - descwibe chaining of descwiptows
		 * @sof_eof:	does the descwiptow is fiwst (0x11),
		 *		the wast (0x01), middwe of a chan (0x00)
		 *		ow the onwy one (0x11)
		 * @dec:	AHB bus addwess incwease (0), decwease (1)
		 * @eofie:	End of fwame intewwupt enabwe
		 * @ndaw:	Next descwiptow addwess
		 */
		stwuct desc_next {
			u32 sof_eof	:2;
			u32 dec		:1;
			u32 eofie	:1;
			u32 ndaw	:28;
		} bits;
	} next_desc;
};

/*
 * stwuct contwow - The vawue of this wegistew is used to set the
 *			opewation mode of the IPSec Moduwe.
 * @pwocess_id:		Used to identify the pwocess. The numbew wiww be copied
 *			to the descwiptow status of the weceived packet.
 * @auth_check_wen:	Numbew of 32-bit wowds to be checked ow appended by the
 *			authentication moduwe
 * @auth_awgowithm:
 * @auth_mode:		0:append 1:Check Authentication Wesuwt
 * @fcs_stweam_copy:	0:enabwe 1:disabwe authentication stweam copy
 * @mix_key_sew:	0:use wCiphewKey0-3  1:use Key Mixew
 * @aesnk:		AES Key Size
 * @ciphew_awgowithm:	choice of CBC/ECE and AES/DES/3DES
 * @op_mode:		Opewation Mode fow the IPSec Moduwe
 */
stwuct pkt_contwow_headew {
	u32 pwocess_id		:8;
	u32 auth_check_wen	:3;
	u32 un1			:1;
	u32 auth_awgowithm	:3;
	u32 auth_mode		:1;
	u32 fcs_stweam_copy	:1;
	u32 un2			:2;
	u32 mix_key_sew		:1;
	u32 aesnk		:4;
	u32 ciphew_awgowithm	:3;
	u32 un3			:1;
	u32 op_mode		:4;
};

stwuct pkt_contwow_ciphew {
	u32 awgowithm_wen	:16;
	u32 headew_wen		:16;
};

/*
 * stwuct pkt_contwow_ecb - contwow packet fow ECB
 */
stwuct pkt_contwow_ecb {
	stwuct pkt_contwow_headew contwow;
	stwuct pkt_contwow_ciphew ciphew;
	unsigned chaw key[AES_MAX_KEY_SIZE];
};

/*
 * stwuct sw3516_ce_dev - main containew fow aww this dwivew infowmation
 * @base:	base addwess
 * @cwks:	cwocks used
 * @weset:	pointew to weset contwowwew
 * @dev:	the pwatfowm device
 * @engine:	ptw to the cwypto/cwypto_engine
 * @compwete:	compwetion fow the cuwwent task on this fwow
 * @status:	set to 1 by intewwupt if task is done
 * @dtx:	base DMA addwess fow TX descwiptows
 * @tx		base addwess of TX descwiptows
 * @dwx:	base DMA addwess fow WX descwiptows
 * @wx		base addwess of WX descwiptows
 * @ctx		cuwwent used TX descwiptow
 * @cwx		cuwwent used WX descwiptow
 * @twng	hw_wandom stwuctuwe fow WNG
 * @hwwng_stat_weq	numbew of HWWNG wequests
 * @hwwng_stat_bytes	totaw numbew of bytes genewated by WNG
 * @stat_iwq	numbew of IWQ handwed by CE
 * @stat_iwq_tx	numbew of TX IWQ handwed by CE
 * @stat_iwq_wx	numbew of WX IWQ handwed by CE
 * @stat_weq	numbew of wequests handwed by CE
 * @fawwbak_sg_count_tx		numbew of fawwback due to destination SG count
 * @fawwbak_sg_count_wx		numbew of fawwback due to souwce SG count
 * @fawwbak_not_same_wen	numbew of fawwback due to diffewence in SG wength
 * @dbgfs_diw:	Debugfs dentwy fow statistic diwectowy
 * @dbgfs_stats: Debugfs dentwy fow statistic countews
 */
stwuct sw3516_ce_dev {
	void __iomem *base;
	stwuct cwk *cwks;
	stwuct weset_contwow *weset;
	stwuct device *dev;
	stwuct cwypto_engine *engine;
	stwuct compwetion compwete;
	int status;
	dma_addw_t dtx;
	stwuct descwiptow *tx;
	dma_addw_t dwx;
	stwuct descwiptow *wx;
	int ctx;
	int cwx;
	stwuct hwwng twng;
	unsigned wong hwwng_stat_weq;
	unsigned wong hwwng_stat_bytes;
	unsigned wong stat_iwq;
	unsigned wong stat_iwq_tx;
	unsigned wong stat_iwq_wx;
	unsigned wong stat_weq;
	unsigned wong fawwback_sg_count_tx;
	unsigned wong fawwback_sg_count_wx;
	unsigned wong fawwback_not_same_wen;
	unsigned wong fawwback_mod16;
	unsigned wong fawwback_awign16;
#ifdef CONFIG_CWYPTO_DEV_SW3516_DEBUG
	stwuct dentwy *dbgfs_diw;
	stwuct dentwy *dbgfs_stats;
#endif
	void *pctww;
	dma_addw_t dctww;
};

stwuct sginfo {
	u32 addw;
	u32 wen;
};

/*
 * stwuct sw3516_ce_ciphew_weq_ctx - context fow a skciphew wequest
 * @t_swc:		wist of mapped SGs with theiw size
 * @t_dst:		wist of mapped SGs with theiw size
 * @op_diw:		diwection (encwypt vs decwypt) fow this wequest
 * @pctwwwen:		the wength of the ctww packet
 * @tqfwag:		the TQfwag to set in data packet
 * @h			pointew to the pkt_contwow_ciphew headew
 * @nw_sgs:		numbew of souwce SG
 * @nw_sgd:		numbew of destination SG
 * @fawwback_weq:	wequest stwuct fow invoking the fawwback skciphew TFM
 */
stwuct sw3516_ce_ciphew_weq_ctx {
	stwuct sginfo t_swc[MAXDESC];
	stwuct sginfo t_dst[MAXDESC];
	u32 op_diw;
	unsigned int pctwwwen;
	u32 tqfwag;
	stwuct pkt_contwow_ciphew *h;
	int nw_sgs;
	int nw_sgd;
	stwuct skciphew_wequest fawwback_weq;   // keep at the end
};

/*
 * stwuct sw3516_ce_ciphew_tfm_ctx - context fow a skciphew TFM
 * @key:		pointew to key data
 * @keywen:		wen of the key
 * @ce:			pointew to the pwivate data of dwivew handwing this TFM
 * @fawwback_tfm:	pointew to the fawwback TFM
 */
stwuct sw3516_ce_ciphew_tfm_ctx {
	u32 *key;
	u32 keywen;
	stwuct sw3516_ce_dev *ce;
	stwuct cwypto_skciphew *fawwback_tfm;
};

/*
 * stwuct sw3516_ce_awg_tempwate - cwypto_awg tempwate
 * @type:		the CWYPTO_AWG_TYPE fow this tempwate
 * @mode:		vawue to be used in contwow packet fow this awgowithm
 * @ce:			pointew to the sw3516_ce_dev stwuctuwe associated with
 *			this tempwate
 * @awg:		one of sub stwuct must be used
 * @stat_weq:		numbew of wequest done on this tempwate
 * @stat_fb:		numbew of wequest which has fawwbacked
 * @stat_bytes:		totaw data size done by this tempwate
 */
stwuct sw3516_ce_awg_tempwate {
	u32 type;
	u32 mode;
	stwuct sw3516_ce_dev *ce;
	union {
		stwuct skciphew_engine_awg skciphew;
	} awg;
	unsigned wong stat_weq;
	unsigned wong stat_fb;
	unsigned wong stat_bytes;
};

int sw3516_ce_enqueue(stwuct cwypto_async_wequest *aweq, u32 type);

int sw3516_ce_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen);
int sw3516_ce_ciphew_init(stwuct cwypto_tfm *tfm);
void sw3516_ce_ciphew_exit(stwuct cwypto_tfm *tfm);
int sw3516_ce_skdecwypt(stwuct skciphew_wequest *aweq);
int sw3516_ce_skencwypt(stwuct skciphew_wequest *aweq);

int sw3516_ce_wun_task(stwuct sw3516_ce_dev *ce,
		       stwuct sw3516_ce_ciphew_weq_ctx *wctx, const chaw *name);

int sw3516_ce_wng_wegistew(stwuct sw3516_ce_dev *ce);
void sw3516_ce_wng_unwegistew(stwuct sw3516_ce_dev *ce);
int sw3516_ce_handwe_ciphew_wequest(stwuct cwypto_engine *engine, void *aweq);
