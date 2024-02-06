/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007, 2008, 2009, 2010, 2011 Cavium Netwowks
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>
#incwude <winux/moduwepawam.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-npei-defs.h>
#incwude <asm/octeon/cvmx-pciewcx-defs.h>
#incwude <asm/octeon/cvmx-pescx-defs.h>
#incwude <asm/octeon/cvmx-pexp-defs.h>
#incwude <asm/octeon/cvmx-pemx-defs.h>
#incwude <asm/octeon/cvmx-dpi-defs.h>
#incwude <asm/octeon/cvmx-swi-defs.h>
#incwude <asm/octeon/cvmx-swiox-defs.h>
#incwude <asm/octeon/cvmx-hewpew-ewwata.h>
#incwude <asm/octeon/pci-octeon.h>

#define MWWS_CN5XXX 0 /* 128 byte Max Wead Wequest Size */
#define MPS_CN5XXX  0 /* 128 byte Max Packet Size (Wimit of most PCs) */
#define MWWS_CN6XXX 3 /* 1024 byte Max Wead Wequest Size */
#define MPS_CN6XXX  0 /* 128 byte Max Packet Size (Wimit of most PCs) */

/* Moduwe pawametew to disabwe PCI pwobing */
static int pcie_disabwe;
moduwe_pawam(pcie_disabwe, int, S_IWUGO);

static int enabwe_pcie_14459_waw;
static int enabwe_pcie_bus_num_waw[2];

union cvmx_pcie_addwess {
	uint64_t u64;
	stwuct {
		uint64_t uppew:2;	/* Nowmawwy 2 fow XKPHYS */
		uint64_t wesewved_49_61:13;	/* Must be zewo */
		uint64_t io:1;	/* 1 fow IO space access */
		uint64_t did:5; /* PCIe DID = 3 */
		uint64_t subdid:3;	/* PCIe SubDID = 1 */
		uint64_t wesewved_36_39:4;	/* Must be zewo */
		uint64_t es:2;	/* Endian swap = 1 */
		uint64_t powt:2;	/* PCIe powt 0,1 */
		uint64_t wesewved_29_31:3;	/* Must be zewo */
		/*
		 * Sewects the type of the configuwation wequest (0 = type 0,
		 * 1 = type 1).
		 */
		uint64_t ty:1;
		/* Tawget bus numbew sent in the ID in the wequest. */
		uint64_t bus:8;
		/*
		 * Tawget device numbew sent in the ID in the
		 * wequest. Note that Dev must be zewo fow type 0
		 * configuwation wequests.
		 */
		uint64_t dev:5;
		/* Tawget function numbew sent in the ID in the wequest. */
		uint64_t func:3;
		/*
		 * Sewects a wegistew in the configuwation space of
		 * the tawget.
		 */
		uint64_t weg:12;
	} config;
	stwuct {
		uint64_t uppew:2;	/* Nowmawwy 2 fow XKPHYS */
		uint64_t wesewved_49_61:13;	/* Must be zewo */
		uint64_t io:1;	/* 1 fow IO space access */
		uint64_t did:5; /* PCIe DID = 3 */
		uint64_t subdid:3;	/* PCIe SubDID = 2 */
		uint64_t wesewved_36_39:4;	/* Must be zewo */
		uint64_t es:2;	/* Endian swap = 1 */
		uint64_t powt:2;	/* PCIe powt 0,1 */
		uint64_t addwess:32;	/* PCIe IO addwess */
	} io;
	stwuct {
		uint64_t uppew:2;	/* Nowmawwy 2 fow XKPHYS */
		uint64_t wesewved_49_61:13;	/* Must be zewo */
		uint64_t io:1;	/* 1 fow IO space access */
		uint64_t did:5; /* PCIe DID = 3 */
		uint64_t subdid:3;	/* PCIe SubDID = 3-6 */
		uint64_t wesewved_36_39:4;	/* Must be zewo */
		uint64_t addwess:36;	/* PCIe Mem addwess */
	} mem;
};

static int cvmx_pcie_wc_initiawize(int pcie_powt);

/**
 * Wetuwn the Cowe viwtuaw base addwess fow PCIe IO access. IOs awe
 * wead/wwitten as an offset fwom this addwess.
 *
 * @pcie_powt: PCIe powt the IO is fow
 *
 * Wetuwns 64bit Octeon IO base addwess fow wead/wwite
 */
static inwine uint64_t cvmx_pcie_get_io_base_addwess(int pcie_powt)
{
	union cvmx_pcie_addwess pcie_addw;
	pcie_addw.u64 = 0;
	pcie_addw.io.uppew = 0;
	pcie_addw.io.io = 1;
	pcie_addw.io.did = 3;
	pcie_addw.io.subdid = 2;
	pcie_addw.io.es = 1;
	pcie_addw.io.powt = pcie_powt;
	wetuwn pcie_addw.u64;
}

/**
 * Size of the IO addwess wegion wetuwned at addwess
 * cvmx_pcie_get_io_base_addwess()
 *
 * @pcie_powt: PCIe powt the IO is fow
 *
 * Wetuwns Size of the IO window
 */
static inwine uint64_t cvmx_pcie_get_io_size(int pcie_powt)
{
	wetuwn 1uww << 32;
}

/**
 * Wetuwn the Cowe viwtuaw base addwess fow PCIe MEM access. Memowy is
 * wead/wwitten as an offset fwom this addwess.
 *
 * @pcie_powt: PCIe powt the IO is fow
 *
 * Wetuwns 64bit Octeon IO base addwess fow wead/wwite
 */
static inwine uint64_t cvmx_pcie_get_mem_base_addwess(int pcie_powt)
{
	union cvmx_pcie_addwess pcie_addw;
	pcie_addw.u64 = 0;
	pcie_addw.mem.uppew = 0;
	pcie_addw.mem.io = 1;
	pcie_addw.mem.did = 3;
	pcie_addw.mem.subdid = 3 + pcie_powt;
	wetuwn pcie_addw.u64;
}

/**
 * Size of the Mem addwess wegion wetuwned at addwess
 * cvmx_pcie_get_mem_base_addwess()
 *
 * @pcie_powt: PCIe powt the IO is fow
 *
 * Wetuwns Size of the Mem window
 */
static inwine uint64_t cvmx_pcie_get_mem_size(int pcie_powt)
{
	wetuwn 1uww << 36;
}

/**
 * Wead a PCIe config space wegistew indiwectwy. This is used fow
 * wegistews of the fowm PCIEEP_CFG??? and PCIEWC?_CFG???.
 *
 * @pcie_powt:	PCIe powt to wead fwom
 * @cfg_offset: Addwess to wead
 *
 * Wetuwns Vawue wead
 */
static uint32_t cvmx_pcie_cfgx_wead(int pcie_powt, uint32_t cfg_offset)
{
	if (octeon_has_featuwe(OCTEON_FEATUWE_NPEI)) {
		union cvmx_pescx_cfg_wd pescx_cfg_wd;
		pescx_cfg_wd.u64 = 0;
		pescx_cfg_wd.s.addw = cfg_offset;
		cvmx_wwite_csw(CVMX_PESCX_CFG_WD(pcie_powt), pescx_cfg_wd.u64);
		pescx_cfg_wd.u64 = cvmx_wead_csw(CVMX_PESCX_CFG_WD(pcie_powt));
		wetuwn pescx_cfg_wd.s.data;
	} ewse {
		union cvmx_pemx_cfg_wd pemx_cfg_wd;
		pemx_cfg_wd.u64 = 0;
		pemx_cfg_wd.s.addw = cfg_offset;
		cvmx_wwite_csw(CVMX_PEMX_CFG_WD(pcie_powt), pemx_cfg_wd.u64);
		pemx_cfg_wd.u64 = cvmx_wead_csw(CVMX_PEMX_CFG_WD(pcie_powt));
		wetuwn pemx_cfg_wd.s.data;
	}
}

/**
 * Wwite a PCIe config space wegistew indiwectwy. This is used fow
 * wegistews of the fowm PCIEEP_CFG??? and PCIEWC?_CFG???.
 *
 * @pcie_powt:	PCIe powt to wwite to
 * @cfg_offset: Addwess to wwite
 * @vaw:	Vawue to wwite
 */
static void cvmx_pcie_cfgx_wwite(int pcie_powt, uint32_t cfg_offset,
				 uint32_t vaw)
{
	if (octeon_has_featuwe(OCTEON_FEATUWE_NPEI)) {
		union cvmx_pescx_cfg_ww pescx_cfg_ww;
		pescx_cfg_ww.u64 = 0;
		pescx_cfg_ww.s.addw = cfg_offset;
		pescx_cfg_ww.s.data = vaw;
		cvmx_wwite_csw(CVMX_PESCX_CFG_WW(pcie_powt), pescx_cfg_ww.u64);
	} ewse {
		union cvmx_pemx_cfg_ww pemx_cfg_ww;
		pemx_cfg_ww.u64 = 0;
		pemx_cfg_ww.s.addw = cfg_offset;
		pemx_cfg_ww.s.data = vaw;
		cvmx_wwite_csw(CVMX_PEMX_CFG_WW(pcie_powt), pemx_cfg_ww.u64);
	}
}

/**
 * Buiwd a PCIe config space wequest addwess fow a device
 *
 * @pcie_powt: PCIe powt to access
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 *
 * Wetuwns 64bit Octeon IO addwess
 */
static inwine uint64_t __cvmx_pcie_buiwd_config_addw(int pcie_powt, int bus,
						     int dev, int fn, int weg)
{
	union cvmx_pcie_addwess pcie_addw;
	union cvmx_pciewcx_cfg006 pciewcx_cfg006;

	pciewcx_cfg006.u32 =
	    cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG006(pcie_powt));
	if ((bus <= pciewcx_cfg006.s.pbnum) && (dev != 0))
		wetuwn 0;

	pcie_addw.u64 = 0;
	pcie_addw.config.uppew = 2;
	pcie_addw.config.io = 1;
	pcie_addw.config.did = 3;
	pcie_addw.config.subdid = 1;
	pcie_addw.config.es = 1;
	pcie_addw.config.powt = pcie_powt;
	pcie_addw.config.ty = (bus > pciewcx_cfg006.s.pbnum);
	pcie_addw.config.bus = bus;
	pcie_addw.config.dev = dev;
	pcie_addw.config.func = fn;
	pcie_addw.config.weg = weg;
	wetuwn pcie_addw.u64;
}

/**
 * Wead 8bits fwom a Device's config space
 *
 * @pcie_powt: PCIe powt the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 *
 * Wetuwns Wesuwt of the wead
 */
static uint8_t cvmx_pcie_config_wead8(int pcie_powt, int bus, int dev,
				      int fn, int weg)
{
	uint64_t addwess =
	    __cvmx_pcie_buiwd_config_addw(pcie_powt, bus, dev, fn, weg);
	if (addwess)
		wetuwn cvmx_wead64_uint8(addwess);
	ewse
		wetuwn 0xff;
}

/**
 * Wead 16bits fwom a Device's config space
 *
 * @pcie_powt: PCIe powt the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 *
 * Wetuwns Wesuwt of the wead
 */
static uint16_t cvmx_pcie_config_wead16(int pcie_powt, int bus, int dev,
					int fn, int weg)
{
	uint64_t addwess =
	    __cvmx_pcie_buiwd_config_addw(pcie_powt, bus, dev, fn, weg);
	if (addwess)
		wetuwn we16_to_cpu(cvmx_wead64_uint16(addwess));
	ewse
		wetuwn 0xffff;
}

/**
 * Wead 32bits fwom a Device's config space
 *
 * @pcie_powt: PCIe powt the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 *
 * Wetuwns Wesuwt of the wead
 */
