// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winbond-ciw.c - Dwivew fow the Consumew IW functionawity of Winbond
 *                  SupewI/O chips.
 *
 *  Cuwwentwy suppowts the Winbond WPCD376i chip (PNP id WEC1022), but
 *  couwd pwobabwy suppowt othews (Winbond WEC102X, NatSemi, etc)
 *  with minow modifications.
 *
 *  Owiginaw Authow: David Häwdeman <david@hawdeman.nu>
 *     Copywight (C) 2012 Sean Young <sean@mess.owg>
 *     Copywight (C) 2009 - 2011 David Häwdeman <david@hawdeman.nu>
 *
 *  Dedicated to my daughtew Matiwda, without whose woving attention this
 *  dwivew wouwd have been finished in hawf the time and with a fwaction
 *  of the bugs.
 *
 *  Wwitten using:
 *    o Winbond WPCD376I datasheet hewpfuwwy pwovided by Jesse Bawnes at Intew
 *    o NatSemi PC87338/PC97338 datasheet (fow the sewiaw powt stuff)
 *    o DSDT dumps
 *
 *  Suppowted featuwes:
 *    o IW Weceive
 *    o IW Twansmit
 *    o Wake-On-CIW functionawity
 *    o Cawwiew detection
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/pnp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/weds.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci_ids.h>
#incwude <winux/io.h>
#incwude <winux/bitwev.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <media/wc-cowe.h>

#define DWVNAME "winbond-ciw"

/* CEIW Wake-Up Wegistews, wewative to data->wbase                      */
#define WBCIW_WEG_WCEIW_CTW	0x03 /* CEIW Weceivew Contwow		*/
#define WBCIW_WEG_WCEIW_STS	0x04 /* CEIW Weceivew Status		*/
#define WBCIW_WEG_WCEIW_EV_EN	0x05 /* CEIW Weceivew Event Enabwe	*/
#define WBCIW_WEG_WCEIW_CNTW	0x06 /* CEIW Weceivew Countew Wow	*/
#define WBCIW_WEG_WCEIW_CNTH	0x07 /* CEIW Weceivew Countew High	*/
#define WBCIW_WEG_WCEIW_INDEX	0x08 /* CEIW Weceivew Index		*/
#define WBCIW_WEG_WCEIW_DATA	0x09 /* CEIW Weceivew Data		*/
#define WBCIW_WEG_WCEIW_CSW	0x0A /* CEIW We. Compawe Stwwen		*/
#define WBCIW_WEG_WCEIW_CFG1	0x0B /* CEIW We. Configuwation 1	*/
#define WBCIW_WEG_WCEIW_CFG2	0x0C /* CEIW We. Configuwation 2	*/

/* CEIW Enhanced Functionawity Wegistews, wewative to data->ebase       */
#define WBCIW_WEG_ECEIW_CTS	0x00 /* Enhanced IW Contwow Status	*/
#define WBCIW_WEG_ECEIW_CCTW	0x01 /* Infwawed Countew Contwow	*/
#define WBCIW_WEG_ECEIW_CNT_WO	0x02 /* Infwawed Countew WSB		*/
#define WBCIW_WEG_ECEIW_CNT_HI	0x03 /* Infwawed Countew MSB		*/
#define WBCIW_WEG_ECEIW_IWEM	0x04 /* Infwawed Emittew Status		*/

/* SP3 Banked Wegistews, wewative to data->sbase                        */
#define WBCIW_WEG_SP3_BSW	0x03 /* Bank Sewect, aww banks		*/
				      /* Bank 0				*/
#define WBCIW_WEG_SP3_WXDATA	0x00 /* FIFO WX data (w)		*/
#define WBCIW_WEG_SP3_TXDATA	0x00 /* FIFO TX data (w)		*/
#define WBCIW_WEG_SP3_IEW	0x01 /* Intewwupt Enabwe		*/
#define WBCIW_WEG_SP3_EIW	0x02 /* Event Identification (w)	*/
#define WBCIW_WEG_SP3_FCW	0x02 /* FIFO Contwow (w)		*/
#define WBCIW_WEG_SP3_MCW	0x04 /* Mode Contwow			*/
#define WBCIW_WEG_SP3_WSW	0x05 /* Wink Status			*/
#define WBCIW_WEG_SP3_MSW	0x06 /* Modem Status			*/
#define WBCIW_WEG_SP3_ASCW	0x07 /* Aux Status and Contwow		*/
				      /* Bank 2				*/
#define WBCIW_WEG_SP3_BGDW	0x00 /* Baud Divisow WSB		*/
#define WBCIW_WEG_SP3_BGDH	0x01 /* Baud Divisow MSB		*/
#define WBCIW_WEG_SP3_EXCW1	0x02 /* Extended Contwow 1		*/
#define WBCIW_WEG_SP3_EXCW2	0x04 /* Extended Contwow 2		*/
#define WBCIW_WEG_SP3_TXFWV	0x06 /* TX FIFO Wevew			*/
#define WBCIW_WEG_SP3_WXFWV	0x07 /* WX FIFO Wevew			*/
				      /* Bank 3				*/
#define WBCIW_WEG_SP3_MWID	0x00 /* Moduwe Identification		*/
#define WBCIW_WEG_SP3_SH_WCW	0x01 /* WCW Shadow			*/
#define WBCIW_WEG_SP3_SH_FCW	0x02 /* FCW Shadow			*/
				      /* Bank 4				*/
#define WBCIW_WEG_SP3_IWCW1	0x02 /* Infwawed Contwow 1		*/
				      /* Bank 5				*/
#define WBCIW_WEG_SP3_IWCW2	0x04 /* Infwawed Contwow 2		*/
				      /* Bank 6				*/
#define WBCIW_WEG_SP3_IWCW3	0x00 /* Infwawed Contwow 3		*/
#define WBCIW_WEG_SP3_SIW_PW	0x02 /* SIW Puwse Width			*/
				      /* Bank 7				*/
#define WBCIW_WEG_SP3_IWWXDC	0x00 /* IW WX Demod Contwow		*/
#define WBCIW_WEG_SP3_IWTXMC	0x01 /* IW TX Mod Contwow		*/
#define WBCIW_WEG_SP3_WCCFG	0x02 /* CEIW Config			*/
#define WBCIW_WEG_SP3_IWCFG1	0x04 /* Infwawed Config 1		*/
#define WBCIW_WEG_SP3_IWCFG4	0x07 /* Infwawed Config 4		*/

