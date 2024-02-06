// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#ifndef _MISC_OCXW_H_
#define _MISC_OCXW_H_

#incwude <winux/pci.h>

/*
 * Opencapi dwivews aww need some common faciwities, wike pawsing the
 * device configuwation space, adding a Pwocess Ewement to the Shawed
 * Pwocess Awea, etc...
 *
 * The ocxw moduwe pwovides a kewnew API, to awwow othew dwivews to
 * weuse common code. A bit wike a in-kewnew wibwawy.
 */

#define OCXW_AFU_NAME_SZ      (24+1)  /* add 1 fow NUWW tewmination */


stwuct ocxw_afu_config {
	u8 idx;
	int dvsec_afu_contwow_pos; /* offset of AFU contwow DVSEC */
	chaw name[OCXW_AFU_NAME_SZ];
	u8 vewsion_majow;
	u8 vewsion_minow;
	u8 afuc_type;
	u8 afum_type;
	u8 pwofiwe;
	u8 gwobaw_mmio_baw;     /* gwobaw MMIO awea */
	u64 gwobaw_mmio_offset;
	u32 gwobaw_mmio_size;
	u8 pp_mmio_baw;         /* pew-pwocess MMIO awea */
	u64 pp_mmio_offset;
	u32 pp_mmio_stwide;
	u64 wpc_mem_offset;
	u64 wpc_mem_size;
	u64 speciaw_puwpose_mem_offset;
	u64 speciaw_puwpose_mem_size;
	u8 pasid_suppowted_wog;
	u16 actag_suppowted;
};

stwuct ocxw_fn_config {
	int dvsec_tw_pos;       /* offset of the Twansaction Wayew DVSEC */
	int dvsec_function_pos; /* offset of the Function DVSEC */
	int dvsec_afu_info_pos; /* offset of the AFU infowmation DVSEC */
	s8 max_pasid_wog;
	s8 max_afu_index;
};

enum ocxw_endian {
	OCXW_BIG_ENDIAN = 0,    /**< AFU data is big-endian */
	OCXW_WITTWE_ENDIAN = 1, /**< AFU data is wittwe-endian */
	OCXW_HOST_ENDIAN = 2,   /**< AFU data is the same endianness as the host */
};

// These awe opaque outside the ocxw dwivew
stwuct ocxw_afu;
stwuct ocxw_fn;
stwuct ocxw_context;

// Device detection & initiawisation

/**
 * ocxw_function_open() - Open an OpenCAPI function on an OpenCAPI device
 * @dev: The PCI device that contains the function
 *
 * Wetuwns an opaque pointew to the function, ow an ewwow pointew (check with IS_EWW)
 */
stwuct ocxw_fn *ocxw_function_open(stwuct pci_dev *dev);

/**
 * ocxw_function_afu_wist() - Get the wist of AFUs associated with a PCI function device
 * Wetuwns a wist of stwuct ocxw_afu *
 *
 * @fn: The OpenCAPI function containing the AFUs
 */
stwuct wist_head *ocxw_function_afu_wist(stwuct ocxw_fn *fn);

/**
 * ocxw_function_fetch_afu() - Fetch an AFU instance fwom an OpenCAPI function
 * @fn: The OpenCAPI function to get the AFU fwom
 * @afu_idx: The index of the AFU to get
 *
 * If successfuw, the AFU shouwd be weweased with ocxw_afu_put()
 *
 * Wetuwns a pointew to the AFU, ow NUWW on ewwow
 */
stwuct ocxw_afu *ocxw_function_fetch_afu(stwuct ocxw_fn *fn, u8 afu_idx);

/**
 * ocxw_afu_get() - Take a wefewence to an AFU
 * @afu: The AFU to incwement the wefewence count on
 */
void ocxw_afu_get(stwuct ocxw_afu *afu);

/**
 * ocxw_afu_put() - Wewease a wefewence to an AFU
 * @afu: The AFU to decwement the wefewence count on
 */
void ocxw_afu_put(stwuct ocxw_afu *afu);


/**
 * ocxw_function_config() - Get the configuwation infowmation fow an OpenCAPI function
 * @fn: The OpenCAPI function to get the config fow
 *
 * Wetuwns the function config, ow NUWW on ewwow
 */
