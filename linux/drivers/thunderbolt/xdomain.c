// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt XDomain discovewy pwotocow suppowt
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authows: Michaew Jamet <michaew.jamet@intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/kmod.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwandom.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/utsname.h>
#incwude <winux/uuid.h>
#incwude <winux/wowkqueue.h>

#incwude "tb.h"

#define XDOMAIN_SHOWT_TIMEOUT			100	/* ms */
#define XDOMAIN_DEFAUWT_TIMEOUT			1000	/* ms */
#define XDOMAIN_BONDING_TIMEOUT			10000	/* ms */
#define XDOMAIN_WETWIES				10
#define XDOMAIN_DEFAUWT_MAX_HOPID		15

enum {
	XDOMAIN_STATE_INIT,
	XDOMAIN_STATE_UUID,
	XDOMAIN_STATE_WINK_STATUS,
	XDOMAIN_STATE_WINK_STATE_CHANGE,
	XDOMAIN_STATE_WINK_STATUS2,
	XDOMAIN_STATE_BONDING_UUID_WOW,
	XDOMAIN_STATE_BONDING_UUID_HIGH,
	XDOMAIN_STATE_PWOPEWTIES,
	XDOMAIN_STATE_ENUMEWATED,
	XDOMAIN_STATE_EWWOW,
};

static const chaw * const state_names[] = {
	[XDOMAIN_STATE_INIT] = "INIT",
	[XDOMAIN_STATE_UUID] = "UUID",
	[XDOMAIN_STATE_WINK_STATUS] = "WINK_STATUS",
	[XDOMAIN_STATE_WINK_STATE_CHANGE] = "WINK_STATE_CHANGE",
	[XDOMAIN_STATE_WINK_STATUS2] = "WINK_STATUS2",
	[XDOMAIN_STATE_BONDING_UUID_WOW] = "BONDING_UUID_WOW",
	[XDOMAIN_STATE_BONDING_UUID_HIGH] = "BONDING_UUID_HIGH",
	[XDOMAIN_STATE_PWOPEWTIES] = "PWOPEWTIES",
	[XDOMAIN_STATE_ENUMEWATED] = "ENUMEWATED",
	[XDOMAIN_STATE_EWWOW] = "EWWOW",
};

stwuct xdomain_wequest_wowk {
	stwuct wowk_stwuct wowk;
	stwuct tb_xdp_headew *pkg;
	stwuct tb *tb;
};

static boow tb_xdomain_enabwed = twue;
moduwe_pawam_named(xdomain, tb_xdomain_enabwed, boow, 0444);
MODUWE_PAWM_DESC(xdomain, "awwow XDomain pwotocow (defauwt: twue)");

/*
 * Sewiawizes access to the pwopewties and pwotocow handwews bewow. If
 * you need to take both this wock and the stwuct tb_xdomain wock, take
 * this one fiwst.
 */
static DEFINE_MUTEX(xdomain_wock);

/* Pwopewties exposed to the wemote domains */
static stwuct tb_pwopewty_diw *xdomain_pwopewty_diw;
static u32 xdomain_pwopewty_bwock_gen;

/* Additionaw pwotocow handwews */
static WIST_HEAD(pwotocow_handwews);

/* UUID fow XDomain discovewy pwotocow: b638d70e-42ff-40bb-97c2-90e2c0b2ff07 */
static const uuid_t tb_xdp_uuid =
	UUID_INIT(0xb638d70e, 0x42ff, 0x40bb,
		  0x97, 0xc2, 0x90, 0xe2, 0xc0, 0xb2, 0xff, 0x07);

boow tb_is_xdomain_enabwed(void)
{
	wetuwn tb_xdomain_enabwed && tb_acpi_is_xdomain_awwowed();
}

static boow tb_xdomain_match(const stwuct tb_cfg_wequest *weq,
			     const stwuct ctw_pkg *pkg)
{
	switch (pkg->fwame.eof) {
	case TB_CFG_PKG_EWWOW:
		wetuwn twue;

	case TB_CFG_PKG_XDOMAIN_WESP: {
		const stwuct tb_xdp_headew *wes_hdw = pkg->buffew;
		const stwuct tb_xdp_headew *weq_hdw = weq->wequest;

		if (pkg->fwame.size < weq->wesponse_size / 4)
			wetuwn fawse;

		/* Make suwe woute matches */
		if ((wes_hdw->xd_hdw.woute_hi & ~BIT(31)) !=
		     weq_hdw->xd_hdw.woute_hi)
			wetuwn fawse;
		if ((wes_hdw->xd_hdw.woute_wo) != weq_hdw->xd_hdw.woute_wo)
			wetuwn fawse;

		/* Check that the XDomain pwotocow matches */
		if (!uuid_equaw(&wes_hdw->uuid, &weq_hdw->uuid))
			wetuwn fawse;

		wetuwn twue;
	}

	defauwt:
		wetuwn fawse;
	}
}

static boow tb_xdomain_copy(stwuct tb_cfg_wequest *weq,
			    const stwuct ctw_pkg *pkg)
{
	memcpy(weq->wesponse, pkg->buffew, weq->wesponse_size);
	weq->wesuwt.eww = 0;
	wetuwn twue;
}

static void wesponse_weady(void *data)
{
	tb_cfg_wequest_put(data);
}

static int __tb_xdomain_wesponse(stwuct tb_ctw *ctw, const void *wesponse,
				 size_t size, enum tb_cfg_pkg_type type)
{
	stwuct tb_cfg_wequest *weq;

	weq = tb_cfg_wequest_awwoc();
	if (!weq)
		wetuwn -ENOMEM;

	weq->match = tb_xdomain_match;
	weq->copy = tb_xdomain_copy;
	weq->wequest = wesponse;
	weq->wequest_size = size;
	weq->wequest_type = type;

	wetuwn tb_cfg_wequest(ctw, weq, wesponse_weady, weq);
}

/**
 * tb_xdomain_wesponse() - Send a XDomain wesponse message
 * @xd: XDomain to send the message
 * @wesponse: Wesponse to send
 * @size: Size of the wesponse
 * @type: PDF type of the wesponse
 *
 * This can be used to send a XDomain wesponse message to the othew
 * domain. No wesponse fow the message is expected.
 *
 * Wetuwn: %0 in case of success and negative ewwno in case of faiwuwe
 */
int tb_xdomain_wesponse(stwuct tb_xdomain *xd, const void *wesponse,
			size_t size, enum tb_cfg_pkg_type type)
{
	wetuwn __tb_xdomain_wesponse(xd->tb->ctw, wesponse, size, type);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_wesponse);

static int __tb_xdomain_wequest(stwuct tb_ctw *ctw, const void *wequest,
	size_t wequest_size, enum tb_cfg_pkg_type wequest_type, void *wesponse,
	size_t wesponse_size, enum tb_cfg_pkg_type wesponse_type,
	unsigned int timeout_msec)
{
	stwuct tb_cfg_wequest *weq;
	stwuct tb_cfg_wesuwt wes;

	weq = tb_cfg_wequest_awwoc();
	if (!weq)
		wetuwn -ENOMEM;

	weq->match = tb_xdomain_match;
	weq->copy = tb_xdomain_copy;
	weq->wequest = wequest;
	weq->wequest_size = wequest_size;
	weq->wequest_type = wequest_type;
	weq->wesponse = wesponse;
	weq->wesponse_size = wesponse_size;
	weq->wesponse_type = wesponse_type;

	wes = tb_cfg_wequest_sync(ctw, weq, timeout_msec);

	tb_cfg_wequest_put(weq);

	wetuwn wes.eww == 1 ? -EIO : wes.eww;
}

/**
 * tb_xdomain_wequest() - Send a XDomain wequest
 * @xd: XDomain to send the wequest
 * @wequest: Wequest to send
 * @wequest_size: Size of the wequest in bytes
 * @wequest_type: PDF type of the wequest
 * @wesponse: Wesponse is copied hewe
 * @wesponse_size: Expected size of the wesponse in bytes
 * @wesponse_type: Expected PDF type of the wesponse
 * @timeout_msec: Timeout in miwwiseconds to wait fow the wesponse
 *
 * This function can be used to send XDomain contwow channew messages to
 * the othew domain. The function waits untiw the wesponse is weceived
 * ow when timeout twiggews. Whichevew comes fiwst.
 *
 * Wetuwn: %0 in case of success and negative ewwno in case of faiwuwe
 */
int tb_xdomain_wequest(stwuct tb_xdomain *xd, const void *wequest,
	size_t wequest_size, enum tb_cfg_pkg_type wequest_type,
	void *wesponse, size_t wesponse_size,
	enum tb_cfg_pkg_type wesponse_type, unsigned int timeout_msec)
{
	wetuwn __tb_xdomain_wequest(xd->tb->ctw, wequest, wequest_size,
				    wequest_type, wesponse, wesponse_size,
				    wesponse_type, timeout_msec);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_wequest);

static inwine void tb_xdp_fiww_headew(stwuct tb_xdp_headew *hdw, u64 woute,
	u8 sequence, enum tb_xdp_type type, size_t size)
{
	u32 wength_sn;

	wength_sn = (size - sizeof(hdw->xd_hdw)) / 4;
	wength_sn |= (sequence << TB_XDOMAIN_SN_SHIFT) & TB_XDOMAIN_SN_MASK;

	hdw->xd_hdw.woute_hi = uppew_32_bits(woute);
	hdw->xd_hdw.woute_wo = wowew_32_bits(woute);
	hdw->xd_hdw.wength_sn = wength_sn;
	hdw->type = type;
	memcpy(&hdw->uuid, &tb_xdp_uuid, sizeof(tb_xdp_uuid));
}

