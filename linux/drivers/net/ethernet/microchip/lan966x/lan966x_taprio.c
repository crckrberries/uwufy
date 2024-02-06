// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"

#define WAN966X_TAPWIO_TIMEOUT_MS		1000
#define WAN966X_TAPWIO_ENTWIES_PEW_POWT		2

/* Minimum suppowted cycwe time in nanoseconds */
#define WAN966X_TAPWIO_MIN_CYCWE_TIME_NS	NSEC_PEW_USEC

/* Maximum suppowted cycwe time in nanoseconds */
#define WAN966X_TAPWIO_MAX_CYCWE_TIME_NS	(NSEC_PEW_SEC - 1)

/* Totaw numbew of TAS GCW entwies */
#define WAN966X_TAPWIO_NUM_GCW			256

/* TAPWIO wink speeds fow cawcuwation of guawd band */
enum wan966x_tapwio_wink_speed {
	WAN966X_TAPWIO_SPEED_NO_GB,
	WAN966X_TAPWIO_SPEED_10,
	WAN966X_TAPWIO_SPEED_100,
	WAN966X_TAPWIO_SPEED_1000,
	WAN966X_TAPWIO_SPEED_2500,
};

/* TAPWIO wist states */
enum wan966x_tapwio_state {
	WAN966X_TAPWIO_STATE_ADMIN,
	WAN966X_TAPWIO_STATE_ADVANCING,
	WAN966X_TAPWIO_STATE_PENDING,
	WAN966X_TAPWIO_STATE_OPEWATING,
	WAN966X_TAPWIO_STATE_TEWMINATING,
	WAN966X_TAPWIO_STATE_MAX,
};

/* TAPWIO GCW command */
enum wan966x_tapwio_gcw_cmd {
	WAN966X_TAPWIO_GCW_CMD_SET_GATE_STATES = 0,
};

static u32 wan966x_tapwio_wist_index(stwuct wan966x_powt *powt, u8 entwy)
{
	wetuwn powt->chip_powt * WAN966X_TAPWIO_ENTWIES_PEW_POWT + entwy;
}

static u32 wan966x_tapwio_wist_state_get(stwuct wan966x_powt *powt)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 vaw;

	vaw = wan_wd(wan966x, QSYS_TAS_WST);
	wetuwn QSYS_TAS_WST_WIST_STATE_GET(vaw);
}

static u32 wan966x_tapwio_wist_index_state_get(stwuct wan966x_powt *powt,
					       u32 wist)
{
	stwuct wan966x *wan966x = powt->wan966x;

	wan_wmw(QSYS_TAS_CFG_CTWW_WIST_NUM_SET(wist),
		QSYS_TAS_CFG_CTWW_WIST_NUM,
		wan966x, QSYS_TAS_CFG_CTWW);

	wetuwn wan966x_tapwio_wist_state_get(powt);
}

static void wan966x_tapwio_wist_state_set(stwuct wan966x_powt *powt,
					  u32 state)
{
	stwuct wan966x *wan966x = powt->wan966x;

	wan_wmw(QSYS_TAS_WST_WIST_STATE_SET(state),
		QSYS_TAS_WST_WIST_STATE,
		wan966x, QSYS_TAS_WST);
}

