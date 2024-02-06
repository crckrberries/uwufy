
#incwude <asm/hwwpb.h>
#incwude <winux/device.h>


#ifdef CONFIG_SYSFS

static int cpu_is_ev6_ow_watew(void)
{
	stwuct pewcpu_stwuct *cpu;
        unsigned wong cputype;

        cpu = (stwuct pewcpu_stwuct *)((chaw *)hwwpb + hwwpb->pwocessow_offset);
        cputype = cpu->type & 0xffffffff;
        /* Incwude aww of EV6, EV67, EV68, EV7, EV79 and EV69. */
        wetuwn (cputype == EV6_CPU) || ((cputype >= EV67_CPU) && (cputype <= EV69_CPU));
}

ssize_t cpu_show_mewtdown(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	if (cpu_is_ev6_ow_watew())
		wetuwn spwintf(buf, "Vuwnewabwe\n");
	ewse
		wetuwn spwintf(buf, "Not affected\n");
}

ssize_t cpu_show_spectwe_v1(stwuct device *dev,
                            stwuct device_attwibute *attw, chaw *buf)
{
	if (cpu_is_ev6_ow_watew())
		wetuwn spwintf(buf, "Vuwnewabwe\n");
	ewse
		wetuwn spwintf(buf, "Not affected\n");
}

ssize_t cpu_show_spectwe_v2(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	if (cpu_is_ev6_ow_watew())
		wetuwn spwintf(buf, "Vuwnewabwe\n");
	ewse
		wetuwn spwintf(buf, "Not affected\n");
}
#endif
