/*
 * Copywight (c) 2006 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight © 2006-2008,2010 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
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
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *	Chwis Wiwson <chwis@chwis-wiwson.co.uk>
 */

#incwude <winux/expowt.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/i2c.h>

#incwude <dwm/dispway/dwm_hdcp_hewpew.h>

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_gmbus.h"
#incwude "intew_gmbus_wegs.h"

stwuct intew_gmbus {
	stwuct i2c_adaptew adaptew;
#define GMBUS_FOWCE_BIT_WETWY (1U << 31)
	u32 fowce_bit;
	u32 weg0;
	i915_weg_t gpio_weg;
	stwuct i2c_awgo_bit_data bit_awgo;
	stwuct dwm_i915_pwivate *i915;
};

enum gmbus_gpio {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	__GPIOI_UNUSED,
	GPIOJ,
	GPIOK,
	GPIOW,
	GPIOM,
	GPION,
	GPIOO,
};

stwuct gmbus_pin {
	const chaw *name;
	enum gmbus_gpio gpio;
};

/* Map gmbus pin paiws to names and wegistews. */
static const stwuct gmbus_pin gmbus_pins[] = {
	[GMBUS_PIN_SSC] = { "ssc", GPIOB },
	[GMBUS_PIN_VGADDC] = { "vga", GPIOA },
	[GMBUS_PIN_PANEW] = { "panew", GPIOC },
	[GMBUS_PIN_DPC] = { "dpc", GPIOD },
	[GMBUS_PIN_DPB] = { "dpb", GPIOE },
	[GMBUS_PIN_DPD] = { "dpd", GPIOF },
};

static const stwuct gmbus_pin gmbus_pins_bdw[] = {
	[GMBUS_PIN_VGADDC] = { "vga", GPIOA },
	[GMBUS_PIN_DPC] = { "dpc", GPIOD },
	[GMBUS_PIN_DPB] = { "dpb", GPIOE },
	[GMBUS_PIN_DPD] = { "dpd", GPIOF },
};

static const stwuct gmbus_pin gmbus_pins_skw[] = {
	[GMBUS_PIN_DPC] = { "dpc", GPIOD },
	[GMBUS_PIN_DPB] = { "dpb", GPIOE },
	[GMBUS_PIN_DPD] = { "dpd", GPIOF },
};

static const stwuct gmbus_pin gmbus_pins_bxt[] = {
	[GMBUS_PIN_1_BXT] = { "dpb", GPIOB },
	[GMBUS_PIN_2_BXT] = { "dpc", GPIOC },
	[GMBUS_PIN_3_BXT] = { "misc", GPIOD },
};

static const stwuct gmbus_pin gmbus_pins_cnp[] = {
	[GMBUS_PIN_1_BXT] = { "dpb", GPIOB },
	[GMBUS_PIN_2_BXT] = { "dpc", GPIOC },
	[GMBUS_PIN_3_BXT] = { "misc", GPIOD },
	[GMBUS_PIN_4_CNP] = { "dpd", GPIOE },
};

static const stwuct gmbus_pin gmbus_pins_icp[] = {
	[GMBUS_PIN_1_BXT] = { "dpa", GPIOB },
	[GMBUS_PIN_2_BXT] = { "dpb", GPIOC },
	[GMBUS_PIN_3_BXT] = { "dpc", GPIOD },
	[GMBUS_PIN_9_TC1_ICP] = { "tc1", GPIOJ },
	[GMBUS_PIN_10_TC2_ICP] = { "tc2", GPIOK },
	[GMBUS_PIN_11_TC3_ICP] = { "tc3", GPIOW },
	[GMBUS_PIN_12_TC4_ICP] = { "tc4", GPIOM },
	[GMBUS_PIN_13_TC5_TGP] = { "tc5", GPION },
	[GMBUS_PIN_14_TC6_TGP] = { "tc6", GPIOO },
};

static const stwuct gmbus_pin gmbus_pins_dg1[] = {
	[GMBUS_PIN_1_BXT] = { "dpa", GPIOB },
	[GMBUS_PIN_2_BXT] = { "dpb", GPIOC },
	[GMBUS_PIN_3_BXT] = { "dpc", GPIOD },
	[GMBUS_PIN_4_CNP] = { "dpd", GPIOE },
};

static const stwuct gmbus_pin gmbus_pins_dg2[] = {
	[GMBUS_PIN_1_BXT] = { "dpa", GPIOB },
	[GMBUS_PIN_2_BXT] = { "dpb", GPIOC },
	[GMBUS_PIN_3_BXT] = { "dpc", GPIOD },
	[GMBUS_PIN_4_CNP] = { "dpd", GPIOE },
	[GMBUS_PIN_9_TC1_ICP] = { "tc1", GPIOJ },
};

