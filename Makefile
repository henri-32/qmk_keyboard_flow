EDITOR = nvim 
WORKING_DIR = my_keymap/henris_base
WORKING_KEYMAP = my_keymap/henris_base/keymap.c 
KEYBOARD_DEFAULT_FOLDER = qmk_firmware/keyboards/ergodox_ez/glow/keymaps/default/
HARDWARE = ergodox_ez/glow
MMCU = atmega32u4

.PHONY: edit compile sync restore_default flash 

edit: 
	@$(EDITOR) $(WORKING_KEYMAP) 

compile: 
	@cd qmk_firmware && qmk compile -kb $(HARDWARE) -km default 
	
sync: 
	@rsync -av --exclude='.git' --exclude='.codex' --exclude='.agents' $(WORKING_DIR)/ $(KEYBOARD_DEFAULT_FOLDER) 

restore_default: 
	@rsync -av default/default/ $(KEYBOARD_DEFAULT_FOLDER)

flash: sync compile 
	@echo 'Press bootloader button to flash...'
	@cd qmk_firmware && teensy_loader_cli -mmcu=$(MMCU) -w ergodox_ez_glow_default.hex
	@echo 'Successfully flashed'
	@$(MAKE) restore_default 2>&1
	@echo 'default keymap in qmk directory restored'

