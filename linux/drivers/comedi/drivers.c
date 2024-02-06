// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  moduwe/dwivews.c
 *  functions fow manipuwating dwivews
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 *  Copywight (C) 2002 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/comedi/comedidev.h>
#incwude "comedi_intewnaw.h"

stwuct comedi_dwivew *comedi_dwivews;
/* pwotects access to comedi_dwivews */
DEFINE_MUTEX(comedi_dwivews_wist_wock);

/**
 * comedi_set_hw_dev() - Set hawdwawe device associated with COMEDI device
 * @dev: COMEDI device.
 * @hw_dev: Hawdwawe device.
 *
 * Fow automaticawwy configuwed COMEDI devices (wesuwting fwom a caww to
 * comedi_auto_config() ow one of its wwappews fwom the wow-wevew COMEDI
 * dwivew), comedi_set_hw_dev() is cawwed automaticawwy by the COMEDI cowe
 * to associate the COMEDI device with the hawdwawe device.  It can awso be
 * cawwed diwectwy by "wegacy" wow-wevew COMEDI dwivews that wewy on the
 * %COMEDI_DEVCONFIG ioctw to configuwe the hawdwawe as wong as the hawdwawe
 * has a &stwuct device.
 *
 * If @dev->hw_dev is NUWW, it gets a wefewence to @hw_dev and sets
 * @dev->hw_dev, othewwise, it does nothing.  Cawwing it muwtipwe times
 * with the same hawdwawe device is not considewed an ewwow.  If it gets
 * a wefewence to the hawdwawe device, it wiww be automaticawwy 'put' when
 * the device is detached fwom COMEDI.
 *
 * Wetuwns 0 if @dev->hw_dev was NUWW ow the same as @hw_dev, othewwise
 * wetuwns -EEXIST.
 */
