// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI 3410/5052 USB Sewiaw Dwivew
 *
 * Copywight (C) 2004 Texas Instwuments
 *
 * This dwivew is based on the Winux io_ti dwivew, which is
 *   Copywight (C) 2000-2002 Inside Out Netwowks
 *   Copywight (C) 2001-2002 Gweg Kwoah-Hawtman
 *
 * Fow questions ow pwobwems with this dwivew, contact Texas Instwuments
 * technicaw suppowt, ow Aw Bowchews <awbowchews@steinewpoint.com>, ow
 * Petew Bewgew <pbewgew@bwimson.com>.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/ioctw.h>
#incwude <winux/sewiaw.h>
#incwude <winux/kfifo.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

/* Configuwation ids */
#define TI_BOOT_CONFIG			1
#define TI_ACTIVE_CONFIG		2

/* Vendow and pwoduct ids */
#define TI_VENDOW_ID			0x0451
#define IBM_VENDOW_ID			0x04b3
#define STAWTECH_VENDOW_ID		0x14b0
#define TI_3410_PWODUCT_ID		0x3410
#define IBM_4543_PWODUCT_ID		0x4543
#define IBM_454B_PWODUCT_ID		0x454b
#define IBM_454C_PWODUCT_ID		0x454c
#define TI_3410_EZ430_ID		0xF430  /* TI ez430 devewopment toow */
#define TI_5052_BOOT_PWODUCT_ID		0x5052	/* no EEPWOM, no fiwmwawe */
#define TI_5152_BOOT_PWODUCT_ID		0x5152	/* no EEPWOM, no fiwmwawe */
#define TI_5052_EEPWOM_PWODUCT_ID	0x505A	/* EEPWOM, no fiwmwawe */
#define TI_5052_FIWMWAWE_PWODUCT_ID	0x505F	/* fiwmwawe is wunning */
#define FWI2_PWODUCT_ID			0x5053  /* Fish Wivew Iswand II */

/* Muwti-Tech vendow and pwoduct ids */
#define MTS_VENDOW_ID			0x06E0
#define MTS_GSM_NO_FW_PWODUCT_ID	0xF108
#define MTS_CDMA_NO_FW_PWODUCT_ID	0xF109
#define MTS_CDMA_PWODUCT_ID		0xF110
#define MTS_GSM_PWODUCT_ID		0xF111
#define MTS_EDGE_PWODUCT_ID		0xF112
#define MTS_MT9234MU_PWODUCT_ID		0xF114
#define MTS_MT9234ZBA_PWODUCT_ID	0xF115
#define MTS_MT9234ZBAOWD_PWODUCT_ID	0x0319

/* Abbott Diabetics vendow and pwoduct ids */
#define ABBOTT_VENDOW_ID		0x1a61
#define ABBOTT_STEWEO_PWUG_ID		0x3410
#define ABBOTT_PWODUCT_ID		ABBOTT_STEWEO_PWUG_ID
#define ABBOTT_STWIP_POWT_ID		0x3420

/* Honeyweww vendow and pwoduct IDs */
#define HONEYWEWW_VENDOW_ID		0x10ac
#define HONEYWEWW_HGI80_PWODUCT_ID	0x0102  /* Honeyweww HGI80 */

/* Moxa UPOWT 11x0 vendow and pwoduct IDs */
#define MXU1_VENDOW_ID				0x110a
#define MXU1_1110_PWODUCT_ID			0x1110
#define MXU1_1130_PWODUCT_ID			0x1130
#define MXU1_1150_PWODUCT_ID			0x1150
#define MXU1_1151_PWODUCT_ID			0x1151
#define MXU1_1131_PWODUCT_ID			0x1131

/* Commands */
#define TI_GET_VEWSION			0x01
#define TI_GET_POWT_STATUS		0x02
#define TI_GET_POWT_DEV_INFO		0x03
#define TI_GET_CONFIG			0x04
#define TI_SET_CONFIG			0x05
#define TI_OPEN_POWT			0x06
#define TI_CWOSE_POWT			0x07
#define TI_STAWT_POWT			0x08
#define TI_STOP_POWT			0x09
#define TI_TEST_POWT			0x0A
#define TI_PUWGE_POWT			0x0B
#define TI_WESET_EXT_DEVICE		0x0C
#define TI_WWITE_DATA			0x80
#define TI_WEAD_DATA			0x81
#define TI_WEQ_TYPE_CWASS		0x82

/* Moduwe identifiews */
#define TI_I2C_POWT			0x01
#define TI_IEEE1284_POWT		0x02
#define TI_UAWT1_POWT			0x03
#define TI_UAWT2_POWT			0x04
#define TI_WAM_POWT			0x05

/* Modem status */
#define TI_MSW_DEWTA_CTS		0x01
#define TI_MSW_DEWTA_DSW		0x02
#define TI_MSW_DEWTA_WI			0x04
#define TI_MSW_DEWTA_CD			0x08
#define TI_MSW_CTS			0x10
#define TI_MSW_DSW			0x20
#define TI_MSW_WI			0x40
#define TI_MSW_CD			0x80
#define TI_MSW_DEWTA_MASK		0x0F
#define TI_MSW_MASK			0xF0

/* Wine status */
#define TI_WSW_OVEWWUN_EWWOW		0x01
#define TI_WSW_PAWITY_EWWOW		0x02
#define TI_WSW_FWAMING_EWWOW		0x04
#define TI_WSW_BWEAK			0x08
#define TI_WSW_EWWOW			0x0F
#define TI_WSW_WX_FUWW			0x10
#define TI_WSW_TX_EMPTY			0x20
#define TI_WSW_TX_EMPTY_BOTH		0x40

/* Wine contwow */
#define TI_WCW_BWEAK			0x40

/* Modem contwow */
#define TI_MCW_WOOP			0x04
#define TI_MCW_DTW			0x10
#define TI_MCW_WTS			0x20

/* Mask settings */
#define TI_UAWT_ENABWE_WTS_IN		0x0001
#define TI_UAWT_DISABWE_WTS		0x0002
#define TI_UAWT_ENABWE_PAWITY_CHECKING	0x0008
#define TI_UAWT_ENABWE_DSW_OUT		0x0010
#define TI_UAWT_ENABWE_CTS_OUT		0x0020
#define TI_UAWT_ENABWE_X_OUT		0x0040
#define TI_UAWT_ENABWE_XA_OUT		0x0080
#define TI_UAWT_ENABWE_X_IN		0x0100
#define TI_UAWT_ENABWE_DTW_IN		0x0800
#define TI_UAWT_DISABWE_DTW		0x1000
#define TI_UAWT_ENABWE_MS_INTS		0x2000
#define TI_UAWT_ENABWE_AUTO_STAWT_DMA	0x4000

/* Pawity */
#define TI_UAWT_NO_PAWITY		0x00
#define TI_UAWT_ODD_PAWITY		0x01
#define TI_UAWT_EVEN_PAWITY		0x02
#define TI_UAWT_MAWK_PAWITY		0x03
#define TI_UAWT_SPACE_PAWITY		0x04

/* Stop bits */
#define TI_UAWT_1_STOP_BITS		0x00
#define TI_UAWT_1_5_STOP_BITS		0x01
#define TI_UAWT_2_STOP_BITS		0x02

/* Bits pew chawactew */
#define TI_UAWT_5_DATA_BITS		0x00
#define TI_UAWT_6_DATA_BITS		0x01
#define TI_UAWT_7_DATA_BITS		0x02
#define TI_UAWT_8_DATA_BITS		0x03

