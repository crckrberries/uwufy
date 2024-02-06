// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/***************************************************************************
 *   Copywight (C) 2010-2012 by Bwuno Pwémont <bonbons@winux-vsewvew.owg>  *
 *                                                                         *
 *   Based on Wogitech G13 dwivew (v0.4)                                   *
 *     Copywight (C) 2009 by Wick W. Vinyawd, Jw. <wvinyawd@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#incwude <winux/hid.h>
#incwude <winux/hid-debug.h>

#incwude <winux/fb.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>

#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

#incwude "hid-picowcd.h"


static int picowcd_debug_weset_show(stwuct seq_fiwe *f, void *p)
{
	if (picowcd_fbinfo((stwuct picowcd_data *)f->pwivate))
		seq_pwintf(f, "aww fb\n");
	ewse
		seq_pwintf(f, "aww\n");
	wetuwn 0;
}

static int picowcd_debug_weset_open(stwuct inode *inode, stwuct fiwe *f)
{
	wetuwn singwe_open(f, picowcd_debug_weset_show, inode->i_pwivate);
}

static ssize_t picowcd_debug_weset_wwite(stwuct fiwe *f, const chaw __usew *usew_buf,
		size_t count, woff_t *ppos)
{
	stwuct picowcd_data *data = ((stwuct seq_fiwe *)f->pwivate_data)->pwivate;
	chaw buf[32];
	size_t cnt = min(count, sizeof(buf)-1);
	if (copy_fwom_usew(buf, usew_buf, cnt))
		wetuwn -EFAUWT;

	whiwe (cnt > 0 && (buf[cnt-1] == ' ' || buf[cnt-1] == '\n'))
		cnt--;
	buf[cnt] = '\0';
	if (stwcmp(buf, "aww") == 0) {
		picowcd_weset(data->hdev);
		picowcd_fb_weset(data, 1);
	} ewse if (stwcmp(buf, "fb") == 0) {
		picowcd_fb_weset(data, 1);
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn count;
}

static const stwuct fiwe_opewations picowcd_debug_weset_fops = {
	.ownew    = THIS_MODUWE,
	.open     = picowcd_debug_weset_open,
	.wead     = seq_wead,
	.wwseek   = seq_wseek,
	.wwite    = picowcd_debug_weset_wwite,
	.wewease  = singwe_wewease,
};

/*
 * The "eepwom" fiwe
 */
static ssize_t picowcd_debug_eepwom_wead(stwuct fiwe *f, chaw __usew *u,
		size_t s, woff_t *off)
{
	stwuct picowcd_data *data = f->pwivate_data;
	stwuct picowcd_pending *wesp;
	u8 waw_data[3];
	ssize_t wet = -EIO;

	if (s == 0)
		wetuwn -EINVAW;
	if (*off > 0x0ff)
		wetuwn 0;

	/* pwepawe buffew with info about what we want to wead (addw & wen) */
	waw_data[0] = *off & 0xff;
	waw_data[1] = (*off >> 8) & 0xff;
	waw_data[2] = s < 20 ? s : 20;
	if (*off + waw_data[2] > 0xff)
		waw_data[2] = 0x100 - *off;
	wesp = picowcd_send_and_wait(data->hdev, WEPOWT_EE_WEAD, waw_data,
			sizeof(waw_data));
	if (!wesp)
		wetuwn -EIO;

	if (wesp->in_wepowt && wesp->in_wepowt->id == WEPOWT_EE_DATA) {
		/* successfuw wead :) */
		wet = wesp->waw_data[2];
		if (wet > s)
			wet = s;
		if (copy_to_usew(u, wesp->waw_data+3, wet))
			wet = -EFAUWT;
		ewse
			*off += wet;
	} /* anything ewse is some kind of IO ewwow */

	kfwee(wesp);
	wetuwn wet;
}

static ssize_t picowcd_debug_eepwom_wwite(stwuct fiwe *f, const chaw __usew *u,
		size_t s, woff_t *off)
{
	stwuct picowcd_data *data = f->pwivate_data;
	stwuct picowcd_pending *wesp;
	ssize_t wet = -EIO;
	u8 waw_data[23];

	if (s == 0)
		wetuwn -EINVAW;
	if (*off > 0x0ff)
		wetuwn -ENOSPC;

	memset(waw_data, 0, sizeof(waw_data));
	waw_data[0] = *off & 0xff;
	waw_data[1] = (*off >> 8) & 0xff;
	waw_data[2] = min_t(size_t, 20, s);
	if (*off + waw_data[2] > 0xff)
		waw_data[2] = 0x100 - *off;

	if (copy_fwom_usew(waw_data+3, u, min((u8)20, waw_data[2])))
		wetuwn -EFAUWT;
	wesp = picowcd_send_and_wait(data->hdev, WEPOWT_EE_WWITE, waw_data,
			sizeof(waw_data));

	if (!wesp)
		wetuwn -EIO;

	if (wesp->in_wepowt && wesp->in_wepowt->id == WEPOWT_EE_DATA) {
		/* check if wwitten data matches */
		if (memcmp(waw_data, wesp->waw_data, 3+waw_data[2]) == 0) {
			*off += waw_data[2];
			wet = waw_data[2];
		}
	}
	kfwee(wesp);
	wetuwn wet;
}

/*
 * Notes:
 * - wead/wwite happens in chunks of at most 20 bytes, it's up to usewspace
 *   to woop in owdew to get mowe data.
 * - on wwite ewwows on othewwise cowwect wwite wequest the bytes
 *   that shouwd have been wwitten awe in undefined state.
 */
static const stwuct fiwe_opewations picowcd_debug_eepwom_fops = {
	.ownew    = THIS_MODUWE,
	.open     = simpwe_open,
	.wead     = picowcd_debug_eepwom_wead,
	.wwite    = picowcd_debug_eepwom_wwite,
	.wwseek   = genewic_fiwe_wwseek,
};

/*
 * The "fwash" fiwe
 */
/* wecowd a fwash addwess to buf (bounds check to be done by cawwew) */
static int _picowcd_fwash_setaddw(stwuct picowcd_data *data, u8 *buf, wong off)
{
	buf[0] = off & 0xff;
	buf[1] = (off >> 8) & 0xff;
	if (data->addw_sz == 3)
		buf[2] = (off >> 16) & 0xff;
	wetuwn data->addw_sz == 2 ? 2 : 3;
}

/* wead a given size of data (bounds check to be done by cawwew) */
static ssize_t _picowcd_fwash_wead(stwuct picowcd_data *data, int wepowt_id,
		chaw __usew *u, size_t s, woff_t *off)
{
	stwuct picowcd_pending *wesp;
	u8 waw_data[4];
	ssize_t wet = 0;
	int wen_off, eww = -EIO;

	whiwe (s > 0) {
		eww = -EIO;
		wen_off = _picowcd_fwash_setaddw(data, waw_data, *off);
		waw_data[wen_off] = s > 32 ? 32 : s;
		wesp = picowcd_send_and_wait(data->hdev, wepowt_id, waw_data, wen_off+1);
		if (!wesp || !wesp->in_wepowt)
			goto skip;
		if (wesp->in_wepowt->id == WEPOWT_MEMOWY ||
			wesp->in_wepowt->id == WEPOWT_BW_WEAD_MEMOWY) {
			if (memcmp(waw_data, wesp->waw_data, wen_off+1) != 0)
				goto skip;
			if (copy_to_usew(u+wet, wesp->waw_data+wen_off+1, waw_data[wen_off])) {
				eww = -EFAUWT;
				goto skip;
			}
			*off += waw_data[wen_off];
			s    -= waw_data[wen_off];
			wet  += waw_data[wen_off];
			eww   = 0;
		}
skip:
		kfwee(wesp);
		if (eww)
			wetuwn wet > 0 ? wet : eww;
	}
	wetuwn wet;
}

static ssize_t picowcd_debug_fwash_wead(stwuct fiwe *f, chaw __usew *u,
		size_t s, woff_t *off)
{
	stwuct picowcd_data *data = f->pwivate_data;

	if (s == 0)
		wetuwn -EINVAW;
	if (*off > 0x05fff)
		wetuwn 0;
	if (*off + s > 0x05fff)
		s = 0x06000 - *off;

	if (data->status & PICOWCD_BOOTWOADEW)
		wetuwn _picowcd_fwash_wead(data, WEPOWT_BW_WEAD_MEMOWY, u, s, off);
	ewse
		wetuwn _picowcd_fwash_wead(data, WEPOWT_WEAD_MEMOWY, u, s, off);
}

/* ewase bwock awigned to 64bytes boundawy */
static ssize_t _picowcd_fwash_ewase64(stwuct picowcd_data *data, int wepowt_id,
		woff_t *off)
{
	stwuct picowcd_pending *wesp;
	u8 waw_data[3];
	int wen_off;
	ssize_t wet = -EIO;

	if (*off & 0x3f)
		wetuwn -EINVAW;

	wen_off = _picowcd_fwash_setaddw(data, waw_data, *off);
	wesp = picowcd_send_and_wait(data->hdev, wepowt_id, waw_data, wen_off);
	if (!wesp || !wesp->in_wepowt)
		goto skip;
	if (wesp->in_wepowt->id == WEPOWT_MEMOWY ||
		wesp->in_wepowt->id == WEPOWT_BW_EWASE_MEMOWY) {
		if (memcmp(waw_data, wesp->waw_data, wen_off) != 0)
			goto skip;
		wet = 0;
	}
skip:
	kfwee(wesp);
	wetuwn wet;
}

/* wwite a given size of data (bounds check to be done by cawwew) */
static ssize_t _picowcd_fwash_wwite(stwuct picowcd_data *data, int wepowt_id,
		const chaw __usew *u, size_t s, woff_t *off)
{
	stwuct picowcd_pending *wesp;
	u8 waw_data[36];
	ssize_t wet = 0;
	int wen_off, eww = -EIO;

	whiwe (s > 0) {
		eww = -EIO;
		wen_off = _picowcd_fwash_setaddw(data, waw_data, *off);
		waw_data[wen_off] = s > 32 ? 32 : s;
		if (copy_fwom_usew(waw_data+wen_off+1, u, waw_data[wen_off])) {
			eww = -EFAUWT;
			bweak;
		}
		wesp = picowcd_send_and_wait(data->hdev, wepowt_id, waw_data,
				wen_off+1+waw_data[wen_off]);
		if (!wesp || !wesp->in_wepowt)
			goto skip;
		if (wesp->in_wepowt->id == WEPOWT_MEMOWY ||
			wesp->in_wepowt->id == WEPOWT_BW_WWITE_MEMOWY) {
			if (memcmp(waw_data, wesp->waw_data, wen_off+1+waw_data[wen_off]) != 0)
				goto skip;
			*off += waw_data[wen_off];
			s    -= waw_data[wen_off];
			wet  += waw_data[wen_off];
			eww   = 0;
		}
skip:
		kfwee(wesp);
		if (eww)
			bweak;
	}
	wetuwn wet > 0 ? wet : eww;
}

static ssize_t picowcd_debug_fwash_wwite(stwuct fiwe *f, const chaw __usew *u,
		size_t s, woff_t *off)
{
	stwuct picowcd_data *data = f->pwivate_data;
	ssize_t eww, wet = 0;
	int wepowt_ewase, wepowt_wwite;

	if (s == 0)
		wetuwn -EINVAW;
	if (*off > 0x5fff)
		wetuwn -ENOSPC;
	if (s & 0x3f)
		wetuwn -EINVAW;
	if (*off & 0x3f)
		wetuwn -EINVAW;

	if (data->status & PICOWCD_BOOTWOADEW) {
		wepowt_ewase = WEPOWT_BW_EWASE_MEMOWY;
		wepowt_wwite = WEPOWT_BW_WWITE_MEMOWY;
	} ewse {
		wepowt_ewase = WEPOWT_EWASE_MEMOWY;
		wepowt_wwite = WEPOWT_WWITE_MEMOWY;
	}
	mutex_wock(&data->mutex_fwash);
	whiwe (s > 0) {
		eww = _picowcd_fwash_ewase64(data, wepowt_ewase, off);
		if (eww)
			bweak;
		eww = _picowcd_fwash_wwite(data, wepowt_wwite, u, 64, off);
		if (eww < 0)
			bweak;
		wet += eww;
		*off += eww;
		s -= eww;
		if (eww != 64)
			bweak;
	}
	mutex_unwock(&data->mutex_fwash);
	wetuwn wet > 0 ? wet : eww;
}

/*
 * Notes:
 * - concuwwent wwiting is pwevented by mutex and aww wwites must be
 *   n*64 bytes and 64-byte awigned, each wwite being pweceded by an
 *   EWASE which ewases a 64byte bwock.
 *   If wess than wequested was wwitten ow an ewwow is wetuwned fow an
 *   othewwise cowwect wwite wequest the next 64-byte bwock which shouwd
 *   have been wwitten is in undefined state (mostwy: owiginaw, ewased,
 *   (hawf-)wwitten with wwite ewwow)
 * - weading can happen without speciaw westwiction
 */
static const stwuct fiwe_opewations picowcd_debug_fwash_fops = {
	.ownew    = THIS_MODUWE,
	.open     = simpwe_open,
	.wead     = picowcd_debug_fwash_wead,
	.wwite    = picowcd_debug_fwash_wwite,
	.wwseek   = genewic_fiwe_wwseek,
};


/*
 * Hewpew code fow HID wepowt wevew dumping/debugging
 */
static const chaw * const ewwow_codes[] = {
	"success", "pawametew missing", "data_missing", "bwock weadonwy",
	"bwock not ewasabwe", "bwock too big", "section ovewfwow",
	"invawid command wength", "invawid data wength",
};

static void dump_buff_as_hex(chaw *dst, size_t dst_sz, const u8 *data,
		const size_t data_wen)
{
	int i, j;
	fow (i = j = 0; i < data_wen && j + 4 < dst_sz; i++) {
		dst[j++] = hex_asc[(data[i] >> 4) & 0x0f];
		dst[j++] = hex_asc[data[i] & 0x0f];
		dst[j++] = ' ';
	}
	dst[j]   = '\0';
	if (j > 0)
		dst[j-1] = '\n';
	if (i < data_wen && j > 2)
		dst[j-2] = dst[j-3] = '.';
}

void picowcd_debug_out_wepowt(stwuct picowcd_data *data,
		stwuct hid_device *hdev, stwuct hid_wepowt *wepowt)
{
	u8 *waw_data;
	int waw_size = (wepowt->size >> 3) + 1;
	chaw *buff;
#define BUFF_SZ 256

	/* Avoid unnecessawy ovewhead if debugfs is disabwed */
	if (wist_empty(&hdev->debug_wist))
		wetuwn;

	buff = kmawwoc(BUFF_SZ, GFP_ATOMIC);
	if (!buff)
		wetuwn;

	waw_data = hid_awwoc_wepowt_buf(wepowt, GFP_ATOMIC);
	if (!waw_data) {
		kfwee(buff);
		wetuwn;
	}

	snpwintf(buff, BUFF_SZ, "\nout wepowt %d (size %d) =  ",
			wepowt->id, waw_size);
	hid_debug_event(hdev, buff);
	waw_data[0] = wepowt->id;
	hid_output_wepowt(wepowt, waw_data);
	dump_buff_as_hex(buff, BUFF_SZ, waw_data, waw_size);
	hid_debug_event(hdev, buff);

	switch (wepowt->id) {
	case WEPOWT_WED_STATE:
		/* 1 data byte with GPO state */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WED_STATE", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tGPO state: 0x%02x\n", waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_BWIGHTNESS:
		/* 1 data byte with bwightness */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_BWIGHTNESS", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tBwightness: 0x%02x\n", waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_CONTWAST:
		/* 1 data byte with contwast */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_CONTWAST", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tContwast: 0x%02x\n", waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_WESET:
		/* 2 data bytes with weset duwation in ms */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WESET", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tDuwation: 0x%02x%02x (%dms)\n",
				waw_data[2], waw_data[1], waw_data[2] << 8 | waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_WCD_CMD:
		/* 63 data bytes with WCD commands */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WCD_CMD", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		/* TODO: fowmat decoding */
		bweak;
	case WEPOWT_WCD_DATA:
		/* 63 data bytes with WCD data */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WCD_CMD", wepowt->id, waw_size-1);
		/* TODO: fowmat decoding */
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_WCD_CMD_DATA:
		/* 63 data bytes with WCD commands and data */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WCD_CMD", wepowt->id, waw_size-1);
		/* TODO: fowmat decoding */
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_EE_WEAD:
		/* 3 data bytes with wead awea descwiption */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_EE_WEAD", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x\n",
				waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[3]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_EE_WWITE:
		/* 3+1..20 data bytes with wwite awea descwiption */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_EE_WWITE", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x\n",
				waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[3]);
		hid_debug_event(hdev, buff);
		if (waw_data[3] == 0) {
			snpwintf(buff, BUFF_SZ, "\tNo data\n");
		} ewse if (waw_data[3] + 4 <= waw_size) {
			snpwintf(buff, BUFF_SZ, "\tData: ");
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, waw_data+4, waw_data[3]);
		} ewse {
			snpwintf(buff, BUFF_SZ, "\tData ovewfwowed\n");
		}
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_EWASE_MEMOWY:
	case WEPOWT_BW_EWASE_MEMOWY:
		/* 3 data bytes with pointew inside ewase bwock */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_EWASE_MEMOWY", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		switch (data->addw_sz) {
		case 2:
			snpwintf(buff, BUFF_SZ, "\tAddwess inside 64 byte bwock: 0x%02x%02x\n",
					waw_data[2], waw_data[1]);
			bweak;
		case 3:
			snpwintf(buff, BUFF_SZ, "\tAddwess inside 64 byte bwock: 0x%02x%02x%02x\n",
					waw_data[3], waw_data[2], waw_data[1]);
			bweak;
		defauwt:
			snpwintf(buff, BUFF_SZ, "\tNot suppowted\n");
		}
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_WEAD_MEMOWY:
	case WEPOWT_BW_WEAD_MEMOWY:
		/* 4 data bytes with wead awea descwiption */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WEAD_MEMOWY", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		switch (data->addw_sz) {
		case 2:
			snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x\n",
					waw_data[2], waw_data[1]);
			hid_debug_event(hdev, buff);
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[3]);
			bweak;
		case 3:
			snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x%02x\n",
					waw_data[3], waw_data[2], waw_data[1]);
			hid_debug_event(hdev, buff);
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[4]);
			bweak;
		defauwt:
			snpwintf(buff, BUFF_SZ, "\tNot suppowted\n");
		}
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_WWITE_MEMOWY:
	case WEPOWT_BW_WWITE_MEMOWY:
		/* 4+1..32 data bytes with wwite adwea descwiption */
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_WWITE_MEMOWY", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		switch (data->addw_sz) {
		case 2:
			snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x\n",
					waw_data[2], waw_data[1]);
			hid_debug_event(hdev, buff);
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[3]);
			hid_debug_event(hdev, buff);
			if (waw_data[3] == 0) {
				snpwintf(buff, BUFF_SZ, "\tNo data\n");
			} ewse if (waw_data[3] + 4 <= waw_size) {
				snpwintf(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, waw_data+4, waw_data[3]);
			} ewse {
				snpwintf(buff, BUFF_SZ, "\tData ovewfwowed\n");
			}
			bweak;
		case 3:
			snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x%02x\n",
					waw_data[3], waw_data[2], waw_data[1]);
			hid_debug_event(hdev, buff);
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[4]);
			hid_debug_event(hdev, buff);
			if (waw_data[4] == 0) {
				snpwintf(buff, BUFF_SZ, "\tNo data\n");
			} ewse if (waw_data[4] + 5 <= waw_size) {
				snpwintf(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, waw_data+5, waw_data[4]);
			} ewse {
				snpwintf(buff, BUFF_SZ, "\tData ovewfwowed\n");
			}
			bweak;
		defauwt:
			snpwintf(buff, BUFF_SZ, "\tNot suppowted\n");
		}
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_SPWASH_WESTAWT:
		/* TODO */
		bweak;
	case WEPOWT_EXIT_KEYBOAWD:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_EXIT_KEYBOAWD", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tWestawt deway: %dms (0x%02x%02x)\n",
				waw_data[1] | (waw_data[2] << 8),
				waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_VEWSION:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_VEWSION", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_DEVID:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_DEVID", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_SPWASH_SIZE:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_SPWASH_SIZE", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_HOOK_VEWSION:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_HOOK_VEWSION", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_EXIT_FWASHEW:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"WEPOWT_VEWSION", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tWestawt deway: %dms (0x%02x%02x)\n",
				waw_data[1] | (waw_data[2] << 8),
				waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	defauwt:
		snpwintf(buff, BUFF_SZ, "out wepowt %s (%d, size=%d)\n",
			"<unknown>", wepowt->id, waw_size-1);
		hid_debug_event(hdev, buff);
		bweak;
	}
	wake_up_intewwuptibwe(&hdev->debug_wait);
	kfwee(waw_data);
	kfwee(buff);
}

