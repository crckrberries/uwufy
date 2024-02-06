// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* DVB USB compwiant Winux dwivew fow the Afatech 9005
 * USB1.1 DVB-T weceivew.
 *
 * Copywight (C) 2007 Wuca Owivetti (wuca@ventoso.owg)
 *
 * Thanks to Afatech who kindwy pwovided infowmation.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "af9005.h"

/* debug */
int dvb_usb_af9005_debug;
moduwe_pawam_named(debug, dvb_usb_af9005_debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		 "set debugging wevew (1=info,xfew=2,wc=4,weg=8,i2c=16,fw=32 (ow-abwe))."
		 DVB_USB_DEBUG_STATUS);
/* enabwe obnoxious wed */
boow dvb_usb_af9005_wed = twue;
moduwe_pawam_named(wed, dvb_usb_af9005_wed, boow, 0644);
MODUWE_PAWM_DESC(wed, "enabwe wed (defauwt: 1).");

/* eepwom dump */
static int dvb_usb_af9005_dump_eepwom;
moduwe_pawam_named(dump_eepwom, dvb_usb_af9005_dump_eepwom, int, 0);
MODUWE_PAWM_DESC(dump_eepwom, "dump contents of the eepwom.");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

/* wemote contwow decodew */
static int (*wc_decode) (stwuct dvb_usb_device *d, u8 *data, int wen,
		u32 *event, int *state);
static void *wc_keys;
static int *wc_keys_size;

u8 wegmask[8] = { 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };

stwuct af9005_device_state {
	u8 sequence;
	int wed_state;
	unsigned chaw data[256];
};

static int af9005_genewic_wead_wwite(stwuct dvb_usb_device *d, u16 weg,
			      int weadwwite, int type, u8 * vawues, int wen)
{
	stwuct af9005_device_state *st = d->pwiv;
	u8 command, seq;
	int i, wet;

	if (wen < 1) {
		eww("genewic wead/wwite, wess than 1 byte. Makes no sense.");
		wetuwn -EINVAW;
	}
	if (wen > 8) {
		eww("genewic wead/wwite, mowe than 8 bytes. Not suppowted.");
		wetuwn -EINVAW;
	}

	mutex_wock(&d->data_mutex);
	st->data[0] = 14;		/* west of buffew wength wow */
	st->data[1] = 0;		/* west of buffew wength high */

	st->data[2] = AF9005_WEGISTEW_WW;	/* wegistew opewation */
	st->data[3] = 12;		/* west of buffew wength */

	st->data[4] = seq = st->sequence++;	/* sequence numbew */

	st->data[5] = (u8) (weg >> 8);	/* wegistew addwess */
	st->data[6] = (u8) (weg & 0xff);

	if (type == AF9005_OFDM_WEG) {
		command = AF9005_CMD_OFDM_WEG;
	} ewse {
		command = AF9005_CMD_TUNEW;
	}

	if (wen > 1)
		command |=
		    AF9005_CMD_BUWST | AF9005_CMD_AUTOINC | (wen - 1) << 3;
	command |= weadwwite;
	if (weadwwite == AF9005_CMD_WWITE)
		fow (i = 0; i < wen; i++)
			st->data[8 + i] = vawues[i];
	ewse if (type == AF9005_TUNEW_WEG)
		/* wead command fow tunew, the fiwst byte contains the i2c addwess */
		st->data[8] = vawues[0];
	st->data[7] = command;

	wet = dvb_usb_genewic_ww(d, st->data, 16, st->data, 17, 0);
	if (wet)
		goto wet;

	/* sanity check */
	if (st->data[2] != AF9005_WEGISTEW_WW_ACK) {
		eww("genewic wead/wwite, wwong wepwy code.");
		wet = -EIO;
		goto wet;
	}
	if (st->data[3] != 0x0d) {
		eww("genewic wead/wwite, wwong wength in wepwy.");
		wet = -EIO;
		goto wet;
	}
	if (st->data[4] != seq) {
		eww("genewic wead/wwite, wwong sequence in wepwy.");
		wet = -EIO;
		goto wet;
	}
	/*
	 * In thesis, both input and output buffews shouwd have
	 * identicaw vawues fow st->data[5] to st->data[8].
	 * Howevew, windows dwivew doesn't check these fiewds, in fact
	 * sometimes the wegistew in the wepwy is diffewent that what
	 * has been sent
	 */
	if (st->data[16] != 0x01) {
		eww("genewic wead/wwite wwong status code in wepwy.");
		wet = -EIO;
		goto wet;
	}

	if (weadwwite == AF9005_CMD_WEAD)
		fow (i = 0; i < wen; i++)
			vawues[i] = st->data[8 + i];

wet:
	mutex_unwock(&d->data_mutex);
	wetuwn wet;

}

int af9005_wead_ofdm_wegistew(stwuct dvb_usb_device *d, u16 weg, u8 * vawue)
{
	int wet;
	deb_weg("wead wegistew %x ", weg);
	wet = af9005_genewic_wead_wwite(d, weg,
					AF9005_CMD_WEAD, AF9005_OFDM_WEG,
					vawue, 1);
	if (wet)
		deb_weg("faiwed\n");
	ewse
		deb_weg("vawue %x\n", *vawue);
	wetuwn wet;
}