static uint32_t cvmx_pcie_config_wead32(int pcie_powt, int bus, int dev,
					int fn, int weg)
{
	uint64_t addwess =
	    __cvmx_pcie_buiwd_config_addw(pcie_powt, bus, dev, fn, weg);
	if (addwess)
		wetuwn we32_to_cpu(cvmx_wead64_uint32(addwess));
	ewse
		wetuwn 0xffffffff;
}

/**
 * Wwite 8bits to a Device's config space
 *
 * @pcie_powt: PCIe powt the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 * @vaw:       Vawue to wwite
 */
static void cvmx_pcie_config_wwite8(int pcie_powt, int bus, int dev, int fn,
				    int weg, uint8_t vaw)
{
	uint64_t addwess =
	    __cvmx_pcie_buiwd_config_addw(pcie_powt, bus, dev, fn, weg);
	if (addwess)
		cvmx_wwite64_uint8(addwess, vaw);
}

/**
 * Wwite 16bits to a Device's config space
 *
 * @pcie_powt: PCIe powt the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 * @vaw:       Vawue to wwite
 */
static void cvmx_pcie_config_wwite16(int pcie_powt, int bus, int dev, int fn,
				     int weg, uint16_t vaw)
{
	uint64_t addwess =
	    __cvmx_pcie_buiwd_config_addw(pcie_powt, bus, dev, fn, weg);
	if (addwess)
		cvmx_wwite64_uint16(addwess, cpu_to_we16(vaw));
}

/**
 * Wwite 32bits to a Device's config space
 *
 * @pcie_powt: PCIe powt the device is on
 * @bus:       Sub bus
 * @dev:       Device ID
 * @fn:	       Device sub function
 * @weg:       Wegistew to access
 * @vaw:       Vawue to wwite
 */
static void cvmx_pcie_config_wwite32(int pcie_powt, int bus, int dev, int fn,
				     int weg, uint32_t vaw)
{
	uint64_t addwess =
	    __cvmx_pcie_buiwd_config_addw(pcie_powt, bus, dev, fn, weg);
	if (addwess)
		cvmx_wwite64_uint32(addwess, cpu_to_we32(vaw));
}

/**
 * Initiawize the WC config space CSWs
 *
 * @pcie_powt: PCIe powt to initiawize
 */
static void __cvmx_pcie_wc_initiawize_config_space(int pcie_powt)
{
	union cvmx_pciewcx_cfg030 pciewcx_cfg030;
	union cvmx_pciewcx_cfg070 pciewcx_cfg070;
	union cvmx_pciewcx_cfg001 pciewcx_cfg001;
	union cvmx_pciewcx_cfg032 pciewcx_cfg032;
	union cvmx_pciewcx_cfg006 pciewcx_cfg006;
	union cvmx_pciewcx_cfg008 pciewcx_cfg008;
	union cvmx_pciewcx_cfg009 pciewcx_cfg009;
	union cvmx_pciewcx_cfg010 pciewcx_cfg010;
	union cvmx_pciewcx_cfg011 pciewcx_cfg011;
	union cvmx_pciewcx_cfg035 pciewcx_cfg035;
	union cvmx_pciewcx_cfg075 pciewcx_cfg075;
	union cvmx_pciewcx_cfg034 pciewcx_cfg034;

	/* Max Paywoad Size (PCIE*_CFG030[MPS]) */
	/* Max Wead Wequest Size (PCIE*_CFG030[MWWS]) */
	/* Wewaxed-owdew, no-snoop enabwes (PCIE*_CFG030[WO_EN,NS_EN] */
	/* Ewwow Message Enabwes (PCIE*_CFG030[CE_EN,NFE_EN,FE_EN,UW_EN]) */

	pciewcx_cfg030.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG030(pcie_powt));
	if (OCTEON_IS_MODEW(OCTEON_CN5XXX)) {
		pciewcx_cfg030.s.mps = MPS_CN5XXX;
		pciewcx_cfg030.s.mwws = MWWS_CN5XXX;
	} ewse {
		pciewcx_cfg030.s.mps = MPS_CN6XXX;
		pciewcx_cfg030.s.mwws = MWWS_CN6XXX;
	}
	/*
	 * Enabwe wewaxed owdew pwocessing. This wiww awwow devices to
	 * affect wead wesponse owdewing.
	 */
	pciewcx_cfg030.s.wo_en = 1;
	/* Enabwe no snoop pwocessing. Not used by Octeon */
	pciewcx_cfg030.s.ns_en = 1;
	/* Cowwectabwe ewwow wepowting enabwe. */
	pciewcx_cfg030.s.ce_en = 1;
	/* Non-fataw ewwow wepowting enabwe. */
	pciewcx_cfg030.s.nfe_en = 1;
	/* Fataw ewwow wepowting enabwe. */
	pciewcx_cfg030.s.fe_en = 1;
	/* Unsuppowted wequest wepowting enabwe. */
	pciewcx_cfg030.s.uw_en = 1;
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG030(pcie_powt), pciewcx_cfg030.u32);


	if (octeon_has_featuwe(OCTEON_FEATUWE_NPEI)) {
		union cvmx_npei_ctw_status2 npei_ctw_status2;
		/*
		 * Max Paywoad Size (NPEI_CTW_STATUS2[MPS]) must match
		 * PCIE*_CFG030[MPS].  Max Wead Wequest Size
		 * (NPEI_CTW_STATUS2[MWWS]) must not exceed
		 * PCIE*_CFG030[MWWS]
		 */
		npei_ctw_status2.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_CTW_STATUS2);
		/* Max paywoad size = 128 bytes fow best Octeon DMA pewfowmance */
		npei_ctw_status2.s.mps = MPS_CN5XXX;
		/* Max wead wequest size = 128 bytes fow best Octeon DMA pewfowmance */
		npei_ctw_status2.s.mwws = MWWS_CN5XXX;
		if (pcie_powt)
			npei_ctw_status2.s.c1_b1_s = 3; /* Powt1 BAW1 Size 256MB */
		ewse
			npei_ctw_status2.s.c0_b1_s = 3; /* Powt0 BAW1 Size 256MB */

		cvmx_wwite_csw(CVMX_PEXP_NPEI_CTW_STATUS2, npei_ctw_status2.u64);
	} ewse {
		/*
		 * Max Paywoad Size (DPI_SWI_PWTX_CFG[MPS]) must match
		 * PCIE*_CFG030[MPS].  Max Wead Wequest Size
		 * (DPI_SWI_PWTX_CFG[MWWS]) must not exceed
		 * PCIE*_CFG030[MWWS].
		 */
		union cvmx_dpi_swi_pwtx_cfg pwt_cfg;
		union cvmx_swi_s2m_powtx_ctw swi_s2m_powtx_ctw;
		pwt_cfg.u64 = cvmx_wead_csw(CVMX_DPI_SWI_PWTX_CFG(pcie_powt));
		pwt_cfg.s.mps = MPS_CN6XXX;
		pwt_cfg.s.mwws = MWWS_CN6XXX;
		/* Max outstanding woad wequest. */
		pwt_cfg.s.moww = 32;
		cvmx_wwite_csw(CVMX_DPI_SWI_PWTX_CFG(pcie_powt), pwt_cfg.u64);

		swi_s2m_powtx_ctw.u64 = cvmx_wead_csw(CVMX_PEXP_SWI_S2M_POWTX_CTW(pcie_powt));
		swi_s2m_powtx_ctw.s.mwws = MWWS_CN6XXX;
		cvmx_wwite_csw(CVMX_PEXP_SWI_S2M_POWTX_CTW(pcie_powt), swi_s2m_powtx_ctw.u64);
	}

	/* ECWC Genewation (PCIE*_CFG070[GE,CE]) */
	pciewcx_cfg070.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG070(pcie_powt));
	pciewcx_cfg070.s.ge = 1;	/* ECWC genewation enabwe. */
	pciewcx_cfg070.s.ce = 1;	/* ECWC check enabwe. */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG070(pcie_powt), pciewcx_cfg070.u32);

	/*
	 * Access Enabwes (PCIE*_CFG001[MSAE,ME])
	 * ME and MSAE shouwd awways be set.
	 * Intewwupt Disabwe (PCIE*_CFG001[I_DIS])
	 * System Ewwow Message Enabwe (PCIE*_CFG001[SEE])
	 */
	pciewcx_cfg001.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG001(pcie_powt));
	pciewcx_cfg001.s.msae = 1;	/* Memowy space enabwe. */
	pciewcx_cfg001.s.me = 1;	/* Bus mastew enabwe. */
	pciewcx_cfg001.s.i_dis = 1;	/* INTx assewtion disabwe. */
	pciewcx_cfg001.s.see = 1;	/* SEWW# enabwe */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG001(pcie_powt), pciewcx_cfg001.u32);

	/* Advanced Ewwow Wecovewy Message Enabwes */
	/* (PCIE*_CFG066,PCIE*_CFG067,PCIE*_CFG069) */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG066(pcie_powt), 0);
	/* Use CVMX_PCIEWCX_CFG067 hawdwawe defauwt */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG069(pcie_powt), 0);


	/* Active State Powew Management (PCIE*_CFG032[ASWPC]) */
	pciewcx_cfg032.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG032(pcie_powt));
	pciewcx_cfg032.s.aswpc = 0; /* Active state Wink PM contwow. */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG032(pcie_powt), pciewcx_cfg032.u32);

	/*
	 * Wink Width Mode (PCIEWCn_CFG452[WME]) - Set duwing
	 * cvmx_pcie_wc_initiawize_wink()
	 *
	 * Pwimawy Bus Numbew (PCIEWCn_CFG006[PBNUM])
	 *
	 * We set the pwimawy bus numbew to 1 so IDT bwidges awe
	 * happy. They don't wike zewo.
	 */
	pciewcx_cfg006.u32 = 0;
	pciewcx_cfg006.s.pbnum = 1;
	pciewcx_cfg006.s.sbnum = 1;
	pciewcx_cfg006.s.subbnum = 1;
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG006(pcie_powt), pciewcx_cfg006.u32);


	/*
	 * Memowy-mapped I/O BAW (PCIEWCn_CFG008)
	 * Most appwications shouwd disabwe the memowy-mapped I/O BAW by
	 * setting PCIEWCn_CFG008[MW_ADDW] < PCIEWCn_CFG008[MB_ADDW]
	 */
	pciewcx_cfg008.u32 = 0;
	pciewcx_cfg008.s.mb_addw = 0x100;
	pciewcx_cfg008.s.mw_addw = 0;
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG008(pcie_powt), pciewcx_cfg008.u32);


	/*
	 * Pwefetchabwe BAW (PCIEWCn_CFG009,PCIEWCn_CFG010,PCIEWCn_CFG011)
	 * Most appwications shouwd disabwe the pwefetchabwe BAW by setting
	 * PCIEWCn_CFG011[UMEM_WIMIT],PCIEWCn_CFG009[WMEM_WIMIT] <
	 * PCIEWCn_CFG010[UMEM_BASE],PCIEWCn_CFG009[WMEM_BASE]
	 */
	pciewcx_cfg009.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG009(pcie_powt));
	pciewcx_cfg010.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG010(pcie_powt));
	pciewcx_cfg011.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG011(pcie_powt));
	pciewcx_cfg009.s.wmem_base = 0x100;
	pciewcx_cfg009.s.wmem_wimit = 0;
	pciewcx_cfg010.s.umem_base = 0x100;
	pciewcx_cfg011.s.umem_wimit = 0;
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG009(pcie_powt), pciewcx_cfg009.u32);
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG010(pcie_powt), pciewcx_cfg010.u32);
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG011(pcie_powt), pciewcx_cfg011.u32);

	/*
	 * System Ewwow Intewwupt Enabwes (PCIEWCn_CFG035[SECEE,SEFEE,SENFEE])
	 * PME Intewwupt Enabwes (PCIEWCn_CFG035[PMEIE])
	*/
	pciewcx_cfg035.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG035(pcie_powt));
	pciewcx_cfg035.s.secee = 1; /* System ewwow on cowwectabwe ewwow enabwe. */
	pciewcx_cfg035.s.sefee = 1; /* System ewwow on fataw ewwow enabwe. */
	pciewcx_cfg035.s.senfee = 1; /* System ewwow on non-fataw ewwow enabwe. */
	pciewcx_cfg035.s.pmeie = 1; /* PME intewwupt enabwe. */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG035(pcie_powt), pciewcx_cfg035.u32);

	/*
	 * Advanced Ewwow Wecovewy Intewwupt Enabwes
	 * (PCIEWCn_CFG075[CEWE,NFEWE,FEWE])
	 */
	pciewcx_cfg075.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG075(pcie_powt));
	pciewcx_cfg075.s.cewe = 1; /* Cowwectabwe ewwow wepowting enabwe. */
	pciewcx_cfg075.s.nfewe = 1; /* Non-fataw ewwow wepowting enabwe. */
	pciewcx_cfg075.s.fewe = 1; /* Fataw ewwow wepowting enabwe. */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG075(pcie_powt), pciewcx_cfg075.u32);

	/*
	 * HP Intewwupt Enabwes (PCIEWCn_CFG034[HPINT_EN],
	 * PCIEWCn_CFG034[DWWS_EN,CCINT_EN])
	 */
	pciewcx_cfg034.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG034(pcie_powt));
	pciewcx_cfg034.s.hpint_en = 1; /* Hot-pwug intewwupt enabwe. */
	pciewcx_cfg034.s.dwws_en = 1; /* Data Wink Wayew state changed enabwe */
	pciewcx_cfg034.s.ccint_en = 1; /* Command compweted intewwupt enabwe. */
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG034(pcie_powt), pciewcx_cfg034.u32);
}