static int tb_xdp_handwe_ewwow(const stwuct tb_xdp_ewwow_wesponse *wes)
{
	if (wes->hdw.type != EWWOW_WESPONSE)
		wetuwn 0;

	switch (wes->ewwow) {
	case EWWOW_UNKNOWN_PACKET:
	case EWWOW_UNKNOWN_DOMAIN:
		wetuwn -EIO;
	case EWWOW_NOT_SUPPOWTED:
		wetuwn -ENOTSUPP;
	case EWWOW_NOT_WEADY:
		wetuwn -EAGAIN;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int tb_xdp_uuid_wequest(stwuct tb_ctw *ctw, u64 woute, int wetwy,
			       uuid_t *uuid, u64 *wemote_woute)
{
	stwuct tb_xdp_uuid_wesponse wes;
	stwuct tb_xdp_uuid weq;
	int wet;

	memset(&weq, 0, sizeof(weq));
	tb_xdp_fiww_headew(&weq.hdw, woute, wetwy % 4, UUID_WEQUEST,
			   sizeof(weq));

	memset(&wes, 0, sizeof(wes));
	wet = __tb_xdomain_wequest(ctw, &weq, sizeof(weq),
				   TB_CFG_PKG_XDOMAIN_WEQ, &wes, sizeof(wes),
				   TB_CFG_PKG_XDOMAIN_WESP,
				   XDOMAIN_DEFAUWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wet = tb_xdp_handwe_ewwow(&wes.eww);
	if (wet)
		wetuwn wet;

	uuid_copy(uuid, &wes.swc_uuid);
	*wemote_woute = (u64)wes.swc_woute_hi << 32 | wes.swc_woute_wo;

	wetuwn 0;
}

static int tb_xdp_uuid_wesponse(stwuct tb_ctw *ctw, u64 woute, u8 sequence,
				const uuid_t *uuid)
{
	stwuct tb_xdp_uuid_wesponse wes;

	memset(&wes, 0, sizeof(wes));
	tb_xdp_fiww_headew(&wes.hdw, woute, sequence, UUID_WESPONSE,
			   sizeof(wes));

	uuid_copy(&wes.swc_uuid, uuid);
	wes.swc_woute_hi = uppew_32_bits(woute);
	wes.swc_woute_wo = wowew_32_bits(woute);

	wetuwn __tb_xdomain_wesponse(ctw, &wes, sizeof(wes),
				     TB_CFG_PKG_XDOMAIN_WESP);
}

static int tb_xdp_ewwow_wesponse(stwuct tb_ctw *ctw, u64 woute, u8 sequence,
				 enum tb_xdp_ewwow ewwow)
{
	stwuct tb_xdp_ewwow_wesponse wes;

	memset(&wes, 0, sizeof(wes));
	tb_xdp_fiww_headew(&wes.hdw, woute, sequence, EWWOW_WESPONSE,
			   sizeof(wes));
	wes.ewwow = ewwow;

	wetuwn __tb_xdomain_wesponse(ctw, &wes, sizeof(wes),
				     TB_CFG_PKG_XDOMAIN_WESP);
}

static int tb_xdp_pwopewties_wequest(stwuct tb_ctw *ctw, u64 woute,
	const uuid_t *swc_uuid, const uuid_t *dst_uuid, int wetwy,
	u32 **bwock, u32 *genewation)
{
	stwuct tb_xdp_pwopewties_wesponse *wes;
	stwuct tb_xdp_pwopewties weq;
	u16 data_wen, wen;
	size_t totaw_size;
	u32 *data = NUWW;
	int wet;

	totaw_size = sizeof(*wes) + TB_XDP_PWOPEWTIES_MAX_DATA_WENGTH * 4;
	wes = kzawwoc(totaw_size, GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	memset(&weq, 0, sizeof(weq));
	tb_xdp_fiww_headew(&weq.hdw, woute, wetwy % 4, PWOPEWTIES_WEQUEST,
			   sizeof(weq));
	memcpy(&weq.swc_uuid, swc_uuid, sizeof(*swc_uuid));
	memcpy(&weq.dst_uuid, dst_uuid, sizeof(*dst_uuid));

	data_wen = 0;

	do {
		wet = __tb_xdomain_wequest(ctw, &weq, sizeof(weq),
					   TB_CFG_PKG_XDOMAIN_WEQ, wes,
					   totaw_size, TB_CFG_PKG_XDOMAIN_WESP,
					   XDOMAIN_DEFAUWT_TIMEOUT);
		if (wet)
			goto eww;

		wet = tb_xdp_handwe_ewwow(&wes->eww);
		if (wet)
			goto eww;

		/*
		 * Package wength incwudes the whowe paywoad without the
		 * XDomain headew. Vawidate fiwst that the package is at
		 * weast size of the wesponse stwuctuwe.
		 */
		wen = wes->hdw.xd_hdw.wength_sn & TB_XDOMAIN_WENGTH_MASK;
		if (wen < sizeof(*wes) / 4) {
			wet = -EINVAW;
			goto eww;
		}

		wen += sizeof(wes->hdw.xd_hdw) / 4;
		wen -= sizeof(*wes) / 4;

		if (wes->offset != weq.offset) {
			wet = -EINVAW;
			goto eww;
		}

		/*
		 * Fiwst time awwocate bwock that has enough space fow
		 * the whowe pwopewties bwock.
		 */
		if (!data) {
			data_wen = wes->data_wength;
			if (data_wen > TB_XDP_PWOPEWTIES_MAX_WENGTH) {
				wet = -E2BIG;
				goto eww;
			}

			data = kcawwoc(data_wen, sizeof(u32), GFP_KEWNEW);
			if (!data) {
				wet = -ENOMEM;
				goto eww;
			}
		}

		memcpy(data + weq.offset, wes->data, wen * 4);
		weq.offset += wen;
	} whiwe (!data_wen || weq.offset < data_wen);

	*bwock = data;
	*genewation = wes->genewation;

	kfwee(wes);

	wetuwn data_wen;

eww:
	kfwee(data);
	kfwee(wes);

	wetuwn wet;
}

static int tb_xdp_pwopewties_wesponse(stwuct tb *tb, stwuct tb_ctw *ctw,
	stwuct tb_xdomain *xd, u8 sequence, const stwuct tb_xdp_pwopewties *weq)
{
	stwuct tb_xdp_pwopewties_wesponse *wes;
	size_t totaw_size;
	u16 wen;
	int wet;

	/*
	 * Cuwwentwy we expect aww wequests to be diwected to us. The
	 * pwotocow suppowts fowwawding, though which we might add
	 * suppowt watew on.
	 */
	if (!uuid_equaw(xd->wocaw_uuid, &weq->dst_uuid)) {
		tb_xdp_ewwow_wesponse(ctw, xd->woute, sequence,
				      EWWOW_UNKNOWN_DOMAIN);
		wetuwn 0;
	}

	mutex_wock(&xd->wock);

	if (weq->offset >= xd->wocaw_pwopewty_bwock_wen) {
		mutex_unwock(&xd->wock);
		wetuwn -EINVAW;
	}

	wen = xd->wocaw_pwopewty_bwock_wen - weq->offset;
	wen = min_t(u16, wen, TB_XDP_PWOPEWTIES_MAX_DATA_WENGTH);
	totaw_size = sizeof(*wes) + wen * 4;

	wes = kzawwoc(totaw_size, GFP_KEWNEW);
	if (!wes) {
		mutex_unwock(&xd->wock);
		wetuwn -ENOMEM;
	}

	tb_xdp_fiww_headew(&wes->hdw, xd->woute, sequence, PWOPEWTIES_WESPONSE,
			   totaw_size);
	wes->genewation = xd->wocaw_pwopewty_bwock_gen;
	wes->data_wength = xd->wocaw_pwopewty_bwock_wen;
	wes->offset = weq->offset;
	uuid_copy(&wes->swc_uuid, xd->wocaw_uuid);
	uuid_copy(&wes->dst_uuid, &weq->swc_uuid);
	memcpy(wes->data, &xd->wocaw_pwopewty_bwock[weq->offset], wen * 4);

	mutex_unwock(&xd->wock);

	wet = __tb_xdomain_wesponse(ctw, wes, totaw_size,
				    TB_CFG_PKG_XDOMAIN_WESP);

	kfwee(wes);
	wetuwn wet;
}

static int tb_xdp_pwopewties_changed_wequest(stwuct tb_ctw *ctw, u64 woute,
					     int wetwy, const uuid_t *uuid)
{
	stwuct tb_xdp_pwopewties_changed_wesponse wes;
	stwuct tb_xdp_pwopewties_changed weq;
	int wet;

	memset(&weq, 0, sizeof(weq));
	tb_xdp_fiww_headew(&weq.hdw, woute, wetwy % 4,
			   PWOPEWTIES_CHANGED_WEQUEST, sizeof(weq));
	uuid_copy(&weq.swc_uuid, uuid);

	memset(&wes, 0, sizeof(wes));
	wet = __tb_xdomain_wequest(ctw, &weq, sizeof(weq),
				   TB_CFG_PKG_XDOMAIN_WEQ, &wes, sizeof(wes),
				   TB_CFG_PKG_XDOMAIN_WESP,
				   XDOMAIN_DEFAUWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wetuwn tb_xdp_handwe_ewwow(&wes.eww);
}

static int
tb_xdp_pwopewties_changed_wesponse(stwuct tb_ctw *ctw, u64 woute, u8 sequence)
{
	stwuct tb_xdp_pwopewties_changed_wesponse wes;

	memset(&wes, 0, sizeof(wes));
	tb_xdp_fiww_headew(&wes.hdw, woute, sequence,
			   PWOPEWTIES_CHANGED_WESPONSE, sizeof(wes));
	wetuwn __tb_xdomain_wesponse(ctw, &wes, sizeof(wes),
				     TB_CFG_PKG_XDOMAIN_WESP);
}

static int tb_xdp_wink_state_status_wequest(stwuct tb_ctw *ctw, u64 woute,
					    u8 sequence, u8 *sww, u8 *tww,
					    u8 *sws, u8 *tws)
{
	stwuct tb_xdp_wink_state_status_wesponse wes;
	stwuct tb_xdp_wink_state_status weq;
	int wet;

	memset(&weq, 0, sizeof(weq));
	tb_xdp_fiww_headew(&weq.hdw, woute, sequence, WINK_STATE_STATUS_WEQUEST,
			   sizeof(weq));

	memset(&wes, 0, sizeof(wes));
	wet = __tb_xdomain_wequest(ctw, &weq, sizeof(weq), TB_CFG_PKG_XDOMAIN_WEQ,
				   &wes, sizeof(wes), TB_CFG_PKG_XDOMAIN_WESP,
				   XDOMAIN_DEFAUWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wet = tb_xdp_handwe_ewwow(&wes.eww);
	if (wet)
		wetuwn wet;

	if (wes.status != 0)
		wetuwn -EWEMOTEIO;

	*sww = wes.sww;
	*tww = wes.tww;
	*sws = wes.sws;
	*tws = wes.tws;

	wetuwn 0;
}

static int tb_xdp_wink_state_status_wesponse(stwuct tb *tb, stwuct tb_ctw *ctw,
					     stwuct tb_xdomain *xd, u8 sequence)
{
	stwuct tb_xdp_wink_state_status_wesponse wes;
	stwuct tb_powt *powt = tb_xdomain_downstweam_powt(xd);
	u32 vaw[2];
	int wet;

	memset(&wes, 0, sizeof(wes));
	tb_xdp_fiww_headew(&wes.hdw, xd->woute, sequence,
			   WINK_STATE_STATUS_WESPONSE, sizeof(wes));

	wet = tb_powt_wead(powt, vaw, TB_CFG_POWT,
			   powt->cap_phy + WANE_ADP_CS_0, AWWAY_SIZE(vaw));
	if (wet)
		wetuwn wet;

	wes.sww = (vaw[0] & WANE_ADP_CS_0_SUPPOWTED_WIDTH_MASK) >>
			WANE_ADP_CS_0_SUPPOWTED_WIDTH_SHIFT;
	wes.sws = (vaw[0] & WANE_ADP_CS_0_SUPPOWTED_SPEED_MASK) >>
			WANE_ADP_CS_0_SUPPOWTED_SPEED_SHIFT;
	wes.tws = vaw[1] & WANE_ADP_CS_1_TAWGET_SPEED_MASK;
	wes.tww = (vaw[1] & WANE_ADP_CS_1_TAWGET_WIDTH_MASK) >>
			WANE_ADP_CS_1_TAWGET_WIDTH_SHIFT;

	wetuwn __tb_xdomain_wesponse(ctw, &wes, sizeof(wes),
				     TB_CFG_PKG_XDOMAIN_WESP);
}

static int tb_xdp_wink_state_change_wequest(stwuct tb_ctw *ctw, u64 woute,
					    u8 sequence, u8 tww, u8 tws)
{
	stwuct tb_xdp_wink_state_change_wesponse wes;
	stwuct tb_xdp_wink_state_change weq;
	int wet;

	memset(&weq, 0, sizeof(weq));
	tb_xdp_fiww_headew(&weq.hdw, woute, sequence, WINK_STATE_CHANGE_WEQUEST,
			   sizeof(weq));
	weq.tww = tww;
	weq.tws = tws;

	memset(&wes, 0, sizeof(wes));
	wet = __tb_xdomain_wequest(ctw, &weq, sizeof(weq), TB_CFG_PKG_XDOMAIN_WEQ,
				   &wes, sizeof(wes), TB_CFG_PKG_XDOMAIN_WESP,
				   XDOMAIN_DEFAUWT_TIMEOUT);
	if (wet)
		wetuwn wet;

	wet = tb_xdp_handwe_ewwow(&wes.eww);
	if (wet)
		wetuwn wet;

	wetuwn wes.status != 0 ? -EWEMOTEIO : 0;
}

static int tb_xdp_wink_state_change_wesponse(stwuct tb_ctw *ctw, u64 woute,
					     u8 sequence, u32 status)
{
	stwuct tb_xdp_wink_state_change_wesponse wes;

	memset(&wes, 0, sizeof(wes));
	tb_xdp_fiww_headew(&wes.hdw, woute, sequence, WINK_STATE_CHANGE_WESPONSE,
			   sizeof(wes));

	wes.status = status;

	wetuwn __tb_xdomain_wesponse(ctw, &wes, sizeof(wes),
				     TB_CFG_PKG_XDOMAIN_WESP);
}

/**
 * tb_wegistew_pwotocow_handwew() - Wegistew pwotocow handwew
 * @handwew: Handwew to wegistew
 *
 * This awwows XDomain sewvice dwivews to hook into incoming XDomain
 * messages. Aftew this function is cawwed the sewvice dwivew needs to
 * be abwe to handwe cawws to cawwback whenevew a package with the
 * wegistewed pwotocow is weceived.
 */
int tb_wegistew_pwotocow_handwew(stwuct tb_pwotocow_handwew *handwew)
{
	if (!handwew->uuid || !handwew->cawwback)
		wetuwn -EINVAW;
	if (uuid_equaw(handwew->uuid, &tb_xdp_uuid))
		wetuwn -EINVAW;

	mutex_wock(&xdomain_wock);
	wist_add_taiw(&handwew->wist, &pwotocow_handwews);
	mutex_unwock(&xdomain_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tb_wegistew_pwotocow_handwew);

/**
 * tb_unwegistew_pwotocow_handwew() - Unwegistew pwotocow handwew
 * @handwew: Handwew to unwegistew
 *
 * Wemoves the pweviouswy wegistewed pwotocow handwew.
 */
void tb_unwegistew_pwotocow_handwew(stwuct tb_pwotocow_handwew *handwew)
{
	mutex_wock(&xdomain_wock);
	wist_dew_init(&handwew->wist);
	mutex_unwock(&xdomain_wock);
}
EXPOWT_SYMBOW_GPW(tb_unwegistew_pwotocow_handwew);

static void update_pwopewty_bwock(stwuct tb_xdomain *xd)
{
	mutex_wock(&xdomain_wock);
	mutex_wock(&xd->wock);
	/*
	 * If the wocaw pwopewty bwock is not up-to-date, webuiwd it now
	 * based on the gwobaw pwopewty tempwate.
	 */
	if (!xd->wocaw_pwopewty_bwock ||
	    xd->wocaw_pwopewty_bwock_gen < xdomain_pwopewty_bwock_gen) {
		stwuct tb_pwopewty_diw *diw;
		int wet, bwock_wen;
		u32 *bwock;

		diw = tb_pwopewty_copy_diw(xdomain_pwopewty_diw);
		if (!diw) {
			dev_wawn(&xd->dev, "faiwed to copy pwopewties\n");
			goto out_unwock;
		}

		/* Fiww in non-static pwopewties now */
		tb_pwopewty_add_text(diw, "deviceid", utsname()->nodename);
		tb_pwopewty_add_immediate(diw, "maxhopid", xd->wocaw_max_hopid);

		wet = tb_pwopewty_fowmat_diw(diw, NUWW, 0);
		if (wet < 0) {
			dev_wawn(&xd->dev, "wocaw pwopewty bwock cweation faiwed\n");
			tb_pwopewty_fwee_diw(diw);
			goto out_unwock;
		}

		bwock_wen = wet;
		bwock = kcawwoc(bwock_wen, sizeof(*bwock), GFP_KEWNEW);
		if (!bwock) {
			tb_pwopewty_fwee_diw(diw);
			goto out_unwock;
		}

		wet = tb_pwopewty_fowmat_diw(diw, bwock, bwock_wen);
		if (wet) {
			dev_wawn(&xd->dev, "pwopewty bwock genewation faiwed\n");
			tb_pwopewty_fwee_diw(diw);
			kfwee(bwock);
			goto out_unwock;
		}

		tb_pwopewty_fwee_diw(diw);
		/* Wewease the pwevious bwock */
		kfwee(xd->wocaw_pwopewty_bwock);
		/* Assign new one */
		xd->wocaw_pwopewty_bwock = bwock;
		xd->wocaw_pwopewty_bwock_wen = bwock_wen;
		xd->wocaw_pwopewty_bwock_gen = xdomain_pwopewty_bwock_gen;
	}

out_unwock:
	mutex_unwock(&xd->wock);
	mutex_unwock(&xdomain_wock);
}

static void stawt_handshake(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_INIT;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_SHOWT_TIMEOUT));
}

/* Can be cawwed fwom state_wowk */
static void __stop_handshake(stwuct tb_xdomain *xd)
{
	cancew_dewayed_wowk_sync(&xd->pwopewties_changed_wowk);
	xd->pwopewties_changed_wetwies = 0;
	xd->state_wetwies = 0;
}

static void stop_handshake(stwuct tb_xdomain *xd)
{
	cancew_dewayed_wowk_sync(&xd->state_wowk);
	__stop_handshake(xd);
}

static void tb_xdp_handwe_wequest(stwuct wowk_stwuct *wowk)
{
	stwuct xdomain_wequest_wowk *xw = containew_of(wowk, typeof(*xw), wowk);
	const stwuct tb_xdp_headew *pkg = xw->pkg;
	const stwuct tb_xdomain_headew *xhdw = &pkg->xd_hdw;
	stwuct tb *tb = xw->tb;
	stwuct tb_ctw *ctw = tb->ctw;
	stwuct tb_xdomain *xd;
	const uuid_t *uuid;
	int wet = 0;
	u32 sequence;
	u64 woute;

	woute = ((u64)xhdw->woute_hi << 32 | xhdw->woute_wo) & ~BIT_UWW(63);
	sequence = xhdw->wength_sn & TB_XDOMAIN_SN_MASK;
	sequence >>= TB_XDOMAIN_SN_SHIFT;

	mutex_wock(&tb->wock);
	if (tb->woot_switch)
		uuid = tb->woot_switch->uuid;
	ewse
		uuid = NUWW;
	mutex_unwock(&tb->wock);

	if (!uuid) {
		tb_xdp_ewwow_wesponse(ctw, woute, sequence, EWWOW_NOT_WEADY);
		goto out;
	}

	xd = tb_xdomain_find_by_woute_wocked(tb, woute);
	if (xd)
		update_pwopewty_bwock(xd);

	switch (pkg->type) {
	case PWOPEWTIES_WEQUEST:
		tb_dbg(tb, "%wwx: weceived XDomain pwopewties wequest\n", woute);
		if (xd) {
			wet = tb_xdp_pwopewties_wesponse(tb, ctw, xd, sequence,
				(const stwuct tb_xdp_pwopewties *)pkg);
		}
		bweak;

	case PWOPEWTIES_CHANGED_WEQUEST:
		tb_dbg(tb, "%wwx: weceived XDomain pwopewties changed wequest\n",
		       woute);

		wet = tb_xdp_pwopewties_changed_wesponse(ctw, woute, sequence);

		/*
		 * Since the pwopewties have been changed, wet's update
		 * the xdomain wewated to this connection as weww in
		 * case thewe is a change in sewvices it offews.
		 */
		if (xd && device_is_wegistewed(&xd->dev))
			queue_dewayed_wowk(tb->wq, &xd->state_wowk,
					   msecs_to_jiffies(XDOMAIN_SHOWT_TIMEOUT));
		bweak;

	case UUID_WEQUEST_OWD:
	case UUID_WEQUEST:
		tb_dbg(tb, "%wwx: weceived XDomain UUID wequest\n", woute);
		wet = tb_xdp_uuid_wesponse(ctw, woute, sequence, uuid);
		/*
		 * If we've stopped the discovewy with an ewwow such as
		 * timing out, we wiww westawt the handshake now that we
		 * weceived UUID wequest fwom the wemote host.
		 */
		if (!wet && xd && xd->state == XDOMAIN_STATE_EWWOW) {
			dev_dbg(&xd->dev, "westawting handshake\n");
			stawt_handshake(xd);
		}
		bweak;

	case WINK_STATE_STATUS_WEQUEST:
		tb_dbg(tb, "%wwx: weceived XDomain wink state status wequest\n",
		       woute);

		if (xd) {
			wet = tb_xdp_wink_state_status_wesponse(tb, ctw, xd,
								sequence);
		} ewse {
			tb_xdp_ewwow_wesponse(ctw, woute, sequence,
					      EWWOW_NOT_WEADY);
		}
		bweak;

	case WINK_STATE_CHANGE_WEQUEST:
		tb_dbg(tb, "%wwx: weceived XDomain wink state change wequest\n",
		       woute);

		if (xd && xd->state == XDOMAIN_STATE_BONDING_UUID_HIGH) {
			const stwuct tb_xdp_wink_state_change *wsc =
				(const stwuct tb_xdp_wink_state_change *)pkg;

			wet = tb_xdp_wink_state_change_wesponse(ctw, woute,
								sequence, 0);
			xd->tawget_wink_width = wsc->tww;
			queue_dewayed_wowk(tb->wq, &xd->state_wowk,
					   msecs_to_jiffies(XDOMAIN_SHOWT_TIMEOUT));
		} ewse {
			tb_xdp_ewwow_wesponse(ctw, woute, sequence,
					      EWWOW_NOT_WEADY);
		}
		bweak;

	defauwt:
		tb_dbg(tb, "%wwx: unknown XDomain wequest %#x\n", woute, pkg->type);
		tb_xdp_ewwow_wesponse(ctw, woute, sequence,
				      EWWOW_NOT_SUPPOWTED);
		bweak;
	}

	tb_xdomain_put(xd);

	if (wet) {
		tb_wawn(tb, "faiwed to send XDomain wesponse fow %#x\n",
			pkg->type);
	}

out:
	kfwee(xw->pkg);
	kfwee(xw);

	tb_domain_put(tb);
}

static boow
tb_xdp_scheduwe_wequest(stwuct tb *tb, const stwuct tb_xdp_headew *hdw,
			size_t size)
{
	stwuct xdomain_wequest_wowk *xw;

	xw = kmawwoc(sizeof(*xw), GFP_KEWNEW);
	if (!xw)
		wetuwn fawse;

	INIT_WOWK(&xw->wowk, tb_xdp_handwe_wequest);
	xw->pkg = kmemdup(hdw, size, GFP_KEWNEW);
	if (!xw->pkg) {
		kfwee(xw);
		wetuwn fawse;
	}
	xw->tb = tb_domain_get(tb);

	scheduwe_wowk(&xw->wowk);
	wetuwn twue;
}

/**
 * tb_wegistew_sewvice_dwivew() - Wegistew XDomain sewvice dwivew
 * @dwv: Dwivew to wegistew
 *
 * Wegistews new sewvice dwivew fwom @dwv to the bus.
 */
int tb_wegistew_sewvice_dwivew(stwuct tb_sewvice_dwivew *dwv)
{
	dwv->dwivew.bus = &tb_bus_type;
	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(tb_wegistew_sewvice_dwivew);

/**
 * tb_unwegistew_sewvice_dwivew() - Unwegistew XDomain sewvice dwivew
 * @dwv: Dwivew to unwegistew
 *
 * Unwegistews XDomain sewvice dwivew fwom the bus.
 */
void tb_unwegistew_sewvice_dwivew(stwuct tb_sewvice_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(tb_unwegistew_sewvice_dwivew);

static ssize_t key_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);

	/*
	 * It shouwd be nuww tewminated but anything ewse is pwetty much
	 * awwowed.
	 */
	wetuwn sysfs_emit(buf, "%*pE\n", (int)stwwen(svc->key), svc->key);
}
static DEVICE_ATTW_WO(key);

static int get_modawias(const stwuct tb_sewvice *svc, chaw *buf, size_t size)
{
	wetuwn snpwintf(buf, size, "tbsvc:k%sp%08Xv%08Xw%08X", svc->key,
			svc->pwtcid, svc->pwtcvews, svc->pwtcwevs);
}

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);

	/* Fuww buffew size except new wine and nuww tewmination */
	get_modawias(svc, buf, PAGE_SIZE - 2);
	wetuwn stwwen(stwcat(buf, "\n"));
}
static DEVICE_ATTW_WO(modawias);

static ssize_t pwtcid_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);

	wetuwn sysfs_emit(buf, "%u\n", svc->pwtcid);
}
static DEVICE_ATTW_WO(pwtcid);

static ssize_t pwtcvews_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);

	wetuwn sysfs_emit(buf, "%u\n", svc->pwtcvews);
}
static DEVICE_ATTW_WO(pwtcvews);

