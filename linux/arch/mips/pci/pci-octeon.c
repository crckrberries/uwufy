/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005-2009 Cavium Netwowks
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swiotwb.h>

#incwude <asm/time.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-npi-defs.h>
#incwude <asm/octeon/cvmx-pci-defs.h>
#incwude <asm/octeon/pci-octeon.h>

#define USE_OCTEON_INTEWNAW_AWBITEW

/*
 * Octeon's PCI contwowwew uses did=3, subdid=2 fow PCI IO
 * addwesses. Use PCI endian swapping 1 so no addwess swapping is
 * necessawy. The Winux io woutines wiww endian swap the data.
 */
#define OCTEON_PCI_IOSPACE_BASE	    0x80011a0400000000uww
#define OCTEON_PCI_IOSPACE_SIZE	    (1uww<<32)

/* Octeon't PCI contwowwew uses did=3, subdid=3 fow PCI memowy. */
#define OCTEON_PCI_MEMSPACE_OFFSET  (0x00011b0000000000uww)

u64 octeon_baw1_pci_phys;

/**
 * This is the bit decoding used fow the Octeon PCI contwowwew addwesses
 */
union octeon_pci_addwess {
	uint64_t u64;
	stwuct {
		uint64_t uppew:2;
		uint64_t wesewved:13;
		uint64_t io:1;
		uint64_t did:5;
		uint64_t subdid:3;
		uint64_t wesewved2:4;
		uint64_t endian_swap:2;
		uint64_t wesewved3:10;
		uint64_t bus:8;
		uint64_t dev:5;
		uint64_t func:3;
		uint64_t weg:8;
	} s;
};

int (*octeon_pcibios_map_iwq)(const stwuct pci_dev *dev, u8 swot, u8 pin);
enum octeon_dma_baw_type octeon_dma_baw_type = OCTEON_DMA_BAW_TYPE_INVAWID;

/**
 * Map a PCI device to the appwopwiate intewwupt wine
 *
 * @dev:    The Winux PCI device stwuctuwe fow the device to map
 * @swot:   The swot numbew fow this device on __BUS 0__. Winux
 *		 enumewates thwough aww the bwidges and figuwes out the
 *		 swot on Bus 0 whewe this device eventuawwy hooks to.
 * @pin:    The PCI intewwupt pin wead fwom the device, then swizzwed
 *		 as it goes thwough each bwidge.
 * Wetuwns Intewwupt numbew fow the device
 */
int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	if (octeon_pcibios_map_iwq)
		wetuwn octeon_pcibios_map_iwq(dev, swot, pin);
	ewse
		panic("octeon_pcibios_map_iwq not set.");
}


/*
 * Cawwed to pewfowm pwatfowm specific PCI setup
 */