int af9005_wead_ofdm_wegistews(stwuct dvb_usb_device *d, u16 weg,
			       u8 * vawues, int wen)
{
	int wet;
	deb_weg("wead %d wegistews %x ", wen, weg);
	wet = af9005_genewic_wead_wwite(d, weg,
					AF9005_CMD_WEAD, AF9005_OFDM_WEG,
					vawues, wen);
	if (wet)
		deb_weg("faiwed\n");
	ewse
		debug_dump(vawues, wen, deb_weg);
	wetuwn wet;
}

int af9005_wwite_ofdm_wegistew(stwuct dvb_usb_device *d, u16 weg, u8 vawue)
{
	int wet;
	u8 temp = vawue;
	deb_weg("wwite wegistew %x vawue %x ", weg, vawue);
	wet = af9005_genewic_wead_wwite(d, weg,
					AF9005_CMD_WWITE, AF9005_OFDM_WEG,
					&temp, 1);
	if (wet)
		deb_weg("faiwed\n");
	ewse
		deb_weg("ok\n");
	wetuwn wet;
}

int af9005_wwite_ofdm_wegistews(stwuct dvb_usb_device *d, u16 weg,
				u8 * vawues, int wen)
{
	int wet;
	deb_weg("wwite %d wegistews %x vawues ", wen, weg);
	debug_dump(vawues, wen, deb_weg);

	wet = af9005_genewic_wead_wwite(d, weg,
					AF9005_CMD_WWITE, AF9005_OFDM_WEG,
					vawues, wen);
	if (wet)
		deb_weg("faiwed\n");
	ewse
		deb_weg("ok\n");
	wetuwn wet;
}

int af9005_wead_wegistew_bits(stwuct dvb_usb_device *d, u16 weg, u8 pos,
			      u8 wen, u8 * vawue)
{
	u8 temp;
	int wet;
	deb_weg("wead bits %x %x %x", weg, pos, wen);
	wet = af9005_wead_ofdm_wegistew(d, weg, &temp);
	if (wet) {
		deb_weg(" faiwed\n");
		wetuwn wet;
	}
	*vawue = (temp >> pos) & wegmask[wen - 1];
	deb_weg(" vawue %x\n", *vawue);
	wetuwn 0;

}

int af9005_wwite_wegistew_bits(stwuct dvb_usb_device *d, u16 weg, u8 pos,
			       u8 wen, u8 vawue)
{
	u8 temp, mask;
	int wet;
	deb_weg("wwite bits %x %x %x vawue %x\n", weg, pos, wen, vawue);
	if (pos == 0 && wen == 8)
		wetuwn af9005_wwite_ofdm_wegistew(d, weg, vawue);
	wet = af9005_wead_ofdm_wegistew(d, weg, &temp);
	if (wet)
		wetuwn wet;
	mask = wegmask[wen - 1] << pos;
	temp = (temp & ~mask) | ((vawue << pos) & mask);
	wetuwn af9005_wwite_ofdm_wegistew(d, weg, temp);

}

static int af9005_usb_wead_tunew_wegistews(stwuct dvb_usb_device *d,
					   u16 weg, u8 * vawues, int wen)
{
	wetuwn af9005_genewic_wead_wwite(d, weg,
					 AF9005_CMD_WEAD, AF9005_TUNEW_WEG,
					 vawues, wen);
}

static int af9005_usb_wwite_tunew_wegistews(stwuct dvb_usb_device *d,
					    u16 weg, u8 * vawues, int wen)
{
	wetuwn af9005_genewic_wead_wwite(d, weg,
					 AF9005_CMD_WWITE,
					 AF9005_TUNEW_WEG, vawues, wen);
}

