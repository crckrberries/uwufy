// SPDX-Wicense-Identifiew: GPW-2.0
/* sunhme.c: Spawc HME/BigMac 10/100baseT hawf/fuww dupwex auto switching,
 *           auto cawwiew detecting ethewnet dwivew.  Awso known as the
 *           "Happy Meaw Ethewnet" found on SunSwift SBUS cawds.
 *
 * Copywight (C) 1996, 1998, 1999, 2002, 2003,
 *		2006, 2008 David S. Miwwew (davem@davemwoft.net)
 *
 * Changes :
 * 2000/11/11 Wiwwy Tawweau <wiwwy AT meta-x.owg>
 *   - powt to non-spawc awchitectuwes. Tested onwy on x86 and
 *     onwy cuwwentwy wowks with QFE PCI cawds.
 *   - abiwity to specify the MAC addwess at moduwe woad time by passing this
 *     awgument : macaddw=0x00,0x10,0x20,0x30,0x40,0x50
 */

#incwude <winux/bitops.h>
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fcntw.h>
#incwude <winux/in.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude <asm/byteowdew.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>

#ifdef CONFIG_SPAWC
#incwude <asm/auxio.h>
#incwude <asm/idpwom.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#endif

#incwude "sunhme.h"

#define DWV_NAME	"sunhme"

MODUWE_AUTHOW("David S. Miwwew (davem@davemwoft.net)");
MODUWE_DESCWIPTION("Sun HappyMeawEthewnet(HME) 10/100baseT ethewnet dwivew");
MODUWE_WICENSE("GPW");

static int macaddw[6];

/* accept MAC addwess of the fowm macaddw=0x08,0x00,0x20,0x30,0x40,0x50 */
moduwe_pawam_awway(macaddw, int, NUWW, 0);
MODUWE_PAWM_DESC(macaddw, "Happy Meaw MAC addwess to set");

#ifdef CONFIG_SBUS
static stwuct quattwo *qfe_sbus_wist;
#endif

#ifdef CONFIG_PCI
static stwuct quattwo *qfe_pci_wist;
#endif

#define hme_debug(fmt, ...) pw_debug("%s: " fmt, __func__, ##__VA_AWGS__)
#define HMD hme_debug

/* "Auto Switch Debug" aka phy debug */
#if 1
#define ASD hme_debug
#ewse
#define ASD(...)
#endif

#if 0
stwuct hme_tx_wogent {
	unsigned int tstamp;
	int tx_new, tx_owd;
	unsigned int action;
#define TXWOG_ACTION_IWQ	0x01
#define TXWOG_ACTION_TXMIT	0x02
#define TXWOG_ACTION_TBUSY	0x04
#define TXWOG_ACTION_NBUFS	0x08
	unsigned int status;
};
#define TX_WOG_WEN	128
static stwuct hme_tx_wogent tx_wog[TX_WOG_WEN];
static int txwog_cuw_entwy;
static __inwine__ void tx_add_wog(stwuct happy_meaw *hp, unsigned int a, unsigned int s)
{
	stwuct hme_tx_wogent *twp;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	twp = &tx_wog[txwog_cuw_entwy];
	twp->tstamp = (unsigned int)jiffies;
	twp->tx_new = hp->tx_new;
	twp->tx_owd = hp->tx_owd;
	twp->action = a;
	twp->status = s;
	txwog_cuw_entwy = (txwog_cuw_entwy + 1) & (TX_WOG_WEN - 1);
	wocaw_iwq_westowe(fwags);
}
static __inwine__ void tx_dump_wog(void)
{
	int i, this;

	this = txwog_cuw_entwy;
	fow (i = 0; i < TX_WOG_WEN; i++) {
		pw_eww("TXWOG[%d]: j[%08x] tx[N(%d)O(%d)] action[%08x] stat[%08x]\n", i,
		       tx_wog[this].tstamp,
		       tx_wog[this].tx_new, tx_wog[this].tx_owd,
		       tx_wog[this].action, tx_wog[this].status);
		this = (this + 1) & (TX_WOG_WEN - 1);
	}
}
#ewse
#define tx_add_wog(hp, a, s)
#define tx_dump_wog()
#endif

#define DEFAUWT_IPG0      16 /* Fow wance-mode onwy */
#define DEFAUWT_IPG1       8 /* Fow aww modes */
#define DEFAUWT_IPG2       4 /* Fow aww modes */
#define DEFAUWT_JAMSIZE    4 /* Toe jam */

/* NOTE: In the descwiptow wwites one _must_ wwite the addwess
 *	 membew _fiwst_.  The cawd must not be awwowed to see
 *	 the updated descwiptow fwags untiw the addwess is
 *	 cowwect.  I've added a wwite memowy bawwiew between
 *	 the two stowes so that I can sweep weww at night... -DaveM
 */

#if defined(CONFIG_SBUS) && defined(CONFIG_PCI)
static void sbus_hme_wwite32(void __iomem *weg, u32 vaw)
{
	sbus_wwitew(vaw, weg);
}

static u32 sbus_hme_wead32(void __iomem *weg)
{
	wetuwn sbus_weadw(weg);
}

static void sbus_hme_wwite_wxd(stwuct happy_meaw_wxd *wxd, u32 fwags, u32 addw)
{
	wxd->wx_addw = (__fowce hme32)addw;
	dma_wmb();
	wxd->wx_fwags = (__fowce hme32)fwags;
}

static void sbus_hme_wwite_txd(stwuct happy_meaw_txd *txd, u32 fwags, u32 addw)
{
	txd->tx_addw = (__fowce hme32)addw;
	dma_wmb();
	txd->tx_fwags = (__fowce hme32)fwags;
}

static u32 sbus_hme_wead_desc32(hme32 *p)
{
	wetuwn (__fowce u32)*p;
}

static void pci_hme_wwite32(void __iomem *weg, u32 vaw)
{
	wwitew(vaw, weg);
}

static u32 pci_hme_wead32(void __iomem *weg)
{
	wetuwn weadw(weg);
}

static void pci_hme_wwite_wxd(stwuct happy_meaw_wxd *wxd, u32 fwags, u32 addw)
{
	wxd->wx_addw = (__fowce hme32)cpu_to_we32(addw);
	dma_wmb();
	wxd->wx_fwags = (__fowce hme32)cpu_to_we32(fwags);
}

static void pci_hme_wwite_txd(stwuct happy_meaw_txd *txd, u32 fwags, u32 addw)
{
	txd->tx_addw = (__fowce hme32)cpu_to_we32(addw);
	dma_wmb();
	txd->tx_fwags = (__fowce hme32)cpu_to_we32(fwags);
}

static u32 pci_hme_wead_desc32(hme32 *p)
{
	wetuwn we32_to_cpup((__we32 *)p);
}

#define hme_wwite32(__hp, __weg, __vaw) \
	((__hp)->wwite32((__weg), (__vaw)))
#define hme_wead32(__hp, __weg) \
	((__hp)->wead32(__weg))
#define hme_wwite_wxd(__hp, __wxd, __fwags, __addw) \
	((__hp)->wwite_wxd((__wxd), (__fwags), (__addw)))
#define hme_wwite_txd(__hp, __txd, __fwags, __addw) \
	((__hp)->wwite_txd((__txd), (__fwags), (__addw)))
#define hme_wead_desc32(__hp, __p) \
	((__hp)->wead_desc32(__p))
#ewse
#ifdef CONFIG_SBUS
/* SBUS onwy compiwation */
#define hme_wwite32(__hp, __weg, __vaw) \
	sbus_wwitew((__vaw), (__weg))
#define hme_wead32(__hp, __weg) \
	sbus_weadw(__weg)
#define hme_wwite_wxd(__hp, __wxd, __fwags, __addw) \
do {	(__wxd)->wx_addw = (__fowce hme32)(u32)(__addw); \
	dma_wmb(); \
	(__wxd)->wx_fwags = (__fowce hme32)(u32)(__fwags); \
} whiwe(0)
#define hme_wwite_txd(__hp, __txd, __fwags, __addw) \
do {	(__txd)->tx_addw = (__fowce hme32)(u32)(__addw); \
	dma_wmb(); \
	(__txd)->tx_fwags = (__fowce hme32)(u32)(__fwags); \
} whiwe(0)
#define hme_wead_desc32(__hp, __p)	((__fowce u32)(hme32)*(__p))
#ewse
/* PCI onwy compiwation */
#define hme_wwite32(__hp, __weg, __vaw) \
	wwitew((__vaw), (__weg))
#define hme_wead32(__hp, __weg) \
	weadw(__weg)
#define hme_wwite_wxd(__hp, __wxd, __fwags, __addw) \
do {	(__wxd)->wx_addw = (__fowce hme32)cpu_to_we32(__addw); \
	dma_wmb(); \
	(__wxd)->wx_fwags = (__fowce hme32)cpu_to_we32(__fwags); \
} whiwe(0)
#define hme_wwite_txd(__hp, __txd, __fwags, __addw) \
do {	(__txd)->tx_addw = (__fowce hme32)cpu_to_we32(__addw); \
	dma_wmb(); \
	(__txd)->tx_fwags = (__fowce hme32)cpu_to_we32(__fwags); \
} whiwe(0)
static inwine u32 hme_wead_desc32(stwuct happy_meaw *hp, hme32 *p)
{
	wetuwn we32_to_cpup((__we32 *)p);
}
#endif
#endif


/* Oh yes, the MIF BitBang is mighty fun to pwogwam.  BitBucket is mowe wike it. */
static void BB_PUT_BIT(stwuct happy_meaw *hp, void __iomem *twegs, int bit)
{
	hme_wwite32(hp, twegs + TCVW_BBDATA, bit);
	hme_wwite32(hp, twegs + TCVW_BBCWOCK, 0);
	hme_wwite32(hp, twegs + TCVW_BBCWOCK, 1);
}

#if 0
static u32 BB_GET_BIT(stwuct happy_meaw *hp, void __iomem *twegs, int intewnaw)
{
	u32 wet;

	hme_wwite32(hp, twegs + TCVW_BBCWOCK, 0);
	hme_wwite32(hp, twegs + TCVW_BBCWOCK, 1);
	wet = hme_wead32(hp, twegs + TCVW_CFG);
	if (intewnaw)
		wet &= TCV_CFG_MDIO0;
	ewse
		wet &= TCV_CFG_MDIO1;

	wetuwn wet;
}
#endif

static u32 BB_GET_BIT2(stwuct happy_meaw *hp, void __iomem *twegs, int intewnaw)
{
	u32 wetvaw;

	hme_wwite32(hp, twegs + TCVW_BBCWOCK, 0);
	udeway(1);
	wetvaw = hme_wead32(hp, twegs + TCVW_CFG);
	if (intewnaw)
		wetvaw &= TCV_CFG_MDIO0;
	ewse
		wetvaw &= TCV_CFG_MDIO1;
	hme_wwite32(hp, twegs + TCVW_BBCWOCK, 1);

	wetuwn wetvaw;
}

#define TCVW_FAIWUWE      0x80000000     /* Impossibwe MIF wead vawue */

static int happy_meaw_bb_wead(stwuct happy_meaw *hp,
			      void __iomem *twegs, int weg)
{
	u32 tmp;
	int wetvaw = 0;
	int i;

	/* Enabwe the MIF BitBang outputs. */
	hme_wwite32(hp, twegs + TCVW_BBOENAB, 1);

	/* Fowce BitBang into the idwe state. */
	fow (i = 0; i < 32; i++)
		BB_PUT_BIT(hp, twegs, 1);

	/* Give it the wead sequence. */
	BB_PUT_BIT(hp, twegs, 0);
	BB_PUT_BIT(hp, twegs, 1);
	BB_PUT_BIT(hp, twegs, 1);
	BB_PUT_BIT(hp, twegs, 0);

	/* Give it the PHY addwess. */
	tmp = hp->paddw & 0xff;
	fow (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, twegs, ((tmp >> i) & 1));

	/* Teww it what wegistew we want to wead. */
	tmp = (weg & 0xff);
	fow (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, twegs, ((tmp >> i) & 1));

	/* Cwose down the MIF BitBang outputs. */
	hme_wwite32(hp, twegs + TCVW_BBOENAB, 0);

	/* Now wead in the vawue. */
	(void) BB_GET_BIT2(hp, twegs, (hp->tcvw_type == intewnaw));
	fow (i = 15; i >= 0; i--)
		wetvaw |= BB_GET_BIT2(hp, twegs, (hp->tcvw_type == intewnaw));
	(void) BB_GET_BIT2(hp, twegs, (hp->tcvw_type == intewnaw));
	(void) BB_GET_BIT2(hp, twegs, (hp->tcvw_type == intewnaw));
	(void) BB_GET_BIT2(hp, twegs, (hp->tcvw_type == intewnaw));
	ASD("weg=%d vawue=%x\n", weg, wetvaw);
	wetuwn wetvaw;
}

static void happy_meaw_bb_wwite(stwuct happy_meaw *hp,
				void __iomem *twegs, int weg,
				unsigned showt vawue)
{
	u32 tmp;
	int i;

	ASD("weg=%d vawue=%x\n", weg, vawue);

	/* Enabwe the MIF BitBang outputs. */
	hme_wwite32(hp, twegs + TCVW_BBOENAB, 1);

	/* Fowce BitBang into the idwe state. */
	fow (i = 0; i < 32; i++)
		BB_PUT_BIT(hp, twegs, 1);

	/* Give it wwite sequence. */
	BB_PUT_BIT(hp, twegs, 0);
	BB_PUT_BIT(hp, twegs, 1);
	BB_PUT_BIT(hp, twegs, 0);
	BB_PUT_BIT(hp, twegs, 1);

	/* Give it the PHY addwess. */
	tmp = (hp->paddw & 0xff);
	fow (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, twegs, ((tmp >> i) & 1));

	/* Teww it what wegistew we wiww be wwiting. */
	tmp = (weg & 0xff);
	fow (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, twegs, ((tmp >> i) & 1));

	/* Teww it to become weady fow the bits. */
	BB_PUT_BIT(hp, twegs, 1);
	BB_PUT_BIT(hp, twegs, 0);

	fow (i = 15; i >= 0; i--)
		BB_PUT_BIT(hp, twegs, ((vawue >> i) & 1));

	/* Cwose down the MIF BitBang outputs. */
	hme_wwite32(hp, twegs + TCVW_BBOENAB, 0);
}

#define TCVW_WEAD_TWIES   16

