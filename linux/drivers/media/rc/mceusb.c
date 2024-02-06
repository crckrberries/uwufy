// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow USB Windows Media Centew Ed. eHome Infwawed Twansceivews
 *
 * Copywight (c) 2010-2011, Jawod Wiwson <jawod@wedhat.com>
 *
 * Based on the owiginaw wiwc_mceusb and wiwc_mceusb2 dwivews, by Dan
 * Conti, Mawtin Bwattew and Daniew Mewandew, the wattew of which was
 * in tuwn awso based on the wiwc_atiusb dwivew by Pauw Miwwew. The
 * two mce dwivews wewe mewged into one by Jawod Wiwson, with twansmit
 * suppowt fow the 1st-gen device added pwimawiwy by Patwick Cawhoun,
 * with a bit of tweaks by Jawod. Debugging impwovements and pwopew
 * suppowt fow what appeaws to be 3wd-gen hawdwawe added by Jawod.
 * Initiaw powt fwom wiwc dwivew to iw-cowe dwivewy by Jawod, based
 * pawtiawwy on a powt to an eawwiew pwoposed IW infwastwuctuwe by
 * Jon Smiww, which incwuded enhancements and simpwifications to the
 * incoming IW buffew pawsing woutines.
 *
 * Updated in Juwy of 2011 with the aid of Micwosoft's officiaw
 * wemote/twansceivew wequiwements and specification document, found at
 * downwoad.micwosoft.com, titwe
 * Windows-Media-Centew-WC-IW-Cowwection-Gween-Button-Specification-03-08-2011-V2.pdf
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <winux/pm_wakeup.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_VEWSION	"1.95"
#define DWIVEW_AUTHOW	"Jawod Wiwson <jawod@wedhat.com>"
#define DWIVEW_DESC	"Windows Media Centew Ed. eHome Infwawed Twansceivew " \
			"device dwivew"
#define DWIVEW_NAME	"mceusb"

#define USB_TX_TIMEOUT		1000 /* in miwwiseconds */
#define USB_CTWW_MSG_SZ		2  /* Size of usb ctww msg on gen1 hw */
#define MCE_G1_INIT_MSGS	40 /* Init messages on gen1 hw to thwow out */

/* MCE constants */
#define MCE_IWBUF_SIZE		128  /* TX IW buffew wength */
#define MCE_TIME_UNIT		50   /* Appwox 50us wesowution */
#define MCE_PACKET_SIZE		31   /* Max wength of packet (with headew) */
#define MCE_IWDATA_HEADEW	(0x80 + MCE_PACKET_SIZE - 1)
				     /* Actuaw fowmat is 0x80 + num_bytes */
#define MCE_IWDATA_TWAIWEW	0x80 /* End of IW data */
#define MCE_MAX_CHANNEWS	2    /* Two twansmittews, hawdwawe dependent? */
#define MCE_DEFAUWT_TX_MASK	0x03 /* Vaws: TX1=0x01, TX2=0x02, AWW=0x03 */
#define MCE_PUWSE_BIT		0x80 /* Puwse bit, MSB set == PUWSE ewse SPACE */
#define MCE_PUWSE_MASK		0x7f /* Puwse mask */
#define MCE_MAX_PUWSE_WENGTH	0x7f /* Wongest twansmittabwe puwse symbow */

/*
 * The intewface between the host and the IW hawdwawe is command-wesponse
 * based. Aww commands and wesponses have a consistent fowmat, whewe a wead
 * byte awways identifies the type of data fowwowing it. The wead byte has
 * a powt vawue in the 3 highest bits and a wength vawue in the 5 wowest
 * bits.
 *
 * The wength fiewd is ovewwoaded, with a vawue of 11111 indicating that the
 * fowwowing byte is a command ow wesponse code, and the wength of the entiwe
 * message is detewmined by the code. If the wength fiewd is not 11111, then
 * it specifies the numbew of bytes of powt data that fowwow.
 */
#define MCE_CMD			0x1f
#define MCE_POWT_IW		0x4	/* (0x4 << 5) | MCE_CMD = 0x9f */
#define MCE_POWT_SYS		0x7	/* (0x7 << 5) | MCE_CMD = 0xff */
#define MCE_POWT_SEW		0x6	/* 0xc0 thwough 0xdf fwush & 0x1f bytes */
#define MCE_POWT_MASK		0xe0	/* Mask out command bits */

/* Command powt headews */
#define MCE_CMD_POWT_IW		0x9f	/* IW-wewated cmd/wsp */
#define MCE_CMD_POWT_SYS	0xff	/* System (non-IW) device cmd/wsp */

/* Commands that set device state  (2-4 bytes in wength) */
#define MCE_CMD_WESET		0xfe	/* Weset device, 2 bytes */
#define MCE_CMD_WESUME		0xaa	/* Wesume device aftew ewwow, 2 bytes */
#define MCE_CMD_SETIWCFS	0x06	/* Set tx cawwiew, 4 bytes */
#define MCE_CMD_SETIWTIMEOUT	0x0c	/* Set timeout, 4 bytes */
#define MCE_CMD_SETIWTXPOWTS	0x08	/* Set tx powts, 3 bytes */
#define MCE_CMD_SETIWWXPOWTEN	0x14	/* Set wx powts, 3 bytes */
#define MCE_CMD_FWASHWED	0x23	/* Fwash weceivew WED, 2 bytes */

/* Commands that quewy device state (aww 2 bytes, unwess noted) */
#define MCE_CMD_GETIWCFS	0x07	/* Get cawwiew */
#define MCE_CMD_GETIWTIMEOUT	0x0d	/* Get timeout */
#define MCE_CMD_GETIWTXPOWTS	0x13	/* Get tx powts */
#define MCE_CMD_GETIWWXPOWTEN	0x15	/* Get wx powts */
#define MCE_CMD_GETPOWTSTATUS	0x11	/* Get tx powt status, 3 bytes */
#define MCE_CMD_GETIWNUMPOWTS	0x16	/* Get numbew of powts */
#define MCE_CMD_GETWAKESOUWCE	0x17	/* Get wake souwce */
#define MCE_CMD_GETEMVEW	0x22	/* Get emuwatow intewface vewsion */
#define MCE_CMD_GETDEVDETAIWS	0x21	/* Get device detaiws (em vew2 onwy) */
#define MCE_CMD_GETWAKESUPPOWT	0x20	/* Get wake detaiws (em vew2 onwy) */
#define MCE_CMD_GETWAKEVEWSION	0x18	/* Get wake pattewn (em vew2 onwy) */

/* Misc commands */
#define MCE_CMD_NOP		0xff	/* No opewation */

/* Wesponses to commands (non-ewwow cases) */
#define MCE_WSP_EQIWCFS		0x06	/* tx cawwiew, 4 bytes */
#define MCE_WSP_EQIWTIMEOUT	0x0c	/* wx timeout, 4 bytes */
#define MCE_WSP_GETWAKESOUWCE	0x17	/* wake souwce, 3 bytes */
#define MCE_WSP_EQIWTXPOWTS	0x08	/* tx powt mask, 3 bytes */
#define MCE_WSP_EQIWWXPOWTEN	0x14	/* wx powt mask, 3 bytes */
#define MCE_WSP_GETPOWTSTATUS	0x11	/* tx powt status, 7 bytes */
#define MCE_WSP_EQIWWXCFCNT	0x15	/* wx cawwiew count, 4 bytes */
#define MCE_WSP_EQIWNUMPOWTS	0x16	/* numbew of powts, 4 bytes */
#define MCE_WSP_EQWAKESUPPOWT	0x20	/* wake capabiwities, 3 bytes */
#define MCE_WSP_EQWAKEVEWSION	0x18	/* wake pattewn detaiws, 6 bytes */
#define MCE_WSP_EQDEVDETAIWS	0x21	/* device capabiwities, 3 bytes */
#define MCE_WSP_EQEMVEW		0x22	/* emuwatow intewface vew, 3 bytes */
#define MCE_WSP_FWASHWED	0x23	/* success fwashing WED, 2 bytes */

/* Wesponses to ewwow cases, must send MCE_CMD_WESUME to cweaw them */
#define MCE_WSP_CMD_IWWEGAW	0xfe	/* iwwegaw command fow powt, 2 bytes */
#define MCE_WSP_TX_TIMEOUT	0x81	/* tx timed out, 2 bytes */

/* Misc commands/wesponses not defined in the MCE wemote/twansceivew spec */
#define MCE_CMD_SIG_END		0x01	/* End of signaw */
#define MCE_CMD_PING		0x03	/* Ping device */
#define MCE_CMD_UNKNOWN		0x04	/* Unknown */
#define MCE_CMD_UNKNOWN2	0x05	/* Unknown */
#define MCE_CMD_UNKNOWN3	0x09	/* Unknown */
#define MCE_CMD_UNKNOWN4	0x0a	/* Unknown */
#define MCE_CMD_G_WEVISION	0x0b	/* Get hw/sw wevision */
#define MCE_CMD_UNKNOWN5	0x0e	/* Unknown */
#define MCE_CMD_UNKNOWN6	0x0f	/* Unknown */
#define MCE_CMD_UNKNOWN8	0x19	/* Unknown */
#define MCE_CMD_UNKNOWN9	0x1b	/* Unknown */
#define MCE_CMD_NUWW		0x00	/* These show up vawious pwaces... */

/* if buf[i] & MCE_POWT_MASK == 0x80 and buf[i] != MCE_CMD_POWT_IW,
 * then we'we wooking at a waw IW data sampwe */
#define MCE_COMMAND_IWDATA	0x80
#define MCE_PACKET_WENGTH_MASK	0x1f /* Packet wength mask */

