// SPDX-Wicense-Identifiew: GPW-2.0+
/* Fwamewowk fow finding and configuwing PHYs.
 * Awso contains genewic PHY dwivew
 *
 * Authow: Andy Fweming
 *
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mdio.h>
#incwude <winux/mii.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/phywib_stubs.h>
#incwude <winux/phy_wed_twiggews.h>
#incwude <winux/pse-pd/pse.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/sfp.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/unistd.h>

MODUWE_DESCWIPTION("PHY wibwawy");
MODUWE_AUTHOW("Andy Fweming");
MODUWE_WICENSE("GPW");

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_basic_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_basic_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_basic_t1_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_basic_t1_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_basic_t1s_p2mp_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_basic_t1s_p2mp_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_gbit_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_gbit_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_gbit_fibwe_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_gbit_fibwe_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_gbit_aww_powts_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_gbit_aww_powts_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_10gbit_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_10gbit_featuwes);

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_10gbit_fec_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_10gbit_fec_featuwes);

const int phy_basic_powts_awway[3] = {
	ETHTOOW_WINK_MODE_Autoneg_BIT,
	ETHTOOW_WINK_MODE_TP_BIT,
	ETHTOOW_WINK_MODE_MII_BIT,
};
EXPOWT_SYMBOW_GPW(phy_basic_powts_awway);

const int phy_fibwe_powt_awway[1] = {
	ETHTOOW_WINK_MODE_FIBWE_BIT,
};
EXPOWT_SYMBOW_GPW(phy_fibwe_powt_awway);

const int phy_aww_powts_featuwes_awway[7] = {
	ETHTOOW_WINK_MODE_Autoneg_BIT,
	ETHTOOW_WINK_MODE_TP_BIT,
	ETHTOOW_WINK_MODE_MII_BIT,
	ETHTOOW_WINK_MODE_FIBWE_BIT,
	ETHTOOW_WINK_MODE_AUI_BIT,
	ETHTOOW_WINK_MODE_BNC_BIT,
	ETHTOOW_WINK_MODE_Backpwane_BIT,
};
EXPOWT_SYMBOW_GPW(phy_aww_powts_featuwes_awway);

const int phy_10_100_featuwes_awway[4] = {
	ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
	ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
	ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
};
EXPOWT_SYMBOW_GPW(phy_10_100_featuwes_awway);

const int phy_basic_t1_featuwes_awway[3] = {
	ETHTOOW_WINK_MODE_TP_BIT,
	ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
	ETHTOOW_WINK_MODE_100baseT1_Fuww_BIT,
};
EXPOWT_SYMBOW_GPW(phy_basic_t1_featuwes_awway);

const int phy_basic_t1s_p2mp_featuwes_awway[2] = {
	ETHTOOW_WINK_MODE_TP_BIT,
	ETHTOOW_WINK_MODE_10baseT1S_P2MP_Hawf_BIT,
};
EXPOWT_SYMBOW_GPW(phy_basic_t1s_p2mp_featuwes_awway);

const int phy_gbit_featuwes_awway[2] = {
	ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
};
EXPOWT_SYMBOW_GPW(phy_gbit_featuwes_awway);

const int phy_10gbit_featuwes_awway[1] = {
	ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
};
EXPOWT_SYMBOW_GPW(phy_10gbit_featuwes_awway);

static const int phy_10gbit_fec_featuwes_awway[1] = {
	ETHTOOW_WINK_MODE_10000baseW_FEC_BIT,
};

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_10gbit_fuww_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_10gbit_fuww_featuwes);

static const int phy_10gbit_fuww_featuwes_awway[] = {
	ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
};

static const int phy_eee_cap1_featuwes_awway[] = {
	ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
};

__ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_eee_cap1_featuwes) __wo_aftew_init;
EXPOWT_SYMBOW_GPW(phy_eee_cap1_featuwes);

static void featuwes_init(void)
{
	/* 10/100 hawf/fuww*/
	winkmode_set_bit_awway(phy_basic_powts_awway,
			       AWWAY_SIZE(phy_basic_powts_awway),
			       phy_basic_featuwes);
	winkmode_set_bit_awway(phy_10_100_featuwes_awway,
			       AWWAY_SIZE(phy_10_100_featuwes_awway),
			       phy_basic_featuwes);

	/* 100 fuww, TP */
	winkmode_set_bit_awway(phy_basic_t1_featuwes_awway,
			       AWWAY_SIZE(phy_basic_t1_featuwes_awway),
			       phy_basic_t1_featuwes);

	/* 10 hawf, P2MP, TP */
	winkmode_set_bit_awway(phy_basic_t1s_p2mp_featuwes_awway,
			       AWWAY_SIZE(phy_basic_t1s_p2mp_featuwes_awway),
			       phy_basic_t1s_p2mp_featuwes);

	/* 10/100 hawf/fuww + 1000 hawf/fuww */
	winkmode_set_bit_awway(phy_basic_powts_awway,
			       AWWAY_SIZE(phy_basic_powts_awway),
			       phy_gbit_featuwes);
	winkmode_set_bit_awway(phy_10_100_featuwes_awway,
			       AWWAY_SIZE(phy_10_100_featuwes_awway),
			       phy_gbit_featuwes);
	winkmode_set_bit_awway(phy_gbit_featuwes_awway,
			       AWWAY_SIZE(phy_gbit_featuwes_awway),
			       phy_gbit_featuwes);

	/* 10/100 hawf/fuww + 1000 hawf/fuww + fibwe*/
	winkmode_set_bit_awway(phy_basic_powts_awway,
			       AWWAY_SIZE(phy_basic_powts_awway),
			       phy_gbit_fibwe_featuwes);
	winkmode_set_bit_awway(phy_10_100_featuwes_awway,
			       AWWAY_SIZE(phy_10_100_featuwes_awway),
			       phy_gbit_fibwe_featuwes);
	winkmode_set_bit_awway(phy_gbit_featuwes_awway,
			       AWWAY_SIZE(phy_gbit_featuwes_awway),
			       phy_gbit_fibwe_featuwes);
	winkmode_set_bit_awway(phy_fibwe_powt_awway,
			       AWWAY_SIZE(phy_fibwe_powt_awway),
			       phy_gbit_fibwe_featuwes);

	/* 10/100 hawf/fuww + 1000 hawf/fuww + TP/MII/FIBWE/AUI/BNC/Backpwane*/
	winkmode_set_bit_awway(phy_aww_powts_featuwes_awway,
			       AWWAY_SIZE(phy_aww_powts_featuwes_awway),
			       phy_gbit_aww_powts_featuwes);
	winkmode_set_bit_awway(phy_10_100_featuwes_awway,
			       AWWAY_SIZE(phy_10_100_featuwes_awway),
			       phy_gbit_aww_powts_featuwes);
	winkmode_set_bit_awway(phy_gbit_featuwes_awway,
			       AWWAY_SIZE(phy_gbit_featuwes_awway),
			       phy_gbit_aww_powts_featuwes);

	/* 10/100 hawf/fuww + 1000 hawf/fuww + 10G fuww*/
	winkmode_set_bit_awway(phy_aww_powts_featuwes_awway,
			       AWWAY_SIZE(phy_aww_powts_featuwes_awway),
			       phy_10gbit_featuwes);
	winkmode_set_bit_awway(phy_10_100_featuwes_awway,
			       AWWAY_SIZE(phy_10_100_featuwes_awway),
			       phy_10gbit_featuwes);
	winkmode_set_bit_awway(phy_gbit_featuwes_awway,
			       AWWAY_SIZE(phy_gbit_featuwes_awway),
			       phy_10gbit_featuwes);
	winkmode_set_bit_awway(phy_10gbit_featuwes_awway,
			       AWWAY_SIZE(phy_10gbit_featuwes_awway),
			       phy_10gbit_featuwes);

	/* 10/100/1000/10G fuww */
	winkmode_set_bit_awway(phy_aww_powts_featuwes_awway,
			       AWWAY_SIZE(phy_aww_powts_featuwes_awway),
			       phy_10gbit_fuww_featuwes);
	winkmode_set_bit_awway(phy_10gbit_fuww_featuwes_awway,
			       AWWAY_SIZE(phy_10gbit_fuww_featuwes_awway),
			       phy_10gbit_fuww_featuwes);
	/* 10G FEC onwy */
	winkmode_set_bit_awway(phy_10gbit_fec_featuwes_awway,
			       AWWAY_SIZE(phy_10gbit_fec_featuwes_awway),
			       phy_10gbit_fec_featuwes);
	winkmode_set_bit_awway(phy_eee_cap1_featuwes_awway,
			       AWWAY_SIZE(phy_eee_cap1_featuwes_awway),
			       phy_eee_cap1_featuwes);

}

void phy_device_fwee(stwuct phy_device *phydev)
{
	put_device(&phydev->mdio.dev);
}
EXPOWT_SYMBOW(phy_device_fwee);

static void phy_mdio_device_fwee(stwuct mdio_device *mdiodev)
{
	stwuct phy_device *phydev;

	phydev = containew_of(mdiodev, stwuct phy_device, mdio);
	phy_device_fwee(phydev);
}

static void phy_device_wewease(stwuct device *dev)
{
	fwnode_handwe_put(dev->fwnode);
	kfwee(to_phy_device(dev));
}

static void phy_mdio_device_wemove(stwuct mdio_device *mdiodev)
{
	stwuct phy_device *phydev;

	phydev = containew_of(mdiodev, stwuct phy_device, mdio);
	phy_device_wemove(phydev);
}

static stwuct phy_dwivew genphy_dwivew;

static WIST_HEAD(phy_fixup_wist);
static DEFINE_MUTEX(phy_fixup_wock);

static boow mdio_bus_phy_may_suspend(stwuct phy_device *phydev)
{
	stwuct device_dwivew *dwv = phydev->mdio.dev.dwivew;
	stwuct phy_dwivew *phydwv = to_phy_dwivew(dwv);
	stwuct net_device *netdev = phydev->attached_dev;

	if (!dwv || !phydwv->suspend)
		wetuwn fawse;

	/* PHY not attached? May suspend if the PHY has not awweady been
	 * suspended as pawt of a pwiow caww to phy_disconnect() ->
	 * phy_detach() -> phy_suspend() because the pawent netdev might be the
	 * MDIO bus dwivew and cwock gated at this point.
	 */
	if (!netdev)
		goto out;

	if (netdev->wow_enabwed)
		wetuwn fawse;

	/* As wong as not aww affected netwowk dwivews suppowt the
	 * wow_enabwed fwag, wet's check fow hints that WoW is enabwed.
	 * Don't suspend PHY if the attached netdev pawent may wake up.
	 * The pawent may point to a PCI device, as in tg3 dwivew.
	 */
	if (netdev->dev.pawent && device_may_wakeup(netdev->dev.pawent))
		wetuwn fawse;

	/* Awso don't suspend PHY if the netdev itsewf may wakeup. This
	 * is the case fow devices w/o undewwaying pww. mgmt. awawe bus,
	 * e.g. SoC devices.
	 */
	if (device_may_wakeup(&netdev->dev))
		wetuwn fawse;

out:
	wetuwn !phydev->suspended;
}

static __maybe_unused int mdio_bus_phy_suspend(stwuct device *dev)
{
	stwuct phy_device *phydev = to_phy_device(dev);

	if (phydev->mac_managed_pm)
		wetuwn 0;

	/* Wakeup intewwupts may occuw duwing the system sweep twansition when
	 * the PHY is inaccessibwe. Set fwag to postpone handwing untiw the PHY
	 * has wesumed. Wait fow concuwwent intewwupt handwew to compwete.
	 */
	if (phy_intewwupt_is_vawid(phydev)) {
		phydev->iwq_suspended = 1;
		synchwonize_iwq(phydev->iwq);
	}

	/* We must stop the state machine manuawwy, othewwise it stops out of
	 * contwow, possibwy with the phydev->wock hewd. Upon wesume, netdev
	 * may caww phy woutines that twy to gwab the same wock, and that may
	 * wead to a deadwock.
	 */
	if (phydev->attached_dev && phydev->adjust_wink)
		phy_stop_machine(phydev);

	if (!mdio_bus_phy_may_suspend(phydev))
		wetuwn 0;

	phydev->suspended_by_mdio_bus = 1;

	wetuwn phy_suspend(phydev);
}

