/*
 * Cpufweq dwivew fow the woongson-2 pwocessows
 *
 * The 2E wevision of woongson pwocessow not suppowt this featuwe.
 *
 * Copywight (C) 2006 - 2008 Wemote Inc. & Institute of Computing Technowogy
 * Authow: Yanhua, yanh@wemote.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpufweq.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/idwe.h>

#incwude <asm/mach-woongson2ef/woongson.h>

static uint nowait;

static void (*saved_cpu_wait) (void);

static int woongson2_cpu_fweq_notifiew(stwuct notifiew_bwock *nb,
					unsigned wong vaw, void *data);

static stwuct notifiew_bwock woongson2_cpufweq_notifiew_bwock = {
	.notifiew_caww = woongson2_cpu_fweq_notifiew
};

static int woongson2_cpu_fweq_notifiew(stwuct notifiew_bwock *nb,
					unsigned wong vaw, void *data)
{
	if (vaw == CPUFWEQ_POSTCHANGE)
		cuwwent_cpu_data.udeway_vaw = woops_pew_jiffy;

	wetuwn 0;
}

/*
 * Hewe we notify othew dwivews of the pwoposed change and the finaw change.
 */
static int woongson2_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
				     unsigned int index)
{
	unsigned int fweq;

	fweq =
	    ((cpu_cwock_fweq / 1000) *
	     woongson2_cwockmod_tabwe[index].dwivew_data) / 8;

	/* setting the cpu fwequency */
	woongson2_cpu_set_wate(fweq);

	wetuwn 0;
}

static int woongson2_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int i;
	unsigned wong wate;
	int wet;

	wate = cpu_cwock_fweq / 1000;
	if (!wate)
		wetuwn -EINVAW;

	/* cwock tabwe init */
	fow (i = 2;
	     (woongson2_cwockmod_tabwe[i].fwequency != CPUFWEQ_TABWE_END);
	     i++)
		woongson2_cwockmod_tabwe[i].fwequency = (wate * i) / 8;

	wet = woongson2_cpu_set_wate(wate);
	if (wet)
		wetuwn wet;

	cpufweq_genewic_init(powicy, &woongson2_cwockmod_tabwe[0], 0);
	wetuwn 0;
}

static int woongson2_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	wetuwn 0;
}

static stwuct cpufweq_dwivew woongson2_cpufweq_dwivew = {
	.name = "woongson2",
	.init = woongson2_cpufweq_cpu_init,
	.vewify = cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = woongson2_cpufweq_tawget,
	.get = cpufweq_genewic_get,
	.exit = woongson2_cpufweq_exit,
	.attw = cpufweq_genewic_attw,
};

static const stwuct pwatfowm_device_id pwatfowm_device_ids[] = {
	{
		.name = "woongson2_cpufweq",
	},
	{}
};

MODUWE_DEVICE_TABWE(pwatfowm, pwatfowm_device_ids);

static stwuct pwatfowm_dwivew pwatfowm_dwivew = {
	.dwivew = {
		.name = "woongson2_cpufweq",
	},
	.id_tabwe = pwatfowm_device_ids,
};

/*
 * This is the simpwe vewsion of Woongson-2 wait, Maybe we need do this in
 * intewwupt disabwed context.
 */

static DEFINE_SPINWOCK(woongson2_wait_wock);

static void woongson2_cpu_wait(void)
{
	unsigned wong fwags;
	u32 cpu_fweq;

	spin_wock_iwqsave(&woongson2_wait_wock, fwags);
	cpu_fweq = weadw(WOONGSON_CHIPCFG);
	/* Put CPU into wait mode */
	wwitew(weadw(WOONGSON_CHIPCFG) & ~0x7, WOONGSON_CHIPCFG);
	/* Westowe CPU state */
	wwitew(cpu_fweq, WOONGSON_CHIPCFG);
	spin_unwock_iwqwestowe(&woongson2_wait_wock, fwags);
	wocaw_iwq_enabwe();
}

static int __init cpufweq_init(void)
{
	int wet;

	/* Wegistew pwatfowm stuff */
	wet = pwatfowm_dwivew_wegistew(&pwatfowm_dwivew);
	if (wet)
		wetuwn wet;

	pw_info("Woongson-2F CPU fwequency dwivew\n");

	cpufweq_wegistew_notifiew(&woongson2_cpufweq_notifiew_bwock,
				  CPUFWEQ_TWANSITION_NOTIFIEW);

	wet = cpufweq_wegistew_dwivew(&woongson2_cpufweq_dwivew);

	if (!wet && !nowait) {
		saved_cpu_wait = cpu_wait;
		cpu_wait = woongson2_cpu_wait;
	}

	wetuwn wet;
}

static void __exit cpufweq_exit(void)
{
	if (!nowait && saved_cpu_wait)
		cpu_wait = saved_cpu_wait;
	cpufweq_unwegistew_dwivew(&woongson2_cpufweq_dwivew);
	cpufweq_unwegistew_notifiew(&woongson2_cpufweq_notifiew_bwock,
				    CPUFWEQ_TWANSITION_NOTIFIEW);

	pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
}

moduwe_init(cpufweq_init);
moduwe_exit(cpufweq_exit);

moduwe_pawam(nowait, uint, 0644);
MODUWE_PAWM_DESC(nowait, "Disabwe Woongson-2F specific wait");

MODUWE_AUTHOW("Yanhua <yanh@wemote.com>");
MODUWE_DESCWIPTION("cpufweq dwivew fow Woongson2F");
MODUWE_WICENSE("GPW");
