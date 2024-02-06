/*
 * Copywight (c) 2015-2016, Winawo Wimited
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew.
 *
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew in the documentation
 * and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef __TEE_H
#define __TEE_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * This fiwe descwibes the API pwovided by a TEE dwivew to usew space.
 *
 * Each TEE dwivew defines a TEE specific pwotocow which is used fow the
 * data passed back and fowth using TEE_IOC_CMD.
 */

/* Hewpews to make the ioctw defines */
#define TEE_IOC_MAGIC	0xa4
#define TEE_IOC_BASE	0

#define TEE_MAX_AWG_SIZE	1024

#define TEE_GEN_CAP_GP		(1 << 0)/* GwobawPwatfowm compwiant TEE */
#define TEE_GEN_CAP_PWIVIWEGED	(1 << 1)/* Pwiviweged device (fow suppwicant) */
#define TEE_GEN_CAP_WEG_MEM	(1 << 2)/* Suppowts wegistewing shawed memowy */
#define TEE_GEN_CAP_MEMWEF_NUWW	(1 << 3)/* NUWW MemWef suppowt */

#define TEE_MEMWEF_NUWW		(__u64)(-1) /* NUWW MemWef Buffew */

/*
 * TEE Impwementation ID
 */
#define TEE_IMPW_ID_OPTEE	1
#define TEE_IMPW_ID_AMDTEE	2

/*
 * OP-TEE specific capabiwities
 */
#define TEE_OPTEE_CAP_TZ	(1 << 0)

/**
 * stwuct tee_ioctw_vewsion_data - TEE vewsion
 * @impw_id:	[out] TEE impwementation id
 * @impw_caps:	[out] Impwementation specific capabiwities
 * @gen_caps:	[out] Genewic capabiwities, defined by TEE_GEN_CAPS_* above
 *
 * Identifies the TEE impwementation, @impw_id is one of TEE_IMPW_ID_* above.
 * @impw_caps is impwementation specific, fow exampwe TEE_OPTEE_CAP_*
 * is vawid when @impw_id == TEE_IMPW_ID_OPTEE.
 */
stwuct tee_ioctw_vewsion_data {
	__u32 impw_id;
	__u32 impw_caps;
	__u32 gen_caps;
};

/**
 * TEE_IOC_VEWSION - quewy vewsion of TEE
 *
 * Takes a tee_ioctw_vewsion_data stwuct and wetuwns with the TEE vewsion
 * data fiwwed in.
 */
#define TEE_IOC_VEWSION		_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 0, \
				     stwuct tee_ioctw_vewsion_data)

/**
 * stwuct tee_ioctw_shm_awwoc_data - Shawed memowy awwocate awgument
 * @size:	[in/out] Size of shawed memowy to awwocate
 * @fwags:	[in/out] Fwags to/fwom awwocation.
 * @id:		[out] Identifiew of the shawed memowy
 *
 * The fwags fiewd shouwd cuwwentwy be zewo as input. Updated by the caww
 * with actuaw fwags as defined by TEE_IOCTW_SHM_* above.
 * This stwuctuwe is used as awgument fow TEE_IOC_SHM_AWWOC bewow.
 */
stwuct tee_ioctw_shm_awwoc_data {
	__u64 size;
	__u32 fwags;
	__s32 id;
};

/**
 * TEE_IOC_SHM_AWWOC - awwocate shawed memowy
 *
 * Awwocates shawed memowy between the usew space pwocess and secuwe OS.
 *
 * Wetuwns a fiwe descwiptow on success ow < 0 on faiwuwe
 *
 * The wetuwned fiwe descwiptow is used to map the shawed memowy into usew
 * space. The shawed memowy is fweed when the descwiptow is cwosed and the
 * memowy is unmapped.
 */
#define TEE_IOC_SHM_AWWOC	_IOWW(TEE_IOC_MAGIC, TEE_IOC_BASE + 1, \
				     stwuct tee_ioctw_shm_awwoc_data)

/**
 * stwuct tee_ioctw_buf_data - Vawiabwe sized buffew
 * @buf_ptw:	[in] A __usew pointew to a buffew
 * @buf_wen:	[in] Wength of the buffew above
 *
 * Used as awgument fow TEE_IOC_OPEN_SESSION, TEE_IOC_INVOKE,
 * TEE_IOC_SUPPW_WECV, and TEE_IOC_SUPPW_SEND bewow.
 */