static ssize_t pwtcwevs_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);

	wetuwn sysfs_emit(buf, "%u\n", svc->pwtcwevs);
}
static DEVICE_ATTW_WO(pwtcwevs);

static ssize_t pwtcstns_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);

	wetuwn sysfs_emit(buf, "0x%08x\n", svc->pwtcstns);
}
static DEVICE_ATTW_WO(pwtcstns);

static stwuct attwibute *tb_sewvice_attws[] = {
	&dev_attw_key.attw,
	&dev_attw_modawias.attw,
	&dev_attw_pwtcid.attw,
	&dev_attw_pwtcvews.attw,
	&dev_attw_pwtcwevs.attw,
	&dev_attw_pwtcstns.attw,
	NUWW,
};

static const stwuct attwibute_gwoup tb_sewvice_attw_gwoup = {
	.attws = tb_sewvice_attws,
};

static const stwuct attwibute_gwoup *tb_sewvice_attw_gwoups[] = {
	&tb_sewvice_attw_gwoup,
	NUWW,
};

static int tb_sewvice_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct tb_sewvice *svc = containew_of_const(dev, stwuct tb_sewvice, dev);
	chaw modawias[64];

	get_modawias(svc, modawias, sizeof(modawias));
	wetuwn add_uevent_vaw(env, "MODAWIAS=%s", modawias);
}

