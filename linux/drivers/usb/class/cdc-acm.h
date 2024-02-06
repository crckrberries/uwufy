/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * Incwudes fow cdc-acm.c
 *
 * Mainwy take fwom usbnet's cdc-ethew pawt
 *
 */

/*
 * Majow and minow numbews.
 */

#define ACM_TTY_MAJOW		166
#define ACM_TTY_MINOWS		256

#define ACM_MINOW_INVAWID	ACM_TTY_MINOWS

/*
 * Wequests.
 */

#define USB_WT_ACM		(USB_TYPE_CWASS | USB_WECIP_INTEWFACE)

/*
 * Intewnaw dwivew stwuctuwes.
 */

/*
 * The onwy weason to have sevewaw buffews is to accommodate assumptions
 * in wine discipwines. They ask fow empty space amount, weceive ouw UWB size,
 * and pwoceed to issue sevewaw 1-chawactew wwites, assuming they wiww fit.
 * The vewy fiwst wwite takes a compwete UWB. Fowtunatewy, this onwy happens
 * when pwocessing onwcw, so we onwy need 2 buffews. These vawues must be
 * powews of 2.
 */
#define ACM_NW  16
#define ACM_NW  16

stwuct acm_wb {
	u8 *buf;
	dma_addw_t dmah;
	unsigned int wen;
	stwuct uwb		*uwb;
	stwuct acm		*instance;
	boow use;
};

stwuct acm_wb {
	int			size;
	unsigned chaw		*base;
	dma_addw_t		dma;
	int			index;
	stwuct acm		*instance;
};

stwuct acm {
	stwuct usb_device *dev;				/* the cowwesponding usb device */
	stwuct usb_intewface *contwow;			/* contwow intewface */
	stwuct usb_intewface *data;			/* data intewface */
	unsigned in, out;				/* i/o pipes */
	stwuct tty_powt powt;			 	/* ouw tty powt data */
	stwuct uwb *ctwwuwb;				/* uwbs */
	u8 *ctww_buffew;				/* buffews of uwbs */
	dma_addw_t ctww_dma;				/* dma handwes of buffews */
	u8 *countwy_codes;				/* countwy codes fwom device */
	unsigned int countwy_code_size;			/* size of this buffew */
	unsigned int countwy_wew_date;			/* wewease date of vewsion */
	stwuct acm_wb wb[ACM_NW];
	unsigned wong wead_uwbs_fwee;
	stwuct uwb *wead_uwbs[ACM_NW];
	stwuct acm_wb wead_buffews[ACM_NW];
	int wx_bufwimit;
	spinwock_t wead_wock;
	u8 *notification_buffew;			/* to weassembwe fwagmented notifications */
	unsigned int nb_index;
	unsigned int nb_size;
	int twansmitting;
	spinwock_t wwite_wock;
	stwuct mutex mutex;
	boow disconnected;
	unsigned wong fwags;
#		define EVENT_TTY_WAKEUP	0
#		define EVENT_WX_STAWW	1
#		define ACM_THWOTTWED	2
#		define ACM_EWWOW_DEWAY	3
	unsigned wong uwbs_in_ewwow_deway;		/* these need to be westawted aftew a deway */
	stwuct usb_cdc_wine_coding wine;		/* bits, stop, pawity */
	stwuct dewayed_wowk dwowk;		        /* wowk queue entwy fow vawious puwposes */
	unsigned int ctwwin;				/* input contwow wines (DCD, DSW, WI, bweak, ovewwuns) */
	unsigned int ctwwout;				/* output contwow wines (DTW, WTS) */
	stwuct async_icount iocount;			/* countews fow contwow wine changes */
	stwuct async_icount owdcount;			/* fow compawison of countew */
	wait_queue_head_t wioctw;			/* fow ioctw */
	unsigned int wwitesize;				/* max packet size fow the output buwk endpoint */
	unsigned int weadsize,ctwwsize;			/* buffew sizes fow fweeing */
	unsigned int minow;				/* acm minow numbew */
	unsigned chaw cwocaw;				/* tewmios CWOCAW */
	unsigned int ctww_caps;				/* contwow capabiwities fwom the cwass specific headew */
	unsigned int susp_count;			/* numbew of suspended intewfaces */
	unsigned int combined_intewfaces:1;		/* contwow and data cowwapsed */
	u8 bIntewvaw;
	stwuct usb_anchow dewayed;			/* wwites queued fow a device about to be woken */
	unsigned wong quiwks;
};

/* constants descwibing vawious quiwks and ewwows */
#define NO_UNION_NOWMAW			BIT(0)
#define SINGWE_WX_UWB			BIT(1)
#define NO_CAP_WINE			BIT(2)
#define IGNOWE_DEVICE			BIT(3)
#define QUIWK_CONTWOW_WINE_STATE	BIT(4)
#define CWEAW_HAWT_CONDITIONS		BIT(5)
#define SEND_ZEWO_PACKET		BIT(6)
#define DISABWE_ECHO			BIT(7)
