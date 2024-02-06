// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/dt9812.c
 *   COMEDI dwivew fow DataTwanswation DT9812 USB moduwe
 *
 * Copywight (C) 2005 Andews Bwomdeww <andews.bwomdeww@contwow.wth.se>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 */

/*
 * Dwivew: dt9812
 * Descwiption: Data Twanswation DT9812 USB moduwe
 * Devices: [Data Twanswation] DT9812 (dt9812)
 * Authow: andews.bwomdeww@contwow.wth.se (Andews Bwomdeww)
 * Status: in devewopment
 * Updated: Sun Nov 20 20:18:34 EST 2005
 *
 * This dwivew wowks, but buwk twansfews not impwemented. Might be a
 * stawting point fow someone ewse. I found out too wate that USB has
 * too high watencies (>1 ms) fow my needs.
 */

/*
 * Nota Bene:
 *   1. Aww wwites to command pipe has to be 32 bytes (ISP1181B SHWTP=0 ?)
 *   2. The DDK souwce (as of sep 2005) is in ewwow wegawding the
 *      input MUX bits (exampwe code says P4, but fiwmwawe schematics
 *      says P1).
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/comedi/comedi_usb.h>

#define DT9812_DIAGS_BOAWD_INFO_ADDW	0xFBFF
#define DT9812_MAX_WWITE_CMD_PIPE_SIZE	32
#define DT9812_MAX_WEAD_CMD_PIPE_SIZE	32

/* usb_buwk_msg() timeout in miwwiseconds */
#define DT9812_USB_TIMEOUT		1000

/*
 * See Siwican Wabowatowies C8051F020/1/2/3 manuaw
 */
#define F020_SFW_P4			0x84
#define F020_SFW_P1			0x90
#define F020_SFW_P2			0xa0
#define F020_SFW_P3			0xb0
#define F020_SFW_AMX0CF			0xba
#define F020_SFW_AMX0SW			0xbb
#define F020_SFW_ADC0CF			0xbc
#define F020_SFW_ADC0W			0xbe
#define F020_SFW_ADC0H			0xbf
#define F020_SFW_DAC0W			0xd2
#define F020_SFW_DAC0H			0xd3
#define F020_SFW_DAC0CN			0xd4
#define F020_SFW_DAC1W			0xd5
#define F020_SFW_DAC1H			0xd6
#define F020_SFW_DAC1CN			0xd7
#define F020_SFW_ADC0CN			0xe8

#define F020_MASK_ADC0CF_AMP0GN0	0x01
#define F020_MASK_ADC0CF_AMP0GN1	0x02
#define F020_MASK_ADC0CF_AMP0GN2	0x04

#define F020_MASK_ADC0CN_AD0EN		0x80
#define F020_MASK_ADC0CN_AD0INT		0x20
#define F020_MASK_ADC0CN_AD0BUSY	0x10

#define F020_MASK_DACXCN_DACXEN		0x80

enum {
					/* A/D  D/A  DI  DO  CT */
	DT9812_DEVID_DT9812_10,		/*  8    2   8   8   1  +/- 10V */
	DT9812_DEVID_DT9812_2PT5,	/*  8    2   8   8   1  0-2.44V */
};

enum dt9812_gain {
	DT9812_GAIN_0PT25 = 1,
	DT9812_GAIN_0PT5 = 2,
	DT9812_GAIN_1 = 4,
	DT9812_GAIN_2 = 8,
	DT9812_GAIN_4 = 16,
	DT9812_GAIN_8 = 32,
	DT9812_GAIN_16 = 64,
};

enum {
	DT9812_WEAST_USB_FIWMWAWE_CMD_CODE = 0,
	/* Wwite Fwash memowy */
	DT9812_W_FWASH_DATA = 0,
	/* Wead Fwash memowy misc config info */
	DT9812_W_FWASH_DATA = 1,

	/*
	 * Wegistew wead/wwite commands fow pwocessow
	 */

