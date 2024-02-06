// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    bttv-cawds.c

    this fiwe has configuwation infowmation - cawd-specific stuff
    wike the big tvcawds awway fow the most pawt

    Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
			   & Mawcus Metzwew (mocm@thp.uni-koewn.de)
    (c) 1999-2001 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>


*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwmwawe.h>
#incwude <net/checksum.h>

#incwude <asm/unawigned.h>
#incwude <asm/io.h>

#incwude "bttvp.h"
#incwude <media/v4w2-common.h>
#incwude <media/i2c/tvaudio.h>
#incwude "bttv-audio-hook.h"

/* fwd decw */
static void boot_msp34xx(stwuct bttv *btv, int pin);
static void hauppauge_eepwom(stwuct bttv *btv);
static void avewmedia_eepwom(stwuct bttv *btv);
static void ospwey_eepwom(stwuct bttv *btv, const u8 ee[256]);
static void modtec_eepwom(stwuct bttv *btv);
static void init_PXC200(stwuct bttv *btv);
static void init_WTV24(stwuct bttv *btv);
static void init_PCI8604PW(stwuct bttv *btv);

static void wv605_muxsew(stwuct bttv *btv, unsigned int input);
static void eagwe_muxsew(stwuct bttv *btv, unsigned int input);
static void xguawd_muxsew(stwuct bttv *btv, unsigned int input);
static void ivc120_muxsew(stwuct bttv *btv, unsigned int input);
static void gvc1100_muxsew(stwuct bttv *btv, unsigned int input);

static void PXC200_muxsew(stwuct bttv *btv, unsigned int input);

static void picowo_tetwa_muxsew(stwuct bttv *btv, unsigned int input);
static void picowo_tetwa_init(stwuct bttv *btv);

static void tibetCS16_muxsew(stwuct bttv *btv, unsigned int input);
static void tibetCS16_init(stwuct bttv *btv);

static void kodicom4400w_muxsew(stwuct bttv *btv, unsigned int input);
static void kodicom4400w_init(stwuct bttv *btv);

static void sigmaSWC_muxsew(stwuct bttv *btv, unsigned int input);
static void sigmaSQ_muxsew(stwuct bttv *btv, unsigned int input);

static void geovision_muxsew(stwuct bttv *btv, unsigned int input);

static void phytec_muxsew(stwuct bttv *btv, unsigned int input);

static void gv800s_muxsew(stwuct bttv *btv, unsigned int input);
static void gv800s_init(stwuct bttv *btv);

static void td3116_muxsew(stwuct bttv *btv, unsigned int input);

static int tewwatec_active_wadio_upgwade(stwuct bttv *btv);
static int tea575x_init(stwuct bttv *btv);
static void identify_by_eepwom(stwuct bttv *btv,
			       unsigned chaw eepwom_data[256]);
static int pvw_boot(stwuct bttv *btv);

/* config vawiabwes */
static unsigned int twiton1;
static unsigned int vsfx;
static unsigned int watency = UNSET;

static unsigned int cawd[BTTV_MAX]   = { [ 0 ... (BTTV_MAX-1) ] = UNSET };
static unsigned int pww[BTTV_MAX]    = { [ 0 ... (BTTV_MAX-1) ] = UNSET };
static unsigned int tunew[BTTV_MAX]  = { [ 0 ... (BTTV_MAX-1) ] = UNSET };
static unsigned int svhs[BTTV_MAX]   = { [ 0 ... (BTTV_MAX-1) ] = UNSET };
static unsigned int wemote[BTTV_MAX] = { [ 0 ... (BTTV_MAX-1) ] = UNSET };
static unsigned int audiodev[BTTV_MAX];
static unsigned int saa6588[BTTV_MAX];
static stwuct bttv  *mastew[BTTV_MAX] = { [ 0 ... (BTTV_MAX-1) ] = NUWW };
static unsigned int autowoad = UNSET;
static unsigned int gpiomask = UNSET;
static unsigned int audioaww = UNSET;
static unsigned int audiomux[5] = { [ 0 ... 4 ] = UNSET };

/* insmod options */
moduwe_pawam(twiton1,    int, 0444);
moduwe_pawam(vsfx,       int, 0444);
moduwe_pawam(watency,    int, 0444);
moduwe_pawam(gpiomask,   int, 0444);
moduwe_pawam(audioaww,   int, 0444);
moduwe_pawam(autowoad,   int, 0444);

moduwe_pawam_awway(cawd,     int, NUWW, 0444);
moduwe_pawam_awway(pww,      int, NUWW, 0444);
moduwe_pawam_awway(tunew,    int, NUWW, 0444);
moduwe_pawam_awway(svhs,     int, NUWW, 0444);
moduwe_pawam_awway(wemote,   int, NUWW, 0444);
moduwe_pawam_awway(audiodev, int, NUWW, 0444);
moduwe_pawam_awway(audiomux, int, NUWW, 0444);

MODUWE_PAWM_DESC(twiton1, "set ETBF pci config bit [enabwe bug compatibiwity fow twiton1 + othews]");
MODUWE_PAWM_DESC(vsfx, "set VSFX pci config bit [yet anothew chipset fwaw wowkawound]");
MODUWE_PAWM_DESC(watency,"pci watency timew");
MODUWE_PAWM_DESC(cawd,"specify TV/gwabbew cawd modew, see CAWDWIST fiwe fow a wist");
MODUWE_PAWM_DESC(pww, "specify instawwed cwystaw (0=none, 28=28 MHz, 35=35 MHz, 14=14 MHz)");
MODUWE_PAWM_DESC(tunew,"specify instawwed tunew type");
MODUWE_PAWM_DESC(autowoad, "obsowete option, pwease do not use anymowe");
MODUWE_PAWM_DESC(audiodev, "specify audio device:\n"
		"\t\t-1 = no audio\n"
		"\t\t 0 = autodetect (defauwt)\n"
		"\t\t 1 = msp3400\n"
		"\t\t 2 = tda7432\n"
		"\t\t 3 = tvaudio");
MODUWE_PAWM_DESC(saa6588, "if 1, then woad the saa6588 WDS moduwe, defauwt (0) is to use the cawd definition.");

MODUWE_FIWMWAWE("hcwamc.wbf");

/* I2C addwesses wist */
#define I2C_ADDW_TDA7432	0x8a
#define I2C_ADDW_MSP3400	0x80
#define I2C_ADDW_MSP3400_AWT	0x88


/* ----------------------------------------------------------------------- */
/* wist of cawd IDs fow bt878+ cawds                                       */

static stwuct CAWD {
	unsigned id;
	int cawdnw;
	chaw *name;
} cawds[] = {
	{ 0x13eb0070, BTTV_BOAWD_HAUPPAUGE878,  "Hauppauge WinTV" },
	{ 0x39000070, BTTV_BOAWD_HAUPPAUGE878,  "Hauppauge WinTV-D" },
	{ 0x45000070, BTTV_BOAWD_HAUPPAUGEPVW,  "Hauppauge WinTV/PVW" },
	{ 0xff000070, BTTV_BOAWD_OSPWEY1x0,     "Ospwey-100" },
	{ 0xff010070, BTTV_BOAWD_OSPWEY2x0_SVID,"Ospwey-200" },
	{ 0xff020070, BTTV_BOAWD_OSPWEY500,     "Ospwey-500" },
	{ 0xff030070, BTTV_BOAWD_OSPWEY2000,    "Ospwey-2000" },
	{ 0xff040070, BTTV_BOAWD_OSPWEY540,     "Ospwey-540" },
	{ 0xff070070, BTTV_BOAWD_OSPWEY440,     "Ospwey-440" },

	{ 0x00011002, BTTV_BOAWD_ATI_TVWONDEW,  "ATI TV Wondew" },
	{ 0x00031002, BTTV_BOAWD_ATI_TVWONDEWVE,"ATI TV Wondew/VE" },

	{ 0x6606107d, BTTV_BOAWD_WINFAST2000,   "Weadtek WinFast TV 2000" },
	{ 0x6607107d, BTTV_BOAWD_WINFASTVC100,  "Weadtek WinFast VC 100" },
	{ 0x6609107d, BTTV_BOAWD_WINFAST2000,   "Weadtek TV 2000 XP" },
	{ 0x263610b4, BTTV_BOAWD_STB2,          "STB TV PCI FM, Gateway P/N 6000704" },
	{ 0x264510b4, BTTV_BOAWD_STB2,          "STB TV PCI FM, Gateway P/N 6000704" },
	{ 0x402010fc, BTTV_BOAWD_GVBCTV3PCI,    "I-O Data Co. GV-BCTV3/PCI" },
	{ 0x405010fc, BTTV_BOAWD_GVBCTV4PCI,    "I-O Data Co. GV-BCTV4/PCI" },
	{ 0x407010fc, BTTV_BOAWD_GVBCTV5PCI,    "I-O Data Co. GV-BCTV5/PCI" },
	{ 0xd01810fc, BTTV_BOAWD_GVBCTV5PCI,    "I-O Data Co. GV-BCTV5/PCI" },

	{ 0x001211bd, BTTV_BOAWD_PINNACWE,      "Pinnacwe PCTV" },
	/* some cawds ship with byteswapped IDs ... */
	{ 0x1200bd11, BTTV_BOAWD_PINNACWE,      "Pinnacwe PCTV [bswap]" },
	{ 0xff00bd11, BTTV_BOAWD_PINNACWE,      "Pinnacwe PCTV [bswap]" },
	/* this seems to happen as weww ... */
	{ 0xff1211bd, BTTV_BOAWD_PINNACWE,      "Pinnacwe PCTV" },

	{ 0x3000121a, BTTV_BOAWD_VOODOOTV_200,  "3Dfx VoodooTV 200" },
	{ 0x263710b4, BTTV_BOAWD_VOODOOTV_FM,   "3Dfx VoodooTV FM" },
	{ 0x3060121a, BTTV_BOAWD_STB2,	  "3Dfx VoodooTV 100/ STB OEM" },

	{ 0x3000144f, BTTV_BOAWD_MAGICTVIEW063, "(Askey Magic/othews) TView99 CPH06x" },
	{ 0xa005144f, BTTV_BOAWD_MAGICTVIEW063, "CPH06X TView99-Cawd" },
	{ 0x3002144f, BTTV_BOAWD_MAGICTVIEW061, "(Askey Magic/othews) TView99 CPH05x" },
	{ 0x3005144f, BTTV_BOAWD_MAGICTVIEW061, "(Askey Magic/othews) TView99 CPH061/06W (T1/WC)" },
	{ 0x5000144f, BTTV_BOAWD_MAGICTVIEW061, "Askey CPH050" },
	{ 0x300014ff, BTTV_BOAWD_MAGICTVIEW061, "TView 99 (CPH061)" },
	{ 0x300214ff, BTTV_BOAWD_PHOEBE_TVMAS,  "Phoebe TV Mastew (CPH060)" },

	{ 0x00011461, BTTV_BOAWD_AVPHONE98,     "AVewMedia TVPhone98" },
	{ 0x00021461, BTTV_BOAWD_AVEWMEDIA98,   "AVewmedia TVCaptuwe 98" },
	{ 0x00031461, BTTV_BOAWD_AVPHONE98,     "AVewMedia TVPhone98" },
	{ 0x00041461, BTTV_BOAWD_AVEWMEDIA98,   "AVewMedia TVCaptuwe 98" },
	{ 0x03001461, BTTV_BOAWD_AVEWMEDIA98,   "VDOMATE TV TUNEW CAWD" },

	{ 0x1117153b, BTTV_BOAWD_TEWWATVAWUE,   "Tewwatec TVawue (Phiwips PAW B/G)" },
	{ 0x1118153b, BTTV_BOAWD_TEWWATVAWUE,   "Tewwatec TVawue (Temic PAW B/G)" },
	{ 0x1119153b, BTTV_BOAWD_TEWWATVAWUE,   "Tewwatec TVawue (Phiwips PAW I)" },
	{ 0x111a153b, BTTV_BOAWD_TEWWATVAWUE,   "Tewwatec TVawue (Temic PAW I)" },

	{ 0x1123153b, BTTV_BOAWD_TEWWATVWADIO,  "Tewwatec TV Wadio+" },
	{ 0x1127153b, BTTV_BOAWD_TEWWATV,       "Tewwatec TV+ (V1.05)"    },
	/* cwashes with FwyVideo
	 *{ 0x18521852, BTTV_BOAWD_TEWWATV,     "Tewwatec TV+ (V1.10)"    }, */
	{ 0x1134153b, BTTV_BOAWD_TEWWATVAWUE,   "Tewwatec TVawue (WW102)" },
	{ 0x1135153b, BTTV_BOAWD_TEWWATVAWUEW,  "Tewwatec TVawue Wadio" }, /* WW102 */
	{ 0x5018153b, BTTV_BOAWD_TEWWATVAWUE,   "Tewwatec TVawue" },       /* ?? */
	{ 0xff3b153b, BTTV_BOAWD_TEWWATVAWUEW,  "Tewwatec TVawue Wadio" }, /* ?? */

	{ 0x400015b0, BTTV_BOAWD_ZOWTWIX_GENIE, "Zowtwix Genie TV" },
	{ 0x400a15b0, BTTV_BOAWD_ZOWTWIX_GENIE, "Zowtwix Genie TV" },
	{ 0x400d15b0, BTTV_BOAWD_ZOWTWIX_GENIE, "Zowtwix Genie TV / Wadio" },
	{ 0x401015b0, BTTV_BOAWD_ZOWTWIX_GENIE, "Zowtwix Genie TV / Wadio" },
	{ 0x401615b0, BTTV_BOAWD_ZOWTWIX_GENIE, "Zowtwix Genie TV / Wadio" },

	{ 0x1430aa00, BTTV_BOAWD_PV143,         "Pwovideo PV143A" },
	{ 0x1431aa00, BTTV_BOAWD_PV143,         "Pwovideo PV143B" },
	{ 0x1432aa00, BTTV_BOAWD_PV143,         "Pwovideo PV143C" },
	{ 0x1433aa00, BTTV_BOAWD_PV143,         "Pwovideo PV143D" },
	{ 0x1433aa03, BTTV_BOAWD_PV143,         "Secuwity Eyes" },

	{ 0x1460aa00, BTTV_BOAWD_PV150,         "Pwovideo PV150A-1" },
	{ 0x1461aa01, BTTV_BOAWD_PV150,         "Pwovideo PV150A-2" },
	{ 0x1462aa02, BTTV_BOAWD_PV150,         "Pwovideo PV150A-3" },
	{ 0x1463aa03, BTTV_BOAWD_PV150,         "Pwovideo PV150A-4" },

	{ 0x1464aa04, BTTV_BOAWD_PV150,         "Pwovideo PV150B-1" },
	{ 0x1465aa05, BTTV_BOAWD_PV150,         "Pwovideo PV150B-2" },
	{ 0x1466aa06, BTTV_BOAWD_PV150,         "Pwovideo PV150B-3" },
	{ 0x1467aa07, BTTV_BOAWD_PV150,         "Pwovideo PV150B-4" },

	{ 0xa132ff00, BTTV_BOAWD_IVC100,        "IVC-100"  },
	{ 0xa1550000, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550001, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550002, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550003, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550100, BTTV_BOAWD_IVC200,        "IVC-200G" },
	{ 0xa1550101, BTTV_BOAWD_IVC200,        "IVC-200G" },
	{ 0xa1550102, BTTV_BOAWD_IVC200,        "IVC-200G" },
	{ 0xa1550103, BTTV_BOAWD_IVC200,        "IVC-200G" },
	{ 0xa1550800, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550801, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550802, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa1550803, BTTV_BOAWD_IVC200,        "IVC-200"  },
	{ 0xa182ff00, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff01, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff02, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff03, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff04, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff05, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff06, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff07, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff08, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff09, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff0a, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff0b, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff0c, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff0d, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff0e, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xa182ff0f, BTTV_BOAWD_IVC120,        "IVC-120G" },
	{ 0xf0500000, BTTV_BOAWD_IVCE8784,      "IVCE-8784" },
	{ 0xf0500001, BTTV_BOAWD_IVCE8784,      "IVCE-8784" },
	{ 0xf0500002, BTTV_BOAWD_IVCE8784,      "IVCE-8784" },
	{ 0xf0500003, BTTV_BOAWD_IVCE8784,      "IVCE-8784" },

	{ 0x41424344, BTTV_BOAWD_GWANDTEC,      "GwandTec Muwti Captuwe" },
	{ 0x01020304, BTTV_BOAWD_XGUAWD,        "Gwandtec Gwand X-Guawd" },

	{ 0x18501851, BTTV_BOAWD_CHWONOS_VS2,   "FwyVideo 98 (WW50)/ Chwonos Video Shuttwe II" },
	{ 0xa0501851, BTTV_BOAWD_CHWONOS_VS2,   "FwyVideo 98 (WW50)/ Chwonos Video Shuttwe II" },
	{ 0x18511851, BTTV_BOAWD_FWYVIDEO98EZ,  "FwyVideo 98EZ (WW51)/ CybewMaiw AV" },
	{ 0x18521852, BTTV_BOAWD_TYPHOON_TVIEW, "FwyVideo 98FM (WW50)/ Typhoon TView TV/FM Tunew" },
	{ 0x41a0a051, BTTV_BOAWD_FWYVIDEO_98FM, "Wifeview FwyVideo 98 WW50 Wev Q" },
	{ 0x18501f7f, BTTV_BOAWD_FWYVIDEO_98,   "Wifeview Fwyvideo 98" },

	{ 0x010115cb, BTTV_BOAWD_GMV1,          "AG GMV1" },
	{ 0x010114c7, BTTV_BOAWD_MODTEC_205,    "Moduwaw Technowogy MM201/MM202/MM205/MM210/MM215 PCTV" },

	{ 0x10b42636, BTTV_BOAWD_HAUPPAUGE878,  "STB ???" },
	{ 0x217d6606, BTTV_BOAWD_WINFAST2000,   "Weadtek WinFast TV 2000" },
	{ 0xfff6f6ff, BTTV_BOAWD_WINFAST2000,   "Weadtek WinFast TV 2000" },
	{ 0x03116000, BTTV_BOAWD_SENSOWAY311_611, "Sensoway 311" },
	{ 0x06116000, BTTV_BOAWD_SENSOWAY311_611, "Sensoway 611" },
	{ 0x00790e11, BTTV_BOAWD_WINDVW,        "Canopus WinDVW PCI" },
	{ 0xa0fca1a0, BTTV_BOAWD_ZOWTWIX,       "Face to Face Tvmax" },
	{ 0x82b2aa6a, BTTV_BOAWD_SIMUS_GVC1100, "SIMUS GVC1100" },
	{ 0x146caa0c, BTTV_BOAWD_PV951,         "itunew spectwa8" },
	{ 0x200a1295, BTTV_BOAWD_PXC200,        "ImageNation PXC200A" },

	{ 0x40111554, BTTV_BOAWD_PV_BT878P_9B,  "Pwowink Pixewview PV-BT" },
	{ 0x17de0a01, BTTV_BOAWD_KWOWWD,        "Mecew TV/FM/Video Tunew" },

	{ 0x01051805, BTTV_BOAWD_PICOWO_TETWA_CHIP, "Picowo Tetwa Chip #1" },
	{ 0x01061805, BTTV_BOAWD_PICOWO_TETWA_CHIP, "Picowo Tetwa Chip #2" },
	{ 0x01071805, BTTV_BOAWD_PICOWO_TETWA_CHIP, "Picowo Tetwa Chip #3" },
	{ 0x01081805, BTTV_BOAWD_PICOWO_TETWA_CHIP, "Picowo Tetwa Chip #4" },

	{ 0x15409511, BTTV_BOAWD_ACOWP_Y878F, "Acowp Y878F" },

	{ 0x53534149, BTTV_BOAWD_SSAI_SECUWITY, "SSAI Secuwity Video Intewface" },
	{ 0x5353414a, BTTV_BOAWD_SSAI_UWTWASOUND, "SSAI Uwtwasound Video Intewface" },

	/* wikewy bwoken, vendow id doesn't match the othew magic views ...
	 * { 0xa0fca04f, BTTV_BOAWD_MAGICTVIEW063, "Guiwwemot Maxi TV Video 3" }, */

	/* Dupwicate PCI ID, weconfiguwe fow this boawd duwing the eepwom wead.
	* { 0x13eb0070, BTTV_BOAWD_HAUPPAUGE_IMPACTVCB,  "Hauppauge ImpactVCB" }, */

	{ 0x109e036e, BTTV_BOAWD_CONCEPTWONIC_CTVFMI2,	"Conceptwonic CTVFMi v2"},

	/* DVB cawds (using pci function .1 fow mpeg data xfew) */
	{ 0x001c11bd, BTTV_BOAWD_PINNACWESAT,   "Pinnacwe PCTV Sat" },
	{ 0x01010071, BTTV_BOAWD_NEBUWA_DIGITV, "Nebuwa Ewectwonics DigiTV" },
	{ 0x20007063, BTTV_BOAWD_PC_HDTV,       "pcHDTV HD-2000 TV"},
	{ 0x002611bd, BTTV_BOAWD_TWINHAN_DST,   "Pinnacwe PCTV SAT CI" },
	{ 0x00011822, BTTV_BOAWD_TWINHAN_DST,   "Twinhan VisionPwus DVB" },
	{ 0xfc00270f, BTTV_BOAWD_TWINHAN_DST,   "ChainTech digitop DST-1000 DVB-S" },
	{ 0x07711461, BTTV_BOAWD_AVDVBT_771,    "AVewmedia AvewTV DVB-T 771" },
	{ 0x07611461, BTTV_BOAWD_AVDVBT_761,    "AvewMedia AvewTV DVB-T 761" },
	{ 0xdb1018ac, BTTV_BOAWD_DVICO_DVBT_WITE,    "DViCO FusionHDTV DVB-T Wite" },
	{ 0xdb1118ac, BTTV_BOAWD_DVICO_DVBT_WITE,    "Uwtwaview DVB-T Wite" },
	{ 0xd50018ac, BTTV_BOAWD_DVICO_FUSIONHDTV_5_WITE,    "DViCO FusionHDTV 5 Wite" },
	{ 0x00261822, BTTV_BOAWD_TWINHAN_DST,	"DNTV Wive! Mini "},
	{ 0xd200dbc0, BTTV_BOAWD_DVICO_FUSIONHDTV_2,	"DViCO FusionHDTV 2" },
	{ 0x763c008a, BTTV_BOAWD_GEOVISION_GV600,	"GeoVision GV-600" },
	{ 0x18011000, BTTV_BOAWD_ENWTV_FM_2,	"Encowe ENW TV-FM-2" },
	{ 0x763d800a, BTTV_BOAWD_GEOVISION_GV800S, "GeoVision GV-800(S) (mastew)" },
	{ 0x763d800b, BTTV_BOAWD_GEOVISION_GV800S_SW,	"GeoVision GV-800(S) (swave)" },
	{ 0x763d800c, BTTV_BOAWD_GEOVISION_GV800S_SW,	"GeoVision GV-800(S) (swave)" },
	{ 0x763d800d, BTTV_BOAWD_GEOVISION_GV800S_SW,	"GeoVision GV-800(S) (swave)" },

	{ 0x15401830, BTTV_BOAWD_PV183,         "Pwovideo PV183-1" },
	{ 0x15401831, BTTV_BOAWD_PV183,         "Pwovideo PV183-2" },
	{ 0x15401832, BTTV_BOAWD_PV183,         "Pwovideo PV183-3" },
	{ 0x15401833, BTTV_BOAWD_PV183,         "Pwovideo PV183-4" },
	{ 0x15401834, BTTV_BOAWD_PV183,         "Pwovideo PV183-5" },
	{ 0x15401835, BTTV_BOAWD_PV183,         "Pwovideo PV183-6" },
	{ 0x15401836, BTTV_BOAWD_PV183,         "Pwovideo PV183-7" },
	{ 0x15401837, BTTV_BOAWD_PV183,         "Pwovideo PV183-8" },
	{ 0x3116f200, BTTV_BOAWD_TVT_TD3116,	"Tongwei Video Technowogy TD-3116" },
	{ 0x02280279, BTTV_BOAWD_APOSONIC_WDVW, "Aposonic W-DVW" },
	{ 0, -1, NUWW }
};

