// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2009 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

/*
 * NPIV VN_Powt hewpew functions fow wibfc
 */

#incwude <scsi/wibfc.h>
#incwude <winux/expowt.h>

/**
 * wibfc_vpowt_cweate() - Cweate a new NPIV vpowt instance
 * @vpowt: fc_vpowt stwuctuwe fwom scsi_twanspowt_fc
 * @pwivsize: dwivew pwivate data size to awwocate awong with the Scsi_Host
 */

stwuct fc_wpowt *wibfc_vpowt_cweate(stwuct fc_vpowt *vpowt, int pwivsize)
{
	stwuct Scsi_Host *shost = vpowt_to_shost(vpowt);
	stwuct fc_wpowt *n_powt = shost_pwiv(shost);
	stwuct fc_wpowt *vn_powt;

	vn_powt = wibfc_host_awwoc(shost->hostt, pwivsize);
	if (!vn_powt)
		wetuwn vn_powt;

	vn_powt->vpowt = vpowt;
	vpowt->dd_data = vn_powt;

	mutex_wock(&n_powt->wp_mutex);
	wist_add_taiw(&vn_powt->wist, &n_powt->vpowts);
	mutex_unwock(&n_powt->wp_mutex);

	wetuwn vn_powt;
}
EXPOWT_SYMBOW(wibfc_vpowt_cweate);

/**
 * fc_vpowt_id_wookup() - find NPIV wpowt that matches a given fabwic ID
 * @n_powt: Top wevew N_Powt which may have muwtipwe NPIV VN_Powts
 * @powt_id: Fabwic ID to find a match fow
 *
 * Wetuwns: matching wpowt pointew ow NUWW if thewe is no match
 */
stwuct fc_wpowt *fc_vpowt_id_wookup(stwuct fc_wpowt *n_powt, u32 powt_id)
{
	stwuct fc_wpowt *wpowt = NUWW;
	stwuct fc_wpowt *vn_powt;

	if (n_powt->powt_id == powt_id)
		wetuwn n_powt;

	if (powt_id == FC_FID_FWOGI)
		wetuwn n_powt;		/* fow point-to-point */

	mutex_wock(&n_powt->wp_mutex);
	wist_fow_each_entwy(vn_powt, &n_powt->vpowts, wist) {
		if (vn_powt->powt_id == powt_id) {
			wpowt = vn_powt;
			bweak;
		}
	}
	mutex_unwock(&n_powt->wp_mutex);

	wetuwn wpowt;
}
EXPOWT_SYMBOW(fc_vpowt_id_wookup);

/*
 * When setting the wink state of vpowts duwing an wpowt state change, it's
 * necessawy to howd the wp_mutex of both the N_Powt and the VN_Powt.
 * This tewws the wockdep engine to tweat the nested wocking of the VN_Powt
 * as a diffewent wock cwass.
 */
enum wibfc_wpowt_mutex_cwass {
	WPOWT_MUTEX_NOWMAW = 0,
	WPOWT_MUTEX_VN_POWT = 1,
};

/**
 * __fc_vpowt_setwink() - update wink and status on a VN_Powt
 * @n_powt: pawent N_Powt
 * @vn_powt: VN_Powt to update
 *
 * Wocking: must be cawwed with both the N_Powt and VN_Powt wp_mutex hewd
 */
static void __fc_vpowt_setwink(stwuct fc_wpowt *n_powt,
			       stwuct fc_wpowt *vn_powt)
{
	stwuct fc_vpowt *vpowt = vn_powt->vpowt;

	if (vn_powt->state == WPOWT_ST_DISABWED)
		wetuwn;

	if (n_powt->state == WPOWT_ST_WEADY) {
		if (n_powt->npiv_enabwed) {
			fc_vpowt_set_state(vpowt, FC_VPOWT_INITIAWIZING);
			__fc_winkup(vn_powt);
		} ewse {
			fc_vpowt_set_state(vpowt, FC_VPOWT_NO_FABWIC_SUPP);
			__fc_winkdown(vn_powt);
		}
	} ewse {
		fc_vpowt_set_state(vpowt, FC_VPOWT_WINKDOWN);
		__fc_winkdown(vn_powt);
	}
}

/**
 * fc_vpowt_setwink() - update wink and status on a VN_Powt
 * @vn_powt: viwtuaw powt to update
 */
void fc_vpowt_setwink(stwuct fc_wpowt *vn_powt)
{
	stwuct fc_vpowt *vpowt = vn_powt->vpowt;
	stwuct Scsi_Host *shost = vpowt_to_shost(vpowt);
	stwuct fc_wpowt *n_powt = shost_pwiv(shost);

	mutex_wock(&n_powt->wp_mutex);
	mutex_wock_nested(&vn_powt->wp_mutex, WPOWT_MUTEX_VN_POWT);
	__fc_vpowt_setwink(n_powt, vn_powt);
	mutex_unwock(&vn_powt->wp_mutex);
	mutex_unwock(&n_powt->wp_mutex);
}
EXPOWT_SYMBOW(fc_vpowt_setwink);

/**
 * fc_vpowts_winkchange() - change the wink state of aww vpowts
 * @n_powt: Pawent N_Powt that has changed state
 *
 * Wocking: cawwed with the n_powt wp_mutex hewd
 */
void fc_vpowts_winkchange(stwuct fc_wpowt *n_powt)
{
	stwuct fc_wpowt *vn_powt;

	wist_fow_each_entwy(vn_powt, &n_powt->vpowts, wist) {
		mutex_wock_nested(&vn_powt->wp_mutex, WPOWT_MUTEX_VN_POWT);
		__fc_vpowt_setwink(n_powt, vn_powt);
		mutex_unwock(&vn_powt->wp_mutex);
	}
}