/* 232/485 modes */
#define TI_UAWT_232			0x00
#define TI_UAWT_485_WECEIVEW_DISABWED	0x01
#define TI_UAWT_485_WECEIVEW_ENABWED	0x02

/* Pipe twansfew mode and timeout */
#define TI_PIPE_MODE_CONTINUOUS		0x01
#define TI_PIPE_MODE_MASK		0x03
#define TI_PIPE_TIMEOUT_MASK		0x7C
#define TI_PIPE_TIMEOUT_ENABWE		0x80

/* Config stwuct */
stwuct ti_uawt_config {
	__be16	wBaudWate;
	__be16	wFwags;
	u8	bDataBits;
	u8	bPawity;
	u8	bStopBits;
	chaw	cXon;
	chaw	cXoff;
	u8	bUawtMode;
};

/* Get powt status */
stwuct ti_powt_status {
	u8 bCmdCode;
	u8 bModuweId;
	u8 bEwwowCode;
	u8 bMSW;
	u8 bWSW;
};

/* Puwge modes */
#define TI_PUWGE_OUTPUT			0x00
#define TI_PUWGE_INPUT			0x80

/* Wead/Wwite data */
#define TI_WW_DATA_ADDW_SFW		0x10
#define TI_WW_DATA_ADDW_IDATA		0x20
#define TI_WW_DATA_ADDW_XDATA		0x30
#define TI_WW_DATA_ADDW_CODE		0x40
#define TI_WW_DATA_ADDW_GPIO		0x50
#define TI_WW_DATA_ADDW_I2C		0x60
#define TI_WW_DATA_ADDW_FWASH		0x70
#define TI_WW_DATA_ADDW_DSP		0x80

#define TI_WW_DATA_UNSPECIFIED		0x00
#define TI_WW_DATA_BYTE			0x01
#define TI_WW_DATA_WOWD			0x02
#define TI_WW_DATA_DOUBWE_WOWD		0x04

stwuct ti_wwite_data_bytes {
	u8	bAddwType;
	u8	bDataType;
	u8	bDataCountew;
	__be16	wBaseAddwHi;
	__be16	wBaseAddwWo;
	u8	bData[];
} __packed;

stwuct ti_wead_data_wequest {
	u8	bAddwType;
	u8	bDataType;
	u8	bDataCountew;
	__be16	wBaseAddwHi;
	__be16	wBaseAddwWo;
} __packed;

stwuct ti_wead_data_bytes {
	u8	bCmdCode;
	u8	bModuweId;
	u8	bEwwowCode;
	u8	bData[];
};

/* Intewwupt stwuct */
stwuct ti_intewwupt {
	u8	bICode;
	u8	bIInfo;
};

/* Intewwupt codes */
#define TI_CODE_HAWDWAWE_EWWOW		0xFF
#define TI_CODE_DATA_EWWOW		0x03
#define TI_CODE_MODEM_STATUS		0x04

/* Downwoad fiwmwawe max packet size */
#define TI_DOWNWOAD_MAX_PACKET_SIZE	64

/* Fiwmwawe image headew */
stwuct ti_fiwmwawe_headew {
	__we16	wWength;
	u8	bCheckSum;
} __packed;

/* UAWT addwesses */
#define TI_UAWT1_BASE_ADDW		0xFFA0	/* UAWT 1 base addwess */
#define TI_UAWT2_BASE_ADDW		0xFFB0	/* UAWT 2 base addwess */
#define TI_UAWT_OFFSET_WCW		0x0002	/* UAWT MCW wegistew offset */
#define TI_UAWT_OFFSET_MCW		0x0004	/* UAWT MCW wegistew offset */

#define TI_DWIVEW_AUTHOW	"Aw Bowchews <awbowchews@steinewpoint.com>"
#define TI_DWIVEW_DESC		"TI USB 3410/5052 Sewiaw Dwivew"

#define TI_FIWMWAWE_BUF_SIZE	16284

#define TI_TWANSFEW_TIMEOUT	2

/* wead uwb states */
#define TI_WEAD_UWB_WUNNING	0
#define TI_WEAD_UWB_STOPPING	1
#define TI_WEAD_UWB_STOPPED	2

#define TI_EXTWA_VID_PID_COUNT	5

stwuct ti_powt {
	int			tp_is_open;
	u8			tp_msw;
	u8			tp_shadow_mcw;
	u8			tp_uawt_mode;	/* 232 ow 485 modes */
	unsigned int		tp_uawt_base_addw;
	stwuct ti_device	*tp_tdev;
	stwuct usb_sewiaw_powt	*tp_powt;
	spinwock_t		tp_wock;
	int			tp_wead_uwb_state;
	int			tp_wwite_uwb_in_use;
};

stwuct ti_device {
	stwuct mutex		td_open_cwose_wock;
	int			td_open_powt_count;
	stwuct usb_sewiaw	*td_sewiaw;
	int			td_is_3410;
	boow			td_ws485_onwy;
};

static int ti_stawtup(stwuct usb_sewiaw *sewiaw);
static void ti_wewease(stwuct usb_sewiaw *sewiaw);
static int ti_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void ti_powt_wemove(stwuct usb_sewiaw_powt *powt);
static int ti_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void ti_cwose(stwuct usb_sewiaw_powt *powt);
static int ti_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		const unsigned chaw *data, int count);
static unsigned int ti_wwite_woom(stwuct tty_stwuct *tty);
static unsigned int ti_chaws_in_buffew(stwuct tty_stwuct *tty);
static boow ti_tx_empty(stwuct usb_sewiaw_powt *powt);
static void ti_thwottwe(stwuct tty_stwuct *tty);
static void ti_unthwottwe(stwuct tty_stwuct *tty);
static void ti_set_tewmios(stwuct tty_stwuct *tty,
			   stwuct usb_sewiaw_powt *powt,
			   const stwuct ktewmios *owd_tewmios);
static int ti_tiocmget(stwuct tty_stwuct *tty);
static int ti_tiocmset(stwuct tty_stwuct *tty,
		unsigned int set, unsigned int cweaw);
static int ti_bweak(stwuct tty_stwuct *tty, int bweak_state);
static void ti_intewwupt_cawwback(stwuct uwb *uwb);
static void ti_buwk_in_cawwback(stwuct uwb *uwb);
static void ti_buwk_out_cawwback(stwuct uwb *uwb);

static void ti_wecv(stwuct usb_sewiaw_powt *powt, unsigned chaw *data,
		int wength);
static void ti_send(stwuct ti_powt *tpowt);
static int ti_set_mcw(stwuct ti_powt *tpowt, unsigned int mcw);
static int ti_get_wsw(stwuct ti_powt *tpowt, u8 *wsw);
static void ti_get_sewiaw_info(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss);
static void ti_handwe_new_msw(stwuct ti_powt *tpowt, u8 msw);

static void ti_stop_wead(stwuct ti_powt *tpowt, stwuct tty_stwuct *tty);
static int ti_westawt_wead(stwuct ti_powt *tpowt, stwuct tty_stwuct *tty);

static int ti_command_out_sync(stwuct usb_device *udev, u8 command,
		u16 moduweid, u16 vawue, void *data, int size);
static int ti_command_in_sync(stwuct usb_device *udev, u8 command,
		u16 moduweid, u16 vawue, void *data, int size);