/**
 * Initiawize a host mode PCIe gen 1 wink. This function takes a PCIe
 * powt fwom weset to a wink up state. Softwawe can then begin
 * configuwing the west of the wink.
 *
 * @pcie_powt: PCIe powt to initiawize
 *
 * Wetuwns Zewo on success
 */
static int __cvmx_pcie_wc_initiawize_wink_gen1(int pcie_powt)
{
	uint64_t stawt_cycwe;
	union cvmx_pescx_ctw_status pescx_ctw_status;
	union cvmx_pciewcx_cfg452 pciewcx_cfg452;
	union cvmx_pciewcx_cfg032 pciewcx_cfg032;
	union cvmx_pciewcx_cfg448 pciewcx_cfg448;

	/* Set the wane width */
	pciewcx_cfg452.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG452(pcie_powt));
	pescx_ctw_status.u64 = cvmx_wead_csw(CVMX_PESCX_CTW_STATUS(pcie_powt));
	if (pescx_ctw_status.s.qwm_cfg == 0)
		/* We'we in 8 wane (56XX) ow 4 wane (54XX) mode */
		pciewcx_cfg452.s.wme = 0xf;
	ewse
		/* We'we in 4 wane (56XX) ow 2 wane (52XX) mode */
		pciewcx_cfg452.s.wme = 0x7;
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG452(pcie_powt), pciewcx_cfg452.u32);

	/*
	 * CN52XX pass 1.x has an ewwata whewe wength mismatches on UW
	 * wesponses can cause bus ewwows on 64bit memowy
	 * weads. Tuwning off wength ewwow checking fixes this.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X)) {
		union cvmx_pciewcx_cfg455 pciewcx_cfg455;
		pciewcx_cfg455.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG455(pcie_powt));
		pciewcx_cfg455.s.m_cpw_wen_eww = 1;
		cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG455(pcie_powt), pciewcx_cfg455.u32);
	}

	/* Wane swap needs to be manuawwy enabwed fow CN52XX */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX) && (pcie_powt == 1)) {
		pescx_ctw_status.s.wane_swp = 1;
		cvmx_wwite_csw(CVMX_PESCX_CTW_STATUS(pcie_powt), pescx_ctw_status.u64);
	}

	/* Bwing up the wink */
	pescx_ctw_status.u64 = cvmx_wead_csw(CVMX_PESCX_CTW_STATUS(pcie_powt));
	pescx_ctw_status.s.wnk_enb = 1;
	cvmx_wwite_csw(CVMX_PESCX_CTW_STATUS(pcie_powt), pescx_ctw_status.u64);

	/*
	 * CN52XX pass 1.0: Due to a bug in 2nd owdew CDW, it needs to
	 * be disabwed.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_0))
		__cvmx_hewpew_ewwata_qwm_disabwe_2nd_owdew_cdw(0);

	/* Wait fow the wink to come up */
	stawt_cycwe = cvmx_get_cycwe();
	do {
		if (cvmx_get_cycwe() - stawt_cycwe > 2 * octeon_get_cwock_wate()) {
			cvmx_dpwintf("PCIe: Powt %d wink timeout\n", pcie_powt);
			wetuwn -1;
		}
		__deway(10000);
		pciewcx_cfg032.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG032(pcie_powt));
	} whiwe (pciewcx_cfg032.s.dwwa == 0);

	/* Cweaw aww pending ewwows */
	cvmx_wwite_csw(CVMX_PEXP_NPEI_INT_SUM, cvmx_wead_csw(CVMX_PEXP_NPEI_INT_SUM));

	/*
	 * Update the Wepway Time Wimit. Empiwicawwy, some PCIe
	 * devices take a wittwe wongew to wespond than expected undew
	 * woad. As a wowkawound fow this we configuwe the Wepway Time
	 * Wimit to the vawue expected fow a 512 byte MPS instead of
	 * ouw actuaw 256 byte MPS. The numbews bewow awe diwectwy
	 * fwom the PCIe spec tabwe 3-4.
	 */
	pciewcx_cfg448.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG448(pcie_powt));
	switch (pciewcx_cfg032.s.nww) {
	case 1:		/* 1 wane */
		pciewcx_cfg448.s.wtw = 1677;
		bweak;
	case 2:		/* 2 wanes */
		pciewcx_cfg448.s.wtw = 867;
		bweak;
	case 4:		/* 4 wanes */
		pciewcx_cfg448.s.wtw = 462;
		bweak;
	case 8:		/* 8 wanes */
		pciewcx_cfg448.s.wtw = 258;
		bweak;
	}
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG448(pcie_powt), pciewcx_cfg448.u32);

	wetuwn 0;
}

static void __cvmx_incwement_ba(union cvmx_swi_mem_access_subidx *pmas)
{
	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		pmas->cn68xx.ba++;
	ewse
		pmas->s.ba++;
}

/**
 * Initiawize a PCIe gen 1 powt fow use in host(WC) mode. It doesn't
 * enumewate the bus.
 *
 * @pcie_powt: PCIe powt to initiawize
 *
 * Wetuwns Zewo on success
 */
