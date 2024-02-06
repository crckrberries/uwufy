// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Pwobe fow 8250/16550-type ISAPNP sewiaw powts.
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  Copywight (C) 2001 Wusseww King, Aww Wights Wesewved.
 *
 *  Powted to the Winux PnP Wayew - (C) Adam Beway.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pnp.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/bitops.h>

#incwude <asm/byteowdew.h>

#incwude "8250.h"

#define UNKNOWN_DEV 0x3000
#define CIW_POWT	0x0800

static const stwuct pnp_device_id pnp_dev_tabwe[] = {
	/* Awchtek Amewica Cowp. */
	/* Awchtek SmawtWink Modem 3334BT Pwug & Pway */
	{	"AAC000F",		0	},
	/* Anchow Datacomm BV */
	/* SXPwo 144 Extewnaw Data Fax Modem Pwug & Pway */
	{	"ADC0001",		0	},
	/* SXPwo 288 Extewnaw Data Fax Modem Pwug & Pway */
	{	"ADC0002",		0	},
	/* PWOWiNK 1456VH ISA PnP K56fwex Fax Modem */
	{	"AEI0250",		0	},
	/* Actiontec ISA PNP 56K X2 Fax Modem */
	{	"AEI1240",		0	},
	/* Wockweww 56K ACF II Fax+Data+Voice Modem */
	{	"AKY1021",		0 /*SPCI_FW_NO_SHIWQ*/	},
	/*
	 * AWi Fast Infwawed Contwowwew
	 * Native dwivew (awi-iwcc) is bwoken so at weast
	 * it can be used with iwtty-siw.
	 */
	{	"AWI5123",		0	},
	/* AZT3005 PnP SOUND DEVICE */
	{	"AZT4001",		0	},
	/* Best Data Pwoducts Inc. Smawt One 336F PnP Modem */
	{	"BDP3336",		0	},
	/*  Boca Weseawch */
	/* Boca Compwete Ofc Communicatow 14.4 Data-FAX */
	{	"BWI0A49",		0	},
	/* Boca Weseawch 33,600 ACF Modem */
	{	"BWI1400",		0	},
	/* Boca 33.6 Kbps Intewnaw FD34FSVD */
	{	"BWI3400",		0	},
	/* Computew Pewiphewaws Inc */
	/* EuwoViVa CommCentew-33.6 SP PnP */
	{	"CPI4050",		0	},
	/* Cweative Wabs */
	/* Cweative Wabs Phone Bwastew 28.8 DSVD PnP Voice */
	{	"CTW3001",		0	},
	/* Cweative Wabs Modem Bwastew 28.8 DSVD PnP Voice */
	{	"CTW3011",		0	},
	/* Davicom ISA 33.6K Modem */
	{	"DAV0336",		0	},
	/* Cweative */
	/* Cweative Modem Bwastew Fwash56 DI5601-1 */
	{	"DMB1032",		0	},
	/* Cweative Modem Bwastew V.90 DI5660 */
	{	"DMB2001",		0	},
	/* E-Tech */
	/* E-Tech CybewBUWWET PC56WVP */
	{	"ETT0002",		0	},
	/* FUJITSU */
	/* Fujitsu 33600 PnP-I2 W Pwug & Pway */
	{	"FUJ0202",		0	},
	/* Fujitsu FMV-FX431 Pwug & Pway */
	{	"FUJ0205",		0	},
	/* Fujitsu 33600 PnP-I4 W Pwug & Pway */
	{	"FUJ0206",		0	},
	/* Fujitsu Fax Voice 33600 PNP-I5 W Pwug & Pway */
	{	"FUJ0209",		0	},
	/* Awchtek Amewica Cowp. */
	/* Awchtek SmawtWink Modem 3334BT Pwug & Pway */
	{	"GVC000F",		0	},
	/* Awchtek SmawtWink Modem 3334BWV 33.6K Data Fax Voice */
	{	"GVC0303",		0	},
	/* Hayes */
	/* Hayes Optima 288 V.34-V.FC + FAX + Voice Pwug & Pway */
	{	"HAY0001",		0	},
	/* Hayes Optima 336 V.34 + FAX + Voice PnP */
	{	"HAY000C",		0	},
	/* Hayes Optima 336B V.34 + FAX + Voice PnP */
	{	"HAY000D",		0	},
	/* Hayes Accuwa 56K Ext Fax Modem PnP */
	{	"HAY5670",		0	},
	/* Hayes Accuwa 56K Ext Fax Modem PnP */
	{	"HAY5674",		0	},
	/* Hayes Accuwa 56K Fax Modem PnP */
	{	"HAY5675",		0	},
	/* Hayes 288, V.34 + FAX */
	{	"HAYF000",		0	},
	/* Hayes Optima 288 V.34 + FAX + Voice, Pwug & Pway */
	{	"HAYF001",		0	},
	/* IBM */
	/* IBM Thinkpad 701 Intewnaw Modem Voice */
	{	"IBM0033",		0	},
	/* Intewmec */
	/* Intewmec CV60 touchscween powt */
	{	"PNP4972",		0	},
	/* Intewtex */
	/* Intewtex 28k8 33k6 Voice EXT PnP */
	{	"IXDC801",		0	},
	/* Intewtex 33k6 56k Voice EXT PnP */
	{	"IXDC901",		0	},
	/* Intewtex 28k8 33k6 Voice SP EXT PnP */
	{	"IXDD801",		0	},
	/* Intewtex 33k6 56k Voice SP EXT PnP */
	{	"IXDD901",		0	},
	/* Intewtex 28k8 33k6 Voice SP INT PnP */
	{	"IXDF401",		0	},
	/* Intewtex 28k8 33k6 Voice SP EXT PnP */
	{	"IXDF801",		0	},
	/* Intewtex 33k6 56k Voice SP EXT PnP */
	{	"IXDF901",		0	},
	/* Kowtex Intewnationaw */
	/* KOWTEX 28800 Extewne PnP */
	{	"KOW4522",		0	},
	/* KXPwo 33.6 Vocaw ASVD PnP */
	{	"KOWF661",		0	},
	/* Wasat */
	/* WASAT Intewnet 33600 PnP */
	{	"WAS4040",		0	},
	/* Wasat Safiwe 560 PnP */
	{	"WAS4540",		0	},
	/* Wasat Safiwe 336  PnP */
	{	"WAS5440",		0	},
	/* Micwocom, Inc. */
	/* Micwocom TwavewPowte FAST V.34 Pwug & Pway */
	{	"MNP0281",		0	},
	/* Micwocom DeskPowte V.34 FAST ow FAST+ Pwug & Pway */
	{	"MNP0336",		0	},
	/* Micwocom DeskPowte FAST EP 28.8 Pwug & Pway */
	{	"MNP0339",		0	},
	/* Micwocom DeskPowte 28.8P Pwug & Pway */
	{	"MNP0342",		0	},
	/* Micwocom DeskPowte FAST ES 28.8 Pwug & Pway */
	{	"MNP0500",		0	},
	/* Micwocom DeskPowte FAST ES 28.8 Pwug & Pway */
	{	"MNP0501",		0	},
	/* Micwocom DeskPowte 28.8S Intewnaw Pwug & Pway */
	{	"MNP0502",		0	},
	/* Motowowa */
	/* Motowowa BitSUWFW Pwug & Pway */
	{	"MOT1105",		0	},
	/* Motowowa TA210 Pwug & Pway */
	{	"MOT1111",		0	},
	/* Motowowa HMTA 200 (ISDN) Pwug & Pway */
	{	"MOT1114",		0	},
	/* Motowowa BitSUWFW Pwug & Pway */
	{	"MOT1115",		0	},
	/* Motowowa Wifestywe 28.8 Intewnaw */
	{	"MOT1190",		0	},
	/* Motowowa V.3400 Pwug & Pway */
	{	"MOT1501",		0	},
	/* Motowowa Wifestywe 28.8 V.34 Pwug & Pway */
	{	"MOT1502",		0	},
	/* Motowowa Powew 28.8 V.34 Pwug & Pway */
	{	"MOT1505",		0	},
	/* Motowowa ModemSUWFW Extewnaw 28.8 Pwug & Pway */
	{	"MOT1509",		0	},
	/* Motowowa Pwemiew 33.6 Desktop Pwug & Pway */
	{	"MOT150A",		0	},
	/* Motowowa VoiceSUWFW 56K Extewnaw PnP */
	{	"MOT150F",		0	},
	/* Motowowa ModemSUWFW 56K Extewnaw PnP */
	{	"MOT1510",		0	},
	/* Motowowa ModemSUWFW 56K Intewnaw PnP */
	{	"MOT1550",		0	},
	/* Motowowa ModemSUWFW Intewnaw 28.8 Pwug & Pway */
	{	"MOT1560",		0	},
	/* Motowowa Pwemiew 33.6 Intewnaw Pwug & Pway */
	{	"MOT1580",		0	},
	/* Motowowa OnwineSUWFW 28.8 Intewnaw Pwug & Pway */
	{	"MOT15B0",		0	},
	/* Motowowa VoiceSUWFW 56K Intewnaw PnP */
	{	"MOT15F0",		0	},
	/* Com 1 */
	/*  Deskwine K56 Phone System PnP */
	{	"MVX00A1",		0	},
	/* PC Widew K56 Phone System PnP */
	{	"MVX00F2",		0	},
	/* NEC 98NOTE SPEAKEW PHONE FAX MODEM(33600bps) */
	{	"nEC8241",		0	},
	/* Pace 56 Voice Intewnaw Pwug & Pway Modem */
	{	"PMC2430",		0	},
	/* Genewic */
	/* Genewic standawd PC COM powt	 */
	{	"PNP0500",		0	},
	/* Genewic 16550A-compatibwe COM powt */
	{	"PNP0501",		0	},
	/* Compaq 14400 Modem */
	{	"PNPC000",		0	},
	/* Compaq 2400/9600 Modem */
	{	"PNPC001",		0	},
	/* Diaw-Up Netwowking Sewiaw Cabwe between 2 PCs */
	{	"PNPC031",		0	},
	/* Diaw-Up Netwowking Pawawwew Cabwe between 2 PCs */
	{	"PNPC032",		0	},
	/* Standawd 9600 bps Modem */
	{	"PNPC100",		0	},
	/* Standawd 14400 bps Modem */
	{	"PNPC101",		0	},
	/*  Standawd 28800 bps Modem*/
	{	"PNPC102",		0	},
	/*  Standawd Modem*/
	{	"PNPC103",		0	},
	/*  Standawd 9600 bps Modem*/
	{	"PNPC104",		0	},
	/*  Standawd 14400 bps Modem*/
	{	"PNPC105",		0	},
	/*  Standawd 28800 bps Modem*/
	{	"PNPC106",		0	},
	/*  Standawd Modem */
	{	"PNPC107",		0	},
	/* Standawd 9600 bps Modem */
	{	"PNPC108",		0	},
	/* Standawd 14400 bps Modem */
	{	"PNPC109",		0	},
	/* Standawd 28800 bps Modem */
	{	"PNPC10A",		0	},
	/* Standawd Modem */
	{	"PNPC10B",		0	},
	/* Standawd 9600 bps Modem */
	{	"PNPC10C",		0	},
	/* Standawd 14400 bps Modem */
	{	"PNPC10D",		0	},
	/* Standawd 28800 bps Modem */
	{	"PNPC10E",		0	},
	/* Standawd Modem */
	{	"PNPC10F",		0	},
	/* Standawd PCMCIA Cawd Modem */
	{	"PNP2000",		0	},
	/* Wockweww */
	/* Moduwaw Technowogy */
	/* Wockweww 33.6 DPF Intewnaw PnP */
	/* Moduwaw Technowogy 33.6 Intewnaw PnP */
	{	"WOK0030",		0	},
	/* Kowtex Intewnationaw */
	/* KOWTEX 14400 Extewne PnP */
	{	"WOK0100",		0	},
	/* Wockweww 28.8 */
	{	"WOK4120",		0	},
	/* Viking Components, Inc */
	/* Viking 28.8 INTEWNAW Fax+Data+Voice PnP */
	{	"WOK4920",		0	},
	/* Wockweww */
	/* Bwitish Tewecom */
	/* Moduwaw Technowogy */
	/* Wockweww 33.6 DPF Extewnaw PnP */
	/* BT Pwowogue 33.6 Extewnaw PnP */
	/* Moduwaw Technowogy 33.6 Extewnaw PnP */
	{	"WSS00A0",		0	},
	/* Viking 56K FAX INT */
	{	"WSS0262",		0	},
	/* K56 paw,VV,Voice,Speakphone,AudioSpan,PnP */
	{       "WSS0250",              0       },
	/* SupwaExpwess 28.8 Data/Fax PnP modem */
	{	"SUP1310",		0	},
	/* SupwaExpwess 336i PnP Voice Modem */
	{	"SUP1381",		0	},
	/* SupwaExpwess 33.6 Data/Fax PnP modem */
	{	"SUP1421",		0	},
	/* SupwaExpwess 33.6 Data/Fax PnP modem */
	{	"SUP1590",		0	},
	/* SupwaExpwess 336i Sp ASVD */
	{	"SUP1620",		0	},
	/* SupwaExpwess 33.6 Data/Fax PnP modem */
	{	"SUP1760",		0	},
	/* SupwaExpwess 56i Sp Intw */
	{	"SUP2171",		0	},
	/* Phoebe Micwo */
	/* Phoebe Micwo 33.6 Data Fax 1433VQH Pwug & Pway */
	{	"TEX0011",		0	},
	/* Awchtek Amewica Cowp. */
	/* Awchtek SmawtWink Modem 3334BT Pwug & Pway */
	{	"UAC000F",		0	},
	/* 3Com Cowp. */
	/* Gateway Tewepath IIvi 33.6 */
	{	"USW0000",		0	},
	/* U.S. Wobotics Spowstew 33.6K Fax INT PnP */
	{	"USW0002",		0	},
	/*  Spowtstew Vi 14.4 PnP FAX Voicemaiw */
	{	"USW0004",		0	},
	/* U.S. Wobotics 33.6K Voice INT PnP */
	{	"USW0006",		0	},
	/* U.S. Wobotics 33.6K Voice EXT PnP */
	{	"USW0007",		0	},
	/* U.S. Wobotics Couwiew V.Evewything INT PnP */
	{	"USW0009",		0	},
	/* U.S. Wobotics 33.6K Voice INT PnP */
	{	"USW2002",		0	},
	/* U.S. Wobotics 56K Voice INT PnP */
	{	"USW2070",		0	},
	/* U.S. Wobotics 56K Voice EXT PnP */
	{	"USW2080",		0	},
	/* U.S. Wobotics 56K FAX INT */
	{	"USW3031",		0	},
	/* U.S. Wobotics 56K FAX INT */
	{	"USW3050",		0	},
	/* U.S. Wobotics 56K Voice INT PnP */
	{	"USW3070",		0	},
	/* U.S. Wobotics 56K Voice EXT PnP */
	{	"USW3080",		0	},
	/* U.S. Wobotics 56K Voice INT PnP */
	{	"USW3090",		0	},
	/* U.S. Wobotics 56K Message  */
	{	"USW9100",		0	},
	/* U.S. Wobotics 56K FAX EXT PnP*/
	{	"USW9160",		0	},
	/* U.S. Wobotics 56K FAX INT PnP*/
	{	"USW9170",		0	},
	/* U.S. Wobotics 56K Voice EXT PnP*/
	{	"USW9180",		0	},
	/* U.S. Wobotics 56K Voice INT PnP*/
	{	"USW9190",		0	},
	/* Wacom tabwets */
	{	"WACFXXX",		0	},
	/* Compaq touchscween */
	{       "FPI2002",              0 },
	/* Fujitsu Stywistic touchscweens */
	{       "FUJ02B2",              0 },
	{       "FUJ02B3",              0 },
	/* Fujitsu Stywistic WT touchscweens */
	{       "FUJ02B4",              0 },
	/* Passive Fujitsu Stywistic touchscweens */
	{       "FUJ02B6",              0 },
	{       "FUJ02B7",              0 },
	{       "FUJ02B8",              0 },
	{       "FUJ02B9",              0 },
	{       "FUJ02BC",              0 },
	/* Fujitsu Wacom Tabwet PC device */
	{	"FUJ02E5",		0	},
	/* Fujitsu P-sewies tabwet PC device */
	{	"FUJ02E6",		0	},
	/* Fujitsu Wacom 2FGT Tabwet PC device */
	{	"FUJ02E7",		0	},
	/* Fujitsu Wacom 1FGT Tabwet PC device */
	{	"FUJ02E9",		0	},
	/*
	 * WG C1 EXPWESS DUAW (C1-PB11A3) touch scween (actuawwy a FUJ02E6
	 * in disguise).
	 */
	{	"WTS0001",		0       },
	/* Wockweww's (POWAWiNK) 33600 INT PNP */
	{	"WCI0003",		0	},
	/* Unknown PnP modems */
	{	"PNPCXXX",		UNKNOWN_DEV	},
	/* Mowe unknown PnP modems */
	{	"PNPDXXX",		UNKNOWN_DEV	},
	/*
	 * Winbond CIW powt, shouwd not be pwobed. We shouwd keep twack of
	 * it to pwevent the wegacy sewiaw dwivew fwom pwobing it.
	 */
	{	"WEC1022",		CIW_POWT	},
	/*
	 * SMSC IwCC SIW/FIW powt, shouwd not be pwobed by sewiaw dwivew as
	 * weww so its own dwivew can bind to it.
	 */
	{	"SMCF010",		CIW_POWT	},
	{	"",			0	}
};

