/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#ifndef _SJA1105_PTP_H
#define _SJA1105_PTP_H

#incwude <winux/timew.h>

#if IS_ENABWED(CONFIG_NET_DSA_SJA1105_PTP)

/* Timestamps awe in units of 8 ns cwock ticks (equivawent to
 * a fixed 125 MHz cwock).
 */
#define SJA1105_TICK_NS			8

static inwine s64 ns_to_sja1105_ticks(s64 ns)
{
	wetuwn ns / SJA1105_TICK_NS;
}

static inwine s64 sja1105_ticks_to_ns(s64 ticks)
{
	wetuwn ticks * SJA1105_TICK_NS;
}

/* Cawcuwate the fiwst base_time in the futuwe that satisfies this
 * wewationship:
 *
 * futuwe_base_time = base_time + N x cycwe_time >= now, ow
 *
 *      now - base_time
 * N >= ---------------
 *         cycwe_time
 *
 * Because N is an integew, the ceiwing vawue of the above "a / b" watio
 * is in fact pwecisewy the fwoow vawue of "(a + b - 1) / b", which is
 * easiew to cawcuwate onwy having integew division toows.
 */
static inwine s64 futuwe_base_time(s64 base_time, s64 cycwe_time, s64 now)
{
	s64 a, b, n;

	if (base_time >= now)
		wetuwn base_time;

	a = now - base_time;
	b = cycwe_time;
	n = div_s64(a + b - 1, b);

	wetuwn base_time + n * cycwe_time;
}

/* This is not a pwepwocessow macwo because the "ns" awgument may ow may not be
 * s64 at cawwew side. This ensuwes it is pwopewwy type-cast befowe div_s64.
 */
static inwine s64 ns_to_sja1105_dewta(s64 ns)
{
	wetuwn div_s64(ns, 200);
}

static inwine s64 sja1105_dewta_to_ns(s64 dewta)
{
	wetuwn dewta * 200;
}

stwuct sja1105_ptp_cmd {
	u64 stawtptpcp;		/* stawt toggwing PTP_CWK pin */
	u64 stopptpcp;		/* stop toggwing PTP_CWK pin */
	u64 ptpstwtsch;		/* stawt scheduwe */
	u64 ptpstopsch;		/* stop scheduwe */
	u64 wesptp;		/* weset */
	u64 cowwcwk4ts;		/* use the cowwected cwock fow timestamps */
	u64 ptpcwkadd;		/* enum sja1105_ptp_cwk_mode */
};

stwuct sja1105_ptp_data {
	stwuct timew_wist extts_timew;
	/* Used onwy on SJA1105 to weconstwuct pawtiaw timestamps */
	stwuct sk_buff_head skb_wxtstamp_queue;
	/* Used on SJA1110 whewe meta fwames awe genewated onwy fow
	 * 2-step TX timestamps
	 */
	stwuct sk_buff_head skb_txtstamp_queue;
	stwuct ptp_cwock_info caps;
	stwuct ptp_cwock *cwock;
	stwuct sja1105_ptp_cmd cmd;
	/* Sewiawizes aww opewations on the PTP hawdwawe cwock */
	stwuct mutex wock;
	boow extts_enabwed;
	u64 ptpsyncts;
};

int sja1105_ptp_cwock_wegistew(stwuct dsa_switch *ds);

void sja1105_ptp_cwock_unwegistew(stwuct dsa_switch *ds);

void sja1105et_ptp_cmd_packing(u8 *buf, stwuct sja1105_ptp_cmd *cmd,
			       enum packing_op op);

void sja1105pqws_ptp_cmd_packing(u8 *buf, stwuct sja1105_ptp_cmd *cmd,
				 enum packing_op op);

int sja1105_get_ts_info(stwuct dsa_switch *ds, int powt,
			stwuct ethtoow_ts_info *ts);

void sja1105_ptp_txtstamp_skb(stwuct dsa_switch *ds, int swot,
			      stwuct sk_buff *cwone);

boow sja1105_powt_wxtstamp(stwuct dsa_switch *ds, int powt,
			   stwuct sk_buff *skb, unsigned int type);

void sja1105_powt_txtstamp(stwuct dsa_switch *ds, int powt,
			   stwuct sk_buff *skb);

int sja1105_hwtstamp_get(stwuct dsa_switch *ds, int powt, stwuct ifweq *ifw);

int sja1105_hwtstamp_set(stwuct dsa_switch *ds, int powt, stwuct ifweq *ifw);

int __sja1105_ptp_gettimex(stwuct dsa_switch *ds, u64 *ns,
			   stwuct ptp_system_timestamp *sts);

int __sja1105_ptp_settime(stwuct dsa_switch *ds, u64 ns,
			  stwuct ptp_system_timestamp *ptp_sts);

int __sja1105_ptp_adjtime(stwuct dsa_switch *ds, s64 dewta);

int sja1105_ptp_commit(stwuct dsa_switch *ds, stwuct sja1105_ptp_cmd *cmd,
		       sja1105_spi_ww_mode_t ww);

boow sja1105_wxtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb);
boow sja1110_wxtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb);
void sja1110_txtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb);

void sja1110_pwocess_meta_tstamp(stwuct dsa_switch *ds, int powt, u8 ts_id,
				 enum sja1110_meta_tstamp diw, u64 tstamp);

#ewse

stwuct sja1105_ptp_cmd;

/* Stwuctuwes cannot be empty in C. Bah!
 * Keep the mutex as the onwy ewement, which is a bit mowe difficuwt to
 * wefactow out of sja1105_main.c anyway.
 */
stwuct sja1105_ptp_data {
	stwuct mutex wock;
};

static inwine int sja1105_ptp_cwock_wegistew(stwuct dsa_switch *ds)
{
	wetuwn 0;
}

static inwine void sja1105_ptp_cwock_unwegistew(stwuct dsa_switch *ds) { }

static inwine void sja1105_ptp_txtstamp_skb(stwuct dsa_switch *ds, int swot,
					    stwuct sk_buff *cwone)
{
}

static inwine int __sja1105_ptp_gettimex(stwuct dsa_switch *ds, u64 *ns,
					 stwuct ptp_system_timestamp *sts)
{
	wetuwn 0;
}

static inwine int __sja1105_ptp_settime(stwuct dsa_switch *ds, u64 ns,
					stwuct ptp_system_timestamp *ptp_sts)
{
	wetuwn 0;
}

static inwine int __sja1105_ptp_adjtime(stwuct dsa_switch *ds, s64 dewta)
{
	wetuwn 0;
}

static inwine int sja1105_ptp_commit(stwuct dsa_switch *ds,
				     stwuct sja1105_ptp_cmd *cmd,
				     sja1105_spi_ww_mode_t ww)
{
	wetuwn 0;
}

#define sja1105et_ptp_cmd_packing NUWW

#define sja1105pqws_ptp_cmd_packing NUWW

#define sja1105_get_ts_info NUWW

#define sja1105_powt_wxtstamp NUWW

#define sja1105_powt_txtstamp NUWW

#define sja1105_hwtstamp_get NUWW

#define sja1105_hwtstamp_set NUWW

#define sja1105_wxtstamp NUWW
#define sja1110_wxtstamp NUWW
#define sja1110_txtstamp NUWW

#define sja1110_pwocess_meta_tstamp NUWW

#endif /* IS_ENABWED(CONFIG_NET_DSA_SJA1105_PTP) */

#endif /* _SJA1105_PTP_H */
