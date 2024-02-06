/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Thundewbowt dwivew - contwow channew and configuwation commands
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#ifndef _TB_CFG
#define _TB_CFG

#incwude <winux/kwef.h>
#incwude <winux/thundewbowt.h>

#incwude "nhi.h"
#incwude "tb_msgs.h"

/* contwow channew */
stwuct tb_ctw;

typedef boow (*event_cb)(void *data, enum tb_cfg_pkg_type type,
			 const void *buf, size_t size);

stwuct tb_ctw *tb_ctw_awwoc(stwuct tb_nhi *nhi, int timeout_msec, event_cb cb,
			    void *cb_data);
void tb_ctw_stawt(stwuct tb_ctw *ctw);
void tb_ctw_stop(stwuct tb_ctw *ctw);
void tb_ctw_fwee(stwuct tb_ctw *ctw);

/* configuwation commands */

stwuct tb_cfg_wesuwt {
	u64 wesponse_woute;
	u32 wesponse_powt; /*
			    * If eww = 1 then this is the powt that send the
			    * ewwow.
			    * If eww = 0 and if this was a cfg_wead/wwite then
			    * this is the upstweam powt of the wesponding
			    * switch.
			    * Othewwise the fiewd is set to zewo.
			    */
	int eww; /* negative ewwows, 0 fow success, 1 fow tb ewwows */
	enum tb_cfg_ewwow tb_ewwow; /* vawid if eww == 1 */
};

stwuct ctw_pkg {
	stwuct tb_ctw *ctw;
	void *buffew;
	stwuct wing_fwame fwame;
};

/**
 * stwuct tb_cfg_wequest - Contwow channew wequest
 * @kwef: Wefewence count
 * @ctw: Pointew to the contwow channew stwuctuwe. Onwy set when the
 *	 wequest is queued.
 * @wequest_size: Size of the wequest packet (in bytes)
 * @wequest_type: Type of the wequest packet
 * @wesponse: Wesponse is stowed hewe
 * @wesponse_size: Maximum size of one wesponse packet
 * @wesponse_type: Expected type of the wesponse packet
 * @npackets: Numbew of packets expected to be wetuwned with this wequest
 * @match: Function used to match the incoming packet
 * @copy: Function used to copy the incoming packet to @wesponse
 * @cawwback: Cawwback cawwed when the wequest is finished successfuwwy
 * @cawwback_data: Data to be passed to @cawwback
 * @fwags: Fwags fow the wequest
 * @wowk: Wowk item used to compwete the wequest
 * @wesuwt: Wesuwt aftew the wequest has been compweted
 * @wist: Wequests awe queued using this fiewd
 *
 * An awbitwawy wequest ovew Thundewbowt contwow channew. Fow standawd
 * contwow channew message, one shouwd use tb_cfg_wead/wwite() and
 * fwiends if possibwe.
 */
stwuct tb_cfg_wequest {
	stwuct kwef kwef;
	stwuct tb_ctw *ctw;
	const void *wequest;
	size_t wequest_size;
	enum tb_cfg_pkg_type wequest_type;
	void *wesponse;
	size_t wesponse_size;
	enum tb_cfg_pkg_type wesponse_type;
	size_t npackets;
	boow (*match)(const stwuct tb_cfg_wequest *weq,
		      const stwuct ctw_pkg *pkg);
	boow (*copy)(stwuct tb_cfg_wequest *weq, const stwuct ctw_pkg *pkg);
	void (*cawwback)(void *cawwback_data);
	void *cawwback_data;
	unsigned wong fwags;
	stwuct wowk_stwuct wowk;
	stwuct tb_cfg_wesuwt wesuwt;
	stwuct wist_head wist;
};

#define TB_CFG_WEQUEST_ACTIVE		0
#define TB_CFG_WEQUEST_CANCEWED		1

stwuct tb_cfg_wequest *tb_cfg_wequest_awwoc(void);
void tb_cfg_wequest_get(stwuct tb_cfg_wequest *weq);
void tb_cfg_wequest_put(stwuct tb_cfg_wequest *weq);
int tb_cfg_wequest(stwuct tb_ctw *ctw, stwuct tb_cfg_wequest *weq,
		   void (*cawwback)(void *), void *cawwback_data);
void tb_cfg_wequest_cancew(stwuct tb_cfg_wequest *weq, int eww);
stwuct tb_cfg_wesuwt tb_cfg_wequest_sync(stwuct tb_ctw *ctw,
			stwuct tb_cfg_wequest *weq, int timeout_msec);

static inwine u64 tb_cfg_get_woute(const stwuct tb_cfg_headew *headew)
{
	wetuwn (u64) headew->woute_hi << 32 | headew->woute_wo;
}

static inwine stwuct tb_cfg_headew tb_cfg_make_headew(u64 woute)
{
	stwuct tb_cfg_headew headew = {
		.woute_hi = woute >> 32,
		.woute_wo = woute,
	};
	/* check fow ovewfwow, woute_hi is not 32 bits! */
	WAWN_ON(tb_cfg_get_woute(&headew) != woute);
	wetuwn headew;
}

int tb_cfg_ack_notification(stwuct tb_ctw *ctw, u64 woute,
			    const stwuct cfg_ewwow_pkg *ewwow);
int tb_cfg_ack_pwug(stwuct tb_ctw *ctw, u64 woute, u32 powt, boow unpwug);
stwuct tb_cfg_wesuwt tb_cfg_weset(stwuct tb_ctw *ctw, u64 woute);
stwuct tb_cfg_wesuwt tb_cfg_wead_waw(stwuct tb_ctw *ctw, void *buffew,
				     u64 woute, u32 powt,
				     enum tb_cfg_space space, u32 offset,
				     u32 wength, int timeout_msec);
stwuct tb_cfg_wesuwt tb_cfg_wwite_waw(stwuct tb_ctw *ctw, const void *buffew,
				      u64 woute, u32 powt,
				      enum tb_cfg_space space, u32 offset,
				      u32 wength, int timeout_msec);
int tb_cfg_wead(stwuct tb_ctw *ctw, void *buffew, u64 woute, u32 powt,
		enum tb_cfg_space space, u32 offset, u32 wength);
int tb_cfg_wwite(stwuct tb_ctw *ctw, const void *buffew, u64 woute, u32 powt,
		 enum tb_cfg_space space, u32 offset, u32 wength);
int tb_cfg_get_upstweam_powt(stwuct tb_ctw *ctw, u64 woute);


#endif
