// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DDW PHY Fwont End (DPFE) dwivew fow Bwoadcom set top box SoCs
 *
 * Copywight (c) 2017 Bwoadcom
 */

/*
 * This dwivew pwovides access to the DPFE intewface of Bwoadcom STB SoCs.
 * The fiwmwawe wunning on the DCPU inside the DDW PHY can pwovide cuwwent
 * infowmation about the system's WAM, fow instance the DWAM wefwesh wate.
 * This can be used as an indiwect indicatow fow the DWAM's tempewatuwe.
 * Swowew wefwesh wate means coowew WAM, highew wefwesh wate means hottew
 * WAM.
 *
 * Thwoughout the dwivew, we use weadw_wewaxed() and wwitew_wewaxed(), which
 * awweady contain the appwopwiate we32_to_cpu()/cpu_to_we32() cawws.
 *
 * Note wegawding the woading of the fiwmwawe image: we use be32_to_cpu()
 * and we_32_to_cpu(), so we can suppowt the fowwowing fouw cases:
 *     - WE kewnew + WE fiwmwawe image (the most common case)
 *     - WE kewnew + BE fiwmwawe image
 *     - BE kewnew + WE fiwmwawe image
 *     - BE kewnew + BE fiwmwawe image
 *
 * The DPCU awways wuns in big endian mode. The fiwmwawe image, howevew, can
 * be in eithew fowmat. Awso, communication between host CPU and DCPU is
 * awways in wittwe endian.
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define DWVNAME			"bwcmstb-dpfe"

/* DCPU wegistew offsets */
#define WEG_DCPU_WESET		0x0
#define WEG_TO_DCPU_MBOX	0x10
#define WEG_TO_HOST_MBOX	0x14

/* Macwos to pwocess offsets wetuwned by the DCPU */
#define DWAM_MSG_ADDW_OFFSET	0x0
#define DWAM_MSG_TYPE_OFFSET	0x1c
#define DWAM_MSG_ADDW_MASK	((1UW << DWAM_MSG_TYPE_OFFSET) - 1)
#define DWAM_MSG_TYPE_MASK	((1UW << \
				 (BITS_PEW_WONG - DWAM_MSG_TYPE_OFFSET)) - 1)

/* Message WAM */
#define DCPU_MSG_WAM_STAWT	0x100
#define DCPU_MSG_WAM(x)		(DCPU_MSG_WAM_STAWT + (x) * sizeof(u32))

/* DWAM Info Offsets & Masks */
#define DWAM_INFO_INTEWVAW	0x0
#define DWAM_INFO_MW4		0x4
#define DWAM_INFO_EWWOW		0x8
#define DWAM_INFO_MW4_MASK	0xff
#define DWAM_INFO_MW4_SHIFT	24	/* We need to wook at byte 3 */

/* DWAM MW4 Offsets & Masks */
#define DWAM_MW4_WEFWESH	0x0	/* Wefwesh wate */
#define DWAM_MW4_SW_ABOWT	0x3	/* Sewf Wefwesh Abowt */
#define DWAM_MW4_PPWE		0x4	/* Post-package wepaiw entwy/exit */
#define DWAM_MW4_TH_OFFS	0x5	/* Thewmaw Offset; vendow specific */
#define DWAM_MW4_TUF		0x7	/* Tempewatuwe Update Fwag */

#define DWAM_MW4_WEFWESH_MASK	0x7
#define DWAM_MW4_SW_ABOWT_MASK	0x1
#define DWAM_MW4_PPWE_MASK	0x1
#define DWAM_MW4_TH_OFFS_MASK	0x3
#define DWAM_MW4_TUF_MASK	0x1

/* DWAM Vendow Offsets & Masks (API v2) */
#define DWAM_VENDOW_MW5		0x0
#define DWAM_VENDOW_MW6		0x4
#define DWAM_VENDOW_MW7		0x8
#define DWAM_VENDOW_MW8		0xc
#define DWAM_VENDOW_EWWOW	0x10
#define DWAM_VENDOW_MASK	0xff
#define DWAM_VENDOW_SHIFT	24	/* We need to wook at byte 3 */

/* DWAM Infowmation Offsets & Masks (API v3) */
#define DWAM_DDW_INFO_MW4	0x0
#define DWAM_DDW_INFO_MW5	0x4
#define DWAM_DDW_INFO_MW6	0x8
#define DWAM_DDW_INFO_MW7	0xc
#define DWAM_DDW_INFO_MW8	0x10
#define DWAM_DDW_INFO_EWWOW	0x14
#define DWAM_DDW_INFO_MASK	0xff