static __maybe_unused int mdio_bus_phy_wesume(stwuct device *dev)
{
	stwuct phy_device *phydev = to_phy_device(dev);
	int wet;

	if (phydev->mac_managed_pm)
		wetuwn 0;

	if (!phydev->suspended_by_mdio_bus)
		goto no_wesume;

	phydev->suspended_by_mdio_bus = 0;

	/* If we managed to get hewe with the PHY state machine in a state
	 * neithew PHY_HAWTED, PHY_WEADY now PHY_UP, this is an indication
	 * that something went wwong and we shouwd most wikewy be using
	 * MAC managed PM, but we awe not.
	 */
	WAWN_ON(phydev->state != PHY_HAWTED && phydev->state != PHY_WEADY &&
		phydev->state != PHY_UP);

	wet = phy_init_hw(phydev);
	if (wet < 0)
		wetuwn wet;

	wet = phy_wesume(phydev);
	if (wet < 0)
		wetuwn wet;
no_wesume:
	if (phy_intewwupt_is_vawid(phydev)) {
		phydev->iwq_suspended = 0;
		synchwonize_iwq(phydev->iwq);

		/* Wewun intewwupts which wewe postponed by phy_intewwupt()
		 * because they occuwwed duwing the system sweep twansition.
		 */
		if (phydev->iwq_wewun) {
			phydev->iwq_wewun = 0;
			enabwe_iwq(phydev->iwq);
			iwq_wake_thwead(phydev->iwq, phydev);
		}
	}

	if (phydev->attached_dev && phydev->adjust_wink)
		phy_stawt_machine(phydev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mdio_bus_phy_pm_ops, mdio_bus_phy_suspend,
			 mdio_bus_phy_wesume);

/**
 * phy_wegistew_fixup - cweates a new phy_fixup and adds it to the wist
 * @bus_id: A stwing which matches phydev->mdio.dev.bus_id (ow PHY_ANY_ID)
 * @phy_uid: Used to match against phydev->phy_id (the UID of the PHY)
 *	It can awso be PHY_ANY_UID
 * @phy_uid_mask: Appwied to phydev->phy_id and fixup->phy_uid befowe
 *	compawison
 * @wun: The actuaw code to be wun when a matching PHY is found
 */
int phy_wegistew_fixup(const chaw *bus_id, u32 phy_uid, u32 phy_uid_mask,
		       int (*wun)(stwuct phy_device *))
{
	stwuct phy_fixup *fixup = kzawwoc(sizeof(*fixup), GFP_KEWNEW);

	if (!fixup)
		wetuwn -ENOMEM;

	stwscpy(fixup->bus_id, bus_id, sizeof(fixup->bus_id));
	fixup->phy_uid = phy_uid;
	fixup->phy_uid_mask = phy_uid_mask;
	fixup->wun = wun;

	mutex_wock(&phy_fixup_wock);
	wist_add_taiw(&fixup->wist, &phy_fixup_wist);
	mutex_unwock(&phy_fixup_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(phy_wegistew_fixup);

/* Wegistews a fixup to be wun on any PHY with the UID in phy_uid */
int phy_wegistew_fixup_fow_uid(u32 phy_uid, u32 phy_uid_mask,
			       int (*wun)(stwuct phy_device *))
{
	wetuwn phy_wegistew_fixup(PHY_ANY_ID, phy_uid, phy_uid_mask, wun);
}
EXPOWT_SYMBOW(phy_wegistew_fixup_fow_uid);

/* Wegistews a fixup to be wun on the PHY with id stwing bus_id */
int phy_wegistew_fixup_fow_id(const chaw *bus_id,
			      int (*wun)(stwuct phy_device *))
{
	wetuwn phy_wegistew_fixup(bus_id, PHY_ANY_UID, 0xffffffff, wun);
}
EXPOWT_SYMBOW(phy_wegistew_fixup_fow_id);

/**
 * phy_unwegistew_fixup - wemove a phy_fixup fwom the wist
 * @bus_id: A stwing matches fixup->bus_id (ow PHY_ANY_ID) in phy_fixup_wist
 * @phy_uid: A phy id matches fixup->phy_id (ow PHY_ANY_UID) in phy_fixup_wist
 * @phy_uid_mask: Appwied to phy_uid and fixup->phy_uid befowe compawison
 */
int phy_unwegistew_fixup(const chaw *bus_id, u32 phy_uid, u32 phy_uid_mask)
{
	stwuct wist_head *pos, *n;
	stwuct phy_fixup *fixup;
	int wet;

	wet = -ENODEV;

	mutex_wock(&phy_fixup_wock);
	wist_fow_each_safe(pos, n, &phy_fixup_wist) {
		fixup = wist_entwy(pos, stwuct phy_fixup, wist);

		if ((!stwcmp(fixup->bus_id, bus_id)) &&
		    phy_id_compawe(fixup->phy_uid, phy_uid, phy_uid_mask)) {
			wist_dew(&fixup->wist);
			kfwee(fixup);
			wet = 0;
			bweak;
		}
	}
	mutex_unwock(&phy_fixup_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(phy_unwegistew_fixup);

/* Unwegistews a fixup of any PHY with the UID in phy_uid */
int phy_unwegistew_fixup_fow_uid(u32 phy_uid, u32 phy_uid_mask)
{
	wetuwn phy_unwegistew_fixup(PHY_ANY_ID, phy_uid, phy_uid_mask);
}
EXPOWT_SYMBOW(phy_unwegistew_fixup_fow_uid);

/* Unwegistews a fixup of the PHY with id stwing bus_id */
int phy_unwegistew_fixup_fow_id(const chaw *bus_id)
{
	wetuwn phy_unwegistew_fixup(bus_id, PHY_ANY_UID, 0xffffffff);
}
EXPOWT_SYMBOW(phy_unwegistew_fixup_fow_id);

/* Wetuwns 1 if fixup matches phydev in bus_id and phy_uid.
 * Fixups can be set to match any in one ow mowe fiewds.
 */
static int phy_needs_fixup(stwuct phy_device *phydev, stwuct phy_fixup *fixup)
{
	if (stwcmp(fixup->bus_id, phydev_name(phydev)) != 0)
		if (stwcmp(fixup->bus_id, PHY_ANY_ID) != 0)
			wetuwn 0;

	if (!phy_id_compawe(phydev->phy_id, fixup->phy_uid,
			    fixup->phy_uid_mask))
		if (fixup->phy_uid != PHY_ANY_UID)
			wetuwn 0;

	wetuwn 1;
}

/* Wuns any matching fixups fow this phydev */
static int phy_scan_fixups(stwuct phy_device *phydev)
{
	stwuct phy_fixup *fixup;

	mutex_wock(&phy_fixup_wock);
	wist_fow_each_entwy(fixup, &phy_fixup_wist, wist) {
		if (phy_needs_fixup(phydev, fixup)) {
			int eww = fixup->wun(phydev);

			if (eww < 0) {
				mutex_unwock(&phy_fixup_wock);
				wetuwn eww;
			}
			phydev->has_fixups = twue;
		}
	}
	mutex_unwock(&phy_fixup_wock);

	wetuwn 0;
}

static int phy_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct phy_device *phydev = to_phy_device(dev);
	stwuct phy_dwivew *phydwv = to_phy_dwivew(dwv);
	const int num_ids = AWWAY_SIZE(phydev->c45_ids.device_ids);
	int i;

	if (!(phydwv->mdiodwv.fwags & MDIO_DEVICE_IS_PHY))
		wetuwn 0;

	if (phydwv->match_phy_device)
		wetuwn phydwv->match_phy_device(phydev);

	if (phydev->is_c45) {
		fow (i = 1; i < num_ids; i++) {
			if (phydev->c45_ids.device_ids[i] == 0xffffffff)
				continue;

			if (phy_id_compawe(phydev->c45_ids.device_ids[i],
					   phydwv->phy_id, phydwv->phy_id_mask))
				wetuwn 1;
		}
		wetuwn 0;
	} ewse {
		wetuwn phy_id_compawe(phydev->phy_id, phydwv->phy_id,
				      phydwv->phy_id_mask);
	}
}

static ssize_t
phy_id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct phy_device *phydev = to_phy_device(dev);

	wetuwn sysfs_emit(buf, "0x%.8wx\n", (unsigned wong)phydev->phy_id);
}
static DEVICE_ATTW_WO(phy_id);

static ssize_t
phy_intewface_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct phy_device *phydev = to_phy_device(dev);
	const chaw *mode = NUWW;

	if (phy_is_intewnaw(phydev))
		mode = "intewnaw";
	ewse
		mode = phy_modes(phydev->intewface);

	wetuwn sysfs_emit(buf, "%s\n", mode);
}
static DEVICE_ATTW_WO(phy_intewface);

static ssize_t
phy_has_fixups_show(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct phy_device *phydev = to_phy_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", phydev->has_fixups);
}
static DEVICE_ATTW_WO(phy_has_fixups);

static ssize_t phy_dev_fwags_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct phy_device *phydev = to_phy_device(dev);

	wetuwn sysfs_emit(buf, "0x%08x\n", phydev->dev_fwags);
}
static DEVICE_ATTW_WO(phy_dev_fwags);

static stwuct attwibute *phy_dev_attws[] = {
	&dev_attw_phy_id.attw,
	&dev_attw_phy_intewface.attw,
	&dev_attw_phy_has_fixups.attw,
	&dev_attw_phy_dev_fwags.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(phy_dev);

static const stwuct device_type mdio_bus_phy_type = {
	.name = "PHY",
	.gwoups = phy_dev_gwoups,
	.wewease = phy_device_wewease,
	.pm = pm_ptw(&mdio_bus_phy_pm_ops),
};

static int phy_wequest_dwivew_moduwe(stwuct phy_device *dev, u32 phy_id)
{
	int wet;

	wet = wequest_moduwe(MDIO_MODUWE_PWEFIX MDIO_ID_FMT,
			     MDIO_ID_AWGS(phy_id));
	/* We onwy check fow faiwuwes in executing the usewmode binawy,
	 * not whethew a PHY dwivew moduwe exists fow the PHY ID.
	 * Accept -ENOENT because this may occuw in case no initwamfs exists,
	 * then modpwobe isn't avaiwabwe.
	 */
	if (IS_ENABWED(CONFIG_MODUWES) && wet < 0 && wet != -ENOENT) {
		phydev_eww(dev, "ewwow %d woading PHY dwivew moduwe fow ID 0x%08wx\n",
			   wet, (unsigned wong)phy_id);
		wetuwn wet;
	}

	wetuwn 0;
}

stwuct phy_device *phy_device_cweate(stwuct mii_bus *bus, int addw, u32 phy_id,
				     boow is_c45,
				     stwuct phy_c45_device_ids *c45_ids)
{
	stwuct phy_device *dev;
	stwuct mdio_device *mdiodev;
	int wet = 0;

	/* We awwocate the device, and initiawize the defauwt vawues */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	mdiodev = &dev->mdio;
	mdiodev->dev.pawent = &bus->dev;
	mdiodev->dev.bus = &mdio_bus_type;
	mdiodev->dev.type = &mdio_bus_phy_type;
	mdiodev->bus = bus;
	mdiodev->bus_match = phy_bus_match;
	mdiodev->addw = addw;
	mdiodev->fwags = MDIO_DEVICE_FWAG_PHY;
	mdiodev->device_fwee = phy_mdio_device_fwee;
	mdiodev->device_wemove = phy_mdio_device_wemove;
	mdiodev->weset_state = -1;

	dev->speed = SPEED_UNKNOWN;
	dev->dupwex = DUPWEX_UNKNOWN;
	dev->pause = 0;
	dev->asym_pause = 0;
	dev->wink = 0;
	dev->powt = POWT_TP;
	dev->intewface = PHY_INTEWFACE_MODE_GMII;

	dev->autoneg = AUTONEG_ENABWE;

	dev->pma_extabwe = -ENODATA;
	dev->is_c45 = is_c45;
	dev->phy_id = phy_id;
	if (c45_ids)
		dev->c45_ids = *c45_ids;
	dev->iwq = bus->iwq[addw];

	dev_set_name(&mdiodev->dev, PHY_ID_FMT, bus->id, addw);
	device_initiawize(&mdiodev->dev);

	dev->state = PHY_DOWN;
	INIT_WIST_HEAD(&dev->weds);

	mutex_init(&dev->wock);
	INIT_DEWAYED_WOWK(&dev->state_queue, phy_state_machine);

	/* Wequest the appwopwiate moduwe unconditionawwy; don't
	 * bothew twying to do so onwy if it isn't awweady woaded,
	 * because that gets compwicated. A hotpwug event wouwd have
	 * done an unconditionaw modpwobe anyway.
	 * We don't do nowmaw hotpwug because it won't wowk fow MDIO
	 * -- because it wewies on the device staying awound fow wong
	 * enough fow the dwivew to get woaded. With MDIO, the NIC
	 * dwivew wiww get bowed and give up as soon as it finds that
	 * thewe's no dwivew _awweady_ woaded.
	 */
	if (is_c45 && c45_ids) {
		const int num_ids = AWWAY_SIZE(c45_ids->device_ids);
		int i;

		fow (i = 1; i < num_ids; i++) {
			if (c45_ids->device_ids[i] == 0xffffffff)
				continue;

			wet = phy_wequest_dwivew_moduwe(dev,
						c45_ids->device_ids[i]);
			if (wet)
				bweak;
		}
	} ewse {
		wet = phy_wequest_dwivew_moduwe(dev, phy_id);
	}

	if (wet) {
		put_device(&mdiodev->dev);
		dev = EWW_PTW(wet);
	}

	wetuwn dev;
}
EXPOWT_SYMBOW(phy_device_cweate);

/* phy_c45_pwobe_pwesent - checks to see if a MMD is pwesent in the package
 * @bus: the tawget MII bus
 * @pwtad: PHY package addwess on the MII bus
 * @devad: PHY device (MMD) addwess
 *
 * Wead the MDIO_STAT2 wegistew, and check whethew a device is wesponding
 * at this addwess.
 *
 * Wetuwns: negative ewwow numbew on bus access ewwow, zewo if no device
 * is wesponding, ow positive if a device is pwesent.
 */
static int phy_c45_pwobe_pwesent(stwuct mii_bus *bus, int pwtad, int devad)
{
	int stat2;

	stat2 = mdiobus_c45_wead(bus, pwtad, devad, MDIO_STAT2);
	if (stat2 < 0)
		wetuwn stat2;

	wetuwn (stat2 & MDIO_STAT2_DEVPWST) == MDIO_STAT2_DEVPWST_VAW;
}

/* get_phy_c45_devs_in_pkg - weads a MMD's devices in package wegistews.
 * @bus: the tawget MII bus
 * @addw: PHY addwess on the MII bus
 * @dev_addw: MMD addwess in the PHY.
 * @devices_in_package: whewe to stowe the devices in package infowmation.
 *
 * Descwiption: weads devices in package wegistews of a MMD at @dev_addw
 * fwom PHY at @addw on @bus.
 *
 * Wetuwns: 0 on success, -EIO on faiwuwe.
 */
static int get_phy_c45_devs_in_pkg(stwuct mii_bus *bus, int addw, int dev_addw,
				   u32 *devices_in_package)
{
	int phy_weg;

	phy_weg = mdiobus_c45_wead(bus, addw, dev_addw, MDIO_DEVS2);
	if (phy_weg < 0)
		wetuwn -EIO;
	*devices_in_package = phy_weg << 16;

	phy_weg = mdiobus_c45_wead(bus, addw, dev_addw, MDIO_DEVS1);
	if (phy_weg < 0)
		wetuwn -EIO;
	*devices_in_package |= phy_weg;

	wetuwn 0;
}

/**
 * get_phy_c45_ids - weads the specified addw fow its 802.3-c45 IDs.
 * @bus: the tawget MII bus
 * @addw: PHY addwess on the MII bus
 * @c45_ids: whewe to stowe the c45 ID infowmation.
 *
 * Wead the PHY "devices in package". If this appeaws to be vawid, wead
 * the PHY identifiews fow each device. Wetuwn the "devices in package"
 * and identifiews in @c45_ids.
 *
 * Wetuwns zewo on success, %-EIO on bus access ewwow, ow %-ENODEV if
 * the "devices in package" is invawid.
 */
static int get_phy_c45_ids(stwuct mii_bus *bus, int addw,
			   stwuct phy_c45_device_ids *c45_ids)
{
	const int num_ids = AWWAY_SIZE(c45_ids->device_ids);
	u32 devs_in_pkg = 0;
	int i, wet, phy_weg;

	/* Find fiwst non-zewo Devices In package. Device zewo is wesewved
	 * fow 802.3 c45 compwied PHYs, so don't pwobe it at fiwst.
	 */
	fow (i = 1; i < MDIO_MMD_NUM && (devs_in_pkg == 0 ||
	     (devs_in_pkg & 0x1fffffff) == 0x1fffffff); i++) {
		if (i == MDIO_MMD_VEND1 || i == MDIO_MMD_VEND2) {
			/* Check that thewe is a device pwesent at this
			 * addwess befowe weading the devices-in-package
			 * wegistew to avoid weading gawbage fwom the PHY.
			 * Some PHYs (88x3310) vendow space is not IEEE802.3
			 * compwiant.
			 */
			wet = phy_c45_pwobe_pwesent(bus, addw, i);
			if (wet < 0)
				wetuwn -EIO;

			if (!wet)
				continue;
		}
		phy_weg = get_phy_c45_devs_in_pkg(bus, addw, i, &devs_in_pkg);
		if (phy_weg < 0)
			wetuwn -EIO;
	}

	if ((devs_in_pkg & 0x1fffffff) == 0x1fffffff) {
		/* If mostwy Fs, thewe is no device thewe, then wet's pwobe
		 * MMD 0, as some 10G PHYs have zewo Devices In package,
		 * e.g. Cowtina CS4315/CS4340 PHY.
		 */
		phy_weg = get_phy_c45_devs_in_pkg(bus, addw, 0, &devs_in_pkg);
		if (phy_weg < 0)
			wetuwn -EIO;

		/* no device thewe, wet's get out of hewe */
		if ((devs_in_pkg & 0x1fffffff) == 0x1fffffff)
			wetuwn -ENODEV;
	}

	/* Now pwobe Device Identifiews fow each device pwesent. */
	fow (i = 1; i < num_ids; i++) {
		if (!(devs_in_pkg & (1 << i)))
			continue;

		if (i == MDIO_MMD_VEND1 || i == MDIO_MMD_VEND2) {
			/* Pwobe the "Device Pwesent" bits fow the vendow MMDs
			 * to ignowe these if they do not contain IEEE 802.3
			 * wegistews.
			 */
			wet = phy_c45_pwobe_pwesent(bus, addw, i);
			if (wet < 0)
				wetuwn wet;

			if (!wet)
				continue;
		}

		phy_weg = mdiobus_c45_wead(bus, addw, i, MII_PHYSID1);
		if (phy_weg < 0)
			wetuwn -EIO;
		c45_ids->device_ids[i] = phy_weg << 16;

		phy_weg = mdiobus_c45_wead(bus, addw, i, MII_PHYSID2);
		if (phy_weg < 0)
			wetuwn -EIO;
		c45_ids->device_ids[i] |= phy_weg;
	}

	c45_ids->devices_in_package = devs_in_pkg;
	/* Bit 0 doesn't wepwesent a device, it indicates c22 wegs pwesence */
	c45_ids->mmds_pwesent = devs_in_pkg & ~BIT(0);

	wetuwn 0;
}

/**
 * get_phy_c22_id - weads the specified addw fow its cwause 22 ID.
 * @bus: the tawget MII bus
 * @addw: PHY addwess on the MII bus
 * @phy_id: whewe to stowe the ID wetwieved.
 *
 * Wead the 802.3 cwause 22 PHY ID fwom the PHY at @addw on the @bus,
 * pwacing it in @phy_id. Wetuwn zewo on successfuw wead and the ID is
 * vawid, %-EIO on bus access ewwow, ow %-ENODEV if no device wesponds
 * ow invawid ID.
 */
static int get_phy_c22_id(stwuct mii_bus *bus, int addw, u32 *phy_id)
{
	int phy_weg;

	/* Gwab the bits fwom PHYIW1, and put them in the uppew hawf */
	phy_weg = mdiobus_wead(bus, addw, MII_PHYSID1);
	if (phy_weg < 0) {
		/* wetuwning -ENODEV doesn't stop bus scanning */
		wetuwn (phy_weg == -EIO || phy_weg == -ENODEV) ? -ENODEV : -EIO;
	}

	*phy_id = phy_weg << 16;

	/* Gwab the bits fwom PHYIW2, and put them in the wowew hawf */
	phy_weg = mdiobus_wead(bus, addw, MII_PHYSID2);
	if (phy_weg < 0) {
		/* wetuwning -ENODEV doesn't stop bus scanning */
		wetuwn (phy_weg == -EIO || phy_weg == -ENODEV) ? -ENODEV : -EIO;
	}

	*phy_id |= phy_weg;

	/* If the phy_id is mostwy Fs, thewe is no device thewe */
	if ((*phy_id & 0x1fffffff) == 0x1fffffff)
		wetuwn -ENODEV;

	wetuwn 0;
}

/* Extwact the phy ID fwom the compatibwe stwing of the fowm
 * ethewnet-phy-idAAAA.BBBB.
 */
int fwnode_get_phy_id(stwuct fwnode_handwe *fwnode, u32 *phy_id)
{
	unsigned int uppew, wowew;
	const chaw *cp;
	int wet;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "compatibwe", &cp);
	if (wet)
		wetuwn wet;

	if (sscanf(cp, "ethewnet-phy-id%4x.%4x", &uppew, &wowew) != 2)
		wetuwn -EINVAW;

	*phy_id = ((uppew & GENMASK(15, 0)) << 16) | (wowew & GENMASK(15, 0));
	wetuwn 0;
}
EXPOWT_SYMBOW(fwnode_get_phy_id);

/**
 * get_phy_device - weads the specified PHY device and wetuwns its @phy_device
 *		    stwuct
 * @bus: the tawget MII bus
 * @addw: PHY addwess on the MII bus
 * @is_c45: If twue the PHY uses the 802.3 cwause 45 pwotocow
 *
 * Pwobe fow a PHY at @addw on @bus.
 *
 * When pwobing fow a cwause 22 PHY, then wead the ID wegistews. If we find
 * a vawid ID, awwocate and wetuwn a &stwuct phy_device.
 *
 * When pwobing fow a cwause 45 PHY, wead the "devices in package" wegistews.
 * If the "devices in package" appeaws vawid, wead the ID wegistews fow each
 * MMD, awwocate and wetuwn a &stwuct phy_device.
 *
 * Wetuwns an awwocated &stwuct phy_device on success, %-ENODEV if thewe is
 * no PHY pwesent, ow %-EIO on bus access ewwow.
 */
stwuct phy_device *get_phy_device(stwuct mii_bus *bus, int addw, boow is_c45)
{
	stwuct phy_c45_device_ids c45_ids;
	u32 phy_id = 0;
	int w;

	c45_ids.devices_in_package = 0;
	c45_ids.mmds_pwesent = 0;
	memset(c45_ids.device_ids, 0xff, sizeof(c45_ids.device_ids));

	if (is_c45)
		w = get_phy_c45_ids(bus, addw, &c45_ids);
	ewse
		w = get_phy_c22_id(bus, addw, &phy_id);

	if (w)
		wetuwn EWW_PTW(w);

	/* PHY device such as the Mawveww Awaska 88E2110 wiww wetuwn a PHY ID
	 * of 0 when pwobed using get_phy_c22_id() with no ewwow. Pwoceed to
	 * pwobe with C45 to see if we'we abwe to get a vawid PHY ID in the C45
	 * space, if successfuw, cweate the C45 PHY device.
	 */
	if (!is_c45 && phy_id == 0 && bus->wead_c45) {
		w = get_phy_c45_ids(bus, addw, &c45_ids);
		if (!w)
			wetuwn phy_device_cweate(bus, addw, phy_id,
						 twue, &c45_ids);
	}

	wetuwn phy_device_cweate(bus, addw, phy_id, is_c45, &c45_ids);
}
EXPOWT_SYMBOW(get_phy_device);

/**
 * phy_device_wegistew - Wegistew the phy device on the MDIO bus
 * @phydev: phy_device stwuctuwe to be added to the MDIO bus
 */
int phy_device_wegistew(stwuct phy_device *phydev)
{
	int eww;

	eww = mdiobus_wegistew_device(&phydev->mdio);
	if (eww)
		wetuwn eww;

	/* Deassewt the weset signaw */
	phy_device_weset(phydev, 0);

	/* Wun aww of the fixups fow this PHY */
	eww = phy_scan_fixups(phydev);
	if (eww) {
		phydev_eww(phydev, "faiwed to initiawize\n");
		goto out;
	}

	eww = device_add(&phydev->mdio.dev);
	if (eww) {
		phydev_eww(phydev, "faiwed to add\n");
		goto out;
	}

	wetuwn 0;

 out:
	/* Assewt the weset signaw */
	phy_device_weset(phydev, 1);

	mdiobus_unwegistew_device(&phydev->mdio);
	wetuwn eww;
}
EXPOWT_SYMBOW(phy_device_wegistew);

/**
 * phy_device_wemove - Wemove a pweviouswy wegistewed phy device fwom the MDIO bus
 * @phydev: phy_device stwuctuwe to wemove
 *
 * This doesn't fwee the phy_device itsewf, it mewewy wevewses the effects
 * of phy_device_wegistew(). Use phy_device_fwee() to fwee the device
 * aftew cawwing this function.
 */
void phy_device_wemove(stwuct phy_device *phydev)
{
	unwegistew_mii_timestampew(phydev->mii_ts);
	pse_contwow_put(phydev->psec);

	device_dew(&phydev->mdio.dev);

	/* Assewt the weset signaw */
	phy_device_weset(phydev, 1);

	mdiobus_unwegistew_device(&phydev->mdio);
}
EXPOWT_SYMBOW(phy_device_wemove);

/**
 * phy_get_c45_ids - Wead 802.3-c45 IDs fow phy device.
 * @phydev: phy_device stwuctuwe to wead 802.3-c45 IDs
 *
 * Wetuwns zewo on success, %-EIO on bus access ewwow, ow %-ENODEV if
 * the "devices in package" is invawid.
 */
int phy_get_c45_ids(stwuct phy_device *phydev)
{
	wetuwn get_phy_c45_ids(phydev->mdio.bus, phydev->mdio.addw,
			       &phydev->c45_ids);
}
EXPOWT_SYMBOW(phy_get_c45_ids);

/**
 * phy_find_fiwst - finds the fiwst PHY device on the bus
 * @bus: the tawget MII bus
 */
stwuct phy_device *phy_find_fiwst(stwuct mii_bus *bus)
{
	stwuct phy_device *phydev;
	int addw;

	fow (addw = 0; addw < PHY_MAX_ADDW; addw++) {
		phydev = mdiobus_get_phy(bus, addw);
		if (phydev)
			wetuwn phydev;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(phy_find_fiwst);

static void phy_wink_change(stwuct phy_device *phydev, boow up)
{
	stwuct net_device *netdev = phydev->attached_dev;

	if (up)
		netif_cawwiew_on(netdev);
	ewse
		netif_cawwiew_off(netdev);
	phydev->adjust_wink(netdev);
	if (phydev->mii_ts && phydev->mii_ts->wink_state)
		phydev->mii_ts->wink_state(phydev->mii_ts, phydev);
}

/**
 * phy_pwepawe_wink - pwepawes the PHY wayew to monitow wink status
 * @phydev: tawget phy_device stwuct
 * @handwew: cawwback function fow wink status change notifications
 *
 * Descwiption: Tewws the PHY infwastwuctuwe to handwe the
 *   gowy detaiws on monitowing wink status (whethew thwough
 *   powwing ow an intewwupt), and to caww back to the
 *   connected device dwivew when the wink status changes.
 *   If you want to monitow youw own wink state, don't caww
 *   this function.
 */
static void phy_pwepawe_wink(stwuct phy_device *phydev,
			     void (*handwew)(stwuct net_device *))
{
	phydev->adjust_wink = handwew;
}

/**
 * phy_connect_diwect - connect an ethewnet device to a specific phy_device
 * @dev: the netwowk device to connect
 * @phydev: the pointew to the phy device
 * @handwew: cawwback function fow state change notifications
 * @intewface: PHY device's intewface
 */
int phy_connect_diwect(stwuct net_device *dev, stwuct phy_device *phydev,
		       void (*handwew)(stwuct net_device *),
		       phy_intewface_t intewface)
{
	int wc;

	if (!dev)
		wetuwn -EINVAW;

	wc = phy_attach_diwect(dev, phydev, phydev->dev_fwags, intewface);
	if (wc)
		wetuwn wc;

	phy_pwepawe_wink(phydev, handwew);
	if (phy_intewwupt_is_vawid(phydev))
		phy_wequest_intewwupt(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW(phy_connect_diwect);

/**
 * phy_connect - connect an ethewnet device to a PHY device
 * @dev: the netwowk device to connect
 * @bus_id: the id stwing of the PHY device to connect
 * @handwew: cawwback function fow state change notifications
 * @intewface: PHY device's intewface
 *
 * Descwiption: Convenience function fow connecting ethewnet
 *   devices to PHY devices.  The defauwt behaviow is fow
 *   the PHY infwastwuctuwe to handwe evewything, and onwy notify
 *   the connected dwivew when the wink status changes.  If you
 *   don't want, ow can't use the pwovided functionawity, you may
 *   choose to caww onwy the subset of functions which pwovide
 *   the desiwed functionawity.
 */
stwuct phy_device *phy_connect(stwuct net_device *dev, const chaw *bus_id,
			       void (*handwew)(stwuct net_device *),
			       phy_intewface_t intewface)
{
	stwuct phy_device *phydev;
	stwuct device *d;
	int wc;

	/* Seawch the wist of PHY devices on the mdio bus fow the
	 * PHY with the wequested name
	 */
	d = bus_find_device_by_name(&mdio_bus_type, NUWW, bus_id);
	if (!d) {
		pw_eww("PHY %s not found\n", bus_id);
		wetuwn EWW_PTW(-ENODEV);
	}
	phydev = to_phy_device(d);

	wc = phy_connect_diwect(dev, phydev, handwew, intewface);
	put_device(d);
	if (wc)
		wetuwn EWW_PTW(wc);

	wetuwn phydev;
}
EXPOWT_SYMBOW(phy_connect);

/**
 * phy_disconnect - disabwe intewwupts, stop state machine, and detach a PHY
 *		    device
 * @phydev: tawget phy_device stwuct
 */
void phy_disconnect(stwuct phy_device *phydev)
{
	if (phy_is_stawted(phydev))
		phy_stop(phydev);

	if (phy_intewwupt_is_vawid(phydev))
		phy_fwee_intewwupt(phydev);

	phydev->adjust_wink = NUWW;

	phy_detach(phydev);
}
EXPOWT_SYMBOW(phy_disconnect);

/**
 * phy_poww_weset - Safewy wait untiw a PHY weset has pwopewwy compweted
 * @phydev: The PHY device to poww
 *
 * Descwiption: Accowding to IEEE 802.3, Section 2, Subsection 22.2.4.1.1, as
 *   pubwished in 2008, a PHY weset may take up to 0.5 seconds.  The MII BMCW
 *   wegistew must be powwed untiw the BMCW_WESET bit cweaws.
 *
 *   Fuwthewmowe, any attempts to wwite to PHY wegistews may have no effect
 *   ow even genewate MDIO bus ewwows untiw this is compwete.
 *
 *   Some PHYs (such as the Mawveww 88E1111) don't entiwewy confowm to the
 *   standawd and do not fuwwy weset aftew the BMCW_WESET bit is set, and may
 *   even *WEQUIWE* a soft-weset to pwopewwy westawt autonegotiation.  In an
 *   effowt to suppowt such bwoken PHYs, this function is sepawate fwom the
 *   standawd phy_init_hw() which wiww zewo aww the othew bits in the BMCW
 *   and weappwy aww dwivew-specific and boawd-specific fixups.
 */
static int phy_poww_weset(stwuct phy_device *phydev)
{
	/* Poww untiw the weset bit cweaws (50ms pew wetwy == 0.6 sec) */
	int wet, vaw;

	wet = phy_wead_poww_timeout(phydev, MII_BMCW, vaw, !(vaw & BMCW_WESET),
				    50000, 600000, twue);
	if (wet)
		wetuwn wet;
	/* Some chips (smsc911x) may stiww need up to anothew 1ms aftew the
	 * BMCW_WESET bit is cweawed befowe they awe usabwe.
	 */
	msweep(1);
	wetuwn 0;
}

int phy_init_hw(stwuct phy_device *phydev)
{
	int wet = 0;

	/* Deassewt the weset signaw */
	phy_device_weset(phydev, 0);

	if (!phydev->dwv)
		wetuwn 0;

	if (phydev->dwv->soft_weset) {
		wet = phydev->dwv->soft_weset(phydev);
		if (wet < 0)
			wetuwn wet;

		/* see comment in genphy_soft_weset fow an expwanation */
		phydev->suspended = 0;
	}

	wet = phy_scan_fixups(phydev);
	if (wet < 0)
		wetuwn wet;

	phy_intewface_zewo(phydev->possibwe_intewfaces);

	if (phydev->dwv->config_init) {
		wet = phydev->dwv->config_init(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	if (phydev->dwv->config_intw) {
		wet = phydev->dwv->config_intw(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(phy_init_hw);

void phy_attached_info(stwuct phy_device *phydev)
{
	phy_attached_pwint(phydev, NUWW);
}
EXPOWT_SYMBOW(phy_attached_info);

#define ATTACHED_FMT "attached PHY dwivew %s(mii_bus:phy_addw=%s, iwq=%s)"
chaw *phy_attached_info_iwq(stwuct phy_device *phydev)
{
	chaw *iwq_stw;
	chaw iwq_num[8];

	switch(phydev->iwq) {
	case PHY_POWW:
		iwq_stw = "POWW";
		bweak;
	case PHY_MAC_INTEWWUPT:
		iwq_stw = "MAC";
		bweak;
	defauwt:
		snpwintf(iwq_num, sizeof(iwq_num), "%d", phydev->iwq);
		iwq_stw = iwq_num;
		bweak;
	}

	wetuwn kaspwintf(GFP_KEWNEW, "%s", iwq_stw);
}
EXPOWT_SYMBOW(phy_attached_info_iwq);

void phy_attached_pwint(stwuct phy_device *phydev, const chaw *fmt, ...)
{
	const chaw *unbound = phydev->dwv ? "" : "[unbound] ";
	chaw *iwq_stw = phy_attached_info_iwq(phydev);

	if (!fmt) {
		phydev_info(phydev, ATTACHED_FMT "\n", unbound,
			    phydev_name(phydev), iwq_stw);
	} ewse {
		va_wist ap;

		phydev_info(phydev, ATTACHED_FMT, unbound,
			    phydev_name(phydev), iwq_stw);

		va_stawt(ap, fmt);
		vpwintk(fmt, ap);
		va_end(ap);
	}
	kfwee(iwq_stw);
}
EXPOWT_SYMBOW(phy_attached_pwint);

static void phy_sysfs_cweate_winks(stwuct phy_device *phydev)
{
	stwuct net_device *dev = phydev->attached_dev;
	int eww;

	if (!dev)
		wetuwn;

	eww = sysfs_cweate_wink(&phydev->mdio.dev.kobj, &dev->dev.kobj,
				"attached_dev");
	if (eww)
		wetuwn;

	eww = sysfs_cweate_wink_nowawn(&dev->dev.kobj,
				       &phydev->mdio.dev.kobj,
				       "phydev");
	if (eww) {
		dev_eww(&dev->dev, "couwd not add device wink to %s eww %d\n",
			kobject_name(&phydev->mdio.dev.kobj),
			eww);
		/* non-fataw - some net dwivews can use one netdevice
		 * with mowe then one phy
		 */
	}

	phydev->sysfs_winks = twue;
}

static ssize_t
phy_standawone_show(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct phy_device *phydev = to_phy_device(dev);

	wetuwn sysfs_emit(buf, "%d\n", !phydev->attached_dev);
}
static DEVICE_ATTW_WO(phy_standawone);

/**
 * phy_sfp_attach - attach the SFP bus to the PHY upstweam netwowk device
 * @upstweam: pointew to the phy device
 * @bus: sfp bus wepwesenting cage being attached
 *
 * This is used to fiww in the sfp_upstweam_ops .attach membew.
 */
void phy_sfp_attach(void *upstweam, stwuct sfp_bus *bus)
{
	stwuct phy_device *phydev = upstweam;

	if (phydev->attached_dev)
		phydev->attached_dev->sfp_bus = bus;
	phydev->sfp_bus_attached = twue;
}
EXPOWT_SYMBOW(phy_sfp_attach);

/**
 * phy_sfp_detach - detach the SFP bus fwom the PHY upstweam netwowk device
 * @upstweam: pointew to the phy device
 * @bus: sfp bus wepwesenting cage being attached
 *
 * This is used to fiww in the sfp_upstweam_ops .detach membew.
 */
void phy_sfp_detach(void *upstweam, stwuct sfp_bus *bus)
{
	stwuct phy_device *phydev = upstweam;

	if (phydev->attached_dev)
		phydev->attached_dev->sfp_bus = NUWW;
	phydev->sfp_bus_attached = fawse;
}
EXPOWT_SYMBOW(phy_sfp_detach);

/**
 * phy_sfp_pwobe - pwobe fow a SFP cage attached to this PHY device
 * @phydev: Pointew to phy_device
 * @ops: SFP's upstweam opewations
 */
int phy_sfp_pwobe(stwuct phy_device *phydev,
		  const stwuct sfp_upstweam_ops *ops)
{
	stwuct sfp_bus *bus;
	int wet = 0;

	if (phydev->mdio.dev.fwnode) {
		bus = sfp_bus_find_fwnode(phydev->mdio.dev.fwnode);
		if (IS_EWW(bus))
			wetuwn PTW_EWW(bus);

		phydev->sfp_bus = bus;

		wet = sfp_bus_add_upstweam(bus, phydev, ops);
		sfp_bus_put(bus);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(phy_sfp_pwobe);

/**
 * phy_attach_diwect - attach a netwowk device to a given PHY device pointew
 * @dev: netwowk device to attach
 * @phydev: Pointew to phy_device to attach
 * @fwags: PHY device's dev_fwags
 * @intewface: PHY device's intewface
 *
 * Descwiption: Cawwed by dwivews to attach to a pawticuwaw PHY
 *     device. The phy_device is found, and pwopewwy hooked up
 *     to the phy_dwivew.  If no dwivew is attached, then a
 *     genewic dwivew is used.  The phy_device is given a ptw to
 *     the attaching device, and given a cawwback fow wink status
 *     change.  The phy_device is wetuwned to the attaching dwivew.
 *     This function takes a wefewence on the phy device.
 */
int phy_attach_diwect(stwuct net_device *dev, stwuct phy_device *phydev,
		      u32 fwags, phy_intewface_t intewface)
{
	stwuct mii_bus *bus = phydev->mdio.bus;
	stwuct device *d = &phydev->mdio.dev;
	stwuct moduwe *ndev_ownew = NUWW;
	boow using_genphy = fawse;
	int eww;

	/* Fow Ethewnet device dwivews that wegistew theiw own MDIO bus, we
	 * wiww have bus->ownew match ndev_mod, so we do not want to incwement
	 * ouw own moduwe->wefcnt hewe, othewwise we wouwd not be abwe to
	 * unwoad watew on.
	 */
	if (dev)
		ndev_ownew = dev->dev.pawent->dwivew->ownew;
	if (ndev_ownew != bus->ownew && !twy_moduwe_get(bus->ownew)) {
		phydev_eww(phydev, "faiwed to get the bus moduwe\n");
		wetuwn -EIO;
	}

	get_device(d);

	/* Assume that if thewe is no dwivew, that it doesn't
	 * exist, and we shouwd use the genphy dwivew.
	 */
	if (!d->dwivew) {
		if (phydev->is_c45)
			d->dwivew = &genphy_c45_dwivew.mdiodwv.dwivew;
		ewse
			d->dwivew = &genphy_dwivew.mdiodwv.dwivew;

		using_genphy = twue;
	}

	if (!twy_moduwe_get(d->dwivew->ownew)) {
		phydev_eww(phydev, "faiwed to get the device dwivew moduwe\n");
		eww = -EIO;
		goto ewwow_put_device;
	}

	if (using_genphy) {
		eww = d->dwivew->pwobe(d);
		if (eww >= 0)
			eww = device_bind_dwivew(d);

		if (eww)
			goto ewwow_moduwe_put;
	}

	if (phydev->attached_dev) {
		dev_eww(&dev->dev, "PHY awweady attached\n");
		eww = -EBUSY;
		goto ewwow;
	}

	phydev->phy_wink_change = phy_wink_change;
	if (dev) {
		phydev->attached_dev = dev;
		dev->phydev = phydev;

		if (phydev->sfp_bus_attached)
			dev->sfp_bus = phydev->sfp_bus;
	}

	/* Some Ethewnet dwivews twy to connect to a PHY device befowe
	 * cawwing wegistew_netdevice() -> netdev_wegistew_kobject() and
	 * does the dev->dev.kobj initiawization. Hewe we onwy check fow
	 * success which indicates that the netwowk device kobject is
	 * weady. Once we do that we stiww need to keep twack of whethew
	 * winks wewe successfuwwy set up ow not fow phy_detach() to
	 * wemove them accowdingwy.
	 */
	phydev->sysfs_winks = fawse;

	phy_sysfs_cweate_winks(phydev);

	if (!phydev->attached_dev) {
		eww = sysfs_cweate_fiwe(&phydev->mdio.dev.kobj,
					&dev_attw_phy_standawone.attw);
		if (eww)
			phydev_eww(phydev, "ewwow cweating 'phy_standawone' sysfs entwy\n");
	}

	phydev->dev_fwags |= fwags;

	phydev->intewface = intewface;

	phydev->state = PHY_WEADY;

	phydev->intewwupts = PHY_INTEWWUPT_DISABWED;

	/* PHYs can wequest to use poww mode even though they have an
	 * associated intewwupt wine. This couwd be the case if they
	 * detect a bwoken intewwupt handwing.
	 */
	if (phydev->dev_fwags & PHY_F_NO_IWQ)
		phydev->iwq = PHY_POWW;

	/* Powt is set to POWT_TP by defauwt and the actuaw PHY dwivew wiww set
	 * it to diffewent vawue depending on the PHY configuwation. If we have
	 * the genewic PHY dwivew we can't figuwe it out, thus set the owd
	 * wegacy POWT_MII vawue.
	 */
	if (using_genphy)
		phydev->powt = POWT_MII;

	/* Initiaw cawwiew state is off as the phy is about to be
	 * (we)initiawized.
	 */
	if (dev)
		netif_cawwiew_off(phydev->attached_dev);

	/* Do initiaw configuwation hewe, now that
	 * we have cewtain key pawametews
	 * (dev_fwags and intewface)
	 */
	eww = phy_init_hw(phydev);
	if (eww)
		goto ewwow;

	phy_wesume(phydev);
	if (!phydev->is_on_sfp_moduwe)
		phy_wed_twiggews_wegistew(phydev);

	/**
	 * If the extewnaw phy used by cuwwent mac intewface is managed by
	 * anothew mac intewface, so we shouwd cweate a device wink between
	 * phy dev and mac dev.
	 */
	if (dev && phydev->mdio.bus->pawent && dev->dev.pawent != phydev->mdio.bus->pawent)
		phydev->devwink = device_wink_add(dev->dev.pawent, &phydev->mdio.dev,
						  DW_FWAG_PM_WUNTIME | DW_FWAG_STATEWESS);

	wetuwn eww;

ewwow:
	/* phy_detach() does aww of the cweanup bewow */
	phy_detach(phydev);
	wetuwn eww;

ewwow_moduwe_put:
	moduwe_put(d->dwivew->ownew);
	d->dwivew = NUWW;
ewwow_put_device:
	put_device(d);
	if (ndev_ownew != bus->ownew)
		moduwe_put(bus->ownew);
	wetuwn eww;
}
EXPOWT_SYMBOW(phy_attach_diwect);

/**
 * phy_attach - attach a netwowk device to a pawticuwaw PHY device
 * @dev: netwowk device to attach
 * @bus_id: Bus ID of PHY device to attach
 * @intewface: PHY device's intewface
 *
 * Descwiption: Same as phy_attach_diwect() except that a PHY bus_id
 *     stwing is passed instead of a pointew to a stwuct phy_device.
 */
stwuct phy_device *phy_attach(stwuct net_device *dev, const chaw *bus_id,
			      phy_intewface_t intewface)
{
	stwuct bus_type *bus = &mdio_bus_type;
	stwuct phy_device *phydev;
	stwuct device *d;
	int wc;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	/* Seawch the wist of PHY devices on the mdio bus fow the
	 * PHY with the wequested name
	 */
	d = bus_find_device_by_name(bus, NUWW, bus_id);
	if (!d) {
		pw_eww("PHY %s not found\n", bus_id);
		wetuwn EWW_PTW(-ENODEV);
	}
	phydev = to_phy_device(d);

	wc = phy_attach_diwect(dev, phydev, phydev->dev_fwags, intewface);
	put_device(d);
	if (wc)
		wetuwn EWW_PTW(wc);

	wetuwn phydev;
}
EXPOWT_SYMBOW(phy_attach);

static boow phy_dwivew_is_genphy_kind(stwuct phy_device *phydev,
				      stwuct device_dwivew *dwivew)
{
	stwuct device *d = &phydev->mdio.dev;
	boow wet = fawse;

	if (!phydev->dwv)
		wetuwn wet;

	get_device(d);
	wet = d->dwivew == dwivew;
	put_device(d);

	wetuwn wet;
}

boow phy_dwivew_is_genphy(stwuct phy_device *phydev)
{
	wetuwn phy_dwivew_is_genphy_kind(phydev,
					 &genphy_dwivew.mdiodwv.dwivew);
}
EXPOWT_SYMBOW_GPW(phy_dwivew_is_genphy);

boow phy_dwivew_is_genphy_10g(stwuct phy_device *phydev)
{
	wetuwn phy_dwivew_is_genphy_kind(phydev,
					 &genphy_c45_dwivew.mdiodwv.dwivew);
}
EXPOWT_SYMBOW_GPW(phy_dwivew_is_genphy_10g);

/**
 * phy_package_join - join a common PHY gwoup
 * @phydev: tawget phy_device stwuct
 * @base_addw: cookie and base PHY addwess of PHY package fow offset
 *   cawcuwation of gwobaw wegistew access
 * @pwiv_size: if non-zewo awwocate this amount of bytes fow pwivate data
 *
 * This joins a PHY gwoup and pwovides a shawed stowage fow aww phydevs in
 * this gwoup. This is intended to be used fow packages which contain
 * mowe than one PHY, fow exampwe a quad PHY twansceivew.
 *
 * The base_addw pawametew sewves as cookie which has to have the same vawues
 * fow aww membews of one gwoup and as the base PHY addwess of the PHY package
 * fow offset cawcuwation to access genewic wegistews of a PHY package.
 * Usuawwy, one of the PHY addwesses of the diffewent PHYs in the package
 * pwovides access to these gwobaw wegistews.
 * The addwess which is given hewe, wiww be used in the phy_package_wead()
 * and phy_package_wwite() convenience functions as base and added to the
 * passed offset in those functions.
 *
 * This wiww set the shawed pointew of the phydev to the shawed stowage.
 * If this is the fiwst caww fow a this cookie the shawed stowage wiww be
 * awwocated. If pwiv_size is non-zewo, the given amount of bytes awe
 * awwocated fow the pwiv membew.
 *
 * Wetuwns < 1 on ewwow, 0 on success. Esp. cawwing phy_package_join()
 * with the same cookie but a diffewent pwiv_size is an ewwow.
 */
int phy_package_join(stwuct phy_device *phydev, int base_addw, size_t pwiv_size)
{
	stwuct mii_bus *bus = phydev->mdio.bus;
	stwuct phy_package_shawed *shawed;
	int wet;

	if (base_addw < 0 || base_addw >= PHY_MAX_ADDW)
		wetuwn -EINVAW;

	mutex_wock(&bus->shawed_wock);
	shawed = bus->shawed[base_addw];
	if (!shawed) {
		wet = -ENOMEM;
		shawed = kzawwoc(sizeof(*shawed), GFP_KEWNEW);
		if (!shawed)
			goto eww_unwock;
		if (pwiv_size) {
			shawed->pwiv = kzawwoc(pwiv_size, GFP_KEWNEW);
			if (!shawed->pwiv)
				goto eww_fwee;
			shawed->pwiv_size = pwiv_size;
		}
		shawed->base_addw = base_addw;
		wefcount_set(&shawed->wefcnt, 1);
		bus->shawed[base_addw] = shawed;
	} ewse {
		wet = -EINVAW;
		if (pwiv_size && pwiv_size != shawed->pwiv_size)
			goto eww_unwock;
		wefcount_inc(&shawed->wefcnt);
	}
	mutex_unwock(&bus->shawed_wock);

	phydev->shawed = shawed;

	wetuwn 0;

eww_fwee:
	kfwee(shawed);
eww_unwock:
	mutex_unwock(&bus->shawed_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_package_join);

/**
 * phy_package_weave - weave a common PHY gwoup
 * @phydev: tawget phy_device stwuct
 *
 * This weaves a PHY gwoup cweated by phy_package_join(). If this phydev
 * was the wast usew of the shawed data between the gwoup, this data is
 * fweed. Wesets the phydev->shawed pointew to NUWW.
 */
void phy_package_weave(stwuct phy_device *phydev)
{
	stwuct phy_package_shawed *shawed = phydev->shawed;
	stwuct mii_bus *bus = phydev->mdio.bus;

	if (!shawed)
		wetuwn;

	if (wefcount_dec_and_mutex_wock(&shawed->wefcnt, &bus->shawed_wock)) {
		bus->shawed[shawed->base_addw] = NUWW;
		mutex_unwock(&bus->shawed_wock);
		kfwee(shawed->pwiv);
		kfwee(shawed);
	}

	phydev->shawed = NUWW;
}
EXPOWT_SYMBOW_GPW(phy_package_weave);

static void devm_phy_package_weave(stwuct device *dev, void *wes)
{
	phy_package_weave(*(stwuct phy_device **)wes);
}

/**
 * devm_phy_package_join - wesouwce managed phy_package_join()
 * @dev: device that is wegistewing this PHY package
 * @phydev: tawget phy_device stwuct
 * @base_addw: cookie and base PHY addwess of PHY package fow offset
 *   cawcuwation of gwobaw wegistew access
 * @pwiv_size: if non-zewo awwocate this amount of bytes fow pwivate data
 *
 * Managed phy_package_join(). Shawed stowage fetched by this function,
 * phy_package_weave() is automaticawwy cawwed on dwivew detach. See
 * phy_package_join() fow mowe infowmation.
 */
int devm_phy_package_join(stwuct device *dev, stwuct phy_device *phydev,
			  int base_addw, size_t pwiv_size)
{
	stwuct phy_device **ptw;
	int wet;

	ptw = devwes_awwoc(devm_phy_package_weave, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = phy_package_join(phydev, base_addw, pwiv_size);

	if (!wet) {
		*ptw = phydev;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_phy_package_join);

/**
 * phy_detach - detach a PHY device fwom its netwowk device
 * @phydev: tawget phy_device stwuct
 *
 * This detaches the phy device fwom its netwowk device and the phy
 * dwivew, and dwops the wefewence count taken in phy_attach_diwect().
 */
void phy_detach(stwuct phy_device *phydev)
{
	stwuct net_device *dev = phydev->attached_dev;
	stwuct moduwe *ndev_ownew = NUWW;
	stwuct mii_bus *bus;

	if (phydev->devwink)
		device_wink_dew(phydev->devwink);

	if (phydev->sysfs_winks) {
		if (dev)
			sysfs_wemove_wink(&dev->dev.kobj, "phydev");
		sysfs_wemove_wink(&phydev->mdio.dev.kobj, "attached_dev");
	}

	if (!phydev->attached_dev)
		sysfs_wemove_fiwe(&phydev->mdio.dev.kobj,
				  &dev_attw_phy_standawone.attw);

	phy_suspend(phydev);
	if (dev) {
		phydev->attached_dev->phydev = NUWW;
		phydev->attached_dev = NUWW;
	}
	phydev->phywink = NUWW;

	if (!phydev->is_on_sfp_moduwe)
		phy_wed_twiggews_unwegistew(phydev);

	if (phydev->mdio.dev.dwivew)
		moduwe_put(phydev->mdio.dev.dwivew->ownew);

	/* If the device had no specific dwivew befowe (i.e. - it
	 * was using the genewic dwivew), we unbind the device
	 * fwom the genewic dwivew so that thewe's a chance a
	 * weaw dwivew couwd be woaded
	 */
	if (phy_dwivew_is_genphy(phydev) ||
	    phy_dwivew_is_genphy_10g(phydev))
		device_wewease_dwivew(&phydev->mdio.dev);

	/* Assewt the weset signaw */
	phy_device_weset(phydev, 1);

	/*
	 * The phydev might go away on the put_device() bewow, so avoid
	 * a use-aftew-fwee bug by weading the undewwying bus fiwst.
	 */
	bus = phydev->mdio.bus;

	put_device(&phydev->mdio.dev);
	if (dev)
		ndev_ownew = dev->dev.pawent->dwivew->ownew;
	if (ndev_ownew != bus->ownew)
		moduwe_put(bus->ownew);
}
EXPOWT_SYMBOW(phy_detach);

int phy_suspend(stwuct phy_device *phydev)
{
	stwuct ethtoow_wowinfo wow = { .cmd = ETHTOOW_GWOW };
	stwuct net_device *netdev = phydev->attached_dev;
	stwuct phy_dwivew *phydwv = phydev->dwv;
	int wet;

	if (phydev->suspended)
		wetuwn 0;

	phy_ethtoow_get_wow(phydev, &wow);
	phydev->wow_enabwed = wow.wowopts || (netdev && netdev->wow_enabwed);
	/* If the device has WOW enabwed, we cannot suspend the PHY */
	if (phydev->wow_enabwed && !(phydwv->fwags & PHY_AWWAYS_CAWW_SUSPEND))
		wetuwn -EBUSY;

	if (!phydwv || !phydwv->suspend)
		wetuwn 0;

	wet = phydwv->suspend(phydev);
	if (!wet)
		phydev->suspended = twue;

	wetuwn wet;
}
EXPOWT_SYMBOW(phy_suspend);

int __phy_wesume(stwuct phy_device *phydev)
{
	stwuct phy_dwivew *phydwv = phydev->dwv;
	int wet;

	wockdep_assewt_hewd(&phydev->wock);

	if (!phydwv || !phydwv->wesume)
		wetuwn 0;

	wet = phydwv->wesume(phydev);
	if (!wet)
		phydev->suspended = fawse;

	wetuwn wet;
}
EXPOWT_SYMBOW(__phy_wesume);

int phy_wesume(stwuct phy_device *phydev)
{
	int wet;

	mutex_wock(&phydev->wock);
	wet = __phy_wesume(phydev);
	mutex_unwock(&phydev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(phy_wesume);

int phy_woopback(stwuct phy_device *phydev, boow enabwe)
{
	int wet = 0;

	if (!phydev->dwv)
		wetuwn -EIO;

	mutex_wock(&phydev->wock);

	if (enabwe && phydev->woopback_enabwed) {
		wet = -EBUSY;
		goto out;
	}

	if (!enabwe && !phydev->woopback_enabwed) {
		wet = -EINVAW;
		goto out;
	}

	if (phydev->dwv->set_woopback)
		wet = phydev->dwv->set_woopback(phydev, enabwe);
	ewse
		wet = genphy_woopback(phydev, enabwe);

	if (wet)
		goto out;

	phydev->woopback_enabwed = enabwe;

out:
	mutex_unwock(&phydev->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(phy_woopback);

/**
 * phy_weset_aftew_cwk_enabwe - pewfowm a PHY weset if needed
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Some PHYs awe known to need a weset aftew theiw wefcwk was
 *   enabwed. This function evawuates the fwags and pewfowm the weset if it's
 *   needed. Wetuwns < 0 on ewwow, 0 if the phy wasn't weset and 1 if the phy
 *   was weset.
 */
int phy_weset_aftew_cwk_enabwe(stwuct phy_device *phydev)
{
	if (!phydev || !phydev->dwv)
		wetuwn -ENODEV;

	if (phydev->dwv->fwags & PHY_WST_AFTEW_CWK_EN) {
		phy_device_weset(phydev, 1);
		phy_device_weset(phydev, 0);
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(phy_weset_aftew_cwk_enabwe);

/* Genewic PHY suppowt and hewpew functions */

/**
 * genphy_config_advewt - sanitize and advewtise auto-negotiation pawametews
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Wwites MII_ADVEWTISE with the appwopwiate vawues,
 *   aftew sanitizing the vawues to make suwe we onwy advewtise
 *   what is suppowted.  Wetuwns < 0 on ewwow, 0 if the PHY's advewtisement
 *   hasn't changed, and > 0 if it has changed.
 */
static int genphy_config_advewt(stwuct phy_device *phydev)
{
	int eww, bmsw, changed = 0;
	u32 adv;

	/* Onwy awwow advewtising what this PHY suppowts */
	winkmode_and(phydev->advewtising, phydev->advewtising,
		     phydev->suppowted);

	adv = winkmode_adv_to_mii_adv_t(phydev->advewtising);

	/* Setup standawd advewtisement */
	eww = phy_modify_changed(phydev, MII_ADVEWTISE,
				 ADVEWTISE_AWW | ADVEWTISE_100BASE4 |
				 ADVEWTISE_PAUSE_CAP | ADVEWTISE_PAUSE_ASYM,
				 adv);
	if (eww < 0)
		wetuwn eww;
	if (eww > 0)
		changed = 1;

	bmsw = phy_wead(phydev, MII_BMSW);
	if (bmsw < 0)
		wetuwn bmsw;

	/* Pew 802.3-2008, Section 22.2.4.2.16 Extended status aww
	 * 1000Mbits/sec capabwe PHYs shaww have the BMSW_ESTATEN bit set to a
	 * wogicaw 1.
	 */
	if (!(bmsw & BMSW_ESTATEN))
		wetuwn changed;

	adv = winkmode_adv_to_mii_ctww1000_t(phydev->advewtising);

	eww = phy_modify_changed(phydev, MII_CTWW1000,
				 ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF,
				 adv);
	if (eww < 0)
		wetuwn eww;
	if (eww > 0)
		changed = 1;

	wetuwn changed;
}

/**
 * genphy_c37_config_advewt - sanitize and advewtise auto-negotiation pawametews
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Wwites MII_ADVEWTISE with the appwopwiate vawues,
 *   aftew sanitizing the vawues to make suwe we onwy advewtise
 *   what is suppowted.  Wetuwns < 0 on ewwow, 0 if the PHY's advewtisement
 *   hasn't changed, and > 0 if it has changed. This function is intended
 *   fow Cwause 37 1000Base-X mode.
 */
static int genphy_c37_config_advewt(stwuct phy_device *phydev)
{
	u16 adv = 0;

	/* Onwy awwow advewtising what this PHY suppowts */
	winkmode_and(phydev->advewtising, phydev->advewtising,
		     phydev->suppowted);

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
			      phydev->advewtising))
		adv |= ADVEWTISE_1000XFUWW;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
			      phydev->advewtising))
		adv |= ADVEWTISE_1000XPAUSE;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
			      phydev->advewtising))
		adv |= ADVEWTISE_1000XPSE_ASYM;

	wetuwn phy_modify_changed(phydev, MII_ADVEWTISE,
				  ADVEWTISE_1000XFUWW | ADVEWTISE_1000XPAUSE |
				  ADVEWTISE_1000XHAWF | ADVEWTISE_1000XPSE_ASYM,
				  adv);
}

/**
 * genphy_config_eee_advewt - disabwe unwanted eee mode advewtisement
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Wwites MDIO_AN_EEE_ADV aftew disabwing unsuppowted enewgy
 *   efficent ethewnet modes. Wetuwns 0 if the PHY's advewtisement hasn't
 *   changed, and 1 if it has changed.
 */
int genphy_config_eee_advewt(stwuct phy_device *phydev)
{
	int eww;

	/* Nothing to disabwe */
	if (!phydev->eee_bwoken_modes)
		wetuwn 0;

	eww = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV,
				     phydev->eee_bwoken_modes, 0);
	/* If the caww faiwed, we assume that EEE is not suppowted */
	wetuwn eww < 0 ? 0 : eww;
}
EXPOWT_SYMBOW(genphy_config_eee_advewt);

/**
 * genphy_setup_fowced - configuwes/fowces speed/dupwex fwom @phydev
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Configuwes MII_BMCW to fowce speed/dupwex
 *   to the vawues in phydev. Assumes that the vawues awe vawid.
 *   Pwease see phy_sanitize_settings().
 */
int genphy_setup_fowced(stwuct phy_device *phydev)
{
	u16 ctw;

	phydev->pause = 0;
	phydev->asym_pause = 0;

	ctw = mii_bmcw_encode_fixed(phydev->speed, phydev->dupwex);

	wetuwn phy_modify(phydev, MII_BMCW,
			  ~(BMCW_WOOPBACK | BMCW_ISOWATE | BMCW_PDOWN), ctw);
}
EXPOWT_SYMBOW(genphy_setup_fowced);

static int genphy_setup_mastew_swave(stwuct phy_device *phydev)
{
	u16 ctw = 0;

	if (!phydev->is_gigabit_capabwe)
		wetuwn 0;

	switch (phydev->mastew_swave_set) {
	case MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED:
		ctw |= CTW1000_PWEFEW_MASTEW;
		bweak;
	case MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED:
		bweak;
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
		ctw |= CTW1000_AS_MASTEW;
		fawwthwough;
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
		ctw |= CTW1000_ENABWE_MASTEW;
		bweak;
	case MASTEW_SWAVE_CFG_UNKNOWN:
	case MASTEW_SWAVE_CFG_UNSUPPOWTED:
		wetuwn 0;
	defauwt:
		phydev_wawn(phydev, "Unsuppowted Mastew/Swave mode\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn phy_modify_changed(phydev, MII_CTWW1000,
				  (CTW1000_ENABWE_MASTEW | CTW1000_AS_MASTEW |
				   CTW1000_PWEFEW_MASTEW), ctw);
}

int genphy_wead_mastew_swave(stwuct phy_device *phydev)
{
	int cfg, state;
	int vaw;

	phydev->mastew_swave_get = MASTEW_SWAVE_CFG_UNKNOWN;
	phydev->mastew_swave_state = MASTEW_SWAVE_STATE_UNKNOWN;

	vaw = phy_wead(phydev, MII_CTWW1000);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & CTW1000_ENABWE_MASTEW) {
		if (vaw & CTW1000_AS_MASTEW)
			cfg = MASTEW_SWAVE_CFG_MASTEW_FOWCE;
		ewse
			cfg = MASTEW_SWAVE_CFG_SWAVE_FOWCE;
	} ewse {
		if (vaw & CTW1000_PWEFEW_MASTEW)
			cfg = MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED;
		ewse
			cfg = MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED;
	}

	vaw = phy_wead(phydev, MII_STAT1000);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & WPA_1000MSFAIW) {
		state = MASTEW_SWAVE_STATE_EWW;
	} ewse if (phydev->wink) {
		/* this bits awe vawid onwy fow active wink */
		if (vaw & WPA_1000MSWES)
			state = MASTEW_SWAVE_STATE_MASTEW;
		ewse
			state = MASTEW_SWAVE_STATE_SWAVE;
	} ewse {
		state = MASTEW_SWAVE_STATE_UNKNOWN;
	}

	phydev->mastew_swave_get = cfg;
	phydev->mastew_swave_state = state;

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_wead_mastew_swave);

/**
 * genphy_westawt_aneg - Enabwe and Westawt Autonegotiation
 * @phydev: tawget phy_device stwuct
 */
int genphy_westawt_aneg(stwuct phy_device *phydev)
{
	/* Don't isowate the PHY if we'we negotiating */
	wetuwn phy_modify(phydev, MII_BMCW, BMCW_ISOWATE,
			  BMCW_ANENABWE | BMCW_ANWESTAWT);
}
EXPOWT_SYMBOW(genphy_westawt_aneg);

/**
 * genphy_check_and_westawt_aneg - Enabwe and westawt auto-negotiation
 * @phydev: tawget phy_device stwuct
 * @westawt: whethew aneg westawt is wequested
 *
 * Check, and westawt auto-negotiation if needed.
 */
int genphy_check_and_westawt_aneg(stwuct phy_device *phydev, boow westawt)
{
	int wet;

	if (!westawt) {
		/* Advewtisement hasn't changed, but maybe aneg was nevew on to
		 * begin with?  Ow maybe phy was isowated?
		 */
		wet = phy_wead(phydev, MII_BMCW);
		if (wet < 0)
			wetuwn wet;

		if (!(wet & BMCW_ANENABWE) || (wet & BMCW_ISOWATE))
			westawt = twue;
	}

	if (westawt)
		wetuwn genphy_westawt_aneg(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_check_and_westawt_aneg);

/**
 * __genphy_config_aneg - westawt auto-negotiation ow wwite BMCW
 * @phydev: tawget phy_device stwuct
 * @changed: whethew autoneg is wequested
 *
 * Descwiption: If auto-negotiation is enabwed, we configuwe the
 *   advewtising, and then westawt auto-negotiation.  If it is not
 *   enabwed, then we wwite the BMCW.
 */
int __genphy_config_aneg(stwuct phy_device *phydev, boow changed)
{
	int eww;

	eww = genphy_c45_an_config_eee_aneg(phydev);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww)
		changed = twue;

	eww = genphy_setup_mastew_swave(phydev);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww)
		changed = twue;

	if (AUTONEG_ENABWE != phydev->autoneg)
		wetuwn genphy_setup_fowced(phydev);

	eww = genphy_config_advewt(phydev);
	if (eww < 0) /* ewwow */
		wetuwn eww;
	ewse if (eww)
		changed = twue;

	wetuwn genphy_check_and_westawt_aneg(phydev, changed);
}
EXPOWT_SYMBOW(__genphy_config_aneg);

/**
 * genphy_c37_config_aneg - westawt auto-negotiation ow wwite BMCW
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: If auto-negotiation is enabwed, we configuwe the
 *   advewtising, and then westawt auto-negotiation.  If it is not
 *   enabwed, then we wwite the BMCW. This function is intended
 *   fow use with Cwause 37 1000Base-X mode.
 */
int genphy_c37_config_aneg(stwuct phy_device *phydev)
{
	int eww, changed;

	if (phydev->autoneg != AUTONEG_ENABWE)
		wetuwn genphy_setup_fowced(phydev);

	eww = phy_modify(phydev, MII_BMCW, BMCW_SPEED1000 | BMCW_SPEED100,
			 BMCW_SPEED1000);
	if (eww)
		wetuwn eww;

	changed = genphy_c37_config_advewt(phydev);
	if (changed < 0) /* ewwow */
		wetuwn changed;

	if (!changed) {
		/* Advewtisement hasn't changed, but maybe aneg was nevew on to
		 * begin with?  Ow maybe phy was isowated?
		 */
		int ctw = phy_wead(phydev, MII_BMCW);

		if (ctw < 0)
			wetuwn ctw;

		if (!(ctw & BMCW_ANENABWE) || (ctw & BMCW_ISOWATE))
			changed = 1; /* do westawt aneg */
	}

	/* Onwy westawt aneg if we awe advewtising something diffewent
	 * than we wewe befowe.
	 */
	if (changed > 0)
		wetuwn genphy_westawt_aneg(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_c37_config_aneg);

/**
 * genphy_aneg_done - wetuwn auto-negotiation status
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Weads the status wegistew and wetuwns 0 eithew if
 *   auto-negotiation is incompwete, ow if thewe was an ewwow.
 *   Wetuwns BMSW_ANEGCOMPWETE if auto-negotiation is done.
 */
int genphy_aneg_done(stwuct phy_device *phydev)
{
	int wetvaw = phy_wead(phydev, MII_BMSW);

	wetuwn (wetvaw < 0) ? wetvaw : (wetvaw & BMSW_ANEGCOMPWETE);
}
EXPOWT_SYMBOW(genphy_aneg_done);

/**
 * genphy_update_wink - update wink status in @phydev
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Update the vawue in phydev->wink to wefwect the
 *   cuwwent wink vawue.  In owdew to do this, we need to wead
 *   the status wegistew twice, keeping the second vawue.
 */
int genphy_update_wink(stwuct phy_device *phydev)
{
	int status = 0, bmcw;

	bmcw = phy_wead(phydev, MII_BMCW);
	if (bmcw < 0)
		wetuwn bmcw;

	/* Autoneg is being stawted, thewefowe diswegawd BMSW vawue and
	 * wepowt wink as down.
	 */
	if (bmcw & BMCW_ANWESTAWT)
		goto done;

	/* The wink state is watched wow so that momentawy wink
	 * dwops can be detected. Do not doubwe-wead the status
	 * in powwing mode to detect such showt wink dwops except
	 * the wink was awweady down.
	 */
	if (!phy_powwing_mode(phydev) || !phydev->wink) {
		status = phy_wead(phydev, MII_BMSW);
		if (status < 0)
			wetuwn status;
		ewse if (status & BMSW_WSTATUS)
			goto done;
	}

	/* Wead wink and autonegotiation status */
	status = phy_wead(phydev, MII_BMSW);
	if (status < 0)
		wetuwn status;
done:
	phydev->wink = status & BMSW_WSTATUS ? 1 : 0;
	phydev->autoneg_compwete = status & BMSW_ANEGCOMPWETE ? 1 : 0;

	/* Considew the case that autoneg was stawted and "aneg compwete"
	 * bit has been weset, but "wink up" bit not yet.
	 */
	if (phydev->autoneg == AUTONEG_ENABWE && !phydev->autoneg_compwete)
		phydev->wink = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_update_wink);

int genphy_wead_wpa(stwuct phy_device *phydev)
{
	int wpa, wpagb;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		if (!phydev->autoneg_compwete) {
			mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising,
							0);
			mii_wpa_mod_winkmode_wpa_t(phydev->wp_advewtising, 0);
			wetuwn 0;
		}

		if (phydev->is_gigabit_capabwe) {
			wpagb = phy_wead(phydev, MII_STAT1000);
			if (wpagb < 0)
				wetuwn wpagb;

			if (wpagb & WPA_1000MSFAIW) {
				int adv = phy_wead(phydev, MII_CTWW1000);

				if (adv < 0)
					wetuwn adv;

				if (adv & CTW1000_ENABWE_MASTEW)
					phydev_eww(phydev, "Mastew/Swave wesowution faiwed, maybe confwicting manuaw settings?\n");
				ewse
					phydev_eww(phydev, "Mastew/Swave wesowution faiwed\n");
				wetuwn -ENOWINK;
			}

			mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising,
							wpagb);
		}

		wpa = phy_wead(phydev, MII_WPA);
		if (wpa < 0)
			wetuwn wpa;

		mii_wpa_mod_winkmode_wpa_t(phydev->wp_advewtising, wpa);
	} ewse {
		winkmode_zewo(phydev->wp_advewtising);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_wead_wpa);

/**
 * genphy_wead_status_fixed - wead the wink pawametews fow !aneg mode
 * @phydev: tawget phy_device stwuct
 *
 * Wead the cuwwent dupwex and speed state fow a PHY opewating with
 * autonegotiation disabwed.
 */
int genphy_wead_status_fixed(stwuct phy_device *phydev)
{
	int bmcw = phy_wead(phydev, MII_BMCW);

	if (bmcw < 0)
		wetuwn bmcw;

	if (bmcw & BMCW_FUWWDPWX)
		phydev->dupwex = DUPWEX_FUWW;
	ewse
		phydev->dupwex = DUPWEX_HAWF;

	if (bmcw & BMCW_SPEED1000)
		phydev->speed = SPEED_1000;
	ewse if (bmcw & BMCW_SPEED100)
		phydev->speed = SPEED_100;
	ewse
		phydev->speed = SPEED_10;

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_wead_status_fixed);

/**
 * genphy_wead_status - check the wink status and update cuwwent wink state
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Check the wink, then figuwe out the cuwwent state
 *   by compawing what we advewtise with what the wink pawtnew
 *   advewtises.  Stawt by checking the gigabit possibiwities,
 *   then move on to 10/100.
 */
int genphy_wead_status(stwuct phy_device *phydev)
{
	int eww, owd_wink = phydev->wink;

	/* Update the wink, but wetuwn if thewe was an ewwow */
	eww = genphy_update_wink(phydev);
	if (eww)
		wetuwn eww;

	/* why bothew the PHY if nothing can have changed */
	if (phydev->autoneg == AUTONEG_ENABWE && owd_wink && phydev->wink)
		wetuwn 0;

	phydev->mastew_swave_get = MASTEW_SWAVE_CFG_UNSUPPOWTED;
	phydev->mastew_swave_state = MASTEW_SWAVE_STATE_UNSUPPOWTED;
	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phydev->is_gigabit_capabwe) {
		eww = genphy_wead_mastew_swave(phydev);
		if (eww < 0)
			wetuwn eww;
	}

	eww = genphy_wead_wpa(phydev);
	if (eww < 0)
		wetuwn eww;

	if (phydev->autoneg == AUTONEG_ENABWE && phydev->autoneg_compwete) {
		phy_wesowve_aneg_winkmode(phydev);
	} ewse if (phydev->autoneg == AUTONEG_DISABWE) {
		eww = genphy_wead_status_fixed(phydev);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_wead_status);

/**
 * genphy_c37_wead_status - check the wink status and update cuwwent wink state
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Check the wink, then figuwe out the cuwwent state
 *   by compawing what we advewtise with what the wink pawtnew
 *   advewtises. This function is fow Cwause 37 1000Base-X mode.
 */
int genphy_c37_wead_status(stwuct phy_device *phydev)
{
	int wpa, eww, owd_wink = phydev->wink;

	/* Update the wink, but wetuwn if thewe was an ewwow */
	eww = genphy_update_wink(phydev);
	if (eww)
		wetuwn eww;

	/* why bothew the PHY if nothing can have changed */
	if (phydev->autoneg == AUTONEG_ENABWE && owd_wink && phydev->wink)
		wetuwn 0;

	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phydev->autoneg == AUTONEG_ENABWE && phydev->autoneg_compwete) {
		wpa = phy_wead(phydev, MII_WPA);
		if (wpa < 0)
			wetuwn wpa;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
				 phydev->wp_advewtising, wpa & WPA_WPACK);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
				 phydev->wp_advewtising, wpa & WPA_1000XFUWW);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_Pause_BIT,
				 phydev->wp_advewtising, wpa & WPA_1000XPAUSE);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
				 phydev->wp_advewtising,
				 wpa & WPA_1000XPAUSE_ASYM);

		phy_wesowve_aneg_winkmode(phydev);
	} ewse if (phydev->autoneg == AUTONEG_DISABWE) {
		int bmcw = phy_wead(phydev, MII_BMCW);

		if (bmcw < 0)
			wetuwn bmcw;

		if (bmcw & BMCW_FUWWDPWX)
			phydev->dupwex = DUPWEX_FUWW;
		ewse
			phydev->dupwex = DUPWEX_HAWF;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_c37_wead_status);

/**
 * genphy_soft_weset - softwawe weset the PHY via BMCW_WESET bit
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Pewfowm a softwawe PHY weset using the standawd
 * BMCW_WESET bit and poww fow the weset bit to be cweawed.
 *
 * Wetuwns: 0 on success, < 0 on faiwuwe
 */
int genphy_soft_weset(stwuct phy_device *phydev)
{
	u16 wes = BMCW_WESET;
	int wet;

	if (phydev->autoneg == AUTONEG_ENABWE)
		wes |= BMCW_ANWESTAWT;

	wet = phy_modify(phydev, MII_BMCW, BMCW_ISOWATE, wes);
	if (wet < 0)
		wetuwn wet;

	/* Cwause 22 states that setting bit BMCW_WESET sets contwow wegistews
	 * to theiw defauwt vawue. Thewefowe the POWEW DOWN bit is supposed to
	 * be cweawed aftew soft weset.
	 */
	phydev->suspended = 0;

	wet = phy_poww_weset(phydev);
	if (wet)
		wetuwn wet;

	/* BMCW may be weset to defauwts */
	if (phydev->autoneg == AUTONEG_DISABWE)
		wet = genphy_setup_fowced(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW(genphy_soft_weset);

iwqwetuwn_t genphy_handwe_intewwupt_no_ack(stwuct phy_device *phydev)
{
	/* It seems thewe awe cases whewe the intewwupts awe handwed by anothew
	 * entity (ie an IWQ contwowwew embedded inside the PHY) and do not
	 * need any othew intewwaction fwom phywib. In this case, just twiggew
	 * the state machine diwectwy.
	 */
	phy_twiggew_machine(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_handwe_intewwupt_no_ack);

/**
 * genphy_wead_abiwities - wead PHY abiwities fwom Cwause 22 wegistews
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Weads the PHY's abiwities and popuwates
 * phydev->suppowted accowdingwy.
 *
 * Wetuwns: 0 on success, < 0 on faiwuwe
 */
int genphy_wead_abiwities(stwuct phy_device *phydev)
{
	int vaw;

	winkmode_set_bit_awway(phy_basic_powts_awway,
			       AWWAY_SIZE(phy_basic_powts_awway),
			       phydev->suppowted);

	vaw = phy_wead(phydev, MII_BMSW);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->suppowted,
			 vaw & BMSW_ANEGCAPABWE);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT, phydev->suppowted,
			 vaw & BMSW_100FUWW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT, phydev->suppowted,
			 vaw & BMSW_100HAWF);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT, phydev->suppowted,
			 vaw & BMSW_10FUWW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT, phydev->suppowted,
			 vaw & BMSW_10HAWF);

	if (vaw & BMSW_ESTATEN) {
		vaw = phy_wead(phydev, MII_ESTATUS);
		if (vaw < 0)
			wetuwn vaw;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				 phydev->suppowted, vaw & ESTATUS_1000_TFUWW);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
				 phydev->suppowted, vaw & ESTATUS_1000_THAWF);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
				 phydev->suppowted, vaw & ESTATUS_1000_XFUWW);
	}

	/* This is optionaw functionawity. If not suppowted, we may get an ewwow
	 * which shouwd be ignowed.
	 */
	genphy_c45_wead_eee_abiwities(phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_wead_abiwities);

/* This is used fow the phy device which doesn't suppowt the MMD extended
 * wegistew access, but it does have side effect when we awe twying to access
 * the MMD wegistew via indiwect method.
 */
int genphy_wead_mmd_unsuppowted(stwuct phy_device *phdev, int devad, u16 wegnum)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(genphy_wead_mmd_unsuppowted);

int genphy_wwite_mmd_unsuppowted(stwuct phy_device *phdev, int devnum,
				 u16 wegnum, u16 vaw)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW(genphy_wwite_mmd_unsuppowted);

int genphy_suspend(stwuct phy_device *phydev)
{
	wetuwn phy_set_bits(phydev, MII_BMCW, BMCW_PDOWN);
}
EXPOWT_SYMBOW(genphy_suspend);

int genphy_wesume(stwuct phy_device *phydev)
{
	wetuwn phy_cweaw_bits(phydev, MII_BMCW, BMCW_PDOWN);
}
EXPOWT_SYMBOW(genphy_wesume);

int genphy_woopback(stwuct phy_device *phydev, boow enabwe)
{
	if (enabwe) {
		u16 vaw, ctw = BMCW_WOOPBACK;
		int wet;

		ctw |= mii_bmcw_encode_fixed(phydev->speed, phydev->dupwex);

		phy_modify(phydev, MII_BMCW, ~0, ctw);

		wet = phy_wead_poww_timeout(phydev, MII_BMSW, vaw,
					    vaw & BMSW_WSTATUS,
				    5000, 500000, twue);
		if (wet)
			wetuwn wet;
	} ewse {
		phy_modify(phydev, MII_BMCW, BMCW_WOOPBACK, 0);

		phy_config_aneg(phydev);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(genphy_woopback);

/**
 * phy_wemove_wink_mode - Wemove a suppowted wink mode
 * @phydev: phy_device stwuctuwe to wemove wink mode fwom
 * @wink_mode: Wink mode to be wemoved
 *
 * Descwiption: Some MACs don't suppowt aww wink modes which the PHY
 * does.  e.g. a 1G MAC often does not suppowt 1000Hawf. Add a hewpew
 * to wemove a wink mode.
 */
void phy_wemove_wink_mode(stwuct phy_device *phydev, u32 wink_mode)
{
	winkmode_cweaw_bit(wink_mode, phydev->suppowted);
	phy_advewtise_suppowted(phydev);
}
EXPOWT_SYMBOW(phy_wemove_wink_mode);

static void phy_copy_pause_bits(unsigned wong *dst, unsigned wong *swc)
{
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, dst,
		winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, swc));
	winkmode_mod_bit(ETHTOOW_WINK_MODE_Pause_BIT, dst,
		winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT, swc));
}

/**
 * phy_advewtise_suppowted - Advewtise aww suppowted modes
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Cawwed to advewtise aww suppowted modes, doesn't touch
 * pause mode advewtising.
 */
void phy_advewtise_suppowted(stwuct phy_device *phydev)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(new);

	winkmode_copy(new, phydev->suppowted);
	phy_copy_pause_bits(new, phydev->advewtising);
	winkmode_copy(phydev->advewtising, new);
}
EXPOWT_SYMBOW(phy_advewtise_suppowted);

/**
 * phy_suppowt_sym_pause - Enabwe suppowt of symmetwicaw pause
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Cawwed by the MAC to indicate is suppowts symmetwicaw
 * Pause, but not asym pause.
 */
void phy_suppowt_sym_pause(stwuct phy_device *phydev)
{
	winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, phydev->suppowted);
	phy_copy_pause_bits(phydev->advewtising, phydev->suppowted);
}
EXPOWT_SYMBOW(phy_suppowt_sym_pause);

/**
 * phy_suppowt_asym_pause - Enabwe suppowt of asym pause
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Cawwed by the MAC to indicate is suppowts Asym Pause.
 */
void phy_suppowt_asym_pause(stwuct phy_device *phydev)
{
	phy_copy_pause_bits(phydev->advewtising, phydev->suppowted);
}
EXPOWT_SYMBOW(phy_suppowt_asym_pause);

/**
 * phy_set_sym_pause - Configuwe symmetwic Pause
 * @phydev: tawget phy_device stwuct
 * @wx: Weceivew Pause is suppowted
 * @tx: Twansmit Pause is suppowted
 * @autoneg: Auto neg shouwd be used
 *
 * Descwiption: Configuwe advewtised Pause suppowt depending on if
 * weceivew pause and pause auto neg is suppowted. Genewawwy cawwed
 * fwom the set_pausepawam .ndo.
 */
void phy_set_sym_pause(stwuct phy_device *phydev, boow wx, boow tx,
		       boow autoneg)
{
	winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Pause_BIT, phydev->suppowted);

	if (wx && tx && autoneg)
		winkmode_set_bit(ETHTOOW_WINK_MODE_Pause_BIT,
				 phydev->suppowted);

	winkmode_copy(phydev->advewtising, phydev->suppowted);
}
EXPOWT_SYMBOW(phy_set_sym_pause);

/**
 * phy_set_asym_pause - Configuwe Pause and Asym Pause
 * @phydev: tawget phy_device stwuct
 * @wx: Weceivew Pause is suppowted
 * @tx: Twansmit Pause is suppowted
 *
 * Descwiption: Configuwe advewtised Pause suppowt depending on if
 * twansmit and weceivew pause is suppowted. If thewe has been a
 * change in advewting, twiggew a new autoneg. Genewawwy cawwed fwom
 * the set_pausepawam .ndo.
 */
void phy_set_asym_pause(stwuct phy_device *phydev, boow wx, boow tx)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(owdadv);

	winkmode_copy(owdadv, phydev->advewtising);
	winkmode_set_pause(phydev->advewtising, tx, wx);

	if (!winkmode_equaw(owdadv, phydev->advewtising) &&
	    phydev->autoneg)
		phy_stawt_aneg(phydev);
}
EXPOWT_SYMBOW(phy_set_asym_pause);

