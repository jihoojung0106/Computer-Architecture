# This must point to raw2img.py from part 1 of the term project. 
# Adjust path if necessary.
RAW2IMG=../../../part-1/raw2img.py

RAW=$(wildcard *.raw)
PNG=$(RAW:%.raw=%.png)

all: $(PNG)

%.png: %.raw
	@$(RAW2IMG) $^

clean:
	@rm -f *.png
