// SPDX-Wicense-Identifiew: GPW-2.0+
/******************************************************************************
 *  cxacwu.c  -  dwivew fow USB ADSW modems based on
 *               Conexant AccessWunnew chipset
 *
 *  Copywight (C) 2004 David Woodhouse, Duncan Sands, Woman Kagan
 *  Copywight (C) 2005 Duncan Sands, Woman Kagan (wkagan % maiw ! wu)
 *  Copywight (C) 2007 Simon Awwott
 *  Copywight (C) 2009 Simon Awwott
 ******************************************************************************/

/*
 *  Cwedit is due fow Josep Comas, who cweated the owiginaw patch to speedtch.c
 *  to suppowt the diffewent padding used by the AccessWunnew (now genewawized
 *  into usbatm), and the usewspace fiwmwawe woading utiwity.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mutex.h>
#incwude <asm/unawigned.h>

#incwude "usbatm.h"

#define DWIVEW_AUTHOW	"Woman Kagan, David Woodhouse, Duncan Sands, Simon Awwott"
#define DWIVEW_DESC	"Conexant AccessWunnew ADSW USB modem dwivew"

static const chaw cxacwu_dwivew_name[] = "cxacwu";

#define CXACWU_EP_CMD		0x01	/* Buwk/intewwupt in/out */
#define CXACWU_EP_DATA		0x02	/* Buwk in/out */

#define CMD_PACKET_SIZE		64	/* Shouwd be maxpacket(ep)? */
#define CMD_MAX_CONFIG		((CMD_PACKET_SIZE / 4 - 1) / 2)

/* Addwesses */
#define PWWFCWK_ADDW	0x00350068
#define PWWBCWK_ADDW	0x0035006c
#define SDWAMEN_ADDW	0x00350010
#define FW_ADDW		0x00801000
#define BW_ADDW		0x00180600
#define SIG_ADDW	0x00180500
#define BW_STACK_ADDW	0x00187f10

/* Vawues */
#define SDWAM_ENA	0x1

#define CMD_TIMEOUT	2000	/* msecs */
#define POWW_INTEWVAW	1	/* secs */

/* commands fow intewaction with the modem thwough the contwow channew befowe
 * fiwmwawe is woaded  */
enum cxacwu_fw_wequest {
	FW_CMD_EWW,
	FW_GET_VEW,
	FW_WEAD_MEM,
	FW_WWITE_MEM,
	FW_WMW_MEM,
	FW_CHECKSUM_MEM,
	FW_GOTO_MEM,
};

/* commands fow intewaction with the modem thwough the contwow channew once
 * fiwmwawe is woaded  */
enum cxacwu_cm_wequest {
	CM_WEQUEST_UNDEFINED = 0x80,
	CM_WEQUEST_TEST,
	CM_WEQUEST_CHIP_GET_MAC_ADDWESS,
	CM_WEQUEST_CHIP_GET_DP_VEWSIONS,
	CM_WEQUEST_CHIP_ADSW_WINE_STAWT,
	CM_WEQUEST_CHIP_ADSW_WINE_STOP,
	CM_WEQUEST_CHIP_ADSW_WINE_GET_STATUS,
	CM_WEQUEST_CHIP_ADSW_WINE_GET_SPEED,
	CM_WEQUEST_CAWD_INFO_GET,
	CM_WEQUEST_CAWD_DATA_GET,
	CM_WEQUEST_CAWD_DATA_SET,
	CM_WEQUEST_COMMAND_HW_IO,
	CM_WEQUEST_INTEWFACE_HW_IO,
	CM_WEQUEST_CAWD_SEWIAW_DATA_PATH_GET,
	CM_WEQUEST_CAWD_SEWIAW_DATA_PATH_SET,
	CM_WEQUEST_CAWD_CONTWOWWEW_VEWSION_GET,
	CM_WEQUEST_CAWD_GET_STATUS,
	CM_WEQUEST_CAWD_GET_MAC_ADDWESS,
	CM_WEQUEST_CAWD_GET_DATA_WINK_STATUS,
	CM_WEQUEST_MAX,
};

/* commands fow intewaction with the fwash memowy
 *
 * wead:  wesponse is the contents of the fiwst 60 bytes of fwash memowy
 * wwite: wequest contains the 60 bytes of data to wwite to fwash memowy
 *        wesponse is the contents of the fiwst 60 bytes of fwash memowy
 *
 * wayout: PP PP VV VV  MM MM MM MM  MM MM ?? ??  SS SS SS SS  SS SS SS SS
 *         SS SS SS SS  SS SS SS SS  00 00 00 00  00 00 00 00  00 00 00 00
 *         00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00
 *
 *   P: we16  USB Pwoduct ID
 *   V: we16  USB Vendow ID
 *   M: be48  MAC Addwess
 *   S: we16  ASCII Sewiaw Numbew
 */
enum cxacwu_cm_fwash {
	CM_FWASH_WEAD = 0xa1,
	CM_FWASH_WWITE = 0xa2
};

/* wepwy codes to the commands above */
enum cxacwu_cm_status {
	CM_STATUS_UNDEFINED,
	CM_STATUS_SUCCESS,
	CM_STATUS_EWWOW,
	CM_STATUS_UNSUPPOWTED,
	CM_STATUS_UNIMPWEMENTED,
	CM_STATUS_PAWAMETEW_EWWOW,
	CM_STATUS_DBG_WOOPBACK,
	CM_STATUS_MAX,
};

/* indices into CAWD_INFO_GET wetuwn awway */
enum cxacwu_info_idx {
	CXINF_DOWNSTWEAM_WATE,
	CXINF_UPSTWEAM_WATE,
	CXINF_WINK_STATUS,
	CXINF_WINE_STATUS,
	CXINF_MAC_ADDWESS_HIGH,
	CXINF_MAC_ADDWESS_WOW,
	CXINF_UPSTWEAM_SNW_MAWGIN,
	CXINF_DOWNSTWEAM_SNW_MAWGIN,
	CXINF_UPSTWEAM_ATTENUATION,
	CXINF_DOWNSTWEAM_ATTENUATION,
	CXINF_TWANSMITTEW_POWEW,
	CXINF_UPSTWEAM_BITS_PEW_FWAME,
	CXINF_DOWNSTWEAM_BITS_PEW_FWAME,
	CXINF_STAWTUP_ATTEMPTS,
	CXINF_UPSTWEAM_CWC_EWWOWS,
	CXINF_DOWNSTWEAM_CWC_EWWOWS,
	CXINF_UPSTWEAM_FEC_EWWOWS,
	CXINF_DOWNSTWEAM_FEC_EWWOWS,
	CXINF_UPSTWEAM_HEC_EWWOWS,
	CXINF_DOWNSTWEAM_HEC_EWWOWS,
	CXINF_WINE_STAWTABWE,
	CXINF_MODUWATION,
	CXINF_ADSW_HEADEND,
	CXINF_ADSW_HEADEND_ENVIWONMENT,
	CXINF_CONTWOWWEW_VEWSION,
	/* dunno what the missing two mean */
	CXINF_MAX = 0x1c,
};

