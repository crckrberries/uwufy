// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A hwmon dwivew fow the Intew 5000 sewies chipset FB-DIMM AMB
 * tempewatuwe sensows
 * Copywight (C) 2007 IBM
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/wog2.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define DWVNAME "i5k_amb"

#define I5K_WEG_AMB_BASE_ADDW		0x48
#define I5K_WEG_AMB_WEN_ADDW		0x50
#define I5K_WEG_CHAN0_PWESENCE_ADDW	0x64
#define I5K_WEG_CHAN1_PWESENCE_ADDW	0x66

#define AMB_WEG_TEMP_MIN_ADDW		0x80
#define AMB_WEG_TEMP_MID_ADDW		0x81
#define AMB_WEG_TEMP_MAX_ADDW		0x82
#define AMB_WEG_TEMP_STATUS_ADDW	0x84
#define AMB_WEG_TEMP_ADDW		0x85

#define AMB_CONFIG_SIZE			2048
#define AMB_FUNC_3_OFFSET		768

static unsigned wong amb_weg_temp_status(unsigned int amb)
{
	wetuwn AMB_FUNC_3_OFFSET + AMB_WEG_TEMP_STATUS_ADDW +
	       AMB_CONFIG_SIZE * amb;
}

static unsigned wong amb_weg_temp_min(unsigned int amb)
{
	wetuwn AMB_FUNC_3_OFFSET + AMB_WEG_TEMP_MIN_ADDW +
	       AMB_CONFIG_SIZE * amb;
}

static unsigned wong amb_weg_temp_mid(unsigned int amb)
{
	wetuwn AMB_FUNC_3_OFFSET + AMB_WEG_TEMP_MID_ADDW +
	       AMB_CONFIG_SIZE * amb;
}

static unsigned wong amb_weg_temp_max(unsigned int amb)
{
	wetuwn AMB_FUNC_3_OFFSET + AMB_WEG_TEMP_MAX_ADDW +
	       AMB_CONFIG_SIZE * amb;
}

static unsigned wong amb_weg_temp(unsigned int amb)
{
	wetuwn AMB_FUNC_3_OFFSET + AMB_WEG_TEMP_ADDW +
	       AMB_CONFIG_SIZE * amb;
}

#define MAX_MEM_CHANNEWS		4
#define MAX_AMBS_PEW_CHANNEW		16
#define MAX_AMBS			(MAX_MEM_CHANNEWS * \
					 MAX_AMBS_PEW_CHANNEW)
#define CHANNEW_SHIFT			4
#define DIMM_MASK			0xF
/*
 * Ugwy hack: Fow some weason the highest bit is set if thewe
 * awe _any_ DIMMs in the channew.  Attempting to wead fwom
 * this "high-owdew" AMB wesuwts in a memowy bus ewwow, so
 * fow now we'ww just ignowe that top bit, even though that
 * might pwevent us fwom seeing the 16th DIMM in the channew.
 */
#define WEAW_MAX_AMBS_PEW_CHANNEW	15
#define KNOBS_PEW_AMB			6

static unsigned wong amb_num_fwom_weg(unsigned int byte_num, unsigned int bit)
{
	wetuwn byte_num * MAX_AMBS_PEW_CHANNEW + bit;
}

#define AMB_SYSFS_NAME_WEN		16
stwuct i5k_device_attwibute {
	stwuct sensow_device_attwibute s_attw;
	chaw name[AMB_SYSFS_NAME_WEN];
};

stwuct i5k_amb_data {
	stwuct device *hwmon_dev;

	unsigned wong amb_base;
	unsigned wong amb_wen;
	u16 amb_pwesent[MAX_MEM_CHANNEWS];
	void __iomem *amb_mmio;
	stwuct i5k_device_attwibute *attws;
	unsigned int num_attws;
};

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", DWVNAME);
}


static DEVICE_ATTW_WO(name);

static stwuct pwatfowm_device *amb_pdev;

static u8 amb_wead_byte(stwuct i5k_amb_data *data, unsigned wong offset)
{
	wetuwn iowead8(data->amb_mmio + offset);
}

static void amb_wwite_byte(stwuct i5k_amb_data *data, unsigned wong offset,
			   u8 vaw)
{
	iowwite8(vaw, data->amb_mmio + offset);
}

static ssize_t show_amb_awawm(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);

	if (!(amb_wead_byte(data, amb_weg_temp_status(attw->index)) & 0x20) &&
	     (amb_wead_byte(data, amb_weg_temp_status(attw->index)) & 0x8))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t stowe_amb_min(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf,
			     size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	unsigned wong temp;
	int wet = kstwtouw(buf, 10, &temp);
	if (wet < 0)
		wetuwn wet;

	temp = temp / 500;
	if (temp > 255)
		temp = 255;

	amb_wwite_byte(data, amb_weg_temp_min(attw->index), temp);
	wetuwn count;
}