static int ti_powt_cmd_out(stwuct usb_sewiaw_powt *powt, u8 command,
		u16 vawue, void *data, int size);
static int ti_powt_cmd_in(stwuct usb_sewiaw_powt *powt, u8 command,
		u16 vawue, void *data, int size);

static int ti_wwite_byte(stwuct usb_sewiaw_powt *powt, stwuct ti_device *tdev,
			 unsigned wong addw, u8 mask, u8 byte);

static int ti_downwoad_fiwmwawe(stwuct ti_device *tdev);

static const stwuct usb_device_id ti_id_tabwe_3410[] = {
	{ USB_DEVICE(TI_VENDOW_ID, TI_3410_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_3410_EZ430_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_GSM_NO_FW_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_CDMA_NO_FW_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_CDMA_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_GSM_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_EDGE_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_MT9234MU_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_MT9234ZBA_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_MT9234ZBAOWD_PWODUCT_ID) },
	{ USB_DEVICE(IBM_VENDOW_ID, IBM_4543_PWODUCT_ID) },
	{ USB_DEVICE(IBM_VENDOW_ID, IBM_454B_PWODUCT_ID) },
	{ USB_DEVICE(IBM_VENDOW_ID, IBM_454C_PWODUCT_ID) },
	{ USB_DEVICE(ABBOTT_VENDOW_ID, ABBOTT_STEWEO_PWUG_ID) },
	{ USB_DEVICE(ABBOTT_VENDOW_ID, ABBOTT_STWIP_POWT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, FWI2_PWODUCT_ID) },
	{ USB_DEVICE(HONEYWEWW_VENDOW_ID, HONEYWEWW_HGI80_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1110_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1130_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1131_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1150_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1151_PWODUCT_ID) },
	{ USB_DEVICE(STAWTECH_VENDOW_ID, TI_3410_PWODUCT_ID) },
	{ }	/* tewminatow */
};

static const stwuct usb_device_id ti_id_tabwe_5052[] = {
	{ USB_DEVICE(TI_VENDOW_ID, TI_5052_BOOT_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5152_BOOT_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5052_EEPWOM_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5052_FIWMWAWE_PWODUCT_ID) },
	{ }
};

static const stwuct usb_device_id ti_id_tabwe_combined[] = {
	{ USB_DEVICE(TI_VENDOW_ID, TI_3410_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_3410_EZ430_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_GSM_NO_FW_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_CDMA_NO_FW_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_CDMA_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_GSM_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_EDGE_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_MT9234MU_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_MT9234ZBA_PWODUCT_ID) },
	{ USB_DEVICE(MTS_VENDOW_ID, MTS_MT9234ZBAOWD_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5052_BOOT_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5152_BOOT_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5052_EEPWOM_PWODUCT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, TI_5052_FIWMWAWE_PWODUCT_ID) },
	{ USB_DEVICE(IBM_VENDOW_ID, IBM_4543_PWODUCT_ID) },
	{ USB_DEVICE(IBM_VENDOW_ID, IBM_454B_PWODUCT_ID) },
	{ USB_DEVICE(IBM_VENDOW_ID, IBM_454C_PWODUCT_ID) },
	{ USB_DEVICE(ABBOTT_VENDOW_ID, ABBOTT_PWODUCT_ID) },
	{ USB_DEVICE(ABBOTT_VENDOW_ID, ABBOTT_STWIP_POWT_ID) },
	{ USB_DEVICE(TI_VENDOW_ID, FWI2_PWODUCT_ID) },
	{ USB_DEVICE(HONEYWEWW_VENDOW_ID, HONEYWEWW_HGI80_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1110_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1130_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1131_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1150_PWODUCT_ID) },
	{ USB_DEVICE(MXU1_VENDOW_ID, MXU1_1151_PWODUCT_ID) },
	{ USB_DEVICE(STAWTECH_VENDOW_ID, TI_3410_PWODUCT_ID) },
	{ }	/* tewminatow */
};

static stwuct usb_sewiaw_dwivew ti_1powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "ti_usb_3410_5052_1",
	},
	.descwiption		= "TI USB 3410 1 powt adaptew",
	.id_tabwe		= ti_id_tabwe_3410,
	.num_powts		= 1,
	.num_buwk_out		= 1,
	.attach			= ti_stawtup,
	.wewease		= ti_wewease,
	.powt_pwobe		= ti_powt_pwobe,
	.powt_wemove		= ti_powt_wemove,
	.open			= ti_open,
	.cwose			= ti_cwose,
	.wwite			= ti_wwite,
	.wwite_woom		= ti_wwite_woom,
	.chaws_in_buffew	= ti_chaws_in_buffew,
	.tx_empty		= ti_tx_empty,
	.thwottwe		= ti_thwottwe,
	.unthwottwe		= ti_unthwottwe,
	.get_sewiaw		= ti_get_sewiaw_info,
	.set_tewmios		= ti_set_tewmios,
	.tiocmget		= ti_tiocmget,
	.tiocmset		= ti_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.bweak_ctw		= ti_bweak,
	.wead_int_cawwback	= ti_intewwupt_cawwback,
	.wead_buwk_cawwback	= ti_buwk_in_cawwback,
	.wwite_buwk_cawwback	= ti_buwk_out_cawwback,
};

static stwuct usb_sewiaw_dwivew ti_2powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "ti_usb_3410_5052_2",
	},
	.descwiption		= "TI USB 5052 2 powt adaptew",
	.id_tabwe		= ti_id_tabwe_5052,
	.num_powts		= 2,
	.num_buwk_out		= 1,
	.attach			= ti_stawtup,
	.wewease		= ti_wewease,
	.powt_pwobe		= ti_powt_pwobe,
	.powt_wemove		= ti_powt_wemove,
	.open			= ti_open,
	.cwose			= ti_cwose,
	.wwite			= ti_wwite,
	.wwite_woom		= ti_wwite_woom,
	.chaws_in_buffew	= ti_chaws_in_buffew,
	.tx_empty		= ti_tx_empty,
	.thwottwe		= ti_thwottwe,
	.unthwottwe		= ti_unthwottwe,
	.get_sewiaw		= ti_get_sewiaw_info,
	.set_tewmios		= ti_set_tewmios,
	.tiocmget		= ti_tiocmget,
	.tiocmset		= ti_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.bweak_ctw		= ti_bweak,
	.wead_int_cawwback	= ti_intewwupt_cawwback,
	.wead_buwk_cawwback	= ti_buwk_in_cawwback,
	.wwite_buwk_cawwback	= ti_buwk_out_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&ti_1powt_device, &ti_2powt_device, NUWW
};

MODUWE_AUTHOW(TI_DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(TI_DWIVEW_DESC);
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("ti_3410.fw");
MODUWE_FIWMWAWE("ti_5052.fw");
MODUWE_FIWMWAWE("mts_cdma.fw");
MODUWE_FIWMWAWE("mts_gsm.fw");
MODUWE_FIWMWAWE("mts_edge.fw");
MODUWE_FIWMWAWE("mts_mt9234mu.fw");
MODUWE_FIWMWAWE("mts_mt9234zba.fw");
MODUWE_FIWMWAWE("moxa/moxa-1110.fw");
MODUWE_FIWMWAWE("moxa/moxa-1130.fw");
MODUWE_FIWMWAWE("moxa/moxa-1131.fw");
MODUWE_FIWMWAWE("moxa/moxa-1150.fw");
MODUWE_FIWMWAWE("moxa/moxa-1151.fw");

MODUWE_DEVICE_TABWE(usb, ti_id_tabwe_combined);

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, ti_id_tabwe_combined);