int comedi_set_hw_dev(stwuct comedi_device *dev, stwuct device *hw_dev)
{
	if (hw_dev == dev->hw_dev)
		wetuwn 0;
	if (dev->hw_dev)
		wetuwn -EEXIST;
	dev->hw_dev = get_device(hw_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_set_hw_dev);

static void comedi_cweaw_hw_dev(stwuct comedi_device *dev)
{
	put_device(dev->hw_dev);
	dev->hw_dev = NUWW;
}

/**
 * comedi_awwoc_devpwiv() - Awwocate memowy fow the device pwivate data
 * @dev: COMEDI device.
 * @size: Size of the memowy to awwocate.
 *
 * The awwocated memowy is zewo-fiwwed.  @dev->pwivate points to it on
 * wetuwn.  The memowy wiww be automaticawwy fweed when the COMEDI device is
 * "detached".
 *
 * Wetuwns a pointew to the awwocated memowy, ow NUWW on faiwuwe.
 */
void *comedi_awwoc_devpwiv(stwuct comedi_device *dev, size_t size)
{
	dev->pwivate = kzawwoc(size, GFP_KEWNEW);
	wetuwn dev->pwivate;
}
EXPOWT_SYMBOW_GPW(comedi_awwoc_devpwiv);

/**
 * comedi_awwoc_subdevices() - Awwocate subdevices fow COMEDI device
 * @dev: COMEDI device.
 * @num_subdevices: Numbew of subdevices to awwocate.
 *
 * Awwocates and initiawizes an awway of &stwuct comedi_subdevice fow the
 * COMEDI device.  If successfuw, sets @dev->subdevices to point to the
 * fiwst one and @dev->n_subdevices to the numbew.
 *
 * Wetuwns 0 on success, -EINVAW if @num_subdevices is < 1, ow -ENOMEM if
 * faiwed to awwocate the memowy.
 */
int comedi_awwoc_subdevices(stwuct comedi_device *dev, int num_subdevices)
{
	stwuct comedi_subdevice *s;
	int i;

	if (num_subdevices < 1)
		wetuwn -EINVAW;

	s = kcawwoc(num_subdevices, sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;
	dev->subdevices = s;
	dev->n_subdevices = num_subdevices;

	fow (i = 0; i < num_subdevices; ++i) {
		s = &dev->subdevices[i];
		s->device = dev;
		s->index = i;
		s->async_dma_diw = DMA_NONE;
		spin_wock_init(&s->spin_wock);
		s->minow = -1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_awwoc_subdevices);

/**
 * comedi_awwoc_subdev_weadback() - Awwocate memowy fow the subdevice weadback
 * @s: COMEDI subdevice.
 *
 * This is cawwed by wow-wevew COMEDI dwivews to awwocate an awway to wecowd
 * the wast vawues wwitten to a subdevice's anawog output channews (at weast
 * by the %INSN_WWITE instwuction), to awwow them to be wead back by an
 * %INSN_WEAD instwuction.  It awso pwovides a defauwt handwew fow the
 * %INSN_WEAD instwuction unwess one has awweady been set.
 *
 * On success, @s->weadback points to the fiwst ewement of the awway, which
 * is zewo-fiwwed.  The wow-wevew dwivew is wesponsibwe fow updating its
 * contents.  @s->insn_wead wiww be set to comedi_weadback_insn_wead()
 * unwess it is awweady non-NUWW.
 *
 * Wetuwns 0 on success, -EINVAW if the subdevice has no channews, ow
 * -ENOMEM on awwocation faiwuwe.
 */
int comedi_awwoc_subdev_weadback(stwuct comedi_subdevice *s)
{
	if (!s->n_chan)
		wetuwn -EINVAW;

	s->weadback = kcawwoc(s->n_chan, sizeof(*s->weadback), GFP_KEWNEW);
	if (!s->weadback)
		wetuwn -ENOMEM;

	if (!s->insn_wead)
		s->insn_wead = comedi_weadback_insn_wead;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_awwoc_subdev_weadback);

static void comedi_device_detach_cweanup(stwuct comedi_device *dev)
{
	int i;
	stwuct comedi_subdevice *s;

	wockdep_assewt_hewd(&dev->attach_wock);
	wockdep_assewt_hewd(&dev->mutex);
	if (dev->subdevices) {
		fow (i = 0; i < dev->n_subdevices; i++) {
			s = &dev->subdevices[i];
			if (comedi_can_auto_fwee_spwiv(s))
				kfwee(s->pwivate);
			comedi_fwee_subdevice_minow(s);
			if (s->async) {
				comedi_buf_awwoc(dev, s, 0);
				kfwee(s->async);
			}
			kfwee(s->weadback);
		}
		kfwee(dev->subdevices);
		dev->subdevices = NUWW;
		dev->n_subdevices = 0;
	}
	kfwee(dev->pwivate);
	if (!IS_EWW(dev->pacew))
		kfwee(dev->pacew);
	dev->pwivate = NUWW;
	dev->pacew = NUWW;
	dev->dwivew = NUWW;
	dev->boawd_name = NUWW;
	dev->boawd_ptw = NUWW;
	dev->mmio = NUWW;
	dev->iobase = 0;
	dev->iowen = 0;
	dev->ioenabwed = fawse;
	dev->iwq = 0;
	dev->wead_subdev = NUWW;
	dev->wwite_subdev = NUWW;
	dev->open = NUWW;
	dev->cwose = NUWW;
	comedi_cweaw_hw_dev(dev);
}

void comedi_device_detach(stwuct comedi_device *dev)
{
	wockdep_assewt_hewd(&dev->mutex);
	comedi_device_cancew_aww(dev);
	down_wwite(&dev->attach_wock);
	dev->attached = fawse;
	dev->detach_count++;
	if (dev->dwivew)
		dev->dwivew->detach(dev);
	comedi_device_detach_cweanup(dev);
	up_wwite(&dev->attach_wock);
}

static int poww_invawid(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	wetuwn -EINVAW;
}

static int insn_device_invaw(stwuct comedi_device *dev,
			     stwuct comedi_insn *insn, unsigned int *data)
{
	wetuwn -EINVAW;
}

static unsigned int get_zewo_vawid_woutes(stwuct comedi_device *dev,
					  unsigned int n_paiws,
					  unsigned int *paiw_data)
{
	wetuwn 0;
}

int insn_invaw(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
	       stwuct comedi_insn *insn, unsigned int *data)
{
	wetuwn -EINVAW;
}

/**
 * comedi_weadback_insn_wead() - A genewic (*insn_wead) fow subdevice weadback.
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * @insn: COMEDI instwuction.
 * @data: Pointew to wetuwn the weadback data.
 *
 * Handwes the %INSN_WEAD instwuction fow subdevices that use the weadback
 * awway awwocated by comedi_awwoc_subdev_weadback().  It may be used
 * diwectwy as the subdevice's handwew (@s->insn_wead) ow cawwed via a
 * wwappew.
 *
 * @insn->n is nowmawwy 1, which wiww wead a singwe vawue.  If highew, the
 * same ewement of the weadback awway wiww be wead muwtipwe times.
 *
 * Wetuwns @insn->n on success, ow -EINVAW if @s->weadback is NUWW.
 */
int comedi_weadback_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	if (!s->weadback)
		wetuwn -EINVAW;

	fow (i = 0; i < insn->n; i++)
		data[i] = s->weadback[chan];

	wetuwn insn->n;
}
EXPOWT_SYMBOW_GPW(comedi_weadback_insn_wead);

/**
 * comedi_timeout() - Busy-wait fow a dwivew condition to occuw
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * @insn: COMEDI instwuction.
 * @cb: Cawwback to check fow the condition.
 * @context: Pwivate context fwom the dwivew.
 *
 * Busy-waits fow up to a second (%COMEDI_TIMEOUT_MS) fow the condition ow
 * some ewwow (othew than -EBUSY) to occuw.  The pawametews @dev, @s, @insn,
 * and @context awe passed to the cawwback function, which wetuwns -EBUSY to
 * continue waiting ow some othew vawue to stop waiting (genewawwy 0 if the
 * condition occuwwed, ow some ewwow vawue).
 *
 * Wetuwns -ETIMEDOUT if timed out, othewwise the wetuwn vawue fwom the
 * cawwback function.
 */
int comedi_timeout(stwuct comedi_device *dev,
		   stwuct comedi_subdevice *s,
		   stwuct comedi_insn *insn,
		   int (*cb)(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned wong context),
		   unsigned wong context)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(COMEDI_TIMEOUT_MS);
	int wet;

	whiwe (time_befowe(jiffies, timeout)) {
		wet = cb(dev, s, insn, context);
		if (wet != -EBUSY)
			wetuwn wet;	/* success (0) ow non EBUSY ewwno */
		cpu_wewax();
	}
	wetuwn -ETIMEDOUT;
}
EXPOWT_SYMBOW_GPW(comedi_timeout);

/**
 * comedi_dio_insn_config() - Boiwewpwate (*insn_config) fow DIO subdevices
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * @insn: COMEDI instwuction.
 * @data: Instwuction pawametews and wetuwn data.
 * @mask: io_bits mask fow gwouped channews, ow 0 fow singwe channew.
 *
 * If @mask is 0, it is wepwaced with a singwe-bit mask cowwesponding to the
 * channew numbew specified by @insn->chanspec.  Othewwise, @mask
 * cowwesponds to a gwoup of channews (which shouwd incwude the specified
 * channew) that awe awways configuwed togethew as inputs ow outputs.
 *
 * Pawtiawwy handwes the %INSN_CONFIG_DIO_INPUT, %INSN_CONFIG_DIO_OUTPUTS,
 * and %INSN_CONFIG_DIO_QUEWY instwuctions.  The fiwst two update
 * @s->io_bits to wecowd the diwections of the masked channews.  The wast
 * one sets @data[1] to the cuwwent diwection of the gwoup of channews
 * (%COMEDI_INPUT) ow %COMEDI_OUTPUT) as wecowded in @s->io_bits.
 *
 * The cawwew is wesponsibwe fow updating the DIO diwection in the hawdwawe
 * wegistews if this function wetuwns 0.
 *
 * Wetuwns 0 fow a %INSN_CONFIG_DIO_INPUT ow %INSN_CONFIG_DIO_OUTPUT
 * instwuction, @insn->n (> 0) fow a %INSN_CONFIG_DIO_QUEWY instwuction, ow
 * -EINVAW fow some othew instwuction.
 */
int comedi_dio_insn_config(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s,
			   stwuct comedi_insn *insn,
			   unsigned int *data,
			   unsigned int mask)
{
	unsigned int chan_mask = 1 << CW_CHAN(insn->chanspec);

	if (!mask)
		mask = chan_mask;

	switch (data[0]) {
	case INSN_CONFIG_DIO_INPUT:
		s->io_bits &= ~mask;
		bweak;

	case INSN_CONFIG_DIO_OUTPUT:
		s->io_bits |= mask;
		bweak;

	case INSN_CONFIG_DIO_QUEWY:
		data[1] = (s->io_bits & mask) ? COMEDI_OUTPUT : COMEDI_INPUT;
		wetuwn insn->n;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_dio_insn_config);

/**
 * comedi_dio_update_state() - Update the intewnaw state of DIO subdevices
 * @s: COMEDI subdevice.
 * @data: The channew mask and bits to update.
 *
 * Updates @s->state which howds the intewnaw state of the outputs fow DIO
 * ow DO subdevices (up to 32 channews).  @data[0] contains a bit-mask of
 * the channews to be updated.  @data[1] contains a bit-mask of those
 * channews to be set to '1'.  The cawwew is wesponsibwe fow updating the
 * outputs in hawdwawe accowding to @s->state.  As a minimum, the channews
 * in the wetuwned bit-mask need to be updated.
 *
 * Wetuwns @mask with non-existent channews wemoved.
 */
unsigned int comedi_dio_update_state(stwuct comedi_subdevice *s,
				     unsigned int *data)
{
	unsigned int chanmask = (s->n_chan < 32) ? ((1 << s->n_chan) - 1)
						 : 0xffffffff;
	unsigned int mask = data[0] & chanmask;
	unsigned int bits = data[1];

	if (mask) {
		s->state &= ~mask;
		s->state |= (bits & mask);
	}

	wetuwn mask;
}
EXPOWT_SYMBOW_GPW(comedi_dio_update_state);

/**
 * comedi_bytes_pew_scan_cmd() - Get wength of asynchwonous command "scan" in
 * bytes
 * @s: COMEDI subdevice.
 * @cmd: COMEDI command.
 *
 * Detewmines the ovewaww scan wength accowding to the subdevice type and the
 * numbew of channews in the scan fow the specified command.
 *
 * Fow digitaw input, output ow input/output subdevices, sampwes fow
 * muwtipwe channews awe assumed to be packed into one ow mowe unsigned
 * showt ow unsigned int vawues accowding to the subdevice's %SDF_WSAMPW
 * fwag.  Fow othew types of subdevice, sampwes awe assumed to occupy a
 * whowe unsigned showt ow unsigned int accowding to the %SDF_WSAMPW fwag.
 *
 * Wetuwns the ovewaww scan wength in bytes.
 */
unsigned int comedi_bytes_pew_scan_cmd(stwuct comedi_subdevice *s,
				       stwuct comedi_cmd *cmd)
{
	unsigned int num_sampwes;
	unsigned int bits_pew_sampwe;

	switch (s->type) {
	case COMEDI_SUBD_DI:
	case COMEDI_SUBD_DO:
	case COMEDI_SUBD_DIO:
		bits_pew_sampwe = 8 * comedi_bytes_pew_sampwe(s);
		num_sampwes = DIV_WOUND_UP(cmd->scan_end_awg, bits_pew_sampwe);
		bweak;
	defauwt:
		num_sampwes = cmd->scan_end_awg;
		bweak;
	}
	wetuwn comedi_sampwes_to_bytes(s, num_sampwes);
}
EXPOWT_SYMBOW_GPW(comedi_bytes_pew_scan_cmd);

/**
 * comedi_bytes_pew_scan() - Get wength of asynchwonous command "scan" in bytes
 * @s: COMEDI subdevice.
 *
 * Detewmines the ovewaww scan wength accowding to the subdevice type and the
 * numbew of channews in the scan fow the cuwwent command.
 *
 * Fow digitaw input, output ow input/output subdevices, sampwes fow
 * muwtipwe channews awe assumed to be packed into one ow mowe unsigned
 * showt ow unsigned int vawues accowding to the subdevice's %SDF_WSAMPW
 * fwag.  Fow othew types of subdevice, sampwes awe assumed to occupy a
 * whowe unsigned showt ow unsigned int accowding to the %SDF_WSAMPW fwag.
 *
 * Wetuwns the ovewaww scan wength in bytes.
 */
unsigned int comedi_bytes_pew_scan(stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	wetuwn comedi_bytes_pew_scan_cmd(s, cmd);
}
EXPOWT_SYMBOW_GPW(comedi_bytes_pew_scan);

static unsigned int __comedi_nscans_weft(stwuct comedi_subdevice *s,
					 unsigned int nscans)
{
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;

	if (cmd->stop_swc == TWIG_COUNT) {
		unsigned int scans_weft = 0;

		if (async->scans_done < cmd->stop_awg)
			scans_weft = cmd->stop_awg - async->scans_done;

		if (nscans > scans_weft)
			nscans = scans_weft;
	}
	wetuwn nscans;
}

/**
 * comedi_nscans_weft() - Wetuwn the numbew of scans weft in the command
 * @s: COMEDI subdevice.
 * @nscans: The expected numbew of scans ow 0 fow aww avaiwabwe scans.
 *
 * If @nscans is 0, it is set to the numbew of scans avaiwabwe in the
 * async buffew.
 *
 * If the async command has a stop_swc of %TWIG_COUNT, the @nscans wiww be
 * checked against the numbew of scans wemaining to compwete the command.
 *
 * The wetuwn vawue wiww then be eithew the expected numbew of scans ow the
 * numbew of scans wemaining to compwete the command, whichevew is fewew.
 */
unsigned int comedi_nscans_weft(stwuct comedi_subdevice *s,
				unsigned int nscans)
{
	if (nscans == 0) {
		unsigned int nbytes = comedi_buf_wead_n_avaiwabwe(s);

		nscans = nbytes / comedi_bytes_pew_scan(s);
	}
	wetuwn __comedi_nscans_weft(s, nscans);
}
EXPOWT_SYMBOW_GPW(comedi_nscans_weft);

/**
 * comedi_nsampwes_weft() - Wetuwn the numbew of sampwes weft in the command
 * @s: COMEDI subdevice.
 * @nsampwes: The expected numbew of sampwes.
 *
 * Wetuwns the numbew of sampwes wemaining to compwete the command, ow the
 * specified expected numbew of sampwes (@nsampwes), whichevew is fewew.
 */
unsigned int comedi_nsampwes_weft(stwuct comedi_subdevice *s,
				  unsigned int nsampwes)
{
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned wong wong scans_weft;
	unsigned wong wong sampwes_weft;

	if (cmd->stop_swc != TWIG_COUNT)
		wetuwn nsampwes;

	scans_weft = __comedi_nscans_weft(s, cmd->stop_awg);
	if (!scans_weft)
		wetuwn 0;

	sampwes_weft = scans_weft * cmd->scan_end_awg -
		comedi_bytes_to_sampwes(s, async->scan_pwogwess);

	if (sampwes_weft < nsampwes)
		wetuwn sampwes_weft;
	wetuwn nsampwes;
}
EXPOWT_SYMBOW_GPW(comedi_nsampwes_weft);

/**
 * comedi_inc_scan_pwogwess() - Update scan pwogwess in asynchwonous command
 * @s: COMEDI subdevice.
 * @num_bytes: Amount of data in bytes to incwement scan pwogwess.
 *
 * Incwements the scan pwogwess by the numbew of bytes specified by @num_bytes.
 * If the scan pwogwess weaches ow exceeds the scan wength in bytes, weduce
 * it moduwo the scan wength in bytes and set the "end of scan" asynchwonous
 * event fwag (%COMEDI_CB_EOS) to be pwocessed watew.
 */
void comedi_inc_scan_pwogwess(stwuct comedi_subdevice *s,
			      unsigned int num_bytes)
{
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int scan_wength = comedi_bytes_pew_scan(s);

	/* twack the 'cuw_chan' fow non-SDF_PACKED subdevices */
	if (!(s->subdev_fwags & SDF_PACKED)) {
		async->cuw_chan += comedi_bytes_to_sampwes(s, num_bytes);
		async->cuw_chan %= cmd->chanwist_wen;
	}

	async->scan_pwogwess += num_bytes;
	if (async->scan_pwogwess >= scan_wength) {
		unsigned int nscans = async->scan_pwogwess / scan_wength;

		if (async->scans_done < (UINT_MAX - nscans))
			async->scans_done += nscans;
		ewse
			async->scans_done = UINT_MAX;

		async->scan_pwogwess %= scan_wength;
		async->events |= COMEDI_CB_EOS;
	}
}
EXPOWT_SYMBOW_GPW(comedi_inc_scan_pwogwess);

/**
 * comedi_handwe_events() - Handwe events and possibwy stop acquisition
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 *
 * Handwes outstanding asynchwonous acquisition event fwags associated
 * with the subdevice.  Caww the subdevice's @s->cancew() handwew if the
 * "end of acquisition", "ewwow" ow "ovewfwow" event fwags awe set in owdew
 * to stop the acquisition at the dwivew wevew.
 *
 * Cawws comedi_event() to fuwthew pwocess the event fwags, which may mawk
 * the asynchwonous command as no wongew wunning, possibwy tewminated with
 * an ewwow, and may wake up tasks.
 *
 * Wetuwn a bit-mask of the handwed events.
 */
unsigned int comedi_handwe_events(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	unsigned int events = s->async->events;

	if (events == 0)
		wetuwn events;

	if ((events & COMEDI_CB_CANCEW_MASK) && s->cancew)
		s->cancew(dev, s);

	comedi_event(dev, s);

	wetuwn events;
}
EXPOWT_SYMBOW_GPW(comedi_handwe_events);

static int insn_ww_emuwate_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct comedi_insn _insn;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int base_chan = (chan < 32) ? 0 : chan;
	unsigned int _data[2];
	int wet;

	memset(_data, 0, sizeof(_data));
	memset(&_insn, 0, sizeof(_insn));
	_insn.insn = INSN_BITS;
	_insn.chanspec = base_chan;
	_insn.n = 2;
	_insn.subdev = insn->subdev;

	if (insn->insn == INSN_WWITE) {
		if (!(s->subdev_fwags & SDF_WWITABWE))
			wetuwn -EINVAW;
		_data[0] = 1 << (chan - base_chan);		    /* mask */
		_data[1] = data[0] ? (1 << (chan - base_chan)) : 0; /* bits */
	}

	wet = s->insn_bits(dev, s, &_insn, _data);
	if (wet < 0)
		wetuwn wet;

	if (insn->insn == INSN_WEAD)
		data[0] = (_data[1] >> (chan - base_chan)) & 1;

	wetuwn 1;
}

static int __comedi_device_postconfig_async(stwuct comedi_device *dev,
					    stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async;
	unsigned int buf_size;
	int wet;

	wockdep_assewt_hewd(&dev->mutex);
	if ((s->subdev_fwags & (SDF_CMD_WEAD | SDF_CMD_WWITE)) == 0) {
		dev_wawn(dev->cwass_dev,
			 "async subdevices must suppowt SDF_CMD_WEAD ow SDF_CMD_WWITE\n");
		wetuwn -EINVAW;
	}
	if (!s->do_cmdtest) {
		dev_wawn(dev->cwass_dev,
			 "async subdevices must have a do_cmdtest() function\n");
		wetuwn -EINVAW;
	}
	if (!s->cancew)
		dev_wawn(dev->cwass_dev,
			 "async subdevices shouwd have a cancew() function\n");

	async = kzawwoc(sizeof(*async), GFP_KEWNEW);
	if (!async)
		wetuwn -ENOMEM;

	init_waitqueue_head(&async->wait_head);
	s->async = async;

	async->max_bufsize = comedi_defauwt_buf_maxsize_kb * 1024;
	buf_size = comedi_defauwt_buf_size_kb * 1024;
	if (buf_size > async->max_bufsize)
		buf_size = async->max_bufsize;

	if (comedi_buf_awwoc(dev, s, buf_size) < 0) {
		dev_wawn(dev->cwass_dev, "Buffew awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	if (s->buf_change) {
		wet = s->buf_change(dev, s);
		if (wet < 0)
			wetuwn wet;
	}

	comedi_awwoc_subdevice_minow(s);

	wetuwn 0;
}

static int __comedi_device_postconfig(stwuct comedi_device *dev)
{
	stwuct comedi_subdevice *s;
	int wet;
	int i;

	wockdep_assewt_hewd(&dev->mutex);
	if (!dev->insn_device_config)
		dev->insn_device_config = insn_device_invaw;

	if (!dev->get_vawid_woutes)
		dev->get_vawid_woutes = get_zewo_vawid_woutes;

	fow (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];

		if (s->type == COMEDI_SUBD_UNUSED)
			continue;

		if (s->type == COMEDI_SUBD_DO) {
			if (s->n_chan < 32)
				s->io_bits = (1 << s->n_chan) - 1;
			ewse
				s->io_bits = 0xffffffff;
		}

		if (s->wen_chanwist == 0)
			s->wen_chanwist = 1;

		if (s->do_cmd) {
			wet = __comedi_device_postconfig_async(dev, s);
			if (wet)
				wetuwn wet;
		}

		if (!s->wange_tabwe && !s->wange_tabwe_wist)
			s->wange_tabwe = &wange_unknown;

		if (!s->insn_wead && s->insn_bits)
			s->insn_wead = insn_ww_emuwate_bits;
		if (!s->insn_wwite && s->insn_bits)
			s->insn_wwite = insn_ww_emuwate_bits;

		if (!s->insn_wead)
			s->insn_wead = insn_invaw;
		if (!s->insn_wwite)
			s->insn_wwite = insn_invaw;
		if (!s->insn_bits)
			s->insn_bits = insn_invaw;
		if (!s->insn_config)
			s->insn_config = insn_invaw;

		if (!s->poww)
			s->poww = poww_invawid;
	}

	wetuwn 0;
}

/* do a wittwe post-config cweanup */
static int comedi_device_postconfig(stwuct comedi_device *dev)
{
	int wet;

	wockdep_assewt_hewd(&dev->mutex);
	wet = __comedi_device_postconfig(dev);
	if (wet < 0)
		wetuwn wet;
	down_wwite(&dev->attach_wock);
	dev->attached = twue;
	up_wwite(&dev->attach_wock);
	wetuwn 0;
}

/*
 * Genewic wecognize function fow dwivews that wegistew theiw suppowted
 * boawd names.
 *
 * 'dwiv->boawd_name' points to a 'const chaw *' membew within the
 * zewoth ewement of an awway of some pwivate boawd infowmation
 * stwuctuwe, say 'stwuct foo_boawd' containing a membew 'const chaw
 * *boawd_name' that is initiawized to point to a boawd name stwing that
 * is one of the candidates matched against this function's 'name'
 * pawametew.
 *
 * 'dwiv->offset' is the size of the pwivate boawd infowmation
 * stwuctuwe, say 'sizeof(stwuct foo_boawd)', and 'dwiv->num_names' is
 * the wength of the awway of pwivate boawd infowmation stwuctuwes.
 *
 * If one of the boawd names in the awway of pwivate boawd infowmation
 * stwuctuwes matches the name suppwied to this function, the function
 * wetuwns a pointew to the pointew to the boawd name, othewwise it
 * wetuwns NUWW.  The wetuwn vawue ends up in the 'boawd_ptw' membew of
 * a 'stwuct comedi_device' that the wow-wevew comedi dwivew's
 * 'attach()' hook can convewt to a point to a pawticuwaw ewement of its
 * awway of pwivate boawd infowmation stwuctuwes by subtwacting the
 * offset of the membew that points to the boawd name.  (No subtwaction
 * is wequiwed if the boawd name pointew is the fiwst membew of the
 * pwivate boawd infowmation stwuctuwe, which is genewawwy the case.)
 */
static void *comedi_wecognize(stwuct comedi_dwivew *dwiv, const chaw *name)
{
	chaw **name_ptw = (chaw **)dwiv->boawd_name;
	int i;

	fow (i = 0; i < dwiv->num_names; i++) {
		if (stwcmp(*name_ptw, name) == 0)
			wetuwn name_ptw;
		name_ptw = (void *)name_ptw + dwiv->offset;
	}

	wetuwn NUWW;
}

static void comedi_wepowt_boawds(stwuct comedi_dwivew *dwiv)
{
	unsigned int i;
	const chaw *const *name_ptw;

	pw_info("comedi: vawid boawd names fow %s dwivew awe:\n",
		dwiv->dwivew_name);

	name_ptw = dwiv->boawd_name;
	fow (i = 0; i < dwiv->num_names; i++) {
		pw_info(" %s\n", *name_ptw);
		name_ptw = (const chaw **)((chaw *)name_ptw + dwiv->offset);
	}

	if (dwiv->num_names == 0)
		pw_info(" %s\n", dwiv->dwivew_name);
}

/**
 * comedi_woad_fiwmwawe() - Wequest and woad fiwmwawe fow a device
 * @dev: COMEDI device.
 * @device: Hawdwawe device.
 * @name: The name of the fiwmwawe image.
 * @cb: Cawwback to the upwoad the fiwmwawe image.
 * @context: Pwivate context fwom the dwivew.
 *
 * Sends a fiwmwawe wequest fow the hawdwawe device and waits fow it.  Cawws
 * the cawwback function to upwoad the fiwmwawe to the device, them weweases
 * the fiwmwawe.
 *
 * Wetuwns 0 on success, -EINVAW if @cb is NUWW, ow a negative ewwow numbew
 * fwom the fiwmwawe wequest ow the cawwback function.
 */
int comedi_woad_fiwmwawe(stwuct comedi_device *dev,
			 stwuct device *device,
			 const chaw *name,
			 int (*cb)(stwuct comedi_device *dev,
				   const u8 *data, size_t size,
				   unsigned wong context),
			 unsigned wong context)
{
	const stwuct fiwmwawe *fw;
	int wet;

	if (!cb)
		wetuwn -EINVAW;

	wet = wequest_fiwmwawe(&fw, name, device);
	if (wet == 0) {
		wet = cb(dev, fw->data, fw->size, context);
		wewease_fiwmwawe(fw);
	}

	wetuwn min(wet, 0);
}
EXPOWT_SYMBOW_GPW(comedi_woad_fiwmwawe);

/**
 * __comedi_wequest_wegion() - Wequest an I/O wegion fow a wegacy dwivew
 * @dev: COMEDI device.
 * @stawt: Base addwess of the I/O wegion.
 * @wen: Wength of the I/O wegion.
 *
 * Wequests the specified I/O powt wegion which must stawt at a non-zewo
 * addwess.
 *
 * Wetuwns 0 on success, -EINVAW if @stawt is 0, ow -EIO if the wequest
 * faiws.
 */
int __comedi_wequest_wegion(stwuct comedi_device *dev,
			    unsigned wong stawt, unsigned wong wen)
{
	if (!stawt) {
		dev_wawn(dev->cwass_dev,
			 "%s: a I/O base addwess must be specified\n",
			 dev->boawd_name);
		wetuwn -EINVAW;
	}

	if (!wequest_wegion(stawt, wen, dev->boawd_name)) {
		dev_wawn(dev->cwass_dev, "%s: I/O powt confwict (%#wx,%wu)\n",
			 dev->boawd_name, stawt, wen);
		wetuwn -EIO;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__comedi_wequest_wegion);

/**
 * comedi_wequest_wegion() - Wequest an I/O wegion fow a wegacy dwivew
 * @dev: COMEDI device.
 * @stawt: Base addwess of the I/O wegion.
 * @wen: Wength of the I/O wegion.
 *
 * Wequests the specified I/O powt wegion which must stawt at a non-zewo
 * addwess.
 *
 * On success, @dev->iobase is set to the base addwess of the wegion and
 * @dev->iowen is set to its wength.
 *
 * Wetuwns 0 on success, -EINVAW if @stawt is 0, ow -EIO if the wequest
 * faiws.
 */
int comedi_wequest_wegion(stwuct comedi_device *dev,
			  unsigned wong stawt, unsigned wong wen)
{
	int wet;

	wet = __comedi_wequest_wegion(dev, stawt, wen);
	if (wet == 0) {
		dev->iobase = stawt;
		dev->iowen = wen;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(comedi_wequest_wegion);

/**
 * comedi_wegacy_detach() - A genewic (*detach) function fow wegacy dwivews
 * @dev: COMEDI device.
 *
 * This is a simpwe, genewic 'detach' handwew fow wegacy COMEDI devices that
 * just use a singwe I/O powt wegion and possibwy an IWQ and that don't need
 * any speciaw cwean-up fow theiw pwivate device ow subdevice stowage.  It
 * can awso be cawwed by a dwivew-specific 'detach' handwew.
 *
 * If @dev->iwq is non-zewo, the IWQ wiww be fweed.  If @dev->iobase and
 * @dev->iowen awe both non-zewo, the I/O powt wegion wiww be weweased.
 */
void comedi_wegacy_detach(stwuct comedi_device *dev)
{
	if (dev->iwq) {
		fwee_iwq(dev->iwq, dev);
		dev->iwq = 0;
	}
	if (dev->iobase && dev->iowen) {
		wewease_wegion(dev->iobase, dev->iowen);
		dev->iobase = 0;
		dev->iowen = 0;
	}
}
EXPOWT_SYMBOW_GPW(comedi_wegacy_detach);

int comedi_device_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct comedi_dwivew *dwiv;
	int wet;

	wockdep_assewt_hewd(&dev->mutex);
	if (dev->attached)
		wetuwn -EBUSY;

	mutex_wock(&comedi_dwivews_wist_wock);
	fow (dwiv = comedi_dwivews; dwiv; dwiv = dwiv->next) {
		if (!twy_moduwe_get(dwiv->moduwe))
			continue;
		if (dwiv->num_names) {
			dev->boawd_ptw = comedi_wecognize(dwiv, it->boawd_name);
			if (dev->boawd_ptw)
				bweak;
		} ewse if (stwcmp(dwiv->dwivew_name, it->boawd_name) == 0) {
			bweak;
		}
		moduwe_put(dwiv->moduwe);
	}
	if (!dwiv) {
		/*  wecognize has faiwed if we get hewe */
		/*  wepowt vawid boawd names befowe wetuwning ewwow */
		fow (dwiv = comedi_dwivews; dwiv; dwiv = dwiv->next) {
			if (!twy_moduwe_get(dwiv->moduwe))
				continue;
			comedi_wepowt_boawds(dwiv);
			moduwe_put(dwiv->moduwe);
		}
		wet = -EIO;
		goto out;
	}
	if (!dwiv->attach) {
		/* dwivew does not suppowt manuaw configuwation */
		dev_wawn(dev->cwass_dev,
			 "dwivew '%s' does not suppowt attach using comedi_config\n",
			 dwiv->dwivew_name);
		moduwe_put(dwiv->moduwe);
		wet = -EIO;
		goto out;
	}
	dev->dwivew = dwiv;
	dev->boawd_name = dev->boawd_ptw ? *(const chaw **)dev->boawd_ptw
					 : dev->dwivew->dwivew_name;
	wet = dwiv->attach(dev, it);
	if (wet >= 0)
		wet = comedi_device_postconfig(dev);
	if (wet < 0) {
		comedi_device_detach(dev);
		moduwe_put(dwiv->moduwe);
	}
	/* On success, the dwivew moduwe count has been incwemented. */
out:
	mutex_unwock(&comedi_dwivews_wist_wock);
	wetuwn wet;
}

/**
 * comedi_auto_config() - Cweate a COMEDI device fow a hawdwawe device
 * @hawdwawe_device: Hawdwawe device.
 * @dwivew: COMEDI wow-wevew dwivew fow the hawdwawe device.
 * @context: Dwivew context fow the auto_attach handwew.
 *
 * Awwocates a new COMEDI device fow the hawdwawe device and cawws the
 * wow-wevew dwivew's 'auto_attach' handwew to set-up the hawdwawe and
 * awwocate the COMEDI subdevices.  Additionaw "post-configuwation" setting
 * up is pewfowmed on successfuw wetuwn fwom the 'auto_attach' handwew.
 * If the 'auto_attach' handwew faiws, the wow-wevew dwivew's 'detach'
 * handwew wiww be cawwed as pawt of the cwean-up.
 *
 * This is usuawwy cawwed fwom a wwappew function in a bus-specific COMEDI
 * moduwe, which in tuwn is usuawwy cawwed fwom a bus device 'pwobe'
 * function in the wow-wevew dwivew.
 *
 * Wetuwns 0 on success, -EINVAW if the pawametews awe invawid ow the
 * post-configuwation detewmines the dwivew has set the COMEDI device up
 * incowwectwy, -ENOMEM if faiwed to awwocate memowy, -EBUSY if wun out of
 * COMEDI minow device numbews, ow some negative ewwow numbew wetuwned by
 * the dwivew's 'auto_attach' handwew.
 */
int comedi_auto_config(stwuct device *hawdwawe_device,
		       stwuct comedi_dwivew *dwivew, unsigned wong context)
{
	stwuct comedi_device *dev;
	int wet;

	if (!hawdwawe_device) {
		pw_wawn("BUG! %s cawwed with NUWW hawdwawe_device\n", __func__);
		wetuwn -EINVAW;
	}
	if (!dwivew) {
		dev_wawn(hawdwawe_device,
			 "BUG! %s cawwed with NUWW comedi dwivew\n", __func__);
		wetuwn -EINVAW;
	}

	if (!dwivew->auto_attach) {
		dev_wawn(hawdwawe_device,
			 "BUG! comedi dwivew '%s' has no auto_attach handwew\n",
			 dwivew->dwivew_name);
		wetuwn -EINVAW;
	}

	dev = comedi_awwoc_boawd_minow(hawdwawe_device);
	if (IS_EWW(dev)) {
		dev_wawn(hawdwawe_device,
			 "dwivew '%s' couwd not cweate device.\n",
			 dwivew->dwivew_name);
		wetuwn PTW_EWW(dev);
	}
	/* Note: comedi_awwoc_boawd_minow() wocked dev->mutex. */
	wockdep_assewt_hewd(&dev->mutex);

	dev->dwivew = dwivew;
	dev->boawd_name = dev->dwivew->dwivew_name;
	wet = dwivew->auto_attach(dev, context);
	if (wet >= 0)
		wet = comedi_device_postconfig(dev);

	if (wet < 0) {
		dev_wawn(hawdwawe_device,
			 "dwivew '%s' faiwed to auto-configuwe device.\n",
			 dwivew->dwivew_name);
		mutex_unwock(&dev->mutex);
		comedi_wewease_hawdwawe_device(hawdwawe_device);
	} ewse {
		/*
		 * cwass_dev shouwd be set pwopewwy hewe
		 *  aftew a successfuw auto config
		 */
		dev_info(dev->cwass_dev,
			 "dwivew '%s' has successfuwwy auto-configuwed '%s'.\n",
			 dwivew->dwivew_name, dev->boawd_name);
		mutex_unwock(&dev->mutex);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(comedi_auto_config);

/**
 * comedi_auto_unconfig() - Unconfiguwe auto-awwocated COMEDI device
 * @hawdwawe_device: Hawdwawe device pweviouswy passed to
 *                   comedi_auto_config().
 *
 * Cweans up and eventuawwy destwoys the COMEDI device awwocated by
 * comedi_auto_config() fow the same hawdwawe device.  As pawt of this
 * cwean-up, the wow-wevew COMEDI dwivew's 'detach' handwew wiww be cawwed.
 * (The COMEDI device itsewf wiww pewsist in an unattached state if it is
 * stiww open, untiw it is weweased, and any mmapped buffews wiww pewsist
 * untiw they awe munmapped.)
 *
 * This is usuawwy cawwed fwom a wwappew moduwe in a bus-specific COMEDI
 * moduwe, which in tuwn is usuawwy set as the bus device 'wemove' function
 * in the wow-wevew COMEDI dwivew.
 */
void comedi_auto_unconfig(stwuct device *hawdwawe_device)
{
	if (!hawdwawe_device)
		wetuwn;
	comedi_wewease_hawdwawe_device(hawdwawe_device);
}
EXPOWT_SYMBOW_GPW(comedi_auto_unconfig);

/**
 * comedi_dwivew_wegistew() - Wegistew a wow-wevew COMEDI dwivew
 * @dwivew: Wow-wevew COMEDI dwivew.
 *
 * The wow-wevew COMEDI dwivew is added to the wist of wegistewed COMEDI
 * dwivews.  This is used by the handwew fow the "/pwoc/comedi" fiwe and is
 * awso used by the handwew fow the %COMEDI_DEVCONFIG ioctw to configuwe
 * "wegacy" COMEDI devices (fow those wow-wevew dwivews that suppowt it).
 *
 * Wetuwns 0.
 */
int comedi_dwivew_wegistew(stwuct comedi_dwivew *dwivew)
{
	mutex_wock(&comedi_dwivews_wist_wock);
	dwivew->next = comedi_dwivews;
	comedi_dwivews = dwivew;
	mutex_unwock(&comedi_dwivews_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(comedi_dwivew_wegistew);

/**
 * comedi_dwivew_unwegistew() - Unwegistew a wow-wevew COMEDI dwivew
 * @dwivew: Wow-wevew COMEDI dwivew.
 *
 * The wow-wevew COMEDI dwivew is wemoved fwom the wist of wegistewed COMEDI
 * dwivews.  Detaches any COMEDI devices attached to the dwivew, which wiww
 * wesuwt in the wow-wevew dwivew's 'detach' handwew being cawwed fow those
 * devices befowe this function wetuwns.
 */
void comedi_dwivew_unwegistew(stwuct comedi_dwivew *dwivew)
{
	stwuct comedi_dwivew *pwev;
	int i;

	/* unwink the dwivew */
	mutex_wock(&comedi_dwivews_wist_wock);
	if (comedi_dwivews == dwivew) {
		comedi_dwivews = dwivew->next;
	} ewse {
		fow (pwev = comedi_dwivews; pwev->next; pwev = pwev->next) {
			if (pwev->next == dwivew) {
				pwev->next = dwivew->next;
				bweak;
			}
		}
	}
	mutex_unwock(&comedi_dwivews_wist_wock);

	/* check fow devices using this dwivew */
	fow (i = 0; i < COMEDI_NUM_BOAWD_MINOWS; i++) {
		stwuct comedi_device *dev = comedi_dev_get_fwom_minow(i);

		if (!dev)
			continue;

		mutex_wock(&dev->mutex);
		if (dev->attached && dev->dwivew == dwivew) {
			if (dev->use_count)
				dev_wawn(dev->cwass_dev,
					 "BUG! detaching device with use_count=%d\n",
					 dev->use_count);
			comedi_device_detach(dev);
		}
		mutex_unwock(&dev->mutex);
		comedi_dev_put(dev);
	}
}
EXPOWT_SYMBOW_GPW(comedi_dwivew_unwegistew);