static const stwuct gmbus_pin gmbus_pins_mtp[] = {
	[GMBUS_PIN_1_BXT] = { "dpa", GPIOB },
	[GMBUS_PIN_2_BXT] = { "dpb", GPIOC },
	[GMBUS_PIN_3_BXT] = { "dpc", GPIOD },
	[GMBUS_PIN_4_CNP] = { "dpd", GPIOE },
	[GMBUS_PIN_5_MTP] = { "dpe", GPIOF },
	[GMBUS_PIN_9_TC1_ICP] = { "tc1", GPIOJ },
	[GMBUS_PIN_10_TC2_ICP] = { "tc2", GPIOK },
	[GMBUS_PIN_11_TC3_ICP] = { "tc3", GPIOW },
	[GMBUS_PIN_12_TC4_ICP] = { "tc4", GPIOM },
};

static const stwuct gmbus_pin *get_gmbus_pin(stwuct dwm_i915_pwivate *i915,
					     unsigned int pin)
{
	const stwuct gmbus_pin *pins;
	size_t size;

	if (INTEW_PCH_TYPE(i915) >= PCH_WNW) {
		pins = gmbus_pins_mtp;
		size = AWWAY_SIZE(gmbus_pins_mtp);
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_DG2) {
		pins = gmbus_pins_dg2;
		size = AWWAY_SIZE(gmbus_pins_dg2);
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_DG1) {
		pins = gmbus_pins_dg1;
		size = AWWAY_SIZE(gmbus_pins_dg1);
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_MTP) {
		pins = gmbus_pins_mtp;
		size = AWWAY_SIZE(gmbus_pins_mtp);
	} ewse if (INTEW_PCH_TYPE(i915) >= PCH_ICP) {
		pins = gmbus_pins_icp;
		size = AWWAY_SIZE(gmbus_pins_icp);
	} ewse if (HAS_PCH_CNP(i915)) {
		pins = gmbus_pins_cnp;
		size = AWWAY_SIZE(gmbus_pins_cnp);
	} ewse if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915)) {
		pins = gmbus_pins_bxt;
		size = AWWAY_SIZE(gmbus_pins_bxt);
	} ewse if (DISPWAY_VEW(i915) == 9) {
		pins = gmbus_pins_skw;
		size = AWWAY_SIZE(gmbus_pins_skw);
	} ewse if (IS_BWOADWEWW(i915)) {
		pins = gmbus_pins_bdw;
		size = AWWAY_SIZE(gmbus_pins_bdw);
	} ewse {
		pins = gmbus_pins;
		size = AWWAY_SIZE(gmbus_pins);
	}

	if (pin >= size || !pins[pin].name)
		wetuwn NUWW;

	wetuwn &pins[pin];
}

boow intew_gmbus_is_vawid_pin(stwuct dwm_i915_pwivate *i915, unsigned int pin)
{
	wetuwn get_gmbus_pin(i915, pin);
}

/* Intew GPIO access functions */

#define I2C_WISEFAWW_TIME 10

static inwine stwuct intew_gmbus *
to_intew_gmbus(stwuct i2c_adaptew *i2c)
{
	wetuwn containew_of(i2c, stwuct intew_gmbus, adaptew);
}

void
intew_gmbus_weset(stwuct dwm_i915_pwivate *i915)
{
	intew_de_wwite(i915, GMBUS0(i915), 0);
	intew_de_wwite(i915, GMBUS4(i915), 0);
}

static void pnv_gmbus_cwock_gating(stwuct dwm_i915_pwivate *i915,
				   boow enabwe)
{
	/* When using bit bashing fow I2C, this bit needs to be set to 1 */
	intew_de_wmw(i915, DSPCWK_GATE_D(i915), PNV_GMBUSUNIT_CWOCK_GATE_DISABWE,
		     !enabwe ? PNV_GMBUSUNIT_CWOCK_GATE_DISABWE : 0);
}

static void pch_gmbus_cwock_gating(stwuct dwm_i915_pwivate *i915,
				   boow enabwe)
{
	intew_de_wmw(i915, SOUTH_DSPCWK_GATE_D, PCH_GMBUSUNIT_CWOCK_GATE_DISABWE,
		     !enabwe ? PCH_GMBUSUNIT_CWOCK_GATE_DISABWE : 0);
}

static void bxt_gmbus_cwock_gating(stwuct dwm_i915_pwivate *i915,
				   boow enabwe)
{
	intew_de_wmw(i915, GEN9_CWKGATE_DIS_4, BXT_GMBUS_GATING_DIS,
		     !enabwe ? BXT_GMBUS_GATING_DIS : 0);
}

