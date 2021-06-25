-- The NEORV32 RISC-V Processor, https://github.com/stnolting/neorv32
-- Auto-generated memory init file (for APPLICATION) from source file <blink_led/main.bin>
-- Size: 64 bytes

library ieee;
use ieee.std_logic_1164.all;

library neorv32;
use neorv32.neorv32_package.all;

package neorv32_application_image is

  constant application_init_image : mem32_t := (
    00000000 => x"00000013",
    00000001 => x"00000517",
    00000002 => x"01c50513",
    00000003 => x"30551073",
    00000004 => x"30001073",
    00000005 => x"30401073",
    00000006 => x"f8400513",
    00000007 => x"00052023",
    00000008 => x"00052583",
    00000009 => x"fff5c593",
    00000010 => x"00b52023",
    00000011 => x"001e85b7",
    00000012 => x"48058593",
    00000013 => x"fff58593",
    00000014 => x"fe059ee3",
    00000015 => x"fe5ff06f"
  );

end neorv32_application_image;