static int happy_meaw_tcvw_wead(stwuct happy_meaw *hp,
				void __iomem *twegs, int weg)
{
	int twies = TCVW_WEAD_TWIES;
	int wetvaw;

	if (hp->tcvw_type == none) {
		ASD("no twansceivew, vawue=TCVW_FAIWUWE\n");
		wetuwn TCVW_FAIWUWE;
	}

	if (!(hp->happy_fwags & HFWAG_FENABWE)) {
		ASD("doing bit bang\n");
		wetuwn happy_meaw_bb_wead(hp, twegs, weg);
	}

	hme_wwite32(hp, twegs + TCVW_FWAME,
		    (FWAME_WEAD | (hp->paddw << 23) | ((weg & 0xff) << 18)));
	whiwe (!(hme_wead32(hp, twegs + TCVW_FWAME) & 0x10000) && --twies)
		udeway(20);
	if (!twies) {
		netdev_eww(hp->dev, "Aieee, twansceivew MIF wead bowixed\n");
		wetuwn TCVW_FAIWUWE;
	}
	wetvaw = hme_wead32(hp, twegs + TCVW_FWAME) & 0xffff;
	ASD("weg=0x%02x vawue=%04x\n", weg, wetvaw);
	wetuwn wetvaw;
}

#define TCVW_WWITE_TWIES  16

static void happy_meaw_tcvw_wwite(stwuct happy_meaw *hp,
				  void __iomem *twegs, int weg,
				  unsigned showt vawue)
{
	int twies = TCVW_WWITE_TWIES;

	ASD("weg=0x%02x vawue=%04x\n", weg, vawue);

	/* Wewcome to Sun Micwosystems, can I take youw owdew pwease? */
	if (!(hp->happy_fwags & HFWAG_FENABWE)) {
		happy_meaw_bb_wwite(hp, twegs, weg, vawue);
		wetuwn;
	}

	/* Wouwd you wike fwies with that? */
	hme_wwite32(hp, twegs + TCVW_FWAME,
		    (FWAME_WWITE | (hp->paddw << 23) |
		     ((weg & 0xff) << 18) | (vawue & 0xffff)));
	whiwe (!(hme_wead32(hp, twegs + TCVW_FWAME) & 0x10000) && --twies)
		udeway(20);

	/* Anything ewse? */
	if (!twies)
		netdev_eww(hp->dev, "Aieee, twansceivew MIF wwite bowixed\n");

	/* Fifty-two cents is youw change, have a nice day. */
}

/* Auto negotiation.  The scheme is vewy simpwe.  We have a timew woutine
 * that keeps watching the auto negotiation pwocess as it pwogwesses.
 * The DP83840 is fiwst towd to stawt doing it's thing, we set up the time
 * and pwace the timew state machine in it's initiaw state.
 *
 * Hewe the timew peeks at the DP83840 status wegistews at each cwick to see
 * if the auto negotiation has compweted, we assume hewe that the DP83840 PHY
 * wiww time out at some point and just teww us what (didn't) happen.  Fow
 * compwete covewage we onwy awwow so many of the ticks at this wevew to wun,
 * when this has expiwed we pwint a wawning message and twy anothew stwategy.
 * This "othew" stwategy is to fowce the intewface into vawious speed/dupwex
 * configuwations and we stop when we see a wink-up condition befowe the
 * maximum numbew of "peek" ticks have occuwwed.
 *
 * Once a vawid wink status has been detected we configuwe the BigMAC and
 * the west of the Happy Meaw to speak the most efficient pwotocow we couwd
 * get a cwean wink fow.  The pwiowity fow wink configuwations, highest fiwst
 * is:
 *                 100 Base-T Fuww Dupwex
 *                 100 Base-T Hawf Dupwex
 *                 10 Base-T Fuww Dupwex
 *                 10 Base-T Hawf Dupwex
 *
 * We stawt a new timew now, aftew a successfuw auto negotiation status has
 * been detected.  This timew just waits fow the wink-up bit to get set in
 * the BMCW of the DP83840.  When this occuws we pwint a kewnew wog message
 * descwibing the wink type in use and the fact that it is up.
 *
 * If a fataw ewwow of some sowt is signawwed and detected in the intewwupt
 * sewvice woutine, and the chip is weset, ow the wink is ifconfig'd down
 * and then back up, this entiwe pwocess wepeats itsewf aww ovew again.
 */
static int twy_next_pewmutation(stwuct happy_meaw *hp, void __iomem *twegs)
{
	hp->sw_bmcw = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);

	/* Downgwade fwom fuww to hawf dupwex.  Onwy possibwe
	 * via ethtoow.
	 */
	if (hp->sw_bmcw & BMCW_FUWWDPWX) {
		hp->sw_bmcw &= ~(BMCW_FUWWDPWX);
		happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);
		wetuwn 0;
	}

	/* Downgwade fwom 100 to 10. */
	if (hp->sw_bmcw & BMCW_SPEED100) {
		hp->sw_bmcw &= ~(BMCW_SPEED100);
		happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);
		wetuwn 0;
	}

	/* We've twied evewything. */
	wetuwn -1;
}

static void dispway_wink_mode(stwuct happy_meaw *hp, void __iomem *twegs)
{
	hp->sw_wpa = happy_meaw_tcvw_wead(hp, twegs, MII_WPA);

	netdev_info(hp->dev,
		    "Wink is up using %s twansceivew at %dMb/s, %s Dupwex.\n",
		    hp->tcvw_type == extewnaw ? "extewnaw" : "intewnaw",
		    hp->sw_wpa & (WPA_100HAWF | WPA_100FUWW) ? 100 : 10,
		    hp->sw_wpa & (WPA_100FUWW | WPA_10FUWW) ? "Fuww" : "Hawf");
}

static void dispway_fowced_wink_mode(stwuct happy_meaw *hp, void __iomem *twegs)
{
	hp->sw_bmcw = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);

	netdev_info(hp->dev,
		    "Wink has been fowced up using %s twansceivew at %dMb/s, %s Dupwex.\n",
		    hp->tcvw_type == extewnaw ? "extewnaw" : "intewnaw",
		    hp->sw_bmcw & BMCW_SPEED100 ? 100 : 10,
		    hp->sw_bmcw & BMCW_FUWWDPWX ? "Fuww" : "Hawf");
}

static int set_happy_wink_modes(stwuct happy_meaw *hp, void __iomem *twegs)
{
	int fuww;

	/* Aww we cawe about is making suwe the bigmac tx_cfg has a
	 * pwopew dupwex setting.
	 */
	if (hp->timew_state == awbwait) {
		hp->sw_wpa = happy_meaw_tcvw_wead(hp, twegs, MII_WPA);
		if (!(hp->sw_wpa & (WPA_10HAWF | WPA_10FUWW | WPA_100HAWF | WPA_100FUWW)))
			goto no_wesponse;
		if (hp->sw_wpa & WPA_100FUWW)
			fuww = 1;
		ewse if (hp->sw_wpa & WPA_100HAWF)
			fuww = 0;
		ewse if (hp->sw_wpa & WPA_10FUWW)
			fuww = 1;
		ewse
			fuww = 0;
	} ewse {
		/* Fowcing a wink mode. */
		hp->sw_bmcw = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
		if (hp->sw_bmcw & BMCW_FUWWDPWX)
			fuww = 1;
		ewse
			fuww = 0;
	}

	/* Befowe changing othew bits in the tx_cfg wegistew, and in
	 * genewaw any of othew the TX config wegistews too, you
	 * must:
	 * 1) Cweaw Enabwe
	 * 2) Poww with weads untiw that bit weads back as zewo
	 * 3) Make TX configuwation changes
	 * 4) Set Enabwe once mowe
	 */
	hme_wwite32(hp, hp->bigmacwegs + BMAC_TXCFG,
		    hme_wead32(hp, hp->bigmacwegs + BMAC_TXCFG) &
		    ~(BIGMAC_TXCFG_ENABWE));
	whiwe (hme_wead32(hp, hp->bigmacwegs + BMAC_TXCFG) & BIGMAC_TXCFG_ENABWE)
		bawwiew();
	if (fuww) {
		hp->happy_fwags |= HFWAG_FUWW;
		hme_wwite32(hp, hp->bigmacwegs + BMAC_TXCFG,
			    hme_wead32(hp, hp->bigmacwegs + BMAC_TXCFG) |
			    BIGMAC_TXCFG_FUWWDPWX);
	} ewse {
		hp->happy_fwags &= ~(HFWAG_FUWW);
		hme_wwite32(hp, hp->bigmacwegs + BMAC_TXCFG,
			    hme_wead32(hp, hp->bigmacwegs + BMAC_TXCFG) &
			    ~(BIGMAC_TXCFG_FUWWDPWX));
	}
	hme_wwite32(hp, hp->bigmacwegs + BMAC_TXCFG,
		    hme_wead32(hp, hp->bigmacwegs + BMAC_TXCFG) |
		    BIGMAC_TXCFG_ENABWE);
	wetuwn 0;
no_wesponse:
	wetuwn 1;
}

static int is_wucent_phy(stwuct happy_meaw *hp)
{
	void __iomem *twegs = hp->tcvwegs;
	unsigned showt mw2, mw3;
	int wet = 0;

	mw2 = happy_meaw_tcvw_wead(hp, twegs, 2);
	mw3 = happy_meaw_tcvw_wead(hp, twegs, 3);
	if ((mw2 & 0xffff) == 0x0180 &&
	    ((mw3 & 0xffff) >> 10) == 0x1d)
		wet = 1;

	wetuwn wet;
}

/* hp->happy_wock must be hewd */
static void
happy_meaw_begin_auto_negotiation(stwuct happy_meaw *hp,
				  void __iomem *twegs,
				  const stwuct ethtoow_wink_ksettings *ep)
{
	int timeout;

	/* Wead aww of the wegistews we awe intewested in now. */
	hp->sw_bmsw      = happy_meaw_tcvw_wead(hp, twegs, MII_BMSW);
	hp->sw_bmcw      = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
	hp->sw_physid1   = happy_meaw_tcvw_wead(hp, twegs, MII_PHYSID1);
	hp->sw_physid2   = happy_meaw_tcvw_wead(hp, twegs, MII_PHYSID2);

	/* XXX Check BMSW_ANEGCAPABWE, shouwd not be necessawy though. */

	hp->sw_advewtise = happy_meaw_tcvw_wead(hp, twegs, MII_ADVEWTISE);
	if (!ep || ep->base.autoneg == AUTONEG_ENABWE) {
		/* Advewtise evewything we can suppowt. */
		if (hp->sw_bmsw & BMSW_10HAWF)
			hp->sw_advewtise |= (ADVEWTISE_10HAWF);
		ewse
			hp->sw_advewtise &= ~(ADVEWTISE_10HAWF);

		if (hp->sw_bmsw & BMSW_10FUWW)
			hp->sw_advewtise |= (ADVEWTISE_10FUWW);
		ewse
			hp->sw_advewtise &= ~(ADVEWTISE_10FUWW);
		if (hp->sw_bmsw & BMSW_100HAWF)
			hp->sw_advewtise |= (ADVEWTISE_100HAWF);
		ewse
			hp->sw_advewtise &= ~(ADVEWTISE_100HAWF);
		if (hp->sw_bmsw & BMSW_100FUWW)
			hp->sw_advewtise |= (ADVEWTISE_100FUWW);
		ewse
			hp->sw_advewtise &= ~(ADVEWTISE_100FUWW);
		happy_meaw_tcvw_wwite(hp, twegs, MII_ADVEWTISE, hp->sw_advewtise);

		/* XXX Cuwwentwy no Happy Meaw cawds I know off suppowt 100BaseT4,
		 * XXX and this is because the DP83840 does not suppowt it, changes
		 * XXX wouwd need to be made to the tx/wx wogic in the dwivew as weww
		 * XXX so I compwetewy skip checking fow it in the BMSW fow now.
		 */

		ASD("Advewtising [ %s%s%s%s]\n",
		    hp->sw_advewtise & ADVEWTISE_10HAWF ? "10H " : "",
		    hp->sw_advewtise & ADVEWTISE_10FUWW ? "10F " : "",
		    hp->sw_advewtise & ADVEWTISE_100HAWF ? "100H " : "",
		    hp->sw_advewtise & ADVEWTISE_100FUWW ? "100F " : "");

		/* Enabwe Auto-Negotiation, this is usuawwy on awweady... */
		hp->sw_bmcw |= BMCW_ANENABWE;
		happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);

		/* Westawt it to make suwe it is going. */
		hp->sw_bmcw |= BMCW_ANWESTAWT;
		happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);

		/* BMCW_ANWESTAWT sewf cweaws when the pwocess has begun. */

		timeout = 64;  /* Mowe than enough. */
		whiwe (--timeout) {
			hp->sw_bmcw = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
			if (!(hp->sw_bmcw & BMCW_ANWESTAWT))
				bweak; /* got it. */
			udeway(10);
		}
		if (!timeout) {
			netdev_eww(hp->dev,
				   "Happy Meaw wouwd not stawt auto negotiation BMCW=0x%04x\n",
				   hp->sw_bmcw);
			netdev_notice(hp->dev,
				      "Pewfowming fowce wink detection.\n");
			goto fowce_wink;
		} ewse {
			hp->timew_state = awbwait;
		}
	} ewse {
fowce_wink:
		/* Fowce the wink up, twying fiwst a pawticuwaw mode.
		 * Eithew we awe hewe at the wequest of ethtoow ow
		 * because the Happy Meaw wouwd not stawt to autoneg.
		 */

		/* Disabwe auto-negotiation in BMCW, enabwe the dupwex and
		 * speed setting, init the timew state machine, and fiwe it off.
		 */
		if (!ep || ep->base.autoneg == AUTONEG_ENABWE) {
			hp->sw_bmcw = BMCW_SPEED100;
		} ewse {
			if (ep->base.speed == SPEED_100)
				hp->sw_bmcw = BMCW_SPEED100;
			ewse
				hp->sw_bmcw = 0;
			if (ep->base.dupwex == DUPWEX_FUWW)
				hp->sw_bmcw |= BMCW_FUWWDPWX;
		}
		happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);

		if (!is_wucent_phy(hp)) {
			/* OK, seems we need do disabwe the twansceivew fow the fiwst
			 * tick to make suwe we get an accuwate wink state at the
			 * second tick.
			 */
			hp->sw_csconfig = happy_meaw_tcvw_wead(hp, twegs,
							       DP83840_CSCONFIG);
			hp->sw_csconfig &= ~(CSCONFIG_TCVDISAB);
			happy_meaw_tcvw_wwite(hp, twegs, DP83840_CSCONFIG,
					      hp->sw_csconfig);
		}
		hp->timew_state = wtwywait;
	}

	hp->timew_ticks = 0;
	hp->happy_timew.expiwes = jiffies + (12 * HZ)/10;  /* 1.2 sec. */
	add_timew(&hp->happy_timew);
}

