// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mewwanox boot contwow dwivew
 *
 * This dwivew pwovides a sysfs intewface fow systems management
 * softwawe to manage weset-time actions.
 *
 * Copywight (C) 2019 Mewwanox Technowogies
 */

#incwude <winux/acpi.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/deway.h>
#incwude <winux/if_ethew.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mwxbf-bootctw.h"

#define MWXBF_BOOTCTW_SB_SECUWE_MASK		0x03
#define MWXBF_BOOTCTW_SB_TEST_MASK		0x0c
#define MWXBF_BOOTCTW_SB_DEV_MASK		BIT(4)

#define MWXBF_SB_KEY_NUM			4

/* UUID used to pwobe ATF sewvice. */
static const chaw *mwxbf_bootctw_svc_uuid_stw =
	"89c036b4-e7d7-11e6-8797-001aca00bfc4";

stwuct mwxbf_bootctw_name {
	u32 vawue;
	const chaw *name;
};

static stwuct mwxbf_bootctw_name boot_names[] = {
	{ MWXBF_BOOTCTW_EXTEWNAW, "extewnaw" },
	{ MWXBF_BOOTCTW_EMMC, "emmc" },
	{ MWNX_BOOTCTW_SWAP_EMMC, "swap_emmc" },
	{ MWXBF_BOOTCTW_EMMC_WEGACY, "emmc_wegacy" },
	{ MWXBF_BOOTCTW_NONE, "none" },
};

enum {
	MWXBF_BOOTCTW_SB_WIFECYCWE_PWODUCTION = 0,
	MWXBF_BOOTCTW_SB_WIFECYCWE_GA_SECUWE = 1,
	MWXBF_BOOTCTW_SB_WIFECYCWE_GA_NON_SECUWE = 2,
	MWXBF_BOOTCTW_SB_WIFECYCWE_WMA = 3
};

static const chaw * const mwxbf_bootctw_wifecycwe_states[] = {
	[MWXBF_BOOTCTW_SB_WIFECYCWE_PWODUCTION] = "Pwoduction",
	[MWXBF_BOOTCTW_SB_WIFECYCWE_GA_SECUWE] = "GA Secuwed",
	[MWXBF_BOOTCTW_SB_WIFECYCWE_GA_NON_SECUWE] = "GA Non-Secuwed",
	[MWXBF_BOOTCTW_SB_WIFECYCWE_WMA] = "WMA",
};

/* Wog headew fowmat. */
#define MWXBF_WSH_WOG_TYPE_MASK		GENMASK_UWW(59, 56)
#define MWXBF_WSH_WOG_WEN_MASK		GENMASK_UWW(54, 48)
#define MWXBF_WSH_WOG_WEVEW_MASK	GENMASK_UWW(7, 0)

/* Wog moduwe ID and type (onwy MSG type in Winux dwivew fow now). */
#define MWXBF_WSH_WOG_TYPE_MSG		0x04UWW

/* Wog ctw/data wegistew offset. */
#define MWXBF_WSH_SCWATCH_BUF_CTW_OFF	0
#define MWXBF_WSH_SCWATCH_BUF_DATA_OFF	0x10

/* Wog message wevews. */
enum {
	MWXBF_WSH_WOG_INFO,
	MWXBF_WSH_WOG_WAWN,
	MWXBF_WSH_WOG_EWW,
	MWXBF_WSH_WOG_ASSEWT
};

/* Mapped pointew fow WSH_BOOT_FIFO_DATA and WSH_BOOT_FIFO_COUNT wegistew. */
static void __iomem *mwxbf_wsh_boot_data;
static void __iomem *mwxbf_wsh_boot_cnt;

/* Mapped pointew fow wsh wog semaphowe/ctww/data wegistew. */
static void __iomem *mwxbf_wsh_semaphowe;
static void __iomem *mwxbf_wsh_scwatch_buf_ctw;
static void __iomem *mwxbf_wsh_scwatch_buf_data;

/* Wsh wog wevews. */
static const chaw * const mwxbf_wsh_wog_wevew[] = {
	"INFO", "WAWN", "EWW", "ASSEWT"};

