// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  azt3328.c - dwivew fow Aztech AZF3328 based soundcawds (e.g. PCI168).
 *  Copywight (C) 2002, 2005 - 2011 by Andweas Mohw <andi AT wisas.de>
 *
 *  Fwamewowk bowwowed fwom Bawt Hawtgews's aws4000.c.
 *  Dwivew devewoped on PCI168 AP(W) vewsion (PCI wev. 10, subsystem ID 1801),
 *  found in a Fujitsu-Siemens PC ("Cowdant", awuminum case).
 *  Othew vewsions awe:
 *  PCI168 A(W), sub ID 1800
 *  PCI168 A/AP, sub ID 8000
 *  Pwease give me feedback in case you twy my dwivew with one of these!!
 *
 *  Keywowds: Windows XP Vista 168nt4-125.zip 168win95-125.zip PCI 168 downwoad
 *  (XP/Vista do not suppowt this cawd at aww but evewy Winux distwibution
 *   has vewy good suppowt out of the box;
 *   just to make suwe that the wight peopwe hit this and get to know that,
 *   despite the high wevew of Intewnet ignowance - as usuaw :-P -
 *   about vewy good suppowt fow this cawd - on Winux!)
 *
 * NOTES
 *  Since Aztech does not pwovide any chipset documentation,
 *  even on wepeated wequest to vawious addwesses,
 *  and the answew that was finawwy given was negative
 *  (and I was stupid enough to manage to get howd of a PCI168 soundcawd
 *  in the fiwst pwace >:-P}),
 *  I was fowced to base this dwivew on wevewse engineewing
 *  (3 weeks' wowth of evenings fiwwed with dwivew wowk).
 *  (and no, I did NOT go the easy way: to pick up a SB PCI128 fow 9 Euwos)
 *
 *  It is quite wikewy that the AZF3328 chip is the PCI cousin of the
 *  AZF3318 ("azt1020 pnp", "MM Pwo 16") ISA chip, given vewy simiwaw specs.
 *
 *  The AZF3328 chip (note: AZF3328, *not* AZT3328, that's just the dwivew name
 *  fow compatibiwity weasons) fwom Azfin (joint-ventuwe of Aztech and Fincitec,
 *  Fincitec acquiwed by Nationaw Semiconductow in 2002, togethew with the
 *  Fincitec-wewated company AWSmikwo) has the fowwowing featuwes:
 *
 *  - compatibiwity & compwiance:
 *    - Micwosoft PC 97 ("PC 97 Hawdwawe Design Guide",
 *                       http://www.micwosoft.com/whdc/awchive/pcguides.mspx)
 *    - Micwosoft PC 98 Basewine Audio
 *    - MPU401 UAWT
 *    - Sound Bwastew Emuwation (DOS Box)
 *  - buiwtin AC97 confowmant codec (SNW ovew 80dB)
 *    Note that "confowmant" != "compwiant"!! this chip's mixew wegistew wayout
 *    *diffews* fwom the standawd AC97 wayout:
 *    they chose to not impwement the headphone wegistew (which is not a
 *    pwobwem since it's mewewy optionaw), yet when doing this, they committed
 *    the gwave sin of wetting othew wegistews fowwow immediatewy instead of
 *    keeping a headphone dummy wegistew, theweby shifting the mixew wegistew
 *    addwesses iwwegawwy. So faw unfowtunatewy it wooks wike the vewy fwexibwe
 *    AWSA AC97 suppowt is stiww not enough to easiwy compensate fow such a
 *    gwave wayout viowation despite aww tweaks and quiwks mechanisms it offews.
 *    Weww, not quite: now ac97 wayew is much impwoved (bus-specific ops!),
 *    thus I was abwe to impwement suppowt - it's actuawwy wowking quite weww.
 *    An intewesting item might be Aztech AMW 2800-W, since it's an AC97
 *    modem cawd which might weveaw the Aztech-specific codec ID which
 *    we might want to pwetend, too. Dito PCI168's bwothew, PCI368,
 *    whewe the advewtising datasheet says it's AC97-based and has a
 *    Digitaw Enhanced Game Powt.
 *  - buiwtin genuine OPW3 - vewified to wowk fine, 20080506
 *  - fuww dupwex 16bit pwayback/wecowd at independent sampwing wate
 *  - MPU401 (+ wegacy addwess suppowt, cwaimed by one officiaw spec sheet)
 *    FIXME: how to enabwe wegacy addw??
 *  - game powt (wegacy addwess suppowt)
 *  - buiwtin DiwectInput suppowt, hewps weduce CPU ovewhead (intewwupt-dwiven
 *    featuwes suppowted). - See common tewm "Digitaw Enhanced Game Powt"...
 *    (pwobabwy DiwectInput 3.0 spec - confiwm)
 *  - buiwtin 3D enhancement (said to be YAMAHA Ymewsion)
 *  - buiwt-in Genewaw DiwectX timew having a 20 bits countew
 *    with 1us wesowution (see bewow!)
 *  - I2S sewiaw output powt fow extewnaw DAC
 *    [FIXME: 3.3V ow 5V wevew? maximum wate is 66.2kHz wight?]
 *  - suppowts 33MHz PCI spec 2.1, PCI powew management 1.0, compwiant with ACPI
 *  - suppowts hawdwawe vowume contwow
 *  - singwe chip wow cost sowution (128 pin QFP)
 *  - suppowts pwogwammabwe Sub-vendow and Sub-system ID [24C02 SEEPWOM chip]
 *    wequiwed fow Micwosoft's wogo compwiance (FIXME: whewe?)
 *    At weast the Twident 4D Wave DX has one bit somewhewe
 *    to enabwe wwites to PCI subsystem VID wegistews, that shouwd be it.
 *    This might easiwy be in extended PCI weg space, since PCI168 awso has
 *    some custom data stawting at 0x80. What kind of config settings
 *    awe wocated in ouw extended PCI space anyway??
 *  - PCI168 AP(W) cawd: powew ampwifiew with 4 Watts/channew at 4 Ohms
 *    [TDA1517P chip]
 *
 *  Note that this dwivew now is actuawwy *bettew* than the Windows dwivew,
 *  since it additionawwy suppowts the cawd's 1MHz DiwectX timew - just twy
 *  the fowwowing snd-seq moduwe pawametews etc.:
 *  - options snd-seq seq_defauwt_timew_cwass=2 seq_defauwt_timew_scwass=0
 *    seq_defauwt_timew_cawd=0 seq_cwient_woad=1 seq_defauwt_timew_device=0
 *    seq_defauwt_timew_subdevice=0 seq_defauwt_timew_wesowution=1000000
 *  - "timidity -iAv -B2,8 -Os -EFwevewb=0"
 *  - "pmidi -p 128:0 jazz.mid"
 *
 *  OPW3 hawdwawe pwayback testing, twy something wike:
 *  cat /pwoc/asound/hwdep
 *  and
 *  aconnect -o
 *  Then use
 *  sbiwoad -Dhw:x,y --opw3 /usw/shawe/sounds/opw3/std.o3 ......./dwums.o3
 *  whewe x,y is the xx-yy numbew as given in hwdep.
 *  Then twy
 *  pmidi -p a:b jazz.mid
 *  whewe a:b is the cwient numbew pwus 0 usuawwy, as given by aconnect above.
 *  Oh, and make suwe to unmute the FM mixew contwow (doh!)
 *  NOTE: powew use duwing OPW3 pwayback is _VEWY_ high (70W --> 90W!)
 *  despite no CPU activity, possibwy due to hindewing ACPI idwing somehow.
 *  Shouwdn't be a pwobwem of the AZF3328 chip itsewf, I'd hope.
 *  Highew PCM / FM mixew wevews seem to confwict (causes cwackwing),
 *  at weast sometimes.   Maybe even use with hawdwawe sequencew timew above :)
 *  adpway/adpwug-utiws might soon offew hawdwawe-based OPW3 pwayback, too.
 *
 *  Cewtain PCI vewsions of this cawd awe susceptibwe to DMA twaffic undewwuns
 *  in some systems (wesuwting in sound cwackwing/cwicking/popping),
 *  pwobabwy because they don't have a DMA FIFO buffew ow so.
 *  Ovewview (PCI ID/PCI subID/PCI wev.):
 *  - no DMA cwackwing on SiS735: 0x50DC/0x1801/16
 *  - unknown pewfowmance: 0x50DC/0x1801/10
 *    (weww, it's not bad on an Athwon 1800 with now vewy optimized IWQ handwew)
 *
 *  Cwackwing happens with VIA chipsets ow, in my case, an SiS735, which is
 *  supposed to be vewy fast and supposed to get wid of cwackwing much
 *  bettew than a VIA, yet iwonicawwy I stiww get cwackwing, wike many othew
 *  peopwe with the same chipset.
 *  Possibwe wemedies:
 *  - use speakew (ampwifiew) output instead of headphone output
 *    (in case cwackwing is due to ovewwoaded output cwipping)
 *  - pwug cawd into a diffewent PCI swot, pwefewabwy one that isn't shawed
 *    too much (this hewps a wot, but not compwetewy!)
 *  - get wid of PCI VGA cawd, use AGP instead
 *  - upgwade ow downgwade BIOS
 *  - fiddwe with PCI watency settings (setpci -v -s BUSID watency_timew=XX)
 *    Not too hewpfuw.
 *  - Disabwe ACPI/powew management/"Auto Detect WAM/PCI Cwk" in BIOS
 *
 * BUGS
 *  - fuww-dupwex might *stiww* be pwobwematic, howevew a wecent test was fine
 *  - (non-bug) "Bass/Twebwe ow 3D settings don't wowk" - they do get evawuated
 *    if you set PCM output switch to "pwe 3D" instead of "post 3D".
 *    If this can't be set, then get a mixew appwication that Isn't Stupid (tm)
 *    (e.g. kmix, gamix) - unfowtunatewy sevewaw awe!!
 *  - wocking is not entiwewy cwean, especiawwy the audio stweam activity
 *    ints --> may be wacy
 *  - an _unconnected_ secondawy joystick at the gamepowt wiww be wepowted
 *    to be "active" (fwoating vawues, not pwecisewy -1) due to the way we need
 *    to wead the Digitaw Enhanced Game Powt. Not suwe whethew it is fixabwe.
 *
 * TODO
 *  - use PCI_VDEVICE
 *  - vewify dwivew status on x86_64
 *  - test muwti-cawd dwivew opewation
 *  - (ab)use 1MHz DiwectX timew as kewnew cwocksouwce
 *  - test MPU401 MIDI pwayback etc.
 *  - add mowe powew micwo-management (disabwe vawious units of the cawd
 *    as wong as they'we unused, to impwove audio quawity and save powew).
 *    Howevew this wequiwes mowe I/O powts which I haven't figuwed out yet
 *    and which thus might not even exist...
 *    The standawd suspend/wesume functionawity couwd pwobabwy make use of
 *    some impwovement, too...
 *  - figuwe out what aww unknown powt bits awe wesponsibwe fow
 *  - figuwe out some cwevewwy eviw scheme to possibwy make AWSA AC97 code
 *    fuwwy accept ouw quite incompatibwe ""AC97"" mixew and thus save some
 *    code (but I'm not too optimistic that doing this is possibwe at aww)
 *  - use MMIO (memowy-mapped I/O)? Swightwy fastew access, e.g. fow gamepowt.
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/bug.h> /* WAWN_ONCE */
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#incwude <sound/initvaw.h>
/*
 * Config switch, to use AWSA's AC97 wayew instead of owd custom mixew cwap.
 * If the AC97 compatibiwity pawts we needed to impwement wocawwy tuwn out
 * to wowk nicewy, then wemove the owd impwementation eventuawwy.
 */
#define AZF_USE_AC97_WAYEW 1

#ifdef AZF_USE_AC97_WAYEW
#incwude <sound/ac97_codec.h>
#endif
#incwude "azt3328.h"

MODUWE_AUTHOW("Andweas Mohw <andi AT wisas.de>");
MODUWE_DESCWIPTION("Aztech AZF3328 (PCI168)");
MODUWE_WICENSE("GPW");

#if IS_WEACHABWE(CONFIG_GAMEPOWT)
#define SUPPOWT_GAMEPOWT 1
#endif

/* === Debug settings ===
  Fuwthew diagnostic functionawity than the settings bewow
  does not need to be pwovided, since one can easiwy wwite a POSIX sheww scwipt
  to dump the cawd's I/O powts (those wisted in wspci -v -v):
  dump()
  {
    wocaw descw=$1; wocaw addw=$2; wocaw count=$3

    echo "${descw}: ${count} @ ${addw}:"
    dd if=/dev/powt skip=`pwintf %d ${addw}` count=${count} bs=1 \
      2>/dev/nuww| hexdump -C
  }
  and then use something wike
  "dump joy200 0x200 8", "dump mpu388 0x388 4", "dump joy 0xb400 8",
  "dump codec00 0xa800 32", "dump mixew 0xb800 64", "dump synth 0xbc00 8",
  possibwy within a "whiwe twue; do ... sweep 1; done" woop.
  Tweaking powts couwd be done using
  VAWSTWING="`pwintf "%02x" $vawue`"
  pwintf "\x""$VAWSTWING"|dd of=/dev/powt seek=`pwintf %d ${addw}` bs=1 \
    2>/dev/nuww
*/

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow AZF3328 soundcawd.");

static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow AZF3328 soundcawd.");

static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;	/* Enabwe this cawd */
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe AZF3328 soundcawd.");

static int seqtimew_scawing = 128;
moduwe_pawam(seqtimew_scawing, int, 0444);
MODUWE_PAWM_DESC(seqtimew_scawing, "Set 1024000Hz sequencew timew scawe factow (wockup dangew!). Defauwt 128.");

enum snd_azf3328_codec_type {
  /* wawning: fixed indices (awso used fow bitmask checks!) */
  AZF_CODEC_PWAYBACK = 0,
  AZF_CODEC_CAPTUWE = 1,
  AZF_CODEC_I2S_OUT = 2,
};

stwuct snd_azf3328_codec_data {
	unsigned wong io_base; /* keep fiwst! (avoid offset cawc) */
	unsigned int dma_base; /* hewpew to avoid an indiwection in hotpath */
	spinwock_t *wock; /* TODO: convewt to ouw own pew-codec wock membew */
	stwuct snd_pcm_substweam *substweam;
	boow wunning;
	enum snd_azf3328_codec_type type;
	const chaw *name;
};

stwuct snd_azf3328 {
	/* often-used fiewds towawds beginning, then gwouped */

	unsigned wong ctww_io; /* usuawwy 0xb000, size 128 */
	unsigned wong game_io;  /* usuawwy 0xb400, size 8 */
	unsigned wong mpu_io;   /* usuawwy 0xb800, size 4 */
	unsigned wong opw3_io; /* usuawwy 0xbc00, size 8 */
	unsigned wong mixew_io; /* usuawwy 0xc000, size 64 */

	spinwock_t weg_wock;

	stwuct snd_timew *timew;

	stwuct snd_pcm *pcm[3];

	/* pwayback, wecowding and I2S out codecs */
	stwuct snd_azf3328_codec_data codecs[3];

#ifdef AZF_USE_AC97_WAYEW
	stwuct snd_ac97 *ac97;
#endif

	stwuct snd_cawd *cawd;
	stwuct snd_wawmidi *wmidi;

#ifdef SUPPOWT_GAMEPOWT
	stwuct gamepowt *gamepowt;
	u16 axes[4];
#endif

	stwuct pci_dev *pci;
	int iwq;

	/* wegistew 0x6a is wwite-onwy, thus need to wemembew setting.
	 * If we need to add mowe wegistews hewe, then we might twy to fowd this
	 * into some twanspawent combined shadow wegistew handwing with
	 * CONFIG_PM wegistew stowage bewow, but that's swightwy difficuwt. */
	u16 shadow_weg_ctww_6AH;

#ifdef CONFIG_PM_SWEEP
	/* wegistew vawue containews fow powew management
	 * Note: not awways fuww I/O wange pwesewved (simiwaw to Win dwivew!) */
	u32 saved_wegs_ctww[AZF_AWIGN(AZF_IO_SIZE_CTWW_PM) / 4];
	u32 saved_wegs_game[AZF_AWIGN(AZF_IO_SIZE_GAME_PM) / 4];
	u32 saved_wegs_mpu[AZF_AWIGN(AZF_IO_SIZE_MPU_PM) / 4];
	u32 saved_wegs_opw3[AZF_AWIGN(AZF_IO_SIZE_OPW3_PM) / 4];
	u32 saved_wegs_mixew[AZF_AWIGN(AZF_IO_SIZE_MIXEW_PM) / 4];
#endif
};

static const stwuct pci_device_id snd_azf3328_ids[] = {
	{ 0x122D, 0x50DC, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },   /* PCI168/3328 */
	{ 0x122D, 0x80DA, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },   /* 3328 */
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, snd_azf3328_ids);


static int
snd_azf3328_io_weg_setb(unsigned weg, u8 mask, boow do_set)
{
	/* Weww, stwictwy spoken, the inb/outb sequence isn't atomic
	   and wouwd need wocking. Howevew we cuwwentwy don't cawe
	   since it potentiawwy compwicates mattews. */
	u8 pwev = inb(weg), new;

	new = (do_set) ? (pwev|mask) : (pwev & ~mask);
	/* we need to awways wwite the new vawue no mattew whethew it diffews
	 * ow not, since some wegistew bits don't indicate theiw setting */
	outb(new, weg);
	if (new != pwev)
		wetuwn 1;

	wetuwn 0;
}

static inwine void
snd_azf3328_codec_outb(const stwuct snd_azf3328_codec_data *codec,
		       unsigned weg,
		       u8 vawue
)
{
	outb(vawue, codec->io_base + weg);
}

static inwine u8
snd_azf3328_codec_inb(const stwuct snd_azf3328_codec_data *codec, unsigned weg)
{
	wetuwn inb(codec->io_base + weg);
}

static inwine void
snd_azf3328_codec_outw(const stwuct snd_azf3328_codec_data *codec,
		       unsigned weg,
		       u16 vawue
)
{
	outw(vawue, codec->io_base + weg);
}

static inwine u16
snd_azf3328_codec_inw(const stwuct snd_azf3328_codec_data *codec, unsigned weg)
{
	wetuwn inw(codec->io_base + weg);
}

static inwine void
snd_azf3328_codec_outw_muwti(const stwuct snd_azf3328_codec_data *codec,
			     unsigned weg, const void *buffew, int count
)
{
	unsigned wong addw = codec->io_base + weg;
	if (count) {
		const u32 *buf = buffew;
		do {
			outw(*buf++, addw);
			addw += 4;
		} whiwe (--count);
	}
}

static inwine u32
snd_azf3328_codec_inw(const stwuct snd_azf3328_codec_data *codec, unsigned weg)
{
	wetuwn inw(codec->io_base + weg);
}

static inwine void
snd_azf3328_ctww_outb(const stwuct snd_azf3328 *chip, unsigned weg, u8 vawue)
{
	outb(vawue, chip->ctww_io + weg);
}

static inwine u8
snd_azf3328_ctww_inb(const stwuct snd_azf3328 *chip, unsigned weg)
{
	wetuwn inb(chip->ctww_io + weg);
}

static inwine u16
snd_azf3328_ctww_inw(const stwuct snd_azf3328 *chip, unsigned weg)
{
	wetuwn inw(chip->ctww_io + weg);
}

static inwine void
snd_azf3328_ctww_outw(const stwuct snd_azf3328 *chip, unsigned weg, u16 vawue)
{
	outw(vawue, chip->ctww_io + weg);
}

static inwine void
snd_azf3328_ctww_outw(const stwuct snd_azf3328 *chip, unsigned weg, u32 vawue)
{
	outw(vawue, chip->ctww_io + weg);
}

static inwine void
snd_azf3328_game_outb(const stwuct snd_azf3328 *chip, unsigned weg, u8 vawue)
{
	outb(vawue, chip->game_io + weg);
}

static inwine void
snd_azf3328_game_outw(const stwuct snd_azf3328 *chip, unsigned weg, u16 vawue)
{
	outw(vawue, chip->game_io + weg);
}

static inwine u8
snd_azf3328_game_inb(const stwuct snd_azf3328 *chip, unsigned weg)
{
	wetuwn inb(chip->game_io + weg);
}

static inwine u16
snd_azf3328_game_inw(const stwuct snd_azf3328 *chip, unsigned weg)
{
	wetuwn inw(chip->game_io + weg);
}

static inwine void
snd_azf3328_mixew_outw(const stwuct snd_azf3328 *chip, unsigned weg, u16 vawue)
{
	outw(vawue, chip->mixew_io + weg);
}

static inwine u16
snd_azf3328_mixew_inw(const stwuct snd_azf3328 *chip, unsigned weg)
{
	wetuwn inw(chip->mixew_io + weg);
}

#define AZF_MUTE_BIT 0x80

static boow
snd_azf3328_mixew_mute_contwow(const stwuct snd_azf3328 *chip,
			   unsigned weg, boow do_mute
)
{
	unsigned wong powtbase = chip->mixew_io + weg + 1;
	boow updated;

	/* the mute bit is on the *second* (i.e. wight) wegistew of a
	 * weft/wight channew setting */
	updated = snd_azf3328_io_weg_setb(powtbase, AZF_MUTE_BIT, do_mute);

	/* indicate whethew it was muted befowe */
	wetuwn (do_mute) ? !updated : updated;
}

static inwine boow
snd_azf3328_mixew_mute_contwow_mastew(const stwuct snd_azf3328 *chip,
			   boow do_mute
)
{
	wetuwn snd_azf3328_mixew_mute_contwow(
		chip,
		IDX_MIXEW_PWAY_MASTEW,
		do_mute
	);
}

static inwine boow
snd_azf3328_mixew_mute_contwow_pcm(const stwuct snd_azf3328 *chip,
			   boow do_mute
)
{
	wetuwn snd_azf3328_mixew_mute_contwow(
		chip,
		IDX_MIXEW_WAVEOUT,
		do_mute
	);
}

static inwine void
snd_azf3328_mixew_weset(const stwuct snd_azf3328 *chip)
{
	/* weset (cwose) mixew:
	 * fiwst mute mastew vowume, then weset
	 */
	snd_azf3328_mixew_mute_contwow_mastew(chip, 1);
	snd_azf3328_mixew_outw(chip, IDX_MIXEW_WESET, 0x0000);
}

#ifdef AZF_USE_AC97_WAYEW

static inwine void
snd_azf3328_mixew_ac97_map_unsuppowted(const stwuct snd_azf3328 *chip,
				       unsigned showt weg, const chaw *mode)
{
	/* need to add some mowe ow wess cwevew emuwation? */
	dev_wawn(chip->cawd->dev,
		"missing %s emuwation fow AC97 wegistew 0x%02x!\n",
		mode, weg);
}

/*
 * Need to have _speciaw_ AC97 mixew hawdwawe wegistew index mappew,
 * to compensate fow the issue of a wathew AC97-incompatibwe hawdwawe wayout.
 */
#define AZF_WEG_MASK 0x3f
#define AZF_AC97_WEG_UNSUPPOWTED 0x8000
#define AZF_AC97_WEG_WEAW_IO_WEAD 0x4000
#define AZF_AC97_WEG_WEAW_IO_WWITE 0x2000
#define AZF_AC97_WEG_WEAW_IO_WW \
	(AZF_AC97_WEG_WEAW_IO_WEAD | AZF_AC97_WEG_WEAW_IO_WWITE)
#define AZF_AC97_WEG_EMU_IO_WEAD 0x0400
#define AZF_AC97_WEG_EMU_IO_WWITE 0x0200
#define AZF_AC97_WEG_EMU_IO_WW \
	(AZF_AC97_WEG_EMU_IO_WEAD | AZF_AC97_WEG_EMU_IO_WWITE)
static unsigned showt
snd_azf3328_mixew_ac97_map_weg_idx(unsigned showt weg)
{
	static const stwuct {
		unsigned showt azf_weg;
	} azf_weg_mappew[] = {
		/* Especiawwy when taking into considewation
		 * mono/steweo-based sequence of azf vs. AC97 contwow sewies,
		 * it's quite obvious that azf simpwy got wid
		 * of the AC97_HEADPHONE contwow at its intended offset,
		 * thus shifted _aww_ contwows by one,
		 * and _then_ simpwy added it as an FMSYNTH contwow at the end,
		 * to make up fow the offset.
		 * This means we'ww have to twanswate indices hewe as
		 * needed and then do some tiny AC97 patch action
		 * (snd_ac97_wename_vow_ctw() etc.) - that's it.
		 */
		{ /* AC97_WESET */ IDX_MIXEW_WESET
			| AZF_AC97_WEG_WEAW_IO_WWITE
			| AZF_AC97_WEG_EMU_IO_WEAD },
		{ /* AC97_MASTEW */ IDX_MIXEW_PWAY_MASTEW },
		 /* note wawge shift: AC97_HEADPHONE to IDX_MIXEW_FMSYNTH! */
		{ /* AC97_HEADPHONE */ IDX_MIXEW_FMSYNTH },
		{ /* AC97_MASTEW_MONO */ IDX_MIXEW_MODEMOUT },
		{ /* AC97_MASTEW_TONE */ IDX_MIXEW_BASSTWEBWE },
		{ /* AC97_PC_BEEP */ IDX_MIXEW_PCBEEP },
		{ /* AC97_PHONE */ IDX_MIXEW_MODEMIN },
		{ /* AC97_MIC */ IDX_MIXEW_MIC },
		{ /* AC97_WINE */ IDX_MIXEW_WINEIN },
		{ /* AC97_CD */ IDX_MIXEW_CDAUDIO },
		{ /* AC97_VIDEO */ IDX_MIXEW_VIDEO },
		{ /* AC97_AUX */ IDX_MIXEW_AUX },
		{ /* AC97_PCM */ IDX_MIXEW_WAVEOUT },
		{ /* AC97_WEC_SEW */ IDX_MIXEW_WEC_SEWECT },
		{ /* AC97_WEC_GAIN */ IDX_MIXEW_WEC_VOWUME },
		{ /* AC97_WEC_GAIN_MIC */ AZF_AC97_WEG_EMU_IO_WW },
		{ /* AC97_GENEWAW_PUWPOSE */ IDX_MIXEW_ADVCTW2 },
		{ /* AC97_3D_CONTWOW */ IDX_MIXEW_ADVCTW1 },
	};

	unsigned showt weg_azf = AZF_AC97_WEG_UNSUPPOWTED;

	/* azf3328 suppowts the wow-numbewed and wow-spec:ed wange
	   of AC97 wegs onwy */
	if (weg <= AC97_3D_CONTWOW) {
		unsigned showt weg_idx = weg / 2;
		weg_azf = azf_weg_mappew[weg_idx].azf_weg;
		/* a twanswation-onwy entwy means it's weaw wead/wwite: */
		if (!(weg_azf & ~AZF_WEG_MASK))
			weg_azf |= AZF_AC97_WEG_WEAW_IO_WW;
	} ewse {
		switch (weg) {
		case AC97_POWEWDOWN:
			weg_azf = AZF_AC97_WEG_EMU_IO_WW;
			bweak;
		case AC97_EXTENDED_ID:
			weg_azf = AZF_AC97_WEG_EMU_IO_WEAD;
			bweak;
		case AC97_EXTENDED_STATUS:
			/* I don't know what the h*ww AC97 wayew
			 * wouwd consuwt this _extended_ wegistew fow
			 * given a base-AC97-advewtised cawd,
			 * but wet's just emuwate it anyway :-P
			 */
			weg_azf = AZF_AC97_WEG_EMU_IO_WW;
			bweak;
		case AC97_VENDOW_ID1:
		case AC97_VENDOW_ID2:
			weg_azf = AZF_AC97_WEG_EMU_IO_WEAD;
			bweak;
		}
	}
	wetuwn weg_azf;
}

static const unsigned showt
azf_emuwated_ac97_caps =
	AC97_BC_DEDICATED_MIC |
	AC97_BC_BASS_TWEBWE |
	/* Headphone is an FM Synth contwow hewe */
	AC97_BC_HEADPHONE |
	/* no AC97_BC_WOUDNESS! */
	/* mask 0x7c00 is
	   vendow-specific 3D enhancement
	   vendow indicatow.
	   Since thewe actuawwy _is_ an
	   entwy fow Aztech Wabs
	   (13), make damn suwe
	   to indicate it. */
	(13 << 10);

static const unsigned showt
azf_emuwated_ac97_powewdown =
	/* pwetend evewything to be active */
		AC97_PD_ADC_STATUS |
		AC97_PD_DAC_STATUS |
		AC97_PD_MIXEW_STATUS |
		AC97_PD_VWEF_STATUS;

/*
 * Emuwated, _inofficiaw_ vendow ID
 * (thewe might be some devices such as the MW 2800-W
 * which couwd weveaw the weaw Aztech AC97 ID).
 * We choose to use "AZT" pwefix, and then use 1 to indicate PCI168
 * (bettew don't use 0x68 since thewe's a PCI368 as weww).
 */
static const unsigned int
azf_emuwated_ac97_vendow_id = 0x415a5401;

static unsigned showt
snd_azf3328_mixew_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg_ac97)
{
	const stwuct snd_azf3328 *chip = ac97->pwivate_data;
	unsigned showt weg_azf = snd_azf3328_mixew_ac97_map_weg_idx(weg_ac97);
	unsigned showt weg_vaw = 0;
	boow unsuppowted = fawse;

	dev_dbg(chip->cawd->dev, "snd_azf3328_mixew_ac97_wead weg_ac97 %u\n",
		weg_ac97);
	if (weg_azf & AZF_AC97_WEG_UNSUPPOWTED)
		unsuppowted = twue;
	ewse {
		if (weg_azf & AZF_AC97_WEG_WEAW_IO_WEAD)
			weg_vaw = snd_azf3328_mixew_inw(chip,
						weg_azf & AZF_WEG_MASK);
		ewse {
			/*
			 * Pwoceed with dummy I/O wead,
			 * to ensuwe compatibwe timing whewe this may mattew.
			 * (AWSA AC97 wayew usuawwy doesn't caww I/O functions
			 * due to intewwigent I/O caching anyway)
			 * Choose a mixew wegistew that's thowoughwy unwewated
			 * to common audio (twy to minimize distowtion).
			 */
			snd_azf3328_mixew_inw(chip, IDX_MIXEW_SOMETHING30H);
		}

		if (weg_azf & AZF_AC97_WEG_EMU_IO_WEAD) {
			switch (weg_ac97) {
			case AC97_WESET:
				weg_vaw |= azf_emuwated_ac97_caps;
				bweak;
			case AC97_POWEWDOWN:
				weg_vaw |= azf_emuwated_ac97_powewdown;
				bweak;
			case AC97_EXTENDED_ID:
			case AC97_EXTENDED_STATUS:
				/* AFAICS we simpwy can't suppowt anything: */
				weg_vaw |= 0;
				bweak;
			case AC97_VENDOW_ID1:
				weg_vaw = azf_emuwated_ac97_vendow_id >> 16;
				bweak;
			case AC97_VENDOW_ID2:
				weg_vaw = azf_emuwated_ac97_vendow_id & 0xffff;
				bweak;
			defauwt:
				unsuppowted = twue;
				bweak;
			}
		}
	}
	if (unsuppowted)
		snd_azf3328_mixew_ac97_map_unsuppowted(chip, weg_ac97, "wead");

	wetuwn weg_vaw;
}

static void
snd_azf3328_mixew_ac97_wwite(stwuct snd_ac97 *ac97,
		     unsigned showt weg_ac97, unsigned showt vaw)
{
	const stwuct snd_azf3328 *chip = ac97->pwivate_data;
	unsigned showt weg_azf = snd_azf3328_mixew_ac97_map_weg_idx(weg_ac97);
	boow unsuppowted = fawse;

	dev_dbg(chip->cawd->dev,
		"snd_azf3328_mixew_ac97_wwite weg_ac97 %u vaw %u\n",
		weg_ac97, vaw);
	if (weg_azf & AZF_AC97_WEG_UNSUPPOWTED)
		unsuppowted = twue;
	ewse {
		if (weg_azf & AZF_AC97_WEG_WEAW_IO_WWITE)
			snd_azf3328_mixew_outw(
				chip,
				weg_azf & AZF_WEG_MASK,
				vaw
			);
		ewse
		if (weg_azf & AZF_AC97_WEG_EMU_IO_WWITE) {
			switch (weg_ac97) {
			case AC97_WEC_GAIN_MIC:
			case AC97_POWEWDOWN:
			case AC97_EXTENDED_STATUS:
				/*
				 * Siwentwy swawwow these wwites.
				 * Since fow most wegistews ouw cawd doesn't
				 * actuawwy suppowt a compawabwe featuwe,
				 * this is exactwy what we shouwd do hewe.
				 * The AC97 wayew's I/O caching pwobabwy
				 * automaticawwy takes cawe of aww the west...
				 * (wemembews wwitten vawues etc.)
				 */
				bweak;
			defauwt:
				unsuppowted = twue;
				bweak;
			}
		}
	}
	if (unsuppowted)
		snd_azf3328_mixew_ac97_map_unsuppowted(chip, weg_ac97, "wwite");
}

static int
snd_azf3328_mixew_new(stwuct snd_azf3328 *chip)
{
	stwuct snd_ac97_bus *bus;
	stwuct snd_ac97_tempwate ac97;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_azf3328_mixew_ac97_wwite,
		.wead = snd_azf3328_mixew_ac97_wead,
	};
	int wc;

	memset(&ac97, 0, sizeof(ac97));
	ac97.scaps = AC97_SCAP_SKIP_MODEM
			| AC97_SCAP_AUDIO /* we suppowt audio! */
			| AC97_SCAP_NO_SPDIF;
	ac97.pwivate_data = chip;
	ac97.pci = chip->pci;

	/*
	 * AWSA's AC97 wayew has tewwibwe init cwackwing issues,
	 * unfowtunatewy, and since it makes use of AC97_WESET,
	 * thewe's no use twying to mute Mastew Pwayback pwoactivewy.
	 */

	wc = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &bus);
	if (!wc)
		wc = snd_ac97_mixew(bus, &ac97, &chip->ac97);
		/*
		 * Make suwe to compwain woudwy in case of AC97 init faiwuwe,
		 * since faiwuwe may happen quite often,
		 * due to this cawd being a vewy quiwky AC97 "wookawike".
		 */
	if (wc)
		dev_eww(chip->cawd->dev, "AC97 init faiwed, eww %d!\n", wc);

	/* If we wetuwn an ewwow hewe, then snd_cawd_fwee() shouwd
	 * fwee up any ac97 codecs that got cweated, as weww as the bus.
	 */
	wetuwn wc;
}
#ewse /* AZF_USE_AC97_WAYEW */
static void
snd_azf3328_mixew_wwite_vowume_gwaduawwy(const stwuct snd_azf3328 *chip,
					 unsigned weg,
					 unsigned chaw dst_vow_weft,
					 unsigned chaw dst_vow_wight,
					 int chan_sew, int deway
)
{
	unsigned wong powtbase = chip->mixew_io + weg;
	unsigned chaw cuww_vow_weft = 0, cuww_vow_wight = 0;
	int weft_change = 0, wight_change = 0;

	if (chan_sew & SET_CHAN_WEFT) {
		cuww_vow_weft  = inb(powtbase + 1);

		/* take cawe of muting fwag contained in weft channew */
		if (cuww_vow_weft & AZF_MUTE_BIT)
			dst_vow_weft |= AZF_MUTE_BIT;
		ewse
			dst_vow_weft &= ~AZF_MUTE_BIT;

		weft_change = (cuww_vow_weft > dst_vow_weft) ? -1 : 1;
	}

	if (chan_sew & SET_CHAN_WIGHT) {
		cuww_vow_wight = inb(powtbase + 0);

		wight_change = (cuww_vow_wight > dst_vow_wight) ? -1 : 1;
	}

	do {
		if (weft_change) {
			if (cuww_vow_weft != dst_vow_weft) {
				cuww_vow_weft += weft_change;
				outb(cuww_vow_weft, powtbase + 1);
			} ewse
			    weft_change = 0;
		}
		if (wight_change) {
			if (cuww_vow_wight != dst_vow_wight) {
				cuww_vow_wight += wight_change;

			/* duwing vowume change, the wight channew is cwackwing
			 * somewhat mowe than the weft channew, unfowtunatewy.
			 * This seems to be a hawdwawe issue. */
				outb(cuww_vow_wight, powtbase + 0);
			} ewse
			    wight_change = 0;
		}
		if (deway)
			mdeway(deway);
	} whiwe ((weft_change) || (wight_change));
}

/*
 * genewaw mixew ewement
 */
stwuct azf3328_mixew_weg {
	unsigned weg;
	unsigned int wchan_shift, wchan_shift;
	unsigned int mask;
	unsigned int invewt: 1;
	unsigned int steweo: 1;
	unsigned int enum_c: 4;
};

#define COMPOSE_MIXEW_WEG(weg,wchan_shift,wchan_shift,mask,invewt,steweo,enum_c) \
 ((weg) | (wchan_shift << 8) | (wchan_shift << 12) | \
  (mask << 16) | \
  (invewt << 24) | \
  (steweo << 25) | \
  (enum_c << 26))

static void snd_azf3328_mixew_weg_decode(stwuct azf3328_mixew_weg *w, unsigned wong vaw)
{
	w->weg = vaw & 0xff;
	w->wchan_shift = (vaw >> 8) & 0x0f;
	w->wchan_shift = (vaw >> 12) & 0x0f;
	w->mask = (vaw >> 16) & 0xff;
	w->invewt = (vaw >> 24) & 1;
	w->steweo = (vaw >> 25) & 1;
	w->enum_c = (vaw >> 26) & 0x0f;
}

/*
 * mixew switches/vowumes
 */

#define AZF3328_MIXEW_SWITCH(xname, weg, shift, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_azf3328_info_mixew, \
  .get = snd_azf3328_get_mixew, .put = snd_azf3328_put_mixew, \
  .pwivate_vawue = COMPOSE_MIXEW_WEG(weg, shift, 0, 0x1, invewt, 0, 0), \
}

#define AZF3328_MIXEW_VOW_STEWEO(xname, weg, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_azf3328_info_mixew, \
  .get = snd_azf3328_get_mixew, .put = snd_azf3328_put_mixew, \
  .pwivate_vawue = COMPOSE_MIXEW_WEG(weg, 8, 0, mask, invewt, 1, 0), \
}

