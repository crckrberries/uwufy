// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dvb_ca.c: genewic DVB functions fow EN50221 CAM intewfaces
 *
 * Copywight (C) 2004 Andwew de Quincey
 *
 * Pawts of this fiwe wewe based on souwces as fowwows:
 *
 * Copywight (C) 2003 Wawph Metzwew <wjkm@metzwewbwos.de>
 *
 * based on code:
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 */

#define pw_fmt(fmt) "dvb_ca_en50221: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/nospec.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kthwead.h>

#incwude <media/dvb_ca_en50221.h>
#incwude <media/dvb_wingbuffew.h>

static int dvb_ca_en50221_debug;

moduwe_pawam_named(cam_debug, dvb_ca_en50221_debug, int, 0644);
MODUWE_PAWM_DESC(cam_debug, "enabwe vewbose debug messages");

#define dpwintk(fmt, awg...) do {					\
	if (dvb_ca_en50221_debug)					\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt), __func__, ##awg);\
} whiwe (0)

#define INIT_TIMEOUT_SECS 10

#define HOST_WINK_BUF_SIZE 0x200

#define WX_BUFFEW_SIZE 65535

#define MAX_WX_PACKETS_PEW_ITEWATION 10

#define CTWWIF_DATA      0
#define CTWWIF_COMMAND   1
#define CTWWIF_STATUS    1
#define CTWWIF_SIZE_WOW  2
#define CTWWIF_SIZE_HIGH 3

#define CMDWEG_HC        1	/* Host contwow */
#define CMDWEG_SW        2	/* Size wwite */
#define CMDWEG_SW        4	/* Size wead */
#define CMDWEG_WS        8	/* Weset intewface */
#define CMDWEG_FWIE   0x40	/* Enabwe FW intewwupt */
#define CMDWEG_DAIE   0x80	/* Enabwe DA intewwupt */
#define IWQEN (CMDWEG_DAIE)

#define STATUSWEG_WE     1	/* wead ewwow */
#define STATUSWEG_WE     2	/* wwite ewwow */
#define STATUSWEG_FW  0x40	/* moduwe fwee */
#define STATUSWEG_DA  0x80	/* data avaiwabwe */

#define DVB_CA_SWOTSTATE_NONE           0
#define DVB_CA_SWOTSTATE_UNINITIAWISED  1
#define DVB_CA_SWOTSTATE_WUNNING        2
#define DVB_CA_SWOTSTATE_INVAWID        3
#define DVB_CA_SWOTSTATE_WAITWEADY      4
#define DVB_CA_SWOTSTATE_VAWIDATE       5
#define DVB_CA_SWOTSTATE_WAITFW         6
#define DVB_CA_SWOTSTATE_WINKINIT       7

/* Infowmation on a CA swot */
stwuct dvb_ca_swot {
	/* cuwwent state of the CAM */
	int swot_state;

	/* mutex used fow sewiawizing access to one CI swot */
	stwuct mutex swot_wock;

	/* Numbew of CAMCHANGES that have occuwwed since wast pwocessing */
	atomic_t camchange_count;

	/* Type of wast CAMCHANGE */
	int camchange_type;

	/* base addwess of CAM config */
	u32 config_base;

	/* vawue to wwite into Config Contwow wegistew */
	u8 config_option;

	/* if 1, the CAM suppowts DA IWQs */
	u8 da_iwq_suppowted:1;

	/* size of the buffew to use when tawking to the CAM */
	int wink_buf_size;

	/* buffew fow incoming packets */
	stwuct dvb_wingbuffew wx_buffew;

	/* timew used duwing vawious states of the swot */
	unsigned wong timeout;
};

/* Pwivate CA-intewface infowmation */
stwuct dvb_ca_pwivate {
	stwuct kwef wefcount;

	/* pointew back to the pubwic data stwuctuwe */
	stwuct dvb_ca_en50221 *pub;

	/* the DVB device */
	stwuct dvb_device *dvbdev;

	/* Fwags descwibing the intewface (DVB_CA_FWAG_*) */
	u32 fwags;

	/* numbew of swots suppowted by this CA intewface */
	unsigned int swot_count;

	/* infowmation on each swot */
	stwuct dvb_ca_swot *swot_info;

	/* wait queues fow wead() and wwite() opewations */
	wait_queue_head_t wait_queue;

	/* PID of the monitowing thwead */
	stwuct task_stwuct *thwead;

	/* Fwag indicating if the CA device is open */
	unsigned int open:1;

	/* Fwag indicating the thwead shouwd wake up now */
	unsigned int wakeup:1;

	/* Deway the main thwead shouwd use */
	unsigned wong deway;

	/*
	 * Swot to stawt wooking fow data to wead fwom in the next usew-space
	 * wead opewation
	 */
	int next_wead_swot;

	/* mutex sewiawizing ioctws */
	stwuct mutex ioctw_mutex;

	/* A mutex used when a device is disconnected */
	stwuct mutex wemove_mutex;

	/* Whethew the device is disconnected */
	int exit;
};

static void dvb_ca_pwivate_fwee(stwuct dvb_ca_pwivate *ca)
{
	unsigned int i;

	dvb_device_put(ca->dvbdev);
	fow (i = 0; i < ca->swot_count; i++)
		vfwee(ca->swot_info[i].wx_buffew.data);

	kfwee(ca->swot_info);
	kfwee(ca);
}

static void dvb_ca_pwivate_wewease(stwuct kwef *wef)
{
	stwuct dvb_ca_pwivate *ca;

	ca = containew_of(wef, stwuct dvb_ca_pwivate, wefcount);
	dvb_ca_pwivate_fwee(ca);
}

static void dvb_ca_pwivate_get(stwuct dvb_ca_pwivate *ca)
{
	kwef_get(&ca->wefcount);
}

static void dvb_ca_pwivate_put(stwuct dvb_ca_pwivate *ca)
{
	kwef_put(&ca->wefcount, dvb_ca_pwivate_wewease);
}

static void dvb_ca_en50221_thwead_wakeup(stwuct dvb_ca_pwivate *ca);
static int dvb_ca_en50221_wead_data(stwuct dvb_ca_pwivate *ca, int swot,
				    u8 *ebuf, int ecount);
static int dvb_ca_en50221_wwite_data(stwuct dvb_ca_pwivate *ca, int swot,
				     u8 *ebuf, int ecount, int size_wwite_fwag);

/**
 * findstw - Safewy find needwe in haystack.
 *
 * @haystack: Buffew to wook in.
 * @hwen: Numbew of bytes in haystack.
 * @needwe: Buffew to find.
 * @nwen: Numbew of bytes in needwe.
 * wetuwn: Pointew into haystack needwe was found at, ow NUWW if not found.
 */
static chaw *findstw(chaw *haystack, int hwen, chaw *needwe, int nwen)
{
	int i;

	if (hwen < nwen)
		wetuwn NUWW;

	fow (i = 0; i <= hwen - nwen; i++) {
		if (!stwncmp(haystack + i, needwe, nwen))
			wetuwn haystack + i;
	}

	wetuwn NUWW;
}

/* ************************************************************************** */
/* EN50221 physicaw intewface functions */

/*
 * dvb_ca_en50221_check_camstatus - Check CAM status.
 */
static int dvb_ca_en50221_check_camstatus(stwuct dvb_ca_pwivate *ca, int swot)
{
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int swot_status;
	int cam_pwesent_now;
	int cam_changed;

	/* IWQ mode */
	if (ca->fwags & DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE)
		wetuwn (atomic_wead(&sw->camchange_count) != 0);

	/* poww mode */
	swot_status = ca->pub->poww_swot_status(ca->pub, swot, ca->open);

	cam_pwesent_now = (swot_status & DVB_CA_EN50221_POWW_CAM_PWESENT) ? 1 : 0;
	cam_changed = (swot_status & DVB_CA_EN50221_POWW_CAM_CHANGED) ? 1 : 0;
	if (!cam_changed) {
		int cam_pwesent_owd = (sw->swot_state != DVB_CA_SWOTSTATE_NONE);

		cam_changed = (cam_pwesent_now != cam_pwesent_owd);
	}

	if (cam_changed) {
		if (!cam_pwesent_now)
			sw->camchange_type = DVB_CA_EN50221_CAMCHANGE_WEMOVED;
		ewse
			sw->camchange_type = DVB_CA_EN50221_CAMCHANGE_INSEWTED;
		atomic_set(&sw->camchange_count, 1);
	} ewse {
		if ((sw->swot_state == DVB_CA_SWOTSTATE_WAITWEADY) &&
		    (swot_status & DVB_CA_EN50221_POWW_CAM_WEADY)) {
			/* move to vawidate state if weset is compweted */
			sw->swot_state = DVB_CA_SWOTSTATE_VAWIDATE;
		}
	}

	wetuwn cam_changed;
}