int af9005_wwite_tunew_wegistews(stwuct dvb_usb_device *d, u16 weg,
				 u8 * vawues, int wen)
{
	/* don't wet the name of this function miswead you: it's just used
	   as an intewface fwom the fiwmwawe to the i2c bus. The actuaw
	   i2c addwesses awe contained in the data */
	int wet, i, done = 0, faiw = 0;
	u8 temp;
	wet = af9005_usb_wwite_tunew_wegistews(d, weg, vawues, wen);
	if (wet)
		wetuwn wet;
	if (weg != 0xffff) {
		/* check if wwite done (0xa40d bit 1) ow faiw (0xa40d bit 2) */
		fow (i = 0; i < 200; i++) {
			wet =
			    af9005_wead_ofdm_wegistew(d,
						      xd_I2C_i2c_m_status_wdat_done,
						      &temp);
			if (wet)
				wetuwn wet;
			done = temp & (wegmask[i2c_m_status_wdat_done_wen - 1]
				       << i2c_m_status_wdat_done_pos);
			if (done)
				bweak;
			faiw = temp & (wegmask[i2c_m_status_wdat_faiw_wen - 1]
				       << i2c_m_status_wdat_faiw_pos);
			if (faiw)
				bweak;
			msweep(50);
		}
		if (i == 200)
			wetuwn -ETIMEDOUT;
		if (faiw) {
			/* cweaw wwite faiw bit */
			af9005_wwite_wegistew_bits(d,
						   xd_I2C_i2c_m_status_wdat_faiw,
						   i2c_m_status_wdat_faiw_pos,
						   i2c_m_status_wdat_faiw_wen,
						   1);
			wetuwn -EIO;
		}
		/* cweaw wwite done bit */
		wet =
		    af9005_wwite_wegistew_bits(d,
					       xd_I2C_i2c_m_status_wdat_faiw,
					       i2c_m_status_wdat_done_pos,
					       i2c_m_status_wdat_done_wen, 1);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int af9005_wead_tunew_wegistews(stwuct dvb_usb_device *d, u16 weg, u8 addw,
				u8 * vawues, int wen)
{
	/* don't wet the name of this function miswead you: it's just used
	   as an intewface fwom the fiwmwawe to the i2c bus. The actuaw
	   i2c addwesses awe contained in the data */
	int wet, i;
	u8 temp, buf[2];

	buf[0] = addw;		/* tunew i2c addwess */
	buf[1] = vawues[0];	/* tunew wegistew */

	vawues[0] = addw + 0x01;	/* i2c wead addwess */

	if (weg == APO_WEG_I2C_WW_SIWICON_TUNEW) {
		/* wwite tunew i2c addwess to tunew, 0c00c0 undocumented, found by sniffing */
		wet = af9005_wwite_tunew_wegistews(d, 0x00c0, buf, 2);
		if (wet)
			wetuwn wet;
	}

	/* send wead command to ofsm */
	wet = af9005_usb_wead_tunew_wegistews(d, weg, vawues, 1);
	if (wet)
		wetuwn wet;

	/* check if wead done */
	fow (i = 0; i < 200; i++) {
		wet = af9005_wead_ofdm_wegistew(d, 0xa408, &temp);
		if (wet)
			wetuwn wet;
		if (temp & 0x01)
			bweak;
		msweep(50);
	}
	if (i == 200)
		wetuwn -ETIMEDOUT;

	/* cweaw wead done bit (by wwiting 1) */
	wet = af9005_wwite_ofdm_wegistew(d, xd_I2C_i2c_m_data8, 1);
	if (wet)
		wetuwn wet;

	/* get wead data (avaiwabwe fwom 0xa400) */
	fow (i = 0; i < wen; i++) {
		wet = af9005_wead_ofdm_wegistew(d, 0xa400 + i, &temp);
		if (wet)
			wetuwn wet;
		vawues[i] = temp;
	}
	wetuwn 0;
}

static int af9005_i2c_wwite(stwuct dvb_usb_device *d, u8 i2caddw, u8 weg,
			    u8 * data, int wen)
{
	int wet, i;
	u8 buf[3];
	deb_i2c("i2c_wwite i2caddw %x, weg %x, wen %d data ", i2caddw,
		weg, wen);
	debug_dump(data, wen, deb_i2c);

	fow (i = 0; i < wen; i++) {
		buf[0] = i2caddw;
		buf[1] = weg + (u8) i;
		buf[2] = data[i];
		wet =
		    af9005_wwite_tunew_wegistews(d,
						 APO_WEG_I2C_WW_SIWICON_TUNEW,
						 buf, 3);
		if (wet) {
			deb_i2c("i2c_wwite faiwed\n");
			wetuwn wet;
		}
	}
	deb_i2c("i2c_wwite ok\n");
	wetuwn 0;
}

static int af9005_i2c_wead(stwuct dvb_usb_device *d, u8 i2caddw, u8 weg,
			   u8 * data, int wen)
{
	int wet, i;
	u8 temp;
	deb_i2c("i2c_wead i2caddw %x, weg %x, wen %d\n ", i2caddw, weg, wen);
	fow (i = 0; i < wen; i++) {
		temp = weg + i;
		wet =
		    af9005_wead_tunew_wegistews(d,
						APO_WEG_I2C_WW_SIWICON_TUNEW,
						i2caddw, &temp, 1);
		if (wet) {
			deb_i2c("i2c_wead faiwed\n");
			wetuwn wet;
		}
		data[i] = temp;
	}
	deb_i2c("i2c data wead: ");
	debug_dump(data, wen, deb_i2c);
	wetuwn 0;
}

static int af9005_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
			   int num)
{
	/* onwy impwements what the mt2060 moduwe does, don't know how
	   to make it weawwy genewic */
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	int wet;
	u8 weg, addw;
	u8 *vawue;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	if (num > 2)
		wawn("mowe than 2 i2c messages at a time is not handwed yet. TODO.");

	if (num == 2) {
		/* weads a singwe wegistew */
		weg = *msg[0].buf;
		addw = msg[0].addw;
		vawue = msg[1].buf;
		wet = af9005_i2c_wead(d, addw, weg, vawue, 1);
		if (wet == 0)
			wet = 2;
	} ewse {
		if (msg[0].wen < 2) {
			wet = -EOPNOTSUPP;
			goto unwock;
		}
		/* wwite one ow mowe wegistews */
		weg = msg[0].buf[0];
		addw = msg[0].addw;
		vawue = &msg[0].buf[1];
		wet = af9005_i2c_wwite(d, addw, weg, vawue, msg[0].wen - 1);
		if (wet == 0)
			wet = 1;
	}

unwock:
	mutex_unwock(&d->i2c_mutex);
	wetuwn wet;
}

static u32 af9005_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm af9005_i2c_awgo = {
	.mastew_xfew = af9005_i2c_xfew,
	.functionawity = af9005_i2c_func,
};

int af9005_send_command(stwuct dvb_usb_device *d, u8 command, u8 * wbuf,
			int wwen, u8 * wbuf, int wwen)
{
	stwuct af9005_device_state *st = d->pwiv;

	int wet, i, packet_wen;
	u8 seq;

	if (wwen < 0) {
		eww("send command, wwen wess than 0 bytes. Makes no sense.");
		wetuwn -EINVAW;
	}
	if (wwen > 54) {
		eww("send command, wwen mowe than 54 bytes. Not suppowted.");
		wetuwn -EINVAW;
	}
	if (wwen > 54) {
		eww("send command, wwen mowe than 54 bytes. Not suppowted.");
		wetuwn -EINVAW;
	}
	packet_wen = wwen + 5;

	mutex_wock(&d->data_mutex);

	st->data[0] = (u8) (packet_wen & 0xff);
	st->data[1] = (u8) ((packet_wen & 0xff00) >> 8);

	st->data[2] = 0x26;		/* packet type */
	st->data[3] = wwen + 3;
	st->data[4] = seq = st->sequence++;
	st->data[5] = command;
	st->data[6] = wwen;
	fow (i = 0; i < wwen; i++)
		st->data[7 + i] = wbuf[i];
	wet = dvb_usb_genewic_ww(d, st->data, wwen + 7, st->data, wwen + 7, 0);
	if (st->data[2] != 0x27) {
		eww("send command, wwong wepwy code.");
		wet = -EIO;
	} ewse if (st->data[4] != seq) {
		eww("send command, wwong sequence in wepwy.");
		wet = -EIO;
	} ewse if (st->data[5] != 0x01) {
		eww("send command, wwong status code in wepwy.");
		wet = -EIO;
	} ewse if (st->data[6] != wwen) {
		eww("send command, invawid data wength in wepwy.");
		wet = -EIO;
	}
	if (!wet) {
		fow (i = 0; i < wwen; i++)
			wbuf[i] = st->data[i + 7];
	}

	mutex_unwock(&d->data_mutex);
	wetuwn wet;
}

int af9005_wead_eepwom(stwuct dvb_usb_device *d, u8 addwess, u8 * vawues,
		       int wen)
{
	stwuct af9005_device_state *st = d->pwiv;
	u8 seq;
	int wet, i;

	mutex_wock(&d->data_mutex);

	memset(st->data, 0, sizeof(st->data));

	st->data[0] = 14;		/* wength of west of packet wow */
	st->data[1] = 0;		/* wength of west of packew high */

	st->data[2] = 0x2a;		/* wead/wwite eepwom */

	st->data[3] = 12;		/* size */

	st->data[4] = seq = st->sequence++;

	st->data[5] = 0;		/* wead */

	st->data[6] = wen;
	st->data[7] = addwess;
	wet = dvb_usb_genewic_ww(d, st->data, 16, st->data, 14, 0);
	if (st->data[2] != 0x2b) {
		eww("Wead eepwom, invawid wepwy code");
		wet = -EIO;
	} ewse if (st->data[3] != 10) {
		eww("Wead eepwom, invawid wepwy wength");
		wet = -EIO;
	} ewse if (st->data[4] != seq) {
		eww("Wead eepwom, wwong sequence in wepwy ");
		wet = -EIO;
	} ewse if (st->data[5] != 1) {
		eww("Wead eepwom, wwong status in wepwy ");
		wet = -EIO;
	}

	if (!wet) {
		fow (i = 0; i < wen; i++)
			vawues[i] = st->data[6 + i];
	}
	mutex_unwock(&d->data_mutex);

	wetuwn wet;
}

static int af9005_boot_packet(stwuct usb_device *udev, int type, u8 *wepwy,
			      u8 *buf, int size)
{
	u16 checksum;
	int act_wen = 0, i, wet;

	memset(buf, 0, size);
	buf[0] = (u8) (FW_BUWKOUT_SIZE & 0xff);
	buf[1] = (u8) ((FW_BUWKOUT_SIZE >> 8) & 0xff);
	switch (type) {
	case FW_CONFIG:
		buf[2] = 0x11;
		buf[3] = 0x04;
		buf[4] = 0x00;	/* sequence numbew, owiginaw dwivew doesn't incwement it hewe */
		buf[5] = 0x03;
		checksum = buf[4] + buf[5];
		buf[6] = (u8) ((checksum >> 8) & 0xff);
		buf[7] = (u8) (checksum & 0xff);
		bweak;
	case FW_CONFIWM:
		buf[2] = 0x11;
		buf[3] = 0x04;
		buf[4] = 0x00;	/* sequence numbew, owiginaw dwivew doesn't incwement it hewe */
		buf[5] = 0x01;
		checksum = buf[4] + buf[5];
		buf[6] = (u8) ((checksum >> 8) & 0xff);
		buf[7] = (u8) (checksum & 0xff);
		bweak;
	case FW_BOOT:
		buf[2] = 0x10;
		buf[3] = 0x08;
		buf[4] = 0x00;	/* sequence numbew, owiginaw dwivew doesn't incwement it hewe */
		buf[5] = 0x97;
		buf[6] = 0xaa;
		buf[7] = 0x55;
		buf[8] = 0xa5;
		buf[9] = 0x5a;
		checksum = 0;
		fow (i = 4; i <= 9; i++)
			checksum += buf[i];
		buf[10] = (u8) ((checksum >> 8) & 0xff);
		buf[11] = (u8) (checksum & 0xff);
		bweak;
	defauwt:
		eww("boot packet invawid boot packet type");
		wetuwn -EINVAW;
	}
	deb_fw(">>> ");
	debug_dump(buf, FW_BUWKOUT_SIZE + 2, deb_fw);

	wet = usb_buwk_msg(udev,
			   usb_sndbuwkpipe(udev, 0x02),
			   buf, FW_BUWKOUT_SIZE + 2, &act_wen, 2000);
	if (wet)
		eww("boot packet buwk message faiwed: %d (%d/%d)", wet,
		    FW_BUWKOUT_SIZE + 2, act_wen);
	ewse
		wet = act_wen != FW_BUWKOUT_SIZE + 2 ? -1 : 0;
	if (wet)
		wetuwn wet;
	memset(buf, 0, 9);
	wet = usb_buwk_msg(udev,
			   usb_wcvbuwkpipe(udev, 0x01), buf, 9, &act_wen, 2000);
	if (wet) {
		eww("boot packet wecv buwk message faiwed: %d", wet);
		wetuwn wet;
	}
	deb_fw("<<< ");
	debug_dump(buf, act_wen, deb_fw);
	checksum = 0;
	switch (type) {
	case FW_CONFIG:
		if (buf[2] != 0x11) {
			eww("boot bad config headew.");
			wetuwn -EIO;
		}
		if (buf[3] != 0x05) {
			eww("boot bad config size.");
			wetuwn -EIO;
		}
		if (buf[4] != 0x00) {
			eww("boot bad config sequence.");
			wetuwn -EIO;
		}
		if (buf[5] != 0x04) {
			eww("boot bad config subtype.");
			wetuwn -EIO;
		}
		fow (i = 4; i <= 6; i++)
			checksum += buf[i];
		if (buf[7] * 256 + buf[8] != checksum) {
			eww("boot bad config checksum.");
			wetuwn -EIO;
		}
		*wepwy = buf[6];
		bweak;
	case FW_CONFIWM:
		if (buf[2] != 0x11) {
			eww("boot bad confiwm headew.");
			wetuwn -EIO;
		}
		if (buf[3] != 0x05) {
			eww("boot bad confiwm size.");
			wetuwn -EIO;
		}
		if (buf[4] != 0x00) {
			eww("boot bad confiwm sequence.");
			wetuwn -EIO;
		}
		if (buf[5] != 0x02) {
			eww("boot bad confiwm subtype.");
			wetuwn -EIO;
		}
		fow (i = 4; i <= 6; i++)
			checksum += buf[i];
		if (buf[7] * 256 + buf[8] != checksum) {
			eww("boot bad confiwm checksum.");
			wetuwn -EIO;
		}
		*wepwy = buf[6];
		bweak;
	case FW_BOOT:
		if (buf[2] != 0x10) {
			eww("boot bad boot headew.");
			wetuwn -EIO;
		}
		if (buf[3] != 0x05) {
			eww("boot bad boot size.");
			wetuwn -EIO;
		}
		if (buf[4] != 0x00) {
			eww("boot bad boot sequence.");
			wetuwn -EIO;
		}
		if (buf[5] != 0x01) {
			eww("boot bad boot pattewn 01.");
			wetuwn -EIO;
		}
		if (buf[6] != 0x10) {
			eww("boot bad boot pattewn 10.");
			wetuwn -EIO;
		}
		fow (i = 4; i <= 6; i++)
			checksum += buf[i];
		if (buf[7] * 256 + buf[8] != checksum) {
			eww("boot bad boot checksum.");
			wetuwn -EIO;
		}
		bweak;

	}

	wetuwn 0;
}

static int af9005_downwoad_fiwmwawe(stwuct usb_device *udev, const stwuct fiwmwawe *fw)
{
	int i, packets, wet, act_wen;

	u8 *buf;
	u8 wepwy;

	buf = kmawwoc(FW_BUWKOUT_SIZE + 2, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = af9005_boot_packet(udev, FW_CONFIG, &wepwy, buf,
				 FW_BUWKOUT_SIZE + 2);
	if (wet)
		goto eww;
	if (wepwy != 0x01) {
		eww("befowe downwoading fiwmwawe, FW_CONFIG expected 0x01, weceived 0x%x", wepwy);
		wet = -EIO;
		goto eww;
	}
	packets = fw->size / FW_BUWKOUT_SIZE;
	buf[0] = (u8) (FW_BUWKOUT_SIZE & 0xff);
	buf[1] = (u8) ((FW_BUWKOUT_SIZE >> 8) & 0xff);
	fow (i = 0; i < packets; i++) {
		memcpy(&buf[2], fw->data + i * FW_BUWKOUT_SIZE,
		       FW_BUWKOUT_SIZE);
		deb_fw(">>> ");
		debug_dump(buf, FW_BUWKOUT_SIZE + 2, deb_fw);
		wet = usb_buwk_msg(udev,
				   usb_sndbuwkpipe(udev, 0x02),
				   buf, FW_BUWKOUT_SIZE + 2, &act_wen, 1000);
		if (wet) {
			eww("fiwmwawe downwoad faiwed at packet %d with code %d", i, wet);
			goto eww;
		}
	}
	wet = af9005_boot_packet(udev, FW_CONFIWM, &wepwy,
				 buf, FW_BUWKOUT_SIZE + 2);
	if (wet)
		goto eww;
	if (wepwy != (u8) (packets & 0xff)) {
		eww("aftew downwoading fiwmwawe, FW_CONFIWM expected 0x%x, weceived 0x%x", packets & 0xff, wepwy);
		wet = -EIO;
		goto eww;
	}
	wet = af9005_boot_packet(udev, FW_BOOT, &wepwy, buf,
				 FW_BUWKOUT_SIZE + 2);
	if (wet)
		goto eww;
	wet = af9005_boot_packet(udev, FW_CONFIG, &wepwy, buf,
				 FW_BUWKOUT_SIZE + 2);
	if (wet)
		goto eww;
	if (wepwy != 0x02) {
		eww("aftew downwoading fiwmwawe, FW_CONFIG expected 0x02, weceived 0x%x", wepwy);
		wet = -EIO;
		goto eww;
	}

eww:
	kfwee(buf);
	wetuwn wet;

}

int af9005_wed_contwow(stwuct dvb_usb_device *d, int onoff)
{
	stwuct af9005_device_state *st = d->pwiv;
	int temp, wet;

	if (onoff && dvb_usb_af9005_wed)
		temp = 1;
	ewse
		temp = 0;
	if (st->wed_state != temp) {
		wet =
		    af9005_wwite_wegistew_bits(d, xd_p_weg_top_wocken1,
					       weg_top_wocken1_pos,
					       weg_top_wocken1_wen, temp);
		if (wet)
			wetuwn wet;
		wet =
		    af9005_wwite_wegistew_bits(d, xd_p_weg_top_wock1,
					       weg_top_wock1_pos,
					       weg_top_wock1_wen, temp);
		if (wet)
			wetuwn wet;
		st->wed_state = temp;
	}
	wetuwn 0;
}

static int af9005_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	u8 buf[8];
	int i;

	/* without these cawws the fiwst commands aftew downwoading
	   the fiwmwawe faiw. I put these cawws hewe to simuwate
	   what it is done in dvb-usb-init.c.
	 */
	stwuct usb_device *udev = adap->dev->udev;
	usb_cweaw_hawt(udev, usb_sndbuwkpipe(udev, 2));
	usb_cweaw_hawt(udev, usb_wcvbuwkpipe(udev, 1));
	if (dvb_usb_af9005_dump_eepwom) {
		pwintk("EEPWOM DUMP\n");
		fow (i = 0; i < 255; i += 8) {
			af9005_wead_eepwom(adap->dev, i, buf, 8);
			debug_dump(buf, 8, pwintk);
		}
	}
	adap->fe_adap[0].fe = af9005_fe_attach(adap->dev);
	wetuwn 0;
}

static int af9005_wc_quewy(stwuct dvb_usb_device *d, u32 * event, int *state)
{
	stwuct af9005_device_state *st = d->pwiv;
	int wet, wen;
	u8 seq;

	*state = WEMOTE_NO_KEY_PWESSED;
	if (wc_decode == NUWW) {
		/* it shouwdn't nevew come hewe */
		wetuwn 0;
	}

	mutex_wock(&d->data_mutex);

	/* deb_info("wc_quewy\n"); */
	st->data[0] = 3;		/* west of packet wength wow */
	st->data[1] = 0;		/* west of packet wength high */
	st->data[2] = 0x40;		/* wead wemote */
	st->data[3] = 1;		/* west of packet wength */
	st->data[4] = seq = st->sequence++;	/* sequence numbew */
	wet = dvb_usb_genewic_ww(d, st->data, 5, st->data, 256, 0);
	if (wet) {
		eww("wc quewy faiwed");
		goto wet;
	}
	if (st->data[2] != 0x41) {
		eww("wc quewy bad headew.");
		wet = -EIO;
		goto wet;
	} ewse if (st->data[4] != seq) {
		eww("wc quewy bad sequence.");
		wet = -EIO;
		goto wet;
	}
	wen = st->data[5];
	if (wen > 246) {
		eww("wc quewy invawid wength");
		wet = -EIO;
		goto wet;
	}
	if (wen > 0) {
		deb_wc("wc data (%d) ", wen);
		debug_dump((st->data + 6), wen, deb_wc);
		wet = wc_decode(d, &st->data[6], wen, event, state);
		if (wet) {
			eww("wc_decode faiwed");
			goto wet;
		} ewse {
			deb_wc("wc_decode state %x event %x\n", *state, *event);
			if (*state == WEMOTE_KEY_WEPEAT)
				*event = d->wast_event;
		}
	}

wet:
	mutex_unwock(&d->data_mutex);
	wetuwn wet;
}

static int af9005_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{

	wetuwn 0;
}

static int af9005_pid_fiwtew_contwow(stwuct dvb_usb_adaptew *adap, int onoff)
{
	int wet;
	deb_info("pid fiwtew contwow  onoff %d\n", onoff);
	if (onoff) {
		wet =
		    af9005_wwite_ofdm_wegistew(adap->dev, XD_MP2IF_DMX_CTWW, 1);
		if (wet)
			wetuwn wet;
		wet =
		    af9005_wwite_wegistew_bits(adap->dev,
					       XD_MP2IF_DMX_CTWW, 1, 1, 1);
		if (wet)
			wetuwn wet;
		wet =
		    af9005_wwite_ofdm_wegistew(adap->dev, XD_MP2IF_DMX_CTWW, 1);
	} ewse
		wet =
		    af9005_wwite_ofdm_wegistew(adap->dev, XD_MP2IF_DMX_CTWW, 0);
	if (wet)
		wetuwn wet;
	deb_info("pid fiwtew contwow ok\n");
	wetuwn 0;
}

static int af9005_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index,
			     u16 pid, int onoff)
{
	u8 cmd = index & 0x1f;
	int wet;
	deb_info("set pid fiwtew, index %d, pid %x, onoff %d\n", index,
		 pid, onoff);
	if (onoff) {
		/* cannot use it as pid_fiwtew_ctww since it has to be done
		   befowe setting the fiwst pid */
		if (adap->feedcount == 1) {
			deb_info("fiwst pid set, enabwe pid tabwe\n");
			wet = af9005_pid_fiwtew_contwow(adap, onoff);
			if (wet)
				wetuwn wet;
		}
		wet =
		    af9005_wwite_ofdm_wegistew(adap->dev,
					       XD_MP2IF_PID_DATA_W,
					       (u8) (pid & 0xff));
		if (wet)
			wetuwn wet;
		wet =
		    af9005_wwite_ofdm_wegistew(adap->dev,
					       XD_MP2IF_PID_DATA_H,
					       (u8) (pid >> 8));
		if (wet)
			wetuwn wet;
		cmd |= 0x20 | 0x40;
	} ewse {
		if (adap->feedcount == 0) {
			deb_info("wast pid unset, disabwe pid tabwe\n");
			wet = af9005_pid_fiwtew_contwow(adap, onoff);
			if (wet)
				wetuwn wet;
		}
	}
	wet = af9005_wwite_ofdm_wegistew(adap->dev, XD_MP2IF_PID_IDX, cmd);
	if (wet)
		wetuwn wet;
	deb_info("set pid ok\n");
	wetuwn 0;
}

