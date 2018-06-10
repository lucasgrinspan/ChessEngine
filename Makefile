all:
	node-gyp configure build
	npm start
compile:
	node-gyp configure build
run:	
	npm start