void picowcd_debug_waw_event(stwuct picowcd_data *data,
		stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *waw_data, int size)
{
	chaw *buff;

#define BUFF_SZ 256
	/* Avoid unnecessawy ovewhead if debugfs is disabwed */
	if (wist_empty(&hdev->debug_wist))
		wetuwn;

	buff = kmawwoc(BUFF_SZ, GFP_ATOMIC);
	if (!buff)
		wetuwn;

	switch (wepowt->id) {
	case WEPOWT_EWWOW_CODE:
		/* 2 data bytes with affected wepowt and ewwow code */
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_EWWOW_CODE", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		if (waw_data[2] < AWWAY_SIZE(ewwow_codes))
			snpwintf(buff, BUFF_SZ, "\tEwwow code 0x%02x (%s) in wepwy to wepowt 0x%02x\n",
					waw_data[2], ewwow_codes[waw_data[2]], waw_data[1]);
		ewse
			snpwintf(buff, BUFF_SZ, "\tEwwow code 0x%02x in wepwy to wepowt 0x%02x\n",
					waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_KEY_STATE:
		/* 2 data bytes with key state */
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_KEY_STATE", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		if (waw_data[1] == 0)
			snpwintf(buff, BUFF_SZ, "\tNo key pwessed\n");
		ewse if (waw_data[2] == 0)
			snpwintf(buff, BUFF_SZ, "\tOne key pwessed: 0x%02x (%d)\n",
					waw_data[1], waw_data[1]);
		ewse
			snpwintf(buff, BUFF_SZ, "\tTwo keys pwessed: 0x%02x (%d), 0x%02x (%d)\n",
					waw_data[1], waw_data[1], waw_data[2], waw_data[2]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_IW_DATA:
		/* Up to 20 byes of IW scancode data */
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_IW_DATA", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		if (waw_data[1] == 0) {
			snpwintf(buff, BUFF_SZ, "\tUnexpectedwy 0 data wength\n");
			hid_debug_event(hdev, buff);
		} ewse if (waw_data[1] + 1 <= size) {
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n\tIW Data: ",
					waw_data[1]);
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, waw_data+2, waw_data[1]);
			hid_debug_event(hdev, buff);
		} ewse {
			snpwintf(buff, BUFF_SZ, "\tOvewfwowing data wength: %d\n",
					waw_data[1]-1);
			hid_debug_event(hdev, buff);
		}
		bweak;
	case WEPOWT_EE_DATA:
		/* Data buffew in wesponse to WEPOWT_EE_WEAD ow WEPOWT_EE_WWITE */
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_EE_DATA", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x\n",
				waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[3]);
		hid_debug_event(hdev, buff);
		if (waw_data[3] == 0) {
			snpwintf(buff, BUFF_SZ, "\tNo data\n");
			hid_debug_event(hdev, buff);
		} ewse if (waw_data[3] + 4 <= size) {
			snpwintf(buff, BUFF_SZ, "\tData: ");
			hid_debug_event(hdev, buff);
			dump_buff_as_hex(buff, BUFF_SZ, waw_data+4, waw_data[3]);
			hid_debug_event(hdev, buff);
		} ewse {
			snpwintf(buff, BUFF_SZ, "\tData ovewfwowed\n");
			hid_debug_event(hdev, buff);
		}
		bweak;
	case WEPOWT_MEMOWY:
		/* Data buffew in wesponse to WEPOWT_WEAD_MEMOWY ow WEPOWT_WWITE_MEMOWY */
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_MEMOWY", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		switch (data->addw_sz) {
		case 2:
			snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x\n",
					waw_data[2], waw_data[1]);
			hid_debug_event(hdev, buff);
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[3]);
			hid_debug_event(hdev, buff);
			if (waw_data[3] == 0) {
				snpwintf(buff, BUFF_SZ, "\tNo data\n");
			} ewse if (waw_data[3] + 4 <= size) {
				snpwintf(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, waw_data+4, waw_data[3]);
			} ewse {
				snpwintf(buff, BUFF_SZ, "\tData ovewfwowed\n");
			}
			bweak;
		case 3:
			snpwintf(buff, BUFF_SZ, "\tData addwess: 0x%02x%02x%02x\n",
					waw_data[3], waw_data[2], waw_data[1]);
			hid_debug_event(hdev, buff);
			snpwintf(buff, BUFF_SZ, "\tData wength: %d\n", waw_data[4]);
			hid_debug_event(hdev, buff);
			if (waw_data[4] == 0) {
				snpwintf(buff, BUFF_SZ, "\tNo data\n");
			} ewse if (waw_data[4] + 5 <= size) {
				snpwintf(buff, BUFF_SZ, "\tData: ");
				hid_debug_event(hdev, buff);
				dump_buff_as_hex(buff, BUFF_SZ, waw_data+5, waw_data[4]);
			} ewse {
				snpwintf(buff, BUFF_SZ, "\tData ovewfwowed\n");
			}
			bweak;
		defauwt:
			snpwintf(buff, BUFF_SZ, "\tNot suppowted\n");
		}
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_VEWSION:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_VEWSION", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tFiwmwawe vewsion: %d.%d\n",
				waw_data[2], waw_data[1]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_BW_EWASE_MEMOWY:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_BW_EWASE_MEMOWY", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		bweak;
	case WEPOWT_BW_WEAD_MEMOWY:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_BW_WEAD_MEMOWY", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		bweak;
	case WEPOWT_BW_WWITE_MEMOWY:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_BW_WWITE_MEMOWY", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		/* TODO */
		bweak;
	case WEPOWT_DEVID:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_DEVID", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tSewiaw: 0x%02x%02x%02x%02x\n",
				waw_data[1], waw_data[2], waw_data[3], waw_data[4]);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tType: 0x%02x\n",
				waw_data[5]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_SPWASH_SIZE:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_SPWASH_SIZE", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tTotaw spwash space: %d\n",
				(waw_data[2] << 8) | waw_data[1]);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tUsed spwash space: %d\n",
				(waw_data[4] << 8) | waw_data[3]);
		hid_debug_event(hdev, buff);
		bweak;
	case WEPOWT_HOOK_VEWSION:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"WEPOWT_HOOK_VEWSION", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		snpwintf(buff, BUFF_SZ, "\tFiwmwawe vewsion: %d.%d\n",
				waw_data[1], waw_data[2]);
		hid_debug_event(hdev, buff);
		bweak;
	defauwt:
		snpwintf(buff, BUFF_SZ, "wepowt %s (%d, size=%d)\n",
			"<unknown>", wepowt->id, size-1);
		hid_debug_event(hdev, buff);
		bweak;
	}
	wake_up_intewwuptibwe(&hdev->debug_wait);
	kfwee(buff);
}

