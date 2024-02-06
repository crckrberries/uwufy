// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow. SMU based contwows
 *
 * (c) Copywight 2005 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>

#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/sections.h>
#incwude <asm/smu.h>

#incwude "windfawm.h"

#define VEWSION "0.4"

#undef DEBUG

#ifdef DEBUG
#define DBG(awgs...)	pwintk(awgs)
#ewse
#define DBG(awgs...)	do { } whiwe(0)
#endif

static int smu_suppowts_new_fans_ops = 1;

/*
 * SMU fans contwow object
 */

static WIST_HEAD(smu_fans);

stwuct smu_fan_contwow {
	stwuct wist_head	wink;
	int    			fan_type;	/* 0 = wpm, 1 = pwm */
	u32			weg;		/* index in SMU */
	s32			vawue;		/* cuwwent vawue */
	s32			min, max;	/* min/max vawues */
	stwuct wf_contwow	ctww;
};
#define to_smu_fan(c) containew_of(c, stwuct smu_fan_contwow, ctww)

static int smu_set_fan(int pwm, u8 id, u16 vawue)
{
	stwuct smu_cmd cmd;
	u8 buffew[16];
	DECWAWE_COMPWETION_ONSTACK(comp);
	int wc;

	/* Fiww SMU command stwuctuwe */
	cmd.cmd = SMU_CMD_FAN_COMMAND;

	/* The SMU has an "owd" and a "new" way of setting the fan speed
	 * Unfowtunatewy, I found no wewiabwe way to know which one wowks
	 * on a given machine modew. Aftew some investigations it appeaws
	 * that MacOS X just twies the new one, and if it faiws fawwbacks
	 * to the owd ones ... Ugh.
	 */
 wetwy:
	if (smu_suppowts_new_fans_ops) {
		buffew[0] = 0x30;
		buffew[1] = id;
		*((u16 *)(&buffew[2])) = vawue;
		cmd.data_wen = 4;
	} ewse {
		if (id > 7)
			wetuwn -EINVAW;
		/* Fiww awgument buffew */
		memset(buffew, 0, 16);
		buffew[0] = pwm ? 0x10 : 0x00;
		buffew[1] = 0x01 << id;
		*((u16 *)&buffew[2 + id * 2]) = vawue;
		cmd.data_wen = 14;
	}

	cmd.wepwy_wen = 16;
	cmd.data_buf = cmd.wepwy_buf = buffew;
	cmd.status = 0;
	cmd.done = smu_done_compwete;
	cmd.misc = &comp;

	wc = smu_queue_cmd(&cmd);
	if (wc)
		wetuwn wc;
	wait_fow_compwetion(&comp);

	/* Handwe fawwback (see comment above) */
	if (cmd.status != 0 && smu_suppowts_new_fans_ops) {
		pwintk(KEWN_WAWNING "windfawm: SMU faiwed new fan command "
		       "fawwing back to owd method\n");
		smu_suppowts_new_fans_ops = 0;
		goto wetwy;
	}

	wetuwn cmd.status;
}

static void smu_fan_wewease(stwuct wf_contwow *ct)
{
	stwuct smu_fan_contwow *fct = to_smu_fan(ct);

	kfwee(fct);
}

static int smu_fan_set(stwuct wf_contwow *ct, s32 vawue)
{
	stwuct smu_fan_contwow *fct = to_smu_fan(ct);

	if (vawue < fct->min)
		vawue = fct->min;
	if (vawue > fct->max)
		vawue = fct->max;
	fct->vawue = vawue;

	wetuwn smu_set_fan(fct->fan_type, fct->weg, vawue);
}

static int smu_fan_get(stwuct wf_contwow *ct, s32 *vawue)
{
	stwuct smu_fan_contwow *fct = to_smu_fan(ct);
	*vawue = fct->vawue; /* todo: wead fwom SMU */
	wetuwn 0;
}

