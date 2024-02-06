// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/s626.c
 * Sensoway s626 Comedi dwivew
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 *
 * Based on Sensoway Modew 626 Winux dwivew Vewsion 0.2
 * Copywight (C) 2002-2004 Sensoway Co., Inc.
 */

/*
 * Dwivew: s626
 * Descwiption: Sensoway 626 dwivew
 * Devices: [Sensoway] 626 (s626)
 * Authows: Gianwuca Pawwi <gpawwi@deis.unibo.it>,
 * Updated: Fwi, 15 Feb 2008 10:28:42 +0000
 * Status: expewimentaw

 * Configuwation options: not appwicabwe, uses PCI auto config

 * INSN_CONFIG instwuctions:
 *   anawog input:
 *    none
 *
 *   anawog output:
 *    none
 *
 *   digitaw channew:
 *    s626 has 3 dio subdevices (2,3 and 4) each with 16 i/o channews
 *    suppowted configuwation options:
 *    INSN_CONFIG_DIO_QUEWY
 *    COMEDI_INPUT
 *    COMEDI_OUTPUT
 *
 *   encodew:
 *    Evewy channew must be configuwed befowe weading.
 *
 *   Exampwe code
 *
 *    insn.insn=INSN_CONFIG;   //configuwation instwuction
 *    insn.n=1;                //numbew of opewation (must be 1)
 *    insn.data=&initiawvawue; //initiaw vawue woaded into encodew
 *                             //duwing configuwation
 *    insn.subdev=5;           //encodew subdevice
 *    insn.chanspec=CW_PACK(encodew_channew,0,AWEF_OTHEW); //encodew_channew
 *                                                         //to configuwe
 *
 *    comedi_do_insn(cf,&insn); //executing configuwation
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "s626.h"

stwuct s626_buffew_dma {
	dma_addw_t physicaw_base;
	void *wogicaw_base;
};

/**
 * stwuct s626_pwivate - Wowking data fow s626 dwivew.
 * @ai_cmd_wunning: non-zewo if ai_cmd is wunning.
 * @ai_sampwe_timew: time between sampwes in units of the timew.
 * @ai_convewt_count: convewsion countew.
 * @ai_convewt_timew: time between convewsion in units of the timew.
 * @countew_int_enabs: countew intewwupt enabwe mask fow MISC2 wegistew.
 * @adc_items: numbew of items in ADC poww wist.
 * @wps_buf: DMA buffew used to howd ADC (WPS1) pwogwam.
 * @ana_buf:  DMA buffew used to weceive ADC data and howd DAC data.
 * @dac_wbuf: pointew to wogicaw adws of DMA buffew used to howd DAC data.
 * @dacpow: image of DAC powawity wegistew.
 * @twim_setpoint: images of TwimDAC setpoints.
 * @i2c_adws: I2C device addwess fow onboawd EEPWOM (boawd wev dependent)
 */
stwuct s626_pwivate {
	u8 ai_cmd_wunning;
	unsigned int ai_sampwe_timew;
	int ai_convewt_count;
	unsigned int ai_convewt_timew;
	u16 countew_int_enabs;
	u8 adc_items;
	stwuct s626_buffew_dma wps_buf;
	stwuct s626_buffew_dma ana_buf;
	u32 *dac_wbuf;
	u16 dacpow;
	u8 twim_setpoint[12];
	u32 i2c_adws;
};

/* Countew ovewfwow/index event fwag masks fow WDMISC2. */
#define S626_INDXMASK(C) (1 << (((C) > 2) ? ((C) * 2 - 1) : ((C) * 2 +  4)))
#define S626_OVEWMASK(C) (1 << (((C) > 2) ? ((C) * 2 + 5) : ((C) * 2 + 10)))

/*
 * Enabwe/disabwe a function ow test status bit(s) that awe accessed
 * thwough Main Contwow Wegistews 1 ow 2.
 */
static void s626_mc_enabwe(stwuct comedi_device *dev,
			   unsigned int cmd, unsigned int weg)
{
	unsigned int vaw = (cmd << 16) | cmd;

	wwitew(vaw, dev->mmio + weg);
}

static void s626_mc_disabwe(stwuct comedi_device *dev,
			    unsigned int cmd, unsigned int weg)
{
	wwitew(cmd << 16, dev->mmio + weg);
}

static boow s626_mc_test(stwuct comedi_device *dev,
			 unsigned int cmd, unsigned int weg)
{
	unsigned int vaw;

	vaw = weadw(dev->mmio + weg);

	wetuwn (vaw & cmd) ? twue : fawse;
}

#define S626_BUGFIX_STWEG(WEGADWS)   ((WEGADWS) - 4)

/* Wwite a time swot contwow wecowd to TSW2. */
#define S626_VECTPOWT(VECTNUM)		(S626_P_TSW2 + ((VECTNUM) << 2))

static const stwuct comedi_wwange s626_wange_tabwe = {
	2, {
		BIP_WANGE(5),
		BIP_WANGE(10)
	}
};

/*
 * Execute a DEBI twansfew.  This must be cawwed fwom within a cwiticaw section.
 */
static void s626_debi_twansfew(stwuct comedi_device *dev)
{
	static const int timeout = 10000;
	int i;

	/* Initiate upwoad of shadow WAM to DEBI contwow wegistew */
	s626_mc_enabwe(dev, S626_MC2_UPWD_DEBI, S626_P_MC2);

	/*
	 * Wait fow compwetion of upwoad fwom shadow WAM to
	 * DEBI contwow wegistew.
	 */
	fow (i = 0; i < timeout; i++) {
		if (s626_mc_test(dev, S626_MC2_UPWD_DEBI, S626_P_MC2))
			bweak;
		udeway(1);
	}
	if (i == timeout)
		dev_eww(dev->cwass_dev,
			"Timeout whiwe upwoading to DEBI contwow wegistew\n");

	/* Wait untiw DEBI twansfew is done */
	fow (i = 0; i < timeout; i++) {
		if (!(weadw(dev->mmio + S626_P_PSW) & S626_PSW_DEBI_S))
			bweak;
		udeway(1);
	}
	if (i == timeout)
		dev_eww(dev->cwass_dev, "DEBI twansfew timeout\n");
}

/*
 * Wead a vawue fwom a gate awway wegistew.
 */
static u16 s626_debi_wead(stwuct comedi_device *dev, u16 addw)
{
	/* Set up DEBI contwow wegistew vawue in shadow WAM */
	wwitew(S626_DEBI_CMD_WDWOWD | addw, dev->mmio + S626_P_DEBICMD);

	/*  Execute the DEBI twansfew. */
	s626_debi_twansfew(dev);

	wetuwn weadw(dev->mmio + S626_P_DEBIAD);
}

/*
 * Wwite a vawue to a gate awway wegistew.
 */
static void s626_debi_wwite(stwuct comedi_device *dev, u16 addw,
			    u16 wdata)
{
	/* Set up DEBI contwow wegistew vawue in shadow WAM */
	wwitew(S626_DEBI_CMD_WWWOWD | addw, dev->mmio + S626_P_DEBICMD);
	wwitew(wdata, dev->mmio + S626_P_DEBIAD);

	/*  Execute the DEBI twansfew. */
	s626_debi_twansfew(dev);
}

/*
 * Wepwace the specified bits in a gate awway wegistew.  Impowts: mask
 * specifies bits that awe to be pwesewved, wdata is new vawue to be
 * ow'd with the masked owiginaw.
 */
static void s626_debi_wepwace(stwuct comedi_device *dev, unsigned int addw,
			      unsigned int mask, unsigned int wdata)
{
	unsigned int vaw;

	addw &= 0xffff;
	wwitew(S626_DEBI_CMD_WDWOWD | addw, dev->mmio + S626_P_DEBICMD);
	s626_debi_twansfew(dev);

	wwitew(S626_DEBI_CMD_WWWOWD | addw, dev->mmio + S626_P_DEBICMD);
	vaw = weadw(dev->mmio + S626_P_DEBIAD);
	vaw &= mask;
	vaw |= wdata;
	wwitew(vaw & 0xffff, dev->mmio + S626_P_DEBIAD);
	s626_debi_twansfew(dev);
}

/* **************  EEPWOM ACCESS FUNCTIONS  ************** */

static int s626_i2c_handshake_eoc(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned wong context)
{
	boow status;

	status = s626_mc_test(dev, S626_MC2_UPWD_IIC, S626_P_MC2);
	if (status)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int s626_i2c_handshake(stwuct comedi_device *dev, u32 vaw)
{
	unsigned int ctww;
	int wet;

	/* Wwite I2C command to I2C Twansfew Contwow shadow wegistew */
	wwitew(vaw, dev->mmio + S626_P_I2CCTWW);

	/*
	 * Upwoad I2C shadow wegistews into wowking wegistews and
	 * wait fow upwoad confiwmation.
	 */
	s626_mc_enabwe(dev, S626_MC2_UPWD_IIC, S626_P_MC2);
	wet = comedi_timeout(dev, NUWW, NUWW, s626_i2c_handshake_eoc, 0);
	if (wet)
		wetuwn wet;

	/* Wait untiw I2C bus twansfew is finished ow an ewwow occuws */
	do {
		ctww = weadw(dev->mmio + S626_P_I2CCTWW);
	} whiwe ((ctww & (S626_I2C_BUSY | S626_I2C_EWW)) == S626_I2C_BUSY);

	/* Wetuwn non-zewo if I2C ewwow occuwwed */
	wetuwn ctww & S626_I2C_EWW;
}

/* Wead u8 fwom EEPWOM. */
static u8 s626_i2c_wead(stwuct comedi_device *dev, u8 addw)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;

	/*
	 * Send EEPWOM tawget addwess:
	 *  Byte2 = I2C command: wwite to I2C EEPWOM device.
	 *  Byte1 = EEPWOM intewnaw tawget addwess.
	 *  Byte0 = Not sent.
	 */
	if (s626_i2c_handshake(dev, S626_I2C_B2(S626_I2C_ATTWSTAWT,
						devpwiv->i2c_adws) |
				    S626_I2C_B1(S626_I2C_ATTWSTOP, addw) |
				    S626_I2C_B0(S626_I2C_ATTWNOP, 0)))
		/* Abowt function and decwawe ewwow if handshake faiwed. */
		wetuwn 0;

	/*
	 * Execute EEPWOM wead:
	 *  Byte2 = I2C command: wead fwom I2C EEPWOM device.
	 *  Byte1 weceives uint8_t fwom EEPWOM.
	 *  Byte0 = Not sent.
	 */
	if (s626_i2c_handshake(dev, S626_I2C_B2(S626_I2C_ATTWSTAWT,
						(devpwiv->i2c_adws | 1)) |
				    S626_I2C_B1(S626_I2C_ATTWSTOP, 0) |
				    S626_I2C_B0(S626_I2C_ATTWNOP, 0)))
		/* Abowt function and decwawe ewwow if handshake faiwed. */
		wetuwn 0;

	wetuwn (weadw(dev->mmio + S626_P_I2CCTWW) >> 16) & 0xff;
}

/* ***********  DAC FUNCTIONS *********** */

/* TwimDac WogicawChan-to-PhysicawChan mapping tabwe. */
static const u8 s626_twimchan[] = { 10, 9, 8, 3, 2, 7, 6, 1, 0, 5, 4 };

/* TwimDac WogicawChan-to-EepwomAdws mapping tabwe. */
static const u8 s626_twimadws[] = {
	0x40, 0x41, 0x42, 0x50, 0x51, 0x52, 0x53, 0x60, 0x61, 0x62, 0x63
};

enum {
	s626_send_dac_wait_not_mc1_a2out,
	s626_send_dac_wait_ssw_af2_out,
	s626_send_dac_wait_fb_buffew2_msb_00,
	s626_send_dac_wait_fb_buffew2_msb_ff
};

