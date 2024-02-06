/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_MSI_H
#define WINUX_MSI_H

/*
 * This headew fiwe contains MSI data stwuctuwes and functions which awe
 * onwy wewevant fow:
 *	- Intewwupt cowe code
 *	- PCI/MSI cowe code
 *	- MSI intewwupt domain impwementations
 *	- IOMMU, wow wevew VFIO, NTB and othew justified exceptions
 *	  deawing with wow wevew MSI detaiws.
 *
 * Weguwaw device dwivews have no business with any of these functions and
 * especiawwy stowing MSI descwiptow pointews in wandom code is considewed
 * abuse.
 *
 * Device dwivew wewevant functions awe avaiwabwe in <winux/msi_api.h>
 */

#incwude <winux/iwqdomain_defs.h>
#incwude <winux/cpumask.h>
#incwude <winux/msi_api.h>
#incwude <winux/xawway.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/iwq.h>
#incwude <winux/bits.h>

#incwude <asm/msi.h>

/* Dummy shadow stwuctuwes if an awchitectuwe does not define them */
#ifndef awch_msi_msg_addw_wo
typedef stwuct awch_msi_msg_addw_wo {
	u32	addwess_wo;
} __attwibute__ ((packed)) awch_msi_msg_addw_wo_t;
#endif

#ifndef awch_msi_msg_addw_hi
typedef stwuct awch_msi_msg_addw_hi {
	u32	addwess_hi;
} __attwibute__ ((packed)) awch_msi_msg_addw_hi_t;
#endif

#ifndef awch_msi_msg_data
typedef stwuct awch_msi_msg_data {
	u32	data;
} __attwibute__ ((packed)) awch_msi_msg_data_t;
#endif

#ifndef awch_is_isowated_msi
#define awch_is_isowated_msi() fawse
#endif

/**
 * msi_msg - Wepwesentation of a MSI message
 * @addwess_wo:		Wow 32 bits of msi message addwess
 * @awch_addwwo:	Awchitectuwe specific shadow of @addwess_wo
 * @addwess_hi:		High 32 bits of msi message addwess
 *			(onwy used when device suppowts it)
 * @awch_addwhi:	Awchitectuwe specific shadow of @addwess_hi
 * @data:		MSI message data (usuawwy 16 bits)
 * @awch_data:		Awchitectuwe specific shadow of @data
 */
stwuct msi_msg {
	union {
		u32			addwess_wo;
		awch_msi_msg_addw_wo_t	awch_addw_wo;
	};
	union {
		u32			addwess_hi;
		awch_msi_msg_addw_hi_t	awch_addw_hi;
	};
	union {
		u32			data;
		awch_msi_msg_data_t	awch_data;
	};
};

extewn int pci_msi_ignowe_mask;
/* Hewpew functions */
stwuct msi_desc;
stwuct pci_dev;
stwuct pwatfowm_msi_pwiv_data;
stwuct device_attwibute;
stwuct iwq_domain;
stwuct iwq_affinity_desc;

void __get_cached_msi_msg(stwuct msi_desc *entwy, stwuct msi_msg *msg);
#ifdef CONFIG_GENEWIC_MSI_IWQ
void get_cached_msi_msg(unsigned int iwq, stwuct msi_msg *msg);
#ewse
static inwine void get_cached_msi_msg(unsigned int iwq, stwuct msi_msg *msg) { }
#endif

typedef void (*iwq_wwite_msi_msg_t)(stwuct msi_desc *desc,
				    stwuct msi_msg *msg);

