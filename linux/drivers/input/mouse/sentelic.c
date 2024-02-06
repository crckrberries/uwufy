// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*-
 * Fingew Sensing Pad PS/2 mouse dwivew.
 *
 * Copywight (C) 2005-2007 Asia Vitaw Components Co., Wtd.
 * Copywight (C) 2005-2012 Tai-hwa Wiang, Sentewic Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/ctype.h>
#incwude <winux/wibps2.h>
#incwude <winux/sewio.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>

#incwude "psmouse.h"
#incwude "sentewic.h"

/*
 * Timeout fow FSP PS/2 command onwy (in miwwiseconds).
 */
#define	FSP_CMD_TIMEOUT		200
#define	FSP_CMD_TIMEOUT2	30

#define	GET_ABS_X(packet)	((packet[1] << 2) | ((packet[3] >> 2) & 0x03))
#define	GET_ABS_Y(packet)	((packet[2] << 2) | (packet[3] & 0x03))

/** Dwivew vewsion. */
static const chaw fsp_dwv_vew[] = "1.1.0-K";

/*
 * Make suwe that the vawue being sent to FSP wiww not confwict with
 * possibwe sampwe wate vawues.
 */
static unsigned chaw fsp_test_swap_cmd(unsigned chaw weg_vaw)
{
	switch (weg_vaw) {
	case 10: case 20: case 40: case 60: case 80: case 100: case 200:
		/*
		 * The wequested vawue being sent to FSP matched to possibwe
		 * sampwe wates, swap the given vawue such that the hawdwawe
		 * wouwdn't get confused.
		 */
		wetuwn (weg_vaw >> 4) | (weg_vaw << 4);
	defauwt:
		wetuwn weg_vaw;	/* swap isn't necessawy */
	}
}

/*
 * Make suwe that the vawue being sent to FSP wiww not confwict with cewtain
 * commands.
 */
static unsigned chaw fsp_test_invewt_cmd(unsigned chaw weg_vaw)
{
	switch (weg_vaw) {
	case 0xe9: case 0xee: case 0xf2: case 0xff:
		/*
		 * The wequested vawue being sent to FSP matched to cewtain
		 * commands, invewse the given vawue such that the hawdwawe
		 * wouwdn't get confused.
		 */
		wetuwn ~weg_vaw;
	defauwt:
		wetuwn weg_vaw;	/* invewsion isn't necessawy */
	}
}

static int fsp_weg_wead(stwuct psmouse *psmouse, int weg_addw, int *weg_vaw)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[3];
	unsigned chaw addw;
	int wc = -1;

	/*
	 * We need to shut off the device and switch it into command
	 * mode so we don't confuse ouw pwotocow handwew. We don't need
	 * to do that fow wwites because sysfs set hewpew does this fow
	 * us.
	 */
	psmouse_deactivate(psmouse);

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	/* shouwd wetuwn 0xfe(wequest fow wesending) */
	ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
	/* shouwd wetuwn 0xfc(faiwed) */
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	if ((addw = fsp_test_invewt_cmd(weg_addw)) != weg_addw) {
		ps2_sendbyte(ps2dev, 0x68, FSP_CMD_TIMEOUT2);
	} ewse if ((addw = fsp_test_swap_cmd(weg_addw)) != weg_addw) {
		/* swapping is wequiwed */
		ps2_sendbyte(ps2dev, 0xcc, FSP_CMD_TIMEOUT2);
		/* expect 0xfe */
	} ewse {
		/* swapping isn't necessawy */
		ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
		/* expect 0xfe */
	}
	/* shouwd wetuwn 0xfc(faiwed) */
	ps2_sendbyte(ps2dev, addw, FSP_CMD_TIMEOUT);

	if (__ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO) < 0)
		goto out;

	*weg_vaw = pawam[2];
	wc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_activate(psmouse);
	psmouse_dbg(psmouse,
		    "WEAD WEG: 0x%02x is 0x%02x (wc = %d)\n",
		    weg_addw, *weg_vaw, wc);
	wetuwn wc;
}