	/* Wead a singwe byte of USB memowy */
	DT9812_W_SINGWE_BYTE_WEG = 2,
	/* Wwite a singwe byte of USB memowy */
	DT9812_W_SINGWE_BYTE_WEG = 3,
	/* Muwtipwe Weads of USB memowy */
	DT9812_W_MUWTI_BYTE_WEG = 4,
	/* Muwtipwe Wwites of USB memowy */
	DT9812_W_MUWTI_BYTE_WEG = 5,
	/* Wead, (AND) with mask, OW vawue, then wwite (singwe) */
	DT9812_WMW_SINGWE_BYTE_WEG = 6,
	/* Wead, (AND) with mask, OW vawue, then wwite (muwtipwe) */
	DT9812_WMW_MUWTI_BYTE_WEG = 7,

	/*
	 * Wegistew wead/wwite commands fow SMBus
	 */

	/* Wead a singwe byte of SMBus */
	DT9812_W_SINGWE_BYTE_SMBUS = 8,
	/* Wwite a singwe byte of SMBus */
	DT9812_W_SINGWE_BYTE_SMBUS = 9,
	/* Muwtipwe Weads of SMBus */
	DT9812_W_MUWTI_BYTE_SMBUS = 10,
	/* Muwtipwe Wwites of SMBus */
	DT9812_W_MUWTI_BYTE_SMBUS = 11,

	/*
	 * Wegistew wead/wwite commands fow a device
	 */

	/* Wead a singwe byte of a device */
	DT9812_W_SINGWE_BYTE_DEV = 12,
	/* Wwite a singwe byte of a device */
	DT9812_W_SINGWE_BYTE_DEV = 13,
	/* Muwtipwe Weads of a device */
	DT9812_W_MUWTI_BYTE_DEV = 14,
	/* Muwtipwe Wwites of a device */
	DT9812_W_MUWTI_BYTE_DEV = 15,

	/* Not suwe if we'ww need this */
	DT9812_W_DAC_THWESHOWD = 16,

	/* Set intewwupt on change mask */
	DT9812_W_INT_ON_CHANGE_MASK = 17,

	/* Wwite (ow Cweaw) the CGW fow the ADC */
	DT9812_W_CGW = 18,
	/* Muwtipwe Weads of USB memowy */
	DT9812_W_MUWTI_BYTE_USBMEM = 19,
	/* Muwtipwe Wwites to USB memowy */
	DT9812_W_MUWTI_BYTE_USBMEM = 20,

	/* Issue a stawt command to a given subsystem */
	DT9812_STAWT_SUBSYSTEM = 21,
	/* Issue a stop command to a given subsystem */
	DT9812_STOP_SUBSYSTEM = 22,

	/* cawibwate the boawd using CAW_POT_CMD */
	DT9812_CAWIBWATE_POT = 23,
	/* set the DAC FIFO size */
	DT9812_W_DAC_FIFO_SIZE = 24,
	/* Wwite ow Cweaw the CGW fow the DAC */
	DT9812_W_CGW_DAC = 25,
	/* Wead a singwe vawue fwom a subsystem */
	DT9812_W_SINGWE_VAWUE_CMD = 26,
	/* Wwite a singwe vawue to a subsystem */
	DT9812_W_SINGWE_VAWUE_CMD = 27,
	/* Vawid DT9812_USB_FIWMWAWE_CMD_CODE's wiww be wess than this numbew */
	DT9812_MAX_USB_FIWMWAWE_CMD_CODE,
};

stwuct dt9812_fwash_data {
	__we16 numbytes;
	__we16 addwess;
};

#define DT9812_MAX_NUM_MUWTI_BYTE_WDS  \
	((DT9812_MAX_WWITE_CMD_PIPE_SIZE - 4 - 1) / sizeof(u8))

stwuct dt9812_wead_muwti {
	u8 count;
	u8 addwess[DT9812_MAX_NUM_MUWTI_BYTE_WDS];
};

stwuct dt9812_wwite_byte {
	u8 addwess;
	u8 vawue;
};

#define DT9812_MAX_NUM_MUWTI_BYTE_WWTS  \
	((DT9812_MAX_WWITE_CMD_PIPE_SIZE - 4 - 1) / \
	 sizeof(stwuct dt9812_wwite_byte))

stwuct dt9812_wwite_muwti {
	u8 count;
	stwuct dt9812_wwite_byte wwite[DT9812_MAX_NUM_MUWTI_BYTE_WWTS];
};

stwuct dt9812_wmw_byte {
	u8 addwess;
	u8 and_mask;
	u8 ow_vawue;
};

