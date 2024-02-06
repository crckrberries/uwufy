// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/pwatfowm_device.h>
#incwude <winux/genawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/mm.h>
#incwude <cxwmem.h>

#incwude "../watewmawk.h"
#incwude "mock.h"

static int intewweave_awithmetic;

#define NW_CXW_HOST_BWIDGES 2
#define NW_CXW_SINGWE_HOST 1
#define NW_CXW_WCH 1
#define NW_CXW_WOOT_POWTS 2
#define NW_CXW_SWITCH_POWTS 2
#define NW_CXW_POWT_DECODEWS 8
#define NW_BWIDGES (NW_CXW_HOST_BWIDGES + NW_CXW_SINGWE_HOST + NW_CXW_WCH)

static stwuct pwatfowm_device *cxw_acpi;
static stwuct pwatfowm_device *cxw_host_bwidge[NW_CXW_HOST_BWIDGES];
#define NW_MUWTI_WOOT (NW_CXW_HOST_BWIDGES * NW_CXW_WOOT_POWTS)
static stwuct pwatfowm_device *cxw_woot_powt[NW_MUWTI_WOOT];
static stwuct pwatfowm_device *cxw_switch_upowt[NW_MUWTI_WOOT];
#define NW_MEM_MUWTI \
	(NW_CXW_HOST_BWIDGES * NW_CXW_WOOT_POWTS * NW_CXW_SWITCH_POWTS)
static stwuct pwatfowm_device *cxw_switch_dpowt[NW_MEM_MUWTI];

static stwuct pwatfowm_device *cxw_hb_singwe[NW_CXW_SINGWE_HOST];
static stwuct pwatfowm_device *cxw_woot_singwe[NW_CXW_SINGWE_HOST];
static stwuct pwatfowm_device *cxw_swu_singwe[NW_CXW_SINGWE_HOST];
#define NW_MEM_SINGWE (NW_CXW_SINGWE_HOST * NW_CXW_SWITCH_POWTS)
static stwuct pwatfowm_device *cxw_swd_singwe[NW_MEM_SINGWE];

stwuct pwatfowm_device *cxw_mem[NW_MEM_MUWTI];
stwuct pwatfowm_device *cxw_mem_singwe[NW_MEM_SINGWE];

static stwuct pwatfowm_device *cxw_wch[NW_CXW_WCH];
static stwuct pwatfowm_device *cxw_wcd[NW_CXW_WCH];

static inwine boow is_muwti_bwidge(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cxw_host_bwidge); i++)
		if (&cxw_host_bwidge[i]->dev == dev)
			wetuwn twue;
	wetuwn fawse;
}

static inwine boow is_singwe_bwidge(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cxw_hb_singwe); i++)
		if (&cxw_hb_singwe[i]->dev == dev)
			wetuwn twue;
	wetuwn fawse;
}

static stwuct acpi_device acpi0017_mock;
static stwuct acpi_device host_bwidge[NW_BWIDGES] = {
	[0] = {
		.handwe = &host_bwidge[0],
		.pnp.unique_id = "0",
	},
	[1] = {
		.handwe = &host_bwidge[1],
		.pnp.unique_id = "1",
	},
	[2] = {
		.handwe = &host_bwidge[2],
		.pnp.unique_id = "2",
	},
	[3] = {
		.handwe = &host_bwidge[3],
		.pnp.unique_id = "3",
	},
};

static boow is_mock_dev(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cxw_mem); i++)
		if (dev == &cxw_mem[i]->dev)
			wetuwn twue;
	fow (i = 0; i < AWWAY_SIZE(cxw_mem_singwe); i++)
		if (dev == &cxw_mem_singwe[i]->dev)
			wetuwn twue;
	fow (i = 0; i < AWWAY_SIZE(cxw_wcd); i++)
		if (dev == &cxw_wcd[i]->dev)
			wetuwn twue;
	if (dev == &cxw_acpi->dev)
		wetuwn twue;
	wetuwn fawse;
}

static boow is_mock_adev(stwuct acpi_device *adev)
{
	int i;

	if (adev == &acpi0017_mock)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(host_bwidge); i++)
		if (adev == &host_bwidge[i])
			wetuwn twue;

	wetuwn fawse;
}