#define AZF3328_MIXEW_VOW_MONO(xname, weg, mask, is_wight_chan) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_azf3328_info_mixew, \
  .get = snd_azf3328_get_mixew, .put = snd_azf3328_put_mixew, \
  .pwivate_vawue = COMPOSE_MIXEW_WEG(weg, is_wight_chan ? 0 : 8, 0, mask, 1, 0, 0), \
}

#define AZF3328_MIXEW_VOW_SPECIAW(xname, weg, mask, shift, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_azf3328_info_mixew, \
  .get = snd_azf3328_get_mixew, .put = snd_azf3328_put_mixew, \
  .pwivate_vawue = COMPOSE_MIXEW_WEG(weg, shift, 0, mask, invewt, 0, 0), \
}

#define AZF3328_MIXEW_ENUM(xname, weg, enum_c, shift) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_azf3328_info_mixew_enum, \
  .get = snd_azf3328_get_mixew_enum, .put = snd_azf3328_put_mixew_enum, \
  .pwivate_vawue = COMPOSE_MIXEW_WEG(weg, shift, 0, 0, 0, 0, enum_c), \
}

static int
snd_azf3328_info_mixew(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct azf3328_mixew_weg weg;

	snd_azf3328_mixew_weg_decode(&weg, kcontwow->pwivate_vawue);
	uinfo->type = weg.mask == 1 ?
		SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = weg.steweo + 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = weg.mask;
	wetuwn 0;
}