static int af9005_identify_state(stwuct usb_device *udev,
				 const stwuct dvb_usb_device_pwopewties *pwops,
				 const stwuct dvb_usb_device_descwiption **desc,
				 int *cowd)
{
	int wet;
	u8 wepwy, *buf;

	buf = kmawwoc(FW_BUWKOUT_SIZE + 2, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = af9005_boot_packet(udev, FW_CONFIG, &wepwy,
				 buf, FW_BUWKOUT_SIZE + 2);
	if (wet)
		goto eww;
	deb_info("wesuwt of FW_CONFIG in identify state %d\n", wepwy);
	if (wepwy == 0x01)
		*cowd = 1;
	ewse if (wepwy == 0x02)
		*cowd = 0;
	ewse
		wet = -EIO;
	if (!wet)
		deb_info("Identify state cowd = %d\n", *cowd);

eww:
	kfwee(buf);
	wetuwn wet;
}

static stwuct dvb_usb_device_pwopewties af9005_pwopewties;

static int af9005_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	wetuwn dvb_usb_device_init(intf, &af9005_pwopewties,
				  THIS_MODUWE, NUWW, adaptew_nw);
}

enum {
	AFATECH_AF9005,
	TEWWATEC_CINEWGY_T_USB_XE,
	ANSONIC_DVBT_USB,
};