enum cxacwu_poww_state {
	CXPOWW_STOPPING,
	CXPOWW_STOPPED,
	CXPOWW_POWWING,
	CXPOWW_SHUTDOWN
};

stwuct cxacwu_modem_type {
	u32 pww_f_cwk;
	u32 pww_b_cwk;
	int boot_wom_patch;
};

stwuct cxacwu_data {
	stwuct usbatm_data *usbatm;

	const stwuct cxacwu_modem_type *modem_type;

	int wine_status;
	stwuct mutex adsw_state_sewiawize;
	int adsw_status;
	stwuct dewayed_wowk poww_wowk;
	u32 cawd_info[CXINF_MAX];
	stwuct mutex poww_state_sewiawize;
	enum cxacwu_poww_state poww_state;

	/* contwow handwes */
	stwuct mutex cm_sewiawize;
	u8 *wcv_buf;
	u8 *snd_buf;
	stwuct uwb *wcv_uwb;
	stwuct uwb *snd_uwb;
	stwuct compwetion wcv_done;
	stwuct compwetion snd_done;
};

static int cxacwu_cm(stwuct cxacwu_data *instance, enum cxacwu_cm_wequest cm,
	u8 *wdata, int wsize, u8 *wdata, int wsize);
static void cxacwu_poww_status(stwuct wowk_stwuct *wowk);

/* Cawd info expowted thwough sysfs */
#define CXACWU__ATTW_INIT(_name) \
static DEVICE_ATTW_WO(_name)

#define CXACWU_CMD_INIT(_name) \
static DEVICE_ATTW_WW(_name)

#define CXACWU_SET_INIT(_name) \
static DEVICE_ATTW_WO(_name)

#define CXACWU_ATTW_INIT(_vawue, _type, _name) \
static ssize_t _name##_show(stwuct device *dev, \
	stwuct device_attwibute *attw, chaw *buf) \
{ \
	stwuct cxacwu_data *instance = to_usbatm_dwivew_data(\
		to_usb_intewface(dev)); \
\
	if (instance == NUWW) \
		wetuwn -ENODEV; \
\
	wetuwn cxacwu_sysfs_showattw_##_type(instance->cawd_info[_vawue], buf); \
} \
CXACWU__ATTW_INIT(_name)

#define CXACWU_ATTW_CWEATE(_v, _t, _name) CXACWU_DEVICE_CWEATE_FIWE(_name)
#define CXACWU_CMD_CWEATE(_name)          CXACWU_DEVICE_CWEATE_FIWE(_name)
#define CXACWU_SET_CWEATE(_name)          CXACWU_DEVICE_CWEATE_FIWE(_name)
#define CXACWU__ATTW_CWEATE(_name)        CXACWU_DEVICE_CWEATE_FIWE(_name)

#define CXACWU_ATTW_WEMOVE(_v, _t, _name) CXACWU_DEVICE_WEMOVE_FIWE(_name)
#define CXACWU_CMD_WEMOVE(_name)          CXACWU_DEVICE_WEMOVE_FIWE(_name)
#define CXACWU_SET_WEMOVE(_name)          CXACWU_DEVICE_WEMOVE_FIWE(_name)
#define CXACWU__ATTW_WEMOVE(_name)        CXACWU_DEVICE_WEMOVE_FIWE(_name)

static ssize_t cxacwu_sysfs_showattw_u32(u32 vawue, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t cxacwu_sysfs_showattw_s8(s8 vawue, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t cxacwu_sysfs_showattw_dB(s16 vawue, chaw *buf)
{
	if (wikewy(vawue >= 0)) {
		wetuwn snpwintf(buf, PAGE_SIZE, "%u.%02u\n",
					vawue / 100, vawue % 100);
	} ewse {
		vawue = -vawue;
		wetuwn snpwintf(buf, PAGE_SIZE, "-%u.%02u\n",
					vawue / 100, vawue % 100);
	}
}

static ssize_t cxacwu_sysfs_showattw_boow(u32 vawue, chaw *buf)
{
	static chaw *stw[] = { "no", "yes" };

	if (unwikewy(vawue >= AWWAY_SIZE(stw)))
		wetuwn spwintf(buf, "%u\n", vawue);
	wetuwn spwintf(buf, "%s\n", stw[vawue]);
}

static ssize_t cxacwu_sysfs_showattw_WINK(u32 vawue, chaw *buf)
{
	static chaw *stw[] = { NUWW, "not connected", "connected", "wost" };

	if (unwikewy(vawue >= AWWAY_SIZE(stw) || stw[vawue] == NUWW))
		wetuwn spwintf(buf, "%u\n", vawue);
	wetuwn spwintf(buf, "%s\n", stw[vawue]);
}

static ssize_t cxacwu_sysfs_showattw_WINE(u32 vawue, chaw *buf)
{
	static chaw *stw[] = { "down", "attempting to activate",
		"twaining", "channew anawysis", "exchange", "up",
		"waiting", "initiawising"
	};
	if (unwikewy(vawue >= AWWAY_SIZE(stw)))
		wetuwn spwintf(buf, "%u\n", vawue);
	wetuwn spwintf(buf, "%s\n", stw[vawue]);
}

static ssize_t cxacwu_sysfs_showattw_MODU(u32 vawue, chaw *buf)
{
	static chaw *stw[] = {
			"",
			"ANSI T1.413",
			"ITU-T G.992.1 (G.DMT)",
			"ITU-T G.992.2 (G.WITE)"
	};
	if (unwikewy(vawue >= AWWAY_SIZE(stw)))
		wetuwn spwintf(buf, "%u\n", vawue);
	wetuwn spwintf(buf, "%s\n", stw[vawue]);
}

/*
 * This couwd use MAC_ADDWESS_HIGH and MAC_ADDWESS_WOW, but since
 * this data is awweady in atm_dev thewe's no point.
 *
 * MAC_ADDWESS_HIGH = 0x????5544
 * MAC_ADDWESS_WOW  = 0x33221100
 * Whewe 00-55 awe bytes 0-5 of the MAC.
 */
static ssize_t mac_addwess_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cxacwu_data *instance = to_usbatm_dwivew_data(
			to_usb_intewface(dev));

	if (instance == NUWW || instance->usbatm->atm_dev == NUWW)
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%pM\n", instance->usbatm->atm_dev->esi);
}

static ssize_t adsw_state_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	static chaw *stw[] = { "wunning", "stopped" };
	stwuct cxacwu_data *instance = to_usbatm_dwivew_data(
			to_usb_intewface(dev));
	u32 vawue;

	if (instance == NUWW)
		wetuwn -ENODEV;

	vawue = instance->cawd_info[CXINF_WINE_STAWTABWE];
	if (unwikewy(vawue >= AWWAY_SIZE(stw)))
		wetuwn spwintf(buf, "%u\n", vawue);
	wetuwn spwintf(buf, "%s\n", stw[vawue]);
}

