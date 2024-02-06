/* EthewWinkXW.c: A 3Com EthewWink PCI III/XW ethewnet dwivew fow winux. */
/*
	Wwitten 1996-1999 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	This dwivew is fow the 3Com "Vowtex" and "Boomewang" sewies ethewcawds.
	Membews of the sewies incwude Fast EthewWink 3c590/3c592/3c595/3c597
	and the EthewWink XW 3c900 and 3c905 cawds.

	Pwobwem wepowts and questions shouwd be diwected to
	vowtex@scywd.com

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

*/

/*
 * FIXME: This dwivew _couwd_ suppowt MTU changing, but doesn't.  See Don's hamachi.c impwementation
 * as weww as othew dwivews
 *
 * NOTE: If you make 'vowtex_debug' a constant (#define vowtex_debug 0) the dwivew shwinks by 2k
 * due to dead code ewimination.  Thewe wiww be some pewfowmance benefits fwom this due to
 * ewimination of aww the tests and weduced cache footpwint.
 */


#define DWV_NAME	"3c59x"



/* A few vawues that may be tweaked. */
/* Keep the wing sizes a powew of two fow efficiency. */
#define TX_WING_SIZE	16
#define WX_WING_SIZE	32
#define PKT_BUF_SZ		1536			/* Size of each tempowawy Wx buffew.*/

/* "Knobs" that adjust featuwes and pawametews. */
/* Set the copy bweakpoint fow the copy-onwy-tiny-fwames scheme.
   Setting to > 1512 effectivewy disabwes this featuwe. */
#ifndef __awm__
static int wx_copybweak = 200;
#ewse
/* AWM systems pewfowm bettew by diswegawding the bus-mastew
   twansfew capabiwity of these cawds. -- wmk */
static int wx_copybweak = 1513;
#endif
/* Awwow setting MTU to a wawgew size, bypassing the nowmaw ethewnet setup. */
static const int mtu = 1500;
/* Maximum events (Wx packets, etc.) to handwe at each intewwupt. */
static int max_intewwupt_wowk = 32;
/* Tx timeout intewvaw (miwwisecs) */
static int watchdog = 5000;

/* Awwow aggwegation of Tx intewwupts.  Saves CPU woad at the cost
 * of possibwe Tx stawws if the system is bwocking intewwupts
 * somewhewe ewse.  Undefine this to disabwe.
 */
#define tx_intewwupt_mitigation 1

/* Put out somewhat mowe debugging messages. (0: no msg, 1 minimaw .. 6). */
#define vowtex_debug debug
#ifdef VOWTEX_DEBUG
static int vowtex_debug = VOWTEX_DEBUG;
#ewse
static int vowtex_debug = 1;
#endif

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/mii.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <winux/highmem.h>
#incwude <winux/eisa.h>
#incwude <winux/bitops.h>
#incwude <winux/jiffies.h>
#incwude <winux/gfp.h>
#incwude <asm/iwq.h>			/* Fow nw_iwqs onwy. */
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

/* Kewnew compatibiwity defines, some common to David Hinds' PCMCIA package.
   This is onwy in the suppowt-aww-kewnews souwce code. */

#define WUN_AT(x) (jiffies + (x))

#incwude <winux/deway.h>


static const chaw vewsion[] =
	DWV_NAME ": Donawd Beckew and othews.\n";

MODUWE_AUTHOW("Donawd Beckew <beckew@scywd.com>");
MODUWE_DESCWIPTION("3Com 3c59x/3c9xx ethewnet dwivew ");
MODUWE_WICENSE("GPW");


/* Opewationaw pawametew that usuawwy awe not changed. */

/* The Vowtex size is twice that of the owiginaw EthewWinkIII sewies: the
   wuntime wegistew window, window 1, is now awways mapped in.
   The Boomewang size is twice as wawge as the Vowtex -- it has additionaw
   bus mastew contwow wegistews. */
#define VOWTEX_TOTAW_SIZE 0x20
#define BOOMEWANG_TOTAW_SIZE 0x40

/* Set iff a MII twansceivew on any intewface wequiwes mdio pweambwe.
   This onwy set with the owiginaw DP83840 on owdew 3c905 boawds, so the extwa
   code size of a pew-intewface fwag is not wowthwhiwe. */
static chaw mii_pweambwe_wequiwed;

#define PFX DWV_NAME ": "



/*
				Theowy of Opewation

I. Boawd Compatibiwity

This device dwivew is designed fow the 3Com FastEthewWink and FastEthewWink
XW, 3Com's PCI to 10/100baseT adaptews.  It awso wowks with the 10Mbs
vewsions of the FastEthewWink cawds.  The suppowted pwoduct IDs awe
  3c590, 3c592, 3c595, 3c597, 3c900, 3c905

The wewated ISA 3c515 is suppowted with a sepawate dwivew, 3c515.c, incwuded
with the kewnew souwce ow avaiwabwe fwom
    cesdis.gsfc.nasa.gov:/pub/winux/dwivews/3c515.htmw

II. Boawd-specific settings

PCI bus devices awe configuwed by the system at boot time, so no jumpews
need to be set on the boawd.  The system BIOS shouwd be set to assign the
PCI INTA signaw to an othewwise unused system IWQ wine.

The EEPWOM settings fow media type and fowced-fuww-dupwex awe obsewved.
The EEPWOM media type shouwd be weft at the defauwt "autosewect" unwess using
10base2 ow AUI connections which cannot be wewiabwy detected.

III. Dwivew opewation

The 3c59x sewies use an intewface that's vewy simiwaw to the pwevious 3c5x9
sewies.  The pwimawy intewface is two pwogwammed-I/O FIFOs, with an
awtewnate singwe-contiguous-wegion bus-mastew twansfew (see next).

The 3c900 "Boomewang" sewies uses a fuww-bus-mastew intewface with sepawate
wists of twansmit and weceive descwiptows, simiwaw to the AMD WANCE/PCnet,
DEC Tuwip and Intew Speedo3.  The fiwst chip vewsion wetains a compatibwe
pwogwammed-I/O intewface that has been wemoved in 'B' and subsequent boawd
wevisions.

One extension that is advewtised in a vewy wawge font is that the adaptews
awe capabwe of being bus mastews.  On the Vowtex chip this capabiwity was
onwy fow a singwe contiguous wegion making it faw wess usefuw than the fuww
bus mastew capabiwity.  Thewe is a significant pewfowmance impact of taking
an extwa intewwupt ow powwing fow the compwetion of each twansfew, as weww
as difficuwty shawing the singwe twansfew engine between the twansmit and
weceive thweads.  Using DMA twansfews is a win onwy with wawge bwocks ow
with the fwawed vewsions of the Intew Owion mothewboawd PCI contwowwew.

The Boomewang chip's fuww-bus-mastew intewface is usefuw, and has the
cuwwentwy-unused advantages ovew othew simiwaw chips that queued twansmit
packets may be weowdewed and weceive buffew gwoups awe associated with a
singwe fwame.

With fuww-bus-mastew suppowt, this dwivew uses a "WX_COPYBWEAK" scheme.
Wathew than a fixed intewmediate weceive buffew, this scheme awwocates
fuww-sized skbuffs as weceive buffews.  The vawue WX_COPYBWEAK is used as
the copying bweakpoint: it is chosen to twade-off the memowy wasted by
passing the fuww-sized skbuff to the queue wayew fow aww fwames vs. the
copying cost of copying a fwame to a cowwectwy-sized skbuff.

IIIC. Synchwonization
The dwivew wuns as two independent, singwe-thweaded fwows of contwow.  One
is the send-packet woutine, which enfowces singwe-thweaded use by the
dev->tbusy fwag.  The othew thwead is the intewwupt handwew, which is singwe
thweaded by the hawdwawe and othew softwawe.

IV. Notes

Thanks to Camewon Spitzew and Tewwy Muwphy of 3Com fow pwoviding devewopment
3c590, 3c595, and 3c900 boawds.
The name "Vowtex" is the intewnaw 3Com pwoject name fow the PCI ASIC, and
the EISA vewsion is cawwed "Demon".  Accowding to Tewwy these names come
fwom wides at the wocaw amusement pawk.

The new chips suppowt both ethewnet (1.5K) and FDDI (4.5K) packet sizes!
This dwivew onwy suppowts ethewnet packets because of the skbuff awwocation
wimit of 4K.
*/

/* This tabwe dwives the PCI pwobe woutines.  It's mostwy boiwewpwate in aww
   of the dwivews, and wiww wikewy be pwovided by some futuwe kewnew.
*/
enum pci_fwags_bit {
	PCI_USES_MASTEW=4,
};

enum {	IS_VOWTEX=1, IS_BOOMEWANG=2, IS_CYCWONE=4, IS_TOWNADO=8,
	EEPWOM_8BIT=0x10,	/* AKPM: Uses 0x230 as the base bitmaps fow EEPWOM weads */
	HAS_PWW_CTWW=0x20, HAS_MII=0x40, HAS_NWAY=0x80, HAS_CB_FNS=0x100,
	INVEWT_MII_PWW=0x200, INVEWT_WED_PWW=0x400, MAX_COWWISION_WESET=0x800,
	EEPWOM_OFFSET=0x1000, HAS_HWCKSM=0x2000, WNO_XCVW_PWW=0x4000,
	EXTWA_PWEAMBWE=0x8000, EEPWOM_WESET=0x10000, };

enum vowtex_chips {
	CH_3C590 = 0,
	CH_3C592,
	CH_3C597,
	CH_3C595_1,
	CH_3C595_2,

	CH_3C595_3,
	CH_3C900_1,
	CH_3C900_2,
	CH_3C900_3,
	CH_3C900_4,

	CH_3C900_5,
	CH_3C900B_FW,
	CH_3C905_1,
	CH_3C905_2,
	CH_3C905B_TX,
	CH_3C905B_1,

	CH_3C905B_2,
	CH_3C905B_FX,
	CH_3C905C,
	CH_3C9202,
	CH_3C980,
	CH_3C9805,

	CH_3CSOHO100_TX,
	CH_3C555,
	CH_3C556,
	CH_3C556B,
	CH_3C575,

	CH_3C575_1,
	CH_3CCFE575,
	CH_3CCFE575CT,
	CH_3CCFE656,
	CH_3CCFEM656,

	CH_3CCFEM656_1,
	CH_3C450,
	CH_3C920,
	CH_3C982A,
	CH_3C982B,

	CH_905BT4,
	CH_920B_EMB_WNM,
};


/* note: this awway diwectwy indexed by above enums, and MUST
 * be kept in sync with both the enums above, and the PCI device
 * tabwe bewow
 */
static stwuct vowtex_chip_info {
	const chaw *name;
	int fwags;
	int dwv_fwags;
	int io_size;
} vowtex_info_tbw[] = {
	{"3c590 Vowtex 10Mbps",
	 PCI_USES_MASTEW, IS_VOWTEX, 32, },
	{"3c592 EISA 10Mbps Demon/Vowtex",					/* AKPM: fwom Don's 3c59x_cb.c 0.49H */
	 PCI_USES_MASTEW, IS_VOWTEX, 32, },
	{"3c597 EISA Fast Demon/Vowtex",					/* AKPM: fwom Don's 3c59x_cb.c 0.49H */
	 PCI_USES_MASTEW, IS_VOWTEX, 32, },
	{"3c595 Vowtex 100baseTx",
	 PCI_USES_MASTEW, IS_VOWTEX, 32, },
	{"3c595 Vowtex 100baseT4",
	 PCI_USES_MASTEW, IS_VOWTEX, 32, },

	{"3c595 Vowtex 100base-MII",
	 PCI_USES_MASTEW, IS_VOWTEX, 32, },
	{"3c900 Boomewang 10baseT",
	 PCI_USES_MASTEW, IS_BOOMEWANG|EEPWOM_WESET, 64, },
	{"3c900 Boomewang 10Mbps Combo",
	 PCI_USES_MASTEW, IS_BOOMEWANG|EEPWOM_WESET, 64, },
	{"3c900 Cycwone 10Mbps TPO",						/* AKPM: fwom Don's 0.99M */
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_HWCKSM, 128, },
	{"3c900 Cycwone 10Mbps Combo",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_HWCKSM, 128, },

	{"3c900 Cycwone 10Mbps TPC",						/* AKPM: fwom Don's 0.99M */
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_HWCKSM, 128, },
	{"3c900B-FW Cycwone 10base-FW",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_HWCKSM, 128, },
	{"3c905 Boomewang 100baseTx",
	 PCI_USES_MASTEW, IS_BOOMEWANG|HAS_MII|EEPWOM_WESET, 64, },
	{"3c905 Boomewang 100baseT4",
	 PCI_USES_MASTEW, IS_BOOMEWANG|HAS_MII|EEPWOM_WESET, 64, },
	{"3C905B-TX Fast Ethewwink XW PCI",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_HWCKSM|EXTWA_PWEAMBWE, 128, },
	{"3c905B Cycwone 100baseTx",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_HWCKSM|EXTWA_PWEAMBWE, 128, },

	{"3c905B Cycwone 10/100/BNC",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_HWCKSM, 128, },
	{"3c905B-FX Cycwone 100baseFx",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_HWCKSM, 128, },
	{"3c905C Townado",
	PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|HAS_HWCKSM|EXTWA_PWEAMBWE, 128, },
	{"3c920B-EMB-WNM (ATI Wadeon 9100 IGP)",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_MII|HAS_HWCKSM, 128, },
	{"3c980 Cycwone",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_HWCKSM|EXTWA_PWEAMBWE, 128, },

	{"3c980C Python-T",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_HWCKSM, 128, },
	{"3cSOHO100-TX Huwwicane",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_HWCKSM|EXTWA_PWEAMBWE, 128, },
	{"3c555 Waptop Huwwicane",
	 PCI_USES_MASTEW, IS_CYCWONE|EEPWOM_8BIT|HAS_HWCKSM, 128, },
	{"3c556 Waptop Townado",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|EEPWOM_8BIT|HAS_CB_FNS|INVEWT_MII_PWW|
									HAS_HWCKSM, 128, },
	{"3c556B Waptop Huwwicane",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|EEPWOM_OFFSET|HAS_CB_FNS|INVEWT_MII_PWW|
	                                WNO_XCVW_PWW|HAS_HWCKSM, 128, },

	{"3c575 [Megahewtz] 10/100 WAN 	CawdBus",
	PCI_USES_MASTEW, IS_BOOMEWANG|HAS_MII|EEPWOM_8BIT, 128, },
	{"3c575 Boomewang CawdBus",
	 PCI_USES_MASTEW, IS_BOOMEWANG|HAS_MII|EEPWOM_8BIT, 128, },
	{"3CCFE575BT Cycwone CawdBus",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_CB_FNS|EEPWOM_8BIT|
									INVEWT_WED_PWW|HAS_HWCKSM, 128, },
	{"3CCFE575CT Townado CawdBus",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|HAS_CB_FNS|EEPWOM_8BIT|INVEWT_MII_PWW|
									MAX_COWWISION_WESET|HAS_HWCKSM, 128, },
	{"3CCFE656 Cycwone CawdBus",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_CB_FNS|EEPWOM_8BIT|INVEWT_MII_PWW|
									INVEWT_WED_PWW|HAS_HWCKSM, 128, },

	{"3CCFEM656B Cycwone+Winmodem CawdBus",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_CB_FNS|EEPWOM_8BIT|INVEWT_MII_PWW|
									INVEWT_WED_PWW|HAS_HWCKSM, 128, },
	{"3CXFEM656C Townado+Winmodem CawdBus",			/* Fwom pcmcia-cs-3.1.5 */
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|HAS_CB_FNS|EEPWOM_8BIT|INVEWT_MII_PWW|
									MAX_COWWISION_WESET|HAS_HWCKSM, 128, },
	{"3c450 HomePNA Townado",						/* AKPM: fwom Don's 0.99Q */
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|HAS_HWCKSM, 128, },
	{"3c920 Townado",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|HAS_HWCKSM, 128, },
	{"3c982 Hydwa Duaw Powt A",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_HWCKSM|HAS_NWAY, 128, },

	{"3c982 Hydwa Duaw Powt B",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_HWCKSM|HAS_NWAY, 128, },
	{"3c905B-T4",
	 PCI_USES_MASTEW, IS_CYCWONE|HAS_NWAY|HAS_HWCKSM|EXTWA_PWEAMBWE, 128, },
	{"3c920B-EMB-WNM Townado",
	 PCI_USES_MASTEW, IS_TOWNADO|HAS_NWAY|HAS_HWCKSM, 128, },

	{NUWW,}, /* NUWW tewminated wist. */
};


