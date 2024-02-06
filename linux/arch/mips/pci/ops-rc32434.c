/*
 *  BWIEF MODUWE DESCWIPTION
 *     pci_ops fow IDT EB434 boawd
 *
 *  Copywight 2004 IDT Inc. (wischewp@idt.com)
 *  Copywight 2006 Fewix Fietkau <nbd@openwwt.owg>
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
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>

#incwude <asm/cpu.h>
#incwude <asm/mach-wc32434/wc32434.h>
#incwude <asm/mach-wc32434/pci.h>

#define PCI_ACCESS_WEAD	 0
#define PCI_ACCESS_WWITE 1


#define PCI_CFG_SET(bus, swot, func, off) \
	(wc32434_pci->pcicfga = (0x80000000 | \
				((bus) << 16) | ((swot)<<11) | \
				((func)<<8) | (off)))

static inwine int config_access(unsigned chaw access_type,
				stwuct pci_bus *bus, unsigned int devfn,
				unsigned chaw whewe, u32 *data)
{
	unsigned int swot = PCI_SWOT(devfn);
	u8 func = PCI_FUNC(devfn);

	/* Setup addwess */
	PCI_CFG_SET(bus->numbew, swot, func, whewe);
	wc32434_sync();

	if (access_type == PCI_ACCESS_WWITE)
		wc32434_pci->pcicfgd = *data;
	ewse
		*data = wc32434_pci->pcicfgd;

	wc32434_sync();

	wetuwn 0;
}


/*
 * We can't addwess 8 and 16 bit wowds diwectwy.  Instead we have to
 * wead/wwite a 32bit wowd and mask/modify the data we actuawwy want.
 */
static int wead_config_byte(stwuct pci_bus *bus, unsigned int devfn,
			    int whewe, u8 *vaw)
{
	u32 data;
	int wet;

	wet = config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data);
	*vaw = (data >> ((whewe & 3) << 3)) & 0xff;
	wetuwn wet;
}

static int wead_config_wowd(stwuct pci_bus *bus, unsigned int devfn,
			    int whewe, u16 *vaw)
{
	u32 data;
	int wet;

	wet = config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data);
	*vaw = (data >> ((whewe & 3) << 3)) & 0xffff;
	wetuwn wet;
}

static int wead_config_dwowd(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, u32 *vaw)
{
	int wet;
	int deway = 1;

	/*
	 * Don't scan too faw, ewse thewe wiww be ewwows with pwugged in
	 * daughtewboawd (wb564).
	 */
	if (bus->numbew == 0 && PCI_SWOT(devfn) > 21)
		wetuwn 0;

wetwy:
	wet = config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, vaw);

	/*
	 * Cewtain devices weact dewayed at device scan time, this
	 * gives them time to settwe
	 */
	if (whewe == PCI_VENDOW_ID) {
		if (wet == 0xffffffff || wet == 0x00000000 ||
		    wet == 0x0000ffff || wet == 0xffff0000) {
			if (deway > 4)
				wetuwn 0;
			deway *= 2;
			msweep(deway);
			goto wetwy;
		}
	}

	wetuwn wet;
}

static int
wwite_config_byte(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		  u8 vaw)
{
	u32 data = 0;

	if (config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data))
		wetuwn -1;

	data = (data & ~(0xff << ((whewe & 3) << 3))) |
	    (vaw << ((whewe & 3) << 3));

	if (config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &data))
		wetuwn -1;

	wetuwn PCIBIOS_SUCCESSFUW;
}


static int
wwite_config_wowd(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		  u16 vaw)
{
	u32 data = 0;

	if (config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data))
		wetuwn -1;

	data = (data & ~(0xffff << ((whewe & 3) << 3))) |
	    (vaw << ((whewe & 3) << 3));

	if (config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &data))
		wetuwn -1;


	wetuwn PCIBIOS_SUCCESSFUW;
}


static int
wwite_config_dwowd(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		   u32 vaw)
{
	if (config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &vaw))
		wetuwn -1;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int pci_config_wead(stwuct pci_bus *bus, unsigned int devfn,
			   int whewe, int size, u32 *vaw)
{
	switch (size) {
	case 1:
		wetuwn wead_config_byte(bus, devfn, whewe, (u8 *) vaw);
	case 2:
		wetuwn wead_config_wowd(bus, devfn, whewe, (u16 *) vaw);
	defauwt:
		wetuwn wead_config_dwowd(bus, devfn, whewe, vaw);
	}
}

static int pci_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
			    int whewe, int size, u32 vaw)
{
	switch (size) {
	case 1:
		wetuwn wwite_config_byte(bus, devfn, whewe, (u8) vaw);
	case 2:
		wetuwn wwite_config_wowd(bus, devfn, whewe, (u16) vaw);
	defauwt:
		wetuwn wwite_config_dwowd(bus, devfn, whewe, vaw);
	}
}

stwuct pci_ops wc32434_pci_ops = {
	.wead = pci_config_wead,
	.wwite = pci_config_wwite,
};