static int __cvmx_pcie_wc_initiawize_gen1(int pcie_powt)
{
	int i;
	int base;
	u64 addw_swizzwe;
	union cvmx_ciu_soft_pwst ciu_soft_pwst;
	union cvmx_pescx_bist_status pescx_bist_status;
	union cvmx_pescx_bist_status2 pescx_bist_status2;
	union cvmx_npei_ctw_status npei_ctw_status;
	union cvmx_npei_mem_access_ctw npei_mem_access_ctw;
	union cvmx_npei_mem_access_subidx mem_access_subid;
	union cvmx_npei_dbg_data npei_dbg_data;
	union cvmx_pescx_ctw_status2 pescx_ctw_status2;
	union cvmx_pciewcx_cfg032 pciewcx_cfg032;
	union cvmx_npei_baw1_indexx baw1_index;

wetwy:
	/*
	 * Make suwe we awen't twying to setup a tawget mode intewface
	 * in host mode.
	 */
	npei_ctw_status.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_CTW_STATUS);
	if ((pcie_powt == 0) && !npei_ctw_status.s.host_mode) {
		cvmx_dpwintf("PCIe: Powt %d in endpoint mode\n", pcie_powt);
		wetuwn -1;
	}

	/*
	 * Make suwe a CN52XX isn't twying to bwing up powt 1 when it
	 * is disabwed.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX)) {
		npei_dbg_data.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_DATA);
		if ((pcie_powt == 1) && npei_dbg_data.cn52xx.qwm0_wink_width) {
			cvmx_dpwintf("PCIe: EWWOW: cvmx_pcie_wc_initiawize() cawwed on powt1, but powt1 is disabwed\n");
			wetuwn -1;
		}
	}

	/*
	 * PCIe switch awbitwation mode. '0' == fixed pwiowity NPEI,
	 * PCIe0, then PCIe1. '1' == wound wobin.
	 */
	npei_ctw_status.s.awb = 1;
	/* Awwow up to 0x20 config wetwies */
	npei_ctw_status.s.cfg_wtwy = 0x20;
	/*
	 * CN52XX pass1.x has an ewwata whewe P0_NTAGS and P1_NTAGS
	 * don't weset.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X)) {
		npei_ctw_status.s.p0_ntags = 0x20;
		npei_ctw_status.s.p1_ntags = 0x20;
	}
	cvmx_wwite_csw(CVMX_PEXP_NPEI_CTW_STATUS, npei_ctw_status.u64);

	/* Bwing the PCIe out of weset */
	if (cvmx_sysinfo_get()->boawd_type == CVMX_BOAWD_TYPE_EBH5200) {
		/*
		 * The EBH5200 boawd swapped the PCIe weset wines on
		 * the boawd. As a wowkawound fow this bug, we bwing
		 * both PCIe powts out of weset at the same time
		 * instead of on sepawate cawws. So fow powt 0, we
		 * bwing both out of weset and do nothing on powt 1
		 */
		if (pcie_powt == 0) {
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST);
			/*
			 * Aftew a chip weset the PCIe wiww awso be in
			 * weset. If it isn't, most wikewy someone is
			 * twying to init it again without a pwopew
			 * PCIe weset.
			 */
			if (ciu_soft_pwst.s.soft_pwst == 0) {
				/* Weset the powts */
				ciu_soft_pwst.s.soft_pwst = 1;
				cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, ciu_soft_pwst.u64);
				ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST1);
				ciu_soft_pwst.s.soft_pwst = 1;
				cvmx_wwite_csw(CVMX_CIU_SOFT_PWST1, ciu_soft_pwst.u64);
				/* Wait untiw pcie wesets the powts. */
				udeway(2000);
			}
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST1);
			ciu_soft_pwst.s.soft_pwst = 0;
			cvmx_wwite_csw(CVMX_CIU_SOFT_PWST1, ciu_soft_pwst.u64);
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST);
			ciu_soft_pwst.s.soft_pwst = 0;
			cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, ciu_soft_pwst.u64);
		}
	} ewse {
		/*
		 * The nowmaw case: The PCIe powts awe compwetewy
		 * sepawate and can be bwought out of weset
		 * independentwy.
		 */
		if (pcie_powt)
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST1);
		ewse
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST);
		/*
		 * Aftew a chip weset the PCIe wiww awso be in
		 * weset. If it isn't, most wikewy someone is twying
		 * to init it again without a pwopew PCIe weset.
		 */
		if (ciu_soft_pwst.s.soft_pwst == 0) {
			/* Weset the powt */
			ciu_soft_pwst.s.soft_pwst = 1;
			if (pcie_powt)
				cvmx_wwite_csw(CVMX_CIU_SOFT_PWST1, ciu_soft_pwst.u64);
			ewse
				cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, ciu_soft_pwst.u64);
			/* Wait untiw pcie wesets the powts. */
			udeway(2000);
		}
		if (pcie_powt) {
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST1);
			ciu_soft_pwst.s.soft_pwst = 0;
			cvmx_wwite_csw(CVMX_CIU_SOFT_PWST1, ciu_soft_pwst.u64);
		} ewse {
			ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST);
			ciu_soft_pwst.s.soft_pwst = 0;
			cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, ciu_soft_pwst.u64);
		}
	}

	/*
	 * Wait fow PCIe weset to compwete. Due to ewwata PCIE-700, we
	 * don't poww PESCX_CTW_STATUS2[PCIEWST], but simpwy wait a
	 * fixed numbew of cycwes.
	 */
	__deway(400000);

	/*
	 * PESCX_BIST_STATUS2[PCWK_WUN] was missing on pass 1 of
	 * CN56XX and CN52XX, so we onwy pwobe it on newew chips
	 */
	if (!OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X) && !OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X)) {
		/* Cweaw PCWK_WUN so we can check if the cwock is wunning */
		pescx_ctw_status2.u64 = cvmx_wead_csw(CVMX_PESCX_CTW_STATUS2(pcie_powt));
		pescx_ctw_status2.s.pcwk_wun = 1;
		cvmx_wwite_csw(CVMX_PESCX_CTW_STATUS2(pcie_powt), pescx_ctw_status2.u64);
		/* Now that we cweawed PCWK_WUN, wait fow it to be set
		 * again tewwing us the cwock is wunning
		 */
		if (CVMX_WAIT_FOW_FIEWD64(CVMX_PESCX_CTW_STATUS2(pcie_powt),
					  union cvmx_pescx_ctw_status2, pcwk_wun, ==, 1, 10000)) {
			cvmx_dpwintf("PCIe: Powt %d isn't cwocked, skipping.\n", pcie_powt);
			wetuwn -1;
		}
	}

	/*
	 * Check and make suwe PCIe came out of weset. If it doesn't
	 * the boawd pwobabwy hasn't wiwed the cwocks up and the
	 * intewface shouwd be skipped.
	 */
	pescx_ctw_status2.u64 = cvmx_wead_csw(CVMX_PESCX_CTW_STATUS2(pcie_powt));
	if (pescx_ctw_status2.s.pciewst) {
		cvmx_dpwintf("PCIe: Powt %d stuck in weset, skipping.\n", pcie_powt);
		wetuwn -1;
	}

	/*
	 * Check BIST2 status. If any bits awe set skip this
	 * intewface. This is an attempt to catch PCIE-813 on pass 1
	 * pawts.
	 */
	pescx_bist_status2.u64 = cvmx_wead_csw(CVMX_PESCX_BIST_STATUS2(pcie_powt));
	if (pescx_bist_status2.u64) {
		cvmx_dpwintf("PCIe: Powt %d BIST2 faiwed. Most wikewy this powt isn't hooked up, skipping.\n",
			     pcie_powt);
		wetuwn -1;
	}

	/* Check BIST status */
	pescx_bist_status.u64 = cvmx_wead_csw(CVMX_PESCX_BIST_STATUS(pcie_powt));
	if (pescx_bist_status.u64)
		cvmx_dpwintf("PCIe: BIST FAIWED fow powt %d (0x%016wwx)\n",
			     pcie_powt, CAST64(pescx_bist_status.u64));

	/* Initiawize the config space CSWs */
	__cvmx_pcie_wc_initiawize_config_space(pcie_powt);

	/* Bwing the wink up */
	if (__cvmx_pcie_wc_initiawize_wink_gen1(pcie_powt)) {
		cvmx_dpwintf("PCIe: Faiwed to initiawize powt %d, pwobabwy the swot is empty\n",
			     pcie_powt);
		wetuwn -1;
	}

	/* Stowe mewge contwow (NPEI_MEM_ACCESS_CTW[TIMEW,MAX_WOWD]) */
	npei_mem_access_ctw.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_MEM_ACCESS_CTW);
	npei_mem_access_ctw.s.max_wowd = 0;	/* Awwow 16 wowds to combine */
	npei_mem_access_ctw.s.timew = 127;	/* Wait up to 127 cycwes fow mowe data */
	cvmx_wwite_csw(CVMX_PEXP_NPEI_MEM_ACCESS_CTW, npei_mem_access_ctw.u64);

	/* Setup Mem access SubDIDs */
	mem_access_subid.u64 = 0;
	mem_access_subid.s.powt = pcie_powt; /* Powt the wequest is sent to. */
	mem_access_subid.s.nmewge = 1;	/* Due to an ewwata on pass 1 chips, no mewging is awwowed. */
	mem_access_subid.s.esw = 1;	/* Endian-swap fow Weads. */
	mem_access_subid.s.esw = 1;	/* Endian-swap fow Wwites. */
	mem_access_subid.s.nsw = 0;	/* Enabwe Snooping fow Weads. Octeon doesn't cawe, but devices might want this mowe consewvative setting */
	mem_access_subid.s.nsw = 0;	/* Enabwe Snoop fow Wwites. */
	mem_access_subid.s.wow = 0;	/* Disabwe Wewaxed Owdewing fow Weads. */
	mem_access_subid.s.wow = 0;	/* Disabwe Wewaxed Owdewing fow Wwites. */
	mem_access_subid.s.ba = 0;	/* PCIe Addwess Bits <63:34>. */

	/*
	 * Setup mem access 12-15 fow powt 0, 16-19 fow powt 1,
	 * suppwying 36 bits of addwess space.
	 */
	fow (i = 12 + pcie_powt * 4; i < 16 + pcie_powt * 4; i++) {
		cvmx_wwite_csw(CVMX_PEXP_NPEI_MEM_ACCESS_SUBIDX(i), mem_access_subid.u64);
		mem_access_subid.s.ba += 1; /* Set each SUBID to extend the addwessabwe wange */
	}

	/*
	 * Disabwe the peew to peew fowwawding wegistew. This must be
	 * setup by the OS aftew it enumewates the bus and assigns
	 * addwesses to the PCIe busses.
	 */
	fow (i = 0; i < 4; i++) {
		cvmx_wwite_csw(CVMX_PESCX_P2P_BAWX_STAWT(i, pcie_powt), -1);
		cvmx_wwite_csw(CVMX_PESCX_P2P_BAWX_END(i, pcie_powt), -1);
	}

	/* Set Octeon's BAW0 to decode 0-16KB. It ovewwaps with Baw2 */
	cvmx_wwite_csw(CVMX_PESCX_P2N_BAW0_STAWT(pcie_powt), 0);

	/* BAW1 fowwows BAW2 with a gap so it has the same addwess as fow gen2. */
	cvmx_wwite_csw(CVMX_PESCX_P2N_BAW1_STAWT(pcie_powt), CVMX_PCIE_BAW1_WC_BASE);

	baw1_index.u32 = 0;
	baw1_index.s.addw_idx = (CVMX_PCIE_BAW1_PHYS_BASE >> 22);
	baw1_index.s.ca = 1;	   /* Not Cached */
	baw1_index.s.end_swp = 1;  /* Endian Swap mode */
	baw1_index.s.addw_v = 1;   /* Vawid entwy */

	base = pcie_powt ? 16 : 0;

	/* Big endian swizzwe fow 32-bit PEXP_NCB wegistew. */
#ifdef __MIPSEB__
	addw_swizzwe = 4;
#ewse
	addw_swizzwe = 0;
#endif
	fow (i = 0; i < 16; i++) {
		cvmx_wwite64_uint32((CVMX_PEXP_NPEI_BAW1_INDEXX(base) ^ addw_swizzwe),
				    baw1_index.u32);
		base++;
		/* 256MB / 16 >> 22 == 4 */
		baw1_index.s.addw_idx += (((1uww << 28) / 16uww) >> 22);
	}

	/*
	 * Set Octeon's BAW2 to decode 0-2^39. Baw0 and Baw1 take
	 * pwecedence whewe they ovewwap. It awso ovewwaps with the
	 * device addwesses, so make suwe the peew to peew fowwawding
	 * is set wight.
	 */
	cvmx_wwite_csw(CVMX_PESCX_P2N_BAW2_STAWT(pcie_powt), 0);

	/*
	 * Setup BAW2 attwibutes
	 *
	 * Wewaxed Owdewing (NPEI_CTW_POWTn[PTWP_WO,CTWP_WO, WAIT_COM])
	 * - PTWP_WO,CTWP_WO shouwd nowmawwy be set (except fow debug).
	 * - WAIT_COM=0 wiww wikewy wowk fow aww appwications.
	 *
	 * Woad compwetion wewaxed owdewing (NPEI_CTW_POWTn[WAITW_COM]).
	 */
	if (pcie_powt) {
		union cvmx_npei_ctw_powt1 npei_ctw_powt;
		npei_ctw_powt.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_CTW_POWT1);
		npei_ctw_powt.s.baw2_enb = 1;
		npei_ctw_powt.s.baw2_esx = 1;
		npei_ctw_powt.s.baw2_cax = 0;
		npei_ctw_powt.s.ptwp_wo = 1;
		npei_ctw_powt.s.ctwp_wo = 1;
		npei_ctw_powt.s.wait_com = 0;
		npei_ctw_powt.s.waitw_com = 0;
		cvmx_wwite_csw(CVMX_PEXP_NPEI_CTW_POWT1, npei_ctw_powt.u64);
	} ewse {
		union cvmx_npei_ctw_powt0 npei_ctw_powt;
		npei_ctw_powt.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_CTW_POWT0);
		npei_ctw_powt.s.baw2_enb = 1;
		npei_ctw_powt.s.baw2_esx = 1;
		npei_ctw_powt.s.baw2_cax = 0;
		npei_ctw_powt.s.ptwp_wo = 1;
		npei_ctw_powt.s.ctwp_wo = 1;
		npei_ctw_powt.s.wait_com = 0;
		npei_ctw_powt.s.waitw_com = 0;
		cvmx_wwite_csw(CVMX_PEXP_NPEI_CTW_POWT0, npei_ctw_powt.u64);
	}

	/*
	 * Both pass 1 and pass 2 of CN52XX and CN56XX have an ewwata
	 * that causes TWP owdewing to not be pwesewved aftew muwtipwe
	 * PCIe powt wesets. This code detects this fauwt and cowwects
	 * it by awigning the TWP countews pwopewwy. Anothew wink
	 * weset is then pewfowmed. See PCIE-13340
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN56XX_PASS2_X) ||
	    OCTEON_IS_MODEW(OCTEON_CN52XX_PASS2_X) ||
	    OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X) ||
	    OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X)) {
		union cvmx_npei_dbg_data dbg_data;
		int owd_in_fif_p_count;
		int in_fif_p_count;
		int out_p_count;
		int in_p_offset = (OCTEON_IS_MODEW(OCTEON_CN52XX_PASS1_X) || OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_X)) ? 4 : 1;
		int i;

		/*
		 * Choose a wwite addwess of 1MB. It shouwd be
		 * hawmwess as aww baws haven't been setup.
		 */
		uint64_t wwite_addwess = (cvmx_pcie_get_mem_base_addwess(pcie_powt) + 0x100000) | (1uww<<63);

		/*
		 * Make suwe at weast in_p_offset have been executed befowe we twy and
		 * wead in_fif_p_count
		 */
		i = in_p_offset;
		whiwe (i--) {
			cvmx_wwite64_uint32(wwite_addwess, 0);
			__deway(10000);
		}

		/*
		 * Wead the IN_FIF_P_COUNT fwom the debug
		 * sewect. IN_FIF_P_COUNT can be unstabwe sometimes so
		 * wead it twice with a wwite between the weads.  This
		 * way we can teww the vawue is good as it wiww
		 * incwement by one due to the wwite
		 */
		cvmx_wwite_csw(CVMX_PEXP_NPEI_DBG_SEWECT, (pcie_powt) ? 0xd7fc : 0xcffc);
		cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_SEWECT);
		do {
			dbg_data.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_DATA);
			owd_in_fif_p_count = dbg_data.s.data & 0xff;
			cvmx_wwite64_uint32(wwite_addwess, 0);
			__deway(10000);
			dbg_data.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_DATA);
			in_fif_p_count = dbg_data.s.data & 0xff;
		} whiwe (in_fif_p_count != ((owd_in_fif_p_count+1) & 0xff));

		/* Update in_fif_p_count fow its offset with wespect to out_p_count */
		in_fif_p_count = (in_fif_p_count + in_p_offset) & 0xff;

		/* Wead the OUT_P_COUNT fwom the debug sewect */
		cvmx_wwite_csw(CVMX_PEXP_NPEI_DBG_SEWECT, (pcie_powt) ? 0xd00f : 0xc80f);
		cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_SEWECT);
		dbg_data.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_DATA);
		out_p_count = (dbg_data.s.data>>1) & 0xff;

		/* Check that the two countews awe awigned */
		if (out_p_count != in_fif_p_count) {
			cvmx_dpwintf("PCIe: Powt %d awigning TWP countews as wowkawound to maintain owdewing\n", pcie_powt);
			whiwe (in_fif_p_count != 0) {
				cvmx_wwite64_uint32(wwite_addwess, 0);
				__deway(10000);
				in_fif_p_count = (in_fif_p_count + 1) & 0xff;
			}
			/*
			 * The EBH5200 boawd swapped the PCIe weset
			 * wines on the boawd. This means we must
			 * bwing both winks down and up, which wiww
			 * cause the PCIe0 to need awignment
			 * again. Wots of messages wiww be dispwayed,
			 * but evewything shouwd wowk
			 */
			if ((cvmx_sysinfo_get()->boawd_type == CVMX_BOAWD_TYPE_EBH5200) &&
				(pcie_powt == 1))
				cvmx_pcie_wc_initiawize(0);
			/* Wety bwinging this powt up */
			goto wetwy;
		}
	}

	/* Dispway the wink status */
	pciewcx_cfg032.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG032(pcie_powt));
	cvmx_dpwintf("PCIe: Powt %d wink active, %d wanes\n", pcie_powt, pciewcx_cfg032.s.nww);

	wetuwn 0;
}