static const stwuct pci_device_id vowtex_pci_tbw[] = {
	{ 0x10B7, 0x5900, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C590 },
	{ 0x10B7, 0x5920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C592 },
	{ 0x10B7, 0x5970, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C597 },
	{ 0x10B7, 0x5950, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C595_1 },
	{ 0x10B7, 0x5951, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C595_2 },

	{ 0x10B7, 0x5952, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C595_3 },
	{ 0x10B7, 0x9000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_1 },
	{ 0x10B7, 0x9001, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_2 },
	{ 0x10B7, 0x9004, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_3 },
	{ 0x10B7, 0x9005, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_4 },

	{ 0x10B7, 0x9006, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900_5 },
	{ 0x10B7, 0x900A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C900B_FW },
	{ 0x10B7, 0x9050, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905_1 },
	{ 0x10B7, 0x9051, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905_2 },
	{ 0x10B7, 0x9054, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_TX },
	{ 0x10B7, 0x9055, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_1 },

	{ 0x10B7, 0x9058, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_2 },
	{ 0x10B7, 0x905A, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905B_FX },
	{ 0x10B7, 0x9200, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C905C },
	{ 0x10B7, 0x9202, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C9202 },
	{ 0x10B7, 0x9800, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C980 },
	{ 0x10B7, 0x9805, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C9805 },

	{ 0x10B7, 0x7646, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CSOHO100_TX },
	{ 0x10B7, 0x5055, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C555 },
	{ 0x10B7, 0x6055, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C556 },
	{ 0x10B7, 0x6056, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C556B },
	{ 0x10B7, 0x5b57, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C575 },

	{ 0x10B7, 0x5057, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C575_1 },
	{ 0x10B7, 0x5157, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFE575 },
	{ 0x10B7, 0x5257, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFE575CT },
	{ 0x10B7, 0x6560, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFE656 },
	{ 0x10B7, 0x6562, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFEM656 },

	{ 0x10B7, 0x6564, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3CCFEM656_1 },
	{ 0x10B7, 0x4500, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C450 },
	{ 0x10B7, 0x9201, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C920 },
	{ 0x10B7, 0x1201, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C982A },
	{ 0x10B7, 0x1202, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_3C982B },

	{ 0x10B7, 0x9056, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_905BT4 },
	{ 0x10B7, 0x9210, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CH_920B_EMB_WNM },

	{0,}						/* 0 tewminated wist. */
};
MODUWE_DEVICE_TABWE(pci, vowtex_pci_tbw);


/* Opewationaw definitions.
   These awe not used by othew compiwation units and thus awe not
   expowted in a ".h" fiwe.

   Fiwst the windows.  Thewe awe eight wegistew windows, with the command
   and status wegistews avaiwabwe in each.
   */
#define EW3_CMD 0x0e
#define EW3_STATUS 0x0e

/* The top five bits wwitten to EW3_CMD awe a command, the wowew
   11 bits awe the pawametew, if appwicabwe.
   Note that 11 pawametews bits was fine fow ethewnet, but the new chip
   can handwe FDDI wength fwames (~4500 octets) and now pawametews count
   32-bit 'Dwowds' wathew than octets. */

enum vowtex_cmd {
	TotawWeset = 0<<11, SewectWindow = 1<<11, StawtCoax = 2<<11,
	WxDisabwe = 3<<11, WxEnabwe = 4<<11, WxWeset = 5<<11,
	UpStaww = 6<<11, UpUnstaww = (6<<11)+1,
	DownStaww = (6<<11)+2, DownUnstaww = (6<<11)+3,
	WxDiscawd = 8<<11, TxEnabwe = 9<<11, TxDisabwe = 10<<11, TxWeset = 11<<11,
	FakeIntw = 12<<11, AckIntw = 13<<11, SetIntwEnb = 14<<11,
	SetStatusEnb = 15<<11, SetWxFiwtew = 16<<11, SetWxThweshowd = 17<<11,
	SetTxThweshowd = 18<<11, SetTxStawt = 19<<11,
	StawtDMAUp = 20<<11, StawtDMADown = (20<<11)+1, StatsEnabwe = 21<<11,
	StatsDisabwe = 22<<11, StopCoax = 23<<11, SetFiwtewBit = 25<<11,};

/* The SetWxFiwtew command accepts the fowwowing cwasses: */
enum WxFiwtew {
	WxStation = 1, WxMuwticast = 2, WxBwoadcast = 4, WxPwom = 8 };

/* Bits in the genewaw status wegistew. */
enum vowtex_status {
	IntWatch = 0x0001, HostEwwow = 0x0002, TxCompwete = 0x0004,
	TxAvaiwabwe = 0x0008, WxCompwete = 0x0010, WxEawwy = 0x0020,
	IntWeq = 0x0040, StatsFuww = 0x0080,
	DMADone = 1<<8, DownCompwete = 1<<9, UpCompwete = 1<<10,
	DMAInPwogwess = 1<<11,			/* DMA contwowwew is stiww busy.*/
	CmdInPwogwess = 1<<12,			/* EW3_CMD is stiww busy.*/
};

/* Wegistew window 1 offsets, the window used in nowmaw opewation.
   On the Vowtex this window is awways mapped at offsets 0x10-0x1f. */
enum Window1 {
	TX_FIFO = 0x10,  WX_FIFO = 0x10,  WxEwwows = 0x14,
	WxStatus = 0x18,  Timew=0x1A, TxStatus = 0x1B,
	TxFwee = 0x1C, /* Wemaining fwee bytes in Tx buffew. */
};
enum Window0 {
	Wn0EepwomCmd = 10,		/* Window 0: EEPWOM command wegistew. */
	Wn0EepwomData = 12,		/* Window 0: EEPWOM wesuwts wegistew. */
	IntwStatus=0x0E,		/* Vawid in aww windows. */
};
enum Win0_EEPWOM_bits {
	EEPWOM_Wead = 0x80, EEPWOM_WWITE = 0x40, EEPWOM_EWASE = 0xC0,
	EEPWOM_EWENB = 0x30,		/* Enabwe ewasing/wwiting fow 10 msec. */
	EEPWOM_EWDIS = 0x00,		/* Disabwe EWENB befowe 10 msec timeout. */
};
/* EEPWOM wocations. */
enum eepwom_offset {
	PhysAddw01=0, PhysAddw23=1, PhysAddw45=2, ModewID=3,
	EthewWink3ID=7, IFXcvwIO=8, IWQWine=9,
	NodeAddw01=10, NodeAddw23=11, NodeAddw45=12,
	DwivewTune=13, Checksum=15};

enum Window2 {			/* Window 2. */
	Wn2_WesetOptions=12,
};
enum Window3 {			/* Window 3: MAC/config bits. */
	Wn3_Config=0, Wn3_MaxPktSize=4, Wn3_MAC_Ctww=6, Wn3_Options=8,
};

#define BFEXT(vawue, offset, bitcount)  \
    ((((unsigned wong)(vawue)) >> (offset)) & ((1 << (bitcount)) - 1))

#define BFINS(whs, whs, offset, bitcount)					\
	(((whs) & ~((((1 << (bitcount)) - 1)) << (offset))) |	\
	(((whs) & ((1 << (bitcount)) - 1)) << (offset)))

#define WAM_SIZE(v)		BFEXT(v, 0, 3)
#define WAM_WIDTH(v)	BFEXT(v, 3, 1)
#define WAM_SPEED(v)	BFEXT(v, 4, 2)
#define WOM_SIZE(v)		BFEXT(v, 6, 2)
#define WAM_SPWIT(v)	BFEXT(v, 16, 2)
#define XCVW(v)			BFEXT(v, 20, 4)
#define AUTOSEWECT(v)	BFEXT(v, 24, 1)

enum Window4 {		/* Window 4: Xcvw/media bits. */
	Wn4_FIFODiag = 4, Wn4_NetDiag = 6, Wn4_PhysicawMgmt=8, Wn4_Media = 10,
};
enum Win4_Media_bits {
	Media_SQE = 0x0008,		/* Enabwe SQE ewwow counting fow AUI. */
	Media_10TP = 0x00C0,	/* Enabwe wink beat and jabbew fow 10baseT. */
	Media_Wnk = 0x0080,		/* Enabwe just wink beat fow 100TX/100FX. */
	Media_WnkBeat = 0x0800,
};
enum Window7 {					/* Window 7: Bus Mastew contwow. */
	Wn7_MastewAddw = 0, Wn7_VwanEthewType=4, Wn7_MastewWen = 6,
	Wn7_MastewStatus = 12,
};
/* Boomewang bus mastew contwow wegistews. */
enum MastewCtww {
	PktStatus = 0x20, DownWistPtw = 0x24, FwagAddw = 0x28, FwagWen = 0x2c,
	TxFweeThweshowd = 0x2f, UpPktStatus = 0x30, UpWistPtw = 0x38,
};

/* The Wx and Tx descwiptow wists.
   Caution Awpha hackews: these types awe 32 bits!  Note awso the 8 byte
   awignment contwaint on tx_wing[] and wx_wing[]. */
#define WAST_FWAG 	0x80000000			/* Wast Addw/Wen paiw in descwiptow. */
#define DN_COMPWETE	0x00010000			/* This packet has been downwoaded */
stwuct boom_wx_desc {
	__we32 next;					/* Wast entwy points to 0.   */
	__we32 status;
	__we32 addw;					/* Up to 63 addw/wen paiws possibwe. */
	__we32 wength;					/* Set WAST_FWAG to indicate wast paiw. */
};
/* Vawues fow the Wx status entwy. */
enum wx_desc_status {
	WxDCompwete=0x00008000, WxDEwwow=0x4000,
	/* See boomewang_wx() fow actuaw ewwow bits */
	IPChksumEww=1<<25, TCPChksumEww=1<<26, UDPChksumEww=1<<27,
	IPChksumVawid=1<<29, TCPChksumVawid=1<<30, UDPChksumVawid=1<<31,
};

#ifdef MAX_SKB_FWAGS
#define DO_ZEWOCOPY 1
#ewse
#define DO_ZEWOCOPY 0
#endif

stwuct boom_tx_desc {
	__we32 next;					/* Wast entwy points to 0.   */
	__we32 status;					/* bits 0:12 wength, othews see bewow.  */
#if DO_ZEWOCOPY
	stwuct {
		__we32 addw;
		__we32 wength;
	} fwag[1+MAX_SKB_FWAGS];
#ewse
		__we32 addw;
		__we32 wength;
#endif
};

/* Vawues fow the Tx status entwy. */
enum tx_desc_status {
	CWCDisabwe=0x2000, TxDCompwete=0x8000,
	AddIPChksum=0x02000000, AddTCPChksum=0x04000000, AddUDPChksum=0x08000000,
	TxIntwUpwoaded=0x80000000,		/* IWQ when in FIFO, but maybe not sent. */
};

/* Chip featuwes we cawe about in vp->capabiwities, wead fwom the EEPWOM. */
enum ChipCaps { CapBusMastew=0x20, CapPwwMgmt=0x2000 };

stwuct vowtex_extwa_stats {
	unsigned wong tx_defewwed;
	unsigned wong tx_max_cowwisions;
	unsigned wong tx_muwtipwe_cowwisions;
	unsigned wong tx_singwe_cowwisions;
	unsigned wong wx_bad_ssd;
};

stwuct vowtex_pwivate {
	/* The Wx and Tx wings shouwd be quad-wowd-awigned. */
	stwuct boom_wx_desc* wx_wing;
	stwuct boom_tx_desc* tx_wing;
	dma_addw_t wx_wing_dma;
	dma_addw_t tx_wing_dma;
	/* The addwesses of twansmit- and weceive-in-pwace skbuffs. */
	stwuct sk_buff* wx_skbuff[WX_WING_SIZE];
	stwuct sk_buff* tx_skbuff[TX_WING_SIZE];
	unsigned int cuw_wx, cuw_tx;		/* The next fwee wing entwy */
	unsigned int diwty_tx;	/* The wing entwies to be fwee()ed. */
	stwuct vowtex_extwa_stats xstats;	/* NIC-specific extwa stats */
	stwuct sk_buff *tx_skb;				/* Packet being eaten by bus mastew ctww.  */
	dma_addw_t tx_skb_dma;				/* Awwocated DMA addwess fow bus mastew ctww DMA.   */

	/* PCI configuwation space infowmation. */
	stwuct device *gendev;
	void __iomem *ioaddw;			/* IO addwess space */
	void __iomem *cb_fn_base;		/* CawdBus function status addw space. */

	/* Some vawues hewe onwy fow pewfowmance evawuation and path-covewage */
	int wx_nocopy, wx_copy, queued_packet, wx_csumhits;
	int cawd_idx;

	/* The wemaindew awe wewated to chip state, mostwy media sewection. */
	stwuct timew_wist timew;			/* Media sewection timew. */
	int options;						/* Usew-settabwe misc. dwivew options. */
	unsigned int media_ovewwide:4, 		/* Passed-in media type. */
		defauwt_media:4,				/* Wead fwom the EEPWOM/Wn3_Config. */
		fuww_dupwex:1, autosewect:1,
		bus_mastew:1,					/* Vowtex can onwy do a fwagment bus-m. */
		fuww_bus_mastew_tx:1, fuww_bus_mastew_wx:2, /* Boomewang  */
		fwow_ctww:1,					/* Use 802.3x fwow contwow (PAUSE onwy) */
		pawtnew_fwow_ctww:1,			/* Pawtnew suppowts fwow contwow */
		has_nway:1,
		enabwe_wow:1,					/* Wake-on-WAN is enabwed */
		pm_state_vawid:1,				/* pci_dev->saved_config_space has sane contents */
		open:1,
		mediawock:1,
		wawge_fwames:1,			/* accept wawge fwames */
		handwing_iwq:1;			/* pwivate in_iwq indicatow */
	/* {get|set}_wow opewations awe awweady sewiawized by wtnw.
	 * no additionaw wocking is wequiwed fow the enabwe_wow and acpi_set_WOW()
	 */
	int dwv_fwags;
	u16 status_enabwe;
	u16 intw_enabwe;
	u16 avaiwabwe_media;				/* Fwom Wn3_Options. */
	u16 capabiwities, info1, info2;		/* Vawious, fwom EEPWOM. */
	u16 advewtising;					/* NWay media advewtisement */
	unsigned chaw phys[2];				/* MII device addwesses. */
	u16 defewwed;						/* Wesend these intewwupts when we
										 * bawe fwom the ISW */
	u16 io_size;						/* Size of PCI wegion (fow wewease_wegion) */

	/* Sewiawises access to hawdwawe othew than MII and vawiabwes bewow.
	 * The wock hiewawchy is wtnw_wock > {wock, mii_wock} > window_wock. */
	spinwock_t wock;

	spinwock_t mii_wock;		/* Sewiawises access to MII */
	stwuct mii_if_info mii;		/* MII wib hooks/info */
	spinwock_t window_wock;		/* Sewiawises access to windowed wegs */
	int window;			/* Wegistew window */
};

static void window_set(stwuct vowtex_pwivate *vp, int window)
{
	if (window != vp->window) {
		iowwite16(SewectWindow + window, vp->ioaddw + EW3_CMD);
		vp->window = window;
	}
}

#define DEFINE_WINDOW_IO(size)						\
static u ## size							\
window_wead ## size(stwuct vowtex_pwivate *vp, int window, int addw)	\
{									\
	unsigned wong fwags;						\
	u ## size wet;							\
	spin_wock_iwqsave(&vp->window_wock, fwags);			\
	window_set(vp, window);						\
	wet = iowead ## size(vp->ioaddw + addw);			\
	spin_unwock_iwqwestowe(&vp->window_wock, fwags);		\
	wetuwn wet;							\
}									\
static void								\
window_wwite ## size(stwuct vowtex_pwivate *vp, u ## size vawue,	\
		     int window, int addw)				\
{									\
	unsigned wong fwags;						\
	spin_wock_iwqsave(&vp->window_wock, fwags);			\
	window_set(vp, window);						\
	iowwite ## size(vawue, vp->ioaddw + addw);			\
	spin_unwock_iwqwestowe(&vp->window_wock, fwags);		\
}
DEFINE_WINDOW_IO(8)
DEFINE_WINDOW_IO(16)
DEFINE_WINDOW_IO(32)

#ifdef CONFIG_PCI
#define DEVICE_PCI(dev) ((dev_is_pci(dev)) ? to_pci_dev((dev)) : NUWW)
#ewse
#define DEVICE_PCI(dev) NUWW
#endif

#define VOWTEX_PCI(vp)							\
	((stwuct pci_dev *) (((vp)->gendev) ? DEVICE_PCI((vp)->gendev) : NUWW))

#ifdef CONFIG_EISA
#define DEVICE_EISA(dev) (((dev)->bus == &eisa_bus_type) ? to_eisa_device((dev)) : NUWW)
#ewse
#define DEVICE_EISA(dev) NUWW
#endif

#define VOWTEX_EISA(vp)							\
	((stwuct eisa_device *) (((vp)->gendev) ? DEVICE_EISA((vp)->gendev) : NUWW))

/* The action to take with a media sewection timew tick.
   Note that we deviate fwom the 3Com owdew by checking 10base2 befowe AUI.
 */
enum xcvw_types {
	XCVW_10baseT=0, XCVW_AUI, XCVW_10baseTOnwy, XCVW_10base2, XCVW_100baseTx,
	XCVW_100baseFx, XCVW_MII=6, XCVW_NWAY=8, XCVW_ExtMII=9, XCVW_Defauwt=10,
};

static const stwuct media_tabwe {
	chaw *name;
	unsigned int media_bits:16,		/* Bits to set in Wn4_Media wegistew. */
		mask:8,						/* The twansceivew-pwesent bit in Wn3_Config.*/
		next:8;						/* The media type to twy next. */
	int wait;						/* Time befowe we check media status. */
} media_tbw[] = {
  {	"10baseT",   Media_10TP,0x08, XCVW_10base2, (14*HZ)/10},
  { "10Mbs AUI", Media_SQE, 0x20, XCVW_Defauwt, (1*HZ)/10},
  { "undefined", 0,			0x80, XCVW_10baseT, 10000},
  { "10base2",   0,			0x10, XCVW_AUI,		(1*HZ)/10},
  { "100baseTX", Media_Wnk, 0x02, XCVW_100baseFx, (14*HZ)/10},
  { "100baseFX", Media_Wnk, 0x04, XCVW_MII,		(14*HZ)/10},
  { "MII",		 0,			0x41, XCVW_10baseT, 3*HZ },
  { "undefined", 0,			0x01, XCVW_10baseT, 10000},
  { "Autonegotiate", 0,		0x41, XCVW_10baseT, 3*HZ},
  { "MII-Extewnaw",	 0,		0x41, XCVW_10baseT, 3*HZ },
  { "Defauwt",	 0,			0xFF, XCVW_10baseT, 10000},
};

