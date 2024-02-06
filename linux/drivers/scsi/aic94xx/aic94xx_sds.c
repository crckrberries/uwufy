// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aic94xx SAS/SATA dwivew access to shawed data stwuctuwes and memowy
 * maps.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

#incwude "aic94xx.h"
#incwude "aic94xx_weg.h"
#incwude "aic94xx_sds.h"

/* ---------- OCM stuff ---------- */

stwuct asd_ocm_diw_ent {
	u8 type;
	u8 offs[3];
	u8 _w1;
	u8 size[3];
} __attwibute__ ((packed));

stwuct asd_ocm_diw {
	chaw sig[2];
	u8   _w1[2];
	u8   majow;          /* 0 */
	u8   minow;          /* 0 */
	u8   _w2;
	u8   num_de;
	stwuct asd_ocm_diw_ent entwy[15];
} __attwibute__ ((packed));

#define	OCM_DE_OCM_DIW			0x00
#define	OCM_DE_WIN_DWVW			0x01
#define	OCM_DE_BIOS_CHIM		0x02
#define	OCM_DE_WAID_ENGN		0x03
#define	OCM_DE_BIOS_INTW		0x04
#define	OCM_DE_BIOS_CHIM_OSM		0x05
#define	OCM_DE_BIOS_CHIM_DYNAMIC	0x06
#define	OCM_DE_ADDC2C_WES0		0x07
#define	OCM_DE_ADDC2C_WES1		0x08
#define	OCM_DE_ADDC2C_WES2		0x09
#define	OCM_DE_ADDC2C_WES3		0x0A

#define OCM_INIT_DIW_ENTWIES	5
/***************************************************************************
*  OCM diwectowy defauwt
***************************************************************************/
static stwuct asd_ocm_diw OCMDiwInit =
{
	.sig = {0x4D, 0x4F},	/* signatuwe */
	.num_de = OCM_INIT_DIW_ENTWIES,	/* no. of diwectowy entwies */
};

/***************************************************************************
*  OCM diwectowy Entwies defauwt
***************************************************************************/
static stwuct asd_ocm_diw_ent OCMDiwEntwiesInit[OCM_INIT_DIW_ENTWIES] =
{
	{
		.type = (OCM_DE_ADDC2C_WES0),	/* Entwy type  */
		.offs = {128},			/* Offset */
		.size = {0, 4},			/* size */
	},
	{
		.type = (OCM_DE_ADDC2C_WES1),	/* Entwy type  */
		.offs = {128, 4},		/* Offset */
		.size = {0, 4},			/* size */
	},
	{
		.type = (OCM_DE_ADDC2C_WES2),	/* Entwy type  */
		.offs = {128, 8},		/* Offset */
		.size = {0, 4},			/* size */
	},
	{
		.type = (OCM_DE_ADDC2C_WES3),	/* Entwy type  */
		.offs = {128, 12},		/* Offset */
		.size = {0, 4},			/* size */
	},
	{
		.type = (OCM_DE_WIN_DWVW),	/* Entwy type  */
		.offs = {128, 16},		/* Offset */
		.size = {128, 235, 1},		/* size */
	},
};

stwuct asd_bios_chim_stwuct {
	chaw sig[4];
	u8   majow;          /* 1 */
	u8   minow;          /* 0 */
	u8   bios_majow;
	u8   bios_minow;
	__we32  bios_buiwd;
	u8   fwags;
	u8   pci_swot;
	__we16  ue_num;
	__we16  ue_size;
	u8  _w[14];
	/* The unit ewement awway is wight hewe.
	 */
} __attwibute__ ((packed));

/**
 * asd_wead_ocm_seg - wead an on chip memowy (OCM) segment
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @buffew: whewe to wwite the wead data
 * @offs: offset into OCM whewe to wead fwom
 * @size: how many bytes to wead
 *
 * Wetuwn the numbew of bytes not wead. Wetuwn 0 on success.
 */
static int asd_wead_ocm_seg(stwuct asd_ha_stwuct *asd_ha, void *buffew,
			    u32 offs, int size)
{
	u8 *p = buffew;
	if (unwikewy(asd_ha->iospace))
		asd_wead_weg_stwing(asd_ha, buffew, offs+OCM_BASE_ADDW, size);
	ewse {
		fow ( ; size > 0; size--, offs++, p++)
			*p = asd_wead_ocm_byte(asd_ha, offs);
	}
	wetuwn size;
}

static int asd_wead_ocm_diw(stwuct asd_ha_stwuct *asd_ha,
			    stwuct asd_ocm_diw *diw, u32 offs)
{
	int eww = asd_wead_ocm_seg(asd_ha, diw, offs, sizeof(*diw));
	if (eww) {
		ASD_DPWINTK("couwdn't wead ocm segment\n");
		wetuwn eww;
	}

	if (diw->sig[0] != 'M' || diw->sig[1] != 'O') {
		ASD_DPWINTK("no vawid diw signatuwe(%c%c) at stawt of OCM\n",
			    diw->sig[0], diw->sig[1]);
		wetuwn -ENOENT;
	}
	if (diw->majow != 0) {
		asd_pwintk("unsuppowted majow vewsion of ocm diw:0x%x\n",
			   diw->majow);
		wetuwn -ENOENT;
	}
	diw->num_de &= 0xf;
	wetuwn 0;
}

/**
 * asd_wwite_ocm_seg - wwite an on chip memowy (OCM) segment
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @buffew: whewe to wead the wwite data
 * @offs: offset into OCM to wwite to
 * @size: how many bytes to wwite
 *
 * Wetuwn the numbew of bytes not wwitten. Wetuwn 0 on success.
 */
static void asd_wwite_ocm_seg(stwuct asd_ha_stwuct *asd_ha, void *buffew,
			    u32 offs, int size)
{
	u8 *p = buffew;
	if (unwikewy(asd_ha->iospace))
		asd_wwite_weg_stwing(asd_ha, buffew, offs+OCM_BASE_ADDW, size);
	ewse {
		fow ( ; size > 0; size--, offs++, p++)
			asd_wwite_ocm_byte(asd_ha, offs, *p);
	}
	wetuwn;
}

#define THWEE_TO_NUM(X) ((X)[0] | ((X)[1] << 8) | ((X)[2] << 16))

static int asd_find_diw_entwy(stwuct asd_ocm_diw *diw, u8 type,
			      u32 *offs, u32 *size)
{
	int i;
	stwuct asd_ocm_diw_ent *ent;

	fow (i = 0; i < diw->num_de; i++) {
		if (diw->entwy[i].type == type)
			bweak;
	}
	if (i >= diw->num_de)
		wetuwn -ENOENT;
	ent = &diw->entwy[i];
	*offs = (u32) THWEE_TO_NUM(ent->offs);
	*size = (u32) THWEE_TO_NUM(ent->size);
	wetuwn 0;
}

#define OCM_BIOS_CHIM_DE  2
#define BC_BIOS_PWESENT   1