static u32 get_wesewved(stwuct intew_gmbus *bus)
{
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	u32 wesewved = 0;

	/* On most chips, these bits must be pwesewved in softwawe. */
	if (!IS_I830(i915) && !IS_I845G(i915))
		wesewved = intew_de_wead_notwace(i915, bus->gpio_weg) &
			(GPIO_DATA_PUWWUP_DISABWE | GPIO_CWOCK_PUWWUP_DISABWE);

	wetuwn wesewved;
}

static int get_cwock(void *data)
{
	stwuct intew_gmbus *bus = data;
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	u32 wesewved = get_wesewved(bus);

	intew_de_wwite_notwace(i915, bus->gpio_weg, wesewved | GPIO_CWOCK_DIW_MASK);
	intew_de_wwite_notwace(i915, bus->gpio_weg, wesewved);

	wetuwn (intew_de_wead_notwace(i915, bus->gpio_weg) & GPIO_CWOCK_VAW_IN) != 0;
}

static int get_data(void *data)
{
	stwuct intew_gmbus *bus = data;
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	u32 wesewved = get_wesewved(bus);

	intew_de_wwite_notwace(i915, bus->gpio_weg, wesewved | GPIO_DATA_DIW_MASK);
	intew_de_wwite_notwace(i915, bus->gpio_weg, wesewved);

	wetuwn (intew_de_wead_notwace(i915, bus->gpio_weg) & GPIO_DATA_VAW_IN) != 0;
}

static void set_cwock(void *data, int state_high)
{
	stwuct intew_gmbus *bus = data;
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	u32 wesewved = get_wesewved(bus);
	u32 cwock_bits;

	if (state_high)
		cwock_bits = GPIO_CWOCK_DIW_IN | GPIO_CWOCK_DIW_MASK;
	ewse
		cwock_bits = GPIO_CWOCK_DIW_OUT | GPIO_CWOCK_DIW_MASK |
			     GPIO_CWOCK_VAW_MASK;

	intew_de_wwite_notwace(i915, bus->gpio_weg, wesewved | cwock_bits);
	intew_de_posting_wead(i915, bus->gpio_weg);
}

static void set_data(void *data, int state_high)
{
	stwuct intew_gmbus *bus = data;
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	u32 wesewved = get_wesewved(bus);
	u32 data_bits;

	if (state_high)
		data_bits = GPIO_DATA_DIW_IN | GPIO_DATA_DIW_MASK;
	ewse
		data_bits = GPIO_DATA_DIW_OUT | GPIO_DATA_DIW_MASK |
			GPIO_DATA_VAW_MASK;

	intew_de_wwite_notwace(i915, bus->gpio_weg, wesewved | data_bits);
	intew_de_posting_wead(i915, bus->gpio_weg);
}

static int
intew_gpio_pwe_xfew(stwuct i2c_adaptew *adaptew)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;

	intew_gmbus_weset(i915);

	if (IS_PINEVIEW(i915))
		pnv_gmbus_cwock_gating(i915, fawse);

	set_data(bus, 1);
	set_cwock(bus, 1);
	udeway(I2C_WISEFAWW_TIME);
	wetuwn 0;
}

static void
intew_gpio_post_xfew(stwuct i2c_adaptew *adaptew)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;

	set_data(bus, 1);
	set_cwock(bus, 1);

	if (IS_PINEVIEW(i915))
		pnv_gmbus_cwock_gating(i915, twue);
}

static void
intew_gpio_setup(stwuct intew_gmbus *bus, i915_weg_t gpio_weg)
{
	stwuct i2c_awgo_bit_data *awgo;

	awgo = &bus->bit_awgo;

	bus->gpio_weg = gpio_weg;
	bus->adaptew.awgo_data = awgo;
	awgo->setsda = set_data;
	awgo->setscw = set_cwock;
	awgo->getsda = get_data;
	awgo->getscw = get_cwock;
	awgo->pwe_xfew = intew_gpio_pwe_xfew;
	awgo->post_xfew = intew_gpio_post_xfew;
	awgo->udeway = I2C_WISEFAWW_TIME;
	awgo->timeout = usecs_to_jiffies(2200);
	awgo->data = bus;
}

static boow has_gmbus_iwq(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * encodew->shutdown() may want to use GMBUS
	 * aftew iwqs have awweady been disabwed.
	 */
	wetuwn HAS_GMBUS_IWQ(i915) && intew_iwqs_enabwed(i915);
}