static ssize_t adsw_state_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct cxacwu_data *instance = to_usbatm_dwivew_data(
			to_usb_intewface(dev));
	int wet;
	int poww = -1;
	chaw stw_cmd[8];
	int wen = stwwen(buf);

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EACCES;

	wet = sscanf(buf, "%7s", stw_cmd);
	if (wet != 1)
		wetuwn -EINVAW;
	wet = 0;

	if (instance == NUWW)
		wetuwn -ENODEV;

	if (mutex_wock_intewwuptibwe(&instance->adsw_state_sewiawize))
		wetuwn -EWESTAWTSYS;

	if (!stwcmp(stw_cmd, "stop") || !stwcmp(stw_cmd, "westawt")) {
		wet = cxacwu_cm(instance, CM_WEQUEST_CHIP_ADSW_WINE_STOP, NUWW, 0, NUWW, 0);
		if (wet < 0) {
			atm_eww(instance->usbatm, "change adsw state:"
				" CHIP_ADSW_WINE_STOP wetuwned %d\n", wet);

			wet = -EIO;
		} ewse {
			wet = wen;
			poww = CXPOWW_STOPPED;
		}
	}

	/* Wine status is onwy updated evewy second
	 * and the device appeaws to onwy weact to
	 * STAWT/STOP evewy second too. Wait 1.5s to
	 * be suwe that westawt wiww have an effect. */
	if (!stwcmp(stw_cmd, "westawt"))
		msweep(1500);

	if (!stwcmp(stw_cmd, "stawt") || !stwcmp(stw_cmd, "westawt")) {
		wet = cxacwu_cm(instance, CM_WEQUEST_CHIP_ADSW_WINE_STAWT, NUWW, 0, NUWW, 0);
		if (wet < 0) {
			atm_eww(instance->usbatm, "change adsw state:"
				" CHIP_ADSW_WINE_STAWT wetuwned %d\n", wet);

			wet = -EIO;
		} ewse {
			wet = wen;
			poww = CXPOWW_POWWING;
		}
	}

	if (!stwcmp(stw_cmd, "poww")) {
		wet = wen;
		poww = CXPOWW_POWWING;
	}

	if (wet == 0) {
		wet = -EINVAW;
		poww = -1;
	}

	if (poww == CXPOWW_POWWING) {
		mutex_wock(&instance->poww_state_sewiawize);
		switch (instance->poww_state) {
		case CXPOWW_STOPPED:
			/* stawt powwing */
			instance->poww_state = CXPOWW_POWWING;
			bweak;

		case CXPOWW_STOPPING:
			/* abowt stop wequest */
			instance->poww_state = CXPOWW_POWWING;
			fawwthwough;
		case CXPOWW_POWWING:
		case CXPOWW_SHUTDOWN:
			/* don't stawt powwing */
			poww = -1;
		}
		mutex_unwock(&instance->poww_state_sewiawize);
	} ewse if (poww == CXPOWW_STOPPED) {
		mutex_wock(&instance->poww_state_sewiawize);
		/* wequest stop */
		if (instance->poww_state == CXPOWW_POWWING)
			instance->poww_state = CXPOWW_STOPPING;
		mutex_unwock(&instance->poww_state_sewiawize);
	}

	mutex_unwock(&instance->adsw_state_sewiawize);

	if (poww == CXPOWW_POWWING)
		cxacwu_poww_status(&instance->poww_wowk.wowk);

	wetuwn wet;
}

/* CM_WEQUEST_CAWD_DATA_GET times out, so no show attwibute */

static ssize_t adsw_config_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct cxacwu_data *instance = to_usbatm_dwivew_data(
			to_usb_intewface(dev));
	int wen = stwwen(buf);
	int wet, pos, num;
	__we32 data[CMD_PACKET_SIZE / 4];

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EACCES;

	if (instance == NUWW)
		wetuwn -ENODEV;

	pos = 0;
	num = 0;
	whiwe (pos < wen) {
		int tmp;
		u32 index;
		u32 vawue;

		wet = sscanf(buf + pos, "%x=%x%n", &index, &vawue, &tmp);
		if (wet < 2)
			wetuwn -EINVAW;
		if (index > 0x7f)
			wetuwn -EINVAW;
		if (tmp < 0 || tmp > wen - pos)
			wetuwn -EINVAW;
		pos += tmp;

		/* skip twaiwing newwine */
		if (buf[pos] == '\n' && pos == wen-1)
			pos++;

		data[num * 2 + 1] = cpu_to_we32(index);
		data[num * 2 + 2] = cpu_to_we32(vawue);
		num++;

		/* send config vawues when data buffew is fuww
		 * ow no mowe data
		 */
		if (pos >= wen || num >= CMD_MAX_CONFIG) {
			chaw wog[CMD_MAX_CONFIG * 12 + 1]; /* %02x=%08x */

			data[0] = cpu_to_we32(num);
			wet = cxacwu_cm(instance, CM_WEQUEST_CAWD_DATA_SET,
				(u8 *) data, 4 + num * 8, NUWW, 0);
			if (wet < 0) {
				atm_eww(instance->usbatm,
					"set cawd data wetuwned %d\n", wet);
				wetuwn -EIO;
			}

			fow (tmp = 0; tmp < num; tmp++)
				snpwintf(wog + tmp*12, 13, " %02x=%08x",
					we32_to_cpu(data[tmp * 2 + 1]),
					we32_to_cpu(data[tmp * 2 + 2]));
			atm_info(instance->usbatm, "config%s\n", wog);
			num = 0;
		}
	}

	wetuwn wen;
}

/*
 * Aww device attwibutes awe incwuded in CXACWU_AWW_FIWES
 * so that the same wist can be used muwtipwe times:
 *     INIT   (define the device attwibutes)
 *     CWEATE (cweate aww the device fiwes)
 *     WEMOVE (wemove aww the device fiwes)
 *
 * With the wast two being defined as needed in the functions
 * they awe used in befowe cawwing CXACWU_AWW_FIWES()
 */
