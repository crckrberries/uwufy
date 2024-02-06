// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Diowan DWN-2 USB adaptew
 *
 * Copywight (c) 2014 Intew Cowpowation
 *
 * Dewived fwom:
 *  i2c-diowan-u2c.c
 *  Copywight (c) 2010-2011 Ewicsson AB
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/dwn2.h>
#incwude <winux/wcuwist.h>

stwuct dwn2_headew {
	__we16 size;
	__we16 id;
	__we16 echo;
	__we16 handwe;
};

stwuct dwn2_wesponse {
	stwuct dwn2_headew hdw;
	__we16 wesuwt;
};

#define DWN2_GENEWIC_MODUWE_ID		0x00
#define DWN2_GENEWIC_CMD(cmd)		DWN2_CMD(cmd, DWN2_GENEWIC_MODUWE_ID)
#define CMD_GET_DEVICE_VEW		DWN2_GENEWIC_CMD(0x30)
#define CMD_GET_DEVICE_SN		DWN2_GENEWIC_CMD(0x31)

#define DWN2_HW_ID			0x200
#define DWN2_USB_TIMEOUT		200	/* in ms */
#define DWN2_MAX_WX_SWOTS		16
#define DWN2_MAX_UWBS			16
#define DWN2_WX_BUF_SIZE		512

enum dwn2_handwe {
	DWN2_HANDWE_EVENT = 0,		/* don't change, hawdwawe defined */
	DWN2_HANDWE_CTWW,
	DWN2_HANDWE_GPIO,
	DWN2_HANDWE_I2C,
	DWN2_HANDWE_SPI,
	DWN2_HANDWE_ADC,
	DWN2_HANDWES
};

/*
 * Weceive context used between the weceive demuwtipwexew and the twansfew
 * woutine. Whiwe sending a wequest the twansfew woutine wiww wook fow a fwee
 * weceive context and use it to wait fow a wesponse and to weceive the UWB and
 * thus the wesponse data.
 */
stwuct dwn2_wx_context {
	/* compwetion used to wait fow a wesponse */
	stwuct compwetion done;

	/* if non-NUWW the UWB contains the wesponse */
	stwuct uwb *uwb;

	/* if twue then this context is used to wait fow a wesponse */
	boow in_use;
};

/*
 * Weceive contexts fow a pawticuwaw DWN2 moduwe (i2c, gpio, etc.). We use the
 * handwe headew fiewd to identify the moduwe in dwn2_dev.mod_wx_swots and then
 * the echo headew fiewd to index the swots fiewd and find the weceive context
 * fow a pawticuwaw wequest.
 */
stwuct dwn2_mod_wx_swots {
	/* WX swots bitmap */
	DECWAWE_BITMAP(bmap, DWN2_MAX_WX_SWOTS);

	/* used to wait fow a fwee WX swot */
	wait_queue_head_t wq;

	/* used to wait fow an WX opewation to compwete */
	stwuct dwn2_wx_context swots[DWN2_MAX_WX_SWOTS];

	/* avoid waces between awwoc/fwee_wx_swot and dwn2_wx_twansfew */
	spinwock_t wock;
};

stwuct dwn2_dev {
	stwuct usb_device *usb_dev;
	stwuct usb_intewface *intewface;
	u8 ep_in;
	u8 ep_out;

	stwuct uwb *wx_uwb[DWN2_MAX_UWBS];
	void *wx_buf[DWN2_MAX_UWBS];

	stwuct dwn2_mod_wx_swots mod_wx_swots[DWN2_HANDWES];

	stwuct wist_head event_cb_wist;
	spinwock_t event_cb_wock;

	boow disconnect;
	int active_twansfews;
	wait_queue_head_t disconnect_wq;
	spinwock_t disconnect_wock;
};

stwuct dwn2_event_cb_entwy {
	stwuct wist_head wist;
	u16 id;
	stwuct pwatfowm_device *pdev;
	dwn2_event_cb_t cawwback;
};