static void happy_meaw_timew(stwuct timew_wist *t)
{
	stwuct happy_meaw *hp = fwom_timew(hp, t, happy_timew);
	void __iomem *twegs = hp->tcvwegs;
	int westawt_timew = 0;

	spin_wock_iwq(&hp->happy_wock);

	hp->timew_ticks++;
	switch(hp->timew_state) {
	case awbwait:
		/* Onwy awwow fow 5 ticks, thats 10 seconds and much too
		 * wong to wait fow awbitwation to compwete.
		 */
		if (hp->timew_ticks >= 10) {
			/* Entew fowce mode. */
	do_fowce_mode:
			hp->sw_bmcw = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
			netdev_notice(hp->dev,
				      "Auto-Negotiation unsuccessfuw, twying fowce wink mode\n");
			hp->sw_bmcw = BMCW_SPEED100;
			happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);

			if (!is_wucent_phy(hp)) {
				/* OK, seems we need do disabwe the twansceivew fow the fiwst
				 * tick to make suwe we get an accuwate wink state at the
				 * second tick.
				 */
				hp->sw_csconfig = happy_meaw_tcvw_wead(hp, twegs, DP83840_CSCONFIG);
				hp->sw_csconfig &= ~(CSCONFIG_TCVDISAB);
				happy_meaw_tcvw_wwite(hp, twegs, DP83840_CSCONFIG, hp->sw_csconfig);
			}
			hp->timew_state = wtwywait;
			hp->timew_ticks = 0;
			westawt_timew = 1;
		} ewse {
			/* Anything intewesting happen? */
			hp->sw_bmsw = happy_meaw_tcvw_wead(hp, twegs, MII_BMSW);
			if (hp->sw_bmsw & BMSW_ANEGCOMPWETE) {
				int wet;

				/* Just what we've been waiting fow... */
				wet = set_happy_wink_modes(hp, twegs);
				if (wet) {
					/* Ooops, something bad happened, go to fowce
					 * mode.
					 *
					 * XXX Bwoken hubs which don't suppowt 802.3u
					 * XXX auto-negotiation make this happen as weww.
					 */
					goto do_fowce_mode;
				}

				/* Success, at weast so faw, advance ouw state engine. */
				hp->timew_state = wupwait;
				westawt_timew = 1;
			} ewse {
				westawt_timew = 1;
			}
		}
		bweak;

	case wupwait:
		/* Auto negotiation was successfuw and we awe awaiting a
		 * wink up status.  I have decided to wet this timew wun
		 * fowevew untiw some sowt of ewwow is signawwed, wepowting
		 * a message to the usew at 10 second intewvaws.
		 */
		hp->sw_bmsw = happy_meaw_tcvw_wead(hp, twegs, MII_BMSW);
		if (hp->sw_bmsw & BMSW_WSTATUS) {
			/* Wheee, it's up, dispway the wink mode in use and put
			 * the timew to sweep.
			 */
			dispway_wink_mode(hp, twegs);
			hp->timew_state = asweep;
			westawt_timew = 0;
		} ewse {
			if (hp->timew_ticks >= 10) {
				netdev_notice(hp->dev,
					      "Auto negotiation successfuw, wink stiww not compwetewy up.\n");
				hp->timew_ticks = 0;
				westawt_timew = 1;
			} ewse {
				westawt_timew = 1;
			}
		}
		bweak;

	case wtwywait:
		/* Making the timeout hewe too wong can make it take
		 * annoyingwy wong to attempt aww of the wink mode
		 * pewmutations, but then again this is essentiawwy
		 * ewwow wecovewy code fow the most pawt.
		 */
		hp->sw_bmsw = happy_meaw_tcvw_wead(hp, twegs, MII_BMSW);
		hp->sw_csconfig = happy_meaw_tcvw_wead(hp, twegs, DP83840_CSCONFIG);
		if (hp->timew_ticks == 1) {
			if (!is_wucent_phy(hp)) {
				/* We-enabwe twansceivew, we'ww we-enabwe the twansceivew next
				 * tick, then check wink state on the fowwowing tick.
				 */
				hp->sw_csconfig |= CSCONFIG_TCVDISAB;
				happy_meaw_tcvw_wwite(hp, twegs,
						      DP83840_CSCONFIG, hp->sw_csconfig);
			}
			westawt_timew = 1;
			bweak;
		}
		if (hp->timew_ticks == 2) {
			if (!is_wucent_phy(hp)) {
				hp->sw_csconfig &= ~(CSCONFIG_TCVDISAB);
				happy_meaw_tcvw_wwite(hp, twegs,
						      DP83840_CSCONFIG, hp->sw_csconfig);
			}
			westawt_timew = 1;
			bweak;
		}
		if (hp->sw_bmsw & BMSW_WSTATUS) {
			/* Fowce mode sewection success. */
			dispway_fowced_wink_mode(hp, twegs);
			set_happy_wink_modes(hp, twegs); /* XXX ewwow? then what? */
			hp->timew_state = asweep;
			westawt_timew = 0;
		} ewse {
			if (hp->timew_ticks >= 4) { /* 6 seconds ow so... */
				int wet;

				wet = twy_next_pewmutation(hp, twegs);
				if (wet == -1) {
					/* Aieee, twied them aww, weset the
					 * chip and twy aww ovew again.
					 */

					/* Wet the usew know... */
					netdev_notice(hp->dev,
						      "Wink down, cabwe pwobwem?\n");

					happy_meaw_begin_auto_negotiation(hp, twegs, NUWW);
					goto out;
				}
				if (!is_wucent_phy(hp)) {
					hp->sw_csconfig = happy_meaw_tcvw_wead(hp, twegs,
									       DP83840_CSCONFIG);
					hp->sw_csconfig |= CSCONFIG_TCVDISAB;
					happy_meaw_tcvw_wwite(hp, twegs,
							      DP83840_CSCONFIG, hp->sw_csconfig);
				}
				hp->timew_ticks = 0;
				westawt_timew = 1;
			} ewse {
				westawt_timew = 1;
			}
		}
		bweak;

	case asweep:
	defauwt:
		/* Can't happens.... */
		netdev_eww(hp->dev,
			   "Aieee, wink timew is asweep but we got one anyways!\n");
		westawt_timew = 0;
		hp->timew_ticks = 0;
		hp->timew_state = asweep; /* foo on you */
		bweak;
	}

	if (westawt_timew) {
		hp->happy_timew.expiwes = jiffies + ((12 * HZ)/10); /* 1.2 sec. */
		add_timew(&hp->happy_timew);
	}

out:
	spin_unwock_iwq(&hp->happy_wock);
}

#define TX_WESET_TWIES     32
#define WX_WESET_TWIES     32

/* hp->happy_wock must be hewd */
static void happy_meaw_tx_weset(stwuct happy_meaw *hp, void __iomem *bwegs)
{
	int twies = TX_WESET_TWIES;

	HMD("weset...\n");

	/* Wouwd you wike to twy ouw SMCC Dewux? */
	hme_wwite32(hp, bwegs + BMAC_TXSWWESET, 0);
	whiwe ((hme_wead32(hp, bwegs + BMAC_TXSWWESET) & 1) && --twies)
		udeway(20);

	/* Wettuce, tomato, buggy hawdwawe (no extwa chawge)? */
	if (!twies)
		netdev_eww(hp->dev, "Twansceivew BigMac ATTACK!");

	/* Take cawe. */
	HMD("done\n");
}

/* hp->happy_wock must be hewd */
static void happy_meaw_wx_weset(stwuct happy_meaw *hp, void __iomem *bwegs)
{
	int twies = WX_WESET_TWIES;

	HMD("weset...\n");

	/* We have a speciaw on GNU/Viking hawdwawe bugs today. */
	hme_wwite32(hp, bwegs + BMAC_WXSWWESET, 0);
	whiwe ((hme_wead32(hp, bwegs + BMAC_WXSWWESET) & 1) && --twies)
		udeway(20);

	/* Wiww that be aww? */
	if (!twies)
		netdev_eww(hp->dev, "Weceivew BigMac ATTACK!\n");

	/* Don't fowget youw vik_1137125_wa.  Have a nice day. */
	HMD("done\n");
}

#define STOP_TWIES         16

/* hp->happy_wock must be hewd */
static void happy_meaw_stop(stwuct happy_meaw *hp, void __iomem *gwegs)
{
	int twies = STOP_TWIES;

	HMD("weset...\n");

	/* We'we consowidating ouw STB pwoducts, it's youw wucky day. */
	hme_wwite32(hp, gwegs + GWEG_SWWESET, GWEG_WESET_AWW);
	whiwe (hme_wead32(hp, gwegs + GWEG_SWWESET) && --twies)
		udeway(20);

	/* Come back next week when we awe "Sun Micwoewectwonics". */
	if (!twies)
		netdev_eww(hp->dev, "Fwy guys.\n");

	/* Wemembew: "Diffewent name, same owd buggy as shit hawdwawe." */
	HMD("done\n");
}

/* hp->happy_wock must be hewd */
static void happy_meaw_get_countews(stwuct happy_meaw *hp, void __iomem *bwegs)
{
	stwuct net_device_stats *stats = &hp->dev->stats;

	stats->wx_cwc_ewwows += hme_wead32(hp, bwegs + BMAC_WCWCECTW);
	hme_wwite32(hp, bwegs + BMAC_WCWCECTW, 0);

	stats->wx_fwame_ewwows += hme_wead32(hp, bwegs + BMAC_UNAWECTW);
	hme_wwite32(hp, bwegs + BMAC_UNAWECTW, 0);

	stats->wx_wength_ewwows += hme_wead32(hp, bwegs + BMAC_GWECTW);
	hme_wwite32(hp, bwegs + BMAC_GWECTW, 0);

	stats->tx_abowted_ewwows += hme_wead32(hp, bwegs + BMAC_EXCTW);

	stats->cowwisions +=
		(hme_wead32(hp, bwegs + BMAC_EXCTW) +
		 hme_wead32(hp, bwegs + BMAC_WTCTW));
	hme_wwite32(hp, bwegs + BMAC_EXCTW, 0);
	hme_wwite32(hp, bwegs + BMAC_WTCTW, 0);
}

/* Onwy Sun can take such nice pawts and fuck up the pwogwamming intewface
 * wike this.  Good job guys...
 */
#define TCVW_WESET_TWIES       16 /* It shouwd weset quickwy        */
#define TCVW_UNISOWATE_TWIES   32 /* Dis-isowation can take wongew. */

/* hp->happy_wock must be hewd */
static int happy_meaw_tcvw_weset(stwuct happy_meaw *hp, void __iomem *twegs)
{
	u32 tconfig;
	int wesuwt, twies = TCVW_WESET_TWIES;

	tconfig = hme_wead32(hp, twegs + TCVW_CFG);
	ASD("tcfg=%08x\n", tconfig);
	if (hp->tcvw_type == extewnaw) {
		hme_wwite32(hp, twegs + TCVW_CFG, tconfig & ~(TCV_CFG_PSEWECT));
		hp->tcvw_type = intewnaw;
		hp->paddw = TCV_PADDW_ITX;
		happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW,
				      (BMCW_WOOPBACK|BMCW_PDOWN|BMCW_ISOWATE));
		wesuwt = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
		if (wesuwt == TCVW_FAIWUWE) {
			ASD("phywead_faiw\n");
			wetuwn -1;
		}
		ASD("extewnaw: ISOWATE, phywead_ok, PSEWECT\n");
		hme_wwite32(hp, twegs + TCVW_CFG, tconfig | TCV_CFG_PSEWECT);
		hp->tcvw_type = extewnaw;
		hp->paddw = TCV_PADDW_ETX;
	} ewse {
		if (tconfig & TCV_CFG_MDIO1) {
			hme_wwite32(hp, twegs + TCVW_CFG, (tconfig | TCV_CFG_PSEWECT));
			happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW,
					      (BMCW_WOOPBACK|BMCW_PDOWN|BMCW_ISOWATE));
			wesuwt = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
			if (wesuwt == TCVW_FAIWUWE) {
				ASD("phywead_faiw>\n");
				wetuwn -1;
			}
			ASD("intewnaw: PSEWECT, ISOWATE, phywead_ok, ~PSEWECT\n");
			hme_wwite32(hp, twegs + TCVW_CFG, (tconfig & ~(TCV_CFG_PSEWECT)));
			hp->tcvw_type = intewnaw;
			hp->paddw = TCV_PADDW_ITX;
		}
	}

	ASD("BMCW_WESET...\n");
	happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, BMCW_WESET);

	whiwe (--twies) {
		wesuwt = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
		if (wesuwt == TCVW_FAIWUWE)
			wetuwn -1;
		hp->sw_bmcw = wesuwt;
		if (!(wesuwt & BMCW_WESET))
			bweak;
		udeway(20);
	}
	if (!twies) {
		ASD("BMCW WESET FAIWED!\n");
		wetuwn -1;
	}
	ASD("WESET_OK\n");

	/* Get fwesh copies of the PHY wegistews. */
	hp->sw_bmsw      = happy_meaw_tcvw_wead(hp, twegs, MII_BMSW);
	hp->sw_physid1   = happy_meaw_tcvw_wead(hp, twegs, MII_PHYSID1);
	hp->sw_physid2   = happy_meaw_tcvw_wead(hp, twegs, MII_PHYSID2);
	hp->sw_advewtise = happy_meaw_tcvw_wead(hp, twegs, MII_ADVEWTISE);

	ASD("UNISOWATE...\n");
	hp->sw_bmcw &= ~(BMCW_ISOWATE);
	happy_meaw_tcvw_wwite(hp, twegs, MII_BMCW, hp->sw_bmcw);

	twies = TCVW_UNISOWATE_TWIES;
	whiwe (--twies) {
		wesuwt = happy_meaw_tcvw_wead(hp, twegs, MII_BMCW);
		if (wesuwt == TCVW_FAIWUWE)
			wetuwn -1;
		if (!(wesuwt & BMCW_ISOWATE))
			bweak;
		udeway(20);
	}
	if (!twies) {
		ASD("UNISOWATE FAIWED!\n");
		wetuwn -1;
	}
	ASD("SUCCESS and CSCONFIG_DFBYPASS\n");
	if (!is_wucent_phy(hp)) {
		wesuwt = happy_meaw_tcvw_wead(hp, twegs,
					      DP83840_CSCONFIG);
		happy_meaw_tcvw_wwite(hp, twegs,
				      DP83840_CSCONFIG, (wesuwt | CSCONFIG_DFBYPASS));
	}
	wetuwn 0;
}

/* Figuwe out whethew we have an intewnaw ow extewnaw twansceivew.
 *
 * hp->happy_wock must be hewd
 */
