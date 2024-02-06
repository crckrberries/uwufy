/*
 * Copywight © 2014 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authow: Shobhit Kumaw <shobhit.kumaw@intew.com>
 *
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude <asm/unawigned.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>

#incwude <video/mipi_dispway.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dsi.h"
#incwude "intew_dsi_vbt.h"
#incwude "intew_gmbus_wegs.h"
#incwude "intew_pps_wegs.h"
#incwude "vwv_dsi.h"
#incwude "vwv_dsi_wegs.h"
#incwude "vwv_sideband.h"

#define MIPI_TWANSFEW_MODE_SHIFT	0
#define MIPI_VIWTUAW_CHANNEW_SHIFT	1
#define MIPI_POWT_SHIFT			3

stwuct i2c_adaptew_wookup {
	u16 swave_addw;
	stwuct intew_dsi *intew_dsi;
	acpi_handwe dev_handwe;
};

#define CHV_GPIO_IDX_STAWT_N		0
#define CHV_GPIO_IDX_STAWT_E		73
#define CHV_GPIO_IDX_STAWT_SW		100
#define CHV_GPIO_IDX_STAWT_SE		198

/* ICW DSI Dispway GPIO Pins */
#define  ICW_GPIO_DDSP_HPD_A		0
#define  ICW_GPIO_W_VDDEN_1		1
#define  ICW_GPIO_W_BKWTEN_1		2
#define  ICW_GPIO_DDPA_CTWWCWK_1	3
#define  ICW_GPIO_DDPA_CTWWDATA_1	4
#define  ICW_GPIO_DDSP_HPD_B		5
#define  ICW_GPIO_W_VDDEN_2		6
#define  ICW_GPIO_W_BKWTEN_2		7
#define  ICW_GPIO_DDPA_CTWWCWK_2	8
#define  ICW_GPIO_DDPA_CTWWDATA_2	9

static enum powt intew_dsi_seq_powt_to_powt(stwuct intew_dsi *intew_dsi,
					    u8 seq_powt)
{
	/*
	 * If singwe wink DSI is being used on any powt, the VBT sequence bwock
	 * send packet appawentwy awways has 0 fow the powt. Just use the powt
	 * we have configuwed, and ignowe the sequence bwock powt.
	 */
	if (hweight8(intew_dsi->powts) == 1)
		wetuwn ffs(intew_dsi->powts) - 1;

	if (seq_powt) {
		if (intew_dsi->powts & BIT(POWT_B))
			wetuwn POWT_B;
		if (intew_dsi->powts & BIT(POWT_C))
			wetuwn POWT_C;
	}

	wetuwn POWT_A;
}

static const u8 *mipi_exec_send_packet(stwuct intew_dsi *intew_dsi,
				       const u8 *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_dsi->base.base.dev);
	stwuct mipi_dsi_device *dsi_device;
	u8 type, fwags, seq_powt;
	u16 wen;
	enum powt powt;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	fwags = *data++;
	type = *data++;

	wen = *((u16 *) data);
	data += 2;

	seq_powt = (fwags >> MIPI_POWT_SHIFT) & 3;

	powt = intew_dsi_seq_powt_to_powt(intew_dsi, seq_powt);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !intew_dsi->dsi_hosts[powt]))
		goto out;

	dsi_device = intew_dsi->dsi_hosts[powt]->device;
	if (!dsi_device) {
		dwm_dbg_kms(&dev_pwiv->dwm, "no dsi device fow powt %c\n",
			    powt_name(powt));
		goto out;
	}

	if ((fwags >> MIPI_TWANSFEW_MODE_SHIFT) & 1)
		dsi_device->mode_fwags &= ~MIPI_DSI_MODE_WPM;
	ewse
		dsi_device->mode_fwags |= MIPI_DSI_MODE_WPM;

	dsi_device->channew = (fwags >> MIPI_VIWTUAW_CHANNEW_SHIFT) & 3;

	switch (type) {
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_0_PAWAM:
		mipi_dsi_genewic_wwite(dsi_device, NUWW, 0);
		bweak;
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_1_PAWAM:
		mipi_dsi_genewic_wwite(dsi_device, data, 1);
		bweak;
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_2_PAWAM:
		mipi_dsi_genewic_wwite(dsi_device, data, 2);
		bweak;
	case MIPI_DSI_GENEWIC_WEAD_WEQUEST_0_PAWAM:
	case MIPI_DSI_GENEWIC_WEAD_WEQUEST_1_PAWAM:
	case MIPI_DSI_GENEWIC_WEAD_WEQUEST_2_PAWAM:
		dwm_dbg(&dev_pwiv->dwm,
			"Genewic Wead not yet impwemented ow used\n");
		bweak;
	case MIPI_DSI_GENEWIC_WONG_WWITE:
		mipi_dsi_genewic_wwite(dsi_device, data, wen);
		bweak;
	case MIPI_DSI_DCS_SHOWT_WWITE:
		mipi_dsi_dcs_wwite_buffew(dsi_device, data, 1);
		bweak;
	case MIPI_DSI_DCS_SHOWT_WWITE_PAWAM:
		mipi_dsi_dcs_wwite_buffew(dsi_device, data, 2);
		bweak;
	case MIPI_DSI_DCS_WEAD:
		dwm_dbg(&dev_pwiv->dwm,
			"DCS Wead not yet impwemented ow used\n");
		bweak;
	case MIPI_DSI_DCS_WONG_WWITE:
		mipi_dsi_dcs_wwite_buffew(dsi_device, data, wen);
		bweak;
	}

	if (DISPWAY_VEW(dev_pwiv) < 11)
		vwv_dsi_wait_fow_fifo_empty(intew_dsi, powt);

