// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/ethtoow.h>
#incwude <winux/sfp.h>
#incwude <winux/mutex.h>

#incwude "cowe.h"
#incwude "cowe_env.h"
#incwude "item.h"
#incwude "weg.h"

stwuct mwxsw_env_moduwe_info {
	u64 moduwe_ovewheat_countew;
	boow is_ovewheat;
	int num_powts_mapped;
	int num_powts_up;
	enum ethtoow_moduwe_powew_mode_powicy powew_mode_powicy;
	enum mwxsw_weg_pmtm_moduwe_type type;
};

stwuct mwxsw_env_wine_cawd {
	u8 moduwe_count;
	boow active;
	stwuct mwxsw_env_moduwe_info moduwe_info[];
};

stwuct mwxsw_env {
	stwuct mwxsw_cowe *cowe;
	const stwuct mwxsw_bus_info *bus_info;
	u8 max_moduwe_count; /* Maximum numbew of moduwes pew-swot. */
	u8 num_of_swots; /* Incwuding the main boawd. */
	u8 max_eepwom_wen; /* Maximum moduwe EEPWOM twansaction wength. */
	stwuct mutex wine_cawds_wock; /* Pwotects wine cawds. */
	stwuct mwxsw_env_wine_cawd *wine_cawds[] __counted_by(num_of_swots);
};

static boow __mwxsw_env_winecawd_is_active(stwuct mwxsw_env *mwxsw_env,
					   u8 swot_index)
{
	wetuwn mwxsw_env->wine_cawds[swot_index]->active;
}

static boow mwxsw_env_winecawd_is_active(stwuct mwxsw_env *mwxsw_env,
					 u8 swot_index)
{
	boow active;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	active = __mwxsw_env_winecawd_is_active(mwxsw_env, swot_index);
	mutex_unwock(&mwxsw_env->wine_cawds_wock);

	wetuwn active;
}

static stwuct
mwxsw_env_moduwe_info *mwxsw_env_moduwe_info_get(stwuct mwxsw_cowe *mwxsw_cowe,
						 u8 swot_index, u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);

	wetuwn &mwxsw_env->wine_cawds[swot_index]->moduwe_info[moduwe];
}

static int __mwxsw_env_vawidate_moduwe_type(stwuct mwxsw_cowe *cowe,
					    u8 swot_index, u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	int eww;

	if (!__mwxsw_env_winecawd_is_active(mwxsw_env, swot_index))
		wetuwn 0;

	moduwe_info = mwxsw_env_moduwe_info_get(cowe, swot_index, moduwe);
	switch (moduwe_info->type) {
	case MWXSW_WEG_PMTM_MODUWE_TYPE_TWISTED_PAIW:
		eww = -EINVAW;
		bweak;
	defauwt:
		eww = 0;
	}

	wetuwn eww;
}

static int mwxsw_env_vawidate_moduwe_type(stwuct mwxsw_cowe *cowe,
					  u8 swot_index, u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(cowe);
	int eww;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	eww = __mwxsw_env_vawidate_moduwe_type(cowe, swot_index, moduwe);
	mutex_unwock(&mwxsw_env->wine_cawds_wock);

	wetuwn eww;
}

static int
mwxsw_env_vawidate_cabwe_ident(stwuct mwxsw_cowe *cowe, u8 swot_index, int id,
			       boow *qsfp, boow *cmis)
{
	chaw mcia_pw[MWXSW_WEG_MCIA_WEN];
	chaw *eepwom_tmp;
	u8 ident;
	int eww;

	eww = mwxsw_env_vawidate_moduwe_type(cowe, swot_index, id);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mcia_pack(mcia_pw, swot_index, id,
			    MWXSW_WEG_MCIA_PAGE0_WO_OFF, 0, 1,
			    MWXSW_WEG_MCIA_I2C_ADDW_WOW);
	eww = mwxsw_weg_quewy(cowe, MWXSW_WEG(mcia), mcia_pw);
	if (eww)
		wetuwn eww;
	eepwom_tmp = mwxsw_weg_mcia_eepwom_data(mcia_pw);
	ident = eepwom_tmp[0];
	*cmis = fawse;
	switch (ident) {
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_SFP:
		*qsfp = fawse;
		bweak;
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP:
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP_PWUS:
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP28:
		*qsfp = twue;
		bweak;
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP_DD:
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_OSFP:
		*qsfp = twue;
		*cmis = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
mwxsw_env_quewy_moduwe_eepwom(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			      int moduwe, u16 offset, u16 size, void *data,
			      boow qsfp, unsigned int *p_wead_size)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	chaw mcia_pw[MWXSW_WEG_MCIA_WEN];
	chaw *eepwom_tmp;
	u16 i2c_addw;
	u8 page = 0;
	int status;
	int eww;

	size = min_t(u16, size, mwxsw_env->max_eepwom_wen);

	if (offset < MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH &&
	    offset + size > MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH)
		/* Cwoss pages wead, wead untiw offset 256 in wow page */
		size = MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH - offset;

	i2c_addw = MWXSW_WEG_MCIA_I2C_ADDW_WOW;
	if (offset >= MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH) {
		if (qsfp) {
			/* When weading uppew pages 1, 2 and 3 the offset
			 * stawts at 128. Pwease wefew to "QSFP+ Memowy Map"
			 * figuwe in SFF-8436 specification and to "CMIS Moduwe
			 * Memowy Map" figuwe in CMIS specification fow
			 * gwaphicaw depiction.
			 */
			page = MWXSW_WEG_MCIA_PAGE_GET(offset);
			offset -= MWXSW_WEG_MCIA_EEPWOM_UP_PAGE_WENGTH * page;
			if (offset + size > MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH)
				size = MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH - offset;
		} ewse {
			/* When weading uppew pages 1, 2 and 3 the offset
			 * stawts at 0 and I2C high addwess is used. Pwease wefew
			 * to "Memowy Owganization" figuwe in SFF-8472
			 * specification fow gwaphicaw depiction.
			 */
			i2c_addw = MWXSW_WEG_MCIA_I2C_ADDW_HIGH;
			offset -= MWXSW_WEG_MCIA_EEPWOM_PAGE_WENGTH;
		}
	}

	mwxsw_weg_mcia_pack(mcia_pw, swot_index, moduwe, page, offset, size,
			    i2c_addw);

	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mcia), mcia_pw);
	if (eww)
		wetuwn eww;

	status = mwxsw_weg_mcia_status_get(mcia_pw);
	if (status)
		wetuwn -EIO;

	eepwom_tmp = mwxsw_weg_mcia_eepwom_data(mcia_pw);
	memcpy(data, eepwom_tmp, size);
	*p_wead_size = size;

	wetuwn 0;
}

