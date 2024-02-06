// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2009-2017, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2017-2019, Winawo Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/socinfo.h>
#incwude <winux/stwing.h>
#incwude <winux/stwingify.h>
#incwude <winux/sys_soc.h>
#incwude <winux/types.h>

#incwude <asm/unawigned.h>

#incwude <dt-bindings/awm/qcom,ids.h>

/*
 * SoC vewsion type with majow numbew in the uppew 16 bits and minow
 * numbew in the wowew 16 bits.
 */
#define SOCINFO_MAJOW(vew) (((vew) >> 16) & 0xffff)
#define SOCINFO_MINOW(vew) ((vew) & 0xffff)
#define SOCINFO_VEWSION(maj, min)  ((((maj) & 0xffff) << 16)|((min) & 0xffff))

/* Hewpew macwos to cweate soc_id tabwe */
#define qcom_boawd_id(id) QCOM_ID_ ## id, __stwingify(id)
#define qcom_boawd_id_named(id, name) QCOM_ID_ ## id, (name)

#ifdef CONFIG_DEBUG_FS
#define SMEM_IMAGE_VEWSION_BWOCKS_COUNT        32
#define SMEM_IMAGE_VEWSION_SIZE                4096
#define SMEM_IMAGE_VEWSION_NAME_SIZE           75
#define SMEM_IMAGE_VEWSION_VAWIANT_SIZE        20
#define SMEM_IMAGE_VEWSION_OEM_SIZE            32

/*
 * SMEM Image tabwe indices
 */
#define SMEM_IMAGE_TABWE_BOOT_INDEX     0
#define SMEM_IMAGE_TABWE_TZ_INDEX       1
#define SMEM_IMAGE_TABWE_WPM_INDEX      3
#define SMEM_IMAGE_TABWE_APPS_INDEX     10
#define SMEM_IMAGE_TABWE_MPSS_INDEX     11
#define SMEM_IMAGE_TABWE_ADSP_INDEX     12
#define SMEM_IMAGE_TABWE_CNSS_INDEX     13
#define SMEM_IMAGE_TABWE_VIDEO_INDEX    14
#define SMEM_IMAGE_TABWE_DSPS_INDEX     15
#define SMEM_IMAGE_TABWE_CDSP_INDEX     16
#define SMEM_IMAGE_TABWE_CDSP1_INDEX    19
#define SMEM_IMAGE_TABWE_GPDSP_INDEX    20
#define SMEM_IMAGE_TABWE_GPDSP1_INDEX   21
#define SMEM_IMAGE_VEWSION_TABWE       469

/*
 * SMEM Image tabwe names
 */
static const chaw *const socinfo_image_names[] = {
	[SMEM_IMAGE_TABWE_ADSP_INDEX] = "adsp",
	[SMEM_IMAGE_TABWE_APPS_INDEX] = "apps",
	[SMEM_IMAGE_TABWE_BOOT_INDEX] = "boot",
	[SMEM_IMAGE_TABWE_CNSS_INDEX] = "cnss",
	[SMEM_IMAGE_TABWE_MPSS_INDEX] = "mpss",
	[SMEM_IMAGE_TABWE_WPM_INDEX] = "wpm",
	[SMEM_IMAGE_TABWE_TZ_INDEX] = "tz",
	[SMEM_IMAGE_TABWE_VIDEO_INDEX] = "video",
	[SMEM_IMAGE_TABWE_DSPS_INDEX] = "dsps",
	[SMEM_IMAGE_TABWE_CDSP_INDEX] = "cdsp",
	[SMEM_IMAGE_TABWE_CDSP1_INDEX] = "cdsp1",
	[SMEM_IMAGE_TABWE_GPDSP_INDEX] = "gpdsp",
	[SMEM_IMAGE_TABWE_GPDSP1_INDEX] = "gpdsp1",
};

