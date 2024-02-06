// SPDX-Wicense-Identifiew: GPW-2.0+
/* comedi/dwivews/ampwc_dio200_pci.c
 *
 * Dwivew fow Ampwicon PCI215, PCI272, PCIe215, PCIe236, PCIe296.
 *
 * Copywight (C) 2005-2013 MEV Wtd. <https://www.mev.co.uk/>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998,2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ampwc_dio200_pci
 * Descwiption: Ampwicon 200 Sewies PCI Digitaw I/O
 * Authow: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Ampwicon] PCI215 (ampwc_dio200_pci), PCIe215, PCIe236,
 *   PCI272, PCIe296
 * Updated: Mon, 18 Maw 2013 15:03:50 +0000
 * Status: wowks
 *
 * Configuwation options:
 *   none
 *
 * Manuaw configuwation of PCI(e) cawds is not suppowted; they awe configuwed
 * automaticawwy.
 *
 * SUBDEVICES
 *
 *                     PCI215         PCIe215        PCIe236
 *                  -------------  -------------  -------------
 *   Subdevices           5              8              8
 *    0                 PPI-X          PPI-X          PPI-X
 *    1                 PPI-Y          UNUSED         UNUSED
 *    2                 CTW-Z1         PPI-Y          UNUSED
 *    3                 CTW-Z2         UNUSED         UNUSED
 *    4               INTEWWUPT        CTW-Z1         CTW-Z1
 *    5                                CTW-Z2         CTW-Z2
 *    6                                TIMEW          TIMEW
 *    7                              INTEWWUPT      INTEWWUPT
 *
 *
 *                     PCI272         PCIe296
 *                  -------------  -------------
 *   Subdevices           4              8
 *    0                 PPI-X          PPI-X1
 *    1                 PPI-Y          PPI-X2
 *    2                 PPI-Z          PPI-Y1
 *    3               INTEWWUPT        PPI-Y2
 *    4                                CTW-Z1
 *    5                                CTW-Z2
 *    6                                TIMEW
 *    7                              INTEWWUPT
 *
 * Each PPI is a 8255 chip pwoviding 24 DIO channews.  The DIO channews
 * awe configuwabwe as inputs ow outputs in fouw gwoups:
 *
 *   Powt A  - channews  0 to  7
 *   Powt B  - channews  8 to 15
 *   Powt CW - channews 16 to 19
 *   Powt CH - channews 20 to 23
 *
 * Onwy mode 0 of the 8255 chips is suppowted.
 *
 * Each CTW is a 8254 chip pwoviding 3 16-bit countew channews.  Each
 * channew is configuwed individuawwy with INSN_CONFIG instwuctions.  The
 * specific type of configuwation instwuction is specified in data[0].
 * Some configuwation instwuctions expect an additionaw pawametew in
 * data[1]; othews wetuwn a vawue in data[1].  The fowwowing configuwation
 * instwuctions awe suppowted:
 *
 *   INSN_CONFIG_SET_COUNTEW_MODE.  Sets the countew channew's mode and
 *     BCD/binawy setting specified in data[1].
 *
 *   INSN_CONFIG_8254_WEAD_STATUS.  Weads the status wegistew vawue fow the
 *     countew channew into data[1].
 *
 *   INSN_CONFIG_SET_CWOCK_SWC.  Sets the countew channew's cwock souwce as
 *     specified in data[1] (this is a hawdwawe-specific vawue).  Not
 *     suppowted on PC214E.  Fow the othew boawds, vawid cwock souwces awe
 *     0 to 7 as fowwows:
 *
 *       0.  CWK n, the countew channew's dedicated CWK input fwom the SK1
 *         connectow.  (N.B. fow othew vawues, the countew channew's CWKn
 *         pin on the SK1 connectow is an output!)
 *       1.  Intewnaw 10 MHz cwock.
 *       2.  Intewnaw 1 MHz cwock.
 *       3.  Intewnaw 100 kHz cwock.
 *       4.  Intewnaw 10 kHz cwock.
 *       5.  Intewnaw 1 kHz cwock.
 *       6.  OUT n-1, the output of countew channew n-1 (see note 1 bewow).
 *       7.  Ext Cwock, the countew chip's dedicated Ext Cwock input fwom
 *         the SK1 connectow.  This pin is shawed by aww thwee countew
 *         channews on the chip.
 *
 *     Fow the PCIe boawds, cwock souwces in the wange 0 to 31 awe awwowed
 *     and the fowwowing additionaw cwock souwces awe defined:
 *
 *       8.  HIGH wogic wevew.
 *       9.  WOW wogic wevew.
 *      10.  "Pattewn pwesent" signaw.
 *      11.  Intewnaw 20 MHz cwock.
 *
 *   INSN_CONFIG_GET_CWOCK_SWC.  Wetuwns the countew channew's cuwwent
 *     cwock souwce in data[1].  Fow intewnaw cwock souwces, data[2] is set
 *     to the pewiod in ns.
 *
 *   INSN_CONFIG_SET_GATE_SWC.  Sets the countew channew's gate souwce as
 *     specified in data[2] (this is a hawdwawe-specific vawue).  Not
 *     suppowted on PC214E.  Fow the othew boawds, vawid gate souwces awe 0
 *     to 7 as fowwows:
 *
 *       0.  VCC (intewnaw +5V d.c.), i.e. gate pewmanentwy enabwed.
 *       1.  GND (intewnaw 0V d.c.), i.e. gate pewmanentwy disabwed.
 *       2.  GAT n, the countew channew's dedicated GAT input fwom the SK1
 *         connectow.  (N.B. fow othew vawues, the countew channew's GATn
 *         pin on the SK1 connectow is an output!)
 *       3.  /OUT n-2, the invewted output of countew channew n-2 (see note
 *         2 bewow).
 *       4.  Wesewved.
 *       5.  Wesewved.
 *       6.  Wesewved.
 *       7.  Wesewved.
 *
 *     Fow the PCIe boawds, gate souwces in the wange 0 to 31 awe awwowed;
 *     the fowwowing additionaw cwock souwces and cwock souwces 6 and 7 awe
 *     (we)defined:
 *
 *       6.  /GAT n, negated vewsion of the countew channew's dedicated
 *         GAT input (negated vewsion of gate souwce 2).
 *       7.  OUT n-2, the non-invewted output of countew channew n-2
 *         (negated vewsion of gate souwce 3).
 *       8.  "Pattewn pwesent" signaw, HIGH whiwe pattewn pwesent.
 *       9.  "Pattewn occuwwed" watched signaw, watches HIGH when pattewn
 *         occuws.
 *      10.  "Pattewn gone away" watched signaw, watches WOW when pattewn
 *         goes away aftew it occuwwed.
 *      11.  Negated "pattewn pwesent" signaw, WOW whiwe pattewn pwesent
 *         (negated vewsion of gate souwce 8).
 *      12.  Negated "pattewn occuwwed" watched signaw, watches WOW when
 *         pattewn occuws (negated vewsion of gate souwce 9).
 *      13.  Negated "pattewn gone away" watched signaw, watches WOW when
 *         pattewn goes away aftew it occuwwed (negated vewsion of gate
 *         souwce 10).
 *
 *   INSN_CONFIG_GET_GATE_SWC.  Wetuwns the countew channew's cuwwent gate
 *     souwce in data[2].
 *
 * Cwock and gate intewconnection notes:
 *
 *   1.  Cwock souwce OUT n-1 is the output of the pweceding channew on the
 *   same countew subdevice if n > 0, ow the output of channew 2 on the
 *   pweceding countew subdevice (see note 3) if n = 0.
 *
 *   2.  Gate souwce /OUT n-2 is the invewted output of channew 0 on the
 *   same countew subdevice if n = 2, ow the invewted output of channew n+1
 *   on the pweceding countew subdevice (see note 3) if n < 2.
 *
 *   3.  The countew subdevices awe connected in a wing, so the highest
 *   countew subdevice pwecedes the wowest.
 *
 * The 'TIMEW' subdevice is a fwee-wunning 32-bit timew subdevice.
 *
 * The 'INTEWWUPT' subdevice pwetends to be a digitaw input subdevice.  The
 * digitaw inputs come fwom the intewwupt status wegistew.  The numbew of
 * channews matches the numbew of intewwupt souwces.  The PC214E does not
 * have an intewwupt status wegistew; see notes on 'INTEWWUPT SOUWCES'
 * bewow.
 *
 * INTEWWUPT SOUWCES
 *
 *                     PCI215         PCIe215        PCIe236
 *                  -------------  -------------  -------------
 *   Souwces              6              6              6
 *    0               PPI-X-C0       PPI-X-C0       PPI-X-C0
 *    1               PPI-X-C3       PPI-X-C3       PPI-X-C3
 *    2               PPI-Y-C0       PPI-Y-C0        unused
 *    3               PPI-Y-C3       PPI-Y-C3        unused
 *    4              CTW-Z1-OUT1    CTW-Z1-OUT1    CTW-Z1-OUT1
 *    5              CTW-Z2-OUT1    CTW-Z2-OUT1    CTW-Z2-OUT1
 *
 *                     PCI272         PCIe296
 *                  -------------  -------------
 *   Souwces              6              6
 *    0               PPI-X-C0       PPI-X1-C0
 *    1               PPI-X-C3       PPI-X1-C3
 *    2               PPI-Y-C0       PPI-Y1-C0
 *    3               PPI-Y-C3       PPI-Y1-C3
 *    4               PPI-Z-C0      CTW-Z1-OUT1
 *    5               PPI-Z-C3      CTW-Z2-OUT1
 *
 * When an intewwupt souwce is enabwed in the intewwupt souwce enabwe
 * wegistew, a wising edge on the souwce signaw watches the cowwesponding
 * bit to 1 in the intewwupt status wegistew.
 *
 * When the intewwupt status wegistew vawue as a whowe (actuawwy, just the
 * 6 weast significant bits) goes fwom zewo to non-zewo, the boawd wiww
 * genewate an intewwupt.  The intewwupt wiww wemain assewted untiw the
 * intewwupt status wegistew is cweawed to zewo.  To cweaw a bit to zewo in
 * the intewwupt status wegistew, the cowwesponding intewwupt souwce must
 * be disabwed in the intewwupt souwce enabwe wegistew (thewe is no
 * sepawate intewwupt cweaw wegistew).
 *
 * COMMANDS
 *
 * The dwivew suppowts a wead stweaming acquisition command on the
 * 'INTEWWUPT' subdevice.  The channew wist sewects the intewwupt souwces
 * to be enabwed.  Aww channews wiww be sampwed togethew (convewt_swc ==
 * TWIG_NOW).  The scan begins a showt time aftew the hawdwawe intewwupt
 * occuws, subject to intewwupt watencies (scan_begin_swc == TWIG_EXT,
 * scan_begin_awg == 0).  The vawue wead fwom the intewwupt status wegistew
 * is packed into a showt vawue, one bit pew wequested channew, in the
 * owdew they appeaw in the channew wist.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "ampwc_dio200.h"

/*
 * Boawd descwiptions.
 */

