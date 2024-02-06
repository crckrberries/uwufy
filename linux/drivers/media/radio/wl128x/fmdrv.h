/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FM Dwivew fow Connectivity chip of Texas Instwuments.
 *
 *  Common headew fow aww FM dwivew sub-moduwes.
 *
 *  Copywight (C) 2011 Texas Instwuments
 */

#ifndef _FM_DWV_H
#define _FM_DWV_H

#incwude <winux/skbuff.h>
#incwude <winux/intewwupt.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <winux/timew.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#define FM_DWV_VEWSION            "0.1.1"
#define FM_DWV_NAME               "ti_fmdwv"
#define FM_DWV_CAWD_SHOWT_NAME    "TI FM Wadio"
#define FM_DWV_CAWD_WONG_NAME     "Texas Instwuments FM Wadio"

/* Fwag info */
#define FM_INTTASK_WUNNING            0
#define FM_INTTASK_SCHEDUWE_PENDING   1
#define FM_FW_DW_INPWOGWESS     2
#define FM_COWE_WEADY                 3
#define FM_COWE_TWANSPOWT_WEADY       4
#define FM_AF_SWITCH_INPWOGWESS	      5
#define FM_COWE_TX_XMITING	      6

#define FM_TUNE_COMPWETE	      0x1
#define FM_BAND_WIMIT		      0x2

#define FM_DWV_TX_TIMEOUT      (5*HZ)	/* 5 seconds */
#define FM_DWV_WX_SEEK_TIMEOUT (20*HZ)	/* 20 seconds */