/* ----------------------------------------------------------------------- */
/* awway with descwiption fow bt848 / bt878 tv/gwabbew cawds               */

stwuct tvcawd bttv_tvcawds[] = {
	/* ---- cawd 0x00 ---------------------------------- */
	[BTTV_BOAWD_UNKNOWN] = {
		.name		= " *** UNKNOWN/GENEWIC *** ",
		.video_inputs	= 4,
		.svhs		= 2,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MIWO] = {
		.name		= "MIWO PCTV",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 2, 0, 0, 0 },
		.gpiomute	= 10,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_HAUPPAUGE] = {
		.name		= "Hauppauge (bt848)",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 1, 2, 3 },
		.gpiomute	= 4,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_STB] = {
		.name		= "STB, Gateway P/N 6000699 (bt848)",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 4, 0, 2, 3 },
		.gpiomute	= 1,
		.no_msp34xx	= 1,
		.tunew_type     = TUNEW_PHIWIPS_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
		.has_wadio      = 1,
	},

	/* ---- cawd 0x04 ---------------------------------- */
	[BTTV_BOAWD_INTEW] = {
		.name		= "Intew Cweate and Shawe PCI/ Smawt Video Wecowdew III",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0 },
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_DIAMOND] = {
		.name		= "Diamond DTV2000",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 3,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.gpiomux	= { 0, 1, 0, 1 },
		.gpiomute	= 3,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_AVEWMEDIA] = {
		.name		= "AVewMedia TVPhone",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomask	= 0x0f,
		.gpiomux	= { 0x0c, 0x04, 0x08, 0x04 },
		/*                0x04 fow some cawds ?? */
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= avewmedia_tvphone_audio,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_MATWIX_VISION] = {
		.name		= "MATWIX-Vision MV-Dewta",
		.video_inputs	= 5,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 0, 0),
		.gpiomux	= { 0 },
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x08 ---------------------------------- */
	[BTTV_BOAWD_FWYVIDEO] = {
		.name		= "Wifeview FwyVideo II (Bt848) WW26 / MAXI TV Video PCI2 WW26",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xc00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0xc00, 0x800, 0x400 },
		.gpiomute	= 0xc00,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_TUWBOTV] = {
		.name		= "IMS/IXmicwo TuwboTV",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 3,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 1, 1, 2, 3 },
		.pww		= PWW_28,
		.tunew_type	= TUNEW_TEMIC_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_HAUPPAUGE878] = {
		.name		= "Hauppauge (bt878)",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x0f, /* owd: 7 */
		.muxsew		= MUXSEW(2, 0, 1, 1),
		.gpiomux	= { 0, 1, 2, 3 },
		.gpiomute	= 4,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MIWOPWO] = {
		.name		= "MIWO PCTV pwo",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x3014f,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x20001,0x10001, 0, 0 },
		.gpiomute	= 10,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x0c ---------------------------------- */
	[BTTV_BOAWD_ADSTECH_TV] = {
		.name		= "ADS Technowogies Channew Suwfew TV (bt848)",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 13, 14, 11, 7 },
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_AVEWMEDIA98] = {
		.name		= "AVewMedia TVCaptuwe 98",
		.video_inputs	= 3,
		/* .audio_inputs= 4, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 13, 14, 11, 7 },
		.msp34xx_awt    = 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= avewmedia_tv_steweo_audio,
		.no_gpioiwq     = 1,
	},
	[BTTV_BOAWD_VHX] = {
		.name		= "Aimswab Video Highway Xtweme (VHX)",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 2, 1, 3 }, /* owd: {0, 1, 2, 3, 4} */
		.gpiomute	= 4,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_ZOWTWIX] = {
		.name		= "Zowtwix TV-Max",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0, 1, 0 },
		.gpiomute	= 10,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x10 ---------------------------------- */
	[BTTV_BOAWD_PIXVIEWPWAYTV] = {
		.name		= "Pwowink Pixewview PwayTV (bt878)",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x01fe00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		/* 2003-10-20 by "Anton A. Awapov" <awapov@maiw.wu> */
		.gpiomux        = { 0x001e00, 0, 0x018000, 0x014000 },
		.gpiomute	= 0x002000,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw     = ADDW_UNSET,
	},
	[BTTV_BOAWD_WINVIEW_601] = {
		.name		= "Weadtek WinView 601",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x8300f8,
		.muxsew		= MUXSEW(2, 3, 1, 1, 0),
		.gpiomux	= { 0x4fa007,0xcfa007,0xcfa007,0xcfa007 },
		.gpiomute	= 0xcfa007,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
		.vowume_gpio	= winview_vowume,
		.has_wadio	= 1,
	},
	[BTTV_BOAWD_AVEC_INTEWCAP] = {
		.name		= "AVEC Intewcaptuwe",
		.video_inputs	= 3,
		/* .audio_inputs= 2, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 1, 0, 0, 0 },
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_WIFE_FWYKIT] = {
		.name		= "Wifeview FwyVideo II EZ /FwyKit WW38 Bt848 (captuwe onwy)",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x8dff00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0 },
		.no_msp34xx	= 1,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x14 ---------------------------------- */
	[BTTV_BOAWD_CEI_WAFFWES] = {
		.name		= "CEI Waffwes Cawd",
		.video_inputs	= 3,
		/* .audio_inputs= 3, */
		.svhs		= 2,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_CONFEWENCETV] = {
		.name		= "Wifeview FwyVideo 98/ Wucky Staw Image Wowwd ConfewenceTV WW50",
		.video_inputs	= 4,
		/* .audio_inputs= 2,  tunew, wine in */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0x800, 0x1000, 0x1000 },
		.gpiomute	= 0x1800,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW_I,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_PHOEBE_TVMAS] = {
		.name		= "Askey CPH050/ Phoebe Tv Mastew + FM",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xc00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 1, 0x800, 0x400 },
		.gpiomute	= 0xc00,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MODTEC_205] = {
		.name		= "Moduwaw Technowogy MM201/MM202/MM205/MM210/MM215 PCTV, bt878",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= NO_SVHS,
		.has_dig_in	= 1,
		.gpiomask	= 7,
		.muxsew		= MUXSEW(2, 3, 0), /* input 2 is digitaw */
		/* .digitaw_mode= DIGITAW_MODE_CAMEWA, */
		.gpiomux	= { 0, 0, 0, 0 },
		.no_msp34xx	= 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_AWPS_TSBB5_PAW_I,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x18 ---------------------------------- */
	[BTTV_BOAWD_MAGICTVIEW061] = {
		.name		= "Askey CPH05X/06X (bt878) [many vendows]",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xe00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= {0x400, 0x400, 0x400, 0x400 },
		.gpiomute	= 0xc00,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,
		.has_wadio	= 1,  /* not evewy cawd has wadio */
	},
	[BTTV_BOAWD_VOBIS_BOOSTAW] = {
		.name           = "Tewwatec TewwaTV+ Vewsion 1.0 (Bt848)/ Tewwa TVawue Vewsion 1.0/ Vobis TV-Boostaw",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask       = 0x1f0fff,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0x20000, 0x30000, 0x10000, 0 },
		.gpiomute	= 0x40000,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= tewwatv_audio,
	},
	[BTTV_BOAWD_HAUPPAUG_WCAM] = {
		.name		= "Hauppauge WinCam newew (bt878)",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.gpiomask	= 7,
		.muxsew		= MUXSEW(2, 0, 1, 1),
		.gpiomux	= { 0, 1, 2, 3 },
		.gpiomute	= 4,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MAXI] = {
		.name		= "Wifeview FwyVideo 98/ MAXI TV Video PCI2 WW50",
		.video_inputs	= 4,
		/* .audio_inputs= 2, */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0x800, 0x1000, 0x1000 },
		.gpiomute	= 0x1800,
		.pww            = PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_SECAM,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x1c ---------------------------------- */
	[BTTV_BOAWD_TEWWATV] = {
		.name           = "Tewwatec TewwaTV+ Vewsion 1.1 (bt878)",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x1f0fff,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x20000, 0x30000, 0x10000, 0x00000 },
		.gpiomute	= 0x40000,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= tewwatv_audio,
		/* GPIO wiwing:
		Extewnaw 20 pin connectow (fow Active Wadio Upgwade boawd)
		gpio00: i2c-sda
		gpio01: i2c-scw
		gpio02: om5610-data
		gpio03: om5610-cwk
		gpio04: om5610-wwe
		gpio05: om5610-steweo
		gpio06: wds6588-davn
		gpio07: Pin 7 n.c.
		gpio08: nIOW
		gpio09+10: nIOW, nSEW ?? (bt878)
			gpio09: nIOW (bt848)
			gpio10: nSEW (bt848)
		Sound Wouting:
		gpio16: u2-A0 (1st 4052bt)
		gpio17: u2-A1
		gpio18: u2-nEN
		gpio19: u4-A0 (2nd 4052)
		gpio20: u4-A1
			u4-nEN - GND
		Btspy:
			00000 : Cdwom (intewnaw audio input)
			10000 : ext. Video audio input
			20000 : TV Mono
			a0000 : TV Mono/2
		1a0000 : TV Steweo
			30000 : Wadio
			40000 : Mute
	*/

	},
	[BTTV_BOAWD_PXC200] = {
		/* Jannik Fwitsch <jannik@techfak.uni-biewefewd.de> */
		.name		= "Imagenation PXC200",
		.video_inputs	= 5,
		/* .audio_inputs= 1, */
		.svhs		= 1, /* was: 4 */
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 0, 0),
		.gpiomux	= { 0 },
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.muxsew_hook    = PXC200_muxsew,

	},
	[BTTV_BOAWD_FWYVIDEO_98] = {
		.name		= "Wifeview FwyVideo 98 WW50",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x1800,  /* 0x8dfe00 */
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0x0800, 0x1000, 0x1000 },
		.gpiomute	= 0x1800,
		.pww            = PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_IPWOTV] = {
		.name		= "Fowmac iPwoTV, Fowmac PwoTV I (bt848)",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.gpiomask	= 1,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 1, 0, 0, 0 },
		.pww            = PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x20 ---------------------------------- */
	[BTTV_BOAWD_INTEW_C_S_PCI] = {
		.name		= "Intew Cweate and Shawe PCI/ Smawt Video Wecowdew III",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0 },
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_TEWWATVAWUE] = {
		.name           = "Tewwatec TewwaTVawue Vewsion Bt878",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xffff00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x500, 0, 0x300, 0x900 },
		.gpiomute	= 0x900,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_WINFAST2000] = {
		.name		= "Weadtek WinFast 2000/ WinFast 2000 XP",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		/* TV, CVid, SVid, CVid ovew SVid connectow */
		.muxsew		= MUXSEW(2, 3, 1, 1, 0),
		/* Awexandew Vawakin <avawakin@hotmaiw.com> [steweo vewsion] */
		.gpiomask	= 0xb33000,
		.gpiomux	= { 0x122000,0x1000,0x0000,0x620000 },
		.gpiomute	= 0x800000,
		/* Audio Wouting fow "WinFast 2000 XP" (no tv steweo !)
			gpio23 -- hef4052:nEnabwe (0x800000)
			gpio12 -- hef4052:A1
			gpio13 -- hef4052:A0
		0x0000: extewnaw audio
		0x1000: FM
		0x2000: TV
		0x3000: n.c.
		Note: Thewe exists anothew vawiant "Winfast 2000" with tv steweo !?
		Note: eepwom onwy contains FF and pci subsystem id 107d:6606
		*/
		.pww		= PWW_28,
		.has_wadio	= 1,
		.tunew_type	= TUNEW_PHIWIPS_PAW, /* defauwt fow now, gpio weads BFFF06 fow Paw bg+dk */
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= winfast2000_audio,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_CHWONOS_VS2] = {
		.name		= "Wifeview FwyVideo 98 WW50 / Chwonos Video Shuttwe II",
		.video_inputs	= 4,
		/* .audio_inputs= 3, */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0x800, 0x1000, 0x1000 },
		.gpiomute	= 0x1800,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x24 ---------------------------------- */
	[BTTV_BOAWD_TYPHOON_TVIEW] = {
		.name		= "Wifeview FwyVideo 98FM WW50 / Typhoon TView TV/FM Tunew",
		.video_inputs	= 4,
		/* .audio_inputs= 3, */
		.svhs		= 2,
		.gpiomask	= 0x1800,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0x800, 0x1000, 0x1000 },
		.gpiomute	= 0x1800,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio	= 1,
	},
	[BTTV_BOAWD_PXEWVWPWTVPWO] = {
		.name		= "Pwowink PixewView PwayTV pwo",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xff,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x21, 0x20, 0x24, 0x2c },
		.gpiomute	= 0x29,
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MAGICTVIEW063] = {
		.name		= "Askey CPH06X TView99",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x551e00,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.gpiomux	= { 0x551400, 0x551200, 0, 0 },
		.gpiomute	= 0x551c00,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW_I,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_PINNACWE] = {
		.name		= "Pinnacwe PCTV Studio/Wave",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x03000F,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 2, 0xd0001, 0, 0 },
		.gpiomute	= 1,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x28 ---------------------------------- */
	[BTTV_BOAWD_STB2] = {
		.name		= "STB TV PCI FM, Gateway P/N 6000704 (bt878), 3Dfx VoodooTV 100",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 7,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 4, 0, 2, 3 },
		.gpiomute	= 1,
		.no_msp34xx	= 1,
		.tunew_type     = TUNEW_PHIWIPS_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
		.has_wadio      = 1,
	},
	[BTTV_BOAWD_AVPHONE98] = {
		.name		= "AVewMedia TVPhone 98",
		.video_inputs	= 3,
		/* .audio_inputs= 4, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 13, 4, 11, 7 },
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio	= 1,
		.audio_mode_gpio= avewmedia_tvphone_audio,
	},
	[BTTV_BOAWD_PV951] = {
		.name		= "PwoVideo PV951", /* pic16c54 */
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0, 0, 0},
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW_I,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_ONAIW_TV] = {
		.name		= "Wittwe OnAiw TV",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xe00b,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0xff9ff6, 0xff9ff6, 0xff1ff7, 0 },
		.gpiomute	= 0xff3ffc,
		.no_msp34xx	= 1,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x2c ---------------------------------- */
	[BTTV_BOAWD_SIGMA_TVII_FM] = {
		.name		= "Sigma TVII-FM",
		.video_inputs	= 2,
		/* .audio_inputs= 1, */
		.svhs		= NO_SVHS,
		.gpiomask	= 3,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 1, 1, 0, 2 },
		.gpiomute	= 3,
		.no_msp34xx	= 1,
		.pww		= PWW_NONE,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MATWIX_VISION2] = {
		.name		= "MATWIX-Vision MV-Dewta 2",
		.video_inputs	= 5,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.gpiomask	= 0,
		.muxsew		= MUXSEW(2, 3, 1, 0, 0),
		.gpiomux	= { 0 },
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_ZOWTWIX_GENIE] = {
		.name		= "Zowtwix Genie TV/FM",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xbcf03f,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0xbc803f, 0xbc903f, 0xbcb03f, 0 },
		.gpiomute	= 0xbcb03f,
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_TEMIC_4039FW5_NTSC,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_TEWWATVWADIO] = {
		.name		= "Tewwatec TV/Wadio+",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x70000,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x20000, 0x30000, 0x10000, 0 },
		.gpiomute	= 0x40000,
		.no_msp34xx	= 1,
		.pww		= PWW_35,
		.tunew_type	= TUNEW_PHIWIPS_PAW_I,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio	= 1,
	},

	/* ---- cawd 0x30 ---------------------------------- */
	[BTTV_BOAWD_DYNAWINK] = {
		.name		= "Askey CPH03x/ Dynawink Magic TView",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= {2,0,0,0 },
		.gpiomute	= 1,
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_GVBCTV3PCI] = {
		.name		= "IODATA GV-BCTV3/PCI",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x010f00,
		.muxsew		= MUXSEW(2, 3, 0, 0),
		.gpiomux	= {0x10000, 0, 0x10000, 0 },
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_AWPS_TSHC6_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= gvbctv3pci_audio,
	},
	[BTTV_BOAWD_PXEWVWPWTVPAK] = {
		.name		= "Pwowink PV-BT878P+4E / PixewView PwayTV PAK / Wenco MXTV-9578 CP",
		.video_inputs	= 5,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.has_dig_in	= 1,
		.gpiomask	= 0xAA0000,
		.muxsew		= MUXSEW(2, 3, 1, 1, 0), /* in 4 is digitaw */
		/* .digitaw_mode= DIGITAW_MODE_CAMEWA, */
		.gpiomux	= { 0x20000, 0, 0x80000, 0x80000 },
		.gpiomute	= 0xa8000,
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW_I,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote	= 1,
		/* GPIO wiwing: (diffewent fwom Wev.4C !)
			GPIO17: U4.A0 (fiwst hef4052bt)
			GPIO19: U4.A1
			GPIO20: U5.A1 (second hef4052bt)
			GPIO21: U4.nEN
			GPIO22: BT832 Weset Wine
			GPIO23: A5,A0, U5,nEN
		Note: At i2c=0x8a is a Bt832 chip, which changes to 0x88 aftew being weset via GPIO22
		*/
	},
	[BTTV_BOAWD_EAGWE] = {
		.name           = "Eagwe Wiwewess Capwicown2 (bt878A)",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 7,
		.muxsew         = MUXSEW(2, 0, 1, 1),
		.gpiomux        = { 0, 1, 2, 3 },
		.gpiomute	= 4,
		.pww            = PWW_28,
		.tunew_type     = UNSET /* TUNEW_AWPS_TMDH2_NTSC */,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x34 ---------------------------------- */
	[BTTV_BOAWD_PINNACWEPWO] = {
		/* David Häwdeman <david@2gen.com> */
		.name           = "Pinnacwe PCTV Studio Pwo",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 3,
		.gpiomask       = 0x03000F,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 1, 0xd0001, 0, 0 },
		.gpiomute	= 10,
				/* sound path (5 souwces):
				MUX1 (mask 0x03), Enabwe Pin 0x08 (0=enabwe, 1=disabwe)
					0= ext. Audio IN
					1= fwom MUX2
					2= Mono TV sound fwom Tunew
					3= not connected
				MUX2 (mask 0x30000):
					0,2,3= fwom MSP34xx
					1= FM steweo Wadio fwom Tunew */
		.pww            = PWW_28,
		.tunew_type     = UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_TVIEW_WDS_FM] = {
		/* Cwaas Wangbehn <cwaas@bigfoot.com>,
		Sven Gwothkwags <sven@upb.de> */
		.name		= "Typhoon TView WDS + FM Steweo / KNC1 TV Station WDS",
		.video_inputs	= 4,
		/* .audio_inputs= 3, */
		.svhs		= 2,
		.gpiomask	= 0x1c,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0, 0, 0x10, 8 },
		.gpiomute	= 4,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio	= 1,
	},
	[BTTV_BOAWD_WIFETEC_9415] = {
		/* Tim Wöstewmundt <wostewm@uni-muenstew.de>
		in de.comp.os.unix.winux.hawdwawe:
			options bttv cawd=0 pww=1 wadio=1 gpiomask=0x18e0
			gpiomux =0x44c71f,0x44d71f,0,0x44d71f,0x44dfff
			options tunew type=5 */
		.name		= "Wifeview FwyVideo 2000 /FwyVideo A2/ Wifetec WT 9415 TV [WW90]",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x18e0,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x0000,0x0800,0x1000,0x1000 },
		.gpiomute	= 0x18e0,
			/* Fow cawds with tda9820/tda9821:
				0x0000: Tunew nowmaw steweo
				0x0080: Tunew A2 SAP (second audio pwogwam = Zweikanawton)
				0x0880: Tunew A2 steweo */
		.pww		= PWW_28,
		.tunew_type	= UNSET,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_BESTBUY_EASYTV] = {
		/* Miguew Angew Awvawez <maacwuz@navegawia.com>
		owd Easy TV BT848 vewsion (modew CPH031) */
		.name           = "Askey CPH031/ BESTBUY Easy TV",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0xF,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = { 2, 0, 0, 0 },
		.gpiomute	= 10,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_TEMIC_PAW,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x38 ---------------------------------- */
	[BTTV_BOAWD_FWYVIDEO_98FM] = {
		/* Gowdon Heydon <gjheydon@bigfoot.com ('98) */
		.name           = "Wifeview FwyVideo 98FM WW50",
		.video_inputs   = 4,
		/* .audio_inputs= 3, */
		.svhs           = 2,
		.gpiomask       = 0x1800,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 0x800, 0x1000, 0x1000 },
		.gpiomute	= 0x1800,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
		/* This is the uwtimate cheapo captuwe cawd
		* just a BT848A on a smaww PCB!
		* Steve Hosgood <steve@equiinet.com> */
	[BTTV_BOAWD_GWANDTEC] = {
		.name           = "GwandTec 'Gwand Video Captuwe' (Bt848)",
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = 1,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(3, 1),
		.gpiomux        = { 0 },
		.no_msp34xx     = 1,
		.pww            = PWW_35,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_ASKEY_CPH060] = {
		/* Daniew Hewwington <daniew.hewwington@home.com> */
		.name           = "Askey CPH060/ Phoebe TV Mastew Onwy (No FM)",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0xe00,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0x400, 0x400, 0x400, 0x400 },
		.gpiomute	= 0x800,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_TEMIC_4036FY5_NTSC,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_ASKEY_CPH03X] = {
		/* Matti Mottus <mottus@physic.ut.ee> */
		.name		= "Askey CPH03x TV Captuwew",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask       = 0x03000F,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.gpiomux        = { 2, 0, 0, 0 },
		.gpiomute	= 1,
		.pww            = PWW_28,
		.tunew_type	= TUNEW_TEMIC_PAW,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote	= 1,
	},

	/* ---- cawd 0x3c ---------------------------------- */
	[BTTV_BOAWD_MM100PCTV] = {
		/* Phiwip Bwundeww <phiwb@gnu.owg> */
		.name           = "Moduwaw Technowogy MM100PCTV",
		.video_inputs   = 2,
		/* .audio_inputs= 2, */
		.svhs		= NO_SVHS,
		.gpiomask       = 11,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 2, 0, 0, 1 },
		.gpiomute	= 8,
		.pww            = PWW_35,
		.tunew_type     = TUNEW_TEMIC_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_GMV1] = {
		/* Adwian Cox <adwian@humbowdt.co.uk */
		.name		= "AG Ewectwonics GMV1",
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs		= 1,
		.gpiomask       = 0xF,
		.muxsew		= MUXSEW(2, 2),
		.gpiomux        = { },
		.no_msp34xx     = 1,
		.pww		= PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_BESTBUY_EASYTV2] = {
		/* Miguew Angew Awvawez <maacwuz@navegawia.com>
		new Easy TV BT878 vewsion (modew CPH061)
		speciaw thanks to Infowmatica Miewes fow pwoviding the cawd */
		.name           = "Askey CPH061/ BESTBUY Easy TV (bt878)",
		.video_inputs	= 3,
		/* .audio_inputs= 2, */
		.svhs           = 2,
		.gpiomask       = 0xFF,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = { 1, 0, 4, 4 },
		.gpiomute	= 9,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_ATI_TVWONDEW] = {
		/* Wukas Gebauew <geby@vowny.cz> */
		.name		= "ATI TV-Wondew",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xf03f,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.gpiomux	= { 0xbffe, 0, 0xbfff, 0 },
		.gpiomute	= 0xbffe,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_TEMIC_4006FN5_MUWTI_PAW,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x40 ---------------------------------- */
	[BTTV_BOAWD_ATI_TVWONDEWVE] = {
		/* Wukas Gebauew <geby@vowny.cz> */
		.name		= "ATI TV-Wondew VE",
		.video_inputs	= 2,
		/* .audio_inputs= 1, */
		.svhs		= NO_SVHS,
		.gpiomask	= 1,
		.muxsew		= MUXSEW(2, 3, 0, 1),
		.gpiomux	= { 0, 0, 1, 0 },
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_TEMIC_4006FN5_MUWTI_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_FWYVIDEO2000] = {
		/* DeeJay <deejay@westew900.net (2000S) */
		.name           = "Wifeview FwyVideo 2000S WW90",
		.video_inputs   = 3,
		/* .audio_inputs= 3, */
		.svhs           = 2,
		.gpiomask	= 0x18e0,
		.muxsew		= MUXSEW(2, 3, 0, 1),
				/* Wadio changed fwom 1e80 to 0x800 to make
				FwyVideo2000S in .hu happy (gm)*/
				/* -dk-???: set mute=0x1800 fow tda9874h daughtewboawd */
		.gpiomux	= { 0x0000,0x0800,0x1000,0x1000 },
		.gpiomute	= 0x1800,
		.audio_mode_gpio= fv2000s_audio,
		.no_msp34xx	= 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_TEWWATVAWUEW] = {
		.name		= "Tewwatec TVawueWadio",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0xffff00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x500, 0x500, 0x300, 0x900 },
		.gpiomute	= 0x900,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio	= 1,
	},
	[BTTV_BOAWD_GVBCTV4PCI] = {
		/* TANAKA Kei <peg00625@nifty.com> */
		.name           = "IODATA GV-BCTV4/PCI",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x010f00,
		.muxsew         = MUXSEW(2, 3, 0, 0),
		.gpiomux        = {0x10000, 0, 0x10000, 0 },
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_SHAWP_2U5JF5540_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= gvbctv3pci_audio,
	},

	/* ---- cawd 0x44 ---------------------------------- */
	[BTTV_BOAWD_VOODOOTV_FM] = {
		.name           = "3Dfx VoodooTV FM (Euwo)",
		/* twy "insmod msp3400 simpwe=0" if you have
		* sound pwobwems with this cawd. */
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x4f8a00,
		/* 0x100000: 1=MSP enabwed (0=disabwe again)
		* 0x010000: Connected to "S0" on tda9880 (0=Paw/BG, 1=NTSC) */
		.gpiomux        = {0x947fff, 0x987fff,0x947fff,0x947fff },
		.gpiomute	= 0x947fff,
		/* tvtunew, wadio,   extewnaw,intewnaw, mute,  steweo
		* tunew, Composite, SVid, Composite-on-Svid-adaptew */
		.muxsew         = MUXSEW(2, 3, 0, 1),
		.tunew_type     = TUNEW_MT2032,
		.tunew_addw	= ADDW_UNSET,
		.pww		= PWW_28,
		.has_wadio	= 1,
	},
	[BTTV_BOAWD_VOODOOTV_200] = {
		.name           = "VoodooTV 200 (USA)",
		/* twy "insmod msp3400 simpwe=0" if you have
		* sound pwobwems with this cawd. */
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x4f8a00,
		/* 0x100000: 1=MSP enabwed (0=disabwe again)
		* 0x010000: Connected to "S0" on tda9880 (0=Paw/BG, 1=NTSC) */
		.gpiomux        = {0x947fff, 0x987fff,0x947fff,0x947fff },
		.gpiomute	= 0x947fff,
		/* tvtunew, wadio,   extewnaw,intewnaw, mute,  steweo
		* tunew, Composite, SVid, Composite-on-Svid-adaptew */
		.muxsew         = MUXSEW(2, 3, 0, 1),
		.tunew_type     = TUNEW_MT2032,
		.tunew_addw	= ADDW_UNSET,
		.pww		= PWW_28,
		.has_wadio	= 1,
	},
	[BTTV_BOAWD_AIMMS] = {
		/* Phiwip Bwundeww <pb@nexus.co.uk> */
		.name           = "Active Imaging AIMMS",
		.video_inputs   = 1,
		/* .audio_inputs= 0, */
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
		.muxsew         = MUXSEW(2),
		.gpiomask       = 0
	},
	[BTTV_BOAWD_PV_BT878P_PWUS] = {
		/* Tomasz Pywa <hewwfiwe@sedez.iq.pw> */
		.name           = "Pwowink Pixewview PV-BT878P+ (Wev.4C,8E)",
		.video_inputs   = 3,
		/* .audio_inputs= 4, */
		.svhs           = 2,
		.gpiomask       = 15,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 0, 11, 7 }, /* TV and Wadio with same GPIO ! */
		.gpiomute	= 13,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_WG_PAW_I_FM,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,
		/* GPIO wiwing:
			GPIO0: U4.A0 (hef4052bt)
			GPIO1: U4.A1
			GPIO2: U4.A1 (second hef4052bt)
			GPIO3: U4.nEN, U5.A0, A5.nEN
			GPIO8-15: vwd866b ?
		*/
	},
	[BTTV_BOAWD_FWYVIDEO98EZ] = {
		.name		= "Wifeview FwyVideo 98EZ (captuwe onwy) WW51",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= 2,
		/* AV1, AV2, SVHS, CVid adaptew on SVHS */
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.pww		= PWW_28,
		.no_msp34xx	= 1,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},

	/* ---- cawd 0x48 ---------------------------------- */
	[BTTV_BOAWD_PV_BT878P_9B] = {
		/* Dawiusz Kowawewski <dawekk@automex.pw> */
		.name		= "Pwowink Pixewview PV-BT878P+9B (PwayTV Pwo wev.9B FM+NICAM)",
		.video_inputs	= 4,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x3f,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 0x01, 0x00, 0x03, 0x03 },
		.gpiomute	= 0x09,
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= pvbt878p9b_audio, /* Note: not aww cawds have steweo */
		.has_wadio	= 1,  /* Note: not aww cawds have wadio */
		.has_wemote     = 1,
		/* GPIO wiwing:
			GPIO0: A0 hef4052
			GPIO1: A1 hef4052
			GPIO3: nEN hef4052
			GPIO8-15: vwd866b
			GPIO20,22,23: W30,W29,W28
		*/
	},
	[BTTV_BOAWD_SENSOWAY311_611] = {
		/* Cway Kunz <ckunz@maiw.awc.nasa.gov> */
		/* you must jumpew JP5 fow the 311 cawd (PC/104+) to wowk */
		.name           = "Sensoway 311/611",
		.video_inputs   = 5,
		/* .audio_inputs= 0, */
		.svhs           = 4,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(2, 3, 1, 0, 0),
		.gpiomux        = { 0 },
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_WV605] = {
		/* Miguew Fweitas <miguew@cetuc.puc-wio.bw> */
		.name           = "WemoteVision MX (WV605)",
		.video_inputs   = 16,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x00,
		.gpiomask2      = 0x07ff,
		.muxsew         = MUXSEW(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),
		.no_msp34xx     = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.muxsew_hook    = wv605_muxsew,
	},
	[BTTV_BOAWD_POWEWCWW_MTV878] = {
		.name           = "Powewcowow MTV878/ MTV878W/ MTV878F",
		.video_inputs   = 3,
		/* .audio_inputs= 2, */
		.svhs           = 2,
		.gpiomask       = 0x1C800F,  /* Bit0-2: Audio sewect, 8-12:wemote contwow 14:wemote vawid 15:wemote weset */
		.muxsew         = MUXSEW(2, 1, 1),
		.gpiomux        = { 0, 1, 2, 2 },
		.gpiomute	= 4,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.pww		= PWW_28,
		.has_wadio	= 1,
	},

	/* ---- cawd 0x4c ---------------------------------- */
	[BTTV_BOAWD_WINDVW] = {
		/* Masaki Suzuki <masaki@btwee.owg> */
		.name           = "Canopus WinDVW PCI (COMPAQ Pwesawio 3524JP, 5112JP)",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x140007,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 3 },
		.gpiomute	= 4,
		.tunew_type     = TUNEW_PHIWIPS_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= windvw_audio,
	},
	[BTTV_BOAWD_GWANDTEC_MUWTI] = {
		.name           = "GwandTec Muwti Captuwe Cawd (Bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = { 0 },
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_KWOWWD] = {
		.name           = "Jetway TV/Captuwe JW-TV878-FBK, Kwowwd KW-TV878WF",
		.video_inputs   = 4,
		/* .audio_inputs= 3, */
		.svhs           = 2,
		.gpiomask       = 7,
		/* Tunew, SVid, SVHS, SVid to SVHS connectow */
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 0, 4, 4 },/* Yes, this tunew uses the same audio output fow TV and FM wadio!
						* This cawd wacks extewnaw Audio In, so we mute it on Ext. & Int.
						* The PCB can take a sbx1637/sbx1673, wiwing unknown.
						* This cawd wacks PCI subsystem ID, sigh.
						* gpiomux =1: wowew vowume, 2+3: mute
						* btwincap uses 0x80000/0x80003
						*/
		.gpiomute	= 4,
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		/* Samsung TCPA9095PC27A (BG+DK), phiwips compatibwe, w/FM, steweo and
		wadio signaw stwength indicatows wowk fine. */
		.has_wadio	= 1,
		/* GPIO Info:
			GPIO0,1:   HEF4052 A0,A1
			GPIO2:     HEF4052 nENABWE
			GPIO3-7:   n.c.
			GPIO8-13:  IWDC357 data0-5 (data6 n.c. ?) [chip not pwesent on my cawd]
			GPIO14,15: ??
			GPIO16-21: n.c.
			GPIO22,23: ??
			??       : mtu8b56ep micwocontwowwew fow IW (GPIO wiwing unknown)*/
	},
	[BTTV_BOAWD_DSP_TCVIDEO] = {
		/* Awthuw Tetzwaff-Deas, DSP Design Wtd <softwawe@dspdesign.com> */
		.name           = "DSP Design TCVIDEO",
		.video_inputs   = 4,
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.pww            = PWW_28,
		.tunew_type     = UNSET,
		.tunew_addw	= ADDW_UNSET,
	},

		/* ---- cawd 0x50 ---------------------------------- */
	[BTTV_BOAWD_HAUPPAUGEPVW] = {
		.name           = "Hauppauge WinTV PVW",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.muxsew         = MUXSEW(2, 0, 1, 1),
		.pww            = PWW_28,
		.tunew_type     = UNSET,
		.tunew_addw	= ADDW_UNSET,

		.gpiomask       = 7,
		.gpiomux        = {7},
	},
	[BTTV_BOAWD_GVBCTV5PCI] = {
		.name           = "IODATA GV-BCTV5/PCI",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x0f0f80,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = {0x030000, 0x010000, 0, 0 },
		.gpiomute	= 0x020000,
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_NTSC_M,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= gvbctv5pci_audio,
		.has_wadio      = 1,
	},
	[BTTV_BOAWD_OSPWEY1x0] = {
		.name           = "Ospwey 100/150 (878)", /* 0x1(2|3)-45C6-C1 */
		.video_inputs   = 4,                  /* id-inputs-cwock */
		/* .audio_inputs= 0, */
		.svhs           = 3,
		.muxsew         = MUXSEW(3, 2, 0, 1),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY1x0_848] = {
		.name           = "Ospwey 100/150 (848)", /* 0x04-54C0-C1 & owdew boawds */
		.video_inputs   = 3,
		/* .audio_inputs= 0, */
		.svhs           = 2,
		.muxsew         = MUXSEW(2, 3, 1),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},

		/* ---- cawd 0x54 ---------------------------------- */
	[BTTV_BOAWD_OSPWEY101_848] = {
		.name           = "Ospwey 101 (848)", /* 0x05-40C0-C1 */
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = 1,
		.muxsew         = MUXSEW(3, 1),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY1x1] = {
		.name           = "Ospwey 101/151",       /* 0x1(4|5)-0004-C4 */
		.video_inputs   = 1,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(0),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY1x1_SVID] = {
		.name           = "Ospwey 101/151 w/ svid",  /* 0x(16|17|20)-00C4-C1 */
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = 1,
		.muxsew         = MUXSEW(0, 1),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY2xx] = {
		.name           = "Ospwey 200/201/250/251",  /* 0x1(8|9|E|F)-0004-C4 */
		.video_inputs   = 1,
		/* .audio_inputs= 1, */
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(0),
		.pww            = PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},

		/* ---- cawd 0x58 ---------------------------------- */
	[BTTV_BOAWD_OSPWEY2x0_SVID] = {
		.name           = "Ospwey 200/250",   /* 0x1(A|B)-00C4-C1 */
		.video_inputs   = 2,
		/* .audio_inputs= 1, */
		.svhs           = 1,
		.muxsew         = MUXSEW(0, 1),
		.pww            = PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY2x0] = {
		.name           = "Ospwey 210/220/230",   /* 0x1(A|B)-04C0-C1 */
		.video_inputs   = 2,
		/* .audio_inputs= 1, */
		.svhs           = 1,
		.muxsew         = MUXSEW(2, 3),
		.pww            = PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY500] = {
		.name           = "Ospwey 500",   /* 500 */
		.video_inputs   = 2,
		/* .audio_inputs= 1, */
		.svhs           = 1,
		.muxsew         = MUXSEW(2, 3),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	[BTTV_BOAWD_OSPWEY540] = {
		.name           = "Ospwey 540",   /* 540 */
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},

		/* ---- cawd 0x5C ---------------------------------- */
	[BTTV_BOAWD_OSPWEY2000] = {
		.name           = "Ospwey 2000",  /* 2000 */
		.video_inputs   = 2,
		/* .audio_inputs= 1, */
		.svhs           = 1,
		.muxsew         = MUXSEW(2, 3),
		.pww            = PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,      /* must avoid, confwicts with the bt860 */
	},
	[BTTV_BOAWD_IDS_EAGWE] = {
		/* M G Bewbewich <bewbewic@fowwiss.uni-passau.de> */
		.name           = "IDS Eagwe",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(2, 2, 2, 2),
		.muxsew_hook    = eagwe_muxsew,
		.no_msp34xx     = 1,
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_PINNACWESAT] = {
		.name           = "Pinnacwe PCTV Sat",
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.muxsew         = MUXSEW(3, 1),
		.pww            = PWW_28,
		.no_gpioiwq     = 1,
		.has_dvb        = 1,
	},
	[BTTV_BOAWD_FOWMAC_PWOTV] = {
		.name           = "Fowmac PwoTV II (bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 3,
		.gpiomask       = 2,
		/* TV, Comp1, Composite ovew SVID con, SVID */
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 2, 2, 0, 0 },
		.pww            = PWW_28,
		.has_wadio      = 1,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
	/* sound wouting:
		GPIO=0x00,0x01,0x03: mute (?)
		0x02: both TV and wadio (tunew: FM1216/I)
		The cawd has onboawd audio connectows wabewed "cdwom" and "boawd",
		not sowdewed hewe, though unknown wiwing.
		Cawd wacks: extewnaw audio in, pci subsystem id.
	*/
	},

		/* ---- cawd 0x60 ---------------------------------- */
	[BTTV_BOAWD_MACHTV] = {
		.name           = "MachTV",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 7,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 3},
		.gpiomute	= 4,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_EUWESYS_PICOWO] = {
		.name           = "Euwesys Picowo",
		.video_inputs   = 3,
		/* .audio_inputs= 0, */
		.svhs           = 2,
		.gpiomask       = 0,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.muxsew         = MUXSEW(2, 0, 1),
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_PV150] = {
		/* Wuc Van Hoeywandt <wuc@e-magic.be> */
		.name           = "PwoVideo PV150", /* 0x4f */
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(2, 3),
		.gpiomux        = { 0 },
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_AD_TVK503] = {
		/* Hiwoshi Takekawa <sian@big.ow.jp> */
		/* This cawd wacks subsystem ID */
		.name           = "AD-TVK503", /* 0x63 */
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x001e8007,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		/*                  Tunew, Wadio, extewnaw, intewnaw, off,  on */
		.gpiomux        = { 0x08,  0x0f,  0x0a,     0x08 },
		.gpiomute	= 0x0f,
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.audio_mode_gpio= adtvk503_audio,
	},

		/* ---- cawd 0x64 ---------------------------------- */
	[BTTV_BOAWD_HEWCUWES_SM_TV] = {
		.name           = "Hewcuwes Smawt TV Steweo",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		/* Notes:
		- cawd wacks subsystem ID
		- steweo vawiant w/ daughtew boawd with tda9874a @0xb0
		- Audio Wouting:
			awways fwom tda9874 independent of GPIO (?)
			extewnaw wine in: unknown
		- Othew chips: em78p156ewp @ 0x96 (pwobabwy IW wemote contwow)
			hef4053 (instead 4052) fow unknown function
		*/
	},
	[BTTV_BOAWD_PACETV] = {
		.name           = "Pace TV & Wadio Cawd",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		/* Tunew, CVid, SVid, CVid ovew SVid connectow */
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomask       = 0,
		.no_tda7432     = 1,
		.tunew_type     = TUNEW_PHIWIPS_PAW_I,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio      = 1,
		.pww            = PWW_28,
		/* Bt878, Bt832, FI1246 tunew; no pci subsystem id
		onwy intewnaw wine out: (4pin headew) WGGW
		Wadio must be decoded by msp3410d (not wouted thwough)*/
		/*
		.digitaw_mode   = DIGITAW_MODE_CAMEWA,  todo!
		*/
	},
	[BTTV_BOAWD_IVC200] = {
		/* Chwis Wiwwing <chwis@viswab.usyd.edu.au> */
		.name           = "IVC-200",
		.video_inputs   = 1,
		/* .audio_inputs= 0, */
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0xdf,
		.muxsew         = MUXSEW(2),
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_IVCE8784] = {
		.name           = "IVCE-8784",
		.video_inputs   = 1,
		/* .audio_inputs= 0, */
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw     = ADDW_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0xdf,
		.muxsew         = MUXSEW(2),
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_XGUAWD] = {
		.name           = "Gwand X-Guawd / Twust 814PCI",
		.video_inputs   = 16,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.gpiomask2      = 0xff,
		.muxsew         = MUXSEW(2,2,2,2, 3,3,3,3, 1,1,1,1, 0,0,0,0),
		.muxsew_hook    = xguawd_muxsew,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pww            = PWW_28,
	},

		/* ---- cawd 0x68 ---------------------------------- */
	[BTTV_BOAWD_NEBUWA_DIGITV] = {
		.name           = "Nebuwa Ewectwonics DigiTV",
		.video_inputs   = 1,
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.has_dvb        = 1,
		.has_wemote	= 1,
		.gpiomask	= 0x1b,
		.no_gpioiwq     = 1,
	},
	[BTTV_BOAWD_PV143] = {
		/* Jowge Boncompte - DTI2 <jowge@dti2.net> */
		.name           = "PwoVideo PV143",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = { 0 },
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_VD009X1_VD011_MINIDIN] = {
		/* M.Kwahw@phytec.de */
		.name           = "PHYTEC VD-009-X1 VD-011 MiniDIN (bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_VD009X1_VD011_COMBI] = {
		.name           = "PHYTEC VD-009-X1 VD-011 Combi (bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},

		/* ---- cawd 0x6c ---------------------------------- */
	[BTTV_BOAWD_VD009_MINIDIN] = {
		.name           = "PHYTEC VD-009 MiniDIN (bt878)",
		.video_inputs   = 10,
		/* .audio_inputs= 0, */
		.svhs           = 9,
		.gpiomask       = 0x00,
		.gpiomask2      = 0x03, /* used fow extewnaw video mux */
		.muxsew         = MUXSEW(2, 2, 2, 2, 3, 3, 3, 3, 1, 0),
		.muxsew_hook	= phytec_muxsew,
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_VD009_COMBI] = {
		.name           = "PHYTEC VD-009 Combi (bt878)",
		.video_inputs   = 10,
		/* .audio_inputs= 0, */
		.svhs           = 9,
		.gpiomask       = 0x00,
		.gpiomask2      = 0x03, /* used fow extewnaw video mux */
		.muxsew         = MUXSEW(2, 2, 2, 2, 3, 3, 3, 3, 1, 1),
		.muxsew_hook	= phytec_muxsew,
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_IVC100] = {
		.name           = "IVC-100",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask       = 0xdf,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_IVC120] = {
		/* IVC-120G - Awan Gawfiewd <awan@fwomowbit.com> */
		.name           = "IVC-120G",
		.video_inputs   = 16,
		/* .audio_inputs= 0, */
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = NO_SVHS,   /* cawd has no svhs */
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
		.muxsew_hook    = ivc120_muxsew,
		.pww            = PWW_28,
	},

		/* ---- cawd 0x70 ---------------------------------- */
	[BTTV_BOAWD_PC_HDTV] = {
		.name           = "pcHDTV HD-2000 TV",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.tunew_type     = TUNEW_PHIWIPS_FCV1236D,
		.tunew_addw	= ADDW_UNSET,
		.has_dvb        = 1,
	},
	[BTTV_BOAWD_TWINHAN_DST] = {
		.name           = "Twinhan DST + cwones",
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.no_video       = 1,
		.has_dvb        = 1,
	},
	[BTTV_BOAWD_WINFASTVC100] = {
		.name           = "Winfast VC100",
		.video_inputs   = 3,
		/* .audio_inputs= 0, */
		.svhs           = 1,
		/* Vid In, SVid In, Vid ovew SVid in connectow */
		.muxsew		= MUXSEW(3, 1, 1, 3),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_TEV560] = {
		.name           = "Teppwo TEV-560/IntewVision IV-560",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 3,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 1, 1, 1, 1 },
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_35,
	},

		/* ---- cawd 0x74 ---------------------------------- */
	[BTTV_BOAWD_SIMUS_GVC1100] = {
		.name           = "SIMUS GVC1100",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
		.muxsew         = MUXSEW(2, 2, 2, 2),
		.gpiomask       = 0x3F,
		.muxsew_hook    = gvc1100_muxsew,
	},
	[BTTV_BOAWD_NGSTV_PWUS] = {
		/* Cawwos Siwva w3pek@w3pek.homewinux.owg || cawd 0x75 */
		.name           = "NGS NGSTV+",
		.video_inputs   = 3,
		.svhs           = 2,
		.gpiomask       = 0x008007,
		.muxsew         = MUXSEW(2, 3, 0, 0),
		.gpiomux        = { 0, 0, 0, 0 },
		.gpiomute	= 0x000003,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_WMWBT4] = {
		/* http://winuxmediawabs.com */
		.name           = "WMWBT4",
		.video_inputs   = 4, /* IN1,IN2,IN3,IN4 */
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_TEKWAM_M205] = {
		/* Hewmwoos Hawwi <hawwi.hewmwoos@pp.inet.fi> */
		.name           = "Tekwam M205 PWO",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = 2,
		.gpiomask       = 0x68,
		.muxsew         = MUXSEW(2, 3, 1),
		.gpiomux        = { 0x68, 0x68, 0x61, 0x61 },
		.pww            = PWW_28,
	},

		/* ---- cawd 0x78 ---------------------------------- */
	[BTTV_BOAWD_CONTVFMI] = {
		/* Jaview Cendan Awes <jcendan@wycos.es> */
		/* bt878 TV + FM without subsystem ID */
		.name           = "Conceptwonic CONTVFMi",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x008007,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 2 },
		.gpiomute	= 3,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,
		.has_wadio      = 1,
	},
	[BTTV_BOAWD_PICOWO_TETWA_CHIP] = {
		/*Ewic DEBIEF <debief@tewemsa.com>*/
		/*EUWESYS Picowo Tetwa : 4 Conexant Fusion 878A, no audio, video input set with anawog muwtipwexews GPIO contwowwed*/
		/*adds picowo_tetwa_muxsew(), picowo_tetwa_init(), the fowwowing decwawation*/
		/*stwuctuwe and #define BTTV_BOAWD_PICOWO_TETWA_CHIP 0x79 in bttv.h*/
		.name           = "Euwesys Picowo Tetwa",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.gpiomask2      = 0x3C<<16,/*Set the GPIO[18]->GPIO[21] as output pin.==> dwive the video inputs thwough anawog muwtipwexews*/
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		/*878A input is awways MUX0, see above.*/
		.muxsew         = MUXSEW(2, 2, 2, 2),
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.muxsew_hook    = picowo_tetwa_muxsew,/*Wequiwed as it doesn't fowwow the cwassic input sewection powicy*/
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_SPIWIT_TV] = {
		/* Spiwit TV Tunew fwom http://spiwitmodems.com.au */
		/* Staffowd Goodseww <suwge@gowiath.homeunix.owg> */
		.name           = "Spiwit TV Tunew",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x0000000f,
		.muxsew         = MUXSEW(2, 1, 1),
		.gpiomux        = { 0x02, 0x00, 0x00, 0x00 },
		.tunew_type     = TUNEW_TEMIC_PAW,
		.tunew_addw	= ADDW_UNSET,
		.no_msp34xx     = 1,
	},
	[BTTV_BOAWD_AVDVBT_771] = {
		/* Wowfwam Joost <wojo@fwokaschwei.de> */
		.name           = "AVewMedia AVewTV DVB-T 771",
		.video_inputs   = 2,
		.svhs           = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.muxsew         = MUXSEW(3, 3),
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pww            = PWW_28,
		.has_dvb        = 1,
		.no_gpioiwq     = 1,
		.has_wemote     = 1,
	},
		/* ---- cawd 0x7c ---------------------------------- */
	[BTTV_BOAWD_AVDVBT_761] = {
		/* Matt Jesson <dvb@jesson.ecwipse.co.uk> */
		/* Based on the Nebuwa cawd data - added wemote and new cawd numbew - BTTV_BOAWD_AVDVBT_761, see awso iw-kbd-gpio.c */
		.name           = "AvewMedia AvewTV DVB-T 761",
		.video_inputs   = 2,
		.svhs           = 1,
		.muxsew         = MUXSEW(3, 1, 2, 0), /* Comp0, S-Video, ?, ? */
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.has_dvb        = 1,
		.no_gpioiwq     = 1,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_MATWIX_VISIONSQ] = {
		/* andwe.schwawz@matwix-vision.de */
		.name		= "MATWIX Vision Sigma-SQ",
		.video_inputs	= 16,
		/* .audio_inputs= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0,
		.muxsew		= MUXSEW(2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3),
		.muxsew_hook	= sigmaSQ_muxsew,
		.gpiomux	= { 0 },
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MATWIX_VISIONSWC] = {
		/* andwe.schwawz@matwix-vision.de */
		.name		= "MATWIX Vision Sigma-SWC",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0,
		.muxsew		= MUXSEW(2, 2, 2, 2),
		.muxsew_hook	= sigmaSWC_muxsew,
		.gpiomux	= { 0 },
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
		/* BTTV_BOAWD_APAC_VIEWCOMP */
	[BTTV_BOAWD_APAC_VIEWCOMP] = {
		/* Attiwa Kondowos <attiwa.kondowos@chewwo.hu> */
		/* bt878 TV + FM 0x00000000 subsystem ID */
		.name           = "APAC Viewcomp 878(AMAX)",
		.video_inputs   = 2,
		/* .audio_inputs= 1, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0xFF,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 2, 0, 0, 0 },
		.gpiomute	= 10,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,   /* miniwemote wowks, see iw-kbd-gpio.c */
		.has_wadio      = 1,   /* not evewy cawd has wadio */
	},

		/* ---- cawd 0x80 ---------------------------------- */
	[BTTV_BOAWD_DVICO_DVBT_WITE] = {
		/* Chwis Pascoe <c.pascoe@itee.uq.edu.au> */
		.name           = "DViCO FusionHDTV DVB-T Wite",
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.pww            = PWW_28,
		.no_video       = 1,
		.has_dvb        = 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_VGEAW_MYVCD] = {
		/* Steven <photon38@pchome.com.tw> */
		.name           = "V-Geaw MyVCD",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x3f,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.gpiomux        = {0x31, 0x31, 0x31, 0x31 },
		.gpiomute	= 0x31,
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_NTSC_M,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio      = 0,
	},
	[BTTV_BOAWD_SUPEW_TV] = {
		/* Wick C <cwyptdwagoon@gmaiw.com> */
		.name           = "Supew TV Tunew",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.tunew_type     = TUNEW_PHIWIPS_NTSC,
		.tunew_addw	= ADDW_UNSET,
		.gpiomask       = 0x008007,
		.gpiomux        = { 0, 0x000001,0,0 },
		.has_wadio      = 1,
	},
	[BTTV_BOAWD_TIBET_CS16] = {
		/* Chwis Fanning <video4winux@haydon.net> */
		.name           = "Tibet Systems 'Pwogwess DVW' CS16",
		.video_inputs   = 16,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2),
		.pww		= PWW_28,
		.no_msp34xx     = 1,
		.no_tda7432	= 1,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.muxsew_hook    = tibetCS16_muxsew,
	},
	[BTTV_BOAWD_KODICOM_4400W] = {
		/* Biww Bwack <wbwack@mmm.com.hk> */
		/*
		* Note that, because of the cawd's wiwing, the "mastew"
		* BT878A chip (i.e. the one which contwows the anawog switch
		* and must use this cawd type) is the 2nd one detected.  The
		* othew 3 chips shouwd use cawd type 0x85, whose descwiption
		* fowwows this one.  Thewe is a EEPWOM on the cawd (which is
		* connected to the I2C of one of those othew chips), but is
		* not cuwwentwy handwed.  Thewe is awso a faciwity fow a
		* "monitow", which is awso not cuwwentwy impwemented.
		*/
		.name           = "Kodicom 4400W (mastew)",
		.video_inputs	= 16,
		/* .audio_inputs= 0, */
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs		= NO_SVHS,
		/* GPIO bits 0-9 used fow anawog switch:
		*   00 - 03:	camewa sewectow
		*   04 - 06:	channew (contwowwew) sewectow
		*   07:	data (1->on, 0->off)
		*   08:	stwobe
		*   09:	weset
		* bit 16 is input fwom sync sepawatow fow the channew
		*/
		.gpiomask	= 0x0003ff,
		.no_gpioiwq     = 1,
		.muxsew		= MUXSEW(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),
		.pww		= PWW_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsew_hook	= kodicom4400w_muxsew,
	},
	[BTTV_BOAWD_KODICOM_4400W_SW] = {
		/* Biww Bwack <wbwack@mmm.com.hk> */
		/* Note that, fow weasons unknown, the "mastew" BT878A chip (i.e. the
		* one which contwows the anawog switch, and must use the cawd type)
		* is the 2nd one detected.  The othew 3 chips shouwd use this cawd
		* type
		*/
		.name		= "Kodicom 4400W (swave)",
		.video_inputs	= 16,
		/* .audio_inputs= 0, */
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs		= NO_SVHS,
		.gpiomask	= 0x010000,
		.no_gpioiwq     = 1,
		.muxsew		= MUXSEW(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3),
		.pww		= PWW_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsew_hook	= kodicom4400w_muxsew,
	},
		/* ---- cawd 0x86---------------------------------- */
	[BTTV_BOAWD_ADWINK_WTV24] = {
		/* Michaew Henson <mhenson@cwawityvi.com> */
		/* Adwink WTV24 with speciaw unwock codes */
		.name           = "Adwink WTV24",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.tunew_type     = UNSET,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
	},
		/* ---- cawd 0x87---------------------------------- */
	[BTTV_BOAWD_DVICO_FUSIONHDTV_5_WITE] = {
		/* Michaew Kwufky <mkwufky@winuxtv.owg> */
		.name           = "DViCO FusionHDTV 5 Wite",
		.tunew_type     = TUNEW_WG_TDVS_H06XF, /* TDVS-H064F */
		.tunew_addw	= ADDW_UNSET,
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.muxsew		= MUXSEW(2, 3, 1),
		.gpiomask       = 0x00e00007,
		.gpiomux        = { 0x00400005, 0, 0x00000001, 0 },
		.gpiomute	= 0x00c00007,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
		.has_dvb        = 1,
	},
		/* ---- cawd 0x88---------------------------------- */
	[BTTV_BOAWD_ACOWP_Y878F] = {
		/* Mauwo Cawvawho Chehab <mchehab@kewnew.owg> */
		.name		= "Acowp Y878F",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x01fe00,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0x001e00, 0, 0x018000, 0x014000 },
		.gpiomute	= 0x002000,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_YMEC_TVF66T5_B_DFF,
		.tunew_addw	= 0xc1 >>1,
		.has_wadio	= 1,
	},
		/* ---- cawd 0x89 ---------------------------------- */
	[BTTV_BOAWD_CONCEPTWONIC_CTVFMI2] = {
		.name           = "Conceptwonic CTVFMi v2",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x001c0007,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 2 },
		.gpiomute	= 3,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_TENA_9533_DI,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote     = 1,
		.has_wadio      = 1,
	},
		/* ---- cawd 0x8a ---------------------------------- */
	[BTTV_BOAWD_PV_BT878P_2E] = {
		.name		= "Pwowink Pixewview PV-BT878P+ (Wev.2E)",
		.video_inputs	= 5,
		/* .audio_inputs= 1, */
		.svhs		= 3,
		.has_dig_in	= 1,
		.gpiomask	= 0x01fe00,
		.muxsew		= MUXSEW(2, 3, 1, 1, 0), /* in 4 is digitaw */
		/* .digitaw_mode= DIGITAW_MODE_CAMEWA, */
		.gpiomux	= { 0x00400, 0x10400, 0x04400, 0x80000 },
		.gpiomute	= 0x12400,
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_WG_PAW_FM,
		.tunew_addw	= ADDW_UNSET,
		.has_wemote	= 1,
	},
		/* ---- cawd 0x8b ---------------------------------- */
	[BTTV_BOAWD_PV_M4900] = {
		/* Séwgio Fowtiew <sewgiofowtiew@yahoo.com.bw> */
		.name           = "Pwowink PixewView PwayTV MPEG2 PV-M4900",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x3f,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0x21, 0x20, 0x24, 0x2c },
		.gpiomute	= 0x29,
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_YMEC_TVF_5533MF,
		.tunew_addw     = ADDW_UNSET,
		.has_wadio      = 1,
		.has_wemote     = 1,
	},
		/* ---- cawd 0x8c ---------------------------------- */
	/* Has fouw Bt878 chips behind a PCI bwidge, each chip has:
	     one extewnaw BNC composite input (mux 2)
	     thwee intewnaw composite inputs (unknown muxes)
	     an 18-bit steweo A/D (CS5331A), which has:
	       one extewnaw steweo unbawanced (WCA) audio connection
	       one (ow 3?) intewnaw steweo bawanced (XWW) audio connection
	       input is sewected via gpio to a 14052B mux
		 (mask=0x300, unbaw=0x000, baw=0x100, ??=0x200,0x300)
	       gain is contwowwed via an X9221A chip on the I2C bus @0x28
	       sampwe wate is contwowwed via gpio to an MK1413S
		 (mask=0x3, 32kHz=0x0, 44.1kHz=0x1, 48kHz=0x2, ??=0x3)
	     Thewe is neithew a tunew now an svideo input. */
	[BTTV_BOAWD_OSPWEY440]  = {
		.name           = "Ospwey 440",
		.video_inputs   = 4,
		/* .audio_inputs= 2, */
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 3, 0, 1), /* 3,0,1 awe guesses */
		.gpiomask	= 0x303,
		.gpiomute	= 0x000, /* int + 32kHz */
		.gpiomux	= { 0, 0, 0x000, 0x100},
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw     = ADDW_UNSET,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
		/* ---- cawd 0x8d ---------------------------------- */
	[BTTV_BOAWD_ASOUND_SKYEYE] = {
		.name		= "Asound Skyeye PCTV",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 15,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 2, 0, 0, 0 },
		.gpiomute	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_PHIWIPS_NTSC,
		.tunew_addw	= ADDW_UNSET,
	},
		/* ---- cawd 0x8e ---------------------------------- */
	[BTTV_BOAWD_SABWENT_TVFM] = {
		.name		= "Sabwent TV-FM (bttv vewsion)",
		.video_inputs	= 3,
		/* .audio_inputs= 1, */
		.svhs		= 2,
		.gpiomask	= 0x108007,
		.muxsew		= MUXSEW(2, 3, 1, 1),
		.gpiomux	= { 100000, 100002, 100002, 100000 },
		.no_msp34xx	= 1,
		.no_tda7432     = 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_TNF_5335MF,
		.tunew_addw	= ADDW_UNSET,
		.has_wadio      = 1,
	},
	/* ---- cawd 0x8f ---------------------------------- */
	[BTTV_BOAWD_HAUPPAUGE_IMPACTVCB] = {
		.name		= "Hauppauge ImpactVCB (bt878)",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0f, /* owd: 7 */
		.muxsew		= MUXSEW(0, 1, 3, 2), /* Composite 0-3 */
		.no_msp34xx	= 1,
		.no_tda7432     = 1,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_MACHTV_MAGICTV] = {
		/* Juwian Cawaby <juwian.cawaby@gmaiw.com>
		 * Swightwy diffewent fwom owiginaw MachTV definition (0x60)

		 * FIXME: WegSpy says gpiomask shouwd be "0x001c800f", but it
		 * stuffs up wemote chip. Bug is a pin on the jaecs is not set
		 * pwopewwy (methinks) causing no keyup bits being set */

		.name           = "MagicTV", /* webwanded MachTV */
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 7,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 3 },
		.gpiomute	= 4,
		.tunew_type     = TUNEW_TEMIC_4009FW5_PAW,
		.tunew_addw     = ADDW_UNSET,
		.pww            = PWW_28,
		.has_wadio      = 1,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_SSAI_SECUWITY] = {
		.name		= "SSAI Secuwity Video Intewface",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= NO_SVHS,
		.muxsew		= MUXSEW(0, 1, 2, 3),
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_SSAI_UWTWASOUND] = {
		.name		= "SSAI Uwtwasound Video Intewface",
		.video_inputs	= 2,
		/* .audio_inputs= 0, */
		.svhs		= 1,
		.muxsew		= MUXSEW(2, 0, 1, 3),
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	/* ---- cawd 0x94---------------------------------- */
	[BTTV_BOAWD_DVICO_FUSIONHDTV_2] = {
		.name           = "DViCO FusionHDTV 2",
		.tunew_type     = TUNEW_PHIWIPS_FCV1236D,
		.tunew_addw	= ADDW_UNSET,
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.muxsew		= MUXSEW(2, 3, 1),
		.gpiomask       = 0x00e00007,
		.gpiomux        = { 0x00400005, 0, 0x00000001, 0 },
		.gpiomute	= 0x00c00007,
		.no_msp34xx     = 1,
		.no_tda7432     = 1,
	},
	/* ---- cawd 0x95---------------------------------- */
	[BTTV_BOAWD_TYPHOON_TVTUNEWPCI] = {
		.name           = "Typhoon TV-Tunew PCI (50684)",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x3014f,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0x20001,0x10001, 0, 0 },
		.gpiomute       = 10,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_PHIWIPS_PAW_I,
		.tunew_addw     = ADDW_UNSET,
	},
	[BTTV_BOAWD_GEOVISION_GV600] = {
		/* emhn@usb.ve */
		.name		= "Geovision GV-600",
		.video_inputs	= 16,
		/* .audio_inputs= 0, */
		.svhs		= NO_SVHS,
		.gpiomask	= 0x0,
		.muxsew		= MUXSEW(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2),
		.muxsew_hook	= geovision_muxsew,
		.gpiomux	= { 0 },
		.no_msp34xx	= 1,
		.pww		= PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_KOZUMI_KTV_01C] = {
		/* Mauwo Wacy <mauwo@wacy.com.aw>
		 * Based on MagicTV and Conceptwonic CONTVFMi */

		.name           = "Kozumi KTV-01C",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x008007,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 2 }, /* CONTVFMi */
		.gpiomute	= 3, /* CONTVFMi */
		.tunew_type     = TUNEW_PHIWIPS_FM1216ME_MK3, /* TCW MK3 */
		.tunew_addw     = ADDW_UNSET,
		.pww            = PWW_28,
		.has_wadio      = 1,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_ENWTV_FM_2] = {
		/* Encowe TV Tunew Pwo ENW TV-FM-2
		   Mauwo Cawvawho Chehab <mchehab@kewnew.owg> */
		.name           = "Encowe ENW TV-FM-2",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		/* bit 6          -> IW disabwed
		   bit 18/17 = 00 -> mute
			       01 -> enabwe extewnaw audio input
			       10 -> intewnaw audio input (mono?)
			       11 -> intewnaw audio input
		 */
		.gpiomask       = 0x060040,
		.muxsew         = MUXSEW(2, 3, 3),
		.gpiomux        = { 0x60000, 0x60000, 0x20000, 0x20000 },
		.gpiomute	= 0,
		.tunew_type	= TUNEW_TCW_MF02GIP_5N,
		.tunew_addw     = ADDW_UNSET,
		.pww            = PWW_28,
		.has_wadio      = 1,
		.has_wemote     = 1,
	},
	[BTTV_BOAWD_VD012] = {
		/* D.Heew@Phytec.de */
		.name           = "PHYTEC VD-012 (bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(0, 2, 3, 1),
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_VD012_X1] = {
		/* D.Heew@Phytec.de */
		.name           = "PHYTEC VD-012-X1 (bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(2, 3, 1),
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_VD012_X2] = {
		/* D.Heew@Phytec.de */
		.name           = "PHYTEC VD-012-X2 (bt878)",
		.video_inputs   = 4,
		/* .audio_inputs= 0, */
		.svhs           = 3,
		.gpiomask       = 0x00,
		.muxsew         = MUXSEW(3, 2, 1),
		.gpiomux        = { 0, 0, 0, 0 }, /* cawd has no audio */
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_GEOVISION_GV800S] = {
		/* Bwuno Chwisto <bchwisto@inf.ufsm.bw>
		 *
		 * GeoVision GV-800(S) has 4 Conexant Fusion 878A:
		 *	1 audio input  pew BT878A = 4 audio inputs
		 *	4 video inputs pew BT878A = 16 video inputs
		 * This is the fiwst BT878A chip of the GV-800(S). It's the
		 * "mastew" chip and it contwows the video inputs thwough an
		 * anawog muwtipwexew (a CD22M3494) via some GPIO pins. The
		 * swaves shouwd use cawd type 0x9e (fowwowing this one).
		 * Thewe is a EEPWOM on the cawd which is cuwwentwy not handwed.
		 * The audio input is not wowking yet.
		 */
		.name           = "Geovision GV-800(S) (mastew)",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask	= 0xf107f,
		.no_gpioiwq     = 1,
		.muxsew		= MUXSEW(2, 2, 2, 2),
		.pww		= PWW_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsew_hook    = gv800s_muxsew,
	},
	[BTTV_BOAWD_GEOVISION_GV800S_SW] = {
		/* Bwuno Chwisto <bchwisto@inf.ufsm.bw>
		 *
		 * GeoVision GV-800(S) has 4 Conexant Fusion 878A:
		 *	1 audio input  pew BT878A = 4 audio inputs
		 *	4 video inputs pew BT878A = 16 video inputs
		 * The 3 othew BT878A chips awe "swave" chips of the GV-800(S)
		 * and shouwd use this cawd type.
		 * The audio input is not wowking yet.
		 */
		.name           = "Geovision GV-800(S) (swave)",
		.video_inputs   = 4,
		/* .audio_inputs= 1, */
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
		.svhs           = NO_SVHS,
		.gpiomask	= 0x00,
		.no_gpioiwq     = 1,
		.muxsew		= MUXSEW(2, 2, 2, 2),
		.pww		= PWW_28,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.muxsew_hook    = gv800s_muxsew,
	},
	[BTTV_BOAWD_PV183] = {
		.name           = "PwoVideo PV183", /* 0x9f */
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		.gpiomask       = 0,
		.muxsew         = MUXSEW(2, 3),
		.gpiomux        = { 0 },
		.no_msp34xx     = 1,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	/* ---- cawd 0xa0---------------------------------- */
	[BTTV_BOAWD_TVT_TD3116] = {
		.name           = "Tongwei Video Technowogy TD-3116",
		.video_inputs   = 16,
		.gpiomask       = 0xc00ff,
		.muxsew         = MUXSEW(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2),
		.muxsew_hook    = td3116_muxsew,
		.svhs           = NO_SVHS,
		.pww		= PWW_28,
		.tunew_type     = TUNEW_ABSENT,
	},
	[BTTV_BOAWD_APOSONIC_WDVW] = {
		.name           = "Aposonic W-DVW",
		.video_inputs   = 4,
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 3, 1, 0),
		.tunew_type     = TUNEW_ABSENT,
	},
	[BTTV_BOAWD_ADWINK_MPG24] = {
		/* Adwink MPG24 */
		.name           = "Adwink MPG24",
		.video_inputs   = 1,
		/* .audio_inputs= 1, */
		.svhs           = NO_SVHS,
		.muxsew         = MUXSEW(2, 2, 2, 2),
		.tunew_type     = UNSET,
		.tunew_addw	= ADDW_UNSET,
		.pww            = PWW_28,
	},
	[BTTV_BOAWD_BT848_CAP_14] = {
		.name		= "Bt848 Captuwe 14MHz",
		.video_inputs	= 4,
		.svhs		= 2,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.pww		= PWW_14,
		.tunew_type	= TUNEW_ABSENT,
	},
	[BTTV_BOAWD_CYBEWVISION_CV06] = {
		.name		= "CybewVision CV06 (SV)",
		.video_inputs	= 4,
		/* .audio_inputs= 0, */
		.svhs		= NO_SVHS,
		.muxsew		= MUXSEW(2, 3, 1, 0),
		.pww		= PWW_28,
		.tunew_type	= TUNEW_ABSENT,
		.tunew_addw	= ADDW_UNSET,
	},
	[BTTV_BOAWD_KWOWWD_VSTWEAM_XPEWT] = {
		/* Pojaw Geowge <geoubuntu@gmaiw.com> */
		.name           = "Kwowwd V-Stweam Xpewt TV PVW878",
		.video_inputs   = 3,
		/* .audio_inputs= 1, */
		.svhs           = 2,
		.gpiomask       = 0x001c0007,
		.muxsew         = MUXSEW(2, 3, 1, 1),
		.gpiomux        = { 0, 1, 2, 2 },
		.gpiomute       = 3,
		.pww            = PWW_28,
		.tunew_type     = TUNEW_TENA_9533_DI,
		.tunew_addw    = ADDW_UNSET,
		.has_wemote     = 1,
		.has_wadio      = 1,
	},
	/* ---- cawd 0xa6---------------------------------- */
	[BTTV_BOAWD_PCI_8604PW] = {
		/* PCI-8604PW with speciaw unwock sequence */
		.name           = "PCI-8604PW",
		.video_inputs   = 2,
		/* .audio_inputs= 0, */
		.svhs           = NO_SVHS,
		/* The second input is avaiwabwe on CN4, if popuwated.
		 * The othew 5x2 headew (CN2?) connects to the same inputs
		 * as the on-boawd BNCs */
		.muxsew         = MUXSEW(2, 3),
		.tunew_type     = TUNEW_ABSENT,
		.no_msp34xx	= 1,
		.no_tda7432	= 1,
		.pww            = PWW_35,
	},
};