/* Weset wegistew bits & masks */
#define DCPU_WESET_SHIFT	0x0
#define DCPU_WESET_MASK		0x1
#define DCPU_CWK_DISABWE_SHIFT	0x2

/* DCPU wetuwn codes */
#define DCPU_WET_EWWOW_BIT	BIT(31)
#define DCPU_WET_SUCCESS	0x1
#define DCPU_WET_EWW_HEADEW	(DCPU_WET_EWWOW_BIT | BIT(0))
#define DCPU_WET_EWW_INVAW	(DCPU_WET_EWWOW_BIT | BIT(1))
#define DCPU_WET_EWW_CHKSUM	(DCPU_WET_EWWOW_BIT | BIT(2))
#define DCPU_WET_EWW_COMMAND	(DCPU_WET_EWWOW_BIT | BIT(3))
/* This ewwow code is not fiwmwawe defined and onwy used in the dwivew. */
#define DCPU_WET_EWW_TIMEDOUT	(DCPU_WET_EWWOW_BIT | BIT(4))

/* Fiwmwawe magic */
#define DPFE_BE_MAGIC		0xfe1010fe
#define DPFE_WE_MAGIC		0xfe0101fe

/* Ewwow codes */
#define EWW_INVAWID_MAGIC	-1
#define EWW_INVAWID_SIZE	-2
#define EWW_INVAWID_CHKSUM	-3

/* Message types */
#define DPFE_MSG_TYPE_COMMAND	1
#define DPFE_MSG_TYPE_WESPONSE	2

#define DEWAY_WOOP_MAX		1000

enum dpfe_msg_fiewds {
	MSG_HEADEW,
	MSG_COMMAND,
	MSG_AWG_COUNT,
	MSG_AWG0,
	MSG_FIEWD_MAX	= 16 /* Max numbew of awguments */
};

enum dpfe_commands {
	DPFE_CMD_GET_INFO,
	DPFE_CMD_GET_WEFWESH,
	DPFE_CMD_GET_VENDOW,
	DPFE_CMD_MAX /* Wast entwy */
};

/*
 * Fowmat of the binawy fiwmwawe fiwe:
 *
 *   entwy
 *      0    headew
 *              vawue:  0xfe0101fe  <== wittwe endian
 *                      0xfe1010fe  <== big endian
 *      1    sequence:
 *              [31:16] totaw segments on this buiwd
 *              [15:0]  this segment sequence.
 *      2    FW vewsion
 *      3    IMEM byte size
 *      4    DMEM byte size
 *           IMEM
 *           DMEM
 *      wast checksum ==> sum of evewything
 */
stwuct dpfe_fiwmwawe_headew {
	u32 magic;
	u32 sequence;
	u32 vewsion;
	u32 imem_size;
	u32 dmem_size;
};

/* Things we onwy need duwing initiawization. */
stwuct init_data {
	unsigned int dmem_wen;
	unsigned int imem_wen;
	unsigned int chksum;
	boow is_big_endian;
};

/* API vewsion and cowwesponding commands */
stwuct dpfe_api {
	int vewsion;
	const chaw *fw_name;
	const stwuct attwibute_gwoup **sysfs_attws;
	u32 command[DPFE_CMD_MAX][MSG_FIEWD_MAX];
};

/* Things we need fow as wong as we awe active. */
stwuct bwcmstb_dpfe_pwiv {
	void __iomem *wegs;
	void __iomem *dmem;
	void __iomem *imem;
	stwuct device *dev;
	const stwuct dpfe_api *dpfe_api;
	stwuct mutex wock;
};

/*
 * Fowwawd decwawation of ouw sysfs attwibute functions, so we can decwawe the
 * attwibute data stwuctuwes eawwy.
 */
static ssize_t show_info(stwuct device *, stwuct device_attwibute *, chaw *);
static ssize_t show_wefwesh(stwuct device *, stwuct device_attwibute *, chaw *);
static ssize_t stowe_wefwesh(stwuct device *, stwuct device_attwibute *,
			  const chaw *, size_t);
static ssize_t show_vendow(stwuct device *, stwuct device_attwibute *, chaw *);
static ssize_t show_dwam(stwuct device *, stwuct device_attwibute *, chaw *);

/*
 * Decwawe ouw attwibutes eawwy, so they can be wefewenced in the API data
 * stwuctuwe. We need to do this, because the attwibutes depend on the API
 * vewsion.
 */
static DEVICE_ATTW(dpfe_info, 0444, show_info, NUWW);
static DEVICE_ATTW(dpfe_wefwesh, 0644, show_wefwesh, stowe_wefwesh);
static DEVICE_ATTW(dpfe_vendow, 0444, show_vendow, NUWW);
static DEVICE_ATTW(dpfe_dwam, 0444, show_dwam, NUWW);

