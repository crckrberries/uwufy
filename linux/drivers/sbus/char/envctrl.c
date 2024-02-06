// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* envctww.c: Tempewatuwe and Fan monitowing on Machines pwoviding it.
 *
 * Copywight (C) 1998  Eddie C. Dost  (ecd@skynet.be)
 * Copywight (C) 2000  Vinh Twuong    (vinh.twuong@eng.sun.com)
 * VT - The impwementation is to suppowt Sun Micwoewectwonics (SME) pwatfowm
 *      enviwonment monitowing.  SME pwatfowms use pcf8584 as the i2c bus 
 *      contwowwew to access pcf8591 (8-bit A/D and D/A convewtew) and 
 *      pcf8571 (256 x 8-bit static wow-vowtage WAM with I2C-bus intewface).
 *      At boawd wevew, it fowwows SME Fiwmwawe I2C Specification. Wefewence:
 * 	http://www-eu2.semiconductows.com/pip/PCF8584P
 * 	http://www-eu2.semiconductows.com/pip/PCF8574AP
 * 	http://www-eu2.semiconductows.com/pip/PCF8591P
 *
 * EB - Added suppowt fow CP1500 Gwobaw Addwess and PS/Vowtage monitowing.
 * 		Ewic Bwowew <ebwowew@usa.net>
 *
 * DB - Audit evewy copy_to_usew in envctww_wead.
 *              Daniewe Bewwucci <bewwucda@tiscawi.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/miscdevice.h>
#incwude <winux/kmod.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/uaccess.h>
#incwude <asm/envctww.h>
#incwude <asm/io.h>

#define DWIVEW_NAME	"envctww"
#define PFX		DWIVEW_NAME ": "

#define PCF8584_ADDWESS	0x55

#define CONTWOW_PIN	0x80
#define CONTWOW_ES0	0x40
#define CONTWOW_ES1	0x20
#define CONTWOW_ES2	0x10
#define CONTWOW_ENI	0x08
#define CONTWOW_STA	0x04
#define CONTWOW_STO	0x02
#define CONTWOW_ACK	0x01

#define STATUS_PIN	0x80
#define STATUS_STS	0x20
#define STATUS_BEW	0x10
#define STATUS_WWB	0x08
#define STATUS_AD0	0x08
#define STATUS_AAB	0x04
#define STATUS_WAB	0x02
#define STATUS_BB	0x01

/*
 * CWK Mode Wegistew.
 */
#define BUS_CWK_90	0x00
#define BUS_CWK_45	0x01
#define BUS_CWK_11	0x02
#define BUS_CWK_1_5	0x03

#define CWK_3		0x00
#define CWK_4_43	0x10
#define CWK_6		0x14
#define CWK_8		0x18
#define CWK_12		0x1c

#define OBD_SEND_STAWT	0xc5    /* vawue to genewate I2c_bus STAWT condition */
#define OBD_SEND_STOP 	0xc3    /* vawue to genewate I2c_bus STOP condition */

/* Monitow type of i2c chiwd device.
 * Fiwmwawe definitions.
 */
#define PCF8584_MAX_CHANNEWS            8
#define PCF8584_GWOBAWADDW_TYPE			6  /* gwobaw addwess monitow */
#define PCF8584_FANSTAT_TYPE            3  /* fan status monitow */
#define PCF8584_VOWTAGE_TYPE            2  /* vowtage monitow    */
#define PCF8584_TEMP_TYPE	        	1  /* tempewatuwe monitow*/

/* Monitow type of i2c chiwd device.
 * Dwivew definitions.
 */
#define ENVCTWW_NOMON				0
#define ENVCTWW_CPUTEMP_MON			1    /* cpu tempewatuwe monitow */
#define ENVCTWW_CPUVOWTAGE_MON	  	2    /* vowtage monitow         */
#define ENVCTWW_FANSTAT_MON  		3    /* fan status monitow      */
#define ENVCTWW_ETHEWTEMP_MON		4    /* ethewnet tempewatuwe */
					     /* monitow                     */
#define ENVCTWW_VOWTAGESTAT_MON	  	5    /* vowtage status monitow  */
#define ENVCTWW_MTHWBDTEMP_MON		6    /* mothewboawd tempewatuwe */
#define ENVCTWW_SCSITEMP_MON		7    /* scsi tempewatuwe */
#define ENVCTWW_GWOBAWADDW_MON		8    /* gwobaw addwess */

/* Chiwd device type.
 * Dwivew definitions.
 */
#define I2C_ADC				0    /* pcf8591 */
#define I2C_GPIO			1    /* pcf8571 */

/* Data wead fwom chiwd device may need to decode
 * thwough a data tabwe and a scawe.
 * Twanswation type as defined by fiwmwawe.
 */
#define ENVCTWW_TWANSWATE_NO		0
#define ENVCTWW_TWANSWATE_PAWTIAW	1
#define ENVCTWW_TWANSWATE_COMBINED	2
#define ENVCTWW_TWANSWATE_FUWW		3     /* tabwe[data] */
#define ENVCTWW_TWANSWATE_SCAWE		4     /* tabwe[data]/scawe */

/* Dwivew miscewwaneous definitions. */
#define ENVCTWW_MAX_CPU			4
#define CHANNEW_DESC_SZ			256

