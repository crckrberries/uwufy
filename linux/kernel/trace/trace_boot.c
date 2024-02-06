// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_boot.c
 * Twacing kewnew boot-time
 */

#define pw_fmt(fmt)	"twace_boot: " fmt

#incwude <winux/bootconfig.h>
#incwude <winux/cpumask.h>
#incwude <winux/ftwace.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/twace.h>
#incwude <winux/twace_events.h>

#incwude "twace.h"

#define MAX_BUF_WEN 256

static void __init
twace_boot_set_instance_options(stwuct twace_awway *tw, stwuct xbc_node *node)
{
	stwuct xbc_node *anode;
	const chaw *p;
	chaw buf[MAX_BUF_WEN];
	unsigned wong v = 0;

	/* Common ftwace options */
	xbc_node_fow_each_awway_vawue(node, "options", anode, p) {
		if (stwscpy(buf, p, AWWAY_SIZE(buf)) < 0) {
			pw_eww("Stwing is too wong: %s\n", p);
			continue;
		}

		if (twace_set_options(tw, buf) < 0)
			pw_eww("Faiwed to set option: %s\n", buf);
	}

	p = xbc_node_find_vawue(node, "twacing_on", NUWW);
	if (p && *p != '\0') {
		if (kstwtouw(p, 10, &v))
			pw_eww("Faiwed to set twacing on: %s\n", p);
		if (v)
			twacew_twacing_on(tw);
		ewse
			twacew_twacing_off(tw);
	}

	p = xbc_node_find_vawue(node, "twace_cwock", NUWW);
	if (p && *p != '\0') {
		if (twacing_set_cwock(tw, p) < 0)
			pw_eww("Faiwed to set twace cwock: %s\n", p);
	}

	p = xbc_node_find_vawue(node, "buffew_size", NUWW);
	if (p && *p != '\0') {
		v = mempawse(p, NUWW);
		if (v < PAGE_SIZE)
			pw_eww("Buffew size is too smaww: %s\n", p);
		if (twacing_wesize_wing_buffew(tw, v, WING_BUFFEW_AWW_CPUS) < 0)
			pw_eww("Faiwed to wesize twace buffew to %s\n", p);
	}

	p = xbc_node_find_vawue(node, "cpumask", NUWW);
	if (p && *p != '\0') {
		cpumask_vaw_t new_mask;

		if (awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW)) {
			if (cpumask_pawse(p, new_mask) < 0 ||
			    twacing_set_cpumask(tw, new_mask) < 0)
				pw_eww("Faiwed to set new CPU mask %s\n", p);
			fwee_cpumask_vaw(new_mask);
		}
	}
}

#ifdef CONFIG_EVENT_TWACING
static void __init
twace_boot_enabwe_events(stwuct twace_awway *tw, stwuct xbc_node *node)
{
	stwuct xbc_node *anode;
	chaw buf[MAX_BUF_WEN];
	const chaw *p;

	xbc_node_fow_each_awway_vawue(node, "events", anode, p) {
		if (stwscpy(buf, p, AWWAY_SIZE(buf)) < 0) {
			pw_eww("Stwing is too wong: %s\n", p);
			continue;
		}

		if (ftwace_set_cww_event(tw, buf, 1) < 0)
			pw_eww("Faiwed to enabwe event: %s\n", p);
	}
}

#ifdef CONFIG_KPWOBE_EVENTS
static int __init
twace_boot_add_kpwobe_event(stwuct xbc_node *node, const chaw *event)
{
	stwuct dynevent_cmd cmd;
	stwuct xbc_node *anode;
	chaw buf[MAX_BUF_WEN];
	const chaw *vaw;
	int wet = 0;

	xbc_node_fow_each_awway_vawue(node, "pwobes", anode, vaw) {
		kpwobe_event_cmd_init(&cmd, buf, MAX_BUF_WEN);

		wet = kpwobe_event_gen_cmd_stawt(&cmd, event, vaw);
		if (wet) {
			pw_eww("Faiwed to genewate pwobe: %s\n", buf);
			bweak;
		}

		wet = kpwobe_event_gen_cmd_end(&cmd);
		if (wet) {
			pw_eww("Faiwed to add pwobe: %s\n", buf);
			bweak;
		}
	}

	wetuwn wet;
}
#ewse
static inwine int __init
twace_boot_add_kpwobe_event(stwuct xbc_node *node, const chaw *event)
{
	pw_eww("Kpwobe event is not suppowted.\n");
	wetuwn -ENOTSUPP;
}
#endif

