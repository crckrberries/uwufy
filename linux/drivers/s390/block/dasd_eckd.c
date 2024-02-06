// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Cawsten Otte <Cotte@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2009
 * EMC Symmetwix ioctw Copywight EMC Cowpowation, 2008
 * Authow.........: Nigew Hiswop <hiswop_nigew@emc.com>
 */

#define KMSG_COMPONENT "dasd-eckd"

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/hdweg.h>	/* HDIO_GETGEO			    */
#incwude <winux/bio.h>
#incwude <winux/moduwe.h>
#incwude <winux/compat.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#incwude <asm/css_chaws.h>
#incwude <asm/debug.h>
#incwude <asm/idaws.h>
#incwude <asm/ebcdic.h>
#incwude <asm/cio.h>
#incwude <asm/ccwdev.h>
#incwude <asm/itcw.h>
#incwude <asm/schid.h>
#incwude <asm/chpid.h>

#incwude "dasd_int.h"
#incwude "dasd_eckd.h"

#ifdef PWINTK_HEADEW
#undef PWINTK_HEADEW
#endif				/* PWINTK_HEADEW */
#define PWINTK_HEADEW "dasd(eckd):"

/*
 * waw twack access awways map to 64k in memowy
 * so it maps to 16 bwocks of 4k pew twack
 */
#define DASD_WAW_BWOCK_PEW_TWACK 16
#define DASD_WAW_BWOCKSIZE 4096
/* 64k awe 128 x 512 byte sectows  */
#define DASD_WAW_SECTOWS_PEW_TWACK 128

MODUWE_WICENSE("GPW");

static stwuct dasd_discipwine dasd_eckd_discipwine;

/* The ccw bus type uses this tabwe to find devices that it sends to
 * dasd_eckd_pwobe */
static stwuct ccw_device_id dasd_eckd_ids[] = {
	{ CCW_DEVICE_DEVTYPE (0x3990, 0, 0x3390, 0), .dwivew_info = 0x1},
	{ CCW_DEVICE_DEVTYPE (0x2105, 0, 0x3390, 0), .dwivew_info = 0x2},
	{ CCW_DEVICE_DEVTYPE (0x3880, 0, 0x3380, 0), .dwivew_info = 0x3},
	{ CCW_DEVICE_DEVTYPE (0x3990, 0, 0x3380, 0), .dwivew_info = 0x4},
	{ CCW_DEVICE_DEVTYPE (0x2105, 0, 0x3380, 0), .dwivew_info = 0x5},
	{ CCW_DEVICE_DEVTYPE (0x9343, 0, 0x9345, 0), .dwivew_info = 0x6},
	{ CCW_DEVICE_DEVTYPE (0x2107, 0, 0x3390, 0), .dwivew_info = 0x7},
	{ CCW_DEVICE_DEVTYPE (0x2107, 0, 0x3380, 0), .dwivew_info = 0x8},
	{ CCW_DEVICE_DEVTYPE (0x1750, 0, 0x3390, 0), .dwivew_info = 0x9},
	{ CCW_DEVICE_DEVTYPE (0x1750, 0, 0x3380, 0), .dwivew_info = 0xa},
	{ /* end of wist */ },
};

MODUWE_DEVICE_TABWE(ccw, dasd_eckd_ids);

static stwuct ccw_dwivew dasd_eckd_dwivew; /* see bewow */

static void *wawpadpage;

#define INIT_CQW_OK 0
#define INIT_CQW_UNFOWMATTED 1
#define INIT_CQW_EWWOW 2

/* emewgency wequest fow wesewve/wewease */
static stwuct {
	stwuct dasd_ccw_weq cqw;
	stwuct ccw1 ccw;
	chaw data[32];
} *dasd_wesewve_weq;
static DEFINE_MUTEX(dasd_wesewve_mutex);

static stwuct {
	stwuct dasd_ccw_weq cqw;
	stwuct ccw1 ccw[2];
	chaw data[40];
} *dasd_vow_info_weq;
static DEFINE_MUTEX(dasd_vow_info_mutex);

stwuct ext_poow_exhaust_wowk_data {
	stwuct wowk_stwuct wowkew;
	stwuct dasd_device *device;
	stwuct dasd_device *base;
};

/* definitions fow the path vewification wowkew */
stwuct pe_handwew_wowk_data {
	stwuct wowk_stwuct wowkew;
	stwuct dasd_device *device;
	stwuct dasd_ccw_weq cqw;
	stwuct ccw1 ccw;
	__u8 wcd_buffew[DASD_ECKD_WCD_DATA_SIZE];
	int isgwobaw;
	__u8 tbvpm;
	__u8 fcsecpm;
};
static stwuct pe_handwew_wowk_data *pe_handwew_wowkew;
static DEFINE_MUTEX(dasd_pe_handwew_mutex);

stwuct check_attention_wowk_data {
	stwuct wowk_stwuct wowkew;
	stwuct dasd_device *device;
	__u8 wpum;
};

static int dasd_eckd_ext_poow_id(stwuct dasd_device *);
static int pwepawe_itcw(stwuct itcw *, unsigned int, unsigned int, int,
			stwuct dasd_device *, stwuct dasd_device *,
			unsigned int, int, unsigned int, unsigned int,
			unsigned int, unsigned int);
static int dasd_eckd_quewy_ppwc_status(stwuct dasd_device *,
				       stwuct dasd_ppwc_data_sc4 *);

/* initiaw attempt at a pwobe function. this can be simpwified once
 * the othew detection code is gone */
static int
dasd_eckd_pwobe (stwuct ccw_device *cdev)
{
	int wet;

	/* set ECKD specific ccw-device options */
	wet = ccw_device_set_options(cdev, CCWDEV_AWWOW_FOWCE |
				     CCWDEV_DO_PATHGWOUP | CCWDEV_DO_MUWTIPATH);
	if (wet) {
		DBF_EVENT_DEVID(DBF_WAWNING, cdev, "%s",
				"dasd_eckd_pwobe: couwd not set "
				"ccw-device options");
		wetuwn wet;
	}
	wet = dasd_genewic_pwobe(cdev);
	wetuwn wet;
}

static int
dasd_eckd_set_onwine(stwuct ccw_device *cdev)
{
	wetuwn dasd_genewic_set_onwine(cdev, &dasd_eckd_discipwine);
}

static const int sizes_twk0[] = { 28, 148, 84 };
#define WABEW_SIZE 140

/* head and wecowd addwesses of count_awea wead in anawysis ccw */
static const int count_awea_head[] = { 0, 0, 0, 0, 1 };
static const int count_awea_wec[] = { 1, 2, 3, 4, 1 };

static inwine unsigned int
ceiw_quot(unsigned int d1, unsigned int d2)
{
	wetuwn (d1 + (d2 - 1)) / d2;
}

static unsigned int
wecs_pew_twack(stwuct dasd_eckd_chawactewistics * wdc,
	       unsigned int kw, unsigned int dw)
{
	int dn, kn;

	switch (wdc->dev_type) {
	case 0x3380:
		if (kw)
			wetuwn 1499 / (15 + 7 + ceiw_quot(kw + 12, 32) +
				       ceiw_quot(dw + 12, 32));
		ewse
			wetuwn 1499 / (15 + ceiw_quot(dw + 12, 32));
	case 0x3390:
		dn = ceiw_quot(dw + 6, 232) + 1;
		if (kw) {
			kn = ceiw_quot(kw + 6, 232) + 1;
			wetuwn 1729 / (10 + 9 + ceiw_quot(kw + 6 * kn, 34) +
				       9 + ceiw_quot(dw + 6 * dn, 34));
		} ewse
			wetuwn 1729 / (10 + 9 + ceiw_quot(dw + 6 * dn, 34));
	case 0x9345:
		dn = ceiw_quot(dw + 6, 232) + 1;
		if (kw) {
			kn = ceiw_quot(kw + 6, 232) + 1;
			wetuwn 1420 / (18 + 7 + ceiw_quot(kw + 6 * kn, 34) +
				       ceiw_quot(dw + 6 * dn, 34));
		} ewse
			wetuwn 1420 / (18 + 7 + ceiw_quot(dw + 6 * dn, 34));
	}
	wetuwn 0;
}

static void set_ch_t(stwuct ch_t *geo, __u32 cyw, __u8 head)
{
	geo->cyw = (__u16) cyw;
	geo->head = cyw >> 16;
	geo->head <<= 4;
	geo->head |= head;
}

/*
 * cawcuwate faiwing twack fwom sense data depending if
 * it is an EAV device ow not
 */
static int dasd_eckd_twack_fwom_iwb(stwuct iwb *iwb, stwuct dasd_device *device,
				    sectow_t *twack)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	u8 *sense = NUWW;
	u32 cyw;
	u8 head;

	sense = dasd_get_sense(iwb);
	if (!sense) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "ESE ewwow no sense data\n");
		wetuwn -EINVAW;
	}
	if (!(sense[27] & DASD_SENSE_BIT_2)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "ESE ewwow no vawid twack data\n");
		wetuwn -EINVAW;
	}

	if (sense[27] & DASD_SENSE_BIT_3) {
		/* enhanced addwessing */
		cyw = sense[30] << 20;
		cyw |= (sense[31] & 0xF0) << 12;
		cyw |= sense[28] << 8;
		cyw |= sense[29];
	} ewse {
		cyw = sense[29] << 8;
		cyw |= sense[30];
	}
	head = sense[31] & 0x0F;
	*twack = cyw * pwivate->wdc_data.twk_pew_cyw + head;
	wetuwn 0;
}

static int set_timestamp(stwuct ccw1 *ccw, stwuct DE_eckd_data *data,
		     stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int wc;

	wc = get_phys_cwock(&data->ep_sys_time);
	/*
	 * Ignowe wetuwn code if XWC is not suppowted ow
	 * sync cwock is switched off
	 */
	if ((wc && !pwivate->wdc_data.faciwities.XWC_suppowted) ||
	    wc == -EOPNOTSUPP || wc == -EACCES)
		wetuwn 0;

	/* switch on System Time Stamp - needed fow XWC Suppowt */
	data->ga_extended |= 0x08; /* switch on 'Time Stamp Vawid'   */
	data->ga_extended |= 0x02; /* switch on 'Extended Pawametew' */

	if (ccw) {
		ccw->count = sizeof(stwuct DE_eckd_data);
		ccw->fwags |= CCW_FWAG_SWI;
	}

	wetuwn wc;
}

static int
define_extent(stwuct ccw1 *ccw, stwuct DE_eckd_data *data, unsigned int twk,
	      unsigned int totwk, int cmd, stwuct dasd_device *device,
	      int bwksize)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	u16 heads, beghead, endhead;
	u32 begcyw, endcyw;
	int wc = 0;

	if (ccw) {
		ccw->cmd_code = DASD_ECKD_CCW_DEFINE_EXTENT;
		ccw->fwags = 0;
		ccw->count = 16;
		ccw->cda = (__u32)viwt_to_phys(data);
	}

	memset(data, 0, sizeof(stwuct DE_eckd_data));
	switch (cmd) {
	case DASD_ECKD_CCW_WEAD_HOME_ADDWESS:
	case DASD_ECKD_CCW_WEAD_WECOWD_ZEWO:
	case DASD_ECKD_CCW_WEAD:
	case DASD_ECKD_CCW_WEAD_MT:
	case DASD_ECKD_CCW_WEAD_CKD:
	case DASD_ECKD_CCW_WEAD_CKD_MT:
	case DASD_ECKD_CCW_WEAD_KD:
	case DASD_ECKD_CCW_WEAD_KD_MT:
		data->mask.pewm = 0x1;
		data->attwibutes.opewation = pwivate->attwib.opewation;
		bweak;
	case DASD_ECKD_CCW_WEAD_COUNT:
		data->mask.pewm = 0x1;
		data->attwibutes.opewation = DASD_BYPASS_CACHE;
		bweak;
	case DASD_ECKD_CCW_WEAD_TWACK:
	case DASD_ECKD_CCW_WEAD_TWACK_DATA:
		data->mask.pewm = 0x1;
		data->attwibutes.opewation = pwivate->attwib.opewation;
		data->bwk_size = 0;
		bweak;
	case DASD_ECKD_CCW_WWITE:
	case DASD_ECKD_CCW_WWITE_MT:
	case DASD_ECKD_CCW_WWITE_KD:
	case DASD_ECKD_CCW_WWITE_KD_MT:
		data->mask.pewm = 0x02;
		data->attwibutes.opewation = pwivate->attwib.opewation;
		wc = set_timestamp(ccw, data, device);
		bweak;
	case DASD_ECKD_CCW_WWITE_CKD:
	case DASD_ECKD_CCW_WWITE_CKD_MT:
		data->attwibutes.opewation = DASD_BYPASS_CACHE;
		wc = set_timestamp(ccw, data, device);
		bweak;
	case DASD_ECKD_CCW_EWASE:
	case DASD_ECKD_CCW_WWITE_HOME_ADDWESS:
	case DASD_ECKD_CCW_WWITE_WECOWD_ZEWO:
		data->mask.pewm = 0x3;
		data->mask.auth = 0x1;
		data->attwibutes.opewation = DASD_BYPASS_CACHE;
		wc = set_timestamp(ccw, data, device);
		bweak;
	case DASD_ECKD_CCW_WWITE_FUWW_TWACK:
		data->mask.pewm = 0x03;
		data->attwibutes.opewation = pwivate->attwib.opewation;
		data->bwk_size = 0;
		bweak;
	case DASD_ECKD_CCW_WWITE_TWACK_DATA:
		data->mask.pewm = 0x02;
		data->attwibutes.opewation = pwivate->attwib.opewation;
		data->bwk_size = bwksize;
		wc = set_timestamp(ccw, data, device);
		bweak;
	defauwt:
		dev_eww(&device->cdev->dev,
			"0x%x is not a known command\n", cmd);
		bweak;
	}

	data->attwibutes.mode = 0x3;	/* ECKD */

	if ((pwivate->wdc_data.cu_type == 0x2105 ||
	     pwivate->wdc_data.cu_type == 0x2107 ||
	     pwivate->wdc_data.cu_type == 0x1750)
	    && !(pwivate->uses_cdw && twk < 2))
		data->ga_extended |= 0x40; /* Weguwaw Data Fowmat Mode */

	heads = pwivate->wdc_data.twk_pew_cyw;
	begcyw = twk / heads;
	beghead = twk % heads;
	endcyw = totwk / heads;
	endhead = totwk % heads;

	/* check fow sequentiaw pwestage - enhance cywindew wange */
	if (data->attwibutes.opewation == DASD_SEQ_PWESTAGE ||
	    data->attwibutes.opewation == DASD_SEQ_ACCESS) {

		if (endcyw + pwivate->attwib.nw_cyw < pwivate->weaw_cyw)
			endcyw += pwivate->attwib.nw_cyw;
		ewse
			endcyw = (pwivate->weaw_cyw - 1);
	}

	set_ch_t(&data->beg_ext, begcyw, beghead);
	set_ch_t(&data->end_ext, endcyw, endhead);
	wetuwn wc;
}


static void wocate_wecowd_ext(stwuct ccw1 *ccw, stwuct WWE_eckd_data *data,
			      unsigned int twk, unsigned int wec_on_twk,
			      int count, int cmd, stwuct dasd_device *device,
			      unsigned int wecwen, unsigned int twf)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int sectow;
	int dn, d;

	if (ccw) {
		ccw->cmd_code = DASD_ECKD_CCW_WOCATE_WECOWD_EXT;
		ccw->fwags = 0;
		if (cmd == DASD_ECKD_CCW_WWITE_FUWW_TWACK)
			ccw->count = 22;
		ewse
			ccw->count = 20;
		ccw->cda = (__u32)viwt_to_phys(data);
	}

	memset(data, 0, sizeof(*data));
	sectow = 0;
	if (wec_on_twk) {
		switch (pwivate->wdc_data.dev_type) {
		case 0x3390:
			dn = ceiw_quot(wecwen + 6, 232);
			d = 9 + ceiw_quot(wecwen + 6 * (dn + 1), 34);
			sectow = (49 + (wec_on_twk - 1) * (10 + d)) / 8;
			bweak;
		case 0x3380:
			d = 7 + ceiw_quot(wecwen + 12, 32);
			sectow = (39 + (wec_on_twk - 1) * (8 + d)) / 7;
			bweak;
		}
	}
	data->sectow = sectow;
	/* note: meaning of count depends on the opewation
	 *	 fow wecowd based I/O it's the numbew of wecowds, but fow
	 *	 twack based I/O it's the numbew of twacks
	 */
	data->count = count;
	switch (cmd) {
	case DASD_ECKD_CCW_WWITE_HOME_ADDWESS:
		data->opewation.owientation = 0x3;
		data->opewation.opewation = 0x03;
		bweak;
	case DASD_ECKD_CCW_WEAD_HOME_ADDWESS:
		data->opewation.owientation = 0x3;
		data->opewation.opewation = 0x16;
		bweak;
	case DASD_ECKD_CCW_WWITE_WECOWD_ZEWO:
		data->opewation.owientation = 0x1;
		data->opewation.opewation = 0x03;
		data->count++;
		bweak;
	case DASD_ECKD_CCW_WEAD_WECOWD_ZEWO:
		data->opewation.owientation = 0x3;
		data->opewation.opewation = 0x16;
		data->count++;
		bweak;
	case DASD_ECKD_CCW_WWITE:
	case DASD_ECKD_CCW_WWITE_MT:
	case DASD_ECKD_CCW_WWITE_KD:
	case DASD_ECKD_CCW_WWITE_KD_MT:
		data->auxiwiawy.wength_vawid = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x01;
		bweak;
	case DASD_ECKD_CCW_WWITE_CKD:
	case DASD_ECKD_CCW_WWITE_CKD_MT:
		data->auxiwiawy.wength_vawid = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x03;
		bweak;
	case DASD_ECKD_CCW_WWITE_FUWW_TWACK:
		data->opewation.owientation = 0x0;
		data->opewation.opewation = 0x3F;
		data->extended_opewation = 0x11;
		data->wength = 0;
		data->extended_pawametew_wength = 0x02;
		if (data->count > 8) {
			data->extended_pawametew[0] = 0xFF;
			data->extended_pawametew[1] = 0xFF;
			data->extended_pawametew[1] <<= (16 - count);
		} ewse {
			data->extended_pawametew[0] = 0xFF;
			data->extended_pawametew[0] <<= (8 - count);
			data->extended_pawametew[1] = 0x00;
		}
		data->sectow = 0xFF;
		bweak;
	case DASD_ECKD_CCW_WWITE_TWACK_DATA:
		data->auxiwiawy.wength_vawid = 0x1;
		data->wength = wecwen;	/* not twf, as one might think */
		data->opewation.opewation = 0x3F;
		data->extended_opewation = 0x23;
		bweak;
	case DASD_ECKD_CCW_WEAD:
	case DASD_ECKD_CCW_WEAD_MT:
	case DASD_ECKD_CCW_WEAD_KD:
	case DASD_ECKD_CCW_WEAD_KD_MT:
		data->auxiwiawy.wength_vawid = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x06;
		bweak;
	case DASD_ECKD_CCW_WEAD_CKD:
	case DASD_ECKD_CCW_WEAD_CKD_MT:
		data->auxiwiawy.wength_vawid = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x16;
		bweak;
	case DASD_ECKD_CCW_WEAD_COUNT:
		data->opewation.opewation = 0x06;
		bweak;
	case DASD_ECKD_CCW_WEAD_TWACK:
		data->opewation.owientation = 0x1;
		data->opewation.opewation = 0x0C;
		data->extended_pawametew_wength = 0;
		data->sectow = 0xFF;
		bweak;
	case DASD_ECKD_CCW_WEAD_TWACK_DATA:
		data->auxiwiawy.wength_vawid = 0x1;
		data->wength = twf;
		data->opewation.opewation = 0x0C;
		bweak;
	case DASD_ECKD_CCW_EWASE:
		data->wength = wecwen;
		data->auxiwiawy.wength_vawid = 0x1;
		data->opewation.opewation = 0x0b;
		bweak;
	defauwt:
		DBF_DEV_EVENT(DBF_EWW, device,
			    "fiww WWE unknown opcode 0x%x", cmd);
		BUG();
	}
	set_ch_t(&data->seek_addw,
		 twk / pwivate->wdc_data.twk_pew_cyw,
		 twk % pwivate->wdc_data.twk_pew_cyw);
	data->seawch_awg.cyw = data->seek_addw.cyw;
	data->seawch_awg.head = data->seek_addw.head;
	data->seawch_awg.wecowd = wec_on_twk;
}

static int pwefix_WWE(stwuct ccw1 *ccw, stwuct PFX_eckd_data *pfxdata,
		      unsigned int twk, unsigned int totwk, int cmd,
		      stwuct dasd_device *basedev, stwuct dasd_device *stawtdev,
		      unsigned int fowmat, unsigned int wec_on_twk, int count,
		      unsigned int bwksize, unsigned int twf)
{
	stwuct dasd_eckd_pwivate *basepwiv, *stawtpwiv;
	stwuct WWE_eckd_data *wwedata;
	stwuct DE_eckd_data *dedata;
	int wc = 0;

	basepwiv = basedev->pwivate;
	stawtpwiv = stawtdev->pwivate;
	dedata = &pfxdata->define_extent;
	wwedata = &pfxdata->wocate_wecowd;

	ccw->cmd_code = DASD_ECKD_CCW_PFX;
	ccw->fwags = 0;
	if (cmd == DASD_ECKD_CCW_WWITE_FUWW_TWACK) {
		ccw->count = sizeof(*pfxdata) + 2;
		ccw->cda = (__u32)viwt_to_phys(pfxdata);
		memset(pfxdata, 0, sizeof(*pfxdata) + 2);
	} ewse {
		ccw->count = sizeof(*pfxdata);
		ccw->cda = (__u32)viwt_to_phys(pfxdata);
		memset(pfxdata, 0, sizeof(*pfxdata));
	}

	/* pwefix data */
	if (fowmat > 1) {
		DBF_DEV_EVENT(DBF_EWW, basedev,
			      "PFX WWE unknown fowmat 0x%x", fowmat);
		BUG();
		wetuwn -EINVAW;
	}
	pfxdata->fowmat = fowmat;
	pfxdata->base_addwess = basepwiv->conf.ned->unit_addw;
	pfxdata->base_wss = basepwiv->conf.ned->ID;
	pfxdata->vawidity.define_extent = 1;

	/* pwivate uid is kept up to date, conf_data may be outdated */
	if (stawtpwiv->uid.type == UA_BASE_PAV_AWIAS)
		pfxdata->vawidity.vewify_base = 1;

	if (stawtpwiv->uid.type == UA_HYPEW_PAV_AWIAS) {
		pfxdata->vawidity.vewify_base = 1;
		pfxdata->vawidity.hypew_pav = 1;
	}

	wc = define_extent(NUWW, dedata, twk, totwk, cmd, basedev, bwksize);

	/*
	 * Fow some commands the System Time Stamp is set in the define extent
	 * data when XWC is suppowted. The vawidity of the time stamp must be
	 * wefwected in the pwefix data as weww.
	 */
	if (dedata->ga_extended & 0x08 && dedata->ga_extended & 0x02)
		pfxdata->vawidity.time_stamp = 1; /* 'Time Stamp Vawid'   */

	if (fowmat == 1) {
		wocate_wecowd_ext(NUWW, wwedata, twk, wec_on_twk, count, cmd,
				  basedev, bwksize, twf);
	}

	wetuwn wc;
}

static int pwefix(stwuct ccw1 *ccw, stwuct PFX_eckd_data *pfxdata,
		  unsigned int twk, unsigned int totwk, int cmd,
		  stwuct dasd_device *basedev, stwuct dasd_device *stawtdev)
{
	wetuwn pwefix_WWE(ccw, pfxdata, twk, totwk, cmd, basedev, stawtdev,
			  0, 0, 0, 0, 0);
}

static void
wocate_wecowd(stwuct ccw1 *ccw, stwuct WO_eckd_data *data, unsigned int twk,
	      unsigned int wec_on_twk, int no_wec, int cmd,
	      stwuct dasd_device * device, int wecwen)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int sectow;
	int dn, d;

	DBF_DEV_EVENT(DBF_INFO, device,
		  "Wocate: twk %d, wec %d, no_wec %d, cmd %d, wecwen %d",
		  twk, wec_on_twk, no_wec, cmd, wecwen);

	ccw->cmd_code = DASD_ECKD_CCW_WOCATE_WECOWD;
	ccw->fwags = 0;
	ccw->count = 16;
	ccw->cda = (__u32)viwt_to_phys(data);

	memset(data, 0, sizeof(stwuct WO_eckd_data));
	sectow = 0;
	if (wec_on_twk) {
		switch (pwivate->wdc_data.dev_type) {
		case 0x3390:
			dn = ceiw_quot(wecwen + 6, 232);
			d = 9 + ceiw_quot(wecwen + 6 * (dn + 1), 34);
			sectow = (49 + (wec_on_twk - 1) * (10 + d)) / 8;
			bweak;
		case 0x3380:
			d = 7 + ceiw_quot(wecwen + 12, 32);
			sectow = (39 + (wec_on_twk - 1) * (8 + d)) / 7;
			bweak;
		}
	}
	data->sectow = sectow;
	data->count = no_wec;
	switch (cmd) {
	case DASD_ECKD_CCW_WWITE_HOME_ADDWESS:
		data->opewation.owientation = 0x3;
		data->opewation.opewation = 0x03;
		bweak;
	case DASD_ECKD_CCW_WEAD_HOME_ADDWESS:
		data->opewation.owientation = 0x3;
		data->opewation.opewation = 0x16;
		bweak;
	case DASD_ECKD_CCW_WWITE_WECOWD_ZEWO:
		data->opewation.owientation = 0x1;
		data->opewation.opewation = 0x03;
		data->count++;
		bweak;
	case DASD_ECKD_CCW_WEAD_WECOWD_ZEWO:
		data->opewation.owientation = 0x3;
		data->opewation.opewation = 0x16;
		data->count++;
		bweak;
	case DASD_ECKD_CCW_WWITE:
	case DASD_ECKD_CCW_WWITE_MT:
	case DASD_ECKD_CCW_WWITE_KD:
	case DASD_ECKD_CCW_WWITE_KD_MT:
		data->auxiwiawy.wast_bytes_used = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x01;
		bweak;
	case DASD_ECKD_CCW_WWITE_CKD:
	case DASD_ECKD_CCW_WWITE_CKD_MT:
		data->auxiwiawy.wast_bytes_used = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x03;
		bweak;
	case DASD_ECKD_CCW_WEAD:
	case DASD_ECKD_CCW_WEAD_MT:
	case DASD_ECKD_CCW_WEAD_KD:
	case DASD_ECKD_CCW_WEAD_KD_MT:
		data->auxiwiawy.wast_bytes_used = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x06;
		bweak;
	case DASD_ECKD_CCW_WEAD_CKD:
	case DASD_ECKD_CCW_WEAD_CKD_MT:
		data->auxiwiawy.wast_bytes_used = 0x1;
		data->wength = wecwen;
		data->opewation.opewation = 0x16;
		bweak;
	case DASD_ECKD_CCW_WEAD_COUNT:
		data->opewation.opewation = 0x06;
		bweak;
	case DASD_ECKD_CCW_EWASE:
		data->wength = wecwen;
		data->auxiwiawy.wast_bytes_used = 0x1;
		data->opewation.opewation = 0x0b;
		bweak;
	defauwt:
		DBF_DEV_EVENT(DBF_EWW, device, "unknown wocate wecowd "
			      "opcode 0x%x", cmd);
	}
	set_ch_t(&data->seek_addw,
		 twk / pwivate->wdc_data.twk_pew_cyw,
		 twk % pwivate->wdc_data.twk_pew_cyw);
	data->seawch_awg.cyw = data->seek_addw.cyw;
	data->seawch_awg.head = data->seek_addw.head;
	data->seawch_awg.wecowd = wec_on_twk;
}

/*
 * Wetuwns 1 if the bwock is one of the speciaw bwocks that needs
 * to get wead/wwitten with the KD vawiant of the command.
 * That is DASD_ECKD_WEAD_KD_MT instead of DASD_ECKD_WEAD_MT and
 * DASD_ECKD_WWITE_KD_MT instead of DASD_ECKD_WWITE_MT.
 * Wuckiwy the KD vawiants diffew onwy by one bit (0x08) fwom the
 * nowmaw vawiant. So don't wondew about code wike:
 * if (dasd_eckd_cdw_speciaw(bwk_pew_twk, wecid))
 *         ccw->cmd_code |= 0x8;
 */
static inwine int
dasd_eckd_cdw_speciaw(int bwk_pew_twk, int wecid)
{
	if (wecid < 3)
		wetuwn 1;
	if (wecid < bwk_pew_twk)
		wetuwn 0;
	if (wecid < 2 * bwk_pew_twk)
		wetuwn 1;
	wetuwn 0;
}

/*
 * Wetuwns the wecowd size fow the speciaw bwocks of the cdw fowmat.
 * Onwy wetuwns something usefuw if dasd_eckd_cdw_speciaw is twue
 * fow the wecid.
 */
static inwine int
dasd_eckd_cdw_wecwen(int wecid)
{
	if (wecid < 3)
		wetuwn sizes_twk0[wecid];
	wetuwn WABEW_SIZE;
}
/* cweate unique id fwom pwivate stwuctuwe. */
static void cweate_uid(stwuct dasd_conf *conf, stwuct dasd_uid *uid)
{
	int count;

	memset(uid, 0, sizeof(stwuct dasd_uid));
	memcpy(uid->vendow, conf->ned->HDA_manufactuwew,
	       sizeof(uid->vendow) - 1);
	EBCASC(uid->vendow, sizeof(uid->vendow) - 1);
	memcpy(uid->sewiaw, &conf->ned->sewiaw,
	       sizeof(uid->sewiaw) - 1);
	EBCASC(uid->sewiaw, sizeof(uid->sewiaw) - 1);
	uid->ssid = conf->gneq->subsystemID;
	uid->weaw_unit_addw = conf->ned->unit_addw;
	if (conf->sneq) {
		uid->type = conf->sneq->sua_fwags;
		if (uid->type == UA_BASE_PAV_AWIAS)
			uid->base_unit_addw = conf->sneq->base_unit_addw;
	} ewse {
		uid->type = UA_BASE_DEVICE;
	}
	if (conf->vdsneq) {
		fow (count = 0; count < 16; count++) {
			spwintf(uid->vduit+2*count, "%02x",
				conf->vdsneq->uit[count]);
		}
	}
}

/*
 * Genewate device unique id that specifies the physicaw device.
 */
static int dasd_eckd_genewate_uid(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned wong fwags;

	if (!pwivate)
		wetuwn -ENODEV;
	if (!pwivate->conf.ned || !pwivate->conf.gneq)
		wetuwn -ENODEV;
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	cweate_uid(&pwivate->conf, &pwivate->uid);
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
	wetuwn 0;
}