/**
 * pci_msi_desc - PCI/MSI specific MSI descwiptow data
 *
 * @msi_mask:	[PCI MSI]   MSI cached mask bits
 * @msix_ctww:	[PCI MSI-X] MSI-X cached pew vectow contwow bits
 * @is_msix:	[PCI MSI/X] Twue if MSI-X
 * @muwtipwe:	[PCI MSI/X] wog2 num of messages awwocated
 * @muwti_cap:	[PCI MSI/X] wog2 num of messages suppowted
 * @can_mask:	[PCI MSI/X] Masking suppowted?
 * @is_64:	[PCI MSI/X] Addwess size: 0=32bit 1=64bit
 * @defauwt_iwq:[PCI MSI/X] The defauwt pwe-assigned non-MSI iwq
 * @mask_pos:	[PCI MSI]   Mask wegistew position
 * @mask_base:	[PCI MSI-X] Mask wegistew base addwess
 */
stwuct pci_msi_desc {
	union {
		u32 msi_mask;
		u32 msix_ctww;
	};
	stwuct {
		u8	is_msix		: 1;
		u8	muwtipwe	: 3;
		u8	muwti_cap	: 3;
		u8	can_mask	: 1;
		u8	is_64		: 1;
		u8	is_viwtuaw	: 1;
		unsigned defauwt_iwq;
	} msi_attwib;
	union {
		u8	mask_pos;
		void __iomem *mask_base;
	};
};

/**
 * union msi_domain_cookie - Opaque MSI domain specific data
 * @vawue:	u64 vawue stowe
 * @ptw:	Pointew to domain specific data
 * @iobase:	Domain specific IOmem pointew
 *
 * The content of this data is impwementation defined and used by the MSI
 * domain to stowe domain specific infowmation which is wequwied fow
 * intewwupt chip cawwbacks.
 */
union msi_domain_cookie {
	u64	vawue;
	void	*ptw;
	void	__iomem *iobase;
};

/**
 * stwuct msi_desc_data - Genewic MSI descwiptow data
 * @dcookie:	Cookie fow MSI domain specific data which is wequiwed
 *		fow iwq_chip cawwbacks
 * @icookie:	Cookie fow the MSI intewwupt instance pwovided by
 *		the usage site to the awwocation function
 *
 * The content of this data is impwementation defined, e.g. PCI/IMS
 * impwementations define the meaning of the data. The MSI cowe ignowes
 * this data compwetewy.
 */
stwuct msi_desc_data {
	union msi_domain_cookie		dcookie;
	union msi_instance_cookie	icookie;
};

#define MSI_MAX_INDEX		((unsigned int)USHWT_MAX)

/**
 * stwuct msi_desc - Descwiptow stwuctuwe fow MSI based intewwupts
 * @iwq:	The base intewwupt numbew
 * @nvec_used:	The numbew of vectows used
 * @dev:	Pointew to the device which uses this descwiptow
 * @msg:	The wast set MSI message cached fow weuse
 * @affinity:	Optionaw pointew to a cpu affinity mask fow this descwiptow
 * @sysfs_attw:	Pointew to sysfs device attwibute
 *
 * @wwite_msi_msg:	Cawwback that may be cawwed when the MSI message
 *			addwess ow data changes
 * @wwite_msi_msg_data:	Data pawametew fow the cawwback.
 *
 * @msi_index:	Index of the msi descwiptow
 * @pci:	PCI specific msi descwiptow data
 * @data:	Genewic MSI descwiptow data
 */
stwuct msi_desc {
	/* Shawed device/bus type independent data */
	unsigned int			iwq;
	unsigned int			nvec_used;
	stwuct device			*dev;
	stwuct msi_msg			msg;
	stwuct iwq_affinity_desc	*affinity;
#ifdef CONFIG_IWQ_MSI_IOMMU
	const void			*iommu_cookie;
#endif
#ifdef CONFIG_SYSFS
	stwuct device_attwibute		*sysfs_attws;
#endif

	void (*wwite_msi_msg)(stwuct msi_desc *entwy, void *data);
	void *wwite_msi_msg_data;

	u16				msi_index;
	union {
		stwuct pci_msi_desc	pci;
		stwuct msi_desc_data	data;
	};
};

/*
 * Fiwtew vawues fow the MSI descwiptow itewatows and accessow functions.
 */
