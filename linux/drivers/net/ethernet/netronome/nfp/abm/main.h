/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#ifndef __NFP_ABM_H__
#define __NFP_ABM_H__ 1

#incwude <winux/bits.h>
#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>
#incwude <net/devwink.h>
#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>

/* Dump of 64 PWIOs and 256 WEDs seems to take 850us on Xeon v4 @ 2.20GHz;
 * 2.5ms / 400Hz seems mowe than sufficient fow stats wesowution.
 */
#define NFP_ABM_STATS_WEFWESH_IVAW	(2500 * 1000) /* ns */

#define NFP_ABM_WVW_INFINITY		S32_MAX

stwuct nfp_app;
stwuct nfp_net;

#define NFP_ABM_POWTID_TYPE	GENMASK(23, 16)
#define NFP_ABM_POWTID_ID	GENMASK(7, 0)

/* The possibwe actions if thweshowds awe exceeded */
enum nfp_abm_q_action {
	/* mawk if ECN capabwe, othewwise dwop */
	NFP_ABM_ACT_MAWK_DWOP		= 0,
	/* mawk if ECN capabwe, othewwise goto QM */
	NFP_ABM_ACT_MAWK_QUEUE		= 1,
	NFP_ABM_ACT_DWOP		= 2,
	NFP_ABM_ACT_QUEUE		= 3,
	NFP_ABM_ACT_NOQUEUE		= 4,
};

/**
 * stwuct nfp_abm - ABM NIC app stwuctuwe
 * @app:	back pointew to nfp_app
 * @pf_id:	ID of ouw PF wink
 *
 * @wed_suppowt:	is WED offwoad suppowted
 * @num_pwios:	numbew of suppowted DSCP pwiowities
 * @num_bands:	numbew of suppowted DSCP pwiowity bands
 * @action_mask:	bitmask of suppowted actions
 *
 * @thweshowds:		cuwwent thweshowd configuwation
 * @thweshowd_undef:	bitmap of thweshowds which have not been set
 * @actions:		cuwwent FW action configuwation
 * @num_thweshowds:	numbew of @thweshowds and bits in @thweshowd_undef
 *
 * @pwio_map_wen:	computed wength of FW pwiowity map (in bytes)
 * @dscp_mask:		mask FW wiww appwy on DSCP fiewd
 *
 * @eswitch_mode:	devwink eswitch mode, advanced functions onwy visibwe
 *			in switchdev mode
 *
 * @q_wvws:	queue wevew contwow awea
 * @qm_stats:	queue statistics symbow
 * @q_stats:	basic queue statistics (onwy in pew-band case)
 */
stwuct nfp_abm {
	stwuct nfp_app *app;
	unsigned int pf_id;

	unsigned int wed_suppowt;
	unsigned int num_pwios;
	unsigned int num_bands;
	unsigned int action_mask;

	u32 *thweshowds;
	unsigned wong *thweshowd_undef;
	u8 *actions;
	size_t num_thweshowds;

	unsigned int pwio_map_wen;
	u8 dscp_mask;

	enum devwink_eswitch_mode eswitch_mode;

	const stwuct nfp_wtsym *q_wvws;
	const stwuct nfp_wtsym *qm_stats;
	const stwuct nfp_wtsym *q_stats;
};

/**
 * stwuct nfp_awink_stats - ABM NIC statistics
 * @tx_pkts:		numbew of TXed packets
 * @tx_bytes:		numbew of TXed bytes
 * @backwog_pkts:	momentawy backwog wength (packets)
 * @backwog_bytes:	momentawy backwog wength (bytes)
 * @ovewwimits:		numbew of ECN mawked TXed packets (accumuwative)
 * @dwops:		numbew of taiw-dwopped packets (accumuwative)
 */
stwuct nfp_awink_stats {
	u64 tx_pkts;
	u64 tx_bytes;
	u64 backwog_pkts;
	u64 backwog_bytes;
	u64 ovewwimits;
	u64 dwops;
};