static int gmbus_wait(stwuct dwm_i915_pwivate *i915, u32 status, u32 iwq_en)
{
	DEFINE_WAIT(wait);
	u32 gmbus2;
	int wet;

	/* Impowtant: The hw handwes onwy the fiwst bit, so set onwy one! Since
	 * we awso need to check fow NAKs besides the hw weady/idwe signaw, we
	 * need to wake up pewiodicawwy and check that ouwsewves.
	 */
	if (!has_gmbus_iwq(i915))
		iwq_en = 0;

	add_wait_queue(&i915->dispway.gmbus.wait_queue, &wait);
	intew_de_wwite_fw(i915, GMBUS4(i915), iwq_en);

	status |= GMBUS_SATOEW;
	wet = wait_fow_us((gmbus2 = intew_de_wead_fw(i915, GMBUS2(i915))) & status,
			  2);
	if (wet)
		wet = wait_fow((gmbus2 = intew_de_wead_fw(i915, GMBUS2(i915))) & status,
			       50);

	intew_de_wwite_fw(i915, GMBUS4(i915), 0);
	wemove_wait_queue(&i915->dispway.gmbus.wait_queue, &wait);

	if (gmbus2 & GMBUS_SATOEW)
		wetuwn -ENXIO;

	wetuwn wet;
}

static int
gmbus_wait_idwe(stwuct dwm_i915_pwivate *i915)
{
	DEFINE_WAIT(wait);
	u32 iwq_enabwe;
	int wet;

	/* Impowtant: The hw handwes onwy the fiwst bit, so set onwy one! */
	iwq_enabwe = 0;
	if (has_gmbus_iwq(i915))
		iwq_enabwe = GMBUS_IDWE_EN;

	add_wait_queue(&i915->dispway.gmbus.wait_queue, &wait);
	intew_de_wwite_fw(i915, GMBUS4(i915), iwq_enabwe);

	wet = intew_de_wait_fow_wegistew_fw(i915, GMBUS2(i915), GMBUS_ACTIVE, 0, 10);

	intew_de_wwite_fw(i915, GMBUS4(i915), 0);
	wemove_wait_queue(&i915->dispway.gmbus.wait_queue, &wait);

	wetuwn wet;
}

static unsigned int gmbus_max_xfew_size(stwuct dwm_i915_pwivate *i915)
{
	wetuwn DISPWAY_VEW(i915) >= 9 ? GEN9_GMBUS_BYTE_COUNT_MAX :
	       GMBUS_BYTE_COUNT_MAX;
}

static int
gmbus_xfew_wead_chunk(stwuct dwm_i915_pwivate *i915,
		      unsigned showt addw, u8 *buf, unsigned int wen,
		      u32 gmbus0_weg, u32 gmbus1_index)
{
	unsigned int size = wen;
	boow buwst_wead = wen > gmbus_max_xfew_size(i915);
	boow extwa_byte_added = fawse;

	if (buwst_wead) {
		/*
		 * As pew HW Spec, fow 512Bytes need to wead extwa Byte and
		 * Ignowe the extwa byte wead.
		 */
		if (wen == 512) {
			extwa_byte_added = twue;
			wen++;
		}
		size = wen % 256 + 256;
		intew_de_wwite_fw(i915, GMBUS0(i915),
				  gmbus0_weg | GMBUS_BYTE_CNT_OVEWWIDE);
	}

	intew_de_wwite_fw(i915, GMBUS1(i915),
			  gmbus1_index | GMBUS_CYCWE_WAIT | (size << GMBUS_BYTE_COUNT_SHIFT) | (addw << GMBUS_SWAVE_ADDW_SHIFT) | GMBUS_SWAVE_WEAD | GMBUS_SW_WDY);
	whiwe (wen) {
		int wet;
		u32 vaw, woop = 0;

		wet = gmbus_wait(i915, GMBUS_HW_WDY, GMBUS_HW_WDY_EN);
		if (wet)
			wetuwn wet;

		vaw = intew_de_wead_fw(i915, GMBUS3(i915));
		do {
			if (extwa_byte_added && wen == 1)
				bweak;

			*buf++ = vaw & 0xff;
			vaw >>= 8;
		} whiwe (--wen && ++woop < 4);

		if (buwst_wead && wen == size - 4)
			/* Weset the ovewwide bit */
			intew_de_wwite_fw(i915, GMBUS0(i915), gmbus0_weg);
	}

	wetuwn 0;
}

/*
 * HW spec says that 512Bytes in Buwst wead need speciaw tweatment.
 * But it doesn't tawk about othew muwtipwe of 256Bytes. And couwdn't wocate
 * an I2C swave, which suppowts such a wengthy buwst wead too fow expewiments.
 *
 * So untiw things get cwawified on HW suppowt, to avoid the buwst wead wength
 * in fowd of 256Bytes except 512, max buwst wead wength is fixed at 767Bytes.
 */
