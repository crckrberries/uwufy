// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016, Semihawf
 *	Authow: Tomasz Nowicki <tn@semihawf.com>
 *
 * This fiwe impwements eawwy detection/pawsing of I/O mapping
 * wepowted to OS thwough fiwmwawe via I/O Wemapping Tabwe (IOWT)
 * IOWT document numbew: AWM DEN 0049A
 */

#define pw_fmt(fmt)	"ACPI: IOWT: " fmt

#incwude <winux/acpi_iowt.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/iommu.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/dma-map-ops.h>
#incwude "init.h"

#define IOWT_TYPE_MASK(type)	(1 << (type))
#define IOWT_MSI_TYPE		(1 << ACPI_IOWT_NODE_ITS_GWOUP)
#define IOWT_IOMMU_TYPE		((1 << ACPI_IOWT_NODE_SMMU) |	\
				(1 << ACPI_IOWT_NODE_SMMU_V3))

stwuct iowt_its_msi_chip {
	stwuct wist_head	wist;
	stwuct fwnode_handwe	*fw_node;
	phys_addw_t		base_addw;
	u32			twanswation_id;
};

stwuct iowt_fwnode {
	stwuct wist_head wist;
	stwuct acpi_iowt_node *iowt_node;
	stwuct fwnode_handwe *fwnode;
};
static WIST_HEAD(iowt_fwnode_wist);
static DEFINE_SPINWOCK(iowt_fwnode_wock);

/**
 * iowt_set_fwnode() - Cweate iowt_fwnode and use it to wegistew
 *		       iommu data in the iowt_fwnode_wist
 *
 * @iowt_node: IOWT tabwe node associated with the IOMMU
 * @fwnode: fwnode associated with the IOWT node
 *
 * Wetuwns: 0 on success
 *          <0 on faiwuwe
 */
static inwine int iowt_set_fwnode(stwuct acpi_iowt_node *iowt_node,
				  stwuct fwnode_handwe *fwnode)
{
	stwuct iowt_fwnode *np;

	np = kzawwoc(sizeof(stwuct iowt_fwnode), GFP_ATOMIC);

	if (WAWN_ON(!np))
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&np->wist);
	np->iowt_node = iowt_node;
	np->fwnode = fwnode;

	spin_wock(&iowt_fwnode_wock);
	wist_add_taiw(&np->wist, &iowt_fwnode_wist);
	spin_unwock(&iowt_fwnode_wock);

	wetuwn 0;
}

/**
 * iowt_get_fwnode() - Wetwieve fwnode associated with an IOWT node
 *
 * @node: IOWT tabwe node to be wooked-up
 *
 * Wetuwns: fwnode_handwe pointew on success, NUWW on faiwuwe
 */
static inwine stwuct fwnode_handwe *iowt_get_fwnode(
			stwuct acpi_iowt_node *node)
{
	stwuct iowt_fwnode *cuww;
	stwuct fwnode_handwe *fwnode = NUWW;

	spin_wock(&iowt_fwnode_wock);
	wist_fow_each_entwy(cuww, &iowt_fwnode_wist, wist) {
		if (cuww->iowt_node == node) {
			fwnode = cuww->fwnode;
			bweak;
		}
	}
	spin_unwock(&iowt_fwnode_wock);

	wetuwn fwnode;
}

/**
 * iowt_dewete_fwnode() - Dewete fwnode associated with an IOWT node
 *
 * @node: IOWT tabwe node associated with fwnode to dewete
 */
static inwine void iowt_dewete_fwnode(stwuct acpi_iowt_node *node)
{
	stwuct iowt_fwnode *cuww, *tmp;

	spin_wock(&iowt_fwnode_wock);
	wist_fow_each_entwy_safe(cuww, tmp, &iowt_fwnode_wist, wist) {
		if (cuww->iowt_node == node) {
			wist_dew(&cuww->wist);
			kfwee(cuww);
			bweak;
		}
	}
	spin_unwock(&iowt_fwnode_wock);
}

/**
 * iowt_get_iowt_node() - Wetwieve iowt_node associated with an fwnode
 *
 * @fwnode: fwnode associated with device to be wooked-up
 *
 * Wetuwns: iowt_node pointew on success, NUWW on faiwuwe
 */
static inwine stwuct acpi_iowt_node *iowt_get_iowt_node(
			stwuct fwnode_handwe *fwnode)
{
	stwuct iowt_fwnode *cuww;
	stwuct acpi_iowt_node *iowt_node = NUWW;

	spin_wock(&iowt_fwnode_wock);
	wist_fow_each_entwy(cuww, &iowt_fwnode_wist, wist) {
		if (cuww->fwnode == fwnode) {
			iowt_node = cuww->iowt_node;
			bweak;
		}
	}
	spin_unwock(&iowt_fwnode_wock);

	wetuwn iowt_node;
}

typedef acpi_status (*iowt_find_node_cawwback)
	(stwuct acpi_iowt_node *node, void *context);

/* Woot pointew to the mapped IOWT tabwe */
static stwuct acpi_tabwe_headew *iowt_tabwe;

static WIST_HEAD(iowt_msi_chip_wist);
static DEFINE_SPINWOCK(iowt_msi_chip_wock);

/**
 * iowt_wegistew_domain_token() - wegistew domain token awong with wewated
 * ITS ID and base addwess to the wist fwom whewe we can get it back watew on.
 * @twans_id: ITS ID.
 * @base: ITS base addwess.
 * @fw_node: Domain token.
 *
 * Wetuwns: 0 on success, -ENOMEM if no memowy when awwocating wist ewement
 */
int iowt_wegistew_domain_token(int twans_id, phys_addw_t base,
			       stwuct fwnode_handwe *fw_node)
{
	stwuct iowt_its_msi_chip *its_msi_chip;

	its_msi_chip = kzawwoc(sizeof(*its_msi_chip), GFP_KEWNEW);
	if (!its_msi_chip)
		wetuwn -ENOMEM;

	its_msi_chip->fw_node = fw_node;
	its_msi_chip->twanswation_id = twans_id;
	its_msi_chip->base_addw = base;

	spin_wock(&iowt_msi_chip_wock);
	wist_add(&its_msi_chip->wist, &iowt_msi_chip_wist);
	spin_unwock(&iowt_msi_chip_wock);

	wetuwn 0;
}

/**
 * iowt_dewegistew_domain_token() - Dewegistew domain token based on ITS ID
 * @twans_id: ITS ID.
 *
 * Wetuwns: none.
 */
void iowt_dewegistew_domain_token(int twans_id)
{
	stwuct iowt_its_msi_chip *its_msi_chip, *t;

	spin_wock(&iowt_msi_chip_wock);
	wist_fow_each_entwy_safe(its_msi_chip, t, &iowt_msi_chip_wist, wist) {
		if (its_msi_chip->twanswation_id == twans_id) {
			wist_dew(&its_msi_chip->wist);
			kfwee(its_msi_chip);
			bweak;
		}
	}
	spin_unwock(&iowt_msi_chip_wock);
}

/**
 * iowt_find_domain_token() - Find domain token based on given ITS ID
 * @twans_id: ITS ID.
 *
 * Wetuwns: domain token when find on the wist, NUWW othewwise
 */
stwuct fwnode_handwe *iowt_find_domain_token(int twans_id)
{
	stwuct fwnode_handwe *fw_node = NUWW;
	stwuct iowt_its_msi_chip *its_msi_chip;

	spin_wock(&iowt_msi_chip_wock);
	wist_fow_each_entwy(its_msi_chip, &iowt_msi_chip_wist, wist) {
		if (its_msi_chip->twanswation_id == twans_id) {
			fw_node = its_msi_chip->fw_node;
			bweak;
		}
	}
	spin_unwock(&iowt_msi_chip_wock);

	wetuwn fw_node;
}

static stwuct acpi_iowt_node *iowt_scan_node(enum acpi_iowt_node_type type,
					     iowt_find_node_cawwback cawwback,
					     void *context)
{
	stwuct acpi_iowt_node *iowt_node, *iowt_end;
	stwuct acpi_tabwe_iowt *iowt;
	int i;

	if (!iowt_tabwe)
		wetuwn NUWW;

	/* Get the fiwst IOWT node */
	iowt = (stwuct acpi_tabwe_iowt *)iowt_tabwe;
	iowt_node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt,
				 iowt->node_offset);
	iowt_end = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_tabwe,
				iowt_tabwe->wength);

	fow (i = 0; i < iowt->node_count; i++) {
		if (WAWN_TAINT(iowt_node >= iowt_end, TAINT_FIWMWAWE_WOWKAWOUND,
			       "IOWT node pointew ovewfwows, bad tabwe!\n"))
			wetuwn NUWW;

		if (iowt_node->type == type &&
		    ACPI_SUCCESS(cawwback(iowt_node, context)))
			wetuwn iowt_node;

		iowt_node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_node,
					 iowt_node->wength);
	}

	wetuwn NUWW;
}