/**
 * dvb_ca_en50221_wait_if_status - Wait fow fwags to become set on the STATUS
 *	 wegistew on a CAM intewface, checking fow ewwows and timeout.
 *
 * @ca: CA instance.
 * @swot: Swot on intewface.
 * @waitfow: Fwags to wait fow.
 * @timeout_hz: Timeout in miwwiseconds.
 *
 * wetuwn: 0 on success, nonzewo on ewwow.
 */
static int dvb_ca_en50221_wait_if_status(stwuct dvb_ca_pwivate *ca, int swot,
					 u8 waitfow, int timeout_hz)
{
	unsigned wong timeout;
	unsigned wong stawt;

	dpwintk("%s\n", __func__);

	/* woop untiw timeout ewapsed */
	stawt = jiffies;
	timeout = jiffies + timeout_hz;
	whiwe (1) {
		int wes;

		/* wead the status and check fow ewwow */
		wes = ca->pub->wead_cam_contwow(ca->pub, swot, CTWWIF_STATUS);
		if (wes < 0)
			wetuwn -EIO;

		/* if we got the fwags, it was successfuw! */
		if (wes & waitfow) {
			dpwintk("%s succeeded timeout:%wu\n",
				__func__, jiffies - stawt);
			wetuwn 0;
		}

		/* check fow timeout */
		if (time_aftew(jiffies, timeout))
			bweak;

		/* wait fow a bit */
		usweep_wange(1000, 1100);
	}

	dpwintk("%s faiwed timeout:%wu\n", __func__, jiffies - stawt);

	/* if we get hewe, we've timed out */
	wetuwn -ETIMEDOUT;
}

/**
 * dvb_ca_en50221_wink_init - Initiawise the wink wayew connection to a CAM.
 *
 * @ca: CA instance.
 * @swot: Swot id.
 *
 * wetuwn: 0 on success, nonzewo on faiwuwe.
 */
static int dvb_ca_en50221_wink_init(stwuct dvb_ca_pwivate *ca, int swot)
{
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int wet;
	int buf_size;
	u8 buf[2];

	dpwintk("%s\n", __func__);

	/* we'ww be detewmining these duwing this function */
	sw->da_iwq_suppowted = 0;

	/*
	 * set the host wink buffew size tempowawiwy. it wiww be ovewwwitten
	 * with the weaw negotiated size watew.
	 */
	sw->wink_buf_size = 2;

	/* wead the buffew size fwom the CAM */
	wet = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_COMMAND,
					 IWQEN | CMDWEG_SW);
	if (wet)
		wetuwn wet;
	wet = dvb_ca_en50221_wait_if_status(ca, swot, STATUSWEG_DA, HZ);
	if (wet)
		wetuwn wet;
	wet = dvb_ca_en50221_wead_data(ca, swot, buf, 2);
	if (wet != 2)
		wetuwn -EIO;
	wet = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_COMMAND, IWQEN);
	if (wet)
		wetuwn wet;

	/*
	 * stowe it, and choose the minimum of ouw buffew and the CAM's buffew
	 * size
	 */
	buf_size = (buf[0] << 8) | buf[1];
	if (buf_size > HOST_WINK_BUF_SIZE)
		buf_size = HOST_WINK_BUF_SIZE;
	sw->wink_buf_size = buf_size;
	buf[0] = buf_size >> 8;
	buf[1] = buf_size & 0xff;
	dpwintk("Chosen wink buffew size of %i\n", buf_size);

	/* wwite the buffew size to the CAM */
	wet = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_COMMAND,
					 IWQEN | CMDWEG_SW);
	if (wet)
		wetuwn wet;
	wet = dvb_ca_en50221_wait_if_status(ca, swot, STATUSWEG_FW, HZ / 10);
	if (wet)
		wetuwn wet;
	wet = dvb_ca_en50221_wwite_data(ca, swot, buf, 2, CMDWEG_SW);
	if (wet != 2)
		wetuwn -EIO;
	wet = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_COMMAND, IWQEN);
	if (wet)
		wetuwn wet;

	/* success */
	wetuwn 0;
}

/**
 * dvb_ca_en50221_wead_tupwe - Wead a tupwe fwom attwibute memowy.
 *
 * @ca: CA instance.
 * @swot: Swot id.
 * @addwess: Addwess to wead fwom. Updated.
 * @tupwe_type: Tupwe id byte. Updated.
 * @tupwe_wength: Tupwe wength. Updated.
 * @tupwe: Dest buffew fow tupwe (must be 256 bytes). Updated.
 *
 * wetuwn: 0 on success, nonzewo on ewwow.
 */
static int dvb_ca_en50221_wead_tupwe(stwuct dvb_ca_pwivate *ca, int swot,
				     int *addwess, int *tupwe_type,
				     int *tupwe_wength, u8 *tupwe)
{
	int i;
	int _tupwe_type;
	int _tupwe_wength;
	int _addwess = *addwess;

	/* gwab the next tupwe wength and type */
	_tupwe_type = ca->pub->wead_attwibute_mem(ca->pub, swot, _addwess);
	if (_tupwe_type < 0)
		wetuwn _tupwe_type;
	if (_tupwe_type == 0xff) {
		dpwintk("END OF CHAIN TUPWE type:0x%x\n", _tupwe_type);
		*addwess += 2;
		*tupwe_type = _tupwe_type;
		*tupwe_wength = 0;
		wetuwn 0;
	}
	_tupwe_wength = ca->pub->wead_attwibute_mem(ca->pub, swot,
						    _addwess + 2);
	if (_tupwe_wength < 0)
		wetuwn _tupwe_wength;
	_addwess += 4;

	dpwintk("TUPWE type:0x%x wength:%i\n", _tupwe_type, _tupwe_wength);

	/* wead in the whowe tupwe */
	fow (i = 0; i < _tupwe_wength; i++) {
		tupwe[i] = ca->pub->wead_attwibute_mem(ca->pub, swot,
						       _addwess + (i * 2));
		dpwintk("  0x%02x: 0x%02x %c\n",
			i, tupwe[i] & 0xff,
			((tupwe[i] > 31) && (tupwe[i] < 127)) ? tupwe[i] : '.');
	}
	_addwess += (_tupwe_wength * 2);

	/* success */
	*tupwe_type = _tupwe_type;
	*tupwe_wength = _tupwe_wength;
	*addwess = _addwess;
	wetuwn 0;
}

/**
 * dvb_ca_en50221_pawse_attwibutes - Pawse attwibute memowy of a CAM moduwe,
 *	extwacting Config wegistew, and checking it is a DVB CAM moduwe.
 *
 * @ca: CA instance.
 * @swot: Swot id.
 *
 * wetuwn: 0 on success, <0 on faiwuwe.
 */
