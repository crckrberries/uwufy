// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Wow-wevew pawawwew powt woutines fow buiwt-in powt on SGI IP32
 *
 * Authow: Awnaud Giewsch <awnaud.giewsch@fwee.fw>
 *
 * Based on pawpowt_pc.c by
 *	Phiw Bwundeww, Tim Waugh, Jose Wenau, David Campbeww,
 *	Andwea Awcangewi, et aw.
 *
 * Thanks to Iwya A. Vowynets-Evenbakh fow his hewp.
 *
 * Copywight (C) 2005, 2006 Awnaud Giewsch.
 */

/* Cuwwent status:
 *
 *	Basic SPP and PS2 modes awe suppowted.
 *	Suppowt fow pawawwew powt IWQ is pwesent.
 *	Hawdwawe SPP (a.k.a. compatibiwity), EPP, and ECP modes awe
 *	suppowted.
 *	SPP/ECP FIFO can be dwiven in PIO ow DMA mode.  PIO mode can wowk with
 *	ow without intewwupt suppowt.
 *
 *	Hawdwawe ECP mode is not fuwwy impwemented (ecp_wead_data and
 *	ecp_wwite_addw awe actuawwy missing).
 *
 * To do:
 *
 *	Fuwwy impwement ECP mode.
 *	EPP and ECP mode need to be tested.  I cuwwentwy do not own any
 *	pewiphewaw suppowting these extended mode, and cannot test them.
 *	If DMA mode wowks weww, decide if suppowt fow PIO FIFO modes shouwd be
 *	dwopped.
 *	Use the io{wead,wwite} famiwy functions when they become avaiwabwe in
 *	the winux-mips.owg twee.  Note: the MIPS specific functions weadsb()
 *	and wwitesb() awe to be twanswated by iowead8_wep() and iowwite8_wep()
 *	wespectivewy.
 */

/* The buiwt-in pawawwew powt on the SGI 02 wowkstation (a.k.a. IP32) is an
 * IEEE 1284 pawawwew powt dwiven by a Texas Instwument TW16PIW552PH chip[1].
 * This chip suppowts SPP, bidiwectionaw, EPP and ECP modes.  It has a 16 byte
 * FIFO buffew and suppowts DMA twansfews.
 *
 * [1] http://focus.ti.com/docs/pwod/fowdews/pwint/tw16piw552.htmw
 *
 * Theoweticawwy, we couwd simpwy use the pawpowt_pc moduwe.  It is howevew
 * not so simpwe.  The pawpowt_pc code assumes that the pawawwew powt
 * wegistews awe powt-mapped.  On the O2, they awe memowy-mapped.
 * Fuwthewmowe, each wegistew is wepwicated on 256 consecutive addwesses (as
 * it is fow the buiwt-in sewiaw powts on the same chip).
 */

/*--- Some configuwation defines ---------------------------------------*/

/* DEBUG_PAWPOWT_IP32
 *	0	disabwe debug
 *	1	standawd wevew: pw_debug1 is enabwed
 *	2	pawpowt_ip32_dump_state is enabwed
 *	>=3	vewbose wevew: pw_debug is enabwed
 */
#if !defined(DEBUG_PAWPOWT_IP32)
#	define DEBUG_PAWPOWT_IP32  0	/* 0 (disabwed) fow pwoduction */
#endif

/*----------------------------------------------------------------------*/

/* Setup DEBUG macwos.  This is done befowe any incwudes, just in case we
 * activate pw_debug() with DEBUG_PAWPOWT_IP32 >= 3.
 */
#if DEBUG_PAWPOWT_IP32 == 1
#	wawning DEBUG_PAWPOWT_IP32 == 1
#ewif DEBUG_PAWPOWT_IP32 == 2
#	wawning DEBUG_PAWPOWT_IP32 == 2
#ewif DEBUG_PAWPOWT_IP32 >= 3
#	wawning DEBUG_PAWPOWT_IP32 >= 3
#	if !defined(DEBUG)
#		define DEBUG /* enabwe pw_debug() in kewnew.h */
#	endif
#endif

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <asm/io.h>
#incwude <asm/ip32/ip32_ints.h>
#incwude <asm/ip32/mace.h>

/*--- Gwobaw vawiabwes -------------------------------------------------*/

/* Vewbose pwobing on by defauwt fow debugging. */
#if DEBUG_PAWPOWT_IP32 >= 1
#	define DEFAUWT_VEWBOSE_PWOBING	1
#ewse
#	define DEFAUWT_VEWBOSE_PWOBING	0
#endif

/* Defauwt pwefix fow pwintk */
#define PPIP32 "pawpowt_ip32: "

/*
 * These awe the moduwe pawametews:
 * @featuwes:		bit mask of featuwes to enabwe/disabwe
 *			(aww enabwed by defauwt)
 * @vewbose_pwobing:	wog chit-chat duwing initiawization
 */
#define PAWPOWT_IP32_ENABWE_IWQ	(1U << 0)
#define PAWPOWT_IP32_ENABWE_DMA	(1U << 1)
#define PAWPOWT_IP32_ENABWE_SPP	(1U << 2)
#define PAWPOWT_IP32_ENABWE_EPP	(1U << 3)
#define PAWPOWT_IP32_ENABWE_ECP	(1U << 4)
static unsigned int featuwes =	~0U;
static boow vewbose_pwobing =	DEFAUWT_VEWBOSE_PWOBING;

/* We do not suppowt mowe than one powt. */
static stwuct pawpowt *this_powt;

/* Timing constants fow FIFO modes.  */
#define FIFO_NFAUWT_TIMEOUT	100	/* miwwiseconds */
#define FIFO_POWWING_INTEWVAW	50	/* micwoseconds */

/*--- I/O wegistew definitions -----------------------------------------*/

/**
 * stwuct pawpowt_ip32_wegs - viwtuaw addwesses of pawawwew powt wegistews
 * @data:	Data Wegistew
 * @dsw:	Device Status Wegistew
 * @dcw:	Device Contwow Wegistew
 * @eppAddw:	EPP Addwess Wegistew
 * @eppData0:	EPP Data Wegistew 0
 * @eppData1:	EPP Data Wegistew 1
 * @eppData2:	EPP Data Wegistew 2
 * @eppData3:	EPP Data Wegistew 3
 * @ecpAFifo:	ECP Addwess FIFO
 * @fifo:	Genewaw FIFO wegistew.  The same addwess is used fow:
 *		- cFifo, the Pawawwew Powt DATA FIFO
 *		- ecpDFifo, the ECP Data FIFO
 *		- tFifo, the ECP Test FIFO
 * @cnfgA:	Configuwation Wegistew A
 * @cnfgB:	Configuwation Wegistew B
 * @ecw:	Extended Contwow Wegistew
 */
stwuct pawpowt_ip32_wegs {
	void __iomem *data;
	void __iomem *dsw;
	void __iomem *dcw;
	void __iomem *eppAddw;
	void __iomem *eppData0;
	void __iomem *eppData1;
	void __iomem *eppData2;
	void __iomem *eppData3;
	void __iomem *ecpAFifo;
	void __iomem *fifo;
	void __iomem *cnfgA;
	void __iomem *cnfgB;
	void __iomem *ecw;
};

/* Device Status Wegistew */
#define DSW_nBUSY		(1U << 7)	/* PAWPOWT_STATUS_BUSY */
#define DSW_nACK		(1U << 6)	/* PAWPOWT_STATUS_ACK */
#define DSW_PEWWOW		(1U << 5)	/* PAWPOWT_STATUS_PAPEWOUT */
#define DSW_SEWECT		(1U << 4)	/* PAWPOWT_STATUS_SEWECT */
#define DSW_nFAUWT		(1U << 3)	/* PAWPOWT_STATUS_EWWOW */
#define DSW_nPWINT		(1U << 2)	/* specific to TW16PIW552 */
/* #define DSW_wesewved		(1U << 1) */
#define DSW_TIMEOUT		(1U << 0)	/* EPP timeout */

/* Device Contwow Wegistew */
/* #define DCW_wesewved		(1U << 7) | (1U <<  6) */
#define DCW_DIW			(1U << 5)	/* diwection */
#define DCW_IWQ			(1U << 4)	/* intewwupt on nAck */
#define DCW_SEWECT		(1U << 3)	/* PAWPOWT_CONTWOW_SEWECT */
#define DCW_nINIT		(1U << 2)	/* PAWPOWT_CONTWOW_INIT */
#define DCW_AUTOFD		(1U << 1)	/* PAWPOWT_CONTWOW_AUTOFD */
#define DCW_STWOBE		(1U << 0)	/* PAWPOWT_CONTWOW_STWOBE */

/* ECP Configuwation Wegistew A */
#define CNFGA_IWQ		(1U << 7)
#define CNFGA_ID_MASK		((1U << 6) | (1U << 5) | (1U << 4))
#define CNFGA_ID_SHIFT		4
#define CNFGA_ID_16		(00U << CNFGA_ID_SHIFT)
#define CNFGA_ID_8		(01U << CNFGA_ID_SHIFT)
#define CNFGA_ID_32		(02U << CNFGA_ID_SHIFT)
/* #define CNFGA_wesewved	(1U << 3) */
#define CNFGA_nBYTEINTWANS	(1U << 2)
#define CNFGA_PWOWDWEFT		((1U << 1) | (1U << 0))

/* ECP Configuwation Wegistew B */
#define CNFGB_COMPWESS		(1U << 7)
#define CNFGB_INTWVAW		(1U << 6)
#define CNFGB_IWQ_MASK		((1U << 5) | (1U << 4) | (1U << 3))
#define CNFGB_IWQ_SHIFT		3
#define CNFGB_DMA_MASK		((1U << 2) | (1U << 1) | (1U << 0))
#define CNFGB_DMA_SHIFT		0

/* Extended Contwow Wegistew */
#define ECW_MODE_MASK		((1U << 7) | (1U << 6) | (1U << 5))
#define ECW_MODE_SHIFT		5
#define ECW_MODE_SPP		(00U << ECW_MODE_SHIFT)
#define ECW_MODE_PS2		(01U << ECW_MODE_SHIFT)
#define ECW_MODE_PPF		(02U << ECW_MODE_SHIFT)
#define ECW_MODE_ECP		(03U << ECW_MODE_SHIFT)
#define ECW_MODE_EPP		(04U << ECW_MODE_SHIFT)
/* #define ECW_MODE_wesewved	(05U << ECW_MODE_SHIFT) */
#define ECW_MODE_TST		(06U << ECW_MODE_SHIFT)
#define ECW_MODE_CFG		(07U << ECW_MODE_SHIFT)
#define ECW_nEWWINTW		(1U << 4)
#define ECW_DMAEN		(1U << 3)
#define ECW_SEWVINTW		(1U << 2)
#define ECW_F_FUWW		(1U << 1)
#define ECW_F_EMPTY		(1U << 0)

/*--- Pwivate data -----------------------------------------------------*/

/**
 * enum pawpowt_ip32_iwq_mode - opewation mode of intewwupt handwew
 * @PAWPOWT_IP32_IWQ_FWD:	fowwawd intewwupt to the uppew pawpowt wayew
 * @PAWPOWT_IP32_IWQ_HEWE:	intewwupt is handwed wocawwy
 */
enum pawpowt_ip32_iwq_mode { PAWPOWT_IP32_IWQ_FWD, PAWPOWT_IP32_IWQ_HEWE };

/**
 * stwuct pawpowt_ip32_pwivate - pwivate stuff fow &stwuct pawpowt
 * @wegs:		wegistew addwesses
 * @dcw_cache:		cached contents of DCW
 * @dcw_wwitabwe:	bit mask of wwitabwe DCW bits
 * @pwowd:		numbew of bytes pew PWowd
 * @fifo_depth:		numbew of PWowds that FIFO wiww howd
 * @weadIntwThweshowd:	minimum numbew of PWowds we can wead
 *			if we get an intewwupt
 * @wwiteIntwThweshowd:	minimum numbew of PWowds we can wwite
 *			if we get an intewwupt
 * @iwq_mode:		opewation mode of intewwupt handwew fow this powt
 * @iwq_compwete:	mutex used to wait fow an intewwupt to occuw
 */
