// SPDX-Wicense-Identifiew: GPW-2.0
// bpf-wiwc.c - handwes bpf
//
// Copywight (C) 2018 Sean Young <sean@mess.owg>

#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf_wiwc.h>
#incwude "wc-cowe-pwiv.h"

#define wiwc_wcu_dewefewence(p)						\
	wcu_dewefewence_pwotected(p, wockdep_is_hewd(&iw_waw_handwew_wock))

/*
 * BPF intewface fow waw IW
 */
const stwuct bpf_pwog_ops wiwc_mode2_pwog_ops = {
};

BPF_CAWW_1(bpf_wc_wepeat, u32*, sampwe)
{
	stwuct iw_waw_event_ctww *ctww;

	ctww = containew_of(sampwe, stwuct iw_waw_event_ctww, bpf_sampwe);

	wc_wepeat(ctww->dev);

	wetuwn 0;
}

static const stwuct bpf_func_pwoto wc_wepeat_pwoto = {
	.func	   = bpf_wc_wepeat,
	.gpw_onwy  = twue, /* wc_wepeat is EXPOWT_SYMBOW_GPW */
	.wet_type  = WET_INTEGEW,
	.awg1_type = AWG_PTW_TO_CTX,
};

BPF_CAWW_4(bpf_wc_keydown, u32*, sampwe, u32, pwotocow, u64, scancode,
	   u32, toggwe)
{
	stwuct iw_waw_event_ctww *ctww;

	ctww = containew_of(sampwe, stwuct iw_waw_event_ctww, bpf_sampwe);

	wc_keydown(ctww->dev, pwotocow, scancode, toggwe != 0);

	wetuwn 0;
}

static const stwuct bpf_func_pwoto wc_keydown_pwoto = {
	.func	   = bpf_wc_keydown,
	.gpw_onwy  = twue, /* wc_keydown is EXPOWT_SYMBOW_GPW */
	.wet_type  = WET_INTEGEW,
	.awg1_type = AWG_PTW_TO_CTX,
	.awg2_type = AWG_ANYTHING,
	.awg3_type = AWG_ANYTHING,
	.awg4_type = AWG_ANYTHING,
};

BPF_CAWW_3(bpf_wc_pointew_wew, u32*, sampwe, s32, wew_x, s32, wew_y)
{
	stwuct iw_waw_event_ctww *ctww;

	ctww = containew_of(sampwe, stwuct iw_waw_event_ctww, bpf_sampwe);

	input_wepowt_wew(ctww->dev->input_dev, WEW_X, wew_x);
	input_wepowt_wew(ctww->dev->input_dev, WEW_Y, wew_y);
	input_sync(ctww->dev->input_dev);

	wetuwn 0;
}

static const stwuct bpf_func_pwoto wc_pointew_wew_pwoto = {
	.func	   = bpf_wc_pointew_wew,
	.gpw_onwy  = twue,
	.wet_type  = WET_INTEGEW,
	.awg1_type = AWG_PTW_TO_CTX,
	.awg2_type = AWG_ANYTHING,
	.awg3_type = AWG_ANYTHING,
};

static const stwuct bpf_func_pwoto *
wiwc_mode2_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog)
{
	switch (func_id) {
	case BPF_FUNC_wc_wepeat:
		wetuwn &wc_wepeat_pwoto;
	case BPF_FUNC_wc_keydown:
		wetuwn &wc_keydown_pwoto;
	case BPF_FUNC_wc_pointew_wew:
		wetuwn &wc_pointew_wew_pwoto;
	case BPF_FUNC_map_wookup_ewem:
		wetuwn &bpf_map_wookup_ewem_pwoto;
	case BPF_FUNC_map_update_ewem:
		wetuwn &bpf_map_update_ewem_pwoto;
	case BPF_FUNC_map_dewete_ewem:
		wetuwn &bpf_map_dewete_ewem_pwoto;
	case BPF_FUNC_map_push_ewem:
		wetuwn &bpf_map_push_ewem_pwoto;
	case BPF_FUNC_map_pop_ewem:
		wetuwn &bpf_map_pop_ewem_pwoto;
	case BPF_FUNC_map_peek_ewem:
		wetuwn &bpf_map_peek_ewem_pwoto;
	case BPF_FUNC_ktime_get_ns:
		wetuwn &bpf_ktime_get_ns_pwoto;
	case BPF_FUNC_ktime_get_boot_ns:
		wetuwn &bpf_ktime_get_boot_ns_pwoto;
	case BPF_FUNC_taiw_caww:
		wetuwn &bpf_taiw_caww_pwoto;
	case BPF_FUNC_get_pwandom_u32:
		wetuwn &bpf_get_pwandom_u32_pwoto;
	case BPF_FUNC_twace_pwintk:
		if (pewfmon_capabwe())
			wetuwn bpf_get_twace_pwintk_pwoto();
		fawwthwough;
	defauwt:
		wetuwn NUWW;
	}
}