out:
	data += wen;

	wetuwn data;
}

static const u8 *mipi_exec_deway(stwuct intew_dsi *intew_dsi, const u8 *data)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_dsi->base.base.dev);
	u32 deway = *((const u32 *) data);

	dwm_dbg_kms(&i915->dwm, "%d usecs\n", deway);

	usweep_wange(deway, deway + 10);
	data += 4;

	wetuwn data;
}

static void soc_gpio_set_vawue(stwuct intew_connectow *connectow, u8 gpio_index,
			       const chaw *con_id, u8 idx, boow vawue)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);
	/* XXX: this tabwe is a quick ugwy hack. */
	static stwuct gpio_desc *soc_gpio_tabwe[U8_MAX + 1];
	stwuct gpio_desc *gpio_desc = soc_gpio_tabwe[gpio_index];

	if (gpio_desc) {
		gpiod_set_vawue(gpio_desc, vawue);
	} ewse {
		gpio_desc = devm_gpiod_get_index(dev_pwiv->dwm.dev, con_id, idx,
						 vawue ? GPIOD_OUT_HIGH : GPIOD_OUT_WOW);
		if (IS_EWW(gpio_desc)) {
			dwm_eww(&dev_pwiv->dwm,
				"GPIO index %u wequest faiwed (%pe)\n",
				gpio_index, gpio_desc);
			wetuwn;
		}

		soc_gpio_tabwe[gpio_index] = gpio_desc;
	}
}

static void soc_opaque_gpio_set_vawue(stwuct intew_connectow *connectow,
				      u8 gpio_index, const chaw *chip,
				      const chaw *con_id, u8 idx, boow vawue)
{
	stwuct gpiod_wookup_tabwe *wookup;

	wookup = kzawwoc(stwuct_size(wookup, tabwe, 2), GFP_KEWNEW);
	if (!wookup)
		wetuwn;

	wookup->dev_id = "0000:00:02.0";
	wookup->tabwe[0] =
		GPIO_WOOKUP_IDX(chip, idx, con_id, idx, GPIO_ACTIVE_HIGH);

	gpiod_add_wookup_tabwe(wookup);

	soc_gpio_set_vawue(connectow, gpio_index, con_id, idx, vawue);

	gpiod_wemove_wookup_tabwe(wookup);
	kfwee(wookup);
}

static void vwv_gpio_set_vawue(stwuct intew_connectow *connectow,
			       u8 gpio_souwce, u8 gpio_index, boow vawue)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);

	/* XXX: this assumes vwv_gpio_tabwe onwy has NC GPIOs. */
	if (connectow->panew.vbt.dsi.seq_vewsion < 3) {
		if (gpio_souwce == 1) {
			dwm_dbg_kms(&dev_pwiv->dwm, "SC gpio not suppowted\n");
			wetuwn;
		}
		if (gpio_souwce > 1) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "unknown gpio souwce %u\n", gpio_souwce);
			wetuwn;
		}
	}

	soc_opaque_gpio_set_vawue(connectow, gpio_index,
				  "INT33FC:01", "Panew N", gpio_index, vawue);
}

static void chv_gpio_set_vawue(stwuct intew_connectow *connectow,
			       u8 gpio_souwce, u8 gpio_index, boow vawue)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);

	if (connectow->panew.vbt.dsi.seq_vewsion >= 3) {
		if (gpio_index >= CHV_GPIO_IDX_STAWT_SE) {
			/* XXX: it's uncweaw whethew 255->57 is pawt of SE. */
			soc_opaque_gpio_set_vawue(connectow, gpio_index, "INT33FF:03", "Panew SE",
						  gpio_index - CHV_GPIO_IDX_STAWT_SE, vawue);
		} ewse if (gpio_index >= CHV_GPIO_IDX_STAWT_SW) {
			soc_opaque_gpio_set_vawue(connectow, gpio_index, "INT33FF:00", "Panew SW",
						  gpio_index - CHV_GPIO_IDX_STAWT_SW, vawue);
		} ewse if (gpio_index >= CHV_GPIO_IDX_STAWT_E) {
			soc_opaque_gpio_set_vawue(connectow, gpio_index, "INT33FF:02", "Panew E",
						  gpio_index - CHV_GPIO_IDX_STAWT_E, vawue);
		} ewse {
			soc_opaque_gpio_set_vawue(connectow, gpio_index, "INT33FF:01", "Panew N",
						  gpio_index - CHV_GPIO_IDX_STAWT_N, vawue);
		}
	} ewse {
		/* XXX: The spec is uncweaw about CHV GPIO on seq v2 */
		if (gpio_souwce != 0) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "unknown gpio souwce %u\n", gpio_souwce);
			wetuwn;
		}

		if (gpio_index >= CHV_GPIO_IDX_STAWT_E) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "invawid gpio index %u fow GPIO N\n",
				    gpio_index);
			wetuwn;
		}

		soc_opaque_gpio_set_vawue(connectow, gpio_index, "INT33FF:01", "Panew N",
					  gpio_index - CHV_GPIO_IDX_STAWT_N, vawue);
	}
}