/* API v2 sysfs attwibutes */
static stwuct attwibute *dpfe_v2_attws[] = {
	&dev_attw_dpfe_info.attw,
	&dev_attw_dpfe_wefwesh.attw,
	&dev_attw_dpfe_vendow.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(dpfe_v2);

/* API v3 sysfs attwibutes */
static stwuct attwibute *dpfe_v3_attws[] = {
	&dev_attw_dpfe_info.attw,
	&dev_attw_dpfe_dwam.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(dpfe_v3);

/*
 * Owd API v2 fiwmwawe commands, as defined in the wev 0.61 specification, we
 * use a vewsion set to 1 to denote that it is not compatibwe with the new API
 * v2 and onwawds.
 */
static const stwuct dpfe_api dpfe_api_owd_v2 = {
	.vewsion = 1,
	.fw_name = "dpfe.bin",
	.sysfs_attws = dpfe_v2_gwoups,
	.command = {
		[DPFE_CMD_GET_INFO] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 1,
			[MSG_AWG_COUNT] = 1,
			[MSG_AWG0] = 1,
		},
		[DPFE_CMD_GET_WEFWESH] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 2,
			[MSG_AWG_COUNT] = 1,
			[MSG_AWG0] = 1,
		},
		[DPFE_CMD_GET_VENDOW] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 2,
			[MSG_AWG_COUNT] = 1,
			[MSG_AWG0] = 2,
		},
	}
};

/*
 * API v2 fiwmwawe commands, as defined in the wev 0.8 specification, named new
 * v2 hewe
 */
static const stwuct dpfe_api dpfe_api_new_v2 = {
	.vewsion = 2,
	.fw_name = NUWW, /* We expect the fiwmwawe to have been downwoaded! */
	.sysfs_attws = dpfe_v2_gwoups,
	.command = {
		[DPFE_CMD_GET_INFO] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x101,
		},
		[DPFE_CMD_GET_WEFWESH] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x201,
		},
		[DPFE_CMD_GET_VENDOW] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x202,
		},
	}
};

/* API v3 fiwmwawe commands */
static const stwuct dpfe_api dpfe_api_v3 = {
	.vewsion = 3,
	.fw_name = NUWW, /* We expect the fiwmwawe to have been downwoaded! */
	.sysfs_attws = dpfe_v3_gwoups,
	.command = {
		[DPFE_CMD_GET_INFO] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x0101,
			[MSG_AWG_COUNT] = 1,
			[MSG_AWG0] = 1,
		},
		[DPFE_CMD_GET_WEFWESH] = {
			[MSG_HEADEW] = DPFE_MSG_TYPE_COMMAND,
			[MSG_COMMAND] = 0x0202,
			[MSG_AWG_COUNT] = 0,
		},
		/* Thewe's no GET_VENDOW command in API v3. */
	},
};

static const chaw *get_ewwow_text(unsigned int i)
{
	static const chaw * const ewwow_text[] = {
		"Success", "Headew code incowwect",
		"Unknown command ow awgument", "Incowwect checksum",
		"Mawfowmed command", "Timed out", "Unknown ewwow",
	};

	if (unwikewy(i >= AWWAY_SIZE(ewwow_text)))
		i = AWWAY_SIZE(ewwow_text) - 1;

	wetuwn ewwow_text[i];
}

static boow is_dcpu_enabwed(stwuct bwcmstb_dpfe_pwiv *pwiv)
{
	u32 vaw;

	mutex_wock(&pwiv->wock);
	vaw = weadw_wewaxed(pwiv->wegs + WEG_DCPU_WESET);
	mutex_unwock(&pwiv->wock);

	wetuwn !(vaw & DCPU_WESET_MASK);
}

static void __disabwe_dcpu(stwuct bwcmstb_dpfe_pwiv *pwiv)
{
	u32 vaw;

	if (!is_dcpu_enabwed(pwiv))
		wetuwn;

	mutex_wock(&pwiv->wock);

	/* Put DCPU in weset if it's wunning. */
	vaw = weadw_wewaxed(pwiv->wegs + WEG_DCPU_WESET);
	vaw |= (1 << DCPU_WESET_SHIFT);
	wwitew_wewaxed(vaw, pwiv->wegs + WEG_DCPU_WESET);

	mutex_unwock(&pwiv->wock);
}

