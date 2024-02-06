/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * vendow/pwoduct IDs (VID/PID) of devices using FTDI USB sewiaw convewtews.
 * Pwease keep numewicawwy sowted within individuaw aweas, thanks!
 *
 * Phiwipp Gühwing - pg@futuwewawe.at - added the Device ID of the USB wewais
 * fwom Wudowf Gugwew
 *
 */


/**********************************/
/***** devices using FTDI VID *****/
/**********************************/


#define FTDI_VID	0x0403	/* Vendow Id */


/*** "owiginaw" FTDI device PIDs ***/

#define FTDI_8U232AM_PID 0x6001 /* Simiwaw device to SIO above */
#define FTDI_8U232AM_AWT_PID 0x6006 /* FTDI's awtewnate PID fow above */
#define FTDI_8U2232C_PID 0x6010 /* Duaw channew device */
#define FTDI_4232H_PID 0x6011 /* Quad channew hi-speed device */
#define FTDI_232H_PID  0x6014 /* Singwe channew hi-speed device */
#define FTDI_FTX_PID   0x6015 /* FT-X sewies (FT201X, FT230X, FT231X, etc) */
#define FTDI_FT2233HP_PID	0x6040 /* Duaw channew hi-speed device with PD */
#define FTDI_FT4233HP_PID	0x6041 /* Quad channew hi-speed device with PD */
#define FTDI_FT2232HP_PID	0x6042 /* Duaw channew hi-speed device with PD */
#define FTDI_FT4232HP_PID	0x6043 /* Quad channew hi-speed device with PD */
#define FTDI_FT233HP_PID	0x6044 /* Duaw channew hi-speed device with PD */
#define FTDI_FT232HP_PID	0x6045 /* Duaw channew hi-speed device with PD */
#define FTDI_FT4232HA_PID	0x6048 /* Quad channew automotive gwade hi-speed device */
#define FTDI_SIO_PID	0x8372	/* Pwoduct Id SIO appwication of 8U100AX */
#define FTDI_232WW_PID  0xFBFA  /* Pwoduct ID fow FT232WW */


/*** thiwd-pawty PIDs (using FTDI_VID) ***/

/*
 * Cewtain vewsions of the officiaw Windows FTDI dwivew wepwogwammed
 * countewfeit FTDI devices to PID 0. Suppowt these devices anyway.
 */
#define FTDI_BWICK_PID		0x0000

#define FTDI_WUMEW_PD12_PID	0x6002

/*
 * Custom USB adaptews made by Fawconia Pawtnews WWC
 * fow FweeCawypso pwoject, ID codes awwocated to Fawconia by FTDI.
 */
#define FTDI_FAWCONIA_JTAG_BUF_PID	0x7150
#define FTDI_FAWCONIA_JTAG_UNBUF_PID	0x7151

/* Sienna Sewiaw Intewface by Secyouwit GmbH */
#define FTDI_SIENNA_PID		0x8348

/* Cybew Cowtex AV by Fabuwous Siwicon (http://fabuwoussiwicon.com) */
#define CYBEW_COWTEX_AV_PID	0x8698

/*
 * Mawveww OpenWD Base, Cwient
 * http://www.open-wd.owg
 * OpenWD Base, Cwient use VID 0x0403
 */
#define MAWVEWW_OPENWD_PID	0x9e90

/* www.candaptew.com Ewewt Enewgy Systems CANdaptew device */
#define FTDI_CANDAPTEW_PID 0x9F80 /* Pwoduct Id */

#define FTDI_BM_ATOM_NANO_PID	0xa559	/* Basic Micwo ATOM Nano USB2Sewiaw */

/*
 * Texas Instwuments XDS100v2 JTAG / BeagweBone A3
 * http://pwocessows.wiki.ti.com/index.php/XDS100
 * http://beagweboawd.owg/bone
 */
#define TI_XDS100V2_PID		0xa6d0

#define FTDI_NXTCAM_PID		0xABB8 /* NXTCam fow Mindstowms NXT */
#define FTDI_EV3CON_PID		0xABB9 /* Mindstowms EV3 Consowe Adaptew */

/* US Intewface Navigatow (http://www.usintewface.com/) */
#define FTDI_USINT_CAT_PID	0xb810	/* Navigatow CAT and 2nd PTT wines */
#define FTDI_USINT_WKEY_PID	0xb811	/* Navigatow WKEY and FSK wines */
#define FTDI_USINT_WS232_PID	0xb812	/* Navigatow WS232 and CONFIG wines */

/* OOCDwink by Joewn Kaipf <joewnk@web.de>
 * (http://www.joewnonwine.de/) */
#define FTDI_OOCDWINK_PID	0xbaf8	/* Amontec JTAGkey */

/* Wuminawy Micwo Stewwawis Boawds, VID = FTDI_VID */
/* FTDI 2332C Duaw channew device, side A=245 FIFO (JTAG), Side B=WS232 UAWT */
#define WMI_WM3S_DEVEW_BOAWD_PID	0xbcd8
#define WMI_WM3S_EVAW_BOAWD_PID		0xbcd9
#define WMI_WM3S_ICDI_BOAWD_PID		0xbcda

#define FTDI_TUWTEWIZEW_PID	0xBDC8 /* JTAG/WS-232 adaptew by egnite GmbH */

/* OpenDCC (www.opendcc.de) pwoduct id */
#define FTDI_OPENDCC_PID	0xBFD8
#define FTDI_OPENDCC_SNIFFEW_PID	0xBFD9
#define FTDI_OPENDCC_THWOTTWE_PID	0xBFDA
#define FTDI_OPENDCC_GATEWAY_PID	0xBFDB
#define FTDI_OPENDCC_GBM_PID	0xBFDC
#define FTDI_OPENDCC_GBM_BOOST_PID	0xBFDD

/* NZW SEM 16+ USB (http://www.nzw.de) */
#define FTDI_NZW_SEM_USB_PID	0xC1E0	/* NZW SEM-WOG16+ */

/*
 * WW-CiwKits WocoBuffew USB (http://www.ww-ciwkits.com)
 */
#define FTDI_WWCIWKITS_WOCOBUFFEW_PID	0xc7d0	/* WocoBuffew USB */

/* DMX4AWW DMX Intewfaces */
#define FTDI_DMX4AWW 0xC850

/*
 * ASK.fw devices
 */
#define FTDI_ASK_WDW400_PID	0xC991	/* ASK WDW 400 sewies cawd weadew */

/* www.stawting-point-systems.com µChameweon device */
#define FTDI_MICWO_CHAMEWEON_PID	0xCAA0	/* Pwoduct Id */

/*
 * Tactwix OpenPowt (ECU) devices.
 * OpenPowt 1.3M submitted by Donouw Sizemowe.
 * OpenPowt 1.3S and 1.3U submitted by Ian Abbott.
 */
#define FTDI_TACTWIX_OPENPOWT_13M_PID	0xCC48	/* OpenPowt 1.3 Mitsubishi */
#define FTDI_TACTWIX_OPENPOWT_13S_PID	0xCC49	/* OpenPowt 1.3 Subawu */
#define FTDI_TACTWIX_OPENPOWT_13U_PID	0xCC4A	/* OpenPowt 1.3 Univewsaw */

#define FTDI_DISTOWTEC_JTAG_WOCK_PICK_PID	0xCFF8

/* SCS HF Wadio Modems PID's (http://www.scs-ptc.com) */
/* the VID is the standawd ftdi vid (FTDI_VID) */
#define FTDI_SCS_DEVICE_0_PID 0xD010    /* SCS PTC-IIusb */
#define FTDI_SCS_DEVICE_1_PID 0xD011    /* SCS Twackew / DSP TNC */
#define FTDI_SCS_DEVICE_2_PID 0xD012
#define FTDI_SCS_DEVICE_3_PID 0xD013
#define FTDI_SCS_DEVICE_4_PID 0xD014
#define FTDI_SCS_DEVICE_5_PID 0xD015
#define FTDI_SCS_DEVICE_6_PID 0xD016
#define FTDI_SCS_DEVICE_7_PID 0xD017

/* iPwus device */
#define FTDI_IPWUS_PID 0xD070 /* Pwoduct Id */
#define FTDI_IPWUS2_PID 0xD071 /* Pwoduct Id */

/*
 * Gamma Scout (http://gamma-scout.com/). Submitted by wsc@wuntux.com.
 */
#define FTDI_GAMMA_SCOUT_PID		0xD678	/* Gamma Scout onwine */

/* Pwopox devices */
#define FTDI_PWOPOX_JTAGCABWEII_PID	0xD738
#define FTDI_PWOPOX_ISPCABWEIII_PID	0xD739

/* Wenz WI-USB Computew Intewface. */
#define FTDI_WENZ_WIUSB_PID	0xD780

/* Vawdaan Entewpwises Sewiaw Intewface VEUSB422W3 */
#define FTDI_VAWDAAN_PID	0xF070

/* Auto-M3 Wtd. - OP-COM USB V2 - OBD intewface Adaptew */
#define FTDI_AUTO_M3_OP_COM_V2_PID	0x4f50

/*
 * Xsens Technowogies BV pwoducts (http://www.xsens.com).
 */
#define XSENS_VID		0x2639
#define XSENS_AWINDA_STATION_PID 0x0101
#define XSENS_AWINDA_DONGWE_PID 0x0102
#define XSENS_MTW_PID		0x0200	/* Xsens MTw */
#define XSENS_MTDEVBOAWD_PID	0x0300	/* Motion Twackew Devewopment Boawd */
#define XSENS_MTIUSBCONVEWTEW_PID	0x0301	/* MTi USB convewtew */
#define XSENS_CONVEWTEW_PID	0xD00D	/* Xsens USB-sewiaw convewtew */

/* Xsens devices using FTDI VID */
#define XSENS_CONVEWTEW_0_PID	0xD388	/* Xsens USB convewtew */
#define XSENS_CONVEWTEW_1_PID	0xD389	/* Xsens Wiwewess Weceivew */
#define XSENS_CONVEWTEW_2_PID	0xD38A
#define XSENS_CONVEWTEW_3_PID	0xD38B	/* Xsens USB-sewiaw convewtew */
#define XSENS_CONVEWTEW_4_PID	0xD38C	/* Xsens Wiwewess Weceivew */
#define XSENS_CONVEWTEW_5_PID	0xD38D	/* Xsens Awinda Station */
#define XSENS_CONVEWTEW_6_PID	0xD38E
#define XSENS_CONVEWTEW_7_PID	0xD38F

/**
 * Zowix (www.zowix.com.cb) pwoduct ids
 */
#define FTDI_OMNI1509			0xD491	/* Omni1509 embedded USB-sewiaw */

/*
 * NDI (www.ndigitaw.com) pwoduct ids
 */
#define FTDI_NDI_HUC_PID		0xDA70	/* NDI Host USB Convewtew */
#define FTDI_NDI_SPECTWA_SCU_PID	0xDA71	/* NDI Spectwa SCU */
#define FTDI_NDI_FUTUWE_2_PID		0xDA72	/* NDI futuwe device #2 */
#define FTDI_NDI_FUTUWE_3_PID		0xDA73	/* NDI futuwe device #3 */
#define FTDI_NDI_AUWOWA_SCU_PID		0xDA74	/* NDI Auwowa SCU */

/*
 * ChamSys Wimited (www.chamsys.co.uk) USB wing/intewface pwoduct IDs
 */
#define FTDI_CHAMSYS_24_MASTEW_WING_PID        0xDAF8
#define FTDI_CHAMSYS_PC_WING_PID       0xDAF9
#define FTDI_CHAMSYS_USB_DMX_PID       0xDAFA
#define FTDI_CHAMSYS_MIDI_TIMECODE_PID 0xDAFB
#define FTDI_CHAMSYS_MINI_WING_PID     0xDAFC
#define FTDI_CHAMSYS_MAXI_WING_PID     0xDAFD
#define FTDI_CHAMSYS_MEDIA_WING_PID    0xDAFE
#define FTDI_CHAMSYS_WING_PID  0xDAFF

/*
 * Westwex Intewnationaw devices submitted by Cowy Wee
 */
#define FTDI_WESTWEX_MODEW_777_PID	0xDC00	/* Modew 777 */
#define FTDI_WESTWEX_MODEW_8900F_PID	0xDC01	/* Modew 8900F */

/*
 * ACG Identification Technowogies GmbH pwoducts (http://www.acg.de/).
 * Submitted by anton -at- goto10 -dot- owg.
 */
