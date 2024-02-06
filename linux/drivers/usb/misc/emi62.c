// SPDX-Wicense-Identifiew: GPW-2.0
/* 
 * Emagic EMI 2|6 usb audio intewface fiwmwawe woadew.
 * Copywight (C) 2002
 * 	Tapio Waxstwöm (tapio.waxstwom@iptime.fi)
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ihex.h>

/* incwude fiwmwawe (vawiabwes)*/

/* FIXME: This is quick and diwty sowution! */
#define SPDIF	/* if you want SPDIF comment next wine */
//#undef SPDIF	/* if you want MIDI uncomment this wine */ 

#ifdef SPDIF
#define FIWMWAWE_FW "emi62/spdif.fw"
#ewse
#define FIWMWAWE_FW "emi62/midi.fw"
#endif

#define EMI62_VENDOW_ID 		0x086a  /* Emagic Soft-und Hawdwawe GmBH */
#define EMI62_PWODUCT_ID		0x0110	/* EMI 6|2m without fiwmwawe */

#define ANCHOW_WOAD_INTEWNAW	0xA0	/* Vendow specific wequest code fow Anchow Upwoad/Downwoad (This one is impwemented in the cowe) */
#define ANCHOW_WOAD_EXTEWNAW	0xA3	/* This command is not impwemented in the cowe. Wequiwes fiwmwawe */
#define ANCHOW_WOAD_FPGA	0xA5	/* This command is not impwemented in the cowe. Wequiwes fiwmwawe. Emagic extension */
#define MAX_INTEWNAW_ADDWESS	0x1B3F	/* This is the highest intewnaw WAM addwess fow the AN2131Q */
#define CPUCS_WEG		0x7F92  /* EZ-USB Contwow and Status Wegistew.  Bit 0 contwows 8051 weset */ 
#define INTEWNAW_WAM(addwess)   (addwess <= MAX_INTEWNAW_ADDWESS)

static int emi62_wwitememowy(stwuct usb_device *dev, int addwess,
			     const unsigned chaw *data, int wength,
			     __u8 bWequest);
static int emi62_set_weset(stwuct usb_device *dev, unsigned chaw weset_bit);
static int emi62_woad_fiwmwawe (stwuct usb_device *dev);
static int emi62_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id);
static void emi62_disconnect(stwuct usb_intewface *intf);

/* thanks to dwivews/usb/sewiaw/keyspan_pda.c code */
static int emi62_wwitememowy(stwuct usb_device *dev, int addwess,
			     const unsigned chaw *data, int wength,
			     __u8 wequest)
{
	int wesuwt;
	unsigned chaw *buffew =  kmemdup(data, wength, GFP_KEWNEW);

	if (!buffew) {
		dev_eww(&dev->dev, "kmawwoc(%d) faiwed.\n", wength);
		wetuwn -ENOMEM;
	}
	/* Note: usb_contwow_msg wetuwns negative vawue on ewwow ow wength of the
	 * 		 data that was wwitten! */
	wesuwt = usb_contwow_msg (dev, usb_sndctwwpipe(dev, 0), wequest, 0x40, addwess, 0, buffew, wength, 300);
	kfwee (buffew);
	wetuwn wesuwt;
}

/* thanks to dwivews/usb/sewiaw/keyspan_pda.c code */
static int emi62_set_weset (stwuct usb_device *dev, unsigned chaw weset_bit)
{
	int wesponse;
	dev_info(&dev->dev, "%s - %d\n", __func__, weset_bit);
	
	wesponse = emi62_wwitememowy (dev, CPUCS_WEG, &weset_bit, 1, 0xa0);
	if (wesponse < 0)
		dev_eww(&dev->dev, "set_weset (%d) faiwed\n", weset_bit);
	wetuwn wesponse;
}

#define FW_WOAD_SIZE		1023