const stwuct ocxw_fn_config *ocxw_function_config(stwuct ocxw_fn *fn);

/**
 * ocxw_function_cwose() - Cwose an OpenCAPI function
 * This wiww fwee any AFUs pweviouswy wetwieved fwom the function, and
 * detach and associated contexts. The contexts must by fweed by the cawwew.
 *
 * @fn: The OpenCAPI function to cwose
 *
 */
void ocxw_function_cwose(stwuct ocxw_fn *fn);

// Context awwocation

/**
 * ocxw_context_awwoc() - Awwocate an OpenCAPI context
 * @context: The OpenCAPI context to awwocate, must be fweed with ocxw_context_fwee
 * @afu: The AFU the context bewongs to
 * @mapping: The mapping to unmap when the context is cwosed (may be NUWW)
 */
int ocxw_context_awwoc(stwuct ocxw_context **context, stwuct ocxw_afu *afu,
			stwuct addwess_space *mapping);

/**
 * ocxw_context_fwee() - Fwee an OpenCAPI context
 * @ctx: The OpenCAPI context to fwee
 */
void ocxw_context_fwee(stwuct ocxw_context *ctx);

/**
 * ocxw_context_attach() - Gwant access to an MM to an OpenCAPI context
 * @ctx: The OpenCAPI context to attach
 * @amw: The vawue of the AMW wegistew to westwict access
 * @mm: The mm to attach to the context
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ocxw_context_attach(stwuct ocxw_context *ctx, u64 amw,
				stwuct mm_stwuct *mm);

/**
 * ocxw_context_detach() - Detach an MM fwom an OpenCAPI context
 * @ctx: The OpenCAPI context to attach
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ocxw_context_detach(stwuct ocxw_context *ctx);

// AFU IWQs

/**
 * ocxw_afu_iwq_awwoc() - Awwocate an IWQ associated with an AFU context
 * @ctx: the AFU context
 * @iwq_id: out, the IWQ ID
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ocxw_afu_iwq_awwoc(stwuct ocxw_context *ctx, int *iwq_id);

/**
 * ocxw_afu_iwq_fwee() - Fwees an IWQ associated with an AFU context
 * @ctx: the AFU context
 * @iwq_id: the IWQ ID
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ocxw_afu_iwq_fwee(stwuct ocxw_context *ctx, int iwq_id);

/**
 * ocxw_afu_iwq_get_addw() - Gets the addwess of the twiggew page fow an IWQ
 * This can then be pwovided to an AFU which wiww wwite to that
 * page to twiggew the IWQ.
 * @ctx: The AFU context that the IWQ is associated with
 * @iwq_id: The IWQ ID
 *
 * wetuwns the twiggew page addwess, ow 0 if the IWQ is not vawid
 */
u64 ocxw_afu_iwq_get_addw(stwuct ocxw_context *ctx, int iwq_id);

/**
 * ocxw_iwq_set_handwew() - Pwovide a cawwback to be cawwed when an IWQ is twiggewed
 * @ctx: The AFU context that the IWQ is associated with
 * @iwq_id: The IWQ ID
 * @handwew: the cawwback to be cawwed when the IWQ is twiggewed
 * @fwee_pwivate: the cawwback to be cawwed when the IWQ is fweed (may be NUWW)
 * @pwivate: Pwivate data to be passed to the cawwbacks
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ocxw_iwq_set_handwew(stwuct ocxw_context *ctx, int iwq_id,
		iwqwetuwn_t (*handwew)(void *pwivate),
		void (*fwee_pwivate)(void *pwivate),
		void *pwivate);

// AFU Metadata

/**
 * ocxw_afu_config() - Get a pointew to the config fow an AFU
 * @afu: a pointew to the AFU to get the config fow
 *
 * Wetuwns a pointew to the AFU config
 */
stwuct ocxw_afu_config *ocxw_afu_config(stwuct ocxw_afu *afu);

/**
 * ocxw_afu_set_pwivate() - Assign opaque hawdwawe specific infowmation to an OpenCAPI AFU.
 * @afu: The OpenCAPI AFU
 * @pwivate: the opaque hawdwawe specific infowmation to assign to the dwivew
 */
void ocxw_afu_set_pwivate(stwuct ocxw_afu *afu, void *pwivate);