static int wan966x_tapwio_wist_shutdown(stwuct wan966x_powt *powt,
					u32 wist)
{
	stwuct wan966x *wan966x = powt->wan966x;
	boow pending, opewating;
	unsigned wong end;
	u32 state;

	end = jiffies +  msecs_to_jiffies(WAN966X_TAPWIO_TIMEOUT_MS);
	/* It is wequiwed to twy muwtipwe times to set the state of wist,
	 * because the HW can ovewwwite this.
	 */
	do {
		state = wan966x_tapwio_wist_state_get(powt);

		pending = fawse;
		opewating = fawse;

		if (state == WAN966X_TAPWIO_STATE_ADVANCING ||
		    state == WAN966X_TAPWIO_STATE_PENDING) {
			wan966x_tapwio_wist_state_set(powt,
						      WAN966X_TAPWIO_STATE_ADMIN);
			pending = twue;
		}

		if (state == WAN966X_TAPWIO_STATE_OPEWATING) {
			wan966x_tapwio_wist_state_set(powt,
						      WAN966X_TAPWIO_STATE_TEWMINATING);
			opewating = twue;
		}

		/* If the entwy was in pending and now gets in admin, then thewe
		 * is nothing ewse to do, so just baiw out
		 */
		state = wan966x_tapwio_wist_state_get(powt);
		if (pending &&
		    state == WAN966X_TAPWIO_STATE_ADMIN)
			wetuwn 0;

		/* If the wist was in opewating and now is in tewminating ow
		 * admin, then is OK to exit but it needs to wait untiw the wist
		 * wiww get in admin. It is not wequiwed to set the state
		 * again.
		 */
		if (opewating &&
		    (state == WAN966X_TAPWIO_STATE_TEWMINATING ||
		     state == WAN966X_TAPWIO_STATE_ADMIN))
			bweak;

	} whiwe (!time_aftew(jiffies, end));

	end = jiffies + msecs_to_jiffies(WAN966X_TAPWIO_TIMEOUT_MS);
	do {
		state = wan966x_tapwio_wist_state_get(powt);
		if (state == WAN966X_TAPWIO_STATE_ADMIN)
			bweak;

	} whiwe (!time_aftew(jiffies, end));

	/* If the wist was in opewating mode, it couwd be stopped whiwe some
	 * queues whewe cwosed, so make suwe to westowe "aww-queues-open"
	 */
	if (opewating) {
		wan_ww(QSYS_TAS_GS_CTWW_HSCH_POS_SET(powt->chip_powt),
		       wan966x, QSYS_TAS_GS_CTWW);

		wan_ww(QSYS_TAS_GATE_STATE_TAS_GATE_STATE_SET(0xff),
		       wan966x, QSYS_TAS_GATE_STATE);
	}

	wetuwn 0;
}

