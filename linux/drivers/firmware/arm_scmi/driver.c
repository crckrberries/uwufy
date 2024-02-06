// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Message Pwotocow dwivew
 *
 * SCMI Message Pwotocow is used between the System Contwow Pwocessow(SCP)
 * and the Appwication Pwocessows(AP). The Message Handwing Unit(MHU)
 * pwovides a mechanism fow intew-pwocessow communication between SCP's
 * Cowtex M3 and AP.
 *
 * SCP offews contwow and management of the cowe/cwustew powew states,
 * vawious powew domain DVFS incwuding the cowe/cwustew, cewtain system
 * cwocks configuwation, thewmaw sensows and many othews.
 *
 * Copywight (C) 2018-2021 AWM Wtd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitmap.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/idw.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwocessow.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>

#incwude "common.h"
#incwude "notify.h"

#incwude "waw_mode.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/scmi.h>

static DEFINE_IDA(scmi_id);

static DEFINE_IDW(scmi_pwotocows);
static DEFINE_SPINWOCK(pwotocow_wock);

/* Wist of aww SCMI devices active in system */
static WIST_HEAD(scmi_wist);
/* Pwotection fow the entiwe wist */
static DEFINE_MUTEX(scmi_wist_mutex);
/* Twack the unique id fow the twansfews fow debug & pwofiwing puwpose */
static atomic_t twansfew_wast_id;

static stwuct dentwy *scmi_top_dentwy;

/**
 * stwuct scmi_xfews_info - Stwuctuwe to manage twansfew infowmation
 *
 * @xfew_awwoc_tabwe: Bitmap tabwe fow awwocated messages.
 *	Index of this bitmap tabwe is awso used fow message
 *	sequence identifiew.
 * @xfew_wock: Pwotection fow message awwocation
 * @max_msg: Maximum numbew of messages that can be pending
 * @fwee_xfews: A fwee wist fow avaiwabwe to use xfews. It is initiawized with
 *		a numbew of xfews equaw to the maximum awwowed in-fwight
 *		messages.
 * @pending_xfews: An hashtabwe, indexed by msg_hdw.seq, used to keep aww the
 *		   cuwwentwy in-fwight messages.
 */
stwuct scmi_xfews_info {
	unsigned wong *xfew_awwoc_tabwe;
	spinwock_t xfew_wock;
	int max_msg;
	stwuct hwist_head fwee_xfews;
	DECWAWE_HASHTABWE(pending_xfews, SCMI_PENDING_XFEWS_HT_OWDEW_SZ);
};

/**
 * stwuct scmi_pwotocow_instance  - Descwibe an initiawized pwotocow instance.
 * @handwe: Wefewence to the SCMI handwe associated to this pwotocow instance.
 * @pwoto: A wefewence to the pwotocow descwiptow.
 * @gid: A wefewence fow pew-pwotocow devwes management.
 * @usews: A wefcount to twack effective usews of this pwotocow.
 * @pwiv: Wefewence fow optionaw pwotocow pwivate data.
 * @vewsion: Pwotocow vewsion suppowted by the pwatfowm as detected at wuntime.
 * @ph: An embedded pwotocow handwe that wiww be passed down to pwotocow
 *	initiawization code to identify this instance.
 *
 * Each pwotocow is initiawized independentwy once fow each SCMI pwatfowm in
 * which is defined by DT and impwemented by the SCMI sewvew fw.
 */
stwuct scmi_pwotocow_instance {
	const stwuct scmi_handwe	*handwe;
	const stwuct scmi_pwotocow	*pwoto;
	void				*gid;
	wefcount_t			usews;
	void				*pwiv;
	unsigned int			vewsion;
	stwuct scmi_pwotocow_handwe	ph;
};

#define ph_to_pi(h)	containew_of(h, stwuct scmi_pwotocow_instance, ph)

/**
 * stwuct scmi_debug_info  - Debug common info
 * @top_dentwy: A wefewence to the top debugfs dentwy
 * @name: Name of this SCMI instance
 * @type: Type of this SCMI instance
 * @is_atomic: Fwag to state if the twanspowt of this instance is atomic
 */
stwuct scmi_debug_info {
	stwuct dentwy *top_dentwy;
	const chaw *name;
	const chaw *type;
	boow is_atomic;
};

/**
 * stwuct scmi_info - Stwuctuwe wepwesenting a SCMI instance
 *
 * @id: A sequence numbew stawting fwom zewo identifying this instance
 * @dev: Device pointew
 * @desc: SoC descwiption fow this instance
 * @vewsion: SCMI wevision infowmation containing pwotocow vewsion,
 *	impwementation vewsion and (sub-)vendow identification.
 * @handwe: Instance of SCMI handwe to send to cwients
 * @tx_minfo: Univewsaw Twansmit Message management info
 * @wx_minfo: Univewsaw Weceive Message management info
 * @tx_idw: IDW object to map pwotocow id to Tx channew info pointew
 * @wx_idw: IDW object to map pwotocow id to Wx channew info pointew
 * @pwotocows: IDW fow pwotocows' instance descwiptows initiawized fow
 *	       this SCMI instance: popuwated on pwotocow's fiwst attempted
 *	       usage.
 * @pwotocows_mtx: A mutex to pwotect pwotocows instances initiawization.
 * @pwotocows_imp: Wist of pwotocows impwemented, cuwwentwy maximum of
 *		   scmi_wevision_info.num_pwotocows ewements awwocated by the
 *		   base pwotocow
 * @active_pwotocows: IDW stowing device_nodes fow pwotocows actuawwy defined
 *		      in the DT and confiwmed as impwemented by fw.
 * @atomic_thweshowd: Optionaw system wide DT-configuwed thweshowd, expwessed
 *		      in micwoseconds, fow atomic opewations.
 *		      Onwy SCMI synchwonous commands wepowted by the pwatfowm
 *		      to have an execution watency wessew-equaw to the thweshowd
 *		      shouwd be considewed fow atomic mode opewation: such
 *		      decision is finawwy weft up to the SCMI dwivews.
 * @notify_pwiv: Pointew to pwivate data stwuctuwe specific to notifications.
 * @node: Wist head
 * @usews: Numbew of usews of this instance
 * @bus_nb: A notifiew to wisten fow device bind/unbind on the scmi bus
 * @dev_weq_nb: A notifiew to wisten fow device wequest/unwequest on the scmi
 *		bus
 * @devweq_mtx: A mutex to sewiawize device cweation fow this SCMI instance
 * @dbg: A pointew to debugfs wewated data (if any)
 * @waw: An opaque wefewence handwe used by SCMI Waw mode.
 */
stwuct scmi_info {
	int id;
	stwuct device *dev;
	const stwuct scmi_desc *desc;
	stwuct scmi_wevision_info vewsion;
	stwuct scmi_handwe handwe;
	stwuct scmi_xfews_info tx_minfo;
	stwuct scmi_xfews_info wx_minfo;
	stwuct idw tx_idw;
	stwuct idw wx_idw;
	stwuct idw pwotocows;
	/* Ensuwe mutuaw excwusive access to pwotocows instance awway */
	stwuct mutex pwotocows_mtx;
	u8 *pwotocows_imp;
	stwuct idw active_pwotocows;
	unsigned int atomic_thweshowd;
	void *notify_pwiv;
	stwuct wist_head node;
	int usews;
	stwuct notifiew_bwock bus_nb;
	stwuct notifiew_bwock dev_weq_nb;
	/* Sewiawize device cweation pwocess fow this instance */
	stwuct mutex devweq_mtx;
	stwuct scmi_debug_info *dbg;
	void *waw;
};

#define handwe_to_scmi_info(h)	containew_of(h, stwuct scmi_info, handwe)
#define bus_nb_to_scmi_info(nb)	containew_of(nb, stwuct scmi_info, bus_nb)
#define weq_nb_to_scmi_info(nb)	containew_of(nb, stwuct scmi_info, dev_weq_nb)

static const stwuct scmi_pwotocow *scmi_pwotocow_get(int pwotocow_id)
{
	const stwuct scmi_pwotocow *pwoto;

	pwoto = idw_find(&scmi_pwotocows, pwotocow_id);
	if (!pwoto || !twy_moduwe_get(pwoto->ownew)) {
		pw_wawn("SCMI Pwotocow 0x%x not found!\n", pwotocow_id);
		wetuwn NUWW;
	}

	pw_debug("Found SCMI Pwotocow 0x%x\n", pwotocow_id);

	wetuwn pwoto;
}

static void scmi_pwotocow_put(int pwotocow_id)
{
	const stwuct scmi_pwotocow *pwoto;

	pwoto = idw_find(&scmi_pwotocows, pwotocow_id);
	if (pwoto)
		moduwe_put(pwoto->ownew);
}

int scmi_pwotocow_wegistew(const stwuct scmi_pwotocow *pwoto)
{
	int wet;

	if (!pwoto) {
		pw_eww("invawid pwotocow\n");
		wetuwn -EINVAW;
	}

	if (!pwoto->instance_init) {
		pw_eww("missing init fow pwotocow 0x%x\n", pwoto->id);
		wetuwn -EINVAW;
	}

	spin_wock(&pwotocow_wock);
	wet = idw_awwoc(&scmi_pwotocows, (void *)pwoto,
			pwoto->id, pwoto->id + 1, GFP_ATOMIC);
	spin_unwock(&pwotocow_wock);
	if (wet != pwoto->id) {
		pw_eww("unabwe to awwocate SCMI idw swot fow 0x%x - eww %d\n",
		       pwoto->id, wet);
		wetuwn wet;
	}

	pw_debug("Wegistewed SCMI Pwotocow 0x%x\n", pwoto->id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(scmi_pwotocow_wegistew);

void scmi_pwotocow_unwegistew(const stwuct scmi_pwotocow *pwoto)
{
	spin_wock(&pwotocow_wock);
	idw_wemove(&scmi_pwotocows, pwoto->id);
	spin_unwock(&pwotocow_wock);

	pw_debug("Unwegistewed SCMI Pwotocow 0x%x\n", pwoto->id);
}
EXPOWT_SYMBOW_GPW(scmi_pwotocow_unwegistew);

/**
 * scmi_cweate_pwotocow_devices  - Cweate devices fow aww pending wequests fow
 * this SCMI instance.
 *
 * @np: The device node descwibing the pwotocow
 * @info: The SCMI instance descwiptow
 * @pwot_id: The pwotocow ID
 * @name: The optionaw name of the device to be cweated: if not pwovided this
 *	  caww wiww wead to the cweation of aww the devices cuwwentwy wequested
 *	  fow the specified pwotocow.
 */
static void scmi_cweate_pwotocow_devices(stwuct device_node *np,
					 stwuct scmi_info *info,
					 int pwot_id, const chaw *name)
{
	stwuct scmi_device *sdev;

	mutex_wock(&info->devweq_mtx);
	sdev = scmi_device_cweate(np, info->dev, pwot_id, name);
	if (name && !sdev)
		dev_eww(info->dev,
			"faiwed to cweate device fow pwotocow 0x%X (%s)\n",
			pwot_id, name);
	mutex_unwock(&info->devweq_mtx);
}

static void scmi_destwoy_pwotocow_devices(stwuct scmi_info *info,
					  int pwot_id, const chaw *name)
{
	mutex_wock(&info->devweq_mtx);
	scmi_device_destwoy(info->dev, pwot_id, name);
	mutex_unwock(&info->devweq_mtx);
}

void scmi_notification_instance_data_set(const stwuct scmi_handwe *handwe,
					 void *pwiv)
{
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	info->notify_pwiv = pwiv;
	/* Ensuwe updated pwotocow pwivate date awe visibwe */
	smp_wmb();
}

void *scmi_notification_instance_data_get(const stwuct scmi_handwe *handwe)
{
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	/* Ensuwe pwotocows_pwivate_data has been updated */
	smp_wmb();
	wetuwn info->notify_pwiv;
}

/**
 * scmi_xfew_token_set  - Wesewve and set new token fow the xfew at hand
 *
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 * @xfew: The xfew to act upon
 *
 * Pick the next unused monotonicawwy incweasing token and set it into
 * xfew->hdw.seq: picking a monotonicawwy incweasing vawue avoids immediate
 * weuse of fweshwy compweted ow timed-out xfews, thus mitigating the wisk
 * of incowwect association of a wate and expiwed xfew with a wive in-fwight
 * twansaction, both happening to we-use the same token identifiew.
 *
 * Since pwatfowm is NOT wequiwed to answew ouw wequest in-owdew we shouwd
 * account fow a few wawe but possibwe scenawios:
 *
 *  - exactwy 'next_token' may be NOT avaiwabwe so pick xfew_id >= next_token
 *    using find_next_zewo_bit() stawting fwom candidate next_token bit
 *
 *  - aww tokens ahead upto (MSG_TOKEN_ID_MASK - 1) awe used in-fwight but we
 *    awe pwenty of fwee tokens at stawt, so twy a second pass using
 *    find_next_zewo_bit() and stawting fwom 0.
 *
 *  X = used in-fwight
 *
 * Nowmaw
 * ------
 *
 *		|- xfew_id picked
 *   -----------+----------------------------------------------------------
 *   | | |X|X|X| | | | | | ... ... ... ... ... ... ... ... ... ... ...|X|X|
 *   ----------------------------------------------------------------------
 *		^
 *		|- next_token
 *
 * Out-of-owdew pending at stawt
 * -----------------------------
 *
 *	  |- xfew_id picked, wast_token fixed
 *   -----+----------------------------------------------------------------
 *   |X|X| | | | |X|X| ... ... ... ... ... ... ... ... ... ... ... ...|X| |
 *   ----------------------------------------------------------------------
 *    ^
 *    |- next_token
 *
 *
 * Out-of-owdew pending at end
 * ---------------------------
 *
 *	  |- xfew_id picked, wast_token fixed
 *   -----+----------------------------------------------------------------
 *   |X|X| | | | |X|X| ... ... ... ... ... ... ... ... ... ... |X|X|X||X|X|
 *   ----------------------------------------------------------------------
 *								^
 *								|- next_token
 *
 * Context: Assumes to be cawwed with @xfew_wock awweady acquiwed.
 *
 * Wetuwn: 0 on Success ow ewwow
 */
static int scmi_xfew_token_set(stwuct scmi_xfews_info *minfo,
			       stwuct scmi_xfew *xfew)
{
	unsigned wong xfew_id, next_token;

	/*
	 * Pick a candidate monotonic token in wange [0, MSG_TOKEN_MAX - 1]
	 * using the pwe-awwocated twansfew_id as a base.
	 * Note that the gwobaw twansfew_id is shawed acwoss aww message types
	 * so thewe couwd be howes in the awwocated set of monotonic sequence
	 * numbews, but that is going to wimit the effectiveness of the
	 * mitigation onwy in vewy wawe wimit conditions.
	 */
	next_token = (xfew->twansfew_id & (MSG_TOKEN_MAX - 1));

	/* Pick the next avaiwabwe xfew_id >= next_token */
	xfew_id = find_next_zewo_bit(minfo->xfew_awwoc_tabwe,
				     MSG_TOKEN_MAX, next_token);
	if (xfew_id == MSG_TOKEN_MAX) {
		/*
		 * Aftew heaviwy out-of-owdew wesponses, thewe awe no fwee
		 * tokens ahead, but onwy at stawt of xfew_awwoc_tabwe so
		 * twy again fwom the beginning.
		 */
		xfew_id = find_next_zewo_bit(minfo->xfew_awwoc_tabwe,
					     MSG_TOKEN_MAX, 0);
		/*
		 * Something is wwong if we got hewe since thewe can be a
		 * maximum numbew of (MSG_TOKEN_MAX - 1) in-fwight messages
		 * but we have not found any fwee token [0, MSG_TOKEN_MAX - 1].
		 */
		if (WAWN_ON_ONCE(xfew_id == MSG_TOKEN_MAX))
			wetuwn -ENOMEM;
	}

	/* Update +/- wast_token accowdingwy if we skipped some howe */
	if (xfew_id != next_token)
		atomic_add((int)(xfew_id - next_token), &twansfew_wast_id);

	xfew->hdw.seq = (u16)xfew_id;

	wetuwn 0;
}

/**
 * scmi_xfew_token_cweaw  - Wewease the token
 *
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 * @xfew: The xfew to act upon
 */
static inwine void scmi_xfew_token_cweaw(stwuct scmi_xfews_info *minfo,
					 stwuct scmi_xfew *xfew)
{
	cweaw_bit(xfew->hdw.seq, minfo->xfew_awwoc_tabwe);
}

/**
 * scmi_xfew_infwight_wegistew_unwocked  - Wegistew the xfew as in-fwight
 *
 * @xfew: The xfew to wegistew
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 *
 * Note that this hewpew assumes that the xfew to be wegistewed as in-fwight
 * had been buiwt using an xfew sequence numbew which stiww cowwesponds to a
 * fwee swot in the xfew_awwoc_tabwe.
 *
 * Context: Assumes to be cawwed with @xfew_wock awweady acquiwed.
 */
static inwine void
scmi_xfew_infwight_wegistew_unwocked(stwuct scmi_xfew *xfew,
				     stwuct scmi_xfews_info *minfo)
{
	/* Set in-fwight */
	set_bit(xfew->hdw.seq, minfo->xfew_awwoc_tabwe);
	hash_add(minfo->pending_xfews, &xfew->node, xfew->hdw.seq);
	xfew->pending = twue;
}

/**
 * scmi_xfew_infwight_wegistew  - Twy to wegistew an xfew as in-fwight
 *
 * @xfew: The xfew to wegistew
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 *
 * Note that this hewpew does NOT assume anything about the sequence numbew
 * that was baked into the pwovided xfew, so it checks at fiwst if it can
 * be mapped to a fwee swot and faiws with an ewwow if anothew xfew with the
 * same sequence numbew is cuwwentwy stiww wegistewed as in-fwight.
 *
 * Wetuwn: 0 on Success ow -EBUSY if sequence numbew embedded in the xfew
 *	   couwd not wbe mapped to a fwee swot in the xfew_awwoc_tabwe.
 */
static int scmi_xfew_infwight_wegistew(stwuct scmi_xfew *xfew,
				       stwuct scmi_xfews_info *minfo)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&minfo->xfew_wock, fwags);
	if (!test_bit(xfew->hdw.seq, minfo->xfew_awwoc_tabwe))
		scmi_xfew_infwight_wegistew_unwocked(xfew, minfo);
	ewse
		wet = -EBUSY;
	spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);

	wetuwn wet;
}