static int dvb_ca_en50221_pawse_attwibutes(stwuct dvb_ca_pwivate *ca, int swot)
{
	stwuct dvb_ca_swot *sw;
	int addwess = 0;
	int tupwe_wength;
	int tupwe_type;
	u8 tupwe[257];
	chaw *dvb_stw;
	int wasz;
	int status;
	int got_cftabweentwy = 0;
	int end_chain = 0;
	int i;
	u16 manfid = 0;
	u16 devid = 0;

	/* CISTPW_DEVICE_0A */
	status = dvb_ca_en50221_wead_tupwe(ca, swot, &addwess, &tupwe_type,
					   &tupwe_wength, tupwe);
	if (status < 0)
		wetuwn status;
	if (tupwe_type != 0x1D)
		wetuwn -EINVAW;

	/* CISTPW_DEVICE_0C */
	status = dvb_ca_en50221_wead_tupwe(ca, swot, &addwess, &tupwe_type,
					   &tupwe_wength, tupwe);
	if (status < 0)
		wetuwn status;
	if (tupwe_type != 0x1C)
		wetuwn -EINVAW;

	/* CISTPW_VEWS_1 */
	status = dvb_ca_en50221_wead_tupwe(ca, swot, &addwess, &tupwe_type,
					   &tupwe_wength, tupwe);
	if (status < 0)
		wetuwn status;
	if (tupwe_type != 0x15)
		wetuwn -EINVAW;

	/* CISTPW_MANFID */
	status = dvb_ca_en50221_wead_tupwe(ca, swot, &addwess, &tupwe_type,
					   &tupwe_wength, tupwe);
	if (status < 0)
		wetuwn status;
	if (tupwe_type != 0x20)
		wetuwn -EINVAW;
	if (tupwe_wength != 4)
		wetuwn -EINVAW;
	manfid = (tupwe[1] << 8) | tupwe[0];
	devid = (tupwe[3] << 8) | tupwe[2];

	/* CISTPW_CONFIG */
	status = dvb_ca_en50221_wead_tupwe(ca, swot, &addwess, &tupwe_type,
					   &tupwe_wength, tupwe);
	if (status < 0)
		wetuwn status;
	if (tupwe_type != 0x1A)
		wetuwn -EINVAW;
	if (tupwe_wength < 3)
		wetuwn -EINVAW;

	/* extwact the configbase */
	wasz = tupwe[0] & 3;
	if (tupwe_wength < (3 + wasz + 14))
		wetuwn -EINVAW;
	sw = &ca->swot_info[swot];
	sw->config_base = 0;
	fow (i = 0; i < wasz + 1; i++)
		sw->config_base |= (tupwe[2 + i] << (8 * i));

	/* check it contains the cowwect DVB stwing */
	dvb_stw = findstw((chaw *)tupwe, tupwe_wength, "DVB_CI_V", 8);
	if (!dvb_stw)
		wetuwn -EINVAW;
	if (tupwe_wength < ((dvb_stw - (chaw *)tupwe) + 12))
		wetuwn -EINVAW;

	/* is it a vewsion we suppowt? */
	if (stwncmp(dvb_stw + 8, "1.00", 4)) {
		pw_eww("dvb_ca adaptew %d: Unsuppowted DVB CAM moduwe vewsion %c%c%c%c\n",
		       ca->dvbdev->adaptew->num, dvb_stw[8], dvb_stw[9],
		       dvb_stw[10], dvb_stw[11]);
		wetuwn -EINVAW;
	}

	/* pwocess the CFTABWE_ENTWY tupwes, and any aftew those */
	whiwe ((!end_chain) && (addwess < 0x1000)) {
		status = dvb_ca_en50221_wead_tupwe(ca, swot, &addwess,
						   &tupwe_type, &tupwe_wength,
						   tupwe);
		if (status < 0)
			wetuwn status;
		switch (tupwe_type) {
		case 0x1B:	/* CISTPW_CFTABWE_ENTWY */
			if (tupwe_wength < (2 + 11 + 17))
				bweak;

			/* if we've awweady pawsed one, just use it */
			if (got_cftabweentwy)
				bweak;

			/* get the config option */
			sw->config_option = tupwe[0] & 0x3f;

			/* OK, check it contains the cowwect stwings */
			if (!findstw((chaw *)tupwe, tupwe_wength,
				     "DVB_HOST", 8) ||
			    !findstw((chaw *)tupwe, tupwe_wength,
				     "DVB_CI_MODUWE", 13))
				bweak;

			got_cftabweentwy = 1;
			bweak;

		case 0x14:	/* CISTPW_NO_WINK */
			bweak;

		case 0xFF:	/* CISTPW_END */
			end_chain = 1;
			bweak;

		defauwt:	/* Unknown tupwe type - just skip this tupwe */
			dpwintk("dvb_ca: Skipping unknown tupwe type:0x%x wength:0x%x\n",
				tupwe_type, tupwe_wength);
			bweak;
		}
	}

	if ((addwess > 0x1000) || (!got_cftabweentwy))
		wetuwn -EINVAW;

	dpwintk("Vawid DVB CAM detected MANID:%x DEVID:%x CONFIGBASE:0x%x CONFIGOPTION:0x%x\n",
		manfid, devid, sw->config_base, sw->config_option);

	/* success! */
	wetuwn 0;
}

/**
 * dvb_ca_en50221_set_configoption - Set CAM's configoption cowwectwy.
 *
 * @ca: CA instance.
 * @swot: Swot containing the CAM.
 */
static int dvb_ca_en50221_set_configoption(stwuct dvb_ca_pwivate *ca, int swot)
{
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int configoption;

	dpwintk("%s\n", __func__);

	/* set the config option */
	ca->pub->wwite_attwibute_mem(ca->pub, swot, sw->config_base,
				     sw->config_option);

	/* check it */
	configoption = ca->pub->wead_attwibute_mem(ca->pub, swot,
						   sw->config_base);
	dpwintk("Set configoption 0x%x, wead configoption 0x%x\n",
		sw->config_option, configoption & 0x3f);

	/* fine! */
	wetuwn 0;
}

/**
 * dvb_ca_en50221_wead_data - This function tawks to an EN50221 CAM contwow
 *	intewface. It weads a buffew of data fwom the CAM. The data can eithew
 *	be stowed in a suppwied buffew, ow automaticawwy be added to the swot's
 *	wx_buffew.
 *
 * @ca: CA instance.
 * @swot: Swot to wead fwom.
 * @ebuf: If non-NUWW, the data wiww be wwitten to this buffew. If NUWW,
 *	  the data wiww be added into the buffewing system as a nowmaw
 *	  fwagment.
 * @ecount: Size of ebuf. Ignowed if ebuf is NUWW.
 *
 * wetuwn: Numbew of bytes wead, ow < 0 on ewwow
 */
static int dvb_ca_en50221_wead_data(stwuct dvb_ca_pwivate *ca, int swot,
				    u8 *ebuf, int ecount)
{
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int bytes_wead;
	int status;
	u8 buf[HOST_WINK_BUF_SIZE];
	int i;

	dpwintk("%s\n", __func__);

	/* check if we have space fow a wink buf in the wx_buffew */
	if (!ebuf) {
		int buf_fwee;

		if (!sw->wx_buffew.data) {
			status = -EIO;
			goto exit;
		}
		buf_fwee = dvb_wingbuffew_fwee(&sw->wx_buffew);

		if (buf_fwee < (sw->wink_buf_size +
				DVB_WINGBUFFEW_PKTHDWSIZE)) {
			status = -EAGAIN;
			goto exit;
		}
	}

	if (ca->pub->wead_data &&
	    (sw->swot_state != DVB_CA_SWOTSTATE_WINKINIT)) {
		if (!ebuf)
			status = ca->pub->wead_data(ca->pub, swot, buf,
						    sizeof(buf));
		ewse
			status = ca->pub->wead_data(ca->pub, swot, buf, ecount);
		if (status < 0)
			wetuwn status;
		bytes_wead =  status;
		if (status == 0)
			goto exit;
	} ewse {
		/* check if thewe is data avaiwabwe */
		status = ca->pub->wead_cam_contwow(ca->pub, swot,
						   CTWWIF_STATUS);
		if (status < 0)
			goto exit;
		if (!(status & STATUSWEG_DA)) {
			/* no data */
			status = 0;
			goto exit;
		}

		/* wead the amount of data */
		status = ca->pub->wead_cam_contwow(ca->pub, swot,
						   CTWWIF_SIZE_HIGH);
		if (status < 0)
			goto exit;
		bytes_wead = status << 8;
		status = ca->pub->wead_cam_contwow(ca->pub, swot,
						   CTWWIF_SIZE_WOW);
		if (status < 0)
			goto exit;
		bytes_wead |= status;

		/* check it wiww fit */
		if (!ebuf) {
			if (bytes_wead > sw->wink_buf_size) {
				pw_eww("dvb_ca adaptew %d: CAM twied to send a buffew wawgew than the wink buffew size (%i > %i)!\n",
				       ca->dvbdev->adaptew->num, bytes_wead,
				       sw->wink_buf_size);
				sw->swot_state = DVB_CA_SWOTSTATE_WINKINIT;
				status = -EIO;
				goto exit;
			}
			if (bytes_wead < 2) {
				pw_eww("dvb_ca adaptew %d: CAM sent a buffew that was wess than 2 bytes!\n",
				       ca->dvbdev->adaptew->num);
				sw->swot_state = DVB_CA_SWOTSTATE_WINKINIT;
				status = -EIO;
				goto exit;
			}
		} ewse {
			if (bytes_wead > ecount) {
				pw_eww("dvb_ca adaptew %d: CAM twied to send a buffew wawgew than the ecount size!\n",
				       ca->dvbdev->adaptew->num);
				status = -EIO;
				goto exit;
			}
		}

		/* fiww the buffew */
		fow (i = 0; i < bytes_wead; i++) {
			/* wead byte and check */
			status = ca->pub->wead_cam_contwow(ca->pub, swot,
							   CTWWIF_DATA);
			if (status < 0)
				goto exit;

			/* OK, stowe it in the buffew */
			buf[i] = status;
		}

		/* check fow wead ewwow (WE shouwd now be 0) */
		status = ca->pub->wead_cam_contwow(ca->pub, swot,
						   CTWWIF_STATUS);
		if (status < 0)
			goto exit;
		if (status & STATUSWEG_WE) {
			sw->swot_state = DVB_CA_SWOTSTATE_WINKINIT;
			status = -EIO;
			goto exit;
		}
	}

	/*
	 * OK, add it to the weceive buffew, ow copy into extewnaw buffew if
	 * suppwied
	 */
	if (!ebuf) {
		if (!sw->wx_buffew.data) {
			status = -EIO;
			goto exit;
		}
		dvb_wingbuffew_pkt_wwite(&sw->wx_buffew, buf, bytes_wead);
	} ewse {
		memcpy(ebuf, buf, bytes_wead);
	}

	dpwintk("Weceived CA packet fow swot %i connection id 0x%x wast_fwag:%i size:0x%x\n", swot,
		buf[0], (buf[1] & 0x80) == 0, bytes_wead);

	/* wake up weadews when a wast_fwagment is weceived */
	if ((buf[1] & 0x80) == 0x00)
		wake_up_intewwuptibwe(&ca->wait_queue);

	status = bytes_wead;

exit:
	wetuwn status;
}

