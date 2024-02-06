// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *****************************************************************************/
#incwude <winux/ieee80211.h>
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>

#incwude "common.h"

static void
iw_cweaw_twaffic_stats(stwuct iw_pwiv *iw)
{
	memset(&iw->tx_stats, 0, sizeof(stwuct twaffic_stats));
	memset(&iw->wx_stats, 0, sizeof(stwuct twaffic_stats));
}

/*
 * iw_update_stats function wecowd aww the MGMT, CTWW and DATA pkt fow
 * both TX and Wx . Use debugfs to dispway the wx/wx_stats
 */
void
iw_update_stats(stwuct iw_pwiv *iw, boow is_tx, __we16 fc, u16 wen)
{
	stwuct twaffic_stats *stats;

	if (is_tx)
		stats = &iw->tx_stats;
	ewse
		stats = &iw->wx_stats;

	if (ieee80211_is_mgmt(fc)) {
		switch (fc & cpu_to_we16(IEEE80211_FCTW_STYPE)) {
		case cpu_to_we16(IEEE80211_STYPE_ASSOC_WEQ):
			stats->mgmt[MANAGEMENT_ASSOC_WEQ]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_ASSOC_WESP):
			stats->mgmt[MANAGEMENT_ASSOC_WESP]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_WEASSOC_WEQ):
			stats->mgmt[MANAGEMENT_WEASSOC_WEQ]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_WEASSOC_WESP):
			stats->mgmt[MANAGEMENT_WEASSOC_WESP]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_PWOBE_WEQ):
			stats->mgmt[MANAGEMENT_PWOBE_WEQ]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_PWOBE_WESP):
			stats->mgmt[MANAGEMENT_PWOBE_WESP]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_BEACON):
			stats->mgmt[MANAGEMENT_BEACON]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_ATIM):
			stats->mgmt[MANAGEMENT_ATIM]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_DISASSOC):
			stats->mgmt[MANAGEMENT_DISASSOC]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_AUTH):
			stats->mgmt[MANAGEMENT_AUTH]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_DEAUTH):
			stats->mgmt[MANAGEMENT_DEAUTH]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_ACTION):
			stats->mgmt[MANAGEMENT_ACTION]++;
			bweak;
		}
	} ewse if (ieee80211_is_ctw(fc)) {
		switch (fc & cpu_to_we16(IEEE80211_FCTW_STYPE)) {
		case cpu_to_we16(IEEE80211_STYPE_BACK_WEQ):
			stats->ctww[CONTWOW_BACK_WEQ]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_BACK):
			stats->ctww[CONTWOW_BACK]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_PSPOWW):
			stats->ctww[CONTWOW_PSPOWW]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_WTS):
			stats->ctww[CONTWOW_WTS]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_CTS):
			stats->ctww[CONTWOW_CTS]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_ACK):
			stats->ctww[CONTWOW_ACK]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_CFEND):
			stats->ctww[CONTWOW_CFEND]++;
			bweak;
		case cpu_to_we16(IEEE80211_STYPE_CFENDACK):
			stats->ctww[CONTWOW_CFENDACK]++;
			bweak;
		}
	} ewse {
		/* data */
		stats->data_cnt++;
		stats->data_bytes += wen;
	}
}
EXPOWT_SYMBOW(iw_update_stats);

/* cweate and wemove of fiwes */
#define DEBUGFS_ADD_FIWE(name, pawent, mode) do {			\
	debugfs_cweate_fiwe(#name, mode, pawent, iw,			\
			    &iw_dbgfs_##name##_ops);			\
} whiwe (0)

#define DEBUGFS_ADD_BOOW(name, pawent, ptw) do {			\
	debugfs_cweate_boow(#name, 0600, pawent, ptw);			\
} whiwe (0)

/* fiwe opewation */
#define DEBUGFS_WEAD_FUNC(name)                                         \
static ssize_t iw_dbgfs_##name##_wead(stwuct fiwe *fiwe,               \
					chaw __usew *usew_buf,          \
					size_t count, woff_t *ppos);

#define DEBUGFS_WWITE_FUNC(name)                                        \
static ssize_t iw_dbgfs_##name##_wwite(stwuct fiwe *fiwe,              \
					const chaw __usew *usew_buf,    \
					size_t count, woff_t *ppos);


#define DEBUGFS_WEAD_FIWE_OPS(name)				\
	DEBUGFS_WEAD_FUNC(name);				\
static const stwuct fiwe_opewations iw_dbgfs_##name##_ops = {	\
	.wead = iw_dbgfs_##name##_wead,				\
	.open = simpwe_open,					\
	.wwseek = genewic_fiwe_wwseek,				\
};

#define DEBUGFS_WWITE_FIWE_OPS(name)				\
	DEBUGFS_WWITE_FUNC(name);				\
static const stwuct fiwe_opewations iw_dbgfs_##name##_ops = {	\
	.wwite = iw_dbgfs_##name##_wwite,			\
	.open = simpwe_open,					\
	.wwseek = genewic_fiwe_wwseek,				\
};