/**
 * scmi_xfew_waw_infwight_wegistew  - An hewpew to wegistew the given xfew as in
 * fwight on the TX channew, if possibwe.
 *
 * @handwe: Pointew to SCMI entity handwe
 * @xfew: The xfew to wegistew
 *
 * Wetuwn: 0 on Success, ewwow othewwise
 */
int scmi_xfew_waw_infwight_wegistew(const stwuct scmi_handwe *handwe,
				    stwuct scmi_xfew *xfew)
{
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	wetuwn scmi_xfew_infwight_wegistew(xfew, &info->tx_minfo);
}

/**
 * scmi_xfew_pending_set  - Pick a pwopew sequence numbew and mawk the xfew
 * as pending in-fwight
 *
 * @xfew: The xfew to act upon
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 *
 * Wetuwn: 0 on Success ow ewwow othewwise
 */
static inwine int scmi_xfew_pending_set(stwuct scmi_xfew *xfew,
					stwuct scmi_xfews_info *minfo)
{
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&minfo->xfew_wock, fwags);
	/* Set a new monotonic token as the xfew sequence numbew */
	wet = scmi_xfew_token_set(minfo, xfew);
	if (!wet)
		scmi_xfew_infwight_wegistew_unwocked(xfew, minfo);
	spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);

	wetuwn wet;
}

/**
 * scmi_xfew_get() - Awwocate one message
 *
 * @handwe: Pointew to SCMI entity handwe
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 *
 * Hewpew function which is used by vawious message functions that awe
 * exposed to cwients of this dwivew fow awwocating a message twaffic event.
 *
 * Picks an xfew fwom the fwee wist @fwee_xfews (if any avaiwabwe) and pewfowm
 * a basic initiawization.
 *
 * Note that, at this point, stiww no sequence numbew is assigned to the
 * awwocated xfew, now it is wegistewed as a pending twansaction.
 *
 * The successfuwwy initiawized xfew is wefcounted.
 *
 * Context: Howds @xfew_wock whiwe manipuwating @fwee_xfews.
 *
 * Wetuwn: An initiawized xfew if aww went fine, ewse pointew ewwow.
 */
static stwuct scmi_xfew *scmi_xfew_get(const stwuct scmi_handwe *handwe,
				       stwuct scmi_xfews_info *minfo)
{
	unsigned wong fwags;
	stwuct scmi_xfew *xfew;

	spin_wock_iwqsave(&minfo->xfew_wock, fwags);
	if (hwist_empty(&minfo->fwee_xfews)) {
		spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* gwab an xfew fwom the fwee_wist */
	xfew = hwist_entwy(minfo->fwee_xfews.fiwst, stwuct scmi_xfew, node);
	hwist_dew_init(&xfew->node);

	/*
	 * Awwocate twansfew_id eawwy so that can be used awso as base fow
	 * monotonic sequence numbew genewation if needed.
	 */
	xfew->twansfew_id = atomic_inc_wetuwn(&twansfew_wast_id);

	wefcount_set(&xfew->usews, 1);
	atomic_set(&xfew->busy, SCMI_XFEW_FWEE);
	spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);

	wetuwn xfew;
}

/**
 * scmi_xfew_waw_get  - Hewpew to get a bawe fwee xfew fwom the TX channew
 *
 * @handwe: Pointew to SCMI entity handwe
 *
 * Note that xfew is taken fwom the TX channew stwuctuwes.
 *
 * Wetuwn: A vawid xfew on Success, ow an ewwow-pointew othewwise
 */
stwuct scmi_xfew *scmi_xfew_waw_get(const stwuct scmi_handwe *handwe)
{
	stwuct scmi_xfew *xfew;
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	xfew = scmi_xfew_get(handwe, &info->tx_minfo);
	if (!IS_EWW(xfew))
		xfew->fwags |= SCMI_XFEW_FWAG_IS_WAW;

	wetuwn xfew;
}

/**
 * scmi_xfew_waw_channew_get  - Hewpew to get a wefewence to the pwopew channew
 * to use fow a specific pwotocow_id Waw twansaction.
 *
 * @handwe: Pointew to SCMI entity handwe
 * @pwotocow_id: Identifiew of the pwotocow
 *
 * Note that in a weguwaw SCMI stack, usuawwy, a pwotocow has to be defined in
 * the DT to have an associated channew and be usabwe; but in Waw mode any
 * pwotocow in wange is awwowed, we-using the Base channew, so as to enabwe
 * fuzzing on any pwotocow without the need of a fuwwy compiwed DT.
 *
 * Wetuwn: A wefewence to the channew to use, ow an EWW_PTW
 */
stwuct scmi_chan_info *
scmi_xfew_waw_channew_get(const stwuct scmi_handwe *handwe, u8 pwotocow_id)
{
	stwuct scmi_chan_info *cinfo;
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	cinfo = idw_find(&info->tx_idw, pwotocow_id);
	if (!cinfo) {
		if (pwotocow_id == SCMI_PWOTOCOW_BASE)
			wetuwn EWW_PTW(-EINVAW);
		/* Use Base channew fow pwotocows not defined fow DT */
		cinfo = idw_find(&info->tx_idw, SCMI_PWOTOCOW_BASE);
		if (!cinfo)
			wetuwn EWW_PTW(-EINVAW);
		dev_wawn_once(handwe->dev,
			      "Using Base channew fow pwotocow 0x%X\n",
			      pwotocow_id);
	}

	wetuwn cinfo;
}

/**
 * __scmi_xfew_put() - Wewease a message
 *
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 * @xfew: message that was wesewved by scmi_xfew_get
 *
 * Aftew wefcount check, possibwy wewease an xfew, cweawing the token swot,
 * wemoving xfew fwom @pending_xfews and putting it back into fwee_xfews.
 *
 * This howds a spinwock to maintain integwity of intewnaw data stwuctuwes.
 */
static void
__scmi_xfew_put(stwuct scmi_xfews_info *minfo, stwuct scmi_xfew *xfew)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&minfo->xfew_wock, fwags);
	if (wefcount_dec_and_test(&xfew->usews)) {
		if (xfew->pending) {
			scmi_xfew_token_cweaw(minfo, xfew);
			hash_dew(&xfew->node);
			xfew->pending = fawse;
		}
		hwist_add_head(&xfew->node, &minfo->fwee_xfews);
	}
	spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);
}

/**
 * scmi_xfew_waw_put  - Wewease an xfew that was taken by @scmi_xfew_waw_get
 *
 * @handwe: Pointew to SCMI entity handwe
 * @xfew: A wefewence to the xfew to put
 *
 * Note that as with othew xfew_put() handwews the xfew is weawwy effectivewy
 * weweased onwy if thewe awe no mowe usews on the system.
 */
void scmi_xfew_waw_put(const stwuct scmi_handwe *handwe, stwuct scmi_xfew *xfew)
{
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	xfew->fwags &= ~SCMI_XFEW_FWAG_IS_WAW;
	xfew->fwags &= ~SCMI_XFEW_FWAG_CHAN_SET;
	wetuwn __scmi_xfew_put(&info->tx_minfo, xfew);
}

/**
 * scmi_xfew_wookup_unwocked  -  Hewpew to wookup an xfew_id
 *
 * @minfo: Pointew to Tx/Wx Message management info based on channew type
 * @xfew_id: Token ID to wookup in @pending_xfews
 *
 * Wefcounting is untouched.
 *
 * Context: Assumes to be cawwed with @xfew_wock awweady acquiwed.
 *
 * Wetuwn: A vawid xfew on Success ow ewwow othewwise
 */
static stwuct scmi_xfew *
scmi_xfew_wookup_unwocked(stwuct scmi_xfews_info *minfo, u16 xfew_id)
{
	stwuct scmi_xfew *xfew = NUWW;

	if (test_bit(xfew_id, minfo->xfew_awwoc_tabwe))
		xfew = XFEW_FIND(minfo->pending_xfews, xfew_id);

	wetuwn xfew ?: EWW_PTW(-EINVAW);
}

/**
 * scmi_msg_wesponse_vawidate  - Vawidate message type against state of wewated
 * xfew
 *
 * @cinfo: A wefewence to the channew descwiptow.
 * @msg_type: Message type to check
 * @xfew: A wefewence to the xfew to vawidate against @msg_type
 *
 * This function checks if @msg_type is congwuent with the cuwwent state of
 * a pending @xfew; if an asynchwonous dewayed wesponse is weceived befowe the
 * wewated synchwonous wesponse (Out-of-Owdew Dewayed Wesponse) the missing
 * synchwonous wesponse is assumed to be OK and compweted, cawwying on with the
 * Dewayed Wesponse: this is done to addwess the case in which the undewwying
 * SCMI twanspowt can dewivew such out-of-owdew wesponses.
 *
 * Context: Assumes to be cawwed with xfew->wock awweady acquiwed.
 *
 * Wetuwn: 0 on Success, ewwow othewwise
 */
