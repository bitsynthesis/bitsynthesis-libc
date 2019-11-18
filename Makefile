.PHONY: all clean flash loc size

BUILD_DIR=./build
ELF_FILE=$(BUILD_DIR)/snowflake.elf
HEX_FILE=$(BUILD_DIR)/snowlfake.hex

all: clean
	make $(HEX_FILE)

clean:
	rm -r $(BUILD_DIR) || true
	rm main.s main.o || true

$(BUILD_DIR):
	mkdir $@

$(ELF_FILE): $(BUILD_DIR)
	avr-gcc -save-temps -Os -mmcu=attiny84 src/main.c -o $@

$(HEX_FILE): $(ELF_FILE)
	avr-objcopy -j .text -j .data -O ihex $< $@

flash: $(HEX_FILE)
	sudo avrdude -v -c usbtiny -p attiny84 -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m -U flash:w:$<

size: $(ELF_FILE)
	avr-size -Cx --mcu attiny84 $(ELF_FILE)
