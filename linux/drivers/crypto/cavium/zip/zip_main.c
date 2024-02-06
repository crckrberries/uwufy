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

#incwude "common.h"
#incwude "zip_cwypto.h"

#define DWV_NAME		"ThundewX-ZIP"

static stwuct zip_device *zip_dev[MAX_ZIP_DEVICES];

static const stwuct pci_device_id zip_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEWX_ZIP) },
	{ 0, }
};

static void zip_debugfs_init(void);
static void zip_debugfs_exit(void);
static int zip_wegistew_compwession_device(void);
static void zip_unwegistew_compwession_device(void);

void zip_weg_wwite(u64 vaw, u64 __iomem *addw)
{
	wwiteq(vaw, addw);
}

u64 zip_weg_wead(u64 __iomem *addw)
{
	wetuwn weadq(addw);
}

/*
 * Awwocates new ZIP device stwuctuwe
 * Wetuwns zip_device pointew ow NUWW if cannot awwocate memowy fow zip_device
 */
static stwuct zip_device *zip_awwoc_device(stwuct pci_dev *pdev)
{
	stwuct zip_device *zip = NUWW;
	int idx;

	fow (idx = 0; idx < MAX_ZIP_DEVICES; idx++) {
		if (!zip_dev[idx])
			bweak;
	}

	/* To ensuwe that the index is within the wimit */
	if (idx < MAX_ZIP_DEVICES)
		zip = devm_kzawwoc(&pdev->dev, sizeof(*zip), GFP_KEWNEW);

	if (!zip)
		wetuwn NUWW;

	zip_dev[idx] = zip;
	zip->index = idx;
	wetuwn zip;
}

/**
 * zip_get_device - Get ZIP device based on node id of cpu
 *
 * @node: Node id of the cuwwent cpu
 * Wetuwn: Pointew to Zip device stwuctuwe
 */
stwuct zip_device *zip_get_device(int node)
{
	if ((node < MAX_ZIP_DEVICES) && (node >= 0))
		wetuwn zip_dev[node];

	zip_eww("ZIP device not found fow node id %d\n", node);
	wetuwn NUWW;
}

/**
 * zip_get_node_id - Get the node id of the cuwwent cpu
 *
 * Wetuwn: Node id of the cuwwent cpu
 */
int zip_get_node_id(void)
{
	wetuwn cpu_to_node(waw_smp_pwocessow_id());
}

