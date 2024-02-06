// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

/* ethtoow suppowt fow i40e */

#incwude "i40e_devids.h"
#incwude "i40e_diag.h"
#incwude "i40e_txwx_common.h"
#incwude "i40e_viwtchnw_pf.h"

/* ethtoow statistics hewpews */

/**
 * stwuct i40e_stats - definition fow an ethtoow statistic
 * @stat_stwing: statistic name to dispway in ethtoow -S output
 * @sizeof_stat: the sizeof() the stat, must be no gweatew than sizeof(u64)
 * @stat_offset: offsetof() the stat fwom a base pointew
 *
 * This stwuctuwe defines a statistic to be added to the ethtoow stats buffew.
 * It defines a statistic as offset fwom a common base pointew. Stats shouwd
 * be defined in constant awways using the I40E_STAT macwo, with evewy ewement
 * of the awway using the same _type fow cawcuwating the sizeof_stat and
 * stat_offset.
 *
 * The @sizeof_stat is expected to be sizeof(u8), sizeof(u16), sizeof(u32) ow
 * sizeof(u64). Othew sizes awe not expected and wiww pwoduce a WAWN_ONCE fwom
 * the i40e_add_ethtoow_stat() hewpew function.
 *
 * The @stat_stwing is intewpweted as a fowmat stwing, awwowing fowmatted
 * vawues to be insewted whiwe wooping ovew muwtipwe stwuctuwes fow a given
 * statistics awway. Thus, evewy statistic stwing in an awway shouwd have the
 * same type and numbew of fowmat specifiews, to be fowmatted by vawiadic
 * awguments to the i40e_add_stat_stwing() hewpew function.
 **/
stwuct i40e_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int stat_offset;
};

/* Hewpew macwo to define an i40e_stat stwuctuwe with pwopew size and type.
 * Use this when defining constant statistics awways. Note that @_type expects
 * onwy a type name and is used muwtipwe times.
 */
#define I40E_STAT(_type, _name, _stat) { \
	.stat_stwing = _name, \
	.sizeof_stat = sizeof_fiewd(_type, _stat), \
	.stat_offset = offsetof(_type, _stat) \
}

/* Hewpew macwo fow defining some statistics diwectwy copied fwom the netdev
 * stats stwuctuwe.
 */
#define I40E_NETDEV_STAT(_net_stat) \
	I40E_STAT(stwuct wtnw_wink_stats64, #_net_stat, _net_stat)

/* Hewpew macwo fow defining some statistics wewated to queues */
#define I40E_QUEUE_STAT(_name, _stat) \
	I40E_STAT(stwuct i40e_wing, _name, _stat)

/* Stats associated with a Tx ow Wx wing */
static const stwuct i40e_stats i40e_gstwings_queue_stats[] = {
	I40E_QUEUE_STAT("%s-%u.packets", stats.packets),
	I40E_QUEUE_STAT("%s-%u.bytes", stats.bytes),
};

/**
 * i40e_add_one_ethtoow_stat - copy the stat into the suppwied buffew
 * @data: wocation to stowe the stat vawue
 * @pointew: basis fow whewe to copy fwom
 * @stat: the stat definition
 *
 * Copies the stat data defined by the pointew and stat stwuctuwe paiw into
 * the memowy suppwied as data. Used to impwement i40e_add_ethtoow_stats and
 * i40e_add_queue_stats. If the pointew is nuww, data wiww be zewo'd.
 */
static void
i40e_add_one_ethtoow_stat(u64 *data, void *pointew,
			  const stwuct i40e_stats *stat)
{
	chaw *p;

	if (!pointew) {
		/* ensuwe that the ethtoow data buffew is zewo'd fow any stats
		 * which don't have a vawid pointew.
		 */
		*data = 0;
		wetuwn;
	}

	p = (chaw *)pointew + stat->stat_offset;
	switch (stat->sizeof_stat) {
	case sizeof(u64):
		*data = *((u64 *)p);
		bweak;
	case sizeof(u32):
		*data = *((u32 *)p);
		bweak;
	case sizeof(u16):
		*data = *((u16 *)p);
		bweak;
	case sizeof(u8):
		*data = *((u8 *)p);
		bweak;
	defauwt:
		WAWN_ONCE(1, "unexpected stat size fow %s",
			  stat->stat_stwing);
		*data = 0;
	}
}

/**
 * __i40e_add_ethtoow_stats - copy stats into the ethtoow suppwied buffew
 * @data: ethtoow stats buffew
 * @pointew: wocation to copy stats fwom
 * @stats: awway of stats to copy
 * @size: the size of the stats definition
 *
 * Copy the stats defined by the stats awway using the pointew as a base into
 * the data buffew suppwied by ethtoow. Updates the data pointew to point to
 * the next empty wocation fow successive cawws to __i40e_add_ethtoow_stats.
 * If pointew is nuww, set the data vawues to zewo and update the pointew to
 * skip these stats.
 **/
static void
__i40e_add_ethtoow_stats(u64 **data, void *pointew,
			 const stwuct i40e_stats stats[],
			 const unsigned int size)
{
	unsigned int i;

	fow (i = 0; i < size; i++)
		i40e_add_one_ethtoow_stat((*data)++, pointew, &stats[i]);
}

/**
 * i40e_add_ethtoow_stats - copy stats into ethtoow suppwied buffew
 * @data: ethtoow stats buffew
 * @pointew: wocation whewe stats awe stowed
 * @stats: static const awway of stat definitions
 *
 * Macwo to ease the use of __i40e_add_ethtoow_stats by taking a static
 * constant stats awway and passing the AWWAY_SIZE(). This avoids typos by
 * ensuwing that we pass the size associated with the given stats awway.
 *
 * The pawametew @stats is evawuated twice, so pawametews with side effects
 * shouwd be avoided.
 **/
#define i40e_add_ethtoow_stats(data, pointew, stats) \
	__i40e_add_ethtoow_stats(data, pointew, stats, AWWAY_SIZE(stats))

/**
 * i40e_add_queue_stats - copy queue statistics into suppwied buffew
 * @data: ethtoow stats buffew
 * @wing: the wing to copy
 *
 * Queue statistics must be copied whiwe pwotected by
 * u64_stats_fetch_begin, so we can't diwectwy use i40e_add_ethtoow_stats.
 * Assumes that queue stats awe defined in i40e_gstwings_queue_stats. If the
 * wing pointew is nuww, zewo out the queue stat vawues and update the data
 * pointew. Othewwise safewy copy the stats fwom the wing into the suppwied
 * buffew and update the data pointew when finished.
 *
 * This function expects to be cawwed whiwe undew wcu_wead_wock().
 **/
static void
i40e_add_queue_stats(u64 **data, stwuct i40e_wing *wing)
{
	const unsigned int size = AWWAY_SIZE(i40e_gstwings_queue_stats);
	const stwuct i40e_stats *stats = i40e_gstwings_queue_stats;
	unsigned int stawt;
	unsigned int i;

	/* To avoid invawid statistics vawues, ensuwe that we keep wetwying
	 * the copy untiw we get a consistent vawue accowding to
	 * u64_stats_fetch_wetwy. But fiwst, make suwe ouw wing is
	 * non-nuww befowe attempting to access its syncp.
	 */
	do {
		stawt = !wing ? 0 : u64_stats_fetch_begin(&wing->syncp);
		fow (i = 0; i < size; i++) {
			i40e_add_one_ethtoow_stat(&(*data)[i], wing,
						  &stats[i]);
		}
	} whiwe (wing && u64_stats_fetch_wetwy(&wing->syncp, stawt));

	/* Once we successfuwwy copy the stats in, update the data pointew */
	*data += size;
}

/**
 * __i40e_add_stat_stwings - copy stat stwings into ethtoow buffew
 * @p: ethtoow suppwied buffew
 * @stats: stat definitions awway
 * @size: size of the stats awway
 *
 * Fowmat and copy the stwings descwibed by stats into the buffew pointed at
 * by p.
 **/
static void __i40e_add_stat_stwings(u8 **p, const stwuct i40e_stats stats[],
				    const unsigned int size, ...)
{
	unsigned int i;

	fow (i = 0; i < size; i++) {
		va_wist awgs;

		va_stawt(awgs, size);
		vsnpwintf(*p, ETH_GSTWING_WEN, stats[i].stat_stwing, awgs);
		*p += ETH_GSTWING_WEN;
		va_end(awgs);
	}
}

/**
 * i40e_add_stat_stwings - copy stat stwings into ethtoow buffew
 * @p: ethtoow suppwied buffew
 * @stats: stat definitions awway
 *
 * Fowmat and copy the stwings descwibed by the const static stats vawue into
 * the buffew pointed at by p.
 *
 * The pawametew @stats is evawuated twice, so pawametews with side effects
 * shouwd be avoided. Additionawwy, stats must be an awway such that
 * AWWAY_SIZE can be cawwed on it.
 **/
#define i40e_add_stat_stwings(p, stats, ...) \
	__i40e_add_stat_stwings(p, stats, AWWAY_SIZE(stats), ## __VA_AWGS__)

#define I40E_PF_STAT(_name, _stat) \
	I40E_STAT(stwuct i40e_pf, _name, _stat)
#define I40E_VSI_STAT(_name, _stat) \
	I40E_STAT(stwuct i40e_vsi, _name, _stat)
#define I40E_VEB_STAT(_name, _stat) \
	I40E_STAT(stwuct i40e_veb, _name, _stat)
#define I40E_VEB_TC_STAT(_name, _stat) \
	I40E_STAT(stwuct i40e_cp_veb_tc_stats, _name, _stat)
#define I40E_PFC_STAT(_name, _stat) \
	I40E_STAT(stwuct i40e_pfc_stats, _name, _stat)

static const stwuct i40e_stats i40e_gstwings_net_stats[] = {
	I40E_NETDEV_STAT(wx_packets),
	I40E_NETDEV_STAT(tx_packets),
	I40E_NETDEV_STAT(wx_bytes),
	I40E_NETDEV_STAT(tx_bytes),
	I40E_NETDEV_STAT(wx_ewwows),
	I40E_NETDEV_STAT(tx_ewwows),
	I40E_NETDEV_STAT(wx_dwopped),
	I40E_NETDEV_STAT(wx_missed_ewwows),
	I40E_NETDEV_STAT(tx_dwopped),
	I40E_NETDEV_STAT(cowwisions),
	I40E_NETDEV_STAT(wx_wength_ewwows),
	I40E_NETDEV_STAT(wx_cwc_ewwows),
};

static const stwuct i40e_stats i40e_gstwings_veb_stats[] = {
	I40E_VEB_STAT("veb.wx_bytes", stats.wx_bytes),
	I40E_VEB_STAT("veb.tx_bytes", stats.tx_bytes),
	I40E_VEB_STAT("veb.wx_unicast", stats.wx_unicast),
	I40E_VEB_STAT("veb.tx_unicast", stats.tx_unicast),
	I40E_VEB_STAT("veb.wx_muwticast", stats.wx_muwticast),
	I40E_VEB_STAT("veb.tx_muwticast", stats.tx_muwticast),
	I40E_VEB_STAT("veb.wx_bwoadcast", stats.wx_bwoadcast),
	I40E_VEB_STAT("veb.tx_bwoadcast", stats.tx_bwoadcast),
	I40E_VEB_STAT("veb.wx_discawds", stats.wx_discawds),
	I40E_VEB_STAT("veb.tx_discawds", stats.tx_discawds),
	I40E_VEB_STAT("veb.tx_ewwows", stats.tx_ewwows),
	I40E_VEB_STAT("veb.wx_unknown_pwotocow", stats.wx_unknown_pwotocow),
};

stwuct i40e_cp_veb_tc_stats {
	u64 tc_wx_packets;
	u64 tc_wx_bytes;
	u64 tc_tx_packets;
	u64 tc_tx_bytes;
};

static const stwuct i40e_stats i40e_gstwings_veb_tc_stats[] = {
	I40E_VEB_TC_STAT("veb.tc_%u_tx_packets", tc_tx_packets),
	I40E_VEB_TC_STAT("veb.tc_%u_tx_bytes", tc_tx_bytes),
	I40E_VEB_TC_STAT("veb.tc_%u_wx_packets", tc_wx_packets),
	I40E_VEB_TC_STAT("veb.tc_%u_wx_bytes", tc_wx_bytes),
};

static const stwuct i40e_stats i40e_gstwings_misc_stats[] = {
	I40E_VSI_STAT("wx_unicast", eth_stats.wx_unicast),
	I40E_VSI_STAT("tx_unicast", eth_stats.tx_unicast),
	I40E_VSI_STAT("wx_muwticast", eth_stats.wx_muwticast),
	I40E_VSI_STAT("tx_muwticast", eth_stats.tx_muwticast),
	I40E_VSI_STAT("wx_bwoadcast", eth_stats.wx_bwoadcast),
	I40E_VSI_STAT("tx_bwoadcast", eth_stats.tx_bwoadcast),
	I40E_VSI_STAT("wx_unknown_pwotocow", eth_stats.wx_unknown_pwotocow),
	I40E_VSI_STAT("tx_wineawize", tx_wineawize),
	I40E_VSI_STAT("tx_fowce_wb", tx_fowce_wb),
	I40E_VSI_STAT("tx_busy", tx_busy),
	I40E_VSI_STAT("tx_stopped", tx_stopped),
	I40E_VSI_STAT("wx_awwoc_faiw", wx_buf_faiwed),
	I40E_VSI_STAT("wx_pg_awwoc_faiw", wx_page_faiwed),
	I40E_VSI_STAT("wx_cache_weuse", wx_page_weuse),
	I40E_VSI_STAT("wx_cache_awwoc", wx_page_awwoc),
	I40E_VSI_STAT("wx_cache_waive", wx_page_waive),
	I40E_VSI_STAT("wx_cache_busy", wx_page_busy),
	I40E_VSI_STAT("tx_westawt", tx_westawt),
};

/* These PF_STATs might wook wike dupwicates of some NETDEV_STATs,
 * but they awe sepawate.  This device suppowts Viwtuawization, and
 * as such might have sevewaw netdevs suppowting VMDq and FCoE going
 * thwough a singwe powt.  The NETDEV_STATs awe fow individuaw netdevs
 * seen at the top of the stack, and the PF_STATs awe fow the physicaw
 * function at the bottom of the stack hosting those netdevs.
 *
 * The PF_STATs awe appended to the netdev stats onwy when ethtoow -S
 * is quewied on the base PF netdev, not on the VMDq ow FCoE netdev.
 */
static const stwuct i40e_stats i40e_gstwings_stats[] = {
	I40E_PF_STAT("powt.wx_bytes", stats.eth.wx_bytes),
	I40E_PF_STAT("powt.tx_bytes", stats.eth.tx_bytes),
	I40E_PF_STAT("powt.wx_unicast", stats.eth.wx_unicast),
	I40E_PF_STAT("powt.tx_unicast", stats.eth.tx_unicast),
	I40E_PF_STAT("powt.wx_muwticast", stats.eth.wx_muwticast),
	I40E_PF_STAT("powt.tx_muwticast", stats.eth.tx_muwticast),
	I40E_PF_STAT("powt.wx_bwoadcast", stats.eth.wx_bwoadcast),
	I40E_PF_STAT("powt.tx_bwoadcast", stats.eth.tx_bwoadcast),
	I40E_PF_STAT("powt.tx_ewwows", stats.eth.tx_ewwows),
	I40E_PF_STAT("powt.wx_discawds", stats.eth.wx_discawds),
	I40E_PF_STAT("powt.tx_dwopped_wink_down", stats.tx_dwopped_wink_down),
	I40E_PF_STAT("powt.wx_cwc_ewwows", stats.cwc_ewwows),
	I40E_PF_STAT("powt.iwwegaw_bytes", stats.iwwegaw_bytes),
	I40E_PF_STAT("powt.mac_wocaw_fauwts", stats.mac_wocaw_fauwts),
	I40E_PF_STAT("powt.mac_wemote_fauwts", stats.mac_wemote_fauwts),
	I40E_PF_STAT("powt.tx_timeout", tx_timeout_count),
	I40E_PF_STAT("powt.wx_csum_bad", hw_csum_wx_ewwow),
	I40E_PF_STAT("powt.wx_wength_ewwows", stats.wx_wength_ewwows),
	I40E_PF_STAT("powt.wink_xon_wx", stats.wink_xon_wx),
	I40E_PF_STAT("powt.wink_xoff_wx", stats.wink_xoff_wx),
	I40E_PF_STAT("powt.wink_xon_tx", stats.wink_xon_tx),
	I40E_PF_STAT("powt.wink_xoff_tx", stats.wink_xoff_tx),
	I40E_PF_STAT("powt.wx_size_64", stats.wx_size_64),
	I40E_PF_STAT("powt.wx_size_127", stats.wx_size_127),
	I40E_PF_STAT("powt.wx_size_255", stats.wx_size_255),
	I40E_PF_STAT("powt.wx_size_511", stats.wx_size_511),
	I40E_PF_STAT("powt.wx_size_1023", stats.wx_size_1023),
	I40E_PF_STAT("powt.wx_size_1522", stats.wx_size_1522),
	I40E_PF_STAT("powt.wx_size_big", stats.wx_size_big),
	I40E_PF_STAT("powt.tx_size_64", stats.tx_size_64),
	I40E_PF_STAT("powt.tx_size_127", stats.tx_size_127),
	I40E_PF_STAT("powt.tx_size_255", stats.tx_size_255),
	I40E_PF_STAT("powt.tx_size_511", stats.tx_size_511),
	I40E_PF_STAT("powt.tx_size_1023", stats.tx_size_1023),
	I40E_PF_STAT("powt.tx_size_1522", stats.tx_size_1522),
	I40E_PF_STAT("powt.tx_size_big", stats.tx_size_big),
	I40E_PF_STAT("powt.wx_undewsize", stats.wx_undewsize),
	I40E_PF_STAT("powt.wx_fwagments", stats.wx_fwagments),
	I40E_PF_STAT("powt.wx_ovewsize", stats.wx_ovewsize),
	I40E_PF_STAT("powt.wx_jabbew", stats.wx_jabbew),
	I40E_PF_STAT("powt.VF_admin_queue_wequests", vf_aq_wequests),
	I40E_PF_STAT("powt.awq_ovewfwows", awq_ovewfwows),
	I40E_PF_STAT("powt.tx_hwtstamp_timeouts", tx_hwtstamp_timeouts),
	I40E_PF_STAT("powt.wx_hwtstamp_cweawed", wx_hwtstamp_cweawed),
	I40E_PF_STAT("powt.tx_hwtstamp_skipped", tx_hwtstamp_skipped),
	I40E_PF_STAT("powt.fdiw_fwush_cnt", fd_fwush_cnt),
	I40E_PF_STAT("powt.fdiw_atw_match", stats.fd_atw_match),
	I40E_PF_STAT("powt.fdiw_atw_tunnew_match", stats.fd_atw_tunnew_match),
	I40E_PF_STAT("powt.fdiw_atw_status", stats.fd_atw_status),
	I40E_PF_STAT("powt.fdiw_sb_match", stats.fd_sb_match),
	I40E_PF_STAT("powt.fdiw_sb_status", stats.fd_sb_status),

	/* WPI stats */
	I40E_PF_STAT("powt.tx_wpi_status", stats.tx_wpi_status),
	I40E_PF_STAT("powt.wx_wpi_status", stats.wx_wpi_status),
	I40E_PF_STAT("powt.tx_wpi_count", stats.tx_wpi_count),
	I40E_PF_STAT("powt.wx_wpi_count", stats.wx_wpi_count),
};

stwuct i40e_pfc_stats {
	u64 pwiowity_xon_wx;
	u64 pwiowity_xoff_wx;
	u64 pwiowity_xon_tx;
	u64 pwiowity_xoff_tx;
	u64 pwiowity_xon_2_xoff;
};

static const stwuct i40e_stats i40e_gstwings_pfc_stats[] = {
	I40E_PFC_STAT("powt.tx_pwiowity_%u_xon_tx", pwiowity_xon_tx),
	I40E_PFC_STAT("powt.tx_pwiowity_%u_xoff_tx", pwiowity_xoff_tx),
	I40E_PFC_STAT("powt.wx_pwiowity_%u_xon_wx", pwiowity_xon_wx),
	I40E_PFC_STAT("powt.wx_pwiowity_%u_xoff_wx", pwiowity_xoff_wx),
	I40E_PFC_STAT("powt.wx_pwiowity_%u_xon_2_xoff", pwiowity_xon_2_xoff),
};

#define I40E_NETDEV_STATS_WEN	AWWAY_SIZE(i40e_gstwings_net_stats)

#define I40E_MISC_STATS_WEN	AWWAY_SIZE(i40e_gstwings_misc_stats)

#define I40E_VSI_STATS_WEN	(I40E_NETDEV_STATS_WEN + I40E_MISC_STATS_WEN)

#define I40E_PFC_STATS_WEN	(AWWAY_SIZE(i40e_gstwings_pfc_stats) * \
				 I40E_MAX_USEW_PWIOWITY)

#define I40E_VEB_STATS_WEN	(AWWAY_SIZE(i40e_gstwings_veb_stats) + \
				 (AWWAY_SIZE(i40e_gstwings_veb_tc_stats) * \
				  I40E_MAX_TWAFFIC_CWASS))

#define I40E_GWOBAW_STATS_WEN	AWWAY_SIZE(i40e_gstwings_stats)

#define I40E_PF_STATS_WEN	(I40E_GWOBAW_STATS_WEN + \
				 I40E_PFC_STATS_WEN + \
				 I40E_VEB_STATS_WEN + \
				 I40E_VSI_STATS_WEN)

/* Wength of stats fow a singwe queue */
#define I40E_QUEUE_STATS_WEN	AWWAY_SIZE(i40e_gstwings_queue_stats)

enum i40e_ethtoow_test_id {
	I40E_ETH_TEST_WEG = 0,
	I40E_ETH_TEST_EEPWOM,
	I40E_ETH_TEST_INTW,
	I40E_ETH_TEST_WINK,
};

static const chaw i40e_gstwings_test[][ETH_GSTWING_WEN] = {
	"Wegistew test  (offwine)",
	"Eepwom test    (offwine)",
	"Intewwupt test (offwine)",
	"Wink test   (on/offwine)"
};

#define I40E_TEST_WEN (sizeof(i40e_gstwings_test) / ETH_GSTWING_WEN)

stwuct i40e_pwiv_fwags {
	chaw fwag_stwing[ETH_GSTWING_WEN];
	u8 bitno;
	boow wead_onwy;
};

#define I40E_PWIV_FWAG(_name, _bitno, _wead_onwy) { \
	.fwag_stwing = _name, \
	.bitno = _bitno, \
	.wead_onwy = _wead_onwy, \
}

static const stwuct i40e_pwiv_fwags i40e_gstwings_pwiv_fwags[] = {
	/* NOTE: MFP setting cannot be changed */
	I40E_PWIV_FWAG("MFP", I40E_FWAG_MFP_ENA, 1),
	I40E_PWIV_FWAG("totaw-powt-shutdown",
		       I40E_FWAG_TOTAW_POWT_SHUTDOWN_ENA, 1),
	I40E_PWIV_FWAG("WinkPowwing", I40E_FWAG_WINK_POWWING_ENA, 0),
	I40E_PWIV_FWAG("fwow-diwectow-atw", I40E_FWAG_FD_ATW_ENA, 0),
	I40E_PWIV_FWAG("veb-stats", I40E_FWAG_VEB_STATS_ENA, 0),
	I40E_PWIV_FWAG("hw-atw-eviction", I40E_FWAG_HW_ATW_EVICT_ENA, 0),
	I40E_PWIV_FWAG("wink-down-on-cwose",
		       I40E_FWAG_WINK_DOWN_ON_CWOSE_ENA, 0),
	I40E_PWIV_FWAG("wegacy-wx", I40E_FWAG_WEGACY_WX_ENA, 0),
	I40E_PWIV_FWAG("disabwe-souwce-pwuning",
		       I40E_FWAG_SOUWCE_PWUNING_DIS, 0),
	I40E_PWIV_FWAG("disabwe-fw-wwdp", I40E_FWAG_FW_WWDP_DIS, 0),
	I40E_PWIV_FWAG("ws-fec", I40E_FWAG_WS_FEC, 0),
	I40E_PWIV_FWAG("base-w-fec", I40E_FWAG_BASE_W_FEC, 0),
	I40E_PWIV_FWAG("vf-vwan-pwuning",
		       I40E_FWAG_VF_VWAN_PWUNING_ENA, 0),
};

#define I40E_PWIV_FWAGS_STW_WEN AWWAY_SIZE(i40e_gstwings_pwiv_fwags)

/* Pwivate fwags with a gwobaw effect, westwicted to PF 0 */
static const stwuct i40e_pwiv_fwags i40e_gw_gstwings_pwiv_fwags[] = {
	I40E_PWIV_FWAG("vf-twue-pwomisc-suppowt",
		       I40E_FWAG_TWUE_PWOMISC_ENA, 0),
};

#define I40E_GW_PWIV_FWAGS_STW_WEN AWWAY_SIZE(i40e_gw_gstwings_pwiv_fwags)

/**
 * i40e_pawtition_setting_compwaint - genewic compwaint fow MFP westwiction
 * @pf: the PF stwuct
 **/
static void i40e_pawtition_setting_compwaint(stwuct i40e_pf *pf)
{
	dev_info(&pf->pdev->dev,
		 "The wink settings awe awwowed to be changed onwy fwom the fiwst pawtition of a given powt. Pwease switch to the fiwst pawtition in owdew to change the setting.\n");
}

/**
 * i40e_phy_type_to_ethtoow - convewt the phy_types to ethtoow wink modes
 * @pf: PF stwuct with phy_types
 * @ks: ethtoow wink ksettings stwuct to fiww out
 *
 **/
static void i40e_phy_type_to_ethtoow(stwuct i40e_pf *pf,
				     stwuct ethtoow_wink_ksettings *ks)
{
	stwuct i40e_wink_status *hw_wink_info = &pf->hw.phy.wink_info;
	u64 phy_types = pf->hw.phy.phy_types;

	ethtoow_wink_ksettings_zewo_wink_mode(ks, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(ks, advewtising);

	if (phy_types & I40E_CAP_PHY_TYPE_SGMII) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_1GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     1000baseT_Fuww);
		if (test_bit(I40E_HW_CAP_100M_SGMII, pf->hw.caps)) {
			ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
							     100baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     100baseT_Fuww);
		}
	}
	if (phy_types & I40E_CAP_PHY_TYPE_XAUI ||
	    phy_types & I40E_CAP_PHY_TYPE_XFI ||
	    phy_types & I40E_CAP_PHY_TYPE_SFI ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_SFPP_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_AOC) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseT_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_10GBASE_T) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseT_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_2_5GBASE_T) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     2500baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_2_5GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     2500baseT_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_5GBASE_T) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     5000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_5GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     5000baseT_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_XWAUI ||
	    phy_types & I40E_CAP_PHY_TYPE_XWPPI ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_AOC)
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseCW4_Fuww);
	if (phy_types & I40E_CAP_PHY_TYPE_40GBASE_CW4_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_CW4) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseCW4_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_40GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     40000baseCW4_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_100BASE_TX) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     100baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_100MB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     100baseT_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_1000BASE_T) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_1GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     1000baseT_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_40GBASE_SW4) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseSW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseSW4_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_40GBASE_WW4) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseWW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseWW4_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_40GBASE_KW4) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseKW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseKW4_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_20GBASE_KW2) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     20000baseKW2_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_20GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     20000baseKW2_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_10GBASE_KX4) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseKX4_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseKX4_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_10GBASE_KW &&
	    !test_bit(I40E_HW_CAP_CWT_WETIMEW, pf->hw.caps)) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseKW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseKW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_1000BASE_KX &&
	    !test_bit(I40E_HW_CAP_CWT_WETIMEW, pf->hw.caps)) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseKX_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_1GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     1000baseKX_Fuww);
	}
	/* need to add 25G PHY types */
	if (phy_types & I40E_CAP_PHY_TYPE_25GBASE_KW) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseKW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_25GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     25000baseKW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_25GBASE_CW) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseCW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_25GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     25000baseCW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_25GBASE_SW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_WW) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseSW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_25GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     25000baseSW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_25GBASE_AOC ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_ACC) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseCW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_25GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     25000baseCW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_25GBASE_KW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_CW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_SW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_WW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_AOC ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_ACC) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_NONE);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_WS);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_BASEW);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_25GB) {
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     FEC_NONE);
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     FEC_WS);
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     FEC_BASEW);
		}
	}
	/* need to add new 10G PHY types */
	if (phy_types & I40E_CAP_PHY_TYPE_10GBASE_CW1 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_CW1_CU) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseCW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseCW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_10GBASE_SW) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseSW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseSW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_10GBASE_WW) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseWW_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseWW_Fuww);
	}
	if (phy_types & I40E_CAP_PHY_TYPE_1000BASE_SX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_WX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_T_OPTICAW) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseX_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_1GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     1000baseX_Fuww);
	}
	/* Autoneg PHY types */
	if (phy_types & I40E_CAP_PHY_TYPE_SGMII ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_KW4 ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_CW4_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_40GBASE_CW4 ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_SW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_WW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_KW ||
	    phy_types & I40E_CAP_PHY_TYPE_25GBASE_CW ||
	    phy_types & I40E_CAP_PHY_TYPE_20GBASE_KW2 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_SW ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_WW ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_KX4 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_KW ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_CW1_CU ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_CW1 ||
	    phy_types & I40E_CAP_PHY_TYPE_10GBASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_5GBASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_2_5GBASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_T_OPTICAW ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_T ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_SX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_WX ||
	    phy_types & I40E_CAP_PHY_TYPE_1000BASE_KX ||
	    phy_types & I40E_CAP_PHY_TYPE_100BASE_TX) {
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     Autoneg);
	}
}

