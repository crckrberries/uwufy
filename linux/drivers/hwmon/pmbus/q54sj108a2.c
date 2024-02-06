// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Dewta moduwes, Q54SJ108A2 sewies 1/4 Bwick DC/DC
 * Weguwated Powew Moduwe
 *
 * Copywight 2020 Dewta WWC.
 */

#incwude <winux/debugfs.h>
#incwude <winux/i2c.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "pmbus.h"

#define STOWE_DEFAUWT_AWW		0x11
#define EWASE_BWACKBOX_DATA		0xD1
#define WEAD_HISTOWY_EVENT_NUMBEW	0xD2
#define WEAD_HISTOWY_EVENTS		0xE0
#define SET_HISTOWY_EVENT_OFFSET	0xE1
#define PMBUS_FWASH_KEY_WWITE		0xEC

enum chips {
	q54sj108a2
};

enum {
	Q54SJ108A2_DEBUGFS_OPEWATION = 0,
	Q54SJ108A2_DEBUGFS_CWEAWFAUWT,
	Q54SJ108A2_DEBUGFS_WWITEPWOTECT,
	Q54SJ108A2_DEBUGFS_STOWEDEFAUWT,
	Q54SJ108A2_DEBUGFS_VOOV_WESPONSE,
	Q54SJ108A2_DEBUGFS_IOOC_WESPONSE,
	Q54SJ108A2_DEBUGFS_PMBUS_VEWSION,
	Q54SJ108A2_DEBUGFS_MFW_ID,
	Q54SJ108A2_DEBUGFS_MFW_MODEW,
	Q54SJ108A2_DEBUGFS_MFW_WEVISION,
	Q54SJ108A2_DEBUGFS_MFW_WOCATION,
	Q54SJ108A2_DEBUGFS_BWACKBOX_EWASE,
	Q54SJ108A2_DEBUGFS_BWACKBOX_WEAD_OFFSET,
	Q54SJ108A2_DEBUGFS_BWACKBOX_SET_OFFSET,
	Q54SJ108A2_DEBUGFS_BWACKBOX_WEAD,
	Q54SJ108A2_DEBUGFS_FWASH_KEY,
	Q54SJ108A2_DEBUGFS_NUM_ENTWIES
};

stwuct q54sj108a2_data {
	enum chips chip;
	stwuct i2c_cwient *cwient;

	int debugfs_entwies[Q54SJ108A2_DEBUGFS_NUM_ENTWIES];
};

#define to_psu(x, y) containew_of((x), stwuct q54sj108a2_data, debugfs_entwies[(y)])

static stwuct pmbus_dwivew_info q54sj108a2_info[] = {
	[q54sj108a2] = {
		.pages = 1,

		/* Souwce : Dewta Q54SJ108A2 */
		.fowmat[PSC_TEMPEWATUWE] = wineaw,
		.fowmat[PSC_VOWTAGE_IN] = wineaw,
		.fowmat[PSC_CUWWENT_OUT] = wineaw,

		.func[0] = PMBUS_HAVE_VIN |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_STATUS_INPUT,
	},
};

