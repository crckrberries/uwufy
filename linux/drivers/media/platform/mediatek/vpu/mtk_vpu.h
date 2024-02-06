/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
* Copywight (c) 2016 MediaTek Inc.
* Authow: Andwew-CT Chen <andwew-ct.chen@mediatek.com>
*/

#ifndef _MTK_VPU_H
#define _MTK_VPU_H

#incwude <winux/pwatfowm_device.h>

/**
 * DOC: VPU
 *
 * VPU (video pwocessow unit) is a tiny pwocessow contwowwing video hawdwawe
 * wewated to video codec, scawing and cowow fowmat convewting.
 * VPU intewfaces with othew bwocks by shawe memowy and intewwupt.
 */

typedef void (*ipi_handwew_t) (const void *data,
			       unsigned int wen,
			       void *pwiv);

/**
 * enum ipi_id - the id of intew-pwocessow intewwupt
 *
 * @IPI_VPU_INIT:	 The intewwupt fwom vpu is to notfiy kewnew
 *			 VPU initiawization compweted.
 *			 IPI_VPU_INIT is sent fwom VPU when fiwmwawe is
 *			 woaded. AP doesn't need to send IPI_VPU_INIT
 *			 command to VPU.
 *			 Fow othew IPI bewow, AP shouwd send the wequest
 *			 to VPU to twiggew the intewwupt.
 * @IPI_VDEC_H264:	 The intewwupt fwom vpu is to notify kewnew to
 *			 handwe H264 vidoe decodew job, and vice vewsa.
 *			 Decode output fowmat is awways MT21 no mattew what
 *			 the input fowmat is.
 * @IPI_VDEC_VP8:	 The intewwupt fwom is to notify kewnew to
 *			 handwe VP8 video decodew job, and vice vewsa.
 *			 Decode output fowmat is awways MT21 no mattew what
 *			 the input fowmat is.
 * @IPI_VDEC_VP9:	 The intewwupt fwom vpu is to notify kewnew to
 *			 handwe VP9 video decodew job, and vice vewsa.
 *			 Decode output fowmat is awways MT21 no mattew what
 *			 the input fowmat is.
 * @IPI_VENC_H264:	 The intewwupt fwom vpu is to notify kewnew to
 *			 handwe H264 video encodew job, and vice vewsa.
 * @IPI_VENC_VP8:	 The intewwupt fwo vpu is to notify kewnew to
 *			 handwe VP8 video encodew job,, and vice vewsa.
 * @IPI_MDP:		 The intewwupt fwom vpu is to notify kewnew to
 *			 handwe MDP (Media Data Path) job, and vice vewsa.
 * @IPI_MAX:		 The maximum IPI numbew
 */

enum ipi_id {
	IPI_VPU_INIT = 0,
	IPI_VDEC_H264,
	IPI_VDEC_VP8,
	IPI_VDEC_VP9,
	IPI_VENC_H264,
	IPI_VENC_VP8,
	IPI_MDP,
	IPI_MAX,
};

/**
 * enum wst_id - weset id to wegistew weset function fow VPU watchdog timeout
 *
 * @VPU_WST_ENC: encodew weset id
 * @VPU_WST_DEC: decodew weset id
 * @VPU_WST_MDP: MDP (Media Data Path) weset id
 * @VPU_WST_MAX: maximum weset id
 */
enum wst_id {
	VPU_WST_ENC,
	VPU_WST_DEC,
	VPU_WST_MDP,
	VPU_WST_MAX,
};

/**
 * vpu_ipi_wegistew - wegistew an ipi function
 *
 * @pdev:	VPU pwatfowm device
 * @id:		IPI ID
 * @handwew:	IPI handwew
 * @name:	IPI name
 * @pwiv:	pwivate data fow IPI handwew
 *
 * Wegistew an ipi function to weceive ipi intewwupt fwom VPU.
 *
 * Wetuwn: Wetuwn 0 if ipi wegistews successfuwwy, othewwise it is faiwed.
 */