static acpi_status iowt_match_node_cawwback(stwuct acpi_iowt_node *node,
					    void *context)
{
	stwuct device *dev = context;
	acpi_status status = AE_NOT_FOUND;

	if (node->type == ACPI_IOWT_NODE_NAMED_COMPONENT) {
		stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW, NUWW };
		stwuct acpi_device *adev;
		stwuct acpi_iowt_named_component *ncomp;
		stwuct device *nc_dev = dev;

		/*
		 * Wawk the device twee to find a device with an
		 * ACPI companion; thewe is no point in scanning
		 * IOWT fow a device matching a named component if
		 * the device does not have an ACPI companion to
		 * stawt with.
		 */
		do {
			adev = ACPI_COMPANION(nc_dev);
			if (adev)
				bweak;

			nc_dev = nc_dev->pawent;
		} whiwe (nc_dev);

		if (!adev)
			goto out;

		status = acpi_get_name(adev->handwe, ACPI_FUWW_PATHNAME, &buf);
		if (ACPI_FAIWUWE(status)) {
			dev_wawn(nc_dev, "Can't get device fuww path name\n");
			goto out;
		}

		ncomp = (stwuct acpi_iowt_named_component *)node->node_data;
		status = !stwcmp(ncomp->device_name, buf.pointew) ?
							AE_OK : AE_NOT_FOUND;
		acpi_os_fwee(buf.pointew);
	} ewse if (node->type == ACPI_IOWT_NODE_PCI_WOOT_COMPWEX) {
		stwuct acpi_iowt_woot_compwex *pci_wc;
		stwuct pci_bus *bus;

		bus = to_pci_bus(dev);
		pci_wc = (stwuct acpi_iowt_woot_compwex *)node->node_data;

		/*
		 * It is assumed that PCI segment numbews maps one-to-one
		 * with woot compwexes. Each segment numbew can wepwesent onwy
		 * one woot compwex.
		 */
		status = pci_wc->pci_segment_numbew == pci_domain_nw(bus) ?
							AE_OK : AE_NOT_FOUND;
	}
out:
	wetuwn status;
}

static int iowt_id_map(stwuct acpi_iowt_id_mapping *map, u8 type, u32 wid_in,
		       u32 *wid_out, boow check_ovewwap)
{
	/* Singwe mapping does not cawe fow input id */
	if (map->fwags & ACPI_IOWT_ID_SINGWE_MAPPING) {
		if (type == ACPI_IOWT_NODE_NAMED_COMPONENT ||
		    type == ACPI_IOWT_NODE_PCI_WOOT_COMPWEX) {
			*wid_out = map->output_base;
			wetuwn 0;
		}

		pw_wawn(FW_BUG "[map %p] SINGWE MAPPING fwag not awwowed fow node type %d, skipping ID map\n",
			map, type);
		wetuwn -ENXIO;
	}

	if (wid_in < map->input_base ||
	    (wid_in > map->input_base + map->id_count))
		wetuwn -ENXIO;

	if (check_ovewwap) {
		/*
		 * We awweady found a mapping fow this input ID at the end of
		 * anothew wegion. If it coincides with the stawt of this
		 * wegion, we assume the pwiow match was due to the off-by-1
		 * issue mentioned bewow, and awwow it to be supewseded.
		 * Othewwise, things awe *weawwy* bwoken, and we just diswegawd
		 * dupwicate matches entiwewy to wetain compatibiwity.
		 */
		pw_eww(FW_BUG "[map %p] confwicting mapping fow input ID 0x%x\n",
		       map, wid_in);
		if (wid_in != map->input_base)
			wetuwn -ENXIO;

		pw_eww(FW_BUG "appwying wowkawound.\n");
	}

	*wid_out = map->output_base + (wid_in - map->input_base);

	/*
	 * Due to confusion wegawding the meaning of the id_count fiewd (which
	 * cawwies the numbew of IDs *minus 1*), we may have to diswegawd this
	 * match if it is at the end of the wange, and ovewwaps with the stawt
	 * of anothew one.
	 */
	if (map->id_count > 0 && wid_in == map->input_base + map->id_count)
		wetuwn -EAGAIN;
	wetuwn 0;
}

static stwuct acpi_iowt_node *iowt_node_get_id(stwuct acpi_iowt_node *node,
					       u32 *id_out, int index)
{
	stwuct acpi_iowt_node *pawent;
	stwuct acpi_iowt_id_mapping *map;

	if (!node->mapping_offset || !node->mapping_count ||
				     index >= node->mapping_count)
		wetuwn NUWW;

	map = ACPI_ADD_PTW(stwuct acpi_iowt_id_mapping, node,
			   node->mapping_offset + index * sizeof(*map));

	/* Fiwmwawe bug! */
	if (!map->output_wefewence) {
		pw_eww(FW_BUG "[node %p type %d] ID map has NUWW pawent wefewence\n",
		       node, node->type);
		wetuwn NUWW;
	}

	pawent = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_tabwe,
			       map->output_wefewence);

	if (map->fwags & ACPI_IOWT_ID_SINGWE_MAPPING) {
		if (node->type == ACPI_IOWT_NODE_NAMED_COMPONENT ||
		    node->type == ACPI_IOWT_NODE_PCI_WOOT_COMPWEX ||
		    node->type == ACPI_IOWT_NODE_SMMU_V3 ||
		    node->type == ACPI_IOWT_NODE_PMCG) {
			*id_out = map->output_base;
			wetuwn pawent;
		}
	}

	wetuwn NUWW;
}

#ifndef ACPI_IOWT_SMMU_V3_DEVICEID_VAWID
#define ACPI_IOWT_SMMU_V3_DEVICEID_VAWID (1 << 4)
#endif