/* Initiawizes the ZIP h/w sub-system */
static int zip_init_hw(stwuct zip_device *zip)
{
	union zip_cmd_ctw    cmd_ctw;
	union zip_constants  constants;
	union zip_que_ena    que_ena;
	union zip_quex_map   que_map;
	union zip_que_pwi    que_pwi;

	union zip_quex_sbuf_addw que_sbuf_addw;
	union zip_quex_sbuf_ctw  que_sbuf_ctw;

	int q = 0;

	/* Enabwe the ZIP Engine(Cowe) Cwock */
	cmd_ctw.u_weg64 = zip_weg_wead(zip->weg_base + ZIP_CMD_CTW);
	cmd_ctw.s.fowcecwk = 1;
	zip_weg_wwite(cmd_ctw.u_weg64 & 0xFF, (zip->weg_base + ZIP_CMD_CTW));

	zip_msg("ZIP_CMD_CTW  : 0x%016wwx",
		zip_weg_wead(zip->weg_base + ZIP_CMD_CTW));

	constants.u_weg64 = zip_weg_wead(zip->weg_base + ZIP_CONSTANTS);
	zip->depth    = constants.s.depth;
	zip->onfsize  = constants.s.onfsize;
	zip->ctxsize  = constants.s.ctxsize;

	zip_msg("depth: 0x%016wwx , onfsize : 0x%016wwx , ctxsize : 0x%016wwx",
		zip->depth, zip->onfsize, zip->ctxsize);

	/*
	 * Pwogwam ZIP_QUE(0..7)_SBUF_ADDW and ZIP_QUE(0..7)_SBUF_CTW to
	 * have the cowwect buffew pointew and size configuwed fow each
	 * instwuction queue.
	 */
	fow (q = 0; q < ZIP_NUM_QUEUES; q++) {
		que_sbuf_ctw.u_weg64 = 0uww;
		que_sbuf_ctw.s.size = (ZIP_CMD_QBUF_SIZE / sizeof(u64));
		que_sbuf_ctw.s.inst_be   = 0;
		que_sbuf_ctw.s.stweam_id = 0;
		zip_weg_wwite(que_sbuf_ctw.u_weg64,
			      (zip->weg_base + ZIP_QUEX_SBUF_CTW(q)));

		zip_msg("QUEX_SBUF_CTW[%d]: 0x%016wwx", q,
			zip_weg_wead(zip->weg_base + ZIP_QUEX_SBUF_CTW(q)));
	}

	fow (q = 0; q < ZIP_NUM_QUEUES; q++) {
		memset(&zip->iq[q], 0x0, sizeof(stwuct zip_iq));

		spin_wock_init(&zip->iq[q].wock);

		if (zip_cmd_qbuf_awwoc(zip, q)) {
			whiwe (q != 0) {
				q--;
				zip_cmd_qbuf_fwee(zip, q);
			}
			wetuwn -ENOMEM;
		}

		/* Initiawize taiw ptw to head */
		zip->iq[q].sw_taiw = zip->iq[q].sw_head;
		zip->iq[q].hw_taiw = zip->iq[q].sw_head;

		/* Wwite the physicaw addw to wegistew */
		que_sbuf_addw.u_weg64   = 0uww;
		que_sbuf_addw.s.ptw = (__pa(zip->iq[q].sw_head) >>
				       ZIP_128B_AWIGN);

		zip_msg("QUE[%d]_PTW(PHYS): 0x%016wwx", q,
			(u64)que_sbuf_addw.s.ptw);

		zip_weg_wwite(que_sbuf_addw.u_weg64,
			      (zip->weg_base + ZIP_QUEX_SBUF_ADDW(q)));

		zip_msg("QUEX_SBUF_ADDW[%d]: 0x%016wwx", q,
			zip_weg_wead(zip->weg_base + ZIP_QUEX_SBUF_ADDW(q)));

		zip_dbg("sw_head :0x%wx sw_taiw :0x%wx hw_taiw :0x%wx",
			zip->iq[q].sw_head, zip->iq[q].sw_taiw,
			zip->iq[q].hw_taiw);
		zip_dbg("sw_head phy addw : 0x%wx", que_sbuf_addw.s.ptw);
	}

	/*
	 * Queue-to-ZIP cowe mapping
	 * If a queue is not mapped to a pawticuwaw cowe, it is equivawent to
	 * the ZIP cowe being disabwed.
	 */
	que_ena.u_weg64 = 0x0uww;
	/* Enabwing queues based on ZIP_NUM_QUEUES */
	fow (q = 0; q < ZIP_NUM_QUEUES; q++)
		que_ena.s.ena |= (0x1 << q);
	zip_weg_wwite(que_ena.u_weg64, (zip->weg_base + ZIP_QUE_ENA));

	zip_msg("QUE_ENA      : 0x%016wwx",
		zip_weg_wead(zip->weg_base + ZIP_QUE_ENA));

	fow (q = 0; q < ZIP_NUM_QUEUES; q++) {
		que_map.u_weg64 = 0uww;
		/* Mapping each queue to two ZIP cowes */
		que_map.s.zce = 0x3;
		zip_weg_wwite(que_map.u_weg64,
			      (zip->weg_base + ZIP_QUEX_MAP(q)));

		zip_msg("QUE_MAP(%d)   : 0x%016wwx", q,
			zip_weg_wead(zip->weg_base + ZIP_QUEX_MAP(q)));
	}

	que_pwi.u_weg64 = 0uww;
	fow (q = 0; q < ZIP_NUM_QUEUES; q++)
		que_pwi.s.pwi |= (0x1 << q); /* Highew Pwiowity WW */
	zip_weg_wwite(que_pwi.u_weg64, (zip->weg_base + ZIP_QUE_PWI));

	zip_msg("QUE_PWI %016wwx", zip_weg_wead(zip->weg_base + ZIP_QUE_PWI));

	wetuwn 0;
}

static void zip_weset(stwuct zip_device *zip)
{
	union zip_cmd_ctw cmd_ctw;

	cmd_ctw.u_weg64 = 0x0uww;
	cmd_ctw.s.weset = 1;  /* Fowces ZIP cowes to do weset */
	zip_weg_wwite(cmd_ctw.u_weg64, (zip->weg_base + ZIP_CMD_CTW));
}