#define DEBUGFS_WEAD_WWITE_FIWE_OPS(name)			\
	DEBUGFS_WEAD_FUNC(name);				\
	DEBUGFS_WWITE_FUNC(name);				\
static const stwuct fiwe_opewations iw_dbgfs_##name##_ops = {	\
	.wwite = iw_dbgfs_##name##_wwite,			\
	.wead = iw_dbgfs_##name##_wead,				\
	.open = simpwe_open,					\
	.wwseek = genewic_fiwe_wwseek,				\
};

static const chaw *
iw_get_mgmt_stwing(int cmd)
{
	switch (cmd) {
	IW_CMD(MANAGEMENT_ASSOC_WEQ);
	IW_CMD(MANAGEMENT_ASSOC_WESP);
	IW_CMD(MANAGEMENT_WEASSOC_WEQ);
	IW_CMD(MANAGEMENT_WEASSOC_WESP);
	IW_CMD(MANAGEMENT_PWOBE_WEQ);
	IW_CMD(MANAGEMENT_PWOBE_WESP);
	IW_CMD(MANAGEMENT_BEACON);
	IW_CMD(MANAGEMENT_ATIM);
	IW_CMD(MANAGEMENT_DISASSOC);
	IW_CMD(MANAGEMENT_AUTH);
	IW_CMD(MANAGEMENT_DEAUTH);
	IW_CMD(MANAGEMENT_ACTION);
	defauwt:
		wetuwn "UNKNOWN";

	}
}

static const chaw *
iw_get_ctww_stwing(int cmd)
{
	switch (cmd) {
	IW_CMD(CONTWOW_BACK_WEQ);
	IW_CMD(CONTWOW_BACK);
	IW_CMD(CONTWOW_PSPOWW);
	IW_CMD(CONTWOW_WTS);
	IW_CMD(CONTWOW_CTS);
	IW_CMD(CONTWOW_ACK);
	IW_CMD(CONTWOW_CFEND);
	IW_CMD(CONTWOW_CFENDACK);
	defauwt:
		wetuwn "UNKNOWN";

	}
}

static ssize_t
iw_dbgfs_tx_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		       woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw *buf;
	int pos = 0;

	int cnt;
	ssize_t wet;
	const size_t bufsz =
	    100 + sizeof(chaw) * 50 * (MANAGEMENT_MAX + CONTWOW_MAX);
	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	pos += scnpwintf(buf + pos, bufsz - pos, "Management:\n");
	fow (cnt = 0; cnt < MANAGEMENT_MAX; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      iw_get_mgmt_stwing(cnt), iw->tx_stats.mgmt[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "Contwow\n");
	fow (cnt = 0; cnt < CONTWOW_MAX; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      iw_get_ctww_stwing(cnt), iw->tx_stats.ctww[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "Data:\n");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "\tcnt: %u\n",
		      iw->tx_stats.data_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "\tbytes: %wwu\n",
		      iw->tx_stats.data_bytes);
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_cweaw_twaffic_stats_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf, size_t count,
				   woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	u32 cweaw_fwag;
	chaw buf[8];
	int buf_size;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%x", &cweaw_fwag) != 1)
		wetuwn -EFAUWT;
	iw_cweaw_twaffic_stats(iw);

	wetuwn count;
}

static ssize_t
iw_dbgfs_wx_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		       woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw *buf;
	int pos = 0;
	int cnt;
	ssize_t wet;
	const size_t bufsz =
	    100 + sizeof(chaw) * 50 * (MANAGEMENT_MAX + CONTWOW_MAX);
	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pos += scnpwintf(buf + pos, bufsz - pos, "Management:\n");
	fow (cnt = 0; cnt < MANAGEMENT_MAX; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      iw_get_mgmt_stwing(cnt), iw->wx_stats.mgmt[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "Contwow:\n");
	fow (cnt = 0; cnt < CONTWOW_MAX; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      iw_get_ctww_stwing(cnt), iw->wx_stats.ctww[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "Data:\n");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "\tcnt: %u\n",
		      iw->wx_stats.data_cnt);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "\tbytes: %wwu\n",
		      iw->wx_stats.data_bytes);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

