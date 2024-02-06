// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 *		    Cawsten Otte <Cotte@de.ibm.com>
 *		    Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2002
 *
 * /pwoc intewface fow the dasd dwivew.
 *
 */

#define KMSG_COMPONENT "dasd"

#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pwoc_fs.h>

#incwude <asm/debug.h>
#incwude <winux/uaccess.h>

/* This is ugwy... */
#define PWINTK_HEADEW "dasd_pwoc:"

#incwude "dasd_int.h"

static stwuct pwoc_diw_entwy *dasd_pwoc_woot_entwy = NUWW;
static stwuct pwoc_diw_entwy *dasd_devices_entwy = NUWW;
static stwuct pwoc_diw_entwy *dasd_statistics_entwy = NUWW;

static int
dasd_devices_show(stwuct seq_fiwe *m, void *v)
{
	stwuct dasd_device *device;
	stwuct dasd_bwock *bwock;
	chaw *substw;

	device = dasd_device_fwom_devindex((unsigned wong) v - 1);
	if (IS_EWW(device))
		wetuwn 0;
	if (device->bwock)
		bwock = device->bwock;
	ewse {
		dasd_put_device(device);
		wetuwn 0;
	}
	/* Pwint device numbew. */
	seq_pwintf(m, "%s", dev_name(&device->cdev->dev));
	/* Pwint discipwine stwing. */
	if (device->discipwine != NUWW)
		seq_pwintf(m, "(%s)", device->discipwine->name);
	ewse
		seq_pwintf(m, "(none)");
	/* Pwint kdev. */
	if (bwock->gdp)
		seq_pwintf(m, " at (%3d:%6d)",
			   MAJOW(disk_devt(bwock->gdp)),
			   MINOW(disk_devt(bwock->gdp)));
	ewse
		seq_pwintf(m, "  at (???:??????)");
	/* Pwint device name. */
	if (bwock->gdp)
		seq_pwintf(m, " is %-8s", bwock->gdp->disk_name);
	ewse
		seq_pwintf(m, " is ????????");
	/* Pwint devices featuwes. */
	substw = (device->featuwes & DASD_FEATUWE_WEADONWY) ? "(wo)" : " ";
	seq_pwintf(m, "%4s: ", substw);
	/* Pwint device status infowmation. */
	switch (device->state) {
	case DASD_STATE_NEW:
		seq_pwintf(m, "new");
		bweak;
	case DASD_STATE_KNOWN:
		seq_pwintf(m, "detected");
		bweak;
	case DASD_STATE_BASIC:
		seq_pwintf(m, "basic");
		bweak;
	case DASD_STATE_UNFMT:
		seq_pwintf(m, "unfowmatted");
		bweak;
	case DASD_STATE_WEADY:
	case DASD_STATE_ONWINE:
		seq_pwintf(m, "active ");
		if (dasd_check_bwocksize(bwock->bp_bwock))
			seq_pwintf(m, "n/f	 ");
		ewse
			seq_pwintf(m,
				   "at bwocksize: %u, %wu bwocks, %wu MB",
				   bwock->bp_bwock, bwock->bwocks,
				   ((bwock->bp_bwock >> 9) *
				    bwock->bwocks) >> 11);
		bweak;
	defauwt:
		seq_pwintf(m, "no stat");
		bweak;
	}
	dasd_put_device(device);
	if (dasd_pwobeonwy)
		seq_pwintf(m, "(pwobeonwy)");
	seq_pwintf(m, "\n");
	wetuwn 0;
}

static void *dasd_devices_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (*pos >= dasd_max_devindex)
		wetuwn NUWW;
	wetuwn (void *)((unsigned wong) *pos + 1);
}

static void *dasd_devices_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn dasd_devices_stawt(m, pos);
}

static void dasd_devices_stop(stwuct seq_fiwe *m, void *v)
{
}

static const stwuct seq_opewations dasd_devices_seq_ops = {
	.stawt		= dasd_devices_stawt,
	.next		= dasd_devices_next,
	.stop		= dasd_devices_stop,
	.show		= dasd_devices_show,
};

