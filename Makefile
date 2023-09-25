BUILD_DIR = ./build
SRC_DIR = ./src
IMAGE_DIR = ./src/image
FONT_DIR = ./src/font
GAME_DIR = ./src/game

#--------------------------------------Makefile-------------------------------------
CFILES = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

IMAGECFILES = $(wildcard $(IMAGE_DIR)/*.c)
IMAGEOFILES = $(IMAGECFILES:$(IMAGE_DIR)/%.c=$(BUILD_DIR)/%.o)

FONTCFILES = $(wildcard $(FONT_DIR)/*.c)
FONTOFILES = $(FONTCFILES:$(FONT_DIR)/%.c=$(BUILD_DIR)/%.o)

GAMECFILES = $(wildcard $(GAME_DIR)/*.c)
GAMEOFILES = $(GAMECFILES:$(GAME_DIR)/%.c=$(BUILD_DIR)/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib 

all: clean kernel8.img run

$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c     
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(IMAGE_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(FONT_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(GAME_DIR)/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@
 
kernel8.img: $(BUILD_DIR)/boot.o $(OFILES) $(IMAGEOFILES) $(FONTOFILES) $(GAMEOFILES)
	aarch64-none-elf-ld $(BUILD_DIR)/boot.o $(LDFLAGS) $(OFILES) $(IMAGEOFILES) $(FONTOFILES)  $(GAMEOFILES) -T $(SRC_DIR)/link.ld -o $(BUILD_DIR)/kernel8.elf
	aarch64-none-elf-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

clean:
	del  *.img .\build\*.elf .\build\*.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio