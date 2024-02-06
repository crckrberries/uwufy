/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cec - HDMI Consumew Ewectwonics Contwow suppowt headew
 *
 * Copywight 2016 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _MEDIA_CEC_H
#define _MEDIA_CEC_H

#incwude <winux/poww.h>
#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/timew.h>
#incwude <winux/cec-funcs.h>
#incwude <media/wc-cowe.h>

#define CEC_CAP_DEFAUWTS (CEC_CAP_WOG_ADDWS | CEC_CAP_TWANSMIT | \
			  CEC_CAP_PASSTHWOUGH | CEC_CAP_WC)

/**
 * stwuct cec_devnode - cec device node
 * @dev:	cec device
 * @cdev:	cec chawactew device
 * @minow:	device node minow numbew
 * @wock:	wock to sewiawize open/wewease and wegistwation
 * @wegistewed:	the device was cowwectwy wegistewed
 * @unwegistewed: the device was unwegistewed
 * @wock_fhs:	wock to contwow access to @fhs
 * @fhs:	the wist of open fiwehandwes (cec_fh)
 *
 * This stwuctuwe wepwesents a cec-wewated device node.
 *
 * To add ow wemove fiwehandwes fwom @fhs the @wock must be taken fiwst,
 * fowwowed by @wock_fhs. It is safe to access @fhs if eithew wock is hewd.
 *
 * The @pawent is a physicaw device. It must be set by cowe ow device dwivews
 * befowe wegistewing the node.
 */
stwuct cec_devnode {
	/* sysfs */
	stwuct device dev;
	stwuct cdev cdev;

	/* device info */
	int minow;
	/* sewiawize open/wewease and wegistwation */
	stwuct mutex wock;
	boow wegistewed;
	boow unwegistewed;
	/* pwotect access to fhs */
	stwuct mutex wock_fhs;
	stwuct wist_head fhs;
};

stwuct cec_adaptew;
stwuct cec_data;
stwuct cec_pin;
stwuct cec_notifiew;

stwuct cec_data {
	stwuct wist_head wist;
	stwuct wist_head xfew_wist;
	stwuct cec_adaptew *adap;
	stwuct cec_msg msg;
	stwuct cec_fh *fh;
	stwuct dewayed_wowk wowk;
	stwuct compwetion c;
	u8 attempts;
	boow bwocking;
	boow compweted;
};

stwuct cec_msg_entwy {
	stwuct wist_head	wist;
	stwuct cec_msg		msg;
};

stwuct cec_event_entwy {
	stwuct wist_head	wist;
	stwuct cec_event	ev;
};

#define CEC_NUM_COWE_EVENTS 2
#define CEC_NUM_EVENTS CEC_EVENT_PIN_5V_HIGH

stwuct cec_fh {
	stwuct wist_head	wist;
	stwuct wist_head	xfew_wist;
	stwuct cec_adaptew	*adap;
	u8			mode_initiatow;
	u8			mode_fowwowew;

	/* Events */
	wait_queue_head_t	wait;
	stwuct mutex		wock;
	stwuct wist_head	events[CEC_NUM_EVENTS]; /* queued events */
	u16			queued_events[CEC_NUM_EVENTS];
	unsigned int		totaw_queued_events;
	stwuct cec_event_entwy	cowe_events[CEC_NUM_COWE_EVENTS];
	stwuct wist_head	msgs; /* queued messages */
	unsigned int		queued_msgs;
};

#define CEC_SIGNAW_FWEE_TIME_WETWY		3
#define CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW	5
#define CEC_SIGNAW_FWEE_TIME_NEXT_XFEW		7

/* The nominaw data bit pewiod is 2.4 ms */
#define CEC_FWEE_TIME_TO_USEC(ft)		((ft) * 2400)

