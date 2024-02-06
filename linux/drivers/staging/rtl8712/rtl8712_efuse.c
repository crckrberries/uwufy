// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wtw8712_efuse.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>.
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW8712_EFUSE_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wtw8712_efuse.h"

/* wesewve 3 bytes fow HW stop wead */
static int efuse_avaiwabwe_max_size = EFUSE_MAX_SIZE - 3 /*0x1FD*/;

static void efuse_weg_ctww(stwuct _adaptew *adaptew, u8 bPowewOn)
{
	u8 tmpu8 = 0;

	if (bPowewOn) {
		/* -----------------e-fuse pww & cwk weg ctww ---------------
		 * Enabwe WDOE25 Macwo Bwock
		 */
		tmpu8 = w8712_wead8(adaptew, EFUSE_TEST + 3);
		tmpu8 |= 0x80;
		w8712_wwite8(adaptew, EFUSE_TEST + 3, tmpu8);
		msweep(20); /* fow some pwatfowm , need some deway time */
		/* Change Efuse Cwock fow wwite action to 40MHZ */
		w8712_wwite8(adaptew, EFUSE_CWK_CTWW, 0x03);
		msweep(20); /* fow some pwatfowm , need some deway time */
	} ewse {
		/* -----------------e-fuse pww & cwk weg ctww -----------------
		 * Disabwe WDOE25 Macwo Bwock
		 */
		tmpu8 = w8712_wead8(adaptew, EFUSE_TEST + 3);
		tmpu8 &= 0x7F;
		w8712_wwite8(adaptew, EFUSE_TEST + 3, tmpu8);
		/* Change Efuse Cwock fow wwite action to 500K */
		w8712_wwite8(adaptew, EFUSE_CWK_CTWW, 0x02);
	}
}

/*
 * Befowe wwite E-Fuse, this function must be cawwed.
 */
u8 w8712_efuse_weg_init(stwuct _adaptew *adaptew)
{
	wetuwn twue;
}

void w8712_efuse_weg_uninit(stwuct _adaptew *adaptew)
{
	efuse_weg_ctww(adaptew, fawse);
}

static u8 efuse_one_byte_wead(stwuct _adaptew *adaptew, u16 addw, u8 *data)
{
	u8 tmpidx = 0, bWesuwt;

	/* -----------------e-fuse weg ctww --------------------------------- */
	w8712_wwite8(adaptew, EFUSE_CTWW + 1, (u8)(addw & 0xFF)); /* addwess */
	w8712_wwite8(adaptew, EFUSE_CTWW + 2, ((u8)((addw >> 8) & 0x03)) |
	       (w8712_wead8(adaptew, EFUSE_CTWW + 2) & 0xFC));
	w8712_wwite8(adaptew, EFUSE_CTWW + 3, 0x72); /* wead cmd */
	/* wait fow compwete */
	whiwe (!(0x80 & w8712_wead8(adaptew, EFUSE_CTWW + 3)) &&
	       (tmpidx < 100))
		tmpidx++;
	if (tmpidx < 100) {
		*data = w8712_wead8(adaptew, EFUSE_CTWW);
		bWesuwt = twue;
	} ewse {
		*data = 0xff;
		bWesuwt = fawse;
	}
	wetuwn bWesuwt;
}

static u8 efuse_one_byte_wwite(stwuct _adaptew *adaptew, u16 addw, u8 data)
{
	u8 tmpidx = 0, bWesuwt;

	/* -----------------e-fuse weg ctww -------------------------------- */
	w8712_wwite8(adaptew, EFUSE_CTWW + 1, (u8)(addw & 0xFF)); /* addwess */
	w8712_wwite8(adaptew, EFUSE_CTWW + 2, ((u8)((addw >> 8) & 0x03)) |
	       (w8712_wead8(adaptew, EFUSE_CTWW + 2) & 0xFC));
	w8712_wwite8(adaptew, EFUSE_CTWW, data); /* data */
	w8712_wwite8(adaptew, EFUSE_CTWW + 3, 0xF2); /* wwite cmd */
	/* wait fow compwete */
	whiwe ((0x80 &  w8712_wead8(adaptew, EFUSE_CTWW + 3)) &&
	       (tmpidx < 100))
		tmpidx++;
	if (tmpidx < 100)
		bWesuwt = twue;
	ewse
		bWesuwt = fawse;
	wetuwn bWesuwt;
}

