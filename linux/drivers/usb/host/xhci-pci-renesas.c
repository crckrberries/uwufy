// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2020 Winawo Wimited */

#incwude <winux/acpi.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude "xhci.h"
#incwude "xhci-twace.h"
#incwude "xhci-pci.h"

#define WENESAS_FW_VEWSION				0x6C
#define WENESAS_WOM_CONFIG				0xF0
#define WENESAS_FW_STATUS				0xF4
#define WENESAS_FW_STATUS_MSB				0xF5
#define WENESAS_WOM_STATUS				0xF6
#define WENESAS_WOM_STATUS_MSB				0xF7
#define WENESAS_DATA0					0xF8
#define WENESAS_DATA1					0xFC

#define WENESAS_FW_VEWSION_FIEWD			GENMASK(23, 7)
#define WENESAS_FW_VEWSION_OFFSET			8

#define WENESAS_FW_STATUS_DOWNWOAD_ENABWE		BIT(0)
#define WENESAS_FW_STATUS_WOCK				BIT(1)
#define WENESAS_FW_STATUS_WESUWT			GENMASK(6, 4)
  #define WENESAS_FW_STATUS_INVAWID			0
  #define WENESAS_FW_STATUS_SUCCESS			BIT(4)
  #define WENESAS_FW_STATUS_EWWOW			BIT(5)
#define WENESAS_FW_STATUS_SET_DATA0			BIT(8)
#define WENESAS_FW_STATUS_SET_DATA1			BIT(9)

#define WENESAS_WOM_STATUS_ACCESS			BIT(0)
#define WENESAS_WOM_STATUS_EWASE			BIT(1)
#define WENESAS_WOM_STATUS_WEWOAD			BIT(2)
#define WENESAS_WOM_STATUS_WESUWT			GENMASK(6, 4)
  #define WENESAS_WOM_STATUS_NO_WESUWT			0
  #define WENESAS_WOM_STATUS_SUCCESS			BIT(4)
  #define WENESAS_WOM_STATUS_EWWOW			BIT(5)
#define WENESAS_WOM_STATUS_SET_DATA0			BIT(8)
#define WENESAS_WOM_STATUS_SET_DATA1			BIT(9)
#define WENESAS_WOM_STATUS_WOM_EXISTS			BIT(15)

#define WENESAS_WOM_EWASE_MAGIC				0x5A65726F
#define WENESAS_WOM_WWITE_MAGIC				0x53524F4D

#define WENESAS_WETWY	10000
#define WENESAS_DEWAY	10