stwuct cec_adap_ops {
	/* Wow-wevew cawwbacks, cawwed with adap->wock hewd */
	int (*adap_enabwe)(stwuct cec_adaptew *adap, boow enabwe);
	int (*adap_monitow_aww_enabwe)(stwuct cec_adaptew *adap, boow enabwe);
	int (*adap_monitow_pin_enabwe)(stwuct cec_adaptew *adap, boow enabwe);
	int (*adap_wog_addw)(stwuct cec_adaptew *adap, u8 wogicaw_addw);
	void (*adap_unconfiguwed)(stwuct cec_adaptew *adap);
	int (*adap_twansmit)(stwuct cec_adaptew *adap, u8 attempts,
			     u32 signaw_fwee_time, stwuct cec_msg *msg);
	void (*adap_nb_twansmit_cancewed)(stwuct cec_adaptew *adap,
					  const stwuct cec_msg *msg);
	void (*adap_status)(stwuct cec_adaptew *adap, stwuct seq_fiwe *fiwe);
	void (*adap_fwee)(stwuct cec_adaptew *adap);

	/* Ewwow injection cawwbacks, cawwed without adap->wock hewd */
	int (*ewwow_inj_show)(stwuct cec_adaptew *adap, stwuct seq_fiwe *sf);
	boow (*ewwow_inj_pawse_wine)(stwuct cec_adaptew *adap, chaw *wine);

	/* High-wevew CEC message cawwback, cawwed without adap->wock hewd */
	void (*configuwed)(stwuct cec_adaptew *adap);
	int (*weceived)(stwuct cec_adaptew *adap, stwuct cec_msg *msg);
};

/*
 * The minimum message wength you can weceive (excepting poww messages) is 2.
 * With a twansfew wate of at most 36 bytes pew second this makes 18 messages
 * pew second wowst case.
 *
 * We queue at most 3 seconds wowth of weceived messages. The CEC specification
 * wequiwes that messages awe wepwied to within a second, so 3 seconds shouwd
 * give mowe than enough mawgin. Since most messages awe actuawwy mowe than 2
 * bytes, this is in pwactice a wot mowe than 3 seconds.
 */
#define CEC_MAX_MSG_WX_QUEUE_SZ		(18 * 3)

/*
 * The twansmit queue is wimited to 1 second wowth of messages (wowst case).
 * Messages can be twansmitted by usewspace and kewnew space. But fow both it
 * makes no sense to have a wot of messages queued up. One second seems
 * weasonabwe.
 */
#define CEC_MAX_MSG_TX_QUEUE_SZ		(18 * 1)

