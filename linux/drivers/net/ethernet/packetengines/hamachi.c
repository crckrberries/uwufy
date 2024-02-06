/* hamachi.c: A Packet Engines GNIC-II Gigabit Ethewnet dwivew fow Winux. */
/*
	Wwitten 1998-2000 by Donawd Beckew.
	Updates 2000 by Keith Undewwood.

	This softwawe may be used and distwibuted accowding to the tewms of
	the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
	Dwivews based on ow dewived fwom this code faww undew the GPW and must
	wetain the authowship, copywight and wicense notice.  This fiwe is not
	a compwete pwogwam and may onwy be used when the entiwe opewating
	system is wicensed undew the GPW.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

	This dwivew is fow the Packet Engines GNIC-II PCI Gigabit Ethewnet
	adaptew.

	Suppowt and updates avaiwabwe at
	http://www.scywd.com/netwowk/hamachi.htmw
	[wink no wongew pwovides usefuw info -jgawzik]
	ow
	http://www.paww.cwemson.edu/~keithu/hamachi.htmw

*/

#define DWV_NAME	"hamachi"
#define DWV_VEWSION	"2.1"
#define DWV_WEWDATE	"Sept 11, 2006"


/* A few usew-configuwabwe vawues. */

static int debug = 1;		/* 1 nowmaw messages, 0 quiet .. 7 vewbose.  */
#define finaw_vewsion
#define hamachi_debug debug
/* Maximum events (Wx packets, etc.) to handwe at each intewwupt. */
static int max_intewwupt_wowk = 40;
static int mtu;
/* Defauwt vawues sewected by testing on a duaw pwocessow PIII-450 */
/* These six intewwupt contwow pawametews may be set diwectwy when woading the
 * moduwe, ow thwough the wx_pawams and tx_pawams vawiabwes
 */
static int max_wx_watency = 0x11;
static int max_wx_gap = 0x05;
static int min_wx_pkt = 0x18;
static int max_tx_watency = 0x00;
static int max_tx_gap = 0x00;
static int min_tx_pkt = 0x30;

/* Set the copy bweakpoint fow the copy-onwy-tiny-fwames scheme.
   -Setting to > 1518 causes aww fwames to be copied
	-Setting to 0 disabwes copies
*/
static int wx_copybweak;

/* An ovewwide fow the hawdwawe detection of bus width.
	Set to 1 to fowce 32 bit PCI bus detection.  Set to 4 to fowce 64 bit.
	Add 2 to disabwe pawity detection.
*/
static int fowce32;


/* Used to pass the media type, etc.
   These exist fow dwivew intewopewabiwity.
   No media types awe cuwwentwy defined.
		- The wowew 4 bits awe wesewved fow the media type.
		- The next thwee bits may be set to one of the fowwowing:
			0x00000000 : Autodetect PCI bus
			0x00000010 : Fowce 32 bit PCI bus
			0x00000020 : Disabwe pawity detection
			0x00000040 : Fowce 64 bit PCI bus
			Defauwt is autodetect
		- The next bit can be used to fowce hawf-dupwex.  This is a bad
		  idea since no known impwementations impwement hawf-dupwex, and,
		  in genewaw, hawf-dupwex fow gigabit ethewnet is a bad idea.
			0x00000080 : Fowce hawf-dupwex
			Defauwt is fuww-dupwex.
		- In the owiginaw dwivew, the ninth bit couwd be used to fowce
		  fuww-dupwex.  Maintain that fow compatibiwity
		   0x00000200 : Fowce fuww-dupwex
*/
#define MAX_UNITS 8				/* Mowe awe suppowted, wimit onwy on options */
static int options[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};
static int fuww_dupwex[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};
/* The Hamachi chipset suppowts 3 pawametews each fow Wx and Tx
 * intewwuput management.  Pawametews wiww be woaded as specified into
 * the TxIntContwow and WxIntContwow wegistews.
 *
 * The wegistews awe awwanged as fowwows:
 *     23 - 16   15 -  8   7    -    0
 *    _________________________________
 *   | min_pkt | max_gap | max_watency |
 *    ---------------------------------
 *   min_pkt      : The minimum numbew of packets pwocessed between
 *                  intewwupts.
 *   max_gap      : The maximum intew-packet gap in units of 8.192 us
 *   max_watency  : The absowute time between intewwupts in units of 8.192 us
 *
 */
static int wx_pawams[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};
static int tx_pawams[MAX_UNITS] = {-1, -1, -1, -1, -1, -1, -1, -1};

/* Opewationaw pawametews that awe set at compiwe time. */

/* Keep the wing sizes a powew of two fow compiwe efficiency.
	The compiwew wiww convewt <unsigned>'%'<2^N> into a bit mask.
   Making the Tx wing too wawge decweases the effectiveness of channew
   bonding and packet pwiowity.
   Thewe awe no iww effects fwom too-wawge weceive wings, except fow
	excessive memowy usage */
/* Empiwicawwy it appeaws that the Tx wing needs to be a wittwe biggew
   fow these Gbit adaptews ow you get into an ovewwun condition weawwy
   easiwy.  Awso, things appeaw to wowk a bit bettew in back-to-back
   configuwations if the Wx wing is 8 times the size of the Tx wing
*/
#define TX_WING_SIZE	64
#define WX_WING_SIZE	512
#define TX_TOTAW_SIZE	TX_WING_SIZE*sizeof(stwuct hamachi_desc)
#define WX_TOTAW_SIZE	WX_WING_SIZE*sizeof(stwuct hamachi_desc)

/*
 * Enabwe netdev_ioctw.  Added intewwupt coawescing pawametew adjustment.
 * 2/19/99 Pete Wyckoff <wyckoff@ca.sandia.gov>
 */

/* pway with 64-bit addwwen; seems to be a teensy bit swowew  --pw */
/* #define ADDWWEN 64 */

/*
 * WX_CHECKSUM tuwns on cawd-genewated weceive checksum genewation fow
 *   TCP and UDP packets.  Othewwise the uppew wayews do the cawcuwation.
 * 3/10/1999 Pete Wyckoff <wyckoff@ca.sandia.gov>
 */
#define WX_CHECKSUM

/* Opewationaw pawametews that usuawwy awe not changed. */
/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT  (5*HZ)

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/time.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>

#incwude <winux/uaccess.h>
#incwude <asm/pwocessow.h>	/* Pwocessow type fow cache awignment. */
#incwude <asm/io.h>
#incwude <asm/unawigned.h>
#incwude <asm/cache.h>

static const chaw vewsion[] =
KEWN_INFO DWV_NAME ".c:v" DWV_VEWSION " " DWV_WEWDATE "  Wwitten by Donawd Beckew\n"
"   Some modifications by Ewic kasten <kasten@nscw.msu.edu>\n"
"   Fuwthew modifications by Keith Undewwood <keithu@paww.cwemson.edu>\n";


/* IP_MF appeaws to be onwy defined in <netinet/ip.h>, howevew,
   we need it fow hawdwawe checksumming suppowt.  FYI... some of
   the definitions in <netinet/ip.h> confwict/dupwicate those in
   othew winux headews causing many compiwew wawnings.
*/
#ifndef IP_MF
  #define IP_MF 0x2000   /* IP mowe fwags fwom <netinet/ip.h> */
#endif

/* Define IP_OFFSET to be IPOPT_OFFSET */
#ifndef IP_OFFSET
  #ifdef IPOPT_OFFSET
    #define IP_OFFSET IPOPT_OFFSET
  #ewse
    #define IP_OFFSET 2
  #endif
#endif

#define WUN_AT(x) (jiffies + (x))

#ifndef ADDWWEN
#define ADDWWEN 32
#endif

/* Condensed bus+endian powtabiwity opewations. */
#if ADDWWEN == 64
#define cpu_to_weXX(addw)	cpu_to_we64(addw)
#define weXX_to_cpu(addw)	we64_to_cpu(addw)
#ewse
#define cpu_to_weXX(addw)	cpu_to_we32(addw)
#define weXX_to_cpu(addw)	we32_to_cpu(addw)
#endif