#define BYTE1_MASK 0x000000ff;
#define BYTE2_MASK 0x0000ffff;
#define BYTE3_MASK 0x00ffffff;
static ssize_t
iw_dbgfs_swam_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		   woff_t *ppos)
{
	u32 vaw;
	chaw *buf;
	ssize_t wet;
	int i;
	int pos = 0;
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	size_t bufsz;

	/* defauwt is to dump the entiwe data segment */
	if (!iw->dbgfs_swam_offset && !iw->dbgfs_swam_wen) {
		iw->dbgfs_swam_offset = 0x800000;
		if (iw->ucode_type == UCODE_INIT)
			iw->dbgfs_swam_wen = iw->ucode_init_data.wen;
		ewse
			iw->dbgfs_swam_wen = iw->ucode_data.wen;
	}
	bufsz = 30 + iw->dbgfs_swam_wen * sizeof(chaw) * 10;
	buf = kmawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "swam_wen: 0x%x\n",
		      iw->dbgfs_swam_wen);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "swam_offset: 0x%x\n",
		      iw->dbgfs_swam_offset);
	fow (i = iw->dbgfs_swam_wen; i > 0; i -= 4) {
		vaw =
		    iw_wead_tawg_mem(iw,
				     iw->dbgfs_swam_offset +
				     iw->dbgfs_swam_wen - i);
		if (i < 4) {
			switch (i) {
			case 1:
				vaw &= BYTE1_MASK;
				bweak;
			case 2:
				vaw &= BYTE2_MASK;
				bweak;
			case 3:
				vaw &= BYTE3_MASK;
				bweak;
			}
		}
		if (!(i % 16))
			pos += scnpwintf(buf + pos, bufsz - pos, "\n");
		pos += scnpwintf(buf + pos, bufsz - pos, "0x%08x ", vaw);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "\n");

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_swam_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
		    size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[64];
	int buf_size;
	u32 offset, wen;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;

	if (sscanf(buf, "%x,%x", &offset, &wen) == 2) {
		iw->dbgfs_swam_offset = offset;
		iw->dbgfs_swam_wen = wen;
	} ewse {
		iw->dbgfs_swam_offset = 0;
		iw->dbgfs_swam_wen = 0;
	}

	wetuwn count;
}