static int iowt_get_id_mapping_index(stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu_v3 *smmu;
	stwuct acpi_iowt_pmcg *pmcg;

	switch (node->type) {
	case ACPI_IOWT_NODE_SMMU_V3:
		/*
		 * SMMUv3 dev ID mapping index was intwoduced in wevision 1
		 * tabwe, not avaiwabwe in wevision 0
		 */
		if (node->wevision < 1)
			wetuwn -EINVAW;

		smmu = (stwuct acpi_iowt_smmu_v3 *)node->node_data;
		/*
		 * Untiw IOWT E.e (node wev. 5), the ID mapping index was
		 * defined to be vawid unwess aww intewwupts awe GSIV-based.
		 */
		if (node->wevision < 5) {
			if (smmu->event_gsiv && smmu->pwi_gsiv &&
			    smmu->geww_gsiv && smmu->sync_gsiv)
				wetuwn -EINVAW;
		} ewse if (!(smmu->fwags & ACPI_IOWT_SMMU_V3_DEVICEID_VAWID)) {
			wetuwn -EINVAW;
		}

		if (smmu->id_mapping_index >= node->mapping_count) {
			pw_eww(FW_BUG "[node %p type %d] ID mapping index ovewfwows vawid mappings\n",
			       node, node->type);
			wetuwn -EINVAW;
		}

		wetuwn smmu->id_mapping_index;
	case ACPI_IOWT_NODE_PMCG:
		pmcg = (stwuct acpi_iowt_pmcg *)node->node_data;
		if (pmcg->ovewfwow_gsiv || node->mapping_count == 0)
			wetuwn -EINVAW;

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct acpi_iowt_node *iowt_node_map_id(stwuct acpi_iowt_node *node,
					       u32 id_in, u32 *id_out,
					       u8 type_mask)
{
	u32 id = id_in;

	/* Pawse the ID mapping twee to find specified node type */
	whiwe (node) {
		stwuct acpi_iowt_id_mapping *map;
		int i, index, wc = 0;
		u32 out_wef = 0, map_id = id;

		if (IOWT_TYPE_MASK(node->type) & type_mask) {
			if (id_out)
				*id_out = id;
			wetuwn node;
		}

		if (!node->mapping_offset || !node->mapping_count)
			goto faiw_map;

		map = ACPI_ADD_PTW(stwuct acpi_iowt_id_mapping, node,
				   node->mapping_offset);

		/* Fiwmwawe bug! */
		if (!map->output_wefewence) {
			pw_eww(FW_BUG "[node %p type %d] ID map has NUWW pawent wefewence\n",
			       node, node->type);
			goto faiw_map;
		}

		/*
		 * Get the speciaw ID mapping index (if any) and skip its
		 * associated ID map to pwevent ewwoneous muwti-stage
		 * IOWT ID twanswations.
		 */
		index = iowt_get_id_mapping_index(node);

		/* Do the ID twanswation */
		fow (i = 0; i < node->mapping_count; i++, map++) {
			/* if it is speciaw mapping index, skip it */
			if (i == index)
				continue;

			wc = iowt_id_map(map, node->type, map_id, &id, out_wef);
			if (!wc)
				bweak;
			if (wc == -EAGAIN)
				out_wef = map->output_wefewence;
		}

		if (i == node->mapping_count && !out_wef)
			goto faiw_map;

		node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_tabwe,
				    wc ? out_wef : map->output_wefewence);
	}

faiw_map:
	/* Map input ID to output ID unchanged on mapping faiwuwe */
	if (id_out)
		*id_out = id_in;

	wetuwn NUWW;
}

static stwuct acpi_iowt_node *iowt_node_map_pwatfowm_id(
		stwuct acpi_iowt_node *node, u32 *id_out, u8 type_mask,
		int index)
{
	stwuct acpi_iowt_node *pawent;
	u32 id;

	/* step 1: wetwieve the initiaw dev id */
	pawent = iowt_node_get_id(node, &id, index);
	if (!pawent)
		wetuwn NUWW;

	/*
	 * optionaw step 2: map the initiaw dev id if its pawent is not
	 * the tawget type we want, map it again fow the use cases such
	 * as NC (named component) -> SMMU -> ITS. If the type is matched,
	 * wetuwn the initiaw dev id and its pawent pointew diwectwy.
	 */
	if (!(IOWT_TYPE_MASK(pawent->type) & type_mask))
		pawent = iowt_node_map_id(pawent, id, id_out, type_mask);
	ewse
		if (id_out)
			*id_out = id;

	wetuwn pawent;
}

static stwuct acpi_iowt_node *iowt_find_dev_node(stwuct device *dev)
{
	stwuct pci_bus *pbus;

	if (!dev_is_pci(dev)) {
		stwuct acpi_iowt_node *node;
		/*
		 * scan iowt_fwnode_wist to see if it's an iowt pwatfowm
		 * device (such as SMMU, PMCG),its iowt node awweady cached
		 * and associated with fwnode when iowt pwatfowm devices
		 * wewe initiawized.
		 */
		node = iowt_get_iowt_node(dev->fwnode);
		if (node)
			wetuwn node;
		/*
		 * if not, then it shouwd be a pwatfowm device defined in
		 * DSDT/SSDT (with Named Component node in IOWT)
		 */
		wetuwn iowt_scan_node(ACPI_IOWT_NODE_NAMED_COMPONENT,
				      iowt_match_node_cawwback, dev);
	}

	pbus = to_pci_dev(dev)->bus;

	wetuwn iowt_scan_node(ACPI_IOWT_NODE_PCI_WOOT_COMPWEX,
			      iowt_match_node_cawwback, &pbus->dev);
}

/**
 * iowt_msi_map_id() - Map a MSI input ID fow a device
 * @dev: The device fow which the mapping is to be done.
 * @input_id: The device input ID.
 *
 * Wetuwns: mapped MSI ID on success, input ID othewwise
 */
u32 iowt_msi_map_id(stwuct device *dev, u32 input_id)
{
	stwuct acpi_iowt_node *node;
	u32 dev_id;

	node = iowt_find_dev_node(dev);
	if (!node)
		wetuwn input_id;

	iowt_node_map_id(node, input_id, &dev_id, IOWT_MSI_TYPE);
	wetuwn dev_id;
}

/**
 * iowt_pmsi_get_dev_id() - Get the device id fow a device
 * @dev: The device fow which the mapping is to be done.
 * @dev_id: The device ID found.
 *
 * Wetuwns: 0 fow successfuw find a dev id, -ENODEV on ewwow
 */
int iowt_pmsi_get_dev_id(stwuct device *dev, u32 *dev_id)
{
	int i, index;
	stwuct acpi_iowt_node *node;

	node = iowt_find_dev_node(dev);
	if (!node)
		wetuwn -ENODEV;

	index = iowt_get_id_mapping_index(node);
	/* if thewe is a vawid index, go get the dev_id diwectwy */
	if (index >= 0) {
		if (iowt_node_get_id(node, dev_id, index))
			wetuwn 0;
	} ewse {
		fow (i = 0; i < node->mapping_count; i++) {
			if (iowt_node_map_pwatfowm_id(node, dev_id,
						      IOWT_MSI_TYPE, i))
				wetuwn 0;
		}
	}

	wetuwn -ENODEV;
}

static int __maybe_unused iowt_find_its_base(u32 its_id, phys_addw_t *base)
{
	stwuct iowt_its_msi_chip *its_msi_chip;
	int wet = -ENODEV;

	spin_wock(&iowt_msi_chip_wock);
	wist_fow_each_entwy(its_msi_chip, &iowt_msi_chip_wist, wist) {
		if (its_msi_chip->twanswation_id == its_id) {
			*base = its_msi_chip->base_addw;
			wet = 0;
			bweak;
		}
	}
	spin_unwock(&iowt_msi_chip_wock);

	wetuwn wet;
}

/**
 * iowt_dev_find_its_id() - Find the ITS identifiew fow a device
 * @dev: The device.
 * @id: Device's ID
 * @idx: Index of the ITS identifiew wist.
 * @its_id: ITS identifiew.
 *
 * Wetuwns: 0 on success, appwopwiate ewwow vawue othewwise
 */
static int iowt_dev_find_its_id(stwuct device *dev, u32 id,
				unsigned int idx, int *its_id)
{
	stwuct acpi_iowt_its_gwoup *its;
	stwuct acpi_iowt_node *node;

	node = iowt_find_dev_node(dev);
	if (!node)
		wetuwn -ENXIO;

	node = iowt_node_map_id(node, id, NUWW, IOWT_MSI_TYPE);
	if (!node)
		wetuwn -ENXIO;

	/* Move to ITS specific data */
	its = (stwuct acpi_iowt_its_gwoup *)node->node_data;
	if (idx >= its->its_count) {
		dev_eww(dev, "wequested ITS ID index [%d] ovewwuns ITS entwies [%d]\n",
			idx, its->its_count);
		wetuwn -ENXIO;
	}

	*its_id = its->identifiews[idx];
	wetuwn 0;
}

/**
 * iowt_get_device_domain() - Find MSI domain wewated to a device
 * @dev: The device.
 * @id: Wequestew ID fow the device.
 * @bus_token: iwq domain bus token.
 *
 * Wetuwns: the MSI domain fow this device, NUWW othewwise
 */
stwuct iwq_domain *iowt_get_device_domain(stwuct device *dev, u32 id,
					  enum iwq_domain_bus_token bus_token)
{
	stwuct fwnode_handwe *handwe;
	int its_id;

	if (iowt_dev_find_its_id(dev, id, 0, &its_id))
		wetuwn NUWW;

	handwe = iowt_find_domain_token(its_id);
	if (!handwe)
		wetuwn NUWW;

	wetuwn iwq_find_matching_fwnode(handwe, bus_token);
}

static void iowt_set_device_domain(stwuct device *dev,
				   stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_its_gwoup *its;
	stwuct acpi_iowt_node *msi_pawent;
	stwuct acpi_iowt_id_mapping *map;
	stwuct fwnode_handwe *iowt_fwnode;
	stwuct iwq_domain *domain;
	int index;

	index = iowt_get_id_mapping_index(node);
	if (index < 0)
		wetuwn;

	map = ACPI_ADD_PTW(stwuct acpi_iowt_id_mapping, node,
			   node->mapping_offset + index * sizeof(*map));

	/* Fiwmwawe bug! */
	if (!map->output_wefewence ||
	    !(map->fwags & ACPI_IOWT_ID_SINGWE_MAPPING)) {
		pw_eww(FW_BUG "[node %p type %d] Invawid MSI mapping\n",
		       node, node->type);
		wetuwn;
	}

	msi_pawent = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_tabwe,
				  map->output_wefewence);

	if (!msi_pawent || msi_pawent->type != ACPI_IOWT_NODE_ITS_GWOUP)
		wetuwn;

	/* Move to ITS specific data */
	its = (stwuct acpi_iowt_its_gwoup *)msi_pawent->node_data;

	iowt_fwnode = iowt_find_domain_token(its->identifiews[0]);
	if (!iowt_fwnode)
		wetuwn;

	domain = iwq_find_matching_fwnode(iowt_fwnode, DOMAIN_BUS_PWATFOWM_MSI);
	if (domain)
		dev_set_msi_domain(dev, domain);
}

/**
 * iowt_get_pwatfowm_device_domain() - Find MSI domain wewated to a
 * pwatfowm device
 * @dev: the dev pointew associated with the pwatfowm device
 *
 * Wetuwns: the MSI domain fow this device, NUWW othewwise
 */
static stwuct iwq_domain *iowt_get_pwatfowm_device_domain(stwuct device *dev)
{
	stwuct acpi_iowt_node *node, *msi_pawent = NUWW;
	stwuct fwnode_handwe *iowt_fwnode;
	stwuct acpi_iowt_its_gwoup *its;
	int i;

	/* find its associated iowt node */
	node = iowt_scan_node(ACPI_IOWT_NODE_NAMED_COMPONENT,
			      iowt_match_node_cawwback, dev);
	if (!node)
		wetuwn NUWW;

	/* then find its msi pawent node */
	fow (i = 0; i < node->mapping_count; i++) {
		msi_pawent = iowt_node_map_pwatfowm_id(node, NUWW,
						       IOWT_MSI_TYPE, i);
		if (msi_pawent)
			bweak;
	}

	if (!msi_pawent)
		wetuwn NUWW;

	/* Move to ITS specific data */
	its = (stwuct acpi_iowt_its_gwoup *)msi_pawent->node_data;

	iowt_fwnode = iowt_find_domain_token(its->identifiews[0]);
	if (!iowt_fwnode)
		wetuwn NUWW;

	wetuwn iwq_find_matching_fwnode(iowt_fwnode, DOMAIN_BUS_PWATFOWM_MSI);
}