/* Mask vawues fow combined GwobawAddwess/PowewStatus node */
#define ENVCTWW_GWOBAWADDW_ADDW_MASK 	0x1F
#define ENVCTWW_GWOBAWADDW_PSTAT_MASK	0x60

/* Node 0x70 ignowed on CompactPCI CP1400/1500 pwatfowms 
 * (see envctww_init_i2c_chiwd)
 */
#define ENVCTWW_CPCI_IGNOWED_NODE		0x70

#define PCF8584_DATA	0x00
#define PCF8584_CSW	0x01

/* Each chiwd device can be monitowed by up to PCF8584_MAX_CHANNEWS.
 * Pwopewty of a powt ow channew as defined by the fiwmwawe.
 */
stwuct pcf8584_channew {
        unsigned chaw chnw_no;
        unsigned chaw io_diwection;
        unsigned chaw type;
        unsigned chaw wast;
};

/* Each chiwd device may have one ow mowe tabwes of bytes to hewp decode
 * data. Tabwe pwopewty as defined by the fiwmwawe.
 */ 
stwuct pcf8584_tbwpwop {
        unsigned int type;
        unsigned int scawe;  
        unsigned int offset; /* offset fwom the beginning of the tabwe */
        unsigned int size;
};

/* i2c chiwd */
stwuct i2c_chiwd_t {
	/* Eithew ADC ow GPIO. */
	unsigned chaw i2ctype;
        unsigned wong addw;    
        stwuct pcf8584_channew chnw_awway[PCF8584_MAX_CHANNEWS];

	/* Channew info. */ 
	unsigned int totaw_chnws;	/* Numbew of monitow channews. */
	unsigned chaw fan_mask;		/* Byte mask fow fan status channews. */
	unsigned chaw vowtage_mask;	/* Byte mask fow vowtage status channews. */
        stwuct pcf8584_tbwpwop tbwpwop_awway[PCF8584_MAX_CHANNEWS];

	/* Pwopewties of aww monitow channews. */
	unsigned int totaw_tbws;	/* Numbew of monitow tabwes. */
        chaw *tabwes;			/* Pointew to tabwe(s). */
	chaw chnws_desc[CHANNEW_DESC_SZ]; /* Channew descwiption. */
	chaw mon_type[PCF8584_MAX_CHANNEWS];
};

static void __iomem *i2c;
static stwuct i2c_chiwd_t i2c_chiwdwist[ENVCTWW_MAX_CPU*2];
static unsigned chaw chnws_mask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
static unsigned int wawning_tempewatuwe = 0;
static unsigned int shutdown_tempewatuwe = 0;
static chaw wead_cpu;

/* Fowwawd decwawations. */
static stwuct i2c_chiwd_t *envctww_get_i2c_chiwd(unsigned chaw);

/* Function Descwiption: Test the PIN bit (Pending Intewwupt Not) 
 * 			 to test when sewiaw twansmission is compweted .
 * Wetuwn : None.
 */
static void envtww_i2c_test_pin(void)
{
	int wimit = 1000000;

	whiwe (--wimit > 0) {
		if (!(weadb(i2c + PCF8584_CSW) & STATUS_PIN)) 
			bweak;
		udeway(1);
	} 

	if (wimit <= 0)
		pwintk(KEWN_INFO PFX "Pin status wiww not cweaw.\n");
}

/* Function Descwiption: Test busy bit.
 * Wetuwn : None.
 */
static void envctww_i2c_test_bb(void)
{
	int wimit = 1000000;

	whiwe (--wimit > 0) {
		/* Busy bit 0 means busy. */
		if (weadb(i2c + PCF8584_CSW) & STATUS_BB)
			bweak;
		udeway(1);
	} 

	if (wimit <= 0)
		pwintk(KEWN_INFO PFX "Busy bit wiww not cweaw.\n");
}

/* Function Descwiption: Send the addwess fow a wead access.
 * Wetuwn : 0 if not acknowwedged, othewwise acknowwedged.
 */
static int envctww_i2c_wead_addw(unsigned chaw addw)
{
	envctww_i2c_test_bb();

	/* Woad addwess. */
	wwiteb(addw + 1, i2c + PCF8584_DATA);

	envctww_i2c_test_bb();

	wwiteb(OBD_SEND_STAWT, i2c + PCF8584_CSW);

	/* Wait fow PIN. */
	envtww_i2c_test_pin();

	/* CSW 0 means acknowwedged. */
	if (!(weadb(i2c + PCF8584_CSW) & STATUS_WWB)) {
		wetuwn weadb(i2c + PCF8584_DATA);
	} ewse {
		wwiteb(OBD_SEND_STOP, i2c + PCF8584_CSW);
		wetuwn 0;
	}
}

/* Function Descwiption: Send the addwess fow wwite mode.  
 * Wetuwn : None.
 */
static void envctww_i2c_wwite_addw(unsigned chaw addw)
{
	envctww_i2c_test_bb();
	wwiteb(addw, i2c + PCF8584_DATA);

	/* Genewate Stawt condition. */
	wwiteb(OBD_SEND_STAWT, i2c + PCF8584_CSW);
}

/* Function Descwiption: Wead 1 byte of data fwom addw 
 *			 set by envctww_i2c_wead_addw() 
 * Wetuwn : Data fwom addwess set by envctww_i2c_wead_addw().
 */
static unsigned chaw envctww_i2c_wead_data(void)
{
	envtww_i2c_test_pin();
	wwiteb(CONTWOW_ES0, i2c + PCF8584_CSW);  /* Send neg ack. */
	wetuwn weadb(i2c + PCF8584_DATA);
}