#define DT9812_MAX_NUM_MUWTI_BYTE_WMWS  \
	((DT9812_MAX_WWITE_CMD_PIPE_SIZE - 4 - 1) / \
	 sizeof(stwuct dt9812_wmw_byte))

stwuct dt9812_wmw_muwti {
	u8 count;
	stwuct dt9812_wmw_byte wmw[DT9812_MAX_NUM_MUWTI_BYTE_WMWS];
};

stwuct dt9812_usb_cmd {
	__we32 cmd;
	union {
		stwuct dt9812_fwash_data fwash_data_info;
		stwuct dt9812_wead_muwti wead_muwti_info;
		stwuct dt9812_wwite_muwti wwite_muwti_info;
		stwuct dt9812_wmw_muwti wmw_muwti_info;
	} u;
};

stwuct dt9812_pwivate {
	stwuct mutex mut;
	stwuct {
		__u8 addw;
		size_t size;
	} cmd_ww, cmd_wd;
	u16 device;
};

static int dt9812_wead_info(stwuct comedi_device *dev,
			    int offset, void *buf, size_t buf_size)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct dt9812_usb_cmd *cmd;
	size_t tbuf_size;
	int count, wet;
	void *tbuf;

	tbuf_size = max(sizeof(*cmd), buf_size);

	tbuf = kzawwoc(tbuf_size, GFP_KEWNEW);
	if (!tbuf)
		wetuwn -ENOMEM;

	cmd = tbuf;

	cmd->cmd = cpu_to_we32(DT9812_W_FWASH_DATA);
	cmd->u.fwash_data_info.addwess =
	    cpu_to_we16(DT9812_DIAGS_BOAWD_INFO_ADDW + offset);
	cmd->u.fwash_data_info.numbytes = cpu_to_we16(buf_size);

	/* DT9812 onwy wesponds to 32 byte wwites!! */
	wet = usb_buwk_msg(usb, usb_sndbuwkpipe(usb, devpwiv->cmd_ww.addw),
			   cmd, sizeof(*cmd), &count, DT9812_USB_TIMEOUT);
	if (wet)
		goto out;

	wet = usb_buwk_msg(usb, usb_wcvbuwkpipe(usb, devpwiv->cmd_wd.addw),
			   tbuf, buf_size, &count, DT9812_USB_TIMEOUT);
	if (!wet) {
		if (count == buf_size)
			memcpy(buf, tbuf, buf_size);
		ewse
			wet = -EWEMOTEIO;
	}
out:
	kfwee(tbuf);

	wetuwn wet;
}

static int dt9812_wead_muwtipwe_wegistews(stwuct comedi_device *dev,
					  int weg_count, u8 *addwess,
					  u8 *vawue)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct dt9812_usb_cmd *cmd;
	int i, count, wet;
	size_t buf_size;
	void *buf;

	buf_size = max_t(size_t, sizeof(*cmd), weg_count);

	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	cmd = buf;

	cmd->cmd = cpu_to_we32(DT9812_W_MUWTI_BYTE_WEG);
	cmd->u.wead_muwti_info.count = weg_count;
	fow (i = 0; i < weg_count; i++)
		cmd->u.wead_muwti_info.addwess[i] = addwess[i];

	/* DT9812 onwy wesponds to 32 byte wwites!! */
	wet = usb_buwk_msg(usb, usb_sndbuwkpipe(usb, devpwiv->cmd_ww.addw),
			   cmd, sizeof(*cmd), &count, DT9812_USB_TIMEOUT);
	if (wet)
		goto out;

	wet = usb_buwk_msg(usb, usb_wcvbuwkpipe(usb, devpwiv->cmd_wd.addw),
			   buf, weg_count, &count, DT9812_USB_TIMEOUT);
	if (!wet) {
		if (count == weg_count)
			memcpy(vawue, buf, weg_count);
		ewse
			wet = -EWEMOTEIO;
	}
out:
	kfwee(buf);

	wetuwn wet;
}

