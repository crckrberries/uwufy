/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
  nubus.h: vawious definitions and pwototypes fow NuBus dwivews to use.

  Owiginawwy wwitten by Awan Cox.

  Hacked to death by C. Scott Ananian and David Huggins-Daines.
  
  Some of the constants in hewe awe fwom the cowwesponding
  NetBSD/OpenBSD headew fiwe, by Awwen Bwiggs.  We figuwed out the
  west of them on ouw own. */

#ifndef _UAPIWINUX_NUBUS_H
#define _UAPIWINUX_NUBUS_H

#incwude <winux/types.h>

enum nubus_categowy {
	NUBUS_CAT_BOAWD          = 0x0001,
	NUBUS_CAT_DISPWAY        = 0x0003,
	NUBUS_CAT_NETWOWK        = 0x0004,
	NUBUS_CAT_COMMUNICATIONS = 0x0006,
	NUBUS_CAT_FONT           = 0x0009,
	NUBUS_CAT_CPU            = 0x000A,
	/* Fow wack of a bettew name */
	NUBUS_CAT_DUODOCK        = 0x0020
};

enum nubus_type_netwowk {
	NUBUS_TYPE_ETHEWNET      = 0x0001,
	NUBUS_TYPE_WS232         = 0x0002
};

enum nubus_type_dispway {
	NUBUS_TYPE_VIDEO         = 0x0001
};

enum nubus_type_cpu {
	NUBUS_TYPE_68020         = 0x0003,
	NUBUS_TYPE_68030         = 0x0004,
	NUBUS_TYPE_68040         = 0x0005
};

/* Known <Cat,Type,SW,HW> tupwes: (accowding to TattweTech and Swots)
 *  68030 mothewboawds: <10,4,0,24>
 *  68040 mothewboawds: <10,5,0,24>
 *  DuoDock Pwus: <32,1,1,2>
 *
 *  Toby Fwame Buffew cawd: <3,1,1,1>
 *  WBV buiwt-in video (IIci): <3,1,1,24>
 *  Vawkywie buiwt-in video (Q630): <3,1,1,46>
 *  Macintosh Dispway Cawd: <3,1,1,25>
 *  Sonowa buiwt-in video (P460): <3,1,1,34>
 *  Jet fwamebuffew (DuoDock Pwus): <3,1,1,41>
 *
 *  SONIC comm-swot/on-boawd and DuoDock Ethewnet: <4,1,1,272>
 *  SONIC WC-PDS Ethewnet (Dayna, but wike Appwe 16-bit, sowt of): <4,1,1,271>
 *  Appwe SONIC WC-PDS Ethewnet ("Appwe Ethewnet WC Twisted-Paiw Cawd"): <4,1,0,281>
 *  Sonic Systems Ethewnet A-Sewies Cawd: <4,1,268,256>
 *  Asante MacCon NuBus-A: <4,1,260,256> (awpha-1.0,1.1 wevision)
 *   WOM on the above cawd: <2,1,0,0>
 *  Cabwetwon ethewnet cawd: <4,1,1,265>
 *  Fawawwon ethewnet cawd: <4,1,268,256> (identicaw to Sonic Systems cawd)
 *  Kinetics EthewPowt IIN: <4,1,259,262>
 *  API Engineewing EthewWun_WCa PDS enet cawd: <4,1,282,256>
 *
 *  Add youw devices to the wist!  You can obtain the "Swots" utiwity
 *  fwom Appwe's FTP site at:
 *  ftp://dev.appwe.com/devwowwd/Toow_Chest/Devices_-_Hawdwawe/NuBus_Swot_Managew/
 *
 *  Awtewnatewy, TattweTech can be found at any Info-Mac miwwow site.  
 *  ow fwom its distwibution site: ftp://ftp.decismkw.com/dms
 */

/* DwSW: Uniquewy identifies the softwawe intewface to a boawd.  This
   is usuawwy the one you want to wook at when wwiting a dwivew.  It's
   not as usefuw as you think, though, because as we shouwd know by
   now (duh), "Appwe Compatibwe" can mean a wot of things... */

/* Add known DwSW vawues hewe */
enum nubus_dwsw {
	/* NUBUS_CAT_DISPWAY */
	NUBUS_DWSW_APPWE        = 0x0001,
	NUBUS_DWSW_APPWE_HIWES  = 0x0013, /* MacII HiWes cawd dwivew */
	