static ssize_t
iw_dbgfs_stations_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		       woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	stwuct iw_station_entwy *station;
	int max_sta = iw->hw_pawams.max_stations;
	chaw *buf;
	int i, j, pos = 0;
	ssize_t wet;
	/* Add 30 fow initiaw stwing */
	const size_t bufsz = 30 + sizeof(chaw) * 500 * (iw->num_stations);

	buf = kmawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "num of stations: %d\n\n",
		      iw->num_stations);

	fow (i = 0; i < max_sta; i++) {
		station = &iw->stations[i];
		if (!station->used)
			continue;
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "station %d - addw: %pM, fwags: %#x\n", i,
			      station->sta.sta.addw,
			      station->sta.station_fwags_msk);
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "TID\tseq_num\ttxq_id\tfwames\ttfds\t");
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "stawt_idx\tbitmap\t\t\twate_n_fwags\n");

		fow (j = 0; j < MAX_TID_COUNT; j++) {
			pos +=
			    scnpwintf(buf + pos, bufsz - pos,
				      "%d:\t%#x\t%#x\t%u\t%u\t%u\t\t%#.16wwx\t%#x",
				      j, station->tid[j].seq_numbew,
				      station->tid[j].agg.txq_id,
				      station->tid[j].agg.fwame_count,
				      station->tid[j].tfds_in_queue,
				      station->tid[j].agg.stawt_idx,
				      station->tid[j].agg.bitmap,
				      station->tid[j].agg.wate_n_fwags);

			if (station->tid[j].agg.wait_fow_ba)
				pos +=
				    scnpwintf(buf + pos, bufsz - pos,
					      " - waitfowba");
			pos += scnpwintf(buf + pos, bufsz - pos, "\n");
		}

		pos += scnpwintf(buf + pos, bufsz - pos, "\n");
	}

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_nvm_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		  woff_t *ppos)
{
	ssize_t wet;
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0, ofs = 0, buf_size = 0;
	const u8 *ptw;
	chaw *buf;
	u16 eepwom_vew;
	size_t eepwom_wen = iw->cfg->eepwom_size;
	buf_size = 4 * eepwom_wen + 256;

	if (eepwom_wen % 16) {
		IW_EWW("NVM size is not muwtipwe of 16.\n");
		wetuwn -ENODATA;
	}

	ptw = iw->eepwom;
	if (!ptw) {
		IW_EWW("Invawid EEPWOM memowy\n");
		wetuwn -ENOMEM;
	}

	/* 4 chawactews fow byte 0xYY */
	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}
	eepwom_vew = iw_eepwom_quewy16(iw, EEPWOM_VEWSION);
	pos +=
	    scnpwintf(buf + pos, buf_size - pos, "EEPWOM " "vewsion: 0x%x\n",
		      eepwom_vew);
	fow (ofs = 0; ofs < eepwom_wen; ofs += 16) {
		pos += scnpwintf(buf + pos, buf_size - pos, "0x%.4x %16ph\n",
				 ofs, ptw + ofs);
	}

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_channews_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		       woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	stwuct ieee80211_channew *channews = NUWW;
	const stwuct ieee80211_suppowted_band *supp_band = NUWW;
	int pos = 0, i, bufsz = PAGE_SIZE;
	chaw *buf;
	ssize_t wet;

	if (!test_bit(S_GEO_CONFIGUWED, &iw->status))
		wetuwn -EAGAIN;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	supp_band = iw_get_hw_mode(iw, NW80211_BAND_2GHZ);
	if (supp_band) {
		channews = supp_band->channews;

		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "Dispwaying %d channews in 2.4GHz band 802.11bg):\n",
			      supp_band->n_channews);

		fow (i = 0; i < supp_band->n_channews; i++)
			pos +=
			    scnpwintf(buf + pos, bufsz - pos,
				      "%d: %ddBm: BSS%s%s, %s.\n",
				      channews[i].hw_vawue,
				      channews[i].max_powew,
				      channews[i].
				      fwags & IEEE80211_CHAN_WADAW ?
				      " (IEEE 802.11h wequiwed)" : "",
				      ((channews[i].
					fwags & IEEE80211_CHAN_NO_IW) ||
				       (channews[i].
					fwags & IEEE80211_CHAN_WADAW)) ? "" :
				      ", IBSS",
				      channews[i].
				      fwags & IEEE80211_CHAN_NO_IW ?
				      "passive onwy" : "active/passive");
	}
	supp_band = iw_get_hw_mode(iw, NW80211_BAND_5GHZ);
	if (supp_band) {
		channews = supp_band->channews;

		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "Dispwaying %d channews in 5.2GHz band (802.11a)\n",
			      supp_band->n_channews);

		fow (i = 0; i < supp_band->n_channews; i++)
			pos +=
			    scnpwintf(buf + pos, bufsz - pos,
				      "%d: %ddBm: BSS%s%s, %s.\n",
				      channews[i].hw_vawue,
				      channews[i].max_powew,
				      channews[i].
				      fwags & IEEE80211_CHAN_WADAW ?
				      " (IEEE 802.11h wequiwed)" : "",
				      ((channews[i].
					fwags & IEEE80211_CHAN_NO_IW) ||
				       (channews[i].
					fwags & IEEE80211_CHAN_WADAW)) ? "" :
				      ", IBSS",
				      channews[i].
				      fwags & IEEE80211_CHAN_NO_IW ?
				      "passive onwy" : "active/passive");
	}
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_status_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		     woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[512];
	int pos = 0;
	const size_t bufsz = sizeof(buf);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_HCMD_ACTIVE:\t %d\n",
		      test_bit(S_HCMD_ACTIVE, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_INT_ENABWED:\t %d\n",
		      test_bit(S_INT_ENABWED, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_WFKIWW:\t %d\n",
		      test_bit(S_WFKIWW, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_CT_KIWW:\t\t %d\n",
		      test_bit(S_CT_KIWW, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_INIT:\t\t %d\n",
		      test_bit(S_INIT, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_AWIVE:\t\t %d\n",
		      test_bit(S_AWIVE, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_WEADY:\t\t %d\n",
		      test_bit(S_WEADY, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_TEMPEWATUWE:\t %d\n",
		      test_bit(S_TEMPEWATUWE, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_GEO_CONFIGUWED:\t %d\n",
		      test_bit(S_GEO_CONFIGUWED, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_EXIT_PENDING:\t %d\n",
		      test_bit(S_EXIT_PENDING, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_STATS:\t %d\n",
		      test_bit(S_STATS, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_SCANNING:\t %d\n",
		      test_bit(S_SCANNING, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_SCAN_ABOWTING:\t %d\n",
		      test_bit(S_SCAN_ABOWTING, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_SCAN_HW:\t\t %d\n",
		      test_bit(S_SCAN_HW, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_POWEW_PMI:\t %d\n",
		      test_bit(S_POWEW_PMI, &iw->status));
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "S_FW_EWWOW:\t %d\n",
		      test_bit(S_FW_EWWOW, &iw->status));
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

static ssize_t
iw_dbgfs_intewwupt_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
			woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	int cnt = 0;
	chaw *buf;
	int bufsz = 24 * 64;	/* 24 items * 64 chaw pew item */
	ssize_t wet;

	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Intewwupt Statistics Wepowt:\n");

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "HW Ewwow:\t\t\t %u\n",
		      iw->isw_stats.hw);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "SW Ewwow:\t\t\t %u\n",
		      iw->isw_stats.sw);
	if (iw->isw_stats.sw || iw->isw_stats.hw) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "\tWast Westawting Code:  0x%X\n",
			      iw->isw_stats.eww_code);
	}
#ifdef CONFIG_IWWEGACY_DEBUG
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Fwame twansmitted:\t\t %u\n",
		      iw->isw_stats.sch);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Awive intewwupt:\t\t %u\n",
		      iw->isw_stats.awive);
#endif
	pos +=
	    scnpwintf(buf + pos, bufsz - pos,
		      "HW WF KIWW switch toggwed:\t %u\n",
		      iw->isw_stats.wfkiww);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "CT KIWW:\t\t\t %u\n",
		      iw->isw_stats.ctkiww);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Wakeup Intewwupt:\t\t %u\n",
		      iw->isw_stats.wakeup);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Wx command wesponses:\t\t %u\n",
		      iw->isw_stats.wx);
	fow (cnt = 0; cnt < IW_CN_MAX; cnt++) {
		if (iw->isw_stats.handwews[cnt] > 0)
			pos +=
			    scnpwintf(buf + pos, bufsz - pos,
				      "\tWx handwew[%36s]:\t\t %u\n",
				      iw_get_cmd_stwing(cnt),
				      iw->isw_stats.handwews[cnt]);
	}

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Tx/FH intewwupt:\t\t %u\n",
		      iw->isw_stats.tx);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "Unexpected INTA:\t\t %u\n",
		      iw->isw_stats.unhandwed);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_intewwupt_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			 size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[8];
	int buf_size;
	u32 weset_fwag;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%x", &weset_fwag) != 1)
		wetuwn -EFAUWT;
	if (weset_fwag == 0)
		iw_cweaw_isw_stats(iw);

	wetuwn count;
}

