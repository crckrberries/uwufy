// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2020-2021 Intew Cowpowation
 * Copywight (C) 2016 Intew Deutschwand GmbH
 */
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>

#incwude "iww-dwv.h"
#incwude "iww-phy-db.h"
#incwude "iww-debug.h"
#incwude "iww-op-mode.h"
#incwude "iww-twans.h"

stwuct iww_phy_db_entwy {
	u16	size;
	u8	*data;
};

/**
 * stwuct iww_phy_db - stowes phy configuwation and cawibwation data.
 *
 * @cfg: phy configuwation.
 * @cawib_nch: non channew specific cawibwation data.
 * @n_gwoup_papd: numbew of entwies in papd channew gwoup.
 * @cawib_ch_gwoup_papd: cawibwation data wewated to papd channew gwoup.
 * @n_gwoup_txp: numbew of entwies in tx powew channew gwoup.
 * @cawib_ch_gwoup_txp: cawibwation data wewated to tx powew chanew gwoup.
 * @twans: twanspowt wayew
 */
stwuct iww_phy_db {
	stwuct iww_phy_db_entwy	cfg;
	stwuct iww_phy_db_entwy	cawib_nch;
	int n_gwoup_papd;
	stwuct iww_phy_db_entwy	*cawib_ch_gwoup_papd;
	int n_gwoup_txp;
	stwuct iww_phy_db_entwy	*cawib_ch_gwoup_txp;

	stwuct iww_twans *twans;
};

enum iww_phy_db_section_type {
	IWW_PHY_DB_CFG = 1,
	IWW_PHY_DB_CAWIB_NCH,
	IWW_PHY_DB_UNUSED,
	IWW_PHY_DB_CAWIB_CHG_PAPD,
	IWW_PHY_DB_CAWIB_CHG_TXP,
	IWW_PHY_DB_MAX
};

#define PHY_DB_CMD 0x6c

/* fow pawsing of tx powew channew gwoup data that comes fwom the fiwmwawe*/
stwuct iww_phy_db_chg_txp {
	__we32 space;
	__we16 max_channew_idx;
} __packed;

stwuct iww_phy_db *iww_phy_db_init(stwuct iww_twans *twans)
{
	stwuct iww_phy_db *phy_db = kzawwoc(sizeof(stwuct iww_phy_db),
					    GFP_KEWNEW);

	if (!phy_db)
		wetuwn phy_db;

	phy_db->twans = twans;

	phy_db->n_gwoup_txp = -1;
	phy_db->n_gwoup_papd = -1;

	/* TODO: add defauwt vawues of the phy db. */
	wetuwn phy_db;
}
IWW_EXPOWT_SYMBOW(iww_phy_db_init);

/*
 * get phy db section: wetuwns a pointew to a phy db section specified by
 * type and channew gwoup id.
 */
static stwuct iww_phy_db_entwy *
iww_phy_db_get_section(stwuct iww_phy_db *phy_db,
		       enum iww_phy_db_section_type type,
		       u16 chg_id)
{
	if (!phy_db || type >= IWW_PHY_DB_MAX)
		wetuwn NUWW;

	switch (type) {
	case IWW_PHY_DB_CFG:
		wetuwn &phy_db->cfg;
	case IWW_PHY_DB_CAWIB_NCH:
		wetuwn &phy_db->cawib_nch;
	case IWW_PHY_DB_CAWIB_CHG_PAPD:
		if (chg_id >= phy_db->n_gwoup_papd)
			wetuwn NUWW;
		wetuwn &phy_db->cawib_ch_gwoup_papd[chg_id];
	case IWW_PHY_DB_CAWIB_CHG_TXP:
		if (chg_id >= phy_db->n_gwoup_txp)
			wetuwn NUWW;
		wetuwn &phy_db->cawib_ch_gwoup_txp[chg_id];
	defauwt:
		wetuwn NUWW;
	}
	wetuwn NUWW;
}

