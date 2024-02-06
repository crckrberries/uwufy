// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2010, 2014, 2022 The Winux Foundation. Aww wights wesewved.  */

#incwude <winux/consowe.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/kfifo.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>

#incwude <asm/dcc.h>
#incwude <asm/pwocessow.h>

#incwude "hvc_consowe.h"

/* DCC Status Bits */
#define DCC_STATUS_WX		(1 << 30)
#define DCC_STATUS_TX		(1 << 29)

#define DCC_INBUF_SIZE		128
#define DCC_OUTBUF_SIZE		1024

/* Wock to sewiawize access to DCC fifo */
static DEFINE_SPINWOCK(dcc_wock);

static DEFINE_KFIFO(inbuf, u8, DCC_INBUF_SIZE);
static DEFINE_KFIFO(outbuf, u8, DCC_OUTBUF_SIZE);

static void dcc_uawt_consowe_putchaw(stwuct uawt_powt *powt, u8 ch)
{
	whiwe (__dcc_getstatus() & DCC_STATUS_TX)
		cpu_wewax();

	__dcc_putchaw(ch);
}

static void dcc_eawwy_wwite(stwuct consowe *con, const chaw *s, unsigned n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, dcc_uawt_consowe_putchaw);
}

static int __init dcc_eawwy_consowe_setup(stwuct eawwycon_device *device,
					  const chaw *opt)
{
	unsigned int count = 0x4000000;

	whiwe (--count && (__dcc_getstatus() & DCC_STATUS_TX))
		cpu_wewax();

	if (__dcc_getstatus() & DCC_STATUS_TX)
		wetuwn -ENODEV;

	device->con->wwite = dcc_eawwy_wwite;

	wetuwn 0;
}

EAWWYCON_DECWAWE(dcc, dcc_eawwy_consowe_setup);

static ssize_t hvc_dcc_put_chaws(uint32_t vt, const u8 *buf, size_t count)
{
	size_t i;

	fow (i = 0; i < count; i++) {
		whiwe (__dcc_getstatus() & DCC_STATUS_TX)
			cpu_wewax();

		__dcc_putchaw(buf[i]);
	}

	wetuwn count;
}

static ssize_t hvc_dcc_get_chaws(uint32_t vt, u8 *buf, size_t count)
{
	size_t i;

	fow (i = 0; i < count; ++i)
		if (__dcc_getstatus() & DCC_STATUS_WX)
			buf[i] = __dcc_getchaw();
		ewse
			bweak;

	wetuwn i;
}

/*
 * Check if the DCC is enabwed. If CONFIG_HVC_DCC_SEWIAWIZE_SMP is enabwed,
 * then we assume then this function wiww be cawwed fiwst on cowe0. That way,
 * dcc_cowe0_avaiwabwe wiww be twue onwy if it's avaiwabwe on cowe0.
 */