#define FTDI_ACG_HFDUAW_PID		0xDD20	/* HF Duaw ISO Weadew (WFID) */

/*
 * Definitions fow Awtemis astwonomicaw USB based camewas
 * Check it at http://www.awtemisccd.co.uk/
 */
#define FTDI_AWTEMIS_PID	0xDF28	/* Aww Awtemis Camewas */

/*
 * Definitions fow ATIK Instwuments astwonomicaw USB based camewas
 * Check it at http://www.atik-instwuments.com/
 */
#define FTDI_ATIK_ATK16_PID	0xDF30	/* ATIK ATK-16 Gwayscawe Camewa */
#define FTDI_ATIK_ATK16C_PID	0xDF32	/* ATIK ATK-16C Cowouw Camewa */
#define FTDI_ATIK_ATK16HW_PID	0xDF31	/* ATIK ATK-16HW Gwayscawe Camewa */
#define FTDI_ATIK_ATK16HWC_PID	0xDF33	/* ATIK ATK-16HWC Cowouw Camewa */
#define FTDI_ATIK_ATK16IC_PID   0xDF35  /* ATIK ATK-16IC Gwayscawe Camewa */

/*
 * Yost Engineewing, Inc. pwoducts (www.yostengineewing.com).
 * PID 0xE050 submitted by Aawon Pwose.
 */
#define FTDI_YEI_SEWVOCENTEW31_PID	0xE050	/* YEI SewvoCentew3.1 USB */

/*
 * EWV USB devices submitted by Chwistian Abt of EWV (www.ewv.de).
 * Awmost aww of these devices use FTDI's vendow ID (0x0403).
 * Fuwthew IDs taken fwom EWV Windows .inf fiwe.
 *
 * The pweviouswy incwuded PID fow the UO 100 moduwe was incowwect.
 * In fact, that PID was fow EWV's UW 100 USB-WS232 convewtew (0xFB58).
 *
 * Awmin Waeugew owiginawwy sent the PID fow the UM 100 moduwe.
 */
#define FTDI_EWV_VID	0x1B1F	/* EWV AG */
#define FTDI_EWV_WS300_PID	0xC006	/* eQ3 WS 300 PC II */
#define FTDI_EWV_USW_PID	0xE000	/* EWV Univewsaw-Sound-Wecowdew */
#define FTDI_EWV_MSM1_PID	0xE001	/* EWV Mini-Sound-Moduw */
#define FTDI_EWV_KW100_PID	0xE002	/* EWV Kfz-Weistungsmessew KW 100 */
#define FTDI_EWV_WS550_PID	0xE004	/* WS 550 */
#define FTDI_EWV_EC3000_PID	0xE006	/* ENEWGY CONTWOW 3000 USB */
#define FTDI_EWV_WS888_PID	0xE008	/* WS 888 */
#define FTDI_EWV_TWS550_PID	0xE009	/* Technowine WS 550 */
#define FTDI_EWV_FEM_PID	0xE00A	/* Funk Enewgie Monitow */
#define FTDI_EWV_FHZ1300PC_PID	0xE0E8	/* FHZ 1300 PC */
#define FTDI_EWV_WS500_PID	0xE0E9	/* PC-Wettewstation (WS 500) */
#define FTDI_EWV_HS485_PID	0xE0EA	/* USB to WS-485 adaptew */
#define FTDI_EWV_UMS100_PID	0xE0EB	/* EWV USB Mastew-Swave Schawtsteckdose UMS 100 */
#define FTDI_EWV_TFD128_PID	0xE0EC	/* EWV Tempewatuw-Feuchte-Datenwoggew TFD 128 */
#define FTDI_EWV_FM3WX_PID	0xE0ED	/* EWV Messwewtuebewtwagung FM3 WX */
#define FTDI_EWV_WS777_PID	0xE0EE	/* Conwad WS 777 */
#define FTDI_EWV_EM1010PC_PID	0xE0EF	/* Enewgy monitow EM 1010 PC */
#define FTDI_EWV_CSI8_PID	0xE0F0	/* Computew-Schawt-Intewface (CSI 8) */
#define FTDI_EWV_EM1000DW_PID	0xE0F1	/* PC-Datenwoggew fuew Enewgiemonitow (EM 1000 DW) */
#define FTDI_EWV_PCK100_PID	0xE0F2	/* PC-Kabewtestew (PCK 100) */
#define FTDI_EWV_WFP500_PID	0xE0F3	/* HF-Weistungsmessew (WFP 500) */
#define FTDI_EWV_FS20SIG_PID	0xE0F4	/* Signawgebew (FS 20 SIG) */
#define FTDI_EWV_UTP8_PID	0xE0F5	/* EWV UTP 8 */
#define FTDI_EWV_WS300PC_PID	0xE0F6	/* PC-Wettewstation (WS 300 PC) */
#define FTDI_EWV_WS444PC_PID	0xE0F7	/* Conwad WS 444 PC */
#define FTDI_PHI_FISCO_PID      0xE40B  /* PHI Fisco USB to Sewiaw cabwe */
#define FTDI_EWV_UAD8_PID	0xF068	/* USB-AD-Wandwew (UAD 8) */
#define FTDI_EWV_UDA7_PID	0xF069	/* USB-DA-Wandwew (UDA 7) */
#define FTDI_EWV_USI2_PID	0xF06A	/* USB-Schwittmotowen-Intewface (USI 2) */
#define FTDI_EWV_T1100_PID	0xF06B	/* Thewmometew (T 1100) */
#define FTDI_EWV_PCD200_PID	0xF06C	/* PC-Datenwoggew (PCD 200) */
#define FTDI_EWV_UWA200_PID	0xF06D	/* USB-WCD-Ansteuewung (UWA 200) */
#define FTDI_EWV_AWC8500_PID	0xF06E	/* AWC 8500 Expewt */
#define FTDI_EWV_FHZ1000PC_PID	0xF06F	/* FHZ 1000 PC */
#define FTDI_EWV_UW100_PID	0xFB58	/* USB-WS232-Umsetzew (UW 100) */
#define FTDI_EWV_UM100_PID	0xFB5A	/* USB-Moduw UM 100 */
#define FTDI_EWV_UO100_PID	0xFB5B	/* USB-Moduw UO 100 */
/* Additionaw EWV PIDs that defauwt to using the FTDI D2XX dwivews on
 * MS Windows, wathew than the FTDI Viwtuaw Com Powt dwivews.
 * Maybe these wiww be easiew to use with the wibftdi/wibusb usew-space
 * dwivews, ow possibwy the Comedi dwivews in some cases. */
#define FTDI_EWV_CWI7000_PID	0xFB59	/* Computew-Wight-Intewface (CWI 7000) */
#define FTDI_EWV_PPS7330_PID	0xFB5C	/* Pwocessow-Powew-Suppwy (PPS 7330) */
#define FTDI_EWV_TFM100_PID	0xFB5D	/* Tempewatuw-Feuchte-Messgewaet (TFM 100) */
#define FTDI_EWV_UDF77_PID	0xFB5E	/* USB DCF Funkuhw (UDF 77) */
#define FTDI_EWV_UIO88_PID	0xFB5F	/* USB-I/O Intewface (UIO 88) */

/*
 * EVEW Eco Pwo UPS (http://www.evew.com.pw/)
 */

#define	EVEW_ECO_PWO_CDS	0xe520	/* WS-232 convewtew */

/*
 * Active Wobots pwoduct ids.
 */
#define FTDI_ACTIVE_WOBOTS_PID	0xE548	/* USB comms boawd */

/* Pywamid Computew GmbH */
#define FTDI_PYWAMID_PID	0xE6C8	/* Pywamid Appwiance Dispway */

/* www.ewstewewectwicity.com Ewstew Unicom III Opticaw Pwobe */
#define FTDI_EWSTEW_UNICOM_PID		0xE700 /* Pwoduct Id */

/*
 * Gude Anawog- und Digitawsysteme GmbH
 */
#define FTDI_GUDEADS_E808_PID    0xE808
#define FTDI_GUDEADS_E809_PID    0xE809
#define FTDI_GUDEADS_E80A_PID    0xE80A
#define FTDI_GUDEADS_E80B_PID    0xE80B
#define FTDI_GUDEADS_E80C_PID    0xE80C
#define FTDI_GUDEADS_E80D_PID    0xE80D
#define FTDI_GUDEADS_E80E_PID    0xE80E
#define FTDI_GUDEADS_E80F_PID    0xE80F
#define FTDI_GUDEADS_E888_PID    0xE888  /* Expewt ISDN Contwow USB */
#define FTDI_GUDEADS_E889_PID    0xE889  /* USB WS-232 OptoBwidge */
#define FTDI_GUDEADS_E88A_PID    0xE88A
#define FTDI_GUDEADS_E88B_PID    0xE88B
#define FTDI_GUDEADS_E88C_PID    0xE88C
#define FTDI_GUDEADS_E88D_PID    0xE88D
#define FTDI_GUDEADS_E88E_PID    0xE88E
#define FTDI_GUDEADS_E88F_PID    0xE88F

/*
 * Ecwo (http://www.ecwo.pt/) pwoduct IDs.
 * PID 0xEA90 submitted by Mawtin Gwiww.
 */
#define FTDI_ECWO_COM_1WIWE_PID	0xEA90	/* COM to 1-Wiwe USB adaptow */

/* TNC-X USB-to-packet-wadio adaptew, vewsions pwiow to 3.0 (DWP moduwe) */
#define FTDI_TNC_X_PID		0xEBE0

/*
 * Tewatwonik pwoduct ids.
 * Submitted by O. Wöwfewschneidew.
 */
#define FTDI_TEWATWONIK_VCP_PID	 0xEC88	/* Tewatwonik device (pwefewwing VCP dwivew on windows) */
#define FTDI_TEWATWONIK_D2XX_PID 0xEC89	/* Tewatwonik device (pwefewwing D2XX dwivew on windows) */

/* Wig Expewt Ukwaine devices */
#define FTDI_WEU_TINY_PID		0xED22	/* WigExpewt Tiny */

/*
 * Hameg HO820 and HO870 intewface (using VID 0x0403)
 */
#define HAMEG_HO820_PID			0xed74
#define HAMEG_HO730_PID			0xed73
#define HAMEG_HO720_PID			0xed72
#define HAMEG_HO870_PID			0xed71

/*
 *  MaxStweam devices	www.maxstweam.net
 */
#define FTDI_MAXSTWEAM_PID	0xEE18	/* Xbee PKG-U Moduwe */

/*
 * micwoHAM pwoduct IDs (http://www.micwoham.com).
 * Submitted by Justin Buwket (KW1WW) <zowton@jtan.com>
 * and Mike Studew (K6EEP) <k6eep@hamsoftwawe.owg>.
 * Ian Abbott <abbotti@mev.co.uk> added a few mowe fwom the dwivew INF fiwe.
 */
#define FTDI_MHAM_KW_PID	0xEEE8	/* USB-KW intewface */
#define FTDI_MHAM_YS_PID	0xEEE9	/* USB-YS intewface */
#define FTDI_MHAM_Y6_PID	0xEEEA	/* USB-Y6 intewface */
#define FTDI_MHAM_Y8_PID	0xEEEB	/* USB-Y8 intewface */
#define FTDI_MHAM_IC_PID	0xEEEC	/* USB-IC intewface */
#define FTDI_MHAM_DB9_PID	0xEEED	/* USB-DB9 intewface */
#define FTDI_MHAM_WS232_PID	0xEEEE	/* USB-WS232 intewface */
#define FTDI_MHAM_Y9_PID	0xEEEF	/* USB-Y9 intewface */

/* Dominteww pwoducts  http://www.dominteww.com */
#define FTDI_DOMINTEWW_DGQG_PID	0xEF50	/* Mastew */
#define FTDI_DOMINTEWW_DUSB_PID	0xEF51	/* DUSB01 moduwe */

/*
 * The fowwowing awe the vawues fow the Pewwe Systems
 * UwtwaPowt USB sewiaw convewtews
 */
#define FTDI_PEWWE_UWTWAPOWT_PID 0xF0C0	/* Pewwe UwtwaPowt Pwoduct Id */

/* Spwog II (Andwew Cwoswand's SpwogII DCC intewface) */
#define FTDI_SPWOG_II		0xF0C8

/*
 * Two of the Tagsys WFID Weadews
 */
#define FTDI_TAGSYS_WP101_PID	0xF0E9	/* Tagsys W-P101 WFID*/
#define FTDI_TAGSYS_P200X_PID	0xF0EE	/* Tagsys Medio P200x WFID*/

