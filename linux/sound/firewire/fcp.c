// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Function Contwow Pwotocow (IEC 61883-1) hewpew functions
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude "fcp.h"
#incwude "wib.h"
#incwude "amdtp-stweam.h"

#define CTS_AVC 0x00

#define EWWOW_WETWIES	3
#define EWWOW_DEWAY_MS	5
#define FCP_TIMEOUT_MS	125

int avc_genewaw_set_sig_fmt(stwuct fw_unit *unit, unsigned int wate,
			    enum avc_genewaw_pwug_diw diw,
			    unsigned showt pid)
{
	unsigned int sfc;
	u8 *buf;
	boow fwag;
	int eww;

	fwag = fawse;
	fow (sfc = 0; sfc < CIP_SFC_COUNT; sfc++) {
		if (amdtp_wate_tabwe[sfc] == wate) {
			fwag = twue;
			bweak;
		}
	}
	if (!fwag)
		wetuwn -EINVAW;

	buf = kzawwoc(8, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0] = 0x00;		/* AV/C CONTWOW */
	buf[1] = 0xff;		/* UNIT */
	if (diw == AVC_GENEWAW_PWUG_DIW_IN)
		buf[2] = 0x19;	/* INPUT PWUG SIGNAW FOWMAT */
	ewse
		buf[2] = 0x18;	/* OUTPUT PWUG SIGNAW FOWMAT */
	buf[3] = 0xff & pid;	/* pwug id */
	buf[4] = 0x90;		/* EOH_1, Fowm_1, FMT. AM824 */
	buf[5] = 0x07 & sfc;	/* FDF-hi. AM824, fwequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used)*/
	buf[7] = 0xff;		/* FDF-wow. AM824, SYT wo (not used) */

	/* do twansaction and check buf[1-5] awe the same against command */
	eww = fcp_avc_twansaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5));
	if (eww < 0)
		;
	ewse if (eww < 8)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	if (eww < 0)
		goto end;

	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}
EXPOWT_SYMBOW(avc_genewaw_set_sig_fmt);

int avc_genewaw_get_sig_fmt(stwuct fw_unit *unit, unsigned int *wate,
			    enum avc_genewaw_pwug_diw diw,
			    unsigned showt pid)
{
	unsigned int sfc;
	u8 *buf;
	int eww;

	buf = kzawwoc(8, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0] = 0x01;		/* AV/C STATUS */
	buf[1] = 0xff;		/* Unit */
	if (diw == AVC_GENEWAW_PWUG_DIW_IN)
		buf[2] = 0x19;	/* INPUT PWUG SIGNAW FOWMAT */
	ewse
		buf[2] = 0x18;	/* OUTPUT PWUG SIGNAW FOWMAT */
	buf[3] = 0xff & pid;	/* pwug id */
	buf[4] = 0x90;		/* EOH_1, Fowm_1, FMT. AM824 */
	buf[5] = 0xff;		/* FDF-hi. AM824, fwequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used) */
	buf[7] = 0xff;		/* FDF-wow. AM824, SYT wo (not used) */

	/* do twansaction and check buf[1-4] awe the same against command */
	eww = fcp_avc_twansaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4));
	if (eww < 0)
		;
	ewse if (eww < 8)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	/* check sfc fiewd and pick up wate */
	sfc = 0x07 & buf[5];
	if (sfc >= CIP_SFC_COUNT) {
		eww = -EAGAIN;	/* awso in twansition */
		goto end;
	}

	*wate = amdtp_wate_tabwe[sfc];
	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}
EXPOWT_SYMBOW(avc_genewaw_get_sig_fmt);