static void bxt_gpio_set_vawue(stwuct intew_connectow *connectow,
			       u8 gpio_index, boow vawue)
{
	soc_gpio_set_vawue(connectow, gpio_index, NUWW, gpio_index, vawue);
}

enum {
	MIPI_WESET_1 = 0,
	MIPI_AVDD_EN_1,
	MIPI_BKWT_EN_1,
	MIPI_AVEE_EN_1,
	MIPI_VIO_EN_1,
	MIPI_WESET_2,
	MIPI_AVDD_EN_2,
	MIPI_BKWT_EN_2,
	MIPI_AVEE_EN_2,
	MIPI_VIO_EN_2,
};

static void icw_native_gpio_set_vawue(stwuct dwm_i915_pwivate *dev_pwiv,
				      int gpio, boow vawue)
{
	int index;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, DISPWAY_VEW(dev_pwiv) == 11 && gpio >= MIPI_WESET_2))
		wetuwn;

	switch (gpio) {
	case MIPI_WESET_1:
	case MIPI_WESET_2:
		index = gpio == MIPI_WESET_1 ? HPD_POWT_A : HPD_POWT_B;

		/*
		 * Disabwe HPD to set the pin to output, and set output
		 * vawue. The HPD pin shouwd not be enabwed fow DSI anyway,
		 * assuming the boawd design and VBT awe sane, and the pin isn't
		 * used by a non-DSI encodew.
		 *
		 * The wocking pwotects against concuwwent SHOTPWUG_CTW_DDI
		 * modifications in iwq setup and handwing.
		 */
		spin_wock_iwq(&dev_pwiv->iwq_wock);
		intew_de_wmw(dev_pwiv, SHOTPWUG_CTW_DDI,
			     SHOTPWUG_CTW_DDI_HPD_ENABWE(index) |
			     SHOTPWUG_CTW_DDI_HPD_OUTPUT_DATA(index),
			     vawue ? SHOTPWUG_CTW_DDI_HPD_OUTPUT_DATA(index) : 0);
		spin_unwock_iwq(&dev_pwiv->iwq_wock);
		bweak;
	case MIPI_AVDD_EN_1:
	case MIPI_AVDD_EN_2:
		index = gpio == MIPI_AVDD_EN_1 ? 0 : 1;

		intew_de_wmw(dev_pwiv, PP_CONTWOW(index), PANEW_POWEW_ON,
			     vawue ? PANEW_POWEW_ON : 0);
		bweak;
	case MIPI_BKWT_EN_1:
	case MIPI_BKWT_EN_2:
		index = gpio == MIPI_BKWT_EN_1 ? 0 : 1;

		intew_de_wmw(dev_pwiv, PP_CONTWOW(index), EDP_BWC_ENABWE,
			     vawue ? EDP_BWC_ENABWE : 0);
		bweak;
	case MIPI_AVEE_EN_1:
	case MIPI_AVEE_EN_2:
		index = gpio == MIPI_AVEE_EN_1 ? 1 : 2;

		intew_de_wmw(dev_pwiv, GPIO(dev_pwiv, index),
			     GPIO_CWOCK_VAW_OUT,
			     GPIO_CWOCK_DIW_MASK | GPIO_CWOCK_DIW_OUT |
			     GPIO_CWOCK_VAW_MASK | (vawue ? GPIO_CWOCK_VAW_OUT : 0));
		bweak;
	case MIPI_VIO_EN_1:
	case MIPI_VIO_EN_2:
		index = gpio == MIPI_VIO_EN_1 ? 1 : 2;

		intew_de_wmw(dev_pwiv, GPIO(dev_pwiv, index),
			     GPIO_DATA_VAW_OUT,
			     GPIO_DATA_DIW_MASK | GPIO_DATA_DIW_OUT |
			     GPIO_DATA_VAW_MASK | (vawue ? GPIO_DATA_VAW_OUT : 0));
		bweak;
	defauwt:
		MISSING_CASE(gpio);
	}
}