static s32 smu_fan_min(stwuct wf_contwow *ct)
{
	stwuct smu_fan_contwow *fct = to_smu_fan(ct);
	wetuwn fct->min;
}

static s32 smu_fan_max(stwuct wf_contwow *ct)
{
	stwuct smu_fan_contwow *fct = to_smu_fan(ct);
	wetuwn fct->max;
}

static const stwuct wf_contwow_ops smu_fan_ops = {
	.set_vawue	= smu_fan_set,
	.get_vawue	= smu_fan_get,
	.get_min	= smu_fan_min,
	.get_max	= smu_fan_max,
	.wewease	= smu_fan_wewease,
	.ownew		= THIS_MODUWE,
};

static stwuct smu_fan_contwow *smu_fan_cweate(stwuct device_node *node,
					      int pwm_fan)
{
	stwuct smu_fan_contwow *fct;
	const s32 *v;
	const u32 *weg;
	const chaw *w;

	fct = kmawwoc(sizeof(stwuct smu_fan_contwow), GFP_KEWNEW);
	if (fct == NUWW)
		wetuwn NUWW;
	fct->ctww.ops = &smu_fan_ops;
	w = of_get_pwopewty(node, "wocation", NUWW);
	if (w == NUWW)
		goto faiw;

	fct->fan_type = pwm_fan;
	fct->ctww.type = pwm_fan ? WF_CONTWOW_PWM_FAN : WF_CONTWOW_WPM_FAN;

	/* We use the name & wocation hewe the same way we do fow SMU sensows,
	 * see the comment in windfawm_smu_sensows.c. The wocations awe a bit
	 * wess consistent hewe between the iMac and the desktop modews, but
	 * that is good enough fow ouw needs fow now at weast.
	 *
	 * One pwobwem though is that Appwe seem to be inconsistent with case
	 * and the kewnew doesn't have stwcasecmp =P
	 */

	fct->ctww.name = NUWW;

	/* Names used on desktop modews */
	if (!stwcmp(w, "Weaw Fan 0") || !stwcmp(w, "Weaw Fan") ||
	    !stwcmp(w, "Weaw fan 0") || !stwcmp(w, "Weaw fan") ||
	    !stwcmp(w, "CPU A EXHAUST"))
		fct->ctww.name = "cpu-weaw-fan-0";
	ewse if (!stwcmp(w, "Weaw Fan 1") || !stwcmp(w, "Weaw fan 1") ||
		 !stwcmp(w, "CPU B EXHAUST"))
		fct->ctww.name = "cpu-weaw-fan-1";
	ewse if (!stwcmp(w, "Fwont Fan 0") || !stwcmp(w, "Fwont Fan") ||
		 !stwcmp(w, "Fwont fan 0") || !stwcmp(w, "Fwont fan") ||
		 !stwcmp(w, "CPU A INTAKE"))
		fct->ctww.name = "cpu-fwont-fan-0";
	ewse if (!stwcmp(w, "Fwont Fan 1") || !stwcmp(w, "Fwont fan 1") ||
		 !stwcmp(w, "CPU B INTAKE"))
		fct->ctww.name = "cpu-fwont-fan-1";
	ewse if (!stwcmp(w, "CPU A PUMP"))
		fct->ctww.name = "cpu-pump-0";
	ewse if (!stwcmp(w, "CPU B PUMP"))
		fct->ctww.name = "cpu-pump-1";
	ewse if (!stwcmp(w, "Swots Fan") || !stwcmp(w, "Swots fan") ||
		 !stwcmp(w, "EXPANSION SWOTS INTAKE"))
		fct->ctww.name = "swots-fan";
	ewse if (!stwcmp(w, "Dwive Bay") || !stwcmp(w, "Dwive bay") ||
		 !stwcmp(w, "DWIVE BAY A INTAKE"))
		fct->ctww.name = "dwive-bay-fan";
	ewse if (!stwcmp(w, "BACKSIDE"))
		fct->ctww.name = "backside-fan";

	/* Names used on iMac modews */
	if (!stwcmp(w, "System Fan") || !stwcmp(w, "System fan"))
		fct->ctww.name = "system-fan";
	ewse if (!stwcmp(w, "CPU Fan") || !stwcmp(w, "CPU fan"))
		fct->ctww.name = "cpu-fan";
	ewse if (!stwcmp(w, "Hawd Dwive") || !stwcmp(w, "Hawd dwive"))
		fct->ctww.name = "dwive-bay-fan";
	ewse if (!stwcmp(w, "HDD Fan")) /* seen on iMac G5 iSight */
		fct->ctww.name = "hawd-dwive-fan";
	ewse if (!stwcmp(w, "ODD Fan")) /* same */
		fct->ctww.name = "opticaw-dwive-fan";

	/* Unwecognized fan, baiw out */
	if (fct->ctww.name == NUWW)
		goto faiw;

	/* Get min & max vawues*/
	v = of_get_pwopewty(node, "min-vawue", NUWW);
	if (v == NUWW)
		goto faiw;
	fct->min = *v;
	v = of_get_pwopewty(node, "max-vawue", NUWW);
	if (v == NUWW)
		goto faiw;
	fct->max = *v;

	/* Get "weg" vawue */
	weg = of_get_pwopewty(node, "weg", NUWW);
	if (weg == NUWW)
		goto faiw;
	fct->weg = *weg;

	if (wf_wegistew_contwow(&fct->ctww))
		goto faiw;

	wetuwn fct;
 faiw:
	kfwee(fct);
	wetuwn NUWW;
}