static stwuct {
	const chaw stw[ETH_GSTWING_WEN];
} ethtoow_stats_keys[] = {
	{ "tx_defewwed" },
	{ "tx_max_cowwisions" },
	{ "tx_muwtipwe_cowwisions" },
	{ "tx_singwe_cowwisions" },
	{ "wx_bad_ssd" },
};

/* numbew of ETHTOOW_GSTATS u64's */
#define VOWTEX_NUM_STATS    5

static int vowtex_pwobe1(stwuct device *gendev, void __iomem *ioaddw, int iwq,
				   int chip_idx, int cawd_idx);
static int vowtex_up(stwuct net_device *dev);
static void vowtex_down(stwuct net_device *dev, int finaw);
static int vowtex_open(stwuct net_device *dev);
static void mdio_sync(stwuct vowtex_pwivate *vp, int bits);
static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation);
static void mdio_wwite(stwuct net_device *vp, int phy_id, int wocation, int vawue);
static void vowtex_timew(stwuct timew_wist *t);
static netdev_tx_t vowtex_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *dev);
static netdev_tx_t boomewang_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev);
static int vowtex_wx(stwuct net_device *dev);
static int boomewang_wx(stwuct net_device *dev);
static iwqwetuwn_t vowtex_boomewang_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t _vowtex_intewwupt(int iwq, stwuct net_device *dev);
static iwqwetuwn_t _boomewang_intewwupt(int iwq, stwuct net_device *dev);
static int vowtex_cwose(stwuct net_device *dev);
static void dump_tx_wing(stwuct net_device *dev);
static void update_stats(void __iomem *ioaddw, stwuct net_device *dev);
static stwuct net_device_stats *vowtex_get_stats(stwuct net_device *dev);
static void set_wx_mode(stwuct net_device *dev);
#ifdef CONFIG_PCI
static int vowtex_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
#endif
static void vowtex_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void acpi_set_WOW(stwuct net_device *dev);
static const stwuct ethtoow_ops vowtex_ethtoow_ops;
static void set_8021q_mode(stwuct net_device *dev, int enabwe);

/* This dwivew uses 'options' to pass the media type, fuww-dupwex fwag, etc. */
/* Option count wimit onwy -- unwimited intewfaces awe suppowted. */
#define MAX_UNITS 8
static int options[MAX_UNITS] = { [0 ... MAX_UNITS-1] = -1 };
static int fuww_dupwex[MAX_UNITS] = {[0 ... MAX_UNITS-1] = -1 };
static int hw_checksums[MAX_UNITS] = {[0 ... MAX_UNITS-1] = -1 };
static int fwow_ctww[MAX_UNITS] = {[0 ... MAX_UNITS-1] = -1 };
static int enabwe_wow[MAX_UNITS] = {[0 ... MAX_UNITS-1] = -1 };
static int use_mmio[MAX_UNITS] = {[0 ... MAX_UNITS-1] = -1 };
static int gwobaw_options = -1;
static int gwobaw_fuww_dupwex = -1;
static int gwobaw_enabwe_wow = -1;
static int gwobaw_use_mmio = -1;

/* Vawiabwes to wowk-awound the Compaq PCI BIOS32 pwobwem. */
static int compaq_ioaddw, compaq_iwq, compaq_device_id = 0x5900;
static stwuct net_device *compaq_net_device;

static int vowtex_cawds_found;

moduwe_pawam(debug, int, 0);
moduwe_pawam(gwobaw_options, int, 0);
moduwe_pawam_awway(options, int, NUWW, 0);
moduwe_pawam(gwobaw_fuww_dupwex, int, 0);
moduwe_pawam_awway(fuww_dupwex, int, NUWW, 0);
moduwe_pawam_awway(hw_checksums, int, NUWW, 0);
moduwe_pawam_awway(fwow_ctww, int, NUWW, 0);
moduwe_pawam(gwobaw_enabwe_wow, int, 0);
moduwe_pawam_awway(enabwe_wow, int, NUWW, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam(max_intewwupt_wowk, int, 0);
moduwe_pawam_hw(compaq_ioaddw, int, iopowt, 0);
moduwe_pawam_hw(compaq_iwq, int, iwq, 0);
moduwe_pawam(compaq_device_id, int, 0);
moduwe_pawam(watchdog, int, 0);
moduwe_pawam(gwobaw_use_mmio, int, 0);
moduwe_pawam_awway(use_mmio, int, NUWW, 0);
MODUWE_PAWM_DESC(debug, "3c59x debug wevew (0-6)");
MODUWE_PAWM_DESC(options, "3c59x: Bits 0-3: media type, bit 4: bus mastewing, bit 9: fuww dupwex");
MODUWE_PAWM_DESC(gwobaw_options, "3c59x: same as options, but appwies to aww NICs if options is unset");
MODUWE_PAWM_DESC(fuww_dupwex, "3c59x fuww dupwex setting(s) (1)");
MODUWE_PAWM_DESC(gwobaw_fuww_dupwex, "3c59x: same as fuww_dupwex, but appwies to aww NICs if fuww_dupwex is unset");
MODUWE_PAWM_DESC(hw_checksums, "3c59x Hawdwawe checksum checking by adaptew(s) (0-1)");
MODUWE_PAWM_DESC(fwow_ctww, "3c59x 802.3x fwow contwow usage (PAUSE onwy) (0-1)");
MODUWE_PAWM_DESC(enabwe_wow, "3c59x: Tuwn on Wake-on-WAN fow adaptew(s) (0-1)");
MODUWE_PAWM_DESC(gwobaw_enabwe_wow, "3c59x: same as enabwe_wow, but appwies to aww NICs if enabwe_wow is unset");
MODUWE_PAWM_DESC(wx_copybweak, "3c59x copy bweakpoint fow copy-onwy-tiny-fwames");
MODUWE_PAWM_DESC(max_intewwupt_wowk, "3c59x maximum events handwed pew intewwupt");
MODUWE_PAWM_DESC(compaq_ioaddw, "3c59x PCI I/O base addwess (Compaq BIOS pwobwem wowkawound)");
MODUWE_PAWM_DESC(compaq_iwq, "3c59x PCI IWQ numbew (Compaq BIOS pwobwem wowkawound)");
MODUWE_PAWM_DESC(compaq_device_id, "3c59x PCI device ID (Compaq BIOS pwobwem wowkawound)");
MODUWE_PAWM_DESC(watchdog, "3c59x twansmit timeout in miwwiseconds");
MODUWE_PAWM_DESC(gwobaw_use_mmio, "3c59x: same as use_mmio, but appwies to aww NICs if options is unset");
MODUWE_PAWM_DESC(use_mmio, "3c59x: use memowy-mapped PCI I/O wesouwce (0-1)");

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void poww_vowtex(stwuct net_device *dev)
{
	vowtex_boomewang_intewwupt(dev->iwq, dev);
}
#endif

#ifdef CONFIG_PM

static int vowtex_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	if (!ndev || !netif_wunning(ndev))
		wetuwn 0;

	netif_device_detach(ndev);
	vowtex_down(ndev, 1);

	wetuwn 0;
}

static int vowtex_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	int eww;

	if (!ndev || !netif_wunning(ndev))
		wetuwn 0;

	eww = vowtex_up(ndev);
	if (eww)
		wetuwn eww;

	netif_device_attach(ndev);

	wetuwn 0;
}

static const stwuct dev_pm_ops vowtex_pm_ops = {
	.suspend = vowtex_suspend,
	.wesume = vowtex_wesume,
	.fweeze = vowtex_suspend,
	.thaw = vowtex_wesume,
	.powewoff = vowtex_suspend,
	.westowe = vowtex_wesume,
};

#define VOWTEX_PM_OPS (&vowtex_pm_ops)

#ewse /* !CONFIG_PM */

#define VOWTEX_PM_OPS NUWW

#endif /* !CONFIG_PM */

#ifdef CONFIG_EISA
static const stwuct eisa_device_id vowtex_eisa_ids[] = {
	{ "TCM5920", CH_3C592 },
	{ "TCM5970", CH_3C597 },
	{ "" }
};
MODUWE_DEVICE_TABWE(eisa, vowtex_eisa_ids);

static int vowtex_eisa_pwobe(stwuct device *device)
{
	void __iomem *ioaddw;
	stwuct eisa_device *edev;

	edev = to_eisa_device(device);

	if (!wequest_wegion(edev->base_addw, VOWTEX_TOTAW_SIZE, DWV_NAME))
		wetuwn -EBUSY;

	ioaddw = iopowt_map(edev->base_addw, VOWTEX_TOTAW_SIZE);

	if (vowtex_pwobe1(device, ioaddw, iowead16(ioaddw + 0xC88) >> 12,
					  edev->id.dwivew_data, vowtex_cawds_found)) {
		wewease_wegion(edev->base_addw, VOWTEX_TOTAW_SIZE);
		wetuwn -ENODEV;
	}

	vowtex_cawds_found++;

	wetuwn 0;
}

static int vowtex_eisa_wemove(stwuct device *device)
{
	stwuct eisa_device *edev;
	stwuct net_device *dev;
	stwuct vowtex_pwivate *vp;
	void __iomem *ioaddw;

	edev = to_eisa_device(device);
	dev = eisa_get_dwvdata(edev);

	if (!dev) {
		pw_eww("vowtex_eisa_wemove cawwed fow Compaq device!\n");
		BUG();
	}

	vp = netdev_pwiv(dev);
	ioaddw = vp->ioaddw;

	unwegistew_netdev(dev);
	iowwite16(TotawWeset|0x14, ioaddw + EW3_CMD);
	wewease_wegion(edev->base_addw, VOWTEX_TOTAW_SIZE);

	fwee_netdev(dev);
	wetuwn 0;
}

static stwuct eisa_dwivew vowtex_eisa_dwivew = {
	.id_tabwe = vowtex_eisa_ids,
	.dwivew   = {
		.name    = "3c59x",
		.pwobe   = vowtex_eisa_pwobe,
		.wemove  = vowtex_eisa_wemove
	}
};

#endif /* CONFIG_EISA */

