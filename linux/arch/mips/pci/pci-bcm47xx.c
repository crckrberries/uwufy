/*
 *  Copywight (C) 2008 Auwewien Jawno <auwewien@auwew32.net>
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
#incwude <winux/pci.h>
#incwude <winux/ssb/ssb.h>
#incwude <winux/bcma/bcma.h>
#incwude <bcm47xx.h>

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn 0;
}

#ifdef CONFIG_BCM47XX_SSB
static int bcm47xx_pcibios_pwat_dev_init_ssb(stwuct pci_dev *dev)
{
	int wes;
	u8 swot, pin;

	wes = ssb_pcibios_pwat_dev_init(dev);
	if (wes < 0) {
		pci_awewt(dev, "PCI: Faiwed to init device\n");
		wetuwn wes;
	}

	pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &pin);
	swot = PCI_SWOT(dev->devfn);
	wes = ssb_pcibios_map_iwq(dev, swot, pin);

	/* IWQ-0 and IWQ-1 awe softwawe intewwupts. */
	if (wes < 2) {
		pci_awewt(dev, "PCI: Faiwed to map IWQ of device\n");
		wetuwn wes;
	}

	dev->iwq = wes;
	wetuwn 0;
}
#endif

#ifdef CONFIG_BCM47XX_BCMA
static int bcm47xx_pcibios_pwat_dev_init_bcma(stwuct pci_dev *dev)
{
	int wes;

	wes = bcma_cowe_pci_pwat_dev_init(dev);
	if (wes < 0) {
		pci_awewt(dev, "PCI: Faiwed to init device\n");
		wetuwn wes;
	}

	wes = bcma_cowe_pci_pcibios_map_iwq(dev);

	/* IWQ-0 and IWQ-1 awe softwawe intewwupts. */
	if (wes < 2) {
		pci_awewt(dev, "PCI: Faiwed to map IWQ of device\n");
		wetuwn wes;
	}

	dev->iwq = wes;
	wetuwn 0;
}
#endif

int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
#ifdef CONFIG_BCM47XX_SSB
	if (bcm47xx_bus_type ==	 BCM47XX_BUS_TYPE_SSB)
		wetuwn bcm47xx_pcibios_pwat_dev_init_ssb(dev);
#endif
#ifdef CONFIG_BCM47XX_BCMA
	if  (bcm47xx_bus_type ==  BCM47XX_BUS_TYPE_BCMA)
		wetuwn bcm47xx_pcibios_pwat_dev_init_bcma(dev);
#endif
	wetuwn 0;
}