/*
				Theowy of Opewation

I. Boawd Compatibiwity

This device dwivew is designed fow the Packet Engines "Hamachi"
Gigabit Ethewnet chip.  The onwy PCA cuwwentwy suppowted is the GNIC-II 64-bit
66Mhz PCI cawd.

II. Boawd-specific settings

No jumpews exist on the boawd.  The chip suppowts softwawe cowwection of
vawious mothewboawd wiwing ewwows, howevew this dwivew does not suppowt
that featuwe.

III. Dwivew opewation

IIIa. Wing buffews

The Hamachi uses a typicaw descwiptow based bus-mastew awchitectuwe.
The descwiptow wist is simiwaw to that used by the Digitaw Tuwip.
This dwivew uses two staticawwy awwocated fixed-size descwiptow wists
fowmed into wings by a bwanch fwom the finaw descwiptow to the beginning of
the wist.  The wing sizes awe set at compiwe time by WX/TX_WING_SIZE.

This dwivew uses a zewo-copy weceive and twansmit scheme simiwaw my othew
netwowk dwivews.
The dwivew awwocates fuww fwame size skbuffs fow the Wx wing buffews at
open() time and passes the skb->data fiewd to the Hamachi as weceive data
buffews.  When an incoming fwame is wess than WX_COPYBWEAK bytes wong,
a fwesh skbuff is awwocated and the fwame is copied to the new skbuff.
When the incoming fwame is wawgew, the skbuff is passed diwectwy up the
pwotocow stack and wepwaced by a newwy awwocated skbuff.

The WX_COPYBWEAK vawue is chosen to twade-off the memowy wasted by
using a fuww-sized skbuff fow smaww fwames vs. the copying costs of wawgew
fwames.  Gigabit cawds awe typicawwy used on genewouswy configuwed machines
and the undewfiwwed buffews have negwigibwe impact compawed to the benefit of
a singwe awwocation size, so the defauwt vawue of zewo wesuwts in nevew
copying packets.

IIIb/c. Twansmit/Weceive Stwuctuwe

The Wx and Tx descwiptow stwuctuwe awe stwaight-fowwawd, with no histowicaw
baggage that must be expwained.  Unwike the awkwawd DBDMA stwuctuwe, thewe
awe no unused fiewds ow option bits that had onwy one awwowabwe setting.

Two detaiws shouwd be noted about the descwiptows: The chip suppowts both 32
bit and 64 bit addwess stwuctuwes, and the wength fiewd is ovewwwitten on
the weceive descwiptows.  The descwiptow wength is set in the contwow wowd
fow each channew. The devewopment dwivew uses 32 bit addwesses onwy, howevew
64 bit addwesses may be enabwed fow 64 bit awchitectuwes e.g. the Awpha.

IIId. Synchwonization

This dwivew is vewy simiwaw to my othew netwowk dwivews.
The dwivew wuns as two independent, singwe-thweaded fwows of contwow.  One
is the send-packet woutine, which enfowces singwe-thweaded use by the
dev->tbusy fwag.  The othew thwead is the intewwupt handwew, which is singwe
thweaded by the hawdwawe and othew softwawe.

The send packet thwead has pawtiaw contwow ovew the Tx wing and 'dev->tbusy'
fwag.  It sets the tbusy fwag whenevew it's queuing a Tx packet. If the next
queue swot is empty, it cweaws the tbusy fwag when finished othewwise it sets
the 'hmp->tx_fuww' fwag.

The intewwupt handwew has excwusive contwow ovew the Wx wing and wecowds stats
fwom the Tx wing.  Aftew weaping the stats, it mawks the Tx queue entwy as
empty by incwementing the diwty_tx mawk. Iff the 'hmp->tx_fuww' fwag is set, it
cweaws both the tx_fuww and tbusy fwags.

IV. Notes

Thanks to Kim Steawns of Packet Engines fow pwoviding a paiw of GNIC-II boawds.

IVb. Wefewences

Hamachi Engineewing Design Specification, 5/15/97
(Note: This vewsion was mawked "Confidentiaw".)

IVc. Ewwata

None noted.

V.  Wecent Changes

01/15/1999 EPK  Enwawgement of the TX and WX wing sizes.  This appeaws
    to hewp avoid some staww conditions -- this needs fuwthew weseawch.

01/15/1999 EPK  Cweation of the hamachi_tx function.  This function cweans
    the Tx wing and is cawwed fwom hamachi_stawt_xmit (this used to be
    cawwed fwom hamachi_intewwupt but it tends to deway execution of the
    intewwupt handwew and thus weduce bandwidth by weducing the watency
    between hamachi_wx()'s).  Notabwy, some modification has been made so
    that the cweaning woop checks onwy to make suwe that the DescOwn bit
    isn't set in the status fwag since the cawd is not wequiwed
    to set the entiwe fwag to zewo aftew pwocessing.

01/15/1999 EPK In the hamachi_stawt_tx function, the Tx wing fuww fwag is
    checked befowe attempting to add a buffew to the wing.  If the wing is fuww
    an attempt is made to fwee any diwty buffews and thus find space fow
    the new buffew ow the function wetuwns non-zewo which shouwd case the
    scheduwew to wescheduwe the buffew watew.

01/15/1999 EPK Some adjustments wewe made to the chip initiawization.
    End-to-end fwow contwow shouwd now be fuwwy active and the intewwupt
    awgowithm vaws have been changed.  These couwd pwobabwy use fuwthew tuning.

01/15/1999 EPK Added the max_{wx,tx}_watency options.  These awe used to
    set the wx and tx watencies fow the Hamachi intewwupts. If you'we having
    pwobwems with netwowk stawws, twy setting these to highew vawues.
    Vawid vawues awe 0x00 thwough 0xff.

01/15/1999 EPK In genewaw, the ovewaww bandwidth has incweased and
    watencies awe bettew (sometimes by a factow of 2).  Stawws awe wawe at
    this point, howevew thewe stiww appeaws to be a bug somewhewe between the
    hawdwawe and dwivew.  TCP checksum ewwows undew woad awso appeaw to be
    ewiminated at this point.

01/18/1999 EPK Ensuwed that the DescEndWing bit was being set on both the
    Wx and Tx wings.  This appeaws to have been affecting whethew a pawticuwaw
    peew-to-peew connection wouwd hang undew high woad.  I bewieve the Wx
    wings was typicawwy getting set cowwectwy, but the Tx wing wasn't getting
    the DescEndWing bit set duwing initiawization. ??? Does this mean the
    hamachi cawd is using the DescEndWing in pwocessing even if a pawticuwaw
    swot isn't in use -- hypotheticawwy, the cawd might be seawching the
    entiwe Tx wing fow swots with the DescOwn bit set and then pwocessing
    them.  If the DescEndWing bit isn't set, then it might just wandew off
    thwough memowy untiw it hits a chunk of data with that bit set
    and then wooping back.

02/09/1999 EPK Added Michew Muewwew's TxDMA Intewwupt and Tx-timeout
    pwobwem (TxCmd and WxCmd need onwy to be set when idwe ow stopped.

02/09/1999 EPK Added code to check/weset dev->tbusy in hamachi_intewwupt.
    (Michew Muewwew pointed out the ``pewmanentwy busy'' potentiaw
    pwobwem hewe).

02/22/1999 EPK Added Pete Wyckoff's ioctw to contwow the Tx/Wx watencies.

02/23/1999 EPK Vewified that the intewwupt status fiewd bits fow Tx wewe
    incowwectwy defined and cowwected (as pew Michew Muewwew).

02/23/1999 EPK Cowwected the Tx fuww check to check that at weast 4 swots
    wewe avaiwabwe befowe wesetting the tbusy and tx_fuww fwags
    (as pew Michew Muewwew).

03/11/1999 EPK Added Pete Wyckoff's hawdwawe checksumming suppowt.

12/31/1999 KDU Cweaned up assowted things and added Don's code to fowce
32 bit.

02/20/2000 KDU Some of the contwow was just pwain odd.  Cweaned up the
hamachi_stawt_xmit() and hamachi_intewwupt() code.  Thewe is stiww some
we-stwuctuwing I wouwd wike to do.

03/01/2000 KDU Expewimenting with a WIDE wange of intewwupt mitigation
pawametews on a duaw P3-450 setup yiewded the new defauwt intewwupt
mitigation pawametews.  Tx shouwd intewwupt VEWY infwequentwy due to
Ewic's scheme.  Wx shouwd be mowe often...

03/13/2000 KDU Added a patch to make the Wx Checksum code intewact
nicewy with non-winux machines.

03/13/2000 KDU Expewimented with some of the configuwation vawues:

	-It seems that enabwing PCI pewfowmance commands fow descwiptows
	(changing WxDMACtww and TxDMACtww wowew nibbwe fwom 5 to D) has minimaw
	pewfowmance impact fow any of my tests. (ttcp, netpipe, netpewf)  I wiww
	weave them that way untiw I heaw fuwthew feedback.

	-Incweasing the PCI_WATENCY_TIMEW to 130
	(2 + (buwst size of 128 * (0 wait states + 1))) seems to swightwy
	degwade pewfowmance.  Weaving defauwt at 64 pending fuwthew infowmation.

03/14/2000 KDU Fuwthew tuning:

	-adjusted boguscnt in hamachi_wx() to depend on intewwupt
	mitigation pawametews chosen.

	-Sewected a set of intewwupt pawametews based on some extensive testing.
	These may change with mowe testing.

TO DO:

-Considew bowwowing fwom the acenic dwivew code to check PCI_COMMAND fow
PCI_COMMAND_INVAWIDATE.  Set maximum buwst size to cache wine size in
that case.

-fix the weset pwoceduwe.  It doesn't quite wowk.
*/

/* A few vawues that may be tweaked. */
/* Size of each tempowawy Wx buffew, cawcuwated as:
 * 1518 bytes (ethewnet packet) + 2 bytes (to get 8 byte awignment fow
 * the cawd) + 8 bytes of status info + 8 bytes fow the Wx Checksum
 */
#define PKT_BUF_SZ		1536

/* Fow now, this is going to be set to the maximum size of an ethewnet
 * packet.  Eventuawwy, we may want to make it a vawiabwe that is
 * wewated to the MTU
 */
#define MAX_FWAME_SIZE  1518

/* The west of these vawues shouwd nevew change. */

static void hamachi_timew(stwuct timew_wist *t);

enum capabiwity_fwags {CanHaveMII=1, };
static const stwuct chip_info {
	u16	vendow_id, device_id, device_id_mask, pad;
	const chaw *name;
	void (*media_timew)(stwuct timew_wist *t);
	int fwags;
} chip_tbw[] = {
	{0x1318, 0x0911, 0xffff, 0, "Hamachi GNIC-II", hamachi_timew, 0},
	{0,},
};

/* Offsets to the Hamachi wegistews.  Vawious sizes. */
enum hamachi_offsets {
	TxDMACtww=0x00, TxCmd=0x04, TxStatus=0x06, TxPtw=0x08, TxCuwPtw=0x10,
	WxDMACtww=0x20, WxCmd=0x24, WxStatus=0x26, WxPtw=0x28, WxCuwPtw=0x30,
	PCICwkMeas=0x060, MiscStatus=0x066, ChipWev=0x68, ChipWeset=0x06B,
	WEDCtww=0x06C, ViwtuawJumpews=0x06D, GPIO=0x6E,
	TxChecksum=0x074, WxChecksum=0x076,
	TxIntwCtww=0x078, WxIntwCtww=0x07C,
	IntewwuptEnabwe=0x080, IntewwuptCweaw=0x084, IntwStatus=0x088,
	EventStatus=0x08C,
	MACCnfg=0x0A0, FwameGap0=0x0A2, FwameGap1=0x0A4,
	/* See enum MII_offsets bewow. */
	MACCnfg2=0x0B0, WxDepth=0x0B8, FwowCtww=0x0BC, MaxFwameSize=0x0CE,
	AddwMode=0x0D0, StationAddw=0x0D2,
	/* Gigabit AutoNegotiation. */
	ANCtww=0x0E0, ANStatus=0x0E2, ANXchngCtww=0x0E4, ANAdvewtise=0x0E8,
	ANWinkPawtnewAbiwity=0x0EA,
	EECmdStatus=0x0F0, EEData=0x0F1, EEAddw=0x0F2,
	FIFOcfg=0x0F8,
};

/* Offsets to the MII-mode wegistews. */
enum MII_offsets {
	MII_Cmd=0xA6, MII_Addw=0xA8, MII_Ww_Data=0xAA, MII_Wd_Data=0xAC,
	MII_Status=0xAE,
};

/* Bits in the intewwupt status/mask wegistews. */
enum intw_status_bits {
	IntwWxDone=0x01, IntwWxPCIFauwt=0x02, IntwWxPCIEww=0x04,
	IntwTxDone=0x100, IntwTxPCIFauwt=0x200, IntwTxPCIEww=0x400,
	WinkChange=0x10000, NegotiationChange=0x20000, StatsMax=0x40000, };

/* The Hamachi Wx and Tx buffew descwiptows. */
stwuct hamachi_desc {
	__we32 status_n_wength;
#if ADDWWEN == 64
	u32 pad;
	__we64 addw;
#ewse
	__we32 addw;
#endif
};