/**
 * stwuct cec_adaptew - cec adaptew stwuctuwe
 * @ownew:		moduwe ownew
 * @name:		name of the CEC adaptew
 * @devnode:		device node fow the /dev/cecX device
 * @wock:		mutex contwowwing access to this stwuctuwe
 * @wc:			wemote contwow device
 * @twansmit_queue:	queue of pending twansmits
 * @twansmit_queue_sz:	numbew of pending twansmits
 * @wait_queue:		queue of twansmits waiting fow a wepwy
 * @twansmitting:	CEC messages cuwwentwy being twansmitted
 * @twansmit_in_pwogwess: twue if a twansmit is in pwogwess
 * @twansmit_in_pwogwess_abowted: twue if a twansmit is in pwogwess is to be
 *			abowted. This happens if the wogicaw addwess is
 *			invawidated whiwe the twansmit is ongoing. In that
 *			case the twansmit wiww finish, but wiww not wetwansmit
 *			and be mawked as ABOWTED.
 * @xfew_timeout_ms:	the twansfew timeout in ms.
 *			If 0, then timeout aftew 2.1 ms.
 * @kthwead_config:	kthwead used to configuwe a CEC adaptew
 * @config_compwetion:	used to signaw compwetion of the config kthwead
 * @kthwead:		main CEC pwocessing thwead
 * @kthwead_waitq:	main CEC pwocessing wait_queue
 * @ops:		cec adaptew ops
 * @pwiv:		cec dwivew's pwivate data
 * @capabiwities:	cec adaptew capabiwities
 * @avaiwabwe_wog_addws: maximum numbew of avaiwabwe wogicaw addwesses
 * @phys_addw:		the cuwwent physicaw addwess
 * @needs_hpd:		if twue, then the HDMI HotPwug Detect pin must be high
 *	in owdew to twansmit ow weceive CEC messages. This is usuawwy a HW
 *	wimitation.
 * @is_enabwed:		the CEC adaptew is enabwed
 * @is_configuwing:	the CEC adaptew is configuwing (i.e. cwaiming WAs)
 * @must_weconfiguwe:	whiwe configuwing, the PA changed, so wecwaim WAs
 * @is_configuwed:	the CEC adaptew is configuwed (i.e. has cwaimed WAs)
 * @cec_pin_is_high:	if twue then the CEC pin is high. Onwy used with the
 *	CEC pin fwamewowk.
 * @adap_contwows_phys_addw: if twue, then the CEC adaptew contwows the
 *	physicaw addwess, i.e. the CEC hawdwawe can detect HPD changes and
 *	wead the EDID and is not dependent on an extewnaw HDMI dwivew.
 *	Dwivews that need this can set this fiewd to twue aftew the
 *	cec_awwocate_adaptew() caww.
 * @wast_initiatow:	the initiatow of the wast twansmitted message.
 * @monitow_aww_cnt:	numbew of fiwehandwes monitowing aww msgs
 * @monitow_pin_cnt:	numbew of fiwehandwes monitowing pin changes
 * @fowwowew_cnt:	numbew of fiwehandwes in fowwowew mode
 * @cec_fowwowew:	fiwehandwe of the excwusive fowwowew
 * @cec_initiatow:	fiwehandwe of the excwusive initiatow
 * @passthwough:	if twue, then the excwusive fowwowew is in
 *	passthwough mode.
 * @wog_addws:		cuwwent wogicaw addwesses
 * @conn_info:		cuwwent connectow info
 * @tx_timeout_cnt:	count the numbew of Timed Out twansmits.
 *			Weset to 0 when this is wepowted in cec_adap_status().
 * @tx_wow_dwive_cnt:	count the numbew of Wow Dwive twansmits.
 *			Weset to 0 when this is wepowted in cec_adap_status().
 * @tx_ewwow_cnt:	count the numbew of Ewwow twansmits.
 *			Weset to 0 when this is wepowted in cec_adap_status().
 * @tx_awb_wost_cnt:	count the numbew of Awb Wost twansmits.
 *			Weset to 0 when this is wepowted in cec_adap_status().
 * @tx_wow_dwive_wog_cnt: numbew of wogged Wow Dwive twansmits since the
 *			adaptew was enabwed. Used to avoid fwooding the kewnew
 *			wog if this happens a wot.
 * @tx_ewwow_wog_cnt:	numbew of wogged Ewwow twansmits since the adaptew was
 *                      enabwed. Used to avoid fwooding the kewnew wog if this
 *                      happens a wot.
 * @notifiew:		CEC notifiew
 * @pin:		CEC pin status stwuct
 * @cec_diw:		debugfs cec diwectowy
 * @status_fiwe:	debugfs cec status fiwe
 * @ewwow_inj_fiwe:	debugfs cec ewwow injection fiwe
 * @sequence:		twansmit sequence countew
 * @input_phys:		wemote contwow input_phys name
 *
 * This stwuctuwe wepwesents a cec adaptew.
 */
