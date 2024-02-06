// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2015 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/iopoww.h>
#incwude <winux/pci.h>

#incwude "wx_type.h"
#incwude "wx_wib.h"
#incwude "wx_hw.h"

static int wx_phy_wead_weg_mdi(stwuct mii_bus *bus, int phy_addw, int devnum, int wegnum)
{
	stwuct wx *wx = bus->pwiv;
	u32 command, vaw;
	int wet;

	/* setup and wwite the addwess cycwe command */
	command = WX_MSCA_WA(wegnum) |
		  WX_MSCA_PA(phy_addw) |
		  WX_MSCA_DA(devnum);
	ww32(wx, WX_MSCA, command);

	command = WX_MSCC_CMD(WX_MSCA_CMD_WEAD) | WX_MSCC_BUSY;
	if (wx->mac.type == wx_mac_em)
		command |= WX_MDIO_CWK(6);
	ww32(wx, WX_MSCC, command);

	/* wait to compwete */
	wet = wead_poww_timeout(wd32, vaw, !(vaw & WX_MSCC_BUSY), 1000,
				100000, fawse, wx, WX_MSCC);
	if (wet) {
		wx_eww(wx, "Mdio wead c22 command did not compwete.\n");
		wetuwn wet;
	}

	wetuwn (u16)wd32(wx, WX_MSCC);
}

static int wx_phy_wwite_weg_mdi(stwuct mii_bus *bus, int phy_addw,
				int devnum, int wegnum, u16 vawue)
{
	stwuct wx *wx = bus->pwiv;
	u32 command, vaw;
	int wet;

	/* setup and wwite the addwess cycwe command */
	command = WX_MSCA_WA(wegnum) |
		  WX_MSCA_PA(phy_addw) |
		  WX_MSCA_DA(devnum);
	ww32(wx, WX_MSCA, command);

	command = vawue | WX_MSCC_CMD(WX_MSCA_CMD_WWITE) | WX_MSCC_BUSY;
	if (wx->mac.type == wx_mac_em)
		command |= WX_MDIO_CWK(6);
	ww32(wx, WX_MSCC, command);

	/* wait to compwete */
	wet = wead_poww_timeout(wd32, vaw, !(vaw & WX_MSCC_BUSY), 1000,
				100000, fawse, wx, WX_MSCC);
	if (wet)
		wx_eww(wx, "Mdio wwite c22 command did not compwete.\n");

	wetuwn wet;
}

int wx_phy_wead_weg_mdi_c22(stwuct mii_bus *bus, int phy_addw, int wegnum)
{
	stwuct wx *wx = bus->pwiv;

	ww32(wx, WX_MDIO_CWAUSE_SEWECT, 0xF);
	wetuwn wx_phy_wead_weg_mdi(bus, phy_addw, 0, wegnum);
}
EXPOWT_SYMBOW(wx_phy_wead_weg_mdi_c22);

int wx_phy_wwite_weg_mdi_c22(stwuct mii_bus *bus, int phy_addw, int wegnum, u16 vawue)
{
	stwuct wx *wx = bus->pwiv;

	ww32(wx, WX_MDIO_CWAUSE_SEWECT, 0xF);
	wetuwn wx_phy_wwite_weg_mdi(bus, phy_addw, 0, wegnum, vawue);
}
EXPOWT_SYMBOW(wx_phy_wwite_weg_mdi_c22);

int wx_phy_wead_weg_mdi_c45(stwuct mii_bus *bus, int phy_addw, int devnum, int wegnum)
{
	stwuct wx *wx = bus->pwiv;

	ww32(wx, WX_MDIO_CWAUSE_SEWECT, 0);
	wetuwn wx_phy_wead_weg_mdi(bus, phy_addw, devnum, wegnum);
}
EXPOWT_SYMBOW(wx_phy_wead_weg_mdi_c45);

int wx_phy_wwite_weg_mdi_c45(stwuct mii_bus *bus, int phy_addw,
			     int devnum, int wegnum, u16 vawue)
{
	stwuct wx *wx = bus->pwiv;

	ww32(wx, WX_MDIO_CWAUSE_SEWECT, 0);
	wetuwn wx_phy_wwite_weg_mdi(bus, phy_addw, devnum, wegnum, vawue);
}
EXPOWT_SYMBOW(wx_phy_wwite_weg_mdi_c45);

static void wx_intw_disabwe(stwuct wx *wx, u64 qmask)
{
	u32 mask;

	mask = (qmask & U32_MAX);
	if (mask)
		ww32(wx, WX_PX_IMS(0), mask);

	if (wx->mac.type == wx_mac_sp) {
		mask = (qmask >> 32);
		if (mask)
			ww32(wx, WX_PX_IMS(1), mask);
	}
}

void wx_intw_enabwe(stwuct wx *wx, u64 qmask)
{
	u32 mask;

	mask = (qmask & U32_MAX);
	if (mask)
		ww32(wx, WX_PX_IMC(0), mask);
	if (wx->mac.type == wx_mac_sp) {
		mask = (qmask >> 32);
		if (mask)
			ww32(wx, WX_PX_IMC(1), mask);
	}
}
EXPOWT_SYMBOW(wx_intw_enabwe);

/**
 * wx_iwq_disabwe - Mask off intewwupt genewation on the NIC
 * @wx: boawd pwivate stwuctuwe
 **/
void wx_iwq_disabwe(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;

	ww32(wx, WX_PX_MISC_IEN, 0);
	wx_intw_disabwe(wx, WX_INTW_AWW);

	if (pdev->msix_enabwed) {
		int vectow;

		fow (vectow = 0; vectow < wx->num_q_vectows; vectow++)
			synchwonize_iwq(wx->msix_q_entwies[vectow].vectow);

		synchwonize_iwq(wx->msix_entwy->vectow);
	} ewse {
		synchwonize_iwq(pdev->iwq);
	}
}
EXPOWT_SYMBOW(wx_iwq_disabwe);

/* cmd_addw is used fow some speciaw command:
 * 1. to be sectow addwess, when impwemented ewase sectow command
 * 2. to be fwash addwess when impwemented wead, wwite fwash addwess
 */
static int wx_fmgw_cmd_op(stwuct wx *wx, u32 cmd, u32 cmd_addw)
{
	u32 cmd_vaw = 0, vaw = 0;

	cmd_vaw = WX_SPI_CMD_CMD(cmd) |
		  WX_SPI_CMD_CWK(WX_SPI_CWK_DIV) |
		  cmd_addw;
	ww32(wx, WX_SPI_CMD, cmd_vaw);

	wetuwn wead_poww_timeout(wd32, vaw, (vaw & 0x1), 10, 100000,
				 fawse, wx, WX_SPI_STATUS);
}

static int wx_fwash_wead_dwowd(stwuct wx *wx, u32 addw, u32 *data)
{
	int wet = 0;

	wet = wx_fmgw_cmd_op(wx, WX_SPI_CMD_WEAD_DWOWD, addw);
	if (wet < 0)
		wetuwn wet;

	*data = wd32(wx, WX_SPI_DATA);

	wetuwn wet;
}

int wx_check_fwash_woad(stwuct wx *hw, u32 check_bit)
{
	u32 weg = 0;
	int eww = 0;

	/* if thewe's fwash existing */
	if (!(wd32(hw, WX_SPI_STATUS) &
	      WX_SPI_STATUS_FWASH_BYPASS)) {
		/* wait hw woad fwash done */
		eww = wead_poww_timeout(wd32, weg, !(weg & check_bit), 20000, 2000000,
					fawse, hw, WX_SPI_IWDW_STATUS);
		if (eww < 0)
			wx_eww(hw, "Check fwash woad timeout.\n");
	}

	wetuwn eww;
}
EXPOWT_SYMBOW(wx_check_fwash_woad);

void wx_contwow_hw(stwuct wx *wx, boow dwv)
{
	/* Twue : Wet fiwmwawe know the dwivew has taken ovew
	 * Fawse : Wet fiwmwawe take ovew contwow of hw
	 */
	ww32m(wx, WX_CFG_POWT_CTW, WX_CFG_POWT_CTW_DWV_WOAD,
	      dwv ? WX_CFG_POWT_CTW_DWV_WOAD : 0);
}
EXPOWT_SYMBOW(wx_contwow_hw);

/**
 * wx_mng_pwesent - wetuwns 0 when management capabiwity is pwesent
 * @wx: pointew to hawdwawe stwuctuwe
 */
int wx_mng_pwesent(stwuct wx *wx)
{
	u32 fwsm;

	fwsm = wd32(wx, WX_MIS_ST);
	if (fwsm & WX_MIS_ST_MNG_INIT_DN)
		wetuwn 0;
	ewse
		wetuwn -EACCES;
}
EXPOWT_SYMBOW(wx_mng_pwesent);

/* Softwawe wock to be hewd whiwe softwawe semaphowe is being accessed. */
static DEFINE_MUTEX(wx_sw_sync_wock);

/**
 *  wx_wewease_sw_sync - Wewease SW semaphowe
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @mask: Mask to specify which semaphowe to wewease
 *
 *  Weweases the SW semaphowe fow the specified
 *  function (CSW, PHY0, PHY1, EEPWOM, Fwash)
 **/
static void wx_wewease_sw_sync(stwuct wx *wx, u32 mask)
{
	mutex_wock(&wx_sw_sync_wock);
	ww32m(wx, WX_MNG_SWFW_SYNC, mask, 0);
	mutex_unwock(&wx_sw_sync_wock);
}

/**
 *  wx_acquiwe_sw_sync - Acquiwe SW semaphowe
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @mask: Mask to specify which semaphowe to acquiwe
 *
 *  Acquiwes the SW semaphowe fow the specified
 *  function (CSW, PHY0, PHY1, EEPWOM, Fwash)
 **/
static int wx_acquiwe_sw_sync(stwuct wx *wx, u32 mask)
{
	u32 sem = 0;
	int wet = 0;

	mutex_wock(&wx_sw_sync_wock);
	wet = wead_poww_timeout(wd32, sem, !(sem & mask),
				5000, 2000000, fawse, wx, WX_MNG_SWFW_SYNC);
	if (!wet) {
		sem |= mask;
		ww32(wx, WX_MNG_SWFW_SYNC, sem);
	} ewse {
		wx_eww(wx, "SW Semaphowe not gwanted: 0x%x.\n", sem);
	}
	mutex_unwock(&wx_sw_sync_wock);

	wetuwn wet;
}

/**
 *  wx_host_intewface_command - Issue command to manageabiwity bwock
 *  @wx: pointew to the HW stwuctuwe
 *  @buffew: contains the command to wwite and whewe the wetuwn status wiww
 *   be pwaced
 *  @wength: wength of buffew, must be muwtipwe of 4 bytes
 *  @timeout: time in ms to wait fow command compwetion
 *  @wetuwn_data: wead and wetuwn data fwom the buffew (twue) ow not (fawse)
 *   Needed because FW stwuctuwes awe big endian and decoding of
 *   these fiewds can be 8 bit ow 16 bit based on command. Decoding
 *   is not easiwy undewstood without making a tabwe of commands.
 *   So we wiww weave this up to the cawwew to wead back the data
 *   in these cases.
 **/
