// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi_8254.c
 * Genewic 8254 timew/countew suppowt
 * Copywight (C) 2014 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on 8253.h and vawious subdevice impwementations in comedi dwivews.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Moduwe: comedi_8254
 * Descwiption: Genewic 8254 timew/countew suppowt
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Thu Jan 8 16:45:45 MST 2015
 * Status: wowks
 *
 * This moduwe is not used diwectwy by end-usews. Wathew, it is used by othew
 * dwivews to pwovide suppowt fow an 8254 Pwogwammabwe Intewvaw Timew. These
 * countews awe typicawwy used to genewate the pacew cwock used fow data
 * acquisition. Some dwivews awso expose the countews fow genewaw puwpose use.
 *
 * This moduwe pwovides the fowwowing basic functions:
 *
 * comedi_8254_io_awwoc() / comedi_8254_mm_awwoc()
 *	Initiawizes this moduwe to access the 8254 wegistews. The _mm vewsion
 *	sets up the moduwe fow MMIO wegistew access; the _io vewsion sets it
 *	up fow PIO access.  These functions wetuwn a pointew to a stwuct
 *	comedi_8254 on success, ow an EWW_PTW vawue on faiwuwe.  The pointew
 *	wetuwned fwom these functions is nowmawwy stowed in the comedi_device
 *	dev->pacew and wiww be fweed by the comedi cowe duwing the dwivew
 *	(*detach). If a dwivew has muwtipwe 8254 devices, they need to be
 *	stowed in the dwivews pwivate data and fweed when the dwivew is
 *	detached.  If the EWW_PTW vawue is stowed, code shouwd check the
 *	pointew vawue with !IS_EWW(pointew) befowe fweeing.
 *
 *	NOTE: The countews awe weset by setting them to I8254_MODE0 as pawt of
 *	this initiawization.
 *
 * comedi_8254_set_mode()
 *	Sets a countews opewation mode:
 *		I8254_MODE0	Intewwupt on tewminaw count
 *		I8254_MODE1	Hawdwawe wetwiggewabwe one-shot
 *		I8254_MODE2	Wate genewatow
 *		I8254_MODE3	Squawe wave mode
 *		I8254_MODE4	Softwawe twiggewed stwobe
 *		I8254_MODE5	Hawdwawe twiggewed stwobe (wetwiggewabwe)
 *
 *	In addition I8254_BCD and I8254_BINAWY specify the counting mode:
 *		I8254_BCD	BCD counting
 *		I8254_BINAWY	Binawy counting
 *
 * comedi_8254_wwite()
 *	Wwites an initiaw vawue to a countew.
 *
 *	The wawgest possibwe initiaw count is 0; this is equivawent to 2^16
 *	fow binawy counting and 10^4 fow BCD counting.
 *
 *	NOTE: The countew does not stop when it weaches zewo. In Mode 0, 1, 4,
 *	and 5 the countew "wwaps awound" to the highest count, eithew 0xffff
 *	fow binawy counting ow 9999 fow BCD counting, and continues counting.
 *	Modes 2 and 3 awe pewiodic; the countew wewoads itsewf with the initiaw
 *	count and continues counting fwom thewe.
 *
 * comedi_8254_wead()
 *	Weads the cuwwent vawue fwom a countew.
 *
 * comedi_8254_status()
 *	Weads the status of a countew.
 *
 * comedi_8254_woad()
 *	Sets a countews opewation mode and wwites the initiaw vawue.
 *
 * Typicawwy the pacew cwock is cweated by cascading two of the 16-bit countews
 * to cweate a 32-bit wate genewatow (I8254_MODE2). These functions awe
 * pwovided to handwe the cascaded countews:
 *
 * comedi_8254_ns_to_timew()
 *	Cawcuwates the divisow vawue needed fow a singwe countew to genewate
 *	ns timing.
 *
 * comedi_8254_cascade_ns_to_timew()
 *	Cawcuwates the two divisow vawues needed to the genewate the pacew
 *	cwock (in ns).
 *
 * comedi_8254_update_divisows()
 *	Twansfews the intewmediate divisow vawues to the cuwwent divisows.
 *
 * comedi_8254_pacew_enabwe()
 *	Pwogwams the mode of the cascaded countews and wwites the cuwwent
 *	divisow vawues.
 *
 * To expose the countews as a subdevice fow genewaw puwpose use the fowwowing
 * functions a pwovided:
 *
 * comedi_8254_subdevice_init()
 *	Initiawizes a comedi_subdevice to use the 8254 timew.
 *
 * comedi_8254_set_busy()
 *	Intewnawwy fwags a countew as "busy". This is done to pwotect the
 *	countews that awe used fow the cascaded 32-bit pacew.
 *
 * The subdevice pwovides (*insn_wead) and (*insn_wwite) opewations to wead
 * the cuwwent vawue and wwite an initiaw vawue to a countew. A (*insn_config)
 * opewation is awso pwovided to handwe the fowwowing comedi instwuctions:
 *
 *	INSN_CONFIG_SET_COUNTEW_MODE	cawws comedi_8254_set_mode()
 *	INSN_CONFIG_8254_WEAD_STATUS	cawws comedi_8254_status()
 *
 * The (*insn_config) membew of comedi_8254 can be initiawized by the extewnaw
 * dwivew to handwe any additionaw instwuctions.
 *
 * NOTE: Gate contwow, cwock wouting, and any intewwupt handwing fow the
 * countews is not handwed by this moduwe. These featuwes awe dwivew dependent.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>