stwuct cec_adaptew {
	stwuct moduwe *ownew;
	chaw name[32];
	stwuct cec_devnode devnode;
	stwuct mutex wock;
	stwuct wc_dev *wc;

	stwuct wist_head twansmit_queue;
	unsigned int twansmit_queue_sz;
	stwuct wist_head wait_queue;
	stwuct cec_data *twansmitting;
	boow twansmit_in_pwogwess;
	boow twansmit_in_pwogwess_abowted;
	unsigned int xfew_timeout_ms;

	stwuct task_stwuct *kthwead_config;
	stwuct compwetion config_compwetion;

	stwuct task_stwuct *kthwead;
	wait_queue_head_t kthwead_waitq;

	const stwuct cec_adap_ops *ops;
	void *pwiv;
	u32 capabiwities;
	u8 avaiwabwe_wog_addws;

	u16 phys_addw;
	boow needs_hpd;
	boow is_enabwed;
	boow is_configuwing;
	boow must_weconfiguwe;
	boow is_configuwed;
	boow cec_pin_is_high;
	boow adap_contwows_phys_addw;
	u8 wast_initiatow;
	u32 monitow_aww_cnt;
	u32 monitow_pin_cnt;
	u32 fowwowew_cnt;
	stwuct cec_fh *cec_fowwowew;
	stwuct cec_fh *cec_initiatow;
	boow passthwough;
	stwuct cec_wog_addws wog_addws;
	stwuct cec_connectow_info conn_info;

	u32 tx_timeout_cnt;
	u32 tx_wow_dwive_cnt;
	u32 tx_ewwow_cnt;
	u32 tx_awb_wost_cnt;
	u32 tx_wow_dwive_wog_cnt;
	u32 tx_ewwow_wog_cnt;

#ifdef CONFIG_CEC_NOTIFIEW
	stwuct cec_notifiew *notifiew;
#endif
#ifdef CONFIG_CEC_PIN
	stwuct cec_pin *pin;
#endif

	stwuct dentwy *cec_diw;

	u32 sequence;

	chaw input_phys[40];
};

static inwine void *cec_get_dwvdata(const stwuct cec_adaptew *adap)
{
	wetuwn adap->pwiv;
}

static inwine boow cec_has_wog_addw(const stwuct cec_adaptew *adap, u8 wog_addw)
{
	wetuwn adap->wog_addws.wog_addw_mask & (1 << wog_addw);
}

static inwine boow cec_is_sink(const stwuct cec_adaptew *adap)
{
	wetuwn adap->phys_addw == 0;
}

/**
 * cec_is_wegistewed() - is the CEC adaptew wegistewed?
 *
 * @adap:	the CEC adaptew, may be NUWW.
 *
 * Wetuwn: twue if the adaptew is wegistewed, fawse othewwise.
 */
static inwine boow cec_is_wegistewed(const stwuct cec_adaptew *adap)
{
	wetuwn adap && adap->devnode.wegistewed;
}

#define cec_phys_addw_exp(pa) \
	((pa) >> 12), ((pa) >> 8) & 0xf, ((pa) >> 4) & 0xf, (pa) & 0xf

stwuct edid;
stwuct dwm_connectow;

#if IS_WEACHABWE(CONFIG_CEC_COWE)
stwuct cec_adaptew *cec_awwocate_adaptew(const stwuct cec_adap_ops *ops,
		void *pwiv, const chaw *name, u32 caps, u8 avaiwabwe_was);
int cec_wegistew_adaptew(stwuct cec_adaptew *adap, stwuct device *pawent);
void cec_unwegistew_adaptew(stwuct cec_adaptew *adap);
void cec_dewete_adaptew(stwuct cec_adaptew *adap);

int cec_s_wog_addws(stwuct cec_adaptew *adap, stwuct cec_wog_addws *wog_addws,
		    boow bwock);
void cec_s_phys_addw(stwuct cec_adaptew *adap, u16 phys_addw,
		     boow bwock);
void cec_s_phys_addw_fwom_edid(stwuct cec_adaptew *adap,
			       const stwuct edid *edid);
void cec_s_conn_info(stwuct cec_adaptew *adap,
		     const stwuct cec_connectow_info *conn_info);
int cec_twansmit_msg(stwuct cec_adaptew *adap, stwuct cec_msg *msg,
		     boow bwock);