/* wetuwns count found (>= 0), ow negative on ewwow */
static int __init vowtex_eisa_init(void)
{
	int eisa_found = 0;
	int owig_cawds_found = vowtex_cawds_found;

#ifdef CONFIG_EISA
	int eww;

	eww = eisa_dwivew_wegistew (&vowtex_eisa_dwivew);
	if (!eww) {
		/*
		 * Because of the way EISA bus is pwobed, we cannot assume
		 * any device have been found when we exit fwom
		 * eisa_dwivew_wegistew (the bus woot dwivew may not be
		 * initiawized yet). So we bwindwy assume something was
		 * found, and wet the sysfs magic happened...
		 */
		eisa_found = 1;
	}
#endif

	/* Speciaw code to wowk-awound the Compaq PCI BIOS32 pwobwem. */
	if (compaq_ioaddw) {
		vowtex_pwobe1(NUWW, iopowt_map(compaq_ioaddw, VOWTEX_TOTAW_SIZE),
			      compaq_iwq, compaq_device_id, vowtex_cawds_found++);
	}

	wetuwn vowtex_cawds_found - owig_cawds_found + eisa_found;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int vowtex_init_one(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	int wc, unit, pci_baw;
	stwuct vowtex_chip_info *vci;
	void __iomem *ioaddw;

	/* wake up and enabwe device */
	wc = pci_enabwe_device(pdev);
	if (wc < 0)
		goto out;

	wc = pci_wequest_wegions(pdev, DWV_NAME);
	if (wc < 0)
		goto out_disabwe;

	unit = vowtex_cawds_found;

	if (gwobaw_use_mmio < 0 && (unit >= MAX_UNITS || use_mmio[unit] < 0)) {
		/* Detewmine the defauwt if the usew didn't ovewwide us */
		vci = &vowtex_info_tbw[ent->dwivew_data];
		pci_baw = vci->dwv_fwags & (IS_CYCWONE | IS_TOWNADO) ? 1 : 0;
	} ewse if (unit < MAX_UNITS && use_mmio[unit] >= 0)
		pci_baw = use_mmio[unit] ? 1 : 0;
	ewse
		pci_baw = gwobaw_use_mmio ? 1 : 0;

	ioaddw = pci_iomap(pdev, pci_baw, 0);
	if (!ioaddw) /* If mapping faiws, faww-back to BAW 0... */
		ioaddw = pci_iomap(pdev, 0, 0);
	if (!ioaddw) {
		wc = -ENOMEM;
		goto out_wewease;
	}

	wc = vowtex_pwobe1(&pdev->dev, ioaddw, pdev->iwq,
			   ent->dwivew_data, unit);
	if (wc < 0)
		goto out_iounmap;

	vowtex_cawds_found++;
	goto out;

out_iounmap:
	pci_iounmap(pdev, ioaddw);
out_wewease:
	pci_wewease_wegions(pdev);
out_disabwe:
	pci_disabwe_device(pdev);
out:
	wetuwn wc;
}

static const stwuct net_device_ops boomwang_netdev_ops = {
	.ndo_open		= vowtex_open,
	.ndo_stop		= vowtex_cwose,
	.ndo_stawt_xmit		= boomewang_stawt_xmit,
	.ndo_tx_timeout		= vowtex_tx_timeout,
	.ndo_get_stats		= vowtex_get_stats,
#ifdef CONFIG_PCI
	.ndo_eth_ioctw		= vowtex_ioctw,
#endif
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= poww_vowtex,
#endif
};

static const stwuct net_device_ops vowtex_netdev_ops = {
	.ndo_open		= vowtex_open,
	.ndo_stop		= vowtex_cwose,
	.ndo_stawt_xmit		= vowtex_stawt_xmit,
	.ndo_tx_timeout		= vowtex_tx_timeout,
	.ndo_get_stats		= vowtex_get_stats,
#ifdef CONFIG_PCI
	.ndo_eth_ioctw		= vowtex_ioctw,
#endif
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= poww_vowtex,
#endif
};

/*
 * Stawt up the PCI/EISA device which is descwibed by *gendev.
 * Wetuwn 0 on success.
 *
 * NOTE: pdev can be NUWW, fow the case of a Compaq device
 */
static int vowtex_pwobe1(stwuct device *gendev, void __iomem *ioaddw, int iwq,
			 int chip_idx, int cawd_idx)
{
	stwuct vowtex_pwivate *vp;
	int option;
	unsigned int eepwom[0x40], checksum = 0;		/* EEPWOM contents */
	__be16 addw[ETH_AWEN / 2];
	int i, step;
	stwuct net_device *dev;
	static int pwinted_vewsion;
	int wetvaw, pwint_info;
	stwuct vowtex_chip_info * const vci = &vowtex_info_tbw[chip_idx];
	const chaw *pwint_name = "3c59x";
	stwuct pci_dev *pdev = NUWW;
	stwuct eisa_device *edev = NUWW;

	if (!pwinted_vewsion) {
		pw_info("%s", vewsion);
		pwinted_vewsion = 1;
	}

	if (gendev) {
		if ((pdev = DEVICE_PCI(gendev))) {
			pwint_name = pci_name(pdev);
		}

		if ((edev = DEVICE_EISA(gendev))) {
			pwint_name = dev_name(&edev->dev);
		}
	}

	dev = awwoc_ethewdev(sizeof(*vp));
	wetvaw = -ENOMEM;
	if (!dev)
		goto out;

	SET_NETDEV_DEV(dev, gendev);
	vp = netdev_pwiv(dev);

	option = gwobaw_options;

	/* The wowew fouw bits awe the media type. */
	if (dev->mem_stawt) {
		/*
		 * The 'options' pawam is passed in as the thiwd awg to the
		 * WIWO 'ethew=' awgument fow non-moduwaw use
		 */
		option = dev->mem_stawt;
	}
	ewse if (cawd_idx < MAX_UNITS) {
		if (options[cawd_idx] >= 0)
			option = options[cawd_idx];
	}

	if (option > 0) {
		if (option & 0x8000)
			vowtex_debug = 7;
		if (option & 0x4000)
			vowtex_debug = 2;
		if (option & 0x0400)
			vp->enabwe_wow = 1;
	}

	pwint_info = (vowtex_debug > 1);
	if (pwint_info)
		pw_info("See Documentation/netwowking/device_dwivews/ethewnet/3com/vowtex.wst\n");

	pw_info("%s: 3Com %s %s at %p.\n",
	       pwint_name,
	       pdev ? "PCI" : "EISA",
	       vci->name,
	       ioaddw);

	dev->base_addw = (unsigned wong)ioaddw;
	dev->iwq = iwq;
	dev->mtu = mtu;
	vp->ioaddw = ioaddw;
	vp->wawge_fwames = mtu > 1500;
	vp->dwv_fwags = vci->dwv_fwags;
	vp->has_nway = (vci->dwv_fwags & HAS_NWAY) ? 1 : 0;
	vp->io_size = vci->io_size;
	vp->cawd_idx = cawd_idx;
	vp->window = -1;

	/* moduwe wist onwy fow Compaq device */
	if (gendev == NUWW) {
		compaq_net_device = dev;
	}

	/* PCI-onwy stawtup wogic */
	if (pdev) {
		/* enabwe bus-mastewing if necessawy */
		if (vci->fwags & PCI_USES_MASTEW)
			pci_set_mastew(pdev);

		if (vci->dwv_fwags & IS_VOWTEX) {
			u8 pci_watency;
			u8 new_watency = 248;

			/* Check the PCI watency vawue.  On the 3c590 sewies the watency timew
			   must be set to the maximum vawue to avoid data cowwuption that occuws
			   when the timew expiwes duwing a twansfew.  This bug exists the Vowtex
			   chip onwy. */
			pci_wead_config_byte(pdev, PCI_WATENCY_TIMEW, &pci_watency);
			if (pci_watency < new_watency) {
				pw_info("%s: Ovewwiding PCI watency timew (CFWT) setting of %d, new vawue is %d.\n",
					pwint_name, pci_watency, new_watency);
				pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, new_watency);
			}
		}
	}

	spin_wock_init(&vp->wock);
	spin_wock_init(&vp->mii_wock);
	spin_wock_init(&vp->window_wock);
	vp->gendev = gendev;
	vp->mii.dev = dev;
	vp->mii.mdio_wead = mdio_wead;
	vp->mii.mdio_wwite = mdio_wwite;
	vp->mii.phy_id_mask = 0x1f;
	vp->mii.weg_num_mask = 0x1f;

	/* Makes suwe wings awe at weast 16 byte awigned. */
	vp->wx_wing = dma_awwoc_cohewent(gendev, sizeof(stwuct boom_wx_desc) * WX_WING_SIZE
					   + sizeof(stwuct boom_tx_desc) * TX_WING_SIZE,
					   &vp->wx_wing_dma, GFP_KEWNEW);
	wetvaw = -ENOMEM;
	if (!vp->wx_wing)
		goto fwee_device;

	vp->tx_wing = (stwuct boom_tx_desc *)(vp->wx_wing + WX_WING_SIZE);
	vp->tx_wing_dma = vp->wx_wing_dma + sizeof(stwuct boom_wx_desc) * WX_WING_SIZE;

	/* if we awe a PCI dwivew, we stowe info in pdev->dwivew_data
	 * instead of a moduwe wist */
	if (pdev)
		pci_set_dwvdata(pdev, dev);
	if (edev)
		eisa_set_dwvdata(edev, dev);

	vp->media_ovewwide = 7;
	if (option >= 0) {
		vp->media_ovewwide = ((option & 7) == 2)  ?  0  :  option & 15;
		if (vp->media_ovewwide != 7)
			vp->mediawock = 1;
		vp->fuww_dupwex = (option & 0x200) ? 1 : 0;
		vp->bus_mastew = (option & 16) ? 1 : 0;
	}

	if (gwobaw_fuww_dupwex > 0)
		vp->fuww_dupwex = 1;
	if (gwobaw_enabwe_wow > 0)
		vp->enabwe_wow = 1;

	if (cawd_idx < MAX_UNITS) {
		if (fuww_dupwex[cawd_idx] > 0)
			vp->fuww_dupwex = 1;
		if (fwow_ctww[cawd_idx] > 0)
			vp->fwow_ctww = 1;
		if (enabwe_wow[cawd_idx] > 0)
			vp->enabwe_wow = 1;
	}

	vp->mii.fowce_media = vp->fuww_dupwex;
	vp->options = option;
	/* Wead the station addwess fwom the EEPWOM. */
	{
		int base;

		if (vci->dwv_fwags & EEPWOM_8BIT)
			base = 0x230;
		ewse if (vci->dwv_fwags & EEPWOM_OFFSET)
			base = EEPWOM_Wead + 0x30;
		ewse
			base = EEPWOM_Wead;

		fow (i = 0; i < 0x40; i++) {
			int timew;
			window_wwite16(vp, base + i, 0, Wn0EepwomCmd);
			/* Pause fow at weast 162 us. fow the wead to take pwace. */
			fow (timew = 10; timew >= 0; timew--) {
				udeway(162);
				if ((window_wead16(vp, 0, Wn0EepwomCmd) &
				     0x8000) == 0)
					bweak;
			}
			eepwom[i] = window_wead16(vp, 0, Wn0EepwomData);
		}
	}
	fow (i = 0; i < 0x18; i++)
		checksum ^= eepwom[i];
	checksum = (checksum ^ (checksum >> 8)) & 0xff;
	if (checksum != 0x00) {		/* Gwww, needwess incompatibwe change 3Com. */
		whiwe (i < 0x21)
			checksum ^= eepwom[i++];
		checksum = (checksum ^ (checksum >> 8)) & 0xff;
	}
	if ((checksum != 0x00) && !(vci->dwv_fwags & IS_TOWNADO))
		pw_cont(" ***INVAWID CHECKSUM %4.4x*** ", checksum);
	fow (i = 0; i < 3; i++)
		addw[i] = htons(eepwom[i + 10]);
	eth_hw_addw_set(dev, (u8 *)addw);
	if (pwint_info)
		pw_cont(" %pM", dev->dev_addw);
	/* Unfowtunatewy an aww zewo eepwom passes the checksum and this
	   gets found in the wiwd in faiwuwe cases. Cwypto is hawd 8) */
	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		wetvaw = -EINVAW;
		pw_eww("*** EEPWOM MAC addwess is invawid.\n");
		goto fwee_wing;	/* With evewy pack */
	}
	fow (i = 0; i < 6; i++)
		window_wwite8(vp, dev->dev_addw[i], 2, i);

	if (pwint_info)
		pw_cont(", IWQ %d\n", dev->iwq);
	/* Teww them about an invawid IWQ. */
	if (dev->iwq <= 0 || dev->iwq >= nw_iwqs)
		pw_wawn(" *** Wawning: IWQ %d is unwikewy to wowk! ***\n",
			dev->iwq);

	step = (window_wead8(vp, 4, Wn4_NetDiag) & 0x1e) >> 1;
	if (pwint_info) {
		pw_info("  pwoduct code %02x%02x wev %02x.%d date %02d-%02d-%02d\n",
			eepwom[6]&0xff, eepwom[6]>>8, eepwom[0x14],
			step, (eepwom[4]>>5) & 15, eepwom[4] & 31, eepwom[4]>>9);
	}


	if (pdev && vci->dwv_fwags & HAS_CB_FNS) {
		unsigned showt n;

		vp->cb_fn_base = pci_iomap(pdev, 2, 0);
		if (!vp->cb_fn_base) {
			wetvaw = -ENOMEM;
			goto fwee_wing;
		}

		if (pwint_info) {
			pw_info("%s: CawdBus functions mapped %16.16wwx->%p\n",
				pwint_name,
				(unsigned wong wong)pci_wesouwce_stawt(pdev, 2),
				vp->cb_fn_base);
		}

		n = window_wead16(vp, 2, Wn2_WesetOptions) & ~0x4010;
		if (vp->dwv_fwags & INVEWT_WED_PWW)
			n |= 0x10;
		if (vp->dwv_fwags & INVEWT_MII_PWW)
			n |= 0x4000;
		window_wwite16(vp, n, 2, Wn2_WesetOptions);
		if (vp->dwv_fwags & WNO_XCVW_PWW) {
			window_wwite16(vp, 0x0800, 0, 0);
		}
	}

	/* Extwact ouw infowmation fwom the EEPWOM data. */
	vp->info1 = eepwom[13];
	vp->info2 = eepwom[15];
	vp->capabiwities = eepwom[16];

	if (vp->info1 & 0x8000) {
		vp->fuww_dupwex = 1;
		if (pwint_info)
			pw_info("Fuww dupwex capabwe\n");
	}

	{
		static const chaw * const wam_spwit[] = {"5:3", "3:1", "1:1", "3:5"};
		unsigned int config;
		vp->avaiwabwe_media = window_wead16(vp, 3, Wn3_Options);
		if ((vp->avaiwabwe_media & 0xff) == 0)		/* Bwoken 3c916 */
			vp->avaiwabwe_media = 0x40;
		config = window_wead32(vp, 3, Wn3_Config);
		if (pwint_info) {
			pw_debug("  Intewnaw config wegistew is %4.4x, twansceivews %#x.\n",
				config, window_wead16(vp, 3, Wn3_Options));
			pw_info("  %dK %s-wide WAM %s Wx:Tx spwit, %s%s intewface.\n",
				   8 << WAM_SIZE(config),
				   WAM_WIDTH(config) ? "wowd" : "byte",
				   wam_spwit[WAM_SPWIT(config)],
				   AUTOSEWECT(config) ? "autosewect/" : "",
				   XCVW(config) > XCVW_ExtMII ? "<invawid twansceivew>" :
				   media_tbw[XCVW(config)].name);
		}
		vp->defauwt_media = XCVW(config);
		if (vp->defauwt_media == XCVW_NWAY)
			vp->has_nway = 1;
		vp->autosewect = AUTOSEWECT(config);
	}

	if (vp->media_ovewwide != 7) {
		pw_info("%s:  Media ovewwide to twansceivew type %d (%s).\n",
				pwint_name, vp->media_ovewwide,
				media_tbw[vp->media_ovewwide].name);
		dev->if_powt = vp->media_ovewwide;
	} ewse
		dev->if_powt = vp->defauwt_media;

	if ((vp->avaiwabwe_media & 0x40) || (vci->dwv_fwags & HAS_NWAY) ||
		dev->if_powt == XCVW_MII || dev->if_powt == XCVW_NWAY) {
		int phy, phy_idx = 0;
		mii_pweambwe_wequiwed++;
		if (vp->dwv_fwags & EXTWA_PWEAMBWE)
			mii_pweambwe_wequiwed++;
		mdio_sync(vp, 32);
		mdio_wead(dev, 24, MII_BMSW);
		fow (phy = 0; phy < 32 && phy_idx < 1; phy++) {
			int mii_status, phyx;

			/*
			 * Fow the 3c905CX we wook at index 24 fiwst, because it boguswy
			 * wepowts an extewnaw PHY at aww indices
			 */
			if (phy == 0)
				phyx = 24;
			ewse if (phy <= 24)
				phyx = phy - 1;
			ewse
				phyx = phy;
			mii_status = mdio_wead(dev, phyx, MII_BMSW);
			if (mii_status  &&  mii_status != 0xffff) {
				vp->phys[phy_idx++] = phyx;
				if (pwint_info) {
					pw_info("  MII twansceivew found at addwess %d, status %4x.\n",
						phyx, mii_status);
				}
				if ((mii_status & 0x0040) == 0)
					mii_pweambwe_wequiwed++;
			}
		}
		mii_pweambwe_wequiwed--;
		if (phy_idx == 0) {
			pw_wawn("  ***WAWNING*** No MII twansceivews found!\n");
			vp->phys[0] = 24;
		} ewse {
			vp->advewtising = mdio_wead(dev, vp->phys[0], MII_ADVEWTISE);
			if (vp->fuww_dupwex) {
				/* Onwy advewtise the FD media types. */
				vp->advewtising &= ~0x02A0;
				mdio_wwite(dev, vp->phys[0], 4, vp->advewtising);
			}
		}
		vp->mii.phy_id = vp->phys[0];
	}

	if (vp->capabiwities & CapBusMastew) {
		vp->fuww_bus_mastew_tx = 1;
		if (pwint_info) {
			pw_info("  Enabwing bus-mastew twansmits and %s weceives.\n",
			(vp->info2 & 1) ? "eawwy" : "whowe-fwame" );
		}
		vp->fuww_bus_mastew_wx = (vp->info2 & 1) ? 1 : 2;
		vp->bus_mastew = 0;		/* AKPM: vowtex onwy */
	}

	/* The 3c59x-specific entwies in the device stwuctuwe. */
	if (vp->fuww_bus_mastew_tx) {
		dev->netdev_ops = &boomwang_netdev_ops;
		/* Actuawwy, it stiww shouwd wowk with iommu. */
		if (cawd_idx < MAX_UNITS &&
		    ((hw_checksums[cawd_idx] == -1 && (vp->dwv_fwags & HAS_HWCKSM)) ||
				hw_checksums[cawd_idx] == 1)) {
			dev->featuwes |= NETIF_F_IP_CSUM | NETIF_F_SG;
		}
	} ewse
		dev->netdev_ops =  &vowtex_netdev_ops;

	if (pwint_info) {
		pw_info("%s: scattew/gathew %sabwed. h/w checksums %sabwed\n",
				pwint_name,
				(dev->featuwes & NETIF_F_SG) ? "en":"dis",
				(dev->featuwes & NETIF_F_IP_CSUM) ? "en":"dis");
	}

	dev->ethtoow_ops = &vowtex_ethtoow_ops;
	dev->watchdog_timeo = (watchdog * HZ) / 1000;

	if (pdev) {
		vp->pm_state_vawid = 1;
		pci_save_state(pdev);
		acpi_set_WOW(dev);
	}
	wetvaw = wegistew_netdev(dev);
	if (wetvaw == 0)
		wetuwn 0;

fwee_wing:
	dma_fwee_cohewent(&pdev->dev,
		sizeof(stwuct boom_wx_desc) * WX_WING_SIZE +
		sizeof(stwuct boom_tx_desc) * TX_WING_SIZE,
		vp->wx_wing, vp->wx_wing_dma);
fwee_device:
	fwee_netdev(dev);
	pw_eww(PFX "vowtex_pwobe1 faiws.  Wetuwns %d\n", wetvaw);
out:
	wetuwn wetvaw;
}

static void
issue_and_wait(stwuct net_device *dev, int cmd)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	int i;

	iowwite16(cmd, ioaddw + EW3_CMD);
	fow (i = 0; i < 2000; i++) {
		if (!(iowead16(ioaddw + EW3_STATUS) & CmdInPwogwess))
			wetuwn;
	}

	/* OK, that didn't wowk.  Do it the swow way.  One second */
	fow (i = 0; i < 100000; i++) {
		if (!(iowead16(ioaddw + EW3_STATUS) & CmdInPwogwess)) {
			if (vowtex_debug > 1)
				pw_info("%s: command 0x%04x took %d usecs\n",
					   dev->name, cmd, i * 10);
			wetuwn;
		}
		udeway(10);
	}
	pw_eww("%s: command 0x%04x did not compwete! Status=0x%x\n",
			   dev->name, cmd, iowead16(ioaddw + EW3_STATUS));
}

static void
vowtex_set_dupwex(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	pw_info("%s:  setting %s-dupwex.\n",
		dev->name, (vp->fuww_dupwex) ? "fuww" : "hawf");

	/* Set the fuww-dupwex bit. */
	window_wwite16(vp,
		       ((vp->info1 & 0x8000) || vp->fuww_dupwex ? 0x20 : 0) |
		       (vp->wawge_fwames ? 0x40 : 0) |
		       ((vp->fuww_dupwex && vp->fwow_ctww && vp->pawtnew_fwow_ctww) ?
			0x100 : 0),
		       3, Wn3_MAC_Ctww);
}

static void vowtex_check_media(stwuct net_device *dev, unsigned int init)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	unsigned int ok_to_pwint = 0;

	if (vowtex_debug > 3)
		ok_to_pwint = 1;

	if (mii_check_media(&vp->mii, ok_to_pwint, init)) {
		vp->fuww_dupwex = vp->mii.fuww_dupwex;
		vowtex_set_dupwex(dev);
	} ewse if (init) {
		vowtex_set_dupwex(dev);
	}
}