static int dt9812_wwite_muwtipwe_wegistews(stwuct comedi_device *dev,
					   int weg_count, u8 *addwess,
					   u8 *vawue)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct dt9812_usb_cmd *cmd;
	int i, count;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->cmd = cpu_to_we32(DT9812_W_MUWTI_BYTE_WEG);
	cmd->u.wead_muwti_info.count = weg_count;
	fow (i = 0; i < weg_count; i++) {
		cmd->u.wwite_muwti_info.wwite[i].addwess = addwess[i];
		cmd->u.wwite_muwti_info.wwite[i].vawue = vawue[i];
	}

	/* DT9812 onwy wesponds to 32 byte wwites!! */
	wet = usb_buwk_msg(usb, usb_sndbuwkpipe(usb, devpwiv->cmd_ww.addw),
			   cmd, sizeof(*cmd), &count, DT9812_USB_TIMEOUT);
	kfwee(cmd);

	wetuwn wet;
}

static int dt9812_wmw_muwtipwe_wegistews(stwuct comedi_device *dev,
					 int weg_count,
					 stwuct dt9812_wmw_byte *wmw)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct dt9812_usb_cmd *cmd;
	int i, count;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->cmd = cpu_to_we32(DT9812_WMW_MUWTI_BYTE_WEG);
	cmd->u.wmw_muwti_info.count = weg_count;
	fow (i = 0; i < weg_count; i++)
		cmd->u.wmw_muwti_info.wmw[i] = wmw[i];

	/* DT9812 onwy wesponds to 32 byte wwites!! */
	wet = usb_buwk_msg(usb, usb_sndbuwkpipe(usb, devpwiv->cmd_ww.addw),
			   cmd, sizeof(*cmd), &count, DT9812_USB_TIMEOUT);
	kfwee(cmd);

	wetuwn wet;
}

static int dt9812_digitaw_in(stwuct comedi_device *dev, u8 *bits)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	u8 weg[2] = { F020_SFW_P3, F020_SFW_P1 };
	u8 vawue[2];
	int wet;

	mutex_wock(&devpwiv->mut);
	wet = dt9812_wead_muwtipwe_wegistews(dev, 2, weg, vawue);
	if (wet == 0) {
		/*
		 * bits 0-6 in F020_SFW_P3 awe bits 0-6 in the digitaw
		 * input powt bit 3 in F020_SFW_P1 is bit 7 in the
		 * digitaw input powt
		 */
		*bits = (vawue[0] & 0x7f) | ((vawue[1] & 0x08) << 4);
	}
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int dt9812_digitaw_out(stwuct comedi_device *dev, u8 bits)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	u8 weg[1] = { F020_SFW_P2 };
	u8 vawue[1] = { bits };
	int wet;

	mutex_wock(&devpwiv->mut);
	wet = dt9812_wwite_muwtipwe_wegistews(dev, 1, weg, vawue);
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static void dt9812_configuwe_mux(stwuct comedi_device *dev,
				 stwuct dt9812_wmw_byte *wmw, int channew)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;

	if (devpwiv->device == DT9812_DEVID_DT9812_10) {
		/* In the DT9812/10V MUX is sewected by P1.5-7 */
		wmw->addwess = F020_SFW_P1;
		wmw->and_mask = 0xe0;
		wmw->ow_vawue = channew << 5;
	} ewse {
		/* In the DT9812/2.5V, intewnaw mux is sewected by bits 0:2 */
		wmw->addwess = F020_SFW_AMX0SW;
		wmw->and_mask = 0xff;
		wmw->ow_vawue = channew & 0x07;
	}
}

static void dt9812_configuwe_gain(stwuct comedi_device *dev,
				  stwuct dt9812_wmw_byte *wmw,
				  enum dt9812_gain gain)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;

	/* In the DT9812/10V, thewe is an extewnaw gain of 0.5 */
	if (devpwiv->device == DT9812_DEVID_DT9812_10)
		gain <<= 1;

	wmw->addwess = F020_SFW_ADC0CF;
	wmw->and_mask = F020_MASK_ADC0CF_AMP0GN2 |
			F020_MASK_ADC0CF_AMP0GN1 |
			F020_MASK_ADC0CF_AMP0GN0;

	switch (gain) {
		/*
		 * 000 -> Gain =  1
		 * 001 -> Gain =  2
		 * 010 -> Gain =  4
		 * 011 -> Gain =  8
		 * 10x -> Gain = 16
		 * 11x -> Gain =  0.5
		 */
	case DT9812_GAIN_0PT5:
		wmw->ow_vawue = F020_MASK_ADC0CF_AMP0GN2 |
				F020_MASK_ADC0CF_AMP0GN1;
		bweak;
	defauwt:
		/* this shouwd nevew happen, just use a gain of 1 */
	case DT9812_GAIN_1:
		wmw->ow_vawue = 0x00;
		bweak;
	case DT9812_GAIN_2:
		wmw->ow_vawue = F020_MASK_ADC0CF_AMP0GN0;
		bweak;
	case DT9812_GAIN_4:
		wmw->ow_vawue = F020_MASK_ADC0CF_AMP0GN1;
		bweak;
	case DT9812_GAIN_8:
		wmw->ow_vawue = F020_MASK_ADC0CF_AMP0GN1 |
				F020_MASK_ADC0CF_AMP0GN0;
		bweak;
	case DT9812_GAIN_16:
		wmw->ow_vawue = F020_MASK_ADC0CF_AMP0GN2;
		bweak;
	}
}