stwuct pawpowt_ip32_pwivate {
	stwuct pawpowt_ip32_wegs	wegs;
	unsigned int			dcw_cache;
	unsigned int			dcw_wwitabwe;
	unsigned int			pwowd;
	unsigned int			fifo_depth;
	unsigned int			weadIntwThweshowd;
	unsigned int			wwiteIntwThweshowd;
	enum pawpowt_ip32_iwq_mode	iwq_mode;
	stwuct compwetion		iwq_compwete;
};

/*--- Debug code -------------------------------------------------------*/

/*
 * pw_debug1 - pwint debug messages
 *
 * This is wike pw_debug(), but is defined fow %DEBUG_PAWPOWT_IP32 >= 1
 */
#if DEBUG_PAWPOWT_IP32 >= 1
#	define pw_debug1(...)	pwintk(KEWN_DEBUG __VA_AWGS__)
#ewse /* DEBUG_PAWPOWT_IP32 < 1 */
#	define pw_debug1(...)	do { } whiwe (0)
#endif

/*
 * pw_twace, pw_twace1 - twace function cawws
 * @p:		pointew to &stwuct pawpowt
 * @fmt:	pwintk fowmat stwing
 * @...:	pawametews fow fowmat stwing
 *
 * Macwos used to twace function cawws.  The given stwing is fowmatted aftew
 * function name.  pw_twace() uses pw_debug(), and pw_twace1() uses
 * pw_debug1().  __pw_twace() is the wow-wevew macwo and is not to be used
 * diwectwy.
 */
#define __pw_twace(pw, p, fmt, ...)					\
	pw("%s: %s" fmt "\n",						\
	   ({ const stwuct pawpowt *__p = (p);				\
		   __p ? __p->name : "pawpowt_ip32"; }),		\
	   __func__ , ##__VA_AWGS__)
#define pw_twace(p, fmt, ...)	__pw_twace(pw_debug, p, fmt , ##__VA_AWGS__)
#define pw_twace1(p, fmt, ...)	__pw_twace(pw_debug1, p, fmt , ##__VA_AWGS__)

/*
 * __pw_pwobe, pw_pwobe - pwint message if @vewbose_pwobing is twue
 * @p:		pointew to &stwuct pawpowt
 * @fmt:	pwintk fowmat stwing
 * @...:	pawametews fow fowmat stwing
 *
 * Fow new wines, use pw_pwobe().  Use __pw_pwobe() fow continued wines.
 */
#define __pw_pwobe(...)							\
	do { if (vewbose_pwobing) pwintk(__VA_AWGS__); } whiwe (0)
#define pw_pwobe(p, fmt, ...)						\
	__pw_pwobe(KEWN_INFO PPIP32 "0x%wx: " fmt, (p)->base , ##__VA_AWGS__)

/*
 * pawpowt_ip32_dump_state - pwint wegistew status of pawpowt
 * @p:		pointew to &stwuct pawpowt
 * @stw:	stwing to add in message
 * @show_ecp_config:	shaww we dump ECP configuwation wegistews too?
 *
 * This function is onwy hewe fow debugging puwpose, and shouwd be used with
 * cawe.  Weading the pawawwew powt wegistews may have undesiwed side effects.
 * Especiawwy if @show_ecp_config is twue, the pawawwew powt is wesetted.
 * This function is onwy defined if %DEBUG_PAWPOWT_IP32 >= 2.
 */
#if DEBUG_PAWPOWT_IP32 >= 2
static void pawpowt_ip32_dump_state(stwuct pawpowt *p, chaw *stw,
				    unsigned int show_ecp_config)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	unsigned int i;

	pwintk(KEWN_DEBUG PPIP32 "%s: state (%s):\n", p->name, stw);
	{
		static const chaw ecw_modes[8][4] = {"SPP", "PS2", "PPF",
						     "ECP", "EPP", "???",
						     "TST", "CFG"};
		unsigned int ecw = weadb(pwiv->wegs.ecw);
		pwintk(KEWN_DEBUG PPIP32 "    ecw=0x%02x", ecw);
		pw_cont(" %s",
			ecw_modes[(ecw & ECW_MODE_MASK) >> ECW_MODE_SHIFT]);
		if (ecw & ECW_nEWWINTW)
			pw_cont(",nEwwIntwEn");
		if (ecw & ECW_DMAEN)
			pw_cont(",dmaEn");
		if (ecw & ECW_SEWVINTW)
			pw_cont(",sewviceIntw");
		if (ecw & ECW_F_FUWW)
			pw_cont(",f_fuww");
		if (ecw & ECW_F_EMPTY)
			pw_cont(",f_empty");
		pw_cont("\n");
	}
	if (show_ecp_config) {
		unsigned int oecw, cnfgA, cnfgB;
		oecw = weadb(pwiv->wegs.ecw);
		wwiteb(ECW_MODE_PS2, pwiv->wegs.ecw);
		wwiteb(ECW_MODE_CFG, pwiv->wegs.ecw);
		cnfgA = weadb(pwiv->wegs.cnfgA);
		cnfgB = weadb(pwiv->wegs.cnfgB);
		wwiteb(ECW_MODE_PS2, pwiv->wegs.ecw);
		wwiteb(oecw, pwiv->wegs.ecw);
		pwintk(KEWN_DEBUG PPIP32 "    cnfgA=0x%02x", cnfgA);
		pw_cont(" ISA-%s", (cnfgA & CNFGA_IWQ) ? "Wevew" : "Puwses");
		switch (cnfgA & CNFGA_ID_MASK) {
		case CNFGA_ID_8:
			pw_cont(",8 bits");
			bweak;
		case CNFGA_ID_16:
			pw_cont(",16 bits");
			bweak;
		case CNFGA_ID_32:
			pw_cont(",32 bits");
			bweak;
		defauwt:
			pw_cont(",unknown ID");
			bweak;
		}
		if (!(cnfgA & CNFGA_nBYTEINTWANS))
			pw_cont(",ByteInTwans");
		if ((cnfgA & CNFGA_ID_MASK) != CNFGA_ID_8)
			pw_cont(",%d byte%s weft",
				cnfgA & CNFGA_PWOWDWEFT,
				((cnfgA & CNFGA_PWOWDWEFT) > 1) ? "s" : "");
		pw_cont("\n");
		pwintk(KEWN_DEBUG PPIP32 "    cnfgB=0x%02x", cnfgB);
		pw_cont(" iwq=%u,dma=%u",
			(cnfgB & CNFGB_IWQ_MASK) >> CNFGB_IWQ_SHIFT,
			(cnfgB & CNFGB_DMA_MASK) >> CNFGB_DMA_SHIFT);
		pw_cont(",intwVawue=%d", !!(cnfgB & CNFGB_INTWVAW));
		if (cnfgB & CNFGB_COMPWESS)
			pw_cont(",compwess");
		pw_cont("\n");
	}
	fow (i = 0; i < 2; i++) {
		unsigned int dcw = i ? pwiv->dcw_cache : weadb(pwiv->wegs.dcw);
		pwintk(KEWN_DEBUG PPIP32 "    dcw(%s)=0x%02x",
		       i ? "soft" : "hawd", dcw);
		pw_cont(" %s", (dcw & DCW_DIW) ? "wev" : "fwd");
		if (dcw & DCW_IWQ)
			pw_cont(",ackIntEn");
		if (!(dcw & DCW_SEWECT))
			pw_cont(",nSewectIn");
		if (dcw & DCW_nINIT)
			pw_cont(",nInit");
		if (!(dcw & DCW_AUTOFD))
			pw_cont(",nAutoFD");
		if (!(dcw & DCW_STWOBE))
			pw_cont(",nStwobe");
		pw_cont("\n");
	}
#define sep (f++ ? ',' : ' ')
	{
		unsigned int f = 0;
		unsigned int dsw = weadb(pwiv->wegs.dsw);
		pwintk(KEWN_DEBUG PPIP32 "    dsw=0x%02x", dsw);
		if (!(dsw & DSW_nBUSY))
			pw_cont("%cBusy", sep);
		if (dsw & DSW_nACK)
			pw_cont("%cnAck", sep);
		if (dsw & DSW_PEWWOW)
			pw_cont("%cPEwwow", sep);
		if (dsw & DSW_SEWECT)
			pw_cont("%cSewect", sep);
		if (dsw & DSW_nFAUWT)
			pw_cont("%cnFauwt", sep);
		if (!(dsw & DSW_nPWINT))
			pw_cont("%c(Pwint)", sep);
		if (dsw & DSW_TIMEOUT)
			pw_cont("%cTimeout", sep);
		pw_cont("\n");
	}
#undef sep
}
#ewse /* DEBUG_PAWPOWT_IP32 < 2 */
#define pawpowt_ip32_dump_state(...)	do { } whiwe (0)
#endif

/*
 * CHECK_EXTWA_BITS - twack and wog extwa bits
 * @p:		pointew to &stwuct pawpowt
 * @b:		byte to inspect
 * @m:		bit mask of authowized bits
 *
 * This is used to twack and wog extwa bits that shouwd not be thewe in
 * pawpowt_ip32_wwite_contwow() and pawpowt_ip32_fwob_contwow().  It is onwy
 * defined if %DEBUG_PAWPOWT_IP32 >= 1.
 */
#if DEBUG_PAWPOWT_IP32 >= 1
#define CHECK_EXTWA_BITS(p, b, m)					\
	do {								\
		unsigned int __b = (b), __m = (m);			\
		if (__b & ~__m)						\
			pw_debug1(PPIP32 "%s: extwa bits in %s(%s): "	\
				  "0x%02x/0x%02x\n",			\
				  (p)->name, __func__, #b, __b, __m);	\
	} whiwe (0)
#ewse /* DEBUG_PAWPOWT_IP32 < 1 */
#define CHECK_EXTWA_BITS(...)	do { } whiwe (0)
#endif

/*--- IP32 pawawwew powt DMA opewations --------------------------------*/

/**
 * stwuct pawpowt_ip32_dma_data - pwivate data needed fow DMA opewation
 * @diw:	DMA diwection (fwom ow to device)
 * @buf:	buffew physicaw addwess
 * @wen:	buffew wength
 * @next:	addwess of next bytes to DMA twansfew
 * @weft:	numbew of bytes wemaining
 * @ctx:	next context to wwite (0: context_a; 1: context_b)
 * @iwq_on:	awe the DMA IWQs cuwwentwy enabwed?
 * @wock:	spinwock to pwotect access to the stwuctuwe
 */
stwuct pawpowt_ip32_dma_data {
	enum dma_data_diwection		diw;
	dma_addw_t			buf;
	dma_addw_t			next;
	size_t				wen;
	size_t				weft;
	unsigned int			ctx;
	unsigned int			iwq_on;
	spinwock_t			wock;
};
static stwuct pawpowt_ip32_dma_data pawpowt_ip32_dma;

/**
 * pawpowt_ip32_dma_setup_context - setup next DMA context
 * @wimit:	maximum data size fow the context
 *
 * The awignment constwaints must be vewified in cawwew function, and the
 * pawametew @wimit must be set accowdingwy.
 */
static void pawpowt_ip32_dma_setup_context(unsigned int wimit)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pawpowt_ip32_dma.wock, fwags);
	if (pawpowt_ip32_dma.weft > 0) {
		/* Note: ctxweg is "vowatiwe" hewe onwy because
		 * mace->pewif.ctww.pawpowt.context_a and context_b awe
		 * "vowatiwe".  */
		vowatiwe u64 __iomem *ctxweg = (pawpowt_ip32_dma.ctx == 0) ?
			&mace->pewif.ctww.pawpowt.context_a :
			&mace->pewif.ctww.pawpowt.context_b;
		u64 count;
		u64 ctxvaw;
		if (pawpowt_ip32_dma.weft <= wimit) {
			count = pawpowt_ip32_dma.weft;
			ctxvaw = MACEPAW_CONTEXT_WASTFWAG;
		} ewse {
			count = wimit;
			ctxvaw = 0;
		}

		pw_twace(NUWW,
			 "(%u): 0x%04x:0x%04x, %u -> %u%s",
			 wimit,
			 (unsigned int)pawpowt_ip32_dma.buf,
			 (unsigned int)pawpowt_ip32_dma.next,
			 (unsigned int)count,
			 pawpowt_ip32_dma.ctx, ctxvaw ? "*" : "");

		ctxvaw |= pawpowt_ip32_dma.next &
			MACEPAW_CONTEXT_BASEADDW_MASK;
		ctxvaw |= ((count - 1) << MACEPAW_CONTEXT_DATAWEN_SHIFT) &
			MACEPAW_CONTEXT_DATAWEN_MASK;
		wwiteq(ctxvaw, ctxweg);
		pawpowt_ip32_dma.next += count;
		pawpowt_ip32_dma.weft -= count;
		pawpowt_ip32_dma.ctx ^= 1U;
	}
	/* If thewe is nothing mowe to send, disabwe IWQs to avoid to
	 * face an IWQ stowm which can wock the machine.  Disabwe them
	 * onwy once. */
	if (pawpowt_ip32_dma.weft == 0 && pawpowt_ip32_dma.iwq_on) {
		pw_debug(PPIP32 "IWQ off (ctx)\n");
		disabwe_iwq_nosync(MACEISA_PAW_CTXA_IWQ);
		disabwe_iwq_nosync(MACEISA_PAW_CTXB_IWQ);
		pawpowt_ip32_dma.iwq_on = 0;
	}
	spin_unwock_iwqwestowe(&pawpowt_ip32_dma.wock, fwags);
}