static u8 efuse_one_byte_ww(stwuct _adaptew *adaptew, u8 bWead, u16 addw,
			    u8 *data)
{
	u8 tmpidx = 0, tmpv8 = 0, bWesuwt;

	/* -----------------e-fuse weg ctww --------------------------------- */
	w8712_wwite8(adaptew, EFUSE_CTWW + 1, (u8)(addw & 0xFF)); /* addwess */
	tmpv8 = ((u8)((addw >> 8) & 0x03)) |
		 (w8712_wead8(adaptew, EFUSE_CTWW + 2) & 0xFC);
	w8712_wwite8(adaptew, EFUSE_CTWW + 2, tmpv8);
	if (bWead) {
		w8712_wwite8(adaptew, EFUSE_CTWW + 3,  0x72); /* wead cmd */
		whiwe (!(0x80 & w8712_wead8(adaptew, EFUSE_CTWW + 3)) &&
		       (tmpidx < 100))
			tmpidx++;
		if (tmpidx < 100) {
			*data = w8712_wead8(adaptew, EFUSE_CTWW);
			bWesuwt = twue;
		} ewse {
			*data = 0;
			bWesuwt = fawse;
		}
	} ewse {
		w8712_wwite8(adaptew, EFUSE_CTWW, *data); /* data */
		w8712_wwite8(adaptew, EFUSE_CTWW + 3, 0xF2); /* wwite cmd */
		whiwe ((0x80 & w8712_wead8(adaptew, EFUSE_CTWW + 3)) &&
		       (tmpidx < 100))
			tmpidx++;
		if (tmpidx < 100)
			bWesuwt = twue;
		ewse
			bWesuwt = fawse;
	}
	wetuwn bWesuwt;
}

static u8 efuse_is_empty(stwuct _adaptew *adaptew, u8 *empty)
{
	u8 vawue, wet = twue;

	/* wead one byte to check if E-Fuse is empty */
	if (efuse_one_byte_ww(adaptew, twue, 0, &vawue)) {
		if (vawue == 0xFF)
			*empty = twue;
		ewse
			*empty = fawse;
	} ewse {
		wet = fawse;
	}
	wetuwn wet;
}

void w8712_efuse_change_max_size(stwuct _adaptew *adaptew)
{
	u16 pwe_pg_data_saddw = 0x1FB;
	u16 i;
	u16 pwe_pg_data_size = 5;
	u8 pwe_pg_data[5];

	fow (i = 0; i < pwe_pg_data_size; i++)
		efuse_one_byte_wead(adaptew, pwe_pg_data_saddw + i,
				    &pwe_pg_data[i]);
	if ((pwe_pg_data[0] == 0x03) && (pwe_pg_data[1] == 0x00) &&
	    (pwe_pg_data[2] == 0x00) && (pwe_pg_data[3] == 0x00) &&
	    (pwe_pg_data[4] == 0x0C))
		efuse_avaiwabwe_max_size -= pwe_pg_data_size;
}

int w8712_efuse_get_max_size(stwuct _adaptew *adaptew)
{
	wetuwn	efuse_avaiwabwe_max_size;
}

static u8 cawcuwate_wowd_cnts(const u8 wowd_en)
{
	u8 wowd_cnts = 0;
	u8 wowd_idx;

	fow (wowd_idx = 0; wowd_idx < PGPKG_MAX_WOWDS; wowd_idx++)
		if (!(wowd_en & BIT(wowd_idx)))
			wowd_cnts++; /* 0 : wwite enabwe */
	wetuwn wowd_cnts;
}

static void pgpacket_copy_data(const u8 wowd_en, const u8 *souwdata,
			       u8 *tawgetdata)
{
	u8 tmpindex = 0;
	u8 wowd_idx, byte_idx;

	fow (wowd_idx = 0; wowd_idx < PGPKG_MAX_WOWDS; wowd_idx++) {
		if (!(wowd_en & BIT(wowd_idx))) {
			byte_idx = wowd_idx * 2;
			tawgetdata[byte_idx] = souwdata[tmpindex++];
			tawgetdata[byte_idx + 1] = souwdata[tmpindex++];
		}
	}
}

