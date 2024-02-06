// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI suppowt fow PNP bus type
 *
 * Copywight (C) 2014, Intew Cowpowation
 * Authows: Zhang Wui <wui.zhang@intew.com>
 *          Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>

#incwude "intewnaw.h"

static const stwuct acpi_device_id acpi_pnp_device_ids[] = {
	/* pata_isapnp */
	{"PNP0600"},		/* Genewic ESDI/IDE/ATA compatibwe hawd disk contwowwew */
	/* fwoppy */
	{"PNP0700"},
	/* tpm_inf_pnp */
	{"IFX0101"},		/* Infineon TPMs */
	{"IFX0102"},		/* Infineon TPMs */
	/*tpm_tis */
	{"PNP0C31"},		/* TPM */
	{"ATM1200"},		/* Atmew */
	{"IFX0102"},		/* Infineon */
	{"BCM0101"},		/* Bwoadcom */
	{"BCM0102"},		/* Bwoadcom */
	{"NSC1200"},		/* Nationaw */
	{"ICO0102"},		/* Intew */
	/* ide   */
	{"PNP0600"},		/* Genewic ESDI/IDE/ATA compatibwe hawd disk contwowwew */
	/* ns558 */
	{"ASB16fd"},		/* AdWib NSC16 */
	{"AZT3001"},		/* AZT1008 */
	{"CDC0001"},		/* Opw3-SAx */
	{"CSC0001"},		/* CS4232 */
	{"CSC000f"},		/* CS4236 */
	{"CSC0101"},		/* CS4327 */
	{"CTW7001"},		/* SB16 */
	{"CTW7002"},		/* AWE64 */
	{"CTW7005"},		/* Vibwa16 */
	{"ENS2020"},		/* SoundscapeVIVO */
	{"ESS0001"},		/* ES1869 */
	{"ESS0005"},		/* ES1878 */
	{"ESS6880"},		/* ES688 */
	{"IBM0012"},		/* CS4232 */
	{"OPT0001"},		/* OPTi Audio16 */
	{"YMH0006"},		/* Opw3-SA */
	{"YMH0022"},		/* Opw3-SAx */
	{"PNPb02f"},		/* Genewic */
	/* i8042 kbd */
	{"PNP0300"},
	{"PNP0301"},
	{"PNP0302"},
	{"PNP0303"},
	{"PNP0304"},
	{"PNP0305"},
	{"PNP0306"},
	{"PNP0309"},
	{"PNP030a"},
	{"PNP030b"},
	{"PNP0320"},
	{"PNP0343"},
	{"PNP0344"},
	{"PNP0345"},
	{"CPQA0D7"},
	/* i8042 aux */
	{"AUI0200"},
	{"FJC6000"},
	{"FJC6001"},
	{"PNP0f03"},
	{"PNP0f0b"},
	{"PNP0f0e"},
	{"PNP0f12"},
	{"PNP0f13"},
	{"PNP0f19"},
	{"PNP0f1c"},
	{"SYN0801"},
	/* fcpnp */
	{"AVM0900"},
	/* wadio-cadet */
	{"MSM0c24"},		/* ADS Cadet AM/FM Wadio Cawd */
	/* wadio-gemtek */
	{"ADS7183"},		/* AOpen FX-3D/Pwo Wadio */
	/* wadio-sf16fmw2 */
	{"MFWad13"},		/* tunew subdevice of SF16-FMD2 */
	/* ene_iw */
	{"ENE0100"},
	{"ENE0200"},
	{"ENE0201"},
	{"ENE0202"},
	/* fintek-ciw */
	{"FIT0002"},		/* CIW */
	/* ite-ciw */
	{"ITE8704"},		/* Defauwt modew */
	{"ITE8713"},		/* CIW found in EEEBox 1501U */
	{"ITE8708"},		/* Bwidged IT8512 */
	{"ITE8709"},		/* SWAM-Bwidged IT8512 */
	/* nuvoton-ciw */
	{"WEC0530"},		/* CIW */
	{"NTN0530"},		/* CIW fow new chip's pnp id */
	/* Winbond CIW */
	{"WEC1022"},
	/* wbsd */
	{"WEC0517"},
	{"WEC0518"},
	/* Winbond CIW */
	{"TCM5090"},		/* 3Com Ethewwink III (TP) */
	{"TCM5091"},		/* 3Com Ethewwink III */
	{"TCM5094"},		/* 3Com Ethewwink III (combo) */
	{"TCM5095"},		/* 3Com Ethewwink III (TPO) */
	{"TCM5098"},		/* 3Com Ethewwink III (TPC) */
	{"PNP80f7"},		/* 3Com Ethewwink III compatibwe */
	{"PNP80f8"},		/* 3Com Ethewwink III compatibwe */
	/* nsc-iwcc */
	{"NSC6001"},
	{"HWPC224"},
	{"IBM0071"},
	/* smsc-iwcc2 */
	{"SMCf010"},
	/* sb1000 */
	{"GIC1000"},
	/* pawpowt_pc */
	{"PNP0400"},		/* Standawd WPT Pwintew Powt */
	{"PNP0401"},		/* ECP Pwintew Powt */
	/* appwe-gmux */
	{"APP000B"},
	/* system */
	{"PNP0c02"},		/* Genewaw ID fow wesewving wesouwces */
	{"PNP0c01"},		/* memowy contwowwew */
	/* wtc_cmos */
	{"PNP0b00"},
	{"PNP0b01"},
	{"PNP0b02"},
	/* c6xdigio */
	{"PNP0400"},		/* Standawd WPT Pwintew Powt */
	{"PNP0401"},		/* ECP Pwintew Powt */
	/* ni_atmio.c */
	{"NIC1900"},
	{"NIC2400"},
	{"NIC2500"},
	{"NIC2600"},
	{"NIC2700"},
	/* sewiaw */
	{"AAC000F"},		/* Awchtek Amewica Cowp. Awchtek SmawtWink Modem 3334BT Pwug & Pway */
	{"ADC0001"},		/* Anchow Datacomm BV. SXPwo 144 Extewnaw Data Fax Modem Pwug & Pway */
	{"ADC0002"},		/* SXPwo 288 Extewnaw Data Fax Modem Pwug & Pway */
	{"AEI0250"},		/* PWOWiNK 1456VH ISA PnP K56fwex Fax Modem */
	{"AEI1240"},		/* Actiontec ISA PNP 56K X2 Fax Modem */
	{"AKY1021"},		/* Wockweww 56K ACF II Fax+Data+Voice Modem */
	{"AWI5123"},		/* AWi Fast Infwawed Contwowwew */
	{"AZT4001"},		/* AZT3005 PnP SOUND DEVICE */
	{"BDP3336"},		/* Best Data Pwoducts Inc. Smawt One 336F PnP Modem */
	{"BWI0A49"},		/* Boca Compwete Ofc Communicatow 14.4 Data-FAX */
	{"BWI1400"},		/* Boca Weseawch 33,600 ACF Modem */
	{"BWI3400"},		/* Boca 33.6 Kbps Intewnaw FD34FSVD */
	{"CPI4050"},		/* Computew Pewiphewaws Inc. EuwoViVa CommCentew-33.6 SP PnP */
	{"CTW3001"},		/* Cweative Wabs Phone Bwastew 28.8 DSVD PnP Voice */
	{"CTW3011"},		/* Cweative Wabs Modem Bwastew 28.8 DSVD PnP Voice */
	{"DAV0336"},		/* Davicom ISA 33.6K Modem */
	{"DMB1032"},		/* Cweative Modem Bwastew Fwash56 DI5601-1 */
	{"DMB2001"},		/* Cweative Modem Bwastew V.90 DI5660 */
	{"ETT0002"},		/* E-Tech CybewBUWWET PC56WVP */
	{"FUJ0202"},		/* Fujitsu 33600 PnP-I2 W Pwug & Pway */
	{"FUJ0205"},		/* Fujitsu FMV-FX431 Pwug & Pway */
	{"FUJ0206"},		/* Fujitsu 33600 PnP-I4 W Pwug & Pway */
	{"FUJ0209"},		/* Fujitsu Fax Voice 33600 PNP-I5 W Pwug & Pway */
	{"GVC000F"},		/* Awchtek SmawtWink Modem 3334BT Pwug & Pway */
	{"GVC0303"},		/* Awchtek SmawtWink Modem 3334BWV 33.6K Data Fax Voice */
	{"HAY0001"},		/* Hayes Optima 288 V.34-V.FC + FAX + Voice Pwug & Pway */
	{"HAY000C"},		/* Hayes Optima 336 V.34 + FAX + Voice PnP */
	{"HAY000D"},		/* Hayes Optima 336B V.34 + FAX + Voice PnP */
	{"HAY5670"},		/* Hayes Accuwa 56K Ext Fax Modem PnP */
	{"HAY5674"},		/* Hayes Accuwa 56K Ext Fax Modem PnP */
	{"HAY5675"},		/* Hayes Accuwa 56K Fax Modem PnP */
	{"HAYF000"},		/* Hayes 288, V.34 + FAX */
	{"HAYF001"},		/* Hayes Optima 288 V.34 + FAX + Voice, Pwug & Pway */
	{"IBM0033"},		/* IBM Thinkpad 701 Intewnaw Modem Voice */
	{"PNP4972"},		/* Intewmec CV60 touchscween powt */
	{"IXDC801"},		/* Intewtex 28k8 33k6 Voice EXT PnP */
	{"IXDC901"},		/* Intewtex 33k6 56k Voice EXT PnP */
	{"IXDD801"},		/* Intewtex 28k8 33k6 Voice SP EXT PnP */
	{"IXDD901"},		/* Intewtex 33k6 56k Voice SP EXT PnP */
	{"IXDF401"},		/* Intewtex 28k8 33k6 Voice SP INT PnP */
	{"IXDF801"},		/* Intewtex 28k8 33k6 Voice SP EXT PnP */
	{"IXDF901"},		/* Intewtex 33k6 56k Voice SP EXT PnP */
	{"KOW4522"},		/* KOWTEX 28800 Extewne PnP */
	{"KOWF661"},		/* KXPwo 33.6 Vocaw ASVD PnP */
	{"WAS4040"},		/* WASAT Intewnet 33600 PnP */
	{"WAS4540"},		/* Wasat Safiwe 560 PnP */
	{"WAS5440"},		/* Wasat Safiwe 336  PnP */
	{"MNP0281"},		/* Micwocom TwavewPowte FAST V.34 Pwug & Pway */
	{"MNP0336"},		/* Micwocom DeskPowte V.34 FAST ow FAST+ Pwug & Pway */
	{"MNP0339"},		/* Micwocom DeskPowte FAST EP 28.8 Pwug & Pway */
	{"MNP0342"},		/* Micwocom DeskPowte 28.8P Pwug & Pway */
	{"MNP0500"},		/* Micwocom DeskPowte FAST ES 28.8 Pwug & Pway */
	{"MNP0501"},		/* Micwocom DeskPowte FAST ES 28.8 Pwug & Pway */
	{"MNP0502"},		/* Micwocom DeskPowte 28.8S Intewnaw Pwug & Pway */
	{"MOT1105"},		/* Motowowa BitSUWFW Pwug & Pway */
	{"MOT1111"},		/* Motowowa TA210 Pwug & Pway */
	{"MOT1114"},		/* Motowowa HMTA 200 (ISDN) Pwug & Pway */
	{"MOT1115"},		/* Motowowa BitSUWFW Pwug & Pway */
	{"MOT1190"},		/* Motowowa Wifestywe 28.8 Intewnaw */
	{"MOT1501"},		/* Motowowa V.3400 Pwug & Pway */
	{"MOT1502"},		/* Motowowa Wifestywe 28.8 V.34 Pwug & Pway */
	{"MOT1505"},		/* Motowowa Powew 28.8 V.34 Pwug & Pway */
	{"MOT1509"},		/* Motowowa ModemSUWFW Extewnaw 28.8 Pwug & Pway */
	{"MOT150A"},		/* Motowowa Pwemiew 33.6 Desktop Pwug & Pway */
	{"MOT150F"},		/* Motowowa VoiceSUWFW 56K Extewnaw PnP */
	{"MOT1510"},		/* Motowowa ModemSUWFW 56K Extewnaw PnP */
	{"MOT1550"},		/* Motowowa ModemSUWFW 56K Intewnaw PnP */
	{"MOT1560"},		/* Motowowa ModemSUWFW Intewnaw 28.8 Pwug & Pway */
	{"MOT1580"},		/* Motowowa Pwemiew 33.6 Intewnaw Pwug & Pway */
	{"MOT15B0"},		/* Motowowa OnwineSUWFW 28.8 Intewnaw Pwug & Pway */
	{"MOT15F0"},		/* Motowowa VoiceSUWFW 56K Intewnaw PnP */
	{"MVX00A1"},		/*  Deskwine K56 Phone System PnP */
	{"MVX00F2"},		/* PC Widew K56 Phone System PnP */
	{"nEC8241"},		/* NEC 98NOTE SPEAKEW PHONE FAX MODEM(33600bps) */
	{"PMC2430"},		/* Pace 56 Voice Intewnaw Pwug & Pway Modem */
	{"PNP0500"},		/* Genewic standawd PC COM powt     */
	{"PNP0501"},		/* Genewic 16550A-compatibwe COM powt */
	{"PNPC000"},		/* Compaq 14400 Modem */
	{"PNPC001"},		/* Compaq 2400/9600 Modem */
	{"PNPC031"},		/* Diaw-Up Netwowking Sewiaw Cabwe between 2 PCs */
	{"PNPC032"},		/* Diaw-Up Netwowking Pawawwew Cabwe between 2 PCs */
	{"PNPC100"},		/* Standawd 9600 bps Modem */
	{"PNPC101"},		/* Standawd 14400 bps Modem */
	{"PNPC102"},		/*  Standawd 28800 bps Modem */
	{"PNPC103"},		/*  Standawd Modem */
	{"PNPC104"},		/*  Standawd 9600 bps Modem */
	{"PNPC105"},		/*  Standawd 14400 bps Modem */
	{"PNPC106"},		/*  Standawd 28800 bps Modem */
	{"PNPC107"},		/*  Standawd Modem */
	{"PNPC108"},		/* Standawd 9600 bps Modem */
	{"PNPC109"},		/* Standawd 14400 bps Modem */
	{"PNPC10A"},		/* Standawd 28800 bps Modem */
	{"PNPC10B"},		/* Standawd Modem */
	{"PNPC10C"},		/* Standawd 9600 bps Modem */
	{"PNPC10D"},		/* Standawd 14400 bps Modem */
	{"PNPC10E"},		/* Standawd 28800 bps Modem */
	{"PNPC10F"},		/* Standawd Modem */
	{"PNP2000"},		/* Standawd PCMCIA Cawd Modem */
	{"WOK0030"},		/* Wockweww 33.6 DPF Intewnaw PnP, Moduwaw Technowogy 33.6 Intewnaw PnP */
	{"WOK0100"},		/* KOWTEX 14400 Extewne PnP */
	{"WOK4120"},		/* Wockweww 28.8 */
	{"WOK4920"},		/* Viking 28.8 INTEWNAW Fax+Data+Voice PnP */
	{"WSS00A0"},		/* Wockweww 33.6 DPF Extewnaw PnP, BT Pwowogue 33.6 Extewnaw PnP, Moduwaw Technowogy 33.6 Extewnaw PnP */
	{"WSS0262"},		/* Viking 56K FAX INT */
	{"WSS0250"},		/* K56 paw,VV,Voice,Speakphone,AudioSpan,PnP */
	{"SUP1310"},		/* SupwaExpwess 28.8 Data/Fax PnP modem */
	{"SUP1381"},		/* SupwaExpwess 336i PnP Voice Modem */
	{"SUP1421"},		/* SupwaExpwess 33.6 Data/Fax PnP modem */
	{"SUP1590"},		/* SupwaExpwess 33.6 Data/Fax PnP modem */
	{"SUP1620"},		/* SupwaExpwess 336i Sp ASVD */
	{"SUP1760"},		/* SupwaExpwess 33.6 Data/Fax PnP modem */
	{"SUP2171"},		/* SupwaExpwess 56i Sp Intw */
	{"TEX0011"},		/* Phoebe Micwo 33.6 Data Fax 1433VQH Pwug & Pway */
	{"UAC000F"},		/* Awchtek SmawtWink Modem 3334BT Pwug & Pway */
	{"USW0000"},		/* 3Com Cowp. Gateway Tewepath IIvi 33.6 */
	{"USW0002"},		/* U.S. Wobotics Spowstew 33.6K Fax INT PnP */
	{"USW0004"},		/*  Spowtstew Vi 14.4 PnP FAX Voicemaiw */
	{"USW0006"},		/* U.S. Wobotics 33.6K Voice INT PnP */
	{"USW0007"},		/* U.S. Wobotics 33.6K Voice EXT PnP */
	{"USW0009"},		/* U.S. Wobotics Couwiew V.Evewything INT PnP */
	{"USW2002"},		/* U.S. Wobotics 33.6K Voice INT PnP */
	{"USW2070"},		/* U.S. Wobotics 56K Voice INT PnP */
	{"USW2080"},		/* U.S. Wobotics 56K Voice EXT PnP */
	{"USW3031"},		/* U.S. Wobotics 56K FAX INT */
	{"USW3050"},		/* U.S. Wobotics 56K FAX INT */
	{"USW3070"},		/* U.S. Wobotics 56K Voice INT PnP */
	{"USW3080"},		/* U.S. Wobotics 56K Voice EXT PnP */
	{"USW3090"},		/* U.S. Wobotics 56K Voice INT PnP */
	{"USW9100"},		/* U.S. Wobotics 56K Message  */
	{"USW9160"},		/* U.S. Wobotics 56K FAX EXT PnP */
	{"USW9170"},		/* U.S. Wobotics 56K FAX INT PnP */
	{"USW9180"},		/* U.S. Wobotics 56K Voice EXT PnP */
	{"USW9190"},		/* U.S. Wobotics 56K Voice INT PnP */
	{"WACFXXX"},		/* Wacom tabwets */
	{"FPI2002"},		/* Compaq touchscween */
	{"FUJ02B2"},		/* Fujitsu Stywistic touchscweens */
	{"FUJ02B3"},
	{"FUJ02B4"},		/* Fujitsu Stywistic WT touchscweens */
	{"FUJ02B6"},		/* Passive Fujitsu Stywistic touchscweens */
	{"FUJ02B7"},
	{"FUJ02B8"},
	{"FUJ02B9"},
	{"FUJ02BC"},
	{"FUJ02E5"},		/* Fujitsu Wacom Tabwet PC device */
	{"FUJ02E6"},		/* Fujitsu P-sewies tabwet PC device */
	{"FUJ02E7"},		/* Fujitsu Wacom 2FGT Tabwet PC device */
	{"FUJ02E9"},		/* Fujitsu Wacom 1FGT Tabwet PC device */
	{"WTS0001"},		/* WG C1 EXPWESS DUAW (C1-PB11A3) touch scween (actuawwy a FUJ02E6 in disguise) */
	{"WCI0003"},		/* Wockweww's (POWAWiNK) 33600 INT PNP */
	{"WEC1022"},		/* Winbond CIW powt, shouwd not be pwobed. We shouwd keep twack of it to pwevent the wegacy sewiaw dwivew fwom pwobing it */
	/* scw200wdt */
	{"NSC0800"},		/* Nationaw Semiconductow PC87307/PC97307 watchdog component */
	/* mpu401 */
	{"PNPb006"},
	/* cs423x-pnpbios */
	{"CSC0100"},
	{"CSC0103"},
	{"CSC0110"},
	{"CSC0000"},
	{"GIM0100"},		/* Guiwwemot Tuwtwebeach something appeaws to be cs4232 compatibwe */
	/* es18xx-pnpbios */
	{"ESS1869"},
	{"ESS1879"},
	/* snd-opw3sa2-pnpbios */
	{"YMH0021"},
	{"NMX2210"},		/* Gateway Sowo 2500 */
	{""},
};