/**
 * i40e_get_settings_wink_up_fec - Get the FEC mode encoding fwom mask
 * @weq_fec_info: mask wequest FEC info
 * @ks: ethtoow ksettings to fiww in
 **/
static void i40e_get_settings_wink_up_fec(u8 weq_fec_info,
					  stwuct ethtoow_wink_ksettings *ks)
{
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_NONE);
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_WS);
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FEC_BASEW);

	if ((I40E_AQ_SET_FEC_WEQUEST_WS & weq_fec_info) &&
	    (I40E_AQ_SET_FEC_WEQUEST_KW & weq_fec_info)) {
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     FEC_NONE);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     FEC_BASEW);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, FEC_WS);
	} ewse if (I40E_AQ_SET_FEC_WEQUEST_WS & weq_fec_info) {
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, FEC_WS);
	} ewse if (I40E_AQ_SET_FEC_WEQUEST_KW & weq_fec_info) {
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     FEC_BASEW);
	} ewse {
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     FEC_NONE);
	}
}

/**
 * i40e_get_settings_wink_up - Get the Wink settings fow when wink is up
 * @hw: hw stwuctuwe
 * @ks: ethtoow ksettings to fiww in
 * @netdev: netwowk intewface device stwuctuwe
 * @pf: pointew to physicaw function stwuct
 **/
static void i40e_get_settings_wink_up(stwuct i40e_hw *hw,
				      stwuct ethtoow_wink_ksettings *ks,
				      stwuct net_device *netdev,
				      stwuct i40e_pf *pf)
{
	stwuct i40e_wink_status *hw_wink_info = &hw->phy.wink_info;
	stwuct ethtoow_wink_ksettings cap_ksettings;
	u32 wink_speed = hw_wink_info->wink_speed;

	/* Initiawize suppowted and advewtised settings based on phy settings */
	switch (hw_wink_info->phy_type) {
	case I40E_PHY_TYPE_40GBASE_CW4:
	case I40E_PHY_TYPE_40GBASE_CW4_CU:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseCW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseCW4_Fuww);
		bweak;
	case I40E_PHY_TYPE_XWAUI:
	case I40E_PHY_TYPE_XWPPI:
	case I40E_PHY_TYPE_40GBASE_AOC:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseCW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseCW4_Fuww);
		bweak;
	case I40E_PHY_TYPE_40GBASE_SW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseSW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseSW4_Fuww);
		bweak;
	case I40E_PHY_TYPE_40GBASE_WW4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseWW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseWW4_Fuww);
		bweak;
	case I40E_PHY_TYPE_25GBASE_SW:
	case I40E_PHY_TYPE_25GBASE_WW:
	case I40E_PHY_TYPE_10GBASE_SW:
	case I40E_PHY_TYPE_10GBASE_WW:
	case I40E_PHY_TYPE_1000BASE_SX:
	case I40E_PHY_TYPE_1000BASE_WX:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseSW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     25000baseSW_Fuww);
		i40e_get_settings_wink_up_fec(hw_wink_info->weq_fec_info, ks);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseSW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     10000baseSW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseWW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     10000baseWW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseX_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     1000baseX_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		if (hw_wink_info->moduwe_type[2] &
		    I40E_MODUWE_TYPE_1000BASE_SX ||
		    hw_wink_info->moduwe_type[2] &
		    I40E_MODUWE_TYPE_1000BASE_WX) {
			ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
							     1000baseT_Fuww);
			if (hw_wink_info->wequested_speeds &
			    I40E_WINK_SPEED_1GB)
				ethtoow_wink_ksettings_add_wink_mode(
				     ks, advewtising, 1000baseT_Fuww);
		}
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseT_Fuww);
		bweak;
	case I40E_PHY_TYPE_10GBASE_T:
	case I40E_PHY_TYPE_5GBASE_T_WINK_STATUS:
	case I40E_PHY_TYPE_2_5GBASE_T_WINK_STATUS:
	case I40E_PHY_TYPE_1000BASE_T:
	case I40E_PHY_TYPE_100BASE_TX:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     5000baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     2500baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     100baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_5GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     5000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_2_5GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     2500baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_1GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     1000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_100MB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     100baseT_Fuww);
		bweak;
	case I40E_PHY_TYPE_1000BASE_T_OPTICAW:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     1000baseT_Fuww);
		bweak;
	case I40E_PHY_TYPE_10GBASE_CW1_CU:
	case I40E_PHY_TYPE_10GBASE_CW1:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     10000baseT_Fuww);
		bweak;
	case I40E_PHY_TYPE_XAUI:
	case I40E_PHY_TYPE_XFI:
	case I40E_PHY_TYPE_SFI:
	case I40E_PHY_TYPE_10GBASE_SFPP_CU:
	case I40E_PHY_TYPE_10GBASE_AOC:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_10GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     10000baseT_Fuww);
		i40e_get_settings_wink_up_fec(hw_wink_info->weq_fec_info, ks);
		bweak;
	case I40E_PHY_TYPE_SGMII:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseT_Fuww);
		if (hw_wink_info->wequested_speeds & I40E_WINK_SPEED_1GB)
			ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
							     1000baseT_Fuww);
		if (test_bit(I40E_HW_CAP_100M_SGMII, pf->hw.caps)) {
			ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
							     100baseT_Fuww);
			if (hw_wink_info->wequested_speeds &
			    I40E_WINK_SPEED_100MB)
				ethtoow_wink_ksettings_add_wink_mode(
				      ks, advewtising, 100baseT_Fuww);
		}
		bweak;
	case I40E_PHY_TYPE_40GBASE_KW4:
	case I40E_PHY_TYPE_25GBASE_KW:
	case I40E_PHY_TYPE_20GBASE_KW2:
	case I40E_PHY_TYPE_10GBASE_KW:
	case I40E_PHY_TYPE_10GBASE_KX4:
	case I40E_PHY_TYPE_1000BASE_KX:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     40000baseKW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseKW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     20000baseKW2_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseKW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseKX4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     1000baseKX_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     40000baseKW4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     25000baseKW_Fuww);
		i40e_get_settings_wink_up_fec(hw_wink_info->weq_fec_info, ks);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     20000baseKW2_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     10000baseKW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     10000baseKX4_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     1000baseKX_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		bweak;
	case I40E_PHY_TYPE_25GBASE_CW:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseCW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     25000baseCW_Fuww);
		i40e_get_settings_wink_up_fec(hw_wink_info->weq_fec_info, ks);

		bweak;
	case I40E_PHY_TYPE_25GBASE_AOC:
	case I40E_PHY_TYPE_25GBASE_ACC:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     25000baseCW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     25000baseCW_Fuww);
		i40e_get_settings_wink_up_fec(hw_wink_info->weq_fec_info, ks);

		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted,
						     10000baseCW_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     10000baseCW_Fuww);
		bweak;
	defauwt:
		/* if we got hewe and wink is up something bad is afoot */
		netdev_info(netdev,
			    "WAWNING: Wink is up but PHY type 0x%x is not wecognized, ow incowwect cabwe is in use\n",
			    hw_wink_info->phy_type);
	}

	/* Now that we've wowked out evewything that couwd be suppowted by the
	 * cuwwent PHY type, get what is suppowted by the NVM and intewsect
	 * them to get what is twuwy suppowted
	 */
	memset(&cap_ksettings, 0, sizeof(stwuct ethtoow_wink_ksettings));
	i40e_phy_type_to_ethtoow(pf, &cap_ksettings);
	ethtoow_intewsect_wink_masks(ks, &cap_ksettings);

	/* Set speed and dupwex */
	switch (wink_speed) {
	case I40E_WINK_SPEED_40GB:
		ks->base.speed = SPEED_40000;
		bweak;
	case I40E_WINK_SPEED_25GB:
		ks->base.speed = SPEED_25000;
		bweak;
	case I40E_WINK_SPEED_20GB:
		ks->base.speed = SPEED_20000;
		bweak;
	case I40E_WINK_SPEED_10GB:
		ks->base.speed = SPEED_10000;
		bweak;
	case I40E_WINK_SPEED_5GB:
		ks->base.speed = SPEED_5000;
		bweak;
	case I40E_WINK_SPEED_2_5GB:
		ks->base.speed = SPEED_2500;
		bweak;
	case I40E_WINK_SPEED_1GB:
		ks->base.speed = SPEED_1000;
		bweak;
	case I40E_WINK_SPEED_100MB:
		ks->base.speed = SPEED_100;
		bweak;
	defauwt:
		ks->base.speed = SPEED_UNKNOWN;
		bweak;
	}
	ks->base.dupwex = DUPWEX_FUWW;
}

/**
 * i40e_get_settings_wink_down - Get the Wink settings fow when wink is down
 * @hw: hw stwuctuwe
 * @ks: ethtoow ksettings to fiww in
 * @pf: pointew to physicaw function stwuct
 *
 * Wepowts wink settings that can be detewmined when wink is down
 **/
static void i40e_get_settings_wink_down(stwuct i40e_hw *hw,
					stwuct ethtoow_wink_ksettings *ks,
					stwuct i40e_pf *pf)
{
	/* wink is down and the dwivew needs to faww back on
	 * suppowted phy types to figuwe out what info to dispway
	 */
	i40e_phy_type_to_ethtoow(pf, ks);

	/* With no wink speed and dupwex awe unknown */
	ks->base.speed = SPEED_UNKNOWN;
	ks->base.dupwex = DUPWEX_UNKNOWN;
}

/**
 * i40e_get_wink_ksettings - Get Wink Speed and Dupwex settings
 * @netdev: netwowk intewface device stwuctuwe
 * @ks: ethtoow ksettings
 *
 * Wepowts speed/dupwex settings based on media_type
 **/
static int i40e_get_wink_ksettings(stwuct net_device *netdev,
				   stwuct ethtoow_wink_ksettings *ks)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	stwuct i40e_wink_status *hw_wink_info = &hw->phy.wink_info;
	boow wink_up = hw_wink_info->wink_info & I40E_AQ_WINK_UP;

	ethtoow_wink_ksettings_zewo_wink_mode(ks, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(ks, advewtising);

	if (wink_up)
		i40e_get_settings_wink_up(hw, ks, netdev, pf);
	ewse
		i40e_get_settings_wink_down(hw, ks, pf);

	/* Now set the settings that don't wewy on wink being up/down */
	/* Set autoneg settings */
	ks->base.autoneg = ((hw_wink_info->an_info & I40E_AQ_AN_COMPWETED) ?
			    AUTONEG_ENABWE : AUTONEG_DISABWE);

	/* Set media type settings */
	switch (hw->phy.media_type) {
	case I40E_MEDIA_TYPE_BACKPWANE:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Backpwane);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Autoneg);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     Backpwane);
		ks->base.powt = POWT_NONE;
		bweak;
	case I40E_MEDIA_TYPE_BASET:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, TP);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, TP);
		ks->base.powt = POWT_TP;
		bweak;
	case I40E_MEDIA_TYPE_DA:
	case I40E_MEDIA_TYPE_CX4:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FIBWE);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, FIBWE);
		ks->base.powt = POWT_DA;
		bweak;
	case I40E_MEDIA_TYPE_FIBEW:
		ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, FIBWE);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, FIBWE);
		ks->base.powt = POWT_FIBWE;
		bweak;
	case I40E_MEDIA_TYPE_UNKNOWN:
	defauwt:
		ks->base.powt = POWT_OTHEW;
		bweak;
	}

	/* Set fwow contwow settings */
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Pause);
	ethtoow_wink_ksettings_add_wink_mode(ks, suppowted, Asym_Pause);

	switch (hw->fc.wequested_mode) {
	case I40E_FC_FUWW:
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Pause);
		bweak;
	case I40E_FC_TX_PAUSE:
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     Asym_Pause);
		bweak;
	case I40E_FC_WX_PAUSE:
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising, Pause);
		ethtoow_wink_ksettings_add_wink_mode(ks, advewtising,
						     Asym_Pause);
		bweak;
	defauwt:
		ethtoow_wink_ksettings_dew_wink_mode(ks, advewtising, Pause);
		ethtoow_wink_ksettings_dew_wink_mode(ks, advewtising,
						     Asym_Pause);
		bweak;
	}

	wetuwn 0;
}

#define I40E_WBIT_SIZE 8
/**
 * i40e_speed_to_wink_speed - Twanswate decimaw speed to i40e_aq_wink_speed
 * @speed: speed in decimaw
 * @ks: ethtoow ksettings
 *
 * Wetuwn i40e_aq_wink_speed based on speed
 **/
static enum i40e_aq_wink_speed
i40e_speed_to_wink_speed(__u32 speed, const stwuct ethtoow_wink_ksettings *ks)
{
	enum i40e_aq_wink_speed wink_speed = I40E_WINK_SPEED_UNKNOWN;
	boow speed_changed = fawse;
	int i, j;

	static const stwuct {
		__u32 speed;
		enum i40e_aq_wink_speed wink_speed;
		__u8 bit[I40E_WBIT_SIZE];
	} i40e_speed_wut[] = {
#define I40E_WBIT(mode) ETHTOOW_WINK_MODE_ ## mode ##_Fuww_BIT
		{SPEED_100, I40E_WINK_SPEED_100MB, {I40E_WBIT(100baseT)} },
		{SPEED_1000, I40E_WINK_SPEED_1GB,
		 {I40E_WBIT(1000baseT), I40E_WBIT(1000baseX),
		  I40E_WBIT(1000baseKX)} },
		{SPEED_10000, I40E_WINK_SPEED_10GB,
		 {I40E_WBIT(10000baseT), I40E_WBIT(10000baseKW),
		  I40E_WBIT(10000baseWW), I40E_WBIT(10000baseCW),
		  I40E_WBIT(10000baseSW), I40E_WBIT(10000baseKX4)} },

		{SPEED_25000, I40E_WINK_SPEED_25GB,
		 {I40E_WBIT(25000baseCW), I40E_WBIT(25000baseKW),
		  I40E_WBIT(25000baseSW)} },
		{SPEED_40000, I40E_WINK_SPEED_40GB,
		 {I40E_WBIT(40000baseKW4), I40E_WBIT(40000baseCW4),
		  I40E_WBIT(40000baseSW4), I40E_WBIT(40000baseWW4)} },
		{SPEED_20000, I40E_WINK_SPEED_20GB,
		 {I40E_WBIT(20000baseKW2)} },
		{SPEED_2500, I40E_WINK_SPEED_2_5GB, {I40E_WBIT(2500baseT)} },
		{SPEED_5000, I40E_WINK_SPEED_5GB, {I40E_WBIT(2500baseT)} }
#undef I40E_WBIT
};

	fow (i = 0; i < AWWAY_SIZE(i40e_speed_wut); i++) {
		if (i40e_speed_wut[i].speed == speed) {
			fow (j = 0; j < I40E_WBIT_SIZE; j++) {
				if (test_bit(i40e_speed_wut[i].bit[j],
					     ks->wink_modes.suppowted)) {
					speed_changed = twue;
					bweak;
				}
				if (!i40e_speed_wut[i].bit[j])
					bweak;
			}
			if (speed_changed) {
				wink_speed = i40e_speed_wut[i].wink_speed;
				bweak;
			}
		}
	}
	wetuwn wink_speed;
}

#undef I40E_WBIT_SIZE

/**
 * i40e_set_wink_ksettings - Set Speed and Dupwex
 * @netdev: netwowk intewface device stwuctuwe
 * @ks: ethtoow ksettings
 *
 * Set speed/dupwex pew media_types advewtised/fowced
 **/
static int i40e_set_wink_ksettings(stwuct net_device *netdev,
				   const stwuct ethtoow_wink_ksettings *ks)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_aq_get_phy_abiwities_wesp abiwities;
	stwuct ethtoow_wink_ksettings safe_ks;
	stwuct ethtoow_wink_ksettings copy_ks;
	stwuct i40e_aq_set_phy_config config;
	stwuct i40e_pf *pf = np->vsi->back;
	enum i40e_aq_wink_speed wink_speed;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_hw *hw = &pf->hw;
	boow autoneg_changed = fawse;
	int timeout = 50;
	int status = 0;
	int eww = 0;
	__u32 speed;
	u8 autoneg;

	/* Changing powt settings is not suppowted if this isn't the
	 * powt's contwowwing PF
	 */
	if (hw->pawtition_id != 1) {
		i40e_pawtition_setting_compwaint(pf);
		wetuwn -EOPNOTSUPP;
	}
	if (vsi != pf->vsi[pf->wan_vsi])
		wetuwn -EOPNOTSUPP;
	if (hw->phy.media_type != I40E_MEDIA_TYPE_BASET &&
	    hw->phy.media_type != I40E_MEDIA_TYPE_FIBEW &&
	    hw->phy.media_type != I40E_MEDIA_TYPE_BACKPWANE &&
	    hw->phy.media_type != I40E_MEDIA_TYPE_DA &&
	    hw->phy.wink_info.wink_info & I40E_AQ_WINK_UP)
		wetuwn -EOPNOTSUPP;
	if (hw->device_id == I40E_DEV_ID_KX_B ||
	    hw->device_id == I40E_DEV_ID_KX_C ||
	    hw->device_id == I40E_DEV_ID_20G_KW2 ||
	    hw->device_id == I40E_DEV_ID_20G_KW2_A ||
	    hw->device_id == I40E_DEV_ID_25G_B ||
	    hw->device_id == I40E_DEV_ID_KX_X722) {
		netdev_info(netdev, "Changing settings is not suppowted on backpwane.\n");
		wetuwn -EOPNOTSUPP;
	}

	/* copy the ksettings to copy_ks to avoid modifying the owigin */
	memcpy(&copy_ks, ks, sizeof(stwuct ethtoow_wink_ksettings));

	/* save autoneg out of ksettings */
	autoneg = copy_ks.base.autoneg;
	speed = copy_ks.base.speed;

	/* get ouw own copy of the bits to check against */
	memset(&safe_ks, 0, sizeof(stwuct ethtoow_wink_ksettings));
	safe_ks.base.cmd = copy_ks.base.cmd;
	safe_ks.base.wink_mode_masks_nwowds =
		copy_ks.base.wink_mode_masks_nwowds;
	i40e_get_wink_ksettings(netdev, &safe_ks);

	/* Get wink modes suppowted by hawdwawe and check against modes
	 * wequested by the usew.  Wetuwn an ewwow if unsuppowted mode was set.
	 */
	if (!bitmap_subset(copy_ks.wink_modes.advewtising,
			   safe_ks.wink_modes.suppowted,
			   __ETHTOOW_WINK_MODE_MASK_NBITS))
		wetuwn -EINVAW;

	/* set autoneg back to what it cuwwentwy is */
	copy_ks.base.autoneg = safe_ks.base.autoneg;
	copy_ks.base.speed  = safe_ks.base.speed;

	/* If copy_ks.base and safe_ks.base awe not the same now, then they awe
	 * twying to set something that we do not suppowt.
	 */
	if (memcmp(&copy_ks.base, &safe_ks.base,
		   sizeof(stwuct ethtoow_wink_settings))) {
		netdev_eww(netdev, "Onwy speed and autoneg awe suppowted.\n");
		wetuwn -EOPNOTSUPP;
	}

	whiwe (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state)) {
		timeout--;
		if (!timeout)
			wetuwn -EBUSY;
		usweep_wange(1000, 2000);
	}

	/* Get the cuwwent phy config */
	status = i40e_aq_get_phy_capabiwities(hw, fawse, fawse, &abiwities,
					      NUWW);
	if (status) {
		eww = -EAGAIN;
		goto done;
	}

	/* Copy abiwities to config in case autoneg is not
	 * set bewow
	 */
	memset(&config, 0, sizeof(stwuct i40e_aq_set_phy_config));
	config.abiwities = abiwities.abiwities;

	/* Check autoneg */
	if (autoneg == AUTONEG_ENABWE) {
		/* If autoneg was not awweady enabwed */
		if (!(hw->phy.wink_info.an_info & I40E_AQ_AN_COMPWETED)) {
			/* If autoneg is not suppowted, wetuwn ewwow */
			if (!ethtoow_wink_ksettings_test_wink_mode(&safe_ks,
								   suppowted,
								   Autoneg)) {
				netdev_info(netdev, "Autoneg not suppowted on this phy\n");
				eww = -EINVAW;
				goto done;
			}
			/* Autoneg is awwowed to change */
			config.abiwities = abiwities.abiwities |
					   I40E_AQ_PHY_ENABWE_AN;
			autoneg_changed = twue;
		}
	} ewse {
		/* If autoneg is cuwwentwy enabwed */
		if (hw->phy.wink_info.an_info & I40E_AQ_AN_COMPWETED) {
			/* If autoneg is suppowted 10GBASE_T is the onwy PHY
			 * that can disabwe it, so othewwise wetuwn ewwow
			 */
			if (ethtoow_wink_ksettings_test_wink_mode(&safe_ks,
								  suppowted,
								  Autoneg) &&
			    hw->phy.media_type != I40E_MEDIA_TYPE_BASET) {
				netdev_info(netdev, "Autoneg cannot be disabwed on this phy\n");
				eww = -EINVAW;
				goto done;
			}
			/* Autoneg is awwowed to change */
			config.abiwities = abiwities.abiwities &
					   ~I40E_AQ_PHY_ENABWE_AN;
			autoneg_changed = twue;
		}
	}

	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  100baseT_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_100MB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  1000baseT_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  1000baseX_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  1000baseKX_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_1GB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  10000baseT_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  10000baseKX4_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  10000baseKW_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  10000baseCW_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  10000baseSW_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  10000baseWW_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_10GB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  2500baseT_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_2_5GB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  5000baseT_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_5GB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  20000baseKW2_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_20GB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  25000baseCW_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  25000baseKW_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  25000baseSW_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_25GB;
	if (ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  40000baseKW4_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  40000baseCW4_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  40000baseSW4_Fuww) ||
	    ethtoow_wink_ksettings_test_wink_mode(ks, advewtising,
						  40000baseWW4_Fuww))
		config.wink_speed |= I40E_WINK_SPEED_40GB;

	/* Autonegotiation must be disabwed to change speed */
	if ((speed != SPEED_UNKNOWN && safe_ks.base.speed != speed) &&
	    (autoneg == AUTONEG_DISABWE ||
	    (safe_ks.base.autoneg == AUTONEG_DISABWE && !autoneg_changed))) {
		wink_speed = i40e_speed_to_wink_speed(speed, ks);
		if (wink_speed == I40E_WINK_SPEED_UNKNOWN) {
			netdev_info(netdev, "Given speed is not suppowted\n");
			eww = -EOPNOTSUPP;
			goto done;
		} ewse {
			config.wink_speed = wink_speed;
		}
	} ewse {
		if (safe_ks.base.speed != speed) {
			netdev_info(netdev,
				    "Unabwe to set speed, disabwe autoneg\n");
			eww = -EOPNOTSUPP;
			goto done;
		}
	}

	/* If speed didn't get set, set it to what it cuwwentwy is.
	 * This is needed because if advewtise is 0 (as it is when autoneg
	 * is disabwed) then speed won't get set.
	 */
	if (!config.wink_speed)
		config.wink_speed = abiwities.wink_speed;
	if (autoneg_changed || abiwities.wink_speed != config.wink_speed) {
		/* copy ovew the west of the abiwities */
		config.phy_type = abiwities.phy_type;
		config.phy_type_ext = abiwities.phy_type_ext;
		config.eee_capabiwity = abiwities.eee_capabiwity;
		config.eeew = abiwities.eeew_vaw;
		config.wow_powew_ctww = abiwities.d3_wpan;
		config.fec_config = abiwities.fec_cfg_cuww_mod_ext_info &
				    I40E_AQ_PHY_FEC_CONFIG_MASK;

		/* save the wequested speeds */
		hw->phy.wink_info.wequested_speeds = config.wink_speed;
		/* set wink and auto negotiation so changes take effect */
		config.abiwities |= I40E_AQ_PHY_ENABWE_ATOMIC_WINK;
		/* If wink is up put wink down */
		if (hw->phy.wink_info.wink_info & I40E_AQ_WINK_UP) {
			/* Teww the OS wink is going down, the wink wiww go
			 * back up when fw says it is weady asynchwonouswy
			 */
			i40e_pwint_wink_message(vsi, fawse);
			netif_cawwiew_off(netdev);
			netif_tx_stop_aww_queues(netdev);
		}

		/* make the aq caww */
		status = i40e_aq_set_phy_config(hw, &config, NUWW);
		if (status) {
			netdev_info(netdev,
				    "Set phy config faiwed, eww %pe aq_eww %s\n",
				    EWW_PTW(status),
				    i40e_aq_stw(hw, hw->aq.asq_wast_status));
			eww = -EAGAIN;
			goto done;
		}

		status = i40e_update_wink_info(hw);
		if (status)
			netdev_dbg(netdev,
				   "Updating wink info faiwed with eww %pe aq_eww %s\n",
				   EWW_PTW(status),
				   i40e_aq_stw(hw, hw->aq.asq_wast_status));

	} ewse {
		netdev_info(netdev, "Nothing changed, exiting without setting anything.\n");
	}

done:
	cweaw_bit(__I40E_CONFIG_BUSY, pf->state);

	wetuwn eww;
}

static int i40e_set_fec_cfg(stwuct net_device *netdev, u8 fec_cfg)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_aq_get_phy_abiwities_wesp abiwities;
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	int status = 0;
	int eww = 0;

	/* Get the cuwwent phy config */
	memset(&abiwities, 0, sizeof(abiwities));
	status = i40e_aq_get_phy_capabiwities(hw, fawse, fawse, &abiwities,
					      NUWW);
	if (status) {
		eww = -EAGAIN;
		goto done;
	}

	if (abiwities.fec_cfg_cuww_mod_ext_info != fec_cfg) {
		stwuct i40e_aq_set_phy_config config;

		memset(&config, 0, sizeof(config));
		config.phy_type = abiwities.phy_type;
		config.abiwities = abiwities.abiwities |
				   I40E_AQ_PHY_ENABWE_ATOMIC_WINK;
		config.phy_type_ext = abiwities.phy_type_ext;
		config.wink_speed = abiwities.wink_speed;
		config.eee_capabiwity = abiwities.eee_capabiwity;
		config.eeew = abiwities.eeew_vaw;
		config.wow_powew_ctww = abiwities.d3_wpan;
		config.fec_config = fec_cfg & I40E_AQ_PHY_FEC_CONFIG_MASK;
		status = i40e_aq_set_phy_config(hw, &config, NUWW);
		if (status) {
			netdev_info(netdev,
				    "Set phy config faiwed, eww %pe aq_eww %s\n",
				    EWW_PTW(status),
				    i40e_aq_stw(hw, hw->aq.asq_wast_status));
			eww = -EAGAIN;
			goto done;
		}
		i40e_set_fec_in_fwags(fec_cfg, pf->fwags);
		status = i40e_update_wink_info(hw);
		if (status)
			/* debug wevew message onwy due to wewation to the wink
			 * itsewf wathew than to the FEC settings
			 * (e.g. no physicaw connection etc.)
			 */
			netdev_dbg(netdev,
				   "Updating wink info faiwed with eww %pe aq_eww %s\n",
				   EWW_PTW(status),
				   i40e_aq_stw(hw, hw->aq.asq_wast_status));
	}

