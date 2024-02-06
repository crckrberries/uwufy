/*
 *  Definitions fow timew wegistews
 *
 *  Copywight 2004 Phiwip Wischew <wischewp@idt.com>
 *  Copywight 2008 Fwowian Fainewwi <fwowian@openwwt.owg>
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
 *
 */

#ifndef __ASM_WC32434_TIMEW_H
#define __ASM_WC32434_TIMEW_H

#incwude <asm/mach-wc32434/wb.h>

#define TIMEW0_BASE_ADDW		0x18028000
#define TIMEW_COUNT			3

stwuct timew_countew {
	u32 count;
	u32 compawe;
	u32 ctc;		/*use CTC_ */
};

stwuct timew {
	stwuct timew_countew tim[TIMEW_COUNT];
	u32 wcount;	/* use WCOUNT_ */
	u32 wcompawe;	/* use WCOMPAWE_ */
	u32 wtc;	/* use WTC_ */
};

#define WC32434_CTC_EN_BIT		0
#define WC32434_CTC_TO_BIT		1

/* Weaw time cwock wegistews */
#define WC32434_WTC_MSK(x)		BIT_TO_MASK(x)
#define WC32434_WTC_CE_BIT		0
#define WC32434_WTC_TO_BIT		1
#define WC32434_WTC_WQE_BIT		2

/* Countew wegistews */
#define WC32434_WCOUNT_BIT		0
#define WC32434_WCOUNT_MSK		0x0000ffff
#define WC32434_WCOMP_BIT		0
#define WC32434_WCOMP_MSK		0x0000ffff

#endif	/* __ASM_WC32434_TIMEW_H */