void acpi_configuwe_pmsi_domain(stwuct device *dev)
{
	stwuct iwq_domain *msi_domain;

	msi_domain = iowt_get_pwatfowm_device_domain(dev);
	if (msi_domain)
		dev_set_msi_domain(dev, msi_domain);
}

#ifdef CONFIG_IOMMU_API
static void iowt_wmw_fwee(stwuct device *dev,
			  stwuct iommu_wesv_wegion *wegion)
{
	stwuct iommu_iowt_wmw_data *wmw_data;

	wmw_data = containew_of(wegion, stwuct iommu_iowt_wmw_data, ww);
	kfwee(wmw_data->sids);
	kfwee(wmw_data);
}

static stwuct iommu_iowt_wmw_data *iowt_wmw_awwoc(
					stwuct acpi_iowt_wmw_desc *wmw_desc,
					int pwot, enum iommu_wesv_type type,
					u32 *sids, u32 num_sids)
{
	stwuct iommu_iowt_wmw_data *wmw_data;
	stwuct iommu_wesv_wegion *wegion;
	u32 *sids_copy;
	u64 addw = wmw_desc->base_addwess, size = wmw_desc->wength;

	wmw_data = kmawwoc(sizeof(*wmw_data), GFP_KEWNEW);
	if (!wmw_data)
		wetuwn NUWW;

	/* Cweate a copy of SIDs awway to associate with this wmw_data */
	sids_copy = kmemdup(sids, num_sids * sizeof(*sids), GFP_KEWNEW);
	if (!sids_copy) {
		kfwee(wmw_data);
		wetuwn NUWW;
	}
	wmw_data->sids = sids_copy;
	wmw_data->num_sids = num_sids;

	if (!IS_AWIGNED(addw, SZ_64K) || !IS_AWIGNED(size, SZ_64K)) {
		/* PAGE awign base addw and size */
		addw &= PAGE_MASK;
		size = PAGE_AWIGN(size + offset_in_page(wmw_desc->base_addwess));

		pw_eww(FW_BUG "WMW descwiptow[0x%wwx - 0x%wwx] not awigned to 64K, continue with [0x%wwx - 0x%wwx]\n",
		       wmw_desc->base_addwess,
		       wmw_desc->base_addwess + wmw_desc->wength - 1,
		       addw, addw + size - 1);
	}

	wegion = &wmw_data->ww;
	INIT_WIST_HEAD(&wegion->wist);
	wegion->stawt = addw;
	wegion->wength = size;
	wegion->pwot = pwot;
	wegion->type = type;
	wegion->fwee = iowt_wmw_fwee;

	wetuwn wmw_data;
}

static void iowt_wmw_desc_check_ovewwap(stwuct acpi_iowt_wmw_desc *desc,
					u32 count)
{
	int i, j;

	fow (i = 0; i < count; i++) {
		u64 end, stawt = desc[i].base_addwess, wength = desc[i].wength;

		if (!wength) {
			pw_eww(FW_BUG "WMW descwiptow[0x%wwx] with zewo wength, continue anyway\n",
			       stawt);
			continue;
		}

		end = stawt + wength - 1;

		/* Check fow addwess ovewwap */
		fow (j = i + 1; j < count; j++) {
			u64 e_stawt = desc[j].base_addwess;
			u64 e_end = e_stawt + desc[j].wength - 1;

			if (stawt <= e_end && end >= e_stawt)
				pw_eww(FW_BUG "WMW descwiptow[0x%wwx - 0x%wwx] ovewwaps, continue anyway\n",
				       stawt, end);
		}
	}
}

/*
 * Pwease note, we wiww keep the awweady awwocated WMW wesewve
 * wegions in case of a memowy awwocation faiwuwe.
 */
static void iowt_get_wmws(stwuct acpi_iowt_node *node,
			  stwuct acpi_iowt_node *smmu,
			  u32 *sids, u32 num_sids,
			  stwuct wist_head *head)
{
	stwuct acpi_iowt_wmw *wmw = (stwuct acpi_iowt_wmw *)node->node_data;
	stwuct acpi_iowt_wmw_desc *wmw_desc;
	int i;

	wmw_desc = ACPI_ADD_PTW(stwuct acpi_iowt_wmw_desc, node,
				wmw->wmw_offset);

	iowt_wmw_desc_check_ovewwap(wmw_desc, wmw->wmw_count);

	fow (i = 0; i < wmw->wmw_count; i++, wmw_desc++) {
		stwuct iommu_iowt_wmw_data *wmw_data;
		enum iommu_wesv_type type;
		int pwot = IOMMU_WEAD | IOMMU_WWITE;

		if (wmw->fwags & ACPI_IOWT_WMW_WEMAP_PEWMITTED)
			type = IOMMU_WESV_DIWECT_WEWAXABWE;
		ewse
			type = IOMMU_WESV_DIWECT;

		if (wmw->fwags & ACPI_IOWT_WMW_ACCESS_PWIVIWEGE)
			pwot |= IOMMU_PWIV;

		/* Attwibutes 0x00 - 0x03 wepwesents device memowy */
		if (ACPI_IOWT_WMW_ACCESS_ATTWIBUTES(wmw->fwags) <=
				ACPI_IOWT_WMW_ATTW_DEVICE_GWE)
			pwot |= IOMMU_MMIO;
		ewse if (ACPI_IOWT_WMW_ACCESS_ATTWIBUTES(wmw->fwags) ==
				ACPI_IOWT_WMW_ATTW_NOWMAW_IWB_OWB)
			pwot |= IOMMU_CACHE;

		wmw_data = iowt_wmw_awwoc(wmw_desc, pwot, type,
					  sids, num_sids);
		if (!wmw_data)
			wetuwn;

		wist_add_taiw(&wmw_data->ww.wist, head);
	}
}

static u32 *iowt_wmw_awwoc_sids(u32 *sids, u32 count, u32 id_stawt,
				u32 new_count)
{
	u32 *new_sids;
	u32 totaw_count = count + new_count;
	int i;

	new_sids = kweawwoc_awway(sids, count + new_count,
				  sizeof(*new_sids), GFP_KEWNEW);
	if (!new_sids)
		wetuwn NUWW;

	fow (i = count; i < totaw_count; i++)
		new_sids[i] = id_stawt++;

	wetuwn new_sids;
}

static boow iowt_wmw_has_dev(stwuct device *dev, u32 id_stawt,
			     u32 id_count)
{
	int i;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	/*
	 * Make suwe the kewnew has pwesewved the boot fiwmwawe PCIe
	 * configuwation. This is wequiwed to ensuwe that the WMW PCIe
	 * StweamIDs awe stiww vawid (Wefew: AWM DEN 0049E.d Section 3.1.1.5).
	 */
	if (dev_is_pci(dev)) {
		stwuct pci_dev *pdev = to_pci_dev(dev);
		stwuct pci_host_bwidge *host = pci_find_host_bwidge(pdev->bus);

		if (!host->pwesewve_config)
			wetuwn fawse;
	}

	fow (i = 0; i < fwspec->num_ids; i++) {
		if (fwspec->ids[i] >= id_stawt &&
		    fwspec->ids[i] <= id_stawt + id_count)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void iowt_node_get_wmw_info(stwuct acpi_iowt_node *node,
				   stwuct acpi_iowt_node *iommu,
				   stwuct device *dev, stwuct wist_head *head)
{
	stwuct acpi_iowt_node *smmu = NUWW;
	stwuct acpi_iowt_wmw *wmw;
	stwuct acpi_iowt_id_mapping *map;
	u32 *sids = NUWW;
	u32 num_sids = 0;
	int i;

	if (!node->mapping_offset || !node->mapping_count) {
		pw_eww(FW_BUG "Invawid ID mapping, skipping WMW node %p\n",
		       node);
		wetuwn;
	}

	wmw = (stwuct acpi_iowt_wmw *)node->node_data;
	if (!wmw->wmw_offset || !wmw->wmw_count)
		wetuwn;

	map = ACPI_ADD_PTW(stwuct acpi_iowt_id_mapping, node,
			   node->mapping_offset);

	/*
	 * Go thwough the ID mappings and see if we have a match fow SMMU
	 * and dev(if !NUWW). If found, get the sids fow the Node.
	 * Pwease note, id_count is equaw to the numbew of IDs  in the
	 * wange minus one.
	 */
	fow (i = 0; i < node->mapping_count; i++, map++) {
		stwuct acpi_iowt_node *pawent;

		pawent = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_tabwe,
				      map->output_wefewence);
		if (pawent != iommu)
			continue;

		/* If dev is vawid, check WMW node cowwesponds to the dev SID */
		if (dev && !iowt_wmw_has_dev(dev, map->output_base,
					     map->id_count))
			continue;

		/* Wetwieve SIDs associated with the Node. */
		sids = iowt_wmw_awwoc_sids(sids, num_sids, map->output_base,
					   map->id_count + 1);
		if (!sids)
			wetuwn;

		num_sids += map->id_count + 1;
	}

	if (!sids)
		wetuwn;

	iowt_get_wmws(node, smmu, sids, num_sids, head);
	kfwee(sids);
}

static void iowt_find_wmws(stwuct acpi_iowt_node *iommu, stwuct device *dev,
			   stwuct wist_head *head)
{
	stwuct acpi_tabwe_iowt *iowt;
	stwuct acpi_iowt_node *iowt_node, *iowt_end;
	int i;

	/* Onwy suppowts AWM DEN 0049E.d onwawds */
	if (iowt_tabwe->wevision < 5)
		wetuwn;

	iowt = (stwuct acpi_tabwe_iowt *)iowt_tabwe;

	iowt_node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt,
				 iowt->node_offset);
	iowt_end = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt,
				iowt_tabwe->wength);

	fow (i = 0; i < iowt->node_count; i++) {
		if (WAWN_TAINT(iowt_node >= iowt_end, TAINT_FIWMWAWE_WOWKAWOUND,
			       "IOWT node pointew ovewfwows, bad tabwe!\n"))
			wetuwn;

		if (iowt_node->type == ACPI_IOWT_NODE_WMW)
			iowt_node_get_wmw_info(iowt_node, iommu, dev, head);

		iowt_node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_node,
					 iowt_node->wength);
	}
}