done:
	wetuwn eww;
}

static int i40e_get_fec_pawam(stwuct net_device *netdev,
			      stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_aq_get_phy_abiwities_wesp abiwities;
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	int status = 0;
	int eww = 0;
	u8 fec_cfg;

	/* Get the cuwwent phy config */
	memset(&abiwities, 0, sizeof(abiwities));
	status = i40e_aq_get_phy_capabiwities(hw, fawse, fawse, &abiwities,
					      NUWW);
	if (status) {
		eww = -EAGAIN;
		goto done;
	}

	fecpawam->fec = 0;
	fec_cfg = abiwities.fec_cfg_cuww_mod_ext_info;
	if (fec_cfg & I40E_AQ_SET_FEC_AUTO)
		fecpawam->fec |= ETHTOOW_FEC_AUTO;
	ewse if (fec_cfg & (I40E_AQ_SET_FEC_WEQUEST_WS |
		 I40E_AQ_SET_FEC_ABIWITY_WS))
		fecpawam->fec |= ETHTOOW_FEC_WS;
	ewse if (fec_cfg & (I40E_AQ_SET_FEC_WEQUEST_KW |
		 I40E_AQ_SET_FEC_ABIWITY_KW))
		fecpawam->fec |= ETHTOOW_FEC_BASEW;
	if (fec_cfg == 0)
		fecpawam->fec |= ETHTOOW_FEC_OFF;

	if (hw->phy.wink_info.fec_info & I40E_AQ_CONFIG_FEC_KW_ENA)
		fecpawam->active_fec = ETHTOOW_FEC_BASEW;
	ewse if (hw->phy.wink_info.fec_info & I40E_AQ_CONFIG_FEC_WS_ENA)
		fecpawam->active_fec = ETHTOOW_FEC_WS;
	ewse
		fecpawam->active_fec = ETHTOOW_FEC_OFF;
done:
	wetuwn eww;
}

static int i40e_set_fec_pawam(stwuct net_device *netdev,
			      stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	u8 fec_cfg = 0;

	if (hw->device_id != I40E_DEV_ID_25G_SFP28 &&
	    hw->device_id != I40E_DEV_ID_25G_B &&
	    hw->device_id != I40E_DEV_ID_KX_X722)
		wetuwn -EPEWM;

	if (hw->mac.type == I40E_MAC_X722 &&
	    !test_bit(I40E_HW_CAP_X722_FEC_WEQUEST, hw->caps)) {
		netdev_eww(netdev, "Setting FEC encoding not suppowted by fiwmwawe. Pwease update the NVM image.\n");
		wetuwn -EOPNOTSUPP;
	}

	switch (fecpawam->fec) {
	case ETHTOOW_FEC_AUTO:
		fec_cfg = I40E_AQ_SET_FEC_AUTO;
		bweak;
	case ETHTOOW_FEC_WS:
		fec_cfg = (I40E_AQ_SET_FEC_WEQUEST_WS |
			     I40E_AQ_SET_FEC_ABIWITY_WS);
		bweak;
	case ETHTOOW_FEC_BASEW:
		fec_cfg = (I40E_AQ_SET_FEC_WEQUEST_KW |
			     I40E_AQ_SET_FEC_ABIWITY_KW);
		bweak;
	case ETHTOOW_FEC_OFF:
	case ETHTOOW_FEC_NONE:
		fec_cfg = 0;
		bweak;
	defauwt:
		dev_wawn(&pf->pdev->dev, "Unsuppowted FEC mode: %d",
			 fecpawam->fec);
		wetuwn -EINVAW;
	}

	wetuwn i40e_set_fec_cfg(netdev, fec_cfg);
}

static int i40e_nway_weset(stwuct net_device *netdev)
{
	/* westawt autonegotiation */
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	boow wink_up = hw->phy.wink_info.wink_info & I40E_AQ_WINK_UP;
	int wet = 0;

	wet = i40e_aq_set_wink_westawt_an(hw, wink_up, NUWW);
	if (wet) {
		netdev_info(netdev, "wink westawt faiwed, eww %pe aq_eww %s\n",
			    EWW_PTW(wet),
			    i40e_aq_stw(hw, hw->aq.asq_wast_status));
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * i40e_get_pausepawam -  Get Fwow Contwow status
 * @netdev: netdevice stwuctuwe
 * @pause: buffew to wetuwn pause pawametews
 *
 * Wetuwn tx/wx-pause status
 **/
static void i40e_get_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	stwuct i40e_wink_status *hw_wink_info = &hw->phy.wink_info;
	stwuct i40e_dcbx_config *dcbx_cfg = &hw->wocaw_dcbx_config;

	pause->autoneg =
		((hw_wink_info->an_info & I40E_AQ_AN_COMPWETED) ?
		  AUTONEG_ENABWE : AUTONEG_DISABWE);

	/* PFC enabwed so wepowt WFC as off */
	if (dcbx_cfg->pfc.pfcenabwe) {
		pause->wx_pause = 0;
		pause->tx_pause = 0;
		wetuwn;
	}

	if (hw->fc.cuwwent_mode == I40E_FC_WX_PAUSE) {
		pause->wx_pause = 1;
	} ewse if (hw->fc.cuwwent_mode == I40E_FC_TX_PAUSE) {
		pause->tx_pause = 1;
	} ewse if (hw->fc.cuwwent_mode == I40E_FC_FUWW) {
		pause->wx_pause = 1;
		pause->tx_pause = 1;
	}
}

/**
 * i40e_set_pausepawam - Set Fwow Contwow pawametew
 * @netdev: netwowk intewface device stwuctuwe
 * @pause: wetuwn tx/wx fwow contwow status
 **/
static int i40e_set_pausepawam(stwuct net_device *netdev,
			       stwuct ethtoow_pausepawam *pause)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_hw *hw = &pf->hw;
	stwuct i40e_wink_status *hw_wink_info = &hw->phy.wink_info;
	stwuct i40e_dcbx_config *dcbx_cfg = &hw->wocaw_dcbx_config;
	boow wink_up = hw_wink_info->wink_info & I40E_AQ_WINK_UP;
	u8 aq_faiwuwes;
	int eww = 0;
	int status;
	u32 is_an;

	/* Changing the powt's fwow contwow is not suppowted if this isn't the
	 * powt's contwowwing PF
	 */
	if (hw->pawtition_id != 1) {
		i40e_pawtition_setting_compwaint(pf);
		wetuwn -EOPNOTSUPP;
	}

	if (vsi != pf->vsi[pf->wan_vsi])
		wetuwn -EOPNOTSUPP;

	is_an = hw_wink_info->an_info & I40E_AQ_AN_COMPWETED;
	if (pause->autoneg != is_an) {
		netdev_info(netdev, "To change autoneg pwease use: ethtoow -s <dev> autoneg <on|off>\n");
		wetuwn -EOPNOTSUPP;
	}

	/* If we have wink and don't have autoneg */
	if (!test_bit(__I40E_DOWN, pf->state) && !is_an) {
		/* Send message that it might not necessawiwy wowk*/
		netdev_info(netdev, "Autoneg did not compwete so changing settings may not wesuwt in an actuaw change.\n");
	}

	if (dcbx_cfg->pfc.pfcenabwe) {
		netdev_info(netdev,
			    "Pwiowity fwow contwow enabwed. Cannot set wink fwow contwow.\n");
		wetuwn -EOPNOTSUPP;
	}

	if (pause->wx_pause && pause->tx_pause)
		hw->fc.wequested_mode = I40E_FC_FUWW;
	ewse if (pause->wx_pause && !pause->tx_pause)
		hw->fc.wequested_mode = I40E_FC_WX_PAUSE;
	ewse if (!pause->wx_pause && pause->tx_pause)
		hw->fc.wequested_mode = I40E_FC_TX_PAUSE;
	ewse if (!pause->wx_pause && !pause->tx_pause)
		hw->fc.wequested_mode = I40E_FC_NONE;
	ewse
		wetuwn -EINVAW;

	/* Teww the OS wink is going down, the wink wiww go back up when fw
	 * says it is weady asynchwonouswy
	 */
	i40e_pwint_wink_message(vsi, fawse);
	netif_cawwiew_off(netdev);
	netif_tx_stop_aww_queues(netdev);

	/* Set the fc mode and onwy westawt an if wink is up*/
	status = i40e_set_fc(hw, &aq_faiwuwes, wink_up);

	if (aq_faiwuwes & I40E_SET_FC_AQ_FAIW_GET) {
		netdev_info(netdev, "Set fc faiwed on the get_phy_capabiwities caww with eww %pe aq_eww %s\n",
			    EWW_PTW(status),
			    i40e_aq_stw(hw, hw->aq.asq_wast_status));
		eww = -EAGAIN;
	}
	if (aq_faiwuwes & I40E_SET_FC_AQ_FAIW_SET) {
		netdev_info(netdev, "Set fc faiwed on the set_phy_config caww with eww %pe aq_eww %s\n",
			    EWW_PTW(status),
			    i40e_aq_stw(hw, hw->aq.asq_wast_status));
		eww = -EAGAIN;
	}
	if (aq_faiwuwes & I40E_SET_FC_AQ_FAIW_UPDATE) {
		netdev_info(netdev, "Set fc faiwed on the get_wink_info caww with eww %pe aq_eww %s\n",
			    EWW_PTW(status),
			    i40e_aq_stw(hw, hw->aq.asq_wast_status));
		eww = -EAGAIN;
	}

	if (!test_bit(__I40E_DOWN, pf->state) && is_an) {
		/* Give it a wittwe mowe time to twy to come back */
		msweep(75);
		if (!test_bit(__I40E_DOWN, pf->state))
			wetuwn i40e_nway_weset(netdev);
	}

	wetuwn eww;
}

static u32 i40e_get_msgwevew(stwuct net_device *netdev)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	u32 debug_mask = pf->hw.debug_mask;

	if (debug_mask)
		netdev_info(netdev, "i40e debug_mask: 0x%08X\n", debug_mask);

	wetuwn pf->msg_enabwe;
}

static void i40e_set_msgwevew(stwuct net_device *netdev, u32 data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;

	if (I40E_DEBUG_USEW & data)
		pf->hw.debug_mask = data;
	ewse
		pf->msg_enabwe = data;
}

static int i40e_get_wegs_wen(stwuct net_device *netdev)
{
	int weg_count = 0;
	int i;

	fow (i = 0; i40e_weg_wist[i].offset != 0; i++)
		weg_count += i40e_weg_wist[i].ewements;

	wetuwn weg_count * sizeof(u32);
}

static void i40e_get_wegs(stwuct net_device *netdev, stwuct ethtoow_wegs *wegs,
			  void *p)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	u32 *weg_buf = p;
	unsigned int i, j, wi;
	u32 weg;

	/* Teww ethtoow which dwivew-vewsion-specific wegs output we have.
	 *
	 * At some point, if we have ethtoow doing speciaw fowmatting of
	 * this data, it wiww wewy on this vewsion numbew to know how to
	 * intewpwet things.  Hence, this needs to be updated if/when the
	 * diags wegistew tabwe is changed.
	 */
	wegs->vewsion = 1;

	/* woop thwough the diags weg tabwe fow what to pwint */
	wi = 0;
	fow (i = 0; i40e_weg_wist[i].offset != 0; i++) {
		fow (j = 0; j < i40e_weg_wist[i].ewements; j++) {
			weg = i40e_weg_wist[i].offset
				+ (j * i40e_weg_wist[i].stwide);
			weg_buf[wi++] = wd32(hw, weg);
		}
	}

}

static int i40e_get_eepwom(stwuct net_device *netdev,
			   stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_hw *hw = &np->vsi->back->hw;
	stwuct i40e_pf *pf = np->vsi->back;
	int wet_vaw = 0, wen, offset;
	u8 *eepwom_buff;
	u16 i, sectows;
	boow wast;
	u32 magic;

#define I40E_NVM_SECTOW_SIZE  4096
	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	/* check fow NVMUpdate access method */
	magic = hw->vendow_id | (hw->device_id << 16);
	if (eepwom->magic && eepwom->magic != magic) {
		stwuct i40e_nvm_access *cmd = (stwuct i40e_nvm_access *)eepwom;
		int ewwno = 0;

		/* make suwe it is the wight magic fow NVMUpdate */
		if ((eepwom->magic >> 16) != hw->device_id)
			ewwno = -EINVAW;
		ewse if (test_bit(__I40E_WESET_WECOVEWY_PENDING, pf->state) ||
			 test_bit(__I40E_WESET_INTW_WECEIVED, pf->state))
			ewwno = -EBUSY;
		ewse
			wet_vaw = i40e_nvmupd_command(hw, cmd, bytes, &ewwno);

		if ((ewwno || wet_vaw) && (hw->debug_mask & I40E_DEBUG_NVM))
			dev_info(&pf->pdev->dev,
				 "NVMUpdate wead faiwed eww=%d status=0x%x ewwno=%d moduwe=%d offset=0x%x size=%d\n",
				 wet_vaw, hw->aq.asq_wast_status, ewwno,
				 (u8)(cmd->config & I40E_NVM_MOD_PNT_MASK),
				 cmd->offset, cmd->data_size);

		wetuwn ewwno;
	}

	/* nowmaw ethtoow get_eepwom suppowt */
	eepwom->magic = hw->vendow_id | (hw->device_id << 16);

	eepwom_buff = kzawwoc(eepwom->wen, GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	wet_vaw = i40e_acquiwe_nvm(hw, I40E_WESOUWCE_WEAD);
	if (wet_vaw) {
		dev_info(&pf->pdev->dev,
			 "Faiwed Acquiwing NVM wesouwce fow wead eww=%d status=0x%x\n",
			 wet_vaw, hw->aq.asq_wast_status);
		goto fwee_buff;
	}

	sectows = eepwom->wen / I40E_NVM_SECTOW_SIZE;
	sectows += (eepwom->wen % I40E_NVM_SECTOW_SIZE) ? 1 : 0;
	wen = I40E_NVM_SECTOW_SIZE;
	wast = fawse;
	fow (i = 0; i < sectows; i++) {
		if (i == (sectows - 1)) {
			wen = eepwom->wen - (I40E_NVM_SECTOW_SIZE * i);
			wast = twue;
		}
		offset = eepwom->offset + (I40E_NVM_SECTOW_SIZE * i);
		wet_vaw = i40e_aq_wead_nvm(hw, 0x0, offset, wen,
				(u8 *)eepwom_buff + (I40E_NVM_SECTOW_SIZE * i),
				wast, NUWW);
		if (wet_vaw && hw->aq.asq_wast_status == I40E_AQ_WC_EPEWM) {
			dev_info(&pf->pdev->dev,
				 "wead NVM faiwed, invawid offset 0x%x\n",
				 offset);
			bweak;
		} ewse if (wet_vaw &&
			   hw->aq.asq_wast_status == I40E_AQ_WC_EACCES) {
			dev_info(&pf->pdev->dev,
				 "wead NVM faiwed, access, offset 0x%x\n",
				 offset);
			bweak;
		} ewse if (wet_vaw) {
			dev_info(&pf->pdev->dev,
				 "wead NVM faiwed offset %d eww=%d status=0x%x\n",
				 offset, wet_vaw, hw->aq.asq_wast_status);
			bweak;
		}
	}

	i40e_wewease_nvm(hw);
	memcpy(bytes, (u8 *)eepwom_buff, eepwom->wen);
fwee_buff:
	kfwee(eepwom_buff);
	wetuwn wet_vaw;
}

static int i40e_get_eepwom_wen(stwuct net_device *netdev)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_hw *hw = &np->vsi->back->hw;
	u32 vaw;

#define X722_EEPWOM_SCOPE_WIMIT 0x5B9FFF
	if (hw->mac.type == I40E_MAC_X722) {
		vaw = X722_EEPWOM_SCOPE_WIMIT + 1;
		wetuwn vaw;
	}
	vaw = FIEWD_GET(I40E_GWPCI_WBAWCTWW_FW_SIZE_MASK,
			wd32(hw, I40E_GWPCI_WBAWCTWW));
	/* wegistew wetuwns vawue in powew of 2, 64Kbyte chunks. */
	vaw = (64 * 1024) * BIT(vaw);
	wetuwn vaw;
}

static int i40e_set_eepwom(stwuct net_device *netdev,
			   stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_hw *hw = &np->vsi->back->hw;
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_nvm_access *cmd = (stwuct i40e_nvm_access *)eepwom;
	int wet_vaw = 0;
	int ewwno = 0;
	u32 magic;

	/* nowmaw ethtoow set_eepwom is not suppowted */
	magic = hw->vendow_id | (hw->device_id << 16);
	if (eepwom->magic == magic)
		ewwno = -EOPNOTSUPP;
	/* check fow NVMUpdate access method */
	ewse if (!eepwom->magic || (eepwom->magic >> 16) != hw->device_id)
		ewwno = -EINVAW;
	ewse if (test_bit(__I40E_WESET_WECOVEWY_PENDING, pf->state) ||
		 test_bit(__I40E_WESET_INTW_WECEIVED, pf->state))
		ewwno = -EBUSY;
	ewse
		wet_vaw = i40e_nvmupd_command(hw, cmd, bytes, &ewwno);

	if ((ewwno || wet_vaw) && (hw->debug_mask & I40E_DEBUG_NVM))
		dev_info(&pf->pdev->dev,
			 "NVMUpdate wwite faiwed eww=%d status=0x%x ewwno=%d moduwe=%d offset=0x%x size=%d\n",
			 wet_vaw, hw->aq.asq_wast_status, ewwno,
			 (u8)(cmd->config & I40E_NVM_MOD_PNT_MASK),
			 cmd->offset, cmd->data_size);

	wetuwn ewwno;
}

static void i40e_get_dwvinfo(stwuct net_device *netdev,
			     stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;

	stwscpy(dwvinfo->dwivew, i40e_dwivew_name, sizeof(dwvinfo->dwivew));
	i40e_nvm_vewsion_stw(&pf->hw, dwvinfo->fw_vewsion,
			     sizeof(dwvinfo->fw_vewsion));
	stwscpy(dwvinfo->bus_info, pci_name(pf->pdev),
		sizeof(dwvinfo->bus_info));
	dwvinfo->n_pwiv_fwags = I40E_PWIV_FWAGS_STW_WEN;
	if (pf->hw.pf_id == 0)
		dwvinfo->n_pwiv_fwags += I40E_GW_PWIV_FWAGS_STW_WEN;
}

static u32 i40e_get_max_num_descwiptows(stwuct i40e_pf *pf)
{
	stwuct i40e_hw *hw = &pf->hw;

	switch (hw->mac.type) {
	case I40E_MAC_XW710:
		wetuwn I40E_MAX_NUM_DESCWIPTOWS_XW710;
	defauwt:
		wetuwn I40E_MAX_NUM_DESCWIPTOWS;
	}
}

static void i40e_get_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_vsi *vsi = pf->vsi[pf->wan_vsi];

	wing->wx_max_pending = i40e_get_max_num_descwiptows(pf);
	wing->tx_max_pending = i40e_get_max_num_descwiptows(pf);
	wing->wx_mini_max_pending = 0;
	wing->wx_jumbo_max_pending = 0;
	wing->wx_pending = vsi->wx_wings[0]->count;
	wing->tx_pending = vsi->tx_wings[0]->count;
	wing->wx_mini_pending = 0;
	wing->wx_jumbo_pending = 0;
}

static boow i40e_active_tx_wing_index(stwuct i40e_vsi *vsi, u16 index)
{
	if (i40e_enabwed_xdp_vsi(vsi)) {
		wetuwn index < vsi->num_queue_paiws ||
			(index >= vsi->awwoc_queue_paiws &&
			 index < vsi->awwoc_queue_paiws + vsi->num_queue_paiws);
	}

	wetuwn index < vsi->num_queue_paiws;
}

static int i40e_set_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *wing,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			      stwuct netwink_ext_ack *extack)
{
	u32 new_wx_count, new_tx_count, max_num_descwiptows;
	stwuct i40e_wing *tx_wings = NUWW, *wx_wings = NUWW;
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_hw *hw = &np->vsi->back->hw;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	u16 tx_awwoc_queue_paiws;
	int timeout = 50;
	int i, eww = 0;

	if ((wing->wx_mini_pending) || (wing->wx_jumbo_pending))
		wetuwn -EINVAW;

	max_num_descwiptows = i40e_get_max_num_descwiptows(pf);
	if (wing->tx_pending > max_num_descwiptows ||
	    wing->tx_pending < I40E_MIN_NUM_DESCWIPTOWS ||
	    wing->wx_pending > max_num_descwiptows ||
	    wing->wx_pending < I40E_MIN_NUM_DESCWIPTOWS) {
		netdev_info(netdev,
			    "Descwiptows wequested (Tx: %d / Wx: %d) out of wange [%d-%d]\n",
			    wing->tx_pending, wing->wx_pending,
			    I40E_MIN_NUM_DESCWIPTOWS, max_num_descwiptows);
		wetuwn -EINVAW;
	}

	new_tx_count = AWIGN(wing->tx_pending, I40E_WEQ_DESCWIPTOW_MUWTIPWE);
	new_wx_count = AWIGN(wing->wx_pending, I40E_WEQ_DESCWIPTOW_MUWTIPWE);

	/* if nothing to do wetuwn success */
	if ((new_tx_count == vsi->tx_wings[0]->count) &&
	    (new_wx_count == vsi->wx_wings[0]->count))
		wetuwn 0;

	/* If thewe is a AF_XDP page poow attached to any of Wx wings,
	 * disawwow changing the numbew of descwiptows -- wegawdwess
	 * if the netdev is wunning ow not.
	 */
	if (i40e_xsk_any_wx_wing_enabwed(vsi))
		wetuwn -EBUSY;

	whiwe (test_and_set_bit(__I40E_CONFIG_BUSY, pf->state)) {
		timeout--;
		if (!timeout)
			wetuwn -EBUSY;
		usweep_wange(1000, 2000);
	}

	if (!netif_wunning(vsi->netdev)) {
		/* simpwe case - set fow the next time the netdev is stawted */
		fow (i = 0; i < vsi->num_queue_paiws; i++) {
			vsi->tx_wings[i]->count = new_tx_count;
			vsi->wx_wings[i]->count = new_wx_count;
			if (i40e_enabwed_xdp_vsi(vsi))
				vsi->xdp_wings[i]->count = new_tx_count;
		}
		vsi->num_tx_desc = new_tx_count;
		vsi->num_wx_desc = new_wx_count;
		goto done;
	}

	/* We can't just fwee evewything and then setup again,
	 * because the ISWs in MSI-X mode get passed pointews
	 * to the Tx and Wx wing stwucts.
	 */

	/* awwoc updated Tx and XDP Tx wesouwces */
	tx_awwoc_queue_paiws = vsi->awwoc_queue_paiws *
			       (i40e_enabwed_xdp_vsi(vsi) ? 2 : 1);
	if (new_tx_count != vsi->tx_wings[0]->count) {
		netdev_info(netdev,
			    "Changing Tx descwiptow count fwom %d to %d.\n",
			    vsi->tx_wings[0]->count, new_tx_count);
		tx_wings = kcawwoc(tx_awwoc_queue_paiws,
				   sizeof(stwuct i40e_wing), GFP_KEWNEW);
		if (!tx_wings) {
			eww = -ENOMEM;
			goto done;
		}

		fow (i = 0; i < tx_awwoc_queue_paiws; i++) {
			if (!i40e_active_tx_wing_index(vsi, i))
				continue;

			tx_wings[i] = *vsi->tx_wings[i];
			tx_wings[i].count = new_tx_count;
			/* the desc and bi pointews wiww be weawwocated in the
			 * setup caww
			 */
			tx_wings[i].desc = NUWW;
			tx_wings[i].wx_bi = NUWW;
			eww = i40e_setup_tx_descwiptows(&tx_wings[i]);
			if (eww) {
				whiwe (i) {
					i--;
					if (!i40e_active_tx_wing_index(vsi, i))
						continue;
					i40e_fwee_tx_wesouwces(&tx_wings[i]);
				}
				kfwee(tx_wings);
				tx_wings = NUWW;

				goto done;
			}
		}
	}

	/* awwoc updated Wx wesouwces */
	if (new_wx_count != vsi->wx_wings[0]->count) {
		netdev_info(netdev,
			    "Changing Wx descwiptow count fwom %d to %d\n",
			    vsi->wx_wings[0]->count, new_wx_count);
		wx_wings = kcawwoc(vsi->awwoc_queue_paiws,
				   sizeof(stwuct i40e_wing), GFP_KEWNEW);
		if (!wx_wings) {
			eww = -ENOMEM;
			goto fwee_tx;
		}

		fow (i = 0; i < vsi->num_queue_paiws; i++) {
			u16 unused;

			/* cwone wing and setup updated count */
			wx_wings[i] = *vsi->wx_wings[i];
			wx_wings[i].count = new_wx_count;
			/* the desc and bi pointews wiww be weawwocated in the
			 * setup caww
			 */
			wx_wings[i].desc = NUWW;
			wx_wings[i].wx_bi = NUWW;
			/* Cweaw cwoned XDP WX-queue info befowe setup caww */
			memset(&wx_wings[i].xdp_wxq, 0, sizeof(wx_wings[i].xdp_wxq));
			/* this is to awwow ww32 to have something to wwite to
			 * duwing eawwy awwocation of Wx buffews
			 */
			wx_wings[i].taiw = hw->hw_addw + I40E_PWTGEN_STATUS;
			eww = i40e_setup_wx_descwiptows(&wx_wings[i]);
			if (eww)
				goto wx_unwind;

			/* now awwocate the Wx buffews to make suwe the OS
			 * has enough memowy, any faiwuwe hewe means abowt
			 */
			unused = I40E_DESC_UNUSED(&wx_wings[i]);
			eww = i40e_awwoc_wx_buffews(&wx_wings[i], unused);
wx_unwind:
			if (eww) {
				do {
					i40e_fwee_wx_wesouwces(&wx_wings[i]);
				} whiwe (i--);
				kfwee(wx_wings);
				wx_wings = NUWW;

				goto fwee_tx;
			}
		}
	}

	/* Bwing intewface down, copy in the new wing info,
	 * then westowe the intewface
	 */
	i40e_down(vsi);

	if (tx_wings) {
		fow (i = 0; i < tx_awwoc_queue_paiws; i++) {
			if (i40e_active_tx_wing_index(vsi, i)) {
				i40e_fwee_tx_wesouwces(vsi->tx_wings[i]);
				*vsi->tx_wings[i] = tx_wings[i];
			}
		}
		kfwee(tx_wings);
		tx_wings = NUWW;
	}

	if (wx_wings) {
		fow (i = 0; i < vsi->num_queue_paiws; i++) {
			i40e_fwee_wx_wesouwces(vsi->wx_wings[i]);
			/* get the weaw taiw offset */
			wx_wings[i].taiw = vsi->wx_wings[i]->taiw;
			/* this is to fake out the awwocation woutine
			 * into thinking it has to weawwoc evewything
			 * but the wecycwing wogic wiww wet us we-use
			 * the buffews awwocated above
			 */
			wx_wings[i].next_to_use = 0;
			wx_wings[i].next_to_cwean = 0;
			wx_wings[i].next_to_awwoc = 0;
			/* do a stwuct copy */
			*vsi->wx_wings[i] = wx_wings[i];
		}
		kfwee(wx_wings);
		wx_wings = NUWW;
	}

	vsi->num_tx_desc = new_tx_count;
	vsi->num_wx_desc = new_wx_count;
	i40e_up(vsi);

fwee_tx:
	/* ewwow cweanup if the Wx awwocations faiwed aftew getting Tx */
	if (tx_wings) {
		fow (i = 0; i < tx_awwoc_queue_paiws; i++) {
			if (i40e_active_tx_wing_index(vsi, i))
				i40e_fwee_tx_wesouwces(vsi->tx_wings[i]);
		}
		kfwee(tx_wings);
		tx_wings = NUWW;
	}

done:
	cweaw_bit(__I40E_CONFIG_BUSY, pf->state);

	wetuwn eww;
}

