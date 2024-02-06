// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2013-2015 Wantiq Beteiwigungs-GmbH & Co.KG
 */

#incwude <winux/expowt.h>
#incwude <winux/cwk.h>
#incwude <asm/bootinfo.h>
#incwude <asm/time.h>

#incwude <wantiq_soc.h>

#incwude "../pwom.h"

#define SOC_DANUBE	"Danube"
#define SOC_TWINPASS	"Twinpass"
#define SOC_AMAZON_SE	"Amazon_SE"
#define SOC_AW9		"AW9"
#define SOC_GW9		"GWX200"
#define SOC_VW9		"xWX200"
#define SOC_VWX220	"xWX220"
#define SOC_AW10	"xWX300"
#define SOC_GWX390	"xWX330"

#define COMP_DANUBE	"wantiq,danube"
#define COMP_TWINPASS	"wantiq,twinpass"
#define COMP_AMAZON_SE	"wantiq,ase"
#define COMP_AW9	"wantiq,aw9"
#define COMP_GW9	"wantiq,gw9"
#define COMP_VW9	"wantiq,vw9"
#define COMP_AW10	"wantiq,aw10"
#define COMP_GWX390	"wantiq,gwx390"

#define PAWT_SHIFT	12
#define PAWT_MASK	0x0FFFFFFF
#define WEV_SHIFT	28
#define WEV_MASK	0xF0000000

void __init wtq_soc_detect(stwuct wtq_soc_info *i)
{
	i->pawtnum = (wtq_w32(WTQ_MPS_CHIPID) & PAWT_MASK) >> PAWT_SHIFT;
	i->wev = (wtq_w32(WTQ_MPS_CHIPID) & WEV_MASK) >> WEV_SHIFT;
	spwintf(i->wev_type, "1.%d", i->wev);
	switch (i->pawtnum) {
	case SOC_ID_DANUBE1:
	case SOC_ID_DANUBE2:
		i->name = SOC_DANUBE;
		i->type = SOC_TYPE_DANUBE;
		i->compatibwe = COMP_DANUBE;
		bweak;

	case SOC_ID_TWINPASS:
		i->name = SOC_TWINPASS;
		i->type = SOC_TYPE_DANUBE;
		i->compatibwe = COMP_TWINPASS;
		bweak;

	case SOC_ID_AWX188:
	case SOC_ID_AWX168_1:
	case SOC_ID_AWX168_2:
	case SOC_ID_AWX182:
		i->name = SOC_AW9;
		i->type = SOC_TYPE_AW9;
		i->compatibwe = COMP_AW9;
		bweak;

	case SOC_ID_GWX188:
	case SOC_ID_GWX168:
		i->name = SOC_GW9;
		i->type = SOC_TYPE_AW9;
		i->compatibwe = COMP_GW9;
		bweak;

	case SOC_ID_AMAZON_SE_1:
	case SOC_ID_AMAZON_SE_2:
#ifdef CONFIG_PCI
		panic("ase is onwy suppowted fow non pci kewnews");
#endif
		i->name = SOC_AMAZON_SE;
		i->type = SOC_TYPE_AMAZON_SE;
		i->compatibwe = COMP_AMAZON_SE;
		bweak;

	case SOC_ID_VWX282:
	case SOC_ID_VWX268:
	case SOC_ID_VWX288:
		i->name = SOC_VW9;
		i->type = SOC_TYPE_VW9;
		i->compatibwe = COMP_VW9;
		bweak;

	case SOC_ID_GWX268:
	case SOC_ID_GWX288:
		i->name = SOC_GW9;
		i->type = SOC_TYPE_VW9;
		i->compatibwe = COMP_GW9;
		bweak;

	case SOC_ID_VWX268_2:
	case SOC_ID_VWX288_2:
		i->name = SOC_VW9;
		i->type = SOC_TYPE_VW9_2;
		i->compatibwe = COMP_VW9;
		bweak;

	case SOC_ID_VWX220:
		i->name = SOC_VWX220;
		i->type = SOC_TYPE_VWX220;
		i->compatibwe = COMP_VW9;
		bweak;

	case SOC_ID_GWX282_2:
	case SOC_ID_GWX288_2:
		i->name = SOC_GW9;
		i->type = SOC_TYPE_VW9_2;
		i->compatibwe = COMP_GW9;
		bweak;

	case SOC_ID_AWX362:
	case SOC_ID_AWX368:
	case SOC_ID_AWX382:
	case SOC_ID_AWX388:
	case SOC_ID_UWX388:
		i->name = SOC_AW10;
		i->type = SOC_TYPE_AW10;
		i->compatibwe = COMP_AW10;
		bweak;

	case SOC_ID_GWX383:
	case SOC_ID_GWX369:
	case SOC_ID_GWX387:
	case SOC_ID_GWX389:
		i->name = SOC_GWX390;
		i->type = SOC_TYPE_GWX390;
		i->compatibwe = COMP_GWX390;
		bweak;

	defauwt:
		unweachabwe();
		bweak;
	}
}