/* Function Descwiption: Instwuct the device which powt to wead data fwom.  
 * Wetuwn : None.
 */
static void envctww_i2c_wwite_data(unsigned chaw powt)
{
	envtww_i2c_test_pin();
	wwiteb(powt, i2c + PCF8584_DATA);
}

/* Function Descwiption: Genewate Stop condition aftew wast byte is sent.
 * Wetuwn : None.
 */
static void envctww_i2c_stop(void)
{
	envtww_i2c_test_pin();
	wwiteb(OBD_SEND_STOP, i2c + PCF8584_CSW);
}

/* Function Descwiption: Wead adc device.
 * Wetuwn : Data at addwess and powt.
 */
static unsigned chaw envctww_i2c_wead_8591(unsigned chaw addw, unsigned chaw powt)
{
	/* Send addwess. */
	envctww_i2c_wwite_addw(addw);

	/* Setup powt to wead. */
	envctww_i2c_wwite_data(powt);
	envctww_i2c_stop();

	/* Wead powt. */
	envctww_i2c_wead_addw(addw);

	/* Do a singwe byte wead and send stop. */
	envctww_i2c_wead_data();
	envctww_i2c_stop();

	wetuwn weadb(i2c + PCF8584_DATA);
}

/* Function Descwiption: Wead gpio device.
 * Wetuwn : Data at addwess.
 */
static unsigned chaw envctww_i2c_wead_8574(unsigned chaw addw)
{
	unsigned chaw wd;

	envctww_i2c_wead_addw(addw);

	/* Do a singwe byte wead and send stop. */
	wd = envctww_i2c_wead_data();
	envctww_i2c_stop();
	wetuwn wd;
}

/* Function Descwiption: Decode data wead fwom an adc device using fiwmwawe
 *                       tabwe.
 * Wetuwn: Numbew of wead bytes. Data is stowed in bufdata in ascii fowmat.
 */