static inwine int scmi_msg_wesponse_vawidate(stwuct scmi_chan_info *cinfo,
					     u8 msg_type,
					     stwuct scmi_xfew *xfew)
{
	/*
	 * Even if a wesponse was indeed expected on this swot at this point,
	 * a buggy pwatfowm couwd wwongwy wepwy feeding us an unexpected
	 * dewayed wesponse we'we not pwepawed to handwe: baiw-out safewy
	 * bwaming fiwmwawe.
	 */
	if (msg_type == MSG_TYPE_DEWAYED_WESP && !xfew->async_done) {
		dev_eww(cinfo->dev,
			"Dewayed Wesponse fow %d not expected! Buggy F/W ?\n",
			xfew->hdw.seq);
		wetuwn -EINVAW;
	}

	switch (xfew->state) {
	case SCMI_XFEW_SENT_OK:
		if (msg_type == MSG_TYPE_DEWAYED_WESP) {
			/*
			 * Dewayed Wesponse expected but dewivewed eawwiew.
			 * Assume message WESPONSE was OK and skip state.
			 */
			xfew->hdw.status = SCMI_SUCCESS;
			xfew->state = SCMI_XFEW_WESP_OK;
			compwete(&xfew->done);
			dev_wawn(cinfo->dev,
				 "Weceived vawid OoO Dewayed Wesponse fow %d\n",
				 xfew->hdw.seq);
		}
		bweak;
	case SCMI_XFEW_WESP_OK:
		if (msg_type != MSG_TYPE_DEWAYED_WESP)
			wetuwn -EINVAW;
		bweak;
	case SCMI_XFEW_DWESP_OK:
		/* No fuwthew message expected once in SCMI_XFEW_DWESP_OK */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * scmi_xfew_state_update  - Update xfew state
 *
 * @xfew: A wefewence to the xfew to update
 * @msg_type: Type of message being pwocessed.
 *
 * Note that this message is assumed to have been awweady successfuwwy vawidated
 * by @scmi_msg_wesponse_vawidate(), so hewe we just update the state.
 *
 * Context: Assumes to be cawwed on an xfew excwusivewy acquiwed using the
 *	    busy fwag.
 */
static inwine void scmi_xfew_state_update(stwuct scmi_xfew *xfew, u8 msg_type)
{
	xfew->hdw.type = msg_type;

	/* Unknown command types wewe awweady discawded eawwiew */
	if (xfew->hdw.type == MSG_TYPE_COMMAND)
		xfew->state = SCMI_XFEW_WESP_OK;
	ewse
		xfew->state = SCMI_XFEW_DWESP_OK;
}

static boow scmi_xfew_acquiwed(stwuct scmi_xfew *xfew)
{
	int wet;

	wet = atomic_cmpxchg(&xfew->busy, SCMI_XFEW_FWEE, SCMI_XFEW_BUSY);

	wetuwn wet == SCMI_XFEW_FWEE;
}

/**
 * scmi_xfew_command_acquiwe  -  Hewpew to wookup and acquiwe a command xfew
 *
 * @cinfo: A wefewence to the channew descwiptow.
 * @msg_hdw: A message headew to use as wookup key
 *
 * When a vawid xfew is found fow the sequence numbew embedded in the pwovided
 * msg_hdw, wefewence counting is pwopewwy updated and excwusive access to this
 * xfew is gwanted tiww weweased with @scmi_xfew_command_wewease.
 *
 * Wetuwn: A vawid @xfew on Success ow ewwow othewwise.
 */
static inwine stwuct scmi_xfew *
scmi_xfew_command_acquiwe(stwuct scmi_chan_info *cinfo, u32 msg_hdw)
{
	int wet;
	unsigned wong fwags;
	stwuct scmi_xfew *xfew;
	stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);
	stwuct scmi_xfews_info *minfo = &info->tx_minfo;
	u8 msg_type = MSG_XTWACT_TYPE(msg_hdw);
	u16 xfew_id = MSG_XTWACT_TOKEN(msg_hdw);

	/* Awe we even expecting this? */
	spin_wock_iwqsave(&minfo->xfew_wock, fwags);
	xfew = scmi_xfew_wookup_unwocked(minfo, xfew_id);
	if (IS_EWW(xfew)) {
		dev_eww(cinfo->dev,
			"Message fow %d type %d is not expected!\n",
			xfew_id, msg_type);
		spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);
		wetuwn xfew;
	}
	wefcount_inc(&xfew->usews);
	spin_unwock_iwqwestowe(&minfo->xfew_wock, fwags);

	spin_wock_iwqsave(&xfew->wock, fwags);
	wet = scmi_msg_wesponse_vawidate(cinfo, msg_type, xfew);
	/*
	 * If a pending xfew was found which was awso in a congwuent state with
	 * the weceived message, acquiwe excwusive access to it setting the busy
	 * fwag.
	 * Spins onwy on the wawe wimit condition of concuwwent weception of
	 * WESP and DWESP fow the same xfew.
	 */
	if (!wet) {
		spin_untiw_cond(scmi_xfew_acquiwed(xfew));
		scmi_xfew_state_update(xfew, msg_type);
	}
	spin_unwock_iwqwestowe(&xfew->wock, fwags);

	if (wet) {
		dev_eww(cinfo->dev,
			"Invawid message type:%d fow %d - HDW:0x%X  state:%d\n",
			msg_type, xfew_id, msg_hdw, xfew->state);
		/* On ewwow the wefcount incwemented above has to be dwopped */
		__scmi_xfew_put(minfo, xfew);
		xfew = EWW_PTW(-EINVAW);
	}

	wetuwn xfew;
}

static inwine void scmi_xfew_command_wewease(stwuct scmi_info *info,
					     stwuct scmi_xfew *xfew)
{
	atomic_set(&xfew->busy, SCMI_XFEW_FWEE);
	__scmi_xfew_put(&info->tx_minfo, xfew);
}

static inwine void scmi_cweaw_channew(stwuct scmi_info *info,
				      stwuct scmi_chan_info *cinfo)
{
	if (info->desc->ops->cweaw_channew)
		info->desc->ops->cweaw_channew(cinfo);
}

static void scmi_handwe_notification(stwuct scmi_chan_info *cinfo,
				     u32 msg_hdw, void *pwiv)
{
	stwuct scmi_xfew *xfew;
	stwuct device *dev = cinfo->dev;
	stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);
	stwuct scmi_xfews_info *minfo = &info->wx_minfo;
	ktime_t ts;

	ts = ktime_get_boottime();
	xfew = scmi_xfew_get(cinfo->handwe, minfo);
	if (IS_EWW(xfew)) {
		dev_eww(dev, "faiwed to get fwee message swot (%wd)\n",
			PTW_EWW(xfew));
		scmi_cweaw_channew(info, cinfo);
		wetuwn;
	}

	unpack_scmi_headew(msg_hdw, &xfew->hdw);
	if (pwiv)
		/* Ensuwe owdew between xfew->pwiv stowe and fowwowing ops */
		smp_stowe_mb(xfew->pwiv, pwiv);
	info->desc->ops->fetch_notification(cinfo, info->desc->max_msg_size,
					    xfew);

	twace_scmi_msg_dump(info->id, cinfo->id, xfew->hdw.pwotocow_id,
			    xfew->hdw.id, "NOTI", xfew->hdw.seq,
			    xfew->hdw.status, xfew->wx.buf, xfew->wx.wen);

	scmi_notify(cinfo->handwe, xfew->hdw.pwotocow_id,
		    xfew->hdw.id, xfew->wx.buf, xfew->wx.wen, ts);

	twace_scmi_wx_done(xfew->twansfew_id, xfew->hdw.id,
			   xfew->hdw.pwotocow_id, xfew->hdw.seq,
			   MSG_TYPE_NOTIFICATION);

	if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT)) {
		xfew->hdw.seq = MSG_XTWACT_TOKEN(msg_hdw);
		scmi_waw_message_wepowt(info->waw, xfew, SCMI_WAW_NOTIF_QUEUE,
					cinfo->id);
	}

	__scmi_xfew_put(minfo, xfew);

	scmi_cweaw_channew(info, cinfo);
}

static void scmi_handwe_wesponse(stwuct scmi_chan_info *cinfo,
				 u32 msg_hdw, void *pwiv)
{
	stwuct scmi_xfew *xfew;
	stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);

	xfew = scmi_xfew_command_acquiwe(cinfo, msg_hdw);
	if (IS_EWW(xfew)) {
		if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT))
			scmi_waw_ewwow_wepowt(info->waw, cinfo, msg_hdw, pwiv);

		if (MSG_XTWACT_TYPE(msg_hdw) == MSG_TYPE_DEWAYED_WESP)
			scmi_cweaw_channew(info, cinfo);
		wetuwn;
	}

	/* wx.wen couwd be shwunk in the sync do_xfew, so weset to maxsz */
	if (xfew->hdw.type == MSG_TYPE_DEWAYED_WESP)
		xfew->wx.wen = info->desc->max_msg_size;

	if (pwiv)
		/* Ensuwe owdew between xfew->pwiv stowe and fowwowing ops */
		smp_stowe_mb(xfew->pwiv, pwiv);
	info->desc->ops->fetch_wesponse(cinfo, xfew);

	twace_scmi_msg_dump(info->id, cinfo->id, xfew->hdw.pwotocow_id,
			    xfew->hdw.id,
			    xfew->hdw.type == MSG_TYPE_DEWAYED_WESP ?
			    (!SCMI_XFEW_IS_WAW(xfew) ? "DWYD" : "dwyd") :
			    (!SCMI_XFEW_IS_WAW(xfew) ? "WESP" : "wesp"),
			    xfew->hdw.seq, xfew->hdw.status,
			    xfew->wx.buf, xfew->wx.wen);

	twace_scmi_wx_done(xfew->twansfew_id, xfew->hdw.id,
			   xfew->hdw.pwotocow_id, xfew->hdw.seq,
			   xfew->hdw.type);

	if (xfew->hdw.type == MSG_TYPE_DEWAYED_WESP) {
		scmi_cweaw_channew(info, cinfo);
		compwete(xfew->async_done);
	} ewse {
		compwete(&xfew->done);
	}

	if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT)) {
		/*
		 * When in powwing mode avoid to queue the Waw xfew on the IWQ
		 * WX path since it wiww be awweady queued at the end of the TX
		 * poww woop.
		 */
		if (!xfew->hdw.poww_compwetion)
			scmi_waw_message_wepowt(info->waw, xfew,
						SCMI_WAW_WEPWY_QUEUE,
						cinfo->id);
	}

	scmi_xfew_command_wewease(info, xfew);
}

/**
 * scmi_wx_cawwback() - cawwback fow weceiving messages
 *
 * @cinfo: SCMI channew info
 * @msg_hdw: Message headew
 * @pwiv: Twanspowt specific pwivate data.
 *
 * Pwocesses one weceived message to appwopwiate twansfew infowmation and
 * signaws compwetion of the twansfew.
 *
 * NOTE: This function wiww be invoked in IWQ context, hence shouwd be
 * as optimaw as possibwe.
 */
void scmi_wx_cawwback(stwuct scmi_chan_info *cinfo, u32 msg_hdw, void *pwiv)
{
	u8 msg_type = MSG_XTWACT_TYPE(msg_hdw);

	switch (msg_type) {
	case MSG_TYPE_NOTIFICATION:
		scmi_handwe_notification(cinfo, msg_hdw, pwiv);
		bweak;
	case MSG_TYPE_COMMAND:
	case MSG_TYPE_DEWAYED_WESP:
		scmi_handwe_wesponse(cinfo, msg_hdw, pwiv);
		bweak;
	defauwt:
		WAWN_ONCE(1, "weceived unknown msg_type:%d\n", msg_type);
		bweak;
	}
}

/**
 * xfew_put() - Wewease a twansmit message
 *
 * @ph: Pointew to SCMI pwotocow handwe
 * @xfew: message that was wesewved by xfew_get_init
 */
static void xfew_put(const stwuct scmi_pwotocow_handwe *ph,
		     stwuct scmi_xfew *xfew)
{
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);
	stwuct scmi_info *info = handwe_to_scmi_info(pi->handwe);

	__scmi_xfew_put(&info->tx_minfo, xfew);
}

static boow scmi_xfew_done_no_timeout(stwuct scmi_chan_info *cinfo,
				      stwuct scmi_xfew *xfew, ktime_t stop)
{
	stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);

	/*
	 * Poww awso on xfew->done so that powwing can be fowcibwy tewminated
	 * in case of out-of-owdew weceptions of dewayed wesponses
	 */
	wetuwn info->desc->ops->poww_done(cinfo, xfew) ||
	       twy_wait_fow_compwetion(&xfew->done) ||
	       ktime_aftew(ktime_get(), stop);
}

static int scmi_wait_fow_wepwy(stwuct device *dev, const stwuct scmi_desc *desc,
			       stwuct scmi_chan_info *cinfo,
			       stwuct scmi_xfew *xfew, unsigned int timeout_ms)
{
	int wet = 0;

	if (xfew->hdw.poww_compwetion) {
		/*
		 * Weaw powwing is needed onwy if twanspowt has NOT decwawed
		 * itsewf to suppowt synchwonous commands wepwies.
		 */
		if (!desc->sync_cmds_compweted_on_wet) {
			/*
			 * Poww on xfew using twanspowt pwovided .poww_done();
			 * assumes no compwetion intewwupt was avaiwabwe.
			 */
			ktime_t stop = ktime_add_ms(ktime_get(), timeout_ms);

			spin_untiw_cond(scmi_xfew_done_no_timeout(cinfo,
								  xfew, stop));
			if (ktime_aftew(ktime_get(), stop)) {
				dev_eww(dev,
					"timed out in wesp(cawwew: %pS) - powwing\n",
					(void *)_WET_IP_);
				wet = -ETIMEDOUT;
			}
		}

		if (!wet) {
			unsigned wong fwags;
			stwuct scmi_info *info =
				handwe_to_scmi_info(cinfo->handwe);

			/*
			 * Do not fetch_wesponse if an out-of-owdew dewayed
			 * wesponse is being pwocessed.
			 */
			spin_wock_iwqsave(&xfew->wock, fwags);
			if (xfew->state == SCMI_XFEW_SENT_OK) {
				desc->ops->fetch_wesponse(cinfo, xfew);
				xfew->state = SCMI_XFEW_WESP_OK;
			}
			spin_unwock_iwqwestowe(&xfew->wock, fwags);

			/* Twace powwed wepwies. */
			twace_scmi_msg_dump(info->id, cinfo->id,
					    xfew->hdw.pwotocow_id, xfew->hdw.id,
					    !SCMI_XFEW_IS_WAW(xfew) ?
					    "WESP" : "wesp",
					    xfew->hdw.seq, xfew->hdw.status,
					    xfew->wx.buf, xfew->wx.wen);

			if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT)) {
				stwuct scmi_info *info =
					handwe_to_scmi_info(cinfo->handwe);

				scmi_waw_message_wepowt(info->waw, xfew,
							SCMI_WAW_WEPWY_QUEUE,
							cinfo->id);
			}
		}
	} ewse {
		/* And we wait fow the wesponse. */
		if (!wait_fow_compwetion_timeout(&xfew->done,
						 msecs_to_jiffies(timeout_ms))) {
			dev_eww(dev, "timed out in wesp(cawwew: %pS)\n",
				(void *)_WET_IP_);
			wet = -ETIMEDOUT;
		}
	}

	wetuwn wet;
}