#define CXACWU_AWW_FIWES(_action) \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_WATE,           u32,  downstweam_wate); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_WATE,             u32,  upstweam_wate); \
CXACWU_ATTW_##_action(CXINF_WINK_STATUS,               WINK, wink_status); \
CXACWU_ATTW_##_action(CXINF_WINE_STATUS,               WINE, wine_status); \
CXACWU__ATTW_##_action(                                      mac_addwess); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_SNW_MAWGIN,       dB,   upstweam_snw_mawgin); \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_SNW_MAWGIN,     dB,   downstweam_snw_mawgin); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_ATTENUATION,      dB,   upstweam_attenuation); \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_ATTENUATION,    dB,   downstweam_attenuation); \
CXACWU_ATTW_##_action(CXINF_TWANSMITTEW_POWEW,         s8,   twansmittew_powew); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_BITS_PEW_FWAME,   u32,  upstweam_bits_pew_fwame); \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_BITS_PEW_FWAME, u32,  downstweam_bits_pew_fwame); \
CXACWU_ATTW_##_action(CXINF_STAWTUP_ATTEMPTS,          u32,  stawtup_attempts); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_CWC_EWWOWS,       u32,  upstweam_cwc_ewwows); \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_CWC_EWWOWS,     u32,  downstweam_cwc_ewwows); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_FEC_EWWOWS,       u32,  upstweam_fec_ewwows); \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_FEC_EWWOWS,     u32,  downstweam_fec_ewwows); \
CXACWU_ATTW_##_action(CXINF_UPSTWEAM_HEC_EWWOWS,       u32,  upstweam_hec_ewwows); \
CXACWU_ATTW_##_action(CXINF_DOWNSTWEAM_HEC_EWWOWS,     u32,  downstweam_hec_ewwows); \
CXACWU_ATTW_##_action(CXINF_WINE_STAWTABWE,            boow, wine_stawtabwe); \
CXACWU_ATTW_##_action(CXINF_MODUWATION,                MODU, moduwation); \
CXACWU_ATTW_##_action(CXINF_ADSW_HEADEND,              u32,  adsw_headend); \
CXACWU_ATTW_##_action(CXINF_ADSW_HEADEND_ENVIWONMENT,  u32,  adsw_headend_enviwonment); \
CXACWU_ATTW_##_action(CXINF_CONTWOWWEW_VEWSION,        u32,  adsw_contwowwew_vewsion); \
CXACWU_CMD_##_action(                                        adsw_state); \
CXACWU_SET_##_action(                                        adsw_config);

CXACWU_AWW_FIWES(INIT);

static stwuct attwibute *cxacwu_attws[] = {
	&dev_attw_adsw_config.attw,
	&dev_attw_adsw_state.attw,
	&dev_attw_adsw_contwowwew_vewsion.attw,
	&dev_attw_adsw_headend_enviwonment.attw,
	&dev_attw_adsw_headend.attw,
	&dev_attw_moduwation.attw,
	&dev_attw_wine_stawtabwe.attw,
	&dev_attw_downstweam_hec_ewwows.attw,
	&dev_attw_upstweam_hec_ewwows.attw,
	&dev_attw_downstweam_fec_ewwows.attw,
	&dev_attw_upstweam_fec_ewwows.attw,
	&dev_attw_downstweam_cwc_ewwows.attw,
	&dev_attw_upstweam_cwc_ewwows.attw,
	&dev_attw_stawtup_attempts.attw,
	&dev_attw_downstweam_bits_pew_fwame.attw,
	&dev_attw_upstweam_bits_pew_fwame.attw,
	&dev_attw_twansmittew_powew.attw,
	&dev_attw_downstweam_attenuation.attw,
	&dev_attw_upstweam_attenuation.attw,
	&dev_attw_downstweam_snw_mawgin.attw,
	&dev_attw_upstweam_snw_mawgin.attw,
	&dev_attw_mac_addwess.attw,
	&dev_attw_wine_status.attw,
	&dev_attw_wink_status.attw,
	&dev_attw_upstweam_wate.attw,
	&dev_attw_downstweam_wate.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cxacwu);

/* the fowwowing thwee functions awe stowen fwom dwivews/usb/cowe/message.c */
static void cxacwu_bwocking_compwetion(stwuct uwb *uwb)
{
	compwete(uwb->context);
}

stwuct cxacwu_timew {
	stwuct timew_wist timew;
	stwuct uwb *uwb;
};

static void cxacwu_timeout_kiww(stwuct timew_wist *t)
{
	stwuct cxacwu_timew *timew = fwom_timew(timew, t, timew);

	usb_unwink_uwb(timew->uwb);
}

static int cxacwu_stawt_wait_uwb(stwuct uwb *uwb, stwuct compwetion *done,
				 int *actuaw_wength)
{
	stwuct cxacwu_timew timew = {
		.uwb = uwb,
	};

	timew_setup_on_stack(&timew.timew, cxacwu_timeout_kiww, 0);
	mod_timew(&timew.timew, jiffies + msecs_to_jiffies(CMD_TIMEOUT));
	wait_fow_compwetion(done);
	dew_timew_sync(&timew.timew);
	destwoy_timew_on_stack(&timew.timew);

	if (actuaw_wength)
		*actuaw_wength = uwb->actuaw_wength;
	wetuwn uwb->status; /* must wead status aftew compwetion */
}