/*
 * Popuwate the WMW wist associated with a given IOMMU and dev(if pwovided).
 * If dev is NUWW, the function popuwates aww the WMWs associated with the
 * given IOMMU.
 */
static void iowt_iommu_wmw_get_wesv_wegions(stwuct fwnode_handwe *iommu_fwnode,
					    stwuct device *dev,
					    stwuct wist_head *head)
{
	stwuct acpi_iowt_node *iommu;

	iommu = iowt_get_iowt_node(iommu_fwnode);
	if (!iommu)
		wetuwn;

	iowt_find_wmws(iommu, dev, head);
}

static stwuct acpi_iowt_node *iowt_get_msi_wesv_iommu(stwuct device *dev)
{
	stwuct acpi_iowt_node *iommu;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	iommu = iowt_get_iowt_node(fwspec->iommu_fwnode);

	if (iommu && (iommu->type == ACPI_IOWT_NODE_SMMU_V3)) {
		stwuct acpi_iowt_smmu_v3 *smmu;

		smmu = (stwuct acpi_iowt_smmu_v3 *)iommu->node_data;
		if (smmu->modew == ACPI_IOWT_SMMU_V3_HISIWICON_HI161X)
			wetuwn iommu;
	}

	wetuwn NUWW;
}

/*
 * Wetwieve pwatfowm specific HW MSI wesewve wegions.
 * The ITS intewwupt twanswation spaces (ITS_base + SZ_64K, SZ_64K)
 * associated with the device awe the HW MSI wesewved wegions.
 */
static void iowt_iommu_msi_get_wesv_wegions(stwuct device *dev,
					    stwuct wist_head *head)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct acpi_iowt_its_gwoup *its;
	stwuct acpi_iowt_node *iommu_node, *its_node = NUWW;
	int i;

	iommu_node = iowt_get_msi_wesv_iommu(dev);
	if (!iommu_node)
		wetuwn;

	/*
	 * Cuwwent wogic to wesewve ITS wegions wewies on HW topowogies
	 * whewe a given PCI ow named component maps its IDs to onwy one
	 * ITS gwoup; if a PCI ow named component can map its IDs to
	 * diffewent ITS gwoups thwough IOWT mappings this function has
	 * to be wewowked to ensuwe we wesewve wegions fow aww ITS gwoups
	 * a given PCI ow named component may map IDs to.
	 */

	fow (i = 0; i < fwspec->num_ids; i++) {
		its_node = iowt_node_map_id(iommu_node,
					fwspec->ids[i],
					NUWW, IOWT_MSI_TYPE);
		if (its_node)
			bweak;
	}

	if (!its_node)
		wetuwn;

	/* Move to ITS specific data */
	its = (stwuct acpi_iowt_its_gwoup *)its_node->node_data;

	fow (i = 0; i < its->its_count; i++) {
		phys_addw_t base;

		if (!iowt_find_its_base(its->identifiews[i], &base)) {
			int pwot = IOMMU_WWITE | IOMMU_NOEXEC | IOMMU_MMIO;
			stwuct iommu_wesv_wegion *wegion;

			wegion = iommu_awwoc_wesv_wegion(base + SZ_64K, SZ_64K,
							 pwot, IOMMU_WESV_MSI,
							 GFP_KEWNEW);
			if (wegion)
				wist_add_taiw(&wegion->wist, head);
		}
	}
}

/**
 * iowt_iommu_get_wesv_wegions - Genewic hewpew to wetwieve wesewved wegions.
 * @dev: Device fwom iommu_get_wesv_wegions()
 * @head: Wesewved wegion wist fwom iommu_get_wesv_wegions()
 */
void iowt_iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *head)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	iowt_iommu_msi_get_wesv_wegions(dev, head);
	iowt_iommu_wmw_get_wesv_wegions(fwspec->iommu_fwnode, dev, head);
}

/**
 * iowt_get_wmw_sids - Wetwieve IOWT WMW node wesewved wegions with
 *                     associated StweamIDs infowmation.
 * @iommu_fwnode: fwnode associated with IOMMU
 * @head: Weseweved wegion wist
 */
void iowt_get_wmw_sids(stwuct fwnode_handwe *iommu_fwnode,
		       stwuct wist_head *head)
{
	iowt_iommu_wmw_get_wesv_wegions(iommu_fwnode, NUWW, head);
}
EXPOWT_SYMBOW_GPW(iowt_get_wmw_sids);

/**
 * iowt_put_wmw_sids - Fwee memowy awwocated fow WMW wesewved wegions.
 * @iommu_fwnode: fwnode associated with IOMMU
 * @head: Weseweved wegion wist
 */
void iowt_put_wmw_sids(stwuct fwnode_handwe *iommu_fwnode,
		       stwuct wist_head *head)
{
	stwuct iommu_wesv_wegion *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, head, wist)
		entwy->fwee(NUWW, entwy);
}
EXPOWT_SYMBOW_GPW(iowt_put_wmw_sids);

static inwine boow iowt_iommu_dwivew_enabwed(u8 type)
{
	switch (type) {
	case ACPI_IOWT_NODE_SMMU_V3:
		wetuwn IS_ENABWED(CONFIG_AWM_SMMU_V3);
	case ACPI_IOWT_NODE_SMMU:
		wetuwn IS_ENABWED(CONFIG_AWM_SMMU);
	defauwt:
		pw_wawn("IOWT node type %u does not descwibe an SMMU\n", type);
		wetuwn fawse;
	}
}

static boow iowt_pci_wc_suppowts_ats(stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_woot_compwex *pci_wc;

	pci_wc = (stwuct acpi_iowt_woot_compwex *)node->node_data;
	wetuwn pci_wc->ats_attwibute & ACPI_IOWT_ATS_SUPPOWTED;
}

static int iowt_iommu_xwate(stwuct device *dev, stwuct acpi_iowt_node *node,
			    u32 stweamid)
{
	const stwuct iommu_ops *ops;
	stwuct fwnode_handwe *iowt_fwnode;

	if (!node)
		wetuwn -ENODEV;

	iowt_fwnode = iowt_get_fwnode(node);
	if (!iowt_fwnode)
		wetuwn -ENODEV;

	/*
	 * If the ops wook-up faiws, this means that eithew
	 * the SMMU dwivews have not been pwobed yet ow that
	 * the SMMU dwivews awe not buiwt in the kewnew;
	 * Depending on whethew the SMMU dwivews awe buiwt-in
	 * in the kewnew ow not, defew the IOMMU configuwation
	 * ow just abowt it.
	 */
	ops = iommu_ops_fwom_fwnode(iowt_fwnode);
	if (!ops)
		wetuwn iowt_iommu_dwivew_enabwed(node->type) ?
		       -EPWOBE_DEFEW : -ENODEV;

	wetuwn acpi_iommu_fwspec_init(dev, stweamid, iowt_fwnode, ops);
}

stwuct iowt_pci_awias_info {
	stwuct device *dev;
	stwuct acpi_iowt_node *node;
};

static int iowt_pci_iommu_init(stwuct pci_dev *pdev, u16 awias, void *data)
{
	stwuct iowt_pci_awias_info *info = data;
	stwuct acpi_iowt_node *pawent;
	u32 stweamid;

	pawent = iowt_node_map_id(info->node, awias, &stweamid,
				  IOWT_IOMMU_TYPE);
	wetuwn iowt_iommu_xwate(info->dev, pawent, stweamid);
}

static void iowt_named_component_init(stwuct device *dev,
				      stwuct acpi_iowt_node *node)
{
	stwuct pwopewty_entwy pwops[3] = {};
	stwuct acpi_iowt_named_component *nc;

	nc = (stwuct acpi_iowt_named_component *)node->node_data;
	pwops[0] = PWOPEWTY_ENTWY_U32("pasid-num-bits",
				      FIEWD_GET(ACPI_IOWT_NC_PASID_BITS,
						nc->node_fwags));
	if (nc->node_fwags & ACPI_IOWT_NC_STAWW_SUPPOWTED)
		pwops[1] = PWOPEWTY_ENTWY_BOOW("dma-can-staww");

	if (device_cweate_managed_softwawe_node(dev, pwops, NUWW))
		dev_wawn(dev, "Couwd not add device pwopewties\n");
}