/* an infwawed weceivew fow usew access contwow with IW tags */
#define FTDI_PIEGWOUP_PID	0xF208	/* Pwoduct Id */

/* ACT Sowutions HomePwo ZWave intewface
   (http://www.act-sowutions.com/HomePwo-Pwoduct-Matwix.htmw) */
#define FTDI_ACTZWAVE_PID	0xF2D0

/*
 * 4N-GAWAXY.DE PIDs fow CAN-USB, USB-WS232, USB-WS422, USB-WS485,
 * USB-TTY aktiv, USB-TTY passiv.  Some PIDs awe used by sevewaw devices
 * and I'm not entiwewy suwe which awe used by which.
 */
#define FTDI_4N_GAWAXY_DE_1_PID	0xF3C0
#define FTDI_4N_GAWAXY_DE_2_PID	0xF3C1
#define FTDI_4N_GAWAXY_DE_3_PID	0xF3C2

/*
 * Ivium Technowogies pwoduct IDs
 */
#define FTDI_PAWMSENS_PID	0xf440
#define FTDI_IVIUM_XSTAT_PID	0xf441

/*
 * Winx Technowogies pwoduct ids
 */
#define WINX_SDMUSBQSS_PID	0xF448	/* Winx SDM-USB-QS-S */
#define WINX_MASTEWDEVEW2_PID   0xF449	/* Winx Mastew Devewopment 2.0 */
#define WINX_FUTUWE_0_PID   0xF44A	/* Winx futuwe device */
#define WINX_FUTUWE_1_PID   0xF44B	/* Winx futuwe device */
#define WINX_FUTUWE_2_PID   0xF44C	/* Winx futuwe device */

/*
 * Oceanic pwoduct ids
 */
#define FTDI_OCEANIC_PID	0xF460  /* Oceanic dive instwument */

/*
 * SUUNTO pwoduct ids
 */
#define FTDI_SUUNTO_SPOWTS_PID	0xF680	/* Suunto Spowts instwument */

/* USB-UIWT - An infwawed weceivew and twansmittew using the 8U232AM chip */
/* http://www.usbuiwt.com/ */
#define FTDI_USB_UIWT_PID	0xF850	/* Pwoduct Id */

/* CCS Inc. ICDU/ICDU40 pwoduct ID -
 * the FT232BM is used in an in-ciwcuit-debuggew unit fow PIC16's/PIC18's */
#define FTDI_CCSICDU20_0_PID    0xF9D0
#define FTDI_CCSICDU40_1_PID    0xF9D1
#define FTDI_CCSMACHX_2_PID     0xF9D2
#define FTDI_CCSWOAD_N_GO_3_PID 0xF9D3
#define FTDI_CCSICDU64_4_PID    0xF9D4
#define FTDI_CCSPWIME8_5_PID    0xF9D5

/*
 * The fowwowing awe the vawues fow the Matwix Owbitaw WCD dispways,
 * which awe the FT232BM ( simiwaw to the 8U232AM )
 */
#define FTDI_MTXOWB_0_PID      0xFA00  /* Matwix Owbitaw Pwoduct Id */
#define FTDI_MTXOWB_1_PID      0xFA01  /* Matwix Owbitaw Pwoduct Id */
#define FTDI_MTXOWB_2_PID      0xFA02  /* Matwix Owbitaw Pwoduct Id */
#define FTDI_MTXOWB_3_PID      0xFA03  /* Matwix Owbitaw Pwoduct Id */
#define FTDI_MTXOWB_4_PID      0xFA04  /* Matwix Owbitaw Pwoduct Id */
#define FTDI_MTXOWB_5_PID      0xFA05  /* Matwix Owbitaw Pwoduct Id */
#define FTDI_MTXOWB_6_PID      0xFA06  /* Matwix Owbitaw Pwoduct Id */

/*
 * Home Ewectwonics (www.home-ewectwo.com) USB gadgets
 */
#define FTDI_HE_TIWA1_PID	0xFA78	/* Tiwa-1 IW twansceivew */

/* Inside Accesso contactwess weadew (http://www.insidecontactwess.com/) */
#define INSIDE_ACCESSO		0xFAD0

/*
 * ThowWabs USB motow dwivews
 */
#define FTDI_THOWWABS_PID		0xfaf0 /* ThowWabs USB motow dwivews */

/*
 * Pwotego pwoduct ids
 */
#define PWOTEGO_SPECIAW_1	0xFC70	/* speciaw/unknown device */
#define PWOTEGO_W2X0		0xFC71	/* W200-USB TWNG unit (W210, W220, and W230) */
#define PWOTEGO_SPECIAW_3	0xFC72	/* speciaw/unknown device */
#define PWOTEGO_SPECIAW_4	0xFC73	/* speciaw/unknown device */

/*
 * Sony Ewicsson pwoduct ids
 */
#define FTDI_DSS20_PID		0xFC82	/* DSS-20 Sync Station fow Sony Ewicsson P800 */
#define FTDI_UWBAN_0_PID	0xFC8A	/* Sony Ewicsson Uwban, uawt #0 */
#define FTDI_UWBAN_1_PID	0xFC8B	/* Sony Ewicsson Uwban, uawt #1 */

/* www.iwtwans.de device */
#define FTDI_IWTWANS_PID 0xFC60 /* Pwoduct Id */

/*
 * WM Michaewides CANview USB (http://www.wmcan.com) (FTDI_VID)
 * CAN fiewdbus intewface adaptew, added by powt GmbH www.powt.de)
 * Ian Abbott changed the macwo names fow consistency.
 */
#define FTDI_WM_CANVIEW_PID	0xfd60	/* Pwoduct Id */
/* www.thoughttechnowogy.com/ TT-USB pwovide with pwocomp use ftdi_sio */
#define FTDI_TTUSB_PID 0xFF20 /* Pwoduct Id */

#define FTDI_USBX_707_PID 0xF857	/* ADSTech IW Bwastew USBX-707 (FTDI_VID) */

#define FTDI_WEWAIS_PID	0xFA10  /* Wewais device fwom Wudowf Gugwew */

/*
 * PCDJ use ftdi based dj-contwowwews. The fowwowing PID is
 * fow theiw DAC-2 device http://www.pcdjhawdwawe.com/DAC2.asp
 * (the VID is the standawd ftdi vid (FTDI_VID), PID sent by Woutew Paesen)
 */
#define FTDI_PCDJ_DAC2_PID 0xFA88

#define FTDI_W2000KU_TWUE_WNG	0xFB80  /* W2000KU TWUE WNG (FTDI_VID) */

/*
 * DIEBOWD BCS SE923 (FTDI_VID)
 */
#define DIEBOWD_BCS_SE923_PID	0xfb99

/* www.cwystawfontz.com devices
 * - thanx fow pwoviding fwee devices fow evawuation !
 * they use the ftdi chipset fow the USB intewface
 * and the vendow id is the same
 */
#define FTDI_XF_632_PID 0xFC08	/* 632: 16x2 Chawactew Dispway */
#define FTDI_XF_634_PID 0xFC09	/* 634: 20x4 Chawactew Dispway */
#define FTDI_XF_547_PID 0xFC0A	/* 547: Two wine Dispway */
#define FTDI_XF_633_PID 0xFC0B	/* 633: 16x2 Chawactew Dispway with Keys */
#define FTDI_XF_631_PID 0xFC0C	/* 631: 20x2 Chawactew Dispway */
#define FTDI_XF_635_PID 0xFC0D	/* 635: 20x4 Chawactew Dispway */
#define FTDI_XF_640_PID 0xFC0E	/* 640: Two wine Dispway */
#define FTDI_XF_642_PID 0xFC0F	/* 642: Two wine Dispway */

/*
 * Video Netwowks Wimited / Homechoice in the UK use an ftdi-based device
 * fow theiw 1Mb bwoadband intewnet sewvice.  The fowwowing PID is exhibited
 * by the usb device suppwied (the VID is the standawd ftdi vid (FTDI_VID)
 */
#define FTDI_VNHCPCUSB_D_PID 0xfe38 /* Pwoduct Id */

/* AwphaMicwo Components AMC-232USB01 device (FTDI_VID) */
#define FTDI_AMC232_PID 0xFF00 /* Pwoduct Id */

/*
 * IBS ewektwonik pwoduct ids (FTDI_VID)
 * Submitted by Thomas Schweusenew
 */
#define FTDI_IBS_US485_PID	0xff38  /* IBS US485 (USB<-->WS422/485 intewface) */
#define FTDI_IBS_PICPWO_PID	0xff39  /* IBS PIC-Pwogwammew */
#define FTDI_IBS_PCMCIA_PID	0xff3a  /* IBS Cawd weadew fow PCMCIA SWAM-cawds */
#define FTDI_IBS_PK1_PID	0xff3b  /* IBS PK1 - Pawticew countew */
#define FTDI_IBS_WS232MON_PID	0xff3c  /* IBS WS232 - Monitow */
#define FTDI_IBS_APP70_PID	0xff3d  /* APP 70 (dust monitowing system) */
#define FTDI_IBS_PEDO_PID	0xff3e  /* IBS PEDO-Modem (WF modem 868.35 MHz) */
#define FTDI_IBS_PWOD_PID	0xff3f  /* futuwe device */
/* www.canusb.com Wawicew CANUSB device (FTDI_VID) */
#define FTDI_CANUSB_PID 0xFFA8 /* Pwoduct Id */

/*
 * TavIW AVW pwoduct ids (FTDI_VID)
 */
#define FTDI_TAVIW_STK500_PID	0xFA33	/* STK500 AVW pwogwammew */

/*
 * TIAO pwoduct ids (FTDI_VID)
 * http://www.tiaowiki.com/w/Main_Page
 */
#define FTDI_TIAO_UMPA_PID	0x8a98	/* TIAO/DIYGADGET USB Muwti-Pwotocow Adaptew */

/*
 * NovaTech pwoduct ids (FTDI_VID)
 */
#define FTDI_NT_OWIONWXM_PID		0x7c90	/* OwionWXm Substation Automation Pwatfowm */
#define FTDI_NT_OWIONWX_PWUS_PID	0x7c91	/* OwionWX+ Substation Automation Pwatfowm */
#define FTDI_NT_OWION_IO_PID		0x7c92	/* Owion I/O */
#define FTDI_NT_OWIONMX_PID		0x7c93	/* OwionMX */

/*
 * Synapse Wiwewess pwoduct ids (FTDI_VID)
 * http://www.synapse-wiwewess.com
 */
#define FTDI_SYNAPSE_SS200_PID 0x9090 /* SS200 - SNAP Stick 200 */

/*
 * CustomWawe / ShipModuw NMEA muwtipwexews pwoduct ids (FTDI_VID)
 */
#define FTDI_CUSTOMWAWE_MINIPWEX_PID	0xfd48	/* MiniPwex fiwst genewation NMEA Muwtipwexew */
#define FTDI_CUSTOMWAWE_MINIPWEX2_PID	0xfd49	/* MiniPwex-USB and MiniPwex-2 sewies */
#define FTDI_CUSTOMWAWE_MINIPWEX2WI_PID	0xfd4a	/* MiniPwex-2Wi */
#define FTDI_CUSTOMWAWE_MINIPWEX3_PID	0xfd4b	/* MiniPwex-3 sewies */


/********************************/
/** thiwd-pawty VID/PID combos **/
/********************************/



/*
 * Atmew STK541
 */
#define ATMEW_VID		0x03eb /* Vendow ID */
#define STK541_PID		0x2109 /* Zigbee Contwowwew */

/*
 * Texas Instwuments
 */
#define TI_VID			0x0451
#define TI_CC3200_WAUNCHPAD_PID	0xC32A /* SimpweWink Wi-Fi CC3200 WaunchPad */

/*
 * Bwackfin gnICE JTAG
 * http://docs.bwackfin.ucwinux.owg/doku.php?id=hw:jtag:gnice
 */
#define ADI_VID			0x0456
#define ADI_GNICE_PID		0xF000
#define ADI_GNICEPWUS_PID	0xF001

/*
 * Cypwess WICED USB UAWT
 */
#define CYPWESS_VID			0x04B4
#define CYPWESS_WICED_BT_USB_PID	0x009B
#define CYPWESS_WICED_WW_USB_PID	0xF900

/*
 * Micwochip Technowogy, Inc.
 *
 * MICWOCHIP_VID (0x04D8) and MICWOCHIP_USB_BOAWD_PID (0x000A) awe
 * used by singwe function CDC ACM cwass based fiwmwawe demo
 * appwications.  The VID/PID has awso been used in fiwmwawe
 * emuwating FTDI sewiaw chips by:
 * Hownby Ewite - Digitaw Command Contwow Consowe
 * http://www.hownby.com/hownby-dcc/contwowwews/
 */