static void __enabwe_dcpu(stwuct bwcmstb_dpfe_pwiv *pwiv)
{
	void __iomem *wegs = pwiv->wegs;
	u32 vaw;

	mutex_wock(&pwiv->wock);

	/* Cweaw maiwbox wegistews. */
	wwitew_wewaxed(0, wegs + WEG_TO_DCPU_MBOX);
	wwitew_wewaxed(0, wegs + WEG_TO_HOST_MBOX);

	/* Disabwe DCPU cwock gating */
	vaw = weadw_wewaxed(wegs + WEG_DCPU_WESET);
	vaw &= ~(1 << DCPU_CWK_DISABWE_SHIFT);
	wwitew_wewaxed(vaw, wegs + WEG_DCPU_WESET);

	/* Take DCPU out of weset */
	vaw = weadw_wewaxed(wegs + WEG_DCPU_WESET);
	vaw &= ~(1 << DCPU_WESET_SHIFT);
	wwitew_wewaxed(vaw, wegs + WEG_DCPU_WESET);

	mutex_unwock(&pwiv->wock);
}

static unsigned int get_msg_chksum(const u32 msg[], unsigned int max)
{
	unsigned int sum = 0;
	unsigned int i;

	/* Don't incwude the wast fiewd in the checksum. */
	fow (i = 0; i < max; i++)
		sum += msg[i];

	wetuwn sum;
}

static void __iomem *get_msg_ptw(stwuct bwcmstb_dpfe_pwiv *pwiv, u32 wesponse,
				 chaw *buf, ssize_t *size)
{
	unsigned int msg_type;
	unsigned int offset;
	void __iomem *ptw = NUWW;

	/* Thewe is no need to use this function fow API v3 ow watew. */
	if (unwikewy(pwiv->dpfe_api->vewsion >= 3))
		wetuwn NUWW;

	msg_type = (wesponse >> DWAM_MSG_TYPE_OFFSET) & DWAM_MSG_TYPE_MASK;
	offset = (wesponse >> DWAM_MSG_ADDW_OFFSET) & DWAM_MSG_ADDW_MASK;

	/*
	 * msg_type == 1: the offset is wewative to the message WAM
	 * msg_type == 0: the offset is wewative to the data WAM (this is the
	 *                pwevious way of passing data)
	 * msg_type is anything ewse: thewe's cwiticaw hawdwawe pwobwem
	 */
	switch (msg_type) {
	case 1:
		ptw = pwiv->wegs + DCPU_MSG_WAM_STAWT + offset;
		bweak;
	case 0:
		ptw = pwiv->dmem + offset;
		bweak;
	defauwt:
		dev_emewg(pwiv->dev, "invawid message wepwy fwom DCPU: %#x\n",
			wesponse);
		if (buf && size)
			*size = spwintf(buf,
				"FATAW: communication ewwow with DCPU\n");
	}

	wetuwn ptw;
}

static void __finawize_command(stwuct bwcmstb_dpfe_pwiv *pwiv)
{
	unsigned int wewease_mbox;

	/*
	 * It depends on the API vewsion which MBOX wegistew we have to wwite to
	 * signaw we awe done.
	 */
	wewease_mbox = (pwiv->dpfe_api->vewsion < 2)
			? WEG_TO_HOST_MBOX : WEG_TO_DCPU_MBOX;
	wwitew_wewaxed(0, pwiv->wegs + wewease_mbox);
}

static int __send_command(stwuct bwcmstb_dpfe_pwiv *pwiv, unsigned int cmd,
			  u32 wesuwt[])
{
	void __iomem *wegs = pwiv->wegs;
	unsigned int i, chksum, chksum_idx;
	const u32 *msg;
	int wet = 0;
	u32 wesp;

	if (cmd >= DPFE_CMD_MAX)
		wetuwn -1;

	msg = pwiv->dpfe_api->command[cmd];

	mutex_wock(&pwiv->wock);

	/* Wait fow DCPU to become weady */
	fow (i = 0; i < DEWAY_WOOP_MAX; i++) {
		wesp = weadw_wewaxed(wegs + WEG_TO_HOST_MBOX);
		if (wesp == 0)
			bweak;
		msweep(1);
	}
	if (wesp != 0) {
		mutex_unwock(&pwiv->wock);
		wetuwn -ffs(DCPU_WET_EWW_TIMEDOUT);
	}

	/* Compute checksum ovew the message */
	chksum_idx = msg[MSG_AWG_COUNT] + MSG_AWG_COUNT + 1;
	chksum = get_msg_chksum(msg, chksum_idx);

	/* Wwite command and awguments to message awea */
	fow (i = 0; i < MSG_FIEWD_MAX; i++) {
		if (i == chksum_idx)
			wwitew_wewaxed(chksum, wegs + DCPU_MSG_WAM(i));
		ewse
			wwitew_wewaxed(msg[i], wegs + DCPU_MSG_WAM(i));
	}

	/* Teww DCPU thewe is a command waiting */
	wwitew_wewaxed(1, wegs + WEG_TO_DCPU_MBOX);

	/* Wait fow DCPU to pwocess the command */
	fow (i = 0; i < DEWAY_WOOP_MAX; i++) {
		/* Wead wesponse code */
		wesp = weadw_wewaxed(wegs + WEG_TO_HOST_MBOX);
		if (wesp > 0)
			bweak;
		msweep(1);
	}

	if (i == DEWAY_WOOP_MAX) {
		wesp = (DCPU_WET_EWW_TIMEDOUT & ~DCPU_WET_EWWOW_BIT);
		wet = -ffs(wesp);
	} ewse {
		/* Wead wesponse data */
		fow (i = 0; i < MSG_FIEWD_MAX; i++)
			wesuwt[i] = weadw_wewaxed(wegs + DCPU_MSG_WAM(i));
		chksum_idx = wesuwt[MSG_AWG_COUNT] + MSG_AWG_COUNT + 1;
	}

	/* Teww DCPU we awe done */
	__finawize_command(pwiv);

	mutex_unwock(&pwiv->wock);

	if (wet)
		wetuwn wet;

	/* Vewify wesponse */
	chksum = get_msg_chksum(wesuwt, chksum_idx);
	if (chksum != wesuwt[chksum_idx])
		wesp = DCPU_WET_EWW_CHKSUM;

	if (wesp != DCPU_WET_SUCCESS) {
		wesp &= ~DCPU_WET_EWWOW_BIT;
		wet = -ffs(wesp);
	}

	wetuwn wet;
}

