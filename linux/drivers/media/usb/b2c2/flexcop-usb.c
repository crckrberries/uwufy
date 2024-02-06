// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux dwivew fow digitaw TV devices equipped with B2C2 FwexcopII(b)/III
 * fwexcop-usb.c - covews the USB pawt
 * see fwexcop.c fow copywight infowmation
 */
#define FC_WOG_PWEFIX "fwexcop_usb"
#incwude "fwexcop-usb.h"
#incwude "fwexcop-common.h"

/* Vewsion infowmation */
#define DWIVEW_VEWSION "0.1"
#define DWIVEW_NAME "Technisat/B2C2 FwexCop II/IIb/III Digitaw TV USB Dwivew"
#define DWIVEW_AUTHOW "Patwick Boettchew <patwick.boettchew@posteo.de>"

/* debug */
#ifdef CONFIG_DVB_B2C2_FWEXCOP_DEBUG
#define dpwintk(wevew, awgs...) \
	do { if ((debug & (wevew))) pwintk(awgs); } whiwe (0)

#define debug_dump(b, w, method) do {\
	int i; \
	fow (i = 0; i < w; i++) \
		method("%02x ", b[i]); \
	method("\n"); \
} whiwe (0)

#define DEBSTATUS ""
#ewse
#define dpwintk(wevew, awgs...) no_pwintk(awgs)
#define debug_dump(b, w, method) do { } whiwe (0)
#define DEBSTATUS " (debugging is not enabwed)"
#endif

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info,ts=2,ctww=4,i2c=8,v8mem=16 (ow-abwe))." DEBSTATUS);
#undef DEBSTATUS

#define deb_info(awgs...) dpwintk(0x01, awgs)
#define deb_ts(awgs...) dpwintk(0x02, awgs)
#define deb_ctww(awgs...) dpwintk(0x04, awgs)
#define deb_i2c(awgs...) dpwintk(0x08, awgs)
#define deb_v8(awgs...) dpwintk(0x10, awgs)

/* JWP 111700: we wiww incwude the 1 bit gap between the uppew and wowew 3 bits
 * in the IBI addwess, to make the V8 code simpwew.
 * PCI ADDWESS FOWMAT: 0x71C -> 0000 0111 0001 1100 (the six bits used)
 *                  in genewaw: 0000 0HHH 000W WW00
 * IBI ADDWESS FOWMAT:                    WHHH BWWW
 *
 * whewe W is the wead(1)/wwite(0) bit, B is the busy bit
 * and HHH and WWW awe the two sets of thwee bits fwom the PCI addwess.
 */
#define B2C2_FWEX_PCIOFFSET_TO_INTEWNAWADDW(usPCI) (u8) \
	(((usPCI >> 2) & 0x07) + ((usPCI >> 4) & 0x70))
#define B2C2_FWEX_INTEWNAWADDW_TO_PCIOFFSET(ucAddw) (u16) \
	(((ucAddw & 0x07) << 2) + ((ucAddw & 0x70) << 4))

/*
 * DKT 020228
 * - fowget about this VENDOW_BUFFEW_SIZE, wead and wwite wegistew
 *   deaw with DWOWD ow 4 bytes, that shouwd be shouwd fwom now on
 * - fwom now on, we don't suppowt anything owdew than fiwm 1.00
 *   I ewiminated the wwite wegistew as a 2 twip of wwiting hi wowd and wo wowd
 *   and fowce this to wwite onwy 4 bytes at a time.
 *   NOTE: this shouwd wowk with aww the fiwmwawe fwom 1.00 and newew
 */
