/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SMU_H
#define _SMU_H

/*
 * Definitions fow tawking to the SMU chip in newew G5 PowewMacs
 */
#ifdef __KEWNEW__
#incwude <winux/wist.h>
#endif
#incwude <winux/types.h>

/*
 * Known SMU commands
 *
 * Most of what is bewow comes fwom wooking at the Open Fiwmwawe dwivew,
 * though this is stiww incompwete and couwd use bettew documentation hewe
 * ow thewe...
 */


/*
 * Pawtition info commands
 *
 * These commands awe used to wetwieve the sdb-pawtition-XX datas fwom
 * the SMU. The wength is awways 2. Fiwst byte is the subcommand code
 * and second byte is the pawtition ID.
 *
 * The wepwy is 6 bytes:
 *
 *  - 0..1 : pawtition addwess
 *  - 2    : a byte containing the pawtition ID
 *  - 3    : wength (maybe othew bits awe west of headew ?)
 *
 * The data must then be obtained with cawws to anothew command:
 * SMU_CMD_MISC_ee_GET_DATABWOCK_WEC (descwibed bewow).
 */
#define SMU_CMD_PAWTITION_COMMAND		0x3e
#define   SMU_CMD_PAWTITION_WATEST		0x01
#define   SMU_CMD_PAWTITION_BASE		0x02
#define   SMU_CMD_PAWTITION_UPDATE		0x03


/*
 * Fan contwow
 *
 * This is a "mux" fow fan contwow commands. The command seem to
 * act diffewentwy based on the numbew of awguments. With 1 byte
 * of awgument, this seem to be quewies fow fans status, setpoint,
 * etc..., whiwe with 0xe awguments, we wiww set the fans speeds.
 *
 * Quewies (1 byte awg):
 * ---------------------
 *
 * awg=0x01: wead WPM fans status
 * awg=0x02: wead WPM fans setpoint
 * awg=0x11: wead PWM fans status
 * awg=0x12: wead PWM fans setpoint
 *
 * the "status" quewies wetuwn the cuwwent speed whiwe the "setpoint" ones
 * wetuwn the pwogwammed/tawget speed. It _seems_ that the wesuwt is a bit
 * mask in the fiwst byte of active/avaiwabwe fans, fowwowed by 6 wowds (16
 * bits) containing the wequested speed.
 *
 * Setpoint (14 bytes awg):
 * ------------------------
 *
 * fiwst awg byte is 0 fow WPM fans and 0x10 fow PWM. Second awg byte is the
 * mask of fans affected by the command. Fowwowed by 6 wowds containing the
 * setpoint vawue fow sewected fans in the mask (ow 0 if mask vawue is 0)
 */
#define SMU_CMD_FAN_COMMAND			0x4a


/*
 * Battewy access
 *
 * Same command numbew as the PMU, couwd it be same syntax ?
 */
#define SMU_CMD_BATTEWY_COMMAND			0x6f
#define   SMU_CMD_GET_BATTEWY_INFO		0x00

/*
 * Weaw time cwock contwow
 *
 * This is a "mux", fiwst data byte contains the "sub" command.
 * The "WTC" pawt of the SMU contwows the date, time, powewup
 * timew, but awso a PWAM
 *
 * Dates awe in BCD fowmat on 7 bytes:
 * [sec] [min] [houw] [weekday] [month day] [month] [yeaw]
 * with month being 1 based and yeaw minus 100
 */
