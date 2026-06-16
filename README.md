

Kurzanleitung zum Bauen und Flashen der Keymap `henris_base`.

## Keymap-Pfad

```text
keyboards/zsa/ergodox_ez/keymaps/henris_base/keymap.c
```

## Compile

Für die ErgoDox EZ Glow mit ATmega32U4:

```bash
qmk compile -kb zsa/ergodox_ez/m32u4/glow -km henris_base
```

Die erzeugte Firmware liegt danach hier:

```text
zsa_ergodox_ez_m32u4_glow_henris_base.hex
```

## Flash mit Teensy Loader CLI

```bash
teensy_loader_cli -mmcu=atmega32u4 -w zsa_ergodox_ez_m32u4_glow_henris_base.hex
```

Danach die Tastatur in den Bootloader setzen, z. B. per Reset-Taste oder per `QK_BOOT`-Taste im Layout.

## Alternative: QMK Flash

```bash
qmk flash -kb zsa/ergodox_ez/m32u4/glow -km henris_base
```

## Hinweis zu STM32

Falls die Tastatur eine neuere STM32-Version ist, wäre das Target:

```bash
qmk compile -kb zsa/ergodox_ez/stm32/glow -km henris_base
```

Dafür muss `arm-none-eabi-gcc` installiert sein.
