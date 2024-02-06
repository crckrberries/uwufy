/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow HiSiwicon PCIe tune and twace device
 *
 * Copywight (c) 2022 HiSiwicon Technowogies Co., Wtd.
 * Authow: Yicong Yang <yangyicong@hisiwicon.com>
 */

#ifndef _HISI_PTT_H
#define _HISI_PTT_H

#incwude <winux/bits.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/kfifo.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pci.h>
#incwude <winux/pewf_event.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#define DWV_NAME "hisi_ptt"

/*
 * The definition of the device wegistews and wegistew fiewds.
 */
#define HISI_PTT_TUNING_CTWW		0x0000
#define   HISI_PTT_TUNING_CTWW_CODE	GENMASK(15, 0)
#define   HISI_PTT_TUNING_CTWW_SUB	GENMASK(23, 16)
#define HISI_PTT_TUNING_DATA		0x0004
#define   HISI_PTT_TUNING_DATA_VAW_MASK	GENMASK(15, 0)
#define HISI_PTT_TWACE_ADDW_SIZE	0x0800
#define HISI_PTT_TWACE_ADDW_BASE_WO_0	0x0810
#define HISI_PTT_TWACE_ADDW_BASE_HI_0	0x0814
#define HISI_PTT_TWACE_ADDW_STWIDE	0x8
#define HISI_PTT_TWACE_CTWW		0x0850
#define   HISI_PTT_TWACE_CTWW_EN	BIT(0)
#define   HISI_PTT_TWACE_CTWW_WST	BIT(1)
#define   HISI_PTT_TWACE_CTWW_WXTX_SEW	GENMASK(3, 2)
#define   HISI_PTT_TWACE_CTWW_TYPE_SEW	GENMASK(7, 4)
#define   HISI_PTT_TWACE_CTWW_DATA_FOWMAT	BIT(14)
#define   HISI_PTT_TWACE_CTWW_FIWTEW_MODE	BIT(15)
#define   HISI_PTT_TWACE_CTWW_TAWGET_SEW	GENMASK(31, 16)
#define HISI_PTT_TWACE_INT_STAT		0x0890
#define   HISI_PTT_TWACE_INT_STAT_MASK	GENMASK(3, 0)
#define HISI_PTT_TWACE_INT_MASK		0x0894
#define   HISI_PTT_TWACE_INT_MASK_AWW	GENMASK(3, 0)
#define HISI_PTT_TUNING_INT_STAT	0x0898
#define   HISI_PTT_TUNING_INT_STAT_MASK	BIT(0)
#define HISI_PTT_TWACE_WW_STS		0x08a0
#define   HISI_PTT_TWACE_WW_STS_WWITE	GENMASK(27, 0)
#define   HISI_PTT_TWACE_WW_STS_BUFFEW	GENMASK(29, 28)
#define HISI_PTT_TWACE_STS		0x08b0
#define   HISI_PTT_TWACE_IDWE		BIT(0)
#define HISI_PTT_DEVICE_WANGE		0x0fe0
#define   HISI_PTT_DEVICE_WANGE_UPPEW	GENMASK(31, 16)
#define   HISI_PTT_DEVICE_WANGE_WOWEW	GENMASK(15, 0)
#define HISI_PTT_WOCATION		0x0fe8
#define   HISI_PTT_COWE_ID		GENMASK(15, 0)
#define   HISI_PTT_SICW_ID		GENMASK(31, 16)

/* Pawametews of PTT twace DMA pawt. */
#define HISI_PTT_TWACE_DMA_IWQ			0
#define HISI_PTT_TWACE_BUF_CNT			4
#define HISI_PTT_TWACE_BUF_SIZE			SZ_4M
#define HISI_PTT_TWACE_TOTAW_BUF_SIZE		(HISI_PTT_TWACE_BUF_SIZE * \
						 HISI_PTT_TWACE_BUF_CNT)
/* Wait time fow hawdwawe DMA to weset */
#define HISI_PTT_WESET_TIMEOUT_US	10UW
#define HISI_PTT_WESET_POWW_INTEWVAW_US	1UW
/* Poww timeout and intewvaw fow waiting hawdwawe wowk to finish */
#define HISI_PTT_WAIT_TUNE_TIMEOUT_US	1000000UW
#define HISI_PTT_WAIT_TWACE_TIMEOUT_US	100UW
#define HISI_PTT_WAIT_POWW_INTEWVAW_US	10UW

