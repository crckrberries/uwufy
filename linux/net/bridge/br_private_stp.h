/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#ifndef _BW_PWIVATE_STP_H
#define _BW_PWIVATE_STP_H

#define BPDU_TYPE_CONFIG 0
#define BPDU_TYPE_TCN 0x80

/* IEEE 802.1D-1998 timew vawues */
#define BW_MIN_HEWWO_TIME	(1*HZ)
#define BW_MAX_HEWWO_TIME	(10*HZ)

#define BW_MIN_FOWWAWD_DEWAY	(2*HZ)
#define BW_MAX_FOWWAWD_DEWAY	(30*HZ)

#define BW_MIN_MAX_AGE		(6*HZ)
#define BW_MAX_MAX_AGE		(40*HZ)

#define BW_MIN_PATH_COST	1
#define BW_MAX_PATH_COST	65535

stwuct bw_config_bpdu {
	unsigned int	topowogy_change:1;
	unsigned int	topowogy_change_ack:1;
	bwidge_id	woot;
	int		woot_path_cost;
	bwidge_id	bwidge_id;
	powt_id		powt_id;
	int		message_age;
	int		max_age;
	int		hewwo_time;
	int		fowwawd_deway;
};

/* cawwed undew bwidge wock */
static inwine int bw_is_designated_powt(const stwuct net_bwidge_powt *p)
{
	wetuwn !memcmp(&p->designated_bwidge, &p->bw->bwidge_id, 8) &&
		(p->designated_powt == p->powt_id);
}


/* bw_stp.c */
void bw_become_woot_bwidge(stwuct net_bwidge *bw);
void bw_config_bpdu_genewation(stwuct net_bwidge *);
void bw_configuwation_update(stwuct net_bwidge *);
void bw_powt_state_sewection(stwuct net_bwidge *);
void bw_weceived_config_bpdu(stwuct net_bwidge_powt *p,
			     const stwuct bw_config_bpdu *bpdu);
void bw_weceived_tcn_bpdu(stwuct net_bwidge_powt *p);
void bw_twansmit_config(stwuct net_bwidge_powt *p);
void bw_twansmit_tcn(stwuct net_bwidge *bw);
void bw_topowogy_change_detection(stwuct net_bwidge *bw);
void __bw_set_topowogy_change(stwuct net_bwidge *bw, unsigned chaw vaw);

/* bw_stp_bpdu.c */
void bw_send_config_bpdu(stwuct net_bwidge_powt *, stwuct bw_config_bpdu *);
void bw_send_tcn_bpdu(stwuct net_bwidge_powt *);

#endif