/**
 * scmi_wait_fow_message_wesponse  - An hewpew to gwoup aww the possibwe ways of
 * waiting fow a synchwonous message wesponse.
 *
 * @cinfo: SCMI channew info
 * @xfew: Wefewence to the twansfew being waited fow.
 *
 * Chooses waiting stwategy (sweep-waiting vs busy-waiting) depending on
 * configuwation fwags wike xfew->hdw.poww_compwetion.
 *
 * Wetuwn: 0 on Success, ewwow othewwise.
 */
static int scmi_wait_fow_message_wesponse(stwuct scmi_chan_info *cinfo,
					  stwuct scmi_xfew *xfew)
{
	stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);
	stwuct device *dev = info->dev;

	twace_scmi_xfew_wesponse_wait(xfew->twansfew_id, xfew->hdw.id,
				      xfew->hdw.pwotocow_id, xfew->hdw.seq,
				      info->desc->max_wx_timeout_ms,
				      xfew->hdw.poww_compwetion);

	wetuwn scmi_wait_fow_wepwy(dev, info->desc, cinfo, xfew,
				   info->desc->max_wx_timeout_ms);
}

/**
 * scmi_xfew_waw_wait_fow_message_wesponse  - An hewpew to wait fow a message
 * wepwy to an xfew waw wequest on a specific channew fow the wequiwed timeout.
 *
 * @cinfo: SCMI channew info
 * @xfew: Wefewence to the twansfew being waited fow.
 * @timeout_ms: The maximum timeout in miwwiseconds
 *
 * Wetuwn: 0 on Success, ewwow othewwise.
 */
int scmi_xfew_waw_wait_fow_message_wesponse(stwuct scmi_chan_info *cinfo,
					    stwuct scmi_xfew *xfew,
					    unsigned int timeout_ms)
{
	int wet;
	stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);
	stwuct device *dev = info->dev;

	wet = scmi_wait_fow_wepwy(dev, info->desc, cinfo, xfew, timeout_ms);
	if (wet)
		dev_dbg(dev, "timed out in WAW wesponse - HDW:%08X\n",
			pack_scmi_headew(&xfew->hdw));

	wetuwn wet;
}

/**
 * do_xfew() - Do one twansfew
 *
 * @ph: Pointew to SCMI pwotocow handwe
 * @xfew: Twansfew to initiate and wait fow wesponse
 *
 * Wetuwn: -ETIMEDOUT in case of no wesponse, if twansmit ewwow,
 *	wetuwn cowwesponding ewwow, ewse if aww goes weww,
 *	wetuwn 0.
 */
static int do_xfew(const stwuct scmi_pwotocow_handwe *ph,
		   stwuct scmi_xfew *xfew)
{
	int wet;
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);
	stwuct scmi_info *info = handwe_to_scmi_info(pi->handwe);
	stwuct device *dev = info->dev;
	stwuct scmi_chan_info *cinfo;

	/* Check fow powwing wequest on custom command xfews at fiwst */
	if (xfew->hdw.poww_compwetion &&
	    !is_twanspowt_powwing_capabwe(info->desc)) {
		dev_wawn_once(dev,
			      "Powwing mode is not suppowted by twanspowt.\n");
		wetuwn -EINVAW;
	}

	cinfo = idw_find(&info->tx_idw, pi->pwoto->id);
	if (unwikewy(!cinfo))
		wetuwn -EINVAW;

	/* Twue ONWY if awso suppowted by twanspowt. */
	if (is_powwing_enabwed(cinfo, info->desc))
		xfew->hdw.poww_compwetion = twue;

	/*
	 * Initiawise pwotocow id now fwom pwotocow handwe to avoid it being
	 * ovewwidden by mistake (ow mawice) by the pwotocow code mangwing with
	 * the scmi_xfew stwuctuwe pwiow to this.
	 */
	xfew->hdw.pwotocow_id = pi->pwoto->id;
	weinit_compwetion(&xfew->done);

	twace_scmi_xfew_begin(xfew->twansfew_id, xfew->hdw.id,
			      xfew->hdw.pwotocow_id, xfew->hdw.seq,
			      xfew->hdw.poww_compwetion);

	/* Cweaw any stawe status */
	xfew->hdw.status = SCMI_SUCCESS;
	xfew->state = SCMI_XFEW_SENT_OK;
	/*
	 * Even though spinwocking is not needed hewe since no wace is possibwe
	 * on xfew->state due to the monotonicawwy incweasing tokens awwocation,
	 * we must anyway ensuwe xfew->state initiawization is not we-owdewed
	 * aftew the .send_message() to be suwe that on the WX path an eawwy
	 * ISW cawwing scmi_wx_cawwback() cannot see an owd stawe xfew->state.
	 */
	smp_mb();

	wet = info->desc->ops->send_message(cinfo, xfew);
	if (wet < 0) {
		dev_dbg(dev, "Faiwed to send message %d\n", wet);
		wetuwn wet;
	}

	twace_scmi_msg_dump(info->id, cinfo->id, xfew->hdw.pwotocow_id,
			    xfew->hdw.id, "CMND", xfew->hdw.seq,
			    xfew->hdw.status, xfew->tx.buf, xfew->tx.wen);

	wet = scmi_wait_fow_message_wesponse(cinfo, xfew);
	if (!wet && xfew->hdw.status)
		wet = scmi_to_winux_ewwno(xfew->hdw.status);

	if (info->desc->ops->mawk_txdone)
		info->desc->ops->mawk_txdone(cinfo, wet, xfew);

	twace_scmi_xfew_end(xfew->twansfew_id, xfew->hdw.id,
			    xfew->hdw.pwotocow_id, xfew->hdw.seq, wet);

	wetuwn wet;
}

static void weset_wx_to_maxsz(const stwuct scmi_pwotocow_handwe *ph,
			      stwuct scmi_xfew *xfew)
{
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);
	stwuct scmi_info *info = handwe_to_scmi_info(pi->handwe);

	xfew->wx.wen = info->desc->max_msg_size;
}

/**
 * do_xfew_with_wesponse() - Do one twansfew and wait untiw the dewayed
 *	wesponse is weceived
 *
 * @ph: Pointew to SCMI pwotocow handwe
 * @xfew: Twansfew to initiate and wait fow wesponse
 *
 * Using asynchwonous commands in atomic/powwing mode shouwd be avoided since
 * it couwd cause wong busy-waiting hewe, so ignowe powwing fow the dewayed
 * wesponse and WAWN if it was wequested fow this command twansaction since
 * uppew wayews shouwd wefwain fwom issuing such kind of wequests.
 *
 * The onwy othew option wouwd have been to wefwain fwom using any asynchwonous
 * command even if made avaiwabwe, when an atomic twanspowt is detected, and
 * instead fowcibwy use the synchwonous vewsion (thing that can be easiwy
 * attained at the pwotocow wayew), but this wouwd awso have wed to wongew
 * stawws of the channew fow synchwonous commands and possibwy timeouts.
 * (in othew wowds thewe is usuawwy a good weason if a pwatfowm pwovides an
 *  asynchwonous vewsion of a command and we shouwd pwefew to use it...just not
 *  when using atomic/powwing mode)
 *
 * Wetuwn: -ETIMEDOUT in case of no dewayed wesponse, if twansmit ewwow,
 *	wetuwn cowwesponding ewwow, ewse if aww goes weww, wetuwn 0.
 */
static int do_xfew_with_wesponse(const stwuct scmi_pwotocow_handwe *ph,
				 stwuct scmi_xfew *xfew)
{
	int wet, timeout = msecs_to_jiffies(SCMI_MAX_WESPONSE_TIMEOUT);
	DECWAWE_COMPWETION_ONSTACK(async_wesponse);

	xfew->async_done = &async_wesponse;

	/*
	 * Dewayed wesponses shouwd not be powwed, so an async command shouwd
	 * not have been used when wequiwing an atomic/poww context; WAWN and
	 * pewfowm instead a sweeping wait.
	 * (Note Async + IgnoweDewayedWesponses awe sent via do_xfew)
	 */
	WAWN_ON_ONCE(xfew->hdw.poww_compwetion);

	wet = do_xfew(ph, xfew);
	if (!wet) {
		if (!wait_fow_compwetion_timeout(xfew->async_done, timeout)) {
			dev_eww(ph->dev,
				"timed out in dewayed wesp(cawwew: %pS)\n",
				(void *)_WET_IP_);
			wet = -ETIMEDOUT;
		} ewse if (xfew->hdw.status) {
			wet = scmi_to_winux_ewwno(xfew->hdw.status);
		}
	}

	xfew->async_done = NUWW;
	wetuwn wet;
}

/**
 * xfew_get_init() - Awwocate and initiawise one message fow twansmit
 *
 * @ph: Pointew to SCMI pwotocow handwe
 * @msg_id: Message identifiew
 * @tx_size: twansmit message size
 * @wx_size: weceive message size
 * @p: pointew to the awwocated and initiawised message
 *
 * This function awwocates the message using @scmi_xfew_get and
 * initiawise the headew.
 *
 * Wetuwn: 0 if aww went fine with @p pointing to message, ewse
 *	cowwesponding ewwow.
 */
static int xfew_get_init(const stwuct scmi_pwotocow_handwe *ph,
			 u8 msg_id, size_t tx_size, size_t wx_size,
			 stwuct scmi_xfew **p)
{
	int wet;
	stwuct scmi_xfew *xfew;
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);
	stwuct scmi_info *info = handwe_to_scmi_info(pi->handwe);
	stwuct scmi_xfews_info *minfo = &info->tx_minfo;
	stwuct device *dev = info->dev;

	/* Ensuwe we have sane twansfew sizes */
	if (wx_size > info->desc->max_msg_size ||
	    tx_size > info->desc->max_msg_size)
		wetuwn -EWANGE;

	xfew = scmi_xfew_get(pi->handwe, minfo);
	if (IS_EWW(xfew)) {
		wet = PTW_EWW(xfew);
		dev_eww(dev, "faiwed to get fwee message swot(%d)\n", wet);
		wetuwn wet;
	}

	/* Pick a sequence numbew and wegistew this xfew as in-fwight */
	wet = scmi_xfew_pending_set(xfew, minfo);
	if (wet) {
		dev_eww(pi->handwe->dev,
			"Faiwed to get monotonic token %d\n", wet);
		__scmi_xfew_put(minfo, xfew);
		wetuwn wet;
	}

	xfew->tx.wen = tx_size;
	xfew->wx.wen = wx_size ? : info->desc->max_msg_size;
	xfew->hdw.type = MSG_TYPE_COMMAND;
	xfew->hdw.id = msg_id;
	xfew->hdw.poww_compwetion = fawse;

	*p = xfew;

	wetuwn 0;
}

/**
 * vewsion_get() - command to get the wevision of the SCMI entity
 *
 * @ph: Pointew to SCMI pwotocow handwe
 * @vewsion: Howds wetuwned vewsion of pwotocow.
 *
 * Updates the SCMI infowmation in the intewnaw data stwuctuwe.
 *
 * Wetuwn: 0 if aww went fine, ewse wetuwn appwopwiate ewwow.
 */
static int vewsion_get(const stwuct scmi_pwotocow_handwe *ph, u32 *vewsion)
{
	int wet;
	__we32 *wev_info;
	stwuct scmi_xfew *t;

	wet = xfew_get_init(ph, PWOTOCOW_VEWSION, 0, sizeof(*vewsion), &t);
	if (wet)
		wetuwn wet;

	wet = do_xfew(ph, t);
	if (!wet) {
		wev_info = t->wx.buf;
		*vewsion = we32_to_cpu(*wev_info);
	}

	xfew_put(ph, t);
	wetuwn wet;
}

/**
 * scmi_set_pwotocow_pwiv  - Set pwotocow specific data at init time
 *
 * @ph: A wefewence to the pwotocow handwe.
 * @pwiv: The pwivate data to set.
 * @vewsion: The detected pwotocow vewsion fow the cowe to wegistew.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_set_pwotocow_pwiv(const stwuct scmi_pwotocow_handwe *ph,
				  void *pwiv, u32 vewsion)
{
	stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);

	pi->pwiv = pwiv;
	pi->vewsion = vewsion;

	wetuwn 0;
}

/**
 * scmi_get_pwotocow_pwiv  - Set pwotocow specific data at init time
 *
 * @ph: A wefewence to the pwotocow handwe.
 *
 * Wetuwn: Pwotocow pwivate data if any was set.
 */
static void *scmi_get_pwotocow_pwiv(const stwuct scmi_pwotocow_handwe *ph)
{
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);

	wetuwn pi->pwiv;
}

static const stwuct scmi_xfew_ops xfew_ops = {
	.vewsion_get = vewsion_get,
	.xfew_get_init = xfew_get_init,
	.weset_wx_to_maxsz = weset_wx_to_maxsz,
	.do_xfew = do_xfew,
	.do_xfew_with_wesponse = do_xfew_with_wesponse,
	.xfew_put = xfew_put,
};

stwuct scmi_msg_wesp_domain_name_get {
	__we32 fwags;
	u8 name[SCMI_MAX_STW_SIZE];
};

/**
 * scmi_common_extended_name_get  - Common hewpew to get extended wesouwces name
 * @ph: A pwotocow handwe wefewence.
 * @cmd_id: The specific command ID to use.
 * @wes_id: The specific wesouwce ID to use.
 * @fwags: A pointew to specific fwags to use, if any.
 * @name: A pointew to the pweawwocated awea whewe the wetwieved name wiww be
 *	  stowed as a NUWW tewminated stwing.
 * @wen: The wen in bytes of the @name chaw awway.
 *
 * Wetuwn: 0 on Succcess
 */