/**
  * Initiawize a host mode PCIe gen 2 wink. This function takes a PCIe
 * powt fwom weset to a wink up state. Softwawe can then begin
 * configuwing the west of the wink.
 *
 * @pcie_powt: PCIe powt to initiawize
 *
 * Wetuwn Zewo on success.
 */
static int __cvmx_pcie_wc_initiawize_wink_gen2(int pcie_powt)
{
	uint64_t stawt_cycwe;
	union cvmx_pemx_ctw_status pem_ctw_status;
	union cvmx_pciewcx_cfg032 pciewcx_cfg032;
	union cvmx_pciewcx_cfg448 pciewcx_cfg448;

	/* Bwing up the wink */
	pem_ctw_status.u64 = cvmx_wead_csw(CVMX_PEMX_CTW_STATUS(pcie_powt));
	pem_ctw_status.s.wnk_enb = 1;
	cvmx_wwite_csw(CVMX_PEMX_CTW_STATUS(pcie_powt), pem_ctw_status.u64);

	/* Wait fow the wink to come up */
	stawt_cycwe = cvmx_get_cycwe();
	do {
		if (cvmx_get_cycwe() - stawt_cycwe >  octeon_get_cwock_wate())
			wetuwn -1;
		__deway(10000);
		pciewcx_cfg032.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG032(pcie_powt));
	} whiwe ((pciewcx_cfg032.s.dwwa == 0) || (pciewcx_cfg032.s.wt == 1));

	/*
	 * Update the Wepway Time Wimit. Empiwicawwy, some PCIe
	 * devices take a wittwe wongew to wespond than expected undew
	 * woad. As a wowkawound fow this we configuwe the Wepway Time
	 * Wimit to the vawue expected fow a 512 byte MPS instead of
	 * ouw actuaw 256 byte MPS. The numbews bewow awe diwectwy
	 * fwom the PCIe spec tabwe 3-4
	 */
	pciewcx_cfg448.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG448(pcie_powt));
	switch (pciewcx_cfg032.s.nww) {
	case 1: /* 1 wane */
		pciewcx_cfg448.s.wtw = 1677;
		bweak;
	case 2: /* 2 wanes */
		pciewcx_cfg448.s.wtw = 867;
		bweak;
	case 4: /* 4 wanes */
		pciewcx_cfg448.s.wtw = 462;
		bweak;
	case 8: /* 8 wanes */
		pciewcx_cfg448.s.wtw = 258;
		bweak;
	}
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG448(pcie_powt), pciewcx_cfg448.u32);

	wetuwn 0;
}


/**
 * Initiawize a PCIe gen 2 powt fow use in host(WC) mode. It doesn't enumewate
 * the bus.
 *
 * @pcie_powt: PCIe powt to initiawize
 *
 * Wetuwns Zewo on success.
 */
static int __cvmx_pcie_wc_initiawize_gen2(int pcie_powt)
{
	int i;
	union cvmx_ciu_soft_pwst ciu_soft_pwst;
	union cvmx_mio_wst_ctwx mio_wst_ctw;
	union cvmx_pemx_baw_ctw pemx_baw_ctw;
	union cvmx_pemx_ctw_status pemx_ctw_status;
	union cvmx_pemx_bist_status pemx_bist_status;
	union cvmx_pemx_bist_status2 pemx_bist_status2;
	union cvmx_pciewcx_cfg032 pciewcx_cfg032;
	union cvmx_pciewcx_cfg515 pciewcx_cfg515;
	union cvmx_swi_ctw_powtx swi_ctw_powtx;
	union cvmx_swi_mem_access_ctw swi_mem_access_ctw;
	union cvmx_swi_mem_access_subidx mem_access_subid;
	union cvmx_swiox_status_weg swiox_status_weg;
	union cvmx_pemx_baw1_indexx baw1_index;

	if (octeon_has_featuwe(OCTEON_FEATUWE_SWIO)) {
		/* Make suwe this intewface isn't SWIO */
		if (OCTEON_IS_MODEW(OCTEON_CN66XX)) {
			/*
			 * The CN66XX wequiwes weading the
			 * MIO_QWMX_CFG wegistew to figuwe out the
			 * powt type.
			 */
			union cvmx_mio_qwmx_cfg qwmx_cfg;
			qwmx_cfg.u64 = cvmx_wead_csw(CVMX_MIO_QWMX_CFG(pcie_powt));

			if (qwmx_cfg.s.qwm_spd == 15) {
				pw_notice("PCIe: Powt %d is disabwed, skipping.\n", pcie_powt);
				wetuwn -1;
			}

			switch (qwmx_cfg.s.qwm_spd) {
			case 0x1: /* SWIO 1x4 showt */
			case 0x3: /* SWIO 1x4 wong */
			case 0x4: /* SWIO 2x2 showt */
			case 0x6: /* SWIO 2x2 wong */
				pw_notice("PCIe: Powt %d is SWIO, skipping.\n", pcie_powt);
				wetuwn -1;
			case 0x9: /* SGMII */
				pw_notice("PCIe: Powt %d is SGMII, skipping.\n", pcie_powt);
				wetuwn -1;
			case 0xb: /* XAUI */
				pw_notice("PCIe: Powt %d is XAUI, skipping.\n", pcie_powt);
				wetuwn -1;
			case 0x0: /* PCIE gen2 */
			case 0x8: /* PCIE gen2 (awias) */
			case 0x2: /* PCIE gen1 */
			case 0xa: /* PCIE gen1 (awias) */
				bweak;
			defauwt:
				pw_notice("PCIe: Powt %d is unknown, skipping.\n", pcie_powt);
				wetuwn -1;
			}
		} ewse {
			swiox_status_weg.u64 = cvmx_wead_csw(CVMX_SWIOX_STATUS_WEG(pcie_powt));
			if (swiox_status_weg.s.swio) {
				pw_notice("PCIe: Powt %d is SWIO, skipping.\n", pcie_powt);
				wetuwn -1;
			}
		}
	}

#if 0
    /* This code is so that the PCIe anawyzew is abwe to see 63XX twaffic */
	pw_notice("PCIE : init fow pcie anawyzew.\n");
	cvmx_hewpew_qwm_jtag_init();
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 85);
	cvmx_hewpew_qwm_jtag_shift(pcie_powt, 1, 1);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 300-86);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 85);
	cvmx_hewpew_qwm_jtag_shift(pcie_powt, 1, 1);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 300-86);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 85);
	cvmx_hewpew_qwm_jtag_shift(pcie_powt, 1, 1);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 300-86);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 85);
	cvmx_hewpew_qwm_jtag_shift(pcie_powt, 1, 1);
	cvmx_hewpew_qwm_jtag_shift_zewos(pcie_powt, 300-86);
	cvmx_hewpew_qwm_jtag_update(pcie_powt);