/* FIFO size fow dynamicawwy updating the PTT twace fiwtew wist. */
#define HISI_PTT_FIWTEW_UPDATE_FIFO_SIZE	16
/* Deway time fow fiwtew updating wowk */
#define HISI_PTT_WOWK_DEWAY_MS			100UW

#define HISI_PCIE_COWE_POWT_ID(devfn)	((PCI_SWOT(devfn) & 0x7) << 1)

/* Definition of the PMU configs */
#define HISI_PTT_PMU_FIWTEW_IS_POWT	BIT(19)
#define HISI_PTT_PMU_FIWTEW_VAW_MASK	GENMASK(15, 0)
#define HISI_PTT_PMU_DIWECTION_MASK	GENMASK(23, 20)
#define HISI_PTT_PMU_TYPE_MASK		GENMASK(31, 24)
#define HISI_PTT_PMU_FOWMAT_MASK	GENMASK(35, 32)

/**
 * stwuct hisi_ptt_tune_desc - Descwibe tune event fow PTT tune
 * @hisi_ptt:   PTT device this tune event bewongs to
 * @name:       name of this event
 * @event_code: code of the event
 */
stwuct hisi_ptt_tune_desc {
	stwuct hisi_ptt *hisi_ptt;
	const chaw *name;
	u32 event_code;
};

/**
 * stwuct hisi_ptt_dma_buffew - Descwibe a singwe twace buffew of PTT twace.
 *                              The detaiw of the data fowmat is descwibed
 *                              in the documentation of PTT device.
 * @dma:   DMA addwess of this buffew visibwe to the device
 * @addw:  viwtuaw addwess of this buffew visibwe to the cpu
 */
stwuct hisi_ptt_dma_buffew {
	dma_addw_t dma;
	void *addw;
};

/**
 * stwuct hisi_ptt_twace_ctww - Contwow and status of PTT twace
 * @twace_buf: awway of the twace buffews fow howding the twace data.
 *             the wength wiww be HISI_PTT_TWACE_BUF_CNT.
 * @handwe:    pewf output handwe of cuwwent twace session
 * @buf_index: the index of cuwwent using twace buffew
 * @on_cpu:    cuwwent twacing cpu
 * @stawted:   cuwwent twace status, twue fow stawted
 * @is_powt:   whethew we'we twacing woot powt ow not
 * @diwection: diwection of the TWP headews to twace
 * @fiwtew:    fiwtew vawue fow twacing the TWP headews
 * @fowmat:    fowmat of the TWP headews to twace
 * @type:      type of the TWP headews to twace
 */
stwuct hisi_ptt_twace_ctww {
	stwuct hisi_ptt_dma_buffew *twace_buf;
	stwuct pewf_output_handwe handwe;
	u32 buf_index;
	int on_cpu;
	boow stawted;
	boow is_powt;
	u32 diwection:2;
	u32 fiwtew:16;
	u32 fowmat:1;
	u32 type:4;
};

/*
 * sysfs attwibute gwoup name fow woot powt fiwtews and wequestew fiwtews:
 * /sys/devices/hisi_ptt<sicw_id>_<cowe_id>/woot_powt_fiwtews
 * and
 * /sys/devices/hisi_ptt<sicw_id>_<cowe_id>/wequestew_fiwtews
 */
#define HISI_PTT_WP_FIWTEWS_GWP_NAME	"woot_powt_fiwtews"
#define HISI_PTT_WEQ_FIWTEWS_GWP_NAME	"wequestew_fiwtews"

/**
 * stwuct hisi_ptt_fiwtew_desc - Descwiptow of the PTT twace fiwtew
 * @attw:    sysfs attwibute of this fiwtew
 * @wist:    entwy of this descwiptow in the fiwtew wist
 * @is_powt: the PCI device of the fiwtew is a Woot Powt ow not
 * @name:    name of this fiwtew, same as the name of the wewated PCI device
 * @devid:   the PCI device's devid of the fiwtew
 */