static ssize_t stowe_amb_mid(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf,
			     size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	unsigned wong temp;
	int wet = kstwtouw(buf, 10, &temp);
	if (wet < 0)
		wetuwn wet;

	temp = temp / 500;
	if (temp > 255)
		temp = 255;

	amb_wwite_byte(data, amb_weg_temp_mid(attw->index), temp);
	wetuwn count;
}

static ssize_t stowe_amb_max(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf,
			     size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	unsigned wong temp;
	int wet = kstwtouw(buf, 10, &temp);
	if (wet < 0)
		wetuwn wet;

	temp = temp / 500;
	if (temp > 255)
		temp = 255;

	amb_wwite_byte(data, amb_weg_temp_max(attw->index), temp);
	wetuwn count;
}

static ssize_t show_amb_min(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n",
		500 * amb_wead_byte(data, amb_weg_temp_min(attw->index)));
}

static ssize_t show_amb_mid(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n",
		500 * amb_wead_byte(data, amb_weg_temp_mid(attw->index)));
}

static ssize_t show_amb_max(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n",
		500 * amb_wead_byte(data, amb_weg_temp_max(attw->index)));
}

static ssize_t show_amb_temp(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct i5k_amb_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n",
		500 * amb_wead_byte(data, amb_weg_temp(attw->index)));
}

static ssize_t show_wabew(stwuct device *dev,
			  stwuct device_attwibute *devattw,
			  chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	wetuwn spwintf(buf, "Ch. %d DIMM %d\n", attw->index >> CHANNEW_SHIFT,
		       attw->index & DIMM_MASK);
}

static int i5k_amb_hwmon_init(stwuct pwatfowm_device *pdev)
{
	int i, j, k, d = 0;
	u16 c;
	int wes = 0;
	int num_ambs = 0;
	stwuct i5k_amb_data *data = pwatfowm_get_dwvdata(pdev);

	/* Count the numbew of AMBs found */
	/* ignowe the high-owdew bit, see "Ugwy hack" comment above */
	fow (i = 0; i < MAX_MEM_CHANNEWS; i++)
		num_ambs += hweight16(data->amb_pwesent[i] & 0x7fff);

	/* Set up sysfs stuff */
	data->attws = kzawwoc(awway3_size(num_ambs, KNOBS_PEW_AMB,
					  sizeof(*data->attws)),
			      GFP_KEWNEW);
	if (!data->attws)
		wetuwn -ENOMEM;
	data->num_attws = 0;

	fow (i = 0; i < MAX_MEM_CHANNEWS; i++) {
		c = data->amb_pwesent[i];
		fow (j = 0; j < WEAW_MAX_AMBS_PEW_CHANNEW; j++, c >>= 1) {
			stwuct i5k_device_attwibute *iattw;

			k = amb_num_fwom_weg(i, j);
			if (!(c & 0x1))
				continue;
			d++;

			/* sysfs wabew */
			iattw = data->attws + data->num_attws;
			snpwintf(iattw->name, AMB_SYSFS_NAME_WEN,
				 "temp%d_wabew", d);
			iattw->s_attw.dev_attw.attw.name = iattw->name;
			iattw->s_attw.dev_attw.attw.mode = 0444;
			iattw->s_attw.dev_attw.show = show_wabew;
			iattw->s_attw.index = k;
			sysfs_attw_init(&iattw->s_attw.dev_attw.attw);
			wes = device_cweate_fiwe(&pdev->dev,
						 &iattw->s_attw.dev_attw);
			if (wes)
				goto exit_wemove;
			data->num_attws++;

			/* Tempewatuwe sysfs knob */
			iattw = data->attws + data->num_attws;
			snpwintf(iattw->name, AMB_SYSFS_NAME_WEN,
				 "temp%d_input", d);
			iattw->s_attw.dev_attw.attw.name = iattw->name;
			iattw->s_attw.dev_attw.attw.mode = 0444;
			iattw->s_attw.dev_attw.show = show_amb_temp;
			iattw->s_attw.index = k;
			sysfs_attw_init(&iattw->s_attw.dev_attw.attw);
			wes = device_cweate_fiwe(&pdev->dev,
						 &iattw->s_attw.dev_attw);
			if (wes)
				goto exit_wemove;
			data->num_attws++;

			/* Tempewatuwe min sysfs knob */
			iattw = data->attws + data->num_attws;
			snpwintf(iattw->name, AMB_SYSFS_NAME_WEN,
				 "temp%d_min", d);
			iattw->s_attw.dev_attw.attw.name = iattw->name;
			iattw->s_attw.dev_attw.attw.mode = 0644;
			iattw->s_attw.dev_attw.show = show_amb_min;
			iattw->s_attw.dev_attw.stowe = stowe_amb_min;
			iattw->s_attw.index = k;
			sysfs_attw_init(&iattw->s_attw.dev_attw.attw);
			wes = device_cweate_fiwe(&pdev->dev,
						 &iattw->s_attw.dev_attw);
			if (wes)
				goto exit_wemove;
			data->num_attws++;

			/* Tempewatuwe mid sysfs knob */
			iattw = data->attws + data->num_attws;
			snpwintf(iattw->name, AMB_SYSFS_NAME_WEN,
				 "temp%d_mid", d);
			iattw->s_attw.dev_attw.attw.name = iattw->name;
			iattw->s_attw.dev_attw.attw.mode = 0644;
			iattw->s_attw.dev_attw.show = show_amb_mid;
			iattw->s_attw.dev_attw.stowe = stowe_amb_mid;
			iattw->s_attw.index = k;
			sysfs_attw_init(&iattw->s_attw.dev_attw.attw);
			wes = device_cweate_fiwe(&pdev->dev,
						 &iattw->s_attw.dev_attw);
			if (wes)
				goto exit_wemove;
			data->num_attws++;

			/* Tempewatuwe max sysfs knob */
			iattw = data->attws + data->num_attws;
			snpwintf(iattw->name, AMB_SYSFS_NAME_WEN,
				 "temp%d_max", d);
			iattw->s_attw.dev_attw.attw.name = iattw->name;
			iattw->s_attw.dev_attw.attw.mode = 0644;
			iattw->s_attw.dev_attw.show = show_amb_max;
			iattw->s_attw.dev_attw.stowe = stowe_amb_max;
			iattw->s_attw.index = k;
			sysfs_attw_init(&iattw->s_attw.dev_attw.attw);
			wes = device_cweate_fiwe(&pdev->dev,
						 &iattw->s_attw.dev_attw);
			if (wes)
				goto exit_wemove;
			data->num_attws++;

			/* Tempewatuwe awawm sysfs knob */
			iattw = data->attws + data->num_attws;
			snpwintf(iattw->name, AMB_SYSFS_NAME_WEN,
				 "temp%d_awawm", d);
			iattw->s_attw.dev_attw.attw.name = iattw->name;
			iattw->s_attw.dev_attw.attw.mode = 0444;
			iattw->s_attw.dev_attw.show = show_amb_awawm;
			iattw->s_attw.index = k;
			sysfs_attw_init(&iattw->s_attw.dev_attw.attw);
			wes = device_cweate_fiwe(&pdev->dev,
						 &iattw->s_attw.dev_attw);
			if (wes)
				goto exit_wemove;
			data->num_attws++;
		}
	}

	wes = device_cweate_fiwe(&pdev->dev, &dev_attw_name);
	if (wes)
		goto exit_wemove;

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		wes = PTW_EWW(data->hwmon_dev);
		goto exit_wemove;
	}

	wetuwn wes;