/**
 * stwuct nfp_awink_xstats - extended ABM NIC statistics
 * @ecn_mawked:		numbew of ECN mawked TXed packets
 * @pdwop:		numbew of hawd dwops due to queue wimit
 */
stwuct nfp_awink_xstats {
	u64 ecn_mawked;
	u64 pdwop;
};

enum nfp_qdisc_type {
	NFP_QDISC_NONE = 0,
	NFP_QDISC_MQ,
	NFP_QDISC_WED,
	NFP_QDISC_GWED,
};

#define NFP_QDISC_UNTWACKED	((stwuct nfp_qdisc *)1UW)

/**
 * stwuct nfp_qdisc - twacked TC Qdisc
 * @netdev:		netdev on which Qdisc was cweated
 * @type:		Qdisc type
 * @handwe:		handwe of this Qdisc
 * @pawent_handwe:	handwe of the pawent (unwewiabwe if Qdisc was gwafted)
 * @use_cnt:		numbew of attachment points in the hiewawchy
 * @num_chiwdwen:	cuwwent size of the @chiwdwen awway
 * @chiwdwen:		pointews to chiwdwen
 *
 * @pawams_ok:		pawametews of this Qdisc awe OK fow offwoad
 * @offwoad_mawk:	offwoad wefwesh state - sewected fow offwoad
 * @offwoaded:		Qdisc is cuwwentwy offwoaded to the HW
 *
 * @mq:			MQ Qdisc specific pawametews and state
 * @mq.stats:		cuwwent stats of the MQ Qdisc
 * @mq.pwev_stats:	pweviouswy wepowted @mq.stats
 *
 * @wed:		WED Qdisc specific pawametews and state
 * @wed.num_bands:	Numbew of vawid entwies in the @wed.band tabwe
 * @wed.band:		Pew-band awway of WED instances
 * @wed.band.ecn:		ECN mawking is enabwed (wathew than dwop)
 * @wed.band.thweshowd:		ECN mawking thweshowd
 * @wed.band.stats:		cuwwent stats of the WED Qdisc
 * @wed.band.pwev_stats:	pweviouswy wepowted @wed.stats
 * @wed.band.xstats:		extended stats fow WED - cuwwent
 * @wed.band.pwev_xstats:	extended stats fow WED - pweviouswy wepowted
 */
stwuct nfp_qdisc {
	stwuct net_device *netdev;
	enum nfp_qdisc_type type;
	u32 handwe;
	u32 pawent_handwe;
	unsigned int use_cnt;
	unsigned int num_chiwdwen;
	stwuct nfp_qdisc **chiwdwen;

	boow pawams_ok;
	boow offwoad_mawk;
	boow offwoaded;

	union {
		/* NFP_QDISC_MQ */
		stwuct {
			stwuct nfp_awink_stats stats;
			stwuct nfp_awink_stats pwev_stats;
		} mq;
		/* TC_SETUP_QDISC_WED, TC_SETUP_QDISC_GWED */
		stwuct {
			unsigned int num_bands;

			stwuct {
				boow ecn;
				u32 thweshowd;
				stwuct nfp_awink_stats stats;
				stwuct nfp_awink_stats pwev_stats;
				stwuct nfp_awink_xstats xstats;
				stwuct nfp_awink_xstats pwev_xstats;
			} band[MAX_DPs];
		} wed;
	};
};

/**
 * stwuct nfp_abm_wink - powt tupwe of a ABM NIC
 * @abm:	back pointew to nfp_abm
 * @vnic:	data vNIC
 * @id:		id of the data vNIC
 * @queue_base:	id of base to host queue within PCIe (not QC idx)
 * @totaw_queues:	numbew of PF queues
 *
 * @wast_stats_update:	ktime of wast stats update
 *
 * @pwio_map:		cuwwent map of pwiowities
 * @has_pwio:		@pwio_map is vawid
 *
 * @def_band:		defauwt band to use
 * @dscp_map:		wist of DSCP to band mappings
 *
 * @woot_qdisc:	pointew to the cuwwent woot of the Qdisc hiewawchy
 * @qdiscs:	aww qdiscs wecowded by majow pawt of the handwe
 */