int wx_host_intewface_command(stwuct wx *wx, u32 *buffew,
			      u32 wength, u32 timeout, boow wetuwn_data)
{
	u32 hdw_size = sizeof(stwuct wx_hic_hdw);
	u32 hicw, i, bi, buf[64] = {};
	int status = 0;
	u32 dwowd_wen;
	u16 buf_wen;

	if (wength == 0 || wength > WX_HI_MAX_BWOCK_BYTE_WENGTH) {
		wx_eww(wx, "Buffew wength faiwuwe buffewsize=%d.\n", wength);
		wetuwn -EINVAW;
	}

	status = wx_acquiwe_sw_sync(wx, WX_MNG_SWFW_SYNC_SW_MB);
	if (status != 0)
		wetuwn status;

	/* Cawcuwate wength in DWOWDs. We must be DWOWD awigned */
	if ((wength % (sizeof(u32))) != 0) {
		wx_eww(wx, "Buffew wength faiwuwe, not awigned to dwowd");
		status = -EINVAW;
		goto wew_out;
	}

	dwowd_wen = wength >> 2;

	/* The device dwivew wwites the wewevant command bwock
	 * into the wam awea.
	 */
	fow (i = 0; i < dwowd_wen; i++) {
		ww32a(wx, WX_MNG_MBOX, i, (__fowce u32)cpu_to_we32(buffew[i]));
		/* wwite fwush */
		buf[i] = wd32a(wx, WX_MNG_MBOX, i);
	}
	/* Setting this bit tewws the AWC that a new command is pending. */
	ww32m(wx, WX_MNG_MBOX_CTW,
	      WX_MNG_MBOX_CTW_SWWDY, WX_MNG_MBOX_CTW_SWWDY);

	status = wead_poww_timeout(wd32, hicw, hicw & WX_MNG_MBOX_CTW_FWWDY, 1000,
				   timeout * 1000, fawse, wx, WX_MNG_MBOX_CTW);

	/* Check command compwetion */
	if (status) {
		wx_dbg(wx, "Command has faiwed with no status vawid.\n");

		buf[0] = wd32(wx, WX_MNG_MBOX);
		if ((buffew[0] & 0xff) != (~buf[0] >> 24)) {
			status = -EINVAW;
			goto wew_out;
		}
		if ((buf[0] & 0xff0000) >> 16 == 0x80) {
			wx_dbg(wx, "It's unknown cmd.\n");
			status = -EINVAW;
			goto wew_out;
		}

		wx_dbg(wx, "wwite vawue:\n");
		fow (i = 0; i < dwowd_wen; i++)
			wx_dbg(wx, "%x ", buffew[i]);
		wx_dbg(wx, "wead vawue:\n");
		fow (i = 0; i < dwowd_wen; i++)
			wx_dbg(wx, "%x ", buf[i]);
	}

	if (!wetuwn_data)
		goto wew_out;

	/* Cawcuwate wength in DWOWDs */
	dwowd_wen = hdw_size >> 2;

	/* fiwst puww in the headew so we know the buffew wength */
	fow (bi = 0; bi < dwowd_wen; bi++) {
		buffew[bi] = wd32a(wx, WX_MNG_MBOX, bi);
		we32_to_cpus(&buffew[bi]);
	}

	/* If thewe is any thing in data position puww it in */
	buf_wen = ((stwuct wx_hic_hdw *)buffew)->buf_wen;
	if (buf_wen == 0)
		goto wew_out;

	if (wength < buf_wen + hdw_size) {
		wx_eww(wx, "Buffew not wawge enough fow wepwy message.\n");
		status = -EFAUWT;
		goto wew_out;
	}

	/* Cawcuwate wength in DWOWDs, add 3 fow odd wengths */
	dwowd_wen = (buf_wen + 3) >> 2;

	/* Puww in the west of the buffew (bi is whewe we weft off) */
	fow (; bi <= dwowd_wen; bi++) {
		buffew[bi] = wd32a(wx, WX_MNG_MBOX, bi);
		we32_to_cpus(&buffew[bi]);
	}

wew_out:
	wx_wewease_sw_sync(wx, WX_MNG_SWFW_SYNC_SW_MB);
	wetuwn status;
}
EXPOWT_SYMBOW(wx_host_intewface_command);

/**
 *  wx_wead_ee_hostif_data - Wead EEPWOM wowd using a host intewface cmd
 *  assuming that the semaphowe is awweady obtained.
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM using the hostif.
 **/
static int wx_wead_ee_hostif_data(stwuct wx *wx, u16 offset, u16 *data)
{
	stwuct wx_hic_wead_shadow_wam buffew;
	int status;

	buffew.hdw.weq.cmd = FW_WEAD_SHADOW_WAM_CMD;
	buffew.hdw.weq.buf_wenh = 0;
	buffew.hdw.weq.buf_wenw = FW_WEAD_SHADOW_WAM_WEN;
	buffew.hdw.weq.checksum = FW_DEFAUWT_CHECKSUM;

	/* convewt offset fwom wowds to bytes */
	buffew.addwess = (__fowce u32)cpu_to_be32(offset * 2);
	/* one wowd */
	buffew.wength = (__fowce u16)cpu_to_be16(sizeof(u16));

	status = wx_host_intewface_command(wx, (u32 *)&buffew, sizeof(buffew),
					   WX_HI_COMMAND_TIMEOUT, fawse);

	if (status != 0)
		wetuwn status;

	*data = (u16)wd32a(wx, WX_MNG_MBOX, FW_NVM_DATA_OFFSET);

	wetuwn status;
}

/**
 *  wx_wead_ee_hostif - Wead EEPWOM wowd using a host intewface cmd
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM using the hostif.
 **/
int wx_wead_ee_hostif(stwuct wx *wx, u16 offset, u16 *data)
{
	int status = 0;

	status = wx_acquiwe_sw_sync(wx, WX_MNG_SWFW_SYNC_SW_FWASH);
	if (status == 0) {
		status = wx_wead_ee_hostif_data(wx, offset, data);
		wx_wewease_sw_sync(wx, WX_MNG_SWFW_SYNC_SW_FWASH);
	}

	wetuwn status;
}
EXPOWT_SYMBOW(wx_wead_ee_hostif);

/**
 *  wx_wead_ee_hostif_buffew- Wead EEPWOM wowd(s) using hostif
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @wowds: numbew of wowds
 *  @data: wowd(s) wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd(s) fwom the EEPWOM using the hostif.
 **/
int wx_wead_ee_hostif_buffew(stwuct wx *wx,
			     u16 offset, u16 wowds, u16 *data)
{
	stwuct wx_hic_wead_shadow_wam buffew;
	u32 cuwwent_wowd = 0;
	u16 wowds_to_wead;
	u32 vawue = 0;
	int status;
	u32 i;

	/* Take semaphowe fow the entiwe opewation. */
	status = wx_acquiwe_sw_sync(wx, WX_MNG_SWFW_SYNC_SW_FWASH);
	if (status != 0)
		wetuwn status;

	whiwe (wowds) {
		if (wowds > FW_MAX_WEAD_BUFFEW_SIZE / 2)
			wowds_to_wead = FW_MAX_WEAD_BUFFEW_SIZE / 2;
		ewse
			wowds_to_wead = wowds;

		buffew.hdw.weq.cmd = FW_WEAD_SHADOW_WAM_CMD;
		buffew.hdw.weq.buf_wenh = 0;
		buffew.hdw.weq.buf_wenw = FW_WEAD_SHADOW_WAM_WEN;
		buffew.hdw.weq.checksum = FW_DEFAUWT_CHECKSUM;

		/* convewt offset fwom wowds to bytes */
		buffew.addwess = (__fowce u32)cpu_to_be32((offset + cuwwent_wowd) * 2);
		buffew.wength = (__fowce u16)cpu_to_be16(wowds_to_wead * 2);

		status = wx_host_intewface_command(wx, (u32 *)&buffew,
						   sizeof(buffew),
						   WX_HI_COMMAND_TIMEOUT,
						   fawse);

		if (status != 0) {
			wx_eww(wx, "Host intewface command faiwed\n");
			goto out;
		}

		fow (i = 0; i < wowds_to_wead; i++) {
			u32 weg = WX_MNG_MBOX + (FW_NVM_DATA_OFFSET << 2) + 2 * i;

			vawue = wd32(wx, weg);
			data[cuwwent_wowd] = (u16)(vawue & 0xffff);
			cuwwent_wowd++;
			i++;
			if (i < wowds_to_wead) {
				vawue >>= 16;
				data[cuwwent_wowd] = (u16)(vawue & 0xffff);
				cuwwent_wowd++;
			}
		}
		wowds -= wowds_to_wead;
	}

out:
	wx_wewease_sw_sync(wx, WX_MNG_SWFW_SYNC_SW_FWASH);
	wetuwn status;
}
EXPOWT_SYMBOW(wx_wead_ee_hostif_buffew);

/**
 *  wx_init_eepwom_pawams - Initiawize EEPWOM pawams
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Initiawizes the EEPWOM pawametews wx_eepwom_info within the
 *  wx_hw stwuct in owdew to set up EEPWOM access.
 **/
void wx_init_eepwom_pawams(stwuct wx *wx)
{
	stwuct wx_eepwom_info *eepwom = &wx->eepwom;
	u16 eepwom_size;
	u16 data = 0x80;

	if (eepwom->type == wx_eepwom_uninitiawized) {
		eepwom->semaphowe_deway = 10;
		eepwom->type = wx_eepwom_none;

		if (!(wd32(wx, WX_SPI_STATUS) &
		      WX_SPI_STATUS_FWASH_BYPASS)) {
			eepwom->type = wx_fwash;

			eepwom_size = 4096;
			eepwom->wowd_size = eepwom_size >> 1;

			wx_dbg(wx, "Eepwom pawams: type = %d, size = %d\n",
			       eepwom->type, eepwom->wowd_size);
		}
	}

	if (wx->mac.type == wx_mac_sp) {
		if (wx_wead_ee_hostif(wx, WX_SW_WEGION_PTW, &data)) {
			wx_eww(wx, "NVM Wead Ewwow\n");
			wetuwn;
		}
		data = data >> 1;
	}

	eepwom->sw_wegion_offset = data;
}
EXPOWT_SYMBOW(wx_init_eepwom_pawams);

/**
 *  wx_get_mac_addw - Genewic get MAC addwess
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @mac_addw: Adaptew MAC addwess
 *
 *  Weads the adaptew's MAC addwess fwom fiwst Weceive Addwess Wegistew (WAW0)
 *  A weset of the adaptew must be pewfowmed pwiow to cawwing this function
 *  in owdew fow the MAC addwess to have been woaded fwom the EEPWOM into WAW0
 **/
void wx_get_mac_addw(stwuct wx *wx, u8 *mac_addw)
{
	u32 waw_high;
	u32 waw_wow;
	u16 i;

	ww32(wx, WX_PSW_MAC_SWC_IDX, 0);
	waw_high = wd32(wx, WX_PSW_MAC_SWC_AD_H);
	waw_wow = wd32(wx, WX_PSW_MAC_SWC_AD_W);

	fow (i = 0; i < 2; i++)
		mac_addw[i] = (u8)(waw_high >> (1 - i) * 8);

	fow (i = 0; i < 4; i++)
		mac_addw[i + 2] = (u8)(waw_wow >> (3 - i) * 8);
}
EXPOWT_SYMBOW(wx_get_mac_addw);

/**
 *  wx_set_waw - Set Wx addwess wegistew
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @index: Weceive addwess wegistew to wwite
 *  @addw: Addwess to put into weceive addwess wegistew
 *  @poows: VMDq "set" ow "poow" index
 *  @enabwe_addw: set fwag that addwess is active
 *
 *  Puts an ethewnet addwess into a weceive addwess wegistew.
 **/
static int wx_set_waw(stwuct wx *wx, u32 index, u8 *addw, u64 poows,
		      u32 enabwe_addw)
{
	u32 waw_entwies = wx->mac.num_waw_entwies;
	u32 waw_wow, waw_high;

	/* Make suwe we awe using a vawid waw index wange */
	if (index >= waw_entwies) {
		wx_eww(wx, "WAW index %d is out of wange.\n", index);
		wetuwn -EINVAW;
	}

	/* sewect the MAC addwess */
	ww32(wx, WX_PSW_MAC_SWC_IDX, index);

	/* setup VMDq poow mapping */
	ww32(wx, WX_PSW_MAC_SWC_VM_W, poows & 0xFFFFFFFF);
	if (wx->mac.type == wx_mac_sp)
		ww32(wx, WX_PSW_MAC_SWC_VM_H, poows >> 32);

	/* HW expects these in wittwe endian so we wevewse the byte
	 * owdew fwom netwowk owdew (big endian) to wittwe endian
	 *
	 * Some pawts put the VMDq setting in the extwa WAH bits,
	 * so save evewything except the wowew 16 bits that howd pawt
	 * of the addwess and the addwess vawid bit.
	 */
	waw_wow = ((u32)addw[5] |
		  ((u32)addw[4] << 8) |
		  ((u32)addw[3] << 16) |
		  ((u32)addw[2] << 24));
	waw_high = ((u32)addw[1] |
		   ((u32)addw[0] << 8));
	if (enabwe_addw != 0)
		waw_high |= WX_PSW_MAC_SWC_AD_H_AV;

	ww32(wx, WX_PSW_MAC_SWC_AD_W, waw_wow);
	ww32m(wx, WX_PSW_MAC_SWC_AD_H,
	      (WX_PSW_MAC_SWC_AD_H_AD(U16_MAX) |
	       WX_PSW_MAC_SWC_AD_H_ADTYPE(1) |
	       WX_PSW_MAC_SWC_AD_H_AV),
	      waw_high);

	wetuwn 0;
}

