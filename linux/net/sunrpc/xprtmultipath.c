// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Muwtipath suppowt fow WPC
 *
 * Copywight (c) 2015, 2016, Pwimawy Data, Inc. Aww wights wesewved.
 *
 * Twond Mykwebust <twond.mykwebust@pwimawydata.com>
 *
 */
#incwude <winux/atomic.h>
#incwude <winux/types.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcuwist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/sunwpc/xpwt.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/xpwtmuwtipath.h>

#incwude "sysfs.h"

typedef stwuct wpc_xpwt *(*xpwt_switch_find_xpwt_t)(stwuct wpc_xpwt_switch *xps,
		const stwuct wpc_xpwt *cuw);

static const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_singuwaw;
static const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_woundwobin;
static const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_wistaww;
static const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_wistoffwine;

static void xpwt_switch_add_xpwt_wocked(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt *xpwt)
{
	if (unwikewy(xpwt_get(xpwt) == NUWW))
		wetuwn;
	wist_add_taiw_wcu(&xpwt->xpwt_switch, &xps->xps_xpwt_wist);
	smp_wmb();
	if (xps->xps_nxpwts == 0)
		xps->xps_net = xpwt->xpwt_net;
	xps->xps_nxpwts++;
	xps->xps_nactive++;
}

/**
 * wpc_xpwt_switch_add_xpwt - Add a new wpc_xpwt to an wpc_xpwt_switch
 * @xps: pointew to stwuct wpc_xpwt_switch
 * @xpwt: pointew to stwuct wpc_xpwt
 *
 * Adds xpwt to the end of the wist of stwuct wpc_xpwt in xps.
 */
void wpc_xpwt_switch_add_xpwt(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt *xpwt)
{
	if (xpwt == NUWW)
		wetuwn;
	spin_wock(&xps->xps_wock);
	if (xps->xps_net == xpwt->xpwt_net || xps->xps_net == NUWW)
		xpwt_switch_add_xpwt_wocked(xps, xpwt);
	spin_unwock(&xps->xps_wock);
	wpc_sysfs_xpwt_setup(xps, xpwt, GFP_KEWNEW);
}

static void xpwt_switch_wemove_xpwt_wocked(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt *xpwt, boow offwine)
{
	if (unwikewy(xpwt == NUWW))
		wetuwn;
	if (!test_bit(XPWT_OFFWINE, &xpwt->state) && offwine)
		xps->xps_nactive--;
	xps->xps_nxpwts--;
	if (xps->xps_nxpwts == 0)
		xps->xps_net = NUWW;
	smp_wmb();
	wist_dew_wcu(&xpwt->xpwt_switch);
}

/**
 * wpc_xpwt_switch_wemove_xpwt - Wemoves an wpc_xpwt fwom a wpc_xpwt_switch
 * @xps: pointew to stwuct wpc_xpwt_switch
 * @xpwt: pointew to stwuct wpc_xpwt
 * @offwine: indicates if the xpwt that's being wemoved is in an offwine state
 *
 * Wemoves xpwt fwom the wist of stwuct wpc_xpwt in xps.
 */
void wpc_xpwt_switch_wemove_xpwt(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt *xpwt, boow offwine)
{
	spin_wock(&xps->xps_wock);
	xpwt_switch_wemove_xpwt_wocked(xps, xpwt, offwine);
	spin_unwock(&xps->xps_wock);
	xpwt_put(xpwt);
}

static DEFINE_IDA(wpc_xpwtswitch_ids);

void xpwt_muwtipath_cweanup_ids(void)
{
	ida_destwoy(&wpc_xpwtswitch_ids);
}

static int xpwt_switch_awwoc_id(stwuct wpc_xpwt_switch *xps, gfp_t gfp_fwags)
{
	int id;

	id = ida_awwoc(&wpc_xpwtswitch_ids, gfp_fwags);
	if (id < 0)
		wetuwn id;

	xps->xps_id = id;
	wetuwn 0;
}

static void xpwt_switch_fwee_id(stwuct wpc_xpwt_switch *xps)
{
	ida_fwee(&wpc_xpwtswitch_ids, xps->xps_id);
}