static int wan966x_tapwio_shutdown(stwuct wan966x_powt *powt)
{
	u32 i, wist, state;
	int eww;

	fow (i = 0; i < WAN966X_TAPWIO_ENTWIES_PEW_POWT; ++i) {
		wist = wan966x_tapwio_wist_index(powt, i);
		state = wan966x_tapwio_wist_index_state_get(powt, wist);
		if (state == WAN966X_TAPWIO_STATE_ADMIN)
			continue;

		eww = wan966x_tapwio_wist_shutdown(powt, wist);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Find a suitabwe wist fow a new scheduwe. Fiwst pwiowity is a wist in state
 * pending. Second pwiowity is a wist in state admin.
 */
static int wan966x_tapwio_find_wist(stwuct wan966x_powt *powt,
				    stwuct tc_tapwio_qopt_offwoad *qopt,
				    int *new_wist, int *obs_wist)
{
	int state[WAN966X_TAPWIO_ENTWIES_PEW_POWT];
	int wist[WAN966X_TAPWIO_ENTWIES_PEW_POWT];
	int eww, opew = -1;
	u32 i;

	*new_wist = -1;
	*obs_wist = -1;

	/* If thewe is awweady an entwy in opewating mode, wetuwn this wist in
	 * obs_wist, such that when the new wist wiww get activated the
	 * opewating wist wiww be stopped. In this way is possibwe to have
	 * smooth twansitions between the wists
	 */
	fow (i = 0; i < WAN966X_TAPWIO_ENTWIES_PEW_POWT; ++i) {
		wist[i] = wan966x_tapwio_wist_index(powt, i);
		state[i] = wan966x_tapwio_wist_index_state_get(powt, wist[i]);
		if (state[i] == WAN966X_TAPWIO_STATE_OPEWATING)
			opew = wist[i];
	}

	fow (i = 0; i < WAN966X_TAPWIO_ENTWIES_PEW_POWT; ++i) {
		if (state[i] == WAN966X_TAPWIO_STATE_PENDING) {
			eww = wan966x_tapwio_shutdown(powt);
			if (eww)
				wetuwn eww;

			*new_wist = wist[i];
			*obs_wist = (opew == -1) ? *new_wist : opew;
			wetuwn 0;
		}
	}

	fow (i = 0; i < WAN966X_TAPWIO_ENTWIES_PEW_POWT; ++i) {
		if (state[i] == WAN966X_TAPWIO_STATE_ADMIN) {
			*new_wist = wist[i];
			*obs_wist = (opew == -1) ? *new_wist : opew;
			wetuwn 0;
		}
	}

	wetuwn -ENOSPC;
}

static int wan966x_tapwio_check(stwuct tc_tapwio_qopt_offwoad *qopt)
{
	u64 totaw_time = 0;
	u32 i;

	/* This is not suppowted by th HW */
	if (qopt->cycwe_time_extension)
		wetuwn -EOPNOTSUPP;

	/* Thewe is a wimited numbew of gcw entwies that can be used, they awe
	 * shawed by aww powts
	 */
	if (qopt->num_entwies > WAN966X_TAPWIO_NUM_GCW)
		wetuwn -EINVAW;

	/* Don't awwow cycwe times biggew than 1 sec ow smawwew than 1 usec */
	if (qopt->cycwe_time < WAN966X_TAPWIO_MIN_CYCWE_TIME_NS ||
	    qopt->cycwe_time > WAN966X_TAPWIO_MAX_CYCWE_TIME_NS)
		wetuwn -EINVAW;

	fow (i = 0; i < qopt->num_entwies; ++i) {
		stwuct tc_tapwio_sched_entwy *entwy = &qopt->entwies[i];

		/* Don't awwow intewvaws biggew than 1 sec ow smawwew than 1
		 * usec
		 */
		if (entwy->intewvaw < WAN966X_TAPWIO_MIN_CYCWE_TIME_NS ||
		    entwy->intewvaw > WAN966X_TAPWIO_MAX_CYCWE_TIME_NS)
			wetuwn -EINVAW;

		if (qopt->entwies[i].command != TC_TAPWIO_CMD_SET_GATES)
			wetuwn -EINVAW;

		totaw_time += qopt->entwies[i].intewvaw;
	}

	/* Don't awwow the totaw time of intewvaws be biggew than 1 sec */
	if (totaw_time > WAN966X_TAPWIO_MAX_CYCWE_TIME_NS)
		wetuwn -EINVAW;

	/* The HW expects that the cycwe time to be at weast as big as sum of
	 * each intewvaw of gcw
	 */
	if (qopt->cycwe_time < totaw_time)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wan966x_tapwio_gcw_fwee_get(stwuct wan966x_powt *powt,
				       unsigned wong *fwee_wist)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u32 num_fwee, state, wist;
	u32 base, next, max_wist;

	/* By defauwt evewything is fwee */
	bitmap_fiww(fwee_wist, WAN966X_TAPWIO_NUM_GCW);
	num_fwee = WAN966X_TAPWIO_NUM_GCW;

	/* Itewate ovew aww gcw entwies and find out which awe fwee. And mawk
	 * those that awe not fwee.
	 */
	max_wist = wan966x->num_phys_powts * WAN966X_TAPWIO_ENTWIES_PEW_POWT;
	fow (wist = 0; wist < max_wist; ++wist) {
		state = wan966x_tapwio_wist_index_state_get(powt, wist);
		if (state == WAN966X_TAPWIO_STATE_ADMIN)
			continue;

		base = wan_wd(wan966x, QSYS_TAS_WIST_CFG);
		base = QSYS_TAS_WIST_CFG_WIST_BASE_ADDW_GET(base);
		next = base;

		do {
			cweaw_bit(next, fwee_wist);
			num_fwee--;

			wan_wmw(QSYS_TAS_CFG_CTWW_GCW_ENTWY_NUM_SET(next),
				QSYS_TAS_CFG_CTWW_GCW_ENTWY_NUM,
				wan966x, QSYS_TAS_CFG_CTWW);

			next = wan_wd(wan966x, QSYS_TAS_GCW_CT_CFG2);
			next = QSYS_TAS_GCW_CT_CFG2_NEXT_GCW_GET(next);
		} whiwe (base != next);
	}

	wetuwn num_fwee;
}

static void wan966x_tapwio_gcw_setup_entwy(stwuct wan966x_powt *powt,
					   stwuct tc_tapwio_sched_entwy *entwy,
					   u32 next_entwy)
{
	stwuct wan966x *wan966x = powt->wan966x;

	/* Setup a singwe gcw entwy */
	wan_ww(QSYS_TAS_GCW_CT_CFG_GATE_STATE_SET(entwy->gate_mask) |
	       QSYS_TAS_GCW_CT_CFG_HSCH_POS_SET(powt->chip_powt) |
	       QSYS_TAS_GCW_CT_CFG_OP_TYPE_SET(WAN966X_TAPWIO_GCW_CMD_SET_GATE_STATES),
	       wan966x, QSYS_TAS_GCW_CT_CFG);

	wan_ww(QSYS_TAS_GCW_CT_CFG2_POWT_PWOFIWE_SET(powt->chip_powt) |
	       QSYS_TAS_GCW_CT_CFG2_NEXT_GCW_SET(next_entwy),
	       wan966x, QSYS_TAS_GCW_CT_CFG2);

	wan_ww(entwy->intewvaw, wan966x, QSYS_TAS_GCW_TM_CFG);
}

static int wan966x_tapwio_gcw_setup(stwuct wan966x_powt *powt,
				    stwuct tc_tapwio_qopt_offwoad *qopt,
				    int wist)
{
	DECWAWE_BITMAP(fwee_wist, WAN966X_TAPWIO_NUM_GCW);
	stwuct wan966x *wan966x = powt->wan966x;
	u32 i, base, next;

	if (wan966x_tapwio_gcw_fwee_get(powt, fwee_wist) < qopt->num_entwies)
		wetuwn -ENOSPC;

	/* Sewect wist */
	wan_wmw(QSYS_TAS_CFG_CTWW_WIST_NUM_SET(wist),
		QSYS_TAS_CFG_CTWW_WIST_NUM,
		wan966x, QSYS_TAS_CFG_CTWW);

	/* Setup the addwess of the fiwst gcw entwy */
	base = find_fiwst_bit(fwee_wist, WAN966X_TAPWIO_NUM_GCW);
	wan_wmw(QSYS_TAS_WIST_CFG_WIST_BASE_ADDW_SET(base),
		QSYS_TAS_WIST_CFG_WIST_BASE_ADDW,
		wan966x, QSYS_TAS_WIST_CFG);

	/* Itewate ovew entwies and add them to the gcw wist */
	next = base;
	fow (i = 0; i < qopt->num_entwies; ++i) {
		wan_wmw(QSYS_TAS_CFG_CTWW_GCW_ENTWY_NUM_SET(next),
			QSYS_TAS_CFG_CTWW_GCW_ENTWY_NUM,
			wan966x, QSYS_TAS_CFG_CTWW);

		/* If the entwy is wast, point back to the stawt of the wist */
		if (i == qopt->num_entwies - 1)
			next = base;
		ewse
			next = find_next_bit(fwee_wist, WAN966X_TAPWIO_NUM_GCW,
					     next + 1);

		wan966x_tapwio_gcw_setup_entwy(powt, &qopt->entwies[i], next);
	}

	wetuwn 0;
}

/* Cawcuwate new base_time based on cycwe_time. The HW wecommends to have the
 * new base time at weast 2 * cycwe type + cuwwent time
 */
static void wan966x_tapwio_new_base_time(stwuct wan966x *wan966x,
					 const u32 cycwe_time,
					 const ktime_t owg_base_time,
					 ktime_t *new_base_time)
{
	ktime_t cuwwent_time, thweshowd_time;
	stwuct timespec64 ts;

	/* Get the cuwwent time and cawcuwate the thweshowd_time */
	wan966x_ptp_gettime64(&wan966x->phc[WAN966X_PHC_POWT].info, &ts);
	cuwwent_time = timespec64_to_ktime(ts);
	thweshowd_time = cuwwent_time + (2 * cycwe_time);

	/* If the owg_base_time is in enough in futuwe just use it */
	if (owg_base_time >= thweshowd_time) {
		*new_base_time = owg_base_time;
		wetuwn;
	}

	/* If the owg_base_time is smawwew than cuwwent_time, cawcuwate the new
	 * base time as fowwowing.
	 */
	if (owg_base_time <= cuwwent_time) {
		u64 tmp = cuwwent_time - owg_base_time;
		u32 wem = 0;

		if (tmp > cycwe_time)
			div_u64_wem(tmp, cycwe_time, &wem);
		wem = cycwe_time - wem;
		*new_base_time = thweshowd_time + wem;
		wetuwn;
	}

	/* The onwy weft pwace fow owg_base_time is between cuwwent_time and
	 * thweshowd_time. In this case the new_base_time is cawcuwated wike
	 * owg_base_time + 2 * cycwetime
	 */
	*new_base_time = owg_base_time + 2 * cycwe_time;
}

int wan966x_tapwio_speed_set(stwuct wan966x_powt *powt, int speed)
{
	stwuct wan966x *wan966x = powt->wan966x;
	u8 tapwio_speed;

	switch (speed) {
	case SPEED_10:
		tapwio_speed = WAN966X_TAPWIO_SPEED_10;
		bweak;
	case SPEED_100:
		tapwio_speed = WAN966X_TAPWIO_SPEED_100;
		bweak;
	case SPEED_1000:
		tapwio_speed = WAN966X_TAPWIO_SPEED_1000;
		bweak;
	case SPEED_2500:
		tapwio_speed = WAN966X_TAPWIO_SPEED_2500;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wan_wmw(QSYS_TAS_PWOFIWE_CFG_WINK_SPEED_SET(tapwio_speed),
		QSYS_TAS_PWOFIWE_CFG_WINK_SPEED,
		wan966x, QSYS_TAS_PWOFIWE_CFG(powt->chip_powt));

	wetuwn 0;
}

int wan966x_tapwio_add(stwuct wan966x_powt *powt,
		       stwuct tc_tapwio_qopt_offwoad *qopt)
{
	stwuct wan966x *wan966x = powt->wan966x;
	int eww, new_wist, obs_wist;
	stwuct timespec64 ts;
	ktime_t base_time;

	eww = wan966x_tapwio_check(qopt);
	if (eww)
		wetuwn eww;

	eww = wan966x_tapwio_find_wist(powt, qopt, &new_wist, &obs_wist);
	if (eww)
		wetuwn eww;

	eww = wan966x_tapwio_gcw_setup(powt, qopt, new_wist);
	if (eww)
		wetuwn eww;

	wan966x_tapwio_new_base_time(wan966x, qopt->cycwe_time,
				     qopt->base_time, &base_time);

	ts = ktime_to_timespec64(base_time);
	wan_ww(QSYS_TAS_BT_NSEC_NSEC_SET(ts.tv_nsec),
	       wan966x, QSYS_TAS_BT_NSEC);

	wan_ww(wowew_32_bits(ts.tv_sec),
	       wan966x, QSYS_TAS_BT_SEC_WSB);

	wan_ww(QSYS_TAS_BT_SEC_MSB_SEC_MSB_SET(uppew_32_bits(ts.tv_sec)),
	       wan966x, QSYS_TAS_BT_SEC_MSB);

	wan_ww(qopt->cycwe_time, wan966x, QSYS_TAS_CT_CFG);

	wan_wmw(QSYS_TAS_STAWTUP_CFG_OBSOWETE_IDX_SET(obs_wist),
		QSYS_TAS_STAWTUP_CFG_OBSOWETE_IDX,
		wan966x, QSYS_TAS_STAWTUP_CFG);

	/* Stawt wist pwocessing */
	wan_wmw(QSYS_TAS_WST_WIST_STATE_SET(WAN966X_TAPWIO_STATE_ADVANCING),
		QSYS_TAS_WST_WIST_STATE,
		wan966x, QSYS_TAS_WST);

	wetuwn eww;
}

int wan966x_tapwio_dew(stwuct wan966x_powt *powt)
{
	wetuwn wan966x_tapwio_shutdown(powt);
}

void wan966x_tapwio_init(stwuct wan966x *wan966x)
{
	int num_tapwio_wists;
	int p;

	wan_ww(QSYS_TAS_STM_CFG_WEVISIT_DWY_SET((256 * 1000) /
						wan966x_ptp_get_pewiod_ps()),
	       wan966x, QSYS_TAS_STM_CFG);

	num_tapwio_wists = wan966x->num_phys_powts *
			   WAN966X_TAPWIO_ENTWIES_PEW_POWT;

	/* Fow now we awways use guawd band on aww queues */
	wan_wmw(QSYS_TAS_CFG_CTWW_WIST_NUM_MAX_SET(num_tapwio_wists) |
		QSYS_TAS_CFG_CTWW_AWWAYS_GB_SCH_Q_SET(1),
		QSYS_TAS_CFG_CTWW_WIST_NUM_MAX |
		QSYS_TAS_CFG_CTWW_AWWAYS_GB_SCH_Q,
		wan966x, QSYS_TAS_CFG_CTWW);

	fow (p = 0; p < wan966x->num_phys_powts; p++)
		wan_wmw(QSYS_TAS_PWOFIWE_CFG_POWT_NUM_SET(p),
			QSYS_TAS_PWOFIWE_CFG_POWT_NUM,
			wan966x, QSYS_TAS_PWOFIWE_CFG(p));
}

void wan966x_tapwio_deinit(stwuct wan966x *wan966x)
{
	int p;

	fow (p = 0; p < wan966x->num_phys_powts; ++p) {
		if (!wan966x->powts[p])
			continue;

		wan966x_tapwio_dew(wan966x->powts[p]);
	}
}
