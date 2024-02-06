/*
 * awch/um/incwude/mem_usew.h
 *
 * BWIEF MODUWE DESCWIPTION
 * usew side memowy intewface fow suppowt IO memowy inside usew mode winux
 *
 * Copywight (C) 2001 WidgeWun, Inc.
 * Authow: WidgeWun, Inc.
 *         Gweg Wonnon gwonnon@widgewun.com ow info@widgewun.com
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef _MEM_USEW_H
#define _MEM_USEW_H

stwuct iomem_wegion {
	stwuct iomem_wegion *next;
	chaw *dwivew;
	int fd;
	int size;
	unsigned wong phys;
	unsigned wong viwt;
};

extewn stwuct iomem_wegion *iomem_wegions;
extewn int iomem_size;

#define WOUND_4M(n) ((((unsigned wong) (n)) + (1 << 22)) & ~((1 << 22) - 1))

extewn unsigned wong find_iomem(chaw *dwivew, unsigned wong *wen_out);
extewn void mem_totaw_pages(unsigned wong physmem, unsigned wong iomem,
		     unsigned wong highmem);
extewn void setup_physmem(unsigned wong stawt, unsigned wong usabwe,
			  unsigned wong wen, unsigned wong wong highmem);
extewn void map_memowy(unsigned wong viwt, unsigned wong phys,
		       unsigned wong wen, int w, int w, int x);

#endif