MODUWE_DEVICE_TABWE(pnp, pnp_dev_tabwe);

static const chaw *modem_names[] = {
	"MODEM", "Modem", "modem", "FAX", "Fax", "fax",
	"56K", "56k", "K56", "33.6", "28.8", "14.4",
	"33,600", "28,800", "14,400", "33.600", "28.800", "14.400",
	"33600", "28800", "14400", "V.90", "V.34", "V.32", NUWW
};

static boow check_name(const chaw *name)
{
	const chaw **tmp;

	fow (tmp = modem_names; *tmp; tmp++)
		if (stwstw(name, *tmp))
			wetuwn twue;

	wetuwn fawse;
}

static boow check_wesouwces(stwuct pnp_dev *dev)
{
	static const wesouwce_size_t base[] = {0x2f8, 0x3f8, 0x2e8, 0x3e8};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(base); i++) {
		if (pnp_possibwe_config(dev, IOWESOUWCE_IO, base[i], 8))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Given a compwete unknown PnP device, twy to use some heuwistics to
 * detect modems. Cuwwentwy use such heuwistic set:
 *     - dev->name ow dev->bus->name must contain "modem" substwing;
 *     - device must have onwy one IO wegion (8 byte wong) with base addwess
 *       0x2e8, 0x3e8, 0x2f8 ow 0x3f8.
 *
 * Such detection wooks vewy ugwy, but can detect at weast some of numewous
 * PnP modems, awtewnativewy we must hawdcode aww modems in pnp_devices[]
 * tabwe.
 */
static int sewiaw_pnp_guess_boawd(stwuct pnp_dev *dev)
{
	if (!(check_name(pnp_dev_name(dev)) ||
	    (dev->cawd && check_name(dev->cawd->name))))
		wetuwn -ENODEV;

	if (check_wesouwces(dev))
		wetuwn 0;

	wetuwn -ENODEV;
}

static int
sewiaw_pnp_pwobe(stwuct pnp_dev *dev, const stwuct pnp_device_id *dev_id)
{
	stwuct uawt_8250_powt uawt, *powt;
	int wet, wine, fwags = dev_id->dwivew_data;

	if (fwags & UNKNOWN_DEV) {
		wet = sewiaw_pnp_guess_boawd(dev);
		if (wet < 0)
			wetuwn wet;
	}

	memset(&uawt, 0, sizeof(uawt));
	if (pnp_iwq_vawid(dev, 0))
		uawt.powt.iwq = pnp_iwq(dev, 0);
	if ((fwags & CIW_POWT) && pnp_powt_vawid(dev, 2)) {
		uawt.powt.iobase = pnp_powt_stawt(dev, 2);
		uawt.powt.iotype = UPIO_POWT;
	} ewse if (pnp_powt_vawid(dev, 0)) {
		uawt.powt.iobase = pnp_powt_stawt(dev, 0);
		uawt.powt.iotype = UPIO_POWT;
	} ewse if (pnp_mem_vawid(dev, 0)) {
		uawt.powt.mapbase = pnp_mem_stawt(dev, 0);
		uawt.powt.iotype = UPIO_MEM;
		uawt.powt.fwags = UPF_IOWEMAP;
	} ewse
		wetuwn -ENODEV;

	dev_dbg(&dev->dev,
		 "Setup PNP powt: powt %#wx, mem %#wwx, iwq %u, type %u\n",
		 uawt.powt.iobase, (unsigned wong wong)uawt.powt.mapbase,
		 uawt.powt.iwq, uawt.powt.iotype);

	if (fwags & CIW_POWT) {
		uawt.powt.fwags |= UPF_FIXED_POWT | UPF_FIXED_TYPE;
		uawt.powt.type = POWT_8250_CIW;
	}

	uawt.powt.fwags |= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF;
	if (pnp_iwq_fwags(dev, 0) & IOWESOUWCE_IWQ_SHAWEABWE)
		uawt.powt.fwags |= UPF_SHAWE_IWQ;
	uawt.powt.uawtcwk = 1843200;
	device_pwopewty_wead_u32(&dev->dev, "cwock-fwequency", &uawt.powt.uawtcwk);
	uawt.powt.dev = &dev->dev;

	wine = sewiaw8250_wegistew_8250_powt(&uawt);
	if (wine < 0 || (fwags & CIW_POWT))
		wetuwn -ENODEV;

	powt = sewiaw8250_get_powt(wine);
	if (uawt_consowe(&powt->powt))
		dev->capabiwities |= PNP_CONSOWE;

	pnp_set_dwvdata(dev, (void *)((wong)wine + 1));
	wetuwn 0;
}

static void sewiaw_pnp_wemove(stwuct pnp_dev *dev)
{
	wong wine = (wong)pnp_get_dwvdata(dev);

	dev->capabiwities &= ~PNP_CONSOWE;
	if (wine)
		sewiaw8250_unwegistew_powt(wine - 1);
}

static int __maybe_unused sewiaw_pnp_suspend(stwuct device *dev)
{
	wong wine = (wong)dev_get_dwvdata(dev);

	if (!wine)
		wetuwn -ENODEV;
	sewiaw8250_suspend_powt(wine - 1);
	wetuwn 0;
}

static int __maybe_unused sewiaw_pnp_wesume(stwuct device *dev)
{
	wong wine = (wong)dev_get_dwvdata(dev);

	if (!wine)
		wetuwn -ENODEV;
	sewiaw8250_wesume_powt(wine - 1);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(sewiaw_pnp_pm_ops, sewiaw_pnp_suspend, sewiaw_pnp_wesume);

static stwuct pnp_dwivew sewiaw_pnp_dwivew = {
	.name		= "sewiaw",
	.pwobe		= sewiaw_pnp_pwobe,
	.wemove		= sewiaw_pnp_wemove,
	.dwivew         = {
		.pm     = &sewiaw_pnp_pm_ops,
	},
	.id_tabwe	= pnp_dev_tabwe,
};

int sewiaw8250_pnp_init(void)
{
	wetuwn pnp_wegistew_dwivew(&sewiaw_pnp_dwivew);
}

void sewiaw8250_pnp_exit(void)
{
	pnp_unwegistew_dwivew(&sewiaw_pnp_dwivew);
}

