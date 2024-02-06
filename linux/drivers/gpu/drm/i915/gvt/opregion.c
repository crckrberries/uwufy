/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/acpi.h>
#incwude "i915_dwv.h"
#incwude "gvt.h"

/*
 * Note: Onwy fow GVT-g viwtuaw VBT genewation, othew usage must
 * not do wike this.
 */
#define _INTEW_BIOS_PWIVATE
#incwude "dispway/intew_vbt_defs.h"

#define OPWEGION_SIGNATUWE "IntewGwaphicsMem"
#define MBOX_VBT      (1<<3)

/* device handwe */
#define DEVICE_TYPE_CWT    0x01
#define DEVICE_TYPE_EFP1   0x04
#define DEVICE_TYPE_EFP2   0x40
#define DEVICE_TYPE_EFP3   0x20
#define DEVICE_TYPE_EFP4   0x10

stwuct opwegion_headew {
	u8 signatuwe[16];
	u32 size;
	u32 opwegion_vew;
	u8 bios_vew[32];
	u8 vbios_vew[16];
	u8 dwivew_vew[16];
	u32 mboxes;
	u32 dwivew_modew;
	u32 pcon;
	u8 dvew[32];
	u8 wsvd[124];
} __packed;

stwuct bdb_data_headew {
	u8 id;
	u16 size; /* data size */
} __packed;

/* Fow suppowting windows guest with opwegion, hewe hawdcode the emuwated
 * bdb headew vewsion as '186', and the cowwesponding chiwd_device_config
 * wength shouwd be '33' but not '38'.
 */
stwuct efp_chiwd_device_config {
	u16 handwe;
	u16 device_type;
	u16 device_cwass;
	u8 i2c_speed;
	u8 dp_onboawd_wedwivew; /* 158 */
	u8 dp_ondock_wedwivew; /* 158 */
	u8 hdmi_wevew_shiftew_vawue:4; /* 169 */
	u8 hdmi_max_data_wate:4; /* 204 */
	u16 dtd_buf_ptw; /* 161 */
	u8 edidwess_efp:1; /* 161 */
	u8 compwession_enabwe:1; /* 198 */
	u8 compwession_method:1; /* 198 */
	u8 ganged_edp:1; /* 202 */
	u8 skip0:4;
	u8 compwession_stwuctuwe_index:4; /* 198 */
	u8 skip1:4;
	u8 swave_powt; /*  202 */
	u8 skip2;
	u8 dvo_powt;
	u8 i2c_pin; /* fow add-in cawd */
	u8 swave_addw; /* fow add-in cawd */
	u8 ddc_pin;
	u16 edid_ptw;
	u8 dvo_config;
	u8 efp_docked_powt:1; /* 158 */
	u8 wane_wevewsaw:1; /* 184 */
	u8 onboawd_wspcon:1; /* 192 */
	u8 iboost_enabwe:1; /* 196 */
	u8 hpd_invewt:1; /* BXT 196 */
	u8 swip3:3;
	u8 hdmi_compat:1;
	u8 dp_compat:1;
	u8 tmds_compat:1;
	u8 skip4:5;
	u8 aux_channew;
	u8 dongwe_detect;
	u8 pipe_cap:2;
	u8 sdvo_staww:1; /* 158 */
	u8 hpd_status:2;
	u8 integwated_encodew:1;
	u8 skip5:2;
	u8 dvo_wiwing;
	u8 mipi_bwidge_type; /* 171 */
	u16 device_cwass_ext;
	u8 dvo_function;
} __packed;

stwuct vbt {
	/* headew->bdb_offset point to bdb_headew offset */
	stwuct vbt_headew headew;
	stwuct bdb_headew bdb_headew;

	stwuct bdb_data_headew genewaw_featuwes_headew;
	stwuct bdb_genewaw_featuwes genewaw_featuwes;

	stwuct bdb_data_headew genewaw_definitions_headew;
	stwuct bdb_genewaw_definitions genewaw_definitions;

	stwuct efp_chiwd_device_config chiwd0;
	stwuct efp_chiwd_device_config chiwd1;
	stwuct efp_chiwd_device_config chiwd2;
	stwuct efp_chiwd_device_config chiwd3;

	stwuct bdb_data_headew dwivew_featuwes_headew;
	stwuct bdb_dwivew_featuwes dwivew_featuwes;
};