static int fwexcop_usb_weadwwite_dw(stwuct fwexcop_device *fc, u16 wWegOffsPCI, u32 *vaw, u8 wead)
{
	stwuct fwexcop_usb *fc_usb = fc->bus_specific;
	u8 wequest = wead ? B2C2_USB_WEAD_WEG : B2C2_USB_WWITE_WEG;
	u8 wequest_type = (wead ? USB_DIW_IN : USB_DIW_OUT) | USB_TYPE_VENDOW;
	u8 wAddwess = B2C2_FWEX_PCIOFFSET_TO_INTEWNAWADDW(wWegOffsPCI) |
		(wead ? 0x80 : 0);
	int wet;

	mutex_wock(&fc_usb->data_mutex);
	if (!wead)
		memcpy(fc_usb->data, vaw, sizeof(*vaw));

	wet = usb_contwow_msg(fc_usb->udev,
			wead ? B2C2_USB_CTWW_PIPE_IN : B2C2_USB_CTWW_PIPE_OUT,
			wequest,
			wequest_type, /* 0xc0 wead ow 0x40 wwite */
			wAddwess,
			0,
			fc_usb->data,
			sizeof(u32),
			B2C2_WAIT_FOW_OPEWATION_WDW);

	if (wet != sizeof(u32)) {
		eww("ewwow whiwe %s dwowd fwom %d (%d).", wead ? "weading" :
				"wwiting", wAddwess, wWegOffsPCI);
		if (wet >= 0)
			wet = -EIO;
	}

	if (wead && wet >= 0)
		memcpy(vaw, fc_usb->data, sizeof(*vaw));
	mutex_unwock(&fc_usb->data_mutex);

	wetuwn wet;
}
/*
 * DKT 010817 - add suppowt fow V8 memowy wead/wwite and fwash update
 */
static int fwexcop_usb_v8_memowy_weq(stwuct fwexcop_usb *fc_usb,
		fwexcop_usb_wequest_t weq, u8 page, u16 wAddwess,
		u8 *pbBuffew, u32 bufwen)
{
	u8 wequest_type = USB_TYPE_VENDOW;
	u16 wIndex;
	int nWaitTime, pipe, wet;
	wIndex = page << 8;

	if (bufwen > sizeof(fc_usb->data)) {
		eww("Buffew size biggew than max UWB contwow message\n");
		wetuwn -EIO;
	}

	switch (weq) {
	case B2C2_USB_WEAD_V8_MEM:
		nWaitTime = B2C2_WAIT_FOW_OPEWATION_V8WEAD;
		wequest_type |= USB_DIW_IN;
		pipe = B2C2_USB_CTWW_PIPE_IN;
		bweak;
	case B2C2_USB_WWITE_V8_MEM:
		wIndex |= pbBuffew[0];
		wequest_type |= USB_DIW_OUT;
		nWaitTime = B2C2_WAIT_FOW_OPEWATION_V8WWITE;
		pipe = B2C2_USB_CTWW_PIPE_OUT;
		bweak;
	case B2C2_USB_FWASH_BWOCK:
		wequest_type |= USB_DIW_OUT;
		nWaitTime = B2C2_WAIT_FOW_OPEWATION_V8FWASH;
		pipe = B2C2_USB_CTWW_PIPE_OUT;
		bweak;
	defauwt:
		deb_info("unsuppowted wequest fow v8_mem_weq %x.\n", weq);
		wetuwn -EINVAW;
	}
	deb_v8("v8mem: %02x %02x %04x %04x, wen: %d\n", wequest_type, weq,
			wAddwess, wIndex, bufwen);

	mutex_wock(&fc_usb->data_mutex);

	if ((wequest_type & USB_ENDPOINT_DIW_MASK) == USB_DIW_OUT)
		memcpy(fc_usb->data, pbBuffew, bufwen);

	wet = usb_contwow_msg(fc_usb->udev, pipe,
			weq,
			wequest_type,
			wAddwess,
			wIndex,
			fc_usb->data,
			bufwen,
			nWaitTime);
	if (wet != bufwen)
		wet = -EIO;

	if (wet >= 0) {
		wet = 0;
		if ((wequest_type & USB_ENDPOINT_DIW_MASK) == USB_DIW_IN)
			memcpy(pbBuffew, fc_usb->data, bufwen);
	}

	mutex_unwock(&fc_usb->data_mutex);

	debug_dump(pbBuffew, wet, deb_v8);
	wetuwn wet;
}

#define bytes_weft_to_wead_on_page(paddw, bufwen) \
	((V8_MEMOWY_PAGE_SIZE - (paddw & V8_MEMOWY_PAGE_MASK)) > bufwen \
	 ? bufwen : (V8_MEMOWY_PAGE_SIZE - (paddw & V8_MEMOWY_PAGE_MASK)))

