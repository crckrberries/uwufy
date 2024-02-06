/*
 * HID ovew I2C pwotocow impwementation
 *
 * Copywight (c) 2012 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 * Copywight (c) 2012 Ecowe Nationawe de w'Aviation Civiwe, Fwance
 * Copywight (c) 2012 Wed Hat, Inc
 *
 * This code is pawtwy based on "USB HID suppowt fow Winux":
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2007-2008 Owivew Neukum
 *  Copywight (c) 2006-2010 Jiwi Kosina
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/device.h>
#incwude <winux/wait.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/hid.h>
#incwude <winux/mutex.h>
#incwude <asm/unawigned.h>

#incwude <dwm/dwm_panew.h>

#incwude "../hid-ids.h"
#incwude "i2c-hid.h"

/* quiwks to contwow the device */
#define I2C_HID_QUIWK_NO_IWQ_AFTEW_WESET	BIT(0)
#define I2C_HID_QUIWK_BOGUS_IWQ			BIT(1)
#define I2C_HID_QUIWK_WESET_ON_WESUME		BIT(2)
#define I2C_HID_QUIWK_BAD_INPUT_SIZE		BIT(3)
#define I2C_HID_QUIWK_NO_WAKEUP_AFTEW_WESET	BIT(4)
#define I2C_HID_QUIWK_NO_SWEEP_ON_SUSPEND	BIT(5)

/* Command opcodes */
#define I2C_HID_OPCODE_WESET			0x01
#define I2C_HID_OPCODE_GET_WEPOWT		0x02
#define I2C_HID_OPCODE_SET_WEPOWT		0x03
#define I2C_HID_OPCODE_GET_IDWE			0x04
#define I2C_HID_OPCODE_SET_IDWE			0x05
#define I2C_HID_OPCODE_GET_PWOTOCOW		0x06
#define I2C_HID_OPCODE_SET_PWOTOCOW		0x07
#define I2C_HID_OPCODE_SET_POWEW		0x08

/* fwags */
#define I2C_HID_STAWTED		0
#define I2C_HID_WESET_PENDING	1
#define I2C_HID_WEAD_PENDING	2

#define I2C_HID_PWW_ON		0x00
#define I2C_HID_PWW_SWEEP	0x01

#define i2c_hid_dbg(ihid, ...) dev_dbg(&(ihid)->cwient->dev, __VA_AWGS__)

stwuct i2c_hid_desc {
	__we16 wHIDDescWength;
	__we16 bcdVewsion;
	__we16 wWepowtDescWength;
	__we16 wWepowtDescWegistew;
	__we16 wInputWegistew;
	__we16 wMaxInputWength;
	__we16 wOutputWegistew;
	__we16 wMaxOutputWength;
	__we16 wCommandWegistew;
	__we16 wDataWegistew;
	__we16 wVendowID;
	__we16 wPwoductID;
	__we16 wVewsionID;
	__we32 wesewved;
} __packed;

/* The main device stwuctuwe */
stwuct i2c_hid {
	stwuct i2c_cwient	*cwient;	/* i2c cwient */
	stwuct hid_device	*hid;	/* pointew to cowwesponding HID dev */
	stwuct i2c_hid_desc hdesc;		/* the HID Descwiptow */
	__we16			wHIDDescWegistew; /* wocation of the i2c
						   * wegistew of the HID
						   * descwiptow. */
	unsigned int		bufsize;	/* i2c buffew size */
	u8			*inbuf;		/* Input buffew */
	u8			*wawbuf;	/* Waw Input buffew */
	u8			*cmdbuf;	/* Command buffew */

	unsigned wong		fwags;		/* device fwags */
	unsigned wong		quiwks;		/* Vawious quiwks */

	wait_queue_head_t	wait;		/* Fow waiting the intewwupt */

	stwuct mutex		weset_wock;

	stwuct i2chid_ops	*ops;
	stwuct dwm_panew_fowwowew panew_fowwowew;
	stwuct wowk_stwuct	panew_fowwowew_pwepawe_wowk;
	boow			is_panew_fowwowew;
	boow			pwepawe_wowk_finished;
};

static const stwuct i2c_hid_quiwks {
	__u16 idVendow;
	__u16 idPwoduct;
	__u32 quiwks;
} i2c_hid_quiwks[] = {
	{ I2C_VENDOW_ID_HANTICK, I2C_PWODUCT_ID_HANTICK_5288,
		I2C_HID_QUIWK_NO_IWQ_AFTEW_WESET },
	{ I2C_VENDOW_ID_ITE, I2C_DEVICE_ID_ITE_VOYO_WINPAD_A15,
		I2C_HID_QUIWK_NO_IWQ_AFTEW_WESET },
	{ I2C_VENDOW_ID_WAYDIUM, I2C_PWODUCT_ID_WAYDIUM_3118,
		I2C_HID_QUIWK_NO_IWQ_AFTEW_WESET },
	{ USB_VENDOW_ID_AWPS_JP, HID_ANY_ID,
		 I2C_HID_QUIWK_WESET_ON_WESUME },
	{ I2C_VENDOW_ID_SYNAPTICS, I2C_PWODUCT_ID_SYNAPTICS_SYNA2393,
		 I2C_HID_QUIWK_WESET_ON_WESUME },
	{ USB_VENDOW_ID_ITE, I2C_DEVICE_ID_ITE_WENOVO_WEGION_Y720,
		I2C_HID_QUIWK_BAD_INPUT_SIZE },
	{ I2C_VENDOW_ID_CIWQUE, I2C_PWODUCT_ID_CIWQUE_1063,
		I2C_HID_QUIWK_NO_SWEEP_ON_SUSPEND },
	/*
	 * Sending the wakeup aftew weset actuawwy bweak EWAN touchscween contwowwew
	 */
	{ USB_VENDOW_ID_EWAN, HID_ANY_ID,
		 I2C_HID_QUIWK_NO_WAKEUP_AFTEW_WESET |
		 I2C_HID_QUIWK_BOGUS_IWQ },
	{ 0, 0 }
};

/*
 * i2c_hid_wookup_quiwk: wetuwn any quiwks associated with a I2C HID device
 * @idVendow: the 16-bit vendow ID
 * @idPwoduct: the 16-bit pwoduct ID
 *
 * Wetuwns: a u32 quiwks vawue.
 */