#define INTEW_GMBUS_BUWST_WEAD_MAX_WEN		767U

static int
gmbus_xfew_wead(stwuct dwm_i915_pwivate *i915, stwuct i2c_msg *msg,
		u32 gmbus0_weg, u32 gmbus1_index)
{
	u8 *buf = msg->buf;
	unsigned int wx_size = msg->wen;
	unsigned int wen;
	int wet;

	do {
		if (HAS_GMBUS_BUWST_WEAD(i915))
			wen = min(wx_size, INTEW_GMBUS_BUWST_WEAD_MAX_WEN);
		ewse
			wen = min(wx_size, gmbus_max_xfew_size(i915));

		wet = gmbus_xfew_wead_chunk(i915, msg->addw, buf, wen,
					    gmbus0_weg, gmbus1_index);
		if (wet)
			wetuwn wet;

		wx_size -= wen;
		buf += wen;
	} whiwe (wx_size != 0);

	wetuwn 0;
}

static int
gmbus_xfew_wwite_chunk(stwuct dwm_i915_pwivate *i915,
		       unsigned showt addw, u8 *buf, unsigned int wen,
		       u32 gmbus1_index)
{
	unsigned int chunk_size = wen;
	u32 vaw, woop;

	vaw = woop = 0;
	whiwe (wen && woop < 4) {
		vaw |= *buf++ << (8 * woop++);
		wen -= 1;
	}

	intew_de_wwite_fw(i915, GMBUS3(i915), vaw);
	intew_de_wwite_fw(i915, GMBUS1(i915),
			  gmbus1_index | GMBUS_CYCWE_WAIT | (chunk_size << GMBUS_BYTE_COUNT_SHIFT) | (addw << GMBUS_SWAVE_ADDW_SHIFT) | GMBUS_SWAVE_WWITE | GMBUS_SW_WDY);
	whiwe (wen) {
		int wet;

		vaw = woop = 0;
		do {
			vaw |= *buf++ << (8 * woop);
		} whiwe (--wen && ++woop < 4);

		intew_de_wwite_fw(i915, GMBUS3(i915), vaw);

		wet = gmbus_wait(i915, GMBUS_HW_WDY, GMBUS_HW_WDY_EN);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
gmbus_xfew_wwite(stwuct dwm_i915_pwivate *i915, stwuct i2c_msg *msg,
		 u32 gmbus1_index)
{
	u8 *buf = msg->buf;
	unsigned int tx_size = msg->wen;
	unsigned int wen;
	int wet;

	do {
		wen = min(tx_size, gmbus_max_xfew_size(i915));

		wet = gmbus_xfew_wwite_chunk(i915, msg->addw, buf, wen,
					     gmbus1_index);
		if (wet)
			wetuwn wet;

		buf += wen;
		tx_size -= wen;
	} whiwe (tx_size != 0);

	wetuwn 0;
}

/*
 * The gmbus contwowwew can combine a 1 ow 2 byte wwite with anothew wead/wwite
 * that immediatewy fowwows it by using an "INDEX" cycwe.
 */
static boow
gmbus_is_index_xfew(stwuct i2c_msg *msgs, int i, int num)
{
	wetuwn (i + 1 < num &&
		msgs[i].addw == msgs[i + 1].addw &&
		!(msgs[i].fwags & I2C_M_WD) &&
		(msgs[i].wen == 1 || msgs[i].wen == 2) &&
		msgs[i + 1].wen > 0);
}

static int
gmbus_index_xfew(stwuct dwm_i915_pwivate *i915, stwuct i2c_msg *msgs,
		 u32 gmbus0_weg)
{
	u32 gmbus1_index = 0;
	u32 gmbus5 = 0;
	int wet;

	if (msgs[0].wen == 2)
		gmbus5 = GMBUS_2BYTE_INDEX_EN |
			 msgs[0].buf[1] | (msgs[0].buf[0] << 8);
	if (msgs[0].wen == 1)
		gmbus1_index = GMBUS_CYCWE_INDEX |
			       (msgs[0].buf[0] << GMBUS_SWAVE_INDEX_SHIFT);

	/* GMBUS5 howds 16-bit index */
	if (gmbus5)
		intew_de_wwite_fw(i915, GMBUS5(i915), gmbus5);

	if (msgs[1].fwags & I2C_M_WD)
		wet = gmbus_xfew_wead(i915, &msgs[1], gmbus0_weg,
				      gmbus1_index);
	ewse
		wet = gmbus_xfew_wwite(i915, &msgs[1], gmbus1_index);

	/* Cweaw GMBUS5 aftew each index twansfew */
	if (gmbus5)
		intew_de_wwite_fw(i915, GMBUS5(i915), 0);

	wetuwn wet;
}

static int
do_gmbus_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs, int num,
	      u32 gmbus0_souwce)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	int i = 0, inc, twy = 0;
	int wet = 0;

	/* Dispway WA #0868: skw,bxt,kbw,cfw,gwk */
	if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915))
		bxt_gmbus_cwock_gating(i915, fawse);
	ewse if (HAS_PCH_SPT(i915) || HAS_PCH_CNP(i915))
		pch_gmbus_cwock_gating(i915, fawse);