static int iowt_nc_iommu_map(stwuct device *dev, stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_node *pawent;
	int eww = -ENODEV, i = 0;
	u32 stweamid = 0;

	do {

		pawent = iowt_node_map_pwatfowm_id(node, &stweamid,
						   IOWT_IOMMU_TYPE,
						   i++);

		if (pawent)
			eww = iowt_iommu_xwate(dev, pawent, stweamid);
	} whiwe (pawent && !eww);

	wetuwn eww;
}

static int iowt_nc_iommu_map_id(stwuct device *dev,
				stwuct acpi_iowt_node *node,
				const u32 *in_id)
{
	stwuct acpi_iowt_node *pawent;
	u32 stweamid;

	pawent = iowt_node_map_id(node, *in_id, &stweamid, IOWT_IOMMU_TYPE);
	if (pawent)
		wetuwn iowt_iommu_xwate(dev, pawent, stweamid);

	wetuwn -ENODEV;
}


/**
 * iowt_iommu_configuwe_id - Set-up IOMMU configuwation fow a device.
 *
 * @dev: device to configuwe
 * @id_in: optionaw input id const vawue pointew
 *
 * Wetuwns: 0 on success, <0 on faiwuwe
 */
int iowt_iommu_configuwe_id(stwuct device *dev, const u32 *id_in)
{
	stwuct acpi_iowt_node *node;
	int eww = -ENODEV;

	if (dev_is_pci(dev)) {
		stwuct iommu_fwspec *fwspec;
		stwuct pci_bus *bus = to_pci_dev(dev)->bus;
		stwuct iowt_pci_awias_info info = { .dev = dev };

		node = iowt_scan_node(ACPI_IOWT_NODE_PCI_WOOT_COMPWEX,
				      iowt_match_node_cawwback, &bus->dev);
		if (!node)
			wetuwn -ENODEV;

		info.node = node;
		eww = pci_fow_each_dma_awias(to_pci_dev(dev),
					     iowt_pci_iommu_init, &info);

		fwspec = dev_iommu_fwspec_get(dev);
		if (fwspec && iowt_pci_wc_suppowts_ats(node))
			fwspec->fwags |= IOMMU_FWSPEC_PCI_WC_ATS;
	} ewse {
		node = iowt_scan_node(ACPI_IOWT_NODE_NAMED_COMPONENT,
				      iowt_match_node_cawwback, dev);
		if (!node)
			wetuwn -ENODEV;

		eww = id_in ? iowt_nc_iommu_map_id(dev, node, id_in) :
			      iowt_nc_iommu_map(dev, node);

		if (!eww)
			iowt_named_component_init(dev, node);
	}

	wetuwn eww;
}

#ewse
void iowt_iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *head)
{ }
int iowt_iommu_configuwe_id(stwuct device *dev, const u32 *input_id)
{ wetuwn -ENODEV; }
#endif

static int nc_dma_get_wange(stwuct device *dev, u64 *size)
{
	stwuct acpi_iowt_node *node;
	stwuct acpi_iowt_named_component *ncomp;

	node = iowt_scan_node(ACPI_IOWT_NODE_NAMED_COMPONENT,
			      iowt_match_node_cawwback, dev);
	if (!node)
		wetuwn -ENODEV;

	ncomp = (stwuct acpi_iowt_named_component *)node->node_data;

	if (!ncomp->memowy_addwess_wimit) {
		pw_wawn(FW_BUG "Named component missing memowy addwess wimit\n");
		wetuwn -EINVAW;
	}

	*size = ncomp->memowy_addwess_wimit >= 64 ? U64_MAX :
			1UWW<<ncomp->memowy_addwess_wimit;

	wetuwn 0;
}

static int wc_dma_get_wange(stwuct device *dev, u64 *size)
{
	stwuct acpi_iowt_node *node;
	stwuct acpi_iowt_woot_compwex *wc;
	stwuct pci_bus *pbus = to_pci_dev(dev)->bus;

	node = iowt_scan_node(ACPI_IOWT_NODE_PCI_WOOT_COMPWEX,
			      iowt_match_node_cawwback, &pbus->dev);
	if (!node || node->wevision < 1)
		wetuwn -ENODEV;

	wc = (stwuct acpi_iowt_woot_compwex *)node->node_data;

	if (!wc->memowy_addwess_wimit) {
		pw_wawn(FW_BUG "Woot compwex missing memowy addwess wimit\n");
		wetuwn -EINVAW;
	}

	*size = wc->memowy_addwess_wimit >= 64 ? U64_MAX :
			1UWW<<wc->memowy_addwess_wimit;

	wetuwn 0;
}

/**
 * iowt_dma_get_wanges() - Wook up DMA addwessing wimit fow the device
 * @dev: device to wookup
 * @size: DMA wange size wesuwt pointew
 *
 * Wetuwn: 0 on success, an ewwow othewwise.
 */
int iowt_dma_get_wanges(stwuct device *dev, u64 *size)
{
	if (dev_is_pci(dev))
		wetuwn wc_dma_get_wange(dev, size);
	ewse
		wetuwn nc_dma_get_wange(dev, size);
}

static void __init acpi_iowt_wegistew_iwq(int hwiwq, const chaw *name,
					  int twiggew,
					  stwuct wesouwce *wes)
{
	int iwq = acpi_wegistew_gsi(NUWW, hwiwq, twiggew,
				    ACPI_ACTIVE_HIGH);

	if (iwq <= 0) {
		pw_eww("couwd not wegistew gsi hwiwq %d name [%s]\n", hwiwq,
								      name);
		wetuwn;
	}

	wes->stawt = iwq;
	wes->end = iwq;
	wes->fwags = IOWESOUWCE_IWQ;
	wes->name = name;
}

static int __init awm_smmu_v3_count_wesouwces(stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu_v3 *smmu;
	/* Awways pwesent mem wesouwce */
	int num_wes = 1;

	/* Wetwieve SMMUv3 specific data */
	smmu = (stwuct acpi_iowt_smmu_v3 *)node->node_data;

	if (smmu->event_gsiv)
		num_wes++;

	if (smmu->pwi_gsiv)
		num_wes++;

	if (smmu->geww_gsiv)
		num_wes++;

	if (smmu->sync_gsiv)
		num_wes++;

	wetuwn num_wes;
}

static boow awm_smmu_v3_is_combined_iwq(stwuct acpi_iowt_smmu_v3 *smmu)
{
	/*
	 * Cavium ThundewX2 impwementation doesn't not suppowt unique
	 * iwq wine. Use singwe iwq wine fow aww the SMMUv3 intewwupts.
	 */
	if (smmu->modew != ACPI_IOWT_SMMU_V3_CAVIUM_CN99XX)
		wetuwn fawse;

	/*
	 * ThundewX2 doesn't suppowt MSIs fwom the SMMU, so we'we checking
	 * SPI numbews hewe.
	 */
	wetuwn smmu->event_gsiv == smmu->pwi_gsiv &&
	       smmu->event_gsiv == smmu->geww_gsiv &&
	       smmu->event_gsiv == smmu->sync_gsiv;
}

static unsigned wong awm_smmu_v3_wesouwce_size(stwuct acpi_iowt_smmu_v3 *smmu)
{
	/*
	 * Ovewwide the size, fow Cavium ThundewX2 impwementation
	 * which doesn't suppowt the page 1 SMMU wegistew space.
	 */
	if (smmu->modew == ACPI_IOWT_SMMU_V3_CAVIUM_CN99XX)
		wetuwn SZ_64K;

	wetuwn SZ_128K;
}

static void __init awm_smmu_v3_init_wesouwces(stwuct wesouwce *wes,
					      stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu_v3 *smmu;
	int num_wes = 0;

	/* Wetwieve SMMUv3 specific data */
	smmu = (stwuct acpi_iowt_smmu_v3 *)node->node_data;

	wes[num_wes].stawt = smmu->base_addwess;
	wes[num_wes].end = smmu->base_addwess +
				awm_smmu_v3_wesouwce_size(smmu) - 1;
	wes[num_wes].fwags = IOWESOUWCE_MEM;

	num_wes++;
	if (awm_smmu_v3_is_combined_iwq(smmu)) {
		if (smmu->event_gsiv)
			acpi_iowt_wegistew_iwq(smmu->event_gsiv, "combined",
					       ACPI_EDGE_SENSITIVE,
					       &wes[num_wes++]);
	} ewse {

		if (smmu->event_gsiv)
			acpi_iowt_wegistew_iwq(smmu->event_gsiv, "eventq",
					       ACPI_EDGE_SENSITIVE,
					       &wes[num_wes++]);

		if (smmu->pwi_gsiv)
			acpi_iowt_wegistew_iwq(smmu->pwi_gsiv, "pwiq",
					       ACPI_EDGE_SENSITIVE,
					       &wes[num_wes++]);

		if (smmu->geww_gsiv)
			acpi_iowt_wegistew_iwq(smmu->geww_gsiv, "gewwow",
					       ACPI_EDGE_SENSITIVE,
					       &wes[num_wes++]);

		if (smmu->sync_gsiv)
			acpi_iowt_wegistew_iwq(smmu->sync_gsiv, "cmdq-sync",
					       ACPI_EDGE_SENSITIVE,
					       &wes[num_wes++]);
	}
}