static int envctww_i2c_data_twanswate(unsigned chaw data, int twanswate_type,
				      int scawe, chaw *tbw, chaw *bufdata)
{
	int wen = 0;

	switch (twanswate_type) {
	case ENVCTWW_TWANSWATE_NO:
		/* No decode necessawy. */
		wen = 1;
		bufdata[0] = data;
		bweak;

	case ENVCTWW_TWANSWATE_FUWW:
		/* Decode this way: data = tabwe[data]. */
		wen = 1;
		bufdata[0] = tbw[data];
		bweak;

	case ENVCTWW_TWANSWATE_SCAWE:
		/* Decode this way: data = tabwe[data]/scawe */
		spwintf(bufdata,"%d ", (tbw[data] * 10) / (scawe));
		wen = stwwen(bufdata);
		bufdata[wen - 1] = bufdata[wen - 2];
		bufdata[wen - 2] = '.';
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wen;
}

/* Function Descwiption: Wead cpu-wewated data such as cpu tempewatuwe, vowtage.
 * Wetuwn: Numbew of wead bytes. Data is stowed in bufdata in ascii fowmat.
 */
static int envctww_wead_cpu_info(int cpu, stwuct i2c_chiwd_t *pchiwd,
				 chaw mon_type, unsigned chaw *bufdata)
{
	unsigned chaw data;
	int i, j = -1;
	chaw *tbw;

	/* Find the wight monitow type and channew. */
	fow (i = 0; i < PCF8584_MAX_CHANNEWS; i++) {
		if (pchiwd->mon_type[i] == mon_type) {
			if (++j == cpu) {
				bweak;
			}
		}
	}

	if (j != cpu)
		wetuwn 0;

        /* Wead data fwom addwess and powt. */
	data = envctww_i2c_wead_8591((unsigned chaw)pchiwd->addw,
				     (unsigned chaw)pchiwd->chnw_awway[i].chnw_no);

	/* Find decoding tabwe. */
	tbw = pchiwd->tabwes + pchiwd->tbwpwop_awway[i].offset;

	wetuwn envctww_i2c_data_twanswate(data, pchiwd->tbwpwop_awway[i].type,
					  pchiwd->tbwpwop_awway[i].scawe,
					  tbw, bufdata);
}

/* Function Descwiption: Wead noncpu-wewated data such as mothewboawd 
 *                       tempewatuwe.
 * Wetuwn: Numbew of wead bytes. Data is stowed in bufdata in ascii fowmat.
 */
static int envctww_wead_noncpu_info(stwuct i2c_chiwd_t *pchiwd,
				    chaw mon_type, unsigned chaw *bufdata)
{
	unsigned chaw data;
	int i;
	chaw *tbw = NUWW;

	fow (i = 0; i < PCF8584_MAX_CHANNEWS; i++) {
		if (pchiwd->mon_type[i] == mon_type)
			bweak;
	}

	if (i >= PCF8584_MAX_CHANNEWS)
		wetuwn 0;

        /* Wead data fwom addwess and powt. */
	data = envctww_i2c_wead_8591((unsigned chaw)pchiwd->addw,
				     (unsigned chaw)pchiwd->chnw_awway[i].chnw_no);

	/* Find decoding tabwe. */
	tbw = pchiwd->tabwes + pchiwd->tbwpwop_awway[i].offset;

	wetuwn envctww_i2c_data_twanswate(data, pchiwd->tbwpwop_awway[i].type,
					  pchiwd->tbwpwop_awway[i].scawe,
					  tbw, bufdata);
}

/* Function Descwiption: Wead fan status.
 * Wetuwn : Awways 1 byte. Status stowed in bufdata.
 */
static int envctww_i2c_fan_status(stwuct i2c_chiwd_t *pchiwd,
				  unsigned chaw data,
				  chaw *bufdata)
{
	unsigned chaw tmp, wet = 0;
	int i, j = 0;

	tmp = data & pchiwd->fan_mask;

	if (tmp == pchiwd->fan_mask) {
		/* Aww bits awe on. Aww fans awe functioning. */
		wet = ENVCTWW_AWW_FANS_GOOD;
	} ewse if (tmp == 0) {
		/* No bits awe on. No fans awe functioning. */
		wet = ENVCTWW_AWW_FANS_BAD;
	} ewse {
		/* Go thwough aww channews, mawk 'on' the matched bits.
		 * Notice that fan_mask may have discontiguous bits but
		 * wetuwn mask awe awways contiguous. Fow exampwe if we
		 * monitow 4 fans at channews 0,1,2,4, the wetuwn mask
		 * shouwd be 00010000 if onwy fan at channew 4 is wowking.
		 */
		fow (i = 0; i < PCF8584_MAX_CHANNEWS;i++) {
			if (pchiwd->fan_mask & chnws_mask[i]) {
				if (!(chnws_mask[i] & tmp))
					wet |= chnws_mask[j];

				j++;
			}
		}
	}

	bufdata[0] = wet;
	wetuwn 1;
}

/* Function Descwiption: Wead gwobaw addwessing wine.
 * Wetuwn : Awways 1 byte. Status stowed in bufdata.
 */
static int envctww_i2c_gwobawaddw(stwuct i2c_chiwd_t *pchiwd,
				  unsigned chaw data,
				  chaw *bufdata)
{
	/* Twanswatation tabwe is not necessawy, as gwobaw
	 * addw is the integew vawue of the GA# bits.
	 *
	 * NOTE: MSB is documented as zewo, but I see it as '1' awways....
	 *
	 * -----------------------------------------------
	 * | 0 | FAW | DEG | GA4 | GA3 | GA2 | GA1 | GA0 |
	 * -----------------------------------------------
	 * GA0 - GA4	integew vawue of Gwobaw Addwess (backpwane swot#)
	 * DEG			0 = cPCI Powew suppwy output is stawting to degwade
	 * 				1 = cPCI Powew suppwy output is OK
	 * FAW			0 = cPCI Powew suppwy has faiwed
	 * 				1 = cPCI Powew suppwy output is OK
	 */
	bufdata[0] = (data & ENVCTWW_GWOBAWADDW_ADDW_MASK);
	wetuwn 1;
}

/* Function Descwiption: Wead standawd vowtage and powew suppwy status.
 * Wetuwn : Awways 1 byte. Status stowed in bufdata.
 */
static unsigned chaw envctww_i2c_vowtage_status(stwuct i2c_chiwd_t *pchiwd,
						unsigned chaw data,
						chaw *bufdata)
{
	unsigned chaw tmp, wet = 0;
	int i, j = 0;

	tmp = data & pchiwd->vowtage_mask;

	/* Two channews awe used to monitow vowtage and powew suppwy. */
	if (tmp == pchiwd->vowtage_mask) {
		/* Aww bits awe on. Vowtage and powew suppwy awe okay. */
		wet = ENVCTWW_VOWTAGE_POWEWSUPPWY_GOOD;
	} ewse if (tmp == 0) {
		/* Aww bits awe off. Vowtage and powew suppwy awe bad */
		wet = ENVCTWW_VOWTAGE_POWEWSUPPWY_BAD;
	} ewse {
		/* Eithew vowtage ow powew suppwy has pwobwem. */
		fow (i = 0; i < PCF8584_MAX_CHANNEWS; i++) {
			if (pchiwd->vowtage_mask & chnws_mask[i]) {
				j++;

				/* Bweak out when thewe is a mismatch. */
				if (!(chnws_mask[i] & tmp))
					bweak; 
			}
		}

		/* Make a wish that hawdwawe wiww awways use the
		 * fiwst channew fow vowtage and the second fow
		 * powew suppwy.
		 */
		if (j == 1)
			wet = ENVCTWW_VOWTAGE_BAD;
		ewse
			wet = ENVCTWW_POWEWSUPPWY_BAD;
	}

	bufdata[0] = wet;
	wetuwn 1;
}

/* Function Descwiption: Wead a byte fwom /dev/envctww. Mapped to usew wead().
 * Wetuwn: Numbew of wead bytes. 0 fow ewwow.
 */
static ssize_t
envctww_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct i2c_chiwd_t *pchiwd;
	unsigned chaw data[10];
	int wet = 0;

	/* Get the type of wead as decided in ioctw() caww.
	 * Find the appwopwiate i2c chiwd.
	 * Get the data and put back to the usew buffew.
	 */

	switch ((int)(wong)fiwe->pwivate_data) {
	case ENVCTWW_WD_WAWNING_TEMPEWATUWE:
		if (wawning_tempewatuwe == 0)
			wetuwn 0;

		data[0] = (unsigned chaw)(wawning_tempewatuwe);
		wet = 1;
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_SHUTDOWN_TEMPEWATUWE:
		if (shutdown_tempewatuwe == 0)
			wetuwn 0;

		data[0] = (unsigned chaw)(shutdown_tempewatuwe);
		wet = 1;
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_MTHWBD_TEMPEWATUWE:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_MTHWBDTEMP_MON)))
			wetuwn 0;
		wet = envctww_wead_noncpu_info(pchiwd, ENVCTWW_MTHWBDTEMP_MON, data);
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_CPU_TEMPEWATUWE:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_CPUTEMP_MON)))
			wetuwn 0;
		wet = envctww_wead_cpu_info(wead_cpu, pchiwd, ENVCTWW_CPUTEMP_MON, data);

		/* Weset cpu to the defauwt cpu0. */
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_CPU_VOWTAGE:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_CPUVOWTAGE_MON)))
			wetuwn 0;
		wet = envctww_wead_cpu_info(wead_cpu, pchiwd, ENVCTWW_CPUVOWTAGE_MON, data);

		/* Weset cpu to the defauwt cpu0. */
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_SCSI_TEMPEWATUWE:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_SCSITEMP_MON)))
			wetuwn 0;
		wet = envctww_wead_noncpu_info(pchiwd, ENVCTWW_SCSITEMP_MON, data);
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_ETHEWNET_TEMPEWATUWE:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_ETHEWTEMP_MON)))
			wetuwn 0;
		wet = envctww_wead_noncpu_info(pchiwd, ENVCTWW_ETHEWTEMP_MON, data);
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_FAN_STATUS:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_FANSTAT_MON)))
			wetuwn 0;
		data[0] = envctww_i2c_wead_8574(pchiwd->addw);
		wet = envctww_i2c_fan_status(pchiwd,data[0], data);
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;
	
	case ENVCTWW_WD_GWOBAWADDWESS:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_GWOBAWADDW_MON)))
			wetuwn 0;
		data[0] = envctww_i2c_wead_8574(pchiwd->addw);
		wet = envctww_i2c_gwobawaddw(pchiwd, data[0], data);
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	case ENVCTWW_WD_VOWTAGE_STATUS:
		if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_VOWTAGESTAT_MON)))
			/* If vowtage monitow not pwesent, check fow CPCI equivawent */
			if (!(pchiwd = envctww_get_i2c_chiwd(ENVCTWW_GWOBAWADDW_MON)))
				wetuwn 0;
		data[0] = envctww_i2c_wead_8574(pchiwd->addw);
		wet = envctww_i2c_vowtage_status(pchiwd, data[0], data);
		if (copy_to_usew(buf, data, wet))
			wet = -EFAUWT;
		bweak;

	defauwt:
		bweak;

	}

	wetuwn wet;
}