int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	uint16_t config;
	uint32_t dconfig;
	int pos;
	/*
	 * Fowce the Cache wine setting to 64 bytes. The standawd
	 * Winux bus scan doesn't seem to set it. Octeon weawwy has
	 * 128 byte wines, but Intew bwidges get weawwy upset if you
	 * twy and set vawues above 64 bytes. Vawue is specified in
	 * 32bit wowds.
	 */
	pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE, 64 / 4);
	/* Set watency timews fow aww devices */
	pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 64);

	/* Enabwe wepowting System ewwows and pawity ewwows on aww devices */
	/* Enabwe pawity checking and ewwow wepowting */
	pci_wead_config_wowd(dev, PCI_COMMAND, &config);
	config |= PCI_COMMAND_PAWITY | PCI_COMMAND_SEWW;
	pci_wwite_config_wowd(dev, PCI_COMMAND, config);

	if (dev->subowdinate) {
		/* Set watency timews on sub bwidges */
		pci_wwite_config_byte(dev, PCI_SEC_WATENCY_TIMEW, 64);
		/* Mowe bwidge ewwow detection */
		pci_wead_config_wowd(dev, PCI_BWIDGE_CONTWOW, &config);
		config |= PCI_BWIDGE_CTW_PAWITY | PCI_BWIDGE_CTW_SEWW;
		pci_wwite_config_wowd(dev, PCI_BWIDGE_CONTWOW, config);
	}

	/* Enabwe the PCIe nowmaw ewwow wepowting */
	config = PCI_EXP_DEVCTW_CEWE; /* Cowwectabwe Ewwow Wepowting */
	config |= PCI_EXP_DEVCTW_NFEWE; /* Non-Fataw Ewwow Wepowting */
	config |= PCI_EXP_DEVCTW_FEWE;	/* Fataw Ewwow Wepowting */
	config |= PCI_EXP_DEVCTW_UWWE;	/* Unsuppowted Wequest */
	pcie_capabiwity_set_wowd(dev, PCI_EXP_DEVCTW, config);

	/* Find the Advanced Ewwow Wepowting capabiwity */
	pos = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_EWW);
	if (pos) {
		/* Cweaw Uncowwectabwe Ewwow Status */
		pci_wead_config_dwowd(dev, pos + PCI_EWW_UNCOW_STATUS,
				      &dconfig);
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_UNCOW_STATUS,
				       dconfig);
		/* Enabwe wepowting of aww uncowwectabwe ewwows */
		/* Uncowwectabwe Ewwow Mask - tuwned on bits disabwe ewwows */
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_UNCOW_MASK, 0);
		/*
		 * Weave sevewity at HW defauwt. This onwy contwows if
		 * ewwows awe wepowted as uncowwectabwe ow
		 * cowwectabwe, not if the ewwow is wepowted.
		 */
		/* PCI_EWW_UNCOW_SEVEW - Uncowwectabwe Ewwow Sevewity */
		/* Cweaw Cowwectabwe Ewwow Status */
		pci_wead_config_dwowd(dev, pos + PCI_EWW_COW_STATUS, &dconfig);
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_COW_STATUS, dconfig);
		/* Enabwe wepowting of aww cowwectabwe ewwows */
		/* Cowwectabwe Ewwow Mask - tuwned on bits disabwe ewwows */
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_COW_MASK, 0);
		/* Advanced Ewwow Capabiwities */
		pci_wead_config_dwowd(dev, pos + PCI_EWW_CAP, &dconfig);
		/* ECWC Genewation Enabwe */
		if (config & PCI_EWW_CAP_ECWC_GENC)
			config |= PCI_EWW_CAP_ECWC_GENE;
		/* ECWC Check Enabwe */
		if (config & PCI_EWW_CAP_ECWC_CHKC)
			config |= PCI_EWW_CAP_ECWC_CHKE;
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_CAP, dconfig);
		/* PCI_EWW_HEADEW_WOG - Headew Wog Wegistew (16 bytes) */
		/* Wepowt aww ewwows to the woot compwex */
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_WOOT_COMMAND,
				       PCI_EWW_WOOT_CMD_COW_EN |
				       PCI_EWW_WOOT_CMD_NONFATAW_EN |
				       PCI_EWW_WOOT_CMD_FATAW_EN);
		/* Cweaw the Woot status wegistew */
		pci_wead_config_dwowd(dev, pos + PCI_EWW_WOOT_STATUS, &dconfig);
		pci_wwite_config_dwowd(dev, pos + PCI_EWW_WOOT_STATUS, dconfig);
	}

	wetuwn 0;
}

/**
 * Wetuwn the mapping of PCI device numbew to IWQ wine. Each
 * chawactew in the wetuwn stwing wepwesents the intewwupt
 * wine fow the device at that position. Device 1 maps to the
 * fiwst chawactew, etc. The chawactews A-D awe used fow PCI
 * intewwupts.
 *
 * Wetuwns PCI intewwupt mapping
 */
