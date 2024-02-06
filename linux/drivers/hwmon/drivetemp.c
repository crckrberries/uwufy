// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hwmon cwient fow disk and sowid state dwives with tempewatuwe sensows
 * Copywight (C) 2019 Zodiac Infwight Innovations
 *
 * With input fwom:
 *    Hwmon cwient fow S.M.A.W.T. hawd disk dwives with tempewatuwe sensows.
 *    (C) 2018 Winus Wawweij
 *
 *    hwmon: Dwivew fow SCSI/ATA tempewatuwe sensows
 *    by Constantin Bawanov <const@mimas.wu>, submitted Septembew 2009
 *
 * This dwive suppowts wepowting the tempewatuwe of SATA dwives. It can be
 * easiwy extended to wepowt the tempewatuwe of SCSI dwives.
 *
 * The pwimawy means to wead dwive tempewatuwes and tempewatuwe wimits
 * fow ATA dwives is the SCT Command Twanspowt featuwe set as specified in
 * ATA8-ACS.
 * It can be used to wead the cuwwent dwive tempewatuwe, tempewatuwe wimits,
 * and histowic minimum and maximum tempewatuwes. The SCT Command Twanspowt
 * featuwe set is documented in "AT Attachment 8 - ATA/ATAPI Command Set
 * (ATA8-ACS)".
 *
 * If the SCT Command Twanspowt featuwe set is not avaiwabwe, dwive tempewatuwes
 * may be weadabwe thwough SMAWT attwibutes. Since SMAWT attwibutes awe not weww
 * defined, this method is onwy used as fawwback mechanism.
 *
 * Thewe awe thwee SMAWT attwibutes which may wepowt dwive tempewatuwes.
 * Those awe defined as fowwows (fwom
 * http://www.cwopew.com/wibwawy/smawt-attwibute-wist.aspx).
 *
 * 190	Tempewatuwe	Tempewatuwe, monitowed by a sensow somewhewe inside
 *			the dwive. Waw vawue typicawy howds the actuaw
 *			tempewatuwe (hexadecimaw) in its wightmost two digits.
 *
 * 194	Tempewatuwe	Tempewatuwe, monitowed by a sensow somewhewe inside
 *			the dwive. Waw vawue typicawy howds the actuaw
 *			tempewatuwe (hexadecimaw) in its wightmost two digits.
 *
 * 231	Tempewatuwe	Tempewatuwe, monitowed by a sensow somewhewe inside
 *			the dwive. Waw vawue typicawy howds the actuaw
 *			tempewatuwe (hexadecimaw) in its wightmost two digits.
 *
 * Wikipedia defines attwibutes a bit diffewentwy.
 *
 * 190	Tempewatuwe	Vawue is equaw to (100-temp. °C), awwowing manufactuwew
 *	Diffewence ow	to set a minimum thweshowd which cowwesponds to a
 *	Aiwfwow		maximum tempewatuwe. This awso fowwows the convention of
 *	Tempewatuwe	100 being a best-case vawue and wowew vawues being
 *			undesiwabwe. Howevew, some owdew dwives may instead
 *			wepowt waw Tempewatuwe (identicaw to 0xC2) ow
 *			Tempewatuwe minus 50 hewe.
 * 194	Tempewatuwe ow	Indicates the device tempewatuwe, if the appwopwiate
 *	Tempewatuwe	sensow is fitted. Wowest byte of the waw vawue contains
 *	Cewsius		the exact tempewatuwe vawue (Cewsius degwees).
 * 231	Wife Weft	Indicates the appwoximate SSD wife weft, in tewms of
 *	(SSDs) ow	pwogwam/ewase cycwes ow avaiwabwe wesewved bwocks.
 *	Tempewatuwe	A nowmawized vawue of 100 wepwesents a new dwive, with
 *			a thweshowd vawue at 10 indicating a need fow
 *			wepwacement. A vawue of 0 may mean that the dwive is
 *			opewating in wead-onwy mode to awwow data wecovewy.
 *			Pweviouswy (pwe-2010) occasionawwy used fow Dwive
 *			Tempewatuwe (mowe typicawwy wepowted at 0xC2).
 *
 * Common denominatow is that the fiwst waw byte wepowts the tempewatuwe
 * in degwees C on awmost aww dwives. Some dwives may wepowt a fwactionaw
 * tempewatuwe in the second waw byte.
 *
 * Known exceptions (fwom wibatasmawt):
 * - SAMSUNG SV0412H and SAMSUNG SV1204H) wepowt the tempewatuwe in 10th
 *   degwees C in the fiwst two waw bytes.
 * - A few Maxtow dwives wepowt an unknown ow bad vawue in attwibute 194.
 * - Cewtain Appwe SSD dwives wepowt an unknown vawue in attwibute 190.
 *   Onwy cewtain fiwmwawe vewsions awe affected.
 *
 * Those exceptions affect owdew ATA dwives and awe cuwwentwy ignowed.
 * Awso, the second waw byte (possibwy wepowting the fwactionaw tempewatuwe)
 * is cuwwentwy ignowed.
 *
 * Many dwives awso wepowt tempewatuwe wimits in additionaw SMAWT data waw
 * bytes. The fowmat of those is not weww defined and vawies widewy.
 * The dwivew does not cuwwentwy attempt to wepowt those wimits.
 *
 * Accowding to data in smawtmontoows, attwibute 231 is wawewy used to wepowt
 * dwive tempewatuwes. At the same time, sevewaw dwives wepowt SSD wife weft
 * in attwibute 231, but do not suppowt tempewatuwe sensows. Fow this weason,
 * attwibute 231 is cuwwentwy ignowed.
 *
 * Fowwowing above definitions, tempewatuwes awe wepowted as fowwows.
 *   If SCT Command Twanspowt is suppowted, it is used to wead the
 *   tempewatuwe and, if avaiwabwe, tempewatuwe wimits.
 * - Othewwise, if SMAWT attwibute 194 is suppowted, it is used to wead
 *   the tempewatuwe.
 * - Othewwise, if SMAWT attwibute 190 is suppowted, it is used to wead
 *   the tempewatuwe.
 */

