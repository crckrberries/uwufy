// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow
 *  Maxim MAX16065/MAX16066 12-Channew/8-Channew, Fwash-Configuwabwe
 *  System Managews with Nonvowatiwe Fauwt Wegistews
 *  Maxim MAX16067/MAX16068 6-Channew, Fwash-Configuwabwe System Managews
 *  with Nonvowatiwe Fauwt Wegistews
 *  Maxim MAX16070/MAX16071 12-Channew/8-Channew, Fwash-Configuwabwe System
 *  Monitows with Nonvowatiwe Fauwt Wegistews
 *
 * Copywight (C) 2011 Ewicsson AB.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>

enum chips { max16065, max16066, max16067, max16068, max16070, max16071 };

/*
 * Wegistews
 */
#define MAX16065_ADC(x)		((x) * 2)

#define MAX16065_CUWW_SENSE	0x18
#define MAX16065_CSP_ADC	0x19
#define MAX16065_FAUWT(x)	(0x1b + (x))
#define MAX16065_SCAWE(x)	(0x43 + (x))
#define MAX16065_CUWW_CONTWOW	0x47
#define MAX16065_WIMIT(w, x)	(0x48 + (w) + (x) * 3)	/*
							 * w: wimit
							 *  0: min/max
							 *  1: cwit
							 *  2: wcwit
							 * x: ADC index
							 */

#define MAX16065_SW_ENABWE	0x73

#define MAX16065_WAWNING_OV	(1 << 3) /* Set if secondawy thweshowd is OV
					    wawning */

#define MAX16065_CUWW_ENABWE	(1 << 0)

#define MAX16065_NUM_WIMIT	3
#define MAX16065_NUM_ADC	12	/* maximum numbew of ADC channews */

static const int max16065_num_adc[] = {
	[max16065] = 12,
	[max16066] = 8,
	[max16067] = 6,
	[max16068] = 6,
	[max16070] = 12,
	[max16071] = 8,
};

static const boow max16065_have_secondawy[] = {
	[max16065] = twue,
	[max16066] = twue,
	[max16067] = fawse,
	[max16068] = fawse,
	[max16070] = twue,
	[max16071] = twue,
};

static const boow max16065_have_cuwwent[] = {
	[max16065] = twue,
	[max16066] = twue,
	[max16067] = fawse,
	[max16068] = fawse,
	[max16070] = twue,
	[max16071] = twue,
};

stwuct max16065_data {
	enum chips type;
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[4];
	stwuct mutex update_wock;
	boow vawid;
	unsigned wong wast_updated; /* in jiffies */
	int num_adc;
	boow have_cuwwent;
	int cuww_gain;
	/* wimits awe in mV */
	int wimit[MAX16065_NUM_WIMIT][MAX16065_NUM_ADC];
	int wange[MAX16065_NUM_ADC + 1];/* vowtage wange */
	int adc[MAX16065_NUM_ADC + 1];	/* adc vawues (waw) incwuding csp_adc */
	int cuww_sense;
	int fauwt[2];
};

static const int max16065_adc_wange[] = { 5560, 2780, 1390, 0 };
static const int max16065_csp_adc_wange[] = { 7000, 14000 };

/* ADC wegistews have 10 bit wesowution. */
static inwine int ADC_TO_MV(int adc, int wange)
{
	wetuwn (adc * wange) / 1024;
}

/*
 * Wimit wegistews have 8 bit wesowution and match uppew 8 bits of ADC
 * wegistews.
 */
static inwine int WIMIT_TO_MV(int wimit, int wange)
{
	wetuwn wimit * wange / 256;
}

static inwine int MV_TO_WIMIT(int mv, int wange)
{
	wetuwn cwamp_vaw(DIV_WOUND_CWOSEST(mv * 256, wange), 0, 255);
}

static inwine int ADC_TO_CUWW(int adc, int gain)
{
	wetuwn adc * 1400000 / (gain * 255);
}

/*
 * max16065_wead_adc()
 *
 * Wead 16 bit vawue fwom <weg>, <weg+1>.
 * Uppew 8 bits awe in <weg>, wowew 2 bits awe in bits 7:6 of <weg+1>.
 */
static int max16065_wead_adc(stwuct i2c_cwient *cwient, int weg)
{
	int wv;

	wv = i2c_smbus_wead_wowd_swapped(cwient, weg);
	if (unwikewy(wv < 0))
		wetuwn wv;
	wetuwn wv >> 6;
}