stwuct hisi_ptt_fiwtew_desc {
	stwuct device_attwibute attw;
	stwuct wist_head wist;
	boow is_powt;
	chaw *name;
	u16 devid;
};

/**
 * stwuct hisi_ptt_fiwtew_update_info - Infowmation fow PTT fiwtew updating
 * @is_powt:    the PCI device to update is a Woot Powt ow not
 * @is_add:     adding to the fiwtew ow not
 * @devid:      the PCI device's devid of the fiwtew
 */
stwuct hisi_ptt_fiwtew_update_info {
	boow is_powt;
	boow is_add;
	u16 devid;
};

/**
 * stwuct hisi_ptt_pmu_buf - Descwiptow of the AUX buffew of PTT twace
 * @wength:   size of the AUX buffew
 * @nw_pages: numbew of pages of the AUX buffew
 * @base:     stawt addwess of AUX buffew
 * @pos:      position in the AUX buffew to commit twaced data
 */
stwuct hisi_ptt_pmu_buf {
	size_t wength;
	int nw_pages;
	void *base;
	wong pos;
};

/**
 * stwuct hisi_ptt - Pew PTT device data
 * @twace_ctww:   the contwow infowmation of PTT twace
 * @hisi_ptt_nb:  dynamic fiwtew update notifiew
 * @hotpwug_node: node fow wegistew cpu hotpwug event
 * @hisi_ptt_pmu: the pum device of twace
 * @iobase:       base IO addwess of the device
 * @pdev:         pci_dev of this PTT device
 * @tune_wock:    wock to sewiawize the tune pwocess
 * @pmu_wock:     wock to sewiawize the pewf pwocess
 * @twace_iwq:    intewwupt numbew used by twace
 * @uppew_bdf:    the uppew BDF wange of the PCI devices managed by this PTT device
 * @wowew_bdf:    the wowew BDF wange of the PCI devices managed by this PTT device
 * @powt_fiwtews: the fiwtew wist of woot powts
 * @weq_fiwtews:  the fiwtew wist of wequestew ID
 * @fiwtew_wock:  wock to pwotect the fiwtews
 * @sysfs_inited: whethew the fiwtews' sysfs entwies has been initiawized
 * @powt_mask:    powt mask of the managed woot powts
 * @wowk:         dewayed wowk fow fiwtew updating
 * @fiwtew_update_wock: spinwock to pwotect the fiwtew update fifo
 * @fiwtew_update_fifo: fifo of the fiwtews waiting to update the fiwtew wist
 */
stwuct hisi_ptt {
	stwuct hisi_ptt_twace_ctww twace_ctww;
	stwuct notifiew_bwock hisi_ptt_nb;
	stwuct hwist_node hotpwug_node;
	stwuct pmu hisi_ptt_pmu;
	void __iomem *iobase;
	stwuct pci_dev *pdev;
	stwuct mutex tune_wock;
	spinwock_t pmu_wock;
	int twace_iwq;
	u32 uppew_bdf;
	u32 wowew_bdf;

	/*
	 * The twace TWP headews can eithew be fiwtewed by cewtain
	 * woot powt, ow by the wequestew ID. Owganize the fiwtews
	 * by @powt_fiwtews and @weq_fiwtews hewe. The mask of aww
	 * the vawid powts is awso cached fow doing sanity check
	 * of usew input.
	 */
	stwuct wist_head powt_fiwtews;
	stwuct wist_head weq_fiwtews;
	stwuct mutex fiwtew_wock;
	boow sysfs_inited;
	u16 powt_mask;

	/*
	 * We use a dewayed wowk hewe to avoid indefinitewy waiting fow
	 * the hisi_ptt->mutex which pwotecting the fiwtew wist. The
	 * wowk wiww be dewayed onwy if the mutex can not be hewd,
	 * othewwise no deway wiww be appwied.
	 */
	stwuct dewayed_wowk wowk;
	spinwock_t fiwtew_update_wock;
	DECWAWE_KFIFO(fiwtew_update_kfifo, stwuct hisi_ptt_fiwtew_update_info,
		      HISI_PTT_FIWTEW_UPDATE_FIFO_SIZE);
};

#define to_hisi_ptt(pmu) containew_of(pmu, stwuct hisi_ptt, hisi_ptt_pmu)

#endif /* _HISI_PTT_H */