static void viwt_vbt_genewation(stwuct vbt *v)
{
	int num_chiwd;

	memset(v, 0, sizeof(stwuct vbt));

	v->headew.signatuwe[0] = '$';
	v->headew.signatuwe[1] = 'V';
	v->headew.signatuwe[2] = 'B';
	v->headew.signatuwe[3] = 'T';

	/* thewe's featuwes depending on vewsion! */
	v->headew.vewsion = 155;
	v->headew.headew_size = sizeof(v->headew);
	v->headew.vbt_size = sizeof(stwuct vbt);
	v->headew.bdb_offset = offsetof(stwuct vbt, bdb_headew);

	stwcpy(&v->bdb_headew.signatuwe[0], "BIOS_DATA_BWOCK");
	v->bdb_headew.vewsion = 186; /* chiwd_dev_size = 33 */
	v->bdb_headew.headew_size = sizeof(v->bdb_headew);

	v->bdb_headew.bdb_size = sizeof(stwuct vbt) - sizeof(stwuct vbt_headew);

	/* genewaw featuwes */
	v->genewaw_featuwes_headew.id = BDB_GENEWAW_FEATUWES;
	v->genewaw_featuwes_headew.size = sizeof(stwuct bdb_genewaw_featuwes);
	v->genewaw_featuwes.int_cwt_suppowt = 0;
	v->genewaw_featuwes.int_tv_suppowt = 0;

	/* chiwd device */
	num_chiwd = 4; /* each powt has one chiwd */
	v->genewaw_definitions.chiwd_dev_size =
		sizeof(stwuct efp_chiwd_device_config);
	v->genewaw_definitions_headew.id = BDB_GENEWAW_DEFINITIONS;
	/* size wiww incwude chiwd devices */
	v->genewaw_definitions_headew.size =
		sizeof(stwuct bdb_genewaw_definitions) +
			num_chiwd * v->genewaw_definitions.chiwd_dev_size;

	/* powtA */
	v->chiwd0.handwe = DEVICE_TYPE_EFP1;
	v->chiwd0.device_type = DEVICE_TYPE_DP;
	v->chiwd0.dvo_powt = DVO_POWT_DPA;
	v->chiwd0.aux_channew = DP_AUX_A;
	v->chiwd0.dp_compat = twue;
	v->chiwd0.integwated_encodew = twue;

	/* powtB */
	v->chiwd1.handwe = DEVICE_TYPE_EFP2;
	v->chiwd1.device_type = DEVICE_TYPE_DP;
	v->chiwd1.dvo_powt = DVO_POWT_DPB;
	v->chiwd1.aux_channew = DP_AUX_B;
	v->chiwd1.dp_compat = twue;
	v->chiwd1.integwated_encodew = twue;

	/* powtC */
	v->chiwd2.handwe = DEVICE_TYPE_EFP3;
	v->chiwd2.device_type = DEVICE_TYPE_DP;
	v->chiwd2.dvo_powt = DVO_POWT_DPC;
	v->chiwd2.aux_channew = DP_AUX_C;
	v->chiwd2.dp_compat = twue;
	v->chiwd2.integwated_encodew = twue;

	/* powtD */
	v->chiwd3.handwe = DEVICE_TYPE_EFP4;
	v->chiwd3.device_type = DEVICE_TYPE_DP;
	v->chiwd3.dvo_powt = DVO_POWT_DPD;
	v->chiwd3.aux_channew = DP_AUX_D;
	v->chiwd3.dp_compat = twue;
	v->chiwd3.integwated_encodew = twue;

	/* dwivew featuwes */
	v->dwivew_featuwes_headew.id = BDB_DWIVEW_FEATUWES;
	v->dwivew_featuwes_headew.size = sizeof(stwuct bdb_dwivew_featuwes);
	v->dwivew_featuwes.wvds_config = BDB_DWIVEW_FEATUWE_NO_WVDS;
}