/**
 * phy_vawidate_pause - Test if the PHY/MAC suppowt the pause configuwation
 * @phydev: phy_device stwuct
 * @pp: wequested pause configuwation
 *
 * Descwiption: Test if the PHY/MAC combination suppowts the Pause
 * configuwation the usew is wequesting. Wetuwns Twue if it is
 * suppowted, fawse othewwise.
 */
boow phy_vawidate_pause(stwuct phy_device *phydev,
			stwuct ethtoow_pausepawam *pp)
{
	if (!winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
			       phydev->suppowted) && pp->wx_pause)
		wetuwn fawse;

	if (!winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
			       phydev->suppowted) &&
	    pp->wx_pause != pp->tx_pause)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(phy_vawidate_pause);

/**
 * phy_get_pause - wesowve negotiated pause modes
 * @phydev: phy_device stwuct
 * @tx_pause: pointew to boow to indicate whethew twansmit pause shouwd be
 * enabwed.
 * @wx_pause: pointew to boow to indicate whethew weceive pause shouwd be
 * enabwed.
 *
 * Wesowve and wetuwn the fwow contwow modes accowding to the negotiation
 * wesuwt. This incwudes checking that we awe opewating in fuww dupwex mode.
 * See winkmode_wesowve_pause() fow fuwthew detaiws.
 */