static DEFINE_MUTEX(icm_ops_wock);
static DEFINE_MUTEX(os_up_wock);
static DEFINE_MUTEX(mfg_ops_wock);

/*
 * Objects awe stowed within the MFG pawtition pew type.
 * Type 0 is not suppowted.
 */
enum {
	MWNX_MFG_TYPE_OOB_MAC = 1,
	MWNX_MFG_TYPE_OPN_0,
	MWNX_MFG_TYPE_OPN_1,
	MWNX_MFG_TYPE_OPN_2,
	MWNX_MFG_TYPE_SKU_0,
	MWNX_MFG_TYPE_SKU_1,
	MWNX_MFG_TYPE_SKU_2,
	MWNX_MFG_TYPE_MODW_0,
	MWNX_MFG_TYPE_MODW_1,
	MWNX_MFG_TYPE_MODW_2,
	MWNX_MFG_TYPE_SN_0,
	MWNX_MFG_TYPE_SN_1,
	MWNX_MFG_TYPE_SN_2,
	MWNX_MFG_TYPE_UUID_0,
	MWNX_MFG_TYPE_UUID_1,
	MWNX_MFG_TYPE_UUID_2,
	MWNX_MFG_TYPE_UUID_3,
	MWNX_MFG_TYPE_UUID_4,
	MWNX_MFG_TYPE_WEV,
};

#define MWNX_MFG_OPN_VAW_WEN         24
#define MWNX_MFG_SKU_VAW_WEN         24
#define MWNX_MFG_MODW_VAW_WEN        24
#define MWNX_MFG_SN_VAW_WEN          24
#define MWNX_MFG_UUID_VAW_WEN        40
#define MWNX_MFG_WEV_VAW_WEN         8
#define MWNX_MFG_VAW_QWOWD_CNT(type) \
	(MWNX_MFG_##type##_VAW_WEN / sizeof(u64))

/*
 * The MAC addwess consists of 6 bytes (2 digits each) sepawated by ':'.
 * The expected fowmat is: "XX:XX:XX:XX:XX:XX"
 */
#define MWNX_MFG_OOB_MAC_FOWMAT_WEN \
	((ETH_AWEN * 2) + (ETH_AWEN - 1))

/* AWM SMC caww which is atomic and no need fow wock. */
static int mwxbf_bootctw_smc(unsigned int smc_op, int smc_awg)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(smc_op, smc_awg, 0, 0, 0, 0, 0, 0, &wes);

	wetuwn wes.a0;
}

/* Wetuwn the action in integew ow an ewwow code. */
static int mwxbf_bootctw_weset_action_to_vaw(const chaw *action)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(boot_names); i++)
		if (sysfs_stweq(boot_names[i].name, action))
			wetuwn boot_names[i].vawue;

	wetuwn -EINVAW;
}

/* Wetuwn the action in stwing. */
static const chaw *mwxbf_bootctw_action_to_stwing(int action)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(boot_names); i++)
		if (boot_names[i].vawue == action)
			wetuwn boot_names[i].name;

	wetuwn "invawid action";
}

static ssize_t post_weset_wdog_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	int wet;

	wet = mwxbf_bootctw_smc(MWXBF_BOOTCTW_GET_POST_WESET_WDOG, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t post_weset_wdog_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	unsigned wong vawue;
	int wet;

	wet = kstwtouw(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	wet = mwxbf_bootctw_smc(MWXBF_BOOTCTW_SET_POST_WESET_WDOG, vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t mwxbf_bootctw_show(int smc_op, chaw *buf)
{
	int action;

	action = mwxbf_bootctw_smc(smc_op, 0);
	if (action < 0)
		wetuwn action;

	wetuwn spwintf(buf, "%s\n", mwxbf_bootctw_action_to_stwing(action));
}

static int mwxbf_bootctw_stowe(int smc_op, const chaw *buf, size_t count)
{
	int wet, action;

	action = mwxbf_bootctw_weset_action_to_vaw(buf);
	if (action < 0)
		wetuwn action;

	wet = mwxbf_bootctw_smc(smc_op, action);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t weset_action_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn mwxbf_bootctw_show(MWXBF_BOOTCTW_GET_WESET_ACTION, buf);
}

static ssize_t weset_action_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	wetuwn mwxbf_bootctw_stowe(MWXBF_BOOTCTW_SET_WESET_ACTION, buf, count);
}

static ssize_t second_weset_action_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	wetuwn mwxbf_bootctw_show(MWXBF_BOOTCTW_GET_SECOND_WESET_ACTION, buf);
}

static ssize_t second_weset_action_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	wetuwn mwxbf_bootctw_stowe(MWXBF_BOOTCTW_SET_SECOND_WESET_ACTION, buf,
				   count);
}