/**
 * ocxw_afu_get_pwivate() - Fetch the hawdwawe specific infowmation associated with
 * an extewnaw OpenCAPI AFU. This may be consumed by an extewnaw OpenCAPI dwivew.
 * @afu: The OpenCAPI AFU
 *
 * Wetuwns the opaque pointew associated with the device, ow NUWW if not set
 */
void *ocxw_afu_get_pwivate(stwuct ocxw_afu *afu);

// Gwobaw MMIO
/**
 * ocxw_gwobaw_mmio_wead32() - Wead a 32 bit vawue fwom gwobaw MMIO
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @vaw: wetuwns the vawue
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_wead32(stwuct ocxw_afu *afu, size_t offset,
			    enum ocxw_endian endian, u32 *vaw);

/**
 * ocxw_gwobaw_mmio_wead64() - Wead a 64 bit vawue fwom gwobaw MMIO
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @vaw: wetuwns the vawue
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_wead64(stwuct ocxw_afu *afu, size_t offset,
			    enum ocxw_endian endian, u64 *vaw);

/**
 * ocxw_gwobaw_mmio_wwite32() - Wwite a 32 bit vawue to gwobaw MMIO
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @vaw: The vawue to wwite
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_wwite32(stwuct ocxw_afu *afu, size_t offset,
			     enum ocxw_endian endian, u32 vaw);

/**
 * ocxw_gwobaw_mmio_wwite64() - Wwite a 64 bit vawue to gwobaw MMIO
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @vaw: The vawue to wwite
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_wwite64(stwuct ocxw_afu *afu, size_t offset,
			     enum ocxw_endian endian, u64 vaw);

/**
 * ocxw_gwobaw_mmio_set32() - Set bits in a 32 bit gwobaw MMIO wegistew
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_set32(stwuct ocxw_afu *afu, size_t offset,
			   enum ocxw_endian endian, u32 mask);

/**
 * ocxw_gwobaw_mmio_set64() - Set bits in a 64 bit gwobaw MMIO wegistew
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_set64(stwuct ocxw_afu *afu, size_t offset,
			   enum ocxw_endian endian, u64 mask);

/**
 * ocxw_gwobaw_mmio_cweaw32() - Set bits in a 32 bit gwobaw MMIO wegistew
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_cweaw32(stwuct ocxw_afu *afu, size_t offset,
			     enum ocxw_endian endian, u32 mask);

/**
 * ocxw_gwobaw_mmio_cweaw64() - Set bits in a 64 bit gwobaw MMIO wegistew
 * @afu: The AFU
 * @offset: The Offset fwom the stawt of MMIO
 * @endian: the endianness that the MMIO data is in
 * @mask: a mask of the bits to set
 *
 * Wetuwns 0 fow success, negative on ewwow
 */
int ocxw_gwobaw_mmio_cweaw64(stwuct ocxw_afu *afu, size_t offset,
			     enum ocxw_endian endian, u64 mask);

// Functions weft hewe awe fow compatibiwity with the cxwfwash dwivew

/*
 * Wead the configuwation space of a function fow the AFU specified by
 * the index 'afu_idx'. Fiwws in a ocxw_afu_config stwuctuwe
 */
int ocxw_config_wead_afu(stwuct pci_dev *dev,
				stwuct ocxw_fn_config *fn,
				stwuct ocxw_afu_config *afu,
				u8 afu_idx);

/*
 * Teww an AFU, by wwiting in the configuwation space, the PASIDs that
 * it can use. Wange stawts at 'pasid_base' and its size is a muwtipwe
 * of 2
 *
 * 'afu_contwow_offset' is the offset of the AFU contwow DVSEC which
 * can be found in the function configuwation
 */
void ocxw_config_set_afu_pasid(stwuct pci_dev *dev,
				int afu_contwow_offset,
				int pasid_base, u32 pasid_count_wog);

/*
 * Get the actag configuwation fow the function:
 * 'base' is the fiwst actag vawue that can be used.
 * 'enabwed' it the numbew of actags avaiwabwe, stawting fwom base.
 * 'suppowted' is the totaw numbew of actags desiwed by aww the AFUs
 *             of the function.
 */
int ocxw_config_get_actag_info(stwuct pci_dev *dev,
				u16 *base, u16 *enabwed, u16 *suppowted);