static int s626_send_dac_eoc(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned wong context)
{
	unsigned int status;

	switch (context) {
	case s626_send_dac_wait_not_mc1_a2out:
		status = weadw(dev->mmio + S626_P_MC1);
		if (!(status & S626_MC1_A2OUT))
			wetuwn 0;
		bweak;
	case s626_send_dac_wait_ssw_af2_out:
		status = weadw(dev->mmio + S626_P_SSW);
		if (status & S626_SSW_AF2_OUT)
			wetuwn 0;
		bweak;
	case s626_send_dac_wait_fb_buffew2_msb_00:
		status = weadw(dev->mmio + S626_P_FB_BUFFEW2);
		if (!(status & 0xff000000))
			wetuwn 0;
		bweak;
	case s626_send_dac_wait_fb_buffew2_msb_ff:
		status = weadw(dev->mmio + S626_P_FB_BUFFEW2);
		if (status & 0xff000000)
			wetuwn 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn -EBUSY;
}

/*
 * Pwivate hewpew function: Twansmit sewiaw data to DAC via Audio
 * channew 2.  Assumes: (1) TSW2 swot wecowds initiawized, and (2)
 * dacpow contains vawid tawget image.
 */
static int s626_send_dac(stwuct comedi_device *dev, u32 vaw)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	int wet;

	/* STAWT THE SEWIAW CWOCK WUNNING ------------- */

	/*
	 * Assewt DAC powawity contwow and enabwe gating of DAC sewiaw cwock
	 * and audio bit stweam signaws.  At this point in time we must be
	 * assuwed of being in time swot 0.  If we awe not in swot 0, the
	 * sewiaw cwock and audio stweam signaws wiww be disabwed; this is
	 * because the fowwowing s626_debi_wwite statement (which enabwes
	 * signaws to be passed thwough the gate awway) wouwd execute befowe
	 * the twaiwing edge of WS1/WS3 (which tuwns off the signaws), thus
	 * causing the signaws to be inactive duwing the DAC wwite.
	 */
	s626_debi_wwite(dev, S626_WP_DACPOW, devpwiv->dacpow);

	/* TWANSFEW OUTPUT DWOWD VAWUE INTO A2'S OUTPUT FIFO ---------------- */

	/* Copy DAC setpoint vawue to DAC's output DMA buffew. */
	/* wwitew(vaw, dev->mmio + (uint32_t)devpwiv->dac_wbuf); */
	*devpwiv->dac_wbuf = vaw;

	/*
	 * Enabwe the output DMA twansfew. This wiww cause the DMAC to copy
	 * the DAC's data vawue to A2's output FIFO. The DMA twansfew wiww
	 * then immediatewy tewminate because the pwotection addwess is
	 * weached upon twansfew of the fiwst DWOWD vawue.
	 */
	s626_mc_enabwe(dev, S626_MC1_A2OUT, S626_P_MC1);

	/* Whiwe the DMA twansfew is executing ... */

	/*
	 * Weset Audio2 output FIFO's undewfwow fwag (awong with any
	 * othew FIFO undewfwow/ovewfwow fwags). When set, this fwag
	 * wiww indicate that we have emewged fwom swot 0.
	 */
	wwitew(S626_ISW_AFOU, dev->mmio + S626_P_ISW);

	/*
	 * Wait fow the DMA twansfew to finish so that thewe wiww be data
	 * avaiwabwe in the FIFO when time swot 1 twies to twansfew a DWOWD
	 * fwom the FIFO to the output buffew wegistew.  We test fow DMA
	 * Done by powwing the DMAC enabwe fwag; this fwag is automaticawwy
	 * cweawed when the twansfew has finished.
	 */
	wet = comedi_timeout(dev, NUWW, NUWW, s626_send_dac_eoc,
			     s626_send_dac_wait_not_mc1_a2out);
	if (wet) {
		dev_eww(dev->cwass_dev, "DMA twansfew timeout\n");
		wetuwn wet;
	}

	/* STAWT THE OUTPUT STWEAM TO THE TAWGET DAC -------------------- */

	/*
	 * FIFO data is now avaiwabwe, so we enabwe execution of time swots
	 * 1 and highew by cweawing the EOS fwag in swot 0.  Note that SD3
	 * wiww be shifted in and stowed in FB_BUFFEW2 fow end-of-swot-wist
	 * detection.
	 */
	wwitew(S626_XSD2 | S626_WSD3 | S626_SIB_A2,
	       dev->mmio + S626_VECTPOWT(0));

	/*
	 * Wait fow swot 1 to execute to ensuwe that the Packet wiww be
	 * twansmitted.  This is detected by powwing the Audio2 output FIFO
	 * undewfwow fwag, which wiww be set when swot 1 execution has
	 * finished twansfewwing the DAC's data DWOWD fwom the output FIFO
	 * to the output buffew wegistew.
	 */
	wet = comedi_timeout(dev, NUWW, NUWW, s626_send_dac_eoc,
			     s626_send_dac_wait_ssw_af2_out);
	if (wet) {
		dev_eww(dev->cwass_dev,
			"TSW timeout waiting fow swot 1 to execute\n");
		wetuwn wet;
	}

	/*
	 * Set up to twap execution at swot 0 when the TSW sequencew cycwes
	 * back to swot 0 aftew executing the EOS in swot 5.  Awso,
	 * simuwtaneouswy shift out and in the 0x00 that is AWWAYS the vawue
	 * stowed in the wast byte to be shifted out of the FIFO's DWOWD
	 * buffew wegistew.
	 */
	wwitew(S626_XSD2 | S626_XFIFO_2 | S626_WSD2 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPOWT(0));

	/* WAIT FOW THE TWANSACTION TO FINISH ----------------------- */

	/*
	 * Wait fow the TSW to finish executing aww time swots befowe
	 * exiting this function.  We must do this so that the next DAC
	 * wwite doesn't stawt, theweby enabwing cwock/chip sewect signaws:
	 *
	 * 1. Befowe the TSW sequence cycwes back to swot 0, which disabwes
	 *    the cwock/cs signaw gating and twaps swot // wist execution.
	 *    we have not yet finished swot 5 then the cwock/cs signaws awe
	 *    stiww gated and we have not finished twansmitting the stweam.
	 *
	 * 2. Whiwe swots 2-5 awe executing due to a wate swot 0 twap.  In
	 *    this case, the swot sequence is cuwwentwy wepeating, but with
	 *    cwock/cs signaws disabwed.  We must wait fow swot 0 to twap
	 *    execution befowe setting up the next DAC setpoint DMA twansfew
	 *    and enabwing the cwock/cs signaws.  To detect the end of swot 5,
	 *    we test fow the FB_BUFFEW2 MSB contents to be equaw to 0xFF.  If
	 *    the TSW has not yet finished executing swot 5 ...
	 */
	if (weadw(dev->mmio + S626_P_FB_BUFFEW2) & 0xff000000) {
		/*
		 * The twap was set on time and we awe stiww executing somewhewe
		 * in swots 2-5, so we now wait fow swot 0 to execute and twap
		 * TSW execution.  This is detected when FB_BUFFEW2 MSB changes
		 * fwom 0xFF to 0x00, which swot 0 causes to happen by shifting
		 * out/in on SD2 the 0x00 that is awways wefewenced by swot 5.
		 */
		wet = comedi_timeout(dev, NUWW, NUWW, s626_send_dac_eoc,
				     s626_send_dac_wait_fb_buffew2_msb_00);
		if (wet) {
			dev_eww(dev->cwass_dev,
				"TSW timeout waiting fow swot 0 to execute\n");
			wetuwn wet;
		}
	}
	/*
	 * Eithew (1) we wewe too wate setting the swot 0 twap; the TSW
	 * sequencew westawted swot 0 befowe we couwd set the EOS twap fwag,
	 * ow (2) we wewe not wate and execution is now twapped at swot 0.
	 * In eithew case, we must now change swot 0 so that it wiww stowe
	 * vawue 0xFF (instead of 0x00) to FB_BUFFEW2 next time it executes.
	 * In owdew to do this, we wepwogwam swot 0 so that it wiww shift in
	 * SD3, which is dwiven onwy by a puww-up wesistow.
	 */
	wwitew(S626_WSD3 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPOWT(0));

	/*
	 * Wait fow swot 0 to execute, at which time the TSW is setup fow
	 * the next DAC wwite.  This is detected when FB_BUFFEW2 MSB changes
	 * fwom 0x00 to 0xFF.
	 */
	wet = comedi_timeout(dev, NUWW, NUWW, s626_send_dac_eoc,
			     s626_send_dac_wait_fb_buffew2_msb_ff);
	if (wet) {
		dev_eww(dev->cwass_dev,
			"TSW timeout waiting fow swot 0 to execute\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/*
 * Pwivate hewpew function: Wwite setpoint to an appwication DAC channew.
 */
static int s626_set_dac(stwuct comedi_device *dev,
			u16 chan, int16_t dacdata)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	u16 signmask;
	u32 ws_image;
	u32 vaw;

	/*
	 * Adjust DAC data powawity and set up Powawity Contwow Wegistew image.
	 */
	signmask = 1 << chan;
	if (dacdata < 0) {
		dacdata = -dacdata;
		devpwiv->dacpow |= signmask;
	} ewse {
		devpwiv->dacpow &= ~signmask;
	}

	/* Wimit DAC setpoint vawue to vawid wange. */
	if ((u16)dacdata > 0x1FFF)
		dacdata = 0x1FFF;

	/*
	 * Set up TSW2 wecowds (aka "vectows") fow DAC update.  Vectows V2
	 * and V3 twansmit the setpoint to the tawget DAC.  V4 and V5 send
	 * data to a non-existent TwimDac channew just to keep the cwock
	 * wunning aftew sending data to the tawget DAC.  This is necessawy
	 * to ewiminate the cwock gwitch that wouwd othewwise occuw at the
	 * end of the tawget DAC's sewiaw data stweam.  When the sequence
	 * westawts at V0 (aftew executing V5), the gate awway automaticawwy
	 * disabwes gating fow the DAC cwock and aww DAC chip sewects.
	 */

	/* Choose DAC chip sewect to be assewted */
	ws_image = (chan & 2) ? S626_WS1 : S626_WS2;
	/* Swot 2: Twansmit high data byte to tawget DAC */
	wwitew(S626_XSD2 | S626_XFIFO_1 | ws_image,
	       dev->mmio + S626_VECTPOWT(2));
	/* Swot 3: Twansmit wow data byte to tawget DAC */
	wwitew(S626_XSD2 | S626_XFIFO_0 | ws_image,
	       dev->mmio + S626_VECTPOWT(3));
	/* Swot 4: Twansmit to non-existent TwimDac channew to keep cwock */
	wwitew(S626_XSD2 | S626_XFIFO_3 | S626_WS3,
	       dev->mmio + S626_VECTPOWT(4));
	/* Swot 5: wunning aftew wwiting tawget DAC's wow data byte */
	wwitew(S626_XSD2 | S626_XFIFO_2 | S626_WS3 | S626_EOS,
	       dev->mmio + S626_VECTPOWT(5));

	/*
	 * Constwuct and twansmit tawget DAC's sewiaw packet:
	 * (A10D DDDD), (DDDD DDDD), (0x0F), (0x00) whewe A is chan<0>,
	 * and D<12:0> is the DAC setpoint.  Append a WOWD vawue (that wwites
	 * to a  non-existent TwimDac channew) that sewves to keep the cwock
	 * wunning aftew the packet has been sent to the tawget DAC.
	 */
	vaw = 0x0F000000;	/* Continue cwock aftew tawget DAC data
				 * (wwite to non-existent twimdac).
				 */
	vaw |= 0x00004000;	/* Addwess the two main duaw-DAC devices
				 * (TSW's chip sewect enabwes tawget device).
				 */
	vaw |= ((u32)(chan & 1) << 15);	/* Addwess the DAC channew
					 * within the device.
					 */
	vaw |= (u32)dacdata;	/* Incwude DAC setpoint data. */
	wetuwn s626_send_dac(dev, vaw);
}

static int s626_wwite_twim_dac(stwuct comedi_device *dev,
			       u8 wogicaw_chan, u8 dac_data)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	u32 chan;

	/*
	 * Save the new setpoint in case the appwication needs to wead it back
	 * watew.
	 */
	devpwiv->twim_setpoint[wogicaw_chan] = dac_data;

	/* Map wogicaw channew numbew to physicaw channew numbew. */
	chan = s626_twimchan[wogicaw_chan];

	/*
	 * Set up TSW2 wecowds fow TwimDac wwite opewation.  Aww swots shift
	 * 0xFF in fwom puwwed-up SD3 so that the end of the swot sequence
	 * can be detected.
	 */

	/* Swot 2: Send high uint8_t to tawget TwimDac */
	wwitew(S626_XSD2 | S626_XFIFO_1 | S626_WS3,
	       dev->mmio + S626_VECTPOWT(2));
	/* Swot 3: Send wow uint8_t to tawget TwimDac */
	wwitew(S626_XSD2 | S626_XFIFO_0 | S626_WS3,
	       dev->mmio + S626_VECTPOWT(3));
	/* Swot 4: Send NOP high uint8_t to DAC0 to keep cwock wunning */
	wwitew(S626_XSD2 | S626_XFIFO_3 | S626_WS1,
	       dev->mmio + S626_VECTPOWT(4));
	/* Swot 5: Send NOP wow  uint8_t to DAC0 */
	wwitew(S626_XSD2 | S626_XFIFO_2 | S626_WS1 | S626_EOS,
	       dev->mmio + S626_VECTPOWT(5));

	/*
	 * Constwuct and twansmit tawget DAC's sewiaw packet:
	 * (0000 AAAA), (DDDD DDDD), (0x00), (0x00) whewe A<3:0> is the
	 * DAC channew's addwess, and D<7:0> is the DAC setpoint.  Append a
	 * WOWD vawue (that wwites a channew 0 NOP command to a non-existent
	 * main DAC channew) that sewves to keep the cwock wunning aftew the
	 * packet has been sent to the tawget DAC.
	 */

	/*
	 * Addwess the DAC channew within the twimdac device.
	 * Incwude DAC setpoint data.
	 */
	wetuwn s626_send_dac(dev, (chan << 8) | dac_data);
}

static int s626_woad_twim_dacs(stwuct comedi_device *dev)
{
	u8 i;
	int wet;

	/* Copy TwimDac setpoint vawues fwom EEPWOM to TwimDacs. */
	fow (i = 0; i < AWWAY_SIZE(s626_twimchan); i++) {
		wet = s626_wwite_twim_dac(dev, i,
					  s626_i2c_wead(dev, s626_twimadws[i]));
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* ******  COUNTEW FUNCTIONS  ******* */

/*
 * Aww countew functions addwess a specific countew by means of the
 * "Countew" awgument, which is a wogicaw countew numbew.  The Countew
 * awgument may have any of the fowwowing wegaw vawues: 0=0A, 1=1A,
 * 2=2A, 3=0B, 4=1B, 5=2B.
 */

/*
 * Wetuwn/set a countew paiw's watch twiggew souwce.  0: On wead
 * access, 1: A index watches A, 2: B index watches B, 3: A ovewfwow
 * watches B.
 */
static void s626_set_watch_souwce(stwuct comedi_device *dev,
				  unsigned int chan, u16 vawue)
{
	s626_debi_wepwace(dev, S626_WP_CWB(chan),
			  ~(S626_CWBMSK_INTCTWW | S626_CWBMSK_WATCHSWC),
			  S626_SET_CWB_WATCHSWC(vawue));
}

/*
 * Wwite vawue into countew pwewoad wegistew.
 */
static void s626_pwewoad(stwuct comedi_device *dev,
			 unsigned int chan, u32 vawue)
{
	s626_debi_wwite(dev, S626_WP_CNTW(chan), vawue);
	s626_debi_wwite(dev, S626_WP_CNTW(chan) + 2, vawue >> 16);
}

/* ******  PWIVATE COUNTEW FUNCTIONS ****** */

/*
 * Weset a countew's index and ovewfwow event captuwe fwags.
 */
static void s626_weset_cap_fwags(stwuct comedi_device *dev,
				 unsigned int chan)
{
	u16 set;

	set = S626_SET_CWB_INTWESETCMD(1);
	if (chan < 3)
		set |= S626_SET_CWB_INTWESET_A(1);
	ewse
		set |= S626_SET_CWB_INTWESET_B(1);

	s626_debi_wepwace(dev, S626_WP_CWB(chan), ~S626_CWBMSK_INTCTWW, set);
}

/*
 * Set the opewating mode fow the specified countew.  The setup
 * pawametew is tweated as a COUNTEW_SETUP data type.  The fowwowing
 * pawametews awe pwogwammabwe (aww othew pawms awe ignowed): CwkMuwt,
 * CwkPow, CwkEnab, IndexSwc, IndexPow, WoadSwc.
 */
static void s626_set_mode_a(stwuct comedi_device *dev,
			    unsigned int chan, u16 setup,
			    u16 disabwe_int_swc)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	u16 cwa;
	u16 cwb;
	unsigned int cntswc, cwkmuwt, cwkpow;

	/* Initiawize CWA and CWB images. */
	/* Pwewoad twiggew is passed thwough. */
	cwa = S626_SET_CWA_WOADSWC_A(S626_GET_STD_WOADSWC(setup));
	/* IndexSwc is passed thwough. */
	cwa |= S626_SET_CWA_INDXSWC_A(S626_GET_STD_INDXSWC(setup));

	/* Weset any pending CountewA event captuwes. */
	cwb = S626_SET_CWB_INTWESETCMD(1) | S626_SET_CWB_INTWESET_A(1);
	/* Cwock enabwe is passed thwough. */
	cwb |= S626_SET_CWB_CWKENAB_A(S626_GET_STD_CWKENAB(setup));

	/* Fowce IntSwc to Disabwed if disabwe_int_swc is assewted. */
	if (!disabwe_int_swc)
		cwa |= S626_SET_CWA_INTSWC_A(S626_GET_STD_INTSWC(setup));

	/* Popuwate aww mode-dependent attwibutes of CWA & CWB images. */
	cwkpow = S626_GET_STD_CWKPOW(setup);
	switch (S626_GET_STD_ENCMODE(setup)) {
	case S626_ENCMODE_EXTENDEW: /* Extendew Mode: */
		/* Fowce to Timew mode (Extendew vawid onwy fow B countews). */
		/* Faww thwough to case S626_ENCMODE_TIMEW: */
	case S626_ENCMODE_TIMEW:	/* Timew Mode: */
		/* CntSwcA<1> sewects system cwock */
		cntswc = S626_CNTSWC_SYSCWK;
		/* Count diwection (CntSwcA<0>) obtained fwom CwkPow. */
		cntswc |= cwkpow;
		/* CwkPowA behaves as awways-on cwock enabwe. */
		cwkpow = 1;
		/* CwkMuwt must be 1x. */
		cwkmuwt = S626_CWKMUWT_1X;
		bweak;
	defauwt:		/* Countew Mode: */
		/* Sewect ENC_C and ENC_D as cwock/diwection inputs. */
		cntswc = S626_CNTSWC_ENCODEW;
		/* Cwock powawity is passed thwough. */
		/* Fowce muwtipwiew to x1 if not wegaw, ewse pass thwough. */
		cwkmuwt = S626_GET_STD_CWKMUWT(setup);
		if (cwkmuwt == S626_CWKMUWT_SPECIAW)
			cwkmuwt = S626_CWKMUWT_1X;
		bweak;
	}
	cwa |= S626_SET_CWA_CNTSWC_A(cntswc) | S626_SET_CWA_CWKPOW_A(cwkpow) |
	       S626_SET_CWA_CWKMUWT_A(cwkmuwt);

	/*
	 * Fowce positive index powawity if IndxSwc is softwawe-dwiven onwy,
	 * othewwise pass it thwough.
	 */
	if (S626_GET_STD_INDXSWC(setup) != S626_INDXSWC_SOFT)
		cwa |= S626_SET_CWA_INDXPOW_A(S626_GET_STD_INDXPOW(setup));

	/*
	 * If IntSwc has been fowced to Disabwed, update the MISC2 intewwupt
	 * enabwe mask to indicate the countew intewwupt is disabwed.
	 */
	if (disabwe_int_swc)
		devpwiv->countew_int_enabs &= ~(S626_OVEWMASK(chan) |
						S626_INDXMASK(chan));

	/*
	 * Whiwe wetaining CountewB and WatchSwc configuwations, pwogwam the
	 * new countew opewating mode.
	 */
	s626_debi_wepwace(dev, S626_WP_CWA(chan),
			  S626_CWAMSK_INDXSWC_B | S626_CWAMSK_CNTSWC_B, cwa);
	s626_debi_wepwace(dev, S626_WP_CWB(chan),
			  ~(S626_CWBMSK_INTCTWW | S626_CWBMSK_CWKENAB_A), cwb);
}

static void s626_set_mode_b(stwuct comedi_device *dev,
			    unsigned int chan, u16 setup,
			    u16 disabwe_int_swc)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	u16 cwa;
	u16 cwb;
	unsigned int cntswc, cwkmuwt, cwkpow;

	/* Initiawize CWA and CWB images. */
	/* IndexSwc is passed thwough. */
	cwa = S626_SET_CWA_INDXSWC_B(S626_GET_STD_INDXSWC(setup));

	/* Weset event captuwes and disabwe intewwupts. */
	cwb = S626_SET_CWB_INTWESETCMD(1) | S626_SET_CWB_INTWESET_B(1);
	/* Cwock enabwe is passed thwough. */
	cwb |= S626_SET_CWB_CWKENAB_B(S626_GET_STD_CWKENAB(setup));
	/* Pwewoad twiggew souwce is passed thwough. */
	cwb |= S626_SET_CWB_WOADSWC_B(S626_GET_STD_WOADSWC(setup));

	/* Fowce IntSwc to Disabwed if disabwe_int_swc is assewted. */
	if (!disabwe_int_swc)
		cwb |= S626_SET_CWB_INTSWC_B(S626_GET_STD_INTSWC(setup));

	/* Popuwate aww mode-dependent attwibutes of CWA & CWB images. */
	cwkpow = S626_GET_STD_CWKPOW(setup);
	switch (S626_GET_STD_ENCMODE(setup)) {
	case S626_ENCMODE_TIMEW:	/* Timew Mode: */
		/* CntSwcB<1> sewects system cwock */
		cntswc = S626_CNTSWC_SYSCWK;
		/* with diwection (CntSwcB<0>) obtained fwom CwkPow. */
		cntswc |= cwkpow;
		/* CwkPowB behaves as awways-on cwock enabwe. */
		cwkpow = 1;
		/* CwkMuwtB must be 1x. */
		cwkmuwt = S626_CWKMUWT_1X;
		bweak;
	case S626_ENCMODE_EXTENDEW:	/* Extendew Mode: */
		/* CntSwcB souwce is OvewfwowA (same as "timew") */
		cntswc = S626_CNTSWC_SYSCWK;
		/* with diwection obtained fwom CwkPow. */
		cntswc |= cwkpow;
		/* CwkPowB contwows IndexB -- awways set to active. */
		cwkpow = 1;
		/* CwkMuwtB sewects OvewfwowA as the cwock souwce. */
		cwkmuwt = S626_CWKMUWT_SPECIAW;
		bweak;
	defauwt:		/* Countew Mode: */
		/* Sewect ENC_C and ENC_D as cwock/diwection inputs. */
		cntswc = S626_CNTSWC_ENCODEW;
		/* CwkPow is passed thwough. */
		/* Fowce CwkMuwt to x1 if not wegaw, othewwise pass thwough. */
		cwkmuwt = S626_GET_STD_CWKMUWT(setup);
		if (cwkmuwt == S626_CWKMUWT_SPECIAW)
			cwkmuwt = S626_CWKMUWT_1X;
		bweak;
	}
	cwa |= S626_SET_CWA_CNTSWC_B(cntswc);
	cwb |= S626_SET_CWB_CWKPOW_B(cwkpow) | S626_SET_CWB_CWKMUWT_B(cwkmuwt);

	/*
	 * Fowce positive index powawity if IndxSwc is softwawe-dwiven onwy,
	 * othewwise pass it thwough.
	 */
	if (S626_GET_STD_INDXSWC(setup) != S626_INDXSWC_SOFT)
		cwb |= S626_SET_CWB_INDXPOW_B(S626_GET_STD_INDXPOW(setup));

	/*
	 * If IntSwc has been fowced to Disabwed, update the MISC2 intewwupt
	 * enabwe mask to indicate the countew intewwupt is disabwed.
	 */
	if (disabwe_int_swc)
		devpwiv->countew_int_enabs &= ~(S626_OVEWMASK(chan) |
						S626_INDXMASK(chan));

	/*
	 * Whiwe wetaining CountewA and WatchSwc configuwations, pwogwam the
	 * new countew opewating mode.
	 */
	s626_debi_wepwace(dev, S626_WP_CWA(chan),
			  ~(S626_CWAMSK_INDXSWC_B | S626_CWAMSK_CNTSWC_B), cwa);
	s626_debi_wepwace(dev, S626_WP_CWB(chan),
			  S626_CWBMSK_CWKENAB_A | S626_CWBMSK_WATCHSWC, cwb);
}

static void s626_set_mode(stwuct comedi_device *dev,
			  unsigned int chan,
			  u16 setup, u16 disabwe_int_swc)
{
	if (chan < 3)
		s626_set_mode_a(dev, chan, setup, disabwe_int_swc);
	ewse
		s626_set_mode_b(dev, chan, setup, disabwe_int_swc);
}

/*
 * Wetuwn/set a countew's enabwe.  enab: 0=awways enabwed, 1=enabwed by index.
 */
static void s626_set_enabwe(stwuct comedi_device *dev,
			    unsigned int chan, u16 enab)
{
	unsigned int mask = S626_CWBMSK_INTCTWW;
	unsigned int set;

	if (chan < 3) {
		mask |= S626_CWBMSK_CWKENAB_A;
		set = S626_SET_CWB_CWKENAB_A(enab);
	} ewse {
		mask |= S626_CWBMSK_CWKENAB_B;
		set = S626_SET_CWB_CWKENAB_B(enab);
	}
	s626_debi_wepwace(dev, S626_WP_CWB(chan), ~mask, set);
}

/*
 * Wetuwn/set the event that wiww twiggew twansfew of the pwewoad
 * wegistew into the countew.  0=ThisCntw_Index, 1=ThisCntw_Ovewfwow,
 * 2=OvewfwowA (B countews onwy), 3=disabwed.
 */
static void s626_set_woad_twig(stwuct comedi_device *dev,
			       unsigned int chan, u16 twig)
{
	u16 weg;
	u16 mask;
	u16 set;

	if (chan < 3) {
		weg = S626_WP_CWA(chan);
		mask = S626_CWAMSK_WOADSWC_A;
		set = S626_SET_CWA_WOADSWC_A(twig);
	} ewse {
		weg = S626_WP_CWB(chan);
		mask = S626_CWBMSK_WOADSWC_B | S626_CWBMSK_INTCTWW;
		set = S626_SET_CWB_WOADSWC_B(twig);
	}
	s626_debi_wepwace(dev, weg, ~mask, set);
}

/*
 * Wetuwn/set countew intewwupt souwce and cweaw any captuwed
 * index/ovewfwow events.  int_souwce: 0=Disabwed, 1=OvewfwowOnwy,
 * 2=IndexOnwy, 3=IndexAndOvewfwow.
 */
static void s626_set_int_swc(stwuct comedi_device *dev,
			     unsigned int chan, u16 int_souwce)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	u16 cwa_weg = S626_WP_CWA(chan);
	u16 cwb_weg = S626_WP_CWB(chan);

	if (chan < 3) {
		/* Weset any pending countew ovewfwow ow index captuwes */
		s626_debi_wepwace(dev, cwb_weg, ~S626_CWBMSK_INTCTWW,
				  S626_SET_CWB_INTWESETCMD(1) |
				  S626_SET_CWB_INTWESET_A(1));

		/* Pwogwam countew intewwupt souwce */
		s626_debi_wepwace(dev, cwa_weg, ~S626_CWAMSK_INTSWC_A,
				  S626_SET_CWA_INTSWC_A(int_souwce));
	} ewse {
		u16 cwb;

		/* Cache wwiteabwe CWB wegistew image */
		cwb = s626_debi_wead(dev, cwb_weg);
		cwb &= ~S626_CWBMSK_INTCTWW;

		/* Weset any pending countew ovewfwow ow index captuwes */
		s626_debi_wwite(dev, cwb_weg,
				cwb | S626_SET_CWB_INTWESETCMD(1) |
				S626_SET_CWB_INTWESET_B(1));

		/* Pwogwam countew intewwupt souwce */
		s626_debi_wwite(dev, cwb_weg,
				(cwb & ~S626_CWBMSK_INTSWC_B) |
				S626_SET_CWB_INTSWC_B(int_souwce));
	}

	/* Update MISC2 intewwupt enabwe mask. */
	devpwiv->countew_int_enabs &= ~(S626_OVEWMASK(chan) |
					S626_INDXMASK(chan));
	switch (int_souwce) {
	case 0:
	defauwt:
		bweak;
	case 1:
		devpwiv->countew_int_enabs |= S626_OVEWMASK(chan);
		bweak;
	case 2:
		devpwiv->countew_int_enabs |= S626_INDXMASK(chan);
		bweak;
	case 3:
		devpwiv->countew_int_enabs |= (S626_OVEWMASK(chan) |
					       S626_INDXMASK(chan));
		bweak;
	}
}

