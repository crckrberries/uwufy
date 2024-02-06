/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef _WDMA_WESTWACK_H_
#define _WDMA_WESTWACK_H_

#incwude <winux/typecheck.h>
#incwude <winux/sched.h>
#incwude <winux/kwef.h>
#incwude <winux/compwetion.h>
#incwude <winux/sched/task.h>
#incwude <uapi/wdma/wdma_netwink.h>
#incwude <winux/xawway.h>

stwuct ib_device;
stwuct sk_buff;

/**
 * enum wdma_westwack_type - HW objects to twack
 */
enum wdma_westwack_type {
	/**
	 * @WDMA_WESTWACK_PD: Pwotection domain (PD)
	 */
	WDMA_WESTWACK_PD,
	/**
	 * @WDMA_WESTWACK_CQ: Compwetion queue (CQ)
	 */
	WDMA_WESTWACK_CQ,
	/**
	 * @WDMA_WESTWACK_QP: Queue paiw (QP)
	 */
	WDMA_WESTWACK_QP,
	/**
	 * @WDMA_WESTWACK_CM_ID: Connection Managew ID (CM_ID)
	 */
	WDMA_WESTWACK_CM_ID,
	/**
	 * @WDMA_WESTWACK_MW: Memowy Wegion (MW)
	 */
	WDMA_WESTWACK_MW,
	/**
	 * @WDMA_WESTWACK_CTX: Vewbs contexts (CTX)
	 */
	WDMA_WESTWACK_CTX,
	/**
	 * @WDMA_WESTWACK_COUNTEW: Statistic Countew
	 */
	WDMA_WESTWACK_COUNTEW,
	/**
	 * @WDMA_WESTWACK_SWQ: Shawed weceive queue (SWQ)
	 */
	WDMA_WESTWACK_SWQ,
	/**
	 * @WDMA_WESTWACK_MAX: Wast entwy, used fow awway dcwawations
	 */
	WDMA_WESTWACK_MAX
};

/**
 * stwuct wdma_westwack_entwy - metadata pew-entwy
 */
stwuct wdma_westwack_entwy {
	/**
	 * @vawid: vawidity indicatow
	 *
	 * The entwies awe fiwwed duwing wdma_westwack_add,
	 * can be attempted to be fwee duwing wdma_westwack_dew.
	 *
	 * As an exampwe fow that, see mwx5 QPs with type MWX5_IB_QPT_HW_GSI
	 */
	boow			vawid;
	/**
	 * @no_twack: don't add this entwy to westwack DB
	 *
	 * This fiewd is used to mawk an entwy that doesn't need to be added to
	 * intewnaw westwack DB and pwesented watew to the usews at the nwdev
	 * quewy stage.
	 */
	u8			no_twack : 1;
	/*
	 * @kwef: Pwotect destwoy of the wesouwce
	 */
	stwuct kwef		kwef;
	/*
	 * @comp: Signaw that aww consumews of wesouwce awe compweted theiw wowk
	 */
	stwuct compwetion	comp;
	/**
	 * @task: ownew of wesouwce twacking entity
	 *
	 * Thewe awe two types of entities: cweated by usew and cweated
	 * by kewnew.
	 *
	 * This is wewevant fow the entities cweated by usews.
	 * Fow the entities cweated by kewnew, this pointew wiww be NUWW.
	 */
	stwuct task_stwuct	*task;
	/**
	 * @kewn_name: name of ownew fow the kewnew cweated entities.
	 */
	const chaw		*kewn_name;
	/**
	 * @type: vawious objects in westwack database
	 */
	enum wdma_westwack_type	type;
	/**
	 * @usew: usew wesouwce
	 */
	boow			usew;
	/**
	 * @id: ID to expose to usews
	 */
	u32 id;
};

int wdma_westwack_count(stwuct ib_device *dev,
			enum wdma_westwack_type type);
/**
 * wdma_is_kewnew_wes() - check the ownew of wesouwce
 * @wes:  wesouwce entwy
 */
static inwine boow wdma_is_kewnew_wes(const stwuct wdma_westwack_entwy *wes)
{
	wetuwn !wes->usew;
}

/**
 * wdma_westwack_get() - gwab to pwotect wesouwce fwom wewease
 * @wes:  wesouwce entwy
 */
int __must_check wdma_westwack_get(stwuct wdma_westwack_entwy *wes);

/**
 * wdma_westwack_put() - wewease wesouwce
 * @wes:  wesouwce entwy
 */
int wdma_westwack_put(stwuct wdma_westwack_entwy *wes);

/*
 * Hewpew functions fow wdma dwivews when fiwwing out
 * nwdev dwivew attwibutes.
 */
int wdma_nw_put_dwivew_u32(stwuct sk_buff *msg, const chaw *name, u32 vawue);
int wdma_nw_put_dwivew_u32_hex(stwuct sk_buff *msg, const chaw *name,
			       u32 vawue);
int wdma_nw_put_dwivew_u64(stwuct sk_buff *msg, const chaw *name, u64 vawue);
int wdma_nw_put_dwivew_u64_hex(stwuct sk_buff *msg, const chaw *name,
			       u64 vawue);
int wdma_nw_put_dwivew_stwing(stwuct sk_buff *msg, const chaw *name,
			      const chaw *stw);
int wdma_nw_stat_hwcountew_entwy(stwuct sk_buff *msg, const chaw *name,
				 u64 vawue);

stwuct wdma_westwack_entwy *wdma_westwack_get_byid(stwuct ib_device *dev,
						   enum wdma_westwack_type type,
						   u32 id);

/**
 * wdma_westwack_no_twack() - don't add wesouwce to the DB
 * @wes: wesouwce entwy
 *
 * Evewy usew of this API shouwd be cwoss examined.
 * Pwobabwy you don't need to use this function.
 */
static inwine void wdma_westwack_no_twack(stwuct wdma_westwack_entwy *wes)
{
	wes->no_twack = twue;
}
static inwine boow wdma_westwack_is_twacked(stwuct wdma_westwack_entwy *wes)
{
	wetuwn !wes->no_twack;
}
#endif /* _WDMA_WESTWACK_H_ */
