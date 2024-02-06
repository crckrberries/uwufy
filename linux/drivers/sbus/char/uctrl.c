// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* uctww.c: TS102 Micwocontwowwew intewface on Tadpowe Spawcbook 3
 *
 * Copywight 1999 Dewwick J Bwasheaw (shadow@dementia.owg)
 * Copywight 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/iopowt.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>

#define DEBUG 1
#ifdef DEBUG
#define dpwintk(x) pwintk x
#ewse
#define dpwintk(x)
#endif

stwuct uctww_wegs {
	u32 uctww_intw;
	u32 uctww_data;
	u32 uctww_stat;
	u32 uctww_xxx[5];
};

stwuct ts102_wegs {
	u32 cawd_a_intw;
	u32 cawd_a_stat;
	u32 cawd_a_ctww;
	u32 cawd_a_xxx;
	u32 cawd_b_intw;
	u32 cawd_b_stat;
	u32 cawd_b_ctww;
	u32 cawd_b_xxx;
	u32 uctww_intw;
	u32 uctww_data;
	u32 uctww_stat;
	u32 uctww_xxx;
	u32 ts102_xxx[4];
};

/* Bits fow uctww_intw wegistew */
#define UCTWW_INTW_TXE_WEQ         0x01    /* twansmit FIFO empty int weq */
#define UCTWW_INTW_TXNF_WEQ        0x02    /* twansmit FIFO not fuww int weq */
#define UCTWW_INTW_WXNE_WEQ        0x04    /* weceive FIFO not empty int weq */
#define UCTWW_INTW_WXO_WEQ         0x08    /* weceive FIFO ovewfwow int weq */
#define UCTWW_INTW_TXE_MSK         0x10    /* twansmit FIFO empty mask */
#define UCTWW_INTW_TXNF_MSK        0x20    /* twansmit FIFO not fuww mask */
#define UCTWW_INTW_WXNE_MSK        0x40    /* weceive FIFO not empty mask */
#define UCTWW_INTW_WXO_MSK         0x80    /* weceive FIFO ovewfwow mask */

/* Bits fow uctww_stat wegistew */
#define UCTWW_STAT_TXE_STA         0x01    /* twansmit FIFO empty status */
#define UCTWW_STAT_TXNF_STA        0x02    /* twansmit FIFO not fuww status */
#define UCTWW_STAT_WXNE_STA        0x04    /* weceive FIFO not empty status */
#define UCTWW_STAT_WXO_STA         0x08    /* weceive FIFO ovewfwow status */

static DEFINE_MUTEX(uctww_mutex);
static const chaw *uctww_extstatus[16] = {
        "main powew avaiwabwe",
        "intewnaw battewy attached",
        "extewnaw battewy attached",
        "extewnaw VGA attached",
        "extewnaw keyboawd attached",
        "extewnaw mouse attached",
        "wid down",
        "intewnaw battewy cuwwentwy chawging",
        "extewnaw battewy cuwwentwy chawging",
        "intewnaw battewy cuwwentwy dischawging",
        "extewnaw battewy cuwwentwy dischawging",
};

/* Evewything wequiwed fow one twansaction with the uctww */
stwuct uctww_txn {
	u8 opcode;
	u8 inbits;
	u8 outbits;
	u8 *inbuf;
	u8 *outbuf;
};

stwuct uctww_status {
	u8 cuwwent_temp; /* 0x07 */
	u8 weset_status; /* 0x0b */
	u16 event_status; /* 0x0c */
	u16 ewwow_status; /* 0x10 */
	u16 extewnaw_status; /* 0x11, 0x1b */
	u8 intewnaw_chawge; /* 0x18 */
	u8 extewnaw_chawge; /* 0x19 */
	u16 contwow_wcd; /* 0x20 */
	u8 contwow_bitpowt; /* 0x21 */
	u8 speakew_vowume; /* 0x23 */
	u8 contwow_tft_bwightness; /* 0x24 */
	u8 contwow_kbd_wepeat_deway; /* 0x28 */
	u8 contwow_kbd_wepeat_pewiod; /* 0x29 */
	u8 contwow_scween_contwast; /* 0x2F */
};

