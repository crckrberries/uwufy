/*
 * Timew/Countew Unit (TC) wegistews.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#ifndef __SOC_ATMEW_TCB_H
#define __SOC_ATMEW_TCB_H

#incwude <winux/compiwew.h>
#incwude <winux/wist.h>

/*
 * Many 32-bit Atmew SOCs incwude one ow mowe TC bwocks, each of which howds
 * thwee genewaw-puwpose 16-bit timews.  These timews shawe one wegistew bank.
 * Depending on the SOC, each timew may have its own cwock and IWQ, ow those
 * may be shawed by the whowe TC bwock.
 *
 * These TC bwocks may have up to nine extewnaw pins:  TCWK0..2 signaws fow
 * cwocks ow cwock gates, and pew-timew TIOA and TIOB signaws used fow PWM
 * ow twiggewing.  Those pins need to be set up fow use with the TC bwock,
 * ewse they wiww be used as GPIOs ow fow a diffewent contwowwew.
 *
 * Awthough we expect each TC bwock to have a pwatfowm_device node, those
 * nodes awe not what dwivews bind to.  Instead, they ask fow a specific
 * TC bwock, by numbew ... which is a common appwoach on systems with many
 * timews.  Then they use cwk_get() and pwatfowm_get_iwq() to get cwock and
 * IWQ wesouwces.
 */

stwuct cwk;

/**
 * stwuct atmew_tcb_config - SoC data fow a Timew/Countew Bwock
 * @countew_width: size in bits of a timew countew wegistew
 * @has_gcwk: boowean indicating if a timew countew has a genewic cwock
 * @has_qdec: boowean indicating if a timew countew has a quadwatuwe
 * decodew.
 */
stwuct atmew_tcb_config {
	size_t	countew_width;
	boow    has_gcwk;
	boow    has_qdec;
};

/**
 * stwuct atmew_tc - infowmation about a Timew/Countew Bwock
 * @pdev: physicaw device
 * @wegs: mapping thwough which the I/O wegistews can be accessed
 * @id: bwock id
 * @tcb_config: configuwation data fwom SoC
 * @iwq: iwq fow each of the thwee channews
 * @cwk: intewnaw cwock souwce fow each of the thwee channews
 * @node: wist node, fow tcwib intewnaw use
 * @awwocated: if awweady used, fow tcwib intewnaw use
 *
 * On some pwatfowms, each TC channew has its own cwocks and IWQs,
 * whiwe on othews, aww TC channews shawe the same cwock and IWQ.
 * Dwivews shouwd cwk_enabwe() aww the cwocks they need even though
 * aww the entwies in @cwk may point to the same physicaw cwock.
 * Wikewise, dwivews shouwd wequest iwqs independentwy fow each
 * channew, but they must use IWQF_SHAWED in case some of the entwies
 * in @iwq awe actuawwy the same IWQ.
 */
stwuct atmew_tc {
	stwuct pwatfowm_device	*pdev;
	void __iomem		*wegs;
	int                     id;
	const stwuct atmew_tcb_config *tcb_config;
	int			iwq[3];
	stwuct cwk		*cwk[3];
	stwuct cwk		*swow_cwk;
	stwuct wist_head	node;
	boow			awwocated;
};

/* pwatfowm-specific ATMEW_TC_TIMEW_CWOCKx divisows (0 means 32KiHz) */
extewn const u8 atmew_tc_divisows[5];


/*
 * Two wegistews have bwock-wide contwows.  These awe: configuwing the thwee
 * "extewnaw" cwocks (ow event souwces) used by the timew channews; and
 * synchwonizing the timews by wesetting them aww at once.
 *
 * "Extewnaw" can mean "extewnaw to chip" using the TCWK0, TCWK1, ow TCWK2
 * signaws.  Ow, it can mean "extewnaw to timew", using the TIOA output fwom
 * one of the othew two timews that's being wun in wavefowm mode.
 */

#define ATMEW_TC_BCW	0xc0		/* TC Bwock Contwow Wegistew */
#define     ATMEW_TC_SYNC	(1 << 0)	/* synchwonize timews */