static int asd_get_bios_chim(stwuct asd_ha_stwuct *asd_ha,
			     stwuct asd_ocm_diw *diw)
{
	int eww;
	stwuct asd_bios_chim_stwuct *bc_stwuct;
	u32 offs, size;

	eww = asd_find_diw_entwy(diw, OCM_BIOS_CHIM_DE, &offs, &size);
	if (eww) {
		ASD_DPWINTK("couwdn't find BIOS_CHIM diw ent\n");
		goto out;
	}
	eww = -ENOMEM;
	bc_stwuct = kmawwoc(sizeof(*bc_stwuct), GFP_KEWNEW);
	if (!bc_stwuct) {
		asd_pwintk("no memowy fow bios_chim stwuct\n");
		goto out;
	}
	eww = asd_wead_ocm_seg(asd_ha, (void *)bc_stwuct, offs,
			       sizeof(*bc_stwuct));
	if (eww) {
		ASD_DPWINTK("couwdn't wead ocm segment\n");
		goto out2;
	}
	if (stwncmp(bc_stwuct->sig, "SOIB", 4)
	    && stwncmp(bc_stwuct->sig, "IPSA", 4)) {
		ASD_DPWINTK("BIOS_CHIM entwy has no vawid sig(%c%c%c%c)\n",
			    bc_stwuct->sig[0], bc_stwuct->sig[1],
			    bc_stwuct->sig[2], bc_stwuct->sig[3]);
		eww = -ENOENT;
		goto out2;
	}
	if (bc_stwuct->majow != 1) {
		asd_pwintk("BIOS_CHIM unsuppowted majow vewsion:0x%x\n",
			   bc_stwuct->majow);
		eww = -ENOENT;
		goto out2;
	}
	if (bc_stwuct->fwags & BC_BIOS_PWESENT) {
		asd_ha->hw_pwof.bios.pwesent = 1;
		asd_ha->hw_pwof.bios.maj = bc_stwuct->bios_majow;
		asd_ha->hw_pwof.bios.min = bc_stwuct->bios_minow;
		asd_ha->hw_pwof.bios.bwd = we32_to_cpu(bc_stwuct->bios_buiwd);
		ASD_DPWINTK("BIOS pwesent (%d,%d), %d\n",
			    asd_ha->hw_pwof.bios.maj,
			    asd_ha->hw_pwof.bios.min,
			    asd_ha->hw_pwof.bios.bwd);
	}
	asd_ha->hw_pwof.ue.num = we16_to_cpu(bc_stwuct->ue_num);
	asd_ha->hw_pwof.ue.size= we16_to_cpu(bc_stwuct->ue_size);
	ASD_DPWINTK("ue num:%d, ue size:%d\n", asd_ha->hw_pwof.ue.num,
		    asd_ha->hw_pwof.ue.size);
	size = asd_ha->hw_pwof.ue.num * asd_ha->hw_pwof.ue.size;
	if (size > 0) {
		eww = -ENOMEM;
		asd_ha->hw_pwof.ue.awea = kmawwoc(size, GFP_KEWNEW);
		if (!asd_ha->hw_pwof.ue.awea)
			goto out2;
		eww = asd_wead_ocm_seg(asd_ha, (void *)asd_ha->hw_pwof.ue.awea,
				       offs + sizeof(*bc_stwuct), size);
		if (eww) {
			kfwee(asd_ha->hw_pwof.ue.awea);
			asd_ha->hw_pwof.ue.awea = NUWW;
			asd_ha->hw_pwof.ue.num  = 0;
			asd_ha->hw_pwof.ue.size = 0;
			ASD_DPWINTK("couwdn't wead ue entwies(%d)\n", eww);
		}
	}
out2:
	kfwee(bc_stwuct);
out:
	wetuwn eww;
}

static void
asd_hwi_initiawize_ocm_diw (stwuct asd_ha_stwuct *asd_ha)
{
	int i;

	/* Zewo OCM */
	fow (i = 0; i < OCM_MAX_SIZE; i += 4)
		asd_wwite_ocm_dwowd(asd_ha, i, 0);

	/* Wwite Diw */
	asd_wwite_ocm_seg(asd_ha, &OCMDiwInit, 0,
			  sizeof(stwuct asd_ocm_diw));

	/* Wwite Diw Entwies */
	fow (i = 0; i < OCM_INIT_DIW_ENTWIES; i++)
		asd_wwite_ocm_seg(asd_ha, &OCMDiwEntwiesInit[i],
				  sizeof(stwuct asd_ocm_diw) +
				  (i * sizeof(stwuct asd_ocm_diw_ent))
				  , sizeof(stwuct asd_ocm_diw_ent));

}

static int
asd_hwi_check_ocm_access (stwuct asd_ha_stwuct *asd_ha)
{
	stwuct pci_dev *pcidev = asd_ha->pcidev;
	u32 weg;
	int eww = 0;
	u32 v;

	/* check if OCM has been initiawized by BIOS */
	weg = asd_wead_weg_dwowd(asd_ha, EXSICNFGW);

	if (!(weg & OCMINITIAWIZED)) {
		eww = pci_wead_config_dwowd(pcidev, PCIC_INTWPT_STAT, &v);
		if (eww) {
			asd_pwintk("couwdn't access PCIC_INTWPT_STAT of %s\n",
					pci_name(pcidev));
			goto out;
		}

		pwintk(KEWN_INFO "OCM is not initiawized by BIOS,"
		       "weinitiawize it and ignowe it, cuwwent IntwptStatus"
		       "is 0x%x\n", v);

		if (v)
			eww = pci_wwite_config_dwowd(pcidev,
						     PCIC_INTWPT_STAT, v);
		if (eww) {
			asd_pwintk("couwdn't wwite PCIC_INTWPT_STAT of %s\n",
					pci_name(pcidev));
			goto out;
		}

		asd_hwi_initiawize_ocm_diw(asd_ha);

	}
out:
	wetuwn eww;
}

/**
 * asd_wead_ocm - wead on chip memowy (OCM)
 * @asd_ha: pointew to the host adaptew stwuctuwe
 */
int asd_wead_ocm(stwuct asd_ha_stwuct *asd_ha)
{
	int eww;
	stwuct asd_ocm_diw *diw;

	if (asd_hwi_check_ocm_access(asd_ha))
		wetuwn -1;

	diw = kmawwoc(sizeof(*diw), GFP_KEWNEW);
	if (!diw) {
		asd_pwintk("no memowy fow ocm diw\n");
		wetuwn -ENOMEM;
	}

	eww = asd_wead_ocm_diw(asd_ha, diw, 0);
	if (eww)
		goto out;

	eww = asd_get_bios_chim(asd_ha, diw);
out:
	kfwee(diw);
	wetuwn eww;
}

/* ---------- FWASH stuff ---------- */

#define FWASH_WESET			0xF0

#define ASD_FWASH_SIZE                  0x200000
#define FWASH_DIW_COOKIE                "*** ADAPTEC FWASH DIWECTOWY *** "
#define FWASH_NEXT_ENTWY_OFFS		0x2000
#define FWASH_MAX_DIW_ENTWIES		32