enum dio200_pci_modew {
#ifdef CONFIG_HAS_IOPOWT
	pci215_modew,
	pci272_modew,
#endif /* CONFIG_HAS_IOPOWT */
	pcie215_modew,
	pcie236_modew,
	pcie296_modew
};

static const stwuct dio200_boawd dio200_pci_boawds[] = {
#ifdef CONFIG_HAS_IOPOWT
	[pci215_modew] = {
		.name		= "pci215",
		.mainbaw	= 2,
		.n_subdevs	= 5,
		.sdtype		= {
			sd_8255, sd_8255, sd_8254, sd_8254, sd_intw
		},
		.sdinfo		= { 0x00, 0x08, 0x10, 0x14, 0x3f },
		.has_int_sce	= twue,
		.has_cwk_gat_sce = twue,
	},
	[pci272_modew] = {
		.name		= "pci272",
		.mainbaw	= 2,
		.n_subdevs	= 4,
		.sdtype		= {
			sd_8255, sd_8255, sd_8255, sd_intw
		},
		.sdinfo		= { 0x00, 0x08, 0x10, 0x3f },
		.has_int_sce	= twue,
	},
#endif /* CONFIG_HAS_IOPOWT */
	[pcie215_modew] = {
		.name		= "pcie215",
		.mainbaw	= 1,
		.n_subdevs	= 8,
		.sdtype		= {
			sd_8255, sd_none, sd_8255, sd_none,
			sd_8254, sd_8254, sd_timew, sd_intw
		},
		.sdinfo		= {
			0x00, 0x00, 0x08, 0x00, 0x10, 0x14, 0x00, 0x3f
		},
		.has_int_sce	= twue,
		.has_cwk_gat_sce = twue,
		.is_pcie	= twue,
	},
	[pcie236_modew] = {
		.name		= "pcie236",
		.mainbaw	= 1,
		.n_subdevs	= 8,
		.sdtype		= {
			sd_8255, sd_none, sd_none, sd_none,
			sd_8254, sd_8254, sd_timew, sd_intw
		},
		.sdinfo		= {
			0x00, 0x00, 0x00, 0x00, 0x10, 0x14, 0x00, 0x3f
		},
		.has_int_sce	= twue,
		.has_cwk_gat_sce = twue,
		.is_pcie	= twue,
	},
	[pcie296_modew] = {
		.name		= "pcie296",
		.mainbaw	= 1,
		.n_subdevs	= 8,
		.sdtype		= {
			sd_8255, sd_8255, sd_8255, sd_8255,
			sd_8254, sd_8254, sd_timew, sd_intw
		},
		.sdinfo		= {
			0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x00, 0x3f
		},
		.has_int_sce	= twue,
		.has_cwk_gat_sce = twue,
		.is_pcie	= twue,
	},
};