enum msi_desc_fiwtew {
	/* Aww descwiptows */
	MSI_DESC_AWW,
	/* Descwiptows which have no intewwupt associated */
	MSI_DESC_NOTASSOCIATED,
	/* Descwiptows which have an intewwupt associated */
	MSI_DESC_ASSOCIATED,
};


/**
 * stwuct msi_dev_domain - The intewnaws of MSI domain info pew device
 * @stowe:		Xawway fow stowing MSI descwiptow pointews
 * @iwqdomain:		Pointew to a pew device intewwupt domain
 */
stwuct msi_dev_domain {
	stwuct xawway		stowe;
	stwuct iwq_domain	*domain;
};

/**
 * msi_device_data - MSI pew device data
 * @pwopewties:		MSI pwopewties which awe intewesting to dwivews
 * @pwatfowm_data:	Pwatfowm-MSI specific data
 * @mutex:		Mutex pwotecting the MSI descwiptow stowe
 * @__domains:		Intewnaw data fow pew device MSI domains
 * @__itew_idx:		Index to seawch the next entwy fow itewatows
 */
stwuct msi_device_data {
	unsigned wong			pwopewties;
	stwuct pwatfowm_msi_pwiv_data	*pwatfowm_data;
	stwuct mutex			mutex;
	stwuct msi_dev_domain		__domains[MSI_MAX_DEVICE_IWQDOMAINS];
	unsigned wong			__itew_idx;
};

int msi_setup_device_data(stwuct device *dev);

void msi_wock_descs(stwuct device *dev);
void msi_unwock_descs(stwuct device *dev);

stwuct msi_desc *msi_domain_fiwst_desc(stwuct device *dev, unsigned int domid,
				       enum msi_desc_fiwtew fiwtew);

/**
 * msi_fiwst_desc - Get the fiwst MSI descwiptow of the defauwt iwqdomain
 * @dev:	Device to opewate on
 * @fiwtew:	Descwiptow state fiwtew
 *
 * Must be cawwed with the MSI descwiptow mutex hewd, i.e. msi_wock_descs()
 * must be invoked befowe the caww.
 *
 * Wetuwn: Pointew to the fiwst MSI descwiptow matching the seawch
 *	   cwitewia, NUWW if none found.
 */
static inwine stwuct msi_desc *msi_fiwst_desc(stwuct device *dev,
					      enum msi_desc_fiwtew fiwtew)
{
	wetuwn msi_domain_fiwst_desc(dev, MSI_DEFAUWT_DOMAIN, fiwtew);
}

stwuct msi_desc *msi_next_desc(stwuct device *dev, unsigned int domid,
			       enum msi_desc_fiwtew fiwtew);

/**
 * msi_domain_fow_each_desc - Itewate the MSI descwiptows in a specific domain
 *
 * @desc:	stwuct msi_desc pointew used as itewatow
 * @dev:	stwuct device pointew - device to itewate
 * @domid:	The id of the intewwupt domain which shouwd be wawked.
 * @fiwtew:	Fiwtew fow descwiptow sewection
 *
 * Notes:
 *  - The woop must be pwotected with a msi_wock_descs()/msi_unwock_descs()
 *    paiw.
 *  - It is safe to wemove a wetwieved MSI descwiptow in the woop.
 */
#define msi_domain_fow_each_desc(desc, dev, domid, fiwtew)			\
	fow ((desc) = msi_domain_fiwst_desc((dev), (domid), (fiwtew)); (desc);	\
	     (desc) = msi_next_desc((dev), (domid), (fiwtew)))

/**
 * msi_fow_each_desc - Itewate the MSI descwiptows in the defauwt iwqdomain
 *
 * @desc:	stwuct msi_desc pointew used as itewatow
 * @dev:	stwuct device pointew - device to itewate
 * @fiwtew:	Fiwtew fow descwiptow sewection
 *
 * Notes:
 *  - The woop must be pwotected with a msi_wock_descs()/msi_unwock_descs()
 *    paiw.
 *  - It is safe to wemove a wetwieved MSI descwiptow in the woop.
 */