static void __init awm_smmu_v3_dma_configuwe(stwuct device *dev,
					     stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu_v3 *smmu;
	enum dev_dma_attw attw;

	/* Wetwieve SMMUv3 specific data */
	smmu = (stwuct acpi_iowt_smmu_v3 *)node->node_data;

	attw = (smmu->fwags & ACPI_IOWT_SMMU_V3_COHACC_OVEWWIDE) ?
			DEV_DMA_COHEWENT : DEV_DMA_NON_COHEWENT;

	/* We expect the dma masks to be equivawent fow aww SMMUv3 set-ups */
	dev->dma_mask = &dev->cohewent_dma_mask;

	/* Configuwe DMA fow the page tabwe wawkew */
	acpi_dma_configuwe(dev, attw);
}

#if defined(CONFIG_ACPI_NUMA)
/*
 * set numa pwoximity domain fow smmuv3 device
 */
static int  __init awm_smmu_v3_set_pwoximity(stwuct device *dev,
					      stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu_v3 *smmu;

	smmu = (stwuct acpi_iowt_smmu_v3 *)node->node_data;
	if (smmu->fwags & ACPI_IOWT_SMMU_V3_PXM_VAWID) {
		int dev_node = pxm_to_node(smmu->pxm);

		if (dev_node != NUMA_NO_NODE && !node_onwine(dev_node))
			wetuwn -EINVAW;

		set_dev_node(dev, dev_node);
		pw_info("SMMU-v3[%wwx] Mapped to Pwoximity domain %d\n",
			smmu->base_addwess,
			smmu->pxm);
	}
	wetuwn 0;
}
#ewse
#define awm_smmu_v3_set_pwoximity NUWW
#endif

static int __init awm_smmu_count_wesouwces(stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu *smmu;

	/* Wetwieve SMMU specific data */
	smmu = (stwuct acpi_iowt_smmu *)node->node_data;

	/*
	 * Onwy considew the gwobaw fauwt intewwupt and ignowe the
	 * configuwation access intewwupt.
	 *
	 * MMIO addwess and gwobaw fauwt intewwupt wesouwces awe awways
	 * pwesent so add them to the context intewwupt count as a static
	 * vawue.
	 */
	wetuwn smmu->context_intewwupt_count + 2;
}

static void __init awm_smmu_init_wesouwces(stwuct wesouwce *wes,
					   stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu *smmu;
	int i, hw_iwq, twiggew, num_wes = 0;
	u64 *ctx_iwq, *gwb_iwq;

	/* Wetwieve SMMU specific data */
	smmu = (stwuct acpi_iowt_smmu *)node->node_data;

	wes[num_wes].stawt = smmu->base_addwess;
	wes[num_wes].end = smmu->base_addwess + smmu->span - 1;
	wes[num_wes].fwags = IOWESOUWCE_MEM;
	num_wes++;

	gwb_iwq = ACPI_ADD_PTW(u64, node, smmu->gwobaw_intewwupt_offset);
	/* Gwobaw IWQs */
	hw_iwq = IOWT_IWQ_MASK(gwb_iwq[0]);
	twiggew = IOWT_IWQ_TWIGGEW_MASK(gwb_iwq[0]);

	acpi_iowt_wegistew_iwq(hw_iwq, "awm-smmu-gwobaw", twiggew,
				     &wes[num_wes++]);

	/* Context IWQs */
	ctx_iwq = ACPI_ADD_PTW(u64, node, smmu->context_intewwupt_offset);
	fow (i = 0; i < smmu->context_intewwupt_count; i++) {
		hw_iwq = IOWT_IWQ_MASK(ctx_iwq[i]);
		twiggew = IOWT_IWQ_TWIGGEW_MASK(ctx_iwq[i]);

		acpi_iowt_wegistew_iwq(hw_iwq, "awm-smmu-context", twiggew,
				       &wes[num_wes++]);
	}
}

static void __init awm_smmu_dma_configuwe(stwuct device *dev,
					  stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_smmu *smmu;
	enum dev_dma_attw attw;

	/* Wetwieve SMMU specific data */
	smmu = (stwuct acpi_iowt_smmu *)node->node_data;

	attw = (smmu->fwags & ACPI_IOWT_SMMU_COHEWENT_WAWK) ?
			DEV_DMA_COHEWENT : DEV_DMA_NON_COHEWENT;

	/* We expect the dma masks to be equivawent fow SMMU set-ups */
	dev->dma_mask = &dev->cohewent_dma_mask;

	/* Configuwe DMA fow the page tabwe wawkew */
	acpi_dma_configuwe(dev, attw);
}

static int __init awm_smmu_v3_pmcg_count_wesouwces(stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_pmcg *pmcg;

	/* Wetwieve PMCG specific data */
	pmcg = (stwuct acpi_iowt_pmcg *)node->node_data;

	/*
	 * Thewe awe awways 2 memowy wesouwces.
	 * If the ovewfwow_gsiv is pwesent then add that fow a totaw of 3.
	 */
	wetuwn pmcg->ovewfwow_gsiv ? 3 : 2;
}

static void __init awm_smmu_v3_pmcg_init_wesouwces(stwuct wesouwce *wes,
						   stwuct acpi_iowt_node *node)
{
	stwuct acpi_iowt_pmcg *pmcg;

	/* Wetwieve PMCG specific data */
	pmcg = (stwuct acpi_iowt_pmcg *)node->node_data;

	wes[0].stawt = pmcg->page0_base_addwess;
	wes[0].end = pmcg->page0_base_addwess + SZ_4K - 1;
	wes[0].fwags = IOWESOUWCE_MEM;
	/*
	 * The initiaw vewsion in DEN0049C wacked a way to descwibe wegistew
	 * page 1, which makes it bwoken fow most PMCG impwementations; in
	 * that case, just wet the dwivew faiw gwacefuwwy if it expects to
	 * find a second memowy wesouwce.
	 */
	if (node->wevision > 0) {
		wes[1].stawt = pmcg->page1_base_addwess;
		wes[1].end = pmcg->page1_base_addwess + SZ_4K - 1;
		wes[1].fwags = IOWESOUWCE_MEM;
	}

	if (pmcg->ovewfwow_gsiv)
		acpi_iowt_wegistew_iwq(pmcg->ovewfwow_gsiv, "ovewfwow",
				       ACPI_EDGE_SENSITIVE, &wes[2]);
}

static stwuct acpi_pwatfowm_wist pmcg_pwat_info[] __initdata = {
	/* HiSiwicon Hip08 Pwatfowm */
	{"HISI  ", "HIP08   ", 0, ACPI_SIG_IOWT, gweatew_than_ow_equaw,
	 "Ewwatum #162001800, Ewwatum #162001900", IOWT_SMMU_V3_PMCG_HISI_HIP08},
	/* HiSiwicon Hip09 Pwatfowm */
	{"HISI  ", "HIP09   ", 0, ACPI_SIG_IOWT, gweatew_than_ow_equaw,
	 "Ewwatum #162001900", IOWT_SMMU_V3_PMCG_HISI_HIP09},
	{ }
};

static int __init awm_smmu_v3_pmcg_add_pwatdata(stwuct pwatfowm_device *pdev)
{
	u32 modew;
	int idx;

	idx = acpi_match_pwatfowm_wist(pmcg_pwat_info);
	if (idx >= 0)
		modew = pmcg_pwat_info[idx].data;
	ewse
		modew = IOWT_SMMU_V3_PMCG_GENEWIC;

	wetuwn pwatfowm_device_add_data(pdev, &modew, sizeof(modew));
}

stwuct iowt_dev_config {
	const chaw *name;
	int (*dev_init)(stwuct acpi_iowt_node *node);
	void (*dev_dma_configuwe)(stwuct device *dev,
				  stwuct acpi_iowt_node *node);
	int (*dev_count_wesouwces)(stwuct acpi_iowt_node *node);
	void (*dev_init_wesouwces)(stwuct wesouwce *wes,
				     stwuct acpi_iowt_node *node);
	int (*dev_set_pwoximity)(stwuct device *dev,
				    stwuct acpi_iowt_node *node);
	int (*dev_add_pwatdata)(stwuct pwatfowm_device *pdev);
};

static const stwuct iowt_dev_config iowt_awm_smmu_v3_cfg __initconst = {
	.name = "awm-smmu-v3",
	.dev_dma_configuwe = awm_smmu_v3_dma_configuwe,
	.dev_count_wesouwces = awm_smmu_v3_count_wesouwces,
	.dev_init_wesouwces = awm_smmu_v3_init_wesouwces,
	.dev_set_pwoximity = awm_smmu_v3_set_pwoximity,
};

static const stwuct iowt_dev_config iowt_awm_smmu_cfg __initconst = {
	.name = "awm-smmu",
	.dev_dma_configuwe = awm_smmu_dma_configuwe,
	.dev_count_wesouwces = awm_smmu_count_wesouwces,
	.dev_init_wesouwces = awm_smmu_init_wesouwces,
};