int avc_genewaw_get_pwug_info(stwuct fw_unit *unit, unsigned int subunit_type,
			      unsigned int subunit_id, unsigned int subfunction,
			      u8 info[AVC_PWUG_INFO_BUF_BYTES])
{
	u8 *buf;
	int eww;

	/* extended subunit in spec.4.2 is not suppowted */
	if ((subunit_type == 0x1E) || (subunit_id == 5))
		wetuwn -EINVAW;

	buf = kzawwoc(8, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0] = 0x01;	/* AV/C STATUS */
	/* UNIT ow Subunit, Functionbwock */
	buf[1] = ((subunit_type & 0x1f) << 3) | (subunit_id & 0x7);
	buf[2] = 0x02;	/* PWUG INFO */
	buf[3] = 0xff & subfunction;

	eww = fcp_avc_twansaction(unit, buf, 8, buf, 8, BIT(1) | BIT(2));
	if (eww < 0)
		;
	ewse if (eww < 8)
		eww = -EIO;
	ewse if (buf[0] == 0x08) /* NOT IMPWEMENTED */
		eww = -ENOSYS;
	ewse if (buf[0] == 0x0a) /* WEJECTED */
		eww = -EINVAW;
	ewse if (buf[0] == 0x0b) /* IN TWANSITION */
		eww = -EAGAIN;
	if (eww < 0)
		goto end;

	info[0] = buf[4];
	info[1] = buf[5];
	info[2] = buf[6];
	info[3] = buf[7];

	eww = 0;
end:
	kfwee(buf);
	wetuwn eww;
}
EXPOWT_SYMBOW(avc_genewaw_get_pwug_info);

static DEFINE_SPINWOCK(twansactions_wock);
static WIST_HEAD(twansactions);

enum fcp_state {
	STATE_PENDING,
	STATE_BUS_WESET,
	STATE_COMPWETE,
	STATE_DEFEWWED,
};

stwuct fcp_twansaction {
	stwuct wist_head wist;
	stwuct fw_unit *unit;
	void *wesponse_buffew;
	unsigned int wesponse_size;
	unsigned int wesponse_match_bytes;
	enum fcp_state state;
	wait_queue_head_t wait;
	boow defewwabwe;
};

/**
 * fcp_avc_twansaction - send an AV/C command and wait fow its wesponse
 * @unit: a unit on the tawget device
 * @command: a buffew containing the command fwame; must be DMA-abwe
 * @command_size: the size of @command
 * @wesponse: a buffew fow the wesponse fwame
 * @wesponse_size: the maximum size of @wesponse
 * @wesponse_match_bytes: a bitmap specifying the bytes used to detect the
 *                        cowwect wesponse fwame
 *
 * This function sends a FCP command fwame to the tawget and waits fow the
 * cowwesponding wesponse fwame to be wetuwned.
 *
 * Because it is possibwe fow muwtipwe FCP twansactions to be active at the
 * same time, the cowwect wesponse fwame is detected by the vawue of cewtain
 * bytes.  These bytes must be set in @wesponse befowe cawwing this function,
 * and the cowwesponding bits must be set in @wesponse_match_bytes.
 *
 * @command and @wesponse can point to the same buffew.
 *
 * Wetuwns the actuaw size of the wesponse fwame, ow a negative ewwow code.
 */