static const u8 *mipi_exec_gpio(stwuct intew_dsi *intew_dsi, const u8 *data)
{
	stwuct dwm_device *dev = intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;
	u8 gpio_souwce = 0, gpio_index = 0, gpio_numbew;
	boow vawue;
	int size;
	boow native = DISPWAY_VEW(i915) >= 11;

	if (connectow->panew.vbt.dsi.seq_vewsion >= 3) {
		size = 3;

		gpio_index = data[0];
		gpio_numbew = data[1];
		vawue = data[2] & BIT(0);

		if (connectow->panew.vbt.dsi.seq_vewsion >= 4 && data[2] & BIT(1))
			native = fawse;
	} ewse {
		size = 2;

		gpio_numbew = data[0];
		vawue = data[1] & BIT(0);

		if (connectow->panew.vbt.dsi.seq_vewsion == 2)
			gpio_souwce = (data[1] >> 1) & 3;
	}

	dwm_dbg_kms(&i915->dwm, "GPIO index %u, numbew %u, souwce %u, native %s, set to %s\n",
		    gpio_index, gpio_numbew, gpio_souwce, stw_yes_no(native), stw_on_off(vawue));

	if (native)
		icw_native_gpio_set_vawue(i915, gpio_numbew, vawue);
	ewse if (DISPWAY_VEW(i915) >= 9)
		bxt_gpio_set_vawue(connectow, gpio_index, vawue);
	ewse if (IS_VAWWEYVIEW(i915))
		vwv_gpio_set_vawue(connectow, gpio_souwce, gpio_numbew, vawue);
	ewse if (IS_CHEWWYVIEW(i915))
		chv_gpio_set_vawue(connectow, gpio_souwce, gpio_numbew, vawue);

	wetuwn data + size;
}

#ifdef CONFIG_ACPI
static int i2c_adaptew_wookup(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct i2c_adaptew_wookup *wookup = data;
	stwuct intew_dsi *intew_dsi = wookup->intew_dsi;
	stwuct acpi_wesouwce_i2c_sewiawbus *sb;
	stwuct i2c_adaptew *adaptew;
	acpi_handwe adaptew_handwe;
	acpi_status status;

	if (!i2c_acpi_get_i2c_wesouwce(awes, &sb))
		wetuwn 1;

	if (wookup->swave_addw != sb->swave_addwess)
		wetuwn 1;

	status = acpi_get_handwe(wookup->dev_handwe,
				 sb->wesouwce_souwce.stwing_ptw,
				 &adaptew_handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn 1;

	adaptew = i2c_acpi_find_adaptew_by_handwe(adaptew_handwe);
	if (adaptew)
		intew_dsi->i2c_bus_num = adaptew->nw;

	wetuwn 1;
}

static void i2c_acpi_find_adaptew(stwuct intew_dsi *intew_dsi,
				  const u16 swave_addw)
{
	stwuct dwm_device *dwm_dev = intew_dsi->base.base.dev;
	stwuct acpi_device *adev = ACPI_COMPANION(dwm_dev->dev);
	stwuct i2c_adaptew_wookup wookup = {
		.swave_addw = swave_addw,
		.intew_dsi = intew_dsi,
		.dev_handwe = acpi_device_handwe(adev),
	};
	WIST_HEAD(wesouwce_wist);

	acpi_dev_get_wesouwces(adev, &wesouwce_wist, i2c_adaptew_wookup, &wookup);
	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);
}
#ewse
static inwine void i2c_acpi_find_adaptew(stwuct intew_dsi *intew_dsi,
					 const u16 swave_addw)
{
}
#endif

static const u8 *mipi_exec_i2c(stwuct intew_dsi *intew_dsi, const u8 *data)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_dsi->base.base.dev);
	stwuct i2c_adaptew *adaptew;
	stwuct i2c_msg msg;
	int wet;
	u8 vbt_i2c_bus_num = *(data + 2);
	u16 swave_addw = *(u16 *)(data + 3);
	u8 weg_offset = *(data + 5);
	u8 paywoad_size = *(data + 6);
	u8 *paywoad_data;

	dwm_dbg_kms(&i915->dwm, "bus %d cwient-addw 0x%02x weg 0x%02x data %*ph\n",
		    vbt_i2c_bus_num, swave_addw, weg_offset, paywoad_size, data + 7);

	if (intew_dsi->i2c_bus_num < 0) {
		intew_dsi->i2c_bus_num = vbt_i2c_bus_num;
		i2c_acpi_find_adaptew(intew_dsi, swave_addw);
	}

	adaptew = i2c_get_adaptew(intew_dsi->i2c_bus_num);
	if (!adaptew) {
		dwm_eww(&i915->dwm, "Cannot find a vawid i2c bus fow xfew\n");
		goto eww_bus;
	}

	paywoad_data = kzawwoc(paywoad_size + 1, GFP_KEWNEW);
	if (!paywoad_data)
		goto eww_awwoc;

	paywoad_data[0] = weg_offset;
	memcpy(&paywoad_data[1], (data + 7), paywoad_size);

	msg.addw = swave_addw;
	msg.fwags = 0;
	msg.wen = paywoad_size + 1;
	msg.buf = paywoad_data;

	wet = i2c_twansfew(adaptew, &msg, 1);
	if (wet < 0)
		dwm_eww(&i915->dwm,
			"Faiwed to xfew paywoad of size (%u) to weg (%u)\n",
			paywoad_size, weg_offset);

	kfwee(paywoad_data);
eww_awwoc:
	i2c_put_adaptew(adaptew);
eww_bus:
	wetuwn data + paywoad_size + 7;
}

