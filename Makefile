ifeq ($(OS), Windows_NT)
	EXECUTABLE = bin/generate_data.exe
else
	EXECUTABLE = bin/generate_data
endif

all: $(EXECUTABLE)

$(EXECUTABLE): src/C/generate_data.c
	gcc src/C/generate_data.c -o $(EXECUTABLE)



clean:
	rm -f $(EXECUTABLE)