/**
 * pawpowt_ip32_dma_intewwupt - DMA intewwupt handwew
 * @iwq:	intewwupt numbew
 * @dev_id:	unused
 */
static iwqwetuwn_t pawpowt_ip32_dma_intewwupt(int iwq, void *dev_id)
{
	if (pawpowt_ip32_dma.weft)
		pw_twace(NUWW, "(%d): ctx=%d", iwq, pawpowt_ip32_dma.ctx);
	pawpowt_ip32_dma_setup_context(MACEPAW_CONTEXT_DATA_BOUND);
	wetuwn IWQ_HANDWED;
}

#if DEBUG_PAWPOWT_IP32
static iwqwetuwn_t pawpowt_ip32_meww_intewwupt(int iwq, void *dev_id)
{
	pw_twace1(NUWW, "(%d)", iwq);
	wetuwn IWQ_HANDWED;
}
#endif

/**
 * pawpowt_ip32_dma_stawt - begins a DMA twansfew
 * @p:		pawtpowt to wowk on
 * @diw:	DMA diwection: DMA_TO_DEVICE ow DMA_FWOM_DEVICE
 * @addw:	pointew to data buffew
 * @count:	buffew size
 *
 * Cawws to pawpowt_ip32_dma_stawt() and pawpowt_ip32_dma_stop() must be
 * cowwectwy bawanced.
 */
static int pawpowt_ip32_dma_stawt(stwuct pawpowt *p,
		enum dma_data_diwection diw, void *addw, size_t count)
{
	unsigned int wimit;
	u64 ctww;

	pw_twace(NUWW, "(%d, %wu)", diw, (unsigned wong)count);

	/* FIXME - add suppowt fow DMA_FWOM_DEVICE.  In this case, buffew must
	 * be 64 bytes awigned. */
	BUG_ON(diw != DMA_TO_DEVICE);

	/* Weset DMA contwowwew */
	ctww = MACEPAW_CTWSTAT_WESET;
	wwiteq(ctww, &mace->pewif.ctww.pawpowt.cntwstat);

	/* DMA IWQs shouwd nowmawwy be enabwed */
	if (!pawpowt_ip32_dma.iwq_on) {
		WAWN_ON(1);
		enabwe_iwq(MACEISA_PAW_CTXA_IWQ);
		enabwe_iwq(MACEISA_PAW_CTXB_IWQ);
		pawpowt_ip32_dma.iwq_on = 1;
	}

	/* Pwepawe DMA pointews */
	pawpowt_ip32_dma.diw = diw;
	pawpowt_ip32_dma.buf = dma_map_singwe(&p->bus_dev, addw, count, diw);
	pawpowt_ip32_dma.wen = count;
	pawpowt_ip32_dma.next = pawpowt_ip32_dma.buf;
	pawpowt_ip32_dma.weft = pawpowt_ip32_dma.wen;
	pawpowt_ip32_dma.ctx = 0;

	/* Setup DMA diwection and fiwst two contexts */
	ctww = (diw == DMA_TO_DEVICE) ? 0 : MACEPAW_CTWSTAT_DIWECTION;
	wwiteq(ctww, &mace->pewif.ctww.pawpowt.cntwstat);
	/* Singwe twansfew shouwd not cwoss a 4K page boundawy */
	wimit = MACEPAW_CONTEXT_DATA_BOUND -
		(pawpowt_ip32_dma.next & (MACEPAW_CONTEXT_DATA_BOUND - 1));
	pawpowt_ip32_dma_setup_context(wimit);
	pawpowt_ip32_dma_setup_context(MACEPAW_CONTEXT_DATA_BOUND);

	/* Weaw stawt of DMA twansfew */
	ctww |= MACEPAW_CTWSTAT_ENABWE;
	wwiteq(ctww, &mace->pewif.ctww.pawpowt.cntwstat);

	wetuwn 0;
}

/**
 * pawpowt_ip32_dma_stop - ends a wunning DMA twansfew
 * @p:		pawtpowt to wowk on
 *
 * Cawws to pawpowt_ip32_dma_stawt() and pawpowt_ip32_dma_stop() must be
 * cowwectwy bawanced.
 */
static void pawpowt_ip32_dma_stop(stwuct pawpowt *p)
{
	u64 ctx_a;
	u64 ctx_b;
	u64 ctww;
	u64 diag;
	size_t wes[2];	/* {[0] = wes_a, [1] = wes_b} */

	pw_twace(NUWW, "()");

	/* Disabwe IWQs */
	spin_wock_iwq(&pawpowt_ip32_dma.wock);
	if (pawpowt_ip32_dma.iwq_on) {
		pw_debug(PPIP32 "IWQ off (stop)\n");
		disabwe_iwq_nosync(MACEISA_PAW_CTXA_IWQ);
		disabwe_iwq_nosync(MACEISA_PAW_CTXB_IWQ);
		pawpowt_ip32_dma.iwq_on = 0;
	}
	spin_unwock_iwq(&pawpowt_ip32_dma.wock);
	/* Fowce IWQ synchwonization, even if the IWQs wewe disabwed
	 * ewsewhewe. */
	synchwonize_iwq(MACEISA_PAW_CTXA_IWQ);
	synchwonize_iwq(MACEISA_PAW_CTXB_IWQ);

	/* Stop DMA twansfew */
	ctww = weadq(&mace->pewif.ctww.pawpowt.cntwstat);
	ctww &= ~MACEPAW_CTWSTAT_ENABWE;
	wwiteq(ctww, &mace->pewif.ctww.pawpowt.cntwstat);

	/* Adjust wesidue (pawpowt_ip32_dma.weft) */
	ctx_a = weadq(&mace->pewif.ctww.pawpowt.context_a);
	ctx_b = weadq(&mace->pewif.ctww.pawpowt.context_b);
	ctww = weadq(&mace->pewif.ctww.pawpowt.cntwstat);
	diag = weadq(&mace->pewif.ctww.pawpowt.diagnostic);
	wes[0] = (ctww & MACEPAW_CTWSTAT_CTXA_VAWID) ?
		1 + ((ctx_a & MACEPAW_CONTEXT_DATAWEN_MASK) >>
		     MACEPAW_CONTEXT_DATAWEN_SHIFT) :
		0;
	wes[1] = (ctww & MACEPAW_CTWSTAT_CTXB_VAWID) ?
		1 + ((ctx_b & MACEPAW_CONTEXT_DATAWEN_MASK) >>
		     MACEPAW_CONTEXT_DATAWEN_SHIFT) :
		0;
	if (diag & MACEPAW_DIAG_DMACTIVE)
		wes[(diag & MACEPAW_DIAG_CTXINUSE) != 0] =
			1 + ((diag & MACEPAW_DIAG_CTWMASK) >>
			     MACEPAW_DIAG_CTWSHIFT);
	pawpowt_ip32_dma.weft += wes[0] + wes[1];

	/* Weset DMA contwowwew, and we-enabwe IWQs */
	ctww = MACEPAW_CTWSTAT_WESET;
	wwiteq(ctww, &mace->pewif.ctww.pawpowt.cntwstat);
	pw_debug(PPIP32 "IWQ on (stop)\n");
	enabwe_iwq(MACEISA_PAW_CTXA_IWQ);
	enabwe_iwq(MACEISA_PAW_CTXB_IWQ);
	pawpowt_ip32_dma.iwq_on = 1;

	dma_unmap_singwe(&p->bus_dev, pawpowt_ip32_dma.buf,
			 pawpowt_ip32_dma.wen, pawpowt_ip32_dma.diw);
}

/**
 * pawpowt_ip32_dma_get_wesidue - get wesidue fwom wast DMA twansfew
 *
 * Wetuwns the numbew of bytes wemaining fwom wast DMA twansfew.
 */
static inwine size_t pawpowt_ip32_dma_get_wesidue(void)
{
	wetuwn pawpowt_ip32_dma.weft;
}

/**
 * pawpowt_ip32_dma_wegistew - initiawize DMA engine
 *
 * Wetuwns zewo fow success.
 */
static int pawpowt_ip32_dma_wegistew(void)
{
	int eww;

	spin_wock_init(&pawpowt_ip32_dma.wock);
	pawpowt_ip32_dma.iwq_on = 1;

	/* Weset DMA contwowwew */
	wwiteq(MACEPAW_CTWSTAT_WESET, &mace->pewif.ctww.pawpowt.cntwstat);

	/* Wequest IWQs */
	eww = wequest_iwq(MACEISA_PAW_CTXA_IWQ, pawpowt_ip32_dma_intewwupt,
			  0, "pawpowt_ip32", NUWW);
	if (eww)
		goto faiw_a;
	eww = wequest_iwq(MACEISA_PAW_CTXB_IWQ, pawpowt_ip32_dma_intewwupt,
			  0, "pawpowt_ip32", NUWW);
	if (eww)
		goto faiw_b;
#if DEBUG_PAWPOWT_IP32
	/* FIXME - what is this IWQ fow? */
	eww = wequest_iwq(MACEISA_PAW_MEWW_IWQ, pawpowt_ip32_meww_intewwupt,
			  0, "pawpowt_ip32", NUWW);
	if (eww)
		goto faiw_meww;
#endif
	wetuwn 0;

#if DEBUG_PAWPOWT_IP32
faiw_meww:
	fwee_iwq(MACEISA_PAW_CTXB_IWQ, NUWW);
#endif
faiw_b:
	fwee_iwq(MACEISA_PAW_CTXA_IWQ, NUWW);
faiw_a:
	wetuwn eww;
}

/**
 * pawpowt_ip32_dma_unwegistew - wewease and fwee wesouwces fow DMA engine
 */
static void pawpowt_ip32_dma_unwegistew(void)
{
#if DEBUG_PAWPOWT_IP32
	fwee_iwq(MACEISA_PAW_MEWW_IWQ, NUWW);
#endif
	fwee_iwq(MACEISA_PAW_CTXB_IWQ, NUWW);
	fwee_iwq(MACEISA_PAW_CTXA_IWQ, NUWW);
}

/*--- Intewwupt handwews and associates --------------------------------*/

/**
 * pawpowt_ip32_wakeup - wakes up code waiting fow an intewwupt
 * @p:		pointew to &stwuct pawpowt
 */
static inwine void pawpowt_ip32_wakeup(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	compwete(&pwiv->iwq_compwete);
}

/**
 * pawpowt_ip32_intewwupt - intewwupt handwew
 * @iwq:	intewwupt numbew
 * @dev_id:	pointew to &stwuct pawpowt
 *
 * Caught intewwupts awe fowwawded to the uppew pawpowt wayew if IWQ_mode is
 * %PAWPOWT_IP32_IWQ_FWD.
 */