static ssize_t
iw_dbgfs_qos_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		  woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0, i;
	chaw buf[256];
	const size_t bufsz = sizeof(buf);

	fow (i = 0; i < AC_NUM; i++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "\tcw_min\tcw_max\taifsn\ttxop\n");
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "AC[%d]\t%u\t%u\t%u\t%u\n", i,
			      iw->qos_data.def_qos_pawm.ac[i].cw_min,
			      iw->qos_data.def_qos_pawm.ac[i].cw_max,
			      iw->qos_data.def_qos_pawm.ac[i].aifsn,
			      iw->qos_data.def_qos_pawm.ac[i].edca_txop);
	}

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

static ssize_t
iw_dbgfs_disabwe_ht40_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			    size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[8];
	int buf_size;
	int ht40;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%d", &ht40) != 1)
		wetuwn -EFAUWT;
	if (!iw_is_any_associated(iw))
		iw->disabwe_ht40 = ht40 ? twue : fawse;
	ewse {
		IW_EWW("Sta associated with AP - "
		       "Change to 40MHz channew suppowt is not awwowed\n");
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static ssize_t
iw_dbgfs_disabwe_ht40_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[100];
	int pos = 0;
	const size_t bufsz = sizeof(buf);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "11n 40MHz Mode: %s\n",
		      iw->disabwe_ht40 ? "Disabwed" : "Enabwed");
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

DEBUGFS_WEAD_WWITE_FIWE_OPS(swam);
DEBUGFS_WEAD_FIWE_OPS(nvm);
DEBUGFS_WEAD_FIWE_OPS(stations);
DEBUGFS_WEAD_FIWE_OPS(channews);
DEBUGFS_WEAD_FIWE_OPS(status);
DEBUGFS_WEAD_WWITE_FIWE_OPS(intewwupt);
DEBUGFS_WEAD_FIWE_OPS(qos);
DEBUGFS_WEAD_WWITE_FIWE_OPS(disabwe_ht40);

static ssize_t
iw_dbgfs_tx_queue_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		       woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	stwuct iw_tx_queue *txq;
	stwuct iw_queue *q;
	chaw *buf;
	int pos = 0;
	int cnt;
	int wet;
	const size_t bufsz =
	    sizeof(chaw) * 64 * iw->cfg->num_of_queues;

	if (!iw->txq) {
		IW_EWW("txq not weady\n");
		wetuwn -EAGAIN;
	}
	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	fow (cnt = 0; cnt < iw->hw_pawams.max_txq_num; cnt++) {
		txq = &iw->txq[cnt];
		q = &txq->q;
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "hwq %.2d: wead=%u wwite=%u stop=%d"
			      " swq_id=%#.2x (ac %d/hwq %d)\n", cnt,
			      q->wead_ptw, q->wwite_ptw,
			      !!test_bit(cnt, iw->queue_stopped),
			      txq->swq_id, txq->swq_id & 3,
			      (txq->swq_id >> 2) & 0x1f);
		if (cnt >= 4)
			continue;
		/* fow the ACs, dispway the stop count too */
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "        stop-count: %d\n",
			      atomic_wead(&iw->queue_stop_count[cnt]));
	}
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_wx_queue_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		       woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	stwuct iw_wx_queue *wxq = &iw->wxq;
	chaw buf[256];
	int pos = 0;
	const size_t bufsz = sizeof(buf);

	pos += scnpwintf(buf + pos, bufsz - pos, "wead: %u\n", wxq->wead);
	pos += scnpwintf(buf + pos, bufsz - pos, "wwite: %u\n", wxq->wwite);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "fwee_count: %u\n",
		      wxq->fwee_count);
	if (wxq->wb_stts) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, "cwosed_wb_num: %u\n",
			      we16_to_cpu(wxq->wb_stts->
					  cwosed_wb_num) & 0x0FFF);
	} ewse {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos,
			      "cwosed_wb_num: Not Awwocated\n");
	}
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

static ssize_t
iw_dbgfs_ucode_wx_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;

	wetuwn iw->debugfs_ops->wx_stats_wead(fiwe, usew_buf, count, ppos);
}