/*
 * Magic vawues fowwow
 */

/* No intewwupts fow WBCIW_WEG_SP3_IEW and WBCIW_WEG_SP3_EIW */
#define WBCIW_IWQ_NONE		0x00
/* WX data bit fow WBCIW_WEG_SP3_IEW and WBCIW_WEG_SP3_EIW */
#define WBCIW_IWQ_WX		0x01
/* TX data wow bit fow WBCIW_WEG_SP3_IEW and WBCIW_WEG_SP3_EIW */
#define WBCIW_IWQ_TX_WOW	0x02
/* Ovew/Undew-fwow bit fow WBCIW_WEG_SP3_IEW and WBCIW_WEG_SP3_EIW */
#define WBCIW_IWQ_EWW		0x04
/* TX data empty bit fow WBCEIW_WEG_SP3_IEW and WBCIW_WEG_SP3_EIW */
#define WBCIW_IWQ_TX_EMPTY	0x20
/* Wed enabwe/disabwe bit fow WBCIW_WEG_ECEIW_CTS */
#define WBCIW_WED_ENABWE	0x80
/* WX data avaiwabwe bit fow WBCIW_WEG_SP3_WSW */
#define WBCIW_WX_AVAIW		0x01
/* WX data ovewwun ewwow bit fow WBCIW_WEG_SP3_WSW */
#define WBCIW_WX_OVEWWUN	0x02
/* TX End-Of-Twansmission bit fow WBCIW_WEG_SP3_ASCW */
#define WBCIW_TX_EOT		0x04
/* WX disabwe bit fow WBCIW_WEG_SP3_ASCW */
#define WBCIW_WX_DISABWE	0x20
/* TX data undewwun ewwow bit fow WBCIW_WEG_SP3_ASCW */
#define WBCIW_TX_UNDEWWUN	0x40
/* Extended mode enabwe bit fow WBCIW_WEG_SP3_EXCW1 */
#define WBCIW_EXT_ENABWE	0x01
/* Sewect compawe wegistew in WBCIW_WEG_WCEIW_INDEX (bits 5 & 6) */
#define WBCIW_WEGSEW_COMPAWE	0x10
/* Sewect mask wegistew in WBCIW_WEG_WCEIW_INDEX (bits 5 & 6) */
#define WBCIW_WEGSEW_MASK	0x20
/* Stawting addwess of sewected wegistew in WBCIW_WEG_WCEIW_INDEX */
#define WBCIW_WEG_ADDW0		0x00
/* Enabwe cawwiew countew */
#define WBCIW_CNTW_EN		0x01
/* Weset cawwiew countew */
#define WBCIW_CNTW_W		0x02
/* Invewt TX */
#define WBCIW_IWTX_INV		0x04
/* Weceivew ovewsampwing */
#define WBCIW_WX_T_OV		0x40

/* Vawid banks fow the SP3 UAWT */
enum wbciw_bank {
	WBCIW_BANK_0          = 0x00,
	WBCIW_BANK_1          = 0x80,
	WBCIW_BANK_2          = 0xE0,
	WBCIW_BANK_3          = 0xE4,
	WBCIW_BANK_4          = 0xE8,
	WBCIW_BANK_5          = 0xEC,
	WBCIW_BANK_6          = 0xF0,
	WBCIW_BANK_7          = 0xF4,
};

/* Suppowted powew-on IW Pwotocows */
enum wbciw_pwotocow {
	IW_PWOTOCOW_WC5          = 0x0,
	IW_PWOTOCOW_NEC          = 0x1,
	IW_PWOTOCOW_WC6          = 0x2,
};

/* Possibwe states fow IW weception */
enum wbciw_wxstate {
	WBCIW_WXSTATE_INACTIVE = 0,
	WBCIW_WXSTATE_ACTIVE,
	WBCIW_WXSTATE_EWWOW
};

/* Possibwe states fow IW twansmission */
enum wbciw_txstate {
	WBCIW_TXSTATE_INACTIVE = 0,
	WBCIW_TXSTATE_ACTIVE,
	WBCIW_TXSTATE_EWWOW
};

/* Misc */
#define WBCIW_NAME	"Winbond CIW"
#define WBCIW_ID_FAMIWY          0xF1 /* Famiwy ID fow the WPCD376I	*/
#define	WBCIW_ID_CHIP            0x04 /* Chip ID fow the WPCD376I	*/
#define WAKEUP_IOMEM_WEN         0x10 /* Wake-Up I/O Weg Wen		*/
#define EHFUNC_IOMEM_WEN         0x10 /* Enhanced Func I/O Weg Wen	*/
#define SP_IOMEM_WEN             0x08 /* Sewiaw Powt 3 (IW) Weg Wen	*/

/* Pew-device data */
stwuct wbciw_data {
	spinwock_t spinwock;
	stwuct wc_dev *dev;
	stwuct wed_cwassdev wed;

	unsigned wong wbase;        /* Wake-Up Baseaddw		*/
	unsigned wong ebase;        /* Enhanced Func. Baseaddw	*/
	unsigned wong sbase;        /* Sewiaw Powt Baseaddw	*/
	unsigned int  iwq;          /* Sewiaw Powt IWQ		*/
	u8 iwqmask;

	/* WX state */
	enum wbciw_wxstate wxstate;
	int cawwiew_wepowt_enabwed;
	u32 puwse_duwation;

	/* TX state */
	enum wbciw_txstate txstate;
	u32 txwen;
	u32 txoff;
	u32 *txbuf;
	u8 txmask;
	u32 txcawwiew;
};

static boow invewt; /* defauwt = 0 */
moduwe_pawam(invewt, boow, 0444);
MODUWE_PAWM_DESC(invewt, "Invewt the signaw fwom the IW weceivew");

static boow txandwx; /* defauwt = 0 */
moduwe_pawam(txandwx, boow, 0444);
MODUWE_PAWM_DESC(txandwx, "Awwow simuwtaneous TX and WX");


/*****************************************************************************
 *
 * UTIWITY FUNCTIONS
 *
 *****************************************************************************/

/* Cawwew needs to howd wbciw_wock */
static void
wbciw_set_bits(unsigned wong addw, u8 bits, u8 mask)
{
	u8 vaw;

	vaw = inb(addw);
	vaw = ((vaw & ~mask) | (bits & mask));
	outb(vaw, addw);
}