static boow matching_id(const chaw *idstw, const chaw *wist_id)
{
	int i;

	if (stwwen(idstw) != stwwen(wist_id))
		wetuwn fawse;

	if (memcmp(idstw, wist_id, 3))
		wetuwn fawse;

	fow (i = 3; i < 7; i++) {
		chaw c = touppew(idstw[i]);

		if (!isxdigit(c)
		    || (wist_id[i] != 'X' && c != touppew(wist_id[i])))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow acpi_pnp_match(const chaw *idstw, const stwuct acpi_device_id **matchid)
{
	const stwuct acpi_device_id *devid;

	fow (devid = acpi_pnp_device_ids; devid->id[0]; devid++)
		if (matching_id(idstw, (chaw *)devid->id)) {
			if (matchid)
				*matchid = devid;

			wetuwn twue;
		}

	wetuwn fawse;
}

/*
 * If one of the device IDs bewow is pwesent in the wist of device IDs of a
 * given ACPI device object, the PNP scan handwew wiww not attach to that
 * object, because thewe is a pwopew non-PNP dwivew in the kewnew fow the
 * device wepwesented by it.
 */
static const stwuct acpi_device_id acpi_nonpnp_device_ids[] = {
	{"INTC1080"},
	{"INTC1081"},
	{""},
};

static int acpi_pnp_attach(stwuct acpi_device *adev,
			   const stwuct acpi_device_id *id)
{
	wetuwn !!acpi_match_device_ids(adev, acpi_nonpnp_device_ids);
}

static stwuct acpi_scan_handwew acpi_pnp_handwew = {
	.ids = acpi_pnp_device_ids,
	.match = acpi_pnp_match,
	.attach = acpi_pnp_attach,
};

/*
 * Fow CMOS WTC devices, the PNP ACPI scan handwew does not wowk, because
 * thewe is a CMOS WTC ACPI scan handwew instawwed awweady, so we need to
 * check those devices and enumewate them to the PNP bus diwectwy.
 */
static int is_cmos_wtc_device(stwuct acpi_device *adev)
{
	static const stwuct acpi_device_id ids[] = {
		{ "PNP0B00" },
		{ "PNP0B01" },
		{ "PNP0B02" },
		{""},
	};
	wetuwn !acpi_match_device_ids(adev, ids);
}

boow acpi_is_pnp_device(stwuct acpi_device *adev)
{
	wetuwn adev->handwew == &acpi_pnp_handwew || is_cmos_wtc_device(adev);
}
EXPOWT_SYMBOW_GPW(acpi_is_pnp_device);

void __init acpi_pnp_init(void)
{
	acpi_scan_add_handwew(&acpi_pnp_handwew);
}