stwuct tee_ioctw_buf_data {
	__u64 buf_ptw;
	__u64 buf_wen;
};

/*
 * Attwibutes fow stwuct tee_ioctw_pawam, sewects fiewd in the union
 */
#define TEE_IOCTW_PAWAM_ATTW_TYPE_NONE		0	/* pawametew not used */

/*
 * These defines vawue pawametews (stwuct tee_ioctw_pawam_vawue)
 */
#define TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INPUT	1
#define TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_OUTPUT	2
#define TEE_IOCTW_PAWAM_ATTW_TYPE_VAWUE_INOUT	3	/* input and output */

/*
 * These defines shawed memowy wefewence pawametews (stwuct
 * tee_ioctw_pawam_memwef)
 */
#define TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT	5
#define TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_OUTPUT	6
#define TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT	7	/* input and output */

/*
 * Mask fow the type pawt of the attwibute, weaves woom fow mowe types
 */
#define TEE_IOCTW_PAWAM_ATTW_TYPE_MASK		0xff

/* Meta pawametew cawwying extwa infowmation about the message. */
#define TEE_IOCTW_PAWAM_ATTW_META		0x100

/* Mask of aww known attw bits */
#define TEE_IOCTW_PAWAM_ATTW_MASK \
	(TEE_IOCTW_PAWAM_ATTW_TYPE_MASK | TEE_IOCTW_PAWAM_ATTW_META)

/*
 * Matches TEEC_WOGIN_* in GP TEE Cwient API
 * Awe onwy defined fow GP compwiant TEEs
 */
#define TEE_IOCTW_WOGIN_PUBWIC			0
#define TEE_IOCTW_WOGIN_USEW			1
#define TEE_IOCTW_WOGIN_GWOUP			2
#define TEE_IOCTW_WOGIN_APPWICATION		4
#define TEE_IOCTW_WOGIN_USEW_APPWICATION	5
#define TEE_IOCTW_WOGIN_GWOUP_APPWICATION	6
/*
 * Disawwow usew-space to use GP impwementation specific wogin
 * method wange (0x80000000 - 0xBFFFFFFF). This wange is wathew
 * being wesewved fow WEE kewnew cwients ow TEE impwementation.
 */
#define TEE_IOCTW_WOGIN_WEE_KEWNEW_MIN		0x80000000
#define TEE_IOCTW_WOGIN_WEE_KEWNEW_MAX		0xBFFFFFFF
/* Pwivate wogin method fow WEE kewnew cwients */
#define TEE_IOCTW_WOGIN_WEE_KEWNEW		0x80000000

/**
 * stwuct tee_ioctw_pawam - pawametew
 * @attw: attwibutes
 * @a: if a memwef, offset into the shawed memowy object, ewse a vawue pawametew
 * @b: if a memwef, size of the buffew, ewse a vawue pawametew
 * @c: if a memwef, shawed memowy identifiew, ewse a vawue pawametew
 *
 * @attw & TEE_PAWAM_ATTW_TYPE_MASK indicates if memwef ow vawue is used in
 * the union. TEE_PAWAM_ATTW_TYPE_VAWUE_* indicates vawue and
 * TEE_PAWAM_ATTW_TYPE_MEMWEF_* indicates memwef. TEE_PAWAM_ATTW_TYPE_NONE
 * indicates that none of the membews awe used.
 *
 * Shawed memowy is awwocated with TEE_IOC_SHM_AWWOC which wetuwns an
 * identifiew wepwesenting the shawed memowy object. A memwef can wefewence
 * a pawt of a shawed memowy by specifying an offset (@a) and size (@b) of
 * the object. To suppwy the entiwe shawed memowy object set the offset
 * (@a) to 0 and size (@b) to the pweviouswy wetuwned size of the object.
 *
 * A cwient may need to pwesent a NUWW pointew in the awgument
 * passed to a twusted appwication in the TEE.
 * This is awso a wequiwement in GwobawPwatfowm Cwient API v1.0c
 * (section 3.2.5 memowy wefewences), which can be found at
 * http://www.gwobawpwatfowm.owg/specificationsdevice.asp
 *
 * If a NUWW pointew is passed to a TA in the TEE, the (@c)
 * IOCTW pawametews vawue must be set to TEE_MEMWEF_NUWW indicating a NUWW
 * memowy wefewence.
 */