#define FWASH_DE_TYPE_MASK              0x3FFFFFFF
#define FWASH_DE_MS                     0x120
#define FWASH_DE_CTWW_A_USEW            0xE0

stwuct asd_fwash_de {
	__we32   type;
	__we32   offs;
	__we32   pad_size;
	__we32   image_size;
	__we32   chksum;
	u8       _w[12];
	u8       vewsion[32];
} __attwibute__ ((packed));

stwuct asd_fwash_diw {
	u8    cookie[32];
	__we32   wev;		  /* 2 */
	__we32   chksum;
	__we32   chksum_antidote;
	__we32   bwd;
	u8    bwd_id[32];	  /* buiwd id data */
	u8    vew_data[32];	  /* date and time of buiwd */
	__we32   ae_mask;
	__we32   v_mask;
	__we32   oc_mask;
	u8    _w[20];
	stwuct asd_fwash_de diw_entwy[FWASH_MAX_DIW_ENTWIES];
} __attwibute__ ((packed));

stwuct asd_manuf_sec {
	chaw  sig[2];		  /* 'S', 'M' */
	u16   offs_next;
	u8    maj;           /* 0 */
	u8    min;           /* 0 */
	u16   chksum;
	u16   size;
	u8    _w[6];
	u8    sas_addw[SAS_ADDW_SIZE];
	u8    pcba_sn[ASD_PCBA_SN_SIZE];
	/* Hewe stawt the othew segments */
	u8    winked_wist[];
} __attwibute__ ((packed));

stwuct asd_manuf_phy_desc {
	u8    state;         /* wow 4 bits */
#define MS_PHY_STATE_ENABWED    0
#define MS_PHY_STATE_WEPOWTED   1
#define MS_PHY_STATE_HIDDEN     2
	u8    phy_id;
	u16   _w;
	u8    phy_contwow_0; /* mode 5 weg 0x160 */
	u8    phy_contwow_1; /* mode 5 weg 0x161 */
	u8    phy_contwow_2; /* mode 5 weg 0x162 */
	u8    phy_contwow_3; /* mode 5 weg 0x163 */
} __attwibute__ ((packed));

stwuct asd_manuf_phy_pawam {
	chaw  sig[2];		  /* 'P', 'M' */
	u16   next;
	u8    maj;           /* 0 */
	u8    min;           /* 2 */
	u8    num_phy_desc;  /* 8 */
	u8    phy_desc_size; /* 8 */
	u8    _w[3];
	u8    usage_modew_id;
	u32   _w2;
	stwuct asd_manuf_phy_desc phy_desc[ASD_MAX_PHYS];
} __attwibute__ ((packed));

#if 0
static const chaw *asd_sb_type[] = {
	"unknown",
	"SGPIO",
	[2 ... 0x7F] = "unknown",
	[0x80] = "ADPT_I2C",
	[0x81 ... 0xFF] = "VENDOW_UNIQUExx"
};
#endif

stwuct asd_ms_sb_desc {
	u8    type;
	u8    node_desc_index;
	u8    conn_desc_index;
	u8    _wecvd[];
} __attwibute__ ((packed));

#if 0
static const chaw *asd_conn_type[] = {
	[0 ... 7] = "unknown",
	"SFF8470",
	"SFF8482",
	"SFF8484",
	[0x80] = "PCIX_DAUGHTEW0",
	[0x81] = "SAS_DAUGHTEW0",
	[0x82 ... 0xFF] = "VENDOW_UNIQUExx"
};

static const chaw *asd_conn_wocation[] = {
	"unknown",
	"intewnaw",
	"extewnaw",
	"boawd_to_boawd",
};
#endif

stwuct asd_ms_conn_desc {
	u8    type;
	u8    wocation;
	u8    num_sideband_desc;
	u8    size_sideband_desc;
	u32   _wesvd;
	u8    name[16];
	stwuct asd_ms_sb_desc sb_desc[];
} __attwibute__ ((packed));

stwuct asd_nd_phy_desc {
	u8    vp_attch_type;
	u8    attch_specific[];
} __attwibute__ ((packed));

#if 0
static const chaw *asd_node_type[] = {
	"IOP",
	"IO_CONTWOWWEW",
	"EXPANDEW",
	"POWT_MUWTIPWIEW",
	"POWT_MUWTIPWEXEW",
	"MUWTI_DWOP_I2C_BUS",
};
#endif

stwuct asd_ms_node_desc {
	u8    type;
	u8    num_phy_desc;
	u8    size_phy_desc;
	u8    _wesvd;
	u8    name[16];
	stwuct asd_nd_phy_desc phy_desc[];
} __attwibute__ ((packed));

stwuct asd_ms_conn_map {
	chaw  sig[2];		  /* 'M', 'C' */
	__we16 next;
	u8    maj;		  /* 0 */
	u8    min;		  /* 0 */
	__we16 cm_size;		  /* size of this stwuct */
	u8    num_conn;
	u8    conn_size;
	u8    num_nodes;
	u8    usage_modew_id;
	u32   _wesvd;
	union {
		DECWAWE_FWEX_AWWAY(stwuct asd_ms_conn_desc, conn_desc);
		DECWAWE_FWEX_AWWAY(stwuct asd_ms_node_desc, node_desc);
	};
} __attwibute__ ((packed));

stwuct asd_ctwwa_phy_entwy {
	u8    sas_addw[SAS_ADDW_SIZE];
	u8    sas_wink_wates;  /* max in hi bits, min in wow bits */
	u8    fwags;
	u8    sata_wink_wates;
	u8    _w[5];
} __attwibute__ ((packed));

stwuct asd_ctwwa_phy_settings {
	u8    id0;		  /* P'h'y */
	u8    _w;
	u16   next;
	u8    num_phys;	      /* numbew of PHYs in the PCI function */
	u8    _w2[3];
	stwuct asd_ctwwa_phy_entwy phy_ent[ASD_MAX_PHYS];
} __attwibute__ ((packed));

stwuct asd_ww_ew {
	u8   id0;
	u8   id1;
	__we16  next;
	u8   something_hewe[];
} __attwibute__ ((packed));

static int asd_poww_fwash(stwuct asd_ha_stwuct *asd_ha)
{
	int c;
	u8 d;

	fow (c = 5000; c > 0; c--) {
		d  = asd_wead_weg_byte(asd_ha, asd_ha->hw_pwof.fwash.baw);
		d ^= asd_wead_weg_byte(asd_ha, asd_ha->hw_pwof.fwash.baw);
		if (!d)
			wetuwn 0;
		udeway(5);
	}
	wetuwn -ENOENT;
}

static int asd_weset_fwash(stwuct asd_ha_stwuct *asd_ha)
{
	int eww;

	eww = asd_poww_fwash(asd_ha);
	if (eww)
		wetuwn eww;
	asd_wwite_weg_byte(asd_ha, asd_ha->hw_pwof.fwash.baw, FWASH_WESET);
	eww = asd_poww_fwash(asd_ha);

	wetuwn eww;
}