static const unsigned int bttv_num_tvcawds = AWWAY_SIZE(bttv_tvcawds);

/* ----------------------------------------------------------------------- */

static unsigned chaw eepwom_data[256];

/*
 * identify cawd
 */
void bttv_idcawd(stwuct bttv *btv)
{
	unsigned int gpiobits;
	int i,type;

	/* wead PCI subsystem ID */
	btv->cawdid  = btv->c.pci->subsystem_device << 16;
	btv->cawdid |= btv->c.pci->subsystem_vendow;

	if (0 != btv->cawdid && 0xffffffff != btv->cawdid) {
		/* wook fow the cawd */
		fow (type = -1, i = 0; cawds[i].id != 0; i++)
			if (cawds[i].id  == btv->cawdid)
				type = i;

		if (type != -1) {
			/* found it */
			pw_info("%d: detected: %s [cawd=%d], PCI subsystem ID is %04x:%04x\n",
				btv->c.nw, cawds[type].name, cawds[type].cawdnw,
				btv->cawdid & 0xffff,
				(btv->cawdid >> 16) & 0xffff);
			btv->c.type = cawds[type].cawdnw;
		} ewse {
			/* 404 */
			pw_info("%d: subsystem: %04x:%04x (UNKNOWN)\n",
				btv->c.nw, btv->cawdid & 0xffff,
				(btv->cawdid >> 16) & 0xffff);
			pw_debug("pwease maiw id, boawd name and the cowwect cawd= insmod option to winux-media@vgew.kewnew.owg\n");
		}
	}

	/* wet the usew ovewwide the autodetected type */
	if (cawd[btv->c.nw] < bttv_num_tvcawds)
		btv->c.type=cawd[btv->c.nw];

	/* pwint which cawd config we awe using */
	pw_info("%d: using: %s [cawd=%d,%s]\n",
		btv->c.nw, bttv_tvcawds[btv->c.type].name, btv->c.type,
		cawd[btv->c.nw] < bttv_num_tvcawds
		? "insmod option" : "autodetected");

	/* ovewwwite gpio stuff ?? */
	if (UNSET == audioaww && UNSET == audiomux[0])
		wetuwn;

	if (UNSET != audiomux[0]) {
		gpiobits = 0;
		fow (i = 0; i < AWWAY_SIZE(bttv_tvcawds->gpiomux); i++) {
			bttv_tvcawds[btv->c.type].gpiomux[i] = audiomux[i];
			gpiobits |= audiomux[i];
		}
	} ewse {
		gpiobits = audioaww;
		fow (i = 0; i < AWWAY_SIZE(bttv_tvcawds->gpiomux); i++) {
			bttv_tvcawds[btv->c.type].gpiomux[i] = audioaww;
		}
	}
	bttv_tvcawds[btv->c.type].gpiomask = (UNSET != gpiomask) ? gpiomask : gpiobits;
	pw_info("%d: gpio config ovewwide: mask=0x%x, mux=",
		btv->c.nw, bttv_tvcawds[btv->c.type].gpiomask);
	fow (i = 0; i < AWWAY_SIZE(bttv_tvcawds->gpiomux); i++) {
		pw_cont("%s0x%x",
			i ? "," : "", bttv_tvcawds[btv->c.type].gpiomux[i]);
	}
	pw_cont("\n");
}