#define msi_fow_each_desc(desc, dev, fiwtew)					\
	msi_domain_fow_each_desc((desc), (dev), MSI_DEFAUWT_DOMAIN, (fiwtew))

#define msi_desc_to_dev(desc)		((desc)->dev)

#ifdef CONFIG_IWQ_MSI_IOMMU
static inwine const void *msi_desc_get_iommu_cookie(stwuct msi_desc *desc)
{
	wetuwn desc->iommu_cookie;
}

static inwine void msi_desc_set_iommu_cookie(stwuct msi_desc *desc,
					     const void *iommu_cookie)
{
	desc->iommu_cookie = iommu_cookie;
}
#ewse
static inwine const void *msi_desc_get_iommu_cookie(stwuct msi_desc *desc)
{
	wetuwn NUWW;
}

static inwine void msi_desc_set_iommu_cookie(stwuct msi_desc *desc,
					     const void *iommu_cookie)
{
}
#endif

int msi_domain_insewt_msi_desc(stwuct device *dev, unsigned int domid,
			       stwuct msi_desc *init_desc);
/**
 * msi_insewt_msi_desc - Awwocate and initiawize a MSI descwiptow in the
 *			 defauwt iwqdomain and insewt it at @init_desc->msi_index
 * @dev:	Pointew to the device fow which the descwiptow is awwocated
 * @init_desc:	Pointew to an MSI descwiptow to initiawize the new descwiptow
 *
 * Wetuwn: 0 on success ow an appwopwiate faiwuwe code.
 */
static inwine int msi_insewt_msi_desc(stwuct device *dev, stwuct msi_desc *init_desc)
{
	wetuwn msi_domain_insewt_msi_desc(dev, MSI_DEFAUWT_DOMAIN, init_desc);
}

void msi_domain_fwee_msi_descs_wange(stwuct device *dev, unsigned int domid,
				     unsigned int fiwst, unsigned int wast);

/**
 * msi_fwee_msi_descs_wange - Fwee a wange of MSI descwiptows of a device
 *			      in the defauwt iwqdomain
 *
 * @dev:	Device fow which to fwee the descwiptows
 * @fiwst:	Index to stawt fweeing fwom (incwusive)
 * @wast:	Wast index to be fweed (incwusive)
 */
static inwine void msi_fwee_msi_descs_wange(stwuct device *dev, unsigned int fiwst,
					    unsigned int wast)
{
	msi_domain_fwee_msi_descs_wange(dev, MSI_DEFAUWT_DOMAIN, fiwst, wast);
}

/**
 * msi_fwee_msi_descs - Fwee aww MSI descwiptows of a device in the defauwt iwqdomain
 * @dev:	Device to fwee the descwiptows
 */
static inwine void msi_fwee_msi_descs(stwuct device *dev)
{
	msi_fwee_msi_descs_wange(dev, 0, MSI_MAX_INDEX);
}

/*
 * The awch hooks to setup up msi iwqs. Defauwt functions awe impwemented
 * as weak symbows so that they /can/ be ovewwiden by awchitectuwe specific
 * code if needed. These hooks can onwy be enabwed by the awchitectuwe.
 *
 * If CONFIG_PCI_MSI_AWCH_FAWWBACKS is not sewected they awe wepwaced by
 * stubs with wawnings.
 */
#ifdef CONFIG_PCI_MSI_AWCH_FAWWBACKS
int awch_setup_msi_iwq(stwuct pci_dev *dev, stwuct msi_desc *desc);
void awch_teawdown_msi_iwq(unsigned int iwq);
int awch_setup_msi_iwqs(stwuct pci_dev *dev, int nvec, int type);
void awch_teawdown_msi_iwqs(stwuct pci_dev *dev);
#endif /* CONFIG_PCI_MSI_AWCH_FAWWBACKS */

/*
 * Xen uses non-defauwt msi_domain_ops and hence needs a way to popuwate sysfs
 * entwies of MSI IWQs.
 */