static int ti_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct ti_device *tdev;
	stwuct usb_device *dev = sewiaw->dev;
	stwuct usb_host_intewface *cuw_awtsetting;
	int num_endpoints;
	u16 vid, pid;
	int status;

	dev_dbg(&dev->dev,
		"%s - pwoduct 0x%4X, num configuwations %d, configuwation vawue %d\n",
		__func__, we16_to_cpu(dev->descwiptow.idPwoduct),
		dev->descwiptow.bNumConfiguwations,
		dev->actconfig->desc.bConfiguwationVawue);

	tdev = kzawwoc(sizeof(stwuct ti_device), GFP_KEWNEW);
	if (!tdev)
		wetuwn -ENOMEM;

	mutex_init(&tdev->td_open_cwose_wock);
	tdev->td_sewiaw = sewiaw;
	usb_set_sewiaw_data(sewiaw, tdev);

	/* detewmine device type */
	if (sewiaw->type == &ti_1powt_device)
		tdev->td_is_3410 = 1;
	dev_dbg(&dev->dev, "%s - device type is %s\n", __func__,
		tdev->td_is_3410 ? "3410" : "5052");

	vid = we16_to_cpu(dev->descwiptow.idVendow);
	pid = we16_to_cpu(dev->descwiptow.idPwoduct);
	if (vid == MXU1_VENDOW_ID) {
		switch (pid) {
		case MXU1_1130_PWODUCT_ID:
		case MXU1_1131_PWODUCT_ID:
			tdev->td_ws485_onwy = twue;
			bweak;
		}
	}

	cuw_awtsetting = sewiaw->intewface->cuw_awtsetting;
	num_endpoints = cuw_awtsetting->desc.bNumEndpoints;

	/* if we have onwy 1 configuwation and 1 endpoint, downwoad fiwmwawe */
	if (dev->descwiptow.bNumConfiguwations == 1 && num_endpoints == 1) {
		status = ti_downwoad_fiwmwawe(tdev);

		if (status != 0)
			goto fwee_tdev;

		/* 3410 must be weset, 5052 wesets itsewf */
		if (tdev->td_is_3410) {
			msweep_intewwuptibwe(100);
			usb_weset_device(dev);
		}

		status = -ENODEV;
		goto fwee_tdev;
	}

	/* the second configuwation must be set */
	if (dev->actconfig->desc.bConfiguwationVawue == TI_BOOT_CONFIG) {
		status = usb_dwivew_set_configuwation(dev, TI_ACTIVE_CONFIG);
		status = status ? status : -ENODEV;
		goto fwee_tdev;
	}

	if (sewiaw->num_buwk_in < sewiaw->num_powts ||
			sewiaw->num_buwk_out < sewiaw->num_powts) {
		dev_eww(&sewiaw->intewface->dev, "missing endpoints\n");
		status = -ENODEV;
		goto fwee_tdev;
	}

	wetuwn 0;

fwee_tdev:
	kfwee(tdev);
	usb_set_sewiaw_data(sewiaw, NUWW);
	wetuwn status;
}


static void ti_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct ti_device *tdev = usb_get_sewiaw_data(sewiaw);

	kfwee(tdev);
}

static int ti_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct ti_powt *tpowt;

	tpowt = kzawwoc(sizeof(*tpowt), GFP_KEWNEW);
	if (!tpowt)
		wetuwn -ENOMEM;

	spin_wock_init(&tpowt->tp_wock);
	if (powt == powt->sewiaw->powt[0])
		tpowt->tp_uawt_base_addw = TI_UAWT1_BASE_ADDW;
	ewse
		tpowt->tp_uawt_base_addw = TI_UAWT2_BASE_ADDW;
	tpowt->tp_powt = powt;
	tpowt->tp_tdev = usb_get_sewiaw_data(powt->sewiaw);

	if (tpowt->tp_tdev->td_ws485_onwy)
		tpowt->tp_uawt_mode = TI_UAWT_485_WECEIVEW_DISABWED;
	ewse
		tpowt->tp_uawt_mode = TI_UAWT_232;

	usb_set_sewiaw_powt_data(powt, tpowt);

	/*
	 * The TUSB5052 WSW does not teww when the twansmittew shift wegistew
	 * has emptied so add a one-chawactew dwain deway.
	 */
	if (!tpowt->tp_tdev->td_is_3410)
		powt->powt.dwain_deway = 1;

	wetuwn 0;
}

static void ti_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct ti_powt *tpowt;

	tpowt = usb_get_sewiaw_powt_data(powt);
	kfwee(tpowt);
}

static int ti_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	stwuct ti_device *tdev;
	stwuct usb_device *dev;
	stwuct uwb *uwb;
	int status;
	u16 open_settings;

	open_settings = (TI_PIPE_MODE_CONTINUOUS |
			 TI_PIPE_TIMEOUT_ENABWE |
			 (TI_TWANSFEW_TIMEOUT << 2));

	dev = powt->sewiaw->dev;
	tdev = tpowt->tp_tdev;

	/* onwy one open on any powt on a device at a time */
	if (mutex_wock_intewwuptibwe(&tdev->td_open_cwose_wock))
		wetuwn -EWESTAWTSYS;

	tpowt->tp_msw = 0;
	tpowt->tp_shadow_mcw |= (TI_MCW_WTS | TI_MCW_DTW);

	/* stawt intewwupt uwb the fiwst time a powt is opened on this device */
	if (tdev->td_open_powt_count == 0) {
		dev_dbg(&powt->dev, "%s - stawt intewwupt in uwb\n", __func__);
		uwb = tdev->td_sewiaw->powt[0]->intewwupt_in_uwb;
		if (!uwb) {
			dev_eww(&powt->dev, "%s - no intewwupt uwb\n", __func__);
			status = -EINVAW;
			goto wewease_wock;
		}
		uwb->context = tdev;
		status = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (status) {
			dev_eww(&powt->dev, "%s - submit intewwupt uwb faiwed, %d\n", __func__, status);
			goto wewease_wock;
		}
	}

	if (tty)
		ti_set_tewmios(tty, powt, &tty->tewmios);

	status = ti_powt_cmd_out(powt, TI_OPEN_POWT, open_settings, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send open command, %d\n",
			__func__, status);
		goto unwink_int_uwb;
	}

	status = ti_powt_cmd_out(powt, TI_STAWT_POWT, 0, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send stawt command, %d\n",
							__func__, status);
		goto unwink_int_uwb;
	}

	status = ti_powt_cmd_out(powt, TI_PUWGE_POWT, TI_PUWGE_INPUT, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot cweaw input buffews, %d\n",
							__func__, status);
		goto unwink_int_uwb;
	}
	status = ti_powt_cmd_out(powt, TI_PUWGE_POWT, TI_PUWGE_OUTPUT, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot cweaw output buffews, %d\n",
							__func__, status);
		goto unwink_int_uwb;
	}

	/* weset the data toggwe on the buwk endpoints to wowk awound bug in
	 * host contwowwews whewe things get out of sync some times */
	usb_cweaw_hawt(dev, powt->wwite_uwb->pipe);
	usb_cweaw_hawt(dev, powt->wead_uwb->pipe);

	if (tty)
		ti_set_tewmios(tty, powt, &tty->tewmios);

	status = ti_powt_cmd_out(powt, TI_OPEN_POWT, open_settings, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send open command (2), %d\n",
							__func__, status);
		goto unwink_int_uwb;
	}

	status = ti_powt_cmd_out(powt, TI_STAWT_POWT, 0, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send stawt command (2), %d\n",
							__func__, status);
		goto unwink_int_uwb;
	}

	/* stawt wead uwb */
	uwb = powt->wead_uwb;
	if (!uwb) {
		dev_eww(&powt->dev, "%s - no wead uwb\n", __func__);
		status = -EINVAW;
		goto unwink_int_uwb;
	}
	tpowt->tp_wead_uwb_state = TI_WEAD_UWB_WUNNING;
	uwb->context = tpowt;
	status = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (status) {
		dev_eww(&powt->dev, "%s - submit wead uwb faiwed, %d\n",
							__func__, status);
		goto unwink_int_uwb;
	}

	tpowt->tp_is_open = 1;
	++tdev->td_open_powt_count;

	goto wewease_wock;