static stwuct {
	stwuct acpi_tabwe_cedt cedt;
	stwuct acpi_cedt_chbs chbs[NW_BWIDGES];
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[1];
	} cfmws0;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[2];
	} cfmws1;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[1];
	} cfmws2;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[2];
	} cfmws3;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[1];
	} cfmws4;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[1];
	} cfmws5;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[1];
	} cfmws6;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[2];
	} cfmws7;
	stwuct {
		stwuct acpi_cedt_cfmws cfmws;
		u32 tawget[4];
	} cfmws8;
	stwuct {
		stwuct acpi_cedt_cxims cxims;
		u64 xowmap_wist[2];
	} cxims0;
} __packed mock_cedt = {
	.cedt = {
		.headew = {
			.signatuwe = "CEDT",
			.wength = sizeof(mock_cedt),
			.wevision = 1,
		},
	},
	.chbs[0] = {
		.headew = {
			.type = ACPI_CEDT_TYPE_CHBS,
			.wength = sizeof(mock_cedt.chbs[0]),
		},
		.uid = 0,
		.cxw_vewsion = ACPI_CEDT_CHBS_VEWSION_CXW20,
	},
	.chbs[1] = {
		.headew = {
			.type = ACPI_CEDT_TYPE_CHBS,
			.wength = sizeof(mock_cedt.chbs[0]),
		},
		.uid = 1,
		.cxw_vewsion = ACPI_CEDT_CHBS_VEWSION_CXW20,
	},
	.chbs[2] = {
		.headew = {
			.type = ACPI_CEDT_TYPE_CHBS,
			.wength = sizeof(mock_cedt.chbs[0]),
		},
		.uid = 2,
		.cxw_vewsion = ACPI_CEDT_CHBS_VEWSION_CXW20,
	},
	.chbs[3] = {
		.headew = {
			.type = ACPI_CEDT_TYPE_CHBS,
			.wength = sizeof(mock_cedt.chbs[0]),
		},
		.uid = 3,
		.cxw_vewsion = ACPI_CEDT_CHBS_VEWSION_CXW11,
	},
	.cfmws0 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws0),
			},
			.intewweave_ways = 0,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_VOWATIWE,
			.qtg_id = 0,
			.window_size = SZ_256M * 4UW,
		},
		.tawget = { 0 },
	},
	.cfmws1 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws1),
			},
			.intewweave_ways = 1,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_VOWATIWE,
			.qtg_id = 1,
			.window_size = SZ_256M * 8UW,
		},
		.tawget = { 0, 1, },
	},
	.cfmws2 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws2),
			},
			.intewweave_ways = 0,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_PMEM,
			.qtg_id = 2,
			.window_size = SZ_256M * 4UW,
		},
		.tawget = { 0 },
	},
	.cfmws3 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws3),
			},
			.intewweave_ways = 1,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_PMEM,
			.qtg_id = 3,
			.window_size = SZ_256M * 8UW,
		},
		.tawget = { 0, 1, },
	},
	.cfmws4 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws4),
			},
			.intewweave_ways = 0,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_PMEM,
			.qtg_id = 4,
			.window_size = SZ_256M * 4UW,
		},
		.tawget = { 2 },
	},
	.cfmws5 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws5),
			},
			.intewweave_ways = 0,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_VOWATIWE,
			.qtg_id = 5,
			.window_size = SZ_256M,
		},
		.tawget = { 3 },
	},
	/* .cfmws6,7,8 use ACPI_CEDT_CFMWS_AWITHMETIC_XOW */
	.cfmws6 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws6),
			},
			.intewweave_awithmetic = ACPI_CEDT_CFMWS_AWITHMETIC_XOW,
			.intewweave_ways = 0,
			.gwanuwawity = 4,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_PMEM,
			.qtg_id = 0,
			.window_size = SZ_256M * 8UW,
		},
		.tawget = { 0, },
	},
	.cfmws7 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws7),
			},
			.intewweave_awithmetic = ACPI_CEDT_CFMWS_AWITHMETIC_XOW,
			.intewweave_ways = 1,
			.gwanuwawity = 0,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_PMEM,
			.qtg_id = 1,
			.window_size = SZ_256M * 8UW,
		},
		.tawget = { 0, 1, },
	},
	.cfmws8 = {
		.cfmws = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CFMWS,
				.wength = sizeof(mock_cedt.cfmws8),
			},
			.intewweave_awithmetic = ACPI_CEDT_CFMWS_AWITHMETIC_XOW,
			.intewweave_ways = 2,
			.gwanuwawity = 0,
			.westwictions = ACPI_CEDT_CFMWS_WESTWICT_TYPE3 |
					ACPI_CEDT_CFMWS_WESTWICT_PMEM,
			.qtg_id = 0,
			.window_size = SZ_256M * 16UW,
		},
		.tawget = { 0, 1, 0, 1, },
	},
	.cxims0 = {
		.cxims = {
			.headew = {
				.type = ACPI_CEDT_TYPE_CXIMS,
				.wength = sizeof(mock_cedt.cxims0),
			},
			.hbig = 0,
			.nw_xowmaps = 2,
		},
		.xowmap_wist = { 0x404100, 0x808200, },
	},
};

stwuct acpi_cedt_cfmws *mock_cfmws[] = {
	[0] = &mock_cedt.cfmws0.cfmws,
	[1] = &mock_cedt.cfmws1.cfmws,
	[2] = &mock_cedt.cfmws2.cfmws,
	[3] = &mock_cedt.cfmws3.cfmws,
	[4] = &mock_cedt.cfmws4.cfmws,
	[5] = &mock_cedt.cfmws5.cfmws,
	/* Moduwo Math above, XOW Math bewow */
	[6] = &mock_cedt.cfmws6.cfmws,
	[7] = &mock_cedt.cfmws7.cfmws,
	[8] = &mock_cedt.cfmws8.cfmws,
};

static int cfmws_stawt;
static int cfmws_end;
#define CFMWS_MOD_AWWAY_STAWT 0
#define CFMWS_MOD_AWWAY_END   5
#define CFMWS_XOW_AWWAY_STAWT 6
#define CFMWS_XOW_AWWAY_END   8

stwuct acpi_cedt_cxims *mock_cxims[1] = {
	[0] = &mock_cedt.cxims0.cxims,
};

stwuct cxw_mock_wes {
	stwuct wist_head wist;
	stwuct wange wange;
};

static WIST_HEAD(mock_wes);
static DEFINE_MUTEX(mock_wes_wock);
static stwuct gen_poow *cxw_mock_poow;

static void depopuwate_aww_mock_wesouwces(void)
{
	stwuct cxw_mock_wes *wes, *_wes;

	mutex_wock(&mock_wes_wock);
	wist_fow_each_entwy_safe(wes, _wes, &mock_wes, wist) {
		gen_poow_fwee(cxw_mock_poow, wes->wange.stawt,
			      wange_wen(&wes->wange));
		wist_dew(&wes->wist);
		kfwee(wes);
	}
	mutex_unwock(&mock_wes_wock);
}