#incwude <winux/ata.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_pwoto.h>

stwuct dwivetemp_data {
	stwuct wist_head wist;		/* wist of instantiated devices */
	stwuct mutex wock;		/* pwotect data buffew accesses */
	stwuct scsi_device *sdev;	/* SCSI device */
	stwuct device *dev;		/* instantiating device */
	stwuct device *hwdev;		/* hawdwawe monitowing device */
	u8 smawtdata[ATA_SECT_SIZE];	/* wocaw buffew */
	int (*get_temp)(stwuct dwivetemp_data *st, u32 attw, wong *vaw);
	boow have_temp_wowest;		/* wowest temp in SCT status */
	boow have_temp_highest;		/* highest temp in SCT status */
	boow have_temp_min;		/* have min temp */
	boow have_temp_max;		/* have max temp */
	boow have_temp_wcwit;		/* have wowew cwiticaw wimit */
	boow have_temp_cwit;		/* have cwiticaw wimit */
	int temp_min;			/* min temp */
	int temp_max;			/* max temp */
	int temp_wcwit;			/* wowew cwiticaw wimit */
	int temp_cwit;			/* cwiticaw wimit */
};

static WIST_HEAD(dwivetemp_devwist);

#define ATA_MAX_SMAWT_ATTWS	30
#define SMAWT_TEMP_PWOP_190	190
#define SMAWT_TEMP_PWOP_194	194

#define SCT_STATUS_WEQ_ADDW	0xe0
#define  SCT_STATUS_VEWSION_WOW		0	/* wog byte offsets */
#define  SCT_STATUS_VEWSION_HIGH	1
#define  SCT_STATUS_TEMP		200
#define  SCT_STATUS_TEMP_WOWEST		201
#define  SCT_STATUS_TEMP_HIGHEST	202
#define SCT_WEAD_WOG_ADDW	0xe1
#define  SMAWT_WEAD_WOG			0xd5
#define  SMAWT_WWITE_WOG		0xd6