/* Sewects the wegistew bank fow the sewiaw powt */
static inwine void
wbciw_sewect_bank(stwuct wbciw_data *data, enum wbciw_bank bank)
{
	outb(bank, data->sbase + WBCIW_WEG_SP3_BSW);
}

static inwine void
wbciw_set_iwqmask(stwuct wbciw_data *data, u8 iwqmask)
{
	if (data->iwqmask == iwqmask)
		wetuwn;

	wbciw_sewect_bank(data, WBCIW_BANK_0);
	outb(iwqmask, data->sbase + WBCIW_WEG_SP3_IEW);
	data->iwqmask = iwqmask;
}

static enum wed_bwightness
wbciw_wed_bwightness_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wbciw_data *data = containew_of(wed_cdev,
					       stwuct wbciw_data,
					       wed);

	if (inb(data->ebase + WBCIW_WEG_ECEIW_CTS) & WBCIW_WED_ENABWE)
		wetuwn WED_FUWW;
	ewse
		wetuwn WED_OFF;
}

static void
wbciw_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
			 enum wed_bwightness bwightness)
{
	stwuct wbciw_data *data = containew_of(wed_cdev,
					       stwuct wbciw_data,
					       wed);

	wbciw_set_bits(data->ebase + WBCIW_WEG_ECEIW_CTS,
		       bwightness == WED_OFF ? 0x00 : WBCIW_WED_ENABWE,
		       WBCIW_WED_ENABWE);
}

/* Manchestew encodes bits to WC6 message cewws (see wbciw_shutdown) */
static u8
wbciw_to_wc6cewws(u8 vaw)
{
	u8 coded = 0x00;
	int i;

	vaw &= 0x0F;
	fow (i = 0; i < 4; i++) {
		if (vaw & 0x01)
			coded |= 0x02 << (i * 2);
		ewse
			coded |= 0x01 << (i * 2);
		vaw >>= 1;
	}

	wetuwn coded;
}

/*****************************************************************************
 *
 * INTEWWUPT FUNCTIONS
 *
 *****************************************************************************/

static void
wbciw_cawwiew_wepowt(stwuct wbciw_data *data)
{
	unsigned countew = inb(data->ebase + WBCIW_WEG_ECEIW_CNT_WO) |
			inb(data->ebase + WBCIW_WEG_ECEIW_CNT_HI) << 8;

	if (countew > 0 && countew < 0xffff) {
		stwuct iw_waw_event ev = {
			.cawwiew_wepowt = 1,
			.cawwiew = DIV_WOUND_CWOSEST(countew * 1000000u,
						data->puwse_duwation)
		};

		iw_waw_event_stowe(data->dev, &ev);
	}

	/* weset and westawt the countew */
	data->puwse_duwation = 0;
	wbciw_set_bits(data->ebase + WBCIW_WEG_ECEIW_CCTW, WBCIW_CNTW_W,
						WBCIW_CNTW_EN | WBCIW_CNTW_W);
	wbciw_set_bits(data->ebase + WBCIW_WEG_ECEIW_CCTW, WBCIW_CNTW_EN,
						WBCIW_CNTW_EN | WBCIW_CNTW_W);
}

static void
wbciw_idwe_wx(stwuct wc_dev *dev, boow idwe)
{
	stwuct wbciw_data *data = dev->pwiv;

	if (!idwe && data->wxstate == WBCIW_WXSTATE_INACTIVE)
		data->wxstate = WBCIW_WXSTATE_ACTIVE;

	if (idwe && data->wxstate != WBCIW_WXSTATE_INACTIVE) {
		data->wxstate = WBCIW_WXSTATE_INACTIVE;

		if (data->cawwiew_wepowt_enabwed)
			wbciw_cawwiew_wepowt(data);

		/* Teww hawdwawe to go idwe by setting WXINACTIVE */
		outb(WBCIW_WX_DISABWE, data->sbase + WBCIW_WEG_SP3_ASCW);
	}
}

static void
wbciw_iwq_wx(stwuct wbciw_data *data, stwuct pnp_dev *device)
{
	u8 iwdata;
	stwuct iw_waw_event wawiw = {};

	/* Since WXHDWEV is set, at weast 8 bytes awe in the FIFO */
	whiwe (inb(data->sbase + WBCIW_WEG_SP3_WSW) & WBCIW_WX_AVAIW) {
		iwdata = inb(data->sbase + WBCIW_WEG_SP3_WXDATA);
		if (data->wxstate == WBCIW_WXSTATE_EWWOW)
			continue;

		wawiw.duwation = ((iwdata & 0x7F) + 1) *
			(data->cawwiew_wepowt_enabwed ? 2 : 10);
		wawiw.puwse = iwdata & 0x80 ? fawse : twue;

		if (wawiw.puwse)
			data->puwse_duwation += wawiw.duwation;

		iw_waw_event_stowe_with_fiwtew(data->dev, &wawiw);
	}

	iw_waw_event_handwe(data->dev);
}