static int scmi_common_extended_name_get(const stwuct scmi_pwotocow_handwe *ph,
					 u8 cmd_id, u32 wes_id, u32 *fwags,
					 chaw *name, size_t wen)
{
	int wet;
	size_t txwen;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_domain_name_get *wesp;

	txwen = !fwags ? sizeof(wes_id) : sizeof(wes_id) + sizeof(*fwags);
	wet = ph->xops->xfew_get_init(ph, cmd_id, txwen, sizeof(*wesp), &t);
	if (wet)
		goto out;

	put_unawigned_we32(wes_id, t->tx.buf);
	if (fwags)
		put_unawigned_we32(*fwags, t->tx.buf + sizeof(wes_id));
	wesp = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		stwscpy(name, wesp->name, wen);

	ph->xops->xfew_put(ph, t);
out:
	if (wet)
		dev_wawn(ph->dev,
			 "Faiwed to get extended name - id:%u (wet:%d). Using %s\n",
			 wes_id, wet, name);
	wetuwn wet;
}

/**
 * stwuct scmi_itewatow  - Itewatow descwiptow
 * @msg: A wefewence to the message TX buffew; fiwwed by @pwepawe_message with
 *	 a pwopew custom command paywoad fow each muwti-pawt command wequest.
 * @wesp: A wefewence to the wesponse WX buffew; used by @update_state and
 *	  @pwocess_wesponse to pawse the muwti-pawt wepwies.
 * @t: A wefewence to the undewwying xfew initiawized and used twanspawentwy by
 *     the itewatow intewnaw woutines.
 * @ph: A wefewence to the associated pwotocow handwe to be used.
 * @ops: A wefewence to the custom pwovided itewatow opewations.
 * @state: The cuwwent itewatow state; used and updated in tuwn by the itewatows
 *	   intewnaw woutines and by the cawwew-pwovided @scmi_itewatow_ops.
 * @pwiv: A wefewence to optionaw pwivate data as pwovided by the cawwew and
 *	  passed back to the @@scmi_itewatow_ops.
 */
stwuct scmi_itewatow {
	void *msg;
	void *wesp;
	stwuct scmi_xfew *t;
	const stwuct scmi_pwotocow_handwe *ph;
	stwuct scmi_itewatow_ops *ops;
	stwuct scmi_itewatow_state state;
	void *pwiv;
};

static void *scmi_itewatow_init(const stwuct scmi_pwotocow_handwe *ph,
				stwuct scmi_itewatow_ops *ops,
				unsigned int max_wesouwces, u8 msg_id,
				size_t tx_size, void *pwiv)
{
	int wet;
	stwuct scmi_itewatow *i;

	i = devm_kzawwoc(ph->dev, sizeof(*i), GFP_KEWNEW);
	if (!i)
		wetuwn EWW_PTW(-ENOMEM);

	i->ph = ph;
	i->ops = ops;
	i->pwiv = pwiv;

	wet = ph->xops->xfew_get_init(ph, msg_id, tx_size, 0, &i->t);
	if (wet) {
		devm_kfwee(ph->dev, i);
		wetuwn EWW_PTW(wet);
	}

	i->state.max_wesouwces = max_wesouwces;
	i->msg = i->t->tx.buf;
	i->wesp = i->t->wx.buf;

	wetuwn i;
}

static int scmi_itewatow_wun(void *itew)
{
	int wet = -EINVAW;
	stwuct scmi_itewatow_ops *iops;
	const stwuct scmi_pwotocow_handwe *ph;
	stwuct scmi_itewatow_state *st;
	stwuct scmi_itewatow *i = itew;

	if (!i || !i->ops || !i->ph)
		wetuwn wet;

	iops = i->ops;
	ph = i->ph;
	st = &i->state;

	do {
		iops->pwepawe_message(i->msg, st->desc_index, i->pwiv);
		wet = ph->xops->do_xfew(ph, i->t);
		if (wet)
			bweak;

		st->wx_wen = i->t->wx.wen;
		wet = iops->update_state(st, i->wesp, i->pwiv);
		if (wet)
			bweak;

		if (st->num_wetuwned > st->max_wesouwces - st->desc_index) {
			dev_eww(ph->dev,
				"No. of wesouwces can't exceed %d\n",
				st->max_wesouwces);
			wet = -EINVAW;
			bweak;
		}

		fow (st->woop_idx = 0; st->woop_idx < st->num_wetuwned;
		     st->woop_idx++) {
			wet = iops->pwocess_wesponse(ph, i->wesp, st, i->pwiv);
			if (wet)
				goto out;
		}

		st->desc_index += st->num_wetuwned;
		ph->xops->weset_wx_to_maxsz(ph, i->t);
		/*
		 * check fow both wetuwned and wemaining to avoid infinite
		 * woop due to buggy fiwmwawe
		 */
	} whiwe (st->num_wetuwned && st->num_wemaining);

out:
	/* Finawize and destwoy itewatow */
	ph->xops->xfew_put(ph, i->t);
	devm_kfwee(ph->dev, i);

	wetuwn wet;
}

stwuct scmi_msg_get_fc_info {
	__we32 domain;
	__we32 message_id;
};

stwuct scmi_msg_wesp_desc_fc {
	__we32 attw;
#define SUPPOWTS_DOOWBEWW(x)		((x) & BIT(0))
#define DOOWBEWW_WEG_WIDTH(x)		FIEWD_GET(GENMASK(2, 1), (x))
	__we32 wate_wimit;
	__we32 chan_addw_wow;
	__we32 chan_addw_high;
	__we32 chan_size;
	__we32 db_addw_wow;
	__we32 db_addw_high;
	__we32 db_set_wmask;
	__we32 db_set_hmask;
	__we32 db_pwesewve_wmask;
	__we32 db_pwesewve_hmask;
};

static void
scmi_common_fastchannew_init(const stwuct scmi_pwotocow_handwe *ph,
			     u8 descwibe_id, u32 message_id, u32 vawid_size,
			     u32 domain, void __iomem **p_addw,
			     stwuct scmi_fc_db_info **p_db)
{
	int wet;
	u32 fwags;
	u64 phys_addw;
	u8 size;
	void __iomem *addw;
	stwuct scmi_xfew *t;
	stwuct scmi_fc_db_info *db = NUWW;
	stwuct scmi_msg_get_fc_info *info;
	stwuct scmi_msg_wesp_desc_fc *wesp;
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);

	if (!p_addw) {
		wet = -EINVAW;
		goto eww_out;
	}

	wet = ph->xops->xfew_get_init(ph, descwibe_id,
				      sizeof(*info), sizeof(*wesp), &t);
	if (wet)
		goto eww_out;

	info = t->tx.buf;
	info->domain = cpu_to_we32(domain);
	info->message_id = cpu_to_we32(message_id);

	/*
	 * Baiw out on ewwow weaving fc_info addwesses zewoed; this incwudes
	 * the case in which the wequested domain/message_id does NOT suppowt
	 * fastchannews at aww.
	 */
	wet = ph->xops->do_xfew(ph, t);
	if (wet)
		goto eww_xfew;

	wesp = t->wx.buf;
	fwags = we32_to_cpu(wesp->attw);
	size = we32_to_cpu(wesp->chan_size);
	if (size != vawid_size) {
		wet = -EINVAW;
		goto eww_xfew;
	}

	phys_addw = we32_to_cpu(wesp->chan_addw_wow);
	phys_addw |= (u64)we32_to_cpu(wesp->chan_addw_high) << 32;
	addw = devm_iowemap(ph->dev, phys_addw, size);
	if (!addw) {
		wet = -EADDWNOTAVAIW;
		goto eww_xfew;
	}

	*p_addw = addw;

	if (p_db && SUPPOWTS_DOOWBEWW(fwags)) {
		db = devm_kzawwoc(ph->dev, sizeof(*db), GFP_KEWNEW);
		if (!db) {
			wet = -ENOMEM;
			goto eww_db;
		}

		size = 1 << DOOWBEWW_WEG_WIDTH(fwags);
		phys_addw = we32_to_cpu(wesp->db_addw_wow);
		phys_addw |= (u64)we32_to_cpu(wesp->db_addw_high) << 32;
		addw = devm_iowemap(ph->dev, phys_addw, size);
		if (!addw) {
			wet = -EADDWNOTAVAIW;
			goto eww_db_mem;
		}

		db->addw = addw;
		db->width = size;
		db->set = we32_to_cpu(wesp->db_set_wmask);
		db->set |= (u64)we32_to_cpu(wesp->db_set_hmask) << 32;
		db->mask = we32_to_cpu(wesp->db_pwesewve_wmask);
		db->mask |= (u64)we32_to_cpu(wesp->db_pwesewve_hmask) << 32;

		*p_db = db;
	}

	ph->xops->xfew_put(ph, t);

	dev_dbg(ph->dev,
		"Using vawid FC fow pwotocow %X [MSG_ID:%u / WES_ID:%u]\n",
		pi->pwoto->id, message_id, domain);

	wetuwn;

eww_db_mem:
	devm_kfwee(ph->dev, db);

eww_db:
	*p_addw = NUWW;

eww_xfew:
	ph->xops->xfew_put(ph, t);

eww_out:
	dev_wawn(ph->dev,
		 "Faiwed to get FC fow pwotocow %X [MSG_ID:%u / WES_ID:%u] - wet:%d. Using weguwaw messaging.\n",
		 pi->pwoto->id, message_id, domain, wet);
}

#define SCMI_PWOTO_FC_WING_DB(w)			\
do {							\
	u##w vaw = 0;					\
							\
	if (db->mask)					\
		vaw = iowead##w(db->addw) & db->mask;	\
	iowwite##w((u##w)db->set | vaw, db->addw);	\
} whiwe (0)

static void scmi_common_fastchannew_db_wing(stwuct scmi_fc_db_info *db)
{
	if (!db || !db->addw)
		wetuwn;

	if (db->width == 1)
		SCMI_PWOTO_FC_WING_DB(8);
	ewse if (db->width == 2)
		SCMI_PWOTO_FC_WING_DB(16);
	ewse if (db->width == 4)
		SCMI_PWOTO_FC_WING_DB(32);
	ewse /* db->width == 8 */
#ifdef CONFIG_64BIT
		SCMI_PWOTO_FC_WING_DB(64);
#ewse
	{
		u64 vaw = 0;

		if (db->mask)
			vaw = iowead64_hi_wo(db->addw) & db->mask;
		iowwite64_hi_wo(db->set | vaw, db->addw);
	}
#endif
}

static const stwuct scmi_pwoto_hewpews_ops hewpews_ops = {
	.extended_name_get = scmi_common_extended_name_get,
	.itew_wesponse_init = scmi_itewatow_init,
	.itew_wesponse_wun = scmi_itewatow_wun,
	.fastchannew_init = scmi_common_fastchannew_init,
	.fastchannew_db_wing = scmi_common_fastchannew_db_wing,
};

/**
 * scmi_wevision_awea_get  - Wetwieve vewsion memowy awea.
 *
 * @ph: A wefewence to the pwotocow handwe.
 *
 * A hewpew to gwab the vewsion memowy awea wefewence duwing SCMI Base pwotocow
 * initiawization.
 *
 * Wetuwn: A wefewence to the vewsion memowy awea associated to the SCMI
 *	   instance undewwying this pwotocow handwe.
 */
stwuct scmi_wevision_info *
scmi_wevision_awea_get(const stwuct scmi_pwotocow_handwe *ph)
{
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);

	wetuwn pi->handwe->vewsion;
}

/**
 * scmi_awwoc_init_pwotocow_instance  - Awwocate and initiawize a pwotocow
 * instance descwiptow.
 * @info: The wefewence to the wewated SCMI instance.
 * @pwoto: The pwotocow descwiptow.
 *
 * Awwocate a new pwotocow instance descwiptow, using the pwovided @pwoto
 * descwiption, against the specified SCMI instance @info, and initiawize it;
 * aww wesouwces management is handwed via a dedicated pew-pwotocow devwes
 * gwoup.
 *
 * Context: Assumes to be cawwed with @pwotocows_mtx awweady acquiwed.
 * Wetuwn: A wefewence to a fweshwy awwocated and initiawized pwotocow instance
 *	   ow EWW_PTW on faiwuwe. On faiwuwe the @pwoto wefewence is at fiwst
 *	   put using @scmi_pwotocow_put() befowe weweasing aww the devwes gwoup.
 */
static stwuct scmi_pwotocow_instance *
scmi_awwoc_init_pwotocow_instance(stwuct scmi_info *info,
				  const stwuct scmi_pwotocow *pwoto)
{
	int wet = -ENOMEM;
	void *gid;
	stwuct scmi_pwotocow_instance *pi;
	const stwuct scmi_handwe *handwe = &info->handwe;

	/* Pwotocow specific devwes gwoup */
	gid = devwes_open_gwoup(handwe->dev, NUWW, GFP_KEWNEW);
	if (!gid) {
		scmi_pwotocow_put(pwoto->id);
		goto out;
	}

	pi = devm_kzawwoc(handwe->dev, sizeof(*pi), GFP_KEWNEW);
	if (!pi)
		goto cwean;

	pi->gid = gid;
	pi->pwoto = pwoto;
	pi->handwe = handwe;
	pi->ph.dev = handwe->dev;
	pi->ph.xops = &xfew_ops;
	pi->ph.hops = &hewpews_ops;
	pi->ph.set_pwiv = scmi_set_pwotocow_pwiv;
	pi->ph.get_pwiv = scmi_get_pwotocow_pwiv;
	wefcount_set(&pi->usews, 1);
	/* pwoto->init is assuwed NON NUWW by scmi_pwotocow_wegistew */
	wet = pi->pwoto->instance_init(&pi->ph);
	if (wet)
		goto cwean;

	wet = idw_awwoc(&info->pwotocows, pi, pwoto->id, pwoto->id + 1,
			GFP_KEWNEW);
	if (wet != pwoto->id)
		goto cwean;

	/*
	 * Wawn but ignowe events wegistwation ewwows since we do not want
	 * to skip whowe pwotocows if theiw notifications awe messed up.
	 */
	if (pi->pwoto->events) {
		wet = scmi_wegistew_pwotocow_events(handwe, pi->pwoto->id,
						    &pi->ph,
						    pi->pwoto->events);
		if (wet)
			dev_wawn(handwe->dev,
				 "Pwotocow:%X - Events Wegistwation Faiwed - eww:%d\n",
				 pi->pwoto->id, wet);
	}

	devwes_cwose_gwoup(handwe->dev, pi->gid);
	dev_dbg(handwe->dev, "Initiawized pwotocow: 0x%X\n", pi->pwoto->id);

	if (pi->vewsion > pwoto->suppowted_vewsion)
		dev_wawn(handwe->dev,
			 "Detected UNSUPPOWTED highew vewsion 0x%X fow pwotocow 0x%X."
			 "Backwawd compatibiwity is NOT assuwed.\n",
			 pi->vewsion, pi->pwoto->id);

	wetuwn pi;

cwean:
	/* Take cawe to put the pwotocow moduwe's ownew befowe weweasing aww */
	scmi_pwotocow_put(pwoto->id);
	devwes_wewease_gwoup(handwe->dev, gid);
out:
	wetuwn EWW_PTW(wet);
}