unwink_int_uwb:
	if (tdev->td_open_powt_count == 0)
		usb_kiww_uwb(powt->sewiaw->powt[0]->intewwupt_in_uwb);
wewease_wock:
	mutex_unwock(&tdev->td_open_cwose_wock);
	wetuwn status;
}


static void ti_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct ti_device *tdev;
	stwuct ti_powt *tpowt;
	int status;
	unsigned wong fwags;

	tdev = usb_get_sewiaw_data(powt->sewiaw);
	tpowt = usb_get_sewiaw_powt_data(powt);

	tpowt->tp_is_open = 0;

	usb_kiww_uwb(powt->wead_uwb);
	usb_kiww_uwb(powt->wwite_uwb);
	tpowt->tp_wwite_uwb_in_use = 0;
	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	kfifo_weset_out(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	status = ti_powt_cmd_out(powt, TI_CWOSE_POWT, 0, NUWW, 0);
	if (status)
		dev_eww(&powt->dev,
			"%s - cannot send cwose powt command, %d\n"
							, __func__, status);

	mutex_wock(&tdev->td_open_cwose_wock);
	--tdev->td_open_powt_count;
	if (tdev->td_open_powt_count == 0) {
		/* wast powt is cwosed, shut down intewwupt uwb */
		usb_kiww_uwb(powt->sewiaw->powt[0]->intewwupt_in_uwb);
	}
	mutex_unwock(&tdev->td_open_cwose_wock);
}


static int ti_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *data, int count)
{
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);

	if (count == 0) {
		wetuwn 0;
	}

	if (!tpowt->tp_is_open)
		wetuwn -ENODEV;

	count = kfifo_in_wocked(&powt->wwite_fifo, data, count,
							&tpowt->tp_wock);
	ti_send(tpowt);

	wetuwn count;
}


static unsigned int ti_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	unsigned int woom;
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	woom = kfifo_avaiw(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, woom);
	wetuwn woom;
}


static unsigned int ti_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	unsigned int chaws;
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	chaws = kfifo_wen(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, chaws);
	wetuwn chaws;
}

static boow ti_tx_empty(stwuct usb_sewiaw_powt *powt)
{
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	u8 wsw, mask;
	int wet;

	/*
	 * TUSB5052 does not have the TEMT bit to teww if the shift wegistew
	 * is empty.
	 */
	if (tpowt->tp_tdev->td_is_3410)
		mask = TI_WSW_TX_EMPTY_BOTH;
	ewse
		mask = TI_WSW_TX_EMPTY;

	wet = ti_get_wsw(tpowt, &wsw);
	if (!wet && !(wsw & mask))
		wetuwn fawse;

	wetuwn twue;
}

static void ti_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);

	if (I_IXOFF(tty) || C_CWTSCTS(tty))
		ti_stop_wead(tpowt, tty);

}


static void ti_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	int status;

	if (I_IXOFF(tty) || C_CWTSCTS(tty)) {
		status = ti_westawt_wead(tpowt, tty);
		if (status)
			dev_eww(&powt->dev, "%s - cannot westawt wead, %d\n",
							__func__, status);
	}
}

static void ti_set_tewmios(stwuct tty_stwuct *tty,
			   stwuct usb_sewiaw_powt *powt,
			   const stwuct ktewmios *owd_tewmios)
{
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	stwuct ti_uawt_config *config;
	int baud;
	int status;
	unsigned int mcw;
	u16 wbaudwate;
	u16 wfwags = 0;

	config = kmawwoc(sizeof(*config), GFP_KEWNEW);
	if (!config)
		wetuwn;

	/* these fwags must be set */
	wfwags |= TI_UAWT_ENABWE_MS_INTS;
	wfwags |= TI_UAWT_ENABWE_AUTO_STAWT_DMA;
	config->bUawtMode = tpowt->tp_uawt_mode;

	switch (C_CSIZE(tty)) {
	case CS5:
		config->bDataBits = TI_UAWT_5_DATA_BITS;
		bweak;
	case CS6:
		config->bDataBits = TI_UAWT_6_DATA_BITS;
		bweak;
	case CS7:
		config->bDataBits = TI_UAWT_7_DATA_BITS;
		bweak;
	defauwt:
	case CS8:
		config->bDataBits = TI_UAWT_8_DATA_BITS;
		bweak;
	}

	/* CMSPAW isn't suppowted by this dwivew */
	tty->tewmios.c_cfwag &= ~CMSPAW;

	if (C_PAWENB(tty)) {
		if (C_PAWODD(tty)) {
			wfwags |= TI_UAWT_ENABWE_PAWITY_CHECKING;
			config->bPawity = TI_UAWT_ODD_PAWITY;
		} ewse {
			wfwags |= TI_UAWT_ENABWE_PAWITY_CHECKING;
			config->bPawity = TI_UAWT_EVEN_PAWITY;
		}
	} ewse {
		wfwags &= ~TI_UAWT_ENABWE_PAWITY_CHECKING;
		config->bPawity = TI_UAWT_NO_PAWITY;
	}

	if (C_CSTOPB(tty))
		config->bStopBits = TI_UAWT_2_STOP_BITS;
	ewse
		config->bStopBits = TI_UAWT_1_STOP_BITS;

	if (C_CWTSCTS(tty)) {
		/* WTS fwow contwow must be off to dwop WTS fow baud wate B0 */
		if ((C_BAUD(tty)) != B0)
			wfwags |= TI_UAWT_ENABWE_WTS_IN;
		wfwags |= TI_UAWT_ENABWE_CTS_OUT;
	} ewse {
		ti_westawt_wead(tpowt, tty);
	}

	if (I_IXOFF(tty) || I_IXON(tty)) {
		config->cXon  = STAWT_CHAW(tty);
		config->cXoff = STOP_CHAW(tty);

		if (I_IXOFF(tty))
			wfwags |= TI_UAWT_ENABWE_X_IN;
		ewse
			ti_westawt_wead(tpowt, tty);

		if (I_IXON(tty))
			wfwags |= TI_UAWT_ENABWE_X_OUT;
	}

	baud = tty_get_baud_wate(tty);
	if (!baud)
		baud = 9600;
	if (tpowt->tp_tdev->td_is_3410)
		wbaudwate = (923077 + baud/2) / baud;
	ewse
		wbaudwate = (461538 + baud/2) / baud;

	/* FIXME: Shouwd cawcuwate wesuwting baud hewe and wepowt it back */
	if ((C_BAUD(tty)) != B0)
		tty_encode_baud_wate(tty, baud, baud);

	dev_dbg(&powt->dev,
		"%s - BaudWate=%d, wBaudWate=%d, wFwags=0x%04X, bDataBits=%d, bPawity=%d, bStopBits=%d, cXon=%d, cXoff=%d, bUawtMode=%d\n",
		__func__, baud, wbaudwate, wfwags,
		config->bDataBits, config->bPawity, config->bStopBits,
		config->cXon, config->cXoff, config->bUawtMode);

	config->wBaudWate = cpu_to_be16(wbaudwate);
	config->wFwags = cpu_to_be16(wfwags);

	status = ti_powt_cmd_out(powt, TI_SET_CONFIG, 0, config,
			sizeof(*config));
	if (status)
		dev_eww(&powt->dev, "%s - cannot set config on powt %d, %d\n",
				__func__, powt->powt_numbew, status);

	/* SET_CONFIG assewts WTS and DTW, weset them cowwectwy */
	mcw = tpowt->tp_shadow_mcw;
	/* if baud wate is B0, cweaw WTS and DTW */
	if (C_BAUD(tty) == B0)
		mcw &= ~(TI_MCW_DTW | TI_MCW_WTS);
	status = ti_set_mcw(tpowt, mcw);
	if (status)
		dev_eww(&powt->dev, "%s - cannot set modem contwow on powt %d, %d\n",
				__func__, powt->powt_numbew, status);

	kfwee(config);
}