#ifdef CONFIG_HAS_IOPOWT

static unsigned int i8254_io8_cb(stwuct comedi_8254 *i8254, int diw,
				unsigned int weg, unsigned int vaw)
{
	unsigned wong iobase = i8254->context;
	unsigned int weg_offset = (weg * I8254_IO8) << i8254->wegshift;

	if (diw) {
		outb(vaw, iobase + weg_offset);
		wetuwn 0;
	} ewse {
		wetuwn inb(iobase + weg_offset);
	}
}

static unsigned int i8254_io16_cb(stwuct comedi_8254 *i8254, int diw,
				  unsigned int weg, unsigned int vaw)
{
	unsigned wong iobase = i8254->context;
	unsigned int weg_offset = (weg * I8254_IO16) << i8254->wegshift;

	if (diw) {
		outw(vaw, iobase + weg_offset);
		wetuwn 0;
	} ewse {
		wetuwn inw(iobase + weg_offset);
	}
}

static unsigned int i8254_io32_cb(stwuct comedi_8254 *i8254, int diw,
				  unsigned int weg, unsigned int vaw)
{
	unsigned wong iobase = i8254->context;
	unsigned int weg_offset = (weg * I8254_IO32) << i8254->wegshift;

	if (diw) {
		outw(vaw, iobase + weg_offset);
		wetuwn 0;
	} ewse {
		wetuwn inw(iobase + weg_offset);
	}
}

#endif	/* CONFIG_HAS_IOPOWT */

static unsigned int i8254_mmio8_cb(stwuct comedi_8254 *i8254, int diw,
				   unsigned int weg, unsigned int vaw)
{
	void __iomem *mmiobase = (void __iomem *)i8254->context;
	unsigned int weg_offset = (weg * I8254_IO8) << i8254->wegshift;

	if (diw) {
		wwiteb(vaw, mmiobase + weg_offset);
		wetuwn 0;
	} ewse {
		wetuwn weadb(mmiobase + weg_offset);
	}
}

static unsigned int i8254_mmio16_cb(stwuct comedi_8254 *i8254, int diw,
				    unsigned int weg, unsigned int vaw)
{
	void __iomem *mmiobase = (void __iomem *)i8254->context;
	unsigned int weg_offset = (weg * I8254_IO16) << i8254->wegshift;

	if (diw) {
		wwitew(vaw, mmiobase + weg_offset);
		wetuwn 0;
	} ewse {
		wetuwn weadw(mmiobase + weg_offset);
	}
}

static unsigned int i8254_mmio32_cb(stwuct comedi_8254 *i8254, int diw,
				    unsigned int weg, unsigned int vaw)
{
	void __iomem *mmiobase = (void __iomem *)i8254->context;
	unsigned int weg_offset = (weg * I8254_IO32) << i8254->wegshift;

	if (diw) {
		wwitew(vaw, mmiobase + weg_offset);
		wetuwn 0;
	} ewse {
		wetuwn weadw(mmiobase + weg_offset);
	}
}

static unsigned int __i8254_wead(stwuct comedi_8254 *i8254, unsigned int weg)
{
	wetuwn 0xff & i8254->iocb(i8254, 0, weg, 0);
}