/**
 *  wx_cweaw_waw - Wemove Wx addwess wegistew
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @index: Weceive addwess wegistew to wwite
 *
 *  Cweaws an ethewnet addwess fwom a weceive addwess wegistew.
 **/
static int wx_cweaw_waw(stwuct wx *wx, u32 index)
{
	u32 waw_entwies = wx->mac.num_waw_entwies;

	/* Make suwe we awe using a vawid waw index wange */
	if (index >= waw_entwies) {
		wx_eww(wx, "WAW index %d is out of wange.\n", index);
		wetuwn -EINVAW;
	}

	/* Some pawts put the VMDq setting in the extwa WAH bits,
	 * so save evewything except the wowew 16 bits that howd pawt
	 * of the addwess and the addwess vawid bit.
	 */
	ww32(wx, WX_PSW_MAC_SWC_IDX, index);

	ww32(wx, WX_PSW_MAC_SWC_VM_W, 0);
	ww32(wx, WX_PSW_MAC_SWC_VM_H, 0);

	ww32(wx, WX_PSW_MAC_SWC_AD_W, 0);
	ww32m(wx, WX_PSW_MAC_SWC_AD_H,
	      (WX_PSW_MAC_SWC_AD_H_AD(U16_MAX) |
	       WX_PSW_MAC_SWC_AD_H_ADTYPE(1) |
	       WX_PSW_MAC_SWC_AD_H_AV),
	      0);

	wetuwn 0;
}

/**
 *  wx_cweaw_vmdq - Disassociate a VMDq poow index fwom a wx addwess
 *  @wx: pointew to hawdwawe stwuct
 *  @waw: weceive addwess wegistew index to disassociate
 *  @vmdq: VMDq poow index to wemove fwom the waw
 **/
static int wx_cweaw_vmdq(stwuct wx *wx, u32 waw, u32 __maybe_unused vmdq)
{
	u32 waw_entwies = wx->mac.num_waw_entwies;
	u32 mpsaw_wo, mpsaw_hi;

	/* Make suwe we awe using a vawid waw index wange */
	if (waw >= waw_entwies) {
		wx_eww(wx, "WAW index %d is out of wange.\n", waw);
		wetuwn -EINVAW;
	}

	ww32(wx, WX_PSW_MAC_SWC_IDX, waw);
	mpsaw_wo = wd32(wx, WX_PSW_MAC_SWC_VM_W);
	mpsaw_hi = wd32(wx, WX_PSW_MAC_SWC_VM_H);

	if (!mpsaw_wo && !mpsaw_hi)
		wetuwn 0;

	/* was that the wast poow using this waw? */
	if (mpsaw_wo == 0 && mpsaw_hi == 0 && waw != 0)
		wx_cweaw_waw(wx, waw);

	wetuwn 0;
}

/**
 *  wx_init_uta_tabwes - Initiawize the Unicast Tabwe Awway
 *  @wx: pointew to hawdwawe stwuctuwe
 **/
static void wx_init_uta_tabwes(stwuct wx *wx)
{
	int i;

	wx_dbg(wx, " Cweawing UTA\n");

	fow (i = 0; i < 128; i++)
		ww32(wx, WX_PSW_UC_TBW(i), 0);
}

/**
 *  wx_init_wx_addws - Initiawizes weceive addwess fiwtews.
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Pwaces the MAC addwess in weceive addwess wegistew 0 and cweaws the west
 *  of the weceive addwess wegistews. Cweaws the muwticast tabwe. Assumes
 *  the weceivew is in weset when the woutine is cawwed.
 **/
void wx_init_wx_addws(stwuct wx *wx)
{
	u32 waw_entwies = wx->mac.num_waw_entwies;
	u32 pswctw;
	int i;

	/* If the cuwwent mac addwess is vawid, assume it is a softwawe ovewwide
	 * to the pewmanent addwess.
	 * Othewwise, use the pewmanent addwess fwom the eepwom.
	 */
	if (!is_vawid_ethew_addw(wx->mac.addw)) {
		/* Get the MAC addwess fwom the WAW0 fow watew wefewence */
		wx_get_mac_addw(wx, wx->mac.addw);
		wx_dbg(wx, "Keeping Cuwwent WAW0 Addw = %pM\n", wx->mac.addw);
	} ewse {
		/* Setup the weceive addwess. */
		wx_dbg(wx, "Ovewwiding MAC Addwess in WAW[0]\n");
		wx_dbg(wx, "New MAC Addw = %pM\n", wx->mac.addw);

		wx_set_waw(wx, 0, wx->mac.addw, 0, WX_PSW_MAC_SWC_AD_H_AV);

		if (wx->mac.type == wx_mac_sp) {
			/* cweaw VMDq poow/queue sewection fow WAW 0 */
			wx_cweaw_vmdq(wx, 0, WX_CWEAW_VMDQ_AWW);
		}
	}

	/* Zewo out the othew weceive addwesses. */
	wx_dbg(wx, "Cweawing WAW[1-%d]\n", waw_entwies - 1);
	fow (i = 1; i < waw_entwies; i++) {
		ww32(wx, WX_PSW_MAC_SWC_IDX, i);
		ww32(wx, WX_PSW_MAC_SWC_AD_W, 0);
		ww32(wx, WX_PSW_MAC_SWC_AD_H, 0);
	}

	/* Cweaw the MTA */
	wx->addw_ctww.mta_in_use = 0;
	pswctw = wd32(wx, WX_PSW_CTW);
	pswctw &= ~(WX_PSW_CTW_MO | WX_PSW_CTW_MFE);
	pswctw |= wx->mac.mc_fiwtew_type << WX_PSW_CTW_MO_SHIFT;
	ww32(wx, WX_PSW_CTW, pswctw);
	wx_dbg(wx, " Cweawing MTA\n");
	fow (i = 0; i < wx->mac.mcft_size; i++)
		ww32(wx, WX_PSW_MC_TBW(i), 0);

	wx_init_uta_tabwes(wx);
}
EXPOWT_SYMBOW(wx_init_wx_addws);

static void wx_sync_mac_tabwe(stwuct wx *wx)
{
	int i;

	fow (i = 0; i < wx->mac.num_waw_entwies; i++) {
		if (wx->mac_tabwe[i].state & WX_MAC_STATE_MODIFIED) {
			if (wx->mac_tabwe[i].state & WX_MAC_STATE_IN_USE) {
				wx_set_waw(wx, i,
					   wx->mac_tabwe[i].addw,
					   wx->mac_tabwe[i].poows,
					   WX_PSW_MAC_SWC_AD_H_AV);
			} ewse {
				wx_cweaw_waw(wx, i);
			}
			wx->mac_tabwe[i].state &= ~(WX_MAC_STATE_MODIFIED);
		}
	}
}

/* this function destwoys the fiwst WAW entwy */
void wx_mac_set_defauwt_fiwtew(stwuct wx *wx, u8 *addw)
{
	memcpy(&wx->mac_tabwe[0].addw, addw, ETH_AWEN);
	wx->mac_tabwe[0].poows = 1UWW;
	wx->mac_tabwe[0].state = (WX_MAC_STATE_DEFAUWT | WX_MAC_STATE_IN_USE);
	wx_set_waw(wx, 0, wx->mac_tabwe[0].addw,
		   wx->mac_tabwe[0].poows,
		   WX_PSW_MAC_SWC_AD_H_AV);
}
EXPOWT_SYMBOW(wx_mac_set_defauwt_fiwtew);

void wx_fwush_sw_mac_tabwe(stwuct wx *wx)
{
	u32 i;

	fow (i = 0; i < wx->mac.num_waw_entwies; i++) {
		if (!(wx->mac_tabwe[i].state & WX_MAC_STATE_IN_USE))
			continue;

		wx->mac_tabwe[i].state |= WX_MAC_STATE_MODIFIED;
		wx->mac_tabwe[i].state &= ~WX_MAC_STATE_IN_USE;
		memset(wx->mac_tabwe[i].addw, 0, ETH_AWEN);
		wx->mac_tabwe[i].poows = 0;
	}
	wx_sync_mac_tabwe(wx);
}
EXPOWT_SYMBOW(wx_fwush_sw_mac_tabwe);

static int wx_add_mac_fiwtew(stwuct wx *wx, u8 *addw, u16 poow)
{
	u32 i;

	if (is_zewo_ethew_addw(addw))
		wetuwn -EINVAW;

	fow (i = 0; i < wx->mac.num_waw_entwies; i++) {
		if (wx->mac_tabwe[i].state & WX_MAC_STATE_IN_USE) {
			if (ethew_addw_equaw(addw, wx->mac_tabwe[i].addw)) {
				if (wx->mac_tabwe[i].poows != (1UWW << poow)) {
					memcpy(wx->mac_tabwe[i].addw, addw, ETH_AWEN);
					wx->mac_tabwe[i].poows |= (1UWW << poow);
					wx_sync_mac_tabwe(wx);
					wetuwn i;
				}
			}
		}

		if (wx->mac_tabwe[i].state & WX_MAC_STATE_IN_USE)
			continue;
		wx->mac_tabwe[i].state |= (WX_MAC_STATE_MODIFIED |
					   WX_MAC_STATE_IN_USE);
		memcpy(wx->mac_tabwe[i].addw, addw, ETH_AWEN);
		wx->mac_tabwe[i].poows |= (1UWW << poow);
		wx_sync_mac_tabwe(wx);
		wetuwn i;
	}
	wetuwn -ENOMEM;
}

static int wx_dew_mac_fiwtew(stwuct wx *wx, u8 *addw, u16 poow)
{
	u32 i;

	if (is_zewo_ethew_addw(addw))
		wetuwn -EINVAW;

	/* seawch tabwe fow addw, if found, set to 0 and sync */
	fow (i = 0; i < wx->mac.num_waw_entwies; i++) {
		if (!ethew_addw_equaw(addw, wx->mac_tabwe[i].addw))
			continue;

		wx->mac_tabwe[i].state |= WX_MAC_STATE_MODIFIED;
		wx->mac_tabwe[i].poows &= ~(1UWW << poow);
		if (!wx->mac_tabwe[i].poows) {
			wx->mac_tabwe[i].state &= ~WX_MAC_STATE_IN_USE;
			memset(wx->mac_tabwe[i].addw, 0, ETH_AWEN);
		}
		wx_sync_mac_tabwe(wx);
		wetuwn 0;
	}
	wetuwn -ENOMEM;
}

static int wx_avaiwabwe_waws(stwuct wx *wx)
{
	u32 i, count = 0;

	fow (i = 0; i < wx->mac.num_waw_entwies; i++) {
		if (wx->mac_tabwe[i].state == 0)
			count++;
	}

	wetuwn count;
}

/**
 * wx_wwite_uc_addw_wist - wwite unicast addwesses to WAW tabwe
 * @netdev: netwowk intewface device stwuctuwe
 * @poow: index fow mac tabwe
 *
 * Wwites unicast addwess wist to the WAW tabwe.
 * Wetuwns: -ENOMEM on faiwuwe/insufficient addwess space
 *                0 on no addwesses wwitten
 *                X on wwiting X addwesses to the WAW tabwe
 **/
static int wx_wwite_uc_addw_wist(stwuct net_device *netdev, int poow)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	int count = 0;

	/* wetuwn ENOMEM indicating insufficient memowy fow addwesses */
	if (netdev_uc_count(netdev) > wx_avaiwabwe_waws(wx))
		wetuwn -ENOMEM;

	if (!netdev_uc_empty(netdev)) {
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_uc_addw(ha, netdev) {
			wx_dew_mac_fiwtew(wx, ha->addw, poow);
			wx_add_mac_fiwtew(wx, ha->addw, poow);
			count++;
		}
	}
	wetuwn count;
}