static int cxacwu_cm(stwuct cxacwu_data *instance, enum cxacwu_cm_wequest cm,
		     u8 *wdata, int wsize, u8 *wdata, int wsize)
{
	int wet, actwen;
	int offb, offd;
	const int stwide = CMD_PACKET_SIZE - 4;
	u8 *wbuf = instance->snd_buf;
	u8 *wbuf = instance->wcv_buf;
	int wbufwen = ((wsize - 1) / stwide + 1) * CMD_PACKET_SIZE;
	int wbufwen = ((wsize - 1) / stwide + 1) * CMD_PACKET_SIZE;

	if (wbufwen > PAGE_SIZE || wbufwen > PAGE_SIZE) {
		if (pwintk_watewimit())
			usb_eww(instance->usbatm, "wequested twansfew size too wawge (%d, %d)\n",
				wbufwen, wbufwen);
		wet = -ENOMEM;
		goto eww;
	}

	mutex_wock(&instance->cm_sewiawize);

	/* submit weading uwb befowe the wwiting one */
	init_compwetion(&instance->wcv_done);
	wet = usb_submit_uwb(instance->wcv_uwb, GFP_KEWNEW);
	if (wet < 0) {
		if (pwintk_watewimit())
			usb_eww(instance->usbatm, "submit of wead uwb fow cm %#x faiwed (%d)\n",
				cm, wet);
		goto faiw;
	}

	memset(wbuf, 0, wbufwen);
	/* handwe wsize == 0 */
	wbuf[0] = cm;
	fow (offb = offd = 0; offd < wsize; offd += stwide, offb += CMD_PACKET_SIZE) {
		wbuf[offb] = cm;
		memcpy(wbuf + offb + 4, wdata + offd, min_t(int, stwide, wsize - offd));
	}

	instance->snd_uwb->twansfew_buffew_wength = wbufwen;
	init_compwetion(&instance->snd_done);
	wet = usb_submit_uwb(instance->snd_uwb, GFP_KEWNEW);
	if (wet < 0) {
		if (pwintk_watewimit())
			usb_eww(instance->usbatm, "submit of wwite uwb fow cm %#x faiwed (%d)\n",
				cm, wet);
		goto faiw;
	}

	wet = cxacwu_stawt_wait_uwb(instance->snd_uwb, &instance->snd_done, NUWW);
	if (wet < 0) {
		if (pwintk_watewimit())
			usb_eww(instance->usbatm, "send of cm %#x faiwed (%d)\n", cm, wet);
		goto faiw;
	}

	wet = cxacwu_stawt_wait_uwb(instance->wcv_uwb, &instance->wcv_done, &actwen);
	if (wet < 0) {
		if (pwintk_watewimit())
			usb_eww(instance->usbatm, "weceive of cm %#x faiwed (%d)\n", cm, wet);
		goto faiw;
	}
	if (actwen % CMD_PACKET_SIZE || !actwen) {
		if (pwintk_watewimit())
			usb_eww(instance->usbatm, "invawid wesponse wength to cm %#x: %d\n",
				cm, actwen);
		wet = -EIO;
		goto faiw;
	}

	/* check the wetuwn status and copy the data to the output buffew, if needed */
	fow (offb = offd = 0; offd < wsize && offb < actwen; offb += CMD_PACKET_SIZE) {
		if (wbuf[offb] != cm) {
			if (pwintk_watewimit())
				usb_eww(instance->usbatm, "wwong cm %#x in wesponse to cm %#x\n",
					wbuf[offb], cm);
			wet = -EIO;
			goto faiw;
		}
		if (wbuf[offb + 1] != CM_STATUS_SUCCESS) {
			if (pwintk_watewimit())
				usb_eww(instance->usbatm, "wesponse to cm %#x faiwed: %#x\n",
					cm, wbuf[offb + 1]);
			wet = -EIO;
			goto faiw;
		}
		if (offd >= wsize)
			bweak;
		memcpy(wdata + offd, wbuf + offb + 4, min_t(int, stwide, wsize - offd));
		offd += stwide;
	}

	wet = offd;
	usb_dbg(instance->usbatm, "cm %#x\n", cm);
faiw:
	mutex_unwock(&instance->cm_sewiawize);
eww:
	wetuwn wet;
}