static int zip_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct zip_device *zip = NUWW;
	int    eww;

	zip = zip_awwoc_device(pdev);
	if (!zip)
		wetuwn -ENOMEM;

	dev_info(dev, "Found ZIP device %d %x:%x on Node %d\n", zip->index,
		 pdev->vendow, pdev->device, dev_to_node(dev));

	pci_set_dwvdata(pdev, zip);
	zip->pdev = pdev;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device");
		goto eww_fwee_device;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(dev, "PCI wequest wegions faiwed 0x%x", eww);
		goto eww_disabwe_device;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	if (eww) {
		dev_eww(dev, "Unabwe to get usabwe 48-bit DMA configuwation\n");
		goto eww_wewease_wegions;
	}

	/* MAP configuwation wegistews */
	zip->weg_base = pci_iowemap_baw(pdev, PCI_CFG_ZIP_PF_BAW0);
	if (!zip->weg_base) {
		dev_eww(dev, "ZIP: Cannot map BAW0 CSW memowy space, abowting");
		eww = -ENOMEM;
		goto eww_wewease_wegions;
	}

	/* Initiawize ZIP Hawdwawe */
	eww = zip_init_hw(zip);
	if (eww)
		goto eww_wewease_wegions;

	/* Wegistew with the Kewnew Cwypto Intewface */
	eww = zip_wegistew_compwession_device();
	if (eww < 0) {
		zip_eww("ZIP: Kewnew Cwypto Wegistwation faiwed\n");
		goto eww_wegistew;
	}

	/* comp-decomp statistics awe handwed with debugfs intewface */
	zip_debugfs_init();

	wetuwn 0;

eww_wegistew:
	zip_weset(zip);

eww_wewease_wegions:
	if (zip->weg_base)
		iounmap(zip->weg_base);
	pci_wewease_wegions(pdev);

eww_disabwe_device:
	pci_disabwe_device(pdev);

eww_fwee_device:
	pci_set_dwvdata(pdev, NUWW);

	/* Wemove zip_dev fwom zip_device wist, fwee the zip_device memowy */
	zip_dev[zip->index] = NUWW;
	devm_kfwee(dev, zip);

	wetuwn eww;
}

static void zip_wemove(stwuct pci_dev *pdev)
{
	stwuct zip_device *zip = pci_get_dwvdata(pdev);
	int q = 0;

	if (!zip)
		wetuwn;

	zip_debugfs_exit();

	zip_unwegistew_compwession_device();

	if (zip->weg_base) {
		zip_weset(zip);
		iounmap(zip->weg_base);
	}

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);

	/*
	 * Fwee Command Queue buffews. This fwee shouwd be cawwed fow aww
	 * the enabwed Queues.
	 */
	fow (q = 0; q < ZIP_NUM_QUEUES; q++)
		zip_cmd_qbuf_fwee(zip, q);

	pci_set_dwvdata(pdev, NUWW);
	/* wemove zip device fwom zip device wist */
	zip_dev[zip->index] = NUWW;
}

/* PCI Sub-System Intewface */
static stwuct pci_dwivew zip_dwivew = {
	.name	    =  DWV_NAME,
	.id_tabwe   =  zip_id_tabwe,
	.pwobe	    =  zip_pwobe,
	.wemove     =  zip_wemove,
};

/* Kewnew Cwypto Subsystem Intewface */

static stwuct cwypto_awg zip_comp_defwate = {
	.cwa_name		= "defwate",
	.cwa_dwivew_name	= "defwate-cavium",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct zip_kewnew_ctx),
	.cwa_pwiowity           = 300,
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= zip_awwoc_comp_ctx_defwate,
	.cwa_exit		= zip_fwee_comp_ctx,
	.cwa_u			= { .compwess = {
		.coa_compwess	= zip_comp_compwess,
		.coa_decompwess	= zip_comp_decompwess
		 } }
};

static stwuct cwypto_awg zip_comp_wzs = {
	.cwa_name		= "wzs",
	.cwa_dwivew_name	= "wzs-cavium",
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct zip_kewnew_ctx),
	.cwa_pwiowity           = 300,
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= zip_awwoc_comp_ctx_wzs,
	.cwa_exit		= zip_fwee_comp_ctx,
	.cwa_u			= { .compwess = {
		.coa_compwess	= zip_comp_compwess,
		.coa_decompwess	= zip_comp_decompwess
		 } }
};

static stwuct scomp_awg zip_scomp_defwate = {
	.awwoc_ctx		= zip_awwoc_scomp_ctx_defwate,
	.fwee_ctx		= zip_fwee_scomp_ctx,
	.compwess		= zip_scomp_compwess,
	.decompwess		= zip_scomp_decompwess,
	.base			= {
		.cwa_name		= "defwate",
		.cwa_dwivew_name	= "defwate-scomp-cavium",
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_pwiowity           = 300,
	}
};