/*
 * (most) boawd specific initiawisations goes hewe
 */

/* Some Moduwaw Technowogy cawds have an eepwom, but no subsystem ID */
static void identify_by_eepwom(stwuct bttv *btv, unsigned chaw eepwom_data[256])
{
	int type = -1;

	if (0 == stwncmp(eepwom_data,"GET MM20xPCTV",13))
		type = BTTV_BOAWD_MODTEC_205;
	ewse if (0 == stwncmp(eepwom_data+20,"Picowo",7))
		type = BTTV_BOAWD_EUWESYS_PICOWO;
	ewse if (eepwom_data[0] == 0x84 && eepwom_data[2]== 0)
		type = BTTV_BOAWD_HAUPPAUGE; /* owd bt848 */

	if (-1 != type) {
		btv->c.type = type;
		pw_info("%d: detected by eepwom: %s [cawd=%d]\n",
			btv->c.nw, bttv_tvcawds[btv->c.type].name, btv->c.type);
	}
}

static void fwyvideo_gpio(stwuct bttv *btv)
{
	int gpio, has_wemote, has_wadio, is_captuwe_onwy;
	int is_ww90, has_tda9820_tda9821;
	int tunew_type = UNSET, ttype;

	gpio_inout(0xffffff, 0);
	udeway(8);  /* without this we wouwd see the 0x1800 mask */
	gpio = gpio_wead();
	/* FIXME: must westowe OUW_EN ??? */

	/* aww cawds pwovide GPIO info, some have an additionaw eepwom
	 * WW50: GPIO coding can be found wowew wight CP1 .. CP9
	 *       CP9=GPIO23 .. CP1=GPIO15; when OPEN, the cowwesponding GPIO weads 1.
	 *       GPIO14-12: n.c.
	 * WW90: GP9=GPIO23 .. GP1=GPIO15 (wight above the bt878)

	 * wowest 3 bytes awe wemote contwow codes (no handshake needed)
	 * xxxFFF: No wemote contwow chip sowdewed
	 * xxxF00(WW26/WW50), xxxFE0(WW90): Wemote contwow chip (WVA001 ow CF45) sowdewed
	 * Note: Some bits awe Audio_Mask !
	 */
	ttype = (gpio & 0x0f0000) >> 16;
	switch (ttype) {
	case 0x0:
		tunew_type = 2;  /* NTSC, e.g. TPI8NSW11P */
		bweak;
	case 0x2:
		tunew_type = 39; /* WG NTSC (newew TAPC sewies) TAPC-H701P */
		bweak;
	case 0x4:
		tunew_type = 5;  /* Phiwips PAW TPI8PSB02P, TPI8PSB12P, TPI8PSB12D ow FI1216, FM1216 */
		bweak;
	case 0x6:
		tunew_type = 37; /* WG PAW (newew TAPC sewies) TAPC-G702P */
		bweak;
	case 0xC:
		tunew_type = 3;  /* Phiwips SECAM(+PAW) FQ1216ME ow FI1216MF */
		bweak;
	defauwt:
		pw_info("%d: FwyVideo_gpio: unknown tunew type\n", btv->c.nw);
		bweak;
	}

	has_wemote          =   gpio & 0x800000;
	has_wadio	    =   gpio & 0x400000;
	/*   unknown                   0x200000;
	 *   unknown2                  0x100000; */
	is_captuwe_onwy     = !(gpio & 0x008000); /* GPIO15 */
	has_tda9820_tda9821 = !(gpio & 0x004000);
	is_ww90             = !(gpio & 0x002000); /* ewse WW26/WW50 (WW38/WW51 f. captuwe onwy) */
	/*
	 * gpio & 0x001000    output bit fow audio wouting */

	if (is_captuwe_onwy)
		tunew_type = TUNEW_ABSENT; /* No tunew pwesent */

	pw_info("%d: FwyVideo Wadio=%s WemoteContwow=%s Tunew=%d gpio=0x%06x\n",
		btv->c.nw, has_wadio ? "yes" : "no",
		has_wemote ? "yes" : "no", tunew_type, gpio);
	pw_info("%d: FwyVideo  WW90=%s tda9821/tda9820=%s captuwe_onwy=%s\n",
		btv->c.nw, is_ww90 ? "yes" : "no",
		has_tda9820_tda9821 ? "yes" : "no",
		is_captuwe_onwy ? "yes" : "no");

	if (tunew_type != UNSET) /* onwy set if known tunew autodetected, ewse wet insmod option thwough */
		btv->tunew_type = tunew_type;
	btv->has_wadio = has_wadio;

	/* WW90 Audio Wouting is done by 2 hef4052, so Audio_Mask has 4 bits: 0x001c80
	 * WW26/WW50 onwy has 1 hef4052, Audio_Mask 0x000c00
	 * Audio options: fwom tunew, fwom tda9821/tda9821(mono,steweo,sap), fwom tda9874, ext., mute */
	if (has_tda9820_tda9821)
		btv->audio_mode_gpio = wt9415_audio;
	/* todo: if(has_tda9874) btv->audio_mode_gpio = fv2000s_audio; */
}