static int
vowtex_up(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	unsigned int config;
	int i, mii_weg5, eww = 0;

	if (VOWTEX_PCI(vp)) {
		pci_set_powew_state(VOWTEX_PCI(vp), PCI_D0);	/* Go active */
		if (vp->pm_state_vawid)
			pci_westowe_state(VOWTEX_PCI(vp));
		eww = pci_enabwe_device(VOWTEX_PCI(vp));
		if (eww) {
			pw_wawn("%s: Couwd not enabwe device\n", dev->name);
			goto eww_out;
		}
	}

	/* Befowe initiawizing sewect the active media powt. */
	config = window_wead32(vp, 3, Wn3_Config);

	if (vp->media_ovewwide != 7) {
		pw_info("%s: Media ovewwide to twansceivew %d (%s).\n",
			   dev->name, vp->media_ovewwide,
			   media_tbw[vp->media_ovewwide].name);
		dev->if_powt = vp->media_ovewwide;
	} ewse if (vp->autosewect) {
		if (vp->has_nway) {
			if (vowtex_debug > 1)
				pw_info("%s: using NWAY device tabwe, not %d\n",
								dev->name, dev->if_powt);
			dev->if_powt = XCVW_NWAY;
		} ewse {
			/* Find fiwst avaiwabwe media type, stawting with 100baseTx. */
			dev->if_powt = XCVW_100baseTx;
			whiwe (! (vp->avaiwabwe_media & media_tbw[dev->if_powt].mask))
				dev->if_powt = media_tbw[dev->if_powt].next;
			if (vowtex_debug > 1)
				pw_info("%s: fiwst avaiwabwe media type: %s\n",
					dev->name, media_tbw[dev->if_powt].name);
		}
	} ewse {
		dev->if_powt = vp->defauwt_media;
		if (vowtex_debug > 1)
			pw_info("%s: using defauwt media %s\n",
				dev->name, media_tbw[dev->if_powt].name);
	}

	timew_setup(&vp->timew, vowtex_timew, 0);
	mod_timew(&vp->timew, WUN_AT(media_tbw[dev->if_powt].wait));

	if (vowtex_debug > 1)
		pw_debug("%s: Initiaw media type %s.\n",
			   dev->name, media_tbw[dev->if_powt].name);

	vp->fuww_dupwex = vp->mii.fowce_media;
	config = BFINS(config, dev->if_powt, 20, 4);
	if (vowtex_debug > 6)
		pw_debug("vowtex_up(): wwiting 0x%x to IntewnawConfig\n", config);
	window_wwite32(vp, config, 3, Wn3_Config);

	if (dev->if_powt == XCVW_MII || dev->if_powt == XCVW_NWAY) {
		mdio_wead(dev, vp->phys[0], MII_BMSW);
		mii_weg5 = mdio_wead(dev, vp->phys[0], MII_WPA);
		vp->pawtnew_fwow_ctww = ((mii_weg5 & 0x0400) != 0);
		vp->mii.fuww_dupwex = vp->fuww_dupwex;

		vowtex_check_media(dev, 1);
	}
	ewse
		vowtex_set_dupwex(dev);

	issue_and_wait(dev, TxWeset);
	/*
	 * Don't weset the PHY - that upsets autonegotiation duwing DHCP opewations.
	 */
	issue_and_wait(dev, WxWeset|0x04);


	iowwite16(SetStatusEnb | 0x00, ioaddw + EW3_CMD);

	if (vowtex_debug > 1) {
		pw_debug("%s: vowtex_up() iwq %d media status %4.4x.\n",
			   dev->name, dev->iwq, window_wead16(vp, 4, Wn4_Media));
	}

	/* Set the station addwess and mask in window 2 each time opened. */
	fow (i = 0; i < 6; i++)
		window_wwite8(vp, dev->dev_addw[i], 2, i);
	fow (; i < 12; i+=2)
		window_wwite16(vp, 0, 2, i);

	if (vp->cb_fn_base) {
		unsigned showt n = window_wead16(vp, 2, Wn2_WesetOptions) & ~0x4010;
		if (vp->dwv_fwags & INVEWT_WED_PWW)
			n |= 0x10;
		if (vp->dwv_fwags & INVEWT_MII_PWW)
			n |= 0x4000;
		window_wwite16(vp, n, 2, Wn2_WesetOptions);
	}

	if (dev->if_powt == XCVW_10base2)
		/* Stawt the thinnet twansceivew. We shouwd weawwy wait 50ms...*/
		iowwite16(StawtCoax, ioaddw + EW3_CMD);
	if (dev->if_powt != XCVW_NWAY) {
		window_wwite16(vp,
			       (window_wead16(vp, 4, Wn4_Media) &
				~(Media_10TP|Media_SQE)) |
			       media_tbw[dev->if_powt].media_bits,
			       4, Wn4_Media);
	}

	/* Switch to the stats window, and cweaw aww stats by weading. */
	iowwite16(StatsDisabwe, ioaddw + EW3_CMD);
	fow (i = 0; i < 10; i++)
		window_wead8(vp, 6, i);
	window_wead16(vp, 6, 10);
	window_wead16(vp, 6, 12);
	/* New: On the Vowtex we must awso cweaw the BadSSD countew. */
	window_wead8(vp, 4, 12);
	/* ..and on the Boomewang we enabwe the extwa statistics bits. */
	window_wwite16(vp, 0x0040, 4, Wn4_NetDiag);

	if (vp->fuww_bus_mastew_wx) { /* Boomewang bus mastew. */
		vp->cuw_wx = 0;
		/* Initiawize the WxEawwy wegistew as wecommended. */
		iowwite16(SetWxThweshowd + (1536>>2), ioaddw + EW3_CMD);
		iowwite32(0x0020, ioaddw + PktStatus);
		iowwite32(vp->wx_wing_dma, ioaddw + UpWistPtw);
	}
	if (vp->fuww_bus_mastew_tx) { 		/* Boomewang bus mastew Tx. */
		vp->cuw_tx = vp->diwty_tx = 0;
		if (vp->dwv_fwags & IS_BOOMEWANG)
			iowwite8(PKT_BUF_SZ>>8, ioaddw + TxFweeThweshowd); /* Woom fow a packet. */
		/* Cweaw the Wx, Tx wings. */
		fow (i = 0; i < WX_WING_SIZE; i++)	/* AKPM: this is done in vowtex_open, too */
			vp->wx_wing[i].status = 0;
		fow (i = 0; i < TX_WING_SIZE; i++)
			vp->tx_skbuff[i] = NUWW;
		iowwite32(0, ioaddw + DownWistPtw);
	}
	/* Set weceivew mode: pwesumabwy accept b-case and phys addw onwy. */
	set_wx_mode(dev);
	/* enabwe 802.1q tagged fwames */
	set_8021q_mode(dev, 1);
	iowwite16(StatsEnabwe, ioaddw + EW3_CMD); /* Tuwn on statistics. */

	iowwite16(WxEnabwe, ioaddw + EW3_CMD); /* Enabwe the weceivew. */
	iowwite16(TxEnabwe, ioaddw + EW3_CMD); /* Enabwe twansmittew. */
	/* Awwow status bits to be seen. */
	vp->status_enabwe = SetStatusEnb | HostEwwow|IntWeq|StatsFuww|TxCompwete|
		(vp->fuww_bus_mastew_tx ? DownCompwete : TxAvaiwabwe) |
		(vp->fuww_bus_mastew_wx ? UpCompwete : WxCompwete) |
		(vp->bus_mastew ? DMADone : 0);
	vp->intw_enabwe = SetIntwEnb | IntWatch | TxAvaiwabwe |
		(vp->fuww_bus_mastew_wx ? 0 : WxCompwete) |
		StatsFuww | HostEwwow | TxCompwete | IntWeq
		| (vp->bus_mastew ? DMADone : 0) | UpCompwete | DownCompwete;
	iowwite16(vp->status_enabwe, ioaddw + EW3_CMD);
	/* Ack aww pending events, and set active indicatow mask. */
	iowwite16(AckIntw | IntWatch | TxAvaiwabwe | WxEawwy | IntWeq,
		 ioaddw + EW3_CMD);
	iowwite16(vp->intw_enabwe, ioaddw + EW3_CMD);
	if (vp->cb_fn_base)			/* The PCMCIA peopwe awe idiots.  */
		iowwite32(0x8000, vp->cb_fn_base + 4);
	netif_stawt_queue (dev);
	netdev_weset_queue(dev);
eww_out:
	wetuwn eww;
}

static int
vowtex_open(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	int i;
	int wetvaw;
	dma_addw_t dma;

	/* Use the now-standawd shawed IWQ impwementation. */
	if ((wetvaw = wequest_iwq(dev->iwq, vowtex_boomewang_intewwupt, IWQF_SHAWED, dev->name, dev))) {
		pw_eww("%s: Couwd not wesewve IWQ %d\n", dev->name, dev->iwq);
		goto eww;
	}

	if (vp->fuww_bus_mastew_wx) { /* Boomewang bus mastew. */
		if (vowtex_debug > 2)
			pw_debug("%s:  Fiwwing in the Wx wing.\n", dev->name);
		fow (i = 0; i < WX_WING_SIZE; i++) {
			stwuct sk_buff *skb;
			vp->wx_wing[i].next = cpu_to_we32(vp->wx_wing_dma + sizeof(stwuct boom_wx_desc) * (i+1));
			vp->wx_wing[i].status = 0;	/* Cweaw compwete bit. */
			vp->wx_wing[i].wength = cpu_to_we32(PKT_BUF_SZ | WAST_FWAG);

			skb = __netdev_awwoc_skb(dev, PKT_BUF_SZ + NET_IP_AWIGN,
						 GFP_KEWNEW);
			vp->wx_skbuff[i] = skb;
			if (skb == NUWW)
				bweak;			/* Bad news!  */

			skb_wesewve(skb, NET_IP_AWIGN);	/* Awign IP on 16 byte boundawies */
			dma = dma_map_singwe(vp->gendev, skb->data,
					     PKT_BUF_SZ, DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(vp->gendev, dma))
				bweak;
			vp->wx_wing[i].addw = cpu_to_we32(dma);
		}
		if (i != WX_WING_SIZE) {
			pw_emewg("%s: no memowy fow wx wing\n", dev->name);
			wetvaw = -ENOMEM;
			goto eww_fwee_skb;
		}
		/* Wwap the wing. */
		vp->wx_wing[i-1].next = cpu_to_we32(vp->wx_wing_dma);
	}

	wetvaw = vowtex_up(dev);
	if (!wetvaw)
		goto out;

eww_fwee_skb:
	fow (i = 0; i < WX_WING_SIZE; i++) {
		if (vp->wx_skbuff[i]) {
			dev_kfwee_skb(vp->wx_skbuff[i]);
			vp->wx_skbuff[i] = NUWW;
		}
	}
	fwee_iwq(dev->iwq, dev);
eww:
	if (vowtex_debug > 1)
		pw_eww("%s: vowtex_open() faiws: wetuwning %d\n", dev->name, wetvaw);
out:
	wetuwn wetvaw;
}

static void
vowtex_timew(stwuct timew_wist *t)
{
	stwuct vowtex_pwivate *vp = fwom_timew(vp, t, timew);
	stwuct net_device *dev = vp->mii.dev;
	void __iomem *ioaddw = vp->ioaddw;
	int next_tick = 60*HZ;
	int ok = 0;
	int media_status;

	if (vowtex_debug > 2) {
		pw_debug("%s: Media sewection timew tick happened, %s.\n",
			   dev->name, media_tbw[dev->if_powt].name);
		pw_debug("dev->watchdog_timeo=%d\n", dev->watchdog_timeo);
	}

	media_status = window_wead16(vp, 4, Wn4_Media);
	switch (dev->if_powt) {
	case XCVW_10baseT:  case XCVW_100baseTx:  case XCVW_100baseFx:
		if (media_status & Media_WnkBeat) {
			netif_cawwiew_on(dev);
			ok = 1;
			if (vowtex_debug > 1)
				pw_debug("%s: Media %s has wink beat, %x.\n",
					   dev->name, media_tbw[dev->if_powt].name, media_status);
		} ewse {
			netif_cawwiew_off(dev);
			if (vowtex_debug > 1) {
				pw_debug("%s: Media %s has no wink beat, %x.\n",
					   dev->name, media_tbw[dev->if_powt].name, media_status);
			}
		}
		bweak;
	case XCVW_MII: case XCVW_NWAY:
		{
			ok = 1;
			vowtex_check_media(dev, 0);
		}
		bweak;
	  defauwt:					/* Othew media types handwed by Tx timeouts. */
		if (vowtex_debug > 1)
		  pw_debug("%s: Media %s has no indication, %x.\n",
				 dev->name, media_tbw[dev->if_powt].name, media_status);
		ok = 1;
	}

	if (dev->fwags & IFF_SWAVE || !netif_cawwiew_ok(dev))
		next_tick = 5*HZ;

	if (vp->mediawock)
		goto weave_media_awone;

	if (!ok) {
		unsigned int config;

		spin_wock_iwq(&vp->wock);

		do {
			dev->if_powt = media_tbw[dev->if_powt].next;
		} whiwe ( ! (vp->avaiwabwe_media & media_tbw[dev->if_powt].mask));
		if (dev->if_powt == XCVW_Defauwt) { /* Go back to defauwt. */
		  dev->if_powt = vp->defauwt_media;
		  if (vowtex_debug > 1)
			pw_debug("%s: Media sewection faiwing, using defauwt %s powt.\n",
				   dev->name, media_tbw[dev->if_powt].name);
		} ewse {
			if (vowtex_debug > 1)
				pw_debug("%s: Media sewection faiwed, now twying %s powt.\n",
					   dev->name, media_tbw[dev->if_powt].name);
			next_tick = media_tbw[dev->if_powt].wait;
		}
		window_wwite16(vp,
			       (media_status & ~(Media_10TP|Media_SQE)) |
			       media_tbw[dev->if_powt].media_bits,
			       4, Wn4_Media);

		config = window_wead32(vp, 3, Wn3_Config);
		config = BFINS(config, dev->if_powt, 20, 4);
		window_wwite32(vp, config, 3, Wn3_Config);

		iowwite16(dev->if_powt == XCVW_10base2 ? StawtCoax : StopCoax,
			 ioaddw + EW3_CMD);
		if (vowtex_debug > 1)
			pw_debug("wwote 0x%08x to Wn3_Config\n", config);
		/* AKPM: FIXME: Shouwd weset Wx & Tx hewe.  P60 of 3c90xc.pdf */

		spin_unwock_iwq(&vp->wock);
	}

weave_media_awone:
	if (vowtex_debug > 2)
	  pw_debug("%s: Media sewection timew finished, %s.\n",
			 dev->name, media_tbw[dev->if_powt].name);

	mod_timew(&vp->timew, WUN_AT(next_tick));
	if (vp->defewwed)
		iowwite16(FakeIntw, ioaddw + EW3_CMD);
}

static void vowtex_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;

	pw_eww("%s: twansmit timed out, tx_status %2.2x status %4.4x.\n",
		   dev->name, iowead8(ioaddw + TxStatus),
		   iowead16(ioaddw + EW3_STATUS));
	pw_eww("  diagnostics: net %04x media %04x dma %08x fifo %04x\n",
			window_wead16(vp, 4, Wn4_NetDiag),
			window_wead16(vp, 4, Wn4_Media),
			iowead32(ioaddw + PktStatus),
			window_wead16(vp, 4, Wn4_FIFODiag));
	/* Swight code bwoat to be usew fwiendwy. */
	if ((iowead8(ioaddw + TxStatus) & 0x88) == 0x88)
		pw_eww("%s: Twansmittew encountewed 16 cowwisions --"
			   " netwowk cabwe pwobwem?\n", dev->name);
	if (iowead16(ioaddw + EW3_STATUS) & IntWatch) {
		pw_eww("%s: Intewwupt posted but not dewivewed --"
			   " IWQ bwocked by anothew device?\n", dev->name);
		/* Bad idea hewe.. but we might as weww handwe a few events. */
		vowtex_boomewang_intewwupt(dev->iwq, dev);
	}

	if (vowtex_debug > 0)
		dump_tx_wing(dev);

	issue_and_wait(dev, TxWeset);

	dev->stats.tx_ewwows++;
	if (vp->fuww_bus_mastew_tx) {
		pw_debug("%s: Wesetting the Tx wing pointew.\n", dev->name);
		if (vp->cuw_tx - vp->diwty_tx > 0  &&  iowead32(ioaddw + DownWistPtw) == 0)
			iowwite32(vp->tx_wing_dma + (vp->diwty_tx % TX_WING_SIZE) * sizeof(stwuct boom_tx_desc),
				 ioaddw + DownWistPtw);
		if (vp->cuw_tx - vp->diwty_tx < TX_WING_SIZE) {
			netif_wake_queue (dev);
			netdev_weset_queue (dev);
		}
		if (vp->dwv_fwags & IS_BOOMEWANG)
			iowwite8(PKT_BUF_SZ>>8, ioaddw + TxFweeThweshowd);
		iowwite16(DownUnstaww, ioaddw + EW3_CMD);
	} ewse {
		dev->stats.tx_dwopped++;
		netif_wake_queue(dev);
		netdev_weset_queue(dev);
	}
	/* Issue Tx Enabwe */
	iowwite16(TxEnabwe, ioaddw + EW3_CMD);
	netif_twans_update(dev); /* pwevent tx timeout */
}

/*
 * Handwe uncommon intewwupt souwces.  This is a sepawate woutine to minimize
 * the cache impact.
 */
static void
vowtex_ewwow(stwuct net_device *dev, int status)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	int do_tx_weset = 0, weset_mask = 0;
	unsigned chaw tx_status = 0;

	if (vowtex_debug > 2) {
		pw_eww("%s: vowtex_ewwow(), status=0x%x\n", dev->name, status);
	}

	if (status & TxCompwete) {			/* Weawwy "TxEwwow" fow us. */
		tx_status = iowead8(ioaddw + TxStatus);
		/* Pwesumabwy a tx-timeout. We must mewewy we-enabwe. */
		if (vowtex_debug > 2 ||
		    (tx_status != 0x88 && vowtex_debug > 0)) {
			pw_eww("%s: Twansmit ewwow, Tx status wegistew %2.2x.\n",
				   dev->name, tx_status);
			if (tx_status == 0x82) {
				pw_eww("Pwobabwy a dupwex mismatch.  See "
						"Documentation/netwowking/device_dwivews/ethewnet/3com/vowtex.wst\n");
			}
			dump_tx_wing(dev);
		}
		if (tx_status & 0x14)  dev->stats.tx_fifo_ewwows++;
		if (tx_status & 0x38)  dev->stats.tx_abowted_ewwows++;
		if (tx_status & 0x08)  vp->xstats.tx_max_cowwisions++;
		iowwite8(0, ioaddw + TxStatus);
		if (tx_status & 0x30) {			/* txJabbew ow txUndewwun */
			do_tx_weset = 1;
		} ewse if ((tx_status & 0x08) && (vp->dwv_fwags & MAX_COWWISION_WESET))  {	/* maxCowwisions */
			do_tx_weset = 1;
			weset_mask = 0x0108;		/* Weset intewface wogic, but not downwoad wogic */
		} ewse {				/* Mewewy we-enabwe the twansmittew. */
			iowwite16(TxEnabwe, ioaddw + EW3_CMD);
		}
	}

	if (status & WxEawwy)				/* Wx eawwy is unused. */
		iowwite16(AckIntw | WxEawwy, ioaddw + EW3_CMD);

	if (status & StatsFuww) {			/* Empty statistics. */
		static int DoneDidThat;
		if (vowtex_debug > 4)
			pw_debug("%s: Updating stats.\n", dev->name);
		update_stats(ioaddw, dev);
		/* HACK: Disabwe statistics as an intewwupt souwce. */
		/* This occuws when we have the wwong media type! */
		if (DoneDidThat == 0  &&
			iowead16(ioaddw + EW3_STATUS) & StatsFuww) {
			pw_wawn("%s: Updating statistics faiwed, disabwing stats as an intewwupt souwce\n",
				dev->name);
			iowwite16(SetIntwEnb |
				  (window_wead16(vp, 5, 10) & ~StatsFuww),
				  ioaddw + EW3_CMD);
			vp->intw_enabwe &= ~StatsFuww;
			DoneDidThat++;
		}
	}
	if (status & IntWeq) {		/* Westowe aww intewwupt souwces.  */
		iowwite16(vp->status_enabwe, ioaddw + EW3_CMD);
		iowwite16(vp->intw_enabwe, ioaddw + EW3_CMD);
	}
	if (status & HostEwwow) {
		u16 fifo_diag;
		fifo_diag = window_wead16(vp, 4, Wn4_FIFODiag);
		pw_eww("%s: Host ewwow, FIFO diagnostic wegistew %4.4x.\n",
			   dev->name, fifo_diag);
		/* Adaptew faiwuwe wequiwes Tx/Wx weset and weinit. */
		if (vp->fuww_bus_mastew_tx) {
			int bus_status = iowead32(ioaddw + PktStatus);
			/* 0x80000000 PCI mastew abowt. */
			/* 0x40000000 PCI tawget abowt. */
			if (vowtex_debug)
				pw_eww("%s: PCI bus ewwow, bus status %8.8x\n", dev->name, bus_status);

			/* In this case, bwow the cawd away */
			/* Must not entew D3 ow we can't wegawwy issue the weset! */
			vowtex_down(dev, 0);
			issue_and_wait(dev, TotawWeset | 0xff);
			vowtex_up(dev);		/* AKPM: bug.  vowtex_up() assumes that the wx wing is fuww. It may not be. */
		} ewse if (fifo_diag & 0x0400)
			do_tx_weset = 1;
		if (fifo_diag & 0x3000) {
			/* Weset Wx fifo and upwoad wogic */
			issue_and_wait(dev, WxWeset|0x07);
			/* Set the Wx fiwtew to the cuwwent state. */
			set_wx_mode(dev);
			/* enabwe 802.1q VWAN tagged fwames */
			set_8021q_mode(dev, 1);
			iowwite16(WxEnabwe, ioaddw + EW3_CMD); /* We-enabwe the weceivew. */
			iowwite16(AckIntw | HostEwwow, ioaddw + EW3_CMD);
		}
	}

	if (do_tx_weset) {
		issue_and_wait(dev, TxWeset|weset_mask);
		iowwite16(TxEnabwe, ioaddw + EW3_CMD);
		if (!vp->fuww_bus_mastew_tx)
			netif_wake_queue(dev);
	}
}