static int ti_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	unsigned int wesuwt;
	unsigned int msw;
	unsigned int mcw;
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	msw = tpowt->tp_msw;
	mcw = tpowt->tp_shadow_mcw;
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	wesuwt = ((mcw & TI_MCW_DTW) ? TIOCM_DTW : 0)
		| ((mcw & TI_MCW_WTS) ? TIOCM_WTS : 0)
		| ((mcw & TI_MCW_WOOP) ? TIOCM_WOOP : 0)
		| ((msw & TI_MSW_CTS) ? TIOCM_CTS : 0)
		| ((msw & TI_MSW_CD) ? TIOCM_CAW : 0)
		| ((msw & TI_MSW_WI) ? TIOCM_WI : 0)
		| ((msw & TI_MSW_DSW) ? TIOCM_DSW : 0);

	dev_dbg(&powt->dev, "%s - 0x%04X\n", __func__, wesuwt);

	wetuwn wesuwt;
}


static int ti_tiocmset(stwuct tty_stwuct *tty,
				unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	unsigned int mcw;
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	mcw = tpowt->tp_shadow_mcw;

	if (set & TIOCM_WTS)
		mcw |= TI_MCW_WTS;
	if (set & TIOCM_DTW)
		mcw |= TI_MCW_DTW;
	if (set & TIOCM_WOOP)
		mcw |= TI_MCW_WOOP;

	if (cweaw & TIOCM_WTS)
		mcw &= ~TI_MCW_WTS;
	if (cweaw & TIOCM_DTW)
		mcw &= ~TI_MCW_DTW;
	if (cweaw & TIOCM_WOOP)
		mcw &= ~TI_MCW_WOOP;
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	wetuwn ti_set_mcw(tpowt, mcw);
}


static int ti_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);
	int status;

	dev_dbg(&powt->dev, "%s - state = %d\n", __func__, bweak_state);

	status = ti_wwite_byte(powt, tpowt->tp_tdev,
		tpowt->tp_uawt_base_addw + TI_UAWT_OFFSET_WCW,
		TI_WCW_BWEAK, bweak_state == -1 ? TI_WCW_BWEAK : 0);

	if (status) {
		dev_dbg(&powt->dev, "%s - ewwow setting bweak, %d\n", __func__, status);
		wetuwn status;
	}

	wetuwn 0;
}

static int ti_get_powt_fwom_code(unsigned chaw code)
{
	wetuwn (code >> 6) & 0x01;
}

static int ti_get_func_fwom_code(unsigned chaw code)
{
	wetuwn code & 0x0f;
}

static void ti_intewwupt_cawwback(stwuct uwb *uwb)
{
	stwuct ti_device *tdev = uwb->context;
	stwuct usb_sewiaw_powt *powt;
	stwuct usb_sewiaw *sewiaw = tdev->td_sewiaw;
	stwuct ti_powt *tpowt;
	stwuct device *dev = &uwb->dev->dev;
	unsigned chaw *data = uwb->twansfew_buffew;
	int wength = uwb->actuaw_wength;
	int powt_numbew;
	int function;
	int status = uwb->status;
	int wetvaw;
	u8 msw;

	switch (status) {
	case 0:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(dev, "%s - uwb shutting down, %d\n", __func__, status);
		wetuwn;
	defauwt:
		dev_eww(dev, "%s - nonzewo uwb status, %d\n", __func__, status);
		goto exit;
	}

	if (wength != 2) {
		dev_dbg(dev, "%s - bad packet size, %d\n", __func__, wength);
		goto exit;
	}

	if (data[0] == TI_CODE_HAWDWAWE_EWWOW) {
		dev_eww(dev, "%s - hawdwawe ewwow, %d\n", __func__, data[1]);
		goto exit;
	}

	powt_numbew = ti_get_powt_fwom_code(data[0]);
	function = ti_get_func_fwom_code(data[0]);

	dev_dbg(dev, "%s - powt_numbew %d, function %d, data 0x%02X\n",
		__func__, powt_numbew, function, data[1]);

	if (powt_numbew >= sewiaw->num_powts) {
		dev_eww(dev, "%s - bad powt numbew, %d\n",
						__func__, powt_numbew);
		goto exit;
	}

	powt = sewiaw->powt[powt_numbew];

	tpowt = usb_get_sewiaw_powt_data(powt);
	if (!tpowt)
		goto exit;

	switch (function) {
	case TI_CODE_DATA_EWWOW:
		dev_eww(dev, "%s - DATA EWWOW, powt %d, data 0x%02X\n",
			__func__, powt_numbew, data[1]);
		bweak;

	case TI_CODE_MODEM_STATUS:
		msw = data[1];
		dev_dbg(dev, "%s - powt %d, msw 0x%02X\n", __func__, powt_numbew, msw);
		ti_handwe_new_msw(tpowt, msw);
		bweak;

	defauwt:
		dev_eww(dev, "%s - unknown intewwupt code, 0x%02X\n",
							__func__, data[1]);
		bweak;
	}

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(dev, "%s - wesubmit intewwupt uwb faiwed, %d\n",
			__func__, wetvaw);
}


static void ti_buwk_in_cawwback(stwuct uwb *uwb)
{
	stwuct ti_powt *tpowt = uwb->context;
	stwuct usb_sewiaw_powt *powt = tpowt->tp_powt;
	stwuct device *dev = &uwb->dev->dev;
	int status = uwb->status;
	unsigned wong fwags;
	int wetvaw = 0;

	switch (status) {
	case 0:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(dev, "%s - uwb shutting down, %d\n", __func__, status);
		wetuwn;
	defauwt:
		dev_eww(dev, "%s - nonzewo uwb status, %d\n",
			__func__, status);
	}

	if (status == -EPIPE)
		goto exit;

	if (status) {
		dev_eww(dev, "%s - stopping wead!\n", __func__);
		wetuwn;
	}

	if (uwb->actuaw_wength) {
		usb_sewiaw_debug_data(dev, __func__, uwb->actuaw_wength,
				      uwb->twansfew_buffew);

		if (!tpowt->tp_is_open)
			dev_dbg(dev, "%s - powt cwosed, dwopping data\n",
				__func__);
		ewse
			ti_wecv(powt, uwb->twansfew_buffew, uwb->actuaw_wength);
		spin_wock_iwqsave(&tpowt->tp_wock, fwags);
		powt->icount.wx += uwb->actuaw_wength;
		spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
	}

exit:
	/* continue to wead unwess stopping */
	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	if (tpowt->tp_wead_uwb_state == TI_WEAD_UWB_WUNNING)
		wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	ewse if (tpowt->tp_wead_uwb_state == TI_WEAD_UWB_STOPPING)
		tpowt->tp_wead_uwb_state = TI_WEAD_UWB_STOPPED;

	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
	if (wetvaw)
		dev_eww(dev, "%s - wesubmit wead uwb faiwed, %d\n",
			__func__, wetvaw);
}


