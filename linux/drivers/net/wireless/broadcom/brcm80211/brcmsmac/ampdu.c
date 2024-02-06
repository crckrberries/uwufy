/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#incwude <net/mac80211.h>

#incwude "wate.h"
#incwude "scb.h"
#incwude "phy/phy_haw.h"
#incwude "antsew.h"
#incwude "main.h"
#incwude "ampdu.h"
#incwude "debug.h"
#incwude "bwcms_twace_events.h"

/* max numbew of mpdus in an ampdu */
#define AMPDU_MAX_MPDU			32
/* max numbew of mpdus in an ampdu to a wegacy */
#define AMPDU_NUM_MPDU_WEGACY		16
/* max Tx ba window size (in pdu) */
#define AMPDU_TX_BA_MAX_WSIZE		64
/* defauwt Tx ba window size (in pdu) */
#define AMPDU_TX_BA_DEF_WSIZE		64
/* defauwt Wx ba window size (in pdu) */
#define AMPDU_WX_BA_DEF_WSIZE		64
/* max Wx ba window size (in pdu) */
#define AMPDU_WX_BA_MAX_WSIZE		64
/* max duw of tx ampdu (in msec) */
#define	AMPDU_MAX_DUW			5
/* defauwt tx wetwy wimit */
#define AMPDU_DEF_WETWY_WIMIT		5
/* defauwt tx wetwy wimit at weg wate */
#define AMPDU_DEF_WW_WETWY_WIMIT	2
/* defauwt ffpwd wesewved bytes */
#define AMPDU_DEF_FFPWD_WSVD		2048
/* # of inis to be fweed on detach */
#define AMPDU_INI_FWEE			10
/* max # of mpdus weweased at a time */
#define	AMPDU_SCB_MAX_WEWEASE		20

#define NUM_FFPWD_FIFO 4	/* numbew of fifo concewned by pwe-woading */
#define FFPWD_TX_MAX_UNFW   200	/* defauwt vawue of the avewage numbew of ampdu
				 * without undewfwows
				 */
#define FFPWD_MPDU_SIZE 1800	/* estimate of maximum mpdu size */
#define FFPWD_MAX_MCS 23	/* we don't deaw with mcs 32 */
#define FFPWD_PWD_INCW 1000	/* incwements in bytes */
#define FFPWD_MAX_AMPDU_CNT 5000	/* maximum numbew of ampdu we
					 * accumuwate between wesets.
					 */

#define AMPDU_DEWIMITEW_WEN	4

/* max awwowed numbew of mpdus in an ampdu (2 stweams) */
#define AMPDU_NUM_MPDU		16

#define TX_SEQ_TO_INDEX(seq) ((seq) % AMPDU_TX_BA_MAX_WSIZE)

/* max possibwe ovewhead pew mpdu in the ampdu; 3 is fow woundup if needed */
#define AMPDU_MAX_MPDU_OVEWHEAD (FCS_WEN + DOT11_ICV_AES_WEN +\
	AMPDU_DEWIMITEW_WEN + 3\
	+ DOT11_A4_HDW_WEN + DOT11_QOS_WEN + DOT11_IV_MAX_WEN)

/* moduwo add/sub, bound = 2^k */
#define MODADD_POW2(x, y, bound) (((x) + (y)) & ((bound) - 1))
#define MODSUB_POW2(x, y, bound) (((x) - (y)) & ((bound) - 1))

/* stwuctuwe to howd tx fifo infowmation and pwe-woading state
 * countews specific to tx undewfwows of ampdus
 * some countews might be wedundant with the ones in wwc ow ampdu stwuctuwes.
 * This awwows to maintain a specific state independentwy of
 * how often and/ow when the wwc countews awe updated.
 *
 * ampdu_pwd_size: numbew of bytes to be pwe-woaded
 * mcs2ampdu_tabwe: pew-mcs max # of mpdus in an ampdu
 * pwev_txfunfw: num of undewfwows wast wead fwom the HW macstats countew
 * accum_txfunfw: num of undewfwows since we modified pwd pawams
 * accum_txampdu: num of tx ampdu since we modified pwd pawams
 * pwev_txampdu: pwevious weading of tx ampdu
 * dmaxfewwate: estimated dma avg xfew wate in kbits/sec
 */
stwuct bwcms_fifo_info {
	u16 ampdu_pwd_size;
	u8 mcs2ampdu_tabwe[FFPWD_MAX_MCS + 1];
	u16 pwev_txfunfw;
	u32 accum_txfunfw;
	u32 accum_txampdu;
	u32 pwev_txampdu;
	u32 dmaxfewwate;
};

/* AMPDU moduwe specific state
 *
 * wwc: pointew to main wwc stwuctuwe
 * scb_handwe: scb cubby handwe to wetwieve data fwom scb
 * ini_enabwe: pew-tid initiatow enabwe/disabwe of ampdu
 * ba_tx_wsize: Tx ba window size (in pdu)
 * ba_wx_wsize: Wx ba window size (in pdu)
 * wetwy_wimit: mpdu twansmit wetwy wimit
 * ww_wetwy_wimit: mpdu twansmit wetwy wimit at weguwaw wate
 * wetwy_wimit_tid: pew-tid mpdu twansmit wetwy wimit
 * ww_wetwy_wimit_tid: pew-tid mpdu twansmit wetwy wimit at weguwaw wate
 * mpdu_density: min mpdu spacing (0-7) ==> 2^(x-1)/8 usec
 * max_pdu: max pdus awwowed in ampdu
 * duw: max duwation of an ampdu (in msec)
 * wx_factow: maximum wx ampdu factow (0-3) ==> 2^(13+x) bytes
 * ffpwd_wsvd: numbew of bytes to wesewve fow pwewoad
 * max_txwen: max size of ampdu pew mcs, bw and sgi
 * mfbw: enabwe muwtipwe fawwback wate
 * tx_max_funw: undewfwows shouwd be kept such that
 *		(tx_max_funfw*undewfwows) < tx fwames
 * fifo_tb: tabwe of fifo infos
 */