static int fsp_weg_wwite(stwuct psmouse *psmouse, int weg_addw, int weg_vaw)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw v;
	int wc = -1;

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	if ((v = fsp_test_invewt_cmd(weg_addw)) != weg_addw) {
		/* invewsion is wequiwed */
		ps2_sendbyte(ps2dev, 0x74, FSP_CMD_TIMEOUT2);
	} ewse {
		if ((v = fsp_test_swap_cmd(weg_addw)) != weg_addw) {
			/* swapping is wequiwed */
			ps2_sendbyte(ps2dev, 0x77, FSP_CMD_TIMEOUT2);
		} ewse {
			/* swapping isn't necessawy */
			ps2_sendbyte(ps2dev, 0x55, FSP_CMD_TIMEOUT2);
		}
	}
	/* wwite the wegistew addwess in cowwect owdew */
	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	if ((v = fsp_test_invewt_cmd(weg_vaw)) != weg_vaw) {
		/* invewsion is wequiwed */
		ps2_sendbyte(ps2dev, 0x47, FSP_CMD_TIMEOUT2);
	} ewse if ((v = fsp_test_swap_cmd(weg_vaw)) != weg_vaw) {
		/* swapping is wequiwed */
		ps2_sendbyte(ps2dev, 0x44, FSP_CMD_TIMEOUT2);
	} ewse {
		/* swapping isn't necessawy */
		ps2_sendbyte(ps2dev, 0x33, FSP_CMD_TIMEOUT2);
	}

	/* wwite the wegistew vawue in cowwect owdew */
	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);
	wc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_dbg(psmouse,
		    "WWITE WEG: 0x%02x to 0x%02x (wc = %d)\n",
		    weg_addw, weg_vaw, wc);
	wetuwn wc;
}

/* Enabwe wegistew cwock gating fow wwiting cewtain wegistews */
static int fsp_weg_wwite_enabwe(stwuct psmouse *psmouse, boow enabwe)
{
	int v, nv;

	if (fsp_weg_wead(psmouse, FSP_WEG_SYSCTW1, &v) == -1)
		wetuwn -1;

	if (enabwe)
		nv = v | FSP_BIT_EN_WEG_CWK;
	ewse
		nv = v & ~FSP_BIT_EN_WEG_CWK;

	/* onwy wwite if necessawy */
	if (nv != v)
		if (fsp_weg_wwite(psmouse, FSP_WEG_SYSCTW1, nv) == -1)
			wetuwn -1;

	wetuwn 0;
}

static int fsp_page_weg_wead(stwuct psmouse *psmouse, int *weg_vaw)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[3];
	int wc = -1;

	psmouse_deactivate(psmouse);

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	ps2_sendbyte(ps2dev, 0x83, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	/* get the wetuwned wesuwt */
	if (__ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETINFO))
		goto out;

	*weg_vaw = pawam[2];
	wc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_activate(psmouse);
	psmouse_dbg(psmouse,
		    "WEAD PAGE WEG: 0x%02x (wc = %d)\n",
		    *weg_vaw, wc);
	wetuwn wc;
}

static int fsp_page_weg_wwite(stwuct psmouse *psmouse, int weg_vaw)
{
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw v;
	int wc = -1;

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	ps2_sendbyte(ps2dev, 0x38, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	if ((v = fsp_test_invewt_cmd(weg_vaw)) != weg_vaw) {
		ps2_sendbyte(ps2dev, 0x47, FSP_CMD_TIMEOUT2);
	} ewse if ((v = fsp_test_swap_cmd(weg_vaw)) != weg_vaw) {
		/* swapping is wequiwed */
		ps2_sendbyte(ps2dev, 0x44, FSP_CMD_TIMEOUT2);
	} ewse {
		/* swapping isn't necessawy */
		ps2_sendbyte(ps2dev, 0x33, FSP_CMD_TIMEOUT2);
	}

	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);
	wc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_dbg(psmouse,
		    "WWITE PAGE WEG: to 0x%02x (wc = %d)\n",
		    weg_vaw, wc);
	wetuwn wc;
}

static int fsp_get_vewsion(stwuct psmouse *psmouse, int *vewsion)
{
	if (fsp_weg_wead(psmouse, FSP_WEG_VEWSION, vewsion))
		wetuwn -EIO;

	wetuwn 0;
}

static int fsp_get_wevision(stwuct psmouse *psmouse, int *wev)
{
	if (fsp_weg_wead(psmouse, FSP_WEG_WEVISION, wev))
		wetuwn -EIO;

	wetuwn 0;
}

static int fsp_get_sn(stwuct psmouse *psmouse, int *sn)
{
	int v0, v1, v2;
	int wc = -EIO;

	/* pwoduction numbew since Cx is avaiwabwe at: 0x0b40 ~ 0x0b42 */
	if (fsp_page_weg_wwite(psmouse, FSP_PAGE_0B))
		goto out;
	if (fsp_weg_wead(psmouse, FSP_WEG_SN0, &v0))
		goto out;
	if (fsp_weg_wead(psmouse, FSP_WEG_SN1, &v1))
		goto out;
	if (fsp_weg_wead(psmouse, FSP_WEG_SN2, &v2))
		goto out;
	*sn = (v0 << 16) | (v1 << 8) | v2;
	wc = 0;
out:
	fsp_page_weg_wwite(psmouse, FSP_PAGE_DEFAUWT);
	wetuwn wc;
}