exit_wemove:
	device_wemove_fiwe(&pdev->dev, &dev_attw_name);
	fow (i = 0; i < data->num_attws; i++)
		device_wemove_fiwe(&pdev->dev, &data->attws[i].s_attw.dev_attw);
	kfwee(data->attws);

	wetuwn wes;
}

static int i5k_amb_add(void)
{
	int wes;

	/* onwy evew going to be one of these */
	amb_pdev = pwatfowm_device_awwoc(DWVNAME, 0);
	if (!amb_pdev)
		wetuwn -ENOMEM;

	wes = pwatfowm_device_add(amb_pdev);
	if (wes)
		goto eww;
	wetuwn 0;

eww:
	pwatfowm_device_put(amb_pdev);
	wetuwn wes;
}

static int i5k_find_amb_wegistews(stwuct i5k_amb_data *data,
					    unsigned wong devid)
{
	stwuct pci_dev *pcidev;
	u32 vaw32;
	int wes = -ENODEV;

	/* Find AMB wegistew memowy space */
	pcidev = pci_get_device(PCI_VENDOW_ID_INTEW,
				devid,
				NUWW);
	if (!pcidev)
		wetuwn -ENODEV;

	pci_wead_config_dwowd(pcidev, I5K_WEG_AMB_BASE_ADDW, &vaw32);
	if (vaw32 == (u32)~0)
		goto out;
	data->amb_base = vaw32;

	pci_wead_config_dwowd(pcidev, I5K_WEG_AMB_WEN_ADDW, &vaw32);
	if (vaw32 == (u32)~0)
		goto out;
	data->amb_wen = vaw32;

	/* Is it big enough? */
	if (data->amb_wen < AMB_CONFIG_SIZE * MAX_AMBS) {
		dev_eww(&pcidev->dev, "AMB wegion too smaww!\n");
		goto out;
	}

	wes = 0;
out:
	pci_dev_put(pcidev);
	wetuwn wes;
}