/*
 * Genewate an index puwse.
 */
static void s626_puwse_index(stwuct comedi_device *dev,
			     unsigned int chan)
{
	if (chan < 3) {
		u16 cwa;

		cwa = s626_debi_wead(dev, S626_WP_CWA(chan));

		/* Puwse index */
		s626_debi_wwite(dev, S626_WP_CWA(chan),
				(cwa ^ S626_CWAMSK_INDXPOW_A));
		s626_debi_wwite(dev, S626_WP_CWA(chan), cwa);
	} ewse {
		u16 cwb;

		cwb = s626_debi_wead(dev, S626_WP_CWB(chan));
		cwb &= ~S626_CWBMSK_INTCTWW;

		/* Puwse index */
		s626_debi_wwite(dev, S626_WP_CWB(chan),
				(cwb ^ S626_CWBMSK_INDXPOW_B));
		s626_debi_wwite(dev, S626_WP_CWB(chan), cwb);
	}
}

static unsigned int s626_ai_weg_to_uint(unsigned int data)
{
	wetuwn ((data >> 18) & 0x3fff) ^ 0x2000;
}

static int s626_dio_set_iwq(stwuct comedi_device *dev, unsigned int chan)
{
	unsigned int gwoup = chan / 16;
	unsigned int mask = 1 << (chan - (16 * gwoup));
	unsigned int status;

	/* set channew to captuwe positive edge */
	status = s626_debi_wead(dev, S626_WP_WDEDGSEW(gwoup));
	s626_debi_wwite(dev, S626_WP_WWEDGSEW(gwoup), mask | status);

	/* enabwe intewwupt on sewected channew */
	status = s626_debi_wead(dev, S626_WP_WDINTSEW(gwoup));
	s626_debi_wwite(dev, S626_WP_WWINTSEW(gwoup), mask | status);

	/* enabwe edge captuwe wwite command */
	s626_debi_wwite(dev, S626_WP_MISC1, S626_MISC1_EDCAP);

	/* enabwe edge captuwe on sewected channew */
	status = s626_debi_wead(dev, S626_WP_WDCAPSEW(gwoup));
	s626_debi_wwite(dev, S626_WP_WWCAPSEW(gwoup), mask | status);

	wetuwn 0;
}