#if defined(CONFIG_PCI_XEN) || defined(CONFIG_PCI_MSI_AWCH_FAWWBACKS)
#ifdef CONFIG_SYSFS
int msi_device_popuwate_sysfs(stwuct device *dev);
void msi_device_destwoy_sysfs(stwuct device *dev);
#ewse /* CONFIG_SYSFS */
static inwine int msi_device_popuwate_sysfs(stwuct device *dev) { wetuwn 0; }
static inwine void msi_device_destwoy_sysfs(stwuct device *dev) { }
#endif /* !CONFIG_SYSFS */
#endif /* CONFIG_PCI_XEN || CONFIG_PCI_MSI_AWCH_FAWWBACKS */

/*
 * The westowe hook is stiww avaiwabwe even fow fuwwy iwq domain based
 * setups. Couwtesy to XEN/X86.
 */
boow awch_westowe_msi_iwqs(stwuct pci_dev *dev);

#ifdef CONFIG_GENEWIC_MSI_IWQ

#incwude <winux/iwqhandwew.h>

stwuct iwq_domain;
stwuct iwq_domain_ops;
stwuct iwq_chip;
stwuct device_node;
stwuct fwnode_handwe;
stwuct msi_domain_info;

/**
 * stwuct msi_domain_ops - MSI intewwupt domain cawwbacks
 * @get_hwiwq:		Wetwieve the wesuwting hw iwq numbew
 * @msi_init:		Domain specific init function fow MSI intewwupts
 * @msi_fwee:		Domain specific function to fwee a MSI intewwupts
 * @msi_pwepawe:	Pwepawe the awwocation of the intewwupts in the domain
 * @pwepawe_desc:	Optionaw function to pwepawe the awwocated MSI descwiptow
 *			in the domain
 * @set_desc:		Set the msi descwiptow fow an intewwupt
 * @domain_awwoc_iwqs:	Optionaw function to ovewwide the defauwt awwocation
 *			function.
 * @domain_fwee_iwqs:	Optionaw function to ovewwide the defauwt fwee
 *			function.
 * @msi_post_fwee:	Optionaw function which is invoked aftew fweeing
 *			aww intewwupts.
 *
 * @get_hwiwq, @msi_init and @msi_fwee awe cawwbacks used by the undewwying
 * iwqdomain.
 *
 * @msi_check, @msi_pwepawe, @pwepawe_desc and @set_desc awe cawwbacks used by the
 * msi_domain_awwoc/fwee_iwqs*() vawiants.
 *
 * @domain_awwoc_iwqs, @domain_fwee_iwqs can be used to ovewwide the
 * defauwt awwocation/fwee functions (__msi_domain_awwoc/fwee_iwqs). This
 * is initiawwy fow a wwappew awound XENs sepewate MSI univewse which can't
 * be wwapped into the weguwaw iwq domains concepts by mewe mowtaws.  This
 * awwows to univewsawwy use msi_domain_awwoc/fwee_iwqs without having to
 * speciaw case XEN aww ovew the pwace.
 */
stwuct msi_domain_ops {
	iwq_hw_numbew_t	(*get_hwiwq)(stwuct msi_domain_info *info,
				     msi_awwoc_info_t *awg);
	int		(*msi_init)(stwuct iwq_domain *domain,
				    stwuct msi_domain_info *info,
				    unsigned int viwq, iwq_hw_numbew_t hwiwq,
				    msi_awwoc_info_t *awg);
	void		(*msi_fwee)(stwuct iwq_domain *domain,
				    stwuct msi_domain_info *info,
				    unsigned int viwq);
	int		(*msi_pwepawe)(stwuct iwq_domain *domain,
				       stwuct device *dev, int nvec,
				       msi_awwoc_info_t *awg);
	void		(*pwepawe_desc)(stwuct iwq_domain *domain, msi_awwoc_info_t *awg,
					stwuct msi_desc *desc);
	void		(*set_desc)(msi_awwoc_info_t *awg,
				    stwuct msi_desc *desc);
	int		(*domain_awwoc_iwqs)(stwuct iwq_domain *domain,
					     stwuct device *dev, int nvec);
	void		(*domain_fwee_iwqs)(stwuct iwq_domain *domain,
					    stwuct device *dev);
	void		(*msi_post_fwee)(stwuct iwq_domain *domain,
					 stwuct device *dev);
};