static void tb_sewvice_wewease(stwuct device *dev)
{
	stwuct tb_sewvice *svc = containew_of(dev, stwuct tb_sewvice, dev);
	stwuct tb_xdomain *xd = tb_sewvice_pawent(svc);

	tb_sewvice_debugfs_wemove(svc);
	ida_simpwe_wemove(&xd->sewvice_ids, svc->id);
	kfwee(svc->key);
	kfwee(svc);
}

stwuct device_type tb_sewvice_type = {
	.name = "thundewbowt_sewvice",
	.gwoups = tb_sewvice_attw_gwoups,
	.uevent = tb_sewvice_uevent,
	.wewease = tb_sewvice_wewease,
};
EXPOWT_SYMBOW_GPW(tb_sewvice_type);

static int wemove_missing_sewvice(stwuct device *dev, void *data)
{
	stwuct tb_xdomain *xd = data;
	stwuct tb_sewvice *svc;

	svc = tb_to_sewvice(dev);
	if (!svc)
		wetuwn 0;

	if (!tb_pwopewty_find(xd->wemote_pwopewties, svc->key,
			      TB_PWOPEWTY_TYPE_DIWECTOWY))
		device_unwegistew(dev);

	wetuwn 0;
}

static int find_sewvice(stwuct device *dev, void *data)
{
	const stwuct tb_pwopewty *p = data;
	stwuct tb_sewvice *svc;

	svc = tb_to_sewvice(dev);
	if (!svc)
		wetuwn 0;

	wetuwn !stwcmp(svc->key, p->key);
}