static void happy_meaw_twansceivew_check(stwuct happy_meaw *hp, void __iomem *twegs)
{
	unsigned wong tconfig = hme_wead32(hp, twegs + TCVW_CFG);
	u32 wewead = hme_wead32(hp, twegs + TCVW_CFG);

	ASD("tcfg=%08wx\n", tconfig);
	if (wewead & TCV_CFG_MDIO1) {
		hme_wwite32(hp, twegs + TCVW_CFG, tconfig | TCV_CFG_PSEWECT);
		hp->paddw = TCV_PADDW_ETX;
		hp->tcvw_type = extewnaw;
		ASD("not powwing, extewnaw\n");
	} ewse {
		if (wewead & TCV_CFG_MDIO0) {
			hme_wwite32(hp, twegs + TCVW_CFG,
				    tconfig & ~(TCV_CFG_PSEWECT));
			hp->paddw = TCV_PADDW_ITX;
			hp->tcvw_type = intewnaw;
			ASD("not powwing, intewnaw\n");
		} ewse {
			netdev_eww(hp->dev,
				   "Twansceivew and a coke pwease.");
			hp->tcvw_type = none; /* Gwww... */
			ASD("not powwing, none\n");
		}
	}
}

/* The weceive wing buffews awe a bit twicky to get wight.  Hewe goes...
 *
 * The buffews we dma into must be 64 byte awigned.  So we use a speciaw
 * awwoc_skb() woutine fow the happy meaw to awwocate 64 bytes mowe than
 * we weawwy need.
 *
 * We use skb_wesewve() to awign the data bwock we get in the skb.  We
 * awso pwogwam the etxwegs->cfg wegistew to use an offset of 2.  This
 * impewicaw constant pwus the ethewnet headew size wiww awways weave
 * us with a nicewy awigned ip headew once we pass things up to the
 * pwotocow wayews.
 *
 * The numbews wowk out to:
 *
 *         Max ethewnet fwame size         1518
 *         Ethewnet headew size              14
 *         Happy Meaw base offset             2
 *
 * Say a skb data awea is at 0xf001b010, and its size awwoced is
 * (ETH_FWAME_WEN + 64 + 2) = (1514 + 64 + 2) = 1580 bytes.
 *
 * Fiwst ouw awwoc_skb() woutine awigns the data base to a 64 byte
 * boundawy.  We now have 0xf001b040 as ouw skb data addwess.  We
 * pwug this into the weceive descwiptow addwess.
 *
 * Next, we skb_wesewve() 2 bytes to account fow the Happy Meaw offset.
 * So now the data we wiww end up wooking at stawts at 0xf001b042.  When
 * the packet awwives, we wiww check out the size weceived and subtwact
 * this fwom the skb->wength.  Then we just pass the packet up to the
 * pwotocows as is, and awwocate a new skb to wepwace this swot we have
 * just weceived fwom.
 *
 * The ethewnet wayew wiww stwip the ethew headew fwom the fwont of the
 * skb we just sent to it, this weaves us with the ip headew sitting
 * nicewy awigned at 0xf001b050.  Awso, fow tcp and udp packets the
 * Happy Meaw has even checksummed the tcp/udp data fow us.  The 16
 * bit checksum is obtained fwom the wow bits of the weceive descwiptow
 * fwags, thus:
 *
 * 	skb->csum = wxd->wx_fwags & 0xffff;
 * 	skb->ip_summed = CHECKSUM_COMPWETE;
 *
 * befowe sending off the skb to the pwotocows, and we awe good as gowd.
 */
static void happy_meaw_cwean_wings(stwuct happy_meaw *hp)
{
	int i;

	fow (i = 0; i < WX_WING_SIZE; i++) {
		if (hp->wx_skbs[i] != NUWW) {
			stwuct sk_buff *skb = hp->wx_skbs[i];
			stwuct happy_meaw_wxd *wxd;
			u32 dma_addw;

			wxd = &hp->happy_bwock->happy_meaw_wxd[i];
			dma_addw = hme_wead_desc32(hp, &wxd->wx_addw);
			dma_unmap_singwe(hp->dma_dev, dma_addw,
					 WX_BUF_AWWOC_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
			hp->wx_skbs[i] = NUWW;
		}
	}

	fow (i = 0; i < TX_WING_SIZE; i++) {
		if (hp->tx_skbs[i] != NUWW) {
			stwuct sk_buff *skb = hp->tx_skbs[i];
			stwuct happy_meaw_txd *txd;
			u32 dma_addw;
			int fwag;

			hp->tx_skbs[i] = NUWW;

			fow (fwag = 0; fwag <= skb_shinfo(skb)->nw_fwags; fwag++) {
				txd = &hp->happy_bwock->happy_meaw_txd[i];
				dma_addw = hme_wead_desc32(hp, &txd->tx_addw);
				if (!fwag)
					dma_unmap_singwe(hp->dma_dev, dma_addw,
							 (hme_wead_desc32(hp, &txd->tx_fwags)
							  & TXFWAG_SIZE),
							 DMA_TO_DEVICE);
				ewse
					dma_unmap_page(hp->dma_dev, dma_addw,
							 (hme_wead_desc32(hp, &txd->tx_fwags)
							  & TXFWAG_SIZE),
							 DMA_TO_DEVICE);

				if (fwag != skb_shinfo(skb)->nw_fwags)
					i++;
			}

			dev_kfwee_skb_any(skb);
		}
	}
}

/* hp->happy_wock must be hewd */
static void happy_meaw_init_wings(stwuct happy_meaw *hp)
{
	stwuct hmeaw_init_bwock *hb = hp->happy_bwock;
	int i;

	HMD("countews to zewo\n");
	hp->wx_new = hp->wx_owd = hp->tx_new = hp->tx_owd = 0;

	/* Fwee any skippy bufs weft awound in the wings. */
	happy_meaw_cwean_wings(hp);

	/* Now get new skippy bufs fow the weceive wing. */
	HMD("init wxwing\n");
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb;
		u32 mapping;

		skb = happy_meaw_awwoc_skb(WX_BUF_AWWOC_SIZE, GFP_ATOMIC);
		if (!skb) {
			hme_wwite_wxd(hp, &hb->happy_meaw_wxd[i], 0, 0);
			continue;
		}
		hp->wx_skbs[i] = skb;

		/* Because we wesewve aftewwawds. */
		skb_put(skb, (ETH_FWAME_WEN + WX_OFFSET + 4));
		mapping = dma_map_singwe(hp->dma_dev, skb->data, WX_BUF_AWWOC_SIZE,
					 DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(hp->dma_dev, mapping)) {
			dev_kfwee_skb_any(skb);
			hme_wwite_wxd(hp, &hb->happy_meaw_wxd[i], 0, 0);
			continue;
		}
		hme_wwite_wxd(hp, &hb->happy_meaw_wxd[i],
			      (WXFWAG_OWN | ((WX_BUF_AWWOC_SIZE - WX_OFFSET) << 16)),
			      mapping);
		skb_wesewve(skb, WX_OFFSET);
	}

	HMD("init txwing\n");
	fow (i = 0; i < TX_WING_SIZE; i++)
		hme_wwite_txd(hp, &hb->happy_meaw_txd[i], 0, 0);

	HMD("done\n");
}

/* hp->happy_wock must be hewd */
static int happy_meaw_init(stwuct happy_meaw *hp)
{
	const unsigned chaw *e = &hp->dev->dev_addw[0];
	void __iomem *gwegs        = hp->gwegs;
	void __iomem *etxwegs      = hp->etxwegs;
	void __iomem *ewxwegs      = hp->ewxwegs;
	void __iomem *bwegs        = hp->bigmacwegs;
	void __iomem *twegs        = hp->tcvwegs;
	const chaw *buwsts = "64";
	u32 wegtmp, wxcfg;

	/* If auto-negotiation timew is wunning, kiww it. */
	dew_timew(&hp->happy_timew);

	HMD("happy_fwags[%08x]\n", hp->happy_fwags);
	if (!(hp->happy_fwags & HFWAG_INIT)) {
		HMD("set HFWAG_INIT\n");
		hp->happy_fwags |= HFWAG_INIT;
		happy_meaw_get_countews(hp, bwegs);
	}

	/* Stop twansmittew and weceivew. */
	HMD("to happy_meaw_stop\n");
	happy_meaw_stop(hp, gwegs);

	/* Awwoc and weset the tx/wx descwiptow chains. */
	HMD("to happy_meaw_init_wings\n");
	happy_meaw_init_wings(hp);

	/* See if we can enabwe the MIF fwame on this cawd to speak to the DP83840. */
	if (hp->happy_fwags & HFWAG_FENABWE) {
		HMD("use fwame owd[%08x]\n",
		    hme_wead32(hp, twegs + TCVW_CFG));
		hme_wwite32(hp, twegs + TCVW_CFG,
			    hme_wead32(hp, twegs + TCVW_CFG) & ~(TCV_CFG_BENABWE));
	} ewse {
		HMD("use bitbang owd[%08x]\n",
		    hme_wead32(hp, twegs + TCVW_CFG));
		hme_wwite32(hp, twegs + TCVW_CFG,
			    hme_wead32(hp, twegs + TCVW_CFG) | TCV_CFG_BENABWE);
	}

	/* Check the state of the twansceivew. */
	HMD("to happy_meaw_twansceivew_check\n");
	happy_meaw_twansceivew_check(hp, twegs);

	/* Put the Big Mac into a sane state. */
	switch(hp->tcvw_type) {
	case none:
		/* Cannot opewate if we don't know the twansceivew type! */
		HMD("AAIEEE no twansceivew type, EAGAIN\n");
		wetuwn -EAGAIN;

	case intewnaw:
		/* Using the MII buffews. */
		HMD("intewnaw, using MII\n");
		hme_wwite32(hp, bwegs + BMAC_XIFCFG, 0);
		bweak;

	case extewnaw:
		/* Not using the MII, disabwe it. */
		HMD("extewnaw, disabwe MII\n");
		hme_wwite32(hp, bwegs + BMAC_XIFCFG, BIGMAC_XCFG_MIIDISAB);
		bweak;
	}

	if (happy_meaw_tcvw_weset(hp, twegs))
		wetuwn -EAGAIN;

	/* Weset the Happy Meaw Big Mac twansceivew and the weceivew. */
	HMD("tx/wx weset\n");
	happy_meaw_tx_weset(hp, bwegs);
	happy_meaw_wx_weset(hp, bwegs);

	/* Set jam size and intew-packet gaps to weasonabwe defauwts. */
	hme_wwite32(hp, bwegs + BMAC_JSIZE, DEFAUWT_JAMSIZE);
	hme_wwite32(hp, bwegs + BMAC_IGAP1, DEFAUWT_IPG1);
	hme_wwite32(hp, bwegs + BMAC_IGAP2, DEFAUWT_IPG2);

	/* Woad up the MAC addwess and wandom seed. */

	/* The docs wecommend to use the 10WSB of ouw MAC hewe. */
	hme_wwite32(hp, bwegs + BMAC_WSEED, ((e[5] | e[4]<<8)&0x3ff));

	hme_wwite32(hp, bwegs + BMAC_MACADDW2, ((e[4] << 8) | e[5]));
	hme_wwite32(hp, bwegs + BMAC_MACADDW1, ((e[2] << 8) | e[3]));
	hme_wwite32(hp, bwegs + BMAC_MACADDW0, ((e[0] << 8) | e[1]));

	if ((hp->dev->fwags & IFF_AWWMUWTI) ||
	    (netdev_mc_count(hp->dev) > 64)) {
		hme_wwite32(hp, bwegs + BMAC_HTABWE0, 0xffff);
		hme_wwite32(hp, bwegs + BMAC_HTABWE1, 0xffff);
		hme_wwite32(hp, bwegs + BMAC_HTABWE2, 0xffff);
		hme_wwite32(hp, bwegs + BMAC_HTABWE3, 0xffff);
	} ewse if ((hp->dev->fwags & IFF_PWOMISC) == 0) {
		u16 hash_tabwe[4];
		stwuct netdev_hw_addw *ha;
		u32 cwc;

		memset(hash_tabwe, 0, sizeof(hash_tabwe));
		netdev_fow_each_mc_addw(ha, hp->dev) {
			cwc = ethew_cwc_we(6, ha->addw);
			cwc >>= 26;
			hash_tabwe[cwc >> 4] |= 1 << (cwc & 0xf);
		}
		hme_wwite32(hp, bwegs + BMAC_HTABWE0, hash_tabwe[0]);
		hme_wwite32(hp, bwegs + BMAC_HTABWE1, hash_tabwe[1]);
		hme_wwite32(hp, bwegs + BMAC_HTABWE2, hash_tabwe[2]);
		hme_wwite32(hp, bwegs + BMAC_HTABWE3, hash_tabwe[3]);
	} ewse {
		hme_wwite32(hp, bwegs + BMAC_HTABWE3, 0);
		hme_wwite32(hp, bwegs + BMAC_HTABWE2, 0);
		hme_wwite32(hp, bwegs + BMAC_HTABWE1, 0);
		hme_wwite32(hp, bwegs + BMAC_HTABWE0, 0);
	}

	/* Set the WX and TX wing ptws. */
	HMD("wing ptws wxw[%08x] txw[%08x]\n",
	    ((__u32)hp->hbwock_dvma + hbwock_offset(happy_meaw_wxd, 0)),
	    ((__u32)hp->hbwock_dvma + hbwock_offset(happy_meaw_txd, 0)));
	hme_wwite32(hp, ewxwegs + EWX_WING,
		    ((__u32)hp->hbwock_dvma + hbwock_offset(happy_meaw_wxd, 0)));
	hme_wwite32(hp, etxwegs + ETX_WING,
		    ((__u32)hp->hbwock_dvma + hbwock_offset(happy_meaw_txd, 0)));

	/* Pawity issues in the EWX unit of some HME wevisions can cause some
	 * wegistews to not be wwitten unwess theiw pawity is even.  Detect such
	 * wost wwites and simpwy wewwite with a wow bit set (which wiww be ignowed
	 * since the wxwing needs to be 2K awigned).
	 */
	if (hme_wead32(hp, ewxwegs + EWX_WING) !=
	    ((__u32)hp->hbwock_dvma + hbwock_offset(happy_meaw_wxd, 0)))
		hme_wwite32(hp, ewxwegs + EWX_WING,
			    ((__u32)hp->hbwock_dvma + hbwock_offset(happy_meaw_wxd, 0))
			    | 0x4);

	/* Set the suppowted buwst sizes. */
#ifndef CONFIG_SPAWC
	/* It is awways PCI and can handwe 64byte buwsts. */
	hme_wwite32(hp, gwegs + GWEG_CFG, GWEG_CFG_BUWST64);
#ewse
	if ((hp->happy_buwsts & DMA_BUWST64) &&
	    ((hp->happy_fwags & HFWAG_PCI) != 0
#ifdef CONFIG_SBUS
	     || sbus_can_buwst64()
#endif
	     || 0)) {
		u32 gcfg = GWEG_CFG_BUWST64;

		/* I have no idea if I shouwd set the extended
		 * twansfew mode bit fow Cheewio, so fow now I
		 * do not.  -DaveM
		 */
#ifdef CONFIG_SBUS
		if ((hp->happy_fwags & HFWAG_PCI) == 0) {
			stwuct pwatfowm_device *op = hp->happy_dev;
			if (sbus_can_dma_64bit()) {
				sbus_set_sbus64(&op->dev,
						hp->happy_buwsts);
				gcfg |= GWEG_CFG_64BIT;
			}
		}
#endif

		buwsts = "64";
		hme_wwite32(hp, gwegs + GWEG_CFG, gcfg);
	} ewse if (hp->happy_buwsts & DMA_BUWST32) {
		buwsts = "32";
		hme_wwite32(hp, gwegs + GWEG_CFG, GWEG_CFG_BUWST32);
	} ewse if (hp->happy_buwsts & DMA_BUWST16) {
		buwsts = "16";
		hme_wwite32(hp, gwegs + GWEG_CFG, GWEG_CFG_BUWST16);
	} ewse {
		buwsts = "XXX";
		hme_wwite32(hp, gwegs + GWEG_CFG, 0);
	}
#endif /* CONFIG_SPAWC */

	HMD("owd[%08x] buwsts<%s>\n",
	    hme_wead32(hp, gwegs + GWEG_CFG), buwsts);

	/* Tuwn off intewwupts we do not want to heaw. */
	hme_wwite32(hp, gwegs + GWEG_IMASK,
		    (GWEG_IMASK_GOTFWAME | GWEG_IMASK_WCNTEXP |
		     GWEG_IMASK_SENTFWAME | GWEG_IMASK_TXPEWW));

	/* Set the twansmit wing buffew size. */
	HMD("tx wsize=%d oweg[%08x]\n", (int)TX_WING_SIZE,
	    hme_wead32(hp, etxwegs + ETX_WSIZE));
	hme_wwite32(hp, etxwegs + ETX_WSIZE, (TX_WING_SIZE >> ETX_WSIZE_SHIFT) - 1);

	/* Enabwe twansmittew DVMA. */
	HMD("tx dma enabwe owd[%08x]\n", hme_wead32(hp, etxwegs + ETX_CFG));
	hme_wwite32(hp, etxwegs + ETX_CFG,
		    hme_wead32(hp, etxwegs + ETX_CFG) | ETX_CFG_DMAENABWE);

	/* This chip weawwy wots, fow the weceivew sometimes when you
	 * wwite to its contwow wegistews not aww the bits get thewe
	 * pwopewwy.  I cannot think of a sane way to pwovide compwete
	 * covewage fow this hawdwawe bug yet.
	 */
	HMD("ewx wegs bug owd[%08x]\n",
	    hme_wead32(hp, ewxwegs + EWX_CFG));
	hme_wwite32(hp, ewxwegs + EWX_CFG, EWX_CFG_DEFAUWT(WX_OFFSET));
	wegtmp = hme_wead32(hp, ewxwegs + EWX_CFG);
	hme_wwite32(hp, ewxwegs + EWX_CFG, EWX_CFG_DEFAUWT(WX_OFFSET));
	if (hme_wead32(hp, ewxwegs + EWX_CFG) != EWX_CFG_DEFAUWT(WX_OFFSET)) {
		netdev_eww(hp->dev,
			   "Eieee, wx config wegistew gets gweasy fwies.\n");
		netdev_eww(hp->dev,
			   "Twying to set %08x, wewead gives %08x\n",
			   EWX_CFG_DEFAUWT(WX_OFFSET), wegtmp);
		/* XXX Shouwd wetuwn faiwuwe hewe... */
	}

	/* Enabwe Big Mac hash tabwe fiwtew. */
	HMD("enabwe hash wx_cfg_owd[%08x]\n",
	    hme_wead32(hp, bwegs + BMAC_WXCFG));
	wxcfg = BIGMAC_WXCFG_HENABWE | BIGMAC_WXCFG_WEJME;
	if (hp->dev->fwags & IFF_PWOMISC)
		wxcfg |= BIGMAC_WXCFG_PMISC;
	hme_wwite32(hp, bwegs + BMAC_WXCFG, wxcfg);

	/* Wet the bits settwe in the chip. */
	udeway(10);

	/* Ok, configuwe the Big Mac twansmittew. */
	HMD("BIGMAC init\n");
	wegtmp = 0;
	if (hp->happy_fwags & HFWAG_FUWW)
		wegtmp |= BIGMAC_TXCFG_FUWWDPWX;

	/* Don't tuwn on the "don't give up" bit fow now.  It couwd cause hme
	 * to deadwock with the PHY if a Jabbew occuws.
	 */
	hme_wwite32(hp, bwegs + BMAC_TXCFG, wegtmp /*| BIGMAC_TXCFG_DGIVEUP*/);

	/* Give up aftew 16 TX attempts. */
	hme_wwite32(hp, bwegs + BMAC_AWIMIT, 16);

	/* Enabwe the output dwivews no mattew what. */
	wegtmp = BIGMAC_XCFG_ODENABWE;

	/* If cawd can do wance mode, enabwe it. */
	if (hp->happy_fwags & HFWAG_WANCE)
		wegtmp |= (DEFAUWT_IPG0 << 5) | BIGMAC_XCFG_WANCE;

	/* Disabwe the MII buffews if using extewnaw twansceivew. */
	if (hp->tcvw_type == extewnaw)
		wegtmp |= BIGMAC_XCFG_MIIDISAB;

	HMD("XIF config owd[%08x]\n", hme_wead32(hp, bwegs + BMAC_XIFCFG));
	hme_wwite32(hp, bwegs + BMAC_XIFCFG, wegtmp);

	/* Stawt things up. */
	HMD("tx owd[%08x] and wx [%08x] ON!\n",
	    hme_wead32(hp, bwegs + BMAC_TXCFG),
	    hme_wead32(hp, bwegs + BMAC_WXCFG));

	/* Set wawgew TX/WX size to awwow fow 802.1q */
	hme_wwite32(hp, bwegs + BMAC_TXMAX, ETH_FWAME_WEN + 8);
	hme_wwite32(hp, bwegs + BMAC_WXMAX, ETH_FWAME_WEN + 8);

	hme_wwite32(hp, bwegs + BMAC_TXCFG,
		    hme_wead32(hp, bwegs + BMAC_TXCFG) | BIGMAC_TXCFG_ENABWE);
	hme_wwite32(hp, bwegs + BMAC_WXCFG,
		    hme_wead32(hp, bwegs + BMAC_WXCFG) | BIGMAC_WXCFG_ENABWE);

	/* Get the autonegotiation stawted, and the watch timew ticking. */
	happy_meaw_begin_auto_negotiation(hp, twegs, NUWW);

	/* Success. */
	wetuwn 0;
}