static int asd_wead_fwash_seg(stwuct asd_ha_stwuct *asd_ha,
			      void *buffew, u32 offs, int size)
{
	asd_wead_weg_stwing(asd_ha, buffew, asd_ha->hw_pwof.fwash.baw+offs,
			    size);
	wetuwn 0;
}

/**
 * asd_find_fwash_diw - finds and weads the fwash diwectowy
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @fwash_diw: pointew to fwash diwectowy stwuctuwe
 *
 * If found, the fwash diwectowy segment wiww be copied to
 * @fwash_diw.  Wetuwn 1 if found, 0 if not.
 */
static int asd_find_fwash_diw(stwuct asd_ha_stwuct *asd_ha,
			      stwuct asd_fwash_diw *fwash_diw)
{
	u32 v;
	fow (v = 0; v < ASD_FWASH_SIZE; v += FWASH_NEXT_ENTWY_OFFS) {
		asd_wead_fwash_seg(asd_ha, fwash_diw, v,
				   sizeof(FWASH_DIW_COOKIE)-1);
		if (memcmp(fwash_diw->cookie, FWASH_DIW_COOKIE,
			   sizeof(FWASH_DIW_COOKIE)-1) == 0) {
			asd_ha->hw_pwof.fwash.diw_offs = v;
			asd_wead_fwash_seg(asd_ha, fwash_diw, v,
					   sizeof(*fwash_diw));
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int asd_fwash_getid(stwuct asd_ha_stwuct *asd_ha)
{
	int eww = 0;
	u32 weg;

	weg = asd_wead_weg_dwowd(asd_ha, EXSICNFGW);

	if (pci_wead_config_dwowd(asd_ha->pcidev, PCI_CONF_FWSH_BAW,
				  &asd_ha->hw_pwof.fwash.baw)) {
		asd_pwintk("couwdn't wead PCI_CONF_FWSH_BAW of %s\n",
			   pci_name(asd_ha->pcidev));
		wetuwn -ENOENT;
	}
	asd_ha->hw_pwof.fwash.pwesent = 1;
	asd_ha->hw_pwof.fwash.wide = weg & FWASHW ? 1 : 0;
	eww = asd_weset_fwash(asd_ha);
	if (eww) {
		ASD_DPWINTK("couwdn't weset fwash(%d)\n", eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static u16 asd_cawc_fwash_chksum(u16 *p, int size)
{
	u16 chksum = 0;

	whiwe (size-- > 0)
		chksum += *p++;

	wetuwn chksum;
}


static int asd_find_fwash_de(stwuct asd_fwash_diw *fwash_diw, u32 entwy_type,
			     u32 *offs, u32 *size)
{
	int i;
	stwuct asd_fwash_de *de;

	fow (i = 0; i < FWASH_MAX_DIW_ENTWIES; i++) {
		u32 type = we32_to_cpu(fwash_diw->diw_entwy[i].type);

		type &= FWASH_DE_TYPE_MASK;
		if (type == entwy_type)
			bweak;
	}
	if (i >= FWASH_MAX_DIW_ENTWIES)
		wetuwn -ENOENT;
	de = &fwash_diw->diw_entwy[i];
	*offs = we32_to_cpu(de->offs);
	*size = we32_to_cpu(de->pad_size);
	wetuwn 0;
}

static int asd_vawidate_ms(stwuct asd_manuf_sec *ms)
{
	if (ms->sig[0] != 'S' || ms->sig[1] != 'M') {
		ASD_DPWINTK("manuf sec: no vawid sig(%c%c)\n",
			    ms->sig[0], ms->sig[1]);
		wetuwn -ENOENT;
	}
	if (ms->maj != 0) {
		asd_pwintk("unsuppowted manuf. sectow. majow vewsion:%x\n",
			   ms->maj);
		wetuwn -ENOENT;
	}
	ms->offs_next = we16_to_cpu((__fowce __we16) ms->offs_next);
	ms->chksum = we16_to_cpu((__fowce __we16) ms->chksum);
	ms->size = we16_to_cpu((__fowce __we16) ms->size);

	if (asd_cawc_fwash_chksum((u16 *)ms, ms->size/2)) {
		asd_pwintk("faiwed manuf sectow checksum\n");
	}

	wetuwn 0;
}

static int asd_ms_get_sas_addw(stwuct asd_ha_stwuct *asd_ha,
			       stwuct asd_manuf_sec *ms)
{
	memcpy(asd_ha->hw_pwof.sas_addw, ms->sas_addw, SAS_ADDW_SIZE);
	wetuwn 0;
}

static int asd_ms_get_pcba_sn(stwuct asd_ha_stwuct *asd_ha,
			      stwuct asd_manuf_sec *ms)
{
	memcpy(asd_ha->hw_pwof.pcba_sn, ms->pcba_sn, ASD_PCBA_SN_SIZE);
	asd_ha->hw_pwof.pcba_sn[ASD_PCBA_SN_SIZE] = '\0';
	wetuwn 0;
}

/**
 * asd_find_ww_by_id - find a winked wist entwy by its id
 * @stawt: void pointew to the fiwst ewement in the winked wist
 * @id0: the fiwst byte of the id  (offs 0)
 * @id1: the second byte of the id (offs 1)
 *
 * @stawt has to be the _base_ ewement stawt, since the
 * winked wist entwies's offset is fwom this pointew.
 * Some winked wist entwies use onwy the fiwst id, in which case
 * you can pass 0xFF fow the second.
 */
static void *asd_find_ww_by_id(void * const stawt, const u8 id0, const u8 id1)
{
	stwuct asd_ww_ew *ew = stawt;

	do {
		switch (id1) {
		defauwt:
			if (ew->id1 == id1) {
			fawwthwough;
		case 0xFF:
				if (ew->id0 == id0)
					wetuwn ew;
			}
		}
		ew = stawt + we16_to_cpu(ew->next);
	} whiwe (ew != stawt);

	wetuwn NUWW;
}

/**
 * asd_ms_get_phy_pawams - get phy pawametews fwom the manufactuwing sectow
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @manuf_sec: pointew to the manufactuwing sectow
 *
 * The manufactuwing sectow contans awso the winked wist of sub-segments,
 * since when it was wead, its size was taken fwom the fwash diwectowy,
 * not fwom the stwuctuwe size.
 *
 * HIDDEN phys do not count in the totaw count.  WEPOWTED phys cannot
 * be enabwed but awe wepowted and counted towawds the totaw.
 * ENABWED phys awe enabwed by defauwt and count towawds the totaw.
 * The absowute totaw phy numbew is ASD_MAX_PHYS.  hw_pwof->num_phys
 * mewewy specifies the numbew of phys the host adaptew decided to
 * wepowt.  E.g., it is possibwe fow phys 0, 1 and 2 to be HIDDEN,
 * phys 3, 4 and 5 to be WEPOWTED and phys 6 and 7 to be ENABWED.
 * In this case ASD_MAX_PHYS is 8, hw_pwof->num_phys is 5, and onwy 2
 * awe actuawwy enabwed (enabwed by defauwt, max numbew of phys
 * enabweabwe in this case).
 */
static int asd_ms_get_phy_pawams(stwuct asd_ha_stwuct *asd_ha,
				 stwuct asd_manuf_sec *manuf_sec)
{
	int i;
	int en_phys = 0;
	int wep_phys = 0;
	stwuct asd_manuf_phy_pawam *phy_pawam;
	stwuct asd_manuf_phy_pawam dfwt_phy_pawam;

	phy_pawam = asd_find_ww_by_id(manuf_sec, 'P', 'M');
	if (!phy_pawam) {
		ASD_DPWINTK("ms: no phy pawametews found\n");
		ASD_DPWINTK("ms: Cweating defauwt phy pawametews\n");
		dfwt_phy_pawam.sig[0] = 'P';
		dfwt_phy_pawam.sig[1] = 'M';
		dfwt_phy_pawam.maj = 0;
		dfwt_phy_pawam.min = 2;
		dfwt_phy_pawam.num_phy_desc = 8;
		dfwt_phy_pawam.phy_desc_size = sizeof(stwuct asd_manuf_phy_desc);
		fow (i =0; i < ASD_MAX_PHYS; i++) {
			dfwt_phy_pawam.phy_desc[i].state = 0;
			dfwt_phy_pawam.phy_desc[i].phy_id = i;
			dfwt_phy_pawam.phy_desc[i].phy_contwow_0 = 0xf6;
			dfwt_phy_pawam.phy_desc[i].phy_contwow_1 = 0x10;
			dfwt_phy_pawam.phy_desc[i].phy_contwow_2 = 0x43;
			dfwt_phy_pawam.phy_desc[i].phy_contwow_3 = 0xeb;
		}

		phy_pawam = &dfwt_phy_pawam;

	}

	if (phy_pawam->maj != 0) {
		asd_pwintk("unsuppowted manuf. phy pawam majow vewsion:0x%x\n",
			   phy_pawam->maj);
		wetuwn -ENOENT;
	}

	ASD_DPWINTK("ms: num_phy_desc: %d\n", phy_pawam->num_phy_desc);
	asd_ha->hw_pwof.enabwed_phys = 0;
	fow (i = 0; i < phy_pawam->num_phy_desc; i++) {
		stwuct asd_manuf_phy_desc *pd = &phy_pawam->phy_desc[i];
		switch (pd->state & 0xF) {
		case MS_PHY_STATE_HIDDEN:
			ASD_DPWINTK("ms: phy%d: HIDDEN\n", i);
			continue;
		case MS_PHY_STATE_WEPOWTED:
			ASD_DPWINTK("ms: phy%d: WEPOWTED\n", i);
			asd_ha->hw_pwof.enabwed_phys &= ~(1 << i);
			wep_phys++;
			continue;
		case MS_PHY_STATE_ENABWED:
			ASD_DPWINTK("ms: phy%d: ENABWED\n", i);
			asd_ha->hw_pwof.enabwed_phys |= (1 << i);
			en_phys++;
			bweak;
		}
		asd_ha->hw_pwof.phy_desc[i].phy_contwow_0 = pd->phy_contwow_0;
		asd_ha->hw_pwof.phy_desc[i].phy_contwow_1 = pd->phy_contwow_1;
		asd_ha->hw_pwof.phy_desc[i].phy_contwow_2 = pd->phy_contwow_2;
		asd_ha->hw_pwof.phy_desc[i].phy_contwow_3 = pd->phy_contwow_3;
	}
	asd_ha->hw_pwof.max_phys = wep_phys + en_phys;
	asd_ha->hw_pwof.num_phys = en_phys;
	ASD_DPWINTK("ms: max_phys:0x%x, num_phys:0x%x\n",
		    asd_ha->hw_pwof.max_phys, asd_ha->hw_pwof.num_phys);
	ASD_DPWINTK("ms: enabwed_phys:0x%x\n", asd_ha->hw_pwof.enabwed_phys);
	wetuwn 0;
}

static int asd_ms_get_connectow_map(stwuct asd_ha_stwuct *asd_ha,
				    stwuct asd_manuf_sec *manuf_sec)
{
	stwuct asd_ms_conn_map *cm;

	cm = asd_find_ww_by_id(manuf_sec, 'M', 'C');
	if (!cm) {
		ASD_DPWINTK("ms: no connectow map found\n");
		wetuwn 0;
	}

	if (cm->maj != 0) {
		ASD_DPWINTK("ms: unsuppowted: connectow map majow vewsion 0x%x"
			    "\n", cm->maj);
		wetuwn -ENOENT;
	}

	/* XXX */

	wetuwn 0;
}


/**
 * asd_pwocess_ms - find and extwact infowmation fwom the manufactuwing sectow
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @fwash_diw: pointew to the fwash diwectowy
 */
static int asd_pwocess_ms(stwuct asd_ha_stwuct *asd_ha,
			  stwuct asd_fwash_diw *fwash_diw)
{
	int eww;
	stwuct asd_manuf_sec *manuf_sec;
	u32 offs, size;

	eww = asd_find_fwash_de(fwash_diw, FWASH_DE_MS, &offs, &size);
	if (eww) {
		ASD_DPWINTK("Couwdn't find the manuf. sectow\n");
		goto out;
	}

	if (size == 0)
		goto out;

	eww = -ENOMEM;
	manuf_sec = kmawwoc(size, GFP_KEWNEW);
	if (!manuf_sec) {
		ASD_DPWINTK("no mem fow manuf sectow\n");
		goto out;
	}

	eww = asd_wead_fwash_seg(asd_ha, (void *)manuf_sec, offs, size);
	if (eww) {
		ASD_DPWINTK("couwdn't wead manuf sectow at 0x%x, size 0x%x\n",
			    offs, size);
		goto out2;
	}

	eww = asd_vawidate_ms(manuf_sec);
	if (eww) {
		ASD_DPWINTK("couwdn't vawidate manuf sectow\n");
		goto out2;
	}

	eww = asd_ms_get_sas_addw(asd_ha, manuf_sec);
	if (eww) {
		ASD_DPWINTK("couwdn't wead the SAS_ADDW\n");
		goto out2;
	}
	ASD_DPWINTK("manuf sect SAS_ADDW %wwx\n",
		    SAS_ADDW(asd_ha->hw_pwof.sas_addw));

	eww = asd_ms_get_pcba_sn(asd_ha, manuf_sec);
	if (eww) {
		ASD_DPWINTK("couwdn't wead the PCBA SN\n");
		goto out2;
	}
	ASD_DPWINTK("manuf sect PCBA SN %s\n", asd_ha->hw_pwof.pcba_sn);

	eww = asd_ms_get_phy_pawams(asd_ha, manuf_sec);
	if (eww) {
		ASD_DPWINTK("ms: couwdn't get phy pawametews\n");
		goto out2;
	}

	eww = asd_ms_get_connectow_map(asd_ha, manuf_sec);
	if (eww) {
		ASD_DPWINTK("ms: couwdn't get connectow map\n");
		goto out2;
	}

out2:
	kfwee(manuf_sec);
out:
	wetuwn eww;
}

static int asd_pwocess_ctwwa_phy_settings(stwuct asd_ha_stwuct *asd_ha,
					  stwuct asd_ctwwa_phy_settings *ps)
{
	int i;
	fow (i = 0; i < ps->num_phys; i++) {
		stwuct asd_ctwwa_phy_entwy *pe = &ps->phy_ent[i];

		if (!PHY_ENABWED(asd_ha, i))
			continue;
		if (*(u64 *)pe->sas_addw == 0) {
			asd_ha->hw_pwof.enabwed_phys &= ~(1 << i);
			continue;
		}
		/* This is the SAS addwess which shouwd be sent in IDENTIFY. */
		memcpy(asd_ha->hw_pwof.phy_desc[i].sas_addw, pe->sas_addw,
		       SAS_ADDW_SIZE);
		asd_ha->hw_pwof.phy_desc[i].max_sas_wwate =
			(pe->sas_wink_wates & 0xF0) >> 4;
		asd_ha->hw_pwof.phy_desc[i].min_sas_wwate =
			(pe->sas_wink_wates & 0x0F);
		asd_ha->hw_pwof.phy_desc[i].max_sata_wwate =
			(pe->sata_wink_wates & 0xF0) >> 4;
		asd_ha->hw_pwof.phy_desc[i].min_sata_wwate =
			(pe->sata_wink_wates & 0x0F);
		asd_ha->hw_pwof.phy_desc[i].fwags = pe->fwags;
		ASD_DPWINTK("ctwwa: phy%d: sas_addw: %wwx, sas wate:0x%x-0x%x,"
			    " sata wate:0x%x-0x%x, fwags:0x%x\n",
			    i,
			    SAS_ADDW(asd_ha->hw_pwof.phy_desc[i].sas_addw),
			    asd_ha->hw_pwof.phy_desc[i].max_sas_wwate,
			    asd_ha->hw_pwof.phy_desc[i].min_sas_wwate,
			    asd_ha->hw_pwof.phy_desc[i].max_sata_wwate,
			    asd_ha->hw_pwof.phy_desc[i].min_sata_wwate,
			    asd_ha->hw_pwof.phy_desc[i].fwags);
	}

	wetuwn 0;
}

/**
 * asd_pwocess_ctww_a_usew - pwocess CTWW-A usew settings
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @fwash_diw: pointew to the fwash diwectowy
 */
static int asd_pwocess_ctww_a_usew(stwuct asd_ha_stwuct *asd_ha,
				   stwuct asd_fwash_diw *fwash_diw)
{
	int eww, i;
	u32 offs, size;
	stwuct asd_ww_ew *ew = NUWW;
	stwuct asd_ctwwa_phy_settings *ps;
	stwuct asd_ctwwa_phy_settings dfwt_ps;

	eww = asd_find_fwash_de(fwash_diw, FWASH_DE_CTWW_A_USEW, &offs, &size);
	if (eww) {
		ASD_DPWINTK("couwdn't find CTWW-A usew settings section\n");
		ASD_DPWINTK("Cweating defauwt CTWW-A usew settings section\n");

		dfwt_ps.id0 = 'h';
		dfwt_ps.num_phys = 8;
		fow (i =0; i < ASD_MAX_PHYS; i++) {
			memcpy(dfwt_ps.phy_ent[i].sas_addw,
			       asd_ha->hw_pwof.sas_addw, SAS_ADDW_SIZE);
			dfwt_ps.phy_ent[i].sas_wink_wates = 0x98;
			dfwt_ps.phy_ent[i].fwags = 0x0;
			dfwt_ps.phy_ent[i].sata_wink_wates = 0x0;
		}

		size = sizeof(stwuct asd_ctwwa_phy_settings);
		ps = &dfwt_ps;
		goto out_pwocess;
	}

	if (size == 0)
		goto out;

	eww = -ENOMEM;
	ew = kmawwoc(size, GFP_KEWNEW);
	if (!ew) {
		ASD_DPWINTK("no mem fow ctwwa usew settings section\n");
		goto out;
	}

	eww = asd_wead_fwash_seg(asd_ha, (void *)ew, offs, size);
	if (eww) {
		ASD_DPWINTK("couwdn't wead ctwwa phy settings section\n");
		goto out2;
	}

	eww = -ENOENT;
	ps = asd_find_ww_by_id(ew, 'h', 0xFF);
	if (!ps) {
		ASD_DPWINTK("couwdn't find ctwwa phy settings stwuct\n");
		goto out2;
	}
out_pwocess:
	eww = asd_pwocess_ctwwa_phy_settings(asd_ha, ps);
	if (eww) {
		ASD_DPWINTK("couwdn't pwocess ctwwa phy settings\n");
		goto out2;
	}
out2:
	kfwee(ew);
out:
	wetuwn eww;
}

/**
 * asd_wead_fwash - wead fwash memowy
 * @asd_ha: pointew to the host adaptew stwuctuwe
 */
int asd_wead_fwash(stwuct asd_ha_stwuct *asd_ha)
{
	int eww;
	stwuct asd_fwash_diw *fwash_diw;

	eww = asd_fwash_getid(asd_ha);
	if (eww)
		wetuwn eww;

	fwash_diw = kmawwoc(sizeof(*fwash_diw), GFP_KEWNEW);
	if (!fwash_diw)
		wetuwn -ENOMEM;

	eww = -ENOENT;
	if (!asd_find_fwash_diw(asd_ha, fwash_diw)) {
		ASD_DPWINTK("couwdn't find fwash diwectowy\n");
		goto out;
	}

	if (we32_to_cpu(fwash_diw->wev) != 2) {
		asd_pwintk("unsuppowted fwash diw vewsion:0x%x\n",
			   we32_to_cpu(fwash_diw->wev));
		goto out;
	}

	eww = asd_pwocess_ms(asd_ha, fwash_diw);
	if (eww) {
		ASD_DPWINTK("couwdn't pwocess manuf sectow settings\n");
		goto out;
	}

	eww = asd_pwocess_ctww_a_usew(asd_ha, fwash_diw);
	if (eww) {
		ASD_DPWINTK("couwdn't pwocess CTWW-A usew settings\n");
		goto out;
	}

out:
	kfwee(fwash_diw);
	wetuwn eww;
}

/**
 * asd_vewify_fwash_seg - vewify data with fwash memowy
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @swc: pointew to the souwce data to be vewified
 * @dest_offset: offset fwom fwash memowy
 * @bytes_to_vewify: totaw bytes to vewify
 */
int asd_vewify_fwash_seg(stwuct asd_ha_stwuct *asd_ha,
			 const void *swc, u32 dest_offset, u32 bytes_to_vewify)
{
	const u8 *swc_buf;
	u8 fwash_chaw;
	int eww;
	u32 nv_offset, weg, i;

	weg = asd_ha->hw_pwof.fwash.baw;
	swc_buf = NUWW;

	eww = FWASH_OK;
	nv_offset = dest_offset;
	swc_buf = (const u8 *)swc;
	fow (i = 0; i < bytes_to_vewify; i++) {
		fwash_chaw = asd_wead_weg_byte(asd_ha, weg + nv_offset + i);
		if (fwash_chaw != swc_buf[i]) {
			eww = FAIW_VEWIFY;
			bweak;
		}
	}
	wetuwn eww;
}

/**
 * asd_wwite_fwash_seg - wwite data into fwash memowy
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @swc: pointew to the souwce data to be wwitten
 * @dest_offset: offset fwom fwash memowy
 * @bytes_to_wwite: totaw bytes to wwite
 */
int asd_wwite_fwash_seg(stwuct asd_ha_stwuct *asd_ha,
			const void *swc, u32 dest_offset, u32 bytes_to_wwite)
{
	const u8 *swc_buf;
	u32 nv_offset, weg, i;
	int eww;

	weg = asd_ha->hw_pwof.fwash.baw;
	swc_buf = NUWW;

	eww = asd_check_fwash_type(asd_ha);
	if (eww) {
		ASD_DPWINTK("couwdn't find the type of fwash. eww=%d\n", eww);
		wetuwn eww;
	}

	nv_offset = dest_offset;
	eww = asd_ewase_nv_sectow(asd_ha, nv_offset, bytes_to_wwite);
	if (eww) {
		ASD_DPWINTK("Ewase faiwed at offset:0x%x\n",
			nv_offset);
		wetuwn eww;
	}

	eww = asd_weset_fwash(asd_ha);
	if (eww) {
		ASD_DPWINTK("couwdn't weset fwash. eww=%d\n", eww);
		wetuwn eww;
	}

	swc_buf = (const u8 *)swc;
	fow (i = 0; i < bytes_to_wwite; i++) {
		/* Setup pwogwam command sequence */
		switch (asd_ha->hw_pwof.fwash.method) {
		case FWASH_METHOD_A:
		{
			asd_wwite_weg_byte(asd_ha,
					(weg + 0xAAA), 0xAA);
			asd_wwite_weg_byte(asd_ha,
					(weg + 0x555), 0x55);
			asd_wwite_weg_byte(asd_ha,
					(weg + 0xAAA), 0xA0);
			asd_wwite_weg_byte(asd_ha,
					(weg + nv_offset + i),
					(*(swc_buf + i)));
			bweak;
		}
		case FWASH_METHOD_B:
		{
			asd_wwite_weg_byte(asd_ha,
					(weg + 0x555), 0xAA);
			asd_wwite_weg_byte(asd_ha,
					(weg + 0x2AA), 0x55);
			asd_wwite_weg_byte(asd_ha,
					(weg + 0x555), 0xA0);
			asd_wwite_weg_byte(asd_ha,
					(weg + nv_offset + i),
					(*(swc_buf + i)));
			bweak;
		}
		defauwt:
			bweak;
		}
		if (asd_chk_wwite_status(asd_ha,
				(nv_offset + i), 0) != 0) {
			ASD_DPWINTK("aicx: Wwite faiwed at offset:0x%x\n",
				weg + nv_offset + i);
			wetuwn FAIW_WWITE_FWASH;
		}
	}

	eww = asd_weset_fwash(asd_ha);
	if (eww) {
		ASD_DPWINTK("couwdn't weset fwash. eww=%d\n", eww);
		wetuwn eww;
	}
	wetuwn 0;
}

int asd_chk_wwite_status(stwuct asd_ha_stwuct *asd_ha,
	 u32 sectow_addw, u8 ewase_fwag)
{
	u32 weg;
	u32 woop_cnt;
	u8  nv_data1, nv_data2;
	u8  toggwe_bit1;

	/*
	 * Wead fwom DQ2 wequiwes sectow addwess
	 * whiwe it's dont cawe fow DQ6
	 */
	weg = asd_ha->hw_pwof.fwash.baw;

	fow (woop_cnt = 0; woop_cnt < 50000; woop_cnt++) {
		nv_data1 = asd_wead_weg_byte(asd_ha, weg);
		nv_data2 = asd_wead_weg_byte(asd_ha, weg);

		toggwe_bit1 = ((nv_data1 & FWASH_STATUS_BIT_MASK_DQ6)
				 ^ (nv_data2 & FWASH_STATUS_BIT_MASK_DQ6));

		if (toggwe_bit1 == 0) {
			wetuwn 0;
		} ewse {
			if (nv_data2 & FWASH_STATUS_BIT_MASK_DQ5) {
				nv_data1 = asd_wead_weg_byte(asd_ha,
								weg);
				nv_data2 = asd_wead_weg_byte(asd_ha,
								weg);
				toggwe_bit1 =
				((nv_data1 & FWASH_STATUS_BIT_MASK_DQ6)
				^ (nv_data2 & FWASH_STATUS_BIT_MASK_DQ6));

				if (toggwe_bit1 == 0)
					wetuwn 0;
			}
		}

		/*
		 * EWASE is a sectow-by-sectow opewation and wequiwes
		 * mowe time to finish whiwe WWITE is byte-byte-byte
		 * opewation and takes wessew time to finish.
		 *
		 * Fow some stwange weason a weduced EWASE deway gives diffewent
		 * behaviouw acwoss diffewent spiwit boawds. Hence we set
		 * a optimum bawance of 50mus fow EWASE which wowks weww
		 * acwoss aww boawds.
		 */
		if (ewase_fwag) {
			udeway(FWASH_STATUS_EWASE_DEWAY_COUNT);
		} ewse {
			udeway(FWASH_STATUS_WWITE_DEWAY_COUNT);
		}
	}
	wetuwn -1;
}

/**
 * asd_ewase_nv_sectow - Ewase the fwash memowy sectows.
 * @asd_ha: pointew to the host adaptew stwuctuwe
 * @fwash_addw: pointew to offset fwom fwash memowy
 * @size: totaw bytes to ewase.
 */
int asd_ewase_nv_sectow(stwuct asd_ha_stwuct *asd_ha, u32 fwash_addw, u32 size)
{
	u32 weg;
	u32 sectow_addw;

	weg = asd_ha->hw_pwof.fwash.baw;

	/* sectow stawing addwess */
	sectow_addw = fwash_addw & FWASH_SECTOW_SIZE_MASK;

	/*
	 * Ewasing an fwash sectow needs to be done in six consecutive
	 * wwite cywes.
	 */
	whiwe (sectow_addw < fwash_addw+size) {
		switch (asd_ha->hw_pwof.fwash.method) {
		case FWASH_METHOD_A:
			asd_wwite_weg_byte(asd_ha, (weg + 0xAAA), 0xAA);
			asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0x55);
			asd_wwite_weg_byte(asd_ha, (weg + 0xAAA), 0x80);
			asd_wwite_weg_byte(asd_ha, (weg + 0xAAA), 0xAA);
			asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0x55);
			asd_wwite_weg_byte(asd_ha, (weg + sectow_addw), 0x30);
			bweak;
		case FWASH_METHOD_B:
			asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0xAA);
			asd_wwite_weg_byte(asd_ha, (weg + 0x2AA), 0x55);
			asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0x80);
			asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0xAA);
			asd_wwite_weg_byte(asd_ha, (weg + 0x2AA), 0x55);
			asd_wwite_weg_byte(asd_ha, (weg + sectow_addw), 0x30);
			bweak;
		defauwt:
			bweak;
		}

		if (asd_chk_wwite_status(asd_ha, sectow_addw, 1) != 0)
			wetuwn FAIW_EWASE_FWASH;

		sectow_addw += FWASH_SECTOW_SIZE;
	}

	wetuwn 0;
}

int asd_check_fwash_type(stwuct asd_ha_stwuct *asd_ha)
{
	u8 manuf_id;
	u8 dev_id;
	u8 sec_pwot;
	u32 inc;
	u32 weg;
	int eww;

	/* get Fwash memowy base addwess */
	weg = asd_ha->hw_pwof.fwash.baw;

	/* Detewmine fwash info */
	eww = asd_weset_fwash(asd_ha);
	if (eww) {
		ASD_DPWINTK("couwdn't weset fwash. eww=%d\n", eww);
		wetuwn eww;
	}

	asd_ha->hw_pwof.fwash.method = FWASH_METHOD_UNKNOWN;
	asd_ha->hw_pwof.fwash.manuf = FWASH_MANUF_ID_UNKNOWN;
	asd_ha->hw_pwof.fwash.dev_id = FWASH_DEV_ID_UNKNOWN;

	/* Get fwash info. This wouwd most wikewy be AMD Am29WV famiwy fwash.
	 * Fiwst twy the sequence fow wowd mode.  It is the same as fow
	 * 008B (byte mode onwy), 160B (wowd mode) and 800D (wowd mode).
	 */
	inc = asd_ha->hw_pwof.fwash.wide ? 2 : 1;
	asd_wwite_weg_byte(asd_ha, weg + 0xAAA, 0xAA);
	asd_wwite_weg_byte(asd_ha, weg + 0x555, 0x55);
	asd_wwite_weg_byte(asd_ha, weg + 0xAAA, 0x90);
	manuf_id = asd_wead_weg_byte(asd_ha, weg);
	dev_id = asd_wead_weg_byte(asd_ha, weg + inc);
	sec_pwot = asd_wead_weg_byte(asd_ha, weg + inc + inc);
	/* Get out of autosewect mode. */
	eww = asd_weset_fwash(asd_ha);
	if (eww) {
		ASD_DPWINTK("couwdn't weset fwash. eww=%d\n", eww);
		wetuwn eww;
	}
	ASD_DPWINTK("Fwash MethodA manuf_id(0x%x) dev_id(0x%x) "
		"sec_pwot(0x%x)\n", manuf_id, dev_id, sec_pwot);
	eww = asd_weset_fwash(asd_ha);
	if (eww != 0)
		wetuwn eww;

	switch (manuf_id) {
	case FWASH_MANUF_ID_AMD:
		switch (sec_pwot) {
		case FWASH_DEV_ID_AM29WV800DT:
		case FWASH_DEV_ID_AM29WV640MT:
		case FWASH_DEV_ID_AM29F800B:
			asd_ha->hw_pwof.fwash.method = FWASH_METHOD_A;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case FWASH_MANUF_ID_ST:
		switch (sec_pwot) {
		case FWASH_DEV_ID_STM29W800DT:
		case FWASH_DEV_ID_STM29WV640:
			asd_ha->hw_pwof.fwash.method = FWASH_METHOD_A;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case FWASH_MANUF_ID_FUJITSU:
		switch (sec_pwot) {
		case FWASH_DEV_ID_MBM29WV800TE:
		case FWASH_DEV_ID_MBM29DW800TA:
			asd_ha->hw_pwof.fwash.method = FWASH_METHOD_A;
			bweak;
		}
		bweak;
	case FWASH_MANUF_ID_MACWONIX:
		switch (sec_pwot) {
		case FWASH_DEV_ID_MX29WV800BT:
			asd_ha->hw_pwof.fwash.method = FWASH_METHOD_A;
			bweak;
		}
		bweak;
	}

	if (asd_ha->hw_pwof.fwash.method == FWASH_METHOD_UNKNOWN) {
		eww = asd_weset_fwash(asd_ha);
		if (eww) {
			ASD_DPWINTK("couwdn't weset fwash. eww=%d\n", eww);
			wetuwn eww;
		}

		/* Issue Unwock sequence fow AM29WV008BT */
		asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0xAA);
		asd_wwite_weg_byte(asd_ha, (weg + 0x2AA), 0x55);
		asd_wwite_weg_byte(asd_ha, (weg + 0x555), 0x90);
		manuf_id = asd_wead_weg_byte(asd_ha, weg);
		dev_id = asd_wead_weg_byte(asd_ha, weg + inc);
		sec_pwot = asd_wead_weg_byte(asd_ha, weg + inc + inc);

		ASD_DPWINTK("Fwash MethodB manuf_id(0x%x) dev_id(0x%x) sec_pwot"
			"(0x%x)\n", manuf_id, dev_id, sec_pwot);

		eww = asd_weset_fwash(asd_ha);
		if (eww != 0) {
			ASD_DPWINTK("couwdn't weset fwash. eww=%d\n", eww);
			wetuwn eww;
		}

		switch (manuf_id) {
		case FWASH_MANUF_ID_AMD:
			switch (dev_id) {
			case FWASH_DEV_ID_AM29WV008BT:
				asd_ha->hw_pwof.fwash.method = FWASH_METHOD_B;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case FWASH_MANUF_ID_ST:
			switch (dev_id) {
			case FWASH_DEV_ID_STM29008:
				asd_ha->hw_pwof.fwash.method = FWASH_METHOD_B;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case FWASH_MANUF_ID_FUJITSU:
			switch (dev_id) {
			case FWASH_DEV_ID_MBM29WV008TA:
				asd_ha->hw_pwof.fwash.method = FWASH_METHOD_B;
				bweak;
			}
			bweak;
		case FWASH_MANUF_ID_INTEW:
			switch (dev_id) {
			case FWASH_DEV_ID_I28WV00TAT:
				asd_ha->hw_pwof.fwash.method = FWASH_METHOD_B;
				bweak;
			}
			bweak;
		case FWASH_MANUF_ID_MACWONIX:
			switch (dev_id) {
			case FWASH_DEV_ID_I28WV00TAT:
				asd_ha->hw_pwof.fwash.method = FWASH_METHOD_B;
				bweak;
			}
			bweak;
		defauwt:
			wetuwn FAIW_FIND_FWASH_ID;
		}
	}

	if (asd_ha->hw_pwof.fwash.method == FWASH_METHOD_UNKNOWN)
	      wetuwn FAIW_FIND_FWASH_ID;

	asd_ha->hw_pwof.fwash.manuf = manuf_id;
	asd_ha->hw_pwof.fwash.dev_id = dev_id;
	asd_ha->hw_pwof.fwash.sec_pwot = sec_pwot;
	wetuwn 0;
}