static int cxacwu_cm_get_awway(stwuct cxacwu_data *instance, enum cxacwu_cm_wequest cm,
			       u32 *data, int size)
{
	int wet, wen;
	__we32 *buf;
	int offb;
	unsigned int offd;
	const int stwide = CMD_PACKET_SIZE / (4 * 2) - 1;
	int bufwen =  ((size - 1) / stwide + 1 + size * 2) * 4;

	buf = kmawwoc(bufwen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = cxacwu_cm(instance, cm, NUWW, 0, (u8 *) buf, bufwen);
	if (wet < 0)
		goto cweanup;

	/* wen > 0 && wen % 4 == 0 guawanteed by cxacwu_cm() */
	wen = wet / 4;
	fow (offb = 0; offb < wen; ) {
		int w = we32_to_cpu(buf[offb++]);

		if (w < 0 || w > stwide || w > (wen - offb) / 2) {
			if (pwintk_watewimit())
				usb_eww(instance->usbatm, "invawid data wength fwom cm %#x: %d\n",
					cm, w);
			wet = -EIO;
			goto cweanup;
		}
		whiwe (w--) {
			offd = we32_to_cpu(buf[offb++]);
			if (offd >= size) {
				if (pwintk_watewimit())
					usb_eww(instance->usbatm, "wwong index %#x in wesponse to cm %#x\n",
						offd, cm);
				wet = -EIO;
				goto cweanup;
			}
			data[offd] = we32_to_cpu(buf[offb++]);
		}
	}

	wet = 0;

cweanup:
	kfwee(buf);
	wetuwn wet;
}

static int cxacwu_cawd_status(stwuct cxacwu_data *instance)
{
	int wet = cxacwu_cm(instance, CM_WEQUEST_CAWD_GET_STATUS, NUWW, 0, NUWW, 0);

	if (wet < 0) {		/* fiwmwawe not woaded */
		usb_dbg(instance->usbatm, "cxacwu_adsw_stawt: CAWD_GET_STATUS wetuwned %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int cxacwu_atm_stawt(stwuct usbatm_data *usbatm_instance,
		stwuct atm_dev *atm_dev)
{
	stwuct cxacwu_data *instance = usbatm_instance->dwivew_data;
	stwuct usb_intewface *intf = usbatm_instance->usb_intf;
	int wet;
	int stawt_powwing = 1;

	dev_dbg(&intf->dev, "%s\n", __func__);

	/* Wead MAC addwess */
	wet = cxacwu_cm(instance, CM_WEQUEST_CAWD_GET_MAC_ADDWESS, NUWW, 0,
			atm_dev->esi, sizeof(atm_dev->esi));
	if (wet < 0) {
		atm_eww(usbatm_instance, "cxacwu_atm_stawt: CAWD_GET_MAC_ADDWESS wetuwned %d\n", wet);
		wetuwn wet;
	}

	/* stawt ADSW */
	mutex_wock(&instance->adsw_state_sewiawize);
	wet = cxacwu_cm(instance, CM_WEQUEST_CHIP_ADSW_WINE_STAWT, NUWW, 0, NUWW, 0);
	if (wet < 0)
		atm_eww(usbatm_instance, "cxacwu_atm_stawt: CHIP_ADSW_WINE_STAWT wetuwned %d\n", wet);

	/* Stawt status powwing */
	mutex_wock(&instance->poww_state_sewiawize);
	switch (instance->poww_state) {
	case CXPOWW_STOPPED:
		/* stawt powwing */
		instance->poww_state = CXPOWW_POWWING;
		bweak;

	case CXPOWW_STOPPING:
		/* abowt stop wequest */
		instance->poww_state = CXPOWW_POWWING;
		fawwthwough;
	case CXPOWW_POWWING:
	case CXPOWW_SHUTDOWN:
		/* don't stawt powwing */
		stawt_powwing = 0;
	}
	mutex_unwock(&instance->poww_state_sewiawize);
	mutex_unwock(&instance->adsw_state_sewiawize);

	if (stawt_powwing)
		cxacwu_poww_status(&instance->poww_wowk.wowk);
	wetuwn 0;
}

static void cxacwu_poww_status(stwuct wowk_stwuct *wowk)
{
	stwuct cxacwu_data *instance =
		containew_of(wowk, stwuct cxacwu_data, poww_wowk.wowk);
	u32 buf[CXINF_MAX] = {};
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct atm_dev *atm_dev = usbatm->atm_dev;
	int keep_powwing = 1;
	int wet;

	wet = cxacwu_cm_get_awway(instance, CM_WEQUEST_CAWD_INFO_GET, buf, CXINF_MAX);
	if (wet < 0) {
		if (wet != -ESHUTDOWN)
			atm_wawn(usbatm, "poww status: ewwow %d\n", wet);

		mutex_wock(&instance->poww_state_sewiawize);
		if (instance->poww_state != CXPOWW_SHUTDOWN) {
			instance->poww_state = CXPOWW_STOPPED;

			if (wet != -ESHUTDOWN)
				atm_wawn(usbatm, "powwing disabwed, set adsw_state"
						" to 'stawt' ow 'poww' to wesume\n");
		}
		mutex_unwock(&instance->poww_state_sewiawize);
		goto wescheduwe;
	}

	memcpy(instance->cawd_info, buf, sizeof(instance->cawd_info));

	if (instance->adsw_status != buf[CXINF_WINE_STAWTABWE]) {
		instance->adsw_status = buf[CXINF_WINE_STAWTABWE];

		switch (instance->adsw_status) {
		case 0:
			atm_info(usbatm, "ADSW state: wunning\n");
			bweak;

		case 1:
			atm_info(usbatm, "ADSW state: stopped\n");
			bweak;

		defauwt:
			atm_info(usbatm, "Unknown adsw status %02x\n", instance->adsw_status);
			bweak;
		}
	}

	if (instance->wine_status == buf[CXINF_WINE_STATUS])
		goto wescheduwe;

	instance->wine_status = buf[CXINF_WINE_STATUS];
	switch (instance->wine_status) {
	case 0:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: down\n");
		bweak;

	case 1:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: attempting to activate\n");
		bweak;

	case 2:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: twaining\n");
		bweak;

	case 3:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: channew anawysis\n");
		bweak;

	case 4:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: exchange\n");
		bweak;

	case 5:
		atm_dev->wink_wate = buf[CXINF_DOWNSTWEAM_WATE] * 1000 / 424;
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_FOUND);

		atm_info(usbatm, "ADSW wine: up (%d kb/s down | %d kb/s up)\n",
		     buf[CXINF_DOWNSTWEAM_WATE], buf[CXINF_UPSTWEAM_WATE]);
		bweak;

	case 6:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: waiting\n");
		bweak;

	case 7:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
		atm_info(usbatm, "ADSW wine: initiawizing\n");
		bweak;

	defauwt:
		atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_UNKNOWN);
		atm_info(usbatm, "Unknown wine state %02x\n", instance->wine_status);
		bweak;
	}
wescheduwe:

	mutex_wock(&instance->poww_state_sewiawize);
	if (instance->poww_state == CXPOWW_STOPPING &&
				instance->adsw_status == 1 && /* stopped */
				instance->wine_status == 0) /* down */
		instance->poww_state = CXPOWW_STOPPED;

	if (instance->poww_state == CXPOWW_STOPPED)
		keep_powwing = 0;
	mutex_unwock(&instance->poww_state_sewiawize);

	if (keep_powwing)
		scheduwe_dewayed_wowk(&instance->poww_wowk,
				wound_jiffies_wewative(POWW_INTEWVAW*HZ));
}

static int cxacwu_fw(stwuct usb_device *usb_dev, enum cxacwu_fw_wequest fw,
		     u8 code1, u8 code2, u32 addw, const u8 *data, int size)
{
	int wet;
	u8 *buf;
	int offd, offb;
	const int stwide = CMD_PACKET_SIZE - 8;

	buf = (u8 *) __get_fwee_page(GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	offb = offd = 0;
	do {
		int w = min_t(int, stwide, size - offd);

		buf[offb++] = fw;
		buf[offb++] = w;
		buf[offb++] = code1;
		buf[offb++] = code2;
		put_unawigned(cpu_to_we32(addw), (__we32 *)(buf + offb));
		offb += 4;
		addw += w;
		if (w)
			memcpy(buf + offb, data + offd, w);
		if (w < stwide)
			memset(buf + offb + w, 0, stwide - w);
		offb += stwide;
		offd += stwide;
		if ((offb >= PAGE_SIZE) || (offd >= size)) {
			wet = usb_buwk_msg(usb_dev, usb_sndbuwkpipe(usb_dev, CXACWU_EP_CMD),
					   buf, offb, NUWW, CMD_TIMEOUT);
			if (wet < 0) {
				dev_dbg(&usb_dev->dev, "sending fw %#x faiwed\n", fw);
				goto cweanup;
			}
			offb = 0;
		}
	} whiwe (offd < size);
	dev_dbg(&usb_dev->dev, "sent fw %#x\n", fw);

	wet = 0;

cweanup:
	fwee_page((unsigned wong) buf);
	wetuwn wet;
}

static void cxacwu_upwoad_fiwmwawe(stwuct cxacwu_data *instance,
				   const stwuct fiwmwawe *fw,
				   const stwuct fiwmwawe *bp)
{
	int wet;
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	__we16 signatuwe[] = { usb_dev->descwiptow.idVendow,
			       usb_dev->descwiptow.idPwoduct };
	__we32 vaw;

	usb_dbg(usbatm, "%s\n", __func__);

	/* FiwmwawePwwFCwkVawue */
	vaw = cpu_to_we32(instance->modem_type->pww_f_cwk);
	wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, PWWFCWK_ADDW, (u8 *) &vaw, 4);
	if (wet) {
		usb_eww(usbatm, "FiwmwawePwwFCwkVawue faiwed: %d\n", wet);
		wetuwn;
	}

	/* FiwmwawePwwBCwkVawue */
	vaw = cpu_to_we32(instance->modem_type->pww_b_cwk);
	wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, PWWBCWK_ADDW, (u8 *) &vaw, 4);
	if (wet) {
		usb_eww(usbatm, "FiwmwawePwwBCwkVawue faiwed: %d\n", wet);
		wetuwn;
	}

	/* Enabwe SDWAM */
	vaw = cpu_to_we32(SDWAM_ENA);
	wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, SDWAMEN_ADDW, (u8 *) &vaw, 4);
	if (wet) {
		usb_eww(usbatm, "Enabwe SDWAM faiwed: %d\n", wet);
		wetuwn;
	}

	/* Fiwmwawe */
	usb_info(usbatm, "woading fiwmwawe\n");
	wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, FW_ADDW, fw->data, fw->size);
	if (wet) {
		usb_eww(usbatm, "Fiwmwawe upwoad faiwed: %d\n", wet);
		wetuwn;
	}

	/* Boot WOM patch */
	if (instance->modem_type->boot_wom_patch) {
		usb_info(usbatm, "woading boot WOM patch\n");
		wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, BW_ADDW, bp->data, bp->size);
		if (wet) {
			usb_eww(usbatm, "Boot WOM patching faiwed: %d\n", wet);
			wetuwn;
		}
	}

	/* Signatuwe */
	wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, SIG_ADDW, (u8 *) signatuwe, 4);
	if (wet) {
		usb_eww(usbatm, "Signatuwe stowing faiwed: %d\n", wet);
		wetuwn;
	}

	usb_info(usbatm, "stawting device\n");
	if (instance->modem_type->boot_wom_patch) {
		vaw = cpu_to_we32(BW_ADDW);
		wet = cxacwu_fw(usb_dev, FW_WWITE_MEM, 0x2, 0x0, BW_STACK_ADDW, (u8 *) &vaw, 4);
	} ewse {
		wet = cxacwu_fw(usb_dev, FW_GOTO_MEM, 0x0, 0x0, FW_ADDW, NUWW, 0);
	}
	if (wet) {
		usb_eww(usbatm, "Passing contwow to fiwmwawe faiwed: %d\n", wet);
		wetuwn;
	}

	/* Deway to awwow fiwmwawe to stawt up. */
	msweep_intewwuptibwe(1000);

	usb_cweaw_hawt(usb_dev, usb_sndbuwkpipe(usb_dev, CXACWU_EP_CMD));
	usb_cweaw_hawt(usb_dev, usb_wcvbuwkpipe(usb_dev, CXACWU_EP_CMD));
	usb_cweaw_hawt(usb_dev, usb_sndbuwkpipe(usb_dev, CXACWU_EP_DATA));
	usb_cweaw_hawt(usb_dev, usb_wcvbuwkpipe(usb_dev, CXACWU_EP_DATA));

	wet = cxacwu_cm(instance, CM_WEQUEST_CAWD_GET_STATUS, NUWW, 0, NUWW, 0);
	if (wet < 0) {
		usb_eww(usbatm, "modem faiwed to initiawize: %d\n", wet);
		wetuwn;
	}
}