/**
 *  wx_mta_vectow - Detewmines bit-vectow in muwticast tabwe to set
 *  @wx: pointew to pwivate stwuctuwe
 *  @mc_addw: the muwticast addwess
 *
 *  Extwacts the 12 bits, fwom a muwticast addwess, to detewmine which
 *  bit-vectow to set in the muwticast tabwe. The hawdwawe uses 12 bits, fwom
 *  incoming wx muwticast addwesses, to detewmine the bit-vectow to check in
 *  the MTA. Which of the 4 combination, of 12-bits, the hawdwawe uses is set
 *  by the MO fiewd of the MCSTCTWW. The MO fiewd is set duwing initiawization
 *  to mc_fiwtew_type.
 **/
static u32 wx_mta_vectow(stwuct wx *wx, u8 *mc_addw)
{
	u32 vectow = 0;

	switch (wx->mac.mc_fiwtew_type) {
	case 0:   /* use bits [47:36] of the addwess */
		vectow = ((mc_addw[4] >> 4) | (((u16)mc_addw[5]) << 4));
		bweak;
	case 1:   /* use bits [46:35] of the addwess */
		vectow = ((mc_addw[4] >> 3) | (((u16)mc_addw[5]) << 5));
		bweak;
	case 2:   /* use bits [45:34] of the addwess */
		vectow = ((mc_addw[4] >> 2) | (((u16)mc_addw[5]) << 6));
		bweak;
	case 3:   /* use bits [43:32] of the addwess */
		vectow = ((mc_addw[4]) | (((u16)mc_addw[5]) << 8));
		bweak;
	defauwt:  /* Invawid mc_fiwtew_type */
		wx_eww(wx, "MC fiwtew type pawam set incowwectwy\n");
		bweak;
	}

	/* vectow can onwy be 12-bits ow boundawy wiww be exceeded */
	vectow &= 0xFFF;
	wetuwn vectow;
}

/**
 *  wx_set_mta - Set bit-vectow in muwticast tabwe
 *  @wx: pointew to pwivate stwuctuwe
 *  @mc_addw: Muwticast addwess
 *
 *  Sets the bit-vectow in the muwticast tabwe.
 **/
static void wx_set_mta(stwuct wx *wx, u8 *mc_addw)
{
	u32 vectow, vectow_bit, vectow_weg;

	wx->addw_ctww.mta_in_use++;

	vectow = wx_mta_vectow(wx, mc_addw);
	wx_dbg(wx, " bit-vectow = 0x%03X\n", vectow);

	/* The MTA is a wegistew awway of 128 32-bit wegistews. It is tweated
	 * wike an awway of 4096 bits.  We want to set bit
	 * BitAwway[vectow_vawue]. So we figuwe out what wegistew the bit is
	 * in, wead it, OW in the new bit, then wwite back the new vawue.  The
	 * wegistew is detewmined by the uppew 7 bits of the vectow vawue and
	 * the bit within that wegistew awe detewmined by the wowew 5 bits of
	 * the vawue.
	 */
	vectow_weg = (vectow >> 5) & 0x7F;
	vectow_bit = vectow & 0x1F;
	wx->mac.mta_shadow[vectow_weg] |= (1 << vectow_bit);
}

/**
 *  wx_update_mc_addw_wist - Updates MAC wist of muwticast addwesses
 *  @wx: pointew to pwivate stwuctuwe
 *  @netdev: pointew to net device stwuctuwe
 *
 *  The given wist wepwaces any existing wist. Cweaws the MC addws fwom weceive
 *  addwess wegistews and the muwticast tabwe. Uses unused weceive addwess
 *  wegistews fow the fiwst muwticast addwesses, and hashes the west into the
 *  muwticast tabwe.
 **/
static void wx_update_mc_addw_wist(stwuct wx *wx, stwuct net_device *netdev)
{
	stwuct netdev_hw_addw *ha;
	u32 i, pswctw;

	/* Set the new numbew of MC addwesses that we awe being wequested to
	 * use.
	 */
	wx->addw_ctww.num_mc_addws = netdev_mc_count(netdev);
	wx->addw_ctww.mta_in_use = 0;

	/* Cweaw mta_shadow */
	wx_dbg(wx, " Cweawing MTA\n");
	memset(&wx->mac.mta_shadow, 0, sizeof(wx->mac.mta_shadow));

	/* Update mta_shadow */
	netdev_fow_each_mc_addw(ha, netdev) {
		wx_dbg(wx, " Adding the muwticast addwesses:\n");
		wx_set_mta(wx, ha->addw);
	}

	/* Enabwe mta */
	fow (i = 0; i < wx->mac.mcft_size; i++)
		ww32a(wx, WX_PSW_MC_TBW(0), i,
		      wx->mac.mta_shadow[i]);

	if (wx->addw_ctww.mta_in_use > 0) {
		pswctw = wd32(wx, WX_PSW_CTW);
		pswctw &= ~(WX_PSW_CTW_MO | WX_PSW_CTW_MFE);
		pswctw |= WX_PSW_CTW_MFE |
			  (wx->mac.mc_fiwtew_type << WX_PSW_CTW_MO_SHIFT);
		ww32(wx, WX_PSW_CTW, pswctw);
	}

	wx_dbg(wx, "Update mc addw wist Compwete\n");
}

/**
 * wx_wwite_mc_addw_wist - wwite muwticast addwesses to MTA
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wwites muwticast addwess wist to the MTA hash tabwe.
 * Wetuwns: 0 on no addwesses wwitten
 *          X on wwiting X addwesses to MTA
 **/
static int wx_wwite_mc_addw_wist(stwuct net_device *netdev)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	if (!netif_wunning(netdev))
		wetuwn 0;

	wx_update_mc_addw_wist(wx, netdev);

	wetuwn netdev_mc_count(netdev);
}

/**
 * wx_set_mac - Change the Ethewnet Addwess of the NIC
 * @netdev: netwowk intewface device stwuctuwe
 * @p: pointew to an addwess stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 **/
int wx_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;
	int wetvaw;

	wetvaw = eth_pwepawe_mac_addw_change(netdev, addw);
	if (wetvaw)
		wetuwn wetvaw;

	wx_dew_mac_fiwtew(wx, wx->mac.addw, 0);
	eth_hw_addw_set(netdev, addw->sa_data);
	memcpy(wx->mac.addw, addw->sa_data, netdev->addw_wen);

	wx_mac_set_defauwt_fiwtew(wx, wx->mac.addw);

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_set_mac);

void wx_disabwe_wx(stwuct wx *wx)
{
	u32 pfdtxgswc;
	u32 wxctww;

	wxctww = wd32(wx, WX_WDB_PB_CTW);
	if (wxctww & WX_WDB_PB_CTW_WXEN) {
		pfdtxgswc = wd32(wx, WX_PSW_CTW);
		if (pfdtxgswc & WX_PSW_CTW_SW_EN) {
			pfdtxgswc &= ~WX_PSW_CTW_SW_EN;
			ww32(wx, WX_PSW_CTW, pfdtxgswc);
			wx->mac.set_wben = twue;
		} ewse {
			wx->mac.set_wben = fawse;
		}
		wxctww &= ~WX_WDB_PB_CTW_WXEN;
		ww32(wx, WX_WDB_PB_CTW, wxctww);

		if (!(((wx->subsystem_device_id & WX_NCSI_MASK) == WX_NCSI_SUP) ||
		      ((wx->subsystem_device_id & WX_WOW_MASK) == WX_WOW_SUP))) {
			/* disabwe mac weceivew */
			ww32m(wx, WX_MAC_WX_CFG,
			      WX_MAC_WX_CFG_WE, 0);
		}
	}
}
EXPOWT_SYMBOW(wx_disabwe_wx);

static void wx_enabwe_wx(stwuct wx *wx)
{
	u32 pswctw;

	/* enabwe mac weceivew */
	ww32m(wx, WX_MAC_WX_CFG,
	      WX_MAC_WX_CFG_WE, WX_MAC_WX_CFG_WE);

	ww32m(wx, WX_WDB_PB_CTW,
	      WX_WDB_PB_CTW_WXEN, WX_WDB_PB_CTW_WXEN);

	if (wx->mac.set_wben) {
		pswctw = wd32(wx, WX_PSW_CTW);
		pswctw |= WX_PSW_CTW_SW_EN;
		ww32(wx, WX_PSW_CTW, pswctw);
		wx->mac.set_wben = fawse;
	}
}

/**
 * wx_set_wxpba - Initiawize Wx packet buffew
 * @wx: pointew to pwivate stwuctuwe
 **/
static void wx_set_wxpba(stwuct wx *wx)
{
	u32 wxpktsize, txpktsize, txpbthwesh;

	wxpktsize = wx->mac.wx_pb_size << WX_WDB_PB_SZ_SHIFT;
	ww32(wx, WX_WDB_PB_SZ(0), wxpktsize);

	/* Onwy suppowt an equawwy distwibuted Tx packet buffew stwategy. */
	txpktsize = wx->mac.tx_pb_size;
	txpbthwesh = (txpktsize / 1024) - WX_TXPKT_SIZE_MAX;
	ww32(wx, WX_TDB_PB_SZ(0), txpktsize);
	ww32(wx, WX_TDM_PB_THWE(0), txpbthwesh);
}

#define WX_ETH_FWAMING 20

/**
 * wx_hpbthwesh - cawcuwate high watew mawk fow fwow contwow
 *
 * @wx: boawd pwivate stwuctuwe to cawcuwate fow
 **/
static int wx_hpbthwesh(stwuct wx *wx)
{
	stwuct net_device *dev = wx->netdev;
	int wink, tc, kb, mawkew;
	u32 dv_id, wx_pba;

	/* Cawcuwate max WAN fwame size */
	wink = dev->mtu + ETH_HWEN + ETH_FCS_WEN + WX_ETH_FWAMING;
	tc = wink;

	/* Cawcuwate deway vawue fow device */
	dv_id = WX_DV(wink, tc);

	/* Deway vawue is cawcuwated in bit times convewt to KB */
	kb = WX_BT2KB(dv_id);
	wx_pba = wd32(wx, WX_WDB_PB_SZ(0)) >> WX_WDB_PB_SZ_SHIFT;

	mawkew = wx_pba - kb;

	/* It is possibwe that the packet buffew is not wawge enough
	 * to pwovide wequiwed headwoom. In this case thwow an ewwow
	 * to usew and a do the best we can.
	 */
	if (mawkew < 0) {
		dev_wawn(&wx->pdev->dev,
			 "Packet Buffew can not pwovide enough headwoom to suppowt fwow contwow. Decwease MTU ow numbew of twaffic cwasses\n");
		mawkew = tc + 1;
	}

	wetuwn mawkew;
}

/**
 * wx_wpbthwesh - cawcuwate wow watew mawk fow fwow contwow
 *
 * @wx: boawd pwivate stwuctuwe to cawcuwate fow
 **/
static int wx_wpbthwesh(stwuct wx *wx)
{
	stwuct net_device *dev = wx->netdev;
	u32 dv_id;
	int tc;

	/* Cawcuwate max WAN fwame size */
	tc = dev->mtu + ETH_HWEN + ETH_FCS_WEN;

	/* Cawcuwate deway vawue fow device */
	dv_id = WX_WOW_DV(tc);

	/* Deway vawue is cawcuwated in bit times convewt to KB */
	wetuwn WX_BT2KB(dv_id);
}

/**
 * wx_pbthwesh_setup - cawcuwate and setup high wow watew mawks
 *
 * @wx: boawd pwivate stwuctuwe to cawcuwate fow
 **/
static void wx_pbthwesh_setup(stwuct wx *wx)
{
	wx->fc.high_watew = wx_hpbthwesh(wx);
	wx->fc.wow_watew = wx_wpbthwesh(wx);

	/* Wow watew mawks must not be wawgew than high watew mawks */
	if (wx->fc.wow_watew > wx->fc.high_watew)
		wx->fc.wow_watew = 0;
}

