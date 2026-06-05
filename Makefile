EDITOR = nvim 
WORKING_DIR = my_keymap/henris_base/
WORKING_KEYMAP = my_keymap/henris_base/keymap.c 
KEYBOARD_DEFAULT_FOLDER = qmk_firmware/keyboards/ergodox_ez/glow/keymaps/default/
CONFIG_FILE = qmk_firmware/keyboards/ergodox_ez/config.h
HARDWARE = ergodox_ez/glow
MMCU = atmega32u4

MAKEFLAGS += --no-print-directory
 
.PHONY: edit compile compiledb sync restore_default flash 

edit: 
	@$(EDITOR) $(WORKING_KEYMAP) 

	 
sync: 
	@rsync -av --exclude='.git' --exclude='.codex' --exclude='.agents' $(WORKING_DIR) $(KEYBOARD_DEFAULT_FOLDER) 
	@rsync -av --exclude='.git' --exclude='.codex' --exclude='.agents' $(WORKING_DIR)config.h $(CONFIG_FILE)

compile: sync
	@cd qmk_firmware && qmk compile -kb $(HARDWARE) -km default 

compiledb: sync 
	@cd qmk_firmware && qmk compile -kb $(HARDWARE) -km default --compiledb

restore_default: 
	@rsync -av default/default/ $(KEYBOARD_DEFAULT_FOLDER)
	@rsync -av default/default/config.h $(CONFIG_FILE)
	@cd qmk_firmware && rm keyboards/ergodox_ez/glow/keymaps/default/config.h && git restore .

flash: compile 
	@echo 'Press bootloader button to flash...'
	@cd qmk_firmware && teensy_loader_cli -mmcu=$(MMCU) -w ergodox_ez_glow_default.hex
	@echo 'Successfully flashed'
	@$(MAKE) restore_default 2>&1
	@echo 'default keymap in qmk directory restored'