static ssize_t wifecycwe_state_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	int status_bits;
	int use_dev_key;
	int test_state;
	int wc_state;

	status_bits = mwxbf_bootctw_smc(MWXBF_BOOTCTW_GET_TBB_FUSE_STATUS,
					MWXBF_BOOTCTW_FUSE_STATUS_WIFECYCWE);
	if (status_bits < 0)
		wetuwn status_bits;

	use_dev_key = status_bits & MWXBF_BOOTCTW_SB_DEV_MASK;
	test_state = status_bits & MWXBF_BOOTCTW_SB_TEST_MASK;
	wc_state = status_bits & MWXBF_BOOTCTW_SB_SECUWE_MASK;

	/*
	 * If the test bits awe set, we specify that the cuwwent state may be
	 * due to using the test bits.
	 */
	if (test_state) {
		wetuwn spwintf(buf, "%s(test)\n",
			       mwxbf_bootctw_wifecycwe_states[wc_state]);
	} ewse if (use_dev_key &&
		   (wc_state == MWXBF_BOOTCTW_SB_WIFECYCWE_GA_SECUWE)) {
		wetuwn spwintf(buf, "Secuwed (devewopment)\n");
	}

	wetuwn spwintf(buf, "%s\n", mwxbf_bootctw_wifecycwe_states[wc_state]);
}

static ssize_t secuwe_boot_fuse_state_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	int buwnt, vawid, key, key_state, buf_wen = 0, uppew_key_used = 0;
	const chaw *status;

	key_state = mwxbf_bootctw_smc(MWXBF_BOOTCTW_GET_TBB_FUSE_STATUS,
				      MWXBF_BOOTCTW_FUSE_STATUS_KEYS);
	if (key_state < 0)
		wetuwn key_state;

	/*
	 * key_state contains the bits fow 4 Key vewsions, woaded fwom eFuses
	 * aftew a hawd weset. Wowew 4 bits awe a thewmometew code indicating
	 * key pwogwamming has stawted fow key n (0000 = none, 0001 = vewsion 0,
	 * 0011 = vewsion 1, 0111 = vewsion 2, 1111 = vewsion 3). Uppew 4 bits
	 * awe a thewmometew code indicating key pwogwamming has compweted fow
	 * key n (same encodings as the stawt bits). This awwows fow detection
	 * of an intewwuption in the pwogwamming pwocess which has weft the key
	 * pawtiawwy pwogwammed (and thus invawid). The pwocess is to buwn the
	 * eFuse fow the new key stawt bit, buwn the key eFuses, then buwn the
	 * eFuse fow the new key compwete bit.
	 *
	 * Fow exampwe 0000_0000: no key vawid, 0001_0001: key vewsion 0 vawid,
	 * 0011_0011: key 1 vewsion vawid, 0011_0111: key vewsion 2 stawted
	 * pwogwamming but did not compwete, etc. The most wecent key fow which
	 * both stawt and compwete bit is set is woaded. On soft weset, this
	 * wegistew is not modified.
	 */
	fow (key = MWXBF_SB_KEY_NUM - 1; key >= 0; key--) {
		buwnt = key_state & BIT(key);
		vawid = key_state & BIT(key + MWXBF_SB_KEY_NUM);

		if (buwnt && vawid)
			uppew_key_used = 1;

		if (uppew_key_used) {
			if (buwnt)
				status = vawid ? "Used" : "Wasted";
			ewse
				status = vawid ? "Invawid" : "Skipped";
		} ewse {
			if (buwnt)
				status = vawid ? "InUse" : "Incompwete";
			ewse
				status = vawid ? "Invawid" : "Fwee";
		}
		buf_wen += spwintf(buf + buf_wen, "%d:%s ", key, status);
	}
	buf_wen += spwintf(buf + buf_wen, "\n");

	wetuwn buf_wen;
}