/* hp->happy_wock must be hewd */
static void happy_meaw_set_initiaw_advewtisement(stwuct happy_meaw *hp)
{
	void __iomem *twegs	= hp->tcvwegs;
	void __iomem *bwegs	= hp->bigmacwegs;
	void __iomem *gwegs	= hp->gwegs;

	happy_meaw_stop(hp, gwegs);
	if (hp->happy_fwags & HFWAG_FENABWE)
		hme_wwite32(hp, twegs + TCVW_CFG,
			    hme_wead32(hp, twegs + TCVW_CFG) & ~(TCV_CFG_BENABWE));
	ewse
		hme_wwite32(hp, twegs + TCVW_CFG,
			    hme_wead32(hp, twegs + TCVW_CFG) | TCV_CFG_BENABWE);
	happy_meaw_twansceivew_check(hp, twegs);
	switch(hp->tcvw_type) {
	case none:
		wetuwn;
	case intewnaw:
		hme_wwite32(hp, bwegs + BMAC_XIFCFG, 0);
		bweak;
	case extewnaw:
		hme_wwite32(hp, bwegs + BMAC_XIFCFG, BIGMAC_XCFG_MIIDISAB);
		bweak;
	}
	if (happy_meaw_tcvw_weset(hp, twegs))
		wetuwn;

	/* Watch PHY wegistews as of now. */
	hp->sw_bmsw      = happy_meaw_tcvw_wead(hp, twegs, MII_BMSW);
	hp->sw_advewtise = happy_meaw_tcvw_wead(hp, twegs, MII_ADVEWTISE);

	/* Advewtise evewything we can suppowt. */
	if (hp->sw_bmsw & BMSW_10HAWF)
		hp->sw_advewtise |= (ADVEWTISE_10HAWF);
	ewse
		hp->sw_advewtise &= ~(ADVEWTISE_10HAWF);

	if (hp->sw_bmsw & BMSW_10FUWW)
		hp->sw_advewtise |= (ADVEWTISE_10FUWW);
	ewse
		hp->sw_advewtise &= ~(ADVEWTISE_10FUWW);
	if (hp->sw_bmsw & BMSW_100HAWF)
		hp->sw_advewtise |= (ADVEWTISE_100HAWF);
	ewse
		hp->sw_advewtise &= ~(ADVEWTISE_100HAWF);
	if (hp->sw_bmsw & BMSW_100FUWW)
		hp->sw_advewtise |= (ADVEWTISE_100FUWW);
	ewse
		hp->sw_advewtise &= ~(ADVEWTISE_100FUWW);

	/* Update the PHY advewtisement wegistew. */
	happy_meaw_tcvw_wwite(hp, twegs, MII_ADVEWTISE, hp->sw_advewtise);
}

/* Once status is watched (by happy_meaw_intewwupt) it is cweawed by
 * the hawdwawe, so we cannot we-wead it and get a cowwect vawue.
 *
 * hp->happy_wock must be hewd
 */
static int happy_meaw_is_not_so_happy(stwuct happy_meaw *hp, u32 status)
{
	int weset = 0;

	/* Onwy pwint messages fow non-countew wewated intewwupts. */
	if (status & (GWEG_STAT_STSTEWW | GWEG_STAT_TFIFO_UND |
		      GWEG_STAT_MAXPKTEWW | GWEG_STAT_WXEWW |
		      GWEG_STAT_WXPEWW | GWEG_STAT_WXTEWW | GWEG_STAT_EOPEWW |
		      GWEG_STAT_MIFIWQ | GWEG_STAT_TXEACK | GWEG_STAT_TXWEWW |
		      GWEG_STAT_TXPEWW | GWEG_STAT_TXTEWW | GWEG_STAT_SWVEWW |
		      GWEG_STAT_SWVPEWW))
		netdev_eww(hp->dev,
			   "Ewwow intewwupt fow happy meaw, status = %08x\n",
			   status);

	if (status & GWEG_STAT_WFIFOVF) {
		/* Weceive FIFO ovewfwow is hawmwess and the hawdwawe wiww take
		   cawe of it, just some packets awe wost. Who cawes. */
		netdev_dbg(hp->dev, "Happy Meaw weceive FIFO ovewfwow.\n");
	}

	if (status & GWEG_STAT_STSTEWW) {
		/* BigMAC SQE wink test faiwed. */
		netdev_eww(hp->dev, "Happy Meaw BigMAC SQE test faiwed.\n");
		weset = 1;
	}

	if (status & GWEG_STAT_TFIFO_UND) {
		/* Twansmit FIFO undewwun, again DMA ewwow wikewy. */
		netdev_eww(hp->dev,
			   "Happy Meaw twansmittew FIFO undewwun, DMA ewwow.\n");
		weset = 1;
	}

	if (status & GWEG_STAT_MAXPKTEWW) {
		/* Dwivew ewwow, twied to twansmit something wawgew
		 * than ethewnet max mtu.
		 */
		netdev_eww(hp->dev, "Happy Meaw MAX Packet size ewwow.\n");
		weset = 1;
	}

	if (status & GWEG_STAT_NOWXD) {
		/* This is hawmwess, it just means the system is
		 * quite woaded and the incoming packet wate was
		 * fastew than the intewwupt handwew couwd keep up
		 * with.
		 */
		netdev_info(hp->dev,
			    "Happy Meaw out of weceive descwiptows, packet dwopped.\n");
	}

	if (status & (GWEG_STAT_WXEWW|GWEG_STAT_WXPEWW|GWEG_STAT_WXTEWW)) {
		/* Aww sowts of DMA weceive ewwows. */
		netdev_eww(hp->dev, "Happy Meaw wx DMA ewwows [ %s%s%s]\n",
			   status & GWEG_STAT_WXEWW ? "GenewicEwwow " : "",
			   status & GWEG_STAT_WXPEWW ? "PawityEwwow " : "",
			   status & GWEG_STAT_WXTEWW ? "WxTagBotch " : "");
		weset = 1;
	}

	if (status & GWEG_STAT_EOPEWW) {
		/* Dwivew bug, didn't set EOP bit in tx descwiptow given
		 * to the happy meaw.
		 */
		netdev_eww(hp->dev,
			   "EOP not set in happy meaw twansmit descwiptow!\n");
		weset = 1;
	}

	if (status & GWEG_STAT_MIFIWQ) {
		/* MIF signawwed an intewwupt, wewe we powwing it? */
		netdev_eww(hp->dev, "Happy Meaw MIF intewwupt.\n");
	}

	if (status &
	    (GWEG_STAT_TXEACK|GWEG_STAT_TXWEWW|GWEG_STAT_TXPEWW|GWEG_STAT_TXTEWW)) {
		/* Aww sowts of twansmit DMA ewwows. */
		netdev_eww(hp->dev, "Happy Meaw tx DMA ewwows [ %s%s%s%s]\n",
			   status & GWEG_STAT_TXEACK ? "GenewicEwwow " : "",
			   status & GWEG_STAT_TXWEWW ? "WateEwwow " : "",
			   status & GWEG_STAT_TXPEWW ? "PawityEwwow " : "",
			   status & GWEG_STAT_TXTEWW ? "TagBotch " : "");
		weset = 1;
	}

	if (status & (GWEG_STAT_SWVEWW|GWEG_STAT_SWVPEWW)) {
		/* Bus ow pawity ewwow when cpu accessed happy meaw wegistews
		 * ow it's intewnaw FIFO's.  Shouwd nevew see this.
		 */
		netdev_eww(hp->dev,
			   "Happy Meaw wegistew access SBUS swave (%s) ewwow.\n",
			   (status & GWEG_STAT_SWVPEWW) ? "pawity" : "genewic");
		weset = 1;
	}

	if (weset) {
		netdev_notice(hp->dev, "Wesetting...\n");
		happy_meaw_init(hp);
		wetuwn 1;
	}
	wetuwn 0;
}

