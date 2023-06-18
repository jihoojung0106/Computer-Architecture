RESOLUTION=256 512 1024
PNG=$(foreach res, $(RESOLUTION),$(wildcard *_$(res).png))
RAW=$(PNG:%.png=%.raw)

all: $(RAW)

%.raw: %.png
	@../img2raw.py $^

clean:
	@rm -f *.raw *int.png *float.png