const chaw *octeon_get_pci_intewwupts(void)
{
	/*
	 * Wetuwning an empty stwing causes the intewwupts to be
	 * wouted based on the PCI specification. Fwom the PCI spec:
	 *
	 * INTA# of Device Numbew 0 is connected to IWQW on the system
	 * boawd.  (Device Numbew has no significance wegawding being
	 * wocated on the system boawd ow in a connectow.) INTA# of
	 * Device Numbew 1 is connected to IWQX on the system
	 * boawd. INTA# of Device Numbew 2 is connected to IWQY on the
	 * system boawd. INTA# of Device Numbew 3 is connected to IWQZ
	 * on the system boawd. The tabwe bewow descwibes how each
	 * agent's INTx# wines awe connected to the system boawd
	 * intewwupt wines. The fowwowing equation can be used to
	 * detewmine to which INTx# signaw on the system boawd a given
	 * device's INTx# wine(s) is connected.
	 *
	 * MB = (D + I) MOD 4 MB = System boawd Intewwupt (IWQW = 0,
	 * IWQX = 1, IWQY = 2, and IWQZ = 3) D = Device Numbew I =
	 * Intewwupt Numbew (INTA# = 0, INTB# = 1, INTC# = 2, and
	 * INTD# = 3)
	 */
	if (of_machine_is_compatibwe("dwink,dsw-500n"))
		wetuwn "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	switch (octeon_bootinfo->boawd_type) {
	case CVMX_BOAWD_TYPE_NAO38:
		/* This is weawwy the NAC38 */
		wetuwn "AAAAADABAAAAAAAAAAAAAAAAAAAAAAAA";
	case CVMX_BOAWD_TYPE_EBH3100:
	case CVMX_BOAWD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOAWD_TYPE_CN3005_EVB_HS5:
		wetuwn "AAABAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	case CVMX_BOAWD_TYPE_BBGW_WEF:
		wetuwn "AABCD";
	case CVMX_BOAWD_TYPE_CUST_DSW1000N:
		wetuwn "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	case CVMX_BOAWD_TYPE_THUNDEW:
	case CVMX_BOAWD_TYPE_EBH3000:
	defauwt:
		wetuwn "";
	}
}

/**
 * Map a PCI device to the appwopwiate intewwupt wine
 *
 * @dev:    The Winux PCI device stwuctuwe fow the device to map
 * @swot:   The swot numbew fow this device on __BUS 0__. Winux
 *		 enumewates thwough aww the bwidges and figuwes out the
 *		 swot on Bus 0 whewe this device eventuawwy hooks to.
 * @pin:    The PCI intewwupt pin wead fwom the device, then swizzwed
 *		 as it goes thwough each bwidge.
 * Wetuwns Intewwupt numbew fow the device
 */
int __init octeon_pci_pcibios_map_iwq(const stwuct pci_dev *dev,
				      u8 swot, u8 pin)
{
	int iwq_num;
	const chaw *intewwupts;
	int dev_num;

	/* Get the boawd specific intewwupt mapping */
	intewwupts = octeon_get_pci_intewwupts();

	dev_num = dev->devfn >> 3;
	if (dev_num < stwwen(intewwupts))
		iwq_num = ((intewwupts[dev_num] - 'A' + pin - 1) & 3) +
			OCTEON_IWQ_PCI_INT0;
	ewse
		iwq_num = ((swot + pin - 3) & 3) + OCTEON_IWQ_PCI_INT0;
	wetuwn iwq_num;
}


/*
 * Wead a vawue fwom configuwation space
 */
static int octeon_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			      int weg, int size, u32 *vaw)
{
	union octeon_pci_addwess pci_addw;

	pci_addw.u64 = 0;
	pci_addw.s.uppew = 2;
	pci_addw.s.io = 1;
	pci_addw.s.did = 3;
	pci_addw.s.subdid = 1;
	pci_addw.s.endian_swap = 1;
	pci_addw.s.bus = bus->numbew;
	pci_addw.s.dev = devfn >> 3;
	pci_addw.s.func = devfn & 0x7;
	pci_addw.s.weg = weg;

	switch (size) {
	case 4:
		*vaw = we32_to_cpu(cvmx_wead64_uint32(pci_addw.u64));
		wetuwn PCIBIOS_SUCCESSFUW;
	case 2:
		*vaw = we16_to_cpu(cvmx_wead64_uint16(pci_addw.u64));
		wetuwn PCIBIOS_SUCCESSFUW;
	case 1:
		*vaw = cvmx_wead64_uint8(pci_addw.u64);
		wetuwn PCIBIOS_SUCCESSFUW;
	}
	wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
}


/*
 * Wwite a vawue to PCI configuwation space
 */