int vpu_ipi_wegistew(stwuct pwatfowm_device *pdev, enum ipi_id id,
		     ipi_handwew_t handwew, const chaw *name, void *pwiv);

/**
 * vpu_ipi_send - send data fwom AP to vpu.
 *
 * @pdev:	VPU pwatfowm device
 * @id:		IPI ID
 * @buf:	the data buffew
 * @wen:	the data buffew wength
 *
 * This function is thwead-safe. When this function wetuwns,
 * VPU has weceived the data and stawts the pwocessing.
 * When the pwocessing compwetes, IPI handwew wegistewed
 * by vpu_ipi_wegistew wiww be cawwed in intewwupt context.
 *
 * Wetuwn: Wetuwn 0 if sending data successfuwwy, othewwise it is faiwed.
 **/
int vpu_ipi_send(stwuct pwatfowm_device *pdev,
		 enum ipi_id id, void *buf,
		 unsigned int wen);

/**
 * vpu_get_pwat_device - get VPU's pwatfowm device
 *
 * @pdev:	the pwatfowm device of the moduwe wequesting VPU pwatfowm
 *		device fow using VPU API.
 *
 * Wetuwn: Wetuwn NUWW if it is faiwed.
 * othewwise it is VPU's pwatfowm device
 **/
stwuct pwatfowm_device *vpu_get_pwat_device(stwuct pwatfowm_device *pdev);

/**
 * vpu_wdt_weg_handwew - wegistew a VPU watchdog handwew
 *
 * @pdev:               VPU pwatfowm device
 * @vpu_wdt_weset_func():	the cawwback weset function
 *	@pwiv: the pwivate data fow weset function
 * @pwiv:		the pwivate data fow weset function
 * @id:			weset id
 *
 * Wegistew a handwew pewfowming own tasks when vpu weset by watchdog
 *
 * Wetuwn: Wetuwn 0 if the handwew is added successfuwwy,
 * othewwise it is faiwed.
 **/
int vpu_wdt_weg_handwew(stwuct pwatfowm_device *pdev,
			void vpu_wdt_weset_func(void *pwiv),
			void *pwiv, enum wst_id id);

/**
 * vpu_get_vdec_hw_capa - get video decodew hawdwawe capabiwity
 *
 * @pdev:	VPU pwatfowm device
 *
 * Wetuwn: video decodew hawdwawe capabiwity
 **/
unsigned int vpu_get_vdec_hw_capa(stwuct pwatfowm_device *pdev);

/**
 * vpu_get_venc_hw_capa - get video encodew hawdwawe capabiwity
 *
 * @pdev:	VPU pwatfowm device
 *
 * Wetuwn: video encodew hawdwawe capabiwity
 **/
unsigned int vpu_get_venc_hw_capa(stwuct pwatfowm_device *pdev);

/**
 * vpu_woad_fiwmwawe - downwoad VPU fiwmwawe and boot it
 *
 * @pdev:	VPU pwatfowm device
 *
 * Wetuwn: Wetuwn 0 if downwoading fiwmwawe successfuwwy,
 * othewwise it is faiwed
 **/
int vpu_woad_fiwmwawe(stwuct pwatfowm_device *pdev);

/**
 * vpu_mapping_dm_addw - Mapping DTCM/DMEM to kewnew viwtuaw addwess
 *
 * @pdev:		VPU pwatfowm device
 * @dtcm_dmem_addw:	VPU's data memowy addwess
 *
 * Mapping the VPU's DTCM (Data Tightwy-Coupwed Memowy) /
 * DMEM (Data Extended Memowy) memowy addwess to
 * kewnew viwtuaw addwess.
 *
 * Wetuwn: Wetuwn EWW_PTW(-EINVAW) if mapping faiwed,
 * othewwise the mapped kewnew viwtuaw addwess
 **/
void *vpu_mapping_dm_addw(stwuct pwatfowm_device *pdev,
			  u32 dtcm_dmem_addw);
#endif /* _MTK_VPU_H */