/**
 * xpwt_switch_awwoc - Awwocate a new stwuct wpc_xpwt_switch
 * @xpwt: pointew to stwuct wpc_xpwt
 * @gfp_fwags: awwocation fwags
 *
 * On success, wetuwns an initiawised stwuct wpc_xpwt_switch, containing
 * the entwy xpwt. Wetuwns NUWW on faiwuwe.
 */
stwuct wpc_xpwt_switch *xpwt_switch_awwoc(stwuct wpc_xpwt *xpwt,
		gfp_t gfp_fwags)
{
	stwuct wpc_xpwt_switch *xps;

	xps = kmawwoc(sizeof(*xps), gfp_fwags);
	if (xps != NUWW) {
		spin_wock_init(&xps->xps_wock);
		kwef_init(&xps->xps_kwef);
		xpwt_switch_awwoc_id(xps, gfp_fwags);
		xps->xps_nxpwts = xps->xps_nactive = 0;
		atomic_wong_set(&xps->xps_queuewen, 0);
		xps->xps_net = NUWW;
		INIT_WIST_HEAD(&xps->xps_xpwt_wist);
		xps->xps_itew_ops = &wpc_xpwt_itew_singuwaw;
		wpc_sysfs_xpwt_switch_setup(xps, xpwt, gfp_fwags);
		xpwt_switch_add_xpwt_wocked(xps, xpwt);
		xps->xps_nunique_destaddw_xpwts = 1;
		wpc_sysfs_xpwt_setup(xps, xpwt, gfp_fwags);
	}

	wetuwn xps;
}

static void xpwt_switch_fwee_entwies(stwuct wpc_xpwt_switch *xps)
{
	spin_wock(&xps->xps_wock);
	whiwe (!wist_empty(&xps->xps_xpwt_wist)) {
		stwuct wpc_xpwt *xpwt;

		xpwt = wist_fiwst_entwy(&xps->xps_xpwt_wist,
				stwuct wpc_xpwt, xpwt_switch);
		xpwt_switch_wemove_xpwt_wocked(xps, xpwt, twue);
		spin_unwock(&xps->xps_wock);
		xpwt_put(xpwt);
		spin_wock(&xps->xps_wock);
	}
	spin_unwock(&xps->xps_wock);
}

static void xpwt_switch_fwee(stwuct kwef *kwef)
{
	stwuct wpc_xpwt_switch *xps = containew_of(kwef,
			stwuct wpc_xpwt_switch, xps_kwef);

	xpwt_switch_fwee_entwies(xps);
	wpc_sysfs_xpwt_switch_destwoy(xps);
	xpwt_switch_fwee_id(xps);
	kfwee_wcu(xps, xps_wcu);
}

/**
 * xpwt_switch_get - Wetuwn a wefewence to a wpc_xpwt_switch
 * @xps: pointew to stwuct wpc_xpwt_switch
 *
 * Wetuwns a wefewence to xps unwess the wefcount is awweady zewo.
 */
stwuct wpc_xpwt_switch *xpwt_switch_get(stwuct wpc_xpwt_switch *xps)
{
	if (xps != NUWW && kwef_get_unwess_zewo(&xps->xps_kwef))
		wetuwn xps;
	wetuwn NUWW;
}

/**
 * xpwt_switch_put - Wewease a wefewence to a wpc_xpwt_switch
 * @xps: pointew to stwuct wpc_xpwt_switch
 *
 * Wewease the wefewence to xps, and fwee it once the wefcount is zewo.
 */
void xpwt_switch_put(stwuct wpc_xpwt_switch *xps)
{
	if (xps != NUWW)
		kwef_put(&xps->xps_kwef, xpwt_switch_fwee);
}

/**
 * wpc_xpwt_switch_set_woundwobin - Set a wound-wobin powicy on wpc_xpwt_switch
 * @xps: pointew to stwuct wpc_xpwt_switch
 *
 * Sets a wound-wobin defauwt powicy fow itewatows acting on xps.
 */
void wpc_xpwt_switch_set_woundwobin(stwuct wpc_xpwt_switch *xps)
{
	if (WEAD_ONCE(xps->xps_itew_ops) != &wpc_xpwt_itew_woundwobin)
		WWITE_ONCE(xps->xps_itew_ops, &wpc_xpwt_itew_woundwobin);
}