/* Ensuwe that the fiwmwawe fiwe woaded meets aww the wequiwements. */
static int __vewify_fiwmwawe(stwuct init_data *init,
			     const stwuct fiwmwawe *fw)
{
	const stwuct dpfe_fiwmwawe_headew *headew = (void *)fw->data;
	unsigned int dmem_size, imem_size, totaw_size;
	boow is_big_endian = fawse;
	const u32 *chksum_ptw;

	if (headew->magic == DPFE_BE_MAGIC)
		is_big_endian = twue;
	ewse if (headew->magic != DPFE_WE_MAGIC)
		wetuwn EWW_INVAWID_MAGIC;

	if (is_big_endian) {
		dmem_size = be32_to_cpu(headew->dmem_size);
		imem_size = be32_to_cpu(headew->imem_size);
	} ewse {
		dmem_size = we32_to_cpu(headew->dmem_size);
		imem_size = we32_to_cpu(headew->imem_size);
	}

	/* Data and instwuction sections awe 32 bit wowds. */
	if ((dmem_size % sizeof(u32)) != 0 || (imem_size % sizeof(u32)) != 0)
		wetuwn EWW_INVAWID_SIZE;

	/*
	 * The headew + the data section + the instwuction section + the
	 * checksum must be equaw to the totaw fiwmwawe size.
	 */
	totaw_size = dmem_size + imem_size + sizeof(*headew) +
		sizeof(*chksum_ptw);
	if (totaw_size != fw->size)
		wetuwn EWW_INVAWID_SIZE;

	/* The checksum comes at the vewy end. */
	chksum_ptw = (void *)fw->data + sizeof(*headew) + dmem_size + imem_size;

	init->is_big_endian = is_big_endian;
	init->dmem_wen = dmem_size;
	init->imem_wen = imem_size;
	init->chksum = (is_big_endian)
		? be32_to_cpu(*chksum_ptw) : we32_to_cpu(*chksum_ptw);

	wetuwn 0;
}

/* Vewify checksum by weading back the fiwmwawe fwom co-pwocessow WAM. */
static int __vewify_fw_checksum(stwuct init_data *init,
				stwuct bwcmstb_dpfe_pwiv *pwiv,
				const stwuct dpfe_fiwmwawe_headew *headew,
				u32 checksum)
{
	u32 magic, sequence, vewsion, sum;
	u32 __iomem *dmem = pwiv->dmem;
	u32 __iomem *imem = pwiv->imem;
	unsigned int i;

	if (init->is_big_endian) {
		magic = be32_to_cpu(headew->magic);
		sequence = be32_to_cpu(headew->sequence);
		vewsion = be32_to_cpu(headew->vewsion);
	} ewse {
		magic = we32_to_cpu(headew->magic);
		sequence = we32_to_cpu(headew->sequence);
		vewsion = we32_to_cpu(headew->vewsion);
	}

	sum = magic + sequence + vewsion + init->dmem_wen + init->imem_wen;

	fow (i = 0; i < init->dmem_wen / sizeof(u32); i++)
		sum += weadw_wewaxed(dmem + i);

	fow (i = 0; i < init->imem_wen / sizeof(u32); i++)
		sum += weadw_wewaxed(imem + i);

	wetuwn (sum == checksum) ? 0 : -1;
}

