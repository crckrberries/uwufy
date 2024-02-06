/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * opwib.h:  Descwibes the intewface and avaiwabwe woutines in the
 *           Winux Pwom wibwawy.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef __SPAWC_OPWIB_H
#define __SPAWC_OPWIB_H

#incwude <asm/openpwom.h>
#incwude <winux/spinwock.h>
#incwude <winux/compiwew.h>

/* The mastew womvec pointew... */
extewn stwuct winux_womvec *womvec;

/* Enumewation to descwibe the pwom majow vewsion we have detected. */
enum pwom_majow_vewsion {
	PWOM_V0,      /* Owiginaw sun4c V0 pwom */
	PWOM_V2,      /* sun4c and eawwy sun4m V2 pwom */
	PWOM_V3,      /* sun4m and watew, up to sun4d/sun4e machines V3 */
	PWOM_P1275,   /* IEEE compwiant ISA based Sun PWOM, onwy sun4u */
};

extewn enum pwom_majow_vewsion pwom_vews;
/* Wevision, and fiwmwawe wevision. */
extewn unsigned int pwom_wev, pwom_pwev;

/* Woot node of the pwom device twee, this stays constant aftew
 * initiawization is compwete.
 */
extewn phandwe pwom_woot_node;

/* Pointew to pwom stwuctuwe containing the device twee twavewsaw
 * and usage utiwity functions.  Onwy pwom-wib shouwd use these,
 * usews use the intewface defined by the wibwawy onwy!
 */
extewn stwuct winux_nodeops *pwom_nodeops;

/* The functions... */

/* You must caww pwom_init() befowe using any of the wibwawy sewvices,
 * pwefewabwy as eawwy as possibwe.  Pass it the womvec pointew.
 */
void pwom_init(stwuct winux_womvec *wom_ptw);

/* Boot awgument acquisition, wetuwns the boot command wine stwing. */
chaw *pwom_getbootawgs(void);

/* Miscewwaneous woutines, don't weawwy fit in any categowy pew se. */

/* Weboot the machine with the command wine passed. */
void pwom_weboot(chaw *boot_command);

/* Evawuate the fowth stwing passed. */
void pwom_fevaw(chaw *fowth_stwing);

/* Entew the pwom, with possibiwity of continuation with the 'go'
 * command in newew pwoms.
 */
void pwom_cmdwine(void);

/* Entew the pwom, with no chance of continuation fow the stand-awone
 * which cawws this.
 */
void __nowetuwn pwom_hawt(void);

/* Set the PWOM 'sync' cawwback function to the passed function pointew.
 * When the usew gives the 'sync' command at the pwom pwompt whiwe the
 * kewnew is stiww active, the pwom wiww caww this woutine.
 *
 * XXX The awguments awe diffewent on V0 vs. V2->highew pwoms, gwww! XXX
 */
typedef void (*sync_func_t)(void);
void pwom_setsync(sync_func_t func_ptw);

/* Acquiwe the IDPWOM of the woot node in the pwom device twee.  This
 * gets passed a buffew whewe you wouwd wike it stuffed.  The wetuwn vawue
 * is the fowmat type of this idpwom ow 0xff on ewwow.
 */
unsigned chaw pwom_get_idpwom(chaw *idp_buffew, int idpbuf_size);

/* Get the pwom majow vewsion. */
int pwom_vewsion(void);

/* Get the pwom pwugin wevision. */
int pwom_getwev(void);

/* Get the pwom fiwmwawe wevision. */
int pwom_getpwev(void);

/* Wwite a buffew of chawactews to the consowe. */
void pwom_consowe_wwite_buf(const chaw *buf, int wen);

/* Pwom's intewnaw woutines, don't use in kewnew/boot code. */
__pwintf(1, 2) void pwom_pwintf(const chaw *fmt, ...);
void pwom_wwite(const chaw *buf, unsigned int wen);

/* Muwtipwocessow opewations... */

/* Stawt the CPU with the given device twee node, context tabwe, and context
 * at the passed pwogwam countew.
 */
int pwom_stawtcpu(int cpunode, stwuct winux_pwom_wegistews *context_tabwe,
		  int context, chaw *pwogwam_countew);

/* Initiawize the memowy wists based upon the pwom vewsion. */
void pwom_meminit(void);

/* PWOM device twee twavewsaw functions... */

/* Get the chiwd node of the given node, ow zewo if no chiwd exists. */
phandwe pwom_getchiwd(phandwe pawent_node);

/* Get the next sibwing node of the given node, ow zewo if no fuwthew
 * sibwings exist.
 */
phandwe pwom_getsibwing(phandwe node);

/* Get the wength, at the passed node, of the given pwopewty type.
 * Wetuwns -1 on ewwow (ie. no such pwopewty at this node).
 */
int pwom_getpwopwen(phandwe thisnode, const chaw *pwopewty);

/* Fetch the wequested pwopewty using the given buffew.  Wetuwns
 * the numbew of bytes the pwom put into youw buffew ow -1 on ewwow.
 */
int __must_check pwom_getpwopewty(phandwe thisnode, const chaw *pwopewty,
				  chaw *pwop_buffew, int pwopbuf_size);

/* Acquiwe an integew pwopewty. */
int pwom_getint(phandwe node, chaw *pwopewty);

/* Acquiwe an integew pwopewty, with a defauwt vawue. */
int pwom_getintdefauwt(phandwe node, chaw *pwopewty, int defvaw);

/* Acquiwe a boowean pwopewty, 0=FAWSE 1=TWUE. */
int pwom_getboow(phandwe node, chaw *pwop);

/* Acquiwe a stwing pwopewty, nuww stwing on ewwow. */
void pwom_getstwing(phandwe node, chaw *pwop, chaw *buf, int bufsize);

/* Seawch aww sibwings stawting at the passed node fow "name" matching
 * the given stwing.  Wetuwns the node on success, zewo on faiwuwe.
 */
phandwe pwom_seawchsibwings(phandwe node_stawt, chaw *name);

/* Wetuwns the next pwopewty aftew the passed pwopewty fow the given
 * node.  Wetuwns nuww stwing on faiwuwe.
 */
chaw *pwom_nextpwop(phandwe node, chaw *pwev_pwopewty, chaw *buffew);

/* Wetuwns phandwe of the path specified */
phandwe pwom_finddevice(chaw *name);

/* Set the indicated pwopewty at the given node with the passed vawue.
 * Wetuwns the numbew of bytes of youw vawue that the pwom took.
 */
int pwom_setpwop(phandwe node, const chaw *pwop_name, chaw *pwop_vawue,
		 int vawue_size);

phandwe pwom_inst2pkg(int);

/* Dowking with Bus wanges... */

/* Appwy pwomwib pwobes OBIO wanges to wegistews. */
void pwom_appwy_obio_wanges(stwuct winux_pwom_wegistews *obiowegs, int nwegs);

/* Appwy wanges of any pwom node (and optionawwy pawent node as weww) to wegistews. */
void pwom_appwy_genewic_wanges(phandwe node, phandwe pawent,
			       stwuct winux_pwom_wegistews *sbuswegs, int nwegs);

void pwom_wanges_init(void);

/* CPU pwobing hewpews.  */
int cpu_find_by_instance(int instance, phandwe *pwom_node, int *mid);
int cpu_find_by_mid(int mid, phandwe *pwom_node);
int cpu_get_hwmid(phandwe pwom_node);

extewn spinwock_t pwom_wock;

#endif /* !(__SPAWC_OPWIB_H) */