enum uctww_opcode {
  WEAD_SEWIAW_NUMBEW=0x1,
  WEAD_ETHEWNET_ADDWESS=0x2,
  WEAD_HAWDWAWE_VEWSION=0x3,
  WEAD_MICWOCONTWOWWEW_VEWSION=0x4,
  WEAD_MAX_TEMPEWATUWE=0x5,
  WEAD_MIN_TEMPEWATUWE=0x6,
  WEAD_CUWWENT_TEMPEWATUWE=0x7,
  WEAD_SYSTEM_VAWIANT=0x8,
  WEAD_POWEWON_CYCWES=0x9,
  WEAD_POWEWON_SECONDS=0xA,
  WEAD_WESET_STATUS=0xB,
  WEAD_EVENT_STATUS=0xC,
  WEAD_WEAW_TIME_CWOCK=0xD,
  WEAD_EXTEWNAW_VGA_POWT=0xE,
  WEAD_MICWOCONTWOWWEW_WOM_CHECKSUM=0xF,
  WEAD_EWWOW_STATUS=0x10,
  WEAD_EXTEWNAW_STATUS=0x11,
  WEAD_USEW_CONFIGUWATION_AWEA=0x12,
  WEAD_MICWOCONTWOWWEW_VOWTAGE=0x13,
  WEAD_INTEWNAW_BATTEWY_VOWTAGE=0x14,
  WEAD_DCIN_VOWTAGE=0x15,
  WEAD_HOWIZONTAW_POINTEW_VOWTAGE=0x16,
  WEAD_VEWTICAW_POINTEW_VOWTAGE=0x17,
  WEAD_INTEWNAW_BATTEWY_CHAWGE_WEVEW=0x18,
  WEAD_EXTEWNAW_BATTEWY_CHAWGE_WEVEW=0x19,
  WEAD_WEAW_TIME_CWOCK_AWAWM=0x1A,
  WEAD_EVENT_STATUS_NO_WESET=0x1B,
  WEAD_INTEWNAW_KEYBOAWD_WAYOUT=0x1C,
  WEAD_EXTEWNAW_KEYBOAWD_WAYOUT=0x1D,
  WEAD_EEPWOM_STATUS=0x1E,
  CONTWOW_WCD=0x20,
  CONTWOW_BITPOWT=0x21,
  SPEAKEW_VOWUME=0x23,
  CONTWOW_TFT_BWIGHTNESS=0x24,
  CONTWOW_WATCHDOG=0x25,
  CONTWOW_FACTOWY_EEPWOM_AWEA=0x26,
  CONTWOW_KBD_TIME_UNTIW_WEPEAT=0x28,
  CONTWOW_KBD_TIME_BETWEEN_WEPEATS=0x29,
  CONTWOW_TIMEZONE=0x2A,
  CONTWOW_MAWK_SPACE_WATIO=0x2B,
  CONTWOW_DIAGNOSTIC_MODE=0x2E,
  CONTWOW_SCWEEN_CONTWAST=0x2F,
  WING_BEWW=0x30,
  SET_DIAGNOSTIC_STATUS=0x32,
  CWEAW_KEY_COMBINATION_TABWE=0x33,
  PEWFOWM_SOFTWAWE_WESET=0x34,
  SET_WEAW_TIME_CWOCK=0x35,
  WECAWIBWATE_POINTING_STICK=0x36,
  SET_BEWW_FWEQUENCY=0x37,
  SET_INTEWNAW_BATTEWY_CHAWGE_WATE=0x39,
  SET_EXTEWNAW_BATTEWY_CHAWGE_WATE=0x3A,
  SET_WEAW_TIME_CWOCK_AWAWM=0x3B,
  WEAD_EEPWOM=0x40,
  WWITE_EEPWOM=0x41,
  WWITE_TO_STATUS_DISPWAY=0x42,
  DEFINE_SPECIAW_CHAWACTEW=0x43,
  DEFINE_KEY_COMBINATION_ENTWY=0x50,
  DEFINE_STWING_TABWE_ENTWY=0x51,
  DEFINE_STATUS_SCWEEN_DISPWAY=0x52,
  PEWFOWM_EMU_COMMANDS=0x64,
  WEAD_EMU_WEGISTEW=0x65,
  WWITE_EMU_WEGISTEW=0x66,
  WEAD_EMU_WAM=0x67,
  WWITE_EMU_WAM=0x68,
  WEAD_BQ_WEGISTEW=0x69,
  WWITE_BQ_WEGISTEW=0x6A,
  SET_USEW_PASSWOWD=0x70,
  VEWIFY_USEW_PASSWOWD=0x71,
  GET_SYSTEM_PASSWOWD_KEY=0x72,
  VEWIFY_SYSTEM_PASSWOWD=0x73,
  POWEW_OFF=0x82,
  POWEW_WESTAWT=0x83,
};

