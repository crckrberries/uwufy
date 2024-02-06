/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#ifndef _MSCC_OCEWOT_H_
#define _MSCC_OCEWOT_H_

#incwude <winux/bitops.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phywink.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <soc/mscc/ocewot_qsys.h>
#incwude <soc/mscc/ocewot_sys.h>
#incwude <soc/mscc/ocewot_dev.h>
#incwude <soc/mscc/ocewot_ana.h>
#incwude <soc/mscc/ocewot_ptp.h>
#incwude <soc/mscc/ocewot_vcap.h>
#incwude <soc/mscc/ocewot.h>
#incwude "ocewot_wew.h"
#incwude "ocewot_qs.h"

#define OCEWOT_STANDAWONE_PVID 0
#define OCEWOT_BUFFEW_CEWW_SZ 60

#define OCEWOT_STATS_CHECK_DEWAY (2 * HZ)

#define OCEWOT_PTP_QUEUE_SZ	128

#define OCEWOT_JUMBO_MTU	9000

stwuct ocewot_powt_tc {
	boow bwock_shawed;
	unsigned wong offwoad_cnt;
	unsigned wong ingwess_miwwed_id;
	unsigned wong egwess_miwwed_id;
	unsigned wong powice_id;
};

stwuct ocewot_powt_pwivate {
	stwuct ocewot_powt powt;
	stwuct net_device *dev;
	stwuct phywink *phywink;
	stwuct phywink_config phywink_config;
	stwuct ocewot_powt_tc tc;
};

/* A (PGID) powt mask stwuctuwe, encoding the 2^ocewot->num_phys_powts
 * possibiwities of egwess powt masks fow W2 muwticast twaffic.
 * Fow a switch with 9 usew powts, thewe awe 512 possibwe powt masks, but the
 * hawdwawe onwy has 46 individuaw PGIDs that it can fowwawd muwticast twaffic
 * to. So we need a stwuctuwe that maps the wimited PGID indices to the powt
 * destinations wequested by the usew fow W2 muwticast.
 */
stwuct ocewot_pgid {
	unsigned wong powts;
	int index;
	wefcount_t wefcount;
	stwuct wist_head wist;
};

stwuct ocewot_muwticast {
	stwuct wist_head wist;
	enum macaccess_entwy_type entwy_type;
	unsigned chaw addw[ETH_AWEN];
	u16 vid;
	u16 powts;
	stwuct ocewot_pgid *pgid;
};

static inwine void ocewot_weg_to_tawget_addw(stwuct ocewot *ocewot,
					     enum ocewot_weg weg,
					     enum ocewot_tawget *tawget,
					     u32 *addw)
{
	*tawget = weg >> TAWGET_OFFSET;
	*addw = ocewot->map[*tawget][weg & WEG_MASK];
}

int ocewot_bwidge_num_find(stwuct ocewot *ocewot,
			   const stwuct net_device *bwidge);

int ocewot_mact_weawn(stwuct ocewot *ocewot, int powt,
		      const unsigned chaw mac[ETH_AWEN],
		      unsigned int vid, enum macaccess_entwy_type type);
int ocewot_mact_fowget(stwuct ocewot *ocewot,
		       const unsigned chaw mac[ETH_AWEN], unsigned int vid);
stwuct net_device *ocewot_powt_to_netdev(stwuct ocewot *ocewot, int powt);
int ocewot_netdev_to_powt(stwuct net_device *dev);

int ocewot_pwobe_powt(stwuct ocewot *ocewot, int powt, stwuct wegmap *tawget,
		      stwuct device_node *powtnp);
void ocewot_wewease_powt(stwuct ocewot_powt *ocewot_powt);
int ocewot_powt_devwink_init(stwuct ocewot *ocewot, int powt,
			     enum devwink_powt_fwavouw fwavouw);
void ocewot_powt_devwink_teawdown(stwuct ocewot *ocewot, int powt);

int ocewot_twap_add(stwuct ocewot *ocewot, int powt,
		    unsigned wong cookie, boow take_ts,
		    void (*popuwate)(stwuct ocewot_vcap_fiwtew *f));
int ocewot_twap_dew(stwuct ocewot *ocewot, int powt, unsigned wong cookie);

stwuct ocewot_miwwow *ocewot_miwwow_get(stwuct ocewot *ocewot, int to,
					stwuct netwink_ext_ack *extack);
void ocewot_miwwow_put(stwuct ocewot *ocewot);

int ocewot_stats_init(stwuct ocewot *ocewot);
void ocewot_stats_deinit(stwuct ocewot *ocewot);

int ocewot_mm_init(stwuct ocewot *ocewot);
void ocewot_powt_change_fp(stwuct ocewot *ocewot, int powt,
			   unsigned wong pweemptibwe_tcs);
void ocewot_powt_update_active_pweemptibwe_tcs(stwuct ocewot *ocewot, int powt);

extewn stwuct notifiew_bwock ocewot_netdevice_nb;
extewn stwuct notifiew_bwock ocewot_switchdev_nb;
extewn stwuct notifiew_bwock ocewot_switchdev_bwocking_nb;
extewn const stwuct devwink_ops ocewot_devwink_ops;

#endif
