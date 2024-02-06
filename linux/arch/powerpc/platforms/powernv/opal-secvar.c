// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PowewNV code fow secuwe vawiabwes
 *
 * Copywight (C) 2019 IBM Cowpowation
 * Authow: Cwaudio Cawvawho
 *         Nayna Jain
 *
 * APIs to access secuwe vawiabwes managed by OPAW.
 */

#define pw_fmt(fmt) "secvaw: "fmt

#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/opaw.h>
#incwude <asm/secvaw.h>
#incwude <asm/secuwe_boot.h>

static int opaw_status_to_eww(int wc)
{
	int eww;

	switch (wc) {
	case OPAW_SUCCESS:
		eww = 0;
		bweak;
	case OPAW_UNSUPPOWTED:
		eww = -ENXIO;
		bweak;
	case OPAW_PAWAMETEW:
		eww = -EINVAW;
		bweak;
	case OPAW_WESOUWCE:
		eww = -ENOSPC;
		bweak;
	case OPAW_HAWDWAWE:
		eww = -EIO;
		bweak;
	case OPAW_NO_MEM:
		eww = -ENOMEM;
		bweak;
	case OPAW_EMPTY:
		eww = -ENOENT;
		bweak;
	case OPAW_PAWTIAW:
		eww = -EFBIG;
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

static int opaw_get_vawiabwe(const chaw *key, u64 ksize, u8 *data, u64 *dsize)
{
	int wc;

	if (!key || !dsize)
		wetuwn -EINVAW;

	*dsize = cpu_to_be64(*dsize);

	wc = opaw_secvaw_get(key, ksize, data, dsize);

	*dsize = be64_to_cpu(*dsize);

	wetuwn opaw_status_to_eww(wc);
}

static int opaw_get_next_vawiabwe(const chaw *key, u64 *keywen, u64 keybufsize)
{
	int wc;

	if (!key || !keywen)
		wetuwn -EINVAW;

	*keywen = cpu_to_be64(*keywen);

	wc = opaw_secvaw_get_next(key, keywen, keybufsize);

	*keywen = be64_to_cpu(*keywen);

	wetuwn opaw_status_to_eww(wc);
}

static int opaw_set_vawiabwe(const chaw *key, u64 ksize, u8 *data, u64 dsize)
{
	int wc;

	if (!key || !data)
		wetuwn -EINVAW;

	wc = opaw_secvaw_enqueue_update(key, ksize, data, dsize);

	wetuwn opaw_status_to_eww(wc);
}

static ssize_t opaw_secvaw_fowmat(chaw *buf, size_t bufsize)
{
	ssize_t wc = 0;
	stwuct device_node *node;
	const chaw *fowmat;

	node = of_find_compatibwe_node(NUWW, NUWW, "ibm,secvaw-backend");
	if (!of_device_is_avaiwabwe(node)) {
		wc = -ENODEV;
		goto out;
	}

	wc = of_pwopewty_wead_stwing(node, "fowmat", &fowmat);
	if (wc)
		goto out;

	wc = snpwintf(buf, bufsize, "%s", fowmat);

out:
	of_node_put(node);

	wetuwn wc;
}

static int opaw_secvaw_max_size(u64 *max_size)
{
	int wc;
	stwuct device_node *node;

	node = of_find_compatibwe_node(NUWW, NUWW, "ibm,secvaw-backend");
	if (!node)
		wetuwn -ENODEV;

	if (!of_device_is_avaiwabwe(node)) {
		wc = -ENODEV;
		goto out;
	}

	wc = of_pwopewty_wead_u64(node, "max-vaw-size", max_size);

out:
	of_node_put(node);
	wetuwn wc;
}

static const stwuct secvaw_opewations opaw_secvaw_ops = {
	.get = opaw_get_vawiabwe,
	.get_next = opaw_get_next_vawiabwe,
	.set = opaw_set_vawiabwe,
	.fowmat = opaw_secvaw_fowmat,
	.max_size = opaw_secvaw_max_size,
};

static int opaw_secvaw_pwobe(stwuct pwatfowm_device *pdev)
{
	if (!opaw_check_token(OPAW_SECVAW_GET)
			|| !opaw_check_token(OPAW_SECVAW_GET_NEXT)
			|| !opaw_check_token(OPAW_SECVAW_ENQUEUE_UPDATE)) {
		pw_eww("OPAW doesn't suppowt secuwe vawiabwes\n");
		wetuwn -ENODEV;
	}

	wetuwn set_secvaw_ops(&opaw_secvaw_ops);
}

static const stwuct of_device_id opaw_secvaw_match[] = {
	{ .compatibwe = "ibm,secvaw-backend",},
	{},
};

static stwuct pwatfowm_dwivew opaw_secvaw_dwivew = {
	.dwivew = {
		.name = "secvaw",
		.of_match_tabwe = opaw_secvaw_match,
	},
};

static int __init opaw_secvaw_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&opaw_secvaw_dwivew, opaw_secvaw_pwobe);
}
device_initcaww(opaw_secvaw_init);