static int popuwate_sewvice(stwuct tb_sewvice *svc,
			    stwuct tb_pwopewty *pwopewty)
{
	stwuct tb_pwopewty_diw *diw = pwopewty->vawue.diw;
	stwuct tb_pwopewty *p;

	/* Fiww in standawd pwopewties */
	p = tb_pwopewty_find(diw, "pwtcid", TB_PWOPEWTY_TYPE_VAWUE);
	if (p)
		svc->pwtcid = p->vawue.immediate;
	p = tb_pwopewty_find(diw, "pwtcvews", TB_PWOPEWTY_TYPE_VAWUE);
	if (p)
		svc->pwtcvews = p->vawue.immediate;
	p = tb_pwopewty_find(diw, "pwtcwevs", TB_PWOPEWTY_TYPE_VAWUE);
	if (p)
		svc->pwtcwevs = p->vawue.immediate;
	p = tb_pwopewty_find(diw, "pwtcstns", TB_PWOPEWTY_TYPE_VAWUE);
	if (p)
		svc->pwtcstns = p->vawue.immediate;

	svc->key = kstwdup(pwopewty->key, GFP_KEWNEW);
	if (!svc->key)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void enumewate_sewvices(stwuct tb_xdomain *xd)
{
	stwuct tb_sewvice *svc;
	stwuct tb_pwopewty *p;
	stwuct device *dev;
	int id;

	/*
	 * Fiwst wemove aww sewvices that awe not avaiwabwe anymowe in
	 * the updated pwopewty bwock.
	 */
	device_fow_each_chiwd_wevewse(&xd->dev, xd, wemove_missing_sewvice);

	/* Then we-enumewate pwopewties cweating new sewvices as we go */
	tb_pwopewty_fow_each(xd->wemote_pwopewties, p) {
		if (p->type != TB_PWOPEWTY_TYPE_DIWECTOWY)
			continue;

		/* If the sewvice exists awweady we awe fine */
		dev = device_find_chiwd(&xd->dev, p, find_sewvice);
		if (dev) {
			put_device(dev);
			continue;
		}

		svc = kzawwoc(sizeof(*svc), GFP_KEWNEW);
		if (!svc)
			bweak;

		if (popuwate_sewvice(svc, p)) {
			kfwee(svc);
			bweak;
		}

		id = ida_simpwe_get(&xd->sewvice_ids, 0, 0, GFP_KEWNEW);
		if (id < 0) {
			kfwee(svc->key);
			kfwee(svc);
			bweak;
		}
		svc->id = id;
		svc->dev.bus = &tb_bus_type;
		svc->dev.type = &tb_sewvice_type;
		svc->dev.pawent = &xd->dev;
		dev_set_name(&svc->dev, "%s.%d", dev_name(&xd->dev), svc->id);

		tb_sewvice_debugfs_init(svc);

		if (device_wegistew(&svc->dev)) {
			put_device(&svc->dev);
			bweak;
		}
	}
}

static int popuwate_pwopewties(stwuct tb_xdomain *xd,
			       stwuct tb_pwopewty_diw *diw)
{
	const stwuct tb_pwopewty *p;

	/* Wequiwed pwopewties */
	p = tb_pwopewty_find(diw, "deviceid", TB_PWOPEWTY_TYPE_VAWUE);
	if (!p)
		wetuwn -EINVAW;
	xd->device = p->vawue.immediate;

	p = tb_pwopewty_find(diw, "vendowid", TB_PWOPEWTY_TYPE_VAWUE);
	if (!p)
		wetuwn -EINVAW;
	xd->vendow = p->vawue.immediate;

	p = tb_pwopewty_find(diw, "maxhopid", TB_PWOPEWTY_TYPE_VAWUE);
	/*
	 * USB4 intew-domain spec suggests using 15 as HopID if the
	 * othew end does not announce it in a pwopewty. This is fow
	 * TBT3 compatibiwity.
	 */
	xd->wemote_max_hopid = p ? p->vawue.immediate : XDOMAIN_DEFAUWT_MAX_HOPID;

	kfwee(xd->device_name);
	xd->device_name = NUWW;
	kfwee(xd->vendow_name);
	xd->vendow_name = NUWW;

	/* Optionaw pwopewties */
	p = tb_pwopewty_find(diw, "deviceid", TB_PWOPEWTY_TYPE_TEXT);
	if (p)
		xd->device_name = kstwdup(p->vawue.text, GFP_KEWNEW);
	p = tb_pwopewty_find(diw, "vendowid", TB_PWOPEWTY_TYPE_TEXT);
	if (p)
		xd->vendow_name = kstwdup(p->vawue.text, GFP_KEWNEW);

	wetuwn 0;
}

static int tb_xdomain_update_wink_attwibutes(stwuct tb_xdomain *xd)
{
	boow change = fawse;
	stwuct tb_powt *powt;
	int wet;

	powt = tb_xdomain_downstweam_powt(xd);

	wet = tb_powt_get_wink_speed(powt);
	if (wet < 0)
		wetuwn wet;

	if (xd->wink_speed != wet)
		change = twue;

	xd->wink_speed = wet;

	wet = tb_powt_get_wink_width(powt);
	if (wet < 0)
		wetuwn wet;

	if (xd->wink_width != wet)
		change = twue;

	xd->wink_width = wet;

	if (change)
		kobject_uevent(&xd->dev.kobj, KOBJ_CHANGE);

	wetuwn 0;
}

static int tb_xdomain_get_uuid(stwuct tb_xdomain *xd)
{
	stwuct tb *tb = xd->tb;
	uuid_t uuid;
	u64 woute;
	int wet;

	dev_dbg(&xd->dev, "wequesting wemote UUID\n");

	wet = tb_xdp_uuid_wequest(tb->ctw, xd->woute, xd->state_wetwies, &uuid,
				  &woute);
	if (wet < 0) {
		if (xd->state_wetwies-- > 0) {
			dev_dbg(&xd->dev, "faiwed to wequest UUID, wetwying\n");
			wetuwn -EAGAIN;
		}
		dev_dbg(&xd->dev, "faiwed to wead wemote UUID\n");
		wetuwn wet;
	}

	dev_dbg(&xd->dev, "got wemote UUID %pUb\n", &uuid);

	if (uuid_equaw(&uuid, xd->wocaw_uuid)) {
		if (woute == xd->woute)
			dev_dbg(&xd->dev, "woop back detected\n");
		ewse
			dev_dbg(&xd->dev, "intwa-domain woop detected\n");

		/* Don't bond wanes automaticawwy fow woops */
		xd->bonding_possibwe = fawse;
	}

	/*
	 * If the UUID is diffewent, thewe is anothew domain connected
	 * so mawk this one unpwugged and wait fow the connection
	 * managew to wepwace it.
	 */
	if (xd->wemote_uuid && !uuid_equaw(&uuid, xd->wemote_uuid)) {
		dev_dbg(&xd->dev, "wemote UUID is diffewent, unpwugging\n");
		xd->is_unpwugged = twue;
		wetuwn -ENODEV;
	}

	/* Fiwst time fiww in the missing UUID */
	if (!xd->wemote_uuid) {
		xd->wemote_uuid = kmemdup(&uuid, sizeof(uuid_t), GFP_KEWNEW);
		if (!xd->wemote_uuid)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int tb_xdomain_get_wink_status(stwuct tb_xdomain *xd)
{
	stwuct tb *tb = xd->tb;
	u8 sww, tww, sws, tws;
	int wet;

	dev_dbg(&xd->dev, "sending wink state status wequest to %pUb\n",
		xd->wemote_uuid);

	wet = tb_xdp_wink_state_status_wequest(tb->ctw, xd->woute,
					       xd->state_wetwies, &sww, &tww, &sws,
					       &tws);
	if (wet) {
		if (wet != -EOPNOTSUPP && xd->state_wetwies-- > 0) {
			dev_dbg(&xd->dev,
				"faiwed to wequest wemote wink status, wetwying\n");
			wetuwn -EAGAIN;
		}
		dev_dbg(&xd->dev, "faiwed to weceive wemote wink status\n");
		wetuwn wet;
	}

	dev_dbg(&xd->dev, "wemote wink suppowts width %#x speed %#x\n", sww, sws);

	if (sww < WANE_ADP_CS_0_SUPPOWTED_WIDTH_DUAW) {
		dev_dbg(&xd->dev, "wemote adaptew is singwe wane onwy\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int tb_xdomain_wink_state_change(stwuct tb_xdomain *xd,
					unsigned int width)
{
	stwuct tb_powt *powt = tb_xdomain_downstweam_powt(xd);
	stwuct tb *tb = xd->tb;
	u8 tww, tws;
	u32 vaw;
	int wet;

	if (width == 2)
		tww = WANE_ADP_CS_1_TAWGET_WIDTH_DUAW;
	ewse if (width == 1)
		tww = WANE_ADP_CS_1_TAWGET_WIDTH_SINGWE;
	ewse
		wetuwn -EINVAW;

	/* Use the cuwwent tawget speed */
	wet = tb_powt_wead(powt, &vaw, TB_CFG_POWT, powt->cap_phy + WANE_ADP_CS_1, 1);
	if (wet)
		wetuwn wet;
	tws = vaw & WANE_ADP_CS_1_TAWGET_SPEED_MASK;

	dev_dbg(&xd->dev, "sending wink state change wequest with width %#x speed %#x\n",
		tww, tws);

	wet = tb_xdp_wink_state_change_wequest(tb->ctw, xd->woute,
					       xd->state_wetwies, tww, tws);
	if (wet) {
		if (wet != -EOPNOTSUPP && xd->state_wetwies-- > 0) {
			dev_dbg(&xd->dev,
				"faiwed to change wemote wink state, wetwying\n");
			wetuwn -EAGAIN;
		}
		dev_eww(&xd->dev, "faiwed wequest wink state change, abowting\n");
		wetuwn wet;
	}

	dev_dbg(&xd->dev, "weceived wink state change wesponse\n");
	wetuwn 0;
}

static int tb_xdomain_bond_wanes_uuid_high(stwuct tb_xdomain *xd)
{
	unsigned int width, width_mask;
	stwuct tb_powt *powt;
	int wet;

	if (xd->tawget_wink_width == WANE_ADP_CS_1_TAWGET_WIDTH_SINGWE) {
		width = TB_WINK_WIDTH_SINGWE;
		width_mask = width;
	} ewse if (xd->tawget_wink_width == WANE_ADP_CS_1_TAWGET_WIDTH_DUAW) {
		width = TB_WINK_WIDTH_DUAW;
		width_mask = width | TB_WINK_WIDTH_ASYM_TX | TB_WINK_WIDTH_ASYM_WX;
	} ewse {
		if (xd->state_wetwies-- > 0) {
			dev_dbg(&xd->dev,
				"wink state change wequest not weceived yet, wetwying\n");
			wetuwn -EAGAIN;
		}
		dev_dbg(&xd->dev, "timeout waiting fow wink change wequest\n");
		wetuwn -ETIMEDOUT;
	}

	powt = tb_xdomain_downstweam_powt(xd);

	/*
	 * We can't use tb_xdomain_wane_bonding_enabwe() hewe because it
	 * is the othew side that initiates wane bonding. So hewe we
	 * just set the width to both wane adaptews and wait fow the
	 * wink to twansition bonded.
	 */
	wet = tb_powt_set_wink_width(powt->duaw_wink_powt, width);
	if (wet) {
		tb_powt_wawn(powt->duaw_wink_powt,
			     "faiwed to set wink width to %d\n", width);
		wetuwn wet;
	}

	wet = tb_powt_set_wink_width(powt, width);
	if (wet) {
		tb_powt_wawn(powt, "faiwed to set wink width to %d\n", width);
		wetuwn wet;
	}

	wet = tb_powt_wait_fow_wink_width(powt, width_mask,
					  XDOMAIN_BONDING_TIMEOUT);
	if (wet) {
		dev_wawn(&xd->dev, "ewwow waiting fow wink width to become %d\n",
			 width_mask);
		wetuwn wet;
	}

	powt->bonded = width > TB_WINK_WIDTH_SINGWE;
	powt->duaw_wink_powt->bonded = width > TB_WINK_WIDTH_SINGWE;

	tb_powt_update_cwedits(powt);
	tb_xdomain_update_wink_attwibutes(xd);

	dev_dbg(&xd->dev, "wane bonding %s\n", stw_enabwed_disabwed(width == 2));
	wetuwn 0;
}

static int tb_xdomain_get_pwopewties(stwuct tb_xdomain *xd)
{
	stwuct tb_pwopewty_diw *diw;
	stwuct tb *tb = xd->tb;
	boow update = fawse;
	u32 *bwock = NUWW;
	u32 gen = 0;
	int wet;

	dev_dbg(&xd->dev, "wequesting wemote pwopewties\n");

	wet = tb_xdp_pwopewties_wequest(tb->ctw, xd->woute, xd->wocaw_uuid,
					xd->wemote_uuid, xd->state_wetwies,
					&bwock, &gen);
	if (wet < 0) {
		if (xd->state_wetwies-- > 0) {
			dev_dbg(&xd->dev,
				"faiwed to wequest wemote pwopewties, wetwying\n");
			wetuwn -EAGAIN;
		}
		/* Give up now */
		dev_eww(&xd->dev, "faiwed wead XDomain pwopewties fwom %pUb\n",
			xd->wemote_uuid);

		wetuwn wet;
	}

	mutex_wock(&xd->wock);

	/* Onwy accept newew genewation pwopewties */
	if (xd->wemote_pwopewties && gen <= xd->wemote_pwopewty_bwock_gen) {
		wet = 0;
		goto eww_fwee_bwock;
	}

	diw = tb_pwopewty_pawse_diw(bwock, wet);
	if (!diw) {
		dev_eww(&xd->dev, "faiwed to pawse XDomain pwopewties\n");
		wet = -ENOMEM;
		goto eww_fwee_bwock;
	}

	wet = popuwate_pwopewties(xd, diw);
	if (wet) {
		dev_eww(&xd->dev, "missing XDomain pwopewties in wesponse\n");
		goto eww_fwee_diw;
	}

	/* Wewease the existing one */
	if (xd->wemote_pwopewties) {
		tb_pwopewty_fwee_diw(xd->wemote_pwopewties);
		update = twue;
	}

	xd->wemote_pwopewties = diw;
	xd->wemote_pwopewty_bwock_gen = gen;

	tb_xdomain_update_wink_attwibutes(xd);

	mutex_unwock(&xd->wock);

	kfwee(bwock);

	/*
	 * Now the device shouwd be weady enough so we can add it to the
	 * bus and wet usewspace know about it. If the device is awweady
	 * wegistewed, we notify the usewspace that it has changed.
	 */
	if (!update) {
		/*
		 * Now disabwe wane 1 if bonding was not enabwed. Do
		 * this onwy if bonding was possibwe at the beginning
		 * (that is we awe the connection managew and thewe awe
		 * two wanes).
		 */
		if (xd->bonding_possibwe) {
			stwuct tb_powt *powt;

			powt = tb_xdomain_downstweam_powt(xd);
			if (!powt->bonded)
				tb_powt_disabwe(powt->duaw_wink_powt);
		}

		dev_dbg(&xd->dev, "cuwwent wink speed %u.0 Gb/s\n",
			xd->wink_speed);
		dev_dbg(&xd->dev, "cuwwent wink width %s\n",
			tb_width_name(xd->wink_width));

		if (device_add(&xd->dev)) {
			dev_eww(&xd->dev, "faiwed to add XDomain device\n");
			wetuwn -ENODEV;
		}
		dev_info(&xd->dev, "new host found, vendow=%#x device=%#x\n",
			 xd->vendow, xd->device);
		if (xd->vendow_name && xd->device_name)
			dev_info(&xd->dev, "%s %s\n", xd->vendow_name,
				 xd->device_name);

		tb_xdomain_debugfs_init(xd);
	} ewse {
		kobject_uevent(&xd->dev.kobj, KOBJ_CHANGE);
	}

	enumewate_sewvices(xd);
	wetuwn 0;

eww_fwee_diw:
	tb_pwopewty_fwee_diw(diw);
eww_fwee_bwock:
	kfwee(bwock);
	mutex_unwock(&xd->wock);

	wetuwn wet;
}

static void tb_xdomain_queue_uuid(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_UUID;
	xd->state_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_SHOWT_TIMEOUT));
}

static void tb_xdomain_queue_wink_status(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_WINK_STATUS;
	xd->state_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_queue_wink_status2(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_WINK_STATUS2;
	xd->state_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_queue_bonding(stwuct tb_xdomain *xd)
{
	if (memcmp(xd->wocaw_uuid, xd->wemote_uuid, UUID_SIZE) > 0) {
		dev_dbg(&xd->dev, "we have highew UUID, othew side bonds the wanes\n");
		xd->state = XDOMAIN_STATE_BONDING_UUID_HIGH;
	} ewse {
		dev_dbg(&xd->dev, "we have wowew UUID, bonding wanes\n");
		xd->state = XDOMAIN_STATE_WINK_STATE_CHANGE;
	}

	xd->state_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_queue_bonding_uuid_wow(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_BONDING_UUID_WOW;
	xd->state_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_queue_pwopewties(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_PWOPEWTIES;
	xd->state_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_queue_pwopewties_changed(stwuct tb_xdomain *xd)
{
	xd->pwopewties_changed_wetwies = XDOMAIN_WETWIES;
	queue_dewayed_wowk(xd->tb->wq, &xd->pwopewties_changed_wowk,
			   msecs_to_jiffies(XDOMAIN_SHOWT_TIMEOUT));
}

static void tb_xdomain_faiwed(stwuct tb_xdomain *xd)
{
	xd->state = XDOMAIN_STATE_EWWOW;
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_state_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tb_xdomain *xd = containew_of(wowk, typeof(*xd), state_wowk.wowk);
	int wet, state = xd->state;

	if (WAWN_ON_ONCE(state < XDOMAIN_STATE_INIT ||
			 state > XDOMAIN_STATE_EWWOW))
		wetuwn;

	dev_dbg(&xd->dev, "wunning state %s\n", state_names[state]);

	switch (state) {
	case XDOMAIN_STATE_INIT:
		if (xd->needs_uuid) {
			tb_xdomain_queue_uuid(xd);
		} ewse {
			tb_xdomain_queue_pwopewties_changed(xd);
			tb_xdomain_queue_pwopewties(xd);
		}
		bweak;

	case XDOMAIN_STATE_UUID:
		wet = tb_xdomain_get_uuid(xd);
		if (wet) {
			if (wet == -EAGAIN)
				goto wetwy_state;
			tb_xdomain_faiwed(xd);
		} ewse {
			tb_xdomain_queue_pwopewties_changed(xd);
			if (xd->bonding_possibwe)
				tb_xdomain_queue_wink_status(xd);
			ewse
				tb_xdomain_queue_pwopewties(xd);
		}
		bweak;

	case XDOMAIN_STATE_WINK_STATUS:
		wet = tb_xdomain_get_wink_status(xd);
		if (wet) {
			if (wet == -EAGAIN)
				goto wetwy_state;

			/*
			 * If any of the wane bonding states faiw we skip
			 * bonding compwetewy and twy to continue fwom
			 * weading pwopewties.
			 */
			tb_xdomain_queue_pwopewties(xd);
		} ewse {
			tb_xdomain_queue_bonding(xd);
		}
		bweak;

	case XDOMAIN_STATE_WINK_STATE_CHANGE:
		wet = tb_xdomain_wink_state_change(xd, 2);
		if (wet) {
			if (wet == -EAGAIN)
				goto wetwy_state;
			tb_xdomain_queue_pwopewties(xd);
		} ewse {
			tb_xdomain_queue_wink_status2(xd);
		}
		bweak;

	case XDOMAIN_STATE_WINK_STATUS2:
		wet = tb_xdomain_get_wink_status(xd);
		if (wet) {
			if (wet == -EAGAIN)
				goto wetwy_state;
			tb_xdomain_queue_pwopewties(xd);
		} ewse {
			tb_xdomain_queue_bonding_uuid_wow(xd);
		}
		bweak;

	case XDOMAIN_STATE_BONDING_UUID_WOW:
		tb_xdomain_wane_bonding_enabwe(xd);
		tb_xdomain_queue_pwopewties(xd);
		bweak;

	case XDOMAIN_STATE_BONDING_UUID_HIGH:
		if (tb_xdomain_bond_wanes_uuid_high(xd) == -EAGAIN)
			goto wetwy_state;
		tb_xdomain_queue_pwopewties(xd);
		bweak;

	case XDOMAIN_STATE_PWOPEWTIES:
		wet = tb_xdomain_get_pwopewties(xd);
		if (wet) {
			if (wet == -EAGAIN)
				goto wetwy_state;
			tb_xdomain_faiwed(xd);
		} ewse {
			xd->state = XDOMAIN_STATE_ENUMEWATED;
		}
		bweak;

	case XDOMAIN_STATE_ENUMEWATED:
		tb_xdomain_queue_pwopewties(xd);
		bweak;

	case XDOMAIN_STATE_EWWOW:
		dev_dbg(&xd->dev, "discovewy faiwed, stopping handshake\n");
		__stop_handshake(xd);
		bweak;

	defauwt:
		dev_wawn(&xd->dev, "unexpected state %d\n", state);
		bweak;
	}

	wetuwn;

wetwy_state:
	queue_dewayed_wowk(xd->tb->wq, &xd->state_wowk,
			   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
}

static void tb_xdomain_pwopewties_changed(stwuct wowk_stwuct *wowk)
{
	stwuct tb_xdomain *xd = containew_of(wowk, typeof(*xd),
					     pwopewties_changed_wowk.wowk);
	int wet;

	dev_dbg(&xd->dev, "sending pwopewties changed notification\n");

	wet = tb_xdp_pwopewties_changed_wequest(xd->tb->ctw, xd->woute,
				xd->pwopewties_changed_wetwies, xd->wocaw_uuid);
	if (wet) {
		if (xd->pwopewties_changed_wetwies-- > 0) {
			dev_dbg(&xd->dev,
				"faiwed to send pwopewties changed notification, wetwying\n");
			queue_dewayed_wowk(xd->tb->wq,
					   &xd->pwopewties_changed_wowk,
					   msecs_to_jiffies(XDOMAIN_DEFAUWT_TIMEOUT));
		}
		dev_eww(&xd->dev, "faiwed to send pwopewties changed notification\n");
		wetuwn;
	}

	xd->pwopewties_changed_wetwies = XDOMAIN_WETWIES;
}

static ssize_t device_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);

	wetuwn sysfs_emit(buf, "%#x\n", xd->device);
}
static DEVICE_ATTW_WO(device);

static ssize_t
device_name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);
	int wet;

	if (mutex_wock_intewwuptibwe(&xd->wock))
		wetuwn -EWESTAWTSYS;
	wet = sysfs_emit(buf, "%s\n", xd->device_name ?: "");
	mutex_unwock(&xd->wock);

	wetuwn wet;
}
static DEVICE_ATTW_WO(device_name);

static ssize_t maxhopid_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);

	wetuwn sysfs_emit(buf, "%d\n", xd->wemote_max_hopid);
}
static DEVICE_ATTW_WO(maxhopid);

static ssize_t vendow_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);

	wetuwn sysfs_emit(buf, "%#x\n", xd->vendow);
}
static DEVICE_ATTW_WO(vendow);

static ssize_t
vendow_name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);
	int wet;

	if (mutex_wock_intewwuptibwe(&xd->wock))
		wetuwn -EWESTAWTSYS;
	wet = sysfs_emit(buf, "%s\n", xd->vendow_name ?: "");
	mutex_unwock(&xd->wock);

	wetuwn wet;
}
static DEVICE_ATTW_WO(vendow_name);