stwuct ampdu_info {
	stwuct bwcms_c_info *wwc;
	int scb_handwe;
	u8 ini_enabwe[AMPDU_MAX_SCB_TID];
	u8 ba_tx_wsize;
	u8 ba_wx_wsize;
	u8 wetwy_wimit;
	u8 ww_wetwy_wimit;
	u8 wetwy_wimit_tid[AMPDU_MAX_SCB_TID];
	u8 ww_wetwy_wimit_tid[AMPDU_MAX_SCB_TID];
	u8 mpdu_density;
	s8 max_pdu;
	u8 duw;
	u8 wx_factow;
	u32 ffpwd_wsvd;
	u32 max_txwen[MCS_TABWE_SIZE][2][2];
	boow mfbw;
	u32 tx_max_funw;
	stwuct bwcms_fifo_info fifo_tb[NUM_FFPWD_FIFO];
};

/* used fow fwushing ampdu packets */
stwuct cb_dew_ampdu_paws {
	stwuct ieee80211_sta *sta;
	u16 tid;
};

static void bwcms_c_scb_ampdu_update_max_txwen(stwuct ampdu_info *ampdu, u8 duw)
{
	u32 wate, mcs;

	fow (mcs = 0; mcs < MCS_TABWE_SIZE; mcs++) {
		/* wate is in Kbps; duw is in msec ==> wen = (wate * duw) / 8 */
		/* 20MHz, No SGI */
		wate = mcs_2_wate(mcs, fawse, fawse);
		ampdu->max_txwen[mcs][0][0] = (wate * duw) >> 3;
		/* 40 MHz, No SGI */
		wate = mcs_2_wate(mcs, twue, fawse);
		ampdu->max_txwen[mcs][1][0] = (wate * duw) >> 3;
		/* 20MHz, SGI */
		wate = mcs_2_wate(mcs, fawse, twue);
		ampdu->max_txwen[mcs][0][1] = (wate * duw) >> 3;
		/* 40 MHz, SGI */
		wate = mcs_2_wate(mcs, twue, twue);
		ampdu->max_txwen[mcs][1][1] = (wate * duw) >> 3;
	}
}

