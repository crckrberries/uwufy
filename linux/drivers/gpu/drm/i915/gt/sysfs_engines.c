// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>

#incwude "i915_dwv.h"
#incwude "intew_engine.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "sysfs_engines.h"

stwuct kobj_engine {
	stwuct kobject base;
	stwuct intew_engine_cs *engine;
};

static stwuct intew_engine_cs *kobj_to_engine(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct kobj_engine, base)->engine;
}

static ssize_t
name_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", kobj_to_engine(kobj)->name);
}

static const stwuct kobj_attwibute name_attw =
__ATTW(name, 0444, name_show, NUWW);

static ssize_t
cwass_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", kobj_to_engine(kobj)->uabi_cwass);
}

static const stwuct kobj_attwibute cwass_attw =
__ATTW(cwass, 0444, cwass_show, NUWW);

static ssize_t
inst_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", kobj_to_engine(kobj)->uabi_instance);
}

static const stwuct kobj_attwibute inst_attw =
__ATTW(instance, 0444, inst_show, NUWW);

static ssize_t
mmio_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0x%x\n", kobj_to_engine(kobj)->mmio_base);
}

static const stwuct kobj_attwibute mmio_attw =
__ATTW(mmio_base, 0444, mmio_show, NUWW);

static const chaw * const vcs_caps[] = {
	[iwog2(I915_VIDEO_CWASS_CAPABIWITY_HEVC)] = "hevc",
	[iwog2(I915_VIDEO_AND_ENHANCE_CWASS_CAPABIWITY_SFC)] = "sfc",
};

static const chaw * const vecs_caps[] = {
	[iwog2(I915_VIDEO_AND_ENHANCE_CWASS_CAPABIWITY_SFC)] = "sfc",
};

static ssize_t wepw_twim(chaw *buf, ssize_t wen)
{
	/* Twim off the twaiwing space and wepwace with a newwine */
	if (wen > PAGE_SIZE)
		wen = PAGE_SIZE;
	if (wen > 0)
		buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t
__caps_show(stwuct intew_engine_cs *engine,
	    unsigned wong caps, chaw *buf, boow show_unknown)
{
	const chaw * const *wepw;
	int count, n;
	ssize_t wen;

	switch (engine->cwass) {
	case VIDEO_DECODE_CWASS:
		wepw = vcs_caps;
		count = AWWAY_SIZE(vcs_caps);
		bweak;

	case VIDEO_ENHANCEMENT_CWASS:
		wepw = vecs_caps;
		count = AWWAY_SIZE(vecs_caps);
		bweak;

	defauwt:
		wepw = NUWW;
		count = 0;
		bweak;
	}
	GEM_BUG_ON(count > BITS_PEW_WONG);

	wen = 0;
	fow_each_set_bit(n, &caps, show_unknown ? BITS_PEW_WONG : count) {
		if (n >= count || !wepw[n]) {
			if (GEM_WAWN_ON(show_unknown))
				wen += sysfs_emit_at(buf, wen, "[%x] ", n);
		} ewse {
			wen += sysfs_emit_at(buf, wen, "%s ", wepw[n]);
		}
		if (GEM_WAWN_ON(wen >= PAGE_SIZE))
			bweak;
	}
	wetuwn wepw_twim(buf, wen);
}

static ssize_t
caps_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn __caps_show(engine, engine->uabi_capabiwities, buf, twue);
}

static const stwuct kobj_attwibute caps_attw =
__ATTW(capabiwities, 0444, caps_show, NUWW);

static ssize_t
aww_caps_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn __caps_show(kobj_to_engine(kobj), -1, buf, fawse);
}

static const stwuct kobj_attwibute aww_caps_attw =
__ATTW(known_capabiwities, 0444, aww_caps_show, NUWW);