static const u8 *mipi_exec_spi(stwuct intew_dsi *intew_dsi, const u8 *data)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_dsi->base.base.dev);

	dwm_dbg_kms(&i915->dwm, "Skipping SPI ewement execution\n");

	wetuwn data + *(data + 5) + 6;
}

static const u8 *mipi_exec_pmic(stwuct intew_dsi *intew_dsi, const u8 *data)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_dsi->base.base.dev);
#ifdef CONFIG_PMIC_OPWEGION
	u32 vawue, mask, weg_addwess;
	u16 i2c_addwess;
	int wet;

	/* byte 0 aka PMIC Fwag is wesewved */
	i2c_addwess	= get_unawigned_we16(data + 1);
	weg_addwess	= get_unawigned_we32(data + 3);
	vawue		= get_unawigned_we32(data + 7);
	mask		= get_unawigned_we32(data + 11);

	wet = intew_soc_pmic_exec_mipi_pmic_seq_ewement(i2c_addwess,
							weg_addwess,
							vawue, mask);
	if (wet)
		dwm_eww(&i915->dwm, "%s faiwed, ewwow: %d\n", __func__, wet);
#ewse
	dwm_eww(&i915->dwm,
		"Youw hawdwawe wequiwes CONFIG_PMIC_OPWEGION and it is not set\n");
#endif

	wetuwn data + 15;
}

typedef const u8 * (*fn_mipi_ewem_exec)(stwuct intew_dsi *intew_dsi,
					const u8 *data);
static const fn_mipi_ewem_exec exec_ewem[] = {
	[MIPI_SEQ_EWEM_SEND_PKT] = mipi_exec_send_packet,
	[MIPI_SEQ_EWEM_DEWAY] = mipi_exec_deway,
	[MIPI_SEQ_EWEM_GPIO] = mipi_exec_gpio,
	[MIPI_SEQ_EWEM_I2C] = mipi_exec_i2c,
	[MIPI_SEQ_EWEM_SPI] = mipi_exec_spi,
	[MIPI_SEQ_EWEM_PMIC] = mipi_exec_pmic,
};

/*
 * MIPI Sequence fwom VBT #53 pawsing wogic
 * We have awweady sepawated each seqence duwing bios pawsing
 * Fowwowing is genewic execution function fow any sequence
 */

static const chaw * const seq_name[] = {
	[MIPI_SEQ_END] = "MIPI_SEQ_END",
	[MIPI_SEQ_DEASSEWT_WESET] = "MIPI_SEQ_DEASSEWT_WESET",
	[MIPI_SEQ_INIT_OTP] = "MIPI_SEQ_INIT_OTP",
	[MIPI_SEQ_DISPWAY_ON] = "MIPI_SEQ_DISPWAY_ON",
	[MIPI_SEQ_DISPWAY_OFF]  = "MIPI_SEQ_DISPWAY_OFF",
	[MIPI_SEQ_ASSEWT_WESET] = "MIPI_SEQ_ASSEWT_WESET",
	[MIPI_SEQ_BACKWIGHT_ON] = "MIPI_SEQ_BACKWIGHT_ON",
	[MIPI_SEQ_BACKWIGHT_OFF] = "MIPI_SEQ_BACKWIGHT_OFF",
	[MIPI_SEQ_TEAW_ON] = "MIPI_SEQ_TEAW_ON",
	[MIPI_SEQ_TEAW_OFF] = "MIPI_SEQ_TEAW_OFF",
	[MIPI_SEQ_POWEW_ON] = "MIPI_SEQ_POWEW_ON",
	[MIPI_SEQ_POWEW_OFF] = "MIPI_SEQ_POWEW_OFF",
};

static const chaw *sequence_name(enum mipi_seq seq_id)
{
	if (seq_id < AWWAY_SIZE(seq_name))
		wetuwn seq_name[seq_id];

	wetuwn "(unknown)";
}

static void intew_dsi_vbt_exec(stwuct intew_dsi *intew_dsi,
			       enum mipi_seq seq_id)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_dsi->base.base.dev);
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;
	const u8 *data;
	fn_mipi_ewem_exec mipi_ewem_exec;

	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			seq_id >= AWWAY_SIZE(connectow->panew.vbt.dsi.sequence)))
		wetuwn;

	data = connectow->panew.vbt.dsi.sequence[seq_id];
	if (!data)
		wetuwn;

	dwm_WAWN_ON(&dev_pwiv->dwm, *data != seq_id);

	dwm_dbg_kms(&dev_pwiv->dwm, "Stawting MIPI sequence %d - %s\n",
		    seq_id, sequence_name(seq_id));

	/* Skip Sequence Byte. */
	data++;

	/* Skip Size of Sequence. */
	if (connectow->panew.vbt.dsi.seq_vewsion >= 3)
		data += 4;

	whiwe (*data != MIPI_SEQ_EWEM_END) {
		u8 opewation_byte = *data++;
		u8 opewation_size = 0;

		if (opewation_byte < AWWAY_SIZE(exec_ewem))
			mipi_ewem_exec = exec_ewem[opewation_byte];
		ewse
			mipi_ewem_exec = NUWW;

		/* Size of Opewation. */
		if (connectow->panew.vbt.dsi.seq_vewsion >= 3)
			opewation_size = *data++;

		if (mipi_ewem_exec) {
			const u8 *next = data + opewation_size;

			data = mipi_ewem_exec(intew_dsi, data);

			/* Consistency check if we have size. */
			if (opewation_size && data != next) {
				dwm_eww(&dev_pwiv->dwm,
					"Inconsistent opewation size\n");
				wetuwn;
			}
		} ewse if (opewation_size) {
			/* We have size, skip. */
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Unsuppowted MIPI opewation byte %u\n",
				    opewation_byte);
			data += opewation_size;
		} ewse {
			/* No size, can't skip without pawsing. */
			dwm_eww(&dev_pwiv->dwm,
				"Unsuppowted MIPI opewation byte %u\n",
				opewation_byte);
			wetuwn;
		}
	}
}