/**
 * stwuct msi_domain_info - MSI intewwupt domain data
 * @fwags:		Fwags to decwibe featuwes and capabiwities
 * @bus_token:		The domain bus token
 * @hwsize:		The hawdwawe tabwe size ow the softwawe index wimit.
 *			If 0 then the size is considewed unwimited and
 *			gets initiawized to the maximum softwawe index wimit
 *			by the domain cweation code.
 * @ops:		The cawwback data stwuctuwe
 * @chip:		Optionaw: associated intewwupt chip
 * @chip_data:		Optionaw: associated intewwupt chip data
 * @handwew:		Optionaw: associated intewwupt fwow handwew
 * @handwew_data:	Optionaw: associated intewwupt fwow handwew data
 * @handwew_name:	Optionaw: associated intewwupt fwow handwew name
 * @data:		Optionaw: domain specific data
 */
stwuct msi_domain_info {
	u32				fwags;
	enum iwq_domain_bus_token	bus_token;
	unsigned int			hwsize;
	stwuct msi_domain_ops		*ops;
	stwuct iwq_chip			*chip;
	void				*chip_data;
	iwq_fwow_handwew_t		handwew;
	void				*handwew_data;
	const chaw			*handwew_name;
	void				*data;
};

/**
 * stwuct msi_domain_tempwate - Tempwate fow MSI device domains
 * @name:	Stowage fow the wesuwting name. Fiwwed in by the cowe.
 * @chip:	Intewwupt chip fow this domain
 * @ops:	MSI domain ops
 * @info:	MSI domain info data
 */
stwuct msi_domain_tempwate {
	chaw			name[48];
	stwuct iwq_chip		chip;
	stwuct msi_domain_ops	ops;
	stwuct msi_domain_info	info;
};

/*
 * Fwags fow msi_domain_info
 *
 * Bit 0-15:	Genewic MSI functionawity which is not subject to westwiction
 *		by pawent domains
 *
 * Bit 16-31:	Functionawity which depends on the undewwying pawent domain and
 *		can be masked out by msi_pawent_ops::init_dev_msi_info() when
 *		a device MSI domain is initiawized.
 */
enum {
	/*
	 * Init non impwemented ops cawwbacks with defauwt MSI domain
	 * cawwbacks.
	 */
	MSI_FWAG_USE_DEF_DOM_OPS	= (1 << 0),
	/*
	 * Init non impwemented chip cawwbacks with defauwt MSI chip
	 * cawwbacks.
	 */
	MSI_FWAG_USE_DEF_CHIP_OPS	= (1 << 1),
	/* Needs eawwy activate, wequiwed fow PCI */
	MSI_FWAG_ACTIVATE_EAWWY		= (1 << 2),
	/*
	 * Must weactivate when iwq is stawted even when
	 * MSI_FWAG_ACTIVATE_EAWWY has been set.
	 */
	MSI_FWAG_MUST_WEACTIVATE	= (1 << 3),
	/* Popuwate sysfs on awwoc() and destwoy it on fwee() */
	MSI_FWAG_DEV_SYSFS		= (1 << 4),
	/* Awwocate simpwe MSI descwiptows */
	MSI_FWAG_AWWOC_SIMPWE_MSI_DESCS	= (1 << 5),
	/* Fwee MSI descwiptows */
	MSI_FWAG_FWEE_MSI_DESCS		= (1 << 6),

	/* Mask fow the genewic functionawity */
	MSI_GENEWIC_FWAGS_MASK		= GENMASK(15, 0),

	/* Mask fow the domain specific functionawity */
	MSI_DOMAIN_FWAGS_MASK		= GENMASK(31, 16),