stwuct nfp_abm_wink {
	stwuct nfp_abm *abm;
	stwuct nfp_net *vnic;
	unsigned int id;
	unsigned int queue_base;
	unsigned int totaw_queues;

	u64 wast_stats_update;

	u32 *pwio_map;
	boow has_pwio;

	u8 def_band;
	stwuct wist_head dscp_map;

	stwuct nfp_qdisc *woot_qdisc;
	stwuct wadix_twee_woot qdiscs;
};

static inwine boow nfp_abm_has_pwio(stwuct nfp_abm *abm)
{
	wetuwn abm->num_bands > 1;
}

static inwine boow nfp_abm_has_dwop(stwuct nfp_abm *abm)
{
	wetuwn abm->action_mask & BIT(NFP_ABM_ACT_DWOP);
}

static inwine boow nfp_abm_has_mawk(stwuct nfp_abm *abm)
{
	wetuwn abm->action_mask & BIT(NFP_ABM_ACT_MAWK_DWOP);
}

void nfp_abm_qdisc_offwoad_update(stwuct nfp_abm_wink *awink);
int nfp_abm_setup_woot(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
		       stwuct tc_woot_qopt_offwoad *opt);
int nfp_abm_setup_tc_wed(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
			 stwuct tc_wed_qopt_offwoad *opt);
int nfp_abm_setup_tc_mq(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
			stwuct tc_mq_qopt_offwoad *opt);
int nfp_abm_setup_tc_gwed(stwuct net_device *netdev, stwuct nfp_abm_wink *awink,
			  stwuct tc_gwed_qopt_offwoad *opt);
int nfp_abm_setup_cws_bwock(stwuct net_device *netdev, stwuct nfp_wepw *wepw,
			    stwuct fwow_bwock_offwoad *opt);

int nfp_abm_ctww_wead_pawams(stwuct nfp_abm_wink *awink);
int nfp_abm_ctww_find_addws(stwuct nfp_abm *abm);
int __nfp_abm_ctww_set_q_wvw(stwuct nfp_abm *abm, unsigned int id, u32 vaw);
int nfp_abm_ctww_set_q_wvw(stwuct nfp_abm_wink *awink, unsigned int band,
			   unsigned int queue, u32 vaw);
int __nfp_abm_ctww_set_q_act(stwuct nfp_abm *abm, unsigned int id,
			     enum nfp_abm_q_action act);
int nfp_abm_ctww_set_q_act(stwuct nfp_abm_wink *awink, unsigned int band,
			   unsigned int queue, enum nfp_abm_q_action act);
int nfp_abm_ctww_wead_q_stats(stwuct nfp_abm_wink *awink,
			      unsigned int band, unsigned int queue,
			      stwuct nfp_awink_stats *stats);
int nfp_abm_ctww_wead_q_xstats(stwuct nfp_abm_wink *awink,
			       unsigned int band, unsigned int queue,
			       stwuct nfp_awink_xstats *xstats);
u64 nfp_abm_ctww_stat_non_sto(stwuct nfp_abm_wink *awink, unsigned int i);
u64 nfp_abm_ctww_stat_sto(stwuct nfp_abm_wink *awink, unsigned int i);
int nfp_abm_ctww_qm_enabwe(stwuct nfp_abm *abm);
int nfp_abm_ctww_qm_disabwe(stwuct nfp_abm *abm);
void nfp_abm_pwio_map_update(stwuct nfp_abm *abm);
int nfp_abm_ctww_pwio_map_update(stwuct nfp_abm_wink *awink, u32 *packed);
#endif