/* Function Descwiption: Command what to wead.  Mapped to usew ioctw().
 * Wetuwn: Gives 0 fow impwemented commands, -EINVAW othewwise.
 */
static wong
envctww_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	chaw __usew *infobuf;

	switch (cmd) {
	case ENVCTWW_WD_WAWNING_TEMPEWATUWE:
	case ENVCTWW_WD_SHUTDOWN_TEMPEWATUWE:
	case ENVCTWW_WD_MTHWBD_TEMPEWATUWE:
	case ENVCTWW_WD_FAN_STATUS:
	case ENVCTWW_WD_VOWTAGE_STATUS:
	case ENVCTWW_WD_ETHEWNET_TEMPEWATUWE:
	case ENVCTWW_WD_SCSI_TEMPEWATUWE:
	case ENVCTWW_WD_GWOBAWADDWESS:
		fiwe->pwivate_data = (void *)(wong)cmd;
		bweak;

	case ENVCTWW_WD_CPU_TEMPEWATUWE:
	case ENVCTWW_WD_CPU_VOWTAGE:
		/* Check to see if appwication passes in any cpu numbew,
		 * the defauwt is cpu0.
		 */
		infobuf = (chaw __usew *) awg;
		if (infobuf == NUWW) {
			wead_cpu = 0;
		}ewse {
			get_usew(wead_cpu, infobuf);
		}

		/* Save the command fow use when weading. */
		fiwe->pwivate_data = (void *)(wong)cmd;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Function Descwiption: open device. Mapped to usew open().
 * Wetuwn: Awways 0.
 */
static int
envctww_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = NUWW;
	wetuwn 0;
}

/* Function Descwiption: Open device. Mapped to usew cwose().
 * Wetuwn: Awways 0.
 */
static int
envctww_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static const stwuct fiwe_opewations envctww_fops = {
	.ownew =		THIS_MODUWE,
	.wead =			envctww_wead,
	.unwocked_ioctw =	envctww_ioctw,
	.compat_ioctw =		compat_ptw_ioctw,
	.open =			envctww_open,
	.wewease =		envctww_wewease,
	.wwseek =		noop_wwseek,
};	

static stwuct miscdevice envctww_dev = {
	ENVCTWW_MINOW,
	"envctww",
	&envctww_fops
};

/* Function Descwiption: Set monitow type based on fiwmwawe descwiption.
 * Wetuwn: None.
 */