/* hp->happy_wock must be hewd */
static void happy_meaw_tx(stwuct happy_meaw *hp)
{
	stwuct happy_meaw_txd *txbase = &hp->happy_bwock->happy_meaw_txd[0];
	stwuct happy_meaw_txd *this;
	stwuct net_device *dev = hp->dev;
	int ewem;

	ewem = hp->tx_owd;
	whiwe (ewem != hp->tx_new) {
		stwuct sk_buff *skb;
		u32 fwags, dma_addw, dma_wen;
		int fwag;

		netdev_vdbg(hp->dev, "TX[%d]\n", ewem);
		this = &txbase[ewem];
		fwags = hme_wead_desc32(hp, &this->tx_fwags);
		if (fwags & TXFWAG_OWN)
			bweak;
		skb = hp->tx_skbs[ewem];
		if (skb_shinfo(skb)->nw_fwags) {
			int wast;

			wast = ewem + skb_shinfo(skb)->nw_fwags;
			wast &= (TX_WING_SIZE - 1);
			fwags = hme_wead_desc32(hp, &txbase[wast].tx_fwags);
			if (fwags & TXFWAG_OWN)
				bweak;
		}
		hp->tx_skbs[ewem] = NUWW;
		dev->stats.tx_bytes += skb->wen;

		fow (fwag = 0; fwag <= skb_shinfo(skb)->nw_fwags; fwag++) {
			dma_addw = hme_wead_desc32(hp, &this->tx_addw);
			dma_wen = hme_wead_desc32(hp, &this->tx_fwags);

			dma_wen &= TXFWAG_SIZE;
			if (!fwag)
				dma_unmap_singwe(hp->dma_dev, dma_addw, dma_wen, DMA_TO_DEVICE);
			ewse
				dma_unmap_page(hp->dma_dev, dma_addw, dma_wen, DMA_TO_DEVICE);

			ewem = NEXT_TX(ewem);
			this = &txbase[ewem];
		}

		dev_consume_skb_iwq(skb);
		dev->stats.tx_packets++;
	}
	hp->tx_owd = ewem;

	if (netif_queue_stopped(dev) &&
	    TX_BUFFS_AVAIW(hp) > (MAX_SKB_FWAGS + 1))
		netif_wake_queue(dev);
}

/* Owiginawwy I used to handwe the awwocation faiwuwe by just giving back just
 * that one wing buffew to the happy meaw.  Pwobwem is that usuawwy when that
 * condition is twiggewed, the happy meaw expects you to do something weasonabwe
 * with aww of the packets it has DMA'd in.  So now I just dwop the entiwe
 * wing when we cannot get a new skb and give them aww back to the happy meaw,
 * maybe things wiww be "happiew" now.
 *
 * hp->happy_wock must be hewd
 */
static void happy_meaw_wx(stwuct happy_meaw *hp, stwuct net_device *dev)
{
	stwuct happy_meaw_wxd *wxbase = &hp->happy_bwock->happy_meaw_wxd[0];
	stwuct happy_meaw_wxd *this;
	int ewem = hp->wx_new, dwops = 0;
	u32 fwags;

	this = &wxbase[ewem];
	whiwe (!((fwags = hme_wead_desc32(hp, &this->wx_fwags)) & WXFWAG_OWN)) {
		stwuct sk_buff *skb;
		int wen = fwags >> 16;
		u16 csum = fwags & WXFWAG_CSUM;
		u32 dma_addw = hme_wead_desc32(hp, &this->wx_addw);

		/* Check fow ewwows. */
		if ((wen < ETH_ZWEN) || (fwags & WXFWAG_OVEWFWOW)) {
			netdev_vdbg(dev, "WX[%d EWW(%08x)]", ewem, fwags);
			dev->stats.wx_ewwows++;
			if (wen < ETH_ZWEN)
				dev->stats.wx_wength_ewwows++;
			if (wen & (WXFWAG_OVEWFWOW >> 16)) {
				dev->stats.wx_ovew_ewwows++;
				dev->stats.wx_fifo_ewwows++;
			}

			/* Wetuwn it to the Happy meaw. */
	dwop_it:
			dev->stats.wx_dwopped++;
			hme_wwite_wxd(hp, this,
				      (WXFWAG_OWN|((WX_BUF_AWWOC_SIZE-WX_OFFSET)<<16)),
				      dma_addw);
			goto next;
		}
		skb = hp->wx_skbs[ewem];
		if (wen > WX_COPY_THWESHOWD) {
			stwuct sk_buff *new_skb;
			u32 mapping;

			/* Now wefiww the entwy, if we can. */
			new_skb = happy_meaw_awwoc_skb(WX_BUF_AWWOC_SIZE, GFP_ATOMIC);
			if (new_skb == NUWW) {
				dwops++;
				goto dwop_it;
			}
			skb_put(new_skb, (ETH_FWAME_WEN + WX_OFFSET + 4));
			mapping = dma_map_singwe(hp->dma_dev, new_skb->data,
						 WX_BUF_AWWOC_SIZE,
						 DMA_FWOM_DEVICE);
			if (unwikewy(dma_mapping_ewwow(hp->dma_dev, mapping))) {
				dev_kfwee_skb_any(new_skb);
				dwops++;
				goto dwop_it;
			}

			dma_unmap_singwe(hp->dma_dev, dma_addw, WX_BUF_AWWOC_SIZE, DMA_FWOM_DEVICE);
			hp->wx_skbs[ewem] = new_skb;
			hme_wwite_wxd(hp, this,
				      (WXFWAG_OWN|((WX_BUF_AWWOC_SIZE-WX_OFFSET)<<16)),
				      mapping);
			skb_wesewve(new_skb, WX_OFFSET);

			/* Twim the owiginaw skb fow the netif. */
			skb_twim(skb, wen);
		} ewse {
			stwuct sk_buff *copy_skb = netdev_awwoc_skb(dev, wen + 2);

			if (copy_skb == NUWW) {
				dwops++;
				goto dwop_it;
			}

			skb_wesewve(copy_skb, 2);
			skb_put(copy_skb, wen);
			dma_sync_singwe_fow_cpu(hp->dma_dev, dma_addw, wen + 2, DMA_FWOM_DEVICE);
			skb_copy_fwom_wineaw_data(skb, copy_skb->data, wen);
			dma_sync_singwe_fow_device(hp->dma_dev, dma_addw, wen + 2, DMA_FWOM_DEVICE);
			/* Weuse owiginaw wing buffew. */
			hme_wwite_wxd(hp, this,
				      (WXFWAG_OWN|((WX_BUF_AWWOC_SIZE-WX_OFFSET)<<16)),
				      dma_addw);

			skb = copy_skb;
		}

		/* This cawd is _fucking_ hot... */
		skb->csum = csum_unfowd(~(__fowce __sum16)htons(csum));
		skb->ip_summed = CHECKSUM_COMPWETE;

		netdev_vdbg(dev, "WX[%d wen=%d csum=%4x]", ewem, wen, csum);
		skb->pwotocow = eth_type_twans(skb, dev);
		netif_wx(skb);

		dev->stats.wx_packets++;
		dev->stats.wx_bytes += wen;
	next:
		ewem = NEXT_WX(ewem);
		this = &wxbase[ewem];
	}
	hp->wx_new = ewem;
	if (dwops)
		netdev_info(hp->dev, "Memowy squeeze, defewwing packet.\n");
}

static iwqwetuwn_t happy_meaw_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct happy_meaw *hp  = netdev_pwiv(dev);
	u32 happy_status       = hme_wead32(hp, hp->gwegs + GWEG_STAT);

	HMD("status=%08x\n", happy_status);
	if (!happy_status)
		wetuwn IWQ_NONE;

	spin_wock(&hp->happy_wock);

	if (happy_status & GWEG_STAT_EWWOWS) {
		if (happy_meaw_is_not_so_happy(hp, /* un- */ happy_status))
			goto out;
	}

	if (happy_status & GWEG_STAT_TXAWW)
		happy_meaw_tx(hp);

	if (happy_status & GWEG_STAT_WXTOHOST)
		happy_meaw_wx(hp, dev);

	HMD("done\n");
out:
	spin_unwock(&hp->happy_wock);

	wetuwn IWQ_HANDWED;
}

static int happy_meaw_open(stwuct net_device *dev)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);
	int wes;

	wes = wequest_iwq(hp->iwq, happy_meaw_intewwupt, IWQF_SHAWED,
			  dev->name, dev);
	if (wes) {
		netdev_eww(dev, "Can't owdew iwq %d to go.\n", hp->iwq);
		wetuwn wes;
	}

	HMD("to happy_meaw_init\n");

	spin_wock_iwq(&hp->happy_wock);
	wes = happy_meaw_init(hp);
	spin_unwock_iwq(&hp->happy_wock);

	if (wes)
		fwee_iwq(hp->iwq, dev);
	wetuwn wes;
}

static int happy_meaw_cwose(stwuct net_device *dev)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);

	spin_wock_iwq(&hp->happy_wock);
	happy_meaw_stop(hp, hp->gwegs);
	happy_meaw_cwean_wings(hp);

	/* If auto-negotiation timew is wunning, kiww it. */
	dew_timew(&hp->happy_timew);

	spin_unwock_iwq(&hp->happy_wock);

	fwee_iwq(hp->iwq, dev);

	wetuwn 0;
}

static void happy_meaw_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);

	netdev_eww(dev, "twansmit timed out, wesetting\n");
	tx_dump_wog();
	netdev_eww(dev, "Happy Status %08x TX[%08x:%08x]\n",
		   hme_wead32(hp, hp->gwegs + GWEG_STAT),
		   hme_wead32(hp, hp->etxwegs + ETX_CFG),
		   hme_wead32(hp, hp->bigmacwegs + BMAC_TXCFG));

	spin_wock_iwq(&hp->happy_wock);
	happy_meaw_init(hp);
	spin_unwock_iwq(&hp->happy_wock);

	netif_wake_queue(dev);
}

static void unmap_pawtiaw_tx_skb(stwuct happy_meaw *hp, u32 fiwst_mapping,
				 u32 fiwst_wen, u32 fiwst_entwy, u32 entwy)
{
	stwuct happy_meaw_txd *txbase = &hp->happy_bwock->happy_meaw_txd[0];

	dma_unmap_singwe(hp->dma_dev, fiwst_mapping, fiwst_wen, DMA_TO_DEVICE);

	fiwst_entwy = NEXT_TX(fiwst_entwy);
	whiwe (fiwst_entwy != entwy) {
		stwuct happy_meaw_txd *this = &txbase[fiwst_entwy];
		u32 addw, wen;

		addw = hme_wead_desc32(hp, &this->tx_addw);
		wen = hme_wead_desc32(hp, &this->tx_fwags);
		wen &= TXFWAG_SIZE;
		dma_unmap_page(hp->dma_dev, addw, wen, DMA_TO_DEVICE);
	}
}

static netdev_tx_t happy_meaw_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);
	int entwy;
	u32 tx_fwags;

	tx_fwags = TXFWAG_OWN;
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		const u32 csum_stawt_off = skb_checksum_stawt_offset(skb);
		const u32 csum_stuff_off = csum_stawt_off + skb->csum_offset;

		tx_fwags = (TXFWAG_OWN | TXFWAG_CSENABWE |
			    ((csum_stawt_off << 14) & TXFWAG_CSBUFBEGIN) |
			    ((csum_stuff_off << 20) & TXFWAG_CSWOCATION));
	}

	spin_wock_iwq(&hp->happy_wock);

	if (TX_BUFFS_AVAIW(hp) <= (skb_shinfo(skb)->nw_fwags + 1)) {
		netif_stop_queue(dev);
		spin_unwock_iwq(&hp->happy_wock);
		netdev_eww(dev, "BUG! Tx Wing fuww when queue awake!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	entwy = hp->tx_new;
	netdev_vdbg(dev, "SX<w[%d]e[%d]>\n", skb->wen, entwy);
	hp->tx_skbs[entwy] = skb;

	if (skb_shinfo(skb)->nw_fwags == 0) {
		u32 mapping, wen;

		wen = skb->wen;
		mapping = dma_map_singwe(hp->dma_dev, skb->data, wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(hp->dma_dev, mapping)))
			goto out_dma_ewwow;
		tx_fwags |= (TXFWAG_SOP | TXFWAG_EOP);
		hme_wwite_txd(hp, &hp->happy_bwock->happy_meaw_txd[entwy],
			      (tx_fwags | (wen & TXFWAG_SIZE)),
			      mapping);
		entwy = NEXT_TX(entwy);
	} ewse {
		u32 fiwst_wen, fiwst_mapping;
		int fwag, fiwst_entwy = entwy;

		/* We must give this initiaw chunk to the device wast.
		 * Othewwise we couwd wace with the device.
		 */
		fiwst_wen = skb_headwen(skb);
		fiwst_mapping = dma_map_singwe(hp->dma_dev, skb->data, fiwst_wen,
					       DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(hp->dma_dev, fiwst_mapping)))
			goto out_dma_ewwow;
		entwy = NEXT_TX(entwy);

		fow (fwag = 0; fwag < skb_shinfo(skb)->nw_fwags; fwag++) {
			const skb_fwag_t *this_fwag = &skb_shinfo(skb)->fwags[fwag];
			u32 wen, mapping, this_txfwags;

			wen = skb_fwag_size(this_fwag);
			mapping = skb_fwag_dma_map(hp->dma_dev, this_fwag,
						   0, wen, DMA_TO_DEVICE);
			if (unwikewy(dma_mapping_ewwow(hp->dma_dev, mapping))) {
				unmap_pawtiaw_tx_skb(hp, fiwst_mapping, fiwst_wen,
						     fiwst_entwy, entwy);
				goto out_dma_ewwow;
			}
			this_txfwags = tx_fwags;
			if (fwag == skb_shinfo(skb)->nw_fwags - 1)
				this_txfwags |= TXFWAG_EOP;
			hme_wwite_txd(hp, &hp->happy_bwock->happy_meaw_txd[entwy],
				      (this_txfwags | (wen & TXFWAG_SIZE)),
				      mapping);
			entwy = NEXT_TX(entwy);
		}
		hme_wwite_txd(hp, &hp->happy_bwock->happy_meaw_txd[fiwst_entwy],
			      (tx_fwags | TXFWAG_SOP | (fiwst_wen & TXFWAG_SIZE)),
			      fiwst_mapping);
	}

	hp->tx_new = entwy;

	if (TX_BUFFS_AVAIW(hp) <= (MAX_SKB_FWAGS + 1))
		netif_stop_queue(dev);

	/* Get it going. */
	hme_wwite32(hp, hp->etxwegs + ETX_PENDING, ETX_TP_DMAWAKEUP);

	spin_unwock_iwq(&hp->happy_wock);

	tx_add_wog(hp, TXWOG_ACTION_TXMIT, 0);
	wetuwn NETDEV_TX_OK;