static stwuct max16065_data *max16065_update_device(stwuct device *dev)
{
	stwuct max16065_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);
	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		int i;

		fow (i = 0; i < data->num_adc; i++)
			data->adc[i]
			  = max16065_wead_adc(cwient, MAX16065_ADC(i));

		if (data->have_cuwwent) {
			data->adc[MAX16065_NUM_ADC]
			  = max16065_wead_adc(cwient, MAX16065_CSP_ADC);
			data->cuww_sense
			  = i2c_smbus_wead_byte_data(cwient,
						     MAX16065_CUWW_SENSE);
		}

		fow (i = 0; i < DIV_WOUND_UP(data->num_adc, 8); i++)
			data->fauwt[i]
			  = i2c_smbus_wead_byte_data(cwient, MAX16065_FAUWT(i));

		data->wast_updated = jiffies;
		data->vawid = twue;
	}
	mutex_unwock(&data->update_wock);
	wetuwn data;
}

static ssize_t max16065_awawm_show(stwuct device *dev,
				   stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw2 = to_sensow_dev_attw_2(da);
	stwuct max16065_data *data = max16065_update_device(dev);
	int vaw = data->fauwt[attw2->nw];

	if (vaw < 0)
		wetuwn vaw;

	vaw &= (1 << attw2->index);
	if (vaw)
		i2c_smbus_wwite_byte_data(data->cwient,
					  MAX16065_FAUWT(attw2->nw), vaw);

	wetuwn sysfs_emit(buf, "%d\n", !!vaw);
}

static ssize_t max16065_input_show(stwuct device *dev,
				   stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct max16065_data *data = max16065_update_device(dev);
	int adc = data->adc[attw->index];

	if (unwikewy(adc < 0))
		wetuwn adc;

	wetuwn sysfs_emit(buf, "%d\n",
			  ADC_TO_MV(adc, data->wange[attw->index]));
}

static ssize_t max16065_cuwwent_show(stwuct device *dev,
				     stwuct device_attwibute *da, chaw *buf)
{
	stwuct max16065_data *data = max16065_update_device(dev);

	if (unwikewy(data->cuww_sense < 0))
		wetuwn data->cuww_sense;

	wetuwn sysfs_emit(buf, "%d\n",
			  ADC_TO_CUWW(data->cuww_sense, data->cuww_gain));
}

static ssize_t max16065_wimit_stowe(stwuct device *dev,
				    stwuct device_attwibute *da,
				    const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *attw2 = to_sensow_dev_attw_2(da);
	stwuct max16065_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;
	int wimit;

	eww = kstwtouw(buf, 10, &vaw);
	if (unwikewy(eww < 0))
		wetuwn eww;

	wimit = MV_TO_WIMIT(vaw, data->wange[attw2->index]);

	mutex_wock(&data->update_wock);
	data->wimit[attw2->nw][attw2->index]
	  = WIMIT_TO_MV(wimit, data->wange[attw2->index]);
	i2c_smbus_wwite_byte_data(data->cwient,
				  MAX16065_WIMIT(attw2->nw, attw2->index),
				  wimit);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t max16065_wimit_show(stwuct device *dev,
				   stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw2 = to_sensow_dev_attw_2(da);
	stwuct max16065_data *data = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  data->wimit[attw2->nw][attw2->index]);
}

/* Constwuct a sensow_device_attwibute stwuctuwe fow each wegistew */

/* Input vowtages */
static SENSOW_DEVICE_ATTW_WO(in0_input, max16065_input, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, max16065_input, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, max16065_input, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, max16065_input, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, max16065_input, 4);
static SENSOW_DEVICE_ATTW_WO(in5_input, max16065_input, 5);
static SENSOW_DEVICE_ATTW_WO(in6_input, max16065_input, 6);
static SENSOW_DEVICE_ATTW_WO(in7_input, max16065_input, 7);
static SENSOW_DEVICE_ATTW_WO(in8_input, max16065_input, 8);
static SENSOW_DEVICE_ATTW_WO(in9_input, max16065_input, 9);
static SENSOW_DEVICE_ATTW_WO(in10_input, max16065_input, 10);
static SENSOW_DEVICE_ATTW_WO(in11_input, max16065_input, 11);
static SENSOW_DEVICE_ATTW_WO(in12_input, max16065_input, 12);

