PRESET     := debug
BUILD      := $(CURDIR)/build/$(PRESET)
TARGETS    := all
TARGETS    += data
TARGETS    += demo-sphere demo-sphere-phong demo-sphere-gouraud demo-face demo-full
TARGETS    += docs docs-serve
TARGETS    += pretty clang-format cmake-format
TARGETS    += viewer viewer-triplet

$(TARGETS): build
	cmake --build $(BUILD) --parallel --target $@

.PHONY: build
build :
	cmake --preset $(PRESET)
	ln --force --relative --symbolic --no-target-directory $(BUILD)/compile_commands.json $(CURDIR)/build/compile_commands.json

clean:
	cmake --build $(BUILD) --parallel --target clean
	$(RM) --recursive $(CURDIR)/.cache
	$(RM) --recursive $(CURDIR)/build
