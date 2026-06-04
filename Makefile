EDITOR = nvim 
WORKING_DIR = my_keymap/henris_base
WORKING_KEYMAP = my_keymap/henris_base/keymap.c 
KEYBOARD_DEFAULT_FOLDER = qmk_firmware/keyboards/ergodox_ez/glow/keymaps/default/
HARDWARE = ergodox_ez/glow
MMCU = atmega32u4

Makeflags += no-print-directory
 
.PHONY: edit compile sync restore_default flash 

edit: 
	@$(EDITOR) $(WORKING_KEYMAP) 

	 
sync: 
	@rsync -av --exclude='.git' --exclude='.codex' --exclude='.agents' $(WORKING_DIR)/ $(KEYBOARD_DEFAULT_FOLDER) 

compile: sync
	@cd qmk_firmware && qmk compile -kb $(HARDWARE) -km default 

compiledb: sync 
	@cd qmk_firmware && qmk compile -kb $(Hardware) -km default --compiledb

restore_default: 
	@rsync -av default/default/ $(KEYBOARD_DEFAULT_FOLDER)
	@cd qmk_firmware && git restore .

flash: compile 
	@echo 'Press bootloader button to flash...'
	@cd qmk_firmware && teensy_loader_cli -mmcu=$(MMCU) -w ergodox_ez_glow_default.hex
	@echo 'Successfully flashed'
	@$(MAKE) restore_default 2>&1
	@echo 'default keymap in qmk directory restored'