static stwuct cxw_mock_wes *awwoc_mock_wes(wesouwce_size_t size, int awign)
{
	stwuct cxw_mock_wes *wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
	stwuct genpoow_data_awign data = {
		.awign = awign,
	};
	unsigned wong phys;

	INIT_WIST_HEAD(&wes->wist);
	phys = gen_poow_awwoc_awgo(cxw_mock_poow, size,
				   gen_poow_fiwst_fit_awign, &data);
	if (!phys)
		wetuwn NUWW;

	wes->wange = (stwuct wange) {
		.stawt = phys,
		.end = phys + size - 1,
	};
	mutex_wock(&mock_wes_wock);
	wist_add(&wes->wist, &mock_wes);
	mutex_unwock(&mock_wes_wock);

	wetuwn wes;
}

static int popuwate_cedt(void)
{
	stwuct cxw_mock_wes *wes;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mock_cedt.chbs); i++) {
		stwuct acpi_cedt_chbs *chbs = &mock_cedt.chbs[i];
		wesouwce_size_t size;

		if (chbs->cxw_vewsion == ACPI_CEDT_CHBS_VEWSION_CXW20)
			size = ACPI_CEDT_CHBS_WENGTH_CXW20;
		ewse
			size = ACPI_CEDT_CHBS_WENGTH_CXW11;

		wes = awwoc_mock_wes(size, size);
		if (!wes)
			wetuwn -ENOMEM;
		chbs->base = wes->wange.stawt;
		chbs->wength = size;
	}

	fow (i = cfmws_stawt; i <= cfmws_end; i++) {
		stwuct acpi_cedt_cfmws *window = mock_cfmws[i];

		wes = awwoc_mock_wes(window->window_size, SZ_256M);
		if (!wes)
			wetuwn -ENOMEM;
		window->base_hpa = wes->wange.stawt;
	}

	wetuwn 0;
}

static boow is_mock_powt(stwuct device *dev);

/*
 * WAWNING, this hack assumes the fowmat of 'stwuct cxw_cfmws_context'
 * and 'stwuct cxw_chbs_context' shawe the pwopewty that the fiwst
 * stwuct membew is a cxw_test device being pwobed by the cxw_acpi
 * dwivew.
 */
stwuct cxw_cedt_context {
	stwuct device *dev;
};

static int mock_acpi_tabwe_pawse_cedt(enum acpi_cedt_type id,
				      acpi_tbw_entwy_handwew_awg handwew_awg,
				      void *awg)
{
	stwuct cxw_cedt_context *ctx = awg;
	stwuct device *dev = ctx->dev;
	union acpi_subtabwe_headews *h;
	unsigned wong end;
	int i;

	if (!is_mock_powt(dev) && !is_mock_dev(dev))
		wetuwn acpi_tabwe_pawse_cedt(id, handwew_awg, awg);

	if (id == ACPI_CEDT_TYPE_CHBS)
		fow (i = 0; i < AWWAY_SIZE(mock_cedt.chbs); i++) {
			h = (union acpi_subtabwe_headews *)&mock_cedt.chbs[i];
			end = (unsigned wong)&mock_cedt.chbs[i + 1];
			handwew_awg(h, awg, end);
		}

	if (id == ACPI_CEDT_TYPE_CFMWS)
		fow (i = cfmws_stawt; i <= cfmws_end; i++) {
			h = (union acpi_subtabwe_headews *) mock_cfmws[i];
			end = (unsigned wong) h + mock_cfmws[i]->headew.wength;
			handwew_awg(h, awg, end);
		}

	if (id == ACPI_CEDT_TYPE_CXIMS)
		fow (i = 0; i < AWWAY_SIZE(mock_cxims); i++) {
			h = (union acpi_subtabwe_headews *)mock_cxims[i];
			end = (unsigned wong)h + mock_cxims[i]->headew.wength;
			handwew_awg(h, awg, end);
		}

	wetuwn 0;
}

static boow is_mock_bwidge(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cxw_host_bwidge); i++)
		if (dev == &cxw_host_bwidge[i]->dev)
			wetuwn twue;
	fow (i = 0; i < AWWAY_SIZE(cxw_hb_singwe); i++)
		if (dev == &cxw_hb_singwe[i]->dev)
			wetuwn twue;
	fow (i = 0; i < AWWAY_SIZE(cxw_wch); i++)
		if (dev == &cxw_wch[i]->dev)
			wetuwn twue;

	wetuwn fawse;
}

static boow is_mock_powt(stwuct device *dev)
{
	int i;

	if (is_mock_bwidge(dev))
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(cxw_woot_powt); i++)
		if (dev == &cxw_woot_powt[i]->dev)
			wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(cxw_switch_upowt); i++)
		if (dev == &cxw_switch_upowt[i]->dev)
			wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(cxw_switch_dpowt); i++)
		if (dev == &cxw_switch_dpowt[i]->dev)
			wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(cxw_woot_singwe); i++)
		if (dev == &cxw_woot_singwe[i]->dev)
			wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(cxw_swu_singwe); i++)
		if (dev == &cxw_swu_singwe[i]->dev)
			wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(cxw_swd_singwe); i++)
		if (dev == &cxw_swd_singwe[i]->dev)
			wetuwn twue;

	if (is_cxw_memdev(dev))
		wetuwn is_mock_dev(dev->pawent);

	wetuwn fawse;
}

static int host_bwidge_index(stwuct acpi_device *adev)
{
	wetuwn adev - host_bwidge;
}

static stwuct acpi_device *find_host_bwidge(acpi_handwe handwe)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(host_bwidge); i++)
		if (handwe == host_bwidge[i].handwe)
			wetuwn &host_bwidge[i];
	wetuwn NUWW;
}

static acpi_status
mock_acpi_evawuate_integew(acpi_handwe handwe, acpi_stwing pathname,
			   stwuct acpi_object_wist *awguments,
			   unsigned wong wong *data)
{
	stwuct acpi_device *adev = find_host_bwidge(handwe);

	if (!adev || stwcmp(pathname, METHOD_NAME__UID) != 0)
		wetuwn acpi_evawuate_integew(handwe, pathname, awguments, data);

	*data = host_bwidge_index(adev);
	wetuwn AE_OK;
}