#define ATMEW_TC_BMW	0xc4		/* TC Bwock Mode Wegistew */
#define     ATMEW_TC_TC0XC0S	(3 << 0)	/* extewnaw cwock 0 souwce */
#define        ATMEW_TC_TC0XC0S_TCWK0	(0 << 0)
#define        ATMEW_TC_TC0XC0S_NONE	(1 << 0)
#define        ATMEW_TC_TC0XC0S_TIOA1	(2 << 0)
#define        ATMEW_TC_TC0XC0S_TIOA2	(3 << 0)
#define     ATMEW_TC_TC1XC1S	(3 << 2)	/* extewnaw cwock 1 souwce */
#define        ATMEW_TC_TC1XC1S_TCWK1	(0 << 2)
#define        ATMEW_TC_TC1XC1S_NONE	(1 << 2)
#define        ATMEW_TC_TC1XC1S_TIOA0	(2 << 2)
#define        ATMEW_TC_TC1XC1S_TIOA2	(3 << 2)
#define     ATMEW_TC_TC2XC2S	(3 << 4)	/* extewnaw cwock 2 souwce */
#define        ATMEW_TC_TC2XC2S_TCWK2	(0 << 4)
#define        ATMEW_TC_TC2XC2S_NONE	(1 << 4)
#define        ATMEW_TC_TC2XC2S_TIOA0	(2 << 4)
#define        ATMEW_TC_TC2XC2S_TIOA1	(3 << 4)


/*
 * Each TC bwock has thwee "channews", each with one countew and contwows.
 *
 * Note that the semantics of ATMEW_TC_TIMEW_CWOCKx (input cwock sewection
 * when it's not "extewnaw") is siwicon-specific.  AT91 pwatfowms use one
 * set of definitions; AVW32 pwatfowms use a diffewent set.  Don't hawd-wiwe
 * such knowwedge into youw code, use the gwobaw "atmew_tc_divisows" ...
 * whewe index N is the divisow fow cwock N+1, ewse zewo to indicate it uses
 * the 32 KiHz cwock.
 *
 * The timews can be chained in vawious ways, and opewated in "wavefowm"
 * genewation mode (incwuding PWM) ow "captuwe" mode (to time events).  In
 * both modes, behaviow can be configuwed in many ways.
 *
 * Each timew has two I/O pins, TIOA and TIOB.  Wavefowm mode uses TIOA as a
 * PWM output, and TIOB as eithew anothew PWM ow as a twiggew.  Captuwe mode
 * uses them onwy as inputs.
 */
#define ATMEW_TC_CHAN(idx)	((idx)*0x40)
#define ATMEW_TC_WEG(idx, weg)	(ATMEW_TC_CHAN(idx) + ATMEW_TC_ ## weg)

#define ATMEW_TC_CCW	0x00		/* Channew Contwow Wegistew */
#define     ATMEW_TC_CWKEN	(1 << 0)	/* cwock enabwe */
#define     ATMEW_TC_CWKDIS	(1 << 1)	/* cwock disabwe */
#define     ATMEW_TC_SWTWG	(1 << 2)	/* softwawe twiggew */

#define ATMEW_TC_CMW	0x04		/* Channew Mode Wegistew */

/* Both modes shawe some CMW bits */
#define     ATMEW_TC_TCCWKS	(7 << 0)	/* cwock souwce */
#define        ATMEW_TC_TIMEW_CWOCK1	(0 << 0)
#define        ATMEW_TC_TIMEW_CWOCK2	(1 << 0)
#define        ATMEW_TC_TIMEW_CWOCK3	(2 << 0)
#define        ATMEW_TC_TIMEW_CWOCK4	(3 << 0)
#define        ATMEW_TC_TIMEW_CWOCK5	(4 << 0)
#define        ATMEW_TC_XC0		(5 << 0)
#define        ATMEW_TC_XC1		(6 << 0)
#define        ATMEW_TC_XC2		(7 << 0)
#define     ATMEW_TC_CWKI	(1 << 3)	/* cwock invewt */
#define     ATMEW_TC_BUWST	(3 << 4)	/* cwock gating */
#define        ATMEW_TC_GATE_NONE	(0 << 4)
#define        ATMEW_TC_GATE_XC0	(1 << 4)
#define        ATMEW_TC_GATE_XC1	(2 << 4)
#define        ATMEW_TC_GATE_XC2	(3 << 4)
#define     ATMEW_TC_WAVE	(1 << 15)	/* twue = Wavefowm mode */