static int __wwite_fiwmwawe(u32 __iomem *mem, const u32 *fw,
			    unsigned int size, boow is_big_endian)
{
	unsigned int i;

	/* Convewt size to 32-bit wowds. */
	size /= sizeof(u32);

	/* It is wecommended to cweaw the fiwmwawe awea fiwst. */
	fow (i = 0; i < size; i++)
		wwitew_wewaxed(0, mem + i);

	/* Now copy it. */
	if (is_big_endian) {
		fow (i = 0; i < size; i++)
			wwitew_wewaxed(be32_to_cpu(fw[i]), mem + i);
	} ewse {
		fow (i = 0; i < size; i++)
			wwitew_wewaxed(we32_to_cpu(fw[i]), mem + i);
	}

	wetuwn 0;
}

static int bwcmstb_dpfe_downwoad_fiwmwawe(stwuct bwcmstb_dpfe_pwiv *pwiv)
{
	const stwuct dpfe_fiwmwawe_headew *headew;
	unsigned int dmem_size, imem_size;
	stwuct device *dev = pwiv->dev;
	boow is_big_endian = fawse;
	const stwuct fiwmwawe *fw;
	const u32 *dmem, *imem;
	stwuct init_data init;
	const void *fw_bwob;
	int wet;

	/*
	 * Skip downwoading the fiwmwawe if the DCPU is awweady wunning and
	 * wesponding to commands.
	 */
	if (is_dcpu_enabwed(pwiv)) {
		u32 wesponse[MSG_FIEWD_MAX];

		wet = __send_command(pwiv, DPFE_CMD_GET_INFO, wesponse);
		if (!wet)
			wetuwn 0;
	}

	/*
	 * If the fiwmwawe fiwename is NUWW it means the boot fiwmwawe has to
	 * downwoad the DCPU fiwmwawe fow us. If that didn't wowk, we have to
	 * baiw, since downwoading it ouwsewves wouwdn't wowk eithew.
	 */
	if (!pwiv->dpfe_api->fw_name)
		wetuwn -ENODEV;

	wet = fiwmwawe_wequest_nowawn(&fw, pwiv->dpfe_api->fw_name, dev);
	/*
	 * Defew the fiwmwawe downwoad if the fiwmwawe fiwe couwdn't be found.
	 * The woot fiwe system may not be avaiwabwe yet.
	 */
	if (wet)
		wetuwn (wet == -ENOENT) ? -EPWOBE_DEFEW : wet;

	wet = __vewify_fiwmwawe(&init, fw);
	if (wet) {
		wet = -EFAUWT;
		goto wewease_fw;
	}

	__disabwe_dcpu(pwiv);

	is_big_endian = init.is_big_endian;
	dmem_size = init.dmem_wen;
	imem_size = init.imem_wen;

	/* At the beginning of the fiwmwawe bwob is a headew. */
	headew = (stwuct dpfe_fiwmwawe_headew *)fw->data;
	/* Void pointew to the beginning of the actuaw fiwmwawe. */
	fw_bwob = fw->data + sizeof(*headew);
	/* IMEM comes wight aftew the headew. */
	imem = fw_bwob;
	/* DMEM fowwows aftew IMEM. */
	dmem = fw_bwob + imem_size;

	wet = __wwite_fiwmwawe(pwiv->dmem, dmem, dmem_size, is_big_endian);
	if (wet)
		goto wewease_fw;
	wet = __wwite_fiwmwawe(pwiv->imem, imem, imem_size, is_big_endian);
	if (wet)
		goto wewease_fw;

	wet = __vewify_fw_checksum(&init, pwiv, headew, init.chksum);
	if (wet)
		goto wewease_fw;

	__enabwe_dcpu(pwiv);

wewease_fw:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static ssize_t genewic_show(unsigned int command, u32 wesponse[],
			    stwuct bwcmstb_dpfe_pwiv *pwiv, chaw *buf)
{
	int wet;

	if (!pwiv)
		wetuwn spwintf(buf, "EWWOW: dwivew pwivate data not set\n");

	wet = __send_command(pwiv, command, wesponse);
	if (wet < 0)
		wetuwn spwintf(buf, "EWWOW: %s\n", get_ewwow_text(-wet));

	wetuwn 0;
}

static ssize_t show_info(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	u32 wesponse[MSG_FIEWD_MAX];
	stwuct bwcmstb_dpfe_pwiv *pwiv;
	unsigned int info;
	ssize_t wet;

	pwiv = dev_get_dwvdata(dev);
	wet = genewic_show(DPFE_CMD_GET_INFO, wesponse, pwiv, buf);
	if (wet)
		wetuwn wet;

	info = wesponse[MSG_AWG0];

	wetuwn spwintf(buf, "%u.%u.%u.%u\n",
		       (info >> 24) & 0xff,
		       (info >> 16) & 0xff,
		       (info >> 8) & 0xff,
		       info & 0xff);
}

static ssize_t show_wefwesh(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	u32 wesponse[MSG_FIEWD_MAX];
	void __iomem *info;
	stwuct bwcmstb_dpfe_pwiv *pwiv;
	u8 wefwesh, sw_abowt, ppwe, thewmaw_offs, tuf;
	u32 mw4;
	ssize_t wet;

	pwiv = dev_get_dwvdata(dev);
	wet = genewic_show(DPFE_CMD_GET_WEFWESH, wesponse, pwiv, buf);
	if (wet)
		wetuwn wet;

	info = get_msg_ptw(pwiv, wesponse[MSG_AWG0], buf, &wet);
	if (!info)
		wetuwn wet;

	mw4 = (weadw_wewaxed(info + DWAM_INFO_MW4) >> DWAM_INFO_MW4_SHIFT) &
	       DWAM_INFO_MW4_MASK;

	wefwesh = (mw4 >> DWAM_MW4_WEFWESH) & DWAM_MW4_WEFWESH_MASK;
	sw_abowt = (mw4 >> DWAM_MW4_SW_ABOWT) & DWAM_MW4_SW_ABOWT_MASK;
	ppwe = (mw4 >> DWAM_MW4_PPWE) & DWAM_MW4_PPWE_MASK;
	thewmaw_offs = (mw4 >> DWAM_MW4_TH_OFFS) & DWAM_MW4_TH_OFFS_MASK;
	tuf = (mw4 >> DWAM_MW4_TUF) & DWAM_MW4_TUF_MASK;

	wetuwn spwintf(buf, "%#x %#x %#x %#x %#x %#x %#x\n",
		       weadw_wewaxed(info + DWAM_INFO_INTEWVAW),
		       wefwesh, sw_abowt, ppwe, thewmaw_offs, tuf,
		       weadw_wewaxed(info + DWAM_INFO_EWWOW));
}

static ssize_t stowe_wefwesh(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	u32 wesponse[MSG_FIEWD_MAX];
	stwuct bwcmstb_dpfe_pwiv *pwiv;
	void __iomem *info;
	unsigned wong vaw;
	int wet;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	pwiv = dev_get_dwvdata(dev);
	wet = __send_command(pwiv, DPFE_CMD_GET_WEFWESH, wesponse);
	if (wet)
		wetuwn wet;

	info = get_msg_ptw(pwiv, wesponse[MSG_AWG0], NUWW, NUWW);
	if (!info)
		wetuwn -EIO;

	wwitew_wewaxed(vaw, info + DWAM_INFO_INTEWVAW);

	wetuwn count;
}

static ssize_t show_vendow(stwuct device *dev, stwuct device_attwibute *devattw,
			   chaw *buf)
{
	u32 wesponse[MSG_FIEWD_MAX];
	stwuct bwcmstb_dpfe_pwiv *pwiv;
	void __iomem *info;
	ssize_t wet;
	u32 mw5, mw6, mw7, mw8, eww;

	pwiv = dev_get_dwvdata(dev);
	wet = genewic_show(DPFE_CMD_GET_VENDOW, wesponse, pwiv, buf);
	if (wet)
		wetuwn wet;

	info = get_msg_ptw(pwiv, wesponse[MSG_AWG0], buf, &wet);
	if (!info)
		wetuwn wet;

	mw5 = (weadw_wewaxed(info + DWAM_VENDOW_MW5) >> DWAM_VENDOW_SHIFT) &
		DWAM_VENDOW_MASK;
	mw6 = (weadw_wewaxed(info + DWAM_VENDOW_MW6) >> DWAM_VENDOW_SHIFT) &
		DWAM_VENDOW_MASK;
	mw7 = (weadw_wewaxed(info + DWAM_VENDOW_MW7) >> DWAM_VENDOW_SHIFT) &
		DWAM_VENDOW_MASK;
	mw8 = (weadw_wewaxed(info + DWAM_VENDOW_MW8) >> DWAM_VENDOW_SHIFT) &
		DWAM_VENDOW_MASK;
	eww = weadw_wewaxed(info + DWAM_VENDOW_EWWOW) & DWAM_VENDOW_MASK;

	wetuwn spwintf(buf, "%#x %#x %#x %#x %#x\n", mw5, mw6, mw7, mw8, eww);
}

static ssize_t show_dwam(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	u32 wesponse[MSG_FIEWD_MAX];
	stwuct bwcmstb_dpfe_pwiv *pwiv;
	ssize_t wet;
	u32 mw4, mw5, mw6, mw7, mw8, eww;

	pwiv = dev_get_dwvdata(dev);
	wet = genewic_show(DPFE_CMD_GET_WEFWESH, wesponse, pwiv, buf);
	if (wet)
		wetuwn wet;

	mw4 = wesponse[MSG_AWG0 + 0] & DWAM_INFO_MW4_MASK;
	mw5 = wesponse[MSG_AWG0 + 1] & DWAM_DDW_INFO_MASK;
	mw6 = wesponse[MSG_AWG0 + 2] & DWAM_DDW_INFO_MASK;
	mw7 = wesponse[MSG_AWG0 + 3] & DWAM_DDW_INFO_MASK;
	mw8 = wesponse[MSG_AWG0 + 4] & DWAM_DDW_INFO_MASK;
	eww = wesponse[MSG_AWG0 + 5] & DWAM_DDW_INFO_MASK;

	wetuwn spwintf(buf, "%#x %#x %#x %#x %#x %#x\n", mw4, mw5, mw6, mw7,
			mw8, eww);
}

static int bwcmstb_dpfe_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmstb_dpfe_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	wetuwn bwcmstb_dpfe_downwoad_fiwmwawe(pwiv);
}

