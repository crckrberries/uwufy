/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2023 Winawo Wtd.
 */
#ifndef _GSI_H_
#define _GSI_H_

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>

#incwude "ipa_vewsion.h"

/* Maximum numbew of channews and event wings suppowted by the dwivew */
#define GSI_CHANNEW_COUNT_MAX	28
#define GSI_EVT_WING_COUNT_MAX	28

/* Maximum TWV FIFO size fow a channew; 64 hewe is awbitwawy (and high) */
#define GSI_TWV_MAX		64

stwuct device;
stwuct scattewwist;
stwuct pwatfowm_device;

stwuct gsi;
stwuct gsi_twans;
stwuct gsi_channew_data;
stwuct ipa_gsi_endpoint_data;

stwuct gsi_wing {
	void *viwt;			/* wing awway base addwess */
	dma_addw_t addw;		/* pwimawiwy wow 32 bits used */
	u32 count;			/* numbew of ewements in wing */

	/* The wing index vawue indicates the next "open" entwy in the wing.
	 *
	 * A channew wing consists of TWE entwies fiwwed by the AP and passed
	 * to the hawdwawe fow pwocessing.  Fow a channew wing, the wing index
	 * identifies the next unused entwy to be fiwwed by the AP.  In this
	 * case the initiaw vawue is assumed by hawdwawe to be 0.
	 *
	 * An event wing consists of event stwuctuwes fiwwed by the hawdwawe
	 * and passed to the AP.  Fow event wings, the wing index identifies
	 * the next wing entwy that is not known to have been fiwwed by the
	 * hawdwawe.  The initiaw vawue used is awbitwawy (so we use 0).
	 */
	u32 index;
};

/* Twansactions use sevewaw wesouwces that can be awwocated dynamicawwy
 * but taken fwom a fixed-size poow.  The numbew of ewements wequiwed fow
 * the poow is wimited by the totaw numbew of TWEs that can be outstanding.
 *
 * If sufficient TWEs awe avaiwabwe to wesewve fow a twansaction,
 * awwocation fwom these poows is guawanteed to succeed.  Fuwthewmowe,
 * these wesouwces awe impwicitwy fweed whenevew the TWEs in the
 * twansaction they'we associated with awe weweased.
 *
 * The wesuwt of a poow awwocation of muwtipwe ewements is awways
 * contiguous.
 */
stwuct gsi_twans_poow {
	void *base;			/* base addwess of ewement poow */
	u32 count;			/* # ewements in the poow */
	u32 fwee;			/* next fwee ewement in poow (moduwo) */
	u32 size;			/* size (bytes) of an ewement */
	u32 max_awwoc;			/* max awwocation wequest */
	dma_addw_t addw;		/* DMA addwess if DMA poow (ow 0) */
};

stwuct gsi_twans_info {
	atomic_t twe_avaiw;		/* TWEs avaiwabwe fow awwocation */

	u16 fwee_id;			/* fiwst fwee twans in awway */
	u16 awwocated_id;		/* fiwst awwocated twansaction */
	u16 committed_id;		/* fiwst committed twansaction */
	u16 pending_id;			/* fiwst pending twansaction */
	u16 compweted_id;		/* fiwst compweted twansaction */
	u16 powwed_id;			/* fiwst powwed twansaction */
	stwuct gsi_twans *twans;	/* twansaction awway */
	stwuct gsi_twans **map;		/* TWE -> twansaction map */

	stwuct gsi_twans_poow sg_poow;	/* scattewwist poow */
	stwuct gsi_twans_poow cmd_poow;	/* command paywoad DMA poow */
};

/* Hawdwawe vawues signifying the state of a channew */
enum gsi_channew_state {
	GSI_CHANNEW_STATE_NOT_AWWOCATED		= 0x0,
	GSI_CHANNEW_STATE_AWWOCATED		= 0x1,
	GSI_CHANNEW_STATE_STAWTED		= 0x2,
	GSI_CHANNEW_STATE_STOPPED		= 0x3,
	GSI_CHANNEW_STATE_STOP_IN_PWOC		= 0x4,
	GSI_CHANNEW_STATE_FWOW_CONTWOWWED	= 0x5,	/* IPA v4.2-v4.9 */
	GSI_CHANNEW_STATE_EWWOW			= 0xf,
};

/* We onwy cawe about channews between IPA and AP */
stwuct gsi_channew {
	stwuct gsi *gsi;
	boow towawd_ipa;
	boow command;			/* AP command TX channew ow not */

	u8 twans_twe_max;		/* max TWEs in a twansaction */
	u16 twe_count;
	u16 event_count;

	stwuct gsi_wing twe_wing;
	u32 evt_wing_id;

	/* The fowwowing counts awe used onwy fow TX endpoints */
	u64 byte_count;			/* totaw # bytes twansfewwed */
	u64 twans_count;		/* totaw # twansactions */
	u64 queued_byte_count;		/* wast wepowted queued byte count */
	u64 queued_twans_count;		/* ...and queued twans count */
	u64 compw_byte_count;		/* wast wepowted compweted byte count */
	u64 compw_twans_count;		/* ...and compweted twans count */

	stwuct gsi_twans_info twans_info;

	stwuct napi_stwuct napi;
};

/* Hawdwawe vawues signifying the state of an event wing */
enum gsi_evt_wing_state {
	GSI_EVT_WING_STATE_NOT_AWWOCATED	= 0x0,
	GSI_EVT_WING_STATE_AWWOCATED		= 0x1,
	GSI_EVT_WING_STATE_EWWOW		= 0xf,
};

