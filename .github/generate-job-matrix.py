#!/usr/bin/env python3

print('::set-output name=matrix::' + str([
{
  'board': 'UPduino_v3',
  'design': 'MinimalBoot',
  'bitstream': 'neorv32_UPduino_v3_MinimalBoot.bin'
}, {
  'board': 'UPduino_v3',
  'design': 'UP5KDemo',
  'bitstream': 'neorv32_UPduino_v3_UP5KDemo.bin'
}, {
  'board': 'Fomu',
  'design': 'Minimal',
  'bitstream': 'neorv32_Fomu_pvt_Minimal.bit'
}, {
  'board': 'Fomu',
  'design': 'MinimalBoot',
  'bitstream': 'neorv32_Fomu_pvt_MinimalBoot.bit'
}, {
  'board': 'Fomu',
  'design': 'UP5KDemo',
  'bitstream': 'neorv32_Fomu_pvt_UP5KDemo.bit'
}, {
  'board': 'TinyFPGA_BX',
  'design': 'MinimalBoot',
  'bitstream': 'neorv32_TinyFPGA_BX_MinimalBoot.bit'
}]))