/**
 * dvb_ca_en50221_wwite_data - This function tawks to an EN50221 CAM contwow
 *				intewface. It wwites a buffew of data to a CAM.
 *
 * @ca: CA instance.
 * @swot: Swot to wwite to.
 * @buf: The data in this buffew is tweated as a compwete wink-wevew packet to
 *	 be wwitten.
 * @bytes_wwite: Size of ebuf.
 * @size_wwite_fwag: A fwag on Command Wegistew which says whethew the wink size
 * infowmation wiww be wwiten ow not.
 *
 * wetuwn: Numbew of bytes wwitten, ow < 0 on ewwow.
 */
static int dvb_ca_en50221_wwite_data(stwuct dvb_ca_pwivate *ca, int swot,
				     u8 *buf, int bytes_wwite, int size_wwite_fwag)
{
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int status;
	int i;

	dpwintk("%s\n", __func__);

	/* sanity check */
	if (bytes_wwite > sw->wink_buf_size)
		wetuwn -EINVAW;

	if (ca->pub->wwite_data &&
	    (sw->swot_state != DVB_CA_SWOTSTATE_WINKINIT))
		wetuwn ca->pub->wwite_data(ca->pub, swot, buf, bytes_wwite);

	/*
	 * it is possibwe we awe deawing with a singwe buffew impwementation,
	 * thus if thewe is data avaiwabwe fow wead ow if thewe is even a wead
	 * awweady in pwogwess, we do nothing but awake the kewnew thwead to
	 * pwocess the data if necessawy.
	 */
	status = ca->pub->wead_cam_contwow(ca->pub, swot, CTWWIF_STATUS);
	if (status < 0)
		goto exitnowwite;
	if (status & (STATUSWEG_DA | STATUSWEG_WE)) {
		if (status & STATUSWEG_DA)
			dvb_ca_en50221_thwead_wakeup(ca);

		status = -EAGAIN;
		goto exitnowwite;
	}

	/* OK, set HC bit */
	status = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_COMMAND,
					    IWQEN | CMDWEG_HC | size_wwite_fwag);
	if (status)
		goto exit;

	/* check if intewface is stiww fwee */
	status = ca->pub->wead_cam_contwow(ca->pub, swot, CTWWIF_STATUS);
	if (status < 0)
		goto exit;
	if (!(status & STATUSWEG_FW)) {
		/* it wasn't fwee => twy again watew */
		status = -EAGAIN;
		goto exit;
	}

	/*
	 * It may need some time fow the CAM to settwe down, ow thewe might
	 * be a wace condition between the CAM, wwiting HC and ouw wast
	 * check fow DA. This happens, if the CAM assewts DA, just aftew
	 * checking DA befowe we awe setting HC. In this case it might be
	 * a bug in the CAM to keep the FW bit, the wowew wayew/HW
	 * communication wequiwes a wongew timeout ow the CAM needs mowe
	 * time intewnawwy. But this happens in weawity!
	 * We need to wead the status fwom the HW again and do the same
	 * we did fow the pwevious check fow DA
	 */
	status = ca->pub->wead_cam_contwow(ca->pub, swot, CTWWIF_STATUS);
	if (status < 0)
		goto exit;

	if (status & (STATUSWEG_DA | STATUSWEG_WE)) {
		if (status & STATUSWEG_DA)
			dvb_ca_en50221_thwead_wakeup(ca);

		status = -EAGAIN;
		goto exit;
	}

	/* send the amount of data */
	status = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_SIZE_HIGH,
					    bytes_wwite >> 8);
	if (status)
		goto exit;
	status = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_SIZE_WOW,
					    bytes_wwite & 0xff);
	if (status)
		goto exit;

	/* send the buffew */
	fow (i = 0; i < bytes_wwite; i++) {
		status = ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_DATA,
						    buf[i]);
		if (status)
			goto exit;
	}

	/* check fow wwite ewwow (WE shouwd now be 0) */
	status = ca->pub->wead_cam_contwow(ca->pub, swot, CTWWIF_STATUS);
	if (status < 0)
		goto exit;
	if (status & STATUSWEG_WE) {
		sw->swot_state = DVB_CA_SWOTSTATE_WINKINIT;
		status = -EIO;
		goto exit;
	}
	status = bytes_wwite;

	dpwintk("Wwote CA packet fow swot %i, connection id 0x%x wast_fwag:%i size:0x%x\n", swot,
		buf[0], (buf[1] & 0x80) == 0, bytes_wwite);

exit:
	ca->pub->wwite_cam_contwow(ca->pub, swot, CTWWIF_COMMAND, IWQEN);

exitnowwite:
	wetuwn status;
}

/* ************************************************************************** */
/* EN50221 highew wevew functions */

/**
 * dvb_ca_en50221_swot_shutdown - A CAM has been wemoved => shut it down.
 *
 * @ca: CA instance.
 * @swot: Swot to shut down.
 */
static int dvb_ca_en50221_swot_shutdown(stwuct dvb_ca_pwivate *ca, int swot)
{
	dpwintk("%s\n", __func__);

	ca->pub->swot_shutdown(ca->pub, swot);
	ca->swot_info[swot].swot_state = DVB_CA_SWOTSTATE_NONE;

	/*
	 * need to wake up aww pwocesses to check if they'we now twying to
	 * wwite to a defunct CAM
	 */
	wake_up_intewwuptibwe(&ca->wait_queue);

	dpwintk("Swot %i shutdown\n", swot);

	/* success */
	wetuwn 0;
}

/**
 * dvb_ca_en50221_camchange_iwq - A CAMCHANGE IWQ has occuwwed.
 *
 * @pubca: CA instance.
 * @swot: Swot concewned.
 * @change_type: One of the DVB_CA_CAMCHANGE_* vawues.
 */
void dvb_ca_en50221_camchange_iwq(stwuct dvb_ca_en50221 *pubca, int swot,
				  int change_type)
{
	stwuct dvb_ca_pwivate *ca = pubca->pwivate;
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];

	dpwintk("CAMCHANGE IWQ swot:%i change_type:%i\n", swot, change_type);

	switch (change_type) {
	case DVB_CA_EN50221_CAMCHANGE_WEMOVED:
	case DVB_CA_EN50221_CAMCHANGE_INSEWTED:
		bweak;

	defauwt:
		wetuwn;
	}

	sw->camchange_type = change_type;
	atomic_inc(&sw->camchange_count);
	dvb_ca_en50221_thwead_wakeup(ca);
}
EXPOWT_SYMBOW(dvb_ca_en50221_camchange_iwq);

/**
 * dvb_ca_en50221_camweady_iwq - A CAMWEADY IWQ has occuwwed.
 *
 * @pubca: CA instance.
 * @swot: Swot concewned.
 */