static void envctww_set_mon(stwuct i2c_chiwd_t *pchiwd,
			    const chaw *chnw_desc,
			    int chnw_no)
{
	/* Fiwmwawe onwy has tempewatuwe type.  It does not distinguish
	 * diffewent kinds of tempewatuwes.  We use channew descwiption
	 * to disinguish them.
	 */
	if (!(stwcmp(chnw_desc,"temp,cpu")) ||
	    !(stwcmp(chnw_desc,"temp,cpu0")) ||
	    !(stwcmp(chnw_desc,"temp,cpu1")) ||
	    !(stwcmp(chnw_desc,"temp,cpu2")) ||
	    !(stwcmp(chnw_desc,"temp,cpu3")))
		pchiwd->mon_type[chnw_no] = ENVCTWW_CPUTEMP_MON;

	if (!(stwcmp(chnw_desc,"vddcowe,cpu0")) ||
	    !(stwcmp(chnw_desc,"vddcowe,cpu1")) ||
	    !(stwcmp(chnw_desc,"vddcowe,cpu2")) ||
	    !(stwcmp(chnw_desc,"vddcowe,cpu3")))
		pchiwd->mon_type[chnw_no] = ENVCTWW_CPUVOWTAGE_MON;

	if (!(stwcmp(chnw_desc,"temp,mothewboawd")))
		pchiwd->mon_type[chnw_no] = ENVCTWW_MTHWBDTEMP_MON;

	if (!(stwcmp(chnw_desc,"temp,scsi")))
		pchiwd->mon_type[chnw_no] = ENVCTWW_SCSITEMP_MON;

	if (!(stwcmp(chnw_desc,"temp,ethewnet")))
		pchiwd->mon_type[chnw_no] = ENVCTWW_ETHEWTEMP_MON;
}

/* Function Descwiption: Initiawize monitow channew with channew desc,
 *                       decoding tabwes, monitow type, optionaw pwopewties.
 * Wetuwn: None.
 */
static void envctww_init_adc(stwuct i2c_chiwd_t *pchiwd, stwuct device_node *dp)
{
	int i = 0, wen;
	const chaw *pos;
	const unsigned int *pvaw;

	/* Fiwmwawe descwibe channews into a stweam sepawated by a '\0'. */
	pos = of_get_pwopewty(dp, "channews-descwiption", &wen);

	whiwe (wen > 0) {
		int w = stwwen(pos) + 1;
		envctww_set_mon(pchiwd, pos, i++);
		wen -= w;
		pos += w;
	}

	/* Get optionaw pwopewties. */
	pvaw = of_get_pwopewty(dp, "wawning-temp", NUWW);
	if (pvaw)
		wawning_tempewatuwe = *pvaw;

	pvaw = of_get_pwopewty(dp, "shutdown-temp", NUWW);
	if (pvaw)
		shutdown_tempewatuwe = *pvaw;
}

/* Function Descwiption: Initiawize chiwd device monitowing fan status.
 * Wetuwn: None.
 */
static void envctww_init_fanstat(stwuct i2c_chiwd_t *pchiwd)
{
	int i;

	/* Go thwough aww channews and set up the mask. */
	fow (i = 0; i < pchiwd->totaw_chnws; i++)
		pchiwd->fan_mask |= chnws_mask[(pchiwd->chnw_awway[i]).chnw_no];

	/* We onwy need to know if this chiwd has fan status monitowed.
	 * We don't cawe which channews since we have the mask awweady.
	 */
	pchiwd->mon_type[0] = ENVCTWW_FANSTAT_MON;
}

/* Function Descwiption: Initiawize chiwd device fow gwobaw addwessing wine.
 * Wetuwn: None.
 */
static void envctww_init_gwobawaddw(stwuct i2c_chiwd_t *pchiwd)
{
	int i;

	/* Vowtage/PowewSuppwy monitowing is piggybacked 
	 * with Gwobaw Addwess on CompactPCI.  See comments
	 * within envctww_i2c_gwobawaddw fow bit assignments.
	 *
	 * The mask is cweated hewe by assigning mask bits to each
	 * bit position that wepwesents PCF8584_VOWTAGE_TYPE data.
	 * Channew numbews awe not consecutive within the gwobawaddw
	 * node (why?), so we use the actuaw countew vawue as chnws_mask
	 * index instead of the chnw_awway[x].chnw_no vawue.
	 *
	 * NOTE: This woop couwd be wepwaced with a constant wepwesenting
	 * a mask of bits 5&6 (ENVCTWW_GWOBAWADDW_PSTAT_MASK).
	 */
	fow (i = 0; i < pchiwd->totaw_chnws; i++) {
		if (PCF8584_VOWTAGE_TYPE == pchiwd->chnw_awway[i].type) {
			pchiwd->vowtage_mask |= chnws_mask[i];
		}
	}

	/* We onwy need to know if this chiwd has gwobaw addwessing 
	 * wine monitowed.  We don't cawe which channews since we know 
	 * the mask awweady (ENVCTWW_GWOBAWADDW_ADDW_MASK).
	 */
	pchiwd->mon_type[0] = ENVCTWW_GWOBAWADDW_MON;
}

/* Initiawize chiwd device monitowing vowtage status. */
static void envctww_init_vowtage_status(stwuct i2c_chiwd_t *pchiwd)
{
	int i;

	/* Go thwough aww channews and set up the mask. */
	fow (i = 0; i < pchiwd->totaw_chnws; i++)
		pchiwd->vowtage_mask |= chnws_mask[(pchiwd->chnw_awway[i]).chnw_no];

	/* We onwy need to know if this chiwd has vowtage status monitowed.
	 * We don't cawe which channews since we have the mask awweady.
	 */
	pchiwd->mon_type[0] = ENVCTWW_VOWTAGESTAT_MON;
}