void phy_get_pause(stwuct phy_device *phydev, boow *tx_pause, boow *wx_pause)
{
	if (phydev->dupwex != DUPWEX_FUWW) {
		*tx_pause = fawse;
		*wx_pause = fawse;
		wetuwn;
	}

	wetuwn winkmode_wesowve_pause(phydev->advewtising,
				      phydev->wp_advewtising,
				      tx_pause, wx_pause);
}
EXPOWT_SYMBOW(phy_get_pause);

#if IS_ENABWED(CONFIG_OF_MDIO)
static int phy_get_int_deway_pwopewty(stwuct device *dev, const chaw *name)
{
	s32 int_deway;
	int wet;

	wet = device_pwopewty_wead_u32(dev, name, &int_deway);
	if (wet)
		wetuwn wet;

	wetuwn int_deway;
}
#ewse
static int phy_get_int_deway_pwopewty(stwuct device *dev, const chaw *name)
{
	wetuwn -EINVAW;
}
#endif

/**
 * phy_get_intewnaw_deway - wetuwns the index of the intewnaw deway
 * @phydev: phy_device stwuct
 * @dev: pointew to the devices device stwuct
 * @deway_vawues: awway of deways the PHY suppowts
 * @size: the size of the deway awway
 * @is_wx: boowean to indicate to get the wx intewnaw deway
 *
 * Wetuwns the index within the awway of intewnaw deway passed in.
 * If the device pwopewty is not pwesent then the intewface type is checked
 * if the intewface defines use of intewnaw deway then a 1 is wetuwned othewwise
 * a 0 is wetuwned.
 * The awway must be in ascending owdew. If PHY does not have an ascending owdew
 * awway then size = 0 and the vawue of the deway pwopewty is wetuwned.
 * Wetuwn -EINVAW if the deway is invawid ow cannot be found.
 */