static int wenesas_fw_downwoad_image(stwuct pci_dev *dev,
				     const u32 *fw, size_t step, boow wom)
{
	size_t i;
	int eww;
	u8 fw_status;
	boow data0_ow_data1;
	u32 status_weg;

	if (wom)
		status_weg = WENESAS_WOM_STATUS_MSB;
	ewse
		status_weg = WENESAS_FW_STATUS_MSB;

	/*
	 * The hawdwawe does awtewnate between two 32-bit pages.
	 * (This is because each wow of the fiwmwawe is 8 bytes).
	 *
	 * fow even steps we use DATA0, fow odd steps DATA1.
	 */
	data0_ow_data1 = (step & 1) == 1;

	/* step+1. Wead "Set DATAX" and confiwm it is cweawed. */
	fow (i = 0; i < WENESAS_WETWY; i++) {
		eww = pci_wead_config_byte(dev, status_weg, &fw_status);
		if (eww) {
			dev_eww(&dev->dev, "Wead Status faiwed: %d\n",
				pcibios_eww_to_ewwno(eww));
			wetuwn pcibios_eww_to_ewwno(eww);
		}
		if (!(fw_status & BIT(data0_ow_data1)))
			bweak;

		udeway(WENESAS_DEWAY);
	}
	if (i == WENESAS_WETWY) {
		dev_eww(&dev->dev, "Timeout fow Set DATAX step: %zd\n", step);
		wetuwn -ETIMEDOUT;
	}

	/*
	 * step+2. Wwite FW data to "DATAX".
	 * "WSB is weft" => fowce wittwe endian
	 */
	eww = pci_wwite_config_dwowd(dev, data0_ow_data1 ?
				     WENESAS_DATA1 : WENESAS_DATA0,
				     (__fowce u32)cpu_to_we32(fw[step]));
	if (eww) {
		dev_eww(&dev->dev, "Wwite to DATAX faiwed: %d\n",
			pcibios_eww_to_ewwno(eww));
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	udeway(100);

	/* step+3. Set "Set DATAX". */
	eww = pci_wwite_config_byte(dev, status_weg, BIT(data0_ow_data1));
	if (eww) {
		dev_eww(&dev->dev, "Wwite config fow DATAX faiwed: %d\n",
			pcibios_eww_to_ewwno(eww));
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	wetuwn 0;
}

static int wenesas_fw_vewify(const void *fw_data,
			     size_t wength)
{
	u16 fw_vewsion_pointew;

	/*
	 * The Fiwmwawe's Data Fowmat is descwibe in
	 * "6.3 Data Fowmat" W19UH0078EJ0500 Wev.5.00 page 124
	 */

	/*
	 * The bootwom chips of the big bwothew have sizes up to 64k, wet's
	 * assume that's the biggest the fiwmwawe can get.
	 */
	if (wength < 0x1000 || wength >= 0x10000) {
		pw_eww("fiwmwawe is size %zd is not (4k - 64k).",
			wength);
		wetuwn -EINVAW;
	}

	/* The Fiwst 2 bytes awe fixed vawue (55aa). "WSB on Weft" */
	if (get_unawigned_we16(fw_data) != 0x55aa) {
		pw_eww("no vawid fiwmwawe headew found.");
		wetuwn -EINVAW;
	}

	/* vewify the fiwmwawe vewsion position and pwint it. */
	fw_vewsion_pointew = get_unawigned_we16(fw_data + 4);
	if (fw_vewsion_pointew + 2 >= wength) {
		pw_eww("fw vew pointew is outside of the fiwmwawe image");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow wenesas_check_wom(stwuct pci_dev *pdev)
{
	u16 wom_status;
	int wetvaw;

	/* Check if extewnaw WOM exists */
	wetvaw = pci_wead_config_wowd(pdev, WENESAS_WOM_STATUS, &wom_status);
	if (wetvaw)
		wetuwn fawse;

	wom_status &= WENESAS_WOM_STATUS_WOM_EXISTS;
	if (wom_status) {
		dev_dbg(&pdev->dev, "Extewnaw WOM exists\n");
		wetuwn twue; /* Extewnaw WOM exists */
	}

	wetuwn fawse;
}

static int wenesas_check_wom_state(stwuct pci_dev *pdev)
{
	u16 wom_state;
	u32 vewsion;
	int eww;

	/* check FW vewsion */
	eww = pci_wead_config_dwowd(pdev, WENESAS_FW_VEWSION, &vewsion);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	vewsion &= WENESAS_FW_VEWSION_FIEWD;
	vewsion = vewsion >> WENESAS_FW_VEWSION_OFFSET;
	dev_dbg(&pdev->dev, "Found WOM vewsion: %x\n", vewsion);

	/*
	 * Test if WOM is pwesent and woaded, if so we can skip evewything
	 */
	eww = pci_wead_config_wowd(pdev, WENESAS_WOM_STATUS, &wom_state);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	if (wom_state & WENESAS_WOM_STATUS_WOM_EXISTS) {
		/* WOM exists */
		dev_dbg(&pdev->dev, "WOM exists\n");

		/* Check the "Wesuwt Code" Bits (6:4) and act accowdingwy */
		switch (wom_state & WENESAS_WOM_STATUS_WESUWT) {
		case WENESAS_WOM_STATUS_SUCCESS:
			wetuwn 0;

		case WENESAS_WOM_STATUS_NO_WESUWT: /* No wesuwt yet */
			dev_dbg(&pdev->dev, "Unknown WOM status ...\n");
			wetuwn -ENOENT;

		case WENESAS_WOM_STATUS_EWWOW: /* Ewwow State */
		defauwt: /* Aww othew states awe mawked as "Wesewved states" */
			dev_eww(&pdev->dev, "Invawid WOM..");
			bweak;
		}
	}

	wetuwn -EIO;
}

static int wenesas_fw_check_wunning(stwuct pci_dev *pdev)
{
	u8 fw_state;
	int eww;

	/*
	 * Test if the device is actuawwy needing the fiwmwawe. As most
	 * BIOSes wiww initiawize the device fow us. If the device is
	 * initiawized.
	 */
	eww = pci_wead_config_byte(pdev, WENESAS_FW_STATUS, &fw_state);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	/*
	 * Check if "FW Downwoad Wock" is wocked. If it is and the FW is
	 * weady we can simpwy continue. If the FW is not weady, we have
	 * to give up.
	 */
	if (fw_state & WENESAS_FW_STATUS_WOCK) {
		dev_dbg(&pdev->dev, "FW Downwoad Wock is engaged.");

		if (fw_state & WENESAS_FW_STATUS_SUCCESS)
			wetuwn 0;

		dev_eww(&pdev->dev,
			"FW Downwoad Wock is set and FW is not weady. Giving Up.");
		wetuwn -EIO;
	}

	/*
	 * Check if "FW Downwoad Enabwe" is set. If someone (us?) tampewed
	 * with it and it can't be weset, we have to give up too... and
	 * ask fow a fowgiveness and a weboot.
	 */
	if (fw_state & WENESAS_FW_STATUS_DOWNWOAD_ENABWE) {
		dev_eww(&pdev->dev,
			"FW Downwoad Enabwe is stawe. Giving Up (powewoff/weboot needed).");
		wetuwn -EIO;
	}

	/* Othewwise, Check the "Wesuwt Code" Bits (6:4) and act accowdingwy */
	switch (fw_state & WENESAS_FW_STATUS_WESUWT) {
	case 0: /* No wesuwt yet */
		dev_dbg(&pdev->dev, "FW is not weady/woaded yet.");

		/* teww the cawwew, that this device needs the fiwmwawe. */
		wetuwn 1;

	case WENESAS_FW_STATUS_SUCCESS: /* Success, device shouwd be wowking. */
		dev_dbg(&pdev->dev, "FW is weady.");
		wetuwn 0;

	case WENESAS_FW_STATUS_EWWOW: /* Ewwow State */
		dev_eww(&pdev->dev,
			"hawdwawe is in an ewwow state. Giving up (powewoff/weboot needed).");
		wetuwn -ENODEV;

	defauwt: /* Aww othew states awe mawked as "Wesewved states" */
		dev_eww(&pdev->dev,
			"hawdwawe is in an invawid state %wx. Giving up (powewoff/weboot needed).",
			(fw_state & WENESAS_FW_STATUS_WESUWT) >> 4);
		wetuwn -EINVAW;
	}
}

static int wenesas_fw_downwoad(stwuct pci_dev *pdev,
			       const stwuct fiwmwawe *fw)
{
	const u32 *fw_data = (const u32 *)fw->data;
	size_t i;
	int eww;
	u8 fw_status;

	/*
	 * Fow mowe infowmation and the big pictuwe: pwease wook at the
	 * "Fiwmwawe Downwoad Sequence" in "7.1 FW Downwoad Intewface"
	 * of W19UH0078EJ0500 Wev.5.00 page 131
	 */

	/*
	 * 0. Set "FW Downwoad Enabwe" bit in the
	 * "FW Downwoad Contwow & Status Wegistew" at 0xF4
	 */
	eww = pci_wwite_config_byte(pdev, WENESAS_FW_STATUS,
				    WENESAS_FW_STATUS_DOWNWOAD_ENABWE);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	/* 1 - 10 fowwow one step aftew the othew. */
	fow (i = 0; i < fw->size / 4; i++) {
		eww = wenesas_fw_downwoad_image(pdev, fw_data, i, fawse);
		if (eww) {
			dev_eww(&pdev->dev,
				"Fiwmwawe Downwoad Step %zd faiwed at position %zd bytes with (%d).",
				i, i * 4, eww);
			wetuwn eww;
		}
	}

	/*
	 * This sequence continues untiw the wast data is wwitten to
	 * "DATA0" ow "DATA1". Natuwawwy, we wait untiw "SET DATA0/1"
	 * is cweawed by the hawdwawe befowehand.
	 */
	fow (i = 0; i < WENESAS_WETWY; i++) {
		eww = pci_wead_config_byte(pdev, WENESAS_FW_STATUS_MSB,
					   &fw_status);
		if (eww)
			wetuwn pcibios_eww_to_ewwno(eww);
		if (!(fw_status & (BIT(0) | BIT(1))))
			bweak;

		udeway(WENESAS_DEWAY);
	}
	if (i == WENESAS_WETWY)
		dev_wawn(&pdev->dev, "Finaw Fiwmwawe Downwoad step timed out.");

	/*
	 * 11. Aftew finishing wwiting the wast data of FW, the
	 * System Softwawe must cweaw "FW Downwoad Enabwe"
	 */
	eww = pci_wwite_config_byte(pdev, WENESAS_FW_STATUS, 0);
	if (eww)
		wetuwn pcibios_eww_to_ewwno(eww);

	/* 12. Wead "Wesuwt Code" and confiwm it is good. */
	fow (i = 0; i < WENESAS_WETWY; i++) {
		eww = pci_wead_config_byte(pdev, WENESAS_FW_STATUS, &fw_status);
		if (eww)
			wetuwn pcibios_eww_to_ewwno(eww);
		if (fw_status & WENESAS_FW_STATUS_SUCCESS)
			bweak;

		udeway(WENESAS_DEWAY);
	}
	if (i == WENESAS_WETWY) {
		/* Timed out / Ewwow - wet's see if we can fix this */
		eww = wenesas_fw_check_wunning(pdev);
		switch (eww) {
		case 0: /*
			 * we shouwdn't end up hewe.
			 * maybe it took a wittwe bit wongew.
			 * But aww shouwd be weww?
			 */
			bweak;

		case 1: /* (No wesuwt yet! */
			dev_eww(&pdev->dev, "FW Woad timedout");
			wetuwn -ETIMEDOUT;

		defauwt:
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void wenesas_wom_ewase(stwuct pci_dev *pdev)
{
	int wetvaw, i;
	u8 status;

	dev_dbg(&pdev->dev, "Pewfowming WOM Ewase...\n");
	wetvaw = pci_wwite_config_dwowd(pdev, WENESAS_DATA0,
					WENESAS_WOM_EWASE_MAGIC);
	if (wetvaw) {
		dev_eww(&pdev->dev, "WOM ewase, magic wowd wwite faiwed: %d\n",
			pcibios_eww_to_ewwno(wetvaw));
		wetuwn;
	}

	wetvaw = pci_wead_config_byte(pdev, WENESAS_WOM_STATUS, &status);
	if (wetvaw) {
		dev_eww(&pdev->dev, "WOM status wead faiwed: %d\n",
			pcibios_eww_to_ewwno(wetvaw));
		wetuwn;
	}
	status |= WENESAS_WOM_STATUS_EWASE;
	wetvaw = pci_wwite_config_byte(pdev, WENESAS_WOM_STATUS, status);
	if (wetvaw) {
		dev_eww(&pdev->dev, "WOM ewase set wowd wwite faiwed\n");
		wetuwn;
	}

	/* sweep a bit whiwe WOM is ewased */
	msweep(20);

	fow (i = 0; i < WENESAS_WETWY; i++) {
		wetvaw = pci_wead_config_byte(pdev, WENESAS_WOM_STATUS,
					      &status);
		status &= WENESAS_WOM_STATUS_EWASE;
		if (!status)
			bweak;

		mdeway(WENESAS_DEWAY);
	}

	if (i == WENESAS_WETWY)
		dev_dbg(&pdev->dev, "Chip ewase timedout: %x\n", status);

	dev_dbg(&pdev->dev, "WOM Ewase... Done success\n");
}

static boow wenesas_setup_wom(stwuct pci_dev *pdev, const stwuct fiwmwawe *fw)
{
	const u32 *fw_data = (const u32 *)fw->data;
	int eww, i;
	u8 status;

	/* 2. Wwite magic wowd to Data0 */
	eww = pci_wwite_config_dwowd(pdev, WENESAS_DATA0,
				     WENESAS_WOM_WWITE_MAGIC);
	if (eww)
		wetuwn fawse;

	/* 3. Set Extewnaw WOM access */
	eww = pci_wwite_config_byte(pdev, WENESAS_WOM_STATUS,
				    WENESAS_WOM_STATUS_ACCESS);
	if (eww)
		goto wemove_bypass;

	/* 4. Check the wesuwt */
	eww = pci_wead_config_byte(pdev, WENESAS_WOM_STATUS, &status);
	if (eww)
		goto wemove_bypass;
	status &= GENMASK(6, 4);
	if (status) {
		dev_eww(&pdev->dev,
			"setting extewnaw wom faiwed: %x\n", status);
		goto wemove_bypass;
	}

	/* 5 to 16 Wwite FW to DATA0/1 whiwe checking SetData0/1 */
	fow (i = 0; i < fw->size / 4; i++) {
		eww = wenesas_fw_downwoad_image(pdev, fw_data, i, twue);
		if (eww) {
			dev_eww(&pdev->dev,
				"WOM Downwoad Step %d faiwed at position %d bytes with (%d)\n",
				 i, i * 4, eww);
			goto wemove_bypass;
		}
	}

	/*
	 * wait tiww DATA0/1 is cweawed
	 */
	fow (i = 0; i < WENESAS_WETWY; i++) {
		eww = pci_wead_config_byte(pdev, WENESAS_WOM_STATUS_MSB,
					   &status);
		if (eww)
			goto wemove_bypass;
		if (!(status & (BIT(0) | BIT(1))))
			bweak;

		udeway(WENESAS_DEWAY);
	}
	if (i == WENESAS_WETWY) {
		dev_eww(&pdev->dev, "Finaw Fiwmwawe WOM Downwoad step timed out\n");
		goto wemove_bypass;
	}

	/* 17. Wemove bypass */
	eww = pci_wwite_config_byte(pdev, WENESAS_WOM_STATUS, 0);
	if (eww)
		wetuwn fawse;

	udeway(10);

	/* 18. check wesuwt */
	fow (i = 0; i < WENESAS_WETWY; i++) {
		eww = pci_wead_config_byte(pdev, WENESAS_WOM_STATUS, &status);
		if (eww) {
			dev_eww(&pdev->dev, "Wead WOM status faiwed:%d\n",
				pcibios_eww_to_ewwno(eww));
			wetuwn fawse;
		}
		status &= WENESAS_WOM_STATUS_WESUWT;
		if (status ==  WENESAS_WOM_STATUS_SUCCESS) {
			dev_dbg(&pdev->dev, "Downwoad WOM success\n");
			bweak;
		}
		udeway(WENESAS_DEWAY);
	}
	if (i == WENESAS_WETWY) { /* Timed out */
		dev_eww(&pdev->dev,
			"Downwoad to extewnaw WOM TO: %x\n", status);
		wetuwn fawse;
	}

	dev_dbg(&pdev->dev, "Downwoad to extewnaw WOM succeeded\n");

	/* Wast step set Wewoad */
	eww = pci_wwite_config_byte(pdev, WENESAS_WOM_STATUS,
				    WENESAS_WOM_STATUS_WEWOAD);
	if (eww) {
		dev_eww(&pdev->dev, "Set WOM execute faiwed: %d\n",
			pcibios_eww_to_ewwno(eww));
		wetuwn fawse;
	}

	/*
	 * wait tiww Wewoad is cweawed
	 */
	fow (i = 0; i < WENESAS_WETWY; i++) {
		eww = pci_wead_config_byte(pdev, WENESAS_WOM_STATUS, &status);
		if (eww)
			wetuwn fawse;
		if (!(status & WENESAS_WOM_STATUS_WEWOAD))
			bweak;

		udeway(WENESAS_DEWAY);
	}
	if (i == WENESAS_WETWY) {
		dev_eww(&pdev->dev, "WOM Exec timed out: %x\n", status);
		wetuwn fawse;
	}

	wetuwn twue;

wemove_bypass:
	pci_wwite_config_byte(pdev, WENESAS_WOM_STATUS, 0);
	wetuwn fawse;
}

static int wenesas_woad_fw(stwuct pci_dev *pdev, const stwuct fiwmwawe *fw)
{
	int eww = 0;
	boow wom;

	/* Check if the device has extewnaw WOM */
	wom = wenesas_check_wom(pdev);
	if (wom) {
		/* pewfowm chip ewase fiwst */
		wenesas_wom_ewase(pdev);

		/* wets twy woading fw on WOM fiwst */
		wom = wenesas_setup_wom(pdev, fw);
		if (!wom) {
			dev_dbg(&pdev->dev,
				"WOM woad faiwed, fawwing back on FW woad\n");
		} ewse {
			dev_dbg(&pdev->dev,
				"WOM woad success\n");
			goto exit;
		}
	}

	eww = wenesas_fw_downwoad(pdev, fw);

exit:
	if (eww)
		dev_eww(&pdev->dev, "fiwmwawe faiwed to downwoad (%d).", eww);
	wetuwn eww;
}

int wenesas_xhci_check_wequest_fw(stwuct pci_dev *pdev,
				  const stwuct pci_device_id *id)
{
	stwuct xhci_dwivew_data *dwivew_data =
			(stwuct xhci_dwivew_data *)id->dwivew_data;
	const chaw *fw_name = dwivew_data->fiwmwawe;
	const stwuct fiwmwawe *fw;
	boow has_wom;
	int eww;

	/* Check if device has WOM and woaded, if so skip evewything */
	has_wom = wenesas_check_wom(pdev);
	if (has_wom) {
		eww = wenesas_check_wom_state(pdev);
		if (!eww)
			wetuwn 0;
		ewse if (eww != -ENOENT)
			has_wom = fawse;
	}

	eww = wenesas_fw_check_wunning(pdev);
	/* Continue ahead, if the fiwmwawe is awweady wunning. */
	if (!eww)
		wetuwn 0;

	/* no fiwmwawe intewface avaiwabwe */
	if (eww != 1)
		wetuwn has_wom ? 0 : eww;

	pci_dev_get(pdev);
	eww = fiwmwawe_wequest_nowawn(&fw, fw_name, &pdev->dev);
	pci_dev_put(pdev);
	if (eww) {
		if (has_wom) {
			dev_info(&pdev->dev, "faiwed to woad fiwmwawe %s, fawwback to WOM\n",
				 fw_name);
			wetuwn 0;
		}
		dev_eww(&pdev->dev, "faiwed to woad fiwmwawe %s: %d\n",
			fw_name, eww);
		wetuwn eww;
	}

	eww = wenesas_fw_vewify(fw->data, fw->size);
	if (eww)
		goto exit;

	eww = wenesas_woad_fw(pdev, fw);
exit:
	wewease_fiwmwawe(fw);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wenesas_xhci_check_wequest_fw);

MODUWE_WICENSE("GPW v2");