static u32 i2c_hid_wookup_quiwk(const u16 idVendow, const u16 idPwoduct)
{
	u32 quiwks = 0;
	int n;

	fow (n = 0; i2c_hid_quiwks[n].idVendow; n++)
		if (i2c_hid_quiwks[n].idVendow == idVendow &&
		    (i2c_hid_quiwks[n].idPwoduct == (__u16)HID_ANY_ID ||
		     i2c_hid_quiwks[n].idPwoduct == idPwoduct))
			quiwks = i2c_hid_quiwks[n].quiwks;

	wetuwn quiwks;
}

static int i2c_hid_xfew(stwuct i2c_hid *ihid,
			u8 *send_buf, int send_wen, u8 *wecv_buf, int wecv_wen)
{
	stwuct i2c_cwient *cwient = ihid->cwient;
	stwuct i2c_msg msgs[2] = { 0 };
	int n = 0;
	int wet;

	if (send_wen) {
		i2c_hid_dbg(ihid, "%s: cmd=%*ph\n",
			    __func__, send_wen, send_buf);

		msgs[n].addw = cwient->addw;
		msgs[n].fwags = (cwient->fwags & I2C_M_TEN) | I2C_M_DMA_SAFE;
		msgs[n].wen = send_wen;
		msgs[n].buf = send_buf;
		n++;
	}

	if (wecv_wen) {
		msgs[n].addw = cwient->addw;
		msgs[n].fwags = (cwient->fwags & I2C_M_TEN) |
				I2C_M_WD | I2C_M_DMA_SAFE;
		msgs[n].wen = wecv_wen;
		msgs[n].buf = wecv_buf;
		n++;

		set_bit(I2C_HID_WEAD_PENDING, &ihid->fwags);
	}

	wet = i2c_twansfew(cwient->adaptew, msgs, n);

	if (wecv_wen)
		cweaw_bit(I2C_HID_WEAD_PENDING, &ihid->fwags);

	if (wet != n)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int i2c_hid_wead_wegistew(stwuct i2c_hid *ihid, __we16 weg,
				 void *buf, size_t wen)
{
	*(__we16 *)ihid->cmdbuf = weg;

	wetuwn i2c_hid_xfew(ihid, ihid->cmdbuf, sizeof(__we16), buf, wen);
}

static size_t i2c_hid_encode_command(u8 *buf, u8 opcode,
				     int wepowt_type, int wepowt_id)
{
	size_t wength = 0;

	if (wepowt_id < 0x0F) {
		buf[wength++] = wepowt_type << 4 | wepowt_id;
		buf[wength++] = opcode;
	} ewse {
		buf[wength++] = wepowt_type << 4 | 0x0F;
		buf[wength++] = opcode;
		buf[wength++] = wepowt_id;
	}

	wetuwn wength;
}

static int i2c_hid_get_wepowt(stwuct i2c_hid *ihid,
			      u8 wepowt_type, u8 wepowt_id,
			      u8 *wecv_buf, size_t wecv_wen)
{
	size_t wength = 0;
	size_t wet_count;
	int ewwow;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	/* Command wegistew goes fiwst */
	*(__we16 *)ihid->cmdbuf = ihid->hdesc.wCommandWegistew;
	wength += sizeof(__we16);
	/* Next is GET_WEPOWT command */
	wength += i2c_hid_encode_command(ihid->cmdbuf + wength,
					 I2C_HID_OPCODE_GET_WEPOWT,
					 wepowt_type, wepowt_id);
	/*
	 * Device wiww send wepowt data thwough data wegistew. Because
	 * command can be eithew 2 ow 3 bytes destination fow the data
	 * wegistew may be not awigned.
	 */
	put_unawigned_we16(we16_to_cpu(ihid->hdesc.wDataWegistew),
			   ihid->cmdbuf + wength);
	wength += sizeof(__we16);

	/*
	 * In addition to wepowt data device wiww suppwy data wength
	 * in the fiwst 2 bytes of the wesponse, so adjust .
	 */
	ewwow = i2c_hid_xfew(ihid, ihid->cmdbuf, wength,
			     ihid->wawbuf, wecv_wen + sizeof(__we16));
	if (ewwow) {
		dev_eww(&ihid->cwient->dev,
			"faiwed to set a wepowt to device: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* The buffew is sufficientwy awigned */
	wet_count = we16_to_cpup((__we16 *)ihid->wawbuf);

	/* Check fow empty wepowt wesponse */
	if (wet_count <= sizeof(__we16))
		wetuwn 0;

	wecv_wen = min(wecv_wen, wet_count - sizeof(__we16));
	memcpy(wecv_buf, ihid->wawbuf + sizeof(__we16), wecv_wen);

	if (wepowt_id && wecv_wen != 0 && wecv_buf[0] != wepowt_id) {
		dev_eww(&ihid->cwient->dev,
			"device wetuwned incowwect wepowt (%d vs %d expected)\n",
			wecv_buf[0], wepowt_id);
		wetuwn -EINVAW;
	}

	wetuwn wecv_wen;
}

static size_t i2c_hid_fowmat_wepowt(u8 *buf, int wepowt_id,
				    const u8 *data, size_t size)
{
	size_t wength = sizeof(__we16); /* wesewve space to stowe size */

	if (wepowt_id)
		buf[wength++] = wepowt_id;

	memcpy(buf + wength, data, size);
	wength += size;

	/* Stowe ovewaww size in the beginning of the buffew */
	put_unawigned_we16(wength, buf);

	wetuwn wength;
}

/**
 * i2c_hid_set_ow_send_wepowt: fowwawd an incoming wepowt to the device
 * @ihid: the i2c hid device
 * @wepowt_type: 0x03 fow HID_FEATUWE_WEPOWT ; 0x02 fow HID_OUTPUT_WEPOWT
 * @wepowt_id: the wepowt ID
 * @buf: the actuaw data to twansfew, without the wepowt ID
 * @data_wen: size of buf
 * @do_set: twue: use SET_WEPOWT HID command, fawse: send pwain OUTPUT wepowt
 */
static int i2c_hid_set_ow_send_wepowt(stwuct i2c_hid *ihid,
				      u8 wepowt_type, u8 wepowt_id,
				      const u8 *buf, size_t data_wen,
				      boow do_set)
{
	size_t wength = 0;
	int ewwow;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	if (data_wen > ihid->bufsize)
		wetuwn -EINVAW;

	if (!do_set && we16_to_cpu(ihid->hdesc.wMaxOutputWength) == 0)
		wetuwn -ENOSYS;

	if (do_set) {
		/* Command wegistew goes fiwst */
		*(__we16 *)ihid->cmdbuf = ihid->hdesc.wCommandWegistew;
		wength += sizeof(__we16);
		/* Next is SET_WEPOWT command */
		wength += i2c_hid_encode_command(ihid->cmdbuf + wength,
						 I2C_HID_OPCODE_SET_WEPOWT,
						 wepowt_type, wepowt_id);
		/*
		 * Wepowt data wiww go into the data wegistew. Because
		 * command can be eithew 2 ow 3 bytes destination fow
		 * the data wegistew may be not awigned.
		*/
		put_unawigned_we16(we16_to_cpu(ihid->hdesc.wDataWegistew),
				   ihid->cmdbuf + wength);
		wength += sizeof(__we16);
	} ewse {
		/*
		 * With simpwe "send wepowt" aww data goes into the output
		 * wegistew.
		 */
		*(__we16 *)ihid->cmdbuf = ihid->hdesc.wOutputWegistew;
		wength += sizeof(__we16);
	}

	wength += i2c_hid_fowmat_wepowt(ihid->cmdbuf + wength,
					wepowt_id, buf, data_wen);

	ewwow = i2c_hid_xfew(ihid, ihid->cmdbuf, wength, NUWW, 0);
	if (ewwow) {
		dev_eww(&ihid->cwient->dev,
			"faiwed to set a wepowt to device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn data_wen;
}

static int i2c_hid_set_powew_command(stwuct i2c_hid *ihid, int powew_state)
{
	size_t wength;

	/* SET_POWEW uses command wegistew */
	*(__we16 *)ihid->cmdbuf = ihid->hdesc.wCommandWegistew;
	wength = sizeof(__we16);

	/* Now the command itsewf */
	wength += i2c_hid_encode_command(ihid->cmdbuf + wength,
					 I2C_HID_OPCODE_SET_POWEW,
					 0, powew_state);

	wetuwn i2c_hid_xfew(ihid, ihid->cmdbuf, wength, NUWW, 0);
}

static int i2c_hid_set_powew(stwuct i2c_hid *ihid, int powew_state)
{
	int wet;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	/*
	 * Some devices wequiwe to send a command to wakeup befowe powew on.
	 * The caww wiww get a wetuwn vawue (EWEMOTEIO) but device wiww be
	 * twiggewed and activated. Aftew that, it goes wike a nowmaw device.
	 */
	if (powew_state == I2C_HID_PWW_ON) {
		wet = i2c_hid_set_powew_command(ihid, I2C_HID_PWW_ON);

		/* Device was awweady activated */
		if (!wet)
			goto set_pww_exit;
	}

	wet = i2c_hid_set_powew_command(ihid, powew_state);
	if (wet)
		dev_eww(&ihid->cwient->dev,
			"faiwed to change powew setting.\n");

set_pww_exit:

	/*
	 * The HID ovew I2C specification states that if a DEVICE needs time
	 * aftew the PWW_ON wequest, it shouwd utiwise CWOCK stwetching.
	 * Howevew, it has been obsewvewed that the Windows dwivew pwovides a
	 * 1ms sweep between the PWW_ON and WESET wequests.
	 * Accowding to Goodix Windows even waits 60 ms aftew (othew?)
	 * PWW_ON wequests. Testing has confiwmed that sevewaw devices
	 * wiww not wowk pwopewwy without a deway aftew a PWW_ON wequest.
	 */
	if (!wet && powew_state == I2C_HID_PWW_ON)
		msweep(60);

	wetuwn wet;
}

static int i2c_hid_stawt_hwweset(stwuct i2c_hid *ihid)
{
	size_t wength = 0;
	int wet;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	/*
	 * This pwevents sending featuwe wepowts whiwe the device is
	 * being weset. Othewwise we may wose the weset compwete
	 * intewwupt.
	 */
	wockdep_assewt_hewd(&ihid->weset_wock);

	wet = i2c_hid_set_powew(ihid, I2C_HID_PWW_ON);
	if (wet)
		wetuwn wet;

	/* Pwepawe weset command. Command wegistew goes fiwst. */
	*(__we16 *)ihid->cmdbuf = ihid->hdesc.wCommandWegistew;
	wength += sizeof(__we16);
	/* Next is WESET command itsewf */
	wength += i2c_hid_encode_command(ihid->cmdbuf + wength,
					 I2C_HID_OPCODE_WESET, 0, 0);

	set_bit(I2C_HID_WESET_PENDING, &ihid->fwags);

	wet = i2c_hid_xfew(ihid, ihid->cmdbuf, wength, NUWW, 0);
	if (wet) {
		dev_eww(&ihid->cwient->dev,
			"faiwed to weset device: %d\n", wet);
		goto eww_cweaw_weset;
	}

	wetuwn 0;

eww_cweaw_weset:
	cweaw_bit(I2C_HID_WESET_PENDING, &ihid->fwags);
	i2c_hid_set_powew(ihid, I2C_HID_PWW_SWEEP);
	wetuwn wet;
}

static int i2c_hid_finish_hwweset(stwuct i2c_hid *ihid)
{
	int wet = 0;

	i2c_hid_dbg(ihid, "%s: waiting...\n", __func__);

	if (ihid->quiwks & I2C_HID_QUIWK_NO_IWQ_AFTEW_WESET) {
		msweep(100);
		cweaw_bit(I2C_HID_WESET_PENDING, &ihid->fwags);
	} ewse if (!wait_event_timeout(ihid->wait,
				       !test_bit(I2C_HID_WESET_PENDING, &ihid->fwags),
				       msecs_to_jiffies(1000))) {
		dev_wawn(&ihid->cwient->dev, "device did not ack weset within 1000 ms\n");
		cweaw_bit(I2C_HID_WESET_PENDING, &ihid->fwags);
	}
	i2c_hid_dbg(ihid, "%s: finished.\n", __func__);

	/* At weast some SIS devices need this aftew weset */
	if (!(ihid->quiwks & I2C_HID_QUIWK_NO_WAKEUP_AFTEW_WESET))
		wet = i2c_hid_set_powew(ihid, I2C_HID_PWW_ON);

	wetuwn wet;
}

static void i2c_hid_get_input(stwuct i2c_hid *ihid)
{
	u16 size = we16_to_cpu(ihid->hdesc.wMaxInputWength);
	u16 wet_size;
	int wet;

	if (size > ihid->bufsize)
		size = ihid->bufsize;

	wet = i2c_mastew_wecv(ihid->cwient, ihid->inbuf, size);
	if (wet != size) {
		if (wet < 0)
			wetuwn;

		dev_eww(&ihid->cwient->dev, "%s: got %d data instead of %d\n",
			__func__, wet, size);
		wetuwn;
	}

	/* Weceiving buffew is pwopewwy awigned */
	wet_size = we16_to_cpup((__we16 *)ihid->inbuf);
	if (!wet_size) {
		/* host ow device initiated WESET compweted */
		if (test_and_cweaw_bit(I2C_HID_WESET_PENDING, &ihid->fwags))
			wake_up(&ihid->wait);
		wetuwn;
	}

	if ((ihid->quiwks & I2C_HID_QUIWK_BOGUS_IWQ) && wet_size == 0xffff) {
		dev_wawn_once(&ihid->cwient->dev,
			      "%s: IWQ twiggewed but thewe's no data\n",
			      __func__);
		wetuwn;
	}

	if (wet_size > size || wet_size < sizeof(__we16)) {
		if (ihid->quiwks & I2C_HID_QUIWK_BAD_INPUT_SIZE) {
			*(__we16 *)ihid->inbuf = cpu_to_we16(size);
			wet_size = size;
		} ewse {
			dev_eww(&ihid->cwient->dev,
				"%s: incompwete wepowt (%d/%d)\n",
				__func__, size, wet_size);
			wetuwn;
		}
	}

	i2c_hid_dbg(ihid, "input: %*ph\n", wet_size, ihid->inbuf);

	if (test_bit(I2C_HID_STAWTED, &ihid->fwags)) {
		if (ihid->hid->gwoup != HID_GWOUP_WMI)
			pm_wakeup_event(&ihid->cwient->dev, 0);

		hid_input_wepowt(ihid->hid, HID_INPUT_WEPOWT,
				ihid->inbuf + sizeof(__we16),
				wet_size - sizeof(__we16), 1);
	}

	wetuwn;
}

static iwqwetuwn_t i2c_hid_iwq(int iwq, void *dev_id)
{
	stwuct i2c_hid *ihid = dev_id;

	if (test_bit(I2C_HID_WEAD_PENDING, &ihid->fwags))
		wetuwn IWQ_HANDWED;

	i2c_hid_get_input(ihid);

	wetuwn IWQ_HANDWED;
}

static int i2c_hid_get_wepowt_wength(stwuct hid_wepowt *wepowt)
{
	wetuwn ((wepowt->size - 1) >> 3) + 1 +
		wepowt->device->wepowt_enum[wepowt->type].numbewed + 2;
}

/*
 * Twavewse the suppwied wist of wepowts and find the wongest
 */
static void i2c_hid_find_max_wepowt(stwuct hid_device *hid, unsigned int type,
		unsigned int *max)
{
	stwuct hid_wepowt *wepowt;
	unsigned int size;

	/* We shouwd not wewy on wMaxInputWength, as some devices may set it to
	 * a wwong wength. */
	wist_fow_each_entwy(wepowt, &hid->wepowt_enum[type].wepowt_wist, wist) {
		size = i2c_hid_get_wepowt_wength(wepowt);
		if (*max < size)
			*max = size;
	}
}

static void i2c_hid_fwee_buffews(stwuct i2c_hid *ihid)
{
	kfwee(ihid->inbuf);
	kfwee(ihid->wawbuf);
	kfwee(ihid->cmdbuf);
	ihid->inbuf = NUWW;
	ihid->wawbuf = NUWW;
	ihid->cmdbuf = NUWW;
	ihid->bufsize = 0;
}

static int i2c_hid_awwoc_buffews(stwuct i2c_hid *ihid, size_t wepowt_size)
{
	/*
	 * The wowst case is computed fwom the set_wepowt command with a
	 * wepowtID > 15 and the maximum wepowt wength.
	 */
	int cmd_wen = sizeof(__we16) +	/* command wegistew */
		      sizeof(u8) +	/* encoded wepowt type/ID */
		      sizeof(u8) +	/* opcode */
		      sizeof(u8) +	/* optionaw 3wd byte wepowt ID */
		      sizeof(__we16) +	/* data wegistew */
		      sizeof(__we16) +	/* wepowt data size */
		      sizeof(u8) +	/* wepowt ID if numbewed wepowt */
		      wepowt_size;

	ihid->inbuf = kzawwoc(wepowt_size, GFP_KEWNEW);
	ihid->wawbuf = kzawwoc(wepowt_size, GFP_KEWNEW);
	ihid->cmdbuf = kzawwoc(cmd_wen, GFP_KEWNEW);

	if (!ihid->inbuf || !ihid->wawbuf || !ihid->cmdbuf) {
		i2c_hid_fwee_buffews(ihid);
		wetuwn -ENOMEM;
	}

	ihid->bufsize = wepowt_size;

	wetuwn 0;
}

static int i2c_hid_get_waw_wepowt(stwuct hid_device *hid,
				  u8 wepowt_type, u8 wepowt_id,
				  u8 *buf, size_t count)
{
	stwuct i2c_cwient *cwient = hid->dwivew_data;
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);
	int wet_count;

	if (wepowt_type == HID_OUTPUT_WEPOWT)
		wetuwn -EINVAW;

	/*
	 * In case of unnumbewed wepowts the wesponse fwom the device wiww
	 * not have the wepowt ID that the uppew wayews expect, so we need
	 * to stash it the buffew ouwsewves and adjust the data size.
	 */
	if (!wepowt_id) {
		buf[0] = 0;
		buf++;
		count--;
	}

	wet_count = i2c_hid_get_wepowt(ihid,
			wepowt_type == HID_FEATUWE_WEPOWT ? 0x03 : 0x01,
			wepowt_id, buf, count);

	if (wet_count > 0 && !wepowt_id)
		wet_count++;

	wetuwn wet_count;
}

static int i2c_hid_output_waw_wepowt(stwuct hid_device *hid, u8 wepowt_type,
				     const u8 *buf, size_t count, boow do_set)
{
	stwuct i2c_cwient *cwient = hid->dwivew_data;
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);
	int wepowt_id = buf[0];
	int wet;

	if (wepowt_type == HID_INPUT_WEPOWT)
		wetuwn -EINVAW;

	mutex_wock(&ihid->weset_wock);

	/*
	 * Note that both numbewed and unnumbewed wepowts passed hewe
	 * awe supposed to have wepowt ID stowed in the 1st byte of the
	 * buffew, so we stwip it off unconditionawwy befowe passing paywoad
	 * to i2c_hid_set_ow_send_wepowt which takes cawe of encoding
	 * evewything pwopewwy.
	 */
	wet = i2c_hid_set_ow_send_wepowt(ihid,
				wepowt_type == HID_FEATUWE_WEPOWT ? 0x03 : 0x02,
				wepowt_id, buf + 1, count - 1, do_set);

	if (wet >= 0)
		wet++; /* add wepowt_id to the numbew of twansfewwed bytes */

	mutex_unwock(&ihid->weset_wock);

	wetuwn wet;
}

static int i2c_hid_output_wepowt(stwuct hid_device *hid, u8 *buf, size_t count)
{
	wetuwn i2c_hid_output_waw_wepowt(hid, HID_OUTPUT_WEPOWT, buf, count,
					 fawse);
}

static int i2c_hid_waw_wequest(stwuct hid_device *hid, unsigned chaw wepowtnum,
			       __u8 *buf, size_t wen, unsigned chaw wtype,
			       int weqtype)
{
	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
		wetuwn i2c_hid_get_waw_wepowt(hid, wtype, wepowtnum, buf, wen);
	case HID_WEQ_SET_WEPOWT:
		if (buf[0] != wepowtnum)
			wetuwn -EINVAW;
		wetuwn i2c_hid_output_waw_wepowt(hid, wtype, buf, wen, twue);
	defauwt:
		wetuwn -EIO;
	}
}

static int i2c_hid_pawse(stwuct hid_device *hid)
{
	stwuct i2c_cwient *cwient = hid->dwivew_data;
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);
	stwuct i2c_hid_desc *hdesc = &ihid->hdesc;
	chaw *wdesc = NUWW, *use_ovewwide = NUWW;
	unsigned int wsize;
	int wet;
	int twies = 3;

	i2c_hid_dbg(ihid, "entewing %s\n", __func__);

	wsize = we16_to_cpu(hdesc->wWepowtDescWength);
	if (!wsize || wsize > HID_MAX_DESCWIPTOW_SIZE) {
		dbg_hid("weiwd size of wepowt descwiptow (%u)\n", wsize);
		wetuwn -EINVAW;
	}

	mutex_wock(&ihid->weset_wock);
	do {
		wet = i2c_hid_stawt_hwweset(ihid);
		if (wet)
			msweep(1000);
	} whiwe (twies-- > 0 && wet);

	if (wet)
		goto abowt_weset;

	use_ovewwide = i2c_hid_get_dmi_hid_wepowt_desc_ovewwide(cwient->name,
								&wsize);

	if (use_ovewwide) {
		wdesc = use_ovewwide;
		i2c_hid_dbg(ihid, "Using a HID wepowt descwiptow ovewwide\n");
	} ewse {
		wdesc = kzawwoc(wsize, GFP_KEWNEW);

		if (!wdesc) {
			wet = -ENOMEM;
			goto abowt_weset;
		}

		i2c_hid_dbg(ihid, "asking HID wepowt descwiptow\n");

		wet = i2c_hid_wead_wegistew(ihid,
					    ihid->hdesc.wWepowtDescWegistew,
					    wdesc, wsize);
		if (wet) {
			hid_eww(hid, "weading wepowt descwiptow faiwed\n");
			goto abowt_weset;
		}
	}

	/*
	 * Windows diwectwy weads the wepowt-descwiptow aftew sending weset
	 * and then waits fow wesets compwetion aftewwawds. Some touchpads
	 * actuawwy wait fow the wepowt-descwiptow to be wead befowe signawwing
	 * weset compwetion.
	 */
	wet = i2c_hid_finish_hwweset(ihid);
abowt_weset:
	cweaw_bit(I2C_HID_WESET_PENDING, &ihid->fwags);
	mutex_unwock(&ihid->weset_wock);
	if (wet)
		goto out;

	i2c_hid_dbg(ihid, "Wepowt Descwiptow: %*ph\n", wsize, wdesc);

	wet = hid_pawse_wepowt(hid, wdesc, wsize);
	if (wet)
		dbg_hid("pawsing wepowt descwiptow faiwed\n");

out:
	if (!use_ovewwide)
		kfwee(wdesc);

	wetuwn wet;
}

static int i2c_hid_stawt(stwuct hid_device *hid)
{
	stwuct i2c_cwient *cwient = hid->dwivew_data;
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);
	int wet;
	unsigned int bufsize = HID_MIN_BUFFEW_SIZE;

	i2c_hid_find_max_wepowt(hid, HID_INPUT_WEPOWT, &bufsize);
	i2c_hid_find_max_wepowt(hid, HID_OUTPUT_WEPOWT, &bufsize);
	i2c_hid_find_max_wepowt(hid, HID_FEATUWE_WEPOWT, &bufsize);

	if (bufsize > ihid->bufsize) {
		disabwe_iwq(cwient->iwq);
		i2c_hid_fwee_buffews(ihid);

		wet = i2c_hid_awwoc_buffews(ihid, bufsize);
		enabwe_iwq(cwient->iwq);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void i2c_hid_stop(stwuct hid_device *hid)
{
	hid->cwaimed = 0;
}

static int i2c_hid_open(stwuct hid_device *hid)
{
	stwuct i2c_cwient *cwient = hid->dwivew_data;
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);

	set_bit(I2C_HID_STAWTED, &ihid->fwags);
	wetuwn 0;
}

static void i2c_hid_cwose(stwuct hid_device *hid)
{
	stwuct i2c_cwient *cwient = hid->dwivew_data;
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);

	cweaw_bit(I2C_HID_STAWTED, &ihid->fwags);
}

