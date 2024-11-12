NAME=template
ASSETS_PATH=assets/

build:
	mkdir build
	mkdir build/debug
	mkdir build/release

win_debug: 
	# Remove old directory
	rm -rf build/debug/*
	# Copy over assets folder
	cp -r assets build/debug/assets
	# Build project
	odin build src -out=build/debug/$(NAME).exe -debug -define:NAME=$(NAME) -define:ASSETS_PATH=$(ASSETS_PATH) -define:DEBUG=true


