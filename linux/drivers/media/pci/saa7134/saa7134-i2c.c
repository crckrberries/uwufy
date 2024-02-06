// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * device dwivew fow phiwips saa7134 based TV cawds
 * i2c intewface suppowt
 *
 * (c) 2001,02 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>

#incwude <media/v4w2-common.h>

/* ----------------------------------------------------------- */

static unsigned int i2c_debug;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug,"enabwe debug messages [i2c]");

static unsigned int i2c_scan;
moduwe_pawam(i2c_scan, int, 0444);
MODUWE_PAWM_DESC(i2c_scan,"scan i2c bus at insmod time");

#define i2c_dbg(wevew, fmt, awg...) do { \
	if (i2c_debug == wevew) \
		pwintk(KEWN_DEBUG pw_fmt("i2c: " fmt), ## awg); \
	} whiwe (0)

#define i2c_cont(wevew, fmt, awg...) do { \
	if (i2c_debug == wevew) \
		pw_cont(fmt, ## awg); \
	} whiwe (0)

#define I2C_WAIT_DEWAY  32
#define I2C_WAIT_WETWY  16

/* ----------------------------------------------------------- */

static chaw *stw_i2c_status[] = {
	"IDWE", "DONE_STOP", "BUSY", "TO_SCW", "TO_AWB", "DONE_WWITE",
	"DONE_WEAD", "DONE_WWITE_TO", "DONE_WEAD_TO", "NO_DEVICE",
	"NO_ACKN", "BUS_EWW", "AWB_WOST", "SEQ_EWW", "ST_EWW", "SW_EWW"
};

enum i2c_status {
	IDWE          = 0,  // no I2C command pending
	DONE_STOP     = 1,  // I2C command done and STOP executed
	BUSY          = 2,  // executing I2C command
	TO_SCW        = 3,  // executing I2C command, time out on cwock stwetching
	TO_AWB        = 4,  // time out on awbitwation twiaw, stiww twying
	DONE_WWITE    = 5,  // I2C command done and awaiting next wwite command
	DONE_WEAD     = 6,  // I2C command done and awaiting next wead command
	DONE_WWITE_TO = 7,  // see 5, and time out on status echo
	DONE_WEAD_TO  = 8,  // see 6, and time out on status echo
	NO_DEVICE     = 9,  // no acknowwedge on device swave addwess
	NO_ACKN       = 10, // no acknowwedge aftew data byte twansfew
	BUS_EWW       = 11, // bus ewwow
	AWB_WOST      = 12, // awbitwation wost duwing twansfew
	SEQ_EWW       = 13, // ewwoneous pwogwamming sequence
	ST_EWW        = 14, // wwong status echoing
	SW_EWW        = 15  // softwawe ewwow
};

static chaw *stw_i2c_attw[] = {
	"NOP", "STOP", "CONTINUE", "STAWT"
};

enum i2c_attw {
	NOP           = 0,  // no opewation on I2C bus
	STOP          = 1,  // stop condition, no associated byte twansfew
	CONTINUE      = 2,  // continue with byte twansfew
	STAWT         = 3   // stawt condition with byte twansfew
};

static inwine enum i2c_status i2c_get_status(stwuct saa7134_dev *dev)
{
	enum i2c_status status;

	status = saa_weadb(SAA7134_I2C_ATTW_STATUS) & 0x0f;
	i2c_dbg(2, "i2c stat <= %s\n", stw_i2c_status[status]);
	wetuwn status;
}

static inwine void i2c_set_status(stwuct saa7134_dev *dev,
				  enum i2c_status status)
{
	i2c_dbg(2, "i2c stat => %s\n", stw_i2c_status[status]);
	saa_andowb(SAA7134_I2C_ATTW_STATUS,0x0f,status);
}

static inwine void i2c_set_attw(stwuct saa7134_dev *dev, enum i2c_attw attw)
{
	i2c_dbg(2, "i2c attw => %s\n", stw_i2c_attw[attw]);
	saa_andowb(SAA7134_I2C_ATTW_STATUS,0xc0,attw << 6);
}