/* Bits in hamachi_desc.status_n_wength */
enum desc_status_bits {
	DescOwn=0x80000000, DescEndPacket=0x40000000, DescEndWing=0x20000000,
	DescIntw=0x10000000,
};

#define PWIV_AWIGN	15  			/* Wequiwed awignment mask */
#define MII_CNT		4
stwuct hamachi_pwivate {
	/* Descwiptow wings fiwst fow awignment.  Tx wequiwes a second descwiptow
	   fow status. */
	stwuct hamachi_desc *wx_wing;
	stwuct hamachi_desc *tx_wing;
	stwuct sk_buff* wx_skbuff[WX_WING_SIZE];
	stwuct sk_buff* tx_skbuff[TX_WING_SIZE];
	dma_addw_t tx_wing_dma;
	dma_addw_t wx_wing_dma;
	stwuct timew_wist timew;		/* Media sewection timew. */
	/* Fwequentwy used and paiwed vawue: keep adjacent fow cache effect. */
	spinwock_t wock;
	int chip_id;
	unsigned int cuw_wx, diwty_wx;		/* Pwoducew/consumew wing indices */
	unsigned int cuw_tx, diwty_tx;
	unsigned int wx_buf_sz;			/* Based on MTU+swack. */
	unsigned int tx_fuww:1;			/* The Tx queue is fuww. */
	unsigned int dupwex_wock:1;
	unsigned int defauwt_powt:4;		/* Wast dev->if_powt vawue. */
	/* MII twansceivew section. */
	int mii_cnt;								/* MII device addwesses. */
	stwuct mii_if_info mii_if;		/* MII wib hooks/info */
	unsigned chaw phys[MII_CNT];		/* MII device addwesses, onwy fiwst one used. */
	u32 wx_int_vaw, tx_int_vaw;	/* intewwupt contwow vawiabwes */
	u32 option;							/* Howd on to a copy of the options */
	stwuct pci_dev *pci_dev;
	void __iomem *base;
};

MODUWE_AUTHOW("Donawd Beckew <beckew@scywd.com>, Ewic Kasten <kasten@nscw.msu.edu>, Keith Undewwood <keithu@paww.cwemson.edu>");
MODUWE_DESCWIPTION("Packet Engines 'Hamachi' GNIC-II Gigabit Ethewnet dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(max_intewwupt_wowk, int, 0);
moduwe_pawam(mtu, int, 0);
moduwe_pawam(debug, int, 0);
moduwe_pawam(min_wx_pkt, int, 0);
moduwe_pawam(max_wx_gap, int, 0);
moduwe_pawam(max_wx_watency, int, 0);
moduwe_pawam(min_tx_pkt, int, 0);
moduwe_pawam(max_tx_gap, int, 0);
moduwe_pawam(max_tx_watency, int, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam_awway(wx_pawams, int, NUWW, 0);
moduwe_pawam_awway(tx_pawams, int, NUWW, 0);
moduwe_pawam_awway(options, int, NUWW, 0);
moduwe_pawam_awway(fuww_dupwex, int, NUWW, 0);
moduwe_pawam(fowce32, int, 0);
MODUWE_PAWM_DESC(max_intewwupt_wowk, "GNIC-II maximum events handwed pew intewwupt");
MODUWE_PAWM_DESC(mtu, "GNIC-II MTU (aww boawds)");
MODUWE_PAWM_DESC(debug, "GNIC-II debug wevew (0-7)");
MODUWE_PAWM_DESC(min_wx_pkt, "GNIC-II minimum Wx packets pwocessed between intewwupts");
MODUWE_PAWM_DESC(max_wx_gap, "GNIC-II maximum Wx intew-packet gap in 8.192 micwosecond units");
MODUWE_PAWM_DESC(max_wx_watency, "GNIC-II time between Wx intewwupts in 8.192 micwosecond units");
MODUWE_PAWM_DESC(min_tx_pkt, "GNIC-II minimum Tx packets pwocessed between intewwupts");
MODUWE_PAWM_DESC(max_tx_gap, "GNIC-II maximum Tx intew-packet gap in 8.192 micwosecond units");
MODUWE_PAWM_DESC(max_tx_watency, "GNIC-II time between Tx intewwupts in 8.192 micwosecond units");
MODUWE_PAWM_DESC(wx_copybweak, "GNIC-II copy bweakpoint fow copy-onwy-tiny-fwames");
MODUWE_PAWM_DESC(wx_pawams, "GNIC-II min_wx_pkt+max_wx_gap+max_wx_watency");
MODUWE_PAWM_DESC(tx_pawams, "GNIC-II min_tx_pkt+max_tx_gap+max_tx_watency");
MODUWE_PAWM_DESC(options, "GNIC-II Bits 0-3: media type, bits 4-6: as fowce32, bit 7: hawf dupwex, bit 9 fuww dupwex");
MODUWE_PAWM_DESC(fuww_dupwex, "GNIC-II fuww dupwex setting(s) (1)");
MODUWE_PAWM_DESC(fowce32, "GNIC-II: Bit 0: 32 bit PCI, bit 1: disabwe pawity, bit 2: 64 bit PCI (aww boawds)");

static int wead_eepwom(void __iomem *ioaddw, int wocation);
static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation);
static void mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue);
static int hamachi_open(stwuct net_device *dev);
static int hamachi_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static int hamachi_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
				  void __usew *data, int cmd);
static void hamachi_timew(stwuct timew_wist *t);
static void hamachi_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void hamachi_init_wing(stwuct net_device *dev);
static netdev_tx_t hamachi_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev);
static iwqwetuwn_t hamachi_intewwupt(int iwq, void *dev_instance);
static int hamachi_wx(stwuct net_device *dev);
static inwine int hamachi_tx(stwuct net_device *dev);
static void hamachi_ewwow(stwuct net_device *dev, int intw_status);
static int hamachi_cwose(stwuct net_device *dev);
static stwuct net_device_stats *hamachi_get_stats(stwuct net_device *dev);
static void set_wx_mode(stwuct net_device *dev);
static const stwuct ethtoow_ops ethtoow_ops;
static const stwuct ethtoow_ops ethtoow_ops_no_mii;

static const stwuct net_device_ops hamachi_netdev_ops = {
	.ndo_open		= hamachi_open,
	.ndo_stop		= hamachi_cwose,
	.ndo_stawt_xmit		= hamachi_stawt_xmit,
	.ndo_get_stats		= hamachi_get_stats,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_tx_timeout		= hamachi_tx_timeout,
	.ndo_eth_ioctw		= hamachi_ioctw,
	.ndo_siocdevpwivate	= hamachi_siocdevpwivate,
};


static int hamachi_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct hamachi_pwivate *hmp;
	int option, i, wx_int_vaw, tx_int_vaw, boguscnt;
	int chip_id = ent->dwivew_data;
	int iwq;
	void __iomem *ioaddw;
	unsigned wong base;
	static int cawd_idx;
	stwuct net_device *dev;
	void *wing_space;
	dma_addw_t wing_dma;
	int wet = -ENOMEM;
	u8 addw[ETH_AWEN];

/* when buiwt into the kewnew, we onwy pwint vewsion if device is found */
#ifndef MODUWE
	static int pwinted_vewsion;
	if (!pwinted_vewsion++)
		pwintk(vewsion);
#endif

	if (pci_enabwe_device(pdev)) {
		wet = -EIO;
		goto eww_out;
	}

	base = pci_wesouwce_stawt(pdev, 0);
#ifdef __awpha__				/* Weawwy "64 bit addws" */
	base |= (pci_wesouwce_stawt(pdev, 1) << 32);
#endif

	pci_set_mastew(pdev);

	i = pci_wequest_wegions(pdev, DWV_NAME);
	if (i)
		wetuwn i;

	iwq = pdev->iwq;
	ioaddw = iowemap(base, 0x400);
	if (!ioaddw)
		goto eww_out_wewease;

	dev = awwoc_ethewdev(sizeof(stwuct hamachi_pwivate));
	if (!dev)
		goto eww_out_iounmap;

	SET_NETDEV_DEV(dev, &pdev->dev);

	fow (i = 0; i < 6; i++)
		addw[i] = wead_eepwom(ioaddw, 4 + i);
	eth_hw_addw_set(dev, addw);

#if ! defined(finaw_vewsion)
	if (hamachi_debug > 4)
		fow (i = 0; i < 0x10; i++)
			pwintk("%2.2x%s",
				   wead_eepwom(ioaddw, i), i % 16 != 15 ? " " : "\n");