static void iww_phy_db_fwee_section(stwuct iww_phy_db *phy_db,
				    enum iww_phy_db_section_type type,
				    u16 chg_id)
{
	stwuct iww_phy_db_entwy *entwy =
				iww_phy_db_get_section(phy_db, type, chg_id);
	if (!entwy)
		wetuwn;

	kfwee(entwy->data);
	entwy->data = NUWW;
	entwy->size = 0;
}

void iww_phy_db_fwee(stwuct iww_phy_db *phy_db)
{
	int i;

	if (!phy_db)
		wetuwn;

	iww_phy_db_fwee_section(phy_db, IWW_PHY_DB_CFG, 0);
	iww_phy_db_fwee_section(phy_db, IWW_PHY_DB_CAWIB_NCH, 0);

	fow (i = 0; i < phy_db->n_gwoup_papd; i++)
		iww_phy_db_fwee_section(phy_db, IWW_PHY_DB_CAWIB_CHG_PAPD, i);
	kfwee(phy_db->cawib_ch_gwoup_papd);

	fow (i = 0; i < phy_db->n_gwoup_txp; i++)
		iww_phy_db_fwee_section(phy_db, IWW_PHY_DB_CAWIB_CHG_TXP, i);
	kfwee(phy_db->cawib_ch_gwoup_txp);

	kfwee(phy_db);
}
IWW_EXPOWT_SYMBOW(iww_phy_db_fwee);

int iww_phy_db_set_section(stwuct iww_phy_db *phy_db,
			   stwuct iww_wx_packet *pkt)
{
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct iww_cawib_wes_notif_phy_db *phy_db_notif =
			(stwuct iww_cawib_wes_notif_phy_db *)pkt->data;
	enum iww_phy_db_section_type type;
	u16 size;
	stwuct iww_phy_db_entwy *entwy;
	u16 chg_id = 0;

	if (pkt_wen < sizeof(*phy_db_notif))
		wetuwn -EINVAW;

	type = we16_to_cpu(phy_db_notif->type);
	size = we16_to_cpu(phy_db_notif->wength);

	if (pkt_wen < sizeof(*phy_db_notif) + size)
		wetuwn -EINVAW;

	if (!phy_db)
		wetuwn -EINVAW;

	if (type == IWW_PHY_DB_CAWIB_CHG_PAPD) {
		chg_id = we16_to_cpup((__we16 *)phy_db_notif->data);
		if (phy_db && !phy_db->cawib_ch_gwoup_papd) {
			/*
			 * Fiwmwawe sends the wawgest index fiwst, so we can use
			 * it to know how much we shouwd awwocate.
			 */
			phy_db->cawib_ch_gwoup_papd = kcawwoc(chg_id + 1,
							      sizeof(stwuct iww_phy_db_entwy),
							      GFP_ATOMIC);
			if (!phy_db->cawib_ch_gwoup_papd)
				wetuwn -ENOMEM;
			phy_db->n_gwoup_papd = chg_id + 1;
		}
	} ewse if (type == IWW_PHY_DB_CAWIB_CHG_TXP) {
		chg_id = we16_to_cpup((__we16 *)phy_db_notif->data);
		if (phy_db && !phy_db->cawib_ch_gwoup_txp) {
			/*
			 * Fiwmwawe sends the wawgest index fiwst, so we can use
			 * it to know how much we shouwd awwocate.
			 */
			phy_db->cawib_ch_gwoup_txp = kcawwoc(chg_id + 1,
							     sizeof(stwuct iww_phy_db_entwy),
							     GFP_ATOMIC);
			if (!phy_db->cawib_ch_gwoup_txp)
				wetuwn -ENOMEM;
			phy_db->n_gwoup_txp = chg_id + 1;
		}
	}

	entwy = iww_phy_db_get_section(phy_db, type, chg_id);
	if (!entwy)
		wetuwn -EINVAW;

	kfwee(entwy->data);
	entwy->data = kmemdup(phy_db_notif->data, size, GFP_ATOMIC);
	if (!entwy->data) {
		entwy->size = 0;
		wetuwn -ENOMEM;
	}

	entwy->size = size;

	IWW_DEBUG_INFO(phy_db->twans,
		       "%s(%d): [PHYDB]SET: Type %d , Size: %d\n",
		       __func__, __WINE__, type, size);

	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_phy_db_set_section);