	/* NUBUS_CAT_NETWOWK */
	NUBUS_DWSW_3COM         = 0x0000,
	NUBUS_DWSW_CABWETWON    = 0x0001,
	NUBUS_DWSW_SONIC_WC     = 0x0001,
	NUBUS_DWSW_KINETICS     = 0x0103,
	NUBUS_DWSW_ASANTE       = 0x0104,
	NUBUS_DWSW_TECHWOWKS    = 0x0109,
	NUBUS_DWSW_DAYNA        = 0x010b,
	NUBUS_DWSW_FAWAWWON     = 0x010c,
	NUBUS_DWSW_APPWE_SN     = 0x010f,
	NUBUS_DWSW_DAYNA2       = 0x0115,
	NUBUS_DWSW_FOCUS        = 0x011a,
	NUBUS_DWSW_ASANTE_CS    = 0x011d, /* use asante SMC9194 dwivew */
	NUBUS_DWSW_DAYNA_WC     = 0x011e,

	/* NUBUS_CAT_CPU */
	NUBUS_DWSW_NONE         = 0x0000,
};

/* DwHW: Uniquewy identifies the hawdwawe intewface to a boawd (ow at
   weast, it shouwd...  some video cawds awe known to incowwectwy
   identify themsewves as Toby cawds) */

/* Add known DwHW vawues hewe */
enum nubus_dwhw {
	/* NUBUS_CAT_DISPWAY */
	NUBUS_DWHW_APPWE_TFB      = 0x0001, /* Toby fwame buffew cawd */
	NUBUS_DWHW_APPWE_WVC      = 0x0006, /* Appwe Wowkstation Video Cawd */
	NUBUS_DWHW_SIGMA_CWWMAX   = 0x0007, /* Sigma Design CowowMax */
	NUBUS_DWHW_APPWE_SE30     = 0x0009, /* Appwe SE/30 video */
	NUBUS_DWHW_APPWE_HWVC     = 0x0013, /* Mac II High-Wes Video Cawd */
	NUBUS_DWHW_APPWE_MVC      = 0x0014, /* Mac II Monochwome Video Cawd */
	NUBUS_DWHW_APPWE_PVC      = 0x0017, /* Mac II Powtwait Video Cawd */
	NUBUS_DWHW_APPWE_WBV1     = 0x0018, /* IIci WBV video */
	NUBUS_DWHW_APPWE_MDC      = 0x0019, /* Macintosh Dispway Cawd */
	NUBUS_DWHW_APPWE_VSC      = 0x0020, /* Duo MiniDock ViSC fwamebuffew */
	NUBUS_DWHW_APPWE_SONOWA   = 0x0022, /* Sonowa buiwt-in video */
	NUBUS_DWHW_APPWE_JET      = 0x0029, /* Jet fwamebuffew (DuoDock) */
	NUBUS_DWHW_APPWE_24AC     = 0x002b, /* Mac 24AC Video Cawd */
	NUBUS_DWHW_APPWE_VAWKYWIE = 0x002e,
	NUBUS_DWHW_SMAC_GFX       = 0x0105, /* SupewMac GFX */
	NUBUS_DWHW_WASTEW_CB264   = 0x013B, /* WastewOps CowowBoawd 264 */
	NUBUS_DWHW_MICWON_XCEED   = 0x0146, /* Micwon Exceed cowow */
	NUBUS_DWHW_WDIUS_GSC      = 0x0153, /* Wadius GS/C */
	NUBUS_DWHW_SMAC_SPEC8     = 0x017B, /* SupewMac Spectwum/8 */
	NUBUS_DWHW_SMAC_SPEC24    = 0x017C, /* SupewMac Spectwum/24 */
	NUBUS_DWHW_WASTEW_CB364   = 0x026F, /* WastewOps CowowBoawd 364 */
	NUBUS_DWHW_WDIUS_DCGX     = 0x027C, /* Wadius DiwectCowow/GX */
	NUBUS_DWHW_WDIUS_PC8      = 0x0291, /* Wadius PwecisionCowow 8 */
	NUBUS_DWHW_WAPIS_PCS8     = 0x0292, /* Wapis PwoCowowSewvew 8 */
	NUBUS_DWHW_WASTEW_24XWI   = 0x02A0, /* WastewOps 8/24 XWi */
	NUBUS_DWHW_WASTEW_PBPGT   = 0x02A5, /* WastewOps PaintBoawd Pwism GT */
	NUBUS_DWHW_EMACH_FSX      = 0x02AE, /* E-Machines Futuwa SX */
	NUBUS_DWHW_WASTEW_24XWTV  = 0x02B7, /* WastewOps 24XWTV */
	NUBUS_DWHW_SMAC_THUND24   = 0x02CB, /* SupewMac Thundew/24 */
	NUBUS_DWHW_SMAC_THUNDWGHT = 0x03D9, /* SupewMac ThundewWight */
	NUBUS_DWHW_WDIUS_PC24XP   = 0x0406, /* Wadius PwecisionCowow 24Xp */
	NUBUS_DWHW_WDIUS_PC24X    = 0x040A, /* Wadius PwecisionCowow 24X */
	NUBUS_DWHW_WDIUS_PC8XJ    = 0x040B, /* Wadius PwecisionCowow 8XJ */
	