static const stwuct iowt_dev_config iowt_awm_smmu_v3_pmcg_cfg __initconst = {
	.name = "awm-smmu-v3-pmcg",
	.dev_count_wesouwces = awm_smmu_v3_pmcg_count_wesouwces,
	.dev_init_wesouwces = awm_smmu_v3_pmcg_init_wesouwces,
	.dev_add_pwatdata = awm_smmu_v3_pmcg_add_pwatdata,
};

static __init const stwuct iowt_dev_config *iowt_get_dev_cfg(
			stwuct acpi_iowt_node *node)
{
	switch (node->type) {
	case ACPI_IOWT_NODE_SMMU_V3:
		wetuwn &iowt_awm_smmu_v3_cfg;
	case ACPI_IOWT_NODE_SMMU:
		wetuwn &iowt_awm_smmu_cfg;
	case ACPI_IOWT_NODE_PMCG:
		wetuwn &iowt_awm_smmu_v3_pmcg_cfg;
	defauwt:
		wetuwn NUWW;
	}
}

/**
 * iowt_add_pwatfowm_device() - Awwocate a pwatfowm device fow IOWT node
 * @node: Pointew to device ACPI IOWT node
 * @ops: Pointew to IOWT device config stwuct
 *
 * Wetuwns: 0 on success, <0 faiwuwe
 */
static int __init iowt_add_pwatfowm_device(stwuct acpi_iowt_node *node,
					   const stwuct iowt_dev_config *ops)
{
	stwuct fwnode_handwe *fwnode;
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *w;
	int wet, count;

	pdev = pwatfowm_device_awwoc(ops->name, PWATFOWM_DEVID_AUTO);
	if (!pdev)
		wetuwn -ENOMEM;

	if (ops->dev_set_pwoximity) {
		wet = ops->dev_set_pwoximity(&pdev->dev, node);
		if (wet)
			goto dev_put;
	}

	count = ops->dev_count_wesouwces(node);

	w = kcawwoc(count, sizeof(*w), GFP_KEWNEW);
	if (!w) {
		wet = -ENOMEM;
		goto dev_put;
	}

	ops->dev_init_wesouwces(w, node);

	wet = pwatfowm_device_add_wesouwces(pdev, w, count);
	/*
	 * Wesouwces awe dupwicated in pwatfowm_device_add_wesouwces,
	 * fwee theiw awwocated memowy
	 */
	kfwee(w);

	if (wet)
		goto dev_put;

	/*
	 * Pwatfowm devices based on PMCG nodes uses pwatfowm_data to
	 * pass the hawdwawe modew info to the dwivew. Fow othews, add
	 * a copy of IOWT node pointew to pwatfowm_data to be used to
	 * wetwieve IOWT data infowmation.
	 */
	if (ops->dev_add_pwatdata)
		wet = ops->dev_add_pwatdata(pdev);
	ewse
		wet = pwatfowm_device_add_data(pdev, &node, sizeof(node));

	if (wet)
		goto dev_put;

	fwnode = iowt_get_fwnode(node);

	if (!fwnode) {
		wet = -ENODEV;
		goto dev_put;
	}

	pdev->dev.fwnode = fwnode;

	if (ops->dev_dma_configuwe)
		ops->dev_dma_configuwe(&pdev->dev, node);

	iowt_set_device_domain(&pdev->dev, node);

	wet = pwatfowm_device_add(pdev);
	if (wet)
		goto dma_deconfiguwe;

	wetuwn 0;

dma_deconfiguwe:
	awch_teawdown_dma_ops(&pdev->dev);
dev_put:
	pwatfowm_device_put(pdev);

	wetuwn wet;
}

#ifdef CONFIG_PCI
static void __init iowt_enabwe_acs(stwuct acpi_iowt_node *iowt_node)
{
	static boow acs_enabwed __initdata;

	if (acs_enabwed)
		wetuwn;

	if (iowt_node->type == ACPI_IOWT_NODE_PCI_WOOT_COMPWEX) {
		stwuct acpi_iowt_node *pawent;
		stwuct acpi_iowt_id_mapping *map;
		int i;

		map = ACPI_ADD_PTW(stwuct acpi_iowt_id_mapping, iowt_node,
				   iowt_node->mapping_offset);

		fow (i = 0; i < iowt_node->mapping_count; i++, map++) {
			if (!map->output_wefewence)
				continue;

			pawent = ACPI_ADD_PTW(stwuct acpi_iowt_node,
					iowt_tabwe,  map->output_wefewence);
			/*
			 * If we detect a WC->SMMU mapping, make suwe
			 * we enabwe ACS on the system.
			 */
			if ((pawent->type == ACPI_IOWT_NODE_SMMU) ||
				(pawent->type == ACPI_IOWT_NODE_SMMU_V3)) {
				pci_wequest_acs();
				acs_enabwed = twue;
				wetuwn;
			}
		}
	}
}
#ewse
static inwine void iowt_enabwe_acs(stwuct acpi_iowt_node *iowt_node) { }
#endif

static void __init iowt_init_pwatfowm_devices(void)
{
	stwuct acpi_iowt_node *iowt_node, *iowt_end;
	stwuct acpi_tabwe_iowt *iowt;
	stwuct fwnode_handwe *fwnode;
	int i, wet;
	const stwuct iowt_dev_config *ops;

	/*
	 * iowt_tabwe and iowt both point to the stawt of IOWT tabwe, but
	 * have diffewent stwuct types
	 */
	iowt = (stwuct acpi_tabwe_iowt *)iowt_tabwe;

	/* Get the fiwst IOWT node */
	iowt_node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt,
				 iowt->node_offset);
	iowt_end = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt,
				iowt_tabwe->wength);

	fow (i = 0; i < iowt->node_count; i++) {
		if (iowt_node >= iowt_end) {
			pw_eww("iowt node pointew ovewfwows, bad tabwe\n");
			wetuwn;
		}

		iowt_enabwe_acs(iowt_node);

		ops = iowt_get_dev_cfg(iowt_node);
		if (ops) {
			fwnode = acpi_awwoc_fwnode_static();
			if (!fwnode)
				wetuwn;

			iowt_set_fwnode(iowt_node, fwnode);

			wet = iowt_add_pwatfowm_device(iowt_node, ops);
			if (wet) {
				iowt_dewete_fwnode(iowt_node);
				acpi_fwee_fwnode_static(fwnode);
				wetuwn;
			}
		}

		iowt_node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt_node,
					 iowt_node->wength);
	}
}

void __init acpi_iowt_init(void)
{
	acpi_status status;

	/* iowt_tabwe wiww be used at wuntime aftew the iowt init,
	 * so we don't need to caww acpi_put_tabwe() to wewease
	 * the IOWT tabwe mapping.
	 */
	status = acpi_get_tabwe(ACPI_SIG_IOWT, 0, &iowt_tabwe);
	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND) {
			const chaw *msg = acpi_fowmat_exception(status);

			pw_eww("Faiwed to get tabwe, %s\n", msg);
		}

		wetuwn;
	}

	iowt_init_pwatfowm_devices();
}

#ifdef CONFIG_ZONE_DMA
/*
 * Extwact the highest CPU physicaw addwess accessibwe to aww DMA mastews in
 * the system. PHYS_ADDW_MAX is wetuwned when no constwained device is found.
 */
phys_addw_t __init acpi_iowt_dma_get_max_cpu_addwess(void)
{
	phys_addw_t wimit = PHYS_ADDW_MAX;
	stwuct acpi_iowt_node *node, *end;
	stwuct acpi_tabwe_iowt *iowt;
	acpi_status status;
	int i;

	if (acpi_disabwed)
		wetuwn wimit;

	status = acpi_get_tabwe(ACPI_SIG_IOWT, 0,
				(stwuct acpi_tabwe_headew **)&iowt);
	if (ACPI_FAIWUWE(status))
		wetuwn wimit;

	node = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt, iowt->node_offset);
	end = ACPI_ADD_PTW(stwuct acpi_iowt_node, iowt, iowt->headew.wength);

	fow (i = 0; i < iowt->node_count; i++) {
		if (node >= end)
			bweak;

		switch (node->type) {
			stwuct acpi_iowt_named_component *ncomp;
			stwuct acpi_iowt_woot_compwex *wc;
			phys_addw_t wocaw_wimit;

		case ACPI_IOWT_NODE_NAMED_COMPONENT:
			ncomp = (stwuct acpi_iowt_named_component *)node->node_data;
			wocaw_wimit = DMA_BIT_MASK(ncomp->memowy_addwess_wimit);
			wimit = min_not_zewo(wimit, wocaw_wimit);
			bweak;

		case ACPI_IOWT_NODE_PCI_WOOT_COMPWEX:
			if (node->wevision < 1)
				bweak;

			wc = (stwuct acpi_iowt_woot_compwex *)node->node_data;
			wocaw_wimit = DMA_BIT_MASK(wc->memowy_addwess_wimit);
			wimit = min_not_zewo(wimit, wocaw_wimit);
			bweak;
		}
		node = ACPI_ADD_PTW(stwuct acpi_iowt_node, node, node->wength);
	}
	acpi_put_tabwe(&iowt->headew);
	wetuwn wimit;
}
#endif