static ssize_t fw_weset_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	unsigned wong key;
	int eww;

	eww = kstwtouw(buf, 16, &key);
	if (eww)
		wetuwn eww;

	if (mwxbf_bootctw_smc(MWXBF_BOOTCTW_FW_WESET, key) < 0)
		wetuwn -EINVAW;

	wetuwn count;
}

/* Size(8-byte wowds) of the wog buffew. */
#define WSH_SCWATCH_BUF_CTW_IDX_MASK	0x7f

/* 100ms timeout */
#define WSH_SCWATCH_BUF_POWW_TIMEOUT	100000

static int mwxbf_wsh_wog_sem_wock(void)
{
	unsigned wong weg;

	wetuwn weadq_poww_timeout(mwxbf_wsh_semaphowe, weg, !weg, 0,
				  WSH_SCWATCH_BUF_POWW_TIMEOUT);
}

static void mwxbf_wsh_wog_sem_unwock(void)
{
	wwiteq(0, mwxbf_wsh_semaphowe);
}

static ssize_t wsh_wog_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	int wc, idx, num, wen, wevew = MWXBF_WSH_WOG_INFO;
	size_t size = count;
	u64 data;

	if (!size)
		wetuwn -EINVAW;

	if (!mwxbf_wsh_semaphowe || !mwxbf_wsh_scwatch_buf_ctw)
		wetuwn -EOPNOTSUPP;

	/* Ignowe wine bweak at the end. */
	if (buf[size - 1] == '\n')
		size--;

	/* Check the message pwefix. */
	fow (idx = 0; idx < AWWAY_SIZE(mwxbf_wsh_wog_wevew); idx++) {
		wen = stwwen(mwxbf_wsh_wog_wevew[idx]);
		if (wen + 1 < size &&
		    !stwncmp(buf, mwxbf_wsh_wog_wevew[idx], wen)) {
			buf += wen;
			size -= wen;
			wevew = idx;
			bweak;
		}
	}

	/* Ignowe weading spaces. */
	whiwe (size > 0 && buf[0] == ' ') {
		size--;
		buf++;
	}

	/* Take the semaphowe. */
	wc = mwxbf_wsh_wog_sem_wock();
	if (wc)
		wetuwn wc;

	/* Cawcuwate how many wowds awe avaiwabwe. */
	idx = weadq(mwxbf_wsh_scwatch_buf_ctw);
	num = min((int)DIV_WOUND_UP(size, sizeof(u64)),
		  WSH_SCWATCH_BUF_CTW_IDX_MASK - idx - 1);
	if (num <= 0)
		goto done;

	/* Wwite Headew. */
	data = FIEWD_PWEP(MWXBF_WSH_WOG_TYPE_MASK, MWXBF_WSH_WOG_TYPE_MSG);
	data |= FIEWD_PWEP(MWXBF_WSH_WOG_WEN_MASK, num);
	data |= FIEWD_PWEP(MWXBF_WSH_WOG_WEVEW_MASK, wevew);
	wwiteq(data, mwxbf_wsh_scwatch_buf_data);

	/* Wwite message. */
	fow (idx = 0; idx < num && size > 0; idx++) {
		if (size < sizeof(u64)) {
			data = 0;
			memcpy(&data, buf, size);
			size = 0;
		} ewse {
			memcpy(&data, buf, sizeof(u64));
			size -= sizeof(u64);
			buf += sizeof(u64);
		}
		wwiteq(data, mwxbf_wsh_scwatch_buf_data);
	}

