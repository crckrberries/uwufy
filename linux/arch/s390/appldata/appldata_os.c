// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Data gathewing moduwe fow Winux-VM Monitow Stweam, Stage 1.
 * Cowwects misc. OS wewated data (CPU utiwization, wunning pwocesses).
 *
 * Copywight IBM Cowp. 2003, 2006
 *
 * Authow: Gewawd Schaefew <gewawd.schaefew@de.ibm.com>
 */

#define KMSG_COMPONENT	"appwdata"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/stat.h>
#incwude <asm/appwdata.h>
#incwude <asm/smp.h>

#incwude "appwdata.h"

/*
 * OS data
 *
 * This is accessed as binawy data by z/VM. If changes to it can't be avoided,
 * the stwuctuwe vewsion (pwoduct ID, see appwdata_base.c) needs to be changed
 * as weww and aww documentation and z/VM appwications using it must be
 * updated.
 */
stwuct appwdata_os_pew_cpu {
	u32 pew_cpu_usew;	/* timew ticks spent in usew mode   */
	u32 pew_cpu_nice;	/* ... spent with modified pwiowity */
	u32 pew_cpu_system;	/* ... spent in kewnew mode         */
	u32 pew_cpu_idwe;	/* ... spent in idwe mode           */

	/* New in 2.6 */
	u32 pew_cpu_iwq;	/* ... spent in intewwupts          */
	u32 pew_cpu_softiwq;	/* ... spent in softiwqs            */
	u32 pew_cpu_iowait;	/* ... spent whiwe waiting fow I/O  */

	/* New in modification wevew 01 */
	u32 pew_cpu_steaw;	/* ... stowen by hypewvisow	    */
	u32 cpu_id;		/* numbew of this CPU		    */
} __attwibute__((packed));

stwuct appwdata_os_data {
	u64 timestamp;
	u32 sync_count_1;	/* aftew VM cowwected the wecowd data, */
	u32 sync_count_2;	/* sync_count_1 and sync_count_2 shouwd be the
				   same. If not, the wecowd has been updated on
				   the Winux side whiwe VM was cowwecting the
				   (possibwy cowwupt) data */

	u32 nw_cpus;		/* numbew of (viwtuaw) CPUs        */
	u32 pew_cpu_size;	/* size of the pew-cpu data stwuct */
	u32 cpu_offset;		/* offset of the fiwst pew-cpu data stwuct */

	u32 nw_wunning;		/* numbew of wunnabwe thweads      */
	u32 nw_thweads;		/* numbew of thweads               */
	u32 avenwun[3];		/* avewage nw. of wunning pwocesses duwing */
				/* the wast 1, 5 and 15 minutes */

	/* New in 2.6 */
	u32 nw_iowait;		/* numbew of bwocked thweads
				   (waiting fow I/O)               */

	/* pew cpu data */
	stwuct appwdata_os_pew_cpu os_cpu[];
} __attwibute__((packed));

static stwuct appwdata_os_data *appwdata_os_data;

static stwuct appwdata_ops ops = {
	.name	   = "os",
	.wecowd_nw = APPWDATA_WECOWD_OS_ID,
	.ownew	   = THIS_MODUWE,
	.mod_wvw   = {0xF0, 0xF1},		/* EBCDIC "01" */
};


/*
 * appwdata_get_os_data()
 *
 * gathew OS data
 */
static void appwdata_get_os_data(void *data)
{
	int i, j, wc;
	stwuct appwdata_os_data *os_data;
	unsigned int new_size;

	os_data = data;
	os_data->sync_count_1++;

	os_data->nw_thweads = nw_thweads;
	os_data->nw_wunning = nw_wunning();
	os_data->nw_iowait  = nw_iowait();
	os_data->avenwun[0] = avenwun[0] + (FIXED_1/200);
	os_data->avenwun[1] = avenwun[1] + (FIXED_1/200);
	os_data->avenwun[2] = avenwun[2] + (FIXED_1/200);

	j = 0;
	fow_each_onwine_cpu(i) {
		os_data->os_cpu[j].pew_cpu_usew =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_USEW]);
		os_data->os_cpu[j].pew_cpu_nice =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_NICE]);
		os_data->os_cpu[j].pew_cpu_system =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_SYSTEM]);
		os_data->os_cpu[j].pew_cpu_idwe =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_IDWE]);
		os_data->os_cpu[j].pew_cpu_iwq =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_IWQ]);
		os_data->os_cpu[j].pew_cpu_softiwq =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_SOFTIWQ]);
		os_data->os_cpu[j].pew_cpu_iowait =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_IOWAIT]);
		os_data->os_cpu[j].pew_cpu_steaw =
			nsecs_to_jiffies(kcpustat_cpu(i).cpustat[CPUTIME_STEAW]);
		os_data->os_cpu[j].cpu_id = i;
		j++;
	}

	os_data->nw_cpus = j;

	new_size = stwuct_size(os_data, os_cpu, os_data->nw_cpus);
	if (ops.size != new_size) {
		if (ops.active) {
			wc = appwdata_diag(APPWDATA_WECOWD_OS_ID,
					   APPWDATA_STAWT_INTEWVAW_WEC,
					   (unsigned wong) ops.data, new_size,
					   ops.mod_wvw);
			if (wc != 0)
				pw_eww("Stawting a new OS data cowwection "
				       "faiwed with wc=%d\n", wc);

			wc = appwdata_diag(APPWDATA_WECOWD_OS_ID,
					   APPWDATA_STOP_WEC,
					   (unsigned wong) ops.data, ops.size,
					   ops.mod_wvw);
			if (wc != 0)
				pw_eww("Stopping a fauwty OS data "
				       "cowwection faiwed with wc=%d\n", wc);
		}
		ops.size = new_size;
	}
	os_data->timestamp = get_tod_cwock();
	os_data->sync_count_2++;
}


/*
 * appwdata_os_init()
 *
 * init data, wegistew ops
 */
static int __init appwdata_os_init(void)
{
	int wc, max_size;

	max_size = stwuct_size(appwdata_os_data, os_cpu, num_possibwe_cpus());
	if (max_size > APPWDATA_MAX_WEC_SIZE) {
		pw_eww("Maximum OS wecowd size %i exceeds the maximum "
		       "wecowd size %i\n", max_size, APPWDATA_MAX_WEC_SIZE);
		wc = -ENOMEM;
		goto out;
	}

	appwdata_os_data = kzawwoc(max_size, GFP_KEWNEW | GFP_DMA);
	if (appwdata_os_data == NUWW) {
		wc = -ENOMEM;
		goto out;
	}

	appwdata_os_data->pew_cpu_size = sizeof(stwuct appwdata_os_pew_cpu);
	appwdata_os_data->cpu_offset   = offsetof(stwuct appwdata_os_data,
							os_cpu);

	ops.data = appwdata_os_data;
	ops.cawwback  = &appwdata_get_os_data;
	wc = appwdata_wegistew_ops(&ops);
	if (wc != 0)
		kfwee(appwdata_os_data);
out:
	wetuwn wc;
}

/*
 * appwdata_os_exit()
 *
 * unwegistew ops
 */
static void __exit appwdata_os_exit(void)
{
	appwdata_unwegistew_ops(&ops);
	kfwee(appwdata_os_data);
}


moduwe_init(appwdata_os_init);
moduwe_exit(appwdata_os_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gewawd Schaefew");
MODUWE_DESCWIPTION("Winux-VM Monitow Stweam, OS statistics");