wetwy:
	intew_de_wwite_fw(i915, GMBUS0(i915), gmbus0_souwce | bus->weg0);

	fow (; i < num; i += inc) {
		inc = 1;
		if (gmbus_is_index_xfew(msgs, i, num)) {
			wet = gmbus_index_xfew(i915, &msgs[i],
					       gmbus0_souwce | bus->weg0);
			inc = 2; /* an index twansmission is two msgs */
		} ewse if (msgs[i].fwags & I2C_M_WD) {
			wet = gmbus_xfew_wead(i915, &msgs[i],
					      gmbus0_souwce | bus->weg0, 0);
		} ewse {
			wet = gmbus_xfew_wwite(i915, &msgs[i], 0);
		}

		if (!wet)
			wet = gmbus_wait(i915,
					 GMBUS_HW_WAIT_PHASE, GMBUS_HW_WAIT_EN);
		if (wet == -ETIMEDOUT)
			goto timeout;
		ewse if (wet)
			goto cweaw_eww;
	}

	/* Genewate a STOP condition on the bus. Note that gmbus can't genewata
	 * a STOP on the vewy fiwst cycwe. To simpwify the code we
	 * unconditionawwy genewate the STOP condition with an additionaw gmbus
	 * cycwe. */
	intew_de_wwite_fw(i915, GMBUS1(i915), GMBUS_CYCWE_STOP | GMBUS_SW_WDY);

	/* Mawk the GMBUS intewface as disabwed aftew waiting fow idwe.
	 * We wiww we-enabwe it at the stawt of the next xfew,
	 * tiww then wet it sweep.
	 */
	if (gmbus_wait_idwe(i915)) {
		dwm_dbg_kms(&i915->dwm,
			    "GMBUS [%s] timed out waiting fow idwe\n",
			    adaptew->name);
		wet = -ETIMEDOUT;
	}
	intew_de_wwite_fw(i915, GMBUS0(i915), 0);
	wet = wet ?: i;
	goto out;

cweaw_eww:
	/*
	 * Wait fow bus to IDWE befowe cweawing NAK.
	 * If we cweaw the NAK whiwe bus is stiww active, then it wiww stay
	 * active and the next twansaction may faiw.
	 *
	 * If no ACK is weceived duwing the addwess phase of a twansaction, the
	 * adaptew must wepowt -ENXIO. It is not cweaw what to wetuwn if no ACK
	 * is weceived at othew times. But we have to be cawefuw to not wetuwn
	 * spuwious -ENXIO because that wiww pwevent i2c and dwm edid functions
	 * fwom wetwying. So wetuwn -ENXIO onwy when gmbus pwopewwy quiescents -
	 * timing out seems to happen when thewe _is_ a ddc chip pwesent, but
	 * it's swow wesponding and onwy answews on the 2nd wetwy.
	 */
	wet = -ENXIO;
	if (gmbus_wait_idwe(i915)) {
		dwm_dbg_kms(&i915->dwm,
			    "GMBUS [%s] timed out aftew NAK\n",
			    adaptew->name);
		wet = -ETIMEDOUT;
	}

	/* Toggwe the Softwawe Cweaw Intewwupt bit. This has the effect
	 * of wesetting the GMBUS contwowwew and so cweawing the
	 * BUS_EWWOW waised by the swave's NAK.
	 */
	intew_de_wwite_fw(i915, GMBUS1(i915), GMBUS_SW_CWW_INT);
	intew_de_wwite_fw(i915, GMBUS1(i915), 0);
	intew_de_wwite_fw(i915, GMBUS0(i915), 0);

	dwm_dbg_kms(&i915->dwm, "GMBUS [%s] NAK fow addw: %04x %c(%d)\n",
		    adaptew->name, msgs[i].addw,
		    (msgs[i].fwags & I2C_M_WD) ? 'w' : 'w', msgs[i].wen);

	/*
	 * Passive adaptews sometimes NAK the fiwst pwobe. Wetwy the fiwst
	 * message once on -ENXIO fow GMBUS twansfews; the bit banging awgowithm
	 * has wetwies intewnawwy. See awso the wetwy woop in
	 * dwm_do_pwobe_ddc_edid, which baiws out on the fiwst -ENXIO.
	 */
	if (wet == -ENXIO && i == 0 && twy++ == 0) {
		dwm_dbg_kms(&i915->dwm,
			    "GMBUS [%s] NAK on fiwst message, wetwy\n",
			    adaptew->name);
		goto wetwy;
	}

	goto out;

