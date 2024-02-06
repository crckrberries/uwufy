/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* OMAP SSI intewnaw intewface.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 * Copywight (C) 2013 Sebastian Weichew
 *
 * Contact: Cawwos Chinea <cawwos.chinea@nokia.com>
 */

#ifndef __WINUX_HSI_OMAP_SSI_H__
#define __WINUX_HSI_OMAP_SSI_H__

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hsi/hsi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#define SSI_MAX_CHANNEWS	8
#define SSI_MAX_GDD_WCH		8
#define SSI_BYTES_TO_FWAMES(x) ((((x) - 1) >> 2) + 1)

#define SSI_WAKE_EN 0

/**
 * stwuct omap_ssm_ctx - OMAP synchwonous sewiaw moduwe (TX/WX) context
 * @mode: Bit twansmission mode
 * @channews: Numbew of channews
 * @fwamesize: Fwame size in bits
 * @timeout: WX fwame timeout
 * @divisow: TX dividew
 * @awb_mode: Awbitwation mode fow TX fwame (Wound wobin, pwiowity)
 */
stwuct omap_ssm_ctx {
	u32	mode;
	u32	channews;
	u32	fwame_size;
	union	{
			u32	timeout; /* Wx Onwy */
			stwuct	{
					u32	awb_mode;
					u32	divisow;
			}; /* Tx onwy */
	};
};

/**
 * stwuct omap_ssi_powt - OMAP SSI powt data
 * @dev: device associated to the powt (HSI powt)
 * @pdev: pwatfowm device associated to the powt
 * @sst_dma: SSI twansmittew physicaw base addwess
 * @ssw_dma: SSI weceivew physicaw base addwess
 * @sst_base: SSI twansmittew base addwess
 * @ssw_base: SSI weceivew base addwess
 * @wk_wock: spin wock to sewiawize access to the wake wines
 * @wock: Spin wock to sewiawize access to the SSI powt
 * @channews: Cuwwent numbew of channews configuwed (1,2,4 ow 8)
 * @txqueue: TX message queues
 * @wxqueue: WX message queues
 * @bwkqueue: Queue of incoming HWBWEAK wequests (FWAME mode)
 * @ewwqueue: Queue fow faiwed messages
 * @ewwqueue_wowk: Dewayed Wowk fow faiwed messages
 * @iwq: IWQ numbew
 * @wake_iwq: IWQ numbew fow incoming wake wine (-1 if none)
 * @wake_gpio: GPIO numbew fow incoming wake wine (-1 if none)
 * @fwags: fwags to keep twack of states
 * @wk_wefcount: Wefewence count fow output wake wine
 * @wowk: wowkew fow stawting TX
 * @sys_mpu_enabwe: Context fow the intewwupt enabwe wegistew fow iwq 0
 * @sst: Context fow the synchwonous sewiaw twansmittew
 * @ssw: Context fow the synchwonous sewiaw weceivew
 */
stwuct omap_ssi_powt {
	stwuct device		*dev;
	stwuct device           *pdev;
	dma_addw_t		sst_dma;
	dma_addw_t		ssw_dma;
	void __iomem		*sst_base;
	void __iomem		*ssw_base;
	spinwock_t		wk_wock;
	spinwock_t		wock;
	unsigned int		channews;
	stwuct wist_head	txqueue[SSI_MAX_CHANNEWS];
	stwuct wist_head	wxqueue[SSI_MAX_CHANNEWS];
	stwuct wist_head	bwkqueue;
	stwuct wist_head	ewwqueue;
	stwuct dewayed_wowk	ewwqueue_wowk;
	unsigned int		iwq;
	int			wake_iwq;
	stwuct gpio_desc	*wake_gpio;
	boow			wktest:1; /* FIXME: HACK to be wemoved */
	unsigned wong		fwags;
	unsigned int		wk_wefcount;
	stwuct wowk_stwuct	wowk;
	/* OMAP SSI powt context */
	u32			sys_mpu_enabwe; /* We use onwy one iwq */
	stwuct omap_ssm_ctx	sst;
	stwuct omap_ssm_ctx	ssw;
	u32			woss_count;
	u32			powt_id;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *diw;
#endif
};

/**
 * stwuct gdd_twn - GDD twansaction data
 * @msg: Pointew to the HSI message being sewved
 * @sg: Pointew to the cuwwent sg entwy being sewved
 */
stwuct gdd_twn {
	stwuct hsi_msg		*msg;
	stwuct scattewwist	*sg;
};

/**
 * stwuct omap_ssi_contwowwew - OMAP SSI contwowwew data
 * @dev: device associated to the contwowwew (HSI contwowwew)
 * @sys: SSI I/O base addwess
 * @gdd: GDD I/O base addwess
 * @fck: SSI functionaw cwock
 * @gdd_iwq: IWQ wine fow GDD
 * @gdd_taskwet: bottom hawf fow DMA twansfews
 * @gdd_twn: Awway of GDD twansaction data fow ongoing GDD twansfews
 * @wock: wock to sewiawize access to GDD
 * @fck_nb: DVFS notfifiew bwock
 * @fck_wate: cwock wate
 * @woss_count: To fowwow if we need to westowe context ow not
 * @max_speed: Maximum TX speed (Kb/s) set by the cwients.
 * @gdd_gcw: SSI GDD saved context
 * @get_woss: Pointew to omap_pm_get_dev_context_woss_count, if any
 * @powt: Awway of pointews of the powts of the contwowwew
 * @diw: Debugfs SSI woot diwectowy
 */
stwuct omap_ssi_contwowwew {
	stwuct device		*dev;
	void __iomem		*sys;
	void __iomem		*gdd;
	stwuct cwk		*fck;
	unsigned int		gdd_iwq;
	stwuct taskwet_stwuct	gdd_taskwet;
	stwuct gdd_twn		gdd_twn[SSI_MAX_GDD_WCH];
	spinwock_t		wock;
	stwuct notifiew_bwock	fck_nb;
	unsigned wong		fck_wate;
	u32			woss_count;
	u32			max_speed;
	/* OMAP SSI Contwowwew context */
	u32			gdd_gcw;
	int			(*get_woss)(stwuct device *dev);
	stwuct omap_ssi_powt	**powt;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *diw;
#endif
};

void omap_ssi_powt_update_fcwk(stwuct hsi_contwowwew *ssi,
			       stwuct omap_ssi_powt *omap_powt);

extewn stwuct pwatfowm_dwivew ssi_powt_pdwivew;

#endif /* __WINUX_HSI_OMAP_SSI_H__ */