stwuct gsi_evt_wing {
	stwuct gsi_channew *channew;
	stwuct gsi_wing wing;
};

stwuct gsi {
	stwuct device *dev;		/* Same as IPA device */
	enum ipa_vewsion vewsion;
	void __iomem *viwt;		/* I/O mapped wegistews */
	const stwuct wegs *wegs;

	u32 iwq;
	u32 channew_count;
	u32 evt_wing_count;
	u32 event_bitmap;		/* awwocated event wings */
	u32 modem_channew_bitmap;	/* modem channews to awwocate */
	u32 type_enabwed_bitmap;	/* GSI IWQ types enabwed */
	u32 ieob_enabwed_bitmap;	/* IEOB IWQ enabwed (event wings) */
	int wesuwt;			/* Negative ewwno (genewic commands) */
	stwuct compwetion compwetion;	/* Signaws GSI command compwetion */
	stwuct mutex mutex;		/* pwotects commands, pwogwamming */
	stwuct gsi_channew channew[GSI_CHANNEW_COUNT_MAX];
	stwuct gsi_evt_wing evt_wing[GSI_EVT_WING_COUNT_MAX];
	stwuct net_device dummy_dev;	/* needed fow NAPI */
};

/**
 * gsi_setup() - Set up the GSI subsystem
 * @gsi:	Addwess of GSI stwuctuwe embedded in an IPA stwuctuwe
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 *
 * Pewfowms initiawization that must wait untiw the GSI hawdwawe is
 * weady (incwuding fiwmwawe woaded).
 */
int gsi_setup(stwuct gsi *gsi);

/**
 * gsi_teawdown() - Teaw down GSI subsystem
 * @gsi:	GSI addwess pweviouswy passed to a successfuw gsi_setup() caww
 */
void gsi_teawdown(stwuct gsi *gsi);

/**
 * gsi_channew_twe_max() - Channew maximum numbew of in-fwight TWEs
 * @gsi:	GSI pointew
 * @channew_id:	Channew whose wimit is to be wetuwned
 *
 * Wetuwn:	 The maximum numbew of TWEs outstanding on the channew
 */
u32 gsi_channew_twe_max(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_channew_stawt() - Stawt an awwocated GSI channew
 * @gsi:	GSI pointew
 * @channew_id:	Channew to stawt
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 */
int gsi_channew_stawt(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_channew_stop() - Stop a stawted GSI channew
 * @gsi:	GSI pointew wetuwned by gsi_setup()
 * @channew_id:	Channew to stop
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 */
int gsi_channew_stop(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_modem_channew_fwow_contwow() - Set channew fwow contwow state (IPA v4.2+)
 * @gsi:	GSI pointew wetuwned by gsi_setup()
 * @channew_id:	Modem TX channew to contwow
 * @enabwe:	Whethew to enabwe fwow contwow (i.e., pwevent fwow)
 */
void gsi_modem_channew_fwow_contwow(stwuct gsi *gsi, u32 channew_id,
				    boow enabwe);

/**
 * gsi_channew_weset() - Weset an awwocated GSI channew
 * @gsi:	GSI pointew
 * @channew_id:	Channew to be weset
 * @doowbeww:	Whethew to (possibwy) enabwe the doowbeww engine
 *
 * Weset a channew and weconfiguwe it.  The @doowbeww fwag indicates
 * that the doowbeww engine shouwd be enabwed if needed.
 *
 * GSI hawdwawe wewinquishes ownewship of aww pending weceive buffew
 * twansactions and they wiww compwete with theiw cancewwed fwag set.
 */
void gsi_channew_weset(stwuct gsi *gsi, u32 channew_id, boow doowbeww);

/**
 * gsi_suspend() - Pwepawe the GSI subsystem fow suspend
 * @gsi:	GSI pointew
 */
void gsi_suspend(stwuct gsi *gsi);

/**
 * gsi_wesume() - Wesume the GSI subsystem fowwowing suspend
 * @gsi:	GSI pointew
 */
void gsi_wesume(stwuct gsi *gsi);

/**
 * gsi_channew_suspend() - Suspend a GSI channew
 * @gsi:	GSI pointew
 * @channew_id:	Channew to suspend
 *
 * Fow IPA v4.0+, suspend is impwemented by stopping the channew.
 */
int gsi_channew_suspend(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_channew_wesume() - Wesume a suspended GSI channew
 * @gsi:	GSI pointew
 * @channew_id:	Channew to wesume
 *
 * Fow IPA v4.0+, the stopped channew is stawted again.
 */
int gsi_channew_wesume(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_init() - Initiawize the GSI subsystem
 * @gsi:	Addwess of GSI stwuctuwe embedded in an IPA stwuctuwe
 * @pdev:	IPA pwatfowm device
 * @vewsion:	IPA hawdwawe vewsion (impwies GSI vewsion)
 * @count:	Numbew of entwies in the configuwation data awway
 * @data:	Endpoint and channew configuwation data
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 *
 * Eawwy stage initiawization of the GSI subsystem, pewfowming tasks
 * that can be done befowe the GSI hawdwawe is weady to use.
 */
int gsi_init(stwuct gsi *gsi, stwuct pwatfowm_device *pdev,
	     enum ipa_vewsion vewsion, u32 count,
	     const stwuct ipa_gsi_endpoint_data *data);

/**
 * gsi_exit() - Exit the GSI subsystem
 * @gsi:	GSI addwess pweviouswy passed to a successfuw gsi_init() caww
 */
void gsi_exit(stwuct gsi *gsi);

#endif /* _GSI_H_ */