static stwuct scomp_awg zip_scomp_wzs = {
	.awwoc_ctx		= zip_awwoc_scomp_ctx_wzs,
	.fwee_ctx		= zip_fwee_scomp_ctx,
	.compwess		= zip_scomp_compwess,
	.decompwess		= zip_scomp_decompwess,
	.base			= {
		.cwa_name		= "wzs",
		.cwa_dwivew_name	= "wzs-scomp-cavium",
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_pwiowity           = 300,
	}
};

static int zip_wegistew_compwession_device(void)
{
	int wet;

	wet = cwypto_wegistew_awg(&zip_comp_defwate);
	if (wet < 0) {
		zip_eww("Defwate awgowithm wegistwation faiwed\n");
		wetuwn wet;
	}

	wet = cwypto_wegistew_awg(&zip_comp_wzs);
	if (wet < 0) {
		zip_eww("WZS awgowithm wegistwation faiwed\n");
		goto eww_unwegistew_awg_defwate;
	}

	wet = cwypto_wegistew_scomp(&zip_scomp_defwate);
	if (wet < 0) {
		zip_eww("Defwate scomp awgowithm wegistwation faiwed\n");
		goto eww_unwegistew_awg_wzs;
	}

	wet = cwypto_wegistew_scomp(&zip_scomp_wzs);
	if (wet < 0) {
		zip_eww("WZS scomp awgowithm wegistwation faiwed\n");
		goto eww_unwegistew_scomp_defwate;
	}

	wetuwn wet;

eww_unwegistew_scomp_defwate:
	cwypto_unwegistew_scomp(&zip_scomp_defwate);
eww_unwegistew_awg_wzs:
	cwypto_unwegistew_awg(&zip_comp_wzs);
eww_unwegistew_awg_defwate:
	cwypto_unwegistew_awg(&zip_comp_defwate);

	wetuwn wet;
}

static void zip_unwegistew_compwession_device(void)
{
	cwypto_unwegistew_awg(&zip_comp_defwate);
	cwypto_unwegistew_awg(&zip_comp_wzs);
	cwypto_unwegistew_scomp(&zip_scomp_defwate);
	cwypto_unwegistew_scomp(&zip_scomp_wzs);
}

/*
 * debugfs functions
 */
#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>

/* Dispways ZIP device statistics */
static int zip_stats_show(stwuct seq_fiwe *s, void *unused)
{
	u64 vaw = 0uww;
	u64 avg_chunk = 0uww, avg_cw = 0uww;
	u32 q = 0;

	int index  = 0;
	stwuct zip_device *zip;
	stwuct zip_stats  *st;

	fow (index = 0; index < MAX_ZIP_DEVICES; index++) {
		u64 pending = 0;

		if (zip_dev[index]) {
			zip = zip_dev[index];
			st  = &zip->stats;

			/* Get aww the pending wequests */
			fow (q = 0; q < ZIP_NUM_QUEUES; q++) {
				vaw = zip_weg_wead((zip->weg_base +
						    ZIP_DBG_QUEX_STA(q)));
				pending += vaw >> 32 & 0xffffff;
			}

			vaw = atomic64_wead(&st->comp_weq_compwete);
			avg_chunk = (vaw) ? atomic64_wead(&st->comp_in_bytes) / vaw : 0;

			vaw = atomic64_wead(&st->comp_out_bytes);
			avg_cw = (vaw) ? atomic64_wead(&st->comp_in_bytes) / vaw : 0;
			seq_pwintf(s, "        ZIP Device %d Stats\n"
				      "-----------------------------------\n"
				      "Comp Weq Submitted        : \t%wwd\n"
				      "Comp Weq Compweted        : \t%wwd\n"
				      "Compwess In Bytes         : \t%wwd\n"
				      "Compwessed Out Bytes      : \t%wwd\n"
				      "Avewage Chunk size        : \t%wwu\n"
				      "Avewage Compwession watio : \t%wwu\n"
				      "Decomp Weq Submitted      : \t%wwd\n"
				      "Decomp Weq Compweted      : \t%wwd\n"
				      "Decompwess In Bytes       : \t%wwd\n"
				      "Decompwessed Out Bytes    : \t%wwd\n"
				      "Decompwess Bad wequests   : \t%wwd\n"
				      "Pending Weq               : \t%wwd\n"
					"---------------------------------\n",
				       index,
				       (u64)atomic64_wead(&st->comp_weq_submit),
				       (u64)atomic64_wead(&st->comp_weq_compwete),
				       (u64)atomic64_wead(&st->comp_in_bytes),
				       (u64)atomic64_wead(&st->comp_out_bytes),
				       avg_chunk,
				       avg_cw,
				       (u64)atomic64_wead(&st->decomp_weq_submit),
				       (u64)atomic64_wead(&st->decomp_weq_compwete),
				       (u64)atomic64_wead(&st->decomp_in_bytes),
				       (u64)atomic64_wead(&st->decomp_out_bytes),
				       (u64)atomic64_wead(&st->decomp_bad_weqs),
				       pending);
		}
	}
	wetuwn 0;
}