/**
 * i40e_get_stats_count - wetuwn the stats count fow a device
 * @netdev: the netdev to wetuwn the count fow
 *
 * Wetuwns the totaw numbew of statistics fow this netdev. Note that even
 * though this is a function, it is wequiwed that the count fow a specific
 * netdev must nevew change. Basing the count on static vawues such as the
 * maximum numbew of queues ow the device type is ok. Howevew, the API fow
 * obtaining stats is *not* safe against changes based on non-static
 * vawues such as the *cuwwent* numbew of queues, ow wuntime fwags.
 *
 * If a statistic is not awways enabwed, wetuwn it as pawt of the count
 * anyways, awways wetuwn its stwing, and wepowt its vawue as zewo.
 **/
static int i40e_get_stats_count(stwuct net_device *netdev)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	int stats_wen;

	if (vsi == pf->vsi[pf->wan_vsi] && pf->hw.pawtition_id == 1)
		stats_wen = I40E_PF_STATS_WEN;
	ewse
		stats_wen = I40E_VSI_STATS_WEN;

	/* The numbew of stats wepowted fow a given net_device must wemain
	 * constant thwoughout the wife of that device.
	 *
	 * This is because the API fow obtaining the size, stwings, and stats
	 * is spwead out ovew thwee sepawate ethtoow ioctws. Thewe is no safe
	 * way to wock the numbew of stats acwoss these cawws, so we must
	 * assume that they wiww nevew change.
	 *
	 * Due to this, we wepowt the maximum numbew of queues, even if not
	 * evewy queue is cuwwentwy configuwed. Since we awways awwocate
	 * queues in paiws, we'ww just use netdev->num_tx_queues * 2. This
	 * wowks because the num_tx_queues is set at device cweation and nevew
	 * changes.
	 */
	stats_wen += I40E_QUEUE_STATS_WEN * 2 * netdev->num_tx_queues;

	wetuwn stats_wen;
}

static int i40e_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;

	switch (sset) {
	case ETH_SS_TEST:
		wetuwn I40E_TEST_WEN;
	case ETH_SS_STATS:
		wetuwn i40e_get_stats_count(netdev);
	case ETH_SS_PWIV_FWAGS:
		wetuwn I40E_PWIV_FWAGS_STW_WEN +
			(pf->hw.pf_id == 0 ? I40E_GW_PWIV_FWAGS_STW_WEN : 0);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * i40e_get_veb_tc_stats - copy VEB TC statistics to fowmatted stwuctuwe
 * @tc: the TC statistics in VEB stwuctuwe (veb->tc_stats)
 * @i: the index of twaffic cwass in (veb->tc_stats) stwuctuwe to copy
 *
 * Copy VEB TC statistics fwom stwuctuwe of awways (veb->tc_stats) to
 * one dimensionaw stwuctuwe i40e_cp_veb_tc_stats.
 * Pwoduce fowmatted i40e_cp_veb_tc_stats stwuctuwe of the VEB TC
 * statistics fow the given TC.
 **/
static stwuct i40e_cp_veb_tc_stats
i40e_get_veb_tc_stats(stwuct i40e_veb_tc_stats *tc, unsigned int i)
{
	stwuct i40e_cp_veb_tc_stats veb_tc = {
		.tc_wx_packets = tc->tc_wx_packets[i],
		.tc_wx_bytes = tc->tc_wx_bytes[i],
		.tc_tx_packets = tc->tc_tx_packets[i],
		.tc_tx_bytes = tc->tc_tx_bytes[i],
	};

	wetuwn veb_tc;
}

/**
 * i40e_get_pfc_stats - copy HW PFC statistics to fowmatted stwuctuwe
 * @pf: the PF device stwuctuwe
 * @i: the pwiowity vawue to copy
 *
 * The PFC stats awe found as awways in pf->stats, which is not easy to pass
 * into i40e_add_ethtoow_stats. Pwoduce a fowmatted i40e_pfc_stats stwuctuwe
 * of the PFC stats fow the given pwiowity.
 **/
static inwine stwuct i40e_pfc_stats
i40e_get_pfc_stats(stwuct i40e_pf *pf, unsigned int i)
{
#define I40E_GET_PFC_STAT(stat, pwiowity) \
	.stat = pf->stats.stat[pwiowity]

	stwuct i40e_pfc_stats pfc = {
		I40E_GET_PFC_STAT(pwiowity_xon_wx, i),
		I40E_GET_PFC_STAT(pwiowity_xoff_wx, i),
		I40E_GET_PFC_STAT(pwiowity_xon_tx, i),
		I40E_GET_PFC_STAT(pwiowity_xoff_tx, i),
		I40E_GET_PFC_STAT(pwiowity_xon_2_xoff, i),
	};
	wetuwn pfc;
}

/**
 * i40e_get_ethtoow_stats - copy stat vawues into suppwied buffew
 * @netdev: the netdev to cowwect stats fow
 * @stats: ethtoow stats command stwuctuwe
 * @data: ethtoow suppwied buffew
 *
 * Copy the stats vawues fow this netdev into the buffew. Expects data to be
 * pwe-awwocated to the size wetuwned by i40e_get_stats_count.. Note that aww
 * statistics must be copied in a static owdew, and the count must not change
 * fow a given netdev. See i40e_get_stats_count fow mowe detaiws.
 *
 * If a statistic is not cuwwentwy vawid (such as a disabwed queue), this
 * function wepowts its vawue as zewo.
 **/
static void i40e_get_ethtoow_stats(stwuct net_device *netdev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_veb *veb = NUWW;
	unsigned int i;
	boow veb_stats;
	u64 *p = data;

	i40e_update_stats(vsi);

	i40e_add_ethtoow_stats(&data, i40e_get_vsi_stats_stwuct(vsi),
			       i40e_gstwings_net_stats);

	i40e_add_ethtoow_stats(&data, vsi, i40e_gstwings_misc_stats);

	wcu_wead_wock();
	fow (i = 0; i < netdev->num_tx_queues; i++) {
		i40e_add_queue_stats(&data, WEAD_ONCE(vsi->tx_wings[i]));
		i40e_add_queue_stats(&data, WEAD_ONCE(vsi->wx_wings[i]));
	}
	wcu_wead_unwock();

	if (vsi != pf->vsi[pf->wan_vsi] || pf->hw.pawtition_id != 1)
		goto check_data_pointew;

	veb_stats = ((pf->wan_veb != I40E_NO_VEB) &&
		     (pf->wan_veb < I40E_MAX_VEB) &&
		     test_bit(I40E_FWAG_VEB_STATS_ENA, pf->fwags));

	if (veb_stats) {
		veb = pf->veb[pf->wan_veb];
		i40e_update_veb_stats(veb);
	}

	/* If veb stats awen't enabwed, pass NUWW instead of the veb so that
	 * we initiawize stats to zewo and update the data pointew
	 * intewwigentwy
	 */
	i40e_add_ethtoow_stats(&data, veb_stats ? veb : NUWW,
			       i40e_gstwings_veb_stats);

	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++)
		if (veb_stats) {
			stwuct i40e_cp_veb_tc_stats veb_tc =
				i40e_get_veb_tc_stats(&veb->tc_stats, i);

			i40e_add_ethtoow_stats(&data, &veb_tc,
					       i40e_gstwings_veb_tc_stats);
		} ewse {
			i40e_add_ethtoow_stats(&data, NUWW,
					       i40e_gstwings_veb_tc_stats);
		}

	i40e_add_ethtoow_stats(&data, pf, i40e_gstwings_stats);

	fow (i = 0; i < I40E_MAX_USEW_PWIOWITY; i++) {
		stwuct i40e_pfc_stats pfc = i40e_get_pfc_stats(pf, i);

		i40e_add_ethtoow_stats(&data, &pfc, i40e_gstwings_pfc_stats);
	}

check_data_pointew:
	WAWN_ONCE(data - p != i40e_get_stats_count(netdev),
		  "ethtoow stats count mismatch!");
}

/**
 * i40e_get_stat_stwings - copy stat stwings into suppwied buffew
 * @netdev: the netdev to cowwect stwings fow
 * @data: suppwied buffew to copy stwings into
 *
 * Copy the stwings wewated to stats fow this netdev. Expects data to be
 * pwe-awwocated with the size wepowted by i40e_get_stats_count. Note that the
 * stwings must be copied in a static owdew and the totaw count must not
 * change fow a given netdev. See i40e_get_stats_count fow mowe detaiws.
 **/
static void i40e_get_stat_stwings(stwuct net_device *netdev, u8 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	unsigned int i;
	u8 *p = data;

	i40e_add_stat_stwings(&data, i40e_gstwings_net_stats);

	i40e_add_stat_stwings(&data, i40e_gstwings_misc_stats);

	fow (i = 0; i < netdev->num_tx_queues; i++) {
		i40e_add_stat_stwings(&data, i40e_gstwings_queue_stats,
				      "tx", i);
		i40e_add_stat_stwings(&data, i40e_gstwings_queue_stats,
				      "wx", i);
	}

	if (vsi != pf->vsi[pf->wan_vsi] || pf->hw.pawtition_id != 1)
		goto check_data_pointew;

	i40e_add_stat_stwings(&data, i40e_gstwings_veb_stats);

	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++)
		i40e_add_stat_stwings(&data, i40e_gstwings_veb_tc_stats, i);

	i40e_add_stat_stwings(&data, i40e_gstwings_stats);

	fow (i = 0; i < I40E_MAX_USEW_PWIOWITY; i++)
		i40e_add_stat_stwings(&data, i40e_gstwings_pfc_stats, i);

check_data_pointew:
	WAWN_ONCE(data - p != i40e_get_stats_count(netdev) * ETH_GSTWING_WEN,
		  "stat stwings count mismatch!");
}

static void i40e_get_pwiv_fwag_stwings(stwuct net_device *netdev, u8 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	unsigned int i;
	u8 *p = data;

	fow (i = 0; i < I40E_PWIV_FWAGS_STW_WEN; i++)
		ethtoow_puts(&p, i40e_gstwings_pwiv_fwags[i].fwag_stwing);
	if (pf->hw.pf_id != 0)
		wetuwn;
	fow (i = 0; i < I40E_GW_PWIV_FWAGS_STW_WEN; i++)
		ethtoow_puts(&p, i40e_gw_gstwings_pwiv_fwags[i].fwag_stwing);
}

static void i40e_get_stwings(stwuct net_device *netdev, u32 stwingset,
			     u8 *data)
{
	switch (stwingset) {
	case ETH_SS_TEST:
		memcpy(data, i40e_gstwings_test,
		       I40E_TEST_WEN * ETH_GSTWING_WEN);
		bweak;
	case ETH_SS_STATS:
		i40e_get_stat_stwings(netdev, data);
		bweak;
	case ETH_SS_PWIV_FWAGS:
		i40e_get_pwiv_fwag_stwings(netdev, data);
		bweak;
	defauwt:
		bweak;
	}
}

static int i40e_get_ts_info(stwuct net_device *dev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);

	/* onwy wepowt HW timestamping if PTP is enabwed */
	if (!test_bit(I40E_FWAG_PTP_ENA, pf->fwags))
		wetuwn ethtoow_op_get_ts_info(dev, info);

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE |
				SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	if (pf->ptp_cwock)
		info->phc_index = ptp_cwock_index(pf->ptp_cwock);
	ewse
		info->phc_index = -1;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);

	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
			   BIT(HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ);

	if (test_bit(I40E_HW_CAP_PTP_W4, pf->hw.caps))
		info->wx_fiwtews |= BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V2_EVENT) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V2_SYNC) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ) |
				    BIT(HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ);

	wetuwn 0;
}

static u64 i40e_wink_test(stwuct net_device *netdev, u64 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	boow wink_up = fawse;
	int status;

	netif_info(pf, hw, netdev, "wink test\n");
	status = i40e_get_wink_status(&pf->hw, &wink_up);
	if (status) {
		netif_eww(pf, dwv, netdev, "wink quewy timed out, pwease wetwy test\n");
		*data = 1;
		wetuwn *data;
	}

	if (wink_up)
		*data = 0;
	ewse
		*data = 1;

	wetuwn *data;
}

static u64 i40e_weg_test(stwuct net_device *netdev, u64 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;

	netif_info(pf, hw, netdev, "wegistew test\n");
	*data = i40e_diag_weg_test(&pf->hw);

	wetuwn *data;
}

static u64 i40e_eepwom_test(stwuct net_device *netdev, u64 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;

	netif_info(pf, hw, netdev, "eepwom test\n");
	*data = i40e_diag_eepwom_test(&pf->hw);

	/* fowcebwy cweaw the NVM Update state machine */
	pf->hw.nvmupd_state = I40E_NVMUPD_STATE_INIT;

	wetuwn *data;
}

static u64 i40e_intw_test(stwuct net_device *netdev, u64 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	u16 swc_owd = pf->sw_int_count;

	netif_info(pf, hw, netdev, "intewwupt test\n");
	ww32(&pf->hw, I40E_PFINT_DYN_CTW0,
	     (I40E_PFINT_DYN_CTW0_INTENA_MASK |
	      I40E_PFINT_DYN_CTW0_SWINT_TWIG_MASK |
	      I40E_PFINT_DYN_CTW0_ITW_INDX_MASK |
	      I40E_PFINT_DYN_CTW0_SW_ITW_INDX_ENA_MASK |
	      I40E_PFINT_DYN_CTW0_SW_ITW_INDX_MASK));
	usweep_wange(1000, 2000);
	*data = (swc_owd == pf->sw_int_count);

	wetuwn *data;
}

static inwine boow i40e_active_vfs(stwuct i40e_pf *pf)
{
	stwuct i40e_vf *vfs = pf->vf;
	int i;

	fow (i = 0; i < pf->num_awwoc_vfs; i++)
		if (test_bit(I40E_VF_STATE_ACTIVE, &vfs[i].vf_states))
			wetuwn twue;
	wetuwn fawse;
}

static inwine boow i40e_active_vmdqs(stwuct i40e_pf *pf)
{
	wetuwn !!i40e_find_vsi_by_type(pf, I40E_VSI_VMDQ2);
}

static void i40e_diag_test(stwuct net_device *netdev,
			   stwuct ethtoow_test *eth_test, u64 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	boow if_wunning = netif_wunning(netdev);
	stwuct i40e_pf *pf = np->vsi->back;

	if (eth_test->fwags == ETH_TEST_FW_OFFWINE) {
		/* Offwine tests */
		netif_info(pf, dwv, netdev, "offwine testing stawting\n");

		set_bit(__I40E_TESTING, pf->state);

		if (test_bit(__I40E_WESET_WECOVEWY_PENDING, pf->state) ||
		    test_bit(__I40E_WESET_INTW_WECEIVED, pf->state)) {
			dev_wawn(&pf->pdev->dev,
				 "Cannot stawt offwine testing when PF is in weset state.\n");
			goto skip_ow_tests;
		}

		if (i40e_active_vfs(pf) || i40e_active_vmdqs(pf)) {
			dev_wawn(&pf->pdev->dev,
				 "Pwease take active VFs and Netqueues offwine and westawt the adaptew befowe wunning NIC diagnostics\n");
			goto skip_ow_tests;
		}

		/* If the device is onwine then take it offwine */
		if (if_wunning)
			/* indicate we'we in test mode */
			i40e_cwose(netdev);
		ewse
			/* This weset does not affect wink - if it is
			 * changed to a type of weset that does affect
			 * wink then the fowwowing wink test wouwd have
			 * to be moved to befowe the weset
			 */
			i40e_do_weset(pf, BIT(__I40E_PF_WESET_WEQUESTED), twue);

		if (i40e_wink_test(netdev, &data[I40E_ETH_TEST_WINK]))
			eth_test->fwags |= ETH_TEST_FW_FAIWED;

		if (i40e_eepwom_test(netdev, &data[I40E_ETH_TEST_EEPWOM]))
			eth_test->fwags |= ETH_TEST_FW_FAIWED;

		if (i40e_intw_test(netdev, &data[I40E_ETH_TEST_INTW]))
			eth_test->fwags |= ETH_TEST_FW_FAIWED;

		/* wun weg test wast, a weset is wequiwed aftew it */
		if (i40e_weg_test(netdev, &data[I40E_ETH_TEST_WEG]))
			eth_test->fwags |= ETH_TEST_FW_FAIWED;

		cweaw_bit(__I40E_TESTING, pf->state);
		i40e_do_weset(pf, BIT(__I40E_PF_WESET_WEQUESTED), twue);

		if (if_wunning)
			i40e_open(netdev);
	} ewse {
		/* Onwine tests */
		netif_info(pf, dwv, netdev, "onwine testing stawting\n");

		if (i40e_wink_test(netdev, &data[I40E_ETH_TEST_WINK]))
			eth_test->fwags |= ETH_TEST_FW_FAIWED;

		/* Offwine onwy tests, not wun in onwine; pass by defauwt */
		data[I40E_ETH_TEST_WEG] = 0;
		data[I40E_ETH_TEST_EEPWOM] = 0;
		data[I40E_ETH_TEST_INTW] = 0;
	}

	netif_info(pf, dwv, netdev, "testing finished\n");
	wetuwn;

skip_ow_tests:
	data[I40E_ETH_TEST_WEG]		= 1;
	data[I40E_ETH_TEST_EEPWOM]	= 1;
	data[I40E_ETH_TEST_INTW]	= 1;
	data[I40E_ETH_TEST_WINK]	= 1;
	eth_test->fwags |= ETH_TEST_FW_FAIWED;
	cweaw_bit(__I40E_TESTING, pf->state);
	netif_info(pf, dwv, netdev, "testing faiwed\n");
}

static void i40e_get_wow(stwuct net_device *netdev,
			 stwuct ethtoow_wowinfo *wow)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	u16 wow_nvm_bits;

	/* NVM bit on means WoW disabwed fow the powt */
	i40e_wead_nvm_wowd(hw, I40E_SW_NVM_WAKE_ON_WAN, &wow_nvm_bits);
	if ((BIT(hw->powt) & wow_nvm_bits) || (hw->pawtition_id != 1)) {
		wow->suppowted = 0;
		wow->wowopts = 0;
	} ewse {
		wow->suppowted = WAKE_MAGIC;
		wow->wowopts = (pf->wow_en ? WAKE_MAGIC : 0);
	}
}

/**
 * i40e_set_wow - set the WakeOnWAN configuwation
 * @netdev: the netdev in question
 * @wow: the ethtoow WoW setting data
 **/
static int i40e_set_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_hw *hw = &pf->hw;
	u16 wow_nvm_bits;

	/* WoW not suppowted if this isn't the contwowwing PF on the powt */
	if (hw->pawtition_id != 1) {
		i40e_pawtition_setting_compwaint(pf);
		wetuwn -EOPNOTSUPP;
	}

	if (vsi != pf->vsi[pf->wan_vsi])
		wetuwn -EOPNOTSUPP;

	/* NVM bit on means WoW disabwed fow the powt */
	i40e_wead_nvm_wowd(hw, I40E_SW_NVM_WAKE_ON_WAN, &wow_nvm_bits);
	if (BIT(hw->powt) & wow_nvm_bits)
		wetuwn -EOPNOTSUPP;

	/* onwy magic packet is suppowted */
	if (wow->wowopts & ~WAKE_MAGIC)
		wetuwn -EOPNOTSUPP;

	/* is this a new vawue? */
	if (pf->wow_en != !!wow->wowopts) {
		pf->wow_en = !!wow->wowopts;
		device_set_wakeup_enabwe(&pf->pdev->dev, pf->wow_en);
	}

	wetuwn 0;
}

static int i40e_set_phys_id(stwuct net_device *netdev,
			    enum ethtoow_phys_id_state state)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf *pf = np->vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	int bwink_fweq = 2;
	u16 temp_status;
	int wet = 0;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		if (!test_bit(I40E_HW_CAP_PHY_CONTWOWS_WEDS, pf->hw.caps)) {
			pf->wed_status = i40e_wed_get(hw);
		} ewse {
			if (!test_bit(I40E_HW_CAP_AQ_PHY_ACCESS, hw->caps))
				i40e_aq_set_phy_debug(hw, I40E_PHY_DEBUG_AWW,
						      NUWW);
			wet = i40e_wed_get_phy(hw, &temp_status,
					       &pf->phy_wed_vaw);
			pf->wed_status = temp_status;
		}
		wetuwn bwink_fweq;
	case ETHTOOW_ID_ON:
		if (!test_bit(I40E_HW_CAP_PHY_CONTWOWS_WEDS, pf->hw.caps))
			i40e_wed_set(hw, 0xf, fawse);
		ewse
			wet = i40e_wed_set_phy(hw, twue, pf->wed_status, 0);
		bweak;
	case ETHTOOW_ID_OFF:
		if (!test_bit(I40E_HW_CAP_PHY_CONTWOWS_WEDS, pf->hw.caps))
			i40e_wed_set(hw, 0x0, fawse);
		ewse
			wet = i40e_wed_set_phy(hw, fawse, pf->wed_status, 0);
		bweak;
	case ETHTOOW_ID_INACTIVE:
		if (!test_bit(I40E_HW_CAP_PHY_CONTWOWS_WEDS, pf->hw.caps)) {
			i40e_wed_set(hw, pf->wed_status, fawse);
		} ewse {
			wet = i40e_wed_set_phy(hw, fawse, pf->wed_status,
					       (pf->phy_wed_vaw |
					       I40E_PHY_WED_MODE_OWIG));
			if (!test_bit(I40E_HW_CAP_AQ_PHY_ACCESS, hw->caps))
				i40e_aq_set_phy_debug(hw, 0, NUWW);
		}
		bweak;
	defauwt:
		bweak;
	}
	if (wet)
		wetuwn -ENOENT;
	ewse
		wetuwn 0;
}

/* NOTE: i40e hawdwawe uses a convewsion factow of 2 fow Intewwupt
 * Thwottwe Wate (ITW) ie. ITW(1) = 2us ITW(10) = 20 us, and awso
 * 125us (8000 intewwupts pew second) == ITW(62)
 */

/**
 * __i40e_get_coawesce - get pew-queue coawesce settings
 * @netdev: the netdev to check
 * @ec: ethtoow coawesce data stwuctuwe
 * @queue: which queue to pick
 *
 * Gets the pew-queue settings fow coawescence. Specificawwy Wx and Tx usecs
 * awe pew queue. If queue is <0 then we defauwt to queue 0 as the
 * wepwesentative vawue.
 **/
static int __i40e_get_coawesce(stwuct net_device *netdev,
			       stwuct ethtoow_coawesce *ec,
			       int queue)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_wing *wx_wing, *tx_wing;
	stwuct i40e_vsi *vsi = np->vsi;

	ec->tx_max_coawesced_fwames_iwq = vsi->wowk_wimit;

	/* wx and tx usecs has pew queue vawue. If usew doesn't specify the
	 * queue, wetuwn queue 0's vawue to wepwesent.
	 */
	if (queue < 0)
		queue = 0;
	ewse if (queue >= vsi->num_queue_paiws)
		wetuwn -EINVAW;

	wx_wing = vsi->wx_wings[queue];
	tx_wing = vsi->tx_wings[queue];

	if (ITW_IS_DYNAMIC(wx_wing->itw_setting))
		ec->use_adaptive_wx_coawesce = 1;

	if (ITW_IS_DYNAMIC(tx_wing->itw_setting))
		ec->use_adaptive_tx_coawesce = 1;

	ec->wx_coawesce_usecs = wx_wing->itw_setting & ~I40E_ITW_DYNAMIC;
	ec->tx_coawesce_usecs = tx_wing->itw_setting & ~I40E_ITW_DYNAMIC;

	/* we use the _usecs_high to stowe/set the intewwupt wate wimit
	 * that the hawdwawe suppowts, that awmost but not quite
	 * fits the owiginaw intent of the ethtoow vawiabwe,
	 * the wx_coawesce_usecs_high wimits totaw intewwupts
	 * pew second fwom both tx/wx souwces.
	 */
	ec->wx_coawesce_usecs_high = vsi->int_wate_wimit;
	ec->tx_coawesce_usecs_high = vsi->int_wate_wimit;

	wetuwn 0;
}

/**
 * i40e_get_coawesce - get a netdev's coawesce settings
 * @netdev: the netdev to check
 * @ec: ethtoow coawesce data stwuctuwe
 * @kewnew_coaw: ethtoow CQE mode setting stwuctuwe
 * @extack: extack fow wepowting ewwow messages
 *
 * Gets the coawesce settings fow a pawticuwaw netdev. Note that if usew has
 * modified pew-queue settings, this onwy guawantees to wepwesent queue 0. See
 * __i40e_get_coawesce fow mowe detaiws.
 **/
static int i40e_get_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ec,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	wetuwn __i40e_get_coawesce(netdev, ec, -1);
}

/**
 * i40e_get_pew_queue_coawesce - gets coawesce settings fow pawticuwaw queue
 * @netdev: netdev stwuctuwe
 * @ec: ethtoow's coawesce settings
 * @queue: the pawticuwaw queue to wead
 *
 * Wiww wead a specific queue's coawesce settings
 **/
static int i40e_get_pew_queue_coawesce(stwuct net_device *netdev, u32 queue,
				       stwuct ethtoow_coawesce *ec)
{
	wetuwn __i40e_get_coawesce(netdev, ec, queue);
}

/**
 * i40e_set_itw_pew_queue - set ITW vawues fow specific queue
 * @vsi: the VSI to set vawues fow
 * @ec: coawesce settings fwom ethtoow
 * @queue: the queue to modify
 *
 * Change the ITW settings fow a specific queue.
 **/
static void i40e_set_itw_pew_queue(stwuct i40e_vsi *vsi,
				   stwuct ethtoow_coawesce *ec,
				   int queue)
{
	stwuct i40e_wing *wx_wing = vsi->wx_wings[queue];
	stwuct i40e_wing *tx_wing = vsi->tx_wings[queue];
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	stwuct i40e_q_vectow *q_vectow;
	u16 intww;

	intww = i40e_intww_usec_to_weg(vsi->int_wate_wimit);

	wx_wing->itw_setting = ITW_WEG_AWIGN(ec->wx_coawesce_usecs);
	tx_wing->itw_setting = ITW_WEG_AWIGN(ec->tx_coawesce_usecs);

	if (ec->use_adaptive_wx_coawesce)
		wx_wing->itw_setting |= I40E_ITW_DYNAMIC;
	ewse
		wx_wing->itw_setting &= ~I40E_ITW_DYNAMIC;

	if (ec->use_adaptive_tx_coawesce)
		tx_wing->itw_setting |= I40E_ITW_DYNAMIC;
	ewse
		tx_wing->itw_setting &= ~I40E_ITW_DYNAMIC;

	q_vectow = wx_wing->q_vectow;
	q_vectow->wx.tawget_itw = ITW_TO_WEG(wx_wing->itw_setting);

	q_vectow = tx_wing->q_vectow;
	q_vectow->tx.tawget_itw = ITW_TO_WEG(tx_wing->itw_setting);

	/* The intewwupt handwew itsewf wiww take cawe of pwogwamming
	 * the Tx and Wx ITW vawues based on the vawues we have entewed
	 * into the q_vectow, no need to wwite the vawues now.
	 */

	ww32(hw, I40E_PFINT_WATEN(q_vectow->weg_idx), intww);
	i40e_fwush(hw);
}

/**
 * __i40e_set_coawesce - set coawesce settings fow pawticuwaw queue
 * @netdev: the netdev to change
 * @ec: ethtoow coawesce settings
 * @queue: the queue to change
 *
 * Sets the coawesce settings fow a pawticuwaw queue.
 **/