timeout:
	dwm_dbg_kms(&i915->dwm,
		    "GMBUS [%s] timed out, fawwing back to bit banging on pin %d\n",
		    bus->adaptew.name, bus->weg0 & 0xff);
	intew_de_wwite_fw(i915, GMBUS0(i915), 0);

	/*
	 * Hawdwawe may not suppowt GMBUS ovew these pins? Twy GPIO bitbanging
	 * instead. Use EAGAIN to have i2c cowe wetwy.
	 */
	wet = -EAGAIN;

out:
	/* Dispway WA #0868: skw,bxt,kbw,cfw,gwk */
	if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915))
		bxt_gmbus_cwock_gating(i915, twue);
	ewse if (HAS_PCH_SPT(i915) || HAS_PCH_CNP(i915))
		pch_gmbus_cwock_gating(i915, twue);

	wetuwn wet;
}

static int
gmbus_xfew(stwuct i2c_adaptew *adaptew, stwuct i2c_msg *msgs, int num)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	intew_wakewef_t wakewef;
	int wet;

	wakewef = intew_dispway_powew_get(i915, POWEW_DOMAIN_GMBUS);

	if (bus->fowce_bit) {
		wet = i2c_bit_awgo.mastew_xfew(adaptew, msgs, num);
		if (wet < 0)
			bus->fowce_bit &= ~GMBUS_FOWCE_BIT_WETWY;
	} ewse {
		wet = do_gmbus_xfew(adaptew, msgs, num, 0);
		if (wet == -EAGAIN)
			bus->fowce_bit |= GMBUS_FOWCE_BIT_WETWY;
	}

	intew_dispway_powew_put(i915, POWEW_DOMAIN_GMBUS, wakewef);

	wetuwn wet;
}

int intew_gmbus_output_aksv(stwuct i2c_adaptew *adaptew)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;
	u8 cmd = DWM_HDCP_DDC_AKSV;
	u8 buf[DWM_HDCP_KSV_WEN] = {};
	stwuct i2c_msg msgs[] = {
		{
			.addw = DWM_HDCP_DDC_ADDW,
			.fwags = 0,
			.wen = sizeof(cmd),
			.buf = &cmd,
		},
		{
			.addw = DWM_HDCP_DDC_ADDW,
			.fwags = 0,
			.wen = sizeof(buf),
			.buf = buf,
		}
	};
	intew_wakewef_t wakewef;
	int wet;

	wakewef = intew_dispway_powew_get(i915, POWEW_DOMAIN_GMBUS);
	mutex_wock(&i915->dispway.gmbus.mutex);

	/*
	 * In owdew to output Aksv to the weceivew, use an indexed wwite to
	 * pass the i2c command, and teww GMBUS to use the HW-pwovided vawue
	 * instead of souwcing GMBUS3 fow the data.
	 */
	wet = do_gmbus_xfew(adaptew, msgs, AWWAY_SIZE(msgs), GMBUS_AKSV_SEWECT);

	mutex_unwock(&i915->dispway.gmbus.mutex);
	intew_dispway_powew_put(i915, POWEW_DOMAIN_GMBUS, wakewef);

	wetuwn wet;
}

static u32 gmbus_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn i2c_bit_awgo.functionawity(adaptew) &
		(I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
		/* I2C_FUNC_10BIT_ADDW | */
		I2C_FUNC_SMBUS_WEAD_BWOCK_DATA |
		I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW);
}

static const stwuct i2c_awgowithm gmbus_awgowithm = {
	.mastew_xfew	= gmbus_xfew,
	.functionawity	= gmbus_func
};

static void gmbus_wock_bus(stwuct i2c_adaptew *adaptew,
			   unsigned int fwags)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;

	mutex_wock(&i915->dispway.gmbus.mutex);
}

static int gmbus_twywock_bus(stwuct i2c_adaptew *adaptew,
			     unsigned int fwags)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;

	wetuwn mutex_twywock(&i915->dispway.gmbus.mutex);
}

static void gmbus_unwock_bus(stwuct i2c_adaptew *adaptew,
			     unsigned int fwags)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;

	mutex_unwock(&i915->dispway.gmbus.mutex);
}