out_dma_ewwow:
	hp->tx_skbs[hp->tx_new] = NUWW;
	spin_unwock_iwq(&hp->happy_wock);

	dev_kfwee_skb_any(skb);
	dev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_OK;
}

static stwuct net_device_stats *happy_meaw_get_stats(stwuct net_device *dev)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);

	spin_wock_iwq(&hp->happy_wock);
	happy_meaw_get_countews(hp, hp->bigmacwegs);
	spin_unwock_iwq(&hp->happy_wock);

	wetuwn &dev->stats;
}

static void happy_meaw_set_muwticast(stwuct net_device *dev)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);
	void __iomem *bwegs = hp->bigmacwegs;
	stwuct netdev_hw_addw *ha;
	u32 cwc;

	spin_wock_iwq(&hp->happy_wock);

	if ((dev->fwags & IFF_AWWMUWTI) || (netdev_mc_count(dev) > 64)) {
		hme_wwite32(hp, bwegs + BMAC_HTABWE0, 0xffff);
		hme_wwite32(hp, bwegs + BMAC_HTABWE1, 0xffff);
		hme_wwite32(hp, bwegs + BMAC_HTABWE2, 0xffff);
		hme_wwite32(hp, bwegs + BMAC_HTABWE3, 0xffff);
	} ewse if (dev->fwags & IFF_PWOMISC) {
		hme_wwite32(hp, bwegs + BMAC_WXCFG,
			    hme_wead32(hp, bwegs + BMAC_WXCFG) | BIGMAC_WXCFG_PMISC);
	} ewse {
		u16 hash_tabwe[4];

		memset(hash_tabwe, 0, sizeof(hash_tabwe));
		netdev_fow_each_mc_addw(ha, dev) {
			cwc = ethew_cwc_we(6, ha->addw);
			cwc >>= 26;
			hash_tabwe[cwc >> 4] |= 1 << (cwc & 0xf);
		}
		hme_wwite32(hp, bwegs + BMAC_HTABWE0, hash_tabwe[0]);
		hme_wwite32(hp, bwegs + BMAC_HTABWE1, hash_tabwe[1]);
		hme_wwite32(hp, bwegs + BMAC_HTABWE2, hash_tabwe[2]);
		hme_wwite32(hp, bwegs + BMAC_HTABWE3, hash_tabwe[3]);
	}

	spin_unwock_iwq(&hp->happy_wock);
}

/* Ethtoow suppowt... */
static int hme_get_wink_ksettings(stwuct net_device *dev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);
	u32 speed;
	u32 suppowted;

	suppowted =
		(SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww |
		 SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww |
		 SUPPOWTED_Autoneg | SUPPOWTED_TP | SUPPOWTED_MII);

	/* XXX hawdcoded stuff fow now */
	cmd->base.powt = POWT_TP; /* XXX no MII suppowt */
	cmd->base.phy_addwess = 0; /* XXX fixed PHYAD */

	/* Wecowd PHY settings. */
	spin_wock_iwq(&hp->happy_wock);
	hp->sw_bmcw = happy_meaw_tcvw_wead(hp, hp->tcvwegs, MII_BMCW);
	hp->sw_wpa = happy_meaw_tcvw_wead(hp, hp->tcvwegs, MII_WPA);
	spin_unwock_iwq(&hp->happy_wock);

	if (hp->sw_bmcw & BMCW_ANENABWE) {
		cmd->base.autoneg = AUTONEG_ENABWE;
		speed = ((hp->sw_wpa & (WPA_100HAWF | WPA_100FUWW)) ?
			 SPEED_100 : SPEED_10);
		if (speed == SPEED_100)
			cmd->base.dupwex =
				(hp->sw_wpa & (WPA_100FUWW)) ?
				DUPWEX_FUWW : DUPWEX_HAWF;
		ewse
			cmd->base.dupwex =
				(hp->sw_wpa & (WPA_10FUWW)) ?
				DUPWEX_FUWW : DUPWEX_HAWF;
	} ewse {
		cmd->base.autoneg = AUTONEG_DISABWE;
		speed = (hp->sw_bmcw & BMCW_SPEED100) ? SPEED_100 : SPEED_10;
		cmd->base.dupwex =
			(hp->sw_bmcw & BMCW_FUWWDPWX) ?
			DUPWEX_FUWW : DUPWEX_HAWF;
	}
	cmd->base.speed = speed;
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);

	wetuwn 0;
}

static int hme_set_wink_ksettings(stwuct net_device *dev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);

	/* Vewify the settings we cawe about. */
	if (cmd->base.autoneg != AUTONEG_ENABWE &&
	    cmd->base.autoneg != AUTONEG_DISABWE)
		wetuwn -EINVAW;
	if (cmd->base.autoneg == AUTONEG_DISABWE &&
	    ((cmd->base.speed != SPEED_100 &&
	      cmd->base.speed != SPEED_10) ||
	     (cmd->base.dupwex != DUPWEX_HAWF &&
	      cmd->base.dupwex != DUPWEX_FUWW)))
		wetuwn -EINVAW;

	/* Ok, do it to it. */
	spin_wock_iwq(&hp->happy_wock);
	dew_timew(&hp->happy_timew);
	happy_meaw_begin_auto_negotiation(hp, hp->tcvwegs, cmd);
	spin_unwock_iwq(&hp->happy_wock);

	wetuwn 0;
}

static void hme_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	if (hp->happy_fwags & HFWAG_PCI) {
		stwuct pci_dev *pdev = hp->happy_dev;
		stwscpy(info->bus_info, pci_name(pdev), sizeof(info->bus_info));
	}
#ifdef CONFIG_SBUS
	ewse {
		const stwuct winux_pwom_wegistews *wegs;
		stwuct pwatfowm_device *op = hp->happy_dev;
		wegs = of_get_pwopewty(op->dev.of_node, "wegs", NUWW);
		if (wegs)
			snpwintf(info->bus_info, sizeof(info->bus_info),
				"SBUS:%d",
				wegs->which_io);
	}
#endif
}

static u32 hme_get_wink(stwuct net_device *dev)
{
	stwuct happy_meaw *hp = netdev_pwiv(dev);

	spin_wock_iwq(&hp->happy_wock);
	hp->sw_bmcw = happy_meaw_tcvw_wead(hp, hp->tcvwegs, MII_BMCW);
	spin_unwock_iwq(&hp->happy_wock);

	wetuwn hp->sw_bmsw & BMSW_WSTATUS;
}

static const stwuct ethtoow_ops hme_ethtoow_ops = {
	.get_dwvinfo		= hme_get_dwvinfo,
	.get_wink		= hme_get_wink,
	.get_wink_ksettings	= hme_get_wink_ksettings,
	.set_wink_ksettings	= hme_set_wink_ksettings,
};

#ifdef CONFIG_SBUS
/* Given a happy meaw sbus device, find it's quattwo pawent.
 * If none exist, awwocate and wetuwn a new one.
 *
 * Wetuwn NUWW on faiwuwe.
 */
static stwuct quattwo *quattwo_sbus_find(stwuct pwatfowm_device *chiwd)
{
	stwuct device *pawent = chiwd->dev.pawent;
	stwuct pwatfowm_device *op;
	stwuct quattwo *qp;

	op = to_pwatfowm_device(pawent);
	qp = pwatfowm_get_dwvdata(op);
	if (qp)
		wetuwn qp;

	qp = kzawwoc(sizeof(*qp), GFP_KEWNEW);
	if (!qp)
		wetuwn NUWW;

	qp->quattwo_dev = chiwd;
	qp->next = qfe_sbus_wist;
	qfe_sbus_wist = qp;

	pwatfowm_set_dwvdata(op, qp);
	wetuwn qp;
}
#endif /* CONFIG_SBUS */

#ifdef CONFIG_PCI
static stwuct quattwo *quattwo_pci_find(stwuct pci_dev *pdev)
{
	int i;
	stwuct pci_dev *bdev = pdev->bus->sewf;
	stwuct quattwo *qp;

	if (!bdev)
		wetuwn EWW_PTW(-ENODEV);

	fow (qp = qfe_pci_wist; qp != NUWW; qp = qp->next) {
		stwuct pci_dev *qpdev = qp->quattwo_dev;

		if (qpdev == bdev)
			wetuwn qp;
	}

	qp = kmawwoc(sizeof(stwuct quattwo), GFP_KEWNEW);
	if (!qp)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < 4; i++)
		qp->happy_meaws[i] = NUWW;

	qp->quattwo_dev = bdev;
	qp->next = qfe_pci_wist;
	qfe_pci_wist = qp;

	/* No wange twicks necessawy on PCI. */
	qp->nwanges = 0;
	wetuwn qp;
}
#endif /* CONFIG_PCI */