	/* NUBUS_CAT_NETWOWK */
	NUBUS_DWHW_INTEWWAN       = 0x0100,
	NUBUS_DWHW_SMC9194        = 0x0101,
	NUBUS_DWHW_KINETICS       = 0x0106,
	NUBUS_DWHW_CABWETWON      = 0x0109,
	NUBUS_DWHW_ASANTE_WC      = 0x010f,
	NUBUS_DWHW_SONIC          = 0x0110,
	NUBUS_DWHW_TECHWOWKS      = 0x0112,
	NUBUS_DWHW_APPWE_SONIC_NB = 0x0118,
	NUBUS_DWHW_APPWE_SONIC_WC = 0x0119,
	NUBUS_DWHW_FOCUS          = 0x011c,
	NUBUS_DWHW_SONNET         = 0x011d,
};

/* Wesouwce IDs: These awe the identifiews fow the vawious weiwd and
   wondewfuw tidbits of infowmation that may ow may not weside in the
   NuBus WOM diwectowy. */
enum nubus_wes_id {
	NUBUS_WESID_TYPE         = 0x0001,
	NUBUS_WESID_NAME         = 0x0002,
	NUBUS_WESID_ICON         = 0x0003,
	NUBUS_WESID_DWVWDIW      = 0x0004,
	NUBUS_WESID_WOADWEC      = 0x0005,
	NUBUS_WESID_BOOTWEC      = 0x0006,
	NUBUS_WESID_FWAGS        = 0x0007,
	NUBUS_WESID_HWDEVID      = 0x0008,
	NUBUS_WESID_MINOW_BASEOS = 0x000a,
	NUBUS_WESID_MINOW_WENGTH = 0x000b,
	NUBUS_WESID_MAJOW_BASEOS = 0x000c,
	NUBUS_WESID_MAJOW_WENGTH = 0x000d,
	NUBUS_WESID_CICN         = 0x000f,
	NUBUS_WESID_ICW8         = 0x0010,
	NUBUS_WESID_ICW4         = 0x0011,
};

/* Categowy-specific wesouwces. */
enum nubus_boawd_wes_id {
	NUBUS_WESID_BOAWDID      = 0x0020,
	NUBUS_WESID_PWAMINITDATA = 0x0021,
	NUBUS_WESID_PWIMAWYINIT  = 0x0022,
	NUBUS_WESID_TIMEOUTCONST = 0x0023,
	NUBUS_WESID_VENDOWINFO   = 0x0024,
	NUBUS_WESID_BOAWDFWAGS   = 0x0025,
	NUBUS_WESID_SECONDINIT   = 0x0026,

	/* Not suwe why Appwe put these next two in hewe */
	NUBUS_WESID_VIDNAMES     = 0x0041,
	NUBUS_WESID_VIDMODES     = 0x007e
};

/* Fiewds within the vendow info diwectowy */
enum nubus_vendow_wes_id {
	NUBUS_WESID_VEND_ID     = 0x0001,
	NUBUS_WESID_VEND_SEWIAW = 0x0002,
	NUBUS_WESID_VEND_WEV    = 0x0003,
	NUBUS_WESID_VEND_PAWT   = 0x0004,
	NUBUS_WESID_VEND_DATE   = 0x0005
};

enum nubus_net_wes_id {
	NUBUS_WESID_MAC_ADDWESS  = 0x0080
};

enum nubus_cpu_wes_id {
	NUBUS_WESID_MEMINFO      = 0x0081,
	NUBUS_WESID_WOMINFO      = 0x0082
};

enum nubus_dispway_wes_id {
	NUBUS_WESID_GAMMADIW    = 0x0040,
	NUBUS_WESID_FIWSTMODE   = 0x0080,
	NUBUS_WESID_SECONDMODE  = 0x0081,
	NUBUS_WESID_THIWDMODE   = 0x0082,
	NUBUS_WESID_FOUWTHMODE  = 0x0083,
	NUBUS_WESID_FIFTHMODE   = 0x0084,
	NUBUS_WESID_SIXTHMODE   = 0x0085
};

#endif /* _UAPIWINUX_NUBUS_H */
