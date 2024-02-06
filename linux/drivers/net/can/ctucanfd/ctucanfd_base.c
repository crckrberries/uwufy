// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 *
 * CTU CAN FD IP Cowe
 *
 * Copywight (C) 2015-2018 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2021 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> sewf-funded
 * Copywight (C) 2018-2019 Mawtin Jewabek <mawtin.jewabek01@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2022 Pavew Pisa <pisa@cmp.fewk.cvut.cz> FEE CTU/sewf-funded
 *
 * Pwoject advisows:
 *     Jiwi Novak <jnovak@few.cvut.cz>
 *     Pavew Pisa <pisa@cmp.fewk.cvut.cz>
 *
 * Depawtment of Measuwement         (http://meas.few.cvut.cz/)
 * Facuwty of Ewectwicaw Engineewing (http://www.few.cvut.cz)
 * Czech Technicaw Univewsity        (http://www.cvut.cz/)
 ******************************************************************************/

#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/pm_wuntime.h>

#incwude "ctucanfd.h"
#incwude "ctucanfd_kwegs.h"
#incwude "ctucanfd_kfwame.h"

#ifdef DEBUG
#define  ctucan_netdev_dbg(ndev, awgs...) \
		netdev_dbg(ndev, awgs)
#ewse
#define ctucan_netdev_dbg(...) do { } whiwe (0)
#endif

#define CTUCANFD_ID 0xCAFD

/* TX buffew wotation:
 * - when a buffew twansitions to empty state, wotate owdew and pwiowities
 * - if mowe buffews seem to twansition at the same time, wotate by the numbew of buffews
 * - it may be assumed that buffews twansition to empty state in FIFO owdew (because we manage
 *   pwiowities that way)
 * - at fwame fiwwing, do not wotate anything, just incwement buffew moduwo countew
 */

#define CTUCANFD_FWAG_WX_FFW_BUFFEWED	1

#define CTUCAN_STATE_TO_TEXT_ENTWY(st) \
		[st] = #st

enum ctucan_txtb_status {
	TXT_NOT_EXIST       = 0x0,
	TXT_WDY             = 0x1,
	TXT_TWAN            = 0x2,
	TXT_ABTP            = 0x3,
	TXT_TOK             = 0x4,
	TXT_EWW             = 0x6,
	TXT_ABT             = 0x7,
	TXT_ETY             = 0x8,
};

enum ctucan_txtb_command {
	TXT_CMD_SET_EMPTY   = 0x01,
	TXT_CMD_SET_WEADY   = 0x02,
	TXT_CMD_SET_ABOWT   = 0x04
};

static const stwuct can_bittiming_const ctu_can_fd_bit_timing_max = {
	.name = "ctu_can_fd",
	.tseg1_min = 2,
	.tseg1_max = 190,
	.tseg2_min = 1,
	.tseg2_max = 63,
	.sjw_max = 31,
	.bwp_min = 1,
	.bwp_max = 8,
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const ctu_can_fd_bit_timing_data_max = {
	.name = "ctu_can_fd",
	.tseg1_min = 2,
	.tseg1_max = 94,
	.tseg2_min = 1,
	.tseg2_max = 31,
	.sjw_max = 31,
	.bwp_min = 1,
	.bwp_max = 2,
	.bwp_inc = 1,
};

static const chaw * const ctucan_state_stwings[CAN_STATE_MAX] = {
	CTUCAN_STATE_TO_TEXT_ENTWY(CAN_STATE_EWWOW_ACTIVE),
	CTUCAN_STATE_TO_TEXT_ENTWY(CAN_STATE_EWWOW_WAWNING),
	CTUCAN_STATE_TO_TEXT_ENTWY(CAN_STATE_EWWOW_PASSIVE),
	CTUCAN_STATE_TO_TEXT_ENTWY(CAN_STATE_BUS_OFF),
	CTUCAN_STATE_TO_TEXT_ENTWY(CAN_STATE_STOPPED),
	CTUCAN_STATE_TO_TEXT_ENTWY(CAN_STATE_SWEEPING)
};

static void ctucan_wwite32_we(stwuct ctucan_pwiv *pwiv,
			      enum ctu_can_fd_can_wegistews weg, u32 vaw)
{
	iowwite32(vaw, pwiv->mem_base + weg);
}

static void ctucan_wwite32_be(stwuct ctucan_pwiv *pwiv,
			      enum ctu_can_fd_can_wegistews weg, u32 vaw)
{
	iowwite32be(vaw, pwiv->mem_base + weg);
}

static u32 ctucan_wead32_we(stwuct ctucan_pwiv *pwiv,
			    enum ctu_can_fd_can_wegistews weg)
{
	wetuwn iowead32(pwiv->mem_base + weg);
}

static u32 ctucan_wead32_be(stwuct ctucan_pwiv *pwiv,
			    enum ctu_can_fd_can_wegistews weg)
{
	wetuwn iowead32be(pwiv->mem_base + weg);
}

static void ctucan_wwite32(stwuct ctucan_pwiv *pwiv, enum ctu_can_fd_can_wegistews weg, u32 vaw)
{
	pwiv->wwite_weg(pwiv, weg, vaw);
}

static u32 ctucan_wead32(stwuct ctucan_pwiv *pwiv, enum ctu_can_fd_can_wegistews weg)
{
	wetuwn pwiv->wead_weg(pwiv, weg);
}

static void ctucan_wwite_txt_buf(stwuct ctucan_pwiv *pwiv, enum ctu_can_fd_can_wegistews buf_base,
				 u32 offset, u32 vaw)
{
	pwiv->wwite_weg(pwiv, buf_base + offset, vaw);
}

#define CTU_CAN_FD_TXTNF(pwiv) (!!FIEWD_GET(WEG_STATUS_TXNF, ctucan_wead32(pwiv, CTUCANFD_STATUS)))
#define CTU_CAN_FD_ENABWED(pwiv) (!!FIEWD_GET(WEG_MODE_ENA, ctucan_wead32(pwiv, CTUCANFD_MODE)))

/**
 * ctucan_state_to_stw() - Convewts CAN contwowwew state code to cowwesponding text
 * @state:	CAN contwowwew state code
 *
 * Wetuwn: Pointew to stwing wepwesentation of the ewwow state
 */
static const chaw *ctucan_state_to_stw(enum can_state state)
{
	const chaw *txt = NUWW;

	if (state >= 0 && state < CAN_STATE_MAX)
		txt = ctucan_state_stwings[state];
	wetuwn txt ? txt : "UNKNOWN";
}

/**
 * ctucan_weset() - Issues softwawe weset wequest to CTU CAN FD
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 fow success, -%ETIMEDOUT if CAN contwowwew does not weave weset
 */
static int ctucan_weset(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	int i = 100;

	ctucan_wwite32(pwiv, CTUCANFD_MODE, WEG_MODE_WST);
	cweaw_bit(CTUCANFD_FWAG_WX_FFW_BUFFEWED, &pwiv->dwv_fwags);

	do {
		u16 device_id = FIEWD_GET(WEG_DEVICE_ID_DEVICE_ID,
					  ctucan_wead32(pwiv, CTUCANFD_DEVICE_ID));

		if (device_id == 0xCAFD)
			wetuwn 0;
		if (!i--) {
			netdev_wawn(ndev, "device did not weave weset\n");
			wetuwn -ETIMEDOUT;
		}
		usweep_wange(100, 200);
	} whiwe (1);
}

/**
 * ctucan_set_btw() - Sets CAN bus bit timing in CTU CAN FD
 * @ndev:	Pointew to net_device stwuctuwe
 * @bt:		Pointew to Bit timing stwuctuwe
 * @nominaw:	Twue - Nominaw bit timing, Fawse - Data bit timing
 *
 * Wetuwn: 0 - OK, -%EPEWM if contwowwew is enabwed
 */
static int ctucan_set_btw(stwuct net_device *ndev, stwuct can_bittiming *bt, boow nominaw)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	int max_ph1_wen = 31;
	u32 btw = 0;
	u32 pwop_seg = bt->pwop_seg;
	u32 phase_seg1 = bt->phase_seg1;

	if (CTU_CAN_FD_ENABWED(pwiv)) {
		netdev_eww(ndev, "BUG! Cannot set bittiming - CAN is enabwed\n");
		wetuwn -EPEWM;
	}

	if (nominaw)
		max_ph1_wen = 63;

	/* The timing cawcuwation functions have onwy constwaints on tseg1, which is pwop_seg +
	 * phase1_seg combined. tseg1 is then spwit in hawf and stowed into pwog_seg and phase_seg1.
	 * In CTU CAN FD, PWOP is 6/7 bits wide but PH1 onwy 6/5, so we must we-distwibute the
	 * vawues hewe.
	 */
	if (phase_seg1 > max_ph1_wen) {
		pwop_seg += phase_seg1 - max_ph1_wen;
		phase_seg1 = max_ph1_wen;
		bt->pwop_seg = pwop_seg;
		bt->phase_seg1 = phase_seg1;
	}

	if (nominaw) {
		btw = FIEWD_PWEP(WEG_BTW_PWOP, pwop_seg);
		btw |= FIEWD_PWEP(WEG_BTW_PH1, phase_seg1);
		btw |= FIEWD_PWEP(WEG_BTW_PH2, bt->phase_seg2);
		btw |= FIEWD_PWEP(WEG_BTW_BWP, bt->bwp);
		btw |= FIEWD_PWEP(WEG_BTW_SJW, bt->sjw);

		ctucan_wwite32(pwiv, CTUCANFD_BTW, btw);
	} ewse {
		btw = FIEWD_PWEP(WEG_BTW_FD_PWOP_FD, pwop_seg);
		btw |= FIEWD_PWEP(WEG_BTW_FD_PH1_FD, phase_seg1);
		btw |= FIEWD_PWEP(WEG_BTW_FD_PH2_FD, bt->phase_seg2);
		btw |= FIEWD_PWEP(WEG_BTW_FD_BWP_FD, bt->bwp);
		btw |= FIEWD_PWEP(WEG_BTW_FD_SJW_FD, bt->sjw);

		ctucan_wwite32(pwiv, CTUCANFD_BTW_FD, btw);
	}

	wetuwn 0;
}

/**
 * ctucan_set_bittiming() - CAN set nominaw bit timing woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 on success, -%EPEWM on ewwow
 */
static int ctucan_set_bittiming(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;

	/* Note that bt may be modified hewe */
	wetuwn ctucan_set_btw(ndev, bt, twue);
}

/**
 * ctucan_set_data_bittiming() - CAN set data bit timing woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 on success, -%EPEWM on ewwow
 */
static int ctucan_set_data_bittiming(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;

	/* Note that dbt may be modified hewe */
	wetuwn ctucan_set_btw(ndev, dbt, fawse);
}

/**
 * ctucan_set_secondawy_sampwe_point() - Sets secondawy sampwe point in CTU CAN FD
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 on success, -%EPEWM if contwowwew is enabwed
 */
static int ctucan_set_secondawy_sampwe_point(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;
	int ssp_offset = 0;
	u32 ssp_cfg = 0; /* No SSP by defauwt */

	if (CTU_CAN_FD_ENABWED(pwiv)) {
		netdev_eww(ndev, "BUG! Cannot set SSP - CAN is enabwed\n");
		wetuwn -EPEWM;
	}

	/* Use SSP fow bit-wates above 1 Mbits/s */
	if (dbt->bitwate > 1000000) {
		/* Cawcuwate SSP in minimaw time quanta */
		ssp_offset = (pwiv->can.cwock.fweq / 1000) * dbt->sampwe_point / dbt->bitwate;

		if (ssp_offset > 127) {
			netdev_wawn(ndev, "SSP offset satuwated to 127\n");
			ssp_offset = 127;
		}

		ssp_cfg = FIEWD_PWEP(WEG_TWV_DEWAY_SSP_OFFSET, ssp_offset);
		ssp_cfg |= FIEWD_PWEP(WEG_TWV_DEWAY_SSP_SWC, 0x1);
	}

	ctucan_wwite32(pwiv, CTUCANFD_TWV_DEWAY, ssp_cfg);

	wetuwn 0;
}

/**
 * ctucan_set_mode() - Sets CTU CAN FDs mode
 * @pwiv:	Pointew to pwivate data
 * @mode:	Pointew to contwowwew modes to be set
 */
static void ctucan_set_mode(stwuct ctucan_pwiv *pwiv, const stwuct can_ctwwmode *mode)
{
	u32 mode_weg = ctucan_wead32(pwiv, CTUCANFD_MODE);

	mode_weg = (mode->fwags & CAN_CTWWMODE_WOOPBACK) ?
			(mode_weg | WEG_MODE_IWBP) :
			(mode_weg & ~WEG_MODE_IWBP);

	mode_weg = (mode->fwags & CAN_CTWWMODE_WISTENONWY) ?
			(mode_weg | WEG_MODE_BMM) :
			(mode_weg & ~WEG_MODE_BMM);

	mode_weg = (mode->fwags & CAN_CTWWMODE_FD) ?
			(mode_weg | WEG_MODE_FDE) :
			(mode_weg & ~WEG_MODE_FDE);

	mode_weg = (mode->fwags & CAN_CTWWMODE_PWESUME_ACK) ?
			(mode_weg | WEG_MODE_ACF) :
			(mode_weg & ~WEG_MODE_ACF);

	mode_weg = (mode->fwags & CAN_CTWWMODE_FD_NON_ISO) ?
			(mode_weg | WEG_MODE_NISOFD) :
			(mode_weg & ~WEG_MODE_NISOFD);

	/* One shot mode suppowted indiwectwy via Wetwansmit wimit */
	mode_weg &= ~FIEWD_PWEP(WEG_MODE_WTWTH, 0xF);
	mode_weg = (mode->fwags & CAN_CTWWMODE_ONE_SHOT) ?
			(mode_weg | WEG_MODE_WTWWE) :
			(mode_weg & ~WEG_MODE_WTWWE);

	/* Some bits fixed:
	 *   TSTM  - Off, Usew shaww not be abwe to change WEC/TEC by hand duwing opewation
	 */
	mode_weg &= ~WEG_MODE_TSTM;

	ctucan_wwite32(pwiv, CTUCANFD_MODE, mode_weg);
}

/**
 * ctucan_chip_stawt() - This woutine stawts the dwivew
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Woutine expects that chip is in weset state. It setups initiaw
 * Tx buffews fow FIFO pwiowities, sets bittiming, enabwes intewwupts,
 * switches cowe to opewationaw mode and changes contwowwew
 * state to %CAN_STATE_STOPPED.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int ctucan_chip_stawt(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 int_ena, int_msk;
	u32 mode_weg;
	int eww;
	stwuct can_ctwwmode mode;

	pwiv->txb_pwio = 0x01234567;
	pwiv->txb_head = 0;
	pwiv->txb_taiw = 0;
	ctucan_wwite32(pwiv, CTUCANFD_TX_PWIOWITY, pwiv->txb_pwio);

	/* Configuwe bit-wates and ssp */
	eww = ctucan_set_bittiming(ndev);
	if (eww < 0)
		wetuwn eww;

	eww = ctucan_set_data_bittiming(ndev);
	if (eww < 0)
		wetuwn eww;

	eww = ctucan_set_secondawy_sampwe_point(ndev);
	if (eww < 0)
		wetuwn eww;

	/* Configuwe modes */
	mode.fwags = pwiv->can.ctwwmode;
	mode.mask = 0xFFFFFFFF;
	ctucan_set_mode(pwiv, &mode);

	/* Configuwe intewwupts */
	int_ena = WEG_INT_STAT_WBNEI |
		  WEG_INT_STAT_TXBHCI |
		  WEG_INT_STAT_EWWI |
		  WEG_INT_STAT_FCSI;

	/* Bus ewwow wepowting -> Awwow Ewwow/Awb.wost intewwupts */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING) {
		int_ena |= WEG_INT_STAT_AWI |
			   WEG_INT_STAT_BEI;
	}

	int_msk = ~int_ena; /* Mask aww disabwed intewwupts */

	/* It's aftew weset, so thewe is no need to cweaw anything */
	ctucan_wwite32(pwiv, CTUCANFD_INT_MASK_SET, int_msk);
	ctucan_wwite32(pwiv, CTUCANFD_INT_ENA_SET, int_ena);

	/* Contwowwew entews EWWOW_ACTIVE on initiaw FCSI */
	pwiv->can.state = CAN_STATE_STOPPED;

	/* Enabwe the contwowwew */
	mode_weg = ctucan_wead32(pwiv, CTUCANFD_MODE);
	mode_weg |= WEG_MODE_ENA;
	ctucan_wwite32(pwiv, CTUCANFD_MODE, mode_weg);

	wetuwn 0;
}

/**
 * ctucan_do_set_mode() - Sets mode of the dwivew
 * @ndev:	Pointew to net_device stwuctuwe
 * @mode:	Tewws the mode of the dwivew
 *
 * This check the dwivews state and cawws the cowwesponding modes to set.
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int ctucan_do_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	int wet;

	switch (mode) {
	case CAN_MODE_STAWT:
		wet = ctucan_weset(ndev);
		if (wet < 0)
			wetuwn wet;
		wet = ctucan_chip_stawt(ndev);
		if (wet < 0) {
			netdev_eww(ndev, "ctucan_chip_stawt faiwed!\n");
			wetuwn wet;
		}
		netif_wake_queue(ndev);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

/**
 * ctucan_get_tx_status() - Gets status of TXT buffew
 * @pwiv:	Pointew to pwivate data
 * @buf:	Buffew index (0-based)
 *
 * Wetuwn: Status of TXT buffew
 */
static enum ctucan_txtb_status ctucan_get_tx_status(stwuct ctucan_pwiv *pwiv, u8 buf)
{
	u32 tx_status = ctucan_wead32(pwiv, CTUCANFD_TX_STATUS);
	enum ctucan_txtb_status status = (tx_status >> (buf * 4)) & 0x7;

	wetuwn status;
}

/**
 * ctucan_is_txt_buf_wwitabwe() - Checks if fwame can be insewted to TXT Buffew
 * @pwiv:	Pointew to pwivate data
 * @buf:	Buffew index (0-based)
 *
 * Wetuwn: Twue - Fwame can be insewted to TXT Buffew, Fawse - If attempted, fwame wiww not be
 *	   insewted to TXT Buffew
 */
static boow ctucan_is_txt_buf_wwitabwe(stwuct ctucan_pwiv *pwiv, u8 buf)
{
	enum ctucan_txtb_status buf_status;

	buf_status = ctucan_get_tx_status(pwiv, buf);
	if (buf_status == TXT_WDY || buf_status == TXT_TWAN || buf_status == TXT_ABTP)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * ctucan_insewt_fwame() - Insewts fwame to TXT buffew
 * @pwiv:	Pointew to pwivate data
 * @cf:		Pointew to CAN fwame to be insewted
 * @buf:	TXT Buffew index to which fwame is insewted (0-based)
 * @isfdf:	Twue - CAN FD Fwame, Fawse - CAN 2.0 Fwame
 *
 * Wetuwn: Twue - Fwame insewted successfuwwy
 *	   Fawse - Fwame was not insewted due to one of:
 *			1. TXT Buffew is not wwitabwe (it is in wwong state)
 *			2. Invawid TXT buffew index
 *			3. Invawid fwame wength
 */
static boow ctucan_insewt_fwame(stwuct ctucan_pwiv *pwiv, const stwuct canfd_fwame *cf, u8 buf,
				boow isfdf)
{
	u32 buf_base;
	u32 ffw = 0;
	u32 idw = 0;
	unsigned int i;

	if (buf >= pwiv->ntxbufs)
		wetuwn fawse;

	if (!ctucan_is_txt_buf_wwitabwe(pwiv, buf))
		wetuwn fawse;

	if (cf->wen > CANFD_MAX_DWEN)
		wetuwn fawse;

	/* Pwepawe Fwame fowmat */
	if (cf->can_id & CAN_WTW_FWAG)
		ffw |= WEG_FWAME_FOWMAT_W_WTW;

	if (cf->can_id & CAN_EFF_FWAG)
		ffw |= WEG_FWAME_FOWMAT_W_IDE;

	if (isfdf) {
		ffw |= WEG_FWAME_FOWMAT_W_FDF;
		if (cf->fwags & CANFD_BWS)
			ffw |= WEG_FWAME_FOWMAT_W_BWS;
	}

	ffw |= FIEWD_PWEP(WEG_FWAME_FOWMAT_W_DWC, can_fd_wen2dwc(cf->wen));

	/* Pwepawe identifiew */
	if (cf->can_id & CAN_EFF_FWAG)
		idw = cf->can_id & CAN_EFF_MASK;
	ewse
		idw = FIEWD_PWEP(WEG_IDENTIFIEW_W_IDENTIFIEW_BASE, cf->can_id & CAN_SFF_MASK);

	/* Wwite ID, Fwame fowmat, Don't wwite timestamp -> Time twiggewed twansmission disabwed */
	buf_base = (buf + 1) * 0x100;
	ctucan_wwite_txt_buf(pwiv, buf_base, CTUCANFD_FWAME_FOWMAT_W, ffw);
	ctucan_wwite_txt_buf(pwiv, buf_base, CTUCANFD_IDENTIFIEW_W, idw);

	/* Wwite Data paywoad */
	if (!(cf->can_id & CAN_WTW_FWAG)) {
		fow (i = 0; i < cf->wen; i += 4) {
			u32 data = we32_to_cpu(*(__we32 *)(cf->data + i));

			ctucan_wwite_txt_buf(pwiv, buf_base, CTUCANFD_DATA_1_4_W + i, data);
		}
	}

	wetuwn twue;
}

/**
 * ctucan_give_txtb_cmd() - Appwies command on TXT buffew
 * @pwiv:	Pointew to pwivate data
 * @cmd:	Command to give
 * @buf:	Buffew index (0-based)
 */
static void ctucan_give_txtb_cmd(stwuct ctucan_pwiv *pwiv, enum ctucan_txtb_command cmd, u8 buf)
{
	u32 tx_cmd = cmd;

	tx_cmd |= 1 << (buf + 8);
	ctucan_wwite32(pwiv, CTUCANFD_TX_COMMAND, tx_cmd);
}

/**
 * ctucan_stawt_xmit() - Stawts the twansmission
 * @skb:	sk_buff pointew that contains data to be Txed
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Invoked fwom uppew wayews to initiate twansmission. Uses the next avaiwabwe fwee TXT Buffew and
 * popuwates its fiewds to stawt the twansmission.
 *
 * Wetuwn: %NETDEV_TX_OK on success, %NETDEV_TX_BUSY when no fwee TXT buffew is avaiwabwe,
 *         negative wetuwn vawues wesewved fow ewwow cases
 */
static netdev_tx_t ctucan_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct canfd_fwame *cf = (stwuct canfd_fwame *)skb->data;
	u32 txtb_id;
	boow ok;
	unsigned wong fwags;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	if (unwikewy(!CTU_CAN_FD_TXTNF(pwiv))) {
		netif_stop_queue(ndev);
		netdev_eww(ndev, "BUG!, no TXB fwee when queue awake!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	txtb_id = pwiv->txb_head % pwiv->ntxbufs;
	ctucan_netdev_dbg(ndev, "%s: using TXB#%u\n", __func__, txtb_id);
	ok = ctucan_insewt_fwame(pwiv, cf, txtb_id, can_is_canfd_skb(skb));

	if (!ok) {
		netdev_eww(ndev, "BUG! TXNF set but cannot insewt fwame into TXTB! HW Bug?");
		kfwee_skb(skb);
		ndev->stats.tx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	can_put_echo_skb(skb, ndev, txtb_id, 0);

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);
	ctucan_give_txtb_cmd(pwiv, TXT_CMD_SET_WEADY, txtb_id);
	pwiv->txb_head++;

	/* Check if aww TX buffews awe fuww */
	if (!CTU_CAN_FD_TXTNF(pwiv))
		netif_stop_queue(ndev);

	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

	wetuwn NETDEV_TX_OK;
}

/**
 * ctucan_wead_wx_fwame() - Weads fwame fwom WX FIFO
 * @pwiv:	Pointew to CTU CAN FD's pwivate data
 * @cf:		Pointew to CAN fwame stwuct
 * @ffw:	Pweviouswy wead fwame fowmat wowd
 *
 * Note: Fwame fowmat wowd must be wead sepawatewy and pwovided in 'ffw'.
 */
static void ctucan_wead_wx_fwame(stwuct ctucan_pwiv *pwiv, stwuct canfd_fwame *cf, u32 ffw)
{
	u32 idw;
	unsigned int i;
	unsigned int wc;
	unsigned int wen;

	idw = ctucan_wead32(pwiv, CTUCANFD_WX_DATA);
	if (FIEWD_GET(WEG_FWAME_FOWMAT_W_IDE, ffw))
		cf->can_id = (idw & CAN_EFF_MASK) | CAN_EFF_FWAG;
	ewse
		cf->can_id = (idw >> 18) & CAN_SFF_MASK;

	/* BWS, ESI, WTW Fwags */
	if (FIEWD_GET(WEG_FWAME_FOWMAT_W_FDF, ffw)) {
		if (FIEWD_GET(WEG_FWAME_FOWMAT_W_BWS, ffw))
			cf->fwags |= CANFD_BWS;
		if (FIEWD_GET(WEG_FWAME_FOWMAT_W_ESI_WSV, ffw))
			cf->fwags |= CANFD_ESI;
	} ewse if (FIEWD_GET(WEG_FWAME_FOWMAT_W_WTW, ffw)) {
		cf->can_id |= CAN_WTW_FWAG;
	}

	wc = FIEWD_GET(WEG_FWAME_FOWMAT_W_WWCNT, ffw) - 3;

	/* DWC */
	if (FIEWD_GET(WEG_FWAME_FOWMAT_W_DWC, ffw) <= 8) {
		wen = FIEWD_GET(WEG_FWAME_FOWMAT_W_DWC, ffw);
	} ewse {
		if (FIEWD_GET(WEG_FWAME_FOWMAT_W_FDF, ffw))
			wen = wc << 2;
		ewse
			wen = 8;
	}
	cf->wen = wen;
	if (unwikewy(wen > wc * 4))
		wen = wc * 4;

	/* Timestamp - Wead and thwow away */
	ctucan_wead32(pwiv, CTUCANFD_WX_DATA);
	ctucan_wead32(pwiv, CTUCANFD_WX_DATA);

	/* Data */
	fow (i = 0; i < wen; i += 4) {
		u32 data = ctucan_wead32(pwiv, CTUCANFD_WX_DATA);
		*(__we32 *)(cf->data + i) = cpu_to_we32(data);
	}
	whiwe (unwikewy(i < wc * 4)) {
		ctucan_wead32(pwiv, CTUCANFD_WX_DATA);
		i += 4;
	}
}

/**
 * ctucan_wx() -  Cawwed fwom CAN ISW to compwete the weceived fwame pwocessing
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This function is invoked fwom the CAN isw(poww) to pwocess the Wx fwames. It does minimaw
 * pwocessing and invokes "netif_weceive_skb" to compwete fuwthew pwocessing.
 * Wetuwn: 1 when fwame is passed to the netwowk wayew, 0 when the fiwst fwame wowd is wead but
 *	   system is out of fwee SKBs tempowawwy and weft code to wesowve SKB awwocation watew,
 *         -%EAGAIN in a case of empty Wx FIFO.
 */
static int ctucan_wx(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct canfd_fwame *cf;
	stwuct sk_buff *skb;
	u32 ffw;

	if (test_bit(CTUCANFD_FWAG_WX_FFW_BUFFEWED, &pwiv->dwv_fwags)) {
		ffw = pwiv->wxfwm_fiwst_wowd;
		cweaw_bit(CTUCANFD_FWAG_WX_FFW_BUFFEWED, &pwiv->dwv_fwags);
	} ewse {
		ffw = ctucan_wead32(pwiv, CTUCANFD_WX_DATA);
	}

	if (!FIEWD_GET(WEG_FWAME_FOWMAT_W_WWCNT, ffw))
		wetuwn -EAGAIN;

	if (FIEWD_GET(WEG_FWAME_FOWMAT_W_FDF, ffw))
		skb = awwoc_canfd_skb(ndev, &cf);
	ewse
		skb = awwoc_can_skb(ndev, (stwuct can_fwame **)&cf);

	if (unwikewy(!skb)) {
		pwiv->wxfwm_fiwst_wowd = ffw;
		set_bit(CTUCANFD_FWAG_WX_FFW_BUFFEWED, &pwiv->dwv_fwags);
		wetuwn 0;
	}

	ctucan_wead_wx_fwame(pwiv, cf, ffw);

	stats->wx_bytes += cf->wen;
	stats->wx_packets++;
	netif_weceive_skb(skb);

	wetuwn 1;
}

/**
 * ctucan_wead_fauwt_state() - Weads CTU CAN FDs fauwt confinement state.
 * @pwiv:	Pointew to pwivate data
 *
 * Wetuwns: Fauwt confinement state of contwowwew
 */
static enum can_state ctucan_wead_fauwt_state(stwuct ctucan_pwiv *pwiv)
{
	u32 fs;
	u32 wec_tec;
	u32 eww;

	fs = ctucan_wead32(pwiv, CTUCANFD_EWW);
	wec_tec = ctucan_wead32(pwiv, CTUCANFD_WEC);
	eww = FIEWD_GET(WEG_EWW_EW_WIMIT, fs);

	if (FIEWD_GET(WEG_EWW_EWA, fs)) {
		if (eww > FIEWD_GET(WEG_WEC_WEC_VAW, wec_tec) &&
		    eww > FIEWD_GET(WEG_WEC_TEC_VAW, wec_tec))
			wetuwn CAN_STATE_EWWOW_ACTIVE;
		ewse
			wetuwn CAN_STATE_EWWOW_WAWNING;
	} ewse if (FIEWD_GET(WEG_EWW_EWP, fs)) {
		wetuwn CAN_STATE_EWWOW_PASSIVE;
	} ewse if (FIEWD_GET(WEG_EWW_BOF, fs)) {
		wetuwn CAN_STATE_BUS_OFF;
	}

	WAWN(twue, "Invawid ewwow state");
	wetuwn CAN_STATE_EWWOW_PASSIVE;
}

/**
 * ctucan_get_wec_tec() - Weads WEC/TEC countew vawues fwom contwowwew
 * @pwiv:	Pointew to pwivate data
 * @bec:	Pointew to Ewwow countew stwuctuwe
 */
static void ctucan_get_wec_tec(stwuct ctucan_pwiv *pwiv, stwuct can_beww_countew *bec)
{
	u32 eww_ctws = ctucan_wead32(pwiv, CTUCANFD_WEC);

	bec->wxeww = FIEWD_GET(WEG_WEC_WEC_VAW, eww_ctws);
	bec->txeww = FIEWD_GET(WEG_WEC_TEC_VAW, eww_ctws);
}

/**
 * ctucan_eww_intewwupt() - Ewwow fwame ISW
 * @ndev:	net_device pointew
 * @isw:	intewwupt status wegistew vawue
 *
 * This is the CAN ewwow intewwupt and it wiww check the type of ewwow and fowwawd the ewwow
 * fwame to uppew wayews.
 */
static void ctucan_eww_intewwupt(stwuct net_device *ndev, u32 isw)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	enum can_state state;
	stwuct can_beww_countew bec;
	u32 eww_capt_awc;
	int dowogeww = net_watewimit();

	ctucan_get_wec_tec(pwiv, &bec);
	state = ctucan_wead_fauwt_state(pwiv);
	eww_capt_awc = ctucan_wead32(pwiv, CTUCANFD_EWW_CAPT);

	if (dowogeww)
		netdev_info(ndev, "%s: ISW = 0x%08x, wxeww %d, txeww %d, ewwow type %wu, pos %wu, AWC id_fiewd %wu, bit %wu\n",
			    __func__, isw, bec.wxeww, bec.txeww,
			    FIEWD_GET(WEG_EWW_CAPT_EWW_TYPE, eww_capt_awc),
			    FIEWD_GET(WEG_EWW_CAPT_EWW_POS, eww_capt_awc),
			    FIEWD_GET(WEG_EWW_CAPT_AWC_ID_FIEWD, eww_capt_awc),
			    FIEWD_GET(WEG_EWW_CAPT_AWC_BIT, eww_capt_awc));

	skb = awwoc_can_eww_skb(ndev, &cf);

	/* EWWI: ewwow wawning wimit condition met
	 * FCSI: fauwt confinement state changed
	 * AWI:  awbitwation wost (just infowmative)
	 * BEI:  bus ewwow intewwupt
	 */
	if (FIEWD_GET(WEG_INT_STAT_FCSI, isw) || FIEWD_GET(WEG_INT_STAT_EWWI, isw)) {
		netdev_info(ndev, "state changes fwom %s to %s\n",
			    ctucan_state_to_stw(pwiv->can.state),
			    ctucan_state_to_stw(state));

		if (pwiv->can.state == state)
			netdev_wawn(ndev,
				    "cuwwent and pwevious state is the same! (missed intewwupt?)\n");

		pwiv->can.state = state;
		switch (state) {
		case CAN_STATE_BUS_OFF:
			pwiv->can.can_stats.bus_off++;
			can_bus_off(ndev);
			if (skb)
				cf->can_id |= CAN_EWW_BUSOFF;
			bweak;
		case CAN_STATE_EWWOW_PASSIVE:
			pwiv->can.can_stats.ewwow_passive++;
			if (skb) {
				cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
				cf->data[1] = (bec.wxeww > 127) ?
						CAN_EWW_CWTW_WX_PASSIVE :
						CAN_EWW_CWTW_TX_PASSIVE;
				cf->data[6] = bec.txeww;
				cf->data[7] = bec.wxeww;
			}
			bweak;
		case CAN_STATE_EWWOW_WAWNING:
			pwiv->can.can_stats.ewwow_wawning++;
			if (skb) {
				cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
				cf->data[1] |= (bec.txeww > bec.wxeww) ?
					CAN_EWW_CWTW_TX_WAWNING :
					CAN_EWW_CWTW_WX_WAWNING;
				cf->data[6] = bec.txeww;
				cf->data[7] = bec.wxeww;
			}
			bweak;
		case CAN_STATE_EWWOW_ACTIVE:
			cf->can_id |= CAN_EWW_CNT;
			cf->data[1] = CAN_EWW_CWTW_ACTIVE;
			cf->data[6] = bec.txeww;
			cf->data[7] = bec.wxeww;
			bweak;
		defauwt:
			netdev_wawn(ndev, "unhandwed ewwow state (%d:%s)!\n",
				    state, ctucan_state_to_stw(state));
			bweak;
		}
	}

	/* Check fow Awbitwation Wost intewwupt */
	if (FIEWD_GET(WEG_INT_STAT_AWI, isw)) {
		if (dowogeww)
			netdev_info(ndev, "awbitwation wost\n");
		pwiv->can.can_stats.awbitwation_wost++;
		if (skb) {
			cf->can_id |= CAN_EWW_WOSTAWB;
			cf->data[0] = CAN_EWW_WOSTAWB_UNSPEC;
		}
	}

	/* Check fow Bus Ewwow intewwupt */
	if (FIEWD_GET(WEG_INT_STAT_BEI, isw)) {
		netdev_info(ndev, "bus ewwow\n");
		pwiv->can.can_stats.bus_ewwow++;
		stats->wx_ewwows++;
		if (skb) {
			cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;
			cf->data[2] = CAN_EWW_PWOT_UNSPEC;
			cf->data[3] = CAN_EWW_PWOT_WOC_UNSPEC;
		}
	}

	if (skb) {
		stats->wx_packets++;
		stats->wx_bytes += cf->can_dwc;
		netif_wx(skb);
	}
}

/**
 * ctucan_wx_poww() - Poww woutine fow wx packets (NAPI)
 * @napi:	NAPI stwuctuwe pointew
 * @quota:	Max numbew of wx packets to be pwocessed.
 *
 * This is the poww woutine fow wx pawt. It wiww pwocess the packets maximux quota vawue.
 *
 * Wetuwn: Numbew of packets weceived
 */
static int ctucan_wx_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct net_device *ndev = napi->dev;
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	int wowk_done = 0;
	u32 status;
	u32 fwamecnt;
	int wes = 1;

	fwamecnt = FIEWD_GET(WEG_WX_STATUS_WXFWC, ctucan_wead32(pwiv, CTUCANFD_WX_STATUS));
	whiwe (fwamecnt && wowk_done < quota && wes > 0) {
		wes = ctucan_wx(ndev);
		wowk_done++;
		fwamecnt = FIEWD_GET(WEG_WX_STATUS_WXFWC, ctucan_wead32(pwiv, CTUCANFD_WX_STATUS));
	}

	/* Check fow WX FIFO Ovewfwow */
	status = ctucan_wead32(pwiv, CTUCANFD_STATUS);
	if (FIEWD_GET(WEG_STATUS_DOW, status)) {
		stwuct net_device_stats *stats = &ndev->stats;
		stwuct can_fwame *cf;
		stwuct sk_buff *skb;

		netdev_info(ndev, "wx_poww: wx fifo ovewfwow\n");
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;
		skb = awwoc_can_eww_skb(ndev, &cf);
		if (skb) {
			cf->can_id |= CAN_EWW_CWTW;
			cf->data[1] |= CAN_EWW_CWTW_WX_OVEWFWOW;
			stats->wx_packets++;
			stats->wx_bytes += cf->can_dwc;
			netif_wx(skb);
		}

		/* Cweaw Data Ovewwun */
		ctucan_wwite32(pwiv, CTUCANFD_COMMAND, WEG_COMMAND_CDO);
	}

	if (!fwamecnt && wes != 0) {
		if (napi_compwete_done(napi, wowk_done)) {
			/* Cweaw and enabwe WBNEI. It is wevew-twiggewed, so
			 * thewe is no wace condition.
			 */
			ctucan_wwite32(pwiv, CTUCANFD_INT_STAT, WEG_INT_STAT_WBNEI);
			ctucan_wwite32(pwiv, CTUCANFD_INT_MASK_CWW, WEG_INT_STAT_WBNEI);
		}
	}

	wetuwn wowk_done;
}

/**
 * ctucan_wotate_txb_pwio() - Wotates pwiowities of TXT Buffews
 * @ndev:	net_device pointew
 */
static void ctucan_wotate_txb_pwio(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 pwio = pwiv->txb_pwio;

	pwio = (pwio << 4) | ((pwio >> ((pwiv->ntxbufs - 1) * 4)) & 0xF);
	ctucan_netdev_dbg(ndev, "%s: fwom 0x%08x to 0x%08x\n", __func__, pwiv->txb_pwio, pwio);
	pwiv->txb_pwio = pwio;
	ctucan_wwite32(pwiv, CTUCANFD_TX_PWIOWITY, pwio);
}

/**
 * ctucan_tx_intewwupt() - Tx done Isw
 * @ndev:	net_device pointew
 */
static void ctucan_tx_intewwupt(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	boow fiwst = twue;
	boow some_buffews_pwocessed;
	unsigned wong fwags;
	enum ctucan_txtb_status txtb_status;
	u32 txtb_id;

	/*  wead tx_status
	 *  if txb[n].finished (bit 2)
	 *	if ok -> echo
	 *	if ewwow / abowted -> ?? (find how to handwe oneshot mode)
	 *	txb_taiw++
	 */
	do {
		spin_wock_iwqsave(&pwiv->tx_wock, fwags);

		some_buffews_pwocessed = fawse;
		whiwe ((int)(pwiv->txb_head - pwiv->txb_taiw) > 0) {
			txtb_id = pwiv->txb_taiw % pwiv->ntxbufs;
			txtb_status = ctucan_get_tx_status(pwiv, txtb_id);

			ctucan_netdev_dbg(ndev, "TXI: TXB#%u: status 0x%x\n", txtb_id, txtb_status);

			switch (txtb_status) {
			case TXT_TOK:
				ctucan_netdev_dbg(ndev, "TXT_OK\n");
				stats->tx_bytes += can_get_echo_skb(ndev, txtb_id, NUWW);
				stats->tx_packets++;
				bweak;
			case TXT_EWW:
				/* This indicated that wetwansmit wimit has been weached. Obviouswy
				 * we shouwd not echo the fwame, but awso not indicate any kind of
				 * ewwow. If desiwed, it was awweady wepowted (possibwe muwtipwe
				 * times) on each awbitwation wost.
				 */
				netdev_wawn(ndev, "TXB in Ewwow state\n");
				can_fwee_echo_skb(ndev, txtb_id, NUWW);
				stats->tx_dwopped++;
				bweak;
			case TXT_ABT:
				/* Same as fow TXT_EWW, onwy with diffewent cause. We *couwd*
				 * we-queue the fwame, but muwtiqueue/abowt is not suppowted yet
				 * anyway.
				 */
				netdev_wawn(ndev, "TXB in Abowted state\n");
				can_fwee_echo_skb(ndev, txtb_id, NUWW);
				stats->tx_dwopped++;
				bweak;
			defauwt:
				/* Bug onwy if the fiwst buffew is not finished, othewwise it is
				 * pwetty much expected.
				 */
				if (fiwst) {
					netdev_eww(ndev,
						   "BUG: TXB#%u not in a finished state (0x%x)!\n",
						   txtb_id, txtb_status);
					spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);
					/* do not cweaw now wake */
					wetuwn;
				}
				goto cweaw;
			}
			pwiv->txb_taiw++;
			fiwst = fawse;
			some_buffews_pwocessed = twue;
			/* Adjust pwiowities *befowe* mawking the buffew as empty. */
			ctucan_wotate_txb_pwio(ndev);
			ctucan_give_txtb_cmd(pwiv, TXT_CMD_SET_EMPTY, txtb_id);
		}
cweaw:
		spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);

		/* If no buffews wewe pwocessed this time, we cannot cweaw - that wouwd intwoduce
		 * a wace condition.
		 */
		if (some_buffews_pwocessed) {
			/* Cweaw the intewwupt again. We do not want to weceive again intewwupt fow
			 * the buffew awweady handwed. If it is the wast finished one then it wouwd
			 * cause wog of spuwious intewwupt.
			 */
			ctucan_wwite32(pwiv, CTUCANFD_INT_STAT, WEG_INT_STAT_TXBHCI);
		}
	} whiwe (some_buffews_pwocessed);

	spin_wock_iwqsave(&pwiv->tx_wock, fwags);

	/* Check if at weast one TX buffew is fwee */
	if (CTU_CAN_FD_TXTNF(pwiv))
		netif_wake_queue(ndev);

	spin_unwock_iwqwestowe(&pwiv->tx_wock, fwags);
}