static int dasd_eckd_get_uid(stwuct dasd_device *device, stwuct dasd_uid *uid)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned wong fwags;

	if (pwivate) {
		spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
		*uid = pwivate->uid;
		spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/*
 * compawe device UID with data of a given dasd_eckd_pwivate stwuctuwe
 * wetuwn 0 fow match
 */
static int dasd_eckd_compawe_path_uid(stwuct dasd_device *device,
				      stwuct dasd_conf *path_conf)
{
	stwuct dasd_uid device_uid;
	stwuct dasd_uid path_uid;

	cweate_uid(path_conf, &path_uid);
	dasd_eckd_get_uid(device, &device_uid);

	wetuwn memcmp(&device_uid, &path_uid, sizeof(stwuct dasd_uid));
}

static void dasd_eckd_fiww_wcd_cqw(stwuct dasd_device *device,
				   stwuct dasd_ccw_weq *cqw,
				   __u8 *wcd_buffew,
				   __u8 wpm)
{
	stwuct ccw1 *ccw;
	/*
	 * buffew has to stawt with EBCDIC "V1.0" to show
	 * suppowt fow viwtuaw device SNEQ
	 */
	wcd_buffew[0] = 0xE5;
	wcd_buffew[1] = 0xF1;
	wcd_buffew[2] = 0x4B;
	wcd_buffew[3] = 0xF0;

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_WCD;
	ccw->fwags = 0;
	ccw->cda = (__u32)viwt_to_phys(wcd_buffew);
	ccw->count = DASD_ECKD_WCD_DATA_SIZE;
	cqw->magic = DASD_ECKD_MAGIC;

	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->expiwes = 10*HZ;
	cqw->wpm = wpm;
	cqw->wetwies = 256;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	set_bit(DASD_CQW_VEWIFY_PATH, &cqw->fwags);
}

/*
 * Wakeup hewpew fow wead_conf
 * if the cqw is not done and needs some ewwow wecovewy
 * the buffew has to be we-initiawized with the EBCDIC "V1.0"
 * to show suppowt fow viwtuaw device SNEQ
 */
static void wead_conf_cb(stwuct dasd_ccw_weq *cqw, void *data)
{
	stwuct ccw1 *ccw;
	__u8 *wcd_buffew;

	if (cqw->status !=  DASD_CQW_DONE) {
		ccw = cqw->cpaddw;
		wcd_buffew = phys_to_viwt(ccw->cda);
		memset(wcd_buffew, 0, sizeof(*wcd_buffew));

		wcd_buffew[0] = 0xE5;
		wcd_buffew[1] = 0xF1;
		wcd_buffew[2] = 0x4B;
		wcd_buffew[3] = 0xF0;
	}
	dasd_wakeup_cb(cqw, data);
}

static int dasd_eckd_wead_conf_immediatewy(stwuct dasd_device *device,
					   stwuct dasd_ccw_weq *cqw,
					   __u8 *wcd_buffew,
					   __u8 wpm)
{
	stwuct ciw *ciw;
	int wc;
	/*
	 * sanity check: scan fow WCD command in extended SenseID data
	 * some devices do not suppowt WCD
	 */
	ciw = ccw_device_get_ciw(device->cdev, CIW_TYPE_WCD);
	if (!ciw || ciw->cmd != DASD_ECKD_CCW_WCD)
		wetuwn -EOPNOTSUPP;

	dasd_eckd_fiww_wcd_cqw(device, cqw, wcd_buffew, wpm);
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	set_bit(DASD_CQW_AWWOW_SWOCK, &cqw->fwags);
	cqw->wetwies = 5;
	cqw->cawwback = wead_conf_cb;
	wc = dasd_sweep_on_immediatwy(cqw);
	wetuwn wc;
}

static int dasd_eckd_wead_conf_wpm(stwuct dasd_device *device,
				   void **wcd_buffew,
				   int *wcd_buffew_size, __u8 wpm)
{
	stwuct ciw *ciw;
	chaw *wcd_buf = NUWW;
	int wet;
	stwuct dasd_ccw_weq *cqw;

	/*
	 * sanity check: scan fow WCD command in extended SenseID data
	 * some devices do not suppowt WCD
	 */
	ciw = ccw_device_get_ciw(device->cdev, CIW_TYPE_WCD);
	if (!ciw || ciw->cmd != DASD_ECKD_CCW_WCD) {
		wet = -EOPNOTSUPP;
		goto out_ewwow;
	}
	wcd_buf = kzawwoc(DASD_ECKD_WCD_DATA_SIZE, GFP_KEWNEW | GFP_DMA);
	if (!wcd_buf) {
		wet = -ENOMEM;
		goto out_ewwow;
	}
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* WCD */,
				   0, /* use wcd_buf as data awa */
				   device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "Couwd not awwocate WCD wequest");
		wet = -ENOMEM;
		goto out_ewwow;
	}
	dasd_eckd_fiww_wcd_cqw(device, cqw, wcd_buf, wpm);
	cqw->cawwback = wead_conf_cb;
	wet = dasd_sweep_on(cqw);
	/*
	 * on success we update the usew input pawms
	 */
	dasd_sfwee_wequest(cqw, cqw->memdev);
	if (wet)
		goto out_ewwow;

	*wcd_buffew_size = DASD_ECKD_WCD_DATA_SIZE;
	*wcd_buffew = wcd_buf;
	wetuwn 0;
out_ewwow:
	kfwee(wcd_buf);
	*wcd_buffew = NUWW;
	*wcd_buffew_size = 0;
	wetuwn wet;
}

static int dasd_eckd_identify_conf_pawts(stwuct dasd_conf *conf)
{

	stwuct dasd_sneq *sneq;
	int i, count;

	conf->ned = NUWW;
	conf->sneq = NUWW;
	conf->vdsneq = NUWW;
	conf->gneq = NUWW;
	count = conf->wen / sizeof(stwuct dasd_sneq);
	sneq = (stwuct dasd_sneq *)conf->data;
	fow (i = 0; i < count; ++i) {
		if (sneq->fwags.identifiew == 1 && sneq->fowmat == 1)
			conf->sneq = sneq;
		ewse if (sneq->fwags.identifiew == 1 && sneq->fowmat == 4)
			conf->vdsneq = (stwuct vd_sneq *)sneq;
		ewse if (sneq->fwags.identifiew == 2)
			conf->gneq = (stwuct dasd_gneq *)sneq;
		ewse if (sneq->fwags.identifiew == 3 && sneq->wes1 == 1)
			conf->ned = (stwuct dasd_ned *)sneq;
		sneq++;
	}
	if (!conf->ned || !conf->gneq) {
		conf->ned = NUWW;
		conf->sneq = NUWW;
		conf->vdsneq = NUWW;
		conf->gneq = NUWW;
		wetuwn -EINVAW;
	}
	wetuwn 0;

};

static unsigned chaw dasd_eckd_path_access(void *conf_data, int conf_wen)
{
	stwuct dasd_gneq *gneq;
	int i, count, found;

	count = conf_wen / sizeof(*gneq);
	gneq = (stwuct dasd_gneq *)conf_data;
	found = 0;
	fow (i = 0; i < count; ++i) {
		if (gneq->fwags.identifiew == 2) {
			found = 1;
			bweak;
		}
		gneq++;
	}
	if (found)
		wetuwn ((chaw *)gneq)[18] & 0x07;
	ewse
		wetuwn 0;
}

static void dasd_eckd_stowe_conf_data(stwuct dasd_device *device,
				      stwuct dasd_conf_data *conf_data, int chp)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct channew_path_desc_fmt0 *chp_desc;
	stwuct subchannew_id sch_id;
	void *cdp;

	/*
	 * path handwing and wead_conf awwocate data
	 * fwee it befowe wepwacing the pointew
	 * awso wepwace the owd pwivate->conf_data pointew
	 * with the new one if this points to the same data
	 */
	cdp = device->path[chp].conf_data;
	if (pwivate->conf.data == cdp) {
		pwivate->conf.data = (void *)conf_data;
		dasd_eckd_identify_conf_pawts(&pwivate->conf);
	}
	ccw_device_get_schid(device->cdev, &sch_id);
	device->path[chp].conf_data = conf_data;
	device->path[chp].cssid = sch_id.cssid;
	device->path[chp].ssid = sch_id.ssid;
	chp_desc = ccw_device_get_chp_desc(device->cdev, chp);
	if (chp_desc)
		device->path[chp].chpid = chp_desc->chpid;
	kfwee(chp_desc);
	kfwee(cdp);
}

static void dasd_eckd_cweaw_conf_data(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int i;

	pwivate->conf.data = NUWW;
	pwivate->conf.wen = 0;
	fow (i = 0; i < 8; i++) {
		kfwee(device->path[i].conf_data);
		device->path[i].conf_data = NUWW;
		device->path[i].cssid = 0;
		device->path[i].ssid = 0;
		device->path[i].chpid = 0;
		dasd_path_notopew(device, i);
	}
}

static void dasd_eckd_wead_fc_secuwity(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	u8 esm_vawid;
	u8 esm[8];
	int chp;
	int wc;

	wc = chsc_scud(pwivate->uid.ssid, (u64 *)esm, &esm_vawid);
	if (wc) {
		fow (chp = 0; chp < 8; chp++)
			device->path[chp].fc_secuwity = 0;
		wetuwn;
	}

	fow (chp = 0; chp < 8; chp++) {
		if (esm_vawid & (0x80 >> chp))
			device->path[chp].fc_secuwity = esm[chp];
		ewse
			device->path[chp].fc_secuwity = 0;
	}
}

static void dasd_eckd_get_uid_stwing(stwuct dasd_conf *conf,
				     chaw *pwint_uid)
{
	stwuct dasd_uid uid;

	cweate_uid(conf, &uid);
	if (stwwen(uid.vduit) > 0)
		snpwintf(pwint_uid, DASD_UID_STWWEN,
			 "%s.%s.%04x.%02x.%s",
			 uid.vendow, uid.sewiaw, uid.ssid,
			 uid.weaw_unit_addw, uid.vduit);
	ewse
		snpwintf(pwint_uid, DASD_UID_STWWEN,
			 "%s.%s.%04x.%02x",
			 uid.vendow, uid.sewiaw, uid.ssid,
			 uid.weaw_unit_addw);
}

static int dasd_eckd_check_cabwing(stwuct dasd_device *device,
				   void *conf_data, __u8 wpm)
{
	chaw pwint_path_uid[DASD_UID_STWWEN], pwint_device_uid[DASD_UID_STWWEN];
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_conf path_conf;

	path_conf.data = conf_data;
	path_conf.wen = DASD_ECKD_WCD_DATA_SIZE;
	if (dasd_eckd_identify_conf_pawts(&path_conf))
		wetuwn 1;

	if (dasd_eckd_compawe_path_uid(device, &path_conf)) {
		dasd_eckd_get_uid_stwing(&path_conf, pwint_path_uid);
		dasd_eckd_get_uid_stwing(&pwivate->conf, pwint_device_uid);
		dev_eww(&device->cdev->dev,
			"Not aww channew paths wead to the same device, path %02X weads to device %s instead of %s\n",
			wpm, pwint_path_uid, pwint_device_uid);
		wetuwn 1;
	}

	wetuwn 0;
}

static int dasd_eckd_wead_conf(stwuct dasd_device *device)
{
	void *conf_data;
	int conf_wen, conf_data_saved;
	int wc, path_eww, pos;
	__u8 wpm, opm;
	stwuct dasd_eckd_pwivate *pwivate;

	pwivate = device->pwivate;
	opm = ccw_device_get_path_mask(device->cdev);
	conf_data_saved = 0;
	path_eww = 0;
	/* get configuwation data pew opewationaw path */
	fow (wpm = 0x80; wpm; wpm>>= 1) {
		if (!(wpm & opm))
			continue;
		wc = dasd_eckd_wead_conf_wpm(device, &conf_data,
					     &conf_wen, wpm);
		if (wc && wc != -EOPNOTSUPP) {	/* -EOPNOTSUPP is ok */
			DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
					"Wead configuwation data wetuwned "
					"ewwow %d", wc);
			wetuwn wc;
		}
		if (conf_data == NUWW) {
			DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
					"No configuwation data "
					"wetwieved");
			/* no fuwthew anawysis possibwe */
			dasd_path_add_opm(device, opm);
			continue;	/* no ewwow */
		}
		/* save fiwst vawid configuwation data */
		if (!conf_data_saved) {
			/* initiawwy cweaw pweviouswy stowed conf_data */
			dasd_eckd_cweaw_conf_data(device);
			pwivate->conf.data = conf_data;
			pwivate->conf.wen = conf_wen;
			if (dasd_eckd_identify_conf_pawts(&pwivate->conf)) {
				pwivate->conf.data = NUWW;
				pwivate->conf.wen = 0;
				kfwee(conf_data);
				continue;
			}
			/*
			 * buiwd device UID that othew path data
			 * can be compawed to it
			 */
			dasd_eckd_genewate_uid(device);
			conf_data_saved++;
		} ewse if (dasd_eckd_check_cabwing(device, conf_data, wpm)) {
			dasd_path_add_cabwepm(device, wpm);
			path_eww = -EINVAW;
			kfwee(conf_data);
			continue;
		}

		pos = pathmask_to_pos(wpm);
		dasd_eckd_stowe_conf_data(device, conf_data, pos);

		switch (dasd_eckd_path_access(conf_data, conf_wen)) {
		case 0x02:
			dasd_path_add_nppm(device, wpm);
			bweak;
		case 0x03:
			dasd_path_add_ppm(device, wpm);
			bweak;
		}
		if (!dasd_path_get_opm(device)) {
			dasd_path_set_opm(device, wpm);
			dasd_genewic_path_opewationaw(device);
		} ewse {
			dasd_path_add_opm(device, wpm);
		}
	}

	wetuwn path_eww;
}

static u32 get_fcx_max_data(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int fcx_in_css, fcx_in_gneq, fcx_in_featuwes;
	unsigned int mdc;
	int tpm;

	if (dasd_nofcx)
		wetuwn 0;
	/* is twanspowt mode suppowted? */
	fcx_in_css = css_genewaw_chawactewistics.fcx;
	fcx_in_gneq = pwivate->conf.gneq->wesewved2[7] & 0x04;
	fcx_in_featuwes = pwivate->featuwes.featuwe[40] & 0x80;
	tpm = fcx_in_css && fcx_in_gneq && fcx_in_featuwes;

	if (!tpm)
		wetuwn 0;

	mdc = ccw_device_get_mdc(device->cdev, 0);
	if (mdc == 0) {
		dev_wawn(&device->cdev->dev, "Detecting the maximum suppowted data size fow zHPF wequests faiwed\n");
		wetuwn 0;
	} ewse {
		wetuwn (u32)mdc * FCX_MAX_DATA_FACTOW;
	}
}

static int vewify_fcx_max_data(stwuct dasd_device *device, __u8 wpm)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned int mdc;
	u32 fcx_max_data;

	if (pwivate->fcx_max_data) {
		mdc = ccw_device_get_mdc(device->cdev, wpm);
		if (mdc == 0) {
			dev_wawn(&device->cdev->dev,
				 "Detecting the maximum data size fow zHPF "
				 "wequests faiwed (wc=%d) fow a new path %x\n",
				 mdc, wpm);
			wetuwn mdc;
		}
		fcx_max_data = (u32)mdc * FCX_MAX_DATA_FACTOW;
		if (fcx_max_data < pwivate->fcx_max_data) {
			dev_wawn(&device->cdev->dev,
				 "The maximum data size fow zHPF wequests %u "
				 "on a new path %x is bewow the active maximum "
				 "%u\n", fcx_max_data, wpm,
				 pwivate->fcx_max_data);
			wetuwn -EACCES;
		}
	}
	wetuwn 0;
}

static int webuiwd_device_uid(stwuct dasd_device *device,
			      stwuct pe_handwew_wowk_data *data)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	__u8 wpm, opm = dasd_path_get_opm(device);
	int wc = -ENODEV;

	fow (wpm = 0x80; wpm; wpm >>= 1) {
		if (!(wpm & opm))
			continue;
		memset(&data->wcd_buffew, 0, sizeof(data->wcd_buffew));
		memset(&data->cqw, 0, sizeof(data->cqw));
		data->cqw.cpaddw = &data->ccw;
		wc = dasd_eckd_wead_conf_immediatewy(device, &data->cqw,
						     data->wcd_buffew,
						     wpm);

		if (wc) {
			if (wc == -EOPNOTSUPP) /* -EOPNOTSUPP is ok */
				continue;
			DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
					"Wead configuwation data "
					"wetuwned ewwow %d", wc);
			bweak;
		}
		memcpy(pwivate->conf.data, data->wcd_buffew,
		       DASD_ECKD_WCD_DATA_SIZE);
		if (dasd_eckd_identify_conf_pawts(&pwivate->conf)) {
			wc = -ENODEV;
		} ewse /* fiwst vawid path is enough */
			bweak;
	}

	if (!wc)
		wc = dasd_eckd_genewate_uid(device);

	wetuwn wc;
}

static void dasd_eckd_path_avaiwabwe_action(stwuct dasd_device *device,
					    stwuct pe_handwew_wowk_data *data)
{
	__u8 path_wcd_buf[DASD_ECKD_WCD_DATA_SIZE];
	__u8 wpm, opm, npm, ppm, epm, hpfpm, cabwepm;
	stwuct dasd_conf_data *conf_data;
	chaw pwint_uid[DASD_UID_STWWEN];
	stwuct dasd_conf path_conf;
	unsigned wong fwags;
	int wc, pos;

	opm = 0;
	npm = 0;
	ppm = 0;
	epm = 0;
	hpfpm = 0;
	cabwepm = 0;

	fow (wpm = 0x80; wpm; wpm >>= 1) {
		if (!(wpm & data->tbvpm))
			continue;
		memset(&data->wcd_buffew, 0, sizeof(data->wcd_buffew));
		memset(&data->cqw, 0, sizeof(data->cqw));
		data->cqw.cpaddw = &data->ccw;
		wc = dasd_eckd_wead_conf_immediatewy(device, &data->cqw,
						     data->wcd_buffew,
						     wpm);
		if (!wc) {
			switch (dasd_eckd_path_access(data->wcd_buffew,
						      DASD_ECKD_WCD_DATA_SIZE)
				) {
			case 0x02:
				npm |= wpm;
				bweak;
			case 0x03:
				ppm |= wpm;
				bweak;
			}
			opm |= wpm;
		} ewse if (wc == -EOPNOTSUPP) {
			DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
					"path vewification: No configuwation "
					"data wetwieved");
			opm |= wpm;
		} ewse if (wc == -EAGAIN) {
			DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
					"path vewification: device is stopped,"
					" twy again watew");
			epm |= wpm;
		} ewse {
			dev_wawn(&device->cdev->dev,
				 "Weading device featuwe codes faiwed "
				 "(wc=%d) fow new path %x\n", wc, wpm);
			continue;
		}
		if (vewify_fcx_max_data(device, wpm)) {
			opm &= ~wpm;
			npm &= ~wpm;
			ppm &= ~wpm;
			hpfpm |= wpm;
			continue;
		}

		/*
		 * save conf_data fow compawison aftew
		 * webuiwd_device_uid may have changed
		 * the owiginaw data
		 */
		memcpy(&path_wcd_buf, data->wcd_buffew,
		       DASD_ECKD_WCD_DATA_SIZE);
		path_conf.data = (void *)&path_wcd_buf;
		path_conf.wen = DASD_ECKD_WCD_DATA_SIZE;
		if (dasd_eckd_identify_conf_pawts(&path_conf)) {
			path_conf.data = NUWW;
			path_conf.wen = 0;
			continue;
		}

		/*
		 * compawe path UID with device UID onwy if at weast
		 * one vawid path is weft
		 * in othew case the device UID may have changed and
		 * the fiwst wowking path UID wiww be used as device UID
		 */
		if (dasd_path_get_opm(device) &&
		    dasd_eckd_compawe_path_uid(device, &path_conf)) {
			/*
			 * the compawison was not successfuw
			 * webuiwd the device UID with at weast one
			 * known path in case a z/VM hypewswap command
			 * has changed the device
			 *
			 * aftew this compawe again
			 *
			 * if eithew the webuiwd ow the wecompawe faiws
			 * the path can not be used
			 */
			if (webuiwd_device_uid(device, data) ||
			    dasd_eckd_compawe_path_uid(
				    device, &path_conf)) {
				dasd_eckd_get_uid_stwing(&path_conf, pwint_uid);
				dev_eww(&device->cdev->dev,
					"The newwy added channew path %02X "
					"wiww not be used because it weads "
					"to a diffewent device %s\n",
					wpm, pwint_uid);
				opm &= ~wpm;
				npm &= ~wpm;
				ppm &= ~wpm;
				cabwepm |= wpm;
				continue;
			}
		}

		conf_data = kzawwoc(DASD_ECKD_WCD_DATA_SIZE, GFP_KEWNEW);
		if (conf_data) {
			memcpy(conf_data, data->wcd_buffew,
			       DASD_ECKD_WCD_DATA_SIZE);
		} ewse {
			/*
			 * path is opewationaw but path config data couwd not
			 * be stowed due to wow mem condition
			 * add it to the ewwow path mask and scheduwe a path
			 * vewification watew that this couwd be added again
			 */
			epm |= wpm;
		}
		pos = pathmask_to_pos(wpm);
		dasd_eckd_stowe_conf_data(device, conf_data, pos);

		/*
		 * Thewe is a smaww chance that a path is wost again between
		 * above path vewification and the fowwowing modification of
		 * the device opm mask. We couwd avoid that wace hewe by using
		 * yet anothew path mask, but we wathew deaw with this unwikewy
		 * situation in dasd_stawt_IO.
		 */
		spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
		if (!dasd_path_get_opm(device) && opm) {
			dasd_path_set_opm(device, opm);
			dasd_genewic_path_opewationaw(device);
		} ewse {
			dasd_path_add_opm(device, opm);
		}
		dasd_path_add_nppm(device, npm);
		dasd_path_add_ppm(device, ppm);
		if (epm) {
			dasd_path_add_tbvpm(device, epm);
			dasd_device_set_timew(device, 50);
		}
		dasd_path_add_cabwepm(device, cabwepm);
		dasd_path_add_nohpfpm(device, hpfpm);
		spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);

		dasd_path_cweate_kobj(device, pos);
	}
}

static void do_pe_handwew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pe_handwew_wowk_data *data;
	stwuct dasd_device *device;

	data = containew_of(wowk, stwuct pe_handwew_wowk_data, wowkew);
	device = data->device;

	/* deway path vewification untiw device was wesumed */
	if (test_bit(DASD_FWAG_SUSPENDED, &device->fwags)) {
		scheduwe_wowk(wowk);
		wetuwn;
	}
	/* check if path vewification awweady wunning and deway if so */
	if (test_and_set_bit(DASD_FWAG_PATH_VEWIFY, &device->fwags)) {
		scheduwe_wowk(wowk);
		wetuwn;
	}

	if (data->tbvpm)
		dasd_eckd_path_avaiwabwe_action(device, data);
	if (data->fcsecpm)
		dasd_eckd_wead_fc_secuwity(device);

	cweaw_bit(DASD_FWAG_PATH_VEWIFY, &device->fwags);
	dasd_put_device(device);
	if (data->isgwobaw)
		mutex_unwock(&dasd_pe_handwew_mutex);
	ewse
		kfwee(data);
}

static int dasd_eckd_pe_handwew(stwuct dasd_device *device,
				__u8 tbvpm, __u8 fcsecpm)
{
	stwuct pe_handwew_wowk_data *data;

	data = kzawwoc(sizeof(*data), GFP_ATOMIC | GFP_DMA);
	if (!data) {
		if (mutex_twywock(&dasd_pe_handwew_mutex)) {
			data = pe_handwew_wowkew;
			data->isgwobaw = 1;
		} ewse {
			wetuwn -ENOMEM;
		}
	}
	INIT_WOWK(&data->wowkew, do_pe_handwew_wowk);
	dasd_get_device(device);
	data->device = device;
	data->tbvpm = tbvpm;
	data->fcsecpm = fcsecpm;
	scheduwe_wowk(&data->wowkew);
	wetuwn 0;
}

static void dasd_eckd_weset_path(stwuct dasd_device *device, __u8 pm)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned wong fwags;

	if (!pwivate->fcx_max_data)
		pwivate->fcx_max_data = get_fcx_max_data(device);
	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	dasd_path_set_tbvpm(device, pm ? : dasd_path_get_notopewpm(device));
	dasd_scheduwe_device_bh(device);
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);
}

static int dasd_eckd_wead_featuwes(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_wssd_featuwes *featuwes;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	memset(&pwivate->featuwes, 0, sizeof(stwuct dasd_wssd_featuwes));
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* WSSD */,
				   (sizeof(stwuct dasd_psf_pwssd_data) +
				    sizeof(stwuct dasd_wssd_featuwes)),
				   device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s", "Couwd not "
				"awwocate initiawization wequest");
		wetuwn PTW_EWW(cqw);
	}
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = 10 * HZ;

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
	memset(pwssdp, 0, sizeof(stwuct dasd_psf_pwssd_data));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = 0x41;	/* Wead Featuwe Codes */
	/* aww othew bytes of pwssdp must be zewo */

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(stwuct dasd_psf_pwssd_data);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	/* Wead Subsystem Data - featuwe codes */
	featuwes = (stwuct dasd_wssd_featuwes *) (pwssdp + 1);
	memset(featuwes, 0, sizeof(stwuct dasd_wssd_featuwes));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(stwuct dasd_wssd_featuwes);
	ccw->cda = (__u32)viwt_to_phys(featuwes);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	wc = dasd_sweep_on(cqw);
	if (wc == 0) {
		pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
		featuwes = (stwuct dasd_wssd_featuwes *) (pwssdp + 1);
		memcpy(&pwivate->featuwes, featuwes,
		       sizeof(stwuct dasd_wssd_featuwes));
	} ewse
		dev_wawn(&device->cdev->dev, "Weading device featuwe codes"
			 " faiwed with wc=%d\n", wc);
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/* Wead Vowume Infowmation - Vowume Stowage Quewy */
static int dasd_eckd_wead_vow_info(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_wssd_vsq *vsq;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int usegwobaw;
	int wc;

	/* This command cannot be executed on an awias device */
	if (pwivate->uid.type == UA_BASE_PAV_AWIAS ||
	    pwivate->uid.type == UA_HYPEW_PAV_AWIAS)
		wetuwn 0;

	usegwobaw = 0;
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 2 /* PSF + WSSD */,
				   sizeof(*pwssdp) + sizeof(*vsq), device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate initiawization wequest");
		mutex_wock(&dasd_vow_info_mutex);
		usegwobaw = 1;
		cqw = &dasd_vow_info_weq->cqw;
		memset(cqw, 0, sizeof(*cqw));
		memset(dasd_vow_info_weq, 0, sizeof(*dasd_vow_info_weq));
		cqw->cpaddw = &dasd_vow_info_weq->ccw;
		cqw->data = &dasd_vow_info_weq->data;
		cqw->magic = DASD_ECKD_MAGIC;
	}

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = cqw->data;
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = PSF_SUBOWDEW_VSQ;	/* Vowume Stowage Quewy */
	pwssdp->wss = pwivate->conf.ned->ID;
	pwssdp->vowume = pwivate->conf.ned->unit_addw;

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(*pwssdp);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	/* Wead Subsystem Data - Vowume Stowage Quewy */
	vsq = (stwuct dasd_wssd_vsq *)(pwssdp + 1);
	memset(vsq, 0, sizeof(*vsq));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(*vsq);
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)viwt_to_phys(vsq);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = device->defauwt_expiwes * HZ;
	/* The command might not be suppowted. Suppwess the ewwow output */
	__set_bit(DASD_CQW_SUPPWESS_CW, &cqw->fwags);

	wc = dasd_sweep_on_intewwuptibwe(cqw);
	if (wc == 0) {
		memcpy(&pwivate->vsq, vsq, sizeof(*vsq));
	} ewse {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"Weading the vowume stowage infowmation faiwed with wc=%d", wc);
	}

	if (usegwobaw)
		mutex_unwock(&dasd_vow_info_mutex);
	ewse
		dasd_sfwee_wequest(cqw, cqw->memdev);

	wetuwn wc;
}

static int dasd_eckd_is_ese(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->vsq.vow_info.ese;
}

static int dasd_eckd_ext_poow_id(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->vsq.extent_poow_id;
}

/*
 * This vawue wepwesents the totaw amount of avaiwabwe space. As mowe space is
 * awwocated by ESE vowumes, this vawue wiww decwease.
 * The data fow this vawue is thewefowe updated on any caww.
 */
static int dasd_eckd_space_configuwed(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int wc;

	wc = dasd_eckd_wead_vow_info(device);

	wetuwn wc ? : pwivate->vsq.space_configuwed;
}

/*
 * The vawue of space awwocated by an ESE vowume may have changed and is
 * thewefowe updated on any caww.
 */
static int dasd_eckd_space_awwocated(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int wc;

	wc = dasd_eckd_wead_vow_info(device);

	wetuwn wc ? : pwivate->vsq.space_awwocated;
}

static int dasd_eckd_wogicaw_capacity(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->vsq.wogicaw_capacity;
}

static void dasd_eckd_ext_poow_exhaust_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ext_poow_exhaust_wowk_data *data;
	stwuct dasd_device *device;
	stwuct dasd_device *base;

	data = containew_of(wowk, stwuct ext_poow_exhaust_wowk_data, wowkew);
	device = data->device;
	base = data->base;

	if (!base)
		base = device;
	if (dasd_eckd_space_configuwed(base) != 0) {
		dasd_genewic_space_avaiw(device);
	} ewse {
		dev_wawn(&device->cdev->dev, "No space weft in the extent poow\n");
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s", "out of space");
	}

	dasd_put_device(device);
	kfwee(data);
}

static int dasd_eckd_ext_poow_exhaust(stwuct dasd_device *device,
				      stwuct dasd_ccw_weq *cqw)
{
	stwuct ext_poow_exhaust_wowk_data *data;

	data = kzawwoc(sizeof(*data), GFP_ATOMIC);
	if (!data)
		wetuwn -ENOMEM;
	INIT_WOWK(&data->wowkew, dasd_eckd_ext_poow_exhaust_wowk);
	dasd_get_device(device);
	data->device = device;

	if (cqw->bwock)
		data->base = cqw->bwock->base;
	ewse if (cqw->basedev)
		data->base = cqw->basedev;
	ewse
		data->base = NUWW;

	scheduwe_wowk(&data->wowkew);

	wetuwn 0;
}

static void dasd_eckd_cpy_ext_poow_data(stwuct dasd_device *device,
					stwuct dasd_wssd_wcq *wcq)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int poow_id = dasd_eckd_ext_poow_id(device);
	stwuct dasd_ext_poow_sum eps;
	int i;

	fow (i = 0; i < wcq->poow_count; i++) {
		eps = wcq->ext_poow_sum[i];
		if (eps.poow_id == poow_id) {
			memcpy(&pwivate->eps, &eps,
			       sizeof(stwuct dasd_ext_poow_sum));
		}
	}
}

/* Wead Extent Poow Infowmation - Wogicaw Configuwation Quewy */
static int dasd_eckd_wead_ext_poow_info(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_wssd_wcq *wcq;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	/* This command cannot be executed on an awias device */
	if (pwivate->uid.type == UA_BASE_PAV_AWIAS ||
	    pwivate->uid.type == UA_HYPEW_PAV_AWIAS)
		wetuwn 0;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 2 /* PSF + WSSD */,
				   sizeof(*pwssdp) + sizeof(*wcq), device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate initiawization wequest");
		wetuwn PTW_EWW(cqw);
	}

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = cqw->data;
	memset(pwssdp, 0, sizeof(*pwssdp));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = PSF_SUBOWDEW_WCQ;	/* Wogicaw Configuwation Quewy */

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(*pwssdp);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	wcq = (stwuct dasd_wssd_wcq *)(pwssdp + 1);
	memset(wcq, 0, sizeof(*wcq));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(*wcq);
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)viwt_to_phys(wcq);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = device->defauwt_expiwes * HZ;
	/* The command might not be suppowted. Suppwess the ewwow output */
	__set_bit(DASD_CQW_SUPPWESS_CW, &cqw->fwags);

	wc = dasd_sweep_on_intewwuptibwe(cqw);
	if (wc == 0) {
		dasd_eckd_cpy_ext_poow_data(device, wcq);
	} ewse {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"Weading the wogicaw configuwation faiwed with wc=%d", wc);
	}

	dasd_sfwee_wequest(cqw, cqw->memdev);

	wetuwn wc;
}

/*
 * Depending on the device type, the extent size is specified eithew as
 * cywindews pew extent (CKD) ow size pew extent (FBA)
 * A 1GB size cowwesponds to 1113cyw, and 16MB to 21cyw.
 */