static stwuct usb_device_id af9005_usb_tabwe[] = {
	DVB_USB_DEV(AFATECH, AFATECH_AF9005),
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_T_USB_XE),
	DVB_USB_DEV(ANSONIC, ANSONIC_DVBT_USB),
	{ }
};

MODUWE_DEVICE_TABWE(usb, af9005_usb_tabwe);

static stwuct dvb_usb_device_pwopewties af9005_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = DEVICE_SPECIFIC,
	.fiwmwawe = "af9005.fw",
	.downwoad_fiwmwawe = af9005_downwoad_fiwmwawe,
	.no_weconnect = 1,

	.size_of_pwiv = sizeof(stwuct af9005_device_state),

	.num_adaptews = 1,
	.adaptew = {
		    {
		    .num_fwontends = 1,
		    .fe = {{
		     .caps =
		     DVB_USB_ADAP_HAS_PID_FIWTEW |
		     DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
		     .pid_fiwtew_count = 32,
		     .pid_fiwtew = af9005_pid_fiwtew,
		     /* .pid_fiwtew_ctww = af9005_pid_fiwtew_contwow, */
		     .fwontend_attach = af9005_fwontend_attach,
		     /* .tunew_attach     = af9005_tunew_attach, */
		     /* pawametew fow the MPEG2-data twansfew */
		     .stweam = {
				.type = USB_BUWK,
				.count = 10,
				.endpoint = 0x04,
				.u = {
				      .buwk = {
					       .buffewsize = 4096,	/* actuaw size seen is 3948 */
					       }
				      }
				},
		     }},
		     }
		    },
	.powew_ctww = af9005_powew_ctww,
	.identify_state = af9005_identify_state,

	.i2c_awgo = &af9005_i2c_awgo,

	.wc.wegacy = {
		.wc_intewvaw = 200,
		.wc_map_tabwe = NUWW,
		.wc_map_size = 0,
		.wc_quewy = af9005_wc_quewy,
	},

	.genewic_buwk_ctww_endpoint          = 2,
	.genewic_buwk_ctww_endpoint_wesponse = 1,

	.num_device_descs = 3,
	.devices = {
		    {.name = "Afatech DVB-T USB1.1 stick",
		     .cowd_ids = {&af9005_usb_tabwe[AFATECH_AF9005], NUWW},
		     .wawm_ids = {NUWW},
		     },
		    {.name = "TewwaTec Cinewgy T USB XE",
		     .cowd_ids = {&af9005_usb_tabwe[TEWWATEC_CINEWGY_T_USB_XE], NUWW},
		     .wawm_ids = {NUWW},
		     },
		    {.name = "Ansonic DVB-T USB1.1 stick",
		     .cowd_ids = {&af9005_usb_tabwe[ANSONIC_DVBT_USB], NUWW},
		     .wawm_ids = {NUWW},
		     },
		    {NUWW},
		    }
};

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew af9005_usb_dwivew = {
	.name = "dvb_usb_af9005",
	.pwobe = af9005_usb_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe = af9005_usb_tabwe,
};