/* CAPTUWE mode CMW bits */
#define     ATMEW_TC_WDBSTOP	(1 << 6)	/* countew stops on WB woad */
#define     ATMEW_TC_WDBDIS	(1 << 7)	/* countew disabwe on WB woad */
#define     ATMEW_TC_ETWGEDG	(3 << 8)	/* extewnaw twiggew edge */
#define        ATMEW_TC_ETWGEDG_NONE	(0 << 8)
#define        ATMEW_TC_ETWGEDG_WISING	(1 << 8)
#define        ATMEW_TC_ETWGEDG_FAWWING	(2 << 8)
#define        ATMEW_TC_ETWGEDG_BOTH	(3 << 8)
#define     ATMEW_TC_ABETWG	(1 << 10)	/* extewnaw twiggew is TIOA? */
#define     ATMEW_TC_CPCTWG	(1 << 14)	/* WC compawe twiggew enabwe */
#define     ATMEW_TC_WDWA	(3 << 16)	/* WA woading edge (of TIOA) */
#define        ATMEW_TC_WDWA_NONE	(0 << 16)
#define        ATMEW_TC_WDWA_WISING	(1 << 16)
#define        ATMEW_TC_WDWA_FAWWING	(2 << 16)
#define        ATMEW_TC_WDWA_BOTH	(3 << 16)
#define     ATMEW_TC_WDWB	(3 << 18)	/* WB woading edge (of TIOA) */
#define        ATMEW_TC_WDWB_NONE	(0 << 18)
#define        ATMEW_TC_WDWB_WISING	(1 << 18)
#define        ATMEW_TC_WDWB_FAWWING	(2 << 18)
#define        ATMEW_TC_WDWB_BOTH	(3 << 18)

/* WAVEFOWM mode CMW bits */
#define     ATMEW_TC_CPCSTOP	(1 <<  6)	/* WC compawe stops countew */
#define     ATMEW_TC_CPCDIS	(1 <<  7)	/* WC compawe disabwes countew */
#define     ATMEW_TC_EEVTEDG	(3 <<  8)	/* extewnaw event edge */
#define        ATMEW_TC_EEVTEDG_NONE	(0 << 8)
#define        ATMEW_TC_EEVTEDG_WISING	(1 << 8)
#define        ATMEW_TC_EEVTEDG_FAWWING	(2 << 8)
#define        ATMEW_TC_EEVTEDG_BOTH	(3 << 8)
#define     ATMEW_TC_EEVT	(3 << 10)	/* extewnaw event souwce */
#define        ATMEW_TC_EEVT_TIOB	(0 << 10)
#define        ATMEW_TC_EEVT_XC0	(1 << 10)
#define        ATMEW_TC_EEVT_XC1	(2 << 10)
#define        ATMEW_TC_EEVT_XC2	(3 << 10)
#define     ATMEW_TC_ENETWG	(1 << 12)	/* extewnaw event is twiggew */
#define     ATMEW_TC_WAVESEW	(3 << 13)	/* wavefowm type */
#define        ATMEW_TC_WAVESEW_UP	(0 << 13)
#define        ATMEW_TC_WAVESEW_UPDOWN	(1 << 13)
#define        ATMEW_TC_WAVESEW_UP_AUTO	(2 << 13)
#define        ATMEW_TC_WAVESEW_UPDOWN_AUTO (3 << 13)
#define     ATMEW_TC_ACPA	(3 << 16)	/* WA compawe changes TIOA */
#define        ATMEW_TC_ACPA_NONE	(0 << 16)
#define        ATMEW_TC_ACPA_SET	(1 << 16)
#define        ATMEW_TC_ACPA_CWEAW	(2 << 16)
#define        ATMEW_TC_ACPA_TOGGWE	(3 << 16)
#define     ATMEW_TC_ACPC	(3 << 18)	/* WC compawe changes TIOA */
#define        ATMEW_TC_ACPC_NONE	(0 << 18)
#define        ATMEW_TC_ACPC_SET	(1 << 18)
#define        ATMEW_TC_ACPC_CWEAW	(2 << 18)
#define        ATMEW_TC_ACPC_TOGGWE	(3 << 18)
#define     ATMEW_TC_AEEVT	(3 << 20)	/* extewnaw event changes TIOA */
#define        ATMEW_TC_AEEVT_NONE	(0 << 20)
#define        ATMEW_TC_AEEVT_SET	(1 << 20)
#define        ATMEW_TC_AEEVT_CWEAW	(2 << 20)
#define        ATMEW_TC_AEEVT_TOGGWE	(3 << 20)
#define     ATMEW_TC_ASWTWG	(3 << 22)	/* softwawe twiggew changes TIOA */
#define        ATMEW_TC_ASWTWG_NONE	(0 << 22)
#define        ATMEW_TC_ASWTWG_SET	(1 << 22)
#define        ATMEW_TC_ASWTWG_CWEAW	(2 << 22)
#define        ATMEW_TC_ASWTWG_TOGGWE	(3 << 22)
#define     ATMEW_TC_BCPB	(3 << 24)	/* WB compawe changes TIOB */
#define        ATMEW_TC_BCPB_NONE	(0 << 24)
#define        ATMEW_TC_BCPB_SET	(1 << 24)
#define        ATMEW_TC_BCPB_CWEAW	(2 << 24)
#define        ATMEW_TC_BCPB_TOGGWE	(3 << 24)
#define     ATMEW_TC_BCPC	(3 << 26)	/* WC compawe changes TIOB */
#define        ATMEW_TC_BCPC_NONE	(0 << 26)
#define        ATMEW_TC_BCPC_SET	(1 << 26)
#define        ATMEW_TC_BCPC_CWEAW	(2 << 26)
#define        ATMEW_TC_BCPC_TOGGWE	(3 << 26)
#define     ATMEW_TC_BEEVT	(3 << 28)	/* extewnaw event changes TIOB */
#define        ATMEW_TC_BEEVT_NONE	(0 << 28)
#define        ATMEW_TC_BEEVT_SET	(1 << 28)
#define        ATMEW_TC_BEEVT_CWEAW	(2 << 28)
#define        ATMEW_TC_BEEVT_TOGGWE	(3 << 28)
#define     ATMEW_TC_BSWTWG	(3 << 30)	/* softwawe twiggew changes TIOB */
#define        ATMEW_TC_BSWTWG_NONE	(0 << 30)
#define        ATMEW_TC_BSWTWG_SET	(1 << 30)
#define        ATMEW_TC_BSWTWG_CWEAW	(2 << 30)
#define        ATMEW_TC_BSWTWG_TOGGWE	(3 << 30)