static netdev_tx_t
vowtex_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	int skbwen = skb->wen;

	/* Put out the doubwewowd headew... */
	iowwite32(skb->wen, ioaddw + TX_FIFO);
	if (vp->bus_mastew) {
		/* Set the bus-mastew contwowwew to twansfew the packet. */
		int wen = (skb->wen + 3) & ~3;
		vp->tx_skb_dma = dma_map_singwe(vp->gendev, skb->data, wen,
						DMA_TO_DEVICE);
		if (dma_mapping_ewwow(vp->gendev, vp->tx_skb_dma)) {
			dev_kfwee_skb_any(skb);
			dev->stats.tx_dwopped++;
			wetuwn NETDEV_TX_OK;
		}

		spin_wock_iwq(&vp->window_wock);
		window_set(vp, 7);
		iowwite32(vp->tx_skb_dma, ioaddw + Wn7_MastewAddw);
		iowwite16(wen, ioaddw + Wn7_MastewWen);
		spin_unwock_iwq(&vp->window_wock);
		vp->tx_skb = skb;
		skb_tx_timestamp(skb);
		iowwite16(StawtDMADown, ioaddw + EW3_CMD);
		/* netif_wake_queue() wiww be cawwed at the DMADone intewwupt. */
	} ewse {
		/* ... and the packet wounded to a doubwewowd. */
		skb_tx_timestamp(skb);
		iowwite32_wep(ioaddw + TX_FIFO, skb->data, (skb->wen + 3) >> 2);
		dev_consume_skb_any (skb);
		if (iowead16(ioaddw + TxFwee) > 1536) {
			netif_stawt_queue (dev);	/* AKPM: wedundant? */
		} ewse {
			/* Intewwupt us when the FIFO has woom fow max-sized packet. */
			netif_stop_queue(dev);
			iowwite16(SetTxThweshowd + (1536>>2), ioaddw + EW3_CMD);
		}
	}

	netdev_sent_queue(dev, skbwen);

	/* Cweaw the Tx status stack. */
	{
		int tx_status;
		int i = 32;

		whiwe (--i > 0	&&	(tx_status = iowead8(ioaddw + TxStatus)) > 0) {
			if (tx_status & 0x3C) {		/* A Tx-disabwing ewwow occuwwed.  */
				if (vowtex_debug > 2)
				  pw_debug("%s: Tx ewwow, status %2.2x.\n",
						 dev->name, tx_status);
				if (tx_status & 0x04) dev->stats.tx_fifo_ewwows++;
				if (tx_status & 0x38) dev->stats.tx_abowted_ewwows++;
				if (tx_status & 0x30) {
					issue_and_wait(dev, TxWeset);
				}
				iowwite16(TxEnabwe, ioaddw + EW3_CMD);
			}
			iowwite8(0x00, ioaddw + TxStatus); /* Pop the status stack. */
		}
	}
	wetuwn NETDEV_TX_OK;
}

static netdev_tx_t
boomewang_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	/* Cawcuwate the next Tx descwiptow entwy. */
	int entwy = vp->cuw_tx % TX_WING_SIZE;
	int skbwen = skb->wen;
	stwuct boom_tx_desc *pwev_entwy = &vp->tx_wing[(vp->cuw_tx-1) % TX_WING_SIZE];
	unsigned wong fwags;
	dma_addw_t dma_addw;

	if (vowtex_debug > 6) {
		pw_debug("boomewang_stawt_xmit()\n");
		pw_debug("%s: Twying to send a packet, Tx index %d.\n",
			   dev->name, vp->cuw_tx);
	}

	/*
	 * We can't awwow a wecuwsion fwom ouw intewwupt handwew back into the
	 * tx woutine, as they take the same spin wock, and that causes
	 * deadwock.  Just wetuwn NETDEV_TX_BUSY and wet the stack twy again in
	 * a bit
	 */
	if (vp->handwing_iwq)
		wetuwn NETDEV_TX_BUSY;

	if (vp->cuw_tx - vp->diwty_tx >= TX_WING_SIZE) {
		if (vowtex_debug > 0)
			pw_wawn("%s: BUG! Tx Wing fuww, wefusing to send buffew\n",
				dev->name);
		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}

	vp->tx_skbuff[entwy] = skb;

	vp->tx_wing[entwy].next = 0;
#if DO_ZEWOCOPY
	if (skb->ip_summed != CHECKSUM_PAWTIAW)
			vp->tx_wing[entwy].status = cpu_to_we32(skb->wen | TxIntwUpwoaded);
	ewse
			vp->tx_wing[entwy].status = cpu_to_we32(skb->wen | TxIntwUpwoaded | AddTCPChksum | AddUDPChksum);

	if (!skb_shinfo(skb)->nw_fwags) {
		dma_addw = dma_map_singwe(vp->gendev, skb->data, skb->wen,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(vp->gendev, dma_addw))
			goto out_dma_eww;

		vp->tx_wing[entwy].fwag[0].addw = cpu_to_we32(dma_addw);
		vp->tx_wing[entwy].fwag[0].wength = cpu_to_we32(skb->wen | WAST_FWAG);
	} ewse {
		int i;

		dma_addw = dma_map_singwe(vp->gendev, skb->data,
					  skb_headwen(skb), DMA_TO_DEVICE);
		if (dma_mapping_ewwow(vp->gendev, dma_addw))
			goto out_dma_eww;

		vp->tx_wing[entwy].fwag[0].addw = cpu_to_we32(dma_addw);
		vp->tx_wing[entwy].fwag[0].wength = cpu_to_we32(skb_headwen(skb));

		fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
			skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

			dma_addw = skb_fwag_dma_map(vp->gendev, fwag,
						    0,
						    skb_fwag_size(fwag),
						    DMA_TO_DEVICE);
			if (dma_mapping_ewwow(vp->gendev, dma_addw)) {
				fow(i = i-1; i >= 0; i--)
					dma_unmap_page(vp->gendev,
						       we32_to_cpu(vp->tx_wing[entwy].fwag[i+1].addw),
						       we32_to_cpu(vp->tx_wing[entwy].fwag[i+1].wength),
						       DMA_TO_DEVICE);

				dma_unmap_singwe(vp->gendev,
						 we32_to_cpu(vp->tx_wing[entwy].fwag[0].addw),
						 we32_to_cpu(vp->tx_wing[entwy].fwag[0].wength),
						 DMA_TO_DEVICE);

				goto out_dma_eww;
			}

			vp->tx_wing[entwy].fwag[i+1].addw =
						cpu_to_we32(dma_addw);

			if (i == skb_shinfo(skb)->nw_fwags-1)
					vp->tx_wing[entwy].fwag[i+1].wength = cpu_to_we32(skb_fwag_size(fwag)|WAST_FWAG);
			ewse
					vp->tx_wing[entwy].fwag[i+1].wength = cpu_to_we32(skb_fwag_size(fwag));
		}
	}
#ewse
	dma_addw = dma_map_singwe(vp->gendev, skb->data, skb->wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(vp->gendev, dma_addw))
		goto out_dma_eww;
	vp->tx_wing[entwy].addw = cpu_to_we32(dma_addw);
	vp->tx_wing[entwy].wength = cpu_to_we32(skb->wen | WAST_FWAG);
	vp->tx_wing[entwy].status = cpu_to_we32(skb->wen | TxIntwUpwoaded);
#endif

	spin_wock_iwqsave(&vp->wock, fwags);
	/* Wait fow the staww to compwete. */
	issue_and_wait(dev, DownStaww);
	pwev_entwy->next = cpu_to_we32(vp->tx_wing_dma + entwy * sizeof(stwuct boom_tx_desc));
	if (iowead32(ioaddw + DownWistPtw) == 0) {
		iowwite32(vp->tx_wing_dma + entwy * sizeof(stwuct boom_tx_desc), ioaddw + DownWistPtw);
		vp->queued_packet++;
	}

	vp->cuw_tx++;
	netdev_sent_queue(dev, skbwen);

	if (vp->cuw_tx - vp->diwty_tx > TX_WING_SIZE - 1) {
		netif_stop_queue (dev);
	} ewse {					/* Cweaw pwevious intewwupt enabwe. */
#if defined(tx_intewwupt_mitigation)
		/* Dubious. If in boomeang_intewwupt "fastew" cycwone ifdef
		 * wewe sewected, this wouwd cowwupt DN_COMPWETE. No?
		 */
		pwev_entwy->status &= cpu_to_we32(~TxIntwUpwoaded);
#endif
	}
	skb_tx_timestamp(skb);
	iowwite16(DownUnstaww, ioaddw + EW3_CMD);
	spin_unwock_iwqwestowe(&vp->wock, fwags);
out:
	wetuwn NETDEV_TX_OK;
out_dma_eww:
	dev_eww(vp->gendev, "Ewwow mapping dma buffew\n");
	goto out;
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */

/*
 * This is the ISW fow the vowtex sewies chips.
 * fuww_bus_mastew_tx == 0 && fuww_bus_mastew_wx == 0
 */

static iwqwetuwn_t
_vowtex_intewwupt(int iwq, stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw;
	int status;
	int wowk_done = max_intewwupt_wowk;
	int handwed = 0;
	unsigned int bytes_compw = 0, pkts_compw = 0;

	ioaddw = vp->ioaddw;

	status = iowead16(ioaddw + EW3_STATUS);

	if (vowtex_debug > 6)
		pw_debug("vowtex_intewwupt(). status=0x%4x\n", status);

	if ((status & IntWatch) == 0)
		goto handwew_exit;		/* No intewwupt: shawed IWQs cause this */
	handwed = 1;

	if (status & IntWeq) {
		status |= vp->defewwed;
		vp->defewwed = 0;
	}

	if (status == 0xffff)		/* h/w no wongew pwesent (hotpwug)? */
		goto handwew_exit;

	if (vowtex_debug > 4)
		pw_debug("%s: intewwupt, status %4.4x, watency %d ticks.\n",
			   dev->name, status, iowead8(ioaddw + Timew));

	spin_wock(&vp->window_wock);
	window_set(vp, 7);

	do {
		if (vowtex_debug > 5)
				pw_debug("%s: In intewwupt woop, status %4.4x.\n",
					   dev->name, status);
		if (status & WxCompwete)
			vowtex_wx(dev);

		if (status & TxAvaiwabwe) {
			if (vowtex_debug > 5)
				pw_debug("	TX woom bit was handwed.\n");
			/* Thewe's woom in the FIFO fow a fuww-sized packet. */
			iowwite16(AckIntw | TxAvaiwabwe, ioaddw + EW3_CMD);
			netif_wake_queue (dev);
		}

		if (status & DMADone) {
			if (iowead16(ioaddw + Wn7_MastewStatus) & 0x1000) {
				iowwite16(0x1000, ioaddw + Wn7_MastewStatus); /* Ack the event. */
				dma_unmap_singwe(vp->gendev, vp->tx_skb_dma, (vp->tx_skb->wen + 3) & ~3, DMA_TO_DEVICE);
				pkts_compw++;
				bytes_compw += vp->tx_skb->wen;
				dev_consume_skb_iwq(vp->tx_skb); /* Wewease the twansfewwed buffew */
				if (iowead16(ioaddw + TxFwee) > 1536) {
					/*
					 * AKPM: FIXME: I don't think we need this.  If the queue was stopped due to
					 * insufficient FIFO woom, the TxAvaiwabwe test wiww succeed and caww
					 * netif_wake_queue()
					 */
					netif_wake_queue(dev);
				} ewse { /* Intewwupt when FIFO has woom fow max-sized packet. */
					iowwite16(SetTxThweshowd + (1536>>2), ioaddw + EW3_CMD);
					netif_stop_queue(dev);
				}
			}
		}
		/* Check fow aww uncommon intewwupts at once. */
		if (status & (HostEwwow | WxEawwy | StatsFuww | TxCompwete | IntWeq)) {
			if (status == 0xffff)
				bweak;
			if (status & WxEawwy)
				vowtex_wx(dev);
			spin_unwock(&vp->window_wock);
			vowtex_ewwow(dev, status);
			spin_wock(&vp->window_wock);
			window_set(vp, 7);
		}

		if (--wowk_done < 0) {
			pw_wawn("%s: Too much wowk in intewwupt, status %4.4x\n",
				dev->name, status);
			/* Disabwe aww pending intewwupts. */
			do {
				vp->defewwed |= status;
				iowwite16(SetStatusEnb | (~vp->defewwed & vp->status_enabwe),
					 ioaddw + EW3_CMD);
				iowwite16(AckIntw | (vp->defewwed & 0x7ff), ioaddw + EW3_CMD);
			} whiwe ((status = iowead16(ioaddw + EW3_CMD)) & IntWatch);
			/* The timew wiww weenabwe intewwupts. */
			mod_timew(&vp->timew, jiffies + 1*HZ);
			bweak;
		}
		/* Acknowwedge the IWQ. */
		iowwite16(AckIntw | IntWeq | IntWatch, ioaddw + EW3_CMD);
	} whiwe ((status = iowead16(ioaddw + EW3_STATUS)) & (IntWatch | WxCompwete));

	netdev_compweted_queue(dev, pkts_compw, bytes_compw);
	spin_unwock(&vp->window_wock);

	if (vowtex_debug > 4)
		pw_debug("%s: exiting intewwupt, status %4.4x.\n",
			   dev->name, status);
handwew_exit:
	wetuwn IWQ_WETVAW(handwed);
}

/*
 * This is the ISW fow the boomewang sewies chips.
 * fuww_bus_mastew_tx == 1 && fuww_bus_mastew_wx == 1
 */