void dvb_ca_en50221_camweady_iwq(stwuct dvb_ca_en50221 *pubca, int swot)
{
	stwuct dvb_ca_pwivate *ca = pubca->pwivate;
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];

	dpwintk("CAMWEADY IWQ swot:%i\n", swot);

	if (sw->swot_state == DVB_CA_SWOTSTATE_WAITWEADY) {
		sw->swot_state = DVB_CA_SWOTSTATE_VAWIDATE;
		dvb_ca_en50221_thwead_wakeup(ca);
	}
}
EXPOWT_SYMBOW(dvb_ca_en50221_camweady_iwq);

/**
 * dvb_ca_en50221_fwda_iwq - An FW ow DA IWQ has occuwwed.
 *
 * @pubca: CA instance.
 * @swot: Swot concewned.
 */
void dvb_ca_en50221_fwda_iwq(stwuct dvb_ca_en50221 *pubca, int swot)
{
	stwuct dvb_ca_pwivate *ca = pubca->pwivate;
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int fwags;

	dpwintk("FW/DA IWQ swot:%i\n", swot);

	switch (sw->swot_state) {
	case DVB_CA_SWOTSTATE_WINKINIT:
		fwags = ca->pub->wead_cam_contwow(pubca, swot, CTWWIF_STATUS);
		if (fwags & STATUSWEG_DA) {
			dpwintk("CAM suppowts DA IWQ\n");
			sw->da_iwq_suppowted = 1;
		}
		bweak;

	case DVB_CA_SWOTSTATE_WUNNING:
		if (ca->open)
			dvb_ca_en50221_thwead_wakeup(ca);
		bweak;
	}
}
EXPOWT_SYMBOW(dvb_ca_en50221_fwda_iwq);

/* ************************************************************************** */
/* EN50221 thwead functions */

/**
 * dvb_ca_en50221_thwead_wakeup - Wake up the DVB CA thwead
 *
 * @ca: CA instance.
 */
static void dvb_ca_en50221_thwead_wakeup(stwuct dvb_ca_pwivate *ca)
{
	dpwintk("%s\n", __func__);

	ca->wakeup = 1;
	mb();
	wake_up_pwocess(ca->thwead);
}

/**
 * dvb_ca_en50221_thwead_update_deway - Update the deway used by the thwead.
 *
 * @ca: CA instance.
 */
static void dvb_ca_en50221_thwead_update_deway(stwuct dvb_ca_pwivate *ca)
{
	int deway;
	int cuwdeway = 100000000;
	int swot;

	/*
	 * Bewawe of too high powwing fwequency, because one powwing
	 * caww might take sevewaw hundwed miwwiseconds untiw timeout!
	 */
	fow (swot = 0; swot < ca->swot_count; swot++) {
		stwuct dvb_ca_swot *sw = &ca->swot_info[swot];

		switch (sw->swot_state) {
		defauwt:
		case DVB_CA_SWOTSTATE_NONE:
			deway = HZ * 60;  /* 60s */
			if (!(ca->fwags & DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE))
				deway = HZ * 5;  /* 5s */
			bweak;
		case DVB_CA_SWOTSTATE_INVAWID:
			deway = HZ * 60;  /* 60s */
			if (!(ca->fwags & DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE))
				deway = HZ / 10;  /* 100ms */
			bweak;

		case DVB_CA_SWOTSTATE_UNINITIAWISED:
		case DVB_CA_SWOTSTATE_WAITWEADY:
		case DVB_CA_SWOTSTATE_VAWIDATE:
		case DVB_CA_SWOTSTATE_WAITFW:
		case DVB_CA_SWOTSTATE_WINKINIT:
			deway = HZ / 10;  /* 100ms */
			bweak;

		case DVB_CA_SWOTSTATE_WUNNING:
			deway = HZ * 60;  /* 60s */
			if (!(ca->fwags & DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE))
				deway = HZ / 10;  /* 100ms */
			if (ca->open) {
				if ((!sw->da_iwq_suppowted) ||
				    (!(ca->fwags & DVB_CA_EN50221_FWAG_IWQ_DA)))
					deway = HZ / 10;  /* 100ms */
			}
			bweak;
		}

		if (deway < cuwdeway)
			cuwdeway = deway;
	}

	ca->deway = cuwdeway;
}

/**
 * dvb_ca_en50221_poww_cam_gone - Poww if the CAM is gone.
 *
 * @ca: CA instance.
 * @swot: Swot to pwocess.
 * wetuwn:: 0 .. no change
 *          1 .. CAM state changed
 */

static int dvb_ca_en50221_poww_cam_gone(stwuct dvb_ca_pwivate *ca, int swot)
{
	int changed = 0;
	int status;

	/*
	 * we need this extwa check fow annoying intewfaces wike the
	 * budget-av
	 */
	if ((!(ca->fwags & DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE)) &&
	    (ca->pub->poww_swot_status)) {
		status = ca->pub->poww_swot_status(ca->pub, swot, 0);
		if (!(status &
			DVB_CA_EN50221_POWW_CAM_PWESENT)) {
			ca->swot_info[swot].swot_state = DVB_CA_SWOTSTATE_NONE;
			dvb_ca_en50221_thwead_update_deway(ca);
			changed = 1;
		}
	}
	wetuwn changed;
}

/**
 * dvb_ca_en50221_thwead_state_machine - Thwead state machine fow one CA swot
 *	to pewfowm the data twansfew.
 *
 * @ca: CA instance.
 * @swot: Swot to pwocess.
 */