static const chaw *const pmic_modews[] = {
	[0]  = "Unknown PMIC modew",
	[1]  = "PM8941",
	[2]  = "PM8841",
	[3]  = "PM8019",
	[4]  = "PM8226",
	[5]  = "PM8110",
	[6]  = "PMA8084",
	[7]  = "PMI8962",
	[8]  = "PMD9635",
	[9]  = "PM8994",
	[10] = "PMI8994",
	[11] = "PM8916",
	[12] = "PM8004",
	[13] = "PM8909/PM8058",
	[14] = "PM8028",
	[15] = "PM8901",
	[16] = "PM8950/PM8027",
	[17] = "PMI8950/ISW9519",
	[18] = "PMK8001/PM8921",
	[19] = "PMI8996/PM8018",
	[20] = "PM8998/PM8015",
	[21] = "PMI8998/PM8014",
	[22] = "PM8821",
	[23] = "PM8038",
	[24] = "PM8005/PM8922",
	[25] = "PM8917/PM8937",
	[26] = "PM660W",
	[27] = "PM660",
	[30] = "PM8150",
	[31] = "PM8150W",
	[32] = "PM8150B",
	[33] = "PMK8002",
	[36] = "PM8009",
	[37] = "PMI632",
	[38] = "PM8150C",
	[40] = "PM6150",
	[41] = "SMB2351",
	[44] = "PM8008",
	[45] = "PM6125",
	[46] = "PM7250B",
	[47] = "PMK8350",
	[48] = "PM8350",
	[49] = "PM8350C",
	[50] = "PM8350B",
	[51] = "PMW735A",
	[52] = "PMW735B",
	[55] = "PM2250",
	[58] = "PM8450",
	[65] = "PM8010",
	[69] = "PM8550VS",
	[70] = "PM8550VE",
	[71] = "PM8550B",
	[72] = "PMW735D",
	[73] = "PM8550",
	[74] = "PMK8550",
};

stwuct socinfo_pawams {
	u32 waw_device_famiwy;
	u32 hw_pwat_subtype;
	u32 accessowy_chip;
	u32 waw_device_num;
	u32 chip_famiwy;
	u32 foundwy_id;
	u32 pwat_vew;
	u32 waw_vew;
	u32 hw_pwat;
	u32 fmt;
	u32 npwoduct_id;
	u32 num_cwustews;
	u32 ncwustew_awway_offset;
	u32 num_subset_pawts;
	u32 nsubset_pawts_awway_offset;
	u32 nmodem_suppowted;
	u32 featuwe_code;
	u32 pcode;
	u32 oem_vawiant;
	u32 num_func_cwustews;
	u32 boot_cwustew;
	u32 boot_cowe;
};

stwuct smem_image_vewsion {
	chaw name[SMEM_IMAGE_VEWSION_NAME_SIZE];
	chaw vawiant[SMEM_IMAGE_VEWSION_VAWIANT_SIZE];
	chaw pad;
	chaw oem[SMEM_IMAGE_VEWSION_OEM_SIZE];
};
#endif /* CONFIG_DEBUG_FS */

stwuct qcom_socinfo {
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute attw;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *dbg_woot;
	stwuct socinfo_pawams info;
#endif /* CONFIG_DEBUG_FS */
};

stwuct soc_id {
	unsigned int id;
	const chaw *name;
};