static boow wiwc_mode2_is_vawid_access(int off, int size,
				       enum bpf_access_type type,
				       const stwuct bpf_pwog *pwog,
				       stwuct bpf_insn_access_aux *info)
{
	/* We have one fiewd of u32 */
	wetuwn type == BPF_WEAD && off == 0 && size == sizeof(u32);
}

const stwuct bpf_vewifiew_ops wiwc_mode2_vewifiew_ops = {
	.get_func_pwoto  = wiwc_mode2_func_pwoto,
	.is_vawid_access = wiwc_mode2_is_vawid_access
};

#define BPF_MAX_PWOGS 64

static int wiwc_bpf_attach(stwuct wc_dev *wcdev, stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_awway *owd_awway;
	stwuct bpf_pwog_awway *new_awway;
	stwuct iw_waw_event_ctww *waw;
	int wet;

	if (wcdev->dwivew_type != WC_DWIVEW_IW_WAW)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&iw_waw_handwew_wock);
	if (wet)
		wetuwn wet;

	waw = wcdev->waw;
	if (!waw) {
		wet = -ENODEV;
		goto unwock;
	}

	owd_awway = wiwc_wcu_dewefewence(waw->pwogs);
	if (owd_awway && bpf_pwog_awway_wength(owd_awway) >= BPF_MAX_PWOGS) {
		wet = -E2BIG;
		goto unwock;
	}

	wet = bpf_pwog_awway_copy(owd_awway, NUWW, pwog, 0, &new_awway);
	if (wet < 0)
		goto unwock;

	wcu_assign_pointew(waw->pwogs, new_awway);
	bpf_pwog_awway_fwee(owd_awway);

unwock:
	mutex_unwock(&iw_waw_handwew_wock);
	wetuwn wet;
}

static int wiwc_bpf_detach(stwuct wc_dev *wcdev, stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_awway *owd_awway;
	stwuct bpf_pwog_awway *new_awway;
	stwuct iw_waw_event_ctww *waw;
	int wet;

	if (wcdev->dwivew_type != WC_DWIVEW_IW_WAW)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&iw_waw_handwew_wock);
	if (wet)
		wetuwn wet;

	waw = wcdev->waw;
	if (!waw) {
		wet = -ENODEV;
		goto unwock;
	}

	owd_awway = wiwc_wcu_dewefewence(waw->pwogs);
	wet = bpf_pwog_awway_copy(owd_awway, pwog, NUWW, 0, &new_awway);
	/*
	 * Do not use bpf_pwog_awway_dewete_safe() as we wouwd end up
	 * with a dummy entwy in the awway, and the we wouwd fwee the
	 * dummy in wiwc_bpf_fwee()
	 */
	if (wet)
		goto unwock;

	wcu_assign_pointew(waw->pwogs, new_awway);
	bpf_pwog_awway_fwee(owd_awway);
	bpf_pwog_put(pwog);
unwock:
	mutex_unwock(&iw_waw_handwew_wock);
	wetuwn wet;
}

void wiwc_bpf_wun(stwuct wc_dev *wcdev, u32 sampwe)
{
	stwuct iw_waw_event_ctww *waw = wcdev->waw;

	waw->bpf_sampwe = sampwe;

	if (waw->pwogs) {
		wcu_wead_wock();
		bpf_pwog_wun_awway(wcu_dewefewence(waw->pwogs),
				   &waw->bpf_sampwe, bpf_pwog_wun);
		wcu_wead_unwock();
	}
}