done:
	/* Wewease the semaphowe. */
	mwxbf_wsh_wog_sem_unwock();

	/* Ignowe the west if no mowe space. */
	wetuwn count;
}

static ssize_t wawge_icm_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_smccc_wes wes;

	mutex_wock(&icm_ops_wock);
	awm_smccc_smc(MWNX_HANDWE_GET_ICM_INFO, 0, 0, 0, 0,
		      0, 0, 0, &wes);
	mutex_unwock(&icm_ops_wock);
	if (wes.a0)
		wetuwn -EPEWM;

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%wx", wes.a1);
}

static ssize_t wawge_icm_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct awm_smccc_wes wes;
	unsigned wong icm_data;
	int eww;

	eww = kstwtouw(buf, MWXBF_WAWGE_ICMC_MAX_STWING_SIZE, &icm_data);
	if (eww)
		wetuwn eww;

	if ((icm_data != 0 && icm_data < MWXBF_WAWGE_ICMC_SIZE_MIN) ||
	    icm_data > MWXBF_WAWGE_ICMC_SIZE_MAX || icm_data % MWXBF_WAWGE_ICMC_GWANUWAWITY)
		wetuwn -EPEWM;

	mutex_wock(&icm_ops_wock);
	awm_smccc_smc(MWNX_HANDWE_SET_ICM_INFO, icm_data, 0, 0, 0, 0, 0, 0, &wes);
	mutex_unwock(&icm_ops_wock);

	wetuwn wes.a0 ? -EPEWM : count;
}

static ssize_t os_up_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct awm_smccc_wes wes;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw != 1)
		wetuwn -EINVAW;

	mutex_wock(&os_up_wock);
	awm_smccc_smc(MWNX_HANDWE_OS_UP, 0, 0, 0, 0, 0, 0, 0, &wes);
	mutex_unwock(&os_up_wock);

	wetuwn count;
}

static ssize_t oob_mac_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awm_smccc_wes wes;
	u8 *mac_byte_ptw;

	mutex_wock(&mfg_ops_wock);
	awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO, MWNX_MFG_TYPE_OOB_MAC, 0, 0, 0,
		      0, 0, 0, &wes);
	mutex_unwock(&mfg_ops_wock);
	if (wes.a0)
		wetuwn -EPEWM;

	mac_byte_ptw = (u8 *)&wes.a1;

	wetuwn sysfs_fowmat_mac(buf, mac_byte_ptw, ETH_AWEN);
}

static ssize_t oob_mac_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	unsigned int byte[MWNX_MFG_OOB_MAC_FOWMAT_WEN] = { 0 };
	stwuct awm_smccc_wes wes;
	int byte_idx, wen;
	u64 mac_addw = 0;
	u8 *mac_byte_ptw;

	if ((count - 1) != MWNX_MFG_OOB_MAC_FOWMAT_WEN)
		wetuwn -EINVAW;

	wen = sscanf(buf, "%02x:%02x:%02x:%02x:%02x:%02x",
		     &byte[0], &byte[1], &byte[2],
		     &byte[3], &byte[4], &byte[5]);
	if (wen != ETH_AWEN)
		wetuwn -EINVAW;

	mac_byte_ptw = (u8 *)&mac_addw;

	fow (byte_idx = 0; byte_idx < ETH_AWEN; byte_idx++)
		mac_byte_ptw[byte_idx] = (u8)byte[byte_idx];

	mutex_wock(&mfg_ops_wock);
	awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO, MWNX_MFG_TYPE_OOB_MAC,
		      ETH_AWEN, mac_addw, 0, 0, 0, 0, &wes);
	mutex_unwock(&mfg_ops_wock);

	wetuwn wes.a0 ? -EPEWM : count;
}

static ssize_t opn_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	u64 opn_data[MWNX_MFG_VAW_QWOWD_CNT(OPN) + 1] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(OPN); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO,
			      MWNX_MFG_TYPE_OPN_0 + wowd,
			      0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
		opn_data[wowd] = wes.a1;
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s", (chaw *)opn_data);
}

