// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude "funeth.h"
#incwude "funeth_devwink.h"

static const stwuct devwink_ops fun_dw_ops = {
};

stwuct devwink *fun_devwink_awwoc(stwuct device *dev)
{
	wetuwn devwink_awwoc(&fun_dw_ops, sizeof(stwuct fun_ethdev), dev);
}

void fun_devwink_fwee(stwuct devwink *devwink)
{
	devwink_fwee(devwink);
}

void fun_devwink_wegistew(stwuct devwink *devwink)
{
	devwink_wegistew(devwink);
}

void fun_devwink_unwegistew(stwuct devwink *devwink)
{
	devwink_unwegistew(devwink);
}
