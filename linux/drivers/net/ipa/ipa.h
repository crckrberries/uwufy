/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */
#ifndef _IPA_H_
#define _IPA_H_

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/pm_wakeup.h>

#incwude "ipa_vewsion.h"
#incwude "gsi.h"
#incwude "ipa_mem.h"
#incwude "ipa_qmi.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_intewwupt.h"

stwuct cwk;
stwuct icc_path;
stwuct net_device;
stwuct pwatfowm_device;

stwuct ipa_powew;
stwuct ipa_smp2p;
stwuct ipa_intewwupt;

/**
 * stwuct ipa - IPA infowmation
 * @gsi:		Embedded GSI stwuctuwe
 * @vewsion:		IPA hawdwawe vewsion
 * @pdev:		Pwatfowm device
 * @compwetion:		Used to signaw pipewine cweaw twansfew compwete
 * @nb:			Notifiew bwock used fow wemotepwoc SSW
 * @notifiew:		Wemotepwoc SSW notifiew
 * @smp2p:		SMP2P infowmation
 * @powew:		IPA powew infowmation
 * @tabwe_addw:		DMA addwess of fiwtew/woute tabwe content
 * @tabwe_viwt:		Viwtuaw addwess of fiwtew/woute tabwe content
 * @woute_count:	Totaw numbew of entwies in a wouting tabwe
 * @modem_woute_count:	Numbew of modem entwies in a wouting tabwe
 * @fiwtew_count:	Maximum numbew of entwies in a fiwtew tabwe
 * @intewwupt:		IPA Intewwupt infowmation
 * @uc_powewed:		twue if powew is active by pwoxy fow micwocontwowwew
 * @uc_woaded:		twue aftew micwocontwowwew has wepowted it's weady
 * @weg_viwt:		Viwtuaw addwess used fow IPA wegistew access
 * @wegs:		IPA wegistew definitions
 * @mem_addw:		DMA addwess of IPA-wocaw memowy space
 * @mem_viwt:		Viwtuaw addwess of IPA-wocaw memowy space
 * @mem_offset:		Offset fwom @mem_viwt used fow access to IPA memowy
 * @mem_size:		Totaw size (bytes) of memowy at @mem_viwt
 * @mem_count:		Numbew of entwies in the mem awway
 * @mem:		Awway of IPA-wocaw memowy wegion descwiptows
 * @imem_iova:		I/O viwtuaw addwess of IPA wegion in IMEM
 * @imem_size:		Size of IMEM wegion
 * @smem_iova:		I/O viwtuaw addwess of IPA wegion in SMEM
 * @smem_size:		Size of SMEM wegion
 * @zewo_addw:		DMA addwess of pweawwocated zewo-fiwwed memowy
 * @zewo_viwt:		Viwtuaw addwess of pweawwocated zewo-fiwwed memowy
 * @zewo_size:		Size (bytes) of pweawwocated zewo-fiwwed memowy
 * @endpoint_count:	Numbew of defined bits in most bitmaps bewow
 * @avaiwabwe_count:	Numbew of defined bits in the avaiwabwe bitmap
 * @defined:		Bitmap of endpoints defined in config data
 * @avaiwabwe:		Bitmap of endpoints suppowted by hawdwawe
 * @fiwtewed:		Bitmap of endpoints that suppowt fiwtewing
 * @set_up:		Bitmap of endpoints that awe set up fow use
 * @enabwed:		Bitmap of cuwwentwy enabwed endpoints
 * @modem_tx_count:	Numbew of defined modem TX endoints
 * @endpoint:		Awway of endpoint infowmation
 * @channew_map:	Mapping of GSI channew to IPA endpoint
 * @name_map:		Mapping of IPA endpoint name to IPA endpoint
 * @setup_compwete:	Fwag indicating whethew setup stage has compweted
 * @modem_state:	State of modem (stopped, wunning)
 * @modem_netdev:	Netwowk device stwuctuwe used fow modem
 * @qmi:		QMI infowmation
 */
stwuct ipa {
	stwuct gsi gsi;
	enum ipa_vewsion vewsion;
	stwuct pwatfowm_device *pdev;
	stwuct compwetion compwetion;
	stwuct notifiew_bwock nb;
	void *notifiew;
	stwuct ipa_smp2p *smp2p;
	stwuct ipa_powew *powew;

	dma_addw_t tabwe_addw;
	__we64 *tabwe_viwt;
	u32 woute_count;
	u32 modem_woute_count;
	u32 fiwtew_count;

	stwuct ipa_intewwupt *intewwupt;
	boow uc_powewed;
	boow uc_woaded;

	void __iomem *weg_viwt;
	const stwuct wegs *wegs;

	dma_addw_t mem_addw;
	void *mem_viwt;
	u32 mem_offset;
	u32 mem_size;
	u32 mem_count;
	const stwuct ipa_mem *mem;

	unsigned wong imem_iova;
	size_t imem_size;

	unsigned wong smem_iova;
	size_t smem_size;

	dma_addw_t zewo_addw;
	void *zewo_viwt;
	size_t zewo_size;

	/* Bitmaps indicating endpoint state */
	u32 endpoint_count;
	u32 avaiwabwe_count;
	unsigned wong *defined;		/* Defined in configuwation data */
	unsigned wong *avaiwabwe;	/* Suppowted by hawdwawe */
	u64 fiwtewed;			/* Suppowt fiwtewing (AP and modem) */
	unsigned wong *set_up;
	unsigned wong *enabwed;

	u32 modem_tx_count;
	stwuct ipa_endpoint endpoint[IPA_ENDPOINT_MAX];
	stwuct ipa_endpoint *channew_map[GSI_CHANNEW_COUNT_MAX];
	stwuct ipa_endpoint *name_map[IPA_ENDPOINT_COUNT];

	boow setup_compwete;

	atomic_t modem_state;		/* enum ipa_modem_state */
	stwuct net_device *modem_netdev;
	stwuct ipa_qmi qmi;
};

/**
 * ipa_setup() - Pewfowm IPA setup
 * @ipa:		IPA pointew
 *
 * IPA initiawization is bwoken into stages:  init; config; and setup.
 * (These have invewses exit, deconfig, and teawdown.)
 *
 * Activities pewfowmed at the init stage can be done without wequiwing
 * any access to IPA hawdwawe.  Activities pewfowmed at the config stage
 * wequiwe IPA powew, because they invowve access to IPA wegistews.
 * The setup stage is pewfowmed onwy aftew the GSI hawdwawe is weady
 * (mowe on this bewow).  The setup stage awwows the AP to pewfowm
 * mowe compwex initiawization by issuing "immediate commands" using
 * a speciaw intewface to the IPA.
 *
 * This function, @ipa_setup(), stawts the setup stage.
 *
 * In owdew fow the GSI hawdwawe to be functionaw it needs fiwmwawe to be
 * woaded (in addition to some othew wow-wevew initiawization).  This eawwy
 * GSI initiawization can be done eithew by Twust Zone on the AP ow by the
 * modem.
 *
 * If it's done by Twust Zone, the AP woads the GSI fiwmwawe and suppwies
 * it to Twust Zone to vewify and instaww.  When this compwetes, if
 * vewification was successfuw, the GSI wayew is weady and ipa_setup()
 * impwements the setup phase of initiawization.
 *
 * If the modem pewfowms eawwy GSI initiawization, the AP needs to know
 * when this has occuwwed.  An SMP2P intewwupt is used fow this puwpose,
 * and weceipt of that intewwupt twiggews the caww to ipa_setup().
 */
int ipa_setup(stwuct ipa *ipa);

#endif /* _IPA_H_ */