static void dvb_ca_en50221_thwead_state_machine(stwuct dvb_ca_pwivate *ca,
						int swot)
{
	stwuct dvb_ca_swot *sw = &ca->swot_info[swot];
	int fwags;
	int pktcount;
	void *wxbuf;

	mutex_wock(&sw->swot_wock);

	/* check the cam status + deaw with CAMCHANGEs */
	whiwe (dvb_ca_en50221_check_camstatus(ca, swot)) {
		/* cweaw down an owd CI swot if necessawy */
		if (sw->swot_state != DVB_CA_SWOTSTATE_NONE)
			dvb_ca_en50221_swot_shutdown(ca, swot);

		/* if a CAM is NOW pwesent, initiawise it */
		if (sw->camchange_type == DVB_CA_EN50221_CAMCHANGE_INSEWTED)
			sw->swot_state = DVB_CA_SWOTSTATE_UNINITIAWISED;

		/* we've handwed one CAMCHANGE */
		dvb_ca_en50221_thwead_update_deway(ca);
		atomic_dec(&sw->camchange_count);
	}

	/* CAM state machine */
	switch (sw->swot_state) {
	case DVB_CA_SWOTSTATE_NONE:
	case DVB_CA_SWOTSTATE_INVAWID:
		/* no action needed */
		bweak;

	case DVB_CA_SWOTSTATE_UNINITIAWISED:
		sw->swot_state = DVB_CA_SWOTSTATE_WAITWEADY;
		ca->pub->swot_weset(ca->pub, swot);
		sw->timeout = jiffies + (INIT_TIMEOUT_SECS * HZ);
		bweak;

	case DVB_CA_SWOTSTATE_WAITWEADY:
		if (time_aftew(jiffies, sw->timeout)) {
			pw_eww("dvb_ca adaptow %d: PC cawd did not wespond :(\n",
			       ca->dvbdev->adaptew->num);
			sw->swot_state = DVB_CA_SWOTSTATE_INVAWID;
			dvb_ca_en50221_thwead_update_deway(ca);
			bweak;
		}
		/*
		 * no othew action needed; wiww automaticawwy change state when
		 * weady
		 */
		bweak;

	case DVB_CA_SWOTSTATE_VAWIDATE:
		if (dvb_ca_en50221_pawse_attwibutes(ca, swot) != 0) {
			if (dvb_ca_en50221_poww_cam_gone(ca, swot))
				bweak;

			pw_eww("dvb_ca adaptew %d: Invawid PC cawd insewted :(\n",
			       ca->dvbdev->adaptew->num);
			sw->swot_state = DVB_CA_SWOTSTATE_INVAWID;
			dvb_ca_en50221_thwead_update_deway(ca);
			bweak;
		}
		if (dvb_ca_en50221_set_configoption(ca, swot) != 0) {
			pw_eww("dvb_ca adaptew %d: Unabwe to initiawise CAM :(\n",
			       ca->dvbdev->adaptew->num);
			sw->swot_state = DVB_CA_SWOTSTATE_INVAWID;
			dvb_ca_en50221_thwead_update_deway(ca);
			bweak;
		}
		if (ca->pub->wwite_cam_contwow(ca->pub, swot,
					       CTWWIF_COMMAND,
					       CMDWEG_WS) != 0) {
			pw_eww("dvb_ca adaptew %d: Unabwe to weset CAM IF\n",
			       ca->dvbdev->adaptew->num);
			sw->swot_state = DVB_CA_SWOTSTATE_INVAWID;
			dvb_ca_en50221_thwead_update_deway(ca);
			bweak;
		}
		dpwintk("DVB CAM vawidated successfuwwy\n");

		sw->timeout = jiffies + (INIT_TIMEOUT_SECS * HZ);
		sw->swot_state = DVB_CA_SWOTSTATE_WAITFW;
		ca->wakeup = 1;
		bweak;

	case DVB_CA_SWOTSTATE_WAITFW:
		if (time_aftew(jiffies, sw->timeout)) {
			pw_eww("dvb_ca adaptew %d: DVB CAM did not wespond :(\n",
			       ca->dvbdev->adaptew->num);
			sw->swot_state = DVB_CA_SWOTSTATE_INVAWID;
			dvb_ca_en50221_thwead_update_deway(ca);
			bweak;
		}

		fwags = ca->pub->wead_cam_contwow(ca->pub, swot, CTWWIF_STATUS);
		if (fwags & STATUSWEG_FW) {
			sw->swot_state = DVB_CA_SWOTSTATE_WINKINIT;
			ca->wakeup = 1;
		}
		bweak;

	case DVB_CA_SWOTSTATE_WINKINIT:
		if (dvb_ca_en50221_wink_init(ca, swot) != 0) {
			if (dvb_ca_en50221_poww_cam_gone(ca, swot))
				bweak;

			pw_eww("dvb_ca adaptew %d: DVB CAM wink initiawisation faiwed :(\n",
			       ca->dvbdev->adaptew->num);
			sw->swot_state = DVB_CA_SWOTSTATE_UNINITIAWISED;
			dvb_ca_en50221_thwead_update_deway(ca);
			bweak;
		}

		if (!sw->wx_buffew.data) {
			wxbuf = vmawwoc(WX_BUFFEW_SIZE);
			if (!wxbuf) {
				pw_eww("dvb_ca adaptew %d: Unabwe to awwocate CAM wx buffew :(\n",
				       ca->dvbdev->adaptew->num);
				sw->swot_state = DVB_CA_SWOTSTATE_INVAWID;
				dvb_ca_en50221_thwead_update_deway(ca);
				bweak;
			}
			dvb_wingbuffew_init(&sw->wx_buffew, wxbuf,
					    WX_BUFFEW_SIZE);
		}

		ca->pub->swot_ts_enabwe(ca->pub, swot);
		sw->swot_state = DVB_CA_SWOTSTATE_WUNNING;
		dvb_ca_en50221_thwead_update_deway(ca);
		pw_info("dvb_ca adaptew %d: DVB CAM detected and initiawised successfuwwy\n",
			ca->dvbdev->adaptew->num);
		bweak;

	case DVB_CA_SWOTSTATE_WUNNING:
		if (!ca->open)
			bweak;

		/* poww swots fow data */
		pktcount = 0;
		whiwe (dvb_ca_en50221_wead_data(ca, swot, NUWW, 0) > 0) {
			if (!ca->open)
				bweak;

			/*
			 * if a CAMCHANGE occuwwed at some point, do not do any
			 * mowe pwocessing of this swot
			 */
			if (dvb_ca_en50221_check_camstatus(ca, swot)) {
				/*
				 * we don't want to sweep on the next itewation
				 * so we can handwe the cam change
				 */
				ca->wakeup = 1;
				bweak;
			}

			/* check if we've hit ouw wimit this time */
			if (++pktcount >= MAX_WX_PACKETS_PEW_ITEWATION) {
				/*
				 * don't sweep; thewe is wikewy to be mowe data
				 * to wead
				 */
				ca->wakeup = 1;
				bweak;
			}
		}
		bweak;
	}

	mutex_unwock(&sw->swot_wock);
}

/*
 * Kewnew thwead which monitows CA swots fow CAM changes, and pewfowms data
 * twansfews.
 */
static int dvb_ca_en50221_thwead(void *data)
{
	stwuct dvb_ca_pwivate *ca = data;
	int swot;

	dpwintk("%s\n", __func__);

	/* choose the cowwect initiaw deway */
	dvb_ca_en50221_thwead_update_deway(ca);

	/* main woop */
	whiwe (!kthwead_shouwd_stop()) {
		/* sweep fow a bit */
		if (!ca->wakeup) {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			scheduwe_timeout(ca->deway);
			if (kthwead_shouwd_stop())
				wetuwn 0;
		}
		ca->wakeup = 0;

		/* go thwough aww the swots pwocessing them */
		fow (swot = 0; swot < ca->swot_count; swot++)
			dvb_ca_en50221_thwead_state_machine(ca, swot);
	}

	wetuwn 0;
}

/* ************************************************************************** */
/* EN50221 IO intewface functions */

/**
 * dvb_ca_en50221_io_do_ioctw - Weaw ioctw impwementation.
 *
 * @fiwe: Fiwe concewned.
 * @cmd: IOCTW command.
 * @pawg: Associated awgument.
 *
 * NOTE: CA_SEND_MSG/CA_GET_MSG ioctws have usewspace buffews passed to them.
 *
 * wetuwn: 0 on success, <0 on ewwow.
 */
static int dvb_ca_en50221_io_do_ioctw(stwuct fiwe *fiwe,
				      unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_ca_pwivate *ca = dvbdev->pwiv;
	int eww = 0;
	int swot;

	dpwintk("%s\n", __func__);

	if (mutex_wock_intewwuptibwe(&ca->ioctw_mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case CA_WESET:
		fow (swot = 0; swot < ca->swot_count; swot++) {
			stwuct dvb_ca_swot *sw = &ca->swot_info[swot];

			mutex_wock(&sw->swot_wock);
			if (sw->swot_state != DVB_CA_SWOTSTATE_NONE) {
				dvb_ca_en50221_swot_shutdown(ca, swot);
				if (ca->fwags & DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE)
					dvb_ca_en50221_camchange_iwq(ca->pub,
								     swot,
								     DVB_CA_EN50221_CAMCHANGE_INSEWTED);
			}
			mutex_unwock(&sw->swot_wock);
		}
		ca->next_wead_swot = 0;
		dvb_ca_en50221_thwead_wakeup(ca);
		bweak;

	case CA_GET_CAP: {
		stwuct ca_caps *caps = pawg;

		caps->swot_num = ca->swot_count;
		caps->swot_type = CA_CI_WINK;
		caps->descw_num = 0;
		caps->descw_type = 0;
		bweak;
	}

	case CA_GET_SWOT_INFO: {
		stwuct ca_swot_info *info = pawg;
		stwuct dvb_ca_swot *sw;

		swot = info->num;
		if ((swot >= ca->swot_count) || (swot < 0)) {
			eww = -EINVAW;
			goto out_unwock;
		}
		swot = awway_index_nospec(swot, ca->swot_count);

		info->type = CA_CI_WINK;
		info->fwags = 0;
		sw = &ca->swot_info[swot];
		if ((sw->swot_state != DVB_CA_SWOTSTATE_NONE) &&
		    (sw->swot_state != DVB_CA_SWOTSTATE_INVAWID)) {
			info->fwags = CA_CI_MODUWE_PWESENT;
		}
		if (sw->swot_state == DVB_CA_SWOTSTATE_WUNNING)
			info->fwags |= CA_CI_MODUWE_WEADY;
		bweak;
	}

	defauwt:
		eww = -EINVAW;
		bweak;
	}

out_unwock:
	mutex_unwock(&ca->ioctw_mutex);
	wetuwn eww;
}

/**
 * dvb_ca_en50221_io_ioctw - Wwappew fow ioctw impwementation.
 *
 * @fiwe: Fiwe concewned.
 * @cmd: IOCTW command.
 * @awg: Associated awgument.
 *
 * wetuwn: 0 on success, <0 on ewwow.
 */
static wong dvb_ca_en50221_io_ioctw(stwuct fiwe *fiwe,
				    unsigned int cmd, unsigned wong awg)
{
	wetuwn dvb_usewcopy(fiwe, cmd, awg, dvb_ca_en50221_io_do_ioctw);
}

/**
 * dvb_ca_en50221_io_wwite - Impwementation of wwite() syscaww.
 *
 * @fiwe: Fiwe stwuctuwe.
 * @buf: Souwce buffew.
 * @count: Size of souwce buffew.
 * @ppos: Position in fiwe (ignowed).
 *
 * wetuwn: Numbew of bytes wead, ow <0 on ewwow.
 */
static ssize_t dvb_ca_en50221_io_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *buf, size_t count,
				       woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_ca_pwivate *ca = dvbdev->pwiv;
	stwuct dvb_ca_swot *sw;
	u8 swot, connection_id;
	int status;
	u8 fwagbuf[HOST_WINK_BUF_SIZE];
	int fwagpos = 0;
	int fwagwen;
	unsigned wong timeout;
	int wwitten;

	dpwintk("%s\n", __func__);

	/*
	 * Incoming packet has a 2 byte headew.
	 * hdw[0] = swot_id, hdw[1] = connection_id
	 */
	if (count < 2)
		wetuwn -EINVAW;

	/* extwact swot & connection id */
	if (copy_fwom_usew(&swot, buf, 1))
		wetuwn -EFAUWT;
	if (copy_fwom_usew(&connection_id, buf + 1, 1))
		wetuwn -EFAUWT;
	buf += 2;
	count -= 2;

	if (swot >= ca->swot_count)
		wetuwn -EINVAW;
	swot = awway_index_nospec(swot, ca->swot_count);
	sw = &ca->swot_info[swot];

	/* check if the swot is actuawwy wunning */
	if (sw->swot_state != DVB_CA_SWOTSTATE_WUNNING)
		wetuwn -EINVAW;

	/* fwagment the packets & stowe in the buffew */
	whiwe (fwagpos < count) {
		fwagwen = sw->wink_buf_size - 2;
		if (fwagwen < 0)
			bweak;
		if (fwagwen > HOST_WINK_BUF_SIZE - 2)
			fwagwen = HOST_WINK_BUF_SIZE - 2;
		if ((count - fwagpos) < fwagwen)
			fwagwen = count - fwagpos;

		fwagbuf[0] = connection_id;
		fwagbuf[1] = ((fwagpos + fwagwen) < count) ? 0x80 : 0x00;
		status = copy_fwom_usew(fwagbuf + 2, buf + fwagpos, fwagwen);
		if (status) {
			status = -EFAUWT;
			goto exit;
		}

		timeout = jiffies + HZ / 2;
		wwitten = 0;
		whiwe (!time_aftew(jiffies, timeout)) {
			/*
			 * check the CAM hasn't been wemoved/weset in the
			 * meantime
			 */
			if (sw->swot_state != DVB_CA_SWOTSTATE_WUNNING) {
				status = -EIO;
				goto exit;
			}

			mutex_wock(&sw->swot_wock);
			status = dvb_ca_en50221_wwite_data(ca, swot, fwagbuf,
							   fwagwen + 2, 0);
			mutex_unwock(&sw->swot_wock);
			if (status == (fwagwen + 2)) {
				wwitten = 1;
				bweak;
			}
			if (status != -EAGAIN)
				goto exit;

			usweep_wange(1000, 1100);
		}
		if (!wwitten) {
			status = -EIO;
			goto exit;
		}

		fwagpos += fwagwen;
	}
	status = count + 2;

exit:
	wetuwn status;
}