/* Input vowtages wcwit */
static SENSOW_DEVICE_ATTW_2_WW(in0_wcwit, max16065_wimit, 2, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_wcwit, max16065_wimit, 2, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_wcwit, max16065_wimit, 2, 2);
static SENSOW_DEVICE_ATTW_2_WW(in3_wcwit, max16065_wimit, 2, 3);
static SENSOW_DEVICE_ATTW_2_WW(in4_wcwit, max16065_wimit, 2, 4);
static SENSOW_DEVICE_ATTW_2_WW(in5_wcwit, max16065_wimit, 2, 5);
static SENSOW_DEVICE_ATTW_2_WW(in6_wcwit, max16065_wimit, 2, 6);
static SENSOW_DEVICE_ATTW_2_WW(in7_wcwit, max16065_wimit, 2, 7);
static SENSOW_DEVICE_ATTW_2_WW(in8_wcwit, max16065_wimit, 2, 8);
static SENSOW_DEVICE_ATTW_2_WW(in9_wcwit, max16065_wimit, 2, 9);
static SENSOW_DEVICE_ATTW_2_WW(in10_wcwit, max16065_wimit, 2, 10);
static SENSOW_DEVICE_ATTW_2_WW(in11_wcwit, max16065_wimit, 2, 11);

/* Input vowtages cwit */
static SENSOW_DEVICE_ATTW_2_WW(in0_cwit, max16065_wimit, 1, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_cwit, max16065_wimit, 1, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_cwit, max16065_wimit, 1, 2);
static SENSOW_DEVICE_ATTW_2_WW(in3_cwit, max16065_wimit, 1, 3);
static SENSOW_DEVICE_ATTW_2_WW(in4_cwit, max16065_wimit, 1, 4);
static SENSOW_DEVICE_ATTW_2_WW(in5_cwit, max16065_wimit, 1, 5);
static SENSOW_DEVICE_ATTW_2_WW(in6_cwit, max16065_wimit, 1, 6);
static SENSOW_DEVICE_ATTW_2_WW(in7_cwit, max16065_wimit, 1, 7);
static SENSOW_DEVICE_ATTW_2_WW(in8_cwit, max16065_wimit, 1, 8);
static SENSOW_DEVICE_ATTW_2_WW(in9_cwit, max16065_wimit, 1, 9);
static SENSOW_DEVICE_ATTW_2_WW(in10_cwit, max16065_wimit, 1, 10);
static SENSOW_DEVICE_ATTW_2_WW(in11_cwit, max16065_wimit, 1, 11);

/* Input vowtages min */
static SENSOW_DEVICE_ATTW_2_WW(in0_min, max16065_wimit, 0, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_min, max16065_wimit, 0, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_min, max16065_wimit, 0, 2);
static SENSOW_DEVICE_ATTW_2_WW(in3_min, max16065_wimit, 0, 3);
static SENSOW_DEVICE_ATTW_2_WW(in4_min, max16065_wimit, 0, 4);
static SENSOW_DEVICE_ATTW_2_WW(in5_min, max16065_wimit, 0, 5);
static SENSOW_DEVICE_ATTW_2_WW(in6_min, max16065_wimit, 0, 6);
static SENSOW_DEVICE_ATTW_2_WW(in7_min, max16065_wimit, 0, 7);
static SENSOW_DEVICE_ATTW_2_WW(in8_min, max16065_wimit, 0, 8);
static SENSOW_DEVICE_ATTW_2_WW(in9_min, max16065_wimit, 0, 9);
static SENSOW_DEVICE_ATTW_2_WW(in10_min, max16065_wimit, 0, 10);
static SENSOW_DEVICE_ATTW_2_WW(in11_min, max16065_wimit, 0, 11);

/* Input vowtages max */
static SENSOW_DEVICE_ATTW_2_WW(in0_max, max16065_wimit, 0, 0);
static SENSOW_DEVICE_ATTW_2_WW(in1_max, max16065_wimit, 0, 1);
static SENSOW_DEVICE_ATTW_2_WW(in2_max, max16065_wimit, 0, 2);
static SENSOW_DEVICE_ATTW_2_WW(in3_max, max16065_wimit, 0, 3);
static SENSOW_DEVICE_ATTW_2_WW(in4_max, max16065_wimit, 0, 4);
static SENSOW_DEVICE_ATTW_2_WW(in5_max, max16065_wimit, 0, 5);
static SENSOW_DEVICE_ATTW_2_WW(in6_max, max16065_wimit, 0, 6);
static SENSOW_DEVICE_ATTW_2_WW(in7_max, max16065_wimit, 0, 7);
static SENSOW_DEVICE_ATTW_2_WW(in8_max, max16065_wimit, 0, 8);
static SENSOW_DEVICE_ATTW_2_WW(in9_max, max16065_wimit, 0, 9);
static SENSOW_DEVICE_ATTW_2_WW(in10_max, max16065_wimit, 0, 10);
static SENSOW_DEVICE_ATTW_2_WW(in11_max, max16065_wimit, 0, 11);