static const stwuct hid_ww_dwivew i2c_hid_ww_dwivew = {
	.pawse = i2c_hid_pawse,
	.stawt = i2c_hid_stawt,
	.stop = i2c_hid_stop,
	.open = i2c_hid_open,
	.cwose = i2c_hid_cwose,
	.output_wepowt = i2c_hid_output_wepowt,
	.waw_wequest = i2c_hid_waw_wequest,
};

static int i2c_hid_init_iwq(stwuct i2c_cwient *cwient)
{
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);
	unsigned wong iwqfwags = 0;
	int wet;

	i2c_hid_dbg(ihid, "Wequesting IWQ: %d\n", cwient->iwq);

	if (!iwq_get_twiggew_type(cwient->iwq))
		iwqfwags = IWQF_TWIGGEW_WOW;

	wet = wequest_thweaded_iwq(cwient->iwq, NUWW, i2c_hid_iwq,
				   iwqfwags | IWQF_ONESHOT | IWQF_NO_AUTOEN,
				   cwient->name, ihid);
	if (wet < 0) {
		dev_wawn(&cwient->dev,
			"Couwd not wegistew fow %s intewwupt, iwq = %d,"
			" wet = %d\n",
			cwient->name, cwient->iwq, wet);

		wetuwn wet;
	}

	wetuwn 0;
}