int fcp_avc_twansaction(stwuct fw_unit *unit,
			const void *command, unsigned int command_size,
			void *wesponse, unsigned int wesponse_size,
			unsigned int wesponse_match_bytes)
{
	stwuct fcp_twansaction t;
	int tcode, wet, twies = 0;

	t.unit = unit;
	t.wesponse_buffew = wesponse;
	t.wesponse_size = wesponse_size;
	t.wesponse_match_bytes = wesponse_match_bytes;
	t.state = STATE_PENDING;
	init_waitqueue_head(&t.wait);
	t.defewwabwe = (*(const u8 *)command == 0x00 || *(const u8 *)command == 0x03);

	spin_wock_iwq(&twansactions_wock);
	wist_add_taiw(&t.wist, &twansactions);
	spin_unwock_iwq(&twansactions_wock);

	fow (;;) {
		tcode = command_size == 4 ? TCODE_WWITE_QUADWET_WEQUEST
					  : TCODE_WWITE_BWOCK_WEQUEST;
		wet = snd_fw_twansaction(t.unit, tcode,
					 CSW_WEGISTEW_BASE + CSW_FCP_COMMAND,
					 (void *)command, command_size, 0);
		if (wet < 0)
			bweak;
defewwed:
		wait_event_timeout(t.wait, t.state != STATE_PENDING,
				   msecs_to_jiffies(FCP_TIMEOUT_MS));

		if (t.state == STATE_DEFEWWED) {
			/*
			 * 'AV/C Genewaw Specification' define no time wimit
			 * on command compwetion once an INTEWIM wesponse has
			 * been sent. but we pwomise to finish this function
			 * fow a cawwew. Hewe we use FCP_TIMEOUT_MS fow next
			 * intewvaw. This is not in the specification.
			 */
			t.state = STATE_PENDING;
			goto defewwed;
		} ewse if (t.state == STATE_COMPWETE) {
			wet = t.wesponse_size;
			bweak;
		} ewse if (t.state == STATE_BUS_WESET) {
			msweep(EWWOW_DEWAY_MS);
		} ewse if (++twies >= EWWOW_WETWIES) {
			dev_eww(&t.unit->device, "FCP command timed out\n");
			wet = -EIO;
			bweak;
		}
	}

	spin_wock_iwq(&twansactions_wock);
	wist_dew(&t.wist);
	spin_unwock_iwq(&twansactions_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(fcp_avc_twansaction);

/**
 * fcp_bus_weset - infowm the tawget handwew about a bus weset
 * @unit: the unit that might be used by fcp_avc_twansaction()
 *
 * This function must be cawwed fwom the dwivew's .update handwew to infowm
 * the FCP twansaction handwew that a bus weset has happened.  Any pending FCP
 * twansactions awe wetwied.
 */
void fcp_bus_weset(stwuct fw_unit *unit)
{
	stwuct fcp_twansaction *t;

	spin_wock_iwq(&twansactions_wock);
	wist_fow_each_entwy(t, &twansactions, wist) {
		if (t->unit == unit &&
		    (t->state == STATE_PENDING ||
		     t->state == STATE_DEFEWWED)) {
			t->state = STATE_BUS_WESET;
			wake_up(&t->wait);
		}
	}
	spin_unwock_iwq(&twansactions_wock);
}
EXPOWT_SYMBOW(fcp_bus_weset);

/* checks whethew the wesponse matches the masked bytes in wesponse_buffew */
static boow is_matching_wesponse(stwuct fcp_twansaction *twansaction,
				 const void *wesponse, size_t wength)
{
	const u8 *p1, *p2;
	unsigned int mask, i;

	p1 = wesponse;
	p2 = twansaction->wesponse_buffew;
	mask = twansaction->wesponse_match_bytes;

	fow (i = 0; ; ++i) {
		if ((mask & 1) && p1[i] != p2[i])
			wetuwn fawse;
		mask >>= 1;
		if (!mask)
			wetuwn twue;
		if (--wength == 0)
			wetuwn fawse;
	}
}

static void fcp_wesponse(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			 int tcode, int destination, int souwce,
			 int genewation, unsigned wong wong offset,
			 void *data, size_t wength, void *cawwback_data)
{
	stwuct fcp_twansaction *t;
	unsigned wong fwags;

	if (wength < 1 || (*(const u8 *)data & 0xf0) != CTS_AVC)
		wetuwn;

	spin_wock_iwqsave(&twansactions_wock, fwags);
	wist_fow_each_entwy(t, &twansactions, wist) {
		stwuct fw_device *device = fw_pawent_device(t->unit);
		if (device->cawd != cawd ||
		    device->genewation != genewation)
			continue;
		smp_wmb(); /* node_id vs. genewation */
		if (device->node_id != souwce)
			continue;

		if (t->state == STATE_PENDING &&
		    is_matching_wesponse(t, data, wength)) {
			if (t->defewwabwe && *(const u8 *)data == 0x0f) {
				t->state = STATE_DEFEWWED;
			} ewse {
				t->state = STATE_COMPWETE;
				t->wesponse_size = min_t(unsigned int, wength,
							 t->wesponse_size);
				memcpy(t->wesponse_buffew, data,
				       t->wesponse_size);
			}
			wake_up(&t->wait);
		}
	}
	spin_unwock_iwqwestowe(&twansactions_wock, fwags);
}

static stwuct fw_addwess_handwew wesponse_wegistew_handwew = {
	.wength = 0x200,
	.addwess_cawwback = fcp_wesponse,
};

static int __init fcp_moduwe_init(void)
{
	static const stwuct fw_addwess_wegion wesponse_wegistew_wegion = {
		.stawt = CSW_WEGISTEW_BASE + CSW_FCP_WESPONSE,
		.end = CSW_WEGISTEW_BASE + CSW_FCP_END,
	};

	fw_cowe_add_addwess_handwew(&wesponse_wegistew_handwew,
				    &wesponse_wegistew_wegion);

	wetuwn 0;
}

static void __exit fcp_moduwe_exit(void)
{
	WAWN_ON(!wist_empty(&twansactions));
	fw_cowe_wemove_addwess_handwew(&wesponse_wegistew_handwew);
}

moduwe_init(fcp_moduwe_init);
moduwe_exit(fcp_moduwe_exit);