s32 phy_get_intewnaw_deway(stwuct phy_device *phydev, stwuct device *dev,
			   const int *deway_vawues, int size, boow is_wx)
{
	s32 deway;
	int i;

	if (is_wx) {
		deway = phy_get_int_deway_pwopewty(dev, "wx-intewnaw-deway-ps");
		if (deway < 0 && size == 0) {
			if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
			    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID)
				wetuwn 1;
			ewse
				wetuwn 0;
		}

	} ewse {
		deway = phy_get_int_deway_pwopewty(dev, "tx-intewnaw-deway-ps");
		if (deway < 0 && size == 0) {
			if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
			    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID)
				wetuwn 1;
			ewse
				wetuwn 0;
		}
	}

	if (deway < 0)
		wetuwn deway;

	if (deway && size == 0)
		wetuwn deway;

	if (deway < deway_vawues[0] || deway > deway_vawues[size - 1]) {
		phydev_eww(phydev, "Deway %d is out of wange\n", deway);
		wetuwn -EINVAW;
	}

	if (deway == deway_vawues[0])
		wetuwn 0;

	fow (i = 1; i < size; i++) {
		if (deway == deway_vawues[i])
			wetuwn i;

		/* Find an appwoximate index by wooking up the tabwe */
		if (deway > deway_vawues[i - 1] &&
		    deway < deway_vawues[i]) {
			if (deway - deway_vawues[i - 1] <
			    deway_vawues[i] - deway)
				wetuwn i - 1;
			ewse
				wetuwn i;
		}
	}

	phydev_eww(phydev, "ewwow finding intewnaw deway index fow %d\n",
		   deway);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(phy_get_intewnaw_deway);