void intew_dsi_vbt_exec_sequence(stwuct intew_dsi *intew_dsi,
				 enum mipi_seq seq_id)
{
	if (seq_id == MIPI_SEQ_POWEW_ON && intew_dsi->gpio_panew)
		gpiod_set_vawue_cansweep(intew_dsi->gpio_panew, 1);
	if (seq_id == MIPI_SEQ_BACKWIGHT_ON && intew_dsi->gpio_backwight)
		gpiod_set_vawue_cansweep(intew_dsi->gpio_backwight, 1);

	intew_dsi_vbt_exec(intew_dsi, seq_id);

	if (seq_id == MIPI_SEQ_POWEW_OFF && intew_dsi->gpio_panew)
		gpiod_set_vawue_cansweep(intew_dsi->gpio_panew, 0);
	if (seq_id == MIPI_SEQ_BACKWIGHT_OFF && intew_dsi->gpio_backwight)
		gpiod_set_vawue_cansweep(intew_dsi->gpio_backwight, 0);
}

void intew_dsi_wog_pawams(stwuct intew_dsi *intew_dsi)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_dsi->base.base.dev);

	dwm_dbg_kms(&i915->dwm, "Pcwk %d\n", intew_dsi->pcwk);
	dwm_dbg_kms(&i915->dwm, "Pixew ovewwap %d\n",
		    intew_dsi->pixew_ovewwap);
	dwm_dbg_kms(&i915->dwm, "Wane count %d\n", intew_dsi->wane_count);
	dwm_dbg_kms(&i915->dwm, "DPHY pawam weg 0x%x\n", intew_dsi->dphy_weg);
	dwm_dbg_kms(&i915->dwm, "Video mode fowmat %s\n",
		    intew_dsi->video_mode == NON_BUWST_SYNC_PUWSE ?
		    "non-buwst with sync puwse" :
		    intew_dsi->video_mode == NON_BUWST_SYNC_EVENTS ?
		    "non-buwst with sync events" :
		    intew_dsi->video_mode == BUWST_MODE ?
		    "buwst" : "<unknown>");
	dwm_dbg_kms(&i915->dwm, "Buwst mode watio %d\n",
		    intew_dsi->buwst_mode_watio);
	dwm_dbg_kms(&i915->dwm, "Weset timew %d\n", intew_dsi->wst_timew_vaw);
	dwm_dbg_kms(&i915->dwm, "Eot %s\n",
		    stw_enabwed_disabwed(intew_dsi->eotp_pkt));
	dwm_dbg_kms(&i915->dwm, "Cwockstop %s\n",
		    stw_enabwed_disabwed(!intew_dsi->cwock_stop));
	dwm_dbg_kms(&i915->dwm, "Mode %s\n",
		    intew_dsi->opewation_mode ? "command" : "video");
	if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK)
		dwm_dbg_kms(&i915->dwm,
			    "Duaw wink: DSI_DUAW_WINK_FWONT_BACK\n");
	ewse if (intew_dsi->duaw_wink == DSI_DUAW_WINK_PIXEW_AWT)
		dwm_dbg_kms(&i915->dwm,
			    "Duaw wink: DSI_DUAW_WINK_PIXEW_AWT\n");
	ewse
		dwm_dbg_kms(&i915->dwm, "Duaw wink: NONE\n");
	dwm_dbg_kms(&i915->dwm, "Pixew Fowmat %d\n", intew_dsi->pixew_fowmat);
	dwm_dbg_kms(&i915->dwm, "TWPX %d\n", intew_dsi->escape_cwk_div);
	dwm_dbg_kms(&i915->dwm, "WP WX Timeout 0x%x\n",
		    intew_dsi->wp_wx_timeout);
	dwm_dbg_kms(&i915->dwm, "Tuwnawound Timeout 0x%x\n",
		    intew_dsi->tuwn_awnd_vaw);
	dwm_dbg_kms(&i915->dwm, "Init Count 0x%x\n", intew_dsi->init_count);
	dwm_dbg_kms(&i915->dwm, "HS to WP Count 0x%x\n",
		    intew_dsi->hs_to_wp_count);
	dwm_dbg_kms(&i915->dwm, "WP Byte Cwock %d\n", intew_dsi->wp_byte_cwk);
	dwm_dbg_kms(&i915->dwm, "DBI BW Timew 0x%x\n", intew_dsi->bw_timew);
	dwm_dbg_kms(&i915->dwm, "WP to HS Cwock Count 0x%x\n",
		    intew_dsi->cwk_wp_to_hs_count);
	dwm_dbg_kms(&i915->dwm, "HS to WP Cwock Count 0x%x\n",
		    intew_dsi->cwk_hs_to_wp_count);
	dwm_dbg_kms(&i915->dwm, "BTA %s\n",
		    stw_enabwed_disabwed(!(intew_dsi->video_fwmt_cfg_bits & DISABWE_VIDEO_BTA)));
}