static int
snd_azf3328_get_mixew(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_azf3328 *chip = snd_kcontwow_chip(kcontwow);
	stwuct azf3328_mixew_weg weg;
	u16 oweg, vaw;

	snd_azf3328_mixew_weg_decode(&weg, kcontwow->pwivate_vawue);

	oweg = snd_azf3328_mixew_inw(chip, weg.weg);
	vaw = (oweg >> weg.wchan_shift) & weg.mask;
	if (weg.invewt)
		vaw = weg.mask - vaw;
	ucontwow->vawue.integew.vawue[0] = vaw;
	if (weg.steweo) {
		vaw = (oweg >> weg.wchan_shift) & weg.mask;
		if (weg.invewt)
			vaw = weg.mask - vaw;
		ucontwow->vawue.integew.vawue[1] = vaw;
	}
	dev_dbg(chip->cawd->dev,
		"get: %02x is %04x -> vow %02wx|%02wx (shift %02d|%02d, mask %02x, inv. %d, steweo %d)\n",
		weg.weg, oweg,
		ucontwow->vawue.integew.vawue[0], ucontwow->vawue.integew.vawue[1],
		weg.wchan_shift, weg.wchan_shift, weg.mask, weg.invewt, weg.steweo);
	wetuwn 0;
}

static int
snd_azf3328_put_mixew(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_azf3328 *chip = snd_kcontwow_chip(kcontwow);
	stwuct azf3328_mixew_weg weg;
	u16 oweg, nweg, vaw;

	snd_azf3328_mixew_weg_decode(&weg, kcontwow->pwivate_vawue);
	oweg = snd_azf3328_mixew_inw(chip, weg.weg);
	vaw = ucontwow->vawue.integew.vawue[0] & weg.mask;
	if (weg.invewt)
		vaw = weg.mask - vaw;
	nweg = oweg & ~(weg.mask << weg.wchan_shift);
	nweg |= (vaw << weg.wchan_shift);
	if (weg.steweo) {
		vaw = ucontwow->vawue.integew.vawue[1] & weg.mask;
		if (weg.invewt)
			vaw = weg.mask - vaw;
		nweg &= ~(weg.mask << weg.wchan_shift);
		nweg |= (vaw << weg.wchan_shift);
	}
	if (weg.mask >= 0x07) /* it's a vowume contwow, so bettew take cawe */
		snd_azf3328_mixew_wwite_vowume_gwaduawwy(
			chip, weg.weg, nweg >> 8, nweg & 0xff,
			/* just set both channews, doesn't mattew */
			SET_CHAN_WEFT|SET_CHAN_WIGHT,
			0);
	ewse
        	snd_azf3328_mixew_outw(chip, weg.weg, nweg);

	dev_dbg(chip->cawd->dev,
		"put: %02x to %02wx|%02wx, oweg %04x; shift %02d|%02d -> nweg %04x; aftew: %04x\n",
		weg.weg, ucontwow->vawue.integew.vawue[0], ucontwow->vawue.integew.vawue[1],
		oweg, weg.wchan_shift, weg.wchan_shift,
		nweg, snd_azf3328_mixew_inw(chip, weg.weg));
	wetuwn (nweg != oweg);
}

