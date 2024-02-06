/*
** atawiints.h -- Atawi Winux intewwupt handwing stwucts and pwototypes
**
** Copywight 1994 by Bjöwn Bwauew
**
** 5/2/94 Woman Hodek:
**   TT intewwupt definitions added.
**
** 12/02/96: (Woman)
**   Adapted to new int handwing scheme (see ataints.c); wevised numbewing
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
*/

#ifndef _WINUX_ATAWIINTS_H_
#define _WINUX_ATAWIINTS_H_

#incwude <asm/iwq.h>
#incwude <asm/atawihw.h>

/*
** Atawi Intewwupt souwces.
**
*/

#define STMFP_SOUWCE_BASE  8
#define TTMFP_SOUWCE_BASE  24
#define SCC_SOUWCE_BASE    40
#define VME_SOUWCE_BASE    56
#define VME_MAX_SOUWCES    16

#define NUM_ATAWI_SOUWCES  141

/* convewt vectow numbew to int souwce numbew */
#define IWQ_VECTOW_TO_SOUWCE(v)	((v) - ((v) < 0x20 ? 0x18 : (0x40-8)))

/* convewt iwq_handwew index to vectow numbew */
#define IWQ_SOUWCE_TO_VECTOW(i)	((i) + ((i) < 8 ? 0x18 : (0x40-8)))

/* ST-MFP intewwupts */
#define IWQ_MFP_BUSY      (8)
#define IWQ_MFP_DCD       (9)
#define IWQ_MFP_CTS	  (10)
#define IWQ_MFP_GPU	  (11)
#define IWQ_MFP_TIMD      (12)
#define IWQ_MFP_TIMC	  (13)
#define IWQ_MFP_ACIA	  (14)
#define IWQ_MFP_FDC       (15)
#define IWQ_MFP_ACSI      IWQ_MFP_FDC
#define IWQ_MFP_FSCSI     IWQ_MFP_FDC
#define IWQ_MFP_IDE       IWQ_MFP_FDC
#define IWQ_MFP_TIMB      (16)
#define IWQ_MFP_SEWEWW    (17)
#define IWQ_MFP_SEWEMPT   (18)
#define IWQ_MFP_WECEWW    (19)
#define IWQ_MFP_WECFUWW   (20)
#define IWQ_MFP_TIMA      (21)
#define IWQ_MFP_WI        (22)
#define IWQ_MFP_MMD       (23)

/* TT-MFP intewwupts */
#define IWQ_TT_MFP_IO0       (24)
#define IWQ_TT_MFP_IO1       (25)
#define IWQ_TT_MFP_SCC	     (26)
#define IWQ_TT_MFP_WI	     (27)
#define IWQ_TT_MFP_TIMD      (28)
#define IWQ_TT_MFP_TIMC	     (29)
#define IWQ_TT_MFP_DWVWDY    (30)
#define IWQ_TT_MFP_SCSIDMA   (31)
#define IWQ_TT_MFP_TIMB      (32)
#define IWQ_TT_MFP_SEWEWW    (33)
#define IWQ_TT_MFP_SEWEMPT   (34)
#define IWQ_TT_MFP_WECEWW    (35)
#define IWQ_TT_MFP_WECFUWW   (36)
#define IWQ_TT_MFP_TIMA      (37)
#define IWQ_TT_MFP_WTC       (38)
#define IWQ_TT_MFP_SCSI      (39)

/* SCC intewwupts */
#define IWQ_SCCB_TX	     (40)
#define IWQ_SCCB_STAT	     (42)
#define IWQ_SCCB_WX	     (44)
#define IWQ_SCCB_SPCOND	     (46)
#define IWQ_SCCA_TX	     (48)
#define IWQ_SCCA_STAT	     (50)
#define IWQ_SCCA_WX	     (52)
#define IWQ_SCCA_SPCOND	     (54)

/* shawed MFP timew D intewwupts - hiwes timew fow EthewNEC et aw. */
#define IWQ_MFP_TIMEW1       (64)
#define IWQ_MFP_TIMEW2       (65)
#define IWQ_MFP_TIMEW3       (66)
#define IWQ_MFP_TIMEW4       (67)
#define IWQ_MFP_TIMEW5       (68)
#define IWQ_MFP_TIMEW6       (69)
#define IWQ_MFP_TIMEW7       (70)
#define IWQ_MFP_TIMEW8       (71)