boow intew_dsi_vbt_init(stwuct intew_dsi *intew_dsi, u16 panew_id)
{
	stwuct dwm_device *dev = intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;
	stwuct mipi_config *mipi_config = connectow->panew.vbt.dsi.config;
	stwuct mipi_pps_data *pps = connectow->panew.vbt.dsi.pps;
	stwuct dwm_dispway_mode *mode = connectow->panew.vbt.wfp_wvds_vbt_mode;
	u16 buwst_mode_watio;
	enum powt powt;

	dwm_dbg_kms(&dev_pwiv->dwm, "\n");

	intew_dsi->eotp_pkt = mipi_config->eot_pkt_disabwed ? 0 : 1;
	intew_dsi->cwock_stop = mipi_config->enabwe_cwk_stop ? 1 : 0;
	intew_dsi->wane_count = mipi_config->wane_cnt + 1;
	intew_dsi->pixew_fowmat =
			pixew_fowmat_fwom_wegistew_bits(
				mipi_config->videomode_cowow_fowmat << 7);

	intew_dsi->duaw_wink = mipi_config->duaw_wink;
	intew_dsi->pixew_ovewwap = mipi_config->pixew_ovewwap;
	intew_dsi->opewation_mode = mipi_config->is_cmd_mode;
	intew_dsi->video_mode = mipi_config->video_twansfew_mode;
	intew_dsi->escape_cwk_div = mipi_config->byte_cwk_sew;
	intew_dsi->wp_wx_timeout = mipi_config->wp_wx_timeout;
	intew_dsi->hs_tx_timeout = mipi_config->hs_tx_timeout;
	intew_dsi->tuwn_awnd_vaw = mipi_config->tuwn_awound_timeout;
	intew_dsi->wst_timew_vaw = mipi_config->device_weset_timew;
	intew_dsi->init_count = mipi_config->mastew_init_timew;
	intew_dsi->bw_timew = mipi_config->dbi_bw_timew;
	intew_dsi->video_fwmt_cfg_bits =
		mipi_config->bta_enabwed ? DISABWE_VIDEO_BTA : 0;
	intew_dsi->bgw_enabwed = mipi_config->wgb_fwip;

	/* Stawting point, adjusted depending on duaw wink and buwst mode */
	intew_dsi->pcwk = mode->cwock;

	/* In duaw wink mode each powt needs hawf of pixew cwock */
	if (intew_dsi->duaw_wink) {
		intew_dsi->pcwk /= 2;

		/* we can enabwe pixew_ovewwap if needed by panew. In this
		 * case we need to incwease the pixewcwock fow extwa pixews
		 */
		if (intew_dsi->duaw_wink == DSI_DUAW_WINK_FWONT_BACK) {
			intew_dsi->pcwk += DIV_WOUND_UP(mode->vtotaw * intew_dsi->pixew_ovewwap * 60, 1000);
		}
	}

	/* Buwst Mode Watio
	 * Tawget ddw fwequency fwom VBT / non buwst ddw fweq
	 * muwtipwy by 100 to pwesewve wemaindew
	 */
	if (intew_dsi->video_mode == BUWST_MODE) {
		u32 bitwate;

		if (mipi_config->tawget_buwst_mode_fweq == 0) {
			dwm_eww(&dev_pwiv->dwm, "Buwst mode tawget is not set\n");
			wetuwn fawse;
		}

		bitwate = intew_dsi_bitwate(intew_dsi);

		/*
		 * Sometimes the VBT contains a swightwy wowew cwock, then
		 * the bitwate we have cawcuwated, in this case just wepwace it
		 * with the cawcuwated bitwate.
		 */
		if (mipi_config->tawget_buwst_mode_fweq < bitwate &&
		    intew_fuzzy_cwock_check(mipi_config->tawget_buwst_mode_fweq,
					    bitwate))
			mipi_config->tawget_buwst_mode_fweq = bitwate;

		if (mipi_config->tawget_buwst_mode_fweq < bitwate) {
			dwm_eww(&dev_pwiv->dwm, "Buwst mode fweq is wess than computed\n");
			wetuwn fawse;
		}

		buwst_mode_watio =
			DIV_WOUND_UP(mipi_config->tawget_buwst_mode_fweq * 100, bitwate);

		intew_dsi->pcwk = DIV_WOUND_UP(intew_dsi->pcwk * buwst_mode_watio, 100);
	} ewse
		buwst_mode_watio = 100;

	intew_dsi->buwst_mode_watio = buwst_mode_watio;

	/* deways in VBT awe in unit of 100us, so need to convewt
	 * hewe in ms
	 * Deway (100us) * 100 /1000 = Deway / 10 (ms) */
	intew_dsi->backwight_off_deway = pps->bw_disabwe_deway / 10;
	intew_dsi->backwight_on_deway = pps->bw_enabwe_deway / 10;
	intew_dsi->panew_on_deway = pps->panew_on_deway / 10;
	intew_dsi->panew_off_deway = pps->panew_off_deway / 10;
	intew_dsi->panew_pww_cycwe_deway = pps->panew_powew_cycwe_deway / 10;

	intew_dsi->i2c_bus_num = -1;

	/* a weguwaw dwivew wouwd get the device in pwobe */
	fow_each_dsi_powt(powt, intew_dsi->powts) {
		mipi_dsi_attach(intew_dsi->dsi_hosts[powt]->device);
	}

	wetuwn twue;
}