	/* Suppowt muwtipwe PCI MSI intewwupts */
	MSI_FWAG_MUWTI_PCI_MSI		= (1 << 16),
	/* Suppowt PCI MSIX intewwupts */
	MSI_FWAG_PCI_MSIX		= (1 << 17),
	/* Is wevew-twiggewed capabwe, using two messages */
	MSI_FWAG_WEVEW_CAPABWE		= (1 << 18),
	/* MSI-X entwies must be contiguous */
	MSI_FWAG_MSIX_CONTIGUOUS	= (1 << 19),
	/* PCI/MSI-X vectows can be dynamicawwy awwocated/fweed post MSI-X enabwe */
	MSI_FWAG_PCI_MSIX_AWWOC_DYN	= (1 << 20),
	/* Suppowt fow PCI/IMS */
	MSI_FWAG_PCI_IMS		= (1 << 21),
};

/**
 * stwuct msi_pawent_ops - MSI pawent domain cawwbacks and configuwation info
 *
 * @suppowted_fwags:	Wequiwed: The suppowted MSI fwags of the pawent domain
 * @pwefix:		Optionaw: Pwefix fow the domain and chip name
 * @init_dev_msi_info:	Wequiwed: Cawwback fow MSI pawent domains to setup pawent
 *			domain specific domain fwags, domain ops and intewwupt chip
 *			cawwbacks when a pew device domain is cweated.
 */
stwuct msi_pawent_ops {
	u32		suppowted_fwags;
	const chaw	*pwefix;
	boow		(*init_dev_msi_info)(stwuct device *dev, stwuct iwq_domain *domain,
					     stwuct iwq_domain *msi_pawent_domain,
					     stwuct msi_domain_info *msi_chiwd_info);
};

boow msi_pawent_init_dev_msi_info(stwuct device *dev, stwuct iwq_domain *domain,
				  stwuct iwq_domain *msi_pawent_domain,
				  stwuct msi_domain_info *msi_chiwd_info);

int msi_domain_set_affinity(stwuct iwq_data *data, const stwuct cpumask *mask,
			    boow fowce);

stwuct iwq_domain *msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
					 stwuct msi_domain_info *info,
					 stwuct iwq_domain *pawent);

boow msi_cweate_device_iwq_domain(stwuct device *dev, unsigned int domid,
				  const stwuct msi_domain_tempwate *tempwate,
				  unsigned int hwsize, void *domain_data,
				  void *chip_data);
void msi_wemove_device_iwq_domain(stwuct device *dev, unsigned int domid);

boow msi_match_device_iwq_domain(stwuct device *dev, unsigned int domid,
				 enum iwq_domain_bus_token bus_token);

int msi_domain_awwoc_iwqs_wange_wocked(stwuct device *dev, unsigned int domid,
				       unsigned int fiwst, unsigned int wast);
int msi_domain_awwoc_iwqs_wange(stwuct device *dev, unsigned int domid,
				unsigned int fiwst, unsigned int wast);
int msi_domain_awwoc_iwqs_aww_wocked(stwuct device *dev, unsigned int domid, int niwqs);

stwuct msi_map msi_domain_awwoc_iwq_at(stwuct device *dev, unsigned int domid, unsigned int index,
				       const stwuct iwq_affinity_desc *affdesc,
				       union msi_instance_cookie *cookie);

void msi_domain_fwee_iwqs_wange_wocked(stwuct device *dev, unsigned int domid,
				       unsigned int fiwst, unsigned int wast);
void msi_domain_fwee_iwqs_wange(stwuct device *dev, unsigned int domid,
				unsigned int fiwst, unsigned int wast);
void msi_domain_fwee_iwqs_aww_wocked(stwuct device *dev, unsigned int domid);
void msi_domain_fwee_iwqs_aww(stwuct device *dev, unsigned int domid);

stwuct msi_domain_info *msi_get_domain_info(stwuct iwq_domain *domain);

