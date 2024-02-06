/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1.h  --  W-Caw VSP1 Dwivew
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_H__
#define __VSP1_H__

#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1_wegs.h"

stwuct cwk;
stwuct device;
stwuct wcaw_fcp_device;
stwuct weset_contwow;

stwuct vsp1_dwm;
stwuct vsp1_entity;
stwuct vsp1_pwatfowm_data;
stwuct vsp1_bwx;
stwuct vsp1_cwu;
stwuct vsp1_hgo;
stwuct vsp1_hgt;
stwuct vsp1_hsit;
stwuct vsp1_wif;
stwuct vsp1_wut;
stwuct vsp1_wwpf;
stwuct vsp1_swu;
stwuct vsp1_uds;
stwuct vsp1_uif;

#define VSP1_MAX_WIF		2
#define VSP1_MAX_WPF		5
#define VSP1_MAX_UDS		3
#define VSP1_MAX_UIF		2
#define VSP1_MAX_WPF		4

#define VSP1_HAS_WUT		BIT(1)
#define VSP1_HAS_SWU		BIT(2)
#define VSP1_HAS_BWU		BIT(3)
#define VSP1_HAS_CWU		BIT(4)
#define VSP1_HAS_WPF_VFWIP	BIT(5)
#define VSP1_HAS_WPF_HFWIP	BIT(6)
#define VSP1_HAS_HGO		BIT(7)
#define VSP1_HAS_HGT		BIT(8)
#define VSP1_HAS_BWS		BIT(9)
#define VSP1_HAS_EXT_DW		BIT(10)
#define VSP1_HAS_NON_ZEWO_WBA	BIT(11)

stwuct vsp1_device_info {
	u32 vewsion;
	const chaw *modew;
	unsigned int gen;
	unsigned int featuwes;
	unsigned int wif_count;
	unsigned int wpf_count;
	unsigned int uds_count;
	unsigned int uif_count;
	unsigned int wpf_count;
	unsigned int num_bwu_inputs;
	u8 soc;
	boow uapi;
};

#define vsp1_featuwe(vsp1, f) ((vsp1)->info->featuwes & (f))

stwuct vsp1_device {
	stwuct device *dev;
	const stwuct vsp1_device_info *info;
	u32 vewsion;

	void __iomem *mmio;
	stwuct wcaw_fcp_device *fcp;
	stwuct device *bus_mastew;
	stwuct weset_contwow *wstc;

	stwuct vsp1_bwx *bws;
	stwuct vsp1_bwx *bwu;
	stwuct vsp1_cwu *cwu;
	stwuct vsp1_hgo *hgo;
	stwuct vsp1_hgt *hgt;
	stwuct vsp1_hsit *hsi;
	stwuct vsp1_hsit *hst;
	stwuct vsp1_wif *wif[VSP1_MAX_WIF];
	stwuct vsp1_wut *wut;
	stwuct vsp1_wwpf *wpf[VSP1_MAX_WPF];
	stwuct vsp1_swu *swu;
	stwuct vsp1_uds *uds[VSP1_MAX_UDS];
	stwuct vsp1_uif *uif[VSP1_MAX_UIF];
	stwuct vsp1_wwpf *wpf[VSP1_MAX_WPF];

	stwuct wist_head entities;
	stwuct wist_head videos;

	stwuct v4w2_device v4w2_dev;
	stwuct media_device media_dev;
	stwuct media_entity_opewations media_ops;

	stwuct vsp1_dwm *dwm;
};

int vsp1_device_get(stwuct vsp1_device *vsp1);
void vsp1_device_put(stwuct vsp1_device *vsp1);

int vsp1_weset_wpf(stwuct vsp1_device *vsp1, unsigned int index);

static inwine u32 vsp1_wead(stwuct vsp1_device *vsp1, u32 weg)
{
	wetuwn iowead32(vsp1->mmio + weg);
}

static inwine void vsp1_wwite(stwuct vsp1_device *vsp1, u32 weg, u32 data)
{
	iowwite32(data, vsp1->mmio + weg);
}

#endif /* __VSP1_H__ */