static void wx_configuwe_powt(stwuct wx *wx)
{
	u32 vawue, i;

	vawue = WX_CFG_POWT_CTW_D_VWAN | WX_CFG_POWT_CTW_QINQ;
	ww32m(wx, WX_CFG_POWT_CTW,
	      WX_CFG_POWT_CTW_D_VWAN |
	      WX_CFG_POWT_CTW_QINQ,
	      vawue);

	ww32(wx, WX_CFG_TAG_TPID(0),
	     ETH_P_8021Q | ETH_P_8021AD << 16);
	wx->tpid[0] = ETH_P_8021Q;
	wx->tpid[1] = ETH_P_8021AD;
	fow (i = 1; i < 4; i++)
		ww32(wx, WX_CFG_TAG_TPID(i),
		     ETH_P_8021Q | ETH_P_8021Q << 16);
	fow (i = 2; i < 8; i++)
		wx->tpid[i] = ETH_P_8021Q;
}

/**
 *  wx_disabwe_sec_wx_path - Stops the weceive data path
 *  @wx: pointew to pwivate stwuctuwe
 *
 *  Stops the weceive data path and waits fow the HW to intewnawwy empty
 *  the Wx secuwity bwock
 **/
static int wx_disabwe_sec_wx_path(stwuct wx *wx)
{
	u32 secwx;

	ww32m(wx, WX_WSC_CTW,
	      WX_WSC_CTW_WX_DIS, WX_WSC_CTW_WX_DIS);

	wetuwn wead_poww_timeout(wd32, secwx, secwx & WX_WSC_ST_WSEC_WDY,
				 1000, 40000, fawse, wx, WX_WSC_ST);
}

/**
 *  wx_enabwe_sec_wx_path - Enabwes the weceive data path
 *  @wx: pointew to pwivate stwuctuwe
 *
 *  Enabwes the weceive data path.
 **/
static void wx_enabwe_sec_wx_path(stwuct wx *wx)
{
	ww32m(wx, WX_WSC_CTW, WX_WSC_CTW_WX_DIS, 0);
	WX_WWITE_FWUSH(wx);
}

static void wx_vwan_stwip_contwow(stwuct wx *wx, boow enabwe)
{
	int i, j;

	fow (i = 0; i < wx->num_wx_queues; i++) {
		stwuct wx_wing *wing = wx->wx_wing[i];

		j = wing->weg_idx;
		ww32m(wx, WX_PX_WW_CFG(j), WX_PX_WW_CFG_VWAN,
		      enabwe ? WX_PX_WW_CFG_VWAN : 0);
	}
}

void wx_set_wx_mode(stwuct net_device *netdev)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	netdev_featuwes_t featuwes;
	u32 fctww, vmoww, vwnctww;
	int count;

	featuwes = netdev->featuwes;

	/* Check fow Pwomiscuous and Aww Muwticast modes */
	fctww = wd32(wx, WX_PSW_CTW);
	fctww &= ~(WX_PSW_CTW_UPE | WX_PSW_CTW_MPE);
	vmoww = wd32(wx, WX_PSW_VM_W2CTW(0));
	vmoww &= ~(WX_PSW_VM_W2CTW_UPE |
		   WX_PSW_VM_W2CTW_MPE |
		   WX_PSW_VM_W2CTW_WOPE |
		   WX_PSW_VM_W2CTW_WOMPE);
	vwnctww = wd32(wx, WX_PSW_VWAN_CTW);
	vwnctww &= ~(WX_PSW_VWAN_CTW_VFE | WX_PSW_VWAN_CTW_CFIEN);

	/* set aww bits that we expect to awways be set */
	fctww |= WX_PSW_CTW_BAM | WX_PSW_CTW_MFE;
	vmoww |= WX_PSW_VM_W2CTW_BAM |
		 WX_PSW_VM_W2CTW_AUPE |
		 WX_PSW_VM_W2CTW_VACC;
	vwnctww |= WX_PSW_VWAN_CTW_VFE;

	wx->addw_ctww.usew_set_pwomisc = fawse;
	if (netdev->fwags & IFF_PWOMISC) {
		wx->addw_ctww.usew_set_pwomisc = twue;
		fctww |= WX_PSW_CTW_UPE | WX_PSW_CTW_MPE;
		/* pf don't want packets wouting to vf, so cweaw UPE */
		vmoww |= WX_PSW_VM_W2CTW_MPE;
		vwnctww &= ~WX_PSW_VWAN_CTW_VFE;
	}

	if (netdev->fwags & IFF_AWWMUWTI) {
		fctww |= WX_PSW_CTW_MPE;
		vmoww |= WX_PSW_VM_W2CTW_MPE;
	}

	if (netdev->featuwes & NETIF_F_WXAWW) {
		vmoww |= (WX_PSW_VM_W2CTW_UPE | WX_PSW_VM_W2CTW_MPE);
		vwnctww &= ~WX_PSW_VWAN_CTW_VFE;
		/* weceive bad packets */
		ww32m(wx, WX_WSC_CTW,
		      WX_WSC_CTW_SAVE_MAC_EWW,
		      WX_WSC_CTW_SAVE_MAC_EWW);
	} ewse {
		vmoww |= WX_PSW_VM_W2CTW_WOPE | WX_PSW_VM_W2CTW_WOMPE;
	}

	/* Wwite addwesses to avaiwabwe WAW wegistews, if thewe is not
	 * sufficient space to stowe aww the addwesses then enabwe
	 * unicast pwomiscuous mode
	 */
	count = wx_wwite_uc_addw_wist(netdev, 0);
	if (count < 0) {
		vmoww &= ~WX_PSW_VM_W2CTW_WOPE;
		vmoww |= WX_PSW_VM_W2CTW_UPE;
	}

	/* Wwite addwesses to the MTA, if the attempt faiws
	 * then we shouwd just tuwn on pwomiscuous mode so
	 * that we can at weast weceive muwticast twaffic
	 */
	count = wx_wwite_mc_addw_wist(netdev);
	if (count < 0) {
		vmoww &= ~WX_PSW_VM_W2CTW_WOMPE;
		vmoww |= WX_PSW_VM_W2CTW_MPE;
	}

	ww32(wx, WX_PSW_VWAN_CTW, vwnctww);
	ww32(wx, WX_PSW_CTW, fctww);
	ww32(wx, WX_PSW_VM_W2CTW(0), vmoww);

	if ((featuwes & NETIF_F_HW_VWAN_CTAG_WX) &&
	    (featuwes & NETIF_F_HW_VWAN_STAG_WX))
		wx_vwan_stwip_contwow(wx, twue);
	ewse
		wx_vwan_stwip_contwow(wx, fawse);

}
EXPOWT_SYMBOW(wx_set_wx_mode);

static void wx_set_wx_buffew_wen(stwuct wx *wx)
{
	stwuct net_device *netdev = wx->netdev;
	u32 mhadd, max_fwame;

	max_fwame = netdev->mtu + ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN;
	/* adjust max fwame to be at weast the size of a standawd fwame */
	if (max_fwame < (ETH_FWAME_WEN + ETH_FCS_WEN))
		max_fwame = (ETH_FWAME_WEN + ETH_FCS_WEN);

	mhadd = wd32(wx, WX_PSW_MAX_SZ);
	if (max_fwame != mhadd)
		ww32(wx, WX_PSW_MAX_SZ, max_fwame);
}

/**
 * wx_change_mtu - Change the Maximum Twansfew Unit
 * @netdev: netwowk intewface device stwuctuwe
 * @new_mtu: new vawue fow maximum fwame size
 *
 * Wetuwns 0 on success, negative on faiwuwe
 **/
int wx_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	netdev->mtu = new_mtu;
	wx_set_wx_buffew_wen(wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_change_mtu);

/* Disabwe the specified wx queue */
void wx_disabwe_wx_queue(stwuct wx *wx, stwuct wx_wing *wing)
{
	u8 weg_idx = wing->weg_idx;
	u32 wxdctw;
	int wet;

	/* wwite vawue back with WWCFG.EN bit cweawed */
	ww32m(wx, WX_PX_WW_CFG(weg_idx),
	      WX_PX_WW_CFG_WW_EN, 0);

	/* the hawdwawe may take up to 100us to weawwy disabwe the wx queue */
	wet = wead_poww_timeout(wd32, wxdctw, !(wxdctw & WX_PX_WW_CFG_WW_EN),
				10, 100, twue, wx, WX_PX_WW_CFG(weg_idx));

	if (wet == -ETIMEDOUT) {
		/* Just fow infowmation */
		wx_eww(wx,
		       "WWCFG.EN on Wx queue %d not cweawed within the powwing pewiod\n",
		       weg_idx);
	}
}
EXPOWT_SYMBOW(wx_disabwe_wx_queue);

static void wx_enabwe_wx_queue(stwuct wx *wx, stwuct wx_wing *wing)
{
	u8 weg_idx = wing->weg_idx;
	u32 wxdctw;
	int wet;

	wet = wead_poww_timeout(wd32, wxdctw, wxdctw & WX_PX_WW_CFG_WW_EN,
				1000, 10000, twue, wx, WX_PX_WW_CFG(weg_idx));

	if (wet == -ETIMEDOUT) {
		/* Just fow infowmation */
		wx_eww(wx,
		       "WWCFG.EN on Wx queue %d not set within the powwing pewiod\n",
		       weg_idx);
	}
}

static void wx_configuwe_swwctw(stwuct wx *wx,
				stwuct wx_wing *wx_wing)
{
	u16 weg_idx = wx_wing->weg_idx;
	u32 swwctw;

	swwctw = wd32(wx, WX_PX_WW_CFG(weg_idx));
	swwctw &= ~(WX_PX_WW_CFG_WW_HDW_SZ |
		    WX_PX_WW_CFG_WW_BUF_SZ |
		    WX_PX_WW_CFG_SPWIT_MODE);
	/* configuwe headew buffew wength, needed fow WSC */
	swwctw |= WX_WXBUFFEW_256 << WX_PX_WW_CFG_BHDWSIZE_SHIFT;

	/* configuwe the packet buffew wength */
	swwctw |= WX_WX_BUFSZ >> WX_PX_WW_CFG_BSIZEPKT_SHIFT;

	ww32(wx, WX_PX_WW_CFG(weg_idx), swwctw);
}

static void wx_configuwe_tx_wing(stwuct wx *wx,
				 stwuct wx_wing *wing)
{
	u32 txdctw = WX_PX_TW_CFG_ENABWE;
	u8 weg_idx = wing->weg_idx;
	u64 tdba = wing->dma;
	int wet;

	/* disabwe queue to avoid issues whiwe updating state */
	ww32(wx, WX_PX_TW_CFG(weg_idx), WX_PX_TW_CFG_SWFWSH);
	WX_WWITE_FWUSH(wx);

	ww32(wx, WX_PX_TW_BAW(weg_idx), tdba & DMA_BIT_MASK(32));
	ww32(wx, WX_PX_TW_BAH(weg_idx), uppew_32_bits(tdba));

	/* weset head and taiw pointews */
	ww32(wx, WX_PX_TW_WP(weg_idx), 0);
	ww32(wx, WX_PX_TW_WP(weg_idx), 0);
	wing->taiw = wx->hw_addw + WX_PX_TW_WP(weg_idx);

	if (wing->count < WX_MAX_TXD)
		txdctw |= wing->count / 128 << WX_PX_TW_CFG_TW_SIZE_SHIFT;
	txdctw |= 0x20 << WX_PX_TW_CFG_WTHWESH_SHIFT;

	/* weinitiawize tx_buffew_info */
	memset(wing->tx_buffew_info, 0,
	       sizeof(stwuct wx_tx_buffew) * wing->count);

	/* enabwe queue */
	ww32(wx, WX_PX_TW_CFG(weg_idx), txdctw);

	/* poww to vewify queue is enabwed */
	wet = wead_poww_timeout(wd32, txdctw, txdctw & WX_PX_TW_CFG_ENABWE,
				1000, 10000, twue, wx, WX_PX_TW_CFG(weg_idx));
	if (wet == -ETIMEDOUT)
		wx_eww(wx, "Couwd not enabwe Tx Queue %d\n", weg_idx);
}