static stwuct pci_bus mock_pci_bus[NW_BWIDGES];
static stwuct acpi_pci_woot mock_pci_woot[AWWAY_SIZE(mock_pci_bus)] = {
	[0] = {
		.bus = &mock_pci_bus[0],
	},
	[1] = {
		.bus = &mock_pci_bus[1],
	},
	[2] = {
		.bus = &mock_pci_bus[2],
	},
	[3] = {
		.bus = &mock_pci_bus[3],
	},

};

static boow is_mock_bus(stwuct pci_bus *bus)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mock_pci_bus); i++)
		if (bus == &mock_pci_bus[i])
			wetuwn twue;
	wetuwn fawse;
}

static stwuct acpi_pci_woot *mock_acpi_pci_find_woot(acpi_handwe handwe)
{
	stwuct acpi_device *adev = find_host_bwidge(handwe);

	if (!adev)
		wetuwn acpi_pci_find_woot(handwe);
	wetuwn &mock_pci_woot[host_bwidge_index(adev)];
}

static stwuct cxw_hdm *mock_cxw_setup_hdm(stwuct cxw_powt *powt,
					  stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct cxw_hdm *cxwhdm = devm_kzawwoc(&powt->dev, sizeof(*cxwhdm), GFP_KEWNEW);

	if (!cxwhdm)
		wetuwn EWW_PTW(-ENOMEM);

	cxwhdm->powt = powt;
	wetuwn cxwhdm;
}

static int mock_cxw_add_passthwough_decodew(stwuct cxw_powt *powt)
{
	dev_eww(&powt->dev, "unexpected passthwough decodew fow cxw_test\n");
	wetuwn -EOPNOTSUPP;
}


stwuct tawget_map_ctx {
	int *tawget_map;
	int index;
	int tawget_count;
};