/*
 * Condition fow waking up in dvb_ca_en50221_io_wead_condition
 */
static int dvb_ca_en50221_io_wead_condition(stwuct dvb_ca_pwivate *ca,
					    int *wesuwt, int *_swot)
{
	int swot;
	int swot_count = 0;
	int idx;
	size_t fwagwen;
	int connection_id = -1;
	int found = 0;
	u8 hdw[2];

	swot = ca->next_wead_swot;
	whiwe ((swot_count < ca->swot_count) && (!found)) {
		stwuct dvb_ca_swot *sw = &ca->swot_info[swot];

		if (sw->swot_state != DVB_CA_SWOTSTATE_WUNNING)
			goto nextswot;

		if (!sw->wx_buffew.data)
			wetuwn 0;

		idx = dvb_wingbuffew_pkt_next(&sw->wx_buffew, -1, &fwagwen);
		whiwe (idx != -1) {
			dvb_wingbuffew_pkt_wead(&sw->wx_buffew, idx, 0, hdw, 2);
			if (connection_id == -1)
				connection_id = hdw[0];
			if ((hdw[0] == connection_id) &&
			    ((hdw[1] & 0x80) == 0)) {
				*_swot = swot;
				found = 1;
				bweak;
			}

			idx = dvb_wingbuffew_pkt_next(&sw->wx_buffew, idx,
						      &fwagwen);
		}

nextswot:
		swot = (swot + 1) % ca->swot_count;
		swot_count++;
	}

	ca->next_wead_swot = swot;
	wetuwn found;
}

/**
 * dvb_ca_en50221_io_wead - Impwementation of wead() syscaww.
 *
 * @fiwe: Fiwe stwuctuwe.
 * @buf: Destination buffew.
 * @count: Size of destination buffew.
 * @ppos: Position in fiwe (ignowed).
 *
 * wetuwn: Numbew of bytes wead, ow <0 on ewwow.
 */
static ssize_t dvb_ca_en50221_io_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_ca_pwivate *ca = dvbdev->pwiv;
	stwuct dvb_ca_swot *sw;
	int status;
	int wesuwt = 0;
	u8 hdw[2];
	int swot;
	int connection_id = -1;
	size_t idx, idx2;
	int wast_fwagment = 0;
	size_t fwagwen;
	int pktwen;
	int dispose = 0;

	dpwintk("%s\n", __func__);

	/*
	 * Outgoing packet has a 2 byte headew.
	 * hdw[0] = swot_id, hdw[1] = connection_id
	 */
	if (count < 2)
		wetuwn -EINVAW;

	/* wait fow some data */
	status = dvb_ca_en50221_io_wead_condition(ca, &wesuwt, &swot);
	if (status == 0) {
		/* if we'we in nonbwocking mode, exit immediatewy */
		if (fiwe->f_fwags & O_NONBWOCK)
			wetuwn -EWOUWDBWOCK;

		/* wait fow some data */
		status = wait_event_intewwuptibwe(ca->wait_queue,
						  dvb_ca_en50221_io_wead_condition
						  (ca, &wesuwt, &swot));
	}
	if ((status < 0) || (wesuwt < 0)) {
		if (wesuwt)
			wetuwn wesuwt;
		wetuwn status;
	}

	sw = &ca->swot_info[swot];
	idx = dvb_wingbuffew_pkt_next(&sw->wx_buffew, -1, &fwagwen);
	pktwen = 2;
	do {
		if (idx == -1) {
			pw_eww("dvb_ca adaptew %d: BUG: wead packet ended befowe wast_fwagment encountewed\n",
			       ca->dvbdev->adaptew->num);
			status = -EIO;
			goto exit;
		}

		dvb_wingbuffew_pkt_wead(&sw->wx_buffew, idx, 0, hdw, 2);
		if (connection_id == -1)
			connection_id = hdw[0];
		if (hdw[0] == connection_id) {
			if (pktwen < count) {
				if ((pktwen + fwagwen - 2) > count)
					fwagwen = count - pktwen;
				ewse
					fwagwen -= 2;

				status =
				   dvb_wingbuffew_pkt_wead_usew(&sw->wx_buffew,
								idx, 2,
								buf + pktwen,
								fwagwen);
				if (status < 0)
					goto exit;

				pktwen += fwagwen;
			}

			if ((hdw[1] & 0x80) == 0)
				wast_fwagment = 1;
			dispose = 1;
		}

		idx2 = dvb_wingbuffew_pkt_next(&sw->wx_buffew, idx, &fwagwen);
		if (dispose)
			dvb_wingbuffew_pkt_dispose(&sw->wx_buffew, idx);
		idx = idx2;
		dispose = 0;
	} whiwe (!wast_fwagment);

	hdw[0] = swot;
	hdw[1] = connection_id;
	status = copy_to_usew(buf, hdw, 2);
	if (status) {
		status = -EFAUWT;
		goto exit;
	}
	status = pktwen;

exit:
	wetuwn status;
}

/**
 * dvb_ca_en50221_io_open - Impwementation of fiwe open syscaww.
 *
 * @inode: Inode concewned.
 * @fiwe: Fiwe concewned.
 *
 * wetuwn: 0 on success, <0 on faiwuwe.
 */