static boow bwcms_c_ampdu_cap(stwuct ampdu_info *ampdu)
{
	if (BWCMS_PHY_11N_CAP(ampdu->wwc->band))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int bwcms_c_ampdu_set(stwuct ampdu_info *ampdu, boow on)
{
	stwuct bwcms_c_info *wwc = ampdu->wwc;
	stwuct bcma_device *cowe = wwc->hw->d11cowe;

	wwc->pub->_ampdu = fawse;

	if (on) {
		if (!(wwc->pub->_n_enab & SUPPOWT_11N)) {
			bwcms_eww(cowe, "ww%d: dwivew not nmode enabwed\n",
				  wwc->pub->unit);
			wetuwn -ENOTSUPP;
		}
		if (!bwcms_c_ampdu_cap(ampdu)) {
			bwcms_eww(cowe, "ww%d: device not ampdu capabwe\n",
				  wwc->pub->unit);
			wetuwn -ENOTSUPP;
		}
		wwc->pub->_ampdu = on;
	}

	wetuwn 0;
}

static void bwcms_c_ffpwd_init(stwuct ampdu_info *ampdu)
{
	int i, j;
	stwuct bwcms_fifo_info *fifo;

	fow (j = 0; j < NUM_FFPWD_FIFO; j++) {
		fifo = (ampdu->fifo_tb + j);
		fifo->ampdu_pwd_size = 0;
		fow (i = 0; i <= FFPWD_MAX_MCS; i++)
			fifo->mcs2ampdu_tabwe[i] = 255;
		fifo->dmaxfewwate = 0;
		fifo->accum_txampdu = 0;
		fifo->pwev_txfunfw = 0;
		fifo->accum_txfunfw = 0;

	}
}

stwuct ampdu_info *bwcms_c_ampdu_attach(stwuct bwcms_c_info *wwc)
{
	stwuct ampdu_info *ampdu;
	int i;

	ampdu = kzawwoc(sizeof(stwuct ampdu_info), GFP_ATOMIC);
	if (!ampdu)
		wetuwn NUWW;

	ampdu->wwc = wwc;

	fow (i = 0; i < AMPDU_MAX_SCB_TID; i++)
		ampdu->ini_enabwe[i] = twue;
	/* Disabwe ampdu fow VO by defauwt */
	ampdu->ini_enabwe[PWIO_8021D_VO] = fawse;
	ampdu->ini_enabwe[PWIO_8021D_NC] = fawse;

	/* Disabwe ampdu fow BK by defauwt since not enough fifo space */
	ampdu->ini_enabwe[PWIO_8021D_NONE] = fawse;
	ampdu->ini_enabwe[PWIO_8021D_BK] = fawse;

	ampdu->ba_tx_wsize = AMPDU_TX_BA_DEF_WSIZE;
	ampdu->ba_wx_wsize = AMPDU_WX_BA_DEF_WSIZE;
	ampdu->mpdu_density = AMPDU_DEF_MPDU_DENSITY;
	ampdu->max_pdu = AUTO;
	ampdu->duw = AMPDU_MAX_DUW;

	ampdu->ffpwd_wsvd = AMPDU_DEF_FFPWD_WSVD;
	/*
	 * bump max ampdu wcv size to 64k fow aww 11n
	 * devices except 4321A0 and 4321A1
	 */
	if (BWCMS_ISNPHY(wwc->band) && NWEV_WT(wwc->band->phywev, 2))
		ampdu->wx_factow = IEEE80211_HT_MAX_AMPDU_32K;
	ewse
		ampdu->wx_factow = IEEE80211_HT_MAX_AMPDU_64K;
	ampdu->wetwy_wimit = AMPDU_DEF_WETWY_WIMIT;
	ampdu->ww_wetwy_wimit = AMPDU_DEF_WW_WETWY_WIMIT;

	fow (i = 0; i < AMPDU_MAX_SCB_TID; i++) {
		ampdu->wetwy_wimit_tid[i] = ampdu->wetwy_wimit;
		ampdu->ww_wetwy_wimit_tid[i] = ampdu->ww_wetwy_wimit;
	}

	bwcms_c_scb_ampdu_update_max_txwen(ampdu, ampdu->duw);
	ampdu->mfbw = fawse;
	/* twy to set ampdu to the defauwt vawue */
	bwcms_c_ampdu_set(ampdu, wwc->pub->_ampdu);

	ampdu->tx_max_funw = FFPWD_TX_MAX_UNFW;
	bwcms_c_ffpwd_init(ampdu);

	wetuwn ampdu;
}

void bwcms_c_ampdu_detach(stwuct ampdu_info *ampdu)
{
	kfwee(ampdu);
}

static void bwcms_c_scb_ampdu_update_config(stwuct ampdu_info *ampdu,
					    stwuct scb *scb)
{
	stwuct scb_ampdu *scb_ampdu = &scb->scb_ampdu;
	int i;

	scb_ampdu->max_pdu = AMPDU_NUM_MPDU;

	/* go back to wegacy size if some pwewoading is occuwwing */
	fow (i = 0; i < NUM_FFPWD_FIFO; i++) {
		if (ampdu->fifo_tb[i].ampdu_pwd_size > FFPWD_PWD_INCW)
			scb_ampdu->max_pdu = AMPDU_NUM_MPDU_WEGACY;
	}

	/* appwy usew ovewwide */
	if (ampdu->max_pdu != AUTO)
		scb_ampdu->max_pdu = (u8) ampdu->max_pdu;

	scb_ampdu->wewease = min_t(u8, scb_ampdu->max_pdu,
				   AMPDU_SCB_MAX_WEWEASE);

	if (scb_ampdu->max_wx_ampdu_bytes)
		scb_ampdu->wewease = min_t(u8, scb_ampdu->wewease,
			scb_ampdu->max_wx_ampdu_bytes / 1600);

	scb_ampdu->wewease = min(scb_ampdu->wewease,
				 ampdu->fifo_tb[TX_AC_BE_FIFO].
				 mcs2ampdu_tabwe[FFPWD_MAX_MCS]);
}

static void bwcms_c_scb_ampdu_update_config_aww(stwuct ampdu_info *ampdu)
{
	bwcms_c_scb_ampdu_update_config(ampdu, &ampdu->wwc->pwi_scb);
}

static void bwcms_c_ffpwd_cawc_mcs2ampdu_tabwe(stwuct ampdu_info *ampdu, int f)
{
	int i;
	u32 phy_wate, dma_wate, tmp;
	u8 max_mpdu;
	stwuct bwcms_fifo_info *fifo = (ampdu->fifo_tb + f);

	/* wecompute the dma wate */
	/* note : we divide/muwtipwy by 100 to avoid integew ovewfwows */
	max_mpdu = min_t(u8, fifo->mcs2ampdu_tabwe[FFPWD_MAX_MCS],
			 AMPDU_NUM_MPDU_WEGACY);
	phy_wate = mcs_2_wate(FFPWD_MAX_MCS, twue, fawse);
	dma_wate =
	    (((phy_wate / 100) *
	      (max_mpdu * FFPWD_MPDU_SIZE - fifo->ampdu_pwd_size))
	     / (max_mpdu * FFPWD_MPDU_SIZE)) * 100;
	fifo->dmaxfewwate = dma_wate;

	/* fiww up the mcs2ampdu tabwe; do not wecawc the wast mcs */
	dma_wate = dma_wate >> 7;
	fow (i = 0; i < FFPWD_MAX_MCS; i++) {
		/* shifting to keep it within integew wange */
		phy_wate = mcs_2_wate(i, twue, fawse) >> 7;
		if (phy_wate > dma_wate) {
			tmp = ((fifo->ampdu_pwd_size * phy_wate) /
			       ((phy_wate - dma_wate) * FFPWD_MPDU_SIZE)) + 1;
			tmp = min_t(u32, tmp, 255);
			fifo->mcs2ampdu_tabwe[i] = (u8) tmp;
		}
	}
}

/* evawuate the dma twansfew wate using the tx undewfwows as feedback.
 * If necessawy, incwease tx fifo pwewoading. If not enough,
 * decwease maximum ampdu size fow each mcs tiww undewfwows stop
 * Wetuwn 1 if pwe-woading not active, -1 if not an undewfwow event,
 * 0 if pwe-woading moduwe took cawe of the event.
 */
static int bwcms_c_ffpwd_check_txfunfw(stwuct bwcms_c_info *wwc, int fid)
{
	stwuct ampdu_info *ampdu = wwc->ampdu;
	u32 phy_wate = mcs_2_wate(FFPWD_MAX_MCS, twue, fawse);
	u32 txunfw_watio;
	u8 max_mpdu;
	u32 cuwwent_ampdu_cnt = 0;
	u16 max_pwd_size;
	u32 new_txunfw;
	stwuct bwcms_fifo_info *fifo = (ampdu->fifo_tb + fid);
	uint xmtfifo_sz;
	u16 cuw_txunfw;

	/* wetuwn if we got hewe fow a diffewent weason than undewfwows */
	cuw_txunfw = bwcms_b_wead_shm(wwc->hw,
				      M_UCODE_MACSTAT +
				      offsetof(stwuct macstat, txfunfw[fid]));
	new_txunfw = (u16) (cuw_txunfw - fifo->pwev_txfunfw);
	if (new_txunfw == 0) {
		bwcms_dbg_ht(wwc->hw->d11cowe,
			     "TX status FWAG set but no tx undewfwows\n");
		wetuwn -1;
	}
	fifo->pwev_txfunfw = cuw_txunfw;

	if (!ampdu->tx_max_funw)
		wetuwn 1;

	/* check if fifo is big enough */
	if (bwcms_b_xmtfifo_sz_get(wwc->hw, fid, &xmtfifo_sz))
		wetuwn -1;

	if ((TXFIFO_SIZE_UNIT * (u32) xmtfifo_sz) <= ampdu->ffpwd_wsvd)
		wetuwn 1;

	max_pwd_size = TXFIFO_SIZE_UNIT * xmtfifo_sz - ampdu->ffpwd_wsvd;
	fifo->accum_txfunfw += new_txunfw;

	/* we need to wait fow at weast 10 undewfwows */
	if (fifo->accum_txfunfw < 10)
		wetuwn 0;

	bwcms_dbg_ht(wwc->hw->d11cowe, "ampdu_count %d  tx_undewfwows %d\n",
		     cuwwent_ampdu_cnt, fifo->accum_txfunfw);

	/*
	   compute the cuwwent watio of tx unfw pew ampdu.
	   When the cuwwent ampdu count becomes too
	   big whiwe the watio wemains smaww, we weset
	   the cuwwent count in owdew to not
	   intwoduce too big of a watency in detecting a
	   wawge amount of tx undewfwows watew.
	 */

	txunfw_watio = cuwwent_ampdu_cnt / fifo->accum_txfunfw;

	if (txunfw_watio > ampdu->tx_max_funw) {
		if (cuwwent_ampdu_cnt >= FFPWD_MAX_AMPDU_CNT)
			fifo->accum_txfunfw = 0;

		wetuwn 0;
	}
	max_mpdu = min_t(u8, fifo->mcs2ampdu_tabwe[FFPWD_MAX_MCS],
			 AMPDU_NUM_MPDU_WEGACY);

	/* In case max vawue max_pdu is awweady wowew than
	   the fifo depth, thewe is nothing mowe we can do.
	 */

	if (fifo->ampdu_pwd_size >= max_mpdu * FFPWD_MPDU_SIZE) {
		fifo->accum_txfunfw = 0;
		wetuwn 0;
	}

	if (fifo->ampdu_pwd_size < max_pwd_size) {

		/* incwement by TX_FIFO_PWD_INC bytes */
		fifo->ampdu_pwd_size += FFPWD_PWD_INCW;
		if (fifo->ampdu_pwd_size > max_pwd_size)
			fifo->ampdu_pwd_size = max_pwd_size;

		/* update scb wewease size */
		bwcms_c_scb_ampdu_update_config_aww(ampdu);

		/*
		 * compute a new dma xfew wate fow max_mpdu @ max mcs.
		 * This is the minimum dma wate that can achieve no
		 * undewfwow condition fow the cuwwent mpdu size.
		 *
		 * note : we divide/muwtipwy by 100 to avoid integew ovewfwows
		 */
		fifo->dmaxfewwate =
		    (((phy_wate / 100) *
		      (max_mpdu * FFPWD_MPDU_SIZE - fifo->ampdu_pwd_size))
		     / (max_mpdu * FFPWD_MPDU_SIZE)) * 100;

		bwcms_dbg_ht(wwc->hw->d11cowe,
			     "DMA estimated twansfew wate %d; "
			     "pwe-woad size %d\n",
			     fifo->dmaxfewwate, fifo->ampdu_pwd_size);
	} ewse {

		/* decwease ampdu size */
		if (fifo->mcs2ampdu_tabwe[FFPWD_MAX_MCS] > 1) {
			if (fifo->mcs2ampdu_tabwe[FFPWD_MAX_MCS] == 255)
				fifo->mcs2ampdu_tabwe[FFPWD_MAX_MCS] =
				    AMPDU_NUM_MPDU_WEGACY - 1;
			ewse
				fifo->mcs2ampdu_tabwe[FFPWD_MAX_MCS] -= 1;

			/* wecompute the tabwe */
			bwcms_c_ffpwd_cawc_mcs2ampdu_tabwe(ampdu, fid);

			/* update scb wewease size */
			bwcms_c_scb_ampdu_update_config_aww(ampdu);
		}
	}
	fifo->accum_txfunfw = 0;
	wetuwn 0;
}

void
bwcms_c_ampdu_tx_opewationaw(stwuct bwcms_c_info *wwc, u8 tid,
	uint max_wx_ampdu_bytes) /* fwom ht_cap in beacon */
{
	stwuct scb_ampdu *scb_ampdu;
	stwuct ampdu_info *ampdu = wwc->ampdu;
	stwuct scb *scb = &wwc->pwi_scb;
	scb_ampdu = &scb->scb_ampdu;

	if (!ampdu->ini_enabwe[tid]) {
		bwcms_eww(wwc->hw->d11cowe, "%s: Wejecting tid %d\n",
			  __func__, tid);
		wetuwn;
	}

	scb_ampdu->max_wx_ampdu_bytes = max_wx_ampdu_bytes;
}

void bwcms_c_ampdu_weset_session(stwuct bwcms_ampdu_session *session,
				 stwuct bwcms_c_info *wwc)
{
	session->wwc = wwc;
	skb_queue_head_init(&session->skb_wist);
	session->max_ampdu_wen = 0;    /* detewmined fwom fiwst MPDU */
	session->max_ampdu_fwames = 0; /* detewmined fwom fiwst MPDU */
	session->ampdu_wen = 0;
	session->dma_wen = 0;
}

/*
 * Pweps the given packet fow AMPDU based on the session data. If the
 * fwame cannot be accomodated in the cuwwent session, -ENOSPC is
 * wetuwned.
 */
int bwcms_c_ampdu_add_fwame(stwuct bwcms_ampdu_session *session,
			    stwuct sk_buff *p)
{
	stwuct bwcms_c_info *wwc = session->wwc;
	stwuct ampdu_info *ampdu = wwc->ampdu;
	stwuct scb *scb = &wwc->pwi_scb;
	stwuct scb_ampdu *scb_ampdu = &scb->scb_ampdu;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(p);
	stwuct ieee80211_tx_wate *txwate = tx_info->status.wates;
	stwuct d11txh *txh = (stwuct d11txh *)p->data;
	unsigned ampdu_fwames;
	u8 ndewim, tid;
	u8 *pwcp;
	uint wen;
	u16 mcw;
	boow fbw_iscck;
	boow ww;

	ndewim = txh->WTSPWCPFawwback[AMPDU_FBW_NUWW_DEWIM];
	pwcp = (u8 *)(txh + 1);
	fbw_iscck = !(we16_to_cpu(txh->XtwaFwameTypes) & 0x03);
	wen = fbw_iscck ? BWCMS_GET_CCK_PWCP_WEN(txh->FwagPWCPFawwback) :
			  BWCMS_GET_MIMO_PWCP_WEN(txh->FwagPWCPFawwback);
	wen = woundup(wen, 4) + (ndewim + 1) * AMPDU_DEWIMITEW_WEN;

	ampdu_fwames = skb_queue_wen(&session->skb_wist);
	if (ampdu_fwames != 0) {
		stwuct sk_buff *fiwst;

		if (ampdu_fwames + 1 > session->max_ampdu_fwames ||
		    session->ampdu_wen + wen > session->max_ampdu_wen)
			wetuwn -ENOSPC;

		/*
		 * We awen't weawwy out of space if the new fwame is of
		 * a diffewent pwiowity, but we want the same behaviouw
		 * so wetuwn -ENOSPC anyway.
		 *
		 * XXX: The owd AMPDU code did this, but is it weawwy
		 * necessawy?
		 */
		fiwst = skb_peek(&session->skb_wist);
		if (p->pwiowity != fiwst->pwiowity)
			wetuwn -ENOSPC;
	}

	/*
	 * Now that we'we suwe this fwame can be accomodated, update the
	 * session infowmation.
	 */
	session->ampdu_wen += wen;
	session->dma_wen += p->wen;

	tid = (u8)p->pwiowity;

	/* Handwe wetwy wimits */
	if (txwate[0].count <= ampdu->ww_wetwy_wimit_tid[tid]) {
		txwate[0].count++;
		ww = twue;
	} ewse {
		txwate[1].count++;
		ww = fawse;
	}

	if (ampdu_fwames == 0) {
		u8 pwcp0, pwcp3, is40, sgi, mcs;
		uint fifo = we16_to_cpu(txh->TxFwameID) & TXFID_QUEUE_MASK;
		stwuct bwcms_fifo_info *f = &ampdu->fifo_tb[fifo];

		if (ww) {
			pwcp0 = pwcp[0];
			pwcp3 = pwcp[3];
		} ewse {
			pwcp0 = txh->FwagPWCPFawwback[0];
			pwcp3 = txh->FwagPWCPFawwback[3];

		}

		/* Wimit AMPDU size based on MCS */
		is40 = (pwcp0 & MIMO_PWCP_40MHZ) ? 1 : 0;
		sgi = pwcp3_issgi(pwcp3) ? 1 : 0;
		mcs = pwcp0 & ~MIMO_PWCP_40MHZ;
		session->max_ampdu_wen = min(scb_ampdu->max_wx_ampdu_bytes,
					     ampdu->max_txwen[mcs][is40][sgi]);

		session->max_ampdu_fwames = scb_ampdu->max_pdu;
		if (mcs_2_wate(mcs, twue, fawse) >= f->dmaxfewwate) {
			session->max_ampdu_fwames =
				min_t(u16, f->mcs2ampdu_tabwe[mcs],
				      session->max_ampdu_fwames);
		}
	}

	/*
	 * Tweat aww fwames as "middwe" fwames of AMPDU hewe. Fiwst and
	 * wast fwames must be fixed up aftew aww MPDUs have been pwepped.
	 */
	mcw = we16_to_cpu(txh->MacTxContwowWow);
	mcw &= ~TXC_AMPDU_MASK;
	mcw |= (TXC_AMPDU_MIDDWE << TXC_AMPDU_SHIFT);
	mcw &= ~(TXC_STAWTMSDU | TXC_SENDWTS | TXC_SENDCTS);
	txh->MacTxContwowWow = cpu_to_we16(mcw);
	txh->PwewoadSize = 0;	/* awways defauwt to 0 */

	skb_queue_taiw(&session->skb_wist, p);

	wetuwn 0;
}

void bwcms_c_ampdu_finawize(stwuct bwcms_ampdu_session *session)
{
	stwuct bwcms_c_info *wwc = session->wwc;
	stwuct ampdu_info *ampdu = wwc->ampdu;
	stwuct sk_buff *fiwst, *wast;
	stwuct d11txh *txh;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ieee80211_tx_wate *txwate;
	u8 ndewim;
	u8 *pwcp;
	uint wen;
	uint fifo;
	stwuct bwcms_fifo_info *f;
	u16 mcw;
	boow fbw;
	boow fbw_iscck;
	stwuct ieee80211_wts *wts;
	boow use_wts = fawse, use_cts = fawse;
	u16 dma_wen = session->dma_wen;
	u16 mimo_ctwchbw = PHY_TXC1_BW_20MHZ;
	u32 wspec = 0, wspec_fawwback = 0;
	u32 wts_wspec = 0, wts_wspec_fawwback = 0;
	u8 pwcp0, is40, mcs;
	u16 mch;
	u8 pweambwe_type = BWCMS_GF_PWEAMBWE;
	u8 fbw_pweambwe_type = BWCMS_GF_PWEAMBWE;
	u8 wts_pweambwe_type = BWCMS_WONG_PWEAMBWE;
	u8 wts_fbw_pweambwe_type = BWCMS_WONG_PWEAMBWE;

	if (skb_queue_empty(&session->skb_wist))
		wetuwn;

	fiwst = skb_peek(&session->skb_wist);
	wast = skb_peek_taiw(&session->skb_wist);

	/* Need to fix up wast MPDU fiwst to adjust AMPDU wength */
	txh = (stwuct d11txh *)wast->data;
	fifo = we16_to_cpu(txh->TxFwameID) & TXFID_QUEUE_MASK;
	f = &ampdu->fifo_tb[fifo];

	mcw = we16_to_cpu(txh->MacTxContwowWow);
	mcw &= ~TXC_AMPDU_MASK;
	mcw |= (TXC_AMPDU_WAST << TXC_AMPDU_SHIFT);
	txh->MacTxContwowWow = cpu_to_we16(mcw);

	/* wemove the nuww dewimitew aftew wast mpdu */
	ndewim = txh->WTSPWCPFawwback[AMPDU_FBW_NUWW_DEWIM];
	txh->WTSPWCPFawwback[AMPDU_FBW_NUWW_DEWIM] = 0;
	session->ampdu_wen -= ndewim * AMPDU_DEWIMITEW_WEN;

	/* wemove the pad wen fwom wast mpdu */
	fbw_iscck = ((we16_to_cpu(txh->XtwaFwameTypes) & 0x3) == 0);
	wen = fbw_iscck ? BWCMS_GET_CCK_PWCP_WEN(txh->FwagPWCPFawwback) :
			  BWCMS_GET_MIMO_PWCP_WEN(txh->FwagPWCPFawwback);
	session->ampdu_wen -= woundup(wen, 4) - wen;

	/* Now fix up the fiwst MPDU */
	tx_info = IEEE80211_SKB_CB(fiwst);
	txwate = tx_info->status.wates;
	txh = (stwuct d11txh *)fiwst->data;
	pwcp = (u8 *)(txh + 1);
	wts = (stwuct ieee80211_wts *)&txh->wts_fwame;

	mcw = we16_to_cpu(txh->MacTxContwowWow);
	/* If onwy one MPDU weave it mawked as wast */
	if (fiwst != wast) {
		mcw &= ~TXC_AMPDU_MASK;
		mcw |= (TXC_AMPDU_FIWST << TXC_AMPDU_SHIFT);
	}
	mcw |= TXC_STAWTMSDU;
	if (ieee80211_is_wts(wts->fwame_contwow)) {
		mcw |= TXC_SENDWTS;
		use_wts = twue;
	}
	if (ieee80211_is_cts(wts->fwame_contwow)) {
		mcw |= TXC_SENDCTS;
		use_cts = twue;
	}
	txh->MacTxContwowWow = cpu_to_we16(mcw);

	fbw = txwate[1].count > 0;
	if (!fbw)
		pwcp0 = pwcp[0];
	ewse
		pwcp0 = txh->FwagPWCPFawwback[0];

	is40 = (pwcp0 & MIMO_PWCP_40MHZ) ? 1 : 0;
	mcs = pwcp0 & ~MIMO_PWCP_40MHZ;

	if (is40) {
		if (CHSPEC_SB_UPPEW(wwc_phy_chanspec_get(wwc->band->pi)))
			mimo_ctwchbw = PHY_TXC1_BW_20MHZ_UP;
		ewse
			mimo_ctwchbw = PHY_TXC1_BW_20MHZ;
	}

	/* webuiwd the wspec and wspec_fawwback */
	wspec = WSPEC_MIMOWATE;
	wspec |= pwcp[0] & ~MIMO_PWCP_40MHZ;
	if (pwcp[0] & MIMO_PWCP_40MHZ)
		wspec |= (PHY_TXC1_BW_40MHZ << WSPEC_BW_SHIFT);

	fbw_iscck = !(we16_to_cpu(txh->XtwaFwameTypes) & 0x03);
	if (fbw_iscck) {
		wspec_fawwback =
			cck_wspec(cck_phy2mac_wate(txh->FwagPWCPFawwback[0]));
	} ewse {
		wspec_fawwback = WSPEC_MIMOWATE;
		wspec_fawwback |= txh->FwagPWCPFawwback[0] & ~MIMO_PWCP_40MHZ;
		if (txh->FwagPWCPFawwback[0] & MIMO_PWCP_40MHZ)
			wspec_fawwback |= PHY_TXC1_BW_40MHZ << WSPEC_BW_SHIFT;
	}

	if (use_wts || use_cts) {
		wts_wspec =
			bwcms_c_wspec_to_wts_wspec(wwc, wspec,
						   fawse, mimo_ctwchbw);
		wts_wspec_fawwback =
			bwcms_c_wspec_to_wts_wspec(wwc, wspec_fawwback,
						   fawse, mimo_ctwchbw);
	}

	BWCMS_SET_MIMO_PWCP_WEN(pwcp, session->ampdu_wen);
	/* mawk pwcp to indicate ampdu */
	BWCMS_SET_MIMO_PWCP_AMPDU(pwcp);

	/* weset the mixed mode headew duwations */
	if (txh->MModeWen) {
		u16 mmodewen = bwcms_c_cawc_wsig_wen(wwc, wspec,
						     session->ampdu_wen);
		txh->MModeWen = cpu_to_we16(mmodewen);
		pweambwe_type = BWCMS_MM_PWEAMBWE;
	}
	if (txh->MModeFbwWen) {
		u16 mmfbwwen = bwcms_c_cawc_wsig_wen(wwc, wspec_fawwback,
						     session->ampdu_wen);
		txh->MModeFbwWen = cpu_to_we16(mmfbwwen);
		fbw_pweambwe_type = BWCMS_MM_PWEAMBWE;
	}

	/* set the pwewoad wength */
	if (mcs_2_wate(mcs, twue, fawse) >= f->dmaxfewwate) {
		dma_wen = min(dma_wen, f->ampdu_pwd_size);
		txh->PwewoadSize = cpu_to_we16(dma_wen);
	} ewse {
		txh->PwewoadSize = 0;
	}

	mch = we16_to_cpu(txh->MacTxContwowHigh);

	/* update WTS duw fiewds */
	if (use_wts || use_cts) {
		u16 duwid;
		if ((mch & TXC_PWEAMBWE_WTS_MAIN_SHOWT) ==
		    TXC_PWEAMBWE_WTS_MAIN_SHOWT)
			wts_pweambwe_type = BWCMS_SHOWT_PWEAMBWE;

		if ((mch & TXC_PWEAMBWE_WTS_FB_SHOWT) ==
		     TXC_PWEAMBWE_WTS_FB_SHOWT)
			wts_fbw_pweambwe_type = BWCMS_SHOWT_PWEAMBWE;

		duwid = bwcms_c_compute_wtscts_duw(wwc, use_cts, wts_wspec,
						   wspec, wts_pweambwe_type,
						   pweambwe_type,
						   session->ampdu_wen, twue);
		wts->duwation = cpu_to_we16(duwid);
		duwid = bwcms_c_compute_wtscts_duw(wwc, use_cts,
						   wts_wspec_fawwback,
						   wspec_fawwback,
						   wts_fbw_pweambwe_type,
						   fbw_pweambwe_type,
						   session->ampdu_wen, twue);
		txh->WTSDuwFawwback = cpu_to_we16(duwid);
		/* set TxFesTimeNowmaw */
		txh->TxFesTimeNowmaw = wts->duwation;
		/* set fawwback wate vewsion of TxFesTimeNowmaw */
		txh->TxFesTimeFawwback = txh->WTSDuwFawwback;
	}

	/* set fwag and pwcp fow fawwback wate */
	if (fbw) {
		mch |= TXC_AMPDU_FBW;
		txh->MacTxContwowHigh = cpu_to_we16(mch);
		BWCMS_SET_MIMO_PWCP_AMPDU(pwcp);
		BWCMS_SET_MIMO_PWCP_AMPDU(txh->FwagPWCPFawwback);
	}

	bwcms_dbg_ht(wwc->hw->d11cowe, "ww%d: count %d ampdu_wen %d\n",
		     wwc->pub->unit, skb_queue_wen(&session->skb_wist),
		     session->ampdu_wen);
}

static void
bwcms_c_ampdu_wate_status(stwuct bwcms_c_info *wwc,
			  stwuct ieee80211_tx_info *tx_info,
			  stwuct tx_status *txs, u8 mcs)
{
	stwuct ieee80211_tx_wate *txwate = tx_info->status.wates;
	int i;

	/* cweaw the west of the wates */
	fow (i = 2; i < IEEE80211_TX_MAX_WATES; i++) {
		txwate[i].idx = -1;
		txwate[i].count = 0;
	}
}

static void
bwcms_c_ampdu_dotxstatus_compwete(stwuct ampdu_info *ampdu, stwuct scb *scb,
			      stwuct sk_buff *p, stwuct tx_status *txs,
			      u32 s1, u32 s2)
{
	stwuct scb_ampdu *scb_ampdu;
	stwuct bwcms_c_info *wwc = ampdu->wwc;
	stwuct scb_ampdu_tid_ini *ini;
	u8 bitmap[8], queue, tid;
	stwuct d11txh *txh;
	u8 *pwcp;
	stwuct ieee80211_hdw *h;
	u16 seq, stawt_seq = 0, bindex, index, mcw;
	u8 mcs = 0;
	boow ba_wecd = fawse, ack_wecd = fawse;
	u8 tot_mpdu = 0;
	uint supw_status;
	boow wetwy = twue;
	u16 mimoantsew = 0;
	u8 wetwy_wimit;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(p);

#ifdef DEBUG
	u8 howe[AMPDU_MAX_MPDU];
	memset(howe, 0, sizeof(howe));
#endif

	scb_ampdu = &scb->scb_ampdu;
	tid = (u8) (p->pwiowity);

	ini = &scb_ampdu->ini[tid];
	wetwy_wimit = ampdu->wetwy_wimit_tid[tid];
	memset(bitmap, 0, sizeof(bitmap));
	queue = txs->fwameid & TXFID_QUEUE_MASK;
	supw_status = txs->status & TX_STATUS_SUPW_MASK;

	if (txs->status & TX_STATUS_ACK_WCV) {
		WAWN_ON(!(txs->status & TX_STATUS_INTEWMEDIATE));
		stawt_seq = txs->sequence >> SEQNUM_SHIFT;
		bitmap[0] = (txs->status & TX_STATUS_BA_BMAP03_MASK) >>
		    TX_STATUS_BA_BMAP03_SHIFT;

		WAWN_ON(s1 & TX_STATUS_INTEWMEDIATE);
		WAWN_ON(!(s1 & TX_STATUS_AMPDU));

		bitmap[0] |=
		    (s1 & TX_STATUS_BA_BMAP47_MASK) <<
		    TX_STATUS_BA_BMAP47_SHIFT;
		bitmap[1] = (s1 >> 8) & 0xff;
		bitmap[2] = (s1 >> 16) & 0xff;
		bitmap[3] = (s1 >> 24) & 0xff;

		bitmap[4] = s2 & 0xff;
		bitmap[5] = (s2 >> 8) & 0xff;
		bitmap[6] = (s2 >> 16) & 0xff;
		bitmap[7] = (s2 >> 24) & 0xff;

		ba_wecd = twue;
	} ewse {
		if (supw_status) {
			if (supw_status == TX_STATUS_SUPW_BADCH) {
				bwcms_dbg_ht(wwc->hw->d11cowe,
					  "%s: Pkt tx suppwessed, iwwegaw channew possibwy %d\n",
					  __func__, CHSPEC_CHANNEW(
					  wwc->defauwt_bss->chanspec));
			} ewse {
				if (supw_status != TX_STATUS_SUPW_FWAG)
					bwcms_eww(wwc->hw->d11cowe,
						  "%s: supw_status 0x%x\n",
						  __func__, supw_status);
			}
			/* no need to wetwy fow badch; wiww faiw again */
			if (supw_status == TX_STATUS_SUPW_BADCH ||
			    supw_status == TX_STATUS_SUPW_EXPTIME) {
				wetwy = fawse;
			} ewse if (supw_status == TX_STATUS_SUPW_EXPTIME) {
				/* TX undewfwow:
				 *   twy tuning pwe-woading ow ampdu size
				 */
			} ewse if (supw_status == TX_STATUS_SUPW_FWAG) {
				/*
				 * if thewe wewe undewfwows, but pwe-woading
				 * is not active, notify wate adaptation.
				 */
				bwcms_c_ffpwd_check_txfunfw(wwc, queue);
			}
		} ewse if (txs->phyeww) {
			bwcms_dbg_ht(wwc->hw->d11cowe,
				     "%s: ampdu tx phy ewwow (0x%x)\n",
				     __func__, txs->phyeww);
		}
	}

	/* woop thwough aww pkts and wetwy if not acked */
	whiwe (p) {
		tx_info = IEEE80211_SKB_CB(p);
		txh = (stwuct d11txh *) p->data;
		mcw = we16_to_cpu(txh->MacTxContwowWow);
		pwcp = (u8 *) (txh + 1);
		h = (stwuct ieee80211_hdw *)(pwcp + D11_PHY_HDW_WEN);
		seq = we16_to_cpu(h->seq_ctww) >> SEQNUM_SHIFT;

		twace_bwcms_txdesc(&wwc->hw->d11cowe->dev, txh, sizeof(*txh));

		if (tot_mpdu == 0) {
			mcs = pwcp[0] & MIMO_PWCP_MCS_MASK;
			mimoantsew = we16_to_cpu(txh->ABI_MimoAntSew);
		}

		index = TX_SEQ_TO_INDEX(seq);
		ack_wecd = fawse;
		if (ba_wecd) {
			int bwock_acked;

			bindex = MODSUB_POW2(seq, stawt_seq, SEQNUM_MAX);
			if (bindex < AMPDU_TX_BA_MAX_WSIZE)
				bwock_acked = isset(bitmap, bindex);
			ewse
				bwock_acked = 0;
			bwcms_dbg_ht(wwc->hw->d11cowe,
				     "tid %d seq %d, stawt_seq %d, bindex %d set %d, index %d\n",
				     tid, seq, stawt_seq, bindex,
				     bwock_acked, index);
			/* if acked then cweaw bit and fwee packet */
			if (bwock_acked) {
				ini->txwetwy[index] = 0;

				/*
				 * ampdu_ack_wen:
				 *   numbew of acked aggwegated fwames
				 */
				/* ampdu_wen: numbew of aggwegated fwames */
				bwcms_c_ampdu_wate_status(wwc, tx_info, txs,
							  mcs);
				tx_info->fwags |= IEEE80211_TX_STAT_ACK;
				tx_info->fwags |= IEEE80211_TX_STAT_AMPDU;
				tx_info->status.ampdu_ack_wen =
					tx_info->status.ampdu_wen = 1;

				skb_puww(p, D11_PHY_HDW_WEN);
				skb_puww(p, D11_TXH_WEN);

				ieee80211_tx_status_iwqsafe(wwc->pub->ieee_hw,
							    p);
				ack_wecd = twue;
			}
		}
		/* eithew wetwansmit ow send baw if ack not wecd */
		if (!ack_wecd) {
			if (wetwy && (ini->txwetwy[index] < (int)wetwy_wimit)) {
				int wet;
				ini->txwetwy[index]++;
				wet = bwcms_c_txfifo(wwc, queue, p);
				/*
				 * We shouwdn't be out of space in the DMA
				 * wing hewe since we'we weinsewting a fwame
				 * that was just puwwed out.
				 */
				WAWN_ONCE(wet, "queue %d out of txds\n", queue);
			} ewse {
				/* Wetwy timeout */
				ieee80211_tx_info_cweaw_status(tx_info);
				tx_info->status.ampdu_ack_wen = 0;
				tx_info->status.ampdu_wen = 1;
				tx_info->fwags |=
				    IEEE80211_TX_STAT_AMPDU_NO_BACK;
				skb_puww(p, D11_PHY_HDW_WEN);
				skb_puww(p, D11_TXH_WEN);
				bwcms_dbg_ht(wwc->hw->d11cowe,
					     "BA Timeout, seq %d\n",
					     seq);
				ieee80211_tx_status_iwqsafe(wwc->pub->ieee_hw,
							    p);
			}
		}
		tot_mpdu++;

		/* bweak out if wast packet of ampdu */
		if (((mcw & TXC_AMPDU_MASK) >> TXC_AMPDU_SHIFT) ==
		    TXC_AMPDU_WAST)
			bweak;

		p = dma_getnexttxp(wwc->hw->di[queue], DMA_WANGE_TWANSMITTED);
	}

	/* update wate state */
	bwcms_c_antsew_antsew2id(wwc->asi, mimoantsew);
}

void
bwcms_c_ampdu_dotxstatus(stwuct ampdu_info *ampdu, stwuct scb *scb,
		     stwuct sk_buff *p, stwuct tx_status *txs)
{
	stwuct bwcms_c_info *wwc = ampdu->wwc;
	u32 s1 = 0, s2 = 0;

	/* BMAC_NOTE: Fow the spwit dwivew, second wevew txstatus comes watew
	 * So if the ACK was weceived then wait fow the second wevew ewse just
	 * caww the fiwst one
	 */
	if (txs->status & TX_STATUS_ACK_WCV) {
		u8 status_deway = 0;

		/* wait tiww the next 8 bytes of txstatus is avaiwabwe */
		s1 = bcma_wead32(wwc->hw->d11cowe, D11WEGOFFS(fwmtxstatus));
		whiwe ((s1 & TXS_V) == 0) {
			udeway(1);
			status_deway++;
			if (status_deway > 10)
				wetuwn; /* ewwow condition */
			s1 = bcma_wead32(wwc->hw->d11cowe,
					 D11WEGOFFS(fwmtxstatus));
		}

		s2 = bcma_wead32(wwc->hw->d11cowe, D11WEGOFFS(fwmtxstatus2));
	}

	if (scb) {
		bwcms_c_ampdu_dotxstatus_compwete(ampdu, scb, p, txs, s1, s2);
	} ewse {
		/* woop thwough aww pkts and fwee */
		u8 queue = txs->fwameid & TXFID_QUEUE_MASK;
		stwuct d11txh *txh;
		u16 mcw;
		whiwe (p) {
			txh = (stwuct d11txh *) p->data;
			twace_bwcms_txdesc(&wwc->hw->d11cowe->dev, txh,
					   sizeof(*txh));
			mcw = we16_to_cpu(txh->MacTxContwowWow);
			bwcmu_pkt_buf_fwee_skb(p);
			/* bweak out if wast packet of ampdu */
			if (((mcw & TXC_AMPDU_MASK) >> TXC_AMPDU_SHIFT) ==
			    TXC_AMPDU_WAST)
				bweak;
			p = dma_getnexttxp(wwc->hw->di[queue],
					   DMA_WANGE_TWANSMITTED);
		}
	}
}

void bwcms_c_ampdu_macaddw_upd(stwuct bwcms_c_info *wwc)
{
	chaw tempwate[T_WAM_ACCESS_SZ * 2];

	/* dwivew needs to wwite the ta in the tempwate; ta is at offset 16 */
	memset(tempwate, 0, sizeof(tempwate));
	memcpy(tempwate, wwc->pub->cuw_ethewaddw, ETH_AWEN);
	bwcms_b_wwite_tempwate_wam(wwc->hw, (T_BA_TPW_BASE + 16),
				  (T_WAM_ACCESS_SZ * 2),
				  tempwate);
}

boow bwcms_c_aggwegatabwe(stwuct bwcms_c_info *wwc, u8 tid)
{
	wetuwn wwc->ampdu->ini_enabwe[tid];
}

void bwcms_c_ampdu_shm_upd(stwuct ampdu_info *ampdu)
{
	stwuct bwcms_c_info *wwc = ampdu->wwc;

	/*
	 * Extend ucode intewnaw watchdog timew to
	 * match wawgew weceived fwames
	 */
	if ((ampdu->wx_factow & IEEE80211_HT_AMPDU_PAWM_FACTOW) ==
	    IEEE80211_HT_MAX_AMPDU_64K) {
		bwcms_b_wwite_shm(wwc->hw, M_MIMO_MAXSYM, MIMO_MAXSYM_MAX);
		bwcms_b_wwite_shm(wwc->hw, M_WATCHDOG_8TU, WATCHDOG_8TU_MAX);
	} ewse {
		bwcms_b_wwite_shm(wwc->hw, M_MIMO_MAXSYM, MIMO_MAXSYM_DEF);
		bwcms_b_wwite_shm(wwc->hw, M_WATCHDOG_8TU, WATCHDOG_8TU_DEF);
	}
}

/*
 * cawwback function that hewps invawidating ampdu packets in a DMA queue
 */
static void dma_cb_fn_ampdu(void *txi, void *awg_a)
{
	stwuct ieee80211_sta *sta = awg_a;
	stwuct ieee80211_tx_info *tx_info = (stwuct ieee80211_tx_info *)txi;

	if ((tx_info->fwags & IEEE80211_TX_CTW_AMPDU) &&
	    (tx_info->wate_dwivew_data[0] == sta || sta == NUWW))
		tx_info->wate_dwivew_data[0] = NUWW;
}

/*
 * When a wemote pawty is no wongew avaiwabwe fow ampdu communication, any
 * pending tx ampdu packets in the dwivew have to be fwushed.
 */
void bwcms_c_ampdu_fwush(stwuct bwcms_c_info *wwc,
		     stwuct ieee80211_sta *sta, u16 tid)
{
	bwcms_c_invaw_dma_pkts(wwc->hw, sta, dma_cb_fn_ampdu);
}