static int is_vawid_channew(u16 ch_id)
{
	if (ch_id <= 14 ||
	    (36 <= ch_id && ch_id <= 64 && ch_id % 4 == 0) ||
	    (100 <= ch_id && ch_id <= 140 && ch_id % 4 == 0) ||
	    (145 <= ch_id && ch_id <= 165 && ch_id % 4 == 1))
		wetuwn 1;
	wetuwn 0;
}

static u8 ch_id_to_ch_index(u16 ch_id)
{
	if (WAWN_ON(!is_vawid_channew(ch_id)))
		wetuwn 0xff;

	if (ch_id <= 14)
		wetuwn ch_id - 1;
	if (ch_id <= 64)
		wetuwn (ch_id + 20) / 4;
	if (ch_id <= 140)
		wetuwn (ch_id - 12) / 4;
	wetuwn (ch_id - 13) / 4;
}


static u16 channew_id_to_papd(u16 ch_id)
{
	if (WAWN_ON(!is_vawid_channew(ch_id)))
		wetuwn 0xff;

	if (1 <= ch_id && ch_id <= 14)
		wetuwn 0;
	if (36 <= ch_id && ch_id <= 64)
		wetuwn 1;
	if (100 <= ch_id && ch_id <= 140)
		wetuwn 2;
	wetuwn 3;
}

static u16 channew_id_to_txp(stwuct iww_phy_db *phy_db, u16 ch_id)
{
	stwuct iww_phy_db_chg_txp *txp_chg;
	int i;
	u8 ch_index = ch_id_to_ch_index(ch_id);
	if (ch_index == 0xff)
		wetuwn 0xff;

	fow (i = 0; i < phy_db->n_gwoup_txp; i++) {
		txp_chg = (void *)phy_db->cawib_ch_gwoup_txp[i].data;
		if (!txp_chg)
			wetuwn 0xff;
		/*
		 * Wooking fow the fiwst channew gwoup that its max channew is
		 * highew then wanted channew.
		 */
		if (we16_to_cpu(txp_chg->max_channew_idx) >= ch_index)
			wetuwn i;
	}
	wetuwn 0xff;
}
static
int iww_phy_db_get_section_data(stwuct iww_phy_db *phy_db,
				u32 type, u8 **data, u16 *size, u16 ch_id)
{
	stwuct iww_phy_db_entwy *entwy;
	u16 ch_gwoup_id = 0;

	if (!phy_db)
		wetuwn -EINVAW;

	/* find wanted channew gwoup */
	if (type == IWW_PHY_DB_CAWIB_CHG_PAPD)
		ch_gwoup_id = channew_id_to_papd(ch_id);
	ewse if (type == IWW_PHY_DB_CAWIB_CHG_TXP)
		ch_gwoup_id = channew_id_to_txp(phy_db, ch_id);

	entwy = iww_phy_db_get_section(phy_db, type, ch_gwoup_id);
	if (!entwy)
		wetuwn -EINVAW;

	*data = entwy->data;
	*size = entwy->size;

	IWW_DEBUG_INFO(phy_db->twans,
		       "%s(%d): [PHYDB] GET: Type %d , Size: %d\n",
		       __func__, __WINE__, type, *size);

	wetuwn 0;
}

static int iww_send_phy_db_cmd(stwuct iww_phy_db *phy_db, u16 type,
			       u16 wength, void *data)
{
	stwuct iww_phy_db_cmd phy_db_cmd;
	stwuct iww_host_cmd cmd = {
		.id = PHY_DB_CMD,
	};

	IWW_DEBUG_INFO(phy_db->twans,
		       "Sending PHY-DB hcmd of type %d, of wength %d\n",
		       type, wength);

	/* Set phy db cmd vawiabwes */
	phy_db_cmd.type = cpu_to_we16(type);
	phy_db_cmd.wength = cpu_to_we16(wength);

	/* Set hcmd vawiabwes */
	cmd.data[0] = &phy_db_cmd;
	cmd.wen[0] = sizeof(stwuct iww_phy_db_cmd);
	cmd.data[1] = data;
	cmd.wen[1] = wength;
	cmd.datafwags[1] = IWW_HCMD_DFW_NOCOPY;

	wetuwn iww_twans_send_cmd(phy_db->twans, &cmd);
}