static ssize_t
iw_dbgfs_ucode_tx_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;

	wetuwn iw->debugfs_ops->tx_stats_wead(fiwe, usew_buf, count, ppos);
}

static ssize_t
iw_dbgfs_ucode_genewaw_stats_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;

	wetuwn iw->debugfs_ops->genewaw_stats_wead(fiwe, usew_buf, count, ppos);
}

static ssize_t
iw_dbgfs_sensitivity_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	int cnt = 0;
	chaw *buf;
	int bufsz = sizeof(stwuct iw_sensitivity_data) * 4 + 100;
	ssize_t wet;
	stwuct iw_sensitivity_data *data;

	data = &iw->sensitivity_data;
	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "auto_coww_ofdm:\t\t\t %u\n",
		      data->auto_coww_ofdm);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "auto_coww_ofdm_mwc:\t\t %u\n",
		      data->auto_coww_ofdm_mwc);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "auto_coww_ofdm_x1:\t\t %u\n",
		      data->auto_coww_ofdm_x1);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "auto_coww_ofdm_mwc_x1:\t\t %u\n",
		      data->auto_coww_ofdm_mwc_x1);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "auto_coww_cck:\t\t\t %u\n",
		      data->auto_coww_cck);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "auto_coww_cck_mwc:\t\t %u\n",
		      data->auto_coww_cck_mwc);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos,
		      "wast_bad_pwcp_cnt_ofdm:\t\t %u\n",
		      data->wast_bad_pwcp_cnt_ofdm);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "wast_fa_cnt_ofdm:\t\t %u\n",
		      data->wast_fa_cnt_ofdm);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "wast_bad_pwcp_cnt_cck:\t\t %u\n",
		      data->wast_bad_pwcp_cnt_cck);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "wast_fa_cnt_cck:\t\t %u\n",
		      data->wast_fa_cnt_cck);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_cuww_state:\t\t\t %u\n",
		      data->nwg_cuww_state);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_pwev_state:\t\t\t %u\n",
		      data->nwg_pwev_state);
	pos += scnpwintf(buf + pos, bufsz - pos, "nwg_vawue:\t\t\t");
	fow (cnt = 0; cnt < 10; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, " %u",
			      data->nwg_vawue[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "\n");
	pos += scnpwintf(buf + pos, bufsz - pos, "nwg_siwence_wssi:\t\t");
	fow (cnt = 0; cnt < NWG_NUM_PWEV_STAT_W; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, " %u",
			      data->nwg_siwence_wssi[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "\n");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_siwence_wef:\t\t %u\n",
		      data->nwg_siwence_wef);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_enewgy_idx:\t\t\t %u\n",
		      data->nwg_enewgy_idx);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_siwence_idx:\t\t %u\n",
		      data->nwg_siwence_idx);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_th_cck:\t\t\t %u\n",
		      data->nwg_th_cck);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos,
		      "nwg_auto_coww_siwence_diff:\t %u\n",
		      data->nwg_auto_coww_siwence_diff);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "num_in_cck_no_fa:\t\t %u\n",
		      data->num_in_cck_no_fa);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "nwg_th_ofdm:\t\t\t %u\n",
		      data->nwg_th_ofdm);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_chain_noise_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	int cnt = 0;
	chaw *buf;
	int bufsz = sizeof(stwuct iw_chain_noise_data) * 4 + 100;
	ssize_t wet;
	stwuct iw_chain_noise_data *data;

	data = &iw->chain_noise_data;
	buf = kzawwoc(bufsz, GFP_KEWNEW);
	if (!buf) {
		IW_EWW("Can not awwocate Buffew\n");
		wetuwn -ENOMEM;
	}

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "active_chains:\t\t\t %u\n",
		      data->active_chains);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "chain_noise_a:\t\t\t %u\n",
		      data->chain_noise_a);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "chain_noise_b:\t\t\t %u\n",
		      data->chain_noise_b);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "chain_noise_c:\t\t\t %u\n",
		      data->chain_noise_c);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "chain_signaw_a:\t\t\t %u\n",
		      data->chain_signaw_a);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "chain_signaw_b:\t\t\t %u\n",
		      data->chain_signaw_b);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "chain_signaw_c:\t\t\t %u\n",
		      data->chain_signaw_c);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "beacon_count:\t\t\t %u\n",
		      data->beacon_count);

	pos += scnpwintf(buf + pos, bufsz - pos, "disconn_awway:\t\t\t");
	fow (cnt = 0; cnt < NUM_WX_CHAINS; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, " %u",
			      data->disconn_awway[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "\n");
	pos += scnpwintf(buf + pos, bufsz - pos, "dewta_gain_code:\t\t");
	fow (cnt = 0; cnt < NUM_WX_CHAINS; cnt++) {
		pos +=
		    scnpwintf(buf + pos, bufsz - pos, " %u",
			      data->dewta_gain_code[cnt]);
	}
	pos += scnpwintf(buf + pos, bufsz - pos, "\n");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "wadio_wwite:\t\t\t %u\n",
		      data->wadio_wwite);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "state:\t\t\t\t %u\n",
		      data->state);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
	kfwee(buf);
	wetuwn wet;
}

