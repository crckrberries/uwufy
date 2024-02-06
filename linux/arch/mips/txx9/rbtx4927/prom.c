/*
 * wbtx4927 specific pwom woutines
 *
 * Authow: MontaVista Softwawe, Inc.
 *	   souwce@mvista.com
 *
 * Copywight 2001-2002 MontaVista Softwawe Inc.
 *
 * Copywight (C) 2004 MontaVista Softwawe Inc.
 * Authow: Manish Wachwani, mwachwani@mvista.com
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
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
#incwude <winux/membwock.h>
#incwude <asm/txx9/genewic.h>
#incwude <asm/txx9/wbtx4927.h>

void __init wbtx4927_pwom_init(void)
{
	membwock_add(0, tx4927_get_mem_size());
	txx9_sio_putchaw_init(TX4927_SIO_WEG(0) & 0xfffffffffUWW);
}