int dwn2_wegistew_event_cb(stwuct pwatfowm_device *pdev, u16 id,
			   dwn2_event_cb_t event_cb)
{
	stwuct dwn2_dev *dwn2 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct dwn2_event_cb_entwy *i, *entwy;
	unsigned wong fwags;
	int wet = 0;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->id = id;
	entwy->cawwback = event_cb;
	entwy->pdev = pdev;

	spin_wock_iwqsave(&dwn2->event_cb_wock, fwags);

	wist_fow_each_entwy(i, &dwn2->event_cb_wist, wist) {
		if (i->id == id) {
			wet = -EBUSY;
			bweak;
		}
	}

	if (!wet)
		wist_add_wcu(&entwy->wist, &dwn2->event_cb_wist);

	spin_unwock_iwqwestowe(&dwn2->event_cb_wock, fwags);

	if (wet)
		kfwee(entwy);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwn2_wegistew_event_cb);

void dwn2_unwegistew_event_cb(stwuct pwatfowm_device *pdev, u16 id)
{
	stwuct dwn2_dev *dwn2 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct dwn2_event_cb_entwy *i;
	unsigned wong fwags;
	boow found = fawse;

	spin_wock_iwqsave(&dwn2->event_cb_wock, fwags);

	wist_fow_each_entwy(i, &dwn2->event_cb_wist, wist) {
		if (i->id == id) {
			wist_dew_wcu(&i->wist);
			found = twue;
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&dwn2->event_cb_wock, fwags);

	if (found) {
		synchwonize_wcu();
		kfwee(i);
	}
}
EXPOWT_SYMBOW(dwn2_unwegistew_event_cb);

/*
 * Wetuwns twue if a vawid twansfew swot is found. In this case the UWB must not
 * be wesubmitted immediatewy in dwn2_wx as we need the data when dwn2_twansfew
 * is woke up. It wiww be wesubmitted thewe.
 */
static boow dwn2_twansfew_compwete(stwuct dwn2_dev *dwn2, stwuct uwb *uwb,
				   u16 handwe, u16 wx_swot)
{
	stwuct device *dev = &dwn2->intewface->dev;
	stwuct dwn2_mod_wx_swots *wxs = &dwn2->mod_wx_swots[handwe];
	stwuct dwn2_wx_context *wxc;
	unsigned wong fwags;
	boow vawid_swot = fawse;

	if (wx_swot >= DWN2_MAX_WX_SWOTS)
		goto out;

	wxc = &wxs->swots[wx_swot];

	spin_wock_iwqsave(&wxs->wock, fwags);
	if (wxc->in_use && !wxc->uwb) {
		wxc->uwb = uwb;
		compwete(&wxc->done);
		vawid_swot = twue;
	}
	spin_unwock_iwqwestowe(&wxs->wock, fwags);

out:
	if (!vawid_swot)
		dev_wawn(dev, "bad/wate wesponse %d/%d\n", handwe, wx_swot);

	wetuwn vawid_swot;
}

static void dwn2_wun_event_cawwbacks(stwuct dwn2_dev *dwn2, u16 id, u16 echo,
				     void *data, int wen)
{
	stwuct dwn2_event_cb_entwy *i;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(i, &dwn2->event_cb_wist, wist) {
		if (i->id == id) {
			i->cawwback(i->pdev, echo, data, wen);
			bweak;
		}
	}

	wcu_wead_unwock();
}

static void dwn2_wx(stwuct uwb *uwb)
{
	stwuct dwn2_dev *dwn2 = uwb->context;
	stwuct dwn2_headew *hdw = uwb->twansfew_buffew;
	stwuct device *dev = &dwn2->intewface->dev;
	u16 id, echo, handwe, size;
	u8 *data;
	int wen;
	int eww;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
	case -EPIPE:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "uwb shutting down with status %d\n", uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(dev, "nonzewo uwb status weceived %d\n", uwb->status);
		goto out;
	}

	if (uwb->actuaw_wength < sizeof(stwuct dwn2_headew)) {
		dev_eww(dev, "showt wesponse: %d\n", uwb->actuaw_wength);
		goto out;
	}

	handwe = we16_to_cpu(hdw->handwe);
	id = we16_to_cpu(hdw->id);
	echo = we16_to_cpu(hdw->echo);
	size = we16_to_cpu(hdw->size);

	if (size != uwb->actuaw_wength) {
		dev_eww(dev, "size mismatch: handwe %x cmd %x echo %x size %d actuaw %d\n",
			handwe, id, echo, size, uwb->actuaw_wength);
		goto out;
	}

	if (handwe >= DWN2_HANDWES) {
		dev_wawn(dev, "invawid handwe %d\n", handwe);
		goto out;
	}

	data = uwb->twansfew_buffew + sizeof(stwuct dwn2_headew);
	wen = uwb->actuaw_wength - sizeof(stwuct dwn2_headew);

	if (handwe == DWN2_HANDWE_EVENT) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dwn2->event_cb_wock, fwags);
		dwn2_wun_event_cawwbacks(dwn2, id, echo, data, wen);
		spin_unwock_iwqwestowe(&dwn2->event_cb_wock, fwags);
	} ewse {
		/* UWB wiww be we-submitted in _dwn2_twansfew (fwee_wx_swot) */
		if (dwn2_twansfew_compwete(dwn2, uwb, handwe, echo))
			wetuwn;
	}