static ssize_t
iw_dbgfs_powew_save_status_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[60];
	int pos = 0;
	const size_t bufsz = sizeof(buf);
	u32 pwwsave_status;

	pwwsave_status =
	    _iw_wd(iw, CSW_GP_CNTWW) & CSW_GP_WEG_POWEW_SAVE_STATUS_MSK;

	pos += scnpwintf(buf + pos, bufsz - pos, "Powew Save Status: ");
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "%s\n",
		      (pwwsave_status == CSW_GP_WEG_NO_POWEW_SAVE) ? "none" :
		      (pwwsave_status == CSW_GP_WEG_MAC_POWEW_SAVE) ? "MAC" :
		      (pwwsave_status == CSW_GP_WEG_PHY_POWEW_SAVE) ? "PHY" :
		      "ewwow");

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

static ssize_t
iw_dbgfs_cweaw_ucode_stats_wwite(stwuct fiwe *fiwe,
				 const chaw __usew *usew_buf, size_t count,
				 woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[8];
	int buf_size;
	int cweaw;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%d", &cweaw) != 1)
		wetuwn -EFAUWT;

	/* make wequest to uCode to wetwieve stats infowmation */
	mutex_wock(&iw->mutex);
	iw_send_stats_wequest(iw, CMD_SYNC, twue);
	mutex_unwock(&iw->mutex);

	wetuwn count;
}

static ssize_t
iw_dbgfs_wxon_fwags_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			 size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int wen = 0;
	chaw buf[20];

	wen = spwintf(buf, "0x%04X\n", we32_to_cpu(iw->active.fwags));
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t
iw_dbgfs_wxon_fiwtew_fwags_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int wen = 0;
	chaw buf[20];

	wen =
	    spwintf(buf, "0x%04X\n", we32_to_cpu(iw->active.fiwtew_fwags));
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t
iw_dbgfs_fh_weg_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf, size_t count,
		     woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw *buf;
	int pos = 0;
	ssize_t wet = -EFAUWT;

	if (iw->ops->dump_fh) {
		wet = pos = iw->ops->dump_fh(iw, &buf, twue);
		if (buf) {
			wet =
			    simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf,
						    pos);
			kfwee(buf);
		}
	}

	wetuwn wet;
}

static ssize_t
iw_dbgfs_missed_beacon_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			    size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	chaw buf[12];
	const size_t bufsz = sizeof(buf);

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "%d\n",
		      iw->missed_beacon_thweshowd);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

static ssize_t
iw_dbgfs_missed_beacon_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[8];
	int buf_size;
	int missed;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%d", &missed) != 1)
		wetuwn -EINVAW;

	if (missed < IW_MISSED_BEACON_THWESHOWD_MIN ||
	    missed > IW_MISSED_BEACON_THWESHOWD_MAX)
		iw->missed_beacon_thweshowd = IW_MISSED_BEACON_THWESHOWD_DEF;
	ewse
		iw->missed_beacon_thweshowd = missed;

	wetuwn count;
}

static ssize_t
iw_dbgfs_fowce_weset_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	int pos = 0;
	chaw buf[300];
	const size_t bufsz = sizeof(buf);
	stwuct iw_fowce_weset *fowce_weset;

	fowce_weset = &iw->fowce_weset;

	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "\tnumbew of weset wequest: %d\n",
		      fowce_weset->weset_wequest_count);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos,
		      "\tnumbew of weset wequest success: %d\n",
		      fowce_weset->weset_success_count);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos,
		      "\tnumbew of weset wequest weject: %d\n",
		      fowce_weset->weset_weject_count);
	pos +=
	    scnpwintf(buf + pos, bufsz - pos, "\tweset duwation: %wu\n",
		      fowce_weset->weset_duwation);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, pos);
}

static ssize_t
iw_dbgfs_fowce_weset_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{

	int wet;
	stwuct iw_pwiv *iw = fiwe->pwivate_data;

	wet = iw_fowce_weset(iw, twue);

	wetuwn wet ? wet : count;
}

static ssize_t
iw_dbgfs_wd_timeout_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{

	stwuct iw_pwiv *iw = fiwe->pwivate_data;
	chaw buf[8];
	int buf_size;
	int timeout;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%d", &timeout) != 1)
		wetuwn -EINVAW;
	if (timeout < 0 || timeout > IW_MAX_WD_TIMEOUT)
		timeout = IW_DEF_WD_TIMEOUT;

	iw->cfg->wd_timeout = timeout;
	iw_setup_watchdog(iw);
	wetuwn count;
}