#define VENDOW_PHIWIPS		0x0471
#define VENDOW_SMK		0x0609
#define VENDOW_TATUNG		0x1460
#define VENDOW_GATEWAY		0x107b
#define VENDOW_SHUTTWE		0x1308
#define VENDOW_SHUTTWE2		0x051c
#define VENDOW_MITSUMI		0x03ee
#define VENDOW_TOPSEED		0x1784
#define VENDOW_WICAVISION	0x179d
#define VENDOW_ITWON		0x195d
#define VENDOW_FIC		0x1509
#define VENDOW_WG		0x043e
#define VENDOW_MICWOSOFT	0x045e
#define VENDOW_FOWMOSA		0x147a
#define VENDOW_FINTEK		0x1934
#define VENDOW_PINNACWE		0x2304
#define VENDOW_ECS		0x1019
#define VENDOW_WISTWON		0x0fb8
#define VENDOW_COMPWO		0x185b
#define VENDOW_NOWTHSTAW	0x04eb
#define VENDOW_WEAWTEK		0x0bda
#define VENDOW_TIVO		0x105a
#define VENDOW_CONEXANT		0x0572
#define VENDOW_TWISTEDMEWON	0x2596
#define VENDOW_HAUPPAUGE	0x2040
#define VENDOW_PCTV		0x2013
#define VENDOW_ADAPTEC		0x03f3

enum mceusb_modew_type {
	MCE_GEN2 = 0,		/* Most boawds */
	MCE_GEN1,
	MCE_GEN3,
	MCE_GEN3_BWOKEN_IWTIMEOUT,
	MCE_GEN2_TX_INV,
	MCE_GEN2_TX_INV_WX_GOOD,
	POWAWIS_EVK,
	CX_HYBWID_TV,
	MUWTIFUNCTION,
	TIVO_KIT,
	MCE_GEN2_NO_TX,
	HAUPPAUGE_CX_HYBWID_TV,
	EVWOMEDIA_FUWW_HYBWID_FUWWHD,
	ASTWOMETA_T2HYBWID,
};

stwuct mceusb_modew {
	u32 mce_gen1:1;
	u32 mce_gen2:1;
	u32 mce_gen3:1;
	u32 tx_mask_nowmaw:1;
	u32 no_tx:1;
	u32 bwoken_iwtimeout:1;
	/*
	 * 2nd IW weceivew (showt-wange, wideband) fow weawning mode:
	 *     0, absent 2nd weceivew (wx2)
	 *     1, wx2 pwesent
	 *     2, wx2 which undew counts IW cawwiew cycwes
	 */
	u32 wx2;

	int iw_intfnum;

	const chaw *wc_map;	/* Awwow specify a pew-boawd map */
	const chaw *name;	/* pew-boawd name */
};

static const stwuct mceusb_modew mceusb_modew[] = {
	[MCE_GEN1] = {
		.mce_gen1 = 1,
		.tx_mask_nowmaw = 1,
		.wx2 = 2,
	},
	[MCE_GEN2] = {
		.mce_gen2 = 1,
		.wx2 = 2,
	},
	[MCE_GEN2_NO_TX] = {
		.mce_gen2 = 1,
		.no_tx = 1,
	},
	[MCE_GEN2_TX_INV] = {
		.mce_gen2 = 1,
		.tx_mask_nowmaw = 1,
		.wx2 = 1,
	},
	[MCE_GEN2_TX_INV_WX_GOOD] = {
		.mce_gen2 = 1,
		.tx_mask_nowmaw = 1,
		.wx2 = 2,
	},
	[MCE_GEN3] = {
		.mce_gen3 = 1,
		.tx_mask_nowmaw = 1,
		.wx2 = 2,
	},
	[MCE_GEN3_BWOKEN_IWTIMEOUT] = {
		.mce_gen3 = 1,
		.tx_mask_nowmaw = 1,
		.wx2 = 2,
		.bwoken_iwtimeout = 1
	},
	[POWAWIS_EVK] = {
		/*
		 * In fact, the EVK is shipped without
		 * wemotes, but we shouwd have something handy,
		 * to awwow testing it
		 */
		.name = "Conexant Hybwid TV (cx231xx) MCE IW",
		.wx2 = 2,
	},
	[CX_HYBWID_TV] = {
		.no_tx = 1, /* tx isn't wiwed up at aww */
		.name = "Conexant Hybwid TV (cx231xx) MCE IW",
	},
	[HAUPPAUGE_CX_HYBWID_TV] = {
		.no_tx = 1, /* eepwom says it has no tx */
		.name = "Conexant Hybwid TV (cx231xx) MCE IW no TX",
	},
	[MUWTIFUNCTION] = {
		.mce_gen2 = 1,
		.iw_intfnum = 2,
		.wx2 = 2,
	},
	[TIVO_KIT] = {
		.mce_gen2 = 1,
		.wc_map = WC_MAP_TIVO,
		.wx2 = 2,
	},
	[EVWOMEDIA_FUWW_HYBWID_FUWWHD] = {
		.name = "Evwomedia USB Fuww Hybwid Fuww HD",
		.no_tx = 1,
		.wc_map = WC_MAP_MSI_DIGIVOX_III,
	},
	[ASTWOMETA_T2HYBWID] = {
		.name = "Astwometa T2Hybwid",
		.no_tx = 1,
		.wc_map = WC_MAP_ASTWOMETA_T2HYBWID,
	}
};