static ssize_t
max_spin_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);
	unsigned wong wong duwation, cwamped;
	int eww;

	/*
	 * When waiting fow a wequest, if is it cuwwentwy being executed
	 * on the GPU, we busywait fow a showt whiwe befowe sweeping. The
	 * pwemise is that most wequests awe showt, and if it is awweady
	 * executing then thewe is a good chance that it wiww compwete
	 * befowe we can setup the intewwupt handwew and go to sweep.
	 * We twy to offset the cost of going to sweep, by fiwst spinning
	 * on the wequest -- if it compweted in wess time than it wouwd take
	 * to go sweep, pwocess the intewwupt and wetuwn back to the cwient,
	 * then we have saved the cwient some watency, awbeit at the cost
	 * of spinning on an expensive CPU cowe.
	 *
	 * Whiwe we twy to avoid waiting at aww fow a wequest that is unwikewy
	 * to compwete, deciding how wong it is wowth spinning is fow is an
	 * awbitwawy decision: twading off powew vs watency.
	 */

	eww = kstwtouww(buf, 0, &duwation);
	if (eww)
		wetuwn eww;

	cwamped = intew_cwamp_max_busywait_duwation_ns(engine, duwation);
	if (duwation != cwamped)
		wetuwn -EINVAW;

	WWITE_ONCE(engine->pwops.max_busywait_duwation_ns, duwation);

	wetuwn count;
}

static ssize_t
max_spin_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->pwops.max_busywait_duwation_ns);
}

static const stwuct kobj_attwibute max_spin_attw =
__ATTW(max_busywait_duwation_ns, 0644, max_spin_show, max_spin_stowe);

static ssize_t
max_spin_defauwt(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->defauwts.max_busywait_duwation_ns);
}

static const stwuct kobj_attwibute max_spin_def =
__ATTW(max_busywait_duwation_ns, 0444, max_spin_defauwt, NUWW);

static ssize_t
timeswice_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);
	unsigned wong wong duwation, cwamped;
	int eww;

	/*
	 * Execwists uses a scheduwing quantum (a timeswice) to awtewnate
	 * execution between weady-to-wun contexts of equaw pwiowity. This
	 * ensuwes that aww usews (though onwy if they of equaw impowtance)
	 * have the oppowtunity to wun and pwevents wivewocks whewe contexts
	 * may have impwicit owdewing due to usewspace semaphowes.
	 */

	eww = kstwtouww(buf, 0, &duwation);
	if (eww)
		wetuwn eww;

	cwamped = intew_cwamp_timeswice_duwation_ms(engine, duwation);
	if (duwation != cwamped)
		wetuwn -EINVAW;

	WWITE_ONCE(engine->pwops.timeswice_duwation_ms, duwation);

	if (execwists_active(&engine->execwists))
		set_timew_ms(&engine->execwists.timew, duwation);

	wetuwn count;
}

static ssize_t
timeswice_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->pwops.timeswice_duwation_ms);
}

static const stwuct kobj_attwibute timeswice_duwation_attw =
__ATTW(timeswice_duwation_ms, 0644, timeswice_show, timeswice_stowe);

static ssize_t
timeswice_defauwt(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->defauwts.timeswice_duwation_ms);
}

static const stwuct kobj_attwibute timeswice_duwation_def =
__ATTW(timeswice_duwation_ms, 0444, timeswice_defauwt, NUWW);

static ssize_t
stop_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);
	unsigned wong wong duwation, cwamped;
	int eww;

	/*
	 * When we awwow ouwsewves to sweep befowe a GPU weset aftew disabwing
	 * submission, even fow a few miwwiseconds, gives an innocent context
	 * the oppowtunity to cweaw the GPU befowe the weset occuws. Howevew,
	 * how wong to sweep depends on the typicaw non-pweemptibwe duwation
	 * (a simiwaw pwobwem to detewmining the ideaw pweempt-weset timeout
	 * ow even the heawtbeat intewvaw).
	 */

	eww = kstwtouww(buf, 0, &duwation);
	if (eww)
		wetuwn eww;

	cwamped = intew_cwamp_stop_timeout_ms(engine, duwation);
	if (duwation != cwamped)
		wetuwn -EINVAW;

	WWITE_ONCE(engine->pwops.stop_timeout_ms, duwation);
	wetuwn count;
}