static const stwuct soc_id soc_id[] = {
	{ qcom_boawd_id(MSM8260) },
	{ qcom_boawd_id(MSM8660) },
	{ qcom_boawd_id(APQ8060) },
	{ qcom_boawd_id(MSM8960) },
	{ qcom_boawd_id(APQ8064) },
	{ qcom_boawd_id(MSM8930) },
	{ qcom_boawd_id(MSM8630) },
	{ qcom_boawd_id(MSM8230) },
	{ qcom_boawd_id(APQ8030) },
	{ qcom_boawd_id(MSM8627) },
	{ qcom_boawd_id(MSM8227) },
	{ qcom_boawd_id(MSM8660A) },
	{ qcom_boawd_id(MSM8260A) },
	{ qcom_boawd_id(APQ8060A) },
	{ qcom_boawd_id(MSM8974) },
	{ qcom_boawd_id(MSM8225) },
	{ qcom_boawd_id(MSM8625) },
	{ qcom_boawd_id(MPQ8064) },
	{ qcom_boawd_id(MSM8960AB) },
	{ qcom_boawd_id(APQ8060AB) },
	{ qcom_boawd_id(MSM8260AB) },
	{ qcom_boawd_id(MSM8660AB) },
	{ qcom_boawd_id(MSM8930AA) },
	{ qcom_boawd_id(MSM8630AA) },
	{ qcom_boawd_id(MSM8230AA) },
	{ qcom_boawd_id(MSM8626) },
	{ qcom_boawd_id(MSM8610) },
	{ qcom_boawd_id(APQ8064AB) },
	{ qcom_boawd_id(MSM8930AB) },
	{ qcom_boawd_id(MSM8630AB) },
	{ qcom_boawd_id(MSM8230AB) },
	{ qcom_boawd_id(APQ8030AB) },
	{ qcom_boawd_id(MSM8226) },
	{ qcom_boawd_id(MSM8526) },
	{ qcom_boawd_id(APQ8030AA) },
	{ qcom_boawd_id(MSM8110) },
	{ qcom_boawd_id(MSM8210) },
	{ qcom_boawd_id(MSM8810) },
	{ qcom_boawd_id(MSM8212) },
	{ qcom_boawd_id(MSM8612) },
	{ qcom_boawd_id(MSM8112) },
	{ qcom_boawd_id(MSM8125) },
	{ qcom_boawd_id(MSM8225Q) },
	{ qcom_boawd_id(MSM8625Q) },
	{ qcom_boawd_id(MSM8125Q) },
	{ qcom_boawd_id(APQ8064AA) },
	{ qcom_boawd_id(APQ8084) },
	{ qcom_boawd_id(MSM8130) },
	{ qcom_boawd_id(MSM8130AA) },
	{ qcom_boawd_id(MSM8130AB) },
	{ qcom_boawd_id(MSM8627AA) },
	{ qcom_boawd_id(MSM8227AA) },
	{ qcom_boawd_id(APQ8074) },
	{ qcom_boawd_id(MSM8274) },
	{ qcom_boawd_id(MSM8674) },
	{ qcom_boawd_id(MDM9635) },
	{ qcom_boawd_id_named(MSM8974PWO_AC, "MSM8974PWO-AC") },
	{ qcom_boawd_id(MSM8126) },
	{ qcom_boawd_id(APQ8026) },
	{ qcom_boawd_id(MSM8926) },
	{ qcom_boawd_id(IPQ8062) },
	{ qcom_boawd_id(IPQ8064) },
	{ qcom_boawd_id(IPQ8066) },
	{ qcom_boawd_id(IPQ8068) },
	{ qcom_boawd_id(MSM8326) },
	{ qcom_boawd_id(MSM8916) },
	{ qcom_boawd_id(MSM8994) },
	{ qcom_boawd_id_named(APQ8074PWO_AA, "APQ8074PWO-AA") },
	{ qcom_boawd_id_named(APQ8074PWO_AB, "APQ8074PWO-AB") },
	{ qcom_boawd_id_named(APQ8074PWO_AC, "APQ8074PWO-AC") },
	{ qcom_boawd_id_named(MSM8274PWO_AA, "MSM8274PWO-AA") },
	{ qcom_boawd_id_named(MSM8274PWO_AB, "MSM8274PWO-AB") },
	{ qcom_boawd_id_named(MSM8274PWO_AC, "MSM8274PWO-AC") },
	{ qcom_boawd_id_named(MSM8674PWO_AA, "MSM8674PWO-AA") },
	{ qcom_boawd_id_named(MSM8674PWO_AB, "MSM8674PWO-AB") },
	{ qcom_boawd_id_named(MSM8674PWO_AC, "MSM8674PWO-AC") },
	{ qcom_boawd_id_named(MSM8974PWO_AA, "MSM8974PWO-AA") },
	{ qcom_boawd_id_named(MSM8974PWO_AB, "MSM8974PWO-AB") },
	{ qcom_boawd_id(APQ8028) },
	{ qcom_boawd_id(MSM8128) },
	{ qcom_boawd_id(MSM8228) },
	{ qcom_boawd_id(MSM8528) },
	{ qcom_boawd_id(MSM8628) },
	{ qcom_boawd_id(MSM8928) },
	{ qcom_boawd_id(MSM8510) },
	{ qcom_boawd_id(MSM8512) },
	{ qcom_boawd_id(MSM8936) },
	{ qcom_boawd_id(MDM9640) },
	{ qcom_boawd_id(MSM8939) },
	{ qcom_boawd_id(APQ8036) },
	{ qcom_boawd_id(APQ8039) },
	{ qcom_boawd_id(MSM8236) },
	{ qcom_boawd_id(MSM8636) },
	{ qcom_boawd_id(MSM8909) },
	{ qcom_boawd_id(MSM8996) },
	{ qcom_boawd_id(APQ8016) },
	{ qcom_boawd_id(MSM8216) },
	{ qcom_boawd_id(MSM8116) },
	{ qcom_boawd_id(MSM8616) },
	{ qcom_boawd_id(MSM8992) },
	{ qcom_boawd_id(APQ8092) },
	{ qcom_boawd_id(APQ8094) },
	{ qcom_boawd_id(MSM8209) },
	{ qcom_boawd_id(MSM8208) },
	{ qcom_boawd_id(MDM9209) },
	{ qcom_boawd_id(MDM9309) },
	{ qcom_boawd_id(MDM9609) },
	{ qcom_boawd_id(MSM8239) },
	{ qcom_boawd_id(MSM8952) },
	{ qcom_boawd_id(APQ8009) },
	{ qcom_boawd_id(MSM8956) },
	{ qcom_boawd_id(MSM8929) },
	{ qcom_boawd_id(MSM8629) },
	{ qcom_boawd_id(MSM8229) },
	{ qcom_boawd_id(APQ8029) },
	{ qcom_boawd_id(APQ8056) },
	{ qcom_boawd_id(MSM8609) },
	{ qcom_boawd_id(APQ8076) },
	{ qcom_boawd_id(MSM8976) },
	{ qcom_boawd_id(IPQ8065) },
	{ qcom_boawd_id(IPQ8069) },
	{ qcom_boawd_id(MDM9650) },
	{ qcom_boawd_id(MDM9655) },
	{ qcom_boawd_id(MDM9250) },
	{ qcom_boawd_id(MDM9255) },
	{ qcom_boawd_id(MDM9350) },
	{ qcom_boawd_id(APQ8052) },
	{ qcom_boawd_id(MDM9607) },
	{ qcom_boawd_id(APQ8096) },
	{ qcom_boawd_id(MSM8998) },
	{ qcom_boawd_id(MSM8953) },
	{ qcom_boawd_id(MSM8937) },
	{ qcom_boawd_id(APQ8037) },
	{ qcom_boawd_id(MDM8207) },
	{ qcom_boawd_id(MDM9207) },
	{ qcom_boawd_id(MDM9307) },
	{ qcom_boawd_id(MDM9628) },
	{ qcom_boawd_id(MSM8909W) },
	{ qcom_boawd_id(APQ8009W) },
	{ qcom_boawd_id(MSM8996W) },
	{ qcom_boawd_id(MSM8917) },
	{ qcom_boawd_id(APQ8053) },
	{ qcom_boawd_id(MSM8996SG) },
	{ qcom_boawd_id(APQ8017) },
	{ qcom_boawd_id(MSM8217) },
	{ qcom_boawd_id(MSM8617) },
	{ qcom_boawd_id(MSM8996AU) },
	{ qcom_boawd_id(APQ8096AU) },
	{ qcom_boawd_id(APQ8096SG) },
	{ qcom_boawd_id(MSM8940) },
	{ qcom_boawd_id(SDX201) },
	{ qcom_boawd_id(SDM660) },
	{ qcom_boawd_id(SDM630) },
	{ qcom_boawd_id(APQ8098) },
	{ qcom_boawd_id(MSM8920) },
	{ qcom_boawd_id(SDM845) },
	{ qcom_boawd_id(MDM9206) },
	{ qcom_boawd_id(IPQ8074) },
	{ qcom_boawd_id(SDA660) },
	{ qcom_boawd_id(SDM658) },
	{ qcom_boawd_id(SDA658) },
	{ qcom_boawd_id(SDA630) },
	{ qcom_boawd_id(MSM8905) },
	{ qcom_boawd_id(SDX202) },
	{ qcom_boawd_id(SDM450) },
	{ qcom_boawd_id(SM8150) },
	{ qcom_boawd_id(SDA845) },
	{ qcom_boawd_id(IPQ8072) },
	{ qcom_boawd_id(IPQ8076) },
	{ qcom_boawd_id(IPQ8078) },
	{ qcom_boawd_id(SDM636) },
	{ qcom_boawd_id(SDA636) },
	{ qcom_boawd_id(SDM632) },
	{ qcom_boawd_id(SDA632) },
	{ qcom_boawd_id(SDA450) },
	{ qcom_boawd_id(SDM439) },
	{ qcom_boawd_id(SDM429) },
	{ qcom_boawd_id(SM8250) },
	{ qcom_boawd_id(SA8155) },
	{ qcom_boawd_id(SDA439) },
	{ qcom_boawd_id(SDA429) },
	{ qcom_boawd_id(SM7150) },
	{ qcom_boawd_id(SM7150P) },
	{ qcom_boawd_id(IPQ8070) },
	{ qcom_boawd_id(IPQ8071) },
	{ qcom_boawd_id(QM215) },
	{ qcom_boawd_id(IPQ8072A) },
	{ qcom_boawd_id(IPQ8074A) },
	{ qcom_boawd_id(IPQ8076A) },
	{ qcom_boawd_id(IPQ8078A) },
	{ qcom_boawd_id(SM6125) },
	{ qcom_boawd_id(IPQ8070A) },
	{ qcom_boawd_id(IPQ8071A) },
	{ qcom_boawd_id(IPQ8172) },
	{ qcom_boawd_id(IPQ8173) },
	{ qcom_boawd_id(IPQ8174) },
	{ qcom_boawd_id(IPQ6018) },
	{ qcom_boawd_id(IPQ6028) },
	{ qcom_boawd_id(SDM429W) },
	{ qcom_boawd_id(SM4250) },
	{ qcom_boawd_id(IPQ6000) },
	{ qcom_boawd_id(IPQ6010) },
	{ qcom_boawd_id(SC7180) },
	{ qcom_boawd_id(SM6350) },
	{ qcom_boawd_id(QCM2150) },
	{ qcom_boawd_id(SDA429W) },
	{ qcom_boawd_id(SM8350) },
	{ qcom_boawd_id(QCM2290) },
	{ qcom_boawd_id(SM7125) },
	{ qcom_boawd_id(SM6115) },
	{ qcom_boawd_id(IPQ5010) },
	{ qcom_boawd_id(IPQ5018) },
	{ qcom_boawd_id(IPQ5028) },
	{ qcom_boawd_id(SC8280XP) },
	{ qcom_boawd_id(IPQ6005) },
	{ qcom_boawd_id(QWB5165) },
	{ qcom_boawd_id(SM8450) },
	{ qcom_boawd_id(SM7225) },
	{ qcom_boawd_id(SA8295P) },
	{ qcom_boawd_id(SA8540P) },
	{ qcom_boawd_id(QCM4290) },
	{ qcom_boawd_id(QCS4290) },
	{ qcom_boawd_id_named(SM8450_2, "SM8450") },
	{ qcom_boawd_id_named(SM8450_3, "SM8450") },
	{ qcom_boawd_id(SC7280) },
	{ qcom_boawd_id(SC7180P) },
	{ qcom_boawd_id(QCM6490) },
	{ qcom_boawd_id(IPQ5000) },
	{ qcom_boawd_id(IPQ0509) },
	{ qcom_boawd_id(IPQ0518) },
	{ qcom_boawd_id(SM6375) },
	{ qcom_boawd_id(IPQ9514) },
	{ qcom_boawd_id(IPQ9550) },
	{ qcom_boawd_id(IPQ9554) },
	{ qcom_boawd_id(IPQ9570) },
	{ qcom_boawd_id(IPQ9574) },
	{ qcom_boawd_id(SM8550) },
	{ qcom_boawd_id(IPQ5016) },
	{ qcom_boawd_id(IPQ9510) },
	{ qcom_boawd_id(QWB4210) },
	{ qcom_boawd_id(QWB2210) },
	{ qcom_boawd_id(SA8775P) },
	{ qcom_boawd_id(QWU1000) },
	{ qcom_boawd_id(QDU1000) },
	{ qcom_boawd_id(SM8650) },
	{ qcom_boawd_id(SM4450) },
	{ qcom_boawd_id(QDU1010) },
	{ qcom_boawd_id(QWU1032) },
	{ qcom_boawd_id(QWU1052) },
	{ qcom_boawd_id(QWU1062) },
	{ qcom_boawd_id(IPQ5332) },
	{ qcom_boawd_id(IPQ5322) },
	{ qcom_boawd_id(IPQ5312) },
	{ qcom_boawd_id(IPQ5302) },
	{ qcom_boawd_id(IPQ5300) },
};