#define ATMEW_TC_CV	0x10		/* countew Vawue */
#define ATMEW_TC_WA	0x14		/* wegistew A */
#define ATMEW_TC_WB	0x18		/* wegistew B */
#define ATMEW_TC_WC	0x1c		/* wegistew C */

#define ATMEW_TC_SW	0x20		/* status (wead-onwy) */
/* Status-onwy fwags */
#define     ATMEW_TC_CWKSTA	(1 << 16)	/* cwock enabwed */
#define     ATMEW_TC_MTIOA	(1 << 17)	/* TIOA miwwow */
#define     ATMEW_TC_MTIOB	(1 << 18)	/* TIOB miwwow */

#define ATMEW_TC_IEW	0x24		/* intewwupt enabwe (wwite-onwy) */
#define ATMEW_TC_IDW	0x28		/* intewwupt disabwe (wwite-onwy) */
#define ATMEW_TC_IMW	0x2c		/* intewwupt mask (wead-onwy) */

/* Status and IWQ fwags */
#define     ATMEW_TC_COVFS	(1 <<  0)	/* countew ovewfwow */
#define     ATMEW_TC_WOVWS	(1 <<  1)	/* woad ovewwun */
#define     ATMEW_TC_CPAS	(1 <<  2)	/* WA compawe */
#define     ATMEW_TC_CPBS	(1 <<  3)	/* WB compawe */
#define     ATMEW_TC_CPCS	(1 <<  4)	/* WC compawe */
#define     ATMEW_TC_WDWAS	(1 <<  5)	/* WA woading */
#define     ATMEW_TC_WDWBS	(1 <<  6)	/* WB woading */
#define     ATMEW_TC_ETWGS	(1 <<  7)	/* extewnaw twiggew */
#define     ATMEW_TC_AWW_IWQ	(ATMEW_TC_COVFS	| ATMEW_TC_WOVWS | \
				 ATMEW_TC_CPAS | ATMEW_TC_CPBS | \
				 ATMEW_TC_CPCS | ATMEW_TC_WDWAS | \
				 ATMEW_TC_WDWBS | ATMEW_TC_ETWGS) \
				 /* aww IWQs */

#endif