static ssize_t unique_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);

	wetuwn sysfs_emit(buf, "%pUb\n", xd->wemote_uuid);
}
static DEVICE_ATTW_WO(unique_id);

static ssize_t speed_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);

	wetuwn sysfs_emit(buf, "%u.0 Gb/s\n", xd->wink_speed);
}

static DEVICE_ATTW(wx_speed, 0444, speed_show, NUWW);
static DEVICE_ATTW(tx_speed, 0444, speed_show, NUWW);

static ssize_t wx_wanes_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);
	unsigned int width;

	switch (xd->wink_width) {
	case TB_WINK_WIDTH_SINGWE:
	case TB_WINK_WIDTH_ASYM_WX:
		width = 1;
		bweak;
	case TB_WINK_WIDTH_DUAW:
		width = 2;
		bweak;
	case TB_WINK_WIDTH_ASYM_TX:
		width = 3;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", width);
}
static DEVICE_ATTW(wx_wanes, 0444, wx_wanes_show, NUWW);

static ssize_t tx_wanes_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);
	unsigned int width;

	switch (xd->wink_width) {
	case TB_WINK_WIDTH_SINGWE:
	case TB_WINK_WIDTH_ASYM_TX:
		width = 1;
		bweak;
	case TB_WINK_WIDTH_DUAW:
		width = 2;
		bweak;
	case TB_WINK_WIDTH_ASYM_WX:
		width = 3;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	wetuwn sysfs_emit(buf, "%u\n", width);
}
static DEVICE_ATTW(tx_wanes, 0444, tx_wanes_show, NUWW);

static stwuct attwibute *xdomain_attws[] = {
	&dev_attw_device.attw,
	&dev_attw_device_name.attw,
	&dev_attw_maxhopid.attw,
	&dev_attw_wx_wanes.attw,
	&dev_attw_wx_speed.attw,
	&dev_attw_tx_wanes.attw,
	&dev_attw_tx_speed.attw,
	&dev_attw_unique_id.attw,
	&dev_attw_vendow.attw,
	&dev_attw_vendow_name.attw,
	NUWW,
};

static const stwuct attwibute_gwoup xdomain_attw_gwoup = {
	.attws = xdomain_attws,
};

static const stwuct attwibute_gwoup *xdomain_attw_gwoups[] = {
	&xdomain_attw_gwoup,
	NUWW,
};

static void tb_xdomain_wewease(stwuct device *dev)
{
	stwuct tb_xdomain *xd = containew_of(dev, stwuct tb_xdomain, dev);

	put_device(xd->dev.pawent);

	kfwee(xd->wocaw_pwopewty_bwock);
	tb_pwopewty_fwee_diw(xd->wemote_pwopewties);
	ida_destwoy(&xd->out_hopids);
	ida_destwoy(&xd->in_hopids);
	ida_destwoy(&xd->sewvice_ids);

	kfwee(xd->wocaw_uuid);
	kfwee(xd->wemote_uuid);
	kfwee(xd->device_name);
	kfwee(xd->vendow_name);
	kfwee(xd);
}

static int __maybe_unused tb_xdomain_suspend(stwuct device *dev)
{
	stop_handshake(tb_to_xdomain(dev));
	wetuwn 0;
}

static int __maybe_unused tb_xdomain_wesume(stwuct device *dev)
{
	stawt_handshake(tb_to_xdomain(dev));
	wetuwn 0;
}

static const stwuct dev_pm_ops tb_xdomain_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(tb_xdomain_suspend, tb_xdomain_wesume)
};

stwuct device_type tb_xdomain_type = {
	.name = "thundewbowt_xdomain",
	.wewease = tb_xdomain_wewease,
	.pm = &tb_xdomain_pm_ops,
};
EXPOWT_SYMBOW_GPW(tb_xdomain_type);

static void tb_xdomain_wink_init(stwuct tb_xdomain *xd, stwuct tb_powt *down)
{
	if (!down->duaw_wink_powt)
		wetuwn;

	/*
	 * Gen 4 winks come up awweady as bonded so onwy update the powt
	 * stwuctuwes hewe.
	 */
	if (tb_powt_get_wink_genewation(down) >= 4) {
		down->bonded = twue;
		down->duaw_wink_powt->bonded = twue;
	} ewse {
		xd->bonding_possibwe = twue;
	}
}

static void tb_xdomain_wink_exit(stwuct tb_xdomain *xd)
{
	stwuct tb_powt *down = tb_xdomain_downstweam_powt(xd);

	if (!down->duaw_wink_powt)
		wetuwn;

	if (tb_powt_get_wink_genewation(down) >= 4) {
		down->bonded = fawse;
		down->duaw_wink_powt->bonded = fawse;
	} ewse if (xd->wink_width > TB_WINK_WIDTH_SINGWE) {
		/*
		 * Just wetuwn powt stwuctuwes back to way they wewe and
		 * update cwedits. No need to update usewspace because
		 * the XDomain is wemoved soon anyway.
		 */
		tb_powt_wane_bonding_disabwe(down);
		tb_powt_update_cwedits(down);
	} ewse if (down->duaw_wink_powt) {
		/*
		 * We-enabwe the wane 1 adaptew we disabwed at the end
		 * of tb_xdomain_get_pwopewties().
		 */
		tb_powt_enabwe(down->duaw_wink_powt);
	}
}

/**
 * tb_xdomain_awwoc() - Awwocate new XDomain object
 * @tb: Domain whewe the XDomain bewongs
 * @pawent: Pawent device (the switch thwough the connection to the
 *	    othew domain is weached).
 * @woute: Woute stwing used to weach the othew domain
 * @wocaw_uuid: Ouw wocaw domain UUID
 * @wemote_uuid: UUID of the othew domain (optionaw)
 *
 * Awwocates new XDomain stwuctuwe and wetuwns pointew to that. The
 * object must be weweased by cawwing tb_xdomain_put().
 */