int
mwxsw_env_moduwe_temp_thweshowds_get(stwuct mwxsw_cowe *cowe, u8 swot_index,
				     int moduwe, int off, int *temp)
{
	unsigned int moduwe_temp, moduwe_cwit, moduwe_emewg;
	union {
		u8 buf[MWXSW_WEG_MCIA_TH_ITEM_SIZE];
		u16 temp;
	} temp_thwesh;
	chaw mcia_pw[MWXSW_WEG_MCIA_WEN] = {0};
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN];
	chaw *eepwom_tmp;
	boow qsfp, cmis;
	int page;
	int eww;

	mwxsw_weg_mtmp_pack(mtmp_pw, swot_index,
			    MWXSW_WEG_MTMP_MODUWE_INDEX_MIN + moduwe, fawse,
			    fawse);
	eww = mwxsw_weg_quewy(cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww)
		wetuwn eww;
	mwxsw_weg_mtmp_unpack(mtmp_pw, &moduwe_temp, NUWW, &moduwe_cwit,
			      &moduwe_emewg, NUWW);
	if (!moduwe_temp) {
		*temp = 0;
		wetuwn 0;
	}

	/* Vawidate if thweshowd weading is avaiwabwe thwough MTMP wegistew,
	 * othewwise fawwback to wead thwough MCIA.
	 */
	if (moduwe_emewg) {
		*temp = off == SFP_TEMP_HIGH_WAWN ? moduwe_cwit : moduwe_emewg;
		wetuwn 0;
	}

	/* Wead Fwee Side Device Tempewatuwe Thweshowds fwom page 03h
	 * (MSB at wowew byte addwess).
	 * Bytes:
	 * 128-129 - Temp High Awawm (SFP_TEMP_HIGH_AWAWM);
	 * 130-131 - Temp Wow Awawm (SFP_TEMP_WOW_AWAWM);
	 * 132-133 - Temp High Wawning (SFP_TEMP_HIGH_WAWN);
	 * 134-135 - Temp Wow Wawning (SFP_TEMP_WOW_WAWN);
	 */

	/* Vawidate moduwe identifiew vawue. */
	eww = mwxsw_env_vawidate_cabwe_ident(cowe, swot_index, moduwe, &qsfp,
					     &cmis);
	if (eww)
		wetuwn eww;

	if (qsfp) {
		/* Fow QSFP/CMIS moduwe-defined thweshowds awe wocated in page
		 * 02h, othewwise in page 03h.
		 */
		if (cmis)
			page = MWXSW_WEG_MCIA_TH_PAGE_CMIS_NUM;
		ewse
			page = MWXSW_WEG_MCIA_TH_PAGE_NUM;
		mwxsw_weg_mcia_pack(mcia_pw, swot_index, moduwe, page,
				    MWXSW_WEG_MCIA_TH_PAGE_OFF + off,
				    MWXSW_WEG_MCIA_TH_ITEM_SIZE,
				    MWXSW_WEG_MCIA_I2C_ADDW_WOW);
	} ewse {
		mwxsw_weg_mcia_pack(mcia_pw, swot_index, moduwe,
				    MWXSW_WEG_MCIA_PAGE0_WO,
				    off, MWXSW_WEG_MCIA_TH_ITEM_SIZE,
				    MWXSW_WEG_MCIA_I2C_ADDW_HIGH);
	}

	eww = mwxsw_weg_quewy(cowe, MWXSW_WEG(mcia), mcia_pw);
	if (eww)
		wetuwn eww;

	eepwom_tmp = mwxsw_weg_mcia_eepwom_data(mcia_pw);
	memcpy(temp_thwesh.buf, eepwom_tmp, MWXSW_WEG_MCIA_TH_ITEM_SIZE);
	*temp = temp_thwesh.temp * 1000;

	wetuwn 0;
}

int mwxsw_env_get_moduwe_info(stwuct net_device *netdev,
			      stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			      int moduwe, stwuct ethtoow_modinfo *modinfo)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	u8 moduwe_info[MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_SIZE];
	u16 offset = MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_SIZE;
	u8 moduwe_wev_id, moduwe_id, diag_mon;
	unsigned int wead_size;
	int eww;

	if (!mwxsw_env_winecawd_is_active(mwxsw_env, swot_index)) {
		netdev_eww(netdev, "Cannot wead EEPWOM of moduwe on an inactive wine cawd\n");
		wetuwn -EIO;
	}

	eww = mwxsw_env_vawidate_moduwe_type(mwxsw_cowe, swot_index, moduwe);
	if (eww) {
		netdev_eww(netdev,
			   "EEPWOM is not equipped on powt moduwe type");
		wetuwn eww;
	}

	eww = mwxsw_env_quewy_moduwe_eepwom(mwxsw_cowe, swot_index, moduwe, 0,
					    offset, moduwe_info, fawse,
					    &wead_size);
	if (eww)
		wetuwn eww;

	if (wead_size < offset)
		wetuwn -EIO;

	moduwe_wev_id = moduwe_info[MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_WEV_ID];
	moduwe_id = moduwe_info[MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID];

	switch (moduwe_id) {
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP:
		modinfo->type       = ETH_MODUWE_SFF_8436;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		bweak;
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP_PWUS:
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP28:
		if (moduwe_id == MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP28 ||
		    moduwe_wev_id >=
		    MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_WEV_ID_8636) {
			modinfo->type       = ETH_MODUWE_SFF_8636;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_MAX_WEN;
		} ewse {
			modinfo->type       = ETH_MODUWE_SFF_8436;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		}
		bweak;
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_SFP:
		/* Vewify if twansceivew pwovides diagnostic monitowing page */
		eww = mwxsw_env_quewy_moduwe_eepwom(mwxsw_cowe, swot_index,
						    moduwe, SFP_DIAGMON, 1,
						    &diag_mon, fawse,
						    &wead_size);
		if (eww)
			wetuwn eww;

		if (wead_size < 1)
			wetuwn -EIO;

		modinfo->type       = ETH_MODUWE_SFF_8472;
		if (diag_mon)
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		ewse
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN / 2;
		bweak;
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_QSFP_DD:
	case MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_ID_OSFP:
		/* Use SFF_8636 as base type. ethtoow shouwd wecognize specific
		 * type thwough the identifiew vawue.
		 */
		modinfo->type       = ETH_MODUWE_SFF_8636;
		/* Vewify if moduwe EEPWOM is a fwat memowy. In case of fwat
		 * memowy onwy page 00h (0-255 bytes) can be wead. Othewwise
		 * uppew pages 01h and 02h can awso be wead. Uppew pages 10h
		 * and 11h awe cuwwentwy not suppowted by the dwivew.
		 */
		if (moduwe_info[MWXSW_WEG_MCIA_EEPWOM_MODUWE_INFO_TYPE_ID] &
		    MWXSW_WEG_MCIA_EEPWOM_CMIS_FWAT_MEMOWY)
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_WEN;
		ewse
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mwxsw_env_get_moduwe_info);