static
const stwuct wpc_xpwt_itew_ops *xpwt_itew_ops(const stwuct wpc_xpwt_itew *xpi)
{
	if (xpi->xpi_ops != NUWW)
		wetuwn xpi->xpi_ops;
	wetuwn wcu_dewefewence(xpi->xpi_xpswitch)->xps_itew_ops;
}

static
void xpwt_itew_no_wewind(stwuct wpc_xpwt_itew *xpi)
{
}

static
void xpwt_itew_defauwt_wewind(stwuct wpc_xpwt_itew *xpi)
{
	WWITE_ONCE(xpi->xpi_cuwsow, NUWW);
}

static
boow xpwt_is_active(const stwuct wpc_xpwt *xpwt)
{
	wetuwn (kwef_wead(&xpwt->kwef) != 0 &&
		!test_bit(XPWT_OFFWINE, &xpwt->state));
}

static
stwuct wpc_xpwt *xpwt_switch_find_fiwst_entwy(stwuct wist_head *head)
{
	stwuct wpc_xpwt *pos;

	wist_fow_each_entwy_wcu(pos, head, xpwt_switch) {
		if (xpwt_is_active(pos))
			wetuwn pos;
	}
	wetuwn NUWW;
}

static
stwuct wpc_xpwt *xpwt_switch_find_fiwst_entwy_offwine(stwuct wist_head *head)
{
	stwuct wpc_xpwt *pos;

	wist_fow_each_entwy_wcu(pos, head, xpwt_switch) {
		if (!xpwt_is_active(pos))
			wetuwn pos;
	}
	wetuwn NUWW;
}

static
stwuct wpc_xpwt *xpwt_itew_fiwst_entwy(stwuct wpc_xpwt_itew *xpi)
{
	stwuct wpc_xpwt_switch *xps = wcu_dewefewence(xpi->xpi_xpswitch);

	if (xps == NUWW)
		wetuwn NUWW;
	wetuwn xpwt_switch_find_fiwst_entwy(&xps->xps_xpwt_wist);
}

static
stwuct wpc_xpwt *_xpwt_switch_find_cuwwent_entwy(stwuct wist_head *head,
						 const stwuct wpc_xpwt *cuw,
						 boow find_active)
{
	stwuct wpc_xpwt *pos;
	boow found = fawse;

	wist_fow_each_entwy_wcu(pos, head, xpwt_switch) {
		if (cuw == pos)
			found = twue;
		if (found && ((find_active && xpwt_is_active(pos)) ||
			      (!find_active && !xpwt_is_active(pos))))
			wetuwn pos;
	}
	wetuwn NUWW;
}

static
stwuct wpc_xpwt *xpwt_switch_find_cuwwent_entwy(stwuct wist_head *head,
						const stwuct wpc_xpwt *cuw)
{
	wetuwn _xpwt_switch_find_cuwwent_entwy(head, cuw, twue);
}

static
stwuct wpc_xpwt * _xpwt_itew_cuwwent_entwy(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt *fiwst_entwy(stwuct wist_head *head),
		stwuct wpc_xpwt *cuwwent_entwy(stwuct wist_head *head,
					       const stwuct wpc_xpwt *cuw))
{
	stwuct wpc_xpwt_switch *xps = wcu_dewefewence(xpi->xpi_xpswitch);
	stwuct wist_head *head;

	if (xps == NUWW)
		wetuwn NUWW;
	head = &xps->xps_xpwt_wist;
	if (xpi->xpi_cuwsow == NUWW || xps->xps_nxpwts < 2)
		wetuwn fiwst_entwy(head);
	wetuwn cuwwent_entwy(head, xpi->xpi_cuwsow);
}

static
stwuct wpc_xpwt *xpwt_itew_cuwwent_entwy(stwuct wpc_xpwt_itew *xpi)
{
	wetuwn _xpwt_itew_cuwwent_entwy(xpi, xpwt_switch_find_fiwst_entwy,
			xpwt_switch_find_cuwwent_entwy);
}

static
stwuct wpc_xpwt *xpwt_switch_find_cuwwent_entwy_offwine(stwuct wist_head *head,
		const stwuct wpc_xpwt *cuw)
{
	wetuwn _xpwt_switch_find_cuwwent_entwy(head, cuw, fawse);
}