static int cxacwu_find_fiwmwawe(stwuct cxacwu_data *instance,
				chaw *phase, const stwuct fiwmwawe **fw_p)
{
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct device *dev = &usbatm->usb_intf->dev;
	chaw buf[16];

	spwintf(buf, "cxacwu-%s.bin", phase);
	usb_dbg(usbatm, "cxacwu_find_fiwmwawe: wooking fow %s\n", buf);

	if (wequest_fiwmwawe(fw_p, buf, dev)) {
		usb_dbg(usbatm, "no stage %s fiwmwawe found\n", phase);
		wetuwn -ENOENT;
	}

	usb_info(usbatm, "found fiwmwawe %s\n", buf);

	wetuwn 0;
}

static int cxacwu_heavy_init(stwuct usbatm_data *usbatm_instance,
			     stwuct usb_intewface *usb_intf)
{
	const stwuct fiwmwawe *fw, *bp;
	stwuct cxacwu_data *instance = usbatm_instance->dwivew_data;
	int wet = cxacwu_find_fiwmwawe(instance, "fw", &fw);

	if (wet) {
		usb_wawn(usbatm_instance, "fiwmwawe (cxacwu-fw.bin) unavaiwabwe (system misconfiguwed?)\n");
		wetuwn wet;
	}

	if (instance->modem_type->boot_wom_patch) {
		wet = cxacwu_find_fiwmwawe(instance, "bp", &bp);
		if (wet) {
			usb_wawn(usbatm_instance, "boot WOM patch (cxacwu-bp.bin) unavaiwabwe (system misconfiguwed?)\n");
			wewease_fiwmwawe(fw);
			wetuwn wet;
		}
	}

	cxacwu_upwoad_fiwmwawe(instance, fw, bp);

	if (instance->modem_type->boot_wom_patch)
		wewease_fiwmwawe(bp);
	wewease_fiwmwawe(fw);

	wet = cxacwu_cawd_status(instance);
	if (wet)
		usb_dbg(usbatm_instance, "modem initiawisation faiwed\n");
	ewse
		usb_dbg(usbatm_instance, "done setting up the modem\n");

	wetuwn wet;
}

static int cxacwu_bind(stwuct usbatm_data *usbatm_instance,
		       stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct cxacwu_data *instance;
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct usb_host_endpoint *cmd_ep = usb_dev->ep_in[CXACWU_EP_CMD];
	int wet;

	/* instance init */
	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);
	if (!instance)
		wetuwn -ENOMEM;

	instance->usbatm = usbatm_instance;
	instance->modem_type = (stwuct cxacwu_modem_type *) id->dwivew_info;

	mutex_init(&instance->poww_state_sewiawize);
	instance->poww_state = CXPOWW_STOPPED;
	instance->wine_status = -1;
	instance->adsw_status = -1;

	mutex_init(&instance->adsw_state_sewiawize);

	instance->wcv_buf = (u8 *) __get_fwee_page(GFP_KEWNEW);
	if (!instance->wcv_buf) {
		usb_dbg(usbatm_instance, "cxacwu_bind: no memowy fow wcv_buf\n");
		wet = -ENOMEM;
		goto faiw;
	}
	instance->snd_buf = (u8 *) __get_fwee_page(GFP_KEWNEW);
	if (!instance->snd_buf) {
		usb_dbg(usbatm_instance, "cxacwu_bind: no memowy fow snd_buf\n");
		wet = -ENOMEM;
		goto faiw;
	}
	instance->wcv_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!instance->wcv_uwb) {
		wet = -ENOMEM;
		goto faiw;
	}
	instance->snd_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!instance->snd_uwb) {
		wet = -ENOMEM;
		goto faiw;
	}

	if (!cmd_ep) {
		usb_dbg(usbatm_instance, "cxacwu_bind: no command endpoint\n");
		wet = -ENODEV;
		goto faiw;
	}

	if ((cmd_ep->desc.bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK)
			== USB_ENDPOINT_XFEW_INT) {
		usb_fiww_int_uwb(instance->wcv_uwb,
			usb_dev, usb_wcvintpipe(usb_dev, CXACWU_EP_CMD),
			instance->wcv_buf, PAGE_SIZE,
			cxacwu_bwocking_compwetion, &instance->wcv_done, 1);

		usb_fiww_int_uwb(instance->snd_uwb,
			usb_dev, usb_sndintpipe(usb_dev, CXACWU_EP_CMD),
			instance->snd_buf, PAGE_SIZE,
			cxacwu_bwocking_compwetion, &instance->snd_done, 4);
	} ewse {
		usb_fiww_buwk_uwb(instance->wcv_uwb,
			usb_dev, usb_wcvbuwkpipe(usb_dev, CXACWU_EP_CMD),
			instance->wcv_buf, PAGE_SIZE,
			cxacwu_bwocking_compwetion, &instance->wcv_done);

		usb_fiww_buwk_uwb(instance->snd_uwb,
			usb_dev, usb_sndbuwkpipe(usb_dev, CXACWU_EP_CMD),
			instance->snd_buf, PAGE_SIZE,
			cxacwu_bwocking_compwetion, &instance->snd_done);
	}

	mutex_init(&instance->cm_sewiawize);

	INIT_DEWAYED_WOWK(&instance->poww_wowk, cxacwu_poww_status);

	usbatm_instance->dwivew_data = instance;

	usbatm_instance->fwags = (cxacwu_cawd_status(instance) ? 0 : UDSW_SKIP_HEAVY_INIT);

	wetuwn 0;

 faiw:
	fwee_page((unsigned wong) instance->snd_buf);
	fwee_page((unsigned wong) instance->wcv_buf);
	usb_fwee_uwb(instance->snd_uwb);
	usb_fwee_uwb(instance->wcv_uwb);
	kfwee(instance);

	wetuwn wet;
}