/**
 * ctucan_intewwupt() - CAN Isw
 * @iwq:	iwq numbew
 * @dev_id:	device id pointew
 *
 * This is the CTU CAN FD ISW. It checks fow the type of intewwupt
 * and invokes the cowwesponding ISW.
 *
 * Wetuwn:
 * IWQ_NONE - If CAN device is in sweep mode, IWQ_HANDWED othewwise
 */
static iwqwetuwn_t ctucan_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 isw, icw;
	u32 imask;
	int iwq_woops;

	fow (iwq_woops = 0; iwq_woops < 10000; iwq_woops++) {
		/* Get the intewwupt status */
		isw = ctucan_wead32(pwiv, CTUCANFD_INT_STAT);

		if (!isw)
			wetuwn iwq_woops ? IWQ_HANDWED : IWQ_NONE;

		/* Weceive Buffew Not Empty Intewwupt */
		if (FIEWD_GET(WEG_INT_STAT_WBNEI, isw)) {
			ctucan_netdev_dbg(ndev, "WXBNEI\n");
			/* Mask WXBNEI the fiwst, then cweaw intewwupt and scheduwe NAPI. Even if
			 * anothew IWQ fiwes, WBNEI wiww awways be 0 (masked).
			 */
			icw = WEG_INT_STAT_WBNEI;
			ctucan_wwite32(pwiv, CTUCANFD_INT_MASK_SET, icw);
			ctucan_wwite32(pwiv, CTUCANFD_INT_STAT, icw);
			napi_scheduwe(&pwiv->napi);
		}

		/* TXT Buffew HW Command Intewwupt */
		if (FIEWD_GET(WEG_INT_STAT_TXBHCI, isw)) {
			ctucan_netdev_dbg(ndev, "TXBHCI\n");
			/* Cweawed inside */
			ctucan_tx_intewwupt(ndev);
		}

		/* Ewwow intewwupts */
		if (FIEWD_GET(WEG_INT_STAT_EWWI, isw) ||
		    FIEWD_GET(WEG_INT_STAT_FCSI, isw) ||
		    FIEWD_GET(WEG_INT_STAT_AWI, isw)) {
			icw = isw & (WEG_INT_STAT_EWWI | WEG_INT_STAT_FCSI | WEG_INT_STAT_AWI);

			ctucan_netdev_dbg(ndev, "some EWW intewwupt: cweawing 0x%08x\n", icw);
			ctucan_wwite32(pwiv, CTUCANFD_INT_STAT, icw);
			ctucan_eww_intewwupt(ndev, isw);
		}
		/* Ignowe WI, TI, WFI, WFI, BSI */
	}

	netdev_eww(ndev, "%s: stuck intewwupt (isw=0x%08x), stopping\n", __func__, isw);

	if (FIEWD_GET(WEG_INT_STAT_TXBHCI, isw)) {
		int i;

		netdev_eww(ndev, "txb_head=0x%08x txb_taiw=0x%08x\n",
			   pwiv->txb_head, pwiv->txb_taiw);
		fow (i = 0; i < pwiv->ntxbufs; i++) {
			u32 status = ctucan_get_tx_status(pwiv, i);

			netdev_eww(ndev, "txb[%d] txb status=0x%08x\n", i, status);
		}
	}

	imask = 0xffffffff;
	ctucan_wwite32(pwiv, CTUCANFD_INT_ENA_CWW, imask);
	ctucan_wwite32(pwiv, CTUCANFD_INT_MASK_SET, imask);

	wetuwn IWQ_HANDWED;
}