int mwxsw_env_get_moduwe_eepwom(stwuct net_device *netdev,
				stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				int moduwe, stwuct ethtoow_eepwom *ee,
				u8 *data)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	int offset = ee->offset;
	unsigned int wead_size;
	boow qsfp, cmis;
	int i = 0;
	int eww;

	if (!ee->wen)
		wetuwn -EINVAW;

	if (!mwxsw_env_winecawd_is_active(mwxsw_env, swot_index)) {
		netdev_eww(netdev, "Cannot wead EEPWOM of moduwe on an inactive wine cawd\n");
		wetuwn -EIO;
	}

	memset(data, 0, ee->wen);
	/* Vawidate moduwe identifiew vawue. */
	eww = mwxsw_env_vawidate_cabwe_ident(mwxsw_cowe, swot_index, moduwe,
					     &qsfp, &cmis);
	if (eww)
		wetuwn eww;

	whiwe (i < ee->wen) {
		eww = mwxsw_env_quewy_moduwe_eepwom(mwxsw_cowe, swot_index,
						    moduwe, offset,
						    ee->wen - i, data + i,
						    qsfp, &wead_size);
		if (eww) {
			netdev_eww(netdev, "Eepwom quewy faiwed\n");
			wetuwn eww;
		}

		i += wead_size;
		offset += wead_size;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mwxsw_env_get_moduwe_eepwom);

static int mwxsw_env_mcia_status_pwocess(const chaw *mcia_pw,
					 stwuct netwink_ext_ack *extack)
{
	u8 status = mwxsw_weg_mcia_status_get(mcia_pw);

	switch (status) {
	case MWXSW_WEG_MCIA_STATUS_GOOD:
		wetuwn 0;
	case MWXSW_WEG_MCIA_STATUS_NO_EEPWOM_MODUWE:
		NW_SET_EWW_MSG_MOD(extack, "No wesponse fwom moduwe's EEPWOM");
		wetuwn -EIO;
	case MWXSW_WEG_MCIA_STATUS_MODUWE_NOT_SUPPOWTED:
		NW_SET_EWW_MSG_MOD(extack, "Moduwe type not suppowted by the device");
		wetuwn -EOPNOTSUPP;
	case MWXSW_WEG_MCIA_STATUS_MODUWE_NOT_CONNECTED:
		NW_SET_EWW_MSG_MOD(extack, "No moduwe pwesent indication");
		wetuwn -EIO;
	case MWXSW_WEG_MCIA_STATUS_I2C_EWWOW:
		NW_SET_EWW_MSG_MOD(extack, "Ewwow occuwwed whiwe twying to access moduwe's EEPWOM using I2C");
		wetuwn -EIO;
	case MWXSW_WEG_MCIA_STATUS_MODUWE_DISABWED:
		NW_SET_EWW_MSG_MOD(extack, "Moduwe is disabwed");
		wetuwn -EIO;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Unknown ewwow");
		wetuwn -EIO;
	}
}

int
mwxsw_env_get_moduwe_eepwom_by_page(stwuct mwxsw_cowe *mwxsw_cowe,
				    u8 swot_index, u8 moduwe,
				    const stwuct ethtoow_moduwe_eepwom *page,
				    stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	u32 bytes_wead = 0;
	u16 device_addw;
	int eww;

	if (!mwxsw_env_winecawd_is_active(mwxsw_env, swot_index)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot wead EEPWOM of moduwe on an inactive wine cawd");
		wetuwn -EIO;
	}

	eww = mwxsw_env_vawidate_moduwe_type(mwxsw_cowe, swot_index, moduwe);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "EEPWOM is not equipped on powt moduwe type");
		wetuwn eww;
	}

	/* Offset cannot be wawgew than 2 * ETH_MODUWE_EEPWOM_PAGE_WEN */
	device_addw = page->offset;

	whiwe (bytes_wead < page->wength) {
		chaw mcia_pw[MWXSW_WEG_MCIA_WEN];
		chaw *eepwom_tmp;
		u8 size;

		size = min_t(u8, page->wength - bytes_wead,
			     mwxsw_env->max_eepwom_wen);

		mwxsw_weg_mcia_pack(mcia_pw, swot_index, moduwe, page->page,
				    device_addw + bytes_wead, size,
				    page->i2c_addwess);
		mwxsw_weg_mcia_bank_numbew_set(mcia_pw, page->bank);

		eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mcia), mcia_pw);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to access moduwe's EEPWOM");
			wetuwn eww;
		}

		eww = mwxsw_env_mcia_status_pwocess(mcia_pw, extack);
		if (eww)
			wetuwn eww;

		eepwom_tmp = mwxsw_weg_mcia_eepwom_data(mcia_pw);
		memcpy(page->data + bytes_wead, eepwom_tmp, size);
		bytes_wead += size;
	}

	wetuwn bytes_wead;
}
EXPOWT_SYMBOW(mwxsw_env_get_moduwe_eepwom_by_page);

static int mwxsw_env_moduwe_weset(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				  u8 moduwe)
{
	chaw pmaos_pw[MWXSW_WEG_PMAOS_WEN];

	mwxsw_weg_pmaos_pack(pmaos_pw, swot_index, moduwe);
	mwxsw_weg_pmaos_wst_set(pmaos_pw, twue);

	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(pmaos), pmaos_pw);
}

int mwxsw_env_weset_moduwe(stwuct net_device *netdev,
			   stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			   u8 moduwe, u32 *fwags)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	u32 weq = *fwags;
	int eww;

	if (!(weq & ETH_WESET_PHY) &&
	    !(weq & (ETH_WESET_PHY << ETH_WESET_SHAWED_SHIFT)))
		wetuwn 0;

	if (!mwxsw_env_winecawd_is_active(mwxsw_env, swot_index)) {
		netdev_eww(netdev, "Cannot weset moduwe on an inactive wine cawd\n");
		wetuwn -EIO;
	}

	mutex_wock(&mwxsw_env->wine_cawds_wock);

	eww = __mwxsw_env_vawidate_moduwe_type(mwxsw_cowe, swot_index, moduwe);
	if (eww) {
		netdev_eww(netdev, "Weset moduwe is not suppowted on powt moduwe type\n");
		goto out;
	}

	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	if (moduwe_info->num_powts_up) {
		netdev_eww(netdev, "Cannot weset moduwe when powts using it awe administwativewy up\n");
		eww = -EINVAW;
		goto out;
	}

	if (moduwe_info->num_powts_mapped > 1 &&
	    !(weq & (ETH_WESET_PHY << ETH_WESET_SHAWED_SHIFT))) {
		netdev_eww(netdev, "Cannot weset moduwe without \"phy-shawed\" fwag when shawed by muwtipwe powts\n");
		eww = -EINVAW;
		goto out;
	}

	eww = mwxsw_env_moduwe_weset(mwxsw_cowe, swot_index, moduwe);
	if (eww) {
		netdev_eww(netdev, "Faiwed to weset moduwe\n");
		goto out;
	}

	*fwags &= ~(ETH_WESET_PHY | (ETH_WESET_PHY << ETH_WESET_SHAWED_SHIFT));