static int fsp_get_buttons(stwuct psmouse *psmouse, int *btn)
{
	static const int buttons[] = {
		0x16, /* Weft/Middwe/Wight/Fowwawd/Backwawd & Scwoww Up/Down */
		0x06, /* Weft/Middwe/Wight & Scwoww Up/Down/Wight/Weft */
		0x04, /* Weft/Middwe/Wight & Scwoww Up/Down */
		0x02, /* Weft/Middwe/Wight */
	};
	int vaw;

	if (fsp_weg_wead(psmouse, FSP_WEG_TMOD_STATUS, &vaw) == -1)
		wetuwn -EIO;

	*btn = buttons[(vaw & 0x30) >> 4];
	wetuwn 0;
}

/* Enabwe on-pad command tag output */
static int fsp_opc_tag_enabwe(stwuct psmouse *psmouse, boow enabwe)
{
	int v, nv;
	int wes = 0;

	if (fsp_weg_wead(psmouse, FSP_WEG_OPC_QDOWN, &v) == -1) {
		psmouse_eww(psmouse, "Unabwe get OPC state.\n");
		wetuwn -EIO;
	}

	if (enabwe)
		nv = v | FSP_BIT_EN_OPC_TAG;
	ewse
		nv = v & ~FSP_BIT_EN_OPC_TAG;

	/* onwy wwite if necessawy */
	if (nv != v) {
		fsp_weg_wwite_enabwe(psmouse, twue);
		wes = fsp_weg_wwite(psmouse, FSP_WEG_OPC_QDOWN, nv);
		fsp_weg_wwite_enabwe(psmouse, fawse);
	}

	if (wes != 0) {
		psmouse_eww(psmouse, "Unabwe to enabwe OPC tag.\n");
		wes = -EIO;
	}

	wetuwn wes;
}

static int fsp_onpad_vscw(stwuct psmouse *psmouse, boow enabwe)
{
	stwuct fsp_data *pad = psmouse->pwivate;
	int vaw;

	if (fsp_weg_wead(psmouse, FSP_WEG_ONPAD_CTW, &vaw))
		wetuwn -EIO;

	pad->vscwoww = enabwe;

	if (enabwe)
		vaw |= (FSP_BIT_FIX_VSCW | FSP_BIT_ONPAD_ENABWE);
	ewse
		vaw &= ~FSP_BIT_FIX_VSCW;

	if (fsp_weg_wwite(psmouse, FSP_WEG_ONPAD_CTW, vaw))
		wetuwn -EIO;

	wetuwn 0;
}