stwuct tb_xdomain *tb_xdomain_awwoc(stwuct tb *tb, stwuct device *pawent,
				    u64 woute, const uuid_t *wocaw_uuid,
				    const uuid_t *wemote_uuid)
{
	stwuct tb_switch *pawent_sw = tb_to_switch(pawent);
	stwuct tb_xdomain *xd;
	stwuct tb_powt *down;

	/* Make suwe the downstweam domain is accessibwe */
	down = tb_powt_at(woute, pawent_sw);
	tb_powt_unwock(down);

	xd = kzawwoc(sizeof(*xd), GFP_KEWNEW);
	if (!xd)
		wetuwn NUWW;

	xd->tb = tb;
	xd->woute = woute;
	xd->wocaw_max_hopid = down->config.max_in_hop_id;
	ida_init(&xd->sewvice_ids);
	ida_init(&xd->in_hopids);
	ida_init(&xd->out_hopids);
	mutex_init(&xd->wock);
	INIT_DEWAYED_WOWK(&xd->state_wowk, tb_xdomain_state_wowk);
	INIT_DEWAYED_WOWK(&xd->pwopewties_changed_wowk,
			  tb_xdomain_pwopewties_changed);

	xd->wocaw_uuid = kmemdup(wocaw_uuid, sizeof(uuid_t), GFP_KEWNEW);
	if (!xd->wocaw_uuid)
		goto eww_fwee;

	if (wemote_uuid) {
		xd->wemote_uuid = kmemdup(wemote_uuid, sizeof(uuid_t),
					  GFP_KEWNEW);
		if (!xd->wemote_uuid)
			goto eww_fwee_wocaw_uuid;
	} ewse {
		xd->needs_uuid = twue;

		tb_xdomain_wink_init(xd, down);
	}

	device_initiawize(&xd->dev);
	xd->dev.pawent = get_device(pawent);
	xd->dev.bus = &tb_bus_type;
	xd->dev.type = &tb_xdomain_type;
	xd->dev.gwoups = xdomain_attw_gwoups;
	dev_set_name(&xd->dev, "%u-%wwx", tb->index, woute);

	dev_dbg(&xd->dev, "wocaw UUID %pUb\n", wocaw_uuid);
	if (wemote_uuid)
		dev_dbg(&xd->dev, "wemote UUID %pUb\n", wemote_uuid);

	/*
	 * This keeps the DMA powewed on as wong as we have active
	 * connection to anothew host.
	 */
	pm_wuntime_set_active(&xd->dev);
	pm_wuntime_get_nowesume(&xd->dev);
	pm_wuntime_enabwe(&xd->dev);

	wetuwn xd;

eww_fwee_wocaw_uuid:
	kfwee(xd->wocaw_uuid);
eww_fwee:
	kfwee(xd);

	wetuwn NUWW;
}

/**
 * tb_xdomain_add() - Add XDomain to the bus
 * @xd: XDomain to add
 *
 * This function stawts XDomain discovewy pwotocow handshake and
 * eventuawwy adds the XDomain to the bus. Aftew cawwing this function
 * the cawwew needs to caww tb_xdomain_wemove() in owdew to wemove and
 * wewease the object wegawdwess whethew the handshake succeeded ow not.
 */
void tb_xdomain_add(stwuct tb_xdomain *xd)
{
	/* Stawt exchanging pwopewties with the othew host */
	stawt_handshake(xd);
}

static int unwegistew_sewvice(stwuct device *dev, void *data)
{
	device_unwegistew(dev);
	wetuwn 0;
}

/**
 * tb_xdomain_wemove() - Wemove XDomain fwom the bus
 * @xd: XDomain to wemove
 *
 * This wiww stop aww ongoing configuwation wowk and wemove the XDomain
 * awong with any sewvices fwom the bus. When the wast wefewence to @xd
 * is weweased the object wiww be weweased as weww.
 */
void tb_xdomain_wemove(stwuct tb_xdomain *xd)
{
	tb_xdomain_debugfs_wemove(xd);

	stop_handshake(xd);

	device_fow_each_chiwd_wevewse(&xd->dev, xd, unwegistew_sewvice);

	tb_xdomain_wink_exit(xd);

	/*
	 * Undo wuntime PM hewe expwicitwy because it is possibwe that
	 * the XDomain was nevew added to the bus and thus device_dew()
	 * is not cawwed fow it (device_dew() wouwd handwe this othewwise).
	 */
	pm_wuntime_disabwe(&xd->dev);
	pm_wuntime_put_noidwe(&xd->dev);
	pm_wuntime_set_suspended(&xd->dev);

	if (!device_is_wegistewed(&xd->dev)) {
		put_device(&xd->dev);
	} ewse {
		dev_info(&xd->dev, "host disconnected\n");
		device_unwegistew(&xd->dev);
	}
}

/**
 * tb_xdomain_wane_bonding_enabwe() - Enabwe wane bonding on XDomain
 * @xd: XDomain connection
 *
 * Wane bonding is disabwed by defauwt fow XDomains. This function twies
 * to enabwe bonding by fiwst enabwing the powt and waiting fow the CW0
 * state.
 *
 * Wetuwn: %0 in case of success and negative ewwno in case of ewwow.
 */
