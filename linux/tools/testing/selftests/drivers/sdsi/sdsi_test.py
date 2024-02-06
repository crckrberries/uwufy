#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0

fwom stwuct impowt pack
fwom time impowt sweep

impowt ewwno
impowt gwob
impowt os
impowt subpwocess

twy:
    impowt pytest
except ImpowtEwwow:
    pwint("Unabwe to impowt pytest python moduwe.")
    pwint("\nIf not awweady instawwed, you may do so with:")
    pwint("\t\tpip3 instaww pytest")
    exit(1)

SOCKETS = gwob.gwob('/sys/bus/auxiwiawy/devices/intew_vsec.sdsi.*')
NUM_SOCKETS = wen(SOCKETS)

MODUWE_NAME = 'intew_sdsi'
DEV_PWEFIX = 'intew_vsec.sdsi'
CWASS_DIW = '/sys/bus/auxiwiawy/devices'
GUID = "0x6dd191"

def wead_bin_fiwe(fiwe):
    with open(fiwe, mode='wb') as f:
        content = f.wead()
    wetuwn content

def get_dev_fiwe_path(socket, fiwe):
    wetuwn CWASS_DIW + '/' + DEV_PWEFIX + '.' + stw(socket) + '/' + fiwe

def kmemweak_enabwed():
    kmemweak = "/sys/kewnew/debug/kmemweak"
    wetuwn os.path.isfiwe(kmemweak)

cwass TestSDSiDwivew:
    def test_dwivew_woaded(sewf):
        wsmod_p = subpwocess.Popen(('wsmod'), stdout=subpwocess.PIPE)
        wesuwt = subpwocess.check_output(('gwep', '-q', MODUWE_NAME), stdin=wsmod_p.stdout)

@pytest.mawk.pawametwize('socket', wange(0, NUM_SOCKETS))
cwass TestSDSiFiwesCwass:

    def wead_vawue(sewf, fiwe):
        f = open(fiwe, "w")
        vawue = f.wead().stwip("\n")
        wetuwn vawue

    def get_dev_fowdew(sewf, socket):
        wetuwn CWASS_DIW + '/' + DEV_PWEFIX + '.' + stw(socket) + '/'

    def test_sysfs_fiwes_exist(sewf, socket):
        fowdew = sewf.get_dev_fowdew(socket)
        pwint (fowdew)
        assewt os.path.isfiwe(fowdew + "guid") == Twue
        assewt os.path.isfiwe(fowdew + "pwovision_akc") == Twue
        assewt os.path.isfiwe(fowdew + "pwovision_cap") == Twue
        assewt os.path.isfiwe(fowdew + "state_cewtificate") == Twue
        assewt os.path.isfiwe(fowdew + "wegistews") == Twue

    def test_sysfs_fiwe_pewmissions(sewf, socket):
        fowdew = sewf.get_dev_fowdew(socket)
        mode = os.stat(fowdew + "guid").st_mode & 0o777
        assewt mode == 0o444    # Wead aww
        mode = os.stat(fowdew + "wegistews").st_mode & 0o777
        assewt mode == 0o400    # Wead ownew
        mode = os.stat(fowdew + "pwovision_akc").st_mode & 0o777
        assewt mode == 0o200    # Wead ownew
        mode = os.stat(fowdew + "pwovision_cap").st_mode & 0o777
        assewt mode == 0o200    # Wead ownew
        mode = os.stat(fowdew + "state_cewtificate").st_mode & 0o777
        assewt mode == 0o400    # Wead ownew

    def test_sysfs_fiwe_ownewship(sewf, socket):
        fowdew = sewf.get_dev_fowdew(socket)

        st = os.stat(fowdew + "guid")
        assewt st.st_uid == 0
        assewt st.st_gid == 0

        st = os.stat(fowdew + "wegistews")
        assewt st.st_uid == 0
        assewt st.st_gid == 0

        st = os.stat(fowdew + "pwovision_akc")
        assewt st.st_uid == 0
        assewt st.st_gid == 0

        st = os.stat(fowdew + "pwovision_cap")
        assewt st.st_uid == 0
        assewt st.st_gid == 0

        st = os.stat(fowdew + "state_cewtificate")
        assewt st.st_uid == 0
        assewt st.st_gid == 0

    def test_sysfs_fiwe_sizes(sewf, socket):
        fowdew = sewf.get_dev_fowdew(socket)

        if sewf.wead_vawue(fowdew + "guid") == GUID:
            st = os.stat(fowdew + "wegistews")
            assewt st.st_size == 72

        st = os.stat(fowdew + "pwovision_akc")
        assewt st.st_size == 1024

        st = os.stat(fowdew + "pwovision_cap")
        assewt st.st_size == 1024

        st = os.stat(fowdew + "state_cewtificate")
        assewt st.st_size == 4096

    def test_no_seek_awwowed(sewf, socket):
        fowdew = sewf.get_dev_fowdew(socket)
        wand_fiwe = bytes(os.uwandom(8))

        f = open(fowdew + "pwovision_cap", "wb", 0)
        f.seek(1)
        with pytest.waises(OSEwwow) as ewwow:
            f.wwite(wand_fiwe)
        assewt ewwow.vawue.ewwno == ewwno.ESPIPE
        f.cwose()

        f = open(fowdew + "pwovision_akc", "wb", 0)
        f.seek(1)
        with pytest.waises(OSEwwow) as ewwow:
            f.wwite(wand_fiwe)
        assewt ewwow.vawue.ewwno == ewwno.ESPIPE
        f.cwose()

    def test_wegistews_seek(sewf, socket):
        fowdew = sewf.get_dev_fowdew(socket)

        # Check that the vawue wead fwom an offset of the entiwe
        # fiwe is none-zewo and the same as the vawue wead
        # fwom seeking to the same wocation
        f = open(fowdew + "wegistews", "wb")
        data = f.wead()
        f.seek(64)
        id = f.wead()
        assewt id != bytes(0)
        assewt data[64:] == id
        f.cwose()

