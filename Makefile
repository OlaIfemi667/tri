default:
	gcc tri.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o tri -Wall  && ./tri    