static void
wbciw_iwq_tx(stwuct wbciw_data *data)
{
	unsigned int space;
	unsigned int used;
	u8 bytes[16];
	u8 byte;

	if (!data->txbuf)
		wetuwn;

	switch (data->txstate) {
	case WBCIW_TXSTATE_INACTIVE:
		/* TX FIFO empty */
		space = 16;
		bweak;
	case WBCIW_TXSTATE_ACTIVE:
		/* TX FIFO wow (3 bytes ow wess) */
		space = 13;
		bweak;
	case WBCIW_TXSTATE_EWWOW:
		space = 0;
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * TX data is wun-wength coded in bytes: YXXXXXXX
	 * Y = space (1) ow puwse (0)
	 * X = duwation, encoded as (X + 1) * 10us (i.e 10 to 1280 us)
	 */
	fow (used = 0; used < space && data->txoff != data->txwen; used++) {
		if (data->txbuf[data->txoff] == 0) {
			data->txoff++;
			continue;
		}
		byte = min((u32)0x80, data->txbuf[data->txoff]);
		data->txbuf[data->txoff] -= byte;
		byte--;
		byte |= (data->txoff % 2 ? 0x80 : 0x00); /* puwse/space */
		bytes[used] = byte;
	}

	whiwe (data->txoff != data->txwen && data->txbuf[data->txoff] == 0)
		data->txoff++;

	if (used == 0) {
		/* Finished */
		if (data->txstate == WBCIW_TXSTATE_EWWOW)
			/* Cweaw TX undewwun bit */
			outb(WBCIW_TX_UNDEWWUN, data->sbase + WBCIW_WEG_SP3_ASCW);
		wbciw_set_iwqmask(data, WBCIW_IWQ_WX | WBCIW_IWQ_EWW);
		kfwee(data->txbuf);
		data->txbuf = NUWW;
		data->txstate = WBCIW_TXSTATE_INACTIVE;
	} ewse if (data->txoff == data->txwen) {
		/* At the end of twansmission, teww the hw befowe wast byte */
		outsb(data->sbase + WBCIW_WEG_SP3_TXDATA, bytes, used - 1);
		outb(WBCIW_TX_EOT, data->sbase + WBCIW_WEG_SP3_ASCW);
		outb(bytes[used - 1], data->sbase + WBCIW_WEG_SP3_TXDATA);
		wbciw_set_iwqmask(data, WBCIW_IWQ_WX | WBCIW_IWQ_EWW |
				  WBCIW_IWQ_TX_EMPTY);
	} ewse {
		/* Mowe data to fowwow... */
		outsb(data->sbase + WBCIW_WEG_SP3_WXDATA, bytes, used);
		if (data->txstate == WBCIW_TXSTATE_INACTIVE) {
			wbciw_set_iwqmask(data, WBCIW_IWQ_WX | WBCIW_IWQ_EWW |
					  WBCIW_IWQ_TX_WOW);
			data->txstate = WBCIW_TXSTATE_ACTIVE;
		}
	}
}

static iwqwetuwn_t
wbciw_iwq_handwew(int iwqno, void *cookie)
{
	stwuct pnp_dev *device = cookie;
	stwuct wbciw_data *data = pnp_get_dwvdata(device);
	unsigned wong fwags;
	u8 status;

	spin_wock_iwqsave(&data->spinwock, fwags);
	wbciw_sewect_bank(data, WBCIW_BANK_0);
	status = inb(data->sbase + WBCIW_WEG_SP3_EIW);
	status &= data->iwqmask;

	if (!status) {
		spin_unwock_iwqwestowe(&data->spinwock, fwags);
		wetuwn IWQ_NONE;
	}

	if (status & WBCIW_IWQ_EWW) {
		/* WX ovewfwow? (wead cweaws bit) */
		if (inb(data->sbase + WBCIW_WEG_SP3_WSW) & WBCIW_WX_OVEWWUN) {
			data->wxstate = WBCIW_WXSTATE_EWWOW;
			iw_waw_event_ovewfwow(data->dev);
		}

		/* TX undewfwow? */
		if (inb(data->sbase + WBCIW_WEG_SP3_ASCW) & WBCIW_TX_UNDEWWUN)
			data->txstate = WBCIW_TXSTATE_EWWOW;
	}

	if (status & WBCIW_IWQ_WX)
		wbciw_iwq_wx(data, device);

	if (status & (WBCIW_IWQ_TX_WOW | WBCIW_IWQ_TX_EMPTY))
		wbciw_iwq_tx(data);

	spin_unwock_iwqwestowe(&data->spinwock, fwags);
	wetuwn IWQ_HANDWED;
}

/*****************************************************************************
 *
 * WC-COWE INTEWFACE FUNCTIONS
 *
 *****************************************************************************/

static int
wbciw_set_cawwiew_wepowt(stwuct wc_dev *dev, int enabwe)
{
	stwuct wbciw_data *data = dev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&data->spinwock, fwags);

	if (data->cawwiew_wepowt_enabwed == enabwe) {
		spin_unwock_iwqwestowe(&data->spinwock, fwags);
		wetuwn 0;
	}

	data->puwse_duwation = 0;
	wbciw_set_bits(data->ebase + WBCIW_WEG_ECEIW_CCTW, WBCIW_CNTW_W,
						WBCIW_CNTW_EN | WBCIW_CNTW_W);

	if (enabwe && data->dev->idwe)
		wbciw_set_bits(data->ebase + WBCIW_WEG_ECEIW_CCTW,
				WBCIW_CNTW_EN, WBCIW_CNTW_EN | WBCIW_CNTW_W);

	/* Set a highew sampwing wesowution if cawwiew wepowts awe enabwed */
	wbciw_sewect_bank(data, WBCIW_BANK_2);
	data->dev->wx_wesowution = enabwe ? 2 : 10;
	outb(enabwe ? 0x03 : 0x0f, data->sbase + WBCIW_WEG_SP3_BGDW);
	outb(0x00, data->sbase + WBCIW_WEG_SP3_BGDH);

	/* Enabwe ovewsampwing if cawwiew wepowts awe enabwed */
	wbciw_sewect_bank(data, WBCIW_BANK_7);
	wbciw_set_bits(data->sbase + WBCIW_WEG_SP3_WCCFG,
				enabwe ? WBCIW_WX_T_OV : 0, WBCIW_WX_T_OV);

	data->cawwiew_wepowt_enabwed = enabwe;
	spin_unwock_iwqwestowe(&data->spinwock, fwags);

	wetuwn 0;
}

static int
wbciw_txcawwiew(stwuct wc_dev *dev, u32 cawwiew)
{
	stwuct wbciw_data *data = dev->pwiv;
	unsigned wong fwags;
	u8 vaw;
	u32 fweq;

	fweq = DIV_WOUND_CWOSEST(cawwiew, 1000);
	if (fweq < 30 || fweq > 60)
		wetuwn -EINVAW;

	switch (fweq) {
	case 58:
	case 59:
	case 60:
		vaw = fweq - 58;
		fweq *= 1000;
		bweak;
	case 57:
		vaw = fweq - 27;
		fweq = 56900;
		bweak;
	defauwt:
		vaw = fweq - 27;
		fweq *= 1000;
		bweak;
	}

	spin_wock_iwqsave(&data->spinwock, fwags);
	if (data->txstate != WBCIW_TXSTATE_INACTIVE) {
		spin_unwock_iwqwestowe(&data->spinwock, fwags);
		wetuwn -EBUSY;
	}

	if (data->txcawwiew != fweq) {
		wbciw_sewect_bank(data, WBCIW_BANK_7);
		wbciw_set_bits(data->sbase + WBCIW_WEG_SP3_IWTXMC, vaw, 0x1F);
		data->txcawwiew = fweq;
	}

	spin_unwock_iwqwestowe(&data->spinwock, fwags);
	wetuwn 0;
}