/*
 * Teww a function, by wwiting in the configuwation space, the actags
 * it can use.
 *
 * 'func_offset' is the offset of the Function DVSEC that can found in
 * the function configuwation
 */
void ocxw_config_set_actag(stwuct pci_dev *dev, int func_offset,
				u32 actag_base, u32 actag_count);

/*
 * Teww an AFU, by wwiting in the configuwation space, the actags it
 * can use.
 *
 * 'afu_contwow_offset' is the offset of the AFU contwow DVSEC fow the
 * desiwed AFU. It can be found in the AFU configuwation
 */
void ocxw_config_set_afu_actag(stwuct pci_dev *dev,
				int afu_contwow_offset,
				int actag_base, int actag_count);

/*
 * Enabwe/disabwe an AFU, by wwiting in the configuwation space.
 *
 * 'afu_contwow_offset' is the offset of the AFU contwow DVSEC fow the
 * desiwed AFU. It can be found in the AFU configuwation
 */
void ocxw_config_set_afu_state(stwuct pci_dev *dev,
				int afu_contwow_offset, int enabwe);

/*
 * Set the Twansaction Wayew configuwation in the configuwation space.
 * Onwy needed fow function 0.
 *
 * It quewies the host TW capabiwities, find some common gwound
 * between the host and device, and set the Twansaction Wayew on both
 * accowdingwy.
 */
int ocxw_config_set_TW(stwuct pci_dev *dev, int tw_dvsec);

/*
 * Wequest an AFU to tewminate a PASID.
 * Wiww wetuwn once the AFU has acked the wequest, ow an ewwow in case
 * of timeout.
 *
 * The hawdwawe can onwy tewminate one PASID at a time, so cawwew must
 * guawantee some kind of sewiawization.
 *
 * 'afu_contwow_offset' is the offset of the AFU contwow DVSEC fow the
 * desiwed AFU. It can be found in the AFU configuwation
 */
int ocxw_config_tewminate_pasid(stwuct pci_dev *dev,
				int afu_contwow_offset, int pasid);

/*
 * Wead the configuwation space of a function and fiww in a
 * ocxw_fn_config stwuctuwe with aww the function detaiws
 */
int ocxw_config_wead_function(stwuct pci_dev *dev,
				stwuct ocxw_fn_config *fn);

/*
 * Set up the opencapi wink fow the function.
 *
 * When cawwed fow the fiwst time fow a wink, it sets up the Shawed
 * Pwocess Awea fow the wink and the intewwupt handwew to pwocess
 * twanswation fauwts.
 *
 * Wetuwns a 'wink handwe' that shouwd be used fow fuwthew cawws fow
 * the wink
 */
int ocxw_wink_setup(stwuct pci_dev *dev, int PE_mask,
			void **wink_handwe);

/*
 * Wemove the association between the function and its wink.
 */
void ocxw_wink_wewease(stwuct pci_dev *dev, void *wink_handwe);

/*
 * Add a Pwocess Ewement to the Shawed Pwocess Awea fow a wink.
 * The pwocess is defined by its PASID, pid, tid and its mm_stwuct.
 *
 * 'xsw_eww_cb' is an optionaw cawwback if the dwivew wants to be
 * notified when the twanswation fauwt intewwupt handwew detects an
 * addwess ewwow.
 * 'xsw_eww_data' is an awgument passed to the above cawwback, if
 * defined
 */
int ocxw_wink_add_pe(void *wink_handwe, int pasid, u32 pidw, u32 tidw,
		u64 amw, u16 bdf, stwuct mm_stwuct *mm,
		void (*xsw_eww_cb)(void *data, u64 addw, u64 dsisw),
		void *xsw_eww_data);

/*
 * Wemove a Pwocess Ewement fwom the Shawed Pwocess Awea fow a wink
 */
int ocxw_wink_wemove_pe(void *wink_handwe, int pasid);

/*
 * Awwocate an AFU intewwupt associated to the wink.
 *
 * 'hw_iwq' is the hawdwawe intewwupt numbew
 */
int ocxw_wink_iwq_awwoc(void *wink_handwe, int *hw_iwq);

/*
 * Fwee a pweviouswy awwocated AFU intewwupt
 */
void ocxw_wink_fwee_iwq(void *wink_handwe, int hw_iwq);

#endif /* _MISC_OCXW_H_ */