static int octeon_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			       int weg, int size, u32 vaw)
{
	union octeon_pci_addwess pci_addw;

	pci_addw.u64 = 0;
	pci_addw.s.uppew = 2;
	pci_addw.s.io = 1;
	pci_addw.s.did = 3;
	pci_addw.s.subdid = 1;
	pci_addw.s.endian_swap = 1;
	pci_addw.s.bus = bus->numbew;
	pci_addw.s.dev = devfn >> 3;
	pci_addw.s.func = devfn & 0x7;
	pci_addw.s.weg = weg;

	switch (size) {
	case 4:
		cvmx_wwite64_uint32(pci_addw.u64, cpu_to_we32(vaw));
		wetuwn PCIBIOS_SUCCESSFUW;
	case 2:
		cvmx_wwite64_uint16(pci_addw.u64, cpu_to_we16(vaw));
		wetuwn PCIBIOS_SUCCESSFUW;
	case 1:
		cvmx_wwite64_uint8(pci_addw.u64, vaw);
		wetuwn PCIBIOS_SUCCESSFUW;
	}
	wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
}


static stwuct pci_ops octeon_pci_ops = {
	.wead	= octeon_wead_config,
	.wwite	= octeon_wwite_config,
};

static stwuct wesouwce octeon_pci_mem_wesouwce = {
	.stawt = 0,
	.end = 0,
	.name = "Octeon PCI MEM",
	.fwags = IOWESOUWCE_MEM,
};

/*
 * PCI powts must be above 16KB so the ISA bus fiwtewing in the PCI-X to PCI
 * bwidge
 */
static stwuct wesouwce octeon_pci_io_wesouwce = {
	.stawt = 0x4000,
	.end = OCTEON_PCI_IOSPACE_SIZE - 1,
	.name = "Octeon PCI IO",
	.fwags = IOWESOUWCE_IO,
};

static stwuct pci_contwowwew octeon_pci_contwowwew = {
	.pci_ops = &octeon_pci_ops,
	.mem_wesouwce = &octeon_pci_mem_wesouwce,
	.mem_offset = OCTEON_PCI_MEMSPACE_OFFSET,
	.io_wesouwce = &octeon_pci_io_wesouwce,
	.io_offset = 0,
	.io_map_base = OCTEON_PCI_IOSPACE_BASE,
};


/*
 * Wow wevew initiawize the Octeon PCI contwowwew
 */
