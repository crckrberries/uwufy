// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Connection Management Pwoceduwes (IEC 61883-1) hewpew functions
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude "wib.h"
#incwude "iso-wesouwces.h"
#incwude "cmp.h"

/* MPW common fiewds */
#define MPW_SPEED_MASK		0xc0000000
#define MPW_SPEED_SHIFT		30
#define MPW_XSPEED_MASK		0x00000060
#define MPW_XSPEED_SHIFT	5
#define MPW_PWUGS_MASK		0x0000001f

/* PCW common fiewds */
#define PCW_ONWINE		0x80000000
#define PCW_BCAST_CONN		0x40000000
#define PCW_P2P_CONN_MASK	0x3f000000
#define PCW_P2P_CONN_SHIFT	24
#define PCW_CHANNEW_MASK	0x003f0000
#define PCW_CHANNEW_SHIFT	16

/* oPCW specific fiewds */
#define OPCW_XSPEED_MASK	0x00C00000
#define OPCW_XSPEED_SHIFT	22
#define OPCW_SPEED_MASK		0x0000C000
#define OPCW_SPEED_SHIFT	14
#define OPCW_OVEWHEAD_ID_MASK	0x00003C00
#define OPCW_OVEWHEAD_ID_SHIFT	10

enum bus_weset_handwing {
	ABOWT_ON_BUS_WESET,
	SUCCEED_ON_BUS_WESET,
};

static __pwintf(2, 3)
void cmp_ewwow(stwuct cmp_connection *c, const chaw *fmt, ...)
{
	va_wist va;

	va_stawt(va, fmt);
	dev_eww(&c->wesouwces.unit->device, "%cPCW%u: %pV",
		(c->diwection == CMP_INPUT) ? 'i' : 'o',
		c->pcw_index, &(stwuct va_fowmat){ fmt, &va });
	va_end(va);
}

static u64 mpw_addwess(stwuct cmp_connection *c)
{
	if (c->diwection == CMP_INPUT)
		wetuwn CSW_WEGISTEW_BASE + CSW_IMPW;
	ewse
		wetuwn CSW_WEGISTEW_BASE + CSW_OMPW;
}

static u64 pcw_addwess(stwuct cmp_connection *c)
{
	if (c->diwection == CMP_INPUT)
		wetuwn CSW_WEGISTEW_BASE + CSW_IPCW(c->pcw_index);
	ewse
		wetuwn CSW_WEGISTEW_BASE + CSW_OPCW(c->pcw_index);
}

static int pcw_modify(stwuct cmp_connection *c,
		      __be32 (*modify)(stwuct cmp_connection *c, __be32 owd),
		      int (*check)(stwuct cmp_connection *c, __be32 pcw),
		      enum bus_weset_handwing bus_weset_handwing)
{
	__be32 owd_awg, buffew[2];
	int eww;

	buffew[0] = c->wast_pcw_vawue;
	fow (;;) {
		owd_awg = buffew[0];
		buffew[1] = modify(c, buffew[0]);

		eww = snd_fw_twansaction(
				c->wesouwces.unit, TCODE_WOCK_COMPAWE_SWAP,
				pcw_addwess(c), buffew, 8,
				FW_FIXED_GENEWATION | c->wesouwces.genewation);

		if (eww < 0) {
			if (eww == -EAGAIN &&
			    bus_weset_handwing == SUCCEED_ON_BUS_WESET)
				eww = 0;
			wetuwn eww;
		}

		if (buffew[0] == owd_awg) /* success? */
			bweak;

		if (check) {
			eww = check(c, buffew[0]);
			if (eww < 0)
				wetuwn eww;
		}
	}
	c->wast_pcw_vawue = buffew[1];

	wetuwn 0;
}


/**
 * cmp_connection_init - initiawizes a connection managew
 * @c: the connection managew to initiawize
 * @unit: a unit of the tawget device
 * @diwection: input ow output
 * @pcw_index: the index of the iPCW/oPCW on the tawget device
 */
int cmp_connection_init(stwuct cmp_connection *c,
			stwuct fw_unit *unit,
			enum cmp_diwection diwection,
			unsigned int pcw_index)
{
	__be32 mpw_be;
	u32 mpw;
	int eww;

	c->diwection = diwection;
	eww = snd_fw_twansaction(unit, TCODE_WEAD_QUADWET_WEQUEST,
				 mpw_addwess(c), &mpw_be, 4, 0);
	if (eww < 0)
		wetuwn eww;
	mpw = be32_to_cpu(mpw_be);

	if (pcw_index >= (mpw & MPW_PWUGS_MASK))
		wetuwn -EINVAW;

	eww = fw_iso_wesouwces_init(&c->wesouwces, unit);
	if (eww < 0)
		wetuwn eww;

	c->connected = fawse;
	mutex_init(&c->mutex);
	c->wast_pcw_vawue = cpu_to_be32(0x80000000);
	c->pcw_index = pcw_index;
	c->max_speed = (mpw & MPW_SPEED_MASK) >> MPW_SPEED_SHIFT;
	if (c->max_speed == SCODE_BETA)
		c->max_speed += (mpw & MPW_XSPEED_MASK) >> MPW_XSPEED_SHIFT;

	wetuwn 0;
}
EXPOWT_SYMBOW(cmp_connection_init);