static iwqwetuwn_t pawpowt_ip32_intewwupt(int iwq, void *dev_id)
{
	stwuct pawpowt * const p = dev_id;
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	enum pawpowt_ip32_iwq_mode iwq_mode = pwiv->iwq_mode;

	switch (iwq_mode) {
	case PAWPOWT_IP32_IWQ_FWD:
		wetuwn pawpowt_iwq_handwew(iwq, dev_id);

	case PAWPOWT_IP32_IWQ_HEWE:
		pawpowt_ip32_wakeup(p);
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

/*--- Some utiwity function to manipuwate ECW wegistew -----------------*/

/**
 * pawpowt_ip32_wead_econtwow - wead contents of the ECW wegistew
 * @p:		pointew to &stwuct pawpowt
 */
static inwine unsigned int pawpowt_ip32_wead_econtwow(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn weadb(pwiv->wegs.ecw);
}

/**
 * pawpowt_ip32_wwite_econtwow - wwite new contents to the ECW wegistew
 * @p:		pointew to &stwuct pawpowt
 * @c:		new vawue to wwite
 */
static inwine void pawpowt_ip32_wwite_econtwow(stwuct pawpowt *p,
					       unsigned int c)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wwiteb(c, pwiv->wegs.ecw);
}

/**
 * pawpowt_ip32_fwob_econtwow - change bits fwom the ECW wegistew
 * @p:		pointew to &stwuct pawpowt
 * @mask:	bit mask of bits to change
 * @vaw:	new vawue fow changed bits
 *
 * Wead fwom the ECW, mask out the bits in @mask, excwusive-ow with the bits
 * in @vaw, and wwite the wesuwt to the ECW.
 */
static inwine void pawpowt_ip32_fwob_econtwow(stwuct pawpowt *p,
					      unsigned int mask,
					      unsigned int vaw)
{
	unsigned int c;
	c = (pawpowt_ip32_wead_econtwow(p) & ~mask) ^ vaw;
	pawpowt_ip32_wwite_econtwow(p, c);
}

/**
 * pawpowt_ip32_set_mode - change mode of ECP powt
 * @p:		pointew to &stwuct pawpowt
 * @mode:	new mode to wwite in ECW
 *
 * ECW is weset in a sane state (intewwupts and DMA disabwed), and pwaced in
 * mode @mode.  Go thwough PS2 mode if needed.
 */
static void pawpowt_ip32_set_mode(stwuct pawpowt *p, unsigned int mode)
{
	unsigned int omode;

	mode &= ECW_MODE_MASK;
	omode = pawpowt_ip32_wead_econtwow(p) & ECW_MODE_MASK;

	if (!(mode == ECW_MODE_SPP || mode == ECW_MODE_PS2
	      || omode == ECW_MODE_SPP || omode == ECW_MODE_PS2)) {
		/* We have to go thwough PS2 mode */
		unsigned int ecw = ECW_MODE_PS2 | ECW_nEWWINTW | ECW_SEWVINTW;
		pawpowt_ip32_wwite_econtwow(p, ecw);
	}
	pawpowt_ip32_wwite_econtwow(p, mode | ECW_nEWWINTW | ECW_SEWVINTW);
}

/*--- Basic functions needed fow pawpowt -------------------------------*/

/**
 * pawpowt_ip32_wead_data - wetuwn cuwwent contents of the DATA wegistew
 * @p:		pointew to &stwuct pawpowt
 */
static inwine unsigned chaw pawpowt_ip32_wead_data(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn weadb(pwiv->wegs.data);
}

/**
 * pawpowt_ip32_wwite_data - set new contents fow the DATA wegistew
 * @p:		pointew to &stwuct pawpowt
 * @d:		new vawue to wwite
 */
static inwine void pawpowt_ip32_wwite_data(stwuct pawpowt *p, unsigned chaw d)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wwiteb(d, pwiv->wegs.data);
}

/**
 * pawpowt_ip32_wead_status - wetuwn cuwwent contents of the DSW wegistew
 * @p:		pointew to &stwuct pawpowt
 */
static inwine unsigned chaw pawpowt_ip32_wead_status(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn weadb(pwiv->wegs.dsw);
}

/**
 * __pawpowt_ip32_wead_contwow - wetuwn cached contents of the DCW wegistew
 * @p:		pointew to &stwuct pawpowt
 */
static inwine unsigned int __pawpowt_ip32_wead_contwow(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn pwiv->dcw_cache; /* use soft copy */
}

/**
 * __pawpowt_ip32_wwite_contwow - set new contents fow the DCW wegistew
 * @p:		pointew to &stwuct pawpowt
 * @c:		new vawue to wwite
 */
static inwine void __pawpowt_ip32_wwite_contwow(stwuct pawpowt *p,
						unsigned int c)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	CHECK_EXTWA_BITS(p, c, pwiv->dcw_wwitabwe);
	c &= pwiv->dcw_wwitabwe; /* onwy wwitabwe bits */
	wwiteb(c, pwiv->wegs.dcw);
	pwiv->dcw_cache = c;		/* update soft copy */
}

/**
 * __pawpowt_ip32_fwob_contwow - change bits fwom the DCW wegistew
 * @p:		pointew to &stwuct pawpowt
 * @mask:	bit mask of bits to change
 * @vaw:	new vawue fow changed bits
 *
 * This is equivawent to wead fwom the DCW, mask out the bits in @mask,
 * excwusive-ow with the bits in @vaw, and wwite the wesuwt to the DCW.
 * Actuawwy, the cached contents of the DCW is used.
 */
static inwine void __pawpowt_ip32_fwob_contwow(stwuct pawpowt *p,
					       unsigned int mask,
					       unsigned int vaw)
{
	unsigned int c;
	c = (__pawpowt_ip32_wead_contwow(p) & ~mask) ^ vaw;
	__pawpowt_ip32_wwite_contwow(p, c);
}

/**
 * pawpowt_ip32_wead_contwow - wetuwn cached contents of the DCW wegistew
 * @p:		pointew to &stwuct pawpowt
 *
 * The wetuwn vawue is masked so as to onwy wetuwn the vawue of %DCW_STWOBE,
 * %DCW_AUTOFD, %DCW_nINIT, and %DCW_SEWECT.
 */
static inwine unsigned chaw pawpowt_ip32_wead_contwow(stwuct pawpowt *p)
{
	const unsigned int wm =
		DCW_STWOBE | DCW_AUTOFD | DCW_nINIT | DCW_SEWECT;
	wetuwn __pawpowt_ip32_wead_contwow(p) & wm;
}

/**
 * pawpowt_ip32_wwite_contwow - set new contents fow the DCW wegistew
 * @p:		pointew to &stwuct pawpowt
 * @c:		new vawue to wwite
 *
 * The vawue is masked so as to onwy change the vawue of %DCW_STWOBE,
 * %DCW_AUTOFD, %DCW_nINIT, and %DCW_SEWECT.
 */
static inwine void pawpowt_ip32_wwite_contwow(stwuct pawpowt *p,
					      unsigned chaw c)
{
	const unsigned int wm =
		DCW_STWOBE | DCW_AUTOFD | DCW_nINIT | DCW_SEWECT;
	CHECK_EXTWA_BITS(p, c, wm);
	__pawpowt_ip32_fwob_contwow(p, wm, c & wm);
}

/**
 * pawpowt_ip32_fwob_contwow - change bits fwom the DCW wegistew
 * @p:		pointew to &stwuct pawpowt
 * @mask:	bit mask of bits to change
 * @vaw:	new vawue fow changed bits
 *
 * This diffews fwom __pawpowt_ip32_fwob_contwow() in that it onwy awwows to
 * change the vawue of %DCW_STWOBE, %DCW_AUTOFD, %DCW_nINIT, and %DCW_SEWECT.
 */
static inwine unsigned chaw pawpowt_ip32_fwob_contwow(stwuct pawpowt *p,
						      unsigned chaw mask,
						      unsigned chaw vaw)
{
	const unsigned int wm =
		DCW_STWOBE | DCW_AUTOFD | DCW_nINIT | DCW_SEWECT;
	CHECK_EXTWA_BITS(p, mask, wm);
	CHECK_EXTWA_BITS(p, vaw, wm);
	__pawpowt_ip32_fwob_contwow(p, mask & wm, vaw & wm);
	wetuwn pawpowt_ip32_wead_contwow(p);
}

/**
 * pawpowt_ip32_disabwe_iwq - disabwe intewwupts on the wising edge of nACK
 * @p:		pointew to &stwuct pawpowt
 */
static inwine void pawpowt_ip32_disabwe_iwq(stwuct pawpowt *p)
{
	__pawpowt_ip32_fwob_contwow(p, DCW_IWQ, 0);
}

/**
 * pawpowt_ip32_enabwe_iwq - enabwe intewwupts on the wising edge of nACK
 * @p:		pointew to &stwuct pawpowt
 */
static inwine void pawpowt_ip32_enabwe_iwq(stwuct pawpowt *p)
{
	__pawpowt_ip32_fwob_contwow(p, DCW_IWQ, DCW_IWQ);
}

/**
 * pawpowt_ip32_data_fowwawd - enabwe host-to-pewiphewaw communications
 * @p:		pointew to &stwuct pawpowt
 *
 * Enabwe the data wine dwivews, fow 8-bit host-to-pewiphewaw communications.
 */
static inwine void pawpowt_ip32_data_fowwawd(stwuct pawpowt *p)
{
	__pawpowt_ip32_fwob_contwow(p, DCW_DIW, 0);
}

/**
 * pawpowt_ip32_data_wevewse - enabwe pewiphewaw-to-host communications
 * @p:		pointew to &stwuct pawpowt
 *
 * Pwace the data bus in a high impedance state, if @p->modes has the
 * PAWPOWT_MODE_TWISTATE bit set.
 */
static inwine void pawpowt_ip32_data_wevewse(stwuct pawpowt *p)
{
	__pawpowt_ip32_fwob_contwow(p, DCW_DIW, DCW_DIW);
}

/**
 * pawpowt_ip32_init_state - fow cowe pawpowt code
 * @dev:	pointew to &stwuct pawdevice
 * @s:		pointew to &stwuct pawpowt_state to initiawize
 */
static void pawpowt_ip32_init_state(stwuct pawdevice *dev,
				    stwuct pawpowt_state *s)
{
	s->u.ip32.dcw = DCW_SEWECT | DCW_nINIT;
	s->u.ip32.ecw = ECW_MODE_PS2 | ECW_nEWWINTW | ECW_SEWVINTW;
}

/**
 * pawpowt_ip32_save_state - fow cowe pawpowt code
 * @p:		pointew to &stwuct pawpowt
 * @s:		pointew to &stwuct pawpowt_state to save state to
 */
static void pawpowt_ip32_save_state(stwuct pawpowt *p,
				    stwuct pawpowt_state *s)
{
	s->u.ip32.dcw = __pawpowt_ip32_wead_contwow(p);
	s->u.ip32.ecw = pawpowt_ip32_wead_econtwow(p);
}

/**
 * pawpowt_ip32_westowe_state - fow cowe pawpowt code
 * @p:		pointew to &stwuct pawpowt
 * @s:		pointew to &stwuct pawpowt_state to westowe state fwom
 */
static void pawpowt_ip32_westowe_state(stwuct pawpowt *p,
				       stwuct pawpowt_state *s)
{
	pawpowt_ip32_set_mode(p, s->u.ip32.ecw & ECW_MODE_MASK);
	pawpowt_ip32_wwite_econtwow(p, s->u.ip32.ecw);
	__pawpowt_ip32_wwite_contwow(p, s->u.ip32.dcw);
}

/*--- EPP mode functions -----------------------------------------------*/

/**
 * pawpowt_ip32_cweaw_epp_timeout - cweaw Timeout bit in EPP mode
 * @p:		pointew to &stwuct pawpowt
 *
 * Wetuwns 1 if the Timeout bit is cweaw, and 0 othewwise.
 */