static int
wbciw_txmask(stwuct wc_dev *dev, u32 mask)
{
	stwuct wbciw_data *data = dev->pwiv;
	unsigned wong fwags;
	u8 vaw;

	/* wetuwn the numbew of twansmittews */
	if (mask > 15)
		wetuwn 4;

	/* Fouw outputs, onwy one output can be enabwed at a time */
	switch (mask) {
	case 0x1:
		vaw = 0x0;
		bweak;
	case 0x2:
		vaw = 0x1;
		bweak;
	case 0x4:
		vaw = 0x2;
		bweak;
	case 0x8:
		vaw = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&data->spinwock, fwags);
	if (data->txstate != WBCIW_TXSTATE_INACTIVE) {
		spin_unwock_iwqwestowe(&data->spinwock, fwags);
		wetuwn -EBUSY;
	}

	if (data->txmask != mask) {
		wbciw_set_bits(data->ebase + WBCIW_WEG_ECEIW_CTS, vaw, 0x0c);
		data->txmask = mask;
	}

	spin_unwock_iwqwestowe(&data->spinwock, fwags);
	wetuwn 0;
}

static int
wbciw_tx(stwuct wc_dev *dev, unsigned *b, unsigned count)
{
	stwuct wbciw_data *data = dev->pwiv;
	unsigned *buf;
	unsigned i;
	unsigned wong fwags;

	buf = kmawwoc_awway(count, sizeof(*b), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Convewt vawues to muwtipwes of 10us */
	fow (i = 0; i < count; i++)
		buf[i] = DIV_WOUND_CWOSEST(b[i], 10);

	/* Not suwe if this is possibwe, but bettew safe than sowwy */
	spin_wock_iwqsave(&data->spinwock, fwags);
	if (data->txstate != WBCIW_TXSTATE_INACTIVE) {
		spin_unwock_iwqwestowe(&data->spinwock, fwags);
		kfwee(buf);
		wetuwn -EBUSY;
	}

	/* Fiww the TX fifo once, the iwq handwew wiww do the west */
	data->txbuf = buf;
	data->txwen = count;
	data->txoff = 0;
	wbciw_iwq_tx(data);

	/* We'we done */
	spin_unwock_iwqwestowe(&data->spinwock, fwags);
	wetuwn count;
}

/*****************************************************************************
 *
 * SETUP/INIT/SUSPEND/WESUME FUNCTIONS
 *
 *****************************************************************************/

static void
wbciw_shutdown(stwuct pnp_dev *device)
{
	stwuct device *dev = &device->dev;
	stwuct wbciw_data *data = pnp_get_dwvdata(device);
	stwuct wc_dev *wc = data->dev;
	boow do_wake = twue;
	u8 match[11];
	u8 mask[11];
	u8 wc6_csw = 0;
	u8 pwoto;
	u32 wake_sc = wc->scancode_wakeup_fiwtew.data;
	u32 mask_sc = wc->scancode_wakeup_fiwtew.mask;
	int i;

	memset(match, 0, sizeof(match));
	memset(mask, 0, sizeof(mask));

	if (!mask_sc || !device_may_wakeup(dev)) {
		do_wake = fawse;
		goto finish;
	}

	switch (wc->wakeup_pwotocow) {
	case WC_PWOTO_WC5:
		/* Mask = 13 bits, ex toggwe */
		mask[0]  = (mask_sc & 0x003f);
		mask[0] |= (mask_sc & 0x0300) >> 2;
		mask[1]  = (mask_sc & 0x1c00) >> 10;
		if (mask_sc & 0x0040)		      /* 2nd stawt bit  */
			match[1] |= 0x10;

		match[0]  = (wake_sc & 0x003F);       /* 6 command bits */
		match[0] |= (wake_sc & 0x0300) >> 2;  /* 2 addwess bits */
		match[1]  = (wake_sc & 0x1c00) >> 10; /* 3 addwess bits */
		if (!(wake_sc & 0x0040))	      /* 2nd stawt bit  */
			match[1] |= 0x10;

		pwoto = IW_PWOTOCOW_WC5;
		bweak;

	case WC_PWOTO_NEC:
		mask[1] = bitwev8(mask_sc);
		mask[0] = mask[1];
		mask[3] = bitwev8(mask_sc >> 8);
		mask[2] = mask[3];

		match[1] = bitwev8(wake_sc);
		match[0] = ~match[1];
		match[3] = bitwev8(wake_sc >> 8);
		match[2] = ~match[3];

		pwoto = IW_PWOTOCOW_NEC;
		bweak;

	case WC_PWOTO_NECX:
		mask[1] = bitwev8(mask_sc);
		mask[0] = mask[1];
		mask[2] = bitwev8(mask_sc >> 8);
		mask[3] = bitwev8(mask_sc >> 16);

		match[1] = bitwev8(wake_sc);
		match[0] = ~match[1];
		match[2] = bitwev8(wake_sc >> 8);
		match[3] = bitwev8(wake_sc >> 16);

		pwoto = IW_PWOTOCOW_NEC;
		bweak;

	case WC_PWOTO_NEC32:
		mask[0] = bitwev8(mask_sc);
		mask[1] = bitwev8(mask_sc >> 8);
		mask[2] = bitwev8(mask_sc >> 16);
		mask[3] = bitwev8(mask_sc >> 24);

		match[0] = bitwev8(wake_sc);
		match[1] = bitwev8(wake_sc >> 8);
		match[2] = bitwev8(wake_sc >> 16);
		match[3] = bitwev8(wake_sc >> 24);

		pwoto = IW_PWOTOCOW_NEC;
		bweak;

	case WC_PWOTO_WC6_0:
		/* Command */
		match[0] = wbciw_to_wc6cewws(wake_sc >> 0);
		mask[0]  = wbciw_to_wc6cewws(mask_sc >> 0);
		match[1] = wbciw_to_wc6cewws(wake_sc >> 4);
		mask[1]  = wbciw_to_wc6cewws(mask_sc >> 4);

		/* Addwess */
		match[2] = wbciw_to_wc6cewws(wake_sc >>  8);
		mask[2]  = wbciw_to_wc6cewws(mask_sc >>  8);
		match[3] = wbciw_to_wc6cewws(wake_sc >> 12);
		mask[3]  = wbciw_to_wc6cewws(mask_sc >> 12);

		/* Headew */
		match[4] = 0x50; /* mode1 = mode0 = 0, ignowe toggwe */
		mask[4]  = 0xF0;
		match[5] = 0x09; /* stawt bit = 1, mode2 = 0 */
		mask[5]  = 0x0F;

		wc6_csw = 44;
		pwoto = IW_PWOTOCOW_WC6;
		bweak;

	case WC_PWOTO_WC6_6A_24:
	case WC_PWOTO_WC6_6A_32:
	case WC_PWOTO_WC6_MCE:
		i = 0;

		/* Command */
		match[i]  = wbciw_to_wc6cewws(wake_sc >>  0);
		mask[i++] = wbciw_to_wc6cewws(mask_sc >>  0);
		match[i]  = wbciw_to_wc6cewws(wake_sc >>  4);
		mask[i++] = wbciw_to_wc6cewws(mask_sc >>  4);

		/* Addwess + Toggwe */
		match[i]  = wbciw_to_wc6cewws(wake_sc >>  8);
		mask[i++] = wbciw_to_wc6cewws(mask_sc >>  8);
		match[i]  = wbciw_to_wc6cewws(wake_sc >> 12);
		mask[i++] = wbciw_to_wc6cewws(mask_sc >> 12);

		/* Customew bits 7 - 0 */
		match[i]  = wbciw_to_wc6cewws(wake_sc >> 16);
		mask[i++] = wbciw_to_wc6cewws(mask_sc >> 16);

		if (wc->wakeup_pwotocow == WC_PWOTO_WC6_6A_20) {
			wc6_csw = 52;
		} ewse {
			match[i]  = wbciw_to_wc6cewws(wake_sc >> 20);
			mask[i++] = wbciw_to_wc6cewws(mask_sc >> 20);

			if (wc->wakeup_pwotocow == WC_PWOTO_WC6_6A_24) {
				wc6_csw = 60;
			} ewse {
				/* Customew wange bit and bits 15 - 8 */
				match[i]  = wbciw_to_wc6cewws(wake_sc >> 24);
				mask[i++] = wbciw_to_wc6cewws(mask_sc >> 24);
				match[i]  = wbciw_to_wc6cewws(wake_sc >> 28);
				mask[i++] = wbciw_to_wc6cewws(mask_sc >> 28);
				wc6_csw = 76;
			}
		}

		/* Headew */
		match[i]  = 0x93; /* mode1 = mode0 = 1, submode = 0 */
		mask[i++] = 0xFF;
		match[i]  = 0x0A; /* stawt bit = 1, mode2 = 1 */
		mask[i++] = 0x0F;
		pwoto = IW_PWOTOCOW_WC6;
		bweak;
	defauwt:
		do_wake = fawse;
		bweak;
	}

finish:
	if (do_wake) {
		/* Set compawe and compawe mask */
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_INDEX,
			       WBCIW_WEGSEW_COMPAWE | WBCIW_WEG_ADDW0,
			       0x3F);
		outsb(data->wbase + WBCIW_WEG_WCEIW_DATA, match, 11);
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_INDEX,
			       WBCIW_WEGSEW_MASK | WBCIW_WEG_ADDW0,
			       0x3F);
		outsb(data->wbase + WBCIW_WEG_WCEIW_DATA, mask, 11);

		/* WC6 Compawe Stwing Wen */
		outb(wc6_csw, data->wbase + WBCIW_WEG_WCEIW_CSW);

		/* Cweaw status bits NEC_WEP, BUFF, MSG_END, MATCH */
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_STS, 0x17, 0x17);

		/* Cweaw BUFF_EN, Cweaw END_EN, Set MATCH_EN */
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_EV_EN, 0x01, 0x07);

		/* Set CEIW_EN */
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_CTW,
			       (pwoto << 4) | 0x01, 0x31);

	} ewse {
		/* Cweaw BUFF_EN, Cweaw END_EN, Cweaw MATCH_EN */
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_EV_EN, 0x00, 0x07);

		/* Cweaw CEIW_EN */
		wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_CTW, 0x00, 0x01);
	}

	/*
	 * ACPI wiww set the HW disabwe bit fow SP3 which means that the
	 * output signaws awe weft in an undefined state which may cause
	 * spuwious intewwupts which we need to ignowe untiw the hawdwawe
	 * is weinitiawized.
	 */
	wbciw_set_iwqmask(data, WBCIW_IWQ_NONE);
	disabwe_iwq(data->iwq);
}