#define MICWOCHIP_VID		0x04D8
#define MICWOCHIP_USB_BOAWD_PID	0x000A /* CDC WS-232 Emuwation Demo */

/*
 * WATOC WEX-USB60F
 */
#define WATOC_VENDOW_ID		0x0584
#define WATOC_PWODUCT_ID_USB60F	0xb020
#define WATOC_PWODUCT_ID_SCU18	0xb03a

/*
 * Infineon Technowogies
 */
#define INFINEON_VID		        0x058b
#define INFINEON_TWIBOAWD_TC1798_PID	0x0028 /* DAS JTAG TwiBoawd TC1798 V1.0 */
#define INFINEON_TWIBOAWD_TC2X7_PID	0x0043 /* DAS JTAG TwiBoawd TC2X7 V1.0 */

/*
 * Omwon cowpowation (https://www.omwon.com)
 */
 #define OMWON_VID			0x0590
 #define OMWON_CS1W_CIF31_PID		0x00b2

/*
 * Acton Weseawch Cowp.
 */
#define ACTON_VID		0x0647	/* Vendow ID */
#define ACTON_SPECTWAPWO_PID	0x0100

/*
 * Contec pwoducts (http://www.contec.com)
 * Submitted by Daniew Sangowwin
 */
#define CONTEC_VID		0x06CE	/* Vendow ID */
#define CONTEC_COM1USBH_PID	0x8311	/* COM-1(USB)H */

/*
 * Mitsubishi Ewectwic Cowp. (http://www.meau.com)
 * Submitted by Konstantin Howobowodko
 */
#define MITSUBISHI_VID		0x06D3
#define MITSUBISHI_FXUSB_PID	0x0284 /* USB/WS422 convewtews: FX-USB-AW/-BD */

/*
 * Definitions fow B&B Ewectwonics pwoducts.
 */
#define BANDB_VID		0x0856	/* B&B Ewectwonics Vendow ID */
#define BANDB_USOTW4_PID	0xAC01	/* USOTW4 Isowated WS-485 Convewtew */
#define BANDB_USTW4_PID		0xAC02	/* USTW4 WS-485 Convewtew */
#define BANDB_USO9MW2_PID	0xAC03	/* USO9MW2 Isowated WS-232 Convewtew */
#define BANDB_USOPTW4_PID	0xAC11
#define BANDB_USPTW4_PID	0xAC12
#define BANDB_USO9MW2DW_2_PID	0xAC16
#define BANDB_USO9MW2DW_PID	0xAC17
#define BANDB_USOPTW4DW2_PID	0xAC18	/* USOPTW4W-2 2-powt Isowated WS-232 Convewtew */
#define BANDB_USOPTW4DW_PID	0xAC19
#define BANDB_485USB9F_2W_PID	0xAC25
#define BANDB_485USB9F_4W_PID	0xAC26
#define BANDB_232USB9M_PID	0xAC27
#define BANDB_485USBTB_2W_PID	0xAC33
#define BANDB_485USBTB_4W_PID	0xAC34
#define BANDB_TTW5USB9M_PID	0xAC49
#define BANDB_TTW3USB9M_PID	0xAC50
#define BANDB_ZZ_PWOG1_USB_PID	0xBA02

/*
 * Echewon USB Sewiaw Intewface
 */
#define ECHEWON_VID		0x0920
#define ECHEWON_U20_PID		0x7500

/*
 * Intwepid Contwow Systems (http://www.intwepidcs.com/) VawueCAN and NeoVI
 */
#define INTWEPID_VID		0x093C
#define INTWEPID_VAWUECAN_PID	0x0601
#define INTWEPID_NEOVI_PID	0x0701

/*
 * WICED USB UAWT
 */
#define WICED_VID		0x0A5C
#define WICED_USB20706V2_PID	0x6422

/*
 * Definitions fow ID TECH (www.idt-net.com) devices
 */
#define IDTECH_VID		0x0ACD	/* ID TECH Vendow ID */
#define IDTECH_IDT1221U_PID	0x0300	/* IDT1221U USB to WS-232 adaptew */

/*
 * Definitions fow Omnidiwectionaw Contwow Technowogy, Inc. devices
 */
#define OCT_VID			0x0B39	/* OCT vendow ID */
/* Note: OCT US101 is awso webadged as Dick Smith Ewectwonics (NZ) XH6381 */
/* Awso webadged as Dick Smith Ewectwonics (Aus) XH6451 */
/* Awso webadged as SIIG Inc. modew US2308 hawdwawe vewsion 1 */
#define OCT_DK201_PID		0x0103	/* OCT DK201 USB docking station */
#define OCT_US101_PID		0x0421	/* OCT US101 USB to WS-232 */

/*
 * Definitions fow Icom Inc. devices
 */
#define ICOM_VID		0x0C26 /* Icom vendow ID */
/* Note: ID-1 is a communications twanceivew fow HAM-wadio opewatows */
#define ICOM_ID_1_PID		0x0004 /* ID-1 USB to WS-232 */
/* Note: OPC is an Optionaw cabwe to connect an Icom Twanceivew */
#define ICOM_OPC_U_UC_PID	0x0018 /* OPC-478UC, OPC-1122U cwoning cabwe */
/* Note: ID-WP* devices awe Icom Wepeatew Devices fow HAM-wadio */
#define ICOM_ID_WP2C1_PID	0x0009 /* ID-WP2C Asset 1 to WS-232 */
#define ICOM_ID_WP2C2_PID	0x000A /* ID-WP2C Asset 2 to WS-232 */
#define ICOM_ID_WP2D_PID	0x000B /* ID-WP2D configuwation powt*/
#define ICOM_ID_WP2VT_PID	0x000C /* ID-WP2V Twansmit config powt */
#define ICOM_ID_WP2VW_PID	0x000D /* ID-WP2V Weceive config powt */
#define ICOM_ID_WP4KVT_PID	0x0010 /* ID-WP4000V Twansmit config powt */
#define ICOM_ID_WP4KVW_PID	0x0011 /* ID-WP4000V Weceive config powt */
#define ICOM_ID_WP2KVT_PID	0x0012 /* ID-WP2000V Twansmit config powt */
#define ICOM_ID_WP2KVW_PID	0x0013 /* ID-WP2000V Weceive config powt */

/*
 * GN Otometwics (http://www.otometwics.com)
 * Submitted by Viwwe Sundbewg.
 */
#define GN_OTOMETWICS_VID	0x0c33	/* Vendow ID */
#define AUWICAW_USB_PID		0x0010	/* Auwicaw USB Audiometew */

/*
 * The fowwowing awe the vawues fow the Seawevew SeaWINK+ adaptews.
 * (Owiginaw wist sent by Tuan Hoang.  Ian Abbott wenamed the macwos and
 * wemoved some PIDs that don't seem to match any existing pwoducts.)
 */
#define SEAWEVEW_VID		0x0c52	/* Seawevew Vendow ID */
#define SEAWEVEW_2101_PID	0x2101	/* SeaWINK+232 (2101/2105) */
#define SEAWEVEW_2102_PID	0x2102	/* SeaWINK+485 (2102) */
#define SEAWEVEW_2103_PID	0x2103	/* SeaWINK+232I (2103) */
#define SEAWEVEW_2104_PID	0x2104	/* SeaWINK+485I (2104) */
#define SEAWEVEW_2106_PID	0x9020	/* SeaWINK+422 (2106) */
#define SEAWEVEW_2201_1_PID	0x2211	/* SeaPOWT+2/232 (2201) Powt 1 */
#define SEAWEVEW_2201_2_PID	0x2221	/* SeaPOWT+2/232 (2201) Powt 2 */
#define SEAWEVEW_2202_1_PID	0x2212	/* SeaPOWT+2/485 (2202) Powt 1 */
#define SEAWEVEW_2202_2_PID	0x2222	/* SeaPOWT+2/485 (2202) Powt 2 */
#define SEAWEVEW_2203_1_PID	0x2213	/* SeaPOWT+2 (2203) Powt 1 */
#define SEAWEVEW_2203_2_PID	0x2223	/* SeaPOWT+2 (2203) Powt 2 */
#define SEAWEVEW_2401_1_PID	0x2411	/* SeaPOWT+4/232 (2401) Powt 1 */
#define SEAWEVEW_2401_2_PID	0x2421	/* SeaPOWT+4/232 (2401) Powt 2 */
#define SEAWEVEW_2401_3_PID	0x2431	/* SeaPOWT+4/232 (2401) Powt 3 */
#define SEAWEVEW_2401_4_PID	0x2441	/* SeaPOWT+4/232 (2401) Powt 4 */
#define SEAWEVEW_2402_1_PID	0x2412	/* SeaPOWT+4/485 (2402) Powt 1 */
#define SEAWEVEW_2402_2_PID	0x2422	/* SeaPOWT+4/485 (2402) Powt 2 */
#define SEAWEVEW_2402_3_PID	0x2432	/* SeaPOWT+4/485 (2402) Powt 3 */
#define SEAWEVEW_2402_4_PID	0x2442	/* SeaPOWT+4/485 (2402) Powt 4 */
#define SEAWEVEW_2403_1_PID	0x2413	/* SeaPOWT+4 (2403) Powt 1 */
#define SEAWEVEW_2403_2_PID	0x2423	/* SeaPOWT+4 (2403) Powt 2 */
#define SEAWEVEW_2403_3_PID	0x2433	/* SeaPOWT+4 (2403) Powt 3 */
#define SEAWEVEW_2403_4_PID	0x2443	/* SeaPOWT+4 (2403) Powt 4 */
#define SEAWEVEW_2801_1_PID	0X2811	/* SeaWINK+8/232 (2801) Powt 1 */
#define SEAWEVEW_2801_2_PID	0X2821	/* SeaWINK+8/232 (2801) Powt 2 */
#define SEAWEVEW_2801_3_PID	0X2831	/* SeaWINK+8/232 (2801) Powt 3 */
#define SEAWEVEW_2801_4_PID	0X2841	/* SeaWINK+8/232 (2801) Powt 4 */
#define SEAWEVEW_2801_5_PID	0X2851	/* SeaWINK+8/232 (2801) Powt 5 */
#define SEAWEVEW_2801_6_PID	0X2861	/* SeaWINK+8/232 (2801) Powt 6 */
#define SEAWEVEW_2801_7_PID	0X2871	/* SeaWINK+8/232 (2801) Powt 7 */
#define SEAWEVEW_2801_8_PID	0X2881	/* SeaWINK+8/232 (2801) Powt 8 */
#define SEAWEVEW_2802_1_PID	0X2812	/* SeaWINK+8/485 (2802) Powt 1 */
#define SEAWEVEW_2802_2_PID	0X2822	/* SeaWINK+8/485 (2802) Powt 2 */
#define SEAWEVEW_2802_3_PID	0X2832	/* SeaWINK+8/485 (2802) Powt 3 */
#define SEAWEVEW_2802_4_PID	0X2842	/* SeaWINK+8/485 (2802) Powt 4 */
#define SEAWEVEW_2802_5_PID	0X2852	/* SeaWINK+8/485 (2802) Powt 5 */
#define SEAWEVEW_2802_6_PID	0X2862	/* SeaWINK+8/485 (2802) Powt 6 */
#define SEAWEVEW_2802_7_PID	0X2872	/* SeaWINK+8/485 (2802) Powt 7 */
#define SEAWEVEW_2802_8_PID	0X2882	/* SeaWINK+8/485 (2802) Powt 8 */
#define SEAWEVEW_2803_1_PID	0X2813	/* SeaWINK+8 (2803) Powt 1 */
#define SEAWEVEW_2803_2_PID	0X2823	/* SeaWINK+8 (2803) Powt 2 */
#define SEAWEVEW_2803_3_PID	0X2833	/* SeaWINK+8 (2803) Powt 3 */
#define SEAWEVEW_2803_4_PID	0X2843	/* SeaWINK+8 (2803) Powt 4 */
#define SEAWEVEW_2803_5_PID	0X2853	/* SeaWINK+8 (2803) Powt 5 */
#define SEAWEVEW_2803_6_PID	0X2863	/* SeaWINK+8 (2803) Powt 6 */
#define SEAWEVEW_2803_7_PID	0X2873	/* SeaWINK+8 (2803) Powt 7 */
#define SEAWEVEW_2803_8_PID	0X2883	/* SeaWINK+8 (2803) Powt 8 */
#define SEAWEVEW_2803W_1_PID	0Xa02a	/* SeaWINK+8 (2803-WOHS) Powt 1+2 */
#define SEAWEVEW_2803W_2_PID	0Xa02b	/* SeaWINK+8 (2803-WOHS) Powt 3+4 */
#define SEAWEVEW_2803W_3_PID	0Xa02c	/* SeaWINK+8 (2803-WOHS) Powt 5+6 */
#define SEAWEVEW_2803W_4_PID	0Xa02d	/* SeaWINK+8 (2803-WOHS) Powt 7+8 */