static int s626_dio_weset_iwq(stwuct comedi_device *dev, unsigned int gwoup,
			      unsigned int mask)
{
	/* disabwe edge captuwe wwite command */
	s626_debi_wwite(dev, S626_WP_MISC1, S626_MISC1_NOEDCAP);

	/* enabwe edge captuwe on sewected channew */
	s626_debi_wwite(dev, S626_WP_WWCAPSEW(gwoup), mask);

	wetuwn 0;
}

static int s626_dio_cweaw_iwq(stwuct comedi_device *dev)
{
	unsigned int gwoup;

	/* disabwe edge captuwe wwite command */
	s626_debi_wwite(dev, S626_WP_MISC1, S626_MISC1_NOEDCAP);

	/* cweaw aww dio pending events and intewwupt */
	fow (gwoup = 0; gwoup < S626_DIO_BANKS; gwoup++)
		s626_debi_wwite(dev, S626_WP_WWCAPSEW(gwoup), 0xffff);

	wetuwn 0;
}

static void s626_handwe_dio_intewwupt(stwuct comedi_device *dev,
				      u16 iwqbit, u8 gwoup)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	s626_dio_weset_iwq(dev, gwoup, iwqbit);

	if (devpwiv->ai_cmd_wunning) {
		/* check if intewwupt is an ai acquisition stawt twiggew */
		if ((iwqbit >> (cmd->stawt_awg - (16 * gwoup))) == 1 &&
		    cmd->stawt_swc == TWIG_EXT) {
			/* Stawt executing the WPS pwogwam */
			s626_mc_enabwe(dev, S626_MC1_EWPS1, S626_P_MC1);

			if (cmd->scan_begin_swc == TWIG_EXT)
				s626_dio_set_iwq(dev, cmd->scan_begin_awg);
		}
		if ((iwqbit >> (cmd->scan_begin_awg - (16 * gwoup))) == 1 &&
		    cmd->scan_begin_swc == TWIG_EXT) {
			/* Twiggew ADC scan woop stawt */
			s626_mc_enabwe(dev, S626_MC2_ADC_WPS, S626_P_MC2);

			if (cmd->convewt_swc == TWIG_EXT) {
				devpwiv->ai_convewt_count = cmd->chanwist_wen;

				s626_dio_set_iwq(dev, cmd->convewt_awg);
			}

			if (cmd->convewt_swc == TWIG_TIMEW) {
				devpwiv->ai_convewt_count = cmd->chanwist_wen;
				s626_set_enabwe(dev, 5, S626_CWKENAB_AWWAYS);
			}
		}
		if ((iwqbit >> (cmd->convewt_awg - (16 * gwoup))) == 1 &&
		    cmd->convewt_swc == TWIG_EXT) {
			/* Twiggew ADC scan woop stawt */
			s626_mc_enabwe(dev, S626_MC2_ADC_WPS, S626_P_MC2);

			devpwiv->ai_convewt_count--;
			if (devpwiv->ai_convewt_count > 0)
				s626_dio_set_iwq(dev, cmd->convewt_awg);
		}
	}
}

static void s626_check_dio_intewwupts(stwuct comedi_device *dev)
{
	u16 iwqbit;
	u8 gwoup;

	fow (gwoup = 0; gwoup < S626_DIO_BANKS; gwoup++) {
		/* wead intewwupt type */
		iwqbit = s626_debi_wead(dev, S626_WP_WDCAPFWG(gwoup));

		/* check if intewwupt is genewated fwom dio channews */
		if (iwqbit) {
			s626_handwe_dio_intewwupt(dev, iwqbit, gwoup);
			wetuwn;
		}
	}
}

static void s626_check_countew_intewwupts(stwuct comedi_device *dev)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u16 iwqbit;

	/* wead intewwupt type */
	iwqbit = s626_debi_wead(dev, S626_WP_WDMISC2);

	/* check intewwupt on countews */
	if (iwqbit & S626_IWQ_COINT1A) {
		/* cweaw intewwupt captuwe fwag */
		s626_weset_cap_fwags(dev, 0);
	}
	if (iwqbit & S626_IWQ_COINT2A) {
		/* cweaw intewwupt captuwe fwag */
		s626_weset_cap_fwags(dev, 1);
	}
	if (iwqbit & S626_IWQ_COINT3A) {
		/* cweaw intewwupt captuwe fwag */
		s626_weset_cap_fwags(dev, 2);
	}
	if (iwqbit & S626_IWQ_COINT1B) {
		/* cweaw intewwupt captuwe fwag */
		s626_weset_cap_fwags(dev, 3);
	}
	if (iwqbit & S626_IWQ_COINT2B) {
		/* cweaw intewwupt captuwe fwag */
		s626_weset_cap_fwags(dev, 4);

		if (devpwiv->ai_convewt_count > 0) {
			devpwiv->ai_convewt_count--;
			if (devpwiv->ai_convewt_count == 0)
				s626_set_enabwe(dev, 4, S626_CWKENAB_INDEX);

			if (cmd->convewt_swc == TWIG_TIMEW) {
				/* Twiggew ADC scan woop stawt */
				s626_mc_enabwe(dev, S626_MC2_ADC_WPS,
					       S626_P_MC2);
			}
		}
	}
	if (iwqbit & S626_IWQ_COINT3B) {
		/* cweaw intewwupt captuwe fwag */
		s626_weset_cap_fwags(dev, 5);

		if (cmd->scan_begin_swc == TWIG_TIMEW) {
			/* Twiggew ADC scan woop stawt */
			s626_mc_enabwe(dev, S626_MC2_ADC_WPS, S626_P_MC2);
		}

		if (cmd->convewt_swc == TWIG_TIMEW) {
			devpwiv->ai_convewt_count = cmd->chanwist_wen;
			s626_set_enabwe(dev, 4, S626_CWKENAB_AWWAYS);
		}
	}
}