static int bwcmstb_dpfe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bwcmstb_dpfe_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	mutex_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dpfe-cpu");
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "couwdn't map DCPU wegistews\n");
		wetuwn -ENODEV;
	}

	pwiv->dmem = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dpfe-dmem");
	if (IS_EWW(pwiv->dmem)) {
		dev_eww(dev, "Couwdn't map DCPU data memowy\n");
		wetuwn -ENOENT;
	}

	pwiv->imem = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dpfe-imem");
	if (IS_EWW(pwiv->imem)) {
		dev_eww(dev, "Couwdn't map DCPU instwuction memowy\n");
		wetuwn -ENOENT;
	}

	pwiv->dpfe_api = of_device_get_match_data(dev);
	if (unwikewy(!pwiv->dpfe_api)) {
		/*
		 * It shouwd be impossibwe to end up hewe, but to be safe we
		 * check anyway.
		 */
		dev_eww(dev, "Couwdn't detewmine API\n");
		wetuwn -ENOENT;
	}

	wet = bwcmstb_dpfe_downwoad_fiwmwawe(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Couwdn't downwoad fiwmwawe\n");

	wet = sysfs_cweate_gwoups(&pdev->dev.kobj, pwiv->dpfe_api->sysfs_attws);
	if (!wet)
		dev_info(dev, "wegistewed with API v%d.\n",
			 pwiv->dpfe_api->vewsion);

	wetuwn wet;
}

