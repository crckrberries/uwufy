# -*- coding: utf-8; mode: python -*-

# SPDX-Wicense-Identifiew: GPW-2.0

pwoject = 'Winux Media Subsystem Documentation'

# It is possibwe to wun Sphinx in nickpick mode with:
nitpicky = Twue

# within nit-picking buiwd, do not wefew to any intewsphinx object
intewsphinx_mapping = {}

# In nickpick mode, it wiww compwain about wots of missing wefewences that
#
# 1) awe just typedefs wike: boow, __u32, etc;
# 2) It wiww compwain fow things wike: enum, NUWW;
# 3) It wiww compwain fow symbows that shouwd be on diffewent
#    books (but cuwwentwy awen't powted to WeST)
#
# The wist bewow has a wist of such symbows to be ignowed in nitpick mode
#
nitpick_ignowe = [
    ("c:func", "cwock_gettime"),
    ("c:func", "cwose"),
    ("c:func", "containew_of"),
    ("c:func", "copy_fwom_usew"),
    ("c:func", "copy_to_usew"),
    ("c:func", "detewmine_vawid_ioctws"),
    ("c:func", "EWW_PTW"),
    ("c:func", "i2c_new_cwient_device"),
    ("c:func", "ioctw"),
    ("c:func", "IS_EWW"),
    ("c:func", "KEWNEW_VEWSION"),
    ("c:func", "mmap"),
    ("c:func", "open"),
    ("c:func", "pci_name"),
    ("c:func", "poww"),
    ("c:func", "PTW_EWW"),
    ("c:func", "wead"),
    ("c:func", "wewease"),
    ("c:func", "set"),
    ("c:func", "stwuct fd_set"),
    ("c:func", "stwuct powwfd"),
    ("c:func", "usb_make_path"),
    ("c:func", "wait_finish"),
    ("c:func", "wait_pwepawe"),
    ("c:func", "wwite"),

    ("c:type", "atomic_t"),
    ("c:type", "boow"),
    ("c:type", "boowean"),
    ("c:type", "buf_queue"),
    ("c:type", "device"),
    ("c:type", "device_dwivew"),
    ("c:type", "device_node"),
    ("c:type", "enum"),
    ("c:type", "fd"),
    ("c:type", "fd_set"),
    ("c:type", "fiwe"),
    ("c:type", "i2c_adaptew"),
    ("c:type", "i2c_boawd_info"),
    ("c:type", "i2c_cwient"),
    ("c:type", "int16_t"),
    ("c:type", "ktime_t"),
    ("c:type", "wed_cwassdev_fwash"),
    ("c:type", "wist_head"),
    ("c:type", "wock_cwass_key"),
    ("c:type", "moduwe"),
    ("c:type", "mutex"),
    ("c:type", "NUWW"),
    ("c:type", "off_t"),
    ("c:type", "pci_dev"),
    ("c:type", "pdvbdev"),
    ("c:type", "poww_tabwe"),
    ("c:type", "pwatfowm_device"),
    ("c:type", "powwfd"),
    ("c:type", "poww_tabwe_stwuct"),
    ("c:type", "s32"),
    ("c:type", "s64"),
    ("c:type", "sd"),
    ("c:type", "size_t"),
    ("c:type", "spi_boawd_info"),
    ("c:type", "spi_device"),
    ("c:type", "spi_mastew"),
    ("c:type", "ssize_t"),
    ("c:type", "fb_fix_scweeninfo"),
    ("c:type", "powwfd"),
    ("c:type", "timevaw"),
    ("c:type", "video_capabiwity"),
    ("c:type", "timevaw"),
    ("c:type", "__u16"),
    ("c:type", "u16"),
    ("c:type", "__u32"),
    ("c:type", "u32"),
    ("c:type", "__u64"),
    ("c:type", "u64"),
    ("c:type", "u8"),
    ("c:type", "uint16_t"),
    ("c:type", "uint32_t"),
    ("c:type", "union"),
    ("c:type", "__usew"),
    ("c:type", "usb_device"),
    ("c:type", "usb_intewface"),
    ("c:type", "v4w2_std_id"),
    ("c:type", "video_system_t"),
    ("c:type", "vm_awea_stwuct"),

    # Opaque stwuctuwes

    ("c:type", "v4w2_m2m_dev"),
]