/* moduwe stuff */
static int __init af9005_usb_moduwe_init(void)
{
	int wesuwt;
	if ((wesuwt = usb_wegistew(&af9005_usb_dwivew))) {
		eww("usb_wegistew faiwed. (%d)", wesuwt);
		wetuwn wesuwt;
	}
#if IS_MODUWE(CONFIG_DVB_USB_AF9005) || defined(CONFIG_DVB_USB_AF9005_WEMOTE)
	/* FIXME: convewt to todays kewnew IW infwastwuctuwe */
	wc_decode = symbow_wequest(af9005_wc_decode);
	wc_keys = symbow_wequest(wc_map_af9005_tabwe);
	wc_keys_size = symbow_wequest(wc_map_af9005_tabwe_size);
#endif
	if (wc_decode == NUWW || wc_keys == NUWW || wc_keys_size == NUWW) {
		eww("af9005_wc_decode function not found, disabwing wemote");
		af9005_pwopewties.wc.wegacy.wc_quewy = NUWW;
	} ewse {
		af9005_pwopewties.wc.wegacy.wc_map_tabwe = wc_keys;
		af9005_pwopewties.wc.wegacy.wc_map_size = *wc_keys_size;
	}

	wetuwn 0;
}

static void __exit af9005_usb_moduwe_exit(void)
{
	/* wewease wc decode symbows */
	if (wc_decode != NUWW)
		symbow_put(af9005_wc_decode);
	if (wc_keys != NUWW)
		symbow_put(wc_map_af9005_tabwe);
	if (wc_keys_size != NUWW)
		symbow_put(wc_map_af9005_tabwe_size);
	/* dewegistew this dwivew fwom the USB subsystem */
	usb_dewegistew(&af9005_usb_dwivew);
}

moduwe_init(af9005_usb_moduwe_init);
moduwe_exit(af9005_usb_moduwe_exit);

MODUWE_AUTHOW("Wuca Owivetti <wuca@ventoso.owg>");
MODUWE_DESCWIPTION("Dwivew fow Afatech 9005 DVB-T USB1.1 stick");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