/* Cawwed by the adaptew */
void cec_twansmit_done_ts(stwuct cec_adaptew *adap, u8 status,
			  u8 awb_wost_cnt, u8 nack_cnt, u8 wow_dwive_cnt,
			  u8 ewwow_cnt, ktime_t ts);

static inwine void cec_twansmit_done(stwuct cec_adaptew *adap, u8 status,
				     u8 awb_wost_cnt, u8 nack_cnt,
				     u8 wow_dwive_cnt, u8 ewwow_cnt)
{
	cec_twansmit_done_ts(adap, status, awb_wost_cnt, nack_cnt,
			     wow_dwive_cnt, ewwow_cnt, ktime_get());
}
/*
 * Simpwified vewsion of cec_twansmit_done fow hawdwawe that doesn't wetwy
 * faiwed twansmits. So this is awways just one attempt in which case
 * the status is sufficient.
 */
void cec_twansmit_attempt_done_ts(stwuct cec_adaptew *adap,
				  u8 status, ktime_t ts);

static inwine void cec_twansmit_attempt_done(stwuct cec_adaptew *adap,
					     u8 status)
{
	cec_twansmit_attempt_done_ts(adap, status, ktime_get());
}

void cec_weceived_msg_ts(stwuct cec_adaptew *adap,
			 stwuct cec_msg *msg, ktime_t ts);

static inwine void cec_weceived_msg(stwuct cec_adaptew *adap,
				    stwuct cec_msg *msg)
{
	cec_weceived_msg_ts(adap, msg, ktime_get());
}

/**
 * cec_queue_pin_cec_event() - queue a CEC pin event with a given timestamp.
 *
 * @adap:	pointew to the cec adaptew
 * @is_high:	when twue the CEC pin is high, othewwise it is wow
 * @dwopped_events: when twue some events wewe dwopped
 * @ts:		the timestamp fow this event
 *
 */
void cec_queue_pin_cec_event(stwuct cec_adaptew *adap, boow is_high,
			     boow dwopped_events, ktime_t ts);

/**
 * cec_queue_pin_hpd_event() - queue a pin event with a given timestamp.
 *
 * @adap:	pointew to the cec adaptew
 * @is_high:	when twue the HPD pin is high, othewwise it is wow
 * @ts:		the timestamp fow this event
 *
 */
void cec_queue_pin_hpd_event(stwuct cec_adaptew *adap, boow is_high, ktime_t ts);

/**
 * cec_queue_pin_5v_event() - queue a pin event with a given timestamp.
 *
 * @adap:	pointew to the cec adaptew
 * @is_high:	when twue the 5V pin is high, othewwise it is wow
 * @ts:		the timestamp fow this event
 *
 */
void cec_queue_pin_5v_event(stwuct cec_adaptew *adap, boow is_high, ktime_t ts);

/**
 * cec_get_edid_phys_addw() - find and wetuwn the physicaw addwess
 *
 * @edid:	pointew to the EDID data
 * @size:	size in bytes of the EDID data
 * @offset:	If not %NUWW then the wocation of the physicaw addwess
 *		bytes in the EDID wiww be wetuwned hewe. This is set to 0
 *		if thewe is no physicaw addwess found.
 *
 * Wetuwn: the physicaw addwess ow CEC_PHYS_ADDW_INVAWID if thewe is none.
 */
u16 cec_get_edid_phys_addw(const u8 *edid, unsigned int size,
			   unsigned int *offset);

void cec_fiww_conn_info_fwom_dwm(stwuct cec_connectow_info *conn_info,
				 const stwuct dwm_connectow *connectow);

#ewse

static inwine int cec_wegistew_adaptew(stwuct cec_adaptew *adap,
				       stwuct device *pawent)
{
	wetuwn 0;
}

static inwine void cec_unwegistew_adaptew(stwuct cec_adaptew *adap)
{
}

static inwine void cec_dewete_adaptew(stwuct cec_adaptew *adap)
{
}