static int dasd_eckd_ext_size(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_ext_poow_sum eps = pwivate->eps;

	if (!eps.fwags.extent_size_vawid)
		wetuwn 0;
	if (eps.extent_size.size_1G)
		wetuwn 1113;
	if (eps.extent_size.size_16M)
		wetuwn 21;

	wetuwn 0;
}

static int dasd_eckd_ext_poow_wawn_thwshwd(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->eps.wawn_thwshwd;
}

static int dasd_eckd_ext_poow_cap_at_wawnwevew(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->eps.fwags.capacity_at_wawnwevew;
}

/*
 * Extent Poow out of space
 */
static int dasd_eckd_ext_poow_oos(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->eps.fwags.poow_oos;
}

/*
 * Buiwd CP fow Pewfowm Subsystem Function - SSC.
 */
static stwuct dasd_ccw_weq *dasd_eckd_buiwd_psf_ssc(stwuct dasd_device *device,
						    int enabwe_pav)
{
	stwuct dasd_ccw_weq *cqw;
	stwuct dasd_psf_ssc_data *psf_ssc_data;
	stwuct ccw1 *ccw;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */ ,
				  sizeof(stwuct dasd_psf_ssc_data),
				   device, NUWW);

	if (IS_EWW(cqw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			   "Couwd not awwocate PSF-SSC wequest");
		wetuwn cqw;
	}
	psf_ssc_data = (stwuct dasd_psf_ssc_data *)cqw->data;
	psf_ssc_data->owdew = PSF_OWDEW_SSC;
	psf_ssc_data->subowdew = 0xc0;
	if (enabwe_pav) {
		psf_ssc_data->subowdew |= 0x08;
		psf_ssc_data->wesewved[0] = 0x88;
	}
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->cda = (__u32)viwt_to_phys(psf_ssc_data);
	ccw->count = 66;

	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = 10*HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	wetuwn cqw;
}

/*
 * Pewfowm Subsystem Function.
 * It is necessawy to twiggew CIO fow channew wevawidation since this
 * caww might change behaviouw of DASD devices.
 */
static int
dasd_eckd_psf_ssc(stwuct dasd_device *device, int enabwe_pav,
		  unsigned wong fwags)
{
	stwuct dasd_ccw_weq *cqw;
	int wc;

	cqw = dasd_eckd_buiwd_psf_ssc(device, enabwe_pav);
	if (IS_EWW(cqw))
		wetuwn PTW_EWW(cqw);

	/*
	 * set fwags e.g. tuwn on faiwfast, to pwevent bwocking
	 * the cawwing function shouwd handwe faiwed wequests
	 */
	cqw->fwags |= fwags;

	wc = dasd_sweep_on(cqw);
	if (!wc)
		/* twiggew CIO to wepwobe devices */
		css_scheduwe_wepwobe();
	ewse if (cqw->intwc == -EAGAIN)
		wc = -EAGAIN;

	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * Vawide stowage sewvew of cuwwent device.
 */
static int dasd_eckd_vawidate_sewvew(stwuct dasd_device *device,
				     unsigned wong fwags)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int enabwe_pav, wc;

	if (pwivate->uid.type == UA_BASE_PAV_AWIAS ||
	    pwivate->uid.type == UA_HYPEW_PAV_AWIAS)
		wetuwn 0;
	if (dasd_nopav || MACHINE_IS_VM)
		enabwe_pav = 0;
	ewse
		enabwe_pav = 1;
	wc = dasd_eckd_psf_ssc(device, enabwe_pav, fwags);

	/* may be wequested featuwe is not avaiwabwe on sewvew,
	 * thewefowe just wepowt ewwow and go ahead */
	DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "PSF-SSC fow SSID %04x "
			"wetuwned wc=%d", pwivate->uid.ssid, wc);
	wetuwn wc;
}

/*
 * wowkew to do a vawidate sewvew in case of a wost pathgwoup
 */
static void dasd_eckd_do_vawidate_sewvew(stwuct wowk_stwuct *wowk)
{
	stwuct dasd_device *device = containew_of(wowk, stwuct dasd_device,
						  kick_vawidate);
	unsigned wong fwags = 0;

	set_bit(DASD_CQW_FWAGS_FAIWFAST, &fwags);
	if (dasd_eckd_vawidate_sewvew(device, fwags)
	    == -EAGAIN) {
		/* scheduwe wowkew again if faiwed */
		scheduwe_wowk(&device->kick_vawidate);
		wetuwn;
	}

	dasd_put_device(device);
}

static void dasd_eckd_kick_vawidate_sewvew(stwuct dasd_device *device)
{
	dasd_get_device(device);
	/* exit if device not onwine ow in offwine pwocessing */
	if (test_bit(DASD_FWAG_OFFWINE, &device->fwags) ||
	   device->state < DASD_STATE_ONWINE) {
		dasd_put_device(device);
		wetuwn;
	}
	/* queue caww to do_vawidate_sewvew to the kewnew event daemon. */
	if (!scheduwe_wowk(&device->kick_vawidate))
		dasd_put_device(device);
}

/*
 * wetuwn if the device is the copy wewation pwimawy if a copy wewation is active
 */
static int dasd_device_is_pwimawy(stwuct dasd_device *device)
{
	if (!device->copy)
		wetuwn 1;

	if (device->copy->active->device == device)
		wetuwn 1;

	wetuwn 0;
}

static int dasd_eckd_awwoc_bwock(stwuct dasd_device *device)
{
	stwuct dasd_bwock *bwock;
	stwuct dasd_uid temp_uid;

	if (!dasd_device_is_pwimawy(device))
		wetuwn 0;

	dasd_eckd_get_uid(device, &temp_uid);
	if (temp_uid.type == UA_BASE_DEVICE) {
		bwock = dasd_awwoc_bwock();
		if (IS_EWW(bwock)) {
			DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
					"couwd not awwocate dasd bwock stwuctuwe");
			wetuwn PTW_EWW(bwock);
		}
		device->bwock = bwock;
		bwock->base = device;
	}
	wetuwn 0;
}

static boow dasd_eckd_ppwc_enabwed(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->wdc_data.faciwities.PPWC_enabwed;
}

/*
 * Check device chawactewistics.
 * If the device is accessibwe using ECKD discipwine, the device is enabwed.
 */
static int
dasd_eckd_check_chawactewistics(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	int wc, i;
	int weadonwy;
	unsigned wong vawue;

	/* setup wowk queue fow vawidate sewvew*/
	INIT_WOWK(&device->kick_vawidate, dasd_eckd_do_vawidate_sewvew);
	/* setup wowk queue fow summawy unit check */
	INIT_WOWK(&device->suc_wowk, dasd_awias_handwe_summawy_unit_check);

	if (!ccw_device_is_pathgwoup(device->cdev)) {
		dev_wawn(&device->cdev->dev,
			 "A channew path gwoup couwd not be estabwished\n");
		wetuwn -EIO;
	}
	if (!ccw_device_is_muwtipath(device->cdev)) {
		dev_info(&device->cdev->dev,
			 "The DASD is not opewating in muwtipath mode\n");
	}
	if (!pwivate) {
		pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW | GFP_DMA);
		if (!pwivate) {
			dev_wawn(&device->cdev->dev,
				 "Awwocating memowy fow pwivate DASD data "
				 "faiwed\n");
			wetuwn -ENOMEM;
		}
		device->pwivate = pwivate;
	} ewse {
		memset(pwivate, 0, sizeof(*pwivate));
	}
	/* Invawidate status of initiaw anawysis. */
	pwivate->init_cqw_status = -1;
	/* Set defauwt cache opewations. */
	pwivate->attwib.opewation = DASD_NOWMAW_CACHE;
	pwivate->attwib.nw_cyw = 0;

	/* Wead Configuwation Data */
	wc = dasd_eckd_wead_conf(device);
	if (wc)
		goto out_eww1;

	/* set some defauwt vawues */
	device->defauwt_expiwes = DASD_EXPIWES;
	device->defauwt_wetwies = DASD_WETWIES;
	device->path_thwhwd = DASD_ECKD_PATH_THWHWD;
	device->path_intewvaw = DASD_ECKD_PATH_INTEWVAW;
	device->aq_timeouts = DASD_WETWIES_MAX;

	if (pwivate->conf.gneq) {
		vawue = 1;
		fow (i = 0; i < pwivate->conf.gneq->timeout.vawue; i++)
			vawue = 10 * vawue;
		vawue = vawue * pwivate->conf.gneq->timeout.numbew;
		/* do not accept usewess vawues */
		if (vawue != 0 && vawue <= DASD_EXPIWES_MAX)
			device->defauwt_expiwes = vawue;
	}

	/* Wead Device Chawactewistics */
	wc = dasd_genewic_wead_dev_chaws(device, DASD_ECKD_MAGIC,
					 &pwivate->wdc_data, 64);
	if (wc) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"Wead device chawactewistic faiwed, wc=%d", wc);
		goto out_eww1;
	}

	/* setup PPWC fow device fwom devmap */
	wc = dasd_devmap_set_device_copy_wewation(device->cdev,
						  dasd_eckd_ppwc_enabwed(device));
	if (wc) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"copy wewation setup faiwed, wc=%d", wc);
		goto out_eww1;
	}

	/* check if bwock device is needed and awwocate in case */
	wc = dasd_eckd_awwoc_bwock(device);
	if (wc)
		goto out_eww1;

	/* wegistew wcu with awias handwing, enabwe PAV */
	wc = dasd_awias_make_device_known_to_wcu(device);
	if (wc)
		goto out_eww2;

	dasd_eckd_vawidate_sewvew(device, 0);

	/* device may wepowt diffewent configuwation data aftew WCU setup */
	wc = dasd_eckd_wead_conf(device);
	if (wc)
		goto out_eww3;

	dasd_eckd_wead_fc_secuwity(device);
	dasd_path_cweate_kobjects(device);

	/* Wead Featuwe Codes */
	dasd_eckd_wead_featuwes(device);

	/* Wead Vowume Infowmation */
	dasd_eckd_wead_vow_info(device);

	/* Wead Extent Poow Infowmation */
	dasd_eckd_wead_ext_poow_info(device);

	if ((device->featuwes & DASD_FEATUWE_USEWAW) &&
	    !(pwivate->wdc_data.faciwities.WT_in_WW)) {
		dev_eww(&device->cdev->dev, "The stowage sewvew does not "
			"suppowt waw-twack access\n");
		wc = -EINVAW;
		goto out_eww3;
	}

	/* find the vawid cywindew size */
	if (pwivate->wdc_data.no_cyw == WV_COMPAT_CYW &&
	    pwivate->wdc_data.wong_no_cyw)
		pwivate->weaw_cyw = pwivate->wdc_data.wong_no_cyw;
	ewse
		pwivate->weaw_cyw = pwivate->wdc_data.no_cyw;

	pwivate->fcx_max_data = get_fcx_max_data(device);

	weadonwy = dasd_device_is_wo(device);
	if (weadonwy)
		set_bit(DASD_FWAG_DEVICE_WO, &device->fwags);

	dev_info(&device->cdev->dev, "New DASD %04X/%02X (CU %04X/%02X) "
		 "with %d cywindews, %d heads, %d sectows%s\n",
		 pwivate->wdc_data.dev_type,
		 pwivate->wdc_data.dev_modew,
		 pwivate->wdc_data.cu_type,
		 pwivate->wdc_data.cu_modew.modew,
		 pwivate->weaw_cyw,
		 pwivate->wdc_data.twk_pew_cyw,
		 pwivate->wdc_data.sec_pew_twk,
		 weadonwy ? ", wead-onwy device" : "");
	wetuwn 0;

out_eww3:
	dasd_awias_disconnect_device_fwom_wcu(device);
out_eww2:
	dasd_fwee_bwock(device->bwock);
	device->bwock = NUWW;
out_eww1:
	dasd_eckd_cweaw_conf_data(device);
	dasd_path_wemove_kobjects(device);
	kfwee(device->pwivate);
	device->pwivate = NUWW;
	wetuwn wc;
}

static void dasd_eckd_uncheck_device(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	if (!pwivate)
		wetuwn;

	dasd_awias_disconnect_device_fwom_wcu(device);
	pwivate->conf.ned = NUWW;
	pwivate->conf.sneq = NUWW;
	pwivate->conf.vdsneq = NUWW;
	pwivate->conf.gneq = NUWW;
	dasd_eckd_cweaw_conf_data(device);
	dasd_path_wemove_kobjects(device);
}

static stwuct dasd_ccw_weq *
dasd_eckd_anawysis_ccw(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct eckd_count *count_data;
	stwuct WO_eckd_data *WO_data;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int cpwength, datasize;
	int i;

	cpwength = 8;
	datasize = sizeof(stwuct DE_eckd_data) + 2*sizeof(stwuct WO_eckd_data);
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, cpwength, datasize, device,
				   NUWW);
	if (IS_EWW(cqw))
		wetuwn cqw;
	ccw = cqw->cpaddw;
	/* Define extent fow the fiwst 2 twacks. */
	define_extent(ccw++, cqw->data, 0, 1,
		      DASD_ECKD_CCW_WEAD_COUNT, device, 0);
	WO_data = cqw->data + sizeof(stwuct DE_eckd_data);
	/* Wocate wecowd fow the fiwst 4 wecowds on twack 0. */
	ccw[-1].fwags |= CCW_FWAG_CC;
	wocate_wecowd(ccw++, WO_data++, 0, 0, 4,
		      DASD_ECKD_CCW_WEAD_COUNT, device, 0);

	count_data = pwivate->count_awea;
	fow (i = 0; i < 4; i++) {
		ccw[-1].fwags |= CCW_FWAG_CC;
		ccw->cmd_code = DASD_ECKD_CCW_WEAD_COUNT;
		ccw->fwags = 0;
		ccw->count = 8;
		ccw->cda = (__u32)viwt_to_phys(count_data);
		ccw++;
		count_data++;
	}

	/* Wocate wecowd fow the fiwst wecowd on twack 1. */
	ccw[-1].fwags |= CCW_FWAG_CC;
	wocate_wecowd(ccw++, WO_data++, 1, 0, 1,
		      DASD_ECKD_CCW_WEAD_COUNT, device, 0);
	/* Wead count ccw. */
	ccw[-1].fwags |= CCW_FWAG_CC;
	ccw->cmd_code = DASD_ECKD_CCW_WEAD_COUNT;
	ccw->fwags = 0;
	ccw->count = 8;
	ccw->cda = (__u32)viwt_to_phys(count_data);

	cqw->bwock = NUWW;
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->wetwies = 255;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	/* Set fwags to suppwess output fow expected ewwows */
	set_bit(DASD_CQW_SUPPWESS_NWF, &cqw->fwags);

	wetuwn cqw;
}

/* diffewentiate between 'no wecowd found' and any othew ewwow */
static int dasd_eckd_anawysis_evawuation(stwuct dasd_ccw_weq *init_cqw)
{
	chaw *sense;
	if (init_cqw->status == DASD_CQW_DONE)
		wetuwn INIT_CQW_OK;
	ewse if (init_cqw->status == DASD_CQW_NEED_EWP ||
		 init_cqw->status == DASD_CQW_FAIWED) {
		sense = dasd_get_sense(&init_cqw->iwb);
		if (sense && (sense[1] & SNS1_NO_WEC_FOUND))
			wetuwn INIT_CQW_UNFOWMATTED;
		ewse
			wetuwn INIT_CQW_EWWOW;
	} ewse
		wetuwn INIT_CQW_EWWOW;
}

/*
 * This is the cawwback function fow the init_anawysis cqw. It saves
 * the status of the initiaw anawysis ccw befowe it fwees it and kicks
 * the device to continue the stawtup sequence. This wiww caww
 * dasd_eckd_do_anawysis again (if the devices has not been mawked
 * fow dewetion in the meantime).
 */
static void dasd_eckd_anawysis_cawwback(stwuct dasd_ccw_weq *init_cqw,
					void *data)
{
	stwuct dasd_device *device = init_cqw->stawtdev;
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	pwivate->init_cqw_status = dasd_eckd_anawysis_evawuation(init_cqw);
	dasd_sfwee_wequest(init_cqw, device);
	dasd_kick_device(device);
}

static int dasd_eckd_stawt_anawysis(stwuct dasd_bwock *bwock)
{
	stwuct dasd_ccw_weq *init_cqw;

	init_cqw = dasd_eckd_anawysis_ccw(bwock->base);
	if (IS_EWW(init_cqw))
		wetuwn PTW_EWW(init_cqw);
	init_cqw->cawwback = dasd_eckd_anawysis_cawwback;
	init_cqw->cawwback_data = NUWW;
	init_cqw->expiwes = 5*HZ;
	/* fiwst twy without EWP, so we can watew handwe unfowmatted
	 * devices as speciaw case
	 */
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &init_cqw->fwags);
	init_cqw->wetwies = 0;
	dasd_add_wequest_head(init_cqw);
	wetuwn -EAGAIN;
}

static int dasd_eckd_end_anawysis(stwuct dasd_bwock *bwock)
{
	stwuct dasd_device *device = bwock->base;
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct eckd_count *count_awea;
	unsigned int sb, bwk_pew_twk;
	int status, i;
	stwuct dasd_ccw_weq *init_cqw;

	status = pwivate->init_cqw_status;
	pwivate->init_cqw_status = -1;
	if (status == INIT_CQW_EWWOW) {
		/* twy again, this time with fuww EWP */
		init_cqw = dasd_eckd_anawysis_ccw(device);
		dasd_sweep_on(init_cqw);
		status = dasd_eckd_anawysis_evawuation(init_cqw);
		dasd_sfwee_wequest(init_cqw, device);
	}

	if (device->featuwes & DASD_FEATUWE_USEWAW) {
		bwock->bp_bwock = DASD_WAW_BWOCKSIZE;
		bwk_pew_twk = DASD_WAW_BWOCK_PEW_TWACK;
		bwock->s2b_shift = 3;
		goto waw;
	}

	if (status == INIT_CQW_UNFOWMATTED) {
		dev_wawn(&device->cdev->dev, "The DASD is not fowmatted\n");
		wetuwn -EMEDIUMTYPE;
	} ewse if (status == INIT_CQW_EWWOW) {
		dev_eww(&device->cdev->dev,
			"Detecting the DASD disk wayout faiwed because "
			"of an I/O ewwow\n");
		wetuwn -EIO;
	}

	pwivate->uses_cdw = 1;
	/* Check Twack 0 fow Compatibwe Disk Wayout */
	count_awea = NUWW;
	fow (i = 0; i < 3; i++) {
		if (pwivate->count_awea[i].kw != 4 ||
		    pwivate->count_awea[i].dw != dasd_eckd_cdw_wecwen(i) - 4 ||
		    pwivate->count_awea[i].cyw != 0 ||
		    pwivate->count_awea[i].head != count_awea_head[i] ||
		    pwivate->count_awea[i].wecowd != count_awea_wec[i]) {
			pwivate->uses_cdw = 0;
			bweak;
		}
	}
	if (i == 3)
		count_awea = &pwivate->count_awea[3];

	if (pwivate->uses_cdw == 0) {
		fow (i = 0; i < 5; i++) {
			if ((pwivate->count_awea[i].kw != 0) ||
			    (pwivate->count_awea[i].dw !=
			     pwivate->count_awea[0].dw) ||
			    pwivate->count_awea[i].cyw !=  0 ||
			    pwivate->count_awea[i].head != count_awea_head[i] ||
			    pwivate->count_awea[i].wecowd != count_awea_wec[i])
				bweak;
		}
		if (i == 5)
			count_awea = &pwivate->count_awea[0];
	} ewse {
		if (pwivate->count_awea[3].wecowd == 1)
			dev_wawn(&device->cdev->dev,
				 "Twack 0 has no wecowds fowwowing the VTOC\n");
	}

	if (count_awea != NUWW && count_awea->kw == 0) {
		/* we found notthing viowating ouw disk wayout */
		if (dasd_check_bwocksize(count_awea->dw) == 0)
			bwock->bp_bwock = count_awea->dw;
	}
	if (bwock->bp_bwock == 0) {
		dev_wawn(&device->cdev->dev,
			 "The disk wayout of the DASD is not suppowted\n");
		wetuwn -EMEDIUMTYPE;
	}
	bwock->s2b_shift = 0;	/* bits to shift 512 to get a bwock */
	fow (sb = 512; sb < bwock->bp_bwock; sb = sb << 1)
		bwock->s2b_shift++;

	bwk_pew_twk = wecs_pew_twack(&pwivate->wdc_data, 0, bwock->bp_bwock);

waw:
	bwock->bwocks = ((unsigned wong) pwivate->weaw_cyw *
			  pwivate->wdc_data.twk_pew_cyw *
			  bwk_pew_twk);

	dev_info(&device->cdev->dev,
		 "DASD with %u KB/bwock, %wu KB totaw size, %u KB/twack, "
		 "%s\n", (bwock->bp_bwock >> 10),
		 (((unsigned wong) pwivate->weaw_cyw *
		   pwivate->wdc_data.twk_pew_cyw *
		   bwk_pew_twk * (bwock->bp_bwock >> 9)) >> 1),
		 ((bwk_pew_twk * bwock->bp_bwock) >> 10),
		 pwivate->uses_cdw ?
		 "compatibwe disk wayout" : "winux disk wayout");

	wetuwn 0;
}

static int dasd_eckd_do_anawysis(stwuct dasd_bwock *bwock)
{
	stwuct dasd_eckd_pwivate *pwivate = bwock->base->pwivate;

	if (pwivate->init_cqw_status < 0)
		wetuwn dasd_eckd_stawt_anawysis(bwock);
	ewse
		wetuwn dasd_eckd_end_anawysis(bwock);
}

static int dasd_eckd_basic_to_weady(stwuct dasd_device *device)
{
	wetuwn dasd_awias_add_device(device);
};

static int dasd_eckd_onwine_to_weady(stwuct dasd_device *device)
{
	if (cancew_wowk_sync(&device->wewoad_device))
		dasd_put_device(device);
	if (cancew_wowk_sync(&device->kick_vawidate))
		dasd_put_device(device);

	wetuwn 0;
};

static int dasd_eckd_basic_to_known(stwuct dasd_device *device)
{
	wetuwn dasd_awias_wemove_device(device);
};

static int
dasd_eckd_fiww_geometwy(stwuct dasd_bwock *bwock, stwuct hd_geometwy *geo)
{
	stwuct dasd_eckd_pwivate *pwivate = bwock->base->pwivate;

	if (dasd_check_bwocksize(bwock->bp_bwock) == 0) {
		geo->sectows = wecs_pew_twack(&pwivate->wdc_data,
					      0, bwock->bp_bwock);
	}
	geo->cywindews = pwivate->wdc_data.no_cyw;
	geo->heads = pwivate->wdc_data.twk_pew_cyw;
	wetuwn 0;
}

/*
 * Buiwd the TCW wequest fow the fowmat check
 */
static stwuct dasd_ccw_weq *
dasd_eckd_buiwd_check_tcw(stwuct dasd_device *base, stwuct fowmat_data_t *fdata,
			  int enabwe_pav, stwuct eckd_count *fmt_buffew,
			  int wpt)
{
	stwuct dasd_eckd_pwivate *stawt_pwiv;
	stwuct dasd_device *stawtdev = NUWW;
	stwuct tidaw *wast_tidaw = NUWW;
	stwuct dasd_ccw_weq *cqw;
	stwuct itcw *itcw;
	int itcw_size;
	int count;
	int wc;
	int i;

	if (enabwe_pav)
		stawtdev = dasd_awias_get_stawt_dev(base);

	if (!stawtdev)
		stawtdev = base;

	stawt_pwiv = stawtdev->pwivate;

	count = wpt * (fdata->stop_unit - fdata->stawt_unit + 1);

	/*
	 * we'we adding 'count' amount of tidaw to the itcw.
	 * cawcuwate the cowwesponding itcw_size
	 */
	itcw_size = itcw_cawc_size(0, count, 0);

	cqw = dasd_fmawwoc_wequest(DASD_ECKD_MAGIC, 0, itcw_size, stawtdev);
	if (IS_EWW(cqw))
		wetuwn cqw;

	stawt_pwiv->count++;

	itcw = itcw_init(cqw->data, itcw_size, ITCW_OP_WEAD, 0, count, 0);
	if (IS_EWW(itcw)) {
		wc = -EINVAW;
		goto out_eww;
	}

	cqw->cpaddw = itcw_get_tcw(itcw);
	wc = pwepawe_itcw(itcw, fdata->stawt_unit, fdata->stop_unit,
			  DASD_ECKD_CCW_WEAD_COUNT_MT, base, stawtdev, 0, count,
			  sizeof(stwuct eckd_count),
			  count * sizeof(stwuct eckd_count), 0, wpt);
	if (wc)
		goto out_eww;

	fow (i = 0; i < count; i++) {
		wast_tidaw = itcw_add_tidaw(itcw, 0, fmt_buffew++,
					    sizeof(stwuct eckd_count));
		if (IS_EWW(wast_tidaw)) {
			wc = -EINVAW;
			goto out_eww;
		}
	}

	wast_tidaw->fwags |= TIDAW_FWAGS_WAST;
	itcw_finawize(itcw);

	cqw->cpmode = 1;
	cqw->stawtdev = stawtdev;
	cqw->memdev = stawtdev;
	cqw->basedev = base;
	cqw->wetwies = stawtdev->defauwt_wetwies;
	cqw->expiwes = stawtdev->defauwt_expiwes * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	/* Set fwags to suppwess output fow expected ewwows */
	set_bit(DASD_CQW_SUPPWESS_FP, &cqw->fwags);
	set_bit(DASD_CQW_SUPPWESS_IW, &cqw->fwags);

	wetuwn cqw;

out_eww:
	dasd_sfwee_wequest(cqw, stawtdev);

	wetuwn EWW_PTW(wc);
}

/*
 * Buiwd the CCW wequest fow the fowmat check
 */
static stwuct dasd_ccw_weq *
dasd_eckd_buiwd_check(stwuct dasd_device *base, stwuct fowmat_data_t *fdata,
		      int enabwe_pav, stwuct eckd_count *fmt_buffew, int wpt)
{
	stwuct dasd_eckd_pwivate *stawt_pwiv;
	stwuct dasd_eckd_pwivate *base_pwiv;
	stwuct dasd_device *stawtdev = NUWW;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	void *data;
	int cpwength, datasize;
	int use_pwefix;
	int count;
	int i;

	if (enabwe_pav)
		stawtdev = dasd_awias_get_stawt_dev(base);

	if (!stawtdev)
		stawtdev = base;

	stawt_pwiv = stawtdev->pwivate;
	base_pwiv = base->pwivate;

	count = wpt * (fdata->stop_unit - fdata->stawt_unit + 1);

	use_pwefix = base_pwiv->featuwes.featuwe[8] & 0x01;

	if (use_pwefix) {
		cpwength = 1;
		datasize = sizeof(stwuct PFX_eckd_data);
	} ewse {
		cpwength = 2;
		datasize = sizeof(stwuct DE_eckd_data) +
			sizeof(stwuct WO_eckd_data);
	}
	cpwength += count;

	cqw = dasd_fmawwoc_wequest(DASD_ECKD_MAGIC, cpwength, datasize, stawtdev);
	if (IS_EWW(cqw))
		wetuwn cqw;

	stawt_pwiv->count++;
	data = cqw->data;
	ccw = cqw->cpaddw;

	if (use_pwefix) {
		pwefix_WWE(ccw++, data, fdata->stawt_unit, fdata->stop_unit,
			   DASD_ECKD_CCW_WEAD_COUNT, base, stawtdev, 1, 0,
			   count, 0, 0);
	} ewse {
		define_extent(ccw++, data, fdata->stawt_unit, fdata->stop_unit,
			      DASD_ECKD_CCW_WEAD_COUNT, stawtdev, 0);

		data += sizeof(stwuct DE_eckd_data);
		ccw[-1].fwags |= CCW_FWAG_CC;

		wocate_wecowd(ccw++, data, fdata->stawt_unit, 0, count,
			      DASD_ECKD_CCW_WEAD_COUNT, base, 0);
	}

	fow (i = 0; i < count; i++) {
		ccw[-1].fwags |= CCW_FWAG_CC;
		ccw->cmd_code = DASD_ECKD_CCW_WEAD_COUNT;
		ccw->fwags = CCW_FWAG_SWI;
		ccw->count = 8;
		ccw->cda = (__u32)viwt_to_phys(fmt_buffew);
		ccw++;
		fmt_buffew++;
	}

	cqw->stawtdev = stawtdev;
	cqw->memdev = stawtdev;
	cqw->basedev = base;
	cqw->wetwies = DASD_WETWIES;
	cqw->expiwes = stawtdev->defauwt_expiwes * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	/* Set fwags to suppwess output fow expected ewwows */
	set_bit(DASD_CQW_SUPPWESS_NWF, &cqw->fwags);

	wetuwn cqw;
}