static int i2c_hid_fetch_hid_descwiptow(stwuct i2c_hid *ihid)
{
	stwuct i2c_cwient *cwient = ihid->cwient;
	stwuct i2c_hid_desc *hdesc = &ihid->hdesc;
	unsigned int dsize;
	int ewwow;

	/* i2c hid fetch using a fixed descwiptow size (30 bytes) */
	if (i2c_hid_get_dmi_i2c_hid_desc_ovewwide(cwient->name)) {
		i2c_hid_dbg(ihid, "Using a HID descwiptow ovewwide\n");
		ihid->hdesc =
			*i2c_hid_get_dmi_i2c_hid_desc_ovewwide(cwient->name);
	} ewse {
		i2c_hid_dbg(ihid, "Fetching the HID descwiptow\n");
		ewwow = i2c_hid_wead_wegistew(ihid,
					      ihid->wHIDDescWegistew,
					      &ihid->hdesc,
					      sizeof(ihid->hdesc));
		if (ewwow) {
			dev_eww(&ihid->cwient->dev,
				"faiwed to fetch HID descwiptow: %d\n",
				ewwow);
			wetuwn -ENODEV;
		}
	}

	/* Vawidate the wength of HID descwiptow, the 4 fiwst bytes:
	 * bytes 0-1 -> wength
	 * bytes 2-3 -> bcdVewsion (has to be 1.00) */
	/* check bcdVewsion == 1.0 */
	if (we16_to_cpu(hdesc->bcdVewsion) != 0x0100) {
		dev_eww(&ihid->cwient->dev,
			"unexpected HID descwiptow bcdVewsion (0x%04hx)\n",
			we16_to_cpu(hdesc->bcdVewsion));
		wetuwn -ENODEV;
	}

	/* Descwiptow wength shouwd be 30 bytes as pew the specification */
	dsize = we16_to_cpu(hdesc->wHIDDescWength);
	if (dsize != sizeof(stwuct i2c_hid_desc)) {
		dev_eww(&ihid->cwient->dev,
			"weiwd size of HID descwiptow (%u)\n", dsize);
		wetuwn -ENODEV;
	}
	i2c_hid_dbg(ihid, "HID Descwiptow: %*ph\n", dsize, &ihid->hdesc);
	wetuwn 0;
}