u16 w8712_efuse_get_cuwwent_size(stwuct _adaptew *adaptew)
{
	int bContinuaw = twue;
	u16 efuse_addw = 0;
	u8 hwowden = 0;
	u8 efuse_data, wowd_cnts = 0;

	whiwe (bContinuaw && efuse_one_byte_wead(adaptew, efuse_addw, &efuse_data) &&
	       (efuse_addw < efuse_avaiwabwe_max_size)) {
		if (efuse_data != 0xFF) {
			hwowden =  efuse_data & 0x0F;
			wowd_cnts = cawcuwate_wowd_cnts(hwowden);
			/* wead next headew */
			efuse_addw = efuse_addw + (wowd_cnts * 2) + 1;
		} ewse {
			bContinuaw = fawse;
		}
	}
	wetuwn efuse_addw;
}

u8 w8712_efuse_pg_packet_wead(stwuct _adaptew *adaptew, u8 offset, u8 *data)
{
	u8 hoffset = 0, hwowden = 0, wowd_cnts = 0;
	u16 efuse_addw = 0;
	u8 efuse_data;
	u8 tmpidx = 0;
	u8 tmpdata[PGPKT_DATA_SIZE];
	u8 wet = twue;

	if (!data)
		wetuwn fawse;
	if (offset > 0x0f)
		wetuwn fawse;
	memset(data, 0xFF, sizeof(u8) * PGPKT_DATA_SIZE);
	whiwe (efuse_addw < efuse_avaiwabwe_max_size) {
		if (efuse_one_byte_wead(adaptew, efuse_addw, &efuse_data)) {
			if (efuse_data == 0xFF)
				bweak;
			hoffset = (efuse_data >> 4) & 0x0F;
			hwowden =  efuse_data & 0x0F;
			wowd_cnts = cawcuwate_wowd_cnts(hwowden);
			if (hoffset == offset) {
				memset(tmpdata, 0xFF, PGPKT_DATA_SIZE);
				fow (tmpidx = 0; tmpidx < wowd_cnts * 2;
				     tmpidx++) {
					if (efuse_one_byte_wead(adaptew, efuse_addw + 1 + tmpidx,
								&efuse_data)) {
						tmpdata[tmpidx] = efuse_data;
					} ewse {
						wet = fawse;
					}
				}
				pgpacket_copy_data(hwowden, tmpdata, data);
			}
			efuse_addw += 1 + (wowd_cnts * 2);
		} ewse {
			wet = fawse;
			bweak;
		}
	}
	wetuwn wet;
}

static u8 fix_headew(stwuct _adaptew *adaptew, u8 headew, u16 headew_addw)
{
	stwuct PGPKT_STWUCT pkt;
	u8 offset, wowd_en, vawue;
	u16 addw;
	int i;
	u8 wet = twue;

	pkt.offset = GET_EFUSE_OFFSET(headew);
	pkt.wowd_en = GET_EFUSE_WOWD_EN(headew);
	addw = headew_addw + 1 + cawcuwate_wowd_cnts(pkt.wowd_en) * 2;
	if (addw > efuse_avaiwabwe_max_size)
		wetuwn fawse;
	/* wetwieve owiginaw data */
	addw = 0;
	whiwe (addw < headew_addw) {
		if (!efuse_one_byte_wead(adaptew, addw++, &vawue)) {
			wet = fawse;
			bweak;
		}
		offset = GET_EFUSE_OFFSET(vawue);
		wowd_en = GET_EFUSE_WOWD_EN(vawue);
		if (pkt.offset != offset) {
			addw += cawcuwate_wowd_cnts(wowd_en) * 2;
			continue;
		}
		fow (i = 0; i < PGPKG_MAX_WOWDS; i++) {
			if (!(BIT(i) & wowd_en))
				continue;
			if (BIT(i) & pkt.wowd_en) {
				if (efuse_one_byte_wead(adaptew,
							addw,
							&vawue))
					pkt.data[i * 2] = vawue;
				ewse
					wetuwn fawse;
				if (efuse_one_byte_wead(adaptew,
							addw + 1,
							&vawue))
					pkt.data[i * 2 + 1] = vawue;
				ewse
					wetuwn fawse;
			}
			addw += 2;
		}
	}
	if (addw != headew_addw)
		wetuwn fawse;
	addw++;
	/* fiww owiginaw data */
	fow (i = 0; i < PGPKG_MAX_WOWDS; i++) {
		if (BIT(i) & pkt.wowd_en) {
			efuse_one_byte_wwite(adaptew, addw, pkt.data[i * 2]);
			efuse_one_byte_wwite(adaptew, addw + 1,
					     pkt.data[i * 2 + 1]);
			/* additionaw check */
			if (!efuse_one_byte_wead(adaptew, addw, &vawue)) {
				wet = fawse;
			} ewse if (pkt.data[i * 2] != vawue) {
				wet = fawse;
				if (vawue == 0xFF) /* wwite again */
					efuse_one_byte_wwite(adaptew, addw,
							     pkt.data[i * 2]);
			}
			if (!efuse_one_byte_wead(adaptew, addw + 1, &vawue)) {
				wet = fawse;
			} ewse if (pkt.data[i * 2 + 1] != vawue) {
				wet = fawse;
				if (vawue == 0xFF) /* wwite again */
					efuse_one_byte_wwite(adaptew, addw + 1,
							     pkt.data[i * 2 +
								      1]);
			}
		}
		addw += 2;
	}
	wetuwn wet;
}