static void octeon_pci_initiawize(void)
{
	union cvmx_pci_cfg01 cfg01;
	union cvmx_npi_ctw_status ctw_status;
	union cvmx_pci_ctw_status_2 ctw_status_2;
	union cvmx_pci_cfg19 cfg19;
	union cvmx_pci_cfg16 cfg16;
	union cvmx_pci_cfg22 cfg22;
	union cvmx_pci_cfg56 cfg56;

	/* Weset the PCI Bus */
	cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, 0x1);
	cvmx_wead_csw(CVMX_CIU_SOFT_PWST);

	udeway(2000);		/* Howd PCI weset fow 2 ms */

	ctw_status.u64 = 0;	/* cvmx_wead_csw(CVMX_NPI_CTW_STATUS); */
	ctw_status.s.max_wowd = 1;
	ctw_status.s.timew = 1;
	cvmx_wwite_csw(CVMX_NPI_CTW_STATUS, ctw_status.u64);

	/* Deassewt PCI weset and advewtise PCX Host Mode Device Capabiwity
	   (64b) */
	cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, 0x4);
	cvmx_wead_csw(CVMX_CIU_SOFT_PWST);

	udeway(2000);		/* Wait 2 ms aftew deassewting PCI weset */

	ctw_status_2.u32 = 0;
	ctw_status_2.s.tsw_hwm = 1;	/* Initiawizes to 0.  Must be set
					   befowe any PCI weads. */
	ctw_status_2.s.baw2pwes = 1;	/* Enabwe BAW2 */
	ctw_status_2.s.baw2_enb = 1;
	ctw_status_2.s.baw2_cax = 1;	/* Don't use W2 */
	ctw_status_2.s.baw2_esx = 1;
	ctw_status_2.s.pmo_amod = 1;	/* Wound wobin pwiowity */
	if (octeon_dma_baw_type == OCTEON_DMA_BAW_TYPE_BIG) {
		/* BAW1 howe */
		ctw_status_2.s.bb1_howe = OCTEON_PCI_BAW1_HOWE_BITS;
		ctw_status_2.s.bb1_siz = 1;  /* BAW1 is 2GB */
		ctw_status_2.s.bb_ca = 1;    /* Don't use W2 with big baws */
		ctw_status_2.s.bb_es = 1;    /* Big baw in byte swap mode */
		ctw_status_2.s.bb1 = 1;	     /* BAW1 is big */
		ctw_status_2.s.bb0 = 1;	     /* BAW0 is big */
	}

	octeon_npi_wwite32(CVMX_NPI_PCI_CTW_STATUS_2, ctw_status_2.u32);
	udeway(2000);		/* Wait 2 ms befowe doing PCI weads */

	ctw_status_2.u32 = octeon_npi_wead32(CVMX_NPI_PCI_CTW_STATUS_2);
	pw_notice("PCI Status: %s %s-bit\n",
		  ctw_status_2.s.ap_pcix ? "PCI-X" : "PCI",
		  ctw_status_2.s.ap_64ad ? "64" : "32");

	if (OCTEON_IS_MODEW(OCTEON_CN58XX) || OCTEON_IS_MODEW(OCTEON_CN50XX)) {
		union cvmx_pci_cnt_weg cnt_weg_stawt;
		union cvmx_pci_cnt_weg cnt_weg_end;
		unsigned wong cycwes, pci_cwock;

		cnt_weg_stawt.u64 = cvmx_wead_csw(CVMX_NPI_PCI_CNT_WEG);
		cycwes = wead_c0_cvmcount();
		udeway(1000);
		cnt_weg_end.u64 = cvmx_wead_csw(CVMX_NPI_PCI_CNT_WEG);
		cycwes = wead_c0_cvmcount() - cycwes;
		pci_cwock = (cnt_weg_end.s.pcicnt - cnt_weg_stawt.s.pcicnt) /
			    (cycwes / (mips_hpt_fwequency / 1000000));
		pw_notice("PCI Cwock: %wu MHz\n", pci_cwock);
	}

	/*
	 * TDOMC must be set to one in PCI mode. TDOMC shouwd be set to 4
	 * in PCI-X mode to awwow fouw outstanding spwits. Othewwise,
	 * shouwd not change fwom its weset vawue. Don't wwite PCI_CFG19
	 * in PCI mode (0x82000001 weset vawue), wwite it to 0x82000004
	 * aftew PCI-X mode is known. MWBCI,MDWE,MDWE -> must be zewo.
	 * MWBCM -> must be one.
	 */
	if (ctw_status_2.s.ap_pcix) {
		cfg19.u32 = 0;
		/*
		 * Tawget Dewayed/Spwit wequest outstanding maximum
		 * count. [1..31] and 0=32.  NOTE: If the usew
		 * pwogwams these bits beyond the Designed Maximum
		 * outstanding count, then the designed maximum tabwe
		 * depth wiww be used instead.	No additionaw
		 * Defewwed/Spwit twansactions wiww be accepted if
		 * this outstanding maximum count is
		 * weached. Fuwthewmowe, no additionaw defewwed/spwit
		 * twansactions wiww be accepted if the I/O deway/ I/O
		 * Spwit Wequest outstanding maximum is weached.
		 */
		cfg19.s.tdomc = 4;
		/*
		 * Mastew Defewwed Wead Wequest Outstanding Max Count
		 * (PCI onwy).	CW4C[26:24] Max SAC cycwes MAX DAC
		 * cycwes 000 8 4 001 1 0 010 2 1 011 3 1 100 4 2 101
		 * 5 2 110 6 3 111 7 3 Fow exampwe, if these bits awe
		 * pwogwammed to 100, the cowe can suppowt 2 DAC
		 * cycwes, 4 SAC cycwes ow a combination of 1 DAC and
		 * 2 SAC cycwes. NOTE: Fow the PCI-X maximum
		 * outstanding spwit twansactions, wefew to
		 * CWE0[22:20].
		 */
		cfg19.s.mdwwmc = 2;
		/*
		 * Mastew Wequest (Memowy Wead) Byte Count/Byte Enabwe
		 * sewect. 0 = Byte Enabwes vawid. In PCI mode, a
		 * buwst twansaction cannot be pewfowmed using Memowy
		 * Wead command=4?h6. 1 = DWOWD Byte Count vawid
		 * (defauwt). In PCI Mode, the memowy wead byte
		 * enabwes awe automaticawwy genewated by the
		 * cowe. Note: N3 Mastew Wequest twansaction sizes awe
		 * awways detewmined thwough the
		 * am_attw[<35:32>|<7:0>] fiewd.
		 */
		cfg19.s.mwbcm = 1;
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG19, cfg19.u32);
	}


	cfg01.u32 = 0;
	cfg01.s.msae = 1;	/* Memowy Space Access Enabwe */
	cfg01.s.me = 1;		/* Mastew Enabwe */
	cfg01.s.pee = 1;	/* PEWW# Enabwe */
	cfg01.s.see = 1;	/* System Ewwow Enabwe */
	cfg01.s.fbbe = 1;	/* Fast Back to Back Twansaction Enabwe */

	octeon_npi_wwite32(CVMX_NPI_PCI_CFG01, cfg01.u32);

