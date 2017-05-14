CC=gcc
CC_FLAGS=-g -O0 -Wall -Wextra -std=c99
# CC_FLAGS=-g -Wall -Wextra -std=c99 -O3 -msse2 -mavx -mfpmath=sse

all: floating_point_numbers

floating_point_numbers: floating_point_numbers.c
	$(CC) $(CC_FLAGS) -o floating_point_numbers floating_point_numbers.c -lrt
	@echo "------------"

clean:
	rm -vf floating_point_numbers

.PHONEY: clean