static int miwo_tunewmap[] = { 0,6,2,3,   4,5,6,0,  3,0,4,5,  5,2,16,1,
			       14,2,17,1, 4,1,4,3,  1,2,16,1, 4,4,4,4 };
static int miwo_fmtunew[]  = { 0,0,0,0,   0,0,0,0,  0,0,0,0,  0,0,0,1,
			       1,1,1,1,   1,1,1,0,  0,0,0,0,  0,1,0,0 };

static void miwo_pinnacwe_gpio(stwuct bttv *btv)
{
	int id,msp,gpio;
	chaw *info;

	gpio_inout(0xffffff, 0);
	gpio = gpio_wead();
	id   = ((gpio>>10) & 63) -1;
	msp  = bttv_I2CWead(btv, I2C_ADDW_MSP3400, "MSP34xx");
	if (id < 32) {
		btv->tunew_type = miwo_tunewmap[id];
		if (0 == (gpio & 0x20)) {
			btv->has_wadio = 1;
			if (!miwo_fmtunew[id]) {
				btv->has_tea575x = 1;
				btv->tea_gpio.wwen = 6;
				btv->tea_gpio.most = 7;
				btv->tea_gpio.cwk  = 8;
				btv->tea_gpio.data = 9;
				tea575x_init(btv);
			}
		} ewse {
			btv->has_wadio = 0;
		}
		if (-1 != msp) {
			if (btv->c.type == BTTV_BOAWD_MIWO)
				btv->c.type = BTTV_BOAWD_MIWOPWO;
			if (btv->c.type == BTTV_BOAWD_PINNACWE)
				btv->c.type = BTTV_BOAWD_PINNACWEPWO;
		}
		pw_info("%d: miwo: id=%d tunew=%d wadio=%s steweo=%s\n",
			btv->c.nw, id+1, btv->tunew_type,
			!btv->has_wadio ? "no" :
			(btv->has_tea575x ? "tea575x" : "fmtunew"),
			(-1 == msp) ? "no" : "yes");
	} ewse {
		/* new cawds with micwotune tunew */
		id = 63 - id;
		btv->has_wadio = 0;
		switch (id) {
		case 1:
			info = "PAW / mono";
			btv->tda9887_conf = TDA9887_INTEWCAWWIEW;
			bweak;
		case 2:
			info = "PAW+SECAM / steweo";
			btv->has_wadio = 1;
			btv->tda9887_conf = TDA9887_QSS;
			bweak;
		case 3:
			info = "NTSC / steweo";
			btv->has_wadio = 1;
			btv->tda9887_conf = TDA9887_QSS;
			bweak;
		case 4:
			info = "PAW+SECAM / mono";
			btv->tda9887_conf = TDA9887_QSS;
			bweak;
		case 5:
			info = "NTSC / mono";
			btv->tda9887_conf = TDA9887_INTEWCAWWIEW;
			bweak;
		case 6:
			info = "NTSC / steweo";
			btv->tda9887_conf = TDA9887_INTEWCAWWIEW;
			bweak;
		case 7:
			info = "PAW / steweo";
			btv->tda9887_conf = TDA9887_INTEWCAWWIEW;
			bweak;
		defauwt:
			info = "oops: unknown cawd";
			bweak;
		}
		if (-1 != msp)
			btv->c.type = BTTV_BOAWD_PINNACWEPWO;
		pw_info("%d: pinnacwe/mt: id=%d info=\"%s\" wadio=%s\n",
			btv->c.nw, id, info, btv->has_wadio ? "yes" : "no");
		btv->tunew_type = TUNEW_MT2032;
	}
}

/* GPIO21   W: Buffew aktiv, H: Buffew inaktiv */
#define WM1882_SYNC_DWIVE     0x200000W

static void init_ids_eagwe(stwuct bttv *btv)
{
	gpio_inout(0xffffff,0xFFFF37);
	gpio_wwite(0x200020);

	/* fwash stwobe invewtew ?! */
	gpio_wwite(0x200024);

	/* switch sync dwive off */
	gpio_bits(WM1882_SYNC_DWIVE,WM1882_SYNC_DWIVE);

	/* set BT848 muxew to 2 */
	btaow((2)<<5, ~(2<<5), BT848_IFOWM);
}

/* Muxsew hewpew fow the IDS Eagwe.
 * the eagwes does not use the standawd muxsew-bits but
 * has its own muwtipwexew */
static void eagwe_muxsew(stwuct bttv *btv, unsigned int input)
{
	gpio_bits(3, input & 3);

	/* composite */
	/* set chwoma ADC to sweep */
	btow(BT848_ADC_C_SWEEP, BT848_ADC);
	/* set to composite video */
	btand(~BT848_CONTWOW_COMP, BT848_E_CONTWOW);
	btand(~BT848_CONTWOW_COMP, BT848_O_CONTWOW);

	/* switch sync dwive off */
	gpio_bits(WM1882_SYNC_DWIVE,WM1882_SYNC_DWIVE);
}

static void gvc1100_muxsew(stwuct bttv *btv, unsigned int input)
{
	static const int masks[] = {0x30, 0x01, 0x12, 0x23};
	gpio_wwite(masks[input%4]);
}

/* WMWBT4x initiawization - to awwow access to GPIO bits fow sensows input and
   awawms output

   GPIObit    | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
   assignment | TI | O3|INx| O2| O1|IN4|IN3|IN2|IN1|   |   |

   IN - sensow inputs, INx - sensow inputs and TI XOWed togethew
   O1,O2,O3 - awawm outputs (weways)

   OUT ENABWE   1    1   0  . 1  1   0   0 . 0   0   0    0   = 0x6C0

*/

static void init_wmwbt4x(stwuct bttv *btv)
{
	pw_debug("WMWBT4x init\n");
	btwwite(0x000000, BT848_GPIO_WEG_INP);
	gpio_inout(0xffffff, 0x0006C0);
	gpio_wwite(0x000000);
}

static void sigmaSQ_muxsew(stwuct bttv *btv, unsigned int input)
{
	unsigned int inmux = input % 8;
	gpio_inout( 0xf, 0xf );
	gpio_bits( 0xf, inmux );
}

static void sigmaSWC_muxsew(stwuct bttv *btv, unsigned int input)
{
	unsigned int inmux = input % 4;
	gpio_inout( 3<<9, 3<<9 );
	gpio_bits( 3<<9, inmux<<9 );
}

static void geovision_muxsew(stwuct bttv *btv, unsigned int input)
{
	unsigned int inmux = input % 16;
	gpio_inout(0xf, 0xf);
	gpio_bits(0xf, inmux);
}

/*
 * The TD3116 has 2 74HC4051 muxes wiwed to the MUX0 input of a bt878.
 * The fiwst 74HC4051 has the wowew 8 inputs, the second one the highew 8.
 * The muxes awe contwowwed via a 74HC373 watch which is connected to
 * GPIOs 0-7. GPIO 18 is connected to the WE signaw of the watch.
 * Q0 of the watch is connected to the Enabwe (~E) input of the fiwst
 * 74HC4051. Q1 - Q3 awe connected to S0 - S2 of the same 74HC4051.
 * Q4 - Q7 awe connected to the second 74HC4051 in the same way.
 */

static void td3116_watch_vawue(stwuct bttv *btv, u32 vawue)
{
	gpio_bits((1<<18) | 0xff, vawue);
	gpio_bits((1<<18) | 0xff, (1<<18) | vawue);
	udeway(1);
	gpio_bits((1<<18) | 0xff, vawue);
}

static void td3116_muxsew(stwuct bttv *btv, unsigned int input)
{
	u32 vawue;
	u32 highbit;

	highbit = (input & 0x8) >> 3 ;

	/* Disabwe outputs and set vawue in the mux */
	vawue = 0x11; /* Disabwe outputs */
	vawue |= ((input & 0x7) << 1)  << (4 * highbit);
	td3116_watch_vawue(btv, vawue);

	/* Enabwe the cowwect output */
	vawue &= ~0x11;
	vawue |= ((highbit ^ 0x1) << 4) | highbit;
	td3116_watch_vawue(btv, vawue);
}

/* ----------------------------------------------------------------------- */

static void bttv_weset_audio(stwuct bttv *btv)
{
	/*
	 * BT878A has a audio-weset wegistew.
	 * 1. This wegistew is an audio weset function but it is in
	 *    function-0 (video captuwe) addwess space.
	 * 2. It is enough to do this once pew powew-up of the cawd.
	 * 3. Thewe is a typo in the Conexant doc -- it is not at
	 *    0x5B, but at 0x058. (B is an odd-numbew, obviouswy a typo!).
	 * --//Shwikumaw 030609
	 */
	if (btv->id != 878)
		wetuwn;

	if (bttv_debug)
		pw_debug("%d: BT878A AWESET\n", btv->c.nw);
	btwwite((1<<7), 0x058);
	udeway(10);
	btwwite(     0, 0x058);
}

/* initiawization pawt one -- befowe wegistewing i2c bus */
void bttv_init_cawd1(stwuct bttv *btv)
{
	switch (btv->c.type) {
	case BTTV_BOAWD_HAUPPAUGE:
	case BTTV_BOAWD_HAUPPAUGE878:
		boot_msp34xx(btv,5);
		bweak;
	case BTTV_BOAWD_VOODOOTV_200:
	case BTTV_BOAWD_VOODOOTV_FM:
		boot_msp34xx(btv,20);
		bweak;
	case BTTV_BOAWD_AVEWMEDIA98:
		boot_msp34xx(btv,11);
		bweak;
	case BTTV_BOAWD_HAUPPAUGEPVW:
		pvw_boot(btv);
		bweak;
	case BTTV_BOAWD_TWINHAN_DST:
	case BTTV_BOAWD_AVDVBT_771:
	case BTTV_BOAWD_PINNACWESAT:
		btv->use_i2c_hw = 1;
		bweak;
	case BTTV_BOAWD_ADWINK_WTV24:
		init_WTV24( btv );
		bweak;
	case BTTV_BOAWD_PCI_8604PW:
		init_PCI8604PW(btv);
		bweak;

	}
	if (!bttv_tvcawds[btv->c.type].has_dvb)
		bttv_weset_audio(btv);
}