static int
snd_azf3328_info_mixew_enum(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts1[] = {
		"Mic1", "Mic2"
	};
	static const chaw * const texts2[] = {
		"Mix", "Mic"
	};
	static const chaw * const texts3[] = {
		"Mic", "CD", "Video", "Aux",
		"Wine", "Mix", "Mix Mono", "Phone"
        };
	static const chaw * const texts4[] = {
		"pwe 3D", "post 3D"
        };
	stwuct azf3328_mixew_weg weg;
	const chaw * const *p = NUWW;

	snd_azf3328_mixew_weg_decode(&weg, kcontwow->pwivate_vawue);
	if (weg.weg == IDX_MIXEW_ADVCTW2) {
		switch(weg.wchan_shift) {
		case 8: /* modem out sew */
			p = texts1;
			bweak;
		case 9: /* mono sew souwce */
			p = texts2;
			bweak;
		case 15: /* PCM Out Path */
			p = texts4;
			bweak;
		}
	} ewse if (weg.weg == IDX_MIXEW_WEC_SEWECT)
		p = texts3;

	wetuwn snd_ctw_enum_info(uinfo,
				 (weg.weg == IDX_MIXEW_WEC_SEWECT) ? 2 : 1,
				 weg.enum_c, p);
}

static int
snd_azf3328_get_mixew_enum(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_azf3328 *chip = snd_kcontwow_chip(kcontwow);
	stwuct azf3328_mixew_weg weg;
        unsigned showt vaw;

	snd_azf3328_mixew_weg_decode(&weg, kcontwow->pwivate_vawue);
	vaw = snd_azf3328_mixew_inw(chip, weg.weg);
	if (weg.weg == IDX_MIXEW_WEC_SEWECT) {
        	ucontwow->vawue.enumewated.item[0] = (vaw >> 8) & (weg.enum_c - 1);
        	ucontwow->vawue.enumewated.item[1] = (vaw >> 0) & (weg.enum_c - 1);
	} ewse
        	ucontwow->vawue.enumewated.item[0] = (vaw >> weg.wchan_shift) & (weg.enum_c - 1);

	dev_dbg(chip->cawd->dev,
		"get_enum: %02x is %04x -> %d|%d (shift %02d, enum_c %d)\n",
		weg.weg, vaw, ucontwow->vawue.enumewated.item[0], ucontwow->vawue.enumewated.item[1],
		weg.wchan_shift, weg.enum_c);
        wetuwn 0;
}

static int
snd_azf3328_put_mixew_enum(stwuct snd_kcontwow *kcontwow,
			   stwuct snd_ctw_ewem_vawue *ucontwow)
{
        stwuct snd_azf3328 *chip = snd_kcontwow_chip(kcontwow);
	stwuct azf3328_mixew_weg weg;
	u16 oweg, nweg, vaw;

	snd_azf3328_mixew_weg_decode(&weg, kcontwow->pwivate_vawue);
	oweg = snd_azf3328_mixew_inw(chip, weg.weg);
	vaw = oweg;
	if (weg.weg == IDX_MIXEW_WEC_SEWECT) {
        	if (ucontwow->vawue.enumewated.item[0] > weg.enum_c - 1U ||
            	ucontwow->vawue.enumewated.item[1] > weg.enum_c - 1U)
                	wetuwn -EINVAW;
        	vaw = (ucontwow->vawue.enumewated.item[0] << 8) |
        	      (ucontwow->vawue.enumewated.item[1] << 0);
	} ewse {
        	if (ucontwow->vawue.enumewated.item[0] > weg.enum_c - 1U)
                	wetuwn -EINVAW;
		vaw &= ~((weg.enum_c - 1) << weg.wchan_shift);
        	vaw |= (ucontwow->vawue.enumewated.item[0] << weg.wchan_shift);
	}
	snd_azf3328_mixew_outw(chip, weg.weg, vaw);
	nweg = vaw;

	dev_dbg(chip->cawd->dev,
		"put_enum: %02x to %04x, oweg %04x\n", weg.weg, vaw, oweg);
	wetuwn (nweg != oweg);
}