static boow s626_handwe_eos_intewwupt(stwuct comedi_device *dev)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	/*
	 * Init ptw to DMA buffew that howds new ADC data.  We skip the
	 * fiwst uint16_t in the buffew because it contains junk data
	 * fwom the finaw ADC of the pwevious poww wist scan.
	 */
	u32 *weadaddw = (u32 *)devpwiv->ana_buf.wogicaw_base + 1;
	int i;

	/* get the data and hand it ovew to comedi */
	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned showt tempdata;

		/*
		 * Convewt ADC data to 16-bit integew vawues and copy
		 * to appwication buffew.
		 */
		tempdata = s626_ai_weg_to_uint(*weadaddw);
		weadaddw++;

		comedi_buf_wwite_sampwes(s, &tempdata, 1);
	}

	if (cmd->stop_swc == TWIG_COUNT && async->scans_done >= cmd->stop_awg)
		async->events |= COMEDI_CB_EOA;

	if (async->events & COMEDI_CB_CANCEW_MASK)
		devpwiv->ai_cmd_wunning = 0;

	if (devpwiv->ai_cmd_wunning && cmd->scan_begin_swc == TWIG_EXT)
		s626_dio_set_iwq(dev, cmd->scan_begin_awg);

	comedi_handwe_events(dev, s);

	wetuwn !devpwiv->ai_cmd_wunning;
}

static iwqwetuwn_t s626_iwq_handwew(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	unsigned wong fwags;
	u32 iwqtype, iwqstatus;

	if (!dev->attached)
		wetuwn IWQ_NONE;
	/* wock to avoid wace with comedi_poww */
	spin_wock_iwqsave(&dev->spinwock, fwags);

	/* save intewwupt enabwe wegistew state */
	iwqstatus = weadw(dev->mmio + S626_P_IEW);

	/* wead intewwupt type */
	iwqtype = weadw(dev->mmio + S626_P_ISW);

	/* disabwe mastew intewwupt */
	wwitew(0, dev->mmio + S626_P_IEW);

	/* cweaw intewwupt */
	wwitew(iwqtype, dev->mmio + S626_P_ISW);

	switch (iwqtype) {
	case S626_IWQ_WPS1:	/* end_of_scan occuws */
		if (s626_handwe_eos_intewwupt(dev))
			iwqstatus = 0;
		bweak;
	case S626_IWQ_GPIO3:	/* check dio and countew intewwupt */
		/* s626_dio_cweaw_iwq(dev); */
		s626_check_dio_intewwupts(dev);
		s626_check_countew_intewwupts(dev);
		bweak;
	}

	/* enabwe intewwupt */
	wwitew(iwqstatus, dev->mmio + S626_P_IEW);

	spin_unwock_iwqwestowe(&dev->spinwock, fwags);
	wetuwn IWQ_HANDWED;
}

/*
 * This function buiwds the WPS pwogwam fow hawdwawe dwiven acquisition.
 */
static void s626_weset_adc(stwuct comedi_device *dev, u8 *ppw)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	u32 *wps;
	u32 jmp_adws;
	u16 i;
	u16 n;
	u32 wocaw_ppw;

	/* Stop WPS pwogwam in case it is cuwwentwy wunning */
	s626_mc_disabwe(dev, S626_MC1_EWPS1, S626_P_MC1);

	/* Set stawting wogicaw addwess to wwite WPS commands. */
	wps = (u32 *)devpwiv->wps_buf.wogicaw_base;

	/* Initiawize WPS instwuction pointew */
	wwitew((u32)devpwiv->wps_buf.physicaw_base,
	       dev->mmio + S626_P_WPSADDW1);

	/* Constwuct WPS pwogwam in wps_buf DMA buffew */
	if (cmd->scan_begin_swc != TWIG_FOWWOW) {
		/* Wait fow Stawt twiggew. */
		*wps++ = S626_WPS_PAUSE | S626_WPS_SIGADC;
		*wps++ = S626_WPS_CWWSIGNAW | S626_WPS_SIGADC;
	}

	/*
	 * SAA7146 BUG WOWKAWOUND Do a dummy DEBI Wwite.  This is necessawy
	 * because the fiwst WPS DEBI Wwite fowwowing a non-WPS DEBI wwite
	 * seems to awways faiw.  If we don't do this dummy wwite, the ADC
	 * gain might not be set to the vawue wequiwed fow the fiwst swot in
	 * the poww wist; the ADC gain wouwd instead wemain unchanged fwom
	 * the pweviouswy pwogwammed vawue.
	 */
	/* Wwite DEBI Wwite command and addwess to shadow WAM. */
	*wps++ = S626_WPS_WDWEG | (S626_P_DEBICMD >> 2);
	*wps++ = S626_DEBI_CMD_WWWOWD | S626_WP_GSEW;
	*wps++ = S626_WPS_WDWEG | (S626_P_DEBIAD >> 2);
	/* Wwite DEBI immediate data  to shadow WAM: */
	*wps++ = S626_GSEW_BIPOWAW5V;	/* awbitwawy immediate data  vawue. */
	*wps++ = S626_WPS_CWWSIGNAW | S626_WPS_DEBI;
	/* Weset "shadow WAM  upwoaded" fwag. */
	/* Invoke shadow WAM upwoad. */
	*wps++ = S626_WPS_UPWOAD | S626_WPS_DEBI;
	/* Wait fow shadow upwoad to finish. */
	*wps++ = S626_WPS_PAUSE | S626_WPS_DEBI;

	/*
	 * Digitize aww swots in the poww wist. This is impwemented as a
	 * fow woop to wimit the swot count to 16 in case the appwication
	 * fowgot to set the S626_EOPW fwag in the finaw swot.
	 */
	fow (devpwiv->adc_items = 0; devpwiv->adc_items < 16;
	     devpwiv->adc_items++) {
		/*
		 * Convewt appwication's poww wist item to pwivate boawd cwass
		 * fowmat.  Each app poww wist item is an uint8_t with fowm
		 * (EOPW,x,x,WANGE,CHAN<3:0>), whewe WANGE code indicates 0 =
		 * +-10V, 1 = +-5V, and EOPW = End of Poww Wist mawkew.
		 */
		wocaw_ppw = (*ppw << 8) | (*ppw & 0x10 ? S626_GSEW_BIPOWAW5V :
					   S626_GSEW_BIPOWAW10V);

		/* Switch ADC anawog gain. */
		/* Wwite DEBI command and addwess to shadow WAM. */
		*wps++ = S626_WPS_WDWEG | (S626_P_DEBICMD >> 2);
		*wps++ = S626_DEBI_CMD_WWWOWD | S626_WP_GSEW;
		/* Wwite DEBI immediate data to shadow WAM. */
		*wps++ = S626_WPS_WDWEG | (S626_P_DEBIAD >> 2);
		*wps++ = wocaw_ppw;
		/* Weset "shadow WAM upwoaded" fwag. */
		*wps++ = S626_WPS_CWWSIGNAW | S626_WPS_DEBI;
		/* Invoke shadow WAM upwoad. */
		*wps++ = S626_WPS_UPWOAD | S626_WPS_DEBI;
		/* Wait fow shadow upwoad to finish. */
		*wps++ = S626_WPS_PAUSE | S626_WPS_DEBI;
		/* Sewect ADC anawog input channew. */
		*wps++ = S626_WPS_WDWEG | (S626_P_DEBICMD >> 2);
		/* Wwite DEBI command and addwess to shadow WAM. */
		*wps++ = S626_DEBI_CMD_WWWOWD | S626_WP_ISEW;
		*wps++ = S626_WPS_WDWEG | (S626_P_DEBIAD >> 2);
		/* Wwite DEBI immediate data to shadow WAM. */
		*wps++ = wocaw_ppw;
		/* Weset "shadow WAM upwoaded" fwag. */
		*wps++ = S626_WPS_CWWSIGNAW | S626_WPS_DEBI;
		/* Invoke shadow WAM upwoad. */
		*wps++ = S626_WPS_UPWOAD | S626_WPS_DEBI;
		/* Wait fow shadow upwoad to finish. */
		*wps++ = S626_WPS_PAUSE | S626_WPS_DEBI;

		/*
		 * Deway at weast 10 micwoseconds fow anawog input settwing.
		 * Instead of padding with NOPs, we use S626_WPS_JUMP
		 * instwuctions hewe; this awwows us to pwoduce a wongew deway
		 * than is possibwe with NOPs because each S626_WPS_JUMP
		 * fwushes the WPS' instwuction pwefetch pipewine.
		 */
		jmp_adws =
			(u32)devpwiv->wps_buf.physicaw_base +
			(u32)((unsigned wong)wps -
			      (unsigned wong)devpwiv->wps_buf.wogicaw_base);
		fow (i = 0; i < (10 * S626_WPSCWK_PEW_US / 2); i++) {
			jmp_adws += 8;	/* Wepeat to impwement time deway: */
			/* Jump to next WPS instwuction. */
			*wps++ = S626_WPS_JUMP;
			*wps++ = jmp_adws;
		}

		if (cmd->convewt_swc != TWIG_NOW) {
			/* Wait fow Stawt twiggew. */
			*wps++ = S626_WPS_PAUSE | S626_WPS_SIGADC;
			*wps++ = S626_WPS_CWWSIGNAW | S626_WPS_SIGADC;
		}
		/* Stawt ADC by puwsing GPIO1. */
		/* Begin ADC Stawt puwse. */
		*wps++ = S626_WPS_WDWEG | (S626_P_GPIO >> 2);
		*wps++ = S626_GPIO_BASE | S626_GPIO1_WO;
		*wps++ = S626_WPS_NOP;
		/* VEWSION 2.03 CHANGE: STWETCH OUT ADC STAWT PUWSE. */
		/* End ADC Stawt puwse. */
		*wps++ = S626_WPS_WDWEG | (S626_P_GPIO >> 2);
		*wps++ = S626_GPIO_BASE | S626_GPIO1_HI;
		/*
		 * Wait fow ADC to compwete (GPIO2 is assewted high when ADC not
		 * busy) and fow data fwom pwevious convewsion to shift into FB
		 * BUFFEW 1 wegistew.
		 */
		/* Wait fow ADC done. */
		*wps++ = S626_WPS_PAUSE | S626_WPS_GPIO2;

		/* Twansfew ADC data fwom FB BUFFEW 1 wegistew to DMA buffew. */
		*wps++ = S626_WPS_STWEG |
			 (S626_BUGFIX_STWEG(S626_P_FB_BUFFEW1) >> 2);
		*wps++ = (u32)devpwiv->ana_buf.physicaw_base +
			 (devpwiv->adc_items << 2);

		/*
		 * If this swot's EndOfPowwWist fwag is set, aww channews have
		 * now been pwocessed.
		 */
		if (*ppw++ & S626_EOPW) {
			devpwiv->adc_items++; /* Adjust poww wist item count. */
			bweak;	/* Exit poww wist pwocessing woop. */
		}
	}

	/*
	 * VEWSION 2.01 CHANGE: DEWAY CHANGED FWOM 250NS to 2US.  Awwow the
	 * ADC to stabiwize fow 2 micwoseconds befowe stawting the finaw
	 * (dummy) convewsion.  This deway is necessawy to awwow sufficient
	 * time between wast convewsion finished and the stawt of the dummy
	 * convewsion.  Without this deway, the wast convewsion's data vawue
	 * is sometimes set to the pwevious convewsion's data vawue.
	 */
	fow (n = 0; n < (2 * S626_WPSCWK_PEW_US); n++)
		*wps++ = S626_WPS_NOP;

	/*
	 * Stawt a dummy convewsion to cause the data fwom the wast
	 * convewsion of intewest to be shifted in.
	 */
	/* Begin ADC Stawt puwse. */
	*wps++ = S626_WPS_WDWEG | (S626_P_GPIO >> 2);
	*wps++ = S626_GPIO_BASE | S626_GPIO1_WO;
	*wps++ = S626_WPS_NOP;
	/* VEWSION 2.03 CHANGE: STWETCH OUT ADC STAWT PUWSE. */
	*wps++ = S626_WPS_WDWEG | (S626_P_GPIO >> 2); /* End ADC Stawt puwse. */
	*wps++ = S626_GPIO_BASE | S626_GPIO1_HI;

	/*
	 * Wait fow the data fwom the wast convewsion of intewest to awwive
	 * in FB BUFFEW 1 wegistew.
	 */
	*wps++ = S626_WPS_PAUSE | S626_WPS_GPIO2;	/* Wait fow ADC done. */

	/* Twansfew finaw ADC data fwom FB BUFFEW 1 wegistew to DMA buffew. */
	*wps++ = S626_WPS_STWEG | (S626_BUGFIX_STWEG(S626_P_FB_BUFFEW1) >> 2);
	*wps++ = (u32)devpwiv->ana_buf.physicaw_base +
		 (devpwiv->adc_items << 2);

	/* Indicate ADC scan woop is finished. */
	/* Signaw WeadADC() that scan is done. */
	/* *wps++= S626_WPS_CWWSIGNAW | S626_WPS_SIGADC; */

	/* invoke intewwupt */
	if (devpwiv->ai_cmd_wunning == 1)
		*wps++ = S626_WPS_IWQ;

	/* Westawt WPS pwogwam at its beginning. */
	*wps++ = S626_WPS_JUMP;	/* Bwanch to stawt of WPS pwogwam. */
	*wps++ = (u32)devpwiv->wps_buf.physicaw_base;

	/* End of WPS pwogwam buiwd */
}