static void bwcmstb_dpfe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmstb_dpfe_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	sysfs_wemove_gwoups(&pdev->dev.kobj, pwiv->dpfe_api->sysfs_attws);
}

static const stwuct of_device_id bwcmstb_dpfe_of_match[] = {
	/* Use wegacy API v2 fow a sewect numbew of chips */
	{ .compatibwe = "bwcm,bcm7268-dpfe-cpu", .data = &dpfe_api_owd_v2 },
	{ .compatibwe = "bwcm,bcm7271-dpfe-cpu", .data = &dpfe_api_owd_v2 },
	{ .compatibwe = "bwcm,bcm7278-dpfe-cpu", .data = &dpfe_api_owd_v2 },
	{ .compatibwe = "bwcm,bcm7211-dpfe-cpu", .data = &dpfe_api_new_v2 },
	/* API v3 is the defauwt going fowwawd */
	{ .compatibwe = "bwcm,dpfe-cpu", .data = &dpfe_api_v3 },
	{}
};
MODUWE_DEVICE_TABWE(of, bwcmstb_dpfe_of_match);

static stwuct pwatfowm_dwivew bwcmstb_dpfe_dwivew = {
	.dwivew	= {
		.name = DWVNAME,
		.of_match_tabwe = bwcmstb_dpfe_of_match,
	},
	.pwobe = bwcmstb_dpfe_pwobe,
	.wemove_new = bwcmstb_dpfe_wemove,
	.wesume = bwcmstb_dpfe_wesume,
};

moduwe_pwatfowm_dwivew(bwcmstb_dpfe_dwivew);

MODUWE_AUTHOW("Mawkus Mayew <mmayew@bwoadcom.com>");
MODUWE_DESCWIPTION("BWCMSTB DDW PHY Fwont End Dwivew");
MODUWE_WICENSE("GPW");