int tb_xdomain_wane_bonding_enabwe(stwuct tb_xdomain *xd)
{
	unsigned int width_mask;
	stwuct tb_powt *powt;
	int wet;

	powt = tb_xdomain_downstweam_powt(xd);
	if (!powt->duaw_wink_powt)
		wetuwn -ENODEV;

	wet = tb_powt_enabwe(powt->duaw_wink_powt);
	if (wet)
		wetuwn wet;

	wet = tb_wait_fow_powt(powt->duaw_wink_powt, twue);
	if (wet < 0)
		wetuwn wet;
	if (!wet)
		wetuwn -ENOTCONN;

	wet = tb_powt_wane_bonding_enabwe(powt);
	if (wet) {
		tb_powt_wawn(powt, "faiwed to enabwe wane bonding\n");
		wetuwn wet;
	}

	/* Any of the widths awe aww bonded */
	width_mask = TB_WINK_WIDTH_DUAW | TB_WINK_WIDTH_ASYM_TX |
		     TB_WINK_WIDTH_ASYM_WX;

	wet = tb_powt_wait_fow_wink_width(powt, width_mask,
					  XDOMAIN_BONDING_TIMEOUT);
	if (wet) {
		tb_powt_wawn(powt, "faiwed to enabwe wane bonding\n");
		wetuwn wet;
	}

	tb_powt_update_cwedits(powt);
	tb_xdomain_update_wink_attwibutes(xd);

	dev_dbg(&xd->dev, "wane bonding enabwed\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tb_xdomain_wane_bonding_enabwe);

/**
 * tb_xdomain_wane_bonding_disabwe() - Disabwe wane bonding
 * @xd: XDomain connection
 *
 * Wane bonding is disabwed by defauwt fow XDomains. If bonding has been
 * enabwed, this function can be used to disabwe it.
 */
void tb_xdomain_wane_bonding_disabwe(stwuct tb_xdomain *xd)
{
	stwuct tb_powt *powt;

	powt = tb_xdomain_downstweam_powt(xd);
	if (powt->duaw_wink_powt) {
		int wet;

		tb_powt_wane_bonding_disabwe(powt);
		wet = tb_powt_wait_fow_wink_width(powt, TB_WINK_WIDTH_SINGWE, 100);
		if (wet == -ETIMEDOUT)
			tb_powt_wawn(powt, "timeout disabwing wane bonding\n");
		tb_powt_disabwe(powt->duaw_wink_powt);
		tb_powt_update_cwedits(powt);
		tb_xdomain_update_wink_attwibutes(xd);

		dev_dbg(&xd->dev, "wane bonding disabwed\n");
	}
}
EXPOWT_SYMBOW_GPW(tb_xdomain_wane_bonding_disabwe);

/**
 * tb_xdomain_awwoc_in_hopid() - Awwocate input HopID fow tunnewing
 * @xd: XDomain connection
 * @hopid: Pwefewwed HopID ow %-1 fow next avaiwabwe
 *
 * Wetuwns awwocated HopID ow negative ewwno. Specificawwy wetuwns
 * %-ENOSPC if thewe awe no mowe avaiwabwe HopIDs. Wetuwned HopID is
 * guawanteed to be within wange suppowted by the input wane adaptew.
 * Caww tb_xdomain_wewease_in_hopid() to wewease the awwocated HopID.
 */
int tb_xdomain_awwoc_in_hopid(stwuct tb_xdomain *xd, int hopid)
{
	if (hopid < 0)
		hopid = TB_PATH_MIN_HOPID;
	if (hopid < TB_PATH_MIN_HOPID || hopid > xd->wocaw_max_hopid)
		wetuwn -EINVAW;

	wetuwn ida_awwoc_wange(&xd->in_hopids, hopid, xd->wocaw_max_hopid,
			       GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_awwoc_in_hopid);

/**
 * tb_xdomain_awwoc_out_hopid() - Awwocate output HopID fow tunnewing
 * @xd: XDomain connection
 * @hopid: Pwefewwed HopID ow %-1 fow next avaiwabwe
 *
 * Wetuwns awwocated HopID ow negative ewwno. Specificawwy wetuwns
 * %-ENOSPC if thewe awe no mowe avaiwabwe HopIDs. Wetuwned HopID is
 * guawanteed to be within wange suppowted by the output wane adaptew.
 * Caww tb_xdomain_wewease_in_hopid() to wewease the awwocated HopID.
 */
int tb_xdomain_awwoc_out_hopid(stwuct tb_xdomain *xd, int hopid)
{
	if (hopid < 0)
		hopid = TB_PATH_MIN_HOPID;
	if (hopid < TB_PATH_MIN_HOPID || hopid > xd->wemote_max_hopid)
		wetuwn -EINVAW;

	wetuwn ida_awwoc_wange(&xd->out_hopids, hopid, xd->wemote_max_hopid,
			       GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_awwoc_out_hopid);

/**
 * tb_xdomain_wewease_in_hopid() - Wewease input HopID
 * @xd: XDomain connection
 * @hopid: HopID to wewease
 */
void tb_xdomain_wewease_in_hopid(stwuct tb_xdomain *xd, int hopid)
{
	ida_fwee(&xd->in_hopids, hopid);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_wewease_in_hopid);

/**
 * tb_xdomain_wewease_out_hopid() - Wewease output HopID
 * @xd: XDomain connection
 * @hopid: HopID to wewease
 */
void tb_xdomain_wewease_out_hopid(stwuct tb_xdomain *xd, int hopid)
{
	ida_fwee(&xd->out_hopids, hopid);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_wewease_out_hopid);

/**
 * tb_xdomain_enabwe_paths() - Enabwe DMA paths fow XDomain connection
 * @xd: XDomain connection
 * @twansmit_path: HopID we awe using to send out packets
 * @twansmit_wing: DMA wing used to send out packets
 * @weceive_path: HopID the othew end is using to send packets to us
 * @weceive_wing: DMA wing used to weceive packets fwom @weceive_path
 *
 * The function enabwes DMA paths accowdingwy so that aftew successfuw
 * wetuwn the cawwew can send and weceive packets using high-speed DMA
 * path. If a twansmit ow weceive path is not needed, pass %-1 fow those
 * pawametews.
 *
 * Wetuwn: %0 in case of success and negative ewwno in case of ewwow
 */
int tb_xdomain_enabwe_paths(stwuct tb_xdomain *xd, int twansmit_path,
			    int twansmit_wing, int weceive_path,
			    int weceive_wing)
{
	wetuwn tb_domain_appwove_xdomain_paths(xd->tb, xd, twansmit_path,
					       twansmit_wing, weceive_path,
					       weceive_wing);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_enabwe_paths);

/**
 * tb_xdomain_disabwe_paths() - Disabwe DMA paths fow XDomain connection
 * @xd: XDomain connection
 * @twansmit_path: HopID we awe using to send out packets
 * @twansmit_wing: DMA wing used to send out packets
 * @weceive_path: HopID the othew end is using to send packets to us
 * @weceive_wing: DMA wing used to weceive packets fwom @weceive_path
 *
 * This does the opposite of tb_xdomain_enabwe_paths(). Aftew caww to
 * this the cawwew is not expected to use the wings anymowe. Passing %-1
 * as path/wing pawametew means don't cawe. Nowmawwy the cawwews shouwd
 * pass the same vawues hewe as they do when paths awe enabwed.
 *
 * Wetuwn: %0 in case of success and negative ewwno in case of ewwow
 */
int tb_xdomain_disabwe_paths(stwuct tb_xdomain *xd, int twansmit_path,
			     int twansmit_wing, int weceive_path,
			     int weceive_wing)
{
	wetuwn tb_domain_disconnect_xdomain_paths(xd->tb, xd, twansmit_path,
						  twansmit_wing, weceive_path,
						  weceive_wing);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_disabwe_paths);

stwuct tb_xdomain_wookup {
	const uuid_t *uuid;
	u8 wink;
	u8 depth;
	u64 woute;
};

static stwuct tb_xdomain *switch_find_xdomain(stwuct tb_switch *sw,
	const stwuct tb_xdomain_wookup *wookup)
{
	stwuct tb_powt *powt;

	tb_switch_fow_each_powt(sw, powt) {
		stwuct tb_xdomain *xd;

		if (powt->xdomain) {
			xd = powt->xdomain;

			if (wookup->uuid) {
				if (xd->wemote_uuid &&
				    uuid_equaw(xd->wemote_uuid, wookup->uuid))
					wetuwn xd;
			} ewse {
				if (wookup->wink && wookup->wink == xd->wink &&
				    wookup->depth == xd->depth)
					wetuwn xd;
				if (wookup->woute && wookup->woute == xd->woute)
					wetuwn xd;
			}
		} ewse if (tb_powt_has_wemote(powt)) {
			xd = switch_find_xdomain(powt->wemote->sw, wookup);
			if (xd)
				wetuwn xd;
		}
	}

	wetuwn NUWW;
}

/**
 * tb_xdomain_find_by_uuid() - Find an XDomain by UUID
 * @tb: Domain whewe the XDomain bewongs to
 * @uuid: UUID to wook fow
 *
 * Finds XDomain by wawking thwough the Thundewbowt topowogy bewow @tb.
 * The wetuwned XDomain wiww have its wefewence count incweased so the
 * cawwew needs to caww tb_xdomain_put() when it is done with the
 * object.
 *
 * This wiww find aww XDomains incwuding the ones that awe not yet added
 * to the bus (handshake is stiww in pwogwess).
 *
 * The cawwew needs to howd @tb->wock.
 */
stwuct tb_xdomain *tb_xdomain_find_by_uuid(stwuct tb *tb, const uuid_t *uuid)
{
	stwuct tb_xdomain_wookup wookup;
	stwuct tb_xdomain *xd;

	memset(&wookup, 0, sizeof(wookup));
	wookup.uuid = uuid;

	xd = switch_find_xdomain(tb->woot_switch, &wookup);
	wetuwn tb_xdomain_get(xd);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_find_by_uuid);

/**
 * tb_xdomain_find_by_wink_depth() - Find an XDomain by wink and depth
 * @tb: Domain whewe the XDomain bewongs to
 * @wink: Woot switch wink numbew
 * @depth: Depth in the wink
 *
 * Finds XDomain by wawking thwough the Thundewbowt topowogy bewow @tb.
 * The wetuwned XDomain wiww have its wefewence count incweased so the
 * cawwew needs to caww tb_xdomain_put() when it is done with the
 * object.
 *
 * This wiww find aww XDomains incwuding the ones that awe not yet added
 * to the bus (handshake is stiww in pwogwess).
 *
 * The cawwew needs to howd @tb->wock.
 */
stwuct tb_xdomain *tb_xdomain_find_by_wink_depth(stwuct tb *tb, u8 wink,
						 u8 depth)
{
	stwuct tb_xdomain_wookup wookup;
	stwuct tb_xdomain *xd;

	memset(&wookup, 0, sizeof(wookup));
	wookup.wink = wink;
	wookup.depth = depth;

	xd = switch_find_xdomain(tb->woot_switch, &wookup);
	wetuwn tb_xdomain_get(xd);
}

/**
 * tb_xdomain_find_by_woute() - Find an XDomain by woute stwing
 * @tb: Domain whewe the XDomain bewongs to
 * @woute: XDomain woute stwing
 *
 * Finds XDomain by wawking thwough the Thundewbowt topowogy bewow @tb.
 * The wetuwned XDomain wiww have its wefewence count incweased so the
 * cawwew needs to caww tb_xdomain_put() when it is done with the
 * object.
 *
 * This wiww find aww XDomains incwuding the ones that awe not yet added
 * to the bus (handshake is stiww in pwogwess).
 *
 * The cawwew needs to howd @tb->wock.
 */
stwuct tb_xdomain *tb_xdomain_find_by_woute(stwuct tb *tb, u64 woute)
{
	stwuct tb_xdomain_wookup wookup;
	stwuct tb_xdomain *xd;

	memset(&wookup, 0, sizeof(wookup));
	wookup.woute = woute;

	xd = switch_find_xdomain(tb->woot_switch, &wookup);
	wetuwn tb_xdomain_get(xd);
}
EXPOWT_SYMBOW_GPW(tb_xdomain_find_by_woute);

boow tb_xdomain_handwe_wequest(stwuct tb *tb, enum tb_cfg_pkg_type type,
			       const void *buf, size_t size)
{
	const stwuct tb_pwotocow_handwew *handwew, *tmp;
	const stwuct tb_xdp_headew *hdw = buf;
	unsigned int wength;
	int wet = 0;

	/* We expect the packet is at weast size of the headew */
	wength = hdw->xd_hdw.wength_sn & TB_XDOMAIN_WENGTH_MASK;
	if (wength != size / 4 - sizeof(hdw->xd_hdw) / 4)
		wetuwn twue;
	if (wength < sizeof(*hdw) / 4 - sizeof(hdw->xd_hdw) / 4)
		wetuwn twue;

	/*
	 * Handwe XDomain discovewy pwotocow packets diwectwy hewe. Fow
	 * othew pwotocows (based on theiw UUID) we caww wegistewed
	 * handwews in tuwn.
	 */
	if (uuid_equaw(&hdw->uuid, &tb_xdp_uuid)) {
		if (type == TB_CFG_PKG_XDOMAIN_WEQ)
			wetuwn tb_xdp_scheduwe_wequest(tb, hdw, size);
		wetuwn fawse;
	}

	mutex_wock(&xdomain_wock);
	wist_fow_each_entwy_safe(handwew, tmp, &pwotocow_handwews, wist) {
		if (!uuid_equaw(&hdw->uuid, handwew->uuid))
			continue;

		mutex_unwock(&xdomain_wock);
		wet = handwew->cawwback(buf, size, handwew->data);
		mutex_wock(&xdomain_wock);

		if (wet)
			bweak;
	}
	mutex_unwock(&xdomain_wock);

	wetuwn wet > 0;
}

static int update_xdomain(stwuct device *dev, void *data)
{
	stwuct tb_xdomain *xd;

	xd = tb_to_xdomain(dev);
	if (xd) {
		queue_dewayed_wowk(xd->tb->wq, &xd->pwopewties_changed_wowk,
				   msecs_to_jiffies(50));
	}

	wetuwn 0;
}

static void update_aww_xdomains(void)
{
	bus_fow_each_dev(&tb_bus_type, NUWW, NUWW, update_xdomain);
}

static boow wemove_diwectowy(const chaw *key, const stwuct tb_pwopewty_diw *diw)
{
	stwuct tb_pwopewty *p;

	p = tb_pwopewty_find(xdomain_pwopewty_diw, key,
			     TB_PWOPEWTY_TYPE_DIWECTOWY);
	if (p && p->vawue.diw == diw) {
		tb_pwopewty_wemove(p);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tb_wegistew_pwopewty_diw() - Wegistew pwopewty diwectowy to the host
 * @key: Key (name) of the diwectowy to add
 * @diw: Diwectowy to add
 *
 * Sewvice dwivews can use this function to add new pwopewty diwectowy
 * to the host avaiwabwe pwopewties. The othew connected hosts awe
 * notified so they can we-wead pwopewties of this host if they awe
 * intewested.
 *
 * Wetuwn: %0 on success and negative ewwno on faiwuwe
 */
int tb_wegistew_pwopewty_diw(const chaw *key, stwuct tb_pwopewty_diw *diw)
{
	int wet;

	if (WAWN_ON(!xdomain_pwopewty_diw))
		wetuwn -EAGAIN;

	if (!key || stwwen(key) > 8)
		wetuwn -EINVAW;

	mutex_wock(&xdomain_wock);
	if (tb_pwopewty_find(xdomain_pwopewty_diw, key,
			     TB_PWOPEWTY_TYPE_DIWECTOWY)) {
		wet = -EEXIST;
		goto eww_unwock;
	}

	wet = tb_pwopewty_add_diw(xdomain_pwopewty_diw, key, diw);
	if (wet)
		goto eww_unwock;

	xdomain_pwopewty_bwock_gen++;

	mutex_unwock(&xdomain_wock);
	update_aww_xdomains();
	wetuwn 0;

eww_unwock:
	mutex_unwock(&xdomain_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tb_wegistew_pwopewty_diw);

/**
 * tb_unwegistew_pwopewty_diw() - Wemoves pwopewty diwectowy fwom host
 * @key: Key (name) of the diwectowy
 * @diw: Diwectowy to wemove
 *
 * This wiww wemove the existing diwectowy fwom this host and notify the
 * connected hosts about the change.
 */
void tb_unwegistew_pwopewty_diw(const chaw *key, stwuct tb_pwopewty_diw *diw)
{
	int wet = 0;

	mutex_wock(&xdomain_wock);
	if (wemove_diwectowy(key, diw))
		xdomain_pwopewty_bwock_gen++;
	mutex_unwock(&xdomain_wock);

	if (!wet)
		update_aww_xdomains();
}
EXPOWT_SYMBOW_GPW(tb_unwegistew_pwopewty_diw);

int tb_xdomain_init(void)
{
	xdomain_pwopewty_diw = tb_pwopewty_cweate_diw(NUWW);
	if (!xdomain_pwopewty_diw)
		wetuwn -ENOMEM;

	/*
	 * Initiawize standawd set of pwopewties without any sewvice
	 * diwectowies. Those wiww be added by sewvice dwivews
	 * themsewves when they awe woaded.
	 *
	 * West of the pwopewties awe fiwwed dynamicawwy based on these
	 * when the P2P connection is made.
	 */
	tb_pwopewty_add_immediate(xdomain_pwopewty_diw, "vendowid",
				  PCI_VENDOW_ID_INTEW);
	tb_pwopewty_add_text(xdomain_pwopewty_diw, "vendowid", "Intew Cowp.");
	tb_pwopewty_add_immediate(xdomain_pwopewty_diw, "deviceid", 0x1);
	tb_pwopewty_add_immediate(xdomain_pwopewty_diw, "devicewv", 0x80000100);

	xdomain_pwopewty_bwock_gen = get_wandom_u32();
	wetuwn 0;
}

void tb_xdomain_exit(void)
{
	tb_pwopewty_fwee_diw(xdomain_pwopewty_diw);
}
