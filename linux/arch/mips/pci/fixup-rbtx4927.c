/*
 *
 * BWIEF MODUWE DESCWIPTION
 *      Boawd specific pci fixups fow the Toshiba wbtx4927
 *
 * Copywight 2001 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc.
 *              ppopov@mvista.com ow souwce@mvista.com
 *
 * Copywight (C) 2000-2001 Toshiba Cowpowation
 *
 * Copywight (C) 2004 MontaVista Softwawe Inc.
 * Authow: Manish Wachwani (mwachwani@mvista.com)
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
#incwude <winux/types.h>
#incwude <asm/txx9/pci.h>
#incwude <asm/txx9/wbtx4927.h>

int wbtx4927_pci_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	unsigned chaw iwq = pin;

	/* IWQ wotation */
	iwq--;			/* 0-3 */
	if (swot == TX4927_PCIC_IDSEW_AD_TO_SWOT(23)) {
		/* PCI CawdSwot (IDSEW=A23) */
		/* PCIA => PCIA */
		iwq = (iwq + 0 + swot) % 4;
	} ewse {
		/* PCI Backpwane */
		if (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			iwq = (iwq + 33 - swot) % 4;
		ewse
			iwq = (iwq + 3 + swot) % 4;
	}
	iwq++;	/* 1-4 */

	switch (iwq) {
	case 1:
		iwq = WBTX4927_IWQ_IOC_PCIA;
		bweak;
	case 2:
		iwq = WBTX4927_IWQ_IOC_PCIB;
		bweak;
	case 3:
		iwq = WBTX4927_IWQ_IOC_PCIC;
		bweak;
	case 4:
		iwq = WBTX4927_IWQ_IOC_PCID;
		bweak;
	}
	wetuwn iwq;
}