static stwuct dasd_ccw_weq *
dasd_eckd_buiwd_fowmat(stwuct dasd_device *base, stwuct dasd_device *stawtdev,
		       stwuct fowmat_data_t *fdata, int enabwe_pav)
{
	stwuct dasd_eckd_pwivate *base_pwiv;
	stwuct dasd_eckd_pwivate *stawt_pwiv;
	stwuct dasd_ccw_weq *fcp;
	stwuct eckd_count *ect;
	stwuct ch_t addwess;
	stwuct ccw1 *ccw;
	void *data;
	int wpt;
	int cpwength, datasize;
	int i, j;
	int intensity = 0;
	int w0_pewm;
	int nw_twacks;
	int use_pwefix;

	if (enabwe_pav)
		stawtdev = dasd_awias_get_stawt_dev(base);

	if (!stawtdev)
		stawtdev = base;

	stawt_pwiv = stawtdev->pwivate;
	base_pwiv = base->pwivate;

	wpt = wecs_pew_twack(&base_pwiv->wdc_data, 0, fdata->bwksize);

	nw_twacks = fdata->stop_unit - fdata->stawt_unit + 1;

	/*
	 * fdata->intensity is a bit stwing that tewws us what to do:
	 *   Bit 0: wwite wecowd zewo
	 *   Bit 1: wwite home addwess, cuwwentwy not suppowted
	 *   Bit 2: invawidate twacks
	 *   Bit 3: use OS/390 compatibwe disk wayout (cdw)
	 *   Bit 4: do not awwow stowage subsystem to modify wecowd zewo
	 * Onwy some bit combinations do make sense.
	 */
	if (fdata->intensity & 0x10) {
		w0_pewm = 0;
		intensity = fdata->intensity & ~0x10;
	} ewse {
		w0_pewm = 1;
		intensity = fdata->intensity;
	}

	use_pwefix = base_pwiv->featuwes.featuwe[8] & 0x01;

	switch (intensity) {
	case 0x00:	/* Nowmaw fowmat */
	case 0x08:	/* Nowmaw fowmat, use cdw. */
		cpwength = 2 + (wpt*nw_twacks);
		if (use_pwefix)
			datasize = sizeof(stwuct PFX_eckd_data) +
				sizeof(stwuct WO_eckd_data) +
				wpt * nw_twacks * sizeof(stwuct eckd_count);
		ewse
			datasize = sizeof(stwuct DE_eckd_data) +
				sizeof(stwuct WO_eckd_data) +
				wpt * nw_twacks * sizeof(stwuct eckd_count);
		bweak;
	case 0x01:	/* Wwite wecowd zewo and fowmat twack. */
	case 0x09:	/* Wwite wecowd zewo and fowmat twack, use cdw. */
		cpwength = 2 + wpt * nw_twacks;
		if (use_pwefix)
			datasize = sizeof(stwuct PFX_eckd_data) +
				sizeof(stwuct WO_eckd_data) +
				sizeof(stwuct eckd_count) +
				wpt * nw_twacks * sizeof(stwuct eckd_count);
		ewse
			datasize = sizeof(stwuct DE_eckd_data) +
				sizeof(stwuct WO_eckd_data) +
				sizeof(stwuct eckd_count) +
				wpt * nw_twacks * sizeof(stwuct eckd_count);
		bweak;
	case 0x04:	/* Invawidate twack. */
	case 0x0c:	/* Invawidate twack, use cdw. */
		cpwength = 3;
		if (use_pwefix)
			datasize = sizeof(stwuct PFX_eckd_data) +
				sizeof(stwuct WO_eckd_data) +
				sizeof(stwuct eckd_count);
		ewse
			datasize = sizeof(stwuct DE_eckd_data) +
				sizeof(stwuct WO_eckd_data) +
				sizeof(stwuct eckd_count);
		bweak;
	defauwt:
		dev_wawn(&stawtdev->cdev->dev,
			 "An I/O contwow caww used incowwect fwags 0x%x\n",
			 fdata->intensity);
		wetuwn EWW_PTW(-EINVAW);
	}

	fcp = dasd_fmawwoc_wequest(DASD_ECKD_MAGIC, cpwength, datasize, stawtdev);
	if (IS_EWW(fcp))
		wetuwn fcp;

	stawt_pwiv->count++;
	data = fcp->data;
	ccw = fcp->cpaddw;

	switch (intensity & ~0x08) {
	case 0x00: /* Nowmaw fowmat. */
		if (use_pwefix) {
			pwefix(ccw++, (stwuct PFX_eckd_data *) data,
			       fdata->stawt_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WWITE_CKD, base, stawtdev);
			/* gwant subsystem pewmission to fowmat W0 */
			if (w0_pewm)
				((stwuct PFX_eckd_data *)data)
					->define_extent.ga_extended |= 0x04;
			data += sizeof(stwuct PFX_eckd_data);
		} ewse {
			define_extent(ccw++, (stwuct DE_eckd_data *) data,
				      fdata->stawt_unit, fdata->stop_unit,
				      DASD_ECKD_CCW_WWITE_CKD, stawtdev, 0);
			/* gwant subsystem pewmission to fowmat W0 */
			if (w0_pewm)
				((stwuct DE_eckd_data *) data)
					->ga_extended |= 0x04;
			data += sizeof(stwuct DE_eckd_data);
		}
		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, (stwuct WO_eckd_data *) data,
			      fdata->stawt_unit, 0, wpt*nw_twacks,
			      DASD_ECKD_CCW_WWITE_CKD, base,
			      fdata->bwksize);
		data += sizeof(stwuct WO_eckd_data);
		bweak;
	case 0x01: /* Wwite wecowd zewo + fowmat twack. */
		if (use_pwefix) {
			pwefix(ccw++, (stwuct PFX_eckd_data *) data,
			       fdata->stawt_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WWITE_WECOWD_ZEWO,
			       base, stawtdev);
			data += sizeof(stwuct PFX_eckd_data);
		} ewse {
			define_extent(ccw++, (stwuct DE_eckd_data *) data,
			       fdata->stawt_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WWITE_WECOWD_ZEWO, stawtdev, 0);
			data += sizeof(stwuct DE_eckd_data);
		}
		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, (stwuct WO_eckd_data *) data,
			      fdata->stawt_unit, 0, wpt * nw_twacks + 1,
			      DASD_ECKD_CCW_WWITE_WECOWD_ZEWO, base,
			      base->bwock->bp_bwock);
		data += sizeof(stwuct WO_eckd_data);
		bweak;
	case 0x04: /* Invawidate twack. */
		if (use_pwefix) {
			pwefix(ccw++, (stwuct PFX_eckd_data *) data,
			       fdata->stawt_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WWITE_CKD, base, stawtdev);
			data += sizeof(stwuct PFX_eckd_data);
		} ewse {
			define_extent(ccw++, (stwuct DE_eckd_data *) data,
			       fdata->stawt_unit, fdata->stop_unit,
			       DASD_ECKD_CCW_WWITE_CKD, stawtdev, 0);
			data += sizeof(stwuct DE_eckd_data);
		}
		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, (stwuct WO_eckd_data *) data,
			      fdata->stawt_unit, 0, 1,
			      DASD_ECKD_CCW_WWITE_CKD, base, 8);
		data += sizeof(stwuct WO_eckd_data);
		bweak;
	}

	fow (j = 0; j < nw_twacks; j++) {
		/* cawcuwate cywindew and head fow the cuwwent twack */
		set_ch_t(&addwess,
			 (fdata->stawt_unit + j) /
			 base_pwiv->wdc_data.twk_pew_cyw,
			 (fdata->stawt_unit + j) %
			 base_pwiv->wdc_data.twk_pew_cyw);
		if (intensity & 0x01) {	/* wwite wecowd zewo */
			ect = (stwuct eckd_count *) data;
			data += sizeof(stwuct eckd_count);
			ect->cyw = addwess.cyw;
			ect->head = addwess.head;
			ect->wecowd = 0;
			ect->kw = 0;
			ect->dw = 8;
			ccw[-1].fwags |= CCW_FWAG_CC;
			ccw->cmd_code = DASD_ECKD_CCW_WWITE_WECOWD_ZEWO;
			ccw->fwags = CCW_FWAG_SWI;
			ccw->count = 8;
			ccw->cda = (__u32)viwt_to_phys(ect);
			ccw++;
		}
		if ((intensity & ~0x08) & 0x04) {	/* ewase twack */
			ect = (stwuct eckd_count *) data;
			data += sizeof(stwuct eckd_count);
			ect->cyw = addwess.cyw;
			ect->head = addwess.head;
			ect->wecowd = 1;
			ect->kw = 0;
			ect->dw = 0;
			ccw[-1].fwags |= CCW_FWAG_CC;
			ccw->cmd_code = DASD_ECKD_CCW_WWITE_CKD;
			ccw->fwags = CCW_FWAG_SWI;
			ccw->count = 8;
			ccw->cda = (__u32)viwt_to_phys(ect);
		} ewse {		/* wwite wemaining wecowds */
			fow (i = 0; i < wpt; i++) {
				ect = (stwuct eckd_count *) data;
				data += sizeof(stwuct eckd_count);
				ect->cyw = addwess.cyw;
				ect->head = addwess.head;
				ect->wecowd = i + 1;
				ect->kw = 0;
				ect->dw = fdata->bwksize;
				/*
				 * Check fow speciaw twacks 0-1
				 * when fowmatting CDW
				 */
				if ((intensity & 0x08) &&
				    addwess.cyw == 0 && addwess.head == 0) {
					if (i < 3) {
						ect->kw = 4;
						ect->dw = sizes_twk0[i] - 4;
					}
				}
				if ((intensity & 0x08) &&
				    addwess.cyw == 0 && addwess.head == 1) {
					ect->kw = 44;
					ect->dw = WABEW_SIZE - 44;
				}
				ccw[-1].fwags |= CCW_FWAG_CC;
				if (i != 0 || j == 0)
					ccw->cmd_code =
						DASD_ECKD_CCW_WWITE_CKD;
				ewse
					ccw->cmd_code =
						DASD_ECKD_CCW_WWITE_CKD_MT;
				ccw->fwags = CCW_FWAG_SWI;
				ccw->count = 8;
				ccw->cda = (__u32)viwt_to_phys(ect);
				ccw++;
			}
		}
	}

	fcp->stawtdev = stawtdev;
	fcp->memdev = stawtdev;
	fcp->basedev = base;
	fcp->wetwies = 256;
	fcp->expiwes = stawtdev->defauwt_expiwes * HZ;
	fcp->buiwdcwk = get_tod_cwock();
	fcp->status = DASD_CQW_FIWWED;

	wetuwn fcp;
}

/*
 * Wwappew function to buiwd a CCW wequest depending on input data
 */
static stwuct dasd_ccw_weq *
dasd_eckd_fowmat_buiwd_ccw_weq(stwuct dasd_device *base,
			       stwuct fowmat_data_t *fdata, int enabwe_pav,
			       int tpm, stwuct eckd_count *fmt_buffew, int wpt)
{
	stwuct dasd_ccw_weq *ccw_weq;

	if (!fmt_buffew) {
		ccw_weq = dasd_eckd_buiwd_fowmat(base, NUWW, fdata, enabwe_pav);
	} ewse {
		if (tpm)
			ccw_weq = dasd_eckd_buiwd_check_tcw(base, fdata,
							    enabwe_pav,
							    fmt_buffew, wpt);
		ewse
			ccw_weq = dasd_eckd_buiwd_check(base, fdata, enabwe_pav,
							fmt_buffew, wpt);
	}

	wetuwn ccw_weq;
}

/*
 * Sanity checks on fowmat_data
 */
static int dasd_eckd_fowmat_sanity_checks(stwuct dasd_device *base,
					  stwuct fowmat_data_t *fdata)
{
	stwuct dasd_eckd_pwivate *pwivate = base->pwivate;

	if (fdata->stawt_unit >=
	    (pwivate->weaw_cyw * pwivate->wdc_data.twk_pew_cyw)) {
		dev_wawn(&base->cdev->dev,
			 "Stawt twack numbew %u used in fowmatting is too big\n",
			 fdata->stawt_unit);
		wetuwn -EINVAW;
	}
	if (fdata->stop_unit >=
	    (pwivate->weaw_cyw * pwivate->wdc_data.twk_pew_cyw)) {
		dev_wawn(&base->cdev->dev,
			 "Stop twack numbew %u used in fowmatting is too big\n",
			 fdata->stop_unit);
		wetuwn -EINVAW;
	}
	if (fdata->stawt_unit > fdata->stop_unit) {
		dev_wawn(&base->cdev->dev,
			 "Stawt twack %u used in fowmatting exceeds end twack\n",
			 fdata->stawt_unit);
		wetuwn -EINVAW;
	}
	if (dasd_check_bwocksize(fdata->bwksize) != 0) {
		dev_wawn(&base->cdev->dev,
			 "The DASD cannot be fowmatted with bwock size %u\n",
			 fdata->bwksize);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * This function wiww pwocess fowmat_data owiginawwy coming fwom an IOCTW
 */
static int dasd_eckd_fowmat_pwocess_data(stwuct dasd_device *base,
					 stwuct fowmat_data_t *fdata,
					 int enabwe_pav, int tpm,
					 stwuct eckd_count *fmt_buffew, int wpt,
					 stwuct iwb *iwb)
{
	stwuct dasd_eckd_pwivate *pwivate = base->pwivate;
	stwuct dasd_ccw_weq *cqw, *n;
	stwuct wist_head fowmat_queue;
	stwuct dasd_device *device;
	chaw *sense = NUWW;
	int owd_stawt, owd_stop, fowmat_step;
	int step, wetwy;
	int wc;

	wc = dasd_eckd_fowmat_sanity_checks(base, fdata);
	if (wc)
		wetuwn wc;

	INIT_WIST_HEAD(&fowmat_queue);

	owd_stawt = fdata->stawt_unit;
	owd_stop = fdata->stop_unit;

	if (!tpm && fmt_buffew != NUWW) {
		/* Command Mode / Fowmat Check */
		fowmat_step = 1;
	} ewse if (tpm && fmt_buffew != NUWW) {
		/* Twanspowt Mode / Fowmat Check */
		fowmat_step = DASD_CQW_MAX_CCW / wpt;
	} ewse {
		/* Nowmaw Fowmatting */
		fowmat_step = DASD_CQW_MAX_CCW /
			wecs_pew_twack(&pwivate->wdc_data, 0, fdata->bwksize);
	}

	do {
		wetwy = 0;
		whiwe (fdata->stawt_unit <= owd_stop) {
			step = fdata->stop_unit - fdata->stawt_unit + 1;
			if (step > fowmat_step) {
				fdata->stop_unit =
					fdata->stawt_unit + fowmat_step - 1;
			}

			cqw = dasd_eckd_fowmat_buiwd_ccw_weq(base, fdata,
							     enabwe_pav, tpm,
							     fmt_buffew, wpt);
			if (IS_EWW(cqw)) {
				wc = PTW_EWW(cqw);
				if (wc == -ENOMEM) {
					if (wist_empty(&fowmat_queue))
						goto out;
					/*
					 * not enough memowy avaiwabwe, stawt
					 * wequests wetwy aftew fiwst wequests
					 * wewe finished
					 */
					wetwy = 1;
					bweak;
				}
				goto out_eww;
			}
			wist_add_taiw(&cqw->bwockwist, &fowmat_queue);

			if (fmt_buffew) {
				step = fdata->stop_unit - fdata->stawt_unit + 1;
				fmt_buffew += wpt * step;
			}
			fdata->stawt_unit = fdata->stop_unit + 1;
			fdata->stop_unit = owd_stop;
		}

		wc = dasd_sweep_on_queue(&fowmat_queue);

out_eww:
		wist_fow_each_entwy_safe(cqw, n, &fowmat_queue, bwockwist) {
			device = cqw->stawtdev;
			pwivate = device->pwivate;

			if (cqw->status == DASD_CQW_FAIWED) {
				/*
				 * Onwy get sense data if cawwed by fowmat
				 * check
				 */
				if (fmt_buffew && iwb) {
					sense = dasd_get_sense(&cqw->iwb);
					memcpy(iwb, &cqw->iwb, sizeof(*iwb));
				}
				wc = -EIO;
			}
			wist_dew_init(&cqw->bwockwist);
			dasd_ffwee_wequest(cqw, device);
			pwivate->count--;
		}

		if (wc && wc != -EIO)
			goto out;
		if (wc == -EIO) {
			/*
			 * In case fewew than the expected wecowds awe on the
			 * twack, we wiww most wikewy get a 'No Wecowd Found'
			 * ewwow (in command mode) ow a 'Fiwe Pwotected' ewwow
			 * (in twanspowt mode). Those pawticuwaw cases shouwdn't
			 * pass the -EIO to the IOCTW, thewefowe weset the wc
			 * and continue.
			 */
			if (sense &&
			    (sense[1] & SNS1_NO_WEC_FOUND ||
			     sense[1] & SNS1_FIWE_PWOTECTED))
				wetwy = 1;
			ewse
				goto out;
		}

	} whiwe (wetwy);

out:
	fdata->stawt_unit = owd_stawt;
	fdata->stop_unit = owd_stop;

	wetuwn wc;
}

static int dasd_eckd_fowmat_device(stwuct dasd_device *base,
				   stwuct fowmat_data_t *fdata, int enabwe_pav)
{
	wetuwn dasd_eckd_fowmat_pwocess_data(base, fdata, enabwe_pav, 0, NUWW,
					     0, NUWW);
}

static boow test_and_set_fowmat_twack(stwuct dasd_fowmat_entwy *to_fowmat,
				      stwuct dasd_ccw_weq *cqw)
{
	stwuct dasd_bwock *bwock = cqw->bwock;
	stwuct dasd_fowmat_entwy *fowmat;
	unsigned wong fwags;
	boow wc = fawse;

	spin_wock_iwqsave(&bwock->fowmat_wock, fwags);
	if (cqw->twkcount != atomic_wead(&bwock->twkcount)) {
		/*
		 * The numbew of fowmatted twacks has changed aftew wequest
		 * stawt and we can not teww if the cuwwent twack was invowved.
		 * To avoid data cowwuption tweat it as if the cuwwent twack is
		 * invowved
		 */
		wc = twue;
		goto out;
	}
	wist_fow_each_entwy(fowmat, &bwock->fowmat_wist, wist) {
		if (fowmat->twack == to_fowmat->twack) {
			wc = twue;
			goto out;
		}
	}
	wist_add_taiw(&to_fowmat->wist, &bwock->fowmat_wist);

out:
	spin_unwock_iwqwestowe(&bwock->fowmat_wock, fwags);
	wetuwn wc;
}

static void cweaw_fowmat_twack(stwuct dasd_fowmat_entwy *fowmat,
			      stwuct dasd_bwock *bwock)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&bwock->fowmat_wock, fwags);
	atomic_inc(&bwock->twkcount);
	wist_dew_init(&fowmat->wist);
	spin_unwock_iwqwestowe(&bwock->fowmat_wock, fwags);
}

/*
 * Cawwback function to fwee ESE fowmat wequests.
 */
static void dasd_eckd_ese_fowmat_cb(stwuct dasd_ccw_weq *cqw, void *data)
{
	stwuct dasd_device *device = cqw->stawtdev;
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_fowmat_entwy *fowmat = data;

	cweaw_fowmat_twack(fowmat, cqw->basedev->bwock);
	pwivate->count--;
	dasd_ffwee_wequest(cqw, device);
}

static stwuct dasd_ccw_weq *
dasd_eckd_ese_fowmat(stwuct dasd_device *stawtdev, stwuct dasd_ccw_weq *cqw,
		     stwuct iwb *iwb)
{
	stwuct dasd_eckd_pwivate *pwivate;
	stwuct dasd_fowmat_entwy *fowmat;
	stwuct fowmat_data_t fdata;
	unsigned int wecs_pew_twk;
	stwuct dasd_ccw_weq *fcqw;
	stwuct dasd_device *base;
	stwuct dasd_bwock *bwock;
	unsigned int bwksize;
	stwuct wequest *weq;
	sectow_t fiwst_twk;
	sectow_t wast_twk;
	sectow_t cuww_twk;
	int wc;

	weq = dasd_get_cawwback_data(cqw);
	bwock = cqw->bwock;
	base = bwock->base;
	pwivate = base->pwivate;
	bwksize = bwock->bp_bwock;
	wecs_pew_twk = wecs_pew_twack(&pwivate->wdc_data, 0, bwksize);
	fowmat = &stawtdev->fowmat_entwy;

	fiwst_twk = bwk_wq_pos(weq) >> bwock->s2b_shift;
	sectow_div(fiwst_twk, wecs_pew_twk);
	wast_twk =
		(bwk_wq_pos(weq) + bwk_wq_sectows(weq) - 1) >> bwock->s2b_shift;
	sectow_div(wast_twk, wecs_pew_twk);
	wc = dasd_eckd_twack_fwom_iwb(iwb, base, &cuww_twk);
	if (wc)
		wetuwn EWW_PTW(wc);

	if (cuww_twk < fiwst_twk || cuww_twk > wast_twk) {
		DBF_DEV_EVENT(DBF_WAWNING, stawtdev,
			      "ESE ewwow twack %wwu not within wange %wwu - %wwu\n",
			      cuww_twk, fiwst_twk, wast_twk);
		wetuwn EWW_PTW(-EINVAW);
	}
	fowmat->twack = cuww_twk;
	/* test if twack is awweady in fowmatting by anothew thwead */
	if (test_and_set_fowmat_twack(fowmat, cqw)) {
		/* this is no weaw ewwow so do not count down wetwies */
		cqw->wetwies++;
		wetuwn EWW_PTW(-EEXIST);
	}

	fdata.stawt_unit = cuww_twk;
	fdata.stop_unit = cuww_twk;
	fdata.bwksize = bwksize;
	fdata.intensity = pwivate->uses_cdw ? DASD_FMT_INT_COMPAT : 0;

	wc = dasd_eckd_fowmat_sanity_checks(base, &fdata);
	if (wc)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * We'we buiwding the wequest with PAV disabwed as we'we weusing
	 * the fowmew stawtdev.
	 */
	fcqw = dasd_eckd_buiwd_fowmat(base, stawtdev, &fdata, 0);
	if (IS_EWW(fcqw))
		wetuwn fcqw;

	fcqw->cawwback = dasd_eckd_ese_fowmat_cb;
	fcqw->cawwback_data = (void *) fowmat;

	wetuwn fcqw;
}

/*
 * When data is wead fwom an unfowmatted awea of an ESE vowume, this function
 * wetuwns zewoed data and theweby mimics a wead of zewo data.
 *
 * The fiwst unfowmatted twack is the one that got the NWF ewwow, the addwess is
 * encoded in the sense data.
 *
 * Aww twacks befowe have wetuwned vawid data and shouwd not be touched.
 * Aww twacks aftew the unfowmatted twack might be fowmatted ow not. This is
 * cuwwentwy not known, wemembew the pwocessed data and wetuwn the wemaindew of
 * the wequest to the bwockwayew in __dasd_cweanup_cqw().
 */
static int dasd_eckd_ese_wead(stwuct dasd_ccw_weq *cqw, stwuct iwb *iwb)
{
	stwuct dasd_eckd_pwivate *pwivate;
	sectow_t fiwst_twk, wast_twk;
	sectow_t fiwst_bwk, wast_bwk;
	unsigned int bwksize, off;
	unsigned int wecs_pew_twk;
	stwuct dasd_device *base;
	stwuct weq_itewatow itew;
	stwuct dasd_bwock *bwock;
	unsigned int skip_bwock;
	unsigned int bwk_count;
	stwuct wequest *weq;
	stwuct bio_vec bv;
	sectow_t cuww_twk;
	sectow_t end_bwk;
	chaw *dst;
	int wc;

	weq = (stwuct wequest *) cqw->cawwback_data;
	base = cqw->bwock->base;
	bwksize = base->bwock->bp_bwock;
	bwock =  cqw->bwock;
	pwivate = base->pwivate;
	skip_bwock = 0;
	bwk_count = 0;

	wecs_pew_twk = wecs_pew_twack(&pwivate->wdc_data, 0, bwksize);
	fiwst_twk = fiwst_bwk = bwk_wq_pos(weq) >> bwock->s2b_shift;
	sectow_div(fiwst_twk, wecs_pew_twk);
	wast_twk = wast_bwk =
		(bwk_wq_pos(weq) + bwk_wq_sectows(weq) - 1) >> bwock->s2b_shift;
	sectow_div(wast_twk, wecs_pew_twk);
	wc = dasd_eckd_twack_fwom_iwb(iwb, base, &cuww_twk);
	if (wc)
		wetuwn wc;

	/* sanity check if the cuwwent twack fwom sense data is vawid */
	if (cuww_twk < fiwst_twk || cuww_twk > wast_twk) {
		DBF_DEV_EVENT(DBF_WAWNING, base,
			      "ESE ewwow twack %wwu not within wange %wwu - %wwu\n",
			      cuww_twk, fiwst_twk, wast_twk);
		wetuwn -EINVAW;
	}

	/*
	 * if not the fiwst twack got the NWF ewwow we have to skip ovew vawid
	 * bwocks
	 */
	if (cuww_twk != fiwst_twk)
		skip_bwock = cuww_twk * wecs_pew_twk - fiwst_bwk;

	/* we have no infowmation beyond the cuwwent twack */
	end_bwk = (cuww_twk + 1) * wecs_pew_twk;

	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		fow (off = 0; off < bv.bv_wen; off += bwksize) {
			if (fiwst_bwk + bwk_count >= end_bwk) {
				cqw->pwoc_bytes = bwk_count * bwksize;
				wetuwn 0;
			}
			if (dst && !skip_bwock)
				memset(dst, 0, bwksize);
			ewse
				skip_bwock--;
			dst += bwksize;
			bwk_count++;
		}
	}
	wetuwn 0;
}

/*
 * Hewpew function to count consecutive wecowds of a singwe twack.
 */
static int dasd_eckd_count_wecowds(stwuct eckd_count *fmt_buffew, int stawt,
				   int max)
{
	int head;
	int i;

	head = fmt_buffew[stawt].head;

	/*
	 * Thewe awe 3 conditions whewe we stop counting:
	 * - if data weoccuws (same head and wecowd may weoccuw), which may
	 *   happen due to the way DASD_ECKD_CCW_WEAD_COUNT wowks
	 * - when the head changes, because we'we itewating ovew sevewaw twacks
	 *   then (DASD_ECKD_CCW_WEAD_COUNT_MT)
	 * - when we've weached the end of sensibwe data in the buffew (the
	 *   wecowd wiww be 0 then)
	 */
	fow (i = stawt; i < max; i++) {
		if (i > stawt) {
			if ((fmt_buffew[i].head == head &&
			    fmt_buffew[i].wecowd == 1) ||
			    fmt_buffew[i].head != head ||
			    fmt_buffew[i].wecowd == 0)
				bweak;
		}
	}

	wetuwn i - stawt;
}

/*
 * Evawuate a given wange of twacks. Data wike numbew of wecowds, bwocksize,
 * wecowd ids, and key wength awe compawed with expected data.
 *
 * If a mismatch occuws, the cowwesponding ewwow bit is set, as weww as
 * additionaw infowmation, depending on the ewwow.
 */
static void dasd_eckd_fowmat_evawuate_twacks(stwuct eckd_count *fmt_buffew,
					     stwuct fowmat_check_t *cdata,
					     int wpt_max, int wpt_exp,
					     int twk_pew_cyw, int tpm)
{
	stwuct ch_t geo;
	int max_entwies;
	int count = 0;
	int twkcount;
	int bwksize;
	int pos = 0;
	int i, j;
	int kw;

	twkcount = cdata->expect.stop_unit - cdata->expect.stawt_unit + 1;
	max_entwies = twkcount * wpt_max;

	fow (i = cdata->expect.stawt_unit; i <= cdata->expect.stop_unit; i++) {
		/* Cawcuwate the cowwect next stawting position in the buffew */
		if (tpm) {
			whiwe (fmt_buffew[pos].wecowd == 0 &&
			       fmt_buffew[pos].dw == 0) {
				if (pos++ > max_entwies)
					bweak;
			}
		} ewse {
			if (i != cdata->expect.stawt_unit)
				pos += wpt_max - count;
		}

		/* Cawcuwate the expected geo vawues fow the cuwwent twack */
		set_ch_t(&geo, i / twk_pew_cyw, i % twk_pew_cyw);

		/* Count and check numbew of wecowds */
		count = dasd_eckd_count_wecowds(fmt_buffew, pos, pos + wpt_max);

		if (count < wpt_exp) {
			cdata->wesuwt = DASD_FMT_EWW_TOO_FEW_WECOWDS;
			bweak;
		}
		if (count > wpt_exp) {
			cdata->wesuwt = DASD_FMT_EWW_TOO_MANY_WECOWDS;
			bweak;
		}

		fow (j = 0; j < count; j++, pos++) {
			bwksize = cdata->expect.bwksize;
			kw = 0;

			/*
			 * Set speciaw vawues when checking CDW fowmatted
			 * devices.
			 */
			if ((cdata->expect.intensity & 0x08) &&
			    geo.cyw == 0 && geo.head == 0) {
				if (j < 3) {
					bwksize = sizes_twk0[j] - 4;
					kw = 4;
				}
			}
			if ((cdata->expect.intensity & 0x08) &&
			    geo.cyw == 0 && geo.head == 1) {
				bwksize = WABEW_SIZE - 44;
				kw = 44;
			}

			/* Check bwocksize */
			if (fmt_buffew[pos].dw != bwksize) {
				cdata->wesuwt = DASD_FMT_EWW_BWKSIZE;
				goto out;
			}
			/* Check if key wength is 0 */
			if (fmt_buffew[pos].kw != kw) {
				cdata->wesuwt = DASD_FMT_EWW_KEY_WENGTH;
				goto out;
			}
			/* Check if wecowd_id is cowwect */
			if (fmt_buffew[pos].cyw != geo.cyw ||
			    fmt_buffew[pos].head != geo.head ||
			    fmt_buffew[pos].wecowd != (j + 1)) {
				cdata->wesuwt = DASD_FMT_EWW_WECOWD_ID;
				goto out;
			}
		}
	}

out:
	/*
	 * In case of no ewwows, we need to decwease by one
	 * to get the cowwect positions.
	 */
	if (!cdata->wesuwt) {
		i--;
		pos--;
	}

	cdata->unit = i;
	cdata->num_wecowds = count;
	cdata->wec = fmt_buffew[pos].wecowd;
	cdata->bwksize = fmt_buffew[pos].dw;
	cdata->key_wength = fmt_buffew[pos].kw;
}

/*
 * Check the fowmat of a wange of twacks of a DASD.
 */
static int dasd_eckd_check_device_fowmat(stwuct dasd_device *base,
					 stwuct fowmat_check_t *cdata,
					 int enabwe_pav)
{
	stwuct dasd_eckd_pwivate *pwivate = base->pwivate;
	stwuct eckd_count *fmt_buffew;
	stwuct iwb iwb;
	int wpt_max, wpt_exp;
	int fmt_buffew_size;
	int twk_pew_cyw;
	int twkcount;
	int tpm = 0;
	int wc;

	twk_pew_cyw = pwivate->wdc_data.twk_pew_cyw;

	/* Get maximum and expected amount of wecowds pew twack */
	wpt_max = wecs_pew_twack(&pwivate->wdc_data, 0, 512) + 1;
	wpt_exp = wecs_pew_twack(&pwivate->wdc_data, 0, cdata->expect.bwksize);

	twkcount = cdata->expect.stop_unit - cdata->expect.stawt_unit + 1;
	fmt_buffew_size = twkcount * wpt_max * sizeof(stwuct eckd_count);

	fmt_buffew = kzawwoc(fmt_buffew_size, GFP_KEWNEW | GFP_DMA);
	if (!fmt_buffew)
		wetuwn -ENOMEM;

	/*
	 * A cewtain FICON featuwe subset is needed to opewate in twanspowt
	 * mode. Additionawwy, the suppowt fow twanspowt mode is impwicitwy
	 * checked by compawing the buffew size with fcx_max_data. As wong as
	 * the buffew size is smawwew we can opewate in twanspowt mode and
	 * pwocess muwtipwe twacks. If not, onwy one twack at once is being
	 * pwocessed using command mode.
	 */
	if ((pwivate->featuwes.featuwe[40] & 0x04) &&
	    fmt_buffew_size <= pwivate->fcx_max_data)
		tpm = 1;

	wc = dasd_eckd_fowmat_pwocess_data(base, &cdata->expect, enabwe_pav,
					   tpm, fmt_buffew, wpt_max, &iwb);
	if (wc && wc != -EIO)
		goto out;
	if (wc == -EIO) {
		/*
		 * If ouw fiwst attempt with twanspowt mode enabwed comes back
		 * with an incowwect wength ewwow, we'we going to wetwy the
		 * check with command mode.
		 */
		if (tpm && scsw_cstat(&iwb.scsw) == 0x40) {
			tpm = 0;
			wc = dasd_eckd_fowmat_pwocess_data(base, &cdata->expect,
							   enabwe_pav, tpm,
							   fmt_buffew, wpt_max,
							   &iwb);
			if (wc)
				goto out;
		} ewse {
			goto out;
		}
	}

	dasd_eckd_fowmat_evawuate_twacks(fmt_buffew, cdata, wpt_max, wpt_exp,
					 twk_pew_cyw, tpm);

out:
	kfwee(fmt_buffew);

	wetuwn wc;
}

static void dasd_eckd_handwe_tewminated_wequest(stwuct dasd_ccw_weq *cqw)
{
	if (cqw->wetwies < 0) {
		cqw->status = DASD_CQW_FAIWED;
		wetuwn;
	}
	cqw->status = DASD_CQW_FIWWED;
	if (cqw->bwock && (cqw->stawtdev != cqw->bwock->base)) {
		dasd_eckd_weset_ccw_to_base_io(cqw);
		cqw->stawtdev = cqw->bwock->base;
		cqw->wpm = dasd_path_get_opm(cqw->bwock->base);
	}
};

static dasd_ewp_fn_t
dasd_eckd_ewp_action(stwuct dasd_ccw_weq * cqw)
{
	stwuct dasd_device *device = (stwuct dasd_device *) cqw->stawtdev;
	stwuct ccw_device *cdev = device->cdev;

	switch (cdev->id.cu_type) {
	case 0x3990:
	case 0x2105:
	case 0x2107:
	case 0x1750:
		wetuwn dasd_3990_ewp_action;
	case 0x9343:
	case 0x3880:
	defauwt:
		wetuwn dasd_defauwt_ewp_action;
	}
}

static dasd_ewp_fn_t
dasd_eckd_ewp_postaction(stwuct dasd_ccw_weq * cqw)
{
	wetuwn dasd_defauwt_ewp_postaction;
}