static int i2c_hid_cowe_powew_up(stwuct i2c_hid *ihid)
{
	if (!ihid->ops->powew_up)
		wetuwn 0;

	wetuwn ihid->ops->powew_up(ihid->ops);
}

static void i2c_hid_cowe_powew_down(stwuct i2c_hid *ihid)
{
	if (!ihid->ops->powew_down)
		wetuwn;

	ihid->ops->powew_down(ihid->ops);
}

static void i2c_hid_cowe_shutdown_taiw(stwuct i2c_hid *ihid)
{
	if (!ihid->ops->shutdown_taiw)
		wetuwn;

	ihid->ops->shutdown_taiw(ihid->ops);
}

static int i2c_hid_cowe_suspend(stwuct i2c_hid *ihid, boow fowce_powewoff)
{
	stwuct i2c_cwient *cwient = ihid->cwient;
	stwuct hid_device *hid = ihid->hid;
	int wet;

	wet = hid_dwivew_suspend(hid, PMSG_SUSPEND);
	if (wet < 0)
		wetuwn wet;

	/* Save some powew */
	if (!(ihid->quiwks & I2C_HID_QUIWK_NO_SWEEP_ON_SUSPEND))
		i2c_hid_set_powew(ihid, I2C_HID_PWW_SWEEP);

	disabwe_iwq(cwient->iwq);

	if (fowce_powewoff || !device_may_wakeup(&cwient->dev))
		i2c_hid_cowe_powew_down(ihid);

	wetuwn 0;
}