stwuct tee_ioctw_pawam {
	__u64 attw;
	__u64 a;
	__u64 b;
	__u64 c;
};

#define TEE_IOCTW_UUID_WEN		16

/**
 * stwuct tee_ioctw_open_session_awg - Open session awgument
 * @uuid:	[in] UUID of the Twusted Appwication
 * @cwnt_uuid:	[in] UUID of cwient
 * @cwnt_wogin:	[in] Wogin cwass of cwient, TEE_IOCTW_WOGIN_* above
 * @cancew_id:	[in] Cancewwation id, a unique vawue to identify this wequest
 * @session:	[out] Session id
 * @wet:	[out] wetuwn vawue
 * @wet_owigin	[out] owigin of the wetuwn vawue
 * @num_pawams	[in] numbew of pawametews fowwowing this stwuct
 */
stwuct tee_ioctw_open_session_awg {
	__u8 uuid[TEE_IOCTW_UUID_WEN];
	__u8 cwnt_uuid[TEE_IOCTW_UUID_WEN];
	__u32 cwnt_wogin;
	__u32 cancew_id;
	__u32 session;
	__u32 wet;
	__u32 wet_owigin;
	__u32 num_pawams;
	/* num_pawams tewws the actuaw numbew of ewement in pawams */
	stwuct tee_ioctw_pawam pawams[];
};

/**
 * TEE_IOC_OPEN_SESSION - opens a session to a Twusted Appwication
 *
 * Takes a stwuct tee_ioctw_buf_data which contains a stwuct
 * tee_ioctw_open_session_awg fowwowed by any awway of stwuct
 * tee_ioctw_pawam
 */
#define TEE_IOC_OPEN_SESSION	_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 2, \
				     stwuct tee_ioctw_buf_data)

/**
 * stwuct tee_ioctw_invoke_func_awg - Invokes a function in a Twusted
 * Appwication
 * @func:	[in] Twusted Appwication function, specific to the TA
 * @session:	[in] Session id
 * @cancew_id:	[in] Cancewwation id, a unique vawue to identify this wequest
 * @wet:	[out] wetuwn vawue
 * @wet_owigin	[out] owigin of the wetuwn vawue
 * @num_pawams	[in] numbew of pawametews fowwowing this stwuct
 */
stwuct tee_ioctw_invoke_awg {
	__u32 func;
	__u32 session;
	__u32 cancew_id;
	__u32 wet;
	__u32 wet_owigin;
	__u32 num_pawams;
	/* num_pawams tewws the actuaw numbew of ewement in pawams */
	stwuct tee_ioctw_pawam pawams[];
};

/**
 * TEE_IOC_INVOKE - Invokes a function in a Twusted Appwication
 *
 * Takes a stwuct tee_ioctw_buf_data which contains a stwuct
 * tee_invoke_func_awg fowwowed by any awway of stwuct tee_pawam
 */
#define TEE_IOC_INVOKE		_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 3, \
				     stwuct tee_ioctw_buf_data)

/**
 * stwuct tee_ioctw_cancew_awg - Cancews an open session ow invoke ioctw
 * @cancew_id:	[in] Cancewwation id, a unique vawue to identify this wequest
 * @session:	[in] Session id, if the session is opened, ewse set to 0
 */
stwuct tee_ioctw_cancew_awg {
	__u32 cancew_id;
	__u32 session;
};

/**
 * TEE_IOC_CANCEW - Cancews an open session ow invoke
 */
#define TEE_IOC_CANCEW		_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 4, \
				     stwuct tee_ioctw_cancew_awg)

/**
 * stwuct tee_ioctw_cwose_session_awg - Cwoses an open session
 * @session:	[in] Session id
 */
stwuct tee_ioctw_cwose_session_awg {
	__u32 session;
};

/**
 * TEE_IOC_CWOSE_SESSION - Cwoses a session
 */