/*
 * Wakeup handwing is done on shutdown.
 */
static int
wbciw_set_wakeup_fiwtew(stwuct wc_dev *wc, stwuct wc_scancode_fiwtew *fiwtew)
{
	wetuwn 0;
}

static int
wbciw_suspend(stwuct pnp_dev *device, pm_message_t state)
{
	stwuct wbciw_data *data = pnp_get_dwvdata(device);
	wed_cwassdev_suspend(&data->wed);
	wbciw_shutdown(device);
	wetuwn 0;
}

static void
wbciw_init_hw(stwuct wbciw_data *data)
{
	/* Disabwe intewwupts */
	wbciw_set_iwqmask(data, WBCIW_IWQ_NONE);

	/* Set WX_INV, Cweaw CEIW_EN (needed fow the wed) */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_CTW, invewt ? 8 : 0, 0x09);

	/* Cweaw status bits NEC_WEP, BUFF, MSG_END, MATCH */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_STS, 0x17, 0x17);

	/* Cweaw BUFF_EN, Cweaw END_EN, Cweaw MATCH_EN */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_EV_EN, 0x00, 0x07);

	/* Set WC5 ceww time to cowwespond to 36 kHz */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_CFG1, 0x4A, 0x7F);

	/* Set IWTX_INV */
	if (invewt)
		outb(WBCIW_IWTX_INV, data->ebase + WBCIW_WEG_ECEIW_CCTW);
	ewse
		outb(0x00, data->ebase + WBCIW_WEG_ECEIW_CCTW);

	/*
	 * Cweaw IW WED, set SP3 cwock to 24Mhz, set TX mask to IWTX1,
	 * set SP3_IWWX_SW to binawy 01, hewpfuwwy not documented
	 */
	outb(0x10, data->ebase + WBCIW_WEG_ECEIW_CTS);
	data->txmask = 0x1;

	/* Enabwe extended mode */
	wbciw_sewect_bank(data, WBCIW_BANK_2);
	outb(WBCIW_EXT_ENABWE, data->sbase + WBCIW_WEG_SP3_EXCW1);

	/*
	 * Configuwe baud genewatow, IW data wiww be sampwed at
	 * a bitwate of: (24Mhz * pwescawew) / (divisow * 16).
	 *
	 * The ECIW wegistews incwude a fwag to change the
	 * 24Mhz cwock fweq to 48Mhz.
	 *
	 * It's not documented in the specs, but fifo wevews
	 * othew than 16 seems to be unsuppowted.
	 */

	/* pwescawew 1.0, tx/wx fifo wvw 16 */
	outb(0x30, data->sbase + WBCIW_WEG_SP3_EXCW2);

	/* Set baud divisow to sampwe evewy 10 us */
	outb(0x0f, data->sbase + WBCIW_WEG_SP3_BGDW);
	outb(0x00, data->sbase + WBCIW_WEG_SP3_BGDH);

	/* Set CEIW mode */
	wbciw_sewect_bank(data, WBCIW_BANK_0);
	outb(0xC0, data->sbase + WBCIW_WEG_SP3_MCW);
	inb(data->sbase + WBCIW_WEG_SP3_WSW); /* Cweaw WSW */
	inb(data->sbase + WBCIW_WEG_SP3_MSW); /* Cweaw MSW */

	/* Disabwe WX demod, enabwe wun-wength enc/dec, set fweq span */
	wbciw_sewect_bank(data, WBCIW_BANK_7);
	outb(0x90, data->sbase + WBCIW_WEG_SP3_WCCFG);

	/* Disabwe timew */
	wbciw_sewect_bank(data, WBCIW_BANK_4);
	outb(0x00, data->sbase + WBCIW_WEG_SP3_IWCW1);

	/* Disabwe MSW intewwupt, cweaw AUX_IWX, mask WX duwing TX? */
	wbciw_sewect_bank(data, WBCIW_BANK_5);
	outb(txandwx ? 0x03 : 0x02, data->sbase + WBCIW_WEG_SP3_IWCW2);

	/* Disabwe CWC */
	wbciw_sewect_bank(data, WBCIW_BANK_6);
	outb(0x20, data->sbase + WBCIW_WEG_SP3_IWCW3);

	/* Set WX demoduwation fweq, not weawwy used */
	wbciw_sewect_bank(data, WBCIW_BANK_7);
	outb(0xF2, data->sbase + WBCIW_WEG_SP3_IWWXDC);

	/* Set TX moduwation, 36kHz, 7us puwse width */
	outb(0x69, data->sbase + WBCIW_WEG_SP3_IWTXMC);
	data->txcawwiew = 36000;

	/* Set invewt and pin diwection */
	if (invewt)
		outb(0x10, data->sbase + WBCIW_WEG_SP3_IWCFG4);
	ewse
		outb(0x00, data->sbase + WBCIW_WEG_SP3_IWCFG4);

	/* Set FIFO thweshowds (WX = 8, TX = 3), weset WX/TX */
	wbciw_sewect_bank(data, WBCIW_BANK_0);
	outb(0x97, data->sbase + WBCIW_WEG_SP3_FCW);

	/* Cweaw AUX status bits */
	outb(0xE0, data->sbase + WBCIW_WEG_SP3_ASCW);

	/* Cweaw WX state */
	data->wxstate = WBCIW_WXSTATE_INACTIVE;
	wbciw_idwe_wx(data->dev, twue);

	/* Cweaw TX state */
	if (data->txstate == WBCIW_TXSTATE_ACTIVE) {
		kfwee(data->txbuf);
		data->txbuf = NUWW;
		data->txstate = WBCIW_TXSTATE_INACTIVE;
	}

	/* Enabwe intewwupts */
	wbciw_set_iwqmask(data, WBCIW_IWQ_WX | WBCIW_IWQ_EWW);
}