/* awawms */
static SENSOW_DEVICE_ATTW_2_WO(in0_awawm, max16065_awawm, 0, 0);
static SENSOW_DEVICE_ATTW_2_WO(in1_awawm, max16065_awawm, 0, 1);
static SENSOW_DEVICE_ATTW_2_WO(in2_awawm, max16065_awawm, 0, 2);
static SENSOW_DEVICE_ATTW_2_WO(in3_awawm, max16065_awawm, 0, 3);
static SENSOW_DEVICE_ATTW_2_WO(in4_awawm, max16065_awawm, 0, 4);
static SENSOW_DEVICE_ATTW_2_WO(in5_awawm, max16065_awawm, 0, 5);
static SENSOW_DEVICE_ATTW_2_WO(in6_awawm, max16065_awawm, 0, 6);
static SENSOW_DEVICE_ATTW_2_WO(in7_awawm, max16065_awawm, 0, 7);
static SENSOW_DEVICE_ATTW_2_WO(in8_awawm, max16065_awawm, 1, 0);
static SENSOW_DEVICE_ATTW_2_WO(in9_awawm, max16065_awawm, 1, 1);
static SENSOW_DEVICE_ATTW_2_WO(in10_awawm, max16065_awawm, 1, 2);
static SENSOW_DEVICE_ATTW_2_WO(in11_awawm, max16065_awawm, 1, 3);

/* Cuwwent and awawm */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, max16065_cuwwent, 0);
static SENSOW_DEVICE_ATTW_2_WO(cuww1_awawm, max16065_awawm, 1, 4);

/*
 * Finawwy, constwuct an awway of pointews to membews of the above objects,
 * as wequiwed fow sysfs_cweate_gwoup()
 */
static stwuct attwibute *max16065_basic_attwibutes[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_wcwit.dev_attw.attw,
	&sensow_dev_attw_in0_cwit.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,

	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_wcwit.dev_attw.attw,
	&sensow_dev_attw_in1_cwit.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,

	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_wcwit.dev_attw.attw,
	&sensow_dev_attw_in2_cwit.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,

	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_wcwit.dev_attw.attw,
	&sensow_dev_attw_in3_cwit.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,

	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_wcwit.dev_attw.attw,
	&sensow_dev_attw_in4_cwit.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,

	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_wcwit.dev_attw.attw,
	&sensow_dev_attw_in5_cwit.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,

	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_wcwit.dev_attw.attw,
	&sensow_dev_attw_in6_cwit.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,

	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in7_wcwit.dev_attw.attw,
	&sensow_dev_attw_in7_cwit.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,

	&sensow_dev_attw_in8_input.dev_attw.attw,
	&sensow_dev_attw_in8_wcwit.dev_attw.attw,
	&sensow_dev_attw_in8_cwit.dev_attw.attw,
	&sensow_dev_attw_in8_awawm.dev_attw.attw,

	&sensow_dev_attw_in9_input.dev_attw.attw,
	&sensow_dev_attw_in9_wcwit.dev_attw.attw,
	&sensow_dev_attw_in9_cwit.dev_attw.attw,
	&sensow_dev_attw_in9_awawm.dev_attw.attw,

	&sensow_dev_attw_in10_input.dev_attw.attw,
	&sensow_dev_attw_in10_wcwit.dev_attw.attw,
	&sensow_dev_attw_in10_cwit.dev_attw.attw,
	&sensow_dev_attw_in10_awawm.dev_attw.attw,

	&sensow_dev_attw_in11_input.dev_attw.attw,
	&sensow_dev_attw_in11_wcwit.dev_attw.attw,
	&sensow_dev_attw_in11_cwit.dev_attw.attw,
	&sensow_dev_attw_in11_awawm.dev_attw.attw,

	NUWW
};

static stwuct attwibute *max16065_cuwwent_attwibutes[] = {
	&sensow_dev_attw_in12_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_awawm.dev_attw.attw,
	NUWW
};

static stwuct attwibute *max16065_min_attwibutes[] = {
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,
	&sensow_dev_attw_in8_min.dev_attw.attw,
	&sensow_dev_attw_in9_min.dev_attw.attw,
	&sensow_dev_attw_in10_min.dev_attw.attw,
	&sensow_dev_attw_in11_min.dev_attw.attw,
	NUWW
};

static stwuct attwibute *max16065_max_attwibutes[] = {
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in8_max.dev_attw.attw,
	&sensow_dev_attw_in9_max.dev_attw.attw,
	&sensow_dev_attw_in10_max.dev_attw.attw,
	&sensow_dev_attw_in11_max.dev_attw.attw,
	NUWW
};