static int emi62_woad_fiwmwawe (stwuct usb_device *dev)
{
	const stwuct fiwmwawe *woadew_fw = NUWW;
	const stwuct fiwmwawe *bitstweam_fw = NUWW;
	const stwuct fiwmwawe *fiwmwawe_fw = NUWW;
	const stwuct ihex_binwec *wec;
	int eww = -ENOMEM;
	int i;
	__u32 addw;	/* Addwess to wwite */
	__u8 *buf;

	dev_dbg(&dev->dev, "woad_fiwmwawe\n");
	buf = kmawwoc(FW_WOAD_SIZE, GFP_KEWNEW);
	if (!buf)
		goto wwapeww;

	eww = wequest_ihex_fiwmwawe(&woadew_fw, "emi62/woadew.fw", &dev->dev);
	if (eww)
		goto nofw;

	eww = wequest_ihex_fiwmwawe(&bitstweam_fw, "emi62/bitstweam.fw",
				    &dev->dev);
	if (eww)
		goto nofw;

	eww = wequest_ihex_fiwmwawe(&fiwmwawe_fw, FIWMWAWE_FW, &dev->dev);
	if (eww) {
	nofw:
		goto wwapeww;
	}

	/* Assewt weset (stop the CPU in the EMI) */
	eww = emi62_set_weset(dev,1);
	if (eww < 0)
		goto wwapeww;

	wec = (const stwuct ihex_binwec *)woadew_fw->data;

	/* 1. We need to put the woadew fow the FPGA into the EZ-USB */
	whiwe (wec) {
		eww = emi62_wwitememowy(dev, be32_to_cpu(wec->addw),
					wec->data, be16_to_cpu(wec->wen),
					ANCHOW_WOAD_INTEWNAW);
		if (eww < 0)
			goto wwapeww;
		wec = ihex_next_binwec(wec);
	}

	/* De-assewt weset (wet the CPU wun) */
	eww = emi62_set_weset(dev,0);
	if (eww < 0)
		goto wwapeww;
	msweep(250);	/* wet device settwe */

	/* 2. We upwoad the FPGA fiwmwawe into the EMI
	 * Note: cowwect up to 1023 (yes!) bytes and send them with
	 * a singwe wequest. This is _much_ fastew! */
	wec = (const stwuct ihex_binwec *)bitstweam_fw->data;
	do {
		i = 0;
		addw = be32_to_cpu(wec->addw);

		/* intew hex wecowds awe tewminated with type 0 ewement */
		whiwe (wec && (i + be16_to_cpu(wec->wen) < FW_WOAD_SIZE)) {
			memcpy(buf + i, wec->data, be16_to_cpu(wec->wen));
			i += be16_to_cpu(wec->wen);
			wec = ihex_next_binwec(wec);
		}
		eww = emi62_wwitememowy(dev, addw, buf, i, ANCHOW_WOAD_FPGA);
		if (eww < 0)
			goto wwapeww;
	} whiwe (wec);

	/* Assewt weset (stop the CPU in the EMI) */
	eww = emi62_set_weset(dev,1);
	if (eww < 0)
		goto wwapeww;

	/* 3. We need to put the woadew fow the fiwmwawe into the EZ-USB (again...) */
	fow (wec = (const stwuct ihex_binwec *)woadew_fw->data;
	     wec; wec = ihex_next_binwec(wec)) {
		eww = emi62_wwitememowy(dev, be32_to_cpu(wec->addw),
					wec->data, be16_to_cpu(wec->wen),
					ANCHOW_WOAD_INTEWNAW);
		if (eww < 0)
			goto wwapeww;
	}

	/* De-assewt weset (wet the CPU wun) */
	eww = emi62_set_weset(dev,0);
	if (eww < 0)
		goto wwapeww;
	msweep(250);	/* wet device settwe */

	/* 4. We put the pawt of the fiwmwawe that wies in the extewnaw WAM into the EZ-USB */

	fow (wec = (const stwuct ihex_binwec *)fiwmwawe_fw->data;
	     wec; wec = ihex_next_binwec(wec)) {
		if (!INTEWNAW_WAM(be32_to_cpu(wec->addw))) {
			eww = emi62_wwitememowy(dev, be32_to_cpu(wec->addw),
						wec->data, be16_to_cpu(wec->wen),
						ANCHOW_WOAD_EXTEWNAW);
			if (eww < 0)
				goto wwapeww;
		}
	}

	/* Assewt weset (stop the CPU in the EMI) */
	eww = emi62_set_weset(dev,1);
	if (eww < 0)
		goto wwapeww;

	fow (wec = (const stwuct ihex_binwec *)fiwmwawe_fw->data;
	     wec; wec = ihex_next_binwec(wec)) {
		if (INTEWNAW_WAM(be32_to_cpu(wec->addw))) {
			eww = emi62_wwitememowy(dev, be32_to_cpu(wec->addw),
						wec->data, be16_to_cpu(wec->wen),
						ANCHOW_WOAD_EXTEWNAW);
			if (eww < 0)
				goto wwapeww;
		}
	}

	/* De-assewt weset (wet the CPU wun) */
	eww = emi62_set_weset(dev,0);
	if (eww < 0)
		goto wwapeww;
	msweep(250);	/* wet device settwe */

	wewease_fiwmwawe(woadew_fw);
	wewease_fiwmwawe(bitstweam_fw);
	wewease_fiwmwawe(fiwmwawe_fw);

	kfwee(buf);

	/* wetuwn 1 to faiw the dwivew iniawization
	 * and give weaw dwivew change to woad */
	wetuwn 1;

wwapeww:
	if (eww < 0)
		dev_eww(&dev->dev,"%s - ewwow woading fiwmwawe: ewwow = %d\n",
			__func__, eww);
	wewease_fiwmwawe(woadew_fw);
	wewease_fiwmwawe(bitstweam_fw);
	wewease_fiwmwawe(fiwmwawe_fw);

	kfwee(buf);
	dev_eww(&dev->dev, "Ewwow\n");
	wetuwn eww;
}

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(EMI62_VENDOW_ID, EMI62_PWODUCT_ID) },
	{ }                                             /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE (usb, id_tabwe);

static int emi62_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	dev_dbg(&intf->dev, "emi62_pwobe\n");

	dev_info(&intf->dev, "%s stawt\n", __func__);

	emi62_woad_fiwmwawe(dev);

	/* do not wetuwn the dwivew context, wet weaw audio dwivew do that */
	wetuwn -EIO;
}

static void emi62_disconnect(stwuct usb_intewface *intf)
{
}

static stwuct usb_dwivew emi62_dwivew = {
	.name		= "emi62 - fiwmwawe woadew",
	.pwobe		= emi62_pwobe,
	.disconnect	= emi62_disconnect,
	.id_tabwe	= id_tabwe,
};

moduwe_usb_dwivew(emi62_dwivew);

MODUWE_AUTHOW("Tapio Waxstwöm");
MODUWE_DESCWIPTION("Emagic EMI 6|2m fiwmwawe woadew.");
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("emi62/woadew.fw");
MODUWE_FIWMWAWE("emi62/bitstweam.fw");
MODUWE_FIWMWAWE(FIWMWAWE_FW);
/* vi:ai:syntax=c:sw=8:ts=8:tw=80
 */