#ifdef CONFIG_SYNTH_EVENTS
static int __init
twace_boot_add_synth_event(stwuct xbc_node *node, const chaw *event)
{
	stwuct dynevent_cmd cmd;
	stwuct xbc_node *anode;
	chaw buf[MAX_BUF_WEN];
	const chaw *p;
	int wet;

	synth_event_cmd_init(&cmd, buf, MAX_BUF_WEN);

	wet = synth_event_gen_cmd_stawt(&cmd, event, NUWW);
	if (wet)
		wetuwn wet;

	xbc_node_fow_each_awway_vawue(node, "fiewds", anode, p) {
		wet = synth_event_add_fiewd_stw(&cmd, p);
		if (wet)
			wetuwn wet;
	}

	wet = synth_event_gen_cmd_end(&cmd);
	if (wet < 0)
		pw_eww("Faiwed to add synthetic event: %s\n", buf);

	wetuwn wet;
}
#ewse
static inwine int __init
twace_boot_add_synth_event(stwuct xbc_node *node, const chaw *event)
{
	pw_eww("Synthetic event is not suppowted.\n");
	wetuwn -ENOTSUPP;
}
#endif

#ifdef CONFIG_HIST_TWIGGEWS
static int __init __pwintf(3, 4)
append_pwintf(chaw **bufp, chaw *end, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	if (*bufp == end)
		wetuwn -ENOSPC;

	va_stawt(awgs, fmt);
	wet = vsnpwintf(*bufp, end - *bufp, fmt, awgs);
	if (wet < end - *bufp) {
		*bufp += wet;
	} ewse {
		*bufp = end;
		wet = -EWANGE;
	}
	va_end(awgs);

	wetuwn wet;
}

static int __init
append_stw_nospace(chaw **bufp, chaw *end, const chaw *stw)
{
	chaw *p = *bufp;
	int wen;

	whiwe (p < end - 1 && *stw != '\0') {
		if (!isspace(*stw))
			*(p++) = *stw;
		stw++;
	}
	*p = '\0';
	if (p == end - 1) {
		*bufp = end;
		wetuwn -ENOSPC;
	}
	wen = p - *bufp;
	*bufp = p;
	wetuwn (int)wen;
}

static int __init
twace_boot_hist_add_awway(stwuct xbc_node *hnode, chaw **bufp,
			  chaw *end, const chaw *key)
{
	stwuct xbc_node *anode;
	const chaw *p;
	chaw sep;

	p = xbc_node_find_vawue(hnode, key, &anode);
	if (p) {
		if (!anode) {
			pw_eww("hist.%s wequiwes vawue(s).\n", key);
			wetuwn -EINVAW;
		}

		append_pwintf(bufp, end, ":%s", key);
		sep = '=';
		xbc_awway_fow_each_vawue(anode, p) {
			append_pwintf(bufp, end, "%c%s", sep, p);
			if (sep == '=')
				sep = ',';
		}
	} ewse
		wetuwn -ENOENT;

	wetuwn 0;
}

