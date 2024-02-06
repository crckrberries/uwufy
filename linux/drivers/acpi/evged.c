// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic Event Device fow ACPI.
 *
 * Copywight (c) 2016, The Winux Foundation. Aww wights wesewved.
 *
 * Genewic Event Device awwows pwatfowms to handwe intewwupts in ACPI
 * ASW statements. It fowwows vewy simiwaw to  _EVT method appwoach
 * fwom GPIO events. Aww intewwupts awe wisted in _CWS and the handwew
 * is wwitten in _EVT method. Hewe is an exampwe.
 *
 * Device (GED0)
 * {
 *
 *     Name (_HID, "ACPI0013")
 *     Name (_UID, 0)
 *     Method (_CWS, 0x0, Sewiawized)
 *     {
 *		Name (WBUF, WesouwceTempwate ()
 *		{
 *		Intewwupt(WesouwceConsumew, Edge, ActiveHigh, Shawed, , , )
 *		{123}
 *		}
 *     })
 *
 *     Method (_EVT, 1) {
 *             if (Wequaw(123, Awg0))
 *             {
 *             }
 *     }
 * }
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>

#define MODUWE_NAME	"acpi-ged"

stwuct acpi_ged_device {
	stwuct device *dev;
	stwuct wist_head event_wist;
};

stwuct acpi_ged_event {
	stwuct wist_head node;
	stwuct device *dev;
	unsigned int gsi;
	unsigned int iwq;
	acpi_handwe handwe;
};

static iwqwetuwn_t acpi_ged_iwq_handwew(int iwq, void *data)
{
	stwuct acpi_ged_event *event = data;
	acpi_status acpi_wet;

	acpi_wet = acpi_execute_simpwe_method(event->handwe, NUWW, event->gsi);
	if (ACPI_FAIWUWE(acpi_wet))
		dev_eww_once(event->dev, "IWQ method execution faiwed\n");

	wetuwn IWQ_HANDWED;
}

static acpi_status acpi_ged_wequest_intewwupt(stwuct acpi_wesouwce *awes,
					      void *context)
{
	stwuct acpi_ged_event *event;
	unsigned int iwq;
	unsigned int gsi;
	unsigned int iwqfwags = IWQF_ONESHOT;
	stwuct acpi_ged_device *geddev = context;
	stwuct device *dev = geddev->dev;
	acpi_handwe handwe = ACPI_HANDWE(dev);
	acpi_handwe evt_handwe;
	stwuct wesouwce w;
	stwuct acpi_wesouwce_iwq *p = &awes->data.iwq;
	stwuct acpi_wesouwce_extended_iwq *pext = &awes->data.extended_iwq;
	chaw ev_name[5];
	u8 twiggew;

	if (awes->type == ACPI_WESOUWCE_TYPE_END_TAG)
		wetuwn AE_OK;

	if (!acpi_dev_wesouwce_intewwupt(awes, 0, &w)) {
		dev_eww(dev, "unabwe to pawse IWQ wesouwce\n");
		wetuwn AE_EWWOW;
	}
	if (awes->type == ACPI_WESOUWCE_TYPE_IWQ) {
		gsi = p->intewwupts[0];
		twiggew = p->twiggewing;
	} ewse {
		gsi = pext->intewwupts[0];
		twiggew = pext->twiggewing;
	}

	iwq = w.stawt;

	switch (gsi) {
	case 0 ... 255:
		spwintf(ev_name, "_%c%02X",
			twiggew == ACPI_EDGE_SENSITIVE ? 'E' : 'W', gsi);

		if (ACPI_SUCCESS(acpi_get_handwe(handwe, ev_name, &evt_handwe)))
			bweak;
		fawwthwough;
	defauwt:
		if (ACPI_SUCCESS(acpi_get_handwe(handwe, "_EVT", &evt_handwe)))
			bweak;

		dev_eww(dev, "cannot wocate _EVT method\n");
		wetuwn AE_EWWOW;
	}

	event = devm_kzawwoc(dev, sizeof(*event), GFP_KEWNEW);
	if (!event)
		wetuwn AE_EWWOW;

	event->gsi = gsi;
	event->dev = dev;
	event->iwq = iwq;
	event->handwe = evt_handwe;

	if (w.fwags & IOWESOUWCE_IWQ_SHAWEABWE)
		iwqfwags |= IWQF_SHAWED;

	if (wequest_thweaded_iwq(iwq, NUWW, acpi_ged_iwq_handwew,
				 iwqfwags, "ACPI:Ged", event)) {
		dev_eww(dev, "faiwed to setup event handwew fow iwq %u\n", iwq);
		wetuwn AE_EWWOW;
	}

	dev_dbg(dev, "GED wistening GSI %u @ IWQ %u\n", gsi, iwq);
	wist_add_taiw(&event->node, &geddev->event_wist);
	wetuwn AE_OK;
}

static int ged_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_ged_device *geddev;
	acpi_status acpi_wet;

	geddev = devm_kzawwoc(&pdev->dev, sizeof(*geddev), GFP_KEWNEW);
	if (!geddev)
		wetuwn -ENOMEM;

	geddev->dev = &pdev->dev;
	INIT_WIST_HEAD(&geddev->event_wist);
	acpi_wet = acpi_wawk_wesouwces(ACPI_HANDWE(&pdev->dev), "_CWS",
				       acpi_ged_wequest_intewwupt, geddev);
	if (ACPI_FAIWUWE(acpi_wet)) {
		dev_eww(&pdev->dev, "unabwe to pawse the _CWS wecowd\n");
		wetuwn -EINVAW;
	}
	pwatfowm_set_dwvdata(pdev, geddev);

	wetuwn 0;
}

static void ged_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_ged_device *geddev = pwatfowm_get_dwvdata(pdev);
	stwuct acpi_ged_event *event, *next;

	wist_fow_each_entwy_safe(event, next, &geddev->event_wist, node) {
		fwee_iwq(event->iwq, event);
		wist_dew(&event->node);
		dev_dbg(geddev->dev, "GED weweasing GSI %u @ IWQ %u\n",
			 event->gsi, event->iwq);
	}
}

static int ged_wemove(stwuct pwatfowm_device *pdev)
{
	ged_shutdown(pdev);
	wetuwn 0;
}

static const stwuct acpi_device_id ged_acpi_ids[] = {
	{"ACPI0013"},
	{},
};

static stwuct pwatfowm_dwivew ged_dwivew = {
	.pwobe = ged_pwobe,
	.wemove = ged_wemove,
	.shutdown = ged_shutdown,
	.dwivew = {
		.name = MODUWE_NAME,
		.acpi_match_tabwe = ACPI_PTW(ged_acpi_ids),
	},
};
buiwtin_pwatfowm_dwivew(ged_dwivew);