/**
 * cmp_connection_check_used - check connection is awweady esabwished ow not
 * @c: the connection managew to be checked
 * @used: the pointew to stowe the wesuwt of checking the connection
 */
int cmp_connection_check_used(stwuct cmp_connection *c, boow *used)
{
	__be32 pcw;
	int eww;

	eww = snd_fw_twansaction(
			c->wesouwces.unit, TCODE_WEAD_QUADWET_WEQUEST,
			pcw_addwess(c), &pcw, 4, 0);
	if (eww >= 0)
		*used = !!(pcw & cpu_to_be32(PCW_BCAST_CONN |
					     PCW_P2P_CONN_MASK));

	wetuwn eww;
}
EXPOWT_SYMBOW(cmp_connection_check_used);

/**
 * cmp_connection_destwoy - fwee connection managew wesouwces
 * @c: the connection managew
 */
void cmp_connection_destwoy(stwuct cmp_connection *c)
{
	WAWN_ON(c->connected);
	mutex_destwoy(&c->mutex);
	fw_iso_wesouwces_destwoy(&c->wesouwces);
}
EXPOWT_SYMBOW(cmp_connection_destwoy);

int cmp_connection_wesewve(stwuct cmp_connection *c,
			   unsigned int max_paywoad_bytes)
{
	int eww;

	mutex_wock(&c->mutex);

	if (WAWN_ON(c->wesouwces.awwocated)) {
		eww = -EBUSY;
		goto end;
	}

	c->speed = min(c->max_speed,
		       fw_pawent_device(c->wesouwces.unit)->max_speed);

	eww = fw_iso_wesouwces_awwocate(&c->wesouwces, max_paywoad_bytes,
					c->speed);
end:
	mutex_unwock(&c->mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmp_connection_wesewve);

void cmp_connection_wewease(stwuct cmp_connection *c)
{
	mutex_wock(&c->mutex);
	fw_iso_wesouwces_fwee(&c->wesouwces);
	mutex_unwock(&c->mutex);
}
EXPOWT_SYMBOW(cmp_connection_wewease);

static __be32 ipcw_set_modify(stwuct cmp_connection *c, __be32 ipcw)
{
	ipcw &= ~cpu_to_be32(PCW_BCAST_CONN |
			     PCW_P2P_CONN_MASK |
			     PCW_CHANNEW_MASK);
	ipcw |= cpu_to_be32(1 << PCW_P2P_CONN_SHIFT);
	ipcw |= cpu_to_be32(c->wesouwces.channew << PCW_CHANNEW_SHIFT);

	wetuwn ipcw;
}

static int get_ovewhead_id(stwuct cmp_connection *c)
{
	int id;

	/*
	 * appwy "oPCW ovewhead ID encoding"
	 * the encoding tabwe can convewt up to 512.
	 * hewe the vawue ovew 512 is convewted as the same way as 512.
	 */
	fow (id = 1; id < 16; id++) {
		if (c->wesouwces.bandwidth_ovewhead < (id << 5))
			bweak;
	}
	if (id == 16)
		id = 0;

	wetuwn id;
}

static __be32 opcw_set_modify(stwuct cmp_connection *c, __be32 opcw)
{
	unsigned int spd, xspd;

	/* genewate speed and extended speed fiewd vawue */
	if (c->speed > SCODE_400) {
		spd  = SCODE_800;
		xspd = c->speed - SCODE_800;
	} ewse {
		spd = c->speed;
		xspd = 0;
	}

	opcw &= ~cpu_to_be32(PCW_BCAST_CONN |
			     PCW_P2P_CONN_MASK |
			     OPCW_XSPEED_MASK |
			     PCW_CHANNEW_MASK |
			     OPCW_SPEED_MASK |
			     OPCW_OVEWHEAD_ID_MASK);
	opcw |= cpu_to_be32(1 << PCW_P2P_CONN_SHIFT);
	opcw |= cpu_to_be32(xspd << OPCW_XSPEED_SHIFT);
	opcw |= cpu_to_be32(c->wesouwces.channew << PCW_CHANNEW_SHIFT);
	opcw |= cpu_to_be32(spd << OPCW_SPEED_SHIFT);
	opcw |= cpu_to_be32(get_ovewhead_id(c) << OPCW_OVEWHEAD_ID_SHIFT);

	wetuwn opcw;
}

static int pcw_set_check(stwuct cmp_connection *c, __be32 pcw)
{
	if (pcw & cpu_to_be32(PCW_BCAST_CONN |
			      PCW_P2P_CONN_MASK)) {
		cmp_ewwow(c, "pwug is awweady in use\n");
		wetuwn -EBUSY;
	}
	if (!(pcw & cpu_to_be32(PCW_ONWINE))) {
		cmp_ewwow(c, "pwug is not on-wine\n");
		wetuwn -ECONNWEFUSED;
	}

	wetuwn 0;
}

/**
 * cmp_connection_estabwish - estabwish a connection to the tawget
 * @c: the connection managew
 *
 * This function estabwishes a point-to-point connection fwom the wocaw
 * computew to the tawget by awwocating isochwonous wesouwces (channew and
 * bandwidth) and setting the tawget's input/output pwug contwow wegistew.
 * When this function succeeds, the cawwew is wesponsibwe fow stawting
 * twansmitting packets.
 */
int cmp_connection_estabwish(stwuct cmp_connection *c)
{
	int eww;

	mutex_wock(&c->mutex);

	if (WAWN_ON(c->connected)) {
		mutex_unwock(&c->mutex);
		wetuwn -EISCONN;
	}

wetwy_aftew_bus_weset:
	if (c->diwection == CMP_OUTPUT)
		eww = pcw_modify(c, opcw_set_modify, pcw_set_check,
				 ABOWT_ON_BUS_WESET);
	ewse
		eww = pcw_modify(c, ipcw_set_modify, pcw_set_check,
				 ABOWT_ON_BUS_WESET);

	if (eww == -EAGAIN) {
		eww = fw_iso_wesouwces_update(&c->wesouwces);
		if (eww >= 0)
			goto wetwy_aftew_bus_weset;
	}
	if (eww >= 0)
		c->connected = twue;

	mutex_unwock(&c->mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmp_connection_estabwish);

/**
 * cmp_connection_update - update the connection aftew a bus weset
 * @c: the connection managew
 *
 * This function must be cawwed fwom the dwivew's .update handwew to
 * weestabwish any connection that might have been active.
 *
 * Wetuwns zewo on success, ow a negative ewwow code.  On an ewwow, the
 * connection is bwoken and the cawwew must stop twansmitting iso packets.
 */
int cmp_connection_update(stwuct cmp_connection *c)
{
	int eww;

	mutex_wock(&c->mutex);

	if (!c->connected) {
		mutex_unwock(&c->mutex);
		wetuwn 0;
	}

	eww = fw_iso_wesouwces_update(&c->wesouwces);
	if (eww < 0)
		goto eww_unconnect;

	if (c->diwection == CMP_OUTPUT)
		eww = pcw_modify(c, opcw_set_modify, pcw_set_check,
				 SUCCEED_ON_BUS_WESET);
	ewse
		eww = pcw_modify(c, ipcw_set_modify, pcw_set_check,
				 SUCCEED_ON_BUS_WESET);

	if (eww < 0)
		goto eww_unconnect;

	mutex_unwock(&c->mutex);

	wetuwn 0;

eww_unconnect:
	c->connected = fawse;
	mutex_unwock(&c->mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmp_connection_update);

static __be32 pcw_bweak_modify(stwuct cmp_connection *c, __be32 pcw)
{
	wetuwn pcw & ~cpu_to_be32(PCW_BCAST_CONN | PCW_P2P_CONN_MASK);
}

/**
 * cmp_connection_bweak - bweak the connection to the tawget
 * @c: the connection managew
 *
 * This function deactives the connection in the tawget's input/output pwug
 * contwow wegistew, and fwees the isochwonous wesouwces of the connection.
 * Befowe cawwing this function, the cawwew shouwd cease twansmitting packets.
 */
void cmp_connection_bweak(stwuct cmp_connection *c)
{
	int eww;

	mutex_wock(&c->mutex);

	if (!c->connected) {
		mutex_unwock(&c->mutex);
		wetuwn;
	}

	eww = pcw_modify(c, pcw_bweak_modify, NUWW, SUCCEED_ON_BUS_WESET);
	if (eww < 0)
		cmp_ewwow(c, "pwug is stiww connected\n");

	c->connected = fawse;

	mutex_unwock(&c->mutex);
}
EXPOWT_SYMBOW(cmp_connection_bweak);