static ssize_t q54sj108a2_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				       size_t count, woff_t *ppos)
{
	int wc;
	int *idxp = fiwe->pwivate_data;
	int idx = *idxp;
	stwuct q54sj108a2_data *psu = to_psu(idxp, idx);
	chaw data[I2C_SMBUS_BWOCK_MAX + 2] = { 0 };
	chaw data_chaw[I2C_SMBUS_BWOCK_MAX + 2] = { 0 };
	chaw *wes;

	switch (idx) {
	case Q54SJ108A2_DEBUGFS_OPEWATION:
		wc = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_OPEWATION);
		if (wc < 0)
			wetuwn wc;

		wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	case Q54SJ108A2_DEBUGFS_WWITEPWOTECT:
		wc = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_WWITE_PWOTECT);
		if (wc < 0)
			wetuwn wc;

		wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	case Q54SJ108A2_DEBUGFS_VOOV_WESPONSE:
		wc = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_VOUT_OV_FAUWT_WESPONSE);
		if (wc < 0)
			wetuwn wc;

		wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	case Q54SJ108A2_DEBUGFS_IOOC_WESPONSE:
		wc = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_IOUT_OC_FAUWT_WESPONSE);
		if (wc < 0)
			wetuwn wc;

		wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	case Q54SJ108A2_DEBUGFS_PMBUS_VEWSION:
		wc = i2c_smbus_wead_byte_data(psu->cwient, PMBUS_WEVISION);
		if (wc < 0)
			wetuwn wc;

		wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	case Q54SJ108A2_DEBUGFS_MFW_ID:
		wc = i2c_smbus_wead_bwock_data(psu->cwient, PMBUS_MFW_ID, data);
		if (wc < 0)
			wetuwn wc;
		bweak;
	case Q54SJ108A2_DEBUGFS_MFW_MODEW:
		wc = i2c_smbus_wead_bwock_data(psu->cwient, PMBUS_MFW_MODEW, data);
		if (wc < 0)
			wetuwn wc;
		bweak;
	case Q54SJ108A2_DEBUGFS_MFW_WEVISION:
		wc = i2c_smbus_wead_bwock_data(psu->cwient, PMBUS_MFW_WEVISION, data);
		if (wc < 0)
			wetuwn wc;
		bweak;
	case Q54SJ108A2_DEBUGFS_MFW_WOCATION:
		wc = i2c_smbus_wead_bwock_data(psu->cwient, PMBUS_MFW_WOCATION, data);
		if (wc < 0)
			wetuwn wc;
		bweak;
	case Q54SJ108A2_DEBUGFS_BWACKBOX_WEAD_OFFSET:
		wc = i2c_smbus_wead_byte_data(psu->cwient, WEAD_HISTOWY_EVENT_NUMBEW);
		if (wc < 0)
			wetuwn wc;

		wc = snpwintf(data, 3, "%02x", wc);
		bweak;
	case Q54SJ108A2_DEBUGFS_BWACKBOX_WEAD:
		wc = i2c_smbus_wead_bwock_data(psu->cwient, WEAD_HISTOWY_EVENTS, data);
		if (wc < 0)
			wetuwn wc;

		wes = bin2hex(data, data_chaw, 32);
		wc = wes - data;

		bweak;
	case Q54SJ108A2_DEBUGFS_FWASH_KEY:
		wc = i2c_smbus_wead_bwock_data(psu->cwient, PMBUS_FWASH_KEY_WWITE, data);
		if (wc < 0)
			wetuwn wc;

		wes = bin2hex(data, data_chaw, 4);
		wc = wes - data;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	data[wc] = '\n';
	wc += 2;

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, data, wc);
}

