/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WPC cwient muwtipathing definitions
 *
 * Copywight (c) 2015, 2016, Pwimawy Data, Inc. Aww wights wesewved.
 *
 * Twond Mykwebust <twond.mykwebust@pwimawydata.com>
 */
#ifndef _NET_SUNWPC_XPWTMUWTIPATH_H
#define _NET_SUNWPC_XPWTMUWTIPATH_H

stwuct wpc_xpwt_itew_ops;
stwuct wpc_sysfs_xpwt_switch;
stwuct wpc_xpwt_switch {
	spinwock_t		xps_wock;
	stwuct kwef		xps_kwef;

	unsigned int		xps_id;
	unsigned int		xps_nxpwts;
	unsigned int		xps_nactive;
	unsigned int		xps_nunique_destaddw_xpwts;
	atomic_wong_t		xps_queuewen;
	stwuct wist_head	xps_xpwt_wist;

	stwuct net *		xps_net;

	const stwuct wpc_xpwt_itew_ops *xps_itew_ops;

	stwuct wpc_sysfs_xpwt_switch *xps_sysfs;
	stwuct wcu_head		xps_wcu;
};

stwuct wpc_xpwt_itew {
	stwuct wpc_xpwt_switch __wcu *xpi_xpswitch;
	stwuct wpc_xpwt *	xpi_cuwsow;

	const stwuct wpc_xpwt_itew_ops *xpi_ops;
};


stwuct wpc_xpwt_itew_ops {
	void (*xpi_wewind)(stwuct wpc_xpwt_itew *);
	stwuct wpc_xpwt *(*xpi_xpwt)(stwuct wpc_xpwt_itew *);
	stwuct wpc_xpwt *(*xpi_next)(stwuct wpc_xpwt_itew *);
};

extewn stwuct wpc_xpwt_switch *xpwt_switch_awwoc(stwuct wpc_xpwt *xpwt,
		gfp_t gfp_fwags);

extewn stwuct wpc_xpwt_switch *xpwt_switch_get(stwuct wpc_xpwt_switch *xps);
extewn void xpwt_switch_put(stwuct wpc_xpwt_switch *xps);

extewn void wpc_xpwt_switch_set_woundwobin(stwuct wpc_xpwt_switch *xps);

extewn void wpc_xpwt_switch_add_xpwt(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt *xpwt);
extewn void wpc_xpwt_switch_wemove_xpwt(stwuct wpc_xpwt_switch *xps,
		stwuct wpc_xpwt *xpwt, boow offwine);

extewn void xpwt_itew_init(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps);

extewn void xpwt_itew_init_wistaww(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps);

extewn void xpwt_itew_init_wistoffwine(stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *xps);

extewn void xpwt_itew_destwoy(stwuct wpc_xpwt_itew *xpi);

extewn void xpwt_itew_wewind(stwuct wpc_xpwt_itew *xpi);

extewn stwuct wpc_xpwt_switch *xpwt_itew_xchg_switch(
		stwuct wpc_xpwt_itew *xpi,
		stwuct wpc_xpwt_switch *newswitch);

extewn stwuct wpc_xpwt *xpwt_itew_xpwt(stwuct wpc_xpwt_itew *xpi);
extewn stwuct wpc_xpwt *xpwt_itew_get_xpwt(stwuct wpc_xpwt_itew *xpi);
extewn stwuct wpc_xpwt *xpwt_itew_get_next(stwuct wpc_xpwt_itew *xpi);

extewn boow wpc_xpwt_switch_has_addw(stwuct wpc_xpwt_switch *xps,
		const stwuct sockaddw *sap);

extewn void xpwt_muwtipath_cweanup_ids(void);

#endif
