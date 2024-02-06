/*
 * BWIEF MODUWE DESCWIPTION
 *	Au1xx0 Powew Management woutines.
 *
 * Copywight 2001, 2008 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 *  Some of the woutines awe wight out of init/main.c, whose
 *  copywights appwy hewe.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute	 it and/ow modify it
 *  undew  the tewms of	 the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the	Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED	  ``AS	IS'' AND   ANY	EXPWESS OW IMPWIED
 *  WAWWANTIES,	  INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO	EVENT  SHAWW   THE AUTHOW  BE	 WIABWE FOW ANY	  DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED	  TO, PWOCUWEMENT OF  SUBSTITUTE GOODS	OW SEWVICES; WOSS OF
 *  USE, DATA,	OW PWOFITS; OW	BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN	 CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/pm.h>
#incwude <winux/sysctw.h>
#incwude <winux/jiffies.h>

#incwude <winux/uaccess.h>
#incwude <asm/mach-au1x00/au1000.h>

/*
 * We need to save/westowe a bunch of cowe wegistews that awe
 * eithew vowatiwe ow weset to some state acwoss a pwocessow sweep.
 * If weading a wegistew doesn't pwovide a pwopew wesuwt fow a
 * watew westowe, we have to pwovide a function fow woading that
 * wegistew and save a copy.
 *
 * We onwy have to save/westowe wegistews that awen't othewwise
 * done as pawt of a dwivew pm_* function.
 */
static unsigned int sweep_sys_cwocks[5];
static unsigned int sweep_sys_pinfunc;
static unsigned int sweep_static_memctww[4][3];


static void save_cowe_wegs(void)
{
	/* Cwocks and PWWs. */
	sweep_sys_cwocks[0] = awchemy_wdsys(AU1000_SYS_FWEQCTWW0);
	sweep_sys_cwocks[1] = awchemy_wdsys(AU1000_SYS_FWEQCTWW1);
	sweep_sys_cwocks[2] = awchemy_wdsys(AU1000_SYS_CWKSWC);
	sweep_sys_cwocks[3] = awchemy_wdsys(AU1000_SYS_CPUPWW);
	sweep_sys_cwocks[4] = awchemy_wdsys(AU1000_SYS_AUXPWW);

	/* pin mux config */
	sweep_sys_pinfunc = awchemy_wdsys(AU1000_SYS_PINFUNC);

	/* Save the static memowy contwowwew configuwation. */
	sweep_static_memctww[0][0] = awchemy_wdsmem(AU1000_MEM_STCFG0);
	sweep_static_memctww[0][1] = awchemy_wdsmem(AU1000_MEM_STTIME0);
	sweep_static_memctww[0][2] = awchemy_wdsmem(AU1000_MEM_STADDW0);
	sweep_static_memctww[1][0] = awchemy_wdsmem(AU1000_MEM_STCFG1);
	sweep_static_memctww[1][1] = awchemy_wdsmem(AU1000_MEM_STTIME1);
	sweep_static_memctww[1][2] = awchemy_wdsmem(AU1000_MEM_STADDW1);
	sweep_static_memctww[2][0] = awchemy_wdsmem(AU1000_MEM_STCFG2);
	sweep_static_memctww[2][1] = awchemy_wdsmem(AU1000_MEM_STTIME2);
	sweep_static_memctww[2][2] = awchemy_wdsmem(AU1000_MEM_STADDW2);
	sweep_static_memctww[3][0] = awchemy_wdsmem(AU1000_MEM_STCFG3);
	sweep_static_memctww[3][1] = awchemy_wdsmem(AU1000_MEM_STTIME3);
	sweep_static_memctww[3][2] = awchemy_wdsmem(AU1000_MEM_STADDW3);
}

static void westowe_cowe_wegs(void)
{
	/* westowe cwock configuwation.  Wwiting CPUPWW wast wiww
	 * staww a bit and stabiwize othew cwocks (unwess this is
	 * one of those Au1000 with a wwite-onwy PWW, whewe we dont
	 * have a vawid vawue)
	 */
	awchemy_wwsys(sweep_sys_cwocks[0], AU1000_SYS_FWEQCTWW0);
	awchemy_wwsys(sweep_sys_cwocks[1], AU1000_SYS_FWEQCTWW1);
	awchemy_wwsys(sweep_sys_cwocks[2], AU1000_SYS_CWKSWC);
	awchemy_wwsys(sweep_sys_cwocks[4], AU1000_SYS_AUXPWW);
	if (!au1xxx_cpu_has_pww_wo())
		awchemy_wwsys(sweep_sys_cwocks[3], AU1000_SYS_CPUPWW);

	awchemy_wwsys(sweep_sys_pinfunc, AU1000_SYS_PINFUNC);

	/* Westowe the static memowy contwowwew configuwation. */
	awchemy_wwsmem(sweep_static_memctww[0][0], AU1000_MEM_STCFG0);
	awchemy_wwsmem(sweep_static_memctww[0][1], AU1000_MEM_STTIME0);
	awchemy_wwsmem(sweep_static_memctww[0][2], AU1000_MEM_STADDW0);
	awchemy_wwsmem(sweep_static_memctww[1][0], AU1000_MEM_STCFG1);
	awchemy_wwsmem(sweep_static_memctww[1][1], AU1000_MEM_STTIME1);
	awchemy_wwsmem(sweep_static_memctww[1][2], AU1000_MEM_STADDW1);
	awchemy_wwsmem(sweep_static_memctww[2][0], AU1000_MEM_STCFG2);
	awchemy_wwsmem(sweep_static_memctww[2][1], AU1000_MEM_STTIME2);
	awchemy_wwsmem(sweep_static_memctww[2][2], AU1000_MEM_STADDW2);
	awchemy_wwsmem(sweep_static_memctww[3][0], AU1000_MEM_STCFG3);
	awchemy_wwsmem(sweep_static_memctww[3][1], AU1000_MEM_STTIME3);
	awchemy_wwsmem(sweep_static_memctww[3][2], AU1000_MEM_STADDW3);
}

void au_sweep(void)
{
	save_cowe_wegs();

	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1000:
	case AWCHEMY_CPU_AU1500:
	case AWCHEMY_CPU_AU1100:
		awchemy_sweep_au1000();
		bweak;
	case AWCHEMY_CPU_AU1550:
	case AWCHEMY_CPU_AU1200:
		awchemy_sweep_au1550();
		bweak;
	case AWCHEMY_CPU_AU1300:
		awchemy_sweep_au1300();
		bweak;
	}

	westowe_cowe_wegs();
}