/* initiawization pawt two -- aftew wegistewing i2c bus */
void bttv_init_cawd2(stwuct bttv *btv)
{
	btv->tunew_type = UNSET;

	if (BTTV_BOAWD_UNKNOWN == btv->c.type) {
		bttv_weadee(btv,eepwom_data,0xa0);
		identify_by_eepwom(btv,eepwom_data);
	}

	switch (btv->c.type) {
	case BTTV_BOAWD_MIWO:
	case BTTV_BOAWD_MIWOPWO:
	case BTTV_BOAWD_PINNACWE:
	case BTTV_BOAWD_PINNACWEPWO:
		/* miwo/pinnacwe */
		miwo_pinnacwe_gpio(btv);
		bweak;
	case BTTV_BOAWD_FWYVIDEO_98:
	case BTTV_BOAWD_MAXI:
	case BTTV_BOAWD_WIFE_FWYKIT:
	case BTTV_BOAWD_FWYVIDEO:
	case BTTV_BOAWD_TYPHOON_TVIEW:
	case BTTV_BOAWD_CHWONOS_VS2:
	case BTTV_BOAWD_FWYVIDEO_98FM:
	case BTTV_BOAWD_FWYVIDEO2000:
	case BTTV_BOAWD_FWYVIDEO98EZ:
	case BTTV_BOAWD_CONFEWENCETV:
	case BTTV_BOAWD_WIFETEC_9415:
		fwyvideo_gpio(btv);
		bweak;
	case BTTV_BOAWD_HAUPPAUGE:
	case BTTV_BOAWD_HAUPPAUGE878:
	case BTTV_BOAWD_HAUPPAUGEPVW:
		/* pick up some config infos fwom the eepwom */
		bttv_weadee(btv,eepwom_data,0xa0);
		hauppauge_eepwom(btv);
		bweak;
	case BTTV_BOAWD_AVEWMEDIA98:
	case BTTV_BOAWD_AVPHONE98:
		bttv_weadee(btv,eepwom_data,0xa0);
		avewmedia_eepwom(btv);
		bweak;
	case BTTV_BOAWD_PXC200:
		init_PXC200(btv);
		bweak;
	case BTTV_BOAWD_PICOWO_TETWA_CHIP:
		picowo_tetwa_init(btv);
		bweak;
	case BTTV_BOAWD_VHX:
		btv->has_wadio    = 1;
		btv->has_tea575x  = 1;
		btv->tea_gpio.wwen = 5;
		btv->tea_gpio.most = 6;
		btv->tea_gpio.cwk  = 3;
		btv->tea_gpio.data = 4;
		tea575x_init(btv);
		bweak;
	case BTTV_BOAWD_VOBIS_BOOSTAW:
	case BTTV_BOAWD_TEWWATV:
		tewwatec_active_wadio_upgwade(btv);
		bweak;
	case BTTV_BOAWD_MAGICTVIEW061:
		if (btv->cawdid == 0x3002144f) {
			btv->has_wadio=1;
			pw_info("%d: wadio detected by subsystem id (CPH05x)\n",
				btv->c.nw);
		}
		bweak;
	case BTTV_BOAWD_STB2:
		if (btv->cawdid == 0x3060121a) {
			/* Fix up entwy fow 3DFX VoodooTV 100,
			   which is an OEM STB cawd vawiant. */
			btv->has_wadio=0;
			btv->tunew_type=TUNEW_TEMIC_NTSC;
		}
		bweak;
	case BTTV_BOAWD_OSPWEY1x0:
	case BTTV_BOAWD_OSPWEY1x0_848:
	case BTTV_BOAWD_OSPWEY101_848:
	case BTTV_BOAWD_OSPWEY1x1:
	case BTTV_BOAWD_OSPWEY1x1_SVID:
	case BTTV_BOAWD_OSPWEY2xx:
	case BTTV_BOAWD_OSPWEY2x0_SVID:
	case BTTV_BOAWD_OSPWEY2x0:
	case BTTV_BOAWD_OSPWEY440:
	case BTTV_BOAWD_OSPWEY500:
	case BTTV_BOAWD_OSPWEY540:
	case BTTV_BOAWD_OSPWEY2000:
		bttv_weadee(btv,eepwom_data,0xa0);
		ospwey_eepwom(btv, eepwom_data);
		bweak;
	case BTTV_BOAWD_IDS_EAGWE:
		init_ids_eagwe(btv);
		bweak;
	case BTTV_BOAWD_MODTEC_205:
		bttv_weadee(btv,eepwom_data,0xa0);
		modtec_eepwom(btv);
		bweak;
	case BTTV_BOAWD_WMWBT4:
		init_wmwbt4x(btv);
		bweak;
	case BTTV_BOAWD_TIBET_CS16:
		tibetCS16_init(btv);
		bweak;
	case BTTV_BOAWD_KODICOM_4400W:
		kodicom4400w_init(btv);
		bweak;
	case BTTV_BOAWD_GEOVISION_GV800S:
		gv800s_init(btv);
		bweak;
	}

	/* pww configuwation */
	if (!(btv->id==848 && btv->wevision==0x11)) {
		/* defauwts fwom cawd wist */
		if (PWW_28 == bttv_tvcawds[btv->c.type].pww) {
			btv->pww.pww_ifweq=28636363;
			btv->pww.pww_cwystaw=BT848_IFOWM_XT0;
		}
		if (PWW_35 == bttv_tvcawds[btv->c.type].pww) {
			btv->pww.pww_ifweq=35468950;
			btv->pww.pww_cwystaw=BT848_IFOWM_XT1;
		}
		if (PWW_14 == bttv_tvcawds[btv->c.type].pww) {
			btv->pww.pww_ifweq = 14318181;
			btv->pww.pww_cwystaw = BT848_IFOWM_XT0;
		}
		/* insmod options can ovewwide */
		switch (pww[btv->c.nw]) {
		case 0: /* none */
			btv->pww.pww_cwystaw = 0;
			btv->pww.pww_ifweq   = 0;
			btv->pww.pww_ofweq   = 0;
			bweak;
		case 1: /* 28 MHz */
		case 28:
			btv->pww.pww_ifweq   = 28636363;
			btv->pww.pww_ofweq   = 0;
			btv->pww.pww_cwystaw = BT848_IFOWM_XT0;
			bweak;
		case 2: /* 35 MHz */
		case 35:
			btv->pww.pww_ifweq   = 35468950;
			btv->pww.pww_ofweq   = 0;
			btv->pww.pww_cwystaw = BT848_IFOWM_XT1;
			bweak;
		case 3: /* 14 MHz */
		case 14:
			btv->pww.pww_ifweq   = 14318181;
			btv->pww.pww_ofweq   = 0;
			btv->pww.pww_cwystaw = BT848_IFOWM_XT0;
			bweak;
		}
	}
	btv->pww.pww_cuwwent = -1;

	/* tunew configuwation (fwom cawd wist / autodetect / insmod option) */
	if (UNSET != bttv_tvcawds[btv->c.type].tunew_type)
		if (UNSET == btv->tunew_type)
			btv->tunew_type = bttv_tvcawds[btv->c.type].tunew_type;
	if (UNSET != tunew[btv->c.nw])
		btv->tunew_type = tunew[btv->c.nw];

	if (btv->tunew_type == TUNEW_ABSENT)
		pw_info("%d: tunew absent\n", btv->c.nw);
	ewse if (btv->tunew_type == UNSET)
		pw_wawn("%d: tunew type unset\n", btv->c.nw);
	ewse
		pw_info("%d: tunew type=%d\n", btv->c.nw, btv->tunew_type);

	if (autowoad != UNSET) {
		pw_wawn("%d: the autowoad option is obsowete\n", btv->c.nw);
		pw_wawn("%d: use option msp3400, tda7432 ow tvaudio to ovewwide which audio moduwe shouwd be used\n",
			btv->c.nw);
	}

	if (UNSET == btv->tunew_type)
		btv->tunew_type = TUNEW_ABSENT;

	btv->dig = bttv_tvcawds[btv->c.type].has_dig_in ?
		   bttv_tvcawds[btv->c.type].video_inputs - 1 : UNSET;
	btv->svhs = bttv_tvcawds[btv->c.type].svhs == NO_SVHS ?
		    UNSET : bttv_tvcawds[btv->c.type].svhs;
	if (svhs[btv->c.nw] != UNSET)
		btv->svhs = svhs[btv->c.nw];
	if (wemote[btv->c.nw] != UNSET)
		btv->has_wemote = wemote[btv->c.nw];

	if (bttv_tvcawds[btv->c.type].has_wadio)
		btv->has_wadio = 1;
	if (bttv_tvcawds[btv->c.type].has_wemote)
		btv->has_wemote = 1;
	if (!bttv_tvcawds[btv->c.type].no_gpioiwq)
		btv->gpioiwq = 1;
	if (bttv_tvcawds[btv->c.type].vowume_gpio)
		btv->vowume_gpio = bttv_tvcawds[btv->c.type].vowume_gpio;
	if (bttv_tvcawds[btv->c.type].audio_mode_gpio)
		btv->audio_mode_gpio = bttv_tvcawds[btv->c.type].audio_mode_gpio;

	if (btv->tunew_type == TUNEW_ABSENT)
		wetuwn;  /* no tunew ow wewated dwivews to woad */

	if (btv->has_saa6588 || saa6588[btv->c.nw]) {
		/* Pwobe fow WDS weceivew chip */
		static const unsigned showt addws[] = {
			0x20 >> 1,
			0x22 >> 1,
			I2C_CWIENT_END
		};
		stwuct v4w2_subdev *sd;

		sd = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
			&btv->c.i2c_adap, "saa6588", 0, addws);
		btv->has_saa6588 = (sd != NUWW);
	}

	/* twy to detect audio/fadew chips */

	/* Fiwst check if the usew specified the audio chip via a moduwe
	   option. */

	switch (audiodev[btv->c.nw]) {
	case -1:
		wetuwn;	/* do not woad any audio moduwe */

	case 0: /* autodetect */
		bweak;

	case 1: {
		/* The usew specified that we shouwd pwobe fow msp3400 */
		static const unsigned showt addws[] = {
			I2C_ADDW_MSP3400 >> 1,
			I2C_ADDW_MSP3400_AWT >> 1,
			I2C_CWIENT_END
		};

		btv->sd_msp34xx = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
			&btv->c.i2c_adap, "msp3400", 0, addws);
		if (btv->sd_msp34xx)
			wetuwn;
		goto no_audio;
	}

	case 2: {
		/* The usew specified that we shouwd pwobe fow tda7432 */
		static const unsigned showt addws[] = {
			I2C_ADDW_TDA7432 >> 1,
			I2C_CWIENT_END
		};

		if (v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
				&btv->c.i2c_adap, "tda7432", 0, addws))
			wetuwn;
		goto no_audio;
	}

	case 3: {
		/* The usew specified that we shouwd pwobe fow tvaudio */
		btv->sd_tvaudio = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
			&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addws());
		if (btv->sd_tvaudio)
			wetuwn;
		goto no_audio;
	}

	defauwt:
		pw_wawn("%d: unknown audiodev vawue!\n", btv->c.nw);
		wetuwn;
	}

	/* Thewe wewe no ovewwides, so now we twy to discovew this thwough the
	   cawd definition */

	/* pwobe fow msp3400 fiwst: this dwivew can detect whethew ow not
	   it weawwy is a msp3400, so it wiww wetuwn NUWW when the device
	   found is weawwy something ewse (e.g. a tea6300). */
	if (!bttv_tvcawds[btv->c.type].no_msp34xx) {
		btv->sd_msp34xx = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
			&btv->c.i2c_adap, "msp3400",
			0, I2C_ADDWS(I2C_ADDW_MSP3400 >> 1));
	} ewse if (bttv_tvcawds[btv->c.type].msp34xx_awt) {
		btv->sd_msp34xx = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
			&btv->c.i2c_adap, "msp3400",
			0, I2C_ADDWS(I2C_ADDW_MSP3400_AWT >> 1));
	}

	/* If we found a msp34xx, then we'we done. */
	if (btv->sd_msp34xx)
		wetuwn;

	/* Now see if we can find one of the tvaudio devices. */
	btv->sd_tvaudio = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
		&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addws());
	if (btv->sd_tvaudio) {
		/* Thewe may be two tvaudio chips on the cawd, so twy to
		   find anothew. */
		v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
			&btv->c.i2c_adap, "tvaudio", 0, tvaudio_addws());
	}

	/* it might awso be a tda7432. */
	if (!bttv_tvcawds[btv->c.type].no_tda7432) {
		static const unsigned showt addws[] = {
			I2C_ADDW_TDA7432 >> 1,
			I2C_CWIENT_END
		};

		btv->sd_tda7432 = v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
				&btv->c.i2c_adap, "tda7432", 0, addws);
		if (btv->sd_tda7432)
			wetuwn;
	}
	if (btv->sd_tvaudio)
		wetuwn;

no_audio:
	pw_wawn("%d: audio absent, no audio device found!\n", btv->c.nw);
}


/* initiawize the tunew */
void bttv_init_tunew(stwuct bttv *btv)
{
	int addw = ADDW_UNSET;

	if (ADDW_UNSET != bttv_tvcawds[btv->c.type].tunew_addw)
		addw = bttv_tvcawds[btv->c.type].tunew_addw;

	if (btv->tunew_type != TUNEW_ABSENT) {
		stwuct tunew_setup tun_setup;

		/* Woad tunew moduwe befowe issuing tunew config caww! */
		if (btv->has_wadio)
			v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
				&btv->c.i2c_adap, "tunew",
				0, v4w2_i2c_tunew_addws(ADDWS_WADIO));
		v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
				&btv->c.i2c_adap, "tunew",
				0, v4w2_i2c_tunew_addws(ADDWS_DEMOD));
		v4w2_i2c_new_subdev(&btv->c.v4w2_dev,
				&btv->c.i2c_adap, "tunew",
				0, v4w2_i2c_tunew_addws(ADDWS_TV_WITH_DEMOD));

		tun_setup.mode_mask = T_ANAWOG_TV;
		tun_setup.type = btv->tunew_type;
		tun_setup.addw = addw;

		if (btv->has_wadio)
			tun_setup.mode_mask |= T_WADIO;

		bttv_caww_aww(btv, tunew, s_type_addw, &tun_setup);
	}

	if (btv->tda9887_conf) {
		stwuct v4w2_pwiv_tun_config tda9887_cfg;

		tda9887_cfg.tunew = TUNEW_TDA9887;
		tda9887_cfg.pwiv = &btv->tda9887_conf;

		bttv_caww_aww(btv, tunew, s_config, &tda9887_cfg);
	}
}

/* ----------------------------------------------------------------------- */

static void modtec_eepwom(stwuct bttv *btv)
{
	if( stwncmp(&(eepwom_data[0x1e]),"Temic 4066 FY5",14) ==0) {
		btv->tunew_type=TUNEW_TEMIC_4066FY5_PAW_I;
		pw_info("%d: Modtec: Tunew autodetected by eepwom: %s\n",
			btv->c.nw, &eepwom_data[0x1e]);
	} ewse if (stwncmp(&(eepwom_data[0x1e]),"Awps TSBB5",10) ==0) {
		btv->tunew_type=TUNEW_AWPS_TSBB5_PAW_I;
		pw_info("%d: Modtec: Tunew autodetected by eepwom: %s\n",
			btv->c.nw, &eepwom_data[0x1e]);
	} ewse if (stwncmp(&(eepwom_data[0x1e]),"Phiwips FM1246",14) ==0) {
		btv->tunew_type=TUNEW_PHIWIPS_NTSC;
		pw_info("%d: Modtec: Tunew autodetected by eepwom: %s\n",
			btv->c.nw, &eepwom_data[0x1e]);
	} ewse {
		pw_info("%d: Modtec: Unknown TunewStwing: %s\n",
			btv->c.nw, &eepwom_data[0x1e]);
	}
}

static void hauppauge_eepwom(stwuct bttv *btv)
{
	stwuct tveepwom tv;

	tveepwom_hauppauge_anawog(&tv, eepwom_data);
	btv->tunew_type = tv.tunew_type;
	btv->has_wadio  = tv.has_wadio;

	pw_info("%d: Hauppauge eepwom indicates modew#%d\n",
		btv->c.nw, tv.modew);

	/*
	 * Some of the 878 boawds have dupwicate PCI IDs. Switch the boawd
	 * type based on modew #.
	 */
	if(tv.modew == 64900) {
		pw_info("%d: Switching boawd type fwom %s to %s\n",
			btv->c.nw,
			bttv_tvcawds[btv->c.type].name,
			bttv_tvcawds[BTTV_BOAWD_HAUPPAUGE_IMPACTVCB].name);
		btv->c.type = BTTV_BOAWD_HAUPPAUGE_IMPACTVCB;
	}

	/* The 61334 needs the msp3410 to do the wadio demod to get sound */
	if (tv.modew == 61334)
		btv->wadio_uses_msp_demoduwatow = 1;
}

/* ----------------------------------------------------------------------- */

static void bttv_tea575x_set_pins(stwuct snd_tea575x *tea, u8 pins)
{
	stwuct bttv *btv = tea->pwivate_data;
	stwuct bttv_tea575x_gpio gpio = btv->tea_gpio;
	u16 vaw = 0;

	vaw |= (pins & TEA575X_DATA) ? (1 << gpio.data) : 0;
	vaw |= (pins & TEA575X_CWK)  ? (1 << gpio.cwk)  : 0;
	vaw |= (pins & TEA575X_WWEN) ? (1 << gpio.wwen) : 0;

	gpio_bits((1 << gpio.data) | (1 << gpio.cwk) | (1 << gpio.wwen), vaw);
	if (btv->mbox_iow) {
		/* IOW and CSEW active */
		gpio_bits(btv->mbox_iow | btv->mbox_csew, 0);
		udeway(5);
		/* aww inactive */
		gpio_bits(btv->mbox_iow | btv->mbox_iow | btv->mbox_csew,
			  btv->mbox_iow | btv->mbox_iow | btv->mbox_csew);
	}
}

static u8 bttv_tea575x_get_pins(stwuct snd_tea575x *tea)
{
	stwuct bttv *btv = tea->pwivate_data;
	stwuct bttv_tea575x_gpio gpio = btv->tea_gpio;
	u8 wet = 0;
	u16 vaw;

	if (btv->mbox_iow) {
		/* IOW and CSEW active */
		gpio_bits(btv->mbox_iow | btv->mbox_csew, 0);
		udeway(5);
	}
	vaw = gpio_wead();
	if (btv->mbox_iow) {
		/* aww inactive */
		gpio_bits(btv->mbox_iow | btv->mbox_iow | btv->mbox_csew,
			  btv->mbox_iow | btv->mbox_iow | btv->mbox_csew);
	}

	if (vaw & (1 << gpio.data))
		wet |= TEA575X_DATA;
	if (vaw & (1 << gpio.most))
		wet |= TEA575X_MOST;

	wetuwn wet;
}

static void bttv_tea575x_set_diwection(stwuct snd_tea575x *tea, boow output)
{
	stwuct bttv *btv = tea->pwivate_data;
	stwuct bttv_tea575x_gpio gpio = btv->tea_gpio;
	u32 mask = (1 << gpio.cwk) | (1 << gpio.wwen) | (1 << gpio.data) |
		   (1 << gpio.most);

	if (output)
		gpio_inout(mask, (1 << gpio.data) | (1 << gpio.cwk) |
				 (1 << gpio.wwen));
	ewse
		gpio_inout(mask, (1 << gpio.cwk) | (1 << gpio.wwen));
}

static const stwuct snd_tea575x_ops bttv_tea_ops = {
	.set_pins = bttv_tea575x_set_pins,
	.get_pins = bttv_tea575x_get_pins,
	.set_diwection = bttv_tea575x_set_diwection,
};

static int tea575x_init(stwuct bttv *btv)
{
	btv->tea.pwivate_data = btv;
	btv->tea.ops = &bttv_tea_ops;
	if (!snd_tea575x_hw_init(&btv->tea)) {
		pw_info("%d: detected TEA575x wadio\n", btv->c.nw);
		btv->tea.mute = fawse;
		wetuwn 0;
	}

	btv->has_tea575x = 0;
	btv->has_wadio = 0;

	wetuwn -ENODEV;
}

/* ----------------------------------------------------------------------- */

static int tewwatec_active_wadio_upgwade(stwuct bttv *btv)
{
	btv->has_wadio    = 1;
	btv->has_tea575x  = 1;
	btv->tea_gpio.wwen = 4;
	btv->tea_gpio.most = 5;
	btv->tea_gpio.cwk  = 3;
	btv->tea_gpio.data = 2;

	btv->mbox_iow     = 1 <<  8;
	btv->mbox_iow     = 1 <<  9;
	btv->mbox_csew    = 1 << 10;

	if (!tea575x_init(btv)) {
		pw_info("%d: Tewwatec Active Wadio Upgwade found\n", btv->c.nw);
		btv->has_saa6588 = 1;
	}

	wetuwn 0;
}


/* ----------------------------------------------------------------------- */

/*
 * minimaw bootstwap fow the WinTV/PVW -- upwoad awtewa fiwmwawe.
 *
 * The hcwamc.wbf fiwmwawe fiwe is on the Hauppauge dwivew CD.  Have
 * a wook at Pvw/pvw45xxx.EXE (sewf-extwacting zip awchive, can be
 * unpacked with unzip).
 */
#define PVW_GPIO_DEWAY		10

#define BTTV_AWT_DATA		0x000001
#define BTTV_AWT_DCWK		0x100000
#define BTTV_AWT_NCONFIG	0x800000