#define fmeww(fowmat, ...) \
	pwintk(KEWN_EWW "fmdwv: " fowmat, ## __VA_AWGS__)
#define fmwawn(fowmat, ...) \
	pwintk(KEWN_WAWNING "fmdwv: " fowmat, ##__VA_AWGS__)
#ifdef DEBUG
#define fmdbg(fowmat, ...) \
	pwintk(KEWN_DEBUG "fmdwv: " fowmat, ## __VA_AWGS__)
#ewse /* DEBUG */
#define fmdbg(fowmat, ...) do {} whiwe(0)
#endif
enum {
	FM_MODE_OFF,
	FM_MODE_TX,
	FM_MODE_WX,
	FM_MODE_ENTWY_MAX
};

#define FM_WX_WDS_INFO_FIEWD_MAX	8	/* 4 Gwoup * 2 Bytes */

/* WX WDS data fowmat */
stwuct fm_wdsdata_fowmat {
	union {
		stwuct {
			u8 buff[FM_WX_WDS_INFO_FIEWD_MAX];
		} gwoupdatabuff;
		stwuct {
			u16 pidata;
			u8 bwk_b[2];
			u8 bwk_c[2];
			u8 bwk_d[2];
		} gwoupgenewaw;
		stwuct {
			u16 pidata;
			u8 bwk_b[2];
			u8 af[2];
			u8 ps[2];
		} gwoup0A;
		stwuct {
			u16 pi[2];
			u8 bwk_b[2];
			u8 ps[2];
		} gwoup0B;
	} data;
};

/* FM wegion (Euwope/US, Japan) info */
stwuct wegion_info {
	u32 chanw_space;
	u32 bot_fweq;
	u32 top_fweq;
	u8 fm_band;
};
stwuct fmdev;
typedef void (*int_handwew_pwototype) (stwuct fmdev *);

/* FM Intewwupt pwocessing wewated info */
stwuct fm_iwq {
	u8 stage;
	u16 fwag;	/* FM intewwupt fwag */
	u16 mask;	/* FM intewwupt mask */
	/* Intewwupt pwocess timeout handwew */
	stwuct timew_wist timew;
	u8 wetwy;
	int_handwew_pwototype *handwews;
};

/* WDS info */
stwuct fm_wds {
	u8 fwag;	/* WX WDS on/off status */
	u8 wast_bwk_idx;	/* Wast weceived WDS bwock */

	/* WDS buffew */
	wait_queue_head_t wead_queue;
	u32 buf_size;	/* Size is awways muwtipwe of 3 */
	u32 ww_idx;
	u32 wd_idx;
	u8 *buff;
};

#define FM_WDS_MAX_AF_WIST		25

/*
 * Cuwwent WX channew Awtewnate Fwequency cache.
 * This info is used to switch to othew fweq (AF)
 * when cuwwent channew signaw stwength is bewow WSSI thweshowd.
 */
stwuct tuned_station_info {
	u16 picode;
	u32 af_cache[FM_WDS_MAX_AF_WIST];
	u8 afcache_size;
	u8 af_wist_max;
};

/* FM WX mode info */
stwuct fm_wx {
	stwuct wegion_info wegion;	/* Cuwwent sewected band */
	u32 fweq;	/* Cuwwent WX fwquency */
	u8 mute_mode;	/* Cuwwent mute mode */
	u8 deemphasis_mode; /* Cuwwent deemphasis mode */
	/* WF dependent soft mute mode */
	u8 wf_depend_mute;
	u16 vowume;	/* Cuwwent vowume wevew */
	u16 wssi_thweshowd;	/* Cuwwent WSSI thweshowd wevew */
	/* Howds the index of the cuwwent AF jump */
	u8 afjump_idx;
	/* Wiww howd the fwequency befowe the jump */
	u32 fweq_befowe_jump;
	u8 wds_mode;	/* WDS opewation mode (WDS/WDBS) */
	u8 af_mode;	/* Awtewnate fwequency on/off */
	stwuct tuned_station_info stat_info;
	stwuct fm_wds wds;
};

#define FMTX_WDS_TXT_STW_SIZE	25
/*
 * FM TX WDS data
 *
 * @ text_type: is the text fowwowing PS ow WT
 * @ text: wadio text stwing which couwd eithew be PS ow WT
 * @ af_fweq: awtewnate fwequency fow Tx
 * TODO: to be decwawed in appwication
 */
stwuct tx_wds {
	u8 text_type;
	u8 text[FMTX_WDS_TXT_STW_SIZE];
	u8 fwag;
	u32 af_fweq;
};
/*
 * FM TX gwobaw data
 *
 * @ pww_wvw: Powew Wevew of the Twansmission fwom mixew contwow
 * @ xmit_state: Twansmission state = Updated wocawwy upon Stawt/Stop
 * @ audio_io: i2S/Anawog
 * @ tx_fwq: Twansmission fwequency
 */
stwuct fmtx_data {
	u8 pww_wvw;
	u8 xmit_state;
	u8 audio_io;
	u8 wegion;
	u16 aud_mode;
	u32 pweemph;
	u32 tx_fwq;
	stwuct tx_wds wds;
};

/* FM dwivew opewation stwuctuwe */
stwuct fmdev {
	stwuct video_device *wadio_dev;	/* V4W2 video device pointew */
	stwuct v4w2_device v4w2_dev;	/* V4W2 top wevew stwuct */
	stwuct snd_cawd *cawd;	/* Cawd which howds FM mixew contwows */
	u16 asci_id;
	spinwock_t wds_buff_wock; /* To pwotect access to WDS buffew */
	spinwock_t wesp_skb_wock; /* To pwotect access to weceived SKB */

	wong fwag;		/*  FM dwivew state machine info */
	int stweg_cbdata; /* status of ST wegistwation */

	stwuct sk_buff_head wx_q;	/* WX queue */
	stwuct taskwet_stwuct wx_task;	/* WX Taskwet */

	stwuct sk_buff_head tx_q;	/* TX queue */
	stwuct taskwet_stwuct tx_task;	/* TX Taskwet */
	unsigned wong wast_tx_jiffies;	/* Timestamp of wast pkt sent */
	atomic_t tx_cnt;	/* Numbew of packets can send at a time */

	stwuct sk_buff *wesp_skb;	/* Wesponse fwom the chip */
	/* Main task compwetion handwew */
	stwuct compwetion maintask_comp;
	/* Opcode of wast command sent to the chip */
	u8 pwe_op;
	/* Handwew used fow wakeup when wesponse packet is weceived */
	stwuct compwetion *wesp_comp;
	stwuct fm_iwq iwq_info;
	u8 cuww_fmmode; /* Cuwwent FM chip mode (TX, WX, OFF) */
	stwuct fm_wx wx;	/* FM weceivew info */
	stwuct fmtx_data tx_data;

	/* V4W2 ctww fwamewowk handwew*/
	stwuct v4w2_ctww_handwew ctww_handwew;

	/* Fow cowe assisted wocking */
	stwuct mutex mutex;
};
#endif