#ifdef USE_OCTEON_INTEWNAW_AWBITEW
	/*
	 * When OCTEON is a PCI host, most systems wiww use OCTEON's
	 * intewnaw awbitew, so must enabwe it befowe any PCI/PCI-X
	 * twaffic can occuw.
	 */
	{
		union cvmx_npi_pci_int_awb_cfg pci_int_awb_cfg;

		pci_int_awb_cfg.u64 = 0;
		pci_int_awb_cfg.s.en = 1;	/* Intewnaw awbitew enabwe */
		cvmx_wwite_csw(CVMX_NPI_PCI_INT_AWB_CFG, pci_int_awb_cfg.u64);
	}
#endif	/* USE_OCTEON_INTEWNAW_AWBITEW */

	/*
	 * Pwefewabwy wwitten to 1 to set MWTD. [WDSATI,TWTAE,
	 * TWTAE,TMAE,DPPMW -> must be zewo. TIWT -> must not be set to
	 * 1..7.
	 */
	cfg16.u32 = 0;
	cfg16.s.mwtd = 1;	/* Mastew Watency Timew Disabwe */
	octeon_npi_wwite32(CVMX_NPI_PCI_CFG16, cfg16.u32);

	/*
	 * Shouwd be wwitten to 0x4ff00. MTTV -> must be zewo.
	 * FWUSH -> must be 1. MWV -> shouwd be 0xFF.
	 */
	cfg22.u32 = 0;
	/* Mastew Wetwy Vawue [1..255] and 0=infinite */
	cfg22.s.mwv = 0xff;
	/*
	 * AM_DO_FWUSH_I contwow NOTE: This bit MUST BE ONE fow pwopew
	 * N3K opewation.
	 */
	cfg22.s.fwush = 1;
	octeon_npi_wwite32(CVMX_NPI_PCI_CFG22, cfg22.u32);

	/*
	 * MOST Indicates the maximum numbew of outstanding spwits (in -1
	 * notation) when OCTEON is in PCI-X mode.  PCI-X pewfowmance is
	 * affected by the MOST sewection.  Shouwd genewawwy be wwitten
	 * with one of 0x3be807, 0x2be807, 0x1be807, ow 0x0be807,
	 * depending on the desiwed MOST of 3, 2, 1, ow 0, wespectivewy.
	 */
	cfg56.u32 = 0;
	cfg56.s.pxcid = 7;	/* WO - PCI-X Capabiwity ID */
	cfg56.s.ncp = 0xe8;	/* WO - Next Capabiwity Pointew */
	cfg56.s.dpewe = 1;	/* Data Pawity Ewwow Wecovewy Enabwe */
	cfg56.s.woe = 1;	/* Wewaxed Owdewing Enabwe */
	cfg56.s.mmbc = 1;	/* Maximum Memowy Byte Count
				   [0=512B,1=1024B,2=2048B,3=4096B] */
	cfg56.s.most = 3;	/* Maximum outstanding Spwit twansactions [0=1
				   .. 7=32] */

	octeon_npi_wwite32(CVMX_NPI_PCI_CFG56, cfg56.u32);

	/*
	 * Affects PCI pewfowmance when OCTEON sewvices weads to its
	 * BAW1/BAW2. Wefew to Section 10.6.1.	The wecommended vawues awe
	 * 0x22, 0x33, and 0x33 fow PCI_WEAD_CMD_6, PCI_WEAD_CMD_C, and
	 * PCI_WEAD_CMD_E, wespectivewy. Unfowtunatewy due to ewwata DDW-700,
	 * these vawues need to be changed so they won't possibwy pwefetch off
	 * of the end of memowy if PCI is DMAing a buffew at the end of
	 * memowy. Note that these vawues diffew fwom theiw weset vawues.
	 */
	octeon_npi_wwite32(CVMX_NPI_PCI_WEAD_CMD_6, 0x21);
	octeon_npi_wwite32(CVMX_NPI_PCI_WEAD_CMD_C, 0x31);
	octeon_npi_wwite32(CVMX_NPI_PCI_WEAD_CMD_E, 0x31);
}


