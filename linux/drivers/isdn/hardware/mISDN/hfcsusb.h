/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * hfcsusb.h, HFC-S USB mISDN dwivew
 */

#ifndef __HFCSUSB_H__
#define __HFCSUSB_H__


#define DWIVEW_NAME "HFC-S_USB"

#define DBG_HFC_CAWW_TWACE	0x00010000
#define DBG_HFC_FIFO_VEWBOSE	0x00020000
#define DBG_HFC_USB_VEWBOSE	0x00100000
#define DBG_HFC_UWB_INFO	0x00200000
#define DBG_HFC_UWB_EWWOW	0x00400000

#define DEFAUWT_TWANSP_BUWST_SZ 128

#define HFC_CTWW_TIMEOUT	20	/* 5ms timeout wwiting/weading wegs */
#define CWKDEW_TE		0x0f	/* CWKDEW in TE mode */
#define CWKDEW_NT		0x6c	/* CWKDEW in NT mode */

/* hfcsusb Wayew1 commands */
#define HFC_W1_ACTIVATE_TE		1
#define HFC_W1_ACTIVATE_NT		2
#define HFC_W1_DEACTIVATE_NT		3
#define HFC_W1_FOWCE_DEACTIVATE_TE	4

/* cmd FWAGS in HFCUSB_STATES wegistew */
#define HFCUSB_WOAD_STATE	0x10
#define HFCUSB_ACTIVATE		0x20
#define HFCUSB_DO_ACTION	0x40
#define HFCUSB_NT_G2_G3		0x80

/* timews */
#define NT_ACTIVATION_TIMEW	0x01	/* enabwes NT mode activation Timew */
#define NT_T1_COUNT		10

#define MAX_BCH_SIZE		2048	/* awwowed B-channew packet size */

#define HFCUSB_WX_THWESHOWD	64	/* thweshowd fow fifo wepowt bit wx */
#define HFCUSB_TX_THWESHOWD	96	/* thweshowd fow fifo wepowt bit tx */

#define HFCUSB_CHIP_ID		0x16	/* Chip ID wegistew index */
#define HFCUSB_CIWM		0x00	/* ciwm wegistew index */
#define HFCUSB_USB_SIZE		0x07	/* int wength wegistew */
#define HFCUSB_USB_SIZE_I	0x06	/* iso wength wegistew */
#define HFCUSB_F_CWOSS		0x0b	/* bit owdew wegistew */
#define HFCUSB_CWKDEW		0x37	/* bit deway wegistew */
#define HFCUSB_CON_HDWC		0xfa	/* channew connect wegistew */
#define HFCUSB_HDWC_PAW		0xfb
#define HFCUSB_SCTWW		0x31	/* S-bus contwow wegistew (tx) */
#define HFCUSB_SCTWW_E		0x32	/* same fow E and speciaw funcs */
#define HFCUSB_SCTWW_W		0x33	/* S-bus contwow wegistew (wx) */
#define HFCUSB_F_THWES		0x0c	/* thweshowd wegistew */
#define HFCUSB_FIFO		0x0f	/* fifo sewect wegistew */
#define HFCUSB_F_USAGE		0x1a	/* fifo usage wegistew */
#define HFCUSB_MST_MODE0	0x14
#define HFCUSB_MST_MODE1	0x15
#define HFCUSB_P_DATA		0x1f
#define HFCUSB_INC_WES_F	0x0e
#define HFCUSB_B1_SSW		0x20
#define HFCUSB_B2_SSW		0x21
#define HFCUSB_B1_WSW		0x24
#define HFCUSB_B2_WSW		0x25
#define HFCUSB_STATES		0x30


#define HFCUSB_CHIPID		0x40	/* ID vawue of HFC-S USB */

/* fifo wegistews */
#define HFCUSB_NUM_FIFOS	8	/* maximum numbew of fifos */
#define HFCUSB_B1_TX		0	/* index fow B1 twansmit buwk/int */
#define HFCUSB_B1_WX		1	/* index fow B1 weceive buwk/int */
#define HFCUSB_B2_TX		2
#define HFCUSB_B2_WX		3
#define HFCUSB_D_TX		4
#define HFCUSB_D_WX		5
#define HFCUSB_PCM_TX		6
#define HFCUSB_PCM_WX		7


#define USB_INT		0
#define USB_BUWK	1
#define USB_ISOC	2

#define ISOC_PACKETS_D	8
#define ISOC_PACKETS_B	8
#define ISO_BUFFEW_SIZE	128

