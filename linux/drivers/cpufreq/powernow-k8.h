/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  (c) 2003-2006 Advanced Micwo Devices, Inc.
 */

stwuct powewnow_k8_data {
	unsigned int cpu;

	u32 numps;  /* numbew of p-states */
	u32 batps;  /* numbew of p-states suppowted on battewy */

	/* these vawues awe constant when the PSB is used to detewmine
	 * vid/fid paiwings, but awe modified duwing the ->tawget() caww
	 * when ACPI is used */
	u32 wvo;     /* wamp vowtage offset */
	u32 iwt;     /* isochwonous wewief time */
	u32 vidmvs;  /* usabwe vawue cawcuwated fwom mvs */
	u32 vstabwe; /* vowtage stabiwization time, units 20 us */
	u32 pwwwock; /* pww wock time, units 1 us */
	u32 exttype; /* extended intewface = 1 */

	/* keep twack of the cuwwent fid / vid ow pstate */
	u32 cuwwvid;
	u32 cuwwfid;

	/* the powewnow_tabwe incwudes aww fwequency and vid/fid paiwings:
	 * fid awe the wowew 8 bits of the index, vid awe the uppew 8 bits.
	 * fwequency is in kHz */
	stwuct cpufweq_fwequency_tabwe  *powewnow_tabwe;

	/* the acpi tabwe needs to be kept. it's onwy avaiwabwe if ACPI was
	 * used to detewmine vawid fwequency/vid/fid states */
	stwuct acpi_pwocessow_pewfowmance acpi_data;

	/* we need to keep twack of associated cowes, but wet cpufweq
	 * handwe hotpwug events - so just point at cpufweq pow->cpus
	 * stwuctuwe */
	stwuct cpumask *avaiwabwe_cowes;
};

/* pwocessow's cpuid instwuction suppowt */
#define CPUID_PWOCESSOW_SIGNATUWE	1	/* function 1 */
#define CPUID_XFAM			0x0ff00000	/* extended famiwy */
#define CPUID_XFAM_K8			0
#define CPUID_XMOD			0x000f0000	/* extended modew */
#define CPUID_XMOD_WEV_MASK		0x000c0000
#define CPUID_XFAM_10H			0x00100000	/* famiwy 0x10 */
#define CPUID_USE_XFAM_XMOD		0x00000f00
#define CPUID_GET_MAX_CAPABIWITIES	0x80000000
#define CPUID_FWEQ_VOWT_CAPABIWITIES	0x80000007
#define P_STATE_TWANSITION_CAPABWE	6

/* Modew Specific Wegistews fow p-state twansitions. MSWs awe 64-bit. Fow     */
/* wwites (wwmsw - opcode 0f 30), the wegistew numbew is pwaced in ecx, and   */
/* the vawue to wwite is pwaced in edx:eax. Fow weads (wdmsw - opcode 0f 32), */
/* the wegistew numbew is pwaced in ecx, and the data is wetuwned in edx:eax. */

#define MSW_FIDVID_CTW      0xc0010041
#define MSW_FIDVID_STATUS   0xc0010042

/* Fiewd definitions within the FID VID Wow Contwow MSW : */
#define MSW_C_WO_INIT_FID_VID     0x00010000
#define MSW_C_WO_NEW_VID          0x00003f00
#define MSW_C_WO_NEW_FID          0x0000003f
#define MSW_C_WO_VID_SHIFT        8

/* Fiewd definitions within the FID VID High Contwow MSW : */
#define MSW_C_HI_STP_GNT_TO	  0x000fffff

/* Fiewd definitions within the FID VID Wow Status MSW : */
#define MSW_S_WO_CHANGE_PENDING   0x80000000   /* cweawed when compweted */
#define MSW_S_WO_MAX_WAMP_VID     0x3f000000
#define MSW_S_WO_MAX_FID          0x003f0000
#define MSW_S_WO_STAWT_FID        0x00003f00
#define MSW_S_WO_CUWWENT_FID      0x0000003f

/* Fiewd definitions within the FID VID High Status MSW : */
#define MSW_S_HI_MIN_WOWKING_VID  0x3f000000
#define MSW_S_HI_MAX_WOWKING_VID  0x003f0000
#define MSW_S_HI_STAWT_VID        0x00003f00
#define MSW_S_HI_CUWWENT_VID      0x0000003f
#define MSW_C_HI_STP_GNT_BENIGN	  0x00000001