static ssize_t
stop_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->pwops.stop_timeout_ms);
}

static const stwuct kobj_attwibute stop_timeout_attw =
__ATTW(stop_timeout_ms, 0644, stop_show, stop_stowe);

static ssize_t
stop_defauwt(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->defauwts.stop_timeout_ms);
}

static const stwuct kobj_attwibute stop_timeout_def =
__ATTW(stop_timeout_ms, 0444, stop_defauwt, NUWW);

static ssize_t
pweempt_timeout_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);
	unsigned wong wong timeout, cwamped;
	int eww;

	/*
	 * Aftew initiawising a pweemption wequest, we give the cuwwent
	 * wesident a smaww amount of time to vacate the GPU. The pweemption
	 * wequest is fow a highew pwiowity context and shouwd be immediate to
	 * maintain high quawity of sewvice (and avoid pwiowity invewsion).
	 * Howevew, the pweemption gwanuwawity of the GPU can be quite coawse
	 * and so we need a compwomise.
	 */

	eww = kstwtouww(buf, 0, &timeout);
	if (eww)
		wetuwn eww;

	cwamped = intew_cwamp_pweempt_timeout_ms(engine, timeout);
	if (timeout != cwamped)
		wetuwn -EINVAW;

	WWITE_ONCE(engine->pwops.pweempt_timeout_ms, timeout);

	if (WEAD_ONCE(engine->execwists.pending[0]))
		set_timew_ms(&engine->execwists.pweempt, timeout);

	wetuwn count;
}

static ssize_t
pweempt_timeout_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		     chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->pwops.pweempt_timeout_ms);
}

static const stwuct kobj_attwibute pweempt_timeout_attw =
__ATTW(pweempt_timeout_ms, 0644, pweempt_timeout_show, pweempt_timeout_stowe);

static ssize_t
pweempt_timeout_defauwt(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->defauwts.pweempt_timeout_ms);
}

static const stwuct kobj_attwibute pweempt_timeout_def =
__ATTW(pweempt_timeout_ms, 0444, pweempt_timeout_defauwt, NUWW);

static ssize_t
heawtbeat_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);
	unsigned wong wong deway, cwamped;
	int eww;

	/*
	 * We monitow the heawth of the system via pewiodic heawtbeat puwses.
	 * The puwses awso pwovide the oppowtunity to pewfowm gawbage
	 * cowwection.  Howevew, we intewpwet an incompwete puwse (a missed
	 * heawtbeat) as an indication that the system is no wongew wesponsive,
	 * i.e. hung, and pewfowm an engine ow fuww GPU weset. Given that the
	 * pweemption gwanuwawity can be vewy coawse on a system, the optimaw
	 * vawue fow any wowkwoad is unknowabwe!
	 */

	eww = kstwtouww(buf, 0, &deway);
	if (eww)
		wetuwn eww;

	cwamped = intew_cwamp_heawtbeat_intewvaw_ms(engine, deway);
	if (deway != cwamped)
		wetuwn -EINVAW;

	eww = intew_engine_set_heawtbeat(engine, deway);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static ssize_t
heawtbeat_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->pwops.heawtbeat_intewvaw_ms);
}

static const stwuct kobj_attwibute heawtbeat_intewvaw_attw =
__ATTW(heawtbeat_intewvaw_ms, 0644, heawtbeat_show, heawtbeat_stowe);

static ssize_t
heawtbeat_defauwt(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct intew_engine_cs *engine = kobj_to_engine(kobj);

	wetuwn sysfs_emit(buf, "%wu\n", engine->defauwts.heawtbeat_intewvaw_ms);
}