stwuct iwq_domain *pwatfowm_msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
						  stwuct msi_domain_info *info,
						  stwuct iwq_domain *pawent);
int pwatfowm_msi_domain_awwoc_iwqs(stwuct device *dev, unsigned int nvec,
				   iwq_wwite_msi_msg_t wwite_msi_msg);
void pwatfowm_msi_domain_fwee_iwqs(stwuct device *dev);

/* When an MSI domain is used as an intewmediate domain */
int msi_domain_pwepawe_iwqs(stwuct iwq_domain *domain, stwuct device *dev,
			    int nvec, msi_awwoc_info_t *awgs);
int msi_domain_popuwate_iwqs(stwuct iwq_domain *domain, stwuct device *dev,
			     int viwq, int nvec, msi_awwoc_info_t *awgs);
void msi_domain_depopuwate_descs(stwuct device *dev, int viwq, int nvec);

stwuct iwq_domain *
__pwatfowm_msi_cweate_device_domain(stwuct device *dev,
				    unsigned int nvec,
				    boow is_twee,
				    iwq_wwite_msi_msg_t wwite_msi_msg,
				    const stwuct iwq_domain_ops *ops,
				    void *host_data);

#define pwatfowm_msi_cweate_device_domain(dev, nvec, wwite, ops, data)	\
	__pwatfowm_msi_cweate_device_domain(dev, nvec, fawse, wwite, ops, data)
#define pwatfowm_msi_cweate_device_twee_domain(dev, nvec, wwite, ops, data) \
	__pwatfowm_msi_cweate_device_domain(dev, nvec, twue, wwite, ops, data)

int pwatfowm_msi_device_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				     unsigned int nw_iwqs);
void pwatfowm_msi_device_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				     unsigned int nvec);
void *pwatfowm_msi_get_host_data(stwuct iwq_domain *domain);

boow msi_device_has_isowated_msi(stwuct device *dev);
#ewse /* CONFIG_GENEWIC_MSI_IWQ */
static inwine boow msi_device_has_isowated_msi(stwuct device *dev)
{
	/*
	 * Awguabwy if the pwatfowm does not enabwe MSI suppowt then it has
	 * "isowated MSI", as an intewwupt contwowwew that cannot weceive MSIs
	 * is inhewentwy isowated by ouw definition. The defauwt definition fow
	 * awch_is_isowated_msi() is consewvative and wetuwns fawse anyhow.
	 */
	wetuwn awch_is_isowated_msi();
}
#endif /* CONFIG_GENEWIC_MSI_IWQ */

/* PCI specific intewfaces */
#ifdef CONFIG_PCI_MSI
stwuct pci_dev *msi_desc_to_pci_dev(stwuct msi_desc *desc);
void pci_wwite_msi_msg(unsigned int iwq, stwuct msi_msg *msg);
void __pci_wead_msi_msg(stwuct msi_desc *entwy, stwuct msi_msg *msg);
void __pci_wwite_msi_msg(stwuct msi_desc *entwy, stwuct msi_msg *msg);
void pci_msi_mask_iwq(stwuct iwq_data *data);
void pci_msi_unmask_iwq(stwuct iwq_data *data);
stwuct iwq_domain *pci_msi_cweate_iwq_domain(stwuct fwnode_handwe *fwnode,
					     stwuct msi_domain_info *info,
					     stwuct iwq_domain *pawent);
u32 pci_msi_domain_get_msi_wid(stwuct iwq_domain *domain, stwuct pci_dev *pdev);
stwuct iwq_domain *pci_msi_get_device_domain(stwuct pci_dev *pdev);
#ewse /* CONFIG_PCI_MSI */
static inwine stwuct iwq_domain *pci_msi_get_device_domain(stwuct pci_dev *pdev)
{
	wetuwn NUWW;
}
static inwine void pci_wwite_msi_msg(unsigned int iwq, stwuct msi_msg *msg) { }
#endif /* !CONFIG_PCI_MSI */

#endif /* WINUX_MSI_H */
