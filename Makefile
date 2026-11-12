Q ?= @
CC = arm-none-eabi-gcc
BUILD_DIR = output
NWLINK = npx --yes -- nwlink@0.0.16

src = src/main.c
CFLAGS = -std=c99
CFLAGS += $(shell $(NWLINK) eadk-cflags)
CFLAGS += -Os -Wall -Wextra
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -ggdb
LDFLAGS = -Wl,--relocatable -nostartfiles --specs=nano.specs
LDFLAGS += -Wl,-e,main -Wl,-u,eadk_app_name -Wl,-u,eadk_app_icon -Wl,-u,eadk_api_level
LDFLAGS += -Wl,--gc-sections
CFLAGS += -flto -fno-fat-lto-objects -fwhole-program -fvisibility=internal
LDFLAGS += -flinker-output=nolto-rel

.PHONY: build clean
build: $(BUILD_DIR)/app.nwa

$(BUILD_DIR)/app.nwa: $(BUILD_DIR)/main.o $(BUILD_DIR)/icon.o
	$(Q) $(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: src/main.c | $(BUILD_DIR)
	$(Q) $(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/icon.o: src/icon.png | $(BUILD_DIR)
	$(Q) $(NWLINK) png-icon-o $< $@

$(BUILD_DIR):
	$(Q) mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	$(Q) rm -rf $(BUILD_DIR)