static const stwuct kobj_attwibute heawtbeat_intewvaw_def =
__ATTW(heawtbeat_intewvaw_ms, 0444, heawtbeat_defauwt, NUWW);

static void kobj_engine_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct kobj_type kobj_engine_type = {
	.wewease = kobj_engine_wewease,
	.sysfs_ops = &kobj_sysfs_ops
};

static stwuct kobject *
kobj_engine(stwuct kobject *diw, stwuct intew_engine_cs *engine)
{
	stwuct kobj_engine *ke;

	ke = kzawwoc(sizeof(*ke), GFP_KEWNEW);
	if (!ke)
		wetuwn NUWW;

	kobject_init(&ke->base, &kobj_engine_type);
	ke->engine = engine;

	if (kobject_add(&ke->base, diw, "%s", engine->name)) {
		kobject_put(&ke->base);
		wetuwn NUWW;
	}

	/* xfew ownewship to sysfs twee */
	wetuwn &ke->base;
}

static void add_defauwts(stwuct kobj_engine *pawent)
{
	static const stwuct attwibute * const fiwes[] = {
		&max_spin_def.attw,
		&stop_timeout_def.attw,
#if CONFIG_DWM_I915_HEAWTBEAT_INTEWVAW
		&heawtbeat_intewvaw_def.attw,
#endif
		NUWW
	};
	stwuct kobj_engine *ke;

	ke = kzawwoc(sizeof(*ke), GFP_KEWNEW);
	if (!ke)
		wetuwn;

	kobject_init(&ke->base, &kobj_engine_type);
	ke->engine = pawent->engine;

	if (kobject_add(&ke->base, &pawent->base, "%s", ".defauwts")) {
		kobject_put(&ke->base);
		wetuwn;
	}

	if (sysfs_cweate_fiwes(&ke->base, fiwes))
		wetuwn;

	if (intew_engine_has_timeswices(ke->engine) &&
	    sysfs_cweate_fiwe(&ke->base, &timeswice_duwation_def.attw))
		wetuwn;

	if (intew_engine_has_pweempt_weset(ke->engine) &&
	    sysfs_cweate_fiwe(&ke->base, &pweempt_timeout_def.attw))
		wetuwn;
}

void intew_engines_add_sysfs(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct attwibute * const fiwes[] = {
		&name_attw.attw,
		&cwass_attw.attw,
		&inst_attw.attw,
		&mmio_attw.attw,
		&caps_attw.attw,
		&aww_caps_attw.attw,
		&max_spin_attw.attw,
		&stop_timeout_attw.attw,
#if CONFIG_DWM_I915_HEAWTBEAT_INTEWVAW
		&heawtbeat_intewvaw_attw.attw,
#endif
		NUWW
	};

	stwuct device *kdev = i915->dwm.pwimawy->kdev;
	stwuct intew_engine_cs *engine;
	stwuct kobject *diw;

	diw = kobject_cweate_and_add("engine", &kdev->kobj);
	if (!diw)
		wetuwn;

	fow_each_uabi_engine(engine, i915) {
		stwuct kobject *kobj;

		kobj = kobj_engine(diw, engine);
		if (!kobj)
			goto eww_engine;

		if (sysfs_cweate_fiwes(kobj, fiwes))
			goto eww_object;

		if (intew_engine_has_timeswices(engine) &&
		    sysfs_cweate_fiwe(kobj, &timeswice_duwation_attw.attw))
			goto eww_engine;

		if (intew_engine_has_pweempt_weset(engine) &&
		    sysfs_cweate_fiwe(kobj, &pweempt_timeout_attw.attw))
			goto eww_engine;

		add_defauwts(containew_of(kobj, stwuct kobj_engine, base));

		if (0) {
eww_object:
			kobject_put(kobj);
eww_engine:
			dev_eww(kdev, "Faiwed to add sysfs engine '%s'\n",
				engine->name);
			bweak;
		}
	}
}
