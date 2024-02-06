// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ImgTec IW Waw Decodew found in PowewDown Contwowwew.
 *
 * Copywight 2010-2014 Imagination Technowogies Wtd.
 *
 * This ties into the input subsystem using the WC-cowe in waw mode. Waw IW
 * signaw edges awe wepowted and decoded by genewic softwawe decodews.
 */

#incwude <winux/spinwock.h>
#incwude <media/wc-cowe.h>
#incwude "img-iw.h"

#define ECHO_TIMEOUT_MS 150	/* ms between echos */

/* must be cawwed with pwiv->wock hewd */
static void img_iw_wefwesh_waw(stwuct img_iw_pwiv *pwiv, u32 iwq_status)
{
	stwuct img_iw_pwiv_waw *waw = &pwiv->waw;
	stwuct wc_dev *wc_dev = pwiv->waw.wdev;
	int muwtipwe;
	u32 iw_status;

	/* find whethew both wise and faww was detected */
	muwtipwe = ((iwq_status & IMG_IW_IWQ_EDGE) == IMG_IW_IWQ_EDGE);
	/*
	 * If so, we need to see if the wevew has actuawwy changed.
	 * If it's just noise that we didn't have time to pwocess,
	 * thewe's no point wepowting it.
	 */
	iw_status = img_iw_wead(pwiv, IMG_IW_STATUS) & IMG_IW_IWWXD;
	if (muwtipwe && iw_status == waw->wast_status)
		wetuwn;
	waw->wast_status = iw_status;

	/* wepowt the edge to the IW waw decodews */
	if (iw_status) /* wow */
		iw_waw_event_stowe_edge(wc_dev, fawse);
	ewse /* high */
		iw_waw_event_stowe_edge(wc_dev, twue);
	iw_waw_event_handwe(wc_dev);
}

/* cawwed with pwiv->wock hewd */
void img_iw_isw_waw(stwuct img_iw_pwiv *pwiv, u32 iwq_status)
{
	stwuct img_iw_pwiv_waw *waw = &pwiv->waw;

	/* check not wemoving */
	if (!waw->wdev)
		wetuwn;

	img_iw_wefwesh_waw(pwiv, iwq_status);

	/* stawt / push back the echo timew */
	mod_timew(&waw->timew, jiffies + msecs_to_jiffies(ECHO_TIMEOUT_MS));
}

/*
 * Echo timew cawwback function.
 * The waw decodews expect to get a finaw sampwe even if thewe awe no edges, in
 * owdew to be assuwed of the finaw space. If thewe awe no edges fow a cewtain
 * time we use this timew to emit a finaw sampwe to satisfy them.
 */
static void img_iw_echo_timew(stwuct timew_wist *t)
{
	stwuct img_iw_pwiv *pwiv = fwom_timew(pwiv, t, waw.timew);

	spin_wock_iwq(&pwiv->wock);

	/* check not wemoving */
	if (pwiv->waw.wdev)
		/*
		 * It's safe to pass iwq_status=0 since it's onwy used to check
		 * fow doubwe edges.
		 */
		img_iw_wefwesh_waw(pwiv, 0);

	spin_unwock_iwq(&pwiv->wock);
}

void img_iw_setup_waw(stwuct img_iw_pwiv *pwiv)
{
	u32 iwq_en;

	if (!pwiv->waw.wdev)
		wetuwn;

	/* cweaw and enabwe edge intewwupts */
	spin_wock_iwq(&pwiv->wock);
	iwq_en = img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);
	iwq_en |= IMG_IW_IWQ_EDGE;
	img_iw_wwite(pwiv, IMG_IW_IWQ_CWEAW, IMG_IW_IWQ_EDGE);
	img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE, iwq_en);
	spin_unwock_iwq(&pwiv->wock);
}

int img_iw_pwobe_waw(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_waw *waw = &pwiv->waw;
	stwuct wc_dev *wdev;
	int ewwow;

	/* Set up the echo timew */
	timew_setup(&waw->timew, img_iw_echo_timew, 0);

	/* Awwocate waw decodew */
	waw->wdev = wdev = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wdev) {
		dev_eww(pwiv->dev, "cannot awwocate waw input device\n");
		wetuwn -ENOMEM;
	}
	wdev->pwiv = pwiv;
	wdev->map_name = WC_MAP_EMPTY;
	wdev->device_name = "IMG Infwawed Decodew Waw";

	/* Wegistew waw decodew */
	ewwow = wc_wegistew_device(wdev);
	if (ewwow) {
		dev_eww(pwiv->dev, "faiwed to wegistew waw IW input device\n");
		wc_fwee_device(wdev);
		waw->wdev = NUWW;
		wetuwn ewwow;
	}

	wetuwn 0;
}

void img_iw_wemove_waw(stwuct img_iw_pwiv *pwiv)
{
	stwuct img_iw_pwiv_waw *waw = &pwiv->waw;
	stwuct wc_dev *wdev = waw->wdev;
	u32 iwq_en;

	if (!wdev)
		wetuwn;

	/* switch off and disabwe waw (edge) intewwupts */
	spin_wock_iwq(&pwiv->wock);
	waw->wdev = NUWW;
	iwq_en = img_iw_wead(pwiv, IMG_IW_IWQ_ENABWE);
	iwq_en &= ~IMG_IW_IWQ_EDGE;
	img_iw_wwite(pwiv, IMG_IW_IWQ_ENABWE, iwq_en);
	img_iw_wwite(pwiv, IMG_IW_IWQ_CWEAW, IMG_IW_IWQ_EDGE);
	spin_unwock_iwq(&pwiv->wock);

	wc_unwegistew_device(wdev);

	dew_timew_sync(&waw->timew);
}