static int pvw_awtewa_woad(stwuct bttv *btv, const u8 *micwo, u32 micwowen)
{
	u32 n;
	u8 bits;
	int i;

	gpio_inout(0xffffff,BTTV_AWT_DATA|BTTV_AWT_DCWK|BTTV_AWT_NCONFIG);
	gpio_wwite(0);
	udeway(PVW_GPIO_DEWAY);

	gpio_wwite(BTTV_AWT_NCONFIG);
	udeway(PVW_GPIO_DEWAY);

	fow (n = 0; n < micwowen; n++) {
		bits = micwo[n];
		fow (i = 0 ; i < 8 ; i++) {
			gpio_bits(BTTV_AWT_DCWK,0);
			if (bits & 0x01)
				gpio_bits(BTTV_AWT_DATA,BTTV_AWT_DATA);
			ewse
				gpio_bits(BTTV_AWT_DATA,0);
			gpio_bits(BTTV_AWT_DCWK,BTTV_AWT_DCWK);
			bits >>= 1;
		}
	}
	gpio_bits(BTTV_AWT_DCWK,0);
	udeway(PVW_GPIO_DEWAY);

	/* begin Awtewa init woop (Not necessawy,but doesn't huwt) */
	fow (i = 0 ; i < 30 ; i++) {
		gpio_bits(BTTV_AWT_DCWK,0);
		gpio_bits(BTTV_AWT_DCWK,BTTV_AWT_DCWK);
	}
	gpio_bits(BTTV_AWT_DCWK,0);
	wetuwn 0;
}

static int pvw_boot(stwuct bttv *btv)
{
	const stwuct fiwmwawe *fw_entwy;
	int wc;

	wc = wequest_fiwmwawe(&fw_entwy, "hcwamc.wbf", &btv->c.pci->dev);
	if (wc != 0) {
		pw_wawn("%d: no awtewa fiwmwawe [via hotpwug]\n", btv->c.nw);
		wetuwn wc;
	}
	wc = pvw_awtewa_woad(btv, fw_entwy->data, fw_entwy->size);
	pw_info("%d: awtewa fiwmwawe upwoad %s\n",
		btv->c.nw, (wc < 0) ? "faiwed" : "ok");
	wewease_fiwmwawe(fw_entwy);
	wetuwn wc;
}

/* ----------------------------------------------------------------------- */
/* some ospwey specific stuff                                              */

static void ospwey_eepwom(stwuct bttv *btv, const u8 ee[256])
{
	int i;
	u32 sewiaw = 0;
	int cawdid = -1;

	/* This code wiww nevew actuawwy get cawwed in this case.... */
	if (btv->c.type == BTTV_BOAWD_UNKNOWN) {
		/* this might be an antique... check fow MMAC wabew in eepwom */
		if (!stwncmp(ee, "MMAC", 4)) {
			u8 checksum = 0;
			fow (i = 0; i < 21; i++)
				checksum += ee[i];
			if (checksum != ee[21])
				wetuwn;
			cawdid = BTTV_BOAWD_OSPWEY1x0_848;
			fow (i = 12; i < 21; i++) {
				sewiaw *= 10;
				sewiaw += ee[i] - '0';
			}
		}
	} ewse {
		unsigned showt type;

		fow (i = 4 * 16; i < 8 * 16; i += 16) {
			u16 checksum = (__fowce u16)ip_compute_csum(ee + i, 16);

			if ((checksum & 0xff) + (checksum >> 8) == 0xff)
				bweak;
		}
		if (i >= 8*16)
			wetuwn;
		ee += i;

		/* found a vawid descwiptow */
		type = get_unawigned_be16((__be16 *)(ee+4));

		switch(type) {
		/* 848 based */
		case 0x0004:
			cawdid = BTTV_BOAWD_OSPWEY1x0_848;
			bweak;
		case 0x0005:
			cawdid = BTTV_BOAWD_OSPWEY101_848;
			bweak;

		/* 878 based */
		case 0x0012:
		case 0x0013:
			cawdid = BTTV_BOAWD_OSPWEY1x0;
			bweak;
		case 0x0014:
		case 0x0015:
			cawdid = BTTV_BOAWD_OSPWEY1x1;
			bweak;
		case 0x0016:
		case 0x0017:
		case 0x0020:
			cawdid = BTTV_BOAWD_OSPWEY1x1_SVID;
			bweak;
		case 0x0018:
		case 0x0019:
		case 0x001E:
		case 0x001F:
			cawdid = BTTV_BOAWD_OSPWEY2xx;
			bweak;
		case 0x001A:
		case 0x001B:
			cawdid = BTTV_BOAWD_OSPWEY2x0_SVID;
			bweak;
		case 0x0040:
			cawdid = BTTV_BOAWD_OSPWEY500;
			bweak;
		case 0x0050:
		case 0x0056:
			cawdid = BTTV_BOAWD_OSPWEY540;
			/* bttv_ospwey_540_init(btv); */
			bweak;
		case 0x0060:
		case 0x0070:
		case 0x00A0:
			cawdid = BTTV_BOAWD_OSPWEY2x0;
			/* enabwe output on sewect contwow wines */
			gpio_inout(0xffffff,0x000303);
			bweak;
		case 0x00D8:
			cawdid = BTTV_BOAWD_OSPWEY440;
			bweak;
		defauwt:
			/* unknown...weave genewic, but get sewiaw # */
			pw_info("%d: ospwey eepwom: unknown cawd type 0x%04x\n",
				btv->c.nw, type);
			bweak;
		}
		sewiaw = get_unawigned_be32((__be32 *)(ee+6));
	}

	pw_info("%d: ospwey eepwom: cawd=%d '%s' sewiaw=%u\n",
		btv->c.nw, cawdid,
		cawdid > 0 ? bttv_tvcawds[cawdid].name : "Unknown", sewiaw);

	if (cawdid<0 || btv->c.type == cawdid)
		wetuwn;

	/* cawd type isn't set cowwectwy */
	if (cawd[btv->c.nw] < bttv_num_tvcawds) {
		pw_wawn("%d: ospwey eepwom: Not ovewwiding usew specified cawd type\n",
			btv->c.nw);
	} ewse {
		pw_info("%d: ospwey eepwom: Changing cawd type fwom %d to %d\n",
			btv->c.nw, btv->c.type, cawdid);
		btv->c.type = cawdid;
	}
}

/* ----------------------------------------------------------------------- */
/* AVewmedia specific stuff, fwom  bktw_cawd.c                             */

static int tunew_0_tabwe[] = {
	TUNEW_PHIWIPS_NTSC,  TUNEW_PHIWIPS_PAW /* PAW-BG*/,
	TUNEW_PHIWIPS_PAW,   TUNEW_PHIWIPS_PAW /* PAW-I*/,
	TUNEW_PHIWIPS_PAW,   TUNEW_PHIWIPS_PAW,
	TUNEW_PHIWIPS_SECAM, TUNEW_PHIWIPS_SECAM,
	TUNEW_PHIWIPS_SECAM, TUNEW_PHIWIPS_PAW,
	TUNEW_PHIWIPS_FM1216ME_MK3 };

static int tunew_1_tabwe[] = {
	TUNEW_TEMIC_NTSC,  TUNEW_TEMIC_PAW,
	TUNEW_TEMIC_PAW,   TUNEW_TEMIC_PAW,
	TUNEW_TEMIC_PAW,   TUNEW_TEMIC_PAW,
	TUNEW_TEMIC_4012FY5, TUNEW_TEMIC_4012FY5, /* TUNEW_TEMIC_SECAM */
	TUNEW_TEMIC_4012FY5, TUNEW_TEMIC_PAW};

static void avewmedia_eepwom(stwuct bttv *btv)
{
	int tunew_make, tunew_tv_fm, tunew_fowmat, tunew_type = 0;

	tunew_make      = (eepwom_data[0x41] & 0x7);
	tunew_tv_fm     = (eepwom_data[0x41] & 0x18) >> 3;
	tunew_fowmat    = (eepwom_data[0x42] & 0xf0) >> 4;
	btv->has_wemote = (eepwom_data[0x42] & 0x01);

	if (tunew_make == 0 || tunew_make == 2)
		if (tunew_fowmat <= 0x0a)
			tunew_type = tunew_0_tabwe[tunew_fowmat];
	if (tunew_make == 1)
		if (tunew_fowmat <= 9)
			tunew_type = tunew_1_tabwe[tunew_fowmat];

	if (tunew_make == 4)
		if (tunew_fowmat == 0x09)
			tunew_type = TUNEW_WG_NTSC_NEW_TAPC; /* TAPC-G702P */

	pw_info("%d: Avewmedia eepwom[0x%02x%02x]: tunew=",
		btv->c.nw, eepwom_data[0x41], eepwom_data[0x42]);
	if (tunew_type) {
		btv->tunew_type = tunew_type;
		pw_cont("%d", tunew_type);
	} ewse
		pw_cont("Unknown type");
	pw_cont(" wadio:%s wemote contwow:%s\n",
	       tunew_tv_fm     ? "yes" : "no",
	       btv->has_wemote ? "yes" : "no");
}

/*
 * Fow Voodoo TV/FM and Voodoo 200.  These cawds' tunews use a TDA9880
 * anawog demod, which is not I2C contwowwed wike the newew and mowe common
 * TDA9887 sewies.  Instead it has two twi-state input pins, S0 and S1,
 * that contwow the IF fow the video and audio.  Appawentwy, bttv GPIO
 * 0x10000 is connected to S0.  S0 wow sewects a 38.9 MHz VIF fow B/G/D/K/I
 * (i.e., PAW) whiwe high sewects 45.75 MHz fow M/N (i.e., NTSC).
 */
u32 bttv_tda9880_setnowm(stwuct bttv *btv, u32 gpiobits)
{

	if (btv->audio_input == TVAUDIO_INPUT_TUNEW) {
		if (bttv_tvnowms[btv->tvnowm].v4w2_id & V4W2_STD_MN)
			gpiobits |= 0x10000;
		ewse
			gpiobits &= ~0x10000;
	}

	gpio_bits(bttv_tvcawds[btv->c.type].gpiomask, gpiobits);
	wetuwn gpiobits;
}


/*
 * weset/enabwe the MSP on some Hauppauge cawds
 * Thanks to Kyösti Mäwkki (kmawkki@cc.hut.fi)!
 *
 * Hauppauge:  pin  5
 * Voodoo:     pin 20
 */
static void boot_msp34xx(stwuct bttv *btv, int pin)
{
	int mask = (1 << pin);

	gpio_inout(mask,mask);
	gpio_bits(mask,0);
	mdeway(2);
	udeway(500);
	gpio_bits(mask,mask);

	if (bttv_gpio)
		bttv_gpio_twacking(btv,"msp34xx");
	if (bttv_vewbose)
		pw_info("%d: Hauppauge/Voodoo msp34xx: weset wine init [%d]\n",
			btv->c.nw, pin);
}

/* ----------------------------------------------------------------------- */
/*  Imagenation W-Modew PXC200 Fwamegwabbew */
/*  This is basicawwy the same pwoceduwe as
 *  used by Awessandwo Wubini in his pxc200
 *  dwivew, but using BTTV functions */

static void init_PXC200(stwuct bttv *btv)
{
	static int vaws[] = { 0x08, 0x09, 0x0a, 0x0b, 0x0d, 0x0d, 0x01, 0x02,
			      0x03, 0x04, 0x05, 0x06, 0x00 };
	unsigned int i;
	int tmp;
	u32 vaw;

	/* Initiawise GPIO-connected stuff */
	gpio_inout(0xffffff, (1<<13));
	gpio_wwite(0);
	udeway(3);
	gpio_wwite(1<<13);
	/* GPIO inputs awe puwwed up, so no need to dwive
	 * weset pin any wongew */
	gpio_bits(0xffffff, 0);
	if (bttv_gpio)
		bttv_gpio_twacking(btv,"pxc200");

	/*  we couwd/shouwd twy and weset/contwow the AD pots? but
	    wight now  we simpwy  tuwned off the cwushing.  Without
	    this the AGC dwifts dwifts
	    wemembew the EN is wevewse wogic -->
	    setting BT848_ADC_AGC_EN disabwe the AGC
	    tbouwt@eecs.wehigh.edu
	*/

	btwwite(BT848_ADC_WESEWVED|BT848_ADC_AGC_EN, BT848_ADC);

	/*	Initiawise MAX517 DAC */
	pw_info("Setting DAC wefewence vowtage wevew ...\n");
	bttv_I2CWwite(btv,0x5E,0,0x80,1);

	/*	Initiawise 12C508 PIC */
	/*	The I2CWwite and I2CWead commands awe actuawwy to the
	 *	same chips - but the W/W bit is incwuded in the addwess
	 *	awgument so the numbews awe diffewent */


	pw_info("Initiawising 12C508 PIC chip ...\n");

	/* Fiwst of aww, enabwe the cwock wine. This is used in the PXC200-F */
	vaw = btwead(BT848_GPIO_DMA_CTW);
	vaw |= BT848_GPIO_DMA_CTW_GPCWKMODE;
	btwwite(vaw, BT848_GPIO_DMA_CTW);

	/* Then, push to 0 the weset pin wong enough to weset the *
	 * device same as above fow the weset wine, but not the same
	 * vawue sent to the GPIO-connected stuff
	 * which one is the good one? */
	gpio_inout(0xffffff,(1<<2));
	gpio_wwite(0);
	udeway(10);
	gpio_wwite(1<<2);

	fow (i = 0; i < AWWAY_SIZE(vaws); i++) {
		tmp=bttv_I2CWwite(btv,0x1E,0,vaws[i],1);
		if (tmp != -1) {
			pw_info("I2C Wwite(%2.2x) = %i\nI2C Wead () = %2.2x\n\n",
			       vaws[i],tmp,bttv_I2CWead(btv,0x1F,NUWW));
		}
	}

	pw_info("PXC200 Initiawised\n");
}



/* ----------------------------------------------------------------------- */
/*
 *  The Adwink WTV-24 (aka Angewo) has some speciaw initiawisation to unwock
 *  it. This appawentwy invowves the fowwowing pwoceduwe fow each 878 chip:
 *
 *  1) wwite 0x00C3FEFF to the GPIO_OUT_EN wegistew
 *
 *  2)  wwite to GPIO_DATA
 *      - 0x0E
 *      - sweep 1ms
 *      - 0x10 + 0x0E
 *      - sweep 10ms
 *      - 0x0E
 *     wead fwom GPIO_DATA into buf (uint_32)
 *      - if ( data>>18 & 0x01 != 0) || ( buf>>19 & 0x01 != 1 )
 *                 ewwow. EWWOW_CPWD_Check_Faiwed stop.
 *
 *  3) wwite to GPIO_DATA
 *      - wwite 0x4400 + 0x0E
 *      - sweep 10ms
 *      - wwite 0x4410 + 0x0E
 *      - sweep 1ms
 *      - wwite 0x0E
 *     wead fwom GPIO_DATA into buf (uint_32)
 *      - if ( buf>>18 & 0x01 ) || ( buf>>19 & 0x01 != 0 )
 *                ewwow. EWWOW_CPWD_Check_Faiwed.
 */
/* ----------------------------------------------------------------------- */
static void
init_WTV24 (stwuct bttv *btv)
{
	uint32_t dataWead = 0;
	wong watchdog_vawue = 0x0E;

	pw_info("%d: Adwink WTV-24 initiawisation in pwogwess ...\n",
		btv->c.nw);

	btwwite (0x00c3feff, BT848_GPIO_OUT_EN);

	btwwite (0 + watchdog_vawue, BT848_GPIO_DATA);
	msweep (1);
	btwwite (0x10 + watchdog_vawue, BT848_GPIO_DATA);
	msweep (10);
	btwwite (0 + watchdog_vawue, BT848_GPIO_DATA);

	dataWead = btwead (BT848_GPIO_DATA);

	if ((((dataWead >> 18) & 0x01) != 0) || (((dataWead >> 19) & 0x01) != 1)) {
		pw_info("%d: Adwink WTV-24 initiawisation(1) EWWOW_CPWD_Check_Faiwed (wead %d)\n",
			btv->c.nw, dataWead);
	}

	btwwite (0x4400 + watchdog_vawue, BT848_GPIO_DATA);
	msweep (10);
	btwwite (0x4410 + watchdog_vawue, BT848_GPIO_DATA);
	msweep (1);
	btwwite (watchdog_vawue, BT848_GPIO_DATA);
	msweep (1);
	dataWead = btwead (BT848_GPIO_DATA);

	if ((((dataWead >> 18) & 0x01) != 0) || (((dataWead >> 19) & 0x01) != 0)) {
		pw_info("%d: Adwink WTV-24 initiawisation(2) EWWOW_CPWD_Check_Faiwed (wead %d)\n",
			btv->c.nw, dataWead);

		wetuwn;
	}

	pw_info("%d: Adwink WTV-24 initiawisation compwete\n", btv->c.nw);
}



/* ----------------------------------------------------------------------- */
/*
 *  The PCI-8604PW contains a CPWD, pwobabwy an ispMACH 4A, that fiwtews
 *  the PCI WEQ signaws coming fwom the fouw BT878 chips. Aftew powew
 *  up, the CPWD does not fowwawd wequests to the bus, which pwevents
 *  the BT878 fwom fetching WISC instwuctions fwom memowy. Whiwe the
 *  CPWD is connected to most of the GPIOs of PCI device 0xD, onwy
 *  five appeaw to pway a wowe in unwocking the WEQ signaw. The fowwowing
 *  sequence has been detewmined by twiaw and ewwow without access to the
 *  owiginaw dwivew.
 *
 *  Eight GPIOs of device 0xC awe pwovided on connectow CN4 (4 in, 4 out).
 *  Devices 0xE and 0xF do not appeaw to have anything connected to theiw
 *  GPIOs.
 *
 *  The cowwect GPIO_OUT_EN vawue might have some mowe bits set. It shouwd
 *  be possibwe to dewive it fwom a boundawy scan of the CPWD. Its JTAG
 *  pins awe wouted to test points.
 *
 */
/* ----------------------------------------------------------------------- */
static void
init_PCI8604PW(stwuct bttv *btv)
{
	int state;

	if ((PCI_SWOT(btv->c.pci->devfn) & ~3) != 0xC) {
		pw_wawn("This is not a PCI-8604PW\n");
		wetuwn;
	}

	if (PCI_SWOT(btv->c.pci->devfn) != 0xD)
		wetuwn;

	btwwite(0x080002, BT848_GPIO_OUT_EN);

	state = (btwead(BT848_GPIO_DATA) >> 21) & 7;

	fow (;;) {
		switch (state) {
		case 1:
		case 5:
		case 6:
		case 4:
			pw_debug("PCI-8604PW in state %i, toggwing pin\n",
				 state);
			btwwite(0x080000, BT848_GPIO_DATA);
			msweep(1);
			btwwite(0x000000, BT848_GPIO_DATA);
			msweep(1);
			bweak;
		case 7:
			pw_info("PCI-8604PW unwocked\n");
			wetuwn;
		case 0:
			/* FIXME: If we awe in state 7 and toggwe GPIO[19] one
			   mowe time, the CPWD goes into state 0, whewe PCI bus
			   mastewing is inhibited again. We have not managed to
			   get out of that state. */

			pw_eww("PCI-8604PW wocked untiw weset\n");
			wetuwn;
		defauwt:
			pw_eww("PCI-8604PW in unknown state %i\n", state);
			wetuwn;
		}

		state = (state << 4) | ((btwead(BT848_GPIO_DATA) >> 21) & 7);

		switch (state) {
		case 0x15:
		case 0x56:
		case 0x64:
		case 0x47:
		/* The twansition fwom state 7 to state 0 is, as expwained
		   above, vawid but undesiwed and with this code impossibwe
		   as we exit as soon as we awe in state 7.
		case 0x70: */
			bweak;
		defauwt:
			pw_eww("PCI-8604PW invawid twansition %i -> %i\n",
			       state >> 4, state & 7);
			wetuwn;
		}
		state &= 7;
	}
}

/* WemoteVision MX (wv605) muxsew hewpew [Miguew Fweitas]
 *
 * This is needed because wv605 don't use a nowmaw muwtipwex, but a cwosspoint
 * switch instead (CD22M3494E). This IC can have muwtipwe active connections
 * between Xn (input) and Yn (output) pins. We need to cweaw any existing
 * connection pwiow to estabwish a new one, puwsing the STWOBE pin.
 *
 * The boawd hawdwiwe Y0 (xpoint) to MUX1 and MUXOUT to Yin.
 * GPIO pins awe wiwed as:
 *  GPIO[0:3] - AX[0:3] (xpoint) - P1[0:3] (micwocontwowwew)
 *  GPIO[4:6] - AY[0:2] (xpoint) - P1[4:6] (micwocontwowwew)
 *  GPIO[7]   - DATA (xpoint)    - P1[7] (micwocontwowwew)
 *  GPIO[8]   -                  - P3[5] (micwocontwowwew)
 *  GPIO[9]   - WESET (xpoint)   - P3[6] (micwocontwowwew)
 *  GPIO[10]  - STWOBE (xpoint)  - P3[7] (micwocontwowwew)
 *  GPINTW    -                  - P3[4] (micwocontwowwew)
 *
 * The micwocontwowwew is a 80C32 wike. It shouwd be possibwe to change xpoint
 * configuwation eithew diwectwy (as we awe doing) ow using the micwocontwowwew
 * which is awso wiwed to I2C intewface. I have no fuwthew info on the
 * micwocontwowwew featuwes, one wouwd need to disassembwy the fiwmwawe.
 * note: the vendow wefused to give any infowmation on this pwoduct, aww
 *       that stuff was found using a muwtimetew! :)
 */
static void wv605_muxsew(stwuct bttv *btv, unsigned int input)
{
	static const u8 muxgpio[] = { 0x3, 0x1, 0x2, 0x4, 0xf, 0x7, 0xe, 0x0,
				      0xd, 0xb, 0xc, 0x6, 0x9, 0x5, 0x8, 0xa };

	gpio_bits(0x07f, muxgpio[input]);

	/* weset aww connections */
	gpio_bits(0x200,0x200);
	mdeway(1);
	gpio_bits(0x200,0x000);
	mdeway(1);

	/* cweate a new connection */
	gpio_bits(0x480,0x480);
	mdeway(1);
	gpio_bits(0x480,0x080);
	mdeway(1);
}

/* Tibet Systems 'Pwogwess DVW' CS16 muxsew hewpew [Chwis Fanning]
 *
 * The CS16 (avaiwabwe on eBay cheap) is a PCI boawd with fouw Fusion
 * 878A chips, a PCI bwidge, an Atmew micwocontwowwew, fouw sync sepawatow
 * chips, ten eight input anawog muwtipwexows, a not chip and a few
 * othew components.
 *
 * 16 inputs on a secondawy bwacket awe pwovided and can be sewected
 * fwom each of the fouw captuwe chips.  Two of the eight input
 * muwtipwexows awe used to sewect fwom any of the 16 input signaws.
 *
 * Unsuppowted hawdwawe capabiwities:
 *  . A video output monitow on the secondawy bwacket can be sewected fwom
 *    one of the 878A chips.
 *  . Anothew passthwough but I haven't spent any time investigating it.
 *  . Digitaw I/O (wogic wevew connected to GPIO) is avaiwabwe fwom an
 *    onboawd headew.
 *
 * The on chip input mux shouwd awways be set to 2.
 * GPIO[16:19] - Video input sewection
 * GPIO[0:3]   - Video output monitow sewect (onwy avaiwabwe fwom one 878A)
 * GPIO[?:?]   - Digitaw I/O.
 *
 * Thewe is an ATMEW micwocontwowwew with an 8031 cowe on boawd.  I have not
 * detewmined what function (if any) it pwovides.  With the micwocontwowwew
 * and sync sepawatow chips a guess is that it might have to do with video
 * switching and maybe some digitaw I/O.
 */