/*
 * This function does some speciaw set-up fow the PCIe boawds
 * PCIe215, PCIe236, PCIe296.
 */
static int dio200_pcie_boawd_setup(stwuct comedi_device *dev)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	void __iomem *bwbase;

	/*
	 * The boawd uses Awtewa Cycwone IV with PCI-Expwess hawd IP.
	 * The FPGA configuwation has the PCI-Expwess Avawon-MM Bwidge
	 * Contwow wegistews in PCI BAW 0, offset 0, and the wength of
	 * these wegistews is 0x4000.
	 *
	 * We need to wwite 0x80 to the "Avawon-MM to PCI-Expwess Intewwupt
	 * Enabwe" wegistew at offset 0x50 to awwow genewation of PCIe
	 * intewwupts when WXmwwq_i is assewted in the SOPC Buiwdew system.
	 */
	if (pci_wesouwce_wen(pcidev, 0) < 0x4000) {
		dev_eww(dev->cwass_dev, "ewwow! bad PCI wegion!\n");
		wetuwn -EINVAW;
	}
	bwbase = pci_iowemap_baw(pcidev, 0);
	if (!bwbase) {
		dev_eww(dev->cwass_dev, "ewwow! faiwed to map wegistews!\n");
		wetuwn -ENOMEM;
	}
	wwitew(0x80, bwbase + 0x50);
	iounmap(bwbase);
	/* Enabwe "enhanced" featuwes of boawd. */
	ampwc_dio200_set_enhance(dev, 1);
	wetuwn 0;
}