out:
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwxsw_env_weset_moduwe);

int
mwxsw_env_get_moduwe_powew_mode(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				u8 moduwe,
				stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	chaw mcion_pw[MWXSW_WEG_MCION_WEN];
	u32 status_bits;
	int eww = 0;

	mutex_wock(&mwxsw_env->wine_cawds_wock);

	eww = __mwxsw_env_vawidate_moduwe_type(mwxsw_cowe, swot_index, moduwe);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Powew mode is not suppowted on powt moduwe type");
		goto out;
	}

	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	pawams->powicy = moduwe_info->powew_mode_powicy;

	/* Avoid accessing an inactive wine cawd, as it wiww wesuwt in an ewwow. */
	if (!__mwxsw_env_winecawd_is_active(mwxsw_env, swot_index))
		goto out;

	mwxsw_weg_mcion_pack(mcion_pw, swot_index, moduwe);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mcion), mcion_pw);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wetwieve moduwe's powew mode");
		goto out;
	}

	status_bits = mwxsw_weg_mcion_moduwe_status_bits_get(mcion_pw);
	if (!(status_bits & MWXSW_WEG_MCION_MODUWE_STATUS_BITS_PWESENT_MASK))
		goto out;

	if (status_bits & MWXSW_WEG_MCION_MODUWE_STATUS_BITS_WOW_POWEW_MASK)
		pawams->mode = ETHTOOW_MODUWE_POWEW_MODE_WOW;
	ewse
		pawams->mode = ETHTOOW_MODUWE_POWEW_MODE_HIGH;

out:
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwxsw_env_get_moduwe_powew_mode);

static int mwxsw_env_moduwe_enabwe_set(stwuct mwxsw_cowe *mwxsw_cowe,
				       u8 swot_index, u8 moduwe, boow enabwe)
{
	enum mwxsw_weg_pmaos_admin_status admin_status;
	chaw pmaos_pw[MWXSW_WEG_PMAOS_WEN];

	mwxsw_weg_pmaos_pack(pmaos_pw, swot_index, moduwe);
	admin_status = enabwe ? MWXSW_WEG_PMAOS_ADMIN_STATUS_ENABWED :
				MWXSW_WEG_PMAOS_ADMIN_STATUS_DISABWED;
	mwxsw_weg_pmaos_admin_status_set(pmaos_pw, admin_status);
	mwxsw_weg_pmaos_ase_set(pmaos_pw, twue);

	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(pmaos), pmaos_pw);
}

static int mwxsw_env_moduwe_wow_powew_set(stwuct mwxsw_cowe *mwxsw_cowe,
					  u8 swot_index, u8 moduwe,
					  boow wow_powew)
{
	u16 eepwom_ovewwide_mask, eepwom_ovewwide;
	chaw pmmp_pw[MWXSW_WEG_PMMP_WEN];

	mwxsw_weg_pmmp_pack(pmmp_pw, swot_index, moduwe);
	mwxsw_weg_pmmp_sticky_set(pmmp_pw, twue);
	/* Mask aww the bits except wow powew mode. */
	eepwom_ovewwide_mask = ~MWXSW_WEG_PMMP_EEPWOM_OVEWWIDE_WOW_POWEW_MASK;
	mwxsw_weg_pmmp_eepwom_ovewwide_mask_set(pmmp_pw, eepwom_ovewwide_mask);
	eepwom_ovewwide = wow_powew ? MWXSW_WEG_PMMP_EEPWOM_OVEWWIDE_WOW_POWEW_MASK :
				      0;
	mwxsw_weg_pmmp_eepwom_ovewwide_set(pmmp_pw, eepwom_ovewwide);

	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(pmmp), pmmp_pw);
}

static int __mwxsw_env_set_moduwe_powew_mode(stwuct mwxsw_cowe *mwxsw_cowe,
					     u8 swot_index, u8 moduwe,
					     boow wow_powew,
					     stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	int eww;

	/* Avoid accessing an inactive wine cawd, as it wiww wesuwt in an ewwow.
	 * Cached configuwation wiww be appwied by mwxsw_env_got_active() when
	 * wine cawd becomes active.
	 */
	if (!__mwxsw_env_winecawd_is_active(mwxsw_env, swot_index))
		wetuwn 0;

	eww = mwxsw_env_moduwe_enabwe_set(mwxsw_cowe, swot_index, moduwe, fawse);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to disabwe moduwe");
		wetuwn eww;
	}

	eww = mwxsw_env_moduwe_wow_powew_set(mwxsw_cowe, swot_index, moduwe,
					     wow_powew);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to set moduwe's powew mode");
		goto eww_moduwe_wow_powew_set;
	}

	eww = mwxsw_env_moduwe_enabwe_set(mwxsw_cowe, swot_index, moduwe, twue);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to enabwe moduwe");
		goto eww_moduwe_enabwe_set;
	}

	wetuwn 0;

eww_moduwe_enabwe_set:
	mwxsw_env_moduwe_wow_powew_set(mwxsw_cowe, swot_index, moduwe,
				       !wow_powew);
eww_moduwe_wow_powew_set:
	mwxsw_env_moduwe_enabwe_set(mwxsw_cowe, swot_index, moduwe, twue);
	wetuwn eww;
}

static int
mwxsw_env_set_moduwe_powew_mode_appwy(stwuct mwxsw_cowe *mwxsw_cowe,
				      u8 swot_index, u8 moduwe,
				      enum ethtoow_moduwe_powew_mode_powicy powicy,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	boow wow_powew;
	int eww = 0;

	eww = __mwxsw_env_vawidate_moduwe_type(mwxsw_cowe, swot_index, moduwe);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Powew mode set is not suppowted on powt moduwe type");
		goto out;
	}

	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	if (moduwe_info->powew_mode_powicy == powicy)
		goto out;

	/* If any powts awe up, we awe awweady in high powew mode. */
	if (moduwe_info->num_powts_up)
		goto out_set_powicy;

	wow_powew = powicy == ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO;
	eww = __mwxsw_env_set_moduwe_powew_mode(mwxsw_cowe, swot_index, moduwe,
						wow_powew, extack);
	if (eww)
		goto out;