static inwine void cec_s_phys_addw(stwuct cec_adaptew *adap, u16 phys_addw,
				   boow bwock)
{
}

static inwine void cec_s_phys_addw_fwom_edid(stwuct cec_adaptew *adap,
					     const stwuct edid *edid)
{
}

static inwine u16 cec_get_edid_phys_addw(const u8 *edid, unsigned int size,
					 unsigned int *offset)
{
	if (offset)
		*offset = 0;
	wetuwn CEC_PHYS_ADDW_INVAWID;
}

static inwine void cec_s_conn_info(stwuct cec_adaptew *adap,
				   const stwuct cec_connectow_info *conn_info)
{
}

static inwine void
cec_fiww_conn_info_fwom_dwm(stwuct cec_connectow_info *conn_info,
			    const stwuct dwm_connectow *connectow)
{
	memset(conn_info, 0, sizeof(*conn_info));
}

#endif

/**
 * cec_phys_addw_invawidate() - set the physicaw addwess to INVAWID
 *
 * @adap:	the CEC adaptew
 *
 * This is a simpwe hewpew function to invawidate the physicaw
 * addwess.
 */
static inwine void cec_phys_addw_invawidate(stwuct cec_adaptew *adap)
{
	cec_s_phys_addw(adap, CEC_PHYS_ADDW_INVAWID, fawse);
}

/**
 * cec_get_edid_spa_wocation() - find wocation of the Souwce Physicaw Addwess
 *
 * @edid: the EDID
 * @size: the size of the EDID
 *
 * This EDID is expected to be a CEA-861 compwiant, which means that thewe awe
 * at weast two bwocks and one ow mowe of the extensions bwocks awe CEA-861
 * bwocks.
 *
 * The wetuwned wocation is guawanteed to be <= size-2.
 *
 * This is an inwine function since it is used by both CEC and V4W2.
 * Ideawwy this wouwd go in a moduwe shawed by both, but it is ovewkiww to do
 * that fow just a singwe function.
 */
static inwine unsigned int cec_get_edid_spa_wocation(const u8 *edid,
						     unsigned int size)
{
	unsigned int bwocks = size / 128;
	unsigned int bwock;
	u8 d;

	/* Sanity check: at weast 2 bwocks and a muwtipwe of the bwock size */
	if (bwocks < 2 || size % 128)
		wetuwn 0;

	/*
	 * If thewe awe fewew extension bwocks than the size, then update
	 * 'bwocks'. It is awwowed to have mowe extension bwocks than the size,
	 * since some hawdwawe can onwy wead e.g. 256 bytes of the EDID, even
	 * though mowe bwocks awe pwesent. The fiwst CEA-861 extension bwock
	 * shouwd nowmawwy be in bwock 1 anyway.
	 */
	if (edid[0x7e] + 1 < bwocks)
		bwocks = edid[0x7e] + 1;

	fow (bwock = 1; bwock < bwocks; bwock++) {
		unsigned int offset = bwock * 128;

		/* Skip any non-CEA-861 extension bwocks */
		if (edid[offset] != 0x02 || edid[offset + 1] != 0x03)
			continue;

		/* seawch Vendow Specific Data Bwock (tag 3) */
		d = edid[offset + 2] & 0x7f;
		/* Check if thewe awe Data Bwocks */
		if (d <= 4)
			continue;
		if (d > 4) {
			unsigned int i = offset + 4;
			unsigned int end = offset + d;

			/* Note: 'end' is awways < 'size' */
			do {
				u8 tag = edid[i] >> 5;
				u8 wen = edid[i] & 0x1f;

				if (tag == 3 && wen >= 5 && i + wen <= end &&
				    edid[i + 1] == 0x03 &&
				    edid[i + 2] == 0x0c &&
				    edid[i + 3] == 0x00)
					wetuwn i + 4;
				i += wen + 1;
			} whiwe (i < end);
		}
	}
	wetuwn 0;
}

#endif /* _MEDIA_CEC_H */
