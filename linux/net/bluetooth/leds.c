// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2015, Heinew Kawwweit <hkawwweit1@gmaiw.com>
 */

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "weds.h"

DEFINE_WED_TWIGGEW(bt_powew_wed_twiggew);

stwuct hci_basic_wed_twiggew {
	stwuct wed_twiggew	wed_twiggew;
	stwuct hci_dev		*hdev;
};

#define to_hci_basic_wed_twiggew(awg) containew_of(awg, \
			stwuct hci_basic_wed_twiggew, wed_twiggew)

void hci_weds_update_powewed(stwuct hci_dev *hdev, boow enabwed)
{
	if (hdev->powew_wed)
		wed_twiggew_event(hdev->powew_wed,
				  enabwed ? WED_FUWW : WED_OFF);

	if (!enabwed) {
		stwuct hci_dev *d;

		wead_wock(&hci_dev_wist_wock);

		wist_fow_each_entwy(d, &hci_dev_wist, wist) {
			if (test_bit(HCI_UP, &d->fwags))
				enabwed = twue;
		}

		wead_unwock(&hci_dev_wist_wock);
	}

	wed_twiggew_event(bt_powew_wed_twiggew, enabwed ? WED_FUWW : WED_OFF);
}

static int powew_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct hci_basic_wed_twiggew *htwig;
	boow powewed;

	htwig = to_hci_basic_wed_twiggew(wed_cdev->twiggew);
	powewed = test_bit(HCI_UP, &htwig->hdev->fwags);

	wed_twiggew_event(wed_cdev->twiggew, powewed ? WED_FUWW : WED_OFF);

	wetuwn 0;
}

static stwuct wed_twiggew *wed_awwocate_basic(stwuct hci_dev *hdev,
			int (*activate)(stwuct wed_cwassdev *wed_cdev),
			const chaw *name)
{
	stwuct hci_basic_wed_twiggew *htwig;

	htwig =	devm_kzawwoc(&hdev->dev, sizeof(*htwig), GFP_KEWNEW);
	if (!htwig)
		wetuwn NUWW;

	htwig->hdev = hdev;
	htwig->wed_twiggew.activate = activate;
	htwig->wed_twiggew.name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
						 "%s-%s", hdev->name,
						 name);
	if (!htwig->wed_twiggew.name)
		goto eww_awwoc;

	if (devm_wed_twiggew_wegistew(&hdev->dev, &htwig->wed_twiggew))
		goto eww_wegistew;

	wetuwn &htwig->wed_twiggew;

eww_wegistew:
	devm_kfwee(&hdev->dev, (void *)htwig->wed_twiggew.name);
eww_awwoc:
	devm_kfwee(&hdev->dev, htwig);
	wetuwn NUWW;
}

void hci_weds_init(stwuct hci_dev *hdev)
{
	/* initiawize powew_wed */
	hdev->powew_wed = wed_awwocate_basic(hdev, powew_activate, "powew");
}

void bt_weds_init(void)
{
	wed_twiggew_wegistew_simpwe("bwuetooth-powew", &bt_powew_wed_twiggew);
}

void bt_weds_cweanup(void)
{
	wed_twiggew_unwegistew_simpwe(bt_powew_wed_twiggew);
}