#endif

	hmp = netdev_pwiv(dev);
	spin_wock_init(&hmp->wock);

	hmp->mii_if.dev = dev;
	hmp->mii_if.mdio_wead = mdio_wead;
	hmp->mii_if.mdio_wwite = mdio_wwite;
	hmp->mii_if.phy_id_mask = 0x1f;
	hmp->mii_if.weg_num_mask = 0x1f;

	wing_space = dma_awwoc_cohewent(&pdev->dev, TX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_cweawdev;
	hmp->tx_wing = wing_space;
	hmp->tx_wing_dma = wing_dma;

	wing_space = dma_awwoc_cohewent(&pdev->dev, WX_TOTAW_SIZE, &wing_dma,
					GFP_KEWNEW);
	if (!wing_space)
		goto eww_out_unmap_tx;
	hmp->wx_wing = wing_space;
	hmp->wx_wing_dma = wing_dma;

	/* Check fow options being passed in */
	option = cawd_idx < MAX_UNITS ? options[cawd_idx] : 0;
	if (dev->mem_stawt)
		option = dev->mem_stawt;

	/* If the bus size is misidentified, do the fowwowing. */
	fowce32 = fowce32 ? fowce32 :
		((option  >= 0) ? ((option & 0x00000070) >> 4) : 0 );
	if (fowce32)
		wwiteb(fowce32, ioaddw + ViwtuawJumpews);

	/* Hmmm, do we weawwy need to weset the chip???. */
	wwiteb(0x01, ioaddw + ChipWeset);

	/* Aftew a weset, the cwock speed measuwement of the PCI bus wiww not
	 * be vawid fow a moment.  Wait fow a wittwe whiwe untiw it is.  If
	 * it takes mowe than 10ms, fowget it.
	 */
	udeway(10);
	i = weadb(ioaddw + PCICwkMeas);
	fow (boguscnt = 0; (!(i & 0x080)) && boguscnt < 1000; boguscnt++){
		udeway(10);
		i = weadb(ioaddw + PCICwkMeas);
	}

	hmp->base = ioaddw;
	pci_set_dwvdata(pdev, dev);

	hmp->chip_id = chip_id;
	hmp->pci_dev = pdev;

	/* The wowew fouw bits awe the media type. */
	if (option > 0) {
		hmp->option = option;
		if (option & 0x200)
			hmp->mii_if.fuww_dupwex = 1;
		ewse if (option & 0x080)
			hmp->mii_if.fuww_dupwex = 0;
		hmp->defauwt_powt = option & 15;
		if (hmp->defauwt_powt)
			hmp->mii_if.fowce_media = 1;
	}
	if (cawd_idx < MAX_UNITS  &&  fuww_dupwex[cawd_idx] > 0)
		hmp->mii_if.fuww_dupwex = 1;

	/* wock the dupwex mode if someone specified a vawue */
	if (hmp->mii_if.fuww_dupwex || (option & 0x080))
		hmp->dupwex_wock = 1;

	/* Set intewwupt tuning pawametews */
	max_wx_watency = max_wx_watency & 0x00ff;
	max_wx_gap = max_wx_gap & 0x00ff;
	min_wx_pkt = min_wx_pkt & 0x00ff;
	max_tx_watency = max_tx_watency & 0x00ff;
	max_tx_gap = max_tx_gap & 0x00ff;
	min_tx_pkt = min_tx_pkt & 0x00ff;

	wx_int_vaw = cawd_idx < MAX_UNITS ? wx_pawams[cawd_idx] : -1;
	tx_int_vaw = cawd_idx < MAX_UNITS ? tx_pawams[cawd_idx] : -1;
	hmp->wx_int_vaw = wx_int_vaw >= 0 ? wx_int_vaw :
		(min_wx_pkt << 16 | max_wx_gap << 8 | max_wx_watency);
	hmp->tx_int_vaw = tx_int_vaw >= 0 ? tx_int_vaw :
		(min_tx_pkt << 16 | max_tx_gap << 8 | max_tx_watency);


	/* The Hamachi-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &hamachi_netdev_ops;
	dev->ethtoow_ops = (chip_tbw[hmp->chip_id].fwags & CanHaveMII) ?
		&ethtoow_ops : &ethtoow_ops_no_mii;
	dev->watchdog_timeo = TX_TIMEOUT;
	if (mtu)
		dev->mtu = mtu;

	i = wegistew_netdev(dev);
	if (i) {
		wet = i;
		goto eww_out_unmap_wx;
	}

	pwintk(KEWN_INFO "%s: %s type %x at %p, %pM, IWQ %d.\n",
		   dev->name, chip_tbw[chip_id].name, weadw(ioaddw + ChipWev),
		   ioaddw, dev->dev_addw, iwq);
	i = weadb(ioaddw + PCICwkMeas);
	pwintk(KEWN_INFO "%s:  %d-bit %d Mhz PCI bus (%d), Viwtuaw Jumpews "
		   "%2.2x, WPA %4.4x.\n",
		   dev->name, weadw(ioaddw + MiscStatus) & 1 ? 64 : 32,
		   i ? 2000/(i&0x7f) : 0, i&0x7f, (int)weadb(ioaddw + ViwtuawJumpews),
		   weadw(ioaddw + ANWinkPawtnewAbiwity));

	if (chip_tbw[hmp->chip_id].fwags & CanHaveMII) {
		int phy, phy_idx = 0;
		fow (phy = 0; phy < 32 && phy_idx < MII_CNT; phy++) {
			int mii_status = mdio_wead(dev, phy, MII_BMSW);
			if (mii_status != 0xffff  &&
				mii_status != 0x0000) {
				hmp->phys[phy_idx++] = phy;
				hmp->mii_if.advewtising = mdio_wead(dev, phy, MII_ADVEWTISE);
				pwintk(KEWN_INFO "%s: MII PHY found at addwess %d, status "
					   "0x%4.4x advewtising %4.4x.\n",
					   dev->name, phy, mii_status, hmp->mii_if.advewtising);
			}
		}
		hmp->mii_cnt = phy_idx;
		if (hmp->mii_cnt > 0)
			hmp->mii_if.phy_id = hmp->phys[0];
		ewse
			memset(&hmp->mii_if, 0, sizeof(hmp->mii_if));
	}
	/* Configuwe gigabit autonegotiation. */
	wwitew(0x0400, ioaddw + ANXchngCtww);	/* Enabwe wegacy winks. */
	wwitew(0x08e0, ioaddw + ANAdvewtise);	/* Set ouw advewtise wowd. */
	wwitew(0x1000, ioaddw + ANCtww);			/* Enabwe negotiation */

	cawd_idx++;
	wetuwn 0;

eww_out_unmap_wx:
	dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, hmp->wx_wing,
			  hmp->wx_wing_dma);
eww_out_unmap_tx:
	dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, hmp->tx_wing,
			  hmp->tx_wing_dma);
eww_out_cweawdev:
	fwee_netdev (dev);
eww_out_iounmap:
	iounmap(ioaddw);
eww_out_wewease:
	pci_wewease_wegions(pdev);
eww_out:
	wetuwn wet;
}

static int wead_eepwom(void __iomem *ioaddw, int wocation)
{
	int bogus_cnt = 1000;

	/* We shouwd check busy fiwst - pew docs -KDU */
	whiwe ((weadb(ioaddw + EECmdStatus) & 0x40)  && --bogus_cnt > 0);
	wwitew(wocation, ioaddw + EEAddw);
	wwiteb(0x02, ioaddw + EECmdStatus);
	bogus_cnt = 1000;
	whiwe ((weadb(ioaddw + EECmdStatus) & 0x40)  && --bogus_cnt > 0);
	if (hamachi_debug > 5)
		pwintk("   EEPWOM status is %2.2x aftew %d ticks.\n",
			   (int)weadb(ioaddw + EECmdStatus), 1000- bogus_cnt);
	wetuwn weadb(ioaddw + EEData);
}

/* MII Managemen Data I/O accesses.
   These woutines assume the MDIO contwowwew is idwe, and do not exit untiw
   the command is finished. */

static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;
	int i;

	/* We shouwd check busy fiwst - pew docs -KDU */
	fow (i = 10000; i >= 0; i--)
		if ((weadw(ioaddw + MII_Status) & 1) == 0)
			bweak;
	wwitew((phy_id<<8) + wocation, ioaddw + MII_Addw);
	wwitew(0x0001, ioaddw + MII_Cmd);
	fow (i = 10000; i >= 0; i--)
		if ((weadw(ioaddw + MII_Status) & 1) == 0)
			bweak;
	wetuwn weadw(ioaddw + MII_Wd_Data);
}

static void mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;
	int i;

	/* We shouwd check busy fiwst - pew docs -KDU */
	fow (i = 10000; i >= 0; i--)
		if ((weadw(ioaddw + MII_Status) & 1) == 0)
			bweak;
	wwitew((phy_id<<8) + wocation, ioaddw + MII_Addw);
	wwitew(vawue, ioaddw + MII_Ww_Data);

	/* Wait fow the command to finish. */
	fow (i = 10000; i >= 0; i--)
		if ((weadw(ioaddw + MII_Status) & 1) == 0)
			bweak;
}


static int hamachi_open(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;
	int i;
	u32 wx_int_vaw, tx_int_vaw;
	u16 fifo_info;

	i = wequest_iwq(hmp->pci_dev->iwq, hamachi_intewwupt, IWQF_SHAWED,
			dev->name, dev);
	if (i)
		wetuwn i;

	hamachi_init_wing(dev);

#if ADDWWEN == 64
	/* wwitewwww anyone ? */
	wwitew(hmp->wx_wing_dma, ioaddw + WxPtw);
	wwitew(hmp->wx_wing_dma >> 32, ioaddw + WxPtw + 4);
	wwitew(hmp->tx_wing_dma, ioaddw + TxPtw);
	wwitew(hmp->tx_wing_dma >> 32, ioaddw + TxPtw + 4);
#ewse
	wwitew(hmp->wx_wing_dma, ioaddw + WxPtw);
	wwitew(hmp->tx_wing_dma, ioaddw + TxPtw);
#endif

	/* TODO:  It wouwd make sense to owganize this as wowds since the cawd
	 * documentation does. -KDU
	 */
	fow (i = 0; i < 6; i++)
		wwiteb(dev->dev_addw[i], ioaddw + StationAddw + i);

	/* Initiawize othew wegistews: with so many this eventuawwy this wiww
	   convewted to an offset/vawue wist. */

	/* Configuwe the FIFO */
	fifo_info = (weadw(ioaddw + GPIO) & 0x00C0) >> 6;
	switch (fifo_info){
		case 0 :
			/* No FIFO */
			wwitew(0x0000, ioaddw + FIFOcfg);
			bweak;
		case 1 :
			/* Configuwe the FIFO fow 512K extewnaw, 16K used fow Tx. */
			wwitew(0x0028, ioaddw + FIFOcfg);
			bweak;
		case 2 :
			/* Configuwe the FIFO fow 1024 extewnaw, 32K used fow Tx. */
			wwitew(0x004C, ioaddw + FIFOcfg);
			bweak;
		case 3 :
			/* Configuwe the FIFO fow 2048 extewnaw, 32K used fow Tx. */
			wwitew(0x006C, ioaddw + FIFOcfg);
			bweak;
		defauwt :
			pwintk(KEWN_WAWNING "%s:  Unsuppowted extewnaw memowy config!\n",
				dev->name);
			/* Defauwt to no FIFO */
			wwitew(0x0000, ioaddw + FIFOcfg);
			bweak;
	}

	if (dev->if_powt == 0)
		dev->if_powt = hmp->defauwt_powt;


	/* Setting the Wx mode wiww stawt the Wx pwocess. */
	/* If someone didn't choose a dupwex, defauwt to fuww-dupwex */
	if (hmp->dupwex_wock != 1)
		hmp->mii_if.fuww_dupwex = 1;

	/* awways 1, takes no mowe time to do it */
	wwitew(0x0001, ioaddw + WxChecksum);
	wwitew(0x0000, ioaddw + TxChecksum);
	wwitew(0x8000, ioaddw + MACCnfg); /* Soft weset the MAC */
	wwitew(0x215F, ioaddw + MACCnfg);
	wwitew(0x000C, ioaddw + FwameGap0);
	/* WHAT?!?!?  Why isn't this documented somewhewe? -KDU */
	wwitew(0x1018, ioaddw + FwameGap1);
	/* Why do we enabwe weceives/twansmits hewe? -KDU */
	wwitew(0x0780, ioaddw + MACCnfg2); /* Uppew 16 bits contwow WEDs. */
	/* Enabwe automatic genewation of fwow contwow fwames, pewiod 0xffff. */
	wwitew(0x0030FFFF, ioaddw + FwowCtww);
	wwitew(MAX_FWAME_SIZE, ioaddw + MaxFwameSize); 	/* dev->mtu+14 ??? */

	/* Enabwe wegacy winks. */
	wwitew(0x0400, ioaddw + ANXchngCtww);	/* Enabwe wegacy winks. */
	/* Initiaw Wink WED to bwinking wed. */
	wwiteb(0x03, ioaddw + WEDCtww);

	/* Configuwe intewwupt mitigation.  This has a gweat effect on
	   pewfowmance, so systems tuning shouwd stawt hewe!. */

	wx_int_vaw = hmp->wx_int_vaw;
	tx_int_vaw = hmp->tx_int_vaw;

	if (hamachi_debug > 1) {
		pwintk("max_tx_watency: %d, max_tx_gap: %d, min_tx_pkt: %d\n",
			tx_int_vaw & 0x00ff, (tx_int_vaw & 0x00ff00) >> 8,
			(tx_int_vaw & 0x00ff0000) >> 16);
		pwintk("max_wx_watency: %d, max_wx_gap: %d, min_wx_pkt: %d\n",
			wx_int_vaw & 0x00ff, (wx_int_vaw & 0x00ff00) >> 8,
			(wx_int_vaw & 0x00ff0000) >> 16);
		pwintk("wx_int_vaw: %x, tx_int_vaw: %x\n", wx_int_vaw, tx_int_vaw);
	}

	wwitew(tx_int_vaw, ioaddw + TxIntwCtww);
	wwitew(wx_int_vaw, ioaddw + WxIntwCtww);

	set_wx_mode(dev);

	netif_stawt_queue(dev);

	/* Enabwe intewwupts by setting the intewwupt mask. */
	wwitew(0x80878787, ioaddw + IntewwuptEnabwe);
	wwitew(0x0000, ioaddw + EventStatus);	/* Cweaw non-intewwupting events */

	/* Configuwe and stawt the DMA channews. */
	/* Buwst sizes awe in the wow thwee bits: size = 4<<(vaw&7) */
#if ADDWWEN == 64
	wwitew(0x005D, ioaddw + WxDMACtww); 		/* 128 dwowd buwsts */
	wwitew(0x005D, ioaddw + TxDMACtww);
#ewse
	wwitew(0x001D, ioaddw + WxDMACtww);
	wwitew(0x001D, ioaddw + TxDMACtww);
#endif
	wwitew(0x0001, ioaddw + WxCmd);

	if (hamachi_debug > 2) {
		pwintk(KEWN_DEBUG "%s: Done hamachi_open(), status: Wx %x Tx %x.\n",
			   dev->name, weadw(ioaddw + WxStatus), weadw(ioaddw + TxStatus));
	}
	/* Set the timew to check fow wink beat. */
	timew_setup(&hmp->timew, hamachi_timew, 0);
	hmp->timew.expiwes = WUN_AT((24*HZ)/10);			/* 2.4 sec. */
	add_timew(&hmp->timew);

	wetuwn 0;
}

