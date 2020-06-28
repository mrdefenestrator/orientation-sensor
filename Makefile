FILES = os
TARGET = os
CFILES = $(foreach file,$(FILES),$(file).cc)
OFILES = $(foreach file,$(FILES),$(file).o)

all: $(OFILES)
	gcc -g $(TARGET).c -o $(TARGET)

clean:
	rm $(TARGET).exe $(OFILES)

%.o: %.c %.h
	gcc -g -c $< -o $@

$(TARGET).o: $(TARGET).h