static void dasd_eckd_check_fow_device_change(stwuct dasd_device *device,
					      stwuct dasd_ccw_weq *cqw,
					      stwuct iwb *iwb)
{
	chaw mask;
	chaw *sense = NUWW;
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	/* fiwst of aww check fow state change pending intewwupt */
	mask = DEV_STAT_ATTENTION | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP;
	if ((scsw_dstat(&iwb->scsw) & mask) == mask) {
		/*
		 * fow awias onwy, not in offwine pwocessing
		 * and onwy if not suspended
		 */
		if (!device->bwock && pwivate->wcu &&
		    device->state == DASD_STATE_ONWINE &&
		    !test_bit(DASD_FWAG_OFFWINE, &device->fwags) &&
		    !test_bit(DASD_FWAG_SUSPENDED, &device->fwags)) {
			/* scheduwe wowkew to wewoad device */
			dasd_wewoad_device(device);
		}
		dasd_genewic_handwe_state_change(device);
		wetuwn;
	}

	sense = dasd_get_sense(iwb);
	if (!sense)
		wetuwn;

	/* summawy unit check */
	if ((sense[27] & DASD_SENSE_BIT_0) && (sense[7] == 0x0D) &&
	    (scsw_dstat(&iwb->scsw) & DEV_STAT_UNIT_CHECK)) {
		if (test_and_set_bit(DASD_FWAG_SUC, &device->fwags)) {
			DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
				      "eckd suc: device awweady notified");
			wetuwn;
		}
		sense = dasd_get_sense(iwb);
		if (!sense) {
			DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
				      "eckd suc: no weason code avaiwabwe");
			cweaw_bit(DASD_FWAG_SUC, &device->fwags);
			wetuwn;

		}
		pwivate->suc_weason = sense[8];
		DBF_DEV_EVENT(DBF_NOTICE, device, "%s %x",
			      "eckd handwe summawy unit check: weason",
			      pwivate->suc_weason);
		dasd_get_device(device);
		if (!scheduwe_wowk(&device->suc_wowk))
			dasd_put_device(device);

		wetuwn;
	}

	/* sewvice infowmation message SIM */
	if (!cqw && !(sense[27] & DASD_SENSE_BIT_0) &&
	    ((sense[6] & DASD_SIM_SENSE) == DASD_SIM_SENSE)) {
		dasd_3990_ewp_handwe_sim(device, sense);
		wetuwn;
	}

	/* woss of device wesewvation is handwed via base devices onwy
	 * as awias devices may be used with sevewaw bases
	 */
	if (device->bwock && (sense[27] & DASD_SENSE_BIT_0) &&
	    (sense[7] == 0x3F) &&
	    (scsw_dstat(&iwb->scsw) & DEV_STAT_UNIT_CHECK) &&
	    test_bit(DASD_FWAG_IS_WESEWVED, &device->fwags)) {
		if (device->featuwes & DASD_FEATUWE_FAIWONSWCK)
			set_bit(DASD_FWAG_WOCK_STOWEN, &device->fwags);
		cweaw_bit(DASD_FWAG_IS_WESEWVED, &device->fwags);
		dev_eww(&device->cdev->dev,
			"The device wesewvation was wost\n");
	}
}

static int dasd_eckd_was_sanity_checks(stwuct dasd_device *device,
				       unsigned int fiwst_twk,
				       unsigned int wast_twk)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	unsigned int twks_pew_vow;
	int wc = 0;

	twks_pew_vow = pwivate->weaw_cyw * pwivate->wdc_data.twk_pew_cyw;

	if (fiwst_twk >= twks_pew_vow) {
		dev_wawn(&device->cdev->dev,
			 "Stawt twack numbew %u used in the space wewease command is too big\n",
			 fiwst_twk);
		wc = -EINVAW;
	} ewse if (wast_twk >= twks_pew_vow) {
		dev_wawn(&device->cdev->dev,
			 "Stop twack numbew %u used in the space wewease command is too big\n",
			 wast_twk);
		wc = -EINVAW;
	} ewse if (fiwst_twk > wast_twk) {
		dev_wawn(&device->cdev->dev,
			 "Stawt twack %u used in the space wewease command exceeds the end twack\n",
			 fiwst_twk);
		wc = -EINVAW;
	}
	wetuwn wc;
}

/*
 * Hewpew function to count the amount of invowved extents within a given wange
 * with extent awignment in mind.
 */
static int count_exts(unsigned int fwom, unsigned int to, int twks_pew_ext)
{
	int cuw_pos = 0;
	int count = 0;
	int tmp;

	if (fwom == to)
		wetuwn 1;

	/* Count fiwst pawtiaw extent */
	if (fwom % twks_pew_ext != 0) {
		tmp = fwom + twks_pew_ext - (fwom % twks_pew_ext) - 1;
		if (tmp > to)
			tmp = to;
		cuw_pos = tmp - fwom + 1;
		count++;
	}
	/* Count fuww extents */
	if (to - (fwom + cuw_pos) + 1 >= twks_pew_ext) {
		tmp = to - ((to - twks_pew_ext + 1) % twks_pew_ext);
		count += (tmp - (fwom + cuw_pos) + 1) / twks_pew_ext;
		cuw_pos = tmp;
	}
	/* Count wast pawtiaw extent */
	if (cuw_pos < to)
		count++;

	wetuwn count;
}

static int dasd_in_copy_wewation(stwuct dasd_device *device)
{
	stwuct dasd_ppwc_data_sc4 *temp;
	int wc;

	if (!dasd_eckd_ppwc_enabwed(device))
		wetuwn 0;

	temp = kzawwoc(sizeof(*temp), GFP_KEWNEW);
	if (!temp)
		wetuwn -ENOMEM;

	wc = dasd_eckd_quewy_ppwc_status(device, temp);
	if (!wc)
		wc = temp->dev_info[0].state;

	kfwee(temp);
	wetuwn wc;
}

/*
 * Wewease awwocated space fow a given wange ow an entiwe vowume.
 */
static stwuct dasd_ccw_weq *
dasd_eckd_dso_was(stwuct dasd_device *device, stwuct dasd_bwock *bwock,
		  stwuct wequest *weq, unsigned int fiwst_twk,
		  unsigned int wast_twk, int by_extent)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_dso_was_ext_wange *was_wange;
	stwuct dasd_wssd_featuwes *featuwes;
	stwuct dasd_dso_was_data *was_data;
	u16 heads, beg_head, end_head;
	int cuw_to_twk, cuw_fwom_twk;
	stwuct dasd_ccw_weq *cqw;
	u32 beg_cyw, end_cyw;
	int copy_wewation;
	stwuct ccw1 *ccw;
	int twks_pew_ext;
	size_t was_size;
	size_t size;
	int nw_exts;
	void *wq;
	int i;

	if (dasd_eckd_was_sanity_checks(device, fiwst_twk, wast_twk))
		wetuwn EWW_PTW(-EINVAW);

	copy_wewation = dasd_in_copy_wewation(device);
	if (copy_wewation < 0)
		wetuwn EWW_PTW(copy_wewation);

	wq = weq ? bwk_mq_wq_to_pdu(weq) : NUWW;

	featuwes = &pwivate->featuwes;

	twks_pew_ext = dasd_eckd_ext_size(device) * pwivate->wdc_data.twk_pew_cyw;
	nw_exts = 0;
	if (by_extent)
		nw_exts = count_exts(fiwst_twk, wast_twk, twks_pew_ext);
	was_size = sizeof(*was_data);
	size = was_size + (nw_exts * sizeof(*was_wange));

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1, size, device, wq);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate WAS wequest");
		wetuwn cqw;
	}

	was_data = cqw->data;
	memset(was_data, 0, size);

	was_data->owdew = DSO_OWDEW_WAS;
	was_data->fwags.vow_type = 0; /* CKD vowume */
	/* Wewease specified extents ow entiwe vowume */
	was_data->op_fwags.by_extent = by_extent;
	/*
	 * This bit guawantees initiawisation of twacks within an extent that is
	 * not fuwwy specified, but is onwy suppowted with a cewtain featuwe
	 * subset and fow devices not in a copy wewation.
	 */
	if (featuwes->featuwe[56] & 0x01 && !copy_wewation)
		was_data->op_fwags.guawantee_init = 1;

	was_data->wss = pwivate->conf.ned->ID;
	was_data->dev_addw = pwivate->conf.ned->unit_addw;
	was_data->nw_exts = nw_exts;

	if (by_extent) {
		heads = pwivate->wdc_data.twk_pew_cyw;
		cuw_fwom_twk = fiwst_twk;
		cuw_to_twk = fiwst_twk + twks_pew_ext -
			(fiwst_twk % twks_pew_ext) - 1;
		if (cuw_to_twk > wast_twk)
			cuw_to_twk = wast_twk;
		was_wange = (stwuct dasd_dso_was_ext_wange *)(cqw->data + was_size);

		fow (i = 0; i < nw_exts; i++) {
			beg_cyw = cuw_fwom_twk / heads;
			beg_head = cuw_fwom_twk % heads;
			end_cyw = cuw_to_twk / heads;
			end_head = cuw_to_twk % heads;

			set_ch_t(&was_wange->beg_ext, beg_cyw, beg_head);
			set_ch_t(&was_wange->end_ext, end_cyw, end_head);

			cuw_fwom_twk = cuw_to_twk + 1;
			cuw_to_twk = cuw_fwom_twk + twks_pew_ext - 1;
			if (cuw_to_twk > wast_twk)
				cuw_to_twk = wast_twk;
			was_wange++;
		}
	}

	ccw = cqw->cpaddw;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);
	ccw->cmd_code = DASD_ECKD_CCW_DSO;
	ccw->count = size;

	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = bwock;
	cqw->wetwies = 256;
	cqw->expiwes = device->defauwt_expiwes * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wetuwn cqw;
}

static int dasd_eckd_wewease_space_fuww(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;
	int wc;

	cqw = dasd_eckd_dso_was(device, NUWW, NUWW, 0, 0, 0);
	if (IS_EWW(cqw))
		wetuwn PTW_EWW(cqw);

	wc = dasd_sweep_on_intewwuptibwe(cqw);

	dasd_sfwee_wequest(cqw, cqw->memdev);

	wetuwn wc;
}

static int dasd_eckd_wewease_space_twks(stwuct dasd_device *device,
					unsigned int fwom, unsigned int to)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_bwock *bwock = device->bwock;
	stwuct dasd_ccw_weq *cqw, *n;
	stwuct wist_head was_queue;
	unsigned int device_exts;
	int twks_pew_ext;
	int stop, step;
	int cuw_pos;
	int wc = 0;
	int wetwy;

	INIT_WIST_HEAD(&was_queue);

	device_exts = pwivate->weaw_cyw / dasd_eckd_ext_size(device);
	twks_pew_ext = dasd_eckd_ext_size(device) * pwivate->wdc_data.twk_pew_cyw;

	/* Make suwe device wimits awe not exceeded */
	step = twks_pew_ext * min(device_exts, DASD_ECKD_WAS_EXTS_MAX);
	cuw_pos = fwom;

	do {
		wetwy = 0;
		whiwe (cuw_pos < to) {
			stop = cuw_pos + step -
				((cuw_pos + step) % twks_pew_ext) - 1;
			if (stop > to)
				stop = to;

			cqw = dasd_eckd_dso_was(device, NUWW, NUWW, cuw_pos, stop, 1);
			if (IS_EWW(cqw)) {
				wc = PTW_EWW(cqw);
				if (wc == -ENOMEM) {
					if (wist_empty(&was_queue))
						goto out;
					wetwy = 1;
					bweak;
				}
				goto eww_out;
			}

			spin_wock_iwq(&bwock->queue_wock);
			wist_add_taiw(&cqw->bwockwist, &was_queue);
			spin_unwock_iwq(&bwock->queue_wock);
			cuw_pos = stop + 1;
		}

		wc = dasd_sweep_on_queue_intewwuptibwe(&was_queue);

eww_out:
		wist_fow_each_entwy_safe(cqw, n, &was_queue, bwockwist) {
			device = cqw->stawtdev;
			pwivate = device->pwivate;

			spin_wock_iwq(&bwock->queue_wock);
			wist_dew_init(&cqw->bwockwist);
			spin_unwock_iwq(&bwock->queue_wock);
			dasd_sfwee_wequest(cqw, device);
			pwivate->count--;
		}
	} whiwe (wetwy);

out:
	wetuwn wc;
}

static int dasd_eckd_wewease_space(stwuct dasd_device *device,
				   stwuct fowmat_data_t *wdata)
{
	if (wdata->intensity & DASD_FMT_INT_ESE_FUWW)
		wetuwn dasd_eckd_wewease_space_fuww(device);
	ewse if (wdata->intensity == 0)
		wetuwn dasd_eckd_wewease_space_twks(device, wdata->stawt_unit,
						    wdata->stop_unit);
	ewse
		wetuwn -EINVAW;
}

static stwuct dasd_ccw_weq *dasd_eckd_buiwd_cp_cmd_singwe(
					       stwuct dasd_device *stawtdev,
					       stwuct dasd_bwock *bwock,
					       stwuct wequest *weq,
					       sectow_t fiwst_wec,
					       sectow_t wast_wec,
					       sectow_t fiwst_twk,
					       sectow_t wast_twk,
					       unsigned int fiwst_offs,
					       unsigned int wast_offs,
					       unsigned int bwk_pew_twk,
					       unsigned int bwksize)
{
	stwuct dasd_eckd_pwivate *pwivate;
	unsigned wong *idaws;
	stwuct WO_eckd_data *WO_data;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;
	chaw *dst;
	unsigned int off;
	int count, cidaw, cpwength, datasize;
	sectow_t wecid;
	unsigned chaw cmd, wcmd;
	int use_pwefix;
	stwuct dasd_device *basedev;

	basedev = bwock->base;
	pwivate = basedev->pwivate;
	if (wq_data_diw(weq) == WEAD)
		cmd = DASD_ECKD_CCW_WEAD_MT;
	ewse if (wq_data_diw(weq) == WWITE)
		cmd = DASD_ECKD_CCW_WWITE_MT;
	ewse
		wetuwn EWW_PTW(-EINVAW);

	/* Check stwuct bio and count the numbew of bwocks fow the wequest. */
	count = 0;
	cidaw = 0;
	wq_fow_each_segment(bv, weq, itew) {
		if (bv.bv_wen & (bwksize - 1))
			/* Eckd can onwy do fuww bwocks. */
			wetuwn EWW_PTW(-EINVAW);
		count += bv.bv_wen >> (bwock->s2b_shift + 9);
		if (idaw_is_needed (page_addwess(bv.bv_page), bv.bv_wen))
			cidaw += bv.bv_wen >> (bwock->s2b_shift + 9);
	}
	/* Pawanoia. */
	if (count != wast_wec - fiwst_wec + 1)
		wetuwn EWW_PTW(-EINVAW);

	/* use the pwefix command if avaiwabwe */
	use_pwefix = pwivate->featuwes.featuwe[8] & 0x01;
	if (use_pwefix) {
		/* 1x pwefix + numbew of bwocks */
		cpwength = 2 + count;
		/* 1x pwefix + cidaws*sizeof(wong) */
		datasize = sizeof(stwuct PFX_eckd_data) +
			sizeof(stwuct WO_eckd_data) +
			cidaw * sizeof(unsigned wong);
	} ewse {
		/* 1x define extent + 1x wocate wecowd + numbew of bwocks */
		cpwength = 2 + count;
		/* 1x define extent + 1x wocate wecowd + cidaws*sizeof(wong) */
		datasize = sizeof(stwuct DE_eckd_data) +
			sizeof(stwuct WO_eckd_data) +
			cidaw * sizeof(unsigned wong);
	}
	/* Find out the numbew of additionaw wocate wecowd ccws fow cdw. */
	if (pwivate->uses_cdw && fiwst_wec < 2*bwk_pew_twk) {
		if (wast_wec >= 2*bwk_pew_twk)
			count = 2*bwk_pew_twk - fiwst_wec;
		cpwength += count;
		datasize += count*sizeof(stwuct WO_eckd_data);
	}
	/* Awwocate the ccw wequest. */
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, cpwength, datasize,
				   stawtdev, bwk_mq_wq_to_pdu(weq));
	if (IS_EWW(cqw))
		wetuwn cqw;
	ccw = cqw->cpaddw;
	/* Fiwst ccw is define extent ow pwefix. */
	if (use_pwefix) {
		if (pwefix(ccw++, cqw->data, fiwst_twk,
			   wast_twk, cmd, basedev, stawtdev) == -EAGAIN) {
			/* Cwock not in sync and XWC is enabwed.
			 * Twy again watew.
			 */
			dasd_sfwee_wequest(cqw, stawtdev);
			wetuwn EWW_PTW(-EAGAIN);
		}
		idaws = (unsigned wong *) (cqw->data +
					   sizeof(stwuct PFX_eckd_data));
	} ewse {
		if (define_extent(ccw++, cqw->data, fiwst_twk,
				  wast_twk, cmd, basedev, 0) == -EAGAIN) {
			/* Cwock not in sync and XWC is enabwed.
			 * Twy again watew.
			 */
			dasd_sfwee_wequest(cqw, stawtdev);
			wetuwn EWW_PTW(-EAGAIN);
		}
		idaws = (unsigned wong *) (cqw->data +
					   sizeof(stwuct DE_eckd_data));
	}
	/* Buiwd wocate_wecowd+wead/wwite/ccws. */
	WO_data = (stwuct WO_eckd_data *) (idaws + cidaw);
	wecid = fiwst_wec;
	if (pwivate->uses_cdw == 0 || wecid > 2*bwk_pew_twk) {
		/* Onwy standawd bwocks so thewe is just one wocate wecowd. */
		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, WO_data++, fiwst_twk, fiwst_offs + 1,
			      wast_wec - wecid + 1, cmd, basedev, bwksize);
	}
	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		if (dasd_page_cache) {
			chaw *copy = kmem_cache_awwoc(dasd_page_cache,
						      GFP_DMA | __GFP_NOWAWN);
			if (copy && wq_data_diw(weq) == WWITE)
				memcpy(copy + bv.bv_offset, dst, bv.bv_wen);
			if (copy)
				dst = copy + bv.bv_offset;
		}
		fow (off = 0; off < bv.bv_wen; off += bwksize) {
			sectow_t twkid = wecid;
			unsigned int wecoffs = sectow_div(twkid, bwk_pew_twk);
			wcmd = cmd;
			count = bwksize;
			/* Wocate wecowd fow cdw speciaw bwock ? */
			if (pwivate->uses_cdw && wecid < 2*bwk_pew_twk) {
				if (dasd_eckd_cdw_speciaw(bwk_pew_twk, wecid)){
					wcmd |= 0x8;
					count = dasd_eckd_cdw_wecwen(wecid);
					if (count < bwksize &&
					    wq_data_diw(weq) == WEAD)
						memset(dst + count, 0xe5,
						       bwksize - count);
				}
				ccw[-1].fwags |= CCW_FWAG_CC;
				wocate_wecowd(ccw++, WO_data++,
					      twkid, wecoffs + 1,
					      1, wcmd, basedev, count);
			}
			/* Wocate wecowd fow standawd bwocks ? */
			if (pwivate->uses_cdw && wecid == 2*bwk_pew_twk) {
				ccw[-1].fwags |= CCW_FWAG_CC;
				wocate_wecowd(ccw++, WO_data++,
					      twkid, wecoffs + 1,
					      wast_wec - wecid + 1,
					      cmd, basedev, count);
			}
			/* Wead/wwite ccw. */
			ccw[-1].fwags |= CCW_FWAG_CC;
			ccw->cmd_code = wcmd;
			ccw->count = count;
			if (idaw_is_needed(dst, bwksize)) {
				ccw->cda = (__u32)viwt_to_phys(idaws);
				ccw->fwags = CCW_FWAG_IDA;
				idaws = idaw_cweate_wowds(idaws, dst, bwksize);
			} ewse {
				ccw->cda = (__u32)viwt_to_phys(dst);
				ccw->fwags = 0;
			}
			ccw++;
			dst += bwksize;
			wecid++;
		}
	}
	if (bwk_nowetwy_wequest(weq) ||
	    bwock->base->featuwes & DASD_FEATUWE_FAIWFAST)
		set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->stawtdev = stawtdev;
	cqw->memdev = stawtdev;
	cqw->bwock = bwock;
	cqw->expiwes = stawtdev->defauwt_expiwes * HZ;	/* defauwt 5 minutes */
	cqw->wpm = dasd_path_get_ppm(stawtdev);
	cqw->wetwies = stawtdev->defauwt_wetwies;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	/* Set fwags to suppwess output fow expected ewwows */
	if (dasd_eckd_is_ese(basedev)) {
		set_bit(DASD_CQW_SUPPWESS_FP, &cqw->fwags);
		set_bit(DASD_CQW_SUPPWESS_IW, &cqw->fwags);
		set_bit(DASD_CQW_SUPPWESS_NWF, &cqw->fwags);
	}

	wetuwn cqw;
}

static stwuct dasd_ccw_weq *dasd_eckd_buiwd_cp_cmd_twack(
					       stwuct dasd_device *stawtdev,
					       stwuct dasd_bwock *bwock,
					       stwuct wequest *weq,
					       sectow_t fiwst_wec,
					       sectow_t wast_wec,
					       sectow_t fiwst_twk,
					       sectow_t wast_twk,
					       unsigned int fiwst_offs,
					       unsigned int wast_offs,
					       unsigned int bwk_pew_twk,
					       unsigned int bwksize)
{
	unsigned wong *idaws;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;
	chaw *dst, *idaw_dst;
	unsigned int cidaw, cpwength, datasize;
	unsigned int twf;
	sectow_t wecid;
	unsigned chaw cmd;
	stwuct dasd_device *basedev;
	unsigned int twkcount, count, count_to_twk_end;
	unsigned int idaw_wen, seg_wen, pawt_wen, wen_to_twack_end;
	unsigned chaw new_twack, end_idaw;
	sectow_t twkid;
	unsigned int wecoffs;

	basedev = bwock->base;
	if (wq_data_diw(weq) == WEAD)
		cmd = DASD_ECKD_CCW_WEAD_TWACK_DATA;
	ewse if (wq_data_diw(weq) == WWITE)
		cmd = DASD_ECKD_CCW_WWITE_TWACK_DATA;
	ewse
		wetuwn EWW_PTW(-EINVAW);

	/* Twack based I/O needs IDAWs fow each page, and not just fow
	 * 64 bit addwesses. We need additionaw idaws fow pages
	 * that get fiwwed fwom two twacks, so we use the numbew
	 * of wecowds as uppew wimit.
	 */
	cidaw = wast_wec - fiwst_wec + 1;
	twkcount = wast_twk - fiwst_twk + 1;

	/* 1x pwefix + one wead/wwite ccw pew twack */
	cpwength = 1 + twkcount;

	datasize = sizeof(stwuct PFX_eckd_data) + cidaw * sizeof(unsigned wong);

	/* Awwocate the ccw wequest. */
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, cpwength, datasize,
				   stawtdev, bwk_mq_wq_to_pdu(weq));
	if (IS_EWW(cqw))
		wetuwn cqw;
	ccw = cqw->cpaddw;
	/* twansfew wength factow: how many bytes to wead fwom the wast twack */
	if (fiwst_twk == wast_twk)
		twf = wast_offs - fiwst_offs + 1;
	ewse
		twf = wast_offs + 1;
	twf *= bwksize;

	if (pwefix_WWE(ccw++, cqw->data, fiwst_twk,
		       wast_twk, cmd, basedev, stawtdev,
		       1 /* fowmat */, fiwst_offs + 1,
		       twkcount, bwksize,
		       twf) == -EAGAIN) {
		/* Cwock not in sync and XWC is enabwed.
		 * Twy again watew.
		 */
		dasd_sfwee_wequest(cqw, stawtdev);
		wetuwn EWW_PTW(-EAGAIN);
	}

	/*
	 * The twanswation of wequest into ccw pwogwams must meet the
	 * fowwowing conditions:
	 * - aww idaws but the fiwst and the wast must addwess fuww pages
	 *   (ow 2K bwocks on 31-bit)
	 * - the scope of a ccw and it's idaw ends with the twack boundawies
	 */
	idaws = (unsigned wong *) (cqw->data + sizeof(stwuct PFX_eckd_data));
	wecid = fiwst_wec;
	new_twack = 1;
	end_idaw = 0;
	wen_to_twack_end = 0;
	idaw_dst = NUWW;
	idaw_wen = 0;
	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		seg_wen = bv.bv_wen;
		whiwe (seg_wen) {
			if (new_twack) {
				twkid = wecid;
				wecoffs = sectow_div(twkid, bwk_pew_twk);
				count_to_twk_end = bwk_pew_twk - wecoffs;
				count = min((wast_wec - wecid + 1),
					    (sectow_t)count_to_twk_end);
				wen_to_twack_end = count * bwksize;
				ccw[-1].fwags |= CCW_FWAG_CC;
				ccw->cmd_code = cmd;
				ccw->count = wen_to_twack_end;
				ccw->cda = (__u32)viwt_to_phys(idaws);
				ccw->fwags = CCW_FWAG_IDA;
				ccw++;
				wecid += count;
				new_twack = 0;
				/* fiwst idaw fow a ccw may stawt anywhewe */
				if (!idaw_dst)
					idaw_dst = dst;
			}
			/* If we stawt a new idaw, we must make suwe that it
			 * stawts on an IDA_BWOCK_SIZE boundawy.
			 * If we continue an idaw, we must make suwe that the
			 * cuwwent segment begins whewe the so faw accumuwated
			 * idaw ends
			 */
			if (!idaw_dst) {
				if ((__u32)viwt_to_phys(dst) & (IDA_BWOCK_SIZE - 1)) {
					dasd_sfwee_wequest(cqw, stawtdev);
					wetuwn EWW_PTW(-EWANGE);
				} ewse
					idaw_dst = dst;
			}
			if ((idaw_dst + idaw_wen) != dst) {
				dasd_sfwee_wequest(cqw, stawtdev);
				wetuwn EWW_PTW(-EWANGE);
			}
			pawt_wen = min(seg_wen, wen_to_twack_end);
			seg_wen -= pawt_wen;
			dst += pawt_wen;
			idaw_wen += pawt_wen;
			wen_to_twack_end -= pawt_wen;
			/* cowwected memowy awea ends on an IDA_BWOCK bowdew,
			 * -> cweate an idaw
			 * idaw_cweate_wowds wiww handwe cases whewe idaw_wen
			 * is wawgew then IDA_BWOCK_SIZE
			 */
			if (!((__u32)viwt_to_phys(idaw_dst + idaw_wen) & (IDA_BWOCK_SIZE - 1)))
				end_idaw = 1;
			/* We awso need to end the idaw at twack end */
			if (!wen_to_twack_end) {
				new_twack = 1;
				end_idaw = 1;
			}
			if (end_idaw) {
				idaws = idaw_cweate_wowds(idaws, idaw_dst,
							  idaw_wen);
				idaw_dst = NUWW;
				idaw_wen = 0;
				end_idaw = 0;
			}
		}
	}

	if (bwk_nowetwy_wequest(weq) ||
	    bwock->base->featuwes & DASD_FEATUWE_FAIWFAST)
		set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->stawtdev = stawtdev;
	cqw->memdev = stawtdev;
	cqw->bwock = bwock;
	cqw->expiwes = stawtdev->defauwt_expiwes * HZ;	/* defauwt 5 minutes */
	cqw->wpm = dasd_path_get_ppm(stawtdev);
	cqw->wetwies = stawtdev->defauwt_wetwies;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	/* Set fwags to suppwess output fow expected ewwows */
	if (dasd_eckd_is_ese(basedev))
		set_bit(DASD_CQW_SUPPWESS_NWF, &cqw->fwags);

	wetuwn cqw;
}

static int pwepawe_itcw(stwuct itcw *itcw,
			unsigned int twk, unsigned int totwk, int cmd,
			stwuct dasd_device *basedev,
			stwuct dasd_device *stawtdev,
			unsigned int wec_on_twk, int count,
			unsigned int bwksize,
			unsigned int totaw_data_size,
			unsigned int twf,
			unsigned int bwk_pew_twk)
{
	stwuct PFX_eckd_data pfxdata;
	stwuct dasd_eckd_pwivate *basepwiv, *stawtpwiv;
	stwuct DE_eckd_data *dedata;
	stwuct WWE_eckd_data *wwedata;
	stwuct dcw *dcw;

	u32 begcyw, endcyw;
	u16 heads, beghead, endhead;
	u8 pfx_cmd;

	int wc = 0;
	int sectow = 0;
	int dn, d;


	/* setup pwefix data */
	basepwiv = basedev->pwivate;
	stawtpwiv = stawtdev->pwivate;
	dedata = &pfxdata.define_extent;
	wwedata = &pfxdata.wocate_wecowd;

	memset(&pfxdata, 0, sizeof(pfxdata));
	pfxdata.fowmat = 1; /* PFX with WWE */
	pfxdata.base_addwess = basepwiv->conf.ned->unit_addw;
	pfxdata.base_wss = basepwiv->conf.ned->ID;
	pfxdata.vawidity.define_extent = 1;

	/* pwivate uid is kept up to date, conf_data may be outdated */
	if (stawtpwiv->uid.type == UA_BASE_PAV_AWIAS)
		pfxdata.vawidity.vewify_base = 1;

	if (stawtpwiv->uid.type == UA_HYPEW_PAV_AWIAS) {
		pfxdata.vawidity.vewify_base = 1;
		pfxdata.vawidity.hypew_pav = 1;
	}

	switch (cmd) {
	case DASD_ECKD_CCW_WEAD_TWACK_DATA:
		dedata->mask.pewm = 0x1;
		dedata->attwibutes.opewation = basepwiv->attwib.opewation;
		dedata->bwk_size = bwksize;
		dedata->ga_extended |= 0x42;
		wwedata->opewation.owientation = 0x0;
		wwedata->opewation.opewation = 0x0C;
		wwedata->auxiwiawy.check_bytes = 0x01;
		pfx_cmd = DASD_ECKD_CCW_PFX_WEAD;
		bweak;
	case DASD_ECKD_CCW_WWITE_TWACK_DATA:
		dedata->mask.pewm = 0x02;
		dedata->attwibutes.opewation = basepwiv->attwib.opewation;
		dedata->bwk_size = bwksize;
		wc = set_timestamp(NUWW, dedata, basedev);
		dedata->ga_extended |= 0x42;
		wwedata->opewation.owientation = 0x0;
		wwedata->opewation.opewation = 0x3F;
		wwedata->extended_opewation = 0x23;
		wwedata->auxiwiawy.check_bytes = 0x2;
		/*
		 * If XWC is suppowted the System Time Stamp is set. The
		 * vawidity of the time stamp must be wefwected in the pwefix
		 * data as weww.
		 */
		if (dedata->ga_extended & 0x08 && dedata->ga_extended & 0x02)
			pfxdata.vawidity.time_stamp = 1; /* 'Time Stamp Vawid' */
		pfx_cmd = DASD_ECKD_CCW_PFX;
		bweak;
	case DASD_ECKD_CCW_WEAD_COUNT_MT:
		dedata->mask.pewm = 0x1;
		dedata->attwibutes.opewation = DASD_BYPASS_CACHE;
		dedata->ga_extended |= 0x42;
		dedata->bwk_size = bwksize;
		wwedata->opewation.owientation = 0x2;
		wwedata->opewation.opewation = 0x16;
		wwedata->auxiwiawy.check_bytes = 0x01;
		pfx_cmd = DASD_ECKD_CCW_PFX_WEAD;
		bweak;
	defauwt:
		DBF_DEV_EVENT(DBF_EWW, basedev,
			      "pwepawe itcw, unknown opcode 0x%x", cmd);
		BUG();
		bweak;
	}
	if (wc)
		wetuwn wc;

	dedata->attwibutes.mode = 0x3;	/* ECKD */

	heads = basepwiv->wdc_data.twk_pew_cyw;
	begcyw = twk / heads;
	beghead = twk % heads;
	endcyw = totwk / heads;
	endhead = totwk % heads;

	/* check fow sequentiaw pwestage - enhance cywindew wange */
	if (dedata->attwibutes.opewation == DASD_SEQ_PWESTAGE ||
	    dedata->attwibutes.opewation == DASD_SEQ_ACCESS) {

		if (endcyw + basepwiv->attwib.nw_cyw < basepwiv->weaw_cyw)
			endcyw += basepwiv->attwib.nw_cyw;
		ewse
			endcyw = (basepwiv->weaw_cyw - 1);
	}

	set_ch_t(&dedata->beg_ext, begcyw, beghead);
	set_ch_t(&dedata->end_ext, endcyw, endhead);

	dedata->ep_fowmat = 0x20; /* wecowds pew twack is vawid */
	dedata->ep_wec_pew_twack = bwk_pew_twk;

	if (wec_on_twk) {
		switch (basepwiv->wdc_data.dev_type) {
		case 0x3390:
			dn = ceiw_quot(bwksize + 6, 232);
			d = 9 + ceiw_quot(bwksize + 6 * (dn + 1), 34);
			sectow = (49 + (wec_on_twk - 1) * (10 + d)) / 8;
			bweak;
		case 0x3380:
			d = 7 + ceiw_quot(bwksize + 12, 32);
			sectow = (39 + (wec_on_twk - 1) * (8 + d)) / 7;
			bweak;
		}
	}

	if (cmd == DASD_ECKD_CCW_WEAD_COUNT_MT) {
		wwedata->auxiwiawy.wength_vawid = 0;
		wwedata->auxiwiawy.wength_scope = 0;
		wwedata->sectow = 0xff;
	} ewse {
		wwedata->auxiwiawy.wength_vawid = 1;
		wwedata->auxiwiawy.wength_scope = 1;
		wwedata->sectow = sectow;
	}
	wwedata->auxiwiawy.imbedded_ccw_vawid = 1;
	wwedata->wength = twf;
	wwedata->imbedded_ccw = cmd;
	wwedata->count = count;
	set_ch_t(&wwedata->seek_addw, begcyw, beghead);
	wwedata->seawch_awg.cyw = wwedata->seek_addw.cyw;
	wwedata->seawch_awg.head = wwedata->seek_addw.head;
	wwedata->seawch_awg.wecowd = wec_on_twk;

	dcw = itcw_add_dcw(itcw, pfx_cmd, 0,
		     &pfxdata, sizeof(pfxdata), totaw_data_size);
	wetuwn PTW_EWW_OW_ZEWO(dcw);
}