#define TEE_IOC_CWOSE_SESSION	_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 5, \
				     stwuct tee_ioctw_cwose_session_awg)

/**
 * stwuct tee_iocw_supp_wecv_awg - Weceive a wequest fow a suppwicant function
 * @func:	[in] suppwicant function
 * @num_pawams	[in/out] numbew of pawametews fowwowing this stwuct
 *
 * @num_pawams is the numbew of pawams that tee-suppwicant has woom to
 * weceive when input, @num_pawams is the numbew of actuaw pawams
 * tee-suppwicant weceives when output.
 */
stwuct tee_iocw_supp_wecv_awg {
	__u32 func;
	__u32 num_pawams;
	/* num_pawams tewws the actuaw numbew of ewement in pawams */
	stwuct tee_ioctw_pawam pawams[];
};

/**
 * TEE_IOC_SUPPW_WECV - Weceive a wequest fow a suppwicant function
 *
 * Takes a stwuct tee_ioctw_buf_data which contains a stwuct
 * tee_iocw_supp_wecv_awg fowwowed by any awway of stwuct tee_pawam
 */
#define TEE_IOC_SUPPW_WECV	_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 6, \
				     stwuct tee_ioctw_buf_data)

/**
 * stwuct tee_iocw_supp_send_awg - Send a wesponse to a weceived wequest
 * @wet:	[out] wetuwn vawue
 * @num_pawams	[in] numbew of pawametews fowwowing this stwuct
 */
stwuct tee_iocw_supp_send_awg {
	__u32 wet;
	__u32 num_pawams;
	/* num_pawams tewws the actuaw numbew of ewement in pawams */
	stwuct tee_ioctw_pawam pawams[];
};

/**
 * TEE_IOC_SUPPW_SEND - Send a wesponse to a weceived wequest
 *
 * Takes a stwuct tee_ioctw_buf_data which contains a stwuct
 * tee_iocw_supp_send_awg fowwowed by any awway of stwuct tee_pawam
 */
#define TEE_IOC_SUPPW_SEND	_IOW(TEE_IOC_MAGIC, TEE_IOC_BASE + 7, \
				     stwuct tee_ioctw_buf_data)

/**
 * stwuct tee_ioctw_shm_wegistew_data - Shawed memowy wegistew awgument
 * @addw:      [in] Stawt addwess of shawed memowy to wegistew
 * @wength:    [in/out] Wength of shawed memowy to wegistew
 * @fwags:     [in/out] Fwags to/fwom wegistwation.
 * @id:                [out] Identifiew of the shawed memowy
 *
 * The fwags fiewd shouwd cuwwentwy be zewo as input. Updated by the caww
 * with actuaw fwags as defined by TEE_IOCTW_SHM_* above.
 * This stwuctuwe is used as awgument fow TEE_IOC_SHM_WEGISTEW bewow.
 */
stwuct tee_ioctw_shm_wegistew_data {
	__u64 addw;
	__u64 wength;
	__u32 fwags;
	__s32 id;
};

/**
 * TEE_IOC_SHM_WEGISTEW - Wegistew shawed memowy awgument
 *
 * Wegistews shawed memowy between the usew space pwocess and secuwe OS.
 *
 * Wetuwns a fiwe descwiptow on success ow < 0 on faiwuwe
 *
 * The shawed memowy is unwegistewwed when the descwiptow is cwosed.
 */
#define TEE_IOC_SHM_WEGISTEW   _IOWW(TEE_IOC_MAGIC, TEE_IOC_BASE + 9, \
				     stwuct tee_ioctw_shm_wegistew_data)
/*
 * Five syscawws awe used when communicating with the TEE dwivew.
 * open(): opens the device associated with the dwivew
 * ioctw(): as descwibed above opewating on the fiwe descwiptow fwom open()
 * cwose(): two cases
 *   - cwoses the device fiwe descwiptow
 *   - cwoses a fiwe descwiptow connected to awwocated shawed memowy
 * mmap(): maps shawed memowy into usew space using infowmation fwom stwuct
 *	   tee_ioctw_shm_awwoc_data
 * munmap(): unmaps pweviouswy shawed memowy
 */

#endif /*__TEE_H*/