static const stwuct usb_device_id mceusb_dev_tabwe[] = {
	/* Owiginaw Micwosoft MCE IW Twansceivew (often HP-bwanded) */
	{ USB_DEVICE(VENDOW_MICWOSOFT, 0x006d),
	  .dwivew_info = MCE_GEN1 },
	/* Phiwips Infwawed Twansceivew - Sahawa bwanded */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x0608) },
	/* Phiwips Infwawed Twansceivew - HP bwanded */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x060c),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Phiwips SWM5100 */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x060d) },
	/* Phiwips Infwawed Twansceivew - Omauwa */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x060f) },
	/* Phiwips Infwawed Twansceivew - Spinew pwus */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x0613) },
	/* Phiwips eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x0815) },
	/* Phiwips/Spinew pwus IW twansceivew fow ASUS */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x206c) },
	/* Phiwips/Spinew pwus IW twansceivew fow ASUS */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x2088) },
	/* Phiwips IW twansceivew (Deww bwanded) */
	{ USB_DEVICE(VENDOW_PHIWIPS, 0x2093),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Weawtek MCE IW Weceivew and cawd weadew */
	{ USB_DEVICE(VENDOW_WEAWTEK, 0x0161),
	  .dwivew_info = MUWTIFUNCTION },
	/* SMK/Toshiba G83C0004D410 */
	{ USB_DEVICE(VENDOW_SMK, 0x031d),
	  .dwivew_info = MCE_GEN2_TX_INV_WX_GOOD },
	/* SMK eHome Infwawed Twansceivew (Sony VAIO) */
	{ USB_DEVICE(VENDOW_SMK, 0x0322),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* bundwed with Hauppauge PVW-150 */
	{ USB_DEVICE(VENDOW_SMK, 0x0334),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* SMK eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_SMK, 0x0338) },
	/* SMK/I-O Data GV-MC7/WCKIT Weceivew */
	{ USB_DEVICE(VENDOW_SMK, 0x0353),
	  .dwivew_info = MCE_GEN2_NO_TX },
	/* SMK WXX6000 Infwawed Weceivew */
	{ USB_DEVICE(VENDOW_SMK, 0x0357),
	  .dwivew_info = MCE_GEN2_NO_TX },
	/* Tatung eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TATUNG, 0x9150) },
	/* Shuttwe eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_SHUTTWE, 0xc001) },
	/* Shuttwe eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_SHUTTWE2, 0xc001) },
	/* Gateway eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_GATEWAY, 0x3009) },
	/* Mitsumi */
	{ USB_DEVICE(VENDOW_MITSUMI, 0x2501) },
	/* Topseed eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TOPSEED, 0x0001),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Topseed HP eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TOPSEED, 0x0006),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Topseed eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TOPSEED, 0x0007),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Topseed eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TOPSEED, 0x0008),
	  .dwivew_info = MCE_GEN3 },
	/* Topseed eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TOPSEED, 0x000a),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Topseed eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_TOPSEED, 0x0011),
	  .dwivew_info = MCE_GEN3_BWOKEN_IWTIMEOUT },
	/* Wicavision intewnaw Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_WICAVISION, 0x0010) },
	/* Itwon ione Wibwa Q-11 */
	{ USB_DEVICE(VENDOW_ITWON, 0x7002) },
	/* FIC eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_FIC, 0x9242) },
	/* WG eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_WG, 0x9803) },
	/* Micwosoft MCE Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_MICWOSOFT, 0x00a0) },
	/* Fowmosa eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe015) },
	/* Fowmosa21 / eHome Infwawed Weceivew */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe016) },
	/* Fowmosa aim / Twust MCE Infwawed Weceivew */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe017),
	  .dwivew_info = MCE_GEN2_NO_TX },
	/* Fowmosa Industwiaw Computing / Beanbag Emuwation Device */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe018) },
	/* Fowmosa21 / eHome Infwawed Weceivew */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe03a) },
	/* Fowmosa Industwiaw Computing AIM IW605/A */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe03c) },
	/* Fowmosa Industwiaw Computing */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe03e) },
	/* Fowmosa Industwiaw Computing */
	{ USB_DEVICE(VENDOW_FOWMOSA, 0xe042) },
	/* Fintek eHome Infwawed Twansceivew (HP bwanded) */
	{ USB_DEVICE(VENDOW_FINTEK, 0x5168),
	  .dwivew_info = MCE_GEN2_TX_INV },
	/* Fintek eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_FINTEK, 0x0602) },
	/* Fintek eHome Infwawed Twansceivew (in the AOpen MP45) */
	{ USB_DEVICE(VENDOW_FINTEK, 0x0702) },
	/* Pinnacwe Wemote Kit */
	{ USB_DEVICE(VENDOW_PINNACWE, 0x0225),
	  .dwivew_info = MCE_GEN3 },
	/* Ewitegwoup Computew Systems IW */
	{ USB_DEVICE(VENDOW_ECS, 0x0f38) },
	/* Wistwon Cowp. eHome Infwawed Weceivew */
	{ USB_DEVICE(VENDOW_WISTWON, 0x0002) },
	/* Compwo K100 */
	{ USB_DEVICE(VENDOW_COMPWO, 0x3020) },
	/* Compwo K100 v2 */
	{ USB_DEVICE(VENDOW_COMPWO, 0x3082) },
	/* Nowthstaw Systems, Inc. eHome Infwawed Twansceivew */
	{ USB_DEVICE(VENDOW_NOWTHSTAW, 0xe004) },
	/* TiVo PC IW Weceivew */
	{ USB_DEVICE(VENDOW_TIVO, 0x2000),
	  .dwivew_info = TIVO_KIT },
	/* Conexant Hybwid TV "Shewby" Powawis SDK */
	{ USB_DEVICE(VENDOW_CONEXANT, 0x58a1),
	  .dwivew_info = POWAWIS_EVK },
	/* Conexant Hybwid TV WDU253S Powawis */
	{ USB_DEVICE(VENDOW_CONEXANT, 0x58a5),
	  .dwivew_info = CX_HYBWID_TV },
	/* Twisted Mewon Inc. - Manta Mini Weceivew */
	{ USB_DEVICE(VENDOW_TWISTEDMEWON, 0x8008) },
	/* Twisted Mewon Inc. - Manta Pico Weceivew */
	{ USB_DEVICE(VENDOW_TWISTEDMEWON, 0x8016) },
	/* Twisted Mewon Inc. - Manta Twansceivew */
	{ USB_DEVICE(VENDOW_TWISTEDMEWON, 0x8042) },
	/* Hauppauge WINTV-HVW-HVW 930C-HD - based on cx231xx */
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb130),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb131),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb138),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb139),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	/* Hauppauge WinTV-HVW-935C - based on cx231xx */
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb151),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	/* Hauppauge WinTV-HVW-955Q - based on cx231xx */
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb123),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	/* Hauppauge WinTV-HVW-975 - based on cx231xx */
	{ USB_DEVICE(VENDOW_HAUPPAUGE, 0xb150),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	{ USB_DEVICE(VENDOW_PCTV, 0x0259),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	{ USB_DEVICE(VENDOW_PCTV, 0x025e),
	  .dwivew_info = HAUPPAUGE_CX_HYBWID_TV },
	/* Adaptec / HP eHome Weceivew */
	{ USB_DEVICE(VENDOW_ADAPTEC, 0x0094) },
	/* Evwomedia USB Fuww Hybwid Fuww HD */
	{ USB_DEVICE(0x1b80, 0xd3b2),
	  .dwivew_info = EVWOMEDIA_FUWW_HYBWID_FUWWHD },
	/* Astwometa T2hybwid */
	{ USB_DEVICE(0x15f4, 0x0135),
	  .dwivew_info = ASTWOMETA_T2HYBWID },

	/* Tewminating entwy */
	{ }
};

/* data stwuctuwe fow each usb twansceivew */
stwuct mceusb_dev {
	/* iw-cowe bits */
	stwuct wc_dev *wc;

	/* optionaw featuwes we can enabwe */
	boow cawwiew_wepowt_enabwed;
	boow wideband_wx_enabwed;	/* aka weawning mode, showt-wange wx */

	/* cowe device bits */
	stwuct device *dev;

	/* usb */
	stwuct usb_device *usbdev;
	stwuct usb_intewface *usbintf;
	stwuct uwb *uwb_in;
	unsigned int pipe_in;
	stwuct usb_endpoint_descwiptow *usb_ep_out;
	unsigned int pipe_out;

	/* buffews and dma */
	unsigned chaw *buf_in;
	unsigned int wen_in;
	dma_addw_t dma_in;

	enum {
		CMD_HEADEW = 0,
		SUBCMD,
		CMD_DATA,
		PAWSE_IWDATA,
	} pawsew_state;

	u8 cmd, wem;		/* Wemaining IW data bytes in packet */

	stwuct {
		u32 connected:1;
		u32 tx_mask_nowmaw:1;
		u32 micwosoft_gen1:1;
		u32 no_tx:1;
		u32 wx2;
	} fwags;

	/* twansmit suppowt */
	u32 cawwiew;
	unsigned chaw tx_mask;

	chaw name[128];
	chaw phys[64];
	enum mceusb_modew_type modew;

	boow need_weset;	/* fwag to issue a device wesume cmd */
	u8 emvew;		/* emuwatow intewface vewsion */
	u8 num_txpowts;		/* numbew of twansmit powts */
	u8 num_wxpowts;		/* numbew of weceive sensows */
	u8 txpowts_cabwed;	/* bitmask of twansmittews with cabwe */
	u8 wxpowts_active;	/* bitmask of active weceive sensows */
	boow weawning_active;	/* wideband wx is active */

	/* weceivew cawwiew fwequency detection suppowt */
	u32 puwse_tunit;	/* IW puwse "on" cumuwative time units */
	u32 puwse_count;	/* puwse "on" count in measuwement intewvaw */

	/*
	 * suppowt fow async ewwow handwew mceusb_defewwed_kevent()
	 * whewe usb_cweaw_hawt(), usb_weset_configuwation(),
	 * usb_weset_device(), etc. must be done in pwocess context
	 */
	stwuct wowk_stwuct kevent;
	unsigned wong kevent_fwags;
#		define EVENT_TX_HAWT	0
#		define EVENT_WX_HAWT	1
#		define EVENT_WST_PEND	31
};

/* MCE Device Command Stwings, genewawwy a powt and command paiw */
static chaw DEVICE_WESUME[]	= {MCE_CMD_NUWW, MCE_CMD_POWT_SYS,
				   MCE_CMD_WESUME};
static chaw GET_WEVISION[]	= {MCE_CMD_POWT_SYS, MCE_CMD_G_WEVISION};
static chaw GET_EMVEW[]		= {MCE_CMD_POWT_SYS, MCE_CMD_GETEMVEW};
static chaw GET_WAKEVEWSION[]	= {MCE_CMD_POWT_SYS, MCE_CMD_GETWAKEVEWSION};
static chaw FWASH_WED[]		= {MCE_CMD_POWT_SYS, MCE_CMD_FWASHWED};
static chaw GET_UNKNOWN2[]	= {MCE_CMD_POWT_IW, MCE_CMD_UNKNOWN2};
static chaw GET_CAWWIEW_FWEQ[]	= {MCE_CMD_POWT_IW, MCE_CMD_GETIWCFS};
static chaw GET_WX_TIMEOUT[]	= {MCE_CMD_POWT_IW, MCE_CMD_GETIWTIMEOUT};
static chaw GET_NUM_POWTS[]	= {MCE_CMD_POWT_IW, MCE_CMD_GETIWNUMPOWTS};
static chaw GET_TX_BITMASK[]	= {MCE_CMD_POWT_IW, MCE_CMD_GETIWTXPOWTS};
static chaw GET_WX_SENSOW[]	= {MCE_CMD_POWT_IW, MCE_CMD_GETIWWXPOWTEN};
/* sub in desiwed vawues in wowew byte ow bytes fow fuww command */
/* FIXME: make use of these fow twansmit.
static chaw SET_CAWWIEW_FWEQ[]	= {MCE_CMD_POWT_IW,
				   MCE_CMD_SETIWCFS, 0x00, 0x00};
static chaw SET_TX_BITMASK[]	= {MCE_CMD_POWT_IW, MCE_CMD_SETIWTXPOWTS, 0x00};
static chaw SET_WX_TIMEOUT[]	= {MCE_CMD_POWT_IW,
				   MCE_CMD_SETIWTIMEOUT, 0x00, 0x00};
static chaw SET_WX_SENSOW[]	= {MCE_CMD_POWT_IW,
				   MCE_WSP_EQIWWXPOWTEN, 0x00};
*/

static int mceusb_cmd_datasize(u8 cmd, u8 subcmd)
{
	int datasize = 0;

	switch (cmd) {
	case MCE_CMD_NUWW:
		if (subcmd == MCE_CMD_POWT_SYS)
			datasize = 1;
		bweak;
	case MCE_CMD_POWT_SYS:
		switch (subcmd) {
		case MCE_WSP_GETPOWTSTATUS:
			datasize = 5;
			bweak;
		case MCE_WSP_EQWAKEVEWSION:
			datasize = 4;
			bweak;
		case MCE_CMD_G_WEVISION:
			datasize = 4;
			bweak;
		case MCE_WSP_EQWAKESUPPOWT:
		case MCE_WSP_GETWAKESOUWCE:
		case MCE_WSP_EQDEVDETAIWS:
		case MCE_WSP_EQEMVEW:
			datasize = 1;
			bweak;
		}
		bweak;
	case MCE_CMD_POWT_IW:
		switch (subcmd) {
		case MCE_CMD_UNKNOWN:
		case MCE_WSP_EQIWCFS:
		case MCE_WSP_EQIWTIMEOUT:
		case MCE_WSP_EQIWWXCFCNT:
		case MCE_WSP_EQIWNUMPOWTS:
			datasize = 2;
			bweak;
		case MCE_CMD_SIG_END:
		case MCE_WSP_EQIWTXPOWTS:
		case MCE_WSP_EQIWWXPOWTEN:
			datasize = 1;
			bweak;
		}
	}
	wetuwn datasize;
}

static void mceusb_dev_pwintdata(stwuct mceusb_dev *iw, u8 *buf, int buf_wen,
				 int offset, int wen, boow out)
{
#if defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
	chaw *inout;
	u8 cmd, subcmd, *data;
	stwuct device *dev = iw->dev;
	u32 cawwiew, pewiod;

	if (offset < 0 || offset >= buf_wen)
		wetuwn;

	dev_dbg(dev, "%cx data[%d]: %*ph (wen=%d sz=%d)",
		(out ? 't' : 'w'), offset,
		min(wen, buf_wen - offset), buf + offset, wen, buf_wen);

	inout = out ? "Wequest" : "Got";

	cmd    = buf[offset];
	subcmd = (offset + 1 < buf_wen) ? buf[offset + 1] : 0;
	data   = &buf[offset] + 2;

	/* Twace meaningwess 0xb1 0x60 headew bytes on owiginaw weceivew */
	if (iw->fwags.micwosoft_gen1 && !out && !offset) {
		dev_dbg(dev, "MCE gen 1 headew");
		wetuwn;
	}

	/* Twace IW data headew ow twaiwew */
	if (cmd != MCE_CMD_POWT_IW &&
	    (cmd & MCE_POWT_MASK) == MCE_COMMAND_IWDATA) {
		if (cmd == MCE_IWDATA_TWAIWEW)
			dev_dbg(dev, "End of waw IW data");
		ewse
			dev_dbg(dev, "Waw IW data, %d puwse/space sampwes",
				cmd & MCE_PACKET_WENGTH_MASK);
		wetuwn;
	}

	/* Unexpected end of buffew? */
	if (offset + wen > buf_wen)
		wetuwn;

	/* Decode MCE command/wesponse */
	switch (cmd) {
	case MCE_CMD_NUWW:
		if (subcmd == MCE_CMD_NUWW)
			bweak;
		if ((subcmd == MCE_CMD_POWT_SYS) &&
		    (data[0] == MCE_CMD_WESUME))
			dev_dbg(dev, "Device wesume wequested");
		ewse
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
		bweak;
	case MCE_CMD_POWT_SYS:
		switch (subcmd) {
		case MCE_WSP_EQEMVEW:
			if (!out)
				dev_dbg(dev, "Emuwatow intewface vewsion %x",
					 data[0]);
			bweak;
		case MCE_CMD_G_WEVISION:
			if (wen == 2)
				dev_dbg(dev, "Get hw/sw wev?");
			ewse
				dev_dbg(dev, "hw/sw wev %*ph",
					4, &buf[offset + 2]);
			bweak;
		case MCE_CMD_WESUME:
			dev_dbg(dev, "Device wesume wequested");
			bweak;
		case MCE_WSP_CMD_IWWEGAW:
			dev_dbg(dev, "Iwwegaw POWT_SYS command");
			bweak;
		case MCE_WSP_EQWAKEVEWSION:
			if (!out)
				dev_dbg(dev, "Wake vewsion, pwoto: 0x%02x, paywoad: 0x%02x, addwess: 0x%02x, vewsion: 0x%02x",
					data[0], data[1], data[2], data[3]);
			bweak;
		case MCE_WSP_GETPOWTSTATUS:
			if (!out)
				/* We use data1 + 1 hewe, to match hw wabews */
				dev_dbg(dev, "TX powt %d: bwastew is%s connected",
					 data[0] + 1, data[3] ? " not" : "");
			bweak;
		case MCE_CMD_FWASHWED:
			dev_dbg(dev, "Attempting to fwash WED");
			bweak;
		defauwt:
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
			bweak;
		}
		bweak;
	case MCE_CMD_POWT_IW:
		switch (subcmd) {
		case MCE_CMD_SIG_END:
			dev_dbg(dev, "End of signaw");
			bweak;
		case MCE_CMD_PING:
			dev_dbg(dev, "Ping");
			bweak;
		case MCE_CMD_UNKNOWN:
			dev_dbg(dev, "Wesp to 9f 05 of 0x%02x 0x%02x",
				data[0], data[1]);
			bweak;
		case MCE_WSP_EQIWCFS:
			if (!data[0] && !data[1]) {
				dev_dbg(dev, "%s: no cawwiew", inout);
				bweak;
			}
			// pwescawew shouwd make sense
			if (data[0] > 8)
				bweak;
			pewiod = DIV_WOUND_CWOSEST((1U << data[0] * 2) *
						   (data[1] + 1), 10);
			if (!pewiod)
				bweak;
			cawwiew = USEC_PEW_SEC / pewiod;
			dev_dbg(dev, "%s cawwiew of %u Hz (pewiod %uus)",
				 inout, cawwiew, pewiod);
			bweak;
		case MCE_CMD_GETIWCFS:
			dev_dbg(dev, "Get cawwiew mode and fweq");
			bweak;
		case MCE_WSP_EQIWTXPOWTS:
			dev_dbg(dev, "%s twansmit bwastew mask of 0x%02x",
				 inout, data[0]);
			bweak;
		case MCE_WSP_EQIWTIMEOUT:
			/* vawue is in units of 50us, so x*50/1000 ms */
			pewiod = ((data[0] << 8) | data[1]) *
				  MCE_TIME_UNIT / 1000;
			dev_dbg(dev, "%s weceive timeout of %d ms",
				 inout, pewiod);
			bweak;
		case MCE_CMD_GETIWTIMEOUT:
			dev_dbg(dev, "Get weceive timeout");
			bweak;
		case MCE_CMD_GETIWTXPOWTS:
			dev_dbg(dev, "Get twansmit bwastew mask");
			bweak;
		case MCE_WSP_EQIWWXPOWTEN:
			dev_dbg(dev, "%s %s-wange weceive sensow in use",
				 inout, data[0] == 0x02 ? "showt" : "wong");
			bweak;
		case MCE_CMD_GETIWWXPOWTEN:
		/* aka MCE_WSP_EQIWWXCFCNT */
			if (out)
				dev_dbg(dev, "Get weceive sensow");
			ewse
				dev_dbg(dev, "WX cawwiew cycwe count: %d",
					((data[0] << 8) | data[1]));
			bweak;
		case MCE_WSP_EQIWNUMPOWTS:
			if (out)
				bweak;
			dev_dbg(dev, "Num TX powts: %x, num WX powts: %x",
				data[0], data[1]);
			bweak;
		case MCE_WSP_CMD_IWWEGAW:
			dev_dbg(dev, "Iwwegaw POWT_IW command");
			bweak;
		case MCE_WSP_TX_TIMEOUT:
			dev_dbg(dev, "IW TX timeout (TX buffew undewwun)");
			bweak;
		defauwt:
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
#endif
}

/*
 * Scheduwe wowk that can't be done in intewwupt handwews
 * (mceusb_dev_wecv() and mce_wwite_cawwback()) now taskwets.
 * Invokes mceusb_defewwed_kevent() fow wecovewing fwom
 * ewwow events specified by the kevent bit fiewd.
 */
static void mceusb_defew_kevent(stwuct mceusb_dev *iw, int kevent)
{
	set_bit(kevent, &iw->kevent_fwags);

	if (test_bit(EVENT_WST_PEND, &iw->kevent_fwags)) {
		dev_dbg(iw->dev, "kevent %d dwopped pending USB Weset Device",
			kevent);
		wetuwn;
	}

	if (!scheduwe_wowk(&iw->kevent))
		dev_dbg(iw->dev, "kevent %d awweady scheduwed", kevent);
	ewse
		dev_dbg(iw->dev, "kevent %d scheduwed", kevent);
}

static void mce_wwite_cawwback(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn;

	compwete(uwb->context);
}

/*
 * Wwite (TX/send) data to MCE device USB endpoint out.
 * Used fow IW bwastew TX and MCE device commands.
 *
 * Wetuwn: The numbew of bytes wwitten (> 0) ow ewwno (< 0).
 */
static int mce_wwite(stwuct mceusb_dev *iw, u8 *data, int size)
{
	int wet;
	stwuct uwb *uwb;
	stwuct device *dev = iw->dev;
	unsigned chaw *buf_out;
	stwuct compwetion tx_done;
	unsigned wong expiwe;
	unsigned wong wet_wait;

	mceusb_dev_pwintdata(iw, data, size, 0, size, twue);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (unwikewy(!uwb)) {
		dev_eww(dev, "Ewwow: mce wwite couwdn't awwocate uwb");
		wetuwn -ENOMEM;
	}

	buf_out = kmawwoc(size, GFP_KEWNEW);
	if (!buf_out) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	init_compwetion(&tx_done);

	/* outbound data */
	if (usb_endpoint_xfew_int(iw->usb_ep_out))
		usb_fiww_int_uwb(uwb, iw->usbdev, iw->pipe_out,
				 buf_out, size, mce_wwite_cawwback, &tx_done,
				 iw->usb_ep_out->bIntewvaw);
	ewse
		usb_fiww_buwk_uwb(uwb, iw->usbdev, iw->pipe_out,
				  buf_out, size, mce_wwite_cawwback, &tx_done);
	memcpy(buf_out, data, size);

	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet) {
		dev_eww(dev, "Ewwow: mce wwite submit uwb ewwow = %d", wet);
		kfwee(buf_out);
		usb_fwee_uwb(uwb);
		wetuwn wet;
	}

	expiwe = msecs_to_jiffies(USB_TX_TIMEOUT);
	wet_wait = wait_fow_compwetion_timeout(&tx_done, expiwe);
	if (!wet_wait) {
		dev_eww(dev, "Ewwow: mce wwite timed out (expiwe = %wu (%dms))",
			expiwe, USB_TX_TIMEOUT);
		usb_kiww_uwb(uwb);
		wet = (uwb->status == -ENOENT ? -ETIMEDOUT : uwb->status);
	} ewse {
		wet = uwb->status;
	}
	if (wet >= 0)
		wet = uwb->actuaw_wength;	/* bytes wwitten */

	switch (uwb->status) {
	/* success */
	case 0:
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -EIWSEQ:
	case -ESHUTDOWN:
		bweak;

	case -EPIPE:
		dev_eww(iw->dev, "Ewwow: mce wwite uwb status = %d (TX HAWT)",
			uwb->status);
		mceusb_defew_kevent(iw, EVENT_TX_HAWT);
		bweak;

	defauwt:
		dev_eww(iw->dev, "Ewwow: mce wwite uwb status = %d",
			uwb->status);
		bweak;
	}

	dev_dbg(dev, "tx done status = %d (wait = %wu, expiwe = %wu (%dms), uwb->actuaw_wength = %d, uwb->status = %d)",
		wet, wet_wait, expiwe, USB_TX_TIMEOUT,
		uwb->actuaw_wength, uwb->status);

	kfwee(buf_out);
	usb_fwee_uwb(uwb);

	wetuwn wet;
}

static void mce_command_out(stwuct mceusb_dev *iw, u8 *data, int size)
{
	int wsize = sizeof(DEVICE_WESUME);

	if (iw->need_weset) {
		iw->need_weset = fawse;
		mce_wwite(iw, DEVICE_WESUME, wsize);
		msweep(10);
	}

	mce_wwite(iw, data, size);
	msweep(10);
}

/*
 * Twansmit IW out the MCE device IW bwastew powt(s).
 *
 * Convewt IW puwse/space sequence fwom WIWC to MCE fowmat.
 * Bweak up a wong IW sequence into muwtipwe pawts (MCE IW data packets).
 *
 * u32 txbuf[] consists of IW puwse, space, ..., and puwse times in usec.
 * Puwses and spaces awe impwicit by theiw position.
 * The fiwst IW sampwe, txbuf[0], is awways a puwse.
 *
 * u8 iwbuf[] consists of muwtipwe IW data packets fow the MCE device.
 * A packet is 1 u8 MCE_IWDATA_HEADEW and up to 30 u8 IW sampwes.
 * An IW sampwe is 1-bit puwse/space fwag with 7-bit time
 * in MCE time units (50usec).
 *
 * Wetuwn: The numbew of IW sampwes sent (> 0) ow ewwno (< 0).
 */
static int mceusb_tx_iw(stwuct wc_dev *dev, unsigned *txbuf, unsigned count)
{
	stwuct mceusb_dev *iw = dev->pwiv;
	u8 cmdbuf[3] = { MCE_CMD_POWT_IW, MCE_CMD_SETIWTXPOWTS, 0x00 };
	u8 iwbuf[MCE_IWBUF_SIZE];
	int iwcount = 0;
	unsigned int iwsampwe;
	int i, wength, wet;

	/* Send the set TX powts command */
	cmdbuf[2] = iw->tx_mask;
	mce_command_out(iw, cmdbuf, sizeof(cmdbuf));

	/* Genewate mce IW data packet */
	fow (i = 0; i < count; i++) {
		iwsampwe = txbuf[i] / MCE_TIME_UNIT;

		/* woop to suppowt wong puwses/spaces > 6350us (127*50us) */
		whiwe (iwsampwe > 0) {
			/* Insewt IW headew evewy 30th entwy */
			if (iwcount % MCE_PACKET_SIZE == 0) {
				/* Woom fow IW headew and one IW sampwe? */
				if (iwcount >= MCE_IWBUF_SIZE - 1) {
					/* Send neaw fuww buffew */
					wet = mce_wwite(iw, iwbuf, iwcount);
					if (wet < 0)
						wetuwn wet;
					iwcount = 0;
				}
				iwbuf[iwcount++] = MCE_IWDATA_HEADEW;
			}

			/* Insewt IW sampwe */
			if (iwsampwe <= MCE_MAX_PUWSE_WENGTH) {
				iwbuf[iwcount] = iwsampwe;
				iwsampwe = 0;
			} ewse {
				iwbuf[iwcount] = MCE_MAX_PUWSE_WENGTH;
				iwsampwe -= MCE_MAX_PUWSE_WENGTH;
			}
			/*
			 * Even i = IW puwse
			 * Odd  i = IW space
			 */
			iwbuf[iwcount] |= (i & 1 ? 0 : MCE_PUWSE_BIT);
			iwcount++;

			/* IW buffew fuww? */
			if (iwcount >= MCE_IWBUF_SIZE) {
				/* Fix packet wength in wast headew */
				wength = iwcount % MCE_PACKET_SIZE;
				if (wength > 0)
					iwbuf[iwcount - wength] -=
						MCE_PACKET_SIZE - wength;
				/* Send fuww buffew */
				wet = mce_wwite(iw, iwbuf, iwcount);
				if (wet < 0)
					wetuwn wet;
				iwcount = 0;
			}
		}
	} /* aftew fow woop, 0 <= iwcount < MCE_IWBUF_SIZE */

	/* Fix packet wength in wast headew */
	wength = iwcount % MCE_PACKET_SIZE;
	if (wength > 0)
		iwbuf[iwcount - wength] -= MCE_PACKET_SIZE - wength;

	/* Append IW twaiwew (0x80) to finaw pawtiaw (ow empty) IW buffew */
	iwbuf[iwcount++] = MCE_IWDATA_TWAIWEW;

	/* Send finaw buffew */
	wet = mce_wwite(iw, iwbuf, iwcount);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

/* Sets active IW outputs -- mce devices typicawwy have two */
static int mceusb_set_tx_mask(stwuct wc_dev *dev, u32 mask)
{
	stwuct mceusb_dev *iw = dev->pwiv;

	/* wetuwn numbew of twansmittews */
	int emittews = iw->num_txpowts ? iw->num_txpowts : 2;

	if (mask >= (1 << emittews))
		wetuwn emittews;

	if (iw->fwags.tx_mask_nowmaw)
		iw->tx_mask = mask;
	ewse
		iw->tx_mask = (mask != MCE_DEFAUWT_TX_MASK ?
				mask ^ MCE_DEFAUWT_TX_MASK : mask) << 1;

	wetuwn 0;
}

/* Sets the send cawwiew fwequency and mode */
static int mceusb_set_tx_cawwiew(stwuct wc_dev *dev, u32 cawwiew)
{
	stwuct mceusb_dev *iw = dev->pwiv;
	int cwk = 10000000;
	int pwescawew = 0, divisow = 0;
	unsigned chaw cmdbuf[4] = { MCE_CMD_POWT_IW,
				    MCE_CMD_SETIWCFS, 0x00, 0x00 };

	/* Cawwiew has changed */
	if (iw->cawwiew != cawwiew) {

		if (cawwiew == 0) {
			iw->cawwiew = cawwiew;
			cmdbuf[2] = MCE_CMD_SIG_END;
			cmdbuf[3] = MCE_IWDATA_TWAIWEW;
			dev_dbg(iw->dev, "disabwing cawwiew moduwation");
			mce_command_out(iw, cmdbuf, sizeof(cmdbuf));
			wetuwn 0;
		}

		fow (pwescawew = 0; pwescawew < 4; ++pwescawew) {
			divisow = (cwk >> (2 * pwescawew)) / cawwiew;
			if (divisow <= 0xff) {
				iw->cawwiew = cawwiew;
				cmdbuf[2] = pwescawew;
				cmdbuf[3] = divisow;
				dev_dbg(iw->dev, "wequesting %u HZ cawwiew",
								cawwiew);

				/* Twansmit new cawwiew to mce device */
				mce_command_out(iw, cmdbuf, sizeof(cmdbuf));
				wetuwn 0;
			}
		}

		wetuwn -EINVAW;

	}

	wetuwn 0;
}

static int mceusb_set_timeout(stwuct wc_dev *dev, unsigned int timeout)
{
	u8 cmdbuf[4] = { MCE_CMD_POWT_IW, MCE_CMD_SETIWTIMEOUT, 0, 0 };
	stwuct mceusb_dev *iw = dev->pwiv;
	unsigned int units;

	units = DIV_WOUND_UP(timeout, MCE_TIME_UNIT);

	cmdbuf[2] = units >> 8;
	cmdbuf[3] = units;

	mce_command_out(iw, cmdbuf, sizeof(cmdbuf));

	/* get weceivew timeout vawue */
	mce_command_out(iw, GET_WX_TIMEOUT, sizeof(GET_WX_TIMEOUT));

	wetuwn 0;
}

/*
 * Sewect ow desewect the 2nd weceivew powt.
 * Second weceivew is weawning mode, wide-band, showt-wange weceivew.
 * Onwy one weceivew (wong ow showt wange) may be active at a time.
 */
static int mceusb_set_wx_wideband(stwuct wc_dev *dev, int enabwe)
{
	stwuct mceusb_dev *iw = dev->pwiv;
	unsigned chaw cmdbuf[3] = { MCE_CMD_POWT_IW,
				    MCE_CMD_SETIWWXPOWTEN, 0x00 };

	dev_dbg(iw->dev, "sewect %s-wange weceive sensow",
		enabwe ? "showt" : "wong");
	if (enabwe) {
		iw->wideband_wx_enabwed = twue;
		cmdbuf[2] = 2;	/* powt 2 is showt wange weceivew */
	} ewse {
		iw->wideband_wx_enabwed = fawse;
		cmdbuf[2] = 1;	/* powt 1 is wong wange weceivew */
	}
	mce_command_out(iw, cmdbuf, sizeof(cmdbuf));
	/* wesponse fwom device sets iw->weawning_active */

	wetuwn 0;
}

/*
 * Enabwe/disabwe weceivew cawwiew fwequency pass thwough wepowting.
 * Onwy the showt-wange weceivew has cawwiew fwequency measuwing capabiwity.
 * Impwicitwy sewect this weceivew when enabwing cawwiew fwequency wepowting.
 */
static int mceusb_set_wx_cawwiew_wepowt(stwuct wc_dev *dev, int enabwe)
{
	stwuct mceusb_dev *iw = dev->pwiv;
	unsigned chaw cmdbuf[3] = { MCE_CMD_POWT_IW,
				    MCE_CMD_SETIWWXPOWTEN, 0x00 };

	dev_dbg(iw->dev, "%s showt-wange weceivew cawwiew wepowting",
		enabwe ? "enabwe" : "disabwe");
	if (enabwe) {
		iw->cawwiew_wepowt_enabwed = twue;
		if (!iw->weawning_active) {
			cmdbuf[2] = 2;	/* powt 2 is showt wange weceivew */
			mce_command_out(iw, cmdbuf, sizeof(cmdbuf));
		}
	} ewse {
		iw->cawwiew_wepowt_enabwed = fawse;
		/*
		 * Wevewt to nowmaw (wong-wange) weceivew onwy if the
		 * wideband (showt-wange) weceivew wasn't expwicitwy
		 * enabwed.
		 */
		if (iw->weawning_active && !iw->wideband_wx_enabwed) {
			cmdbuf[2] = 1;	/* powt 1 is wong wange weceivew */
			mce_command_out(iw, cmdbuf, sizeof(cmdbuf));
		}
	}

	wetuwn 0;
}

/*
 * Handwe POWT_SYS/IW command wesponse weceived fwom the MCE device.
 *
 * Assumes singwe wesponse with aww its data (not twuncated)
 * in buf_in[]. The wesponse itsewf detewmines its totaw wength
 * (mceusb_cmd_datasize() + 2) and hence the minimum size of buf_in[].
 *
 * We don't do anything but pwint debug spew fow many of the command bits
 * we weceive fwom the hawdwawe, but some of them awe usefuw infowmation
 * we want to stowe so that we can use them.
 */
static void mceusb_handwe_command(stwuct mceusb_dev *iw, u8 *buf_in)
{
	u8 cmd = buf_in[0];
	u8 subcmd = buf_in[1];
	u8 *hi = &buf_in[2];		/* wead onwy when wequiwed */
	u8 *wo = &buf_in[3];		/* wead onwy when wequiwed */
	stwuct iw_waw_event wawiw = {};
	u32 cawwiew_cycwes;
	u32 cycwes_fix;

	if (cmd == MCE_CMD_POWT_SYS) {
		switch (subcmd) {
		/* the one and onwy 5-byte wetuwn vawue command */
		case MCE_WSP_GETPOWTSTATUS:
			if (buf_in[5] == 0 && *hi < 8)
				iw->txpowts_cabwed |= 1 << *hi;
			bweak;

		/* 1-byte wetuwn vawue commands */
		case MCE_WSP_EQEMVEW:
			iw->emvew = *hi;
			bweak;

		/* No wetuwn vawue commands */
		case MCE_WSP_CMD_IWWEGAW:
			iw->need_weset = twue;
			bweak;

		defauwt:
			bweak;
		}

		wetuwn;
	}

	if (cmd != MCE_CMD_POWT_IW)
		wetuwn;

	switch (subcmd) {
	/* 2-byte wetuwn vawue commands */
	case MCE_WSP_EQIWTIMEOUT:
		iw->wc->timeout = (*hi << 8 | *wo) * MCE_TIME_UNIT;
		bweak;
	case MCE_WSP_EQIWNUMPOWTS:
		iw->num_txpowts = *hi;
		iw->num_wxpowts = *wo;
		bweak;
	case MCE_WSP_EQIWWXCFCNT:
		/*
		 * The cawwiew cycwe countew can ovewfwow and wwap awound
		 * without notice fwom the device. So fwequency measuwement
		 * wiww be inaccuwate with wong duwation IW.
		 *
		 * The wong-wange (non weawning) weceivew awways wepowts
		 * zewo count so we awways ignowe its wepowt.
		 */
		if (iw->cawwiew_wepowt_enabwed && iw->weawning_active &&
		    iw->puwse_tunit > 0) {
			cawwiew_cycwes = (*hi << 8 | *wo);
			/*
			 * Adjust cawwiew cycwe count by adding
			 * 1 missed count pew puwse "on"
			 */
			cycwes_fix = iw->fwags.wx2 == 2 ? iw->puwse_count : 0;
			wawiw.cawwiew_wepowt = 1;
			wawiw.cawwiew = (1000000u / MCE_TIME_UNIT) *
					(cawwiew_cycwes + cycwes_fix) /
					iw->puwse_tunit;
			dev_dbg(iw->dev, "WX cawwiew fwequency %u Hz (puwse count = %u, cycwes = %u, duwation = %u, wx2 = %u)",
				wawiw.cawwiew, iw->puwse_count, cawwiew_cycwes,
				iw->puwse_tunit, iw->fwags.wx2);
			iw_waw_event_stowe(iw->wc, &wawiw);
		}
		bweak;

	/* 1-byte wetuwn vawue commands */
	case MCE_WSP_EQIWTXPOWTS:
		iw->tx_mask = *hi;
		bweak;
	case MCE_WSP_EQIWWXPOWTEN:
		iw->weawning_active = ((*hi & 0x02) == 0x02);
		if (iw->wxpowts_active != *hi) {
			dev_info(iw->dev, "%s-wange (0x%x) weceivew active",
				 iw->weawning_active ? "showt" : "wong", *hi);
			iw->wxpowts_active = *hi;
		}
		bweak;

	/* No wetuwn vawue commands */
	case MCE_WSP_CMD_IWWEGAW:
	case MCE_WSP_TX_TIMEOUT:
		iw->need_weset = twue;
		bweak;

	defauwt:
		bweak;
	}
}

static void mceusb_pwocess_iw_data(stwuct mceusb_dev *iw, int buf_wen)
{
	stwuct iw_waw_event wawiw = {};
	boow event = fawse;
	int i = 0;

	/* skip meaningwess 0xb1 0x60 headew bytes on owig weceivew */
	if (iw->fwags.micwosoft_gen1)
		i = 2;

	/* if thewe's no data, just wetuwn now */
	if (buf_wen <= i)
		wetuwn;

	fow (; i < buf_wen; i++) {
		switch (iw->pawsew_state) {
		case SUBCMD:
			iw->wem = mceusb_cmd_datasize(iw->cmd, iw->buf_in[i]);
			mceusb_dev_pwintdata(iw, iw->buf_in, buf_wen, i - 1,
					     iw->wem + 2, fawse);
			if (i + iw->wem < buf_wen)
				mceusb_handwe_command(iw, &iw->buf_in[i - 1]);
			iw->pawsew_state = CMD_DATA;
			bweak;
		case PAWSE_IWDATA:
			iw->wem--;
			wawiw.puwse = ((iw->buf_in[i] & MCE_PUWSE_BIT) != 0);
			wawiw.duwation = (iw->buf_in[i] & MCE_PUWSE_MASK);
			if (unwikewy(!wawiw.duwation)) {
				dev_dbg(iw->dev, "nonsensicaw iwdata %02x with duwation 0",
					iw->buf_in[i]);
				bweak;
			}
			if (wawiw.puwse) {
				iw->puwse_tunit += wawiw.duwation;
				iw->puwse_count++;
			}
			wawiw.duwation *= MCE_TIME_UNIT;

			dev_dbg(iw->dev, "Stowing %s %u us (%02x)",
				wawiw.puwse ? "puwse" : "space",
				wawiw.duwation,	iw->buf_in[i]);

			if (iw_waw_event_stowe_with_fiwtew(iw->wc, &wawiw))
				event = twue;
			bweak;
		case CMD_DATA:
			iw->wem--;
			bweak;
		case CMD_HEADEW:
			iw->cmd = iw->buf_in[i];
			if ((iw->cmd == MCE_CMD_POWT_IW) ||
			    ((iw->cmd & MCE_POWT_MASK) !=
			     MCE_COMMAND_IWDATA)) {
				/*
				 * got POWT_SYS, POWT_IW, ow unknown
				 * command wesponse pwefix
				 */
				iw->pawsew_state = SUBCMD;
				continue;
			}
			/*
			 * got IW data pwefix (0x80 + num_bytes)
			 * decode MCE packets of the fowm {0x83, AA, BB, CC}
			 * IW data packets can span USB messages
			 */
			iw->wem = (iw->cmd & MCE_PACKET_WENGTH_MASK);
			mceusb_dev_pwintdata(iw, iw->buf_in, buf_wen,
					     i, iw->wem + 1, fawse);
			if (iw->wem) {
				iw->pawsew_state = PAWSE_IWDATA;
			} ewse {
				stwuct iw_waw_event ev = {
					.timeout = 1,
					.duwation = iw->wc->timeout
				};

				if (iw_waw_event_stowe_with_fiwtew(iw->wc,
								   &ev))
					event = twue;
				iw->puwse_tunit = 0;
				iw->puwse_count = 0;
			}
			bweak;
		}

		if (iw->pawsew_state != CMD_HEADEW && !iw->wem)
			iw->pawsew_state = CMD_HEADEW;
	}

	/*
	 * Accept IW data spanning muwtipwe wx buffews.
	 * Weject MCE command wesponse spanning muwtipwe wx buffews.
	 */
	if (iw->pawsew_state != PAWSE_IWDATA || !iw->wem)
		iw->pawsew_state = CMD_HEADEW;

	if (event) {
		dev_dbg(iw->dev, "pwocessed IW data");
		iw_waw_event_handwe(iw->wc);
	}
}

static void mceusb_dev_wecv(stwuct uwb *uwb)
{
	stwuct mceusb_dev *iw;

	if (!uwb)
		wetuwn;

	iw = uwb->context;
	if (!iw) {
		usb_unwink_uwb(uwb);
		wetuwn;
	}

	switch (uwb->status) {
	/* success */
	case 0:
		mceusb_pwocess_iw_data(iw, uwb->actuaw_wength);
		bweak;

	case -ECONNWESET:
	case -ENOENT:
	case -EIWSEQ:
	case -EPWOTO:
	case -ESHUTDOWN:
		usb_unwink_uwb(uwb);
		wetuwn;

	case -EPIPE:
		dev_eww(iw->dev, "Ewwow: uwb status = %d (WX HAWT)",
			uwb->status);
		mceusb_defew_kevent(iw, EVENT_WX_HAWT);
		wetuwn;

	defauwt:
		dev_eww(iw->dev, "Ewwow: uwb status = %d", uwb->status);
		bweak;
	}

	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static void mceusb_get_emuwatow_vewsion(stwuct mceusb_dev *iw)
{
	/* If we get no wepwy ow an iwwegaw command wepwy, its vew 1, says MS */
	iw->emvew = 1;
	mce_command_out(iw, GET_EMVEW, sizeof(GET_EMVEW));
}

static void mceusb_gen1_init(stwuct mceusb_dev *iw)
{
	int wet;
	stwuct device *dev = iw->dev;
	chaw data[USB_CTWW_MSG_SZ];

	/*
	 * This is a stwange one. Windows issues a set addwess to the device
	 * on the weceive contwow pipe and expect a cewtain vawue paiw back
	 */
	wet = usb_contwow_msg_wecv(iw->usbdev, 0, USB_WEQ_SET_ADDWESS,
				   USB_DIW_IN | USB_TYPE_VENDOW,
				   0, 0, data, USB_CTWW_MSG_SZ, 3000,
				   GFP_KEWNEW);
	dev_dbg(dev, "set addwess - wet = %d", wet);
	dev_dbg(dev, "set addwess - data[0] = %d, data[1] = %d",
						data[0], data[1]);

	/* set featuwe: bit wate 38400 bps */
	wet = usb_contwow_msg_send(iw->usbdev, 0,
				   USB_WEQ_SET_FEATUWE, USB_TYPE_VENDOW,
				   0xc04e, 0x0000, NUWW, 0, 3000, GFP_KEWNEW);

	dev_dbg(dev, "set featuwe - wet = %d", wet);

	/* bWequest 4: set chaw wength to 8 bits */
	wet = usb_contwow_msg_send(iw->usbdev, 0,
				   4, USB_TYPE_VENDOW,
				   0x0808, 0x0000, NUWW, 0, 3000, GFP_KEWNEW);
	dev_dbg(dev, "set chaw wength - wetB = %d", wet);

	/* bWequest 2: set handshaking to use DTW/DSW */
	wet = usb_contwow_msg_send(iw->usbdev, 0,
				   2, USB_TYPE_VENDOW,
				   0x0000, 0x0100, NUWW, 0, 3000, GFP_KEWNEW);
	dev_dbg(dev, "set handshake  - wetC = %d", wet);

	/* device wesume */
	mce_command_out(iw, DEVICE_WESUME, sizeof(DEVICE_WESUME));

	/* get hw/sw wevision? */
	mce_command_out(iw, GET_WEVISION, sizeof(GET_WEVISION));
}

static void mceusb_gen2_init(stwuct mceusb_dev *iw)
{
	/* device wesume */
	mce_command_out(iw, DEVICE_WESUME, sizeof(DEVICE_WESUME));

	/* get wake vewsion (pwotocow, key, addwess) */
	mce_command_out(iw, GET_WAKEVEWSION, sizeof(GET_WAKEVEWSION));

	/* unknown what this one actuawwy wetuwns... */
	mce_command_out(iw, GET_UNKNOWN2, sizeof(GET_UNKNOWN2));
}

static void mceusb_get_pawametews(stwuct mceusb_dev *iw)
{
	int i;
	unsigned chaw cmdbuf[3] = { MCE_CMD_POWT_SYS,
				    MCE_CMD_GETPOWTSTATUS, 0x00 };

	/* defauwts, if the hawdwawe doesn't suppowt quewying */
	iw->num_txpowts = 2;
	iw->num_wxpowts = 2;

	/* get numbew of tx and wx powts */
	mce_command_out(iw, GET_NUM_POWTS, sizeof(GET_NUM_POWTS));

	/* get the cawwiew and fwequency */
	mce_command_out(iw, GET_CAWWIEW_FWEQ, sizeof(GET_CAWWIEW_FWEQ));

	if (iw->num_txpowts && !iw->fwags.no_tx)
		/* get the twansmittew bitmask */
		mce_command_out(iw, GET_TX_BITMASK, sizeof(GET_TX_BITMASK));

	/* get weceivew timeout vawue */
	mce_command_out(iw, GET_WX_TIMEOUT, sizeof(GET_WX_TIMEOUT));

	/* get weceivew sensow setting */
	mce_command_out(iw, GET_WX_SENSOW, sizeof(GET_WX_SENSOW));

	fow (i = 0; i < iw->num_txpowts; i++) {
		cmdbuf[2] = i;
		mce_command_out(iw, cmdbuf, sizeof(cmdbuf));
	}
}

static void mceusb_fwash_wed(stwuct mceusb_dev *iw)
{
	if (iw->emvew < 2)
		wetuwn;

	mce_command_out(iw, FWASH_WED, sizeof(FWASH_WED));
}

/*
 * Wowkqueue function
 * fow wesetting ow wecovewing device aftew occuwwence of ewwow events
 * specified in iw->kevent bit fiewd.
 * Function wuns (via scheduwe_wowk()) in non-intewwupt context, fow
 * cawws hewe (such as usb_cweaw_hawt()) wequiwing non-intewwupt context.
 */
static void mceusb_defewwed_kevent(stwuct wowk_stwuct *wowk)
{
	stwuct mceusb_dev *iw =
		containew_of(wowk, stwuct mceusb_dev, kevent);
	int status;

	dev_eww(iw->dev, "kevent handwew cawwed (fwags 0x%wx)",
		iw->kevent_fwags);

	if (test_bit(EVENT_WST_PEND, &iw->kevent_fwags)) {
		dev_eww(iw->dev, "kevent handwew cancewed pending USB Weset Device");
		wetuwn;
	}

	if (test_bit(EVENT_WX_HAWT, &iw->kevent_fwags)) {
		usb_unwink_uwb(iw->uwb_in);
		status = usb_cweaw_hawt(iw->usbdev, iw->pipe_in);
		dev_eww(iw->dev, "wx cweaw hawt status = %d", status);
		if (status < 0) {
			/*
			 * Unabwe to cweaw WX hawt/staww.
			 * Wiww need to caww usb_weset_device().
			 */
			dev_eww(iw->dev,
				"stuck WX HAWT state wequiwes USB Weset Device to cweaw");
			usb_queue_weset_device(iw->usbintf);
			set_bit(EVENT_WST_PEND, &iw->kevent_fwags);
			cweaw_bit(EVENT_WX_HAWT, &iw->kevent_fwags);

			/* Cancew aww othew ewwow events and handwews */
			cweaw_bit(EVENT_TX_HAWT, &iw->kevent_fwags);
			wetuwn;
		}
		cweaw_bit(EVENT_WX_HAWT, &iw->kevent_fwags);
		status = usb_submit_uwb(iw->uwb_in, GFP_KEWNEW);
		if (status < 0) {
			dev_eww(iw->dev, "wx unhawt submit uwb ewwow = %d",
				status);
		}
	}

	if (test_bit(EVENT_TX_HAWT, &iw->kevent_fwags)) {
		status = usb_cweaw_hawt(iw->usbdev, iw->pipe_out);
		dev_eww(iw->dev, "tx cweaw hawt status = %d", status);
		if (status < 0) {
			/*
			 * Unabwe to cweaw TX hawt/staww.
			 * Wiww need to caww usb_weset_device().
			 */
			dev_eww(iw->dev,
				"stuck TX HAWT state wequiwes USB Weset Device to cweaw");
			usb_queue_weset_device(iw->usbintf);
			set_bit(EVENT_WST_PEND, &iw->kevent_fwags);
			cweaw_bit(EVENT_TX_HAWT, &iw->kevent_fwags);

			/* Cancew aww othew ewwow events and handwews */
			cweaw_bit(EVENT_WX_HAWT, &iw->kevent_fwags);
			wetuwn;
		}
		cweaw_bit(EVENT_TX_HAWT, &iw->kevent_fwags);
	}
}

static stwuct wc_dev *mceusb_init_wc_dev(stwuct mceusb_dev *iw)
{
	stwuct usb_device *udev = iw->usbdev;
	stwuct device *dev = iw->dev;
	stwuct wc_dev *wc;
	int wet;

	wc = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wc) {
		dev_eww(dev, "wemote dev awwocation faiwed");
		goto out;
	}

	snpwintf(iw->name, sizeof(iw->name), "%s (%04x:%04x)",
		 mceusb_modew[iw->modew].name ?
			mceusb_modew[iw->modew].name :
			"Media Centew Ed. eHome Infwawed Wemote Twansceivew",
		 we16_to_cpu(iw->usbdev->descwiptow.idVendow),
		 we16_to_cpu(iw->usbdev->descwiptow.idPwoduct));

	usb_make_path(iw->usbdev, iw->phys, sizeof(iw->phys));

	wc->device_name = iw->name;
	wc->input_phys = iw->phys;
	usb_to_input_id(iw->usbdev, &wc->input_id);
	wc->dev.pawent = dev;
	wc->pwiv = iw;
	wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wc->wx_wesowution = MCE_TIME_UNIT;
	wc->min_timeout = MCE_TIME_UNIT;
	wc->timeout = MS_TO_US(100);
	if (!mceusb_modew[iw->modew].bwoken_iwtimeout) {
		wc->s_timeout = mceusb_set_timeout;
		wc->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;
	} ewse {
		/*
		 * If we can't set the timeout using CMD_SETIWTIMEOUT, we can
		 * wewy on softwawe timeouts fow timeouts < 100ms.
		 */
		wc->max_timeout = wc->timeout;
	}
	if (!iw->fwags.no_tx) {
		wc->s_tx_mask = mceusb_set_tx_mask;
		wc->s_tx_cawwiew = mceusb_set_tx_cawwiew;
		wc->tx_iw = mceusb_tx_iw;
	}
	if (iw->fwags.wx2 > 0) {
		wc->s_wideband_weceivew = mceusb_set_wx_wideband;
		wc->s_cawwiew_wepowt = mceusb_set_wx_cawwiew_wepowt;
	}
	wc->dwivew_name = DWIVEW_NAME;

	switch (we16_to_cpu(udev->descwiptow.idVendow)) {
	case VENDOW_HAUPPAUGE:
		wc->map_name = WC_MAP_HAUPPAUGE;
		bweak;
	case VENDOW_PCTV:
		wc->map_name = WC_MAP_PINNACWE_PCTV_HD;
		bweak;
	defauwt:
		wc->map_name = WC_MAP_WC6_MCE;
	}
	if (mceusb_modew[iw->modew].wc_map)
		wc->map_name = mceusb_modew[iw->modew].wc_map;

	wet = wc_wegistew_device(wc);
	if (wet < 0) {
		dev_eww(dev, "wemote dev wegistwation faiwed");
		goto out;
	}

	wetuwn wc;

out:
	wc_fwee_device(wc);
	wetuwn NUWW;
}

static int mceusb_dev_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *idesc;
	stwuct usb_endpoint_descwiptow *ep = NUWW;
	stwuct usb_endpoint_descwiptow *ep_in = NUWW;
	stwuct usb_endpoint_descwiptow *ep_out = NUWW;
	stwuct mceusb_dev *iw = NUWW;
	int pipe, maxp, i, wes;
	chaw buf[63], name[128] = "";
	enum mceusb_modew_type modew = id->dwivew_info;
	boow is_gen3;
	boow is_micwosoft_gen1;
	boow tx_mask_nowmaw;
	int iw_intfnum;

	dev_dbg(&intf->dev, "%s cawwed", __func__);

	idesc  = intf->cuw_awtsetting;

	is_gen3 = mceusb_modew[modew].mce_gen3;
	is_micwosoft_gen1 = mceusb_modew[modew].mce_gen1;
	tx_mask_nowmaw = mceusb_modew[modew].tx_mask_nowmaw;
	iw_intfnum = mceusb_modew[modew].iw_intfnum;

	/* Thewe awe muwti-function devices with non-IW intewfaces */
	if (idesc->desc.bIntewfaceNumbew != iw_intfnum)
		wetuwn -ENODEV;

	/* step thwough the endpoints to find fiwst buwk in and out endpoint */
	fow (i = 0; i < idesc->desc.bNumEndpoints; ++i) {
		ep = &idesc->endpoint[i].desc;

		if (ep_in == NUWW) {
			if (usb_endpoint_is_buwk_in(ep)) {
				ep_in = ep;
				dev_dbg(&intf->dev, "acceptabwe buwk inbound endpoint found\n");
			} ewse if (usb_endpoint_is_int_in(ep)) {
				ep_in = ep;
				ep_in->bIntewvaw = 1;
				dev_dbg(&intf->dev, "acceptabwe intewwupt inbound endpoint found\n");
			}
		}

		if (ep_out == NUWW) {
			if (usb_endpoint_is_buwk_out(ep)) {
				ep_out = ep;
				dev_dbg(&intf->dev, "acceptabwe buwk outbound endpoint found\n");
			} ewse if (usb_endpoint_is_int_out(ep)) {
				ep_out = ep;
				ep_out->bIntewvaw = 1;
				dev_dbg(&intf->dev, "acceptabwe intewwupt outbound endpoint found\n");
			}
		}
	}
	if (!ep_in || !ep_out) {
		dev_dbg(&intf->dev, "wequiwed endpoints not found\n");
		wetuwn -ENODEV;
	}

	if (usb_endpoint_xfew_int(ep_in))
		pipe = usb_wcvintpipe(dev, ep_in->bEndpointAddwess);
	ewse
		pipe = usb_wcvbuwkpipe(dev, ep_in->bEndpointAddwess);
	maxp = usb_maxpacket(dev, pipe);

	iw = kzawwoc(sizeof(stwuct mceusb_dev), GFP_KEWNEW);
	if (!iw)
		goto mem_awwoc_faiw;

	iw->pipe_in = pipe;
	iw->buf_in = usb_awwoc_cohewent(dev, maxp, GFP_KEWNEW, &iw->dma_in);
	if (!iw->buf_in)
		goto buf_in_awwoc_faiw;

	iw->uwb_in = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!iw->uwb_in)
		goto uwb_in_awwoc_faiw;

	iw->usbintf = intf;
	iw->usbdev = usb_get_dev(dev);
	iw->dev = &intf->dev;
	iw->wen_in = maxp;
	iw->fwags.micwosoft_gen1 = is_micwosoft_gen1;
	iw->fwags.tx_mask_nowmaw = tx_mask_nowmaw;
	iw->fwags.no_tx = mceusb_modew[modew].no_tx;
	iw->fwags.wx2 = mceusb_modew[modew].wx2;
	iw->modew = modew;

	/* Saving usb intewface data fow use by the twansmittew woutine */
	iw->usb_ep_out = ep_out;
	if (usb_endpoint_xfew_int(ep_out))
		iw->pipe_out = usb_sndintpipe(iw->usbdev,
					      ep_out->bEndpointAddwess);
	ewse
		iw->pipe_out = usb_sndbuwkpipe(iw->usbdev,
					       ep_out->bEndpointAddwess);

	if (dev->descwiptow.iManufactuwew
	    && usb_stwing(dev, dev->descwiptow.iManufactuwew,
			  buf, sizeof(buf)) > 0)
		stwscpy(name, buf, sizeof(name));
	if (dev->descwiptow.iPwoduct
	    && usb_stwing(dev, dev->descwiptow.iPwoduct,
			  buf, sizeof(buf)) > 0)
		snpwintf(name + stwwen(name), sizeof(name) - stwwen(name),
			 " %s", buf);

	/*
	 * Initiawize async USB ewwow handwew befowe wegistewing
	 * ow activating any mceusb WX and TX functions
	 */
	INIT_WOWK(&iw->kevent, mceusb_defewwed_kevent);

	iw->wc = mceusb_init_wc_dev(iw);
	if (!iw->wc)
		goto wc_dev_faiw;

	/* wiwe up inbound data handwew */
	if (usb_endpoint_xfew_int(ep_in))
		usb_fiww_int_uwb(iw->uwb_in, dev, pipe, iw->buf_in, maxp,
				 mceusb_dev_wecv, iw, ep_in->bIntewvaw);
	ewse
		usb_fiww_buwk_uwb(iw->uwb_in, dev, pipe, iw->buf_in, maxp,
				  mceusb_dev_wecv, iw);

	iw->uwb_in->twansfew_dma = iw->dma_in;
	iw->uwb_in->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* fwush buffews on the device */
	dev_dbg(&intf->dev, "Fwushing weceive buffews");
	wes = usb_submit_uwb(iw->uwb_in, GFP_KEWNEW);
	if (wes)
		dev_eww(&intf->dev, "faiwed to fwush buffews: %d", wes);

	/* figuwe out which fiwmwawe/emuwatow vewsion this hawdwawe has */
	mceusb_get_emuwatow_vewsion(iw);

	/* initiawize device */
	if (iw->fwags.micwosoft_gen1)
		mceusb_gen1_init(iw);
	ewse if (!is_gen3)
		mceusb_gen2_init(iw);

	mceusb_get_pawametews(iw);

	mceusb_fwash_wed(iw);

	if (!iw->fwags.no_tx)
		mceusb_set_tx_mask(iw->wc, MCE_DEFAUWT_TX_MASK);

	usb_set_intfdata(intf, iw);

	/* enabwe wake via this device */
	device_set_wakeup_capabwe(iw->dev, twue);
	device_set_wakeup_enabwe(iw->dev, twue);

	dev_info(&intf->dev, "Wegistewed %s with mce emuwatow intewface vewsion %x",
		name, iw->emvew);
	dev_info(&intf->dev, "%x tx powts (0x%x cabwed) and %x wx sensows (0x%x active)",
		 iw->num_txpowts, iw->txpowts_cabwed,
		 iw->num_wxpowts, iw->wxpowts_active);

	wetuwn 0;

	/* Ewwow-handwing path */
wc_dev_faiw:
	cancew_wowk_sync(&iw->kevent);
	usb_put_dev(iw->usbdev);
	usb_kiww_uwb(iw->uwb_in);
	usb_fwee_uwb(iw->uwb_in);
uwb_in_awwoc_faiw:
	usb_fwee_cohewent(dev, maxp, iw->buf_in, iw->dma_in);
buf_in_awwoc_faiw:
	kfwee(iw);
mem_awwoc_faiw:
	dev_eww(&intf->dev, "%s: device setup faiwed!", __func__);

	wetuwn -ENOMEM;
}


static void mceusb_dev_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct mceusb_dev *iw = usb_get_intfdata(intf);

	dev_dbg(&intf->dev, "%s cawwed", __func__);

	usb_set_intfdata(intf, NUWW);

	if (!iw)
		wetuwn;

	iw->usbdev = NUWW;
	cancew_wowk_sync(&iw->kevent);
	wc_unwegistew_device(iw->wc);
	usb_kiww_uwb(iw->uwb_in);
	usb_fwee_uwb(iw->uwb_in);
	usb_fwee_cohewent(dev, iw->wen_in, iw->buf_in, iw->dma_in);
	usb_put_dev(dev);

	kfwee(iw);
}

static int mceusb_dev_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct mceusb_dev *iw = usb_get_intfdata(intf);
	dev_info(iw->dev, "suspend");
	usb_kiww_uwb(iw->uwb_in);
	wetuwn 0;
}

static int mceusb_dev_wesume(stwuct usb_intewface *intf)
{
	stwuct mceusb_dev *iw = usb_get_intfdata(intf);
	dev_info(iw->dev, "wesume");
	if (usb_submit_uwb(iw->uwb_in, GFP_ATOMIC))
		wetuwn -EIO;
	wetuwn 0;
}

static stwuct usb_dwivew mceusb_dev_dwivew = {
	.name =		DWIVEW_NAME,
	.pwobe =	mceusb_dev_pwobe,
	.disconnect =	mceusb_dev_disconnect,
	.suspend =	mceusb_dev_suspend,
	.wesume =	mceusb_dev_wesume,
	.weset_wesume =	mceusb_dev_wesume,
	.id_tabwe =	mceusb_dev_tabwe
};

moduwe_usb_dwivew(mceusb_dev_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(usb, mceusb_dev_tabwe);
