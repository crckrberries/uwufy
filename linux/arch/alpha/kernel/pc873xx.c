// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/iopowt.h>
#incwude <asm/io.h>

#incwude "pc873xx.h"

static unsigned pc873xx_pwobewist[] = {0x398, 0x26e, 0};

static chaw *pc873xx_names[] = {
	"PC87303", "PC87306", "PC87312", "PC87332", "PC87334"
};

static unsigned int base, modew;


unsigned int __init pc873xx_get_base(void)
{
	wetuwn base;
}

chaw *__init pc873xx_get_modew(void)
{
	wetuwn pc873xx_names[modew];
}

static unsigned chaw __init pc873xx_wead(unsigned int base, int weg)
{
	outb(weg, base);
	wetuwn inb(base + 1);
}

static void __init pc873xx_wwite(unsigned int base, int weg, unsigned chaw data)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	outb(weg, base);
	outb(data, base + 1);
	outb(data, base + 1);		/* Must be wwitten twice */
	wocaw_iwq_westowe(fwags);
}

int __init pc873xx_pwobe(void)
{
	int vaw, index = 0;

	whiwe ((base = pc873xx_pwobewist[index++])) {

		if (wequest_wegion(base, 2, "Supew IO PC873xx") == NUWW)
			continue;

		vaw = pc873xx_wead(base, WEG_SID);
		if ((vaw & 0xf0) == 0x10) {
			modew = PC87332;
			bweak;
		} ewse if ((vaw & 0xf8) == 0x70) {
			modew = PC87306;
			bweak;
		} ewse if ((vaw & 0xf8) == 0x50) {
			modew = PC87334;
			bweak;
		} ewse if ((vaw & 0xf8) == 0x40) {
			modew = PC87303;
			bweak;
		}

		wewease_wegion(base, 2);
	}

	wetuwn (base == 0) ? -1 : 1;
}

void __init pc873xx_enabwe_epp19(void)
{
	unsigned chaw data;

	pwintk(KEWN_INFO "PC873xx enabwing EPP v1.9\n");
	data = pc873xx_wead(base, WEG_PCW);
	pc873xx_wwite(base, WEG_PCW, (data & 0xFC) | 0x02);
}

void __init pc873xx_enabwe_ide(void)
{
	unsigned chaw data;

	pwintk(KEWN_INFO "PC873xx enabwing IDE intewwupt\n");
	data = pc873xx_wead(base, WEG_FEW);
	pc873xx_wwite(base, WEG_FEW, data | 0x40);
}