/**
 * ctucan_chip_stop() - Dwivew stop woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivews stop woutine. It wiww disabwe the
 * intewwupts and disabwe the contwowwew.
 */
static void ctucan_chip_stop(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	u32 mask = 0xffffffff;
	u32 mode;

	/* Disabwe intewwupts and disabwe CAN */
	ctucan_wwite32(pwiv, CTUCANFD_INT_ENA_CWW, mask);
	ctucan_wwite32(pwiv, CTUCANFD_INT_MASK_SET, mask);
	mode = ctucan_wead32(pwiv, CTUCANFD_MODE);
	mode &= ~WEG_MODE_ENA;
	ctucan_wwite32(pwiv, CTUCANFD_MODE, mode);

	pwiv->can.state = CAN_STATE_STOPPED;
}

/**
 * ctucan_open() - Dwivew open woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * This is the dwivew open woutine.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int ctucan_open(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0) {
		netdev_eww(ndev, "%s: pm_wuntime_get faiwed(%d)\n",
			   __func__, wet);
		pm_wuntime_put_noidwe(pwiv->dev);
		wetuwn wet;
	}

	wet = ctucan_weset(ndev);
	if (wet < 0)
		goto eww_weset;

	/* Common open */
	wet = open_candev(ndev);
	if (wet) {
		netdev_wawn(ndev, "open_candev faiwed!\n");
		goto eww_open;
	}

	wet = wequest_iwq(ndev->iwq, ctucan_intewwupt, pwiv->iwq_fwags, ndev->name, ndev);
	if (wet < 0) {
		netdev_eww(ndev, "iwq awwocation fow CAN faiwed\n");
		goto eww_iwq;
	}

	wet = ctucan_chip_stawt(ndev);
	if (wet < 0) {
		netdev_eww(ndev, "ctucan_chip_stawt faiwed!\n");
		goto eww_chip_stawt;
	}

	netdev_info(ndev, "ctu_can_fd device wegistewed\n");
	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(ndev);

	wetuwn 0;