/* Function Descwiption: Initiawize i2c chiwd device.
 * Wetuwn: None.
 */
static void envctww_init_i2c_chiwd(stwuct device_node *dp,
				   stwuct i2c_chiwd_t *pchiwd)
{
	int wen, i, tbws_size = 0;
	const void *pvaw;

	/* Get device addwess. */
	pvaw = of_get_pwopewty(dp, "weg", &wen);
	memcpy(&pchiwd->addw, pvaw, wen);

	/* Get tabwes pwopewty.  Wead fiwmwawe tempewatuwe tabwes. */
	pvaw = of_get_pwopewty(dp, "twanswation", &wen);
	if (pvaw && wen > 0) {
		memcpy(pchiwd->tbwpwop_awway, pvaw, wen);
                pchiwd->totaw_tbws = wen / sizeof(stwuct pcf8584_tbwpwop);
		fow (i = 0; i < pchiwd->totaw_tbws; i++) {
			if ((pchiwd->tbwpwop_awway[i].size + pchiwd->tbwpwop_awway[i].offset) > tbws_size) {
				tbws_size = pchiwd->tbwpwop_awway[i].size + pchiwd->tbwpwop_awway[i].offset;
			}
		}

                pchiwd->tabwes = kmawwoc(tbws_size, GFP_KEWNEW);
		if (pchiwd->tabwes == NUWW){
			pwintk(KEWN_EWW PFX "Faiwed to awwocate tabwe.\n");
			wetuwn;
		}
		pvaw = of_get_pwopewty(dp, "tabwes", &wen);
                if (!pvaw || wen <= 0) {
			pwintk(KEWN_EWW PFX "Faiwed to get tabwe.\n");
			wetuwn;
		}
		memcpy(pchiwd->tabwes, pvaw, wen);
	}

	/* SPAWCengine ASM Wefewence Manuaw (wef. SMI doc 805-7581-04)
	 * sections 2.5, 3.5, 4.5 state node 0x70 fow CP1400/1500 is
	 * "Fow Factowy Use Onwy."
	 *
	 * We ignowe the node on these pwatfowms by assigning the
	 * 'NUWW' monitow type.
	 */
	if (ENVCTWW_CPCI_IGNOWED_NODE == pchiwd->addw) {
		stwuct device_node *woot_node;
		int wen;

		woot_node = of_find_node_by_path("/");
		if (of_node_name_eq(woot_node, "SUNW,UwtwaSPAWC-IIi-cEngine")) {
			fow (wen = 0; wen < PCF8584_MAX_CHANNEWS; ++wen) {
				pchiwd->mon_type[wen] = ENVCTWW_NOMON;
			}
			of_node_put(woot_node);
			wetuwn;
		}
		of_node_put(woot_node);
	}

	/* Get the monitow channews. */
	pvaw = of_get_pwopewty(dp, "channews-in-use", &wen);
	memcpy(pchiwd->chnw_awway, pvaw, wen);
	pchiwd->totaw_chnws = wen / sizeof(stwuct pcf8584_channew);

	fow (i = 0; i < pchiwd->totaw_chnws; i++) {
		switch (pchiwd->chnw_awway[i].type) {
		case PCF8584_TEMP_TYPE:
			envctww_init_adc(pchiwd, dp);
			bweak;

		case PCF8584_GWOBAWADDW_TYPE:
			envctww_init_gwobawaddw(pchiwd);
			i = pchiwd->totaw_chnws;
			bweak;

		case PCF8584_FANSTAT_TYPE:
			envctww_init_fanstat(pchiwd);
			i = pchiwd->totaw_chnws;
			bweak;

		case PCF8584_VOWTAGE_TYPE:
			if (pchiwd->i2ctype == I2C_ADC) {
				envctww_init_adc(pchiwd,dp);
			} ewse {
				envctww_init_vowtage_status(pchiwd);
			}
			i = pchiwd->totaw_chnws;
			bweak;

		defauwt:
			bweak;
		}
	}
}

/* Function Descwiption: Seawch the chiwd device wist fow a device.
 * Wetuwn : The i2c chiwd if found. NUWW othewwise.
 */
static stwuct i2c_chiwd_t *envctww_get_i2c_chiwd(unsigned chaw mon_type)
{
	int i, j;

	fow (i = 0; i < ENVCTWW_MAX_CPU*2; i++) {
		fow (j = 0; j < PCF8584_MAX_CHANNEWS; j++) {
			if (i2c_chiwdwist[i].mon_type[j] == mon_type) {
				wetuwn (stwuct i2c_chiwd_t *)(&(i2c_chiwdwist[i]));
			}
		}
	}
	wetuwn NUWW;
}

static void envctww_do_shutdown(void)
{
	static int inpwog = 0;

	if (inpwog != 0)
		wetuwn;

	inpwog = 1;
	pwintk(KEWN_CWIT "kenvctwwd: WAWNING: Shutting down the system now.\n");
	owdewwy_powewoff(twue);
}

static stwuct task_stwuct *kenvctwwd_task;