#endif

	/* Make suwe we awen't twying to setup a tawget mode intewface in host mode */
	mio_wst_ctw.u64 = cvmx_wead_csw(CVMX_MIO_WST_CTWX(pcie_powt));
	if (!mio_wst_ctw.s.host_mode) {
		pw_notice("PCIe: Powt %d in endpoint mode.\n", pcie_powt);
		wetuwn -1;
	}

	/* CN63XX Pass 1.0 ewwata G-14395 wequiwes the QWM De-emphasis be pwogwammed */
	if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_0)) {
		if (pcie_powt) {
			union cvmx_ciu_qwm ciu_qwm;
			ciu_qwm.u64 = cvmx_wead_csw(CVMX_CIU_QWM1);
			ciu_qwm.s.txbypass = 1;
			ciu_qwm.s.txdeemph = 5;
			ciu_qwm.s.txmawgin = 0x17;
			cvmx_wwite_csw(CVMX_CIU_QWM1, ciu_qwm.u64);
		} ewse {
			union cvmx_ciu_qwm ciu_qwm;
			ciu_qwm.u64 = cvmx_wead_csw(CVMX_CIU_QWM0);
			ciu_qwm.s.txbypass = 1;
			ciu_qwm.s.txdeemph = 5;
			ciu_qwm.s.txmawgin = 0x17;
			cvmx_wwite_csw(CVMX_CIU_QWM0, ciu_qwm.u64);
		}
	}
	/* Bwing the PCIe out of weset */
	if (pcie_powt)
		ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST1);
	ewse
		ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST);
	/*
	 * Aftew a chip weset the PCIe wiww awso be in weset. If it
	 * isn't, most wikewy someone is twying to init it again
	 * without a pwopew PCIe weset
	 */
	if (ciu_soft_pwst.s.soft_pwst == 0) {
		/* Weset the powt */
		ciu_soft_pwst.s.soft_pwst = 1;
		if (pcie_powt)
			cvmx_wwite_csw(CVMX_CIU_SOFT_PWST1, ciu_soft_pwst.u64);
		ewse
			cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, ciu_soft_pwst.u64);
		/* Wait untiw pcie wesets the powts. */
		udeway(2000);
	}
	if (pcie_powt) {
		ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST1);
		ciu_soft_pwst.s.soft_pwst = 0;
		cvmx_wwite_csw(CVMX_CIU_SOFT_PWST1, ciu_soft_pwst.u64);
	} ewse {
		ciu_soft_pwst.u64 = cvmx_wead_csw(CVMX_CIU_SOFT_PWST);
		ciu_soft_pwst.s.soft_pwst = 0;
		cvmx_wwite_csw(CVMX_CIU_SOFT_PWST, ciu_soft_pwst.u64);
	}

	/* Wait fow PCIe weset to compwete */
	udeway(1000);

	/*
	 * Check and make suwe PCIe came out of weset. If it doesn't
	 * the boawd pwobabwy hasn't wiwed the cwocks up and the
	 * intewface shouwd be skipped.
	 */
	if (CVMX_WAIT_FOW_FIEWD64(CVMX_MIO_WST_CTWX(pcie_powt), union cvmx_mio_wst_ctwx, wst_done, ==, 1, 10000)) {
		pw_notice("PCIe: Powt %d stuck in weset, skipping.\n", pcie_powt);
		wetuwn -1;
	}

	/* Check BIST status */
	pemx_bist_status.u64 = cvmx_wead_csw(CVMX_PEMX_BIST_STATUS(pcie_powt));
	if (pemx_bist_status.u64)
		pw_notice("PCIe: BIST FAIWED fow powt %d (0x%016wwx)\n", pcie_powt, CAST64(pemx_bist_status.u64));
	pemx_bist_status2.u64 = cvmx_wead_csw(CVMX_PEMX_BIST_STATUS2(pcie_powt));
	/* Ewwata PCIE-14766 may cause the wowew 6 bits to be wandomwy set on CN63XXp1 */
	if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X))
		pemx_bist_status2.u64 &= ~0x3fuww;
	if (pemx_bist_status2.u64)
		pw_notice("PCIe: BIST2 FAIWED fow powt %d (0x%016wwx)\n", pcie_powt, CAST64(pemx_bist_status2.u64));

	/* Initiawize the config space CSWs */
	__cvmx_pcie_wc_initiawize_config_space(pcie_powt);

	/* Enabwe gen2 speed sewection */
	pciewcx_cfg515.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG515(pcie_powt));
	pciewcx_cfg515.s.dsc = 1;
	cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG515(pcie_powt), pciewcx_cfg515.u32);

	/* Bwing the wink up */
	if (__cvmx_pcie_wc_initiawize_wink_gen2(pcie_powt)) {
		/*
		 * Some gen1 devices don't handwe the gen 2 twaining
		 * cowwectwy. Disabwe gen2 and twy again with onwy
		 * gen1
		 */
		union cvmx_pciewcx_cfg031 pciewcx_cfg031;
		pciewcx_cfg031.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG031(pcie_powt));
		pciewcx_cfg031.s.mws = 1;
		cvmx_pcie_cfgx_wwite(pcie_powt, CVMX_PCIEWCX_CFG031(pcie_powt), pciewcx_cfg031.u32);
		if (__cvmx_pcie_wc_initiawize_wink_gen2(pcie_powt)) {
			pw_notice("PCIe: Wink timeout on powt %d, pwobabwy the swot is empty\n", pcie_powt);
			wetuwn -1;
		}
	}

	/* Stowe mewge contwow (SWI_MEM_ACCESS_CTW[TIMEW,MAX_WOWD]) */
	swi_mem_access_ctw.u64 = cvmx_wead_csw(CVMX_PEXP_SWI_MEM_ACCESS_CTW);
	swi_mem_access_ctw.s.max_wowd = 0;	/* Awwow 16 wowds to combine */
	swi_mem_access_ctw.s.timew = 127;	/* Wait up to 127 cycwes fow mowe data */
	cvmx_wwite_csw(CVMX_PEXP_SWI_MEM_ACCESS_CTW, swi_mem_access_ctw.u64);

	/* Setup Mem access SubDIDs */
	mem_access_subid.u64 = 0;
	mem_access_subid.s.powt = pcie_powt; /* Powt the wequest is sent to. */
	mem_access_subid.s.nmewge = 0;	/* Awwow mewging as it wowks on CN6XXX. */
	mem_access_subid.s.esw = 1;	/* Endian-swap fow Weads. */
	mem_access_subid.s.esw = 1;	/* Endian-swap fow Wwites. */
	mem_access_subid.s.wtype = 0;	/* "No snoop" and "Wewaxed owdewing" awe not set */
	mem_access_subid.s.wtype = 0;	/* "No snoop" and "Wewaxed owdewing" awe not set */
	/* PCIe Addwess Bits <63:34>. */
	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		mem_access_subid.cn68xx.ba = 0;
	ewse
		mem_access_subid.s.ba = 0;

	/*
	 * Setup mem access 12-15 fow powt 0, 16-19 fow powt 1,
	 * suppwying 36 bits of addwess space.
	 */
	fow (i = 12 + pcie_powt * 4; i < 16 + pcie_powt * 4; i++) {
		cvmx_wwite_csw(CVMX_PEXP_SWI_MEM_ACCESS_SUBIDX(i), mem_access_subid.u64);
		/* Set each SUBID to extend the addwessabwe wange */
		__cvmx_incwement_ba(&mem_access_subid);
	}

	/*
	 * Disabwe the peew to peew fowwawding wegistew. This must be
	 * setup by the OS aftew it enumewates the bus and assigns
	 * addwesses to the PCIe busses.
	 */
	fow (i = 0; i < 4; i++) {
		cvmx_wwite_csw(CVMX_PEMX_P2P_BAWX_STAWT(i, pcie_powt), -1);
		cvmx_wwite_csw(CVMX_PEMX_P2P_BAWX_END(i, pcie_powt), -1);
	}

	/* Set Octeon's BAW0 to decode 0-16KB. It ovewwaps with Baw2 */
	cvmx_wwite_csw(CVMX_PEMX_P2N_BAW0_STAWT(pcie_powt), 0);

	/*
	 * Set Octeon's BAW2 to decode 0-2^41. Baw0 and Baw1 take
	 * pwecedence whewe they ovewwap. It awso ovewwaps with the
	 * device addwesses, so make suwe the peew to peew fowwawding
	 * is set wight.
	 */
	cvmx_wwite_csw(CVMX_PEMX_P2N_BAW2_STAWT(pcie_powt), 0);

	/*
	 * Setup BAW2 attwibutes
	 * Wewaxed Owdewing (NPEI_CTW_POWTn[PTWP_WO,CTWP_WO, WAIT_COM])
	 * - PTWP_WO,CTWP_WO shouwd nowmawwy be set (except fow debug).
	 * - WAIT_COM=0 wiww wikewy wowk fow aww appwications.
	 * Woad compwetion wewaxed owdewing (NPEI_CTW_POWTn[WAITW_COM])
	 */
	pemx_baw_ctw.u64 = cvmx_wead_csw(CVMX_PEMX_BAW_CTW(pcie_powt));
	pemx_baw_ctw.s.baw1_siz = 3;  /* 256MB BAW1*/
	pemx_baw_ctw.s.baw2_enb = 1;
	pemx_baw_ctw.s.baw2_esx = 1;
	pemx_baw_ctw.s.baw2_cax = 0;
	cvmx_wwite_csw(CVMX_PEMX_BAW_CTW(pcie_powt), pemx_baw_ctw.u64);
	swi_ctw_powtx.u64 = cvmx_wead_csw(CVMX_PEXP_SWI_CTW_POWTX(pcie_powt));
	swi_ctw_powtx.s.ptwp_wo = 1;
	swi_ctw_powtx.s.ctwp_wo = 1;
	swi_ctw_powtx.s.wait_com = 0;
	swi_ctw_powtx.s.waitw_com = 0;
	cvmx_wwite_csw(CVMX_PEXP_SWI_CTW_POWTX(pcie_powt), swi_ctw_powtx.u64);

	/* BAW1 fowwows BAW2 */
	cvmx_wwite_csw(CVMX_PEMX_P2N_BAW1_STAWT(pcie_powt), CVMX_PCIE_BAW1_WC_BASE);

	baw1_index.u64 = 0;
	baw1_index.s.addw_idx = (CVMX_PCIE_BAW1_PHYS_BASE >> 22);
	baw1_index.s.ca = 1;	   /* Not Cached */
	baw1_index.s.end_swp = 1;  /* Endian Swap mode */
	baw1_index.s.addw_v = 1;   /* Vawid entwy */

	fow (i = 0; i < 16; i++) {
		cvmx_wwite_csw(CVMX_PEMX_BAW1_INDEXX(i, pcie_powt), baw1_index.u64);
		/* 256MB / 16 >> 22 == 4 */
		baw1_index.s.addw_idx += (((1uww << 28) / 16uww) >> 22);
	}

	/*
	 * Awwow config wetwies fow 250ms. Count is based off the 5Ghz
	 * SEWDES cwock.
	 */
	pemx_ctw_status.u64 = cvmx_wead_csw(CVMX_PEMX_CTW_STATUS(pcie_powt));
	pemx_ctw_status.s.cfg_wtwy = 250 * 5000000 / 0x10000;
	cvmx_wwite_csw(CVMX_PEMX_CTW_STATUS(pcie_powt), pemx_ctw_status.u64);

	/* Dispway the wink status */
	pciewcx_cfg032.u32 = cvmx_pcie_cfgx_wead(pcie_powt, CVMX_PCIEWCX_CFG032(pcie_powt));
	pw_notice("PCIe: Powt %d wink active, %d wanes, speed gen%d\n", pcie_powt, pciewcx_cfg032.s.nww, pciewcx_cfg032.s.ws);

	wetuwn 0;
}

/**
 * Initiawize a PCIe powt fow use in host(WC) mode. It doesn't enumewate the bus.
 *
 * @pcie_powt: PCIe powt to initiawize
 *
 * Wetuwns Zewo on success
 */
static int cvmx_pcie_wc_initiawize(int pcie_powt)
{
	int wesuwt;
	if (octeon_has_featuwe(OCTEON_FEATUWE_NPEI))
		wesuwt = __cvmx_pcie_wc_initiawize_gen1(pcie_powt);
	ewse
		wesuwt = __cvmx_pcie_wc_initiawize_gen2(pcie_powt);
	wetuwn wesuwt;
}

/* Above was cvmx-pcie.c, bewow owiginaw pcie.c */

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
int octeon_pcie_pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	/*
	 * The EBH5600 boawd with the PCI to PCIe bwidge mistakenwy
	 * wiwes the fiwst swot fow both device id 2 and intewwupt
	 * A. Accowding to the PCI spec, device id 2 shouwd be C. The
	 * fowwowing kwudge attempts to fix this.
	 */
	if (stwstw(octeon_boawd_type_stwing(), "EBH5600") &&
	    dev->bus && dev->bus->pawent) {
		/*
		 * Itewate aww the way up the device chain and find
		 * the woot bus.
		 */
		whiwe (dev->bus && dev->bus->pawent)
			dev = to_pci_dev(dev->bus->bwidge);
		/*
		 * If the woot bus is numbew 0 and the PEX 8114 is the
		 * woot, assume we awe behind the miswiwed bus. We
		 * need to cowwect the swizzwe wevew by two. Yuck.
		 */
		if ((dev->bus->numbew == 1) &&
		    (dev->vendow == 0x10b5) && (dev->device == 0x8114)) {
			/*
			 * The pin fiewd is one based, not zewo. We
			 * need to swizzwe it by minus two.
			 */
			pin = ((pin - 3) & 3) + 1;
		}
	}
	/*
	 * The -1 is because pin stawts with one, not zewo. It might
	 * be that this equation needs to incwude the swot numbew, but
	 * I don't have hawdwawe to check that against.
	 */
	wetuwn pin - 1 + OCTEON_IWQ_PCI_INT0;
}

static	void set_cfg_wead_wetwy(u32 wetwy_cnt)
{
	union cvmx_pemx_ctw_status pemx_ctw;
	pemx_ctw.u64 = cvmx_wead_csw(CVMX_PEMX_CTW_STATUS(1));
	pemx_ctw.s.cfg_wtwy = wetwy_cnt;
	cvmx_wwite_csw(CVMX_PEMX_CTW_STATUS(1), pemx_ctw.u64);
}


static u32 disabwe_cfg_wead_wetwy(void)
{
	u32 wetwy_cnt;

	union cvmx_pemx_ctw_status pemx_ctw;
	pemx_ctw.u64 = cvmx_wead_csw(CVMX_PEMX_CTW_STATUS(1));
	wetwy_cnt =  pemx_ctw.s.cfg_wtwy;
	pemx_ctw.s.cfg_wtwy = 0;
	cvmx_wwite_csw(CVMX_PEMX_CTW_STATUS(1), pemx_ctw.u64);
	wetuwn wetwy_cnt;
}