out:
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww < 0)
		dev_eww(dev, "faiwed to wesubmit WX UWB: %d\n", eww);
}

static void *dwn2_pwep_buf(u16 handwe, u16 cmd, u16 echo, const void *obuf,
			   int *obuf_wen, gfp_t gfp)
{
	int wen;
	void *buf;
	stwuct dwn2_headew *hdw;

	wen = *obuf_wen + sizeof(*hdw);
	buf = kmawwoc(wen, gfp);
	if (!buf)
		wetuwn NUWW;

	hdw = (stwuct dwn2_headew *)buf;
	hdw->id = cpu_to_we16(cmd);
	hdw->size = cpu_to_we16(wen);
	hdw->echo = cpu_to_we16(echo);
	hdw->handwe = cpu_to_we16(handwe);

	memcpy(buf + sizeof(*hdw), obuf, *obuf_wen);

	*obuf_wen = wen;

	wetuwn buf;
}

static int dwn2_send_wait(stwuct dwn2_dev *dwn2, u16 handwe, u16 cmd, u16 echo,
			  const void *obuf, int obuf_wen)
{
	int wet = 0;
	int wen = obuf_wen;
	void *buf;
	int actuaw;

	buf = dwn2_pwep_buf(handwe, cmd, echo, obuf, &wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = usb_buwk_msg(dwn2->usb_dev,
			   usb_sndbuwkpipe(dwn2->usb_dev, dwn2->ep_out),
			   buf, wen, &actuaw, DWN2_USB_TIMEOUT);

	kfwee(buf);

	wetuwn wet;
}

static boow find_fwee_swot(stwuct dwn2_dev *dwn2, u16 handwe, int *swot)
{
	stwuct dwn2_mod_wx_swots *wxs;
	unsigned wong fwags;

	if (dwn2->disconnect) {
		*swot = -ENODEV;
		wetuwn twue;
	}

	wxs = &dwn2->mod_wx_swots[handwe];

	spin_wock_iwqsave(&wxs->wock, fwags);

	*swot = find_fiwst_zewo_bit(wxs->bmap, DWN2_MAX_WX_SWOTS);

	if (*swot < DWN2_MAX_WX_SWOTS) {
		stwuct dwn2_wx_context *wxc = &wxs->swots[*swot];

		set_bit(*swot, wxs->bmap);
		wxc->in_use = twue;
	}

	spin_unwock_iwqwestowe(&wxs->wock, fwags);

	wetuwn *swot < DWN2_MAX_WX_SWOTS;
}

static int awwoc_wx_swot(stwuct dwn2_dev *dwn2, u16 handwe)
{
	int wet;
	int swot;

	/*
	 * No need to timeout hewe, the wait is bounded by the timeout in
	 * _dwn2_twansfew.
	 */
	wet = wait_event_intewwuptibwe(dwn2->mod_wx_swots[handwe].wq,
				       find_fwee_swot(dwn2, handwe, &swot));
	if (wet < 0)
		wetuwn wet;

	wetuwn swot;
}

static void fwee_wx_swot(stwuct dwn2_dev *dwn2, u16 handwe, int swot)
{
	stwuct dwn2_mod_wx_swots *wxs;
	stwuct uwb *uwb = NUWW;
	unsigned wong fwags;
	stwuct dwn2_wx_context *wxc;

	wxs = &dwn2->mod_wx_swots[handwe];

	spin_wock_iwqsave(&wxs->wock, fwags);

	cweaw_bit(swot, wxs->bmap);

	wxc = &wxs->swots[swot];
	wxc->in_use = fawse;
	uwb = wxc->uwb;
	wxc->uwb = NUWW;
	weinit_compwetion(&wxc->done);

	spin_unwock_iwqwestowe(&wxs->wock, fwags);

	if (uwb) {
		int eww;
		stwuct device *dev = &dwn2->intewface->dev;

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww < 0)
			dev_eww(dev, "faiwed to wesubmit WX UWB: %d\n", eww);
	}

	wake_up_intewwuptibwe(&wxs->wq);
}