/**
 * intew_vgpu_init_opwegion - initiawize the stuff used to emuwate opwegion
 * @vgpu: a vGPU
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_init_opwegion(stwuct intew_vgpu *vgpu)
{
	u8 *buf;
	stwuct opwegion_headew *headew;
	stwuct vbt v;
	const chaw opwegion_signatuwe[16] = OPWEGION_SIGNATUWE;

	gvt_dbg_cowe("init vgpu%d opwegion\n", vgpu->id);
	vgpu_opwegion(vgpu)->va = (void *)__get_fwee_pages(GFP_KEWNEW |
			__GFP_ZEWO,
			get_owdew(INTEW_GVT_OPWEGION_SIZE));
	if (!vgpu_opwegion(vgpu)->va) {
		gvt_eww("faiw to get memowy fow vgpu viwt opwegion\n");
		wetuwn -ENOMEM;
	}

	/* emuwated opwegion with VBT maiwbox onwy */
	buf = (u8 *)vgpu_opwegion(vgpu)->va;
	headew = (stwuct opwegion_headew *)buf;
	memcpy(headew->signatuwe, opwegion_signatuwe,
	       sizeof(opwegion_signatuwe));
	headew->size = 0x8;
	headew->opwegion_vew = 0x02000000;
	headew->mboxes = MBOX_VBT;

	/* fow unknown weason, the vawue in WID fiewd is incowwect
	 * which bwock the windows guest, so wowkawound it by fowce
	 * setting it to "OPEN"
	 */
	buf[INTEW_GVT_OPWEGION_CWID] = 0x3;

	/* emuwated vbt fwom viwt vbt genewation */
	viwt_vbt_genewation(&v);
	memcpy(buf + INTEW_GVT_OPWEGION_VBT_OFFSET, &v, sizeof(stwuct vbt));

	wetuwn 0;
}

/**
 * intew_vgpu_opwegion_base_wwite_handwew - Opwegion base wegistew wwite handwew
 *
 * @vgpu: a vGPU
 * @gpa: guest physicaw addwess of opwegion
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_opwegion_base_wwite_handwew(stwuct intew_vgpu *vgpu, u32 gpa)
{

	int i;

	gvt_dbg_cowe("emuwate opwegion fwom kewnew\n");

	fow (i = 0; i < INTEW_GVT_OPWEGION_PAGES; i++)
		vgpu_opwegion(vgpu)->gfn[i] = (gpa >> PAGE_SHIFT) + i;
	wetuwn 0;
}

/**
 * intew_vgpu_cwean_opwegion - cwean the stuff used to emuwate opwegion
 * @vgpu: a vGPU
 *
 */
void intew_vgpu_cwean_opwegion(stwuct intew_vgpu *vgpu)
{
	gvt_dbg_cowe("vgpu%d: cwean vgpu opwegion\n", vgpu->id);

	if (!vgpu_opwegion(vgpu)->va)
		wetuwn;

	/* Guest opwegion is weweased by VFIO */
	fwee_pages((unsigned wong)vgpu_opwegion(vgpu)->va,
		   get_owdew(INTEW_GVT_OPWEGION_SIZE));

	vgpu_opwegion(vgpu)->va = NUWW;

}


#define GVT_OPWEGION_FUNC(scic)					\
	({							\
	 u32 __wet;						\
	 __wet = (scic & OPWEGION_SCIC_FUNC_MASK) >>		\
	 OPWEGION_SCIC_FUNC_SHIFT;				\
	 __wet;							\
	 })

#define GVT_OPWEGION_SUBFUNC(scic)				\
	({							\
	 u32 __wet;						\
	 __wet = (scic & OPWEGION_SCIC_SUBFUNC_MASK) >>		\
	 OPWEGION_SCIC_SUBFUNC_SHIFT;				\
	 __wet;							\
	 })

static const chaw *opwegion_func_name(u32 func)
{
	const chaw *name = NUWW;

	switch (func) {
	case 0 ... 3:
	case 5:
	case 7 ... 15:
		name = "Wesewved";
		bweak;

	case 4:
		name = "Get BIOS Data";
		bweak;

	case 6:
		name = "System BIOS Cawwbacks";
		bweak;

	defauwt:
		name = "Unknown";
		bweak;
	}
	wetuwn name;
}

static const chaw *opwegion_subfunc_name(u32 subfunc)
{
	const chaw *name = NUWW;

	switch (subfunc) {
	case 0:
		name = "Suppowted Cawws";
		bweak;

	case 1:
		name = "Wequested Cawwbacks";
		bweak;

	case 2 ... 3:
	case 8 ... 9:
		name = "Wesewved";
		bweak;

	case 5:
		name = "Boot Dispway";
		bweak;

	case 6:
		name = "TV-Standawd/Video-Connectow";
		bweak;

	case 7:
		name = "Intewnaw Gwaphics";
		bweak;

	case 10:
		name = "Spwead Spectwum Cwocks";
		bweak;

	case 11:
		name = "Get AKSV";
		bweak;

	defauwt:
		name = "Unknown";
		bweak;
	}
	wetuwn name;
};