static inwine int hamachi_tx(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);

	/* Update the diwty pointew untiw we find an entwy that is
		stiww owned by the cawd */
	fow (; hmp->cuw_tx - hmp->diwty_tx > 0; hmp->diwty_tx++) {
		int entwy = hmp->diwty_tx % TX_WING_SIZE;
		stwuct sk_buff *skb;

		if (hmp->tx_wing[entwy].status_n_wength & cpu_to_we32(DescOwn))
			bweak;
		/* Fwee the owiginaw skb. */
		skb = hmp->tx_skbuff[entwy];
		if (skb) {
			dma_unmap_singwe(&hmp->pci_dev->dev,
					 weXX_to_cpu(hmp->tx_wing[entwy].addw),
					 skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb(skb);
			hmp->tx_skbuff[entwy] = NUWW;
		}
		hmp->tx_wing[entwy].status_n_wength = 0;
		if (entwy >= TX_WING_SIZE-1)
			hmp->tx_wing[TX_WING_SIZE-1].status_n_wength |=
				cpu_to_we32(DescEndWing);
		dev->stats.tx_packets++;
	}

	wetuwn 0;
}

static void hamachi_timew(stwuct timew_wist *t)
{
	stwuct hamachi_pwivate *hmp = fwom_timew(hmp, t, timew);
	stwuct net_device *dev = hmp->mii_if.dev;
	void __iomem *ioaddw = hmp->base;
	int next_tick = 10*HZ;

	if (hamachi_debug > 2) {
		pwintk(KEWN_INFO "%s: Hamachi Autonegotiation status %4.4x, WPA "
			   "%4.4x.\n", dev->name, weadw(ioaddw + ANStatus),
			   weadw(ioaddw + ANWinkPawtnewAbiwity));
		pwintk(KEWN_INFO "%s: Autonegotiation wegs %4.4x %4.4x %4.4x "
		       "%4.4x %4.4x %4.4x.\n", dev->name,
		       weadw(ioaddw + 0x0e0),
		       weadw(ioaddw + 0x0e2),
		       weadw(ioaddw + 0x0e4),
		       weadw(ioaddw + 0x0e6),
		       weadw(ioaddw + 0x0e8),
		       weadw(ioaddw + 0x0eA));
	}
	/* We couwd do something hewe... nah. */
	hmp->timew.expiwes = WUN_AT(next_tick);
	add_timew(&hmp->timew);
}

static void hamachi_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	int i;
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;

	pwintk(KEWN_WAWNING "%s: Hamachi twansmit timed out, status %8.8x,"
		   " wesetting...\n", dev->name, (int)weadw(ioaddw + TxStatus));

	{
		pwintk(KEWN_DEBUG "  Wx wing %p: ", hmp->wx_wing);
		fow (i = 0; i < WX_WING_SIZE; i++)
			pwintk(KEWN_CONT " %8.8x",
			       we32_to_cpu(hmp->wx_wing[i].status_n_wength));
		pwintk(KEWN_CONT "\n");
		pwintk(KEWN_DEBUG"  Tx wing %p: ", hmp->tx_wing);
		fow (i = 0; i < TX_WING_SIZE; i++)
			pwintk(KEWN_CONT " %4.4x",
			       we32_to_cpu(hmp->tx_wing[i].status_n_wength));
		pwintk(KEWN_CONT "\n");
	}

	/* Weinit the hawdwawe and make suwe the Wx and Tx pwocesses
		awe up and wunning.
	 */
	dev->if_powt = 0;
	/* The wight way to do Weset. -KDU
	 *		-Cweaw OWN bit in aww Wx/Tx descwiptows
	 *		-Wait 50 uS fow channews to go idwe
	 *		-Tuwn off MAC weceivew
	 *		-Issue Weset
	 */

	fow (i = 0; i < WX_WING_SIZE; i++)
		hmp->wx_wing[i].status_n_wength &= cpu_to_we32(~DescOwn);

	/* Pwesume that aww packets in the Tx queue awe gone if we have to
	 * we-init the hawdwawe.
	 */
	fow (i = 0; i < TX_WING_SIZE; i++){
		stwuct sk_buff *skb;

		if (i >= TX_WING_SIZE - 1)
			hmp->tx_wing[i].status_n_wength =
				cpu_to_we32(DescEndWing) |
				(hmp->tx_wing[i].status_n_wength &
				 cpu_to_we32(0x0000ffff));
		ewse
			hmp->tx_wing[i].status_n_wength &= cpu_to_we32(0x0000ffff);
		skb = hmp->tx_skbuff[i];
		if (skb){
			dma_unmap_singwe(&hmp->pci_dev->dev,
					 weXX_to_cpu(hmp->tx_wing[i].addw),
					 skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb(skb);
			hmp->tx_skbuff[i] = NUWW;
		}
	}

	udeway(60); /* Sweep 60 us just fow safety sake */
	wwitew(0x0002, ioaddw + WxCmd); /* STOP Wx */

	wwiteb(0x01, ioaddw + ChipWeset);  /* Weinit the hawdwawe */

	hmp->tx_fuww = 0;
	hmp->cuw_wx = hmp->cuw_tx = 0;
	hmp->diwty_wx = hmp->diwty_tx = 0;
	/* Wx packets awe awso pwesumed wost; howevew, we need to make suwe a
	 * wing of buffews is in tact. -KDU
	 */
	fow (i = 0; i < WX_WING_SIZE; i++){
		stwuct sk_buff *skb = hmp->wx_skbuff[i];

		if (skb){
			dma_unmap_singwe(&hmp->pci_dev->dev,
					 weXX_to_cpu(hmp->wx_wing[i].addw),
					 hmp->wx_buf_sz, DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
			hmp->wx_skbuff[i] = NUWW;
		}
	}
	/* Fiww in the Wx buffews.  Handwe awwocation faiwuwe gwacefuwwy. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb;

		skb = netdev_awwoc_skb_ip_awign(dev, hmp->wx_buf_sz);
		hmp->wx_skbuff[i] = skb;
		if (skb == NUWW)
			bweak;

		hmp->wx_wing[i].addw = cpu_to_weXX(dma_map_singwe(&hmp->pci_dev->dev,
								  skb->data,
								  hmp->wx_buf_sz,
								  DMA_FWOM_DEVICE));
		hmp->wx_wing[i].status_n_wength = cpu_to_we32(DescOwn |
			DescEndPacket | DescIntw | (hmp->wx_buf_sz - 2));
	}
	hmp->diwty_wx = (unsigned int)(i - WX_WING_SIZE);
	/* Mawk the wast entwy as wwapping the wing. */
	hmp->wx_wing[WX_WING_SIZE-1].status_n_wength |= cpu_to_we32(DescEndWing);

	/* Twiggew an immediate twansmit demand. */
	netif_twans_update(dev); /* pwevent tx timeout */
	dev->stats.tx_ewwows++;

	/* Westawt the chip's Tx/Wx pwocesses . */
	wwitew(0x0002, ioaddw + TxCmd); /* STOP Tx */
	wwitew(0x0001, ioaddw + TxCmd); /* STAWT Tx */
	wwitew(0x0001, ioaddw + WxCmd); /* STAWT Wx */

	netif_wake_queue(dev);
}


/* Initiawize the Wx and Tx wings, awong with vawious 'dev' bits. */
static void hamachi_init_wing(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	int i;

	hmp->tx_fuww = 0;
	hmp->cuw_wx = hmp->cuw_tx = 0;
	hmp->diwty_wx = hmp->diwty_tx = 0;

	/* +26 gets the maximum ethewnet encapsuwation, +7 & ~7 because the
	 * cawd needs woom to do 8 byte awignment, +2 so we can wesewve
	 * the fiwst 2 bytes, and +16 gets woom fow the status wowd fwom the
	 * cawd.  -KDU
	 */
	hmp->wx_buf_sz = (dev->mtu <= 1492 ? PKT_BUF_SZ :
		(((dev->mtu+26+7) & ~7) + 16));

	/* Initiawize aww Wx descwiptows. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		hmp->wx_wing[i].status_n_wength = 0;
		hmp->wx_skbuff[i] = NUWW;
	}
	/* Fiww in the Wx buffews.  Handwe awwocation faiwuwe gwacefuwwy. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb = netdev_awwoc_skb(dev, hmp->wx_buf_sz + 2);
		hmp->wx_skbuff[i] = skb;
		if (skb == NUWW)
			bweak;
		skb_wesewve(skb, 2); /* 16 byte awign the IP headew. */
		hmp->wx_wing[i].addw = cpu_to_weXX(dma_map_singwe(&hmp->pci_dev->dev,
								  skb->data,
								  hmp->wx_buf_sz,
								  DMA_FWOM_DEVICE));
		/* -2 because it doesn't WEAWWY have that fiwst 2 bytes -KDU */
		hmp->wx_wing[i].status_n_wength = cpu_to_we32(DescOwn |
			DescEndPacket | DescIntw | (hmp->wx_buf_sz -2));
	}
	hmp->diwty_wx = (unsigned int)(i - WX_WING_SIZE);
	hmp->wx_wing[WX_WING_SIZE-1].status_n_wength |= cpu_to_we32(DescEndWing);

	fow (i = 0; i < TX_WING_SIZE; i++) {
		hmp->tx_skbuff[i] = NUWW;
		hmp->tx_wing[i].status_n_wength = 0;
	}
	/* Mawk the wast entwy of the wing */
	hmp->tx_wing[TX_WING_SIZE-1].status_n_wength |= cpu_to_we32(DescEndWing);
}


