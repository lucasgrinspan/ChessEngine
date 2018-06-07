all:
	compile
	run
compile:
	node-gyp configure build
run:	
	npm start