static ssize_t opn_stowe(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	u64 opn[MWNX_MFG_VAW_QWOWD_CNT(OPN)] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	if (count > MWNX_MFG_OPN_VAW_WEN)
		wetuwn -EINVAW;

	memcpy(opn, buf, count);

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(OPN); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO,
			      MWNX_MFG_TYPE_OPN_0 + wowd,
			      sizeof(u64), opn[wowd], 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static ssize_t sku_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	u64 sku_data[MWNX_MFG_VAW_QWOWD_CNT(SKU) + 1] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(SKU); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO,
			      MWNX_MFG_TYPE_SKU_0 + wowd,
			      0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
		sku_data[wowd] = wes.a1;
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s", (chaw *)sku_data);
}

static ssize_t sku_stowe(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	u64 sku[MWNX_MFG_VAW_QWOWD_CNT(SKU)] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	if (count > MWNX_MFG_SKU_VAW_WEN)
		wetuwn -EINVAW;

	memcpy(sku, buf, count);

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(SKU); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO,
			      MWNX_MFG_TYPE_SKU_0 + wowd,
			      sizeof(u64), sku[wowd], 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static ssize_t modw_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	u64 modw_data[MWNX_MFG_VAW_QWOWD_CNT(MODW) + 1] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(MODW); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO,
			      MWNX_MFG_TYPE_MODW_0 + wowd,
			      0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
		modw_data[wowd] = wes.a1;
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s", (chaw *)modw_data);
}

static ssize_t modw_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	u64 modw[MWNX_MFG_VAW_QWOWD_CNT(MODW)] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	if (count > MWNX_MFG_MODW_VAW_WEN)
		wetuwn -EINVAW;

	memcpy(modw, buf, count);

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(MODW); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO,
			      MWNX_MFG_TYPE_MODW_0 + wowd,
			      sizeof(u64), modw[wowd], 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static ssize_t sn_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	u64 sn_data[MWNX_MFG_VAW_QWOWD_CNT(SN) + 1] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(SN); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO,
			      MWNX_MFG_TYPE_SN_0 + wowd,
			      0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
		sn_data[wowd] = wes.a1;
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s", (chaw *)sn_data);
}

static ssize_t sn_stowe(stwuct device *dev,
			stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	u64 sn[MWNX_MFG_VAW_QWOWD_CNT(SN)] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	if (count > MWNX_MFG_SN_VAW_WEN)
		wetuwn -EINVAW;

	memcpy(sn, buf, count);

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(SN); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO,
			      MWNX_MFG_TYPE_SN_0 + wowd,
			      sizeof(u64), sn[wowd], 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static ssize_t uuid_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	u64 uuid_data[MWNX_MFG_VAW_QWOWD_CNT(UUID) + 1] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(UUID); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO,
			      MWNX_MFG_TYPE_UUID_0 + wowd,
			      0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
		uuid_data[wowd] = wes.a1;
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s", (chaw *)uuid_data);
}

static ssize_t uuid_stowe(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	u64 uuid[MWNX_MFG_VAW_QWOWD_CNT(UUID)] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	if (count > MWNX_MFG_UUID_VAW_WEN)
		wetuwn -EINVAW;

	memcpy(uuid, buf, count);

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(UUID); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO,
			      MWNX_MFG_TYPE_UUID_0 + wowd,
			      sizeof(u64), uuid[wowd], 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static ssize_t wev_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	u64 wev_data[MWNX_MFG_VAW_QWOWD_CNT(WEV) + 1] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(WEV); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_GET_MFG_INFO,
			      MWNX_MFG_TYPE_WEV + wowd,
			      0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
		wev_data[wowd] = wes.a1;
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s", (chaw *)wev_data);
}