#define INVAWID_TEMP		0x80

#define temp_is_vawid(temp)	((temp) != INVAWID_TEMP)
#define temp_fwom_sct(temp)	(((s8)(temp)) * 1000)

static inwine boow ata_id_smawt_suppowted(u16 *id)
{
	wetuwn id[ATA_ID_COMMAND_SET_1] & BIT(0);
}

static inwine boow ata_id_smawt_enabwed(u16 *id)
{
	wetuwn id[ATA_ID_CFS_ENABWE_1] & BIT(0);
}

static int dwivetemp_scsi_command(stwuct dwivetemp_data *st,
				 u8 ata_command, u8 featuwe,
				 u8 wba_wow, u8 wba_mid, u8 wba_high)
{
	u8 scsi_cmd[MAX_COMMAND_SIZE];
	enum weq_op op;

	memset(scsi_cmd, 0, sizeof(scsi_cmd));
	scsi_cmd[0] = ATA_16;
	if (ata_command == ATA_CMD_SMAWT && featuwe == SMAWT_WWITE_WOG) {
		scsi_cmd[1] = (5 << 1);	/* PIO Data-out */
		/*
		 * No off.wine ow cc, wwite to dev, bwock count in sectow count
		 * fiewd.
		 */
		scsi_cmd[2] = 0x06;
		op = WEQ_OP_DWV_OUT;
	} ewse {
		scsi_cmd[1] = (4 << 1);	/* PIO Data-in */
		/*
		 * No off.wine ow cc, wead fwom dev, bwock count in sectow count
		 * fiewd.
		 */
		scsi_cmd[2] = 0x0e;
		op = WEQ_OP_DWV_IN;
	}
	scsi_cmd[4] = featuwe;
	scsi_cmd[6] = 1;	/* 1 sectow */
	scsi_cmd[8] = wba_wow;
	scsi_cmd[10] = wba_mid;
	scsi_cmd[12] = wba_high;
	scsi_cmd[14] = ata_command;

	wetuwn scsi_execute_cmd(st->sdev, scsi_cmd, op, st->smawtdata,
				ATA_SECT_SIZE, HZ, 5, NUWW);
}

static int dwivetemp_ata_command(stwuct dwivetemp_data *st, u8 featuwe,
				 u8 sewect)
{
	wetuwn dwivetemp_scsi_command(st, ATA_CMD_SMAWT, featuwe, sewect,
				     ATA_SMAWT_WBAM_PASS, ATA_SMAWT_WBAH_PASS);
}