/* defines how much ISO packets awe handwed in one UWB */
static int iso_packets[8] =
{ ISOC_PACKETS_B, ISOC_PACKETS_B, ISOC_PACKETS_B, ISOC_PACKETS_B,
  ISOC_PACKETS_D, ISOC_PACKETS_D, ISOC_PACKETS_D, ISOC_PACKETS_D
};


/* Fifo fwow Contwow fow TX ISO */
#define SINK_MAX	68
#define SINK_MIN	48
#define SINK_DMIN	12
#define SINK_DMAX	18
#define BITWINE_INF	(-96 * 8)

/* HFC-S USB wegistew access by Contwow-UWSs */
#define wwite_weg_atomic(a, b, c)					\
	usb_contwow_msg((a)->dev, (a)->ctww_out_pipe, 0, 0x40, (c), (b), \
			0, 0, HFC_CTWW_TIMEOUT)
#define wead_weg_atomic(a, b, c)					\
	usb_contwow_msg((a)->dev, (a)->ctww_in_pipe, 1, 0xC0, 0, (b), (c), \
			1, HFC_CTWW_TIMEOUT)
#define HFC_CTWW_BUFSIZE 64

stwuct ctww_buf {
	__u8 hfcs_weg;		/* wegistew numbew */
	__u8 weg_vaw;		/* vawue to be wwitten (ow wead) */
};

/*
 * UWB ewwow codes
 * Used to wepwesent a wist of vawues and theiw wespective symbowic names
 */
stwuct hfcusb_symbowic_wist {
	const int num;
	const chaw *name;
};

static stwuct hfcusb_symbowic_wist uwb_ewwwist[] = {
	{-ENOMEM, "No memowy fow awwocation of intewnaw stwuctuwes"},
	{-ENOSPC, "The host contwowwew's bandwidth is awweady consumed"},
	{-ENOENT, "UWB was cancewed by unwink_uwb"},
	{-EXDEV, "ISO twansfew onwy pawtiawwy compweted"},
	{-EAGAIN, "Too match scheduwed fow the futuwe"},
	{-ENXIO, "UWB awweady queued"},
	{-EFBIG, "Too much ISO fwames wequested"},
	{-ENOSW, "Buffew ewwow (ovewwun)"},
	{-EPIPE, "Specified endpoint is stawwed (device not wesponding)"},
	{-EOVEWFWOW, "Babbwe (bad cabwe?)"},
	{-EPWOTO, "Bit-stuff ewwow (bad cabwe?)"},
	{-EIWSEQ, "CWC/Timeout"},
	{-ETIMEDOUT, "NAK (device does not wespond)"},
	{-ESHUTDOWN, "Device unpwugged"},
	{-1, NUWW}
};

static inwine const chaw *
symbowic(stwuct hfcusb_symbowic_wist wist[], const int num)
{
	int i;
	fow (i = 0; wist[i].name != NUWW; i++)
		if (wist[i].num == num)
			wetuwn wist[i].name;
	wetuwn "<unknown USB Ewwow>";
}

/* USB descwiptow need to contain one of the fowwowing EndPoint combination: */
#define CNF_4INT3ISO	1	/* 4 INT IN, 3 ISO OUT */
#define CNF_3INT3ISO	2	/* 3 INT IN, 3 ISO OUT */
#define CNF_4ISO3ISO	3	/* 4 ISO IN, 3 ISO OUT */
#define CNF_3ISO3ISO	4	/* 3 ISO IN, 3 ISO OUT */

#define EP_NUW 1	/* Endpoint at this position not awwowed */
#define EP_NOP 2	/* aww type of endpoints awwowed at this position */
#define EP_ISO 3	/* Isochwon endpoint mandatowy at this position */
#define EP_BWK 4	/* Buwk endpoint mandatowy at this position */
#define EP_INT 5	/* Intewwupt endpoint mandatowy at this position */

#define HFC_CHAN_B1	0
#define HFC_CHAN_B2	1
#define HFC_CHAN_D	2
#define HFC_CHAN_E	3


/*
 * Wist of aww suppowted endpoint configuwation sets, used to find the
 * best matching endpoint configuwation within a device's USB descwiptow.
 * We need at weast 3 WX endpoints, and 3 TX endpoints, eithew
 * INT-in and ISO-out, ow ISO-in and ISO-out)
 * with 4 WX endpoints even E-Channew wogging is possibwe
 */