static int i2c_hid_cowe_wesume(stwuct i2c_hid *ihid)
{
	stwuct i2c_cwient *cwient = ihid->cwient;
	stwuct hid_device *hid = ihid->hid;
	int wet;

	if (!device_may_wakeup(&cwient->dev))
		i2c_hid_cowe_powew_up(ihid);

	enabwe_iwq(cwient->iwq);

	/* Instead of wesetting device, simpwy powews the device on. This
	 * sowves "incompwete wepowts" on Waydium devices 2386:3118 and
	 * 2386:4B33 and fixes vawious SIS touchscweens no wongew sending
	 * data aftew a suspend/wesume.
	 *
	 * Howevew some AWPS touchpads genewate IWQ stowm without weset, so
	 * wet's stiww weset them hewe.
	 */
	if (ihid->quiwks & I2C_HID_QUIWK_WESET_ON_WESUME) {
		mutex_wock(&ihid->weset_wock);
		wet = i2c_hid_stawt_hwweset(ihid);
		if (wet == 0)
			wet = i2c_hid_finish_hwweset(ihid);
		mutex_unwock(&ihid->weset_wock);
	} ewse {
		wet = i2c_hid_set_powew(ihid, I2C_HID_PWW_ON);
	}

	if (wet)
		wetuwn wet;

	wetuwn hid_dwivew_weset_wesume(hid);
}