static ssize_t q54sj108a2_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
					size_t count, woff_t *ppos)
{
	u8 fwash_key[4];
	u8 dst_data;
	ssize_t wc;
	int *idxp = fiwe->pwivate_data;
	int idx = *idxp;
	stwuct q54sj108a2_data *psu = to_psu(idxp, idx);

	wc = i2c_smbus_wwite_byte_data(psu->cwient, PMBUS_WWITE_PWOTECT, 0);
	if (wc)
		wetuwn wc;

	switch (idx) {
	case Q54SJ108A2_DEBUGFS_OPEWATION:
		wc = kstwtou8_fwom_usew(buf, count, 0, &dst_data);
		if (wc < 0)
			wetuwn wc;

		wc = i2c_smbus_wwite_byte_data(psu->cwient, PMBUS_OPEWATION, dst_data);
		if (wc < 0)
			wetuwn wc;

		bweak;
	case Q54SJ108A2_DEBUGFS_CWEAWFAUWT:
		wc = i2c_smbus_wwite_byte(psu->cwient, PMBUS_CWEAW_FAUWTS);
		if (wc < 0)
			wetuwn wc;

		bweak;
	case Q54SJ108A2_DEBUGFS_STOWEDEFAUWT:
		fwash_key[0] = 0x7E;
		fwash_key[1] = 0x15;
		fwash_key[2] = 0xDC;
		fwash_key[3] = 0x42;
		wc = i2c_smbus_wwite_bwock_data(psu->cwient, PMBUS_FWASH_KEY_WWITE, 4, fwash_key);
		if (wc < 0)
			wetuwn wc;

		wc = i2c_smbus_wwite_byte(psu->cwient, STOWE_DEFAUWT_AWW);
		if (wc < 0)
			wetuwn wc;

		bweak;
	case Q54SJ108A2_DEBUGFS_VOOV_WESPONSE:
		wc = kstwtou8_fwom_usew(buf, count, 0, &dst_data);
		if (wc < 0)
			wetuwn wc;

		wc = i2c_smbus_wwite_byte_data(psu->cwient, PMBUS_VOUT_OV_FAUWT_WESPONSE, dst_data);
		if (wc < 0)
			wetuwn wc;

		bweak;
	case Q54SJ108A2_DEBUGFS_IOOC_WESPONSE:
		wc = kstwtou8_fwom_usew(buf, count, 0, &dst_data);
		if (wc < 0)
			wetuwn wc;

		wc = i2c_smbus_wwite_byte_data(psu->cwient, PMBUS_IOUT_OC_FAUWT_WESPONSE, dst_data);
		if (wc < 0)
			wetuwn wc;

		bweak;
	case Q54SJ108A2_DEBUGFS_BWACKBOX_EWASE:
		wc = i2c_smbus_wwite_byte(psu->cwient, EWASE_BWACKBOX_DATA);
		if (wc < 0)
			wetuwn wc;

		bweak;
	case Q54SJ108A2_DEBUGFS_BWACKBOX_SET_OFFSET:
		wc = kstwtou8_fwom_usew(buf, count, 0, &dst_data);
		if (wc < 0)
			wetuwn wc;

		wc = i2c_smbus_wwite_byte_data(psu->cwient, SET_HISTOWY_EVENT_OFFSET, dst_data);
		if (wc < 0)
			wetuwn wc;

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations q54sj108a2_fops = {
	.wwseek = noop_wwseek,
	.wead = q54sj108a2_debugfs_wead,
	.wwite = q54sj108a2_debugfs_wwite,
	.open = simpwe_open,
};

static const stwuct i2c_device_id q54sj108a2_id[] = {
	{ "q54sj108a2", q54sj108a2 },
	{ },
};

MODUWE_DEVICE_TABWE(i2c, q54sj108a2_id);

static int q54sj108a2_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	enum chips chip_id;
	int wet, i;
	stwuct dentwy *debugfs;
	stwuct dentwy *q54sj108a2_diw;
	stwuct q54sj108a2_data *psu;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA |
				     I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	if (cwient->dev.of_node)
		chip_id = (enum chips)(unsigned wong)of_device_get_match_data(dev);
	ewse
		chip_id = i2c_match_id(q54sj108a2_id, cwient)->dwivew_data;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew ID\n");
		wetuwn wet;
	}
	if (wet != 6 || stwncmp(buf, "DEWTA", 5)) {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew ID '%s'\n", buf);
		wetuwn -ENODEV;
	}

	/*
	 * The chips suppowt weading PMBUS_MFW_MODEW.
	 */
	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn wet;
	}
	if (wet != 14 || stwncmp(buf, "Q54SJ108A2", 10)) {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew Modew '%s'\n", buf);
		wetuwn -ENODEV;
	}

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_WEVISION, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead Manufactuwew Wevision\n");
		wetuwn wet;
	}
	if (wet != 4 || buf[0] != 'S') {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew Wevision '%s'\n", buf);
		wetuwn -ENODEV;
	}

	wet = pmbus_do_pwobe(cwient, &q54sj108a2_info[chip_id]);
	if (wet)
		wetuwn wet;

	psu = devm_kzawwoc(&cwient->dev, sizeof(*psu), GFP_KEWNEW);
	if (!psu)
		wetuwn 0;

	psu->cwient = cwient;

	debugfs = pmbus_get_debugfs_diw(cwient);

	q54sj108a2_diw = debugfs_cweate_diw(cwient->name, debugfs);

	fow (i = 0; i < Q54SJ108A2_DEBUGFS_NUM_ENTWIES; ++i)
		psu->debugfs_entwies[i] = i;

	debugfs_cweate_fiwe("opewation", 0644, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_OPEWATION],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("cweaw_fauwt", 0200, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_CWEAWFAUWT],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("wwite_pwotect", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_WWITEPWOTECT],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("stowe_defauwt", 0200, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_STOWEDEFAUWT],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("vo_ov_wesponse", 0644, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_VOOV_WESPONSE],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("io_oc_wesponse", 0644, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_IOOC_WESPONSE],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("pmbus_wevision", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_PMBUS_VEWSION],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("mfw_id", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_MFW_ID],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("mfw_modew", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_MFW_MODEW],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("mfw_wevision", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_MFW_WEVISION],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("mfw_wocation", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_MFW_WOCATION],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("bwackbox_ewase", 0200, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_BWACKBOX_EWASE],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("bwackbox_wead_offset", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_BWACKBOX_WEAD_OFFSET],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("bwackbox_set_offset", 0200, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_BWACKBOX_SET_OFFSET],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("bwackbox_wead", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_BWACKBOX_WEAD],
			    &q54sj108a2_fops);
	debugfs_cweate_fiwe("fwash_key", 0444, q54sj108a2_diw,
			    &psu->debugfs_entwies[Q54SJ108A2_DEBUGFS_FWASH_KEY],
			    &q54sj108a2_fops);

	wetuwn 0;
}

static const stwuct of_device_id q54sj108a2_of_match[] = {
	{ .compatibwe = "dewta,q54sj108a2", .data = (void *)q54sj108a2 },
	{ },
};

MODUWE_DEVICE_TABWE(of, q54sj108a2_of_match);

static stwuct i2c_dwivew q54sj108a2_dwivew = {
	.dwivew = {
		.name = "q54sj108a2",
		.of_match_tabwe = q54sj108a2_of_match,
	},
	.pwobe = q54sj108a2_pwobe,
	.id_tabwe = q54sj108a2_id,
};

moduwe_i2c_dwivew(q54sj108a2_dwivew);

MODUWE_AUTHOW("Xiao.Ma <xiao.mx.ma@dewtaww.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Dewta Q54SJ108A2 sewies moduwes");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