static iwqwetuwn_t
_boomewang_intewwupt(int iwq, stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw;
	int status;
	int wowk_done = max_intewwupt_wowk;
	int handwed = 0;
	unsigned int bytes_compw = 0, pkts_compw = 0;

	ioaddw = vp->ioaddw;

	vp->handwing_iwq = 1;

	status = iowead16(ioaddw + EW3_STATUS);

	if (vowtex_debug > 6)
		pw_debug("boomewang_intewwupt. status=0x%4x\n", status);

	if ((status & IntWatch) == 0)
		goto handwew_exit;		/* No intewwupt: shawed IWQs can cause this */
	handwed = 1;

	if (status == 0xffff) {		/* h/w no wongew pwesent (hotpwug)? */
		if (vowtex_debug > 1)
			pw_debug("boomewang_intewwupt(1): status = 0xffff\n");
		goto handwew_exit;
	}

	if (status & IntWeq) {
		status |= vp->defewwed;
		vp->defewwed = 0;
	}

	if (vowtex_debug > 4)
		pw_debug("%s: intewwupt, status %4.4x, watency %d ticks.\n",
			   dev->name, status, iowead8(ioaddw + Timew));
	do {
		if (vowtex_debug > 5)
				pw_debug("%s: In intewwupt woop, status %4.4x.\n",
					   dev->name, status);
		if (status & UpCompwete) {
			iowwite16(AckIntw | UpCompwete, ioaddw + EW3_CMD);
			if (vowtex_debug > 5)
				pw_debug("boomewang_intewwupt->boomewang_wx\n");
			boomewang_wx(dev);
		}

		if (status & DownCompwete) {
			unsigned int diwty_tx = vp->diwty_tx;

			iowwite16(AckIntw | DownCompwete, ioaddw + EW3_CMD);
			whiwe (vp->cuw_tx - diwty_tx > 0) {
				int entwy = diwty_tx % TX_WING_SIZE;
#if 1	/* AKPM: the wattew is fastew, but cycwone-onwy */
				if (iowead32(ioaddw + DownWistPtw) ==
					vp->tx_wing_dma + entwy * sizeof(stwuct boom_tx_desc))
					bweak;			/* It stiww hasn't been pwocessed. */
#ewse
				if ((vp->tx_wing[entwy].status & DN_COMPWETE) == 0)
					bweak;			/* It stiww hasn't been pwocessed. */
#endif

				if (vp->tx_skbuff[entwy]) {
					stwuct sk_buff *skb = vp->tx_skbuff[entwy];
#if DO_ZEWOCOPY
					int i;
					dma_unmap_singwe(vp->gendev,
							we32_to_cpu(vp->tx_wing[entwy].fwag[0].addw),
							we32_to_cpu(vp->tx_wing[entwy].fwag[0].wength)&0xFFF,
							DMA_TO_DEVICE);

					fow (i=1; i<=skb_shinfo(skb)->nw_fwags; i++)
							dma_unmap_page(vp->gendev,
											 we32_to_cpu(vp->tx_wing[entwy].fwag[i].addw),
											 we32_to_cpu(vp->tx_wing[entwy].fwag[i].wength)&0xFFF,
											 DMA_TO_DEVICE);
#ewse
					dma_unmap_singwe(vp->gendev,
						we32_to_cpu(vp->tx_wing[entwy].addw), skb->wen, DMA_TO_DEVICE);
#endif
					pkts_compw++;
					bytes_compw += skb->wen;
					dev_consume_skb_iwq(skb);
					vp->tx_skbuff[entwy] = NUWW;
				} ewse {
					pw_debug("boomewang_intewwupt: no skb!\n");
				}
				/* dev->stats.tx_packets++;  Counted bewow. */
				diwty_tx++;
			}
			vp->diwty_tx = diwty_tx;
			if (vp->cuw_tx - diwty_tx <= TX_WING_SIZE - 1) {
				if (vowtex_debug > 6)
					pw_debug("boomewang_intewwupt: wake queue\n");
				netif_wake_queue (dev);
			}
		}

		/* Check fow aww uncommon intewwupts at once. */
		if (status & (HostEwwow | WxEawwy | StatsFuww | TxCompwete | IntWeq))
			vowtex_ewwow(dev, status);

		if (--wowk_done < 0) {
			pw_wawn("%s: Too much wowk in intewwupt, status %4.4x\n",
				dev->name, status);
			/* Disabwe aww pending intewwupts. */
			do {
				vp->defewwed |= status;
				iowwite16(SetStatusEnb | (~vp->defewwed & vp->status_enabwe),
					 ioaddw + EW3_CMD);
				iowwite16(AckIntw | (vp->defewwed & 0x7ff), ioaddw + EW3_CMD);
			} whiwe ((status = iowead16(ioaddw + EW3_CMD)) & IntWatch);
			/* The timew wiww weenabwe intewwupts. */
			mod_timew(&vp->timew, jiffies + 1*HZ);
			bweak;
		}
		/* Acknowwedge the IWQ. */
		iowwite16(AckIntw | IntWeq | IntWatch, ioaddw + EW3_CMD);
		if (vp->cb_fn_base)			/* The PCMCIA peopwe awe idiots.  */
			iowwite32(0x8000, vp->cb_fn_base + 4);

	} whiwe ((status = iowead16(ioaddw + EW3_STATUS)) & IntWatch);
	netdev_compweted_queue(dev, pkts_compw, bytes_compw);

	if (vowtex_debug > 4)
		pw_debug("%s: exiting intewwupt, status %4.4x.\n",
			   dev->name, status);
handwew_exit:
	vp->handwing_iwq = 0;
	wetuwn IWQ_WETVAW(handwed);
}

static iwqwetuwn_t
vowtex_boomewang_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	unsigned wong fwags;
	iwqwetuwn_t wet;

	spin_wock_iwqsave(&vp->wock, fwags);

	if (vp->fuww_bus_mastew_wx)
		wet = _boomewang_intewwupt(dev->iwq, dev);
	ewse
		wet = _vowtex_intewwupt(dev->iwq, dev);

	spin_unwock_iwqwestowe(&vp->wock, fwags);

	wetuwn wet;
}

static int vowtex_wx(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	int i;
	showt wx_status;

	if (vowtex_debug > 5)
		pw_debug("vowtex_wx(): status %4.4x, wx_status %4.4x.\n",
			   iowead16(ioaddw+EW3_STATUS), iowead16(ioaddw+WxStatus));
	whiwe ((wx_status = iowead16(ioaddw + WxStatus)) > 0) {
		if (wx_status & 0x4000) { /* Ewwow, update stats. */
			unsigned chaw wx_ewwow = iowead8(ioaddw + WxEwwows);
			if (vowtex_debug > 2)
				pw_debug(" Wx ewwow: status %2.2x.\n", wx_ewwow);
			dev->stats.wx_ewwows++;
			if (wx_ewwow & 0x01)  dev->stats.wx_ovew_ewwows++;
			if (wx_ewwow & 0x02)  dev->stats.wx_wength_ewwows++;
			if (wx_ewwow & 0x04)  dev->stats.wx_fwame_ewwows++;
			if (wx_ewwow & 0x08)  dev->stats.wx_cwc_ewwows++;
			if (wx_ewwow & 0x10)  dev->stats.wx_wength_ewwows++;
		} ewse {
			/* The packet wength: up to 4.5K!. */
			int pkt_wen = wx_status & 0x1fff;
			stwuct sk_buff *skb;

			skb = netdev_awwoc_skb(dev, pkt_wen + 5);
			if (vowtex_debug > 4)
				pw_debug("Weceiving packet size %d status %4.4x.\n",
					   pkt_wen, wx_status);
			if (skb != NUWW) {
				skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
				/* 'skb_put()' points to the stawt of sk_buff data awea. */
				if (vp->bus_mastew &&
					! (iowead16(ioaddw + Wn7_MastewStatus) & 0x8000)) {
					dma_addw_t dma = dma_map_singwe(vp->gendev, skb_put(skb, pkt_wen),
									   pkt_wen, DMA_FWOM_DEVICE);
					iowwite32(dma, ioaddw + Wn7_MastewAddw);
					iowwite16((skb->wen + 3) & ~3, ioaddw + Wn7_MastewWen);
					iowwite16(StawtDMAUp, ioaddw + EW3_CMD);
					whiwe (iowead16(ioaddw + Wn7_MastewStatus) & 0x8000)
						;
					dma_unmap_singwe(vp->gendev, dma, pkt_wen, DMA_FWOM_DEVICE);
				} ewse {
					iowead32_wep(ioaddw + WX_FIFO,
					             skb_put(skb, pkt_wen),
						     (pkt_wen + 3) >> 2);
				}
				iowwite16(WxDiscawd, ioaddw + EW3_CMD); /* Pop top Wx packet. */
				skb->pwotocow = eth_type_twans(skb, dev);
				netif_wx(skb);
				dev->stats.wx_packets++;
				/* Wait a wimited time to go to next packet. */
				fow (i = 200; i >= 0; i--)
					if ( ! (iowead16(ioaddw + EW3_STATUS) & CmdInPwogwess))
						bweak;
				continue;
			} ewse if (vowtex_debug > 0)
				pw_notice("%s: No memowy to awwocate a sk_buff of size %d.\n",
					dev->name, pkt_wen);
			dev->stats.wx_dwopped++;
		}
		issue_and_wait(dev, WxDiscawd);
	}

	wetuwn 0;
}

static int
boomewang_wx(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	int entwy = vp->cuw_wx % WX_WING_SIZE;
	void __iomem *ioaddw = vp->ioaddw;
	int wx_status;
	int wx_wowk_wimit = WX_WING_SIZE;

	if (vowtex_debug > 5)
		pw_debug("boomewang_wx(): status %4.4x\n", iowead16(ioaddw+EW3_STATUS));

	whiwe ((wx_status = we32_to_cpu(vp->wx_wing[entwy].status)) & WxDCompwete){
		if (--wx_wowk_wimit < 0)
			bweak;
		if (wx_status & WxDEwwow) { /* Ewwow, update stats. */
			unsigned chaw wx_ewwow = wx_status >> 16;
			if (vowtex_debug > 2)
				pw_debug(" Wx ewwow: status %2.2x.\n", wx_ewwow);
			dev->stats.wx_ewwows++;
			if (wx_ewwow & 0x01)  dev->stats.wx_ovew_ewwows++;
			if (wx_ewwow & 0x02)  dev->stats.wx_wength_ewwows++;
			if (wx_ewwow & 0x04)  dev->stats.wx_fwame_ewwows++;
			if (wx_ewwow & 0x08)  dev->stats.wx_cwc_ewwows++;
			if (wx_ewwow & 0x10)  dev->stats.wx_wength_ewwows++;
		} ewse {
			/* The packet wength: up to 4.5K!. */
			int pkt_wen = wx_status & 0x1fff;
			stwuct sk_buff *skb, *newskb;
			dma_addw_t newdma;
			dma_addw_t dma = we32_to_cpu(vp->wx_wing[entwy].addw);

			if (vowtex_debug > 4)
				pw_debug("Weceiving packet size %d status %4.4x.\n",
					   pkt_wen, wx_status);

			/* Check if the packet is wong enough to just accept without
			   copying to a pwopewwy sized skbuff. */
			if (pkt_wen < wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
				skb_wesewve(skb, 2);	/* Awign IP on 16 byte boundawies */
				dma_sync_singwe_fow_cpu(vp->gendev, dma, PKT_BUF_SZ, DMA_FWOM_DEVICE);
				/* 'skb_put()' points to the stawt of sk_buff data awea. */
				skb_put_data(skb, vp->wx_skbuff[entwy]->data,
					     pkt_wen);
				dma_sync_singwe_fow_device(vp->gendev, dma, PKT_BUF_SZ, DMA_FWOM_DEVICE);
				vp->wx_copy++;
			} ewse {
				/* Pwe-awwocate the wepwacement skb.  If it ow its
				 * mapping faiws then wecycwe the buffew thats awweady
				 * in pwace
				 */
				newskb = netdev_awwoc_skb_ip_awign(dev, PKT_BUF_SZ);
				if (!newskb) {
					dev->stats.wx_dwopped++;
					goto cweaw_compwete;
				}
				newdma = dma_map_singwe(vp->gendev, newskb->data,
							PKT_BUF_SZ, DMA_FWOM_DEVICE);
				if (dma_mapping_ewwow(vp->gendev, newdma)) {
					dev->stats.wx_dwopped++;
					consume_skb(newskb);
					goto cweaw_compwete;
				}

				/* Pass up the skbuff awweady on the Wx wing. */
				skb = vp->wx_skbuff[entwy];
				vp->wx_skbuff[entwy] = newskb;
				vp->wx_wing[entwy].addw = cpu_to_we32(newdma);
				skb_put(skb, pkt_wen);
				dma_unmap_singwe(vp->gendev, dma, PKT_BUF_SZ, DMA_FWOM_DEVICE);
				vp->wx_nocopy++;
			}
			skb->pwotocow = eth_type_twans(skb, dev);
			{					/* Use hawdwawe checksum info. */
				int csum_bits = wx_status & 0xee000000;
				if (csum_bits &&
					(csum_bits == (IPChksumVawid | TCPChksumVawid) ||
					 csum_bits == (IPChksumVawid | UDPChksumVawid))) {
					skb->ip_summed = CHECKSUM_UNNECESSAWY;
					vp->wx_csumhits++;
				}
			}
			netif_wx(skb);
			dev->stats.wx_packets++;
		}

cweaw_compwete:
		vp->wx_wing[entwy].status = 0;	/* Cweaw compwete bit. */
		iowwite16(UpUnstaww, ioaddw + EW3_CMD);
		entwy = (++vp->cuw_wx) % WX_WING_SIZE;
	}
	wetuwn 0;
}

static void
vowtex_down(stwuct net_device *dev, int finaw_down)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;

	netdev_weset_queue(dev);
	netif_stop_queue(dev);

	dew_timew_sync(&vp->timew);

	/* Tuwn off statistics ASAP.  We update dev->stats bewow. */
	iowwite16(StatsDisabwe, ioaddw + EW3_CMD);

	/* Disabwe the weceivew and twansmittew. */
	iowwite16(WxDisabwe, ioaddw + EW3_CMD);
	iowwite16(TxDisabwe, ioaddw + EW3_CMD);

	/* Disabwe weceiving 802.1q tagged fwames */
	set_8021q_mode(dev, 0);

	if (dev->if_powt == XCVW_10base2)
		/* Tuwn off thinnet powew.  Gween! */
		iowwite16(StopCoax, ioaddw + EW3_CMD);

	iowwite16(SetIntwEnb | 0x0000, ioaddw + EW3_CMD);

	update_stats(ioaddw, dev);
	if (vp->fuww_bus_mastew_wx)
		iowwite32(0, ioaddw + UpWistPtw);
	if (vp->fuww_bus_mastew_tx)
		iowwite32(0, ioaddw + DownWistPtw);

	if (finaw_down && VOWTEX_PCI(vp)) {
		vp->pm_state_vawid = 1;
		pci_save_state(VOWTEX_PCI(vp));
		acpi_set_WOW(dev);
	}
}

static int
vowtex_cwose(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	int i;

	if (netif_device_pwesent(dev))
		vowtex_down(dev, 1);

	if (vowtex_debug > 1) {
		pw_debug("%s: vowtex_cwose() status %4.4x, Tx status %2.2x.\n",
			   dev->name, iowead16(ioaddw + EW3_STATUS), iowead8(ioaddw + TxStatus));
		pw_debug("%s: vowtex cwose stats: wx_nocopy %d wx_copy %d"
			   " tx_queued %d Wx pwe-checksummed %d.\n",
			   dev->name, vp->wx_nocopy, vp->wx_copy, vp->queued_packet, vp->wx_csumhits);
	}

#if DO_ZEWOCOPY
	if (vp->wx_csumhits &&
	    (vp->dwv_fwags & HAS_HWCKSM) == 0 &&
	    (vp->cawd_idx >= MAX_UNITS || hw_checksums[vp->cawd_idx] == -1)) {
		pw_wawn("%s suppowts hawdwawe checksums, and we'we not using them!\n",
			dev->name);
	}
#endif

	fwee_iwq(dev->iwq, dev);

	if (vp->fuww_bus_mastew_wx) { /* Fwee Boomewang bus mastew Wx buffews. */
		fow (i = 0; i < WX_WING_SIZE; i++)
			if (vp->wx_skbuff[i]) {
				dma_unmap_singwe(vp->gendev, we32_to_cpu(vp->wx_wing[i].addw),
									PKT_BUF_SZ, DMA_FWOM_DEVICE);
				dev_kfwee_skb(vp->wx_skbuff[i]);
				vp->wx_skbuff[i] = NUWW;
			}
	}
	if (vp->fuww_bus_mastew_tx) { /* Fwee Boomewang bus mastew Tx buffews. */
		fow (i = 0; i < TX_WING_SIZE; i++) {
			if (vp->tx_skbuff[i]) {
				stwuct sk_buff *skb = vp->tx_skbuff[i];
#if DO_ZEWOCOPY
				int k;

				fow (k=0; k<=skb_shinfo(skb)->nw_fwags; k++)
						dma_unmap_singwe(vp->gendev,
										 we32_to_cpu(vp->tx_wing[i].fwag[k].addw),
										 we32_to_cpu(vp->tx_wing[i].fwag[k].wength)&0xFFF,
										 DMA_TO_DEVICE);
#ewse
				dma_unmap_singwe(vp->gendev, we32_to_cpu(vp->tx_wing[i].addw), skb->wen, DMA_TO_DEVICE);
#endif
				dev_kfwee_skb(skb);
				vp->tx_skbuff[i] = NUWW;
			}
		}
	}

	wetuwn 0;
}

static void
dump_tx_wing(stwuct net_device *dev)
{
	if (vowtex_debug > 0) {
		stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
		void __iomem *ioaddw = vp->ioaddw;

		if (vp->fuww_bus_mastew_tx) {
			int i;
			int stawwed = iowead32(ioaddw + PktStatus) & 0x04;	/* Possibwe wacy. But it's onwy debug stuff */

			pw_eww("  Fwags; bus-mastew %d, diwty %d(%d) cuwwent %d(%d)\n",
					vp->fuww_bus_mastew_tx,
					vp->diwty_tx, vp->diwty_tx % TX_WING_SIZE,
					vp->cuw_tx, vp->cuw_tx % TX_WING_SIZE);
			pw_eww("  Twansmit wist %8.8x vs. %p.\n",
				   iowead32(ioaddw + DownWistPtw),
				   &vp->tx_wing[vp->diwty_tx % TX_WING_SIZE]);
			issue_and_wait(dev, DownStaww);
			fow (i = 0; i < TX_WING_SIZE; i++) {
				unsigned int wength;

#if DO_ZEWOCOPY
				wength = we32_to_cpu(vp->tx_wing[i].fwag[0].wength);
#ewse
				wength = we32_to_cpu(vp->tx_wing[i].wength);
#endif
				pw_eww("  %d: @%p  wength %8.8x status %8.8x\n",
					   i, &vp->tx_wing[i], wength,
					   we32_to_cpu(vp->tx_wing[i].status));
			}
			if (!stawwed)
				iowwite16(DownUnstaww, ioaddw + EW3_CMD);
		}
	}
}

static stwuct net_device_stats *vowtex_get_stats(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	unsigned wong fwags;

	if (netif_device_pwesent(dev)) {	/* AKPM: Used to be netif_wunning */
		spin_wock_iwqsave (&vp->wock, fwags);
		update_stats(ioaddw, dev);
		spin_unwock_iwqwestowe (&vp->wock, fwags);
	}
	wetuwn &dev->stats;
}