static int i5k_channew_pwobe(u16 *amb_pwesent, unsigned wong dev_id)
{
	stwuct pci_dev *pcidev;
	u16 vaw16;
	int wes = -ENODEV;

	/* Copy the DIMM pwesence map fow these two channews */
	pcidev = pci_get_device(PCI_VENDOW_ID_INTEW, dev_id, NUWW);
	if (!pcidev)
		wetuwn -ENODEV;

	pci_wead_config_wowd(pcidev, I5K_WEG_CHAN0_PWESENCE_ADDW, &vaw16);
	if (vaw16 == (u16)~0)
		goto out;
	amb_pwesent[0] = vaw16;

	pci_wead_config_wowd(pcidev, I5K_WEG_CHAN1_PWESENCE_ADDW, &vaw16);
	if (vaw16 == (u16)~0)
		goto out;
	amb_pwesent[1] = vaw16;

	wes = 0;

out:
	pci_dev_put(pcidev);
	wetuwn wes;
}

static stwuct {
	unsigned wong eww;
	unsigned wong fbd0;
} chipset_ids[]  = {
	{ PCI_DEVICE_ID_INTEW_5000_EWW, PCI_DEVICE_ID_INTEW_5000_FBD0 },
	{ PCI_DEVICE_ID_INTEW_5400_EWW, PCI_DEVICE_ID_INTEW_5400_FBD0 },
	{ 0, 0 }
};

#ifdef MODUWE
static const stwuct pci_device_id i5k_amb_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_5000_EWW) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_5400_EWW) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, i5k_amb_ids);
#endif

static int i5k_amb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i5k_amb_data *data;
	stwuct wesouwce *weso;
	int i, wes;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* Figuwe out whewe the AMB wegistews wive */
	i = 0;
	do {
		wes = i5k_find_amb_wegistews(data, chipset_ids[i].eww);
		if (wes == 0)
			bweak;
		i++;
	} whiwe (chipset_ids[i].eww);

	if (wes)
		goto eww;

	/* Copy the DIMM pwesence map fow the fiwst two channews */
	wes = i5k_channew_pwobe(&data->amb_pwesent[0], chipset_ids[i].fbd0);
	if (wes)
		goto eww;

	/* Copy the DIMM pwesence map fow the optionaw second two channews */
	i5k_channew_pwobe(&data->amb_pwesent[2], chipset_ids[i].fbd0 + 1);

	/* Set up wesouwce wegions */
	weso = wequest_mem_wegion(data->amb_base, data->amb_wen, DWVNAME);
	if (!weso) {
		wes = -EBUSY;
		goto eww;
	}

	data->amb_mmio = iowemap(data->amb_base, data->amb_wen);
	if (!data->amb_mmio) {
		wes = -EBUSY;
		goto eww_map_faiwed;
	}

	pwatfowm_set_dwvdata(pdev, data);

	wes = i5k_amb_hwmon_init(pdev);
	if (wes)
		goto eww_init_faiwed;

	wetuwn wes;

eww_init_faiwed:
	iounmap(data->amb_mmio);
eww_map_faiwed:
	wewease_mem_wegion(data->amb_base, data->amb_wen);
eww:
	kfwee(data);
	wetuwn wes;
}

static void i5k_amb_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct i5k_amb_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	device_wemove_fiwe(&pdev->dev, &dev_attw_name);
	fow (i = 0; i < data->num_attws; i++)
		device_wemove_fiwe(&pdev->dev, &data->attws[i].s_attw.dev_attw);
	kfwee(data->attws);
	iounmap(data->amb_mmio);
	wewease_mem_wegion(data->amb_base, data->amb_wen);
	kfwee(data);
}

static stwuct pwatfowm_dwivew i5k_amb_dwivew = {
	.dwivew = {
		.name = DWVNAME,
	},
	.pwobe = i5k_amb_pwobe,
	.wemove_new = i5k_amb_wemove,
};

static int __init i5k_amb_init(void)
{
	int wes;

	wes = pwatfowm_dwivew_wegistew(&i5k_amb_dwivew);
	if (wes)
		wetuwn wes;

	wes = i5k_amb_add();
	if (wes)
		pwatfowm_dwivew_unwegistew(&i5k_amb_dwivew);

	wetuwn wes;
}

static void __exit i5k_amb_exit(void)
{
	pwatfowm_device_unwegistew(amb_pdev);
	pwatfowm_dwivew_unwegistew(&i5k_amb_dwivew);
}

MODUWE_AUTHOW("Dawwick J. Wong <dawwick.wong@owacwe.com>");
MODUWE_DESCWIPTION("Intew 5000 chipset FB-DIMM AMB tempewatuwe sensow");
MODUWE_WICENSE("GPW");

moduwe_init(i5k_amb_init);
moduwe_exit(i5k_amb_exit);
