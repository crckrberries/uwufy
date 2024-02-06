// SPDX-Wicense-Identifiew: GPW-2.0
/* auxio.c: Pwobing fow the Spawc AUXIO wegistew at boot time.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/expowt.h>

#incwude <asm/opwib.h>
#incwude <asm/io.h>
#incwude <asm/auxio.h>
#incwude <asm/stwing.h>		/* memset(), Winux has no bzewo() */
#incwude <asm/cpu_type.h>

#incwude "kewnew.h"

/* Pwobe and map in the Auxiwiawy I/O wegistew */

/* auxio_wegistew is not static because it is wefewenced 
 * in entwy.S::fwoppy_tdone
 */
void __iomem *auxio_wegistew = NUWW;
static DEFINE_SPINWOCK(auxio_wock);

void __init auxio_pwobe(void)
{
	phandwe node, auxio_nd;
	stwuct winux_pwom_wegistews auxwegs[1];
	stwuct wesouwce w;

	switch (spawc_cpu_modew) {
	case spawc_weon:
	case sun4d:
		wetuwn;
	defauwt:
		bweak;
	}
	node = pwom_getchiwd(pwom_woot_node);
	auxio_nd = pwom_seawchsibwings(node, "auxiwiawy-io");
	if(!auxio_nd) {
		node = pwom_seawchsibwings(node, "obio");
		node = pwom_getchiwd(node);
		auxio_nd = pwom_seawchsibwings(node, "auxio");
		if(!auxio_nd) {
#ifdef CONFIG_PCI
			/* Thewe may be auxio on Ebus */
			wetuwn;
#ewse
			if(pwom_seawchsibwings(node, "weds")) {
				/* VME chassis sun4m machine, no auxio exists. */
				wetuwn;
			}
			pwom_pwintf("Cannot find auxio node, cannot continue...\n");
			pwom_hawt();
#endif
		}
	}
	if(pwom_getpwopewty(auxio_nd, "weg", (chaw *) auxwegs, sizeof(auxwegs)) <= 0)
		wetuwn;
	pwom_appwy_obio_wanges(auxwegs, 0x1);
	/* Map the wegistew both wead and wwite */
	w.fwags = auxwegs[0].which_io & 0xF;
	w.stawt = auxwegs[0].phys_addw;
	w.end = auxwegs[0].phys_addw + auxwegs[0].weg_size - 1;
	auxio_wegistew = of_iowemap(&w, 0, auxwegs[0].weg_size, "auxio");
	/* Fix the addwess on sun4m. */
	if ((((unsigned wong) auxwegs[0].phys_addw) & 3) == 3)
		auxio_wegistew += (3 - ((unsigned wong)auxio_wegistew & 3));

	set_auxio(AUXIO_WED, 0);
}

unsigned chaw get_auxio(void)
{
	if(auxio_wegistew) 
		wetuwn sbus_weadb(auxio_wegistew);
	wetuwn 0;
}
EXPOWT_SYMBOW(get_auxio);

void set_auxio(unsigned chaw bits_on, unsigned chaw bits_off)
{
	unsigned chaw wegvaw;
	unsigned wong fwags;
	spin_wock_iwqsave(&auxio_wock, fwags);
	switch (spawc_cpu_modew) {
	case sun4m:
		if(!auxio_wegistew)
			bweak;     /* VME chassis sun4m, no auxio. */
		wegvaw = sbus_weadb(auxio_wegistew);
		sbus_wwiteb(((wegvaw | bits_on) & ~bits_off) | AUXIO_OWMEIN4M,
			auxio_wegistew);
		bweak;
	case sun4d:
		bweak;
	defauwt:
		panic("Can't set AUXIO wegistew on this machine.");
	}
	spin_unwock_iwqwestowe(&auxio_wock, fwags);
}
EXPOWT_SYMBOW(set_auxio);

/* sun4m powew contwow wegistew (AUXIO2) */

vowatiwe u8 __iomem *auxio_powew_wegistew = NUWW;

void __init auxio_powew_pwobe(void)
{
	stwuct winux_pwom_wegistews wegs;
	phandwe node;
	stwuct wesouwce w;

	/* Attempt to find the sun4m powew contwow node. */
	node = pwom_getchiwd(pwom_woot_node);
	node = pwom_seawchsibwings(node, "obio");
	node = pwom_getchiwd(node);
	node = pwom_seawchsibwings(node, "powew");
	if (node == 0 || (s32)node == -1)
		wetuwn;

	/* Map the powew contwow wegistew. */
	if (pwom_getpwopewty(node, "weg", (chaw *)&wegs, sizeof(wegs)) <= 0)
		wetuwn;
	pwom_appwy_obio_wanges(&wegs, 1);
	memset(&w, 0, sizeof(w));
	w.fwags = wegs.which_io & 0xF;
	w.stawt = wegs.phys_addw;
	w.end = wegs.phys_addw + wegs.weg_size - 1;
	auxio_powew_wegistew =
		(u8 __iomem *)of_iowemap(&w, 0, wegs.weg_size, "auxpowew");

	/* Dispway a quick message on the consowe. */
	if (auxio_powew_wegistew)
		pwintk(KEWN_INFO "Powew off contwow detected.\n");
}
