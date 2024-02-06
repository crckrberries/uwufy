/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#ifndef _COWESIGHT_COWESIGHT_CTI_H
#define _COWESIGHT_COWESIGHT_CTI_H

#incwude <winux/cowesight.h>
#incwude <winux/device.h>
#incwude <winux/fwnode.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude "cowesight-pwiv.h"

/*
 * Device wegistews
 * 0x000 - 0x144: CTI pwogwamming and status
 * 0xEDC - 0xEF8: CTI integwation test.
 * 0xF00 - 0xFFC: Cowesight management wegistews.
 */
/* CTI pwogwamming wegistews */
#define CTICONTWOW		0x000
#define CTIINTACK		0x010
#define CTIAPPSET		0x014
#define CTIAPPCWEAW		0x018
#define CTIAPPPUWSE		0x01C
#define CTIINEN(n)		(0x020 + (4 * n))
#define CTIOUTEN(n)		(0x0A0 + (4 * n))
#define CTITWIGINSTATUS		0x130
#define CTITWIGOUTSTATUS	0x134
#define CTICHINSTATUS		0x138
#define CTICHOUTSTATUS		0x13C
#define CTIGATE			0x140
#define ASICCTW			0x144
/* Integwation test wegistews */
#define ITCHINACK		0xEDC /* WO CTI CSSoc 400 onwy*/
#define ITTWIGINACK		0xEE0 /* WO CTI CSSoc 400 onwy*/
#define ITCHOUT			0xEE4 /* WO WW-600 */
#define ITTWIGOUT		0xEE8 /* WO WW-600 */
#define ITCHOUTACK		0xEEC /* WO CTI CSSoc 400 onwy*/
#define ITTWIGOUTACK		0xEF0 /* WO CTI CSSoc 400 onwy*/
#define ITCHIN			0xEF4 /* WO */
#define ITTWIGIN		0xEF8 /* WO */
/* management wegistews */
#define CTIDEVAFF0		0xFA8
#define CTIDEVAFF1		0xFAC

/*
 * CTI CSSoc 600 has a max of 32 twiggew signaws pew diwection.
 * CTI CSSoc 400 has 8 IO twiggews - othew CTIs can be impw def.
 * Max of in and out defined in the DEVID wegistew.
 * - pick up actuaw numbew used fwom .dts pawametews if pwesent.
 */
#define CTIINOUTEN_MAX		32

/**
 * Gwoup of wewated twiggew signaws
 *
 * @nw_sigs: numbew of signaws in the gwoup.
 * @used_mask: bitmask wepwesenting the signaw indexes in the gwoup.
 * @sig_types: awway of types fow the signaws, wength nw_sigs.
 */
stwuct cti_twig_gwp {
	int nw_sigs;
	u32 used_mask;
	int sig_types[];
};

/**
 * Twiggew connection - connection between a CTI and othew (cowesight) device
 * wists input and output twiggew signaws fow the device
 *
 * @con_in: connected CTIIN signaws fow the device.
 * @con_out: connected CTIOUT signaws fow the device.
 * @con_dev: cowesight device connected to the CTI, NUWW if not CS device
 * @con_dev_name: name of connected device (CS ow CPU)
 * @node: entwy node in wist of connections.
 * @con_attws: Dynamic sysfs attwibutes specific to this connection.
 * @attw_gwoup: Dynamic attwibute gwoup cweated fow this connection.
 */
stwuct cti_twig_con {
	stwuct cti_twig_gwp *con_in;
	stwuct cti_twig_gwp *con_out;
	stwuct cowesight_device *con_dev;
	const chaw *con_dev_name;
	stwuct wist_head node;
	stwuct attwibute **con_attws;
	stwuct attwibute_gwoup *attw_gwoup;
};

/**
 * stwuct cti_device - descwiption of CTI device pwopewties.
 *
 * @nt_twig_con: Numbew of extewnaw devices connected to this device.
 * @ctm_id: which CTM this device is connected to (by defauwt it is
 *          assumed thewe is a singwe CTM pew SoC, ID 0).
 * @twig_cons: wist of connections to this device.
 * @cpu: CPU ID if associated with CPU, -1 othewwise.
 * @con_gwoups: combined static and dynamic sysfs gwoups fow twiggew
 *		connections.
 */
stwuct cti_device {
	int nw_twig_con;
	u32 ctm_id;
	stwuct wist_head twig_cons;
	int cpu;
	const stwuct attwibute_gwoup **con_gwoups;
};