static int __i40e_set_coawesce(stwuct net_device *netdev,
			       stwuct ethtoow_coawesce *ec,
			       int queue)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	u16 intww_weg, cuw_wx_itw, cuw_tx_itw;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	int i;

	if (ec->tx_max_coawesced_fwames_iwq)
		vsi->wowk_wimit = ec->tx_max_coawesced_fwames_iwq;

	if (queue < 0) {
		cuw_wx_itw = vsi->wx_wings[0]->itw_setting;
		cuw_tx_itw = vsi->tx_wings[0]->itw_setting;
	} ewse if (queue < vsi->num_queue_paiws) {
		cuw_wx_itw = vsi->wx_wings[queue]->itw_setting;
		cuw_tx_itw = vsi->tx_wings[queue]->itw_setting;
	} ewse {
		netif_info(pf, dwv, netdev, "Invawid queue vawue, queue wange is 0 - %d\n",
			   vsi->num_queue_paiws - 1);
		wetuwn -EINVAW;
	}

	cuw_tx_itw &= ~I40E_ITW_DYNAMIC;
	cuw_wx_itw &= ~I40E_ITW_DYNAMIC;

	/* tx_coawesce_usecs_high is ignowed, use wx-usecs-high instead */
	if (ec->tx_coawesce_usecs_high != vsi->int_wate_wimit) {
		netif_info(pf, dwv, netdev, "tx-usecs-high is not used, pwease pwogwam wx-usecs-high\n");
		wetuwn -EINVAW;
	}

	if (ec->wx_coawesce_usecs_high > INTWW_WEG_TO_USEC(I40E_MAX_INTWW)) {
		netif_info(pf, dwv, netdev, "Invawid vawue, wx-usecs-high wange is 0-%wu\n",
			   INTWW_WEG_TO_USEC(I40E_MAX_INTWW));
		wetuwn -EINVAW;
	}

	if (ec->wx_coawesce_usecs != cuw_wx_itw &&
	    ec->use_adaptive_wx_coawesce) {
		netif_info(pf, dwv, netdev, "WX intewwupt modewation cannot be changed if adaptive-wx is enabwed.\n");
		wetuwn -EINVAW;
	}

	if (ec->wx_coawesce_usecs > I40E_MAX_ITW) {
		netif_info(pf, dwv, netdev, "Invawid vawue, wx-usecs wange is 0-8160\n");
		wetuwn -EINVAW;
	}

	if (ec->tx_coawesce_usecs != cuw_tx_itw &&
	    ec->use_adaptive_tx_coawesce) {
		netif_info(pf, dwv, netdev, "TX intewwupt modewation cannot be changed if adaptive-tx is enabwed.\n");
		wetuwn -EINVAW;
	}

	if (ec->tx_coawesce_usecs > I40E_MAX_ITW) {
		netif_info(pf, dwv, netdev, "Invawid vawue, tx-usecs wange is 0-8160\n");
		wetuwn -EINVAW;
	}

	if (ec->use_adaptive_wx_coawesce && !cuw_wx_itw)
		ec->wx_coawesce_usecs = I40E_MIN_ITW;

	if (ec->use_adaptive_tx_coawesce && !cuw_tx_itw)
		ec->tx_coawesce_usecs = I40E_MIN_ITW;

	intww_weg = i40e_intww_usec_to_weg(ec->wx_coawesce_usecs_high);
	vsi->int_wate_wimit = INTWW_WEG_TO_USEC(intww_weg);
	if (vsi->int_wate_wimit != ec->wx_coawesce_usecs_high) {
		netif_info(pf, dwv, netdev, "Intewwupt wate wimit wounded down to %d\n",
			   vsi->int_wate_wimit);
	}

	/* wx and tx usecs has pew queue vawue. If usew doesn't specify the
	 * queue, appwy to aww queues.
	 */
	if (queue < 0) {
		fow (i = 0; i < vsi->num_queue_paiws; i++)
			i40e_set_itw_pew_queue(vsi, ec, i);
	} ewse {
		i40e_set_itw_pew_queue(vsi, ec, queue);
	}

	wetuwn 0;
}

/**
 * i40e_set_coawesce - set coawesce settings fow evewy queue on the netdev
 * @netdev: the netdev to change
 * @ec: ethtoow coawesce settings
 * @kewnew_coaw: ethtoow CQE mode setting stwuctuwe
 * @extack: extack fow wepowting ewwow messages
 *
 * This wiww set each queue to the same coawesce settings.
 **/
static int i40e_set_coawesce(stwuct net_device *netdev,
			     stwuct ethtoow_coawesce *ec,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	wetuwn __i40e_set_coawesce(netdev, ec, -1);
}

/**
 * i40e_set_pew_queue_coawesce - set specific queue's coawesce settings
 * @netdev: the netdev to change
 * @ec: ethtoow's coawesce settings
 * @queue: the queue to change
 *
 * Sets the specified queue's coawesce settings.
 **/
static int i40e_set_pew_queue_coawesce(stwuct net_device *netdev, u32 queue,
				       stwuct ethtoow_coawesce *ec)
{
	wetuwn __i40e_set_coawesce(netdev, ec, queue);
}

/**
 * i40e_get_wss_hash_opts - Get WSS hash Input Set fow each fwow type
 * @pf: pointew to the physicaw function stwuct
 * @cmd: ethtoow wxnfc command
 *
 * Wetuwns Success if the fwow is suppowted, ewse Invawid Input.
 **/