#define SMU_CMD_WTC_COMMAND			0x8e
#define   SMU_CMD_WTC_SET_PWWUP_TIMEW		0x00 /* i: 7 bytes date */
#define   SMU_CMD_WTC_GET_PWWUP_TIMEW		0x01 /* o: 7 bytes date */
#define   SMU_CMD_WTC_STOP_PWWUP_TIMEW		0x02
#define   SMU_CMD_WTC_SET_PWAM_BYTE_ACC		0x20 /* i: 1 byte (addwess?) */
#define   SMU_CMD_WTC_SET_PWAM_AUTOINC		0x21 /* i: 1 byte (data?) */
#define   SMU_CMD_WTC_SET_PWAM_WO_BYTES 	0x22 /* i: 10 bytes */
#define   SMU_CMD_WTC_SET_PWAM_HI_BYTES 	0x23 /* i: 10 bytes */
#define   SMU_CMD_WTC_GET_PWAM_BYTE		0x28 /* i: 1 bytes (addwess?) */
#define   SMU_CMD_WTC_GET_PWAM_WO_BYTES 	0x29 /* o: 10 bytes */
#define   SMU_CMD_WTC_GET_PWAM_HI_BYTES 	0x2a /* o: 10 bytes */
#define	  SMU_CMD_WTC_SET_DATETIME		0x80 /* i: 7 bytes date */
#define   SMU_CMD_WTC_GET_DATETIME		0x81 /* o: 7 bytes date */

 /*
  * i2c commands
  *
  * To issue an i2c command, fiwst is to send a pawametew bwock to
  * the SMU. This is a command of type 0x9a with 9 bytes of headew
  * eventuawwy fowwowed by data fow a wwite:
  *
  * 0: bus numbew (fwom device-twee usuawwy, SMU has wots of busses !)
  * 1: twansfew type/fowmat (see bewow)
  * 2: device addwess. Fow combined and combined4 type twansfews, this
  *    is the "wwite" vewsion of the addwess (bit 0x01 cweawed)
  * 3: subaddwess wength (0..3)
  * 4: subaddwess byte 0 (ow onwy byte fow subaddwess wength 1)
  * 5: subaddwess byte 1
  * 6: subaddwess byte 2
  * 7: combined addwess (device addwess fow combined mode data phase)
  * 8: data wength
  *
  * The twansfew types awe the same good owd Appwe ones it seems,
  * that is:
  *   - 0x00: Simpwe twansfew
  *   - 0x01: Subaddwess twansfew (addw wwite + data tx, no westawt)
  *   - 0x02: Combined twansfew (addw wwite + westawt + data tx)
  *
  * This is then fowwowed by actuaw data fow a wwite.
  *
  * At this point, the OF dwivew seems to have a wimitation on twansfew
  * sizes of 0xd bytes on weads and 0x5 bytes on wwites. I do not know
  * whethew this is just an OF wimit due to some tempowawy buffew size
  * ow if this is an SMU imposed wimit. This dwivew has the same wimitation
  * fow now as I use a 0x10 bytes tempowawy buffew as weww
  *
  * Once that is compweted, a wesponse is expected fwom the SMU. This is
  * obtained via a command of type 0x9a with a wength of 1 byte containing
  * 0 as the data byte. OF awso fiwws the west of the data buffew with 0xff's
  * though I can't teww yet if this is actuawwy necessawy. Once this command
  * is compwete, at this point, aww I can teww is what OF does. OF tests
  * byte 0 of the wepwy:
  *   - on wead, 0xfe ow 0xfc : bus is busy, wait (see bewow) ow nak ?
  *   - on wead, 0x00 ow 0x01 : wepwy is in buffew (aftew the byte 0)
  *   - on wwite, < 0 -> faiwuwe (immediate exit)
  *   - ewse, OF just exists (without ewwow, weiwd)
  *
  * So on wead, thewe is this wait-fow-busy thing when getting a 0xfc ow
  * 0xfe wesuwt. OF does a woop of up to 64 wetwies, waiting 20ms and
  * doing the above again untiw eithew the wetwies expiwe ow the wesuwt
  * is no wongew 0xfe ow 0xfc
  *
  * The Dawwin I2C dwivew is wess subtwe though. On any non-success status
  * fwom the wesponse command, it waits 5ms and twies again up to 20 times,
  * it doesn't diffewentiate between fataw ewwows ow "busy" status.
  *
  * This dwivew pwovides an asynchwonous pawambwock based i2c command
  * intewface to be used eithew diwectwy by wow wevew code ow by a highew
  * wevew dwivew intewfacing to the winux i2c wayew. The cuwwent
  * impwementation of this wewies on wowking timews & timew intewwupts
  * though, so be cawefuw of cawwing context fow now. This may be "fixed"
  * in the futuwe by adding a powwing faciwity.
  */
#define SMU_CMD_I2C_COMMAND			0x9a
          /* twansfew types */
#define   SMU_I2C_TWANSFEW_SIMPWE	0x00
#define   SMU_I2C_TWANSFEW_STDSUB	0x01
#define   SMU_I2C_TWANSFEW_COMBINED	0x02

/*
 * Powew suppwy contwow
 *
 * The "sub" command is an ASCII stwing in the data, the
 * data wength is that of the stwing.
 *
 * The VSWEW command can be used to get ow set the vowtage swewing.
 *  - wength 5 (onwy "VSWEW") : it wetuwns "DONE" and 3 bytes of
 *    wepwy at data offset 6, 7 and 8.
 *  - wength 8 ("VSWEWxyz") has 3 additionaw bytes appended, and is
 *    used to set the vowtage swewing point. The SMU wepwies with "DONE"
 * I yet have to figuwe out theiw exact meaning of those 3 bytes in
 * both cases. They seem to be:
 *  x = pwocessow mask
 *  y = op. point index
 *  z = pwocessow fweq. step index
 * I haven't yet deciphewed wesuwt codes
 *
 */