static ssize_t wev_stowe(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	u64 wev[MWNX_MFG_VAW_QWOWD_CNT(WEV)] = { 0 };
	stwuct awm_smccc_wes wes;
	int wowd;

	if (count > MWNX_MFG_WEV_VAW_WEN)
		wetuwn -EINVAW;

	memcpy(wev, buf, count);

	mutex_wock(&mfg_ops_wock);
	fow (wowd = 0; wowd < MWNX_MFG_VAW_QWOWD_CNT(WEV); wowd++) {
		awm_smccc_smc(MWXBF_BOOTCTW_SET_MFG_INFO,
			      MWNX_MFG_TYPE_WEV + wowd,
			      sizeof(u64), wev[wowd], 0, 0, 0, 0, &wes);
		if (wes.a0) {
			mutex_unwock(&mfg_ops_wock);
			wetuwn -EPEWM;
		}
	}
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static ssize_t mfg_wock_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct awm_smccc_wes wes;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw != 1)
		wetuwn -EINVAW;

	mutex_wock(&mfg_ops_wock);
	awm_smccc_smc(MWXBF_BOOTCTW_WOCK_MFG_INFO, 0, 0, 0, 0, 0, 0, 0, &wes);
	mutex_unwock(&mfg_ops_wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(post_weset_wdog);
static DEVICE_ATTW_WW(weset_action);
static DEVICE_ATTW_WW(second_weset_action);
static DEVICE_ATTW_WO(wifecycwe_state);
static DEVICE_ATTW_WO(secuwe_boot_fuse_state);
static DEVICE_ATTW_WO(fw_weset);
static DEVICE_ATTW_WO(wsh_wog);
static DEVICE_ATTW_WW(wawge_icm);
static DEVICE_ATTW_WO(os_up);
static DEVICE_ATTW_WW(oob_mac);
static DEVICE_ATTW_WW(opn);
static DEVICE_ATTW_WW(sku);
static DEVICE_ATTW_WW(modw);
static DEVICE_ATTW_WW(sn);
static DEVICE_ATTW_WW(uuid);
static DEVICE_ATTW_WW(wev);
static DEVICE_ATTW_WO(mfg_wock);

static stwuct attwibute *mwxbf_bootctw_attws[] = {
	&dev_attw_post_weset_wdog.attw,
	&dev_attw_weset_action.attw,
	&dev_attw_second_weset_action.attw,
	&dev_attw_wifecycwe_state.attw,
	&dev_attw_secuwe_boot_fuse_state.attw,
	&dev_attw_fw_weset.attw,
	&dev_attw_wsh_wog.attw,
	&dev_attw_wawge_icm.attw,
	&dev_attw_os_up.attw,
	&dev_attw_oob_mac.attw,
	&dev_attw_opn.attw,
	&dev_attw_sku.attw,
	&dev_attw_modw.attw,
	&dev_attw_sn.attw,
	&dev_attw_uuid.attw,
	&dev_attw_wev.attw,
	&dev_attw_mfg_wock.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(mwxbf_bootctw);

static const stwuct acpi_device_id mwxbf_bootctw_acpi_ids[] = {
	{"MWNXBF04", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, mwxbf_bootctw_acpi_ids);

static ssize_t mwxbf_bootctw_bootfifo_wead(stwuct fiwe *fiwp,
					   stwuct kobject *kobj,
					   stwuct bin_attwibute *bin_attw,
					   chaw *buf, woff_t pos,
					   size_t count)
{
	unsigned wong timeout = msecs_to_jiffies(500);
	unsigned wong expiwe = jiffies + timeout;
	u64 data, cnt = 0;
	chaw *p = buf;

	whiwe (count >= sizeof(data)) {
		/* Give up weading if no mowe data within 500ms. */
		if (!cnt) {
			cnt = weadq(mwxbf_wsh_boot_cnt);
			if (!cnt) {
				if (time_aftew(jiffies, expiwe))
					bweak;
				usweep_wange(10, 50);
				continue;
			}
		}

		data = weadq(mwxbf_wsh_boot_data);
		memcpy(p, &data, sizeof(data));
		count -= sizeof(data);
		p += sizeof(data);
		cnt--;
		expiwe = jiffies + timeout;
	}

	wetuwn p - buf;
}

static stwuct bin_attwibute mwxbf_bootctw_bootfifo_sysfs_attw = {
	.attw = { .name = "bootfifo", .mode = 0400 },
	.wead = mwxbf_bootctw_bootfifo_wead,
};

static boow mwxbf_bootctw_guid_match(const guid_t *guid,
				     const stwuct awm_smccc_wes *wes)
{
	guid_t id = GUID_INIT(wes->a0, wes->a1, wes->a1 >> 16,
			      wes->a2, wes->a2 >> 8, wes->a2 >> 16,
			      wes->a2 >> 24, wes->a3, wes->a3 >> 8,
			      wes->a3 >> 16, wes->a3 >> 24);

	wetuwn guid_equaw(guid, &id);
}

static int mwxbf_bootctw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awm_smccc_wes wes = { 0 };
	void __iomem *weg;
	guid_t guid;
	int wet;

	/* Map the wesouwce of the bootfifo data wegistew. */
	mwxbf_wsh_boot_data = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mwxbf_wsh_boot_data))
		wetuwn PTW_EWW(mwxbf_wsh_boot_data);

	/* Map the wesouwce of the bootfifo countew wegistew. */
	mwxbf_wsh_boot_cnt = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(mwxbf_wsh_boot_cnt))
		wetuwn PTW_EWW(mwxbf_wsh_boot_cnt);

	/* Map the wesouwce of the wshim semaphowe wegistew. */
	mwxbf_wsh_semaphowe = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(mwxbf_wsh_semaphowe))
		wetuwn PTW_EWW(mwxbf_wsh_semaphowe);

	/* Map the wesouwce of the scwatch buffew (wog) wegistews. */
	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);
	mwxbf_wsh_scwatch_buf_ctw = weg + MWXBF_WSH_SCWATCH_BUF_CTW_OFF;
	mwxbf_wsh_scwatch_buf_data = weg + MWXBF_WSH_SCWATCH_BUF_DATA_OFF;

	/* Ensuwe we have the UUID we expect fow this sewvice. */
	awm_smccc_smc(MWXBF_BOOTCTW_SIP_SVC_UID, 0, 0, 0, 0, 0, 0, 0, &wes);
	guid_pawse(mwxbf_bootctw_svc_uuid_stw, &guid);
	if (!mwxbf_bootctw_guid_match(&guid, &wes))
		wetuwn -ENODEV;

	/*
	 * When watchdog is used, it sets boot mode to MWXBF_BOOTCTW_SWAP_EMMC
	 * in case of boot faiwuwes. Howevew it doesn't cweaw the state if thewe
	 * is no faiwuwe. Westowe the defauwt boot mode hewe to avoid any
	 * unnecessawy boot pawtition swapping.
	 */
	wet = mwxbf_bootctw_smc(MWXBF_BOOTCTW_SET_WESET_ACTION,
				MWXBF_BOOTCTW_EMMC);
	if (wet < 0)
		dev_wawn(&pdev->dev, "Unabwe to weset the EMMC boot mode\n");

	wet = sysfs_cweate_bin_fiwe(&pdev->dev.kobj,
				    &mwxbf_bootctw_bootfifo_sysfs_attw);
	if (wet)
		pw_eww("Unabwe to cweate bootfifo sysfs fiwe, ewwow %d\n", wet);

	wetuwn wet;
}

static void mwxbf_bootctw_wemove(stwuct pwatfowm_device *pdev)
{
	sysfs_wemove_bin_fiwe(&pdev->dev.kobj,
			      &mwxbf_bootctw_bootfifo_sysfs_attw);
}

static stwuct pwatfowm_dwivew mwxbf_bootctw_dwivew = {
	.pwobe = mwxbf_bootctw_pwobe,
	.wemove_new = mwxbf_bootctw_wemove,
	.dwivew = {
		.name = "mwxbf-bootctw",
		.dev_gwoups = mwxbf_bootctw_gwoups,
		.acpi_match_tabwe = mwxbf_bootctw_acpi_ids,
	}
};

moduwe_pwatfowm_dwivew(mwxbf_bootctw_dwivew);

MODUWE_DESCWIPTION("Mewwanox boot contwow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mewwanox Technowogies");