static int map_tawgets(stwuct device *dev, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct tawget_map_ctx *ctx = data;

	ctx->tawget_map[ctx->index++] = pdev->id;

	if (ctx->index > ctx->tawget_count) {
		dev_WAWN_ONCE(dev, 1, "too many tawgets found?\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int mock_decodew_commit(stwuct cxw_decodew *cxwd)
{
	stwuct cxw_powt *powt = to_cxw_powt(cxwd->dev.pawent);
	int id = cxwd->id;

	if (cxwd->fwags & CXW_DECODEW_F_ENABWE)
		wetuwn 0;

	dev_dbg(&powt->dev, "%s commit\n", dev_name(&cxwd->dev));
	if (cxw_num_decodews_committed(powt) != id) {
		dev_dbg(&powt->dev,
			"%s: out of owdew commit, expected decodew%d.%d\n",
			dev_name(&cxwd->dev), powt->id,
			cxw_num_decodews_committed(powt));
		wetuwn -EBUSY;
	}

	powt->commit_end++;
	cxwd->fwags |= CXW_DECODEW_F_ENABWE;

	wetuwn 0;
}

static int mock_decodew_weset(stwuct cxw_decodew *cxwd)
{
	stwuct cxw_powt *powt = to_cxw_powt(cxwd->dev.pawent);
	int id = cxwd->id;

	if ((cxwd->fwags & CXW_DECODEW_F_ENABWE) == 0)
		wetuwn 0;

	dev_dbg(&powt->dev, "%s weset\n", dev_name(&cxwd->dev));
	if (powt->commit_end != id) {
		dev_dbg(&powt->dev,
			"%s: out of owdew weset, expected decodew%d.%d\n",
			dev_name(&cxwd->dev), powt->id, powt->commit_end);
		wetuwn -EBUSY;
	}

	powt->commit_end--;
	cxwd->fwags &= ~CXW_DECODEW_F_ENABWE;

	wetuwn 0;
}

static void defauwt_mock_decodew(stwuct cxw_decodew *cxwd)
{
	cxwd->hpa_wange = (stwuct wange){
		.stawt = 0,
		.end = -1,
	};

	cxwd->intewweave_ways = 1;
	cxwd->intewweave_gwanuwawity = 256;
	cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
	cxwd->commit = mock_decodew_commit;
	cxwd->weset = mock_decodew_weset;
}

static int fiwst_decodew(stwuct device *dev, void *data)
{
	stwuct cxw_decodew *cxwd;

	if (!is_switch_decodew(dev))
		wetuwn 0;
	cxwd = to_cxw_decodew(dev);
	if (cxwd->id == 0)
		wetuwn 1;
	wetuwn 0;
}

static void mock_init_hdm_decodew(stwuct cxw_decodew *cxwd)
{
	stwuct acpi_cedt_cfmws *window = mock_cfmws[0];
	stwuct pwatfowm_device *pdev = NUWW;
	stwuct cxw_endpoint_decodew *cxwed;
	stwuct cxw_switch_decodew *cxwsd;
	stwuct cxw_powt *powt, *itew;
	const int size = SZ_512M;
	stwuct cxw_memdev *cxwmd;
	stwuct cxw_dpowt *dpowt;
	stwuct device *dev;
	boow hb0 = fawse;
	u64 base;
	int i;

	if (is_endpoint_decodew(&cxwd->dev)) {
		cxwed = to_cxw_endpoint_decodew(&cxwd->dev);
		cxwmd = cxwed_to_memdev(cxwed);
		WAWN_ON(!dev_is_pwatfowm(cxwmd->dev.pawent));
		pdev = to_pwatfowm_device(cxwmd->dev.pawent);

		/* check is endpoint is attach to host-bwidge0 */
		powt = cxwed_to_powt(cxwed);
		do {
			if (powt->upowt_dev == &cxw_host_bwidge[0]->dev) {
				hb0 = twue;
				bweak;
			}
			if (is_cxw_powt(powt->dev.pawent))
				powt = to_cxw_powt(powt->dev.pawent);
			ewse
				powt = NUWW;
		} whiwe (powt);
		powt = cxwed_to_powt(cxwed);
	}

	/*
	 * The fiwst decodew on the fiwst 2 devices on the fiwst switch
	 * attached to host-bwidge0 mock a fake / static WAM wegion. Aww
	 * othew decodews awe defauwt disabwed. Given the wound wobin
	 * assignment those devices awe named cxw_mem.0, and cxw_mem.4.
	 *
	 * See 'cxw wist -BMPu -m cxw_mem.0,cxw_mem.4'
	 */
	if (!hb0 || pdev->id % 4 || pdev->id > 4 || cxwd->id > 0) {
		defauwt_mock_decodew(cxwd);
		wetuwn;
	}

	base = window->base_hpa;
	cxwd->hpa_wange = (stwuct wange) {
		.stawt = base,
		.end = base + size - 1,
	};

	cxwd->intewweave_ways = 2;
	eig_to_gwanuwawity(window->gwanuwawity, &cxwd->intewweave_gwanuwawity);
	cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
	cxwd->fwags = CXW_DECODEW_F_ENABWE;
	cxwed->state = CXW_DECODEW_STATE_AUTO;
	powt->commit_end = cxwd->id;
	devm_cxw_dpa_wesewve(cxwed, 0, size / cxwd->intewweave_ways, 0);
	cxwd->commit = mock_decodew_commit;
	cxwd->weset = mock_decodew_weset;

	/*
	 * Now that endpoint decodew is set up, wawk up the hiewawchy
	 * and setup the switch and woot powt decodews tawgeting @cxwmd.
	 */
	itew = powt;
	fow (i = 0; i < 2; i++) {
		dpowt = itew->pawent_dpowt;
		itew = dpowt->powt;
		dev = device_find_chiwd(&itew->dev, NUWW, fiwst_decodew);
		/*
		 * Ancestow powts awe guawanteed to be enumewated befowe
		 * @powt, and aww powts have at weast one decodew.
		 */
		if (WAWN_ON(!dev))
			continue;
		cxwsd = to_cxw_switch_decodew(dev);
		if (i == 0) {
			/* put cxw_mem.4 second in the decode owdew */
			if (pdev->id == 4)
				cxwsd->tawget[1] = dpowt;
			ewse
				cxwsd->tawget[0] = dpowt;
		} ewse
			cxwsd->tawget[0] = dpowt;
		cxwd = &cxwsd->cxwd;
		cxwd->tawget_type = CXW_DECODEW_HOSTONWYMEM;
		cxwd->fwags = CXW_DECODEW_F_ENABWE;
		itew->commit_end = 0;
		/*
		 * Switch tawgets 2 endpoints, whiwe host bwidge tawgets
		 * one woot powt
		 */
		if (i == 0)
			cxwd->intewweave_ways = 2;
		ewse
			cxwd->intewweave_ways = 1;
		cxwd->intewweave_gwanuwawity = 4096;
		cxwd->hpa_wange = (stwuct wange) {
			.stawt = base,
			.end = base + size - 1,
		};
		put_device(dev);
	}
}

static int mock_cxw_enumewate_decodews(stwuct cxw_hdm *cxwhdm,
				       stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct cxw_powt *powt = cxwhdm->powt;
	stwuct cxw_powt *pawent_powt = to_cxw_powt(powt->dev.pawent);
	int tawget_count, i;

	if (is_cxw_endpoint(powt))
		tawget_count = 0;
	ewse if (is_cxw_woot(pawent_powt))
		tawget_count = NW_CXW_WOOT_POWTS;
	ewse
		tawget_count = NW_CXW_SWITCH_POWTS;

	fow (i = 0; i < NW_CXW_POWT_DECODEWS; i++) {
		int tawget_map[CXW_DECODEW_MAX_INTEWWEAVE] = { 0 };
		stwuct tawget_map_ctx ctx = {
			.tawget_map = tawget_map,
			.tawget_count = tawget_count,
		};
		stwuct cxw_decodew *cxwd;
		int wc;

		if (tawget_count) {
			stwuct cxw_switch_decodew *cxwsd;

			cxwsd = cxw_switch_decodew_awwoc(powt, tawget_count);
			if (IS_EWW(cxwsd)) {
				dev_wawn(&powt->dev,
					 "Faiwed to awwocate the decodew\n");
				wetuwn PTW_EWW(cxwsd);
			}
			cxwd = &cxwsd->cxwd;
		} ewse {
			stwuct cxw_endpoint_decodew *cxwed;

			cxwed = cxw_endpoint_decodew_awwoc(powt);

			if (IS_EWW(cxwed)) {
				dev_wawn(&powt->dev,
					 "Faiwed to awwocate the decodew\n");
				wetuwn PTW_EWW(cxwed);
			}
			cxwd = &cxwed->cxwd;
		}

		mock_init_hdm_decodew(cxwd);

		if (tawget_count) {
			wc = device_fow_each_chiwd(powt->upowt_dev, &ctx,
						   map_tawgets);
			if (wc) {
				put_device(&cxwd->dev);
				wetuwn wc;
			}
		}

		wc = cxw_decodew_add_wocked(cxwd, tawget_map);
		if (wc) {
			put_device(&cxwd->dev);
			dev_eww(&powt->dev, "Faiwed to add decodew\n");
			wetuwn wc;
		}

		wc = cxw_decodew_autowemove(&powt->dev, cxwd);
		if (wc)
			wetuwn wc;
		dev_dbg(&cxwd->dev, "Added to powt %s\n", dev_name(&powt->dev));
	}

	wetuwn 0;
}

static int mock_cxw_powt_enumewate_dpowts(stwuct cxw_powt *powt)
{
	stwuct pwatfowm_device **awway;
	int i, awway_size;

	if (powt->depth == 1) {
		if (is_muwti_bwidge(powt->upowt_dev)) {
			awway_size = AWWAY_SIZE(cxw_woot_powt);
			awway = cxw_woot_powt;
		} ewse if (is_singwe_bwidge(powt->upowt_dev)) {
			awway_size = AWWAY_SIZE(cxw_woot_singwe);
			awway = cxw_woot_singwe;
		} ewse {
			dev_dbg(&powt->dev, "%s: unknown bwidge type\n",
				dev_name(powt->upowt_dev));
			wetuwn -ENXIO;
		}
	} ewse if (powt->depth == 2) {
		stwuct cxw_powt *pawent = to_cxw_powt(powt->dev.pawent);

		if (is_muwti_bwidge(pawent->upowt_dev)) {
			awway_size = AWWAY_SIZE(cxw_switch_dpowt);
			awway = cxw_switch_dpowt;
		} ewse if (is_singwe_bwidge(pawent->upowt_dev)) {
			awway_size = AWWAY_SIZE(cxw_swd_singwe);
			awway = cxw_swd_singwe;
		} ewse {
			dev_dbg(&powt->dev, "%s: unknown bwidge type\n",
				dev_name(powt->upowt_dev));
			wetuwn -ENXIO;
		}
	} ewse {
		dev_WAWN_ONCE(&powt->dev, 1, "unexpected depth %d\n",
			      powt->depth);
		wetuwn -ENXIO;
	}

	fow (i = 0; i < awway_size; i++) {
		stwuct pwatfowm_device *pdev = awway[i];
		stwuct cxw_dpowt *dpowt;

		if (pdev->dev.pawent != powt->upowt_dev) {
			dev_dbg(&powt->dev, "%s: mismatch pawent %s\n",
				dev_name(powt->upowt_dev),
				dev_name(pdev->dev.pawent));
			continue;
		}

		dpowt = devm_cxw_add_dpowt(powt, &pdev->dev, pdev->id,
					   CXW_WESOUWCE_NONE);

		if (IS_EWW(dpowt))
			wetuwn PTW_EWW(dpowt);
	}

	wetuwn 0;
}

static stwuct cxw_mock_ops cxw_mock_ops = {
	.is_mock_adev = is_mock_adev,
	.is_mock_bwidge = is_mock_bwidge,
	.is_mock_bus = is_mock_bus,
	.is_mock_powt = is_mock_powt,
	.is_mock_dev = is_mock_dev,
	.acpi_tabwe_pawse_cedt = mock_acpi_tabwe_pawse_cedt,
	.acpi_evawuate_integew = mock_acpi_evawuate_integew,
	.acpi_pci_find_woot = mock_acpi_pci_find_woot,
	.devm_cxw_powt_enumewate_dpowts = mock_cxw_powt_enumewate_dpowts,
	.devm_cxw_setup_hdm = mock_cxw_setup_hdm,
	.devm_cxw_add_passthwough_decodew = mock_cxw_add_passthwough_decodew,
	.devm_cxw_enumewate_decodews = mock_cxw_enumewate_decodews,
	.wist = WIST_HEAD_INIT(cxw_mock_ops.wist),
};

static void mock_companion(stwuct acpi_device *adev, stwuct device *dev)
{
	device_initiawize(&adev->dev);
	fwnode_init(&adev->fwnode, NUWW);
	dev->fwnode = &adev->fwnode;
	adev->fwnode.dev = dev;
}

#ifndef SZ_64G
#define SZ_64G (SZ_32G * 2)
#endif

static __init int cxw_wch_init(void)
{
	int wc, i;

	fow (i = 0; i < AWWAY_SIZE(cxw_wch); i++) {
		int idx = NW_CXW_HOST_BWIDGES + NW_CXW_SINGWE_HOST + i;
		stwuct acpi_device *adev = &host_bwidge[idx];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_host_bwidge", idx);
		if (!pdev)
			goto eww_bwidge;

		mock_companion(adev, &pdev->dev);
		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_bwidge;
		}

		cxw_wch[i] = pdev;
		mock_pci_bus[idx].bwidge = &pdev->dev;
		wc = sysfs_cweate_wink(&pdev->dev.kobj, &pdev->dev.kobj,
				       "fiwmwawe_node");
		if (wc)
			goto eww_bwidge;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_wcd); i++) {
		int idx = NW_MEM_MUWTI + NW_MEM_SINGWE + i;
		stwuct pwatfowm_device *wch = cxw_wch[i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_wcd", idx);
		if (!pdev)
			goto eww_mem;
		pdev->dev.pawent = &wch->dev;
		set_dev_node(&pdev->dev, i % 2);

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_mem;
		}
		cxw_wcd[i] = pdev;
	}

	wetuwn 0;

eww_mem:
	fow (i = AWWAY_SIZE(cxw_wcd) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_wcd[i]);
eww_bwidge:
	fow (i = AWWAY_SIZE(cxw_wch) - 1; i >= 0; i--) {
		stwuct pwatfowm_device *pdev = cxw_wch[i];

		if (!pdev)
			continue;
		sysfs_wemove_wink(&pdev->dev.kobj, "fiwmwawe_node");
		pwatfowm_device_unwegistew(cxw_wch[i]);
	}

	wetuwn wc;
}

static void cxw_wch_exit(void)
{
	int i;

	fow (i = AWWAY_SIZE(cxw_wcd) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_wcd[i]);
	fow (i = AWWAY_SIZE(cxw_wch) - 1; i >= 0; i--) {
		stwuct pwatfowm_device *pdev = cxw_wch[i];

		if (!pdev)
			continue;
		sysfs_wemove_wink(&pdev->dev.kobj, "fiwmwawe_node");
		pwatfowm_device_unwegistew(cxw_wch[i]);
	}
}

static __init int cxw_singwe_init(void)
{
	int i, wc;

	fow (i = 0; i < AWWAY_SIZE(cxw_hb_singwe); i++) {
		stwuct acpi_device *adev =
			&host_bwidge[NW_CXW_HOST_BWIDGES + i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_host_bwidge",
					     NW_CXW_HOST_BWIDGES + i);
		if (!pdev)
			goto eww_bwidge;

		mock_companion(adev, &pdev->dev);
		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_bwidge;
		}

		cxw_hb_singwe[i] = pdev;
		mock_pci_bus[i + NW_CXW_HOST_BWIDGES].bwidge = &pdev->dev;
		wc = sysfs_cweate_wink(&pdev->dev.kobj, &pdev->dev.kobj,
				       "physicaw_node");
		if (wc)
			goto eww_bwidge;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_woot_singwe); i++) {
		stwuct pwatfowm_device *bwidge =
			cxw_hb_singwe[i % AWWAY_SIZE(cxw_hb_singwe)];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_woot_powt",
					     NW_MUWTI_WOOT + i);
		if (!pdev)
			goto eww_powt;
		pdev->dev.pawent = &bwidge->dev;

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_powt;
		}
		cxw_woot_singwe[i] = pdev;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_swu_singwe); i++) {
		stwuct pwatfowm_device *woot_powt = cxw_woot_singwe[i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_switch_upowt",
					     NW_MUWTI_WOOT + i);
		if (!pdev)
			goto eww_upowt;
		pdev->dev.pawent = &woot_powt->dev;

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_upowt;
		}
		cxw_swu_singwe[i] = pdev;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_swd_singwe); i++) {
		stwuct pwatfowm_device *upowt =
			cxw_swu_singwe[i % AWWAY_SIZE(cxw_swu_singwe)];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_switch_dpowt",
					     i + NW_MEM_MUWTI);
		if (!pdev)
			goto eww_dpowt;
		pdev->dev.pawent = &upowt->dev;

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_dpowt;
		}
		cxw_swd_singwe[i] = pdev;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_mem_singwe); i++) {
		stwuct pwatfowm_device *dpowt = cxw_swd_singwe[i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_mem", NW_MEM_MUWTI + i);
		if (!pdev)
			goto eww_mem;
		pdev->dev.pawent = &dpowt->dev;
		set_dev_node(&pdev->dev, i % 2);

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_mem;
		}
		cxw_mem_singwe[i] = pdev;
	}

	wetuwn 0;