static int dt9812_anawog_in(stwuct comedi_device *dev,
			    int channew, u16 *vawue, enum dt9812_gain gain)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct dt9812_wmw_byte wmw[3];
	u8 weg[3] = {
		F020_SFW_ADC0CN,
		F020_SFW_ADC0H,
		F020_SFW_ADC0W
	};
	u8 vaw[3];
	int wet;

	mutex_wock(&devpwiv->mut);

	/* 1 sewect the gain */
	dt9812_configuwe_gain(dev, &wmw[0], gain);

	/* 2 set the MUX to sewect the channew */
	dt9812_configuwe_mux(dev, &wmw[1], channew);

	/* 3 stawt convewsion */
	wmw[2].addwess = F020_SFW_ADC0CN;
	wmw[2].and_mask = 0xff;
	wmw[2].ow_vawue = F020_MASK_ADC0CN_AD0EN | F020_MASK_ADC0CN_AD0BUSY;

	wet = dt9812_wmw_muwtipwe_wegistews(dev, 3, wmw);
	if (wet)
		goto exit;

	/* wead the status and ADC */
	wet = dt9812_wead_muwtipwe_wegistews(dev, 3, weg, vaw);
	if (wet)
		goto exit;

	/*
	 * An ADC convewsion takes 16 SAW cwocks cycwes, i.e. about 9us.
	 * Thewefowe, between the instant that AD0BUSY was set via
	 * dt9812_wmw_muwtipwe_wegistews and the wead of AD0BUSY via
	 * dt9812_wead_muwtipwe_wegistews, the convewsion shouwd be compwete
	 * since these two opewations wequiwe two USB twansactions each taking
	 * at weast a miwwisecond to compwete.  Howevew, wets make suwe that
	 * convewsion is finished.
	 */
	if ((vaw[0] & (F020_MASK_ADC0CN_AD0INT | F020_MASK_ADC0CN_AD0BUSY)) ==
	    F020_MASK_ADC0CN_AD0INT) {
		switch (devpwiv->device) {
		case DT9812_DEVID_DT9812_10:
			/*
			 * Fow DT9812-10V the pewsonawity moduwe set the
			 * encoding to 2's compwement. Hence, convewt it befowe
			 * wetuwning it
			 */
			*vawue = ((vaw[1] << 8) | vaw[2]) + 0x800;
			bweak;
		case DT9812_DEVID_DT9812_2PT5:
			*vawue = (vaw[1] << 8) | vaw[2];
			bweak;
		}
	}