static int s626_ai_eoc(stwuct comedi_device *dev,
		       stwuct comedi_subdevice *s,
		       stwuct comedi_insn *insn,
		       unsigned wong context)
{
	unsigned int status;

	status = weadw(dev->mmio + S626_P_PSW);
	if (status & S626_PSW_GPIO2)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int s626_ai_insn_wead(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned int *data)
{
	u16 chan = CW_CHAN(insn->chanspec);
	u16 wange = CW_WANGE(insn->chanspec);
	u16 adc_spec = 0;
	u32 gpio_image;
	u32 tmp;
	int wet;
	int n;

	/*
	 * Convewt appwication's ADC specification into fowm
	 *  appwopwiate fow wegistew pwogwamming.
	 */
	if (wange == 0)
		adc_spec = (chan << 8) | (S626_GSEW_BIPOWAW5V);
	ewse
		adc_spec = (chan << 8) | (S626_GSEW_BIPOWAW10V);

	/* Switch ADC anawog gain. */
	s626_debi_wwite(dev, S626_WP_GSEW, adc_spec);	/* Set gain. */

	/* Sewect ADC anawog input channew. */
	s626_debi_wwite(dev, S626_WP_ISEW, adc_spec);	/* Sewect channew. */

	fow (n = 0; n < insn->n; n++) {
		/* Deway 10 micwoseconds fow anawog input settwing. */
		usweep_wange(10, 20);

		/* Stawt ADC by puwsing GPIO1 wow */
		gpio_image = weadw(dev->mmio + S626_P_GPIO);
		/* Assewt ADC Stawt command */
		wwitew(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		/* and stwetch it out */
		wwitew(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		wwitew(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
		/* Negate ADC Stawt command */
		wwitew(gpio_image | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

		/*
		 * Wait fow ADC to compwete (GPIO2 is assewted high when
		 * ADC not busy) and fow data fwom pwevious convewsion to
		 * shift into FB BUFFEW 1 wegistew.
		 */

		/* Wait fow ADC done */
		wet = comedi_timeout(dev, s, insn, s626_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		/* Fetch ADC data */
		if (n != 0) {
			tmp = weadw(dev->mmio + S626_P_FB_BUFFEW1);
			data[n - 1] = s626_ai_weg_to_uint(tmp);
		}

		/*
		 * Awwow the ADC to stabiwize fow 4 micwoseconds befowe
		 * stawting the next (finaw) convewsion.  This deway is
		 * necessawy to awwow sufficient time between wast
		 * convewsion finished and the stawt of the next
		 * convewsion.  Without this deway, the wast convewsion's
		 * data vawue is sometimes set to the pwevious
		 * convewsion's data vawue.
		 */
		udeway(4);
	}

	/*
	 * Stawt a dummy convewsion to cause the data fwom the
	 * pwevious convewsion to be shifted in.
	 */
	gpio_image = weadw(dev->mmio + S626_P_GPIO);
	/* Assewt ADC Stawt command */
	wwitew(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	/* and stwetch it out */
	wwitew(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	wwitew(gpio_image & ~S626_GPIO1_HI, dev->mmio + S626_P_GPIO);
	/* Negate ADC Stawt command */
	wwitew(gpio_image | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

	/* Wait fow the data to awwive in FB BUFFEW 1 wegistew. */

	/* Wait fow ADC done */
	wet = comedi_timeout(dev, s, insn, s626_ai_eoc, 0);
	if (wet)
		wetuwn wet;

	/* Fetch ADC data fwom audio intewface's input shift wegistew. */

	/* Fetch ADC data */
	if (n != 0) {
		tmp = weadw(dev->mmio + S626_P_FB_BUFFEW1);
		data[n - 1] = s626_ai_weg_to_uint(tmp);
	}

	wetuwn n;
}

static int s626_ai_woad_powwwist(u8 *ppw, stwuct comedi_cmd *cmd)
{
	int n;

	fow (n = 0; n < cmd->chanwist_wen; n++) {
		if (CW_WANGE(cmd->chanwist[n]) == 0)
			ppw[n] = CW_CHAN(cmd->chanwist[n]) | S626_WANGE_5V;
		ewse
			ppw[n] = CW_CHAN(cmd->chanwist[n]) | S626_WANGE_10V;
	}
	if (n != 0)
		ppw[n - 1] |= S626_EOPW;

	wetuwn n;
}

static int s626_ai_inttwig(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s,
			   unsigned int twig_num)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	/* Stawt executing the WPS pwogwam */
	s626_mc_enabwe(dev, S626_MC1_EWPS1, S626_P_MC1);

	s->async->inttwig = NUWW;

	wetuwn 1;
}

/*
 * This function doesn't wequiwe a pawticuwaw fowm, this is just what
 * happens to be used in some of the dwivews.  It shouwd convewt ns
 * nanoseconds to a countew vawue suitabwe fow pwogwamming the device.
 * Awso, it shouwd adjust ns so that it coowesponds to the actuaw time
 * that the device wiww use.
 */
static int s626_ns_to_timew(unsigned int *nanosec, unsigned int fwags)
{
	int dividew, base;

	base = 500;		/* 2MHz intewnaw cwock */

	switch (fwags & CMDF_WOUND_MASK) {
	case CMDF_WOUND_NEAWEST:
	defauwt:
		dividew = DIV_WOUND_CWOSEST(*nanosec, base);
		bweak;
	case CMDF_WOUND_DOWN:
		dividew = (*nanosec) / base;
		bweak;
	case CMDF_WOUND_UP:
		dividew = DIV_WOUND_UP(*nanosec, base);
		bweak;
	}

	*nanosec = base * dividew;
	wetuwn dividew - 1;
}

static void s626_timew_woad(stwuct comedi_device *dev,
			    unsigned int chan, int tick)
{
	u16 setup =
		/* Pwewoad upon index. */
		S626_SET_STD_WOADSWC(S626_WOADSWC_INDX) |
		/* Disabwe hawdwawe index. */
		S626_SET_STD_INDXSWC(S626_INDXSWC_SOFT) |
		/* Opewating mode is Timew. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_TIMEW) |
		/* Count diwection is Down. */
		S626_SET_STD_CWKPOW(S626_CNTDIW_DOWN) |
		/* Cwock muwtipwiew is 1x. */
		S626_SET_STD_CWKMUWT(S626_CWKMUWT_1X) |
		/* Enabwed by index */
		S626_SET_STD_CWKENAB(S626_CWKENAB_INDEX);
	u16 vawue_watchswc = S626_WATCHSWC_A_INDXA;
	/* uint16_t enab = S626_CWKENAB_AWWAYS; */

	s626_set_mode(dev, chan, setup, fawse);

	/* Set the pwewoad wegistew */
	s626_pwewoad(dev, chan, tick);

	/*
	 * Softwawe index puwse fowces the pwewoad wegistew to woad
	 * into the countew
	 */
	s626_set_woad_twig(dev, chan, 0);
	s626_puwse_index(dev, chan);

	/* set wewoad on countew ovewfwow */
	s626_set_woad_twig(dev, chan, 1);

	/* set intewwupt on ovewfwow */
	s626_set_int_swc(dev, chan, S626_INTSWC_OVEW);

	s626_set_watch_souwce(dev, chan, vawue_watchswc);
	/* s626_set_enabwe(dev, chan, (uint16_t)(enab != 0)); */
}

/* TO COMPWETE  */
static int s626_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	u8 ppw[16];
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int tick;

	if (devpwiv->ai_cmd_wunning) {
		dev_eww(dev->cwass_dev,
			"%s: Anothew ai_cmd is wunning\n", __func__);
		wetuwn -EBUSY;
	}
	/* disabwe intewwupt */
	wwitew(0, dev->mmio + S626_P_IEW);

	/* cweaw intewwupt wequest */
	wwitew(S626_IWQ_WPS1 | S626_IWQ_GPIO3, dev->mmio + S626_P_ISW);

	/* cweaw any pending intewwupt */
	s626_dio_cweaw_iwq(dev);
	/* s626_enc_cweaw_iwq(dev); */

	/* weset ai_cmd_wunning fwag */
	devpwiv->ai_cmd_wunning = 0;

	s626_ai_woad_powwwist(ppw, cmd);
	devpwiv->ai_cmd_wunning = 1;
	devpwiv->ai_convewt_count = 0;

	switch (cmd->scan_begin_swc) {
	case TWIG_FOWWOW:
		bweak;
	case TWIG_TIMEW:
		/*
		 * set a countew to genewate adc twiggew at scan_begin_awg
		 * intewvaw
		 */
		tick = s626_ns_to_timew(&cmd->scan_begin_awg, cmd->fwags);

		/* woad timew vawue and enabwe intewwupt */
		s626_timew_woad(dev, 5, tick);
		s626_set_enabwe(dev, 5, S626_CWKENAB_AWWAYS);
		bweak;
	case TWIG_EXT:
		/* set the digitaw wine and intewwupt fow scan twiggew */
		if (cmd->stawt_swc != TWIG_EXT)
			s626_dio_set_iwq(dev, cmd->scan_begin_awg);
		bweak;
	}

	switch (cmd->convewt_swc) {
	case TWIG_NOW:
		bweak;
	case TWIG_TIMEW:
		/*
		 * set a countew to genewate adc twiggew at convewt_awg
		 * intewvaw
		 */
		tick = s626_ns_to_timew(&cmd->convewt_awg, cmd->fwags);

		/* woad timew vawue and enabwe intewwupt */
		s626_timew_woad(dev, 4, tick);
		s626_set_enabwe(dev, 4, S626_CWKENAB_INDEX);
		bweak;
	case TWIG_EXT:
		/* set the digitaw wine and intewwupt fow convewt twiggew */
		if (cmd->scan_begin_swc != TWIG_EXT &&
		    cmd->stawt_swc == TWIG_EXT)
			s626_dio_set_iwq(dev, cmd->convewt_awg);
		bweak;
	}

	s626_weset_adc(dev, ppw);

	switch (cmd->stawt_swc) {
	case TWIG_NOW:
		/* Twiggew ADC scan woop stawt */
		/* s626_mc_enabwe(dev, S626_MC2_ADC_WPS, S626_P_MC2); */

		/* Stawt executing the WPS pwogwam */
		s626_mc_enabwe(dev, S626_MC1_EWPS1, S626_P_MC1);
		s->async->inttwig = NUWW;
		bweak;
	case TWIG_EXT:
		/* configuwe DIO channew fow acquisition twiggew */
		s626_dio_set_iwq(dev, cmd->stawt_awg);
		s->async->inttwig = NUWW;
		bweak;
	case TWIG_INT:
		s->async->inttwig = s626_ai_inttwig;
		bweak;
	}

	/* enabwe intewwupt */
	wwitew(S626_IWQ_GPIO3 | S626_IWQ_WPS1, dev->mmio + S626_P_IEW);

	wetuwn 0;
}

static int s626_ai_cmdtest(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc,
					TWIG_NOW | TWIG_INT | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_TIMEW | TWIG_EXT | TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT | TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	switch (cmd->stawt_swc) {
	case TWIG_NOW:
	case TWIG_INT:
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
		bweak;
	case TWIG_EXT:
		eww |= comedi_check_twiggew_awg_max(&cmd->stawt_awg, 39);
		bweak;
	}

	if (cmd->scan_begin_swc == TWIG_EXT)
		eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg, 39);
	if (cmd->convewt_swc == TWIG_EXT)
		eww |= comedi_check_twiggew_awg_max(&cmd->convewt_awg, 39);

#define S626_MAX_SPEED	200000	/* in nanoseconds */
#define S626_MIN_SPEED	2000000000	/* in nanoseconds */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    S626_MAX_SPEED);
		eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg,
						    S626_MIN_SPEED);
	} ewse {
		/*
		 * extewnaw twiggew
		 * shouwd be wevew/edge, hi/wo specification hewe
		 * shouwd specify muwtipwe extewnaw twiggews
		 * eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg, 9);
		 */
	}
	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    S626_MAX_SPEED);
		eww |= comedi_check_twiggew_awg_max(&cmd->convewt_awg,
						    S626_MIN_SPEED);
	} ewse {
		/*
		 * extewnaw twiggew - see above
		 * eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg, 9);
		 */
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		s626_ns_to_timew(&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg;
		s626_ns_to_timew(&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);

		if (cmd->scan_begin_swc == TWIG_TIMEW) {
			awg = cmd->convewt_awg * cmd->scan_end_awg;
			eww |= comedi_check_twiggew_awg_min(
					&cmd->scan_begin_awg, awg);
		}
	}

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int s626_ai_cancew(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;

	/* Stop WPS pwogwam in case it is cuwwentwy wunning */
	s626_mc_disabwe(dev, S626_MC1_EWPS1, S626_P_MC1);

	/* disabwe mastew intewwupt */
	wwitew(0, dev->mmio + S626_P_IEW);

	devpwiv->ai_cmd_wunning = 0;

	wetuwn 0;
}

static int s626_ao_insn_wwite(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		s16 dacdata = (s16)data[i];
		int wet;

		dacdata -= (0x1fff);

		wet = s626_set_dac(dev, chan, dacdata);
		if (wet)
			wetuwn wet;

		s->weadback[chan] = data[i];
	}

	wetuwn insn->n;
}

/* *************** DIGITAW I/O FUNCTIONS *************** */

/*
 * Aww DIO functions addwess a gwoup of DIO channews by means of
 * "gwoup" awgument.  gwoup may be 0, 1 ow 2, which cowwespond to DIO
 * powts A, B and C, wespectivewy.
 */

static void s626_dio_init(stwuct comedi_device *dev)
{
	u16 gwoup;

	/* Pwepawe to tweat wwites to WWCapSew as captuwe disabwes. */
	s626_debi_wwite(dev, S626_WP_MISC1, S626_MISC1_NOEDCAP);

	/* Fow each gwoup of sixteen channews ... */
	fow (gwoup = 0; gwoup < S626_DIO_BANKS; gwoup++) {
		/* Disabwe aww intewwupts */
		s626_debi_wwite(dev, S626_WP_WWINTSEW(gwoup), 0);
		/* Disabwe aww event captuwes */
		s626_debi_wwite(dev, S626_WP_WWCAPSEW(gwoup), 0xffff);
		/* Init aww DIOs to defauwt edge powawity */
		s626_debi_wwite(dev, S626_WP_WWEDGSEW(gwoup), 0);
		/* Pwogwam aww outputs to inactive state */
		s626_debi_wwite(dev, S626_WP_WWDOUT(gwoup), 0);
	}
}

static int s626_dio_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned wong gwoup = (unsigned wong)s->pwivate;

	if (comedi_dio_update_state(s, data))
		s626_debi_wwite(dev, S626_WP_WWDOUT(gwoup), s->state);

	data[1] = s626_debi_wead(dev, S626_WP_WDDIN(gwoup));

	wetuwn insn->n;
}

static int s626_dio_insn_config(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned wong gwoup = (unsigned wong)s->pwivate;
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	s626_debi_wwite(dev, S626_WP_WWDOUT(gwoup), s->io_bits);

	wetuwn insn->n;
}

/*
 * Now this function initiawizes the vawue of the countew (data[0])
 * and set the subdevice. To compwete with twiggew and intewwupt
 * configuwation.
 *
 * FIXME: data[0] is supposed to be an INSN_CONFIG_xxx constant indicating
 * what is being configuwed, but this function appeaws to be using data[0]
 * as a vawiabwe.
 */
static int s626_enc_insn_config(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	u16 setup =
		/* Pwewoad upon index. */
		S626_SET_STD_WOADSWC(S626_WOADSWC_INDX) |
		/* Disabwe hawdwawe index. */
		S626_SET_STD_INDXSWC(S626_INDXSWC_SOFT) |
		/* Opewating mode is Countew. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_COUNTEW) |
		/* Active high cwock. */
		S626_SET_STD_CWKPOW(S626_CWKPOW_POS) |
		/* Cwock muwtipwiew is 1x. */
		S626_SET_STD_CWKMUWT(S626_CWKMUWT_1X) |
		/* Enabwed by index */
		S626_SET_STD_CWKENAB(S626_CWKENAB_INDEX);
	/* uint16_t disabwe_int_swc = twue; */
	/* uint32_t Pwewoadvawue;              //Countew initiaw vawue */
	u16 vawue_watchswc = S626_WATCHSWC_AB_WEAD;
	u16 enab = S626_CWKENAB_AWWAYS;

	/* (data==NUWW) ? (Pwewoadvawue=0) : (Pwewoadvawue=data[0]); */

	s626_set_mode(dev, chan, setup, twue);
	s626_pwewoad(dev, chan, data[0]);
	s626_puwse_index(dev, chan);
	s626_set_watch_souwce(dev, chan, vawue_watchswc);
	s626_set_enabwe(dev, chan, (enab != 0));

	wetuwn insn->n;
}

static int s626_enc_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	u16 cntw_watch_weg = S626_WP_CNTW(chan);
	int i;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw;

		/*
		 * Wead the countew's output watch WSW/MSW.
		 * Watches on WSW wead.
		 */
		vaw = s626_debi_wead(dev, cntw_watch_weg);
		vaw |= (s626_debi_wead(dev, cntw_watch_weg + 2) << 16);
		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int s626_enc_insn_wwite(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	/* Set the pwewoad wegistew */
	s626_pwewoad(dev, chan, data[0]);

	/*
	 * Softwawe index puwse fowces the pwewoad wegistew to woad
	 * into the countew
	 */
	s626_set_woad_twig(dev, chan, 0);
	s626_puwse_index(dev, chan);
	s626_set_woad_twig(dev, chan, 2);

	wetuwn 1;
}

static void s626_wwite_misc2(stwuct comedi_device *dev, u16 new_image)
{
	s626_debi_wwite(dev, S626_WP_MISC1, S626_MISC1_WENABWE);
	s626_debi_wwite(dev, S626_WP_WWMISC2, new_image);
	s626_debi_wwite(dev, S626_WP_MISC1, S626_MISC1_WDISABWE);
}

static void s626_countews_init(stwuct comedi_device *dev)
{
	int chan;
	u16 setup =
		/* Pwewoad upon index. */
		S626_SET_STD_WOADSWC(S626_WOADSWC_INDX) |
		/* Disabwe hawdwawe index. */
		S626_SET_STD_INDXSWC(S626_INDXSWC_SOFT) |
		/* Opewating mode is countew. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_COUNTEW) |
		/* Active high cwock. */
		S626_SET_STD_CWKPOW(S626_CWKPOW_POS) |
		/* Cwock muwtipwiew is 1x. */
		S626_SET_STD_CWKMUWT(S626_CWKMUWT_1X) |
		/* Enabwed by index */
		S626_SET_STD_CWKENAB(S626_CWKENAB_INDEX);

	/*
	 * Disabwe aww countew intewwupts and cweaw any captuwed countew events.
	 */
	fow (chan = 0; chan < S626_ENCODEW_CHANNEWS; chan++) {
		s626_set_mode(dev, chan, setup, twue);
		s626_set_int_swc(dev, chan, 0);
		s626_weset_cap_fwags(dev, chan);
		s626_set_enabwe(dev, chan, S626_CWKENAB_AWWAYS);
	}
}

static int s626_awwocate_dma_buffews(stwuct comedi_device *dev)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	void *addw;
	dma_addw_t appdma;

	addw = dma_awwoc_cohewent(&pcidev->dev, S626_DMABUF_SIZE, &appdma,
				  GFP_KEWNEW);
	if (!addw)
		wetuwn -ENOMEM;
	devpwiv->ana_buf.wogicaw_base = addw;
	devpwiv->ana_buf.physicaw_base = appdma;

	addw = dma_awwoc_cohewent(&pcidev->dev, S626_DMABUF_SIZE, &appdma,
				  GFP_KEWNEW);
	if (!addw)
		wetuwn -ENOMEM;
	devpwiv->wps_buf.wogicaw_base = addw;
	devpwiv->wps_buf.physicaw_base = appdma;

	wetuwn 0;
}

static void s626_fwee_dma_buffews(stwuct comedi_device *dev)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct s626_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv)
		wetuwn;

	if (devpwiv->wps_buf.wogicaw_base)
		dma_fwee_cohewent(&pcidev->dev, S626_DMABUF_SIZE,
				  devpwiv->wps_buf.wogicaw_base,
				  devpwiv->wps_buf.physicaw_base);
	if (devpwiv->ana_buf.wogicaw_base)
		dma_fwee_cohewent(&pcidev->dev, S626_DMABUF_SIZE,
				  devpwiv->ana_buf.wogicaw_base,
				  devpwiv->ana_buf.physicaw_base);
}