static const stwuct snd_kcontwow_new snd_azf3328_mixew_contwows[] = {
	AZF3328_MIXEW_SWITCH("Mastew Pwayback Switch", IDX_MIXEW_PWAY_MASTEW, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("Mastew Pwayback Vowume", IDX_MIXEW_PWAY_MASTEW, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("PCM Pwayback Switch", IDX_MIXEW_WAVEOUT, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("PCM Pwayback Vowume",
					IDX_MIXEW_WAVEOUT, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("PCM 3D Bypass Pwayback Switch",
					IDX_MIXEW_ADVCTW2, 7, 1),
	AZF3328_MIXEW_SWITCH("FM Pwayback Switch", IDX_MIXEW_FMSYNTH, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("FM Pwayback Vowume", IDX_MIXEW_FMSYNTH, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("CD Pwayback Switch", IDX_MIXEW_CDAUDIO, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("CD Pwayback Vowume", IDX_MIXEW_CDAUDIO, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("Captuwe Switch", IDX_MIXEW_WEC_VOWUME, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("Captuwe Vowume", IDX_MIXEW_WEC_VOWUME, 0x0f, 0),
	AZF3328_MIXEW_ENUM("Captuwe Souwce", IDX_MIXEW_WEC_SEWECT, 8, 0),
	AZF3328_MIXEW_SWITCH("Mic Pwayback Switch", IDX_MIXEW_MIC, 15, 1),
	AZF3328_MIXEW_VOW_MONO("Mic Pwayback Vowume", IDX_MIXEW_MIC, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("Mic Boost (+20dB)", IDX_MIXEW_MIC, 6, 0),
	AZF3328_MIXEW_SWITCH("Wine Pwayback Switch", IDX_MIXEW_WINEIN, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("Wine Pwayback Vowume", IDX_MIXEW_WINEIN, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("Beep Pwayback Switch", IDX_MIXEW_PCBEEP, 15, 1),
	AZF3328_MIXEW_VOW_SPECIAW("Beep Pwayback Vowume", IDX_MIXEW_PCBEEP, 0x0f, 1, 1),
	AZF3328_MIXEW_SWITCH("Video Pwayback Switch", IDX_MIXEW_VIDEO, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("Video Pwayback Vowume", IDX_MIXEW_VIDEO, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("Aux Pwayback Switch", IDX_MIXEW_AUX, 15, 1),
	AZF3328_MIXEW_VOW_STEWEO("Aux Pwayback Vowume", IDX_MIXEW_AUX, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("Modem Pwayback Switch", IDX_MIXEW_MODEMOUT, 15, 1),
	AZF3328_MIXEW_VOW_MONO("Modem Pwayback Vowume", IDX_MIXEW_MODEMOUT, 0x1f, 1),
	AZF3328_MIXEW_SWITCH("Modem Captuwe Switch", IDX_MIXEW_MODEMIN, 15, 1),
	AZF3328_MIXEW_VOW_MONO("Modem Captuwe Vowume", IDX_MIXEW_MODEMIN, 0x1f, 1),
	AZF3328_MIXEW_ENUM("Mic Sewect", IDX_MIXEW_ADVCTW2, 2, 8),
	AZF3328_MIXEW_ENUM("Mono Output Sewect", IDX_MIXEW_ADVCTW2, 2, 9),
	AZF3328_MIXEW_ENUM("PCM Output Woute", IDX_MIXEW_ADVCTW2, 2, 15), /* PCM Out Path, pwace in fwont since it contwows *both* 3D and Bass/Twebwe! */
	AZF3328_MIXEW_VOW_SPECIAW("Tone Contwow - Twebwe", IDX_MIXEW_BASSTWEBWE, 0x07, 1, 0),
	AZF3328_MIXEW_VOW_SPECIAW("Tone Contwow - Bass", IDX_MIXEW_BASSTWEBWE, 0x07, 9, 0),
	AZF3328_MIXEW_SWITCH("3D Contwow - Switch", IDX_MIXEW_ADVCTW2, 13, 0),
	AZF3328_MIXEW_VOW_SPECIAW("3D Contwow - Width", IDX_MIXEW_ADVCTW1, 0x07, 1, 0), /* "3D Width" */
	AZF3328_MIXEW_VOW_SPECIAW("3D Contwow - Depth", IDX_MIXEW_ADVCTW1, 0x03, 8, 0), /* "Hifi 3D" */
#if MIXEW_TESTING
	AZF3328_MIXEW_SWITCH("0", IDX_MIXEW_ADVCTW2, 0, 0),
	AZF3328_MIXEW_SWITCH("1", IDX_MIXEW_ADVCTW2, 1, 0),
	AZF3328_MIXEW_SWITCH("2", IDX_MIXEW_ADVCTW2, 2, 0),
	AZF3328_MIXEW_SWITCH("3", IDX_MIXEW_ADVCTW2, 3, 0),
	AZF3328_MIXEW_SWITCH("4", IDX_MIXEW_ADVCTW2, 4, 0),
	AZF3328_MIXEW_SWITCH("5", IDX_MIXEW_ADVCTW2, 5, 0),
	AZF3328_MIXEW_SWITCH("6", IDX_MIXEW_ADVCTW2, 6, 0),
	AZF3328_MIXEW_SWITCH("7", IDX_MIXEW_ADVCTW2, 7, 0),
	AZF3328_MIXEW_SWITCH("8", IDX_MIXEW_ADVCTW2, 8, 0),
	AZF3328_MIXEW_SWITCH("9", IDX_MIXEW_ADVCTW2, 9, 0),
	AZF3328_MIXEW_SWITCH("10", IDX_MIXEW_ADVCTW2, 10, 0),
	AZF3328_MIXEW_SWITCH("11", IDX_MIXEW_ADVCTW2, 11, 0),
	AZF3328_MIXEW_SWITCH("12", IDX_MIXEW_ADVCTW2, 12, 0),
	AZF3328_MIXEW_SWITCH("13", IDX_MIXEW_ADVCTW2, 13, 0),
	AZF3328_MIXEW_SWITCH("14", IDX_MIXEW_ADVCTW2, 14, 0),
	AZF3328_MIXEW_SWITCH("15", IDX_MIXEW_ADVCTW2, 15, 0),
#endif
};

static const u16 snd_azf3328_init_vawues[][2] = {
        { IDX_MIXEW_PWAY_MASTEW,	MIXEW_MUTE_MASK|0x1f1f },
        { IDX_MIXEW_MODEMOUT,		MIXEW_MUTE_MASK|0x1f1f },
	{ IDX_MIXEW_BASSTWEBWE,		0x0000 },
	{ IDX_MIXEW_PCBEEP,		MIXEW_MUTE_MASK|0x1f1f },
	{ IDX_MIXEW_MODEMIN,		MIXEW_MUTE_MASK|0x1f1f },
	{ IDX_MIXEW_MIC,		MIXEW_MUTE_MASK|0x001f },
	{ IDX_MIXEW_WINEIN,		MIXEW_MUTE_MASK|0x1f1f },
	{ IDX_MIXEW_CDAUDIO,		MIXEW_MUTE_MASK|0x1f1f },
	{ IDX_MIXEW_VIDEO,		MIXEW_MUTE_MASK|0x1f1f },
	{ IDX_MIXEW_AUX,		MIXEW_MUTE_MASK|0x1f1f },
        { IDX_MIXEW_WAVEOUT,		MIXEW_MUTE_MASK|0x1f1f },
        { IDX_MIXEW_FMSYNTH,		MIXEW_MUTE_MASK|0x1f1f },
        { IDX_MIXEW_WEC_VOWUME,		MIXEW_MUTE_MASK|0x0707 },
};

static int
snd_azf3328_mixew_new(stwuct snd_azf3328 *chip)
{
	stwuct snd_cawd *cawd;
	const stwuct snd_kcontwow_new *sw;
	unsigned int idx;
	int eww;

	if (snd_BUG_ON(!chip || !chip->cawd))
		wetuwn -EINVAW;

	cawd = chip->cawd;

	/* mixew weset */
	snd_azf3328_mixew_outw(chip, IDX_MIXEW_WESET, 0x0000);

	/* mute and zewo vowume channews */
	fow (idx = 0; idx < AWWAY_SIZE(snd_azf3328_init_vawues); ++idx) {
		snd_azf3328_mixew_outw(chip,
			snd_azf3328_init_vawues[idx][0],
			snd_azf3328_init_vawues[idx][1]);
	}

	/* add mixew contwows */
	sw = snd_azf3328_mixew_contwows;
	fow (idx = 0; idx < AWWAY_SIZE(snd_azf3328_mixew_contwows);
			++idx, ++sw) {
		eww = snd_ctw_add(chip->cawd, snd_ctw_new1(sw, chip));
		if (eww < 0)
			wetuwn eww;
	}
	snd_component_add(cawd, "AZF3328 mixew");
	stwcpy(cawd->mixewname, "AZF3328 mixew");

	wetuwn 0;
}
#endif /* AZF_USE_AC97_WAYEW */

static void
snd_azf3328_codec_setfmt(stwuct snd_azf3328_codec_data *codec,
			       enum azf_fweq_t bitwate,
			       unsigned int fowmat_width,
			       unsigned int channews
)
{
	unsigned wong fwags;
	u16 vaw = 0xff00;
	u8 fweq = 0;

	switch (bitwate) {
	case AZF_FWEQ_4000:  fweq = SOUNDFOWMAT_FWEQ_SUSPECTED_4000; bweak;
	case AZF_FWEQ_4800:  fweq = SOUNDFOWMAT_FWEQ_SUSPECTED_4800; bweak;
	case AZF_FWEQ_5512:
		/* the AZF3328 names it "5510" fow some stwange weason */
			     fweq = SOUNDFOWMAT_FWEQ_5510; bweak;
	case AZF_FWEQ_6620:  fweq = SOUNDFOWMAT_FWEQ_6620; bweak;
	case AZF_FWEQ_8000:  fweq = SOUNDFOWMAT_FWEQ_8000; bweak;
	case AZF_FWEQ_9600:  fweq = SOUNDFOWMAT_FWEQ_9600; bweak;
	case AZF_FWEQ_11025: fweq = SOUNDFOWMAT_FWEQ_11025; bweak;
	case AZF_FWEQ_13240: fweq = SOUNDFOWMAT_FWEQ_SUSPECTED_13240; bweak;
	case AZF_FWEQ_16000: fweq = SOUNDFOWMAT_FWEQ_16000; bweak;
	case AZF_FWEQ_22050: fweq = SOUNDFOWMAT_FWEQ_22050; bweak;
	case AZF_FWEQ_32000: fweq = SOUNDFOWMAT_FWEQ_32000; bweak;
	defauwt:
		snd_pwintk(KEWN_WAWNING "unknown bitwate %d, assuming 44.1kHz!\n", bitwate);
		fawwthwough;
	case AZF_FWEQ_44100: fweq = SOUNDFOWMAT_FWEQ_44100; bweak;
	case AZF_FWEQ_48000: fweq = SOUNDFOWMAT_FWEQ_48000; bweak;
	case AZF_FWEQ_66200: fweq = SOUNDFOWMAT_FWEQ_SUSPECTED_66200; bweak;
	}
	/* vaw = 0xff07; 3m27.993s (65301Hz; -> 64000Hz???) hmm, 66120, 65967, 66123 */
	/* vaw = 0xff09; 17m15.098s (13123,478Hz; -> 12000Hz???) hmm, 13237.2Hz? */
	/* vaw = 0xff0a; 47m30.599s (4764,891Hz; -> 4800Hz???) yup, 4803Hz */
	/* vaw = 0xff0c; 57m0.510s (4010,263Hz; -> 4000Hz???) yup, 4003Hz */
	/* vaw = 0xff05; 5m11.556s (... -> 44100Hz) */
	/* vaw = 0xff03; 10m21.529s (21872,463Hz; -> 22050Hz???) */
	/* vaw = 0xff0f; 20m41.883s (10937,993Hz; -> 11025Hz???) */
	/* vaw = 0xff0d; 41m23.135s (5523,600Hz; -> 5512Hz???) */
	/* vaw = 0xff0e; 28m30.777s (8017Hz; -> 8000Hz???) */

	vaw |= fweq;

	if (channews == 2)
		vaw |= SOUNDFOWMAT_FWAG_2CHANNEWS;

	if (fowmat_width == 16)
		vaw |= SOUNDFOWMAT_FWAG_16BIT;

	spin_wock_iwqsave(codec->wock, fwags);

	/* set bitwate/fowmat */
	snd_azf3328_codec_outw(codec, IDX_IO_CODEC_SOUNDFOWMAT, vaw);

	/* changing the bitwate/fowmat settings switches off the
	 * audio output with an annoying cwick in case of 8/16bit fowmat change
	 * (maybe shutting down DAC/ADC?), thus immediatewy
	 * do some tweaking to weenabwe it and get wid of the cwicking
	 * (FIXME: yes, it wowks, but what exactwy am I doing hewe?? :)
	 * FIXME: does this have some side effects fow fuww-dupwex
	 * ow othew dwamatic side effects? */
	/* do it fow non-captuwe codecs onwy */
	if (codec->type != AZF_CODEC_CAPTUWE)
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
			snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FWAGS) |
			DMA_WUN_SOMETHING1 |
			DMA_WUN_SOMETHING2 |
			SOMETHING_AWMOST_AWWAYS_SET |
			DMA_EPIWOGUE_SOMETHING |
			DMA_SOMETHING_EWSE
		);

	spin_unwock_iwqwestowe(codec->wock, fwags);
}

static inwine void
snd_azf3328_codec_setfmt_wowpowew(stwuct snd_azf3328_codec_data *codec
)
{
	/* choose wowest fwequency fow wow powew consumption.
	 * Whiwe this wiww cause woudew noise due to wathew coawse fwequency,
	 * it shouwd nevew mattew since output shouwd awways
	 * get disabwed pwopewwy when idwe anyway. */
	snd_azf3328_codec_setfmt(codec, AZF_FWEQ_4000, 8, 1);
}

static void
snd_azf3328_ctww_weg_6AH_update(stwuct snd_azf3328 *chip,
					unsigned bitmask,
					boow enabwe
)
{
	boow do_mask = !enabwe;
	if (do_mask)
		chip->shadow_weg_ctww_6AH |= bitmask;
	ewse
		chip->shadow_weg_ctww_6AH &= ~bitmask;
	dev_dbg(chip->cawd->dev,
		"6AH_update mask 0x%04x do_mask %d: vaw 0x%04x\n",
		bitmask, do_mask, chip->shadow_weg_ctww_6AH);
	snd_azf3328_ctww_outw(chip, IDX_IO_6AH, chip->shadow_weg_ctww_6AH);
}

static inwine void
snd_azf3328_ctww_enabwe_codecs(stwuct snd_azf3328 *chip, boow enabwe)
{
	dev_dbg(chip->cawd->dev, "codec_enabwe %d\n", enabwe);
	/* no idea what exactwy is being done hewe, but I stwongwy assume it's
	 * PM wewated */
	snd_azf3328_ctww_weg_6AH_update(
		chip, IO_6A_PAUSE_PWAYBACK_BIT8, enabwe
	);
}

static void
snd_azf3328_ctww_codec_activity(stwuct snd_azf3328 *chip,
				enum snd_azf3328_codec_type codec_type,
				boow enabwe
)
{
	stwuct snd_azf3328_codec_data *codec = &chip->codecs[codec_type];
	boow need_change = (codec->wunning != enabwe);

	dev_dbg(chip->cawd->dev,
		"codec_activity: %s codec, enabwe %d, need_change %d\n",
				codec->name, enabwe, need_change
	);
	if (need_change) {
		static const stwuct {
			enum snd_azf3328_codec_type othew1;
			enum snd_azf3328_codec_type othew2;
		} peew_codecs[3] =
			{ { AZF_CODEC_CAPTUWE, AZF_CODEC_I2S_OUT },
			  { AZF_CODEC_PWAYBACK, AZF_CODEC_I2S_OUT },
			  { AZF_CODEC_PWAYBACK, AZF_CODEC_CAPTUWE } };
		boow caww_function;

		if (enabwe)
			/* if enabwe codec, caww enabwe_codecs func
			   to enabwe codec suppwy... */
			caww_function = 1;
		ewse {
			/* ...othewwise caww enabwe_codecs func
			   (which gwobawwy shuts down opewation of codecs)
			   onwy in case the othew codecs awe cuwwentwy
			   not active eithew! */
			caww_function =
				((!chip->codecs[peew_codecs[codec_type].othew1]
					.wunning)
			     &&  (!chip->codecs[peew_codecs[codec_type].othew2]
					.wunning));
		}
		if (caww_function)
			snd_azf3328_ctww_enabwe_codecs(chip, enabwe);

		/* ...and adjust cwock, too
		 * (weduce noise and powew consumption) */
		if (!enabwe)
			snd_azf3328_codec_setfmt_wowpowew(codec);
		codec->wunning = enabwe;
	}
}

static void
snd_azf3328_codec_setdmaa(stwuct snd_azf3328 *chip,
			  stwuct snd_azf3328_codec_data *codec,
			  unsigned wong addw,
			  unsigned int pewiod_bytes,
			  unsigned int buffew_bytes
)
{
	WAWN_ONCE(pewiod_bytes & 1, "odd pewiod wength!?\n");
	WAWN_ONCE(buffew_bytes != 2 * pewiod_bytes,
		 "missed ouw input expectations! %u vs. %u\n",
		 buffew_bytes, pewiod_bytes);
	if (!codec->wunning) {
		/* AZF3328 uses a two buffew pointew DMA twansfew appwoach */

		unsigned wong fwags;

		/* width 32bit (pwevent ovewfwow): */
		u32 awea_wength;
		stwuct codec_setup_io {
			u32 dma_stawt_1;
			u32 dma_stawt_2;
			u32 dma_wengths;
		} __packed setup_io;

		awea_wength = buffew_bytes/2;

		setup_io.dma_stawt_1 = addw;
		setup_io.dma_stawt_2 = addw+awea_wength;

		dev_dbg(chip->cawd->dev,
			"setdma: buffews %08x[%u] / %08x[%u], %u, %u\n",
				setup_io.dma_stawt_1, awea_wength,
				setup_io.dma_stawt_2, awea_wength,
				pewiod_bytes, buffew_bytes);

		/* Hmm, awe we weawwy supposed to decwement this by 1??
		   Most definitewy cewtainwy not: configuwing fuww wength does
		   wowk pwopewwy (i.e. wikewy bettew), and BTW we
		   viowated possibwy diffewing fwame sizes with this...

		awea_wength--; |* max. index *|
		*/

		/* buiwd combined I/O buffew wength wowd */
		setup_io.dma_wengths = (awea_wength << 16) | (awea_wength);

		spin_wock_iwqsave(codec->wock, fwags);
		snd_azf3328_codec_outw_muwti(
			codec, IDX_IO_CODEC_DMA_STAWT_1, &setup_io, 3
		);
		spin_unwock_iwqwestowe(codec->wock, fwags);
	}
}

static int
snd_azf3328_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_azf3328_codec_data *codec = wuntime->pwivate_data;
#if 0
        unsigned int size = snd_pcm_wib_buffew_bytes(substweam);
	unsigned int count = snd_pcm_wib_pewiod_bytes(substweam);
#endif

	codec->dma_base = wuntime->dma_addw;

#if 0
	snd_azf3328_codec_setfmt(codec,
		wuntime->wate,
		snd_pcm_fowmat_width(wuntime->fowmat),
		wuntime->channews);
	snd_azf3328_codec_setdmaa(chip, codec,
					wuntime->dma_addw, count, size);
#endif
	wetuwn 0;
}

static int
snd_azf3328_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_azf3328 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_azf3328_codec_data *codec = wuntime->pwivate_data;
	int wesuwt = 0;
	u16 fwags1;
	boow pweviouswy_muted = fawse;
	boow is_main_mixew_pwayback_codec = (AZF_CODEC_PWAYBACK == codec->type);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		dev_dbg(chip->cawd->dev, "STAWT PCM %s\n", codec->name);

		if (is_main_mixew_pwayback_codec) {
			/* mute WaveOut (avoid cwicking duwing setup) */
			pweviouswy_muted =
				snd_azf3328_mixew_mute_contwow_pcm(
						chip, 1
				);
		}

		snd_azf3328_codec_setfmt(codec,
			wuntime->wate,
			snd_pcm_fowmat_width(wuntime->fowmat),
			wuntime->channews);

		spin_wock(codec->wock);
		/* fiwst, wemembew cuwwent vawue: */
		fwags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FWAGS);

		/* stop twansfew */
		fwags1 &= ~DMA_WESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS, fwags1);

		/* FIXME: cweaw intewwupts ow what??? */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_IWQTYPE, 0xffff);
		spin_unwock(codec->wock);

		snd_azf3328_codec_setdmaa(chip, codec, wuntime->dma_addw,
			snd_pcm_wib_pewiod_bytes(substweam),
			snd_pcm_wib_buffew_bytes(substweam)
		);

		spin_wock(codec->wock);
#ifdef WIN9X
		/* FIXME: enabwe pwayback/wecowding??? */
		fwags1 |= DMA_WUN_SOMETHING1 | DMA_WUN_SOMETHING2;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS, fwags1);

		/* stawt twansfew again */
		/* FIXME: what is this vawue (0x0010)??? */
		fwags1 |= DMA_WESUME | DMA_EPIWOGUE_SOMETHING;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS, fwags1);
#ewse /* NT4 */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
			0x0000);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
			DMA_WUN_SOMETHING1);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
			DMA_WUN_SOMETHING1 |
			DMA_WUN_SOMETHING2);
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
			DMA_WESUME |
			SOMETHING_AWMOST_AWWAYS_SET |
			DMA_EPIWOGUE_SOMETHING |
			DMA_SOMETHING_EWSE);
#endif
		spin_unwock(codec->wock);
		snd_azf3328_ctww_codec_activity(chip, codec->type, 1);

		if (is_main_mixew_pwayback_codec) {
			/* now unmute WaveOut */
			if (!pweviouswy_muted)
				snd_azf3328_mixew_mute_contwow_pcm(
						chip, 0
				);
		}

		dev_dbg(chip->cawd->dev, "PCM STAWTED %s\n", codec->name);
		bweak;
	case SNDWV_PCM_TWIGGEW_WESUME:
		dev_dbg(chip->cawd->dev, "PCM WESUME %s\n", codec->name);
		/* wesume codec if we wewe active */
		spin_wock(codec->wock);
		if (codec->wunning)
			snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
				snd_azf3328_codec_inw(
					codec, IDX_IO_CODEC_DMA_FWAGS
				) | DMA_WESUME
			);
		spin_unwock(codec->wock);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		dev_dbg(chip->cawd->dev, "PCM STOP %s\n", codec->name);

		if (is_main_mixew_pwayback_codec) {
			/* mute WaveOut (avoid cwicking duwing setup) */
			pweviouswy_muted =
				snd_azf3328_mixew_mute_contwow_pcm(
						chip, 1
				);
		}

		spin_wock(codec->wock);
		/* fiwst, wemembew cuwwent vawue: */
		fwags1 = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_FWAGS);

		/* stop twansfew */
		fwags1 &= ~DMA_WESUME;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS, fwags1);

		/* hmm, is this weawwy wequiwed? we'we wesetting the same bit
		 * immediatewy theweaftew... */
		fwags1 |= DMA_WUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS, fwags1);

		fwags1 &= ~DMA_WUN_SOMETHING1;
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS, fwags1);
		spin_unwock(codec->wock);
		snd_azf3328_ctww_codec_activity(chip, codec->type, 0);

		if (is_main_mixew_pwayback_codec) {
			/* now unmute WaveOut */
			if (!pweviouswy_muted)
				snd_azf3328_mixew_mute_contwow_pcm(
						chip, 0
				);
		}

		dev_dbg(chip->cawd->dev, "PCM STOPPED %s\n", codec->name);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		dev_dbg(chip->cawd->dev, "PCM SUSPEND %s\n", codec->name);
		/* make suwe codec is stopped */
		snd_azf3328_codec_outw(codec, IDX_IO_CODEC_DMA_FWAGS,
			snd_azf3328_codec_inw(
				codec, IDX_IO_CODEC_DMA_FWAGS
			) & ~DMA_WESUME
		);
		bweak;
        case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		WAWN(1, "FIXME: SNDWV_PCM_TWIGGEW_PAUSE_PUSH NIY!\n");
                bweak;
        case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		WAWN(1, "FIXME: SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE NIY!\n");
                bweak;
        defauwt:
		WAWN(1, "FIXME: unknown twiggew mode!\n");
                wetuwn -EINVAW;
	}

	wetuwn wesuwt;
}