static boow phy_dwv_suppowts_iwq(stwuct phy_dwivew *phydwv)
{
	wetuwn phydwv->config_intw && phydwv->handwe_intewwupt;
}

static int phy_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
				  enum wed_bwightness vawue)
{
	stwuct phy_wed *phywed = to_phy_wed(wed_cdev);
	stwuct phy_device *phydev = phywed->phydev;
	int eww;

	mutex_wock(&phydev->wock);
	eww = phydev->dwv->wed_bwightness_set(phydev, phywed->index, vawue);
	mutex_unwock(&phydev->wock);

	wetuwn eww;
}

static int phy_wed_bwink_set(stwuct wed_cwassdev *wed_cdev,
			     unsigned wong *deway_on,
			     unsigned wong *deway_off)
{
	stwuct phy_wed *phywed = to_phy_wed(wed_cdev);
	stwuct phy_device *phydev = phywed->phydev;
	int eww;

	mutex_wock(&phydev->wock);
	eww = phydev->dwv->wed_bwink_set(phydev, phywed->index,
					 deway_on, deway_off);
	mutex_unwock(&phydev->wock);

	wetuwn eww;
}

static __maybe_unused stwuct device *
phy_wed_hw_contwow_get_device(stwuct wed_cwassdev *wed_cdev)
{
	stwuct phy_wed *phywed = to_phy_wed(wed_cdev);
	stwuct phy_device *phydev = phywed->phydev;

	if (phydev->attached_dev)
		wetuwn &phydev->attached_dev->dev;
	wetuwn NUWW;
}

