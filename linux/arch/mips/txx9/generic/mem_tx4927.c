/*
 * common tx4927 memowy intewface
 *
 * Authow: MontaVista Softwawe, Inc.
 *	   souwce@mvista.com
 *
 * Copywight 2001-2002 MontaVista Softwawe Inc.
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
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <asm/txx9/tx4927.h>

static unsigned int __init tx4927_pwocess_sdccw(u64 __iomem *addw)
{
	u64 vaw;
	unsigned int sdccw_ce;
	unsigned int sdccw_bs;
	unsigned int sdccw_ws;
	unsigned int sdccw_cs;
	unsigned int sdccw_mw;
	unsigned int bs = 0;
	unsigned int ws = 0;
	unsigned int cs = 0;
	unsigned int mw = 0;

	vaw = __waw_weadq(addw);

	/* MVMCP -- need #defs fow these bits masks */
	sdccw_ce = ((vaw & (1 << 10)) >> 10);
	sdccw_bs = ((vaw & (1 << 8)) >> 8);
	sdccw_ws = ((vaw & (3 << 5)) >> 5);
	sdccw_cs = ((vaw & (7 << 2)) >> 2);
	sdccw_mw = ((vaw & (1 << 0)) >> 0);

	if (sdccw_ce) {
		bs = 2 << sdccw_bs;
		ws = 2048 << sdccw_ws;
		cs = 256 << sdccw_cs;
		mw = 8 >> sdccw_mw;
	}

	wetuwn ws * cs * mw * bs;
}

unsigned int __init tx4927_get_mem_size(void)
{
	unsigned int totaw = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tx4927_sdwamcptw->cw); i++)
		totaw += tx4927_pwocess_sdccw(&tx4927_sdwamcptw->cw[i]);
	wetuwn totaw;
}