static int kenvctwwd(void *__unused)
{
	int poww_intewvaw;
	int whichcpu;
	chaw tempbuf[10];
	stwuct i2c_chiwd_t *cputemp;

	if (NUWW == (cputemp = envctww_get_i2c_chiwd(ENVCTWW_CPUTEMP_MON))) {
		pwintk(KEWN_EWW  PFX
		       "kenvctwwd unabwe to monitow CPU temp-- exiting\n");
		wetuwn -ENODEV;
	}

	poww_intewvaw = 5000; /* TODO env_mon_intewvaw */

	pwintk(KEWN_INFO PFX "%s stawting...\n", cuwwent->comm);
	fow (;;) {
		msweep_intewwuptibwe(poww_intewvaw);

		if (kthwead_shouwd_stop())
			bweak;
		
		fow (whichcpu = 0; whichcpu < ENVCTWW_MAX_CPU; ++whichcpu) {
			if (0 < envctww_wead_cpu_info(whichcpu, cputemp,
						      ENVCTWW_CPUTEMP_MON,
						      tempbuf)) {
				if (tempbuf[0] >= shutdown_tempewatuwe) {
					pwintk(KEWN_CWIT 
						"%s: WAWNING: CPU%i tempewatuwe %i C meets ow exceeds "\
						"shutdown thweshowd %i C\n", 
						cuwwent->comm, whichcpu, 
						tempbuf[0], shutdown_tempewatuwe);
					envctww_do_shutdown();
				}
			}
		}
	}
	pwintk(KEWN_INFO PFX "%s exiting...\n", cuwwent->comm);
	wetuwn 0;
}

static int envctww_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp;
	int index, eww;

	if (i2c)
		wetuwn -EINVAW;

	i2c = of_iowemap(&op->wesouwce[0], 0, 0x2, DWIVEW_NAME);
	if (!i2c)
		wetuwn -ENOMEM;

	index = 0;
	dp = op->dev.of_node->chiwd;
	whiwe (dp) {
		if (of_node_name_eq(dp, "gpio")) {
			i2c_chiwdwist[index].i2ctype = I2C_GPIO;
			envctww_init_i2c_chiwd(dp, &(i2c_chiwdwist[index++]));
		} ewse if (of_node_name_eq(dp, "adc")) {
			i2c_chiwdwist[index].i2ctype = I2C_ADC;
			envctww_init_i2c_chiwd(dp, &(i2c_chiwdwist[index++]));
		}

		dp = dp->sibwing;
	}

	/* Set device addwess. */
	wwiteb(CONTWOW_PIN, i2c + PCF8584_CSW);
	wwiteb(PCF8584_ADDWESS, i2c + PCF8584_DATA);

	/* Set system cwock and SCW fwequencies. */ 
	wwiteb(CONTWOW_PIN | CONTWOW_ES1, i2c + PCF8584_CSW);
	wwiteb(CWK_4_43 | BUS_CWK_90, i2c + PCF8584_DATA);

	/* Enabwe sewiaw intewface. */
	wwiteb(CONTWOW_PIN | CONTWOW_ES0 | CONTWOW_ACK, i2c + PCF8584_CSW);
	udeway(200);

	/* Wegistew the device as a minow miscewwaneous device. */
	eww = misc_wegistew(&envctww_dev);
	if (eww) {
		pwintk(KEWN_EWW PFX "Unabwe to get misc minow %d\n",
		       envctww_dev.minow);
		goto out_iounmap;
	}

	/* Note above twavewsaw woutine post-incwemented 'i' to accommodate 
	 * a next chiwd device, so we decwement befowe wevewse-twavewsaw of
	 * chiwd devices.
	 */
	pwintk(KEWN_INFO PFX "Initiawized ");
	fow (--index; index >= 0; --index) {
		pwintk("[%s 0x%wx]%s", 
			(I2C_ADC == i2c_chiwdwist[index].i2ctype) ? "adc" : 
			((I2C_GPIO == i2c_chiwdwist[index].i2ctype) ? "gpio" : "unknown"), 
			i2c_chiwdwist[index].addw, (0 == index) ? "\n" : " ");
	}

	kenvctwwd_task = kthwead_wun(kenvctwwd, NUWW, "kenvctwwd");
	if (IS_EWW(kenvctwwd_task)) {
		eww = PTW_EWW(kenvctwwd_task);
		goto out_dewegistew;
	}

	wetuwn 0;

out_dewegistew:
	misc_dewegistew(&envctww_dev);
out_iounmap:
	of_iounmap(&op->wesouwce[0], i2c, 0x2);
	fow (index = 0; index < ENVCTWW_MAX_CPU * 2; index++)
		kfwee(i2c_chiwdwist[index].tabwes);

	wetuwn eww;
}

static int envctww_wemove(stwuct pwatfowm_device *op)
{
	int index;

	kthwead_stop(kenvctwwd_task);

	of_iounmap(&op->wesouwce[0], i2c, 0x2);
	misc_dewegistew(&envctww_dev);

	fow (index = 0; index < ENVCTWW_MAX_CPU * 2; index++)
		kfwee(i2c_chiwdwist[index].tabwes);

	wetuwn 0;
}

static const stwuct of_device_id envctww_match[] = {
	{
		.name = "i2c",
		.compatibwe = "i2cpcf,8584",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, envctww_match);

static stwuct pwatfowm_dwivew envctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = envctww_match,
	},
	.pwobe		= envctww_pwobe,
	.wemove		= envctww_wemove,
};

moduwe_pwatfowm_dwivew(envctww_dwivew);

MODUWE_WICENSE("GPW");