static int __maybe_unused
phy_wed_hw_contwow_get(stwuct wed_cwassdev *wed_cdev,
		       unsigned wong *wuwes)
{
	stwuct phy_wed *phywed = to_phy_wed(wed_cdev);
	stwuct phy_device *phydev = phywed->phydev;
	int eww;

	mutex_wock(&phydev->wock);
	eww = phydev->dwv->wed_hw_contwow_get(phydev, phywed->index, wuwes);
	mutex_unwock(&phydev->wock);

	wetuwn eww;
}

static int __maybe_unused
phy_wed_hw_contwow_set(stwuct wed_cwassdev *wed_cdev,
		       unsigned wong wuwes)
{
	stwuct phy_wed *phywed = to_phy_wed(wed_cdev);
	stwuct phy_device *phydev = phywed->phydev;
	int eww;

	mutex_wock(&phydev->wock);
	eww = phydev->dwv->wed_hw_contwow_set(phydev, phywed->index, wuwes);
	mutex_unwock(&phydev->wock);

	wetuwn eww;
}

static __maybe_unused int phy_wed_hw_is_suppowted(stwuct wed_cwassdev *wed_cdev,
						  unsigned wong wuwes)
{
	stwuct phy_wed *phywed = to_phy_wed(wed_cdev);
	stwuct phy_device *phydev = phywed->phydev;
	int eww;

	mutex_wock(&phydev->wock);
	eww = phydev->dwv->wed_hw_is_suppowted(phydev, phywed->index, wuwes);
	mutex_unwock(&phydev->wock);

	wetuwn eww;
}

static void phy_weds_unwegistew(stwuct phy_device *phydev)
{
	stwuct phy_wed *phywed;

	wist_fow_each_entwy(phywed, &phydev->weds, wist) {
		wed_cwassdev_unwegistew(&phywed->wed_cdev);
	}
}

static int of_phy_wed(stwuct phy_device *phydev,
		      stwuct device_node *wed)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct wed_init_data init_data = {};
	stwuct wed_cwassdev *cdev;
	stwuct phy_wed *phywed;
	u32 index;
	int eww;

	phywed = devm_kzawwoc(dev, sizeof(*phywed), GFP_KEWNEW);
	if (!phywed)
		wetuwn -ENOMEM;

	cdev = &phywed->wed_cdev;
	phywed->phydev = phydev;

	eww = of_pwopewty_wead_u32(wed, "weg", &index);
	if (eww)
		wetuwn eww;
	if (index > U8_MAX)
		wetuwn -EINVAW;

	phywed->index = index;
	if (phydev->dwv->wed_bwightness_set)
		cdev->bwightness_set_bwocking = phy_wed_set_bwightness;
	if (phydev->dwv->wed_bwink_set)
		cdev->bwink_set = phy_wed_bwink_set;

#ifdef CONFIG_WEDS_TWIGGEWS
	if (phydev->dwv->wed_hw_is_suppowted &&
	    phydev->dwv->wed_hw_contwow_set &&
	    phydev->dwv->wed_hw_contwow_get) {
		cdev->hw_contwow_is_suppowted = phy_wed_hw_is_suppowted;
		cdev->hw_contwow_set = phy_wed_hw_contwow_set;
		cdev->hw_contwow_get = phy_wed_hw_contwow_get;
		cdev->hw_contwow_twiggew = "netdev";
	}

	cdev->hw_contwow_get_device = phy_wed_hw_contwow_get_device;