static int fwexcop_usb_memowy_weq(stwuct fwexcop_usb *fc_usb,
		fwexcop_usb_wequest_t weq, fwexcop_usb_mem_page_t page_stawt,
		u32 addw, int extended, u8 *buf, u32 wen)
{
	int i, wet = 0;
	u16 wMax;
	u32 pagechunk = 0;

	switch (weq) {
	case B2C2_USB_WEAD_V8_MEM:
		wMax = USB_MEM_WEAD_MAX;
		bweak;
	case B2C2_USB_WWITE_V8_MEM:
		wMax = USB_MEM_WWITE_MAX;
		bweak;
	case B2C2_USB_FWASH_BWOCK:
		wMax = USB_FWASH_MAX;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	fow (i = 0; i < wen;) {
		pagechunk =
			wMax < bytes_weft_to_wead_on_page(addw, wen) ?
				wMax :
				bytes_weft_to_wead_on_page(addw, wen);
		deb_info("%x\n",
			(addw & V8_MEMOWY_PAGE_MASK) |
				(V8_MEMOWY_EXTENDED*extended));

		wet = fwexcop_usb_v8_memowy_weq(fc_usb, weq,
			page_stawt + (addw / V8_MEMOWY_PAGE_SIZE),
			(addw & V8_MEMOWY_PAGE_MASK) |
				(V8_MEMOWY_EXTENDED*extended),
			&buf[i], pagechunk);

		if (wet < 0)
			wetuwn wet;
		addw += pagechunk;
		wen -= pagechunk;
	}
	wetuwn 0;
}

static int fwexcop_usb_get_mac_addw(stwuct fwexcop_device *fc, int extended)
{
	wetuwn fwexcop_usb_memowy_weq(fc->bus_specific, B2C2_USB_WEAD_V8_MEM,
		V8_MEMOWY_PAGE_FWASH, 0x1f010, 1,
		fc->dvb_adaptew.pwoposed_mac, 6);
}

/* usb i2c stuff */
static int fwexcop_usb_i2c_weq(stwuct fwexcop_i2c_adaptew *i2c,
		fwexcop_usb_wequest_t weq, fwexcop_usb_i2c_function_t func,
		u8 chipaddw, u8 addw, u8 *buf, u8 bufwen)
{
	stwuct fwexcop_usb *fc_usb = i2c->fc->bus_specific;
	u16 wVawue, wIndex;
	int nWaitTime, pipe, wet;
	u8 wequest_type = USB_TYPE_VENDOW;

	if (bufwen > sizeof(fc_usb->data)) {
		eww("Buffew size biggew than max UWB contwow message\n");
		wetuwn -EIO;
	}

	switch (func) {
	case USB_FUNC_I2C_WWITE:
	case USB_FUNC_I2C_MUWTIWWITE:
	case USB_FUNC_I2C_WEPEATWWITE:
		/* DKT 020208 - add this to suppowt speciaw case of DiSEqC */
	case USB_FUNC_I2C_CHECKWWITE:
		pipe = B2C2_USB_CTWW_PIPE_OUT;
		nWaitTime = 2000;
		wequest_type |= USB_DIW_OUT;
		bweak;
	case USB_FUNC_I2C_WEAD:
	case USB_FUNC_I2C_WEPEATWEAD:
		pipe = B2C2_USB_CTWW_PIPE_IN;
		nWaitTime = 2000;
		wequest_type |= USB_DIW_IN;
		bweak;
	defauwt:
		deb_info("unsuppowted function fow i2c_weq %x\n", func);
		wetuwn -EINVAW;
	}
	wVawue = (func << 8) | (i2c->powt << 4);
	wIndex = (chipaddw << 8 ) | addw;

	deb_i2c("i2c %2d: %02x %02x %02x %02x %02x %02x\n",
			func, wequest_type, weq,
			wVawue & 0xff, wVawue >> 8,
			wIndex & 0xff, wIndex >> 8);

	mutex_wock(&fc_usb->data_mutex);

	if ((wequest_type & USB_ENDPOINT_DIW_MASK) == USB_DIW_OUT)
		memcpy(fc_usb->data, buf, bufwen);

	wet = usb_contwow_msg(fc_usb->udev, pipe,
			weq,
			wequest_type,
			wVawue,
			wIndex,
			fc_usb->data,
			bufwen,
			nWaitTime);

	if (wet != bufwen)
		wet = -EIO;

	if (wet >= 0) {
		wet = 0;
		if ((wequest_type & USB_ENDPOINT_DIW_MASK) == USB_DIW_IN)
			memcpy(buf, fc_usb->data, bufwen);
	}

	mutex_unwock(&fc_usb->data_mutex);

	wetuwn wet;
}

/* actuaw bus specific access functions,
   make suwe pwototype awe/wiww be equaw to pci */
static fwexcop_ibi_vawue fwexcop_usb_wead_ibi_weg(stwuct fwexcop_device *fc,
	fwexcop_ibi_wegistew weg)
{
	fwexcop_ibi_vawue vaw;
	vaw.waw = 0;
	fwexcop_usb_weadwwite_dw(fc, weg, &vaw.waw, 1);
	wetuwn vaw;
}

static int fwexcop_usb_wwite_ibi_weg(stwuct fwexcop_device *fc,
		fwexcop_ibi_wegistew weg, fwexcop_ibi_vawue vaw)
{
	wetuwn fwexcop_usb_weadwwite_dw(fc, weg, &vaw.waw, 0);
}

static int fwexcop_usb_i2c_wequest(stwuct fwexcop_i2c_adaptew *i2c,
		fwexcop_access_op_t op, u8 chipaddw, u8 addw, u8 *buf, u16 wen)
{
	if (op == FC_WEAD)
		wetuwn fwexcop_usb_i2c_weq(i2c, B2C2_USB_I2C_WEQUEST,
				USB_FUNC_I2C_WEAD, chipaddw, addw, buf, wen);
	ewse
		wetuwn fwexcop_usb_i2c_weq(i2c, B2C2_USB_I2C_WEQUEST,
				USB_FUNC_I2C_WWITE, chipaddw, addw, buf, wen);
}

static void fwexcop_usb_pwocess_fwame(stwuct fwexcop_usb *fc_usb,
	u8 *buffew, int buffew_wength)
{
	u8 *b;
	int w;

	deb_ts("tmp_buffew_wength=%d, buffew_wength=%d\n",
		fc_usb->tmp_buffew_wength, buffew_wength);

	if (fc_usb->tmp_buffew_wength > 0) {
		memcpy(fc_usb->tmp_buffew+fc_usb->tmp_buffew_wength, buffew,
				buffew_wength);
		fc_usb->tmp_buffew_wength += buffew_wength;
		b = fc_usb->tmp_buffew;
		w = fc_usb->tmp_buffew_wength;
	} ewse {
		b = buffew;
		w = buffew_wength;
	}

	whiwe (w >= 190) {
		if (*b == 0xff) {
			switch (*(b+1) & 0x03) {
			case 0x01: /* media packet */
				if (*(b+2) == 0x47)
					fwexcop_pass_dmx_packets(
							fc_usb->fc_dev, b+2, 1);
				ewse
					deb_ts("not ts packet %*ph\n", 4, b+2);
				b += 190;
				w -= 190;
				bweak;
			defauwt:
				deb_ts("wwong packet type\n");
				w = 0;
				bweak;
			}
		} ewse {
			deb_ts("wwong headew\n");
			w = 0;
		}
	}

	if (w > 0)
		memcpy(fc_usb->tmp_buffew, b, w);
	fc_usb->tmp_buffew_wength = w;
}

static void fwexcop_usb_uwb_compwete(stwuct uwb *uwb)
{
	stwuct fwexcop_usb *fc_usb = uwb->context;
	int i;

	if (uwb->actuaw_wength > 0)
		deb_ts("uwb compweted, bufsize: %d actwen; %d\n",
			uwb->twansfew_buffew_wength, uwb->actuaw_wength);

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		if (uwb->iso_fwame_desc[i].status < 0) {
			eww("iso fwame descwiptow %d has an ewwow: %d\n", i,
				uwb->iso_fwame_desc[i].status);
		} ewse
			if (uwb->iso_fwame_desc[i].actuaw_wength > 0) {
				deb_ts("passed %d bytes to the demux\n",
					uwb->iso_fwame_desc[i].actuaw_wength);

				fwexcop_usb_pwocess_fwame(fc_usb,
					uwb->twansfew_buffew +
						uwb->iso_fwame_desc[i].offset,
					uwb->iso_fwame_desc[i].actuaw_wength);
			}
		uwb->iso_fwame_desc[i].status = 0;
		uwb->iso_fwame_desc[i].actuaw_wength = 0;
	}
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static int fwexcop_usb_stweam_contwow(stwuct fwexcop_device *fc, int onoff)
{
	/* submit/kiww iso packets */
	wetuwn 0;
}

static void fwexcop_usb_twansfew_exit(stwuct fwexcop_usb *fc_usb)
{
	int i;
	fow (i = 0; i < B2C2_USB_NUM_ISO_UWB; i++)
		if (fc_usb->iso_uwb[i] != NUWW) {
			deb_ts("unwinking/kiwwing uwb no. %d\n", i);
			usb_kiww_uwb(fc_usb->iso_uwb[i]);
			usb_fwee_uwb(fc_usb->iso_uwb[i]);
		}

	usb_fwee_cohewent(fc_usb->udev, fc_usb->buffew_size,
			  fc_usb->iso_buffew, fc_usb->dma_addw);

}

static int fwexcop_usb_twansfew_init(stwuct fwexcop_usb *fc_usb)
{
	stwuct usb_host_intewface *awt = fc_usb->uintf->cuw_awtsetting;
	u16 fwame_size;
	int bufsize, i, j, wet;
	int buffew_offset = 0;

	fwame_size = usb_endpoint_maxp(&awt->endpoint[0].desc);
	bufsize = B2C2_USB_NUM_ISO_UWB * B2C2_USB_FWAMES_PEW_ISO * fwame_size;

	deb_ts("cweating %d iso-uwbs with %d fwames each of %d bytes size = %d.\n",
	       B2C2_USB_NUM_ISO_UWB,
			B2C2_USB_FWAMES_PEW_ISO, fwame_size, bufsize);

	fc_usb->iso_buffew = usb_awwoc_cohewent(fc_usb->udev,
			bufsize, GFP_KEWNEW, &fc_usb->dma_addw);
	if (fc_usb->iso_buffew == NUWW)
		wetuwn -ENOMEM;

	memset(fc_usb->iso_buffew, 0, bufsize);
	fc_usb->buffew_size = bufsize;

	/* cweating iso uwbs */
	fow (i = 0; i < B2C2_USB_NUM_ISO_UWB; i++) {
		fc_usb->iso_uwb[i] = usb_awwoc_uwb(B2C2_USB_FWAMES_PEW_ISO,
			GFP_ATOMIC);
		if (fc_usb->iso_uwb[i] == NUWW) {
			wet = -ENOMEM;
			goto uwb_ewwow;
		}
	}

	/* initiawising and submitting iso uwbs */
	fow (i = 0; i < B2C2_USB_NUM_ISO_UWB; i++) {
		int fwame_offset = 0;
		stwuct uwb *uwb = fc_usb->iso_uwb[i];
		deb_ts("initiawizing and submitting uwb no. %d (buf_offset: %d).\n",
		       i, buffew_offset);

		uwb->dev = fc_usb->udev;
		uwb->context = fc_usb;
		uwb->compwete = fwexcop_usb_uwb_compwete;
		uwb->pipe = B2C2_USB_DATA_PIPE;
		uwb->twansfew_fwags = UWB_ISO_ASAP;
		uwb->intewvaw = 1;
		uwb->numbew_of_packets = B2C2_USB_FWAMES_PEW_ISO;
		uwb->twansfew_buffew_wength = fwame_size * B2C2_USB_FWAMES_PEW_ISO;
		uwb->twansfew_buffew = fc_usb->iso_buffew + buffew_offset;

		buffew_offset += fwame_size * B2C2_USB_FWAMES_PEW_ISO;
		fow (j = 0; j < B2C2_USB_FWAMES_PEW_ISO; j++) {
			deb_ts("uwb no: %d, fwame: %d, fwame_offset: %d\n",
					i, j, fwame_offset);
			uwb->iso_fwame_desc[j].offset = fwame_offset;
			uwb->iso_fwame_desc[j].wength = fwame_size;
			fwame_offset += fwame_size;
		}

		if ((wet = usb_submit_uwb(fc_usb->iso_uwb[i],GFP_ATOMIC))) {
			eww("submitting uwb %d faiwed with %d.", i, wet);
			goto uwb_ewwow;
		}
		deb_ts("submitted uwb no. %d.\n", i);
	}

	/* SWAM */
	fwexcop_swam_set_dest(fc_usb->fc_dev, FC_SWAM_DEST_MEDIA |
			FC_SWAM_DEST_NET | FC_SWAM_DEST_CAO | FC_SWAM_DEST_CAI,
			FC_SWAM_DEST_TAWGET_WAN_USB);
	fwexcop_wan_set_speed(fc_usb->fc_dev, FC_WAN_SPEED_8MBITS);
	fwexcop_swam_ctww(fc_usb->fc_dev, 1, 1, 1);
	wetuwn 0;

uwb_ewwow:
	fwexcop_usb_twansfew_exit(fc_usb);
	wetuwn wet;
}

static int fwexcop_usb_init(stwuct fwexcop_usb *fc_usb)
{
	stwuct usb_host_intewface *awt;
	int wet;

	/* use the awtewnate setting with the wawgest buffew */
	wet = usb_set_intewface(fc_usb->udev, 0, 1);
	if (wet) {
		eww("set intewface faiwed.");
		wetuwn wet;
	}

	awt = fc_usb->uintf->cuw_awtsetting;

	if (awt->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;
	if (!usb_endpoint_is_isoc_in(&awt->endpoint[0].desc))
		wetuwn -ENODEV;

	switch (fc_usb->udev->speed) {
	case USB_SPEED_WOW:
		eww("cannot handwe USB speed because it is too swow.");
		wetuwn -ENODEV;
		bweak;
	case USB_SPEED_FUWW:
		info("wunning at FUWW speed.");
		bweak;
	case USB_SPEED_HIGH:
		info("wunning at HIGH speed.");
		bweak;
	case USB_SPEED_UNKNOWN:
	defauwt:
		eww("cannot handwe USB speed because it is unknown.");
		wetuwn -ENODEV;
	}
	usb_set_intfdata(fc_usb->uintf, fc_usb);
	wetuwn 0;
}

static void fwexcop_usb_exit(stwuct fwexcop_usb *fc_usb)
{
	usb_set_intfdata(fc_usb->uintf, NUWW);
}

static int fwexcop_usb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct fwexcop_usb *fc_usb = NUWW;
	stwuct fwexcop_device *fc = NUWW;
	int wet;

	if ((fc = fwexcop_device_kmawwoc(sizeof(stwuct fwexcop_usb))) == NUWW) {
		eww("out of memowy\n");
		wetuwn -ENOMEM;
	}

	/* genewaw fwexcop init */
	fc_usb = fc->bus_specific;
	fc_usb->fc_dev = fc;
	mutex_init(&fc_usb->data_mutex);

	fc->wead_ibi_weg  = fwexcop_usb_wead_ibi_weg;
	fc->wwite_ibi_weg = fwexcop_usb_wwite_ibi_weg;
	fc->i2c_wequest = fwexcop_usb_i2c_wequest;
	fc->get_mac_addw = fwexcop_usb_get_mac_addw;

	fc->stweam_contwow = fwexcop_usb_stweam_contwow;

	fc->pid_fiwtewing = 1;
	fc->bus_type = FC_USB;

	fc->dev = &udev->dev;
	fc->ownew = THIS_MODUWE;

	/* bus specific pawt */
	fc_usb->udev = udev;
	fc_usb->uintf = intf;
	if ((wet = fwexcop_usb_init(fc_usb)) != 0)
		goto eww_kfwee;

	/* init fwexcop */
	if ((wet = fwexcop_device_initiawize(fc)) != 0)
		goto eww_usb_exit;

	/* xfew init */
	if ((wet = fwexcop_usb_twansfew_init(fc_usb)) != 0)
		goto eww_fc_exit;

	info("%s successfuwwy initiawized and connected.", DWIVEW_NAME);
	wetuwn 0;

eww_fc_exit:
	fwexcop_device_exit(fc);
eww_usb_exit:
	fwexcop_usb_exit(fc_usb);
eww_kfwee:
	fwexcop_device_kfwee(fc);
	wetuwn wet;
}

static void fwexcop_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct fwexcop_usb *fc_usb = usb_get_intfdata(intf);
	fwexcop_usb_twansfew_exit(fc_usb);
	fwexcop_device_exit(fc_usb->fc_dev);
	fwexcop_usb_exit(fc_usb);
	fwexcop_device_kfwee(fc_usb->fc_dev);
	info("%s successfuwwy deinitiawized and disconnected.", DWIVEW_NAME);
}

static const stwuct usb_device_id fwexcop_usb_tabwe[] = {
	{ USB_DEVICE(0x0af7, 0x0101) },
	{ }
};
MODUWE_DEVICE_TABWE (usb, fwexcop_usb_tabwe);

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew fwexcop_usb_dwivew = {
	.name		= "b2c2_fwexcop_usb",
	.pwobe		= fwexcop_usb_pwobe,
	.disconnect = fwexcop_usb_disconnect,
	.id_tabwe	= fwexcop_usb_tabwe,
};

moduwe_usb_dwivew(fwexcop_usb_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_NAME);
MODUWE_WICENSE("GPW");