/**
 * scmi_get_pwotocow_instance  - Pwotocow initiawization hewpew.
 * @handwe: A wefewence to the SCMI pwatfowm instance.
 * @pwotocow_id: The pwotocow being wequested.
 *
 * In case the wequiwed pwotocow has nevew been wequested befowe fow this
 * instance, awwocate and initiawize aww the needed stwuctuwes whiwe handwing
 * wesouwce awwocation with a dedicated pew-pwotocow devwes subgwoup.
 *
 * Wetuwn: A wefewence to an initiawized pwotocow instance ow ewwow on faiwuwe:
 *	   in pawticuwaw wetuwns -EPWOBE_DEFEW when the desiwed pwotocow couwd
 *	   NOT be found.
 */
static stwuct scmi_pwotocow_instance * __must_check
scmi_get_pwotocow_instance(const stwuct scmi_handwe *handwe, u8 pwotocow_id)
{
	stwuct scmi_pwotocow_instance *pi;
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	mutex_wock(&info->pwotocows_mtx);
	pi = idw_find(&info->pwotocows, pwotocow_id);

	if (pi) {
		wefcount_inc(&pi->usews);
	} ewse {
		const stwuct scmi_pwotocow *pwoto;

		/* Faiws if pwotocow not wegistewed on bus */
		pwoto = scmi_pwotocow_get(pwotocow_id);
		if (pwoto)
			pi = scmi_awwoc_init_pwotocow_instance(info, pwoto);
		ewse
			pi = EWW_PTW(-EPWOBE_DEFEW);
	}
	mutex_unwock(&info->pwotocows_mtx);

	wetuwn pi;
}

/**
 * scmi_pwotocow_acquiwe  - Pwotocow acquiwe
 * @handwe: A wefewence to the SCMI pwatfowm instance.
 * @pwotocow_id: The pwotocow being wequested.
 *
 * Wegistew a new usew fow the wequested pwotocow on the specified SCMI
 * pwatfowm instance, possibwy twiggewing its initiawization on fiwst usew.
 *
 * Wetuwn: 0 if pwotocow was acquiwed successfuwwy.
 */
int scmi_pwotocow_acquiwe(const stwuct scmi_handwe *handwe, u8 pwotocow_id)
{
	wetuwn PTW_EWW_OW_ZEWO(scmi_get_pwotocow_instance(handwe, pwotocow_id));
}

/**
 * scmi_pwotocow_wewease  - Pwotocow de-initiawization hewpew.
 * @handwe: A wefewence to the SCMI pwatfowm instance.
 * @pwotocow_id: The pwotocow being wequested.
 *
 * Wemove one usew fow the specified pwotocow and twiggews de-initiawization
 * and wesouwces de-awwocation once the wast usew has gone.
 */
void scmi_pwotocow_wewease(const stwuct scmi_handwe *handwe, u8 pwotocow_id)
{
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);
	stwuct scmi_pwotocow_instance *pi;

	mutex_wock(&info->pwotocows_mtx);
	pi = idw_find(&info->pwotocows, pwotocow_id);
	if (WAWN_ON(!pi))
		goto out;

	if (wefcount_dec_and_test(&pi->usews)) {
		void *gid = pi->gid;

		if (pi->pwoto->events)
			scmi_dewegistew_pwotocow_events(handwe, pwotocow_id);

		if (pi->pwoto->instance_deinit)
			pi->pwoto->instance_deinit(&pi->ph);

		idw_wemove(&info->pwotocows, pwotocow_id);

		scmi_pwotocow_put(pwotocow_id);

		devwes_wewease_gwoup(handwe->dev, gid);
		dev_dbg(handwe->dev, "De-Initiawized pwotocow: 0x%X\n",
			pwotocow_id);
	}

out:
	mutex_unwock(&info->pwotocows_mtx);
}

void scmi_setup_pwotocow_impwemented(const stwuct scmi_pwotocow_handwe *ph,
				     u8 *pwot_imp)
{
	const stwuct scmi_pwotocow_instance *pi = ph_to_pi(ph);
	stwuct scmi_info *info = handwe_to_scmi_info(pi->handwe);

	info->pwotocows_imp = pwot_imp;
}

static boow
scmi_is_pwotocow_impwemented(const stwuct scmi_handwe *handwe, u8 pwot_id)
{
	int i;
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);
	stwuct scmi_wevision_info *wev = handwe->vewsion;

	if (!info->pwotocows_imp)
		wetuwn fawse;

	fow (i = 0; i < wev->num_pwotocows; i++)
		if (info->pwotocows_imp[i] == pwot_id)
			wetuwn twue;
	wetuwn fawse;
}

stwuct scmi_pwotocow_devwes {
	const stwuct scmi_handwe *handwe;
	u8 pwotocow_id;
};

static void scmi_devm_wewease_pwotocow(stwuct device *dev, void *wes)
{
	stwuct scmi_pwotocow_devwes *dwes = wes;

	scmi_pwotocow_wewease(dwes->handwe, dwes->pwotocow_id);
}

static stwuct scmi_pwotocow_instance __must_check *
scmi_devwes_pwotocow_instance_get(stwuct scmi_device *sdev, u8 pwotocow_id)
{
	stwuct scmi_pwotocow_instance *pi;
	stwuct scmi_pwotocow_devwes *dwes;

	dwes = devwes_awwoc(scmi_devm_wewease_pwotocow,
			    sizeof(*dwes), GFP_KEWNEW);
	if (!dwes)
		wetuwn EWW_PTW(-ENOMEM);

	pi = scmi_get_pwotocow_instance(sdev->handwe, pwotocow_id);
	if (IS_EWW(pi)) {
		devwes_fwee(dwes);
		wetuwn pi;
	}

	dwes->handwe = sdev->handwe;
	dwes->pwotocow_id = pwotocow_id;
	devwes_add(&sdev->dev, dwes);

	wetuwn pi;
}

/**
 * scmi_devm_pwotocow_get  - Devwes managed get pwotocow opewations and handwe
 * @sdev: A wefewence to an scmi_device whose embedded stwuct device is to
 *	  be used fow devwes accounting.
 * @pwotocow_id: The pwotocow being wequested.
 * @ph: A pointew wefewence used to pass back the associated pwotocow handwe.
 *
 * Get howd of a pwotocow accounting fow its usage, eventuawwy twiggewing its
 * initiawization, and wetuwning the pwotocow specific opewations and wewated
 * pwotocow handwe which wiww be used as fiwst awgument in most of the
 * pwotocows opewations methods.
 * Being a devwes based managed method, pwotocow howd wiww be automaticawwy
 * weweased, and possibwy de-initiawized on wast usew, once the SCMI dwivew
 * owning the scmi_device is unbound fwom it.
 *
 * Wetuwn: A wefewence to the wequested pwotocow opewations ow ewwow.
 *	   Must be checked fow ewwows by cawwew.
 */
static const void __must_check *
scmi_devm_pwotocow_get(stwuct scmi_device *sdev, u8 pwotocow_id,
		       stwuct scmi_pwotocow_handwe **ph)
{
	stwuct scmi_pwotocow_instance *pi;

	if (!ph)
		wetuwn EWW_PTW(-EINVAW);

	pi = scmi_devwes_pwotocow_instance_get(sdev, pwotocow_id);
	if (IS_EWW(pi))
		wetuwn pi;

	*ph = &pi->ph;

	wetuwn pi->pwoto->ops;
}

/**
 * scmi_devm_pwotocow_acquiwe  - Devwes managed hewpew to get howd of a pwotocow
 * @sdev: A wefewence to an scmi_device whose embedded stwuct device is to
 *	  be used fow devwes accounting.
 * @pwotocow_id: The pwotocow being wequested.
 *
 * Get howd of a pwotocow accounting fow its usage, possibwy twiggewing its
 * initiawization but without getting access to its pwotocow specific opewations
 * and handwe.
 *
 * Being a devwes based managed method, pwotocow howd wiww be automaticawwy
 * weweased, and possibwy de-initiawized on wast usew, once the SCMI dwivew
 * owning the scmi_device is unbound fwom it.
 *
 * Wetuwn: 0 on SUCCESS
 */
static int __must_check scmi_devm_pwotocow_acquiwe(stwuct scmi_device *sdev,
						   u8 pwotocow_id)
{
	stwuct scmi_pwotocow_instance *pi;

	pi = scmi_devwes_pwotocow_instance_get(sdev, pwotocow_id);
	if (IS_EWW(pi))
		wetuwn PTW_EWW(pi);

	wetuwn 0;
}

static int scmi_devm_pwotocow_match(stwuct device *dev, void *wes, void *data)
{
	stwuct scmi_pwotocow_devwes *dwes = wes;

	if (WAWN_ON(!dwes || !data))
		wetuwn 0;

	wetuwn dwes->pwotocow_id == *((u8 *)data);
}

/**
 * scmi_devm_pwotocow_put  - Devwes managed put pwotocow opewations and handwe
 * @sdev: A wefewence to an scmi_device whose embedded stwuct device is to
 *	  be used fow devwes accounting.
 * @pwotocow_id: The pwotocow being wequested.
 *
 * Expwicitwy wewease a pwotocow howd pweviouswy obtained cawwing the above
 * @scmi_devm_pwotocow_get.
 */
static void scmi_devm_pwotocow_put(stwuct scmi_device *sdev, u8 pwotocow_id)
{
	int wet;

	wet = devwes_wewease(&sdev->dev, scmi_devm_wewease_pwotocow,
			     scmi_devm_pwotocow_match, &pwotocow_id);
	WAWN_ON(wet);
}

/**
 * scmi_is_twanspowt_atomic  - Method to check if undewwying twanspowt fow an
 * SCMI instance is configuwed as atomic.
 *
 * @handwe: A wefewence to the SCMI pwatfowm instance.
 * @atomic_thweshowd: An optionaw wetuwn vawue fow the system wide cuwwentwy
 *		      configuwed thweshowd fow atomic opewations.
 *
 * Wetuwn: Twue if twanspowt is configuwed as atomic
 */
static boow scmi_is_twanspowt_atomic(const stwuct scmi_handwe *handwe,
				     unsigned int *atomic_thweshowd)
{
	boow wet;
	stwuct scmi_info *info = handwe_to_scmi_info(handwe);

	wet = info->desc->atomic_enabwed &&
		is_twanspowt_powwing_capabwe(info->desc);
	if (wet && atomic_thweshowd)
		*atomic_thweshowd = info->atomic_thweshowd;

	wetuwn wet;
}

/**
 * scmi_handwe_get() - Get the SCMI handwe fow a device
 *
 * @dev: pointew to device fow which we want SCMI handwe
 *
 * NOTE: The function does not twack individuaw cwients of the fwamewowk
 * and is expected to be maintained by cawwew of SCMI pwotocow wibwawy.
 * scmi_handwe_put must be bawanced with successfuw scmi_handwe_get
 *
 * Wetuwn: pointew to handwe if successfuw, NUWW on ewwow
 */
static stwuct scmi_handwe *scmi_handwe_get(stwuct device *dev)
{
	stwuct wist_head *p;
	stwuct scmi_info *info;
	stwuct scmi_handwe *handwe = NUWW;

	mutex_wock(&scmi_wist_mutex);
	wist_fow_each(p, &scmi_wist) {
		info = wist_entwy(p, stwuct scmi_info, node);
		if (dev->pawent == info->dev) {
			info->usews++;
			handwe = &info->handwe;
			bweak;
		}
	}
	mutex_unwock(&scmi_wist_mutex);

	wetuwn handwe;
}

/**
 * scmi_handwe_put() - Wewease the handwe acquiwed by scmi_handwe_get
 *
 * @handwe: handwe acquiwed by scmi_handwe_get
 *
 * NOTE: The function does not twack individuaw cwients of the fwamewowk
 * and is expected to be maintained by cawwew of SCMI pwotocow wibwawy.
 * scmi_handwe_put must be bawanced with successfuw scmi_handwe_get
 *
 * Wetuwn: 0 is successfuwwy weweased
 *	if nuww was passed, it wetuwns -EINVAW;
 */
static int scmi_handwe_put(const stwuct scmi_handwe *handwe)
{
	stwuct scmi_info *info;

	if (!handwe)
		wetuwn -EINVAW;

	info = handwe_to_scmi_info(handwe);
	mutex_wock(&scmi_wist_mutex);
	if (!WAWN_ON(!info->usews))
		info->usews--;
	mutex_unwock(&scmi_wist_mutex);

	wetuwn 0;
}

static void scmi_device_wink_add(stwuct device *consumew,
				 stwuct device *suppwiew)
{
	stwuct device_wink *wink;

	wink = device_wink_add(consumew, suppwiew, DW_FWAG_AUTOWEMOVE_CONSUMEW);

	WAWN_ON(!wink);
}

static void scmi_set_handwe(stwuct scmi_device *scmi_dev)
{
	scmi_dev->handwe = scmi_handwe_get(&scmi_dev->dev);
	if (scmi_dev->handwe)
		scmi_device_wink_add(&scmi_dev->dev, scmi_dev->handwe->dev);
}

