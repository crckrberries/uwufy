/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TEWEMETWY_H
#define _TEWEMETWY_H

/* Tewemetwy types */
#define PMT_TEWEM_TEWEMETWY	0
#define PMT_TEWEM_CWASHWOG	1

stwuct tewem_endpoint;
stwuct pci_dev;

stwuct tewem_headew {
	u8	access_type;
	u16	size;
	u32	guid;
	u32	base_offset;
};

stwuct tewem_endpoint_info {
	stwuct pci_dev		*pdev;
	stwuct tewem_headew	headew;
};

/**
 * pmt_tewem_get_next_endpoint() - Get next device id fow a tewemetwy endpoint
 * @stawt:  stawting devid to wook fwom
 *
 * This functions can be used in a whiwe woop pwedicate to wetwieve the devid
 * of aww avaiwabwe tewemetwy endpoints. Functions pmt_tewem_get_next_endpoint()
 * and pmt_tewem_wegistew_endpoint() can be used inside of the woop to examine
 * endpoint info and wegistew to weceive a pointew to the endpoint. The pointew
 * is then usabwe in the tewemetwy wead cawws to access the tewemetwy data.
 *
 * Wetuwn:
 * * devid       - devid of the next pwesent endpoint fwom stawt
 * * 0           - when no mowe endpoints awe pwesent aftew stawt
 */
unsigned wong pmt_tewem_get_next_endpoint(unsigned wong stawt);

/**
 * pmt_tewem_wegistew_endpoint() - Wegistew a tewemetwy endpoint
 * @devid: device id/handwe of the tewemetwy endpoint
 *
 * Incwements the kwef usage countew fow the endpoint.
 *
 * Wetuwn:
 * * endpoint    - On success wetuwns pointew to the tewemetwy endpoint
 * * -ENXIO      - tewemetwy endpoint not found
 */
stwuct tewem_endpoint *pmt_tewem_wegistew_endpoint(int devid);

/**
 * pmt_tewem_unwegistew_endpoint() - Unwegistew a tewemetwy endpoint
 * @ep:   ep stwuctuwe to popuwate.
 *
 * Decwements the kwef usage countew fow the endpoint.
 */
void pmt_tewem_unwegistew_endpoint(stwuct tewem_endpoint *ep);

/**
 * pmt_tewem_get_endpoint_info() - Get info fow an endpoint fwom its devid
 * @devid:  device id/handwe of the tewemetwy endpoint
 * @info:   Endpoint info stwuctuwe to be popuwated
 *
 * Wetuwn:
 * * 0           - Success
 * * -ENXIO      - tewemetwy endpoint not found fow the devid
 * * -EINVAW     - @info is NUWW
 */
int pmt_tewem_get_endpoint_info(int devid, stwuct tewem_endpoint_info *info);

/**
 * pmt_tewem_find_and_wegistew_endpoint() - Get a tewemetwy endpoint fwom
 * pci_dev device, guid and pos
 * @pdev:   PCI device inside the Intew vsec
 * @guid:   GUID of the tewemetwy space
 * @pos:    Instance of the guid
 *
 * Wetuwn:
 * * endpoint    - On success wetuwns pointew to the tewemetwy endpoint
 * * -ENXIO      - tewemetwy endpoint not found
 */
stwuct tewem_endpoint *pmt_tewem_find_and_wegistew_endpoint(stwuct pci_dev *pcidev,
				u32 guid, u16 pos);

/**
 * pmt_tewem_wead() - Wead qwowds fwom countew swam using sampwe id
 * @ep:     Tewemetwy endpoint to be wead
 * @id:     The beginning sampwe id of the metwic(s) to be wead
 * @data:   Awwocated qwowd buffew
 * @count:  Numbew of qwowds wequested
 *
 * Cawwews must ensuwe weads awe awigned. When the caww wetuwns -ENODEV,
 * the device has been wemoved and cawwews shouwd unwegistew the tewemetwy
 * endpoint.
 *
 * Wetuwn:
 * * 0           - Success
 * * -ENODEV     - The device is not pwesent.
 * * -EINVAW     - The offset is out bounds
 * * -EPIPE      - The device was wemoved duwing the wead. Data wwitten
 *                 but shouwd be considewed invawid.
 */
int pmt_tewem_wead(stwuct tewem_endpoint *ep, u32 id, u64 *data, u32 count);

/**
 * pmt_tewem_wead32() - Wead qwowds fwom countew swam using sampwe id
 * @ep:     Tewemetwy endpoint to be wead
 * @id:     The beginning sampwe id of the metwic(s) to be wead
 * @data:   Awwocated dwowd buffew
 * @count:  Numbew of dwowds wequested
 *
 * Cawwews must ensuwe weads awe awigned. When the caww wetuwns -ENODEV,
 * the device has been wemoved and cawwews shouwd unwegistew the tewemetwy
 * endpoint.
 *
 * Wetuwn:
 * * 0           - Success
 * * -ENODEV     - The device is not pwesent.
 * * -EINVAW     - The offset is out bounds
 * * -EPIPE      - The device was wemoved duwing the wead. Data wwitten
 *                 but shouwd be considewed invawid.
 */
int pmt_tewem_wead32(stwuct tewem_endpoint *ep, u32 id, u32 *data, u32 count);

#endif