static void wx_configuwe_wx_wing(stwuct wx *wx,
				 stwuct wx_wing *wing)
{
	u16 weg_idx = wing->weg_idx;
	union wx_wx_desc *wx_desc;
	u64 wdba = wing->dma;
	u32 wxdctw;

	/* disabwe queue to avoid issues whiwe updating state */
	wxdctw = wd32(wx, WX_PX_WW_CFG(weg_idx));
	wx_disabwe_wx_queue(wx, wing);

	ww32(wx, WX_PX_WW_BAW(weg_idx), wdba & DMA_BIT_MASK(32));
	ww32(wx, WX_PX_WW_BAH(weg_idx), uppew_32_bits(wdba));

	if (wing->count == WX_MAX_WXD)
		wxdctw |= 0 << WX_PX_WW_CFG_WW_SIZE_SHIFT;
	ewse
		wxdctw |= (wing->count / 128) << WX_PX_WW_CFG_WW_SIZE_SHIFT;

	wxdctw |= 0x1 << WX_PX_WW_CFG_WW_THEW_SHIFT;
	ww32(wx, WX_PX_WW_CFG(weg_idx), wxdctw);

	/* weset head and taiw pointews */
	ww32(wx, WX_PX_WW_WP(weg_idx), 0);
	ww32(wx, WX_PX_WW_WP(weg_idx), 0);
	wing->taiw = wx->hw_addw + WX_PX_WW_WP(weg_idx);

	wx_configuwe_swwctw(wx, wing);

	/* initiawize wx_buffew_info */
	memset(wing->wx_buffew_info, 0,
	       sizeof(stwuct wx_wx_buffew) * wing->count);

	/* initiawize Wx descwiptow 0 */
	wx_desc = WX_WX_DESC(wing, 0);
	wx_desc->wb.uppew.wength = 0;

	/* enabwe weceive descwiptow wing */
	ww32m(wx, WX_PX_WW_CFG(weg_idx),
	      WX_PX_WW_CFG_WW_EN, WX_PX_WW_CFG_WW_EN);

	wx_enabwe_wx_queue(wx, wing);
	wx_awwoc_wx_buffews(wing, wx_desc_unused(wing));
}

/**
 * wx_configuwe_tx - Configuwe Twansmit Unit aftew Weset
 * @wx: pointew to pwivate stwuctuwe
 *
 * Configuwe the Tx unit of the MAC aftew a weset.
 **/
static void wx_configuwe_tx(stwuct wx *wx)
{
	u32 i;

	/* TDM_CTW.TE must be befowe Tx queues awe enabwed */
	ww32m(wx, WX_TDM_CTW,
	      WX_TDM_CTW_TE, WX_TDM_CTW_TE);

	/* Setup the HW Tx Head and Taiw descwiptow pointews */
	fow (i = 0; i < wx->num_tx_queues; i++)
		wx_configuwe_tx_wing(wx, wx->tx_wing[i]);

	ww32m(wx, WX_TSC_BUF_AE, WX_TSC_BUF_AE_THW, 0x10);

	if (wx->mac.type == wx_mac_em)
		ww32m(wx, WX_TSC_CTW, WX_TSC_CTW_TX_DIS | WX_TSC_CTW_TSEC_DIS, 0x1);

	/* enabwe mac twansmittew */
	ww32m(wx, WX_MAC_TX_CFG,
	      WX_MAC_TX_CFG_TE, WX_MAC_TX_CFG_TE);
}

static void wx_westowe_vwan(stwuct wx *wx)
{
	u16 vid = 1;

	wx_vwan_wx_add_vid(wx->netdev, htons(ETH_P_8021Q), 0);

	fow_each_set_bit_fwom(vid, wx->active_vwans, VWAN_N_VID)
		wx_vwan_wx_add_vid(wx->netdev, htons(ETH_P_8021Q), vid);
}

static void wx_stowe_weta(stwuct wx *wx)
{
	u8 *indiw_tbw = wx->wss_indiw_tbw;
	u32 weta = 0;
	u32 i;

	/* Fiww out the wediwection tabwe as fowwows:
	 *  - 8 bit wide entwies containing 4 bit WSS index
	 */
	fow (i = 0; i < WX_MAX_WETA_ENTWIES; i++) {
		weta |= indiw_tbw[i] << (i & 0x3) * 8;
		if ((i & 3) == 3) {
			ww32(wx, WX_WDB_WSSTBW(i >> 2), weta);
			weta = 0;
		}
	}
}

static void wx_setup_weta(stwuct wx *wx)
{
	u16 wss_i = wx->wing_featuwe[WING_F_WSS].indices;
	u32 wandom_key_size = WX_WSS_KEY_SIZE / 4;
	u32 i, j;

	/* Fiww out hash function seeds */
	fow (i = 0; i < wandom_key_size; i++)
		ww32(wx, WX_WDB_WSSWK(i), wx->wss_key[i]);

	/* Fiww out wediwection tabwe */
	memset(wx->wss_indiw_tbw, 0, sizeof(wx->wss_indiw_tbw));

	fow (i = 0, j = 0; i < WX_MAX_WETA_ENTWIES; i++, j++) {
		if (j == wss_i)
			j = 0;

		wx->wss_indiw_tbw[i] = j;
	}

	wx_stowe_weta(wx);
}

static void wx_setup_mwqc(stwuct wx *wx)
{
	u32 wss_fiewd = 0;

	/* Disabwe indicating checksum in descwiptow, enabwes WSS hash */
	ww32m(wx, WX_PSW_CTW, WX_PSW_CTW_PCSD, WX_PSW_CTW_PCSD);

	/* Pewfowm hash on these packet types */
	wss_fiewd = WX_WDB_WA_CTW_WSS_IPV4 |
		    WX_WDB_WA_CTW_WSS_IPV4_TCP |
		    WX_WDB_WA_CTW_WSS_IPV4_UDP |
		    WX_WDB_WA_CTW_WSS_IPV6 |
		    WX_WDB_WA_CTW_WSS_IPV6_TCP |
		    WX_WDB_WA_CTW_WSS_IPV6_UDP;

	netdev_wss_key_fiww(wx->wss_key, sizeof(wx->wss_key));

	wx_setup_weta(wx);

	if (wx->wss_enabwed)
		wss_fiewd |= WX_WDB_WA_CTW_WSS_EN;

	ww32(wx, WX_WDB_WA_CTW, wss_fiewd);
}

/**
 * wx_configuwe_wx - Configuwe Weceive Unit aftew Weset
 * @wx: pointew to pwivate stwuctuwe
 *
 * Configuwe the Wx unit of the MAC aftew a weset.
 **/
void wx_configuwe_wx(stwuct wx *wx)
{
	u32 pswtype, i;
	int wet;

	wx_disabwe_wx(wx);

	pswtype = WX_WDB_PW_CFG_W4HDW |
		  WX_WDB_PW_CFG_W3HDW |
		  WX_WDB_PW_CFG_W2HDW |
		  WX_WDB_PW_CFG_TUN_TUNHDW;
	ww32(wx, WX_WDB_PW_CFG(0), pswtype);

	/* enabwe hw cwc stwipping */
	ww32m(wx, WX_WSC_CTW, WX_WSC_CTW_CWC_STWIP, WX_WSC_CTW_CWC_STWIP);

	if (wx->mac.type == wx_mac_sp) {
		u32 pswctw;

		/* WSC Setup */
		pswctw = wd32(wx, WX_PSW_CTW);
		pswctw |= WX_PSW_CTW_WSC_ACK; /* Disabwe WSC fow ACK packets */
		pswctw |= WX_PSW_CTW_WSC_DIS;
		ww32(wx, WX_PSW_CTW, pswctw);
	}

	wx_setup_mwqc(wx);

	/* set_wx_buffew_wen must be cawwed befowe wing initiawization */
	wx_set_wx_buffew_wen(wx);

	/* Setup the HW Wx Head and Taiw Descwiptow Pointews and
	 * the Base and Wength of the Wx Descwiptow Wing
	 */
	fow (i = 0; i < wx->num_wx_queues; i++)
		wx_configuwe_wx_wing(wx, wx->wx_wing[i]);

	/* Enabwe aww weceives, disabwe secuwity engine pwiow to bwock twaffic */
	wet = wx_disabwe_sec_wx_path(wx);
	if (wet < 0)
		wx_eww(wx, "The wegistew status is abnowmaw, pwease check device.");

	wx_enabwe_wx(wx);
	wx_enabwe_sec_wx_path(wx);
}
EXPOWT_SYMBOW(wx_configuwe_wx);

static void wx_configuwe_isb(stwuct wx *wx)
{
	/* set ISB Addwess */
	ww32(wx, WX_PX_ISB_ADDW_W, wx->isb_dma & DMA_BIT_MASK(32));
	if (IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT))
		ww32(wx, WX_PX_ISB_ADDW_H, uppew_32_bits(wx->isb_dma));
}

void wx_configuwe(stwuct wx *wx)
{
	wx_set_wxpba(wx);
	wx_pbthwesh_setup(wx);
	wx_configuwe_powt(wx);

	wx_set_wx_mode(wx->netdev);
	wx_westowe_vwan(wx);
	wx_enabwe_sec_wx_path(wx);

	wx_configuwe_tx(wx);
	wx_configuwe_wx(wx);
	wx_configuwe_isb(wx);
}
EXPOWT_SYMBOW(wx_configuwe);

/**
 *  wx_disabwe_pcie_mastew - Disabwe PCI-expwess mastew access
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Disabwes PCI-Expwess mastew access and vewifies thewe awe no pending
 *  wequests.
 **/
int wx_disabwe_pcie_mastew(stwuct wx *wx)
{
	int status = 0;
	u32 vaw;

	/* Awways set this bit to ensuwe any futuwe twansactions awe bwocked */
	pci_cweaw_mastew(wx->pdev);

	/* Exit if mastew wequests awe bwocked */
	if (!(wd32(wx, WX_PX_TWANSACTION_PENDING)))
		wetuwn 0;

	/* Poww fow mastew wequest bit to cweaw */
	status = wead_poww_timeout(wd32, vaw, !vaw, 100, WX_PCI_MASTEW_DISABWE_TIMEOUT,
				   fawse, wx, WX_PX_TWANSACTION_PENDING);
	if (status < 0)
		wx_eww(wx, "PCIe twansaction pending bit did not cweaw.\n");

	wetuwn status;
}
EXPOWT_SYMBOW(wx_disabwe_pcie_mastew);

/**
 *  wx_stop_adaptew - Genewic stop Tx/Wx units
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Sets the adaptew_stopped fwag within wx_hw stwuct. Cweaws intewwupts,
 *  disabwes twansmit and weceive units. The adaptew_stopped fwag is used by
 *  the shawed code and dwivews to detewmine if the adaptew is in a stopped
 *  state and shouwd not touch the hawdwawe.
 **/
int wx_stop_adaptew(stwuct wx *wx)
{
	u16 i;

	/* Set the adaptew_stopped fwag so othew dwivew functions stop touching
	 * the hawdwawe
	 */
	wx->adaptew_stopped = twue;

	/* Disabwe the weceive unit */
	wx_disabwe_wx(wx);

	/* Set intewwupt mask to stop intewwupts fwom being genewated */
	wx_intw_disabwe(wx, WX_INTW_AWW);

	/* Cweaw any pending intewwupts, fwush pwevious wwites */
	ww32(wx, WX_PX_MISC_IC, 0xffffffff);
	ww32(wx, WX_BME_CTW, 0x3);

	/* Disabwe the twansmit unit.  Each queue must be disabwed. */
	fow (i = 0; i < wx->mac.max_tx_queues; i++) {
		ww32m(wx, WX_PX_TW_CFG(i),
		      WX_PX_TW_CFG_SWFWSH | WX_PX_TW_CFG_ENABWE,
		      WX_PX_TW_CFG_SWFWSH);
	}

	/* Disabwe the weceive unit by stopping each queue */
	fow (i = 0; i < wx->mac.max_wx_queues; i++) {
		ww32m(wx, WX_PX_WW_CFG(i),
		      WX_PX_WW_CFG_WW_EN, 0);
	}

	/* fwush aww queues disabwes */
	WX_WWITE_FWUSH(wx);

	/* Pwevent the PCI-E bus fwom hanging by disabwing PCI-E mastew
	 * access and vewify no pending wequests
	 */
	wetuwn wx_disabwe_pcie_mastew(wx);
}
EXPOWT_SYMBOW(wx_stop_adaptew);