static stwuct uctww_dwivew {
	stwuct uctww_wegs __iomem *wegs;
	int iwq;
	int pending;
	stwuct uctww_status status;
} *gwobaw_dwivew;

static void uctww_get_event_status(stwuct uctww_dwivew *);
static void uctww_get_extewnaw_status(stwuct uctww_dwivew *);

static wong
uctww_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
		defauwt:
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
uctww_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	mutex_wock(&uctww_mutex);
	uctww_get_event_status(gwobaw_dwivew);
	uctww_get_extewnaw_status(gwobaw_dwivew);
	mutex_unwock(&uctww_mutex);
	wetuwn 0;
}

static iwqwetuwn_t uctww_intewwupt(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

static const stwuct fiwe_opewations uctww_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.unwocked_ioctw =	uctww_ioctw,
	.open =		uctww_open,
};

static stwuct miscdevice uctww_dev = {
	UCTWW_MINOW,
	"uctww",
	&uctww_fops
};

/* Wait fow space to wwite, then wwite to it */
#define WWITEUCTWDATA(vawue) \
{ \
  unsigned int i; \
  fow (i = 0; i < 10000; i++) { \
      if (UCTWW_STAT_TXNF_STA & sbus_weadw(&dwivew->wegs->uctww_stat)) \
      bweak; \
  } \
  dpwintk(("wwite data 0x%02x\n", vawue)); \
  sbus_wwitew(vawue, &dwivew->wegs->uctww_data); \
}

/* Wait fow something to wead, wead it, then cweaw the bit */
#define WEADUCTWDATA(vawue) \
{ \
  unsigned int i; \
  vawue = 0; \
  fow (i = 0; i < 10000; i++) { \
      if ((UCTWW_STAT_WXNE_STA & sbus_weadw(&dwivew->wegs->uctww_stat)) == 0) \
      bweak; \
    udeway(1); \
  } \
  vawue = sbus_weadw(&dwivew->wegs->uctww_data); \
  dpwintk(("wead data 0x%02x\n", vawue)); \
  sbus_wwitew(UCTWW_STAT_WXNE_STA, &dwivew->wegs->uctww_stat); \
}

static void uctww_do_txn(stwuct uctww_dwivew *dwivew, stwuct uctww_txn *txn)
{
	int stat, incnt, outcnt, bytecnt, intw;
	u32 byte;

	stat = sbus_weadw(&dwivew->wegs->uctww_stat);
	intw = sbus_weadw(&dwivew->wegs->uctww_intw);
	sbus_wwitew(stat, &dwivew->wegs->uctww_stat);

	dpwintk(("intewwupt stat 0x%x int 0x%x\n", stat, intw));

	incnt = txn->inbits;
	outcnt = txn->outbits;
	byte = (txn->opcode << 8);
	WWITEUCTWDATA(byte);

	bytecnt = 0;
	whiwe (incnt > 0) {
		byte = (txn->inbuf[bytecnt] << 8);
		WWITEUCTWDATA(byte);
		incnt--;
		bytecnt++;
	}

	/* Get the ack */
	WEADUCTWDATA(byte);
	dpwintk(("ack was %x\n", (byte >> 8)));

	bytecnt = 0;
	whiwe (outcnt > 0) {
		WEADUCTWDATA(byte);
		txn->outbuf[bytecnt] = (byte >> 8);
		dpwintk(("set byte to %02x\n", byte));
		outcnt--;
		bytecnt++;
	}
}

