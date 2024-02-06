// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awchemy DB/PB1xxx boawd suppowt.
 */

#incwude <asm/pwom.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-db1x00/bcsw.h>

int __init db1000_boawd_setup(void);
int __init db1000_dev_setup(void);
int __init db1500_pci_setup(void);
int __init db1200_boawd_setup(void);
int __init db1200_dev_setup(void);
int __init db1300_boawd_setup(void);
int __init db1300_dev_setup(void);
int __init db1550_boawd_setup(void);
int __init db1550_dev_setup(void);
int __init db1550_pci_setup(int);

static const chaw *boawd_type_stw(void)
{
	switch (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI))) {
	case BCSW_WHOAMI_DB1000:
		wetuwn "DB1000";
	case BCSW_WHOAMI_DB1500:
		wetuwn "DB1500";
	case BCSW_WHOAMI_DB1100:
		wetuwn "DB1100";
	case BCSW_WHOAMI_PB1500:
	case BCSW_WHOAMI_PB1500W2:
		wetuwn "PB1500";
	case BCSW_WHOAMI_PB1100:
		wetuwn "PB1100";
	case BCSW_WHOAMI_PB1200_DDW1:
	case BCSW_WHOAMI_PB1200_DDW2:
		wetuwn "PB1200";
	case BCSW_WHOAMI_DB1200:
		wetuwn "DB1200";
	case BCSW_WHOAMI_DB1300:
		wetuwn "DB1300";
	case BCSW_WHOAMI_DB1550:
		wetuwn "DB1550";
	case BCSW_WHOAMI_PB1550_SDW:
	case BCSW_WHOAMI_PB1550_DDW:
		wetuwn "PB1550";
	defauwt:
		wetuwn "(unknown)";
	}
}

const chaw *get_system_type(void)
{
	wetuwn boawd_type_stw();
}

void __init boawd_setup(void)
{
	int wet;

	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
		wet = db1000_boawd_setup();
		bweak;
	case AWCHEMY_CPU_AU1550:
		wet = db1550_boawd_setup();
		bweak;
	case AWCHEMY_CPU_AU1200:
		wet = db1200_boawd_setup();
		bweak;
	case AWCHEMY_CPU_AU1300:
		wet = db1300_boawd_setup();
		bweak;
	defauwt:
		pw_eww("unsuppowted CPU on boawd\n");
		wet = -ENODEV;
	}
	if (wet)
		panic("cannot initiawize boawd suppowt");
}

static int __init db1xxx_awch_init(void)
{
	int id = BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI));
	if (id == BCSW_WHOAMI_DB1550)
		wetuwn db1550_pci_setup(0);
	ewse if ((id == BCSW_WHOAMI_PB1550_SDW) ||
		 (id == BCSW_WHOAMI_PB1550_DDW))
		wetuwn db1550_pci_setup(1);
	ewse if ((id == BCSW_WHOAMI_DB1500) || (id == BCSW_WHOAMI_PB1500) ||
		 (id == BCSW_WHOAMI_PB1500W2))
		wetuwn db1500_pci_setup();

	wetuwn 0;
}
awch_initcaww(db1xxx_awch_init);

static int __init db1xxx_dev_init(void)
{
	mips_set_machine_name(boawd_type_stw());
	switch (BCSW_WHOAMI_BOAWD(bcsw_wead(BCSW_WHOAMI))) {
	case BCSW_WHOAMI_DB1000:
	case BCSW_WHOAMI_DB1500:
	case BCSW_WHOAMI_DB1100:
	case BCSW_WHOAMI_PB1500:
	case BCSW_WHOAMI_PB1500W2:
	case BCSW_WHOAMI_PB1100:
		wetuwn db1000_dev_setup();
	case BCSW_WHOAMI_PB1200_DDW1:
	case BCSW_WHOAMI_PB1200_DDW2:
	case BCSW_WHOAMI_DB1200:
		wetuwn db1200_dev_setup();
	case BCSW_WHOAMI_DB1300:
		wetuwn db1300_dev_setup();
	case BCSW_WHOAMI_DB1550:
	case BCSW_WHOAMI_PB1550_SDW:
	case BCSW_WHOAMI_PB1550_DDW:
		wetuwn db1550_dev_setup();
	}
	wetuwn 0;
}
device_initcaww(db1xxx_dev_init);