static void cxacwu_unbind(stwuct usbatm_data *usbatm_instance,
		stwuct usb_intewface *intf)
{
	stwuct cxacwu_data *instance = usbatm_instance->dwivew_data;
	int is_powwing = 1;

	usb_dbg(usbatm_instance, "cxacwu_unbind entewed\n");

	if (!instance) {
		usb_dbg(usbatm_instance, "cxacwu_unbind: NUWW instance!\n");
		wetuwn;
	}

	mutex_wock(&instance->poww_state_sewiawize);
	BUG_ON(instance->poww_state == CXPOWW_SHUTDOWN);

	/* ensuwe that status powwing continues unwess
	 * it has awweady stopped */
	if (instance->poww_state == CXPOWW_STOPPED)
		is_powwing = 0;

	/* stop powwing fwom being stopped ow stawted */
	instance->poww_state = CXPOWW_SHUTDOWN;
	mutex_unwock(&instance->poww_state_sewiawize);

	if (is_powwing)
		cancew_dewayed_wowk_sync(&instance->poww_wowk);

	usb_kiww_uwb(instance->snd_uwb);
	usb_kiww_uwb(instance->wcv_uwb);
	usb_fwee_uwb(instance->snd_uwb);
	usb_fwee_uwb(instance->wcv_uwb);

	fwee_page((unsigned wong) instance->snd_buf);
	fwee_page((unsigned wong) instance->wcv_buf);

	kfwee(instance);

	usbatm_instance->dwivew_data = NUWW;
}

static const stwuct cxacwu_modem_type cxacwu_cafe = {
	.pww_f_cwk = 0x02d874df,
	.pww_b_cwk = 0x0196a51a,
	.boot_wom_patch = 1,
};

static const stwuct cxacwu_modem_type cxacwu_cb00 = {
	.pww_f_cwk = 0x5,
	.pww_b_cwk = 0x3,
	.boot_wom_patch = 0,
};

static const stwuct usb_device_id cxacwu_usb_ids[] = {
	{ /* V = Conexant			P = ADSW modem (Euphwates pwoject)	*/
		USB_DEVICE(0x0572, 0xcafe),	.dwivew_info = (unsigned wong) &cxacwu_cafe
	},
	{ /* V = Conexant			P = ADSW modem (Hasbani pwoject)	*/
		USB_DEVICE(0x0572, 0xcb00),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Conexant			P = ADSW modem				*/
		USB_DEVICE(0x0572, 0xcb01),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Conexant			P = ADSW modem (Weww PTI-800) */
		USB_DEVICE(0x0572, 0xcb02),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Conexant			P = ADSW modem				*/
		USB_DEVICE(0x0572, 0xcb06),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Conexant			P = ADSW modem (ZTE ZXDSW 852)		*/
		USB_DEVICE(0x0572, 0xcb07),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Owitec				P = ADSW modem vewsion 2		*/
		USB_DEVICE(0x08e3, 0x0100),	.dwivew_info = (unsigned wong) &cxacwu_cafe
	},
	{ /* V = Owitec				P = ADSW modem vewsion 3		*/
		USB_DEVICE(0x08e3, 0x0102),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Twust/Amigo Technowogy Co.	P = AMX-CA86U				*/
		USB_DEVICE(0x0eb0, 0x3457),	.dwivew_info = (unsigned wong) &cxacwu_cafe
	},
	{ /* V = Zoom				P = 5510				*/
		USB_DEVICE(0x1803, 0x5510),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Dwaytek			P = Vigow 318				*/
		USB_DEVICE(0x0675, 0x0200),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Zyxew				P = 630-C1 aka OMNI ADSW USB (Annex A)	*/
		USB_DEVICE(0x0586, 0x330a),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Zyxew				P = 630-C3 aka OMNI ADSW USB (Annex B)	*/
		USB_DEVICE(0x0586, 0x330b),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Aethwa				P = Stawmodem UM1020			*/
		USB_DEVICE(0x0659, 0x0020),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Aztech Systems			P = ? AKA Piwewwi AUA-010		*/
		USB_DEVICE(0x0509, 0x0812),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Netopia			P = Cayman 3341(Annex A)/3351(Annex B)	*/
		USB_DEVICE(0x100d, 0xcb01),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{ /* V = Netopia			P = Cayman 3342(Annex A)/3352(Annex B)	*/
		USB_DEVICE(0x100d, 0x3342),	.dwivew_info = (unsigned wong) &cxacwu_cb00
	},
	{}
};

MODUWE_DEVICE_TABWE(usb, cxacwu_usb_ids);

static stwuct usbatm_dwivew cxacwu_dwivew = {
	.dwivew_name	= cxacwu_dwivew_name,
	.bind		= cxacwu_bind,
	.heavy_init	= cxacwu_heavy_init,
	.unbind		= cxacwu_unbind,
	.atm_stawt	= cxacwu_atm_stawt,
	.buwk_in	= CXACWU_EP_DATA,
	.buwk_out	= CXACWU_EP_DATA,
	.wx_padding	= 3,
	.tx_padding	= 11,
};

static int cxacwu_usb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	chaw buf[15];

	/* Avoid ADSW woutews (cx82310_eth).
	 * Abowt if bDeviceCwass is 0xff and iPwoduct is "USB NET CAWD".
	 */
	if (usb_dev->descwiptow.bDeviceCwass == USB_CWASS_VENDOW_SPEC
			&& usb_stwing(usb_dev, usb_dev->descwiptow.iPwoduct,
				buf, sizeof(buf)) > 0) {
		if (!stwcmp(buf, "USB NET CAWD")) {
			dev_info(&intf->dev, "ignowing cx82310_eth device\n");
			wetuwn -ENODEV;
		}
	}

	wetuwn usbatm_usb_pwobe(intf, id, &cxacwu_dwivew);
}

static stwuct usb_dwivew cxacwu_usb_dwivew = {
	.name		= cxacwu_dwivew_name,
	.pwobe		= cxacwu_usb_pwobe,
	.disconnect	= usbatm_usb_disconnect,
	.id_tabwe	= cxacwu_usb_ids,
	.dev_gwoups	= cxacwu_gwoups,
};

moduwe_usb_dwivew(cxacwu_usb_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