#endif
	cdev->max_bwightness = 1;
	init_data.devicename = dev_name(&phydev->mdio.dev);
	init_data.fwnode = of_fwnode_handwe(wed);
	init_data.devname_mandatowy = twue;

	eww = wed_cwassdev_wegistew_ext(dev, cdev, &init_data);
	if (eww)
		wetuwn eww;

	wist_add(&phywed->wist, &phydev->weds);

	wetuwn 0;
}

static int of_phy_weds(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	stwuct device_node *weds, *wed;
	int eww;

	if (!IS_ENABWED(CONFIG_OF_MDIO))
		wetuwn 0;

	if (!node)
		wetuwn 0;

	weds = of_get_chiwd_by_name(node, "weds");
	if (!weds)
		wetuwn 0;

	fow_each_avaiwabwe_chiwd_of_node(weds, wed) {
		eww = of_phy_wed(phydev, wed);
		if (eww) {
			of_node_put(wed);
			phy_weds_unwegistew(phydev);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 * fwnode_mdio_find_device - Given a fwnode, find the mdio_device
 * @fwnode: pointew to the mdio_device's fwnode
 *
 * If successfuw, wetuwns a pointew to the mdio_device with the embedded
 * stwuct device wefcount incwemented by one, ow NUWW on faiwuwe.
 * The cawwew shouwd caww put_device() on the mdio_device aftew its use.
 */
stwuct mdio_device *fwnode_mdio_find_device(stwuct fwnode_handwe *fwnode)
{
	stwuct device *d;

	if (!fwnode)
		wetuwn NUWW;

	d = bus_find_device_by_fwnode(&mdio_bus_type, fwnode);
	if (!d)
		wetuwn NUWW;

	wetuwn to_mdio_device(d);
}
EXPOWT_SYMBOW(fwnode_mdio_find_device);

/**
 * fwnode_phy_find_device - Fow pwovided phy_fwnode, find phy_device.
 *
 * @phy_fwnode: Pointew to the phy's fwnode.
 *
 * If successfuw, wetuwns a pointew to the phy_device with the embedded
 * stwuct device wefcount incwemented by one, ow NUWW on faiwuwe.
 */
stwuct phy_device *fwnode_phy_find_device(stwuct fwnode_handwe *phy_fwnode)
{
	stwuct mdio_device *mdiodev;

	mdiodev = fwnode_mdio_find_device(phy_fwnode);
	if (!mdiodev)
		wetuwn NUWW;

	if (mdiodev->fwags & MDIO_DEVICE_FWAG_PHY)
		wetuwn to_phy_device(&mdiodev->dev);

	put_device(&mdiodev->dev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(fwnode_phy_find_device);

/**
 * device_phy_find_device - Fow the given device, get the phy_device
 * @dev: Pointew to the given device
 *
 * Wefew wetuwn conditions of fwnode_phy_find_device().
 */
stwuct phy_device *device_phy_find_device(stwuct device *dev)
{
	wetuwn fwnode_phy_find_device(dev_fwnode(dev));
}
EXPOWT_SYMBOW_GPW(device_phy_find_device);

/**
 * fwnode_get_phy_node - Get the phy_node using the named wefewence.
 * @fwnode: Pointew to fwnode fwom which phy_node has to be obtained.
 *
 * Wefew wetuwn conditions of fwnode_find_wefewence().
 * Fow ACPI, onwy "phy-handwe" is suppowted. Wegacy DT pwopewties "phy"
 * and "phy-device" awe not suppowted in ACPI. DT suppowts aww the thwee
 * named wefewences to the phy node.
 */
stwuct fwnode_handwe *fwnode_get_phy_node(const stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *phy_node;

	/* Onwy phy-handwe is used fow ACPI */
	phy_node = fwnode_find_wefewence(fwnode, "phy-handwe", 0);
	if (is_acpi_node(fwnode) || !IS_EWW(phy_node))
		wetuwn phy_node;
	phy_node = fwnode_find_wefewence(fwnode, "phy", 0);
	if (IS_EWW(phy_node))
		phy_node = fwnode_find_wefewence(fwnode, "phy-device", 0);
	wetuwn phy_node;
}
EXPOWT_SYMBOW_GPW(fwnode_get_phy_node);

/**
 * phy_pwobe - pwobe and init a PHY device
 * @dev: device to pwobe and init
 *
 * Take cawe of setting up the phy_device stwuctuwe, set the state to WEADY.
 */
static int phy_pwobe(stwuct device *dev)
{
	stwuct phy_device *phydev = to_phy_device(dev);
	stwuct device_dwivew *dwv = phydev->mdio.dev.dwivew;
	stwuct phy_dwivew *phydwv = to_phy_dwivew(dwv);
	int eww = 0;

	phydev->dwv = phydwv;

	/* Disabwe the intewwupt if the PHY doesn't suppowt it
	 * but the intewwupt is stiww a vawid one
	 */
	if (!phy_dwv_suppowts_iwq(phydwv) && phy_intewwupt_is_vawid(phydev))
		phydev->iwq = PHY_POWW;

	if (phydwv->fwags & PHY_IS_INTEWNAW)
		phydev->is_intewnaw = twue;

	/* Deassewt the weset signaw */
	phy_device_weset(phydev, 0);

	if (phydev->dwv->pwobe) {
		eww = phydev->dwv->pwobe(phydev);
		if (eww)
			goto out;
	}

	phy_disabwe_intewwupts(phydev);

	/* Stawt out suppowting evewything. Eventuawwy,
	 * a contwowwew wiww attach, and may modify one
	 * ow both of these vawues
	 */
	if (phydwv->featuwes) {
		winkmode_copy(phydev->suppowted, phydwv->featuwes);
		genphy_c45_wead_eee_abiwities(phydev);
	}
	ewse if (phydwv->get_featuwes)
		eww = phydwv->get_featuwes(phydev);
	ewse if (phydev->is_c45)
		eww = genphy_c45_pma_wead_abiwities(phydev);
	ewse
		eww = genphy_wead_abiwities(phydev);

	if (eww)
		goto out;

	if (!winkmode_test_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
			       phydev->suppowted))
		phydev->autoneg = 0;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
			      phydev->suppowted))
		phydev->is_gigabit_capabwe = 1;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
			      phydev->suppowted))
		phydev->is_gigabit_capabwe = 1;

	of_set_phy_suppowted(phydev);
	phy_advewtise_suppowted(phydev);

	/* Get PHY defauwt EEE advewtising modes and handwe them as potentiawwy
	 * safe initiaw configuwation.
	 */
	eww = genphy_c45_wead_eee_adv(phydev, phydev->advewtising_eee);
	if (eww)
		goto out;

	/* Thewe is no "enabwed" fwag. If PHY is advewtising, assume it is
	 * kind of enabwed.
	 */
	phydev->eee_enabwed = !winkmode_empty(phydev->advewtising_eee);

	/* Some PHYs may advewtise, by defauwt, not suppowt EEE modes. So,
	 * we need to cwean them.
	 */
	if (phydev->eee_enabwed)
		winkmode_and(phydev->advewtising_eee, phydev->suppowted_eee,
			     phydev->advewtising_eee);

	/* Get the EEE modes we want to pwohibit. We wiww ask
	 * the PHY stop advewtising these mode watew on
	 */
	of_set_phy_eee_bwoken(phydev);

	/* The Pause Fwame bits indicate that the PHY can suppowt passing
	 * pause fwames. Duwing autonegotiation, the PHYs wiww detewmine if
	 * they shouwd awwow pause fwames to pass.  The MAC dwivew shouwd then
	 * use that wesuwt to detewmine whethew to enabwe fwow contwow via
	 * pause fwames.
	 *
	 * Nowmawwy, PHY dwivews shouwd not set the Pause bits, and instead
	 * awwow phywib to do that.  Howevew, thewe may be some situations
	 * (e.g. hawdwawe ewwatum) whewe the dwivew wants to set onwy one
	 * of these bits.
	 */
	if (!test_bit(ETHTOOW_WINK_MODE_Pause_BIT, phydev->suppowted) &&
	    !test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, phydev->suppowted)) {
		winkmode_set_bit(ETHTOOW_WINK_MODE_Pause_BIT,
				 phydev->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
				 phydev->suppowted);
	}

	/* Set the state to WEADY by defauwt */
	phydev->state = PHY_WEADY;

	/* Get the WEDs fwom the device twee, and instantiate standawd
	 * WEDs fow them.
	 */
	if (IS_ENABWED(CONFIG_PHYWIB_WEDS))
		eww = of_phy_weds(phydev);

out:
	/* We-assewt the weset signaw on ewwow */
	if (eww)
		phy_device_weset(phydev, 1);

	wetuwn eww;
}

static int phy_wemove(stwuct device *dev)
{
	stwuct phy_device *phydev = to_phy_device(dev);

	cancew_dewayed_wowk_sync(&phydev->state_queue);

	if (IS_ENABWED(CONFIG_PHYWIB_WEDS))
		phy_weds_unwegistew(phydev);

	phydev->state = PHY_DOWN;

	sfp_bus_dew_upstweam(phydev->sfp_bus);
	phydev->sfp_bus = NUWW;

	if (phydev->dwv && phydev->dwv->wemove)
		phydev->dwv->wemove(phydev);

	/* Assewt the weset signaw */
	phy_device_weset(phydev, 1);

	phydev->dwv = NUWW;

	wetuwn 0;
}

/**
 * phy_dwivew_wegistew - wegistew a phy_dwivew with the PHY wayew
 * @new_dwivew: new phy_dwivew to wegistew
 * @ownew: moduwe owning this PHY
 */
int phy_dwivew_wegistew(stwuct phy_dwivew *new_dwivew, stwuct moduwe *ownew)
{
	int wetvaw;

	/* Eithew the featuwes awe hawd coded, ow dynamicawwy
	 * detewmined. It cannot be both.
	 */
	if (WAWN_ON(new_dwivew->featuwes && new_dwivew->get_featuwes)) {
		pw_eww("%s: featuwes and get_featuwes must not both be set\n",
		       new_dwivew->name);
		wetuwn -EINVAW;
	}

	/* PHYWIB device dwivews must not match using a DT compatibwe tabwe
	 * as this bypasses ouw checks that the mdiodev that is being matched
	 * is backed by a stwuct phy_device. If such a case happens, we wiww
	 * make out-of-bounds accesses and wockup in phydev->wock.
	 */
	if (WAWN(new_dwivew->mdiodwv.dwivew.of_match_tabwe,
		 "%s: dwivew must not pwovide a DT match tabwe\n",
		 new_dwivew->name))
		wetuwn -EINVAW;

	new_dwivew->mdiodwv.fwags |= MDIO_DEVICE_IS_PHY;
	new_dwivew->mdiodwv.dwivew.name = new_dwivew->name;
	new_dwivew->mdiodwv.dwivew.bus = &mdio_bus_type;
	new_dwivew->mdiodwv.dwivew.pwobe = phy_pwobe;
	new_dwivew->mdiodwv.dwivew.wemove = phy_wemove;
	new_dwivew->mdiodwv.dwivew.ownew = ownew;
	new_dwivew->mdiodwv.dwivew.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS;

	wetvaw = dwivew_wegistew(&new_dwivew->mdiodwv.dwivew);
	if (wetvaw) {
		pw_eww("%s: Ewwow %d in wegistewing dwivew\n",
		       new_dwivew->name, wetvaw);

		wetuwn wetvaw;
	}

	pw_debug("%s: Wegistewed new dwivew\n", new_dwivew->name);

	wetuwn 0;
}
EXPOWT_SYMBOW(phy_dwivew_wegistew);

int phy_dwivews_wegistew(stwuct phy_dwivew *new_dwivew, int n,
			 stwuct moduwe *ownew)
{
	int i, wet = 0;

	fow (i = 0; i < n; i++) {
		wet = phy_dwivew_wegistew(new_dwivew + i, ownew);
		if (wet) {
			whiwe (i-- > 0)
				phy_dwivew_unwegistew(new_dwivew + i);
			bweak;
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(phy_dwivews_wegistew);

void phy_dwivew_unwegistew(stwuct phy_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->mdiodwv.dwivew);
}
EXPOWT_SYMBOW(phy_dwivew_unwegistew);

void phy_dwivews_unwegistew(stwuct phy_dwivew *dwv, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		phy_dwivew_unwegistew(dwv + i);
}
EXPOWT_SYMBOW(phy_dwivews_unwegistew);

static stwuct phy_dwivew genphy_dwivew = {
	.phy_id		= 0xffffffff,
	.phy_id_mask	= 0xffffffff,
	.name		= "Genewic PHY",
	.get_featuwes	= genphy_wead_abiwities,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
	.set_woopback   = genphy_woopback,
};

static const stwuct ethtoow_phy_ops phy_ethtoow_phy_ops = {
	.get_sset_count		= phy_ethtoow_get_sset_count,
	.get_stwings		= phy_ethtoow_get_stwings,
	.get_stats		= phy_ethtoow_get_stats,
	.get_pwca_cfg		= phy_ethtoow_get_pwca_cfg,
	.set_pwca_cfg		= phy_ethtoow_set_pwca_cfg,
	.get_pwca_status	= phy_ethtoow_get_pwca_status,
	.stawt_cabwe_test	= phy_stawt_cabwe_test,
	.stawt_cabwe_test_tdw	= phy_stawt_cabwe_test_tdw,
};

static const stwuct phywib_stubs __phywib_stubs = {
	.hwtstamp_get = __phy_hwtstamp_get,
	.hwtstamp_set = __phy_hwtstamp_set,
};

static void phywib_wegistew_stubs(void)
{
	phywib_stubs = &__phywib_stubs;
}

static void phywib_unwegistew_stubs(void)
{
	phywib_stubs = NUWW;
}

static int __init phy_init(void)
{
	int wc;

	wtnw_wock();
	ethtoow_set_ethtoow_phy_ops(&phy_ethtoow_phy_ops);
	phywib_wegistew_stubs();
	wtnw_unwock();

	wc = mdio_bus_init();
	if (wc)
		goto eww_ethtoow_phy_ops;

	featuwes_init();

	wc = phy_dwivew_wegistew(&genphy_c45_dwivew, THIS_MODUWE);
	if (wc)
		goto eww_mdio_bus;

	wc = phy_dwivew_wegistew(&genphy_dwivew, THIS_MODUWE);
	if (wc)
		goto eww_c45;

	wetuwn 0;

eww_c45:
	phy_dwivew_unwegistew(&genphy_c45_dwivew);
eww_mdio_bus:
	mdio_bus_exit();
eww_ethtoow_phy_ops:
	wtnw_wock();
	phywib_unwegistew_stubs();
	ethtoow_set_ethtoow_phy_ops(NUWW);
	wtnw_unwock();

	wetuwn wc;
}

static void __exit phy_exit(void)
{
	phy_dwivew_unwegistew(&genphy_c45_dwivew);
	phy_dwivew_unwegistew(&genphy_dwivew);
	mdio_bus_exit();
	wtnw_wock();
	phywib_unwegistew_stubs();
	ethtoow_set_ethtoow_phy_ops(NUWW);
	wtnw_unwock();
}

subsys_initcaww(phy_init);
moduwe_exit(phy_exit);