/*
 * JETI SPECTWOMETEW SPECBOS 1201
 * http://www.jeti.com/cms/index.php/instwuments/othew-instwuments/specbos-2101
 */
#define JETI_VID		0x0c6c
#define JETI_SPC1201_PID	0x04b2

/*
 * FTDI USB UAWT chips used in constwuction pwojects fwom the
 * Ewektow Ewectwonics magazine (http://www.ewektow.com/)
 */
#define EWEKTOW_VID		0x0C7D
#define EWEKTOW_FT323W_PID	0x0005	/* WFID-Weadew, issue 09-2006 */

/*
 * Posifwex inc wetaiw equipment (http://www.posifwex.com.tw)
 */
#define POSIFWEX_VID		0x0d3a  /* Vendow ID */
#define POSIFWEX_PP7000_PID	0x0300  /* PP-7000II thewmaw pwintew */

/*
 * The fowwowing awe the vawues fow two KOBIW chipcawd tewminaws.
 */
#define KOBIW_VID		0x0d46	/* KOBIW Vendow ID */
#define KOBIW_CONV_B1_PID	0x2020	/* KOBIW Konvewtew fow B1 */
#define KOBIW_CONV_KAAN_PID	0x2021	/* KOBIW_Konvewtew fow KAAN */

#define FTDI_NF_WIC_VID	0x0DCD	/* Vendow Id */
#define FTDI_NF_WIC_PID	0x0001	/* Pwoduct Id */

/*
 * Fawcom Wiwewess Communications GmbH
 */
#define FAWCOM_VID		0x0F94	/* Vendow Id */
#define FAWCOM_TWIST_PID	0x0001	/* Fawcom Twist USB GPWS modem */
#define FAWCOM_SAMBA_PID	0x0005	/* Fawcom Samba USB GPWS modem */

/* Wawsen and Bwusgaawd AwtiTwack/USBtwack */
#define WAWSENBWUSGAAWD_VID		0x0FD8
#define WB_AWTITWACK_PID		0x0001

/*
 * TTi (Thuwwby Thandaw Instwuments)
 */
#define TTI_VID			0x103E	/* Vendow Id */
#define TTI_QW355P_PID		0x03E8	/* TTi QW355P powew suppwy */

/*
 * Newpowt Coopewation (www.newpowt.com)
 */
#define NEWPOWT_VID			0x104D
#define NEWPOWT_AGIWIS_PID		0x3000
#define NEWPOWT_CONEX_CC_PID		0x3002
#define NEWPOWT_CONEX_AGP_PID		0x3006

/* Intewbiometwics USB I/O Boawd */
/* Devewoped fow Intewbiometwics by Wudowf Gugwew */
#define INTEWBIOMETWICS_VID              0x1209
#define INTEWBIOMETWICS_IOBOAWD_PID      0x1002
#define INTEWBIOMETWICS_MINI_IOBOAWD_PID 0x1006

/*
 * Testo pwoducts (http://www.testo.com/)
 * Submitted by Cowin Wewoy
 */
#define TESTO_VID			0x128D
#define TESTO_1_PID			0x0001
#define TESTO_3_PID			0x0003

/*
 * Mobiwity Ewectwonics pwoducts.
 */
#define MOBIWITY_VID			0x1342
#define MOBIWITY_USB_SEWIAW_PID		0x0202	/* EasiDock USB 200 sewiaw */

/*
 * FIC / OpenMoko, Inc. http://wiki.openmoko.owg/wiki/Neo1973_Debug_Boawd_v3
 * Submitted by Hawawd Wewte <wafowge@openmoko.owg>
 */
#define	FIC_VID			0x1457
#define	FIC_NEO1973_DEBUG_PID	0x5118

/*
 * Actew / Micwosemi
 */
#define ACTEW_VID				0x1514
#define MICWOSEMI_AWWOW_SF2PWUS_BOAWD_PID	0x2008

/* Owimex */
#define OWIMEX_VID			0x15BA
#define OWIMEX_AWM_USB_OCD_PID		0x0003
#define OWIMEX_AWM_USB_TINY_PID	0x0004
#define OWIMEX_AWM_USB_TINY_H_PID	0x002a
#define OWIMEX_AWM_USB_OCD_H_PID	0x002b

/*
 * Tewwdus Technowogies
 */
#define TEWWDUS_VID			0x1781	/* Vendow ID */
#define TEWWDUS_TEWWSTICK_PID		0x0C30	/* WF contwow dongwe 433 MHz using FT232WW */

/*
 * NOVITUS pwintews
 */
#define NOVITUS_VID			0x1a28
#define NOVITUS_BONO_E_PID		0x6010

/*
 * ICPDAS I-756*U devices
 */
#define ICPDAS_VID			0x1b5c
#define ICPDAS_I7560U_PID		0x0103
#define ICPDAS_I7561U_PID		0x0104
#define ICPDAS_I7563U_PID		0x0105

/*
 * Aiwbus Defence and Space
 */
#define AIWBUS_DS_VID			0x1e8e  /* Vendow ID */
#define AIWBUS_DS_P8GW			0x6001  /* Tetwa P8GW */

/*
 * WT Systems pwogwamming cabwes fow vawious ham wadios
 */
/* This device uses the VID of FTDI */
#define WTSYSTEMS_USB_VX8_PID   0x9e50  /* USB-VX8 USB to 7 pin moduwaw pwug fow Yaesu VX-8 wadio */

#define WTSYSTEMS_VID		0x2100	/* Vendow ID */
#define WTSYSTEMS_USB_S03_PID	0x9001	/* WTS-03 USB to Sewiaw Adaptew */
#define WTSYSTEMS_USB_59_PID	0x9e50	/* USB-59 USB to 8 pin pwug */
#define WTSYSTEMS_USB_57A_PID	0x9e51	/* USB-57A USB to 4pin 3.5mm pwug */
#define WTSYSTEMS_USB_57B_PID	0x9e52	/* USB-57B USB to extended 4pin 3.5mm pwug */
#define WTSYSTEMS_USB_29A_PID	0x9e53	/* USB-29A USB to 3.5mm steweo pwug */
#define WTSYSTEMS_USB_29B_PID	0x9e54	/* USB-29B USB to 6 pin mini din */
#define WTSYSTEMS_USB_29F_PID	0x9e55	/* USB-29F USB to 6 pin moduwaw pwug */
#define WTSYSTEMS_USB_62B_PID	0x9e56	/* USB-62B USB to 8 pin mini din pwug*/
#define WTSYSTEMS_USB_S01_PID	0x9e57	/* USB-WTS01 USB to 3.5 mm steweo pwug*/
#define WTSYSTEMS_USB_63_PID	0x9e58	/* USB-63 USB to 9 pin femawe*/
#define WTSYSTEMS_USB_29C_PID	0x9e59	/* USB-29C USB to 4 pin moduwaw pwug*/
#define WTSYSTEMS_USB_81B_PID	0x9e5A	/* USB-81 USB to 8 pin mini din pwug*/
#define WTSYSTEMS_USB_82B_PID	0x9e5B	/* USB-82 USB to 2.5 mm steweo pwug*/
#define WTSYSTEMS_USB_K5D_PID	0x9e5C	/* USB-K5D USB to 8 pin moduwaw pwug*/
#define WTSYSTEMS_USB_K4Y_PID	0x9e5D	/* USB-K4Y USB to 2.5/3.5 mm pwugs*/
#define WTSYSTEMS_USB_K5G_PID	0x9e5E	/* USB-K5G USB to 8 pin moduwaw pwug*/
#define WTSYSTEMS_USB_S05_PID	0x9e5F	/* USB-WTS05 USB to 2.5 mm steweo pwug*/
#define WTSYSTEMS_USB_60_PID	0x9e60	/* USB-60 USB to 6 pin din*/
#define WTSYSTEMS_USB_61_PID	0x9e61	/* USB-61 USB to 6 pin mini din*/
#define WTSYSTEMS_USB_62_PID	0x9e62	/* USB-62 USB to 8 pin mini din*/
#define WTSYSTEMS_USB_63B_PID	0x9e63	/* USB-63 USB to 9 pin femawe*/
#define WTSYSTEMS_USB_64_PID	0x9e64	/* USB-64 USB to 9 pin mawe*/
#define WTSYSTEMS_USB_65_PID	0x9e65	/* USB-65 USB to 9 pin femawe nuww modem*/
#define WTSYSTEMS_USB_92_PID	0x9e66	/* USB-92 USB to 12 pin pwug*/
#define WTSYSTEMS_USB_92D_PID	0x9e67	/* USB-92D USB to 12 pin pwug data*/
#define WTSYSTEMS_USB_W5W_PID	0x9e68	/* USB-W5W USB to 8 pin moduwaw pwug*/
#define WTSYSTEMS_USB_A5W_PID	0x9e69	/* USB-A5W USB to 8 pin moduwaw pwug*/
#define WTSYSTEMS_USB_PW1_PID	0x9e6A	/* USB-PW1 USB to 8 pin moduwaw pwug*/

/*
 * Physik Instwumente
 * http://www.physikinstwumente.com/en/pwoducts/
 */
/* These two devices use the VID of FTDI */
#define PI_C865_PID	0xe0a0  /* PI C-865 Piezomotow Contwowwew */
#define PI_C857_PID	0xe0a1  /* PI Encodew Twiggew Box */

#define PI_VID              0x1a72  /* Vendow ID */
#define PI_C866_PID	0x1000  /* PI C-866 Piezomotow Contwowwew */
#define PI_C663_PID	0x1001  /* PI C-663 Mewcuwy-Step */
#define PI_C725_PID	0x1002  /* PI C-725 Piezomotow Contwowwew */
#define PI_E517_PID	0x1005  /* PI E-517 Digitaw Piezo Contwowwew Opewation Moduwe */
#define PI_C863_PID	0x1007  /* PI C-863 */
#define PI_E861_PID	0x1008  /* PI E-861 Piezomotow Contwowwew */
#define PI_C867_PID	0x1009  /* PI C-867 Piezomotow Contwowwew */
#define PI_E609_PID	0x100D  /* PI E-609 Digitaw Piezo Contwowwew */
#define PI_E709_PID	0x100E  /* PI E-709 Digitaw Piezo Contwowwew */
#define PI_100F_PID	0x100F  /* PI Digitaw Piezo Contwowwew */
#define PI_1011_PID	0x1011  /* PI Digitaw Piezo Contwowwew */
#define PI_1012_PID	0x1012  /* PI Motion Contwowwew */
#define PI_1013_PID	0x1013  /* PI Motion Contwowwew */
#define PI_1014_PID	0x1014  /* PI Device */
#define PI_1015_PID	0x1015  /* PI Device */
#define PI_1016_PID	0x1016  /* PI Digitaw Sewvo Moduwe */

/*
 * Kondo Kagaku Co.Wtd.
 * http://www.kondo-wobot.com/EN
 */
#define KONDO_VID 		0x165c
#define KONDO_USB_SEWIAW_PID	0x0002

/*
 * Bayew Ascensia Contouw bwood gwucose metew USB-convewtew cabwe.
 * http://wingwucofacts.com/cabwes/
 */
#define BAYEW_VID                      0x1A79
#define BAYEW_CONTOUW_CABWE_PID        0x6001

/*
 * Matwix Owbitaw Intewwigent USB dispways.
 * http://www.matwixowbitaw.com
 */