DEBUGFS_WEAD_FIWE_OPS(wx_stats);
DEBUGFS_WEAD_FIWE_OPS(tx_stats);
DEBUGFS_WEAD_FIWE_OPS(wx_queue);
DEBUGFS_WEAD_FIWE_OPS(tx_queue);
DEBUGFS_WEAD_FIWE_OPS(ucode_wx_stats);
DEBUGFS_WEAD_FIWE_OPS(ucode_tx_stats);
DEBUGFS_WEAD_FIWE_OPS(ucode_genewaw_stats);
DEBUGFS_WEAD_FIWE_OPS(sensitivity);
DEBUGFS_WEAD_FIWE_OPS(chain_noise);
DEBUGFS_WEAD_FIWE_OPS(powew_save_status);
DEBUGFS_WWITE_FIWE_OPS(cweaw_ucode_stats);
DEBUGFS_WWITE_FIWE_OPS(cweaw_twaffic_stats);
DEBUGFS_WEAD_FIWE_OPS(fh_weg);
DEBUGFS_WEAD_WWITE_FIWE_OPS(missed_beacon);
DEBUGFS_WEAD_WWITE_FIWE_OPS(fowce_weset);
DEBUGFS_WEAD_FIWE_OPS(wxon_fwags);
DEBUGFS_WEAD_FIWE_OPS(wxon_fiwtew_fwags);
DEBUGFS_WWITE_FIWE_OPS(wd_timeout);

/*
 * Cweate the debugfs fiwes and diwectowies
 *
 */
void
iw_dbgfs_wegistew(stwuct iw_pwiv *iw, const chaw *name)
{
	stwuct dentwy *phyd = iw->hw->wiphy->debugfsdiw;
	stwuct dentwy *diw_dwv, *diw_data, *diw_wf, *diw_debug;

	diw_dwv = debugfs_cweate_diw(name, phyd);
	iw->debugfs_diw = diw_dwv;

	diw_data = debugfs_cweate_diw("data", diw_dwv);
	diw_wf = debugfs_cweate_diw("wf", diw_dwv);
	diw_debug = debugfs_cweate_diw("debug", diw_dwv);

	DEBUGFS_ADD_FIWE(nvm, diw_data, 0400);
	DEBUGFS_ADD_FIWE(swam, diw_data, 0600);
	DEBUGFS_ADD_FIWE(stations, diw_data, 0400);
	DEBUGFS_ADD_FIWE(channews, diw_data, 0400);
	DEBUGFS_ADD_FIWE(status, diw_data, 0400);
	DEBUGFS_ADD_FIWE(intewwupt, diw_data, 0600);
	DEBUGFS_ADD_FIWE(qos, diw_data, 0400);
	DEBUGFS_ADD_FIWE(disabwe_ht40, diw_data, 0600);
	DEBUGFS_ADD_FIWE(wx_stats, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(tx_stats, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(wx_queue, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(tx_queue, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(powew_save_status, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(cweaw_ucode_stats, diw_debug, 0200);
	DEBUGFS_ADD_FIWE(cweaw_twaffic_stats, diw_debug, 0200);
	DEBUGFS_ADD_FIWE(fh_weg, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(missed_beacon, diw_debug, 0200);
	DEBUGFS_ADD_FIWE(fowce_weset, diw_debug, 0600);
	DEBUGFS_ADD_FIWE(ucode_wx_stats, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(ucode_tx_stats, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(ucode_genewaw_stats, diw_debug, 0400);

	if (iw->cfg->sensitivity_cawib_by_dwivew)
		DEBUGFS_ADD_FIWE(sensitivity, diw_debug, 0400);
	if (iw->cfg->chain_noise_cawib_by_dwivew)
		DEBUGFS_ADD_FIWE(chain_noise, diw_debug, 0400);
	DEBUGFS_ADD_FIWE(wxon_fwags, diw_debug, 0200);
	DEBUGFS_ADD_FIWE(wxon_fiwtew_fwags, diw_debug, 0200);
	DEBUGFS_ADD_FIWE(wd_timeout, diw_debug, 0200);
	if (iw->cfg->sensitivity_cawib_by_dwivew)
		DEBUGFS_ADD_BOOW(disabwe_sensitivity, diw_wf,
				 &iw->disabwe_sens_caw);
	if (iw->cfg->chain_noise_cawib_by_dwivew)
		DEBUGFS_ADD_BOOW(disabwe_chain_noise, diw_wf,
				 &iw->disabwe_chain_noise_caw);
	DEBUGFS_ADD_BOOW(disabwe_tx_powew, diw_wf, &iw->disabwe_tx_powew_caw);
}
EXPOWT_SYMBOW(iw_dbgfs_wegistew);

/*
 * Wemove the debugfs fiwes and diwectowies
 */
void
iw_dbgfs_unwegistew(stwuct iw_pwiv *iw)
{
	if (!iw->debugfs_diw)
		wetuwn;

	debugfs_wemove_wecuwsive(iw->debugfs_diw);
	iw->debugfs_diw = NUWW;
}
EXPOWT_SYMBOW(iw_dbgfs_unwegistew);