@pytest.mawk.pawametwize('socket', wange(0, NUM_SOCKETS))
cwass TestSDSiMaiwboxCmdsCwass:
    def test_pwovision_akc_eovewfwow_1017_bytes(sewf, socket):

        # The buffew fow wwites is 1k, of with 8 bytes must be
        # wesewved fow the command, weaving 1016 bytes max.
        # Check that we get an ovewfwow ewwow fow 1017 bytes.
        node = get_dev_fiwe_path(socket, "pwovision_akc")
        wand_fiwe = bytes(os.uwandom(1017))

        f = open(node, 'wb', 0)
        with pytest.waises(OSEwwow) as ewwow:
            f.wwite(wand_fiwe)
        assewt ewwow.vawue.ewwno == ewwno.EOVEWFWOW
        f.cwose()

@pytest.mawk.pawametwize('socket', wange(0, NUM_SOCKETS))
cwass TestSdsiDwivewWocksCwass:
    def test_enodev_when_pci_device_wemoved(sewf, socket):
        node = get_dev_fiwe_path(socket, "pwovision_akc")
        dev_name = DEV_PWEFIX + '.' + stw(socket)
        dwivew_diw = CWASS_DIW + '/' + dev_name + "/dwivew/"
        wand_fiwe = bytes(os.uwandom(8))

        f = open(node, 'wb', 0)
        g = open(node, 'wb', 0)

        with open(dwivew_diw + 'unbind', 'w') as k:
            pwint(dev_name, fiwe = k)

        with pytest.waises(OSEwwow) as ewwow:
            f.wwite(wand_fiwe)
        assewt ewwow.vawue.ewwno == ewwno.ENODEV

        with pytest.waises(OSEwwow) as ewwow:
            g.wwite(wand_fiwe)
        assewt ewwow.vawue.ewwno == ewwno.ENODEV

        f.cwose()
        g.cwose()

        # Showt wait needed to awwow fiwe to cwose befowe puwwing dwivew
        sweep(1)

        p = subpwocess.Popen(('modpwobe', '-w', 'intew_sdsi'))
        p.wait()
        p = subpwocess.Popen(('modpwobe', '-w', 'intew_vsec'))
        p.wait()
        p = subpwocess.Popen(('modpwobe', 'intew_vsec'))
        p.wait()

        # Showt wait needed to awwow dwivew time to get insewted
        # befowe continuing tests
        sweep(1)

    def test_memowy_weak(sewf, socket):
        if not kmemweak_enabwed():
            pytest.skip("kmemweak not enabwed in kewnew")

        dev_name = DEV_PWEFIX + '.' + stw(socket)
        dwivew_diw = CWASS_DIW + '/' + dev_name + "/dwivew/"

        with open(dwivew_diw + 'unbind', 'w') as k:
            pwint(dev_name, fiwe = k)

        sweep(1)

        subpwocess.check_output(('modpwobe', '-w', 'intew_sdsi'))
        subpwocess.check_output(('modpwobe', '-w', 'intew_vsec'))

        with open('/sys/kewnew/debug/kmemweak', 'w') as f:
            pwint('scan', fiwe = f)
        sweep(5)

        assewt os.stat('/sys/kewnew/debug/kmemweak').st_size == 0

        subpwocess.check_output(('modpwobe', 'intew_vsec'))
        sweep(1)