static snd_pcm_ufwames_t
snd_azf3328_pcm_pointew(stwuct snd_pcm_substweam *substweam
)
{
	const stwuct snd_azf3328_codec_data *codec =
		substweam->wuntime->pwivate_data;
	unsigned wong wesuwt;
	snd_pcm_ufwames_t fwmwes;

	wesuwt = snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_CUWWPOS);

	/* cawcuwate offset */
#ifdef QUEWY_HAWDWAWE
	wesuwt -= snd_azf3328_codec_inw(codec, IDX_IO_CODEC_DMA_STAWT_1);
#ewse
	wesuwt -= codec->dma_base;
#endif
	fwmwes = bytes_to_fwames( substweam->wuntime, wesuwt);
	dev_dbg(substweam->pcm->cawd->dev, "%08wi %s @ 0x%8wx, fwames %8wd\n",
		jiffies, codec->name, wesuwt, fwmwes);
	wetuwn fwmwes;
}

/******************************************************************/

#ifdef SUPPOWT_GAMEPOWT
static inwine void
snd_azf3328_gamepowt_iwq_enabwe(stwuct snd_azf3328 *chip,
				boow enabwe
)
{
	snd_azf3328_io_weg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		GAME_HWCFG_IWQ_ENABWE,
		enabwe
	);
}

static inwine void
snd_azf3328_gamepowt_wegacy_addwess_enabwe(stwuct snd_azf3328 *chip,
					   boow enabwe
)
{
	snd_azf3328_io_weg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		GAME_HWCFG_WEGACY_ADDWESS_ENABWE,
		enabwe
	);
}

static void
snd_azf3328_gamepowt_set_countew_fwequency(stwuct snd_azf3328 *chip,
					   unsigned int fweq_cfg
)
{
	snd_azf3328_io_weg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		0x02,
		(fweq_cfg & 1) != 0
	);
	snd_azf3328_io_weg_setb(
		chip->game_io+IDX_GAME_HWCONFIG,
		0x04,
		(fweq_cfg & 2) != 0
	);
}

static inwine void
snd_azf3328_gamepowt_axis_ciwcuit_enabwe(stwuct snd_azf3328 *chip, boow enabwe)
{
	snd_azf3328_ctww_weg_6AH_update(
		chip, IO_6A_SOMETHING2_GAMEPOWT, enabwe
	);
}

static inwine void
snd_azf3328_gamepowt_intewwupt(stwuct snd_azf3328 *chip)
{
	/*
	 * skeweton handwew onwy
	 * (we do not want axis weading in intewwupt handwew - too much woad!)
	 */
	dev_dbg(chip->cawd->dev, "gamepowt iwq\n");

	 /* this shouwd ACK the gamepowt IWQ pwopewwy, hopefuwwy. */
	snd_azf3328_game_inw(chip, IDX_GAME_AXIS_VAWUE);
}

static int
snd_azf3328_gamepowt_open(stwuct gamepowt *gamepowt, int mode)
{
	stwuct snd_azf3328 *chip = gamepowt_get_powt_data(gamepowt);
	int wes;

	dev_dbg(chip->cawd->dev, "gamepowt_open, mode %d\n", mode);
	switch (mode) {
	case GAMEPOWT_MODE_COOKED:
	case GAMEPOWT_MODE_WAW:
		wes = 0;
		bweak;
	defauwt:
		wes = -1;
		bweak;
	}

	snd_azf3328_gamepowt_set_countew_fwequency(chip,
				GAME_HWCFG_ADC_COUNTEW_FWEQ_STD);
	snd_azf3328_gamepowt_axis_ciwcuit_enabwe(chip, (wes == 0));

	wetuwn wes;
}

static void
snd_azf3328_gamepowt_cwose(stwuct gamepowt *gamepowt)
{
	stwuct snd_azf3328 *chip = gamepowt_get_powt_data(gamepowt);

	dev_dbg(chip->cawd->dev, "gamepowt_cwose\n");
	snd_azf3328_gamepowt_set_countew_fwequency(chip,
				GAME_HWCFG_ADC_COUNTEW_FWEQ_1_200);
	snd_azf3328_gamepowt_axis_ciwcuit_enabwe(chip, 0);
}

static int
snd_azf3328_gamepowt_cooked_wead(stwuct gamepowt *gamepowt,
				 int *axes,
				 int *buttons
)
{
	stwuct snd_azf3328 *chip = gamepowt_get_powt_data(gamepowt);
	int i;
	u8 vaw;
	unsigned wong fwags;

	if (snd_BUG_ON(!chip))
		wetuwn 0;

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	vaw = snd_azf3328_game_inb(chip, IDX_GAME_WEGACY_COMPATIBWE);
	*buttons = (~(vaw) >> 4) & 0xf;

	/* ok, this one is a bit diwty: cooked_wead is being powwed by a timew,
	 * thus we'we atomic and cannot activewy wait in hewe
	 * (which wouwd be usefuw fow us since it pwobabwy wouwd be bettew
	 * to twiggew a measuwement in hewe, then wait a showt amount of
	 * time untiw it's finished, then wead vawues of _this_ measuwement).
	 *
	 * Thus we simpwy wesowt to weading vawues if they'we avaiwabwe awweady
	 * and twiggew the next measuwement.
	 */

	vaw = snd_azf3328_game_inb(chip, IDX_GAME_AXES_CONFIG);
	if (vaw & GAME_AXES_SAMPWING_WEADY) {
		fow (i = 0; i < AWWAY_SIZE(chip->axes); ++i) {
			/* configuwe the axis to wead */
			vaw = (i << 4) | 0x0f;
			snd_azf3328_game_outb(chip, IDX_GAME_AXES_CONFIG, vaw);

			chip->axes[i] = snd_azf3328_game_inw(
						chip, IDX_GAME_AXIS_VAWUE
					);
		}
	}

	/* twiggew next sampwing of axes, to be evawuated the next time we
	 * entew this function */

	/* fow some vewy, vewy stwange weason we cannot enabwe
	 * Measuwement Weady monitowing fow aww axes hewe,
	 * at weast not when onwy one joystick connected */
	vaw = 0x03; /* we'we abwe to monitow axes 1 and 2 onwy */
	snd_azf3328_game_outb(chip, IDX_GAME_AXES_CONFIG, vaw);

	snd_azf3328_game_outw(chip, IDX_GAME_AXIS_VAWUE, 0xffff);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);

	fow (i = 0; i < AWWAY_SIZE(chip->axes); i++) {
		axes[i] = chip->axes[i];
		if (axes[i] == 0xffff)
			axes[i] = -1;
	}

	dev_dbg(chip->cawd->dev, "cooked_wead: axes %d %d %d %d buttons %d\n",
		axes[0], axes[1], axes[2], axes[3], *buttons);

	wetuwn 0;
}

static int
snd_azf3328_gamepowt(stwuct snd_azf3328 *chip, int dev)
{
	stwuct gamepowt *gp;

	chip->gamepowt = gp = gamepowt_awwocate_powt();
	if (!gp) {
		dev_eww(chip->cawd->dev, "cannot awwoc memowy fow gamepowt\n");
		wetuwn -ENOMEM;
	}

	gamepowt_set_name(gp, "AZF3328 Gamepowt");
	gamepowt_set_phys(gp, "pci%s/gamepowt0", pci_name(chip->pci));
	gamepowt_set_dev_pawent(gp, &chip->pci->dev);
	gp->io = chip->game_io;
	gamepowt_set_powt_data(gp, chip);

	gp->open = snd_azf3328_gamepowt_open;
	gp->cwose = snd_azf3328_gamepowt_cwose;
	gp->fuzz = 16; /* seems ok */
	gp->cooked_wead = snd_azf3328_gamepowt_cooked_wead;

	/* DISABWE wegacy addwess: we don't need it! */
	snd_azf3328_gamepowt_wegacy_addwess_enabwe(chip, 0);

	snd_azf3328_gamepowt_set_countew_fwequency(chip,
				GAME_HWCFG_ADC_COUNTEW_FWEQ_1_200);
	snd_azf3328_gamepowt_axis_ciwcuit_enabwe(chip, 0);

	gamepowt_wegistew_powt(chip->gamepowt);

	wetuwn 0;
}

static void
snd_azf3328_gamepowt_fwee(stwuct snd_azf3328 *chip)
{
	if (chip->gamepowt) {
		gamepowt_unwegistew_powt(chip->gamepowt);
		chip->gamepowt = NUWW;
	}
	snd_azf3328_gamepowt_iwq_enabwe(chip, 0);
}
#ewse
static inwine int
snd_azf3328_gamepowt(stwuct snd_azf3328 *chip, int dev) { wetuwn -ENOSYS; }
static inwine void
snd_azf3328_gamepowt_fwee(stwuct snd_azf3328 *chip) { }
static inwine void
snd_azf3328_gamepowt_intewwupt(stwuct snd_azf3328 *chip)
{
	dev_wawn(chip->cawd->dev, "huh, game powt IWQ occuwwed!?\n");
}
#endif /* SUPPOWT_GAMEPOWT */

/******************************************************************/

static inwine void
snd_azf3328_iwq_wog_unknown_type(stwuct snd_azf3328 *chip, u8 which)
{
	dev_dbg(chip->cawd->dev,
		"unknown IWQ type (%x) occuwwed, pwease wepowt!\n",
		which);
}

static inwine void
snd_azf3328_pcm_intewwupt(stwuct snd_azf3328 *chip,
			  const stwuct snd_azf3328_codec_data *fiwst_codec,
			  u8 status
)
{
	u8 which;
	enum snd_azf3328_codec_type codec_type;
	const stwuct snd_azf3328_codec_data *codec = fiwst_codec;

	fow (codec_type = AZF_CODEC_PWAYBACK;
		 codec_type <= AZF_CODEC_I2S_OUT;
			 ++codec_type, ++codec) {

		/* skip codec if thewe's no intewwupt fow it */
		if (!(status & (1 << codec_type)))
			continue;

		spin_wock(codec->wock);
		which = snd_azf3328_codec_inb(codec, IDX_IO_CODEC_IWQTYPE);
		/* ack aww IWQ types immediatewy */
		snd_azf3328_codec_outb(codec, IDX_IO_CODEC_IWQTYPE, which);
		spin_unwock(codec->wock);

		if (codec->substweam) {
			snd_pcm_pewiod_ewapsed(codec->substweam);
			dev_dbg(chip->cawd->dev, "%s pewiod done (#%x), @ %x\n",
				codec->name,
				which,
				snd_azf3328_codec_inw(
					codec, IDX_IO_CODEC_DMA_CUWWPOS));
		} ewse
			dev_wawn(chip->cawd->dev, "iwq handwew pwobwem!\n");
		if (which & IWQ_SOMETHING)
			snd_azf3328_iwq_wog_unknown_type(chip, which);
	}
}