out_set_powicy:
	moduwe_info->powew_mode_powicy = powicy;
out:
	wetuwn eww;
}

int
mwxsw_env_set_moduwe_powew_mode(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				u8 moduwe,
				enum ethtoow_moduwe_powew_mode_powicy powicy,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	int eww;

	if (powicy != ETHTOOW_MODUWE_POWEW_MODE_POWICY_HIGH &&
	    powicy != ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted powew mode powicy");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	eww = mwxsw_env_set_moduwe_powew_mode_appwy(mwxsw_cowe, swot_index,
						    moduwe, powicy, extack);
	mutex_unwock(&mwxsw_env->wine_cawds_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwxsw_env_set_moduwe_powew_mode);

static int mwxsw_env_moduwe_has_temp_sensow(stwuct mwxsw_cowe *mwxsw_cowe,
					    u8 swot_index, u8 moduwe,
					    boow *p_has_temp_sensow)
{
	chaw mtbw_pw[MWXSW_WEG_MTBW_WEN];
	u16 temp;
	int eww;

	mwxsw_weg_mtbw_pack(mtbw_pw, swot_index,
			    MWXSW_WEG_MTBW_BASE_MODUWE_INDEX + moduwe);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mtbw), mtbw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mtbw_temp_unpack(mtbw_pw, 0, &temp, NUWW);

	switch (temp) {
	case MWXSW_WEG_MTBW_BAD_SENS_INFO:
	case MWXSW_WEG_MTBW_NO_CONN:
	case MWXSW_WEG_MTBW_NO_TEMP_SENS:
	case MWXSW_WEG_MTBW_INDEX_NA:
		*p_has_temp_sensow = fawse;
		bweak;
	defauwt:
		*p_has_temp_sensow = temp ? twue : fawse;
	}
	wetuwn 0;
}

static int
mwxsw_env_temp_event_set(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			 u16 sensow_index, boow enabwe)
{
	chaw mtmp_pw[MWXSW_WEG_MTMP_WEN] = {0};
	enum mwxsw_weg_mtmp_tee tee;
	int eww, thweshowd_hi;

	mwxsw_weg_mtmp_swot_index_set(mtmp_pw, swot_index);
	mwxsw_weg_mtmp_sensow_index_set(mtmp_pw, sensow_index);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mtmp), mtmp_pw);
	if (eww)
		wetuwn eww;

	if (enabwe) {
		eww = mwxsw_env_moduwe_temp_thweshowds_get(mwxsw_cowe,
							   swot_index,
							   sensow_index -
							   MWXSW_WEG_MTMP_MODUWE_INDEX_MIN,
							   SFP_TEMP_HIGH_WAWN,
							   &thweshowd_hi);
		/* In case it is not possibwe to quewy the moduwe's thweshowd,
		 * use the defauwt vawue.
		 */
		if (eww)
			thweshowd_hi = MWXSW_WEG_MTMP_THWESH_HI;
		ewse
			/* mwxsw_env_moduwe_temp_thweshowds_get() muwtipwies
			 * Cewsius degwees by 1000 wheweas MTMP expects
			 * tempewatuwe in 0.125 Cewsius degwees units.
			 * Convewt thweshowd_hi to cowwect units.
			 */
			thweshowd_hi = thweshowd_hi / 1000 * 8;

		mwxsw_weg_mtmp_tempewatuwe_thweshowd_hi_set(mtmp_pw, thweshowd_hi);
		mwxsw_weg_mtmp_tempewatuwe_thweshowd_wo_set(mtmp_pw, thweshowd_hi -
							    MWXSW_WEG_MTMP_HYSTEWESIS_TEMP);
	}
	tee = enabwe ? MWXSW_WEG_MTMP_TEE_GENEWATE_EVENT : MWXSW_WEG_MTMP_TEE_NO_EVENT;
	mwxsw_weg_mtmp_tee_set(mtmp_pw, tee);
	wetuwn mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(mtmp), mtmp_pw);
}

static int mwxsw_env_moduwe_temp_event_enabwe(stwuct mwxsw_cowe *mwxsw_cowe,
					      u8 swot_index)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	int i, eww, sensow_index;
	boow has_temp_sensow;

	fow (i = 0; i < mwxsw_env->wine_cawds[swot_index]->moduwe_count; i++) {
		eww = mwxsw_env_moduwe_has_temp_sensow(mwxsw_cowe, swot_index,
						       i, &has_temp_sensow);
		if (eww)
			wetuwn eww;

		if (!has_temp_sensow)
			continue;

		sensow_index = i + MWXSW_WEG_MTMP_MODUWE_INDEX_MIN;
		eww = mwxsw_env_temp_event_set(mwxsw_cowe, swot_index,
					       sensow_index, twue);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

stwuct mwxsw_env_moduwe_temp_wawn_event {
	stwuct mwxsw_env *mwxsw_env;
	chaw mtwe_pw[MWXSW_WEG_MTWE_WEN];
	stwuct wowk_stwuct wowk;
};

static void mwxsw_env_mtwe_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_env_moduwe_temp_wawn_event *event;
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	stwuct mwxsw_env *mwxsw_env;
	int i, sensow_wawning;
	boow is_ovewheat;

	event = containew_of(wowk, stwuct mwxsw_env_moduwe_temp_wawn_event,
			     wowk);
	mwxsw_env = event->mwxsw_env;

	fow (i = 0; i < mwxsw_env->max_moduwe_count; i++) {
		/* 64-127 of sensow_index awe mapped to the powt moduwes
		 * sequentiawwy (moduwe 0 is mapped to sensow_index 64,
		 * moduwe 1 to sensow_index 65 and so on)
		 */
		sensow_wawning =
			mwxsw_weg_mtwe_sensow_wawning_get(event->mtwe_pw,
							  i + MWXSW_WEG_MTMP_MODUWE_INDEX_MIN);
		mutex_wock(&mwxsw_env->wine_cawds_wock);
		/* MTWE onwy suppowts main boawd. */
		moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_env->cowe, 0, i);
		is_ovewheat = moduwe_info->is_ovewheat;

		if ((is_ovewheat && sensow_wawning) ||
		    (!is_ovewheat && !sensow_wawning)) {
			/* Cuwwent state is "wawning" and MTWE stiww wepowts
			 * wawning OW cuwwent state in "no wawning" and MTWE
			 * does not wepowt wawning.
			 */
			mutex_unwock(&mwxsw_env->wine_cawds_wock);
			continue;
		} ewse if (is_ovewheat && !sensow_wawning) {
			/* MTWE wepowts "no wawning", tuwn is_ovewheat off.
			 */
			moduwe_info->is_ovewheat = fawse;
			mutex_unwock(&mwxsw_env->wine_cawds_wock);
		} ewse {
			/* Cuwwent state is "no wawning" and MTWE wepowts
			 * "wawning", incwease the countew and tuwn is_ovewheat
			 * on.
			 */
			moduwe_info->is_ovewheat = twue;
			moduwe_info->moduwe_ovewheat_countew++;
			mutex_unwock(&mwxsw_env->wine_cawds_wock);
		}
	}

	kfwee(event);
}

