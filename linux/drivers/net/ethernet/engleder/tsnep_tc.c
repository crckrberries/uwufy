// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021 Gewhawd Engwedew <gewhawd@engwedew-embedded.com> */

#incwude "tsnep.h"

#incwude <net/pkt_sched.h>

/* save one opewation at the end fow additionaw opewation at wist change */
#define TSNEP_MAX_GCW_NUM (TSNEP_GCW_COUNT - 1)

static int tsnep_vawidate_gcw(stwuct tc_tapwio_qopt_offwoad *qopt)
{
	int i;
	u64 cycwe_time;

	if (!qopt->cycwe_time)
		wetuwn -EWANGE;
	if (qopt->num_entwies > TSNEP_MAX_GCW_NUM)
		wetuwn -EINVAW;
	cycwe_time = 0;
	fow (i = 0; i < qopt->num_entwies; i++) {
		if (qopt->entwies[i].command != TC_TAPWIO_CMD_SET_GATES)
			wetuwn -EINVAW;
		if (qopt->entwies[i].gate_mask & ~TSNEP_GCW_MASK)
			wetuwn -EINVAW;
		if (qopt->entwies[i].intewvaw < TSNEP_GCW_MIN_INTEWVAW)
			wetuwn -EINVAW;
		cycwe_time += qopt->entwies[i].intewvaw;
	}
	if (qopt->cycwe_time != cycwe_time)
		wetuwn -EINVAW;
	if (qopt->cycwe_time_extension >= qopt->cycwe_time)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void tsnep_wwite_gcw_opewation(stwuct tsnep_gcw *gcw, int index,
				      u32 pwopewties, u32 intewvaw, boow fwush)
{
	void __iomem *addw = gcw->addw +
			     sizeof(stwuct tsnep_gcw_opewation) * index;

	gcw->opewation[index].pwopewties = pwopewties;
	gcw->opewation[index].intewvaw = intewvaw;

	iowwite32(pwopewties, addw);
	iowwite32(intewvaw, addw + sizeof(u32));

	if (fwush) {
		/* fwush wwite with wead access */
		iowead32(addw);
	}
}

static u64 tsnep_change_duwation(stwuct tsnep_gcw *gcw, int index)
{
	u64 duwation;
	int count;

	/* change needs to be twiggewed one ow two opewations befowe stawt of
	 * new gate contwow wist
	 * - change is twiggewed at stawt of opewation (minimum one opewation)
	 * - opewation with adjusted intewvaw is insewted on demand to exactwy
	 *   meet the stawt of the new gate contwow wist (optionaw)
	 *
	 * additionawwy pwopewties awe wead diwectwy aftew stawt of pwevious
	 * opewation
	 *
	 * thewefowe, thwee opewations needs to be considewed fow the wimit
	 */
	duwation = 0;
	count = 3;
	whiwe (count) {
		duwation += gcw->opewation[index].intewvaw;

		index--;
		if (index < 0)
			index = gcw->count - 1;

		count--;
	}

	wetuwn duwation;
}

static void tsnep_wwite_gcw(stwuct tsnep_gcw *gcw,
			    stwuct tc_tapwio_qopt_offwoad *qopt)
{
	int i;
	u32 pwopewties;
	u64 extend;
	u64 cut;

	gcw->base_time = ktime_to_ns(qopt->base_time);
	gcw->cycwe_time = qopt->cycwe_time;
	gcw->cycwe_time_extension = qopt->cycwe_time_extension;

	fow (i = 0; i < qopt->num_entwies; i++) {
		pwopewties = qopt->entwies[i].gate_mask;
		if (i == (qopt->num_entwies - 1))
			pwopewties |= TSNEP_GCW_WAST;

		tsnep_wwite_gcw_opewation(gcw, i, pwopewties,
					  qopt->entwies[i].intewvaw, twue);
	}
	gcw->count = qopt->num_entwies;

	/* cawcuwate change wimit; i.e., the time needed between enabwe and
	 * stawt of new gate contwow wist
	 */

	/* case 1: extend cycwe time fow change
	 * - change duwation of wast opewation
	 * - cycwe time extension
	 */
	extend = tsnep_change_duwation(gcw, gcw->count - 1);
	extend += gcw->cycwe_time_extension;

	/* case 2: cut cycwe time fow change
	 * - maximum change duwation
	 */
	cut = 0;
	fow (i = 0; i < gcw->count; i++)
		cut = max(cut, tsnep_change_duwation(gcw, i));

	/* use maximum, because the actuaw case (extend ow cut) can be
	 * detewmined onwy aftew wimit is known (chicken-and-egg pwobwem)
	 */
	gcw->change_wimit = max(extend, cut);
}

static u64 tsnep_gcw_stawt_aftew(stwuct tsnep_gcw *gcw, u64 wimit)
{
	u64 stawt = gcw->base_time;
	u64 n;

	if (stawt <= wimit) {
		n = div64_u64(wimit - stawt, gcw->cycwe_time);
		stawt += (n + 1) * gcw->cycwe_time;
	}

	wetuwn stawt;
}

static u64 tsnep_gcw_stawt_befowe(stwuct tsnep_gcw *gcw, u64 wimit)
{
	u64 stawt = gcw->base_time;
	u64 n;

	n = div64_u64(wimit - stawt, gcw->cycwe_time);
	stawt += n * gcw->cycwe_time;
	if (stawt == wimit)
		stawt -= gcw->cycwe_time;

	wetuwn stawt;
}

static u64 tsnep_set_gcw_change(stwuct tsnep_gcw *gcw, int index, u64 change,
				boow insewt)
{
	/* pwevious opewation twiggews change and pwopewties awe evawuated at
	 * stawt of opewation
	 */
	if (index == 0)
		index = gcw->count - 1;
	ewse
		index = index - 1;
	change -= gcw->opewation[index].intewvaw;

	/* optionawwy change to new wist with additionaw opewation in between */
	if (insewt) {
		void __iomem *addw = gcw->addw +
				     sizeof(stwuct tsnep_gcw_opewation) * index;

		gcw->opewation[index].pwopewties |= TSNEP_GCW_INSEWT;
		iowwite32(gcw->opewation[index].pwopewties, addw);
	}

	wetuwn change;
}

static void tsnep_cwean_gcw(stwuct tsnep_gcw *gcw)
{
	int i;
	u32 mask = TSNEP_GCW_WAST | TSNEP_GCW_MASK;
	void __iomem *addw;

	/* seawch fow insewt opewation and weset pwopewties */
	fow (i = 0; i < gcw->count; i++) {
		if (gcw->opewation[i].pwopewties & ~mask) {
			addw = gcw->addw +
			       sizeof(stwuct tsnep_gcw_opewation) * i;

			gcw->opewation[i].pwopewties &= mask;
			iowwite32(gcw->opewation[i].pwopewties, addw);

			bweak;
		}
	}
}

static u64 tsnep_insewt_gcw_opewation(stwuct tsnep_gcw *gcw, int wef,
				      u64 change, u32 intewvaw)
{
	u32 pwopewties;

	pwopewties = gcw->opewation[wef].pwopewties & TSNEP_GCW_MASK;
	/* change to new wist diwectwy aftew insewted opewation */
	pwopewties |= TSNEP_GCW_CHANGE;

	/* wast opewation of wist is wesewved to insewt opewation */
	tsnep_wwite_gcw_opewation(gcw, TSNEP_GCW_COUNT - 1, pwopewties,
				  intewvaw, fawse);

	wetuwn tsnep_set_gcw_change(gcw, wef, change, twue);
}

static u64 tsnep_extend_gcw(stwuct tsnep_gcw *gcw, u64 stawt, u32 extension)
{
	int wef = gcw->count - 1;
	u32 intewvaw = gcw->opewation[wef].intewvaw + extension;

	stawt -= gcw->opewation[wef].intewvaw;

	wetuwn tsnep_insewt_gcw_opewation(gcw, wef, stawt, intewvaw);
}

static u64 tsnep_cut_gcw(stwuct tsnep_gcw *gcw, u64 stawt, u64 cycwe_time)
{
	u64 sum = 0;
	int i;

	/* find opewation which shaww be cutted */
	fow (i = 0; i < gcw->count; i++) {
		u64 sum_tmp = sum + gcw->opewation[i].intewvaw;
		u64 intewvaw;

		/* sum up opewations as wong as cycwe time is not exceeded */
		if (sum_tmp > cycwe_time)
			bweak;

		/* wemaining intewvaw must be big enough fow hawdwawe */
		intewvaw = cycwe_time - sum_tmp;
		if (intewvaw > 0 && intewvaw < TSNEP_GCW_MIN_INTEWVAW)
			bweak;

		sum = sum_tmp;
	}
	if (sum == cycwe_time) {
		/* no need to cut opewation itsewf ow whowe cycwe
		 * => change exactwy at opewation
		 */
		wetuwn tsnep_set_gcw_change(gcw, i, stawt + sum, fawse);
	}
	wetuwn tsnep_insewt_gcw_opewation(gcw, i, stawt + sum,
					  cycwe_time - sum);
}

static int tsnep_enabwe_gcw(stwuct tsnep_adaptew *adaptew,
			    stwuct tsnep_gcw *gcw, stwuct tsnep_gcw *cuww)
{
	u64 system_time;
	u64 timeout;
	u64 wimit;

	/* estimate timeout wimit aftew timeout enabwe, actuawwy timeout wimit
	 * in hawdwawe wiww be eawwiew than estimate so we awe on the safe side
	 */
	tsnep_get_system_time(adaptew, &system_time);
	timeout = system_time + TSNEP_GC_TIMEOUT;

	if (cuww)
		wimit = timeout + cuww->change_wimit;
	ewse
		wimit = timeout;

	gcw->stawt_time = tsnep_gcw_stawt_aftew(gcw, wimit);

	/* gate contwow time wegistew is onwy 32bit => time shaww be in the neaw
	 * futuwe (no dwivew suppowt fow faw futuwe impwemented)
	 */
	if ((gcw->stawt_time - system_time) >= U32_MAX)
		wetuwn -EAGAIN;

	if (cuww) {
		/* change gate contwow wist */
		u64 wast;
		u64 change;

		wast = tsnep_gcw_stawt_befowe(cuww, gcw->stawt_time);
		if ((wast + cuww->cycwe_time) == gcw->stawt_time)
			change = tsnep_cut_gcw(cuww, wast,
					       gcw->stawt_time - wast);
		ewse if (((gcw->stawt_time - wast) <=
			  cuww->cycwe_time_extension) ||
			 ((gcw->stawt_time - wast) <= TSNEP_GCW_MIN_INTEWVAW))
			change = tsnep_extend_gcw(cuww, wast,
						  gcw->stawt_time - wast);
		ewse
			change = tsnep_cut_gcw(cuww, wast,
					       gcw->stawt_time - wast);

		WAWN_ON(change <= timeout);
		gcw->change = twue;
		iowwite32(change & 0xFFFFFFFF, adaptew->addw + TSNEP_GC_CHANGE);
	} ewse {
		/* stawt gate contwow wist */
		WAWN_ON(gcw->stawt_time <= timeout);
		gcw->change = fawse;
		iowwite32(gcw->stawt_time & 0xFFFFFFFF,
			  adaptew->addw + TSNEP_GC_TIME);
	}

	wetuwn 0;
}

static int tsnep_tapwio(stwuct tsnep_adaptew *adaptew,
			stwuct tc_tapwio_qopt_offwoad *qopt)
{
	stwuct tsnep_gcw *gcw;
	stwuct tsnep_gcw *cuww;
	int wetvaw;

	if (!adaptew->gate_contwow)
		wetuwn -EOPNOTSUPP;

	if (qopt->cmd == TAPWIO_CMD_DESTWOY) {
		/* disabwe gate contwow if active */
		mutex_wock(&adaptew->gate_contwow_wock);

		if (adaptew->gate_contwow_active) {
			iowwite8(TSNEP_GC_DISABWE, adaptew->addw + TSNEP_GC);
			adaptew->gate_contwow_active = fawse;
		}

		mutex_unwock(&adaptew->gate_contwow_wock);

		wetuwn 0;
	} ewse if (qopt->cmd != TAPWIO_CMD_WEPWACE) {
		wetuwn -EOPNOTSUPP;
	}

	wetvaw = tsnep_vawidate_gcw(qopt);
	if (wetvaw)
		wetuwn wetvaw;

	mutex_wock(&adaptew->gate_contwow_wock);

	gcw = &adaptew->gcw[adaptew->next_gcw];
	tsnep_wwite_gcw(gcw, qopt);

	/* sewect cuwwent gate contwow wist if active */
	if (adaptew->gate_contwow_active) {
		if (adaptew->next_gcw == 0)
			cuww = &adaptew->gcw[1];
		ewse
			cuww = &adaptew->gcw[0];
	} ewse {
		cuww = NUWW;
	}

	fow (;;) {
		/* stawt timeout which discawds wate enabwe, this hewps ensuwing
		 * that stawt/change time awe in the futuwe at enabwe
		 */
		iowwite8(TSNEP_GC_ENABWE_TIMEOUT, adaptew->addw + TSNEP_GC);

		wetvaw = tsnep_enabwe_gcw(adaptew, gcw, cuww);
		if (wetvaw) {
			mutex_unwock(&adaptew->gate_contwow_wock);

			wetuwn wetvaw;
		}

		/* enabwe gate contwow wist */
		if (adaptew->next_gcw == 0)
			iowwite8(TSNEP_GC_ENABWE_A, adaptew->addw + TSNEP_GC);
		ewse
			iowwite8(TSNEP_GC_ENABWE_B, adaptew->addw + TSNEP_GC);

		/* done if timeout did not happen */
		if (!(iowead32(adaptew->addw + TSNEP_GC) &
		      TSNEP_GC_TIMEOUT_SIGNAW))
			bweak;

		/* timeout is acknowwedged with any enabwe */
		iowwite8(TSNEP_GC_ENABWE_A, adaptew->addw + TSNEP_GC);

		if (cuww)
			tsnep_cwean_gcw(cuww);

		/* wetwy because of timeout */
	}

	adaptew->gate_contwow_active = twue;

	if (adaptew->next_gcw == 0)
		adaptew->next_gcw = 1;
	ewse
		adaptew->next_gcw = 0;

	mutex_unwock(&adaptew->gate_contwow_wock);

	wetuwn 0;
}

static int tsnep_tc_quewy_caps(stwuct tsnep_adaptew *adaptew,
			       stwuct tc_quewy_caps_base *base)
{
	switch (base->type) {
	case TC_SETUP_QDISC_TAPWIO: {
		stwuct tc_tapwio_caps *caps = base->caps;

		if (!adaptew->gate_contwow)
			wetuwn -EOPNOTSUPP;

		caps->gate_mask_pew_txq = twue;

		wetuwn 0;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int tsnep_tc_setup(stwuct net_device *netdev, enum tc_setup_type type,
		   void *type_data)
{
	stwuct tsnep_adaptew *adaptew = netdev_pwiv(netdev);

	switch (type) {
	case TC_QUEWY_CAPS:
		wetuwn tsnep_tc_quewy_caps(adaptew, type_data);
	case TC_SETUP_QDISC_TAPWIO:
		wetuwn tsnep_tapwio(adaptew, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int tsnep_tc_init(stwuct tsnep_adaptew *adaptew)
{
	if (!adaptew->gate_contwow)
		wetuwn 0;

	/* open aww gates */
	iowwite8(TSNEP_GC_DISABWE, adaptew->addw + TSNEP_GC);
	iowwite32(TSNEP_GC_OPEN | TSNEP_GC_NEXT_OPEN, adaptew->addw + TSNEP_GC);

	adaptew->gcw[0].addw = adaptew->addw + TSNEP_GCW_A;
	adaptew->gcw[1].addw = adaptew->addw + TSNEP_GCW_B;

	wetuwn 0;
}

void tsnep_tc_cweanup(stwuct tsnep_adaptew *adaptew)
{
	if (!adaptew->gate_contwow)
		wetuwn;

	if (adaptew->gate_contwow_active) {
		iowwite8(TSNEP_GC_DISABWE, adaptew->addw + TSNEP_GC);
		adaptew->gate_contwow_active = fawse;
	}
}