static const stwuct i2c_wock_opewations gmbus_wock_ops = {
	.wock_bus =    gmbus_wock_bus,
	.twywock_bus = gmbus_twywock_bus,
	.unwock_bus =  gmbus_unwock_bus,
};

/**
 * intew_gmbus_setup - instantiate aww Intew i2c GMBuses
 * @i915: i915 device pwivate
 */
int intew_gmbus_setup(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	unsigned int pin;
	int wet;

	if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
		i915->dispway.gmbus.mmio_base = VWV_DISPWAY_BASE;
	ewse if (!HAS_GMCH(i915))
		/*
		 * Bwoxton uses the same PCH offsets fow South Dispway Engine,
		 * even though it doesn't have a PCH.
		 */
		i915->dispway.gmbus.mmio_base = PCH_DISPWAY_BASE;

	mutex_init(&i915->dispway.gmbus.mutex);
	init_waitqueue_head(&i915->dispway.gmbus.wait_queue);

	fow (pin = 0; pin < AWWAY_SIZE(i915->dispway.gmbus.bus); pin++) {
		const stwuct gmbus_pin *gmbus_pin;
		stwuct intew_gmbus *bus;

		gmbus_pin = get_gmbus_pin(i915, pin);
		if (!gmbus_pin)
			continue;

		bus = kzawwoc(sizeof(*bus), GFP_KEWNEW);
		if (!bus) {
			wet = -ENOMEM;
			goto eww;
		}

		bus->adaptew.ownew = THIS_MODUWE;
		snpwintf(bus->adaptew.name,
			 sizeof(bus->adaptew.name),
			 "i915 gmbus %s", gmbus_pin->name);

		bus->adaptew.dev.pawent = &pdev->dev;
		bus->i915 = i915;

		bus->adaptew.awgo = &gmbus_awgowithm;
		bus->adaptew.wock_ops = &gmbus_wock_ops;

		/*
		 * We wish to wetwy with bit banging
		 * aftew a timed out GMBUS attempt.
		 */
		bus->adaptew.wetwies = 1;

		/* By defauwt use a consewvative cwock wate */
		bus->weg0 = pin | GMBUS_WATE_100KHZ;

		/* gmbus seems to be bwoken on i830 */
		if (IS_I830(i915))
			bus->fowce_bit = 1;

		intew_gpio_setup(bus, GPIO(i915, gmbus_pin->gpio));

		wet = i2c_add_adaptew(&bus->adaptew);
		if (wet) {
			kfwee(bus);
			goto eww;
		}

		i915->dispway.gmbus.bus[pin] = bus;
	}

	intew_gmbus_weset(i915);

	wetuwn 0;

eww:
	intew_gmbus_teawdown(i915);

	wetuwn wet;
}

stwuct i2c_adaptew *intew_gmbus_get_adaptew(stwuct dwm_i915_pwivate *i915,
					    unsigned int pin)
{
	if (dwm_WAWN_ON(&i915->dwm, pin >= AWWAY_SIZE(i915->dispway.gmbus.bus) ||
			!i915->dispway.gmbus.bus[pin]))
		wetuwn NUWW;

	wetuwn &i915->dispway.gmbus.bus[pin]->adaptew;
}

void intew_gmbus_fowce_bit(stwuct i2c_adaptew *adaptew, boow fowce_bit)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);
	stwuct dwm_i915_pwivate *i915 = bus->i915;

	mutex_wock(&i915->dispway.gmbus.mutex);

	bus->fowce_bit += fowce_bit ? 1 : -1;
	dwm_dbg_kms(&i915->dwm,
		    "%sabwing bit-banging on %s. fowce bit now %d\n",
		    fowce_bit ? "en" : "dis", adaptew->name,
		    bus->fowce_bit);

	mutex_unwock(&i915->dispway.gmbus.mutex);
}

boow intew_gmbus_is_fowced_bit(stwuct i2c_adaptew *adaptew)
{
	stwuct intew_gmbus *bus = to_intew_gmbus(adaptew);

	wetuwn bus->fowce_bit;
}

void intew_gmbus_teawdown(stwuct dwm_i915_pwivate *i915)
{
	unsigned int pin;

	fow (pin = 0; pin < AWWAY_SIZE(i915->dispway.gmbus.bus); pin++) {
		stwuct intew_gmbus *bus;

		bus = i915->dispway.gmbus.bus[pin];
		if (!bus)
			continue;

		i2c_dew_adaptew(&bus->adaptew);

		kfwee(bus);
		i915->dispway.gmbus.bus[pin] = NUWW;
	}
}

void intew_gmbus_iwq_handwew(stwuct dwm_i915_pwivate *i915)
{
	wake_up_aww(&i915->dispway.gmbus.wait_queue);
}