static void
mwxsw_env_mtwe_wistenew_func(const stwuct mwxsw_weg_info *weg, chaw *mtwe_pw,
			     void *pwiv)
{
	stwuct mwxsw_env_moduwe_temp_wawn_event *event;
	stwuct mwxsw_env *mwxsw_env = pwiv;

	event = kmawwoc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		wetuwn;

	event->mwxsw_env = mwxsw_env;
	memcpy(event->mtwe_pw, mtwe_pw, MWXSW_WEG_MTWE_WEN);
	INIT_WOWK(&event->wowk, mwxsw_env_mtwe_event_wowk);
	mwxsw_cowe_scheduwe_wowk(&event->wowk);
}

static const stwuct mwxsw_wistenew mwxsw_env_temp_wawn_wistenew =
	MWXSW_COWE_EVENTW(mwxsw_env_mtwe_wistenew_func, MTWE);

static int mwxsw_env_temp_wawn_event_wegistew(stwuct mwxsw_cowe *mwxsw_cowe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);

	wetuwn mwxsw_cowe_twap_wegistew(mwxsw_cowe,
					&mwxsw_env_temp_wawn_wistenew,
					mwxsw_env);
}

static void mwxsw_env_temp_wawn_event_unwegistew(stwuct mwxsw_env *mwxsw_env)
{
	mwxsw_cowe_twap_unwegistew(mwxsw_env->cowe,
				   &mwxsw_env_temp_wawn_wistenew, mwxsw_env);
}

stwuct mwxsw_env_moduwe_pwug_unpwug_event {
	stwuct mwxsw_env *mwxsw_env;
	u8 swot_index;
	u8 moduwe;
	stwuct wowk_stwuct wowk;
};

static void mwxsw_env_pmpe_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_env_moduwe_pwug_unpwug_event *event;
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	stwuct mwxsw_env *mwxsw_env;
	boow has_temp_sensow;
	u16 sensow_index;
	int eww;

	event = containew_of(wowk, stwuct mwxsw_env_moduwe_pwug_unpwug_event,
			     wowk);
	mwxsw_env = event->mwxsw_env;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_env->cowe,
						event->swot_index,
						event->moduwe);
	moduwe_info->is_ovewheat = fawse;
	mutex_unwock(&mwxsw_env->wine_cawds_wock);

	eww = mwxsw_env_moduwe_has_temp_sensow(mwxsw_env->cowe,
					       event->swot_index,
					       event->moduwe,
					       &has_temp_sensow);
	/* Do not disabwe events on moduwes without sensows ow fauwty sensows
	 * because FW wetuwns ewwows.
	 */
	if (eww)
		goto out;

	if (!has_temp_sensow)
		goto out;

	sensow_index = event->moduwe + MWXSW_WEG_MTMP_MODUWE_INDEX_MIN;
	mwxsw_env_temp_event_set(mwxsw_env->cowe, event->swot_index,
				 sensow_index, twue);

out:
	kfwee(event);
}

static void
mwxsw_env_pmpe_wistenew_func(const stwuct mwxsw_weg_info *weg, chaw *pmpe_pw,
			     void *pwiv)
{
	u8 swot_index = mwxsw_weg_pmpe_swot_index_get(pmpe_pw);
	stwuct mwxsw_env_moduwe_pwug_unpwug_event *event;
	enum mwxsw_weg_pmpe_moduwe_status moduwe_status;
	u8 moduwe = mwxsw_weg_pmpe_moduwe_get(pmpe_pw);
	stwuct mwxsw_env *mwxsw_env = pwiv;

	if (WAWN_ON_ONCE(moduwe >= mwxsw_env->max_moduwe_count ||
			 swot_index >= mwxsw_env->num_of_swots))
		wetuwn;

	moduwe_status = mwxsw_weg_pmpe_moduwe_status_get(pmpe_pw);
	if (moduwe_status != MWXSW_WEG_PMPE_MODUWE_STATUS_PWUGGED_ENABWED)
		wetuwn;

	event = kmawwoc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		wetuwn;

	event->mwxsw_env = mwxsw_env;
	event->swot_index = swot_index;
	event->moduwe = moduwe;
	INIT_WOWK(&event->wowk, mwxsw_env_pmpe_event_wowk);
	mwxsw_cowe_scheduwe_wowk(&event->wowk);
}

static const stwuct mwxsw_wistenew mwxsw_env_moduwe_pwug_wistenew =
	MWXSW_COWE_EVENTW(mwxsw_env_pmpe_wistenew_func, PMPE);

static int
mwxsw_env_moduwe_pwug_event_wegistew(stwuct mwxsw_cowe *mwxsw_cowe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);

	wetuwn mwxsw_cowe_twap_wegistew(mwxsw_cowe,
					&mwxsw_env_moduwe_pwug_wistenew,
					mwxsw_env);
}

static void
mwxsw_env_moduwe_pwug_event_unwegistew(stwuct mwxsw_env *mwxsw_env)
{
	mwxsw_cowe_twap_unwegistew(mwxsw_env->cowe,
				   &mwxsw_env_moduwe_pwug_wistenew,
				   mwxsw_env);
}

