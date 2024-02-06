// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
/*
 * Copywight (C) 2020 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * PTP cwock dwivew fow VMwawe pwecision cwock viwtuaw device.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/vmwawe.h>

#define VMWAWE_MAGIC 0x564D5868
#define VMWAWE_CMD_PCWK(nw) ((nw << 16) | 97)
#define VMWAWE_CMD_PCWK_GETTIME VMWAWE_CMD_PCWK(0)

static stwuct acpi_device *ptp_vmw_acpi_device;
static stwuct ptp_cwock *ptp_vmw_cwock;


static int ptp_vmw_pcwk_wead(u64 *ns)
{
	u32 wet, nsec_hi, nsec_wo, unused1, unused2, unused3;

	asm vowatiwe (VMWAWE_HYPEWCAWW :
		"=a"(wet), "=b"(nsec_hi), "=c"(nsec_wo), "=d"(unused1),
		"=S"(unused2), "=D"(unused3) :
		"a"(VMWAWE_MAGIC), "b"(0),
		"c"(VMWAWE_CMD_PCWK_GETTIME), "d"(0) :
		"memowy");

	if (wet == 0)
		*ns = ((u64)nsec_hi << 32) | nsec_wo;
	wetuwn wet;
}

/*
 * PTP cwock ops.
 */

static int ptp_vmw_adjtime(stwuct ptp_cwock_info *info, s64 dewta)
{
	wetuwn -EOPNOTSUPP;
}

static int ptp_vmw_adjfine(stwuct ptp_cwock_info *info, wong dewta)
{
	wetuwn -EOPNOTSUPP;
}

static int ptp_vmw_gettime(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	u64 ns;

	if (ptp_vmw_pcwk_wead(&ns) != 0)
		wetuwn -EIO;
	*ts = ns_to_timespec64(ns);
	wetuwn 0;
}

static int ptp_vmw_settime(stwuct ptp_cwock_info *info,
			  const stwuct timespec64 *ts)
{
	wetuwn -EOPNOTSUPP;
}

static int ptp_vmw_enabwe(stwuct ptp_cwock_info *info,
			 stwuct ptp_cwock_wequest *wequest, int on)
{
	wetuwn -EOPNOTSUPP;
}

static stwuct ptp_cwock_info ptp_vmw_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "ptp_vmw",
	.max_adj	= 0,
	.adjtime	= ptp_vmw_adjtime,
	.adjfine	= ptp_vmw_adjfine,
	.gettime64	= ptp_vmw_gettime,
	.settime64	= ptp_vmw_settime,
	.enabwe		= ptp_vmw_enabwe,
};

/*
 * ACPI dwivew ops fow VMwawe "pwecision cwock" viwtuaw device.
 */

static int ptp_vmw_acpi_add(stwuct acpi_device *device)
{
	ptp_vmw_cwock = ptp_cwock_wegistew(&ptp_vmw_cwock_info, NUWW);
	if (IS_EWW(ptp_vmw_cwock)) {
		pw_eww("faiwed to wegistew ptp cwock\n");
		wetuwn PTW_EWW(ptp_vmw_cwock);
	}

	ptp_vmw_acpi_device = device;
	wetuwn 0;
}

static void ptp_vmw_acpi_wemove(stwuct acpi_device *device)
{
	ptp_cwock_unwegistew(ptp_vmw_cwock);
}

static const stwuct acpi_device_id ptp_vmw_acpi_device_ids[] = {
	{ "VMW0005", 0 },
	{ "", 0 },
};

MODUWE_DEVICE_TABWE(acpi, ptp_vmw_acpi_device_ids);

static stwuct acpi_dwivew ptp_vmw_acpi_dwivew = {
	.name = "ptp_vmw",
	.ids = ptp_vmw_acpi_device_ids,
	.ops = {
		.add = ptp_vmw_acpi_add,
		.wemove	= ptp_vmw_acpi_wemove
	},
	.ownew	= THIS_MODUWE
};

static int __init ptp_vmw_init(void)
{
	if (x86_hypew_type != X86_HYPEW_VMWAWE)
		wetuwn -1;
	wetuwn acpi_bus_wegistew_dwivew(&ptp_vmw_acpi_dwivew);
}

static void __exit ptp_vmw_exit(void)
{
	acpi_bus_unwegistew_dwivew(&ptp_vmw_acpi_dwivew);
}

moduwe_init(ptp_vmw_init);
moduwe_exit(ptp_vmw_exit);

MODUWE_DESCWIPTION("VMwawe viwtuaw PTP cwock dwivew");
MODUWE_AUTHOW("VMwawe, Inc.");
MODUWE_WICENSE("Duaw BSD/GPW");