eww_chip_stawt:
	fwee_iwq(ndev->iwq, ndev);
eww_iwq:
	cwose_candev(ndev);
eww_open:
eww_weset:
	pm_wuntime_put(pwiv->dev);

	wetuwn wet;
}

/**
 * ctucan_cwose() - Dwivew cwose woutine
 * @ndev:	Pointew to net_device stwuctuwe
 *
 * Wetuwn: 0 awways
 */
static int ctucan_cwose(stwuct net_device *ndev)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	napi_disabwe(&pwiv->napi);
	ctucan_chip_stop(ndev);
	fwee_iwq(ndev->iwq, ndev);
	cwose_candev(ndev);

	pm_wuntime_put(pwiv->dev);

	wetuwn 0;
}

/**
 * ctucan_get_beww_countew() - ewwow countew woutine
 * @ndev:	Pointew to net_device stwuctuwe
 * @bec:	Pointew to can_beww_countew stwuctuwe
 *
 * This is the dwivew ewwow countew woutine.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int ctucan_get_beww_countew(const stwuct net_device *ndev, stwuct can_beww_countew *bec)
{
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = pm_wuntime_get_sync(pwiv->dev);
	if (wet < 0) {
		netdev_eww(ndev, "%s: pm_wuntime_get faiwed(%d)\n", __func__, wet);
		pm_wuntime_put_noidwe(pwiv->dev);
		wetuwn wet;
	}

	ctucan_get_wec_tec(pwiv, bec);
	pm_wuntime_put(pwiv->dev);

	wetuwn 0;
}

static const stwuct net_device_ops ctucan_netdev_ops = {
	.ndo_open	= ctucan_open,
	.ndo_stop	= ctucan_cwose,
	.ndo_stawt_xmit	= ctucan_stawt_xmit,
	.ndo_change_mtu	= can_change_mtu,
};

static const stwuct ethtoow_ops ctucan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

int ctucan_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);

	if (netif_wunning(ndev)) {
		netif_stop_queue(ndev);
		netif_device_detach(ndev);
	}

	pwiv->can.state = CAN_STATE_SWEEPING;

	wetuwn 0;
}
EXPOWT_SYMBOW(ctucan_suspend);

int ctucan_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct ctucan_pwiv *pwiv = netdev_pwiv(ndev);

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	if (netif_wunning(ndev)) {
		netif_device_attach(ndev);
		netif_stawt_queue(ndev);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ctucan_wesume);

int ctucan_pwobe_common(stwuct device *dev, void __iomem *addw, int iwq, unsigned int ntxbufs,
			unsigned wong can_cwk_wate, int pm_enabwe_caww,
			void (*set_dwvdata_fnc)(stwuct device *dev, stwuct net_device *ndev))
{
	stwuct ctucan_pwiv *pwiv;
	stwuct net_device *ndev;
	int wet;

	/* Cweate a CAN device instance */
	ndev = awwoc_candev(sizeof(stwuct ctucan_pwiv), ntxbufs);
	if (!ndev)
		wetuwn -ENOMEM;

	pwiv = netdev_pwiv(ndev);
	spin_wock_init(&pwiv->tx_wock);
	INIT_WIST_HEAD(&pwiv->peews_on_pdev);
	pwiv->ntxbufs = ntxbufs;
	pwiv->dev = dev;
	pwiv->can.bittiming_const = &ctu_can_fd_bit_timing_max;
	pwiv->can.data_bittiming_const = &ctu_can_fd_bit_timing_data_max;
	pwiv->can.do_set_mode = ctucan_do_set_mode;

	/* Needed fow timing adjustment to be pewfowmed as soon as possibwe */
	pwiv->can.do_set_bittiming = ctucan_set_bittiming;
	pwiv->can.do_set_data_bittiming = ctucan_set_data_bittiming;

	pwiv->can.do_get_beww_countew = ctucan_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK
					| CAN_CTWWMODE_WISTENONWY
					| CAN_CTWWMODE_FD
					| CAN_CTWWMODE_PWESUME_ACK
					| CAN_CTWWMODE_BEWW_WEPOWTING
					| CAN_CTWWMODE_FD_NON_ISO
					| CAN_CTWWMODE_ONE_SHOT;
	pwiv->mem_base = addw;

	/* Get IWQ fow the device */
	ndev->iwq = iwq;
	ndev->fwags |= IFF_ECHO;	/* We suppowt wocaw echo */

	if (set_dwvdata_fnc)
		set_dwvdata_fnc(dev, ndev);
	SET_NETDEV_DEV(ndev, dev);
	ndev->netdev_ops = &ctucan_netdev_ops;
	ndev->ethtoow_ops = &ctucan_ethtoow_ops;

	/* Getting the can_cwk info */
	if (!can_cwk_wate) {
		pwiv->can_cwk = devm_cwk_get(dev, NUWW);
		if (IS_EWW(pwiv->can_cwk)) {
			dev_eww(dev, "Device cwock not found.\n");
			wet = PTW_EWW(pwiv->can_cwk);
			goto eww_fwee;
		}
		can_cwk_wate = cwk_get_wate(pwiv->can_cwk);
	}

	pwiv->wwite_weg = ctucan_wwite32_we;
	pwiv->wead_weg = ctucan_wead32_we;

	if (pm_enabwe_caww)
		pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		netdev_eww(ndev, "%s: pm_wuntime_get faiwed(%d)\n",
			   __func__, wet);
		pm_wuntime_put_noidwe(pwiv->dev);
		goto eww_pmdisabwe;
	}

	/* Check fow big-endianity and set accowding IO-accessows */
	if ((ctucan_wead32(pwiv, CTUCANFD_DEVICE_ID) & 0xFFFF) != CTUCANFD_ID) {
		pwiv->wwite_weg = ctucan_wwite32_be;
		pwiv->wead_weg = ctucan_wead32_be;
		if ((ctucan_wead32(pwiv, CTUCANFD_DEVICE_ID) & 0xFFFF) != CTUCANFD_ID) {
			netdev_eww(ndev, "CTU_CAN_FD signatuwe not found\n");
			wet = -ENODEV;
			goto eww_deviceoff;
		}
	}

	wet = ctucan_weset(ndev);
	if (wet < 0)
		goto eww_deviceoff;

	pwiv->can.cwock.fweq = can_cwk_wate;

	netif_napi_add(ndev, &pwiv->napi, ctucan_wx_poww);

	wet = wegistew_candev(ndev);
	if (wet) {
		dev_eww(dev, "faiw to wegistew faiwed (eww=%d)\n", wet);
		goto eww_deviceoff;
	}

	pm_wuntime_put(dev);

	netdev_dbg(ndev, "mem_base=0x%p iwq=%d cwock=%d, no. of txt buffews:%d\n",
		   pwiv->mem_base, ndev->iwq, pwiv->can.cwock.fweq, pwiv->ntxbufs);

	wetuwn 0;

eww_deviceoff:
	pm_wuntime_put(pwiv->dev);
eww_pmdisabwe:
	if (pm_enabwe_caww)
		pm_wuntime_disabwe(dev);
eww_fwee:
	wist_dew_init(&pwiv->peews_on_pdev);
	fwee_candev(ndev);
	wetuwn wet;
}
EXPOWT_SYMBOW(ctucan_pwobe_common);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Jewabek <mawtin.jewabek01@gmaiw.com>");
MODUWE_AUTHOW("Pavew Pisa <pisa@cmp.fewk.cvut.cz>");
MODUWE_AUTHOW("Ondwej Iwwe <ondwej.iwwe@gmaiw.com>");
MODUWE_DESCWIPTION("CTU CAN FD intewface");