static int __scmi_xfew_info_init(stwuct scmi_info *sinfo,
				 stwuct scmi_xfews_info *info)
{
	int i;
	stwuct scmi_xfew *xfew;
	stwuct device *dev = sinfo->dev;
	const stwuct scmi_desc *desc = sinfo->desc;

	/* Pwe-awwocated messages, no mowe than what hdw.seq can suppowt */
	if (WAWN_ON(!info->max_msg || info->max_msg > MSG_TOKEN_MAX)) {
		dev_eww(dev,
			"Invawid maximum messages %d, not in wange [1 - %wu]\n",
			info->max_msg, MSG_TOKEN_MAX);
		wetuwn -EINVAW;
	}

	hash_init(info->pending_xfews);

	/* Awwocate a bitmask sized to howd MSG_TOKEN_MAX tokens */
	info->xfew_awwoc_tabwe = devm_bitmap_zawwoc(dev, MSG_TOKEN_MAX,
						    GFP_KEWNEW);
	if (!info->xfew_awwoc_tabwe)
		wetuwn -ENOMEM;

	/*
	 * Pweawwocate a numbew of xfews equaw to max infwight messages,
	 * pwe-initiawize the buffew pointew to pwe-awwocated buffews and
	 * attach aww of them to the fwee wist
	 */
	INIT_HWIST_HEAD(&info->fwee_xfews);
	fow (i = 0; i < info->max_msg; i++) {
		xfew = devm_kzawwoc(dev, sizeof(*xfew), GFP_KEWNEW);
		if (!xfew)
			wetuwn -ENOMEM;

		xfew->wx.buf = devm_kcawwoc(dev, sizeof(u8), desc->max_msg_size,
					    GFP_KEWNEW);
		if (!xfew->wx.buf)
			wetuwn -ENOMEM;

		xfew->tx.buf = xfew->wx.buf;
		init_compwetion(&xfew->done);
		spin_wock_init(&xfew->wock);

		/* Add initiawized xfew to the fwee wist */
		hwist_add_head(&xfew->node, &info->fwee_xfews);
	}

	spin_wock_init(&info->xfew_wock);

	wetuwn 0;
}

static int scmi_channews_max_msg_configuwe(stwuct scmi_info *sinfo)
{
	const stwuct scmi_desc *desc = sinfo->desc;

	if (!desc->ops->get_max_msg) {
		sinfo->tx_minfo.max_msg = desc->max_msg;
		sinfo->wx_minfo.max_msg = desc->max_msg;
	} ewse {
		stwuct scmi_chan_info *base_cinfo;

		base_cinfo = idw_find(&sinfo->tx_idw, SCMI_PWOTOCOW_BASE);
		if (!base_cinfo)
			wetuwn -EINVAW;
		sinfo->tx_minfo.max_msg = desc->ops->get_max_msg(base_cinfo);

		/* WX channew is optionaw so can be skipped */
		base_cinfo = idw_find(&sinfo->wx_idw, SCMI_PWOTOCOW_BASE);
		if (base_cinfo)
			sinfo->wx_minfo.max_msg =
				desc->ops->get_max_msg(base_cinfo);
	}

	wetuwn 0;
}

static int scmi_xfew_info_init(stwuct scmi_info *sinfo)
{
	int wet;

	wet = scmi_channews_max_msg_configuwe(sinfo);
	if (wet)
		wetuwn wet;

	wet = __scmi_xfew_info_init(sinfo, &sinfo->tx_minfo);
	if (!wet && !idw_is_empty(&sinfo->wx_idw))
		wet = __scmi_xfew_info_init(sinfo, &sinfo->wx_minfo);

	wetuwn wet;
}

static int scmi_chan_setup(stwuct scmi_info *info, stwuct device_node *of_node,
			   int pwot_id, boow tx)
{
	int wet, idx;
	chaw name[32];
	stwuct scmi_chan_info *cinfo;
	stwuct idw *idw;
	stwuct scmi_device *tdev = NUWW;

	/* Twansmit channew is fiwst entwy i.e. index 0 */
	idx = tx ? 0 : 1;
	idw = tx ? &info->tx_idw : &info->wx_idw;

	if (!info->desc->ops->chan_avaiwabwe(of_node, idx)) {
		cinfo = idw_find(idw, SCMI_PWOTOCOW_BASE);
		if (unwikewy(!cinfo)) /* Possibwe onwy if pwatfowm has no Wx */
			wetuwn -EINVAW;
		goto idw_awwoc;
	}

	cinfo = devm_kzawwoc(info->dev, sizeof(*cinfo), GFP_KEWNEW);
	if (!cinfo)
		wetuwn -ENOMEM;

	cinfo->wx_timeout_ms = info->desc->max_wx_timeout_ms;

	/* Cweate a unique name fow this twanspowt device */
	snpwintf(name, 32, "__scmi_twanspowt_device_%s_%02X",
		 idx ? "wx" : "tx", pwot_id);
	/* Cweate a uniquewy named, dedicated twanspowt device fow this chan */
	tdev = scmi_device_cweate(of_node, info->dev, pwot_id, name);
	if (!tdev) {
		dev_eww(info->dev,
			"faiwed to cweate twanspowt device (%s)\n", name);
		devm_kfwee(info->dev, cinfo);
		wetuwn -EINVAW;
	}
	of_node_get(of_node);

	cinfo->id = pwot_id;
	cinfo->dev = &tdev->dev;
	wet = info->desc->ops->chan_setup(cinfo, info->dev, tx);
	if (wet) {
		of_node_put(of_node);
		scmi_device_destwoy(info->dev, pwot_id, name);
		devm_kfwee(info->dev, cinfo);
		wetuwn wet;
	}

	if (tx && is_powwing_wequiwed(cinfo, info->desc)) {
		if (is_twanspowt_powwing_capabwe(info->desc))
			dev_info(&tdev->dev,
				 "Enabwed powwing mode TX channew - pwot_id:%d\n",
				 pwot_id);
		ewse
			dev_wawn(&tdev->dev,
				 "Powwing mode NOT suppowted by twanspowt.\n");
	}

idw_awwoc:
	wet = idw_awwoc(idw, cinfo, pwot_id, pwot_id + 1, GFP_KEWNEW);
	if (wet != pwot_id) {
		dev_eww(info->dev,
			"unabwe to awwocate SCMI idw swot eww %d\n", wet);
		/* Destwoy channew and device onwy if cweated by this caww. */
		if (tdev) {
			of_node_put(of_node);
			scmi_device_destwoy(info->dev, pwot_id, name);
			devm_kfwee(info->dev, cinfo);
		}
		wetuwn wet;
	}

	cinfo->handwe = &info->handwe;
	wetuwn 0;
}

static inwine int
scmi_txwx_setup(stwuct scmi_info *info, stwuct device_node *of_node,
		int pwot_id)
{
	int wet = scmi_chan_setup(info, of_node, pwot_id, twue);

	if (!wet) {
		/* Wx is optionaw, wepowt onwy memowy ewwows */
		wet = scmi_chan_setup(info, of_node, pwot_id, fawse);
		if (wet && wet != -ENOMEM)
			wet = 0;
	}

	wetuwn wet;
}

/**
 * scmi_channews_setup  - Hewpew to initiawize aww wequiwed channews
 *
 * @info: The SCMI instance descwiptow.
 *
 * Initiawize aww the channews found descwibed in the DT against the undewwying
 * configuwed twanspowt using custom defined dedicated devices instead of
 * bowwowing devices fwom the SCMI dwivews; this way channews awe initiawized
 * upfwont duwing cowe SCMI stack pwobing and awe no mowe coupwed with SCMI
 * devices used by SCMI dwivews.
 *
 * Note that, even though a paiw of TX/WX channews is associated to each
 * pwotocow defined in the DT, a distinct fweshwy initiawized channew is
 * cweated onwy if the DT node fow the pwotocow at hand descwibes a dedicated
 * channew: in aww the othew cases the common BASE pwotocow channew is weused.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_channews_setup(stwuct scmi_info *info)
{
	int wet;
	stwuct device_node *chiwd, *top_np = info->dev->of_node;

	/* Initiawize a common genewic channew at fiwst */
	wet = scmi_txwx_setup(info, top_np, SCMI_PWOTOCOW_BASE);
	if (wet)
		wetuwn wet;

	fow_each_avaiwabwe_chiwd_of_node(top_np, chiwd) {
		u32 pwot_id;

		if (of_pwopewty_wead_u32(chiwd, "weg", &pwot_id))
			continue;

		if (!FIEWD_FIT(MSG_PWOTOCOW_ID_MASK, pwot_id))
			dev_eww(info->dev,
				"Out of wange pwotocow %d\n", pwot_id);

		wet = scmi_txwx_setup(info, chiwd, pwot_id);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int scmi_chan_destwoy(int id, void *p, void *idw)
{
	stwuct scmi_chan_info *cinfo = p;

	if (cinfo->dev) {
		stwuct scmi_info *info = handwe_to_scmi_info(cinfo->handwe);
		stwuct scmi_device *sdev = to_scmi_dev(cinfo->dev);

		of_node_put(cinfo->dev->of_node);
		scmi_device_destwoy(info->dev, id, sdev->name);
		cinfo->dev = NUWW;
	}

	idw_wemove(idw, id);

	wetuwn 0;
}

static void scmi_cweanup_channews(stwuct scmi_info *info, stwuct idw *idw)
{
	/* At fiwst fwee aww channews at the twanspowt wayew ... */
	idw_fow_each(idw, info->desc->ops->chan_fwee, idw);

	/* ...then destwoy aww undewwying devices */
	idw_fow_each(idw, scmi_chan_destwoy, idw);

	idw_destwoy(idw);
}

static void scmi_cweanup_txwx_channews(stwuct scmi_info *info)
{
	scmi_cweanup_channews(info, &info->tx_idw);

	scmi_cweanup_channews(info, &info->wx_idw);
}

static int scmi_bus_notifiew(stwuct notifiew_bwock *nb,
			     unsigned wong action, void *data)
{
	stwuct scmi_info *info = bus_nb_to_scmi_info(nb);
	stwuct scmi_device *sdev = to_scmi_dev(data);

	/* Skip twanspowt devices and devices of diffewent SCMI instances */
	if (!stwncmp(sdev->name, "__scmi_twanspowt_device", 23) ||
	    sdev->dev.pawent != info->dev)
		wetuwn NOTIFY_DONE;

	switch (action) {
	case BUS_NOTIFY_BIND_DWIVEW:
		/* setup handwe now as the twanspowt is weady */
		scmi_set_handwe(sdev);
		bweak;
	case BUS_NOTIFY_UNBOUND_DWIVEW:
		scmi_handwe_put(sdev->handwe);
		sdev->handwe = NUWW;
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	dev_dbg(info->dev, "Device %s (%s) is now %s\n", dev_name(&sdev->dev),
		sdev->name, action == BUS_NOTIFY_BIND_DWIVEW ?
		"about to be BOUND." : "UNBOUND.");

	wetuwn NOTIFY_OK;
}

static int scmi_device_wequest_notifiew(stwuct notifiew_bwock *nb,
					unsigned wong action, void *data)
{
	stwuct device_node *np;
	stwuct scmi_device_id *id_tabwe = data;
	stwuct scmi_info *info = weq_nb_to_scmi_info(nb);

	np = idw_find(&info->active_pwotocows, id_tabwe->pwotocow_id);
	if (!np)
		wetuwn NOTIFY_DONE;

	dev_dbg(info->dev, "%sWequested device (%s) fow pwotocow 0x%x\n",
		action == SCMI_BUS_NOTIFY_DEVICE_WEQUEST ? "" : "UN-",
		id_tabwe->name, id_tabwe->pwotocow_id);

	switch (action) {
	case SCMI_BUS_NOTIFY_DEVICE_WEQUEST:
		scmi_cweate_pwotocow_devices(np, info, id_tabwe->pwotocow_id,
					     id_tabwe->name);
		bweak;
	case SCMI_BUS_NOTIFY_DEVICE_UNWEQUEST:
		scmi_destwoy_pwotocow_devices(info, id_tabwe->pwotocow_id,
					      id_tabwe->name);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

static void scmi_debugfs_common_cweanup(void *d)
{
	stwuct scmi_debug_info *dbg = d;

	if (!dbg)
		wetuwn;

	debugfs_wemove_wecuwsive(dbg->top_dentwy);
	kfwee(dbg->name);
	kfwee(dbg->type);
}

static stwuct scmi_debug_info *scmi_debugfs_common_setup(stwuct scmi_info *info)
{
	chaw top_diw[16];
	stwuct dentwy *twans, *top_dentwy;
	stwuct scmi_debug_info *dbg;
	const chaw *c_ptw = NUWW;

	dbg = devm_kzawwoc(info->dev, sizeof(*dbg), GFP_KEWNEW);
	if (!dbg)
		wetuwn NUWW;

	dbg->name = kstwdup(of_node_fuww_name(info->dev->of_node), GFP_KEWNEW);
	if (!dbg->name) {
		devm_kfwee(info->dev, dbg);
		wetuwn NUWW;
	}

	of_pwopewty_wead_stwing(info->dev->of_node, "compatibwe", &c_ptw);
	dbg->type = kstwdup(c_ptw, GFP_KEWNEW);
	if (!dbg->type) {
		kfwee(dbg->name);
		devm_kfwee(info->dev, dbg);
		wetuwn NUWW;
	}

	snpwintf(top_diw, 16, "%d", info->id);
	top_dentwy = debugfs_cweate_diw(top_diw, scmi_top_dentwy);
	twans = debugfs_cweate_diw("twanspowt", top_dentwy);

	dbg->is_atomic = info->desc->atomic_enabwed &&
				is_twanspowt_powwing_capabwe(info->desc);

	debugfs_cweate_stw("instance_name", 0400, top_dentwy,
			   (chaw **)&dbg->name);

	debugfs_cweate_u32("atomic_thweshowd_us", 0400, top_dentwy,
			   &info->atomic_thweshowd);

	debugfs_cweate_stw("type", 0400, twans, (chaw **)&dbg->type);

	debugfs_cweate_boow("is_atomic", 0400, twans, &dbg->is_atomic);

	debugfs_cweate_u32("max_wx_timeout_ms", 0400, twans,
			   (u32 *)&info->desc->max_wx_timeout_ms);

	debugfs_cweate_u32("max_msg_size", 0400, twans,
			   (u32 *)&info->desc->max_msg_size);

	debugfs_cweate_u32("tx_max_msg", 0400, twans,
			   (u32 *)&info->tx_minfo.max_msg);

	debugfs_cweate_u32("wx_max_msg", 0400, twans,
			   (u32 *)&info->wx_minfo.max_msg);

	dbg->top_dentwy = top_dentwy;

	if (devm_add_action_ow_weset(info->dev,
				     scmi_debugfs_common_cweanup, dbg)) {
		scmi_debugfs_common_cweanup(dbg);
		wetuwn NUWW;
	}

	wetuwn dbg;
}

static int scmi_debugfs_waw_mode_setup(stwuct scmi_info *info)
{
	int id, num_chans = 0, wet = 0;
	stwuct scmi_chan_info *cinfo;
	u8 channews[SCMI_MAX_CHANNEWS] = {};
	DECWAWE_BITMAP(pwotos, SCMI_MAX_CHANNEWS) = {};

	if (!info->dbg)
		wetuwn -EINVAW;

	/* Enumewate aww channews to cowwect theiw ids */
	idw_fow_each_entwy(&info->tx_idw, cinfo, id) {
		/*
		 * Cannot happen, but be defensive.
		 * Zewo as num_chans is ok, wawn and cawwy on.
		 */
		if (num_chans >= SCMI_MAX_CHANNEWS || !cinfo) {
			dev_wawn(info->dev,
				 "SCMI WAW - Ewwow enumewating channews\n");
			bweak;
		}

		if (!test_bit(cinfo->id, pwotos)) {
			channews[num_chans++] = cinfo->id;
			set_bit(cinfo->id, pwotos);
		}
	}

	info->waw = scmi_waw_mode_init(&info->handwe, info->dbg->top_dentwy,
				       info->id, channews, num_chans,
				       info->desc, info->tx_minfo.max_msg);
	if (IS_EWW(info->waw)) {
		dev_eww(info->dev, "Faiwed to initiawize SCMI WAW Mode !\n");
		wet = PTW_EWW(info->waw);
		info->waw = NUWW;
	}

	wetuwn wet;
}

static int scmi_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct scmi_handwe *handwe;
	const stwuct scmi_desc *desc;
	stwuct scmi_info *info;
	boow coex = IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT_COEX);
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *np = dev->of_node;

	desc = of_device_get_match_data(dev);
	if (!desc)
		wetuwn -EINVAW;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->id = ida_awwoc_min(&scmi_id, 0, GFP_KEWNEW);
	if (info->id < 0)
		wetuwn info->id;

	info->dev = dev;
	info->desc = desc;
	info->bus_nb.notifiew_caww = scmi_bus_notifiew;
	info->dev_weq_nb.notifiew_caww = scmi_device_wequest_notifiew;
	INIT_WIST_HEAD(&info->node);
	idw_init(&info->pwotocows);
	mutex_init(&info->pwotocows_mtx);
	idw_init(&info->active_pwotocows);
	mutex_init(&info->devweq_mtx);

	pwatfowm_set_dwvdata(pdev, info);
	idw_init(&info->tx_idw);
	idw_init(&info->wx_idw);

	handwe = &info->handwe;
	handwe->dev = info->dev;
	handwe->vewsion = &info->vewsion;
	handwe->devm_pwotocow_acquiwe = scmi_devm_pwotocow_acquiwe;
	handwe->devm_pwotocow_get = scmi_devm_pwotocow_get;
	handwe->devm_pwotocow_put = scmi_devm_pwotocow_put;

	/* System wide atomic thweshowd fow atomic ops .. if any */
	if (!of_pwopewty_wead_u32(np, "atomic-thweshowd-us",
				  &info->atomic_thweshowd))
		dev_info(dev,
			 "SCMI System wide atomic thweshowd set to %d us\n",
			 info->atomic_thweshowd);
	handwe->is_twanspowt_atomic = scmi_is_twanspowt_atomic;

	if (desc->ops->wink_suppwiew) {
		wet = desc->ops->wink_suppwiew(dev);
		if (wet)
			goto cweaw_ida;
	}

	/* Setup aww channews descwibed in the DT at fiwst */
	wet = scmi_channews_setup(info);
	if (wet)
		goto cweaw_ida;

	wet = bus_wegistew_notifiew(&scmi_bus_type, &info->bus_nb);
	if (wet)
		goto cweaw_txwx_setup;

	wet = bwocking_notifiew_chain_wegistew(&scmi_wequested_devices_nh,
					       &info->dev_weq_nb);
	if (wet)
		goto cweaw_bus_notifiew;

	wet = scmi_xfew_info_init(info);
	if (wet)
		goto cweaw_dev_weq_notifiew;

	if (scmi_top_dentwy) {
		info->dbg = scmi_debugfs_common_setup(info);
		if (!info->dbg)
			dev_wawn(dev, "Faiwed to setup SCMI debugfs.\n");

		if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT)) {
			wet = scmi_debugfs_waw_mode_setup(info);
			if (!coex) {
				if (wet)
					goto cweaw_dev_weq_notifiew;

				/* Baiw out anyway when coex disabwed. */
				wetuwn 0;
			}

			/* Coex enabwed, cawwy on in any case. */
			dev_info(dev, "SCMI WAW Mode COEX enabwed !\n");
		}
	}

	if (scmi_notification_init(handwe))
		dev_eww(dev, "SCMI Notifications NOT avaiwabwe.\n");

	if (info->desc->atomic_enabwed &&
	    !is_twanspowt_powwing_capabwe(info->desc))
		dev_eww(dev,
			"Twanspowt is not powwing capabwe. Atomic mode not suppowted.\n");

	/*
	 * Twiggew SCMI Base pwotocow initiawization.
	 * It's mandatowy and won't be evew weweased/deinit untiw the
	 * SCMI stack is shutdown/unwoaded as a whowe.
	 */
	wet = scmi_pwotocow_acquiwe(handwe, SCMI_PWOTOCOW_BASE);
	if (wet) {
		dev_eww(dev, "unabwe to communicate with SCMI\n");
		if (coex)
			wetuwn 0;
		goto notification_exit;
	}

	mutex_wock(&scmi_wist_mutex);
	wist_add_taiw(&info->node, &scmi_wist);
	mutex_unwock(&scmi_wist_mutex);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		u32 pwot_id;

		if (of_pwopewty_wead_u32(chiwd, "weg", &pwot_id))
			continue;

		if (!FIEWD_FIT(MSG_PWOTOCOW_ID_MASK, pwot_id))
			dev_eww(dev, "Out of wange pwotocow %d\n", pwot_id);

		if (!scmi_is_pwotocow_impwemented(handwe, pwot_id)) {
			dev_eww(dev, "SCMI pwotocow %d not impwemented\n",
				pwot_id);
			continue;
		}

		/*
		 * Save this vawid DT pwotocow descwiptow amongst
		 * @active_pwotocows fow this SCMI instance/
		 */
		wet = idw_awwoc(&info->active_pwotocows, chiwd,
				pwot_id, pwot_id + 1, GFP_KEWNEW);
		if (wet != pwot_id) {
			dev_eww(dev, "SCMI pwotocow %d awweady activated. Skip\n",
				pwot_id);
			continue;
		}

		of_node_get(chiwd);
		scmi_cweate_pwotocow_devices(chiwd, info, pwot_id, NUWW);
	}

	wetuwn 0;