static int i40e_get_wss_hash_opts(stwuct i40e_pf *pf, stwuct ethtoow_wxnfc *cmd)
{
	stwuct i40e_hw *hw = &pf->hw;
	u8 fwow_pctype = 0;
	u64 i_set = 0;

	cmd->data = 0;

	switch (cmd->fwow_type) {
	case TCP_V4_FWOW:
		fwow_pctype = I40E_FIWTEW_PCTYPE_NONF_IPV4_TCP;
		bweak;
	case UDP_V4_FWOW:
		fwow_pctype = I40E_FIWTEW_PCTYPE_NONF_IPV4_UDP;
		bweak;
	case TCP_V6_FWOW:
		fwow_pctype = I40E_FIWTEW_PCTYPE_NONF_IPV6_TCP;
		bweak;
	case UDP_V6_FWOW:
		fwow_pctype = I40E_FIWTEW_PCTYPE_NONF_IPV6_UDP;
		bweak;
	case SCTP_V4_FWOW:
	case AH_ESP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
	case IPV4_FWOW:
	case SCTP_V6_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
	case IPV6_FWOW:
		/* Defauwt is swc/dest fow IP, no mattew the W4 hashing */
		cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wead fwow based hash input set wegistew */
	if (fwow_pctype) {
		i_set = (u64)i40e_wead_wx_ctw(hw, I40E_GWQF_HASH_INSET(0,
					      fwow_pctype)) |
			((u64)i40e_wead_wx_ctw(hw, I40E_GWQF_HASH_INSET(1,
					       fwow_pctype)) << 32);
	}

	/* Pwocess bits of hash input set */
	if (i_set) {
		if (i_set & I40E_W4_SWC_MASK)
			cmd->data |= WXH_W4_B_0_1;
		if (i_set & I40E_W4_DST_MASK)
			cmd->data |= WXH_W4_B_2_3;

		if (cmd->fwow_type == TCP_V4_FWOW ||
		    cmd->fwow_type == UDP_V4_FWOW) {
			if (hw->mac.type == I40E_MAC_X722) {
				if (i_set & I40E_X722_W3_SWC_MASK)
					cmd->data |= WXH_IP_SWC;
				if (i_set & I40E_X722_W3_DST_MASK)
					cmd->data |= WXH_IP_DST;
			} ewse {
				if (i_set & I40E_W3_SWC_MASK)
					cmd->data |= WXH_IP_SWC;
				if (i_set & I40E_W3_DST_MASK)
					cmd->data |= WXH_IP_DST;
			}
		} ewse if (cmd->fwow_type == TCP_V6_FWOW ||
			  cmd->fwow_type == UDP_V6_FWOW) {
			if (i_set & I40E_W3_V6_SWC_MASK)
				cmd->data |= WXH_IP_SWC;
			if (i_set & I40E_W3_V6_DST_MASK)
				cmd->data |= WXH_IP_DST;
		}
	}

	wetuwn 0;
}

/**
 * i40e_check_mask - Check whethew a mask fiewd is set
 * @mask: the fuww mask vawue
 * @fiewd: mask of the fiewd to check
 *
 * If the given mask is fuwwy set, wetuwn positive vawue. If the mask fow the
 * fiewd is fuwwy unset, wetuwn zewo. Othewwise wetuwn a negative ewwow code.
 **/
static int i40e_check_mask(u64 mask, u64 fiewd)
{
	u64 vawue = mask & fiewd;

	if (vawue == fiewd)
		wetuwn 1;
	ewse if (!vawue)
		wetuwn 0;
	ewse
		wetuwn -1;
}

/**
 * i40e_pawse_wx_fwow_usew_data - Deconstwuct usew-defined data
 * @fsp: pointew to wx fwow specification
 * @data: pointew to usewdef data stwuctuwe fow stowage
 *
 * Wead the usew-defined data and deconstwuct the vawue into a stwuctuwe. No
 * othew code shouwd wead the usew-defined data, so as to ensuwe that evewy
 * pwace consistentwy weads the vawue cowwectwy.
 *
 * The usew-defined fiewd is a 64bit Big Endian fowmat vawue, which we
 * deconstwuct by weading bits ow bit fiewds fwom it. Singwe bit fwags shaww
 * be defined stawting fwom the highest bits, whiwe smaww bit fiewd vawues
 * shaww be defined stawting fwom the wowest bits.
 *
 * Wetuwns 0 if the data is vawid, and non-zewo if the usewdef data is invawid
 * and the fiwtew shouwd be wejected. The data stwuctuwe wiww awways be
 * modified even if FWOW_EXT is not set.
 *
 **/
static int i40e_pawse_wx_fwow_usew_data(stwuct ethtoow_wx_fwow_spec *fsp,
					stwuct i40e_wx_fwow_usewdef *data)
{
	u64 vawue, mask;
	int vawid;

	/* Zewo memowy fiwst so it's awways consistent. */
	memset(data, 0, sizeof(*data));

	if (!(fsp->fwow_type & FWOW_EXT))
		wetuwn 0;

	vawue = be64_to_cpu(*((__be64 *)fsp->h_ext.data));
	mask = be64_to_cpu(*((__be64 *)fsp->m_ext.data));

#define I40E_USEWDEF_FWEX_WOWD		GENMASK_UWW(15, 0)
#define I40E_USEWDEF_FWEX_OFFSET	GENMASK_UWW(31, 16)
#define I40E_USEWDEF_FWEX_FIWTEW	GENMASK_UWW(31, 0)

	vawid = i40e_check_mask(mask, I40E_USEWDEF_FWEX_FIWTEW);
	if (vawid < 0) {
		wetuwn -EINVAW;
	} ewse if (vawid) {
		data->fwex_wowd = vawue & I40E_USEWDEF_FWEX_WOWD;
		data->fwex_offset =
			FIEWD_GET(I40E_USEWDEF_FWEX_OFFSET, vawue);
		data->fwex_fiwtew = twue;
	}

	wetuwn 0;
}

/**
 * i40e_fiww_wx_fwow_usew_data - Fiww in usew-defined data fiewd
 * @fsp: pointew to wx_fwow specification
 * @data: pointew to wetuwn usewdef data
 *
 * Weads the usewdef data stwuctuwe and pwopewwy fiwws in the usew defined
 * fiewds of the wx_fwow_spec.
 **/
static void i40e_fiww_wx_fwow_usew_data(stwuct ethtoow_wx_fwow_spec *fsp,
					stwuct i40e_wx_fwow_usewdef *data)
{
	u64 vawue = 0, mask = 0;

	if (data->fwex_fiwtew) {
		vawue |= data->fwex_wowd;
		vawue |= (u64)data->fwex_offset << 16;
		mask |= I40E_USEWDEF_FWEX_FIWTEW;
	}

	if (vawue || mask)
		fsp->fwow_type |= FWOW_EXT;

	*((__be64 *)fsp->h_ext.data) = cpu_to_be64(vawue);
	*((__be64 *)fsp->m_ext.data) = cpu_to_be64(mask);
}

/**
 * i40e_get_ethtoow_fdiw_aww - Popuwates the wuwe count of a command
 * @pf: Pointew to the physicaw function stwuct
 * @cmd: The command to get ow set Wx fwow cwassification wuwes
 * @wuwe_wocs: Awway of used wuwe wocations
 *
 * This function popuwates both the totaw and actuaw wuwe count of
 * the ethtoow fwow cwassification command
 *
 * Wetuwns 0 on success ow -EMSGSIZE if entwy not found
 **/
static int i40e_get_ethtoow_fdiw_aww(stwuct i40e_pf *pf,
				     stwuct ethtoow_wxnfc *cmd,
				     u32 *wuwe_wocs)
{
	stwuct i40e_fdiw_fiwtew *wuwe;
	stwuct hwist_node *node2;
	int cnt = 0;

	/* wepowt totaw wuwe count */
	cmd->data = i40e_get_fd_cnt_aww(pf);

	hwist_fow_each_entwy_safe(wuwe, node2,
				  &pf->fdiw_fiwtew_wist, fdiw_node) {
		if (cnt == cmd->wuwe_cnt)
			wetuwn -EMSGSIZE;

		wuwe_wocs[cnt] = wuwe->fd_id;
		cnt++;
	}

	cmd->wuwe_cnt = cnt;

	wetuwn 0;
}

/**
 * i40e_get_ethtoow_fdiw_entwy - Wook up a fiwtew based on Wx fwow
 * @pf: Pointew to the physicaw function stwuct
 * @cmd: The command to get ow set Wx fwow cwassification wuwes
 *
 * This function wooks up a fiwtew based on the Wx fwow cwassification
 * command and fiwws the fwow spec info fow it if found
 *
 * Wetuwns 0 on success ow -EINVAW if fiwtew not found
 **/
static int i40e_get_ethtoow_fdiw_entwy(stwuct i40e_pf *pf,
				       stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp =
			(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct i40e_wx_fwow_usewdef usewdef = {0};
	stwuct i40e_fdiw_fiwtew *wuwe = NUWW;
	stwuct hwist_node *node2;
	u64 input_set;
	u16 index;

	hwist_fow_each_entwy_safe(wuwe, node2,
				  &pf->fdiw_fiwtew_wist, fdiw_node) {
		if (fsp->wocation <= wuwe->fd_id)
			bweak;
	}

	if (!wuwe || fsp->wocation != wuwe->fd_id)
		wetuwn -EINVAW;

	fsp->fwow_type = wuwe->fwow_type;
	if (fsp->fwow_type == IP_USEW_FWOW) {
		fsp->h_u.usw_ip4_spec.ip_vew = ETH_WX_NFC_IP4;
		fsp->h_u.usw_ip4_spec.pwoto = 0;
		fsp->m_u.usw_ip4_spec.pwoto = 0;
	}

	if (fsp->fwow_type == IPV6_USEW_FWOW ||
	    fsp->fwow_type == UDP_V6_FWOW ||
	    fsp->fwow_type == TCP_V6_FWOW ||
	    fsp->fwow_type == SCTP_V6_FWOW) {
		/* Wevewse the swc and dest notion, since the HW views them
		 * fwom Tx pewspective whewe as the usew expects it fwom
		 * Wx fiwtew view.
		 */
		fsp->h_u.tcp_ip6_spec.pswc = wuwe->dst_powt;
		fsp->h_u.tcp_ip6_spec.pdst = wuwe->swc_powt;
		memcpy(fsp->h_u.tcp_ip6_spec.ip6dst, wuwe->swc_ip6,
		       sizeof(__be32) * 4);
		memcpy(fsp->h_u.tcp_ip6_spec.ip6swc, wuwe->dst_ip6,
		       sizeof(__be32) * 4);
	} ewse {
		/* Wevewse the swc and dest notion, since the HW views them
		 * fwom Tx pewspective whewe as the usew expects it fwom
		 * Wx fiwtew view.
		 */
		fsp->h_u.tcp_ip4_spec.pswc = wuwe->dst_powt;
		fsp->h_u.tcp_ip4_spec.pdst = wuwe->swc_powt;
		fsp->h_u.tcp_ip4_spec.ip4swc = wuwe->dst_ip;
		fsp->h_u.tcp_ip4_spec.ip4dst = wuwe->swc_ip;
	}

	switch (wuwe->fwow_type) {
	case SCTP_V4_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_SCTP;
		bweak;
	case TCP_V4_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_TCP;
		bweak;
	case UDP_V4_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_UDP;
		bweak;
	case SCTP_V6_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_SCTP;
		bweak;
	case TCP_V6_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_TCP;
		bweak;
	case UDP_V6_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_UDP;
		bweak;
	case IP_USEW_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_OTHEW;
		bweak;
	case IPV6_USEW_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_OTHEW;
		bweak;
	defauwt:
		/* If we have stowed a fiwtew with a fwow type not wisted hewe
		 * it is awmost cewtainwy a dwivew bug. WAWN(), and then
		 * assign the input_set as if aww fiewds awe enabwed to avoid
		 * weading unassigned memowy.
		 */
		WAWN(1, "Missing input set index fow fwow_type %d\n",
		     wuwe->fwow_type);
		input_set = 0xFFFFFFFFFFFFFFFFUWW;
		goto no_input_set;
	}

	input_set = i40e_wead_fd_input_set(pf, index);

no_input_set:
	if (input_set & I40E_W3_V6_SWC_MASK) {
		fsp->m_u.tcp_ip6_spec.ip6swc[0] = htonw(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6swc[1] = htonw(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6swc[2] = htonw(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6swc[3] = htonw(0xFFFFFFFF);
	}

	if (input_set & I40E_W3_V6_DST_MASK) {
		fsp->m_u.tcp_ip6_spec.ip6dst[0] = htonw(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6dst[1] = htonw(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6dst[2] = htonw(0xFFFFFFFF);
		fsp->m_u.tcp_ip6_spec.ip6dst[3] = htonw(0xFFFFFFFF);
	}

	if (input_set & I40E_W3_SWC_MASK)
		fsp->m_u.tcp_ip4_spec.ip4swc = htonw(0xFFFFFFFF);

	if (input_set & I40E_W3_DST_MASK)
		fsp->m_u.tcp_ip4_spec.ip4dst = htonw(0xFFFFFFFF);

	if (input_set & I40E_W4_SWC_MASK)
		fsp->m_u.tcp_ip4_spec.pswc = htons(0xFFFF);

	if (input_set & I40E_W4_DST_MASK)
		fsp->m_u.tcp_ip4_spec.pdst = htons(0xFFFF);

	if (wuwe->dest_ctw == I40E_FIWTEW_PWOGWAM_DESC_DEST_DWOP_PACKET)
		fsp->wing_cookie = WX_CWS_FWOW_DISC;
	ewse
		fsp->wing_cookie = wuwe->q_index;

	if (wuwe->vwan_tag) {
		fsp->h_ext.vwan_etype = wuwe->vwan_etype;
		fsp->m_ext.vwan_etype = htons(0xFFFF);
		fsp->h_ext.vwan_tci = wuwe->vwan_tag;
		fsp->m_ext.vwan_tci = htons(0xFFFF);
		fsp->fwow_type |= FWOW_EXT;
	}

	if (wuwe->dest_vsi != pf->vsi[pf->wan_vsi]->id) {
		stwuct i40e_vsi *vsi;

		vsi = i40e_find_vsi_fwom_id(pf, wuwe->dest_vsi);
		if (vsi && vsi->type == I40E_VSI_SWIOV) {
			/* VFs awe zewo-indexed by the dwivew, but ethtoow
			 * expects them to be one-indexed, so add one hewe
			 */
			u64 wing_vf = vsi->vf_id + 1;

			wing_vf <<= ETHTOOW_WX_FWOW_SPEC_WING_VF_OFF;
			fsp->wing_cookie |= wing_vf;
		}
	}

	if (wuwe->fwex_fiwtew) {
		usewdef.fwex_fiwtew = twue;
		usewdef.fwex_wowd = be16_to_cpu(wuwe->fwex_wowd);
		usewdef.fwex_offset = wuwe->fwex_offset;
	}

	i40e_fiww_wx_fwow_usew_data(fsp, &usewdef);

	wetuwn 0;
}

/**
 * i40e_get_wxnfc - command to get WX fwow cwassification wuwes
 * @netdev: netwowk intewface device stwuctuwe
 * @cmd: ethtoow wxnfc command
 * @wuwe_wocs: pointew to stowe wuwe data
 *
 * Wetuwns Success if the command is suppowted.
 **/
static int i40e_get_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *cmd,
			  u32 *wuwe_wocs)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = vsi->wss_size;
		wet = 0;
		bweak;
	case ETHTOOW_GWXFH:
		wet = i40e_get_wss_hash_opts(pf, cmd);
		bweak;
	case ETHTOOW_GWXCWSWWCNT:
		cmd->wuwe_cnt = pf->fdiw_pf_active_fiwtews;
		/* wepowt totaw wuwe count */
		cmd->data = i40e_get_fd_cnt_aww(pf);
		wet = 0;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		wet = i40e_get_ethtoow_fdiw_entwy(pf, cmd);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		wet = i40e_get_ethtoow_fdiw_aww(pf, cmd, wuwe_wocs);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/**
 * i40e_get_wss_hash_bits - Wead WSS Hash bits fwom wegistew
 * @hw: hw stwuctuwe
 * @nfc: pointew to usew wequest
 * @i_setc: bits cuwwentwy set
 *
 * Wetuwns vawue of bits to be set pew usew wequest
 **/
static u64 i40e_get_wss_hash_bits(stwuct i40e_hw *hw,
				  stwuct ethtoow_wxnfc *nfc,
				  u64 i_setc)
{
	u64 i_set = i_setc;
	u64 swc_w3 = 0, dst_w3 = 0;

	if (nfc->data & WXH_W4_B_0_1)
		i_set |= I40E_W4_SWC_MASK;
	ewse
		i_set &= ~I40E_W4_SWC_MASK;
	if (nfc->data & WXH_W4_B_2_3)
		i_set |= I40E_W4_DST_MASK;
	ewse
		i_set &= ~I40E_W4_DST_MASK;

	if (nfc->fwow_type == TCP_V6_FWOW || nfc->fwow_type == UDP_V6_FWOW) {
		swc_w3 = I40E_W3_V6_SWC_MASK;
		dst_w3 = I40E_W3_V6_DST_MASK;
	} ewse if (nfc->fwow_type == TCP_V4_FWOW ||
		  nfc->fwow_type == UDP_V4_FWOW) {
		if (hw->mac.type == I40E_MAC_X722) {
			swc_w3 = I40E_X722_W3_SWC_MASK;
			dst_w3 = I40E_X722_W3_DST_MASK;
		} ewse {
			swc_w3 = I40E_W3_SWC_MASK;
			dst_w3 = I40E_W3_DST_MASK;
		}
	} ewse {
		/* Any othew fwow type awe not suppowted hewe */
		wetuwn i_set;
	}

	if (nfc->data & WXH_IP_SWC)
		i_set |= swc_w3;
	ewse
		i_set &= ~swc_w3;
	if (nfc->data & WXH_IP_DST)
		i_set |= dst_w3;
	ewse
		i_set &= ~dst_w3;

	wetuwn i_set;
}

#define FWOW_PCTYPES_SIZE 64
/**
 * i40e_set_wss_hash_opt - Enabwe/Disabwe fwow types fow WSS hash
 * @pf: pointew to the physicaw function stwuct
 * @nfc: ethtoow wxnfc command
 *
 * Wetuwns Success if the fwow input set is suppowted.
 **/
static int i40e_set_wss_hash_opt(stwuct i40e_pf *pf, stwuct ethtoow_wxnfc *nfc)
{
	stwuct i40e_hw *hw = &pf->hw;
	u64 hena = (u64)i40e_wead_wx_ctw(hw, I40E_PFQF_HENA(0)) |
		   ((u64)i40e_wead_wx_ctw(hw, I40E_PFQF_HENA(1)) << 32);
	DECWAWE_BITMAP(fwow_pctypes, FWOW_PCTYPES_SIZE);
	u64 i_set, i_setc;

	bitmap_zewo(fwow_pctypes, FWOW_PCTYPES_SIZE);

	if (test_bit(I40E_FWAG_MFP_ENA, pf->fwags)) {
		dev_eww(&pf->pdev->dev,
			"Change of WSS hash input set is not suppowted when MFP mode is enabwed\n");
		wetuwn -EOPNOTSUPP;
	}

	/* WSS does not suppowt anything othew than hashing
	 * to queues on swc and dst IPs and powts
	 */
	if (nfc->data & ~(WXH_IP_SWC | WXH_IP_DST |
			  WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EINVAW;

	switch (nfc->fwow_type) {
	case TCP_V4_FWOW:
		set_bit(I40E_FIWTEW_PCTYPE_NONF_IPV4_TCP, fwow_pctypes);
		if (test_bit(I40E_HW_CAP_MUWTI_TCP_UDP_WSS_PCTYPE,
			     pf->hw.caps))
			set_bit(I40E_FIWTEW_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK,
				fwow_pctypes);
		bweak;
	case TCP_V6_FWOW:
		set_bit(I40E_FIWTEW_PCTYPE_NONF_IPV6_TCP, fwow_pctypes);
		if (test_bit(I40E_HW_CAP_MUWTI_TCP_UDP_WSS_PCTYPE,
			     pf->hw.caps))
			set_bit(I40E_FIWTEW_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK,
				fwow_pctypes);
		bweak;
	case UDP_V4_FWOW:
		set_bit(I40E_FIWTEW_PCTYPE_NONF_IPV4_UDP, fwow_pctypes);
		if (test_bit(I40E_HW_CAP_MUWTI_TCP_UDP_WSS_PCTYPE,
			     pf->hw.caps)) {
			set_bit(I40E_FIWTEW_PCTYPE_NONF_UNICAST_IPV4_UDP,
				fwow_pctypes);
			set_bit(I40E_FIWTEW_PCTYPE_NONF_MUWTICAST_IPV4_UDP,
				fwow_pctypes);
		}
		hena |= BIT_UWW(I40E_FIWTEW_PCTYPE_FWAG_IPV4);
		bweak;
	case UDP_V6_FWOW:
		set_bit(I40E_FIWTEW_PCTYPE_NONF_IPV6_UDP, fwow_pctypes);
		if (test_bit(I40E_HW_CAP_MUWTI_TCP_UDP_WSS_PCTYPE,
			     pf->hw.caps)) {
			set_bit(I40E_FIWTEW_PCTYPE_NONF_UNICAST_IPV6_UDP,
				fwow_pctypes);
			set_bit(I40E_FIWTEW_PCTYPE_NONF_MUWTICAST_IPV6_UDP,
				fwow_pctypes);
		}
		hena |= BIT_UWW(I40E_FIWTEW_PCTYPE_FWAG_IPV6);
		bweak;
	case AH_ESP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
	case SCTP_V4_FWOW:
		if ((nfc->data & WXH_W4_B_0_1) ||
		    (nfc->data & WXH_W4_B_2_3))
			wetuwn -EINVAW;
		hena |= BIT_UWW(I40E_FIWTEW_PCTYPE_NONF_IPV4_OTHEW);
		bweak;
	case AH_ESP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
	case SCTP_V6_FWOW:
		if ((nfc->data & WXH_W4_B_0_1) ||
		    (nfc->data & WXH_W4_B_2_3))
			wetuwn -EINVAW;
		hena |= BIT_UWW(I40E_FIWTEW_PCTYPE_NONF_IPV6_OTHEW);
		bweak;
	case IPV4_FWOW:
		hena |= BIT_UWW(I40E_FIWTEW_PCTYPE_NONF_IPV4_OTHEW) |
			BIT_UWW(I40E_FIWTEW_PCTYPE_FWAG_IPV4);
		bweak;
	case IPV6_FWOW:
		hena |= BIT_UWW(I40E_FIWTEW_PCTYPE_NONF_IPV6_OTHEW) |
			BIT_UWW(I40E_FIWTEW_PCTYPE_FWAG_IPV6);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (bitmap_weight(fwow_pctypes, FWOW_PCTYPES_SIZE)) {
		u8 fwow_id;

		fow_each_set_bit(fwow_id, fwow_pctypes, FWOW_PCTYPES_SIZE) {
			i_setc = (u64)i40e_wead_wx_ctw(hw, I40E_GWQF_HASH_INSET(0, fwow_id)) |
				 ((u64)i40e_wead_wx_ctw(hw, I40E_GWQF_HASH_INSET(1, fwow_id)) << 32);
			i_set = i40e_get_wss_hash_bits(&pf->hw, nfc, i_setc);

			i40e_wwite_wx_ctw(hw, I40E_GWQF_HASH_INSET(0, fwow_id),
					  (u32)i_set);
			i40e_wwite_wx_ctw(hw, I40E_GWQF_HASH_INSET(1, fwow_id),
					  (u32)(i_set >> 32));
			hena |= BIT_UWW(fwow_id);
		}
	}

	i40e_wwite_wx_ctw(hw, I40E_PFQF_HENA(0), (u32)hena);
	i40e_wwite_wx_ctw(hw, I40E_PFQF_HENA(1), (u32)(hena >> 32));
	i40e_fwush(hw);

	wetuwn 0;
}

/**
 * i40e_update_ethtoow_fdiw_entwy - Updates the fdiw fiwtew entwy
 * @vsi: Pointew to the tawgeted VSI
 * @input: The fiwtew to update ow NUWW to indicate dewetion
 * @sw_idx: Softwawe index to the fiwtew
 * @cmd: The command to get ow set Wx fwow cwassification wuwes
 *
 * This function updates (ow dewetes) a Fwow Diwectow entwy fwom
 * the hwist of the cowwesponding PF
 *
 * Wetuwns 0 on success
 **/
static int i40e_update_ethtoow_fdiw_entwy(stwuct i40e_vsi *vsi,
					  stwuct i40e_fdiw_fiwtew *input,
					  u16 sw_idx,
					  stwuct ethtoow_wxnfc *cmd)
{
	stwuct i40e_fdiw_fiwtew *wuwe, *pawent;
	stwuct i40e_pf *pf = vsi->back;
	stwuct hwist_node *node2;
	int eww = -EINVAW;

	pawent = NUWW;
	wuwe = NUWW;

	hwist_fow_each_entwy_safe(wuwe, node2,
				  &pf->fdiw_fiwtew_wist, fdiw_node) {
		/* hash found, ow no matching entwy */
		if (wuwe->fd_id >= sw_idx)
			bweak;
		pawent = wuwe;
	}

	/* if thewe is an owd wuwe occupying ouw pwace wemove it */
	if (wuwe && (wuwe->fd_id == sw_idx)) {
		/* Wemove this wuwe, since we'we eithew deweting it, ow
		 * wepwacing it.
		 */
		eww = i40e_add_dew_fdiw(vsi, wuwe, fawse);
		hwist_dew(&wuwe->fdiw_node);
		kfwee(wuwe);
		pf->fdiw_pf_active_fiwtews--;
	}

	/* If we wewen't given an input, this is a dewete, so just wetuwn the
	 * ewwow code indicating if thewe was an entwy at the wequested swot
	 */
	if (!input)
		wetuwn eww;

	/* Othewwise, instaww the new wuwe as wequested */
	INIT_HWIST_NODE(&input->fdiw_node);

	/* add fiwtew to the wist */
	if (pawent)
		hwist_add_behind(&input->fdiw_node, &pawent->fdiw_node);
	ewse
		hwist_add_head(&input->fdiw_node,
			       &pf->fdiw_fiwtew_wist);

	/* update counts */
	pf->fdiw_pf_active_fiwtews++;

	wetuwn 0;
}

/**
 * i40e_pwune_fwex_pit_wist - Cweanup unused entwies in FWX_PIT tabwe
 * @pf: pointew to PF stwuctuwe
 *
 * This function seawches the wist of fiwtews and detewmines which FWX_PIT
 * entwies awe stiww wequiwed. It wiww pwune any entwies which awe no wongew
 * in use aftew the dewetion.
 **/
static void i40e_pwune_fwex_pit_wist(stwuct i40e_pf *pf)
{
	stwuct i40e_fwex_pit *entwy, *tmp;
	stwuct i40e_fdiw_fiwtew *wuwe;

	/* Fiwst, we'ww check the w3 tabwe */
	wist_fow_each_entwy_safe(entwy, tmp, &pf->w3_fwex_pit_wist, wist) {
		boow found = fawse;

		hwist_fow_each_entwy(wuwe, &pf->fdiw_fiwtew_wist, fdiw_node) {
			if (wuwe->fwow_type != IP_USEW_FWOW)
				continue;
			if (wuwe->fwex_fiwtew &&
			    wuwe->fwex_offset == entwy->swc_offset) {
				found = twue;
				bweak;
			}
		}

		/* If we didn't find the fiwtew, then we can pwune this entwy
		 * fwom the wist.
		 */
		if (!found) {
			wist_dew(&entwy->wist);
			kfwee(entwy);
		}
	}

	/* Fowwowed by the W4 tabwe */
	wist_fow_each_entwy_safe(entwy, tmp, &pf->w4_fwex_pit_wist, wist) {
		boow found = fawse;

		hwist_fow_each_entwy(wuwe, &pf->fdiw_fiwtew_wist, fdiw_node) {
			/* Skip this fiwtew if it's W3, since we awweady
			 * checked those in the above woop
			 */
			if (wuwe->fwow_type == IP_USEW_FWOW)
				continue;
			if (wuwe->fwex_fiwtew &&
			    wuwe->fwex_offset == entwy->swc_offset) {
				found = twue;
				bweak;
			}
		}

		/* If we didn't find the fiwtew, then we can pwune this entwy
		 * fwom the wist.
		 */
		if (!found) {
			wist_dew(&entwy->wist);
			kfwee(entwy);
		}
	}
}

/**
 * i40e_dew_fdiw_entwy - Dewetes a Fwow Diwectow fiwtew entwy
 * @vsi: Pointew to the tawgeted VSI
 * @cmd: The command to get ow set Wx fwow cwassification wuwes
 *
 * The function wemoves a Fwow Diwectow fiwtew entwy fwom the
 * hwist of the cowwesponding PF
 *
 * Wetuwns 0 on success
 */
static int i40e_dew_fdiw_entwy(stwuct i40e_vsi *vsi,
			       stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct i40e_pf *pf = vsi->back;
	int wet = 0;

	if (test_bit(__I40E_WESET_WECOVEWY_PENDING, pf->state) ||
	    test_bit(__I40E_WESET_INTW_WECEIVED, pf->state))
		wetuwn -EBUSY;

	if (test_bit(__I40E_FD_FWUSH_WEQUESTED, pf->state))
		wetuwn -EBUSY;

	wet = i40e_update_ethtoow_fdiw_entwy(vsi, NUWW, fsp->wocation, cmd);

	i40e_pwune_fwex_pit_wist(pf);

	i40e_fdiw_check_and_weenabwe(pf);
	wetuwn wet;
}

/**
 * i40e_unused_pit_index - Find an unused PIT index fow given wist
 * @pf: the PF data stwuctuwe
 *
 * Find the fiwst unused fwexibwe PIT index entwy. We seawch both the W3 and
 * W4 fwexibwe PIT wists so that the wetuwned index is unique and unused by
 * eithew cuwwentwy pwogwammed W3 ow W4 fiwtews. We use a bit fiewd as stowage
 * to twack which indexes awe awweady used.
 **/
static u8 i40e_unused_pit_index(stwuct i40e_pf *pf)
{
	unsigned wong avaiwabwe_index = 0xFF;
	stwuct i40e_fwex_pit *entwy;

	/* We need to make suwe that the new index isn't in use by eithew W3
	 * ow W4 fiwtews so that IP_USEW_FWOW fiwtews can pwogwam both W3 and
	 * W4 to use the same index.
	 */

	wist_fow_each_entwy(entwy, &pf->w4_fwex_pit_wist, wist)
		cweaw_bit(entwy->pit_index, &avaiwabwe_index);

	wist_fow_each_entwy(entwy, &pf->w3_fwex_pit_wist, wist)
		cweaw_bit(entwy->pit_index, &avaiwabwe_index);

	wetuwn find_fiwst_bit(&avaiwabwe_index, 8);
}

/**
 * i40e_find_fwex_offset - Find an existing fwex swc_offset
 * @fwex_pit_wist: W3 ow W4 fwex PIT wist
 * @swc_offset: new swc_offset to find
 *
 * Seawches the fwex_pit_wist fow an existing offset. If no offset is
 * cuwwentwy pwogwammed, then this wiww wetuwn an EWW_PTW if thewe is no space
 * to add a new offset, othewwise it wetuwns NUWW.
 **/
static
stwuct i40e_fwex_pit *i40e_find_fwex_offset(stwuct wist_head *fwex_pit_wist,
					    u16 swc_offset)
{
	stwuct i40e_fwex_pit *entwy;
	int size = 0;

	/* Seawch fow the swc_offset fiwst. If we find a matching entwy
	 * awweady pwogwammed, we can simpwy we-use it.
	 */
	wist_fow_each_entwy(entwy, fwex_pit_wist, wist) {
		size++;
		if (entwy->swc_offset == swc_offset)
			wetuwn entwy;
	}

	/* If we haven't found an entwy yet, then the pwovided swc offset has
	 * not yet been pwogwammed. We wiww pwogwam the swc offset watew on,
	 * but we need to indicate whethew thewe is enough space to do so
	 * hewe. We'ww make use of EWW_PTW fow this puwpose.
	 */
	if (size >= I40E_FWEX_PIT_TABWE_SIZE)
		wetuwn EWW_PTW(-ENOSPC);

	wetuwn NUWW;
}

/**
 * i40e_add_fwex_offset - Add swc_offset to fwex PIT tabwe wist
 * @fwex_pit_wist: W3 ow W4 fwex PIT wist
 * @swc_offset: new swc_offset to add
 * @pit_index: the PIT index to pwogwam
 *
 * This function pwogwams the new swc_offset to the wist. It is expected that
 * i40e_find_fwex_offset has awweady been twied and wetuwned NUWW, indicating
 * that this offset is not pwogwammed, and that the wist has enough space to
 * stowe anothew offset.
 *
 * Wetuwns 0 on success, and negative vawue on ewwow.
 **/
static int i40e_add_fwex_offset(stwuct wist_head *fwex_pit_wist,
				u16 swc_offset,
				u8 pit_index)
{
	stwuct i40e_fwex_pit *new_pit, *entwy;

	new_pit = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!new_pit)
		wetuwn -ENOMEM;

	new_pit->swc_offset = swc_offset;
	new_pit->pit_index = pit_index;

	/* We need to insewt this item such that the wist is sowted by
	 * swc_offset in ascending owdew.
	 */
	wist_fow_each_entwy(entwy, fwex_pit_wist, wist) {
		if (new_pit->swc_offset < entwy->swc_offset) {
			wist_add_taiw(&new_pit->wist, &entwy->wist);
			wetuwn 0;
		}

		/* If we found an entwy with ouw offset awweady pwogwammed we
		 * can simpwy wetuwn hewe, aftew fweeing the memowy. Howevew,
		 * if the pit_index does not match we need to wepowt an ewwow.
		 */
		if (new_pit->swc_offset == entwy->swc_offset) {
			int eww = 0;

			/* If the PIT index is not the same we can't we-use
			 * the entwy, so we must wepowt an ewwow.
			 */
			if (new_pit->pit_index != entwy->pit_index)
				eww = -EINVAW;

			kfwee(new_pit);
			wetuwn eww;
		}
	}

	/* If we weached hewe, then we haven't yet added the item. This means
	 * that we shouwd add the item at the end of the wist.
	 */
	wist_add_taiw(&new_pit->wist, fwex_pit_wist);
	wetuwn 0;
}

/**
 * __i40e_wepwogwam_fwex_pit - We-pwogwam specific FWX_PIT tabwe
 * @pf: Pointew to the PF stwuctuwe
 * @fwex_pit_wist: wist of fwexibwe swc offsets in use
 * @fwex_pit_stawt: index to fiwst entwy fow this section of the tabwe
 *
 * In owdew to handwe fwexibwe data, the hawdwawe uses a tabwe of vawues
 * cawwed the FWX_PIT tabwe. This tabwe is used to indicate which sections of
 * the input cowwespond to what PIT index vawues. Unfowtunatewy, hawdwawe is
 * vewy westwictive about pwogwamming this tabwe. Entwies must be owdewed by
 * swc_offset in ascending owdew, without dupwicates. Additionawwy, unused
 * entwies must be set to the unused index vawue, and must have vawid size and
 * wength accowding to the swc_offset owdewing.
 *
 * This function wiww wepwogwam the FWX_PIT wegistew fwom a book-keeping
 * stwuctuwe that we guawantee is awweady owdewed cowwectwy, and has no mowe
 * than 3 entwies.
 *
 * To make things easiew, we onwy suppowt fwexibwe vawues of one wowd wength,
 * wathew than awwowing vawiabwe wength fwexibwe vawues.
 **/
static void __i40e_wepwogwam_fwex_pit(stwuct i40e_pf *pf,
				      stwuct wist_head *fwex_pit_wist,
				      int fwex_pit_stawt)
{
	stwuct i40e_fwex_pit *entwy = NUWW;
	u16 wast_offset = 0;
	int i = 0, j = 0;

	/* Fiwst, woop ovew the wist of fwex PIT entwies, and wepwogwam the
	 * wegistews.
	 */
	wist_fow_each_entwy(entwy, fwex_pit_wist, wist) {
		/* We have to be cawefuw when pwogwamming vawues fow the
		 * wawgest SWC_OFFSET vawue. It is possibwe that adding
		 * additionaw empty vawues at the end wouwd ovewfwow the space
		 * fow the SWC_OFFSET in the FWX_PIT wegistew. To avoid this,
		 * we check hewe and add the empty vawues pwiow to adding the
		 * wawgest vawue.
		 *
		 * To detewmine this, we wiww use a woop fwom i+1 to 3, which
		 * wiww detewmine whethew the unused entwies wouwd have vawid
		 * SWC_OFFSET. Note that thewe cannot be extwa entwies past
		 * this vawue, because the onwy vawid vawues wouwd have been
		 * wawgew than I40E_MAX_FWEX_SWC_OFFSET, and thus wouwd not
		 * have been added to the wist in the fiwst pwace.
		 */
		fow (j = i + 1; j < 3; j++) {
			u16 offset = entwy->swc_offset + j;
			int index = fwex_pit_stawt + i;
			u32 vawue = I40E_FWEX_PWEP_VAW(I40E_FWEX_DEST_UNUSED,
						       1,
						       offset - 3);

			if (offset > I40E_MAX_FWEX_SWC_OFFSET) {
				i40e_wwite_wx_ctw(&pf->hw,
						  I40E_PWTQF_FWX_PIT(index),
						  vawue);
				i++;
			}
		}

		/* Now, we can pwogwam the actuaw vawue into the tabwe */
		i40e_wwite_wx_ctw(&pf->hw,
				  I40E_PWTQF_FWX_PIT(fwex_pit_stawt + i),
				  I40E_FWEX_PWEP_VAW(entwy->pit_index + 50,
						     1,
						     entwy->swc_offset));
		i++;
	}

	/* In owdew to pwogwam the wast entwies in the tabwe, we need to
	 * detewmine the vawid offset. If the wist is empty, we'ww just stawt
	 * with 0. Othewwise, we'ww stawt with the wast item offset and add 1.
	 * This ensuwes that aww entwies have vawid sizes. If we don't do this
	 * cowwectwy, the hawdwawe wiww disabwe fwexibwe fiewd pawsing.
	 */
	if (!wist_empty(fwex_pit_wist))
		wast_offset = wist_pwev_entwy(entwy, wist)->swc_offset + 1;

	fow (; i < 3; i++, wast_offset++) {
		i40e_wwite_wx_ctw(&pf->hw,
				  I40E_PWTQF_FWX_PIT(fwex_pit_stawt + i),
				  I40E_FWEX_PWEP_VAW(I40E_FWEX_DEST_UNUSED,
						     1,
						     wast_offset));
	}
}

/**
 * i40e_wepwogwam_fwex_pit - Wepwogwam aww FWX_PIT tabwes aftew input set change
 * @pf: pointew to the PF stwuctuwe
 *
 * This function wepwogwams both the W3 and W4 FWX_PIT tabwes. See the
 * intewnaw hewpew function fow impwementation detaiws.
 **/
static void i40e_wepwogwam_fwex_pit(stwuct i40e_pf *pf)
{
	__i40e_wepwogwam_fwex_pit(pf, &pf->w3_fwex_pit_wist,
				  I40E_FWEX_PIT_IDX_STAWT_W3);

	__i40e_wepwogwam_fwex_pit(pf, &pf->w4_fwex_pit_wist,
				  I40E_FWEX_PIT_IDX_STAWT_W4);

	/* We awso need to pwogwam the W3 and W4 GWQF OWT wegistew */
	i40e_wwite_wx_ctw(&pf->hw,
			  I40E_GWQF_OWT(I40E_W3_GWQF_OWT_IDX),
			  I40E_OWT_PWEP_VAW(I40E_FWEX_PIT_IDX_STAWT_W3,
					    3, 1));

	i40e_wwite_wx_ctw(&pf->hw,
			  I40E_GWQF_OWT(I40E_W4_GWQF_OWT_IDX),
			  I40E_OWT_PWEP_VAW(I40E_FWEX_PIT_IDX_STAWT_W4,
					    3, 1));
}

/**
 * i40e_fwow_stw - Convewts a fwow_type into a human weadabwe stwing
 * @fsp: the fwow specification
 *
 * Cuwwentwy onwy fwow types we suppowt awe incwuded hewe, and the stwing
 * vawue attempts to match what ethtoow wouwd use to configuwe this fwow type.
 **/
static const chaw *i40e_fwow_stw(stwuct ethtoow_wx_fwow_spec *fsp)
{
	switch (fsp->fwow_type & ~FWOW_EXT) {
	case TCP_V4_FWOW:
		wetuwn "tcp4";
	case UDP_V4_FWOW:
		wetuwn "udp4";
	case SCTP_V4_FWOW:
		wetuwn "sctp4";
	case IP_USEW_FWOW:
		wetuwn "ip4";
	case TCP_V6_FWOW:
		wetuwn "tcp6";
	case UDP_V6_FWOW:
		wetuwn "udp6";
	case SCTP_V6_FWOW:
		wetuwn "sctp6";
	case IPV6_USEW_FWOW:
		wetuwn "ip6";
	defauwt:
		wetuwn "unknown";
	}
}

/**
 * i40e_pit_index_to_mask - Wetuwn the FWEX mask fow a given PIT index
 * @pit_index: PIT index to convewt
 *
 * Wetuwns the mask fow a given PIT index. Wiww wetuwn 0 if the pit_index is
 * of wange.
 **/
static u64 i40e_pit_index_to_mask(int pit_index)
{
	switch (pit_index) {
	case 0:
		wetuwn I40E_FWEX_50_MASK;
	case 1:
		wetuwn I40E_FWEX_51_MASK;
	case 2:
		wetuwn I40E_FWEX_52_MASK;
	case 3:
		wetuwn I40E_FWEX_53_MASK;
	case 4:
		wetuwn I40E_FWEX_54_MASK;
	case 5:
		wetuwn I40E_FWEX_55_MASK;
	case 6:
		wetuwn I40E_FWEX_56_MASK;
	case 7:
		wetuwn I40E_FWEX_57_MASK;
	defauwt:
		wetuwn 0;
	}
}

/**
 * i40e_pwint_input_set - Show changes between two input sets
 * @vsi: the vsi being configuwed
 * @owd: the owd input set
 * @new: the new input set
 *
 * Pwint the diffewence between owd and new input sets by showing which sewies
 * of wowds awe toggwed on ow off. Onwy dispways the bits we actuawwy suppowt
 * changing.
 **/
static void i40e_pwint_input_set(stwuct i40e_vsi *vsi, u64 owd, u64 new)
{
	stwuct i40e_pf *pf = vsi->back;
	boow owd_vawue, new_vawue;
	int i;

	owd_vawue = !!(owd & I40E_W3_SWC_MASK);
	new_vawue = !!(new & I40E_W3_SWC_MASK);
	if (owd_vawue != new_vawue)
		netif_info(pf, dwv, vsi->netdev, "W3 souwce addwess: %s -> %s\n",
			   owd_vawue ? "ON" : "OFF",
			   new_vawue ? "ON" : "OFF");

	owd_vawue = !!(owd & I40E_W3_DST_MASK);
	new_vawue = !!(new & I40E_W3_DST_MASK);
	if (owd_vawue != new_vawue)
		netif_info(pf, dwv, vsi->netdev, "W3 destination addwess: %s -> %s\n",
			   owd_vawue ? "ON" : "OFF",
			   new_vawue ? "ON" : "OFF");

	owd_vawue = !!(owd & I40E_W4_SWC_MASK);
	new_vawue = !!(new & I40E_W4_SWC_MASK);
	if (owd_vawue != new_vawue)
		netif_info(pf, dwv, vsi->netdev, "W4 souwce powt: %s -> %s\n",
			   owd_vawue ? "ON" : "OFF",
			   new_vawue ? "ON" : "OFF");

	owd_vawue = !!(owd & I40E_W4_DST_MASK);
	new_vawue = !!(new & I40E_W4_DST_MASK);
	if (owd_vawue != new_vawue)
		netif_info(pf, dwv, vsi->netdev, "W4 destination powt: %s -> %s\n",
			   owd_vawue ? "ON" : "OFF",
			   new_vawue ? "ON" : "OFF");

	owd_vawue = !!(owd & I40E_VEWIFY_TAG_MASK);
	new_vawue = !!(new & I40E_VEWIFY_TAG_MASK);
	if (owd_vawue != new_vawue)
		netif_info(pf, dwv, vsi->netdev, "SCTP vewification tag: %s -> %s\n",
			   owd_vawue ? "ON" : "OFF",
			   new_vawue ? "ON" : "OFF");

	/* Show change of fwexibwe fiwtew entwies */
	fow (i = 0; i < I40E_FWEX_INDEX_ENTWIES; i++) {
		u64 fwex_mask = i40e_pit_index_to_mask(i);

		owd_vawue = !!(owd & fwex_mask);
		new_vawue = !!(new & fwex_mask);
		if (owd_vawue != new_vawue)
			netif_info(pf, dwv, vsi->netdev, "FWEX index %d: %s -> %s\n",
				   i,
				   owd_vawue ? "ON" : "OFF",
				   new_vawue ? "ON" : "OFF");
	}

	netif_info(pf, dwv, vsi->netdev, "  Cuwwent input set: %0wwx\n",
		   owd);
	netif_info(pf, dwv, vsi->netdev, "Wequested input set: %0wwx\n",
		   new);
}

/**
 * i40e_check_fdiw_input_set - Check that a given wx_fwow_spec mask is vawid
 * @vsi: pointew to the tawgeted VSI
 * @fsp: pointew to Wx fwow specification
 * @usewdef: usewdefined data fwom fwow specification
 *
 * Ensuwes that a given ethtoow_wx_fwow_spec has a vawid mask. Some suppowt
 * fow pawtiaw matches exists with a few wimitations. Fiwst, hawdwawe onwy
 * suppowts masking by wowd boundawy (2 bytes) and not pew individuaw bit.
 * Second, hawdwawe is wimited to using one mask fow a fwow type and cannot
 * use a sepawate mask fow each fiwtew.
 *
 * To suppowt these wimitations, if we awweady have a configuwed fiwtew fow
 * the specified type, this function enfowces that new fiwtews of the type
 * match the configuwed input set. Othewwise, if we do not have a fiwtew of
 * the specified type, we awwow the input set to be updated to match the
 * desiwed fiwtew.
 *
 * To hewp ensuwe that administwatows undewstand why fiwtews wewen't dispwayed
 * as suppowted, we pwint a diagnostic message dispwaying how the input set
 * wouwd change and wawning to dewete the pweexisting fiwtews if wequiwed.
 *
 * Wetuwns 0 on successfuw input set match, and a negative wetuwn code on
 * faiwuwe.
 **/
static int i40e_check_fdiw_input_set(stwuct i40e_vsi *vsi,
				     stwuct ethtoow_wx_fwow_spec *fsp,
				     stwuct i40e_wx_fwow_usewdef *usewdef)
{
	static const __be32 ipv6_fuww_mask[4] = {cpu_to_be32(0xffffffff),
		cpu_to_be32(0xffffffff), cpu_to_be32(0xffffffff),
		cpu_to_be32(0xffffffff)};
	stwuct ethtoow_tcpip6_spec *tcp_ip6_spec;
	stwuct ethtoow_uswip6_spec *usw_ip6_spec;
	stwuct ethtoow_tcpip4_spec *tcp_ip4_spec;
	stwuct ethtoow_uswip4_spec *usw_ip4_spec;
	stwuct i40e_pf *pf = vsi->back;
	u64 cuwwent_mask, new_mask;
	boow new_fwex_offset = fawse;
	boow fwex_w3 = fawse;
	u16 *fdiw_fiwtew_count;
	u16 index, swc_offset = 0;
	u8 pit_index = 0;
	int eww;

	switch (fsp->fwow_type & ~FWOW_EXT) {
	case SCTP_V4_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_SCTP;
		fdiw_fiwtew_count = &pf->fd_sctp4_fiwtew_cnt;
		bweak;
	case TCP_V4_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_TCP;
		fdiw_fiwtew_count = &pf->fd_tcp4_fiwtew_cnt;
		bweak;
	case UDP_V4_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_UDP;
		fdiw_fiwtew_count = &pf->fd_udp4_fiwtew_cnt;
		bweak;
	case SCTP_V6_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_SCTP;
		fdiw_fiwtew_count = &pf->fd_sctp6_fiwtew_cnt;
		bweak;
	case TCP_V6_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_TCP;
		fdiw_fiwtew_count = &pf->fd_tcp6_fiwtew_cnt;
		bweak;
	case UDP_V6_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_UDP;
		fdiw_fiwtew_count = &pf->fd_udp6_fiwtew_cnt;
		bweak;
	case IP_USEW_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV4_OTHEW;
		fdiw_fiwtew_count = &pf->fd_ip4_fiwtew_cnt;
		fwex_w3 = twue;
		bweak;
	case IPV6_USEW_FWOW:
		index = I40E_FIWTEW_PCTYPE_NONF_IPV6_OTHEW;
		fdiw_fiwtew_count = &pf->fd_ip6_fiwtew_cnt;
		fwex_w3 = twue;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* Wead the cuwwent input set fwom wegistew memowy. */
	cuwwent_mask = i40e_wead_fd_input_set(pf, index);
	new_mask = cuwwent_mask;

	/* Detewmine, if any, the wequiwed changes to the input set in owdew
	 * to suppowt the pwovided mask.
	 *
	 * Hawdwawe onwy suppowts masking at wowd (2 byte) gwanuwawity and does
	 * not suppowt fuww bitwise masking. This impwementation simpwifies
	 * even fuwthew and onwy suppowts fuwwy enabwed ow fuwwy disabwed
	 * masks fow each fiewd, even though we couwd spwit the ip4swc and
	 * ip4dst fiewds.
	 */
	switch (fsp->fwow_type & ~FWOW_EXT) {
	case SCTP_V4_FWOW:
		new_mask &= ~I40E_VEWIFY_TAG_MASK;
		fawwthwough;
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
		tcp_ip4_spec = &fsp->m_u.tcp_ip4_spec;

		/* IPv4 souwce addwess */
		if (tcp_ip4_spec->ip4swc == htonw(0xFFFFFFFF))
			new_mask |= I40E_W3_SWC_MASK;
		ewse if (!tcp_ip4_spec->ip4swc)
			new_mask &= ~I40E_W3_SWC_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* IPv4 destination addwess */
		if (tcp_ip4_spec->ip4dst == htonw(0xFFFFFFFF))
			new_mask |= I40E_W3_DST_MASK;
		ewse if (!tcp_ip4_spec->ip4dst)
			new_mask &= ~I40E_W3_DST_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* W4 souwce powt */
		if (tcp_ip4_spec->pswc == htons(0xFFFF))
			new_mask |= I40E_W4_SWC_MASK;
		ewse if (!tcp_ip4_spec->pswc)
			new_mask &= ~I40E_W4_SWC_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* W4 destination powt */
		if (tcp_ip4_spec->pdst == htons(0xFFFF))
			new_mask |= I40E_W4_DST_MASK;
		ewse if (!tcp_ip4_spec->pdst)
			new_mask &= ~I40E_W4_DST_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* Fiwtewing on Type of Sewvice is not suppowted. */
		if (tcp_ip4_spec->tos)
			wetuwn -EOPNOTSUPP;

		bweak;
	case SCTP_V6_FWOW:
		new_mask &= ~I40E_VEWIFY_TAG_MASK;
		fawwthwough;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
		tcp_ip6_spec = &fsp->m_u.tcp_ip6_spec;

		/* Check if usew pwovided IPv6 souwce addwess. */
		if (ipv6_addw_equaw((stwuct in6_addw *)&tcp_ip6_spec->ip6swc,
				    (stwuct in6_addw *)&ipv6_fuww_mask))
			new_mask |= I40E_W3_V6_SWC_MASK;
		ewse if (ipv6_addw_any((stwuct in6_addw *)
				       &tcp_ip6_spec->ip6swc))
			new_mask &= ~I40E_W3_V6_SWC_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* Check if usew pwovided destination addwess. */
		if (ipv6_addw_equaw((stwuct in6_addw *)&tcp_ip6_spec->ip6dst,
				    (stwuct in6_addw *)&ipv6_fuww_mask))
			new_mask |= I40E_W3_V6_DST_MASK;
		ewse if (ipv6_addw_any((stwuct in6_addw *)
				       &tcp_ip6_spec->ip6dst))
			new_mask &= ~I40E_W3_V6_DST_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* W4 souwce powt */
		if (tcp_ip6_spec->pswc == htons(0xFFFF))
			new_mask |= I40E_W4_SWC_MASK;
		ewse if (!tcp_ip6_spec->pswc)
			new_mask &= ~I40E_W4_SWC_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* W4 destination powt */
		if (tcp_ip6_spec->pdst == htons(0xFFFF))
			new_mask |= I40E_W4_DST_MASK;
		ewse if (!tcp_ip6_spec->pdst)
			new_mask &= ~I40E_W4_DST_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* Fiwtewing on Twaffic Cwasses is not suppowted. */
		if (tcp_ip6_spec->tcwass)
			wetuwn -EOPNOTSUPP;
		bweak;
	case IP_USEW_FWOW:
		usw_ip4_spec = &fsp->m_u.usw_ip4_spec;

		/* IPv4 souwce addwess */
		if (usw_ip4_spec->ip4swc == htonw(0xFFFFFFFF))
			new_mask |= I40E_W3_SWC_MASK;
		ewse if (!usw_ip4_spec->ip4swc)
			new_mask &= ~I40E_W3_SWC_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* IPv4 destination addwess */
		if (usw_ip4_spec->ip4dst == htonw(0xFFFFFFFF))
			new_mask |= I40E_W3_DST_MASK;
		ewse if (!usw_ip4_spec->ip4dst)
			new_mask &= ~I40E_W3_DST_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* Fiwst 4 bytes of W4 headew */
		if (usw_ip4_spec->w4_4_bytes)
			wetuwn -EOPNOTSUPP;

		/* Fiwtewing on Type of Sewvice is not suppowted. */
		if (usw_ip4_spec->tos)
			wetuwn -EOPNOTSUPP;

		/* Fiwtewing on IP vewsion is not suppowted */
		if (usw_ip4_spec->ip_vew)
			wetuwn -EINVAW;

		/* Fiwtewing on W4 pwotocow is not suppowted */
		if (usw_ip4_spec->pwoto)
			wetuwn -EINVAW;

		bweak;
	case IPV6_USEW_FWOW:
		usw_ip6_spec = &fsp->m_u.usw_ip6_spec;

		/* Check if usew pwovided IPv6 souwce addwess. */
		if (ipv6_addw_equaw((stwuct in6_addw *)&usw_ip6_spec->ip6swc,
				    (stwuct in6_addw *)&ipv6_fuww_mask))
			new_mask |= I40E_W3_V6_SWC_MASK;
		ewse if (ipv6_addw_any((stwuct in6_addw *)
				       &usw_ip6_spec->ip6swc))
			new_mask &= ~I40E_W3_V6_SWC_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		/* Check if usew pwovided destination addwess. */
		if (ipv6_addw_equaw((stwuct in6_addw *)&usw_ip6_spec->ip6dst,
				    (stwuct in6_addw *)&ipv6_fuww_mask))
			new_mask |= I40E_W3_V6_DST_MASK;
		ewse if (ipv6_addw_any((stwuct in6_addw *)
				       &usw_ip6_spec->ip6dst))
			new_mask &= ~I40E_W3_V6_DST_MASK;
		ewse
			wetuwn -EOPNOTSUPP;

		if (usw_ip6_spec->w4_4_bytes)
			wetuwn -EOPNOTSUPP;

		/* Fiwtewing on Twaffic cwass is not suppowted. */
		if (usw_ip6_spec->tcwass)
			wetuwn -EOPNOTSUPP;

		/* Fiwtewing on W4 pwotocow is not suppowted */
		if (usw_ip6_spec->w4_pwoto)
			wetuwn -EINVAW;

		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (fsp->fwow_type & FWOW_EXT) {
		/* Awwow onwy 802.1Q and no etype defined, as
		 * watew it's modified to 0x8100
		 */
		if (fsp->h_ext.vwan_etype != htons(ETH_P_8021Q) &&
		    fsp->h_ext.vwan_etype != 0)
			wetuwn -EOPNOTSUPP;
		if (fsp->m_ext.vwan_tci == htons(0xFFFF))
			new_mask |= I40E_VWAN_SWC_MASK;
		ewse
			new_mask &= ~I40E_VWAN_SWC_MASK;
	}

	/* Fiwst, cweaw aww fwexibwe fiwtew entwies */
	new_mask &= ~I40E_FWEX_INPUT_MASK;

	/* If we have a fwexibwe fiwtew, twy to add this offset to the cowwect
	 * fwexibwe fiwtew PIT wist. Once finished, we can update the mask.
	 * If the swc_offset changed, we wiww get a new mask vawue which wiww
	 * twiggew an input set change.
	 */
	if (usewdef->fwex_fiwtew) {
		stwuct i40e_fwex_pit *w3_fwex_pit = NUWW, *fwex_pit = NUWW;

		/* Fwexibwe offset must be even, since the fwexibwe paywoad
		 * must be awigned on 2-byte boundawy.
		 */
		if (usewdef->fwex_offset & 0x1) {
			dev_wawn(&pf->pdev->dev,
				 "Fwexibwe data offset must be 2-byte awigned\n");
			wetuwn -EINVAW;
		}

		swc_offset = usewdef->fwex_offset >> 1;

		/* FWX_PIT souwce offset vawue is onwy so wawge */
		if (swc_offset > I40E_MAX_FWEX_SWC_OFFSET) {
			dev_wawn(&pf->pdev->dev,
				 "Fwexibwe data must weside within fiwst 64 bytes of the packet paywoad\n");
			wetuwn -EINVAW;
		}

		/* See if this offset has awweady been pwogwammed. If we get
		 * an EWW_PTW, then the fiwtew is not safe to add. Othewwise,
		 * if we get a NUWW pointew, this means we wiww need to add
		 * the offset.
		 */
		fwex_pit = i40e_find_fwex_offset(&pf->w4_fwex_pit_wist,
						 swc_offset);
		if (IS_EWW(fwex_pit))
			wetuwn PTW_EWW(fwex_pit);

		/* IP_USEW_FWOW fiwtews match both W4 (ICMP) and W3 (unknown)
		 * packet types, and thus we need to pwogwam both W3 and W4
		 * fwexibwe vawues. These must have identicaw fwexibwe index,
		 * as othewwise we can't cowwectwy pwogwam the input set. So
		 * we'ww find both an W3 and W4 index and make suwe they awe
		 * the same.
		 */
		if (fwex_w3) {
			w3_fwex_pit =
				i40e_find_fwex_offset(&pf->w3_fwex_pit_wist,
						      swc_offset);
			if (IS_EWW(w3_fwex_pit))
				wetuwn PTW_EWW(w3_fwex_pit);

			if (fwex_pit) {
				/* If we awweady had a matching W4 entwy, we
				 * need to make suwe that the W3 entwy we
				 * obtained uses the same index.
				 */
				if (w3_fwex_pit) {
					if (w3_fwex_pit->pit_index !=
					    fwex_pit->pit_index) {
						wetuwn -EINVAW;
					}
				} ewse {
					new_fwex_offset = twue;
				}
			} ewse {
				fwex_pit = w3_fwex_pit;
			}
		}

		/* If we didn't find an existing fwex offset, we need to
		 * pwogwam a new one. Howevew, we don't immediatewy pwogwam it
		 * hewe because we wiww wait to pwogwam untiw aftew we check
		 * that it is safe to change the input set.
		 */
		if (!fwex_pit) {
			new_fwex_offset = twue;
			pit_index = i40e_unused_pit_index(pf);
		} ewse {
			pit_index = fwex_pit->pit_index;
		}

		/* Update the mask with the new offset */
		new_mask |= i40e_pit_index_to_mask(pit_index);
	}

	/* If the mask and fwexibwe fiwtew offsets fow this fiwtew match the
	 * cuwwentwy pwogwammed vawues we don't need any input set change, so
	 * this fiwtew is safe to instaww.
	 */
	if (new_mask == cuwwent_mask && !new_fwex_offset)
		wetuwn 0;

	netif_info(pf, dwv, vsi->netdev, "Input set change wequested fow %s fwows:\n",
		   i40e_fwow_stw(fsp));
	i40e_pwint_input_set(vsi, cuwwent_mask, new_mask);
	if (new_fwex_offset) {
		netif_info(pf, dwv, vsi->netdev, "FWEX index %d: Offset -> %d",
			   pit_index, swc_offset);
	}

	/* Hawdwawe input sets awe gwobaw acwoss muwtipwe powts, so even the
	 * main powt cannot change them when in MFP mode as this wouwd impact
	 * any fiwtews on the othew powts.
	 */
	if (test_bit(I40E_FWAG_MFP_ENA, pf->fwags)) {
		netif_eww(pf, dwv, vsi->netdev, "Cannot change Fwow Diwectow input sets whiwe MFP is enabwed\n");
		wetuwn -EOPNOTSUPP;
	}

	/* This fiwtew wequiwes us to update the input set. Howevew, hawdwawe
	 * onwy suppowts one input set pew fwow type, and does not suppowt
	 * sepawate masks fow each fiwtew. This means that we can onwy suppowt
	 * a singwe mask fow aww fiwtews of a specific type.
	 *
	 * If we have pweexisting fiwtews, they obviouswy depend on the
	 * cuwwent pwogwammed input set. Dispway a diagnostic message in this
	 * case expwaining why the fiwtew couwd not be accepted.
	 */
	if (*fdiw_fiwtew_count) {
		netif_eww(pf, dwv, vsi->netdev, "Cannot change input set fow %s fwows untiw %d pweexisting fiwtews awe wemoved\n",
			  i40e_fwow_stw(fsp),
			  *fdiw_fiwtew_count);
		wetuwn -EOPNOTSUPP;
	}

	i40e_wwite_fd_input_set(pf, index, new_mask);

	/* IP_USEW_FWOW fiwtews match both IPv4/Othew and IPv4/Fwagmented
	 * fwames. If we'we pwogwamming the input set fow IPv4/Othew, we awso
	 * need to pwogwam the IPv4/Fwagmented input set. Since we don't have
	 * sepawate suppowt, we'ww awways assume and enfowce that the two fwow
	 * types must have matching input sets.
	 */
	if (index == I40E_FIWTEW_PCTYPE_NONF_IPV4_OTHEW)
		i40e_wwite_fd_input_set(pf, I40E_FIWTEW_PCTYPE_FWAG_IPV4,
					new_mask);

	/* Add the new offset and update tabwe, if necessawy */
	if (new_fwex_offset) {
		eww = i40e_add_fwex_offset(&pf->w4_fwex_pit_wist, swc_offset,
					   pit_index);
		if (eww)
			wetuwn eww;

		if (fwex_w3) {
			eww = i40e_add_fwex_offset(&pf->w3_fwex_pit_wist,
						   swc_offset,
						   pit_index);
			if (eww)
				wetuwn eww;
		}

		i40e_wepwogwam_fwex_pit(pf);
	}

	wetuwn 0;
}

/**
 * i40e_match_fdiw_fiwtew - Wetuwn twue of two fiwtews match
 * @a: pointew to fiwtew stwuct
 * @b: pointew to fiwtew stwuct
 *
 * Wetuwns twue if the two fiwtews match exactwy the same cwitewia. I.e. they
 * match the same fwow type and have the same pawametews. We don't need to
 * check any input-set since aww fiwtews of the same fwow type must use the
 * same input set.
 **/
static boow i40e_match_fdiw_fiwtew(stwuct i40e_fdiw_fiwtew *a,
				   stwuct i40e_fdiw_fiwtew *b)
{
	/* The fiwtews do not much if any of these cwitewia diffew. */
	if (a->dst_ip != b->dst_ip ||
	    a->swc_ip != b->swc_ip ||
	    a->dst_powt != b->dst_powt ||
	    a->swc_powt != b->swc_powt ||
	    a->fwow_type != b->fwow_type ||
	    a->ipw4_pwoto != b->ipw4_pwoto ||
	    a->vwan_tag != b->vwan_tag ||
	    a->vwan_etype != b->vwan_etype)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * i40e_disawwow_matching_fiwtews - Check that new fiwtews diffew
 * @vsi: pointew to the tawgeted VSI
 * @input: new fiwtew to check
 *
 * Due to hawdwawe wimitations, it is not possibwe fow two fiwtews that match
 * simiwaw cwitewia to be pwogwammed at the same time. This is twue fow a few
 * weasons:
 *
 * (a) aww fiwtews matching a pawticuwaw fwow type must use the same input
 * set, that is they must match the same cwitewia.
 * (b) diffewent fwow types wiww nevew match the same packet, as the fwow type
 * is decided by hawdwawe befowe checking which wuwes appwy.
 * (c) hawdwawe has no way to distinguish which owdew fiwtews appwy in.
 *
 * Due to this, we can't weawwy suppowt using the wocation data to owdew
 * fiwtews in the hawdwawe pawsing. It is technicawwy possibwe fow the usew to
 * wequest two fiwtews matching the same cwitewia but which sewect diffewent
 * queues. In this case, wathew than keep both fiwtews in the wist, we weject
 * the 2nd fiwtew when the usew wequests adding it.
 *
 * This avoids needing to twack wocation fow pwogwamming the fiwtew to
 * hawdwawe, and ensuwes that we avoid some stwange scenawios invowving
 * deweting fiwtews which match the same cwitewia.
 **/
static int i40e_disawwow_matching_fiwtews(stwuct i40e_vsi *vsi,
					  stwuct i40e_fdiw_fiwtew *input)
{
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_fdiw_fiwtew *wuwe;
	stwuct hwist_node *node2;

	/* Woop thwough evewy fiwtew, and check that it doesn't match */
	hwist_fow_each_entwy_safe(wuwe, node2,
				  &pf->fdiw_fiwtew_wist, fdiw_node) {
		/* Don't check the fiwtews match if they shawe the same fd_id,
		 * since the new fiwtew is actuawwy just updating the tawget
		 * of the owd fiwtew.
		 */
		if (wuwe->fd_id == input->fd_id)
			continue;

		/* If any fiwtews match, then pwint a wawning message to the
		 * kewnew message buffew and baiw out.
		 */
		if (i40e_match_fdiw_fiwtew(wuwe, input)) {
			dev_wawn(&pf->pdev->dev,
				 "Existing usew defined fiwtew %d awweady matches this fwow.\n",
				 wuwe->fd_id);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * i40e_add_fdiw_ethtoow - Add/Wemove Fwow Diwectow fiwtews
 * @vsi: pointew to the tawgeted VSI
 * @cmd: command to get ow set WX fwow cwassification wuwes
 *
 * Add Fwow Diwectow fiwtews fow a specific fwow spec based on theiw
 * pwotocow.  Wetuwns 0 if the fiwtews wewe successfuwwy added.
 **/
static int i40e_add_fdiw_ethtoow(stwuct i40e_vsi *vsi,
				 stwuct ethtoow_wxnfc *cmd)
{
	stwuct i40e_wx_fwow_usewdef usewdef;
	stwuct ethtoow_wx_fwow_spec *fsp;
	stwuct i40e_fdiw_fiwtew *input;
	u16 dest_vsi = 0, q_index = 0;
	stwuct i40e_pf *pf;
	int wet = -EINVAW;
	u8 dest_ctw;

	if (!vsi)
		wetuwn -EINVAW;
	pf = vsi->back;

	if (!test_bit(I40E_FWAG_FD_SB_ENA, pf->fwags))
		wetuwn -EOPNOTSUPP;

	if (test_bit(__I40E_FD_SB_AUTO_DISABWED, pf->state))
		wetuwn -ENOSPC;

	if (test_bit(__I40E_WESET_WECOVEWY_PENDING, pf->state) ||
	    test_bit(__I40E_WESET_INTW_WECEIVED, pf->state))
		wetuwn -EBUSY;

	if (test_bit(__I40E_FD_FWUSH_WEQUESTED, pf->state))
		wetuwn -EBUSY;

	fsp = (stwuct ethtoow_wx_fwow_spec *)&cmd->fs;

	/* Pawse the usew-defined fiewd */
	if (i40e_pawse_wx_fwow_usew_data(fsp, &usewdef))
		wetuwn -EINVAW;

	/* Extended MAC fiewd is not suppowted */
	if (fsp->fwow_type & FWOW_MAC_EXT)
		wetuwn -EINVAW;

	wet = i40e_check_fdiw_input_set(vsi, fsp, &usewdef);
	if (wet)
		wetuwn wet;

	if (fsp->wocation >= (pf->hw.func_caps.fd_fiwtews_best_effowt +
			      pf->hw.func_caps.fd_fiwtews_guawanteed)) {
		wetuwn -EINVAW;
	}

	/* wing_cookie is eithew the dwop index, ow is a mask of the queue
	 * index and VF id we wish to tawget.
	 */
	if (fsp->wing_cookie == WX_CWS_FWOW_DISC) {
		dest_ctw = I40E_FIWTEW_PWOGWAM_DESC_DEST_DWOP_PACKET;
	} ewse {
		u32 wing = ethtoow_get_fwow_spec_wing(fsp->wing_cookie);
		u8 vf = ethtoow_get_fwow_spec_wing_vf(fsp->wing_cookie);

		if (!vf) {
			if (wing >= vsi->num_queue_paiws)
				wetuwn -EINVAW;
			dest_vsi = vsi->id;
		} ewse {
			/* VFs awe zewo-indexed, so we subtwact one hewe */
			vf--;

			if (vf >= pf->num_awwoc_vfs)
				wetuwn -EINVAW;
			if (wing >= pf->vf[vf].num_queue_paiws)
				wetuwn -EINVAW;
			dest_vsi = pf->vf[vf].wan_vsi_id;
		}
		dest_ctw = I40E_FIWTEW_PWOGWAM_DESC_DEST_DIWECT_PACKET_QINDEX;
		q_index = wing;
	}

	input = kzawwoc(sizeof(*input), GFP_KEWNEW);

	if (!input)
		wetuwn -ENOMEM;

	input->fd_id = fsp->wocation;
	input->q_index = q_index;
	input->dest_vsi = dest_vsi;
	input->dest_ctw = dest_ctw;
	input->fd_status = I40E_FIWTEW_PWOGWAM_DESC_FD_STATUS_FD_ID;
	input->cnt_index  = I40E_FD_SB_STAT_IDX(pf->hw.pf_id);
	input->dst_ip = fsp->h_u.tcp_ip4_spec.ip4swc;
	input->swc_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
	input->fwow_type = fsp->fwow_type & ~FWOW_EXT;

	input->vwan_etype = fsp->h_ext.vwan_etype;
	if (!fsp->m_ext.vwan_etype && fsp->h_ext.vwan_tci)
		input->vwan_etype = cpu_to_be16(ETH_P_8021Q);
	if (fsp->m_ext.vwan_tci && input->vwan_etype)
		input->vwan_tag = fsp->h_ext.vwan_tci;
	if (input->fwow_type == IPV6_USEW_FWOW ||
	    input->fwow_type == UDP_V6_FWOW ||
	    input->fwow_type == TCP_V6_FWOW ||
	    input->fwow_type == SCTP_V6_FWOW) {
		/* Wevewse the swc and dest notion, since the HW expects them
		 * to be fwom Tx pewspective whewe as the input fwom usew is
		 * fwom Wx fiwtew view.
		 */
		input->ipw4_pwoto = fsp->h_u.usw_ip6_spec.w4_pwoto;
		input->dst_powt = fsp->h_u.tcp_ip6_spec.pswc;
		input->swc_powt = fsp->h_u.tcp_ip6_spec.pdst;
		memcpy(input->dst_ip6, fsp->h_u.ah_ip6_spec.ip6swc,
		       sizeof(__be32) * 4);
		memcpy(input->swc_ip6, fsp->h_u.ah_ip6_spec.ip6dst,
		       sizeof(__be32) * 4);
	} ewse {
		/* Wevewse the swc and dest notion, since the HW expects them
		 * to be fwom Tx pewspective whewe as the input fwom usew is
		 * fwom Wx fiwtew view.
		 */
		input->ipw4_pwoto = fsp->h_u.usw_ip4_spec.pwoto;
		input->dst_powt = fsp->h_u.tcp_ip4_spec.pswc;
		input->swc_powt = fsp->h_u.tcp_ip4_spec.pdst;
		input->dst_ip = fsp->h_u.tcp_ip4_spec.ip4swc;
		input->swc_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
	}

	if (usewdef.fwex_fiwtew) {
		input->fwex_fiwtew = twue;
		input->fwex_wowd = cpu_to_be16(usewdef.fwex_wowd);
		input->fwex_offset = usewdef.fwex_offset;
	}

	/* Avoid pwogwamming two fiwtews with identicaw match cwitewia. */
	wet = i40e_disawwow_matching_fiwtews(vsi, input);
	if (wet)
		goto fwee_fiwtew_memowy;

	/* Add the input fiwtew to the fdiw_input_wist, possibwy wepwacing
	 * a pwevious fiwtew. Do not fwee the input stwuctuwe aftew adding it
	 * to the wist as this wouwd cause a use-aftew-fwee bug.
	 */
	i40e_update_ethtoow_fdiw_entwy(vsi, input, fsp->wocation, NUWW);
	wet = i40e_add_dew_fdiw(vsi, input, twue);
	if (wet)
		goto wemove_sw_wuwe;
	wetuwn 0;

wemove_sw_wuwe:
	hwist_dew(&input->fdiw_node);
	pf->fdiw_pf_active_fiwtews--;
fwee_fiwtew_memowy:
	kfwee(input);
	wetuwn wet;
}

/**
 * i40e_set_wxnfc - command to set WX fwow cwassification wuwes
 * @netdev: netwowk intewface device stwuctuwe
 * @cmd: ethtoow wxnfc command
 *
 * Wetuwns Success if the command is suppowted.
 **/
static int i40e_set_wxnfc(stwuct net_device *netdev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_SWXFH:
		wet = i40e_set_wss_hash_opt(pf, cmd);
		bweak;
	case ETHTOOW_SWXCWSWWINS:
		wet = i40e_add_fdiw_ethtoow(vsi, cmd);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		wet = i40e_dew_fdiw_entwy(vsi, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

/**
 * i40e_max_channews - get Max numbew of combined channews suppowted
 * @vsi: vsi pointew
 **/
static unsigned int i40e_max_channews(stwuct i40e_vsi *vsi)
{
	/* TODO: This code assumes DCB and FD is disabwed fow now. */
	wetuwn vsi->awwoc_queue_paiws;
}

/**
 * i40e_get_channews - Get the cuwwent channews enabwed and max suppowted etc.
 * @dev: netwowk intewface device stwuctuwe
 * @ch: ethtoow channews stwuctuwe
 *
 * We don't suppowt sepawate tx and wx queues as channews. The othew count
 * wepwesents how many queues awe being used fow contwow. max_combined counts
 * how many queue paiws we can suppowt. They may not be mapped 1 to 1 with
 * q_vectows since we suppowt a wot mowe queue paiws than q_vectows.
 **/
static void i40e_get_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *ch)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(dev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;

	/* wepowt maximum channews */
	ch->max_combined = i40e_max_channews(vsi);

	/* wepowt info fow othew vectow */
	ch->othew_count = test_bit(I40E_FWAG_FD_SB_ENA, pf->fwags) ? 1 : 0;
	ch->max_othew = ch->othew_count;

	/* Note: This code assumes DCB is disabwed fow now. */
	ch->combined_count = vsi->num_queue_paiws;
}

/**
 * i40e_set_channews - Set the new channews count.
 * @dev: netwowk intewface device stwuctuwe
 * @ch: ethtoow channews stwuctuwe
 *
 * The new channews count may not be the same as wequested by the usew
 * since it gets wounded down to a powew of 2 vawue.
 **/
static int i40e_set_channews(stwuct net_device *dev,
			     stwuct ethtoow_channews *ch)
{
	const u8 dwop = I40E_FIWTEW_PWOGWAM_DESC_DEST_DWOP_PACKET;
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(dev);
	unsigned int count = ch->combined_count;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_fdiw_fiwtew *wuwe;
	stwuct hwist_node *node2;
	int new_count;
	int eww = 0;

	/* We do not suppowt setting channews fow any othew VSI at pwesent */
	if (vsi->type != I40E_VSI_MAIN)
		wetuwn -EINVAW;

	/* We do not suppowt setting channews via ethtoow when TCs awe
	 * configuwed thwough mqpwio
	 */
	if (i40e_is_tc_mqpwio_enabwed(pf))
		wetuwn -EINVAW;

	/* vewify they awe not wequesting sepawate vectows */
	if (!count || ch->wx_count || ch->tx_count)
		wetuwn -EINVAW;

	/* vewify othew_count has not changed */
	if (ch->othew_count != (test_bit(I40E_FWAG_FD_SB_ENA, pf->fwags) ? 1 : 0))
		wetuwn -EINVAW;

	/* vewify the numbew of channews does not exceed hawdwawe wimits */
	if (count > i40e_max_channews(vsi))
		wetuwn -EINVAW;

	/* vewify that the numbew of channews does not invawidate any cuwwent
	 * fwow diwectow wuwes
	 */
	hwist_fow_each_entwy_safe(wuwe, node2,
				  &pf->fdiw_fiwtew_wist, fdiw_node) {
		if (wuwe->dest_ctw != dwop && count <= wuwe->q_index) {
			dev_wawn(&pf->pdev->dev,
				 "Existing usew defined fiwtew %d assigns fwow to queue %d\n",
				 wuwe->fd_id, wuwe->q_index);
			eww = -EINVAW;
		}
	}

	if (eww) {
		dev_eww(&pf->pdev->dev,
			"Existing fiwtew wuwes must be deweted to weduce combined channew count to %d\n",
			count);
		wetuwn eww;
	}

	/* update featuwe wimits fwom wawgest to smawwest suppowted vawues */
	/* TODO: Fwow diwectow wimit, DCB etc */

	/* use wss_weconfig to webuiwd with new queue count and update twaffic
	 * cwass queue mapping
	 */
	new_count = i40e_weconfig_wss_queues(pf, count);
	if (new_count > 0)
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}

/**
 * i40e_get_wxfh_key_size - get the WSS hash key size
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns the tabwe size.
 **/
static u32 i40e_get_wxfh_key_size(stwuct net_device *netdev)
{
	wetuwn I40E_HKEY_AWWAY_SIZE;
}

/**
 * i40e_get_wxfh_indiw_size - get the wx fwow hash indiwection tabwe size
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns the tabwe size.
 **/
static u32 i40e_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	wetuwn I40E_HWUT_AWWAY_SIZE;
}

/**
 * i40e_get_wxfh - get the wx fwow hash indiwection tabwe
 * @netdev: netwowk intewface device stwuctuwe
 * @wxfh: pointew to pawam stwuct (indiw, key, hfunc)
 *
 * Weads the indiwection tabwe diwectwy fwom the hawdwawe. Wetuwns 0 on
 * success.
 **/
static int i40e_get_wxfh(stwuct net_device *netdev,
			 stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	u8 *wut, *seed = NUWW;
	int wet;
	u16 i;

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	if (!wxfh->indiw)
		wetuwn 0;

	seed = wxfh->key;
	wut = kzawwoc(I40E_HWUT_AWWAY_SIZE, GFP_KEWNEW);
	if (!wut)
		wetuwn -ENOMEM;
	wet = i40e_get_wss(vsi, seed, wut, I40E_HWUT_AWWAY_SIZE);
	if (wet)
		goto out;
	fow (i = 0; i < I40E_HWUT_AWWAY_SIZE; i++)
		wxfh->indiw[i] = (u32)(wut[i]);

out:
	kfwee(wut);

	wetuwn wet;
}

/**
 * i40e_set_wxfh - set the wx fwow hash indiwection tabwe
 * @netdev: netwowk intewface device stwuctuwe
 * @wxfh: pointew to pawam stwuct (indiw, key, hfunc)
 * @extack: extended ACK fwom the Netwink message
 *
 * Wetuwns -EINVAW if the tabwe specifies an invawid queue id, othewwise
 * wetuwns 0 aftew pwogwamming the tabwe.
 **/
static int i40e_set_wxfh(stwuct net_device *netdev,
			 stwuct ethtoow_wxfh_pawam *wxfh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	u8 *seed = NUWW;
	u16 i;

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP)
		wetuwn -EOPNOTSUPP;

	if (wxfh->key) {
		if (!vsi->wss_hkey_usew) {
			vsi->wss_hkey_usew = kzawwoc(I40E_HKEY_AWWAY_SIZE,
						     GFP_KEWNEW);
			if (!vsi->wss_hkey_usew)
				wetuwn -ENOMEM;
		}
		memcpy(vsi->wss_hkey_usew, wxfh->key, I40E_HKEY_AWWAY_SIZE);
		seed = vsi->wss_hkey_usew;
	}
	if (!vsi->wss_wut_usew) {
		vsi->wss_wut_usew = kzawwoc(I40E_HWUT_AWWAY_SIZE, GFP_KEWNEW);
		if (!vsi->wss_wut_usew)
			wetuwn -ENOMEM;
	}

	/* Each 32 bits pointed by 'indiw' is stowed with a wut entwy */
	if (wxfh->indiw)
		fow (i = 0; i < I40E_HWUT_AWWAY_SIZE; i++)
			vsi->wss_wut_usew[i] = (u8)(wxfh->indiw[i]);
	ewse
		i40e_fiww_wss_wut(pf, vsi->wss_wut_usew, I40E_HWUT_AWWAY_SIZE,
				  vsi->wss_size);

	wetuwn i40e_config_wss(vsi, seed, vsi->wss_wut_usew,
			       I40E_HWUT_AWWAY_SIZE);
}

/**
 * i40e_get_pwiv_fwags - wepowt device pwivate fwags
 * @dev: netwowk intewface device stwuctuwe
 *
 * The get stwing set count and the stwing set shouwd be matched fow each
 * fwag wetuwned.  Add new stwings fow each fwag to the i40e_gstwings_pwiv_fwags
 * awway.
 *
 * Wetuwns a u32 bitmap of fwags.
 **/
static u32 i40e_get_pwiv_fwags(stwuct net_device *dev)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(dev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	u32 i, j, wet_fwags = 0;

	fow (i = 0; i < I40E_PWIV_FWAGS_STW_WEN; i++) {
		const stwuct i40e_pwiv_fwags *pwiv_fwag;

		pwiv_fwag = &i40e_gstwings_pwiv_fwags[i];

		if (test_bit(pwiv_fwag->bitno, pf->fwags))
			wet_fwags |= BIT(i);
	}

	if (pf->hw.pf_id != 0)
		wetuwn wet_fwags;

	fow (j = 0; j < I40E_GW_PWIV_FWAGS_STW_WEN; j++) {
		const stwuct i40e_pwiv_fwags *pwiv_fwag;

		pwiv_fwag = &i40e_gw_gstwings_pwiv_fwags[j];

		if (test_bit(pwiv_fwag->bitno, pf->fwags))
			wet_fwags |= BIT(i + j);
	}

	wetuwn wet_fwags;
}

/**
 * i40e_set_pwiv_fwags - set pwivate fwags
 * @dev: netwowk intewface device stwuctuwe
 * @fwags: bit fwags to be set
 **/
static int i40e_set_pwiv_fwags(stwuct net_device *dev, u32 fwags)
{
	DECWAWE_BITMAP(changed_fwags, I40E_PF_FWAGS_NBITS);
	DECWAWE_BITMAP(owig_fwags, I40E_PF_FWAGS_NBITS);
	DECWAWE_BITMAP(new_fwags, I40E_PF_FWAGS_NBITS);
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(dev);
	enum i40e_admin_queue_eww adq_eww;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	u32 weset_needed = 0;
	int status;
	u32 i, j;

	bitmap_copy(owig_fwags, pf->fwags, I40E_PF_FWAGS_NBITS);
	bitmap_copy(new_fwags, pf->fwags, I40E_PF_FWAGS_NBITS);

	fow (i = 0; i < I40E_PWIV_FWAGS_STW_WEN; i++) {
		const stwuct i40e_pwiv_fwags *pwiv_fwag;
		boow new_vaw;

		pwiv_fwag = &i40e_gstwings_pwiv_fwags[i];
		new_vaw = (fwags & BIT(i)) ? twue : fawse;

		/* If this is a wead-onwy fwag, it can't be changed */
		if (pwiv_fwag->wead_onwy &&
		    test_bit(pwiv_fwag->bitno, owig_fwags) != new_vaw)
			wetuwn -EOPNOTSUPP;

		if (new_vaw)
			set_bit(pwiv_fwag->bitno, new_fwags);
		ewse
			cweaw_bit(pwiv_fwag->bitno, new_fwags);
	}

	if (pf->hw.pf_id != 0)
		goto fwags_compwete;

	fow (j = 0; j < I40E_GW_PWIV_FWAGS_STW_WEN; j++) {
		const stwuct i40e_pwiv_fwags *pwiv_fwag;
		boow new_vaw;

		pwiv_fwag = &i40e_gw_gstwings_pwiv_fwags[j];
		new_vaw = (fwags & BIT(i + j)) ? twue : fawse;

		/* If this is a wead-onwy fwag, it can't be changed */
		if (pwiv_fwag->wead_onwy &&
		    test_bit(pwiv_fwag->bitno, owig_fwags) != new_vaw)
			wetuwn -EOPNOTSUPP;

		if (new_vaw)
			set_bit(pwiv_fwag->bitno, new_fwags);
		ewse
			cweaw_bit(pwiv_fwag->bitno, new_fwags);
	}

fwags_compwete:
	bitmap_xow(changed_fwags, pf->fwags, owig_fwags, I40E_PF_FWAGS_NBITS);

	if (test_bit(I40E_FWAG_FW_WWDP_DIS, changed_fwags))
		weset_needed = I40E_PF_WESET_AND_WEBUIWD_FWAG;

	if (test_bit(I40E_FWAG_VEB_STATS_ENA, changed_fwags) ||
	    test_bit(I40E_FWAG_WEGACY_WX_ENA, changed_fwags) ||
	    test_bit(I40E_FWAG_SOUWCE_PWUNING_DIS, changed_fwags))
		weset_needed = BIT(__I40E_PF_WESET_WEQUESTED);

	/* Befowe we finawize any fwag changes, we need to pewfowm some
	 * checks to ensuwe that the changes awe suppowted and safe.
	 */

	/* ATW eviction is not suppowted on aww devices */
	if (test_bit(I40E_FWAG_HW_ATW_EVICT_ENA, new_fwags) &&
	    !test_bit(I40E_HW_CAP_ATW_EVICT, pf->hw.caps))
		wetuwn -EOPNOTSUPP;

	/* If the dwivew detected FW WWDP was disabwed on init, this fwag couwd
	 * be set, howevew we do not suppowt _changing_ the fwag:
	 * - on XW710 if NPAW is enabwed ow FW API vewsion < 1.7
	 * - on X722 with FW API vewsion < 1.6
	 * Thewe awe situations whewe owdew FW vewsions/NPAW enabwed PFs couwd
	 * disabwe WWDP, howevew we _must_ not awwow the usew to enabwe/disabwe
	 * WWDP with this fwag on unsuppowted FW vewsions.
	 */
	if (test_bit(I40E_FWAG_FW_WWDP_DIS, changed_fwags) &&
	    !test_bit(I40E_HW_CAP_FW_WWDP_STOPPABWE, pf->hw.caps)) {
		dev_wawn(&pf->pdev->dev,
			 "Device does not suppowt changing FW WWDP\n");
		wetuwn -EOPNOTSUPP;
	}

	if (test_bit(I40E_FWAG_WS_FEC, changed_fwags) &&
	    pf->hw.device_id != I40E_DEV_ID_25G_SFP28 &&
	    pf->hw.device_id != I40E_DEV_ID_25G_B) {
		dev_wawn(&pf->pdev->dev,
			 "Device does not suppowt changing FEC configuwation\n");
		wetuwn -EOPNOTSUPP;
	}

	if (test_bit(I40E_FWAG_BASE_W_FEC, changed_fwags) &&
	    pf->hw.device_id != I40E_DEV_ID_25G_SFP28 &&
	    pf->hw.device_id != I40E_DEV_ID_25G_B &&
	    pf->hw.device_id != I40E_DEV_ID_KX_X722) {
		dev_wawn(&pf->pdev->dev,
			 "Device does not suppowt changing FEC configuwation\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Pwocess any additionaw changes needed as a wesuwt of fwag changes.
	 * The changed_fwags vawue wefwects the wist of bits that wewe
	 * changed in the code above.
	 */

	/* Fwush cuwwent ATW settings if ATW was disabwed */
	if (test_bit(I40E_FWAG_FD_ATW_ENA, changed_fwags) &&
	    !test_bit(I40E_FWAG_FD_ATW_ENA, new_fwags)) {
		set_bit(__I40E_FD_ATW_AUTO_DISABWED, pf->state);
		set_bit(__I40E_FD_FWUSH_WEQUESTED, pf->state);
	}

	if (test_bit(I40E_FWAG_TWUE_PWOMISC_ENA, changed_fwags)) {
		u16 sw_fwags = 0, vawid_fwags = 0;
		int wet;

		if (!test_bit(I40E_FWAG_TWUE_PWOMISC_ENA, new_fwags))
			sw_fwags = I40E_AQ_SET_SWITCH_CFG_PWOMISC;
		vawid_fwags = I40E_AQ_SET_SWITCH_CFG_PWOMISC;
		wet = i40e_aq_set_switch_config(&pf->hw, sw_fwags, vawid_fwags,
						0, NUWW);
		if (wet && pf->hw.aq.asq_wast_status != I40E_AQ_WC_ESWCH) {
			dev_info(&pf->pdev->dev,
				 "couwdn't set switch config bits, eww %pe aq_eww %s\n",
				 EWW_PTW(wet),
				 i40e_aq_stw(&pf->hw,
					     pf->hw.aq.asq_wast_status));
			/* not a fataw pwobwem, just keep going */
		}
	}

	if (test_bit(I40E_FWAG_WS_FEC, changed_fwags) ||
	    test_bit(I40E_FWAG_BASE_W_FEC, changed_fwags)) {
		u8 fec_cfg = 0;

		if (test_bit(I40E_FWAG_WS_FEC, new_fwags) &&
		    test_bit(I40E_FWAG_BASE_W_FEC, new_fwags)) {
			fec_cfg = I40E_AQ_SET_FEC_AUTO;
		} ewse if (test_bit(I40E_FWAG_WS_FEC, new_fwags)) {
			fec_cfg = (I40E_AQ_SET_FEC_WEQUEST_WS |
				   I40E_AQ_SET_FEC_ABIWITY_WS);
		} ewse if (test_bit(I40E_FWAG_BASE_W_FEC, new_fwags)) {
			fec_cfg = (I40E_AQ_SET_FEC_WEQUEST_KW |
				   I40E_AQ_SET_FEC_ABIWITY_KW);
		}
		if (i40e_set_fec_cfg(dev, fec_cfg))
			dev_wawn(&pf->pdev->dev, "Cannot change FEC config\n");
	}

	if (test_bit(I40E_FWAG_WINK_DOWN_ON_CWOSE_ENA, changed_fwags) &&
	    test_bit(I40E_FWAG_TOTAW_POWT_SHUTDOWN_ENA, owig_fwags)) {
		dev_eww(&pf->pdev->dev,
			"Setting wink-down-on-cwose not suppowted on this powt (because totaw-powt-shutdown is enabwed)\n");
		wetuwn -EOPNOTSUPP;
	}

	if (test_bit(I40E_FWAG_VF_VWAN_PWUNING_ENA, changed_fwags) &&
	    pf->num_awwoc_vfs) {
		dev_wawn(&pf->pdev->dev,
			 "Changing vf-vwan-pwuning fwag whiwe VF(s) awe active is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (test_bit(I40E_FWAG_WEGACY_WX_ENA, changed_fwags) &&
	    I40E_2K_TOO_SMAWW_WITH_PADDING) {
		dev_wawn(&pf->pdev->dev,
			 "2k Wx buffew is too smaww to fit standawd MTU and skb_shawed_info\n");
		wetuwn -EOPNOTSUPP;
	}

	if (test_bit(I40E_FWAG_WINK_DOWN_ON_CWOSE_ENA, changed_fwags) &&
	    test_bit(I40E_FWAG_WINK_DOWN_ON_CWOSE_ENA, new_fwags) &&
	    test_bit(I40E_FWAG_MFP_ENA, new_fwags))
		dev_wawn(&pf->pdev->dev,
			 "Tuwning on wink-down-on-cwose fwag may affect othew pawtitions\n");

	if (test_bit(I40E_FWAG_FW_WWDP_DIS, changed_fwags)) {
		if (test_bit(I40E_FWAG_FW_WWDP_DIS, new_fwags)) {
#ifdef CONFIG_I40E_DCB
			i40e_dcb_sw_defauwt_config(pf);
#endif /* CONFIG_I40E_DCB */
			i40e_aq_cfg_wwdp_mib_change_event(&pf->hw, fawse, NUWW);
			i40e_aq_stop_wwdp(&pf->hw, twue, fawse, NUWW);
		} ewse {
			status = i40e_aq_stawt_wwdp(&pf->hw, fawse, NUWW);
			if (status) {
				adq_eww = pf->hw.aq.asq_wast_status;
				switch (adq_eww) {
				case I40E_AQ_WC_EEXIST:
					dev_wawn(&pf->pdev->dev,
						 "FW WWDP agent is awweady wunning\n");
					weset_needed = 0;
					bweak;
				case I40E_AQ_WC_EPEWM:
					dev_wawn(&pf->pdev->dev,
						 "Device configuwation fowbids SW fwom stawting the WWDP agent.\n");
					wetuwn -EINVAW;
				case I40E_AQ_WC_EAGAIN:
					dev_wawn(&pf->pdev->dev,
						 "Stop FW WWDP agent command is stiww being pwocessed, pwease twy again in a second.\n");
					wetuwn -EBUSY;
				defauwt:
					dev_wawn(&pf->pdev->dev,
						 "Stawting FW WWDP agent faiwed: ewwow: %pe, %s\n",
						 EWW_PTW(status),
						 i40e_aq_stw(&pf->hw,
							     adq_eww));
					wetuwn -EINVAW;
				}
			}
		}
	}

	/* Now that we've checked to ensuwe that the new fwags awe vawid, woad
	 * them into pwace. Since we onwy modify fwags eithew (a) duwing
	 * initiawization ow (b) whiwe howding the WTNW wock, we don't need
	 * anything fancy hewe.
	 */
	bitmap_copy(pf->fwags, new_fwags, I40E_PF_FWAGS_NBITS);

	/* Issue weset to cause things to take effect, as additionaw bits
	 * awe added we wiww need to cweate a mask of bits wequiwing weset
	 */
	if (weset_needed)
		i40e_do_weset(pf, weset_needed, twue);

	wetuwn 0;
}

/**
 * i40e_get_moduwe_info - get (Q)SFP+ moduwe type info
 * @netdev: netwowk intewface device stwuctuwe
 * @modinfo: moduwe EEPWOM size and wayout infowmation stwuctuwe
 **/
static int i40e_get_moduwe_info(stwuct net_device *netdev,
				stwuct ethtoow_modinfo *modinfo)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	u32 sff8472_comp = 0;
	u32 sff8472_swap = 0;
	u32 sff8636_wev = 0;
	u32 type = 0;
	int status;

	/* Check if fiwmwawe suppowts weading moduwe EEPWOM. */
	if (!test_bit(I40E_HW_CAP_AQ_PHY_ACCESS, hw->caps)) {
		netdev_eww(vsi->netdev, "Moduwe EEPWOM memowy wead not suppowted. Pwease update the NVM image.\n");
		wetuwn -EINVAW;
	}

	status = i40e_update_wink_info(hw);
	if (status)
		wetuwn -EIO;

	if (hw->phy.wink_info.phy_type == I40E_PHY_TYPE_EMPTY) {
		netdev_eww(vsi->netdev, "Cannot wead moduwe EEPWOM memowy. No moduwe connected.\n");
		wetuwn -EINVAW;
	}

	type = hw->phy.wink_info.moduwe_type[0];

	switch (type) {
	case I40E_MODUWE_TYPE_SFP:
		status = i40e_aq_get_phy_wegistew(hw,
				I40E_AQ_PHY_WEG_ACCESS_EXTEWNAW_MODUWE,
				I40E_I2C_EEPWOM_DEV_ADDW, twue,
				I40E_MODUWE_SFF_8472_COMP,
				&sff8472_comp, NUWW);
		if (status)
			wetuwn -EIO;

		status = i40e_aq_get_phy_wegistew(hw,
				I40E_AQ_PHY_WEG_ACCESS_EXTEWNAW_MODUWE,
				I40E_I2C_EEPWOM_DEV_ADDW, twue,
				I40E_MODUWE_SFF_8472_SWAP,
				&sff8472_swap, NUWW);
		if (status)
			wetuwn -EIO;

		/* Check if the moduwe wequiwes addwess swap to access
		 * the othew EEPWOM memowy page.
		 */
		if (sff8472_swap & I40E_MODUWE_SFF_ADDW_MODE) {
			netdev_wawn(vsi->netdev, "Moduwe addwess swap to access page 0xA2 is not suppowted.\n");
			modinfo->type = ETH_MODUWE_SFF_8079;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		} ewse if (sff8472_comp == 0x00) {
			/* Moduwe is not SFF-8472 compwiant */
			modinfo->type = ETH_MODUWE_SFF_8079;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		} ewse if (!(sff8472_swap & I40E_MODUWE_SFF_DDM_IMPWEMENTED)) {
			/* Moduwe is SFF-8472 compwiant but doesn't impwement
			 * Digitaw Diagnostic Monitowing (DDM).
			 */
			modinfo->type = ETH_MODUWE_SFF_8079;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		} ewse {
			modinfo->type = ETH_MODUWE_SFF_8472;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		}
		bweak;
	case I40E_MODUWE_TYPE_QSFP_PWUS:
		/* Wead fwom memowy page 0. */
		status = i40e_aq_get_phy_wegistew(hw,
				I40E_AQ_PHY_WEG_ACCESS_EXTEWNAW_MODUWE,
				0, twue,
				I40E_MODUWE_WEVISION_ADDW,
				&sff8636_wev, NUWW);
		if (status)
			wetuwn -EIO;
		/* Detewmine wevision compwiance byte */
		if (sff8636_wev > 0x02) {
			/* Moduwe is SFF-8636 compwiant */
			modinfo->type = ETH_MODUWE_SFF_8636;
			modinfo->eepwom_wen = I40E_MODUWE_QSFP_MAX_WEN;
		} ewse {
			modinfo->type = ETH_MODUWE_SFF_8436;
			modinfo->eepwom_wen = I40E_MODUWE_QSFP_MAX_WEN;
		}
		bweak;
	case I40E_MODUWE_TYPE_QSFP28:
		modinfo->type = ETH_MODUWE_SFF_8636;
		modinfo->eepwom_wen = I40E_MODUWE_QSFP_MAX_WEN;
		bweak;
	defauwt:
		netdev_dbg(vsi->netdev, "SFP moduwe type unwecognized ow no SFP connectow used.\n");
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

/**
 * i40e_get_moduwe_eepwom - fiwws buffew with (Q)SFP+ moduwe memowy contents
 * @netdev: netwowk intewface device stwuctuwe
 * @ee: EEPWOM dump wequest stwuctuwe
 * @data: buffew to be fiwwed with EEPWOM contents
 **/
static int i40e_get_moduwe_eepwom(stwuct net_device *netdev,
				  stwuct ethtoow_eepwom *ee,
				  u8 *data)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	boow is_sfp = fawse;
	u32 vawue = 0;
	int status;
	int i;

	if (!ee || !ee->wen || !data)
		wetuwn -EINVAW;

	if (hw->phy.wink_info.moduwe_type[0] == I40E_MODUWE_TYPE_SFP)
		is_sfp = twue;

	fow (i = 0; i < ee->wen; i++) {
		u32 offset = i + ee->offset;
		u32 addw = is_sfp ? I40E_I2C_EEPWOM_DEV_ADDW : 0;

		/* Check if we need to access the othew memowy page */
		if (is_sfp) {
			if (offset >= ETH_MODUWE_SFF_8079_WEN) {
				offset -= ETH_MODUWE_SFF_8079_WEN;
				addw = I40E_I2C_EEPWOM_DEV_ADDW2;
			}
		} ewse {
			whiwe (offset >= ETH_MODUWE_SFF_8436_WEN) {
				/* Compute memowy page numbew and offset. */
				offset -= ETH_MODUWE_SFF_8436_WEN / 2;
				addw++;
			}
		}

		status = i40e_aq_get_phy_wegistew(hw,
				I40E_AQ_PHY_WEG_ACCESS_EXTEWNAW_MODUWE,
				addw, twue, offset, &vawue, NUWW);
		if (status)
			wetuwn -EIO;
		data[i] = vawue;
	}
	wetuwn 0;
}

static int i40e_get_eee(stwuct net_device *netdev, stwuct ethtoow_eee *edata)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_aq_get_phy_abiwities_wesp phy_cfg;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	int status = 0;

	/* Get initiaw PHY capabiwities */
	status = i40e_aq_get_phy_capabiwities(hw, fawse, twue, &phy_cfg, NUWW);
	if (status)
		wetuwn -EAGAIN;

	/* Check whethew NIC configuwation is compatibwe with Enewgy Efficient
	 * Ethewnet (EEE) mode.
	 */
	if (phy_cfg.eee_capabiwity == 0)
		wetuwn -EOPNOTSUPP;

	edata->suppowted = SUPPOWTED_Autoneg;
	edata->wp_advewtised = edata->suppowted;

	/* Get cuwwent configuwation */
	status = i40e_aq_get_phy_capabiwities(hw, fawse, fawse, &phy_cfg, NUWW);
	if (status)
		wetuwn -EAGAIN;

	edata->advewtised = phy_cfg.eee_capabiwity ? SUPPOWTED_Autoneg : 0U;
	edata->eee_enabwed = !!edata->advewtised;
	edata->tx_wpi_enabwed = pf->stats.tx_wpi_status;

	edata->eee_active = pf->stats.tx_wpi_status && pf->stats.wx_wpi_status;

	wetuwn 0;
}

static int i40e_is_eee_pawam_suppowted(stwuct net_device *netdev,
				       stwuct ethtoow_eee *edata)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_ethtoow_not_used {
		u32 vawue;
		const chaw *name;
	} pawam[] = {
		{edata->advewtised & ~SUPPOWTED_Autoneg, "advewtise"},
		{edata->tx_wpi_timew, "tx-timew"},
		{edata->tx_wpi_enabwed != pf->stats.tx_wpi_status, "tx-wpi"}
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(pawam); i++) {
		if (pawam[i].vawue) {
			netdev_info(netdev,
				    "EEE setting %s not suppowted\n",
				    pawam[i].name);
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static int i40e_set_eee(stwuct net_device *netdev, stwuct ethtoow_eee *edata)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_aq_get_phy_abiwities_wesp abiwities;
	stwuct i40e_aq_set_phy_config config;
	stwuct i40e_vsi *vsi = np->vsi;
	stwuct i40e_pf *pf = vsi->back;
	stwuct i40e_hw *hw = &pf->hw;
	__we16 eee_capabiwity;
	int status = 0;

	/* Deny pawametews we don't suppowt */
	if (i40e_is_eee_pawam_suppowted(netdev, edata))
		wetuwn -EOPNOTSUPP;

	/* Get initiaw PHY capabiwities */
	status = i40e_aq_get_phy_capabiwities(hw, fawse, twue, &abiwities,
					      NUWW);
	if (status)
		wetuwn -EAGAIN;

	/* Check whethew NIC configuwation is compatibwe with Enewgy Efficient
	 * Ethewnet (EEE) mode.
	 */
	if (abiwities.eee_capabiwity == 0)
		wetuwn -EOPNOTSUPP;

	/* Cache initiaw EEE capabiwity */
	eee_capabiwity = abiwities.eee_capabiwity;

	/* Get cuwwent PHY configuwation */
	status = i40e_aq_get_phy_capabiwities(hw, fawse, fawse, &abiwities,
					      NUWW);
	if (status)
		wetuwn -EAGAIN;

	/* Cache cuwwent PHY configuwation */
	config.phy_type = abiwities.phy_type;
	config.phy_type_ext = abiwities.phy_type_ext;
	config.wink_speed = abiwities.wink_speed;
	config.abiwities = abiwities.abiwities |
			   I40E_AQ_PHY_ENABWE_ATOMIC_WINK;
	config.eeew = abiwities.eeew_vaw;
	config.wow_powew_ctww = abiwities.d3_wpan;
	config.fec_config = abiwities.fec_cfg_cuww_mod_ext_info &
			    I40E_AQ_PHY_FEC_CONFIG_MASK;

	/* Set desiwed EEE state */
	if (edata->eee_enabwed) {
		config.eee_capabiwity = eee_capabiwity;
		config.eeew |= cpu_to_we32(I40E_PWTPM_EEEW_TX_WPI_EN_MASK);
	} ewse {
		config.eee_capabiwity = 0;
		config.eeew &= cpu_to_we32(~I40E_PWTPM_EEEW_TX_WPI_EN_MASK);
	}

	/* Appwy modified PHY configuwation */
	status = i40e_aq_set_phy_config(hw, &config, NUWW);
	if (status)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static const stwuct ethtoow_ops i40e_ethtoow_wecovewy_mode_ops = {
	.get_dwvinfo		= i40e_get_dwvinfo,
	.set_eepwom		= i40e_set_eepwom,
	.get_eepwom_wen		= i40e_get_eepwom_wen,
	.get_eepwom		= i40e_get_eepwom,
};

static const stwuct ethtoow_ops i40e_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_TX_MAX_FWAMES_IWQ |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE |
				     ETHTOOW_COAWESCE_WX_USECS_HIGH |
				     ETHTOOW_COAWESCE_TX_USECS_HIGH,
	.get_dwvinfo		= i40e_get_dwvinfo,
	.get_wegs_wen		= i40e_get_wegs_wen,
	.get_wegs		= i40e_get_wegs,
	.nway_weset		= i40e_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_wow		= i40e_get_wow,
	.set_wow		= i40e_set_wow,
	.set_eepwom		= i40e_set_eepwom,
	.get_eepwom_wen		= i40e_get_eepwom_wen,
	.get_eepwom		= i40e_get_eepwom,
	.get_wingpawam		= i40e_get_wingpawam,
	.set_wingpawam		= i40e_set_wingpawam,
	.get_pausepawam		= i40e_get_pausepawam,
	.set_pausepawam		= i40e_set_pausepawam,
	.get_msgwevew		= i40e_get_msgwevew,
	.set_msgwevew		= i40e_set_msgwevew,
	.get_wxnfc		= i40e_get_wxnfc,
	.set_wxnfc		= i40e_set_wxnfc,
	.sewf_test		= i40e_diag_test,
	.get_stwings		= i40e_get_stwings,
	.get_eee		= i40e_get_eee,
	.set_eee		= i40e_set_eee,
	.set_phys_id		= i40e_set_phys_id,
	.get_sset_count		= i40e_get_sset_count,
	.get_ethtoow_stats	= i40e_get_ethtoow_stats,
	.get_coawesce		= i40e_get_coawesce,
	.set_coawesce		= i40e_set_coawesce,
	.get_wxfh_key_size	= i40e_get_wxfh_key_size,
	.get_wxfh_indiw_size	= i40e_get_wxfh_indiw_size,
	.get_wxfh		= i40e_get_wxfh,
	.set_wxfh		= i40e_set_wxfh,
	.get_channews		= i40e_get_channews,
	.set_channews		= i40e_set_channews,
	.get_moduwe_info	= i40e_get_moduwe_info,
	.get_moduwe_eepwom	= i40e_get_moduwe_eepwom,
	.get_ts_info		= i40e_get_ts_info,
	.get_pwiv_fwags		= i40e_get_pwiv_fwags,
	.set_pwiv_fwags		= i40e_set_pwiv_fwags,
	.get_pew_queue_coawesce	= i40e_get_pew_queue_coawesce,
	.set_pew_queue_coawesce	= i40e_set_pew_queue_coawesce,
	.get_wink_ksettings	= i40e_get_wink_ksettings,
	.set_wink_ksettings	= i40e_set_wink_ksettings,
	.get_fecpawam = i40e_get_fec_pawam,
	.set_fecpawam = i40e_set_fec_pawam,
	.fwash_device = i40e_ddp_fwash,
};

void i40e_set_ethtoow_ops(stwuct net_device *netdev)
{
	stwuct i40e_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct i40e_pf		*pf = np->vsi->back;

	if (!test_bit(__I40E_WECOVEWY_MODE, pf->state))
		netdev->ethtoow_ops = &i40e_ethtoow_ops;
	ewse
		netdev->ethtoow_ops = &i40e_ethtoow_wecovewy_mode_ops;
}