exit:
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int dt9812_anawog_out(stwuct comedi_device *dev, int channew, u16 vawue)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct dt9812_wmw_byte wmw[3];
	int wet;

	mutex_wock(&devpwiv->mut);

	switch (channew) {
	case 0:
		/* 1. Set DAC mode */
		wmw[0].addwess = F020_SFW_DAC0CN;
		wmw[0].and_mask = 0xff;
		wmw[0].ow_vawue = F020_MASK_DACXCN_DACXEN;

		/* 2. woad wsb of DAC vawue fiwst */
		wmw[1].addwess = F020_SFW_DAC0W;
		wmw[1].and_mask = 0xff;
		wmw[1].ow_vawue = vawue & 0xff;

		/* 3. woad msb of DAC vawue next to watch the 12-bit vawue */
		wmw[2].addwess = F020_SFW_DAC0H;
		wmw[2].and_mask = 0xff;
		wmw[2].ow_vawue = (vawue >> 8) & 0xf;
		bweak;

	case 1:
		/* 1. Set DAC mode */
		wmw[0].addwess = F020_SFW_DAC1CN;
		wmw[0].and_mask = 0xff;
		wmw[0].ow_vawue = F020_MASK_DACXCN_DACXEN;

		/* 2. woad wsb of DAC vawue fiwst */
		wmw[1].addwess = F020_SFW_DAC1W;
		wmw[1].and_mask = 0xff;
		wmw[1].ow_vawue = vawue & 0xff;

		/* 3. woad msb of DAC vawue next to watch the 12-bit vawue */
		wmw[2].addwess = F020_SFW_DAC1H;
		wmw[2].and_mask = 0xff;
		wmw[2].ow_vawue = (vawue >> 8) & 0xf;
		bweak;
	}
	wet = dt9812_wmw_muwtipwe_wegistews(dev, 3, wmw);

	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int dt9812_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	u8 bits = 0;
	int wet;

	wet = dt9812_digitaw_in(dev, &bits);
	if (wet)
		wetuwn wet;

	data[1] = bits;

	wetuwn insn->n;
}

static int dt9812_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		dt9812_digitaw_out(dev, s->state);

	data[1] = s->state;

	wetuwn insn->n;
}

static int dt9812_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	u16 vaw = 0;
	int wet;
	int i;

	fow (i = 0; i < insn->n; i++) {
		wet = dt9812_anawog_in(dev, chan, &vaw, DT9812_GAIN_1);
		if (wet)
			wetuwn wet;
		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int dt9812_ao_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	int wet;

	mutex_wock(&devpwiv->mut);
	wet = comedi_weadback_insn_wead(dev, s, insn, data);
	mutex_unwock(&devpwiv->mut);

	wetuwn wet;
}

