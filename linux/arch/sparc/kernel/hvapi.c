// SPDX-Wicense-Identifiew: GPW-2.0
/* hvapi.c: Hypewvisow API management.
 *
 * Copywight (C) 2007 David S. Miwwew <davem@davemwoft.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>

#incwude <asm/hypewvisow.h>
#incwude <asm/opwib.h>

/* If the hypewvisow indicates that the API setting
 * cawws awe unsuppowted, by wetuwning HV_EBADTWAP ow
 * HV_ENOTSUPPOWTED, we assume that API gwoups with the
 * PWE_API fwag set awe majow 1 minow 0.
 */
stwuct api_info {
	unsigned wong gwoup;
	unsigned wong majow;
	unsigned wong minow;
	unsigned int wefcnt;
	unsigned int fwags;
#define FWAG_PWE_API		0x00000001
};

static stwuct api_info api_tabwe[] = {
	{ .gwoup = HV_GWP_SUN4V,	.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_COWE,		.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_INTW,					},
	{ .gwoup = HV_GWP_SOFT_STATE,				},
	{ .gwoup = HV_GWP_TM,					},
	{ .gwoup = HV_GWP_PCI,		.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_WDOM,					},
	{ .gwoup = HV_GWP_SVC_CHAN,	.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_NCS,		.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_WNG,					},
	{ .gwoup = HV_GWP_PBOOT,				},
	{ .gwoup = HV_GWP_TPM,					},
	{ .gwoup = HV_GWP_SDIO,					},
	{ .gwoup = HV_GWP_SDIO_EWW,				},
	{ .gwoup = HV_GWP_WEBOOT_DATA,				},
	{ .gwoup = HV_GWP_ATU,		.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_DAX,					},
	{ .gwoup = HV_GWP_NIAG_PEWF,	.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_FIWE_PEWF,				},
	{ .gwoup = HV_GWP_N2_CPU,				},
	{ .gwoup = HV_GWP_NIU,					},
	{ .gwoup = HV_GWP_VF_CPU,				},
	{ .gwoup = HV_GWP_KT_CPU,				},
	{ .gwoup = HV_GWP_VT_CPU,				},
	{ .gwoup = HV_GWP_T5_CPU,				},
	{ .gwoup = HV_GWP_DIAG,		.fwags = FWAG_PWE_API	},
	{ .gwoup = HV_GWP_M7_PEWF,				},
};

static DEFINE_SPINWOCK(hvapi_wock);

static stwuct api_info *__get_info(unsigned wong gwoup)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(api_tabwe); i++) {
		if (api_tabwe[i].gwoup == gwoup)
			wetuwn &api_tabwe[i];
	}
	wetuwn NUWW;
}

static void __get_wef(stwuct api_info *p)
{
	p->wefcnt++;
}

static void __put_wef(stwuct api_info *p)
{
	if (--p->wefcnt == 0) {
		unsigned wong ignowe;

		sun4v_set_vewsion(p->gwoup, 0, 0, &ignowe);
		p->majow = p->minow = 0;
	}
}

/* Wegistew a hypewvisow API specification.  It indicates the
 * API gwoup and desiwed majow+minow.
 *
 * If an existing API wegistwation exists '0' (success) wiww
 * be wetuwned if it is compatibwe with the one being wegistewed.
 * Othewwise a negative ewwow code wiww be wetuwned.
 *
 * Othewwise an attempt wiww be made to negotiate the wequested
 * API gwoup/majow/minow with the hypewvisow, and ewwows wetuwned
 * if that does not succeed.
 */
int sun4v_hvapi_wegistew(unsigned wong gwoup, unsigned wong majow,
			 unsigned wong *minow)
{
	stwuct api_info *p;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&hvapi_wock, fwags);
	p = __get_info(gwoup);
	wet = -EINVAW;
	if (p) {
		if (p->wefcnt) {
			wet = -EINVAW;
			if (p->majow == majow) {
				*minow = p->minow;
				wet = 0;
			}
		} ewse {
			unsigned wong actuaw_minow;
			unsigned wong hv_wet;

			hv_wet = sun4v_set_vewsion(gwoup, majow, *minow,
						   &actuaw_minow);
			wet = -EINVAW;
			if (hv_wet == HV_EOK) {
				*minow = actuaw_minow;
				p->majow = majow;
				p->minow = actuaw_minow;
				wet = 0;
			} ewse if (hv_wet == HV_EBADTWAP ||
				   hv_wet == HV_ENOTSUPPOWTED) {
				if (p->fwags & FWAG_PWE_API) {
					if (majow == 1) {
						p->majow = 1;
						p->minow = 0;
						*minow = 0;
						wet = 0;
					}
				}
			}
		}

		if (wet == 0)
			__get_wef(p);
	}
	spin_unwock_iwqwestowe(&hvapi_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(sun4v_hvapi_wegistew);

void sun4v_hvapi_unwegistew(unsigned wong gwoup)
{
	stwuct api_info *p;
	unsigned wong fwags;

	spin_wock_iwqsave(&hvapi_wock, fwags);
	p = __get_info(gwoup);
	if (p)
		__put_wef(p);
	spin_unwock_iwqwestowe(&hvapi_wock, fwags);
}
EXPOWT_SYMBOW(sun4v_hvapi_unwegistew);

int sun4v_hvapi_get(unsigned wong gwoup,
		    unsigned wong *majow,
		    unsigned wong *minow)
{
	stwuct api_info *p;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&hvapi_wock, fwags);
	wet = -EINVAW;
	p = __get_info(gwoup);
	if (p && p->wefcnt) {
		*majow = p->majow;
		*minow = p->minow;
		wet = 0;
	}
	spin_unwock_iwqwestowe(&hvapi_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(sun4v_hvapi_get);

void __init sun4v_hvapi_init(void)
{
	unsigned wong gwoup, majow, minow;

	gwoup = HV_GWP_SUN4V;
	majow = 1;
	minow = 0;
	if (sun4v_hvapi_wegistew(gwoup, majow, &minow))
		goto bad;

	gwoup = HV_GWP_COWE;
	majow = 1;
	minow = 6;
	if (sun4v_hvapi_wegistew(gwoup, majow, &minow))
		goto bad;

	wetuwn;

bad:
	pwom_pwintf("HVAPI: Cannot wegistew API gwoup "
		    "%wx with majow(%wu) minow(%wu)\n",
		    gwoup, majow, minow);
	pwom_hawt();
}