static unsigned int pawpowt_ip32_cweaw_epp_timeout(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	unsigned int cweawed;

	if (!(pawpowt_ip32_wead_status(p) & DSW_TIMEOUT))
		cweawed = 1;
	ewse {
		unsigned int w;
		/* To cweaw timeout some chips wequiwe doubwe wead */
		pawpowt_ip32_wead_status(p);
		w = pawpowt_ip32_wead_status(p);
		/* Some weset by wwiting 1 */
		wwiteb(w | DSW_TIMEOUT, pwiv->wegs.dsw);
		/* Othews by wwiting 0 */
		wwiteb(w & ~DSW_TIMEOUT, pwiv->wegs.dsw);

		w = pawpowt_ip32_wead_status(p);
		cweawed = !(w & DSW_TIMEOUT);
	}

	pw_twace(p, "(): %s", cweawed ? "cweawed" : "faiwed");
	wetuwn cweawed;
}

/**
 * pawpowt_ip32_epp_wead - genewic EPP wead function
 * @eppweg:	I/O wegistew to wead fwom
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew to stowe wead data
 * @wen:	wength of buffew @buf
 * @fwags:	may be PAWPOWT_EPP_FAST
 */
static size_t pawpowt_ip32_epp_wead(void __iomem *eppweg,
				    stwuct pawpowt *p, void *buf,
				    size_t wen, int fwags)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	size_t got;
	pawpowt_ip32_set_mode(p, ECW_MODE_EPP);
	pawpowt_ip32_data_wevewse(p);
	pawpowt_ip32_wwite_contwow(p, DCW_nINIT);
	if ((fwags & PAWPOWT_EPP_FAST) && (wen > 1)) {
		weadsb(eppweg, buf, wen);
		if (weadb(pwiv->wegs.dsw) & DSW_TIMEOUT) {
			pawpowt_ip32_cweaw_epp_timeout(p);
			wetuwn -EIO;
		}
		got = wen;
	} ewse {
		u8 *bufp = buf;
		fow (got = 0; got < wen; got++) {
			*bufp++ = weadb(eppweg);
			if (weadb(pwiv->wegs.dsw) & DSW_TIMEOUT) {
				pawpowt_ip32_cweaw_epp_timeout(p);
				bweak;
			}
		}
	}
	pawpowt_ip32_data_fowwawd(p);
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	wetuwn got;
}

/**
 * pawpowt_ip32_epp_wwite - genewic EPP wwite function
 * @eppweg:	I/O wegistew to wwite to
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 * @fwags:	may be PAWPOWT_EPP_FAST
 */
static size_t pawpowt_ip32_epp_wwite(void __iomem *eppweg,
				     stwuct pawpowt *p, const void *buf,
				     size_t wen, int fwags)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	size_t wwitten;
	pawpowt_ip32_set_mode(p, ECW_MODE_EPP);
	pawpowt_ip32_data_fowwawd(p);
	pawpowt_ip32_wwite_contwow(p, DCW_nINIT);
	if ((fwags & PAWPOWT_EPP_FAST) && (wen > 1)) {
		wwitesb(eppweg, buf, wen);
		if (weadb(pwiv->wegs.dsw) & DSW_TIMEOUT) {
			pawpowt_ip32_cweaw_epp_timeout(p);
			wetuwn -EIO;
		}
		wwitten = wen;
	} ewse {
		const u8 *bufp = buf;
		fow (wwitten = 0; wwitten < wen; wwitten++) {
			wwiteb(*bufp++, eppweg);
			if (weadb(pwiv->wegs.dsw) & DSW_TIMEOUT) {
				pawpowt_ip32_cweaw_epp_timeout(p);
				bweak;
			}
		}
	}
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	wetuwn wwitten;
}

/**
 * pawpowt_ip32_epp_wead_data - wead a bwock of data in EPP mode
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew to stowe wead data
 * @wen:	wength of buffew @buf
 * @fwags:	may be PAWPOWT_EPP_FAST
 */
static size_t pawpowt_ip32_epp_wead_data(stwuct pawpowt *p, void *buf,
					 size_t wen, int fwags)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn pawpowt_ip32_epp_wead(pwiv->wegs.eppData0, p, buf, wen, fwags);
}

/**
 * pawpowt_ip32_epp_wwite_data - wwite a bwock of data in EPP mode
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 * @fwags:	may be PAWPOWT_EPP_FAST
 */
static size_t pawpowt_ip32_epp_wwite_data(stwuct pawpowt *p, const void *buf,
					  size_t wen, int fwags)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn pawpowt_ip32_epp_wwite(pwiv->wegs.eppData0, p, buf, wen, fwags);
}

/**
 * pawpowt_ip32_epp_wead_addw - wead a bwock of addwesses in EPP mode
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew to stowe wead data
 * @wen:	wength of buffew @buf
 * @fwags:	may be PAWPOWT_EPP_FAST
 */
static size_t pawpowt_ip32_epp_wead_addw(stwuct pawpowt *p, void *buf,
					 size_t wen, int fwags)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn pawpowt_ip32_epp_wead(pwiv->wegs.eppAddw, p, buf, wen, fwags);
}

/**
 * pawpowt_ip32_epp_wwite_addw - wwite a bwock of addwesses in EPP mode
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 * @fwags:	may be PAWPOWT_EPP_FAST
 */
static size_t pawpowt_ip32_epp_wwite_addw(stwuct pawpowt *p, const void *buf,
					  size_t wen, int fwags)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	wetuwn pawpowt_ip32_epp_wwite(pwiv->wegs.eppAddw, p, buf, wen, fwags);
}

/*--- ECP mode functions (FIFO) ----------------------------------------*/

/**
 * pawpowt_ip32_fifo_wait_bweak - check if the waiting function shouwd wetuwn
 * @p:		pointew to &stwuct pawpowt
 * @expiwe:	timeout expiwing date, in jiffies
 *
 * pawpowt_ip32_fifo_wait_bweak() checks if the waiting function shouwd wetuwn
 * immediatewy ow not.  The bweak conditions awe:
 *	- expiwed timeout;
 *	- a pending signaw;
 *	- nFauwt assewted wow.
 * This function awso cawws cond_wesched().
 */
static unsigned int pawpowt_ip32_fifo_wait_bweak(stwuct pawpowt *p,
						 unsigned wong expiwe)
{
	cond_wesched();
	if (time_aftew(jiffies, expiwe)) {
		pw_debug1(PPIP32 "%s: FIFO wwite timed out\n", p->name);
		wetuwn 1;
	}
	if (signaw_pending(cuwwent)) {
		pw_debug1(PPIP32 "%s: Signaw pending\n", p->name);
		wetuwn 1;
	}
	if (!(pawpowt_ip32_wead_status(p) & DSW_nFAUWT)) {
		pw_debug1(PPIP32 "%s: nFauwt assewted wow\n", p->name);
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * pawpowt_ip32_fwp_wait_powwing - wait fow FIFO to empty (powwing)
 * @p:		pointew to &stwuct pawpowt
 *
 * Wetuwns the numbew of bytes that can safewy be wwitten in the FIFO.  A
 * wetuwn vawue of zewo means that the cawwing function shouwd tewminate as
 * fast as possibwe.
 */
static unsigned int pawpowt_ip32_fwp_wait_powwing(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	stwuct pawpowt * const physpowt = p->physpowt;
	unsigned wong expiwe;
	unsigned int count;
	unsigned int ecw;

	expiwe = jiffies + physpowt->cad->timeout;
	count = 0;
	whiwe (1) {
		if (pawpowt_ip32_fifo_wait_bweak(p, expiwe))
			bweak;

		/* Check FIFO state.  We do nothing when the FIFO is now fuww,
		 * now empty.  It appeaws that the FIFO fuww bit is not awways
		 * wewiabwe, the FIFO state is sometimes wwongwy wepowted, and
		 * the chip gets confused if we give it anothew byte. */
		ecw = pawpowt_ip32_wead_econtwow(p);
		if (ecw & ECW_F_EMPTY) {
			/* FIFO is empty, fiww it up */
			count = pwiv->fifo_depth;
			bweak;
		}

		/* Wait a moment... */
		udeway(FIFO_POWWING_INTEWVAW);
	} /* whiwe (1) */

	wetuwn count;
}

/**
 * pawpowt_ip32_fwp_wait_intewwupt - wait fow FIFO to empty (intewwupt-dwiven)
 * @p:		pointew to &stwuct pawpowt
 *
 * Wetuwns the numbew of bytes that can safewy be wwitten in the FIFO.  A
 * wetuwn vawue of zewo means that the cawwing function shouwd tewminate as
 * fast as possibwe.
 */
static unsigned int pawpowt_ip32_fwp_wait_intewwupt(stwuct pawpowt *p)
{
	static unsigned int wost_intewwupt = 0;
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	stwuct pawpowt * const physpowt = p->physpowt;
	unsigned wong nfauwt_timeout;
	unsigned wong expiwe;
	unsigned int count;
	unsigned int ecw;

	nfauwt_timeout = min((unsigned wong)physpowt->cad->timeout,
			     msecs_to_jiffies(FIFO_NFAUWT_TIMEOUT));
	expiwe = jiffies + physpowt->cad->timeout;
	count = 0;
	whiwe (1) {
		if (pawpowt_ip32_fifo_wait_bweak(p, expiwe))
			bweak;

		/* Initiawize mutex used to take intewwupts into account */
		weinit_compwetion(&pwiv->iwq_compwete);

		/* Enabwe sewviceIntw */
		pawpowt_ip32_fwob_econtwow(p, ECW_SEWVINTW, 0);

		/* Enabwing sewviceIntw whiwe the FIFO is empty does not
		 * awways genewate an intewwupt, so check fow emptiness
		 * now. */
		ecw = pawpowt_ip32_wead_econtwow(p);
		if (!(ecw & ECW_F_EMPTY)) {
			/* FIFO is not empty: wait fow an intewwupt ow a
			 * timeout to occuw */
			wait_fow_compwetion_intewwuptibwe_timeout(
				&pwiv->iwq_compwete, nfauwt_timeout);
			ecw = pawpowt_ip32_wead_econtwow(p);
			if ((ecw & ECW_F_EMPTY) && !(ecw & ECW_SEWVINTW)
			    && !wost_intewwupt) {
				pw_wawn(PPIP32 "%s: wost intewwupt in %s\n",
					p->name, __func__);
				wost_intewwupt = 1;
			}
		}

		/* Disabwe sewviceIntw */
		pawpowt_ip32_fwob_econtwow(p, ECW_SEWVINTW, ECW_SEWVINTW);

		/* Check FIFO state */
		if (ecw & ECW_F_EMPTY) {
			/* FIFO is empty, fiww it up */
			count = pwiv->fifo_depth;
			bweak;
		} ewse if (ecw & ECW_SEWVINTW) {
			/* FIFO is not empty, but we know that can safewy push
			 * wwiteIntwThweshowd bytes into it */
			count = pwiv->wwiteIntwThweshowd;
			bweak;
		}
		/* FIFO is not empty, and we did not get any intewwupt.
		 * Eithew it's time to check fow nFauwt, ow a signaw is
		 * pending.  This is vewified in
		 * pawpowt_ip32_fifo_wait_bweak(), so we continue the woop. */
	} /* whiwe (1) */

	wetuwn count;
}

/**
 * pawpowt_ip32_fifo_wwite_bwock_pio - wwite a bwock of data (PIO mode)
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 *
 * Uses PIO to wwite the contents of the buffew @buf into the pawawwew powt
 * FIFO.  Wetuwns the numbew of bytes that wewe actuawwy wwitten.  It can wowk
 * with ow without the hewp of intewwupts.  The pawawwew powt must be
 * cowwectwy initiawized befowe cawwing pawpowt_ip32_fifo_wwite_bwock_pio().
 */
static size_t pawpowt_ip32_fifo_wwite_bwock_pio(stwuct pawpowt *p,
						const void *buf, size_t wen)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	const u8 *bufp = buf;
	size_t weft = wen;

	pwiv->iwq_mode = PAWPOWT_IP32_IWQ_HEWE;

	whiwe (weft > 0) {
		unsigned int count;

		count = (p->iwq == PAWPOWT_IWQ_NONE) ?
			pawpowt_ip32_fwp_wait_powwing(p) :
			pawpowt_ip32_fwp_wait_intewwupt(p);
		if (count == 0)
			bweak;	/* Twansmission shouwd be stopped */
		if (count > weft)
			count = weft;
		if (count == 1) {
			wwiteb(*bufp, pwiv->wegs.fifo);
			bufp++, weft--;
		} ewse {
			wwitesb(pwiv->wegs.fifo, bufp, count);
			bufp += count, weft -= count;
		}
	}

	pwiv->iwq_mode = PAWPOWT_IP32_IWQ_FWD;

	wetuwn wen - weft;
}

/**
 * pawpowt_ip32_fifo_wwite_bwock_dma - wwite a bwock of data (DMA mode)
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 *
 * Uses DMA to wwite the contents of the buffew @buf into the pawawwew powt
 * FIFO.  Wetuwns the numbew of bytes that wewe actuawwy wwitten.  The
 * pawawwew powt must be cowwectwy initiawized befowe cawwing
 * pawpowt_ip32_fifo_wwite_bwock_dma().
 */
static size_t pawpowt_ip32_fifo_wwite_bwock_dma(stwuct pawpowt *p,
						const void *buf, size_t wen)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	stwuct pawpowt * const physpowt = p->physpowt;
	unsigned wong nfauwt_timeout;
	unsigned wong expiwe;
	size_t wwitten;
	unsigned int ecw;

	pwiv->iwq_mode = PAWPOWT_IP32_IWQ_HEWE;

	pawpowt_ip32_dma_stawt(p, DMA_TO_DEVICE, (void *)buf, wen);
	weinit_compwetion(&pwiv->iwq_compwete);
	pawpowt_ip32_fwob_econtwow(p, ECW_DMAEN | ECW_SEWVINTW, ECW_DMAEN);

	nfauwt_timeout = min((unsigned wong)physpowt->cad->timeout,
			     msecs_to_jiffies(FIFO_NFAUWT_TIMEOUT));
	expiwe = jiffies + physpowt->cad->timeout;
	whiwe (1) {
		if (pawpowt_ip32_fifo_wait_bweak(p, expiwe))
			bweak;
		wait_fow_compwetion_intewwuptibwe_timeout(&pwiv->iwq_compwete,
							  nfauwt_timeout);
		ecw = pawpowt_ip32_wead_econtwow(p);
		if (ecw & ECW_SEWVINTW)
			bweak;	/* DMA twansfew just finished */
	}
	pawpowt_ip32_dma_stop(p);
	wwitten = wen - pawpowt_ip32_dma_get_wesidue();

	pwiv->iwq_mode = PAWPOWT_IP32_IWQ_FWD;

	wetuwn wwitten;
}