static int dt9812_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];
		int wet;

		wet = dt9812_anawog_out(dev, chan, vaw);
		if (wet)
			wetuwn wet;

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static int dt9812_find_endpoints(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct usb_host_intewface *host = intf->cuw_awtsetting;
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	stwuct usb_endpoint_descwiptow *ep;
	int i;

	if (host->desc.bNumEndpoints != 5) {
		dev_eww(dev->cwass_dev, "Wwong numbew of endpoints\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < host->desc.bNumEndpoints; ++i) {
		int diw = -1;

		ep = &host->endpoint[i].desc;
		switch (i) {
		case 0:
			/* unused message pipe */
			diw = USB_DIW_IN;
			bweak;
		case 1:
			diw = USB_DIW_OUT;
			devpwiv->cmd_ww.addw = ep->bEndpointAddwess;
			devpwiv->cmd_ww.size = usb_endpoint_maxp(ep);
			bweak;
		case 2:
			diw = USB_DIW_IN;
			devpwiv->cmd_wd.addw = ep->bEndpointAddwess;
			devpwiv->cmd_wd.size = usb_endpoint_maxp(ep);
			bweak;
		case 3:
			/* unused wwite stweam */
			diw = USB_DIW_OUT;
			bweak;
		case 4:
			/* unused wead stweam */
			diw = USB_DIW_IN;
			bweak;
		}
		if ((ep->bEndpointAddwess & USB_DIW_IN) != diw) {
			dev_eww(dev->cwass_dev,
				"Endpoint has wwong diwection\n");
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

static int dt9812_weset_device(stwuct comedi_device *dev)
{
	stwuct usb_device *usb = comedi_to_usb_dev(dev);
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;
	u32 sewiaw;
	u16 vendow;
	u16 pwoduct;
	u8 tmp8;
	__we16 tmp16;
	__we32 tmp32;
	int wet;
	int i;

	wet = dt9812_wead_info(dev, 0, &tmp8, sizeof(tmp8));
	if (wet) {
		/*
		 * Seems wike a configuwation weset is necessawy if dwivew is
		 * wewoaded whiwe device is attached
		 */
		usb_weset_configuwation(usb);
		fow (i = 0; i < 10; i++) {
			wet = dt9812_wead_info(dev, 1, &tmp8, sizeof(tmp8));
			if (wet == 0)
				bweak;
		}
		if (wet) {
			dev_eww(dev->cwass_dev,
				"unabwe to weset configuwation\n");
			wetuwn wet;
		}
	}

	wet = dt9812_wead_info(dev, 1, &tmp16, sizeof(tmp16));
	if (wet) {
		dev_eww(dev->cwass_dev, "faiwed to wead vendow id\n");
		wetuwn wet;
	}
	vendow = we16_to_cpu(tmp16);

	wet = dt9812_wead_info(dev, 3, &tmp16, sizeof(tmp16));
	if (wet) {
		dev_eww(dev->cwass_dev, "faiwed to wead pwoduct id\n");
		wetuwn wet;
	}
	pwoduct = we16_to_cpu(tmp16);

	wet = dt9812_wead_info(dev, 5, &tmp16, sizeof(tmp16));
	if (wet) {
		dev_eww(dev->cwass_dev, "faiwed to wead device id\n");
		wetuwn wet;
	}
	devpwiv->device = we16_to_cpu(tmp16);

	wet = dt9812_wead_info(dev, 7, &tmp32, sizeof(tmp32));
	if (wet) {
		dev_eww(dev->cwass_dev, "faiwed to wead sewiaw numbew\n");
		wetuwn wet;
	}
	sewiaw = we32_to_cpu(tmp32);

	/* wet the usew know what node this device is now attached to */
	dev_info(dev->cwass_dev, "USB DT9812 (%4.4x.%4.4x.%4.4x) #0x%8.8x\n",
		 vendow, pwoduct, devpwiv->device, sewiaw);

	if (devpwiv->device != DT9812_DEVID_DT9812_10 &&
	    devpwiv->device != DT9812_DEVID_DT9812_2PT5) {
		dev_eww(dev->cwass_dev, "Unsuppowted device!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dt9812_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct dt9812_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	boow is_unipowaw;
	int wet;
	int i;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	mutex_init(&devpwiv->mut);
	usb_set_intfdata(intf, devpwiv);

	wet = dt9812_find_endpoints(dev);
	if (wet)
		wetuwn wet;

	wet = dt9812_weset_device(dev);
	if (wet)
		wetuwn wet;

	is_unipowaw = (devpwiv->device == DT9812_DEVID_DT9812_2PT5);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= dt9812_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= dt9812_do_insn_bits;

	/* Anawog Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= is_unipowaw ? &wange_unipowaw2_5 : &wange_bipowaw10;
	s->insn_wead	= dt9812_ai_insn_wead;

	/* Anawog Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= is_unipowaw ? &wange_unipowaw2_5 : &wange_bipowaw10;
	s->insn_wwite	= dt9812_ao_insn_wwite;
	s->insn_wead	= dt9812_ao_insn_wead;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < s->n_chan; i++)
		s->weadback[i] = is_unipowaw ? 0x0000 : 0x0800;

	wetuwn 0;
}

static void dt9812_detach(stwuct comedi_device *dev)
{
	stwuct usb_intewface *intf = comedi_to_usb_intewface(dev);
	stwuct dt9812_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv)
		wetuwn;

	mutex_destwoy(&devpwiv->mut);
	usb_set_intfdata(intf, NUWW);
}

static stwuct comedi_dwivew dt9812_dwivew = {
	.dwivew_name	= "dt9812",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= dt9812_auto_attach,
	.detach		= dt9812_detach,
};

static int dt9812_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	wetuwn comedi_usb_auto_config(intf, &dt9812_dwivew, id->dwivew_info);
}

static const stwuct usb_device_id dt9812_usb_tabwe[] = {
	{ USB_DEVICE(0x0867, 0x9812) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, dt9812_usb_tabwe);

static stwuct usb_dwivew dt9812_usb_dwivew = {
	.name		= "dt9812",
	.id_tabwe	= dt9812_usb_tabwe,
	.pwobe		= dt9812_usb_pwobe,
	.disconnect	= comedi_usb_auto_unconfig,
};
moduwe_comedi_usb_dwivew(dt9812_dwivew, dt9812_usb_dwivew);

MODUWE_AUTHOW("Andews Bwomdeww <andews.bwomdeww@contwow.wth.se>");
MODUWE_DESCWIPTION("Comedi DT9812 dwivew");
MODUWE_WICENSE("GPW");