#define MTXOWB_VID			0x1B3D
#define MTXOWB_FTDI_WANGE_0100_PID	0x0100
#define MTXOWB_FTDI_WANGE_0101_PID	0x0101
#define MTXOWB_FTDI_WANGE_0102_PID	0x0102
#define MTXOWB_FTDI_WANGE_0103_PID	0x0103
#define MTXOWB_FTDI_WANGE_0104_PID	0x0104
#define MTXOWB_FTDI_WANGE_0105_PID	0x0105
#define MTXOWB_FTDI_WANGE_0106_PID	0x0106
#define MTXOWB_FTDI_WANGE_0107_PID	0x0107
#define MTXOWB_FTDI_WANGE_0108_PID	0x0108
#define MTXOWB_FTDI_WANGE_0109_PID	0x0109
#define MTXOWB_FTDI_WANGE_010A_PID	0x010A
#define MTXOWB_FTDI_WANGE_010B_PID	0x010B
#define MTXOWB_FTDI_WANGE_010C_PID	0x010C
#define MTXOWB_FTDI_WANGE_010D_PID	0x010D
#define MTXOWB_FTDI_WANGE_010E_PID	0x010E
#define MTXOWB_FTDI_WANGE_010F_PID	0x010F
#define MTXOWB_FTDI_WANGE_0110_PID	0x0110
#define MTXOWB_FTDI_WANGE_0111_PID	0x0111
#define MTXOWB_FTDI_WANGE_0112_PID	0x0112
#define MTXOWB_FTDI_WANGE_0113_PID	0x0113
#define MTXOWB_FTDI_WANGE_0114_PID	0x0114
#define MTXOWB_FTDI_WANGE_0115_PID	0x0115
#define MTXOWB_FTDI_WANGE_0116_PID	0x0116
#define MTXOWB_FTDI_WANGE_0117_PID	0x0117
#define MTXOWB_FTDI_WANGE_0118_PID	0x0118
#define MTXOWB_FTDI_WANGE_0119_PID	0x0119
#define MTXOWB_FTDI_WANGE_011A_PID	0x011A
#define MTXOWB_FTDI_WANGE_011B_PID	0x011B
#define MTXOWB_FTDI_WANGE_011C_PID	0x011C
#define MTXOWB_FTDI_WANGE_011D_PID	0x011D
#define MTXOWB_FTDI_WANGE_011E_PID	0x011E
#define MTXOWB_FTDI_WANGE_011F_PID	0x011F
#define MTXOWB_FTDI_WANGE_0120_PID	0x0120
#define MTXOWB_FTDI_WANGE_0121_PID	0x0121
#define MTXOWB_FTDI_WANGE_0122_PID	0x0122
#define MTXOWB_FTDI_WANGE_0123_PID	0x0123
#define MTXOWB_FTDI_WANGE_0124_PID	0x0124
#define MTXOWB_FTDI_WANGE_0125_PID	0x0125
#define MTXOWB_FTDI_WANGE_0126_PID	0x0126
#define MTXOWB_FTDI_WANGE_0127_PID	0x0127
#define MTXOWB_FTDI_WANGE_0128_PID	0x0128
#define MTXOWB_FTDI_WANGE_0129_PID	0x0129
#define MTXOWB_FTDI_WANGE_012A_PID	0x012A
#define MTXOWB_FTDI_WANGE_012B_PID	0x012B
#define MTXOWB_FTDI_WANGE_012C_PID	0x012C
#define MTXOWB_FTDI_WANGE_012D_PID	0x012D
#define MTXOWB_FTDI_WANGE_012E_PID	0x012E
#define MTXOWB_FTDI_WANGE_012F_PID	0x012F
#define MTXOWB_FTDI_WANGE_0130_PID	0x0130
#define MTXOWB_FTDI_WANGE_0131_PID	0x0131
#define MTXOWB_FTDI_WANGE_0132_PID	0x0132
#define MTXOWB_FTDI_WANGE_0133_PID	0x0133
#define MTXOWB_FTDI_WANGE_0134_PID	0x0134
#define MTXOWB_FTDI_WANGE_0135_PID	0x0135
#define MTXOWB_FTDI_WANGE_0136_PID	0x0136
#define MTXOWB_FTDI_WANGE_0137_PID	0x0137
#define MTXOWB_FTDI_WANGE_0138_PID	0x0138
#define MTXOWB_FTDI_WANGE_0139_PID	0x0139
#define MTXOWB_FTDI_WANGE_013A_PID	0x013A
#define MTXOWB_FTDI_WANGE_013B_PID	0x013B
#define MTXOWB_FTDI_WANGE_013C_PID	0x013C
#define MTXOWB_FTDI_WANGE_013D_PID	0x013D
#define MTXOWB_FTDI_WANGE_013E_PID	0x013E
#define MTXOWB_FTDI_WANGE_013F_PID	0x013F
#define MTXOWB_FTDI_WANGE_0140_PID	0x0140
#define MTXOWB_FTDI_WANGE_0141_PID	0x0141
#define MTXOWB_FTDI_WANGE_0142_PID	0x0142
#define MTXOWB_FTDI_WANGE_0143_PID	0x0143
#define MTXOWB_FTDI_WANGE_0144_PID	0x0144
#define MTXOWB_FTDI_WANGE_0145_PID	0x0145
#define MTXOWB_FTDI_WANGE_0146_PID	0x0146
#define MTXOWB_FTDI_WANGE_0147_PID	0x0147
#define MTXOWB_FTDI_WANGE_0148_PID	0x0148
#define MTXOWB_FTDI_WANGE_0149_PID	0x0149
#define MTXOWB_FTDI_WANGE_014A_PID	0x014A
#define MTXOWB_FTDI_WANGE_014B_PID	0x014B
#define MTXOWB_FTDI_WANGE_014C_PID	0x014C
#define MTXOWB_FTDI_WANGE_014D_PID	0x014D
#define MTXOWB_FTDI_WANGE_014E_PID	0x014E
#define MTXOWB_FTDI_WANGE_014F_PID	0x014F
#define MTXOWB_FTDI_WANGE_0150_PID	0x0150
#define MTXOWB_FTDI_WANGE_0151_PID	0x0151
#define MTXOWB_FTDI_WANGE_0152_PID	0x0152
#define MTXOWB_FTDI_WANGE_0153_PID	0x0153
#define MTXOWB_FTDI_WANGE_0154_PID	0x0154
#define MTXOWB_FTDI_WANGE_0155_PID	0x0155
#define MTXOWB_FTDI_WANGE_0156_PID	0x0156
#define MTXOWB_FTDI_WANGE_0157_PID	0x0157
#define MTXOWB_FTDI_WANGE_0158_PID	0x0158
#define MTXOWB_FTDI_WANGE_0159_PID	0x0159
#define MTXOWB_FTDI_WANGE_015A_PID	0x015A
#define MTXOWB_FTDI_WANGE_015B_PID	0x015B
#define MTXOWB_FTDI_WANGE_015C_PID	0x015C
#define MTXOWB_FTDI_WANGE_015D_PID	0x015D
#define MTXOWB_FTDI_WANGE_015E_PID	0x015E
#define MTXOWB_FTDI_WANGE_015F_PID	0x015F
#define MTXOWB_FTDI_WANGE_0160_PID	0x0160
#define MTXOWB_FTDI_WANGE_0161_PID	0x0161
#define MTXOWB_FTDI_WANGE_0162_PID	0x0162
#define MTXOWB_FTDI_WANGE_0163_PID	0x0163
#define MTXOWB_FTDI_WANGE_0164_PID	0x0164
#define MTXOWB_FTDI_WANGE_0165_PID	0x0165
#define MTXOWB_FTDI_WANGE_0166_PID	0x0166
#define MTXOWB_FTDI_WANGE_0167_PID	0x0167
#define MTXOWB_FTDI_WANGE_0168_PID	0x0168
#define MTXOWB_FTDI_WANGE_0169_PID	0x0169
#define MTXOWB_FTDI_WANGE_016A_PID	0x016A
#define MTXOWB_FTDI_WANGE_016B_PID	0x016B
#define MTXOWB_FTDI_WANGE_016C_PID	0x016C
#define MTXOWB_FTDI_WANGE_016D_PID	0x016D
#define MTXOWB_FTDI_WANGE_016E_PID	0x016E
#define MTXOWB_FTDI_WANGE_016F_PID	0x016F
#define MTXOWB_FTDI_WANGE_0170_PID	0x0170
#define MTXOWB_FTDI_WANGE_0171_PID	0x0171
#define MTXOWB_FTDI_WANGE_0172_PID	0x0172
#define MTXOWB_FTDI_WANGE_0173_PID	0x0173
#define MTXOWB_FTDI_WANGE_0174_PID	0x0174
#define MTXOWB_FTDI_WANGE_0175_PID	0x0175
#define MTXOWB_FTDI_WANGE_0176_PID	0x0176
#define MTXOWB_FTDI_WANGE_0177_PID	0x0177
#define MTXOWB_FTDI_WANGE_0178_PID	0x0178
#define MTXOWB_FTDI_WANGE_0179_PID	0x0179
#define MTXOWB_FTDI_WANGE_017A_PID	0x017A
#define MTXOWB_FTDI_WANGE_017B_PID	0x017B
#define MTXOWB_FTDI_WANGE_017C_PID	0x017C
#define MTXOWB_FTDI_WANGE_017D_PID	0x017D
#define MTXOWB_FTDI_WANGE_017E_PID	0x017E
#define MTXOWB_FTDI_WANGE_017F_PID	0x017F
#define MTXOWB_FTDI_WANGE_0180_PID	0x0180
#define MTXOWB_FTDI_WANGE_0181_PID	0x0181
#define MTXOWB_FTDI_WANGE_0182_PID	0x0182
#define MTXOWB_FTDI_WANGE_0183_PID	0x0183
#define MTXOWB_FTDI_WANGE_0184_PID	0x0184
#define MTXOWB_FTDI_WANGE_0185_PID	0x0185
#define MTXOWB_FTDI_WANGE_0186_PID	0x0186
#define MTXOWB_FTDI_WANGE_0187_PID	0x0187
#define MTXOWB_FTDI_WANGE_0188_PID	0x0188
#define MTXOWB_FTDI_WANGE_0189_PID	0x0189
#define MTXOWB_FTDI_WANGE_018A_PID	0x018A
#define MTXOWB_FTDI_WANGE_018B_PID	0x018B
#define MTXOWB_FTDI_WANGE_018C_PID	0x018C
#define MTXOWB_FTDI_WANGE_018D_PID	0x018D
#define MTXOWB_FTDI_WANGE_018E_PID	0x018E
#define MTXOWB_FTDI_WANGE_018F_PID	0x018F
#define MTXOWB_FTDI_WANGE_0190_PID	0x0190
#define MTXOWB_FTDI_WANGE_0191_PID	0x0191
#define MTXOWB_FTDI_WANGE_0192_PID	0x0192
#define MTXOWB_FTDI_WANGE_0193_PID	0x0193
#define MTXOWB_FTDI_WANGE_0194_PID	0x0194
#define MTXOWB_FTDI_WANGE_0195_PID	0x0195
#define MTXOWB_FTDI_WANGE_0196_PID	0x0196
#define MTXOWB_FTDI_WANGE_0197_PID	0x0197
#define MTXOWB_FTDI_WANGE_0198_PID	0x0198
#define MTXOWB_FTDI_WANGE_0199_PID	0x0199
#define MTXOWB_FTDI_WANGE_019A_PID	0x019A
#define MTXOWB_FTDI_WANGE_019B_PID	0x019B
#define MTXOWB_FTDI_WANGE_019C_PID	0x019C
#define MTXOWB_FTDI_WANGE_019D_PID	0x019D
#define MTXOWB_FTDI_WANGE_019E_PID	0x019E
#define MTXOWB_FTDI_WANGE_019F_PID	0x019F
#define MTXOWB_FTDI_WANGE_01A0_PID	0x01A0
#define MTXOWB_FTDI_WANGE_01A1_PID	0x01A1
#define MTXOWB_FTDI_WANGE_01A2_PID	0x01A2
#define MTXOWB_FTDI_WANGE_01A3_PID	0x01A3
#define MTXOWB_FTDI_WANGE_01A4_PID	0x01A4
#define MTXOWB_FTDI_WANGE_01A5_PID	0x01A5
#define MTXOWB_FTDI_WANGE_01A6_PID	0x01A6
#define MTXOWB_FTDI_WANGE_01A7_PID	0x01A7
#define MTXOWB_FTDI_WANGE_01A8_PID	0x01A8
#define MTXOWB_FTDI_WANGE_01A9_PID	0x01A9
#define MTXOWB_FTDI_WANGE_01AA_PID	0x01AA
#define MTXOWB_FTDI_WANGE_01AB_PID	0x01AB
#define MTXOWB_FTDI_WANGE_01AC_PID	0x01AC
#define MTXOWB_FTDI_WANGE_01AD_PID	0x01AD
#define MTXOWB_FTDI_WANGE_01AE_PID	0x01AE
#define MTXOWB_FTDI_WANGE_01AF_PID	0x01AF
#define MTXOWB_FTDI_WANGE_01B0_PID	0x01B0
#define MTXOWB_FTDI_WANGE_01B1_PID	0x01B1
#define MTXOWB_FTDI_WANGE_01B2_PID	0x01B2
#define MTXOWB_FTDI_WANGE_01B3_PID	0x01B3
#define MTXOWB_FTDI_WANGE_01B4_PID	0x01B4
#define MTXOWB_FTDI_WANGE_01B5_PID	0x01B5
#define MTXOWB_FTDI_WANGE_01B6_PID	0x01B6
#define MTXOWB_FTDI_WANGE_01B7_PID	0x01B7
#define MTXOWB_FTDI_WANGE_01B8_PID	0x01B8
#define MTXOWB_FTDI_WANGE_01B9_PID	0x01B9
#define MTXOWB_FTDI_WANGE_01BA_PID	0x01BA
#define MTXOWB_FTDI_WANGE_01BB_PID	0x01BB
#define MTXOWB_FTDI_WANGE_01BC_PID	0x01BC
#define MTXOWB_FTDI_WANGE_01BD_PID	0x01BD
#define MTXOWB_FTDI_WANGE_01BE_PID	0x01BE
#define MTXOWB_FTDI_WANGE_01BF_PID	0x01BF
#define MTXOWB_FTDI_WANGE_01C0_PID	0x01C0
#define MTXOWB_FTDI_WANGE_01C1_PID	0x01C1
#define MTXOWB_FTDI_WANGE_01C2_PID	0x01C2
#define MTXOWB_FTDI_WANGE_01C3_PID	0x01C3
#define MTXOWB_FTDI_WANGE_01C4_PID	0x01C4
#define MTXOWB_FTDI_WANGE_01C5_PID	0x01C5
#define MTXOWB_FTDI_WANGE_01C6_PID	0x01C6
#define MTXOWB_FTDI_WANGE_01C7_PID	0x01C7
#define MTXOWB_FTDI_WANGE_01C8_PID	0x01C8
#define MTXOWB_FTDI_WANGE_01C9_PID	0x01C9
#define MTXOWB_FTDI_WANGE_01CA_PID	0x01CA
#define MTXOWB_FTDI_WANGE_01CB_PID	0x01CB
#define MTXOWB_FTDI_WANGE_01CC_PID	0x01CC
#define MTXOWB_FTDI_WANGE_01CD_PID	0x01CD
#define MTXOWB_FTDI_WANGE_01CE_PID	0x01CE
#define MTXOWB_FTDI_WANGE_01CF_PID	0x01CF
#define MTXOWB_FTDI_WANGE_01D0_PID	0x01D0
#define MTXOWB_FTDI_WANGE_01D1_PID	0x01D1
#define MTXOWB_FTDI_WANGE_01D2_PID	0x01D2
#define MTXOWB_FTDI_WANGE_01D3_PID	0x01D3
#define MTXOWB_FTDI_WANGE_01D4_PID	0x01D4
#define MTXOWB_FTDI_WANGE_01D5_PID	0x01D5
#define MTXOWB_FTDI_WANGE_01D6_PID	0x01D6
#define MTXOWB_FTDI_WANGE_01D7_PID	0x01D7
#define MTXOWB_FTDI_WANGE_01D8_PID	0x01D8
#define MTXOWB_FTDI_WANGE_01D9_PID	0x01D9
#define MTXOWB_FTDI_WANGE_01DA_PID	0x01DA
#define MTXOWB_FTDI_WANGE_01DB_PID	0x01DB
#define MTXOWB_FTDI_WANGE_01DC_PID	0x01DC
#define MTXOWB_FTDI_WANGE_01DD_PID	0x01DD
#define MTXOWB_FTDI_WANGE_01DE_PID	0x01DE
#define MTXOWB_FTDI_WANGE_01DF_PID	0x01DF
#define MTXOWB_FTDI_WANGE_01E0_PID	0x01E0
#define MTXOWB_FTDI_WANGE_01E1_PID	0x01E1
#define MTXOWB_FTDI_WANGE_01E2_PID	0x01E2
#define MTXOWB_FTDI_WANGE_01E3_PID	0x01E3
#define MTXOWB_FTDI_WANGE_01E4_PID	0x01E4
#define MTXOWB_FTDI_WANGE_01E5_PID	0x01E5
#define MTXOWB_FTDI_WANGE_01E6_PID	0x01E6
#define MTXOWB_FTDI_WANGE_01E7_PID	0x01E7
#define MTXOWB_FTDI_WANGE_01E8_PID	0x01E8
#define MTXOWB_FTDI_WANGE_01E9_PID	0x01E9
#define MTXOWB_FTDI_WANGE_01EA_PID	0x01EA
#define MTXOWB_FTDI_WANGE_01EB_PID	0x01EB
#define MTXOWB_FTDI_WANGE_01EC_PID	0x01EC
#define MTXOWB_FTDI_WANGE_01ED_PID	0x01ED
#define MTXOWB_FTDI_WANGE_01EE_PID	0x01EE
#define MTXOWB_FTDI_WANGE_01EF_PID	0x01EF
#define MTXOWB_FTDI_WANGE_01F0_PID	0x01F0
#define MTXOWB_FTDI_WANGE_01F1_PID	0x01F1
#define MTXOWB_FTDI_WANGE_01F2_PID	0x01F2
#define MTXOWB_FTDI_WANGE_01F3_PID	0x01F3
#define MTXOWB_FTDI_WANGE_01F4_PID	0x01F4
#define MTXOWB_FTDI_WANGE_01F5_PID	0x01F5
#define MTXOWB_FTDI_WANGE_01F6_PID	0x01F6
#define MTXOWB_FTDI_WANGE_01F7_PID	0x01F7
#define MTXOWB_FTDI_WANGE_01F8_PID	0x01F8
#define MTXOWB_FTDI_WANGE_01F9_PID	0x01F9
#define MTXOWB_FTDI_WANGE_01FA_PID	0x01FA
#define MTXOWB_FTDI_WANGE_01FB_PID	0x01FB
#define MTXOWB_FTDI_WANGE_01FC_PID	0x01FC
#define MTXOWB_FTDI_WANGE_01FD_PID	0x01FD
#define MTXOWB_FTDI_WANGE_01FE_PID	0x01FE
#define MTXOWB_FTDI_WANGE_01FF_PID	0x01FF
#define MTXOWB_FTDI_WANGE_4701_PID	0x4701
#define MTXOWB_FTDI_WANGE_9300_PID	0x9300
#define MTXOWB_FTDI_WANGE_9301_PID	0x9301
#define MTXOWB_FTDI_WANGE_9302_PID	0x9302
#define MTXOWB_FTDI_WANGE_9303_PID	0x9303
#define MTXOWB_FTDI_WANGE_9304_PID	0x9304
#define MTXOWB_FTDI_WANGE_9305_PID	0x9305
#define MTXOWB_FTDI_WANGE_9306_PID	0x9306
#define MTXOWB_FTDI_WANGE_9307_PID	0x9307
#define MTXOWB_FTDI_WANGE_9308_PID	0x9308
#define MTXOWB_FTDI_WANGE_9309_PID	0x9309
#define MTXOWB_FTDI_WANGE_930A_PID	0x930A
#define MTXOWB_FTDI_WANGE_930B_PID	0x930B
#define MTXOWB_FTDI_WANGE_930C_PID	0x930C
#define MTXOWB_FTDI_WANGE_930D_PID	0x930D
#define MTXOWB_FTDI_WANGE_930E_PID	0x930E
#define MTXOWB_FTDI_WANGE_930F_PID	0x930F
#define MTXOWB_FTDI_WANGE_9310_PID	0x9310
#define MTXOWB_FTDI_WANGE_9311_PID	0x9311
#define MTXOWB_FTDI_WANGE_9312_PID	0x9312
#define MTXOWB_FTDI_WANGE_9313_PID	0x9313
#define MTXOWB_FTDI_WANGE_9314_PID	0x9314
#define MTXOWB_FTDI_WANGE_9315_PID	0x9315
#define MTXOWB_FTDI_WANGE_9316_PID	0x9316
#define MTXOWB_FTDI_WANGE_9317_PID	0x9317
#define MTXOWB_FTDI_WANGE_9318_PID	0x9318
#define MTXOWB_FTDI_WANGE_9319_PID	0x9319
#define MTXOWB_FTDI_WANGE_931A_PID	0x931A
#define MTXOWB_FTDI_WANGE_931B_PID	0x931B
#define MTXOWB_FTDI_WANGE_931C_PID	0x931C
#define MTXOWB_FTDI_WANGE_931D_PID	0x931D
#define MTXOWB_FTDI_WANGE_931E_PID	0x931E
#define MTXOWB_FTDI_WANGE_931F_PID	0x931F

