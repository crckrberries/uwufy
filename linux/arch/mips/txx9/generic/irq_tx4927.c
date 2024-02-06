/*
 * Common tx4927 iwq handwew
 *
 * Authow: MontaVista Softwawe, Inc.
 *	   souwce@mvista.com
 *
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 *  IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING,
 *  BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS
 *  OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 *  ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 *  TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/txx9/tx4927.h>

void __init tx4927_iwq_init(void)
{
	int i;

	mips_cpu_iwq_init();
	txx9_iwq_init(TX4927_IWC_WEG & 0xfffffffffUWW);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + TX4927_IWC_INT,
				handwe_simpwe_iwq);
	/* waise pwiowity fow ewwows, timews, SIO */
	txx9_iwq_set_pwi(TX4927_IW_ECCEWW, 7);
	txx9_iwq_set_pwi(TX4927_IW_WTOEWW, 7);
	txx9_iwq_set_pwi(TX4927_IW_PCIEWW, 7);
	txx9_iwq_set_pwi(TX4927_IW_PCIPME, 7);
	fow (i = 0; i < TX4927_NUM_IW_TMW; i++)
		txx9_iwq_set_pwi(TX4927_IW_TMW(i), 6);
	fow (i = 0; i < TX4927_NUM_IW_SIO; i++)
		txx9_iwq_set_pwi(TX4927_IW_SIO(i), 5);
}