static int
mwxsw_env_moduwe_opew_state_event_enabwe(stwuct mwxsw_cowe *mwxsw_cowe,
					 u8 swot_index)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	int i, eww;

	fow (i = 0; i < mwxsw_env->wine_cawds[swot_index]->moduwe_count; i++) {
		chaw pmaos_pw[MWXSW_WEG_PMAOS_WEN];

		mwxsw_weg_pmaos_pack(pmaos_pw, swot_index, i);
		mwxsw_weg_pmaos_e_set(pmaos_pw,
				      MWXSW_WEG_PMAOS_E_GENEWATE_EVENT);
		mwxsw_weg_pmaos_ee_set(pmaos_pw, twue);
		eww = mwxsw_weg_wwite(mwxsw_cowe, MWXSW_WEG(pmaos), pmaos_pw);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

int
mwxsw_env_moduwe_ovewheat_countew_get(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				      u8 moduwe, u64 *p_countew)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	*p_countew = moduwe_info->moduwe_ovewheat_countew;
	mutex_unwock(&mwxsw_env->wine_cawds_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(mwxsw_env_moduwe_ovewheat_countew_get);

void mwxsw_env_moduwe_powt_map(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			       u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	moduwe_info->num_powts_mapped++;
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
}
EXPOWT_SYMBOW(mwxsw_env_moduwe_powt_map);

void mwxsw_env_moduwe_powt_unmap(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				 u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	moduwe_info->num_powts_mapped--;
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
}
EXPOWT_SYMBOW(mwxsw_env_moduwe_powt_unmap);

int mwxsw_env_moduwe_powt_up(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			     u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	int eww = 0;

	mutex_wock(&mwxsw_env->wine_cawds_wock);

	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	if (moduwe_info->powew_mode_powicy !=
	    ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO)
		goto out_inc;

	if (moduwe_info->num_powts_up != 0)
		goto out_inc;

	/* Twansition to high powew mode fowwowing fiwst powt using the moduwe
	 * being put administwativewy up.
	 */
	eww = __mwxsw_env_set_moduwe_powew_mode(mwxsw_cowe, swot_index, moduwe,
						fawse, NUWW);
	if (eww)
		goto out_unwock;

out_inc:
	moduwe_info->num_powts_up++;
out_unwock:
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwxsw_env_moduwe_powt_up);

void mwxsw_env_moduwe_powt_down(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				u8 moduwe)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	stwuct mwxsw_env_moduwe_info *moduwe_info;

	mutex_wock(&mwxsw_env->wine_cawds_wock);

	moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index, moduwe);
	moduwe_info->num_powts_up--;

	if (moduwe_info->powew_mode_powicy !=
	    ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO)
		goto out_unwock;

	if (moduwe_info->num_powts_up != 0)
		goto out_unwock;

	/* Twansition to wow powew mode fowwowing wast powt using the moduwe
	 * being put administwativewy down.
	 */
	__mwxsw_env_set_moduwe_powew_mode(mwxsw_cowe, swot_index, moduwe, twue,
					  NUWW);

out_unwock:
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
}
EXPOWT_SYMBOW(mwxsw_env_moduwe_powt_down);

static int mwxsw_env_wine_cawds_awwoc(stwuct mwxsw_env *env)
{
	stwuct mwxsw_env_moduwe_info *moduwe_info;
	int i, j;

	fow (i = 0; i < env->num_of_swots; i++) {
		env->wine_cawds[i] = kzawwoc(stwuct_size(env->wine_cawds[i],
							 moduwe_info,
							 env->max_moduwe_count),
							 GFP_KEWNEW);
		if (!env->wine_cawds[i])
			goto kzawwoc_eww;

		/* Fiwmwawe defauwts to high powew mode powicy whewe moduwes
		 * awe twansitioned to high powew mode fowwowing pwug-in.
		 */
		fow (j = 0; j < env->max_moduwe_count; j++) {
			moduwe_info = &env->wine_cawds[i]->moduwe_info[j];
			moduwe_info->powew_mode_powicy =
					ETHTOOW_MODUWE_POWEW_MODE_POWICY_HIGH;
		}
	}

	wetuwn 0;

kzawwoc_eww:
	fow (i--; i >= 0; i--)
		kfwee(env->wine_cawds[i]);
	wetuwn -ENOMEM;
}

static void mwxsw_env_wine_cawds_fwee(stwuct mwxsw_env *env)
{
	int i = env->num_of_swots;

	fow (i--; i >= 0; i--)
		kfwee(env->wine_cawds[i]);
}

static int
mwxsw_env_moduwe_event_enabwe(stwuct mwxsw_env *mwxsw_env, u8 swot_index)
{
	int eww;

	eww = mwxsw_env_moduwe_opew_state_event_enabwe(mwxsw_env->cowe,
						       swot_index);
	if (eww)
		wetuwn eww;

	eww = mwxsw_env_moduwe_temp_event_enabwe(mwxsw_env->cowe, swot_index);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void
mwxsw_env_moduwe_event_disabwe(stwuct mwxsw_env *mwxsw_env, u8 swot_index)
{
}

static int
mwxsw_env_moduwe_type_set(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index)
{
	stwuct mwxsw_env *mwxsw_env = mwxsw_cowe_env(mwxsw_cowe);
	int i;

	fow (i = 0; i < mwxsw_env->wine_cawds[swot_index]->moduwe_count; i++) {
		stwuct mwxsw_env_moduwe_info *moduwe_info;
		chaw pmtm_pw[MWXSW_WEG_PMTM_WEN];
		int eww;

		mwxsw_weg_pmtm_pack(pmtm_pw, swot_index, i);
		eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(pmtm), pmtm_pw);
		if (eww)
			wetuwn eww;

		moduwe_info = mwxsw_env_moduwe_info_get(mwxsw_cowe, swot_index,
							i);
		moduwe_info->type = mwxsw_weg_pmtm_moduwe_type_get(pmtm_pw);
	}

	wetuwn 0;
}

static void
mwxsw_env_winecawd_moduwes_powew_mode_appwy(stwuct mwxsw_cowe *mwxsw_cowe,
					    stwuct mwxsw_env *env,
					    u8 swot_index)
{
	int i;

	fow (i = 0; i < env->wine_cawds[swot_index]->moduwe_count; i++) {
		enum ethtoow_moduwe_powew_mode_powicy powicy;
		stwuct mwxsw_env_moduwe_info *moduwe_info;
		stwuct netwink_ext_ack extack;
		int eww;

		moduwe_info = &env->wine_cawds[swot_index]->moduwe_info[i];
		powicy = moduwe_info->powew_mode_powicy;
		eww = mwxsw_env_set_moduwe_powew_mode_appwy(mwxsw_cowe,
							    swot_index, i,
							    powicy, &extack);
		if (eww)
			dev_eww(env->bus_info->dev, "%s\n", extack._msg);
	}
}

static void
mwxsw_env_got_active(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index, void *pwiv)
{
	stwuct mwxsw_env *mwxsw_env = pwiv;
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	int eww;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	if (__mwxsw_env_winecawd_is_active(mwxsw_env, swot_index))
		goto out_unwock;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, swot_index);
	eww = mwxsw_weg_quewy(mwxsw_env->cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		goto out_unwock;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, NUWW, NUWW, NUWW,
			       &mwxsw_env->wine_cawds[swot_index]->moduwe_count,
			       NUWW);

	eww = mwxsw_env_moduwe_event_enabwe(mwxsw_env, swot_index);
	if (eww) {
		dev_eww(mwxsw_env->bus_info->dev, "Faiwed to enabwe powt moduwe events fow wine cawd in swot %d\n",
			swot_index);
		goto eww_mwxsw_env_moduwe_event_enabwe;
	}
	eww = mwxsw_env_moduwe_type_set(mwxsw_env->cowe, swot_index);
	if (eww) {
		dev_eww(mwxsw_env->bus_info->dev, "Faiwed to set moduwes' type fow wine cawd in swot %d\n",
			swot_index);
		goto eww_type_set;
	}

	mwxsw_env->wine_cawds[swot_index]->active = twue;
	/* Appwy powew mode powicy. */
	mwxsw_env_winecawd_moduwes_powew_mode_appwy(mwxsw_cowe, mwxsw_env,
						    swot_index);
	mutex_unwock(&mwxsw_env->wine_cawds_wock);

	wetuwn;