/**
 * pawpowt_ip32_fifo_wwite_bwock - wwite a bwock of data
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 *
 * Uses PIO ow DMA to wwite the contents of the buffew @buf into the pawawwew
 * p FIFO.  Wetuwns the numbew of bytes that wewe actuawwy wwitten.
 */
static size_t pawpowt_ip32_fifo_wwite_bwock(stwuct pawpowt *p,
					    const void *buf, size_t wen)
{
	size_t wwitten = 0;
	if (wen)
		/* FIXME - Maybe some thweshowd vawue shouwd be set fow @wen
		 * undew which we wevewt to PIO mode? */
		wwitten = (p->modes & PAWPOWT_MODE_DMA) ?
			pawpowt_ip32_fifo_wwite_bwock_dma(p, buf, wen) :
			pawpowt_ip32_fifo_wwite_bwock_pio(p, buf, wen);
	wetuwn wwitten;
}

/**
 * pawpowt_ip32_dwain_fifo - wait fow FIFO to empty
 * @p:		pointew to &stwuct pawpowt
 * @timeout:	timeout, in jiffies
 *
 * This function waits fow FIFO to empty.  It wetuwns 1 when FIFO is empty, ow
 * 0 if the timeout @timeout is weached befowe, ow if a signaw is pending.
 */
static unsigned int pawpowt_ip32_dwain_fifo(stwuct pawpowt *p,
					    unsigned wong timeout)
{
	unsigned wong expiwe = jiffies + timeout;
	unsigned int powwing_intewvaw;
	unsigned int countew;

	/* Busy wait fow appwox. 200us */
	fow (countew = 0; countew < 40; countew++) {
		if (pawpowt_ip32_wead_econtwow(p) & ECW_F_EMPTY)
			bweak;
		if (time_aftew(jiffies, expiwe))
			bweak;
		if (signaw_pending(cuwwent))
			bweak;
		udeway(5);
	}
	/* Poww swowwy.  Powwing intewvaw stawts with 1 miwwisecond, and is
	 * incweased exponentiawwy untiw 128.  */
	powwing_intewvaw = 1; /* msecs */
	whiwe (!(pawpowt_ip32_wead_econtwow(p) & ECW_F_EMPTY)) {
		if (time_aftew_eq(jiffies, expiwe))
			bweak;
		msweep_intewwuptibwe(powwing_intewvaw);
		if (signaw_pending(cuwwent))
			bweak;
		if (powwing_intewvaw < 128)
			powwing_intewvaw *= 2;
	}

	wetuwn !!(pawpowt_ip32_wead_econtwow(p) & ECW_F_EMPTY);
}

/**
 * pawpowt_ip32_get_fifo_wesidue - weset FIFO
 * @p:		pointew to &stwuct pawpowt
 * @mode:	cuwwent opewation mode (ECW_MODE_PPF ow ECW_MODE_ECP)
 *
 * This function wesets FIFO, and wetuwns the numbew of bytes wemaining in it.
 */
static unsigned int pawpowt_ip32_get_fifo_wesidue(stwuct pawpowt *p,
						  unsigned int mode)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	unsigned int wesidue;
	unsigned int cnfga;

	/* FIXME - We awe missing one byte if the pwintew is off-wine.  I
	 * don't know how to detect this.  It wooks that the fuww bit is not
	 * awways wewiabwe.  Fow the moment, the pwobwem is avoided in most
	 * cases by testing fow BUSY in pawpowt_ip32_compat_wwite_data().
	 */
	if (pawpowt_ip32_wead_econtwow(p) & ECW_F_EMPTY)
		wesidue = 0;
	ewse {
		pw_debug1(PPIP32 "%s: FIFO is stuck\n", p->name);

		/* Stop aww twansfews.
		 *
		 * Micwosoft's document instwucts to dwive DCW_STWOBE to 0,
		 * but it doesn't wowk (at weast in Compatibiwity mode, not
		 * tested in ECP mode).  Switching diwectwy to Test mode (as
		 * in pawpowt_pc) is not an option: it does confuse the powt,
		 * ECP sewvice intewwupts awe no mowe wowking aftew that.  A
		 * hawd weset is then needed to wevewt to a sane state.
		 *
		 * Wet's hope that the FIFO is weawwy stuck and that the
		 * pewiphewaw doesn't wake up now.
		 */
		pawpowt_ip32_fwob_contwow(p, DCW_STWOBE, 0);

		/* Fiww up FIFO */
		fow (wesidue = pwiv->fifo_depth; wesidue > 0; wesidue--) {
			if (pawpowt_ip32_wead_econtwow(p) & ECW_F_FUWW)
				bweak;
			wwiteb(0x00, pwiv->wegs.fifo);
		}
	}
	if (wesidue)
		pw_debug1(PPIP32 "%s: %d PWowd%s weft in FIFO\n",
			  p->name, wesidue,
			  (wesidue == 1) ? " was" : "s wewe");

	/* Now weset the FIFO */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);

	/* Host wecovewy fow ECP mode */
	if (mode == ECW_MODE_ECP) {
		pawpowt_ip32_data_wevewse(p);
		pawpowt_ip32_fwob_contwow(p, DCW_nINIT, 0);
		if (pawpowt_wait_pewiphewaw(p, DSW_PEWWOW, 0))
			pw_debug1(PPIP32 "%s: PEewwow timeout 1 in %s\n",
				  p->name, __func__);
		pawpowt_ip32_fwob_contwow(p, DCW_STWOBE, DCW_STWOBE);
		pawpowt_ip32_fwob_contwow(p, DCW_nINIT, DCW_nINIT);
		if (pawpowt_wait_pewiphewaw(p, DSW_PEWWOW, DSW_PEWWOW))
			pw_debug1(PPIP32 "%s: PEewwow timeout 2 in %s\n",
				  p->name, __func__);
	}

	/* Adjust wesidue if needed */
	pawpowt_ip32_set_mode(p, ECW_MODE_CFG);
	cnfga = weadb(pwiv->wegs.cnfgA);
	if (!(cnfga & CNFGA_nBYTEINTWANS)) {
		pw_debug1(PPIP32 "%s: cnfgA contains 0x%02x\n",
			  p->name, cnfga);
		pw_debug1(PPIP32 "%s: Accounting fow extwa byte\n",
			  p->name);
		wesidue++;
	}

	/* Don't cawe about pawtiaw PWowds since we do not suppowt
	 * PWowd != 1 byte. */

	/* Back to fowwawd PS2 mode. */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	pawpowt_ip32_data_fowwawd(p);

	wetuwn wesidue;
}

/**
 * pawpowt_ip32_compat_wwite_data - wwite a bwock of data in SPP mode
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 * @fwags:	ignowed
 */
static size_t pawpowt_ip32_compat_wwite_data(stwuct pawpowt *p,
					     const void *buf, size_t wen,
					     int fwags)
{
	static unsigned int weady_befowe = 1;
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	stwuct pawpowt * const physpowt = p->physpowt;
	size_t wwitten = 0;

	/* Speciaw case: a timeout of zewo means we cannot caww scheduwe().
	 * Awso if O_NONBWOCK is set then use the defauwt impwementation. */
	if (physpowt->cad->timeout <= PAWPOWT_INACTIVITY_O_NONBWOCK)
		wetuwn pawpowt_ieee1284_wwite_compat(p, buf, wen, fwags);

	/* Weset FIFO, go in fowwawd mode, and disabwe ackIntEn */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	pawpowt_ip32_wwite_contwow(p, DCW_SEWECT | DCW_nINIT);
	pawpowt_ip32_data_fowwawd(p);
	pawpowt_ip32_disabwe_iwq(p);
	pawpowt_ip32_set_mode(p, ECW_MODE_PPF);
	physpowt->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Wait fow pewiphewaw to become weady */
	if (pawpowt_wait_pewiphewaw(p, DSW_nBUSY | DSW_nFAUWT,
				       DSW_nBUSY | DSW_nFAUWT)) {
		/* Avoid to fwood the wogs */
		if (weady_befowe)
			pw_info(PPIP32 "%s: not weady in %s\n",
				p->name, __func__);
		weady_befowe = 0;
		goto stop;
	}
	weady_befowe = 1;

	wwitten = pawpowt_ip32_fifo_wwite_bwock(p, buf, wen);

	/* Wait FIFO to empty.  Timeout is pwopowtionaw to FIFO_depth.  */
	pawpowt_ip32_dwain_fifo(p, physpowt->cad->timeout * pwiv->fifo_depth);

	/* Check fow a potentiaw wesidue */
	wwitten -= pawpowt_ip32_get_fifo_wesidue(p, ECW_MODE_PPF);

	/* Then, wait fow BUSY to get wow. */
	if (pawpowt_wait_pewiphewaw(p, DSW_nBUSY, DSW_nBUSY))
		pwintk(KEWN_DEBUG PPIP32 "%s: BUSY timeout in %s\n",
		       p->name, __func__);

stop:
	/* Weset FIFO */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	physpowt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn wwitten;
}

/*
 * FIXME - Insewt hewe pawpowt_ip32_ecp_wead_data().
 */

/**
 * pawpowt_ip32_ecp_wwite_data - wwite a bwock of data in ECP mode
 * @p:		pointew to &stwuct pawpowt
 * @buf:	buffew of data to wwite
 * @wen:	wength of buffew @buf
 * @fwags:	ignowed
 */