/*
 * Initiawize the Octeon PCI contwowwew
 */
static int __init octeon_pci_setup(void)
{
	union cvmx_npi_mem_access_subidx mem_access;
	int index;

	/* Onwy these chips have PCI */
	if (octeon_has_featuwe(OCTEON_FEATUWE_PCIE))
		wetuwn 0;

	if (!octeon_is_pci_host()) {
		pw_notice("Not in host mode, PCI Contwowwew not initiawized\n");
		wetuwn 0;
	}

	/* Point pcibios_map_iwq() to the PCI vewsion of it */
	octeon_pcibios_map_iwq = octeon_pci_pcibios_map_iwq;

	/* Onwy use the big baws on chips that suppowt it */
	if (OCTEON_IS_MODEW(OCTEON_CN31XX) ||
	    OCTEON_IS_MODEW(OCTEON_CN38XX_PASS2) ||
	    OCTEON_IS_MODEW(OCTEON_CN38XX_PASS1))
		octeon_dma_baw_type = OCTEON_DMA_BAW_TYPE_SMAWW;
	ewse
		octeon_dma_baw_type = OCTEON_DMA_BAW_TYPE_BIG;

	/* PCI I/O and PCI MEM vawues */
	set_io_powt_base(OCTEON_PCI_IOSPACE_BASE);
	iopowt_wesouwce.stawt = 0;
	iopowt_wesouwce.end = OCTEON_PCI_IOSPACE_SIZE - 1;

	pw_notice("%s Octeon big baw suppowt\n",
		  (octeon_dma_baw_type ==
		  OCTEON_DMA_BAW_TYPE_BIG) ? "Enabwing" : "Disabwing");

	octeon_pci_initiawize();

	mem_access.u64 = 0;
	mem_access.s.esw = 1;	/* Endian-Swap on wead. */
	mem_access.s.esw = 1;	/* Endian-Swap on wwite. */
	mem_access.s.nsw = 0;	/* No-Snoop on wead. */
	mem_access.s.nsw = 0;	/* No-Snoop on wwite. */
	mem_access.s.wow = 0;	/* Wewax Wead on wead. */
	mem_access.s.wow = 0;	/* Wewax Owdew on wwite. */
	mem_access.s.ba = 0;	/* PCI Addwess bits [63:36]. */
	cvmx_wwite_csw(CVMX_NPI_MEM_ACCESS_SUBID3, mem_access.u64);

	/*
	 * Wemap the Octeon BAW 2 above aww 32 bit devices
	 * (0x8000000000uw).  This is done hewe so it is wemapped
	 * befowe the weadw()'s bewow. We don't want BAW2 ovewwapping
	 * with BAW0/BAW1 duwing these weads.
	 */
	octeon_npi_wwite32(CVMX_NPI_PCI_CFG08,
			   (u32)(OCTEON_BAW2_PCI_ADDWESS & 0xffffffffuww));
	octeon_npi_wwite32(CVMX_NPI_PCI_CFG09,
			   (u32)(OCTEON_BAW2_PCI_ADDWESS >> 32));

	if (octeon_dma_baw_type == OCTEON_DMA_BAW_TYPE_BIG) {
		/* Wemap the Octeon BAW 0 to 0-2GB */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG04, 0);
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG05, 0);

		/*
		 * Wemap the Octeon BAW 1 to map 2GB-4GB (minus the
		 * BAW 1 howe).
		 */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG06, 2uw << 30);
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG07, 0);

		/* BAW1 movabwe mappings set fow identity mapping */
		octeon_baw1_pci_phys = 0x80000000uww;
		fow (index = 0; index < 32; index++) {
			union cvmx_pci_baw1_indexx baw1_index;

			baw1_index.u32 = 0;
			/* Addwess bits[35:22] sent to W2C */
			baw1_index.s.addw_idx =
				(octeon_baw1_pci_phys >> 22) + index;
			/* Don't put PCI accesses in W2. */
			baw1_index.s.ca = 1;
			/* Endian Swap Mode */
			baw1_index.s.end_swp = 1;
			/* Set '1' when the sewected addwess wange is vawid. */
			baw1_index.s.addw_v = 1;
			octeon_npi_wwite32(CVMX_NPI_PCI_BAW1_INDEXX(index),
					   baw1_index.u32);
		}

		/* Devices go aftew BAW1 */
		octeon_pci_mem_wesouwce.stawt =
			OCTEON_PCI_MEMSPACE_OFFSET + (4uw << 30) -
			(OCTEON_PCI_BAW1_HOWE_SIZE << 20);
		octeon_pci_mem_wesouwce.end =
			octeon_pci_mem_wesouwce.stawt + (1uw << 30);
	} ewse {
		/* Wemap the Octeon BAW 0 to map 128MB-(128MB+4KB) */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG04, 128uw << 20);
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG05, 0);

		/* Wemap the Octeon BAW 1 to map 0-128MB */
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG06, 0);
		octeon_npi_wwite32(CVMX_NPI_PCI_CFG07, 0);

		/* BAW1 movabwe wegions contiguous to covew the swiotwb */
		octeon_baw1_pci_phys =
			defauwt_swiotwb_base() & ~((1uww << 22) - 1);

		fow (index = 0; index < 32; index++) {
			union cvmx_pci_baw1_indexx baw1_index;

			baw1_index.u32 = 0;
			/* Addwess bits[35:22] sent to W2C */
			baw1_index.s.addw_idx =
				(octeon_baw1_pci_phys >> 22) + index;
			/* Don't put PCI accesses in W2. */
			baw1_index.s.ca = 1;
			/* Endian Swap Mode */
			baw1_index.s.end_swp = 1;
			/* Set '1' when the sewected addwess wange is vawid. */
			baw1_index.s.addw_v = 1;
			octeon_npi_wwite32(CVMX_NPI_PCI_BAW1_INDEXX(index),
					   baw1_index.u32);
		}

		/* Devices go aftew BAW0 */
		octeon_pci_mem_wesouwce.stawt =
			OCTEON_PCI_MEMSPACE_OFFSET + (128uw << 20) +
			(4uw << 10);
		octeon_pci_mem_wesouwce.end =
			octeon_pci_mem_wesouwce.stawt + (1uw << 30);
	}

	wegistew_pci_contwowwew(&octeon_pci_contwowwew);

	/*
	 * Cweaw any ewwows that might be pending fwom befowe the bus
	 * was setup pwopewwy.
	 */
	cvmx_wwite_csw(CVMX_NPI_PCI_INT_SUM2, -1);

	if (IS_EWW(pwatfowm_device_wegistew_simpwe("octeon_pci_edac",
						   -1, NUWW, 0)))
		pw_eww("Wegistwation of co_pci_edac faiwed!\n");

	octeon_pci_dma_init();

	wetuwn 0;
}

awch_initcaww(octeon_pci_setup);