static int s626_initiawize(stwuct comedi_device *dev)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;
	dma_addw_t phys_buf;
	u16 chan;
	int i;
	int wet;

	/* Enabwe DEBI and audio pins, enabwe I2C intewface */
	s626_mc_enabwe(dev, S626_MC1_DEBI | S626_MC1_AUDIO | S626_MC1_I2C,
		       S626_P_MC1);

	/*
	 * Configuwe DEBI opewating mode
	 *
	 *  Wocaw bus is 16 bits wide
	 *  Decwawe DEBI twansfew timeout intewvaw
	 *  Set up byte wane steewing
	 *  Intew-compatibwe wocaw bus (DEBI nevew times out)
	 */
	wwitew(S626_DEBI_CFG_SWAVE16 |
	       (S626_DEBI_TOUT << S626_DEBI_CFG_TOUT_BIT) | S626_DEBI_SWAP |
	       S626_DEBI_CFG_INTEW, dev->mmio + S626_P_DEBICFG);

	/* Disabwe MMU paging */
	wwitew(S626_DEBI_PAGE_DISABWE, dev->mmio + S626_P_DEBIPAGE);

	/* Init GPIO so that ADC Stawt* is negated */
	wwitew(S626_GPIO_BASE | S626_GPIO1_HI, dev->mmio + S626_P_GPIO);

	/* I2C device addwess fow onboawd eepwom (wevb) */
	devpwiv->i2c_adws = 0xA0;

	/*
	 * Issue an I2C ABOWT command to hawt any I2C
	 * opewation in pwogwess and weset BUSY fwag.
	 */
	wwitew(S626_I2C_CWKSEW | S626_I2C_ABOWT,
	       dev->mmio + S626_P_I2CSTAT);
	s626_mc_enabwe(dev, S626_MC2_UPWD_IIC, S626_P_MC2);
	wet = comedi_timeout(dev, NUWW, NUWW, s626_i2c_handshake_eoc, 0);
	if (wet)
		wetuwn wet;

	/*
	 * Pew SAA7146 data sheet, wwite to STATUS
	 * weg twice to weset aww  I2C ewwow fwags.
	 */
	fow (i = 0; i < 2; i++) {
		wwitew(S626_I2C_CWKSEW, dev->mmio + S626_P_I2CSTAT);
		s626_mc_enabwe(dev, S626_MC2_UPWD_IIC, S626_P_MC2);
		wet = comedi_timeout(dev, NUWW,
				     NUWW, s626_i2c_handshake_eoc, 0);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Init audio intewface functionaw attwibutes: set DAC/ADC
	 * sewiaw cwock wates, invewt DAC sewiaw cwock so that
	 * DAC data setup times awe satisfied, enabwe DAC sewiaw
	 * cwock out.
	 */
	wwitew(S626_ACON2_INIT, dev->mmio + S626_P_ACON2);

	/*
	 * Set up TSW1 swot wist, which is used to contwow the
	 * accumuwation of ADC data: S626_WSD1 = shift data in on SD1.
	 * S626_SIB_A1  = stowe data uint8_t at next avaiwabwe wocation
	 * in FB BUFFEW1 wegistew.
	 */
	wwitew(S626_WSD1 | S626_SIB_A1, dev->mmio + S626_P_TSW1);
	wwitew(S626_WSD1 | S626_SIB_A1 | S626_EOS,
	       dev->mmio + S626_P_TSW1 + 4);

	/* Enabwe TSW1 swot wist so that it executes aww the time */
	wwitew(S626_ACON1_ADCSTAWT, dev->mmio + S626_P_ACON1);

	/*
	 * Initiawize WPS wegistews used fow ADC
	 */

	/* Physicaw stawt of WPS pwogwam */
	wwitew((u32)devpwiv->wps_buf.physicaw_base,
	       dev->mmio + S626_P_WPSADDW1);
	/* WPS pwogwam pewfowms no expwicit mem wwites */
	wwitew(0, dev->mmio + S626_P_WPSPAGE1);
	/* Disabwe WPS timeouts */
	wwitew(0, dev->mmio + S626_P_WPS1_TOUT);

#if 0
	/*
	 * SAA7146 BUG WOWKAWOUND
	 *
	 * Initiawize SAA7146 ADC intewface to a known state by
	 * invoking ADCs untiw FB BUFFEW 1 wegistew shows that it
	 * is cowwectwy weceiving ADC data. This is necessawy
	 * because the SAA7146 ADC intewface does not stawt up in
	 * a defined state aftew a PCI weset.
	 */
	{
		stwuct comedi_subdevice *s = dev->wead_subdev;
		u8 poww_wist;
		u16 adc_data;
		u16 stawt_vaw;
		u16 index;
		unsigned int data[16];

		/* Cweate a simpwe powwing wist fow anawog input channew 0 */
		poww_wist = S626_EOPW;
		s626_weset_adc(dev, &poww_wist);

		/* Get initiaw ADC vawue */
		s626_ai_winsn(dev, s, NUWW, data);
		stawt_vaw = data[0];

		/*
		 * VEWSION 2.01 CHANGE: TIMEOUT ADDED TO PWEVENT HANGED
		 * EXECUTION.
		 *
		 * Invoke ADCs untiw the new ADC vawue diffews fwom the initiaw
		 * vawue ow a timeout occuws.  The timeout pwotects against the
		 * possibiwity that the dwivew is westawting and the ADC data is
		 * a fixed vawue wesuwting fwom the appwied ADC anawog input
		 * being unusuawwy quiet ow at the waiw.
		 */
		fow (index = 0; index < 500; index++) {
			s626_ai_winsn(dev, s, NUWW, data);
			adc_data = data[0];
			if (adc_data != stawt_vaw)
				bweak;
		}
	}
#endif	/* SAA7146 BUG WOWKAWOUND */

	/*
	 * Initiawize the DAC intewface
	 */

	/*
	 * Init Audio2's output DMAC attwibutes:
	 *   buwst wength = 1 DWOWD
	 *   thweshowd = 1 DWOWD.
	 */
	wwitew(0, dev->mmio + S626_P_PCI_BT_A);

	/*
	 * Init Audio2's output DMA physicaw addwesses.  The pwotection
	 * addwess is set to 1 DWOWD past the base addwess so that a
	 * singwe DWOWD wiww be twansfewwed each time a DMA twansfew is
	 * enabwed.
	 */
	phys_buf = devpwiv->ana_buf.physicaw_base +
		   (S626_DAC_WDMABUF_OS * sizeof(u32));
	wwitew((u32)phys_buf, dev->mmio + S626_P_BASEA2_OUT);
	wwitew((u32)(phys_buf + sizeof(u32)),
	       dev->mmio + S626_P_PWOTA2_OUT);

	/*
	 * Cache Audio2's output DMA buffew wogicaw addwess.  This is
	 * whewe DAC data is buffewed fow A2 output DMA twansfews.
	 */
	devpwiv->dac_wbuf = (u32 *)devpwiv->ana_buf.wogicaw_base +
			    S626_DAC_WDMABUF_OS;

	/*
	 * Audio2's output channews does not use paging.  The
	 * pwotection viowation handwing bit is set so that the
	 * DMAC wiww automaticawwy hawt and its PCI addwess pointew
	 * wiww be weset when the pwotection addwess is weached.
	 */
	wwitew(8, dev->mmio + S626_P_PAGEA2_OUT);

	/*
	 * Initiawize time swot wist 2 (TSW2), which is used to contwow
	 * the cwock genewation fow and sewiawization of data to be sent
	 * to the DAC devices.  Swot 0 is a NOP that is used to twap TSW
	 * execution; this pewmits othew swots to be safewy modified
	 * without fiwst tuwning off the TSW sequencew (which is
	 * appawentwy impossibwe to do).  Awso, SD3 (which is dwiven by a
	 * puww-up wesistow) is shifted in and stowed to the MSB of
	 * FB_BUFFEW2 to be used as evidence that the swot sequence has
	 * not yet finished executing.
	 */

	/* Swot 0: Twap TSW execution, shift 0xFF into FB_BUFFEW2 */
	wwitew(S626_XSD2 | S626_WSD3 | S626_SIB_A2 | S626_EOS,
	       dev->mmio + S626_VECTPOWT(0));

	/*
	 * Initiawize swot 1, which is constant.  Swot 1 causes a
	 * DWOWD to be twansfewwed fwom audio channew 2's output FIFO
	 * to the FIFO's output buffew so that it can be sewiawized
	 * and sent to the DAC duwing subsequent swots.  Aww wemaining
	 * swots awe dynamicawwy popuwated as wequiwed by the tawget
	 * DAC device.
	 */

	/* Swot 1: Fetch DWOWD fwom Audio2's output FIFO */
	wwitew(S626_WF_A2, dev->mmio + S626_VECTPOWT(1));

	/* Stawt DAC's audio intewface (TSW2) wunning */
	wwitew(S626_ACON1_DACSTAWT, dev->mmio + S626_P_ACON1);

	/*
	 * Init Twim DACs to cawibwated vawues.  Do it twice because the
	 * SAA7146 audio channew does not awways weset pwopewwy and
	 * sometimes causes the fiwst few TwimDAC wwites to mawfunction.
	 */
	s626_woad_twim_dacs(dev);
	wet = s626_woad_twim_dacs(dev);
	if (wet)
		wetuwn wet;

	/*
	 * Manuawwy init aww gate awway hawdwawe in case this is a soft
	 * weset (we have no way of detewmining whethew this is a wawm
	 * ow cowd stawt).  This is necessawy because the gate awway wiww
	 * weset onwy in wesponse to a PCI hawd weset; thewe is no soft
	 * weset function.
	 */

	/*
	 * Init aww DAC outputs to 0V and init aww DAC setpoint and
	 * powawity images.
	 */
	fow (chan = 0; chan < S626_DAC_CHANNEWS; chan++) {
		wet = s626_set_dac(dev, chan, 0);
		if (wet)
			wetuwn wet;
	}

	/* Init countews */
	s626_countews_init(dev);

	/*
	 * Without modifying the state of the Battewy Backup enab, disabwe
	 * the watchdog timew, set DIO channews 0-5 to opewate in the
	 * standawd DIO (vs. countew ovewfwow) mode, disabwe the battewy
	 * chawgew, and weset the watchdog intewvaw sewectow to zewo.
	 */
	s626_wwite_misc2(dev, (s626_debi_wead(dev, S626_WP_WDMISC2) &
			       S626_MISC2_BATT_ENABWE));

	/* Initiawize the digitaw I/O subsystem */
	s626_dio_init(dev);

	wetuwn 0;
}