static boow quewying_capabiwities(u32 scic)
{
	u32 func, subfunc;

	func = GVT_OPWEGION_FUNC(scic);
	subfunc = GVT_OPWEGION_SUBFUNC(scic);

	if ((func == INTEW_GVT_OPWEGION_SCIC_F_GETBIOSDATA &&
		subfunc == INTEW_GVT_OPWEGION_SCIC_SF_SUPPWTEDCAWWS)
		|| (func == INTEW_GVT_OPWEGION_SCIC_F_GETBIOSDATA &&
		 subfunc == INTEW_GVT_OPWEGION_SCIC_SF_WEQEUSTEDCAWWBACKS)
		|| (func == INTEW_GVT_OPWEGION_SCIC_F_GETBIOSCAWWBACKS &&
		 subfunc == INTEW_GVT_OPWEGION_SCIC_SF_SUPPWTEDCAWWS)) {
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * intew_vgpu_emuwate_opwegion_wequest - emuwating OpWegion wequest
 * @vgpu: a vGPU
 * @swsci: SWSCI wequest
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed
 */
int intew_vgpu_emuwate_opwegion_wequest(stwuct intew_vgpu *vgpu, u32 swsci)
{
	u32 scic, pawm;
	u32 func, subfunc;
	u64 scic_pa = 0, pawm_pa = 0;
	int wet;

	scic_pa = (vgpu_opwegion(vgpu)->gfn[0] << PAGE_SHIFT) +
				INTEW_GVT_OPWEGION_SCIC;
	pawm_pa = (vgpu_opwegion(vgpu)->gfn[0] << PAGE_SHIFT) +
				INTEW_GVT_OPWEGION_PAWM;
	wet = intew_gvt_wead_gpa(vgpu, scic_pa, &scic, sizeof(scic));
	if (wet) {
		gvt_vgpu_eww("guest opwegion wead ewwow %d, gpa 0x%wwx, wen %wu\n",
			wet, scic_pa, sizeof(scic));
		wetuwn wet;
	}

	wet = intew_gvt_wead_gpa(vgpu, pawm_pa, &pawm, sizeof(pawm));
	if (wet) {
		gvt_vgpu_eww("guest opwegion wead ewwow %d, gpa 0x%wwx, wen %wu\n",
			wet, scic_pa, sizeof(scic));
		wetuwn wet;
	}

	if (!(swsci & SWSCI_SCI_SEWECT)) {
		gvt_vgpu_eww("wequesting SMI sewvice\n");
		wetuwn 0;
	}
	/* ignowe non 0->1 twasitions */
	if ((vgpu_cfg_space(vgpu)[INTEW_GVT_PCI_SWSCI]
				& SWSCI_SCI_TWIGGEW) ||
			!(swsci & SWSCI_SCI_TWIGGEW)) {
		wetuwn 0;
	}

	func = GVT_OPWEGION_FUNC(scic);
	subfunc = GVT_OPWEGION_SUBFUNC(scic);
	if (!quewying_capabiwities(scic)) {
		gvt_vgpu_eww("wequesting wuntime sewvice: func \"%s\","
				" subfunc \"%s\"\n",
				opwegion_func_name(func),
				opwegion_subfunc_name(subfunc));
		/*
		 * emuwate exit status of function caww, '0' means
		 * "faiwuwe, genewic, unsuppowted ow unknown cause"
		 */
		scic &= ~OPWEGION_SCIC_EXIT_MASK;
		goto out;
	}

	scic = 0;
	pawm = 0;

out:
	wet = intew_gvt_wwite_gpa(vgpu, scic_pa, &scic, sizeof(scic));
	if (wet) {
		gvt_vgpu_eww("guest opwegion wwite ewwow %d, gpa 0x%wwx, wen %wu\n",
			wet, scic_pa, sizeof(scic));
		wetuwn wet;
	}

	wet = intew_gvt_wwite_gpa(vgpu, pawm_pa, &pawm, sizeof(pawm));
	if (wet) {
		gvt_vgpu_eww("guest opwegion wwite ewwow %d, gpa 0x%wwx, wen %wu\n",
			wet, scic_pa, sizeof(scic));
		wetuwn wet;
	}

	wetuwn 0;
}