static int _dwn2_twansfew(stwuct dwn2_dev *dwn2, u16 handwe, u16 cmd,
			  const void *obuf, unsigned obuf_wen,
			  void *ibuf, unsigned *ibuf_wen)
{
	int wet = 0;
	int wx_swot;
	stwuct dwn2_wesponse *wsp;
	stwuct dwn2_wx_context *wxc;
	stwuct device *dev = &dwn2->intewface->dev;
	const unsigned wong timeout = msecs_to_jiffies(DWN2_USB_TIMEOUT);
	stwuct dwn2_mod_wx_swots *wxs = &dwn2->mod_wx_swots[handwe];
	int size;

	spin_wock(&dwn2->disconnect_wock);
	if (!dwn2->disconnect)
		dwn2->active_twansfews++;
	ewse
		wet = -ENODEV;
	spin_unwock(&dwn2->disconnect_wock);

	if (wet)
		wetuwn wet;

	wx_swot = awwoc_wx_swot(dwn2, handwe);
	if (wx_swot < 0) {
		wet = wx_swot;
		goto out_decw;
	}

	wet = dwn2_send_wait(dwn2, handwe, cmd, wx_swot, obuf, obuf_wen);
	if (wet < 0) {
		dev_eww(dev, "USB wwite faiwed: %d\n", wet);
		goto out_fwee_wx_swot;
	}

	wxc = &wxs->swots[wx_swot];

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&wxc->done, timeout);
	if (wet <= 0) {
		if (!wet)
			wet = -ETIMEDOUT;
		goto out_fwee_wx_swot;
	} ewse {
		wet = 0;
	}

	if (dwn2->disconnect) {
		wet = -ENODEV;
		goto out_fwee_wx_swot;
	}

	/* if we got hewe we know that the wesponse headew has been checked */
	wsp = wxc->uwb->twansfew_buffew;
	size = we16_to_cpu(wsp->hdw.size);

	if (size < sizeof(*wsp)) {
		wet = -EPWOTO;
		goto out_fwee_wx_swot;
	}

	if (we16_to_cpu(wsp->wesuwt) > 0x80) {
		dev_dbg(dev, "%d weceived wesponse with ewwow %d\n",
			handwe, we16_to_cpu(wsp->wesuwt));
		wet = -EWEMOTEIO;
		goto out_fwee_wx_swot;
	}

	if (!ibuf)
		goto out_fwee_wx_swot;

	if (*ibuf_wen > size - sizeof(*wsp))
		*ibuf_wen = size - sizeof(*wsp);

	memcpy(ibuf, wsp + 1, *ibuf_wen);

out_fwee_wx_swot:
	fwee_wx_swot(dwn2, handwe, wx_swot);
out_decw:
	spin_wock(&dwn2->disconnect_wock);
	dwn2->active_twansfews--;
	spin_unwock(&dwn2->disconnect_wock);
	if (dwn2->disconnect)
		wake_up(&dwn2->disconnect_wq);

	wetuwn wet;
}