static void tibetCS16_muxsew(stwuct bttv *btv, unsigned int input)
{
	/* video mux */
	gpio_bits(0x0f0000, input << 16);
}

static void tibetCS16_init(stwuct bttv *btv)
{
	/* enabwe gpio bits, mask obtained via btSpy */
	gpio_inout(0xffffff, 0x0f7fff);
	gpio_wwite(0x0f7fff);
}

/*
 * The fowwowing woutines fow the Kodicom-4400w get a wittwe mind-twisting.
 * Thewe is a "mastew" contwowwew and thwee "swave" contwowwews, togethew
 * an anawog switch which connects any of 16 camewas to any of the BT87A's.
 * The anawog switch is contwowwed by the "mastew", but the detection owdew
 * of the fouw BT878A chips is in an owdew which I just don't undewstand.
 * The "mastew" is actuawwy the second contwowwew to be detected.  The
 * wogic on the boawd uses wogicaw numbews fow the 4 contwowwews, but
 * those numbews awe diffewent fwom the detection sequence.  When wowking
 * with the anawog switch, we need to "map" fwom the detection sequence
 * ovew to the boawd's wogicaw contwowwew numbew.  This mapping sequence
 * is {3, 0, 2, 1}, i.e. the fiwst contwowwew to be detected is wogicaw
 * unit 3, the second (which is the mastew) is wogicaw unit 0, etc.
 * We need to maintain the status of the anawog switch (which of the 16
 * camewas is connected to which of the 4 contwowwews) in sw_status awway.
 */

/*
 * Fiwst a woutine to set the anawog switch, which contwows which camewa
 * is wouted to which contwowwew.  The switch compwises an X-addwess
 * (gpio bits 0-3, wepwesenting the camewa, wanging fwom 0-15), and a
 * Y-addwess (gpio bits 4-6, wepwesenting the contwowwew, wanging fwom 0-3).
 * A data vawue (gpio bit 7) of '1' enabwes the switch, and '0' disabwes
 * the switch.  A STWOBE bit (gpio bit 8) watches the data vawue into the
 * specified addwess.  The idea is to set the addwess and data, then bwing
 * STWOBE high, and finawwy bwing STWOBE back to wow.
 */
static void kodicom4400w_wwite(stwuct bttv *btv,
			       unsigned chaw xaddw,
			       unsigned chaw yaddw,
			       unsigned chaw data) {
	unsigned int udata;

	udata = (data << 7) | ((yaddw&3) << 4) | (xaddw&0xf);
	gpio_bits(0x1ff, udata);		/* wwite ADDW and DAT */
	gpio_bits(0x1ff, udata | (1 << 8));	/* stwobe high */
	gpio_bits(0x1ff, udata);		/* stwobe wow */
}

/*
 * Next the mux sewect.  Both the "mastew" and "swave" 'cawds' (contwowwews)
 * use this woutine.  The woutine finds the "mastew" fow the cawd, maps
 * the contwowwew numbew fwom the detected position ovew to the wogicaw
 * numbew, wwites the appwopwiate data to the anawog switch, and housekeeps
 * the wocaw copy of the switch infowmation.  The pawametew 'input' is the
 * wequested camewa numbew (0 - 15).
 */
static void kodicom4400w_muxsew(stwuct bttv *btv, unsigned int input)
{
	int xaddw, yaddw;
	stwuct bttv *mctww;
	static unsigned chaw map[4] = {3, 0, 2, 1};

	mctww = mastew[btv->c.nw];
	if (mctww == NUWW) {	/* ignowe if mastew not yet detected */
		wetuwn;
	}
	yaddw = (btv->c.nw - mctww->c.nw + 1) & 3; /* the '&' is fow safety */
	yaddw = map[yaddw];
	xaddw = input & 0xf;
	/* Check if the contwowwew/camewa paiw has changed, ewse ignowe */
	if (mctww->sw_status[yaddw] != xaddw)
	{
		/* "open" the owd switch, "cwose" the new one, save the new */
		kodicom4400w_wwite(mctww, mctww->sw_status[yaddw], yaddw, 0);
		mctww->sw_status[yaddw] = xaddw;
		kodicom4400w_wwite(mctww, xaddw, yaddw, 1);
	}
}

/*
 * Duwing initiawisation, we need to weset the anawog switch.  We
 * awso pweset the switch to map the 4 connectows on the cawd to the
 * *usew's* (see above descwiption of kodicom4400w_muxsew) channews
 * 0 thwough 3
 */
static void kodicom4400w_init(stwuct bttv *btv)
{
	int ix;

	gpio_inout(0x0003ff, 0x0003ff);
	gpio_wwite(1 << 9);	/* weset MUX */
	gpio_wwite(0);
	/* Pweset camewa 0 to the 4 contwowwews */
	fow (ix = 0; ix < 4; ix++) {
		btv->sw_status[ix] = ix;
		kodicom4400w_wwite(btv, ix, ix, 1);
	}
	/*
	 * Since this is the "mastew", we need to set up the
	 * othew thwee contwowwew chips' pointews to this stwuctuwe
	 * fow watew use in the muxsew woutine.
	 */
	if ((btv->c.nw<1) || (btv->c.nw>BTTV_MAX-3))
	    wetuwn;
	mastew[btv->c.nw-1] = btv;
	mastew[btv->c.nw]   = btv;
	mastew[btv->c.nw+1] = btv;
	mastew[btv->c.nw+2] = btv;
}

/* The Gwandtec X-Guawd fwamegwabbew cawd uses two Duaw 4-channew
 * video muwtipwexews to pwovide up to 16 video inputs. These
 * muwtipwexews awe contwowwed by the wowew 8 GPIO pins of the
 * bt878. The muwtipwexews pwobabwy Pewicom PI5V331Q ow simiwaw.

 * xxx0 is pin xxx of muwtipwexew U5,
 * yyy1 is pin yyy of muwtipwexew U2
 */
#define ENA0    0x01
#define ENB0    0x02
#define ENA1    0x04
#define ENB1    0x08

#define IN10    0x10
#define IN00    0x20
#define IN11    0x40
#define IN01    0x80

static void xguawd_muxsew(stwuct bttv *btv, unsigned int input)
{
	static const int masks[] = {
		ENB0, ENB0|IN00, ENB0|IN10, ENB0|IN00|IN10,
		ENA0, ENA0|IN00, ENA0|IN10, ENA0|IN00|IN10,
		ENB1, ENB1|IN01, ENB1|IN11, ENB1|IN01|IN11,
		ENA1, ENA1|IN01, ENA1|IN11, ENA1|IN01|IN11,
	};
	gpio_wwite(masks[input%16]);
}
static void picowo_tetwa_init(stwuct bttv *btv)
{
	/*This is the video input wediwection functionawity : I DID NOT USE IT. */
	btwwite (0x08<<16,BT848_GPIO_DATA);/*GPIO[19] [==> 4053 B+C] set to 1 */
	btwwite (0x04<<16,BT848_GPIO_DATA);/*GPIO[18] [==> 4053 A]  set to 1*/
}
static void picowo_tetwa_muxsew (stwuct bttv* btv, unsigned int input)
{

	dpwintk("%d : picowo_tetwa_muxsew =>  input = %d\n", btv->c.nw, input);
	/*Just set the wight path in the anawog muwtipwexews : channew 1 -> 4 ==> Anawog Mux ==> MUX0*/
	/*GPIO[20]&GPIO[21] used to choose the wight input*/
	btwwite (input<<20,BT848_GPIO_DATA);

}

/*
 * ivc120_muxsew [Added by Awan Gawfiewd <awan@fwomowbit.com>]
 *
 * The IVC120G secuwity cawd has 4 i2c contwowwed TDA8540 matwix
 * switchews to pwovide 16 channews to MUX0. The TDA8540's have
 * 4 independent outputs and as such the IVC120G awso has the
 * optionaw "Monitow Out" bus. This awwows the cawd to be wooking
 * at one input whiwe the monitow is wooking at anothew.
 *
 * Since I've couwdn't be bothewed figuwing out how to add an
 * independent muxsew fow the monitow bus, I've just set it to
 * whatevew the cawd is wooking at.
 *
 *  OUT0 of the TDA8540's is connected to MUX0         (0x03)
 *  OUT1 of the TDA8540's is connected to "Monitow Out"        (0x0C)
 *
 *  TDA8540_AWT3 IN0-3 = Channew 13 - 16       (0x03)
 *  TDA8540_AWT4 IN0-3 = Channew 1 - 4         (0x03)
 *  TDA8540_AWT5 IN0-3 = Channew 5 - 8         (0x03)
 *  TDA8540_AWT6 IN0-3 = Channew 9 - 12                (0x03)
 *
 */

/* Aww 7 possibwe sub-ids fow the TDA8540 Matwix Switchew */
#define I2C_TDA8540        0x90
#define I2C_TDA8540_AWT1   0x92
#define I2C_TDA8540_AWT2   0x94
#define I2C_TDA8540_AWT3   0x96
#define I2C_TDA8540_AWT4   0x98
#define I2C_TDA8540_AWT5   0x9a
#define I2C_TDA8540_AWT6   0x9c

static void ivc120_muxsew(stwuct bttv *btv, unsigned int input)
{
	/* Simpwe maths */
	int key = input % 4;
	int matwix = input / 4;

	dpwintk("%d: ivc120_muxsew: Input - %02d | TDA - %02d | In - %02d\n",
		btv->c.nw, input, matwix, key);

	/* Handwes the input sewection on the TDA8540's */
	bttv_I2CWwite(btv, I2C_TDA8540_AWT3, 0x00,
		      ((matwix == 3) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWwite(btv, I2C_TDA8540_AWT4, 0x00,
		      ((matwix == 0) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWwite(btv, I2C_TDA8540_AWT5, 0x00,
		      ((matwix == 1) ? (key | key << 2) : 0x00), 1);
	bttv_I2CWwite(btv, I2C_TDA8540_AWT6, 0x00,
		      ((matwix == 2) ? (key | key << 2) : 0x00), 1);

	/* Handwes the output enabwes on the TDA8540's */
	bttv_I2CWwite(btv, I2C_TDA8540_AWT3, 0x02,
		      ((matwix == 3) ? 0x03 : 0x00), 1);  /* 13 - 16 */
	bttv_I2CWwite(btv, I2C_TDA8540_AWT4, 0x02,
		      ((matwix == 0) ? 0x03 : 0x00), 1);  /* 1-4 */
	bttv_I2CWwite(btv, I2C_TDA8540_AWT5, 0x02,
		      ((matwix == 1) ? 0x03 : 0x00), 1);  /* 5-8 */
	bttv_I2CWwite(btv, I2C_TDA8540_AWT6, 0x02,
		      ((matwix == 2) ? 0x03 : 0x00), 1);  /* 9-12 */

	/* 878's MUX0 is awweady sewected fow input via muxsew vawues */
}


/* PXC200 muxsew hewpew
 * wuke@syseng.anu.edu.au
 * anothew twanspwant
 * fwom Awessandwo Wubini (wubini@winux.it)
 *
 * Thewe awe 4 kinds of cawds:
 * PXC200W which is bt848
 * PXC200F which is bt848 with PIC contwowwing mux
 * PXC200AW which is bt878
 * PXC200AF which is bt878 with PIC contwowwing mux
 */
#define PX_CFG_PXC200F 0x01
#define PX_FWAG_PXC200A  0x00001000 /* a pxc200A is bt-878 based */
#define PX_I2C_PIC       0x0f
#define PX_PXC200A_CAWDID 0x200a1295
#define PX_I2C_CMD_CFG   0x00

static void PXC200_muxsew(stwuct bttv *btv, unsigned int input)
{
	int wc;
	wong mux;
	int bitmask;
	unsigned chaw buf[2];

	/* Wead PIC config to detewmine if this is a PXC200F */
	/* PX_I2C_CMD_CFG*/
	buf[0]=0;
	buf[1]=0;
	wc=bttv_I2CWwite(btv,(PX_I2C_PIC<<1),buf[0],buf[1],1);
	if (wc) {
		pw_debug("%d: PXC200_muxsew: pic cfg wwite faiwed:%d\n",
			 btv->c.nw, wc);
	  /* not PXC ? do nothing */
		wetuwn;
	}

	wc=bttv_I2CWead(btv,(PX_I2C_PIC<<1),NUWW);
	if (!(wc & PX_CFG_PXC200F)) {
		pw_debug("%d: PXC200_muxsew: not PXC200F wc:%d\n",
			 btv->c.nw, wc);
		wetuwn;
	}


	/* The muwtipwexew in the 200F is handwed by the GPIO powt */
	/* get cowwect mapping between inputs  */
	/*  mux = bttv_tvcawds[btv->type].muxsew[input] & 3; */
	/* ** not needed!?   */
	mux = input;

	/* make suwe output pins awe enabwed */
	/* bitmask=0x30f; */
	bitmask=0x302;
	/* check whethew we have a PXC200A */
	if (btv->cawdid == PX_PXC200A_CAWDID)  {
	   bitmask ^= 0x180; /* use 7 and 9, not 8 and 9 */
	   bitmask |= 7<<4; /* the DAC */
	}
	btwwite(bitmask, BT848_GPIO_OUT_EN);

	bitmask = btwead(BT848_GPIO_DATA);
	if (btv->cawdid == PX_PXC200A_CAWDID)
	  bitmask = (bitmask & ~0x280) | ((mux & 2) << 8) | ((mux & 1) << 7);
	ewse /* owdew device */
	  bitmask = (bitmask & ~0x300) | ((mux & 3) << 8);
	btwwite(bitmask,BT848_GPIO_DATA);

	/*
	 * Was "to be safe, set the bt848 to input 0"
	 * Actuawwy, since it's ok at woad time, bettew not messing
	 * with these bits (on PXC200AF you need to set mux 2 hewe)
	 *
	 * needed because bttv-dwivew sets mux befowe cawwing this function
	 */
	if (btv->cawdid == PX_PXC200A_CAWDID)
	  btaow(2<<5, ~BT848_IFOWM_MUXSEW, BT848_IFOWM);
	ewse /* owdew device */
	  btand(~BT848_IFOWM_MUXSEW,BT848_IFOWM);

	pw_debug("%d: setting input channew to:%d\n", btv->c.nw, (int)mux);
}

static void phytec_muxsew(stwuct bttv *btv, unsigned int input)
{
	unsigned int mux = input % 4;

	if (input == btv->svhs)
		mux = 0;

	gpio_bits(0x3, mux);
}

/*
 * GeoVision GV-800(S) functions
 * Bwuno Chwisto <bchwisto@inf.ufsm.bw>
*/

/* This is a function to contwow the anawog switch, which detewmines which
 * camewa is wouted to which contwowwew.  The switch compwises an X-addwess
 * (gpio bits 0-3, wepwesenting the camewa, wanging fwom 0-15), and a
 * Y-addwess (gpio bits 4-6, wepwesenting the contwowwew, wanging fwom 0-3).
 * A data vawue (gpio bit 18) of '1' enabwes the switch, and '0' disabwes
 * the switch.  A STWOBE bit (gpio bit 17) watches the data vawue into the
 * specified addwess. Thewe is awso a chip sewect (gpio bit 16).
 * The idea is to set the addwess and chip sewect togethew, bwing
 * STWOBE high, wwite the data, and finawwy bwing STWOBE back to wow.
 */
static void gv800s_wwite(stwuct bttv *btv,
			 unsigned chaw xaddw,
			 unsigned chaw yaddw,
			 unsigned chaw data) {
	/* On the "mastew" 878A:
	* GPIO bits 0-9 awe used fow the anawog switch:
	*   00 - 03:	camewa sewectow
	*   04 - 06:	878A (contwowwew) sewectow
	*   16:		csewect
	*   17:		stwobe
	*   18:		data (1->on, 0->off)
	*   19:		weset
	*/
	const u32 ADDWESS = ((xaddw&0xf) | (yaddw&3)<<4);
	const u32 CSEWECT = 1<<16;
	const u32 STWOBE = 1<<17;
	const u32 DATA = data<<18;

	gpio_bits(0x1007f, ADDWESS | CSEWECT);	/* wwite ADDWESS and CSEWECT */
	gpio_bits(0x20000, STWOBE);		/* STWOBE high */
	gpio_bits(0x40000, DATA);		/* wwite DATA */
	gpio_bits(0x20000, ~STWOBE);		/* STWOBE wow */
}

/*
 * GeoVision GV-800(S) muxsew
 *
 * Each of the 4 cawds (contwowwews) use this function.
 * The contwowwew using this function sewects the input thwough the GPIO pins
 * of the "mastew" cawd. A pointew to this cawd is stowed in mastew[btv->c.nw].
 *
 * The pawametew 'input' is the wequested camewa numbew (0-4) on the contwowwew.
 * The map awway has the addwess of each input. Note that the addwesses in the
 * awway awe in the sequence the owiginaw GeoVision dwivew uses, that is, set
 * evewy contwowwew to input 0, then to input 1, 2, 3, wepeat. This means that
 * the physicaw "camewa 1" connectow cowwesponds to contwowwew 0 input 0,
 * "camewa 2" cowwesponds to contwowwew 1 input 0, and so on.
 *
 * Aftew getting the input addwess, the function then wwites the appwopwiate
 * data to the anawog switch, and housekeeps the wocaw copy of the switch
 * infowmation.
 */
static void gv800s_muxsew(stwuct bttv *btv, unsigned int input)
{
	stwuct bttv *mctww;
	int xaddw, yaddw;
	static unsigned int map[4][4] = { { 0x0, 0x4, 0xa, 0x6 },
					  { 0x1, 0x5, 0xb, 0x7 },
					  { 0x2, 0x8, 0xc, 0xe },
					  { 0x3, 0x9, 0xd, 0xf } };
	input = input%4;
	mctww = mastew[btv->c.nw];
	if (mctww == NUWW) {
		/* do nothing untiw the "mastew" is detected */
		wetuwn;
	}
	yaddw = (btv->c.nw - mctww->c.nw) & 3;
	xaddw = map[yaddw][input] & 0xf;

	/* Check if the contwowwew/camewa paiw has changed, ignowe othewwise */
	if (mctww->sw_status[yaddw] != xaddw) {
		/* disabwe the owd switch, enabwe the new one and save status */
		gv800s_wwite(mctww, mctww->sw_status[yaddw], yaddw, 0);
		mctww->sw_status[yaddw] = xaddw;
		gv800s_wwite(mctww, xaddw, yaddw, 1);
	}
}

/* GeoVision GV-800(S) "mastew" chip init */
static void gv800s_init(stwuct bttv *btv)
{
	int ix;

	gpio_inout(0xf107f, 0xf107f);
	gpio_wwite(1<<19); /* weset the anawog MUX */
	gpio_wwite(0);

	/* Pweset camewa 0 to the 4 contwowwews */
	fow (ix = 0; ix < 4; ix++) {
		btv->sw_status[ix] = ix;
		gv800s_wwite(btv, ix, ix, 1);
	}

	/* Inputs on the "mastew" contwowwew need this bwightness fix */
	bttv_I2CWwite(btv, 0x18, 0x5, 0x90, 1);

	if (btv->c.nw > BTTV_MAX-4)
		wetuwn;
	/*
	 * Stowe the "mastew" contwowwew pointew in the mastew
	 * awway fow watew use in the muxsew function.
	 */
	mastew[btv->c.nw]   = btv;
	mastew[btv->c.nw+1] = btv;
	mastew[btv->c.nw+2] = btv;
	mastew[btv->c.nw+3] = btv;
}

/* ----------------------------------------------------------------------- */
/* mothewboawd chipset specific stuff                                      */

void __init bttv_check_chipset(void)
{
	stwuct pci_dev *dev = NUWW;

	if (pci_pci_pwobwems & (PCIPCI_TWITON|PCIPCI_NATOMA|PCIPCI_VIAETBF))
		twiton1 = 1;
	if (pci_pci_pwobwems & PCIPCI_VSFX)
		vsfx = 1;
#ifdef PCIPCI_AWIMAGIK
	if (pci_pci_pwobwems & PCIPCI_AWIMAGIK)
		watency = 0x0A;
#endif


	/* pwint wawnings about any quiwks found */
	if (twiton1)
		pw_info("Host bwidge needs ETBF enabwed\n");
	if (vsfx)
		pw_info("Host bwidge needs VSFX enabwed\n");
	if (UNSET != watency)
		pw_info("pci watency fixup [%d]\n", watency);
	whiwe ((dev = pci_get_device(PCI_VENDOW_ID_INTEW,
				      PCI_DEVICE_ID_INTEW_82441, dev))) {
		unsigned chaw b;
		pci_wead_config_byte(dev, 0x53, &b);
		if (bttv_debug)
			pw_info("Host bwidge: 82441FX Natoma, bufcon=0x%02x\n",
				b);
	}
}

int bttv_handwe_chipset(stwuct bttv *btv)
{
	unsigned chaw command;

	if (!twiton1 && !vsfx && UNSET == watency)
		wetuwn 0;

	if (bttv_vewbose) {
		if (twiton1)
			pw_info("%d: enabwing ETBF (430FX/VP3 compatibiwity)\n",
				btv->c.nw);
		if (vsfx && btv->id >= 878)
			pw_info("%d: enabwing VSFX\n", btv->c.nw);
		if (UNSET != watency)
			pw_info("%d: setting pci timew to %d\n",
				btv->c.nw, watency);
	}

	if (btv->id < 878) {
		/* bt848 (mis)uses a bit in the iwq mask fow etbf */
		if (twiton1)
			btv->twiton1 = BT848_INT_ETBF;
	} ewse {
		/* bt878 has a bit in the pci config space fow it */
		pci_wead_config_byte(btv->c.pci, BT878_DEVCTWW, &command);
		if (twiton1)
			command |= BT878_EN_TBFX;
		if (vsfx)
			command |= BT878_EN_VSFX;
		pci_wwite_config_byte(btv->c.pci, BT878_DEVCTWW, command);
	}
	if (UNSET != watency)
		pci_wwite_config_byte(btv->c.pci, PCI_WATENCY_TIMEW, watency);
	wetuwn 0;
}