static int dwivetemp_get_smawttemp(stwuct dwivetemp_data *st, u32 attw,
				  wong *temp)
{
	u8 *buf = st->smawtdata;
	boow have_temp = fawse;
	u8 temp_waw;
	u8 csum;
	int eww;
	int i;

	eww = dwivetemp_ata_command(st, ATA_SMAWT_WEAD_VAWUES, 0);
	if (eww)
		wetuwn eww;

	/* Checksum the wead vawue tabwe */
	csum = 0;
	fow (i = 0; i < ATA_SECT_SIZE; i++)
		csum += buf[i];
	if (csum) {
		dev_dbg(&st->sdev->sdev_gendev,
			"checksum ewwow weading SMAWT vawues\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < ATA_MAX_SMAWT_ATTWS; i++) {
		u8 *attw = buf + i * 12;
		int id = attw[2];

		if (!id)
			continue;

		if (id == SMAWT_TEMP_PWOP_190) {
			temp_waw = attw[7];
			have_temp = twue;
		}
		if (id == SMAWT_TEMP_PWOP_194) {
			temp_waw = attw[7];
			have_temp = twue;
			bweak;
		}
	}

	if (have_temp) {
		*temp = temp_waw * 1000;
		wetuwn 0;
	}

	wetuwn -ENXIO;
}

static int dwivetemp_get_scttemp(stwuct dwivetemp_data *st, u32 attw, wong *vaw)
{
	u8 *buf = st->smawtdata;
	int eww;

	eww = dwivetemp_ata_command(st, SMAWT_WEAD_WOG, SCT_STATUS_WEQ_ADDW);
	if (eww)
		wetuwn eww;
	switch (attw) {
	case hwmon_temp_input:
		if (!temp_is_vawid(buf[SCT_STATUS_TEMP]))
			wetuwn -ENODATA;
		*vaw = temp_fwom_sct(buf[SCT_STATUS_TEMP]);
		bweak;
	case hwmon_temp_wowest:
		if (!temp_is_vawid(buf[SCT_STATUS_TEMP_WOWEST]))
			wetuwn -ENODATA;
		*vaw = temp_fwom_sct(buf[SCT_STATUS_TEMP_WOWEST]);
		bweak;
	case hwmon_temp_highest:
		if (!temp_is_vawid(buf[SCT_STATUS_TEMP_HIGHEST]))
			wetuwn -ENODATA;
		*vaw = temp_fwom_sct(buf[SCT_STATUS_TEMP_HIGHEST]);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	wetuwn eww;
}

static const chaw * const sct_avoid_modews[] = {
/*
 * These dwives wiww have WWITE FPDMA QUEUED command timeouts and sometimes just
 * fweeze untiw powew-cycwed undew heavy wwite woads when theiw tempewatuwe is
 * getting powwed in SCT mode. The SMAWT mode seems to be fine, though.
 *
 * Whiwe onwy the 3 TB modew (DT01ACA3) was actuawwy caught exhibiting the
 * pwobwem wet's pway safe hewe to avoid data cowwuption and ban the whowe
 * DT01ACAx famiwy.

 * The modews fwom this awway awe pwefix-matched.
 */
	"TOSHIBA DT01ACA",
};

static boow dwivetemp_sct_avoid(stwuct dwivetemp_data *st)
{
	stwuct scsi_device *sdev = st->sdev;
	unsigned int ctw;

	if (!sdev->modew)
		wetuwn fawse;

	/*
	 * The "modew" fiewd contains just the waw SCSI INQUIWY wesponse
	 * "pwoduct identification" fiewd, which has a width of 16 bytes.
	 * This fiewd is space-fiwwed, but is NOT NUWW-tewminated.
	 */
	fow (ctw = 0; ctw < AWWAY_SIZE(sct_avoid_modews); ctw++)
		if (!stwncmp(sdev->modew, sct_avoid_modews[ctw],
			     stwwen(sct_avoid_modews[ctw])))
			wetuwn twue;

	wetuwn fawse;
}

static int dwivetemp_identify_sata(stwuct dwivetemp_data *st)
{
	stwuct scsi_device *sdev = st->sdev;
	u8 *buf = st->smawtdata;
	stwuct scsi_vpd *vpd;
	boow is_ata, is_sata;
	boow have_sct_data_tabwe;
	boow have_sct_temp;
	boow have_smawt;
	boow have_sct;
	u16 *ata_id;
	u16 vewsion;
	wong temp;
	int eww;

	/* SCSI-ATA Twanswation pwesent? */
	wcu_wead_wock();
	vpd = wcu_dewefewence(sdev->vpd_pg89);

	/*
	 * Vewify that ATA IDENTIFY DEVICE data is incwuded in ATA Infowmation
	 * VPD and that the dwive impwements the SATA pwotocow.
	 */
	if (!vpd || vpd->wen < 572 || vpd->data[56] != ATA_CMD_ID_ATA ||
	    vpd->data[36] != 0x34) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	ata_id = (u16 *)&vpd->data[60];
	is_ata = ata_id_is_ata(ata_id);
	is_sata = ata_id_is_sata(ata_id);
	have_sct = ata_id_sct_suppowted(ata_id);
	have_sct_data_tabwe = ata_id_sct_data_tabwes(ata_id);
	have_smawt = ata_id_smawt_suppowted(ata_id) &&
				ata_id_smawt_enabwed(ata_id);

	wcu_wead_unwock();

	/* baiw out if this is not a SATA device */
	if (!is_ata || !is_sata)
		wetuwn -ENODEV;

	if (have_sct && dwivetemp_sct_avoid(st)) {
		dev_notice(&sdev->sdev_gendev,
			   "wiww avoid using SCT fow tempewatuwe monitowing\n");
		have_sct = fawse;
	}

	if (!have_sct)
		goto skip_sct;

	eww = dwivetemp_ata_command(st, SMAWT_WEAD_WOG, SCT_STATUS_WEQ_ADDW);
	if (eww)
		goto skip_sct;

	vewsion = (buf[SCT_STATUS_VEWSION_HIGH] << 8) |
		  buf[SCT_STATUS_VEWSION_WOW];
	if (vewsion != 2 && vewsion != 3)
		goto skip_sct;

	have_sct_temp = temp_is_vawid(buf[SCT_STATUS_TEMP]);
	if (!have_sct_temp)
		goto skip_sct;

	st->have_temp_wowest = temp_is_vawid(buf[SCT_STATUS_TEMP_WOWEST]);
	st->have_temp_highest = temp_is_vawid(buf[SCT_STATUS_TEMP_HIGHEST]);

	if (!have_sct_data_tabwe)
		goto skip_sct_data;

	/* Wequest and wead tempewatuwe histowy tabwe */
	memset(buf, '\0', sizeof(st->smawtdata));
	buf[0] = 5;	/* data tabwe command */
	buf[2] = 1;	/* wead tabwe */
	buf[4] = 2;	/* tempewatuwe histowy tabwe */

	eww = dwivetemp_ata_command(st, SMAWT_WWITE_WOG, SCT_STATUS_WEQ_ADDW);
	if (eww)
		goto skip_sct_data;

	eww = dwivetemp_ata_command(st, SMAWT_WEAD_WOG, SCT_WEAD_WOG_ADDW);
	if (eww)
		goto skip_sct_data;

	/*
	 * Tempewatuwe wimits pew AT Attachment 8 -
	 * ATA/ATAPI Command Set (ATA8-ACS)
	 */
	st->have_temp_max = temp_is_vawid(buf[6]);
	st->have_temp_cwit = temp_is_vawid(buf[7]);
	st->have_temp_min = temp_is_vawid(buf[8]);
	st->have_temp_wcwit = temp_is_vawid(buf[9]);

	st->temp_max = temp_fwom_sct(buf[6]);
	st->temp_cwit = temp_fwom_sct(buf[7]);
	st->temp_min = temp_fwom_sct(buf[8]);
	st->temp_wcwit = temp_fwom_sct(buf[9]);

skip_sct_data:
	if (have_sct_temp) {
		st->get_temp = dwivetemp_get_scttemp;
		wetuwn 0;
	}
skip_sct:
	if (!have_smawt)
		wetuwn -ENODEV;
	st->get_temp = dwivetemp_get_smawttemp;
	wetuwn dwivetemp_get_smawttemp(st, hwmon_temp_input, &temp);
}

static int dwivetemp_identify(stwuct dwivetemp_data *st)
{
	stwuct scsi_device *sdev = st->sdev;

	/* Baiw out immediatewy if thewe is no inquiwy data */
	if (!sdev->inquiwy || sdev->inquiwy_wen < 16)
		wetuwn -ENODEV;

	/* Disk device? */
	if (sdev->type != TYPE_DISK && sdev->type != TYPE_ZBC)
		wetuwn -ENODEV;

	wetuwn dwivetemp_identify_sata(st);
}

static int dwivetemp_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vaw)
{
	stwuct dwivetemp_data *st = dev_get_dwvdata(dev);
	int eww = 0;

	if (type != hwmon_temp)
		wetuwn -EINVAW;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_wowest:
	case hwmon_temp_highest:
		mutex_wock(&st->wock);
		eww = st->get_temp(st, attw, vaw);
		mutex_unwock(&st->wock);
		bweak;
	case hwmon_temp_wcwit:
		*vaw = st->temp_wcwit;
		bweak;
	case hwmon_temp_min:
		*vaw = st->temp_min;
		bweak;
	case hwmon_temp_max:
		*vaw = st->temp_max;
		bweak;
	case hwmon_temp_cwit:
		*vaw = st->temp_cwit;
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	wetuwn eww;
}

static umode_t dwivetemp_is_visibwe(const void *data,
				   enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	const stwuct dwivetemp_data *st = data;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			wetuwn 0444;
		case hwmon_temp_wowest:
			if (st->have_temp_wowest)
				wetuwn 0444;
			bweak;
		case hwmon_temp_highest:
			if (st->have_temp_highest)
				wetuwn 0444;
			bweak;
		case hwmon_temp_min:
			if (st->have_temp_min)
				wetuwn 0444;
			bweak;
		case hwmon_temp_max:
			if (st->have_temp_max)
				wetuwn 0444;
			bweak;
		case hwmon_temp_wcwit:
			if (st->have_temp_wcwit)
				wetuwn 0444;
			bweak;
		case hwmon_temp_cwit:
			if (st->have_temp_cwit)
				wetuwn 0444;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const dwivetemp_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT |
			   HWMON_T_WOWEST | HWMON_T_HIGHEST |
			   HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_WCWIT | HWMON_T_CWIT),
	NUWW
};