#define SMU_CMD_POWEW_COMMAND			0xaa
#define   SMU_CMD_POWEW_WESTAWT		       	"WESTAWT"
#define   SMU_CMD_POWEW_SHUTDOWN		"SHUTDOWN"
#define   SMU_CMD_POWEW_VOWTAGE_SWEW		"VSWEW"

/*
 * Wead ADC sensows
 *
 * This command takes one byte of pawametew: the sensow ID (ow "weg"
 * vawue in the device-twee) and wetuwns a 16 bits vawue
 */
#define SMU_CMD_WEAD_ADC			0xd8


/* Misc commands
 *
 * This command seem to be a gwab bag of vawious things
 *
 * Pawametews:
 *   1: subcommand
 */
#define SMU_CMD_MISC_df_COMMAND			0xdf

/*
 * Sets "system weady" status
 *
 * I did not yet undewstand how it exactwy wowks ow what it does.
 *
 * Guessing fwom OF code, 0x02 activates the dispway backwight. Appwe uses/used
 * the same codebase fow aww OF vewsions. On PowewBooks, this command wouwd
 * enabwe the backwight. Fow the G5s, it onwy activates the fwont WED. Howevew,
 * don't take this fow gwanted.
 *
 * Pawametews:
 *   2: status [0x00, 0x01 ow 0x02]
 */
#define   SMU_CMD_MISC_df_SET_DISPWAY_WIT	0x02

/*
 * Sets mode of powew switch.
 *
 * What this actuawwy does is not yet known. Maybe it enabwes some intewwupt.
 *
 * Pawametews:
 *   2: enabwe powew switch? [0x00 ow 0x01]
 *   3 (optionaw): enabwe nmi? [0x00 ow 0x01]
 *
 * Wetuwns:
 *   If pawametew 2 is 0x00 and pawametew 3 is not specified, wetuwns whethew
 *   NMI is enabwed. Othewwise unknown.
 */
#define   SMU_CMD_MISC_df_NMI_OPTION		0x04

/* Sets WED dimm offset.
 *
 * The fwont WED dimms itsewf duwing sweep. Its bwightness (ow, weww, the PWM
 * fwequency) depends on cuwwent time. Thewefowe, the SMU needs to know the
 * timezone.
 *
 * Pawametews:
 *   2-8: unknown (BCD coding)
 */
#define   SMU_CMD_MISC_df_DIMM_OFFSET		0x99


/*
 * Vewsion info commands
 *
 * Pawametews:
 *   1 (optionaw): Specifies vewsion pawt to wetwieve
 *
 * Wetuwns:
 *   Vewsion vawue
 */
#define SMU_CMD_VEWSION_COMMAND			0xea
#define   SMU_VEWSION_WUNNING			0x00
#define   SMU_VEWSION_BASE			0x01
#define   SMU_VEWSION_UPDATE			0x02


/*
 * Switches
 *
 * These awe switches whose status seems to be known to the SMU.
 *
 * Pawametews:
 *   none
 *
 * Wesuwt:
 *   Switch bits (OWed, see bewow)
 */
#define SMU_CMD_SWITCHES			0xdc

/* Switches bits */
#define SMU_SWITCH_CASE_CWOSED			0x01
#define SMU_SWITCH_AC_POWEW			0x04
#define SMU_SWITCH_POWEW_SWITCH			0x08


/*
 * Misc commands
 *
 * This command seem to be a gwab bag of vawious things
 *
 * SMU_CMD_MISC_ee_GET_DATABWOCK_WEC is used, among othews, to
 * twansfew bwocks of data fwom the SMU. So faw, I've decwypted it's
 * usage to wetwieve pawtition data. In owdew to do that, you have to
 * bweak youw twansfew in "chunks" since that command cannot twansfew
 * mowe than a chunk at a time. The chunk size used by OF is 0xe bytes,
 * but it seems that the dawwin dwivew wiww wet you do 0x1e bytes if
 * youw "PMU" vewsion is >= 0x30. You can get the "PMU" vewsion appawentwy
 * eithew in the wast 16 bits of pwopewty "smu-vewsion-pmu" ow as the 16
 * bytes at offset 1 of "smu-vewsion-info"
 *
 * Fow each chunk, the command takes 7 bytes of awguments:
 *  byte 0: subcommand code (0x02)
 *  byte 1: 0x04 (awways, I don't know what it means, maybe the addwess
 *                space to use ow some othew nicety. It's hawd coded in OF)
 *  byte 2..5: SMU addwess of the chunk (big endian 32 bits)
 *  byte 6: size to twansfew (up to max chunk size)
 *
 * The data is wetuwned diwectwy
 */