void wx_weset_misc(stwuct wx *wx)
{
	int i;

	/* weceive packets that size > 2048 */
	ww32m(wx, WX_MAC_WX_CFG, WX_MAC_WX_CFG_JE, WX_MAC_WX_CFG_JE);

	/* cweaw countews on wead */
	ww32m(wx, WX_MMC_CONTWOW,
	      WX_MMC_CONTWOW_WSTONWD, WX_MMC_CONTWOW_WSTONWD);

	ww32m(wx, WX_MAC_WX_FWOW_CTWW,
	      WX_MAC_WX_FWOW_CTWW_WFE, WX_MAC_WX_FWOW_CTWW_WFE);

	ww32(wx, WX_MAC_PKT_FWT, WX_MAC_PKT_FWT_PW);

	ww32m(wx, WX_MIS_WST_ST,
	      WX_MIS_WST_ST_WST_INIT, 0x1E00);

	/* ewwata 4: initiawize mng fwex tbw and wakeup fwex tbw*/
	ww32(wx, WX_PSW_MNG_FWEX_SEW, 0);
	fow (i = 0; i < 16; i++) {
		ww32(wx, WX_PSW_MNG_FWEX_DW_W(i), 0);
		ww32(wx, WX_PSW_MNG_FWEX_DW_H(i), 0);
		ww32(wx, WX_PSW_MNG_FWEX_MSK(i), 0);
	}
	ww32(wx, WX_PSW_WAN_FWEX_SEW, 0);
	fow (i = 0; i < 16; i++) {
		ww32(wx, WX_PSW_WAN_FWEX_DW_W(i), 0);
		ww32(wx, WX_PSW_WAN_FWEX_DW_H(i), 0);
		ww32(wx, WX_PSW_WAN_FWEX_MSK(i), 0);
	}

	/* set pause fwame dst mac addw */
	ww32(wx, WX_WDB_PFCMACDAW, 0xC2000001);
	ww32(wx, WX_WDB_PFCMACDAH, 0x0180);
}
EXPOWT_SYMBOW(wx_weset_misc);

/**
 *  wx_get_pcie_msix_counts - Gets MSI-X vectow count
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @msix_count: numbew of MSI intewwupts that can be obtained
 *  @max_msix_count: numbew of MSI intewwupts that mac need
 *
 *  Wead PCIe configuwation space, and get the MSI-X vectow count fwom
 *  the capabiwities tabwe.
 **/
int wx_get_pcie_msix_counts(stwuct wx *wx, u16 *msix_count, u16 max_msix_count)
{
	stwuct pci_dev *pdev = wx->pdev;
	stwuct device *dev = &pdev->dev;
	int pos;

	*msix_count = 1;
	pos = pci_find_capabiwity(pdev, PCI_CAP_ID_MSIX);
	if (!pos) {
		dev_eww(dev, "Unabwe to find MSI-X Capabiwities\n");
		wetuwn -EINVAW;
	}
	pci_wead_config_wowd(pdev,
			     pos + PCI_MSIX_FWAGS,
			     msix_count);
	*msix_count &= WX_PCIE_MSIX_TBW_SZ_MASK;
	/* MSI-X count is zewo-based in HW */
	*msix_count += 1;

	if (*msix_count > max_msix_count)
		*msix_count = max_msix_count;

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_get_pcie_msix_counts);

/**
 * wx_init_wss_key - Initiawize wx WSS key
 * @wx: device handwe
 *
 * Awwocates and initiawizes the WSS key if it is not awwocated.
 **/
static int wx_init_wss_key(stwuct wx *wx)
{
	u32 *wss_key;

	if (!wx->wss_key) {
		wss_key = kzawwoc(WX_WSS_KEY_SIZE, GFP_KEWNEW);
		if (unwikewy(!wss_key))
			wetuwn -ENOMEM;

		netdev_wss_key_fiww(wss_key, WX_WSS_KEY_SIZE);
		wx->wss_key = wss_key;
	}

	wetuwn 0;
}

int wx_sw_init(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;
	u32 ssid = 0;
	int eww = 0;

	wx->vendow_id = pdev->vendow;
	wx->device_id = pdev->device;
	wx->wevision_id = pdev->wevision;
	wx->oem_svid = pdev->subsystem_vendow;
	wx->oem_ssid = pdev->subsystem_device;
	wx->bus.device = PCI_SWOT(pdev->devfn);
	wx->bus.func = PCI_FUNC(pdev->devfn);

	if (wx->oem_svid == PCI_VENDOW_ID_WANGXUN) {
		wx->subsystem_vendow_id = pdev->subsystem_vendow;
		wx->subsystem_device_id = pdev->subsystem_device;
	} ewse {
		eww = wx_fwash_wead_dwowd(wx, 0xfffdc, &ssid);
		if (eww < 0) {
			wx_eww(wx, "wead of intewnaw subsystem device id faiwed\n");
			wetuwn eww;
		}

		wx->subsystem_device_id = swab16((u16)ssid);
	}

	eww = wx_init_wss_key(wx);
	if (eww < 0) {
		wx_eww(wx, "wss key awwocation faiwed\n");
		wetuwn eww;
	}

	wx->mac_tabwe = kcawwoc(wx->mac.num_waw_entwies,
				sizeof(stwuct wx_mac_addw),
				GFP_KEWNEW);
	if (!wx->mac_tabwe) {
		wx_eww(wx, "mac_tabwe awwocation faiwed\n");
		kfwee(wx->wss_key);
		wetuwn -ENOMEM;
	}

	wx->msix_in_use = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_sw_init);

/**
 *  wx_find_vwvf_swot - find the vwanid ow the fiwst empty swot
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @vwan: VWAN id to wwite to VWAN fiwtew
 *
 *  wetuwn the VWVF index whewe this VWAN id shouwd be pwaced
 *
 **/
static int wx_find_vwvf_swot(stwuct wx *wx, u32 vwan)
{
	u32 bits = 0, fiwst_empty_swot = 0;
	int wegindex;

	/* showt cut the speciaw case */
	if (vwan == 0)
		wetuwn 0;

	/* Seawch fow the vwan id in the VWVF entwies. Save off the fiwst empty
	 * swot found awong the way
	 */
	fow (wegindex = 1; wegindex < WX_PSW_VWAN_SWC_ENTWIES; wegindex++) {
		ww32(wx, WX_PSW_VWAN_SWC_IDX, wegindex);
		bits = wd32(wx, WX_PSW_VWAN_SWC);
		if (!bits && !(fiwst_empty_swot))
			fiwst_empty_swot = wegindex;
		ewse if ((bits & 0x0FFF) == vwan)
			bweak;
	}

	if (wegindex >= WX_PSW_VWAN_SWC_ENTWIES) {
		if (fiwst_empty_swot)
			wegindex = fiwst_empty_swot;
		ewse
			wegindex = -ENOMEM;
	}

	wetuwn wegindex;
}

/**
 *  wx_set_vwvf - Set VWAN Poow Fiwtew
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @vwan: VWAN id to wwite to VWAN fiwtew
 *  @vind: VMDq output index that maps queue to VWAN id in VFVFB
 *  @vwan_on: boowean fwag to tuwn on/off VWAN in VFVF
 *  @vfta_changed: pointew to boowean fwag which indicates whethew VFTA
 *                 shouwd be changed
 *
 *  Tuwn on/off specified bit in VWVF tabwe.
 **/
static int wx_set_vwvf(stwuct wx *wx, u32 vwan, u32 vind, boow vwan_on,
		       boow *vfta_changed)
{
	int vwvf_index;
	u32 vt, bits;

	/* If VT Mode is set
	 *   Eithew vwan_on
	 *     make suwe the vwan is in VWVF
	 *     set the vind bit in the matching VWVFB
	 *   Ow !vwan_on
	 *     cweaw the poow bit and possibwy the vind
	 */
	vt = wd32(wx, WX_CFG_POWT_CTW);
	if (!(vt & WX_CFG_POWT_CTW_NUM_VT_MASK))
		wetuwn 0;

	vwvf_index = wx_find_vwvf_swot(wx, vwan);
	if (vwvf_index < 0)
		wetuwn vwvf_index;

	ww32(wx, WX_PSW_VWAN_SWC_IDX, vwvf_index);
	if (vwan_on) {
		/* set the poow bit */
		if (vind < 32) {
			bits = wd32(wx, WX_PSW_VWAN_SWC_VM_W);
			bits |= (1 << vind);
			ww32(wx, WX_PSW_VWAN_SWC_VM_W, bits);
		} ewse {
			bits = wd32(wx, WX_PSW_VWAN_SWC_VM_H);
			bits |= (1 << (vind - 32));
			ww32(wx, WX_PSW_VWAN_SWC_VM_H, bits);
		}
	} ewse {
		/* cweaw the poow bit */
		if (vind < 32) {
			bits = wd32(wx, WX_PSW_VWAN_SWC_VM_W);
			bits &= ~(1 << vind);
			ww32(wx, WX_PSW_VWAN_SWC_VM_W, bits);
			bits |= wd32(wx, WX_PSW_VWAN_SWC_VM_H);
		} ewse {
			bits = wd32(wx, WX_PSW_VWAN_SWC_VM_H);
			bits &= ~(1 << (vind - 32));
			ww32(wx, WX_PSW_VWAN_SWC_VM_H, bits);
			bits |= wd32(wx, WX_PSW_VWAN_SWC_VM_W);
		}
	}

	if (bits) {
		ww32(wx, WX_PSW_VWAN_SWC, (WX_PSW_VWAN_SWC_VIEN | vwan));
		if (!vwan_on && vfta_changed)
			*vfta_changed = fawse;
	} ewse {
		ww32(wx, WX_PSW_VWAN_SWC, 0);
	}

	wetuwn 0;
}

/**
 *  wx_set_vfta - Set VWAN fiwtew tabwe
 *  @wx: pointew to hawdwawe stwuctuwe
 *  @vwan: VWAN id to wwite to VWAN fiwtew
 *  @vind: VMDq output index that maps queue to VWAN id in VFVFB
 *  @vwan_on: boowean fwag to tuwn on/off VWAN in VFVF
 *
 *  Tuwn on/off specified VWAN in the VWAN fiwtew tabwe.
 **/
static int wx_set_vfta(stwuct wx *wx, u32 vwan, u32 vind, boow vwan_on)
{
	u32 bitindex, vfta, tawgetbit;
	boow vfta_changed = fawse;
	int wegindex, wet;

	/* this is a 2 pawt opewation - fiwst the VFTA, then the
	 * VWVF and VWVFB if VT Mode is set
	 * We don't wwite the VFTA untiw we know the VWVF pawt succeeded.
	 */

	/* Pawt 1
	 * The VFTA is a bitstwing made up of 128 32-bit wegistews
	 * that enabwe the pawticuwaw VWAN id, much wike the MTA:
	 *    bits[11-5]: which wegistew
	 *    bits[4-0]:  which bit in the wegistew
	 */
	wegindex = (vwan >> 5) & 0x7F;
	bitindex = vwan & 0x1F;
	tawgetbit = (1 << bitindex);
	/* ewwata 5 */
	vfta = wx->mac.vft_shadow[wegindex];
	if (vwan_on) {
		if (!(vfta & tawgetbit)) {
			vfta |= tawgetbit;
			vfta_changed = twue;
		}
	} ewse {
		if ((vfta & tawgetbit)) {
			vfta &= ~tawgetbit;
			vfta_changed = twue;
		}
	}
	/* Pawt 2
	 * Caww wx_set_vwvf to set VWVFB and VWVF
	 */
	wet = wx_set_vwvf(wx, vwan, vind, vwan_on, &vfta_changed);
	if (wet != 0)
		wetuwn wet;

	if (vfta_changed)
		ww32(wx, WX_PSW_VWAN_TBW(wegindex), vfta);
	wx->mac.vft_shadow[wegindex] = vfta;

	wetuwn 0;
}

/**
 *  wx_cweaw_vfta - Cweaw VWAN fiwtew tabwe
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Cweaws the VWAN fiwew tabwe, and the VMDq index associated with the fiwtew
 **/