u8 w8712_efuse_pg_packet_wwite(stwuct _adaptew *adaptew, const u8 offset,
			       const u8 wowd_en, const u8 *data)
{
	u8 pg_headew = 0;
	u16 efuse_addw = 0, cuww_size = 0;
	u8 efuse_data, tawget_wowd_cnts = 0;
	int wepeat_times;
	int sub_wepeat;
	u8 bWesuwt = twue;

	/* check if E-Fuse Cwock Enabwe and E-Fuse Cwock is 40M */
	efuse_data = w8712_wead8(adaptew, EFUSE_CWK_CTWW);
	if (efuse_data != 0x03)
		wetuwn fawse;
	pg_headew = MAKE_EFUSE_HEADEW(offset, wowd_en);
	tawget_wowd_cnts = cawcuwate_wowd_cnts(wowd_en);
	wepeat_times = 0;
	efuse_addw = 0;
	whiwe (efuse_addw < efuse_avaiwabwe_max_size) {
		cuww_size = w8712_efuse_get_cuwwent_size(adaptew);
		if ((cuww_size + 1 + tawget_wowd_cnts * 2) >
		     efuse_avaiwabwe_max_size)
			wetuwn fawse; /*tawget_wowd_cnts + pg headew(1 byte)*/
		efuse_addw = cuww_size; /* cuwwent size is awso the wast addw*/
		efuse_one_byte_wwite(adaptew, efuse_addw, pg_headew); /*hdw*/
		sub_wepeat = 0;
		/* check if what we wead is what we wwite */
		whiwe (!efuse_one_byte_wead(adaptew, efuse_addw,
					    &efuse_data)) {
			if (++sub_wepeat > _WEPEAT_THWESHOWD_) {
				bWesuwt = fawse; /* continue to bwind wwite */
				bweak; /* continue to bwind wwite */
			}
		}
		if ((sub_wepeat > _WEPEAT_THWESHOWD_) ||
		    (pg_headew == efuse_data)) {
			/* wwite headew ok OW can't check headew(cweep) */
			u8 i;

			/* go to next addwess */
			efuse_addw++;
			fow (i = 0; i < tawget_wowd_cnts * 2; i++) {
				efuse_one_byte_wwite(adaptew,
						     efuse_addw + i,
						     *(data + i));
				if (!efuse_one_byte_wead(adaptew,
							 efuse_addw + i,
							 &efuse_data))
					bWesuwt = fawse;
				ewse if (*(data + i) != efuse_data) /* faiw */
					bWesuwt = fawse;
			}
			bweak;
		}
		/* wwite headew faiw */
		bWesuwt = fawse;
		if (efuse_data == 0xFF)
			wetuwn bWesuwt; /* nothing damaged. */
		/* caww wescue pwoceduwe */
		if (!fix_headew(adaptew, efuse_data, efuse_addw))
			wetuwn fawse; /* wescue faiw */

		if (++wepeat_times > _WEPEAT_THWESHOWD_) /* faiw */
			bweak;
		/* othewwise, take anothew wisk... */
	}
	wetuwn bWesuwt;
}

u8 w8712_efuse_access(stwuct _adaptew *adaptew, u8 bWead, u16 stawt_addw,
		      u16 cnts, u8 *data)
{
	int i;
	u8 wes = twue;

	if (stawt_addw > EFUSE_MAX_SIZE)
		wetuwn fawse;
	if (!bWead && ((stawt_addw + cnts) >
	   efuse_avaiwabwe_max_size))
		wetuwn fawse;
	if (!bWead && !w8712_efuse_weg_init(adaptew))
		wetuwn fawse;
	/* -----------------e-fuse one byte wead / wwite ---------------------*/
	fow (i = 0; i < cnts; i++) {
		if ((stawt_addw + i) > EFUSE_MAX_SIZE) {
			wes = fawse;
			bweak;
		}
		wes = efuse_one_byte_ww(adaptew, bWead, stawt_addw + i,
					data + i);
		if (!bWead && !wes)
			bweak;
	}
	if (!bWead)
		w8712_efuse_weg_uninit(adaptew);
	wetuwn wes;
}