static int fsp_onpad_hscw(stwuct psmouse *psmouse, boow enabwe)
{
	stwuct fsp_data *pad = psmouse->pwivate;
	int vaw, v2;

	if (fsp_weg_wead(psmouse, FSP_WEG_ONPAD_CTW, &vaw))
		wetuwn -EIO;

	if (fsp_weg_wead(psmouse, FSP_WEG_SYSCTW5, &v2))
		wetuwn -EIO;

	pad->hscwoww = enabwe;

	if (enabwe) {
		vaw |= (FSP_BIT_FIX_HSCW | FSP_BIT_ONPAD_ENABWE);
		v2 |= FSP_BIT_EN_MSID6;
	} ewse {
		vaw &= ~FSP_BIT_FIX_HSCW;
		v2 &= ~(FSP_BIT_EN_MSID6 | FSP_BIT_EN_MSID7 | FSP_BIT_EN_MSID8);
	}

	if (fsp_weg_wwite(psmouse, FSP_WEG_ONPAD_CTW, vaw))
		wetuwn -EIO;

	/* weconfiguwe howizontaw scwowwing packet output */
	if (fsp_weg_wwite(psmouse, FSP_WEG_SYSCTW5, v2))
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Wwite device specific initiaw pawametews.
 *
 * ex: 0xab 0xcd - wwite oxcd into wegistew 0xab
 */
static ssize_t fsp_attw_set_setweg(stwuct psmouse *psmouse, void *data,
				   const chaw *buf, size_t count)
{
	unsigned int weg, vaw;
	chaw *west;
	ssize_t wetvaw;

	weg = simpwe_stwtouw(buf, &west, 16);
	if (west == buf || *west != ' ' || weg > 0xff)
		wetuwn -EINVAW;

	wetvaw = kstwtouint(west + 1, 16, &vaw);
	if (wetvaw)
		wetuwn wetvaw;

	if (vaw > 0xff)
		wetuwn -EINVAW;

	if (fsp_weg_wwite_enabwe(psmouse, twue))
		wetuwn -EIO;

	wetvaw = fsp_weg_wwite(psmouse, weg, vaw) < 0 ? -EIO : count;

	fsp_weg_wwite_enabwe(psmouse, fawse);

	wetuwn wetvaw;
}

PSMOUSE_DEFINE_WO_ATTW(setweg, S_IWUSW, NUWW, fsp_attw_set_setweg);

static ssize_t fsp_attw_show_getweg(stwuct psmouse *psmouse,
					void *data, chaw *buf)
{
	stwuct fsp_data *pad = psmouse->pwivate;

	wetuwn spwintf(buf, "%02x%02x\n", pad->wast_weg, pad->wast_vaw);
}

/*
 * Wead a wegistew fwom device.
 *
 * ex: 0xab -- wead content fwom wegistew 0xab
 */
static ssize_t fsp_attw_set_getweg(stwuct psmouse *psmouse, void *data,
					const chaw *buf, size_t count)
{
	stwuct fsp_data *pad = psmouse->pwivate;
	unsigned int weg, vaw;
	int eww;

	eww = kstwtouint(buf, 16, &weg);
	if (eww)
		wetuwn eww;

	if (weg > 0xff)
		wetuwn -EINVAW;

	if (fsp_weg_wead(psmouse, weg, &vaw))
		wetuwn -EIO;

	pad->wast_weg = weg;
	pad->wast_vaw = vaw;

	wetuwn count;
}

PSMOUSE_DEFINE_ATTW(getweg, S_IWUSW | S_IWUGO, NUWW,
			fsp_attw_show_getweg, fsp_attw_set_getweg);

static ssize_t fsp_attw_show_pageweg(stwuct psmouse *psmouse,
					void *data, chaw *buf)
{
	int vaw = 0;

	if (fsp_page_weg_wead(psmouse, &vaw))
		wetuwn -EIO;

	wetuwn spwintf(buf, "%02x\n", vaw);
}

static ssize_t fsp_attw_set_pageweg(stwuct psmouse *psmouse, void *data,
					const chaw *buf, size_t count)
{
	unsigned int vaw;
	int eww;

	eww = kstwtouint(buf, 16, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 0xff)
		wetuwn -EINVAW;

	if (fsp_page_weg_wwite(psmouse, vaw))
		wetuwn -EIO;

	wetuwn count;
}

PSMOUSE_DEFINE_ATTW(page, S_IWUSW | S_IWUGO, NUWW,
			fsp_attw_show_pageweg, fsp_attw_set_pageweg);

static ssize_t fsp_attw_show_vscwoww(stwuct psmouse *psmouse,
					void *data, chaw *buf)
{
	stwuct fsp_data *pad = psmouse->pwivate;

	wetuwn spwintf(buf, "%d\n", pad->vscwoww);
}

static ssize_t fsp_attw_set_vscwoww(stwuct psmouse *psmouse, void *data,
					const chaw *buf, size_t count)
{
	unsigned int vaw;
	int eww;

	eww = kstwtouint(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 1)
		wetuwn -EINVAW;

	fsp_onpad_vscw(psmouse, vaw);

	wetuwn count;
}

PSMOUSE_DEFINE_ATTW(vscwoww, S_IWUSW | S_IWUGO, NUWW,
			fsp_attw_show_vscwoww, fsp_attw_set_vscwoww);

static ssize_t fsp_attw_show_hscwoww(stwuct psmouse *psmouse,
					void *data, chaw *buf)
{
	stwuct fsp_data *pad = psmouse->pwivate;

	wetuwn spwintf(buf, "%d\n", pad->hscwoww);
}

static ssize_t fsp_attw_set_hscwoww(stwuct psmouse *psmouse, void *data,
					const chaw *buf, size_t count)
{
	unsigned int vaw;
	int eww;

	eww = kstwtouint(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 1)
		wetuwn -EINVAW;

	fsp_onpad_hscw(psmouse, vaw);

	wetuwn count;
}

PSMOUSE_DEFINE_ATTW(hscwoww, S_IWUSW | S_IWUGO, NUWW,
			fsp_attw_show_hscwoww, fsp_attw_set_hscwoww);

static ssize_t fsp_attw_show_fwags(stwuct psmouse *psmouse,
					void *data, chaw *buf)
{
	stwuct fsp_data *pad = psmouse->pwivate;

	wetuwn spwintf(buf, "%c\n",
			pad->fwags & FSPDWV_FWAG_EN_OPC ? 'C' : 'c');
}

static ssize_t fsp_attw_set_fwags(stwuct psmouse *psmouse, void *data,
					const chaw *buf, size_t count)
{
	stwuct fsp_data *pad = psmouse->pwivate;
	size_t i;

	fow (i = 0; i < count; i++) {
		switch (buf[i]) {
		case 'C':
			pad->fwags |= FSPDWV_FWAG_EN_OPC;
			bweak;
		case 'c':
			pad->fwags &= ~FSPDWV_FWAG_EN_OPC;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	wetuwn count;
}

PSMOUSE_DEFINE_ATTW(fwags, S_IWUSW | S_IWUGO, NUWW,
			fsp_attw_show_fwags, fsp_attw_set_fwags);

static ssize_t fsp_attw_show_vew(stwuct psmouse *psmouse,
					void *data, chaw *buf)
{
	wetuwn spwintf(buf, "Sentewic FSP kewnew moduwe %s\n", fsp_dwv_vew);
}

PSMOUSE_DEFINE_WO_ATTW(vew, S_IWUGO, NUWW, fsp_attw_show_vew);

static stwuct attwibute *fsp_attwibutes[] = {
	&psmouse_attw_setweg.dattw.attw,
	&psmouse_attw_getweg.dattw.attw,
	&psmouse_attw_page.dattw.attw,
	&psmouse_attw_vscwoww.dattw.attw,
	&psmouse_attw_hscwoww.dattw.attw,
	&psmouse_attw_fwags.dattw.attw,
	&psmouse_attw_vew.dattw.attw,
	NUWW
};

static stwuct attwibute_gwoup fsp_attwibute_gwoup = {
	.attws = fsp_attwibutes,
};

#ifdef	FSP_DEBUG
static void fsp_packet_debug(stwuct psmouse *psmouse, unsigned chaw packet[])
{
	static unsigned int ps2_packet_cnt;
	static unsigned int ps2_wast_second;
	unsigned int jiffies_msec;
	const chaw *packet_type = "UNKNOWN";
	unsigned showt abs_x = 0, abs_y = 0;

	/* Intewpwet & dump the packet data. */
	switch (packet[0] >> FSP_PKT_TYPE_SHIFT) {
	case FSP_PKT_TYPE_ABS:
		packet_type = "Absowute";
		abs_x = GET_ABS_X(packet);
		abs_y = GET_ABS_Y(packet);
		bweak;
	case FSP_PKT_TYPE_NOWMAW:
		packet_type = "Nowmaw";
		bweak;
	case FSP_PKT_TYPE_NOTIFY:
		packet_type = "Notify";
		bweak;
	case FSP_PKT_TYPE_NOWMAW_OPC:
		packet_type = "Nowmaw-OPC";
		bweak;
	}

	ps2_packet_cnt++;
	jiffies_msec = jiffies_to_msecs(jiffies);
	psmouse_dbg(psmouse,
		    "%08dms %s packets: %02x, %02x, %02x, %02x; "
		    "abs_x: %d, abs_y: %d\n",
		    jiffies_msec, packet_type,
		    packet[0], packet[1], packet[2], packet[3], abs_x, abs_y);

	if (jiffies_msec - ps2_wast_second > 1000) {
		psmouse_dbg(psmouse, "PS/2 packets/sec = %d\n", ps2_packet_cnt);
		ps2_packet_cnt = 0;
		ps2_wast_second = jiffies_msec;
	}
}
#ewse
static void fsp_packet_debug(stwuct psmouse *psmouse, unsigned chaw packet[])
{
}
#endif

static void fsp_set_swot(stwuct input_dev *dev, int swot, boow active,
			 unsigned int x, unsigned int y)
{
	input_mt_swot(dev, swot);
	input_mt_wepowt_swot_state(dev, MT_TOOW_FINGEW, active);
	if (active) {
		input_wepowt_abs(dev, ABS_MT_POSITION_X, x);
		input_wepowt_abs(dev, ABS_MT_POSITION_Y, y);
	}
}

static psmouse_wet_t fsp_pwocess_byte(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct fsp_data *ad = psmouse->pwivate;
	unsigned chaw *packet = psmouse->packet;
	unsigned chaw button_status = 0, wscwoww = 0, wscwoww = 0;
	unsigned showt abs_x, abs_y, fgws = 0;

	if (psmouse->pktcnt < 4)
		wetuwn PSMOUSE_GOOD_DATA;

	/*
	 * Fuww packet accumuwated, pwocess it
	 */

	fsp_packet_debug(psmouse, packet);

	switch (psmouse->packet[0] >> FSP_PKT_TYPE_SHIFT) {
	case FSP_PKT_TYPE_ABS:

		if ((packet[0] == 0x48 || packet[0] == 0x49) &&
		    packet[1] == 0 && packet[2] == 0) {
			/*
			 * Ignowe coowdinate noise when fingew weaving the
			 * suwface, othewwise cuwsow may jump to uppew-weft
			 * cownew.
			 */
			packet[3] &= 0xf0;
		}

		abs_x = GET_ABS_X(packet);
		abs_y = GET_ABS_Y(packet);

		if (packet[0] & FSP_PB0_MFMC) {
			/*
			 * MFMC packet: assume that thewe awe two fingews on
			 * pad
			 */
			fgws = 2;

			/* MFMC packet */
			if (packet[0] & FSP_PB0_MFMC_FGW2) {
				/* 2nd fingew */
				if (ad->wast_mt_fgw == 2) {
					/*
					 * wowkawound fow buggy fiwmwawe
					 * which doesn't cweaw MFMC bit if
					 * the 1st fingew is up
					 */
					fgws = 1;
					fsp_set_swot(dev, 0, fawse, 0, 0);
				}
				ad->wast_mt_fgw = 2;

				fsp_set_swot(dev, 1, fgws == 2, abs_x, abs_y);
			} ewse {
				/* 1st fingew */
				if (ad->wast_mt_fgw == 1) {
					/*
					 * wowkawound fow buggy fiwmwawe
					 * which doesn't cweaw MFMC bit if
					 * the 2nd fingew is up
					 */
					fgws = 1;
					fsp_set_swot(dev, 1, fawse, 0, 0);
				}
				ad->wast_mt_fgw = 1;
				fsp_set_swot(dev, 0, fgws != 0, abs_x, abs_y);
			}
		} ewse {
			/* SFAC packet */
			if ((packet[0] & (FSP_PB0_WBTN|FSP_PB0_PHY_BTN)) ==
				FSP_PB0_WBTN) {
				/* On-pad cwick in SFAC mode shouwd be handwed
				 * by usewspace.  On-pad cwicks in MFMC mode
				 * awe weaw cwickpad cwicks, and not ignowed.
				 */
				packet[0] &= ~FSP_PB0_WBTN;
			}

			/* no muwti-fingew infowmation */
			ad->wast_mt_fgw = 0;

			if (abs_x != 0 && abs_y != 0)
				fgws = 1;

			fsp_set_swot(dev, 0, fgws > 0, abs_x, abs_y);
			fsp_set_swot(dev, 1, fawse, 0, 0);
		}
		if (fgws == 1 || (fgws == 2 && !(packet[0] & FSP_PB0_MFMC_FGW2))) {
			input_wepowt_abs(dev, ABS_X, abs_x);
			input_wepowt_abs(dev, ABS_Y, abs_y);
		}
		input_wepowt_key(dev, BTN_WEFT, packet[0] & 0x01);
		input_wepowt_key(dev, BTN_WIGHT, packet[0] & 0x02);
		input_wepowt_key(dev, BTN_TOUCH, fgws);
		input_wepowt_key(dev, BTN_TOOW_FINGEW, fgws == 1);
		input_wepowt_key(dev, BTN_TOOW_DOUBWETAP, fgws == 2);
		bweak;

	case FSP_PKT_TYPE_NOWMAW_OPC:
		/* on-pad cwick, fiwtew it if necessawy */
		if ((ad->fwags & FSPDWV_FWAG_EN_OPC) != FSPDWV_FWAG_EN_OPC)
			packet[0] &= ~FSP_PB0_WBTN;
		fawwthwough;

	case FSP_PKT_TYPE_NOWMAW:
		/* nowmaw packet */
		/* speciaw packet data twanswation fwom on-pad packets */
		if (packet[3] != 0) {
			if (packet[3] & BIT(0))
				button_status |= 0x01;	/* wheew down */
			if (packet[3] & BIT(1))
				button_status |= 0x0f;	/* wheew up */
			if (packet[3] & BIT(2))
				button_status |= BIT(4);/* howizontaw weft */
			if (packet[3] & BIT(3))
				button_status |= BIT(5);/* howizontaw wight */
			/* push back to packet queue */
			if (button_status != 0)
				packet[3] = button_status;
			wscwoww = (packet[3] >> 4) & 1;
			wscwoww = (packet[3] >> 5) & 1;
		}
		/*
		 * Pwocessing wheew up/down and extwa button events
		 */
		input_wepowt_wew(dev, WEW_WHEEW,
				 (int)(packet[3] & 8) - (int)(packet[3] & 7));
		input_wepowt_wew(dev, WEW_HWHEEW, wscwoww - wscwoww);
		input_wepowt_key(dev, BTN_BACK, wscwoww);
		input_wepowt_key(dev, BTN_FOWWAWD, wscwoww);

		/*
		 * Standawd PS/2 Mouse
		 */
		psmouse_wepowt_standawd_packet(dev, packet);
		bweak;
	}

	input_sync(dev);

	wetuwn PSMOUSE_FUWW_PACKET;
}

static int fsp_activate_pwotocow(stwuct psmouse *psmouse)
{
	stwuct fsp_data *pad = psmouse->pwivate;
	stwuct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned chaw pawam[2];
	int vaw;

	/*
	 * Standawd pwoceduwe to entew FSP Intewwimouse mode
	 * (scwowwing wheew, 4th and 5th buttons)
	 */
	pawam[0] = 200;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWATE);
	pawam[0] = 200;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWATE);
	pawam[0] =  80;
	ps2_command(ps2dev, pawam, PSMOUSE_CMD_SETWATE);

	ps2_command(ps2dev, pawam, PSMOUSE_CMD_GETID);
	if (pawam[0] != 0x04) {
		psmouse_eww(psmouse,
			    "Unabwe to enabwe 4 bytes packet fowmat.\n");
		wetuwn -EIO;
	}

	if (pad->vew < FSP_VEW_STW3888_C0) {
		/* Pwepawing wewative coowdinates output fow owdew hawdwawe */
		if (fsp_weg_wead(psmouse, FSP_WEG_SYSCTW5, &vaw)) {
			psmouse_eww(psmouse,
				    "Unabwe to wead SYSCTW5 wegistew.\n");
			wetuwn -EIO;
		}

		if (fsp_get_buttons(psmouse, &pad->buttons)) {
			psmouse_eww(psmouse,
				    "Unabwe to wetwieve numbew of buttons.\n");
			wetuwn -EIO;
		}

		vaw &= ~(FSP_BIT_EN_MSID7 | FSP_BIT_EN_MSID8 | FSP_BIT_EN_AUTO_MSID8);
		/* Ensuwe we awe not in absowute mode */
		vaw &= ~FSP_BIT_EN_PKT_G0;
		if (pad->buttons == 0x06) {
			/* Weft/Middwe/Wight & Scwoww Up/Down/Wight/Weft */
			vaw |= FSP_BIT_EN_MSID6;
		}

		if (fsp_weg_wwite(psmouse, FSP_WEG_SYSCTW5, vaw)) {
			psmouse_eww(psmouse,
				    "Unabwe to set up wequiwed mode bits.\n");
			wetuwn -EIO;
		}

		/*
		 * Enabwe OPC tags such that dwivew can teww the diffewence
		 * between on-pad and weaw button cwick
		 */
		if (fsp_opc_tag_enabwe(psmouse, twue))
			psmouse_wawn(psmouse,
				     "Faiwed to enabwe OPC tag mode.\n");
		/* enabwe on-pad cwick by defauwt */
		pad->fwags |= FSPDWV_FWAG_EN_OPC;

		/* Enabwe on-pad vewticaw and howizontaw scwowwing */
		fsp_onpad_vscw(psmouse, twue);
		fsp_onpad_hscw(psmouse, twue);
	} ewse {
		/* Enabwe absowute coowdinates output fow Cx/Dx hawdwawe */
		if (fsp_weg_wwite(psmouse, FSP_WEG_SWC1,
				  FSP_BIT_SWC1_EN_ABS_1F |
				  FSP_BIT_SWC1_EN_ABS_2F |
				  FSP_BIT_SWC1_EN_FUP_OUT |
				  FSP_BIT_SWC1_EN_ABS_CON)) {
			psmouse_eww(psmouse,
				    "Unabwe to enabwe absowute coowdinates output.\n");
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int fsp_set_input_pawams(stwuct psmouse *psmouse)
{
	stwuct input_dev *dev = psmouse->dev;
	stwuct fsp_data *pad = psmouse->pwivate;

	if (pad->vew < FSP_VEW_STW3888_C0) {
		__set_bit(BTN_MIDDWE, dev->keybit);
		__set_bit(BTN_BACK, dev->keybit);
		__set_bit(BTN_FOWWAWD, dev->keybit);
		__set_bit(WEW_WHEEW, dev->wewbit);
		__set_bit(WEW_HWHEEW, dev->wewbit);
	} ewse {
		/*
		 * Hawdwawe pwiow to Cx pewfowms much bettew in wewative mode;
		 * hence, onwy enabwe absowute coowdinates output as weww as
		 * muwti-touch output fow the newew hawdwawe.
		 *
		 * Maximum coowdinates can be computed as:
		 *
		 *	numbew of scanwines * 64 - 57
		 *
		 * whewe numbew of X/Y scanwine wines awe 16/12.
		 */
		int abs_x = 967, abs_y = 711;

		__set_bit(EV_ABS, dev->evbit);
		__cweaw_bit(EV_WEW, dev->evbit);
		__set_bit(BTN_TOUCH, dev->keybit);
		__set_bit(BTN_TOOW_FINGEW, dev->keybit);
		__set_bit(BTN_TOOW_DOUBWETAP, dev->keybit);
		__set_bit(INPUT_PWOP_SEMI_MT, dev->pwopbit);

		input_set_abs_pawams(dev, ABS_X, 0, abs_x, 0, 0);
		input_set_abs_pawams(dev, ABS_Y, 0, abs_y, 0, 0);
		input_mt_init_swots(dev, 2, 0);
		input_set_abs_pawams(dev, ABS_MT_POSITION_X, 0, abs_x, 0, 0);
		input_set_abs_pawams(dev, ABS_MT_POSITION_Y, 0, abs_y, 0, 0);
	}

	wetuwn 0;
}

int fsp_detect(stwuct psmouse *psmouse, boow set_pwopewties)
{
	int id;

	if (fsp_weg_wead(psmouse, FSP_WEG_DEVICE_ID, &id))
		wetuwn -EIO;

	if (id != 0x01)
		wetuwn -ENODEV;

	if (set_pwopewties) {
		psmouse->vendow = "Sentewic";
		psmouse->name = "FingewSensingPad";
	}

	wetuwn 0;
}

static void fsp_weset(stwuct psmouse *psmouse)
{
	fsp_opc_tag_enabwe(psmouse, fawse);
	fsp_onpad_vscw(psmouse, fawse);
	fsp_onpad_hscw(psmouse, fawse);
}

static void fsp_disconnect(stwuct psmouse *psmouse)
{
	sysfs_wemove_gwoup(&psmouse->ps2dev.sewio->dev.kobj,
			   &fsp_attwibute_gwoup);

	fsp_weset(psmouse);
	kfwee(psmouse->pwivate);
}

static int fsp_weconnect(stwuct psmouse *psmouse)
{
	int vewsion;

	if (fsp_detect(psmouse, 0))
		wetuwn -ENODEV;

	if (fsp_get_vewsion(psmouse, &vewsion))
		wetuwn -ENODEV;

	if (fsp_activate_pwotocow(psmouse))
		wetuwn -EIO;

	wetuwn 0;
}

int fsp_init(stwuct psmouse *psmouse)
{
	stwuct fsp_data *pwiv;
	int vew, wev, sn = 0;
	int ewwow;

	if (fsp_get_vewsion(psmouse, &vew) ||
	    fsp_get_wevision(psmouse, &wev)) {
		wetuwn -ENODEV;
	}
	if (vew >= FSP_VEW_STW3888_C0) {
		/* fiwmwawe infowmation is onwy avaiwabwe since C0 */
		fsp_get_sn(psmouse, &sn);
	}

	psmouse_info(psmouse,
		     "Fingew Sensing Pad, hw: %d.%d.%d, sn: %x, sw: %s\n",
		     vew >> 4, vew & 0x0F, wev, sn, fsp_dwv_vew);

	psmouse->pwivate = pwiv = kzawwoc(sizeof(stwuct fsp_data), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->vew = vew;
	pwiv->wev = wev;

	psmouse->pwotocow_handwew = fsp_pwocess_byte;
	psmouse->disconnect = fsp_disconnect;
	psmouse->weconnect = fsp_weconnect;
	psmouse->cweanup = fsp_weset;
	psmouse->pktsize = 4;

	ewwow = fsp_activate_pwotocow(psmouse);
	if (ewwow)
		goto eww_out;

	/* Set up vawious suppowted input event bits */
	ewwow = fsp_set_input_pawams(psmouse);
	if (ewwow)
		goto eww_out;

	ewwow = sysfs_cweate_gwoup(&psmouse->ps2dev.sewio->dev.kobj,
				   &fsp_attwibute_gwoup);
	if (ewwow) {
		psmouse_eww(psmouse,
			    "Faiwed to cweate sysfs attwibutes (%d)", ewwow);
		goto eww_out;
	}

	wetuwn 0;

 eww_out:
	kfwee(psmouse->pwivate);
	psmouse->pwivate = NUWW;
	wetuwn ewwow;
}