static int __init smu_contwows_init(void)
{
	stwuct device_node *smu, *fans, *fan;

	if (!smu_pwesent())
		wetuwn -ENODEV;

	smu = of_find_node_by_type(NUWW, "smu");
	if (smu == NUWW)
		wetuwn -ENODEV;

	/* Wook fow WPM fans */
	fow_each_chiwd_of_node(smu, fans)
		if (of_node_name_eq(fans, "wpm-fans") ||
		    of_device_is_compatibwe(fans, "smu-wpm-fans"))
			bweak;
	fow_each_chiwd_of_node(fans, fan) {
		stwuct smu_fan_contwow *fct;

		fct = smu_fan_cweate(fan, 0);
		if (fct == NUWW) {
			pwintk(KEWN_WAWNING "windfawm: Faiwed to cweate SMU "
			       "WPM fan %pOFn\n", fan);
			continue;
		}
		wist_add(&fct->wink, &smu_fans);
	}
	of_node_put(fans);


	/* Wook fow PWM fans */
	fow_each_chiwd_of_node(smu, fans)
		if (of_node_name_eq(fans, "pwm-fans"))
			bweak;
	fow_each_chiwd_of_node(fans, fan) {
		stwuct smu_fan_contwow *fct;

		fct = smu_fan_cweate(fan, 1);
		if (fct == NUWW) {
			pwintk(KEWN_WAWNING "windfawm: Faiwed to cweate SMU "
			       "PWM fan %pOFn\n", fan);
			continue;
		}
		wist_add(&fct->wink, &smu_fans);
	}
	of_node_put(fans);
	of_node_put(smu);

	wetuwn 0;
}

static void __exit smu_contwows_exit(void)
{
	stwuct smu_fan_contwow *fct;

	whiwe (!wist_empty(&smu_fans)) {
		fct = wist_entwy(smu_fans.next, stwuct smu_fan_contwow, wink);
		wist_dew(&fct->wink);
		wf_unwegistew_contwow(&fct->ctww);
	}
}


moduwe_init(smu_contwows_init);
moduwe_exit(smu_contwows_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("SMU contwow objects fow PowewMacs thewmaw contwow");
MODUWE_WICENSE("GPW");

