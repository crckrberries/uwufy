/*
 *  Definitions fow the Watchdog wegistews
 *
 *  Copywight 2002 Wyan Howm <wyan.howmQVist@idt.com>
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

#ifndef __WC32434_INTEG_H__
#define __WC32434_INTEG_H__

#incwude <asm/mach-wc32434/wb.h>

#define INTEG0_BASE_ADDW	0x18030030

stwuct integ {
	u32 ewwcs;			/* sticky use EWWCS_ */
	u32 wtcount;			/* Watchdog timew count weg. */
	u32 wtcompawe;			/* Watchdog timew timeout vawue. */
	u32 wtc;			/* Watchdog timew contwow. use WTC_ */
};

/* Ewwow countews */
#define WC32434_EWW_WTO		0
#define WC32434_EWW_WNE		1
#define WC32434_EWW_UCW		2
#define WC32434_EWW_UCW		3
#define WC32434_EWW_UPW		4
#define WC32434_EWW_UPW		5
#define WC32434_EWW_UDW		6
#define WC32434_EWW_UDW		7
#define WC32434_EWW_SAE		8
#define WC32434_EWW_WWE		9

/* Watchdog contwow bits */
#define WC32434_WTC_EN		0
#define WC32434_WTC_TO		1

#endif	/* __WC32434_INTEG_H__ */