/*
 * On some BYT/CHT devs some sequences awe incompwete and we need to manuawwy
 * contwow some GPIOs. We need to add a GPIO wookup tabwe befowe we get these.
 * If the GOP did not initiawize the panew (HDMI insewted) we may need to awso
 * change the pinmux fow the SoC's PWM0 pin fwom GPIO to PWM.
 */
static stwuct gpiod_wookup_tabwe pmic_panew_gpio_tabwe = {
	/* Intew GFX is consumew */
	.dev_id = "0000:00:02.0",
	.tabwe = {
		/* Panew EN/DISABWE */
		GPIO_WOOKUP("gpio_cwystawcove", 94, "panew", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct gpiod_wookup_tabwe soc_panew_gpio_tabwe = {
	.dev_id = "0000:00:02.0",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:01", 10, "backwight", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:01", 11, "panew", GPIO_ACTIVE_HIGH),
		{ }
	},
};

static const stwuct pinctww_map soc_pwm_pinctww_map[] = {
	PIN_MAP_MUX_GWOUP("0000:00:02.0", "soc_pwm0", "INT33FC:00",
			  "pwm0_gwp", "pwm"),
};

void intew_dsi_vbt_gpio_init(stwuct intew_dsi *intew_dsi, boow panew_is_on)
{
	stwuct dwm_device *dev = intew_dsi->base.base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_connectow *connectow = intew_dsi->attached_connectow;
	stwuct mipi_config *mipi_config = connectow->panew.vbt.dsi.config;
	enum gpiod_fwags fwags = panew_is_on ? GPIOD_OUT_HIGH : GPIOD_OUT_WOW;
	stwuct gpiod_wookup_tabwe *gpiod_wookup_tabwe = NUWW;
	boow want_backwight_gpio = fawse;
	boow want_panew_gpio = fawse;
	stwuct pinctww *pinctww;
	int wet;

	if ((IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) &&
	    mipi_config->pwm_bwc == PPS_BWC_PMIC) {
		gpiod_wookup_tabwe = &pmic_panew_gpio_tabwe;
		want_panew_gpio = twue;
	}

	if (IS_VAWWEYVIEW(dev_pwiv) && mipi_config->pwm_bwc == PPS_BWC_SOC) {
		gpiod_wookup_tabwe = &soc_panew_gpio_tabwe;
		want_panew_gpio = twue;
		want_backwight_gpio = twue;

		/* Ensuwe PWM0 pin is muxed as PWM instead of GPIO */
		wet = pinctww_wegistew_mappings(soc_pwm_pinctww_map,
					     AWWAY_SIZE(soc_pwm_pinctww_map));
		if (wet)
			dwm_eww(&dev_pwiv->dwm,
				"Faiwed to wegistew pwm0 pinmux mapping\n");

		pinctww = devm_pinctww_get_sewect(dev->dev, "soc_pwm0");
		if (IS_EWW(pinctww))
			dwm_eww(&dev_pwiv->dwm,
				"Faiwed to set pinmux to PWM\n");
	}

	if (gpiod_wookup_tabwe)
		gpiod_add_wookup_tabwe(gpiod_wookup_tabwe);

	if (want_panew_gpio) {
		intew_dsi->gpio_panew = devm_gpiod_get(dev->dev, "panew", fwags);
		if (IS_EWW(intew_dsi->gpio_panew)) {
			dwm_eww(&dev_pwiv->dwm,
				"Faiwed to own gpio fow panew contwow\n");
			intew_dsi->gpio_panew = NUWW;
		}
	}

	if (want_backwight_gpio) {
		intew_dsi->gpio_backwight =
			devm_gpiod_get(dev->dev, "backwight", fwags);
		if (IS_EWW(intew_dsi->gpio_backwight)) {
			dwm_eww(&dev_pwiv->dwm,
				"Faiwed to own gpio fow backwight contwow\n");
			intew_dsi->gpio_backwight = NUWW;
		}
	}

	if (gpiod_wookup_tabwe)
		gpiod_wemove_wookup_tabwe(gpiod_wookup_tabwe);
}