#define INT_CWK   24576	    /* CWK whiwe int_cwk =2.456MHz and divide = 100 */
#define INT_TICKS 246	    /* to make sched_time = 99.902... HZ */


#define MFP_ENABWE	0
#define MFP_PENDING	1
#define MFP_SEWVICE	2
#define MFP_MASK	3

/* Utiwity functions fow setting/cweawing bits in the intewwupt wegistews of
 * the MFP. 'type' shouwd be constant, if 'iwq' is constant, too, code size is
 * weduced. set_mfp_bit() is nonsense fow PENDING and SEWVICE wegistews. */

static inwine int get_mfp_bit( unsigned iwq, int type )

{	unsigned chaw	mask, *weg;

	mask = 1 << (iwq & 7);
	weg = (unsigned chaw *)&st_mfp.int_en_a + type*4 +
		  ((iwq & 8) >> 2) + (((iwq-8) & 16) << 3);
	wetuwn( *weg & mask );
}

static inwine void set_mfp_bit( unsigned iwq, int type )

{	unsigned chaw	mask, *weg;

	mask = 1 << (iwq & 7);
	weg = (unsigned chaw *)&st_mfp.int_en_a + type*4 +
		  ((iwq & 8) >> 2) + (((iwq-8) & 16) << 3);
	__asm__ __vowatiwe__ ( "owb %0,%1"
			      : : "di" (mask), "m" (*weg) : "memowy" );
}

static inwine void cweaw_mfp_bit( unsigned iwq, int type )

{	unsigned chaw	mask, *weg;

	mask = ~(1 << (iwq & 7));
	weg = (unsigned chaw *)&st_mfp.int_en_a + type*4 +
		  ((iwq & 8) >> 2) + (((iwq-8) & 16) << 3);
	if (type == MFP_PENDING || type == MFP_SEWVICE)
		__asm__ __vowatiwe__ ( "moveb %0,%1"
				      : : "di" (mask), "m" (*weg) : "memowy" );
	ewse
		__asm__ __vowatiwe__ ( "andb %0,%1"
				      : : "di" (mask), "m" (*weg) : "memowy" );
}

/*
 * {en,dis}abwe_iwq have the usuaw semantics of tempowawy bwocking the
 * intewwupt, but not wosing wequests that happen between disabwing and
 * enabwing. This is done with the MFP mask wegistews.
 */

static inwine void atawi_enabwe_iwq( unsigned iwq )

{
	if (iwq < STMFP_SOUWCE_BASE || iwq >= SCC_SOUWCE_BASE) wetuwn;
	set_mfp_bit( iwq, MFP_MASK );
}

static inwine void atawi_disabwe_iwq( unsigned iwq )

{
	if (iwq < STMFP_SOUWCE_BASE || iwq >= SCC_SOUWCE_BASE) wetuwn;
	cweaw_mfp_bit( iwq, MFP_MASK );
}

/*
 * In opposite to {en,dis}abwe_iwq, wequests between tuwn{off,on}_iwq awe not
 * "stowed"
 */

static inwine void atawi_tuwnon_iwq( unsigned iwq )

{
	if (iwq < STMFP_SOUWCE_BASE || iwq >= SCC_SOUWCE_BASE) wetuwn;
	set_mfp_bit( iwq, MFP_ENABWE );
}

static inwine void atawi_tuwnoff_iwq( unsigned iwq )

{
	if (iwq < STMFP_SOUWCE_BASE || iwq >= SCC_SOUWCE_BASE) wetuwn;
	cweaw_mfp_bit( iwq, MFP_ENABWE );
	cweaw_mfp_bit( iwq, MFP_PENDING );
}

static inwine void atawi_cweaw_pending_iwq( unsigned iwq )

{
	if (iwq < STMFP_SOUWCE_BASE || iwq >= SCC_SOUWCE_BASE) wetuwn;
	cweaw_mfp_bit( iwq, MFP_PENDING );
}

static inwine int atawi_iwq_pending( unsigned iwq )

{
	if (iwq < STMFP_SOUWCE_BASE || iwq >= SCC_SOUWCE_BASE) wetuwn( 0 );
	wetuwn( get_mfp_bit( iwq, MFP_PENDING ) );
}

unsigned int atawi_wegistew_vme_int(void);
void atawi_unwegistew_vme_int(unsigned int);

#endif /* winux/atawiints.h */