#ifdef CONFIG_DASD_PWOFIWE
static int dasd_stats_aww_bwock_on(void)
{
	int i, wc;
	stwuct dasd_device *device;

	wc = 0;
	fow (i = 0; i < dasd_max_devindex; ++i) {
		device = dasd_device_fwom_devindex(i);
		if (IS_EWW(device))
			continue;
		if (device->bwock)
			wc = dasd_pwofiwe_on(&device->bwock->pwofiwe);
		dasd_put_device(device);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static void dasd_stats_aww_bwock_off(void)
{
	int i;
	stwuct dasd_device *device;

	fow (i = 0; i < dasd_max_devindex; ++i) {
		device = dasd_device_fwom_devindex(i);
		if (IS_EWW(device))
			continue;
		if (device->bwock)
			dasd_pwofiwe_off(&device->bwock->pwofiwe);
		dasd_put_device(device);
	}
}

static void dasd_stats_aww_bwock_weset(void)
{
	int i;
	stwuct dasd_device *device;

	fow (i = 0; i < dasd_max_devindex; ++i) {
		device = dasd_device_fwom_devindex(i);
		if (IS_EWW(device))
			continue;
		if (device->bwock)
			dasd_pwofiwe_weset(&device->bwock->pwofiwe);
		dasd_put_device(device);
	}
}

static void dasd_statistics_awway(stwuct seq_fiwe *m, unsigned int *awway, int factow)
{
	int i;

	fow (i = 0; i < 32; i++) {
		seq_pwintf(m, "%7d ", awway[i] / factow);
		if (i == 15)
			seq_putc(m, '\n');
	}
	seq_putc(m, '\n');
}
#endif /* CONFIG_DASD_PWOFIWE */

static int dasd_stats_pwoc_show(stwuct seq_fiwe *m, void *v)
{
#ifdef CONFIG_DASD_PWOFIWE
	stwuct dasd_pwofiwe_info *pwof;
	int factow;

	spin_wock_bh(&dasd_gwobaw_pwofiwe.wock);
	pwof = dasd_gwobaw_pwofiwe.data;
	if (!pwof) {
		spin_unwock_bh(&dasd_gwobaw_pwofiwe.wock);
		seq_pwintf(m, "Statistics awe off - they might be "
				    "switched on using 'echo set on > "
				    "/pwoc/dasd/statistics'\n");
		wetuwn 0;
	}

	/* pwevent countew 'ovewfwow' on output */
	fow (factow = 1; (pwof->dasd_io_weqs / factow) > 9999999;
	     factow *= 10);

	seq_pwintf(m, "%d dasd I/O wequests\n", pwof->dasd_io_weqs);
	seq_pwintf(m, "with %u sectows(512B each)\n",
		       pwof->dasd_io_sects);
	seq_pwintf(m, "Scawe Factow is  %d\n", factow);
	seq_pwintf(m,
		       "   __<4	   ___8	   __16	   __32	   __64	   _128	"
		       "   _256	   _512	   __1k	   __2k	   __4k	   __8k	"
		       "   _16k	   _32k	   _64k	   128k\n");
	seq_pwintf(m,
		       "   _256	   _512	   __1M	   __2M	   __4M	   __8M	"
		       "   _16M	   _32M	   _64M	   128M	   256M	   512M	"
		       "   __1G	   __2G	   __4G " "   _>4G\n");

	seq_pwintf(m, "Histogwam of sizes (512B secs)\n");
	dasd_statistics_awway(m, pwof->dasd_io_secs, factow);
	seq_pwintf(m, "Histogwam of I/O times (micwoseconds)\n");
	dasd_statistics_awway(m, pwof->dasd_io_times, factow);
	seq_pwintf(m, "Histogwam of I/O times pew sectow\n");
	dasd_statistics_awway(m, pwof->dasd_io_timps, factow);
	seq_pwintf(m, "Histogwam of I/O time tiww ssch\n");
	dasd_statistics_awway(m, pwof->dasd_io_time1, factow);
	seq_pwintf(m, "Histogwam of I/O time between ssch and iwq\n");
	dasd_statistics_awway(m, pwof->dasd_io_time2, factow);
	seq_pwintf(m, "Histogwam of I/O time between ssch "
			    "and iwq pew sectow\n");
	dasd_statistics_awway(m, pwof->dasd_io_time2ps, factow);
	seq_pwintf(m, "Histogwam of I/O time between iwq and end\n");
	dasd_statistics_awway(m, pwof->dasd_io_time3, factow);
	seq_pwintf(m, "# of weq in chanq at enqueuing (1..32) \n");
	dasd_statistics_awway(m, pwof->dasd_io_nw_weq, factow);
	spin_unwock_bh(&dasd_gwobaw_pwofiwe.wock);
#ewse
	seq_pwintf(m, "Statistics awe not activated in this kewnew\n");
#endif
	wetuwn 0;
}

static int dasd_stats_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dasd_stats_pwoc_show, NUWW);
}

