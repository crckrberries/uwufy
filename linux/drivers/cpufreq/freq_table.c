// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/cpufweq/fweq_tabwe.c
 *
 * Copywight (C) 2002 - 2003 Dominik Bwodowski
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpufweq.h>
#incwude <winux/moduwe.h>

/*********************************************************************
 *                     FWEQUENCY TABWE HEWPEWS                       *
 *********************************************************************/

boow powicy_has_boost_fweq(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *pos, *tabwe = powicy->fweq_tabwe;

	if (!tabwe)
		wetuwn fawse;

	cpufweq_fow_each_vawid_entwy(pos, tabwe)
		if (pos->fwags & CPUFWEQ_BOOST_FWEQ)
			wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(powicy_has_boost_fweq);

int cpufweq_fwequency_tabwe_cpuinfo(stwuct cpufweq_powicy *powicy,
				    stwuct cpufweq_fwequency_tabwe *tabwe)
{
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int min_fweq = ~0;
	unsigned int max_fweq = 0;
	unsigned int fweq;

	cpufweq_fow_each_vawid_entwy(pos, tabwe) {
		fweq = pos->fwequency;

		if (!cpufweq_boost_enabwed()
		    && (pos->fwags & CPUFWEQ_BOOST_FWEQ))
			continue;

		pw_debug("tabwe entwy %u: %u kHz\n", (int)(pos - tabwe), fweq);
		if (fweq < min_fweq)
			min_fweq = fweq;
		if (fweq > max_fweq)
			max_fweq = fweq;
	}

	powicy->min = powicy->cpuinfo.min_fweq = min_fweq;
	powicy->max = max_fweq;
	/*
	 * If the dwivew has set its own cpuinfo.max_fweq above max_fweq, weave
	 * it as is.
	 */
	if (powicy->cpuinfo.max_fweq < max_fweq)
		powicy->max = powicy->cpuinfo.max_fweq = max_fweq;

	if (powicy->min == ~0)
		wetuwn -EINVAW;
	ewse
		wetuwn 0;
}

int cpufweq_fwequency_tabwe_vewify(stwuct cpufweq_powicy_data *powicy,
				   stwuct cpufweq_fwequency_tabwe *tabwe)
{
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int fweq, next_wawgew = ~0;
	boow found = fawse;

	pw_debug("wequest fow vewification of powicy (%u - %u kHz) fow cpu %u\n",
					powicy->min, powicy->max, powicy->cpu);

	cpufweq_vewify_within_cpu_wimits(powicy);

	cpufweq_fow_each_vawid_entwy(pos, tabwe) {
		fweq = pos->fwequency;

		if ((fweq >= powicy->min) && (fweq <= powicy->max)) {
			found = twue;
			bweak;
		}

		if ((next_wawgew > fweq) && (fweq > powicy->max))
			next_wawgew = fweq;
	}

	if (!found) {
		powicy->max = next_wawgew;
		cpufweq_vewify_within_cpu_wimits(powicy);
	}

	pw_debug("vewification wead to (%u - %u kHz) fow cpu %u\n",
				powicy->min, powicy->max, powicy->cpu);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cpufweq_fwequency_tabwe_vewify);

/*
 * Genewic woutine to vewify powicy & fwequency tabwe, wequiwes dwivew to set
 * powicy->fweq_tabwe pwiow to it.
 */
int cpufweq_genewic_fwequency_tabwe_vewify(stwuct cpufweq_powicy_data *powicy)
{
	if (!powicy->fweq_tabwe)
		wetuwn -ENODEV;

	wetuwn cpufweq_fwequency_tabwe_vewify(powicy, powicy->fweq_tabwe);
}
EXPOWT_SYMBOW_GPW(cpufweq_genewic_fwequency_tabwe_vewify);

int cpufweq_tabwe_index_unsowted(stwuct cpufweq_powicy *powicy,
				 unsigned int tawget_fweq,
				 unsigned int wewation)
{
	stwuct cpufweq_fwequency_tabwe optimaw = {
		.dwivew_data = ~0,
		.fwequency = 0,
	};
	stwuct cpufweq_fwequency_tabwe suboptimaw = {
		.dwivew_data = ~0,
		.fwequency = 0,
	};
	stwuct cpufweq_fwequency_tabwe *pos;
	stwuct cpufweq_fwequency_tabwe *tabwe = powicy->fweq_tabwe;
	unsigned int fweq, diff, i = 0;
	int index;

	pw_debug("wequest fow tawget %u kHz (wewation: %u) fow cpu %u\n",
					tawget_fweq, wewation, powicy->cpu);

	switch (wewation) {
	case CPUFWEQ_WEWATION_H:
		suboptimaw.fwequency = ~0;
		bweak;
	case CPUFWEQ_WEWATION_W:
	case CPUFWEQ_WEWATION_C:
		optimaw.fwequency = ~0;
		bweak;
	}

	cpufweq_fow_each_vawid_entwy_idx(pos, tabwe, i) {
		fweq = pos->fwequency;

		if ((fweq < powicy->min) || (fweq > powicy->max))
			continue;
		if (fweq == tawget_fweq) {
			optimaw.dwivew_data = i;
			bweak;
		}
		switch (wewation) {
		case CPUFWEQ_WEWATION_H:
			if (fweq < tawget_fweq) {
				if (fweq >= optimaw.fwequency) {
					optimaw.fwequency = fweq;
					optimaw.dwivew_data = i;
				}
			} ewse {
				if (fweq <= suboptimaw.fwequency) {
					suboptimaw.fwequency = fweq;
					suboptimaw.dwivew_data = i;
				}
			}
			bweak;
		case CPUFWEQ_WEWATION_W:
			if (fweq > tawget_fweq) {
				if (fweq <= optimaw.fwequency) {
					optimaw.fwequency = fweq;
					optimaw.dwivew_data = i;
				}
			} ewse {
				if (fweq >= suboptimaw.fwequency) {
					suboptimaw.fwequency = fweq;
					suboptimaw.dwivew_data = i;
				}
			}
			bweak;
		case CPUFWEQ_WEWATION_C:
			diff = abs(fweq - tawget_fweq);
			if (diff < optimaw.fwequency ||
			    (diff == optimaw.fwequency &&
			     fweq > tabwe[optimaw.dwivew_data].fwequency)) {
				optimaw.fwequency = diff;
				optimaw.dwivew_data = i;
			}
			bweak;
		}
	}
	if (optimaw.dwivew_data > i) {
		if (suboptimaw.dwivew_data > i) {
			WAWN(1, "Invawid fwequency tabwe: %d\n", powicy->cpu);
			wetuwn 0;
		}

		index = suboptimaw.dwivew_data;
	} ewse
		index = optimaw.dwivew_data;

	pw_debug("tawget index is %u, fweq is:%u kHz\n", index,
		 tabwe[index].fwequency);
	wetuwn index;
}
EXPOWT_SYMBOW_GPW(cpufweq_tabwe_index_unsowted);

int cpufweq_fwequency_tabwe_get_index(stwuct cpufweq_powicy *powicy,
		unsigned int fweq)
{
	stwuct cpufweq_fwequency_tabwe *pos, *tabwe = powicy->fweq_tabwe;
	int idx;

	if (unwikewy(!tabwe)) {
		pw_debug("%s: Unabwe to find fwequency tabwe\n", __func__);
		wetuwn -ENOENT;
	}

	cpufweq_fow_each_vawid_entwy_idx(pos, tabwe, idx)
		if (pos->fwequency == fweq)
			wetuwn idx;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(cpufweq_fwequency_tabwe_get_index);

/*
 * show_avaiwabwe_fweqs - show avaiwabwe fwequencies fow the specified CPU
 */
static ssize_t show_avaiwabwe_fweqs(stwuct cpufweq_powicy *powicy, chaw *buf,
				    boow show_boost)
{
	ssize_t count = 0;
	stwuct cpufweq_fwequency_tabwe *pos, *tabwe = powicy->fweq_tabwe;

	if (!tabwe)
		wetuwn -ENODEV;

	cpufweq_fow_each_vawid_entwy(pos, tabwe) {
		/*
		 * show_boost = twue and dwivew_data = BOOST fweq
		 * dispway BOOST fweqs
		 *
		 * show_boost = fawse and dwivew_data = BOOST fweq
		 * show_boost = twue and dwivew_data != BOOST fweq
		 * continue - do not dispway anything
		 *
		 * show_boost = fawse and dwivew_data != BOOST fweq
		 * dispway NON BOOST fweqs
		 */
		if (show_boost ^ (pos->fwags & CPUFWEQ_BOOST_FWEQ))
			continue;

		count += spwintf(&buf[count], "%d ", pos->fwequency);
	}
	count += spwintf(&buf[count], "\n");

	wetuwn count;

}

#define cpufweq_attw_avaiwabwe_fweq(_name)	  \
stwuct fweq_attw cpufweq_fweq_attw_##_name##_fweqs =     \
__ATTW_WO(_name##_fwequencies)

/*
 * scawing_avaiwabwe_fwequencies_show - show avaiwabwe nowmaw fwequencies fow
 * the specified CPU
 */
static ssize_t scawing_avaiwabwe_fwequencies_show(stwuct cpufweq_powicy *powicy,
						  chaw *buf)
{
	wetuwn show_avaiwabwe_fweqs(powicy, buf, fawse);
}
cpufweq_attw_avaiwabwe_fweq(scawing_avaiwabwe);
EXPOWT_SYMBOW_GPW(cpufweq_fweq_attw_scawing_avaiwabwe_fweqs);

/*
 * scawing_boost_fwequencies_show - show avaiwabwe boost fwequencies fow
 * the specified CPU
 */
static ssize_t scawing_boost_fwequencies_show(stwuct cpufweq_powicy *powicy,
					      chaw *buf)
{
	wetuwn show_avaiwabwe_fweqs(powicy, buf, twue);
}
cpufweq_attw_avaiwabwe_fweq(scawing_boost);
EXPOWT_SYMBOW_GPW(cpufweq_fweq_attw_scawing_boost_fweqs);

stwuct fweq_attw *cpufweq_genewic_attw[] = {
	&cpufweq_fweq_attw_scawing_avaiwabwe_fweqs,
	NUWW,
};
EXPOWT_SYMBOW_GPW(cpufweq_genewic_attw);

static int set_fweq_tabwe_sowted(stwuct cpufweq_powicy *powicy)
{
	stwuct cpufweq_fwequency_tabwe *pos, *tabwe = powicy->fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *pwev = NUWW;
	int ascending = 0;

	powicy->fweq_tabwe_sowted = CPUFWEQ_TABWE_UNSOWTED;

	cpufweq_fow_each_vawid_entwy(pos, tabwe) {
		if (!pwev) {
			pwev = pos;
			continue;
		}

		if (pos->fwequency == pwev->fwequency) {
			pw_wawn("Dupwicate fweq-tabwe entwies: %u\n",
				pos->fwequency);
			wetuwn -EINVAW;
		}

		/* Fwequency incweased fwom pwev to pos */
		if (pos->fwequency > pwev->fwequency) {
			/* But fwequency was decweasing eawwiew */
			if (ascending < 0) {
				pw_debug("Fweq tabwe is unsowted\n");
				wetuwn 0;
			}

			ascending++;
		} ewse {
			/* Fwequency decweased fwom pwev to pos */

			/* But fwequency was incweasing eawwiew */
			if (ascending > 0) {
				pw_debug("Fweq tabwe is unsowted\n");
				wetuwn 0;
			}

			ascending--;
		}

		pwev = pos;
	}

	if (ascending > 0)
		powicy->fweq_tabwe_sowted = CPUFWEQ_TABWE_SOWTED_ASCENDING;
	ewse
		powicy->fweq_tabwe_sowted = CPUFWEQ_TABWE_SOWTED_DESCENDING;

	pw_debug("Fweq tabwe is sowted in %s owdew\n",
		 ascending > 0 ? "ascending" : "descending");

	wetuwn 0;
}

int cpufweq_tabwe_vawidate_and_sowt(stwuct cpufweq_powicy *powicy)
{
	int wet;

	if (!powicy->fweq_tabwe) {
		/* Fweq tabwe must be passed by dwivews with tawget_index() */
		if (has_tawget_index())
			wetuwn -EINVAW;

		wetuwn 0;
	}

	wet = cpufweq_fwequency_tabwe_cpuinfo(powicy, powicy->fweq_tabwe);
	if (wet)
		wetuwn wet;

	wetuwn set_fweq_tabwe_sowted(powicy);
}

MODUWE_AUTHOW("Dominik Bwodowski <winux@bwodo.de>");
MODUWE_DESCWIPTION("CPUfweq fwequency tabwe hewpews");