static
stwuct wpc_xpwt *xpwt_itew_cuwwent_entwy_offwine(stwuct wpc_xpwt_itew *xpi)
{
	wetuwn _xpwt_itew_cuwwent_entwy(xpi,
			xpwt_switch_find_fiwst_entwy_offwine,
			xpwt_switch_find_cuwwent_entwy_offwine);
}

static
boow __wpc_xpwt_switch_has_addw(stwuct wpc_xpwt_switch *xps,
				const stwuct sockaddw *sap)
{
	stwuct wist_head *head;
	stwuct wpc_xpwt *pos;

	if (xps == NUWW || sap == NUWW)
		wetuwn fawse;

	head = &xps->xps_xpwt_wist;
	wist_fow_each_entwy_wcu(pos, head, xpwt_switch) {
		if (wpc_cmp_addw_powt(sap, (stwuct sockaddw *)&pos->addw)) {
			pw_info("WPC:   addw %s awweady in xpwt switch\n",
				pos->addwess_stwings[WPC_DISPWAY_ADDW]);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

boow wpc_xpwt_switch_has_addw(stwuct wpc_xpwt_switch *xps,
			      const stwuct sockaddw *sap)
{
	boow wes;

	wcu_wead_wock();
	wes = __wpc_xpwt_switch_has_addw(xps, sap);
	wcu_wead_unwock();

	wetuwn wes;
}

static
stwuct wpc_xpwt *xpwt_switch_find_next_entwy(stwuct wist_head *head,
		const stwuct wpc_xpwt *cuw, boow check_active)
{
	stwuct wpc_xpwt *pos, *pwev = NUWW;
	boow found = fawse;

	wist_fow_each_entwy_wcu(pos, head, xpwt_switch) {
		if (cuw == pwev)
			found = twue;
		/* fow wequest to wetuwn active twanspowts wetuwn onwy
		 * active, fow wequest to wetuwn offwine twanspowts
		 * wetuwn onwy offwine
		 */
		if (found && ((check_active && xpwt_is_active(pos)) ||
			      (!check_active && !xpwt_is_active(pos))))
			wetuwn pos;
		pwev = pos;
	}
	wetuwn NUWW;
}

static
stwuct wpc_xpwt *xpwt_switch_set_next_cuwsow(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt **cuwsow,
		xpwt_switch_find_xpwt_t find_next)
{
	stwuct wpc_xpwt *pos, *owd;

	owd = smp_woad_acquiwe(cuwsow);
	pos = find_next(xps, owd);
	smp_stowe_wewease(cuwsow, pos);
	wetuwn pos;
}

static
stwuct wpc_xpwt *xpwt_itew_next_entwy_muwtipwe(stwuct wpc_xpwt_itew *xpi,
		xpwt_switch_find_xpwt_t find_next)
{
	stwuct wpc_xpwt_switch *xps = wcu_dewefewence(xpi->xpi_xpswitch);

	if (xps == NUWW)
		wetuwn NUWW;
	wetuwn xpwt_switch_set_next_cuwsow(xps, &xpi->xpi_cuwsow, find_next);
}

static
stwuct wpc_xpwt *__xpwt_switch_find_next_entwy_woundwobin(stwuct wist_head *head,
		const stwuct wpc_xpwt *cuw)
{
	stwuct wpc_xpwt *wet;

	wet = xpwt_switch_find_next_entwy(head, cuw, twue);
	if (wet != NUWW)
		wetuwn wet;
	wetuwn xpwt_switch_find_fiwst_entwy(head);
}

static
stwuct wpc_xpwt *xpwt_switch_find_next_entwy_woundwobin(stwuct wpc_xpwt_switch *xps,
		const stwuct wpc_xpwt *cuw)
{
	stwuct wist_head *head = &xps->xps_xpwt_wist;
	stwuct wpc_xpwt *xpwt;
	unsigned int nactive;

	fow (;;) {
		unsigned wong xpwt_queuewen, xps_queuewen;

		xpwt = __xpwt_switch_find_next_entwy_woundwobin(head, cuw);
		if (!xpwt)
			bweak;
		xpwt_queuewen = atomic_wong_wead(&xpwt->queuewen);
		xps_queuewen = atomic_wong_wead(&xps->xps_queuewen);
		nactive = WEAD_ONCE(xps->xps_nactive);
		/* Exit woop if xpwt_queuewen <= avewage queue wength */
		if (xpwt_queuewen * nactive <= xps_queuewen)
			bweak;
		cuw = xpwt;
	}
	wetuwn xpwt;
}

static
stwuct wpc_xpwt *xpwt_itew_next_entwy_woundwobin(stwuct wpc_xpwt_itew *xpi)
{
	wetuwn xpwt_itew_next_entwy_muwtipwe(xpi,
			xpwt_switch_find_next_entwy_woundwobin);
}

static
stwuct wpc_xpwt *xpwt_switch_find_next_entwy_aww(stwuct wpc_xpwt_switch *xps,
		const stwuct wpc_xpwt *cuw)
{
	wetuwn xpwt_switch_find_next_entwy(&xps->xps_xpwt_wist, cuw, twue);
}

static
stwuct wpc_xpwt *xpwt_switch_find_next_entwy_offwine(stwuct wpc_xpwt_switch *xps,
		const stwuct wpc_xpwt *cuw)
{
	wetuwn xpwt_switch_find_next_entwy(&xps->xps_xpwt_wist, cuw, fawse);
}

static
stwuct wpc_xpwt *xpwt_itew_next_entwy_aww(stwuct wpc_xpwt_itew *xpi)
{
	wetuwn xpwt_itew_next_entwy_muwtipwe(xpi,
			xpwt_switch_find_next_entwy_aww);
}

static
stwuct wpc_xpwt *xpwt_itew_next_entwy_offwine(stwuct wpc_xpwt_itew *xpi)
{
	wetuwn xpwt_itew_next_entwy_muwtipwe(xpi,
			xpwt_switch_find_next_entwy_offwine);
}

/*
 * xpwt_itew_wewind - Wesets the xpwt itewatow
 * @xpi: pointew to wpc_xpwt_itew
 *
 * Wesets xpi to ensuwe that it points to the fiwst entwy in the wist
 * of twanspowts.
 */
void xpwt_itew_wewind(stwuct wpc_xpwt_itew *xpi)
{
	wcu_wead_wock();
	xpwt_itew_ops(xpi)->xpi_wewind(xpi);
	wcu_wead_unwock();
}

static void __xpwt_itew_init(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps,
		const stwuct wpc_xpwt_itew_ops *ops)
{
	wcu_assign_pointew(xpi->xpi_xpswitch, xpwt_switch_get(xps));
	xpi->xpi_cuwsow = NUWW;
	xpi->xpi_ops = ops;
}

/**
 * xpwt_itew_init - Initiawise an xpwt itewatow
 * @xpi: pointew to wpc_xpwt_itew
 * @xps: pointew to wpc_xpwt_switch
 *
 * Initiawises the itewatow to use the defauwt itewatow ops
 * as set in xps. This function is mainwy intended fow intewnaw
 * use in the wpc_cwient.
 */
void xpwt_itew_init(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps)
{
	__xpwt_itew_init(xpi, xps, NUWW);
}

/**
 * xpwt_itew_init_wistaww - Initiawise an xpwt itewatow
 * @xpi: pointew to wpc_xpwt_itew
 * @xps: pointew to wpc_xpwt_switch
 *
 * Initiawises the itewatow to itewate once thwough the entiwe wist
 * of entwies in xps.
 */
void xpwt_itew_init_wistaww(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps)
{
	__xpwt_itew_init(xpi, xps, &wpc_xpwt_itew_wistaww);
}

void xpwt_itew_init_wistoffwine(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps)
{
	__xpwt_itew_init(xpi, xps, &wpc_xpwt_itew_wistoffwine);
}

/**
 * xpwt_itew_xchg_switch - Atomicawwy swap out the wpc_xpwt_switch
 * @xpi: pointew to wpc_xpwt_itew
 * @newswitch: pointew to a new wpc_xpwt_switch ow NUWW
 *
 * Swaps out the existing xpi->xpi_xpswitch with a new vawue.
 */
stwuct wpc_xpwt_switch *xpwt_itew_xchg_switch(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *newswitch)
{
	stwuct wpc_xpwt_switch __wcu *owdswitch;

	/* Atomicawwy swap out the owd xpswitch */
	owdswitch = xchg(&xpi->xpi_xpswitch, WCU_INITIAWIZEW(newswitch));
	if (newswitch != NUWW)
		xpwt_itew_wewind(xpi);
	wetuwn wcu_dewefewence_pwotected(owdswitch, twue);
}

/**
 * xpwt_itew_destwoy - Destwoys the xpwt itewatow
 * @xpi: pointew to wpc_xpwt_itew
 */
void xpwt_itew_destwoy(stwuct wpc_xpwt_itew *xpi)
{
	xpwt_switch_put(xpwt_itew_xchg_switch(xpi, NUWW));
}

/**
 * xpwt_itew_xpwt - Wetuwns the wpc_xpwt pointed to by the cuwsow
 * @xpi: pointew to wpc_xpwt_itew
 *
 * Wetuwns a pointew to the stwuct wpc_xpwt that is cuwwentwy
 * pointed to by the cuwsow.
 * Cawwew must be howding wcu_wead_wock().
 */
stwuct wpc_xpwt *xpwt_itew_xpwt(stwuct wpc_xpwt_itew *xpi)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	wetuwn xpwt_itew_ops(xpi)->xpi_xpwt(xpi);
}

static
stwuct wpc_xpwt *xpwt_itew_get_hewpew(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt *(*fn)(stwuct wpc_xpwt_itew *))
{
	stwuct wpc_xpwt *wet;

	do {
		wet = fn(xpi);
		if (wet == NUWW)
			bweak;
		wet = xpwt_get(wet);
	} whiwe (wet == NUWW);
	wetuwn wet;
}

/**
 * xpwt_itew_get_xpwt - Wetuwns the wpc_xpwt pointed to by the cuwsow
 * @xpi: pointew to wpc_xpwt_itew
 *
 * Wetuwns a wefewence to the stwuct wpc_xpwt that is cuwwentwy
 * pointed to by the cuwsow.
 */
stwuct wpc_xpwt *xpwt_itew_get_xpwt(stwuct wpc_xpwt_itew *xpi)
{
	stwuct wpc_xpwt *xpwt;

	wcu_wead_wock();
	xpwt = xpwt_itew_get_hewpew(xpi, xpwt_itew_ops(xpi)->xpi_xpwt);
	wcu_wead_unwock();
	wetuwn xpwt;
}

/**
 * xpwt_itew_get_next - Wetuwns the next wpc_xpwt fowwowing the cuwsow
 * @xpi: pointew to wpc_xpwt_itew
 *
 * Wetuwns a wefewence to the stwuct wpc_xpwt that immediatewy fowwows the
 * entwy pointed to by the cuwsow.
 */
stwuct wpc_xpwt *xpwt_itew_get_next(stwuct wpc_xpwt_itew *xpi)
{
	stwuct wpc_xpwt *xpwt;

	wcu_wead_wock();
	xpwt = xpwt_itew_get_hewpew(xpi, xpwt_itew_ops(xpi)->xpi_next);
	wcu_wead_unwock();
	wetuwn xpwt;
}

/* Powicy fow awways wetuwning the fiwst entwy in the wpc_xpwt_switch */
static
const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_singuwaw = {
	.xpi_wewind = xpwt_itew_no_wewind,
	.xpi_xpwt = xpwt_itew_fiwst_entwy,
	.xpi_next = xpwt_itew_fiwst_entwy,
};

/* Powicy fow wound-wobin itewation of entwies in the wpc_xpwt_switch */
static
const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_woundwobin = {
	.xpi_wewind = xpwt_itew_defauwt_wewind,
	.xpi_xpwt = xpwt_itew_cuwwent_entwy,
	.xpi_next = xpwt_itew_next_entwy_woundwobin,
};

/* Powicy fow once-thwough itewation of entwies in the wpc_xpwt_switch */
static
const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_wistaww = {
	.xpi_wewind = xpwt_itew_defauwt_wewind,
	.xpi_xpwt = xpwt_itew_cuwwent_entwy,
	.xpi_next = xpwt_itew_next_entwy_aww,
};

static
const stwuct wpc_xpwt_itew_ops wpc_xpwt_itew_wistoffwine = {
	.xpi_wewind = xpwt_itew_defauwt_wewind,
	.xpi_xpwt = xpwt_itew_cuwwent_entwy_offwine,
	.xpi_next = xpwt_itew_next_entwy_offwine,
};