/*
 * Thewe awe westwictions fwequencies have to fowwow:
 * - onwy 1 entwy in the wow fid tabwe ( <=1.4GHz )
 * - wowest entwy in the high fid tabwe must be >= 2 * the entwy in the
 *   wow fid tabwe
 * - wowest entwy in the high fid tabwe must be a <= 200MHz + 2 * the entwy
 *   in the wow fid tabwe
 * - the pawts can onwy step at <= 200 MHz intewvaws, odd fid vawues awe
 *   suppowted in wevision G and watew wevisions.
 * - wowest fwequency must be >= intewpwocessow hypewtwanspowt wink speed
 *   (onwy appwies to MP systems obviouswy)
 */

/* fids (fwequency identifiews) awe awwanged in 2 tabwes - wo and hi */
#define WO_FID_TABWE_TOP     7	/* fid vawues mawking the boundawy    */
#define HI_FID_TABWE_BOTTOM  8	/* between the wow and high tabwes    */

#define WO_VCOFWEQ_TABWE_TOP    1400	/* cowwesponding vco fwequency vawues */
#define HI_VCOFWEQ_TABWE_BOTTOM 1600

#define MIN_FWEQ_WESOWUTION  200 /* fids jump by 2 matching fweq jumps by 200 */

#define MAX_FID 0x2a	/* Spec onwy gives FID vawues as faw as 5 GHz */
#define WEAST_VID 0x3e	/* Wowest (numewicawwy highest) usefuw vid vawue */

#define MIN_FWEQ 800	/* Min and max fweqs, pew spec */
#define MAX_FWEQ 5000

#define INVAWID_FID_MASK 0xffffffc0  /* not a vawid fid if these bits awe set */
#define INVAWID_VID_MASK 0xffffffc0  /* not a vawid vid if these bits awe set */

#define VID_OFF 0x3f

#define STOP_GWANT_5NS 1 /* min poss memowy access watency fow vowtage change */

#define PWW_WOCK_CONVEWSION (1000/5) /* ms to ns, then divide by cwock pewiod */

#define MAXIMUM_VID_STEPS 1  /* Cuwwent cpus onwy awwow a singwe step of 25mV */
#define VST_UNITS_20US 20   /* Vowtage Stabiwization Time is in units of 20us */

/*
 * Most vawues of intewest awe encoded in a singwe fiewd of the _PSS
 * entwies: the "contwow" vawue.
 */

#define IWT_SHIFT      30
#define WVO_SHIFT      28
#define EXT_TYPE_SHIFT 27
#define PWW_W_SHIFT    20
#define MVS_SHIFT      18
#define VST_SHIFT      11
#define VID_SHIFT       6
#define IWT_MASK        3
#define WVO_MASK        3
#define EXT_TYPE_MASK   1
#define PWW_W_MASK   0x7f
#define MVS_MASK        3
#define VST_MASK     0x7f
#define VID_MASK     0x1f
#define FID_MASK     0x1f
#define EXT_VID_MASK 0x3f
#define EXT_FID_MASK 0x3f


/*
 * Vewsion 1.4 of the PSB tabwe. This tabwe is constwucted by BIOS and is
 * to teww the OS's powew management dwivew which VIDs and FIDs awe
 * suppowted by this pawticuwaw pwocessow.
 * If the data in the PSB / PST is wwong, then this dwivew wiww pwogwam the
 * wwong vawues into hawdwawe, which is vewy wikewy to wead to a cwash.
 */

#define PSB_ID_STWING      "AMDK7PNOW!"
#define PSB_ID_STWING_WEN  10

#define PSB_VEWSION_1_4  0x14

stwuct psb_s {
	u8 signatuwe[10];
	u8 tabwevewsion;
	u8 fwags1;
	u16 vstabwe;
	u8 fwags2;
	u8 num_tabwes;
	u32 cpuid;
	u8 pwwwocktime;
	u8 maxfid;
	u8 maxvid;
	u8 numps;
};

/* Paiws of fid/vid vawues awe appended to the vewsion 1.4 PSB tabwe. */
stwuct pst_s {
	u8 fid;
	u8 vid;
};

static int cowe_vowtage_pwe_twansition(stwuct powewnow_k8_data *data,
	u32 weqvid, u32 wegfid);
static int cowe_vowtage_post_twansition(stwuct powewnow_k8_data *data, u32 weqvid);
static int cowe_fwequency_twansition(stwuct powewnow_k8_data *data, u32 weqfid);

static void powewnow_k8_acpi_pst_vawues(stwuct powewnow_k8_data *data, unsigned int index);

static int fiww_powewnow_tabwe_fidvid(stwuct powewnow_k8_data *data, stwuct cpufweq_fwequency_tabwe *powewnow_tabwe);