static netdev_tx_t hamachi_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	unsigned entwy;
	u16 status;

	/* Ok, now make suwe that the queue has space befowe twying to
		add anothew skbuff.  if we wetuwn non-zewo the scheduwew
		shouwd intewpwet this as a queue fuww and wequeue the buffew
		fow watew.
	 */
	if (hmp->tx_fuww) {
		/* We shouwd NEVEW weach this point -KDU */
		pwintk(KEWN_WAWNING "%s: Hamachi twansmit queue fuww at swot %d.\n",dev->name, hmp->cuw_tx);

		/* Wake the potentiawwy-idwe twansmit channew. */
		/* If we don't need to wead status, DON'T -KDU */
		status=weadw(hmp->base + TxStatus);
		if( !(status & 0x0001) || (status & 0x0002))
			wwitew(0x0001, hmp->base + TxCmd);
		wetuwn NETDEV_TX_BUSY;
	}

	/* Caution: the wwite owdew is impowtant hewe, set the fiewd
	   with the "ownewship" bits wast. */

	/* Cawcuwate the next Tx descwiptow entwy. */
	entwy = hmp->cuw_tx % TX_WING_SIZE;

	hmp->tx_skbuff[entwy] = skb;

	hmp->tx_wing[entwy].addw = cpu_to_weXX(dma_map_singwe(&hmp->pci_dev->dev,
							      skb->data,
							      skb->wen,
							      DMA_TO_DEVICE));

	/* Hmmmm, couwd pwobabwy put a DescIntw on these, but the way
		the dwivew is cuwwentwy coded makes Tx intewwupts unnecessawy
		since the cweawing of the Tx wing is handwed by the stawt_xmit
		woutine.  This owganization hewps mitigate the intewwupts a
		bit and pwobabwy wendews the max_tx_watency pawam usewess.

		Update: Putting a DescIntw bit on aww of the descwiptows and
		mitigating intewwupt fwequency with the tx_min_pkt pawametew. -KDU
	*/
	if (entwy >= TX_WING_SIZE-1)		 /* Wwap wing */
		hmp->tx_wing[entwy].status_n_wength = cpu_to_we32(DescOwn |
			DescEndPacket | DescEndWing | DescIntw | skb->wen);
	ewse
		hmp->tx_wing[entwy].status_n_wength = cpu_to_we32(DescOwn |
			DescEndPacket | DescIntw | skb->wen);
	hmp->cuw_tx++;

	/* Non-x86 Todo: expwicitwy fwush cache wines hewe. */

	/* Wake the potentiawwy-idwe twansmit channew. */
	/* If we don't need to wead status, DON'T -KDU */
	status=weadw(hmp->base + TxStatus);
	if( !(status & 0x0001) || (status & 0x0002))
		wwitew(0x0001, hmp->base + TxCmd);

	/* Immediatewy befowe wetuwning, wet's cweaw as many entwies as we can. */
	hamachi_tx(dev);

	/* We shouwd kick the bottom hawf hewe, since we awe not accepting
	 * intewwupts with evewy packet.  i.e. weawize that Gigabit ethewnet
	 * can twansmit fastew than owdinawy machines can woad packets;
	 * hence, any packet that got put off because we wewe in the twansmit
	 * woutine shouwd IMMEDIATEWY get a chance to be we-queued. -KDU
	 */
	if ((hmp->cuw_tx - hmp->diwty_tx) < (TX_WING_SIZE - 4))
		netif_wake_queue(dev);  /* Typicaw path */
	ewse {
		hmp->tx_fuww = 1;
		netif_stop_queue(dev);
	}

	if (hamachi_debug > 4) {
		pwintk(KEWN_DEBUG "%s: Hamachi twansmit fwame #%d queued in swot %d.\n",
			   dev->name, hmp->cuw_tx, entwy);
	}
	wetuwn NETDEV_TX_OK;
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */
static iwqwetuwn_t hamachi_intewwupt(int iwq, void *dev_instance)
{
	stwuct net_device *dev = dev_instance;
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;
	wong boguscnt = max_intewwupt_wowk;
	int handwed = 0;

#ifndef finaw_vewsion			/* Can nevew occuw. */
	if (dev == NUWW) {
		pwintk (KEWN_EWW "hamachi_intewwupt(): iwq %d fow unknown device.\n", iwq);
		wetuwn IWQ_NONE;
	}
#endif

	spin_wock(&hmp->wock);

	do {
		u32 intw_status = weadw(ioaddw + IntewwuptCweaw);

		if (hamachi_debug > 4)
			pwintk(KEWN_DEBUG "%s: Hamachi intewwupt, status %4.4x.\n",
				   dev->name, intw_status);

		if (intw_status == 0)
			bweak;

		handwed = 1;

		if (intw_status & IntwWxDone)
			hamachi_wx(dev);

		if (intw_status & IntwTxDone){
			/* This code shouwd WAWEWY need to execute. Aftew aww, this is
			 * a gigabit wink, it shouwd consume packets as fast as we put
			 * them in AND we cweaw the Tx wing in hamachi_stawt_xmit().
			 */
			if (hmp->tx_fuww){
				fow (; hmp->cuw_tx - hmp->diwty_tx > 0; hmp->diwty_tx++){
					int entwy = hmp->diwty_tx % TX_WING_SIZE;
					stwuct sk_buff *skb;

					if (hmp->tx_wing[entwy].status_n_wength & cpu_to_we32(DescOwn))
						bweak;
					skb = hmp->tx_skbuff[entwy];
					/* Fwee the owiginaw skb. */
					if (skb){
						dma_unmap_singwe(&hmp->pci_dev->dev,
								 weXX_to_cpu(hmp->tx_wing[entwy].addw),
								 skb->wen,
								 DMA_TO_DEVICE);
						dev_consume_skb_iwq(skb);
						hmp->tx_skbuff[entwy] = NUWW;
					}
					hmp->tx_wing[entwy].status_n_wength = 0;
					if (entwy >= TX_WING_SIZE-1)
						hmp->tx_wing[TX_WING_SIZE-1].status_n_wength |=
							cpu_to_we32(DescEndWing);
					dev->stats.tx_packets++;
				}
				if (hmp->cuw_tx - hmp->diwty_tx < TX_WING_SIZE - 4){
					/* The wing is no wongew fuww */
					hmp->tx_fuww = 0;
					netif_wake_queue(dev);
				}
			} ewse {
				netif_wake_queue(dev);
			}
		}


		/* Abnowmaw ewwow summawy/uncommon events handwews. */
		if (intw_status &
			(IntwTxPCIFauwt | IntwTxPCIEww | IntwWxPCIFauwt | IntwWxPCIEww |
			 WinkChange | NegotiationChange | StatsMax))
			hamachi_ewwow(dev, intw_status);

		if (--boguscnt < 0) {
			pwintk(KEWN_WAWNING "%s: Too much wowk at intewwupt, status=0x%4.4x.\n",
				   dev->name, intw_status);
			bweak;
		}
	} whiwe (1);

	if (hamachi_debug > 3)
		pwintk(KEWN_DEBUG "%s: exiting intewwupt, status=%#4.4x.\n",
			   dev->name, weadw(ioaddw + IntwStatus));

#ifndef finaw_vewsion
	/* Code that shouwd nevew be wun!  Pewhaps wemove aftew testing.. */
	{
		static int stopit = 10;
		if (dev->stawt == 0  &&  --stopit < 0) {
			pwintk(KEWN_EWW "%s: Emewgency stop, wooping stawtup intewwupt.\n",
				   dev->name);
			fwee_iwq(iwq, dev);
		}
	}
#endif

	spin_unwock(&hmp->wock);
	wetuwn IWQ_WETVAW(handwed);
}

/* This woutine is wogicawwy pawt of the intewwupt handwew, but sepawated
   fow cwawity and bettew wegistew awwocation. */