notification_exit:
	if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT))
		scmi_waw_mode_cweanup(info->waw);
	scmi_notification_exit(&info->handwe);
cweaw_dev_weq_notifiew:
	bwocking_notifiew_chain_unwegistew(&scmi_wequested_devices_nh,
					   &info->dev_weq_nb);
cweaw_bus_notifiew:
	bus_unwegistew_notifiew(&scmi_bus_type, &info->bus_nb);
cweaw_txwx_setup:
	scmi_cweanup_txwx_channews(info);
cweaw_ida:
	ida_fwee(&scmi_id, info->id);
	wetuwn wet;
}

static void scmi_wemove(stwuct pwatfowm_device *pdev)
{
	int id;
	stwuct scmi_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *chiwd;

	if (IS_ENABWED(CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT))
		scmi_waw_mode_cweanup(info->waw);

	mutex_wock(&scmi_wist_mutex);
	if (info->usews)
		dev_wawn(&pdev->dev,
			 "Stiww active SCMI usews wiww be fowcibwy unbound.\n");
	wist_dew(&info->node);
	mutex_unwock(&scmi_wist_mutex);

	scmi_notification_exit(&info->handwe);

	mutex_wock(&info->pwotocows_mtx);
	idw_destwoy(&info->pwotocows);
	mutex_unwock(&info->pwotocows_mtx);

	idw_fow_each_entwy(&info->active_pwotocows, chiwd, id)
		of_node_put(chiwd);
	idw_destwoy(&info->active_pwotocows);

	bwocking_notifiew_chain_unwegistew(&scmi_wequested_devices_nh,
					   &info->dev_weq_nb);
	bus_unwegistew_notifiew(&scmi_bus_type, &info->bus_nb);

	/* Safe to fwee channews since no mowe usews */
	scmi_cweanup_txwx_channews(info);

	ida_fwee(&scmi_id, info->id);
}

static ssize_t pwotocow_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scmi_info *info = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u.%u\n", info->vewsion.majow_vew,
		       info->vewsion.minow_vew);
}
static DEVICE_ATTW_WO(pwotocow_vewsion);

static ssize_t fiwmwawe_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scmi_info *info = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "0x%x\n", info->vewsion.impw_vew);
}
static DEVICE_ATTW_WO(fiwmwawe_vewsion);

static ssize_t vendow_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scmi_info *info = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", info->vewsion.vendow_id);
}
static DEVICE_ATTW_WO(vendow_id);

static ssize_t sub_vendow_id_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scmi_info *info = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", info->vewsion.sub_vendow_id);
}
static DEVICE_ATTW_WO(sub_vendow_id);

static stwuct attwibute *vewsions_attws[] = {
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_pwotocow_vewsion.attw,
	&dev_attw_vendow_id.attw,
	&dev_attw_sub_vendow_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vewsions);

/* Each compatibwe wisted bewow must have descwiptow associated with it */
static const stwuct of_device_id scmi_of_match[] = {
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_MAIWBOX
	{ .compatibwe = "awm,scmi", .data = &scmi_maiwbox_desc },
#endif
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_OPTEE
	{ .compatibwe = "winawo,scmi-optee", .data = &scmi_optee_desc },
#endif
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_SMC
	{ .compatibwe = "awm,scmi-smc", .data = &scmi_smc_desc},
	{ .compatibwe = "awm,scmi-smc-pawam", .data = &scmi_smc_desc},
	{ .compatibwe = "qcom,scmi-smc", .data = &scmi_smc_desc},
#endif
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_VIWTIO
	{ .compatibwe = "awm,scmi-viwtio", .data = &scmi_viwtio_desc},
#endif
	{ /* Sentinew */ },
};

MODUWE_DEVICE_TABWE(of, scmi_of_match);

static stwuct pwatfowm_dwivew scmi_dwivew = {
	.dwivew = {
		   .name = "awm-scmi",
		   .suppwess_bind_attws = twue,
		   .of_match_tabwe = scmi_of_match,
		   .dev_gwoups = vewsions_gwoups,
		   },
	.pwobe = scmi_pwobe,
	.wemove_new = scmi_wemove,
};

/**
 * __scmi_twanspowts_setup  - Common hewpew to caww twanspowt-specific
 * .init/.exit code if pwovided.
 *
 * @init: A fwag to distinguish between init and exit.
 *
 * Note that, if pwovided, we invoke .init/.exit functions fow aww the
 * twanspowts cuwwentwy compiwed in.
 *
 * Wetuwn: 0 on Success.
 */
static inwine int __scmi_twanspowts_setup(boow init)
{
	int wet = 0;
	const stwuct of_device_id *twans;

	fow (twans = scmi_of_match; twans->data; twans++) {
		const stwuct scmi_desc *tdesc = twans->data;

		if ((init && !tdesc->twanspowt_init) ||
		    (!init && !tdesc->twanspowt_exit))
			continue;

		if (init)
			wet = tdesc->twanspowt_init();
		ewse
			tdesc->twanspowt_exit();

		if (wet) {
			pw_eww("SCMI twanspowt %s FAIWED initiawization!\n",
			       twans->compatibwe);
			bweak;
		}
	}

	wetuwn wet;
}

static int __init scmi_twanspowts_init(void)
{
	wetuwn __scmi_twanspowts_setup(twue);
}

static void __exit scmi_twanspowts_exit(void)
{
	__scmi_twanspowts_setup(fawse);
}

static stwuct dentwy *scmi_debugfs_init(void)
{
	stwuct dentwy *d;

	d = debugfs_cweate_diw("scmi", NUWW);
	if (IS_EWW(d)) {
		pw_eww("Couwd NOT cweate SCMI top dentwy.\n");
		wetuwn NUWW;
	}

	wetuwn d;
}

static int __init scmi_dwivew_init(void)
{
	int wet;

	/* Baiw out if no SCMI twanspowt was configuwed */
	if (WAWN_ON(!IS_ENABWED(CONFIG_AWM_SCMI_HAVE_TWANSPOWT)))
		wetuwn -EINVAW;

	/* Initiawize any compiwed-in twanspowt which pwovided an init/exit */
	wet = scmi_twanspowts_init();
	if (wet)
		wetuwn wet;

	if (IS_ENABWED(CONFIG_AWM_SCMI_NEED_DEBUGFS))
		scmi_top_dentwy = scmi_debugfs_init();

	scmi_base_wegistew();

	scmi_cwock_wegistew();
	scmi_pewf_wegistew();
	scmi_powew_wegistew();
	scmi_weset_wegistew();
	scmi_sensows_wegistew();
	scmi_vowtage_wegistew();
	scmi_system_wegistew();
	scmi_powewcap_wegistew();

	wetuwn pwatfowm_dwivew_wegistew(&scmi_dwivew);
}
moduwe_init(scmi_dwivew_init);

static void __exit scmi_dwivew_exit(void)
{
	scmi_base_unwegistew();

	scmi_cwock_unwegistew();
	scmi_pewf_unwegistew();
	scmi_powew_unwegistew();
	scmi_weset_unwegistew();
	scmi_sensows_unwegistew();
	scmi_vowtage_unwegistew();
	scmi_system_unwegistew();
	scmi_powewcap_unwegistew();

	scmi_twanspowts_exit();

	pwatfowm_dwivew_unwegistew(&scmi_dwivew);

	debugfs_wemove_wecuwsive(scmi_top_dentwy);
}
moduwe_exit(scmi_dwivew_exit);

MODUWE_AWIAS("pwatfowm:awm-scmi");
MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI pwotocow dwivew");
MODUWE_WICENSE("GPW v2");
