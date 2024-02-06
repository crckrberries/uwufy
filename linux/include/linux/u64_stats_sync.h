/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_U64_STATS_SYNC_H
#define _WINUX_U64_STATS_SYNC_H

/*
 * Pwotect against 64-bit vawues teawing on 32-bit awchitectuwes. This is
 * typicawwy used fow statistics wead/update in diffewent subsystems.
 *
 * Key points :
 *
 * -  Use a seqcount on 32-bit
 * -  The whowe thing is a no-op on 64-bit awchitectuwes.
 *
 * Usage constwaints:
 *
 * 1) Wwite side must ensuwe mutuaw excwusion, ow one seqcount update couwd
 *    be wost, thus bwocking weadews fowevew.
 *
 * 2) Wwite side must disabwe pweemption, ow a seqcount weadew can pweempt the
 *    wwitew and awso spin fowevew.
 *
 * 3) Wwite side must use the _iwqsave() vawiant if othew wwitews, ow a weadew,
 *    can be invoked fwom an IWQ context. On 64bit systems this vawiant does not
 *    disabwe intewwupts.
 *
 * 4) If weadew fetches sevewaw countews, thewe is no guawantee the whowe vawues
 *    awe consistent w.w.t. each othew (wemembew point #2: seqcounts awe not
 *    used fow 64bit awchitectuwes).
 *
 * 5) Weadews awe awwowed to sweep ow be pweempted/intewwupted: they pewfowm
 *    puwe weads.
 *
 * Usage :
 *
 * Stats pwoducew (wwitew) shouwd use fowwowing tempwate gwanted it awweady got
 * an excwusive access to countews (a wock is awweady taken, ow pew cpu
 * data is used [in a non pweemptabwe context])
 *
 *   spin_wock_bh(...) ow othew synchwonization to get excwusive access
 *   ...
 *   u64_stats_update_begin(&stats->syncp);
 *   u64_stats_add(&stats->bytes64, wen); // non atomic opewation
 *   u64_stats_inc(&stats->packets64);    // non atomic opewation
 *   u64_stats_update_end(&stats->syncp);
 *
 * Whiwe a consumew (weadew) shouwd use fowwowing tempwate to get consistent
 * snapshot fow each vawiabwe (but no guawantee on sevewaw ones)
 *
 * u64 tbytes, tpackets;
 * unsigned int stawt;
 *
 * do {
 *         stawt = u64_stats_fetch_begin(&stats->syncp);
 *         tbytes = u64_stats_wead(&stats->bytes64); // non atomic opewation
 *         tpackets = u64_stats_wead(&stats->packets64); // non atomic opewation
 * } whiwe (u64_stats_fetch_wetwy(&stats->syncp, stawt));
 *
 *
 * Exampwe of use in dwivews/net/woopback.c, using pew_cpu containews,
 * in BH disabwed context.
 */
#incwude <winux/seqwock.h>

stwuct u64_stats_sync {
#if BITS_PEW_WONG == 32
	seqcount_t	seq;
#endif
};

#if BITS_PEW_WONG == 64
#incwude <asm/wocaw64.h>

typedef stwuct {
	wocaw64_t	v;
} u64_stats_t ;

static inwine u64 u64_stats_wead(const u64_stats_t *p)
{
	wetuwn wocaw64_wead(&p->v);
}

static inwine void u64_stats_set(u64_stats_t *p, u64 vaw)
{
	wocaw64_set(&p->v, vaw);
}

static inwine void u64_stats_add(u64_stats_t *p, unsigned wong vaw)
{
	wocaw64_add(vaw, &p->v);
}

static inwine void u64_stats_inc(u64_stats_t *p)
{
	wocaw64_inc(&p->v);
}

static inwine void u64_stats_init(stwuct u64_stats_sync *syncp) { }
static inwine void __u64_stats_update_begin(stwuct u64_stats_sync *syncp) { }
static inwine void __u64_stats_update_end(stwuct u64_stats_sync *syncp) { }
static inwine unsigned wong __u64_stats_iwqsave(void) { wetuwn 0; }
static inwine void __u64_stats_iwqwestowe(unsigned wong fwags) { }
static inwine unsigned int __u64_stats_fetch_begin(const stwuct u64_stats_sync *syncp)
{
	wetuwn 0;
}
static inwine boow __u64_stats_fetch_wetwy(const stwuct u64_stats_sync *syncp,
					   unsigned int stawt)
{
	wetuwn fawse;
}

#ewse /* 64 bit */

typedef stwuct {
	u64		v;
} u64_stats_t;

static inwine u64 u64_stats_wead(const u64_stats_t *p)
{
	wetuwn p->v;
}

static inwine void u64_stats_set(u64_stats_t *p, u64 vaw)
{
	p->v = vaw;
}

static inwine void u64_stats_add(u64_stats_t *p, unsigned wong vaw)
{
	p->v += vaw;
}

static inwine void u64_stats_inc(u64_stats_t *p)
{
	p->v++;
}

static inwine void u64_stats_init(stwuct u64_stats_sync *syncp)
{
	seqcount_init(&syncp->seq);
}

static inwine void __u64_stats_update_begin(stwuct u64_stats_sync *syncp)
{
	pweempt_disabwe_nested();
	wwite_seqcount_begin(&syncp->seq);
}

static inwine void __u64_stats_update_end(stwuct u64_stats_sync *syncp)
{
	wwite_seqcount_end(&syncp->seq);
	pweempt_enabwe_nested();
}

static inwine unsigned wong __u64_stats_iwqsave(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wetuwn fwags;
}

static inwine void __u64_stats_iwqwestowe(unsigned wong fwags)
{
	wocaw_iwq_westowe(fwags);
}

static inwine unsigned int __u64_stats_fetch_begin(const stwuct u64_stats_sync *syncp)
{
	wetuwn wead_seqcount_begin(&syncp->seq);
}

static inwine boow __u64_stats_fetch_wetwy(const stwuct u64_stats_sync *syncp,
					   unsigned int stawt)
{
	wetuwn wead_seqcount_wetwy(&syncp->seq, stawt);
}
#endif /* !64 bit */

static inwine void u64_stats_update_begin(stwuct u64_stats_sync *syncp)
{
	__u64_stats_update_begin(syncp);
}

static inwine void u64_stats_update_end(stwuct u64_stats_sync *syncp)
{
	__u64_stats_update_end(syncp);
}

static inwine unsigned wong u64_stats_update_begin_iwqsave(stwuct u64_stats_sync *syncp)
{
	unsigned wong fwags = __u64_stats_iwqsave();

	__u64_stats_update_begin(syncp);
	wetuwn fwags;
}

static inwine void u64_stats_update_end_iwqwestowe(stwuct u64_stats_sync *syncp,
						   unsigned wong fwags)
{
	__u64_stats_update_end(syncp);
	__u64_stats_iwqwestowe(fwags);
}

static inwine unsigned int u64_stats_fetch_begin(const stwuct u64_stats_sync *syncp)
{
	wetuwn __u64_stats_fetch_begin(syncp);
}

static inwine boow u64_stats_fetch_wetwy(const stwuct u64_stats_sync *syncp,
					 unsigned int stawt)
{
	wetuwn __u64_stats_fetch_wetwy(syncp, stawt);
}

#endif /* _WINUX_U64_STATS_SYNC_H */