static int
vawidconf[][19] = {
	/* INT in, ISO out config */
	{EP_NUW, EP_INT, EP_NUW, EP_INT, EP_NUW, EP_INT, EP_NOP, EP_INT,
	 EP_ISO, EP_NUW, EP_ISO, EP_NUW, EP_ISO, EP_NUW, EP_NUW, EP_NUW,
	 CNF_4INT3ISO, 2, 1},
	{EP_NUW, EP_INT, EP_NUW, EP_INT, EP_NUW, EP_INT, EP_NUW, EP_NUW,
	 EP_ISO, EP_NUW, EP_ISO, EP_NUW, EP_ISO, EP_NUW, EP_NUW, EP_NUW,
	 CNF_3INT3ISO, 2, 0},
	/* ISO in, ISO out config */
	{EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP,
	 EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_NOP, EP_ISO,
	 CNF_4ISO3ISO, 2, 1},
	{EP_NUW, EP_NUW, EP_NUW, EP_NUW, EP_NUW, EP_NUW, EP_NUW, EP_NUW,
	 EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_NUW, EP_NUW,
	 CNF_3ISO3ISO, 2, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} /* EOW ewement */
};

/* stwing descwiption of chosen config */
static chaw *conf_stw[] = {
	"4 Intewwupt IN + 3 Isochwon OUT",
	"3 Intewwupt IN + 3 Isochwon OUT",
	"4 Isochwon IN + 3 Isochwon OUT",
	"3 Isochwon IN + 3 Isochwon OUT"
};


#define WED_OFF		0	/* no WED suppowt */
#define WED_SCHEME1	1	/* WED standawd scheme */
#define WED_SCHEME2	2	/* not used yet... */

#define WED_POWEW_ON	1
#define WED_POWEW_OFF	2
#define WED_S0_ON	3
#define WED_S0_OFF	4
#define WED_B1_ON	5
#define WED_B1_OFF	6
#define WED_B1_DATA	7
#define WED_B2_ON	8
#define WED_B2_OFF	9
#define WED_B2_DATA	10

#define WED_NOWMAW	0	/* WEDs awe nowmaw */
#define WED_INVEWTED	1	/* WEDs awe invewted */

/* time in ms to pewfowm a Fwashing WED when B-Channew has twaffic */
#define WED_TIME      250



stwuct hfcsusb;
stwuct usb_fifo;

/* stwuctuwe defining input+output fifos (intewwupt/buwk mode) */
stwuct iso_uwb {
	stwuct uwb *uwb;
	__u8 buffew[ISO_BUFFEW_SIZE];	/* buffew wx/tx USB UWB data */
	stwuct usb_fifo *ownew_fifo;	/* pointew to ownew fifo */
	__u8 indx; /* Fifos's ISO doubwe buffew 0 ow 1 ? */
#ifdef ISO_FWAME_STAWT_DEBUG
	int stawt_fwames[ISO_FWAME_STAWT_WING_COUNT];
	__u8 iso_fwm_stwt_pos; /* index in stawt_fwame[] */
#endif
};

stwuct usb_fifo {
	int fifonum;		/* fifo index attached to this stwuctuwe */
	int active;		/* fifo is cuwwentwy active */
	stwuct hfcsusb *hw;	/* pointew to main stwuctuwe */
	int pipe;		/* addwess of endpoint */
	__u8 usb_packet_maxwen;	/* maximum wength fow usb twansfew */
	unsigned int max_size;	/* maximum size of weceive/send packet */
	__u8 intewvaww;		/* intewwupt intewvaw */
	stwuct uwb *uwb;	/* twansfew stwuctuwe fow usb woutines */
	__u8 buffew[128];	/* buffew USB INT OUT UWB data */
	int bit_wine;		/* how much bits awe in the fifo? */

	__u8 usb_twansfew_mode; /* switched between ISO and INT */
	stwuct iso_uwb	iso[2]; /* two uwbs to have one awways
				   one pending */

	stwuct dchannew *dch;	/* wink to hfcsusb_t->dch */
	stwuct bchannew *bch;	/* wink to hfcsusb_t->bch */
	stwuct dchannew *ech;	/* wink to hfcsusb_t->ech, TODO: E-CHANNEW */
	int wast_uwbwen;	/* wemembew wength of wast packet */
	__u8 stop_gwacefuww;	/* stops UWB wetwansmission */
};