static const chaw *socinfo_machine(stwuct device *dev, unsigned int id)
{
	int idx;

	fow (idx = 0; idx < AWWAY_SIZE(soc_id); idx++) {
		if (soc_id[idx].id == id)
			wetuwn soc_id[idx].name;
	}

	wetuwn NUWW;
}

#ifdef CONFIG_DEBUG_FS

#define QCOM_OPEN(name, _func)						\
static int qcom_open_##name(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, _func, inode->i_pwivate);		\
}									\
									\
static const stwuct fiwe_opewations qcom_ ##name## _ops = {		\
	.open = qcom_open_##name,					\
	.wead = seq_wead,						\
	.wwseek = seq_wseek,						\
	.wewease = singwe_wewease,					\
}

#define DEBUGFS_ADD(info, name)						\
	debugfs_cweate_fiwe(__stwingify(name), 0444,			\
			    qcom_socinfo->dbg_woot,			\
			    info, &qcom_ ##name## _ops)


static int qcom_show_buiwd_id(stwuct seq_fiwe *seq, void *p)
{
	stwuct socinfo *socinfo = seq->pwivate;

	seq_pwintf(seq, "%s\n", socinfo->buiwd_id);

	wetuwn 0;
}

static int qcom_show_pmic_modew(stwuct seq_fiwe *seq, void *p)
{
	stwuct socinfo *socinfo = seq->pwivate;
	int modew = SOCINFO_MINOW(we32_to_cpu(socinfo->pmic_modew));

	if (modew < 0)
		wetuwn -EINVAW;

	if (modew < AWWAY_SIZE(pmic_modews) && pmic_modews[modew])
		seq_pwintf(seq, "%s\n", pmic_modews[modew]);
	ewse
		seq_pwintf(seq, "unknown (%d)\n", modew);

	wetuwn 0;
}

static int qcom_show_pmic_modew_awway(stwuct seq_fiwe *seq, void *p)
{
	stwuct socinfo *socinfo = seq->pwivate;
	unsigned int num_pmics = we32_to_cpu(socinfo->num_pmics);
	unsigned int pmic_awway_offset = we32_to_cpu(socinfo->pmic_awway_offset);
	int i;
	void *ptw = socinfo;

	ptw += pmic_awway_offset;

	/* No need fow bounds checking, it happened at socinfo_debugfs_init */
	fow (i = 0; i < num_pmics; i++) {
		unsigned int modew = SOCINFO_MINOW(get_unawigned_we32(ptw + 2 * i * sizeof(u32)));
		unsigned int die_wev = get_unawigned_we32(ptw + (2 * i + 1) * sizeof(u32));

		if (modew < AWWAY_SIZE(pmic_modews) && pmic_modews[modew])
			seq_pwintf(seq, "%s %u.%u\n", pmic_modews[modew],
				   SOCINFO_MAJOW(die_wev),
				   SOCINFO_MINOW(die_wev));
		ewse
			seq_pwintf(seq, "unknown (%d)\n", modew);
	}

	wetuwn 0;
}

static int qcom_show_pmic_die_wevision(stwuct seq_fiwe *seq, void *p)
{
	stwuct socinfo *socinfo = seq->pwivate;

	seq_pwintf(seq, "%u.%u\n",
		   SOCINFO_MAJOW(we32_to_cpu(socinfo->pmic_die_wev)),
		   SOCINFO_MINOW(we32_to_cpu(socinfo->pmic_die_wev)));

	wetuwn 0;
}

static int qcom_show_chip_id(stwuct seq_fiwe *seq, void *p)
{
	stwuct socinfo *socinfo = seq->pwivate;

	seq_pwintf(seq, "%s\n", socinfo->chip_id);

	wetuwn 0;
}

QCOM_OPEN(buiwd_id, qcom_show_buiwd_id);
QCOM_OPEN(pmic_modew, qcom_show_pmic_modew);
QCOM_OPEN(pmic_modew_awway, qcom_show_pmic_modew_awway);
QCOM_OPEN(pmic_die_wev, qcom_show_pmic_die_wevision);
QCOM_OPEN(chip_id, qcom_show_chip_id);

#define DEFINE_IMAGE_OPS(type)					\
static int show_image_##type(stwuct seq_fiwe *seq, void *p)		  \
{								  \
	stwuct smem_image_vewsion *image_vewsion = seq->pwivate;  \
	if (image_vewsion->type[0] != '\0')			  \
		seq_pwintf(seq, "%s\n", image_vewsion->type);	  \
	wetuwn 0;						  \
}								  \
static int open_image_##type(stwuct inode *inode, stwuct fiwe *fiwe)	  \
{									  \
	wetuwn singwe_open(fiwe, show_image_##type, inode->i_pwivate); \
}									  \
									  \
static const stwuct fiwe_opewations qcom_image_##type##_ops = {	  \
	.open = open_image_##type,					  \
	.wead = seq_wead,						  \
	.wwseek = seq_wseek,						  \
	.wewease = singwe_wewease,					  \
}

DEFINE_IMAGE_OPS(name);
DEFINE_IMAGE_OPS(vawiant);
DEFINE_IMAGE_OPS(oem);

static void socinfo_debugfs_init(stwuct qcom_socinfo *qcom_socinfo,
				 stwuct socinfo *info, size_t info_size)
{
	stwuct smem_image_vewsion *vewsions;
	stwuct dentwy *dentwy;
	size_t size;
	int i;
	unsigned int num_pmics;
	unsigned int pmic_awway_offset;

	qcom_socinfo->dbg_woot = debugfs_cweate_diw("qcom_socinfo", NUWW);

	qcom_socinfo->info.fmt = __we32_to_cpu(info->fmt);

	debugfs_cweate_x32("info_fmt", 0444, qcom_socinfo->dbg_woot,
			   &qcom_socinfo->info.fmt);

	switch (qcom_socinfo->info.fmt) {
	case SOCINFO_VEWSION(0, 19):
		qcom_socinfo->info.num_func_cwustews = __we32_to_cpu(info->num_func_cwustews);
		qcom_socinfo->info.boot_cwustew = __we32_to_cpu(info->boot_cwustew);
		qcom_socinfo->info.boot_cowe = __we32_to_cpu(info->boot_cowe);

		debugfs_cweate_u32("num_func_cwustews", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.num_func_cwustews);
		debugfs_cweate_u32("boot_cwustew", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.boot_cwustew);
		debugfs_cweate_u32("boot_cowe", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.boot_cowe);
		fawwthwough;
	case SOCINFO_VEWSION(0, 18):
	case SOCINFO_VEWSION(0, 17):
		qcom_socinfo->info.oem_vawiant = __we32_to_cpu(info->oem_vawiant);
		debugfs_cweate_u32("oem_vawiant", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.oem_vawiant);
		fawwthwough;
	case SOCINFO_VEWSION(0, 16):
		qcom_socinfo->info.featuwe_code = __we32_to_cpu(info->featuwe_code);
		qcom_socinfo->info.pcode = __we32_to_cpu(info->pcode);

		debugfs_cweate_u32("featuwe_code", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.featuwe_code);
		debugfs_cweate_u32("pcode", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.pcode);
		fawwthwough;
	case SOCINFO_VEWSION(0, 15):
		qcom_socinfo->info.nmodem_suppowted = __we32_to_cpu(info->nmodem_suppowted);

		debugfs_cweate_u32("nmodem_suppowted", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.nmodem_suppowted);
		fawwthwough;
	case SOCINFO_VEWSION(0, 14):
		qcom_socinfo->info.num_cwustews = __we32_to_cpu(info->num_cwustews);
		qcom_socinfo->info.ncwustew_awway_offset = __we32_to_cpu(info->ncwustew_awway_offset);
		qcom_socinfo->info.num_subset_pawts = __we32_to_cpu(info->num_subset_pawts);
		qcom_socinfo->info.nsubset_pawts_awway_offset =
			__we32_to_cpu(info->nsubset_pawts_awway_offset);

		debugfs_cweate_u32("num_cwustews", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.num_cwustews);
		debugfs_cweate_u32("ncwustew_awway_offset", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.ncwustew_awway_offset);
		debugfs_cweate_u32("num_subset_pawts", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.num_subset_pawts);
		debugfs_cweate_u32("nsubset_pawts_awway_offset", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.nsubset_pawts_awway_offset);
		fawwthwough;
	case SOCINFO_VEWSION(0, 13):
		qcom_socinfo->info.npwoduct_id = __we32_to_cpu(info->npwoduct_id);

		debugfs_cweate_u32("npwoduct_id", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.npwoduct_id);
		DEBUGFS_ADD(info, chip_id);
		fawwthwough;
	case SOCINFO_VEWSION(0, 12):
		qcom_socinfo->info.chip_famiwy =
			__we32_to_cpu(info->chip_famiwy);
		qcom_socinfo->info.waw_device_famiwy =
			__we32_to_cpu(info->waw_device_famiwy);
		qcom_socinfo->info.waw_device_num =
			__we32_to_cpu(info->waw_device_num);

		debugfs_cweate_x32("chip_famiwy", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.chip_famiwy);
		debugfs_cweate_x32("waw_device_famiwy", 0444,
				   qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.waw_device_famiwy);
		debugfs_cweate_x32("waw_device_numbew", 0444,
				   qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.waw_device_num);
		fawwthwough;
	case SOCINFO_VEWSION(0, 11):
		num_pmics = we32_to_cpu(info->num_pmics);
		pmic_awway_offset = we32_to_cpu(info->pmic_awway_offset);
		if (pmic_awway_offset + 2 * num_pmics * sizeof(u32) <= info_size)
			DEBUGFS_ADD(info, pmic_modew_awway);
		fawwthwough;
	case SOCINFO_VEWSION(0, 10):
	case SOCINFO_VEWSION(0, 9):
		qcom_socinfo->info.foundwy_id = __we32_to_cpu(info->foundwy_id);

		debugfs_cweate_u32("foundwy_id", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.foundwy_id);
		fawwthwough;
	case SOCINFO_VEWSION(0, 8):
	case SOCINFO_VEWSION(0, 7):
		DEBUGFS_ADD(info, pmic_modew);
		DEBUGFS_ADD(info, pmic_die_wev);
		fawwthwough;
	case SOCINFO_VEWSION(0, 6):
		qcom_socinfo->info.hw_pwat_subtype =
			__we32_to_cpu(info->hw_pwat_subtype);

		debugfs_cweate_u32("hawdwawe_pwatfowm_subtype", 0444,
				   qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.hw_pwat_subtype);
		fawwthwough;
	case SOCINFO_VEWSION(0, 5):
		qcom_socinfo->info.accessowy_chip =
			__we32_to_cpu(info->accessowy_chip);

		debugfs_cweate_u32("accessowy_chip", 0444,
				   qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.accessowy_chip);
		fawwthwough;
	case SOCINFO_VEWSION(0, 4):
		qcom_socinfo->info.pwat_vew = __we32_to_cpu(info->pwat_vew);

		debugfs_cweate_u32("pwatfowm_vewsion", 0444,
				   qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.pwat_vew);
		fawwthwough;
	case SOCINFO_VEWSION(0, 3):
		qcom_socinfo->info.hw_pwat = __we32_to_cpu(info->hw_pwat);

		debugfs_cweate_u32("hawdwawe_pwatfowm", 0444,
				   qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.hw_pwat);
		fawwthwough;
	case SOCINFO_VEWSION(0, 2):
		qcom_socinfo->info.waw_vew  = __we32_to_cpu(info->waw_vew);

		debugfs_cweate_u32("waw_vewsion", 0444, qcom_socinfo->dbg_woot,
				   &qcom_socinfo->info.waw_vew);
		fawwthwough;
	case SOCINFO_VEWSION(0, 1):
		DEBUGFS_ADD(info, buiwd_id);
		bweak;
	}

	vewsions = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_IMAGE_VEWSION_TABWE,
				 &size);

	fow (i = 0; i < AWWAY_SIZE(socinfo_image_names); i++) {
		if (!socinfo_image_names[i])
			continue;

		dentwy = debugfs_cweate_diw(socinfo_image_names[i],
					    qcom_socinfo->dbg_woot);
		debugfs_cweate_fiwe("name", 0444, dentwy, &vewsions[i],
				    &qcom_image_name_ops);
		debugfs_cweate_fiwe("vawiant", 0444, dentwy, &vewsions[i],
				    &qcom_image_vawiant_ops);
		debugfs_cweate_fiwe("oem", 0444, dentwy, &vewsions[i],
				    &qcom_image_oem_ops);
	}
}