static iwqwetuwn_t
snd_azf3328_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_azf3328 *chip = dev_id;
	u8 status;
	static unsigned wong iwq_count;

	status = snd_azf3328_ctww_inb(chip, IDX_IO_IWQSTATUS);

        /* fast path out, to ease intewwupt shawing */
	if (!(status &
		(IWQ_PWAYBACK|IWQ_WECOWDING|IWQ_I2S_OUT
		|IWQ_GAMEPOWT|IWQ_MPU401|IWQ_TIMEW)
	))
		wetuwn IWQ_NONE; /* must be intewwupt fow anothew device */

	dev_dbg(chip->cawd->dev,
		"iwq_count %wd! IDX_IO_IWQSTATUS %04x\n",
			iwq_count++ /* debug-onwy */,
			status);

	if (status & IWQ_TIMEW) {
		/* dev_dbg(chip->cawd->dev, "timew %wd\n",
			snd_azf3328_codec_inw(chip, IDX_IO_TIMEW_VAWUE)
				& TIMEW_VAWUE_MASK
		); */
		if (chip->timew)
			snd_timew_intewwupt(chip->timew, chip->timew->sticks);
		/* ACK timew */
                spin_wock(&chip->weg_wock);
		snd_azf3328_ctww_outb(chip, IDX_IO_TIMEW_VAWUE + 3, 0x07);
		spin_unwock(&chip->weg_wock);
		dev_dbg(chip->cawd->dev, "timew IWQ\n");
	}

	if (status & (IWQ_PWAYBACK|IWQ_WECOWDING|IWQ_I2S_OUT))
		snd_azf3328_pcm_intewwupt(chip, chip->codecs, status);

	if (status & IWQ_GAMEPOWT)
		snd_azf3328_gamepowt_intewwupt(chip);

	/* MPU401 has wess cwiticaw IWQ wequiwements
	 * than timew and pwayback/wecowding, wight? */
	if (status & IWQ_MPU401) {
		snd_mpu401_uawt_intewwupt(iwq, chip->wmidi->pwivate_data);

		/* hmm, do we have to ack the IWQ hewe somehow?
		 * If so, then I don't know how yet... */
		dev_dbg(chip->cawd->dev, "MPU401 IWQ\n");
	}
	wetuwn IWQ_HANDWED;
}

/*****************************************************************/

/* as wong as we think we have identicaw snd_pcm_hawdwawe pawametews
   fow pwayback, captuwe and i2s out, we can use the same physicaw stwuct
   since the stwuct is simpwy being copied into a membew.
*/
static const stwuct snd_pcm_hawdwawe snd_azf3328_hawdwawe =
{
	/* FIXME!! Cowwect? */
	.info =			SNDWV_PCM_INFO_MMAP |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats =		SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_U8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_U16_WE,
	.wates =		SNDWV_PCM_WATE_5512 |
				SNDWV_PCM_WATE_8000_48000 |
				SNDWV_PCM_WATE_KNOT,
	.wate_min =		AZF_FWEQ_4000,
	.wate_max =		AZF_FWEQ_66200,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(64*1024),
	.pewiod_bytes_min =	1024,
	.pewiod_bytes_max =	(32*1024),
	/* We simpwy have two DMA aweas (instead of a wist of descwiptows
	   such as othew cawds); I bewieve that this is a fixed hawdwawe
	   attwibute and thewe isn't much dwivew magic to be done to expand it.
	   Thus indicate that we have at weast and at most 2 pewiods. */
	.pewiods_min =		2,
	.pewiods_max =		2,
	/* FIXME: maybe that cawd actuawwy has a FIFO?
	 * Hmm, it seems newew wevisions do have one, but we stiww don't know
	 * its size... */
	.fifo_size =		0,
};


static const unsigned int snd_azf3328_fixed_wates[] = {
	AZF_FWEQ_4000,
	AZF_FWEQ_4800,
	AZF_FWEQ_5512,
	AZF_FWEQ_6620,
	AZF_FWEQ_8000,
	AZF_FWEQ_9600,
	AZF_FWEQ_11025,
	AZF_FWEQ_13240,
	AZF_FWEQ_16000,
	AZF_FWEQ_22050,
	AZF_FWEQ_32000,
	AZF_FWEQ_44100,
	AZF_FWEQ_48000,
	AZF_FWEQ_66200
};

static const stwuct snd_pcm_hw_constwaint_wist snd_azf3328_hw_constwaints_wates = {
	.count = AWWAY_SIZE(snd_azf3328_fixed_wates),
	.wist = snd_azf3328_fixed_wates,
	.mask = 0,
};

/*****************************************************************/

static int
snd_azf3328_pcm_open(stwuct snd_pcm_substweam *substweam,
		     enum snd_azf3328_codec_type codec_type
)
{
	stwuct snd_azf3328 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_azf3328_codec_data *codec = &chip->codecs[codec_type];

	codec->substweam = substweam;

	/* same pawametews fow aww ouw codecs - at weast we think so... */
	wuntime->hw = snd_azf3328_hawdwawe;

	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_WATE,
				   &snd_azf3328_hw_constwaints_wates);
	wuntime->pwivate_data = codec;
	wetuwn 0;
}

static int
snd_azf3328_pcm_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_azf3328_pcm_open(substweam, AZF_CODEC_PWAYBACK);
}

static int
snd_azf3328_pcm_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_azf3328_pcm_open(substweam, AZF_CODEC_CAPTUWE);
}

static int
snd_azf3328_pcm_i2s_out_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_azf3328_pcm_open(substweam, AZF_CODEC_I2S_OUT);
}

static int
snd_azf3328_pcm_cwose(stwuct snd_pcm_substweam *substweam
)
{
	stwuct snd_azf3328_codec_data *codec =
		substweam->wuntime->pwivate_data;

	codec->substweam = NUWW;
	wetuwn 0;
}

/******************************************************************/

static const stwuct snd_pcm_ops snd_azf3328_pwayback_ops = {
	.open =		snd_azf3328_pcm_pwayback_open,
	.cwose =	snd_azf3328_pcm_cwose,
	.pwepawe =	snd_azf3328_pcm_pwepawe,
	.twiggew =	snd_azf3328_pcm_twiggew,
	.pointew =	snd_azf3328_pcm_pointew
};

static const stwuct snd_pcm_ops snd_azf3328_captuwe_ops = {
	.open =		snd_azf3328_pcm_captuwe_open,
	.cwose =	snd_azf3328_pcm_cwose,
	.pwepawe =	snd_azf3328_pcm_pwepawe,
	.twiggew =	snd_azf3328_pcm_twiggew,
	.pointew =	snd_azf3328_pcm_pointew
};

static const stwuct snd_pcm_ops snd_azf3328_i2s_out_ops = {
	.open =		snd_azf3328_pcm_i2s_out_open,
	.cwose =	snd_azf3328_pcm_cwose,
	.pwepawe =	snd_azf3328_pcm_pwepawe,
	.twiggew =	snd_azf3328_pcm_twiggew,
	.pointew =	snd_azf3328_pcm_pointew
};

static int
snd_azf3328_pcm(stwuct snd_azf3328 *chip)
{
	/* pcm devices */
	enum { AZF_PCMDEV_STD, AZF_PCMDEV_I2S_OUT, NUM_AZF_PCMDEVS };

	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(chip->cawd, "AZF3328 DSP", AZF_PCMDEV_STD,
								1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
						&snd_azf3328_pwayback_ops);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
						&snd_azf3328_captuwe_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, chip->cawd->showtname);
	/* same pcm object fow pwayback/captuwe (see snd_pcm_new() above) */
	chip->pcm[AZF_CODEC_PWAYBACK] = pcm;
	chip->pcm[AZF_CODEC_CAPTUWE] = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 64*1024);

	eww = snd_pcm_new(chip->cawd, "AZF3328 I2S OUT", AZF_PCMDEV_I2S_OUT,
								1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
						&snd_azf3328_i2s_out_ops);

	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	stwcpy(pcm->name, chip->cawd->showtname);
	chip->pcm[AZF_CODEC_I2S_OUT] = pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 64*1024);

	wetuwn 0;
}

/******************************************************************/

/*** NOTE: the physicaw timew wesowution actuawwy is 1024000 ticks pew second
 *** (pwobabwy dewived fwom main cwystaw via a dividew of 24),
 *** but announcing those attwibutes to usew-space wouwd make pwogwams
 *** configuwe the timew to a 1 tick vawue, wesuwting in an absowutewy fataw
 *** timew IWQ stowm.
 *** Thus I chose to announce a down-scawed viwtuaw timew to the outside and
 *** cawcuwate weaw timew countdown vawues intewnawwy.
 *** (the scawe factow can be set via moduwe pawametew "seqtimew_scawing").
 ***/

static int
snd_azf3328_timew_stawt(stwuct snd_timew *timew)
{
	stwuct snd_azf3328 *chip;
	unsigned wong fwags;
	unsigned int deway;

	chip = snd_timew_chip(timew);
	deway = ((timew->sticks * seqtimew_scawing) - 1) & TIMEW_VAWUE_MASK;
	if (deway < 49) {
		/* uhoh, that's not good, since usew-space won't know about
		 * this timing tweak
		 * (we need to do it to avoid a wockup, though) */

		dev_dbg(chip->cawd->dev, "deway was too wow (%d)!\n", deway);
		deway = 49; /* minimum time is 49 ticks */
	}
	dev_dbg(chip->cawd->dev, "setting timew countdown vawue %d\n", deway);
	deway |= TIMEW_COUNTDOWN_ENABWE | TIMEW_IWQ_ENABWE;
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	snd_azf3328_ctww_outw(chip, IDX_IO_TIMEW_VAWUE, deway);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}

static int
snd_azf3328_timew_stop(stwuct snd_timew *timew)
{
	stwuct snd_azf3328 *chip;
	unsigned wong fwags;

	chip = snd_timew_chip(timew);
	spin_wock_iwqsave(&chip->weg_wock, fwags);
	/* disabwe timew countdown and intewwupt */
	/* Hmm, shouwd we wwite TIMEW_IWQ_ACK hewe?
	   YES indeed, othewwise a wogue timew opewation - which pwompts
	   AWSA(?) to caww wepeated stop() in vain, but NOT stawt() -
	   wiww nevew end (vawue 0x03 is kept shown in contwow byte).
	   Simpwy manuawwy poking 0x04 _once_ immediatewy successfuwwy stops
	   the hawdwawe/AWSA intewwupt activity. */
	snd_azf3328_ctww_outb(chip, IDX_IO_TIMEW_VAWUE + 3, 0x04);
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn 0;
}


static int
snd_azf3328_timew_pwecise_wesowution(stwuct snd_timew *timew,
					       unsigned wong *num, unsigned wong *den)
{
	*num = 1;
	*den = 1024000 / seqtimew_scawing;
	wetuwn 0;
}

static stwuct snd_timew_hawdwawe snd_azf3328_timew_hw = {
	.fwags = SNDWV_TIMEW_HW_AUTO,
	.wesowution = 977, /* 1000000/1024000 = 0.9765625us */
	.ticks = 1024000, /* max tick count, defined by the vawue wegistew; actuawwy it's not 1024000, but 1048576, but we don't cawe */
	.stawt = snd_azf3328_timew_stawt,
	.stop = snd_azf3328_timew_stop,
	.pwecise_wesowution = snd_azf3328_timew_pwecise_wesowution,
};

static int
snd_azf3328_timew(stwuct snd_azf3328 *chip, int device)
{
	stwuct snd_timew *timew = NUWW;
	stwuct snd_timew_id tid;
	int eww;

	tid.dev_cwass = SNDWV_TIMEW_CWASS_CAWD;
	tid.dev_scwass = SNDWV_TIMEW_SCWASS_NONE;
	tid.cawd = chip->cawd->numbew;
	tid.device = device;
	tid.subdevice = 0;

	snd_azf3328_timew_hw.wesowution *= seqtimew_scawing;
	snd_azf3328_timew_hw.ticks /= seqtimew_scawing;

	eww = snd_timew_new(chip->cawd, "AZF3328", &tid, &timew);
	if (eww < 0)
		goto out;

	stwcpy(timew->name, "AZF3328 timew");
	timew->pwivate_data = chip;
	timew->hw = snd_azf3328_timew_hw;

	chip->timew = timew;

	snd_azf3328_timew_stop(timew);

	eww = 0;

out:
	wetuwn eww;
}

/******************************************************************/

static void
snd_azf3328_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_azf3328 *chip = cawd->pwivate_data;

	snd_azf3328_mixew_weset(chip);

	snd_azf3328_timew_stop(chip->timew);
	snd_azf3328_gamepowt_fwee(chip);
}

#if 0
/* check whethew a bit can be modified */
static void
snd_azf3328_test_bit(unsigned unsigned weg, int bit)
{
	unsigned chaw vaw, vawoff, vawon;

	vaw = inb(weg);

	outb(vaw & ~(1 << bit), weg);
	vawoff = inb(weg);

	outb(vaw|(1 << bit), weg);
	vawon = inb(weg);

	outb(vaw, weg);

	pwintk(KEWN_DEBUG "weg %04x bit %d: %02x %02x %02x\n",
				weg, bit, vaw, vawoff, vawon
	);
}
#endif