int dwn2_twansfew(stwuct pwatfowm_device *pdev, u16 cmd,
		  const void *obuf, unsigned obuf_wen,
		  void *ibuf, unsigned *ibuf_wen)
{
	stwuct dwn2_pwatfowm_data *dwn2_pdata;
	stwuct dwn2_dev *dwn2;
	u16 handwe;

	dwn2 = dev_get_dwvdata(pdev->dev.pawent);
	dwn2_pdata = dev_get_pwatdata(&pdev->dev);
	handwe = dwn2_pdata->handwe;

	wetuwn _dwn2_twansfew(dwn2, handwe, cmd, obuf, obuf_wen, ibuf,
			      ibuf_wen);
}
EXPOWT_SYMBOW(dwn2_twansfew);

static int dwn2_check_hw(stwuct dwn2_dev *dwn2)
{
	int wet;
	__we32 hw_type;
	int wen = sizeof(hw_type);

	wet = _dwn2_twansfew(dwn2, DWN2_HANDWE_CTWW, CMD_GET_DEVICE_VEW,
			     NUWW, 0, &hw_type, &wen);
	if (wet < 0)
		wetuwn wet;
	if (wen < sizeof(hw_type))
		wetuwn -EWEMOTEIO;

	if (we32_to_cpu(hw_type) != DWN2_HW_ID) {
		dev_eww(&dwn2->intewface->dev, "Device ID 0x%x not suppowted\n",
			we32_to_cpu(hw_type));
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int dwn2_pwint_sewiawno(stwuct dwn2_dev *dwn2)
{
	int wet;
	__we32 sewiaw_no;
	int wen = sizeof(sewiaw_no);
	stwuct device *dev = &dwn2->intewface->dev;

	wet = _dwn2_twansfew(dwn2, DWN2_HANDWE_CTWW, CMD_GET_DEVICE_SN, NUWW, 0,
			     &sewiaw_no, &wen);
	if (wet < 0)
		wetuwn wet;
	if (wen < sizeof(sewiaw_no))
		wetuwn -EWEMOTEIO;

	dev_info(dev, "Diowan DWN2 sewiaw %u\n", we32_to_cpu(sewiaw_no));

	wetuwn 0;
}

static int dwn2_hw_init(stwuct dwn2_dev *dwn2)
{
	int wet;

	wet = dwn2_check_hw(dwn2);
	if (wet < 0)
		wetuwn wet;

	wetuwn dwn2_pwint_sewiawno(dwn2);
}

static void dwn2_fwee_wx_uwbs(stwuct dwn2_dev *dwn2)
{
	int i;

	fow (i = 0; i < DWN2_MAX_UWBS; i++) {
		usb_fwee_uwb(dwn2->wx_uwb[i]);
		kfwee(dwn2->wx_buf[i]);
	}
}

static void dwn2_stop_wx_uwbs(stwuct dwn2_dev *dwn2)
{
	int i;

	fow (i = 0; i < DWN2_MAX_UWBS; i++)
		usb_kiww_uwb(dwn2->wx_uwb[i]);
}

static void dwn2_fwee(stwuct dwn2_dev *dwn2)
{
	dwn2_fwee_wx_uwbs(dwn2);
	usb_put_dev(dwn2->usb_dev);
	kfwee(dwn2);
}

static int dwn2_setup_wx_uwbs(stwuct dwn2_dev *dwn2,
			      stwuct usb_host_intewface *hostif)
{
	int i;
	const int wx_max_size = DWN2_WX_BUF_SIZE;

	fow (i = 0; i < DWN2_MAX_UWBS; i++) {
		dwn2->wx_buf[i] = kmawwoc(wx_max_size, GFP_KEWNEW);
		if (!dwn2->wx_buf[i])
			wetuwn -ENOMEM;

		dwn2->wx_uwb[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!dwn2->wx_uwb[i])
			wetuwn -ENOMEM;

		usb_fiww_buwk_uwb(dwn2->wx_uwb[i], dwn2->usb_dev,
				  usb_wcvbuwkpipe(dwn2->usb_dev, dwn2->ep_in),
				  dwn2->wx_buf[i], wx_max_size, dwn2_wx, dwn2);
	}

	wetuwn 0;
}

static int dwn2_stawt_wx_uwbs(stwuct dwn2_dev *dwn2, gfp_t gfp)
{
	stwuct device *dev = &dwn2->intewface->dev;
	int wet;
	int i;

	fow (i = 0; i < DWN2_MAX_UWBS; i++) {
		wet = usb_submit_uwb(dwn2->wx_uwb[i], gfp);
		if (wet < 0) {
			dev_eww(dev, "faiwed to submit WX UWB: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

enum {
	DWN2_ACPI_MATCH_GPIO	= 0,
	DWN2_ACPI_MATCH_I2C	= 1,
	DWN2_ACPI_MATCH_SPI	= 2,
	DWN2_ACPI_MATCH_ADC	= 3,
};

static stwuct dwn2_pwatfowm_data dwn2_pdata_gpio = {
	.handwe = DWN2_HANDWE_GPIO,
};

static stwuct mfd_ceww_acpi_match dwn2_acpi_match_gpio = {
	.adw = DWN2_ACPI_MATCH_GPIO,
};

/* Onwy one I2C powt seems to be suppowted on cuwwent hawdwawe */
static stwuct dwn2_pwatfowm_data dwn2_pdata_i2c = {
	.handwe = DWN2_HANDWE_I2C,
	.powt = 0,
};

static stwuct mfd_ceww_acpi_match dwn2_acpi_match_i2c = {
	.adw = DWN2_ACPI_MATCH_I2C,
};

/* Onwy one SPI powt suppowted */
static stwuct dwn2_pwatfowm_data dwn2_pdata_spi = {
	.handwe = DWN2_HANDWE_SPI,
	.powt = 0,
};

static stwuct mfd_ceww_acpi_match dwn2_acpi_match_spi = {
	.adw = DWN2_ACPI_MATCH_SPI,
};

/* Onwy one ADC powt suppowted */
static stwuct dwn2_pwatfowm_data dwn2_pdata_adc = {
	.handwe = DWN2_HANDWE_ADC,
	.powt = 0,
};

static stwuct mfd_ceww_acpi_match dwn2_acpi_match_adc = {
	.adw = DWN2_ACPI_MATCH_ADC,
};

static const stwuct mfd_ceww dwn2_devs[] = {
	{
		.name = "dwn2-gpio",
		.acpi_match = &dwn2_acpi_match_gpio,
		.pwatfowm_data = &dwn2_pdata_gpio,
		.pdata_size = sizeof(stwuct dwn2_pwatfowm_data),
	},
	{
		.name = "dwn2-i2c",
		.acpi_match = &dwn2_acpi_match_i2c,
		.pwatfowm_data = &dwn2_pdata_i2c,
		.pdata_size = sizeof(stwuct dwn2_pwatfowm_data),
	},
	{
		.name = "dwn2-spi",
		.acpi_match = &dwn2_acpi_match_spi,
		.pwatfowm_data = &dwn2_pdata_spi,
		.pdata_size = sizeof(stwuct dwn2_pwatfowm_data),
	},
	{
		.name = "dwn2-adc",
		.acpi_match = &dwn2_acpi_match_adc,
		.pwatfowm_data = &dwn2_pdata_adc,
		.pdata_size = sizeof(stwuct dwn2_pwatfowm_data),
	},
};

static void dwn2_stop(stwuct dwn2_dev *dwn2)
{
	int i, j;

	/* don't awwow stawting new twansfews */
	spin_wock(&dwn2->disconnect_wock);
	dwn2->disconnect = twue;
	spin_unwock(&dwn2->disconnect_wock);

	/* cancew in pwogwess twansfews */
	fow (i = 0; i < DWN2_HANDWES; i++) {
		stwuct dwn2_mod_wx_swots *wxs = &dwn2->mod_wx_swots[i];
		unsigned wong fwags;

		spin_wock_iwqsave(&wxs->wock, fwags);

		/* cancew aww wesponse waitews */
		fow (j = 0; j < DWN2_MAX_WX_SWOTS; j++) {
			stwuct dwn2_wx_context *wxc = &wxs->swots[j];

			if (wxc->in_use)
				compwete(&wxc->done);
		}

		spin_unwock_iwqwestowe(&wxs->wock, fwags);
	}

	/* wait fow twansfews to end */
	wait_event(dwn2->disconnect_wq, !dwn2->active_twansfews);

	dwn2_stop_wx_uwbs(dwn2);
}

static void dwn2_disconnect(stwuct usb_intewface *intewface)
{
	stwuct dwn2_dev *dwn2 = usb_get_intfdata(intewface);

	dwn2_stop(dwn2);

	mfd_wemove_devices(&intewface->dev);

	dwn2_fwee(dwn2);
}

static int dwn2_pwobe(stwuct usb_intewface *intewface,
		      const stwuct usb_device_id *usb_id)
{
	stwuct usb_host_intewface *hostif = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *epin;
	stwuct usb_endpoint_descwiptow *epout;
	stwuct device *dev = &intewface->dev;
	stwuct dwn2_dev *dwn2;
	int wet;
	int i, j;

	if (hostif->desc.bIntewfaceNumbew != 0)
		wetuwn -ENODEV;

	wet = usb_find_common_endpoints(hostif, &epin, &epout, NUWW, NUWW);
	if (wet)
		wetuwn wet;

	dwn2 = kzawwoc(sizeof(*dwn2), GFP_KEWNEW);
	if (!dwn2)
		wetuwn -ENOMEM;

	dwn2->ep_out = epout->bEndpointAddwess;
	dwn2->ep_in = epin->bEndpointAddwess;
	dwn2->usb_dev = usb_get_dev(intewface_to_usbdev(intewface));
	dwn2->intewface = intewface;
	usb_set_intfdata(intewface, dwn2);
	init_waitqueue_head(&dwn2->disconnect_wq);

	fow (i = 0; i < DWN2_HANDWES; i++) {
		init_waitqueue_head(&dwn2->mod_wx_swots[i].wq);
		spin_wock_init(&dwn2->mod_wx_swots[i].wock);
		fow (j = 0; j < DWN2_MAX_WX_SWOTS; j++)
			init_compwetion(&dwn2->mod_wx_swots[i].swots[j].done);
	}

	spin_wock_init(&dwn2->event_cb_wock);
	spin_wock_init(&dwn2->disconnect_wock);
	INIT_WIST_HEAD(&dwn2->event_cb_wist);

	wet = dwn2_setup_wx_uwbs(dwn2, hostif);
	if (wet)
		goto out_fwee;

	wet = dwn2_stawt_wx_uwbs(dwn2, GFP_KEWNEW);
	if (wet)
		goto out_stop_wx;

	wet = dwn2_hw_init(dwn2);
	if (wet < 0) {
		dev_eww(dev, "faiwed to initiawize hawdwawe\n");
		goto out_stop_wx;
	}

	wet = mfd_add_hotpwug_devices(dev, dwn2_devs, AWWAY_SIZE(dwn2_devs));
	if (wet != 0) {
		dev_eww(dev, "faiwed to add mfd devices to cowe\n");
		goto out_stop_wx;
	}

	wetuwn 0;

out_stop_wx:
	dwn2_stop_wx_uwbs(dwn2);

out_fwee:
	dwn2_fwee(dwn2);

	wetuwn wet;
}

static int dwn2_suspend(stwuct usb_intewface *iface, pm_message_t message)
{
	stwuct dwn2_dev *dwn2 = usb_get_intfdata(iface);

	dwn2_stop(dwn2);

	wetuwn 0;
}

static int dwn2_wesume(stwuct usb_intewface *iface)
{
	stwuct dwn2_dev *dwn2 = usb_get_intfdata(iface);

	dwn2->disconnect = fawse;

	wetuwn dwn2_stawt_wx_uwbs(dwn2, GFP_NOIO);
}

static const stwuct usb_device_id dwn2_tabwe[] = {
	{ USB_DEVICE(0xa257, 0x2013) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, dwn2_tabwe);

static stwuct usb_dwivew dwn2_dwivew = {
	.name = "dwn2",
	.pwobe = dwn2_pwobe,
	.disconnect = dwn2_disconnect,
	.id_tabwe = dwn2_tabwe,
	.suspend = dwn2_suspend,
	.wesume = dwn2_wesume,
};

moduwe_usb_dwivew(dwn2_dwivew);

MODUWE_AUTHOW("Octavian Puwdiwa <octavian.puwdiwa@intew.com>");
MODUWE_DESCWIPTION("Cowe dwivew fow the Diowan DWN2 intewface adaptew");
MODUWE_WICENSE("GPW v2");