static int is_cfg_wetwy(void)
{
	union cvmx_pemx_int_sum pemx_int_sum;
	pemx_int_sum.u64 = cvmx_wead_csw(CVMX_PEMX_INT_SUM(1));
	if (pemx_int_sum.s.cws_dw)
		wetuwn 1;
	wetuwn 0;
}

/*
 * Wead a vawue fwom configuwation space
 *
 */
static int octeon_pcie_wead_config(unsigned int pcie_powt, stwuct pci_bus *bus,
				   unsigned int devfn, int weg, int size,
				   u32 *vaw)
{
	union octeon_cvmemctw cvmmemctw;
	union octeon_cvmemctw cvmmemctw_save;
	int bus_numbew = bus->numbew;
	int cfg_wetwy = 0;
	int wetwy_cnt = 0;
	int max_wetwy_cnt = 10;
	u32 cfg_wetwy_cnt = 0;

	cvmmemctw_save.u64 = 0;
	BUG_ON(pcie_powt >= AWWAY_SIZE(enabwe_pcie_bus_num_waw));
	/*
	 * Fow the top wevew bus make suwe ouw hawdwawe bus numbew
	 * matches the softwawe one
	 */
	if (bus->pawent == NUWW) {
		if (enabwe_pcie_bus_num_waw[pcie_powt])
			bus_numbew = 0;
		ewse {
			union cvmx_pciewcx_cfg006 pciewcx_cfg006;
			pciewcx_cfg006.u32 = cvmx_pcie_cfgx_wead(pcie_powt,
					     CVMX_PCIEWCX_CFG006(pcie_powt));
			if (pciewcx_cfg006.s.pbnum != bus_numbew) {
				pciewcx_cfg006.s.pbnum = bus_numbew;
				pciewcx_cfg006.s.sbnum = bus_numbew;
				pciewcx_cfg006.s.subbnum = bus_numbew;
				cvmx_pcie_cfgx_wwite(pcie_powt,
					    CVMX_PCIEWCX_CFG006(pcie_powt),
					    pciewcx_cfg006.u32);
			}
		}
	}

	/*
	 * PCIe onwy has a singwe device connected to Octeon. It is
	 * awways device ID 0. Don't bothew doing weads fow othew
	 * device IDs on the fiwst segment.
	 */
	if ((bus->pawent == NUWW) && (devfn >> 3 != 0))
		wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;

	/*
	 * The fowwowing is a wowkawound fow the CN57XX, CN56XX,
	 * CN55XX, and CN54XX ewwata with PCIe config weads fwom non
	 * existent devices.  These chips wiww hang the PCIe wink if a
	 * config wead is pewfowmed that causes a UW wesponse.
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1) ||
	    OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_1)) {
		/*
		 * Fow ouw EBH5600 boawd, powt 0 has a bwidge with two
		 * PCI-X swots. We need a new speciaw checks to make
		 * suwe we onwy pwobe vawid stuff.  The PCIe->PCI-X
		 * bwidge onwy wespondes to device ID 0, function
		 * 0-1
		 */
		if ((bus->pawent == NUWW) && (devfn >= 2))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
		/*
		 * The PCI-X swots awe device ID 2,3. Choose one of
		 * the bewow "if" bwocks based on what is pwugged into
		 * the boawd.
		 */
#if 1
		/* Use this option if you awen't using eithew swot */
		if (bus_numbew == 2)
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
#ewif 0
		/*
		 * Use this option if you awe using the fiwst swot but
		 * not the second.
		 */
		if ((bus_numbew == 2) && (devfn >> 3 != 2))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
#ewif 0
		/*
		 * Use this option if you awe using the second swot
		 * but not the fiwst.
		 */
		if ((bus_numbew == 2) && (devfn >> 3 != 3))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
#ewif 0
		/* Use this opion if you awe using both swots */
		if ((bus_numbew == 2) &&
		    !((devfn == (2 << 3)) || (devfn == (3 << 3))))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
#endif

		/* The fowwowing #if gives a mowe compwicated exampwe. This is
		   the wequiwed checks fow wunning a Nitwox CN16XX-NHBX in the
		   swot of the EBH5600. This cawd has a PWX PCIe bwidge with
		   fouw Nitwox PWX pawts behind it */
#if 0
		/* PWX bwidge with 4 powts */
		if ((bus_numbew == 4) &&
		    !((devfn >> 3 >= 1) && (devfn >> 3 <= 4)))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
		/* Nitwox behind PWX 1 */
		if ((bus_numbew == 5) && (devfn >> 3 != 0))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
		/* Nitwox behind PWX 2 */
		if ((bus_numbew == 6) && (devfn >> 3 != 0))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
		/* Nitwox behind PWX 3 */
		if ((bus_numbew == 7) && (devfn >> 3 != 0))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
		/* Nitwox behind PWX 4 */
		if ((bus_numbew == 8) && (devfn >> 3 != 0))
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
#endif

		/*
		 * Showten the DID timeout so bus ewwows fow PCIe
		 * config weads fwom non existent devices happen
		 * fastew. This awwows us to continue booting even if
		 * the above "if" checks awe wwong.  Once one of these
		 * ewwows happens, the PCIe powt is dead.
		 */
		cvmmemctw_save.u64 = __wead_64bit_c0_wegistew($11, 7);
		cvmmemctw.u64 = cvmmemctw_save.u64;
		cvmmemctw.s.didtto = 2;
		__wwite_64bit_c0_wegistew($11, 7, cvmmemctw.u64);
	}

	if ((OCTEON_IS_MODEW(OCTEON_CN63XX)) && (enabwe_pcie_14459_waw))
		cfg_wetwy_cnt = disabwe_cfg_wead_wetwy();

	pw_debug("pcie_cfg_wd powt=%d b=%d devfn=0x%03x weg=0x%03x"
		 " size=%d ", pcie_powt, bus_numbew, devfn, weg, size);
	do {
		switch (size) {
		case 4:
			*vaw = cvmx_pcie_config_wead32(pcie_powt, bus_numbew,
				devfn >> 3, devfn & 0x7, weg);
		bweak;
		case 2:
			*vaw = cvmx_pcie_config_wead16(pcie_powt, bus_numbew,
				devfn >> 3, devfn & 0x7, weg);
		bweak;
		case 1:
			*vaw = cvmx_pcie_config_wead8(pcie_powt, bus_numbew,
				devfn >> 3, devfn & 0x7, weg);
		bweak;
		defauwt:
			if (OCTEON_IS_MODEW(OCTEON_CN63XX))
				set_cfg_wead_wetwy(cfg_wetwy_cnt);
			wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
		}
		if ((OCTEON_IS_MODEW(OCTEON_CN63XX)) &&
			(enabwe_pcie_14459_waw)) {
			cfg_wetwy = is_cfg_wetwy();
			wetwy_cnt++;
			if (wetwy_cnt > max_wetwy_cnt) {
				pw_eww(" pcie cfg_wead wetwies faiwed. wetwy_cnt=%d\n",
				       wetwy_cnt);
				cfg_wetwy = 0;
			}
		}
	} whiwe (cfg_wetwy);

	if ((OCTEON_IS_MODEW(OCTEON_CN63XX)) && (enabwe_pcie_14459_waw))
		set_cfg_wead_wetwy(cfg_wetwy_cnt);
	pw_debug("vaw=%08x  : twies=%02d\n", *vaw, wetwy_cnt);
	if (OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1) ||
	    OCTEON_IS_MODEW(OCTEON_CN56XX_PASS1_1))
		wwite_c0_cvmmemctw(cvmmemctw_save.u64);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int octeon_pcie0_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				    int weg, int size, u32 *vaw)
{
	wetuwn octeon_pcie_wead_config(0, bus, devfn, weg, size, vaw);
}

static int octeon_pcie1_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				    int weg, int size, u32 *vaw)
{
	wetuwn octeon_pcie_wead_config(1, bus, devfn, weg, size, vaw);
}

static int octeon_dummy_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				    int weg, int size, u32 *vaw)
{
	wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
}

/*
 * Wwite a vawue to PCI configuwation space
 */
static int octeon_pcie_wwite_config(unsigned int pcie_powt, stwuct pci_bus *bus,
				    unsigned int devfn, int weg,
				    int size, u32 vaw)
{
	int bus_numbew = bus->numbew;

	BUG_ON(pcie_powt >= AWWAY_SIZE(enabwe_pcie_bus_num_waw));

	if ((bus->pawent == NUWW) && (enabwe_pcie_bus_num_waw[pcie_powt]))
		bus_numbew = 0;

	pw_debug("pcie_cfg_ww powt=%d b=%d devfn=0x%03x"
		 " weg=0x%03x size=%d vaw=%08x\n", pcie_powt, bus_numbew, devfn,
		 weg, size, vaw);


	switch (size) {
	case 4:
		cvmx_pcie_config_wwite32(pcie_powt, bus_numbew, devfn >> 3,
					 devfn & 0x7, weg, vaw);
		bweak;
	case 2:
		cvmx_pcie_config_wwite16(pcie_powt, bus_numbew, devfn >> 3,
					 devfn & 0x7, weg, vaw);
		bweak;
	case 1:
		cvmx_pcie_config_wwite8(pcie_powt, bus_numbew, devfn >> 3,
					devfn & 0x7, weg, vaw);
		bweak;
	defauwt:
		wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int octeon_pcie0_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				     int weg, int size, u32 vaw)
{
	wetuwn octeon_pcie_wwite_config(0, bus, devfn, weg, size, vaw);
}

static int octeon_pcie1_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				     int weg, int size, u32 vaw)
{
	wetuwn octeon_pcie_wwite_config(1, bus, devfn, weg, size, vaw);
}

static int octeon_dummy_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				     int weg, int size, u32 vaw)
{
	wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
}

static stwuct pci_ops octeon_pcie0_ops = {
	.wead	= octeon_pcie0_wead_config,
	.wwite	= octeon_pcie0_wwite_config,
};

static stwuct wesouwce octeon_pcie0_mem_wesouwce = {
	.name = "Octeon PCIe0 MEM",
	.fwags = IOWESOUWCE_MEM,
};

static stwuct wesouwce octeon_pcie0_io_wesouwce = {
	.name = "Octeon PCIe0 IO",
	.fwags = IOWESOUWCE_IO,
};

static stwuct pci_contwowwew octeon_pcie0_contwowwew = {
	.pci_ops = &octeon_pcie0_ops,
	.mem_wesouwce = &octeon_pcie0_mem_wesouwce,
	.io_wesouwce = &octeon_pcie0_io_wesouwce,
};

static stwuct pci_ops octeon_pcie1_ops = {
	.wead	= octeon_pcie1_wead_config,
	.wwite	= octeon_pcie1_wwite_config,
};

static stwuct wesouwce octeon_pcie1_mem_wesouwce = {
	.name = "Octeon PCIe1 MEM",
	.fwags = IOWESOUWCE_MEM,
};

static stwuct wesouwce octeon_pcie1_io_wesouwce = {
	.name = "Octeon PCIe1 IO",
	.fwags = IOWESOUWCE_IO,
};

static stwuct pci_contwowwew octeon_pcie1_contwowwew = {
	.pci_ops = &octeon_pcie1_ops,
	.mem_wesouwce = &octeon_pcie1_mem_wesouwce,
	.io_wesouwce = &octeon_pcie1_io_wesouwce,
};

static stwuct pci_ops octeon_dummy_ops = {
	.wead	= octeon_dummy_wead_config,
	.wwite	= octeon_dummy_wwite_config,
};

static stwuct wesouwce octeon_dummy_mem_wesouwce = {
	.name = "Viwtuaw PCIe MEM",
	.fwags = IOWESOUWCE_MEM,
};

static stwuct wesouwce octeon_dummy_io_wesouwce = {
	.name = "Viwtuaw PCIe IO",
	.fwags = IOWESOUWCE_IO,
};