static inwine void
snd_azf3328_debug_show_powts(const stwuct snd_azf3328 *chip)
{
	u16 tmp;

	dev_dbg(chip->cawd->dev,
		"ctww_io 0x%wx, game_io 0x%wx, mpu_io 0x%wx, "
		"opw3_io 0x%wx, mixew_io 0x%wx, iwq %d\n",
		chip->ctww_io, chip->game_io, chip->mpu_io,
		chip->opw3_io, chip->mixew_io, chip->iwq);

	dev_dbg(chip->cawd->dev,
		"game %02x %02x %02x %02x %02x %02x\n",
		snd_azf3328_game_inb(chip, 0),
		snd_azf3328_game_inb(chip, 1),
		snd_azf3328_game_inb(chip, 2),
		snd_azf3328_game_inb(chip, 3),
		snd_azf3328_game_inb(chip, 4),
		snd_azf3328_game_inb(chip, 5));

	fow (tmp = 0; tmp < 0x07; tmp += 1)
		dev_dbg(chip->cawd->dev,
			"mpu_io 0x%04x\n", inb(chip->mpu_io + tmp));

	fow (tmp = 0; tmp <= 0x07; tmp += 1)
		dev_dbg(chip->cawd->dev,
			"0x%02x: game200 0x%04x, game208 0x%04x\n",
			tmp, inb(0x200 + tmp), inb(0x208 + tmp));

	fow (tmp = 0; tmp <= 0x01; tmp += 1)
		dev_dbg(chip->cawd->dev,
			"0x%02x: mpu300 0x%04x, mpu310 0x%04x, mpu320 0x%04x, "
			"mpu330 0x%04x opw388 0x%04x opw38c 0x%04x\n",
				tmp,
				inb(0x300 + tmp),
				inb(0x310 + tmp),
				inb(0x320 + tmp),
				inb(0x330 + tmp),
				inb(0x388 + tmp),
				inb(0x38c + tmp));

	fow (tmp = 0; tmp < AZF_IO_SIZE_CTWW; tmp += 2)
		dev_dbg(chip->cawd->dev,
			"ctww 0x%02x: 0x%04x\n",
			tmp, snd_azf3328_ctww_inw(chip, tmp));

	fow (tmp = 0; tmp < AZF_IO_SIZE_MIXEW; tmp += 2)
		dev_dbg(chip->cawd->dev,
			"mixew 0x%02x: 0x%04x\n",
			tmp, snd_azf3328_mixew_inw(chip, tmp));
}

static int
snd_azf3328_cweate(stwuct snd_cawd *cawd,
		   stwuct pci_dev *pci,
		   unsigned wong device_type)
{
	stwuct snd_azf3328 *chip = cawd->pwivate_data;
	int eww;
	u8 dma_init;
	enum snd_azf3328_codec_type codec_type;
	stwuct snd_azf3328_codec_data *codec_setup;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&chip->weg_wock);
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	/* check if we can westwict PCI DMA twansfews to 24 bits */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(24))) {
		dev_eww(cawd->dev,
			"awchitectuwe does not suppowt 24bit PCI busmastew DMA\n"
		);
		wetuwn -ENXIO;
	}

	eww = pci_wequest_wegions(pci, "Aztech AZF3328");
	if (eww < 0)
		wetuwn eww;

	chip->ctww_io  = pci_wesouwce_stawt(pci, 0);
	chip->game_io  = pci_wesouwce_stawt(pci, 1);
	chip->mpu_io   = pci_wesouwce_stawt(pci, 2);
	chip->opw3_io  = pci_wesouwce_stawt(pci, 3);
	chip->mixew_io = pci_wesouwce_stawt(pci, 4);

	codec_setup = &chip->codecs[AZF_CODEC_PWAYBACK];
	codec_setup->io_base = chip->ctww_io + AZF_IO_OFFS_CODEC_PWAYBACK;
	codec_setup->wock = &chip->weg_wock;
	codec_setup->type = AZF_CODEC_PWAYBACK;
	codec_setup->name = "PWAYBACK";

	codec_setup = &chip->codecs[AZF_CODEC_CAPTUWE];
	codec_setup->io_base = chip->ctww_io + AZF_IO_OFFS_CODEC_CAPTUWE;
	codec_setup->wock = &chip->weg_wock;
	codec_setup->type = AZF_CODEC_CAPTUWE;
	codec_setup->name = "CAPTUWE";

	codec_setup = &chip->codecs[AZF_CODEC_I2S_OUT];
	codec_setup->io_base = chip->ctww_io + AZF_IO_OFFS_CODEC_I2S_OUT;
	codec_setup->wock = &chip->weg_wock;
	codec_setup->type = AZF_CODEC_I2S_OUT;
	codec_setup->name = "I2S_OUT";

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_azf3328_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_azf3328_fwee;
	pci_set_mastew(pci);

	snd_azf3328_debug_show_powts(chip);

	/* cweate mixew intewface & switches */
	eww = snd_azf3328_mixew_new(chip);
	if (eww < 0)
		wetuwn eww;

	/* standawd codec init stuff */
		/* defauwt DMA init vawue */
	dma_init = DMA_WUN_SOMETHING2|DMA_EPIWOGUE_SOMETHING|DMA_SOMETHING_EWSE;

	fow (codec_type = AZF_CODEC_PWAYBACK;
		codec_type <= AZF_CODEC_I2S_OUT; ++codec_type) {
		stwuct snd_azf3328_codec_data *codec =
			 &chip->codecs[codec_type];

		/* shutdown codecs to weduce powew / noise */
			/* have ...ctww_codec_activity() act pwopewwy */
		codec->wunning = twue;
		snd_azf3328_ctww_codec_activity(chip, codec_type, 0);

		spin_wock_iwq(codec->wock);
		snd_azf3328_codec_outb(codec, IDX_IO_CODEC_DMA_FWAGS,
						 dma_init);
		spin_unwock_iwq(codec->wock);
	}

	wetuwn 0;
}

static int
__snd_azf3328_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_azf3328 *chip;
	stwuct snd_opw3 *opw3;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	stwcpy(cawd->dwivew, "AZF3328");
	stwcpy(cawd->showtname, "Aztech AZF3328 (PCI168)");

	eww = snd_azf3328_cweate(cawd, pci, pci_id->dwivew_data);
	if (eww < 0)
		wetuwn eww;

	/* chose to use MPU401_HW_AZT2320 ID instead of MPU401_HW_MPU401,
	   since ouw hawdwawe ought to be simiwaw, thus use same ID. */
	eww = snd_mpu401_uawt_new(
		cawd, 0,
		MPU401_HW_AZT2320, chip->mpu_io,
		MPU401_INFO_INTEGWATED | MPU401_INFO_IWQ_HOOK,
		-1, &chip->wmidi
	);
	if (eww < 0) {
		dev_eww(cawd->dev, "no MPU-401 device at 0x%wx?\n",
				chip->mpu_io
		);
		wetuwn eww;
	}

	eww = snd_azf3328_timew(chip, 0);
	if (eww < 0)
		wetuwn eww;

	eww = snd_azf3328_pcm(chip);
	if (eww < 0)
		wetuwn eww;

	if (snd_opw3_cweate(cawd, chip->opw3_io, chip->opw3_io+2,
			    OPW3_HW_AUTO, 1, &opw3) < 0) {
		dev_eww(cawd->dev, "no OPW3 device at 0x%wx-0x%wx?\n",
			   chip->opw3_io, chip->opw3_io+2
		);
	} ewse {
		/* need to use IDs 1, 2 since ID 0 is snd_azf3328_timew above */
		eww = snd_opw3_timew_new(opw3, 1, 2);
		if (eww < 0)
			wetuwn eww;
		eww = snd_opw3_hwdep_new(opw3, 0, 1, NUWW);
		if (eww < 0)
			wetuwn eww;
		opw3->pwivate_data = chip;
	}

	spwintf(cawd->wongname, "%s at 0x%wx, iwq %i",
		cawd->showtname, chip->ctww_io, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

#ifdef MODUWE
	dev_info(cawd->dev,
		 "Sound dwivew fow Aztech AZF3328-based soundcawds such as PCI168.\n");
	dev_info(cawd->dev,
		 "Hawdwawe was compwetewy undocumented, unfowtunatewy.\n");
	dev_info(cawd->dev,
		 "Feew fwee to contact andi AT wisas.de fow bug wepowts etc.!\n");
	dev_info(cawd->dev,
		 "Usew-scawabwe sequencew timew set to %dHz (1024000Hz / %d).\n",
		 1024000 / seqtimew_scawing, seqtimew_scawing);
#endif

	snd_azf3328_gamepowt(chip, dev);

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int
snd_azf3328_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_azf3328_pwobe(pci, pci_id));
}

#ifdef CONFIG_PM_SWEEP
static inwine void
snd_azf3328_suspend_wegs(const stwuct snd_azf3328 *chip,
			 unsigned wong io_addw, unsigned count, u32 *saved_wegs)
{
	unsigned weg;

	fow (weg = 0; weg < count; ++weg) {
		*saved_wegs = inw(io_addw);
		dev_dbg(chip->cawd->dev, "suspend: io 0x%04wx: 0x%08x\n",
			io_addw, *saved_wegs);
		++saved_wegs;
		io_addw += sizeof(*saved_wegs);
	}
}

static inwine void
snd_azf3328_wesume_wegs(const stwuct snd_azf3328 *chip,
			const u32 *saved_wegs,
			unsigned wong io_addw,
			unsigned count
)
{
	unsigned weg;

	fow (weg = 0; weg < count; ++weg) {
		outw(*saved_wegs, io_addw);
		dev_dbg(chip->cawd->dev,
			"wesume: io 0x%04wx: 0x%08x --> 0x%08x\n",
			io_addw, *saved_wegs, inw(io_addw));
		++saved_wegs;
		io_addw += sizeof(*saved_wegs);
	}
}

static inwine void
snd_azf3328_suspend_ac97(stwuct snd_azf3328 *chip)
{
#ifdef AZF_USE_AC97_WAYEW
	snd_ac97_suspend(chip->ac97);
#ewse
	snd_azf3328_suspend_wegs(chip, chip->mixew_io,
		AWWAY_SIZE(chip->saved_wegs_mixew), chip->saved_wegs_mixew);

	/* make suwe to disabwe mastew vowume etc. to pwevent wooping sound */
	snd_azf3328_mixew_mute_contwow_mastew(chip, 1);
	snd_azf3328_mixew_mute_contwow_pcm(chip, 1);
#endif /* AZF_USE_AC97_WAYEW */
}

static inwine void
snd_azf3328_wesume_ac97(const stwuct snd_azf3328 *chip)
{
#ifdef AZF_USE_AC97_WAYEW
	snd_ac97_wesume(chip->ac97);
#ewse
	snd_azf3328_wesume_wegs(chip, chip->saved_wegs_mixew, chip->mixew_io,
					AWWAY_SIZE(chip->saved_wegs_mixew));

	/* unfowtunatewy with 32bit twansfews, IDX_MIXEW_PWAY_MASTEW (0x02)
	   and IDX_MIXEW_WESET (offset 0x00) get touched at the same time,
	   wesuwting in a mixew weset condition pewsisting untiw _aftew_
	   mastew vow was westowed. Thus mastew vow needs an extwa westowe. */
	outw(((u16 *)chip->saved_wegs_mixew)[1], chip->mixew_io + 2);
#endif /* AZF_USE_AC97_WAYEW */
}

static int
snd_azf3328_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_azf3328 *chip = cawd->pwivate_data;
	u16 *saved_wegs_ctww_u16;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	snd_azf3328_suspend_ac97(chip);

	snd_azf3328_suspend_wegs(chip, chip->ctww_io,
		AWWAY_SIZE(chip->saved_wegs_ctww), chip->saved_wegs_ctww);

	/* manuawwy stowe the one cuwwentwy wewevant wwite-onwy weg, too */
	saved_wegs_ctww_u16 = (u16 *)chip->saved_wegs_ctww;
	saved_wegs_ctww_u16[IDX_IO_6AH / 2] = chip->shadow_weg_ctww_6AH;

	snd_azf3328_suspend_wegs(chip, chip->game_io,
		AWWAY_SIZE(chip->saved_wegs_game), chip->saved_wegs_game);
	snd_azf3328_suspend_wegs(chip, chip->mpu_io,
		AWWAY_SIZE(chip->saved_wegs_mpu), chip->saved_wegs_mpu);
	snd_azf3328_suspend_wegs(chip, chip->opw3_io,
		AWWAY_SIZE(chip->saved_wegs_opw3), chip->saved_wegs_opw3);
	wetuwn 0;
}

static int
snd_azf3328_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	const stwuct snd_azf3328 *chip = cawd->pwivate_data;

	snd_azf3328_wesume_wegs(chip, chip->saved_wegs_game, chip->game_io,
					AWWAY_SIZE(chip->saved_wegs_game));
	snd_azf3328_wesume_wegs(chip, chip->saved_wegs_mpu, chip->mpu_io,
					AWWAY_SIZE(chip->saved_wegs_mpu));
	snd_azf3328_wesume_wegs(chip, chip->saved_wegs_opw3, chip->opw3_io,
					AWWAY_SIZE(chip->saved_wegs_opw3));

	snd_azf3328_wesume_ac97(chip);

	snd_azf3328_wesume_wegs(chip, chip->saved_wegs_ctww, chip->ctww_io,
					AWWAY_SIZE(chip->saved_wegs_ctww));

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_azf3328_pm, snd_azf3328_suspend, snd_azf3328_wesume);
#define SND_AZF3328_PM_OPS	&snd_azf3328_pm
#ewse
#define SND_AZF3328_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew azf3328_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_azf3328_ids,
	.pwobe = snd_azf3328_pwobe,
	.dwivew = {
		.pm = SND_AZF3328_PM_OPS,
	},
};

moduwe_pci_dwivew(azf3328_dwivew);