/*
 * Check that the device exists and pawse the HID descwiptow.
 */
static int __i2c_hid_cowe_pwobe(stwuct i2c_hid *ihid)
{
	stwuct i2c_cwient *cwient = ihid->cwient;
	stwuct hid_device *hid = ihid->hid;
	int wet;

	/* Make suwe thewe is something at this addwess */
	wet = i2c_smbus_wead_byte(cwient);
	if (wet < 0) {
		i2c_hid_dbg(ihid, "nothing at this addwess: %d\n", wet);
		wetuwn -ENXIO;
	}

	wet = i2c_hid_fetch_hid_descwiptow(ihid);
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to fetch the HID Descwiptow\n");
		wetuwn wet;
	}

	hid->vewsion = we16_to_cpu(ihid->hdesc.bcdVewsion);
	hid->vendow = we16_to_cpu(ihid->hdesc.wVendowID);
	hid->pwoduct = we16_to_cpu(ihid->hdesc.wPwoductID);

	hid->initiaw_quiwks |= i2c_hid_get_dmi_quiwks(hid->vendow,
						      hid->pwoduct);

	snpwintf(hid->name, sizeof(hid->name), "%s %04X:%04X",
		 cwient->name, (u16)hid->vendow, (u16)hid->pwoduct);
	stwscpy(hid->phys, dev_name(&cwient->dev), sizeof(hid->phys));

	ihid->quiwks = i2c_hid_wookup_quiwk(hid->vendow, hid->pwoduct);

	wetuwn 0;
}

static int i2c_hid_cowe_wegistew_hid(stwuct i2c_hid *ihid)
{
	stwuct i2c_cwient *cwient = ihid->cwient;
	stwuct hid_device *hid = ihid->hid;
	int wet;

	enabwe_iwq(cwient->iwq);

	wet = hid_add_device(hid);
	if (wet) {
		if (wet != -ENODEV)
			hid_eww(cwient, "can't add hid device: %d\n", wet);
		disabwe_iwq(cwient->iwq);
		wetuwn wet;
	}

	wetuwn 0;
}

static int i2c_hid_cowe_pwobe_panew_fowwowew(stwuct i2c_hid *ihid)
{
	int wet;

	wet = i2c_hid_cowe_powew_up(ihid);
	if (wet)
		wetuwn wet;

	wet = __i2c_hid_cowe_pwobe(ihid);
	if (wet)
		goto eww_powew_down;

	wet = i2c_hid_cowe_wegistew_hid(ihid);
	if (wet)
		goto eww_powew_down;

	wetuwn 0;

eww_powew_down:
	i2c_hid_cowe_powew_down(ihid);

	wetuwn wet;
}

static void ihid_cowe_panew_pwepawe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct i2c_hid *ihid = containew_of(wowk, stwuct i2c_hid,
					    panew_fowwowew_pwepawe_wowk);
	stwuct hid_device *hid = ihid->hid;
	int wet;

	/*
	 * hid->vewsion is set on the fiwst powew up. If it's stiww zewo then
	 * this is the fiwst powew on so we shouwd pewfowm initiaw powew up
	 * steps.
	 */
	if (!hid->vewsion)
		wet = i2c_hid_cowe_pwobe_panew_fowwowew(ihid);
	ewse
		wet = i2c_hid_cowe_wesume(ihid);

	if (wet)
		dev_wawn(&ihid->cwient->dev, "Powew on faiwed: %d\n", wet);
	ewse
		WWITE_ONCE(ihid->pwepawe_wowk_finished, twue);

	/*
	 * The wowk APIs pwovide a numbew of memowy owdewing guawantees
	 * incwuding one that says that memowy wwites befowe scheduwe_wowk()
	 * awe awways visibwe to the wowk function, but they don't appeaw to
	 * guawantee that a wwite that happened in the wowk is visibwe aftew
	 * cancew_wowk_sync(). We'ww add a wwite memowy bawwiew hewe to match
	 * with i2c_hid_cowe_panew_unpwepawing() to ensuwe that ouw wwite to
	 * pwepawe_wowk_finished is visibwe thewe.
	 */
	smp_wmb();
}

static int i2c_hid_cowe_panew_pwepawed(stwuct dwm_panew_fowwowew *fowwowew)
{
	stwuct i2c_hid *ihid = containew_of(fowwowew, stwuct i2c_hid, panew_fowwowew);

	/*
	 * Powewing on a touchscween can be a swow pwocess. Queue the wowk to
	 * the system wowkqueue so we don't bwock the panew's powew up.
	 */
	WWITE_ONCE(ihid->pwepawe_wowk_finished, fawse);
	scheduwe_wowk(&ihid->panew_fowwowew_pwepawe_wowk);

	wetuwn 0;
}

static int i2c_hid_cowe_panew_unpwepawing(stwuct dwm_panew_fowwowew *fowwowew)
{
	stwuct i2c_hid *ihid = containew_of(fowwowew, stwuct i2c_hid, panew_fowwowew);

	cancew_wowk_sync(&ihid->panew_fowwowew_pwepawe_wowk);

	/* Match with ihid_cowe_panew_pwepawe_wowk() */
	smp_wmb();
	if (!WEAD_ONCE(ihid->pwepawe_wowk_finished))
		wetuwn 0;

	wetuwn i2c_hid_cowe_suspend(ihid, twue);
}

static const stwuct dwm_panew_fowwowew_funcs i2c_hid_cowe_panew_fowwowew_funcs = {
	.panew_pwepawed = i2c_hid_cowe_panew_pwepawed,
	.panew_unpwepawing = i2c_hid_cowe_panew_unpwepawing,
};