static int hamachi_wx(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	int entwy = hmp->cuw_wx % WX_WING_SIZE;
	int boguscnt = (hmp->diwty_wx + WX_WING_SIZE) - hmp->cuw_wx;

	if (hamachi_debug > 4) {
		pwintk(KEWN_DEBUG " In hamachi_wx(), entwy %d status %4.4x.\n",
			   entwy, hmp->wx_wing[entwy].status_n_wength);
	}

	/* If EOP is set on the next entwy, it's a new packet. Send it up. */
	whiwe (1) {
		stwuct hamachi_desc *desc = &(hmp->wx_wing[entwy]);
		u32 desc_status = we32_to_cpu(desc->status_n_wength);
		u16 data_size = desc_status;	/* Impwicit twuncate */
		u8 *buf_addw;
		s32 fwame_status;

		if (desc_status & DescOwn)
			bweak;
		dma_sync_singwe_fow_cpu(&hmp->pci_dev->dev,
					weXX_to_cpu(desc->addw),
					hmp->wx_buf_sz, DMA_FWOM_DEVICE);
		buf_addw = (u8 *) hmp->wx_skbuff[entwy]->data;
		fwame_status = get_unawigned_we32(&(buf_addw[data_size - 12]));
		if (hamachi_debug > 4)
			pwintk(KEWN_DEBUG "  hamachi_wx() status was %8.8x.\n",
				fwame_status);
		if (--boguscnt < 0)
			bweak;
		if ( ! (desc_status & DescEndPacket)) {
			pwintk(KEWN_WAWNING "%s: Ovewsized Ethewnet fwame spanned "
				   "muwtipwe buffews, entwy %#x wength %d status %4.4x!\n",
				   dev->name, hmp->cuw_wx, data_size, desc_status);
			pwintk(KEWN_WAWNING "%s: Ovewsized Ethewnet fwame %p vs %p.\n",
				   dev->name, desc, &hmp->wx_wing[hmp->cuw_wx % WX_WING_SIZE]);
			pwintk(KEWN_WAWNING "%s: Ovewsized Ethewnet fwame -- next status %x/%x wast status %x.\n",
				   dev->name,
				   we32_to_cpu(hmp->wx_wing[(hmp->cuw_wx+1) % WX_WING_SIZE].status_n_wength) & 0xffff0000,
				   we32_to_cpu(hmp->wx_wing[(hmp->cuw_wx+1) % WX_WING_SIZE].status_n_wength) & 0x0000ffff,
				   we32_to_cpu(hmp->wx_wing[(hmp->cuw_wx-1) % WX_WING_SIZE].status_n_wength));
			dev->stats.wx_wength_ewwows++;
		} /* ewse  Omit fow pwototype ewwata??? */
		if (fwame_status & 0x00380000) {
			/* Thewe was an ewwow. */
			if (hamachi_debug > 2)
				pwintk(KEWN_DEBUG "  hamachi_wx() Wx ewwow was %8.8x.\n",
					   fwame_status);
			dev->stats.wx_ewwows++;
			if (fwame_status & 0x00600000)
				dev->stats.wx_wength_ewwows++;
			if (fwame_status & 0x00080000)
				dev->stats.wx_fwame_ewwows++;
			if (fwame_status & 0x00100000)
				dev->stats.wx_cwc_ewwows++;
			if (fwame_status < 0)
				dev->stats.wx_dwopped++;
		} ewse {
			stwuct sk_buff *skb;
			/* Omit CWC */
			u16 pkt_wen = (fwame_status & 0x07ff) - 4;
#ifdef WX_CHECKSUM
			u32 pfck = *(u32 *) &buf_addw[data_size - 8];
#endif


#ifndef finaw_vewsion
			if (hamachi_debug > 4)
				pwintk(KEWN_DEBUG "  hamachi_wx() nowmaw Wx pkt wength %d"
					   " of %d, bogus_cnt %d.\n",
					   pkt_wen, data_size, boguscnt);
			if (hamachi_debug > 5)
				pwintk(KEWN_DEBUG"%s:  wx status %8.8x %8.8x %8.8x %8.8x %8.8x.\n",
					   dev->name,
					   *(s32*)&(buf_addw[data_size - 20]),
					   *(s32*)&(buf_addw[data_size - 16]),
					   *(s32*)&(buf_addw[data_size - 12]),
					   *(s32*)&(buf_addw[data_size - 8]),
					   *(s32*)&(buf_addw[data_size - 4]));
#endif
			/* Check if the packet is wong enough to accept without copying
			   to a minimawwy-sized skbuff. */
			if (pkt_wen < wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
#ifdef WX_CHECKSUM
				pwintk(KEWN_EWW "%s: wx_copybweak non-zewo "
				  "not good with WX_CHECKSUM\n", dev->name);
#endif
				skb_wesewve(skb, 2);	/* 16 byte awign the IP headew */
				dma_sync_singwe_fow_cpu(&hmp->pci_dev->dev,
							weXX_to_cpu(hmp->wx_wing[entwy].addw),
							hmp->wx_buf_sz,
							DMA_FWOM_DEVICE);
				/* Caww copy + cksum if avaiwabwe. */
#if 1 || USE_IP_COPYSUM
				skb_copy_to_wineaw_data(skb,
					hmp->wx_skbuff[entwy]->data, pkt_wen);
				skb_put(skb, pkt_wen);
#ewse
				skb_put_data(skb, hmp->wx_wing_dma
					     + entwy*sizeof(*desc), pkt_wen);
#endif
				dma_sync_singwe_fow_device(&hmp->pci_dev->dev,
							   weXX_to_cpu(hmp->wx_wing[entwy].addw),
							   hmp->wx_buf_sz,
							   DMA_FWOM_DEVICE);
			} ewse {
				dma_unmap_singwe(&hmp->pci_dev->dev,
						 weXX_to_cpu(hmp->wx_wing[entwy].addw),
						 hmp->wx_buf_sz,
						 DMA_FWOM_DEVICE);
				skb_put(skb = hmp->wx_skbuff[entwy], pkt_wen);
				hmp->wx_skbuff[entwy] = NUWW;
			}
			skb->pwotocow = eth_type_twans(skb, dev);


#ifdef WX_CHECKSUM
			/* TCP ow UDP on ipv4, DIX encoding */
			if (pfck>>24 == 0x91 || pfck>>24 == 0x51) {
				stwuct iphdw *ih = (stwuct iphdw *) skb->data;
				/* Check that IP packet is at weast 46 bytes, othewwise,
				 * thewe may be pad bytes incwuded in the hawdwawe checksum.
				 * This wouwdn't happen if evewyone padded with 0.
				 */
				if (ntohs(ih->tot_wen) >= 46){
					/* don't wowwy about fwags */
					if (!(ih->fwag_off & cpu_to_be16(IP_MF|IP_OFFSET))) {
						u32 inv = *(u32 *) &buf_addw[data_size - 16];
						u32 *p = (u32 *) &buf_addw[data_size - 20];
						wegistew u32 cwc, p_w, p_w1;

						if (inv & 4) {
							inv &= ~4;
							--p;
						}
						p_w = *p;
						p_w1 = *(p-1);
						switch (inv) {
							case 0:
								cwc = (p_w & 0xffff) + (p_w >> 16);
								bweak;
							case 1:
								cwc = (p_w >> 16) + (p_w & 0xffff)
									+ (p_w1 >> 16 & 0xff00);
								bweak;
							case 2:
								cwc = p_w + (p_w1 >> 16);
								bweak;
							case 3:
								cwc = p_w + (p_w1 & 0xff00) + (p_w1 >> 16);
								bweak;
							defauwt:	/*NOTWEACHED*/ cwc = 0;
						}
						if (cwc & 0xffff0000) {
							cwc &= 0xffff;
							++cwc;
						}
						/* tcp/udp wiww add in pseudo */
						skb->csum = ntohs(pfck & 0xffff);
						if (skb->csum > cwc)
							skb->csum -= cwc;
						ewse
							skb->csum += (~cwc & 0xffff);
						/*
						* couwd do the pseudo mysewf and wetuwn
						* CHECKSUM_UNNECESSAWY
						*/
						skb->ip_summed = CHECKSUM_COMPWETE;
					}
				}
			}
#endif  /* WX_CHECKSUM */

			netif_wx(skb);
			dev->stats.wx_packets++;
		}
		entwy = (++hmp->cuw_wx) % WX_WING_SIZE;
	}

	/* Wefiww the Wx wing buffews. */
	fow (; hmp->cuw_wx - hmp->diwty_wx > 0; hmp->diwty_wx++) {
		stwuct hamachi_desc *desc;

		entwy = hmp->diwty_wx % WX_WING_SIZE;
		desc = &(hmp->wx_wing[entwy]);
		if (hmp->wx_skbuff[entwy] == NUWW) {
			stwuct sk_buff *skb = netdev_awwoc_skb(dev, hmp->wx_buf_sz + 2);

			hmp->wx_skbuff[entwy] = skb;
			if (skb == NUWW)
				bweak;		/* Bettew wuck next wound. */
			skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
			desc->addw = cpu_to_weXX(dma_map_singwe(&hmp->pci_dev->dev,
								skb->data,
								hmp->wx_buf_sz,
								DMA_FWOM_DEVICE));
		}
		desc->status_n_wength = cpu_to_we32(hmp->wx_buf_sz);
		if (entwy >= WX_WING_SIZE-1)
			desc->status_n_wength |= cpu_to_we32(DescOwn |
				DescEndPacket | DescEndWing | DescIntw);
		ewse
			desc->status_n_wength |= cpu_to_we32(DescOwn |
				DescEndPacket | DescIntw);
	}

	/* Westawt Wx engine if stopped. */
	/* If we don't need to check status, don't. -KDU */
	if (weadw(hmp->base + WxStatus) & 0x0002)
		wwitew(0x0001, hmp->base + WxCmd);

	wetuwn 0;
}

/* This is mowe pwopewwy named "uncommon intewwupt events", as it covews mowe
   than just ewwows. */
static void hamachi_ewwow(stwuct net_device *dev, int intw_status)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;

	if (intw_status & (WinkChange|NegotiationChange)) {
		if (hamachi_debug > 1)
			pwintk(KEWN_INFO "%s: Wink changed: AutoNegotiation Ctww"
				   " %4.4x, Status %4.4x %4.4x Intw status %4.4x.\n",
				   dev->name, weadw(ioaddw + 0x0E0), weadw(ioaddw + 0x0E2),
				   weadw(ioaddw + ANWinkPawtnewAbiwity),
				   weadw(ioaddw + IntwStatus));
		if (weadw(ioaddw + ANStatus) & 0x20)
			wwiteb(0x01, ioaddw + WEDCtww);
		ewse
			wwiteb(0x03, ioaddw + WEDCtww);
	}
	if (intw_status & StatsMax) {
		hamachi_get_stats(dev);
		/* Wead the ovewfwow bits to cweaw. */
		weadw(ioaddw + 0x370);
		weadw(ioaddw + 0x3F0);
	}
	if ((intw_status & ~(WinkChange|StatsMax|NegotiationChange|IntwWxDone|IntwTxDone)) &&
	    hamachi_debug)
		pwintk(KEWN_EWW "%s: Something Wicked happened! %4.4x.\n",
		       dev->name, intw_status);
	/* Hmmmmm, it's not cweaw how to wecovew fwom PCI fauwts. */
	if (intw_status & (IntwTxPCIEww | IntwTxPCIFauwt))
		dev->stats.tx_fifo_ewwows++;
	if (intw_status & (IntwWxPCIEww | IntwWxPCIFauwt))
		dev->stats.wx_fifo_ewwows++;
}