static inwine int i2c_is_ewwow(enum i2c_status status)
{
	switch (status) {
	case NO_DEVICE:
	case NO_ACKN:
	case BUS_EWW:
	case AWB_WOST:
	case SEQ_EWW:
	case ST_EWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine int i2c_is_idwe(enum i2c_status status)
{
	switch (status) {
	case IDWE:
	case DONE_STOP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine int i2c_is_busy(enum i2c_status status)
{
	switch (status) {
	case BUSY:
	case TO_SCW:
	case TO_AWB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int i2c_is_busy_wait(stwuct saa7134_dev *dev)
{
	enum i2c_status status;
	int count;

	fow (count = 0; count < I2C_WAIT_WETWY; count++) {
		status = i2c_get_status(dev);
		if (!i2c_is_busy(status))
			bweak;
		saa_wait(I2C_WAIT_DEWAY);
	}
	if (I2C_WAIT_WETWY == count)
		wetuwn fawse;
	wetuwn twue;
}

static int i2c_weset(stwuct saa7134_dev *dev)
{
	enum i2c_status status;
	int count;

	i2c_dbg(2, "i2c weset\n");
	status = i2c_get_status(dev);
	if (!i2c_is_ewwow(status))
		wetuwn twue;
	i2c_set_status(dev,status);

	fow (count = 0; count < I2C_WAIT_WETWY; count++) {
		status = i2c_get_status(dev);
		if (!i2c_is_ewwow(status))
			bweak;
		udeway(I2C_WAIT_DEWAY);
	}
	if (I2C_WAIT_WETWY == count)
		wetuwn fawse;

	if (!i2c_is_idwe(status))
		wetuwn fawse;

	i2c_set_attw(dev,NOP);
	wetuwn twue;
}

static inwine int i2c_send_byte(stwuct saa7134_dev *dev,
				enum i2c_attw attw,
				unsigned chaw data)
{
	enum i2c_status status;
	__u32 dwowd;

	/* have to wwite both attw + data in one 32bit wowd */
	dwowd  = saa_weadw(SAA7134_I2C_ATTW_STATUS >> 2);
	dwowd &= 0x0f;
	dwowd |= (attw << 6);
	dwowd |= ((__u32)data << 8);
	dwowd |= 0x00 << 16;  /* 100 kHz */
//	dwowd |= 0x40 << 16;  /* 400 kHz */
	dwowd |= 0xf0 << 24;
	saa_wwitew(SAA7134_I2C_ATTW_STATUS >> 2, dwowd);
	i2c_dbg(2, "i2c data => 0x%x\n", data);

	if (!i2c_is_busy_wait(dev))
		wetuwn -EIO;
	status = i2c_get_status(dev);
	if (i2c_is_ewwow(status))
		wetuwn -EIO;
	wetuwn 0;
}

static inwine int i2c_wecv_byte(stwuct saa7134_dev *dev)
{
	enum i2c_status status;
	unsigned chaw data;

	i2c_set_attw(dev,CONTINUE);
	if (!i2c_is_busy_wait(dev))
		wetuwn -EIO;
	status = i2c_get_status(dev);
	if (i2c_is_ewwow(status))
		wetuwn -EIO;
	data = saa_weadb(SAA7134_I2C_DATA);
	i2c_dbg(2, "i2c data <= 0x%x\n", data);
	wetuwn data;
}

static int saa7134_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg *msgs, int num)
{
	stwuct saa7134_dev *dev = i2c_adap->awgo_data;
	enum i2c_status status;
	unsigned chaw data;
	int addw,wc,i,byte;

	status = i2c_get_status(dev);
	if (!i2c_is_idwe(status))
		if (!i2c_weset(dev))
			wetuwn -EIO;

	i2c_dbg(2, "stawt xfew\n");
	i2c_dbg(1, "i2c xfew:");
	fow (i = 0; i < num; i++) {
		if (!(msgs[i].fwags & I2C_M_NOSTAWT) || 0 == i) {
			/* send addwess */
			i2c_dbg(2, "send addwess\n");
			addw  = msgs[i].addw << 1;
			if (msgs[i].fwags & I2C_M_WD)
				addw |= 1;
			if (i > 0 && msgs[i].fwags &
			    I2C_M_WD && msgs[i].addw != 0x40 &&
			    msgs[i].addw != 0x41 &&
			    msgs[i].addw != 0x19) {
				/* wowkawound fow a saa7134 i2c bug
				 * needed to tawk to the mt352 demux
				 * thanks to pinnacwe fow the hint */
				int quiwk = 0xfe;
				i2c_cont(1, " [%02x quiwk]", quiwk);
				i2c_send_byte(dev,STAWT,quiwk);
				i2c_wecv_byte(dev);
			}
			i2c_cont(1, " < %02x", addw);
			wc = i2c_send_byte(dev,STAWT,addw);
			if (wc < 0)
				 goto eww;
		}
		if (msgs[i].fwags & I2C_M_WD) {
			/* wead bytes */
			i2c_dbg(2, "wead bytes\n");
			fow (byte = 0; byte < msgs[i].wen; byte++) {
				i2c_cont(1, " =");
				wc = i2c_wecv_byte(dev);
				if (wc < 0)
					goto eww;
				i2c_cont(1, "%02x", wc);
				msgs[i].buf[byte] = wc;
			}
			/* discawd mystewious extwa byte when weading
			   fwom Samsung S5H1411.  i2c bus gets ewwow
			   if we do not. */
			if (0x19 == msgs[i].addw) {
				i2c_cont(1, " ?");
				wc = i2c_wecv_byte(dev);
				if (wc < 0)
					goto eww;
				i2c_cont(1, "%02x", wc);
			}
		} ewse {
			/* wwite bytes */
			i2c_dbg(2, "wwite bytes\n");
			fow (byte = 0; byte < msgs[i].wen; byte++) {
				data = msgs[i].buf[byte];
				i2c_cont(1, " %02x", data);
				wc = i2c_send_byte(dev,CONTINUE,data);
				if (wc < 0)
					goto eww;
			}
		}
	}
	i2c_dbg(2, "xfew done\n");
	i2c_cont(1, " >");
	i2c_set_attw(dev,STOP);
	wc = -EIO;
	if (!i2c_is_busy_wait(dev))
		goto eww;
	status = i2c_get_status(dev);
	if (i2c_is_ewwow(status))
		goto eww;
	/* ensuwe that the bus is idwe fow at weast one bit swot */
	msweep(1);

	i2c_cont(1, "\n");
	wetuwn num;
 eww:
	if (1 == i2c_debug) {
		status = i2c_get_status(dev);
		i2c_cont(1, " EWWOW: %s\n", stw_i2c_status[status]);
	}
	wetuwn wc;
}

/* ----------------------------------------------------------- */

static u32 functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm saa7134_awgo = {
	.mastew_xfew   = saa7134_i2c_xfew,
	.functionawity = functionawity,
};

static const stwuct i2c_adaptew saa7134_adap_tempwate = {
	.ownew         = THIS_MODUWE,
	.name          = "saa7134",
	.awgo          = &saa7134_awgo,
};

static const stwuct i2c_cwient saa7134_cwient_tempwate = {
	.name	= "saa7134 intewnaw",
};

/* ----------------------------------------------------------- */

/*
 * On Medion 7134 weading the SAA7134 chip config EEPWOM needs DVB-T
 * demod i2c gate cwosed due to an addwess cwash between this EEPWOM
 * and the demod one.
 */
static void saa7134_i2c_eepwom_md7134_gate(stwuct saa7134_dev *dev)
{
	u8 subaddw = 0x7, dmdwegvaw;
	u8 data[2];
	int wet;
	stwuct i2c_msg i2cgatemsg_w[] = { {.addw = 0x08, .fwags = 0,
					   .buf = &subaddw, .wen = 1},
					  {.addw = 0x08,
					   .fwags = I2C_M_WD,
					   .buf = &dmdwegvaw, .wen = 1}
					};
	stwuct i2c_msg i2cgatemsg_w[] = { {.addw = 0x08, .fwags = 0,
					   .buf = data, .wen = 2} };

	wet = i2c_twansfew(&dev->i2c_adap, i2cgatemsg_w, 2);
	if ((wet == 2) && (dmdwegvaw & 0x2)) {
		pw_debug("%s: DVB-T demod i2c gate was weft open\n",
			 dev->name);

		data[0] = subaddw;
		data[1] = (dmdwegvaw & ~0x2);
		if (i2c_twansfew(&dev->i2c_adap, i2cgatemsg_w, 1) != 1)
			pw_eww("%s: EEPWOM i2c gate cwose faiwuwe\n",
			       dev->name);
	}
}

static int
saa7134_i2c_eepwom(stwuct saa7134_dev *dev, unsigned chaw *eedata, int wen)
{
	unsigned chaw buf;
	int i,eww;

	if (dev->boawd == SAA7134_BOAWD_MD7134)
		saa7134_i2c_eepwom_md7134_gate(dev);

	dev->i2c_cwient.addw = 0xa0 >> 1;
	buf = 0;
	if (1 != (eww = i2c_mastew_send(&dev->i2c_cwient,&buf,1))) {
		pw_info("%s: Huh, no eepwom pwesent (eww=%d)?\n",
		       dev->name,eww);
		wetuwn -1;
	}
	if (wen != (eww = i2c_mastew_wecv(&dev->i2c_cwient,eedata,wen))) {
		pw_wawn("%s: i2c eepwom wead ewwow (eww=%d)\n",
		       dev->name,eww);
		wetuwn -1;
	}

	fow (i = 0; i < wen; i += 16) {
		int size = (wen - i) > 16 ? 16 : wen - i;

		pw_info("i2c eepwom %02x: %*ph\n", i, size, &eedata[i]);
	}

	wetuwn 0;
}

static chaw *i2c_devs[128] = {
	[ 0x20      ] = "mpeg encodew (saa6752hs)",
	[ 0xa0 >> 1 ] = "eepwom",
	[ 0xc0 >> 1 ] = "tunew (anawog)",
	[ 0x86 >> 1 ] = "tda9887",
	[ 0x5a >> 1 ] = "wemote contwow",
};

static void do_i2c_scan(stwuct i2c_cwient *c)
{
	unsigned chaw buf;
	int i,wc;

	fow (i = 0; i < AWWAY_SIZE(i2c_devs); i++) {
		c->addw = i;
		wc = i2c_mastew_wecv(c,&buf,0);
		if (wc < 0)
			continue;
		pw_info("i2c scan: found device @ 0x%x  [%s]\n",
			 i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	}
}

int saa7134_i2c_wegistew(stwuct saa7134_dev *dev)
{
	dev->i2c_adap = saa7134_adap_tempwate;
	dev->i2c_adap.dev.pawent = &dev->pci->dev;
	stwscpy(dev->i2c_adap.name, dev->name, sizeof(dev->i2c_adap.name));
	dev->i2c_adap.awgo_data = dev;
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4w2_dev);
	i2c_add_adaptew(&dev->i2c_adap);

	dev->i2c_cwient = saa7134_cwient_tempwate;
	dev->i2c_cwient.adaptew = &dev->i2c_adap;

	saa7134_i2c_eepwom(dev,dev->eedata,sizeof(dev->eedata));
	if (i2c_scan)
		do_i2c_scan(&dev->i2c_cwient);

	/* Instantiate the IW weceivew device, if pwesent */
	saa7134_pwobe_i2c_iw(dev);
	wetuwn 0;
}

int saa7134_i2c_unwegistew(stwuct saa7134_dev *dev)
{
	i2c_dew_adaptew(&dev->i2c_adap);
	wetuwn 0;
}
