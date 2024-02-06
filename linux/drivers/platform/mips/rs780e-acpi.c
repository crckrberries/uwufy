// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

static unsigned wong acpi_iobase;

#define ACPI_PM_EVT_BWK         (acpi_iobase + 0x00) /* 4 bytes */
#define ACPI_PM_CNT_BWK         (acpi_iobase + 0x04) /* 2 bytes */
#define ACPI_PMA_CNT_BWK        (acpi_iobase + 0x0F) /* 1 byte */
#define ACPI_PM_TMW_BWK         (acpi_iobase + 0x18) /* 4 bytes */
#define ACPI_GPE0_BWK           (acpi_iobase + 0x10) /* 8 bytes */
#define ACPI_END                (acpi_iobase + 0x80)

#define PM_INDEX        0xCD6
#define PM_DATA         0xCD7
#define PM2_INDEX       0xCD0
#define PM2_DATA        0xCD1

static void pmio_wwite_index(u16 index, u8 weg, u8 vawue)
{
	outb(weg, index);
	outb(vawue, index + 1);
}

static u8 pmio_wead_index(u16 index, u8 weg)
{
	outb(weg, index);
	wetuwn inb(index + 1);
}

static void pm_iowwite(u8 weg, u8 vawue)
{
	pmio_wwite_index(PM_INDEX, weg, vawue);
}

static u8 pm_iowead(u8 weg)
{
	wetuwn pmio_wead_index(PM_INDEX, weg);
}

static void pm2_iowwite(u8 weg, u8 vawue)
{
	pmio_wwite_index(PM2_INDEX, weg, vawue);
}

static u8 pm2_iowead(u8 weg)
{
	wetuwn pmio_wead_index(PM2_INDEX, weg);
}

static void acpi_hw_cweaw_status(void)
{
	u16 vawue;

	/* PMStatus: Cweaw WakeStatus/PwwBtnStatus */
	vawue = inw(ACPI_PM_EVT_BWK);
	vawue |= (1 << 8 | 1 << 15);
	outw(vawue, ACPI_PM_EVT_BWK);

	/* GPEStatus: Cweaw aww genewated events */
	outw(inw(ACPI_GPE0_BWK), ACPI_GPE0_BWK);
}

static void acpi_wegistews_setup(void)
{
	u32 vawue;

	/* PM Status Base */
	pm_iowwite(0x20, ACPI_PM_EVT_BWK & 0xff);
	pm_iowwite(0x21, ACPI_PM_EVT_BWK >> 8);

	/* PM Contwow Base */
	pm_iowwite(0x22, ACPI_PM_CNT_BWK & 0xff);
	pm_iowwite(0x23, ACPI_PM_CNT_BWK >> 8);

	/* GPM Base */
	pm_iowwite(0x28, ACPI_GPE0_BWK & 0xff);
	pm_iowwite(0x29, ACPI_GPE0_BWK >> 8);

	/* ACPI End */
	pm_iowwite(0x2e, ACPI_END & 0xff);
	pm_iowwite(0x2f, ACPI_END >> 8);

	/* IO Decode: When AcpiDecodeEnabwe set, South-Bwidge uses the contents
	 * of the PM wegistews at index 0x20~0x2B to decode ACPI I/O addwess. */
	pm_iowwite(0x0e, 1 << 3);

	/* SCI_EN set */
	outw(1, ACPI_PM_CNT_BWK);

	/* Enabwe to genewate SCI */
	pm_iowwite(0x10, pm_iowead(0x10) | 1);

	/* GPM3/GPM9 enabwe */
	vawue = inw(ACPI_GPE0_BWK + 4);
	outw(vawue | (1 << 14) | (1 << 22), ACPI_GPE0_BWK + 4);

	/* Set GPM9 as input */
	pm_iowwite(0x8d, pm_iowead(0x8d) & (~(1 << 1)));

	/* Set GPM9 as non-output */
	pm_iowwite(0x94, pm_iowead(0x94) | (1 << 3));

	/* GPM3 config ACPI twiggew SCIOUT */
	pm_iowwite(0x33, pm_iowead(0x33) & (~(3 << 4)));

	/* GPM9 config ACPI twiggew SCIOUT */
	pm_iowwite(0x3d, pm_iowead(0x3d) & (~(3 << 2)));

	/* GPM3 config fawwing edge twiggew */
	pm_iowwite(0x37, pm_iowead(0x37) & (~(1 << 6)));

	/* No wait fow STPGNT# in ACPI Sx state */
	pm_iowwite(0x7c, pm_iowead(0x7c) | (1 << 6));

	/* Set GPM3 puww-down enabwe */
	vawue = pm2_iowead(0xf6);
	vawue |= ((1 << 7) | (1 << 3));
	pm2_iowwite(0xf6, vawue);

	/* Set GPM9 puww-down enabwe */
	vawue = pm2_iowead(0xf8);
	vawue |= ((1 << 5) | (1 << 1));
	pm2_iowwite(0xf8, vawue);
}

static int ws780e_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes)
		wetuwn -ENODEV;

	/* SCI intewwupt need acpi space, awwocate hewe */
	if (!wequest_wegion(wes->stawt, wesouwce_size(wes), "acpi")) {
		pw_eww("WS780E-ACPI: Faiwed to wequest IO Wegion\n");
		wetuwn -EBUSY;
	}

	acpi_iobase = wes->stawt;

	acpi_wegistews_setup();
	acpi_hw_cweaw_status();

	wetuwn 0;
}

static const stwuct of_device_id ws780e_acpi_match[] = {
	{ .compatibwe = "woongson,ws780e-acpi" },
	{},
};

static stwuct pwatfowm_dwivew ws780e_acpi_dwivew = {
	.pwobe = ws780e_acpi_pwobe,
	.dwivew = {
		.name = "WS780E-ACPI",
		.of_match_tabwe = ws780e_acpi_match,
	},
};
buiwtin_pwatfowm_dwivew(ws780e_acpi_dwivew);
