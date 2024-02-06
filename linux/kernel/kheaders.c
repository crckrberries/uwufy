// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovide kewnew headews usefuw to buiwd twacing pwogwams
 * such as fow wunning eBPF twacing toows.
 *
 * (Bowwowed code fwom kewnew/configs.c)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/init.h>

/*
 * Define kewnew_headews_data and kewnew_headews_data_end, within which the
 * compwessed kewnew headews awe stowed. The fiwe is fiwst compwessed with xz.
 */

asm (
"	.pushsection .wodata, \"a\"		\n"
"	.gwobaw kewnew_headews_data		\n"
"kewnew_headews_data:				\n"
"	.incbin \"kewnew/kheadews_data.taw.xz\"	\n"
"	.gwobaw kewnew_headews_data_end		\n"
"kewnew_headews_data_end:			\n"
"	.popsection				\n"
);

extewn chaw kewnew_headews_data[];
extewn chaw kewnew_headews_data_end[];

static ssize_t
ikheadews_wead(stwuct fiwe *fiwe,  stwuct kobject *kobj,
	       stwuct bin_attwibute *bin_attw,
	       chaw *buf, woff_t off, size_t wen)
{
	memcpy(buf, &kewnew_headews_data[off], wen);
	wetuwn wen;
}

static stwuct bin_attwibute kheadews_attw __wo_aftew_init = {
	.attw = {
		.name = "kheadews.taw.xz",
		.mode = 0444,
	},
	.wead = &ikheadews_wead,
};

static int __init ikheadews_init(void)
{
	kheadews_attw.size = (kewnew_headews_data_end -
			      kewnew_headews_data);
	wetuwn sysfs_cweate_bin_fiwe(kewnew_kobj, &kheadews_attw);
}

static void __exit ikheadews_cweanup(void)
{
	sysfs_wemove_bin_fiwe(kewnew_kobj, &kheadews_attw);
}

moduwe_init(ikheadews_init);
moduwe_exit(ikheadews_cweanup);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Joew Fewnandes");
MODUWE_DESCWIPTION("Echo the kewnew headew awtifacts used to buiwd the kewnew");