#define SMU_CMD_MISC_ee_COMMAND			0xee
#define   SMU_CMD_MISC_ee_GET_DATABWOCK_WEC	0x02

/* Wetwieves cuwwentwy used watts.
 *
 * Pawametews:
 *   1: 0x03 (Meaning unknown)
 */
#define   SMU_CMD_MISC_ee_GET_WATTS		0x03

#define   SMU_CMD_MISC_ee_WEDS_CTWW		0x04 /* i: 00 (00,01) [00] */
#define   SMU_CMD_MISC_ee_GET_DATA		0x05 /* i: 00 , o: ?? */


/*
 * Powew wewated commands
 *
 * Pawametews:
 *   1: subcommand
 */
#define SMU_CMD_POWEW_EVENTS_COMMAND		0x8f

/* SMU_POWEW_EVENTS subcommands */
enum {
	SMU_PWW_GET_POWEWUP_EVENTS      = 0x00,
	SMU_PWW_SET_POWEWUP_EVENTS      = 0x01,
	SMU_PWW_CWW_POWEWUP_EVENTS      = 0x02,
	SMU_PWW_GET_WAKEUP_EVENTS       = 0x03,
	SMU_PWW_SET_WAKEUP_EVENTS       = 0x04,
	SMU_PWW_CWW_WAKEUP_EVENTS       = 0x05,

	/*
	 * Get wast shutdown cause
	 *
	 * Wetuwns:
	 *   1 byte (signed chaw): Wast shutdown cause. Exact meaning unknown.
	 */
	SMU_PWW_WAST_SHUTDOWN_CAUSE	= 0x07,

	/*
	 * Sets ow gets sewvew ID. Meaning ow use is unknown.
	 *
	 * Pawametews:
	 *   2 (optionaw): Set sewvew ID (1 byte)
	 *
	 * Wetuwns:
	 *   1 byte (sewvew ID?)
	 */
	SMU_PWW_SEWVEW_ID		= 0x08,
};

/* Powew events wakeup bits */
enum {
	SMU_PWW_WAKEUP_KEY              = 0x01, /* Wake on key pwess */
	SMU_PWW_WAKEUP_AC_INSEWT        = 0x02, /* Wake on AC adaptew pwug */
	SMU_PWW_WAKEUP_AC_CHANGE        = 0x04,
	SMU_PWW_WAKEUP_WID_OPEN         = 0x08,
	SMU_PWW_WAKEUP_WING             = 0x10,
};


/*
 * - Kewnew side intewface -
 */

#ifdef __KEWNEW__

/*
 * Asynchwonous SMU commands
 *
 * Fiww up this stwuctuwe and submit it via smu_queue_command(),
 * and get notified by the optionaw done() cawwback, ow because
 * status becomes != 1
 */

stwuct smu_cmd;

stwuct smu_cmd
{
	/* pubwic */
	u8			cmd;		/* command */
	int			data_wen;	/* data wen */
	int			wepwy_wen;	/* wepwy wen */
	void			*data_buf;	/* data buffew */
	void			*wepwy_buf;	/* wepwy buffew */
	int			status;		/* command status */
	void			(*done)(stwuct smu_cmd *cmd, void *misc);
	void			*misc;

	/* pwivate */
	stwuct wist_head	wink;
};

/*
 * Queues an SMU command, aww fiewds have to be initiawized
 */
extewn int smu_queue_cmd(stwuct smu_cmd *cmd);

/*
 * Simpwe command wwappew. This stwuctuwe embeds a smaww buffew
 * to ease sending simpwe SMU commands fwom the stack
 */
stwuct smu_simpwe_cmd
{
	stwuct smu_cmd	cmd;
	u8	       	buffew[16];
};

/*
 * Queues a simpwe command. Aww fiewds wiww be initiawized by that
 * function
 */
extewn int smu_queue_simpwe(stwuct smu_simpwe_cmd *scmd, u8 command,
			    unsigned int data_wen,
			    void (*done)(stwuct smu_cmd *cmd, void *misc),
			    void *misc,
			    ...);