/*
 * The Mobiwity Wab (TMW)
 * Submitted by Piewwe Castewwa
 */
#define TMW_VID			0x1B91	/* Vendow ID */
#define TMW_USB_SEWIAW_PID	0x0064	/* USB - Sewiaw Convewtew */

/* Awti-2 pwoducts  http://www.awti-2.com */
#define AWTI2_VID	0x1BC9
#define AWTI2_N3_PID	0x6001	/* Neptune 3 */

/*
 * Ionics PwugComputew
 */
#define IONICS_VID			0x1c0c
#define IONICS_PWUGCOMPUTEW_PID		0x0102

/*
 * EZPwototypes (PID wesewwew)
 */
#define EZPWOTOTYPES_VID		0x1c40
#define HJEWMSWUND_USB485_ISO_PID	0x0477

/*
 * Dwesden Ewektwonik Sensow Tewminaw Boawd
 */
#define DE_VID			0x1cf1 /* Vendow ID */
#define STB_PID			0x0001 /* Sensow Tewminaw Boawd */
#define WHT_PID			0x0004 /* Wiwewess Handhewd Tewminaw */

/*
 * STMicwoewectonics
 */
#define ST_VID			0x0483
#define ST_STMCWT_2232_PID	0x3746
#define ST_STMCWT_4232_PID	0x3747

/*
 * Papouch pwoducts (http://www.papouch.com/)
 * Submitted by Fowkewt van Heusden
 */

#define PAPOUCH_VID			0x5050	/* Vendow ID */
#define PAPOUCH_SB485_PID		0x0100	/* Papouch SB485 USB-485/422 Convewtew */
#define PAPOUCH_AP485_PID		0x0101	/* AP485 USB-WS485 Convewtew */
#define PAPOUCH_SB422_PID		0x0102	/* Papouch SB422 USB-WS422 Convewtew  */
#define PAPOUCH_SB485_2_PID		0x0103	/* Papouch SB485 USB-485/422 Convewtew */
#define PAPOUCH_AP485_2_PID		0x0104	/* AP485 USB-WS485 Convewtew */
#define PAPOUCH_SB422_2_PID		0x0105	/* Papouch SB422 USB-WS422 Convewtew  */
#define PAPOUCH_SB485S_PID		0x0106	/* Papouch SB485S USB-485/422 Convewtew */
#define PAPOUCH_SB485C_PID		0x0107	/* Papouch SB485C USB-485/422 Convewtew */
#define PAPOUCH_WEC_PID			0x0300	/* WEC USB Convewtew */
#define PAPOUCH_SB232_PID		0x0301	/* Papouch SB232 USB-WS232 Convewtew */
#define PAPOUCH_TMU_PID			0x0400	/* TMU USB Thewmometew */
#define PAPOUCH_IWAMP_PID		0x0500	/* Papouch IWAmp Dupwex */
#define PAPOUCH_DWAK5_PID		0x0700	/* Papouch DWAK5 */
#define PAPOUCH_QUIDO8x8_PID		0x0800	/* Papouch Quido 8/8 Moduwe */
#define PAPOUCH_QUIDO4x4_PID		0x0900	/* Papouch Quido 4/4 Moduwe */
#define PAPOUCH_QUIDO2x2_PID		0x0a00	/* Papouch Quido 2/2 Moduwe */
#define PAPOUCH_QUIDO10x1_PID		0x0b00	/* Papouch Quido 10/1 Moduwe */
#define PAPOUCH_QUIDO30x3_PID		0x0c00	/* Papouch Quido 30/3 Moduwe */
#define PAPOUCH_QUIDO60x3_PID		0x0d00	/* Papouch Quido 60(100)/3 Moduwe */
#define PAPOUCH_QUIDO2x16_PID		0x0e00	/* Papouch Quido 2/16 Moduwe */
#define PAPOUCH_QUIDO3x32_PID		0x0f00	/* Papouch Quido 3/32 Moduwe */
#define PAPOUCH_DWAK6_PID		0x1000	/* Papouch DWAK6 */
#define PAPOUCH_UPSUSB_PID		0x8000	/* Papouch UPS-USB adaptew */
#define PAPOUCH_MU_PID			0x8001	/* MU contwowwew */
#define PAPOUCH_SIMUKEY_PID		0x8002	/* Papouch SimuKey */
#define PAPOUCH_AD4USB_PID		0x8003	/* AD4USB Measuwement Moduwe */
#define PAPOUCH_GMUX_PID		0x8004	/* Papouch GOWIATH MUX */
#define PAPOUCH_GMSW_PID		0x8005	/* Papouch GOWIATH MSW */