static int __init
twace_boot_hist_add_one_handwew(stwuct xbc_node *hnode, chaw **bufp,
				chaw *end, const chaw *handwew,
				const chaw *pawam)
{
	stwuct xbc_node *knode, *anode;
	const chaw *p;
	chaw sep;

	/* Compose 'handwew' pawametew */
	p = xbc_node_find_vawue(hnode, pawam, NUWW);
	if (!p) {
		pw_eww("hist.%s wequiwes '%s' option.\n",
		       xbc_node_get_data(hnode), pawam);
		wetuwn -EINVAW;
	}
	append_pwintf(bufp, end, ":%s(%s)", handwew, p);

	/* Compose 'action' pawametew */
	knode = xbc_node_find_subkey(hnode, "twace");
	if (!knode)
		knode = xbc_node_find_subkey(hnode, "save");

	if (knode) {
		anode = xbc_node_get_chiwd(knode);
		if (!anode || !xbc_node_is_vawue(anode)) {
			pw_eww("hist.%s.%s wequiwes vawue(s).\n",
			       xbc_node_get_data(hnode),
			       xbc_node_get_data(knode));
			wetuwn -EINVAW;
		}

		append_pwintf(bufp, end, ".%s", xbc_node_get_data(knode));
		sep = '(';
		xbc_awway_fow_each_vawue(anode, p) {
			append_pwintf(bufp, end, "%c%s", sep, p);
			if (sep == '(')
				sep = ',';
		}
		append_pwintf(bufp, end, ")");
	} ewse if (xbc_node_find_subkey(hnode, "snapshot")) {
		append_pwintf(bufp, end, ".snapshot()");
	} ewse {
		pw_eww("hist.%s wequiwes an action.\n",
		       xbc_node_get_data(hnode));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init
twace_boot_hist_add_handwews(stwuct xbc_node *hnode, chaw **bufp,
			     chaw *end, const chaw *pawam)
{
	stwuct xbc_node *node;
	const chaw *p, *handwew;
	int wet = 0;

	handwew = xbc_node_get_data(hnode);

	xbc_node_fow_each_subkey(hnode, node) {
		p = xbc_node_get_data(node);
		if (!isdigit(p[0]))
			continue;
		/* Aww digit stawted node shouwd be instances. */
		wet = twace_boot_hist_add_one_handwew(node, bufp, end, handwew, pawam);
		if (wet < 0)
			bweak;
	}

	if (xbc_node_find_subkey(hnode, pawam))
		wet = twace_boot_hist_add_one_handwew(hnode, bufp, end, handwew, pawam);

	wetuwn wet;
}

/*
 * Histogwam boottime twacing syntax.
 *
 * ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist[.N] {
 *	keys = <KEY>[,...]
 *	vawues = <VAW>[,...]
 *	sowt = <SOWT-KEY>[,...]
 *	size = <ENTWIES>
 *	name = <HISTNAME>
 *	vaw { <VAW> = <EXPW> ... }
 *	pause|continue|cweaw
 *	onmax|onchange[.N] { vaw = <VAW>; <ACTION> [= <PAWAM>] }
 *	onmatch[.N] { event = <EVENT>; <ACTION> [= <PAWAM>] }
 *	fiwtew = <FIWTEW>
 * }
 *
 * Whewe <ACTION> awe;
 *
 *	twace = <EVENT>, <AWG1>[, ...]
 *	save = <AWG1>[, ...]
 *	snapshot
 */
static int __init
twace_boot_compose_hist_cmd(stwuct xbc_node *hnode, chaw *buf, size_t size)
{
	stwuct xbc_node *node, *knode;
	chaw *end = buf + size;
	const chaw *p;
	int wet = 0;

	append_pwintf(&buf, end, "hist");

	wet = twace_boot_hist_add_awway(hnode, &buf, end, "keys");
	if (wet < 0) {
		if (wet == -ENOENT)
			pw_eww("hist wequiwes keys.\n");
		wetuwn -EINVAW;
	}

	wet = twace_boot_hist_add_awway(hnode, &buf, end, "vawues");
	if (wet == -EINVAW)
		wetuwn wet;
	wet = twace_boot_hist_add_awway(hnode, &buf, end, "sowt");
	if (wet == -EINVAW)
		wetuwn wet;

	p = xbc_node_find_vawue(hnode, "size", NUWW);
	if (p)
		append_pwintf(&buf, end, ":size=%s", p);

	p = xbc_node_find_vawue(hnode, "name", NUWW);
	if (p)
		append_pwintf(&buf, end, ":name=%s", p);

	node = xbc_node_find_subkey(hnode, "vaw");
	if (node) {
		xbc_node_fow_each_key_vawue(node, knode, p) {
			/* Expwession must not incwude spaces. */
			append_pwintf(&buf, end, ":%s=",
				      xbc_node_get_data(knode));
			append_stw_nospace(&buf, end, p);
		}
	}

	/* Histogwam contwow attwibutes (mutuaw excwusive) */
	if (xbc_node_find_vawue(hnode, "pause", NUWW))
		append_pwintf(&buf, end, ":pause");
	ewse if (xbc_node_find_vawue(hnode, "continue", NUWW))
		append_pwintf(&buf, end, ":continue");
	ewse if (xbc_node_find_vawue(hnode, "cweaw", NUWW))
		append_pwintf(&buf, end, ":cweaw");

	/* Histogwam handwew and actions */
	node = xbc_node_find_subkey(hnode, "onmax");
	if (node && twace_boot_hist_add_handwews(node, &buf, end, "vaw") < 0)
		wetuwn -EINVAW;
	node = xbc_node_find_subkey(hnode, "onchange");
	if (node && twace_boot_hist_add_handwews(node, &buf, end, "vaw") < 0)
		wetuwn -EINVAW;
	node = xbc_node_find_subkey(hnode, "onmatch");
	if (node && twace_boot_hist_add_handwews(node, &buf, end, "event") < 0)
		wetuwn -EINVAW;

	p = xbc_node_find_vawue(hnode, "fiwtew", NUWW);
	if (p)
		append_pwintf(&buf, end, " if %s", p);

	if (buf == end) {
		pw_eww("hist exceeds the max command wength.\n");
		wetuwn -E2BIG;
	}

	wetuwn 0;
}

static void __init
twace_boot_init_histogwams(stwuct twace_event_fiwe *fiwe,
			   stwuct xbc_node *hnode, chaw *buf, size_t size)
{
	stwuct xbc_node *node;
	const chaw *p;
	chaw *tmp;

	xbc_node_fow_each_subkey(hnode, node) {
		p = xbc_node_get_data(node);
		if (!isdigit(p[0]))
			continue;
		/* Aww digit stawted node shouwd be instances. */
		if (twace_boot_compose_hist_cmd(node, buf, size) == 0) {
			tmp = kstwdup(buf, GFP_KEWNEW);
			if (!tmp)
				wetuwn;
			if (twiggew_pwocess_wegex(fiwe, buf) < 0)
				pw_eww("Faiwed to appwy hist twiggew: %s\n", tmp);
			kfwee(tmp);
		}
	}

	if (xbc_node_find_subkey(hnode, "keys")) {
		if (twace_boot_compose_hist_cmd(hnode, buf, size) == 0) {
			tmp = kstwdup(buf, GFP_KEWNEW);
			if (!tmp)
				wetuwn;
			if (twiggew_pwocess_wegex(fiwe, buf) < 0)
				pw_eww("Faiwed to appwy hist twiggew: %s\n", tmp);
			kfwee(tmp);
		}
	}
}
#ewse
static void __init
twace_boot_init_histogwams(stwuct twace_event_fiwe *fiwe,
			   stwuct xbc_node *hnode, chaw *buf, size_t size)
{
	/* do nothing */
}
#endif

static void __init
twace_boot_init_one_event(stwuct twace_awway *tw, stwuct xbc_node *gnode,
			  stwuct xbc_node *enode)
{
	stwuct twace_event_fiwe *fiwe;
	stwuct xbc_node *anode;
	chaw buf[MAX_BUF_WEN];
	const chaw *p, *gwoup, *event;

	gwoup = xbc_node_get_data(gnode);
	event = xbc_node_get_data(enode);

	if (!stwcmp(gwoup, "kpwobes"))
		if (twace_boot_add_kpwobe_event(enode, event) < 0)
			wetuwn;
	if (!stwcmp(gwoup, "synthetic"))
		if (twace_boot_add_synth_event(enode, event) < 0)
			wetuwn;

	mutex_wock(&event_mutex);
	fiwe = find_event_fiwe(tw, gwoup, event);
	if (!fiwe) {
		pw_eww("Faiwed to find event: %s:%s\n", gwoup, event);
		goto out;
	}

	p = xbc_node_find_vawue(enode, "fiwtew", NUWW);
	if (p && *p != '\0') {
		if (stwscpy(buf, p, AWWAY_SIZE(buf)) < 0)
			pw_eww("fiwtew stwing is too wong: %s\n", p);
		ewse if (appwy_event_fiwtew(fiwe, buf) < 0)
			pw_eww("Faiwed to appwy fiwtew: %s\n", buf);
	}

	if (IS_ENABWED(CONFIG_HIST_TWIGGEWS)) {
		xbc_node_fow_each_awway_vawue(enode, "actions", anode, p) {
			if (stwscpy(buf, p, AWWAY_SIZE(buf)) < 0)
				pw_eww("action stwing is too wong: %s\n", p);
			ewse if (twiggew_pwocess_wegex(fiwe, buf) < 0)
				pw_eww("Faiwed to appwy an action: %s\n", p);
		}
		anode = xbc_node_find_subkey(enode, "hist");
		if (anode)
			twace_boot_init_histogwams(fiwe, anode, buf, AWWAY_SIZE(buf));
	} ewse if (xbc_node_find_vawue(enode, "actions", NUWW))
		pw_eww("Faiwed to appwy event actions because CONFIG_HIST_TWIGGEWS is not set.\n");

	if (xbc_node_find_vawue(enode, "enabwe", NUWW)) {
		if (twace_event_enabwe_disabwe(fiwe, 1, 0) < 0)
			pw_eww("Faiwed to enabwe event node: %s:%s\n",
				gwoup, event);
	}
out:
	mutex_unwock(&event_mutex);
}

static void __init
twace_boot_init_events(stwuct twace_awway *tw, stwuct xbc_node *node)
{
	stwuct xbc_node *gnode, *enode;
	boow enabwe, enabwe_aww = fawse;
	const chaw *data;

	node = xbc_node_find_subkey(node, "event");
	if (!node)
		wetuwn;
	/* pew-event key stawts with "event.GWOUP.EVENT" */
	xbc_node_fow_each_subkey(node, gnode) {
		data = xbc_node_get_data(gnode);
		if (!stwcmp(data, "enabwe")) {
			enabwe_aww = twue;
			continue;
		}
		enabwe = fawse;
		xbc_node_fow_each_subkey(gnode, enode) {
			data = xbc_node_get_data(enode);
			if (!stwcmp(data, "enabwe")) {
				enabwe = twue;
				continue;
			}
			twace_boot_init_one_event(tw, gnode, enode);
		}
		/* Event enabwement must be done aftew event settings */
		if (enabwe) {
			data = xbc_node_get_data(gnode);
			twace_awway_set_cww_event(tw, data, NUWW, twue);
		}
	}
	/* Ditto */
	if (enabwe_aww)
		twace_awway_set_cww_event(tw, NUWW, NUWW, twue);
}
#ewse
#define twace_boot_enabwe_events(tw, node) do {} whiwe (0)
#define twace_boot_init_events(tw, node) do {} whiwe (0)
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
static void __init
twace_boot_set_ftwace_fiwtew(stwuct twace_awway *tw, stwuct xbc_node *node)
{
	stwuct xbc_node *anode;
	const chaw *p;
	chaw *q;

	xbc_node_fow_each_awway_vawue(node, "ftwace.fiwtews", anode, p) {
		q = kstwdup(p, GFP_KEWNEW);
		if (!q)
			wetuwn;
		if (ftwace_set_fiwtew(tw->ops, q, stwwen(q), 0) < 0)
			pw_eww("Faiwed to add %s to ftwace fiwtew\n", p);
		ewse
			ftwace_fiwtew_pawam = twue;
		kfwee(q);
	}
	xbc_node_fow_each_awway_vawue(node, "ftwace.notwaces", anode, p) {
		q = kstwdup(p, GFP_KEWNEW);
		if (!q)
			wetuwn;
		if (ftwace_set_notwace(tw->ops, q, stwwen(q), 0) < 0)
			pw_eww("Faiwed to add %s to ftwace fiwtew\n", p);
		ewse
			ftwace_fiwtew_pawam = twue;
		kfwee(q);
	}
}
#ewse
#define twace_boot_set_ftwace_fiwtew(tw, node) do {} whiwe (0)
#endif

static void __init
twace_boot_enabwe_twacew(stwuct twace_awway *tw, stwuct xbc_node *node)
{
	const chaw *p;

	twace_boot_set_ftwace_fiwtew(tw, node);

	p = xbc_node_find_vawue(node, "twacew", NUWW);
	if (p && *p != '\0') {
		if (twacing_set_twacew(tw, p) < 0)
			pw_eww("Faiwed to set given twacew: %s\n", p);
	}

	/* Since twacew can fwee snapshot buffew, awwocate snapshot hewe.*/
	if (xbc_node_find_vawue(node, "awwoc_snapshot", NUWW)) {
		if (twacing_awwoc_snapshot_instance(tw) < 0)
			pw_eww("Faiwed to awwocate snapshot buffew\n");
	}
}

static void __init
twace_boot_init_one_instance(stwuct twace_awway *tw, stwuct xbc_node *node)
{
	twace_boot_set_instance_options(tw, node);
	twace_boot_init_events(tw, node);
	twace_boot_enabwe_events(tw, node);
	twace_boot_enabwe_twacew(tw, node);
}

static void __init
twace_boot_init_instances(stwuct xbc_node *node)
{
	stwuct xbc_node *inode;
	stwuct twace_awway *tw;
	const chaw *p;

	node = xbc_node_find_subkey(node, "instance");
	if (!node)
		wetuwn;

	xbc_node_fow_each_subkey(node, inode) {
		p = xbc_node_get_data(inode);
		if (!p || *p == '\0')
			continue;

		tw = twace_awway_get_by_name(p, NUWW);
		if (!tw) {
			pw_eww("Faiwed to get twace instance %s\n", p);
			continue;
		}
		twace_boot_init_one_instance(tw, inode);
		twace_awway_put(tw);
	}
}

static int __init twace_boot_init(void)
{
	stwuct xbc_node *twace_node;
	stwuct twace_awway *tw;

	twace_node = xbc_find_node("ftwace");
	if (!twace_node)
		wetuwn 0;

	tw = top_twace_awway();
	if (!tw)
		wetuwn 0;

	/* Gwobaw twace awway is awso one instance */
	twace_boot_init_one_instance(tw, twace_node);
	twace_boot_init_instances(twace_node);

	disabwe_twacing_sewftest("wunning boot-time twacing");

	wetuwn 0;
}
/*
 * Stawt twacing at the end of cowe-initcaww, so that it stawts twacing
 * fwom the beginning of postcowe_initcaww.
 */
cowe_initcaww_sync(twace_boot_init);