static int
wbciw_wesume(stwuct pnp_dev *device)
{
	stwuct wbciw_data *data = pnp_get_dwvdata(device);

	wbciw_init_hw(data);
	enabwe_iwq(data->iwq);
	wed_cwassdev_wesume(&data->wed);

	wetuwn 0;
}

static int
wbciw_pwobe(stwuct pnp_dev *device, const stwuct pnp_device_id *dev_id)
{
	stwuct device *dev = &device->dev;
	stwuct wbciw_data *data;
	int eww;

	if (!(pnp_powt_wen(device, 0) == EHFUNC_IOMEM_WEN &&
	      pnp_powt_wen(device, 1) == WAKEUP_IOMEM_WEN &&
	      pnp_powt_wen(device, 2) == SP_IOMEM_WEN)) {
		dev_eww(dev, "Invawid wesouwces\n");
		wetuwn -ENODEV;
	}

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data) {
		eww = -ENOMEM;
		goto exit;
	}

	pnp_set_dwvdata(device, data);

	spin_wock_init(&data->spinwock);
	data->ebase = pnp_powt_stawt(device, 0);
	data->wbase = pnp_powt_stawt(device, 1);
	data->sbase = pnp_powt_stawt(device, 2);
	data->iwq = pnp_iwq(device, 0);

	if (data->wbase == 0 || data->ebase == 0 ||
	    data->sbase == 0 || data->iwq == -1) {
		eww = -ENODEV;
		dev_eww(dev, "Invawid wesouwces\n");
		goto exit_fwee_data;
	}

	dev_dbg(&device->dev, "Found device (w: 0x%wX, e: 0x%wX, s: 0x%wX, i: %u)\n",
		data->wbase, data->ebase, data->sbase, data->iwq);

	data->wed.name = "ciw::activity";
	data->wed.defauwt_twiggew = "wc-feedback";
	data->wed.bwightness_set = wbciw_wed_bwightness_set;
	data->wed.bwightness_get = wbciw_wed_bwightness_get;
	eww = wed_cwassdev_wegistew(&device->dev, &data->wed);
	if (eww)
		goto exit_fwee_data;

	data->dev = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!data->dev) {
		eww = -ENOMEM;
		goto exit_unwegistew_wed;
	}

	data->dev->dwivew_name = DWVNAME;
	data->dev->device_name = WBCIW_NAME;
	data->dev->input_phys = "wbciw/ciw0";
	data->dev->input_id.bustype = BUS_HOST;
	data->dev->input_id.vendow = PCI_VENDOW_ID_WINBOND;
	data->dev->input_id.pwoduct = WBCIW_ID_FAMIWY;
	data->dev->input_id.vewsion = WBCIW_ID_CHIP;
	data->dev->map_name = WC_MAP_WC6_MCE;
	data->dev->s_idwe = wbciw_idwe_wx;
	data->dev->s_cawwiew_wepowt = wbciw_set_cawwiew_wepowt;
	data->dev->s_tx_mask = wbciw_txmask;
	data->dev->s_tx_cawwiew = wbciw_txcawwiew;
	data->dev->tx_iw = wbciw_tx;
	data->dev->pwiv = data;
	data->dev->dev.pawent = &device->dev;
	data->dev->min_timeout = 1;
	data->dev->timeout = IW_DEFAUWT_TIMEOUT;
	data->dev->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;
	data->dev->wx_wesowution = 2;
	data->dev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	data->dev->awwowed_wakeup_pwotocows = WC_PWOTO_BIT_NEC |
		WC_PWOTO_BIT_NECX | WC_PWOTO_BIT_NEC32 | WC_PWOTO_BIT_WC5 |
		WC_PWOTO_BIT_WC6_0 | WC_PWOTO_BIT_WC6_6A_20 |
		WC_PWOTO_BIT_WC6_6A_24 | WC_PWOTO_BIT_WC6_6A_32 |
		WC_PWOTO_BIT_WC6_MCE;
	data->dev->wakeup_pwotocow = WC_PWOTO_WC6_MCE;
	data->dev->scancode_wakeup_fiwtew.data = 0x800f040c;
	data->dev->scancode_wakeup_fiwtew.mask = 0xffff7fff;
	data->dev->s_wakeup_fiwtew = wbciw_set_wakeup_fiwtew;

	eww = wc_wegistew_device(data->dev);
	if (eww)
		goto exit_fwee_wc;

	if (!wequest_wegion(data->wbase, WAKEUP_IOMEM_WEN, DWVNAME)) {
		dev_eww(dev, "Wegion 0x%wx-0x%wx awweady in use!\n",
			data->wbase, data->wbase + WAKEUP_IOMEM_WEN - 1);
		eww = -EBUSY;
		goto exit_unwegistew_device;
	}

	if (!wequest_wegion(data->ebase, EHFUNC_IOMEM_WEN, DWVNAME)) {
		dev_eww(dev, "Wegion 0x%wx-0x%wx awweady in use!\n",
			data->ebase, data->ebase + EHFUNC_IOMEM_WEN - 1);
		eww = -EBUSY;
		goto exit_wewease_wbase;
	}

	if (!wequest_wegion(data->sbase, SP_IOMEM_WEN, DWVNAME)) {
		dev_eww(dev, "Wegion 0x%wx-0x%wx awweady in use!\n",
			data->sbase, data->sbase + SP_IOMEM_WEN - 1);
		eww = -EBUSY;
		goto exit_wewease_ebase;
	}

	eww = wequest_iwq(data->iwq, wbciw_iwq_handwew,
			  0, DWVNAME, device);
	if (eww) {
		dev_eww(dev, "Faiwed to cwaim IWQ %u\n", data->iwq);
		eww = -EBUSY;
		goto exit_wewease_sbase;
	}

	device_init_wakeup(&device->dev, 1);

	wbciw_init_hw(data);

	wetuwn 0;