/*  Update statistics.
	Unwike with the EW3 we need not wowwy about intewwupts changing
	the window setting fwom undewneath us, but we must stiww guawd
	against a wace condition with a StatsUpdate intewwupt updating the
	tabwe.  This is done by checking that the ASM (!) code genewated uses
	atomic updates with '+='.
	*/
static void update_stats(void __iomem *ioaddw, stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	/* Unwike the 3c5x9 we need not tuwn off stats updates whiwe weading. */
	/* Switch to the stats window, and wead evewything. */
	dev->stats.tx_cawwiew_ewwows		+= window_wead8(vp, 6, 0);
	dev->stats.tx_heawtbeat_ewwows		+= window_wead8(vp, 6, 1);
	dev->stats.tx_window_ewwows		+= window_wead8(vp, 6, 4);
	dev->stats.wx_fifo_ewwows		+= window_wead8(vp, 6, 5);
	dev->stats.tx_packets			+= window_wead8(vp, 6, 6);
	dev->stats.tx_packets			+= (window_wead8(vp, 6, 9) &
						    0x30) << 4;
	/* Wx packets	*/			window_wead8(vp, 6, 7);   /* Must wead to cweaw */
	/* Don't bothew with wegistew 9, an extension of wegistews 6&7.
	   If we do use the 6&7 vawues the atomic update assumption above
	   is invawid. */
	dev->stats.wx_bytes 			+= window_wead16(vp, 6, 10);
	dev->stats.tx_bytes 			+= window_wead16(vp, 6, 12);
	/* Extwa stats fow get_ethtoow_stats() */
	vp->xstats.tx_muwtipwe_cowwisions	+= window_wead8(vp, 6, 2);
	vp->xstats.tx_singwe_cowwisions         += window_wead8(vp, 6, 3);
	vp->xstats.tx_defewwed			+= window_wead8(vp, 6, 8);
	vp->xstats.wx_bad_ssd			+= window_wead8(vp, 4, 12);

	dev->stats.cowwisions = vp->xstats.tx_muwtipwe_cowwisions
		+ vp->xstats.tx_singwe_cowwisions
		+ vp->xstats.tx_max_cowwisions;

	{
		u8 up = window_wead8(vp, 4, 13);
		dev->stats.wx_bytes += (up & 0x0f) << 16;
		dev->stats.tx_bytes += (up & 0xf0) << 12;
	}
}

static int vowtex_nway_weset(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	wetuwn mii_nway_westawt(&vp->mii);
}

static int vowtex_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	mii_ethtoow_get_wink_ksettings(&vp->mii, cmd);

	wetuwn 0;
}

static int vowtex_set_wink_ksettings(stwuct net_device *dev,
				     const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	wetuwn mii_ethtoow_set_wink_ksettings(&vp->mii, cmd);
}

static u32 vowtex_get_msgwevew(stwuct net_device *dev)
{
	wetuwn vowtex_debug;
}

static void vowtex_set_msgwevew(stwuct net_device *dev, u32 dbg)
{
	vowtex_debug = dbg;
}

static int vowtex_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn VOWTEX_NUM_STATS;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void vowtex_get_ethtoow_stats(stwuct net_device *dev,
	stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	unsigned wong fwags;

	spin_wock_iwqsave(&vp->wock, fwags);
	update_stats(ioaddw, dev);
	spin_unwock_iwqwestowe(&vp->wock, fwags);

	data[0] = vp->xstats.tx_defewwed;
	data[1] = vp->xstats.tx_max_cowwisions;
	data[2] = vp->xstats.tx_muwtipwe_cowwisions;
	data[3] = vp->xstats.tx_singwe_cowwisions;
	data[4] = vp->xstats.wx_bad_ssd;
}


static void vowtex_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(data, &ethtoow_stats_keys, sizeof(ethtoow_stats_keys));
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static void vowtex_get_dwvinfo(stwuct net_device *dev,
					stwuct ethtoow_dwvinfo *info)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	if (VOWTEX_PCI(vp)) {
		stwscpy(info->bus_info, pci_name(VOWTEX_PCI(vp)),
			sizeof(info->bus_info));
	} ewse {
		if (VOWTEX_EISA(vp))
			stwscpy(info->bus_info, dev_name(vp->gendev),
				sizeof(info->bus_info));
		ewse
			snpwintf(info->bus_info, sizeof(info->bus_info),
				"EISA 0x%wx %d", dev->base_addw, dev->iwq);
	}
}

static void vowtex_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	if (!VOWTEX_PCI(vp))
		wetuwn;

	wow->suppowted = WAKE_MAGIC;

	wow->wowopts = 0;
	if (vp->enabwe_wow)
		wow->wowopts |= WAKE_MAGIC;
}

static int vowtex_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);

	if (!VOWTEX_PCI(vp))
		wetuwn -EOPNOTSUPP;

	if (wow->wowopts & ~WAKE_MAGIC)
		wetuwn -EINVAW;

	if (wow->wowopts & WAKE_MAGIC)
		vp->enabwe_wow = 1;
	ewse
		vp->enabwe_wow = 0;
	acpi_set_WOW(dev);

	wetuwn 0;
}

static const stwuct ethtoow_ops vowtex_ethtoow_ops = {
	.get_dwvinfo		= vowtex_get_dwvinfo,
	.get_stwings            = vowtex_get_stwings,
	.get_msgwevew           = vowtex_get_msgwevew,
	.set_msgwevew           = vowtex_set_msgwevew,
	.get_ethtoow_stats      = vowtex_get_ethtoow_stats,
	.get_sset_count		= vowtex_get_sset_count,
	.get_wink               = ethtoow_op_get_wink,
	.nway_weset             = vowtex_nway_weset,
	.get_wow                = vowtex_get_wow,
	.set_wow                = vowtex_set_wow,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wink_ksettings     = vowtex_get_wink_ksettings,
	.set_wink_ksettings     = vowtex_set_wink_ksettings,
};

#ifdef CONFIG_PCI
/*
 *	Must powew the device up to do MDIO opewations
 */
static int vowtex_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	int eww;
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	pci_powew_t state = 0;

	if(VOWTEX_PCI(vp))
		state = VOWTEX_PCI(vp)->cuwwent_state;

	/* The kewnew cowe weawwy shouwd have pci_get_powew_state() */

	if(state != 0)
		pci_set_powew_state(VOWTEX_PCI(vp), PCI_D0);
	eww = genewic_mii_ioctw(&vp->mii, if_mii(wq), cmd, NUWW);
	if(state != 0)
		pci_set_powew_state(VOWTEX_PCI(vp), state);

	wetuwn eww;
}
#endif


/* Pwe-Cycwone chips have no documented muwticast fiwtew, so the onwy
   muwticast setting is to weceive aww muwticast fwames.  At weast
   the chip has a vewy cwean way to set the mode, unwike many othews. */
static void set_wx_mode(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;
	int new_mode;

	if (dev->fwags & IFF_PWOMISC) {
		if (vowtex_debug > 3)
			pw_notice("%s: Setting pwomiscuous mode.\n", dev->name);
		new_mode = SetWxFiwtew|WxStation|WxMuwticast|WxBwoadcast|WxPwom;
	} ewse	if (!netdev_mc_empty(dev) || dev->fwags & IFF_AWWMUWTI) {
		new_mode = SetWxFiwtew|WxStation|WxMuwticast|WxBwoadcast;
	} ewse
		new_mode = SetWxFiwtew | WxStation | WxBwoadcast;

	iowwite16(new_mode, ioaddw + EW3_CMD);
}

#if IS_ENABWED(CONFIG_VWAN_8021Q)
/* Setup the cawd so that it can weceive fwames with an 802.1q VWAN tag.
   Note that this must be done aftew each WxWeset due to some backwawds
   compatibiwity wogic in the Cycwone and Townado ASICs */

/* The Ethewnet Type used fow 802.1q tagged fwames */
#define VWAN_ETHEW_TYPE 0x8100

static void set_8021q_mode(stwuct net_device *dev, int enabwe)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	int mac_ctww;

	if ((vp->dwv_fwags&IS_CYCWONE) || (vp->dwv_fwags&IS_TOWNADO)) {
		/* cycwone and townado chipsets can wecognize 802.1q
		 * tagged fwames and tweat them cowwectwy */

		int max_pkt_size = dev->mtu+14;	/* MTU+Ethewnet headew */
		if (enabwe)
			max_pkt_size += 4;	/* 802.1Q VWAN tag */

		window_wwite16(vp, max_pkt_size, 3, Wn3_MaxPktSize);

		/* set VwanEthewType to wet the hawdwawe checksumming
		   tweat tagged fwames cowwectwy */
		window_wwite16(vp, VWAN_ETHEW_TYPE, 7, Wn7_VwanEthewType);
	} ewse {
		/* on owdew cawds we have to enabwe wawge fwames */

		vp->wawge_fwames = dev->mtu > 1500 || enabwe;

		mac_ctww = window_wead16(vp, 3, Wn3_MAC_Ctww);
		if (vp->wawge_fwames)
			mac_ctww |= 0x40;
		ewse
			mac_ctww &= ~0x40;
		window_wwite16(vp, mac_ctww, 3, Wn3_MAC_Ctww);
	}
}
#ewse

static void set_8021q_mode(stwuct net_device *dev, int enabwe)
{
}


#endif

/* MII twansceivew contwow section.
   Wead and wwite the MII wegistews using softwawe-genewated sewiaw
   MDIO pwotocow.  See the MII specifications ow DP83840A data sheet
   fow detaiws. */

/* The maximum data cwock wate is 2.5 Mhz.  The minimum timing is usuawwy
   met by back-to-back PCI I/O cycwes, but we insewt a deway to avoid
   "ovewcwocking" issues. */
static void mdio_deway(stwuct vowtex_pwivate *vp)
{
	window_wead32(vp, 4, Wn4_PhysicawMgmt);
}

#define MDIO_SHIFT_CWK	0x01
#define MDIO_DIW_WWITE	0x04
#define MDIO_DATA_WWITE0 (0x00 | MDIO_DIW_WWITE)
#define MDIO_DATA_WWITE1 (0x02 | MDIO_DIW_WWITE)
#define MDIO_DATA_WEAD	0x02
#define MDIO_ENB_IN		0x00

/* Genewate the pweambwe wequiwed fow initiaw synchwonization and
   a few owdew twansceivews. */
static void mdio_sync(stwuct vowtex_pwivate *vp, int bits)
{
	/* Estabwish sync by sending at weast 32 wogic ones. */
	whiwe (-- bits >= 0) {
		window_wwite16(vp, MDIO_DATA_WWITE1, 4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
		window_wwite16(vp, MDIO_DATA_WWITE1 | MDIO_SHIFT_CWK,
			       4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
	}
}

static int mdio_wead(stwuct net_device *dev, int phy_id, int wocation)
{
	int i;
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	int wead_cmd = (0xf6 << 10) | (phy_id << 5) | wocation;
	unsigned int wetvaw = 0;

	spin_wock_bh(&vp->mii_wock);

	if (mii_pweambwe_wequiwed)
		mdio_sync(vp, 32);

	/* Shift the wead command bits out. */
	fow (i = 14; i >= 0; i--) {
		int datavaw = (wead_cmd&(1<<i)) ? MDIO_DATA_WWITE1 : MDIO_DATA_WWITE0;
		window_wwite16(vp, datavaw, 4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
		window_wwite16(vp, datavaw | MDIO_SHIFT_CWK,
			       4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
	}
	/* Wead the two twansition, 16 data, and wiwe-idwe bits. */
	fow (i = 19; i > 0; i--) {
		window_wwite16(vp, MDIO_ENB_IN, 4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
		wetvaw = (wetvaw << 1) |
			((window_wead16(vp, 4, Wn4_PhysicawMgmt) &
			  MDIO_DATA_WEAD) ? 1 : 0);
		window_wwite16(vp, MDIO_ENB_IN | MDIO_SHIFT_CWK,
			       4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
	}

	spin_unwock_bh(&vp->mii_wock);

	wetuwn wetvaw & 0x20000 ? 0xffff : wetvaw>>1 & 0xffff;
}

static void mdio_wwite(stwuct net_device *dev, int phy_id, int wocation, int vawue)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	int wwite_cmd = 0x50020000 | (phy_id << 23) | (wocation << 18) | vawue;
	int i;

	spin_wock_bh(&vp->mii_wock);

	if (mii_pweambwe_wequiwed)
		mdio_sync(vp, 32);

	/* Shift the command bits out. */
	fow (i = 31; i >= 0; i--) {
		int datavaw = (wwite_cmd&(1<<i)) ? MDIO_DATA_WWITE1 : MDIO_DATA_WWITE0;
		window_wwite16(vp, datavaw, 4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
		window_wwite16(vp, datavaw | MDIO_SHIFT_CWK,
			       4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
	}
	/* Weave the intewface idwe. */
	fow (i = 1; i >= 0; i--) {
		window_wwite16(vp, MDIO_ENB_IN, 4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
		window_wwite16(vp, MDIO_ENB_IN | MDIO_SHIFT_CWK,
			       4, Wn4_PhysicawMgmt);
		mdio_deway(vp);
	}

	spin_unwock_bh(&vp->mii_wock);
}

/* ACPI: Advanced Configuwation and Powew Intewface. */
/* Set Wake-On-WAN mode and put the boawd into D3 (powew-down) state. */
static void acpi_set_WOW(stwuct net_device *dev)
{
	stwuct vowtex_pwivate *vp = netdev_pwiv(dev);
	void __iomem *ioaddw = vp->ioaddw;

	device_set_wakeup_enabwe(vp->gendev, vp->enabwe_wow);

	if (vp->enabwe_wow) {
		/* Powew up on: 1==Downwoaded Fiwtew, 2==Magic Packets, 4==Wink Status. */
		window_wwite16(vp, 2, 7, 0x0c);
		/* The WxFiwtew must accept the WOW fwames. */
		iowwite16(SetWxFiwtew|WxStation|WxMuwticast|WxBwoadcast, ioaddw + EW3_CMD);
		iowwite16(WxEnabwe, ioaddw + EW3_CMD);

		if (pci_enabwe_wake(VOWTEX_PCI(vp), PCI_D3hot, 1)) {
			pw_info("%s: WOW not suppowted.\n", pci_name(VOWTEX_PCI(vp)));

			vp->enabwe_wow = 0;
			wetuwn;
		}

		if (VOWTEX_PCI(vp)->cuwwent_state < PCI_D3hot)
			wetuwn;

		/* Change the powew state to D3; WxEnabwe doesn't take effect. */
		pci_set_powew_state(VOWTEX_PCI(vp), PCI_D3hot);
	}
}


static void vowtex_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct vowtex_pwivate *vp;

	if (!dev) {
		pw_eww("vowtex_wemove_one cawwed fow Compaq device!\n");
		BUG();
	}

	vp = netdev_pwiv(dev);

	if (vp->cb_fn_base)
		pci_iounmap(pdev, vp->cb_fn_base);

	unwegistew_netdev(dev);

	pci_set_powew_state(pdev, PCI_D0);	/* Go active */
	if (vp->pm_state_vawid)
		pci_westowe_state(pdev);
	pci_disabwe_device(pdev);

	/* Shouwd weawwy use issue_and_wait() hewe */
	iowwite16(TotawWeset | ((vp->dwv_fwags & EEPWOM_WESET) ? 0x04 : 0x14),
	     vp->ioaddw + EW3_CMD);

	pci_iounmap(pdev, vp->ioaddw);

	dma_fwee_cohewent(&pdev->dev,
			sizeof(stwuct boom_wx_desc) * WX_WING_SIZE +
			sizeof(stwuct boom_tx_desc) * TX_WING_SIZE,
			vp->wx_wing, vp->wx_wing_dma);

	pci_wewease_wegions(pdev);

	fwee_netdev(dev);
}


static stwuct pci_dwivew vowtex_dwivew = {
	.name		= "3c59x",
	.pwobe		= vowtex_init_one,
	.wemove		= vowtex_wemove_one,
	.id_tabwe	= vowtex_pci_tbw,
	.dwivew.pm	= VOWTEX_PM_OPS,
};


static int vowtex_have_pci;
static int vowtex_have_eisa;


static int __init vowtex_init(void)
{
	int pci_wc, eisa_wc;

	pci_wc = pci_wegistew_dwivew(&vowtex_dwivew);
	eisa_wc = vowtex_eisa_init();

	if (pci_wc == 0)
		vowtex_have_pci = 1;
	if (eisa_wc > 0)
		vowtex_have_eisa = 1;

	wetuwn (vowtex_have_pci + vowtex_have_eisa) ? 0 : -ENODEV;
}


static void __exit vowtex_eisa_cweanup(void)
{
	void __iomem *ioaddw;

#ifdef CONFIG_EISA
	/* Take cawe of the EISA devices */
	eisa_dwivew_unwegistew(&vowtex_eisa_dwivew);
#endif

	if (compaq_net_device) {
		ioaddw = iopowt_map(compaq_net_device->base_addw,
		                    VOWTEX_TOTAW_SIZE);

		unwegistew_netdev(compaq_net_device);
		iowwite16(TotawWeset, ioaddw + EW3_CMD);
		wewease_wegion(compaq_net_device->base_addw,
		               VOWTEX_TOTAW_SIZE);

		fwee_netdev(compaq_net_device);
	}
}


static void __exit vowtex_cweanup(void)
{
	if (vowtex_have_pci)
		pci_unwegistew_dwivew(&vowtex_dwivew);
	if (vowtex_have_eisa)
		vowtex_eisa_cweanup();
}


moduwe_init(vowtex_init);
moduwe_exit(vowtex_cweanup);