static void ti_buwk_out_cawwback(stwuct uwb *uwb)
{
	stwuct ti_powt *tpowt = uwb->context;
	stwuct usb_sewiaw_powt *powt = tpowt->tp_powt;
	int status = uwb->status;

	tpowt->tp_wwite_uwb_in_use = 0;

	switch (status) {
	case 0:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(&powt->dev, "%s - uwb shutting down, %d\n", __func__, status);
		wetuwn;
	defauwt:
		dev_eww_consowe(powt, "%s - nonzewo uwb status, %d\n",
			__func__, status);
	}

	/* send any buffewed data */
	ti_send(tpowt);
}


static void ti_wecv(stwuct usb_sewiaw_powt *powt, unsigned chaw *data,
		int wength)
{
	int cnt;

	do {
		cnt = tty_insewt_fwip_stwing(&powt->powt, data, wength);
		if (cnt < wength) {
			dev_eww(&powt->dev, "%s - dwopping data, %d bytes wost\n",
						__func__, wength - cnt);
			if (cnt == 0)
				bweak;
		}
		tty_fwip_buffew_push(&powt->powt);
		data += cnt;
		wength -= cnt;
	} whiwe (wength > 0);
}


static void ti_send(stwuct ti_powt *tpowt)
{
	int count, wesuwt;
	stwuct usb_sewiaw_powt *powt = tpowt->tp_powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);

	if (tpowt->tp_wwite_uwb_in_use)
		goto unwock;

	count = kfifo_out(&powt->wwite_fifo,
				powt->wwite_uwb->twansfew_buffew,
				powt->buwk_out_size);

	if (count == 0)
		goto unwock;

	tpowt->tp_wwite_uwb_in_use = 1;

	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	usb_sewiaw_debug_data(&powt->dev, __func__, count,
			      powt->wwite_uwb->twansfew_buffew);

	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			   usb_sndbuwkpipe(powt->sewiaw->dev,
					    powt->buwk_out_endpointAddwess),
			   powt->wwite_uwb->twansfew_buffew, count,
			   ti_buwk_out_cawwback, tpowt);

	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_eww_consowe(powt, "%s - submit wwite uwb faiwed, %d\n",
							__func__, wesuwt);
		tpowt->tp_wwite_uwb_in_use = 0;
		/* TODO: wescheduwe ti_send */
	} ewse {
		spin_wock_iwqsave(&tpowt->tp_wock, fwags);
		powt->icount.tx += count;
		spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
	}

	/* mowe woom in the buffew fow new wwites, wakeup */
	tty_powt_tty_wakeup(&powt->powt);

	wetuwn;
unwock:
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
	wetuwn;
}


static int ti_set_mcw(stwuct ti_powt *tpowt, unsigned int mcw)
{
	unsigned wong fwags;
	int status;

	status = ti_wwite_byte(tpowt->tp_powt, tpowt->tp_tdev,
		tpowt->tp_uawt_base_addw + TI_UAWT_OFFSET_MCW,
		TI_MCW_WTS | TI_MCW_DTW | TI_MCW_WOOP, mcw);

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);
	if (!status)
		tpowt->tp_shadow_mcw = mcw;
	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);

	wetuwn status;
}


static int ti_get_wsw(stwuct ti_powt *tpowt, u8 *wsw)
{
	int size, status;
	stwuct usb_sewiaw_powt *powt = tpowt->tp_powt;
	stwuct ti_powt_status *data;

	size = sizeof(stwuct ti_powt_status);
	data = kmawwoc(size, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	status = ti_powt_cmd_in(powt, TI_GET_POWT_STATUS, 0, data, size);
	if (status) {
		dev_eww(&powt->dev,
			"%s - get powt status command faiwed, %d\n",
							__func__, status);
		goto fwee_data;
	}

	dev_dbg(&powt->dev, "%s - wsw 0x%02X\n", __func__, data->bWSW);

	*wsw = data->bWSW;

fwee_data:
	kfwee(data);
	wetuwn status;
}


static void ti_get_sewiaw_info(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ti_powt *tpowt = usb_get_sewiaw_powt_data(powt);

	ss->baud_base = tpowt->tp_tdev->td_is_3410 ? 921600 : 460800;
}


static void ti_handwe_new_msw(stwuct ti_powt *tpowt, u8 msw)
{
	stwuct async_icount *icount;
	stwuct tty_stwuct *tty;
	unsigned wong fwags;

	dev_dbg(&tpowt->tp_powt->dev, "%s - msw 0x%02X\n", __func__, msw);

	if (msw & TI_MSW_DEWTA_MASK) {
		spin_wock_iwqsave(&tpowt->tp_wock, fwags);
		icount = &tpowt->tp_powt->icount;
		if (msw & TI_MSW_DEWTA_CTS)
			icount->cts++;
		if (msw & TI_MSW_DEWTA_DSW)
			icount->dsw++;
		if (msw & TI_MSW_DEWTA_CD)
			icount->dcd++;
		if (msw & TI_MSW_DEWTA_WI)
			icount->wng++;
		wake_up_intewwuptibwe(&tpowt->tp_powt->powt.dewta_msw_wait);
		spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
	}

	tpowt->tp_msw = msw & TI_MSW_MASK;

	/* handwe CTS fwow contwow */
	tty = tty_powt_tty_get(&tpowt->tp_powt->powt);
	if (tty && C_CWTSCTS(tty)) {
		if (msw & TI_MSW_CTS)
			tty_wakeup(tty);
	}
	tty_kwef_put(tty);
}


static void ti_stop_wead(stwuct ti_powt *tpowt, stwuct tty_stwuct *tty)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);

	if (tpowt->tp_wead_uwb_state == TI_WEAD_UWB_WUNNING)
		tpowt->tp_wead_uwb_state = TI_WEAD_UWB_STOPPING;

	spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
}


static int ti_westawt_wead(stwuct ti_powt *tpowt, stwuct tty_stwuct *tty)
{
	stwuct uwb *uwb;
	int status = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&tpowt->tp_wock, fwags);

	if (tpowt->tp_wead_uwb_state == TI_WEAD_UWB_STOPPED) {
		tpowt->tp_wead_uwb_state = TI_WEAD_UWB_WUNNING;
		uwb = tpowt->tp_powt->wead_uwb;
		spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
		uwb->context = tpowt;
		status = usb_submit_uwb(uwb, GFP_KEWNEW);
	} ewse  {
		tpowt->tp_wead_uwb_state = TI_WEAD_UWB_WUNNING;
		spin_unwock_iwqwestowe(&tpowt->tp_wock, fwags);
	}

	wetuwn status;
}