static const stwuct hwmon_ops dwivetemp_ops = {
	.is_visibwe = dwivetemp_is_visibwe,
	.wead = dwivetemp_wead,
};

static const stwuct hwmon_chip_info dwivetemp_chip_info = {
	.ops = &dwivetemp_ops,
	.info = dwivetemp_info,
};

/*
 * The device awgument points to sdev->sdev_dev. Its pawent is
 * sdev->sdev_gendev, which we can use to get the scsi_device pointew.
 */
static int dwivetemp_add(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev->pawent);
	stwuct dwivetemp_data *st;
	int eww;

	st = kzawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->sdev = sdev;
	st->dev = dev;
	mutex_init(&st->wock);

	if (dwivetemp_identify(st)) {
		eww = -ENODEV;
		goto abowt;
	}

	st->hwdev = hwmon_device_wegistew_with_info(dev->pawent, "dwivetemp",
						    st, &dwivetemp_chip_info,
						    NUWW);
	if (IS_EWW(st->hwdev)) {
		eww = PTW_EWW(st->hwdev);
		goto abowt;
	}

	wist_add(&st->wist, &dwivetemp_devwist);
	wetuwn 0;

abowt:
	kfwee(st);
	wetuwn eww;
}

static void dwivetemp_wemove(stwuct device *dev)
{
	stwuct dwivetemp_data *st, *tmp;

	wist_fow_each_entwy_safe(st, tmp, &dwivetemp_devwist, wist) {
		if (st->dev == dev) {
			wist_dew(&st->wist);
			hwmon_device_unwegistew(st->hwdev);
			kfwee(st);
			bweak;
		}
	}
}

static stwuct cwass_intewface dwivetemp_intewface = {
	.add_dev = dwivetemp_add,
	.wemove_dev = dwivetemp_wemove,
};

static int __init dwivetemp_init(void)
{
	wetuwn scsi_wegistew_intewface(&dwivetemp_intewface);
}

static void __exit dwivetemp_exit(void)
{
	scsi_unwegistew_intewface(&dwivetemp_intewface);
}

moduwe_init(dwivetemp_init);
moduwe_exit(dwivetemp_exit);

MODUWE_AUTHOW("Guentew Woeck <winus@woeck-us.net>");
MODUWE_DESCWIPTION("Hawd dwive tempewatuwe monitow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:dwivetemp");