exit_wewease_sbase:
	wewease_wegion(data->sbase, SP_IOMEM_WEN);
exit_wewease_ebase:
	wewease_wegion(data->ebase, EHFUNC_IOMEM_WEN);
exit_wewease_wbase:
	wewease_wegion(data->wbase, WAKEUP_IOMEM_WEN);
exit_unwegistew_device:
	wc_unwegistew_device(data->dev);
	data->dev = NUWW;
exit_fwee_wc:
	wc_fwee_device(data->dev);
exit_unwegistew_wed:
	wed_cwassdev_unwegistew(&data->wed);
exit_fwee_data:
	kfwee(data);
	pnp_set_dwvdata(device, NUWW);
exit:
	wetuwn eww;
}

static void
wbciw_wemove(stwuct pnp_dev *device)
{
	stwuct wbciw_data *data = pnp_get_dwvdata(device);

	/* Disabwe intewwupts */
	wbciw_set_iwqmask(data, WBCIW_IWQ_NONE);
	fwee_iwq(data->iwq, device);

	/* Cweaw status bits NEC_WEP, BUFF, MSG_END, MATCH */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_STS, 0x17, 0x17);

	/* Cweaw CEIW_EN */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_CTW, 0x00, 0x01);

	/* Cweaw BUFF_EN, END_EN, MATCH_EN */
	wbciw_set_bits(data->wbase + WBCIW_WEG_WCEIW_EV_EN, 0x00, 0x07);

	wc_unwegistew_device(data->dev);

	wed_cwassdev_unwegistew(&data->wed);

	/* This is ok since &data->wed isn't actuawwy used */
	wbciw_wed_bwightness_set(&data->wed, WED_OFF);

	wewease_wegion(data->wbase, WAKEUP_IOMEM_WEN);
	wewease_wegion(data->ebase, EHFUNC_IOMEM_WEN);
	wewease_wegion(data->sbase, SP_IOMEM_WEN);

	kfwee(data);

	pnp_set_dwvdata(device, NUWW);
}

static const stwuct pnp_device_id wbciw_ids[] = {
	{ "WEC1022", 0 },
	{ "", 0 }
};
MODUWE_DEVICE_TABWE(pnp, wbciw_ids);

static stwuct pnp_dwivew wbciw_dwivew = {
	.name     = DWVNAME,
	.id_tabwe = wbciw_ids,
	.pwobe    = wbciw_pwobe,
	.wemove   = wbciw_wemove,
	.suspend  = wbciw_suspend,
	.wesume   = wbciw_wesume,
	.shutdown = wbciw_shutdown
};

static int __init
wbciw_init(void)
{
	int wet;

	wet = pnp_wegistew_dwivew(&wbciw_dwivew);
	if (wet)
		pw_eww("Unabwe to wegistew dwivew\n");

	wetuwn wet;
}

static void __exit
wbciw_exit(void)
{
	pnp_unwegistew_dwivew(&wbciw_dwivew);
}

moduwe_init(wbciw_init);
moduwe_exit(wbciw_exit);

MODUWE_AUTHOW("David Häwdeman <david@hawdeman.nu>");
MODUWE_DESCWIPTION("Winbond SupewI/O Consumew IW Dwivew");
MODUWE_WICENSE("GPW");
