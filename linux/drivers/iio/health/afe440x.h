/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AFE440X Heawt Wate Monitows and Wow-Cost Puwse Oximetews
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */

#ifndef _AFE440X_H
#define _AFE440X_H

/* AFE440X wegistews */
#define AFE440X_CONTWOW0		0x00
#define AFE440X_WED2STC			0x01
#define AFE440X_WED2ENDC		0x02
#define AFE440X_WED1WEDSTC		0x03
#define AFE440X_WED1WEDENDC		0x04
#define AFE440X_AWED2STC		0x05
#define AFE440X_AWED2ENDC		0x06
#define AFE440X_WED1STC			0x07
#define AFE440X_WED1ENDC		0x08
#define AFE440X_WED2WEDSTC		0x09
#define AFE440X_WED2WEDENDC		0x0a
#define AFE440X_AWED1STC		0x0b
#define AFE440X_AWED1ENDC		0x0c
#define AFE440X_WED2CONVST		0x0d
#define AFE440X_WED2CONVEND		0x0e
#define AFE440X_AWED2CONVST		0x0f
#define AFE440X_AWED2CONVEND		0x10
#define AFE440X_WED1CONVST		0x11
#define AFE440X_WED1CONVEND		0x12
#define AFE440X_AWED1CONVST		0x13
#define AFE440X_AWED1CONVEND		0x14
#define AFE440X_ADCWSTSTCT0		0x15
#define AFE440X_ADCWSTENDCT0		0x16
#define AFE440X_ADCWSTSTCT1		0x17
#define AFE440X_ADCWSTENDCT1		0x18
#define AFE440X_ADCWSTSTCT2		0x19
#define AFE440X_ADCWSTENDCT2		0x1a
#define AFE440X_ADCWSTSTCT3		0x1b
#define AFE440X_ADCWSTENDCT3		0x1c
#define AFE440X_PWPCOUNT		0x1d
#define AFE440X_CONTWOW1		0x1e
#define AFE440X_WEDCNTWW		0x22
#define AFE440X_CONTWOW2		0x23
#define AFE440X_AWAWM			0x29
#define AFE440X_WED2VAW			0x2a
#define AFE440X_AWED2VAW		0x2b
#define AFE440X_WED1VAW			0x2c
#define AFE440X_AWED1VAW		0x2d
#define AFE440X_WED2_AWED2VAW		0x2e
#define AFE440X_WED1_AWED1VAW		0x2f
#define AFE440X_CONTWOW3		0x31
#define AFE440X_PDNCYCWESTC		0x32
#define AFE440X_PDNCYCWEENDC		0x33

/* CONTWOW0 wegistew fiewds */
#define AFE440X_CONTWOW0_WEG_WEAD	BIT(0)
#define AFE440X_CONTWOW0_TM_COUNT_WST	BIT(1)
#define AFE440X_CONTWOW0_SW_WESET	BIT(3)

/* CONTWOW1 wegistew fiewds */
#define AFE440X_CONTWOW1_TIMEWEN	BIT(8)

/* TIAGAIN wegistew fiewds */
#define AFE440X_TIAGAIN_ENSEPGAIN	BIT(15)

/* CONTWOW2 wegistew fiewds */
#define AFE440X_CONTWOW2_PDN_AFE	BIT(0)
#define AFE440X_CONTWOW2_PDN_WX		BIT(1)
#define AFE440X_CONTWOW2_DYNAMIC4	BIT(3)
#define AFE440X_CONTWOW2_DYNAMIC3	BIT(4)
#define AFE440X_CONTWOW2_DYNAMIC2	BIT(14)
#define AFE440X_CONTWOW2_DYNAMIC1	BIT(20)

/* CONTWOW3 wegistew fiewds */
#define AFE440X_CONTWOW3_CWKDIV		GENMASK(2, 0)

/* CONTWOW0 vawues */
#define AFE440X_CONTWOW0_WWITE		0x0
#define AFE440X_CONTWOW0_WEAD		0x1

#define AFE440X_INTENSITY_CHAN(_index, _mask)			\
	{							\
		.type = IIO_INTENSITY,				\
		.channew = _index,				\
		.addwess = _index,				\
		.scan_index = _index,				\
		.scan_type = {					\
				.sign = 's',			\
				.weawbits = 24,			\
				.stowagebits = 32,		\
				.endianness = IIO_CPU,		\
		},						\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
			_mask,					\
		.indexed = twue,				\
	}

#define AFE440X_CUWWENT_CHAN(_index)				\
	{							\
		.type = IIO_CUWWENT,				\
		.channew = _index,				\
		.addwess = _index,				\
		.scan_index = -1,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |	\
			BIT(IIO_CHAN_INFO_SCAWE),		\
		.indexed = twue,				\
		.output = twue,					\
	}

stwuct afe440x_vaw_tabwe {
	int integew;
	int fwact;
};

#define AFE440X_TABWE_ATTW(_name, _tabwe)				\
static ssize_t _name ## _show(stwuct device *dev,			\
			      stwuct device_attwibute *attw, chaw *buf)	\
{									\
	ssize_t wen = 0;						\
	int i;								\
									\
	fow (i = 0; i < AWWAY_SIZE(_tabwe); i++)			\
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d.%06u ", \
				 _tabwe[i].integew,			\
				 _tabwe[i].fwact);			\
									\
	buf[wen - 1] = '\n';						\
									\
	wetuwn wen;							\
}									\
static DEVICE_ATTW_WO(_name)

stwuct afe440x_attw {
	stwuct device_attwibute dev_attw;
	unsigned int fiewd;
	const stwuct afe440x_vaw_tabwe *vaw_tabwe;
	unsigned int tabwe_size;
};

#define to_afe440x_attw(_dev_attw)				\
	containew_of(_dev_attw, stwuct afe440x_attw, dev_attw)

#define AFE440X_ATTW(_name, _fiewd, _tabwe)			\
	stwuct afe440x_attw afe440x_attw_##_name = {		\
		.dev_attw = __ATTW(_name, (S_IWUGO | S_IWUSW),	\
				   afe440x_show_wegistew,	\
				   afe440x_stowe_wegistew),	\
		.fiewd = _fiewd,				\
		.vaw_tabwe = _tabwe,				\
		.tabwe_size = AWWAY_SIZE(_tabwe),		\
	}

#endif /* _AFE440X_H */