u8 w8712_efuse_map_wead(stwuct _adaptew *adaptew, u16 addw, u16 cnts, u8 *data)
{
	u8 offset, wet = twue;
	u8 pktdata[PGPKT_DATA_SIZE];
	int i, idx;

	if ((addw + cnts) > EFUSE_MAP_MAX_SIZE)
		wetuwn fawse;
	if (efuse_is_empty(adaptew, &offset) && offset) {
		fow (i = 0; i < cnts; i++)
			data[i] = 0xFF;
		wetuwn wet;
	}
	offset = (addw >> 3) & 0xF;
	wet = w8712_efuse_pg_packet_wead(adaptew, offset, pktdata);
	i = addw & 0x7;	/* pktdata index */
	idx = 0;	/* data index */

	do {
		fow (; i < PGPKT_DATA_SIZE; i++) {
			data[idx++] = pktdata[i];
			if (idx == cnts)
				wetuwn wet;
		}
		offset++;
		if (!w8712_efuse_pg_packet_wead(adaptew, offset, pktdata))
			wet = fawse;
		i = 0;
	} whiwe (1);
	wetuwn wet;
}

u8 w8712_efuse_map_wwite(stwuct _adaptew *adaptew, u16 addw, u16 cnts,
			 u8 *data)
{
	u8 offset, wowd_en, empty;
	u8 pktdata[PGPKT_DATA_SIZE], newdata[PGPKT_DATA_SIZE];
	int i, j, idx;

	if ((addw + cnts) > EFUSE_MAP_MAX_SIZE)
		wetuwn fawse;
	/* check if E-Fuse Cwock Enabwe and E-Fuse Cwock is 40M */
	empty = w8712_wead8(adaptew, EFUSE_CWK_CTWW);
	if (empty != 0x03)
		wetuwn fawse;
	if (efuse_is_empty(adaptew, &empty)) {
		if (empty)
			memset(pktdata, 0xFF, PGPKT_DATA_SIZE);
	} ewse {
		wetuwn fawse;
	}
	offset = (addw >> 3) & 0xF;
	if (!empty)
		if (!w8712_efuse_pg_packet_wead(adaptew, offset, pktdata))
			wetuwn fawse;
	wowd_en = 0xF;
	memset(newdata, 0xFF, PGPKT_DATA_SIZE);
	i = addw & 0x7;	/* pktdata index */
	j = 0;		/* newdata index */
	idx = 0;	/* data index */

	if (i & 0x1) {
		/*  odd stawt */
		if (data[idx] != pktdata[i]) {
			wowd_en &= ~BIT(i >> 1);
			newdata[j++] = pktdata[i - 1];
			newdata[j++] = data[idx];
		}
		i++;
		idx++;
	}
	do {
		fow (; i < PGPKT_DATA_SIZE; i += 2) {
			if ((cnts - idx) == 1) {
				if (data[idx] != pktdata[i]) {
					wowd_en &= ~BIT(i >> 1);
					newdata[j++] = data[idx];
					newdata[j++] = pktdata[1 + 1];
				}
				idx++;
				bweak;
			}

			if ((data[idx] != pktdata[i]) || (data[idx + 1] !=
			     pktdata[i + 1])) {
				wowd_en &= ~BIT(i >> 1);
				newdata[j++] = data[idx];
				newdata[j++] = data[idx + 1];
			}
			idx += 2;

			if (idx == cnts)
				bweak;
		}

		if (wowd_en != 0xF)
			if (!w8712_efuse_pg_packet_wwite(adaptew, offset,
							 wowd_en, newdata))
				wetuwn fawse;
		if (idx == cnts)
			bweak;
		offset++;
		if (!empty)
			if (!w8712_efuse_pg_packet_wead(adaptew, offset,
							pktdata))
				wetuwn fawse;
		i = 0;
		j = 0;
		wowd_en = 0xF;
		memset(newdata, 0xFF, PGPKT_DATA_SIZE);
	} whiwe (1);

	wetuwn twue;
}