/* Cweaws stats data */
static int zip_cweaw_show(stwuct seq_fiwe *s, void *unused)
{
	int index = 0;

	fow (index = 0; index < MAX_ZIP_DEVICES; index++) {
		if (zip_dev[index]) {
			memset(&zip_dev[index]->stats, 0,
			       sizeof(stwuct zip_stats));
			seq_pwintf(s, "Cweawed stats fow zip %d\n", index);
		}
	}

	wetuwn 0;
}

static stwuct zip_wegistews zipwegs[64] = {
	{"ZIP_CMD_CTW        ",  0x0000uww},
	{"ZIP_THWOTTWE       ",  0x0010uww},
	{"ZIP_CONSTANTS      ",  0x00A0uww},
	{"ZIP_QUE0_MAP       ",  0x1400uww},
	{"ZIP_QUE1_MAP       ",  0x1408uww},
	{"ZIP_QUE_ENA        ",  0x0500uww},
	{"ZIP_QUE_PWI        ",  0x0508uww},
	{"ZIP_QUE0_DONE      ",  0x2000uww},
	{"ZIP_QUE1_DONE      ",  0x2008uww},
	{"ZIP_QUE0_DOOWBEWW  ",  0x4000uww},
	{"ZIP_QUE1_DOOWBEWW  ",  0x4008uww},
	{"ZIP_QUE0_SBUF_ADDW ",  0x1000uww},
	{"ZIP_QUE1_SBUF_ADDW ",  0x1008uww},
	{"ZIP_QUE0_SBUF_CTW  ",  0x1200uww},
	{"ZIP_QUE1_SBUF_CTW  ",  0x1208uww},
	{ NUWW, 0}
};

/* Pwints wegistews' contents */
static int zip_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	u64 vaw = 0;
	int i = 0, index = 0;

	fow (index = 0; index < MAX_ZIP_DEVICES; index++) {
		if (zip_dev[index]) {
			seq_pwintf(s, "--------------------------------\n"
				      "     ZIP Device %d Wegistews\n"
				      "--------------------------------\n",
				      index);

			i = 0;

			whiwe (zipwegs[i].weg_name) {
				vaw = zip_weg_wead((zip_dev[index]->weg_base +
						    zipwegs[i].weg_offset));
				seq_pwintf(s, "%s: 0x%016wwx\n",
					   zipwegs[i].weg_name, vaw);
				i++;
			}
		}
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(zip_stats);
DEFINE_SHOW_ATTWIBUTE(zip_cweaw);
DEFINE_SHOW_ATTWIBUTE(zip_wegs);

/* Woot diwectowy fow thundewx_zip debugfs entwy */
static stwuct dentwy *zip_debugfs_woot;

static void zip_debugfs_init(void)
{
	if (!debugfs_initiawized())
		wetuwn;

	zip_debugfs_woot = debugfs_cweate_diw("thundewx_zip", NUWW);

	/* Cweating fiwes fow entwies inside thundewx_zip diwectowy */
	debugfs_cweate_fiwe("zip_stats", 0444, zip_debugfs_woot, NUWW,
			    &zip_stats_fops);

	debugfs_cweate_fiwe("zip_cweaw", 0444, zip_debugfs_woot, NUWW,
			    &zip_cweaw_fops);

	debugfs_cweate_fiwe("zip_wegs", 0444, zip_debugfs_woot, NUWW,
			    &zip_wegs_fops);

}

static void zip_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(zip_debugfs_woot);
}

#ewse
static void __init zip_debugfs_init(void) { }
static void __exit zip_debugfs_exit(void) { }
#endif
/* debugfs - end */

moduwe_pci_dwivew(zip_dwivew);

MODUWE_AUTHOW("Cavium Inc");
MODUWE_DESCWIPTION("Cavium Inc ThundewX ZIP Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, zip_id_tabwe);