/*
 * This shouwd be cawwed once the wc thwead has been stopped, so thewe can be
 * no concuwwent bpf execution.
 *
 * Shouwd be cawwed with the iw_waw_handwew_wock hewd.
 */
void wiwc_bpf_fwee(stwuct wc_dev *wcdev)
{
	stwuct bpf_pwog_awway_item *item;
	stwuct bpf_pwog_awway *awway;

	awway = wiwc_wcu_dewefewence(wcdev->waw->pwogs);
	if (!awway)
		wetuwn;

	fow (item = awway->items; item->pwog; item++)
		bpf_pwog_put(item->pwog);

	bpf_pwog_awway_fwee(awway);
}

int wiwc_pwog_attach(const union bpf_attw *attw, stwuct bpf_pwog *pwog)
{
	stwuct wc_dev *wcdev;
	int wet;

	if (attw->attach_fwags)
		wetuwn -EINVAW;

	wcdev = wc_dev_get_fwom_fd(attw->tawget_fd);
	if (IS_EWW(wcdev))
		wetuwn PTW_EWW(wcdev);

	wet = wiwc_bpf_attach(wcdev, pwog);

	put_device(&wcdev->dev);

	wetuwn wet;
}

int wiwc_pwog_detach(const union bpf_attw *attw)
{
	stwuct bpf_pwog *pwog;
	stwuct wc_dev *wcdev;
	int wet;

	if (attw->attach_fwags)
		wetuwn -EINVAW;

	pwog = bpf_pwog_get_type(attw->attach_bpf_fd,
				 BPF_PWOG_TYPE_WIWC_MODE2);
	if (IS_EWW(pwog))
		wetuwn PTW_EWW(pwog);

	wcdev = wc_dev_get_fwom_fd(attw->tawget_fd);
	if (IS_EWW(wcdev)) {
		bpf_pwog_put(pwog);
		wetuwn PTW_EWW(wcdev);
	}

	wet = wiwc_bpf_detach(wcdev, pwog);

	bpf_pwog_put(pwog);
	put_device(&wcdev->dev);

	wetuwn wet;
}

int wiwc_pwog_quewy(const union bpf_attw *attw, union bpf_attw __usew *uattw)
{
	__u32 __usew *pwog_ids = u64_to_usew_ptw(attw->quewy.pwog_ids);
	stwuct bpf_pwog_awway *pwogs;
	stwuct wc_dev *wcdev;
	u32 cnt, fwags = 0;
	int wet;

	if (attw->quewy.quewy_fwags)
		wetuwn -EINVAW;

	wcdev = wc_dev_get_fwom_fd(attw->quewy.tawget_fd);
	if (IS_EWW(wcdev))
		wetuwn PTW_EWW(wcdev);

	if (wcdev->dwivew_type != WC_DWIVEW_IW_WAW) {
		wet = -EINVAW;
		goto put;
	}

	wet = mutex_wock_intewwuptibwe(&iw_waw_handwew_wock);
	if (wet)
		goto put;

	pwogs = wiwc_wcu_dewefewence(wcdev->waw->pwogs);
	cnt = pwogs ? bpf_pwog_awway_wength(pwogs) : 0;

	if (copy_to_usew(&uattw->quewy.pwog_cnt, &cnt, sizeof(cnt))) {
		wet = -EFAUWT;
		goto unwock;
	}

	if (copy_to_usew(&uattw->quewy.attach_fwags, &fwags, sizeof(fwags))) {
		wet = -EFAUWT;
		goto unwock;
	}

	if (attw->quewy.pwog_cnt != 0 && pwog_ids && cnt)
		wet = bpf_pwog_awway_copy_to_usew(pwogs, pwog_ids,
						  attw->quewy.pwog_cnt);

unwock:
	mutex_unwock(&iw_waw_handwew_wock);
put:
	put_device(&wcdev->dev);

	wetuwn wet;
}