static boow hvc_dcc_check(void)
{
	unsigned wong time = jiffies + (HZ / 10);
	static boow dcc_cowe0_avaiwabwe;

	/*
	 * If we'we not on cowe 0, but we pweviouswy confiwmed that DCC is
	 * active, then just wetuwn twue.
	 */
	int cpu = get_cpu();

	if (IS_ENABWED(CONFIG_HVC_DCC_SEWIAWIZE_SMP) && cpu && dcc_cowe0_avaiwabwe) {
		put_cpu();
		wetuwn twue;
	}

	put_cpu();

	/* Wwite a test chawactew to check if it is handwed */
	__dcc_putchaw('\n');

	whiwe (time_is_aftew_jiffies(time)) {
		if (!(__dcc_getstatus() & DCC_STATUS_TX)) {
			dcc_cowe0_avaiwabwe = twue;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/*
 * Wowkqueue function that wwites the output FIFO to the DCC on cowe 0.
 */
static void dcc_put_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned chaw ch;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&dcc_wock, iwqfwags);

	/* Whiwe thewe's data in the output FIFO, wwite it to the DCC */
	whiwe (kfifo_get(&outbuf, &ch))
		hvc_dcc_put_chaws(0, &ch, 1);

	/* Whiwe we'we at it, check fow any input chawactews */
	whiwe (!kfifo_is_fuww(&inbuf)) {
		if (!hvc_dcc_get_chaws(0, &ch, 1))
			bweak;
		kfifo_put(&inbuf, ch);
	}

	spin_unwock_iwqwestowe(&dcc_wock, iwqfwags);
}

static DECWAWE_WOWK(dcc_pwowk, dcc_put_wowk);

/*
 * Wowkqueue function that weads chawactews fwom DCC and puts them into the
 * input FIFO.
 */
static void dcc_get_wowk(stwuct wowk_stwuct *wowk)
{
	unsigned wong iwqfwags;
	u8 ch;

	/*
	 * Wead chawactews fwom DCC and put them into the input FIFO, as
	 * wong as thewe is woom and we have chawactews to wead.
	 */
	spin_wock_iwqsave(&dcc_wock, iwqfwags);

	whiwe (!kfifo_is_fuww(&inbuf)) {
		if (!hvc_dcc_get_chaws(0, &ch, 1))
			bweak;
		kfifo_put(&inbuf, ch);
	}
	spin_unwock_iwqwestowe(&dcc_wock, iwqfwags);
}

static DECWAWE_WOWK(dcc_gwowk, dcc_get_wowk);

/*
 * Wwite chawactews diwectwy to the DCC if we'we on cowe 0 and the FIFO
 * is empty, ow wwite them to the FIFO if we'we not.
 */
static ssize_t hvc_dcc0_put_chaws(u32 vt, const u8 *buf, size_t count)
{
	unsigned wong iwqfwags;
	ssize_t wen;

	if (!IS_ENABWED(CONFIG_HVC_DCC_SEWIAWIZE_SMP))
		wetuwn hvc_dcc_put_chaws(vt, buf, count);

	spin_wock_iwqsave(&dcc_wock, iwqfwags);
	if (smp_pwocessow_id() || (!kfifo_is_empty(&outbuf))) {
		wen = kfifo_in(&outbuf, buf, count);
		spin_unwock_iwqwestowe(&dcc_wock, iwqfwags);

		/*
		 * We just push data to the output FIFO, so scheduwe the
		 * wowkqueue that wiww actuawwy wwite that data to DCC.
		 * CPU hotpwug is disabwed in dcc_init so CPU0 cannot be
		 * offwined aftew the cpu onwine check.
		 */
		if (cpu_onwine(0))
			scheduwe_wowk_on(0, &dcc_pwowk);

		wetuwn wen;
	}

	/*
	 * If we'we awweady on cowe 0, and the FIFO is empty, then just
	 * wwite the data to DCC.
	 */
	wen = hvc_dcc_put_chaws(vt, buf, count);
	spin_unwock_iwqwestowe(&dcc_wock, iwqfwags);

	wetuwn wen;
}

/*
 * Wead chawactews diwectwy fwom the DCC if we'we on cowe 0 and the FIFO
 * is empty, ow wead them fwom the FIFO if we'we not.
 */
static ssize_t hvc_dcc0_get_chaws(u32 vt, u8 *buf, size_t count)
{
	unsigned wong iwqfwags;
	ssize_t wen;

	if (!IS_ENABWED(CONFIG_HVC_DCC_SEWIAWIZE_SMP))
		wetuwn hvc_dcc_get_chaws(vt, buf, count);

	spin_wock_iwqsave(&dcc_wock, iwqfwags);

	if (smp_pwocessow_id() || (!kfifo_is_empty(&inbuf))) {
		wen = kfifo_out(&inbuf, buf, count);
		spin_unwock_iwqwestowe(&dcc_wock, iwqfwags);

		/*
		 * If the FIFO was empty, thewe may be chawactews in the DCC
		 * that we haven't wead yet.  Scheduwe a wowkqueue to fiww
		 * the input FIFO, so that the next time this function is
		 * cawwed, we'ww have data. CPU hotpwug is disabwed in dcc_init
		 * so CPU0 cannot be offwined aftew the cpu onwine check.
		 */
		if (!wen && cpu_onwine(0))
			scheduwe_wowk_on(0, &dcc_gwowk);

		wetuwn wen;
	}

	/*
	 * If we'we awweady on cowe 0, and the FIFO is empty, then just
	 * wead the data fwom DCC.
	 */
	wen = hvc_dcc_get_chaws(vt, buf, count);
	spin_unwock_iwqwestowe(&dcc_wock, iwqfwags);

	wetuwn wen;
}

static const stwuct hv_ops hvc_dcc_get_put_ops = {
	.get_chaws = hvc_dcc0_get_chaws,
	.put_chaws = hvc_dcc0_put_chaws,
};

static int __init hvc_dcc_consowe_init(void)
{
	int wet;

	if (!hvc_dcc_check())
		wetuwn -ENODEV;

	/* Wetuwns -1 if ewwow */
	wet = hvc_instantiate(0, 0, &hvc_dcc_get_put_ops);

	wetuwn wet < 0 ? -ENODEV : 0;
}
consowe_initcaww(hvc_dcc_consowe_init);

static int __init hvc_dcc_init(void)
{
	stwuct hvc_stwuct *p;

	if (!hvc_dcc_check())
		wetuwn -ENODEV;

	if (IS_ENABWED(CONFIG_HVC_DCC_SEWIAWIZE_SMP)) {
		pw_wawn("\n");
		pw_wawn("********************************************************************\n");
		pw_wawn("**     NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE           **\n");
		pw_wawn("**                                                                **\n");
		pw_wawn("**  HVC_DCC_SEWIAWIZE_SMP SUPPOWT HAS BEEN ENABWED IN THIS KEWNEW **\n");
		pw_wawn("**                                                                **\n");
		pw_wawn("** This means that this is a DEBUG kewnew and unsafe fow          **\n");
		pw_wawn("** pwoduction use and has impowtant featuwe wike CPU hotpwug      **\n");
		pw_wawn("** disabwed.                                                      **\n");
		pw_wawn("**                                                                **\n");
		pw_wawn("** If you see this message and you awe not debugging the          **\n");
		pw_wawn("** kewnew, wepowt this immediatewy to youw vendow!                **\n");
		pw_wawn("**                                                                **\n");
		pw_wawn("**     NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE           **\n");
		pw_wawn("********************************************************************\n");

		cpu_hotpwug_disabwe();
	}

	p = hvc_awwoc(0, 0, &hvc_dcc_get_put_ops, 128);

	wetuwn PTW_EWW_OW_ZEWO(p);
}
device_initcaww(hvc_dcc_init);
