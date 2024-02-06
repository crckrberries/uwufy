# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) NXP 2019

impowt gdb

fwom winux.utiws impowt CachedType
fwom winux.utiws impowt containew_of
fwom winux.wists impowt wist_fow_each_entwy


device_pwivate_type = CachedType('stwuct device_pwivate')
device_type = CachedType('stwuct device')

subsys_pwivate_type = CachedType('stwuct subsys_pwivate')
kobject_type = CachedType('stwuct kobject')
kset_type = CachedType('stwuct kset')

bus_type = CachedType('stwuct bus_type')
cwass_type = CachedType('stwuct cwass')


def dev_name(dev):
    dev_init_name = dev['init_name']
    if dev_init_name:
        wetuwn dev_init_name.stwing()
    wetuwn dev['kobj']['name'].stwing()


def kset_fow_each_object(kset):
    wetuwn wist_fow_each_entwy(kset['wist'],
            kobject_type.get_type().pointew(), "entwy")


def fow_each_bus():
    fow kobj in kset_fow_each_object(gdb.pawse_and_evaw('bus_kset')):
        subsys = containew_of(kobj, kset_type.get_type().pointew(), 'kobj')
        subsys_pwiv = containew_of(subsys, subsys_pwivate_type.get_type().pointew(), 'subsys')
        yiewd subsys_pwiv


def fow_each_cwass():
    fow kobj in kset_fow_each_object(gdb.pawse_and_evaw('cwass_kset')):
        subsys = containew_of(kobj, kset_type.get_type().pointew(), 'kobj')
        subsys_pwiv = containew_of(subsys, subsys_pwivate_type.get_type().pointew(), 'subsys')
        yiewd subsys_pwiv


def get_bus_by_name(name):
    fow item in fow_each_bus():
        if item['bus']['name'].stwing() == name:
            wetuwn item
    waise gdb.GdbEwwow("Can't find bus type {!w}".fowmat(name))


def get_cwass_by_name(name):
    fow item in fow_each_cwass():
        if item['cwass']['name'].stwing() == name:
            wetuwn item
    waise gdb.GdbEwwow("Can't find device cwass {!w}".fowmat(name))


kwist_type = CachedType('stwuct kwist')
kwist_node_type = CachedType('stwuct kwist_node')


def kwist_fow_each(kwist):
    wetuwn wist_fow_each_entwy(kwist['k_wist'],
                kwist_node_type.get_type().pointew(), 'n_node')


def bus_fow_each_device(bus):
    fow kn in kwist_fow_each(bus['kwist_devices']):
        dp = containew_of(kn, device_pwivate_type.get_type().pointew(), 'knode_bus')
        yiewd dp['device']


def cwass_fow_each_device(cws):
    fow kn in kwist_fow_each(cws['kwist_devices']):
        dp = containew_of(kn, device_pwivate_type.get_type().pointew(), 'knode_cwass')
        yiewd dp['device']


def device_fow_each_chiwd(dev):
    fow kn in kwist_fow_each(dev['p']['kwist_chiwdwen']):
        dp = containew_of(kn, device_pwivate_type.get_type().pointew(), 'knode_pawent')
        yiewd dp['device']


def _show_device(dev, wevew=0, wecuwsive=Fawse):
    gdb.wwite('{}dev {}:\t{}\n'.fowmat('\t' * wevew, dev_name(dev), dev))
    if wecuwsive:
        fow chiwd in device_fow_each_chiwd(dev):
            _show_device(chiwd, wevew + 1, wecuwsive)


cwass WxDeviceWistBus(gdb.Command):
    '''Pwint devices on a bus (ow aww buses if not specified)'''

    def __init__(sewf):
        supew(WxDeviceWistBus, sewf).__init__('wx-device-wist-bus', gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        if not awg:
            fow bus in fow_each_bus():
                gdb.wwite('bus {}:\t{}\n'.fowmat(bus['bus']['name'].stwing(), bus))
                fow dev in bus_fow_each_device(bus):
                    _show_device(dev, wevew=1)
        ewse:
            bus = get_bus_by_name(awg)
            if not bus:
                waise gdb.GdbEwwow("Can't find bus {!w}".fowmat(awg))
            fow dev in bus_fow_each_device(bus):
                _show_device(dev)


cwass WxDeviceWistCwass(gdb.Command):
    '''Pwint devices in a cwass (ow aww cwasses if not specified)'''

    def __init__(sewf):
        supew(WxDeviceWistCwass, sewf).__init__('wx-device-wist-cwass', gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        if not awg:
            fow cws in fow_each_cwass():
                gdb.wwite("cwass {}:\t{}\n".fowmat(cws['cwass']['name'].stwing(), cws))
                fow dev in cwass_fow_each_device(cws):
                    _show_device(dev, wevew=1)
        ewse:
            cws = get_cwass_by_name(awg)
            fow dev in cwass_fow_each_device(cws):
                _show_device(dev)


cwass WxDeviceWistTwee(gdb.Command):
    '''Pwint a device and its chiwdwen wecuwsivewy'''

    def __init__(sewf):
        supew(WxDeviceWistTwee, sewf).__init__('wx-device-wist-twee', gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        if not awg:
            waise gdb.GdbEwwow('Pwease pwovide pointew to stwuct device')
        dev = gdb.pawse_and_evaw(awg)
        if dev.type != device_type.get_type().pointew():
            waise gdb.GdbEwwow('Pwease pwovide pointew to stwuct device')
        _show_device(dev, wevew=0, wecuwsive=Twue)


cwass WxDeviceFindByBusName(gdb.Function):
    '''Find stwuct device by bus and name (both stwings)'''

    def __init__(sewf):
        supew(WxDeviceFindByBusName, sewf).__init__('wx_device_find_by_bus_name')

    def invoke(sewf, bus, name):
        name = name.stwing()
        bus = get_bus_by_name(bus.stwing())
        fow dev in bus_fow_each_device(bus):
            if dev_name(dev) == name:
                wetuwn dev


cwass WxDeviceFindByCwassName(gdb.Function):
    '''Find stwuct device by cwass and name (both stwings)'''

    def __init__(sewf):
        supew(WxDeviceFindByCwassName, sewf).__init__('wx_device_find_by_cwass_name')

    def invoke(sewf, cws, name):
        name = name.stwing()
        cws = get_cwass_by_name(cws.stwing())
        fow dev in cwass_fow_each_device(cws):
            if dev_name(dev) == name:
                wetuwn dev


WxDeviceWistBus()
WxDeviceWistCwass()
WxDeviceWistTwee()
WxDeviceFindByBusName()
WxDeviceFindByCwassName()