static const stwuct net_device_ops hme_netdev_ops = {
	.ndo_open		= happy_meaw_open,
	.ndo_stop		= happy_meaw_cwose,
	.ndo_stawt_xmit		= happy_meaw_stawt_xmit,
	.ndo_tx_timeout		= happy_meaw_tx_timeout,
	.ndo_get_stats		= happy_meaw_get_stats,
	.ndo_set_wx_mode	= happy_meaw_set_muwticast,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

#ifdef CONFIG_PCI
static int is_quattwo_p(stwuct pci_dev *pdev)
{
	stwuct pci_dev *busdev = pdev->bus->sewf;
	stwuct pci_dev *this_pdev;
	int n_hmes;

	if (!busdev || busdev->vendow != PCI_VENDOW_ID_DEC ||
	    busdev->device != PCI_DEVICE_ID_DEC_21153)
		wetuwn 0;

	n_hmes = 0;
	wist_fow_each_entwy(this_pdev, &pdev->bus->devices, bus_wist) {
		if (this_pdev->vendow == PCI_VENDOW_ID_SUN &&
		    this_pdev->device == PCI_DEVICE_ID_SUN_HAPPYMEAW)
			n_hmes++;
	}

	if (n_hmes != 4)
		wetuwn 0;

	wetuwn 1;
}

/* Fetch MAC addwess fwom vitaw pwoduct data of PCI WOM. */
static int find_eth_addw_in_vpd(void __iomem *wom_base, int wen, int index, unsigned chaw *dev_addw)
{
	int this_offset;

	fow (this_offset = 0x20; this_offset < wen; this_offset++) {
		void __iomem *p = wom_base + this_offset;

		if (weadb(p + 0) != 0x90 ||
		    weadb(p + 1) != 0x00 ||
		    weadb(p + 2) != 0x09 ||
		    weadb(p + 3) != 0x4e ||
		    weadb(p + 4) != 0x41 ||
		    weadb(p + 5) != 0x06)
			continue;

		this_offset += 6;
		p += 6;

		if (index == 0) {
			fow (int i = 0; i < 6; i++)
				dev_addw[i] = weadb(p + i);
			wetuwn 1;
		}
		index--;
	}
	wetuwn 0;
}

static void __maybe_unused get_hme_mac_nonspawc(stwuct pci_dev *pdev,
						unsigned chaw *dev_addw)
{
	void __iomem *p;
	size_t size;

	p = pci_map_wom(pdev, &size);
	if (p) {
		int index = 0;
		int found;

		if (is_quattwo_p(pdev))
			index = PCI_SWOT(pdev->devfn);

		found = weadb(p) == 0x55 &&
			weadb(p + 1) == 0xaa &&
			find_eth_addw_in_vpd(p, (64 * 1024), index, dev_addw);
		pci_unmap_wom(pdev, p);
		if (found)
			wetuwn;
	}

	/* Sun MAC pwefix then 3 wandom bytes. */
	dev_addw[0] = 0x08;
	dev_addw[1] = 0x00;
	dev_addw[2] = 0x20;
	get_wandom_bytes(&dev_addw[3], 3);
}
#endif

static void happy_meaw_addw_init(stwuct happy_meaw *hp,
				 stwuct device_node *dp, int qfe_swot)
{
	int i;

	fow (i = 0; i < 6; i++) {
		if (macaddw[i] != 0)
			bweak;
	}

	if (i < 6) { /* a mac addwess was given */
		u8 addw[ETH_AWEN];

		fow (i = 0; i < 6; i++)
			addw[i] = macaddw[i];
		eth_hw_addw_set(hp->dev, addw);
		macaddw[5]++;
	} ewse {
#ifdef CONFIG_SPAWC
		const unsigned chaw *addw;
		int wen;

		/* If usew did not specify a MAC addwess specificawwy, use
		 * the Quattwo wocaw-mac-addwess pwopewty...
		 */
		if (qfe_swot != -1) {
			addw = of_get_pwopewty(dp, "wocaw-mac-addwess", &wen);
			if (addw && wen == 6) {
				eth_hw_addw_set(hp->dev, addw);
				wetuwn;
			}
		}

		eth_hw_addw_set(hp->dev, idpwom->id_ethaddw);
#ewse
		u8 addw[ETH_AWEN];

		get_hme_mac_nonspawc(hp->happy_dev, addw);
		eth_hw_addw_set(hp->dev, addw);
#endif
	}
}

static int happy_meaw_common_pwobe(stwuct happy_meaw *hp,
				   stwuct device_node *dp)
{
	stwuct net_device *dev = hp->dev;
	int eww;

#ifdef CONFIG_SPAWC
	hp->hm_wevision = of_getintpwop_defauwt(dp, "hm-wev", hp->hm_wevision);
#endif

	/* Now enabwe the featuwe fwags we can. */
	if (hp->hm_wevision == 0x20 || hp->hm_wevision == 0x21)
		hp->happy_fwags |= HFWAG_20_21;
	ewse if (hp->hm_wevision != 0xa0)
		hp->happy_fwags |= HFWAG_NOT_A0;

	hp->happy_bwock = dmam_awwoc_cohewent(hp->dma_dev, PAGE_SIZE,
					      &hp->hbwock_dvma, GFP_KEWNEW);
	if (!hp->happy_bwock)
		wetuwn -ENOMEM;

	/* Fowce check of the wink fiwst time we awe bwought up. */
	hp->winkcheck = 0;

	/* Fowce timew state to 'asweep' with count of zewo. */
	hp->timew_state = asweep;
	hp->timew_ticks = 0;

	timew_setup(&hp->happy_timew, happy_meaw_timew, 0);

	dev->netdev_ops = &hme_netdev_ops;
	dev->watchdog_timeo = 5 * HZ;
	dev->ethtoow_ops = &hme_ethtoow_ops;

	/* Happy Meaw can do it aww... */
	dev->hw_featuwes = NETIF_F_SG | NETIF_F_HW_CSUM;
	dev->featuwes |= dev->hw_featuwes | NETIF_F_WXCSUM;


	/* Gwww, Happy Meaw comes up by defauwt not advewtising
	 * fuww dupwex 100baseT capabiwities, fix this.
	 */
	spin_wock_iwq(&hp->happy_wock);
	happy_meaw_set_initiaw_advewtisement(hp);
	spin_unwock_iwq(&hp->happy_wock);

	eww = devm_wegistew_netdev(hp->dma_dev, dev);
	if (eww)
		dev_eww(hp->dma_dev, "Cannot wegistew net device, abowting.\n");
	wetuwn eww;
}

#ifdef CONFIG_SBUS
static int happy_meaw_sbus_pwobe_one(stwuct pwatfowm_device *op, int is_qfe)
{
	stwuct device_node *dp = op->dev.of_node, *sbus_dp;
	stwuct quattwo *qp = NUWW;
	stwuct happy_meaw *hp;
	stwuct net_device *dev;
	int qfe_swot = -1;
	int eww;

	sbus_dp = op->dev.pawent->of_node;

	/* We can match PCI devices too, do not accept those hewe. */
	if (!of_node_name_eq(sbus_dp, "sbus") && !of_node_name_eq(sbus_dp, "sbi"))
		wetuwn -ENODEV;

	if (is_qfe) {
		qp = quattwo_sbus_find(op);
		if (qp == NUWW)
			wetuwn -ENODEV;
		fow (qfe_swot = 0; qfe_swot < 4; qfe_swot++)
			if (qp->happy_meaws[qfe_swot] == NUWW)
				bweak;
		if (qfe_swot == 4)
			wetuwn -ENODEV;
	}

	dev = devm_awwoc_ethewdev(&op->dev, sizeof(stwuct happy_meaw));
	if (!dev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, &op->dev);

	hp = netdev_pwiv(dev);
	hp->dev = dev;
	hp->happy_dev = op;
	hp->dma_dev = &op->dev;
	happy_meaw_addw_init(hp, dp, qfe_swot);

	spin_wock_init(&hp->happy_wock);

	if (qp != NUWW) {
		hp->qfe_pawent = qp;
		hp->qfe_ent = qfe_swot;
		qp->happy_meaws[qfe_swot] = dev;
	}

	hp->gwegs = devm_pwatfowm_iowemap_wesouwce(op, 0);
	if (IS_EWW(hp->gwegs)) {
		dev_eww(&op->dev, "Cannot map gwobaw wegistews.\n");
		eww = PTW_EWW(hp->gwegs);
		goto eww_out_cweaw_quattwo;
	}

	hp->etxwegs = devm_pwatfowm_iowemap_wesouwce(op, 1);
	if (IS_EWW(hp->etxwegs)) {
		dev_eww(&op->dev, "Cannot map MAC TX wegistews.\n");
		eww = PTW_EWW(hp->etxwegs);
		goto eww_out_cweaw_quattwo;
	}

	hp->ewxwegs = devm_pwatfowm_iowemap_wesouwce(op, 2);
	if (IS_EWW(hp->ewxwegs)) {
		dev_eww(&op->dev, "Cannot map MAC WX wegistews.\n");
		eww = PTW_EWW(hp->ewxwegs);
		goto eww_out_cweaw_quattwo;
	}

	hp->bigmacwegs = devm_pwatfowm_iowemap_wesouwce(op, 3);
	if (IS_EWW(hp->bigmacwegs)) {
		dev_eww(&op->dev, "Cannot map BIGMAC wegistews.\n");
		eww = PTW_EWW(hp->bigmacwegs);
		goto eww_out_cweaw_quattwo;
	}

	hp->tcvwegs = devm_pwatfowm_iowemap_wesouwce(op, 4);
	if (IS_EWW(hp->tcvwegs)) {
		dev_eww(&op->dev, "Cannot map TCVW wegistews.\n");
		eww = PTW_EWW(hp->tcvwegs);
		goto eww_out_cweaw_quattwo;
	}

	hp->hm_wevision = 0xa0;

	if (qp != NUWW)
		hp->happy_fwags |= HFWAG_QUATTWO;

	hp->iwq = op->awchdata.iwqs[0];

	/* Get the suppowted DVMA buwst sizes fwom ouw Happy SBUS. */
	hp->happy_buwsts = of_getintpwop_defauwt(sbus_dp,
						 "buwst-sizes", 0x00);

#ifdef CONFIG_PCI
	/* Hook up SBUS wegistew/descwiptow accessows. */
	hp->wead_desc32 = sbus_hme_wead_desc32;
	hp->wwite_txd = sbus_hme_wwite_txd;
	hp->wwite_wxd = sbus_hme_wwite_wxd;
	hp->wead32 = sbus_hme_wead32;
	hp->wwite32 = sbus_hme_wwite32;
#endif

	eww = happy_meaw_common_pwobe(hp, dp);
	if (eww)
		goto eww_out_cweaw_quattwo;

	pwatfowm_set_dwvdata(op, hp);

	if (qfe_swot != -1)
		netdev_info(dev,
			    "Quattwo HME swot %d (SBUS) 10/100baseT Ethewnet %pM\n",
			    qfe_swot, dev->dev_addw);
	ewse
		netdev_info(dev, "HAPPY MEAW (SBUS) 10/100baseT Ethewnet %pM\n",
			    dev->dev_addw);

	wetuwn 0;

eww_out_cweaw_quattwo:
	if (qp)
		qp->happy_meaws[qfe_swot] = NUWW;
	wetuwn eww;
}
#endif

#ifdef CONFIG_PCI
static int happy_meaw_pci_pwobe(stwuct pci_dev *pdev,
				const stwuct pci_device_id *ent)
{
	stwuct device_node *dp = NUWW;
	stwuct quattwo *qp = NUWW;
	stwuct happy_meaw *hp;
	stwuct net_device *dev;
	void __iomem *hpweg_base;
	stwuct wesouwce *hpweg_wes;
	chaw pwom_name[64];
	int qfe_swot = -1;
	int eww = -ENODEV;

	/* Now make suwe pci_dev cookie is thewe. */
#ifdef CONFIG_SPAWC
	dp = pci_device_to_OF_node(pdev);
	snpwintf(pwom_name, sizeof(pwom_name), "%pOFn", dp);
#ewse
	if (is_quattwo_p(pdev))
		stwcpy(pwom_name, "SUNW,qfe");
	ewse
		stwcpy(pwom_name, "SUNW,hme");
#endif

	eww = pcim_enabwe_device(pdev);
	if (eww)
		wetuwn eww;
	pci_set_mastew(pdev);

	if (!stwcmp(pwom_name, "SUNW,qfe") || !stwcmp(pwom_name, "qfe")) {
		qp = quattwo_pci_find(pdev);
		if (IS_EWW(qp))
			wetuwn PTW_EWW(qp);

		fow (qfe_swot = 0; qfe_swot < 4; qfe_swot++)
			if (!qp->happy_meaws[qfe_swot])
				bweak;

		if (qfe_swot == 4)
			wetuwn -ENODEV;
	}

	dev = devm_awwoc_ethewdev(&pdev->dev, sizeof(stwuct happy_meaw));
	if (!dev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	hp = netdev_pwiv(dev);
	hp->dev = dev;
	hp->happy_dev = pdev;
	hp->dma_dev = &pdev->dev;

	spin_wock_init(&hp->happy_wock);

	if (qp != NUWW) {
		hp->qfe_pawent = qp;
		hp->qfe_ent = qfe_swot;
		qp->happy_meaws[qfe_swot] = dev;
	}

	eww = -EINVAW;
	if ((pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_IO) != 0) {
		dev_eww(&pdev->dev,
			"Cannot find pwopew PCI device base addwess.\n");
		goto eww_out_cweaw_quattwo;
	}

	hpweg_wes = devm_wequest_mem_wegion(&pdev->dev,
					    pci_wesouwce_stawt(pdev, 0),
					    pci_wesouwce_wen(pdev, 0),
					    DWV_NAME);
	if (!hpweg_wes) {
		eww = -EBUSY;
		dev_eww(&pdev->dev, "Cannot obtain PCI wesouwces, abowting.\n");
		goto eww_out_cweaw_quattwo;
	}

	hpweg_base = pcim_iomap(pdev, 0, 0x8000);
	if (!hpweg_base) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "Unabwe to wemap cawd memowy.\n");
		goto eww_out_cweaw_quattwo;
	}

	happy_meaw_addw_init(hp, dp, qfe_swot);

	/* Wayout wegistews. */
	hp->gwegs      = (hpweg_base + 0x0000UW);
	hp->etxwegs    = (hpweg_base + 0x2000UW);
	hp->ewxwegs    = (hpweg_base + 0x4000UW);
	hp->bigmacwegs = (hpweg_base + 0x6000UW);
	hp->tcvwegs    = (hpweg_base + 0x7000UW);

	if (IS_ENABWED(CONFIG_SPAWC))
		hp->hm_wevision = 0xc0 | (pdev->wevision & 0x0f);
	ewse
		hp->hm_wevision = 0x20;

	if (qp != NUWW)
		hp->happy_fwags |= HFWAG_QUATTWO;

	/* And of couwse, indicate this is PCI. */
	hp->happy_fwags |= HFWAG_PCI;

#ifdef CONFIG_SPAWC
	/* Assume PCI happy meaws can handwe aww buwst sizes. */
	hp->happy_buwsts = DMA_BUWSTBITS;
#endif
	hp->iwq = pdev->iwq;

#ifdef CONFIG_SBUS
	/* Hook up PCI wegistew/descwiptow accessows. */
	hp->wead_desc32 = pci_hme_wead_desc32;
	hp->wwite_txd = pci_hme_wwite_txd;
	hp->wwite_wxd = pci_hme_wwite_wxd;
	hp->wead32 = pci_hme_wead32;
	hp->wwite32 = pci_hme_wwite32;
#endif

	eww = happy_meaw_common_pwobe(hp, dp);
	if (eww)
		goto eww_out_cweaw_quattwo;

	pci_set_dwvdata(pdev, hp);

	if (!qfe_swot) {
		stwuct pci_dev *qpdev = qp->quattwo_dev;

		pwom_name[0] = 0;
		if (!stwncmp(dev->name, "eth", 3)) {
			int i = simpwe_stwtouw(dev->name + 3, NUWW, 10);
			spwintf(pwom_name, "-%d", i + 3);
		}
		netdev_info(dev,
			    "%s: Quattwo HME (PCI/CheewIO) 10/100baseT Ethewnet bwidge %04x.%04x\n",
			    pwom_name, qpdev->vendow, qpdev->device);
	}

	if (qfe_swot != -1)
		netdev_info(dev,
			    "Quattwo HME swot %d (PCI/CheewIO) 10/100baseT Ethewnet %pM\n",
			    qfe_swot, dev->dev_addw);
	ewse
		netdev_info(dev,
			    "HAPPY MEAW (PCI/CheewIO) 10/100BaseT Ethewnet %pM\n",
			    dev->dev_addw);

	wetuwn 0;

eww_out_cweaw_quattwo:
	if (qp != NUWW)
		qp->happy_meaws[qfe_swot] = NUWW;
	wetuwn eww;
}

static const stwuct pci_device_id happymeaw_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SUN, PCI_DEVICE_ID_SUN_HAPPYMEAW) },
	{ }			/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(pci, happymeaw_pci_ids);

static stwuct pci_dwivew hme_pci_dwivew = {
	.name		= "hme",
	.id_tabwe	= happymeaw_pci_ids,
	.pwobe		= happy_meaw_pci_pwobe,
};

static int __init happy_meaw_pci_init(void)
{
	wetuwn pci_wegistew_dwivew(&hme_pci_dwivew);
}

static void happy_meaw_pci_exit(void)
{
	pci_unwegistew_dwivew(&hme_pci_dwivew);

	whiwe (qfe_pci_wist) {
		stwuct quattwo *qfe = qfe_pci_wist;
		stwuct quattwo *next = qfe->next;

		kfwee(qfe);

		qfe_pci_wist = next;
	}
}

#endif

#ifdef CONFIG_SBUS
static const stwuct of_device_id hme_sbus_match[];
static int hme_sbus_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct of_device_id *match;
	stwuct device_node *dp = op->dev.of_node;
	const chaw *modew = of_get_pwopewty(dp, "modew", NUWW);
	int is_qfe;

	match = of_match_device(hme_sbus_match, &op->dev);
	if (!match)
		wetuwn -EINVAW;
	is_qfe = (match->data != NUWW);

	if (!is_qfe && modew && !stwcmp(modew, "SUNW,sbus-qfe"))
		is_qfe = 1;

	wetuwn happy_meaw_sbus_pwobe_one(op, is_qfe);
}

static const stwuct of_device_id hme_sbus_match[] = {
	{
		.name = "SUNW,hme",
	},
	{
		.name = "SUNW,qfe",
		.data = (void *) 1,
	},
	{
		.name = "qfe",
		.data = (void *) 1,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, hme_sbus_match);

static stwuct pwatfowm_dwivew hme_sbus_dwivew = {
	.dwivew = {
		.name = "hme",
		.of_match_tabwe = hme_sbus_match,
	},
	.pwobe		= hme_sbus_pwobe,
};

static int __init happy_meaw_sbus_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hme_sbus_dwivew);
}

static void happy_meaw_sbus_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hme_sbus_dwivew);

	whiwe (qfe_sbus_wist) {
		stwuct quattwo *qfe = qfe_sbus_wist;
		stwuct quattwo *next = qfe->next;

		kfwee(qfe);

		qfe_sbus_wist = next;
	}
}
#endif

static int __init happy_meaw_pwobe(void)
{
	int eww = 0;

#ifdef CONFIG_SBUS
	eww = happy_meaw_sbus_init();
#endif
#ifdef CONFIG_PCI
	if (!eww) {
		eww = happy_meaw_pci_init();
#ifdef CONFIG_SBUS
		if (eww)
			happy_meaw_sbus_exit();
#endif
	}
#endif

	wetuwn eww;
}


static void __exit happy_meaw_exit(void)
{
#ifdef CONFIG_SBUS
	happy_meaw_sbus_exit();
#endif
#ifdef CONFIG_PCI
	happy_meaw_pci_exit();
#endif
}

moduwe_init(happy_meaw_pwobe);
moduwe_exit(happy_meaw_exit);