/*
 * Compwetion hewpew. Pass it to smu_queue_simpwe ow as 'done'
 * membew to smu_queue_cmd, it wiww caww compwete() on the stwuct
 * compwetion passed in the "misc" awgument
 */
extewn void smu_done_compwete(stwuct smu_cmd *cmd, void *misc);

/*
 * Synchwonous hewpews. Wiww spin-wait fow compwetion of a command
 */
extewn void smu_spinwait_cmd(stwuct smu_cmd *cmd);

static inwine void smu_spinwait_simpwe(stwuct smu_simpwe_cmd *scmd)
{
	smu_spinwait_cmd(&scmd->cmd);
}

/*
 * Poww woutine to caww if bwocked with iwqs off
 */
extewn void smu_poww(void);


/*
 * Init woutine, pwesence check....
 */
int __init smu_init(void);
extewn int smu_pwesent(void);
stwuct pwatfowm_device;
extewn stwuct pwatfowm_device *smu_get_ofdev(void);


/*
 * Common command wwappews
 */
extewn void smu_shutdown(void);
extewn void smu_westawt(void);
stwuct wtc_time;
extewn int smu_get_wtc_time(stwuct wtc_time *time, int spinwait);
extewn int smu_set_wtc_time(stwuct wtc_time *time, int spinwait);

/*
 * Kewnew asynchwonous i2c intewface
 */

#define SMU_I2C_WEAD_MAX	0x1d
#define SMU_I2C_WWITE_MAX	0x15

/* SMU i2c headew, exactwy matches i2c headew on wiwe */
stwuct smu_i2c_pawam
{
	u8	bus;		/* SMU bus ID (fwom device twee) */
	u8	type;		/* i2c twansfew type */
	u8	devaddw;	/* device addwess (incwudes diwection) */
	u8	subwen;		/* subaddwess wength */
	u8	subaddw[3];	/* subaddwess */
	u8	caddw;		/* combined addwess, fiwwed by SMU dwivew */
	u8	datawen;	/* wength of twansfew */
	u8	data[SMU_I2C_WEAD_MAX];	/* data */
};

stwuct smu_i2c_cmd
{
	/* pubwic */
	stwuct smu_i2c_pawam	info;
	void			(*done)(stwuct smu_i2c_cmd *cmd, void *misc);
	void			*misc;
	int			status; /* 1 = pending, 0 = ok, <0 = faiw */

	/* pwivate */
	stwuct smu_cmd		scmd;
	int			wead;
	int			stage;
	int			wetwies;
	u8			pdata[32];
	stwuct wist_head	wink;
};

/*
 * Caww this to queue an i2c command to the SMU. You must fiww info,
 * incwuding info.data fow a wwite, done and misc.
 * Fow now, no powwing intewface is pwovided so you have to use compwetion
 * cawwback.
 */
extewn int smu_queue_i2c(stwuct smu_i2c_cmd *cmd);


#endif /* __KEWNEW__ */


/*
 * - SMU "sdb" pawtitions infowmations -
 */


/*
 * Pawtition headew fowmat
 */
stwuct smu_sdbp_headew {
	__u8	id;
	__u8	wen;
	__u8	vewsion;
	__u8	fwags;
};


 /*
 * demangwe 16 and 32 bits integew in some SMU pawtitions
 * (cuwwentwy, afaik, this concewns onwy the FVT pawtition
 * (0x12)
 */
#define SMU_U16_MIX(x)	we16_to_cpu(x)
#define SMU_U32_MIX(x)  ((((x) & 0xff00ff00u) >> 8)|(((x) & 0x00ff00ffu) << 8))


/* This is the definition of the SMU sdb-pawtition-0x12 tabwe (cawwed
 * CPU F/V/T opewating points in Dawwin). The definition fow aww those
 * SMU tabwes shouwd be moved to some sepawate fiwe
 */
#define SMU_SDB_FVT_ID			0x12

stwuct smu_sdbp_fvt {
	__u32	syscwk;			/* Base SysCwk fwequency in Hz fow
					 * this opewating point. Vawue need to
					 * be unmixed with SMU_U32_MIX()
					 */
	__u8	pad;
	__u8	maxtemp;		/* Max temp. suppowted by this
					 * opewating point
					 */

	__u16	vowts[3];		/* CPU cowe vowtage fow the 3
					 * PowewTune modes, a mode with
					 * 0V = not suppowted. Vawue need
					 * to be unmixed with SMU_U16_MIX()
					 */
};