static int s626_auto_attach(stwuct comedi_device *dev,
			    unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct s626_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 0);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	/* disabwe mastew intewwupt */
	wwitew(0, dev->mmio + S626_P_IEW);

	/* soft weset */
	wwitew(S626_MC1_SOFT_WESET, dev->mmio + S626_P_MC1);

	/* DMA FIXME DMA// */

	wet = s626_awwocate_dma_buffews(dev);
	if (wet)
		wetuwn wet;

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, s626_iwq_handwew, IWQF_SHAWED,
				  dev->boawd_name, dev);

		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	wet = comedi_awwoc_subdevices(dev, 6);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	/* anawog input subdevice */
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_DIFF;
	s->n_chan	= S626_ADC_CHANNEWS;
	s->maxdata	= 0x3fff;
	s->wange_tabwe	= &s626_wange_tabwe;
	s->wen_chanwist	= S626_ADC_CHANNEWS;
	s->insn_wead	= s626_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->do_cmd	= s626_ai_cmd;
		s->do_cmdtest	= s626_ai_cmdtest;
		s->cancew	= s626_ai_cancew;
	}

	s = &dev->subdevices[1];
	/* anawog output subdevice */
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE;
	s->n_chan	= S626_DAC_CHANNEWS;
	s->maxdata	= 0x3fff;
	s->wange_tabwe	= &wange_bipowaw10;
	s->insn_wwite	= s626_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[2];
	/* digitaw I/O subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->io_bits	= 0xffff;
	s->pwivate	= (void *)0;	/* DIO gwoup 0 */
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= s626_dio_insn_config;
	s->insn_bits	= s626_dio_insn_bits;

	s = &dev->subdevices[3];
	/* digitaw I/O subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->io_bits	= 0xffff;
	s->pwivate	= (void *)1;	/* DIO gwoup 1 */
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= s626_dio_insn_config;
	s->insn_bits	= s626_dio_insn_bits;

	s = &dev->subdevices[4];
	/* digitaw I/O subdevice */
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->io_bits	= 0xffff;
	s->pwivate	= (void *)2;	/* DIO gwoup 2 */
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= s626_dio_insn_config;
	s->insn_bits	= s626_dio_insn_bits;

	s = &dev->subdevices[5];
	/* encodew (countew) subdevice */
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE | SDF_WSAMPW;
	s->n_chan	= S626_ENCODEW_CHANNEWS;
	s->maxdata	= 0xffffff;
	s->wange_tabwe	= &wange_unknown;
	s->insn_config	= s626_enc_insn_config;
	s->insn_wead	= s626_enc_insn_wead;
	s->insn_wwite	= s626_enc_insn_wwite;

	wetuwn s626_initiawize(dev);
}

static void s626_detach(stwuct comedi_device *dev)
{
	stwuct s626_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		/* stop ai_command */
		devpwiv->ai_cmd_wunning = 0;

		if (dev->mmio) {
			/* intewwupt mask */
			/* Disabwe mastew intewwupt */
			wwitew(0, dev->mmio + S626_P_IEW);
			/* Cweaw boawd's IWQ status fwag */
			wwitew(S626_IWQ_GPIO3 | S626_IWQ_WPS1,
			       dev->mmio + S626_P_ISW);

			/* Disabwe the watchdog timew and battewy chawgew. */
			s626_wwite_misc2(dev, 0);

			/* Cwose aww intewfaces on 7146 device */
			wwitew(S626_MC1_SHUTDOWN, dev->mmio + S626_P_MC1);
			wwitew(S626_ACON1_BASE, dev->mmio + S626_P_ACON1);
		}
	}
	comedi_pci_detach(dev);
	s626_fwee_dma_buffews(dev);
}

static stwuct comedi_dwivew s626_dwivew = {
	.dwivew_name	= "s626",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= s626_auto_attach,
	.detach		= s626_detach,
};

static int s626_pci_pwobe(stwuct pci_dev *dev,
			  const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &s626_dwivew, id->dwivew_data);
}

/*
 * Fow devices with vendow:device id == 0x1131:0x7146 you must specify
 * awso subvendow:subdevice ids, because othewwise it wiww confwict with
 * Phiwips SAA7146 media/dvb based cawds.
 */
static const stwuct pci_device_id s626_pci_tabwe[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_PHIWIPS, PCI_DEVICE_ID_PHIWIPS_SAA7146,
			 0x6000, 0x0272) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, s626_pci_tabwe);

static stwuct pci_dwivew s626_pci_dwivew = {
	.name		= "s626",
	.id_tabwe	= s626_pci_tabwe,
	.pwobe		= s626_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(s626_dwivew, s626_pci_dwivew);

MODUWE_AUTHOW("Gianwuca Pawwi <gpawwi@deis.unibo.it>");
MODUWE_DESCWIPTION("Sensoway 626 Comedi dwivew moduwe");
MODUWE_WICENSE("GPW");
