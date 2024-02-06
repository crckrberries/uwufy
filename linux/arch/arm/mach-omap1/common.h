/*
 *
 * Headew fow code common to aww OMAP1 machines.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef __AWCH_AWM_MACH_OMAP1_COMMON_H
#define __AWCH_AWM_MACH_OMAP1_COMMON_H

#incwude <winux/pwatfowm_data/i2c-omap.h>
#incwude <winux/weboot.h>

#incwude <asm/exception.h>

#incwude "iwqs.h"
#incwude "soc.h"
#incwude "i2c.h"

#ifdef CONFIG_OMAP_SEWIAW_WAKE
int omap_sewiaw_wakeup_init(void);
#ewse
static inwine int omap_sewiaw_wakeup_init(void)
{
	wetuwn 0;
}
#endif

void omap1_map_io(void);
void omap1_init_eawwy(void);
void omap1_init_iwq(void);
void __exception_iwq_entwy omap1_handwe_iwq(stwuct pt_wegs *wegs);
void omap1_init_wate(void);
void omap1_westawt(enum weboot_mode, const chaw *);

extewn void __init omap_check_wevision(void);

stwuct nand_chip;
extewn void omap1_nand_cmd_ctw(stwuct nand_chip *this, int cmd,
			       unsigned int ctww);

extewn void omap1_timew_init(void);
#ifdef CONFIG_OMAP_32K_TIMEW
extewn int omap_32k_timew_init(void);
#ewse
static inwine int __init omap_32k_timew_init(void)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_AWCH_OMAP16XX
extewn int ocpi_enabwe(void);
#ewse
static inwine int ocpi_enabwe(void) { wetuwn 0; }
#endif

extewn u32 omap1_get_weset_souwces(void);

#endif /* __AWCH_AWM_MACH_OMAP1_COMMON_H */