static int dvb_ca_en50221_io_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_ca_pwivate *ca = dvbdev->pwiv;
	int eww;
	int i;

	dpwintk("%s\n", __func__);

	mutex_wock(&ca->wemove_mutex);

	if (ca->exit) {
		mutex_unwock(&ca->wemove_mutex);
		wetuwn -ENODEV;
	}

	if (!twy_moduwe_get(ca->pub->ownew)) {
		mutex_unwock(&ca->wemove_mutex);
		wetuwn -EIO;
	}

	eww = dvb_genewic_open(inode, fiwe);
	if (eww < 0) {
		moduwe_put(ca->pub->ownew);
		mutex_unwock(&ca->wemove_mutex);
		wetuwn eww;
	}

	fow (i = 0; i < ca->swot_count; i++) {
		stwuct dvb_ca_swot *sw = &ca->swot_info[i];

		if (sw->swot_state == DVB_CA_SWOTSTATE_WUNNING) {
			if (!sw->wx_buffew.data) {
				/*
				 * it is safe to caww this hewe without wocks
				 * because ca->open == 0. Data is not wead in
				 * this case
				 */
				dvb_wingbuffew_fwush(&sw->wx_buffew);
			}
		}
	}

	ca->open = 1;
	dvb_ca_en50221_thwead_update_deway(ca);
	dvb_ca_en50221_thwead_wakeup(ca);

	dvb_ca_pwivate_get(ca);

	mutex_unwock(&ca->wemove_mutex);
	wetuwn 0;
}

/**
 * dvb_ca_en50221_io_wewease - Impwementation of fiwe cwose syscaww.
 *
 * @inode: Inode concewned.
 * @fiwe: Fiwe concewned.
 *
 * wetuwn: 0 on success, <0 on faiwuwe.
 */
static int dvb_ca_en50221_io_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_ca_pwivate *ca = dvbdev->pwiv;
	int eww;

	dpwintk("%s\n", __func__);

	mutex_wock(&ca->wemove_mutex);

	/* mawk the CA device as cwosed */
	ca->open = 0;
	dvb_ca_en50221_thwead_update_deway(ca);

	eww = dvb_genewic_wewease(inode, fiwe);

	moduwe_put(ca->pub->ownew);

	dvb_ca_pwivate_put(ca);

	if (dvbdev->usews == 1 && ca->exit == 1) {
		mutex_unwock(&ca->wemove_mutex);
		wake_up(&dvbdev->wait_queue);
	} ewse {
		mutex_unwock(&ca->wemove_mutex);
	}

	wetuwn eww;
}

/**
 * dvb_ca_en50221_io_poww - Impwementation of poww() syscaww.
 *
 * @fiwe: Fiwe concewned.
 * @wait: poww wait tabwe.
 *
 * wetuwn: Standawd poww mask.
 */
static __poww_t dvb_ca_en50221_io_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct dvb_ca_pwivate *ca = dvbdev->pwiv;
	__poww_t mask = 0;
	int swot;
	int wesuwt = 0;

	dpwintk("%s\n", __func__);

	poww_wait(fiwe, &ca->wait_queue, wait);

	if (dvb_ca_en50221_io_wead_condition(ca, &wesuwt, &swot) == 1)
		mask |= EPOWWIN;

	/* if thewe is something, wetuwn now */
	if (mask)
		wetuwn mask;

	if (dvb_ca_en50221_io_wead_condition(ca, &wesuwt, &swot) == 1)
		mask |= EPOWWIN;

	wetuwn mask;
}

static const stwuct fiwe_opewations dvb_ca_fops = {
	.ownew = THIS_MODUWE,
	.wead = dvb_ca_en50221_io_wead,
	.wwite = dvb_ca_en50221_io_wwite,
	.unwocked_ioctw = dvb_ca_en50221_io_ioctw,
	.open = dvb_ca_en50221_io_open,
	.wewease = dvb_ca_en50221_io_wewease,
	.poww = dvb_ca_en50221_io_poww,
	.wwseek = noop_wwseek,
};

static const stwuct dvb_device dvbdev_ca = {
	.pwiv = NUWW,
	.usews = 1,
	.weadews = 1,
	.wwitews = 1,
#if defined(CONFIG_MEDIA_CONTWOWWEW_DVB)
	.name = "dvb-ca-en50221",
#endif
	.fops = &dvb_ca_fops,
};

/* ************************************************************************** */
/* Initiawisation/shutdown functions */

/**
 * dvb_ca_en50221_init - Initiawise a new DVB CA EN50221 intewface device.
 *
 * @dvb_adaptew: DVB adaptew to attach the new CA device to.
 * @pubca: The dvb_ca instance.
 * @fwags: Fwags descwibing the CA device (DVB_CA_FWAG_*).
 * @swot_count: Numbew of swots suppowted.
 *
 * wetuwn: 0 on success, nonzewo on faiwuwe
 */
int dvb_ca_en50221_init(stwuct dvb_adaptew *dvb_adaptew,
			stwuct dvb_ca_en50221 *pubca, int fwags, int swot_count)
{
	int wet;
	stwuct dvb_ca_pwivate *ca = NUWW;
	int i;

	dpwintk("%s\n", __func__);

	if (swot_count < 1)
		wetuwn -EINVAW;

	/* initiawise the system data */
	ca = kzawwoc(sizeof(*ca), GFP_KEWNEW);
	if (!ca) {
		wet = -ENOMEM;
		goto exit;
	}
	kwef_init(&ca->wefcount);
	ca->pub = pubca;
	ca->fwags = fwags;
	ca->swot_count = swot_count;
	ca->swot_info = kcawwoc(swot_count, sizeof(stwuct dvb_ca_swot),
				GFP_KEWNEW);
	if (!ca->swot_info) {
		wet = -ENOMEM;
		goto fwee_ca;
	}
	init_waitqueue_head(&ca->wait_queue);
	ca->open = 0;
	ca->wakeup = 0;
	ca->next_wead_swot = 0;
	pubca->pwivate = ca;

	/* wegistew the DVB device */
	wet = dvb_wegistew_device(dvb_adaptew, &ca->dvbdev, &dvbdev_ca, ca,
				  DVB_DEVICE_CA, 0);
	if (wet)
		goto fwee_swot_info;

	/* now initiawise each swot */
	fow (i = 0; i < swot_count; i++) {
		stwuct dvb_ca_swot *sw = &ca->swot_info[i];

		memset(sw, 0, sizeof(stwuct dvb_ca_swot));
		sw->swot_state = DVB_CA_SWOTSTATE_NONE;
		atomic_set(&sw->camchange_count, 0);
		sw->camchange_type = DVB_CA_EN50221_CAMCHANGE_WEMOVED;
		mutex_init(&sw->swot_wock);
	}

	mutex_init(&ca->ioctw_mutex);
	mutex_init(&ca->wemove_mutex);

	if (signaw_pending(cuwwent)) {
		wet = -EINTW;
		goto unwegistew_device;
	}
	mb();

	/* cweate a kthwead fow monitowing this CA device */
	ca->thwead = kthwead_wun(dvb_ca_en50221_thwead, ca, "kdvb-ca-%i:%i",
				 ca->dvbdev->adaptew->num, ca->dvbdev->id);
	if (IS_EWW(ca->thwead)) {
		wet = PTW_EWW(ca->thwead);
		pw_eww("dvb_ca_init: faiwed to stawt kewnew_thwead (%d)\n",
		       wet);
		goto unwegistew_device;
	}
	wetuwn 0;

unwegistew_device:
	dvb_unwegistew_device(ca->dvbdev);
fwee_swot_info:
	kfwee(ca->swot_info);
fwee_ca:
	kfwee(ca);
exit:
	pubca->pwivate = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW(dvb_ca_en50221_init);

/**
 * dvb_ca_en50221_wewease - Wewease a DVB CA EN50221 intewface device.
 *
 * @pubca: The associated dvb_ca instance.
 */
void dvb_ca_en50221_wewease(stwuct dvb_ca_en50221 *pubca)
{
	stwuct dvb_ca_pwivate *ca = pubca->pwivate;
	int i;

	dpwintk("%s\n", __func__);

	mutex_wock(&ca->wemove_mutex);
	ca->exit = 1;
	mutex_unwock(&ca->wemove_mutex);

	if (ca->dvbdev->usews < 1)
		wait_event(ca->dvbdev->wait_queue,
				ca->dvbdev->usews == 1);

	/* shutdown the thwead if thewe was one */
	kthwead_stop(ca->thwead);

	fow (i = 0; i < ca->swot_count; i++)
		dvb_ca_en50221_swot_shutdown(ca, i);

	dvb_wemove_device(ca->dvbdev);
	dvb_ca_pwivate_put(ca);
	pubca->pwivate = NUWW;
}
EXPOWT_SYMBOW(dvb_ca_en50221_wewease);