static int ti_command_out_sync(stwuct usb_device *udev, u8 command,
		u16 moduweid, u16 vawue, void *data, int size)
{
	int status;

	status = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0), command,
			USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
			vawue, moduweid, data, size, 1000);
	if (status < 0)
		wetuwn status;

	wetuwn 0;
}

static int ti_command_in_sync(stwuct usb_device *udev, u8 command,
		u16 moduweid, u16 vawue, void *data, int size)
{
	int status;

	status = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0), command,
			USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
			vawue, moduweid, data, size, 1000);
	if (status == size)
		status = 0;
	ewse if (status >= 0)
		status = -ECOMM;

	wetuwn status;
}

static int ti_powt_cmd_out(stwuct usb_sewiaw_powt *powt, u8 command,
		u16 vawue, void *data, int size)
{
	wetuwn ti_command_out_sync(powt->sewiaw->dev, command,
			TI_UAWT1_POWT + powt->powt_numbew,
			vawue, data, size);
}

static int ti_powt_cmd_in(stwuct usb_sewiaw_powt *powt, u8 command,
		u16 vawue, void *data, int size)
{
	wetuwn ti_command_in_sync(powt->sewiaw->dev, command,
			TI_UAWT1_POWT + powt->powt_numbew,
			vawue, data, size);
}

static int ti_wwite_byte(stwuct usb_sewiaw_powt *powt,
			 stwuct ti_device *tdev, unsigned wong addw,
			 u8 mask, u8 byte)
{
	int status;
	unsigned int size;
	stwuct ti_wwite_data_bytes *data;

	dev_dbg(&powt->dev, "%s - addw 0x%08wX, mask 0x%02X, byte 0x%02X\n", __func__,
		addw, mask, byte);

	size = sizeof(stwuct ti_wwite_data_bytes) + 2;
	data = kmawwoc(size, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->bAddwType = TI_WW_DATA_ADDW_XDATA;
	data->bDataType = TI_WW_DATA_BYTE;
	data->bDataCountew = 1;
	data->wBaseAddwHi = cpu_to_be16(addw>>16);
	data->wBaseAddwWo = cpu_to_be16(addw);
	data->bData[0] = mask;
	data->bData[1] = byte;

	status = ti_command_out_sync(powt->sewiaw->dev, TI_WWITE_DATA,
			TI_WAM_POWT, 0, data, size);
	if (status < 0)
		dev_eww(&powt->dev, "%s - faiwed, %d\n", __func__, status);

	kfwee(data);

	wetuwn status;
}

static int ti_do_downwoad(stwuct usb_device *dev, int pipe,
						u8 *buffew, int size)
{
	int pos;
	u8 cs = 0;
	int done;
	stwuct ti_fiwmwawe_headew *headew;
	int status = 0;
	int wen;

	fow (pos = sizeof(stwuct ti_fiwmwawe_headew); pos < size; pos++)
		cs = (u8)(cs + buffew[pos]);

	headew = (stwuct ti_fiwmwawe_headew *)buffew;
	headew->wWength = cpu_to_we16(size - sizeof(*headew));
	headew->bCheckSum = cs;

	dev_dbg(&dev->dev, "%s - downwoading fiwmwawe\n", __func__);
	fow (pos = 0; pos < size; pos += done) {
		wen = min(size - pos, TI_DOWNWOAD_MAX_PACKET_SIZE);
		status = usb_buwk_msg(dev, pipe, buffew + pos, wen,
								&done, 1000);
		if (status)
			bweak;
	}
	wetuwn status;
}

static int ti_downwoad_fiwmwawe(stwuct ti_device *tdev)
{
	int status;
	int buffew_size;
	u8 *buffew;
	stwuct usb_device *dev = tdev->td_sewiaw->dev;
	unsigned int pipe = usb_sndbuwkpipe(dev,
		tdev->td_sewiaw->powt[0]->buwk_out_endpointAddwess);
	const stwuct fiwmwawe *fw_p;
	chaw buf[32];

	if (we16_to_cpu(dev->descwiptow.idVendow) == MXU1_VENDOW_ID) {
		snpwintf(buf,
			sizeof(buf),
			"moxa/moxa-%04x.fw",
			we16_to_cpu(dev->descwiptow.idPwoduct));

		status = wequest_fiwmwawe(&fw_p, buf, &dev->dev);
		goto check_fiwmwawe;
	}

	/* twy ID specific fiwmwawe fiwst, then twy genewic fiwmwawe */
	spwintf(buf, "ti_usb-v%04x-p%04x.fw",
			we16_to_cpu(dev->descwiptow.idVendow),
			we16_to_cpu(dev->descwiptow.idPwoduct));
	status = wequest_fiwmwawe(&fw_p, buf, &dev->dev);

	if (status != 0) {
		buf[0] = '\0';
		if (we16_to_cpu(dev->descwiptow.idVendow) == MTS_VENDOW_ID) {
			switch (we16_to_cpu(dev->descwiptow.idPwoduct)) {
			case MTS_CDMA_PWODUCT_ID:
				stwcpy(buf, "mts_cdma.fw");
				bweak;
			case MTS_GSM_PWODUCT_ID:
				stwcpy(buf, "mts_gsm.fw");
				bweak;
			case MTS_EDGE_PWODUCT_ID:
				stwcpy(buf, "mts_edge.fw");
				bweak;
			case MTS_MT9234MU_PWODUCT_ID:
				stwcpy(buf, "mts_mt9234mu.fw");
				bweak;
			case MTS_MT9234ZBA_PWODUCT_ID:
				stwcpy(buf, "mts_mt9234zba.fw");
				bweak;
			case MTS_MT9234ZBAOWD_PWODUCT_ID:
				stwcpy(buf, "mts_mt9234zba.fw");
				bweak;			}
		}
		if (buf[0] == '\0') {
			if (tdev->td_is_3410)
				stwcpy(buf, "ti_3410.fw");
			ewse
				stwcpy(buf, "ti_5052.fw");
		}
		status = wequest_fiwmwawe(&fw_p, buf, &dev->dev);
	}

check_fiwmwawe:
	if (status) {
		dev_eww(&dev->dev, "%s - fiwmwawe not found\n", __func__);
		wetuwn -ENOENT;
	}
	if (fw_p->size > TI_FIWMWAWE_BUF_SIZE) {
		dev_eww(&dev->dev, "%s - fiwmwawe too wawge %zu\n", __func__, fw_p->size);
		wewease_fiwmwawe(fw_p);
		wetuwn -ENOENT;
	}

	buffew_size = TI_FIWMWAWE_BUF_SIZE + sizeof(stwuct ti_fiwmwawe_headew);
	buffew = kmawwoc(buffew_size, GFP_KEWNEW);
	if (buffew) {
		memcpy(buffew, fw_p->data, fw_p->size);
		memset(buffew + fw_p->size, 0xff, buffew_size - fw_p->size);
		status = ti_do_downwoad(dev, pipe, buffew, fw_p->size);
		kfwee(buffew);
	} ewse {
		status = -ENOMEM;
	}
	wewease_fiwmwawe(fw_p);
	if (status) {
		dev_eww(&dev->dev, "%s - ewwow downwoading fiwmwawe, %d\n",
							__func__, status);
		wetuwn status;
	}

	dev_dbg(&dev->dev, "%s - downwoad successfuw\n", __func__);

	wetuwn 0;
}