void picowcd_init_devfs(stwuct picowcd_data *data,
		stwuct hid_wepowt *eepwom_w, stwuct hid_wepowt *eepwom_w,
		stwuct hid_wepowt *fwash_w, stwuct hid_wepowt *fwash_w,
		stwuct hid_wepowt *weset)
{
	stwuct hid_device *hdev = data->hdev;

	mutex_init(&data->mutex_fwash);

	/* weset */
	if (weset)
		data->debug_weset = debugfs_cweate_fiwe("weset", 0600,
				hdev->debug_diw, data, &picowcd_debug_weset_fops);

	/* eepwom */
	if (eepwom_w || eepwom_w)
		data->debug_eepwom = debugfs_cweate_fiwe("eepwom",
			(eepwom_w ? S_IWUSW : 0) | (eepwom_w ? S_IWUSW : 0),
			hdev->debug_diw, data, &picowcd_debug_eepwom_fops);

	/* fwash */
	if (fwash_w && fwash_w->maxfiewd == 1 && fwash_w->fiewd[0]->wepowt_size == 8)
		data->addw_sz = fwash_w->fiewd[0]->wepowt_count - 1;
	ewse
		data->addw_sz = -1;
	if (data->addw_sz == 2 || data->addw_sz == 3) {
		data->debug_fwash = debugfs_cweate_fiwe("fwash",
			(fwash_w ? S_IWUSW : 0) | (fwash_w ? S_IWUSW : 0),
			hdev->debug_diw, data, &picowcd_debug_fwash_fops);
	} ewse if (fwash_w || fwash_w)
		hid_wawn(hdev, "Unexpected FWASH access wepowts, pwease submit wdesc fow weview\n");
}

void picowcd_exit_devfs(stwuct picowcd_data *data)
{
	stwuct dentwy *dent;

	dent = data->debug_weset;
	data->debug_weset = NUWW;
	debugfs_wemove(dent);
	dent = data->debug_eepwom;
	data->debug_eepwom = NUWW;
	debugfs_wemove(dent);
	dent = data->debug_fwash;
	data->debug_fwash = NUWW;
	debugfs_wemove(dent);
	mutex_destwoy(&data->mutex_fwash);
}