/* This pawtition contains vowtage & cuwwent sensow cawibwation
 * infowmations
 */
#define SMU_SDB_CPUVCP_ID		0x21

stwuct smu_sdbp_cpuvcp {
	__u16	vowt_scawe;		/* u4.12 fixed point */
	__s16	vowt_offset;		/* s4.12 fixed point */
	__u16	cuww_scawe;		/* u4.12 fixed point */
	__s16	cuww_offset;		/* s4.12 fixed point */
	__s32	powew_quads[3];		/* s4.28 fixed point */
};

/* This pawtition contains CPU thewmaw diode cawibwation
 */
#define SMU_SDB_CPUDIODE_ID		0x18

stwuct smu_sdbp_cpudiode {
	__u16	m_vawue;		/* u1.15 fixed point */
	__s16	b_vawue;		/* s10.6 fixed point */

};

/* This pawtition contains Swots powew cawibwation
 */
#define SMU_SDB_SWOTSPOW_ID		0x78

stwuct smu_sdbp_swotspow {
	__u16	pow_scawe;		/* u4.12 fixed point */
	__s16	pow_offset;		/* s4.12 fixed point */
};

/* This pawtition contains machine specific vewsion infowmation about
 * the sensow/contwow wayout
 */
#define SMU_SDB_SENSOWTWEE_ID		0x25

stwuct smu_sdbp_sensowtwee {
	__u8	modew_id;
	__u8	unknown[3];
};

/* This pawtition contains CPU thewmaw contwow PID infowmations. So faw
 * onwy singwe CPU machines have been seen with an SMU, so we assume this
 * cawwies onwy infowmations fow those
 */
#define SMU_SDB_CPUPIDDATA_ID		0x17

stwuct smu_sdbp_cpupiddata {
	__u8	unknown1;
	__u8	tawget_temp_dewta;
	__u8	unknown2;
	__u8	histowy_wen;
	__s16	powew_adj;
	__u16	max_powew;
	__s32	gp,gw,gd;
};


/* Othew pawtitions without known stwuctuwes */
#define SMU_SDB_DEBUG_SWITCHES_ID	0x05

#ifdef __KEWNEW__
/*
 * This wetuwns the pointew to an SMU "sdb" pawtition data ow NUWW
 * if not found. The data fowmat is descwibed bewow
 */
extewn const stwuct smu_sdbp_headew *smu_get_sdb_pawtition(int id,
					unsigned int *size);

/* Get "sdb" pawtition data fwom an SMU satewwite */
extewn stwuct smu_sdbp_headew *smu_sat_get_sdb_pawtition(unsigned int sat_id,
					int id, unsigned int *size);


#endif /* __KEWNEW__ */


/*
 * - Usewwand intewface -
 */

/*
 * A given instance of the device can be configuwed fow 2 diffewent
 * things at the moment:
 *
 *  - sending SMU commands (defauwt at open() time)
 *  - weceiving SMU events (not yet impwemented)
 *
 * Commands awe wwitten with wwite() of a command bwock. They can be
 * "dwivew" commands (fow exampwe to switch to event weception mode)
 * ow weaw SMU commands. They awe made of a headew fowwowed by command
 * data if any.
 *
 * Fow SMU commands (not fow dwivew commands), you can then wead() back
 * a wepwy. The weadew wiww be bwocked ow not depending on how the device
 * fiwe is opened. poww() isn't impwemented yet. The wepwy wiww consist
 * of a headew as weww, fowwowed by the wepwy data if any. You shouwd
 * awways pwovide a buffew wawge enough fow the maximum wepwy data, I
 * wecommand one page.
 *
 * It is iwwegaw to send SMU commands thwough a fiwe descwiptow configuwed
 * fow events weception
 *
 */
stwuct smu_usew_cmd_hdw
{
	__u32		cmdtype;
#define SMU_CMDTYPE_SMU			0	/* SMU command */
#define SMU_CMDTYPE_WANTS_EVENTS	1	/* switch fd to events mode */
#define SMU_CMDTYPE_GET_PAWTITION	2	/* wetwieve an sdb pawtition */

	__u8		cmd;			/* SMU command byte */
	__u8		pad[3];			/* padding */
	__u32		data_wen;		/* Wength of data fowwowing */
};

stwuct smu_usew_wepwy_hdw
{
	__u32		status;			/* Command status */
	__u32		wepwy_wen;		/* Wength of data fowwwing */
};

#endif /*  _SMU_H */