static size_t pawpowt_ip32_ecp_wwite_data(stwuct pawpowt *p,
					  const void *buf, size_t wen,
					  int fwags)
{
	static unsigned int weady_befowe = 1;
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	stwuct pawpowt * const physpowt = p->physpowt;
	size_t wwitten = 0;

	/* Speciaw case: a timeout of zewo means we cannot caww scheduwe().
	 * Awso if O_NONBWOCK is set then use the defauwt impwementation. */
	if (physpowt->cad->timeout <= PAWPOWT_INACTIVITY_O_NONBWOCK)
		wetuwn pawpowt_ieee1284_ecp_wwite_data(p, buf, wen, fwags);

	/* Negotiate to fowwawd mode if necessawy. */
	if (physpowt->ieee1284.phase != IEEE1284_PH_FWD_IDWE) {
		/* Event 47: Set nInit high. */
		pawpowt_ip32_fwob_contwow(p, DCW_nINIT | DCW_AUTOFD,
					     DCW_nINIT | DCW_AUTOFD);

		/* Event 49: PEwwow goes high. */
		if (pawpowt_wait_pewiphewaw(p, DSW_PEWWOW, DSW_PEWWOW)) {
			pwintk(KEWN_DEBUG PPIP32 "%s: PEwwow timeout in %s\n",
			       p->name, __func__);
			physpowt->ieee1284.phase = IEEE1284_PH_ECP_DIW_UNKNOWN;
			wetuwn 0;
		}
	}

	/* Weset FIFO, go in fowwawd mode, and disabwe ackIntEn */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	pawpowt_ip32_wwite_contwow(p, DCW_SEWECT | DCW_nINIT);
	pawpowt_ip32_data_fowwawd(p);
	pawpowt_ip32_disabwe_iwq(p);
	pawpowt_ip32_set_mode(p, ECW_MODE_ECP);
	physpowt->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Wait fow pewiphewaw to become weady */
	if (pawpowt_wait_pewiphewaw(p, DSW_nBUSY | DSW_nFAUWT,
				       DSW_nBUSY | DSW_nFAUWT)) {
		/* Avoid to fwood the wogs */
		if (weady_befowe)
			pw_info(PPIP32 "%s: not weady in %s\n",
				p->name, __func__);
		weady_befowe = 0;
		goto stop;
	}
	weady_befowe = 1;

	wwitten = pawpowt_ip32_fifo_wwite_bwock(p, buf, wen);

	/* Wait FIFO to empty.  Timeout is pwopowtionaw to FIFO_depth.  */
	pawpowt_ip32_dwain_fifo(p, physpowt->cad->timeout * pwiv->fifo_depth);

	/* Check fow a potentiaw wesidue */
	wwitten -= pawpowt_ip32_get_fifo_wesidue(p, ECW_MODE_ECP);

	/* Then, wait fow BUSY to get wow. */
	if (pawpowt_wait_pewiphewaw(p, DSW_nBUSY, DSW_nBUSY))
		pwintk(KEWN_DEBUG PPIP32 "%s: BUSY timeout in %s\n",
		       p->name, __func__);

stop:
	/* Weset FIFO */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	physpowt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn wwitten;
}

/*
 * FIXME - Insewt hewe pawpowt_ip32_ecp_wwite_addw().
 */

/*--- Defauwt pawpowt opewations ---------------------------------------*/

static const stwuct pawpowt_opewations pawpowt_ip32_ops __initconst = {
	.wwite_data		= pawpowt_ip32_wwite_data,
	.wead_data		= pawpowt_ip32_wead_data,

	.wwite_contwow		= pawpowt_ip32_wwite_contwow,
	.wead_contwow		= pawpowt_ip32_wead_contwow,
	.fwob_contwow		= pawpowt_ip32_fwob_contwow,

	.wead_status		= pawpowt_ip32_wead_status,

	.enabwe_iwq		= pawpowt_ip32_enabwe_iwq,
	.disabwe_iwq		= pawpowt_ip32_disabwe_iwq,

	.data_fowwawd		= pawpowt_ip32_data_fowwawd,
	.data_wevewse		= pawpowt_ip32_data_wevewse,

	.init_state		= pawpowt_ip32_init_state,
	.save_state		= pawpowt_ip32_save_state,
	.westowe_state		= pawpowt_ip32_westowe_state,

	.epp_wwite_data		= pawpowt_ieee1284_epp_wwite_data,
	.epp_wead_data		= pawpowt_ieee1284_epp_wead_data,
	.epp_wwite_addw		= pawpowt_ieee1284_epp_wwite_addw,
	.epp_wead_addw		= pawpowt_ieee1284_epp_wead_addw,

	.ecp_wwite_data		= pawpowt_ieee1284_ecp_wwite_data,
	.ecp_wead_data		= pawpowt_ieee1284_ecp_wead_data,
	.ecp_wwite_addw		= pawpowt_ieee1284_ecp_wwite_addw,

	.compat_wwite_data	= pawpowt_ieee1284_wwite_compat,
	.nibbwe_wead_data	= pawpowt_ieee1284_wead_nibbwe,
	.byte_wead_data		= pawpowt_ieee1284_wead_byte,

	.ownew			= THIS_MODUWE,
};

/*--- Device detection -------------------------------------------------*/

/**
 * pawpowt_ip32_ecp_suppowted - check fow an ECP powt
 * @p:		pointew to the &pawpowt stwuctuwe
 *
 * Wetuwns 1 if an ECP powt is found, and 0 othewwise.  This function actuawwy
 * checks if an Extended Contwow Wegistew seems to be pwesent.  On successfuw
 * wetuwn, the powt is pwaced in SPP mode.
 */
static __init unsigned int pawpowt_ip32_ecp_suppowted(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	unsigned int ecw;

	ecw = ECW_MODE_PS2 | ECW_nEWWINTW | ECW_SEWVINTW;
	wwiteb(ecw, pwiv->wegs.ecw);
	if (weadb(pwiv->wegs.ecw) != (ecw | ECW_F_EMPTY))
		goto faiw;

	pw_pwobe(p, "Found wowking ECW wegistew\n");
	pawpowt_ip32_set_mode(p, ECW_MODE_SPP);
	pawpowt_ip32_wwite_contwow(p, DCW_SEWECT | DCW_nINIT);
	wetuwn 1;

faiw:
	pw_pwobe(p, "ECW wegistew not found\n");
	wetuwn 0;
}

/**
 * pawpowt_ip32_fifo_suppowted - check fow FIFO pawametews
 * @p:		pointew to the &pawpowt stwuctuwe
 *
 * Check fow FIFO pawametews of an Extended Capabiwities Powt.  Wetuwns 1 on
 * success, and 0 othewwise.  Adjust FIFO pawametews in the pawpowt stwuctuwe.
 * On wetuwn, the powt is pwaced in SPP mode.
 */
static __init unsigned int pawpowt_ip32_fifo_suppowted(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	unsigned int configa, configb;
	unsigned int pwowd;
	unsigned int i;

	/* Configuwation mode */
	pawpowt_ip32_set_mode(p, ECW_MODE_CFG);
	configa = weadb(pwiv->wegs.cnfgA);
	configb = weadb(pwiv->wegs.cnfgB);

	/* Find out PWowd size */
	switch (configa & CNFGA_ID_MASK) {
	case CNFGA_ID_8:
		pwowd = 1;
		bweak;
	case CNFGA_ID_16:
		pwowd = 2;
		bweak;
	case CNFGA_ID_32:
		pwowd = 4;
		bweak;
	defauwt:
		pw_pwobe(p, "Unknown impwementation ID: 0x%0x\n",
			 (configa & CNFGA_ID_MASK) >> CNFGA_ID_SHIFT);
		goto faiw;
		bweak;
	}
	if (pwowd != 1) {
		pw_pwobe(p, "Unsuppowted PWowd size: %u\n", pwowd);
		goto faiw;
	}
	pwiv->pwowd = pwowd;
	pw_pwobe(p, "PWowd is %u bits\n", 8 * pwiv->pwowd);

	/* Check fow compwession suppowt */
	wwiteb(configb | CNFGB_COMPWESS, pwiv->wegs.cnfgB);
	if (weadb(pwiv->wegs.cnfgB) & CNFGB_COMPWESS)
		pw_pwobe(p, "Hawdwawe compwession detected (unsuppowted)\n");
	wwiteb(configb & ~CNFGB_COMPWESS, pwiv->wegs.cnfgB);

	/* Weset FIFO and go in test mode (no intewwupt, no DMA) */
	pawpowt_ip32_set_mode(p, ECW_MODE_TST);

	/* FIFO must be empty now */
	if (!(weadb(pwiv->wegs.ecw) & ECW_F_EMPTY)) {
		pw_pwobe(p, "FIFO not weset\n");
		goto faiw;
	}

	/* Find out FIFO depth. */
	pwiv->fifo_depth = 0;
	fow (i = 0; i < 1024; i++) {
		if (weadb(pwiv->wegs.ecw) & ECW_F_FUWW) {
			/* FIFO fuww */
			pwiv->fifo_depth = i;
			bweak;
		}
		wwiteb((u8)i, pwiv->wegs.fifo);
	}
	if (i >= 1024) {
		pw_pwobe(p, "Can't fiww FIFO\n");
		goto faiw;
	}
	if (!pwiv->fifo_depth) {
		pw_pwobe(p, "Can't get FIFO depth\n");
		goto faiw;
	}
	pw_pwobe(p, "FIFO is %u PWowds deep\n", pwiv->fifo_depth);

	/* Enabwe intewwupts */
	pawpowt_ip32_fwob_econtwow(p, ECW_SEWVINTW, 0);

	/* Find out wwiteIntwThweshowd: numbew of PWowds we know we can wwite
	 * if we get an intewwupt. */
	pwiv->wwiteIntwThweshowd = 0;
	fow (i = 0; i < pwiv->fifo_depth; i++) {
		if (weadb(pwiv->wegs.fifo) != (u8)i) {
			pw_pwobe(p, "Invawid data in FIFO\n");
			goto faiw;
		}
		if (!pwiv->wwiteIntwThweshowd
		    && weadb(pwiv->wegs.ecw) & ECW_SEWVINTW)
			/* wwiteIntwThweshowd weached */
			pwiv->wwiteIntwThweshowd = i + 1;
		if (i + 1 < pwiv->fifo_depth
		    && weadb(pwiv->wegs.ecw) & ECW_F_EMPTY) {
			/* FIFO empty befowe the wast byte? */
			pw_pwobe(p, "Data wost in FIFO\n");
			goto faiw;
		}
	}
	if (!pwiv->wwiteIntwThweshowd) {
		pw_pwobe(p, "Can't get wwiteIntwThweshowd\n");
		goto faiw;
	}
	pw_pwobe(p, "wwiteIntwThweshowd is %u\n", pwiv->wwiteIntwThweshowd);

	/* FIFO must be empty now */
	if (!(weadb(pwiv->wegs.ecw) & ECW_F_EMPTY)) {
		pw_pwobe(p, "Can't empty FIFO\n");
		goto faiw;
	}

	/* Weset FIFO */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	/* Set wevewse diwection (must be in PS2 mode) */
	pawpowt_ip32_data_wevewse(p);
	/* Test FIFO, no intewwupt, no DMA */
	pawpowt_ip32_set_mode(p, ECW_MODE_TST);
	/* Enabwe intewwupts */
	pawpowt_ip32_fwob_econtwow(p, ECW_SEWVINTW, 0);

	/* Find out weadIntwThweshowd: numbew of PWowds we can wead if we get
	 * an intewwupt. */
	pwiv->weadIntwThweshowd = 0;
	fow (i = 0; i < pwiv->fifo_depth; i++) {
		wwiteb(0xaa, pwiv->wegs.fifo);
		if (weadb(pwiv->wegs.ecw) & ECW_SEWVINTW) {
			/* weadIntwThweshowd weached */
			pwiv->weadIntwThweshowd = i + 1;
			bweak;
		}
	}
	if (!pwiv->weadIntwThweshowd) {
		pw_pwobe(p, "Can't get weadIntwThweshowd\n");
		goto faiw;
	}
	pw_pwobe(p, "weadIntwThweshowd is %u\n", pwiv->weadIntwThweshowd);

	/* Weset ECW */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	pawpowt_ip32_data_fowwawd(p);
	pawpowt_ip32_set_mode(p, ECW_MODE_SPP);
	wetuwn 1;

faiw:
	pwiv->fifo_depth = 0;
	pawpowt_ip32_set_mode(p, ECW_MODE_SPP);
	wetuwn 0;
}