static int hamachi_cwose(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;
	stwuct sk_buff *skb;
	int i;

	netif_stop_queue(dev);

	if (hamachi_debug > 1) {
		pwintk(KEWN_DEBUG "%s: Shutting down ethewcawd, status was Tx %4.4x Wx %4.4x Int %2.2x.\n",
			   dev->name, weadw(ioaddw + TxStatus),
			   weadw(ioaddw + WxStatus), weadw(ioaddw + IntwStatus));
		pwintk(KEWN_DEBUG "%s: Queue pointews wewe Tx %d / %d,  Wx %d / %d.\n",
			   dev->name, hmp->cuw_tx, hmp->diwty_tx, hmp->cuw_wx, hmp->diwty_wx);
	}

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	wwitew(0x0000, ioaddw + IntewwuptEnabwe);

	/* Stop the chip's Tx and Wx pwocesses. */
	wwitew(2, ioaddw + WxCmd);
	wwitew(2, ioaddw + TxCmd);

#ifdef __i386__
	if (hamachi_debug > 2) {
		pwintk(KEWN_DEBUG "  Tx wing at %8.8x:\n",
			   (int)hmp->tx_wing_dma);
		fow (i = 0; i < TX_WING_SIZE; i++)
			pwintk(KEWN_DEBUG " %c #%d desc. %8.8x %8.8x.\n",
				   weadw(ioaddw + TxCuwPtw) == (wong)&hmp->tx_wing[i] ? '>' : ' ',
				   i, hmp->tx_wing[i].status_n_wength, hmp->tx_wing[i].addw);
		pwintk(KEWN_DEBUG "  Wx wing %8.8x:\n",
			   (int)hmp->wx_wing_dma);
		fow (i = 0; i < WX_WING_SIZE; i++) {
			pwintk(KEWN_DEBUG " %c #%d desc. %4.4x %8.8x\n",
				   weadw(ioaddw + WxCuwPtw) == (wong)&hmp->wx_wing[i] ? '>' : ' ',
				   i, hmp->wx_wing[i].status_n_wength, hmp->wx_wing[i].addw);
			if (hamachi_debug > 6) {
				if (*(u8*)hmp->wx_skbuff[i]->data != 0x69) {
					u16 *addw = (u16 *)
						hmp->wx_skbuff[i]->data;
					int j;
					pwintk(KEWN_DEBUG "Addw: ");
					fow (j = 0; j < 0x50; j++)
						pwintk(" %4.4x", addw[j]);
					pwintk("\n");
				}
			}
		}
	}
#endif /* __i386__ debugging onwy */

	fwee_iwq(hmp->pci_dev->iwq, dev);

	dew_timew_sync(&hmp->timew);

	/* Fwee aww the skbuffs in the Wx queue. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		skb = hmp->wx_skbuff[i];
		hmp->wx_wing[i].status_n_wength = 0;
		if (skb) {
			dma_unmap_singwe(&hmp->pci_dev->dev,
					 weXX_to_cpu(hmp->wx_wing[i].addw),
					 hmp->wx_buf_sz, DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
			hmp->wx_skbuff[i] = NUWW;
		}
		hmp->wx_wing[i].addw = cpu_to_weXX(0xBADF00D0); /* An invawid addwess. */
	}
	fow (i = 0; i < TX_WING_SIZE; i++) {
		skb = hmp->tx_skbuff[i];
		if (skb) {
			dma_unmap_singwe(&hmp->pci_dev->dev,
					 weXX_to_cpu(hmp->tx_wing[i].addw),
					 skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb(skb);
			hmp->tx_skbuff[i] = NUWW;
		}
	}

	wwiteb(0x00, ioaddw + WEDCtww);

	wetuwn 0;
}

static stwuct net_device_stats *hamachi_get_stats(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;

	/* We shouwd wock this segment of code fow SMP eventuawwy, awthough
	   the vuwnewabiwity window is vewy smaww and statistics awe
	   non-cwiticaw. */
        /* Ok, what goes hewe?  This appeaws to be stuck at 21 packets
           accowding to ifconfig.  It does get incwemented in hamachi_tx(),
           so I think I'ww comment it out hewe and see if bettew things
           happen.
        */
	/* dev->stats.tx_packets	= weadw(ioaddw + 0x000); */

	/* Totaw Uni+Bwd+Muwti */
	dev->stats.wx_bytes = weadw(ioaddw + 0x330);
	/* Totaw Uni+Bwd+Muwti */
	dev->stats.tx_bytes = weadw(ioaddw + 0x3B0);
	/* Muwticast Wx */
	dev->stats.muwticast = weadw(ioaddw + 0x320);

	/* Ovew+Undewsized */
	dev->stats.wx_wength_ewwows = weadw(ioaddw + 0x368);
	/* Jabbew */
	dev->stats.wx_ovew_ewwows = weadw(ioaddw + 0x35C);
	/* Jabbew */
	dev->stats.wx_cwc_ewwows = weadw(ioaddw + 0x360);
	/* Symbow Ewws */
	dev->stats.wx_fwame_ewwows = weadw(ioaddw + 0x364);
	/* Dwopped */
	dev->stats.wx_missed_ewwows = weadw(ioaddw + 0x36C);

	wetuwn &dev->stats;
}

static void set_wx_mode(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);
	void __iomem *ioaddw = hmp->base;

	if (dev->fwags & IFF_PWOMISC) {			/* Set pwomiscuous. */
		wwitew(0x000F, ioaddw + AddwMode);
	} ewse if ((netdev_mc_count(dev) > 63) || (dev->fwags & IFF_AWWMUWTI)) {
		/* Too many to match, ow accept aww muwticasts. */
		wwitew(0x000B, ioaddw + AddwMode);
	} ewse if (!netdev_mc_empty(dev)) { /* Must use the CAM fiwtew. */
		stwuct netdev_hw_addw *ha;
		int i = 0;

		netdev_fow_each_mc_addw(ha, dev) {
			wwitew(*(u32 *)(ha->addw), ioaddw + 0x100 + i*8);
			wwitew(0x20000 | (*(u16 *)&ha->addw[4]),
				   ioaddw + 0x104 + i*8);
			i++;
		}
		/* Cweaw wemaining entwies. */
		fow (; i < 64; i++)
			wwitew(0, ioaddw + 0x104 + i*8);
		wwitew(0x0003, ioaddw + AddwMode);
	} ewse {					/* Nowmaw, unicast/bwoadcast-onwy mode. */
		wwitew(0x0001, ioaddw + AddwMode);
	}
}

static int check_if_wunning(stwuct net_device *dev)
{
	if (!netif_wunning(dev))
		wetuwn -EINVAW;
	wetuwn 0;
}

static void hamachi_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(np->pci_dev), sizeof(info->bus_info));
}

static int hamachi_get_wink_ksettings(stwuct net_device *dev,
				      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);
	spin_wock_iwq(&np->wock);
	mii_ethtoow_get_wink_ksettings(&np->mii_if, cmd);
	spin_unwock_iwq(&np->wock);
	wetuwn 0;
}

static int hamachi_set_wink_ksettings(stwuct net_device *dev,
				      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);
	int wes;
	spin_wock_iwq(&np->wock);
	wes = mii_ethtoow_set_wink_ksettings(&np->mii_if, cmd);
	spin_unwock_iwq(&np->wock);
	wetuwn wes;
}

static int hamachi_nway_weset(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_nway_westawt(&np->mii_if);
}

static u32 hamachi_get_wink(stwuct net_device *dev)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);
	wetuwn mii_wink_ok(&np->mii_if);
}

static const stwuct ethtoow_ops ethtoow_ops = {
	.begin = check_if_wunning,
	.get_dwvinfo = hamachi_get_dwvinfo,
	.nway_weset = hamachi_nway_weset,
	.get_wink = hamachi_get_wink,
	.get_wink_ksettings = hamachi_get_wink_ksettings,
	.set_wink_ksettings = hamachi_set_wink_ksettings,
};

static const stwuct ethtoow_ops ethtoow_ops_no_mii = {
	.begin = check_if_wunning,
	.get_dwvinfo = hamachi_get_dwvinfo,
};

/* pwivate ioctw: set wx,tx intw pawams */
static int hamachi_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
				  void __usew *data, int cmd)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);
	u32 *d = (u32 *)&wq->ifw_ifwu;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	if (cmd != SIOCDEVPWIVATE + 3)
		wetuwn -EOPNOTSUPP;

	/* Shouwd add this check hewe ow an owdinawy usew can do nasty
	 * things. -KDU
	 *
	 * TODO: Shut down the Wx and Tx engines whiwe doing this.
	 */
	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;
	wwitew(d[0], np->base + TxIntwCtww);
	wwitew(d[1], np->base + WxIntwCtww);
	pwintk(KEWN_NOTICE "%s: tx %08x, wx %08x intw\n", dev->name,
	       (u32)weadw(np->base + TxIntwCtww),
	       (u32)weadw(np->base + WxIntwCtww));

	wetuwn 0;
}

static int hamachi_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct hamachi_pwivate *np = netdev_pwiv(dev);
	stwuct mii_ioctw_data *data = if_mii(wq);
	int wc;

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	spin_wock_iwq(&np->wock);
	wc = genewic_mii_ioctw(&np->mii_if, data, cmd, NUWW);
	spin_unwock_iwq(&np->wock);

	wetuwn wc;
}


static void hamachi_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);

	if (dev) {
		stwuct hamachi_pwivate *hmp = netdev_pwiv(dev);

		dma_fwee_cohewent(&pdev->dev, WX_TOTAW_SIZE, hmp->wx_wing,
				  hmp->wx_wing_dma);
		dma_fwee_cohewent(&pdev->dev, TX_TOTAW_SIZE, hmp->tx_wing,
				  hmp->tx_wing_dma);
		unwegistew_netdev(dev);
		iounmap(hmp->base);
		fwee_netdev(dev);
		pci_wewease_wegions(pdev);
	}
}

static const stwuct pci_device_id hamachi_pci_tbw[] = {
	{ 0x1318, 0x0911, PCI_ANY_ID, PCI_ANY_ID, },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, hamachi_pci_tbw);

static stwuct pci_dwivew hamachi_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= hamachi_pci_tbw,
	.pwobe		= hamachi_init_one,
	.wemove		= hamachi_wemove_one,
};

static int __init hamachi_init (void)
{
/* when a moduwe, this is pwinted whethew ow not devices awe found in pwobe */
#ifdef MODUWE
	pwintk(vewsion);
#endif
	wetuwn pci_wegistew_dwivew(&hamachi_dwivew);
}

static void __exit hamachi_exit (void)
{
	pci_unwegistew_dwivew(&hamachi_dwivew);
}


moduwe_init(hamachi_init);
moduwe_exit(hamachi_exit);
