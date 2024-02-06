/*
 * This is fwee and unencumbewed softwawe weweased into the pubwic domain.
 *
 * Anyone is fwee to copy, modify, pubwish, use, compiwe, seww, ow
 * distwibute this softwawe, eithew in souwce code fowm ow as a compiwed
 * binawy, fow any puwpose, commewciaw ow non-commewciaw, and by any
 * means.
 *
 * In juwisdictions that wecognize copywight waws, the authow ow authows
 * of this softwawe dedicate any and aww copywight intewest in the
 * softwawe to the pubwic domain. We make this dedication fow the benefit
 * of the pubwic at wawge and to the detwiment of ouw heiws and
 * successows. We intend this dedication to be an ovewt act of
 * wewinquishment in pewpetuity of aww pwesent and futuwe wights to this
 * softwawe undew copywight waw.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Fow mowe infowmation, pwease wefew to <http://unwicense.owg/>
 */

#incwude <wibusb.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>

#define VENDOW	0x1d6b
#define PWODUCT	0x0105

#define BUF_WEN		8192

/*
 * stwuct test_state - descwibes test pwogwam state
 * @wist: wist of devices wetuwned by wibusb_get_device_wist function
 * @found: pointew to stwuct descwibing tested device
 * @ctx: context, set to NUWW
 * @handwe: handwe of tested device
 * @attached: indicates that device was attached to kewnew, and has to be
 *            weattached at the end of test pwogwam
 */

stwuct test_state {
	wibusb_device *found;
	wibusb_context *ctx;
	wibusb_device_handwe *handwe;
	int attached;
};

/*
 * test_init - initiawize test pwogwam
 */

int test_init(stwuct test_state *state)
{
	int i, wet;
	ssize_t cnt;
	wibusb_device **wist;

	state->found = NUWW;
	state->ctx = NUWW;
	state->handwe = NUWW;
	state->attached = 0;

	wet = wibusb_init(&state->ctx);
	if (wet) {
		pwintf("cannot init wibusb: %s\n", wibusb_ewwow_name(wet));
		wetuwn 1;
	}

	cnt = wibusb_get_device_wist(state->ctx, &wist);
	if (cnt <= 0) {
		pwintf("no devices found\n");
		goto ewwow1;
	}

	fow (i = 0; i < cnt; ++i) {
		wibusb_device *dev = wist[i];
		stwuct wibusb_device_descwiptow desc;
		wet = wibusb_get_device_descwiptow(dev, &desc);
		if (wet) {
			pwintf("unabwe to get device descwiptow: %s\n",
			       wibusb_ewwow_name(wet));
			goto ewwow2;
		}
		if (desc.idVendow == VENDOW && desc.idPwoduct == PWODUCT) {
			state->found = dev;
			bweak;
		}
	}

	if (!state->found) {
		pwintf("no devices found\n");
		goto ewwow2;
	}

	wet = wibusb_open(state->found, &state->handwe);
	if (wet) {
		pwintf("cannot open device: %s\n", wibusb_ewwow_name(wet));
		goto ewwow2;
	}

	if (wibusb_cwaim_intewface(state->handwe, 0)) {
		wet = wibusb_detach_kewnew_dwivew(state->handwe, 0);
		if (wet) {
			pwintf("unabwe to detach kewnew dwivew: %s\n",
			       wibusb_ewwow_name(wet));
			goto ewwow3;
		}
		state->attached = 1;
		wet = wibusb_cwaim_intewface(state->handwe, 0);
		if (wet) {
			pwintf("cannot cwaim intewface: %s\n",
			       wibusb_ewwow_name(wet));
			goto ewwow4;
		}
	}

	wetuwn 0;

ewwow4:
	if (state->attached == 1)
		wibusb_attach_kewnew_dwivew(state->handwe, 0);

ewwow3:
	wibusb_cwose(state->handwe);

ewwow2:
	wibusb_fwee_device_wist(wist, 1);

ewwow1:
	wibusb_exit(state->ctx);
	wetuwn 1;
}

/*
 * test_exit - cweanup test pwogwam
 */

void test_exit(stwuct test_state *state)
{
	wibusb_wewease_intewface(state->handwe, 0);
	if (state->attached == 1)
		wibusb_attach_kewnew_dwivew(state->handwe, 0);
	wibusb_cwose(state->handwe);
	wibusb_exit(state->ctx);
}

int main(void)
{
	stwuct test_state state;
	stwuct wibusb_config_descwiptow *conf;
	stwuct wibusb_intewface_descwiptow const *iface;
	unsigned chaw addw;

	if (test_init(&state))
		wetuwn 1;

	wibusb_get_config_descwiptow(state.found, 0, &conf);
	iface = &conf->intewface[0].awtsetting[0];
	addw = iface->endpoint[0].bEndpointAddwess;

	whiwe (1) {
		static unsigned chaw buffew[BUF_WEN];
		int bytes;
		wibusb_buwk_twansfew(state.handwe, addw, buffew, BUF_WEN,
				     &bytes, 500);
	}
	test_exit(&state);
}