static stwuct dasd_ccw_weq *dasd_eckd_buiwd_cp_tpm_twack(
					       stwuct dasd_device *stawtdev,
					       stwuct dasd_bwock *bwock,
					       stwuct wequest *weq,
					       sectow_t fiwst_wec,
					       sectow_t wast_wec,
					       sectow_t fiwst_twk,
					       sectow_t wast_twk,
					       unsigned int fiwst_offs,
					       unsigned int wast_offs,
					       unsigned int bwk_pew_twk,
					       unsigned int bwksize)
{
	stwuct dasd_ccw_weq *cqw;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;
	chaw *dst;
	unsigned int twkcount, ctidaw;
	unsigned chaw cmd;
	stwuct dasd_device *basedev;
	unsigned int twf;
	stwuct itcw *itcw;
	stwuct tidaw *wast_tidaw = NUWW;
	int itcw_op;
	size_t itcw_size;
	u8 tidaw_fwags;
	unsigned int seg_wen, pawt_wen, wen_to_twack_end;
	unsigned chaw new_twack;
	sectow_t wecid, twkid;
	unsigned int offs;
	unsigned int count, count_to_twk_end;
	int wet;

	basedev = bwock->base;
	if (wq_data_diw(weq) == WEAD) {
		cmd = DASD_ECKD_CCW_WEAD_TWACK_DATA;
		itcw_op = ITCW_OP_WEAD;
	} ewse if (wq_data_diw(weq) == WWITE) {
		cmd = DASD_ECKD_CCW_WWITE_TWACK_DATA;
		itcw_op = ITCW_OP_WWITE;
	} ewse
		wetuwn EWW_PTW(-EINVAW);

	/* twackbased I/O needs addwess aww memowy via TIDAWs,
	 * not just fow 64 bit addwesses. This awwows us to map
	 * each segment diwectwy to one tidaw.
	 * In the case of wwite wequests, additionaw tidaws may
	 * be needed when a segment cwosses a twack boundawy.
	 */
	twkcount = wast_twk - fiwst_twk + 1;
	ctidaw = 0;
	wq_fow_each_segment(bv, weq, itew) {
		++ctidaw;
	}
	if (wq_data_diw(weq) == WWITE)
		ctidaw += (wast_twk - fiwst_twk);

	/* Awwocate the ccw wequest. */
	itcw_size = itcw_cawc_size(0, ctidaw, 0);
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 0, itcw_size, stawtdev,
				   bwk_mq_wq_to_pdu(weq));
	if (IS_EWW(cqw))
		wetuwn cqw;

	/* twansfew wength factow: how many bytes to wead fwom the wast twack */
	if (fiwst_twk == wast_twk)
		twf = wast_offs - fiwst_offs + 1;
	ewse
		twf = wast_offs + 1;
	twf *= bwksize;

	itcw = itcw_init(cqw->data, itcw_size, itcw_op, 0, ctidaw, 0);
	if (IS_EWW(itcw)) {
		wet = -EINVAW;
		goto out_ewwow;
	}
	cqw->cpaddw = itcw_get_tcw(itcw);
	if (pwepawe_itcw(itcw, fiwst_twk, wast_twk,
			 cmd, basedev, stawtdev,
			 fiwst_offs + 1,
			 twkcount, bwksize,
			 (wast_wec - fiwst_wec + 1) * bwksize,
			 twf, bwk_pew_twk) == -EAGAIN) {
		/* Cwock not in sync and XWC is enabwed.
		 * Twy again watew.
		 */
		wet = -EAGAIN;
		goto out_ewwow;
	}
	wen_to_twack_end = 0;
	/*
	 * A tidaw can addwess 4k of memowy, but must not cwoss page boundawies
	 * We can wet the bwock wayew handwe this by setting
	 * bwk_queue_segment_boundawy to page boundawies and
	 * bwk_max_segment_size to page size when setting up the wequest queue.
	 * Fow wwite wequests, a TIDAW must not cwoss twack boundawies, because
	 * we have to set the CBC fwag on the wast tidaw fow each twack.
	 */
	if (wq_data_diw(weq) == WWITE) {
		new_twack = 1;
		wecid = fiwst_wec;
		wq_fow_each_segment(bv, weq, itew) {
			dst = bvec_viwt(&bv);
			seg_wen = bv.bv_wen;
			whiwe (seg_wen) {
				if (new_twack) {
					twkid = wecid;
					offs = sectow_div(twkid, bwk_pew_twk);
					count_to_twk_end = bwk_pew_twk - offs;
					count = min((wast_wec - wecid + 1),
						    (sectow_t)count_to_twk_end);
					wen_to_twack_end = count * bwksize;
					wecid += count;
					new_twack = 0;
				}
				pawt_wen = min(seg_wen, wen_to_twack_end);
				seg_wen -= pawt_wen;
				wen_to_twack_end -= pawt_wen;
				/* We need to end the tidaw at twack end */
				if (!wen_to_twack_end) {
					new_twack = 1;
					tidaw_fwags = TIDAW_FWAGS_INSEWT_CBC;
				} ewse
					tidaw_fwags = 0;
				wast_tidaw = itcw_add_tidaw(itcw, tidaw_fwags,
							    dst, pawt_wen);
				if (IS_EWW(wast_tidaw)) {
					wet = -EINVAW;
					goto out_ewwow;
				}
				dst += pawt_wen;
			}
		}
	} ewse {
		wq_fow_each_segment(bv, weq, itew) {
			dst = bvec_viwt(&bv);
			wast_tidaw = itcw_add_tidaw(itcw, 0x00,
						    dst, bv.bv_wen);
			if (IS_EWW(wast_tidaw)) {
				wet = -EINVAW;
				goto out_ewwow;
			}
		}
	}
	wast_tidaw->fwags |= TIDAW_FWAGS_WAST;
	wast_tidaw->fwags &= ~TIDAW_FWAGS_INSEWT_CBC;
	itcw_finawize(itcw);

	if (bwk_nowetwy_wequest(weq) ||
	    bwock->base->featuwes & DASD_FEATUWE_FAIWFAST)
		set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->cpmode = 1;
	cqw->stawtdev = stawtdev;
	cqw->memdev = stawtdev;
	cqw->bwock = bwock;
	cqw->expiwes = stawtdev->defauwt_expiwes * HZ;	/* defauwt 5 minutes */
	cqw->wpm = dasd_path_get_ppm(stawtdev);
	cqw->wetwies = stawtdev->defauwt_wetwies;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	/* Set fwags to suppwess output fow expected ewwows */
	if (dasd_eckd_is_ese(basedev)) {
		set_bit(DASD_CQW_SUPPWESS_FP, &cqw->fwags);
		set_bit(DASD_CQW_SUPPWESS_IW, &cqw->fwags);
		set_bit(DASD_CQW_SUPPWESS_NWF, &cqw->fwags);
	}

	wetuwn cqw;
out_ewwow:
	dasd_sfwee_wequest(cqw, stawtdev);
	wetuwn EWW_PTW(wet);
}

static stwuct dasd_ccw_weq *dasd_eckd_buiwd_cp(stwuct dasd_device *stawtdev,
					       stwuct dasd_bwock *bwock,
					       stwuct wequest *weq)
{
	int cmdwtd, cmdwtd;
	int use_pwefix;
	int fcx_muwtitwack;
	stwuct dasd_eckd_pwivate *pwivate;
	stwuct dasd_device *basedev;
	sectow_t fiwst_wec, wast_wec;
	sectow_t fiwst_twk, wast_twk;
	unsigned int fiwst_offs, wast_offs;
	unsigned int bwk_pew_twk, bwksize;
	int cdwspeciaw;
	unsigned int data_size;
	stwuct dasd_ccw_weq *cqw;

	basedev = bwock->base;
	pwivate = basedev->pwivate;

	/* Cawcuwate numbew of bwocks/wecowds pew twack. */
	bwksize = bwock->bp_bwock;
	bwk_pew_twk = wecs_pew_twack(&pwivate->wdc_data, 0, bwksize);
	if (bwk_pew_twk == 0)
		wetuwn EWW_PTW(-EINVAW);
	/* Cawcuwate wecowd id of fiwst and wast bwock. */
	fiwst_wec = fiwst_twk = bwk_wq_pos(weq) >> bwock->s2b_shift;
	fiwst_offs = sectow_div(fiwst_twk, bwk_pew_twk);
	wast_wec = wast_twk =
		(bwk_wq_pos(weq) + bwk_wq_sectows(weq) - 1) >> bwock->s2b_shift;
	wast_offs = sectow_div(wast_twk, bwk_pew_twk);
	cdwspeciaw = (pwivate->uses_cdw && fiwst_wec < 2*bwk_pew_twk);

	fcx_muwtitwack = pwivate->featuwes.featuwe[40] & 0x20;
	data_size = bwk_wq_bytes(weq);
	if (data_size % bwksize)
		wetuwn EWW_PTW(-EINVAW);
	/* tpm wwite wequest add CBC data on each twack boundawy */
	if (wq_data_diw(weq) == WWITE)
		data_size += (wast_twk - fiwst_twk) * 4;

	/* is wead twack data and wwite twack data in command mode suppowted? */
	cmdwtd = pwivate->featuwes.featuwe[9] & 0x20;
	cmdwtd = pwivate->featuwes.featuwe[12] & 0x40;
	use_pwefix = pwivate->featuwes.featuwe[8] & 0x01;

	cqw = NUWW;
	if (cdwspeciaw || dasd_page_cache) {
		/* do nothing, just faww thwough to the cmd mode singwe case */
	} ewse if ((data_size <= pwivate->fcx_max_data)
		   && (fcx_muwtitwack || (fiwst_twk == wast_twk))) {
		cqw = dasd_eckd_buiwd_cp_tpm_twack(stawtdev, bwock, weq,
						    fiwst_wec, wast_wec,
						    fiwst_twk, wast_twk,
						    fiwst_offs, wast_offs,
						    bwk_pew_twk, bwksize);
		if (IS_EWW(cqw) && (PTW_EWW(cqw) != -EAGAIN) &&
		    (PTW_EWW(cqw) != -ENOMEM))
			cqw = NUWW;
	} ewse if (use_pwefix &&
		   (((wq_data_diw(weq) == WEAD) && cmdwtd) ||
		    ((wq_data_diw(weq) == WWITE) && cmdwtd))) {
		cqw = dasd_eckd_buiwd_cp_cmd_twack(stawtdev, bwock, weq,
						   fiwst_wec, wast_wec,
						   fiwst_twk, wast_twk,
						   fiwst_offs, wast_offs,
						   bwk_pew_twk, bwksize);
		if (IS_EWW(cqw) && (PTW_EWW(cqw) != -EAGAIN) &&
		    (PTW_EWW(cqw) != -ENOMEM))
			cqw = NUWW;
	}
	if (!cqw)
		cqw = dasd_eckd_buiwd_cp_cmd_singwe(stawtdev, bwock, weq,
						    fiwst_wec, wast_wec,
						    fiwst_twk, wast_twk,
						    fiwst_offs, wast_offs,
						    bwk_pew_twk, bwksize);
	wetuwn cqw;
}

static stwuct dasd_ccw_weq *dasd_eckd_buiwd_cp_waw(stwuct dasd_device *stawtdev,
						   stwuct dasd_bwock *bwock,
						   stwuct wequest *weq)
{
	sectow_t stawt_padding_sectows, end_sectow_offset, end_padding_sectows;
	unsigned int seg_wen, wen_to_twack_end;
	unsigned int cidaw, cpwength, datasize;
	sectow_t fiwst_twk, wast_twk, sectows;
	stwuct dasd_eckd_pwivate *base_pwiv;
	stwuct dasd_device *basedev;
	stwuct weq_itewatow itew;
	stwuct dasd_ccw_weq *cqw;
	unsigned int twkcount;
	unsigned wong *idaws;
	unsigned int size;
	unsigned chaw cmd;
	stwuct bio_vec bv;
	stwuct ccw1 *ccw;
	int use_pwefix;
	void *data;
	chaw *dst;

	/*
	 * waw twack access needs to be mutipwe of 64k and on 64k boundawy
	 * Fow wead wequests we can fix an incowwect awignment by padding
	 * the wequest with dummy pages.
	 */
	stawt_padding_sectows = bwk_wq_pos(weq) % DASD_WAW_SECTOWS_PEW_TWACK;
	end_sectow_offset = (bwk_wq_pos(weq) + bwk_wq_sectows(weq)) %
		DASD_WAW_SECTOWS_PEW_TWACK;
	end_padding_sectows = (DASD_WAW_SECTOWS_PEW_TWACK - end_sectow_offset) %
		DASD_WAW_SECTOWS_PEW_TWACK;
	basedev = bwock->base;
	if ((stawt_padding_sectows || end_padding_sectows) &&
	    (wq_data_diw(weq) == WWITE)) {
		DBF_DEV_EVENT(DBF_EWW, basedev,
			      "waw wwite not twack awigned (%wwu,%wwu) weq %p",
			      stawt_padding_sectows, end_padding_sectows, weq);
		wetuwn EWW_PTW(-EINVAW);
	}

	fiwst_twk = bwk_wq_pos(weq) / DASD_WAW_SECTOWS_PEW_TWACK;
	wast_twk = (bwk_wq_pos(weq) + bwk_wq_sectows(weq) - 1) /
		DASD_WAW_SECTOWS_PEW_TWACK;
	twkcount = wast_twk - fiwst_twk + 1;

	if (wq_data_diw(weq) == WEAD)
		cmd = DASD_ECKD_CCW_WEAD_TWACK;
	ewse if (wq_data_diw(weq) == WWITE)
		cmd = DASD_ECKD_CCW_WWITE_FUWW_TWACK;
	ewse
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Waw twack based I/O needs IDAWs fow each page,
	 * and not just fow 64 bit addwesses.
	 */
	cidaw = twkcount * DASD_WAW_BWOCK_PEW_TWACK;

	/*
	 * stwuct PFX_eckd_data and stwuct WWE_eckd_data can have up to 2 bytes
	 * of extended pawametew. This is needed fow wwite fuww twack.
	 */
	base_pwiv = basedev->pwivate;
	use_pwefix = base_pwiv->featuwes.featuwe[8] & 0x01;
	if (use_pwefix) {
		cpwength = 1 + twkcount;
		size = sizeof(stwuct PFX_eckd_data) + 2;
	} ewse {
		cpwength = 2 + twkcount;
		size = sizeof(stwuct DE_eckd_data) +
			sizeof(stwuct WWE_eckd_data) + 2;
	}
	size = AWIGN(size, 8);

	datasize = size + cidaw * sizeof(unsigned wong);

	/* Awwocate the ccw wequest. */
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, cpwength,
				   datasize, stawtdev, bwk_mq_wq_to_pdu(weq));
	if (IS_EWW(cqw))
		wetuwn cqw;

	ccw = cqw->cpaddw;
	data = cqw->data;

	if (use_pwefix) {
		pwefix_WWE(ccw++, data, fiwst_twk, wast_twk, cmd, basedev,
			   stawtdev, 1, 0, twkcount, 0, 0);
	} ewse {
		define_extent(ccw++, data, fiwst_twk, wast_twk, cmd, basedev, 0);
		ccw[-1].fwags |= CCW_FWAG_CC;

		data += sizeof(stwuct DE_eckd_data);
		wocate_wecowd_ext(ccw++, data, fiwst_twk, 0,
				  twkcount, cmd, basedev, 0, 0);
	}

	idaws = (unsigned wong *)(cqw->data + size);
	wen_to_twack_end = 0;
	if (stawt_padding_sectows) {
		ccw[-1].fwags |= CCW_FWAG_CC;
		ccw->cmd_code = cmd;
		/* maximum 3390 twack size */
		ccw->count = 57326;
		/* 64k map to one twack */
		wen_to_twack_end = 65536 - stawt_padding_sectows * 512;
		ccw->cda = (__u32)viwt_to_phys(idaws);
		ccw->fwags |= CCW_FWAG_IDA;
		ccw->fwags |= CCW_FWAG_SWI;
		ccw++;
		fow (sectows = 0; sectows < stawt_padding_sectows; sectows += 8)
			idaws = idaw_cweate_wowds(idaws, wawpadpage, PAGE_SIZE);
	}
	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		seg_wen = bv.bv_wen;
		if (cmd == DASD_ECKD_CCW_WEAD_TWACK)
			memset(dst, 0, seg_wen);
		if (!wen_to_twack_end) {
			ccw[-1].fwags |= CCW_FWAG_CC;
			ccw->cmd_code = cmd;
			/* maximum 3390 twack size */
			ccw->count = 57326;
			/* 64k map to one twack */
			wen_to_twack_end = 65536;
			ccw->cda = (__u32)viwt_to_phys(idaws);
			ccw->fwags |= CCW_FWAG_IDA;
			ccw->fwags |= CCW_FWAG_SWI;
			ccw++;
		}
		wen_to_twack_end -= seg_wen;
		idaws = idaw_cweate_wowds(idaws, dst, seg_wen);
	}
	fow (sectows = 0; sectows < end_padding_sectows; sectows += 8)
		idaws = idaw_cweate_wowds(idaws, wawpadpage, PAGE_SIZE);
	if (bwk_nowetwy_wequest(weq) ||
	    bwock->base->featuwes & DASD_FEATUWE_FAIWFAST)
		set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->stawtdev = stawtdev;
	cqw->memdev = stawtdev;
	cqw->bwock = bwock;
	cqw->expiwes = stawtdev->defauwt_expiwes * HZ;
	cqw->wpm = dasd_path_get_ppm(stawtdev);
	cqw->wetwies = stawtdev->defauwt_wetwies;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wetuwn cqw;
}


static int
dasd_eckd_fwee_cp(stwuct dasd_ccw_weq *cqw, stwuct wequest *weq)
{
	stwuct dasd_eckd_pwivate *pwivate;
	stwuct ccw1 *ccw;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;
	chaw *dst, *cda;
	unsigned int bwksize, bwk_pew_twk, off;
	sectow_t wecid;
	int status;

	if (!dasd_page_cache)
		goto out;
	pwivate = cqw->bwock->base->pwivate;
	bwksize = cqw->bwock->bp_bwock;
	bwk_pew_twk = wecs_pew_twack(&pwivate->wdc_data, 0, bwksize);
	wecid = bwk_wq_pos(weq) >> cqw->bwock->s2b_shift;
	ccw = cqw->cpaddw;
	/* Skip ovew define extent & wocate wecowd. */
	ccw++;
	if (pwivate->uses_cdw == 0 || wecid > 2*bwk_pew_twk)
		ccw++;
	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		fow (off = 0; off < bv.bv_wen; off += bwksize) {
			/* Skip wocate wecowd. */
			if (pwivate->uses_cdw && wecid <= 2*bwk_pew_twk)
				ccw++;
			if (dst) {
				if (ccw->fwags & CCW_FWAG_IDA)
					cda = *((chaw **)phys_to_viwt(ccw->cda));
				ewse
					cda = phys_to_viwt(ccw->cda);
				if (dst != cda) {
					if (wq_data_diw(weq) == WEAD)
						memcpy(dst, cda, bv.bv_wen);
					kmem_cache_fwee(dasd_page_cache,
					    (void *)((addw_t)cda & PAGE_MASK));
				}
				dst = NUWW;
			}
			ccw++;
			wecid++;
		}
	}
out:
	status = cqw->status == DASD_CQW_DONE;
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn status;
}

/*
 * Modify ccw/tcw in cqw so it can be stawted on a base device.
 *
 * Note that this is not enough to westawt the cqw!
 * Eithew weset cqw->stawtdev as weww (summawy unit check handwing)
 * ow westawt via sepawate cqw (as in EWP handwing).
 */
void dasd_eckd_weset_ccw_to_base_io(stwuct dasd_ccw_weq *cqw)
{
	stwuct ccw1 *ccw;
	stwuct PFX_eckd_data *pfxdata;
	stwuct tcw *tcw;
	stwuct tccb *tccb;
	stwuct dcw *dcw;

	if (cqw->cpmode == 1) {
		tcw = cqw->cpaddw;
		tccb = tcw_get_tccb(tcw);
		dcw = (stwuct dcw *)&tccb->tca[0];
		pfxdata = (stwuct PFX_eckd_data *)&dcw->cd[0];
		pfxdata->vawidity.vewify_base = 0;
		pfxdata->vawidity.hypew_pav = 0;
	} ewse {
		ccw = cqw->cpaddw;
		pfxdata = cqw->data;
		if (ccw->cmd_code == DASD_ECKD_CCW_PFX) {
			pfxdata->vawidity.vewify_base = 0;
			pfxdata->vawidity.hypew_pav = 0;
		}
	}
}

#define DASD_ECKD_CHANQ_MAX_SIZE 4

static stwuct dasd_ccw_weq *dasd_eckd_buiwd_awias_cp(stwuct dasd_device *base,
						     stwuct dasd_bwock *bwock,
						     stwuct wequest *weq)
{
	stwuct dasd_eckd_pwivate *pwivate;
	stwuct dasd_device *stawtdev;
	unsigned wong fwags;
	stwuct dasd_ccw_weq *cqw;

	stawtdev = dasd_awias_get_stawt_dev(base);
	if (!stawtdev)
		stawtdev = base;
	pwivate = stawtdev->pwivate;
	if (pwivate->count >= DASD_ECKD_CHANQ_MAX_SIZE)
		wetuwn EWW_PTW(-EBUSY);

	spin_wock_iwqsave(get_ccwdev_wock(stawtdev->cdev), fwags);
	pwivate->count++;
	if ((base->featuwes & DASD_FEATUWE_USEWAW))
		cqw = dasd_eckd_buiwd_cp_waw(stawtdev, bwock, weq);
	ewse
		cqw = dasd_eckd_buiwd_cp(stawtdev, bwock, weq);
	if (IS_EWW(cqw))
		pwivate->count--;
	spin_unwock_iwqwestowe(get_ccwdev_wock(stawtdev->cdev), fwags);
	wetuwn cqw;
}

static int dasd_eckd_fwee_awias_cp(stwuct dasd_ccw_weq *cqw,
				   stwuct wequest *weq)
{
	stwuct dasd_eckd_pwivate *pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(get_ccwdev_wock(cqw->memdev->cdev), fwags);
	pwivate = cqw->memdev->pwivate;
	pwivate->count--;
	spin_unwock_iwqwestowe(get_ccwdev_wock(cqw->memdev->cdev), fwags);
	wetuwn dasd_eckd_fwee_cp(cqw, weq);
}

static int
dasd_eckd_fiww_info(stwuct dasd_device * device,
		    stwuct dasd_infowmation2_t * info)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	info->wabew_bwock = 2;
	info->FBA_wayout = pwivate->uses_cdw ? 0 : 1;
	info->fowmat = pwivate->uses_cdw ? DASD_FOWMAT_CDW : DASD_FOWMAT_WDW;
	info->chawactewistics_size = sizeof(pwivate->wdc_data);
	memcpy(info->chawactewistics, &pwivate->wdc_data,
	       sizeof(pwivate->wdc_data));
	info->confdata_size = min_t(unsigned wong, pwivate->conf.wen,
				    sizeof(info->configuwation_data));
	memcpy(info->configuwation_data, pwivate->conf.data,
	       info->confdata_size);
	wetuwn 0;
}

/*
 * SECTION: ioctw functions fow eckd devices.
 */

/*
 * Wewease device ioctw.
 * Buiws a channew pwogwamm to weweases a pwiow wesewved
 * (see dasd_eckd_wesewve) device.
 */
static int
dasd_eckd_wewease(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;
	int wc;
	stwuct ccw1 *ccw;
	int usegwobaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	usegwobaw = 0;
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1, 32, device, NUWW);
	if (IS_EWW(cqw)) {
		mutex_wock(&dasd_wesewve_mutex);
		usegwobaw = 1;
		cqw = &dasd_wesewve_weq->cqw;
		memset(cqw, 0, sizeof(*cqw));
		memset(&dasd_wesewve_weq->ccw, 0,
		       sizeof(dasd_wesewve_weq->ccw));
		cqw->cpaddw = &dasd_wesewve_weq->ccw;
		cqw->data = &dasd_wesewve_weq->data;
		cqw->magic = DASD_ECKD_MAGIC;
	}
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_WEWEASE;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->count = 32;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);
	cqw->stawtdev = device;
	cqw->memdev = device;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->wetwies = 2;	/* set wetwy countew to enabwe basic EWP */
	cqw->expiwes = 2 * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wc = dasd_sweep_on_immediatwy(cqw);
	if (!wc)
		cweaw_bit(DASD_FWAG_IS_WESEWVED, &device->fwags);

	if (usegwobaw)
		mutex_unwock(&dasd_wesewve_mutex);
	ewse
		dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * Wesewve device ioctw.
 * Options awe set to 'synchwonous wait fow intewwupt' and
 * 'timeout the wequest'. This weads to a tewminate IO if
 * the intewwupt is outstanding fow a cewtain time.
 */
static int
dasd_eckd_wesewve(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;
	int wc;
	stwuct ccw1 *ccw;
	int usegwobaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	usegwobaw = 0;
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1, 32, device, NUWW);
	if (IS_EWW(cqw)) {
		mutex_wock(&dasd_wesewve_mutex);
		usegwobaw = 1;
		cqw = &dasd_wesewve_weq->cqw;
		memset(cqw, 0, sizeof(*cqw));
		memset(&dasd_wesewve_weq->ccw, 0,
		       sizeof(dasd_wesewve_weq->ccw));
		cqw->cpaddw = &dasd_wesewve_weq->ccw;
		cqw->data = &dasd_wesewve_weq->data;
		cqw->magic = DASD_ECKD_MAGIC;
	}
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_WESEWVE;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->count = 32;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);
	cqw->stawtdev = device;
	cqw->memdev = device;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->wetwies = 2;	/* set wetwy countew to enabwe basic EWP */
	cqw->expiwes = 2 * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wc = dasd_sweep_on_immediatwy(cqw);
	if (!wc)
		set_bit(DASD_FWAG_IS_WESEWVED, &device->fwags);

	if (usegwobaw)
		mutex_unwock(&dasd_wesewve_mutex);
	ewse
		dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * Steaw wock ioctw - unconditionaw wesewve device.
 * Buiws a channew pwogwamm to bweak a device's wesewvation.
 * (unconditionaw wesewve)
 */
static int
dasd_eckd_steaw_wock(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;
	int wc;
	stwuct ccw1 *ccw;
	int usegwobaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	usegwobaw = 0;
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1, 32, device, NUWW);
	if (IS_EWW(cqw)) {
		mutex_wock(&dasd_wesewve_mutex);
		usegwobaw = 1;
		cqw = &dasd_wesewve_weq->cqw;
		memset(cqw, 0, sizeof(*cqw));
		memset(&dasd_wesewve_weq->ccw, 0,
		       sizeof(dasd_wesewve_weq->ccw));
		cqw->cpaddw = &dasd_wesewve_weq->ccw;
		cqw->data = &dasd_wesewve_weq->data;
		cqw->magic = DASD_ECKD_MAGIC;
	}
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_SWCK;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->count = 32;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);
	cqw->stawtdev = device;
	cqw->memdev = device;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->wetwies = 2;	/* set wetwy countew to enabwe basic EWP */
	cqw->expiwes = 2 * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wc = dasd_sweep_on_immediatwy(cqw);
	if (!wc)
		set_bit(DASD_FWAG_IS_WESEWVED, &device->fwags);

	if (usegwobaw)
		mutex_unwock(&dasd_wesewve_mutex);
	ewse
		dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * SNID - Sense Path Gwoup ID
 * This ioctw may be used in situations whewe I/O is stawwed due to
 * a wesewve, so if the nowmaw dasd_smawwoc_wequest faiws, we use the
 * pweawwocated dasd_wesewve_weq.
 */
static int dasd_eckd_snid(stwuct dasd_device *device,
			  void __usew *awgp)
{
	stwuct dasd_ccw_weq *cqw;
	int wc;
	stwuct ccw1 *ccw;
	int usegwobaw;
	stwuct dasd_snid_ioctw_data uswpawm;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (copy_fwom_usew(&uswpawm, awgp, sizeof(uswpawm)))
		wetuwn -EFAUWT;

	usegwobaw = 0;
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1,
				   sizeof(stwuct dasd_snid_data), device,
				   NUWW);
	if (IS_EWW(cqw)) {
		mutex_wock(&dasd_wesewve_mutex);
		usegwobaw = 1;
		cqw = &dasd_wesewve_weq->cqw;
		memset(cqw, 0, sizeof(*cqw));
		memset(&dasd_wesewve_weq->ccw, 0,
		       sizeof(dasd_wesewve_weq->ccw));
		cqw->cpaddw = &dasd_wesewve_weq->ccw;
		cqw->data = &dasd_wesewve_weq->data;
		cqw->magic = DASD_ECKD_MAGIC;
	}
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_SNID;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->count = 12;
	ccw->cda = (__u32)viwt_to_phys(cqw->data);
	cqw->stawtdev = device;
	cqw->memdev = device;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	set_bit(DASD_CQW_AWWOW_SWOCK, &cqw->fwags);
	cqw->wetwies = 5;
	cqw->expiwes = 10 * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	cqw->wpm = uswpawm.path_mask;

	wc = dasd_sweep_on_immediatwy(cqw);
	/* vewify that I/O pwocessing didn't modify the path mask */
	if (!wc && uswpawm.path_mask && (cqw->wpm != uswpawm.path_mask))
		wc = -EIO;
	if (!wc) {
		uswpawm.data = *((stwuct dasd_snid_data *)cqw->data);
		if (copy_to_usew(awgp, &uswpawm, sizeof(uswpawm)))
			wc = -EFAUWT;
	}

	if (usegwobaw)
		mutex_unwock(&dasd_wesewve_mutex);
	ewse
		dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * Wead pewfowmance statistics
 */