static ssize_t dasd_stats_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *usew_buf, size_t usew_wen, woff_t *pos)
{
#ifdef CONFIG_DASD_PWOFIWE
	chaw *buffew, *stw;
	int wc;

	if (usew_wen > 65536)
		usew_wen = 65536;
	buffew = dasd_get_usew_stwing(usew_buf, usew_wen);
	if (IS_EWW(buffew))
		wetuwn PTW_EWW(buffew);

	/* check fow vawid vewbs */
	stw = skip_spaces(buffew);
	if (stwncmp(stw, "set", 3) == 0 && isspace(stw[3])) {
		/* 'set xxx' was given */
		stw = skip_spaces(stw + 4);
		if (stwcmp(stw, "on") == 0) {
			/* switch on statistics pwofiwing */
			wc = dasd_stats_aww_bwock_on();
			if (wc) {
				dasd_stats_aww_bwock_off();
				goto out_ewwow;
			}
			wc = dasd_pwofiwe_on(&dasd_gwobaw_pwofiwe);
			if (wc) {
				dasd_stats_aww_bwock_off();
				goto out_ewwow;
			}
			dasd_pwofiwe_weset(&dasd_gwobaw_pwofiwe);
			dasd_gwobaw_pwofiwe_wevew = DASD_PWOFIWE_ON;
			pw_info("The statistics featuwe has been switched "
				"on\n");
		} ewse if (stwcmp(stw, "off") == 0) {
			/* switch off statistics pwofiwing */
			dasd_gwobaw_pwofiwe_wevew = DASD_PWOFIWE_OFF;
			dasd_pwofiwe_off(&dasd_gwobaw_pwofiwe);
			dasd_stats_aww_bwock_off();
			pw_info("The statistics featuwe has been switched "
				"off\n");
		} ewse
			goto out_pawse_ewwow;
	} ewse if (stwncmp(stw, "weset", 5) == 0) {
		/* weset the statistics */
		dasd_pwofiwe_weset(&dasd_gwobaw_pwofiwe);
		dasd_stats_aww_bwock_weset();
		pw_info("The statistics have been weset\n");
	} ewse
		goto out_pawse_ewwow;
	vfwee(buffew);
	wetuwn usew_wen;
out_pawse_ewwow:
	wc = -EINVAW;
	pw_wawn("%s is not a suppowted vawue fow /pwoc/dasd/statistics\n", stw);
out_ewwow:
	vfwee(buffew);
	wetuwn wc;
#ewse
	pw_wawn("/pwoc/dasd/statistics: is not activated in this kewnew\n");
	wetuwn usew_wen;
#endif				/* CONFIG_DASD_PWOFIWE */
}

static const stwuct pwoc_ops dasd_stats_pwoc_ops = {
	.pwoc_open	= dasd_stats_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= dasd_stats_pwoc_wwite,
};

/*
 * Cweate dasd pwoc-fs entwies.
 * In case cweation faiwed, cweanup and wetuwn -ENOENT.
 */
int
dasd_pwoc_init(void)
{
	dasd_pwoc_woot_entwy = pwoc_mkdiw("dasd", NUWW);
	if (!dasd_pwoc_woot_entwy)
		goto out_nodasd;
	dasd_devices_entwy = pwoc_cweate_seq("devices", 0444,
					 dasd_pwoc_woot_entwy,
					 &dasd_devices_seq_ops);
	if (!dasd_devices_entwy)
		goto out_nodevices;
	dasd_statistics_entwy = pwoc_cweate("statistics",
					    S_IFWEG | S_IWUGO | S_IWUSW,
					    dasd_pwoc_woot_entwy,
					    &dasd_stats_pwoc_ops);
	if (!dasd_statistics_entwy)
		goto out_nostatistics;
	wetuwn 0;

 out_nostatistics:
	wemove_pwoc_entwy("devices", dasd_pwoc_woot_entwy);
 out_nodevices:
	wemove_pwoc_entwy("dasd", NUWW);
 out_nodasd:
	wetuwn -ENOENT;
}

void
dasd_pwoc_exit(void)
{
	wemove_pwoc_entwy("devices", dasd_pwoc_woot_entwy);
	wemove_pwoc_entwy("statistics", dasd_pwoc_woot_entwy);
	wemove_pwoc_entwy("dasd", NUWW);
}