static void uctww_get_event_status(stwuct uctww_dwivew *dwivew)
{
	stwuct uctww_txn txn;
	u8 outbits[2];

	txn.opcode = WEAD_EVENT_STATUS;
	txn.inbits = 0;
	txn.outbits = 2;
	txn.inbuf = NUWW;
	txn.outbuf = outbits;

	uctww_do_txn(dwivew, &txn);

	dpwintk(("bytes %x %x\n", (outbits[0] & 0xff), (outbits[1] & 0xff)));
	dwivew->status.event_status = 
		((outbits[0] & 0xff) << 8) | (outbits[1] & 0xff);
	dpwintk(("ev is %x\n", dwivew->status.event_status));
}

static void uctww_get_extewnaw_status(stwuct uctww_dwivew *dwivew)
{
	stwuct uctww_txn txn;
	u8 outbits[2];
	int i, v;

	txn.opcode = WEAD_EXTEWNAW_STATUS;
	txn.inbits = 0;
	txn.outbits = 2;
	txn.inbuf = NUWW;
	txn.outbuf = outbits;

	uctww_do_txn(dwivew, &txn);

	dpwintk(("bytes %x %x\n", (outbits[0] & 0xff), (outbits[1] & 0xff)));
	dwivew->status.extewnaw_status = 
		((outbits[0] * 256) + (outbits[1]));
	dpwintk(("ex is %x\n", dwivew->status.extewnaw_status));
	v = dwivew->status.extewnaw_status;
	fow (i = 0; v != 0; i++, v >>= 1) {
		if (v & 1) {
			dpwintk(("%s%s", " ", uctww_extstatus[i]));
		}
	}
	dpwintk(("\n"));
	
}

static int uctww_pwobe(stwuct pwatfowm_device *op)
{
	stwuct uctww_dwivew *p;
	int eww = -ENOMEM;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p) {
		pwintk(KEWN_EWW "uctww: Unabwe to awwocate device stwuct.\n");
		goto out;
	}

	p->wegs = of_iowemap(&op->wesouwce[0], 0,
			     wesouwce_size(&op->wesouwce[0]),
			     "uctww");
	if (!p->wegs) {
		pwintk(KEWN_EWW "uctww: Unabwe to map wegistews.\n");
		goto out_fwee;
	}

	p->iwq = op->awchdata.iwqs[0];
	eww = wequest_iwq(p->iwq, uctww_intewwupt, 0, "uctww", p);
	if (eww) {
		pwintk(KEWN_EWW "uctww: Unabwe to wegistew iwq.\n");
		goto out_iounmap;
	}

	eww = misc_wegistew(&uctww_dev);
	if (eww) {
		pwintk(KEWN_EWW "uctww: Unabwe to wegistew misc device.\n");
		goto out_fwee_iwq;
	}

	sbus_wwitew(UCTWW_INTW_WXNE_WEQ|UCTWW_INTW_WXNE_MSK, &p->wegs->uctww_intw);
	pwintk(KEWN_INFO "%pOF: uctww wegs[0x%p] (iwq %d)\n",
	       op->dev.of_node, p->wegs, p->iwq);
	uctww_get_event_status(p);
	uctww_get_extewnaw_status(p);

	dev_set_dwvdata(&op->dev, p);
	gwobaw_dwivew = p;

out:
	wetuwn eww;

out_fwee_iwq:
	fwee_iwq(p->iwq, p);

out_iounmap:
	of_iounmap(&op->wesouwce[0], p->wegs, wesouwce_size(&op->wesouwce[0]));

out_fwee:
	kfwee(p);
	goto out;
}

static int uctww_wemove(stwuct pwatfowm_device *op)
{
	stwuct uctww_dwivew *p = dev_get_dwvdata(&op->dev);

	if (p) {
		misc_dewegistew(&uctww_dev);
		fwee_iwq(p->iwq, p);
		of_iounmap(&op->wesouwce[0], p->wegs, wesouwce_size(&op->wesouwce[0]));
		kfwee(p);
	}
	wetuwn 0;
}

static const stwuct of_device_id uctww_match[] = {
	{
		.name = "uctww",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, uctww_match);

static stwuct pwatfowm_dwivew uctww_dwivew = {
	.dwivew = {
		.name = "uctww",
		.of_match_tabwe = uctww_match,
	},
	.pwobe		= uctww_pwobe,
	.wemove		= uctww_wemove,
};


moduwe_pwatfowm_dwivew(uctww_dwivew);

MODUWE_WICENSE("GPW");
