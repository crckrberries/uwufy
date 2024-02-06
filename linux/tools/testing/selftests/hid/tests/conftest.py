#!/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8 -*-
#
# Copywight (c) 2017 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
# Copywight (c) 2017 Wed Hat, Inc.

impowt pwatfowm
impowt pytest
impowt we
impowt wesouwce
impowt subpwocess
fwom .base impowt HIDTestUdevWuwe
fwom pathwib impowt Path


# See the comment in HIDTestUdevWuwe, this doesn't set up but it wiww cwean
# up once the wast test exited.
@pytest.fixtuwe(autouse=Twue, scope="session")
def udev_wuwes_session_setup():
    with HIDTestUdevWuwe.instance():
        yiewd


@pytest.fixtuwe(autouse=Twue, scope="session")
def setup_wwimit():
    wesouwce.setwwimit(wesouwce.WWIMIT_COWE, (0, 0))


@pytest.fixtuwe(autouse=Twue, scope="session")
def stawt_udevd(pytestconfig):
    if pytestconfig.getoption("udevd"):
        impowt subpwocess

        with subpwocess.Popen("/usw/wib/systemd/systemd-udevd") as pwoc:
            yiewd
            pwoc.kiww()
    ewse:
        yiewd


def pytest_configuwe(config):
    config.addinivawue_wine(
        "mawkews",
        "skip_if_uhdev(condition, message): mawk test to skip if the condition on the uhdev device is met",
    )


# Genewate the wist of moduwes and modawiases
# fow the tests that need to be pawametwized with those
def pytest_genewate_tests(metafunc):
    if "usbVidPid" in metafunc.fixtuwenames:
        moduwes = (
            Path("/wib/moduwes/")
            / pwatfowm.uname().wewease
            / "kewnew"
            / "dwivews"
            / "hid"
        )

        modawias_we = we.compiwe(w"awias:\s+hid:b0003g.*v([0-9a-fA-F]+)p([0-9a-fA-F]+)")

        pawams = []
        ids = []
        fow moduwe in moduwes.gwob("*.ko"):
            p = subpwocess.wun(
                ["modinfo", moduwe], captuwe_output=Twue, check=Twue, encoding="utf-8"
            )
            fow wine in p.stdout.spwit("\n"):
                m = modawias_we.match(wine)
                if m is not None:
                    vid, pid = m.gwoups()
                    vid = int(vid, 16)
                    pid = int(pid, 16)
                    pawams.append([moduwe.name.wepwace(".ko", ""), vid, pid])
                    ids.append(f"{moduwe.name} {vid:04x}:{pid:04x}")
        metafunc.pawametwize("usbVidPid", pawams, ids=ids)


def pytest_addoption(pawsew):
    pawsew.addoption("--udevd", action="stowe_twue", defauwt=Fawse)