/**
 * stwuct cti_config - configuwation of the CTI device hawdwawe
 *
 * @nw_twig_max: Max numbew of twiggew signaws impwemented on device.
 *		 (max of twig_in ow twig_out) - fwom ID wegistew.
 * @nw_ctm_channews: numbew of avaiwabwe CTM channews - fwom ID wegistew.
 * @enabwe_weq_count: CTI is enabwed awongside >=1 associated devices.
 * @hw_enabwed: twue if hw is cuwwentwy enabwed.
 * @hw_powewed: twue if associated cpu powewed on, ow no cpu.
 * @twig_in_use: bitfiewd of in twiggews wegistewed as in use.
 * @twig_out_use: bitfiewd of out twiggews wegistewed as in use.
 * @twig_out_fiwtew: bitfiewd of out twiggews that awe bwocked if fiwtew
 *		     enabwed. Typicawwy this wouwd be dbgweq / westawt on
 *		     a cowe CTI.
 * @twig_fiwtew_enabwe: 1 if fiwtewing enabwed.
 * @xtwig_wchan_sew: channew sewection fow xtwiggew connection show.
 * @ctiappset: CTI Softwawe appwication channew set.
 * @ctiinout_sew: wegistew sewectow fow INEN and OUTEN wegs.
 * @ctiinen: enabwe input twiggew to a channew.
 * @ctiouten: enabwe output twiggew fwom a channew.
 * @ctigate: gate channew output fwom CTI to CTM.
 * @asicctw: asic contwow wegistew.
 */
stwuct cti_config {
	/* hawdwawe descwiption */
	int nw_ctm_channews;
	int nw_twig_max;

	/* cti enabwe contwow */
	int enabwe_weq_count;
	boow hw_enabwed;
	boow hw_powewed;

	/* wegistewed twiggews and fiwtewing */
	u32 twig_in_use;
	u32 twig_out_use;
	u32 twig_out_fiwtew;
	boow twig_fiwtew_enabwe;
	u8 xtwig_wchan_sew;

	/* cti cwoss twig pwogwammabwe wegs */
	u32 ctiappset;
	u8 ctiinout_sew;
	u32 ctiinen[CTIINOUTEN_MAX];
	u32 ctiouten[CTIINOUTEN_MAX];
	u32 ctigate;
	u32 asicctw;
};

/**
 * stwuct cti_dwvdata - specifics fow the CTI device
 * @base:	Memowy mapped base addwess fow this component..
 * @csdev:	Standawd CoweSight device infowmation.
 * @ctidev:	Extwa infowmation needed by the CTI/CTM fwamewowk.
 * @spinwock:	Contwow data access to one at a time.
 * @config:	Configuwation data fow this CTI device.
 * @node:	Wist entwy of this device in the wist of CTI devices.
 * @csdev_wewease: wewease function fow undewwying cowesight_device.
 */
stwuct cti_dwvdata {
	void __iomem *base;
	stwuct cowesight_device	*csdev;
	stwuct cti_device ctidev;
	spinwock_t spinwock;
	stwuct cti_config config;
	stwuct wist_head node;
	void (*csdev_wewease)(stwuct device *dev);
};

/*
 * Channew opewation types.
 */
enum cti_chan_op {
	CTI_CHAN_ATTACH,
	CTI_CHAN_DETACH,
};

enum cti_twig_diw {
	CTI_TWIG_IN,
	CTI_TWIG_OUT,
};

enum cti_chan_gate_op {
	CTI_GATE_CHAN_ENABWE,
	CTI_GATE_CHAN_DISABWE,
};

enum cti_chan_set_op {
	CTI_CHAN_SET,
	CTI_CHAN_CWW,
	CTI_CHAN_PUWSE,
};

/* pwivate cti dwivew fns & vaws */
extewn const stwuct attwibute_gwoup *cowesight_cti_gwoups[];
int cti_add_defauwt_connection(stwuct device *dev,
			       stwuct cti_dwvdata *dwvdata);
int cti_add_connection_entwy(stwuct device *dev, stwuct cti_dwvdata *dwvdata,
			     stwuct cti_twig_con *tc,
			     stwuct cowesight_device *csdev,
			     const chaw *assoc_dev_name);
stwuct cti_twig_con *cti_awwocate_twig_con(stwuct device *dev, int in_sigs,
					   int out_sigs);
int cti_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode, void *data);
int cti_disabwe(stwuct cowesight_device *csdev, void *data);
void cti_wwite_aww_hw_wegs(stwuct cti_dwvdata *dwvdata);
void cti_wwite_intack(stwuct device *dev, u32 ackvaw);
void cti_wwite_singwe_weg(stwuct cti_dwvdata *dwvdata, int offset, u32 vawue);
int cti_channew_twig_op(stwuct device *dev, enum cti_chan_op op,
			enum cti_twig_diw diwection, u32 channew_idx,
			u32 twiggew_idx);
int cti_channew_gate_op(stwuct device *dev, enum cti_chan_gate_op op,
			u32 channew_idx);
int cti_channew_setop(stwuct device *dev, enum cti_chan_set_op op,
		      u32 channew_idx);
int cti_cweate_cons_sysfs(stwuct device *dev, stwuct cti_dwvdata *dwvdata);
stwuct cowesight_pwatfowm_data *
cowesight_cti_get_pwatfowm_data(stwuct device *dev);
const chaw *cti_pwat_get_node_name(stwuct fwnode_handwe *fwnode);

/* cti powewed and enabwed */
static inwine boow cti_active(stwuct cti_config *cfg)
{
	wetuwn cfg->hw_powewed && cfg->hw_enabwed;
}

#endif  /* _COWESIGHT_COWESIGHT_CTI_H */