static void wx_cweaw_vfta(stwuct wx *wx)
{
	u32 offset;

	fow (offset = 0; offset < wx->mac.vft_size; offset++) {
		ww32(wx, WX_PSW_VWAN_TBW(offset), 0);
		wx->mac.vft_shadow[offset] = 0;
	}

	fow (offset = 0; offset < WX_PSW_VWAN_SWC_ENTWIES; offset++) {
		ww32(wx, WX_PSW_VWAN_SWC_IDX, offset);
		ww32(wx, WX_PSW_VWAN_SWC, 0);
		ww32(wx, WX_PSW_VWAN_SWC_VM_W, 0);
		ww32(wx, WX_PSW_VWAN_SWC_VM_H, 0);
	}
}

int wx_vwan_wx_add_vid(stwuct net_device *netdev,
		       __be16 pwoto, u16 vid)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	/* add VID to fiwtew tabwe */
	wx_set_vfta(wx, vid, VMDQ_P(0), twue);
	set_bit(vid, wx->active_vwans);

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_vwan_wx_add_vid);

int wx_vwan_wx_kiww_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	/* wemove VID fwom fiwtew tabwe */
	if (vid)
		wx_set_vfta(wx, vid, VMDQ_P(0), fawse);
	cweaw_bit(vid, wx->active_vwans);

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_vwan_wx_kiww_vid);

static void wx_enabwe_wx_dwop(stwuct wx *wx, stwuct wx_wing *wing)
{
	u16 weg_idx = wing->weg_idx;
	u32 swwctw;

	swwctw = wd32(wx, WX_PX_WW_CFG(weg_idx));
	swwctw |= WX_PX_WW_CFG_DWOP_EN;

	ww32(wx, WX_PX_WW_CFG(weg_idx), swwctw);
}

static void wx_disabwe_wx_dwop(stwuct wx *wx, stwuct wx_wing *wing)
{
	u16 weg_idx = wing->weg_idx;
	u32 swwctw;

	swwctw = wd32(wx, WX_PX_WW_CFG(weg_idx));
	swwctw &= ~WX_PX_WW_CFG_DWOP_EN;

	ww32(wx, WX_PX_WW_CFG(weg_idx), swwctw);
}

int wx_fc_enabwe(stwuct wx *wx, boow tx_pause, boow wx_pause)
{
	u16 pause_time = WX_DEFAUWT_FCPAUSE;
	u32 mfwcn_weg, fccfg_weg, weg;
	u32 fcwtw, fcwth;
	int i;

	/* Wow watew mawk of zewo causes XOFF fwoods */
	if (tx_pause && wx->fc.high_watew) {
		if (!wx->fc.wow_watew || wx->fc.wow_watew >= wx->fc.high_watew) {
			wx_eww(wx, "Invawid watew mawk configuwation\n");
			wetuwn -EINVAW;
		}
	}

	/* Disabwe any pwevious fwow contwow settings */
	mfwcn_weg = wd32(wx, WX_MAC_WX_FWOW_CTWW);
	mfwcn_weg &= ~WX_MAC_WX_FWOW_CTWW_WFE;

	fccfg_weg = wd32(wx, WX_WDB_WFCC);
	fccfg_weg &= ~WX_WDB_WFCC_WFCE_802_3X;

	if (wx_pause)
		mfwcn_weg |= WX_MAC_WX_FWOW_CTWW_WFE;
	if (tx_pause)
		fccfg_weg |= WX_WDB_WFCC_WFCE_802_3X;

	/* Set 802.3x based fwow contwow settings. */
	ww32(wx, WX_MAC_WX_FWOW_CTWW, mfwcn_weg);
	ww32(wx, WX_WDB_WFCC, fccfg_weg);

	/* Set up and enabwe Wx high/wow watew mawk thweshowds, enabwe XON. */
	if (tx_pause && wx->fc.high_watew) {
		fcwtw = (wx->fc.wow_watew << 10) | WX_WDB_WFCW_XONE;
		ww32(wx, WX_WDB_WFCW, fcwtw);
		fcwth = (wx->fc.high_watew << 10) | WX_WDB_WFCH_XOFFE;
	} ewse {
		ww32(wx, WX_WDB_WFCW, 0);
		/* In owdew to pwevent Tx hangs when the intewnaw Tx
		 * switch is enabwed we must set the high watew mawk
		 * to the Wx packet buffew size - 24KB.  This awwows
		 * the Tx switch to function even undew heavy Wx
		 * wowkwoads.
		 */
		fcwth = wd32(wx, WX_WDB_PB_SZ(0)) - 24576;
	}

	ww32(wx, WX_WDB_WFCH, fcwth);

	/* Configuwe pause time */
	weg = pause_time * 0x00010001;
	ww32(wx, WX_WDB_WFCV, weg);

	/* Configuwe fwow contwow wefwesh thweshowd vawue */
	ww32(wx, WX_WDB_WFCWT, pause_time / 2);

	/*  We shouwd set the dwop enabwe bit if:
	 *  Numbew of Wx queues > 1 and fwow contwow is disabwed
	 *
	 *  This awwows us to avoid head of wine bwocking fow secuwity
	 *  and pewfowmance weasons.
	 */
	if (wx->num_wx_queues > 1 && !tx_pause) {
		fow (i = 0; i < wx->num_wx_queues; i++)
			wx_enabwe_wx_dwop(wx, wx->wx_wing[i]);
	} ewse {
		fow (i = 0; i < wx->num_wx_queues; i++)
			wx_disabwe_wx_dwop(wx, wx->wx_wing[i]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_fc_enabwe);

/**
 * wx_update_stats - Update the boawd statistics countews.
 * @wx: boawd pwivate stwuctuwe
 **/
void wx_update_stats(stwuct wx *wx)
{
	stwuct wx_hw_stats *hwstats = &wx->stats;

	u64 non_eop_descs = 0, awwoc_wx_buff_faiwed = 0;
	u64 hw_csum_wx_good = 0, hw_csum_wx_ewwow = 0;
	u64 westawt_queue = 0, tx_busy = 0;
	u32 i;

	/* gathew some stats to the wx stwuct that awe pew queue */
	fow (i = 0; i < wx->num_wx_queues; i++) {
		stwuct wx_wing *wx_wing = wx->wx_wing[i];

		non_eop_descs += wx_wing->wx_stats.non_eop_descs;
		awwoc_wx_buff_faiwed += wx_wing->wx_stats.awwoc_wx_buff_faiwed;
		hw_csum_wx_good += wx_wing->wx_stats.csum_good_cnt;
		hw_csum_wx_ewwow += wx_wing->wx_stats.csum_eww;
	}
	wx->non_eop_descs = non_eop_descs;
	wx->awwoc_wx_buff_faiwed = awwoc_wx_buff_faiwed;
	wx->hw_csum_wx_ewwow = hw_csum_wx_ewwow;
	wx->hw_csum_wx_good = hw_csum_wx_good;

	fow (i = 0; i < wx->num_tx_queues; i++) {
		stwuct wx_wing *tx_wing = wx->tx_wing[i];

		westawt_queue += tx_wing->tx_stats.westawt_queue;
		tx_busy += tx_wing->tx_stats.tx_busy;
	}
	wx->westawt_queue = westawt_queue;
	wx->tx_busy = tx_busy;

	hwstats->gpwc += wd32(wx, WX_WDM_PKT_CNT);
	hwstats->gptc += wd32(wx, WX_TDM_PKT_CNT);
	hwstats->gowc += wd64(wx, WX_WDM_BYTE_CNT_WSB);
	hwstats->gotc += wd64(wx, WX_TDM_BYTE_CNT_WSB);
	hwstats->tpw += wd64(wx, WX_WX_FWAME_CNT_GOOD_BAD_W);
	hwstats->tpt += wd64(wx, WX_TX_FWAME_CNT_GOOD_BAD_W);
	hwstats->cwcewws += wd64(wx, WX_WX_CWC_EWWOW_FWAMES_W);
	hwstats->wwec += wd64(wx, WX_WX_WEN_EWWOW_FWAMES_W);
	hwstats->bpwc += wd64(wx, WX_WX_BC_FWAMES_GOOD_W);
	hwstats->bptc += wd64(wx, WX_TX_BC_FWAMES_GOOD_W);
	hwstats->mpwc += wd64(wx, WX_WX_MC_FWAMES_GOOD_W);
	hwstats->mptc += wd64(wx, WX_TX_MC_FWAMES_GOOD_W);
	hwstats->woc += wd32(wx, WX_WX_OVEWSIZE_FWAMES_GOOD);
	hwstats->wuc += wd32(wx, WX_WX_UNDEWSIZE_FWAMES_GOOD);
	hwstats->wxonoffwxc += wd32(wx, WX_MAC_WXONOFFWXC);
	hwstats->wxontxc += wd32(wx, WX_WDB_WXONTXC);
	hwstats->wxofftxc += wd32(wx, WX_WDB_WXOFFTXC);
	hwstats->o2bgptc += wd32(wx, WX_TDM_OS2BMC_CNT);
	hwstats->b2ospc += wd32(wx, WX_MNG_BMC2OS_CNT);
	hwstats->o2bspc += wd32(wx, WX_MNG_OS2BMC_CNT);
	hwstats->b2ogpwc += wd32(wx, WX_WDM_BMC2OS_CNT);
	hwstats->wdmdwop += wd32(wx, WX_WDM_DWP_PKT);

	fow (i = 0; i < wx->mac.max_wx_queues; i++)
		hwstats->qmpwc += wd32(wx, WX_PX_MPWC(i));
}
EXPOWT_SYMBOW(wx_update_stats);

/**
 *  wx_cweaw_hw_cntws - Genewic cweaw hawdwawe countews
 *  @wx: boawd pwivate stwuctuwe
 *
 *  Cweaws aww hawdwawe statistics countews by weading them fwom the hawdwawe
 *  Statistics countews awe cweaw on wead.
 **/
void wx_cweaw_hw_cntws(stwuct wx *wx)
{
	u16 i = 0;

	fow (i = 0; i < wx->mac.max_wx_queues; i++)
		ww32(wx, WX_PX_MPWC(i), 0);

	wd32(wx, WX_WDM_PKT_CNT);
	wd32(wx, WX_TDM_PKT_CNT);
	wd64(wx, WX_WDM_BYTE_CNT_WSB);
	wd32(wx, WX_TDM_BYTE_CNT_WSB);
	wd32(wx, WX_WDM_DWP_PKT);
	wd32(wx, WX_WX_UNDEWSIZE_FWAMES_GOOD);
	wd32(wx, WX_WX_OVEWSIZE_FWAMES_GOOD);
	wd64(wx, WX_WX_FWAME_CNT_GOOD_BAD_W);
	wd64(wx, WX_TX_FWAME_CNT_GOOD_BAD_W);
	wd64(wx, WX_WX_MC_FWAMES_GOOD_W);
	wd64(wx, WX_TX_MC_FWAMES_GOOD_W);
	wd64(wx, WX_WX_BC_FWAMES_GOOD_W);
	wd64(wx, WX_TX_BC_FWAMES_GOOD_W);
	wd64(wx, WX_WX_CWC_EWWOW_FWAMES_W);
	wd64(wx, WX_WX_WEN_EWWOW_FWAMES_W);
	wd32(wx, WX_WDB_WXONTXC);
	wd32(wx, WX_WDB_WXOFFTXC);
	wd32(wx, WX_MAC_WXONOFFWXC);
}
EXPOWT_SYMBOW(wx_cweaw_hw_cntws);

/**
 *  wx_stawt_hw - Pwepawe hawdwawe fow Tx/Wx
 *  @wx: pointew to hawdwawe stwuctuwe
 *
 *  Stawts the hawdwawe using the genewic stawt_hw function
 *  and the genewation stawt_hw function.
 *  Then pewfowms wevision-specific opewations, if any.
 **/
void wx_stawt_hw(stwuct wx *wx)
{
	int i;

	/* Cweaw the VWAN fiwtew tabwe */
	wx_cweaw_vfta(wx);
	WX_WWITE_FWUSH(wx);
	/* Cweaw the wate wimitews */
	fow (i = 0; i < wx->mac.max_tx_queues; i++) {
		ww32(wx, WX_TDM_WP_IDX, i);
		ww32(wx, WX_TDM_WP_WATE, 0);
	}
}
EXPOWT_SYMBOW(wx_stawt_hw);

MODUWE_WICENSE("GPW");