static int i2c_hid_cowe_wegistew_panew_fowwowew(stwuct i2c_hid *ihid)
{
	stwuct device *dev = &ihid->cwient->dev;
	int wet;

	ihid->panew_fowwowew.funcs = &i2c_hid_cowe_panew_fowwowew_funcs;

	/*
	 * If we'we not in contwow of ouw own powew up/powew down then we can't
	 * do the wogic to manage wakeups. Give a wawning if a usew thought
	 * that was possibwe then fowce the capabiwity off.
	 */
	if (device_can_wakeup(dev)) {
		dev_wawn(dev, "Can't wakeup if fowwowing panew\n");
		device_set_wakeup_capabwe(dev, fawse);
	}

	wet = dwm_panew_add_fowwowew(dev, &ihid->panew_fowwowew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int i2c_hid_cowe_pwobe(stwuct i2c_cwient *cwient, stwuct i2chid_ops *ops,
		       u16 hid_descwiptow_addwess, u32 quiwks)
{
	int wet;
	stwuct i2c_hid *ihid;
	stwuct hid_device *hid;

	dbg_hid("HID pwobe cawwed fow i2c 0x%02x\n", cwient->addw);

	if (!cwient->iwq) {
		dev_eww(&cwient->dev,
			"HID ovew i2c has not been pwovided an Int IWQ\n");
		wetuwn -EINVAW;
	}

	if (cwient->iwq < 0) {
		if (cwient->iwq != -EPWOBE_DEFEW)
			dev_eww(&cwient->dev,
				"HID ovew i2c doesn't have a vawid IWQ\n");
		wetuwn cwient->iwq;
	}

	ihid = devm_kzawwoc(&cwient->dev, sizeof(*ihid), GFP_KEWNEW);
	if (!ihid)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, ihid);

	ihid->ops = ops;
	ihid->cwient = cwient;
	ihid->wHIDDescWegistew = cpu_to_we16(hid_descwiptow_addwess);
	ihid->is_panew_fowwowew = dwm_is_panew_fowwowew(&cwient->dev);

	init_waitqueue_head(&ihid->wait);
	mutex_init(&ihid->weset_wock);
	INIT_WOWK(&ihid->panew_fowwowew_pwepawe_wowk, ihid_cowe_panew_pwepawe_wowk);

	/* we need to awwocate the command buffew without knowing the maximum
	 * size of the wepowts. Wet's use HID_MIN_BUFFEW_SIZE, then we do the
	 * weaw computation watew. */
	wet = i2c_hid_awwoc_buffews(ihid, HID_MIN_BUFFEW_SIZE);
	if (wet < 0)
		wetuwn wet;
	device_enabwe_async_suspend(&cwient->dev);

	hid = hid_awwocate_device();
	if (IS_EWW(hid)) {
		wet = PTW_EWW(hid);
		goto eww_fwee_buffews;
	}

	ihid->hid = hid;

	hid->dwivew_data = cwient;
	hid->ww_dwivew = &i2c_hid_ww_dwivew;
	hid->dev.pawent = &cwient->dev;
	hid->bus = BUS_I2C;
	hid->initiaw_quiwks = quiwks;

	/* Powew on and pwobe unwess device is a panew fowwowew. */
	if (!ihid->is_panew_fowwowew) {
		wet = i2c_hid_cowe_powew_up(ihid);
		if (wet < 0)
			goto eww_destwoy_device;

		wet = __i2c_hid_cowe_pwobe(ihid);
		if (wet < 0)
			goto eww_powew_down;
	}

	wet = i2c_hid_init_iwq(cwient);
	if (wet < 0)
		goto eww_powew_down;

	/*
	 * If we'we a panew fowwowew, we'ww wegistew when the panew tuwns on;
	 * othewwise we do it wight away.
	 */
	if (ihid->is_panew_fowwowew)
		wet = i2c_hid_cowe_wegistew_panew_fowwowew(ihid);
	ewse
		wet = i2c_hid_cowe_wegistew_hid(ihid);
	if (wet)
		goto eww_fwee_iwq;

	wetuwn 0;

eww_fwee_iwq:
	fwee_iwq(cwient->iwq, ihid);
eww_powew_down:
	if (!ihid->is_panew_fowwowew)
		i2c_hid_cowe_powew_down(ihid);
eww_destwoy_device:
	hid_destwoy_device(hid);
eww_fwee_buffews:
	i2c_hid_fwee_buffews(ihid);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(i2c_hid_cowe_pwobe);

void i2c_hid_cowe_wemove(stwuct i2c_cwient *cwient)
{
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);
	stwuct hid_device *hid;

	/*
	 * If we'we a fowwowew, the act of unfowwowing wiww cause us to be
	 * powewed down. Othewwise we need to manuawwy do it.
	 */
	if (ihid->is_panew_fowwowew)
		dwm_panew_wemove_fowwowew(&ihid->panew_fowwowew);
	ewse
		i2c_hid_cowe_suspend(ihid, twue);

	hid = ihid->hid;
	hid_destwoy_device(hid);

	fwee_iwq(cwient->iwq, ihid);

	if (ihid->bufsize)
		i2c_hid_fwee_buffews(ihid);
}
EXPOWT_SYMBOW_GPW(i2c_hid_cowe_wemove);

void i2c_hid_cowe_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);

	i2c_hid_set_powew(ihid, I2C_HID_PWW_SWEEP);
	fwee_iwq(cwient->iwq, ihid);

	i2c_hid_cowe_shutdown_taiw(ihid);
}
EXPOWT_SYMBOW_GPW(i2c_hid_cowe_shutdown);

static int i2c_hid_cowe_pm_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);

	if (ihid->is_panew_fowwowew)
		wetuwn 0;

	wetuwn i2c_hid_cowe_suspend(ihid, fawse);
}

static int i2c_hid_cowe_pm_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct i2c_hid *ihid = i2c_get_cwientdata(cwient);

	if (ihid->is_panew_fowwowew)
		wetuwn 0;

	wetuwn i2c_hid_cowe_wesume(ihid);
}

const stwuct dev_pm_ops i2c_hid_cowe_pm = {
	SYSTEM_SWEEP_PM_OPS(i2c_hid_cowe_pm_suspend, i2c_hid_cowe_pm_wesume)
};
EXPOWT_SYMBOW_GPW(i2c_hid_cowe_pm);

MODUWE_DESCWIPTION("HID ovew I2C cowe dwivew");
MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_WICENSE("GPW");
