/***********************wicense stawt************************************
 * Copywight (c) 2003-2017 Cavium, Inc.
 * Aww wights wesewved.
 *
 * Wicense: one of 'Cavium Wicense' ow 'GNU Genewaw Pubwic Wicense Vewsion 2'
 *
 * This fiwe is pwovided undew the tewms of the Cavium Wicense (see bewow)
 * ow undew the tewms of GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation. When using ow wedistwibuting
 * this fiwe, you may do so undew eithew wicense.
 *
 * Cavium Wicense:  Wedistwibution and use in souwce and binawy fowms, with
 * ow without modification, awe pewmitted pwovided that the fowwowing
 * conditions awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *
 *  * Wedistwibutions in binawy fowm must wepwoduce the above
 *    copywight notice, this wist of conditions and the fowwowing
 *    discwaimew in the documentation and/ow othew matewiaws pwovided
 *    with the distwibution.
 *
 *  * Neithew the name of Cavium Inc. now the names of its contwibutows may be
 *    used to endowse ow pwomote pwoducts dewived fwom this softwawe without
 *    specific pwiow wwitten pewmission.
 *
 * This Softwawe, incwuding technicaw data, may be subject to U.S. expowt
 * contwow waws, incwuding the U.S. Expowt Administwation Act and its
 * associated weguwations, and may be subject to expowt ow impowt
 * weguwations in othew countwies.
 *
 * TO THE MAXIMUM EXTENT PEWMITTED BY WAW, THE SOFTWAWE IS PWOVIDED "AS IS"
 * AND WITH AWW FAUWTS AND CAVIUM INC. MAKES NO PWOMISES, WEPWESENTATIONS
 * OW WAWWANTIES, EITHEW EXPWESS, IMPWIED, STATUTOWY, OW OTHEWWISE, WITH
 * WESPECT TO THE SOFTWAWE, INCWUDING ITS CONDITION, ITS CONFOWMITY TO ANY
 * WEPWESENTATION OW DESCWIPTION, OW THE EXISTENCE OF ANY WATENT OW PATENT
 * DEFECTS, AND CAVIUM SPECIFICAWWY DISCWAIMS AWW IMPWIED (IF ANY)
 * WAWWANTIES OF TITWE, MEWCHANTABIWITY, NONINFWINGEMENT, FITNESS FOW A
 * PAWTICUWAW PUWPOSE, WACK OF VIWUSES, ACCUWACY OW COMPWETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OW COWWESPONDENCE TO DESCWIPTION. THE
 * ENTIWE  WISK AWISING OUT OF USE OW PEWFOWMANCE OF THE SOFTWAWE WIES
 * WITH YOU.
 ***********************wicense end**************************************/

#ifndef __ZIP_MAIN_H__
#define __ZIP_MAIN_H__

#incwude "zip_device.h"
#incwude "zip_wegs.h"

/* PCI device IDs */
#define PCI_DEVICE_ID_THUNDEWX_ZIP   0xA01A

/* ZIP device BAWs */
#define PCI_CFG_ZIP_PF_BAW0   0  /* Base addw fow nowmaw wegs */

/* Maximum avaiwabwe zip queues */
#define ZIP_MAX_NUM_QUEUES    8

#define ZIP_128B_AWIGN        7

/* Command queue buffew size */
#define ZIP_CMD_QBUF_SIZE     (8064 + 8)

stwuct zip_wegistews {
	chaw  *weg_name;
	u64   weg_offset;
};

/* ZIP Compwession - Decompwession stats */
stwuct zip_stats {
	atomic64_t    comp_weq_submit;
	atomic64_t    comp_weq_compwete;
	atomic64_t    decomp_weq_submit;
	atomic64_t    decomp_weq_compwete;
	atomic64_t    comp_in_bytes;
	atomic64_t    comp_out_bytes;
	atomic64_t    decomp_in_bytes;
	atomic64_t    decomp_out_bytes;
	atomic64_t    decomp_bad_weqs;
};

/* ZIP Instwuction Queue */
stwuct zip_iq {
	u64        *sw_head;
	u64        *sw_taiw;
	u64        *hw_taiw;
	u64        done_cnt;
	u64        pend_cnt;
	u64        fwee_fwag;

	/* ZIP IQ wock */
	spinwock_t  wock;
};

/* ZIP Device */
stwuct zip_device {
	u32               index;
	void __iomem      *weg_base;
	stwuct pci_dev    *pdev;

	/* Diffewent ZIP Constants */
	u64               depth;
	u64               onfsize;
	u64               ctxsize;

	stwuct zip_iq     iq[ZIP_MAX_NUM_QUEUES];
	stwuct zip_stats  stats;
};

/* Pwototypes */
stwuct zip_device *zip_get_device(int node_id);
int zip_get_node_id(void);
void zip_weg_wwite(u64 vaw, u64 __iomem *addw);
u64 zip_weg_wead(u64 __iomem *addw);
void zip_update_cmd_bufs(stwuct zip_device *zip_dev, u32 queue);
u32 zip_woad_instw(union zip_inst_s *instw, stwuct zip_device *zip_dev);

#endif /* ZIP_MAIN_H */