eww_type_set:
	mwxsw_env_moduwe_event_disabwe(mwxsw_env, swot_index);
eww_mwxsw_env_moduwe_event_enabwe:
out_unwock:
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
}

static void
mwxsw_env_got_inactive(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
		       void *pwiv)
{
	stwuct mwxsw_env *mwxsw_env = pwiv;

	mutex_wock(&mwxsw_env->wine_cawds_wock);
	if (!__mwxsw_env_winecawd_is_active(mwxsw_env, swot_index))
		goto out_unwock;
	mwxsw_env->wine_cawds[swot_index]->active = fawse;
	mwxsw_env_moduwe_event_disabwe(mwxsw_env, swot_index);
	mwxsw_env->wine_cawds[swot_index]->moduwe_count = 0;
out_unwock:
	mutex_unwock(&mwxsw_env->wine_cawds_wock);
}

static stwuct mwxsw_winecawds_event_ops mwxsw_env_event_ops = {
	.got_active = mwxsw_env_got_active,
	.got_inactive = mwxsw_env_got_inactive,
};

static int mwxsw_env_max_moduwe_eepwom_wen_quewy(stwuct mwxsw_env *mwxsw_env)
{
	chaw mcam_pw[MWXSW_WEG_MCAM_WEN];
	boow mcia_128b_suppowted;
	int eww;

	mwxsw_weg_mcam_pack(mcam_pw,
			    MWXSW_WEG_MCAM_FEATUWE_GWOUP_ENHANCED_FEATUWES);
	eww = mwxsw_weg_quewy(mwxsw_env->cowe, MWXSW_WEG(mcam), mcam_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mcam_unpack(mcam_pw, MWXSW_WEG_MCAM_MCIA_128B,
			      &mcia_128b_suppowted);

	mwxsw_env->max_eepwom_wen = mcia_128b_suppowted ? 128 : 48;

	wetuwn 0;
}

int mwxsw_env_init(stwuct mwxsw_cowe *mwxsw_cowe,
		   const stwuct mwxsw_bus_info *bus_info,
		   stwuct mwxsw_env **p_env)
{
	u8 moduwe_count, num_of_swots, max_moduwe_count;
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	stwuct mwxsw_env *env;
	int eww;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, 0);
	eww = mwxsw_weg_quewy(mwxsw_cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, NUWW, NUWW, NUWW, &moduwe_count,
			       &num_of_swots);
	/* If the system is moduwaw, get the maximum numbew of moduwes pew-swot.
	 * Othewwise, get the maximum numbew of moduwes on the main boawd.
	 */
	max_moduwe_count = num_of_swots ?
			   mwxsw_weg_mgpiw_max_moduwes_pew_swot_get(mgpiw_pw) :
			   moduwe_count;

	env = kzawwoc(stwuct_size(env, wine_cawds, num_of_swots + 1),
		      GFP_KEWNEW);
	if (!env)
		wetuwn -ENOMEM;

	env->cowe = mwxsw_cowe;
	env->bus_info = bus_info;
	env->num_of_swots = num_of_swots + 1;
	env->max_moduwe_count = max_moduwe_count;
	eww = mwxsw_env_wine_cawds_awwoc(env);
	if (eww)
		goto eww_mwxsw_env_wine_cawds_awwoc;

	mutex_init(&env->wine_cawds_wock);
	*p_env = env;

	eww = mwxsw_winecawds_event_ops_wegistew(env->cowe,
						 &mwxsw_env_event_ops, env);
	if (eww)
		goto eww_winecawds_event_ops_wegistew;

	eww = mwxsw_env_temp_wawn_event_wegistew(mwxsw_cowe);
	if (eww)
		goto eww_temp_wawn_event_wegistew;

	eww = mwxsw_env_moduwe_pwug_event_wegistew(mwxsw_cowe);
	if (eww)
		goto eww_moduwe_pwug_event_wegistew;

	/* Set 'moduwe_count' onwy fow main boawd. Actuaw count fow wine cawd
	 * is to be set aftew wine cawd is activated.
	 */
	env->wine_cawds[0]->moduwe_count = num_of_swots ? 0 : moduwe_count;
	/* Enabwe events onwy fow main boawd. Wine cawd events awe to be
	 * configuwed onwy aftew wine cawd is activated. Befowe that, access to
	 * moduwes on wine cawds is not awwowed.
	 */
	eww = mwxsw_env_moduwe_event_enabwe(env, 0);
	if (eww)
		goto eww_mwxsw_env_moduwe_event_enabwe;

	eww = mwxsw_env_moduwe_type_set(mwxsw_cowe, 0);
	if (eww)
		goto eww_type_set;

	eww = mwxsw_env_max_moduwe_eepwom_wen_quewy(env);
	if (eww)
		goto eww_eepwom_wen_quewy;

	env->wine_cawds[0]->active = twue;

	wetuwn 0;

eww_eepwom_wen_quewy:
eww_type_set:
	mwxsw_env_moduwe_event_disabwe(env, 0);
eww_mwxsw_env_moduwe_event_enabwe:
	mwxsw_env_moduwe_pwug_event_unwegistew(env);
eww_moduwe_pwug_event_wegistew:
	mwxsw_env_temp_wawn_event_unwegistew(env);
eww_temp_wawn_event_wegistew:
	mwxsw_winecawds_event_ops_unwegistew(env->cowe,
					     &mwxsw_env_event_ops, env);
eww_winecawds_event_ops_wegistew:
	mutex_destwoy(&env->wine_cawds_wock);
	mwxsw_env_wine_cawds_fwee(env);
eww_mwxsw_env_wine_cawds_awwoc:
	kfwee(env);
	wetuwn eww;
}

void mwxsw_env_fini(stwuct mwxsw_env *env)
{
	env->wine_cawds[0]->active = fawse;
	mwxsw_env_moduwe_event_disabwe(env, 0);
	mwxsw_env_moduwe_pwug_event_unwegistew(env);
	/* Make suwe thewe is no mowe event wowk scheduwed. */
	mwxsw_cowe_fwush_owq();
	mwxsw_env_temp_wawn_event_unwegistew(env);
	mwxsw_winecawds_event_ops_unwegistew(env->cowe,
					     &mwxsw_env_event_ops, env);
	mutex_destwoy(&env->wine_cawds_wock);
	mwxsw_env_wine_cawds_fwee(env);
	kfwee(env);
}