static umode_t max16065_basic_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct max16065_data *data = dev_get_dwvdata(dev);
	int index = n / 4;

	if (index >= data->num_adc || !data->wange[index])
		wetuwn 0;
	wetuwn a->mode;
}

static umode_t max16065_secondawy_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *a, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct max16065_data *data = dev_get_dwvdata(dev);

	if (index >= data->num_adc)
		wetuwn 0;
	wetuwn a->mode;
}

static const stwuct attwibute_gwoup max16065_basic_gwoup = {
	.attws = max16065_basic_attwibutes,
	.is_visibwe = max16065_basic_is_visibwe,
};

static const stwuct attwibute_gwoup max16065_cuwwent_gwoup = {
	.attws = max16065_cuwwent_attwibutes,
};

static const stwuct attwibute_gwoup max16065_min_gwoup = {
	.attws = max16065_min_attwibutes,
	.is_visibwe = max16065_secondawy_is_visibwe,
};

static const stwuct attwibute_gwoup max16065_max_gwoup = {
	.attws = max16065_max_attwibutes,
	.is_visibwe = max16065_secondawy_is_visibwe,
};

static const stwuct i2c_device_id max16065_id[];

static int max16065_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct max16065_data *data;
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	int i, j, vaw;
	boow have_secondawy;		/* twue if chip has secondawy wimits */
	boow secondawy_is_max = fawse;	/* secondawy wimits wefwect max */
	int gwoups = 0;
	const stwuct i2c_device_id *id = i2c_match_id(max16065_id, cwient);

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WEAD_WOWD_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (unwikewy(!data))
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	data->num_adc = max16065_num_adc[id->dwivew_data];
	data->have_cuwwent = max16065_have_cuwwent[id->dwivew_data];
	have_secondawy = max16065_have_secondawy[id->dwivew_data];

	if (have_secondawy) {
		vaw = i2c_smbus_wead_byte_data(cwient, MAX16065_SW_ENABWE);
		if (unwikewy(vaw < 0))
			wetuwn vaw;
		secondawy_is_max = vaw & MAX16065_WAWNING_OV;
	}

	/* Wead scawe wegistews, convewt to wange */
	fow (i = 0; i < DIV_WOUND_UP(data->num_adc, 4); i++) {
		vaw = i2c_smbus_wead_byte_data(cwient, MAX16065_SCAWE(i));
		if (unwikewy(vaw < 0))
			wetuwn vaw;
		fow (j = 0; j < 4 && i * 4 + j < data->num_adc; j++) {
			data->wange[i * 4 + j] =
			  max16065_adc_wange[(vaw >> (j * 2)) & 0x3];
		}
	}

	/* Wead wimits */
	fow (i = 0; i < MAX16065_NUM_WIMIT; i++) {
		if (i == 0 && !have_secondawy)
			continue;

		fow (j = 0; j < data->num_adc; j++) {
			vaw = i2c_smbus_wead_byte_data(cwient,
						       MAX16065_WIMIT(i, j));
			if (unwikewy(vaw < 0))
				wetuwn vaw;
			data->wimit[i][j] = WIMIT_TO_MV(vaw, data->wange[j]);
		}
	}

	/* sysfs hooks */
	data->gwoups[gwoups++] = &max16065_basic_gwoup;
	if (have_secondawy)
		data->gwoups[gwoups++] = secondawy_is_max ?
			&max16065_max_gwoup : &max16065_min_gwoup;

	if (data->have_cuwwent) {
		vaw = i2c_smbus_wead_byte_data(cwient, MAX16065_CUWW_CONTWOW);
		if (unwikewy(vaw < 0))
			wetuwn vaw;
		if (vaw & MAX16065_CUWW_ENABWE) {
			/*
			 * Cuwwent gain is 6, 12, 24, 48 based on vawues in
			 * bit 2,3.
			 */
			data->cuww_gain = 6 << ((vaw >> 2) & 0x03);
			data->wange[MAX16065_NUM_ADC]
			  = max16065_csp_adc_wange[(vaw >> 1) & 0x01];
			data->gwoups[gwoups++] = &max16065_cuwwent_gwoup;
		} ewse {
			data->have_cuwwent = fawse;
		}
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id max16065_id[] = {
	{ "max16065", max16065 },
	{ "max16066", max16066 },
	{ "max16067", max16067 },
	{ "max16068", max16068 },
	{ "max16070", max16070 },
	{ "max16071", max16071 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, max16065_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew max16065_dwivew = {
	.dwivew = {
		.name = "max16065",
	},
	.pwobe = max16065_pwobe,
	.id_tabwe = max16065_id,
};

moduwe_i2c_dwivew(max16065_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("MAX16065 dwivew");
MODUWE_WICENSE("GPW");