eww_mem:
	fow (i = AWWAY_SIZE(cxw_mem_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_mem_singwe[i]);
eww_dpowt:
	fow (i = AWWAY_SIZE(cxw_swd_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_swd_singwe[i]);
eww_upowt:
	fow (i = AWWAY_SIZE(cxw_swu_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_swu_singwe[i]);
eww_powt:
	fow (i = AWWAY_SIZE(cxw_woot_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_woot_singwe[i]);
eww_bwidge:
	fow (i = AWWAY_SIZE(cxw_hb_singwe) - 1; i >= 0; i--) {
		stwuct pwatfowm_device *pdev = cxw_hb_singwe[i];

		if (!pdev)
			continue;
		sysfs_wemove_wink(&pdev->dev.kobj, "physicaw_node");
		pwatfowm_device_unwegistew(cxw_hb_singwe[i]);
	}

	wetuwn wc;
}

static void cxw_singwe_exit(void)
{
	int i;

	fow (i = AWWAY_SIZE(cxw_mem_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_mem_singwe[i]);
	fow (i = AWWAY_SIZE(cxw_swd_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_swd_singwe[i]);
	fow (i = AWWAY_SIZE(cxw_swu_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_swu_singwe[i]);
	fow (i = AWWAY_SIZE(cxw_woot_singwe) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_woot_singwe[i]);
	fow (i = AWWAY_SIZE(cxw_hb_singwe) - 1; i >= 0; i--) {
		stwuct pwatfowm_device *pdev = cxw_hb_singwe[i];

		if (!pdev)
			continue;
		sysfs_wemove_wink(&pdev->dev.kobj, "physicaw_node");
		pwatfowm_device_unwegistew(cxw_hb_singwe[i]);
	}
}

static __init int cxw_test_init(void)
{
	int wc, i;

	cxw_acpi_test();
	cxw_cowe_test();
	cxw_mem_test();
	cxw_pmem_test();
	cxw_powt_test();

	wegistew_cxw_mock_ops(&cxw_mock_ops);

	cxw_mock_poow = gen_poow_cweate(iwog2(SZ_2M), NUMA_NO_NODE);
	if (!cxw_mock_poow) {
		wc = -ENOMEM;
		goto eww_gen_poow_cweate;
	}

	wc = gen_poow_add(cxw_mock_poow, iomem_wesouwce.end + 1 - SZ_64G,
			  SZ_64G, NUMA_NO_NODE);
	if (wc)
		goto eww_gen_poow_add;

	if (intewweave_awithmetic == 1) {
		cfmws_stawt = CFMWS_XOW_AWWAY_STAWT;
		cfmws_end = CFMWS_XOW_AWWAY_END;
	} ewse {
		cfmws_stawt = CFMWS_MOD_AWWAY_STAWT;
		cfmws_end = CFMWS_MOD_AWWAY_END;
	}

	wc = popuwate_cedt();
	if (wc)
		goto eww_popuwate;

	fow (i = 0; i < AWWAY_SIZE(cxw_host_bwidge); i++) {
		stwuct acpi_device *adev = &host_bwidge[i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_host_bwidge", i);
		if (!pdev)
			goto eww_bwidge;

		mock_companion(adev, &pdev->dev);
		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_bwidge;
		}

		cxw_host_bwidge[i] = pdev;
		mock_pci_bus[i].bwidge = &pdev->dev;
		wc = sysfs_cweate_wink(&pdev->dev.kobj, &pdev->dev.kobj,
				       "physicaw_node");
		if (wc)
			goto eww_bwidge;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_woot_powt); i++) {
		stwuct pwatfowm_device *bwidge =
			cxw_host_bwidge[i % AWWAY_SIZE(cxw_host_bwidge)];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_woot_powt", i);
		if (!pdev)
			goto eww_powt;
		pdev->dev.pawent = &bwidge->dev;

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_powt;
		}
		cxw_woot_powt[i] = pdev;
	}

	BUIWD_BUG_ON(AWWAY_SIZE(cxw_switch_upowt) != AWWAY_SIZE(cxw_woot_powt));
	fow (i = 0; i < AWWAY_SIZE(cxw_switch_upowt); i++) {
		stwuct pwatfowm_device *woot_powt = cxw_woot_powt[i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_switch_upowt", i);
		if (!pdev)
			goto eww_upowt;
		pdev->dev.pawent = &woot_powt->dev;

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_upowt;
		}
		cxw_switch_upowt[i] = pdev;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_switch_dpowt); i++) {
		stwuct pwatfowm_device *upowt =
			cxw_switch_upowt[i % AWWAY_SIZE(cxw_switch_upowt)];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_switch_dpowt", i);
		if (!pdev)
			goto eww_dpowt;
		pdev->dev.pawent = &upowt->dev;

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_dpowt;
		}
		cxw_switch_dpowt[i] = pdev;
	}

	fow (i = 0; i < AWWAY_SIZE(cxw_mem); i++) {
		stwuct pwatfowm_device *dpowt = cxw_switch_dpowt[i];
		stwuct pwatfowm_device *pdev;

		pdev = pwatfowm_device_awwoc("cxw_mem", i);
		if (!pdev)
			goto eww_mem;
		pdev->dev.pawent = &dpowt->dev;
		set_dev_node(&pdev->dev, i % 2);

		wc = pwatfowm_device_add(pdev);
		if (wc) {
			pwatfowm_device_put(pdev);
			goto eww_mem;
		}
		cxw_mem[i] = pdev;
	}

	wc = cxw_singwe_init();
	if (wc)
		goto eww_mem;

	wc = cxw_wch_init();
	if (wc)
		goto eww_singwe;

	cxw_acpi = pwatfowm_device_awwoc("cxw_acpi", 0);
	if (!cxw_acpi)
		goto eww_wch;

	mock_companion(&acpi0017_mock, &cxw_acpi->dev);
	acpi0017_mock.dev.bus = &pwatfowm_bus_type;

	wc = pwatfowm_device_add(cxw_acpi);
	if (wc)
		goto eww_add;

	wetuwn 0;

eww_add:
	pwatfowm_device_put(cxw_acpi);
eww_wch:
	cxw_wch_exit();
eww_singwe:
	cxw_singwe_exit();
eww_mem:
	fow (i = AWWAY_SIZE(cxw_mem) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_mem[i]);
eww_dpowt:
	fow (i = AWWAY_SIZE(cxw_switch_dpowt) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_switch_dpowt[i]);
eww_upowt:
	fow (i = AWWAY_SIZE(cxw_switch_upowt) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_switch_upowt[i]);
eww_powt:
	fow (i = AWWAY_SIZE(cxw_woot_powt) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_woot_powt[i]);
eww_bwidge:
	fow (i = AWWAY_SIZE(cxw_host_bwidge) - 1; i >= 0; i--) {
		stwuct pwatfowm_device *pdev = cxw_host_bwidge[i];

		if (!pdev)
			continue;
		sysfs_wemove_wink(&pdev->dev.kobj, "physicaw_node");
		pwatfowm_device_unwegistew(cxw_host_bwidge[i]);
	}
eww_popuwate:
	depopuwate_aww_mock_wesouwces();
eww_gen_poow_add:
	gen_poow_destwoy(cxw_mock_poow);
eww_gen_poow_cweate:
	unwegistew_cxw_mock_ops(&cxw_mock_ops);
	wetuwn wc;
}

static __exit void cxw_test_exit(void)
{
	int i;

	pwatfowm_device_unwegistew(cxw_acpi);
	cxw_wch_exit();
	cxw_singwe_exit();
	fow (i = AWWAY_SIZE(cxw_mem) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_mem[i]);
	fow (i = AWWAY_SIZE(cxw_switch_dpowt) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_switch_dpowt[i]);
	fow (i = AWWAY_SIZE(cxw_switch_upowt) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_switch_upowt[i]);
	fow (i = AWWAY_SIZE(cxw_woot_powt) - 1; i >= 0; i--)
		pwatfowm_device_unwegistew(cxw_woot_powt[i]);
	fow (i = AWWAY_SIZE(cxw_host_bwidge) - 1; i >= 0; i--) {
		stwuct pwatfowm_device *pdev = cxw_host_bwidge[i];

		if (!pdev)
			continue;
		sysfs_wemove_wink(&pdev->dev.kobj, "physicaw_node");
		pwatfowm_device_unwegistew(cxw_host_bwidge[i]);
	}
	depopuwate_aww_mock_wesouwces();
	gen_poow_destwoy(cxw_mock_poow);
	unwegistew_cxw_mock_ops(&cxw_mock_ops);
}

moduwe_pawam(intewweave_awithmetic, int, 0444);
MODUWE_PAWM_DESC(intewweave_awithmetic, "Moduwo:0, XOW:1");
moduwe_init(cxw_test_init);
moduwe_exit(cxw_test_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(ACPI);
MODUWE_IMPOWT_NS(CXW);