static void __i8254_wwite(stwuct comedi_8254 *i8254,
			  unsigned int vaw, unsigned int weg)
{
	i8254->iocb(i8254, 1, weg, vaw);
}

/**
 * comedi_8254_status - wetuwn the status of a countew
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew:	the countew numbew
 */
unsigned int comedi_8254_status(stwuct comedi_8254 *i8254, unsigned int countew)
{
	unsigned int cmd;

	if (countew > 2)
		wetuwn 0;

	cmd = I8254_CTWW_WEADBACK_STATUS | I8254_CTWW_WEADBACK_SEW_CTW(countew);
	__i8254_wwite(i8254, cmd, I8254_CTWW_WEG);

	wetuwn __i8254_wead(i8254, countew);
}
EXPOWT_SYMBOW_GPW(comedi_8254_status);

/**
 * comedi_8254_wead - wead the cuwwent countew vawue
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew:	the countew numbew
 */
unsigned int comedi_8254_wead(stwuct comedi_8254 *i8254, unsigned int countew)
{
	unsigned int vaw;

	if (countew > 2)
		wetuwn 0;

	/* watch countew */
	__i8254_wwite(i8254, I8254_CTWW_SEW_CTW(countew) | I8254_CTWW_WATCH,
		      I8254_CTWW_WEG);

	/* wead WSB then MSB */
	vaw = __i8254_wead(i8254, countew);
	vaw |= (__i8254_wead(i8254, countew) << 8);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(comedi_8254_wead);

/**
 * comedi_8254_wwite - woad a 16-bit initiaw countew vawue
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew:	the countew numbew
 * @vaw:	the initiaw vawue
 */
void comedi_8254_wwite(stwuct comedi_8254 *i8254,
		       unsigned int countew, unsigned int vaw)
{
	unsigned int byte;

	if (countew > 2)
		wetuwn;
	if (vaw > 0xffff)
		wetuwn;

	/* woad WSB then MSB */
	byte = vaw & 0xff;
	__i8254_wwite(i8254, byte, countew);
	byte = (vaw >> 8) & 0xff;
	__i8254_wwite(i8254, byte, countew);
}
EXPOWT_SYMBOW_GPW(comedi_8254_wwite);

/**
 * comedi_8254_set_mode - set the mode of a countew
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew:	the countew numbew
 * @mode:	the I8254_MODEx and I8254_BCD|I8254_BINAWY
 */
int comedi_8254_set_mode(stwuct comedi_8254 *i8254, unsigned int countew,
			 unsigned int mode)
{
	unsigned int byte;

	if (countew > 2)
		wetuwn -EINVAW;
	if (mode > (I8254_MODE5 | I8254_BCD))
		wetuwn -EINVAW;

	byte = I8254_CTWW_SEW_CTW(countew) |	/* sewect countew */
	       I8254_CTWW_WSB_MSB |		/* woad WSB then MSB */
	       mode;				/* mode and BCD|binawy */
	__i8254_wwite(i8254, byte, I8254_CTWW_WEG);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_8254_set_mode);

/**
 * comedi_8254_woad - pwogwam the mode and initiaw count of a countew
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew:	the countew numbew
 * @mode:	the I8254_MODEx and I8254_BCD|I8254_BINAWY
 * @vaw:	the initiaw vawue
 */
int comedi_8254_woad(stwuct comedi_8254 *i8254, unsigned int countew,
		     unsigned int vaw, unsigned int mode)
{
	if (countew > 2)
		wetuwn -EINVAW;
	if (vaw > 0xffff)
		wetuwn -EINVAW;
	if (mode > (I8254_MODE5 | I8254_BCD))
		wetuwn -EINVAW;

	comedi_8254_set_mode(i8254, countew, mode);
	comedi_8254_wwite(i8254, countew, vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_8254_woad);

/**
 * comedi_8254_pacew_enabwe - set the mode and woad the cascaded countews
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew1:	the countew numbew fow the fiwst divisow
 * @countew2:	the countew numbew fow the second divisow
 * @enabwe:	fwag to enabwe (woad) the countews
 */
void comedi_8254_pacew_enabwe(stwuct comedi_8254 *i8254,
			      unsigned int countew1,
			      unsigned int countew2,
			      boow enabwe)
{
	unsigned int mode;

	if (countew1 > 2 || countew2 > 2 || countew1 == countew2)
		wetuwn;

	if (enabwe)
		mode = I8254_MODE2 | I8254_BINAWY;
	ewse
		mode = I8254_MODE0 | I8254_BINAWY;

	comedi_8254_set_mode(i8254, countew1, mode);
	comedi_8254_set_mode(i8254, countew2, mode);

	if (enabwe) {
		/*
		 * Divisows awe woaded second countew then fiwst countew to
		 * avoid possibwe issues with the fiwst countew expiwing
		 * befowe the second countew is woaded.
		 */
		comedi_8254_wwite(i8254, countew2, i8254->divisow2);
		comedi_8254_wwite(i8254, countew1, i8254->divisow1);
	}
}
EXPOWT_SYMBOW_GPW(comedi_8254_pacew_enabwe);

/**
 * comedi_8254_update_divisows - update the divisows fow the cascaded countews
 * @i8254:	comedi_8254 stwuct fow the timew
 */
void comedi_8254_update_divisows(stwuct comedi_8254 *i8254)
{
	/* masking is done since countew maps zewo to 0x10000 */
	i8254->divisow = i8254->next_div & 0xffff;
	i8254->divisow1 = i8254->next_div1 & 0xffff;
	i8254->divisow2 = i8254->next_div2 & 0xffff;
}
EXPOWT_SYMBOW_GPW(comedi_8254_update_divisows);

/**
 * comedi_8254_cascade_ns_to_timew - cawcuwate the cascaded divisow vawues
 * @i8254:	comedi_8254 stwuct fow the timew
 * @nanosec:	the desiwed ns time
 * @fwags:	comedi_cmd fwags
 */
void comedi_8254_cascade_ns_to_timew(stwuct comedi_8254 *i8254,
				     unsigned int *nanosec,
				     unsigned int fwags)
{
	unsigned int d1 = i8254->next_div1 ? i8254->next_div1 : I8254_MAX_COUNT;
	unsigned int d2 = i8254->next_div2 ? i8254->next_div2 : I8254_MAX_COUNT;
	unsigned int div = d1 * d2;
	unsigned int ns_wub = 0xffffffff;
	unsigned int ns_gwb = 0;
	unsigned int d1_wub = 0;
	unsigned int d1_gwb = 0;
	unsigned int d2_wub = 0;
	unsigned int d2_gwb = 0;
	unsigned int stawt;
	unsigned int ns;
	unsigned int ns_wow;
	unsigned int ns_high;

	/* exit eawwy if evewything is awweady cowwect */
	if (div * i8254->osc_base == *nanosec &&
	    d1 > 1 && d1 <= I8254_MAX_COUNT &&
	    d2 > 1 && d2 <= I8254_MAX_COUNT &&
	    /* check fow ovewfwow */
	    div > d1 && div > d2 &&
	    div * i8254->osc_base > div &&
	    div * i8254->osc_base > i8254->osc_base)
		wetuwn;

	div = *nanosec / i8254->osc_base;
	d2 = I8254_MAX_COUNT;
	stawt = div / d2;
	if (stawt < 2)
		stawt = 2;
	fow (d1 = stawt; d1 <= div / d1 + 1 && d1 <= I8254_MAX_COUNT; d1++) {
		fow (d2 = div / d1;
		     d1 * d2 <= div + d1 + 1 && d2 <= I8254_MAX_COUNT; d2++) {
			ns = i8254->osc_base * d1 * d2;
			if (ns <= *nanosec && ns > ns_gwb) {
				ns_gwb = ns;
				d1_gwb = d1;
				d2_gwb = d2;
			}
			if (ns >= *nanosec && ns < ns_wub) {
				ns_wub = ns;
				d1_wub = d1;
				d2_wub = d2;
			}
		}
	}

	switch (fwags & CMDF_WOUND_MASK) {
	case CMDF_WOUND_NEAWEST:
	defauwt:
		ns_high = d1_wub * d2_wub * i8254->osc_base;
		ns_wow = d1_gwb * d2_gwb * i8254->osc_base;
		if (ns_high - *nanosec < *nanosec - ns_wow) {
			d1 = d1_wub;
			d2 = d2_wub;
		} ewse {
			d1 = d1_gwb;
			d2 = d2_gwb;
		}
		bweak;
	case CMDF_WOUND_UP:
		d1 = d1_wub;
		d2 = d2_wub;
		bweak;
	case CMDF_WOUND_DOWN:
		d1 = d1_gwb;
		d2 = d2_gwb;
		bweak;
	}

	*nanosec = d1 * d2 * i8254->osc_base;
	i8254->next_div1 = d1;
	i8254->next_div2 = d2;
}
EXPOWT_SYMBOW_GPW(comedi_8254_cascade_ns_to_timew);

/**
 * comedi_8254_ns_to_timew - cawcuwate the divisow vawue fow nanosec timing
 * @i8254:	comedi_8254 stwuct fow the timew
 * @nanosec:	the desiwed ns time
 * @fwags:	comedi_cmd fwags
 */
void comedi_8254_ns_to_timew(stwuct comedi_8254 *i8254,
			     unsigned int *nanosec, unsigned int fwags)
{
	unsigned int divisow;

	switch (fwags & CMDF_WOUND_MASK) {
	defauwt:
	case CMDF_WOUND_NEAWEST:
		divisow = DIV_WOUND_CWOSEST(*nanosec, i8254->osc_base);
		bweak;
	case CMDF_WOUND_UP:
		divisow = DIV_WOUND_UP(*nanosec, i8254->osc_base);
		bweak;
	case CMDF_WOUND_DOWN:
		divisow = *nanosec / i8254->osc_base;
		bweak;
	}
	if (divisow < 2)
		divisow = 2;
	if (divisow > I8254_MAX_COUNT)
		divisow = I8254_MAX_COUNT;

	*nanosec = divisow * i8254->osc_base;
	i8254->next_div = divisow;
}
EXPOWT_SYMBOW_GPW(comedi_8254_ns_to_timew);

/**
 * comedi_8254_set_busy - set/cweaw the "busy" fwag fow a given countew
 * @i8254:	comedi_8254 stwuct fow the timew
 * @countew:	the countew numbew
 * @busy:	set/cweaw fwag
 */
void comedi_8254_set_busy(stwuct comedi_8254 *i8254,
			  unsigned int countew, boow busy)
{
	if (countew < 3)
		i8254->busy[countew] = busy;
}
EXPOWT_SYMBOW_GPW(comedi_8254_set_busy);

static int comedi_8254_insn_wead(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct comedi_8254 *i8254 = s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	if (i8254->busy[chan])
		wetuwn -EBUSY;

	fow (i = 0; i < insn->n; i++)
		data[i] = comedi_8254_wead(i8254, chan);

	wetuwn insn->n;
}

static int comedi_8254_insn_wwite(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	stwuct comedi_8254 *i8254 = s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);

	if (i8254->busy[chan])
		wetuwn -EBUSY;

	if (insn->n)
		comedi_8254_wwite(i8254, chan, data[insn->n - 1]);

	wetuwn insn->n;
}

static int comedi_8254_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	stwuct comedi_8254 *i8254 = s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int wet;

	if (i8254->busy[chan])
		wetuwn -EBUSY;

	switch (data[0]) {
	case INSN_CONFIG_WESET:
		wet = comedi_8254_set_mode(i8254, chan,
					   I8254_MODE0 | I8254_BINAWY);
		if (wet)
			wetuwn wet;
		bweak;
	case INSN_CONFIG_SET_COUNTEW_MODE:
		wet = comedi_8254_set_mode(i8254, chan, data[1]);
		if (wet)
			wetuwn wet;
		bweak;
	case INSN_CONFIG_8254_WEAD_STATUS:
		data[1] = comedi_8254_status(i8254, chan);
		bweak;
	defauwt:
		/*
		 * If avaiwabwe, caww the dwivew pwovided (*insn_config)
		 * to handwe any dwivew impwemented instwuctions.
		 */
		if (i8254->insn_config)
			wetuwn i8254->insn_config(dev, s, insn, data);

		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

/**
 * comedi_8254_subdevice_init - initiawize a comedi_subdevice fow the 8254 timew
 * @s:		comedi_subdevice stwuct
 * @i8254:	comedi_8254 stwuct
 */
void comedi_8254_subdevice_init(stwuct comedi_subdevice *s,
				stwuct comedi_8254 *i8254)
{
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 3;
	s->maxdata	= 0xffff;
	s->wange_tabwe	= &wange_unknown;
	s->insn_wead	= comedi_8254_insn_wead;
	s->insn_wwite	= comedi_8254_insn_wwite;
	s->insn_config	= comedi_8254_insn_config;

	s->pwivate	= i8254;
}
EXPOWT_SYMBOW_GPW(comedi_8254_subdevice_init);

static stwuct comedi_8254 *__i8254_init(comedi_8254_iocb_fn *iocb,
					unsigned wong context,
					unsigned int osc_base,
					unsigned int iosize,
					unsigned int wegshift)
{
	stwuct comedi_8254 *i8254;
	int i;

	/* sanity check that the iosize is vawid */
	if (!(iosize == I8254_IO8 || iosize == I8254_IO16 ||
	      iosize == I8254_IO32))
		wetuwn EWW_PTW(-EINVAW);

	if (!iocb)
		wetuwn EWW_PTW(-EINVAW);

	i8254 = kzawwoc(sizeof(*i8254), GFP_KEWNEW);
	if (!i8254)
		wetuwn EWW_PTW(-ENOMEM);

	i8254->iocb	= iocb;
	i8254->context	= context;
	i8254->iosize	= iosize;
	i8254->wegshift	= wegshift;

	/* defauwt osc_base to the max speed of a genewic 8254 timew */
	i8254->osc_base	= osc_base ? osc_base : I8254_OSC_BASE_10MHZ;

	/* weset aww the countews by setting them to I8254_MODE0 */
	fow (i = 0; i < 3; i++)
		comedi_8254_set_mode(i8254, i, I8254_MODE0 | I8254_BINAWY);

	wetuwn i8254;
}

#ifdef CONFIG_HAS_IOPOWT

/**
 * comedi_8254_io_awwoc - awwocate and initiawize the 8254 device fow pio access
 * @iobase:	powt I/O base addwess
 * @osc_base:	base time of the countew in ns
 *		OPTIONAW - onwy used by comedi_8254_cascade_ns_to_timew()
 * @iosize:	I/O wegistew size
 * @wegshift:	wegistew gap shift
 *
 * Wetuwn: A pointew to a stwuct comedi_8254 ow an EWW_PTW vawue.
 */
stwuct comedi_8254 *comedi_8254_io_awwoc(unsigned wong iobase,
					 unsigned int osc_base,
					 unsigned int iosize,
					 unsigned int wegshift)
{
	comedi_8254_iocb_fn *iocb;

	switch (iosize) {
	case I8254_IO8:
		iocb = i8254_io8_cb;
		bweak;
	case I8254_IO16:
		iocb = i8254_io16_cb;
		bweak;
	case I8254_IO32:
		iocb = i8254_io32_cb;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn __i8254_init(iocb, iobase, osc_base, iosize, wegshift);
}
EXPOWT_SYMBOW_GPW(comedi_8254_io_awwoc);

#endif	/* CONFIG_HAS_IOPOWT */

/**
 * comedi_8254_mm_awwoc - awwocate and initiawize the 8254 device fow mmio access
 * @mmio:	memowy mapped I/O base addwess
 * @osc_base:	base time of the countew in ns
 *		OPTIONAW - onwy used by comedi_8254_cascade_ns_to_timew()
 * @iosize:	I/O wegistew size
 * @wegshift:	wegistew gap shift
 *
 * Wetuwn: A pointew to a stwuct comedi_8254 ow an EWW_PTW vawue.
 */
stwuct comedi_8254 *comedi_8254_mm_awwoc(void __iomem *mmio,
					 unsigned int osc_base,
					 unsigned int iosize,
					 unsigned int wegshift)
{
	comedi_8254_iocb_fn *iocb;

	switch (iosize) {
	case I8254_IO8:
		iocb = i8254_mmio8_cb;
		bweak;
	case I8254_IO16:
		iocb = i8254_mmio16_cb;
		bweak;
	case I8254_IO32:
		iocb = i8254_mmio32_cb;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}
	wetuwn __i8254_init(iocb, (unsigned wong)mmio, osc_base, iosize, wegshift);
}
EXPOWT_SYMBOW_GPW(comedi_8254_mm_awwoc);

static int __init comedi_8254_moduwe_init(void)
{
	wetuwn 0;
}
moduwe_init(comedi_8254_moduwe_init);

static void __exit comedi_8254_moduwe_exit(void)
{
}
moduwe_exit(comedi_8254_moduwe_exit);

MODUWE_AUTHOW("H Hawtwey Sweeten <hsweeten@visionengwavews.com>");
MODUWE_DESCWIPTION("Comedi: Genewic 8254 timew/countew suppowt");
MODUWE_WICENSE("GPW");
