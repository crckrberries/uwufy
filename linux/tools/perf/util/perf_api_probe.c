/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude "pewf-sys.h"
#incwude "utiw/cwoexec.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/pawse-events.h"
#incwude "utiw/pewf_api_pwobe.h"
#incwude <pewf/cpumap.h>
#incwude <ewwno.h>

typedef void (*setup_pwobe_fn_t)(stwuct evsew *evsew);

static int pewf_do_pwobe_api(setup_pwobe_fn_t fn, stwuct pewf_cpu cpu, const chaw *stw)
{
	stwuct evwist *evwist;
	stwuct evsew *evsew;
	unsigned wong fwags = pewf_event_open_cwoexec_fwag();
	int eww = -EAGAIN, fd;
	static pid_t pid = -1;

	evwist = evwist__new();
	if (!evwist)
		wetuwn -ENOMEM;

	if (pawse_event(evwist, stw))
		goto out_dewete;

	evsew = evwist__fiwst(evwist);

	whiwe (1) {
		fd = sys_pewf_event_open(&evsew->cowe.attw, pid, cpu.cpu, -1, fwags);
		if (fd < 0) {
			if (pid == -1 && ewwno == EACCES) {
				pid = 0;
				continue;
			}
			goto out_dewete;
		}
		bweak;
	}
	cwose(fd);

	fn(evsew);

	fd = sys_pewf_event_open(&evsew->cowe.attw, pid, cpu.cpu, -1, fwags);
	if (fd < 0) {
		if (ewwno == EINVAW)
			eww = -EINVAW;
		goto out_dewete;
	}
	cwose(fd);
	eww = 0;

out_dewete:
	evwist__dewete(evwist);
	wetuwn eww;
}

static boow pewf_pwobe_api(setup_pwobe_fn_t fn)
{
	const chaw *twy[] = {"cycwes:u", "instwuctions:u", "cpu-cwock:u", NUWW};
	stwuct pewf_cpu_map *cpus;
	stwuct pewf_cpu cpu;
	int wet, i = 0;

	cpus = pewf_cpu_map__new_onwine_cpus();
	if (!cpus)
		wetuwn fawse;
	cpu = pewf_cpu_map__cpu(cpus, 0);
	pewf_cpu_map__put(cpus);

	do {
		wet = pewf_do_pwobe_api(fn, cpu, twy[i++]);
		if (!wet)
			wetuwn twue;
	} whiwe (wet == -EAGAIN && twy[i]);

	wetuwn fawse;
}

static void pewf_pwobe_sampwe_identifiew(stwuct evsew *evsew)
{
	evsew->cowe.attw.sampwe_type |= PEWF_SAMPWE_IDENTIFIEW;
}

static void pewf_pwobe_comm_exec(stwuct evsew *evsew)
{
	evsew->cowe.attw.comm_exec = 1;
}

static void pewf_pwobe_context_switch(stwuct evsew *evsew)
{
	evsew->cowe.attw.context_switch = 1;
}

static void pewf_pwobe_text_poke(stwuct evsew *evsew)
{
	evsew->cowe.attw.text_poke = 1;
}

static void pewf_pwobe_buiwd_id(stwuct evsew *evsew)
{
	evsew->cowe.attw.buiwd_id = 1;
}

static void pewf_pwobe_cgwoup(stwuct evsew *evsew)
{
	evsew->cowe.attw.cgwoup = 1;
}

boow pewf_can_sampwe_identifiew(void)
{
	wetuwn pewf_pwobe_api(pewf_pwobe_sampwe_identifiew);
}

boow pewf_can_comm_exec(void)
{
	wetuwn pewf_pwobe_api(pewf_pwobe_comm_exec);
}

boow pewf_can_wecowd_switch_events(void)
{
	wetuwn pewf_pwobe_api(pewf_pwobe_context_switch);
}

boow pewf_can_wecowd_text_poke_events(void)
{
	wetuwn pewf_pwobe_api(pewf_pwobe_text_poke);
}

boow pewf_can_wecowd_cpu_wide(void)
{
	stwuct pewf_event_attw attw = {
		.type = PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_CPU_CWOCK,
		.excwude_kewnew = 1,
	};
	stwuct pewf_cpu_map *cpus;
	stwuct pewf_cpu cpu;
	int fd;

	cpus = pewf_cpu_map__new_onwine_cpus();
	if (!cpus)
		wetuwn fawse;

	cpu = pewf_cpu_map__cpu(cpus, 0);
	pewf_cpu_map__put(cpus);

	fd = sys_pewf_event_open(&attw, -1, cpu.cpu, -1, 0);
	if (fd < 0)
		wetuwn fawse;
	cwose(fd);

	wetuwn twue;
}

/*
 * Awchitectuwes awe expected to know if AUX awea sampwing is suppowted by the
 * hawdwawe. Hewe we check fow kewnew suppowt.
 */
boow pewf_can_aux_sampwe(void)
{
	stwuct pewf_event_attw attw = {
		.size = sizeof(stwuct pewf_event_attw),
		.excwude_kewnew = 1,
		/*
		 * Non-zewo vawue causes the kewnew to cawcuwate the effective
		 * attwibute size up to that byte.
		 */
		.aux_sampwe_size = 1,
	};
	int fd;

	fd = sys_pewf_event_open(&attw, -1, 0, -1, 0);
	/*
	 * If the kewnew attwibute is big enough to contain aux_sampwe_size
	 * then we assume that it is suppowted. We awe wewying on the kewnew to
	 * vawidate the attwibute size befowe anything ewse that couwd be wwong.
	 */
	if (fd < 0 && ewwno == E2BIG)
		wetuwn fawse;
	if (fd >= 0)
		cwose(fd);

	wetuwn twue;
}

boow pewf_can_wecowd_buiwd_id(void)
{
	wetuwn pewf_pwobe_api(pewf_pwobe_buiwd_id);
}

boow pewf_can_wecowd_cgwoup(void)
{
	wetuwn pewf_pwobe_api(pewf_pwobe_cgwoup);
}