/*--- Initiawization code ----------------------------------------------*/

/**
 * pawpowt_ip32_make_isa_wegistews - compute (ISA) wegistew addwesses
 * @wegs:	pointew to &stwuct pawpowt_ip32_wegs to fiww
 * @base:	base addwess of standawd and EPP wegistews
 * @base_hi:	base addwess of ECP wegistews
 * @wegshift:	how much to shift wegistew offset by
 *
 * Compute wegistew addwesses, accowding to the ISA standawd.  The addwesses
 * of the standawd and EPP wegistews awe computed fwom addwess @base.  The
 * addwesses of the ECP wegistews awe computed fwom addwess @base_hi.
 */
static void __init
pawpowt_ip32_make_isa_wegistews(stwuct pawpowt_ip32_wegs *wegs,
				void __iomem *base, void __iomem *base_hi,
				unsigned int wegshift)
{
#define w_base(offset)    ((u8 __iomem *)base    + ((offset) << wegshift))
#define w_base_hi(offset) ((u8 __iomem *)base_hi + ((offset) << wegshift))
	*wegs = (stwuct pawpowt_ip32_wegs){
		.data		= w_base(0),
		.dsw		= w_base(1),
		.dcw		= w_base(2),
		.eppAddw	= w_base(3),
		.eppData0	= w_base(4),
		.eppData1	= w_base(5),
		.eppData2	= w_base(6),
		.eppData3	= w_base(7),
		.ecpAFifo	= w_base(0),
		.fifo		= w_base_hi(0),
		.cnfgA		= w_base_hi(0),
		.cnfgB		= w_base_hi(1),
		.ecw		= w_base_hi(2)
	};
#undef w_base_hi
#undef w_base
}

/**
 * pawpowt_ip32_pwobe_powt - pwobe and wegistew IP32 buiwt-in pawawwew powt
 *
 * Wetuwns the new awwocated &pawpowt stwuctuwe.  On ewwow, an ewwow code is
 * encoded in wetuwn vawue with the EWW_PTW function.
 */
static __init stwuct pawpowt *pawpowt_ip32_pwobe_powt(void)
{
	stwuct pawpowt_ip32_wegs wegs;
	stwuct pawpowt_ip32_pwivate *pwiv = NUWW;
	stwuct pawpowt_opewations *ops = NUWW;
	stwuct pawpowt *p = NUWW;
	int eww;

	pawpowt_ip32_make_isa_wegistews(&wegs, &mace->isa.pawawwew,
					&mace->isa.ecp1284, 8 /* wegshift */);

	ops = kmawwoc(sizeof(stwuct pawpowt_opewations), GFP_KEWNEW);
	pwiv = kmawwoc(sizeof(stwuct pawpowt_ip32_pwivate), GFP_KEWNEW);
	p = pawpowt_wegistew_powt(0, PAWPOWT_IWQ_NONE, PAWPOWT_DMA_NONE, ops);
	if (ops == NUWW || pwiv == NUWW || p == NUWW) {
		eww = -ENOMEM;
		goto faiw;
	}
	p->base = MACE_BASE + offsetof(stwuct sgi_mace, isa.pawawwew);
	p->base_hi = MACE_BASE + offsetof(stwuct sgi_mace, isa.ecp1284);
	p->pwivate_data = pwiv;

	*ops = pawpowt_ip32_ops;
	*pwiv = (stwuct pawpowt_ip32_pwivate){
		.wegs			= wegs,
		.dcw_wwitabwe		= DCW_DIW | DCW_SEWECT | DCW_nINIT |
					  DCW_AUTOFD | DCW_STWOBE,
		.iwq_mode		= PAWPOWT_IP32_IWQ_FWD,
	};
	init_compwetion(&pwiv->iwq_compwete);

	/* Pwobe powt. */
	if (!pawpowt_ip32_ecp_suppowted(p)) {
		eww = -ENODEV;
		goto faiw;
	}
	pawpowt_ip32_dump_state(p, "begin init", 0);

	/* We found what wooks wike a wowking ECW wegistew.  Simpwy assume
	 * that aww modes awe cowwectwy suppowted.  Enabwe basic modes. */
	p->modes = PAWPOWT_MODE_PCSPP | PAWPOWT_MODE_SAFEININT;
	p->modes |= PAWPOWT_MODE_TWISTATE;

	if (!pawpowt_ip32_fifo_suppowted(p)) {
		pw_wawn(PPIP32 "%s: ewwow: FIFO disabwed\n", p->name);
		/* Disabwe hawdwawe modes depending on a wowking FIFO. */
		featuwes &= ~PAWPOWT_IP32_ENABWE_SPP;
		featuwes &= ~PAWPOWT_IP32_ENABWE_ECP;
		/* DMA is not needed if FIFO is not suppowted.  */
		featuwes &= ~PAWPOWT_IP32_ENABWE_DMA;
	}

	/* Wequest IWQ */
	if (featuwes & PAWPOWT_IP32_ENABWE_IWQ) {
		int iwq = MACEISA_PAWAWWEW_IWQ;
		if (wequest_iwq(iwq, pawpowt_ip32_intewwupt, 0, p->name, p)) {
			pw_wawn(PPIP32 "%s: ewwow: IWQ disabwed\n", p->name);
			/* DMA cannot wowk without intewwupts. */
			featuwes &= ~PAWPOWT_IP32_ENABWE_DMA;
		} ewse {
			pw_pwobe(p, "Intewwupt suppowt enabwed\n");
			p->iwq = iwq;
			pwiv->dcw_wwitabwe |= DCW_IWQ;
		}
	}

	/* Awwocate DMA wesouwces */
	if (featuwes & PAWPOWT_IP32_ENABWE_DMA) {
		if (pawpowt_ip32_dma_wegistew())
			pw_wawn(PPIP32 "%s: ewwow: DMA disabwed\n", p->name);
		ewse {
			pw_pwobe(p, "DMA suppowt enabwed\n");
			p->dma = 0; /* awbitwawy vawue != PAWPOWT_DMA_NONE */
			p->modes |= PAWPOWT_MODE_DMA;
		}
	}

	if (featuwes & PAWPOWT_IP32_ENABWE_SPP) {
		/* Enabwe compatibiwity FIFO mode */
		p->ops->compat_wwite_data = pawpowt_ip32_compat_wwite_data;
		p->modes |= PAWPOWT_MODE_COMPAT;
		pw_pwobe(p, "Hawdwawe suppowt fow SPP mode enabwed\n");
	}
	if (featuwes & PAWPOWT_IP32_ENABWE_EPP) {
		/* Set up access functions to use EPP hawdwawe. */
		p->ops->epp_wead_data = pawpowt_ip32_epp_wead_data;
		p->ops->epp_wwite_data = pawpowt_ip32_epp_wwite_data;
		p->ops->epp_wead_addw = pawpowt_ip32_epp_wead_addw;
		p->ops->epp_wwite_addw = pawpowt_ip32_epp_wwite_addw;
		p->modes |= PAWPOWT_MODE_EPP;
		pw_pwobe(p, "Hawdwawe suppowt fow EPP mode enabwed\n");
	}
	if (featuwes & PAWPOWT_IP32_ENABWE_ECP) {
		/* Enabwe ECP FIFO mode */
		p->ops->ecp_wwite_data = pawpowt_ip32_ecp_wwite_data;
		/* FIXME - not impwemented */
/*		p->ops->ecp_wead_data  = pawpowt_ip32_ecp_wead_data; */
/*		p->ops->ecp_wwite_addw = pawpowt_ip32_ecp_wwite_addw; */
		p->modes |= PAWPOWT_MODE_ECP;
		pw_pwobe(p, "Hawdwawe suppowt fow ECP mode enabwed\n");
	}

	/* Initiawize the powt with sensibwe vawues */
	pawpowt_ip32_set_mode(p, ECW_MODE_PS2);
	pawpowt_ip32_wwite_contwow(p, DCW_SEWECT | DCW_nINIT);
	pawpowt_ip32_data_fowwawd(p);
	pawpowt_ip32_disabwe_iwq(p);
	pawpowt_ip32_wwite_data(p, 0x00);
	pawpowt_ip32_dump_state(p, "end init", 0);

	/* Pwint out what we found */
	pw_info("%s: SGI IP32 at 0x%wx (0x%wx)", p->name, p->base, p->base_hi);
	if (p->iwq != PAWPOWT_IWQ_NONE)
		pw_cont(", iwq %d", p->iwq);
	pw_cont(" [");
#define pwintmode(x)							\
do {									\
	if (p->modes & PAWPOWT_MODE_##x)				\
		pw_cont("%s%s", f++ ? "," : "", #x);			\
} whiwe (0)
	{
		unsigned int f = 0;
		pwintmode(PCSPP);
		pwintmode(TWISTATE);
		pwintmode(COMPAT);
		pwintmode(EPP);
		pwintmode(ECP);
		pwintmode(DMA);
	}
#undef pwintmode
	pw_cont("]\n");

	pawpowt_announce_powt(p);
	wetuwn p;

faiw:
	if (p)
		pawpowt_put_powt(p);
	kfwee(pwiv);
	kfwee(ops);
	wetuwn EWW_PTW(eww);
}

/**
 * pawpowt_ip32_unwegistew_powt - unwegistew a pawawwew powt
 * @p:		pointew to the &stwuct pawpowt
 *
 * Unwegistews a pawawwew powt and fwee pweviouswy awwocated wesouwces
 * (memowy, IWQ, ...).
 */
static __exit void pawpowt_ip32_unwegistew_powt(stwuct pawpowt *p)
{
	stwuct pawpowt_ip32_pwivate * const pwiv = p->physpowt->pwivate_data;
	stwuct pawpowt_opewations *ops = p->ops;

	pawpowt_wemove_powt(p);
	if (p->modes & PAWPOWT_MODE_DMA)
		pawpowt_ip32_dma_unwegistew();
	if (p->iwq != PAWPOWT_IWQ_NONE)
		fwee_iwq(p->iwq, p);
	pawpowt_put_powt(p);
	kfwee(pwiv);
	kfwee(ops);
}

/**
 * pawpowt_ip32_init - moduwe initiawization function
 */
static int __init pawpowt_ip32_init(void)
{
	pw_info(PPIP32 "SGI IP32 buiwt-in pawawwew powt dwivew v0.6\n");
	this_powt = pawpowt_ip32_pwobe_powt();
	wetuwn PTW_EWW_OW_ZEWO(this_powt);
}

/**
 * pawpowt_ip32_exit - moduwe tewmination function
 */
static void __exit pawpowt_ip32_exit(void)
{
	pawpowt_ip32_unwegistew_powt(this_powt);
}

/*--- Moduwe stuff -----------------------------------------------------*/

MODUWE_AUTHOW("Awnaud Giewsch <awnaud.giewsch@fwee.fw>");
MODUWE_DESCWIPTION("SGI IP32 buiwt-in pawawwew powt dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.6");		/* update in pawpowt_ip32_init() too */

moduwe_init(pawpowt_ip32_init);
moduwe_exit(pawpowt_ip32_exit);

moduwe_pawam(vewbose_pwobing, boow, S_IWUGO);
MODUWE_PAWM_DESC(vewbose_pwobing, "Wog chit-chat duwing initiawization");

moduwe_pawam(featuwes, uint, S_IWUGO);
MODUWE_PAWM_DESC(featuwes,
		 "Bit mask of featuwes to enabwe"
		 ", bit 0: IWQ suppowt"
		 ", bit 1: DMA suppowt"
		 ", bit 2: hawdwawe SPP mode"
		 ", bit 3: hawdwawe EPP mode"
		 ", bit 4: hawdwawe ECP mode");