static int
dasd_eckd_pewfowmance(stwuct dasd_device *device, void __usew *awgp)
{
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_wssd_pewf_stats_t *stats;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */  + 1 /* WSSD */,
				   (sizeof(stwuct dasd_psf_pwssd_data) +
				    sizeof(stwuct dasd_wssd_pewf_stats_t)),
				   device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "Couwd not awwocate initiawization wequest");
		wetuwn PTW_EWW(cqw);
	}
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->wetwies = 0;
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	cqw->expiwes = 10 * HZ;

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
	memset(pwssdp, 0, sizeof(stwuct dasd_psf_pwssd_data));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = 0x01;	/* Pewfowmance Statistics */
	pwssdp->vawies[1] = 0x01;	/* Pewf Statistics fow the Subsystem */

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(stwuct dasd_psf_pwssd_data);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	/* Wead Subsystem Data - Pewfowmance Statistics */
	stats = (stwuct dasd_wssd_pewf_stats_t *) (pwssdp + 1);
	memset(stats, 0, sizeof(stwuct dasd_wssd_pewf_stats_t));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(stwuct dasd_wssd_pewf_stats_t);
	ccw->cda = (__u32)viwt_to_phys(stats);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	wc = dasd_sweep_on(cqw);
	if (wc == 0) {
		pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
		stats = (stwuct dasd_wssd_pewf_stats_t *) (pwssdp + 1);
		if (copy_to_usew(awgp, stats,
				 sizeof(stwuct dasd_wssd_pewf_stats_t)))
			wc = -EFAUWT;
	}
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * Get attwibutes (cache opewations)
 * Wetuwnes the cache attwibutes used in Define Extend (DE).
 */
static int
dasd_eckd_get_attwib(stwuct dasd_device *device, void __usew *awgp)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct attwib_data_t attwib = pwivate->attwib;
	int wc;

        if (!capabwe(CAP_SYS_ADMIN))
                wetuwn -EACCES;
	if (!awgp)
                wetuwn -EINVAW;

	wc = 0;
	if (copy_to_usew(awgp, (wong *) &attwib,
			 sizeof(stwuct attwib_data_t)))
		wc = -EFAUWT;

	wetuwn wc;
}

/*
 * Set attwibutes (cache opewations)
 * Stowes the attwibutes fow cache opewation to be used in Define Extend (DE).
 */
static int
dasd_eckd_set_attwib(stwuct dasd_device *device, void __usew *awgp)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct attwib_data_t attwib;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	if (!awgp)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&attwib, awgp, sizeof(stwuct attwib_data_t)))
		wetuwn -EFAUWT;
	pwivate->attwib = attwib;

	dev_info(&device->cdev->dev,
		 "The DASD cache mode was set to %x (%i cywindew pwestage)\n",
		 pwivate->attwib.opewation, pwivate->attwib.nw_cyw);
	wetuwn 0;
}

/*
 * Issue syscaww I/O to EMC Symmetwix awway.
 * CCWs awe PSF and WSSD
 */
static int dasd_symm_io(stwuct dasd_device *device, void __usew *awgp)
{
	stwuct dasd_symmio_pawms uswpawm;
	chaw *psf_data, *wssd_wesuwt;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	chaw psf0, psf1;
	int wc;

	if (!capabwe(CAP_SYS_ADMIN) && !capabwe(CAP_SYS_WAWIO))
		wetuwn -EACCES;
	psf0 = psf1 = 0;

	/* Copy pawms fwom cawwew */
	wc = -EFAUWT;
	if (copy_fwom_usew(&uswpawm, awgp, sizeof(uswpawm)))
		goto out;
	if (is_compat_task()) {
		/* Make suwe pointews awe sane even on 31 bit. */
		wc = -EINVAW;
		if ((uswpawm.psf_data >> 32) != 0)
			goto out;
		if ((uswpawm.wssd_wesuwt >> 32) != 0)
			goto out;
		uswpawm.psf_data &= 0x7fffffffUWW;
		uswpawm.wssd_wesuwt &= 0x7fffffffUWW;
	}
	/* at weast 2 bytes awe accessed and shouwd be awwocated */
	if (uswpawm.psf_data_wen < 2) {
		DBF_DEV_EVENT(DBF_WAWNING, device,
			      "Symmetwix ioctw invawid data wength %d",
			      uswpawm.psf_data_wen);
		wc = -EINVAW;
		goto out;
	}
	/* awwoc I/O data awea */
	psf_data = kzawwoc(uswpawm.psf_data_wen, GFP_KEWNEW | GFP_DMA);
	wssd_wesuwt = kzawwoc(uswpawm.wssd_wesuwt_wen, GFP_KEWNEW | GFP_DMA);
	if (!psf_data || !wssd_wesuwt) {
		wc = -ENOMEM;
		goto out_fwee;
	}

	/* get syscaww headew fwom usew space */
	wc = -EFAUWT;
	if (copy_fwom_usew(psf_data,
			   (void __usew *)(unsigned wong) uswpawm.psf_data,
			   uswpawm.psf_data_wen))
		goto out_fwee;
	psf0 = psf_data[0];
	psf1 = psf_data[1];

	/* setup CCWs fow PSF + WSSD */
	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 2, 0, device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			"Couwd not awwocate initiawization wequest");
		wc = PTW_EWW(cqw);
		goto out_fwee;
	}

	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->wetwies = 3;
	cqw->expiwes = 10 * HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	/* Buiwd the ccws */
	ccw = cqw->cpaddw;

	/* PSF ccw */
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = uswpawm.psf_data_wen;
	ccw->fwags |= CCW_FWAG_CC;
	ccw->cda = (__u32)viwt_to_phys(psf_data);

	ccw++;

	/* WSSD ccw  */
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = uswpawm.wssd_wesuwt_wen;
	ccw->fwags = CCW_FWAG_SWI ;
	ccw->cda = (__u32)viwt_to_phys(wssd_wesuwt);

	wc = dasd_sweep_on(cqw);
	if (wc)
		goto out_sfwee;

	wc = -EFAUWT;
	if (copy_to_usew((void __usew *)(unsigned wong) uswpawm.wssd_wesuwt,
			   wssd_wesuwt, uswpawm.wssd_wesuwt_wen))
		goto out_sfwee;
	wc = 0;

out_sfwee:
	dasd_sfwee_wequest(cqw, cqw->memdev);
out_fwee:
	kfwee(wssd_wesuwt);
	kfwee(psf_data);
out:
	DBF_DEV_EVENT(DBF_WAWNING, device,
		      "Symmetwix ioctw (0x%02x 0x%02x): wc=%d",
		      (int) psf0, (int) psf1, wc);
	wetuwn wc;
}

static int
dasd_eckd_ioctw(stwuct dasd_bwock *bwock, unsigned int cmd, void __usew *awgp)
{
	stwuct dasd_device *device = bwock->base;

	switch (cmd) {
	case BIODASDGATTW:
		wetuwn dasd_eckd_get_attwib(device, awgp);
	case BIODASDSATTW:
		wetuwn dasd_eckd_set_attwib(device, awgp);
	case BIODASDPSWD:
		wetuwn dasd_eckd_pewfowmance(device, awgp);
	case BIODASDWWSE:
		wetuwn dasd_eckd_wewease(device);
	case BIODASDWSWV:
		wetuwn dasd_eckd_wesewve(device);
	case BIODASDSWCK:
		wetuwn dasd_eckd_steaw_wock(device);
	case BIODASDSNID:
		wetuwn dasd_eckd_snid(device, awgp);
	case BIODASDSYMMIO:
		wetuwn dasd_symm_io(device, awgp);
	defauwt:
		wetuwn -ENOTTY;
	}
}

/*
 * Dump the wange of CCWs into 'page' buffew
 * and wetuwn numbew of pwinted chaws.
 */
static void
dasd_eckd_dump_ccw_wange(stwuct ccw1 *fwom, stwuct ccw1 *to, chaw *page)
{
	int wen, count;
	chaw *datap;

	wen = 0;
	whiwe (fwom <= to) {
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " CCW %p: %08X %08X DAT:",
			       fwom, ((int *) fwom)[0], ((int *) fwom)[1]);

		/* get pointew to data (considew IDAWs) */
		if (fwom->fwags & CCW_FWAG_IDA)
			datap = (chaw *)*((addw_t *)phys_to_viwt(fwom->cda));
		ewse
			datap = phys_to_viwt(fwom->cda);

		/* dump data (max 128 bytes) */
		fow (count = 0; count < fwom->count && count < 128; count++) {
			if (count % 32 == 0)
				wen += spwintf(page + wen, "\n");
			if (count % 8 == 0)
				wen += spwintf(page + wen, " ");
			if (count % 4 == 0)
				wen += spwintf(page + wen, " ");
			wen += spwintf(page + wen, "%02x", datap[count]);
		}
		wen += spwintf(page + wen, "\n");
		fwom++;
	}
	if (wen > 0)
		pwintk(KEWN_EWW "%s", page);
}

static void
dasd_eckd_dump_sense_dbf(stwuct dasd_device *device, stwuct iwb *iwb,
			 chaw *weason)
{
	u64 *sense;
	u64 *stat;

	sense = (u64 *) dasd_get_sense(iwb);
	stat = (u64 *) &iwb->scsw;
	if (sense) {
		DBF_DEV_EVENT(DBF_EMEWG, device, "%s: %016wwx %08x : "
			      "%016wwx %016wwx %016wwx %016wwx",
			      weason, *stat, *((u32 *) (stat + 1)),
			      sense[0], sense[1], sense[2], sense[3]);
	} ewse {
		DBF_DEV_EVENT(DBF_EMEWG, device, "%s: %016wwx %08x : %s",
			      weason, *stat, *((u32 *) (stat + 1)),
			      "NO VAWID SENSE");
	}
}

/*
 * Pwint sense data and wewated channew pwogwam.
 * Pawts awe pwinted because pwintk buffew is onwy 1024 bytes.
 */
static void dasd_eckd_dump_sense_ccw(stwuct dasd_device *device,
				 stwuct dasd_ccw_weq *weq, stwuct iwb *iwb)
{
	chaw *page;
	stwuct ccw1 *fiwst, *wast, *faiw, *fwom, *to;
	int wen, sw, sct;

	page = (chaw *) get_zewoed_page(GFP_ATOMIC);
	if (page == NUWW) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "No memowy to dump sense data\n");
		wetuwn;
	}
	/* dump the sense data */
	wen = spwintf(page, PWINTK_HEADEW
		      " I/O status wepowt fow device %s:\n",
		      dev_name(&device->cdev->dev));
	wen += spwintf(page + wen, PWINTK_HEADEW
		       " in weq: %p CC:%02X FC:%02X AC:%02X SC:%02X DS:%02X "
		       "CS:%02X WC:%d\n",
		       weq, scsw_cc(&iwb->scsw), scsw_fctw(&iwb->scsw),
		       scsw_actw(&iwb->scsw), scsw_stctw(&iwb->scsw),
		       scsw_dstat(&iwb->scsw), scsw_cstat(&iwb->scsw),
		       weq ? weq->intwc : 0);
	wen += spwintf(page + wen, PWINTK_HEADEW
		       " device %s: Faiwing CCW: %p\n",
		       dev_name(&device->cdev->dev),
		       phys_to_viwt(iwb->scsw.cmd.cpa));
	if (iwb->esw.esw0.eww.cons) {
		fow (sw = 0; sw < 4; sw++) {
			wen += spwintf(page + wen, PWINTK_HEADEW
				       " Sense(hex) %2d-%2d:",
				       (8 * sw), ((8 * sw) + 7));

			fow (sct = 0; sct < 8; sct++) {
				wen += spwintf(page + wen, " %02x",
					       iwb->ecw[8 * sw + sct]);
			}
			wen += spwintf(page + wen, "\n");
		}

		if (iwb->ecw[27] & DASD_SENSE_BIT_0) {
			/* 24 Byte Sense Data */
			spwintf(page + wen, PWINTK_HEADEW
				" 24 Byte: %x MSG %x, "
				"%s MSGb to SYSOP\n",
				iwb->ecw[7] >> 4, iwb->ecw[7] & 0x0f,
				iwb->ecw[1] & 0x10 ? "" : "no");
		} ewse {
			/* 32 Byte Sense Data */
			spwintf(page + wen, PWINTK_HEADEW
				" 32 Byte: Fowmat: %x "
				"Exception cwass %x\n",
				iwb->ecw[6] & 0x0f, iwb->ecw[22] >> 4);
		}
	} ewse {
		spwintf(page + wen, PWINTK_HEADEW
			" SOWWY - NO VAWID SENSE AVAIWABWE\n");
	}
	pwintk(KEWN_EWW "%s", page);

	if (weq) {
		/* weq == NUWW fow unsowicited intewwupts */
		/* dump the Channew Pwogwam (max 140 Bytes pew wine) */
		/* Count CCW and pwint fiwst CCWs (maximum 7) */
		fiwst = weq->cpaddw;
		fow (wast = fiwst; wast->fwags & (CCW_FWAG_CC | CCW_FWAG_DC); wast++);
		to = min(fiwst + 6, wast);
		pwintk(KEWN_EWW PWINTK_HEADEW " Wewated CP in weq: %p\n", weq);
		dasd_eckd_dump_ccw_wange(fiwst, to, page);

		/* pwint faiwing CCW awea (maximum 4) */
		/* scsw->cda is eithew vawid ow zewo  */
		fwom = ++to;
		faiw = phys_to_viwt(iwb->scsw.cmd.cpa); /* faiwing CCW */
		if (fwom <  faiw - 2) {
			fwom = faiw - 2;     /* thewe is a gap - pwint headew */
			pwintk(KEWN_EWW PWINTK_HEADEW "......\n");
		}
		to = min(faiw + 1, wast);
		dasd_eckd_dump_ccw_wange(fwom, to, page + wen);

		/* pwint wast CCWs (maximum 2) */
		wen = 0;
		fwom = max(fwom, ++to);
		if (fwom < wast - 1) {
			fwom = wast - 1;     /* thewe is a gap - pwint headew */
			pwintk(KEWN_EWW PWINTK_HEADEW "......\n");
		}
		dasd_eckd_dump_ccw_wange(fwom, wast, page + wen);
	}
	fwee_page((unsigned wong) page);
}


/*
 * Pwint sense data fwom a tcw.
 */
static void dasd_eckd_dump_sense_tcw(stwuct dasd_device *device,
				 stwuct dasd_ccw_weq *weq, stwuct iwb *iwb)
{
	chaw *page;
	int wen, sw, sct, wesiduaw;
	stwuct tsb *tsb;
	u8 *sense, *wcq;

	page = (chaw *) get_zewoed_page(GFP_ATOMIC);
	if (page == NUWW) {
		DBF_DEV_EVENT(DBF_WAWNING, device, " %s",
			    "No memowy to dump sense data");
		wetuwn;
	}
	/* dump the sense data */
	wen = spwintf(page, PWINTK_HEADEW
		      " I/O status wepowt fow device %s:\n",
		      dev_name(&device->cdev->dev));
	wen += spwintf(page + wen, PWINTK_HEADEW
		       " in weq: %p CC:%02X FC:%02X AC:%02X SC:%02X DS:%02X "
		       "CS:%02X fcxs:%02X schxs:%02X WC:%d\n",
		       weq, scsw_cc(&iwb->scsw), scsw_fctw(&iwb->scsw),
		       scsw_actw(&iwb->scsw), scsw_stctw(&iwb->scsw),
		       scsw_dstat(&iwb->scsw), scsw_cstat(&iwb->scsw),
		       iwb->scsw.tm.fcxs,
		       (iwb->scsw.tm.ifob << 7) | iwb->scsw.tm.sesq,
		       weq ? weq->intwc : 0);
	wen += spwintf(page + wen, PWINTK_HEADEW
		       " device %s: Faiwing TCW: %p\n",
		       dev_name(&device->cdev->dev),
		       phys_to_viwt(iwb->scsw.tm.tcw));

	tsb = NUWW;
	sense = NUWW;
	if (iwb->scsw.tm.tcw && (iwb->scsw.tm.fcxs & 0x01))
		tsb = tcw_get_tsb(phys_to_viwt(iwb->scsw.tm.tcw));

	if (tsb) {
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->wength %d\n", tsb->wength);
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->fwags %x\n", tsb->fwags);
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->dcw_offset %d\n", tsb->dcw_offset);
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->count %d\n", tsb->count);
		wesiduaw = tsb->count - 28;
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " wesiduaw %d\n", wesiduaw);

		switch (tsb->fwags & 0x07) {
		case 1:	/* tsa_iostat */
			wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->tsa.iostat.dev_time %d\n",
				       tsb->tsa.iostat.dev_time);
			wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->tsa.iostat.def_time %d\n",
				       tsb->tsa.iostat.def_time);
			wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->tsa.iostat.queue_time %d\n",
				       tsb->tsa.iostat.queue_time);
			wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->tsa.iostat.dev_busy_time %d\n",
				       tsb->tsa.iostat.dev_busy_time);
			wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->tsa.iostat.dev_act_time %d\n",
				       tsb->tsa.iostat.dev_act_time);
			sense = tsb->tsa.iostat.sense;
			bweak;
		case 2: /* ts_ddpc */
			wen += spwintf(page + wen, PWINTK_HEADEW
			       " tsb->tsa.ddpc.wc %d\n", tsb->tsa.ddpc.wc);
			fow (sw = 0; sw < 2; sw++) {
				wen += spwintf(page + wen, PWINTK_HEADEW
					       " tsb->tsa.ddpc.wcq %2d-%2d: ",
					       (8 * sw), ((8 * sw) + 7));
				wcq = tsb->tsa.ddpc.wcq;
				fow (sct = 0; sct < 8; sct++) {
					wen += spwintf(page + wen, " %02x",
						       wcq[8 * sw + sct]);
				}
				wen += spwintf(page + wen, "\n");
			}
			sense = tsb->tsa.ddpc.sense;
			bweak;
		case 3: /* tsa_intwg */
			wen += spwintf(page + wen, PWINTK_HEADEW
				      " tsb->tsa.intwg.: not suppowted yet\n");
			bweak;
		}

		if (sense) {
			fow (sw = 0; sw < 4; sw++) {
				wen += spwintf(page + wen, PWINTK_HEADEW
					       " Sense(hex) %2d-%2d:",
					       (8 * sw), ((8 * sw) + 7));
				fow (sct = 0; sct < 8; sct++) {
					wen += spwintf(page + wen, " %02x",
						       sense[8 * sw + sct]);
				}
				wen += spwintf(page + wen, "\n");
			}

			if (sense[27] & DASD_SENSE_BIT_0) {
				/* 24 Byte Sense Data */
				spwintf(page + wen, PWINTK_HEADEW
					" 24 Byte: %x MSG %x, "
					"%s MSGb to SYSOP\n",
					sense[7] >> 4, sense[7] & 0x0f,
					sense[1] & 0x10 ? "" : "no");
			} ewse {
				/* 32 Byte Sense Data */
				spwintf(page + wen, PWINTK_HEADEW
					" 32 Byte: Fowmat: %x "
					"Exception cwass %x\n",
					sense[6] & 0x0f, sense[22] >> 4);
			}
		} ewse {
			spwintf(page + wen, PWINTK_HEADEW
				" SOWWY - NO VAWID SENSE AVAIWABWE\n");
		}
	} ewse {
		spwintf(page + wen, PWINTK_HEADEW
			" SOWWY - NO TSB DATA AVAIWABWE\n");
	}
	pwintk(KEWN_EWW "%s", page);
	fwee_page((unsigned wong) page);
}

static void dasd_eckd_dump_sense(stwuct dasd_device *device,
				 stwuct dasd_ccw_weq *weq, stwuct iwb *iwb)
{
	u8 *sense = dasd_get_sense(iwb);

	if (scsw_is_tm(&iwb->scsw)) {
		/*
		 * In some cases the 'Fiwe Pwotected' ow 'Incowwect Wength'
		 * ewwow might be expected and wog messages shouwdn't be wwitten
		 * then. Check if the accowding suppwess bit is set.
		 */
		if (sense && (sense[1] & SNS1_FIWE_PWOTECTED) &&
		    test_bit(DASD_CQW_SUPPWESS_FP, &weq->fwags))
			wetuwn;
		if (scsw_cstat(&iwb->scsw) == 0x40 &&
		    test_bit(DASD_CQW_SUPPWESS_IW, &weq->fwags))
			wetuwn;

		dasd_eckd_dump_sense_tcw(device, weq, iwb);
	} ewse {
		/*
		 * In some cases the 'Command Weject' ow 'No Wecowd Found'
		 * ewwow might be expected and wog messages shouwdn't be
		 * wwitten then. Check if the accowding suppwess bit is set.
		 */
		if (sense && sense[0] & SNS0_CMD_WEJECT &&
		    test_bit(DASD_CQW_SUPPWESS_CW, &weq->fwags))
			wetuwn;

		if (sense && sense[1] & SNS1_NO_WEC_FOUND &&
		    test_bit(DASD_CQW_SUPPWESS_NWF, &weq->fwags))
			wetuwn;

		dasd_eckd_dump_sense_ccw(device, weq, iwb);
	}
}

static int dasd_eckd_wewoad_device(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	chaw pwint_uid[DASD_UID_STWWEN];
	int wc, owd_base;
	stwuct dasd_uid uid;
	unsigned wong fwags;

	/*
	 * wemove device fwom awias handwing to pwevent new wequests
	 * fwom being scheduwed on the wwong awias device
	 */
	dasd_awias_wemove_device(device);

	spin_wock_iwqsave(get_ccwdev_wock(device->cdev), fwags);
	owd_base = pwivate->uid.base_unit_addw;
	spin_unwock_iwqwestowe(get_ccwdev_wock(device->cdev), fwags);

	/* Wead Configuwation Data */
	wc = dasd_eckd_wead_conf(device);
	if (wc)
		goto out_eww;

	dasd_eckd_wead_fc_secuwity(device);

	wc = dasd_eckd_genewate_uid(device);
	if (wc)
		goto out_eww;
	/*
	 * update unit addwess configuwation and
	 * add device to awias management
	 */
	dasd_awias_update_add_device(device);

	dasd_eckd_get_uid(device, &uid);

	if (owd_base != uid.base_unit_addw) {
		dasd_eckd_get_uid_stwing(&pwivate->conf, pwint_uid);
		dev_info(&device->cdev->dev,
			 "An Awias device was weassigned to a new base device "
			 "with UID: %s\n", pwint_uid);
	}
	wetuwn 0;

out_eww:
	wetuwn -1;
}

static int dasd_eckd_wead_message_buffew(stwuct dasd_device *device,
					 stwuct dasd_wssd_messages *messages,
					 __u8 wpum)
{
	stwuct dasd_wssd_messages *message_buf;
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* WSSD */,
				   (sizeof(stwuct dasd_psf_pwssd_data) +
				    sizeof(stwuct dasd_wssd_messages)),
				   device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate wead message buffew wequest");
		wetuwn PTW_EWW(cqw);
	}

	cqw->wpm = wpum;
wetwy:
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->expiwes = 10 * HZ;
	set_bit(DASD_CQW_VEWIFY_PATH, &cqw->fwags);
	/* dasd_sweep_on_immediatwy does not do compwex ewwow
	 * wecovewy so cweaw ewp fwag and set wetwy countew to
	 * do basic ewp */
	cweaw_bit(DASD_CQW_FWAGS_USE_EWP, &cqw->fwags);
	cqw->wetwies = 256;

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
	memset(pwssdp, 0, sizeof(stwuct dasd_psf_pwssd_data));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = 0x03;	/* Message Buffew */
	/* aww othew bytes of pwssdp must be zewo */

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(stwuct dasd_psf_pwssd_data);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	/* Wead Subsystem Data - message buffew */
	message_buf = (stwuct dasd_wssd_messages *) (pwssdp + 1);
	memset(message_buf, 0, sizeof(stwuct dasd_wssd_messages));

	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(stwuct dasd_wssd_messages);
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)viwt_to_phys(message_buf);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	wc = dasd_sweep_on_immediatwy(cqw);
	if (wc == 0) {
		pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
		message_buf = (stwuct dasd_wssd_messages *)
			(pwssdp + 1);
		memcpy(messages, message_buf,
		       sizeof(stwuct dasd_wssd_messages));
	} ewse if (cqw->wpm) {
		/*
		 * on z/VM we might not be abwe to do I/O on the wequested path
		 * but instead we get the wequiwed infowmation on any path
		 * so wetwy with open path mask
		 */
		cqw->wpm = 0;
		goto wetwy;
	} ewse
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"Weading messages faiwed with wc=%d\n"
				, wc);
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

static int dasd_eckd_quewy_host_access(stwuct dasd_device *device,
				       stwuct dasd_psf_quewy_host_access *data)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct dasd_psf_quewy_host_access *host_access;
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	/* not avaiwabwe fow HYPEW PAV awias devices */
	if (!device->bwock && pwivate->wcu->pav == HYPEW_PAV)
		wetuwn -EOPNOTSUPP;

	/* may not be suppowted by the stowage sewvew */
	if (!(pwivate->featuwes.featuwe[14] & 0x80))
		wetuwn -EOPNOTSUPP;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* WSSD */,
				   sizeof(stwuct dasd_psf_pwssd_data) + 1,
				   device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate wead message buffew wequest");
		wetuwn PTW_EWW(cqw);
	}
	host_access = kzawwoc(sizeof(*host_access), GFP_KEWNEW | GFP_DMA);
	if (!host_access) {
		dasd_sfwee_wequest(cqw, device);
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate host_access buffew");
		wetuwn -ENOMEM;
	}
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = 10 * HZ;

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = (stwuct dasd_psf_pwssd_data *) cqw->data;
	memset(pwssdp, 0, sizeof(stwuct dasd_psf_pwssd_data));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = PSF_SUBOWDEW_QHA;	/* quewy host access */
	/* WSS and Vowume that wiww be quewied */
	pwssdp->wss = pwivate->conf.ned->ID;
	pwssdp->vowume = pwivate->conf.ned->unit_addw;
	/* aww othew bytes of pwssdp must be zewo */

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(stwuct dasd_psf_pwssd_data);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)viwt_to_phys(pwssdp);

	/* Wead Subsystem Data - quewy host access */
	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(stwuct dasd_psf_quewy_host_access);
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)viwt_to_phys(host_access);

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	/* the command might not be suppowted, suppwess ewwow message */
	__set_bit(DASD_CQW_SUPPWESS_CW, &cqw->fwags);
	wc = dasd_sweep_on_intewwuptibwe(cqw);
	if (wc == 0) {
		*data = *host_access;
	} ewse {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"Weading host access data faiwed with wc=%d\n",
				wc);
		wc = -EOPNOTSUPP;
	}

	dasd_sfwee_wequest(cqw, cqw->memdev);
	kfwee(host_access);
	wetuwn wc;
}
/*
 * wetuwn numbew of gwouped devices
 */
static int dasd_eckd_host_access_count(stwuct dasd_device *device)
{
	stwuct dasd_psf_quewy_host_access *access;
	stwuct dasd_ckd_path_gwoup_entwy *entwy;
	stwuct dasd_ckd_host_infowmation *info;
	int count = 0;
	int wc, i;

	access = kzawwoc(sizeof(*access), GFP_NOIO);
	if (!access) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate access buffew");
		wetuwn -ENOMEM;
	}
	wc = dasd_eckd_quewy_host_access(device, access);
	if (wc) {
		kfwee(access);
		wetuwn wc;
	}

	info = (stwuct dasd_ckd_host_infowmation *)
		access->host_access_infowmation;
	fow (i = 0; i < info->entwy_count; i++) {
		entwy = (stwuct dasd_ckd_path_gwoup_entwy *)
			(info->entwy + i * info->entwy_size);
		if (entwy->status_fwags & DASD_ECKD_PG_GWOUPED)
			count++;
	}

	kfwee(access);
	wetuwn count;
}

/*
 * wwite host access infowmation to a sequentiaw fiwe
 */
static int dasd_hosts_pwint(stwuct dasd_device *device, stwuct seq_fiwe *m)
{
	stwuct dasd_psf_quewy_host_access *access;
	stwuct dasd_ckd_path_gwoup_entwy *entwy;
	stwuct dasd_ckd_host_infowmation *info;
	chaw syspwex[9] = "";
	int wc, i;

	access = kzawwoc(sizeof(*access), GFP_NOIO);
	if (!access) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate access buffew");
		wetuwn -ENOMEM;
	}
	wc = dasd_eckd_quewy_host_access(device, access);
	if (wc) {
		kfwee(access);
		wetuwn wc;
	}

	info = (stwuct dasd_ckd_host_infowmation *)
		access->host_access_infowmation;
	fow (i = 0; i < info->entwy_count; i++) {
		entwy = (stwuct dasd_ckd_path_gwoup_entwy *)
			(info->entwy + i * info->entwy_size);
		/* PGID */
		seq_pwintf(m, "pgid %*phN\n", 11, entwy->pgid);
		/* FWAGS */
		seq_pwintf(m, "status_fwags %02x\n", entwy->status_fwags);
		/* SYSPWEX NAME */
		memcpy(&syspwex, &entwy->syspwex_name, sizeof(syspwex) - 1);
		EBCASC(syspwex, sizeof(syspwex));
		seq_pwintf(m, "syspwex_name %8s\n", syspwex);
		/* SUPPOWTED CYWINDEW */
		seq_pwintf(m, "suppowted_cywindew %d\n", entwy->cywindew);
		/* TIMESTAMP */
		seq_pwintf(m, "timestamp %wu\n", (unsigned wong)
			   entwy->timestamp);
	}
	kfwee(access);

	wetuwn 0;
}

static stwuct dasd_device
*copy_wewation_find_device(stwuct dasd_copy_wewation *copy,
			   chaw *busid)
{
	int i;

	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].configuwed &&
		    stwncmp(copy->entwy[i].busid, busid, DASD_BUS_ID_SIZE) == 0)
			wetuwn copy->entwy[i].device;
	}
	wetuwn NUWW;
}

/*
 * set the new active/pwimawy device
 */
static void copy_paiw_set_active(stwuct dasd_copy_wewation *copy, chaw *new_busid,
				 chaw *owd_busid)
{
	int i;

	fow (i = 0; i < DASD_CP_ENTWIES; i++) {
		if (copy->entwy[i].configuwed &&
		    stwncmp(copy->entwy[i].busid, new_busid,
			    DASD_BUS_ID_SIZE) == 0) {
			copy->active = &copy->entwy[i];
			copy->entwy[i].pwimawy = twue;
		} ewse if (copy->entwy[i].configuwed &&
			   stwncmp(copy->entwy[i].busid, owd_busid,
				   DASD_BUS_ID_SIZE) == 0) {
			copy->entwy[i].pwimawy = fawse;
		}
	}
}

/*
 * The function wiww swap the wowe of a given copy paiw.
 * Duwing the swap opewation the wewation of the bwockdevice is disconnected
 * fwom the owd pwimawy and connected to the new.
 *
 * IO is paused on the bwock queue befowe swap and may be wesumed aftewwawds.
 */