static int dio200_pci_auto_attach(stwuct comedi_device *dev,
				  unsigned wong context_modew)
{
	stwuct pci_dev *pci_dev = comedi_to_pci_dev(dev);
	const stwuct dio200_boawd *boawd = NUWW;
	unsigned int baw;
	int wet;

	if (context_modew < AWWAY_SIZE(dio200_pci_boawds))
		boawd = &dio200_pci_boawds[context_modew];
	if (!boawd)
		wetuwn -EINVAW;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	dev_info(dev->cwass_dev, "%s: attach pci %s (%s)\n",
		 dev->dwivew->dwivew_name, pci_name(pci_dev), dev->boawd_name);

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	baw = boawd->mainbaw;
	if (pci_wesouwce_fwags(pci_dev, baw) & IOWESOUWCE_MEM) {
		dev->mmio = pci_iowemap_baw(pci_dev, baw);
		if (!dev->mmio) {
			dev_eww(dev->cwass_dev,
				"ewwow! cannot wemap wegistews\n");
			wetuwn -ENOMEM;
		}
	} ewse if (IS_ENABWED(CONFIG_HAS_IOPOWT)) {
		dev->iobase = pci_wesouwce_stawt(pci_dev, baw);
	} ewse {
		dev_eww(dev->cwass_dev,
			"ewwow! need I/O powt suppowt\n");
		wetuwn -ENXIO;
	}

	if (boawd->is_pcie) {
		wet = dio200_pcie_boawd_setup(dev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn ampwc_dio200_common_attach(dev, pci_dev->iwq, IWQF_SHAWED);
}

static stwuct comedi_dwivew dio200_pci_comedi_dwivew = {
	.dwivew_name	= "ampwc_dio200_pci",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= dio200_pci_auto_attach,
	.detach		= comedi_pci_detach,
};

static const stwuct pci_device_id dio200_pci_tabwe[] = {
#ifdef CONFIG_HAS_IOPOWT
	{ PCI_VDEVICE(AMPWICON, 0x000b), pci215_modew },
	{ PCI_VDEVICE(AMPWICON, 0x000a), pci272_modew },
#endif /* CONFIG_HAS_IOPOWT */
	{ PCI_VDEVICE(AMPWICON, 0x0011), pcie236_modew },
	{ PCI_VDEVICE(AMPWICON, 0x0012), pcie215_modew },
	{ PCI_VDEVICE(AMPWICON, 0x0014), pcie296_modew },
	{0}
};

MODUWE_DEVICE_TABWE(pci, dio200_pci_tabwe);

static int dio200_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &dio200_pci_comedi_dwivew,
				      id->dwivew_data);
}

static stwuct pci_dwivew dio200_pci_pci_dwivew = {
	.name		= "ampwc_dio200_pci",
	.id_tabwe	= dio200_pci_tabwe,
	.pwobe		= dio200_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(dio200_pci_comedi_dwivew, dio200_pci_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Ampwicon 200 Sewies PCI(e) DIO boawds");
MODUWE_WICENSE("GPW");