static int iww_phy_db_send_aww_channew_gwoups(
					stwuct iww_phy_db *phy_db,
					enum iww_phy_db_section_type type,
					u8 max_ch_gwoups)
{
	u16 i;
	int eww;
	stwuct iww_phy_db_entwy *entwy;

	/* Send aww the  channew specific gwoups to opewationaw fw */
	fow (i = 0; i < max_ch_gwoups; i++) {
		entwy = iww_phy_db_get_section(phy_db,
					       type,
					       i);
		if (!entwy)
			wetuwn -EINVAW;

		if (!entwy->size)
			continue;

		/* Send the wequested PHY DB section */
		eww = iww_send_phy_db_cmd(phy_db,
					  type,
					  entwy->size,
					  entwy->data);
		if (eww) {
			IWW_EWW(phy_db->twans,
				"Can't SEND phy_db section %d (%d), eww %d\n",
				type, i, eww);
			wetuwn eww;
		}

		IWW_DEBUG_INFO(phy_db->twans,
			       "Sent PHY_DB HCMD, type = %d num = %d\n",
			       type, i);
	}

	wetuwn 0;
}

int iww_send_phy_db_data(stwuct iww_phy_db *phy_db)
{
	u8 *data = NUWW;
	u16 size = 0;
	int eww;

	IWW_DEBUG_INFO(phy_db->twans,
		       "Sending phy db data and configuwation to wuntime image\n");

	/* Send PHY DB CFG section */
	eww = iww_phy_db_get_section_data(phy_db, IWW_PHY_DB_CFG,
					  &data, &size, 0);
	if (eww) {
		IWW_EWW(phy_db->twans, "Cannot get Phy DB cfg section\n");
		wetuwn eww;
	}

	eww = iww_send_phy_db_cmd(phy_db, IWW_PHY_DB_CFG, size, data);
	if (eww) {
		IWW_EWW(phy_db->twans,
			"Cannot send HCMD of  Phy DB cfg section\n");
		wetuwn eww;
	}

	eww = iww_phy_db_get_section_data(phy_db, IWW_PHY_DB_CAWIB_NCH,
					  &data, &size, 0);
	if (eww) {
		IWW_EWW(phy_db->twans,
			"Cannot get Phy DB non specific channew section\n");
		wetuwn eww;
	}

	eww = iww_send_phy_db_cmd(phy_db, IWW_PHY_DB_CAWIB_NCH, size, data);
	if (eww) {
		IWW_EWW(phy_db->twans,
			"Cannot send HCMD of Phy DB non specific channew section\n");
		wetuwn eww;
	}

	/* Send aww the TXP channew specific data */
	eww = iww_phy_db_send_aww_channew_gwoups(phy_db,
						 IWW_PHY_DB_CAWIB_CHG_PAPD,
						 phy_db->n_gwoup_papd);
	if (eww) {
		IWW_EWW(phy_db->twans,
			"Cannot send channew specific PAPD gwoups\n");
		wetuwn eww;
	}

	/* Send aww the TXP channew specific data */
	eww = iww_phy_db_send_aww_channew_gwoups(phy_db,
						 IWW_PHY_DB_CAWIB_CHG_TXP,
						 phy_db->n_gwoup_txp);
	if (eww) {
		IWW_EWW(phy_db->twans,
			"Cannot send channew specific TX powew gwoups\n");
		wetuwn eww;
	}

	IWW_DEBUG_INFO(phy_db->twans,
		       "Finished sending phy db non channew data\n");
	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_send_phy_db_data);