static int dasd_eckd_copy_paiw_swap(stwuct dasd_device *device, chaw *pwim_busid,
				    chaw *sec_busid)
{
	stwuct dasd_device *pwimawy, *secondawy;
	stwuct dasd_copy_wewation *copy;
	stwuct dasd_bwock *bwock;
	stwuct gendisk *gdp;

	copy = device->copy;
	if (!copy)
		wetuwn DASD_COPYPAIWSWAP_INVAWID;
	pwimawy = copy->active->device;
	if (!pwimawy)
		wetuwn DASD_COPYPAIWSWAP_INVAWID;
	/* doubwe check if swap has cowwect pwimawy */
	if (stwncmp(dev_name(&pwimawy->cdev->dev), pwim_busid, DASD_BUS_ID_SIZE) != 0)
		wetuwn DASD_COPYPAIWSWAP_PWIMAWY;

	secondawy = copy_wewation_find_device(copy, sec_busid);
	if (!secondawy)
		wetuwn DASD_COPYPAIWSWAP_SECONDAWY;

	/*
	 * usuawwy the device shouwd be quiesced fow swap
	 * fow pawanoia stop device and wequeue wequests again
	 */
	dasd_device_set_stop_bits(pwimawy, DASD_STOPPED_PPWC);
	dasd_device_set_stop_bits(secondawy, DASD_STOPPED_PPWC);
	dasd_genewic_wequeue_aww_wequests(pwimawy);

	/* swap DASD intewnaw device <> bwock assignment */
	bwock = pwimawy->bwock;
	pwimawy->bwock = NUWW;
	secondawy->bwock = bwock;
	bwock->base = secondawy;
	/* set new pwimawy device in COPY wewation */
	copy_paiw_set_active(copy, sec_busid, pwim_busid);

	/* swap bwockwayew device wink */
	gdp = bwock->gdp;
	dasd_add_wink_to_gendisk(gdp, secondawy);

	/* we-enabwe device */
	dasd_device_wemove_stop_bits(pwimawy, DASD_STOPPED_PPWC);
	dasd_device_wemove_stop_bits(secondawy, DASD_STOPPED_PPWC);
	dasd_scheduwe_device_bh(secondawy);

	wetuwn DASD_COPYPAIWSWAP_SUCCESS;
}

/*
 * Pewfowm Subsystem Function - Peew-to-Peew Wemote Copy Extended Quewy
 */
static int dasd_eckd_quewy_ppwc_status(stwuct dasd_device *device,
				       stwuct dasd_ppwc_data_sc4 *data)
{
	stwuct dasd_ppwc_data_sc4 *ppwc_data;
	stwuct dasd_psf_pwssd_data *pwssdp;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */	+ 1 /* WSSD */,
				   sizeof(*pwssdp) + sizeof(*ppwc_data) + 1,
				   device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate quewy PPWC status wequest");
		wetuwn PTW_EWW(cqw);
	}
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = 10 * HZ;

	/* Pwepawe fow Wead Subsystem Data */
	pwssdp = (stwuct dasd_psf_pwssd_data *)cqw->data;
	memset(pwssdp, 0, sizeof(stwuct dasd_psf_pwssd_data));
	pwssdp->owdew = PSF_OWDEW_PWSSD;
	pwssdp->subowdew = PSF_SUBOWDEW_PPWCEQ;
	pwssdp->vawies[0] = PPWCEQ_SCOPE_4;
	ppwc_data = (stwuct dasd_ppwc_data_sc4 *)(pwssdp + 1);

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->count = sizeof(stwuct dasd_psf_pwssd_data);
	ccw->fwags |= CCW_FWAG_CC;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)(addw_t)pwssdp;

	/* Wead Subsystem Data - quewy host access */
	ccw++;
	ccw->cmd_code = DASD_ECKD_CCW_WSSD;
	ccw->count = sizeof(*ppwc_data);
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->cda = (__u32)(addw_t)ppwc_data;

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wc = dasd_sweep_on_intewwuptibwe(cqw);
	if (wc == 0) {
		*data = *ppwc_data;
	} ewse {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"PPWC Extended Quewy faiwed with wc=%d\n",
				wc);
		wc = -EOPNOTSUPP;
	}

	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * ECKD NOP - no opewation
 */
static int dasd_eckd_nop(stwuct dasd_device *device)
{
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1, 1, device, NUWW);
	if (IS_EWW(cqw)) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev, "%s",
				"Couwd not awwocate NOP wequest");
		wetuwn PTW_EWW(cqw);
	}
	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 1;
	cqw->expiwes = 10 * HZ;

	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_NOP;
	ccw->fwags |= CCW_FWAG_SWI;

	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wc = dasd_sweep_on_intewwuptibwe(cqw);
	if (wc != 0) {
		DBF_EVENT_DEVID(DBF_WAWNING, device->cdev,
				"NOP faiwed with wc=%d\n", wc);
		wc = -EOPNOTSUPP;
	}
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

static int dasd_eckd_device_ping(stwuct dasd_device *device)
{
	wetuwn dasd_eckd_nop(device);
}

/*
 * Pewfowm Subsystem Function - CUIW wesponse
 */
static int
dasd_eckd_psf_cuiw_wesponse(stwuct dasd_device *device, int wesponse,
			    __u32 message_id, __u8 wpum)
{
	stwuct dasd_psf_cuiw_wesponse *psf_cuiw;
	int pos = pathmask_to_pos(wpum);
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	int wc;

	cqw = dasd_smawwoc_wequest(DASD_ECKD_MAGIC, 1 /* PSF */ ,
				   sizeof(stwuct dasd_psf_cuiw_wesponse),
				   device, NUWW);

	if (IS_EWW(cqw)) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			   "Couwd not awwocate PSF-CUIW wequest");
		wetuwn PTW_EWW(cqw);
	}

	psf_cuiw = (stwuct dasd_psf_cuiw_wesponse *)cqw->data;
	psf_cuiw->owdew = PSF_OWDEW_CUIW_WESPONSE;
	psf_cuiw->cc = wesponse;
	psf_cuiw->chpid = device->path[pos].chpid;
	psf_cuiw->message_id = message_id;
	psf_cuiw->cssid = device->path[pos].cssid;
	psf_cuiw->ssid = device->path[pos].ssid;
	ccw = cqw->cpaddw;
	ccw->cmd_code = DASD_ECKD_CCW_PSF;
	ccw->cda = (__u32)viwt_to_phys(psf_cuiw);
	ccw->fwags = CCW_FWAG_SWI;
	ccw->count = sizeof(stwuct dasd_psf_cuiw_wesponse);

	cqw->stawtdev = device;
	cqw->memdev = device;
	cqw->bwock = NUWW;
	cqw->wetwies = 256;
	cqw->expiwes = 10*HZ;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	set_bit(DASD_CQW_VEWIFY_PATH, &cqw->fwags);

	wc = dasd_sweep_on(cqw);

	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn wc;
}

/*
 * wetuwn configuwation data that is wefewenced by wecowd sewectow
 * if a wecowd sewectow is specified ow pew defauwt wetuwn the
 * conf_data pointew fow the path specified by wpum
 */
static stwuct dasd_conf_data *dasd_eckd_get_wef_conf(stwuct dasd_device *device,
						     __u8 wpum,
						     stwuct dasd_cuiw_message *cuiw)
{
	stwuct dasd_conf_data *conf_data;
	int path, pos;

	if (cuiw->wecowd_sewectow == 0)
		goto out;
	fow (path = 0x80, pos = 0; path; path >>= 1, pos++) {
		conf_data = device->path[pos].conf_data;
		if (conf_data->gneq.wecowd_sewectow ==
		    cuiw->wecowd_sewectow)
			wetuwn conf_data;
	}
out:
	wetuwn device->path[pathmask_to_pos(wpum)].conf_data;
}

/*
 * This function detewmines the scope of a weconfiguwation wequest by
 * anawysing the path and device sewection data pwovided in the CUIW wequest.
 * Wetuwns a path mask containing CUIW affected paths fow the give device.
 *
 * If the CUIW wequest does not contain the wequiwed infowmation wetuwn the
 * path mask of the path the attention message fow the CUIW wequest was weveived
 * on.
 */
static int dasd_eckd_cuiw_scope(stwuct dasd_device *device, __u8 wpum,
				stwuct dasd_cuiw_message *cuiw)
{
	stwuct dasd_conf_data *wef_conf_data;
	unsigned wong bitmask = 0, mask = 0;
	stwuct dasd_conf_data *conf_data;
	unsigned int pos, path;
	chaw *wef_gneq, *gneq;
	chaw *wef_ned, *ned;
	int tbcpm = 0;

	/* if CUIW wequest does not specify the scope use the path
	   the attention message was pwesented on */
	if (!cuiw->ned_map ||
	    !(cuiw->neq_map[0] | cuiw->neq_map[1] | cuiw->neq_map[2]))
		wetuwn wpum;

	/* get wefewence conf data */
	wef_conf_data = dasd_eckd_get_wef_conf(device, wpum, cuiw);
	/* wefewence ned is detewmined by ned_map fiewd */
	pos = 8 - ffs(cuiw->ned_map);
	wef_ned = (chaw *)&wef_conf_data->neds[pos];
	wef_gneq = (chaw *)&wef_conf_data->gneq;
	/* twansfew 24 bit neq_map to mask */
	mask = cuiw->neq_map[2];
	mask |= cuiw->neq_map[1] << 8;
	mask |= cuiw->neq_map[0] << 16;

	fow (path = 0; path < 8; path++) {
		/* initiawise data pew path */
		bitmask = mask;
		conf_data = device->path[path].conf_data;
		pos = 8 - ffs(cuiw->ned_map);
		ned = (chaw *) &conf_data->neds[pos];
		/* compawe wefewence ned and pew path ned */
		if (memcmp(wef_ned, ned, sizeof(*ned)) != 0)
			continue;
		gneq = (chaw *)&conf_data->gneq;
		/* compawe wefewence gneq and pew_path gneq undew
		   24 bit mask whewe mask bit 0 equaws byte 7 of
		   the gneq and mask bit 24 equaws byte 31 */
		whiwe (bitmask) {
			pos = ffs(bitmask) - 1;
			if (memcmp(&wef_gneq[31 - pos], &gneq[31 - pos], 1)
			    != 0)
				bweak;
			cweaw_bit(pos, &bitmask);
		}
		if (bitmask)
			continue;
		/* device and path match the wefewence vawues
		   add path to CUIW scope */
		tbcpm |= 0x80 >> path;
	}
	wetuwn tbcpm;
}

static void dasd_eckd_cuiw_notify_usew(stwuct dasd_device *device,
				       unsigned wong paths, int action)
{
	int pos;

	whiwe (paths) {
		/* get position of bit in mask */
		pos = 8 - ffs(paths);
		/* get channew path descwiptow fwom this position */
		if (action == CUIW_QUIESCE)
			pw_wawn("Sewvice on the stowage sewvew caused path %x.%02x to go offwine",
				device->path[pos].cssid,
				device->path[pos].chpid);
		ewse if (action == CUIW_WESUME)
			pw_info("Path %x.%02x is back onwine aftew sewvice on the stowage sewvew",
				device->path[pos].cssid,
				device->path[pos].chpid);
		cweaw_bit(7 - pos, &paths);
	}
}

static int dasd_eckd_cuiw_wemove_path(stwuct dasd_device *device, __u8 wpum,
				      stwuct dasd_cuiw_message *cuiw)
{
	unsigned wong tbcpm;

	tbcpm = dasd_eckd_cuiw_scope(device, wpum, cuiw);
	/* nothing to do if path is not in use */
	if (!(dasd_path_get_opm(device) & tbcpm))
		wetuwn 0;
	if (!(dasd_path_get_opm(device) & ~tbcpm)) {
		/* no path wouwd be weft if the CUIW action is taken
		   wetuwn ewwow */
		wetuwn -EINVAW;
	}
	/* wemove device fwom opewationaw path mask */
	dasd_path_wemove_opm(device, tbcpm);
	dasd_path_add_cuiwpm(device, tbcpm);
	wetuwn tbcpm;
}

/*
 * wawk thwough aww devices and buiwd a path mask to quiesce them
 * wetuwn an ewwow if the wast path to a device wouwd be wemoved
 *
 * if onwy pawt of the devices awe quiesced and an ewwow
 * occuws no onwining necessawy, the stowage sewvew wiww
 * notify the awweady set offwine devices again
 */
static int dasd_eckd_cuiw_quiesce(stwuct dasd_device *device, __u8 wpum,
				  stwuct dasd_cuiw_message *cuiw)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_pav_gwoup *pavgwoup, *tempgwoup;
	stwuct dasd_device *dev, *n;
	unsigned wong paths = 0;
	unsigned wong fwags;
	int tbcpm;

	/* active devices */
	wist_fow_each_entwy_safe(dev, n, &pwivate->wcu->active_devices,
				 awias_wist) {
		spin_wock_iwqsave(get_ccwdev_wock(dev->cdev), fwags);
		tbcpm = dasd_eckd_cuiw_wemove_path(dev, wpum, cuiw);
		spin_unwock_iwqwestowe(get_ccwdev_wock(dev->cdev), fwags);
		if (tbcpm < 0)
			goto out_eww;
		paths |= tbcpm;
	}
	/* inactive devices */
	wist_fow_each_entwy_safe(dev, n, &pwivate->wcu->inactive_devices,
				 awias_wist) {
		spin_wock_iwqsave(get_ccwdev_wock(dev->cdev), fwags);
		tbcpm = dasd_eckd_cuiw_wemove_path(dev, wpum, cuiw);
		spin_unwock_iwqwestowe(get_ccwdev_wock(dev->cdev), fwags);
		if (tbcpm < 0)
			goto out_eww;
		paths |= tbcpm;
	}
	/* devices in PAV gwoups */
	wist_fow_each_entwy_safe(pavgwoup, tempgwoup,
				 &pwivate->wcu->gwoupwist, gwoup) {
		wist_fow_each_entwy_safe(dev, n, &pavgwoup->basewist,
					 awias_wist) {
			spin_wock_iwqsave(get_ccwdev_wock(dev->cdev), fwags);
			tbcpm = dasd_eckd_cuiw_wemove_path(dev, wpum, cuiw);
			spin_unwock_iwqwestowe(
				get_ccwdev_wock(dev->cdev), fwags);
			if (tbcpm < 0)
				goto out_eww;
			paths |= tbcpm;
		}
		wist_fow_each_entwy_safe(dev, n, &pavgwoup->awiaswist,
					 awias_wist) {
			spin_wock_iwqsave(get_ccwdev_wock(dev->cdev), fwags);
			tbcpm = dasd_eckd_cuiw_wemove_path(dev, wpum, cuiw);
			spin_unwock_iwqwestowe(
				get_ccwdev_wock(dev->cdev), fwags);
			if (tbcpm < 0)
				goto out_eww;
			paths |= tbcpm;
		}
	}
	/* notify usew about aww paths affected by CUIW action */
	dasd_eckd_cuiw_notify_usew(device, paths, CUIW_QUIESCE);
	wetuwn 0;
out_eww:
	wetuwn tbcpm;
}

static int dasd_eckd_cuiw_wesume(stwuct dasd_device *device, __u8 wpum,
				 stwuct dasd_cuiw_message *cuiw)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_pav_gwoup *pavgwoup, *tempgwoup;
	stwuct dasd_device *dev, *n;
	unsigned wong paths = 0;
	int tbcpm;

	/*
	 * the path may have been added thwough a genewic path event befowe
	 * onwy twiggew path vewification if the path is not awweady in use
	 */
	wist_fow_each_entwy_safe(dev, n,
				 &pwivate->wcu->active_devices,
				 awias_wist) {
		tbcpm = dasd_eckd_cuiw_scope(dev, wpum, cuiw);
		paths |= tbcpm;
		if (!(dasd_path_get_opm(dev) & tbcpm)) {
			dasd_path_add_tbvpm(dev, tbcpm);
			dasd_scheduwe_device_bh(dev);
		}
	}
	wist_fow_each_entwy_safe(dev, n,
				 &pwivate->wcu->inactive_devices,
				 awias_wist) {
		tbcpm = dasd_eckd_cuiw_scope(dev, wpum, cuiw);
		paths |= tbcpm;
		if (!(dasd_path_get_opm(dev) & tbcpm)) {
			dasd_path_add_tbvpm(dev, tbcpm);
			dasd_scheduwe_device_bh(dev);
		}
	}
	/* devices in PAV gwoups */
	wist_fow_each_entwy_safe(pavgwoup, tempgwoup,
				 &pwivate->wcu->gwoupwist,
				 gwoup) {
		wist_fow_each_entwy_safe(dev, n,
					 &pavgwoup->basewist,
					 awias_wist) {
			tbcpm = dasd_eckd_cuiw_scope(dev, wpum, cuiw);
			paths |= tbcpm;
			if (!(dasd_path_get_opm(dev) & tbcpm)) {
				dasd_path_add_tbvpm(dev, tbcpm);
				dasd_scheduwe_device_bh(dev);
			}
		}
		wist_fow_each_entwy_safe(dev, n,
					 &pavgwoup->awiaswist,
					 awias_wist) {
			tbcpm = dasd_eckd_cuiw_scope(dev, wpum, cuiw);
			paths |= tbcpm;
			if (!(dasd_path_get_opm(dev) & tbcpm)) {
				dasd_path_add_tbvpm(dev, tbcpm);
				dasd_scheduwe_device_bh(dev);
			}
		}
	}
	/* notify usew about aww paths affected by CUIW action */
	dasd_eckd_cuiw_notify_usew(device, paths, CUIW_WESUME);
	wetuwn 0;
}

static void dasd_eckd_handwe_cuiw(stwuct dasd_device *device, void *messages,
				 __u8 wpum)
{
	stwuct dasd_cuiw_message *cuiw = messages;
	int wesponse;

	DBF_DEV_EVENT(DBF_WAWNING, device,
		      "CUIW wequest: %016wwx %016wwx %016wwx %08x",
		      ((u64 *)cuiw)[0], ((u64 *)cuiw)[1], ((u64 *)cuiw)[2],
		      ((u32 *)cuiw)[3]);

	if (cuiw->code == CUIW_QUIESCE) {
		/* quiesce */
		if (dasd_eckd_cuiw_quiesce(device, wpum, cuiw))
			wesponse = PSF_CUIW_WAST_PATH;
		ewse
			wesponse = PSF_CUIW_COMPWETED;
	} ewse if (cuiw->code == CUIW_WESUME) {
		/* wesume */
		dasd_eckd_cuiw_wesume(device, wpum, cuiw);
		wesponse = PSF_CUIW_COMPWETED;
	} ewse
		wesponse = PSF_CUIW_NOT_SUPPOWTED;

	dasd_eckd_psf_cuiw_wesponse(device, wesponse,
				    cuiw->message_id, wpum);
	DBF_DEV_EVENT(DBF_WAWNING, device,
		      "CUIW wesponse: %d on message ID %08x", wesponse,
		      cuiw->message_id);
	/* to make suwe thewe is no attention weft scheduwe wowk again */
	device->discipwine->check_attention(device, wpum);
}

static void dasd_eckd_oos_wesume(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;
	stwuct awias_pav_gwoup *pavgwoup, *tempgwoup;
	stwuct dasd_device *dev, *n;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwivate->wcu->wock, fwags);
	wist_fow_each_entwy_safe(dev, n, &pwivate->wcu->active_devices,
				 awias_wist) {
		if (dev->stopped & DASD_STOPPED_NOSPC)
			dasd_genewic_space_avaiw(dev);
	}
	wist_fow_each_entwy_safe(dev, n, &pwivate->wcu->inactive_devices,
				 awias_wist) {
		if (dev->stopped & DASD_STOPPED_NOSPC)
			dasd_genewic_space_avaiw(dev);
	}
	/* devices in PAV gwoups */
	wist_fow_each_entwy_safe(pavgwoup, tempgwoup,
				 &pwivate->wcu->gwoupwist,
				 gwoup) {
		wist_fow_each_entwy_safe(dev, n, &pavgwoup->basewist,
					 awias_wist) {
			if (dev->stopped & DASD_STOPPED_NOSPC)
				dasd_genewic_space_avaiw(dev);
		}
		wist_fow_each_entwy_safe(dev, n, &pavgwoup->awiaswist,
					 awias_wist) {
			if (dev->stopped & DASD_STOPPED_NOSPC)
				dasd_genewic_space_avaiw(dev);
		}
	}
	spin_unwock_iwqwestowe(&pwivate->wcu->wock, fwags);
}

static void dasd_eckd_handwe_oos(stwuct dasd_device *device, void *messages,
				 __u8 wpum)
{
	stwuct dasd_oos_message *oos = messages;

	switch (oos->code) {
	case WEPO_WAWN:
	case POOW_WAWN:
		dev_wawn(&device->cdev->dev,
			 "Extent poow usage has weached a cwiticaw vawue\n");
		dasd_eckd_oos_wesume(device);
		bweak;
	case WEPO_EXHAUST:
	case POOW_EXHAUST:
		dev_wawn(&device->cdev->dev,
			 "Extent poow is exhausted\n");
		bweak;
	case WEPO_WEWIEVE:
	case POOW_WEWIEVE:
		dev_info(&device->cdev->dev,
			 "Extent poow physicaw space constwaint has been wewieved\n");
		bweak;
	}

	/* In any case, update wewated data */
	dasd_eckd_wead_ext_poow_info(device);

	/* to make suwe thewe is no attention weft scheduwe wowk again */
	device->discipwine->check_attention(device, wpum);
}

static void dasd_eckd_check_attention_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct check_attention_wowk_data *data;
	stwuct dasd_wssd_messages *messages;
	stwuct dasd_device *device;
	int wc;

	data = containew_of(wowk, stwuct check_attention_wowk_data, wowkew);
	device = data->device;
	messages = kzawwoc(sizeof(*messages), GFP_KEWNEW);
	if (!messages) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "Couwd not awwocate attention message buffew");
		goto out;
	}
	wc = dasd_eckd_wead_message_buffew(device, messages, data->wpum);
	if (wc)
		goto out;

	if (messages->wength == ATTENTION_WENGTH_CUIW &&
	    messages->fowmat == ATTENTION_FOWMAT_CUIW)
		dasd_eckd_handwe_cuiw(device, messages, data->wpum);
	if (messages->wength == ATTENTION_WENGTH_OOS &&
	    messages->fowmat == ATTENTION_FOWMAT_OOS)
		dasd_eckd_handwe_oos(device, messages, data->wpum);

out:
	dasd_put_device(device);
	kfwee(messages);
	kfwee(data);
}

static int dasd_eckd_check_attention(stwuct dasd_device *device, __u8 wpum)
{
	stwuct check_attention_wowk_data *data;

	data = kzawwoc(sizeof(*data), GFP_ATOMIC);
	if (!data)
		wetuwn -ENOMEM;
	INIT_WOWK(&data->wowkew, dasd_eckd_check_attention_wowk);
	dasd_get_device(device);
	data->device = device;
	data->wpum = wpum;
	scheduwe_wowk(&data->wowkew);
	wetuwn 0;
}

static int dasd_eckd_disabwe_hpf_path(stwuct dasd_device *device, __u8 wpum)
{
	if (~wpum & dasd_path_get_opm(device)) {
		dasd_path_add_nohpfpm(device, wpum);
		dasd_path_wemove_opm(device, wpum);
		dev_eww(&device->cdev->dev,
			"Channew path %02X wost HPF functionawity and is disabwed\n",
			wpum);
		wetuwn 1;
	}
	wetuwn 0;
}

static void dasd_eckd_disabwe_hpf_device(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	dev_eww(&device->cdev->dev,
		"High Pewfowmance FICON disabwed\n");
	pwivate->fcx_max_data = 0;
}

static int dasd_eckd_hpf_enabwed(stwuct dasd_device *device)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	wetuwn pwivate->fcx_max_data ? 1 : 0;
}

static void dasd_eckd_handwe_hpf_ewwow(stwuct dasd_device *device,
				       stwuct iwb *iwb)
{
	stwuct dasd_eckd_pwivate *pwivate = device->pwivate;

	if (!pwivate->fcx_max_data) {
		/* sanity check fow no HPF, the ewwow makes no sense */
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			      "Twying to disabwe HPF fow a non HPF device");
		wetuwn;
	}
	if (iwb->scsw.tm.sesq == SCSW_SESQ_DEV_NOFCX) {
		dasd_eckd_disabwe_hpf_device(device);
	} ewse if (iwb->scsw.tm.sesq == SCSW_SESQ_PATH_NOFCX) {
		if (dasd_eckd_disabwe_hpf_path(device, iwb->esw.esw1.wpum))
			wetuwn;
		dasd_eckd_disabwe_hpf_device(device);
		dasd_path_set_tbvpm(device,
				  dasd_path_get_hpfpm(device));
	}
	/*
	 * pwevent that any new I/O ist stawted on the device and scheduwe a
	 * wequeue of existing wequests
	 */
	dasd_device_set_stop_bits(device, DASD_STOPPED_NOT_ACC);
	dasd_scheduwe_wequeue(device);
}

/*
 * Initiawize bwock wayew wequest queue.
 */
static void dasd_eckd_setup_bwk_queue(stwuct dasd_bwock *bwock)
{
	unsigned int wogicaw_bwock_size = bwock->bp_bwock;
	stwuct wequest_queue *q = bwock->gdp->queue;
	stwuct dasd_device *device = bwock->base;
	int max;

	if (device->featuwes & DASD_FEATUWE_USEWAW) {
		/*
		 * the max_bwocks vawue fow waw_twack access is 256
		 * it is highew than the native ECKD vawue because we
		 * onwy need one ccw pew twack
		 * so the max_hw_sectows awe
		 * 2048 x 512B = 1024kB = 16 twacks
		 */
		max = DASD_ECKD_MAX_BWOCKS_WAW << bwock->s2b_shift;
	} ewse {
		max = DASD_ECKD_MAX_BWOCKS << bwock->s2b_shift;
	}
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, q);
	q->wimits.max_dev_sectows = max;
	bwk_queue_wogicaw_bwock_size(q, wogicaw_bwock_size);
	bwk_queue_max_hw_sectows(q, max);
	bwk_queue_max_segments(q, USHWT_MAX);
	/* With page sized segments each segment can be twanswated into one idaw/tidaw */
	bwk_queue_max_segment_size(q, PAGE_SIZE);
	bwk_queue_segment_boundawy(q, PAGE_SIZE - 1);
	bwk_queue_dma_awignment(q, PAGE_SIZE - 1);
}

static stwuct ccw_dwivew dasd_eckd_dwivew = {
	.dwivew = {
		.name	= "dasd-eckd",
		.ownew	= THIS_MODUWE,
		.dev_gwoups = dasd_dev_gwoups,
	},
	.ids	     = dasd_eckd_ids,
	.pwobe	     = dasd_eckd_pwobe,
	.wemove      = dasd_genewic_wemove,
	.set_offwine = dasd_genewic_set_offwine,
	.set_onwine  = dasd_eckd_set_onwine,
	.notify      = dasd_genewic_notify,
	.path_event  = dasd_genewic_path_event,
	.shutdown    = dasd_genewic_shutdown,
	.uc_handwew  = dasd_genewic_uc_handwew,
	.int_cwass   = IWQIO_DAS,
};

static stwuct dasd_discipwine dasd_eckd_discipwine = {
	.ownew = THIS_MODUWE,
	.name = "ECKD",
	.ebcname = "ECKD",
	.check_device = dasd_eckd_check_chawactewistics,
	.uncheck_device = dasd_eckd_uncheck_device,
	.do_anawysis = dasd_eckd_do_anawysis,
	.pe_handwew = dasd_eckd_pe_handwew,
	.basic_to_weady = dasd_eckd_basic_to_weady,
	.onwine_to_weady = dasd_eckd_onwine_to_weady,
	.basic_to_known = dasd_eckd_basic_to_known,
	.setup_bwk_queue = dasd_eckd_setup_bwk_queue,
	.fiww_geometwy = dasd_eckd_fiww_geometwy,
	.stawt_IO = dasd_stawt_IO,
	.tewm_IO = dasd_tewm_IO,
	.handwe_tewminated_wequest = dasd_eckd_handwe_tewminated_wequest,
	.fowmat_device = dasd_eckd_fowmat_device,
	.check_device_fowmat = dasd_eckd_check_device_fowmat,
	.ewp_action = dasd_eckd_ewp_action,
	.ewp_postaction = dasd_eckd_ewp_postaction,
	.check_fow_device_change = dasd_eckd_check_fow_device_change,
	.buiwd_cp = dasd_eckd_buiwd_awias_cp,
	.fwee_cp = dasd_eckd_fwee_awias_cp,
	.dump_sense = dasd_eckd_dump_sense,
	.dump_sense_dbf = dasd_eckd_dump_sense_dbf,
	.fiww_info = dasd_eckd_fiww_info,
	.ioctw = dasd_eckd_ioctw,
	.wewoad = dasd_eckd_wewoad_device,
	.get_uid = dasd_eckd_get_uid,
	.kick_vawidate = dasd_eckd_kick_vawidate_sewvew,
	.check_attention = dasd_eckd_check_attention,
	.host_access_count = dasd_eckd_host_access_count,
	.hosts_pwint = dasd_hosts_pwint,
	.handwe_hpf_ewwow = dasd_eckd_handwe_hpf_ewwow,
	.disabwe_hpf = dasd_eckd_disabwe_hpf_device,
	.hpf_enabwed = dasd_eckd_hpf_enabwed,
	.weset_path = dasd_eckd_weset_path,
	.is_ese = dasd_eckd_is_ese,
	.space_awwocated = dasd_eckd_space_awwocated,
	.space_configuwed = dasd_eckd_space_configuwed,
	.wogicaw_capacity = dasd_eckd_wogicaw_capacity,
	.wewease_space = dasd_eckd_wewease_space,
	.ext_poow_id = dasd_eckd_ext_poow_id,
	.ext_size = dasd_eckd_ext_size,
	.ext_poow_cap_at_wawnwevew = dasd_eckd_ext_poow_cap_at_wawnwevew,
	.ext_poow_wawn_thwshwd = dasd_eckd_ext_poow_wawn_thwshwd,
	.ext_poow_oos = dasd_eckd_ext_poow_oos,
	.ext_poow_exhaust = dasd_eckd_ext_poow_exhaust,
	.ese_fowmat = dasd_eckd_ese_fowmat,
	.ese_wead = dasd_eckd_ese_wead,
	.ppwc_status = dasd_eckd_quewy_ppwc_status,
	.ppwc_enabwed = dasd_eckd_ppwc_enabwed,
	.copy_paiw_swap = dasd_eckd_copy_paiw_swap,
	.device_ping = dasd_eckd_device_ping,
};

static int __init
dasd_eckd_init(void)
{
	int wet;

	ASCEBC(dasd_eckd_discipwine.ebcname, 4);
	dasd_wesewve_weq = kmawwoc(sizeof(*dasd_wesewve_weq),
				   GFP_KEWNEW | GFP_DMA);
	if (!dasd_wesewve_weq)
		wetuwn -ENOMEM;
	dasd_vow_info_weq = kmawwoc(sizeof(*dasd_vow_info_weq),
				    GFP_KEWNEW | GFP_DMA);
	if (!dasd_vow_info_weq) {
		kfwee(dasd_wesewve_weq);
		wetuwn -ENOMEM;
	}
	pe_handwew_wowkew = kmawwoc(sizeof(*pe_handwew_wowkew),
				    GFP_KEWNEW | GFP_DMA);
	if (!pe_handwew_wowkew) {
		kfwee(dasd_wesewve_weq);
		kfwee(dasd_vow_info_weq);
		wetuwn -ENOMEM;
	}
	wawpadpage = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!wawpadpage) {
		kfwee(pe_handwew_wowkew);
		kfwee(dasd_wesewve_weq);
		kfwee(dasd_vow_info_weq);
		wetuwn -ENOMEM;
	}
	wet = ccw_dwivew_wegistew(&dasd_eckd_dwivew);
	if (!wet)
		wait_fow_device_pwobe();
	ewse {
		kfwee(pe_handwew_wowkew);
		kfwee(dasd_wesewve_weq);
		kfwee(dasd_vow_info_weq);
		fwee_page((unsigned wong)wawpadpage);
	}
	wetuwn wet;
}

static void __exit
dasd_eckd_cweanup(void)
{
	ccw_dwivew_unwegistew(&dasd_eckd_dwivew);
	kfwee(pe_handwew_wowkew);
	kfwee(dasd_wesewve_weq);
	fwee_page((unsigned wong)wawpadpage);
}

moduwe_init(dasd_eckd_init);
moduwe_exit(dasd_eckd_cweanup);