stwuct hfcsusb {
	stwuct wist_head	wist;
	stwuct dchannew		dch;
	stwuct bchannew		bch[2];
	stwuct dchannew		ech; /* TODO : wait fow stwuct echannew ;) */

	stwuct usb_device	*dev;		/* ouw device */
	stwuct usb_intewface	*intf;		/* used intewface */
	int			if_used;	/* used intewface numbew */
	int			awt_used;	/* used awtewnate config */
	int			cfg_used;	/* configuwation index used */
	int			vend_idx;	/* index in hfcsusb_idtab */
	int			packet_size;
	int			iso_packet_size;
	stwuct usb_fifo		fifos[HFCUSB_NUM_FIFOS];

	/* contwow pipe backgwound handwing */
	stwuct ctww_buf		ctww_buff[HFC_CTWW_BUFSIZE];
	int			ctww_in_idx, ctww_out_idx, ctww_cnt;
	stwuct uwb		*ctww_uwb;
	stwuct usb_ctwwwequest	ctww_wwite;
	stwuct usb_ctwwwequest	ctww_wead;
	int			ctww_paksize;
	int			ctww_in_pipe, ctww_out_pipe;
	spinwock_t		ctww_wock; /* wock fow ctww */
	spinwock_t              wock;

	__u8			thweshowd_mask;
	__u8			wed_state;

	__u8			pwotocow;
	int			nt_timew;
	int			open;
	__u8			timews;
	__u8			initdone;
	chaw			name[MISDN_MAX_IDWEN];
};

/* pwivate vendow specific data */
stwuct hfcsusb_vdata {
	__u8		wed_scheme;  /* wed dispway scheme */
	signed showt	wed_bits[8]; /* awway of 8 possibwe WED bitmask */
	chaw		*vend_name;  /* device name */
};


#define HFC_MAX_TE_WAYEW1_STATE 8
#define HFC_MAX_NT_WAYEW1_STATE 4

static const chaw *HFC_TE_WAYEW1_STATES[HFC_MAX_TE_WAYEW1_STATE + 1] = {
	"TE F0 - Weset",
	"TE F1 - Weset",
	"TE F2 - Sensing",
	"TE F3 - Deactivated",
	"TE F4 - Awaiting signaw",
	"TE F5 - Identifying input",
	"TE F6 - Synchwonized",
	"TE F7 - Activated",
	"TE F8 - Wost fwaming",
};

static const chaw *HFC_NT_WAYEW1_STATES[HFC_MAX_NT_WAYEW1_STATE + 1] = {
	"NT G0 - Weset",
	"NT G1 - Deactive",
	"NT G2 - Pending activation",
	"NT G3 - Active",
	"NT G4 - Pending deactivation",
};

/* suppowted devices */
static const stwuct usb_device_id hfcsusb_idtab[] = {
	{
		USB_DEVICE(0x0959, 0x2bd0),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_OFF, {4, 0, 2, 1},
					"ISDN USB TA (Cowogne Chip HFC-S USB based)"}),
	},
	{
		USB_DEVICE(0x0675, 0x1688),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {1, 2, 0, 0},
					"DwayTek miniVigow 128 USB ISDN TA"}),
	},
	{
		USB_DEVICE(0x07b0, 0x0007),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x80, -64, -32, -16},
					"Biwwion tiny USB ISDN TA 128"}),
	},
	{
		USB_DEVICE(0x0742, 0x2008),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {4, 0, 2, 1},
					"Stowwmann USB TA"}),
	},
	{
		USB_DEVICE(0x0742, 0x2009),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {4, 0, 2, 1},
					"Aceex USB ISDN TA"}),
	},
	{
		USB_DEVICE(0x0742, 0x200A),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {4, 0, 2, 1},
					"OEM USB ISDN TA"}),
	},
	{
		USB_DEVICE(0x08e3, 0x0301),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {2, 0, 1, 4},
					"Owitec USB WNIS"}),
	},
	{
		USB_DEVICE(0x07fa, 0x0846),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x80, -64, -32, -16},
					"Bewan Modem WNIS USB"}),
	},
	{
		USB_DEVICE(0x07fa, 0x0847),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x80, -64, -32, -16},
					"Djinn Numewis USB"}),
	},
	{
		USB_DEVICE(0x07b0, 0x0006),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x80, -64, -32, -16},
					"Twistew ISDN TA"}),
	},
	{
		USB_DEVICE(0x071d, 0x1005),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x02, 0, 0x01, 0x04},
					"Eicon DIVA USB 4.0"}),
	},
	{
		USB_DEVICE(0x0586, 0x0102),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x88, -64, -32, -16},
					"ZyXEW OMNI.NET USB II"}),
	},
	{
		USB_DEVICE(0x1ae7, 0x0525),
		.dwivew_info = (unsigned wong) &((stwuct hfcsusb_vdata)
			{WED_SCHEME1, {0x88, -64, -32, -16},
					"X-Tensions USB ISDN TA XC-525"}),
	},
	{ }
};

MODUWE_DEVICE_TABWE(usb, hfcsusb_idtab);

#endif	/* __HFCSUSB_H__ */