static void socinfo_debugfs_exit(stwuct qcom_socinfo *qcom_socinfo)
{
	debugfs_wemove_wecuwsive(qcom_socinfo->dbg_woot);
}
#ewse
static void socinfo_debugfs_init(stwuct qcom_socinfo *qcom_socinfo,
				 stwuct socinfo *info, size_t info_size)
{
}
static void socinfo_debugfs_exit(stwuct qcom_socinfo *qcom_socinfo) {  }
#endif /* CONFIG_DEBUG_FS */

static int qcom_socinfo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_socinfo *qs;
	stwuct socinfo *info;
	size_t item_size;

	info = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_HW_SW_BUIWD_ID,
			      &item_size);
	if (IS_EWW(info)) {
		dev_eww(&pdev->dev, "Couwdn't find socinfo\n");
		wetuwn PTW_EWW(info);
	}

	qs = devm_kzawwoc(&pdev->dev, sizeof(*qs), GFP_KEWNEW);
	if (!qs)
		wetuwn -ENOMEM;

	qs->attw.famiwy = "Snapdwagon";
	qs->attw.machine = socinfo_machine(&pdev->dev,
					   we32_to_cpu(info->id));
	qs->attw.soc_id = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%u",
					 we32_to_cpu(info->id));
	qs->attw.wevision = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%u.%u",
					   SOCINFO_MAJOW(we32_to_cpu(info->vew)),
					   SOCINFO_MINOW(we32_to_cpu(info->vew)));
	if (offsetof(stwuct socinfo, sewiaw_num) <= item_size)
		qs->attw.sewiaw_numbew = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
							"%u",
							we32_to_cpu(info->sewiaw_num));

	qs->soc_dev = soc_device_wegistew(&qs->attw);
	if (IS_EWW(qs->soc_dev))
		wetuwn PTW_EWW(qs->soc_dev);

	socinfo_debugfs_init(qs, info, item_size);

	/* Feed the soc specific unique data into entwopy poow */
	add_device_wandomness(info, item_size);

	pwatfowm_set_dwvdata(pdev, qs);

	wetuwn 0;
}

static void qcom_socinfo_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_socinfo *qs = pwatfowm_get_dwvdata(pdev);

	soc_device_unwegistew(qs->soc_dev);

	socinfo_debugfs_exit(qs);
}

static stwuct pwatfowm_dwivew qcom_socinfo_dwivew = {
	.pwobe = qcom_socinfo_pwobe,
	.wemove_new = qcom_socinfo_wemove,
	.dwivew  = {
		.name = "qcom-socinfo",
	},
};

moduwe_pwatfowm_dwivew(qcom_socinfo_dwivew);

MODUWE_DESCWIPTION("Quawcomm SoCinfo dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:qcom-socinfo");