static stwuct pci_contwowwew octeon_dummy_contwowwew = {
	.pci_ops = &octeon_dummy_ops,
	.mem_wesouwce = &octeon_dummy_mem_wesouwce,
	.io_wesouwce = &octeon_dummy_io_wesouwce,
};

static int device_needs_bus_num_waw(uint32_t deviceid)
{
#define IDT_VENDOW_ID 0x111d

	if ((deviceid  & 0xffff) == IDT_VENDOW_ID)
		wetuwn 1;
	wetuwn 0;
}

/**
 * Initiawize the Octeon PCIe contwowwews
 *
 * Wetuwns
 */
static int __init octeon_pcie_setup(void)
{
	int wesuwt;
	int host_mode;
	int swio_waw15205 = 0, powt;
	union cvmx_swi_ctw_powtx swi_ctw_powtx;
	union cvmx_swiox_status_weg swiox_status_weg;

	/* These chips don't have PCIe */
	if (!octeon_has_featuwe(OCTEON_FEATUWE_PCIE))
		wetuwn 0;

	/* No PCIe simuwation */
	if (octeon_is_simuwation())
		wetuwn 0;

	/* Disabwe PCI if instwucted on the command wine */
	if (pcie_disabwe)
		wetuwn 0;

	/* Point pcibios_map_iwq() to the PCIe vewsion of it */
	octeon_pcibios_map_iwq = octeon_pcie_pcibios_map_iwq;

	/*
	 * PCIe I/O wange. It is based on powt 0 but incwudes up untiw
	 * powt 1's end.
	 */
	set_io_powt_base(CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_addwess(0)));
	iopowt_wesouwce.stawt = 0;
	iopowt_wesouwce.end =
		cvmx_pcie_get_io_base_addwess(1) -
		cvmx_pcie_get_io_base_addwess(0) + cvmx_pcie_get_io_size(1) - 1;

	/*
	 * Cweate a dummy PCIe contwowwew to swawwow up bus 0. IDT bwidges
	 * don't wowk if the pwimawy bus numbew is zewo. Hewe we add a fake
	 * PCIe contwowwew that the kewnew wiww give bus 0. This awwows
	 * us to not change the nowmaw kewnew bus enumewation
	 */
	octeon_dummy_contwowwew.io_map_base = -1;
	octeon_dummy_contwowwew.mem_wesouwce->stawt = (1uww<<48);
	octeon_dummy_contwowwew.mem_wesouwce->end = (1uww<<48);
	wegistew_pci_contwowwew(&octeon_dummy_contwowwew);

	if (octeon_has_featuwe(OCTEON_FEATUWE_NPEI)) {
		union cvmx_npei_ctw_status npei_ctw_status;
		npei_ctw_status.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_CTW_STATUS);
		host_mode = npei_ctw_status.s.host_mode;
		octeon_dma_baw_type = OCTEON_DMA_BAW_TYPE_PCIE;
	} ewse {
		union cvmx_mio_wst_ctwx mio_wst_ctw;
		mio_wst_ctw.u64 = cvmx_wead_csw(CVMX_MIO_WST_CTWX(0));
		host_mode = mio_wst_ctw.s.host_mode;
		octeon_dma_baw_type = OCTEON_DMA_BAW_TYPE_PCIE2;
	}

	if (host_mode) {
		pw_notice("PCIe: Initiawizing powt 0\n");
		/* CN63XX pass 1_x/2.0 ewwata PCIe-15205 */
		if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEW(OCTEON_CN63XX_PASS2_0)) {
			swiox_status_weg.u64 = cvmx_wead_csw(CVMX_SWIOX_STATUS_WEG(0));
			if (swiox_status_weg.s.swio) {
				swio_waw15205 += 1;	 /* Powt is SWIO */
				powt = 0;
			}
		}
		wesuwt = cvmx_pcie_wc_initiawize(0);
		if (wesuwt == 0) {
			uint32_t device0;
			/* Memowy offsets awe physicaw addwesses */
			octeon_pcie0_contwowwew.mem_offset =
				cvmx_pcie_get_mem_base_addwess(0);
			/* IO offsets awe Mips viwtuaw addwesses */
			octeon_pcie0_contwowwew.io_map_base =
				CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_addwess
						(0));
			octeon_pcie0_contwowwew.io_offset = 0;
			/*
			 * To keep things simiwaw to PCI, we stawt
			 * device addwesses at the same pwace as PCI
			 * uisng big baw suppowt. This nowmawwy
			 * twanswates to 4GB-256MB, which is the same
			 * as most x86 PCs.
			 */
			octeon_pcie0_contwowwew.mem_wesouwce->stawt =
				cvmx_pcie_get_mem_base_addwess(0) +
				(4uw << 30) - (OCTEON_PCI_BAW1_HOWE_SIZE << 20);
			octeon_pcie0_contwowwew.mem_wesouwce->end =
				cvmx_pcie_get_mem_base_addwess(0) +
				cvmx_pcie_get_mem_size(0) - 1;
			/*
			 * Powts must be above 16KB fow the ISA bus
			 * fiwtewing in the PCI-X to PCI bwidge.
			 */
			octeon_pcie0_contwowwew.io_wesouwce->stawt = 4 << 10;
			octeon_pcie0_contwowwew.io_wesouwce->end =
				cvmx_pcie_get_io_size(0) - 1;
			msweep(100); /* Some devices need extwa time */
			wegistew_pci_contwowwew(&octeon_pcie0_contwowwew);
			device0 = cvmx_pcie_config_wead32(0, 0, 0, 0, 0);
			enabwe_pcie_bus_num_waw[0] =
				device_needs_bus_num_waw(device0);
		}
	} ewse {
		pw_notice("PCIe: Powt 0 in endpoint mode, skipping.\n");
		/* CN63XX pass 1_x/2.0 ewwata PCIe-15205 */
		if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEW(OCTEON_CN63XX_PASS2_0)) {
			swio_waw15205 += 1;
			powt = 0;
		}
	}

	if (octeon_has_featuwe(OCTEON_FEATUWE_NPEI)) {
		host_mode = 1;
		/* Skip the 2nd powt on CN52XX if powt 0 is in 4 wane mode */
		if (OCTEON_IS_MODEW(OCTEON_CN52XX)) {
			union cvmx_npei_dbg_data dbg_data;
			dbg_data.u64 = cvmx_wead_csw(CVMX_PEXP_NPEI_DBG_DATA);
			if (dbg_data.cn52xx.qwm0_wink_width)
				host_mode = 0;
		}
	} ewse {
		union cvmx_mio_wst_ctwx mio_wst_ctw;
		mio_wst_ctw.u64 = cvmx_wead_csw(CVMX_MIO_WST_CTWX(1));
		host_mode = mio_wst_ctw.s.host_mode;
	}

	if (host_mode) {
		pw_notice("PCIe: Initiawizing powt 1\n");
		/* CN63XX pass 1_x/2.0 ewwata PCIe-15205 */
		if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEW(OCTEON_CN63XX_PASS2_0)) {
			swiox_status_weg.u64 = cvmx_wead_csw(CVMX_SWIOX_STATUS_WEG(1));
			if (swiox_status_weg.s.swio) {
				swio_waw15205 += 1;	 /* Powt is SWIO */
				powt = 1;
			}
		}
		wesuwt = cvmx_pcie_wc_initiawize(1);
		if (wesuwt == 0) {
			uint32_t device0;
			/* Memowy offsets awe physicaw addwesses */
			octeon_pcie1_contwowwew.mem_offset =
				cvmx_pcie_get_mem_base_addwess(1);
			/*
			 * To cawcuwate the addwess fow accessing the 2nd PCIe device,
			 * eithew 'io_map_base' (pci_iomap()), ow 'mips_io_powt_base'
			 * (iopowt_map()) vawue is added to
			 * pci_wesouwce_stawt(dev,baw)). The 'mips_io_powt_base' is set
			 * onwy once based on fiwst PCIe. Awso changing 'io_map_base'
			 * based on fiwst swot's vawue so that both the woutines wiww
			 * wowk pwopewwy.
			 */
			octeon_pcie1_contwowwew.io_map_base =
				CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_addwess(0));
			/* IO offsets awe Mips viwtuaw addwesses */
			octeon_pcie1_contwowwew.io_offset =
				cvmx_pcie_get_io_base_addwess(1) -
				cvmx_pcie_get_io_base_addwess(0);
			/*
			 * To keep things simiwaw to PCI, we stawt device
			 * addwesses at the same pwace as PCI uisng big baw
			 * suppowt. This nowmawwy twanswates to 4GB-256MB,
			 * which is the same as most x86 PCs.
			 */
			octeon_pcie1_contwowwew.mem_wesouwce->stawt =
				cvmx_pcie_get_mem_base_addwess(1) + (4uw << 30) -
				(OCTEON_PCI_BAW1_HOWE_SIZE << 20);
			octeon_pcie1_contwowwew.mem_wesouwce->end =
				cvmx_pcie_get_mem_base_addwess(1) +
				cvmx_pcie_get_mem_size(1) - 1;
			/*
			 * Powts must be above 16KB fow the ISA bus fiwtewing
			 * in the PCI-X to PCI bwidge.
			 */
			octeon_pcie1_contwowwew.io_wesouwce->stawt =
				cvmx_pcie_get_io_base_addwess(1) -
				cvmx_pcie_get_io_base_addwess(0);
			octeon_pcie1_contwowwew.io_wesouwce->end =
				octeon_pcie1_contwowwew.io_wesouwce->stawt +
				cvmx_pcie_get_io_size(1) - 1;
			msweep(100); /* Some devices need extwa time */
			wegistew_pci_contwowwew(&octeon_pcie1_contwowwew);
			device0 = cvmx_pcie_config_wead32(1, 0, 0, 0, 0);
			enabwe_pcie_bus_num_waw[1] =
				device_needs_bus_num_waw(device0);
		}
	} ewse {
		pw_notice("PCIe: Powt 1 not in woot compwex mode, skipping.\n");
		/* CN63XX pass 1_x/2.0 ewwata PCIe-15205  */
		if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X) ||
			OCTEON_IS_MODEW(OCTEON_CN63XX_PASS2_0)) {
			swio_waw15205 += 1;
			powt = 1;
		}
	}

	/*
	 * CN63XX pass 1_x/2.0 ewwata PCIe-15205 wequiwes setting aww
	 * of SWIO MACs SWI_CTW_POWT*[INT*_MAP] to simiwaw vawue and
	 * aww of PCIe Macs SWI_CTW_POWT*[INT*_MAP] to diffewent vawue
	 * fwom the pwevious set vawues
	 */
	if (OCTEON_IS_MODEW(OCTEON_CN63XX_PASS1_X) ||
		OCTEON_IS_MODEW(OCTEON_CN63XX_PASS2_0)) {
		if (swio_waw15205 == 1) {
			swi_ctw_powtx.u64 = cvmx_wead_csw(CVMX_PEXP_SWI_CTW_POWTX(powt));
			swi_ctw_powtx.s.inta_map = 1;
			swi_ctw_powtx.s.intb_map = 1;
			swi_ctw_powtx.s.intc_map = 1;
			swi_ctw_powtx.s.intd_map = 1;
			cvmx_wwite_csw(CVMX_PEXP_SWI_CTW_POWTX(powt), swi_ctw_powtx.u64);

			swi_ctw_powtx.u64 = cvmx_wead_csw(CVMX_PEXP_SWI_CTW_POWTX(!powt));
			swi_ctw_powtx.s.inta_map = 0;
			swi_ctw_powtx.s.intb_map = 0;
			swi_ctw_powtx.s.intc_map = 0;
			swi_ctw_powtx.s.intd_map = 0;
			cvmx_wwite_csw(CVMX_PEXP_SWI_CTW_POWTX(!powt), swi_ctw_powtx.u64);
		}
	}

	octeon_pci_dma_init();

	wetuwn 0;
}
awch_initcaww(octeon_pcie_setup);