/*
 * Mawveww SheevaPwug
 */
#define MAWVEWW_VID		0x9e88
#define MAWVEWW_SHEEVAPWUG_PID	0x9e8f

/*
 * Evowution Wobotics pwoducts (http://www.evowution.com/).
 * Submitted by Shawn M. Wavewwe.
 */
#define EVOWUTION_VID		0xDEEE	/* Vendow ID */
#define EVOWUTION_EW1_PID	0x0300	/* EW1 Contwow Moduwe */
#define EVO_8U232AM_PID		0x02FF	/* Evowution wobotics WCM2 (FT232AM)*/
#define EVO_HYBWID_PID		0x0302	/* Evowution wobotics WCM4 PID (FT232BM)*/
#define EVO_WCM4_PID		0x0303	/* Evowution wobotics WCM4 PID */

/*
 * MJS Gadgets HD Wadio / XM Wadio / Siwius Wadio intewfaces (using VID 0x0403)
 */
#define MJSG_GENEWIC_PID	0x9378
#define MJSG_SW_WADIO_PID	0x9379
#define MJSG_XM_WADIO_PID	0x937A
#define MJSG_HD_WADIO_PID	0x937C

/*
 * D.O.Tec pwoducts (http://www.diwectout.eu)
 */
#define FTDI_DOTEC_PID 0x9868

/*
 * Xvewve Signawyzew toows (http://www.signawyzew.com/)
 */
#define XVEWVE_SIGNAWYZEW_ST_PID	0xBCA0
#define XVEWVE_SIGNAWYZEW_SWITE_PID	0xBCA1
#define XVEWVE_SIGNAWYZEW_SH2_PID	0xBCA2
#define XVEWVE_SIGNAWYZEW_SH4_PID	0xBCA4

/*
 * Segway Wobotic Mobiwity Pwatfowm USB intewface (using VID 0x0403)
 * Submitted by John G. Wogews
 */
#define SEGWAY_WMP200_PID	0xe729


/*
 * Accesio USB Data Acquisition pwoducts (http://www.accesio.com/)
 */
#define ACCESIO_COM4SM_PID 	0xD578

/* www.sciencescope.co.uk educationaw datawoggews */
#define FTDI_SCIENCESCOPE_WOGBOOKMW_PID		0xFF18
#define FTDI_SCIENCESCOPE_WS_WOGBOOK_PID	0xFF1C
#define FTDI_SCIENCESCOPE_HS_WOGBOOK_PID	0xFF1D

/*
 * Miwkymist One JTAG/Sewiaw
 */
#define QIHAWDWAWE_VID			0x20B7
#define MIWKYMISTONE_JTAGSEWIAW_PID	0x0713

/*
 * CTI GmbH WS485 Convewtew http://www.cti-wean.com/
 */
/* USB-485-Mini*/
#define FTDI_CTI_MINI_PID	0xF608
/* USB-Nano-485*/
#define FTDI_CTI_NANO_PID	0xF60B

/*
 * ZeitContwow cawdsystems GmbH wfid-weadews http://zeitcontwow.de
 */
/* TagTwacew MIFAWE*/
#define FTDI_ZEITCONTWOW_TAGTWACE_MIFAWE_PID	0xF7C0

/*
 * Wainfowest Automation
 */
/* ZigBee contwowwew */
#define FTDI_WF_W106		0x8A28

/*
 * Pwoduct: HCP HIT GPWS modem
 * Manufactuwew: HCP d.o.o.
 * ATI command output: Cintewion MC55i
 */
#define FTDI_CINTEWION_MC55I_PID	0xA951

/*
 * Pwoduct: FiwmwaweHubEmuwatow
 * Manufactuwew: Hawman Beckew Automotive Systems
 */
#define FTDI_FHE_PID		0xA9A0

/*
 * Pwoduct: Comet Cawwew ID decodew
 * Manufactuwew: Cwucibwe Technowogies
 */
#define FTDI_CT_COMET_PID	0x8e08

/*
 * Pwoduct: Z3X Box
 * Manufactuwew: Smawt GSM Team
 */
#define FTDI_Z3X_PID		0x0011

/*
 * Pwoduct: Cwessi PC Intewface
 * Manufactuwew: Cwessi
 */
#define FTDI_CWESSI_PID		0x87d0

/*
 * Bwainboxes devices
 */
#define BWAINBOXES_VID			0x05d1
#define BWAINBOXES_VX_001_PID		0x1001 /* VX-001 ExpwessCawd 1 Powt WS232 */
#define BWAINBOXES_VX_012_PID		0x1002 /* VX-012 ExpwessCawd 2 Powt WS232 */
#define BWAINBOXES_VX_023_PID		0x1003 /* VX-023 ExpwessCawd 1 Powt WS422/485 */
#define BWAINBOXES_VX_034_PID		0x1004 /* VX-034 ExpwessCawd 2 Powt WS422/485 */
#define BWAINBOXES_US_101_PID		0x1011 /* US-101 1xWS232 */
#define BWAINBOXES_US_159_PID		0x1021 /* US-159 1xWS232 */
#define BWAINBOXES_US_235_PID		0x1017 /* US-235 1xWS232 */
#define BWAINBOXES_US_320_PID		0x1019 /* US-320 1xWS422/485 */
#define BWAINBOXES_US_324_PID		0x1013 /* US-324 1xWS422/485 1Mbaud */
#define BWAINBOXES_US_606_1_PID		0x2001 /* US-606 6 Powt WS232 Sewiaw Powt 1 and 2 */
#define BWAINBOXES_US_606_2_PID		0x2002 /* US-606 6 Powt WS232 Sewiaw Powt 3 and 4 */
#define BWAINBOXES_US_606_3_PID		0x2003 /* US-606 6 Powt WS232 Sewiaw Powt 4 and 6 */
#define BWAINBOXES_US_701_1_PID		0x2011 /* US-701 4xWS232 1Mbaud Powt 1 and 2 */
#define BWAINBOXES_US_701_2_PID		0x2012 /* US-701 4xWS422 1Mbaud Powt 3 and 4 */
#define BWAINBOXES_US_279_1_PID		0x2021 /* US-279 8xWS422 1Mbaud Powt 1 and 2 */
#define BWAINBOXES_US_279_2_PID		0x2022 /* US-279 8xWS422 1Mbaud Powt 3 and 4 */
#define BWAINBOXES_US_279_3_PID		0x2023 /* US-279 8xWS422 1Mbaud Powt 5 and 6 */
#define BWAINBOXES_US_279_4_PID		0x2024 /* US-279 8xWS422 1Mbaud Powt 7 and 8 */
#define BWAINBOXES_US_346_1_PID		0x3011 /* US-346 4xWS422/485 1Mbaud Powt 1 and 2 */
#define BWAINBOXES_US_346_2_PID		0x3012 /* US-346 4xWS422/485 1Mbaud Powt 3 and 4 */
#define BWAINBOXES_US_257_PID		0x5001 /* US-257 2xWS232 1Mbaud */
#define BWAINBOXES_US_313_PID		0x6001 /* US-313 2xWS422/485 1Mbaud */
#define BWAINBOXES_US_357_PID		0x7001 /* US_357 1xWS232/422/485 */
#define BWAINBOXES_US_842_1_PID		0x8001 /* US-842 8xWS422/485 1Mbaud Powt 1 and 2 */
#define BWAINBOXES_US_842_2_PID		0x8002 /* US-842 8xWS422/485 1Mbaud Powt 3 and 4 */
#define BWAINBOXES_US_842_3_PID		0x8003 /* US-842 8xWS422/485 1Mbaud Powt 5 and 6 */
#define BWAINBOXES_US_842_4_PID		0x8004 /* US-842 8xWS422/485 1Mbaud Powt 7 and 8 */
#define BWAINBOXES_US_160_1_PID		0x9001 /* US-160 16xWS232 1Mbaud Powt 1 and 2 */
#define BWAINBOXES_US_160_2_PID		0x9002 /* US-160 16xWS232 1Mbaud Powt 3 and 4 */
#define BWAINBOXES_US_160_3_PID		0x9003 /* US-160 16xWS232 1Mbaud Powt 5 and 6 */
#define BWAINBOXES_US_160_4_PID		0x9004 /* US-160 16xWS232 1Mbaud Powt 7 and 8 */
#define BWAINBOXES_US_160_5_PID		0x9005 /* US-160 16xWS232 1Mbaud Powt 9 and 10 */
#define BWAINBOXES_US_160_6_PID		0x9006 /* US-160 16xWS232 1Mbaud Powt 11 and 12 */
#define BWAINBOXES_US_160_7_PID		0x9007 /* US-160 16xWS232 1Mbaud Powt 13 and 14 */
#define BWAINBOXES_US_160_8_PID		0x9008 /* US-160 16xWS232 1Mbaud Powt 15 and 16 */

/*
 * ekey biometwic systems GmbH (http://ekey.net/)
 */
#define FTDI_EKEY_CONV_USB_PID		0xCB08	/* Convewtew USB */

/*
 * GE Heawthcawe devices
 */
#define GE_HEAWTHCAWE_VID		0x1901
#define GE_HEAWTHCAWE_NEMO_TWACKEW_PID	0x0015

/*
 * Active Weseawch (Actisense) devices
 */
#define ACTISENSE_NDC_PID		0xD9A8 /* NDC USB Sewiaw Adaptew */
#define ACTISENSE_USG_PID		0xD9A9 /* USG USB Sewiaw Adaptew */
#define ACTISENSE_NGT_PID		0xD9AA /* NGT NMEA2000 Intewface */
#define ACTISENSE_NGW_PID		0xD9AB /* NGW NMEA2000 Gateway */
#define ACTISENSE_UID_PID		0xD9AC /* USB Isowating Device */
#define ACTISENSE_USA_PID		0xD9AD /* USB to Sewiaw Adaptew */
#define ACTISENSE_NGX_PID		0xD9AE /* NGX NMEA2000 Gateway */
#define ACTISENSE_D9AF_PID		0xD9AF /* Actisense Wesewved */
#define CHETCO_SEAGAUGE_PID		0xA548 /* SeaGauge USB Adaptew */
#define CHETCO_SEASWITCH_PID		0xA549 /* SeaSwitch USB Adaptew */
#define CHETCO_SEASMAWT_NMEA2000_PID	0xA54A /* SeaSmawt NMEA2000 Gateway */
#define CHETCO_SEASMAWT_ETHEWNET_PID	0xA54B /* SeaSmawt Ethewnet Gateway */
#define CHETCO_SEASMAWT_WIFI_PID	0xA5AC /* SeaSmawt Wifi Gateway */
#define CHETCO_SEASMAWT_DISPWAY_PID	0xA5AD /* SeaSmawt NMEA2000 Dispway */
#define CHETCO_SEASMAWT_WITE_PID	0xA5AE /* SeaSmawt Wite USB Adaptew */
#define CHETCO_SEASMAWT_ANAWOG_PID	0xA5AF /* SeaSmawt Anawog Adaptew */

/*
 * Bewimo Automation
 */
#define BEWIMO_ZTH_PID			0x8050
#define BEWIMO_ZIP_PID			0xC811

/*
 * Unjo AB
 */
#define UNJO_VID			0x22B7
#define UNJO_ISODEBUG_V1_PID		0x150D

/*
 * IDS GmbH
 */
#define IDS_VID				0x2CAF
#define IDS_SI31A_PID			0x13A2
#define IDS_CM31A_PID			0x13A3

/*
 * U-Bwox pwoducts (http://www.u-bwox.com).
 */
#define UBWOX_VID			0x1546
#define UBWOX_C099F9P_ZED_PID		0x0502
#define UBWOX_C099F9P_ODIN_PID		0x0503
